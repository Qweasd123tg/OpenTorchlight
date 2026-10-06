#include <CEGUI.h>
#include <new>
extern "C" {
void ctor_default(void *p) { new (p) CEGUI::String(); }
void ctor_empty_chars(void *p) { new (p) CEGUI::String(""); }
void ctor_zero_count(void *p) { new (p) CEGUI::String((CEGUI::String::size_type)0, (CEGUI::utf32)0); }
void ctor_empty_span(void *p) { new (p) CEGUI::String("", (CEGUI::String::size_type)0); }
unsigned long sdk_string_size() { return sizeof(CEGUI::String); }
long width_probe(long x) { return x >> 40; }
}
