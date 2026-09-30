# Accepted UI contract evidence; original inputs are external/read-only.
# Torchlight.bin.x86_64 SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Addressed whole bodies for click/double/open/scroll/delete; native SVB/preview dependencies remain partial.
# See research/cegui-character-load.md for production consumers and exact residue.


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c3fe80 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:
  c3fe80:	push   %rbx
  c3fe81:	cmpb   $0x0,0x30(%rdi)
  c3fe85:	mov    %rdi,%rbx
  c3fe88:	jne    c3fe90 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x10>
  c3fe8a:	cmpb   $0x0,0x31(%rdi)
  c3fe8e:	jne    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3fe90:	sub    $0x3,%esi
  c3fe93:	cmp    $0x57,%esi
  c3fe96:	jbe    c3fea0 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x20>
  c3fe98:	mov    $0x1,%eax
  c3fe9d:	pop    %rbx
  c3fe9e:	ret
  c3fe9f:	nop
  c3fea0:	mov    %esi,%esi
  c3fea2:	jmp    *0xff27d8(,%rsi,8)
  c3fea9:	nopl   0x0(%rax)
  c3feb0:	mov    0x198(%rbx),%rdi
  c3feb7:	mov    $0x1,%esi
  c3febc:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  c3fec1:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3fec3:	nopl   0x0(%rax,%rax,1)
  c3fec8:	movslq 0xc8(%rbx),%rdx
  c3fecf:	mov    0x1e8(%rbx),%rax
  c3fed6:	mov    (%rax,%rdx,8),%rax
  c3feda:	movss  0xe0(%rax),%xmm0
  c3fee2:	ucomiss 0x36490f(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  c3fee9:	jbe    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3feeb:	mov    0x40(%rbx),%rdi
  c3feef:	xor    %edx,%edx
  c3fef1:	mov    $0x2,%esi
  c3fef6:	call   a828f0 <CGameUI::requestSetGameState(EGameState, EMenu)>
  c3fefb:	mov    (%rbx),%rax
  c3fefe:	xor    %esi,%esi
  c3ff00:	mov    %rbx,%rdi
  c3ff03:	call   *0x38(%rax)
  c3ff06:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff08:	nopl   0x0(%rax,%rax,1)
  c3ff10:	mov    0x40(%rbx),%rdi
  c3ff14:	xor    %edx,%edx
  c3ff16:	xor    %esi,%esi
  c3ff18:	jmp    c3fef6 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x76>
  c3ff1a:	nopw   0x0(%rax,%rax,1)
  c3ff20:	mov    0x198(%rbx),%rdi
  c3ff27:	xor    %esi,%esi
  c3ff29:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  c3ff2e:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff33:	nopl   0x0(%rax,%rax,1)
  c3ff38:	mov    0x198(%rbx),%rdi
  c3ff3f:	xor    %esi,%esi
  c3ff41:	call   5561d8 <CEGUI::Window::isVisible(bool) const@plt>
  c3ff46:	test   %al,%al
  c3ff48:	je     c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff4e:	mov    0x198(%rbx),%rdi
  c3ff55:	xor    %esi,%esi
  c3ff57:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  c3ff5c:	mov    %rbx,%rdi
  c3ff5f:	call   c3fd00 <CContinueGameMenu::deleteCharacter()>
  c3ff64:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff69:	nopl   0x0(%rax)
  c3ff70:	mov    %rbx,%rdi
  c3ff73:	call   c3e2a0 <CContinueGameMenu::scrollUp()>
  c3ff78:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff7d:	nopl   (%rax)
  c3ff80:	mov    %rbx,%rdi
  c3ff83:	call   c3e2c0 <CContinueGameMenu::scrollDown()>
  c3ff88:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ff8d:	nopl   (%rax)
  c3ff90:	xor    %edx,%edx
  c3ff92:	xor    %esi,%esi
  c3ff94:	mov    %rbx,%rdi
  c3ff97:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3ff9c:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ffa1:	nopl   0x0(%rax)
  c3ffa8:	xor    %edx,%edx
  c3ffaa:	mov    $0x1,%esi
  c3ffaf:	mov    %rbx,%rdi
  c3ffb2:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3ffb7:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ffbc:	nopl   0x0(%rax)
  c3ffc0:	xor    %edx,%edx
  c3ffc2:	mov    $0x2,%esi
  c3ffc7:	mov    %rbx,%rdi
  c3ffca:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3ffcf:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ffd4:	nopl   0x0(%rax)
  c3ffd8:	xor    %edx,%edx
  c3ffda:	mov    $0x3,%esi
  c3ffdf:	mov    %rbx,%rdi
  c3ffe2:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3ffe7:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c3ffec:	nopl   0x0(%rax)
  c3fff0:	xor    %edx,%edx
  c3fff2:	mov    $0x4,%esi
  c3fff7:	mov    %rbx,%rdi
  c3fffa:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3ffff:	jmp    c3fe98 <CContinueGameMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c334e0 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:
  c334e0:	push   %rbx
  c334e1:	cmpb   $0x0,0x30(%rdi)
  c334e5:	mov    %rdi,%rbx
  c334e8:	jne    c334f8 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c334ea:	xor    %eax,%eax
  c334ec:	cmpb   $0x0,0x31(%rdi)
  c334f0:	je     c334f8 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18>
  c334f2:	pop    %rbx
  c334f3:	ret
  c334f4:	nopl   0x0(%rax)
  c334f8:	mov    0x1e8(%rbx),%rdx
  c334ff:	mov    0x1f0(%rbx),%rax
  c33506:	sub    %rdx,%rax
  c33509:	sar    $0x3,%rax
  c3350d:	test   %rax,%rax
  c33510:	jne    c33520 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x40>
  c33512:	mov    $0x1,%eax
  c33517:	pop    %rbx
  c33518:	ret
  c33519:	nopl   0x0(%rax)
  c33520:	movslq 0xc8(%rbx),%rax
  c33527:	xorps  %xmm0,%xmm0
  c3352a:	mov    (%rdx,%rax,8),%rax
  c3352e:	ucomiss 0xe0(%rax),%xmm0
  c33535:	jae    c33512 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x32>
  c33537:	cmp    $0xf,%esi
  c3353a:	je     c33548 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x68>
  c3353c:	jg     c33570 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x90>
  c3353e:	cmp    $0xe,%esi
  c33541:	jne    c33512 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x32>
  c33543:	nopl   0x0(%rax,%rax,1)
  c33548:	mov    0x40(%rbx),%rdi
  c3354c:	xor    %edx,%edx
  c3354e:	mov    $0x2,%esi
  c33553:	call   a828f0 <CGameUI::requestSetGameState(EGameState, EMenu)>
  c33558:	mov    (%rbx),%rax
  c3355b:	mov    %rbx,%rdi
  c3355e:	xor    %esi,%esi
  c33560:	call   *0x38(%rax)
  c33563:	mov    $0x1,%eax
  c33568:	pop    %rbx
  c33569:	ret
  c3356a:	nopw   0x0(%rax,%rax,1)
  c33570:	cmp    $0x10,%esi
  c33573:	je     c33548 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x68>
  c33575:	cmp    $0x11,%esi
  c33578:	jne    c33512 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x32>
  c3357a:	jmp    c33548 <CContinueGameMenu::onDoubleClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x68>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c40010 <CContinueGameMenu::setOpen(bool)>:
  c40010:	test   %sil,%sil
  c40013:	push   %rbx
  c40014:	mov    %rdi,%rbx
  c40017:	jne    c40028 <CContinueGameMenu::setOpen(bool)+0x18>
  c40019:	pop    %rbx
  c4001a:	xor    %esi,%esi
  c4001c:	jmp    b18e50 <CDropdownMenu::setOpen(bool)>
  c40021:	nopl   0x0(%rax)
  c40028:	xor    %esi,%esi
  c4002a:	call   c3e420 <CContinueGameMenu::reloadFiles(bool)>
  c4002f:	mov    $0x1,%esi
  c40034:	mov    %rbx,%rdi
  c40037:	call   b18e50 <CDropdownMenu::setOpen(bool)>
  c4003c:	mov    %rbx,%rdi
  c4003f:	call   c3b2f0 <CContinueGameMenu::updateCharacterList()>
  c40044:	mov    %rbx,%rdi
  c40047:	mov    $0x1,%edx
  c4004c:	xor    %esi,%esi
  c4004e:	pop    %rbx
  c4004f:	jmp    c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c3e2a0 <CContinueGameMenu::scrollUp()>:
  c3e2a0:	mov    0xc4(%rdi),%edx
  c3e2a6:	xor    %eax,%eax
  c3e2a8:	sub    $0x1,%edx
  c3e2ab:	cmovns %edx,%eax
  c3e2ae:	mov    %eax,0xc4(%rdi)
  c3e2b4:	jmp    c3b2f0 <CContinueGameMenu::updateCharacterList()>
  c3e2b9:	nop
  c3e2ba:	nopw   0x0(%rax,%rax,1)

0000000000c3e2c0 <CContinueGameMenu::scrollDown()>:
  c3e2c0:	mov    0x1f0(%rdi),%rax
  c3e2c7:	sub    0x1e8(%rdi),%rax
  c3e2ce:	mov    0xc4(%rdi),%edx
  c3e2d4:	shr    $0x3,%rax
  c3e2d8:	add    $0x1,%edx
  c3e2db:	lea    -0x4(%rax),%ecx
  c3e2de:	mov    %edx,0xc4(%rdi)
  c3e2e4:	cmp    %ecx,%edx
  c3e2e6:	jl     c3e2f6 <CContinueGameMenu::scrollDown()+0x36>
  c3e2e8:	xor    %edx,%edx
  c3e2ea:	sub    $0x5,%eax
  c3e2ed:	cmovns %eax,%edx
  c3e2f0:	mov    %edx,0xc4(%rdi)
  c3e2f6:	jmp    c3b2f0 <CContinueGameMenu::updateCharacterList()>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c3fd00 <CContinueGameMenu::deleteCharacter()>:
  c3fd00:	mov    %rbx,-0x20(%rsp)
  c3fd05:	mov    %rbp,-0x18(%rsp)
  c3fd0a:	mov    %rdi,%rbx
  c3fd0d:	mov    %r12,-0x10(%rsp)
  c3fd12:	mov    %r13,-0x8(%rsp)
  c3fd17:	sub    $0x48,%rsp
  c3fd1b:	mov    0x1f0(%rdi),%rax
  c3fd22:	sub    0x1e8(%rdi),%rax
  c3fd29:	mov    0xc8(%rdi),%r13d
  c3fd30:	sar    $0x3,%rax
  c3fd34:	cmp    %eax,%r13d
  c3fd37:	jge    c3fdd1 <CContinueGameMenu::deleteCharacter()+0xd1>
  c3fd3d:	movslq %r13d,%r13
  c3fd40:	lea    0x10(%rsp),%r12
  c3fd45:	shl    $0x3,%r13
  c3fd49:	add    0x218(%rdi),%r13
  c3fd50:	mov    %rsp,%rdi
  c3fd53:	call   c76730 <FILESYSTEM::GetSaveDataPath()>
  c3fd58:	mov    %rsp,%rsi
  c3fd5b:	mov    %r12,%rdi
  c3fd5e:	mov    %r13,%rdx
  c3fd61:	call   c73aa0 <FILESYSTEM::AssembleAbsolutePath(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  c3fd66:	mov    (%rsp),%rdi
  c3fd6a:	sub    $0x18,%rdi
  c3fd6e:	cmp    $0x1424540,%rdi
  c3fd75:	jne    c3fdf2 <CContinueGameMenu::deleteCharacter()+0xf2>
  c3fd77:	mov    0x10(%rsp),%rdi
  c3fd7c:	call   f61350 <DeleteFile(wchar_t const*)>
  c3fd81:	subl   $0x1,0xc8(%rbx)
  c3fd88:	xor    %eax,%eax
  c3fd8a:	mov    %rbx,%rdi
  c3fd8d:	mov    0xc8(%rbx),%r11d
  c3fd94:	test   %r11d,%r11d
  c3fd97:	cmovns 0xc8(%rbx),%eax
  c3fd9e:	xor    %esi,%esi
  c3fda0:	mov    %eax,0xc8(%rbx)
  c3fda6:	call   c3e420 <CContinueGameMenu::reloadFiles(bool)>
  c3fdab:	mov    0xc8(%rbx),%esi
  c3fdb1:	mov    $0x1,%edx
  c3fdb6:	mov    %rbx,%rdi
  c3fdb9:	call   c3f8c0 <CContinueGameMenu::selectCharacter(int, bool)>
  c3fdbe:	mov    0x10(%rsp),%rdi
  c3fdc3:	mov    $0x1424540,%eax
  c3fdc8:	sub    $0x18,%rdi
  c3fdcc:	cmp    %rdi,%rax
  c3fdcf:	jne    c3fe1b <CContinueGameMenu::deleteCharacter()+0x11b>
  c3fdd1:	mov    %rbx,%rdi
  c3fdd4:	call   c3b2f0 <CContinueGameMenu::updateCharacterList()>
  c3fdd9:	mov    0x28(%rsp),%rbx
  c3fdde:	mov    0x30(%rsp),%rbp
  c3fde3:	mov    0x38(%rsp),%r12
  c3fde8:	mov    0x40(%rsp),%r13
  c3fded:	add    $0x48,%rsp
  c3fdf1:	ret
  c3fdf2:	mov    $0x5541c8,%eax
  c3fdf7:	test   %rax,%rax
  c3fdfa:	je     c3fe6e <CContinueGameMenu::deleteCharacter()+0x16e>
  c3fdfc:	or     $0xffffffff,%eax
  c3fdff:	lock xadd %eax,0x10(%rdi)
  c3fe04:	test   %eax,%eax
  c3fe06:	jg     c3fd77 <CContinueGameMenu::deleteCharacter()+0x77>
  c3fe0c:	lea    0x1f(%rsp),%rsi
  c3fe11:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  c3fe16:	jmp    c3fd77 <CContinueGameMenu::deleteCharacter()+0x77>
  c3fe1b:	mov    $0x5541c8,%eax
  c3fe20:	test   %rax,%rax
  c3fe23:	je     c3fe50 <CContinueGameMenu::deleteCharacter()+0x150>
  c3fe25:	or     $0xffffffff,%eax
  c3fe28:	lock xadd %eax,0x10(%rdi)
  c3fe2d:	test   %eax,%eax
  c3fe2f:	jg     c3fdd1 <CContinueGameMenu::deleteCharacter()+0xd1>
  c3fe31:	lea    0x1e(%rsp),%rsi
  c3fe36:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  c3fe3b:	jmp    c3fdd1 <CContinueGameMenu::deleteCharacter()+0xd1>
  c3fe3d:	mov    %rax,%rbx
  c3fe40:	mov    %rsp,%rdi
  c3fe43:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  c3fe48:	mov    %rbx,%rdi
  c3fe4b:	call   554498 <_Unwind_Resume@plt>
  c3fe50:	mov    0x10(%rdi),%eax
  c3fe53:	lea    -0x1(%rax),%edx
  c3fe56:	mov    %edx,0x10(%rdi)
  c3fe59:	jmp    c3fe2d <CContinueGameMenu::deleteCharacter()+0x12d>
  c3fe5b:	mov    %rax,%rbx
  c3fe5e:	mov    %r12,%rdi
  c3fe61:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  c3fe66:	mov    %rbx,%rdi
  c3fe69:	call   554498 <_Unwind_Resume@plt>
  c3fe6e:	mov    0x10(%rdi),%eax
  c3fe71:	lea    -0x1(%rax),%edx
  c3fe74:	mov    %edx,0x10(%rdi)
  c3fe77:	jmp    c3fe04 <CContinueGameMenu::deleteCharacter()+0x104>
