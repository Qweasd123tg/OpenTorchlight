# Vendored CEGUI Mk-2 0.6.2

Source: official CEGUI `v0-6-2` tag, commit
`3ed5c719c3bb27b877b192e034ef2c0b05ea722c`.
The source archive used for this import has SHA-256
`fe7509fce6a16fc307032254e08cff70dce2f7eb5233ee57bc24bc27b733cc84`.
The import includes `src`, `include`, `WindowRendererSets/Falagard`,
`XMLParserModules/TinyXMLParser`, `COPYING`, and `AUTHORS`. Original source
notices are retained. The bundled `ceguitinyxml` files retain Lee Thomason's
licence and attribution in their headers. This file marks the altered version.

Local source changes:

1. `XMLParserModules/TinyXMLParser/CEGUITinyXMLParser.cpp`: compare the first
   byte of `Value()` with NUL instead of comparing a pointer with a character,
   which GCC 16 rejects. Disable TinyXML whitespace condensation and apply
   XML 1.0 raw-input line-end normalisation (CRLF or lone CR to LF) before
   parsing. This matches the original game's Expat text delivery for
   `CreditsB` property bodies while retaining explicit `&#13;` references.
   The shipped `GUILayout_xmlHandler::text @0xe3560` appends each delivered
   fragment; see `research/mainmenu-controller-painter.md`.
2. `src/CEGUIFont.cpp`: recognize Torchlight's `|cAARRGGBB` and `|u` tags on
   `Serif`, `SerifBig`, `SerifHuge`, and `SerifSmall`, including measurement,
   hit position, normal drawing, and justified drawing. A complete tag has no
   advance; `|c` uses hex stream prefix parsing and modulates its alpha with
   the supplied colour; `|u` restores that colour. Incomplete `|c` remains
   literal. Each drawn physical line begins with its supplied colour. The
   game ELF registration and shipped library behavior are recorded with
   addresses in `research/ui-inline-text.md`.

Build integration is in `cmake/CEGUI062.cmake`. It defines static
`CEGUI062::Base` and `CEGUI062::Falagard` targets; Base includes bundled
TinyXML, FreeType, PCRE, and `dl`. The original renderer modules, Lua, and
sample programs are outside this import. The upstream FreeType source already
uses `FT_LOAD_FORCE_AUTOHINT` for preload and rendering, matching the shipped
library's `updateFont` load flag `0x20` at `0xe0997` recorded in
`research/ui-font-autohint.md`.
