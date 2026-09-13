
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a843a0 <CGameUI::keyEvent(unsigned int, unsigned int, long)>:
  a843a0:	mov    %r12,-0x10(%rsp)
  a843a5:	mov    %rdi,%r12
  a843a8:	lea    0x590(%rdi),%rdi
  a843af:	mov    %rbx,-0x20(%rsp)
  a843b4:	mov    %rbp,-0x18(%rsp)
  a843b9:	mov    %edx,%ebx
  a843bb:	mov    %r13,-0x8(%rsp)
  a843c0:	sub    $0x28,%rsp
  a843c4:	mov    %esi,%ebp
  a843c6:	mov    %rcx,%r13
  a843c9:	call   91ab90 <CKeyManager::keyEvent(unsigned int, unsigned int)>
  a843ce:	mov    0x1690(%r12),%rdi
  a843d6:	test   %rdi,%rdi
  a843d9:	je     a843e7 <CGameUI::keyEvent(unsigned int, unsigned int, long)+0x47>
  a843db:	mov    %r13,%rcx
  a843de:	mov    %ebx,%edx
  a843e0:	mov    %ebp,%esi
  a843e2:	call   ae19d0 <CConsole::keyEvent(unsigned int, unsigned int, long)>
  a843e7:	sub    $0x100,%ebp
  a843ed:	cmp    $0x5,%ebp
  a843f0:	jbe    a84410 <CGameUI::keyEvent(unsigned int, unsigned int, long)+0x70>
  a843f2:	mov    0x8(%rsp),%rbx
  a843f7:	mov    0x10(%rsp),%rbp
  a843fc:	mov    0x18(%rsp),%r12
  a84401:	mov    0x20(%rsp),%r13
  a84406:	add    $0x28,%rsp
  a8440a:	ret
  a8440b:	nopl   0x0(%rax,%rax,1)
  a84410:	mov    %ebp,%ebp
  a84412:	jmp    *0xfe4340(,%rbp,8)
  a84419:	nopl   0x0(%rax)
  a84420:	mov    $0x10,%edi
  a84425:	call   f63260 <GetAsyncKeyState(unsigned int)>
  a8442a:	test   %ax,%ax
  a8442d:	js     a844c0 <CGameUI::keyEvent(unsigned int, unsigned int, long)+0x120>
  a84433:	call   555678 <CEGUI::System::getSingleton()@plt>
  a84438:	mov    %ebx,%esi
  a8443a:	mov    0x10(%rsp),%rbp
  a8443f:	mov    0x8(%rsp),%rbx
  a84444:	mov    0x18(%rsp),%r12
  a84449:	mov    0x20(%rsp),%r13
  a8444e:	mov    %rax,%rdi
  a84451:	add    $0x28,%rsp
  a84455:	jmp    5554f8 <CEGUI::System::injectChar(unsigned int)@plt>
  a8445a:	nopw   0x0(%rax,%rax,1)
  a84460:	mov    %ebx,%edi
  a84462:	call   f632a0 <LinuxMapVirtual2Scancode(unsigned int)>
  a84467:	mov    %eax,%ebx
  a84469:	call   555678 <CEGUI::System::getSingleton()@plt>
  a8446e:	mov    %ebx,%esi
  a84470:	mov    0x10(%rsp),%rbp
  a84475:	mov    0x8(%rsp),%rbx
  a8447a:	mov    0x18(%rsp),%r12
  a8447f:	mov    0x20(%rsp),%r13
  a84484:	mov    %rax,%rdi
  a84487:	add    $0x28,%rsp
  a8448b:	jmp    5539c8 <CEGUI::System::injectKeyUp(unsigned int)@plt>
  a84490:	mov    %ebx,%edi
  a84492:	call   f632a0 <LinuxMapVirtual2Scancode(unsigned int)>
  a84497:	mov    %eax,%ebx
  a84499:	call   555678 <CEGUI::System::getSingleton()@plt>
  a8449e:	mov    %ebx,%esi
  a844a0:	mov    0x10(%rsp),%rbp
  a844a5:	mov    0x8(%rsp),%rbx
  a844aa:	mov    0x18(%rsp),%r12
  a844af:	mov    0x20(%rsp),%r13
  a844b4:	mov    %rax,%rdi
  a844b7:	add    $0x28,%rsp
  a844bb:	jmp    556128 <CEGUI::System::injectKeyDown(unsigned int)@plt>
  a844c0:	cmp    $0x7e,%ebx
  a844c3:	jne    a84433 <CGameUI::keyEvent(unsigned int, unsigned int, long)+0x93>
  a844c9:	jmp    a843f2 <CGameUI::keyEvent(unsigned int, unsigned int, long)+0x52>
