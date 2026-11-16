#!/usr/bin/env python3
"""Package a freshly compiled Arduino ESP32-S3 build for safe ESP Web Tools flashing.

Requires the four binaries from arduino-cli (NOT the old files in web/firmware).
The NVS save area at 0x9000 must never be included in an image flashed at 0.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]
# Die Boot-Dateien stammen aus dem ORIGINAL, das auf dem Gerät funktioniert hat.
# Nur die Anwendungs-Firmware wird mit dem angepassten Quellcode neu kompiliert.
PARTS = (
    ('bootloader.bin', 0x0),
    ('partitions.bin', 0x8000),
    ('boot_app0.bin', 0xE000),
    ('app.bin', 0x10000),
)
ORIGINAL_DIR = ROOT / 'tools' / 'original_firmware'
EXPECTED_ORIGINAL_HASHES = {
    'bootloader.bin': '31b3c1be45dc5a76aa85c82540d6787b675e711eaf11021a5eea7e36f469c6de',
    'partitions.bin': 'ace02503447d0f470692e65fa76002f2d77a92dc81cd3813d8aa66718d716da9',
    'boot_app0.bin': 'f94c5d786a7a8fab06ac5d10e33bf37711a6697636dc037559ea19cc410a17f0',
}


HTML = '''<!doctype html>
<html lang="de"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>TamaPoke – Deutsche Pokémon-Namen</title>
<style>body{background:#111827;color:#f3f4f6;font:17px system-ui,sans-serif;max-width:700px;margin:55px auto;padding:0 20px;line-height:1.6}main{padding:24px;border:1px solid #4b5563;border-radius:15px}h1{margin:0 0 12px}strong{color:#a7f3d0}button{font:inherit;padding:12px 20px;border-radius:8px;background:#fcd34d;color:#111827;border:0;cursor:pointer}a{color:#93c5fd}small{color:#cbd5e1}</style>
</head><body><main><h1>TamaPoke – deutsche Pokémon-Namen</h1>
<p>Diese Version zeigt bei deutscher Sprache die <strong>deutschen Namen aller 1.025 Pokémon</strong>. Trainer Red, Sprites und Spiellogik bleiben wie in der mitgelieferten Quelle.</p>
<p>Verbinde dein Waveshare <strong>ESP32-S3-Touch-AMOLED-1.75</strong> per Daten-USB-C mit dem PC. Öffne diese Seite in <strong>Chrome oder Edge</strong> und klicke auf Installieren.</p>
<esp-web-install-button manifest="manifest.json"><button slot="activate">Firmware installieren</button>
<span slot="unsupported">Bitte Chrome oder Edge auf einem Desktop-PC verwenden.</span>
<span slot="not-allowed">Der Installer benötigt HTTPS (GitHub Pages) oder localhost.</span>
</esp-web-install-button>
<p><strong>Wichtig:</strong> Wenn du deinen Spielstand behalten möchtest, lasse „Erase device“ <strong>deaktiviert</strong>. Ein Löschen des gesamten Flash-Speichers entfernt Spielstand und eventuell SD-Daten. Der Installer installiert nur die Firmware – vorhandene Sprite-Pakete bleiben unverändert.</p>
<small>Nur für die oben genannte Hardware. Teste die Firmware nach dem Flashen zuerst auf dem Gerät. Kein offizielles TamaPoke-Release.</small>
</main><script type="module" src="https://unpkg.com/esp-web-tools@10/dist/web/install-button.js"></script></body></html>
'''


def sha256(path: Path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def check_image(data: bytes, name: str):
    if len(data) < 48 or data[0] != 0xE9:
        raise SystemExit(f'{name}: keine gültige ESP32-Image-Signatur')
    mode = data[2]
    chip = int.from_bytes(data[12:14], 'little')
    if mode != 2 or chip != 9:
        raise SystemExit(f'{name}: falscher Flash-Modus oder Chip: mode={mode}, chip={chip}')


def package(built: Path, destination: Path):
    if not built.is_dir():
        raise SystemExit(f'Build-Ordner nicht gefunden: {built}')
    destination.mkdir(parents=True, exist_ok=True)
    firmware_dir = destination / 'firmware'
    firmware_dir.mkdir(parents=True, exist_ok=True)

    sketches = list(ROOT.glob('*.ino'))
    if len(sketches) != 1:
        raise SystemExit(f'Genau eine .ino-Datei im Projekt erwartet, gefunden: {sketches}')
    sketch = sketches[0]
    compiled_app = built / (sketch.name + '.bin')
    compiled_partitions = built / (sketch.name + '.partitions.bin')
    if not compiled_app.is_file() or not compiled_partitions.is_file():
        raise SystemExit('Kompilierte App/Partitionstabelle nicht gefunden: ' + str(compiled_app))

    # Identische Partitionierung zur ORIGINAL-Firmware erzwingen.
    expected_partitions = ORIGINAL_DIR / 'partitions.bin'
    if sha256(compiled_partitions) != sha256(expected_partitions):
        raise SystemExit('STOP: Neue Partitionierung weicht von der Original-Firmware ab!')

    app_data = compiled_app.read_bytes()
    check_image(app_data, 'app.bin')
    if b'3.3.11' not in app_data:
        raise SystemExit('STOP: App wurde nicht mit Arduino-ESP32 3.3.11 gebaut')
    if len(app_data) > 0x300000:
        raise SystemExit('STOP: App ist größer als Original-App-Partition (3 MiB)')

    parts = []
    for final_name, offset in PARTS:
        if final_name == 'app.bin':
            data = app_data
        else:
            original = ORIGINAL_DIR / final_name
            data = original.read_bytes()
            digest = hashlib.sha256(data).hexdigest()
            if digest != EXPECTED_ORIGINAL_HASHES[final_name]:
                raise SystemExit(f'Original-Datei verändert: {final_name}')
            if final_name == 'bootloader.bin':
                check_image(data, final_name)
        dst = firmware_dir / final_name
        dst.write_bytes(data)
        digest = sha256(dst)[:16]
        parts.append({'path': f'firmware/{final_name}?v={digest}', 'offset': offset})
        print(f'{final_name}: offset 0x{offset:05X}; {len(data):,} bytes; sha256 {digest}')

    # Keine der vier Dateien darf den Save/NVS-Bereich überschreiben.
    for entry, (file_name, _) in zip(parts, PARTS):
        start = entry['offset']
        end = start + (firmware_dir / file_name).stat().st_size
        if start < 0xE000 and 0x9000 < end:
            raise SystemExit(f'UNSAFE: {file_name} würde NVS überschreiben')

    source = sketch.read_text(encoding='utf-8')
    firmware_version = re.search(r'#define FW_VERSION\s+"([^"]+)"', source)
    if not firmware_version:
        raise SystemExit('FW_VERSION in der Firmware nicht gefunden')
    version = firmware_version.group(1)
    if version != '3.28':
        raise SystemExit(f'Firmwareversion unerwartet: {version}')
    manifest = {
        'name': 'TamaPoke – deutsche Pokémon-Namen (Test, Core 3.3.11)',
        'version': version,
        'new_install_prompt_erase': True,
        'builds': [{'chipFamily': 'ESP32-S3', 'parts': parts}],
    }
    (destination / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    (destination / 'index.html').write_text(HTML.replace('TamaPoke – deutsche Pokémon-Namen', 'TamaPoke – deutsche Pokémon-Namen (Testbuild)').replace(
        '<small>Nur für die oben genannte Hardware.',
        '<small>Ungetestete Anpassung: Bitte Original-Installer zur Wiederherstellung bereithalten. Nur für die oben genannte Hardware.'
    ), encoding='utf-8')

    subprocess.run(['python3', str(ROOT / 'tools/check_installer.py'),
                    str(destination / 'manifest.json')], check=True)
    print('OK: altes Bootloader-/Partitions-Paket mit neuer App und Core 3.3.11')


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('--built-dir', type=Path, required=True, help='Fresh arduino-cli --output-dir')
    p.add_argument('--out', type=Path, default=Path('german-webflash'))
    args = p.parse_args()
    package(args.built_dir.resolve(), args.out.resolve())
