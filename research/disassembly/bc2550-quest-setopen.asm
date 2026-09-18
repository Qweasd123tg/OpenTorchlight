
/mnt/data/ot-original-inputs/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000bc2550 <CQuestMenu::setOpen(bool)>:
  bc2550:	mov    %rbx,-0x18(%rsp)
  bc2555:	mov    %rbp,-0x10(%rsp)
  bc255a:	mov    %rdi,%rbx
  bc255d:	mov    %r12,-0x8(%rsp)
  bc2562:	sub    $0x78,%rsp
  bc2566:	cmpb   $0x0,0x188(%rdi)
  bc256d:	mov    %esi,%ebp
  bc256f:	jne    bc2598 <CQuestMenu::setOpen(bool)+0x48>
  bc2571:	test   %sil,%sil
  bc2574:	jne    bc2620 <CQuestMenu::setOpen(bool)+0xd0>
  bc257a:	mov    %bpl,0x188(%rbx)
  bc2581:	mov    0x60(%rsp),%rbx
  bc2586:	mov    0x68(%rsp),%rbp
  bc258b:	mov    0x70(%rsp),%r12
  bc2590:	add    $0x78,%rsp
  bc2594:	ret
  bc2595:	nopl   (%rax)
  bc2598:	test   %sil,%sil
  bc259b:	jne    bc257a <CQuestMenu::setOpen(bool)+0x2a>
  bc259d:	xorps  %xmm1,%xmm1
  bc25a0:	mov    0x1d8(%rdi),%rdi
  bc25a7:	xor    %edx,%edx
  bc25a9:	mov    $0x42,%esi
  bc25ae:	xor    %ecx,%ecx
  bc25b0:	lea    0x10(%rsp),%r12
  bc25b5:	movaps %xmm1,%xmm0
  bc25b8:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  bc25bd:	lea    0x5b(%rsp),%rdx
  bc25c2:	mov    $0xfe6008,%esi
  bc25c7:	mov    %r12,%rdi
  bc25ca:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  bc25cf:	mov    0x1b0(%rbx),%rdi
  bc25d6:	movss  0x3e6182(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  bc25de:	movss  0x3e223e(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  bc25e6:	xor    %edx,%edx
  bc25e8:	movss  0x3e221c(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  bc25f0:	mov    %r12,%rsi
  bc25f3:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  bc25f8:	mov    0x10(%rsp),%rdi
  bc25fd:	sub    $0x18,%rdi
  bc2601:	cmp    $0x1423a20,%rdi
  bc2608:	jne    bc280b <CQuestMenu::setOpen(bool)+0x2bb>
  bc260e:	movb   $0x0,0x189(%rbx)
  bc2615:	jmp    bc257a <CQuestMenu::setOpen(bool)+0x2a>
  bc261a:	nopw   0x0(%rax,%rax,1)
  bc2620:	xorps  %xmm1,%xmm1
  bc2623:	mov    0x1d8(%rdi),%rdi
  bc262a:	xor    %edx,%edx
  bc262c:	xor    %ecx,%ecx
  bc262e:	mov    $0x16,%esi
  bc2633:	lea    0x50(%rsp),%r12
  bc2638:	movaps %xmm1,%xmm0
  bc263b:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  bc2640:	mov    0x198(%rbx),%rdi
  bc2647:	mov    0x948e17(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  bc264d:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  bc2652:	mov    0x198(%rbx),%rdi
  bc2659:	mov    0x948e09(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  bc265f:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  bc2664:	mov    0x1b0(%rbx),%rdi
  bc266b:	mov    $0x1,%esi
  bc2670:	mov    (%rdi),%rax
  bc2673:	call   *0x50(%rax)
  bc2676:	lea    0x5f(%rsp),%rdx
  bc267b:	mov    $0xfe6008,%esi
  bc2680:	mov    %r12,%rdi
  bc2683:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  bc2688:	mov    0x1b0(%rbx),%rdi
  bc268f:	mov    %r12,%rsi
  bc2692:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  bc2697:	mov    0x50(%rsp),%rdi
  bc269c:	sub    $0x18,%rdi
  bc26a0:	cmp    $0x1423a20,%rdi
  bc26a7:	jne    bc27d5 <CQuestMenu::setOpen(bool)+0x285>
  bc26ad:	test   %al,%al
  bc26af:	je     bc2790 <CQuestMenu::setOpen(bool)+0x240>
  bc26b5:	lea    0x40(%rsp),%r12
  bc26ba:	lea    0x5e(%rsp),%rdx
  bc26bf:	mov    $0xfe600e,%esi
  bc26c4:	mov    %r12,%rdi
  bc26c7:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  bc26cc:	mov    0x1b0(%rbx),%rdi
  bc26d3:	movss  0x3e6085(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  bc26db:	movss  0x3e2141(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  bc26e3:	xor    %edx,%edx
  bc26e5:	movss  0x3e211f(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  bc26ed:	mov    %r12,%rsi
  bc26f0:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  bc26f5:	mov    %r12,%rdi
  bc26f8:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  bc26fd:	lea    0x20(%rsp),%r12
  bc2702:	lea    0x5c(%rsp),%rdx
  bc2707:	mov    $0xfc993a,%esi
  bc270c:	mov    %r12,%rdi
  bc270f:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  bc2714:	mov    0x1b0(%rbx),%rdi
  bc271b:	movss  0x3e20d9(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  bc2723:	movss  0x3e20e1(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  bc272b:	mov    $0x1,%edx
  bc2730:	mov    %r12,%rsi
  bc2733:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  bc2738:	mov    0x20(%rsp),%rdi
  bc273d:	mov    $0x1423a20,%eax
  bc2742:	sub    $0x18,%rdi
  bc2746:	cmp    %rdi,%rax
  bc2749:	jne    bc2838 <CQuestMenu::setOpen(bool)+0x2e8>
  bc274f:	mov    0x18(%rbx),%rsi
  bc2753:	mov    0x10(%rbx),%rdi
  bc2757:	call   5561f8 <CEGUI::Window::addChildWindow(CEGUI::Window*)@plt>
  bc275c:	mov    0x18(%rbx),%rdi
  bc2760:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  bc2765:	mov    (%rbx),%rax
  bc2768:	mov    %rbx,%rdi
  bc276b:	call   *0x48(%rax)
  bc276e:	mov    0x18(%rbx),%rdi
  bc2772:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  bc2777:	mov    0x20(%rbx),%rdi
  bc277b:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  bc2780:	mov    0x28(%rbx),%rdi
  bc2784:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  bc2789:	jmp    bc257a <CQuestMenu::setOpen(bool)+0x2a>
  bc278e:	xchg   %ax,%ax
  bc2790:	lea    0x30(%rsp),%r12
  bc2795:	lea    0x5d(%rsp),%rdx
  bc279a:	mov    $0xfe600e,%esi
  bc279f:	mov    %r12,%rdi
  bc27a2:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  bc27a7:	mov    0x1b0(%rbx),%rdi
  bc27ae:	movss  0x3e5faa(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  bc27b6:	movss  0x3e2066(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  bc27be:	xor    %edx,%edx
  bc27c0:	mov    %r12,%rsi
  bc27c3:	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  bc27c8:	mov    %r12,%rdi
  bc27cb:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  bc27d0:	jmp    bc26fd <CQuestMenu::setOpen(bool)+0x1ad>
  bc27d5:	mov    $0x5541c8,%edx
  bc27da:	test   %rdx,%rdx
  bc27dd:	je     bc28a2 <CQuestMenu::setOpen(bool)+0x352>
  bc27e3:	or     $0xffffffff,%edx
  bc27e6:	lock xadd %edx,0x10(%rdi)
  bc27eb:	test   %edx,%edx
  bc27ed:	jg     bc26ad <CQuestMenu::setOpen(bool)+0x15d>
  bc27f3:	lea    0x5a(%rsp),%rsi
  bc27f8:	mov    %al,0x8(%rsp)
  bc27fc:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  bc2801:	movzbl 0x8(%rsp),%eax
  bc2806:	jmp    bc26ad <CQuestMenu::setOpen(bool)+0x15d>
  bc280b:	mov    $0x5541c8,%eax
  bc2810:	test   %rax,%rax
  bc2813:	je     bc28b2 <CQuestMenu::setOpen(bool)+0x362>
  bc2819:	or     $0xffffffff,%eax
  bc281c:	lock xadd %eax,0x10(%rdi)
  bc2821:	test   %eax,%eax
  bc2823:	jg     bc260e <CQuestMenu::setOpen(bool)+0xbe>
  bc2829:	lea    0x58(%rsp),%rsi
  bc282e:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  bc2833:	jmp    bc260e <CQuestMenu::setOpen(bool)+0xbe>
  bc2838:	mov    $0x5541c8,%eax
  bc283d:	test   %rax,%rax
  bc2840:	je     bc2882 <CQuestMenu::setOpen(bool)+0x332>
  bc2842:	or     $0xffffffff,%eax
  bc2845:	lock xadd %eax,0x10(%rdi)
  bc284a:	test   %eax,%eax
  bc284c:	jg     bc274f <CQuestMenu::setOpen(bool)+0x1ff>
  bc2852:	lea    0x59(%rsp),%rsi
  bc2857:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  bc285c:	jmp    bc274f <CQuestMenu::setOpen(bool)+0x1ff>
  bc2861:	mov    %r12,%rdi
  bc2864:	mov    %rax,%rbx
  bc2867:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  bc286c:	mov    %rbx,%rdi
  bc286f:	call   554498 <_Unwind_Resume@plt>
  bc2874:	mov    %rax,%rbx
  bc2877:	jmp    bc286c <CQuestMenu::setOpen(bool)+0x31c>
  bc2879:	jmp    bc2861 <CQuestMenu::setOpen(bool)+0x311>
  bc287b:	nopl   0x0(%rax,%rax,1)
  bc2880:	jmp    bc2874 <CQuestMenu::setOpen(bool)+0x324>
  bc2882:	mov    0x10(%rdi),%eax
  bc2885:	lea    -0x1(%rax),%edx
  bc2888:	mov    %edx,0x10(%rdi)
  bc288b:	jmp    bc284a <CQuestMenu::setOpen(bool)+0x2fa>
  bc288d:	jmp    bc2861 <CQuestMenu::setOpen(bool)+0x311>
  bc288f:	nop
  bc2890:	jmp    bc2874 <CQuestMenu::setOpen(bool)+0x324>
  bc2892:	jmp    bc2861 <CQuestMenu::setOpen(bool)+0x311>
  bc2894:	jmp    bc2874 <CQuestMenu::setOpen(bool)+0x324>
  bc2896:	cs nopw 0x0(%rax,%rax,1)
  bc28a0:	jmp    bc2861 <CQuestMenu::setOpen(bool)+0x311>
  bc28a2:	mov    0x10(%rdi),%edx
  bc28a5:	lea    -0x1(%rdx),%ecx
  bc28a8:	mov    %ecx,0x10(%rdi)
  bc28ab:	jmp    bc27eb <CQuestMenu::setOpen(bool)+0x29b>
  bc28b0:	jmp    bc2874 <CQuestMenu::setOpen(bool)+0x324>
  bc28b2:	mov    0x10(%rdi),%eax
  bc28b5:	lea    -0x1(%rax),%edx
  bc28b8:	mov    %edx,0x10(%rdi)
  bc28bb:	jmp    bc2821 <CQuestMenu::setOpen(bool)+0x2d1>
