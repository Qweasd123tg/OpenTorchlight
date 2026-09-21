# Original inline text markup

## Evidence

The pinned `lib64/libCEGUIBase.so.1` is SHA-256
`57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
The pinned game ELF is SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

`CGameUI` registers the literal tags `|c` and `|u` for every shipped Serif
font in `research/ui-deep-map/09-original-font-customisation.md`:
`game_ui.c` 8710-8749 for Serif, then 8756-8878 for SerifBig, SerifHuge,
and SerifSmall. The registration flag is written at 8750 and analogously
after the other font pairs.

In the library, `CEGUI::Font::getTextExtent` is at absolute ELF offset
`0xd1dd0` and `CEGUI::Font::drawTextLine` at `0xd23d0`. Both convert the
string to wide characters, recognize the configured tags with `wcsncmp`, and
skip recognized tags in the glyph loop. `|c` requires eight following
characters and consumes the tag plus payload (ten codepoints total); `|u`
consumes two. Their payloads have zero advance.

`drawTextLine` at `0xd2824` recognizes `|c`; the payload is extracted
as hexadecimal by `basic_istream::_M_extract<unsigned int>` at `0xd2d5f`,
then passed to `CEGUI::colour(unsigned int)` at `0xd2d73` and applied with
`ColourRect::setColours` at `0xd2d94`. `|u` is recognized at `0xd2994` and
restores the saved input ColourRect (`0xd29ab` onward). The implementation
does not validate all eight characters: a malformed full payload is consumed
and stream-style prefix parsing is retained; an incomplete payload is literal.

Measurement is independent of the color value. `getWrappedTextExtent`
(`0xd3970`) calls `getNextWord` and then `getTextExtent` (`0xd3a92`,
`0xd3b9d`, `0xd3cad`). `getFormattedLineCount` (`0xd3ec0`) follows the same
word/ex-tent path. Each eventual `drawTextLine` starts from its supplied
ColourRect, so color does not persist across an explicit newline or a
wrapped physical line unless the markup is repeated in that line.

## Port contract

`ui_text_lines(..., inline_markup=true)` implements only this bounded
contract. Tags are removed before wrapping and measurement. `UiTextLine::colors`
has one entry per output codepoint: `nullopt` means the caller's original
ColourRect; a value is the original 32-bit `AARRGGBB` value. The parser resets
to `nullopt` on `|u` and at every physical line boundary. The default argument
is false for existing callers.

The allowlist helper `ui_font_uses_inline_colours` returns true only for
`Serif`, `SerifBig`, `SerifHuge`, and `SerifSmall`, matching the four font
customization sequences in the original ELF.

The GLES renderer passes this allowlist result to `ui_text_lines`. For an
inline-coloured glyph, the parsed AARRGGBB replaces the source RGB (matching
`ColourRect::setColours` at `0xd2d94`); only its alpha is multiplied by the
source/effective alpha. Unmarked glyphs retain the original look/base RGB and
per-corner skin colour. `|u` returns to that source ColourRect. No GL or frame
behavior is inferred beyond this CPU-side batch contract.
