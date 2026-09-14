
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a842c0 <CGameUI::mouseEvent(unsigned int, unsigned int)>:
  a842c0:	mov    %rbx,-0x10(%rsp)
  a842c5:	mov    %rbp,-0x8(%rsp)
  a842ca:	sub    $0x28,%rsp
  a842ce:	cmp    $0x201,%esi
  a842d4:	mov    %rdi,%rbp
  a842d7:	mov    %esi,%ebx
  a842d9:	je     a84338 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x78>
  a842db:	cmp    $0x202,%esi
  a842e1:	je     a84358 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x98>
  a842e3:	cmp    $0x204,%esi
  a842e9:	je     a84378 <CGameUI::mouseEvent(unsigned int, unsigned int)+0xb8>
  a842ef:	cmp    $0x205,%esi
  a842f5:	je     a84318 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x58>
  a842f7:	lea    0x12a8(%rbp),%rdi
  a842fe:	mov    %ebx,%esi
  a84300:	mov    0x20(%rsp),%rbp
  a84305:	mov    0x18(%rsp),%rbx
  a8430a:	add    $0x28,%rsp
  a8430e:	jmp    91ac90 <CMouseManager::mouseEvent(unsigned int, unsigned int)>
  a84313:	nopl   0x0(%rax,%rax,1)
  a84318:	mov    %edx,0x8(%rsp)
  a8431c:	call   555678 <CEGUI::System::getSingleton()@plt>
  a84321:	mov    $0x1,%esi
  a84326:	mov    %rax,%rdi
  a84329:	call   553e38 <CEGUI::System::injectMouseButtonUp(CEGUI::MouseButton)@plt>
  a8432e:	mov    0x8(%rsp),%edx
  a84332:	jmp    a842f7 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x37>
  a84334:	nopl   0x0(%rax)
  a84338:	mov    %edx,0x8(%rsp)
  a8433c:	call   555678 <CEGUI::System::getSingleton()@plt>
  a84341:	xor    %esi,%esi
  a84343:	mov    %rax,%rdi
  a84346:	call   556158 <CEGUI::System::injectMouseButtonDown(CEGUI::MouseButton)@plt>
  a8434b:	mov    0x8(%rsp),%edx
  a8434f:	jmp    a842f7 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x37>
  a84351:	nopl   0x0(%rax)
  a84358:	mov    %edx,0x8(%rsp)
  a8435c:	call   555678 <CEGUI::System::getSingleton()@plt>
  a84361:	xor    %esi,%esi
  a84363:	mov    %rax,%rdi
  a84366:	call   553e38 <CEGUI::System::injectMouseButtonUp(CEGUI::MouseButton)@plt>
  a8436b:	mov    0x8(%rsp),%edx
  a8436f:	jmp    a842f7 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x37>
  a84371:	nopl   0x0(%rax)
  a84378:	mov    %edx,0x8(%rsp)
  a8437c:	call   555678 <CEGUI::System::getSingleton()@plt>
  a84381:	mov    $0x1,%esi
  a84386:	mov    %rax,%rdi
  a84389:	call   556158 <CEGUI::System::injectMouseButtonDown(CEGUI::MouseButton)@plt>
  a8438e:	mov    0x8(%rsp),%edx
  a84392:	jmp    a842f7 <CGameUI::mouseEvent(unsigned int, unsigned int)+0x37>
