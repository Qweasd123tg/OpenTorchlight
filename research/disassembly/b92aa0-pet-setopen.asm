
/mnt/data/ot-original-inputs/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000b92aa0 <CPetMenu::setOpen(bool)>:
  b92aa0:	mov    %rbx,-0x28(%rsp)
  b92aa5:	mov    %rbp,-0x20(%rsp)
  b92aaa:	mov    %rdi,%rbx
  b92aad:	mov    %r12,-0x18(%rsp)
  b92ab2:	mov    %r13,-0x10(%rsp)
  b92ab7:	mov    %esi,%ebp
  b92ab9:	mov    %r14,-0x8(%rsp)
  b92abe:	sub    $0xc8,%rsp
  b92ac5:	test   %sil,%sil
  b92ac8:	je     b92ae3 <CPetMenu::setOpen(bool)+0x43>
  b92aca:	mov    0x58(%rdi),%rax
  b92ace:	test   %rax,%rax
  b92ad1:	je     b92ae3 <CPetMenu::setOpen(bool)+0x43>
  b92ad3:	mov    0x330(%rax),%eax
  b92ad9:	cmp    $0x29,%eax
  b92adc:	je     b92af6 <CPetMenu::setOpen(bool)+0x56>
  b92ade:	cmp    $0x2a,%eax
  b92ae1:	je     b92af6 <CPetMenu::setOpen(bool)+0x56>
  b92ae3:	cmpb   $0x0,0x68(%rbx)
  b92ae7:	jne    b92b30 <CPetMenu::setOpen(bool)+0x90>
  b92ae9:	test   %bpl,%bpl
  b92aec:	jne    b92be0 <CPetMenu::setOpen(bool)+0x140>
  b92af2:	movb   $0x0,0x68(%rbx)
  b92af6:	mov    0xa0(%rsp),%rbx
  b92afe:	mov    0xa8(%rsp),%rbp
  b92b06:	mov    0xb0(%rsp),%r12
  b92b0e:	mov    0xb8(%rsp),%r13
  b92b16:	mov    0xc0(%rsp),%r14
  b92b1e:	add    $0xc8,%rsp
  b92b25:	ret
  b92b26:	cs nopw 0x0(%rax,%rax,1)
  b92b30:	test   %bpl,%bpl
  b92b33:	jne    b92dc7 <CPetMenu::setOpen(bool)+0x327>
  b92b39:	mov    0x91f0(%rbx),%rax
  b92b40:	test   %rax,%rax
  b92b43:	je     b92b5a <CPetMenu::setOpen(bool)+0xba>
  b92b45:	mov    0x30(%rax),%rsi
  b92b49:	mov    0xb0(%rsi),%rdi
  b92b50:	test   %rdi,%rdi
  b92b53:	je     b92b5a <CPetMenu::setOpen(bool)+0xba>
  b92b55:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  b92b5a:	xorps  %xmm1,%xmm1
  b92b5d:	mov    0x91b8(%rbx),%rdi
  b92b64:	xor    %edx,%edx
  b92b66:	mov    $0x42,%esi
  b92b6b:	xor    %ecx,%ecx
  b92b6d:	lea    0x50(%rsp),%rbp
  b92b72:	movaps %xmm1,%xmm0
  b92b75:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  b92b7a:	lea    0x9b(%rsp),%rdx
  b92b82:	mov    $0xfe6008,%esi
  b92b87:	mov    %rbp,%rdi
  b92b8a:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b92b8f:	mov    0x91a0(%rbx),%rdi
  b92b96:	movss  0x415bc2(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b92b9e:	movss  0x411c7e(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b92ba6:	xor    %edx,%edx
  b92ba8:	movss  0x411c5c(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b92bb0:	mov    %rbp,%rsi
  b92bb3:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  b92bb8:	mov    0x50(%rsp),%rdi
  b92bbd:	sub    $0x18,%rdi
  b92bc1:	cmp    $0x1423a20,%rdi
  b92bc8:	jne    b92fe4 <CPetMenu::setOpen(bool)+0x544>
  b92bce:	movb   $0x0,0x69(%rbx)
  b92bd2:	movb   $0x0,0x68(%rbx)
  b92bd6:	jmp    b92af6 <CPetMenu::setOpen(bool)+0x56>
  b92bdb:	nopl   0x0(%rax,%rax,1)
  b92be0:	xorps  %xmm1,%xmm1
  b92be3:	mov    0x91b8(%rbx),%rdi
  b92bea:	xor    %edx,%edx
  b92bec:	xor    %ecx,%ecx
  b92bee:	mov    $0x16,%esi
  b92bf3:	lea    0x90(%rsp),%r12
  b92bfb:	movaps %xmm1,%xmm0
  b92bfe:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  b92c03:	mov    0x88(%rbx),%rdi
  b92c0a:	mov    0x978854(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  b92c10:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  b92c15:	cvtsi2ss %eax,%xmm0
  b92c19:	mov    0x978849(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  b92c1f:	movss  %xmm0,0x38(%rsp)
  b92c25:	mov    0x88(%rbx),%rdi
  b92c2c:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  b92c31:	cvtsi2ss %eax,%xmm0
  b92c35:	mov    $0x1,%esi
  b92c3a:	movss  %xmm0,0x3c(%rsp)
  b92c40:	mov    0x91a0(%rbx),%rdi
  b92c47:	mov    (%rdi),%rax
  b92c4a:	call   *0x50(%rax)
  b92c4d:	lea    0x9f(%rsp),%rdx
  b92c55:	mov    $0xfe6008,%esi
  b92c5a:	mov    %r12,%rdi
  b92c5d:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b92c62:	mov    0x91a0(%rbx),%rdi
  b92c69:	mov    %r12,%rsi
  b92c6c:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  b92c71:	mov    %r12,%rdi
  b92c74:	mov    %eax,%r13d
  b92c77:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b92c7c:	test   %r13b,%r13b
  b92c7f:	jne    b92de0 <CPetMenu::setOpen(bool)+0x340>
  b92c85:	lea    0x70(%rsp),%r12
  b92c8a:	lea    0x9d(%rsp),%rdx
  b92c92:	mov    $0xfe600e,%esi
  b92c97:	mov    %r12,%rdi
  b92c9a:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b92c9f:	mov    0x91a0(%rbx),%rdi
  b92ca6:	movss  0x415ab2(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b92cae:	movss  0x411b6e(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b92cb6:	xor    %edx,%edx
  b92cb8:	mov    %r12,%rsi
  b92cbb:	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  b92cc0:	mov    %r12,%rdi
  b92cc3:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b92cc8:	lea    0x60(%rsp),%r12
  b92ccd:	lea    0x9c(%rsp),%rdx
  b92cd5:	mov    $0xfc993a,%esi
  b92cda:	mov    %r12,%rdi
  b92cdd:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b92ce2:	mov    0x91a0(%rbx),%rdi
  b92ce9:	movss  0x411b0b(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  b92cf1:	movss  0x411b13(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b92cf9:	mov    $0x1,%edx
  b92cfe:	mov    %r12,%rsi
  b92d01:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  b92d06:	mov    %r12,%rdi
  b92d09:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b92d0e:	mov    0x20(%rbx),%rsi
  b92d12:	mov    0x18(%rbx),%rdi
  b92d16:	call   5561f8 <CEGUI::Window::addChildWindow(CEGUI::Window*)@plt>
  b92d1b:	mov    0x20(%rbx),%rdi
  b92d1f:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  b92d24:	mov    0x91d8(%rbx),%rdi
  b92d2b:	mov    $0x1,%esi
  b92d30:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b92d35:	mov    0x91e0(%rbx),%rdi
  b92d3c:	xor    %esi,%esi
  b92d3e:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b92d43:	mov    0x91e8(%rbx),%rdi
  b92d4a:	xor    %esi,%esi
  b92d4c:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  b92d51:	mov    0x91c0(%rbx),%rdi
  b92d58:	mov    $0x1,%esi
  b92d5d:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b92d62:	mov    0x91c8(%rbx),%rdi
  b92d69:	xor    %esi,%esi
  b92d6b:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b92d70:	mov    0x91d0(%rbx),%rdi
  b92d77:	xor    %esi,%esi
  b92d79:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  b92d7e:	mov    0x20(%rbx),%rdi
  b92d82:	movl   $0x0,0x6c(%rbx)
  b92d89:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  b92d8e:	mov    0x48(%rbx),%rdi
  b92d92:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  b92d97:	mov    0x28(%rbx),%rdi
  b92d9b:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  b92da0:	cmpq   $0x0,0x9180(%rbx)
  b92da8:	je     b92e33 <CPetMenu::setOpen(bool)+0x393>
  b92dae:	mov    0x91a8(%rbx),%rdi
  b92db5:	call   d6f740 <CResourceManager::getGameUI()>
  b92dba:	mov    $0xf,%esi
  b92dbf:	mov    %rax,%rdi
  b92dc2:	call   a8f450 <CGameUI::queueTip(EContextTip)>
  b92dc7:	mov    (%rbx),%rax
  b92dca:	mov    %bpl,0x68(%rbx)
  b92dce:	mov    %rbx,%rdi
  b92dd1:	call   *0x48(%rax)
  b92dd4:	jmp    b92af6 <CPetMenu::setOpen(bool)+0x56>
  b92dd9:	nopl   0x0(%rax)
  b92de0:	lea    0x80(%rsp),%r12
  b92de8:	lea    0x9e(%rsp),%rdx
  b92df0:	mov    $0xfe600e,%esi
  b92df5:	mov    %r12,%rdi
  b92df8:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  b92dfd:	mov    0x91a0(%rbx),%rdi
  b92e04:	movss  0x415954(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  b92e0c:	movss  0x411a10(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  b92e14:	xor    %edx,%edx
  b92e16:	movss  0x4119ee(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  b92e1e:	mov    %r12,%rsi
  b92e21:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  b92e26:	mov    %r12,%rdi
  b92e29:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b92e2e:	jmp    b92cc8 <CPetMenu::setOpen(bool)+0x228>
  b92e33:	mov    0x9178(%rbx),%rdi
  b92e3a:	xorps  %xmm1,%xmm1
  b92e3d:	movss  0x4119b7(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  b92e45:	mov    0x9170(%rbx),%rsi
  b92e4c:	movaps %xmm3,%xmm2
  b92e4f:	mov    $0x4,%edx
  b92e54:	mov    (%rdi),%rax
  b92e57:	movaps %xmm1,%xmm0
  b92e5a:	call   *0x48(%rax)
  b92e5d:	mov    0x90(%rbx),%rdi
  b92e64:	mov    %rax,0x9180(%rbx)
  b92e6b:	mov    %rax,%r12
  b92e6e:	movss  0x91b4(%rbx),%xmm4
  b92e76:	movss  0x43b696(%rip),%xmm0        # fce514 <vtable for iInventoryListener+0xd4>
  b92e7e:	movss  %xmm4,(%rsp)
  b92e83:	call   a83e70 <CGameUI::scaledY(float)>
  b92e88:	movss  (%rsp),%xmm4
  b92e8d:	addss  %xmm0,%xmm4
  b92e91:	mov    0x90(%rbx),%rdi
  b92e98:	movss  0x45ceb8(%rip),%xmm0        # fefd58 <typeinfo name for CEGUI::MemberFunctionSlot<CInventoryMenu>+0x38>
  b92ea0:	divss  0x38(%rsp),%xmm4
  b92ea6:	movss  %xmm4,(%rsp)
  b92eab:	call   a83e70 <CGameUI::scaledY(float)>
  b92eb0:	xorps  %xmm1,%xmm1
  b92eb3:	movaps %xmm0,%xmm2
  b92eb6:	movss  (%rsp),%xmm4
  b92ebb:	divss  0x38(%rsp),%xmm2
  b92ec1:	ucomiss %xmm4,%xmm1
  b92ec4:	jbe    b92ee3 <CPetMenu::setOpen(bool)+0x443>
  b92ec6:	movss  0x41192e(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  b92ece:	addss  %xmm4,%xmm2
  b92ed2:	divss  0x38(%rsp),%xmm0
  b92ed8:	movaps %xmm1,%xmm4
  b92edb:	addss  %xmm1,%xmm0
  b92edf:	maxss  %xmm0,%xmm2
  b92ee3:	mov    0x90(%rbx),%rdi
  b92eea:	movss  0x45d9d6(%rip),%xmm0        # ff08c8 <typeinfo name for CEGUI::MemberFunctionSlot<CPetMenu>+0x28>
  b92ef2:	movss  %xmm2,0x10(%rsp)
  b92ef8:	movss  %xmm4,(%rsp)
  b92efd:	call   a83e70 <CGameUI::scaledY(float)>
  b92f02:	mov    0x90(%rbx),%rdi
  b92f09:	movaps %xmm0,%xmm3
  b92f0c:	movss  0x45d9b8(%rip),%xmm0        # ff08cc <typeinfo name for CEGUI::MemberFunctionSlot<CPetMenu>+0x2c>
  b92f14:	movss  %xmm3,0x20(%rsp)
  b92f1a:	call   a83e70 <CGameUI::scaledY(float)>
  b92f1f:	movaps %xmm0,%xmm1
  b92f22:	mov    0x9180(%rbx),%rdi
  b92f29:	movss  0x20(%rsp),%xmm3
  b92f2f:	divss  0x3c(%rsp),%xmm3
  b92f35:	movss  (%rsp),%xmm4
  b92f3a:	movaps %xmm4,%xmm0
  b92f3d:	movss  0x10(%rsp),%xmm2
  b92f43:	divss  0x3c(%rsp),%xmm1
  b92f49:	call   552ba8 <Ogre::Viewport::setDimensions(float, float, float, float)@plt>
  b92f4e:	movl   $0x0,0x40(%rsp)
  b92f56:	movl   $0x0,0x44(%rsp)
  b92f5e:	lea    0x40(%rsp),%rsi
  b92f63:	movl   $0x0,0x48(%rsp)
  b92f6b:	movl   $0x3f800000,0x4c(%rsp)
  b92f73:	mov    0x9180(%rbx),%rdi
  b92f7a:	call   553c18 <Ogre::Viewport::setBackgroundColour(Ogre::ColourValue const&)@plt>
  b92f7f:	mov    0x9180(%rbx),%rdi
  b92f86:	mov    $0x3,%edx
  b92f8b:	mov    $0x1,%esi
  b92f90:	call   553898 <Ogre::Viewport::setClearEveryFrame(bool, unsigned int)@plt>
  b92f95:	mov    0x9170(%rbx),%rax
  b92f9c:	mov    %r12,%rdi
  b92f9f:	mov    (%rax),%rax
  b92fa2:	mov    0x278(%rax),%r13
  b92fa9:	call   553978 <Ogre::Viewport::getActualWidth() const@plt>
  b92fae:	mov    %r12,%rdi
  b92fb1:	mov    %eax,%r14d
  b92fb4:	call   554968 <Ogre::Viewport::getActualHeight() const@plt>
  b92fb9:	cvtsi2ss %r14d,%xmm0
  b92fbe:	mov    0x9170(%rbx),%rdi
  b92fc5:	cvtsi2ss %eax,%xmm1
  b92fc9:	divss  %xmm1,%xmm0
  b92fcd:	call   *%r13
  b92fd0:	mov    0x9170(%rbx),%rsi
  b92fd7:	mov    %r12,%rdi
  b92fda:	call   555e18 <Ogre::Viewport::setCamera(Ogre::Camera*)@plt>
  b92fdf:	jmp    b92dae <CPetMenu::setOpen(bool)+0x30e>
  b92fe4:	mov    $0x5541c8,%eax
  b92fe9:	test   %rax,%rax
  b92fec:	je     b93028 <CPetMenu::setOpen(bool)+0x588>
  b92fee:	or     $0xffffffff,%eax
  b92ff1:	lock xadd %eax,0x10(%rdi)
  b92ff6:	test   %eax,%eax
  b92ff8:	jg     b92bce <CPetMenu::setOpen(bool)+0x12e>
  b92ffe:	lea    0x9a(%rsp),%rsi
  b93006:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  b9300b:	jmp    b92bce <CPetMenu::setOpen(bool)+0x12e>
  b93010:	mov    %r12,%rdi
  b93013:	mov    %rax,%rbx
  b93016:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b9301b:	mov    %rbx,%rdi
  b9301e:	call   554498 <_Unwind_Resume@plt>
  b93023:	mov    %rax,%rbx
  b93026:	jmp    b9301b <CPetMenu::setOpen(bool)+0x57b>
  b93028:	mov    0x10(%rdi),%eax
  b9302b:	lea    -0x1(%rax),%edx
  b9302e:	mov    %edx,0x10(%rdi)
  b93031:	jmp    b92ff6 <CPetMenu::setOpen(bool)+0x556>
  b93033:	jmp    b93010 <CPetMenu::setOpen(bool)+0x570>
  b93035:	jmp    b93023 <CPetMenu::setOpen(bool)+0x583>
  b93037:	mov    %rbp,%rdi
  b9303a:	mov    %rax,%rbx
  b9303d:	nopl   (%rax)
  b93040:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  b93045:	jmp    b9301b <CPetMenu::setOpen(bool)+0x57b>
  b93047:	jmp    b93023 <CPetMenu::setOpen(bool)+0x583>
  b93049:	nopl   0x0(%rax)
  b93050:	jmp    b93010 <CPetMenu::setOpen(bool)+0x570>
  b93052:	jmp    b93023 <CPetMenu::setOpen(bool)+0x583>
  b93054:	jmp    b93010 <CPetMenu::setOpen(bool)+0x570>
  b93056:	cs nopw 0x0(%rax,%rax,1)
  b93060:	jmp    b93023 <CPetMenu::setOpen(bool)+0x583>
