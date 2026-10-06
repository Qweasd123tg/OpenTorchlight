extern "C" unsigned mul7(unsigned x) { return x * 7u; }
extern "C" unsigned mul7_shift(unsigned x) { return (x << 3u) - x; }
extern "C" unsigned mul7_split(unsigned x) { return (x << 2u) + (x << 1u) + x; }
extern "C" unsigned mul8_bad(unsigned x) { return (x << 3u); }
