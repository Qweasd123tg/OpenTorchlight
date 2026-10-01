# Volatile RNG: исправление 44 -> 52 fraction bits

2026-10-02. Ошибка найдена при продолжении menu Group seed/stream разбора.
Вход, source bytes hash и конкретные результаты:
[volatile-random-comparison.json](volatile-random-comparison.json).
[ASM](disassembly/volatile-random-fraction.asm) содержит полное151-byte тело
pinned UTILITIES::randomBetweenVolatile @0xc92b50. Исполнялись только copied
машинные функции в частном reference image; ELF оставался read-only.
Полный оригинальный game process и GUI/device playback не запускались.

## Контракт

`original-code`: ucomiss/jp/je @0xc92b50..0xc92b55 направляет NaN в random
ветвь, равные bounds возвращают low без расхода state. Range вычислен subss,
затем преобразован в double. g_RandVolatile uint64@0x14ecaf8 использует два
шага multiply-with-carry: low32*0x29777b41 + high32; оба unsigned64 wrap.
Writeback второго состояния на0xc92b9c. Mantissa составлена из первого
state<<32 и low32 второго. **movabs 0xfffffffffffff @0xc92ba8** оставляет
52 младших бита; OR 0x3ff0000000000000, reinterpret double и subtract1.0
создают fraction в[0,1). Double range*fraction округляется вfloat, затем
addss low; signed zero, reversed bounds, NaN/infinities не подменяются clamp.

В порте и старом numpy emulator была маска0xFFFFFFFFFFF (44 bits). Fraction
ограничивалась[0,1/256), хотя генератор state расходовал правильные два шага.
Поэтому совпадение states и одинаковая ошибка обоих transcription tools
не доказывали результат. При state1/bounds[-2.5,7.25] прежний port float bits
0xc01e4900, оригинал0x4003c700; after-state в обоих0x06b77d3ea3c58681.
Новый oracle сначала воспроизвёл это расхождение на старом коде.

## Перенос, production ownership и сравнение

Исправлена только fraction mask в VolatileRandom::between. Seed/state algorithm,
число шагов и equal/NaN dispatch не менялись. Numpy reference mask исправлена;
восемь старых unit literals заменены значениями, снятыми непосредственно с
оригинальной функции. Они больше не происходят из повторяющего ошибку emulator.

`integration`: UiSoundPlayer::play -> channel_gain(volume,variation, local
VolatileRandom) -> UiSoundVoice.gain -> PCM mix/worker. Этот существующий caller
действительно потребляет исправленный результат. Исходная additive/capped gain
формула min(volume+random(0,variation),1) подтверждена
[dropdown-animation-lifecycle.md](dropdown-animation-lifecycle.md),
CSound::play clamp minss@0xa6cd4f. MissileMotion module принимает RNG callback;
его полный production RNG/jitter путь этим исправлением не подключается.

`original_comparison`: tests/compare_original_random.py проверяет SHA/entry/size,
переиспользует existing MAP_FIXED_NOREPLACE private image, rodata1.0 и RW state
page. Изолированно вызывает реальный original machine code и C++ shared probe.
28 000 сравнений float bits/state:7 входных states x2000 вызовов, включая
zero/32-bit/64-bit continuations и equal/reversed/signed-zero/NaN/infinite/
случайные конечные bounds. Ещё4000 сравнений идут через **настоящий**
UiSoundPlayer::channel_gain; expected random получен original ASM, затем source
float32 additive/capped формула. Existing normal RNG/weighted/intersection
gate64 004 тоже проходит. Этот oracle отличается от numpy transcription.

Desktop, shared Application probe, randomizer comparison, missile motion и
UI sound CPU targets собраны. CPU/resource sound и missile-motion gates прошли;
Gate **4/4**: original_randomizer_comparison, missile_motion, ui_sound_contract,
original_ui_sound_contract. Registry sync **237 bounded /165 cited**.
Reference gate включён в текущем ignored build через TORCHLIGHT_ORIGINAL.
Whole completion остаётся partial: port-owned локальный stream не заменяет
original process-global g_RandVolatile, его initializer/GetTickCount/других
callers/thread/FMOD lifecycle. Menu dungeon seed offsets, compiled Group order,
общая generation sequence и frame/audio-device parity пока не заявляются.
