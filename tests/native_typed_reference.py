"""Read-only original arithmetic harness; whole game is not executed.
rollAttack is intercepted after damage-channel assembly, before block/glancing/procs/HP/UI.
Critical result, resource callbacks and evaluated effect contributions are explicit fixture inputs.
"""
import ctypes as c, struct, sys, hashlib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from original import Original

# All addresses belong to the fingerprinted external ELF. Writable/executable
# pages are separate after setup. Never use MAP_FIXED to displace the host.
class Memory:

    def __init__(self):
        self.libc = c.CDLL(None, use_errno=True)
        self.pages = set()
        self.callbacks = []
        self.libc.mmap.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_int, c.c_int, c.c_long]
        self.libc.mmap.restype = c.c_void_p
        self.libc.mprotect.argtypes = [c.c_void_p, c.c_size_t, c.c_int]
        self.libc.munmap.argtypes = [c.c_void_p, c.c_size_t]

    def put(self, a, b):
        for p in range(a & ~4095, (a + len(b) - 1 & ~4095) + 4096, 4096):
            if p not in self.pages:
                v = self.libc.mmap(p, 4096, 3, 1048610, -1, 0)
                if v != p:
                    if v not in (None, c.c_void_p(-1).value):
                        self.libc.munmap(v, 4096)
                    raise OSError(c.get_errno(), 'MAP_FIXED_NOREPLACE failed; use PIE Python; mappings are never overwritten')
                self.pages.add(p)
            else:
                self.libc.mprotect(p, 4096, 3)
        c.memmove(a, b, len(b))

    def callback(self, a, t, fn):
        f = t(fn)
        self.callbacks.append(f)
        self.put(a, b'H\xb8' + struct.pack('<Q', c.cast(f, c.c_void_p).value) + b'\xff\xe0')

    def protect(self, writable=()):
        for p in self.pages:
            if self.libc.mprotect(p, 4096, 3 if p in writable else 5):
                raise OSError(c.get_errno(), 'mprotect')

    def close(self):
        for p in self.pages:
            self.libc.munmap(p, 4096)
        self.pages.clear()

class Native(Memory):
    """Original ordinary attack through channel assembly; critical=false.

    Object constructors, getEffectValue, hand/type queries are controlled fixture
    callbacks. Interception occurs at 0x844d98, after the original arithmetic,
    before glancing/blocking/procs and damage delivery. Allocation uses unchanged
    slices with an explicit ABI wrapper; no original game file is distributed.
    """

    def __init__(self, elf):
        super().__init__()
        try:
            self._initialize(elf)
        except BaseException:
            self.close()
            raise

    def _initialize(self, elf):
        self.original = Original(elf)
        o = self.original
        self.evidence = []
        names = ['CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)', 'CCharacter::maxDamage(CAttackDescription*, CCharacter*)', 'CCharacter::strength()', 'CCharacter::dexterity()', 'CCharacter::magic()', 'CCharacter::defense()', 'CCharacter::armorBonus()', 'CCharacter::AC()', 'CCharacter::minimumAC()', 'CCharacter::damageDefense(EDAMAGE_TYPES)', 'CCharacter::damageDefensePercent(EDAMAGE_TYPES)', 'CCharacter::modifyDamage(int, EDAMAGE_TYPES, int, float)', 'CEquipment::getDamageBonus(EDAMAGE_TYPES)', 'UTILITIES::randomIntegerBetweenVolatile(int, int)']
        for name in names:
            s = o.symbol(name)
            b = o.read(s.address, s.size)
            self.put(s.address, b)
            self.evidence.append({'name': name, 'address': hex(s.address), 'size': s.size, 'sha256': hashlib.sha256(b).hexdigest()})
        for a, n in [(16402424, 96), (16571712, 28), (16573744, 4)]:
            self.put(a, o.read(a, n))
        self.put(21940984, struct.pack('<Q', 1))
        self.put(22066312, bytes(4))
        self.actor = c.create_string_buffer(2048)
        self.target = c.create_string_buffer(2048)
        self.weapon = c.create_string_buffer(1280)
        self.inv = c.create_string_buffer(64)
        self.tinv = c.create_string_buffer(64)
        self.desc = c.create_string_buffer(128)
        self.indexes = (c.c_int * 7)(*range(7))
        self.values = (c.c_int * 7)()
        self.zeros = (c.c_int * 7)()
        self.effects = []
        self.target_effects = []
        self.flags = set()
        self.output = None
        self.critical = False
        self.left_hand = False
        for obj, off, val in [(self.actor, 1168, c.addressof(self.inv)), (self.target, 1168, c.addressof(self.tinv)), (self.actor, 912, c.addressof(self.desc)), (self.actor, 1176, c.addressof(self.weapon)), (self.weapon, 672, c.addressof(self.desc)), (self.weapon, 848, c.addressof(self.indexes)), (self.weapon, 856, c.addressof(self.indexes) + 28), (self.weapon, 872, c.addressof(self.values)), (self.weapon, 896, c.addressof(self.zeros))]:
            struct.pack_into('<Q', obj, off, val)
        struct.pack_into('<?', self.actor, 1184, True)
        struct.pack_into('<Q', self.weapon, 0x2a8, c.addressof(self.desc))
        struct.pack_into('<f', self.actor, 1824, 1.0)
        struct.pack_into('<f', self.desc, 112, 1.0)
        cf = c.CFUNCTYPE

        def effect(a, t, d):
            value = 0.0
            for typ, dt, v in self.target_effects if a == c.addressof(self.target) else self.effects:
                if t == typ and (d == 7 or dt == d):
                    value = struct.unpack('<f', struct.pack('<f', value + v))[0]
            return value
        self.callback(8468448, cf(c.c_float, c.c_void_p, c.c_uint, c.c_uint), effect)
        self.callback(8468240, cf(c.c_float, c.c_void_p, c.c_uint, c.c_uint, c.c_uint), lambda a, t, h, d: effect(a, t, d))
        self.callback(8348320, cf(c.c_bool, c.c_void_p, c.c_uint), lambda a, t: a == c.addressof(self.weapon) and t in self.flags)
        self.callback(9548896, cf(c.c_void_p, c.c_void_p, c.c_uint), lambda a, h: c.addressof(self.weapon) if a == c.addressof(self.inv) and h == int(self.left_hand) else 0)
        self.callback(8453152, cf(c.c_void_p, c.c_void_p), lambda a: c.addressof(self.weapon) if self.left_hand else 0)
        self.callback(8453200, cf(c.c_void_p, c.c_void_p), lambda a: 0 if self.left_hand else c.addressof(self.weapon))
        self.callback(8479648, cf(c.c_float, c.c_void_p), lambda a: 0.0)
        self.callback(8619024, cf(c.c_bool, c.c_void_p, c.c_void_p), lambda a, b: self.critical)
        self.callback(13034560, cf(c.c_int, c.c_void_p, c.c_uint), lambda a, b: 0)
        self.callback(8348128, cf(c.c_bool, c.c_void_p, c.c_uint), lambda a, b: False)
        libm = c.CDLL('libm.so.6')
        self.put(5584504, b'H\xb8' + struct.pack('<Q', c.cast(libm.ceilf, c.c_void_p).value) + b'\xff\xe0')

        def capture(p, n, maximum, rolled, applied):
            self.output = ([struct.unpack('<ii', c.string_at(p + 8 * i, 8)) for i in range(n)], maximum, rolled, applied)
        cap = cf(None, c.c_void_p, c.c_uint, c.c_int, c.c_int, c.c_int)(capture)
        self.callbacks.append(cap)
        # Capture stack channel list, total maximum/roll/applied; then original epilogue.
        patch = bytes.fromhex('48 8d bc 24 b0 00 00 00 8b b4 24 80 00 00 00 8b 94 24 88 00 00 00 8b 8c 24 90 00 00 00 44 8b 44 24 7c 48 b8') + struct.pack('<Q', c.cast(cap, c.c_void_p).value) + bytes.fromhex('ff d0 48 b8') + struct.pack('<Q', 8667344) + bytes.fromhex('ff e0')
        self.put(8670616, patch)

        def jump(a):
            return b'I\xbb' + struct.pack('<Q', a) + b'A\xff\xe3'
        for a, end in [(8917544, 8917560), (8917633, 8917659), (8918028, 8918058), (8918720, 8918733)]:
            raw = o.read(a, end - a)
            self.put(a, raw)
            self.evidence.append({'name': 'calculateCombatStats allocation slice', 'address': hex(a), 'size': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()})
        # Allocation ABI wrapper: RBX=equipment, stack+0x28=float graph/100.
        wrapper = 536870912
        exit = wrapper + 256
        self.put(wrapper, bytes.fromhex('53 48 83 ec 30 48 89 fb 89 74 24 20 89 54 24 24') + jump(8917544))
        self.put(exit, bytes.fromhex('48 83 c4 30 5b c3'))
        self.put(8917560, bytes.fromhex('f3 0f 11 44 24 28 8b 44 24 20 83 7c 24 24 00 74 0d') + jump(8918028) + jump(8917633))
        self.put(8917659, b'\xe9' + struct.pack('<i', wrapper + 288 - (8917659 + 5)))
        self.put(wrapper + 288, bytes.fromhex('89 d0') + jump(exit))
        self.put(8917664, bytes.fromhex('31 c0') + jump(exit))
        self.put(8918058, jump(exit))
        self.protect((21940984 & ~4095,))
        self.allocation = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_int, c.c_int)(wrapper)
        self.roll = c.CFUNCTYPE(c.c_bool, c.c_void_p, c.c_void_p, c.c_void_p, c.c_void_p, c.c_uint, c.c_float, c.c_float, c.c_uint)(8666832)
        self.ac = c.CFUNCTYPE(c.c_int, c.c_void_p)(0x814670)
        self.defense = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_int)(8476944)
        self.magic = c.CFUNCTYPE(c.c_int, c.c_void_p)(8471744)
        self.defense_percent = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_int)(8476864)
        self.modify = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_int, c.c_int, c.c_int, c.c_float)(8616960)

    def allocate(self, graph, percent, physical):
        struct.pack_into('<i', self.weapon, 820, graph)
        return self.allocation(c.addressof(self.weapon), percent, int(physical))

    def run(self, base, bonus, strength=0, dexterity=0, magic=0, effects=(), armor=0, defense=0, elemental=None, target_effects=(), seed=1, flags=(), *, damage_fraction=1.0, soak_multiplier=1.0, use_dps=False, dps_speed=1.0, left_hand=False):
        self.left_hand = left_hand
        self.flags = set(flags)
        self.effects = list(effects)
        self.target_effects = list(target_effects)
        struct.pack_into('<i', self.desc, 36, base)
        # original-code: rollAttack reads attackDesc+0x70 at 0x844157.
        # The existing oracle already maps the 0.7333333 constant at 0xfce530.
        # These are controlled roll inputs, not recovered equipment/skill wiring.
        struct.pack_into('<f', self.desc, 0x70, dps_speed)
        for off, val in [(1068, strength), (1064, dexterity), (1076, magic)]:
            struct.pack_into('<i', self.actor, off, val)
        struct.pack_into('<i', self.target, 1060, armor)
        struct.pack_into('<i', self.target, 1072, defense)
        for i in range(7):
            self.values[i] = bonus[i]
            struct.pack_into('<i', self.target, 1568 + 4 * i, (elemental or [0] * 7)[i])
        c.c_uint64.from_address(21940984).value = seed
        self.output = None
        self.roll(c.addressof(self.actor), 0, c.addressof(self.target), c.addressof(self.weapon),
                  0x400 if use_dps else 0, damage_fraction, soak_multiplier, 7)
        return (self.output, c.c_uint64.from_address(21940984).value)
