
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000f63280 <GetKeyState(unsigned int)>:
  f63280:	mov    %edi,%edi
  f63282:	cmpb   $0x1,0x154de00(%rdi)
  f63289:	sbb    %eax,%eax
  f6328b:	not    %eax
  f6328d:	and    $0x8000,%ax
  f63291:	ret
