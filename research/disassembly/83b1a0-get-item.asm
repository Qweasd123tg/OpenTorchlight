000000000083b1a0 <CCharacter::getItem(CItem*, CLevel&)>:
  83b1a0:	48 89 5c 24 d0       	mov    QWORD PTR [rsp-0x30],rbx
  83b1a5:	48 89 6c 24 d8       	mov    QWORD PTR [rsp-0x28],rbp
  83b1aa:	48 89 f3             	mov    rbx,rsi
  83b1ad:	4c 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],r13
  83b1b2:	4c 89 64 24 e0       	mov    QWORD PTR [rsp-0x20],r12
  83b1b7:	48 89 fd             	mov    rbp,rdi
  83b1ba:	4c 89 74 24 f0       	mov    QWORD PTR [rsp-0x10],r14
  83b1bf:	4c 89 7c 24 f8       	mov    QWORD PTR [rsp-0x8],r15
  83b1c4:	48 81 ec 18 01 00 00 	sub    rsp,0x118
  83b1cb:	48 85 f6             	test   rsi,rsi
  83b1ce:	49 89 d5             	mov    r13,rdx
  83b1d1:	0f 84 73 02 00 00    	je     83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b1d7:	be 22 00 00 00       	mov    esi,0x22
  83b1dc:	48 89 df             	mov    rdi,rbx
  83b1df:	e8 bc b0 fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  83b1e4:	84 c0                	test   al,al
  83b1e6:	0f 84 9c 02 00 00    	je     83b488 <CCharacter::getItem(CItem*, CLevel&)+0x2e8>
  83b1ec:	31 c9                	xor    ecx,ecx
  83b1ee:	ba d0 22 fd 00       	mov    edx,0xfd22d0
  83b1f3:	be a0 1d fd 00       	mov    esi,0xfd1da0
  83b1f8:	48 89 df             	mov    rdi,rbx
  83b1fb:	e8 58 a5 d1 ff       	call   555758 <__dynamic_cast@plt>
  83b200:	31 f6                	xor    esi,esi
  83b202:	49 89 c4             	mov    r12,rax
  83b205:	48 89 c7             	mov    rdi,rax
  83b208:	e8 23 75 08 00       	call   8c2730 <CItemGold::playTakeSound(Ogre::SceneNode*)>
  83b20d:	41 8b b4 24 2c 02 00 00 	mov    esi,DWORD PTR [r12+0x22c]
  83b215:	48 89 ef             	mov    rdi,rbp
  83b218:	e8 53 68 fd ff       	call   811a70 <CCharacter::giveGold(int)>
  83b21d:	31 f6                	xor    esi,esi
  83b21f:	48 89 ef             	mov    rdi,rbp
  83b222:	e8 f9 96 fe ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  83b227:	80 3d 82 36 c4 00 00 	cmp    BYTE PTR [rip+0xc43682],0x0        # 147e8b0 <guard variable for CCharacter::getItem(CItem*, CLevel&)::g_Gold>
  83b22e:	0f 84 9c 03 00 00    	je     83b5d0 <CCharacter::getItem(CItem*, CLevel&)+0x430>
  83b234:	48 8b 05 7d 36 c4 00 	mov    rax,QWORD PTR [rip+0xc4367d]        # 147e8b8 <CCharacter::getItem(CItem*, CLevel&)::g_Gold>
  83b23b:	48 83 78 e8 00       	cmp    QWORD PTR [rax-0x18],0x0
  83b240:	0f 84 02 03 00 00    	je     83b548 <CCharacter::getItem(CItem*, CLevel&)+0x3a8>
  83b246:	f3 0f 10 1d ae 95 76 00 	movss  xmm3,DWORD PTR [rip+0x7695ae]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  83b24e:	48 8d 7c 24 30       	lea    rdi,[rsp+0x30]
  83b253:	0f 28 c3             	movaps xmm0,xmm3
  83b256:	f3 0f 10 15 da 95 76 00 	movss  xmm2,DWORD PTR [rip+0x7695da]        # fa4838 <vtable for Ogre::FrameListener+0x78>
  83b25e:	f3 0f 10 0d c6 95 76 00 	movss  xmm1,DWORD PTR [rip+0x7695c6]        # fa482c <vtable for Ogre::FrameListener+0x6c>
  83b266:	e8 ad 8e d1 ff       	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  83b26b:	f3 0f 10 1d 89 95 76 00 	movss  xmm3,DWORD PTR [rip+0x769589]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  83b273:	48 8d 7c 24 50       	lea    rdi,[rsp+0x50]
  83b278:	0f 28 c3             	movaps xmm0,xmm3
  83b27b:	f3 0f 10 15 b5 95 76 00 	movss  xmm2,DWORD PTR [rip+0x7695b5]        # fa4838 <vtable for Ogre::FrameListener+0x78>
  83b283:	f3 0f 10 0d a1 95 76 00 	movss  xmm1,DWORD PTR [rip+0x7695a1]        # fa482c <vtable for Ogre::FrameListener+0x6c>
  83b28b:	e8 88 8e d1 ff       	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  83b290:	41 8b b4 24 2c 02 00 00 	mov    esi,DWORD PTR [r12+0x22c]
  83b298:	48 8d bc 24 c0 00 00 00 	lea    rdi,[rsp+0xc0]
  83b2a0:	4c 8d a4 24 b0 00 00 00 	lea    r12,[rsp+0xb0]
  83b2a8:	e8 f3 60 45 00       	call   c913a0 <STRINGS::GetValueAsWString(int)>
  83b2ad:	48 8d b4 24 c0 00 00 00 	lea    rsi,[rsp+0xc0]
  83b2b5:	4c 89 e7             	mov    rdi,r12
  83b2b8:	e8 cb 7f d1 ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  83b2bd:	bf 98 0b fd 00       	mov    edi,0xfd0b98
  83b2c2:	e8 41 93 d1 ff       	call   554608 <wcslen@plt>
  83b2c7:	be 98 0b fd 00       	mov    esi,0xfd0b98
  83b2cc:	48 89 c2             	mov    rdx,rax
  83b2cf:	4c 89 e7             	mov    rdi,r12
  83b2d2:	e8 f1 88 d1 ff       	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  83b2d7:	4c 8d bc 24 a0 00 00 00 	lea    r15,[rsp+0xa0]
  83b2df:	ba b8 e8 47 01       	mov    edx,0x147e8b8
  83b2e4:	4c 89 e6             	mov    rsi,r12
  83b2e7:	4c 89 ff             	mov    rdi,r15
  83b2ea:	e8 e1 64 ec ff       	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  83b2ef:	4c 8d b4 24 90 00 00 00 	lea    r14,[rsp+0x90]
  83b2f7:	4c 89 fe             	mov    rsi,r15
  83b2fa:	4c 89 f7             	mov    rdi,r14
  83b2fd:	e8 8e 29 45 00       	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  83b302:	f3 0f 10 05 32 98 be 00 	movss  xmm0,DWORD PTR [rip+0xbe9832]        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  83b30a:	be 01 00 00 00       	mov    esi,0x1
  83b30f:	f3 0f 11 44 24 14    	movss  DWORD PTR [rsp+0x14],xmm0
  83b315:	48 89 df             	mov    rdi,rbx
  83b318:	f3 0f 10 05 18 98 be 00 	movss  xmm0,DWORD PTR [rip+0xbe9818]        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  83b320:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  83b326:	f3 0f 10 05 06 98 be 00 	movss  xmm0,DWORD PTR [rip+0xbe9806]        # 1424b34 <Ogre::Vector3::UNIT_Y>
  83b32e:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  83b334:	e8 47 bd 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83b339:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  83b33f:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  83b344:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  83b34a:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  83b350:	48 89 84 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rax
  83b358:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  83b35d:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  83b361:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  83b367:	f3 0f 58 84 24 80 00 00 00 	addss  xmm0,DWORD PTR [rsp+0x80]
  83b370:	f3 0f 10 54 24 14    	movss  xmm2,DWORD PTR [rsp+0x14]
  83b376:	f3 0f 58 8c 24 84 00 00 00 	addss  xmm1,DWORD PTR [rsp+0x84]
  83b37f:	89 84 24 88 00 00 00 	mov    DWORD PTR [rsp+0x88],eax
  83b386:	31 c0                	xor    eax,eax
  83b388:	f3 0f 58 94 24 88 00 00 00 	addss  xmm2,DWORD PTR [rsp+0x88]
  83b391:	f3 0f 11 44 24 70    	movss  DWORD PTR [rsp+0x70],xmm0
  83b397:	f3 0f 11 4c 24 74    	movss  DWORD PTR [rsp+0x74],xmm1
  83b39d:	f3 0f 11 54 24 78    	movss  DWORD PTR [rsp+0x78],xmm2
  83b3a3:	48 8b 55 68          	mov    rdx,QWORD PTR [rbp+0x68]
  83b3a7:	48 85 d2             	test   rdx,rdx
  83b3aa:	74 04                	je     83b3b0 <CCharacter::getItem(CItem*, CLevel&)+0x210>
  83b3ac:	48 8b 42 18          	mov    rax,QWORD PTR [rdx+0x18]
  83b3b0:	48 8b 80 20 02 00 00 	mov    rax,QWORD PTR [rax+0x220]
  83b3b7:	48 8d 74 24 70       	lea    rsi,[rsp+0x70]
  83b3bc:	4c 8d 44 24 30       	lea    r8,[rsp+0x30]
  83b3c1:	48 8d 4c 24 50       	lea    rcx,[rsp+0x50]
  83b3c6:	f3 0f 10 0d 72 d3 76 00 	movss  xmm1,DWORD PTR [rip+0x76d372]        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  83b3ce:	f3 0f 10 05 26 94 76 00 	movss  xmm0,DWORD PTR [rip+0x769426]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  83b3d6:	4c 89 f2             	mov    rdx,r14
  83b3d9:	48 8b 78 78          	mov    rdi,QWORD PTR [rax+0x78]
  83b3dd:	e8 be 0e 26 00       	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  83b3e2:	48 8b bc 24 90 00 00 00 	mov    rdi,QWORD PTR [rsp+0x90]
  83b3ea:	48 83 ef 18          	sub    rdi,0x18
  83b3ee:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  83b3f5:	0f 85 6b 03 00 00    	jne    83b766 <CCharacter::getItem(CItem*, CLevel&)+0x5c6>
  83b3fb:	48 8b bc 24 a0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xa0]
  83b403:	bd 40 45 42 01       	mov    ebp,0x1424540
  83b408:	48 83 ef 18          	sub    rdi,0x18
  83b40c:	48 39 ef             	cmp    rdi,rbp
  83b40f:	0f 85 81 03 00 00    	jne    83b796 <CCharacter::getItem(CItem*, CLevel&)+0x5f6>
  83b415:	48 8b bc 24 b0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xb0]
  83b41d:	48 83 ef 18          	sub    rdi,0x18
  83b421:	48 39 fd             	cmp    rbp,rdi
  83b424:	0f 85 9c 03 00 00    	jne    83b7c6 <CCharacter::getItem(CItem*, CLevel&)+0x626>
  83b42a:	48 8b bc 24 c0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xc0]
  83b432:	48 83 ef 18          	sub    rdi,0x18
  83b436:	48 39 fd             	cmp    rbp,rdi
  83b439:	0f 85 b7 03 00 00    	jne    83b7f6 <CCharacter::getItem(CItem*, CLevel&)+0x656>
  83b43f:	48 89 de             	mov    rsi,rbx
  83b442:	4c 89 ef             	mov    rdi,r13
  83b445:	e8 c6 ea 10 00       	call   949f10 <CLevel::deleteItem(CItem*)>
  83b44a:	48 8b 9c 24 e8 00 00 00 	mov    rbx,QWORD PTR [rsp+0xe8]
  83b452:	48 8b ac 24 f0 00 00 00 	mov    rbp,QWORD PTR [rsp+0xf0]
  83b45a:	4c 8b a4 24 f8 00 00 00 	mov    r12,QWORD PTR [rsp+0xf8]
  83b462:	4c 8b ac 24 00 01 00 00 	mov    r13,QWORD PTR [rsp+0x100]
  83b46a:	4c 8b b4 24 08 01 00 00 	mov    r14,QWORD PTR [rsp+0x108]
  83b472:	4c 8b bc 24 10 01 00 00 	mov    r15,QWORD PTR [rsp+0x110]
  83b47a:	48 81 c4 18 01 00 00 	add    rsp,0x118
  83b481:	c3                   	ret
  83b482:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  83b488:	31 c9                	xor    ecx,ecx
  83b48a:	ba c0 10 fd 00       	mov    edx,0xfd10c0
  83b48f:	be a0 1d fd 00       	mov    esi,0xfd1da0
  83b494:	48 89 df             	mov    rdi,rbx
  83b497:	e8 bc a2 d1 ff       	call   555758 <__dynamic_cast@plt>
  83b49c:	48 85 c0             	test   rax,rax
  83b49f:	49 89 c4             	mov    r12,rax
  83b4a2:	74 a6                	je     83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b4a4:	ba 01 00 00 00       	mov    edx,0x1
  83b4a9:	48 89 de             	mov    rsi,rbx
  83b4ac:	4c 89 ef             	mov    rdi,r13
  83b4af:	e8 ec ed 10 00       	call   94a2a0 <CLevel::removeItem(CItem*, bool)>
  83b4b4:	84 c0                	test   al,al
  83b4b6:	0f 84 04 01 00 00    	je     83b5c0 <CCharacter::getItem(CItem*, CLevel&)+0x420>
  83b4bc:	31 f6                	xor    esi,esi
  83b4be:	4c 89 e7             	mov    rdi,r12
  83b4c1:	e8 da 36 03 00       	call   86eba0 <CEquipment::playTakeSound(Ogre::SceneNode*)>
  83b4c6:	48 8b bd 90 04 00 00 	mov    rdi,QWORD PTR [rbp+0x490]
  83b4cd:	ba 01 00 00 00       	mov    edx,0x1
  83b4d2:	4c 89 e6             	mov    rsi,r12
  83b4d5:	e8 d6 9c 0e 00       	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  83b4da:	48 85 c0             	test   rax,rax
  83b4dd:	48 89 c3             	mov    rbx,rax
  83b4e0:	0f 84 a2 01 00 00    	je     83b688 <CCharacter::getItem(CItem*, CLevel&)+0x4e8>
  83b4e6:	be 1c 00 00 00       	mov    esi,0x1c
  83b4eb:	48 89 ef             	mov    rdi,rbp
  83b4ee:	e8 ad ad fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  83b4f3:	84 c0                	test   al,al
  83b4f5:	0f 85 15 01 00 00    	jne    83b610 <CCharacter::getItem(CItem*, CLevel&)+0x470>
  83b4fb:	31 f6                	xor    esi,esi
  83b4fd:	48 89 ef             	mov    rdi,rbp
  83b500:	e8 1b 94 fe ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  83b505:	48 8b bd 90 04 00 00 	mov    rdi,QWORD PTR [rbp+0x490]
  83b50c:	31 d2                	xor    edx,edx
  83b50e:	48 89 de             	mov    rsi,rbx
  83b511:	e8 aa 08 0e 00       	call   91bdc0 <CInventory::canEquip(CEquipment*, bool)>
  83b516:	84 c0                	test   al,al
  83b518:	0f 84 2c ff ff ff    	je     83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b51e:	48 8b bd 90 04 00 00 	mov    rdi,QWORD PTR [rbp+0x490]
  83b525:	48 89 de             	mov    rsi,rbx
  83b528:	e8 43 a4 0e 00       	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  83b52d:	0f b6 b5 a1 04 00 00 	movzx  esi,BYTE PTR [rbp+0x4a1]
  83b534:	48 89 ef             	mov    rdi,rbp
  83b537:	e8 54 45 fd ff       	call   80fa90 <CCharacter::setRenderBehind(bool)>
  83b53c:	e9 09 ff ff ff       	jmp    83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b541:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  83b548:	4c 8d b4 24 d0 00 00 00 	lea    r14,[rsp+0xd0]
  83b550:	e8 0b b8 5d 00       	call   e16d60 <CStringTranslate::getSinglton()>
  83b555:	4c 89 f7             	mov    rdi,r14
  83b558:	48 89 c6             	mov    rsi,rax
  83b55b:	ba 8c d1 fc 00       	mov    edx,0xfcd18c
  83b560:	e8 8b b9 5d 00       	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  83b565:	4c 89 f6             	mov    rsi,r14
  83b568:	bf b8 e8 47 01       	mov    edi,0x147e8b8
  83b56d:	e8 c6 aa d1 ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  83b572:	48 8b bc 24 d0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xd0]
  83b57a:	48 83 ef 18          	sub    rdi,0x18
  83b57e:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  83b585:	0f 84 bb fc ff ff    	je     83b246 <CCharacter::getItem(CItem*, CLevel&)+0xa6>
  83b58b:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83b590:	48 85 c0             	test   rax,rax
  83b593:	0f 84 f3 02 00 00    	je     83b88c <CCharacter::getItem(CItem*, CLevel&)+0x6ec>
  83b599:	83 c8 ff             	or     eax,0xffffffff
  83b59c:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83b5a1:	85 c0                	test   eax,eax
  83b5a3:	0f 8f 9d fc ff ff    	jg     83b246 <CCharacter::getItem(CItem*, CLevel&)+0xa6>
  83b5a9:	48 8d b4 24 df 00 00 00 	lea    rsi,[rsp+0xdf]
  83b5b1:	e8 92 7f d1 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  83b5b6:	e9 8b fc ff ff       	jmp    83b246 <CCharacter::getItem(CItem*, CLevel&)+0xa6>
  83b5bb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  83b5c0:	31 f6                	xor    esi,esi
  83b5c2:	48 89 ef             	mov    rdi,rbp
  83b5c5:	e8 56 93 fe ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  83b5ca:	e9 7b fe ff ff       	jmp    83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b5cf:	90                   	nop
  83b5d0:	bf b0 e8 47 01       	mov    edi,0x147e8b0
  83b5d5:	e8 7e 7f d1 ff       	call   553558 <__cxa_guard_acquire@plt>
  83b5da:	85 c0                	test   eax,eax
  83b5dc:	0f 84 52 fc ff ff    	je     83b234 <CCharacter::getItem(CItem*, CLevel&)+0x94>
  83b5e2:	bf b0 e8 47 01       	mov    edi,0x147e8b0
  83b5e7:	48 c7 05 c6 32 c4 00 58 45 42 01 	mov    QWORD PTR [rip+0xc432c6],0x1424558        # 147e8b8 <CCharacter::getItem(CItem*, CLevel&)::g_Gold>
  83b5f2:	e8 d1 89 d1 ff       	call   553fc8 <__cxa_guard_release@plt>
  83b5f7:	ba 88 f7 f9 00       	mov    edx,0xf9f788
  83b5fc:	be b8 e8 47 01       	mov    esi,0x147e8b8
  83b601:	bf d8 48 55 00       	mov    edi,0x5548d8
  83b606:	e8 dd 9b d1 ff       	call   5551e8 <__cxa_atexit@plt>
  83b60b:	e9 24 fc ff ff       	jmp    83b234 <CCharacter::getItem(CItem*, CLevel&)+0x94>
  83b610:	be 78 00 00 00       	mov    esi,0x78
  83b615:	48 89 df             	mov    rdi,rbx
  83b618:	e8 83 ac fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  83b61d:	84 c0                	test   al,al
  83b61f:	74 3e                	je     83b65f <CCharacter::getItem(CItem*, CLevel&)+0x4bf>
  83b621:	48 8b 7d 68          	mov    rdi,QWORD PTR [rbp+0x68]
  83b625:	e8 16 41 53 00       	call   d6f740 <CResourceManager::getGameUI()>
  83b62a:	be 0a 00 00 00       	mov    esi,0xa
  83b62f:	48 89 c7             	mov    rdi,rax
  83b632:	e8 19 3e 25 00       	call   a8f450 <CGameUI::queueTip(EContextTip)>
  83b637:	80 bb 48 03 00 00 00 	cmp    BYTE PTR [rbx+0x348],0x0
  83b63e:	0f 85 b7 fe ff ff    	jne    83b4fb <CCharacter::getItem(CItem*, CLevel&)+0x35b>
  83b644:	48 8b 7d 68          	mov    rdi,QWORD PTR [rbp+0x68]
  83b648:	e8 f3 40 53 00       	call   d6f740 <CResourceManager::getGameUI()>
  83b64d:	be 01 00 00 00       	mov    esi,0x1
  83b652:	48 89 c7             	mov    rdi,rax
  83b655:	e8 f6 3d 25 00       	call   a8f450 <CGameUI::queueTip(EContextTip)>
  83b65a:	e9 9c fe ff ff       	jmp    83b4fb <CCharacter::getItem(CItem*, CLevel&)+0x35b>
  83b65f:	be 81 00 00 00       	mov    esi,0x81
  83b664:	48 89 df             	mov    rdi,rbx
  83b667:	e8 34 ac fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  83b66c:	84 c0                	test   al,al
  83b66e:	74 c7                	je     83b637 <CCharacter::getItem(CItem*, CLevel&)+0x497>
  83b670:	48 8b 7d 68          	mov    rdi,QWORD PTR [rbp+0x68]
  83b674:	e8 c7 40 53 00       	call   d6f740 <CResourceManager::getGameUI()>
  83b679:	be 13 00 00 00       	mov    esi,0x13
  83b67e:	48 89 c7             	mov    rdi,rax
  83b681:	e8 ca 3d 25 00       	call   a8f450 <CGameUI::queueTip(EContextTip)>
  83b686:	eb af                	jmp    83b637 <CCharacter::getItem(CItem*, CLevel&)+0x497>
  83b688:	48 8b bd 90 04 00 00 	mov    rdi,QWORD PTR [rbp+0x490]
  83b68f:	4c 89 e6             	mov    rsi,r12
  83b692:	e8 d9 a2 0e 00       	call   925970 <CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)>
  83b697:	84 c0                	test   al,al
  83b699:	74 08                	je     83b6a3 <CCharacter::getItem(CItem*, CLevel&)+0x503>
  83b69b:	4c 89 e3             	mov    rbx,r12
  83b69e:	e9 43 fe ff ff       	jmp    83b4e6 <CCharacter::getItem(CItem*, CLevel&)+0x346>
  83b6a3:	48 89 ef             	mov    rdi,rbp
  83b6a6:	e8 05 f6 01 00       	call   85acb0 <CBaseUnit::isPlayer()>
  83b6ab:	84 c0                	test   al,al
  83b6ad:	75 7e                	jne    83b72d <CCharacter::getItem(CItem*, CLevel&)+0x58d>
  83b6af:	48 8b bd 40 06 00 00 	mov    rdi,QWORD PTR [rbp+0x640]
  83b6b6:	48 85 ff             	test   rdi,rdi
  83b6b9:	74 31                	je     83b6ec <CCharacter::getItem(CItem*, CLevel&)+0x54c>
  83b6bb:	e8 f0 f5 01 00       	call   85acb0 <CBaseUnit::isPlayer()>
  83b6c0:	84 c0                	test   al,al
  83b6c2:	74 28                	je     83b6ec <CCharacter::getItem(CItem*, CLevel&)+0x54c>
  83b6c4:	48 8b 85 40 06 00 00 	mov    rax,QWORD PTR [rbp+0x640]
  83b6cb:	48 8b b8 98 02 00 00 	mov    rdi,QWORD PTR [rax+0x298]
  83b6d2:	48 85 ff             	test   rdi,rdi
  83b6d5:	74 15                	je     83b6ec <CCharacter::getItem(CItem*, CLevel&)+0x54c>
  83b6d7:	0f 57 c0             	xorps  xmm0,xmm0
  83b6da:	be 2a 00 00 00       	mov    esi,0x2a
  83b6df:	f3 0f 10 0d 25 91 76 00 	movss  xmm1,DWORD PTR [rip+0x769125]        # fa480c <vtable for Ogre::FrameListener+0x4c>
  83b6e7:	e8 b4 d1 22 00       	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  83b6ec:	48 8d 9d 84 00 00 00 	lea    rbx,[rbp+0x84]
  83b6f3:	b9 01 00 00 00       	mov    ecx,0x1
  83b6f8:	4c 89 e6             	mov    rsi,r12
  83b6fb:	4c 89 ef             	mov    rdi,r13
  83b6fe:	48 89 da             	mov    rdx,rbx
  83b701:	e8 6a 12 12 00       	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  83b706:	48 89 de             	mov    rsi,rbx
  83b709:	4c 89 e7             	mov    rdi,r12
  83b70c:	e8 cf b9 1a 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  83b711:	49 8b 04 24          	mov    rax,QWORD PTR [r12]
  83b715:	4c 89 e7             	mov    rdi,r12
  83b718:	ff 90 60 03 00 00    	call   QWORD PTR [rax+0x360]
  83b71e:	31 f6                	xor    esi,esi
  83b720:	48 89 ef             	mov    rdi,rbp
  83b723:	e8 f8 91 fe ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  83b728:	e9 1d fd ff ff       	jmp    83b44a <CCharacter::getItem(CItem*, CLevel&)+0x2aa>
  83b72d:	48 8b 7d 68          	mov    rdi,QWORD PTR [rbp+0x68]
  83b731:	e8 0a 40 53 00       	call   d6f740 <CResourceManager::getGameUI()>
  83b736:	be 02 00 00 00       	mov    esi,0x2
  83b73b:	48 89 c7             	mov    rdi,rax
  83b73e:	e8 0d 3d 25 00       	call   a8f450 <CGameUI::queueTip(EContextTip)>
  83b743:	48 8b bd 98 02 00 00 	mov    rdi,QWORD PTR [rbp+0x298]
  83b74a:	48 85 ff             	test   rdi,rdi
  83b74d:	74 9d                	je     83b6ec <CCharacter::getItem(CItem*, CLevel&)+0x54c>
  83b74f:	0f 57 c0             	xorps  xmm0,xmm0
  83b752:	be 2f 00 00 00       	mov    esi,0x2f
  83b757:	f3 0f 10 0d ad 90 76 00 	movss  xmm1,DWORD PTR [rip+0x7690ad]        # fa480c <vtable for Ogre::FrameListener+0x4c>
  83b75f:	e8 3c d1 22 00       	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  83b764:	eb 86                	jmp    83b6ec <CCharacter::getItem(CItem*, CLevel&)+0x54c>
  83b766:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83b76b:	48 85 c0             	test   rax,rax
  83b76e:	0f 84 26 01 00 00    	je     83b89a <CCharacter::getItem(CItem*, CLevel&)+0x6fa>
  83b774:	83 c8 ff             	or     eax,0xffffffff
  83b777:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83b77c:	85 c0                	test   eax,eax
  83b77e:	0f 8f 77 fc ff ff    	jg     83b3fb <CCharacter::getItem(CItem*, CLevel&)+0x25b>
  83b784:	48 8d b4 24 de 00 00 00 	lea    rsi,[rsp+0xde]
  83b78c:	e8 47 a0 d1 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  83b791:	e9 65 fc ff ff       	jmp    83b3fb <CCharacter::getItem(CItem*, CLevel&)+0x25b>
  83b796:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83b79b:	48 85 c0             	test   rax,rax
  83b79e:	0f 84 04 01 00 00    	je     83b8a8 <CCharacter::getItem(CItem*, CLevel&)+0x708>
  83b7a4:	83 c8 ff             	or     eax,0xffffffff
  83b7a7:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83b7ac:	85 c0                	test   eax,eax
  83b7ae:	0f 8f 61 fc ff ff    	jg     83b415 <CCharacter::getItem(CItem*, CLevel&)+0x275>
  83b7b4:	48 8d b4 24 dd 00 00 00 	lea    rsi,[rsp+0xdd]
  83b7bc:	e8 87 7d d1 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  83b7c1:	e9 4f fc ff ff       	jmp    83b415 <CCharacter::getItem(CItem*, CLevel&)+0x275>
  83b7c6:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83b7cb:	48 85 c0             	test   rax,rax
  83b7ce:	0f 84 e2 00 00 00    	je     83b8b6 <CCharacter::getItem(CItem*, CLevel&)+0x716>
  83b7d4:	83 c8 ff             	or     eax,0xffffffff
  83b7d7:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83b7dc:	85 c0                	test   eax,eax
  83b7de:	0f 8f 46 fc ff ff    	jg     83b42a <CCharacter::getItem(CItem*, CLevel&)+0x28a>
  83b7e4:	48 8d b4 24 dc 00 00 00 	lea    rsi,[rsp+0xdc]
  83b7ec:	e8 57 7d d1 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  83b7f1:	e9 34 fc ff ff       	jmp    83b42a <CCharacter::getItem(CItem*, CLevel&)+0x28a>
  83b7f6:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83b7fb:	48 85 c0             	test   rax,rax
  83b7fe:	74 4d                	je     83b84d <CCharacter::getItem(CItem*, CLevel&)+0x6ad>
  83b800:	83 c8 ff             	or     eax,0xffffffff
  83b803:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83b808:	85 c0                	test   eax,eax
  83b80a:	0f 8f 2f fc ff ff    	jg     83b43f <CCharacter::getItem(CItem*, CLevel&)+0x29f>
  83b810:	48 8d b4 24 db 00 00 00 	lea    rsi,[rsp+0xdb]
  83b818:	e8 2b 7d d1 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  83b81d:	e9 1d fc ff ff       	jmp    83b43f <CCharacter::getItem(CItem*, CLevel&)+0x29f>
  83b822:	48 89 c3             	mov    rbx,rax
  83b825:	4c 89 f7             	mov    rdi,r14
  83b828:	e8 ab 90 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83b82d:	48 89 df             	mov    rdi,rbx
  83b830:	e8 63 8c d1 ff       	call   554498 <_Unwind_Resume@plt>
  83b835:	48 89 c3             	mov    rbx,rax
  83b838:	48 8d bc 24 c0 00 00 00 	lea    rdi,[rsp+0xc0]
  83b840:	e8 93 90 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83b845:	48 89 df             	mov    rdi,rbx
  83b848:	e8 4b 8c d1 ff       	call   554498 <_Unwind_Resume@plt>
  83b84d:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83b850:	8d 50 ff             	lea    edx,[rax-0x1]
  83b853:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83b856:	eb b0                	jmp    83b808 <CCharacter::getItem(CItem*, CLevel&)+0x668>
  83b858:	4c 89 e7             	mov    rdi,r12
  83b85b:	48 89 c3             	mov    rbx,rax
  83b85e:	e8 75 90 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83b863:	eb d3                	jmp    83b838 <CCharacter::getItem(CItem*, CLevel&)+0x698>
  83b865:	48 89 c3             	mov    rbx,rax
  83b868:	4c 89 e7             	mov    rdi,r12
  83b86b:	e8 68 90 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83b870:	eb c6                	jmp    83b838 <CCharacter::getItem(CItem*, CLevel&)+0x698>
  83b872:	48 89 c3             	mov    rbx,rax
  83b875:	4c 89 ff             	mov    rdi,r15
  83b878:	e8 5b 90 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83b87d:	eb e9                	jmp    83b868 <CCharacter::getItem(CItem*, CLevel&)+0x6c8>
  83b87f:	4c 89 f7             	mov    rdi,r14
  83b882:	48 89 c3             	mov    rbx,rax
  83b885:	e8 fe a9 d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  83b88a:	eb e9                	jmp    83b875 <CCharacter::getItem(CItem*, CLevel&)+0x6d5>
  83b88c:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83b88f:	8d 50 ff             	lea    edx,[rax-0x1]
  83b892:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83b895:	e9 07 fd ff ff       	jmp    83b5a1 <CCharacter::getItem(CItem*, CLevel&)+0x401>
  83b89a:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83b89d:	8d 50 ff             	lea    edx,[rax-0x1]
  83b8a0:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83b8a3:	e9 d4 fe ff ff       	jmp    83b77c <CCharacter::getItem(CItem*, CLevel&)+0x5dc>
  83b8a8:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83b8ab:	8d 50 ff             	lea    edx,[rax-0x1]
  83b8ae:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83b8b1:	e9 f6 fe ff ff       	jmp    83b7ac <CCharacter::getItem(CItem*, CLevel&)+0x60c>
  83b8b6:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83b8b9:	8d 50 ff             	lea    edx,[rax-0x1]
  83b8bc:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83b8bf:	e9 18 ff ff ff       	jmp    83b7dc <CCharacter::getItem(CItem*, CLevel&)+0x63c>
  83b8c4:	66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 cs nop WORD PTR [rax+rax*1+0x0]

