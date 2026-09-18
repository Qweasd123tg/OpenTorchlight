
/mnt/data/ot-original-inputs/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000e3a680 <CJournalMenu::setOpen(bool)>:
  e3a680:	mov    %rbx,-0x18(%rsp)
  e3a685:	mov    %rbp,-0x10(%rsp)
  e3a68a:	mov    %rdi,%rbx
  e3a68d:	mov    %r12,-0x8(%rsp)
  e3a692:	sub    $0x78,%rsp
  e3a696:	cmpb   $0x0,0x38(%rdi)
  e3a69a:	mov    %esi,%ebp
  e3a69c:	jne    e3a6c0 <CJournalMenu::setOpen(bool)+0x40>
  e3a69e:	test   %sil,%sil
  e3a6a1:	jne    e3a740 <CJournalMenu::setOpen(bool)+0xc0>
  e3a6a7:	mov    %bpl,0x38(%rbx)
  e3a6ab:	mov    0x60(%rsp),%rbx
  e3a6b0:	mov    0x68(%rsp),%rbp
  e3a6b5:	mov    0x70(%rsp),%r12
  e3a6ba:	add    $0x78,%rsp
  e3a6be:	ret
  e3a6bf:	nop
  e3a6c0:	test   %sil,%sil
  e3a6c3:	jne    e3a6a7 <CJournalMenu::setOpen(bool)+0x27>
  e3a6c5:	xorps  %xmm1,%xmm1
  e3a6c8:	mov    0x80(%rdi),%rdi
  e3a6cf:	xor    %edx,%edx
  e3a6d1:	mov    $0x42,%esi
  e3a6d6:	xor    %ecx,%ecx
  e3a6d8:	lea    0x10(%rsp),%r12
  e3a6dd:	movaps %xmm1,%xmm0
  e3a6e0:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  e3a6e5:	lea    0x5b(%rsp),%rdx
  e3a6ea:	mov    $0xfe6008,%esi
  e3a6ef:	mov    %r12,%rdi
  e3a6f2:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  e3a6f7:	mov    0x58(%rbx),%rdi
  e3a6fb:	movss  0x16e05d(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  e3a703:	movss  0x16a119(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  e3a70b:	xor    %edx,%edx
  e3a70d:	movss  0x16a0f7(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  e3a715:	mov    %r12,%rsi
  e3a718:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  e3a71d:	mov    0x10(%rsp),%rdi
  e3a722:	sub    $0x18,%rdi
  e3a726:	cmp    $0x1423a20,%rdi
  e3a72d:	jne    e3a918 <CJournalMenu::setOpen(bool)+0x298>
  e3a733:	movb   $0x0,0x39(%rbx)
  e3a737:	jmp    e3a6a7 <CJournalMenu::setOpen(bool)+0x27>
  e3a73c:	nopl   0x0(%rax)
  e3a740:	xorps  %xmm1,%xmm1
  e3a743:	mov    0x80(%rdi),%rdi
  e3a74a:	xor    %edx,%edx
  e3a74c:	xor    %ecx,%ecx
  e3a74e:	mov    $0x16,%esi
  e3a753:	lea    0x50(%rsp),%r12
  e3a758:	movaps %xmm1,%xmm0
  e3a75b:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  e3a760:	mov    0x40(%rbx),%rdi
  e3a764:	mov    0x6d0cfa(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  e3a76a:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  e3a76f:	mov    0x40(%rbx),%rdi
  e3a773:	mov    0x6d0cef(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  e3a779:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  e3a77e:	mov    0x58(%rbx),%rdi
  e3a782:	mov    $0x1,%esi
  e3a787:	mov    (%rdi),%rax
  e3a78a:	call   *0x50(%rax)
  e3a78d:	lea    0x5f(%rsp),%rdx
  e3a792:	mov    $0xfe6008,%esi
  e3a797:	mov    %r12,%rdi
  e3a79a:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  e3a79f:	mov    0x58(%rbx),%rdi
  e3a7a3:	mov    %r12,%rsi
  e3a7a6:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  e3a7ab:	mov    0x50(%rsp),%rdi
  e3a7b0:	sub    $0x18,%rdi
  e3a7b4:	cmp    $0x1423a20,%rdi
  e3a7bb:	jne    e3a8e2 <CJournalMenu::setOpen(bool)+0x262>
  e3a7c1:	test   %al,%al
  e3a7c3:	je     e3a8a0 <CJournalMenu::setOpen(bool)+0x220>
  e3a7c9:	lea    0x40(%rsp),%r12
  e3a7ce:	lea    0x5e(%rsp),%rdx
  e3a7d3:	mov    $0xfe600e,%esi
  e3a7d8:	mov    %r12,%rdi
  e3a7db:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  e3a7e0:	mov    0x58(%rbx),%rdi
  e3a7e4:	movss  0x16df74(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  e3a7ec:	movss  0x16a030(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  e3a7f4:	xor    %edx,%edx
  e3a7f6:	movss  0x16a00e(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  e3a7fe:	mov    %r12,%rsi
  e3a801:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  e3a806:	mov    %r12,%rdi
  e3a809:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  e3a80e:	lea    0x20(%rsp),%r12
  e3a813:	lea    0x5c(%rsp),%rdx
  e3a818:	mov    $0xfc993a,%esi
  e3a81d:	mov    %r12,%rdi
  e3a820:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  e3a825:	mov    0x58(%rbx),%rdi
  e3a829:	movss  0x169fcb(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  e3a831:	movss  0x169fd3(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  e3a839:	mov    $0x1,%edx
  e3a83e:	mov    %r12,%rsi
  e3a841:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  e3a846:	mov    0x20(%rsp),%rdi
  e3a84b:	mov    $0x1423a20,%eax
  e3a850:	sub    $0x18,%rdi
  e3a854:	cmp    %rdi,%rax
  e3a857:	jne    e3a945 <CJournalMenu::setOpen(bool)+0x2c5>
  e3a85d:	mov    0x18(%rbx),%rsi
  e3a861:	mov    0x10(%rbx),%rdi
  e3a865:	call   5561f8 <CEGUI::Window::addChildWindow(CEGUI::Window*)@plt>
  e3a86a:	mov    0x18(%rbx),%rdi
  e3a86e:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  e3a873:	mov    (%rbx),%rax
  e3a876:	mov    %rbx,%rdi
  e3a879:	call   *0x48(%rax)
  e3a87c:	mov    0x18(%rbx),%rdi
  e3a880:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  e3a885:	mov    0x20(%rbx),%rdi
  e3a889:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  e3a88e:	mov    0x28(%rbx),%rdi
  e3a892:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  e3a897:	jmp    e3a6a7 <CJournalMenu::setOpen(bool)+0x27>
  e3a89c:	nopl   0x0(%rax)
  e3a8a0:	lea    0x30(%rsp),%r12
  e3a8a5:	lea    0x5d(%rsp),%rdx
  e3a8aa:	mov    $0xfe600e,%esi
  e3a8af:	mov    %r12,%rdi
  e3a8b2:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  e3a8b7:	mov    0x58(%rbx),%rdi
  e3a8bb:	movss  0x16de9d(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  e3a8c3:	movss  0x169f59(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  e3a8cb:	xor    %edx,%edx
  e3a8cd:	mov    %r12,%rsi
  e3a8d0:	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  e3a8d5:	mov    %r12,%rdi
  e3a8d8:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  e3a8dd:	jmp    e3a80e <CJournalMenu::setOpen(bool)+0x18e>
  e3a8e2:	mov    $0x5541c8,%edx
  e3a8e7:	test   %rdx,%rdx
  e3a8ea:	je     e3a9b2 <CJournalMenu::setOpen(bool)+0x332>
  e3a8f0:	or     $0xffffffff,%edx
  e3a8f3:	lock xadd %edx,0x10(%rdi)
  e3a8f8:	test   %edx,%edx
  e3a8fa:	jg     e3a7c1 <CJournalMenu::setOpen(bool)+0x141>
  e3a900:	lea    0x5a(%rsp),%rsi
  e3a905:	mov    %al,0x8(%rsp)
  e3a909:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  e3a90e:	movzbl 0x8(%rsp),%eax
  e3a913:	jmp    e3a7c1 <CJournalMenu::setOpen(bool)+0x141>
  e3a918:	mov    $0x5541c8,%eax
  e3a91d:	test   %rax,%rax
  e3a920:	je     e3a9c2 <CJournalMenu::setOpen(bool)+0x342>
  e3a926:	or     $0xffffffff,%eax
  e3a929:	lock xadd %eax,0x10(%rdi)
  e3a92e:	test   %eax,%eax
  e3a930:	jg     e3a733 <CJournalMenu::setOpen(bool)+0xb3>
  e3a936:	lea    0x58(%rsp),%rsi
  e3a93b:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  e3a940:	jmp    e3a733 <CJournalMenu::setOpen(bool)+0xb3>
  e3a945:	mov    $0x5541c8,%eax
  e3a94a:	test   %rax,%rax
  e3a94d:	je     e3a992 <CJournalMenu::setOpen(bool)+0x312>
  e3a94f:	or     $0xffffffff,%eax
  e3a952:	lock xadd %eax,0x10(%rdi)
  e3a957:	test   %eax,%eax
  e3a959:	jg     e3a85d <CJournalMenu::setOpen(bool)+0x1dd>
  e3a95f:	lea    0x59(%rsp),%rsi
  e3a964:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  e3a969:	jmp    e3a85d <CJournalMenu::setOpen(bool)+0x1dd>
  e3a96e:	mov    %r12,%rdi
  e3a971:	mov    %rax,%rbx
  e3a974:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  e3a979:	mov    %rbx,%rdi
  e3a97c:	call   554498 <_Unwind_Resume@plt>
  e3a981:	mov    %rax,%rbx
  e3a984:	jmp    e3a979 <CJournalMenu::setOpen(bool)+0x2f9>
  e3a986:	jmp    e3a96e <CJournalMenu::setOpen(bool)+0x2ee>
  e3a988:	nopl   0x0(%rax,%rax,1)
  e3a990:	jmp    e3a981 <CJournalMenu::setOpen(bool)+0x301>
  e3a992:	mov    0x10(%rdi),%eax
  e3a995:	lea    -0x1(%rax),%edx
  e3a998:	mov    %edx,0x10(%rdi)
  e3a99b:	jmp    e3a957 <CJournalMenu::setOpen(bool)+0x2d7>
  e3a99d:	jmp    e3a96e <CJournalMenu::setOpen(bool)+0x2ee>
  e3a99f:	nop
  e3a9a0:	jmp    e3a981 <CJournalMenu::setOpen(bool)+0x301>
  e3a9a2:	jmp    e3a96e <CJournalMenu::setOpen(bool)+0x2ee>
  e3a9a4:	jmp    e3a981 <CJournalMenu::setOpen(bool)+0x301>
  e3a9a6:	cs nopw 0x0(%rax,%rax,1)
  e3a9b0:	jmp    e3a96e <CJournalMenu::setOpen(bool)+0x2ee>
  e3a9b2:	mov    0x10(%rdi),%edx
  e3a9b5:	lea    -0x1(%rdx),%ecx
  e3a9b8:	mov    %ecx,0x10(%rdi)
  e3a9bb:	jmp    e3a8f8 <CJournalMenu::setOpen(bool)+0x278>
  e3a9c0:	jmp    e3a981 <CJournalMenu::setOpen(bool)+0x301>
  e3a9c2:	mov    0x10(%rdi),%eax
  e3a9c5:	lea    -0x1(%rax),%edx
  e3a9c8:	mov    %edx,0x10(%rdi)
  e3a9cb:	jmp    e3a92e <CJournalMenu::setOpen(bool)+0x2ae>
