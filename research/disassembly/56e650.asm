
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000056e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>:
  56e650:	mov    %rbx,-0x18(%rsp)
  56e655:	mov    %rbp,-0x10(%rsp)
  56e65a:	mov    %rdi,%rbx
  56e65d:	mov    %r12,-0x8(%rsp)
  56e662:	sub    $0x18,%rsp
  56e666:	mov    0x78(%rdi),%rdi
  56e66a:	mov    %esi,%ebp
  56e66c:	mov    %edx,%r12d
  56e66f:	test   %rdi,%rdi
  56e672:	je     56e679 <CGameClient::keyEvent(unsigned int, unsigned int, long)+0x29>
  56e674:	call   a843a0 <CGameUI::keyEvent(unsigned int, unsigned int, long)>
  56e679:	lea    0x2d0(%rbx),%rdi
  56e680:	mov    %r12d,%edx
  56e683:	mov    %ebp,%esi
  56e685:	mov    (%rsp),%rbx
  56e689:	mov    0x8(%rsp),%rbp
  56e68e:	mov    0x10(%rsp),%r12
  56e693:	add    $0x18,%rsp
  56e697:	jmp    91ab90 <CKeyManager::keyEvent(unsigned int, unsigned int)>
