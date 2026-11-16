# Deutsche Pokémon-Namen für TamaPokeLAN v3.28

Die originale `TamaPoke.ino`-Firmware verwendet englische Artnamen in `DEX_TBL`.
Diese Anpassung ergänzt **1.025 deutsche Pokémon-Namen** in `i18n.cpp` und
zeigt diese über `pokemonName(dex)` an, **wenn die Sprache im Spiel DE ist**.
In anderen Sprachen bleiben die bisherigen englischen Artnamen erhalten.
Die Nummern, Werte, Entwicklungen, Sprites, Trainer-Avatare (einschließlich
**RED**), Spitznamen und Spiellogik werden nicht verändert.

## Zeichensatz

Der Standard-Bitmap-Font dieser Firmware kann keine Umlaute oder Akzente.
Darum werden die Namen in der Anzeige im ASCII-Fallback geschrieben, z. B.:

- BULBASAUR → BISASAM
- CHARMANDER → GLUMANDA
- SQUIRTLE → SCHIGGY
- BRÜLLSCHWEIF → BRUELLSCHWEIF
- NIDORAN♀ → NIDORAN W und NIDORAN♂ → NIDORAN M

## Installation

Dieses ZIP enthält **Quellcode, keine fertig kompilierte Flash-Datei**. Der GitHub-Actions-Workflow `.github/workflows/build-german-firmware.yml` kann die Dateien erzeugen.
Zum Hochladen muss die Firmware mit der bisherigen ESP32-S3-/Arduino-
Konfiguration aus dem Originalprojekt neu kompiliert werden. Der öffentliche
Web-Installer der Originalversion würde die Anpassung wieder überschreiben.
Bitte bei der Installation die vorhandene Partitionierung und SD-Daten
entsprechend der Originalanleitung beibehalten.

## Quellen / Rechte

Basis: [TamaPokeLAN](https://github.com/reallyjustsomeguy/TamaPokeLANExp),
Quellcode v3.28 vom Nutzer bereitgestellt. Namensliste nach National-Dex-
Nummern: [sindresorhus/pokemon/data/de.json](https://github.com/sindresorhus/pokemon/blob/main/data/de.json).
Pokémon-Namen sind Marken / geistiges Eigentum von Nintendo, Game Freak
und The Pokémon Company, nur für persönliche nichtkommerzielle Nutzung.
Die Lizenz des Originalprojekts (`LICENSE`) bleibt enthalten.

## Build-Hinweise

Die Originaldatei `z_battle.cpp` duplizierte die bereits aktive `battle.cpp` und würde beim Arduino-Kompilieren zu mehrfach definierten Symbolen führen. Die ältere Kopie liegt nun außerhalb des Sketch-Ordners unter `tools/legacy/z_battle.cpp.saved.txt`.

Im bereitgestellten Originalquellcode stand `FW_VERSION` **1.01**, während die README **v3.28** nennt und die mitgelieferte vorkompilierte `app.bin` auch **3.28** enthält. Daher wurde die Versionskennung für unseren Build passend auf **3.28** gesetzt. Ein Hardwaretest bleibt erforderlich.
