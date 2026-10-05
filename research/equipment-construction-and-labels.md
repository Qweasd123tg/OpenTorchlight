# Equipment construction, speed labels and rim lighting

Three additional original methods are normalized instruction MATCH with the
original GCC toolchain:

- CEquipment(CResourceManager*), 0x86fd10, 786 bytes (C1/C2 aliases at one entry)
- getAttackSpeedString(EWeaponSpeed), 0x86f790, 935 bytes
- setRimlight(std::wstring), 0x87e2c0, 888 bytes

The constructor preserves the original initialized and uninitialized members.
In particular, it does not zero the whole object or invent defaults for the
remaining opaque fields. Its socket and missile-reference lists grow by one;
the inherited value at 0x194 is 0.375f. The provisional POD vector element types
at 0x398/0x3b0 remain explicitly documented in the destructor report.

Speed labels use five separately lazy-cached translations: Slowest/Slow/
Average/Fast/Fastest Attack Speed. An empty translation remains eligible for a
later retry. The default result is EMPTY_WSTRING and out-of-range enum values
leave it unchanged.

Equipment rim lighting requires a data group before visiting either model.
For each present model it sets rim lighting, then reads TEXTURE_OVERRIDE and
applies a nonempty override. The second model is checked after the first
model's work, preserving collaborator changes and original call order.

MATCH is the acceptance evidence for these methods; it is not a claim that all
rendering/model services or every other Equipment method are recovered.
