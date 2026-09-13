
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000056e600 <CGameClient::mouseEvent(unsigned int, unsigned int)>:
  56e600:	mov    %rbx,-0x18(%rsp)
  56e605:	mov    %rbp,-0x10(%rsp)
  56e60a:	mov    %rdi,%rbx
  56e60d:	mov    %r12,-0x8(%rsp)
  56e612:	sub    $0x18,%rsp
  56e616:	mov    0x78(%rdi),%rdi
  56e61a:	mov    %esi,%ebp
  56e61c:	mov    %edx,%r12d
  56e61f:	test   %rdi,%rdi
  56e622:	je     56e629 <CGameClient::mouseEvent(unsigned int, unsigned int)+0x29>
  56e624:	call   a842c0 <CGameUI::mouseEvent(unsigned int, unsigned int)>
  56e629:	lea    0xfe8(%rbx),%rdi
  56e630:	mov    %r12d,%edx
  56e633:	mov    %ebp,%esi
  56e635:	mov    (%rsp),%rbx
  56e639:	mov    0x8(%rsp),%rbp
  56e63e:	mov    0x10(%rsp),%r12
  56e643:	add    $0x18,%rsp
  56e647:	jmp    91ac90 <CMouseManager::mouseEvent(unsigned int, unsigned int)>
