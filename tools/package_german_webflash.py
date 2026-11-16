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
PARTS = (
    ('TamaPoke-DE.ino.bootloader.bin', 'bootloader.bin', 0x0),
    ('TamaPoke-DE.ino.partitions.bin', 'partitions.bin', 0x8000),
    ('boot_app0.bin', 'boot_app0.bin', 0xE000),
    ('TamaPoke-DE.ino.bin', 'app.bin', 0x10000),
)

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


def package(built: Path, destination: Path):
    if not built.is_dir():
        raise SystemExit(f'Build-Ordner nicht gefunden: {built}')
    destination.mkdir(parents=True, exist_ok=True)
    firmware_dir = destination / 'firmware'
    firmware_dir.mkdir(parents=True, exist_ok=True)
    parts = []
    for source_name, final_name, offset in PARTS:
        src = built / source_name
        if not src.is_file():
            raise SystemExit(f'Erwartete *neu kompilierte* Datei fehlt: {src}')
        dst = firmware_dir / final_name
        shutil.copyfile(src, dst)
        size = dst.stat().st_size
        if size == 0:
            raise SystemExit(f'Leere Firmware-Datei: {dst}')
        digest = hashlib.sha256(dst.read_bytes()).hexdigest()[:16]
        parts.append({'path': f'firmware/{final_name}?v={digest}', 'offset': offset})
        print(f'{final_name}: 0x{offset:05X}, {size:,} bytes, sha256 {digest}')

    # Prevent any part, including a carelessly merged image at 0x0, from
    # touching the NVS partition containing the save game.
    nvs_start, nvs_end = 0x9000, 0xE000
    for entry, (_, file_name, _) in zip(parts, PARTS):
        start = entry['offset']
        end = start + (firmware_dir / file_name).stat().st_size
        if start < nvs_end and nvs_start < end:
            raise SystemExit(f'UNSAFE: {file_name} 0x{start:x}..0x{end:x} overwrites NVS')

    source = (ROOT / 'TamaPoke-DE.ino').read_text(encoding='utf-8')
    firmware_version = re.search(r'#define FW_VERSION\s+"([^"]+)"', source)
    if not firmware_version:
        raise SystemExit('FW_VERSION in der Firmware nicht gefunden')
    version = firmware_version.group(1)
    manifest = {
        'name': 'TamaPoke – deutsche Pokémon-Namen',
        'version': version,
        # Counterintuitive but crucial: true *asks* about erase and defaults to NO.
        'new_install_prompt_erase': True,
        'builds': [{'chipFamily': 'ESP32-S3', 'parts': parts}],
    }
    (destination / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
    (destination / 'index.html').write_text(HTML, encoding='utf-8')

    # Execute upstream safety check against the built partition table/manifest.
    subprocess.run(['python3', str(ROOT / 'tools/check_installer.py'),
                    str(destination / 'manifest.json')], check=True)
    print(f'OK: browser installer in {destination}, source FW_VERSION={version}')


if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('--built-dir', type=Path, required=True, help='Fresh arduino-cli --output-dir')
    p.add_argument('--out', type=Path, default=Path('german-webflash'))
    args = p.parse_args()
    package(args.built_dir.resolve(), args.out.resolve())
