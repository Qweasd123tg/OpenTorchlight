# Reading GCC 4.4 x86-64 code of Torchlight (C++98, -O2)

The ASM is the truth; the Ghidra draft is a hint. Inlined library code shows up in both
as long low-level sequences. Write the short C++ that produced them, not the expansion.

## Calls and arguments
- System V: this/arg1 rdi, then rsi, rdx, rcx, r8, r9; floats in xmm0-xmm7; return in
  rax or xmm0 (a float return means the callee is `float`, a set al means `bool`).
- Ghidra drops the arguments of library calls it has no prototype for
  (`CEGUI::Combobox::getItemCount()`, `Ogre::Node::setPosition()`): take them from the
  registers loaded just before the call in the ASM.
- A function returning a class by value (std::wstring, CEGUI::String, Ogre::Vector3 >16
  bytes) gets a hidden first argument (the result slot) in rdi; `this` moves to rsi.
- `(**(code **)(*(long *)p + 0x18))(p, a)` is a virtual call: slot 0x18 / 8 = 3 of the
  static type's vtable. Use the method declared in that slot (class headers list virtuals
  in slot order; a virtual destructor takes slots 0 and 1). `(**(code **)(*p + 8))(p)`
  on an object is usually `delete p`.
- `extraout_XMM0_Da`, `CONCAT71(extraout_var, x)`: only the return value of the preceding
  call; never write Ghidra helpers (CONCAT*, SUB*, ZEXT*, SEXT*, `code`, `undefined*`).

## std::wstring / std::string (copy-on-write, one pointer `_M_p`)
- Header before the characters: length at p - 0x18 bytes, capacity p - 0x10, refcount
  (int) p - 8. For wchar_t* arithmetic Ghidra writes `p - 6` (length) and `p - 2`
  (refcount): `*(long *)(s._M_p - 6) == 0` is `s.empty()`, the value is `s.length()`.
- `if (rep != &_S_empty_rep_storage) { LOCK(); old = refcount--; UNLOCK();
  if (old < 1) _Rep::_M_destroy(rep); }` is the destructor of a string going out of scope
  (or being overwritten): write nothing.
- `refcount < 0 ? _M_clone : ++refcount` (`_M_grab`, `_M_refcopy`) is a copy:
  `std::wstring b = a;`, returning a string by value, passing it by value.
- `basic_string(local, L"lit", &alloc)` on a stack slot then passing the slot is a
  temporary: `f(L"lit")` when the parameter is `const std::wstring&`.
- `wmemcmp(a, b, min(len_a, len_b))`, then `len_a - len_b` clamped to int, is
  `a.compare(b)`; inside a tree walk it is the `<` of a map/set keyed by strings.
  Equal lengths and `wmemcmp(...) == 0` is `a == b`.
- `_M_leak_hard` / `_M_mutate` come from non-const `s[i]`, `begin()`, `replace`, `insert`.

## std::map / std::set (red-black tree, sizeof 48)
- Map object: header node at +0x08 (root at +0x10, leftmost +0x18, rightmost +0x20),
  size at +0x28. Node: parent +0x08, left +0x10, right +0x18, value (key, then mapped
  value) at +0x20.
- Walk from the root keeping the last node whose key is not less than the key, then one
  more compare: `m.find(key)` (`it == m.end()` is the compare with the header) or
  `m.lower_bound(key)`. Find followed by inserting a default value on a miss is `m[key]`.
- `_Rb_tree_increment(node)` is `++it`; `_Rb_tree_rebalance_for_erase` is `m.erase(it)`.

## std::vector and std::list
- vector: begin +0, end +8, end of storage +0x10. `if (end == eos) _M_insert_aux(v, end,
  &x); else { if (end) *end = x; end++; }` is `v.push_back(x)`. `(end - begin) >> 3` is
  `v.size()` of 8-byte elements.
- list: node next +0, prev +8, value +0x10. `_List_node_base::hook` is `push_back` /
  `insert`, `unhook` + delete is `erase`.

## Engine containers and memory
- `TArrayList<T>`: data +0, count +8, capacity +0x0c, grow-by +0x10 (24 bytes). Use its
  methods (`add`, `removeAt`, `remove`, `find`, `clear`, `deleteAll`, `size`, `[]`);
  `index >= capacity ? data[0] : data[index]` is `list[index]`; a grow-and-copy loop is
  `add`.
- `Ogre::NedPoolingImpl::allocBytes(size, 0, 0, 0)` followed by a constructor call on the
  result is `new T(...)` for a class derived from an Ogre allocated object (CRunicCore and
  everything below it, TArrayList); `deallocBytes` after the destructor is `delete p`.
  `operator_new` + constructor is plain `new T(...)`; the landing pad that frees the memory
  when the constructor throws is generated, write nothing for it.
- `__cxa_guard_acquire(&g) ... __cxa_guard_release(&g); __cxa_atexit(dtor, &obj, ...)` is
  a function-local `static T obj(...)` (names like `Func(args)::g_Name` in the draft).
- `getSingleton()`/`getSinglton()` static methods return the instance; keep the spelling of
  the symbol (`CStringTranslate::getSinglton` is the original name).

## CEGUI
- `CEGUI::String` is 0xb0 bytes: length +0, reserve +8, utf8 buffer +0x10, its data length
  +0x18 and size +0x20, quick buffer of 32 utf32 at +0x28, buffer pointer +0xa8. A stack
  slot of 176 bytes passed to `CEGUI::String::String(slot, "text")` and destroyed later is
  a temporary `CEGUI::String("text")`; the `d_encodedbufflen > 0 -> delete[]` and
  `d_reserve > 32 -> delete[]` tail is its destructor: write nothing.
- `CEGUI::WindowManager::getSingleton().getWindow(name)` and `setText`, `setVisible`,
  `subscribeEvent(name, CEGUI::Event::Subscriber(&Class::handler, this))` are the usual
  UI calls; an Event::Subscriber built on the stack around a `FunctorCopySlot` /
  `MemberFunctionSlot` allocation is that one expression.

## Control flow
- `try { // try from ... CatchHandler` comments and `_Unwind_Resume` blocks are cleanups
  of locals during exceptions: write nothing for them.
- Ghidra loops with `goto` and duplicated tails usually come from `for`/`while` with
  `break`/`continue`, `&&`/`||` chains or a `switch` (jump table through `switchD_`).
- Floats compared with `NAN(x) ||` wrappers are ordinary `<`, `<=`, `==` comparisons.
