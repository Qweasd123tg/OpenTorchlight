
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000880bb0 <CEquipment::calculateCombatStats(bool)+0x260>:
  880bb0:	a4                   	movsb  (%rsi),(%rdi)
  880bb1:	24 f0                	and    $0xf0,%al
  880bb3:	01 00                	add    %eax,(%rax)
  880bb5:	00 48 8d             	add    %cl,-0x73(%rax)
  880bb8:	94                   	xchg   %eax,%esp
  880bb9:	24 b8                	and    $0xb8,%al
  880bbb:	02 00                	add    (%rax),%al
  880bbd:	00 be d0 e9 fa 00    	add    %bh,0xfae9d0(%rsi)
  880bc3:	4c 89 e7             	mov    %r12,%rdi
  880bc6:	e8 8d 52 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880bcb:	48 8b bb b0 01 00 00 	mov    0x1b0(%rbx),%rdi
  880bd2:	ba 64 00 00 00       	mov    $0x64,%edx
  880bd7:	4c 89 e6             	mov    %r12,%rsi
  880bda:	e8 31 e7 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880bdf:	48 8b bc 24 f0 01 00 	mov    0x1f0(%rsp),%rdi
  880be6:	00 
  880be7:	89 44 24 3c          	mov    %eax,0x3c(%rsp)
  880beb:	48 83 ef 18          	sub    $0x18,%rdi
  880bef:	48 39 fd             	cmp    %rdi,%rbp
  880bf2:	0f 85 a1 13 00 00    	jne    881f99 <CEquipment::calculateCombatStats(bool)+0x1649>
  880bf8:	4c 8d a4 24 e0 01 00 	lea    0x1e0(%rsp),%r12
  880bff:	00 
