
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000ab4f80 <CGameUI::handleKeyPresses()>:
  ab4f80:	push   %r15
  ab4f82:	push   %r14
  ab4f84:	push   %r13
  ab4f86:	push   %r12
  ab4f88:	push   %rbp
  ab4f89:	mov    %rdi,%rbp
  ab4f8c:	push   %rbx
  ab4f8d:	sub    $0x198,%rsp
  ab4f94:	cmpq   $0x0,0x1308(%rdi)
  ab4f9c:	je     ab5930 <CGameUI::handleKeyPresses()+0x9b0>
  ab4fa2:	mov    0xa566a0(%rip),%ebx        # 150b648 <KSETTINGS_KEYMAP_CONSOLE_HOLD>
  ab4fa8:	lea    0x590(%rbp),%r15
  ab4faf:	call   a54490 <CMasterResourceManager::getSingleton()>
  ab4fb4:	mov    0x90(%rax),%rdi
  ab4fbb:	mov    %ebx,%esi
  ab4fbd:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab4fc2:	test   %eax,%eax
  ab4fc4:	jle    ab4fed <CGameUI::handleKeyPresses()+0x6d>
  ab4fc6:	mov    0xa5667c(%rip),%ebx        # 150b648 <KSETTINGS_KEYMAP_CONSOLE_HOLD>
  ab4fcc:	call   a54490 <CMasterResourceManager::getSingleton()>
  ab4fd1:	mov    0x90(%rax),%rdi
  ab4fd8:	mov    %ebx,%esi
  ab4fda:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab4fdf:	mov    %r15,%rdi
  ab4fe2:	mov    %eax,%esi
  ab4fe4:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  ab4fe9:	test   %al,%al
  ab4feb:	je     ab5049 <CGameUI::handleKeyPresses()+0xc9>
  ab4fed:	mov    0xa56651(%rip),%ebx        # 150b644 <KSETTINGS_KEYMAP_CONSOLE_PRESS>
  ab4ff3:	call   a54490 <CMasterResourceManager::getSingleton()>
  ab4ff8:	mov    0x90(%rax),%rdi
  ab4fff:	mov    %ebx,%esi
  ab5001:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab5006:	mov    %r15,%rdi
  ab5009:	mov    %eax,%esi
  ab500b:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5010:	test   %al,%al
  ab5012:	je     ab5049 <CGameUI::handleKeyPresses()+0xc9>
  ab5014:	mov    %rbp,%rdi
  ab5017:	movb   $0x0,0x12fb(%rbp)
  ab501e:	movl   $0xffffffff,0x1674(%rbp)
  ab5028:	movl   $0xffffffff,0x1678(%rbp)
  ab5032:	movl   $0xffffffff,0x167c(%rbp)
  ab503c:	call   a84230 <CGameUI::captureProcessInput()>
  ab5041:	mov    %rbp,%rdi
  ab5044:	call   a8e560 <CGameUI::toggleConsole()>
  ab5049:	mov    0x1690(%rbp),%rdi
  ab5050:	call   ae1df0 <CConsole::getVisible()>
  ab5055:	test   %al,%al
  ab5057:	jne    ab5948 <CGameUI::handleKeyPresses()+0x9c8>
  ab505d:	mov    0x78(%rbp),%rdi
  ab5061:	mov    0xa5658d(%rip),%esi        # 150b5f4 <KSETTINGS_KEYMAP_INVENTORY>
  ab5067:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab506c:	mov    %r15,%rdi
  ab506f:	mov    %eax,%esi
  ab5071:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5076:	test   %al,%al
  ab5078:	je     ab59b0 <CGameUI::handleKeyPresses()+0xa30>
  ab507e:	mov    %rbp,%rdi
  ab5081:	movb   $0x0,0xa04b28(%rip)        # 14b9bb0 <gToggleInventory>
  ab5088:	call   a8ea20 <CGameUI::toggleInventory()>
  ab508d:	mov    0x78(%rbp),%rdi
  ab5091:	mov    0xa5659d(%rip),%esi        # 150b634 <KSETTINGS_KEYMAP_WEAPONSET>
  ab5097:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab509c:	mov    %r15,%rdi
  ab509f:	mov    %eax,%esi
  ab50a1:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab50a6:	test   %al,%al
  ab50a8:	je     ab50d8 <CGameUI::handleKeyPresses()+0x158>
  ab50aa:	cmpq   $0x0,0x4d8(%rbp)
  ab50b2:	je     ab50d8 <CGameUI::handleKeyPresses()+0x158>
  ab50b4:	mov    0x38(%rbp),%rdi
  ab50b8:	call   813410 <CCharacter::hasWeaponsInOffSet()>
  ab50bd:	test   %al,%al
  ab50bf:	je     ab5c40 <CGameUI::handleKeyPresses()+0xcc0>
  ab50c5:	mov    0x4d8(%rbp),%rdi
  ab50cc:	call   b45e90 <CInventoryMenu::toggleWeaponSet()>
  ab50d1:	nopl   0x0(%rax)
  ab50d8:	mov    0x78(%rbp),%rdi
  ab50dc:	mov    0xa5651e(%rip),%esi        # 150b600 <KSETTINGS_KEYMAP_SKILLS>
  ab50e2:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab50e7:	mov    %r15,%rdi
  ab50ea:	mov    %eax,%esi
  ab50ec:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab50f1:	test   %al,%al
  ab50f3:	jne    ab5a48 <CGameUI::handleKeyPresses()+0xac8>
  ab50f9:	mov    0x78(%rbp),%rdi
  ab50fd:	mov    0xa56505(%rip),%esi        # 150b608 <KSETTINGS_KEYMAP_JOURNAL>
  ab5103:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab5108:	mov    %r15,%rdi
  ab510b:	mov    %eax,%esi
  ab510d:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5112:	test   %al,%al
  ab5114:	jne    ab5a68 <CGameUI::handleKeyPresses()+0xae8>
  ab511a:	mov    0x78(%rbp),%rdi
  ab511e:	mov    0xa564e0(%rip),%esi        # 150b604 <KSETTINGS_KEYMAP_QUESTS>
  ab5124:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab5129:	mov    %r15,%rdi
  ab512c:	mov    %eax,%esi
  ab512e:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5133:	test   %al,%al
  ab5135:	jne    ab5a58 <CGameUI::handleKeyPresses()+0xad8>
  ab513b:	mov    0x78(%rbp),%rdi
  ab513f:	mov    0xa564b7(%rip),%esi        # 150b5fc <KSETTINGS_KEYMAP_STATS>
  ab5145:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab514a:	mov    %r15,%rdi
  ab514d:	mov    %eax,%esi
  ab514f:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5154:	test   %al,%al
  ab5156:	je     ab5998 <CGameUI::handleKeyPresses()+0xa18>
  ab515c:	mov    %rbp,%rdi
  ab515f:	movb   $0x0,0xa048fb(%rip)        # 14b9a61 <gToggleStats>
  ab5166:	call   a8e6a0 <CGameUI::toggleStats()>
  ab516b:	mov    0x78(%rbp),%rdi
  ab516f:	mov    0xa56483(%rip),%esi        # 150b5f8 <KSETTINGS_KEYMAP_PET>
  ab5175:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab517a:	mov    %r15,%rdi
  ab517d:	mov    %eax,%esi
  ab517f:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5184:	test   %al,%al
  ab5186:	je     ab5980 <CGameUI::handleKeyPresses()+0xa00>
  ab518c:	mov    %rbp,%rdi
  ab518f:	movb   $0x0,0xa048ca(%rip)        # 14b9a60 <gTogglePet>
  ab5196:	call   a8e5f0 <CGameUI::togglePet()>
  ab519b:	mov    0x78(%rbp),%rdi
  ab519f:	mov    0xa5648b(%rip),%esi        # 150b630 <KSETTINGS_KEYMAP_SWAPSKILLS>
  ab51a5:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab51aa:	mov    %r15,%rdi
  ab51ad:	mov    %eax,%esi
  ab51af:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab51b4:	test   %al,%al
  ab51b6:	jne    ab5a78 <CGameUI::handleKeyPresses()+0xaf8>
  ab51bc:	cmpq   $0x0,0x40(%rbp)
  ab51c1:	je     ab58ee <CGameUI::handleKeyPresses()+0x96e>
  ab51c7:	mov    0x78(%rbp),%rdi
  ab51cb:	mov    0xa56443(%rip),%esi        # 150b614 <KSETTINGS_KEYMAP_AUTOMAP>
  ab51d1:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab51d6:	mov    %r15,%rdi
  ab51d9:	mov    %eax,%esi
  ab51db:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab51e0:	test   %al,%al
  ab51e2:	je     ab51f1 <CGameUI::handleKeyPresses()+0x271>
  ab51e4:	cmpb   $0x0,0x1999(%rbp)
  ab51eb:	je     ab5a00 <CGameUI::handleKeyPresses()+0xa80>
  ab51f1:	mov    0x78(%rbp),%rdi
  ab51f5:	mov    0xa56421(%rip),%esi        # 150b61c <KSETTINGS_KEYMAP_AUTOMAPZOOMOUT>
  ab51fb:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab5200:	mov    %r15,%rdi
  ab5203:	mov    %eax,%esi
  ab5205:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab520a:	test   %al,%al
  ab520c:	jne    ab5bd0 <CGameUI::handleKeyPresses()+0xc50>
  ab5212:	mov    0x78(%rbp),%rdi
  ab5216:	mov    0xa563fc(%rip),%esi        # 150b618 <KSETTINGS_KEYMAP_AUTOMAPZOOMIN>
  ab521c:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab5221:	mov    %r15,%rdi
  ab5224:	mov    %eax,%esi
  ab5226:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab522b:	test   %al,%al
  ab522d:	jne    ab5bb0 <CGameUI::handleKeyPresses()+0xc30>
  ab5233:	mov    $0x90,%esi
  ab5238:	mov    %r15,%rdi
  ab523b:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5240:	test   %al,%al
  ab5242:	je     ab58d9 <CGameUI::handleKeyPresses()+0x959>
  ab5248:	mov    0x40(%rbp),%rax
  ab524c:	lea    0x170(%rsp),%r12
  ab5254:	lea    0x160(%rsp),%rbx
  ab525c:	mov    %r12,%rdi
  ab525f:	mov    0x228(%rax),%esi
  ab5265:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  ab526a:	mov    %r12,%rdx
  ab526d:	mov    $0xfe4edc,%esi
  ab5272:	mov    %rbx,%rdi
  ab5275:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  ab527a:	lea    0xf0(%rsp),%rax
  ab5282:	mov    %rbx,%rsi
  ab5285:	mov    %rax,%rdi
  ab5288:	mov    %rax,0x28(%rsp)
  ab528d:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab5292:	mov    $0xfe4ef8,%edi
  ab5297:	call   554608 <wcslen@plt>
  ab529c:	mov    0x28(%rsp),%rdi
  ab52a1:	mov    %rax,%rdx
  ab52a4:	mov    $0xfe4ef8,%esi
  ab52a9:	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  ab52ae:	mov    0x160(%rsp),%rdi
  ab52b6:	sub    $0x18,%rdi
  ab52ba:	cmp    $0x1424540,%rdi
  ab52c1:	jne    ab5df2 <CGameUI::handleKeyPresses()+0xe72>
  ab52c7:	mov    0x170(%rsp),%rdi
  ab52cf:	mov    $0x1424540,%ecx
  ab52d4:	sub    $0x18,%rdi
  ab52d8:	cmp    %rdi,%rcx
  ab52db:	jne    ab5e1e <CGameUI::handleKeyPresses()+0xe9e>
  ab52e1:	mov    0x40(%rbp),%rax
  ab52e5:	lea    0x150(%rsp),%r13
  ab52ed:	mov    %r13,%rdi
  ab52f0:	mov    0x1a4(%rax),%esi
  ab52f6:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  ab52fb:	lea    0x140(%rsp),%r12
  ab5303:	mov    %r13,%rdx
  ab5306:	mov    $0xfe5ad0,%esi
  ab530b:	mov    %r12,%rdi
  ab530e:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  ab5313:	lea    0x130(%rsp),%rbx
  ab531b:	mov    %r12,%rsi
  ab531e:	mov    %rbx,%rdi
  ab5321:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab5326:	mov    $0xfe4ef8,%edi
  ab532b:	call   554608 <wcslen@plt>
  ab5330:	mov    $0xfe4ef8,%esi
  ab5335:	mov    %rax,%rdx
  ab5338:	mov    %rbx,%rdi
  ab533b:	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  ab5340:	mov    0x28(%rsp),%rdi
  ab5345:	mov    %rbx,%rsi
  ab5348:	call   552d28 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab534d:	mov    0x130(%rsp),%rdi
  ab5355:	mov    $0x1424540,%eax
  ab535a:	sub    $0x18,%rdi
  ab535e:	cmp    %rdi,%rax
  ab5361:	jne    ab5ef7 <CGameUI::handleKeyPresses()+0xf77>
  ab5367:	mov    0x140(%rsp),%rdi
  ab536f:	mov    $0x1424540,%ecx
  ab5374:	sub    $0x18,%rdi
  ab5378:	cmp    %rdi,%rcx
  ab537b:	jne    ab5f23 <CGameUI::handleKeyPresses()+0xfa3>
  ab5381:	mov    0x150(%rsp),%rdi
  ab5389:	mov    $0x1424540,%eax
  ab538e:	sub    $0x18,%rdi
  ab5392:	cmp    %rdi,%rax
  ab5395:	jne    ab5f65 <CGameUI::handleKeyPresses()+0xfe5>
  ab539b:	mov    0x38(%rbp),%rdi
  ab539f:	test   %rdi,%rdi
  ab53a2:	je     ab5888 <CGameUI::handleKeyPresses()+0x908>
  ab53a8:	cmpq   $0x0,0x40(%rbp)
  ab53ad:	je     ab5888 <CGameUI::handleKeyPresses()+0x908>
  ab53b3:	mov    $0x1,%esi
  ab53b8:	call   9e7080 <CPositionableObject::getPosition(bool)>
  ab53bd:	movq   %xmm0,0x8(%rsp)
  ab53c3:	mov    0x8(%rsp),%rax
  ab53c8:	lea    0xa0(%rsp),%rsi
  ab53d0:	movss  %xmm1,0x38(%rsp)
  ab53d6:	mov    %rax,0x30(%rsp)
  ab53db:	mov    %rax,0xa0(%rsp)
  ab53e3:	mov    0x38(%rsp),%eax
  ab53e7:	mov    %eax,0xa8(%rsp)
  ab53ee:	mov    0x40(%rbp),%rdi
  ab53f2:	call   945110 <CLevel::getRoomThatPositionIsIn(Ogre::Vector3 const&)>
  ab53f7:	test   %rax,%rax
  ab53fa:	je     ab5888 <CGameUI::handleKeyPresses()+0x908>
  ab5400:	lea    0x168(%rax),%rsi
  ab5407:	lea    0x120(%rsp),%rdi
  ab540f:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab5414:	mov    0x971025(%rip),%rdx        # 1426440 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_Rep::_S_empty_rep_storage>
  ab541b:	lea    0x60(%rsp),%rdi
  ab5420:	xor    %ecx,%ecx
  ab5422:	xor    %esi,%esi
  ab5424:	movq   $0x1426458,0x60(%rsp)
  ab542d:	movq   $0x0,0x78(%rsp)
  ab5436:	movl   $0x0,0x68(%rsp)
  ab543e:	movq   $0x0,0x70(%rsp)
  ab5447:	call   56b4b0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_M_mutate(unsigned long, unsigned long, unsigned long)>
  ab544c:	mov    0x120(%rsp),%rax
  ab5454:	lea    0x60(%rsp),%rdi
  ab5459:	mov    -0x18(%rax),%rsi
  ab545d:	call   56b2c0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::reserve(unsigned long)>
  ab5462:	mov    0x120(%rsp),%rbx
  ab546a:	mov    -0x18(%rbx),%rax
  ab546e:	lea    (%rbx,%rax,4),%rax
  ab5472:	cmp    %rax,%rbx
  ab5475:	mov    %rax,0x18(%rsp)
  ab547a:	je     ab557e <CGameUI::handleKeyPresses()+0x5fe>
  ab5480:	movw   $0x0,0x20(%rsp)
  ab5487:	nopw   0x0(%rax,%rax,1)
  ab5490:	mov    (%rbx),%eax
  ab5492:	mov    $0x1,%r12d
  ab5498:	cmp    $0xffff,%eax
  ab549d:	mov    %eax,%r14d
  ab54a0:	jbe    ab54ca <CGameUI::handleKeyPresses()+0x54a>
  ab54a2:	sub    $0x10000,%eax
  ab54a7:	mov    $0x2,%r12b
  ab54aa:	mov    %eax,%r14d
  ab54ad:	and    $0x3ff,%ax
  ab54b1:	shr    $0xa,%r14d
  ab54b5:	sub    $0x2400,%ax
  ab54b9:	and    $0x3ff,%r14w
  ab54bf:	mov    %ax,0x20(%rsp)
  ab54c4:	sub    $0x2800,%r14w
  ab54ca:	mov    0x60(%rsp),%rax
  ab54cf:	mov    -0x18(%rax),%rdx
  ab54d3:	lea    0x1(%rdx),%r13
  ab54d7:	cmp    -0x10(%rax),%r13
  ab54db:	ja     ab54e8 <CGameUI::handleKeyPresses()+0x568>
  ab54dd:	mov    -0x8(%rax),%edi
  ab54e0:	test   %edi,%edi
  ab54e2:	jle    ab54fe <CGameUI::handleKeyPresses()+0x57e>
  ab54e4:	nopl   0x0(%rax)
  ab54e8:	lea    0x60(%rsp),%rdi
  ab54ed:	mov    %r13,%rsi
  ab54f0:	call   56b2c0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::reserve(unsigned long)>
  ab54f5:	mov    0x60(%rsp),%rax
  ab54fa:	mov    -0x18(%rax),%rdx
  ab54fe:	mov    %r14w,(%rax,%rdx,2)
  ab5503:	mov    0x60(%rsp),%rax
  ab5508:	lea    -0x18(%rax),%rdx
  ab550c:	cmp    $0x1426440,%rdx
  ab5513:	jne    ab5ce1 <CGameUI::handleKeyPresses()+0xd61>
  ab5519:	cmp    $0x2,%r12
  ab551d:	jne    ab556f <CGameUI::handleKeyPresses()+0x5ef>
  ab551f:	mov    0x60(%rsp),%rax
  ab5524:	mov    -0x18(%rax),%rdx
  ab5528:	lea    0x1(%rdx),%r12
  ab552c:	cmp    -0x10(%rax),%r12
  ab5530:	ja     ab5539 <CGameUI::handleKeyPresses()+0x5b9>
  ab5532:	mov    -0x8(%rax),%esi
  ab5535:	test   %esi,%esi
  ab5537:	jle    ab554f <CGameUI::handleKeyPresses()+0x5cf>
  ab5539:	lea    0x60(%rsp),%rdi
  ab553e:	mov    %r12,%rsi
  ab5541:	call   56b2c0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::reserve(unsigned long)>
  ab5546:	mov    0x60(%rsp),%rax
  ab554b:	mov    -0x18(%rax),%rdx
  ab554f:	movzwl 0x20(%rsp),%ecx
  ab5554:	mov    %cx,(%rax,%rdx,2)
  ab5558:	mov    0x60(%rsp),%rax
  ab555d:	mov    $0x1426440,%ecx
  ab5562:	lea    -0x18(%rax),%rdx
  ab5566:	cmp    %rdx,%rcx
  ab5569:	jne    ab5cc9 <CGameUI::handleKeyPresses()+0xd49>
  ab556f:	add    $0x4,%rbx
  ab5573:	cmp    %rbx,0x18(%rsp)
  ab5578:	jne    ab5490 <CGameUI::handleKeyPresses()+0x510>
  ab557e:	lea    0xb0(%rsp),%rbx
  ab5586:	lea    0x189(%rsp),%rdx
  ab558e:	mov    $0xfe4d98,%esi
  ab5593:	movq   $0x1426458,0x80(%rsp)
  ab559f:	movq   $0x0,0x98(%rsp)
  ab55ab:	mov    %rbx,%rdi
  ab55ae:	movl   $0x0,0x88(%rsp)
  ab55b9:	movq   $0x0,0x90(%rsp)
  ab55c5:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  ab55ca:	lea    0x80(%rsp),%rcx
  ab55d2:	mov    %rbx,%rsi
  ab55d5:	mov    %rcx,%rdi
  ab55d8:	mov    %rcx,0x20(%rsp)
  ab55dd:	call   56d680 <Ogre::UTFString::assign(std::string const&)>
  ab55e2:	mov    0xb0(%rsp),%rdi
  ab55ea:	sub    $0x18,%rdi
  ab55ee:	cmp    $0x1423a20,%rdi
  ab55f5:	jne    ab5d6d <CGameUI::handleKeyPresses()+0xded>
  ab55fb:	mov    0x20(%rsp),%rsi
  ab5600:	lea    0x60(%rsp),%rdx
  ab5605:	lea    0x40(%rsp),%rdi
  ab560a:	call   56dc60 <Ogre::operator+(Ogre::UTFString const&, Ogre::UTFString const&)>
  ab560f:	mov    0x48(%rsp),%eax
  ab5613:	cmp    $0x2,%eax
  ab5616:	je     ab5c5a <CGameUI::handleKeyPresses()+0xcda>
  ab561c:	cmpq   $0x0,0x58(%rsp)
  ab5622:	je     ab5648 <CGameUI::handleKeyPresses()+0x6c8>
  ab5624:	cmp    $0x3,%eax
  ab5627:	je     ab5c09 <CGameUI::handleKeyPresses()+0xc89>
  ab562d:	cmp    $0x1,%eax
  ab5630:	je     ab5c65 <CGameUI::handleKeyPresses()+0xce5>
  ab5636:	movq   $0x0,0x58(%rsp)
  ab563f:	movq   $0x0,0x50(%rsp)
  ab5648:	mov    $0x8,%edi
  ab564d:	call   552d68 <operator new(unsigned long)@plt>
  ab5652:	movq   $0x1424558,(%rax)
  ab5659:	mov    %rax,%rdi
  ab565c:	mov    %rax,0x58(%rsp)
  ab5661:	movl   $0x2,0x48(%rsp)
  ab5669:	call   553348 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::clear()@plt>
  ab566e:	mov    0x40(%rsp),%rax
  ab5673:	mov    0x58(%rsp),%r12
  ab5678:	mov    -0x18(%rax),%rsi
  ab567c:	mov    %r12,%rdi
  ab567f:	call   5542c8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::reserve(unsigned long)@plt>
  ab5684:	lea    0x40(%rsp),%rdi
  ab5689:	call   591d30 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_M_leak()>
  ab568e:	mov    0x40(%rsp),%rax
  ab5693:	lea    0x40(%rsp),%rdi
  ab5698:	mov    -0x18(%rax),%rdx
  ab569c:	lea    (%rax,%rdx,2),%rdx
  ab56a0:	mov    %rdx,0x18(%rsp)
  ab56a5:	call   591d30 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_M_leak()>
  ab56aa:	mov    0x40(%rsp),%rax
  ab56af:	mov    %rax,%rbx
  ab56b2:	nopw   0x0(%rax,%rax,1)
  ab56b8:	cmp    %rbx,0x18(%rsp)
  ab56bd:	je     ab5833 <CGameUI::handleKeyPresses()+0x8b3>
  ab56c3:	mov    -0x8(%rax),%ecx
  ab56c6:	lea    -0x18(%rax),%rdx
  ab56ca:	test   %ecx,%ecx
  ab56cc:	js     ab5700 <CGameUI::handleKeyPresses()+0x780>
  ab56ce:	cmp    $0x1426440,%rdx
  ab56d5:	je     ab5700 <CGameUI::handleKeyPresses()+0x780>
  ab56d7:	test   %ecx,%ecx
  ab56d9:	je     ab56f4 <CGameUI::handleKeyPresses()+0x774>
  ab56db:	lea    0x40(%rsp),%rdi
  ab56e0:	xor    %ecx,%ecx
  ab56e2:	xor    %edx,%edx
  ab56e4:	xor    %esi,%esi
  ab56e6:	call   56b4b0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_M_mutate(unsigned long, unsigned long, unsigned long)>
  ab56eb:	mov    0x40(%rsp),%rdx
  ab56f0:	sub    $0x18,%rdx
  ab56f4:	movl   $0xffffffff,0x10(%rdx)
  ab56fb:	mov    0x40(%rsp),%rax
  ab5700:	mov    %rbx,%rdx
  ab5703:	sub    %rax,%rdx
  ab5706:	sar    $1,%rdx
  ab5709:	movzwl (%rax,%rdx,2),%r14d
  ab570e:	lea    0x2800(%r14),%ecx
  ab5715:	cmp    $0x3ff,%cx
  ab571a:	ja     ab5c00 <CGameUI::handleKeyPresses()+0xc80>
  ab5720:	add    $0x1,%rdx
  ab5724:	cmp    -0x18(%rax),%rdx
  ab5728:	jae    ab5c00 <CGameUI::handleKeyPresses()+0xc80>
  ab572e:	movzwl (%rax,%rdx,2),%eax
  ab5732:	add    $0x2400,%ax
  ab5736:	cmp    $0x3ff,%ax
  ab573a:	ja     ab5c00 <CGameUI::handleKeyPresses()+0xc80>
  ab5740:	mov    %eax,%r14d
  ab5743:	and    $0x3ff,%ecx
  ab5749:	and    $0x3ff,%r14d
  ab5750:	shl    $0xa,%ecx
  ab5753:	or     %ecx,%r14d
  ab5756:	add    $0x10000,%r14d
  ab575d:	mov    (%r12),%rax
  ab5761:	mov    -0x18(%rax),%rdx
  ab5765:	lea    0x1(%rdx),%r13
  ab5769:	cmp    -0x10(%rax),%r13
  ab576d:	ja     ab5776 <CGameUI::handleKeyPresses()+0x7f6>
  ab576f:	mov    -0x8(%rax),%ecx
  ab5772:	test   %ecx,%ecx
  ab5774:	jle    ab5789 <CGameUI::handleKeyPresses()+0x809>
  ab5776:	mov    %r13,%rsi
  ab5779:	mov    %r12,%rdi
  ab577c:	call   5542c8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::reserve(unsigned long)@plt>
  ab5781:	mov    (%r12),%rax
  ab5785:	mov    -0x18(%rax),%rdx
  ab5789:	mov    %r14d,(%rax,%rdx,4)
  ab578d:	mov    (%r12),%rax
  ab5791:	mov    $0x1424540,%ecx
  ab5796:	lea    -0x18(%rax),%rdx
  ab579a:	cmp    %rdx,%rcx
  ab579d:	jne    ab5cb0 <CGameUI::handleKeyPresses()+0xd30>
  ab57a3:	mov    0x40(%rsp),%rax
  ab57a8:	mov    -0x8(%rax),%ecx
  ab57ab:	lea    -0x18(%rax),%rdx
  ab57af:	test   %ecx,%ecx
  ab57b1:	js     ab57e9 <CGameUI::handleKeyPresses()+0x869>
  ab57b3:	cmp    $0x1426440,%rdx
  ab57ba:	je     ab57e9 <CGameUI::handleKeyPresses()+0x869>
  ab57bc:	test   %ecx,%ecx
  ab57be:	je     ab57d9 <CGameUI::handleKeyPresses()+0x859>
  ab57c0:	lea    0x40(%rsp),%rdi
  ab57c5:	xor    %ecx,%ecx
  ab57c7:	xor    %edx,%edx
  ab57c9:	xor    %esi,%esi
  ab57cb:	call   56b4b0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::_M_mutate(unsigned long, unsigned long, unsigned long)>
  ab57d0:	mov    0x40(%rsp),%rdx
  ab57d5:	sub    $0x18,%rdx
  ab57d9:	movl   $0xffffffff,0x10(%rdx)
  ab57e0:	mov    0x40(%rsp),%rax
  ab57e5:	lea    -0x18(%rax),%rdx
  ab57e9:	mov    (%rdx),%rdx
  ab57ec:	lea    0x2(%rbx),%rcx
  ab57f0:	lea    (%rax,%rdx,2),%rdx
  ab57f4:	cmp    %rdx,%rcx
  ab57f7:	je     ab5bf0 <CGameUI::handleKeyPresses()+0xc70>
  ab57fd:	movzwl 0x2(%rbx),%edx
  ab5801:	add    $0x2400,%dx
  ab5806:	cmp    $0x3ff,%dx
  ab580b:	ja     ab5bf0 <CGameUI::handleKeyPresses()+0xc70>
  ab5811:	movzwl (%rbx),%edx
  ab5814:	add    $0x2800,%dx
  ab5819:	cmp    $0x3ff,%dx
  ab581e:	ja     ab5bf0 <CGameUI::handleKeyPresses()+0xc70>
  ab5824:	add    $0x4,%rbx
  ab5828:	cmp    %rbx,0x18(%rsp)
  ab582d:	jne    ab56c3 <CGameUI::handleKeyPresses()+0x743>
  ab5833:	lea    0x110(%rsp),%rbx
  ab583b:	mov    0x58(%rsp),%rsi
  ab5840:	mov    %rbx,%rdi
  ab5843:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab5848:	mov    0x28(%rsp),%rdi
  ab584d:	mov    %rbx,%rsi
  ab5850:	call   552d28 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab5855:	mov    %rbx,%rdi
  ab5858:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab585d:	lea    0x40(%rsp),%rdi
  ab5862:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab5867:	mov    0x20(%rsp),%rdi
  ab586c:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab5871:	lea    0x60(%rsp),%rdi
  ab5876:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab587b:	lea    0x120(%rsp),%rdi
  ab5883:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5888:	lea    0x100(%rsp),%rbx
  ab5890:	mov    0x28(%rsp),%rsi
  ab5895:	mov    %rbx,%rdi
  ab5898:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  ab589d:	mov    %rbx,%rdi
  ab58a0:	call   c93080 <UTILITIES::SetClipBoardText(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  ab58a5:	mov    0x100(%rsp),%rdi
  ab58ad:	mov    $0x1424540,%eax
  ab58b2:	sub    $0x18,%rdi
  ab58b6:	cmp    %rdi,%rax
  ab58b9:	jne    ab5eb5 <CGameUI::handleKeyPresses()+0xf35>
  ab58bf:	mov    0xf0(%rsp),%rdi
  ab58c7:	mov    $0x1424540,%ecx
  ab58cc:	sub    $0x18,%rdi
  ab58d0:	cmp    %rdi,%rcx
  ab58d3:	jne    ab5f91 <CGameUI::handleKeyPresses()+0x1011>
  ab58d9:	mov    $0x10,%esi
  ab58de:	mov    %r15,%rdi
  ab58e1:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  ab58e6:	test   %al,%al
  ab58e8:	jne    ab5ab0 <CGameUI::handleKeyPresses()+0xb30>
  ab58ee:	mov    0x78(%rbp),%rdi
  ab58f2:	mov    0xa55d34(%rip),%esi        # 150b62c <KSETTINGS_KEYMAP_CYCLESKILLDOWN>
  ab58f8:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab58fd:	mov    %r15,%rdi
  ab5900:	mov    %eax,%esi
  ab5902:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5907:	test   %al,%al
  ab5909:	jne    ab5a10 <CGameUI::handleKeyPresses()+0xa90>
  ab590f:	mov    0x78(%rbp),%rdi
  ab5913:	mov    0xa55d0f(%rip),%esi        # 150b628 <KSETTINGS_KEYMAP_CYCLESKILLUP>
  ab5919:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  ab591e:	mov    %r15,%rdi
  ab5921:	mov    %eax,%esi
  ab5923:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5928:	test   %al,%al
  ab592a:	jne    ab59c8 <CGameUI::handleKeyPresses()+0xa48>
  ab5930:	add    $0x198,%rsp
  ab5937:	pop    %rbx
  ab5938:	pop    %rbp
  ab5939:	pop    %r12
  ab593b:	pop    %r13
  ab593d:	pop    %r14
  ab593f:	pop    %r15
  ab5941:	ret
  ab5942:	nopw   0x0(%rax,%rax,1)
  ab5948:	movb   $0x0,0x12fb(%rbp)
  ab594f:	movl   $0xffffffff,0x1674(%rbp)
  ab5959:	mov    %rbp,%rdi
  ab595c:	movl   $0xffffffff,0x1678(%rbp)
  ab5966:	movl   $0xffffffff,0x167c(%rbp)
  ab5970:	call   a84230 <CGameUI::captureProcessInput()>
  ab5975:	jmp    ab5930 <CGameUI::handleKeyPresses()+0x9b0>
  ab5977:	nopw   0x0(%rax,%rax,1)
  ab5980:	cmpb   $0x0,0xa040d9(%rip)        # 14b9a60 <gTogglePet>
  ab5987:	je     ab519b <CGameUI::handleKeyPresses()+0x21b>
  ab598d:	nopl   (%rax)
  ab5990:	jmp    ab518c <CGameUI::handleKeyPresses()+0x20c>
  ab5995:	nopl   (%rax)
  ab5998:	cmpb   $0x0,0xa040c2(%rip)        # 14b9a61 <gToggleStats>
  ab599f:	je     ab516b <CGameUI::handleKeyPresses()+0x1eb>
  ab59a5:	jmp    ab515c <CGameUI::handleKeyPresses()+0x1dc>
  ab59aa:	nopw   0x0(%rax,%rax,1)
  ab59b0:	cmpb   $0x0,0xa041f9(%rip)        # 14b9bb0 <gToggleInventory>
  ab59b7:	je     ab508d <CGameUI::handleKeyPresses()+0x10d>
  ab59bd:	nopl   (%rax)
  ab59c0:	jmp    ab507e <CGameUI::handleKeyPresses()+0xfe>
  ab59c5:	nopl   (%rax)
  ab59c8:	mov    0x38(%rbp),%rax
  ab59cc:	xorps  %xmm1,%xmm1
  ab59cf:	mov    0x16a8(%rbp),%rdi
  ab59d6:	xor    %ecx,%ecx
  ab59d8:	mov    $0x1e,%esi
  ab59dd:	mov    0x58(%rax),%rdx
  ab59e1:	movaps %xmm1,%xmm0
  ab59e4:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  ab59e9:	mov    0x38(%rbp),%rdi
  ab59ed:	mov    $0x1,%esi
  ab59f2:	call   80f500 <CCharacter::cycleSkill(int)>
  ab59f7:	jmp    ab5930 <CGameUI::handleKeyPresses()+0x9b0>
  ab59fc:	nopl   0x0(%rax)
  ab5a00:	mov    0x40(%rbp),%rdi
  ab5a04:	call   938830 <CLevel::toggleAutomap()>
  ab5a09:	jmp    ab51f1 <CGameUI::handleKeyPresses()+0x271>
  ab5a0e:	xchg   %ax,%ax
  ab5a10:	mov    0x38(%rbp),%rax
  ab5a14:	xorps  %xmm1,%xmm1
  ab5a17:	mov    0x16a8(%rbp),%rdi
  ab5a1e:	xor    %ecx,%ecx
  ab5a20:	mov    $0x1e,%esi
  ab5a25:	mov    0x58(%rax),%rdx
  ab5a29:	movaps %xmm1,%xmm0
  ab5a2c:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  ab5a31:	mov    0x38(%rbp),%rdi
  ab5a35:	mov    $0xffffffff,%esi
  ab5a3a:	call   80f500 <CCharacter::cycleSkill(int)>
  ab5a3f:	jmp    ab5930 <CGameUI::handleKeyPresses()+0x9b0>
  ab5a44:	nopl   0x0(%rax)
  ab5a48:	mov    %rbp,%rdi
  ab5a4b:	call   a8e930 <CGameUI::toggleSkill()>
  ab5a50:	jmp    ab50f9 <CGameUI::handleKeyPresses()+0x179>
  ab5a55:	nopl   (%rax)
  ab5a58:	mov    %rbp,%rdi
  ab5a5b:	call   a8e750 <CGameUI::toggleQuest()>
  ab5a60:	jmp    ab513b <CGameUI::handleKeyPresses()+0x1bb>
  ab5a65:	nopl   (%rax)
  ab5a68:	mov    %rbp,%rdi
  ab5a6b:	call   a8e840 <CGameUI::toggleJournal()>
  ab5a70:	jmp    ab511a <CGameUI::handleKeyPresses()+0x19a>
  ab5a75:	nopl   (%rax)
  ab5a78:	mov    0x38(%rbp),%rdi
  ab5a7c:	call   80f6b0 <CCharacter::swapSkills()>
  ab5a81:	mov    0x4c0(%rbp),%rax
  ab5a88:	mov    0x348(%rax),%rsi
  ab5a8f:	mov    0xb0(%rsi),%rdi
  ab5a96:	test   %rdi,%rdi
  ab5a99:	je     ab51bc <CGameUI::handleKeyPresses()+0x23c>
  ab5a9f:	call   552ae8 <CEGUI::Window::removeChildWindow(CEGUI::Window*)@plt>
  ab5aa4:	jmp    ab51bc <CGameUI::handleKeyPresses()+0x23c>
  ab5aa9:	nopl   0x0(%rax)
  ab5ab0:	mov    $0x78,%esi
  ab5ab5:	mov    %r15,%rdi
  ab5ab8:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  ab5abd:	test   %al,%al
  ab5abf:	je     ab58ee <CGameUI::handleKeyPresses()+0x96e>
  ab5ac5:	call   a54490 <CMasterResourceManager::getSingleton()>
  ab5aca:	mov    0xb0(%rax),%r12
  ab5ad1:	test   %r12,%r12
  ab5ad4:	je     ab58ee <CGameUI::handleKeyPresses()+0x96e>
  ab5ada:	mov    0xa559bc(%rip),%esi        # 150b49c <KSETTINGS_S_PATH_SCREENSHOTS>
  ab5ae0:	mov    0x78(%rbp),%rdi
  ab5ae4:	lea    0xe0(%rsp),%rbx
  ab5aec:	call   c6e460 <CDynamicPropertyFile::GetString(unsigned int)>
  ab5af1:	mov    %rbx,%rdi
  ab5af4:	mov    %rax,%r13
  ab5af7:	call   c764a0 <FILESYSTEM::GetAppDataPath()>
  ab5afc:	lea    0xf0(%rsp),%rax
  ab5b04:	mov    %r13,%rdx
  ab5b07:	mov    %rbx,%rsi
  ab5b0a:	mov    %rax,%rdi
  ab5b0d:	mov    %rax,0x28(%rsp)
  ab5b12:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  ab5b17:	mov    %rbx,%rdi
  ab5b1a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5b1f:	mov    0x28(%rsp),%rdi
  ab5b24:	call   c76860 <FILESYSTEM::CreateAppDataDirectory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  ab5b29:	mov    (%r12),%rax
  ab5b2d:	lea    0xc0(%rsp),%r14
  ab5b35:	lea    0x18f(%rsp),%rdx
  ab5b3d:	mov    $0xfa06f3,%esi
  ab5b42:	mov    %r14,%rdi
  ab5b45:	mov    0x118(%rax),%rax
  ab5b4c:	mov    %rax,0x18(%rsp)
  ab5b51:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  ab5b56:	lea    0xd0(%rsp),%r13
  ab5b5e:	mov    0xf0(%rsp),%rsi
  ab5b66:	mov    %r13,%rdi
  ab5b69:	call   c8e350 <STRINGS::StringConvertToNarrow(wchar_t const*)>
  ab5b6e:	lea    0xb0(%rsp),%rbx
  ab5b76:	mov    %r14,%rcx
  ab5b79:	mov    %r13,%rdx
  ab5b7c:	mov    %r12,%rsi
  ab5b7f:	mov    %rbx,%rdi
  ab5b82:	call   *0x18(%rsp)
  ab5b86:	mov    %r13,%rdi
  ab5b89:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab5b8e:	mov    %r14,%rdi
  ab5b91:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab5b96:	mov    %rbx,%rdi
  ab5b99:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab5b9e:	mov    0x28(%rsp),%rdi
  ab5ba3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5ba8:	jmp    ab58ee <CGameUI::handleKeyPresses()+0x96e>
  ab5bad:	nopl   (%rax)
  ab5bb0:	mov    0x40(%rbp),%rdi
  ab5bb4:	movss  0x530420(%rip),%xmm0        # fe5fdc <typeinfo name for CSkillFoldout+0x1c>
  ab5bbc:	call   938810 <CLevel::zoomAutomap(float)>
  ab5bc1:	jmp    ab5233 <CGameUI::handleKeyPresses()+0x2b3>
  ab5bc6:	cs nopw 0x0(%rax,%rax,1)
  ab5bd0:	mov    0x40(%rbp),%rdi
  ab5bd4:	movss  0x4f2af4(%rip),%xmm0        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  ab5bdc:	call   938810 <CLevel::zoomAutomap(float)>
  ab5be1:	jmp    ab5212 <CGameUI::handleKeyPresses()+0x292>
  ab5be6:	cs nopw 0x0(%rax,%rax,1)
  ab5bf0:	mov    %rcx,%rbx
  ab5bf3:	jmp    ab56b8 <CGameUI::handleKeyPresses()+0x738>
  ab5bf8:	nopl   0x0(%rax,%rax,1)
  ab5c00:	movzwl %r14w,%r14d
  ab5c04:	jmp    ab575d <CGameUI::handleKeyPresses()+0x7dd>
  ab5c09:	mov    0x58(%rsp),%rbx
  ab5c0e:	test   %rbx,%rbx
  ab5c11:	je     ab5636 <CGameUI::handleKeyPresses()+0x6b6>
  ab5c17:	mov    (%rbx),%rax
  ab5c1a:	lea    -0x18(%rax),%rdi
  ab5c1e:	cmp    $0x1426460,%rdi
  ab5c25:	jne    ab5cf9 <CGameUI::handleKeyPresses()+0xd79>
  ab5c2b:	mov    %rbx,%rdi
  ab5c2e:	call   553f18 <operator delete(void*)@plt>
  ab5c33:	jmp    ab5636 <CGameUI::handleKeyPresses()+0x6b6>
  ab5c38:	nopl   0x0(%rax,%rax,1)
  ab5c40:	mov    0x4d8(%rbp),%rdi
  ab5c47:	mov    (%rdi),%rax
  ab5c4a:	call   *0x20(%rax)
  ab5c4d:	test   %al,%al
  ab5c4f:	je     ab50d8 <CGameUI::handleKeyPresses()+0x158>
  ab5c55:	jmp    ab50c5 <CGameUI::handleKeyPresses()+0x145>
  ab5c5a:	mov    0x58(%rsp),%rdi
  ab5c5f:	nop
  ab5c60:	jmp    ab5669 <CGameUI::handleKeyPresses()+0x6e9>
  ab5c65:	mov    0x58(%rsp),%rbx
  ab5c6a:	test   %rbx,%rbx
  ab5c6d:	je     ab5636 <CGameUI::handleKeyPresses()+0x6b6>
  ab5c73:	mov    (%rbx),%rax
  ab5c76:	mov    $0x1423a20,%edx
  ab5c7b:	lea    -0x18(%rax),%rdi
  ab5c7f:	cmp    %rdi,%rdx
  ab5c82:	je     ab5c2b <CGameUI::handleKeyPresses()+0xcab>
  ab5c84:	mov    $0x5541c8,%edx
  ab5c89:	test   %rdx,%rdx
  ab5c8c:	je     ab5ff3 <CGameUI::handleKeyPresses()+0x1073>
  ab5c92:	or     $0xffffffff,%edx
  ab5c95:	lock xadd %edx,0x10(%rdi)
  ab5c9a:	test   %edx,%edx
  ab5c9c:	jg     ab5c2b <CGameUI::handleKeyPresses()+0xcab>
  ab5c9e:	lea    0x187(%rsp),%rsi
  ab5ca6:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  ab5cab:	jmp    ab5c2b <CGameUI::handleKeyPresses()+0xcab>
  ab5cb0:	movl   $0x0,-0x8(%rax)
  ab5cb7:	mov    %r13,-0x18(%rax)
  ab5cbb:	movl   $0x0,0x18(%rdx,%r13,4)
  ab5cc4:	jmp    ab57a3 <CGameUI::handleKeyPresses()+0x823>
  ab5cc9:	movl   $0x0,-0x8(%rax)
  ab5cd0:	mov    %r12,-0x18(%rax)
  ab5cd4:	movw   $0x0,0x18(%rdx,%r12,2)
  ab5cdc:	jmp    ab556f <CGameUI::handleKeyPresses()+0x5ef>
  ab5ce1:	movl   $0x0,-0x8(%rax)
  ab5ce8:	mov    %r13,-0x18(%rax)
  ab5cec:	movw   $0x0,0x18(%rdx,%r13,2)
  ab5cf4:	jmp    ab5519 <CGameUI::handleKeyPresses()+0x599>
  ab5cf9:	mov    $0x5541c8,%edx
  ab5cfe:	test   %rdx,%rdx
  ab5d01:	je     ab5d49 <CGameUI::handleKeyPresses()+0xdc9>
  ab5d03:	or     $0xffffffff,%edx
  ab5d06:	lock xadd %edx,0x10(%rdi)
  ab5d0b:	test   %edx,%edx
  ab5d0d:	jg     ab5c2b <CGameUI::handleKeyPresses()+0xcab>
  ab5d13:	call   553f18 <operator delete(void*)@plt>
  ab5d18:	jmp    ab5c2b <CGameUI::handleKeyPresses()+0xcab>
  ab5d1d:	lea    0x60(%rsp),%rdi
  ab5d22:	mov    %rax,%rbp
  ab5d25:	call   56b1d0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::~basic_string()>
  ab5d2a:	lea    0x120(%rsp),%rdi
  ab5d32:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5d37:	mov    0x28(%rsp),%rdi
  ab5d3c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5d41:	mov    %rbp,%rdi
  ab5d44:	call   554498 <_Unwind_Resume@plt>
  ab5d49:	mov    -0x8(%rax),%edx
  ab5d4c:	lea    -0x1(%rdx),%ecx
  ab5d4f:	mov    %ecx,-0x8(%rax)
  ab5d52:	jmp    ab5d0b <CGameUI::handleKeyPresses()+0xd8b>
  ab5d54:	mov    %rax,%rbp
  ab5d57:	mov    0x20(%rsp),%rdi
  ab5d5c:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab5d61:	lea    0x60(%rsp),%rdi
  ab5d66:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab5d6b:	jmp    ab5d2a <CGameUI::handleKeyPresses()+0xdaa>
  ab5d6d:	mov    $0x5541c8,%eax
  ab5d72:	test   %rax,%rax
  ab5d75:	je     ab5dc2 <CGameUI::handleKeyPresses()+0xe42>
  ab5d77:	or     $0xffffffff,%eax
  ab5d7a:	lock xadd %eax,0x10(%rdi)
  ab5d7f:	test   %eax,%eax
  ab5d81:	jg     ab55fb <CGameUI::handleKeyPresses()+0x67b>
  ab5d87:	lea    0x188(%rsp),%rsi
  ab5d8f:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  ab5d94:	jmp    ab55fb <CGameUI::handleKeyPresses()+0x67b>
  ab5d99:	mov    %rbx,%rdi
  ab5d9c:	mov    %rax,%rbp
  ab5d9f:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab5da4:	mov    0x20(%rsp),%rdi
  ab5da9:	call   56b1d0 <std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >::~basic_string()>
  ab5dae:	jmp    ab5d61 <CGameUI::handleKeyPresses()+0xde1>
  ab5db0:	mov    %rax,%rbp
  ab5db3:	lea    0x80(%rsp),%rax
  ab5dbb:	mov    %rax,0x20(%rsp)
  ab5dc0:	jmp    ab5da4 <CGameUI::handleKeyPresses()+0xe24>
  ab5dc2:	mov    0x10(%rdi),%eax
  ab5dc5:	lea    -0x1(%rax),%edx
  ab5dc8:	mov    %edx,0x10(%rdi)
  ab5dcb:	jmp    ab5d7f <CGameUI::handleKeyPresses()+0xdff>
  ab5dcd:	mov    0x28(%rsp),%rdi
  ab5dd2:	mov    %rax,%rbp
  ab5dd5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5dda:	mov    %rbx,%rdi
  ab5ddd:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5de2:	mov    %r12,%rdi
  ab5de5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5dea:	mov    %rbp,%rdi
  ab5ded:	call   554498 <_Unwind_Resume@plt>
  ab5df2:	mov    $0x5541c8,%eax
  ab5df7:	test   %rax,%rax
  ab5dfa:	je     ab5e52 <CGameUI::handleKeyPresses()+0xed2>
  ab5dfc:	or     $0xffffffff,%eax
  ab5dff:	lock xadd %eax,0x10(%rdi)
  ab5e04:	test   %eax,%eax
  ab5e06:	jg     ab52c7 <CGameUI::handleKeyPresses()+0x347>
  ab5e0c:	lea    0x18e(%rsp),%rsi
  ab5e14:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5e19:	jmp    ab52c7 <CGameUI::handleKeyPresses()+0x347>
  ab5e1e:	mov    $0x5541c8,%eax
  ab5e23:	test   %rax,%rax
  ab5e26:	je     ab5e5d <CGameUI::handleKeyPresses()+0xedd>
  ab5e28:	or     $0xffffffff,%eax
  ab5e2b:	lock xadd %eax,0x10(%rdi)
  ab5e30:	test   %eax,%eax
  ab5e32:	jg     ab52e1 <CGameUI::handleKeyPresses()+0x361>
  ab5e38:	lea    0x18d(%rsp),%rsi
  ab5e40:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5e45:	jmp    ab52e1 <CGameUI::handleKeyPresses()+0x361>
  ab5e4a:	mov    %rax,%rbp
  ab5e4d:	jmp    ab5d37 <CGameUI::handleKeyPresses()+0xdb7>
  ab5e52:	mov    0x10(%rdi),%eax
  ab5e55:	lea    -0x1(%rax),%edx
  ab5e58:	mov    %edx,0x10(%rdi)
  ab5e5b:	jmp    ab5e04 <CGameUI::handleKeyPresses()+0xe84>
  ab5e5d:	mov    0x10(%rdi),%eax
  ab5e60:	lea    -0x1(%rax),%edx
  ab5e63:	mov    %edx,0x10(%rdi)
  ab5e66:	jmp    ab5e30 <CGameUI::handleKeyPresses()+0xeb0>
  ab5e68:	mov    %rax,%rbp
  ab5e6b:	mov    %r13,%rdi
  ab5e6e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5e73:	jmp    ab5d37 <CGameUI::handleKeyPresses()+0xdb7>
  ab5e78:	mov    %rax,%rbp
  ab5e7b:	mov    %r12,%rdi
  ab5e7e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5e83:	jmp    ab5e6b <CGameUI::handleKeyPresses()+0xeeb>
  ab5e85:	mov    %rbx,%rdi
  ab5e88:	mov    %rax,%rbp
  ab5e8b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5e90:	jmp    ab5e7b <CGameUI::handleKeyPresses()+0xefb>
  ab5e92:	jmp    ab5e85 <CGameUI::handleKeyPresses()+0xf05>
  ab5e94:	mov    %rax,%rbp
  ab5e97:	jmp    ab5de2 <CGameUI::handleKeyPresses()+0xe62>
  ab5e9c:	mov    %rax,%rbp
  ab5e9f:	nop
  ab5ea0:	jmp    ab5dda <CGameUI::handleKeyPresses()+0xe5a>
  ab5ea5:	mov    %rbx,%rdi
  ab5ea8:	mov    %rax,%rbp
  ab5eab:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5eb0:	jmp    ab5d37 <CGameUI::handleKeyPresses()+0xdb7>
  ab5eb5:	mov    $0x5541c8,%eax
  ab5eba:	test   %rax,%rax
  ab5ebd:	je     ab6067 <CGameUI::handleKeyPresses()+0x10e7>
  ab5ec3:	or     $0xffffffff,%eax
  ab5ec6:	lock xadd %eax,0x10(%rdi)
  ab5ecb:	test   %eax,%eax
  ab5ecd:	jg     ab58bf <CGameUI::handleKeyPresses()+0x93f>
  ab5ed3:	lea    0x185(%rsp),%rsi
  ab5edb:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5ee0:	jmp    ab58bf <CGameUI::handleKeyPresses()+0x93f>
  ab5ee5:	mov    %rax,%rbp
  ab5ee8:	lea    0x40(%rsp),%rdi
  ab5eed:	call   56dad0 <Ogre::UTFString::~UTFString()>
  ab5ef2:	jmp    ab5d57 <CGameUI::handleKeyPresses()+0xdd7>
  ab5ef7:	mov    $0x5541c8,%eax
  ab5efc:	test   %rax,%rax
  ab5eff:	je     ab5f4f <CGameUI::handleKeyPresses()+0xfcf>
  ab5f01:	or     $0xffffffff,%eax
  ab5f04:	lock xadd %eax,0x10(%rdi)
  ab5f09:	test   %eax,%eax
  ab5f0b:	jg     ab5367 <CGameUI::handleKeyPresses()+0x3e7>
  ab5f11:	lea    0x18c(%rsp),%rsi
  ab5f19:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5f1e:	jmp    ab5367 <CGameUI::handleKeyPresses()+0x3e7>
  ab5f23:	mov    $0x5541c8,%eax
  ab5f28:	test   %rax,%rax
  ab5f2b:	je     ab5f5a <CGameUI::handleKeyPresses()+0xfda>
  ab5f2d:	or     $0xffffffff,%eax
  ab5f30:	lock xadd %eax,0x10(%rdi)
  ab5f35:	test   %eax,%eax
  ab5f37:	jg     ab5381 <CGameUI::handleKeyPresses()+0x401>
  ab5f3d:	lea    0x18b(%rsp),%rsi
  ab5f45:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5f4a:	jmp    ab5381 <CGameUI::handleKeyPresses()+0x401>
  ab5f4f:	mov    0x10(%rdi),%eax
  ab5f52:	lea    -0x1(%rax),%edx
  ab5f55:	mov    %edx,0x10(%rdi)
  ab5f58:	jmp    ab5f09 <CGameUI::handleKeyPresses()+0xf89>
  ab5f5a:	mov    0x10(%rdi),%eax
  ab5f5d:	lea    -0x1(%rax),%edx
  ab5f60:	mov    %edx,0x10(%rdi)
  ab5f63:	jmp    ab5f35 <CGameUI::handleKeyPresses()+0xfb5>
  ab5f65:	mov    $0x5541c8,%eax
  ab5f6a:	test   %rax,%rax
  ab5f6d:	je     ab5fbd <CGameUI::handleKeyPresses()+0x103d>
  ab5f6f:	or     $0xffffffff,%eax
  ab5f72:	lock xadd %eax,0x10(%rdi)
  ab5f77:	test   %eax,%eax
  ab5f79:	jg     ab539b <CGameUI::handleKeyPresses()+0x41b>
  ab5f7f:	lea    0x18a(%rsp),%rsi
  ab5f87:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5f8c:	jmp    ab539b <CGameUI::handleKeyPresses()+0x41b>
  ab5f91:	mov    $0x5541c8,%eax
  ab5f96:	test   %rax,%rax
  ab5f99:	je     ab5fc8 <CGameUI::handleKeyPresses()+0x1048>
  ab5f9b:	or     $0xffffffff,%eax
  ab5f9e:	lock xadd %eax,0x10(%rdi)
  ab5fa3:	test   %eax,%eax
  ab5fa5:	jg     ab58d9 <CGameUI::handleKeyPresses()+0x959>
  ab5fab:	lea    0x184(%rsp),%rsi
  ab5fb3:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  ab5fb8:	jmp    ab58d9 <CGameUI::handleKeyPresses()+0x959>
  ab5fbd:	mov    0x10(%rdi),%eax
  ab5fc0:	lea    -0x1(%rax),%edx
  ab5fc3:	mov    %edx,0x10(%rdi)
  ab5fc6:	jmp    ab5f77 <CGameUI::handleKeyPresses()+0xff7>
  ab5fc8:	mov    0x10(%rdi),%eax
  ab5fcb:	lea    -0x1(%rax),%edx
  ab5fce:	mov    %edx,0x10(%rdi)
  ab5fd1:	jmp    ab5fa3 <CGameUI::handleKeyPresses()+0x1023>
  ab5fd3:	mov    %rax,%rbp
  ab5fd6:	jmp    ab5d2a <CGameUI::handleKeyPresses()+0xdaa>
  ab5fdb:	mov    %rax,%rbp
  ab5fde:	jmp    ab5d61 <CGameUI::handleKeyPresses()+0xde1>
  ab5fe3:	mov    %rbx,%rdi
  ab5fe6:	mov    %rax,%rbp
  ab5fe9:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab5fee:	jmp    ab5ee8 <CGameUI::handleKeyPresses()+0xf68>
  ab5ff3:	mov    -0x8(%rax),%edx
  ab5ff6:	lea    -0x1(%rdx),%ecx
  ab5ff9:	mov    %ecx,-0x8(%rax)
  ab5ffc:	jmp    ab5c9a <CGameUI::handleKeyPresses()+0xd1a>
  ab6001:	mov    %rax,%rbp
  ab6004:	mov    %r14,%rdi
  ab6007:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab600c:	jmp    ab5d37 <CGameUI::handleKeyPresses()+0xdb7>
  ab6011:	jmp    ab5e4a <CGameUI::handleKeyPresses()+0xeca>
  ab6016:	cs nopw 0x0(%rax,%rax,1)
  ab6020:	jmp    ab5e4a <CGameUI::handleKeyPresses()+0xeca>
  ab6025:	mov    %rax,%rbp
  ab6028:	mov    %rbx,%rdi
  ab602b:	nopl   0x0(%rax,%rax,1)
  ab6030:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  ab6035:	mov    %rbp,%rdi
  ab6038:	call   554498 <_Unwind_Resume@plt>
  ab603d:	mov    %rbx,%rdi
  ab6040:	mov    %rax,%rbp
  ab6043:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab6048:	jmp    ab6004 <CGameUI::handleKeyPresses()+0x1084>
  ab604a:	mov    %r13,%rdi
  ab604d:	mov    %rax,%rbp
  ab6050:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab6055:	jmp    ab6004 <CGameUI::handleKeyPresses()+0x1084>
  ab6057:	mov    %rbx,%rdi
  ab605a:	mov    %rax,%rbp
  ab605d:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  ab6062:	jmp    ab5d37 <CGameUI::handleKeyPresses()+0xdb7>
  ab6067:	mov    0x10(%rdi),%eax
  ab606a:	lea    -0x1(%rax),%edx
  ab606d:	mov    %edx,0x10(%rdi)
  ab6070:	jmp    ab5ecb <CGameUI::handleKeyPresses()+0xf4b>
