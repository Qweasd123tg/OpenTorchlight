
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000f632b0 <ClearKeyState()>:
  f632b0:	mov    $0x154de00,%edx
  f632b5:	mov    $0x20,%ecx
  f632ba:	xor    %eax,%eax
  f632bc:	mov    %rdx,%rdi
  f632bf:	rep stos %rax,(%rdi)
  f632c2:	ret
