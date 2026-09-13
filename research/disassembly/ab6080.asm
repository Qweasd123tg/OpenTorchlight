
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000ab6080 <CGameUI::processIngameInput(void*, float, bool)>:
  ab6080:	push   %r15
  ab6082:	push   %r14
  ab6084:	mov    %edx,%r14d
  ab6087:	push   %r13
  ab6089:	push   %r12
  ab608b:	mov    %rsi,%r12
  ab608e:	push   %rbp
  ab608f:	push   %rbx
  ab6090:	mov    %rdi,%rbx
  ab6093:	sub    $0x118,%rsp
  ab609a:	movss  %xmm0,0x38(%rsp)
  ab60a0:	cmpq   $0x0,0x38(%rdi)
  ab60a5:	je     ab6eb0 <CGameUI::processIngameInput(void*, float, bool)+0xe30>
  ab60ab:	movzbl 0x1998(%rdi),%ebp
  ab60b2:	movb   $0x0,0x1998(%rdi)
  ab60b9:	xor    $0x1,%ebp
  ab60bc:	test   %dl,%dl
  ab60be:	jne    ab6100 <CGameUI::processIngameInput(void*, float, bool)+0x80>
  ab60c0:	movb   $0x0,0x12fb(%rbx)
  ab60c7:	movl   $0xffffffff,0x1674(%rbx)
  ab60d1:	movl   $0xffffffff,0x1678(%rbx)
  ab60db:	movl   $0xffffffff,0x167c(%rbx)
  ab60e5:	add    $0x118,%rsp
  ab60ec:	mov    %ebp,%eax
  ab60ee:	pop    %rbx
  ab60ef:	pop    %rbp
  ab60f0:	pop    %r12
  ab60f2:	pop    %r13
  ab60f4:	pop    %r14
  ab60f6:	pop    %r15
  ab60f8:	ret
  ab60f9:	nopl   0x0(%rax)
  ab6100:	call   a84230 <CGameUI::captureProcessInput()>
  ab6105:	mov    0x4c0(%rbx),%rdx
  ab610c:	xor    %eax,%eax
  ab610e:	cmpb   $0x0,0x1670(%rbx)
  ab6115:	movb   $0x0,0x1670(%rbx)
  ab611c:	mov    0x348(%rdx),%rdx
  ab6123:	cmovne %eax,%ebp
  ab6126:	cmpq   $0x0,0xb0(%rdx)
  ab612e:	je     ab613a <CGameUI::processIngameInput(void*, float, bool)+0xba>
  ab6130:	cmpb   $0x0,0x1660(%rbx)
  ab6137:	cmovne %eax,%ebp
  ab613a:	lea    0x12a8(%rbx),%rax
  ab6141:	mov    %r12,%rsi
  ab6144:	mov    %rax,%rdi
  ab6147:	mov    %rax,0x40(%rsp)
  ab614c:	call   91aec0 <CMouseManager::update(void*)>
  ab6151:	cvtsi2ssq 0x12d8(%rbx),%xmm1
  ab615a:	cvtsi2ssq 0x12d0(%rbx),%xmm0
  ab6163:	movss  %xmm1,0x10(%rsp)
  ab6169:	movss  %xmm0,0x20(%rsp)
  ab616f:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab6174:	movss  0x10(%rsp),%xmm1
  ab617a:	mov    %rax,%rdi
  ab617d:	movss  0x20(%rsp),%xmm0
  ab6183:	call   554108 <CEGUI::System::injectMousePosition(float, float)@plt>
  ab6188:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab618d:	movss  0x38(%rsp),%xmm0
  ab6193:	mov    %rax,%rdi
  ab6196:	call   552b38 <CEGUI::System::injectTimePulse(float)@plt>
  ab619b:	mov    0x40(%rsp),%rdi
  ab61a0:	mov    $0x1,%esi
  ab61a5:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  ab61aa:	test   %al,%al
  ab61ac:	je     ab6e90 <CGameUI::processIngameInput(void*, float, bool)+0xe10>
  ab61b2:	cmpb   $0x0,0x1660(%rbx)
  ab61b9:	jne    ab61f0 <CGameUI::processIngameInput(void*, float, bool)+0x170>
  ab61bb:	cmpb   $0x0,0x1643(%rbx)
  ab61c2:	jne    ab61f0 <CGameUI::processIngameInput(void*, float, bool)+0x170>
  ab61c4:	cmpb   $0x0,0x1641(%rbx)
  ab61cb:	jne    ab61f0 <CGameUI::processIngameInput(void*, float, bool)+0x170>
  ab61cd:	mov    0x4c0(%rbx),%rax
  ab61d4:	mov    0x348(%rax),%rsi
  ab61db:	mov    0xb0(%rsi),%rdi
  ab61e2:	test   %rdi,%rdi
  ab61e5:	je     ab61f0 <CGameUI::processIngameInput(void*, float, bool)+0x170>
  ab61e7:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab61ec:	nopl   0x0(%rax)
  ab61f0:	mov    0x40(%rsp),%rdi
  ab61f5:	mov    $0x1,%esi
  ab61fa:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  ab61ff:	test   %al,%al
  ab6201:	jne    ab6840 <CGameUI::processIngameInput(void*, float, bool)+0x7c0>
  ab6207:	cmpq   $0x0,0xb8(%rbx)
  ab620f:	je     ab62a7 <CGameUI::processIngameInput(void*, float, bool)+0x227>
  ab6215:	cvtsi2ssq 0x12d8(%rbx),%xmm0
  ab621e:	mov    %rbx,%rdi
  ab6221:	movss  %xmm0,0x3c(%rsp)
  ab6227:	movss  0x520a69(%rip),%xmm0        # fd6c98 <typeinfo name for CQuadtreeNode<unsigned int>+0x38>
  ab622f:	call   a83e70 <CGameUI::scaledY(float)>
  ab6234:	movss  0x3c(%rsp),%xmm1
  ab623a:	mov    %rbx,%rdi
  ab623d:	subss  %xmm0,%xmm1
  ab6241:	movss  %xmm1,0x3c(%rsp)
  ab6247:	cvtsi2ssq 0x12d0(%rbx),%xmm0
  ab6250:	movss  %xmm0,0x48(%rsp)
  ab6256:	movss  0x52fd7a(%rip),%xmm0        # fe5fd8 <typeinfo name for CSkillFoldout+0x18>
  ab625e:	call   a83e70 <CGameUI::scaledY(float)>
  ab6263:	movss  0x48(%rsp),%xmm1
  ab6269:	movl   $0x0,0x70(%rsp)
  ab6271:	subss  %xmm0,%xmm1
  ab6275:	movss  0x3c(%rsp),%xmm0
  ab627b:	movss  %xmm0,0x7c(%rsp)
  ab6281:	movl   $0x0,0x78(%rsp)
  ab6289:	lea    0x70(%rsp),%rsi
  ab628e:	movss  %xmm1,0x74(%rsp)
  ab6294:	mov    0xb8(%rbx),%rax
  ab629b:	mov    0x2c8(%rax),%rdi
  ab62a2:	call   5548a8 <CEGUI::Window::setPosition(CEGUI::UVector2 const&)@plt>
  ab62a7:	mov    0x38(%rbx),%rdi
  ab62ab:	test   %rdi,%rdi
  ab62ae:	je     ab6998 <CGameUI::processIngameInput(void*, float, bool)+0x918>
  ab62b4:	mov    (%rdi),%rax
  ab62b7:	call   *0x48(%rax)
  ab62ba:	test   %al,%al
  ab62bc:	jne    ab6998 <CGameUI::processIngameInput(void*, float, bool)+0x918>
  ab62c2:	mov    0x38(%rbx),%rdi
  ab62c6:	test   %rdi,%rdi
  ab62c9:	je     ab68f7 <CGameUI::processIngameInput(void*, float, bool)+0x877>
  ab62cf:	call   80e850 <CCharacter::alive()>
  ab62d4:	test   %al,%al
  ab62d6:	jne    ab68e0 <CGameUI::processIngameInput(void*, float, bool)+0x860>
  ab62dc:	mov    %rbx,%rdi
  ab62df:	call   a8e0d0 <CGameUI::closeAll()>
  ab62e4:	cmpq   $0x0,0xb8(%rbx)
  ab62ec:	je     ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab62ee:	mov    %rbx,%rdi
  ab62f1:	call   a8f4e0 <CGameUI::returnDraggedItem()>
  ab62f6:	mov    0xb8(%rbx),%rax
  ab62fd:	mov    0x498(%rbx),%rdi
  ab6304:	mov    0x2c8(%rax),%rsi
  ab630b:	cmp    0xb0(%rsi),%rdi
  ab6312:	je     ab77e9 <CGameUI::processIngameInput(void*, float, bool)+0x1769>
  ab6318:	lea    0xb8(%rbx),%rdi
  ab631f:	xor    %esi,%esi
  ab6321:	call   acbc30 <TSafePointer<CEquipment>::setObject(CEquipment*)>
  ab6326:	lea    0xc8(%rbx),%rdi
  ab632d:	xor    %esi,%esi
  ab632f:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  ab6334:	movl   $0xffffffff,0xd8(%rbx)
  ab633e:	mov    %rbx,%rdi
  ab6341:	call   a83d60 <CGameUI::updateHardwareCursor()>
  ab6346:	cs nopw 0x0(%rax,%rax,1)
  ab6350:	mov    0x1678(%rbx),%eax
  ab6356:	mov    $0x0,%edx
  ab635b:	cmp    $0xffffffff,%eax
  ab635e:	cmovne %edx,%ebp
  ab6361:	mov    0x167c(%rbx),%edx
  ab6367:	cmp    $0xffffffff,%edx
  ab636a:	je     ab6375 <CGameUI::processIngameInput(void*, float, bool)+0x2f5>
  ab636c:	cmp    $0xffffffff,%eax
  ab636f:	je     ab7170 <CGameUI::processIngameInput(void*, float, bool)+0x10f0>
  ab6375:	mov    0x4d8(%rbx),%rdi
  ab637c:	mov    (%rdi),%rax
  ab637f:	call   *0x20(%rax)
  ab6382:	test   %al,%al
  ab6384:	je     ab63b0 <CGameUI::processIngameInput(void*, float, bool)+0x330>
  ab6386:	mov    0x1674(%rbx),%eax
  ab638c:	cmp    $0xffffffff,%eax
  ab638f:	je     ab73e0 <CGameUI::processIngameInput(void*, float, bool)+0x1360>
  ab6395:	mov    %eax,0x1674(%rbx)
  ab639b:	mov    0x1678(%rbx),%eax
  ab63a1:	cmp    $0xffffffff,%eax
  ab63a4:	je     ab73d0 <CGameUI::processIngameInput(void*, float, bool)+0x1350>
  ab63aa:	mov    %eax,0x1678(%rbx)
  ab63b0:	mov    0x4f8(%rbx),%rdi
  ab63b7:	mov    (%rdi),%rax
  ab63ba:	call   *0x20(%rax)
  ab63bd:	test   %al,%al
  ab63bf:	je     ab63eb <CGameUI::processIngameInput(void*, float, bool)+0x36b>
  ab63c1:	mov    0x1674(%rbx),%eax
  ab63c7:	cmp    $0xffffffff,%eax
  ab63ca:	je     ab7498 <CGameUI::processIngameInput(void*, float, bool)+0x1418>
  ab63d0:	mov    %eax,0x1674(%rbx)
  ab63d6:	mov    0x1678(%rbx),%eax
  ab63dc:	cmp    $0xffffffff,%eax
  ab63df:	je     ab7480 <CGameUI::processIngameInput(void*, float, bool)+0x1400>
  ab63e5:	mov    %eax,0x1678(%rbx)
  ab63eb:	mov    0x500(%rbx),%rdi
  ab63f2:	mov    (%rdi),%rax
  ab63f5:	call   *0x20(%rax)
  ab63f8:	test   %al,%al
  ab63fa:	je     ab6426 <CGameUI::processIngameInput(void*, float, bool)+0x3a6>
  ab63fc:	mov    0x1674(%rbx),%eax
  ab6402:	cmp    $0xffffffff,%eax
  ab6405:	je     ab7468 <CGameUI::processIngameInput(void*, float, bool)+0x13e8>
  ab640b:	mov    %eax,0x1674(%rbx)
  ab6411:	mov    0x1678(%rbx),%eax
  ab6417:	cmp    $0xffffffff,%eax
  ab641a:	je     ab7450 <CGameUI::processIngameInput(void*, float, bool)+0x13d0>
  ab6420:	mov    %eax,0x1678(%rbx)
  ab6426:	mov    0x4f0(%rbx),%r13
  ab642d:	mov    0x0(%r13),%rax
  ab6431:	mov    %r13,%rdi
  ab6434:	call   *0x20(%rax)
  ab6437:	test   %al,%al
  ab6439:	jne    ab6ee0 <CGameUI::processIngameInput(void*, float, bool)+0xe60>
  ab643f:	mov    $0xffffffff,%r15d
  ab6445:	movq   $0x0,0x48(%rsp)
  ab644e:	movl   $0xffffffff,0x3c(%rsp)
  ab6456:	movq   $0x0,0x50(%rsp)
  ab645f:	mov    %r15d,0x58(%rsp)
  ab6464:	mov    0x508(%rbx),%rdi
  ab646b:	mov    (%rdi),%rax
  ab646e:	call   *0x20(%rax)
  ab6471:	test   %al,%al
  ab6473:	je     ab64c0 <CGameUI::processIngameInput(void*, float, bool)+0x440>
  ab6475:	cmpl   $0xffffffff,0x58(%rsp)
  ab647a:	je     ab7430 <CGameUI::processIngameInput(void*, float, bool)+0x13b0>
  ab6480:	mov    0x508(%rbx),%rdi
  ab6487:	mov    (%rdi),%rax
  ab648a:	call   *0x10(%rax)
  ab648d:	cmp    $0xffffffff,%r15d
  ab6491:	mov    %rax,0x50(%rsp)
  ab6496:	mov    0x508(%rbx),%r13
  ab649d:	je     ab7420 <CGameUI::processIngameInput(void*, float, bool)+0x13a0>
  ab64a3:	cmpl   $0xffffffff,0x3c(%rsp)
  ab64a8:	je     ab7408 <CGameUI::processIngameInput(void*, float, bool)+0x1388>
  ab64ae:	mov    0x4e8(%rbx),%rdi
  ab64b5:	mov    (%rdi),%rax
  ab64b8:	call   *0x10(%rax)
  ab64bb:	mov    %rax,0x48(%rsp)
  ab64c0:	mov    0x4e8(%rbx),%rdi
  ab64c7:	mov    (%rdi),%rax
  ab64ca:	call   *0x20(%rax)
  ab64cd:	test   %al,%al
  ab64cf:	je     ab64f8 <CGameUI::processIngameInput(void*, float, bool)+0x478>
  ab64d1:	cmp    $0xffffffff,%r15d
  ab64d5:	je     ab73f0 <CGameUI::processIngameInput(void*, float, bool)+0x1370>
  ab64db:	mov    0x4e8(%rbx),%rdi
  ab64e2:	cmpl   $0xffffffff,0x3c(%rsp)
  ab64e7:	je     ab73c0 <CGameUI::processIngameInput(void*, float, bool)+0x1340>
  ab64ed:	mov    (%rdi),%rax
  ab64f0:	call   *0x10(%rax)
  ab64f3:	mov    %rax,0x48(%rsp)
  ab64f8:	mov    0x0(%r13),%rax
  ab64fc:	mov    %r13,%rdi
  ab64ff:	call   *0x20(%rax)
  ab6502:	test   %al,%al
  ab6504:	jne    ab6c28 <CGameUI::processIngameInput(void*, float, bool)+0xba8>
  ab650a:	cmpq   $0x0,0xb8(%rbx)
  ab6512:	je     ab6c28 <CGameUI::processIngameInput(void*, float, bool)+0xba8>
  ab6518:	mov    0x50(%rsp),%rdx
  ab651d:	cmp    0xc8(%rbx),%rdx
  ab6524:	sete   0x5f(%rsp)
  ab6529:	mov    0x40(%rsp),%rdi
  ab652e:	mov    $0x1,%esi
  ab6533:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  ab6538:	test   %al,%al
  ab653a:	je     ab6c38 <CGameUI::processIngameInput(void*, float, bool)+0xbb8>
  ab6540:	cmpq   $0x0,0xb8(%rbx)
  ab6548:	je     ab6c38 <CGameUI::processIngameInput(void*, float, bool)+0xbb8>
  ab654e:	mov    %rbx,%rdi
  ab6551:	xor    %ebp,%ebp
  ab6553:	call   a8f4e0 <CGameUI::returnDraggedItem()>
  ab6558:	movl   $0xffffffff,0x3c(%rsp)
  ab6560:	mov    0x1674(%rbx),%ecx
  ab6566:	cmp    $0xffffffff,%ecx
  ab6569:	je     ab6c52 <CGameUI::processIngameInput(void*, float, bool)+0xbd2>
  ab656f:	mov    0x4d8(%rbx),%rdx
  ab6576:	mov    0x38(%rbx),%rsi
  ab657a:	movzbl %bpl,%r8d
  ab657e:	mov    %rbx,%rdi
  ab6581:	call   a8f780 <CGameUI::menuItemClick(CCharacter*, CSubMenu*, int, bool)>
  ab6586:	test   %al,%al
  ab6588:	je     ab69e0 <CGameUI::processIngameInput(void*, float, bool)+0x960>
  ab658e:	mov    0x578(%rbx),%rdi
  ab6595:	movzbl %r14b,%r14d
  ab6599:	mov    %r12,%rsi
  ab659c:	mov    %r14d,%edx
  ab659f:	movss  0x38(%rsp),%xmm0
  ab65a5:	mov    (%rdi),%rax
  ab65a8:	call   *0x20(%rax)
  ab65ab:	test   %al,%al
  ab65ad:	mov    $0x0,%eax
  ab65b2:	mov    0x1948(%rbx),%rdx
  ab65b9:	cmove  %eax,%ebp
  ab65bc:	mov    0x1950(%rbx),%rax
  ab65c3:	sub    %rdx,%rax
  ab65c6:	sar    $0x3,%rax
  ab65ca:	test   %rax,%rax
  ab65cd:	je     ab661b <CGameUI::processIngameInput(void*, float, bool)+0x59b>
  ab65cf:	xor    %ecx,%ecx
  ab65d1:	xor    %r15d,%r15d
  ab65d4:	nopl   0x0(%rax)
  ab65d8:	mov    (%rdx,%rcx,8),%rdi
  ab65dc:	movss  0x38(%rsp),%xmm0
  ab65e2:	mov    %r14d,%edx
  ab65e5:	mov    %r12,%rsi
  ab65e8:	mov    (%rdi),%rax
  ab65eb:	call   *0x10(%rax)
  ab65ee:	mov    $0x0,%edx
  ab65f3:	test   %al,%al
  ab65f5:	mov    0x1950(%rbx),%rax
  ab65fc:	cmovne %ebp,%edx
  ab65ff:	add    $0x1,%r15d
  ab6603:	mov    %edx,%ebp
  ab6605:	mov    0x1948(%rbx),%rdx
  ab660c:	mov    %r15d,%ecx
  ab660f:	sub    %rdx,%rax
  ab6612:	sar    $0x3,%rax
  ab6616:	cmp    %rax,%rcx
  ab6619:	jb     ab65d8 <CGameUI::processIngameInput(void*, float, bool)+0x558>
  ab661b:	mov    0x1930(%rbx),%rdx
  ab6622:	mov    0x1938(%rbx),%rax
  ab6629:	sub    %rdx,%rax
  ab662c:	sar    $0x3,%rax
  ab6630:	test   %rax,%rax
  ab6633:	je     ab6683 <CGameUI::processIngameInput(void*, float, bool)+0x603>
  ab6635:	xor    %ecx,%ecx
  ab6637:	xor    %r15d,%r15d
  ab663a:	nopw   0x0(%rax,%rax,1)
  ab6640:	mov    (%rdx,%rcx,8),%rdi
  ab6644:	movss  0x38(%rsp),%xmm0
  ab664a:	mov    %r14d,%edx
  ab664d:	mov    %r12,%rsi
  ab6650:	mov    (%rdi),%rax
  ab6653:	call   *0x60(%rax)
  ab6656:	mov    $0x0,%edx
  ab665b:	test   %al,%al
  ab665d:	mov    0x1938(%rbx),%rax
  ab6664:	cmovne %ebp,%edx
  ab6667:	add    $0x1,%r15d
  ab666b:	mov    %edx,%ebp
  ab666d:	mov    0x1930(%rbx),%rdx
  ab6674:	mov    %r15d,%ecx
  ab6677:	sub    %rdx,%rax
  ab667a:	sar    $0x3,%rax
  ab667e:	cmp    %rax,%rcx
  ab6681:	jb     ab6640 <CGameUI::processIngameInput(void*, float, bool)+0x5c0>
  ab6683:	cmpb   $0x0,0x12fb(%rbx)
  ab668a:	jne    ab6f30 <CGameUI::processIngameInput(void*, float, bool)+0xeb0>
  ab6690:	cmpb   $0x0,0x1640(%rbx)
  ab6697:	jne    ab66b1 <CGameUI::processIngameInput(void*, float, bool)+0x631>
  ab6699:	mov    0x1318(%rbx),%rsi
  ab66a0:	mov    0xb0(%rsi),%rdi
  ab66a7:	test   %rdi,%rdi
  ab66aa:	je     ab66b1 <CGameUI::processIngameInput(void*, float, bool)+0x631>
  ab66ac:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab66b1:	mov    0x4d8(%rbx),%rax
  ab66b8:	mov    0x1020(%rax),%r12
  ab66bf:	test   %r12,%r12
  ab66c2:	je     ab71f0 <CGameUI::processIngameInput(void*, float, bool)+0x1170>
  ab66c8:	mov    0x38(%rbx),%rax
  ab66cc:	cmpq   $0x0,0xb8(%rbx)
  ab66d4:	je     ab74b0 <CGameUI::processIngameInput(void*, float, bool)+0x1430>
  ab66da:	mov    0x4a0(%rbx),%rax
  ab66e1:	mov    0x20(%rax),%rsi
  ab66e5:	cmpq   $0x0,0xb0(%rsi)
  ab66ed:	je     ab66f8 <CGameUI::processIngameInput(void*, float, bool)+0x678>
  ab66ef:	mov    0x18(%rax),%rdi
  ab66f3:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab66f8:	mov    0x4a8(%rbx),%rax
  ab66ff:	mov    0x20(%rax),%rsi
  ab6703:	cmpq   $0x0,0xb0(%rsi)
  ab670b:	je     ab6716 <CGameUI::processIngameInput(void*, float, bool)+0x696>
  ab670d:	mov    0x18(%rax),%rdi
  ab6711:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6716:	mov    0x4b0(%rbx),%rax
  ab671d:	mov    0x20(%rax),%rsi
  ab6721:	cmpq   $0x0,0xb0(%rsi)
  ab6729:	je     ab6734 <CGameUI::processIngameInput(void*, float, bool)+0x6b4>
  ab672b:	mov    0x18(%rax),%rdi
  ab672f:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6734:	mov    0x558(%rbx),%rax
  ab673b:	mov    0x40(%rax),%r14
  ab673f:	mov    0x38(%rbx),%rax
  ab6743:	test   %r14,%r14
  ab6746:	mov    0x1c8(%rax),%rdi
  ab674d:	jne    ab6cf8 <CGameUI::processIngameInput(void*, float, bool)+0xc78>
  ab6753:	movb   $0x0,0x38(%rsp)
  ab6758:	movzbl 0x1643(%rbx),%eax
  ab675f:	test   %al,%al
  ab6761:	jne    ab69f0 <CGameUI::processIngameInput(void*, float, bool)+0x970>
  ab6767:	cmpb   $0x0,0x1660(%rbx)
  ab676e:	jne    ab69f0 <CGameUI::processIngameInput(void*, float, bool)+0x970>
  ab6774:	cmpb   $0x0,0x38(%rsp)
  ab6779:	jne    ab6a42 <CGameUI::processIngameInput(void*, float, bool)+0x9c2>
  ab677f:	mov    0x38(%rbx),%rdx
  ab6783:	mov    0x1c8(%rdx),%r15
  ab678a:	test   %r15,%r15
  ab678d:	je     ab6a42 <CGameUI::processIngameInput(void*, float, bool)+0x9c2>
  ab6793:	lea    0x590(%rbx),%r14
  ab679a:	mov    $0x14b9b80,%r12d
  ab67a0:	xor    %r13d,%r13d
  ab67a3:	jmp    ab67ba <CGameUI::processIngameInput(void*, float, bool)+0x73a>
  ab67a5:	nopl   (%rax)
  ab67a8:	add    $0x1,%r13d
  ab67ac:	add    $0x4,%r12
  ab67b0:	cmp    $0xc,%r13d
  ab67b4:	je     ab6a3b <CGameUI::processIngameInput(void*, float, bool)+0x9bb>
  ab67ba:	mov    0x78(%rbx),%rdi
  ab67be:	mov    (%r12),%esi
  ab67c2:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab67c7:	mov    %r14,%rdi
  ab67ca:	mov    %eax,%esi
  ab67cc:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab67d1:	test   %al,%al
  ab67d3:	je     ab67a8 <CGameUI::processIngameInput(void*, float, bool)+0x728>
  ab67d5:	mov    0x38(%rbx),%rax
  ab67d9:	mov    %r13d,%edx
  ab67dc:	mov    %r15,%rdi
  ab67df:	mov    0x950(%rax,%rdx,8),%rsi
  ab67e7:	mov    %rdx,0x30(%rsp)
  ab67ec:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  ab67f1:	test   %rax,%rax
  ab67f4:	mov    0x30(%rsp),%rdx
  ab67f9:	je     ab7188 <CGameUI::processIngameInput(void*, float, bool)+0x1108>
  ab67ff:	mov    0x38(%rbx),%rdi
  ab6803:	mov    $0x1,%edx
  ab6808:	mov    %rax,%rsi
  ab680b:	call   80f410 <CCharacter::setActiveSkill(CSkill*, bool)>
  ab6810:	mov    0x38(%rbx),%rax
  ab6814:	xorps  %xmm1,%xmm1
  ab6817:	mov    0x16a8(%rbx),%rdi
  ab681e:	xor    %ecx,%ecx
  ab6820:	mov    $0x1e,%esi
  ab6825:	mov    0x58(%rax),%rdx
  ab6829:	movaps %xmm1,%xmm0
  ab682c:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  ab6831:	jmp    ab67a8 <CGameUI::processIngameInput(void*, float, bool)+0x728>
  ab6836:	cs nopw 0x0(%rax,%rax,1)
  ab6840:	cmpq   $0x0,0x80(%rbx)
  ab6848:	je     ab75e5 <CGameUI::processIngameInput(void*, float, bool)+0x1565>
  ab684e:	xor    %esi,%esi
  ab6850:	mov    %rbx,%rdi
  ab6853:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  ab6858:	mov    0x80(%rbx),%rdi
  ab685f:	test   %rdi,%rdi
  ab6862:	je     ab6881 <CGameUI::processIngameInput(void*, float, bool)+0x801>
  ab6864:	mov    0x88(%rbx),%edx
  ab686a:	lea    0x80(%rbx),%rsi
  ab6871:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab6876:	movq   $0x0,0x80(%rbx)
  ab6881:	mov    0xa0(%rbx),%rdi
  ab6888:	test   %rdi,%rdi
  ab688b:	je     ab68aa <CGameUI::processIngameInput(void*, float, bool)+0x82a>
  ab688d:	mov    0xa8(%rbx),%edx
  ab6893:	lea    0xa0(%rbx),%rsi
  ab689a:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab689f:	movq   $0x0,0xa0(%rbx)
  ab68aa:	mov    0x90(%rbx),%rdi
  ab68b1:	test   %rdi,%rdi
  ab68b4:	je     ab6207 <CGameUI::processIngameInput(void*, float, bool)+0x187>
  ab68ba:	mov    0x98(%rbx),%edx
  ab68c0:	lea    0x90(%rbx),%rsi
  ab68c7:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab68cc:	movq   $0x0,0x90(%rbx)
  ab68d7:	jmp    ab6207 <CGameUI::processIngameInput(void*, float, bool)+0x187>
  ab68dc:	nopl   0x0(%rax)
  ab68e0:	mov    0x38(%rbx),%rdi
  ab68e4:	test   %rdi,%rdi
  ab68e7:	je     ab68f7 <CGameUI::processIngameInput(void*, float, bool)+0x877>
  ab68e9:	mov    (%rdi),%rax
  ab68ec:	call   *0x48(%rax)
  ab68ef:	test   %al,%al
  ab68f1:	je     ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab68f7:	mov    0x540(%rbx),%rax
  ab68fe:	test   %rax,%rax
  ab6901:	je     ab6917 <CGameUI::processIngameInput(void*, float, bool)+0x897>
  ab6903:	cmpb   $0x0,0x30(%rax)
  ab6907:	jne    ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab690d:	cmpb   $0x0,0x31(%rax)
  ab6911:	je     ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab6917:	mov    0x38(%rbx),%rdi
  ab691b:	test   %rdi,%rdi
  ab691e:	je     ab692e <CGameUI::processIngameInput(void*, float, bool)+0x8ae>
  ab6920:	mov    (%rdi),%rax
  ab6923:	call   *0x48(%rax)
  ab6926:	test   %al,%al
  ab6928:	je     ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab692e:	mov    %rbx,%rdi
  ab6931:	call   a83580 <CGameUI::getUIIsInCinematic()>
  ab6936:	test   %al,%al
  ab6938:	jne    ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab693e:	mov    0x78(%rbx),%rdi
  ab6942:	mov    0xa54cf0(%rip),%esi        # 150b638 <KSETTINGS_KEYMAP_CLOSEALL>
  ab6948:	lea    0x590(%rbx),%r13
  ab694f:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab6954:	mov    %r13,%rdi
  ab6957:	mov    %eax,%esi
  ab6959:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab695e:	test   %al,%al
  ab6960:	jne    ab7734 <CGameUI::processIngameInput(void*, float, bool)+0x16b4>
  ab6966:	mov    0x78(%rbx),%rdi
  ab696a:	mov    0xa54ca0(%rip),%esi        # 150b610 <KSETTINGS_KEYMAP_PAUSE>
  ab6970:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab6975:	mov    %r13,%rdi
  ab6978:	mov    %eax,%esi
  ab697a:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab697f:	test   %al,%al
  ab6981:	je     ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab6987:	mov    %rbx,%rdi
  ab698a:	call   a8e2d0 <CGameUI::togglePause()>
  ab698f:	nop
  ab6990:	jmp    ab6350 <CGameUI::processIngameInput(void*, float, bool)+0x2d0>
  ab6995:	nopl   (%rax)
  ab6998:	mov    %rbx,%rdi
  ab699b:	call   ab4f80 <CGameUI::handleKeyPresses()>
  ab69a0:	jmp    ab62c2 <CGameUI::processIngameInput(void*, float, bool)+0x242>
  ab69a5:	cmpq   $0x0,0x50(%rsp)
  ab69ab:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab69b1:	cmpl   $0xffffffff,0x58(%rsp)
  ab69b6:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab69bc:	mov    0x58(%rsp),%ecx
  ab69c0:	mov    0x50(%rsp),%rsi
  ab69c5:	movzbl %bpl,%r8d
  ab69c9:	mov    %r13,%rdx
  ab69cc:	mov    %rbx,%rdi
  ab69cf:	call   a8f780 <CGameUI::menuItemClick(CCharacter*, CSubMenu*, int, bool)>
  ab69d4:	test   %al,%al
  ab69d6:	jne    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab69dc:	nopl   0x0(%rax)
  ab69e0:	xor    %ebp,%ebp
  ab69e2:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab69e7:	nopw   0x0(%rax,%rax,1)
  ab69f0:	mov    0x38(%rbx),%rdx
  ab69f4:	test   %rdx,%rdx
  ab69f7:	je     ab6774 <CGameUI::processIngameInput(void*, float, bool)+0x6f4>
  ab69fd:	cmpb   $0x0,0x1660(%rbx)
  ab6a04:	je     ab6cc0 <CGameUI::processIngameInput(void*, float, bool)+0xc40>
  ab6a0a:	mov    0x1668(%rbx),%r14
  ab6a11:	mov    0x1c8(%rdx),%rdi
  ab6a18:	test   %rdi,%rdi
  ab6a1b:	je     ab6a42 <CGameUI::processIngameInput(void*, float, bool)+0x9c2>
  ab6a1d:	mov    %r14,%rsi
  ab6a20:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  ab6a25:	test   %rax,%rax
  ab6a28:	jne    ab6af0 <CGameUI::processIngameInput(void*, float, bool)+0xa70>
  ab6a2e:	cmp    $0xfffffffffffffc19,%r14
  ab6a35:	je     ab6af0 <CGameUI::processIngameInput(void*, float, bool)+0xa70>
  ab6a3b:	movzbl 0x1643(%rbx),%eax
  ab6a42:	test   %al,%al
  ab6a44:	je     ab6a6b <CGameUI::processIngameInput(void*, float, bool)+0x9eb>
  ab6a46:	mov    0x38(%rbx),%rax
  ab6a4a:	test   %rax,%rax
  ab6a4d:	je     ab6a6b <CGameUI::processIngameInput(void*, float, bool)+0x9eb>
  ab6a4f:	mov    0x4c0(%rbx),%rdx
  ab6a56:	mov    0x348(%rdx),%rdx
  ab6a5d:	cmpq   $0x0,0xb0(%rdx)
  ab6a65:	je     ab760a <CGameUI::processIngameInput(void*, float, bool)+0x158a>
  ab6a6b:	cmpb   $0x0,0x1660(%rbx)
  ab6a72:	je     ab6cd0 <CGameUI::processIngameInput(void*, float, bool)+0xc50>
  ab6a78:	mov    0x38(%rbx),%rax
  ab6a7c:	test   %rax,%rax
  ab6a7f:	je     ab6cd0 <CGameUI::processIngameInput(void*, float, bool)+0xc50>
  ab6a85:	mov    0x4c0(%rbx),%rdx
  ab6a8c:	mov    0x348(%rdx),%rdx
  ab6a93:	cmpq   $0x0,0xb0(%rdx)
  ab6a9b:	je     ab6cd0 <CGameUI::processIngameInput(void*, float, bool)+0xc50>
  ab6aa1:	mov    0x1c8(%rax),%rdi
  ab6aa8:	mov    0x1668(%rbx),%rsi
  ab6aaf:	test   %rdi,%rdi
  ab6ab2:	je     ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab6ab8:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  ab6abd:	test   %rax,%rax
  ab6ac0:	je     ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab6ac6:	mov    0x38(%rbx),%rsi
  ab6aca:	mov    0x4b8(%rbx),%rdi
  ab6ad1:	mov    %rax,%rdx
  ab6ad4:	cvtsi2ssq 0x12d0(%rbx),%xmm0
  ab6add:	cvtsi2ssq 0x12d8(%rbx),%xmm1
  ab6ae6:	call   aaeeb0 <CSkillTooltip::showTooltip(CBaseUnit*, CSkill*, float, float)>
  ab6aeb:	jmp    ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab6af0:	cmpb   $0x0,0x1660(%rbx)
  ab6af7:	je     ab6a3b <CGameUI::processIngameInput(void*, float, bool)+0x9bb>
  ab6afd:	lea    0x590(%rbx),%r15
  ab6b04:	mov    $0x14b9b80,%r13d
  ab6b0a:	xor    %r12d,%r12d
  ab6b0d:	jmp    ab6bcd <CGameUI::processIngameInput(void*, float, bool)+0xb4d>
  ab6b12:	nopw   0x0(%rax,%rax,1)
  ab6b18:	mov    0x38(%rbx),%rdi
  ab6b1c:	mov    %r14,%rdx
  ab6b1f:	mov    %r12d,%esi
  ab6b22:	call   8e3f20 <CPlayer::setLeftMappedFunctionSkill(unsigned int, long long)>
  ab6b27:	mov    0x4c0(%rbx),%rdi
  ab6b2e:	mov    0x348(%rdi),%rsi
  ab6b35:	mov    0xb0(%rsi),%rax
  ab6b3c:	test   %rax,%rax
  ab6b3f:	je     ab6b50 <CGameUI::processIngameInput(void*, float, bool)+0xad0>
  ab6b41:	mov    %rax,%rdi
  ab6b44:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6b49:	mov    0x4c0(%rbx),%rdi
  ab6b50:	movzbl 0xcb1(%rdi),%ecx
  ab6b57:	movzbl 0xcb0(%rdi),%edx
  ab6b5e:	mov    0x38(%rbx),%rsi
  ab6b62:	movss  0x4f1bf6(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  ab6b6a:	movaps %xmm1,%xmm0
  ab6b6d:	call   a9c680 <CSkillFoldout::showFoldout(CBaseUnit*, float, float, bool, bool)>
  ab6b72:	mov    0x4b8(%rbx),%rax
  ab6b79:	mov    0x30(%rax),%rsi
  ab6b7d:	mov    0xb0(%rsi),%rdi
  ab6b84:	test   %rdi,%rdi
  ab6b87:	je     ab6b8e <CGameUI::processIngameInput(void*, float, bool)+0xb0e>
  ab6b89:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6b8e:	mov    0x558(%rbx),%rdi
  ab6b95:	mov    (%rdi),%rax
  ab6b98:	call   *0x20(%rax)
  ab6b9b:	test   %al,%al
  ab6b9d:	jne    ab73a8 <CGameUI::processIngameInput(void*, float, bool)+0x1328>
  ab6ba3:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab6ba8:	xorps  %xmm1,%xmm1
  ab6bab:	mov    %rax,%rdi
  ab6bae:	movss  0x4edc46(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  ab6bb6:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  ab6bbb:	add    $0x1,%r12d
  ab6bbf:	add    $0x4,%r13
  ab6bc3:	cmp    $0xc,%r12d
  ab6bc7:	je     ab6a3b <CGameUI::processIngameInput(void*, float, bool)+0x9bb>
  ab6bcd:	mov    0x78(%rbx),%rdi
  ab6bd1:	mov    0x0(%r13),%esi
  ab6bd5:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab6bda:	mov    %r15,%rdi
  ab6bdd:	mov    %eax,%esi
  ab6bdf:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab6be4:	test   %al,%al
  ab6be6:	je     ab6bbb <CGameUI::processIngameInput(void*, float, bool)+0xb3b>
  ab6be8:	mov    0x4c0(%rbx),%rax
  ab6bef:	mov    0x348(%rax),%rdx
  ab6bf6:	cmpq   $0x0,0xb0(%rdx)
  ab6bfe:	je     ab6c0d <CGameUI::processIngameInput(void*, float, bool)+0xb8d>
  ab6c00:	cmpb   $0x0,0xcb1(%rax)
  ab6c07:	jne    ab6b18 <CGameUI::processIngameInput(void*, float, bool)+0xa98>
  ab6c0d:	mov    0x38(%rbx),%rdi
  ab6c11:	mov    %r14,%rdx
  ab6c14:	mov    %r12d,%esi
  ab6c17:	call   8e3ed0 <CPlayer::setMappedFunctionSkill(unsigned int, long long)>
  ab6c1c:	jmp    ab6b27 <CGameUI::processIngameInput(void*, float, bool)+0xaa7>
  ab6c21:	nopl   0x0(%rax)
  ab6c28:	movb   $0x0,0x5f(%rsp)
  ab6c2d:	jmp    ab6529 <CGameUI::processIngameInput(void*, float, bool)+0x4a9>
  ab6c32:	nopw   0x0(%rax,%rax,1)
  ab6c38:	cmpb   $0x0,0x5f(%rsp)
  ab6c3d:	jne    ab654e <CGameUI::processIngameInput(void*, float, bool)+0x4ce>
  ab6c43:	mov    0x1674(%rbx),%ecx
  ab6c49:	cmp    $0xffffffff,%ecx
  ab6c4c:	jne    ab656f <CGameUI::processIngameInput(void*, float, bool)+0x4ef>
  ab6c52:	cmp    $0xffffffff,%r15d
  ab6c56:	je     ab7060 <CGameUI::processIngameInput(void*, float, bool)+0xfe0>
  ab6c5c:	mov    0x4e8(%rbx),%rdx
  ab6c63:	mov    0x48(%rsp),%rsi
  ab6c68:	movzbl %bpl,%r8d
  ab6c6c:	mov    %r15d,%ecx
  ab6c6f:	mov    %rbx,%rdi
  ab6c72:	call   a8f780 <CGameUI::menuItemClick(CCharacter*, CSubMenu*, int, bool)>
  ab6c77:	mov    0x4f0(%rbx),%rdi
  ab6c7e:	test   %al,%al
  ab6c80:	mov    $0x0,%eax
  ab6c85:	cmove  %eax,%ebp
  ab6c88:	mov    (%rdi),%rax
  ab6c8b:	call   *0x20(%rax)
  ab6c8e:	test   %al,%al
  ab6c90:	jne    ab75f8 <CGameUI::processIngameInput(void*, float, bool)+0x1578>
  ab6c96:	mov    0x508(%rbx),%rdi
  ab6c9d:	mov    (%rdi),%rax
  ab6ca0:	call   *0x20(%rax)
  ab6ca3:	test   %al,%al
  ab6ca5:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab6cab:	mov    0x508(%rbx),%rdi
  ab6cb2:	mov    (%rdi),%rax
  ab6cb5:	call   *0x48(%rax)
  ab6cb8:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab6cbd:	nopl   (%rax)
  ab6cc0:	mov    0x1648(%rbx),%r14
  ab6cc7:	jmp    ab6a11 <CGameUI::processIngameInput(void*, float, bool)+0x991>
  ab6ccc:	nopl   0x0(%rax)
  ab6cd0:	mov    0x4b8(%rbx),%rax
  ab6cd7:	mov    0x30(%rax),%rsi
  ab6cdb:	mov    0xb0(%rsi),%rdi
  ab6ce2:	test   %rdi,%rdi
  ab6ce5:	je     ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab6ceb:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6cf0:	jmp    ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab6cf5:	nopl   (%rax)
  ab6cf8:	test   %rdi,%rdi
  ab6cfb:	je     ab6753 <CGameUI::processIngameInput(void*, float, bool)+0x6d3>
  ab6d01:	mov    %r14,%rsi
  ab6d04:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  ab6d09:	test   %rax,%rax
  ab6d0c:	mov    %rax,%r12
  ab6d0f:	je     ab6e78 <CGameUI::processIngameInput(void*, float, bool)+0xdf8>
  ab6d15:	mov    %rax,%rdi
  ab6d18:	call   ca7740 <CSkill::calculateEffectiveSkillLevel()>
  ab6d1d:	mov    0xe0(%r12),%r8d
  ab6d25:	test   %r8d,%r8d
  ab6d28:	je     ab6e78 <CGameUI::processIngameInput(void*, float, bool)+0xdf8>
  ab6d2e:	movzbl 0x6b(%r12),%eax
  ab6d34:	movzbl 0x6d(%r12),%edx
  ab6d3a:	xor    $0x1,%eax
  ab6d3d:	test   %eax,%edx
  ab6d3f:	je     ab6e78 <CGameUI::processIngameInput(void*, float, bool)+0xdf8>
  ab6d45:	cmpl   $0x4,0x60(%r12)
  ab6d4b:	je     ab6e78 <CGameUI::processIngameInput(void*, float, bool)+0xdf8>
  ab6d51:	lea    0x590(%rbx),%r15
  ab6d58:	mov    $0x14b9b80,%r13d
  ab6d5e:	xor    %r12d,%r12d
  ab6d61:	movb   $0x0,0x38(%rsp)
  ab6d66:	jmp    ab6e1f <CGameUI::processIngameInput(void*, float, bool)+0xd9f>
  ab6d6b:	nopl   0x0(%rax,%rax,1)
  ab6d70:	mov    0x38(%rbx),%rdi
  ab6d74:	mov    %r14,%rdx
  ab6d77:	mov    %r12d,%esi
  ab6d7a:	call   8e3f20 <CPlayer::setLeftMappedFunctionSkill(unsigned int, long long)>
  ab6d7f:	mov    0x4c0(%rbx),%rax
  ab6d86:	mov    0x348(%rax),%rsi
  ab6d8d:	mov    0xb0(%rsi),%rdi
  ab6d94:	test   %rdi,%rdi
  ab6d97:	je     ab6de3 <CGameUI::processIngameInput(void*, float, bool)+0xd63>
  ab6d99:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6d9e:	mov    0x4c0(%rbx),%rdi
  ab6da5:	mov    0x38(%rbx),%rsi
  ab6da9:	movss  0x4f19af(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  ab6db1:	movaps %xmm1,%xmm0
  ab6db4:	movzbl 0xcb1(%rdi),%ecx
  ab6dbb:	movzbl 0xcb0(%rdi),%edx
  ab6dc2:	call   a9c680 <CSkillFoldout::showFoldout(CBaseUnit*, float, float, bool, bool)>
  ab6dc7:	mov    0x4b8(%rbx),%rax
  ab6dce:	mov    0x30(%rax),%rsi
  ab6dd2:	mov    0xb0(%rsi),%rdi
  ab6dd9:	test   %rdi,%rdi
  ab6ddc:	je     ab6de3 <CGameUI::processIngameInput(void*, float, bool)+0xd63>
  ab6dde:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab6de3:	mov    0x558(%rbx),%rdi
  ab6dea:	mov    (%rdi),%rax
  ab6ded:	call   *0x48(%rax)
  ab6df0:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab6df5:	xorps  %xmm1,%xmm1
  ab6df8:	mov    %rax,%rdi
  ab6dfb:	movss  0x4ed9f9(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  ab6e03:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  ab6e08:	movb   $0x1,0x38(%rsp)
  ab6e0d:	add    $0x1,%r12d
  ab6e11:	add    $0x4,%r13
  ab6e15:	cmp    $0xc,%r12d
  ab6e19:	je     ab6758 <CGameUI::processIngameInput(void*, float, bool)+0x6d8>
  ab6e1f:	mov    0x78(%rbx),%rdi
  ab6e23:	mov    0x0(%r13),%esi
  ab6e27:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab6e2c:	mov    %r15,%rdi
  ab6e2f:	mov    %eax,%esi
  ab6e31:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab6e36:	test   %al,%al
  ab6e38:	je     ab6e0d <CGameUI::processIngameInput(void*, float, bool)+0xd8d>
  ab6e3a:	mov    0x4c0(%rbx),%rax
  ab6e41:	mov    0x348(%rax),%rdx
  ab6e48:	cmpq   $0x0,0xb0(%rdx)
  ab6e50:	je     ab6e5f <CGameUI::processIngameInput(void*, float, bool)+0xddf>
  ab6e52:	cmpb   $0x0,0xcb1(%rax)
  ab6e59:	jne    ab6d70 <CGameUI::processIngameInput(void*, float, bool)+0xcf0>
  ab6e5f:	mov    0x38(%rbx),%rdi
  ab6e63:	mov    %r14,%rdx
  ab6e66:	mov    %r12d,%esi
  ab6e69:	call   8e3ed0 <CPlayer::setMappedFunctionSkill(unsigned int, long long)>
  ab6e6e:	jmp    ab6d7f <CGameUI::processIngameInput(void*, float, bool)+0xcff>
  ab6e73:	nopl   0x0(%rax,%rax,1)
  ab6e78:	cmp    $0xfffffffffffffc19,%r14
  ab6e7f:	jne    ab6753 <CGameUI::processIngameInput(void*, float, bool)+0x6d3>
  ab6e85:	jmp    ab6d51 <CGameUI::processIngameInput(void*, float, bool)+0xcd1>
  ab6e8a:	nopw   0x0(%rax,%rax,1)
  ab6e90:	mov    0x40(%rsp),%rdi
  ab6e95:	xor    %esi,%esi
  ab6e97:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  ab6e9c:	test   %al,%al
  ab6e9e:	je     ab61f0 <CGameUI::processIngameInput(void*, float, bool)+0x170>
  ab6ea4:	jmp    ab61b2 <CGameUI::processIngameInput(void*, float, bool)+0x132>
  ab6ea9:	nopl   0x0(%rax)
  ab6eb0:	movb   $0x0,0x12fb(%rdi)
  ab6eb7:	movl   $0xffffffff,0x1674(%rdi)
  ab6ec1:	mov    $0x1,%ebp
  ab6ec6:	movl   $0xffffffff,0x1678(%rdi)
  ab6ed0:	movl   $0xffffffff,0x167c(%rdi)
  ab6eda:	jmp    ab60e5 <CGameUI::processIngameInput(void*, float, bool)+0x65>
  ab6edf:	nop
  ab6ee0:	mov    0x4f0(%rbx),%rdi
  ab6ee7:	mov    0x3430(%rdi),%eax
  ab6eed:	mov    %eax,0x58(%rsp)
  ab6ef1:	mov    (%rdi),%rax
  ab6ef4:	call   *0x10(%rax)
  ab6ef7:	mov    %rax,0x50(%rsp)
  ab6efc:	mov    0x4f0(%rbx),%r13
  ab6f03:	mov    0x342c(%r13),%edx
  ab6f0a:	mov    0x3428(%r13),%r15d
  ab6f11:	mov    %edx,0x3c(%rsp)
  ab6f15:	mov    0x4e8(%rbx),%rdi
  ab6f1c:	mov    (%rdi),%rax
  ab6f1f:	call   *0x10(%rax)
  ab6f22:	mov    %rax,0x48(%rsp)
  ab6f27:	jmp    ab6464 <CGameUI::processIngameInput(void*, float, bool)+0x3e4>
  ab6f2c:	nopl   0x0(%rax)
  ab6f30:	mov    0x40(%rsp),%rdi
  ab6f35:	xor    %esi,%esi
  ab6f37:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  ab6f3c:	test   %al,%al
  ab6f3e:	je     ab6690 <CGameUI::processIngameInput(void*, float, bool)+0x610>
  ab6f44:	xor    %r12d,%r12d
  ab6f47:	cmpq   $0x0,0x80(%rbx)
  ab6f4f:	je     ab6fe0 <CGameUI::processIngameInput(void*, float, bool)+0xf60>
  ab6f55:	xor    %esi,%esi
  ab6f57:	mov    %rbx,%rdi
  ab6f5a:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  ab6f5f:	mov    0x80(%rbx),%rdi
  ab6f66:	test   %rdi,%rdi
  ab6f69:	je     ab6f88 <CGameUI::processIngameInput(void*, float, bool)+0xf08>
  ab6f6b:	mov    0x88(%rbx),%edx
  ab6f71:	lea    0x80(%rbx),%rsi
  ab6f78:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab6f7d:	movq   $0x0,0x80(%rbx)
  ab6f88:	mov    0xa0(%rbx),%rdi
  ab6f8f:	test   %rdi,%rdi
  ab6f92:	je     ab6fb1 <CGameUI::processIngameInput(void*, float, bool)+0xf31>
  ab6f94:	mov    0xa8(%rbx),%edx
  ab6f9a:	lea    0xa0(%rbx),%rsi
  ab6fa1:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab6fa6:	movq   $0x0,0xa0(%rbx)
  ab6fb1:	mov    0x90(%rbx),%rdi
  ab6fb8:	mov    $0x1,%r12d
  ab6fbe:	test   %rdi,%rdi
  ab6fc1:	je     ab6fe0 <CGameUI::processIngameInput(void*, float, bool)+0xf60>
  ab6fc3:	mov    0x98(%rbx),%edx
  ab6fc9:	lea    0x90(%rbx),%rsi
  ab6fd0:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  ab6fd5:	movq   $0x0,0x90(%rbx)
  ab6fe0:	cmpq   $0xffffffffffffffff,0xb0(%rbx)
  ab6fe8:	je     ab7005 <CGameUI::processIngameInput(void*, float, bool)+0xf85>
  ab6fea:	xor    %esi,%esi
  ab6fec:	mov    %rbx,%rdi
  ab6fef:	mov    $0x1,%r12d
  ab6ff5:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  ab6ffa:	movq   $0xffffffffffffffff,0xb0(%rbx)
  ab7005:	mov    0xb8(%rbx),%rdi
  ab700c:	test   %rdi,%rdi
  ab700f:	je     ab7038 <CGameUI::processIngameInput(void*, float, bool)+0xfb8>
  ab7011:	mov    0xc8(%rbx),%r14
  ab7018:	cmp    %r14,0x38(%rbx)
  ab701c:	je     ab764f <CGameUI::processIngameInput(void*, float, bool)+0x15cf>
  ab7022:	mov    0x4e8(%rbx),%rdi
  ab7029:	mov    (%rdi),%rax
  ab702c:	call   *0x10(%rax)
  ab702f:	cmp    %r14,%rax
  ab7032:	je     ab7648 <CGameUI::processIngameInput(void*, float, bool)+0x15c8>
  ab7038:	test   %r12b,%r12b
  ab703b:	jne    ab6690 <CGameUI::processIngameInput(void*, float, bool)+0x610>
  ab7041:	mov    %rbx,%rdi
  ab7044:	call   a82ae0 <CGameUI::bothCoveredPartial()>
  ab7049:	test   %al,%al
  ab704b:	je     ab6690 <CGameUI::processIngameInput(void*, float, bool)+0x610>
  ab7051:	mov    %rbx,%rdi
  ab7054:	call   a8e0d0 <CGameUI::closeAll()>
  ab7059:	jmp    ab6690 <CGameUI::processIngameInput(void*, float, bool)+0x610>
  ab705e:	xchg   %ax,%ax
  ab7060:	cmpl   $0xffffffff,0x3c(%rsp)
  ab7065:	je     ab7268 <CGameUI::processIngameInput(void*, float, bool)+0x11e8>
  ab706b:	mov    0x48(%rsp),%rax
  ab7070:	mov    0x3c(%rsp),%esi
  ab7074:	mov    0x490(%rax),%rdi
  ab707b:	call   91b340 <CInventory::getEquipmentInSlot(unsigned int)>
  ab7080:	test   %rax,%rax
  ab7083:	mov    %rax,%r15
  ab7086:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab708c:	cmpq   $0x0,0xb8(%rbx)
  ab7094:	jne    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab709a:	mov    0x48(%rsp),%rdx
  ab709f:	cmpl   $0x2a,0x330(%rdx)
  ab70a6:	je     ab77f5 <CGameUI::processIngameInput(void*, float, bool)+0x1775>
  ab70ac:	mov    %rax,%rdi
  ab70af:	call   acbbe0 <CItem::isUseable()>
  ab70b4:	test   %al,%al
  ab70b6:	je     ab77f5 <CGameUI::processIngameInput(void*, float, bool)+0x1775>
  ab70bc:	mov    0x40(%rbx),%rsi
  ab70c0:	mov    %r15,%rdx
  ab70c3:	mov    %rbx,%rdi
  ab70c6:	call   a92320 <CGameUI::useItem(CLevel&, CEquipment*)>
  ab70cb:	mov    0x4d8(%rbx),%rax
  ab70d2:	movq   $0x0,0x1020(%rax)
  ab70dd:	mov    0x4f0(%rbx),%rax
  ab70e4:	movq   $0x0,0x3438(%rax)
  ab70ef:	mov    0x4f8(%rbx),%rax
  ab70f6:	movq   $0x0,0xf0(%rax)
  ab7101:	mov    0x500(%rbx),%rax
  ab7108:	movq   $0x0,0x190(%rax)
  ab7113:	mov    0x508(%rbx),%rax
  ab711a:	movq   $0x0,0x3408(%rax)
  ab7125:	mov    0x4e8(%rbx),%rax
  ab712c:	movq   $0x0,0x1370(%rax)
  ab7137:	mov    0x4a0(%rbx),%rax
  ab713e:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7146:	mov    0x4a8(%rbx),%rax
  ab714d:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7155:	mov    0x4b0(%rbx),%rax
  ab715c:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7164:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7169:	nopl   0x0(%rax)
  ab7170:	mov    %edx,0x1678(%rbx)
  ab7176:	mov    %eax,0x167c(%rbx)
  ab717c:	jmp    ab6375 <CGameUI::processIngameInput(void*, float, bool)+0x2f5>
  ab7181:	nopl   0x0(%rax)
  ab7188:	mov    0x38(%rbx),%rax
  ab718c:	mov    0x9b0(%rax,%rdx,8),%rsi
  ab7194:	cmp    $0xfffffffffffffc19,%rsi
  ab719b:	je     ab7360 <CGameUI::processIngameInput(void*, float, bool)+0x12e0>
  ab71a1:	mov    %r15,%rdi
  ab71a4:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  ab71a9:	test   %rax,%rax
  ab71ac:	je     ab67a8 <CGameUI::processIngameInput(void*, float, bool)+0x728>
  ab71b2:	mov    %rax,%rdi
  ab71b5:	call   c9ce50 <CSkill::getName()>
  ab71ba:	lea    0xe0(%rsp),%rdi
  ab71c2:	mov    %rax,%rsi
  ab71c5:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab71ca:	mov    0x38(%rbx),%rdi
  ab71ce:	lea    0xe0(%rsp),%rsi
  ab71d6:	call   837b00 <CCharacter::setLeftSkillByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  ab71db:	lea    0xe0(%rsp),%rdi
  ab71e3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab71e8:	jmp    ab6810 <CGameUI::processIngameInput(void*, float, bool)+0x790>
  ab71ed:	nopl   (%rax)
  ab71f0:	cmp    %r13,0x4f0(%rbx)
  ab71f7:	je     ab7395 <CGameUI::processIngameInput(void*, float, bool)+0x1315>
  ab71fd:	mov    0x508(%rbx),%rax
  ab7204:	mov    0x3408(%rax),%r12
  ab720b:	test   %r12,%r12
  ab720e:	je     ab7626 <CGameUI::processIngameInput(void*, float, bool)+0x15a6>
  ab7214:	mov    0x0(%r13),%rax
  ab7218:	mov    %r13,%rdi
  ab721b:	call   *0x10(%rax)
  ab721e:	mov    0x10(%rax),%rdx
  ab7222:	cmp    %rdx,0x18(%r12)
  ab7227:	je     ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab722d:	mov    0x38(%rbx),%rdx
  ab7231:	mov    0x648(%rdx),%rcx
  ab7238:	mov    0x650(%rdx),%rdx
  ab723f:	sub    %rcx,%rdx
  ab7242:	sar    $0x3,%rdx
  ab7246:	test   %edx,%edx
  ab7248:	je     ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab724e:	xor    %eax,%eax
  ab7250:	test   %rdx,%rdx
  ab7253:	je     ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab7259:	mov    (%rcx),%rax
  ab725c:	jmp    ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab7261:	nopl   0x0(%rax)
  ab7268:	mov    0x1678(%rbx),%esi
  ab726e:	cmp    $0xffffffff,%esi
  ab7271:	je     ab69a5 <CGameUI::processIngameInput(void*, float, bool)+0x925>
  ab7277:	mov    0x38(%rbx),%rax
  ab727b:	mov    0x490(%rax),%rdi
  ab7282:	call   91b340 <CInventory::getEquipmentInSlot(unsigned int)>
  ab7287:	test   %rax,%rax
  ab728a:	mov    %rax,%r15
  ab728d:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7293:	cmpq   $0x0,0xb8(%rbx)
  ab729b:	jne    ab69e0 <CGameUI::processIngameInput(void*, float, bool)+0x960>
  ab72a1:	mov    %rax,%rdi
  ab72a4:	call   acbbe0 <CItem::isUseable()>
  ab72a9:	test   %al,%al
  ab72ab:	je     ab7aa2 <CGameUI::processIngameInput(void*, float, bool)+0x1a22>
  ab72b1:	mov    0x40(%rbx),%rsi
  ab72b5:	mov    %r15,%rdx
  ab72b8:	mov    %rbx,%rdi
  ab72bb:	call   a92320 <CGameUI::useItem(CLevel&, CEquipment*)>
  ab72c0:	mov    0x4d8(%rbx),%rax
  ab72c7:	xor    %ebp,%ebp
  ab72c9:	movq   $0x0,0x1020(%rax)
  ab72d4:	mov    0x4f0(%rbx),%rax
  ab72db:	movq   $0x0,0x3438(%rax)
  ab72e6:	mov    0x4f8(%rbx),%rax
  ab72ed:	movq   $0x0,0xf0(%rax)
  ab72f8:	mov    0x500(%rbx),%rax
  ab72ff:	movq   $0x0,0x190(%rax)
  ab730a:	mov    0x508(%rbx),%rax
  ab7311:	movq   $0x0,0x3408(%rax)
  ab731c:	mov    0x4e8(%rbx),%rax
  ab7323:	movq   $0x0,0x1370(%rax)
  ab732e:	mov    0x4a0(%rbx),%rax
  ab7335:	movq   $0xffffffffffffffff,0x10(%rax)
  ab733d:	mov    0x4a8(%rbx),%rax
  ab7344:	movq   $0xffffffffffffffff,0x10(%rax)
  ab734c:	mov    0x4b0(%rbx),%rax
  ab7353:	movq   $0xffffffffffffffff,0x10(%rax)
  ab735b:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7360:	lea    0xf0(%rsp),%rdi
  ab7368:	mov    $0x14b7d08,%esi
  ab736d:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab7372:	mov    0x38(%rbx),%rdi
  ab7376:	lea    0xf0(%rsp),%rsi
  ab737e:	call   837b00 <CCharacter::setLeftSkillByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  ab7383:	lea    0xf0(%rsp),%rdi
  ab738b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab7390:	jmp    ab6810 <CGameUI::processIngameInput(void*, float, bool)+0x790>
  ab7395:	mov    0x3438(%r13),%r12
  ab739c:	jmp    ab720b <CGameUI::processIngameInput(void*, float, bool)+0x118b>
  ab73a1:	nopl   0x0(%rax)
  ab73a8:	mov    0x558(%rbx),%rdi
  ab73af:	mov    (%rdi),%rax
  ab73b2:	call   *0x48(%rax)
  ab73b5:	jmp    ab6ba3 <CGameUI::processIngameInput(void*, float, bool)+0xb23>
  ab73ba:	nopw   0x0(%rax,%rax,1)
  ab73c0:	mov    0x9c(%rdi),%eax
  ab73c6:	mov    %eax,0x3c(%rsp)
  ab73ca:	jmp    ab64ed <CGameUI::processIngameInput(void*, float, bool)+0x46d>
  ab73cf:	nop
  ab73d0:	mov    0x4d8(%rbx),%rax
  ab73d7:	mov    0x7c(%rax),%eax
  ab73da:	jmp    ab63aa <CGameUI::processIngameInput(void*, float, bool)+0x32a>
  ab73df:	nop
  ab73e0:	mov    0x4d8(%rbx),%rax
  ab73e7:	mov    0x78(%rax),%eax
  ab73ea:	jmp    ab6395 <CGameUI::processIngameInput(void*, float, bool)+0x315>
  ab73ef:	nop
  ab73f0:	mov    0x4e8(%rbx),%rdi
  ab73f7:	mov    0x98(%rdi),%r15d
  ab73fe:	jmp    ab64e2 <CGameUI::processIngameInput(void*, float, bool)+0x462>
  ab7403:	nopl   0x0(%rax,%rax,1)
  ab7408:	mov    0x33fc(%r13),%edx
  ab740f:	mov    %edx,0x3c(%rsp)
  ab7413:	jmp    ab64ae <CGameUI::processIngameInput(void*, float, bool)+0x42e>
  ab7418:	nopl   0x0(%rax,%rax,1)
  ab7420:	mov    0x33f8(%r13),%r15d
  ab7427:	jmp    ab64a3 <CGameUI::processIngameInput(void*, float, bool)+0x423>
  ab742c:	nopl   0x0(%rax)
  ab7430:	mov    0x508(%rbx),%rdi
  ab7437:	mov    0x3400(%rdi),%eax
  ab743d:	mov    %eax,0x58(%rsp)
  ab7441:	jmp    ab6487 <CGameUI::processIngameInput(void*, float, bool)+0x407>
  ab7446:	cs nopw 0x0(%rax,%rax,1)
  ab7450:	mov    0x500(%rbx),%rax
  ab7457:	mov    0x18c(%rax),%eax
  ab745d:	jmp    ab6420 <CGameUI::processIngameInput(void*, float, bool)+0x3a0>
  ab7462:	nopw   0x0(%rax,%rax,1)
  ab7468:	mov    0x500(%rbx),%rax
  ab746f:	mov    0x188(%rax),%eax
  ab7475:	jmp    ab640b <CGameUI::processIngameInput(void*, float, bool)+0x38b>
  ab747a:	nopw   0x0(%rax,%rax,1)
  ab7480:	mov    0x4f8(%rbx),%rax
  ab7487:	mov    0xec(%rax),%eax
  ab748d:	jmp    ab63e5 <CGameUI::processIngameInput(void*, float, bool)+0x365>
  ab7492:	nopw   0x0(%rax,%rax,1)
  ab7498:	mov    0x4f8(%rbx),%rax
  ab749f:	mov    0xe8(%rax),%eax
  ab74a5:	jmp    ab63d0 <CGameUI::processIngameInput(void*, float, bool)+0x350>
  ab74aa:	nopw   0x0(%rax,%rax,1)
  ab74b0:	mov    0x4a0(%rbx),%rcx
  ab74b7:	xor    %r9d,%r9d
  ab74ba:	xor    %r8d,%r8d
  ab74bd:	mov    %r12,%rdx
  ab74c0:	mov    %rax,%rsi
  ab74c3:	mov    %rbx,%rdi
  ab74c6:	call   aa6bf0 <CGameUI::showEquipmentTooltip(CCharacter*, CEquipment*, CEquipmentTooltip*, CEquipmentTooltip*, CEquipmentTooltip*)>
  ab74cb:	cmpq   $0x0,0x38(%rbx)
  ab74d0:	je     ab66f8 <CGameUI::processIngameInput(void*, float, bool)+0x678>
  ab74d6:	mov    $0x8,%esi
  ab74db:	mov    %r12,%rdi
  ab74de:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab74e3:	test   %al,%al
  ab74e5:	je     ab75b6 <CGameUI::processIngameInput(void*, float, bool)+0x1536>
  ab74eb:	movq   $0x0,0x108(%rsp)
  ab74f7:	movq   $0x0,0x100(%rsp)
  ab7503:	lea    0x108(%rsp),%rdx
  ab750b:	mov    0x38(%rbx),%rax
  ab750f:	lea    0x100(%rsp),%rcx
  ab7517:	mov    %r12,%rsi
  ab751a:	mov    0x490(%rax),%rdi
  ab7521:	call   91c2a0 <CInventory::getComparisonItems(CEquipment*, CEquipment**, CEquipment**)>
  ab7526:	mov    0x108(%rsp),%rdx
  ab752e:	xor    %eax,%eax
  ab7530:	test   %rdx,%rdx
  ab7533:	je     ab755a <CGameUI::processIngameInput(void*, float, bool)+0x14da>
  ab7535:	mov    0x4a8(%rbx),%rcx
  ab753c:	mov    0x38(%rbx),%rsi
  ab7540:	xor    %r9d,%r9d
  ab7543:	mov    0x4a0(%rbx),%r8
  ab754a:	mov    %rbx,%rdi
  ab754d:	call   aa6bf0 <CGameUI::showEquipmentTooltip(CCharacter*, CEquipment*, CEquipmentTooltip*, CEquipmentTooltip*, CEquipmentTooltip*)>
  ab7552:	mov    0x108(%rsp),%rax
  ab755a:	mov    0x100(%rsp),%rdx
  ab7562:	test   %rdx,%rdx
  ab7565:	je     ab7599 <CGameUI::processIngameInput(void*, float, bool)+0x1519>
  ab7567:	test   %rax,%rax
  ab756a:	je     ab7755 <CGameUI::processIngameInput(void*, float, bool)+0x16d5>
  ab7570:	mov    0x4b0(%rbx),%rcx
  ab7577:	mov    0x38(%rbx),%rsi
  ab757b:	mov    %rbx,%rdi
  ab757e:	mov    0x4a8(%rbx),%r9
  ab7585:	mov    0x4a0(%rbx),%r8
  ab758c:	call   aa6bf0 <CGameUI::showEquipmentTooltip(CCharacter*, CEquipment*, CEquipmentTooltip*, CEquipmentTooltip*, CEquipmentTooltip*)>
  ab7591:	mov    0x108(%rsp),%rax
  ab7599:	test   %rax,%rax
  ab759c:	je     ab7755 <CGameUI::processIngameInput(void*, float, bool)+0x16d5>
  ab75a2:	cmpq   $0x0,0x100(%rsp)
  ab75ab:	jne    ab6734 <CGameUI::processIngameInput(void*, float, bool)+0x6b4>
  ab75b1:	jmp    ab6716 <CGameUI::processIngameInput(void*, float, bool)+0x696>
  ab75b6:	mov    $0xd,%esi
  ab75bb:	mov    %r12,%rdi
  ab75be:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab75c3:	test   %al,%al
  ab75c5:	jne    ab74eb <CGameUI::processIngameInput(void*, float, bool)+0x146b>
  ab75cb:	mov    $0x27,%esi
  ab75d0:	mov    %r12,%rdi
  ab75d3:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab75d8:	test   %al,%al
  ab75da:	je     ab66f8 <CGameUI::processIngameInput(void*, float, bool)+0x678>
  ab75e0:	jmp    ab74eb <CGameUI::processIngameInput(void*, float, bool)+0x146b>
  ab75e5:	cmpq   $0xffffffffffffffff,0xb0(%rbx)
  ab75ed:	jne    ab684e <CGameUI::processIngameInput(void*, float, bool)+0x7ce>
  ab75f3:	jmp    ab6207 <CGameUI::processIngameInput(void*, float, bool)+0x187>
  ab75f8:	mov    0x4f0(%rbx),%rdi
  ab75ff:	mov    (%rdi),%rax
  ab7602:	call   *0x48(%rax)
  ab7605:	jmp    ab6c96 <CGameUI::processIngameInput(void*, float, bool)+0xc16>
  ab760a:	mov    0x1c8(%rax),%rdi
  ab7611:	mov    0x1648(%rbx),%rsi
  ab7618:	test   %rdi,%rdi
  ab761b:	jne    ab6ab8 <CGameUI::processIngameInput(void*, float, bool)+0xa38>
  ab7621:	jmp    ab60c0 <CGameUI::processIngameInput(void*, float, bool)+0x40>
  ab7626:	mov    0x4e8(%rbx),%rdi
  ab762d:	mov    0x1370(%rdi),%r12
  ab7634:	test   %r12,%r12
  ab7637:	je     ab77c9 <CGameUI::processIngameInput(void*, float, bool)+0x1749>
  ab763d:	mov    (%rdi),%rax
  ab7640:	call   *0x10(%rax)
  ab7643:	jmp    ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab7648:	mov    0xb8(%rbx),%rdi
  ab764f:	mov    $0x67,%esi
  ab7654:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab7659:	test   %al,%al
  ab765b:	je     ab769a <CGameUI::processIngameInput(void*, float, bool)+0x161a>
  ab765d:	mov    %rbx,%rdi
  ab7660:	call   a8f4e0 <CGameUI::returnDraggedItem()>
  ab7665:	lea    0xb8(%rbx),%rdi
  ab766c:	xor    %esi,%esi
  ab766e:	xor    %ebp,%ebp
  ab7670:	call   acbc30 <TSafePointer<CEquipment>::setObject(CEquipment*)>
  ab7675:	lea    0xc8(%rbx),%rdi
  ab767c:	xor    %esi,%esi
  ab767e:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  ab7683:	movl   $0xffffffff,0xd8(%rbx)
  ab768d:	mov    %rbx,%rdi
  ab7690:	call   a83d60 <CGameUI::updateHardwareCursor()>
  ab7695:	jmp    ab6690 <CGameUI::processIngameInput(void*, float, bool)+0x610>
  ab769a:	mov    0x4e8(%rbx),%rdi
  ab76a1:	mov    (%rdi),%rax
  ab76a4:	call   *0x10(%rax)
  ab76a7:	cmp    0xc8(%rbx),%rax
  ab76ae:	je     ab7835 <CGameUI::processIngameInput(void*, float, bool)+0x17b5>
  ab76b4:	mov    0x38(%rbx),%rdi
  ab76b8:	mov    $0x1,%esi
  ab76bd:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab76c2:	movq   %xmm0,0x8(%rsp)
  ab76c8:	mov    0x8(%rsp),%rax
  ab76cd:	lea    0x80(%rsp),%rdx
  ab76d5:	movss  %xmm1,0x68(%rsp)
  ab76db:	mov    $0x1,%ecx
  ab76e0:	mov    %rax,0x60(%rsp)
  ab76e5:	mov    %rax,0x80(%rsp)
  ab76ed:	mov    0x68(%rsp),%eax
  ab76f1:	mov    %eax,0x88(%rsp)
  ab76f8:	mov    0xb8(%rbx),%rsi
  ab76ff:	mov    0x40(%rbx),%rdi
  ab7703:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7708:	mov    0xb8(%rbx),%rax
  ab770f:	mov    0x498(%rbx),%rdi
  ab7716:	mov    0x2c8(%rax),%rsi
  ab771d:	cmp    0xb0(%rsi),%rdi
  ab7724:	jne    ab7665 <CGameUI::processIngameInput(void*, float, bool)+0x15e5>
  ab772a:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab772f:	jmp    ab7665 <CGameUI::processIngameInput(void*, float, bool)+0x15e5>
  ab7734:	mov    %rbx,%rdi
  ab7737:	call   a8e440 <CGameUI::unPause()>
  ab773c:	mov    %rbx,%rdi
  ab773f:	call   a82c00 <CGameUI::eitherCoveredPartial()>
  ab7744:	test   %al,%al
  ab7746:	je     ab777c <CGameUI::processIngameInput(void*, float, bool)+0x16fc>
  ab7748:	mov    %rbx,%rdi
  ab774b:	call   a8e0d0 <CGameUI::closeAll()>
  ab7750:	jmp    ab6966 <CGameUI::processIngameInput(void*, float, bool)+0x8e6>
  ab7755:	mov    0x4a8(%rbx),%rax
  ab775c:	mov    0x20(%rax),%rsi
  ab7760:	cmpq   $0x0,0xb0(%rsi)
  ab7768:	je     ab75a2 <CGameUI::processIngameInput(void*, float, bool)+0x1522>
  ab776e:	mov    0x18(%rax),%rdi
  ab7772:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab7777:	jmp    ab75a2 <CGameUI::processIngameInput(void*, float, bool)+0x1522>
  ab777c:	mov    %rbx,%rdi
  ab777f:	call   a82a80 <CGameUI::modalDialogOpenPartial()>
  ab7784:	test   %al,%al
  ab7786:	jne    ab6966 <CGameUI::processIngameInput(void*, float, bool)+0x8e6>
  ab778c:	mov    %rbx,%rdi
  ab778f:	call   a8e0d0 <CGameUI::closeAll()>
  ab7794:	mov    0x4d8(%rbx),%rdi
  ab779b:	mov    $0x1,%esi
  ab77a0:	mov    (%rdi),%rax
  ab77a3:	call   *0x40(%rax)
  ab77a6:	mov    0x4e0(%rbx),%rdi
  ab77ad:	mov    $0x1,%esi
  ab77b2:	mov    (%rdi),%rax
  ab77b5:	call   *0x40(%rax)
  ab77b8:	mov    0x138(%rbx),%rdi
  ab77bf:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  ab77c4:	jmp    ab6966 <CGameUI::processIngameInput(void*, float, bool)+0x8e6>
  ab77c9:	mov    0x4f8(%rbx),%rax
  ab77d0:	mov    0xf0(%rax),%r12
  ab77d7:	test   %r12,%r12
  ab77da:	je     ab7adc <CGameUI::processIngameInput(void*, float, bool)+0x1a5c>
  ab77e0:	mov    0x60(%rax),%rax
  ab77e4:	jmp    ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab77e9:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab77ee:	xchg   %ax,%ax
  ab77f0:	jmp    ab6318 <CGameUI::processIngameInput(void*, float, bool)+0x298>
  ab77f5:	mov    0x48(%rsp),%rax
  ab77fa:	mov    %r15,%rsi
  ab77fd:	mov    0x490(%rax),%rdi
  ab7804:	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  ab7809:	test   %al,%al
  ab780b:	je     ab789a <CGameUI::processIngameInput(void*, float, bool)+0x181a>
  ab7811:	mov    0x48(%rsp),%rdi
  ab7816:	mov    $0x1,%esi
  ab781b:	call   80fa90 <CCharacter::setRenderBehind(bool)>
  ab7820:	mov    0x38(%rbx),%rax
  ab7824:	mov    %r15,%rdi
  ab7827:	mov    0x58(%rax),%rsi
  ab782b:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7830:	jmp    ab70cb <CGameUI::processIngameInput(void*, float, bool)+0x104b>
  ab7835:	mov    0x4e8(%rbx),%rdi
  ab783c:	mov    (%rdi),%rax
  ab783f:	call   *0x10(%rax)
  ab7842:	mov    $0x1,%esi
  ab7847:	mov    %rax,%rdi
  ab784a:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab784f:	movq   %xmm0,0x8(%rsp)
  ab7855:	mov    0x8(%rsp),%rax
  ab785a:	lea    0x90(%rsp),%rdx
  ab7862:	movss  %xmm1,0x68(%rsp)
  ab7868:	mov    $0x1,%ecx
  ab786d:	mov    %rax,0x60(%rsp)
  ab7872:	mov    %rax,0x90(%rsp)
  ab787a:	mov    0x68(%rsp),%eax
  ab787e:	mov    %eax,0x98(%rsp)
  ab7885:	mov    0xb8(%rbx),%rsi
  ab788c:	mov    0x40(%rbx),%rdi
  ab7890:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7895:	jmp    ab7708 <CGameUI::processIngameInput(void*, float, bool)+0x1688>
  ab789a:	mov    (%r15),%rax
  ab789d:	mov    $0x1,%edx
  ab78a2:	mov    0x48(%rsp),%rsi
  ab78a7:	mov    %r15,%rdi
  ab78aa:	call   *0x2f8(%rax)
  ab78b0:	test   %al,%al
  ab78b2:	je     ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab78b8:	mov    0x48(%rsp),%rax
  ab78bd:	movq   $0x0,0x108(%rsp)
  ab78c9:	lea    0x100(%rsp),%rcx
  ab78d1:	movq   $0x0,0x100(%rsp)
  ab78dd:	lea    0x108(%rsp),%rdx
  ab78e5:	mov    %r15,%rsi
  ab78e8:	mov    0x490(%rax),%rdi
  ab78ef:	call   91c2a0 <CInventory::getComparisonItems(CEquipment*, CEquipment**, CEquipment**)>
  ab78f4:	mov    $0xa,%esi
  ab78f9:	mov    %r15,%rdi
  ab78fc:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab7901:	test   %al,%al
  ab7903:	je     ab7923 <CGameUI::processIngameInput(void*, float, bool)+0x18a3>
  ab7905:	mov    0x100(%rsp),%rsi
  ab790d:	test   %rsi,%rsi
  ab7910:	je     ab7923 <CGameUI::processIngameInput(void*, float, bool)+0x18a3>
  ab7912:	mov    0x48(%rsp),%rdx
  ab7917:	mov    0x490(%rdx),%rdi
  ab791e:	call   924810 <CInventory::removeEquipment(CEquipment*)>
  ab7923:	mov    0x108(%rsp),%rsi
  ab792b:	test   %rsi,%rsi
  ab792e:	je     ab7999 <CGameUI::processIngameInput(void*, float, bool)+0x1919>
  ab7930:	mov    0x48(%rsp),%rax
  ab7935:	mov    0x490(%rax),%rdi
  ab793c:	call   924810 <CInventory::removeEquipment(CEquipment*)>
  ab7941:	mov    0x48(%rsp),%rdx
  ab7946:	mov    %r15,%rsi
  ab7949:	mov    0x490(%rdx),%rdi
  ab7950:	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  ab7955:	test   %al,%al
  ab7957:	jne    ab7f9e <CGameUI::processIngameInput(void*, float, bool)+0x1f1e>
  ab795d:	mov    0x48(%rsp),%rax
  ab7962:	mov    0x108(%rsp),%rsi
  ab796a:	mov    $0x1,%edx
  ab796f:	mov    0x490(%rax),%rdi
  ab7976:	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  ab797b:	test   %rax,%rax
  ab797e:	je     ab7f32 <CGameUI::processIngameInput(void*, float, bool)+0x1eb2>
  ab7984:	mov    0x38(%rbx),%rax
  ab7988:	mov    0x108(%rsp),%rdi
  ab7990:	mov    0x58(%rax),%rsi
  ab7994:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7999:	mov    $0xa,%esi
  ab799e:	mov    %r15,%rdi
  ab79a1:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab79a6:	test   %al,%al
  ab79a8:	je     ab79ec <CGameUI::processIngameInput(void*, float, bool)+0x196c>
  ab79aa:	mov    0x100(%rsp),%rsi
  ab79b2:	test   %rsi,%rsi
  ab79b5:	je     ab79ec <CGameUI::processIngameInput(void*, float, bool)+0x196c>
  ab79b7:	mov    0x48(%rsp),%rdx
  ab79bc:	mov    0x490(%rdx),%rdi
  ab79c3:	mov    $0x1,%edx
  ab79c8:	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  ab79cd:	test   %rax,%rax
  ab79d0:	je     ab7ea5 <CGameUI::processIngameInput(void*, float, bool)+0x1e25>
  ab79d6:	mov    0x48(%rsp),%rax
  ab79db:	mov    0x100(%rsp),%rdi
  ab79e3:	mov    0x58(%rax),%rsi
  ab79e7:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab79ec:	mov    0x4d8(%rbx),%rax
  ab79f3:	movq   $0x0,0x1020(%rax)
  ab79fe:	mov    0x4f0(%rbx),%rax
  ab7a05:	movq   $0x0,0x3438(%rax)
  ab7a10:	mov    0x4f8(%rbx),%rax
  ab7a17:	movq   $0x0,0xf0(%rax)
  ab7a22:	mov    0x500(%rbx),%rax
  ab7a29:	movq   $0x0,0x190(%rax)
  ab7a34:	mov    0x508(%rbx),%rax
  ab7a3b:	movq   $0x0,0x3408(%rax)
  ab7a46:	mov    0x4e8(%rbx),%rax
  ab7a4d:	movq   $0x0,0x1370(%rax)
  ab7a58:	mov    0x4a0(%rbx),%rax
  ab7a5f:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7a67:	mov    0x4a8(%rbx),%rax
  ab7a6e:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7a76:	mov    0x4b0(%rbx),%rax
  ab7a7d:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7a85:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab7a8a:	xorps  %xmm1,%xmm1
  ab7a8d:	mov    %rax,%rdi
  ab7a90:	movss  0x4ecd64(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  ab7a98:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  ab7a9d:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7aa2:	mov    0x38(%rbx),%rax
  ab7aa6:	mov    %r15,%rsi
  ab7aa9:	mov    0x490(%rax),%rdi
  ab7ab0:	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  ab7ab5:	test   %al,%al
  ab7ab7:	je     ab7aff <CGameUI::processIngameInput(void*, float, bool)+0x1a7f>
  ab7ab9:	mov    0x38(%rbx),%rdi
  ab7abd:	mov    $0x1,%esi
  ab7ac2:	call   80fa90 <CCharacter::setRenderBehind(bool)>
  ab7ac7:	mov    0x38(%rbx),%rax
  ab7acb:	mov    %r15,%rdi
  ab7ace:	mov    0x58(%rax),%rsi
  ab7ad2:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7ad7:	jmp    ab72c0 <CGameUI::processIngameInput(void*, float, bool)+0x1240>
  ab7adc:	mov    0x500(%rbx),%rax
  ab7ae3:	mov    0x190(%rax),%r12
  ab7aea:	test   %r12,%r12
  ab7aed:	je     ab7fda <CGameUI::processIngameInput(void*, float, bool)+0x1f5a>
  ab7af3:	mov    0x90(%rax),%rax
  ab7afa:	jmp    ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab7aff:	mov    (%r15),%rax
  ab7b02:	mov    0x38(%rbx),%rsi
  ab7b06:	mov    $0x1,%edx
  ab7b0b:	mov    %r15,%rdi
  ab7b0e:	call   *0x2f8(%rax)
  ab7b14:	test   %al,%al
  ab7b16:	je     ab7de9 <CGameUI::processIngameInput(void*, float, bool)+0x1d69>
  ab7b1c:	movq   $0x0,0x100(%rsp)
  ab7b28:	movq   $0x0,0x108(%rsp)
  ab7b34:	lea    0x108(%rsp),%rcx
  ab7b3c:	mov    0x38(%rbx),%rax
  ab7b40:	lea    0x100(%rsp),%rdx
  ab7b48:	mov    %r15,%rsi
  ab7b4b:	mov    0x490(%rax),%rdi
  ab7b52:	call   91c2a0 <CInventory::getComparisonItems(CEquipment*, CEquipment**, CEquipment**)>
  ab7b57:	mov    $0xa,%esi
  ab7b5c:	mov    %r15,%rdi
  ab7b5f:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab7b64:	test   %al,%al
  ab7b66:	je     ab7b85 <CGameUI::processIngameInput(void*, float, bool)+0x1b05>
  ab7b68:	mov    0x108(%rsp),%rsi
  ab7b70:	test   %rsi,%rsi
  ab7b73:	je     ab7b85 <CGameUI::processIngameInput(void*, float, bool)+0x1b05>
  ab7b75:	mov    0x38(%rbx),%rax
  ab7b79:	mov    0x490(%rax),%rdi
  ab7b80:	call   924810 <CInventory::removeEquipment(CEquipment*)>
  ab7b85:	mov    0x100(%rsp),%rsi
  ab7b8d:	xor    %ebp,%ebp
  ab7b8f:	test   %rsi,%rsi
  ab7b92:	je     ab7c1d <CGameUI::processIngameInput(void*, float, bool)+0x1b9d>
  ab7b98:	mov    0x38(%rbx),%rax
  ab7b9c:	mov    0x490(%rax),%rdi
  ab7ba3:	call   924810 <CInventory::removeEquipment(CEquipment*)>
  ab7ba8:	mov    0x38(%rbx),%rax
  ab7bac:	mov    %r15,%rsi
  ab7baf:	mov    0x490(%rax),%rdi
  ab7bb6:	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  ab7bbb:	test   %al,%al
  ab7bbd:	je     ab7be2 <CGameUI::processIngameInput(void*, float, bool)+0x1b62>
  ab7bbf:	mov    0x38(%rbx),%rdi
  ab7bc3:	mov    $0x1,%esi
  ab7bc8:	mov    $0x1,%ebp
  ab7bcd:	call   80fa90 <CCharacter::setRenderBehind(bool)>
  ab7bd2:	mov    0x38(%rbx),%rax
  ab7bd6:	mov    %r15,%rdi
  ab7bd9:	mov    0x58(%rax),%rsi
  ab7bdd:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7be2:	mov    0x38(%rbx),%rax
  ab7be6:	mov    0x100(%rsp),%rsi
  ab7bee:	mov    $0x1,%edx
  ab7bf3:	mov    0x490(%rax),%rdi
  ab7bfa:	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  ab7bff:	test   %rax,%rax
  ab7c02:	je     ab7e3a <CGameUI::processIngameInput(void*, float, bool)+0x1dba>
  ab7c08:	mov    0x38(%rbx),%rax
  ab7c0c:	mov    0x100(%rsp),%rdi
  ab7c14:	mov    0x58(%rax),%rsi
  ab7c18:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7c1d:	mov    $0xa,%esi
  ab7c22:	mov    %r15,%rdi
  ab7c25:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  ab7c2a:	test   %al,%al
  ab7c2c:	je     ab7c6e <CGameUI::processIngameInput(void*, float, bool)+0x1bee>
  ab7c2e:	mov    0x108(%rsp),%rsi
  ab7c36:	test   %rsi,%rsi
  ab7c39:	je     ab7c6e <CGameUI::processIngameInput(void*, float, bool)+0x1bee>
  ab7c3b:	mov    0x38(%rbx),%rax
  ab7c3f:	mov    $0x1,%edx
  ab7c44:	mov    0x490(%rax),%rdi
  ab7c4b:	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  ab7c50:	test   %rax,%rax
  ab7c53:	je     ab7d2f <CGameUI::processIngameInput(void*, float, bool)+0x1caf>
  ab7c59:	mov    0x38(%rbx),%rax
  ab7c5d:	mov    0x108(%rsp),%rdi
  ab7c65:	mov    0x58(%rax),%rsi
  ab7c69:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7c6e:	test   %bpl,%bpl
  ab7c71:	je     ab7d9a <CGameUI::processIngameInput(void*, float, bool)+0x1d1a>
  ab7c77:	mov    0x4d8(%rbx),%rax
  ab7c7e:	xor    %ebp,%ebp
  ab7c80:	movq   $0x0,0x1020(%rax)
  ab7c8b:	mov    0x4f0(%rbx),%rax
  ab7c92:	movq   $0x0,0x3438(%rax)
  ab7c9d:	mov    0x4f8(%rbx),%rax
  ab7ca4:	movq   $0x0,0xf0(%rax)
  ab7caf:	mov    0x500(%rbx),%rax
  ab7cb6:	movq   $0x0,0x190(%rax)
  ab7cc1:	mov    0x508(%rbx),%rax
  ab7cc8:	movq   $0x0,0x3408(%rax)
  ab7cd3:	mov    0x4e8(%rbx),%rax
  ab7cda:	movq   $0x0,0x1370(%rax)
  ab7ce5:	mov    0x4a0(%rbx),%rax
  ab7cec:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7cf4:	mov    0x4a8(%rbx),%rax
  ab7cfb:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7d03:	mov    0x4b0(%rbx),%rax
  ab7d0a:	movq   $0xffffffffffffffff,0x10(%rax)
  ab7d12:	call   555678 <CEGUI::System::getSingleton()@plt>
  ab7d17:	xorps  %xmm1,%xmm1
  ab7d1a:	mov    %rax,%rdi
  ab7d1d:	movss  0x4ecad7(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  ab7d25:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  ab7d2a:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7d2f:	mov    0x38(%rbx),%rdi
  ab7d33:	mov    $0x1,%esi
  ab7d38:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab7d3d:	movq   %xmm0,0x8(%rsp)
  ab7d43:	mov    0x8(%rsp),%rax
  ab7d48:	mov    0x108(%rsp),%rsi
  ab7d50:	movss  %xmm1,0x68(%rsp)
  ab7d56:	lea    0xa0(%rsp),%rdx
  ab7d5e:	mov    $0x1,%ecx
  ab7d63:	mov    %rax,0x60(%rsp)
  ab7d68:	mov    %rax,0xa0(%rsp)
  ab7d70:	mov    0x68(%rsp),%eax
  ab7d74:	mov    %eax,0xa8(%rsp)
  ab7d7b:	mov    0x40(%rbx),%rdi
  ab7d7f:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7d84:	mov    0x108(%rsp),%rdi
  ab7d8c:	mov    (%rdi),%rax
  ab7d8f:	call   *0x360(%rax)
  ab7d95:	jmp    ab7c6e <CGameUI::processIngameInput(void*, float, bool)+0x1bee>
  ab7d9a:	mov    0x38(%rbx),%rax
  ab7d9e:	xorps  %xmm1,%xmm1
  ab7da1:	mov    0x16a8(%rbx),%rdi
  ab7da8:	xor    %ecx,%ecx
  ab7daa:	mov    $0x18,%esi
  ab7daf:	mov    0x58(%rax),%rdx
  ab7db3:	movaps %xmm1,%xmm0
  ab7db6:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  ab7dbb:	mov    0x38(%rbx),%rax
  ab7dbf:	mov    0x298(%rax),%rdi
  ab7dc6:	test   %rdi,%rdi
  ab7dc9:	je     ab7c77 <CGameUI::processIngameInput(void*, float, bool)+0x1bf7>
  ab7dcf:	xorps  %xmm0,%xmm0
  ab7dd2:	mov    $0x31,%esi
  ab7dd7:	movss  0x4eca2d(%rip),%xmm1        # fa480c <vtable for Ogre::FrameListener+0x4c>
  ab7ddf:	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  ab7de4:	jmp    ab7c77 <CGameUI::processIngameInput(void*, float, bool)+0x1bf7>
  ab7de9:	mov    0x38(%rbx),%rax
  ab7ded:	xorps  %xmm1,%xmm1
  ab7df0:	mov    0x16a8(%rbx),%rdi
  ab7df7:	xor    %ecx,%ecx
  ab7df9:	mov    $0x18,%esi
  ab7dfe:	mov    0x58(%rax),%rdx
  ab7e02:	movaps %xmm1,%xmm0
  ab7e05:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  ab7e0a:	mov    0x38(%rbx),%rax
  ab7e0e:	mov    0x298(%rax),%rdi
  ab7e15:	test   %rdi,%rdi
  ab7e18:	je     ab69e0 <CGameUI::processIngameInput(void*, float, bool)+0x960>
  ab7e1e:	xorps  %xmm0,%xmm0
  ab7e21:	mov    $0x31,%esi
  ab7e26:	movss  0x4ec9de(%rip),%xmm1        # fa480c <vtable for Ogre::FrameListener+0x4c>
  ab7e2e:	xor    %ebp,%ebp
  ab7e30:	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  ab7e35:	jmp    ab658e <CGameUI::processIngameInput(void*, float, bool)+0x50e>
  ab7e3a:	mov    0x38(%rbx),%rdi
  ab7e3e:	mov    $0x1,%esi
  ab7e43:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab7e48:	movq   %xmm0,0x8(%rsp)
  ab7e4e:	mov    0x8(%rsp),%rax
  ab7e53:	mov    0x100(%rsp),%rsi
  ab7e5b:	movss  %xmm1,0x68(%rsp)
  ab7e61:	lea    0xb0(%rsp),%rdx
  ab7e69:	mov    $0x1,%ecx
  ab7e6e:	mov    %rax,0x60(%rsp)
  ab7e73:	mov    %rax,0xb0(%rsp)
  ab7e7b:	mov    0x68(%rsp),%eax
  ab7e7f:	mov    %eax,0xb8(%rsp)
  ab7e86:	mov    0x40(%rbx),%rdi
  ab7e8a:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7e8f:	mov    0x100(%rsp),%rdi
  ab7e97:	mov    (%rdi),%rax
  ab7e9a:	call   *0x360(%rax)
  ab7ea0:	jmp    ab7c1d <CGameUI::processIngameInput(void*, float, bool)+0x1b9d>
  ab7ea5:	mov    0x48(%rsp),%rdi
  ab7eaa:	mov    $0x1,%esi
  ab7eaf:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab7eb4:	movq   %xmm0,0x8(%rsp)
  ab7eba:	mov    0x8(%rsp),%rax
  ab7ebf:	mov    0x100(%rsp),%rsi
  ab7ec7:	movss  %xmm1,0x68(%rsp)
  ab7ecd:	lea    0xc0(%rsp),%rdx
  ab7ed5:	mov    $0x1,%ecx
  ab7eda:	mov    %rax,0x60(%rsp)
  ab7edf:	mov    %rax,0xc0(%rsp)
  ab7ee7:	mov    0x68(%rsp),%eax
  ab7eeb:	mov    %eax,0xc8(%rsp)
  ab7ef2:	mov    0x40(%rbx),%rdi
  ab7ef6:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7efb:	mov    0x100(%rsp),%rdi
  ab7f03:	mov    (%rdi),%rax
  ab7f06:	call   *0x360(%rax)
  ab7f0c:	jmp    ab79ec <CGameUI::processIngameInput(void*, float, bool)+0x196c>
  ab7f11:	lea    0xf0(%rsp),%rdi
  ab7f19:	mov    %rax,%rbx
  ab7f1c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab7f21:	mov    %rbx,%rdi
  ab7f24:	call   554498 <_Unwind_Resume@plt>
  ab7f29:	mov    %rax,%rbx
  ab7f2c:	jmp    ab7f21 <CGameUI::processIngameInput(void*, float, bool)+0x1ea1>
  ab7f2e:	xchg   %ax,%ax
  ab7f30:	jmp    ab7f29 <CGameUI::processIngameInput(void*, float, bool)+0x1ea9>
  ab7f32:	mov    0x48(%rsp),%rdi
  ab7f37:	mov    $0x1,%esi
  ab7f3c:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab7f41:	movq   %xmm0,0x8(%rsp)
  ab7f47:	mov    0x8(%rsp),%rax
  ab7f4c:	mov    0x108(%rsp),%rsi
  ab7f54:	movss  %xmm1,0x68(%rsp)
  ab7f5a:	lea    0xd0(%rsp),%rdx
  ab7f62:	mov    $0x1,%ecx
  ab7f67:	mov    %rax,0x60(%rsp)
  ab7f6c:	mov    %rax,0xd0(%rsp)
  ab7f74:	mov    0x68(%rsp),%eax
  ab7f78:	mov    %eax,0xd8(%rsp)
  ab7f7f:	mov    0x40(%rbx),%rdi
  ab7f83:	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  ab7f88:	mov    0x108(%rsp),%rdi
  ab7f90:	mov    (%rdi),%rax
  ab7f93:	call   *0x360(%rax)
  ab7f99:	jmp    ab7999 <CGameUI::processIngameInput(void*, float, bool)+0x1919>
  ab7f9e:	mov    0x48(%rsp),%rdi
  ab7fa3:	mov    $0x1,%esi
  ab7fa8:	call   80fa90 <CCharacter::setRenderBehind(bool)>
  ab7fad:	mov    0x38(%rbx),%rax
  ab7fb1:	mov    %r15,%rdi
  ab7fb4:	mov    0x58(%rax),%rsi
  ab7fb8:	call   86eb70 <CEquipment::playDropSound(Ogre::SceneNode*)>
  ab7fbd:	jmp    ab795d <CGameUI::processIngameInput(void*, float, bool)+0x18dd>
  ab7fc2:	lea    0xe0(%rsp),%rdi
  ab7fca:	mov    %rax,%rbx
  ab7fcd:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab7fd2:	mov    %rbx,%rdi
  ab7fd5:	call   554498 <_Unwind_Resume@plt>
  ab7fda:	mov    0x568(%rbx),%rax
  ab7fe1:	mov    0x170(%rax),%r12
  ab7fe8:	test   %r12,%r12
  ab7feb:	jne    ab66c8 <CGameUI::processIngameInput(void*, float, bool)+0x648>
  ab7ff1:	mov    0x538(%rbx),%rax
  ab7ff8:	mov    0x1e0(%rax),%r12
  ab7fff:	test   %r12,%r12
  ab8002:	jne    ab66c8 <CGameUI::processIngameInput(void*, float, bool)+0x648>
  ab8008:	cmpb   $0x0,0x1641(%rbx)
  ab800f:	je     ab8032 <CGameUI::processIngameInput(void*, float, bool)+0x1fb2>
  ab8011:	mov    0x38(%rbx),%rax
  ab8015:	test   %rax,%rax
  ab8018:	je     ab8032 <CGameUI::processIngameInput(void*, float, bool)+0x1fb2>
  ab801a:	mov    0x4c0(%rbx),%rdx
  ab8021:	mov    0x348(%rdx),%rdx
  ab8028:	cmpq   $0x0,0xb0(%rdx)
  ab8030:	je     ab809a <CGameUI::processIngameInput(void*, float, bool)+0x201a>
  ab8032:	cmpb   $0x0,0x1642(%rbx)
  ab8039:	je     ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
  ab803f:	mov    0x38(%rbx),%rax
  ab8043:	test   %rax,%rax
  ab8046:	je     ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
  ab804c:	mov    0x4c0(%rbx),%rdx
  ab8053:	mov    0x348(%rdx),%rdx
  ab805a:	cmpq   $0x0,0xb0(%rdx)
  ab8062:	je     ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
  ab8068:	mov    0x1658(%rbx),%rsi
  ab806f:	mov    0x490(%rax),%rdi
  ab8076:	call   91b680 <CInventory::getEquipmentOfGuid(long long)>
  ab807b:	test   %rax,%rax
  ab807e:	je     ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
  ab8084:	mov    0x10(%rax),%r12
  ab8088:	mov    0x38(%rbx),%rax
  ab808c:	test   %r12,%r12
  ab808f:	je     ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
  ab8095:	jmp    ab66cc <CGameUI::processIngameInput(void*, float, bool)+0x64c>
  ab809a:	mov    0x1650(%rbx),%rsi
  ab80a1:	mov    0x490(%rax),%rdi
  ab80a8:	call   91b680 <CInventory::getEquipmentOfGuid(long long)>
  ab80ad:	test   %rax,%rax
  ab80b0:	jne    ab8084 <CGameUI::processIngameInput(void*, float, bool)+0x2004>
  ab80b2:	jmp    ab66da <CGameUI::processIngameInput(void*, float, bool)+0x65a>
