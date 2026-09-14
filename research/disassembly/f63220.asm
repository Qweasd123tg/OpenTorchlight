
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000f63220 <GetCursorPos(POINT*)>:
  f63220:	mov    0x5eacd9(%rip),%rax        # 154df00 <MouseX>
  f63227:	mov    %rax,(%rdi)
  f6322a:	mov    0x5eacd7(%rip),%rax        # 154df08 <MouseY>
  f63231:	mov    %rax,0x8(%rdi)
  f63235:	xor    %eax,%eax
  f63237:	ret
