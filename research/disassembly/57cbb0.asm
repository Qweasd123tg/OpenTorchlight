
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000057cbb0 <CGameClient::processInput(void*, float, bool)>:
  57cbb0:	test   %dl,%dl
  57cbb2:	je     57cbd5 <CGameClient::processInput(void*, float, bool)+0x25>
  57cbb4:	mov    0x38d0(%rdi),%eax
  57cbba:	test   %eax,%eax
  57cbbc:	jne    57cbd0 <CGameClient::processInput(void*, float, bool)+0x20>
  57cbbe:	mov    $0x1,%edx
  57cbc3:	jmp    56e4d0 <CGameClient::processMenuInput(void*, float, bool)>
  57cbc8:	nopl   0x0(%rax,%rax,1)
  57cbd0:	cmp    $0x1,%eax
  57cbd3:	je     57cbe0 <CGameClient::processInput(void*, float, bool)+0x30>
  57cbd5:	mov    $0x1,%eax
  57cbda:	ret
  57cbdb:	nopl   0x0(%rax,%rax,1)
  57cbe0:	mov    $0x1,%edx
  57cbe5:	jmp    57c060 <CGameClient::processIngameInput(void*, float, bool)>
