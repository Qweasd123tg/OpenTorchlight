
/mnt/data/ot-original-inputs/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000b6a220 <CMerchantMenu::setOpen(bool)>:
  b6a220:	mov    %rbx,-0x18(%rsp)
  b6a225:	mov    %rbp,-0x10(%rsp)
  b6a22a:	mov    %rdi,%rbx
  b6a22d:	mov    %r12,-0x8(%rsp)
  b6a232:	sub    $0x78,%rsp
  b6a236:	cmpb   $0x0,0x60(%rdi)
  b6a23a:	mov    %esi,%ebp
  b6a23c:	je     b6a260 <CMerchantMenu::setOpen(bool)+0x40>
  b6a23e:	test   %sil,%sil
  b6a241:	je     b6a4d8 <CMerchantMenu::setOpen(bool)+0x2b8>
  b6a247:	mov    (%rbx),%rax
  b6a24a:	mov    %bpl,0x60(%rbx)
  b6a24e:	mov    %rbx,%rdi
  b6a251:	call   *0x48(%rax)
  b6a254:	jmp    b6a269 <CMerchantMenu::setOpen(bool)+0x49>
  b6a256:	cs nopw 0x0(%rax,%rax,1)
  b6a260:	test   %sil,%sil
  b6a263:	jne    b6a280 <CMerchantMenu::setOpen(bool)+0x60>
  b6a265:	movb   $0x0,0x60(%rdi)
  b6a269:	mov    0x60(%rsp),%rbx
  b6a26e:	mov    0x68(%rsp),%rbp
  b6a273:	mov    0x70(%rsp),%r12
  b6a278:	add    $0x78,%rsp
  b6a27c:	ret
  b6a27d:	nopl   (%rax)
  b6a280:	mov    0x68(%rdi),%rdi
  b6a284:	mov    0x9a11da(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  b6a28a:	lea    0x50(%rsp),%r12
  b6a28f:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  b6a294:	mov    0x68(%rbx),%rdi
  b6a298:	mov    0x9a11ca(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  b6a29e:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  b6a2a3:	xorps  %xmm1,%xmm1
  b6a2a6:	mov    0xa8(%rbx),%rdi
  b6a2ad:	xor    %edx,%edx
  b6a2af:	xor    %ecx,%ecx
  b6a2b1:	mov    $0x16,%esi
  b6a2b6:	movaps %xmm1,%xmm0
  b6a2b9:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  b6a2be:	mov    0x90(%rbx),%rdi
  b6a2c5:	mov    $0x1,%esi
  b6a2ca:	mov    (%rdi),%rax
  b6a2cd:	call   *0x50(%rax)
  b6a2d0:	lea    0x5f(%rsp),%rdx
  b6a2d5:	mov    $0xfe6008,%esi
  b6a2da:	mov    %r12,%rdi
  b6a2dd:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b6a2e2:	mov    0x90(%rbx),%rdi
  b6a2e9:	mov    %r12,%rsi
  b6a2ec:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  b6a2f1:	mov    0x50(%rsp),%rdi
  b6a2f6:	sub    $0x18,%rdi
  b6a2fa:	cmp    $0x1423a20,%rdi
  b6a301:	jne    b6a699 <CMerchantMenu::setOpen(bool)+0x479>
  b6a307:	test   %al,%al
  b6a309:	je     b6a578 <CMerchantMenu::setOpen(bool)+0x358>
  b6a30f:	lea    0x40(%rsp),%r12
  b6a314:	lea    0x5e(%rsp),%rdx
  b6a319:	mov    $0xfe600e,%esi
  b6a31e:	mov    %r12,%rdi
  b6a321:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b6a326:	mov    0x90(%rbx),%rdi
  b6a32d:	movss  0x43e42b(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b6a335:	movss  0x43a4e7(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b6a33d:	xor    %edx,%edx
  b6a33f:	movss  0x43a4c5(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b6a347:	mov    %r12,%rsi
  b6a34a:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  b6a34f:	mov    %r12,%rdi
  b6a352:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b6a357:	lea    0x20(%rsp),%r12
  b6a35c:	lea    0x5c(%rsp),%rdx
  b6a361:	mov    $0xfc993a,%esi
  b6a366:	mov    %r12,%rdi
  b6a369:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b6a36e:	mov    0x90(%rbx),%rdi
  b6a375:	movss  0x43a47f(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  b6a37d:	movss  0x43a487(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b6a385:	mov    $0x1,%edx
  b6a38a:	mov    %r12,%rsi
  b6a38d:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  b6a392:	mov    0x20(%rsp),%rdi
  b6a397:	mov    $0x1423a20,%eax
  b6a39c:	sub    $0x18,%rdi
  b6a3a0:	cmp    %rdi,%rax
  b6a3a3:	jne    b6a6cf <CMerchantMenu::setOpen(bool)+0x4af>
  b6a3a9:	mov    0x20(%rbx),%rsi
  b6a3ad:	mov    0x18(%rbx),%rdi
  b6a3b1:	call   5561f8 <CEGUI::Window::addChildWindow(CEGUI::Window*)@plt>
  b6a3b6:	mov    0x20(%rbx),%rdi
  b6a3ba:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  b6a3bf:	mov    0x33e0(%rbx),%rdi
  b6a3c6:	mov    $0x1,%esi
  b6a3cb:	movl   $0x0,0x3454(%rbx)
  b6a3d5:	movl   $0x0,0x3458(%rbx)
  b6a3df:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a3e4:	mov    0x33e8(%rbx),%rdi
  b6a3eb:	xor    %esi,%esi
  b6a3ed:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a3f2:	mov    0x33f0(%rbx),%rdi
  b6a3f9:	xor    %esi,%esi
  b6a3fb:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a400:	mov    0x33c8(%rbx),%rdi
  b6a407:	mov    $0x1,%esi
  b6a40c:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a411:	mov    0x33d0(%rbx),%rdi
  b6a418:	xor    %esi,%esi
  b6a41a:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a41f:	mov    0x33d8(%rbx),%rdi
  b6a426:	xor    %esi,%esi
  b6a428:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a42d:	mov    0x50(%rbx),%rdi
  b6a431:	call   8347c0 <CCharacter::getDefaultMerchantTab()>
  b6a436:	cmp    $0x1,%eax
  b6a439:	je     b6a5c0 <CMerchantMenu::setOpen(bool)+0x3a0>
  b6a43f:	cmp    $0x2,%eax
  b6a442:	je     b6a630 <CMerchantMenu::setOpen(bool)+0x410>
  b6a448:	mov    0x3420(%rbx),%rdi
  b6a44f:	mov    $0x1,%esi
  b6a454:	movl   $0x0,0x3454(%rbx)
  b6a45e:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a463:	mov    0x3410(%rbx),%rdi
  b6a46a:	xor    %esi,%esi
  b6a46c:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a471:	mov    0x3418(%rbx),%rdi
  b6a478:	xor    %esi,%esi
  b6a47a:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a47f:	mov    0x3408(%rbx),%rdi
  b6a486:	mov    $0x1,%esi
  b6a48b:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a490:	mov    0x33f8(%rbx),%rdi
  b6a497:	xor    %esi,%esi
  b6a499:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a49e:	mov    0x3400(%rbx),%rdi
  b6a4a5:	xor    %esi,%esi
  b6a4a7:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a4ac:	mov    0x50(%rbx),%rdi
  b6a4b0:	mov    $0x7f,%esi
  b6a4b5:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  b6a4ba:	test   %al,%al
  b6a4bc:	je     b6a560 <CMerchantMenu::setOpen(bool)+0x340>
  b6a4c2:	mov    0x70(%rbx),%rdi
  b6a4c6:	mov    $0xc,%esi
  b6a4cb:	call   a8f450 <CGameUI::queueTip(EContextTip)>
  b6a4d0:	jmp    b6a247 <CMerchantMenu::setOpen(bool)+0x27>
  b6a4d5:	nopl   (%rax)
  b6a4d8:	xorps  %xmm1,%xmm1
  b6a4db:	mov    0xa8(%rdi),%rdi
  b6a4e2:	xor    %edx,%edx
  b6a4e4:	mov    $0x42,%esi
  b6a4e9:	xor    %ecx,%ecx
  b6a4eb:	lea    0x10(%rsp),%rbp
  b6a4f0:	movaps %xmm1,%xmm0
  b6a4f3:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  b6a4f8:	lea    0x5b(%rsp),%rdx
  b6a4fd:	mov    $0xfe6008,%esi
  b6a502:	mov    %rbp,%rdi
  b6a505:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b6a50a:	mov    0x90(%rbx),%rdi
  b6a511:	movss  0x43e247(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b6a519:	movss  0x43a303(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b6a521:	xor    %edx,%edx
  b6a523:	movss  0x43a2e1(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b6a52b:	mov    %rbp,%rsi
  b6a52e:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  b6a533:	mov    0x10(%rsp),%rdi
  b6a538:	sub    $0x18,%rdi
  b6a53c:	cmp    $0x1423a20,%rdi
  b6a543:	jne    b6a732 <CMerchantMenu::setOpen(bool)+0x512>
  b6a549:	movb   $0x0,0x61(%rbx)
  b6a54d:	movb   $0x0,0x60(%rbx)
  b6a551:	jmp    b6a269 <CMerchantMenu::setOpen(bool)+0x49>
  b6a556:	cs nopw 0x0(%rax,%rax,1)
  b6a560:	mov    0x70(%rbx),%rdi
  b6a564:	mov    $0x5,%esi
  b6a569:	call   a8f450 <CGameUI::queueTip(EContextTip)>
  b6a56e:	jmp    b6a247 <CMerchantMenu::setOpen(bool)+0x27>
  b6a573:	nopl   0x0(%rax,%rax,1)
  b6a578:	lea    0x30(%rsp),%r12
  b6a57d:	lea    0x5d(%rsp),%rdx
  b6a582:	mov    $0xfe600e,%esi
  b6a587:	mov    %r12,%rdi
  b6a58a:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b6a58f:	mov    0x90(%rbx),%rdi
  b6a596:	movss  0x43e1c2(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b6a59e:	movss  0x43a27e(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b6a5a6:	xor    %edx,%edx
  b6a5a8:	mov    %r12,%rsi
  b6a5ab:	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  b6a5b0:	mov    %r12,%rdi
  b6a5b3:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b6a5b8:	jmp    b6a357 <CMerchantMenu::setOpen(bool)+0x137>
  b6a5bd:	nopl   (%rax)
  b6a5c0:	mov    0x3420(%rbx),%rdi
  b6a5c7:	xor    %esi,%esi
  b6a5c9:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a5ce:	mov    0x3410(%rbx),%rdi
  b6a5d5:	mov    $0x1,%esi
  b6a5da:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a5df:	mov    0x3418(%rbx),%rdi
  b6a5e6:	xor    %esi,%esi
  b6a5e8:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a5ed:	mov    0x3408(%rbx),%rdi
  b6a5f4:	xor    %esi,%esi
  b6a5f6:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a5fb:	mov    0x33f8(%rbx),%rdi
  b6a602:	mov    $0x1,%esi
  b6a607:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a60c:	mov    0x3400(%rbx),%rdi
  b6a613:	xor    %esi,%esi
  b6a615:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a61a:	movl   $0x1,0x3454(%rbx)
  b6a624:	jmp    b6a4ac <CMerchantMenu::setOpen(bool)+0x28c>
  b6a629:	nopl   0x0(%rax)
  b6a630:	mov    0x3420(%rbx),%rdi
  b6a637:	xor    %esi,%esi
  b6a639:	movl   $0x2,0x3454(%rbx)
  b6a643:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a648:	mov    0x3410(%rbx),%rdi
  b6a64f:	xor    %esi,%esi
  b6a651:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a656:	mov    0x3418(%rbx),%rdi
  b6a65d:	mov    $0x1,%esi
  b6a662:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b6a667:	mov    0x3408(%rbx),%rdi
  b6a66e:	xor    %esi,%esi
  b6a670:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a675:	mov    0x33f8(%rbx),%rdi
  b6a67c:	xor    %esi,%esi
  b6a67e:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a683:	mov    0x3400(%rbx),%rdi
  b6a68a:	mov    $0x1,%esi
  b6a68f:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b6a694:	jmp    b6a4ac <CMerchantMenu::setOpen(bool)+0x28c>
  b6a699:	mov    $0x5541c8,%edx
  b6a69e:	test   %rdx,%rdx
  b6a6a1:	je     b6a775 <CMerchantMenu::setOpen(bool)+0x555>
  b6a6a7:	or     $0xffffffff,%edx
  b6a6aa:	lock xadd %edx,0x10(%rdi)
  b6a6af:	test   %edx,%edx
  b6a6b1:	jg     b6a307 <CMerchantMenu::setOpen(bool)+0xe7>
  b6a6b7:	lea    0x5a(%rsp),%rsi
  b6a6bc:	mov    %al,0x8(%rsp)
  b6a6c0:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  b6a6c5:	movzbl 0x8(%rsp),%eax
  b6a6ca:	jmp    b6a307 <CMerchantMenu::setOpen(bool)+0xe7>
  b6a6cf:	mov    $0x5541c8,%eax
  b6a6d4:	test   %rax,%rax
  b6a6d7:	je     b6a714 <CMerchantMenu::setOpen(bool)+0x4f4>
  b6a6d9:	or     $0xffffffff,%eax
  b6a6dc:	lock xadd %eax,0x10(%rdi)
  b6a6e1:	test   %eax,%eax
  b6a6e3:	jg     b6a3a9 <CMerchantMenu::setOpen(bool)+0x189>
  b6a6e9:	lea    0x59(%rsp),%rsi
  b6a6ee:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  b6a6f3:	jmp    b6a3a9 <CMerchantMenu::setOpen(bool)+0x189>
  b6a6f8:	mov    %rax,%rbx
  b6a6fb:	mov    %rbx,%rdi
  b6a6fe:	call   554498 <_Unwind_Resume@plt>
  b6a703:	jmp    b6a6f8 <CMerchantMenu::setOpen(bool)+0x4d8>
  b6a705:	mov    %r12,%rdi
  b6a708:	mov    %rax,%rbx
  b6a70b:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b6a710:	jmp    b6a6fb <CMerchantMenu::setOpen(bool)+0x4db>
  b6a712:	jmp    b6a6f8 <CMerchantMenu::setOpen(bool)+0x4d8>
  b6a714:	mov    0x10(%rdi),%eax
  b6a717:	lea    -0x1(%rax),%edx
  b6a71a:	mov    %edx,0x10(%rdi)
  b6a71d:	jmp    b6a6e1 <CMerchantMenu::setOpen(bool)+0x4c1>
  b6a71f:	nop
  b6a720:	jmp    b6a705 <CMerchantMenu::setOpen(bool)+0x4e5>
  b6a722:	jmp    b6a6f8 <CMerchantMenu::setOpen(bool)+0x4d8>
  b6a724:	jmp    b6a705 <CMerchantMenu::setOpen(bool)+0x4e5>
  b6a726:	cs nopw 0x0(%rax,%rax,1)
  b6a730:	jmp    b6a6f8 <CMerchantMenu::setOpen(bool)+0x4d8>
  b6a732:	mov    $0x5541c8,%eax
  b6a737:	test   %rax,%rax
  b6a73a:	je     b6a768 <CMerchantMenu::setOpen(bool)+0x548>
  b6a73c:	or     $0xffffffff,%eax
  b6a73f:	lock xadd %eax,0x10(%rdi)
  b6a744:	test   %eax,%eax
  b6a746:	jg     b6a549 <CMerchantMenu::setOpen(bool)+0x329>
  b6a74c:	lea    0x58(%rsp),%rsi
  b6a751:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  b6a756:	jmp    b6a549 <CMerchantMenu::setOpen(bool)+0x329>
  b6a75b:	mov    %rbp,%rdi
  b6a75e:	mov    %rax,%rbx
  b6a761:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b6a766:	jmp    b6a6fb <CMerchantMenu::setOpen(bool)+0x4db>
  b6a768:	mov    0x10(%rdi),%eax
  b6a76b:	lea    -0x1(%rax),%edx
  b6a76e:	mov    %edx,0x10(%rdi)
  b6a771:	jmp    b6a744 <CMerchantMenu::setOpen(bool)+0x524>
  b6a773:	jmp    b6a705 <CMerchantMenu::setOpen(bool)+0x4e5>
  b6a775:	mov    0x10(%rdi),%edx
  b6a778:	lea    -0x1(%rdx),%ecx
  b6a77b:	mov    %ecx,0x10(%rdi)
  b6a77e:	jmp    b6a6af <CMerchantMenu::setOpen(bool)+0x48f>
