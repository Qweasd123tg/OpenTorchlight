
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000ab80c0 <CGameUI::processInput(CGameClient*, void*, float, bool)>:
  ab80c0:	mov    0x38d0(%rsi),%esi
  ab80c6:	mov    %rdx,%rax
  ab80c9:	test   %esi,%esi
  ab80cb:	jne    ab80e0 <CGameUI::processInput(CGameClient*, void*, float, bool)+0x20>
  ab80cd:	movzbl %cl,%edx
  ab80d0:	mov    %rax,%rsi
  ab80d3:	jmp    a84160 <CGameUI::processMenuInput(void*, float, bool)>
  ab80d8:	nopl   0x0(%rax,%rax,1)
  ab80e0:	cmp    $0x1,%esi
  ab80e3:	je     ab80f0 <CGameUI::processInput(CGameClient*, void*, float, bool)+0x30>
  ab80e5:	mov    $0x1,%eax
  ab80ea:	ret
  ab80eb:	nopl   0x0(%rax,%rax,1)
  ab80f0:	movzbl %cl,%edx
  ab80f3:	mov    %rax,%rsi
  ab80f6:	jmp    ab6080 <CGameUI::processIngameInput(void*, float, bool)>
