
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a83690 <CGameUI::handle_onClick(CEGUI::EventArgs const&)>:
  a83690:	mov    0x28(%rsi),%ecx
  a83693:	mov    0x10(%rsi),%rax
  a83697:	test   %ecx,%ecx
  a83699:	jne    a836b8 <CGameUI::handle_onClick(CEGUI::EventArgs const&)+0x28>
  a8369b:	test   %rax,%rax
  a8369e:	je     a836b8 <CGameUI::handle_onClick(CEGUI::EventArgs const&)+0x28>
  a836a0:	mov    0x1d8(%rax),%rdx
  a836a7:	mov    (%rdi),%rcx
  a836aa:	mov    (%rdx),%esi
  a836ac:	mov    0x10(%rcx),%rax
  a836b0:	jmp    *%rax
  a836b2:	nopw   0x0(%rax,%rax,1)
  a836b8:	mov    $0x1,%eax
  a836bd:	ret
