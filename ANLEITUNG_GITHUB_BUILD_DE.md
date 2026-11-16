# TamaPoke – deutsche Pokémon-Namen, Build und Browserinstallation

## Was diese Dateien enthalten

- Die Pokémon-Namen-Tabelle für alle 1.025 Pokémon; deutsche Ausgabe nur bei UI-Sprache **Deutsch**.
- Trainername **Red**, Avatar-Auswahl, Pokémon-IDs und Sprites bleiben unverändert.
- Eine bereits im Original vorhandene zweite, ältere Kampfdatei `z_battle.cpp` wurde nach `tools/legacy/z_battle.cpp.saved.txt` verschoben, damit der Arduino-Build nicht zwei Implementierungen derselben Funktionen verlinkt. Die aktive `battle.cpp` bleibt unverändert, abgesehen von den deutschen Namensaufrufen.
- `.github/workflows/build-german-firmware.yml` lässt GitHub eine **neue ESP32-S3-Firmware kompilieren**.
- `tools/package_german_webflash.py` erstellt daraus einen **eigenen sicheren Web-Installer**. Er verwendet vier getrennte Binärdateien (Offsets `0x0`, `0x8000`, `0xE000`, `0x10000`) und prüft, dass der Spielstandbereich NVS nicht überschrieben wird.

**Achtung:** Dies ist ein Quellcode-Archiv, **noch keine kompilierte `.bin`**. Die fertigen Binärdateien entstehen erst, wenn GitHub Actions erfolgreich durchläuft.

## Einmalige Einrichtung auf GitHub (am PC)

1. Ein kostenloses **öffentliches** GitHub-Repository erstellen, z. B. `TamaPoke-DE`. Repository nicht mit zusätzlichen Dateien initialisieren.
2. Dieses ZIP **entpacken**. Mit **GitHub Desktop** den entpackten Projektordner als Repository hinzufügen, das neue GitHub-Repository als `origin` eintragen und hochladen. Alternativ in einem lokalen Terminal im Projektordner:

   ```bash
   git init
   git add .
   git commit -m "Deutsche Pokemon-Namen mit Web-Installer"
   git branch -M main
   git remote add origin https://github.com/DEIN-BENUTZERNAME/TamaPoke-DE.git
   git push -u origin main
   ```

3. Auf GitHub im neuen Repository **Settings → Pages → Build and deployment → Source: GitHub Actions** wählen.
4. Unter **Actions** den Workflow **„Deutsche Pokemon-Namen – Firmware bauen und Web-Installer“** öffnen, **Run workflow** drücken und das Ergebnis abwarten. Das ist der eigentliche Kompiliervorgang, der auf GitHub-Rechnern läuft.
5. Nach erfolgreichem Abschluss unter **Actions → Workflow-Lauf** das Artefakt `TamaPoke-DE-Web-Installer` herunterladen. Der Installer wird zusätzlich unter
   `https://DEIN-BENUTZERNAME.github.io/TamaPoke-DE/` veröffentlicht.

## Firmware im Browser aufspielen

1. ESP32-S3-Touch-AMOLED-1.75 per **Daten-USB-C** am PC anschließen.
2. Die eben veröffentlichte GitHub-Pages-Adresse mit **Chrome oder Edge** öffnen.
3. **Firmware installieren** wählen und den USB-Port bestätigen.
4. **„Erase device“ nicht anklicken**, wenn du den bisherigen Spielstand behalten willst. Auch bei einem neuen Spielstand ist das nicht erforderlich.
5. Nach dem Neustart bei der Sprache Deutsch auswählen und prüfen, dass Pokémon Nr. 1 **BISASAM** statt **BULBASAUR** heißt.

Diese Seite ist **nur zum Flashen der Firmware** da. Die Sprite-Pakete werden nicht angefasst; lasse die bereits auf der SD-Karte installierten Pakete dort. Bei einem komplett leeren Gerät musst du die Sprite-Pakete anschließend über den Original-Webinstaller übertragen – dabei darfst du **nicht** erneut dessen Standard-Firmware installieren.

## Wichtige Versionsauffälligkeit

Das Original-ZIP war intern widersprüchlich: `TamaPoke.ino` meldete `FW_VERSION "1.01"`, aber die README bezeichnet die Firmware als **v3.28** und die mitgelieferte `web/firmware/app.bin` enthält ebenfalls **3.28**. Für diesen Build ist die Versionskennung in `TamaPoke.ino` deshalb auf **3.28** berichtigt. Das ändert keine Spiellogik, verhindert aber eine falsche Versionsanzeige und einen vermeidbaren LAN-Versionskonflikt. Ein echter Hardwaretest ist weiterhin nötig.

## Was wurde getestet?

Die Namenszuordnung (1.025 Einträge), die C++-Syntax der modifizierten Module und die Browser-Save-Tests. **Ein echter ESP32-S3-Build und Hardwaretest wurden hier noch nicht durchgeführt**; die GitHub-Action muss dafür zuerst erfolgreich sein. Wenn der Build scheitert, ist das Artefakt nicht flashbereit und die Fehlermeldung unter Actions muss geprüft werden.
