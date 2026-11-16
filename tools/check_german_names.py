#!/usr/bin/env python3
"""Check German names table against the committed National-Dex source list."""
import json
import re
import unicodedata
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
source=json.loads((ROOT/'tools'/'de_species_names.json').read_text(encoding='utf-8'))
code=(ROOT/'i18n.cpp').read_text(encoding='utf-8')
entries=re.findall(r'^\s+"([A-Z0-9: -]+)",\s+// #(\d+): (.+)$',code,re.M)
assert len(source)==1025, len(source)
assert len(entries)==1025, len(entries)
for i,(ascii_name, idx, original) in enumerate(entries,1):
    assert int(idx)==i,(i,idx)
    assert original==source[i-1],(i,original,source[i-1])
    assert len(ascii_name)<=16,(i,ascii_name)
    assert ascii_name==ascii_name.upper()
print('OK: all 1,025 German Pokémon names are aligned and display-safe.')
