#!/usr/bin/env python3
"""Authored malformed library input; contains no original game resources."""
import sys
import zipfile
from pathlib import Path

path = Path(sys.argv[1])
path.parent.mkdir(parents=True, exist_ok=True)
with zipfile.ZipFile(path, "w") as archive:
    archive.writestr("media/UI/GuiLookSkin.scheme", "<GUIScheme")
    archive.writestr("media/UI/mainmenuframe.layout", "<GUILayout/>")
