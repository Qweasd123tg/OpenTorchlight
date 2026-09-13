
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000f63260 <GetAsyncKeyState(unsigned int)>:
  f63260:	mov    %edi,%edi
  f63262:	cmpb   $0x1,0x154de00(%rdi)
  f63269:	sbb    %eax,%eax
  f6326b:	not    %eax
  f6326d:	and    $0x8000,%ax
  f63271:	ret
