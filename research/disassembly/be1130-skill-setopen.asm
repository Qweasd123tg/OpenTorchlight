
/mnt/data/ot-original-inputs/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000be1130 <CSkillMenu::setOpen(bool)>:
  be1130:	mov    %rbx,-0x18(%rsp)
  be1135:	mov    %rbp,-0x10(%rsp)
  be113a:	mov    %rdi,%rbx
  be113d:	mov    %r12,-0x8(%rsp)
  be1142:	sub    $0x78,%rsp
  be1146:	cmpb   $0x0,0x38(%rdi)
  be114a:	mov    %esi,%ebp
  be114c:	jne    be1170 <CSkillMenu::setOpen(bool)+0x40>
  be114e:	test   %sil,%sil
  be1151:	jne    be1210 <CSkillMenu::setOpen(bool)+0xe0>
  be1157:	mov    %bpl,0x38(%rbx)
  be115b:	mov    0x60(%rsp),%rbx
  be1160:	mov    0x68(%rsp),%rbp
  be1165:	mov    0x70(%rsp),%r12
  be116a:	add    $0x78,%rsp
  be116e:	ret
  be116f:	nop
  be1170:	test   %sil,%sil
  be1173:	jne    be1157 <CSkillMenu::setOpen(bool)+0x27>
  be1175:	mov    0x750(%rdi),%rax
  be117c:	test   %rax,%rax
  be117f:	je     be1196 <CSkillMenu::setOpen(bool)+0x66>
  be1181:	mov    0x30(%rax),%rsi
  be1185:	mov    0xb0(%rsi),%rdi
  be118c:	test   %rdi,%rdi
  be118f:	je     be1196 <CSkillMenu::setOpen(bool)+0x66>
  be1191:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  be1196:	xorps  %xmm1,%xmm1
  be1199:	mov    0xe8(%rbx),%rdi
  be11a0:	xor    %edx,%edx
  be11a2:	mov    $0x42,%esi
  be11a7:	xor    %ecx,%ecx
  be11a9:	lea    0x10(%rsp),%r12
  be11ae:	movaps %xmm1,%xmm0
  be11b1:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  be11b6:	lea    0x5b(%rsp),%rdx
  be11bb:	mov    $0xfe6008,%esi
  be11c0:	mov    %r12,%rdi
  be11c3:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  be11c8:	mov    0x60(%rbx),%rdi
  be11cc:	movss  0x3c758c(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  be11d4:	movss  0x3c3648(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  be11dc:	xor    %edx,%edx
  be11de:	movss  0x3c3626(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  be11e6:	mov    %r12,%rsi
  be11e9:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  be11ee:	mov    0x10(%rsp),%rdi
  be11f3:	sub    $0x18,%rdi
  be11f7:	cmp    $0x1423a20,%rdi
  be11fe:	jne    be1574 <CSkillMenu::setOpen(bool)+0x444>
  be1204:	movb   $0x0,0x39(%rbx)
  be1208:	jmp    be1157 <CSkillMenu::setOpen(bool)+0x27>
  be120d:	nopl   (%rax)
  be1210:	xorps  %xmm1,%xmm1
  be1213:	mov    0xe8(%rdi),%rdi
  be121a:	xor    %edx,%edx
  be121c:	xor    %ecx,%ecx
  be121e:	mov    $0x16,%esi
  be1223:	lea    0x50(%rsp),%r12
  be1228:	movaps %xmm1,%xmm0
  be122b:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  be1230:	mov    0x48(%rbx),%rdi
  be1234:	mov    0x92a22a(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  be123a:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  be123f:	mov    0x48(%rbx),%rdi
  be1243:	mov    0x92a21f(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  be1249:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  be124e:	mov    0x60(%rbx),%rdi
  be1252:	mov    $0x1,%esi
  be1257:	mov    (%rdi),%rax
  be125a:	call   *0x50(%rax)
  be125d:	lea    0x5f(%rsp),%rdx
  be1262:	mov    $0xfe6008,%esi
  be1267:	mov    %r12,%rdi
  be126a:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  be126f:	mov    0x60(%rbx),%rdi
  be1273:	mov    %r12,%rsi
  be1276:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  be127b:	mov    0x50(%rsp),%rdi
  be1280:	sub    $0x18,%rdi
  be1284:	cmp    $0x1423a20,%rdi
  be128b:	jne    be153e <CSkillMenu::setOpen(bool)+0x40e>
  be1291:	test   %al,%al
  be1293:	je     be13f0 <CSkillMenu::setOpen(bool)+0x2c0>
  be1299:	lea    0x40(%rsp),%r12
  be129e:	lea    0x5e(%rsp),%rdx
  be12a3:	mov    $0xfe600e,%esi
  be12a8:	mov    %r12,%rdi
  be12ab:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  be12b0:	mov    0x60(%rbx),%rdi
  be12b4:	movss  0x3c74a4(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  be12bc:	movss  0x3c3560(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  be12c4:	xor    %edx,%edx
  be12c6:	movss  0x3c353e(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  be12ce:	mov    %r12,%rsi
  be12d1:	call   8a71d0 <CGenericModel::blendAnimation(std::string const&, bool, float, float, float)>
  be12d6:	mov    %r12,%rdi
  be12d9:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  be12de:	lea    0x20(%rsp),%r12
  be12e3:	lea    0x5c(%rsp),%rdx
  be12e8:	mov    $0xfc993a,%esi
  be12ed:	mov    %r12,%rdi
  be12f0:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  be12f5:	mov    0x60(%rbx),%rdi
  be12f9:	movss  0x3c34fb(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  be1301:	movss  0x3c3503(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  be1309:	mov    $0x1,%edx
  be130e:	mov    %r12,%rsi
  be1311:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  be1316:	mov    0x20(%rsp),%rdi
  be131b:	mov    $0x1423a20,%eax
  be1320:	sub    $0x18,%rdi
  be1324:	cmp    %rdi,%rax
  be1327:	jne    be1511 <CSkillMenu::setOpen(bool)+0x3e1>
  be132d:	mov    0x18(%rbx),%rsi
  be1331:	mov    0x10(%rbx),%rdi
  be1335:	call   5561f8 <CEGUI::Window::addChildWindow(CEGUI::Window*)@plt>
  be133a:	mov    0x18(%rbx),%rdi
  be133e:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  be1343:	mov    0xe0(%rbx),%eax
  be1349:	cmp    $0x1,%eax
  be134c:	je     be14a8 <CSkillMenu::setOpen(bool)+0x378>
  be1352:	cmp    $0x2,%eax
  be1355:	je     be1438 <CSkillMenu::setOpen(bool)+0x308>
  be135b:	test   %eax,%eax
  be135d:	jne    be13c3 <CSkillMenu::setOpen(bool)+0x293>
  be135f:	mov    0x90(%rbx),%rdi
  be1366:	mov    $0x1,%esi
  be136b:	movl   $0x0,0xe0(%rbx)
  be1375:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be137a:	mov    0x98(%rbx),%rdi
  be1381:	xor    %esi,%esi
  be1383:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be1388:	mov    0xa0(%rbx),%rdi
  be138f:	xor    %esi,%esi
  be1391:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be1396:	mov    0xb0(%rbx),%rdi
  be139d:	mov    $0x1,%esi
  be13a2:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be13a7:	mov    0xb8(%rbx),%rdi
  be13ae:	xor    %esi,%esi
  be13b0:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be13b5:	mov    0xc0(%rbx),%rdi
  be13bc:	xor    %esi,%esi
  be13be:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be13c3:	mov    (%rbx),%rax
  be13c6:	mov    %rbx,%rdi
  be13c9:	call   *0x48(%rax)
  be13cc:	mov    0x18(%rbx),%rdi
  be13d0:	call   553a38 <CEGUI::Window::moveToBack()@plt>
  be13d5:	mov    0x20(%rbx),%rdi
  be13d9:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  be13de:	mov    0x28(%rbx),%rdi
  be13e2:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  be13e7:	jmp    be1157 <CSkillMenu::setOpen(bool)+0x27>
  be13ec:	nopl   0x0(%rax)
  be13f0:	lea    0x30(%rsp),%r12
  be13f5:	lea    0x5d(%rsp),%rdx
  be13fa:	mov    $0xfe600e,%esi
  be13ff:	mov    %r12,%rdi
  be1402:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  be1407:	mov    0x60(%rbx),%rdi
  be140b:	movss  0x3c734d(%rip),%xmm1        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  be1413:	movss  0x3c3409(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  be141b:	xor    %edx,%edx
  be141d:	mov    %r12,%rsi
  be1420:	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  be1425:	mov    %r12,%rdi
  be1428:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  be142d:	jmp    be12de <CSkillMenu::setOpen(bool)+0x1ae>
  be1432:	nopw   0x0(%rax,%rax,1)
  be1438:	mov    0x90(%rbx),%rdi
  be143f:	xor    %esi,%esi
  be1441:	movl   $0x2,0xe0(%rbx)
  be144b:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be1450:	mov    0x98(%rbx),%rdi
  be1457:	xor    %esi,%esi
  be1459:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be145e:	mov    0xa0(%rbx),%rdi
  be1465:	mov    $0x1,%esi
  be146a:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be146f:	mov    0xb0(%rbx),%rdi
  be1476:	xor    %esi,%esi
  be1478:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be147d:	mov    0xb8(%rbx),%rdi
  be1484:	xor    %esi,%esi
  be1486:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be148b:	mov    0xc0(%rbx),%rdi
  be1492:	mov    $0x1,%esi
  be1497:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be149c:	jmp    be13c3 <CSkillMenu::setOpen(bool)+0x293>
  be14a1:	nopl   0x0(%rax)
  be14a8:	mov    0x90(%rbx),%rdi
  be14af:	xor    %esi,%esi
  be14b1:	movl   $0x1,0xe0(%rbx)
  be14bb:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be14c0:	mov    0x98(%rbx),%rdi
  be14c7:	mov    $0x1,%esi
  be14cc:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be14d1:	mov    0xa0(%rbx),%rdi
  be14d8:	xor    %esi,%esi
  be14da:	call   554718 <CEGUI::Window::setVisible(bool)@plt>
  be14df:	mov    0xb0(%rbx),%rdi
  be14e6:	xor    %esi,%esi
  be14e8:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be14ed:	mov    0xb8(%rbx),%rdi
  be14f4:	mov    $0x1,%esi
  be14f9:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be14fe:	mov    0xc0(%rbx),%rdi
  be1505:	xor    %esi,%esi
  be1507:	call   554dc8 <CEGUI::RadioButton::setSelected(bool)@plt>
  be150c:	jmp    be13c3 <CSkillMenu::setOpen(bool)+0x293>
  be1511:	mov    $0x5541c8,%eax
  be1516:	test   %rax,%rax
  be1519:	je     be15d2 <CSkillMenu::setOpen(bool)+0x4a2>
  be151f:	or     $0xffffffff,%eax
  be1522:	lock xadd %eax,0x10(%rdi)
  be1527:	test   %eax,%eax
  be1529:	jg     be132d <CSkillMenu::setOpen(bool)+0x1fd>
  be152f:	lea    0x59(%rsp),%rsi
  be1534:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  be1539:	jmp    be132d <CSkillMenu::setOpen(bool)+0x1fd>
  be153e:	mov    $0x5541c8,%edx
  be1543:	test   %rdx,%rdx
  be1546:	je     be15e6 <CSkillMenu::setOpen(bool)+0x4b6>
  be154c:	or     $0xffffffff,%edx
  be154f:	lock xadd %edx,0x10(%rdi)
  be1554:	test   %edx,%edx
  be1556:	jg     be1291 <CSkillMenu::setOpen(bool)+0x161>
  be155c:	lea    0x5a(%rsp),%rsi
  be1561:	mov    %al,0x8(%rsp)
  be1565:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  be156a:	movzbl 0x8(%rsp),%eax
  be156f:	jmp    be1291 <CSkillMenu::setOpen(bool)+0x161>
  be1574:	mov    $0x5541c8,%eax
  be1579:	test   %rax,%rax
  be157c:	je     be15b9 <CSkillMenu::setOpen(bool)+0x489>
  be157e:	or     $0xffffffff,%eax
  be1581:	lock xadd %eax,0x10(%rdi)
  be1586:	test   %eax,%eax
  be1588:	jg     be1204 <CSkillMenu::setOpen(bool)+0xd4>
  be158e:	lea    0x58(%rsp),%rsi
  be1593:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  be1598:	jmp    be1204 <CSkillMenu::setOpen(bool)+0xd4>
  be159d:	mov    %r12,%rdi
  be15a0:	mov    %rax,%rbx
  be15a3:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  be15a8:	mov    %rbx,%rdi
  be15ab:	call   554498 <_Unwind_Resume@plt>
  be15b0:	jmp    be159d <CSkillMenu::setOpen(bool)+0x46d>
  be15b2:	mov    %rax,%rbx
  be15b5:	jmp    be15a8 <CSkillMenu::setOpen(bool)+0x478>
  be15b7:	jmp    be15b2 <CSkillMenu::setOpen(bool)+0x482>
  be15b9:	mov    0x10(%rdi),%eax
  be15bc:	lea    -0x1(%rax),%edx
  be15bf:	mov    %edx,0x10(%rdi)
  be15c2:	jmp    be1586 <CSkillMenu::setOpen(bool)+0x456>
  be15c4:	jmp    be15b2 <CSkillMenu::setOpen(bool)+0x482>
  be15c6:	jmp    be159d <CSkillMenu::setOpen(bool)+0x46d>
  be15c8:	nopl   0x0(%rax,%rax,1)
  be15d0:	jmp    be159d <CSkillMenu::setOpen(bool)+0x46d>
  be15d2:	mov    0x10(%rdi),%eax
  be15d5:	lea    -0x1(%rax),%edx
  be15d8:	mov    %edx,0x10(%rdi)
  be15db:	jmp    be1527 <CSkillMenu::setOpen(bool)+0x3f7>
  be15e0:	jmp    be159d <CSkillMenu::setOpen(bool)+0x46d>
  be15e2:	jmp    be15b2 <CSkillMenu::setOpen(bool)+0x482>
  be15e4:	jmp    be15b2 <CSkillMenu::setOpen(bool)+0x482>
  be15e6:	mov    0x10(%rdi),%edx
  be15e9:	lea    -0x1(%rdx),%ecx
  be15ec:	mov    %ecx,0x10(%rdi)
  be15ef:	nop
  be15f0:	jmp    be1554 <CSkillMenu::setOpen(bool)+0x424>
