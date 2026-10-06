
research/night-audit-2026-10-06/acceptance/driver.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	48 83 ec 08          	sub    $0x8,%rsp
   4:	e8 00 00 00 00       	call   9 <main+0x9>
			5: R_X86_64_PC32	probe-0x4
   9:	48 83 c4 08          	add    $0x8,%rsp
   d:	c3                   	ret
   e:	48 89 c7             	mov    %rax,%rdi
  11:	e8 00 00 00 00       	call   16 <main+0x16>
			12: R_X86_64_PC32	__cxa_begin_catch-0x4
  16:	e8 00 00 00 00       	call   1b <main+0x1b>
			17: R_X86_64_PC32	__cxa_end_catch-0x4
  1b:	b8 63 00 00 00       	mov    $0x63,%eax
  20:	eb e7                	jmp    9 <main+0x9>
  22:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  29:	1f 84 00 00 00 00 00 

0000000000000030 <raise_value>:
  30:	bf 04 00 00 00       	mov    $0x4,%edi
  35:	48 83 ec 08          	sub    $0x8,%rsp
  39:	e8 00 00 00 00       	call   3e <raise_value+0xe>
			3a: R_X86_64_PC32	__cxa_allocate_exception-0x4
  3e:	31 d2                	xor    %edx,%edx
  40:	c7 00 03 00 00 00    	movl   $0x3,(%rax)
  46:	be 00 00 00 00       	mov    $0x0,%esi
			47: R_X86_64_32	typeinfo for int
  4b:	48 89 c7             	mov    %rax,%rdi
  4e:	e8 00 00 00 00       	call   53 <raise_value+0x23>
			4f: R_X86_64_PC32	__cxa_throw-0x4
