
research/night-audit-2026-10-06/acceptance/catch_double.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <probe>:
   0:	48 83 ec 08          	sub    $0x8,%rsp
   4:	e8 00 00 00 00       	call   9 <probe+0x9>
			5: R_X86_64_PC32	raise_value-0x4
   9:	31 c0                	xor    %eax,%eax
   b:	48 83 c4 08          	add    $0x8,%rsp
   f:	c3                   	ret
  10:	48 83 fa 01          	cmp    $0x1,%rdx
  14:	48 89 c7             	mov    %rax,%rdi
  17:	74 05                	je     1e <probe+0x1e>
  19:	e8 00 00 00 00       	call   1e <probe+0x1e>
			1a: R_X86_64_PC32	_Unwind_Resume-0x4
  1e:	e8 00 00 00 00       	call   23 <probe+0x23>
			1f: R_X86_64_PC32	__cxa_begin_catch-0x4
  23:	e8 00 00 00 00       	call   28 <probe+0x28>
			24: R_X86_64_PC32	__cxa_end_catch-0x4
  28:	b8 07 00 00 00       	mov    $0x7,%eax
  2d:	eb dc                	jmp    b <probe+0xb>
