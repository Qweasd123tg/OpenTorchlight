# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000811230 <CCharacter::interrupt(bool)>:
  811230:	48 89 5c 24 e0       	mov    QWORD PTR [rsp-0x20],rbx
  811235:	48 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],rbp
  81123a:	48 89 fb             	mov    rbx,rdi
  81123d:	4c 89 64 24 f0       	mov    QWORD PTR [rsp-0x10],r12
  811242:	4c 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],r13
  811247:	48 81 ec 88 00 00 00 	sub    rsp,0x88
  81124e:	48 8b bf 18 07 00 00 	mov    rdi,QWORD PTR [rdi+0x718]
  811255:	89 f5                	mov    ebp,esi
  811257:	48 85 ff             	test   rdi,rdi
  81125a:	74 34                	je     811290 <CCharacter::interrupt(bool)+0x60>
  81125c:	be 02 00 00 00       	mov    esi,0x2
  811261:	e8 da f9 53 00       	call   d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>
  811266:	84 c0                	test   al,al
  811268:	74 26                	je     811290 <CCharacter::interrupt(bool)+0x60>
  81126a:	48 8b 5c 24 68       	mov    rbx,QWORD PTR [rsp+0x68]
  81126f:	48 8b 6c 24 70       	mov    rbp,QWORD PTR [rsp+0x70]
  811274:	4c 8b 64 24 78       	mov    r12,QWORD PTR [rsp+0x78]
  811279:	4c 8b ac 24 80 00 00 00 	mov    r13,QWORD PTR [rsp+0x80]
  811281:	48 81 c4 88 00 00 00 	add    rsp,0x88
  811288:	c3                   	ret
  811289:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  811290:	8b 83 30 03 00 00    	mov    eax,DWORD PTR [rbx+0x330]
  811296:	83 f8 10             	cmp    eax,0x10
  811299:	74 cf                	je     81126a <CCharacter::interrupt(bool)+0x3a>
  81129b:	83 f8 29             	cmp    eax,0x29
  81129e:	74 ca                	je     81126a <CCharacter::interrupt(bool)+0x3a>
  8112a0:	83 f8 28             	cmp    eax,0x28
  8112a3:	74 c5                	je     81126a <CCharacter::interrupt(bool)+0x3a>
  8112a5:	83 f8 23             	cmp    eax,0x23
  8112a8:	74 c0                	je     81126a <CCharacter::interrupt(bool)+0x3a>
  8112aa:	48 83 bb 98 03 00 00 00 	cmp    QWORD PTR [rbx+0x398],0x0
  8112b2:	74 66                	je     81131a <CCharacter::interrupt(bool)+0xea>
  8112b4:	80 bb 67 02 00 00 00 	cmp    BYTE PTR [rbx+0x267],0x0
  8112bb:	75 1a                	jne    8112d7 <CCharacter::interrupt(bool)+0xa7>
  8112bd:	f3 0f 10 83 80 03 00 00 	movss  xmm0,DWORD PTR [rbx+0x380]
  8112c5:	0f 2e 05 2c 35 79 00 	ucomiss xmm0,DWORD PTR [rip+0x79352c]        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  8112cc:	76 4c                	jbe    81131a <CCharacter::interrupt(bool)+0xea>
  8112ce:	80 bb 7d 03 00 00 00 	cmp    BYTE PTR [rbx+0x37d],0x0
  8112d5:	75 43                	jne    81131a <CCharacter::interrupt(bool)+0xea>
  8112d7:	80 bb a8 03 00 00 00 	cmp    BYTE PTR [rbx+0x3a8],0x0
  8112de:	74 8a                	je     81126a <CCharacter::interrupt(bool)+0x3a>
  8112e0:	4c 8d 64 24 50       	lea    r12,[rsp+0x50]
  8112e5:	48 8d 54 24 5f       	lea    rdx,[rsp+0x5f]
  8112ea:	be 04 99 fc 00       	mov    esi,0xfc9904
  8112ef:	4c 89 e7             	mov    rdi,r12
  8112f2:	e8 01 50 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8112f7:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8112fe:	4c 89 e6             	mov    rsi,r12
  811301:	e8 ba 12 09 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  811306:	4c 89 e7             	mov    rdi,r12
  811309:	41 89 c5             	mov    r13d,eax
  81130c:	e8 77 4f d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811311:	45 84 ed             	test   r13b,r13b
  811314:	0f 84 56 01 00 00    	je     811470 <CCharacter::interrupt(bool)+0x240>
  81131a:	45 31 e4             	xor    r12d,r12d
  81131d:	40 84 ed             	test   bpl,bpl
  811320:	0f 85 fa 00 00 00    	jne    811420 <CCharacter::interrupt(bool)+0x1f0>
  811326:	31 ed                	xor    ebp,ebp
  811328:	8b 83 30 03 00 00    	mov    eax,DWORD PTR [rbx+0x330]
  81132e:	83 f8 10             	cmp    eax,0x10
  811331:	0f 84 33 ff ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  811337:	83 f8 28             	cmp    eax,0x28
  81133a:	0f 84 2a ff ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  811340:	83 f8 29             	cmp    eax,0x29
  811343:	0f 84 21 ff ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  811349:	83 f8 05             	cmp    eax,0x5
  81134c:	0f 84 18 ff ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  811352:	83 f8 06             	cmp    eax,0x6
  811355:	0f 84 0f ff ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  81135b:	48 8b bb c8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1c8]
  811362:	c7 83 78 03 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x378],0x0
  81136c:	c6 83 67 02 00 00 00 	mov    BYTE PTR [rbx+0x267],0x0
  811373:	c7 83 80 03 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x380],0x0
  81137d:	48 85 ff             	test   rdi,rdi
  811380:	74 0b                	je     81138d <CCharacter::interrupt(bool)+0x15d>
  811382:	31 c9                	xor    ecx,ecx
  811384:	31 d2                	xor    edx,edx
  811386:	31 f6                	xor    esi,esi
  811388:	e8 33 9a 4b 00       	call   ccadc0 <CSkillManager::stopAllSkills(bool, bool, bool)>
  81138d:	40 84 ed             	test   bpl,bpl
  811390:	0f 85 4a 01 00 00    	jne    8114e0 <CCharacter::interrupt(bool)+0x2b0>
  811396:	80 bb 64 02 00 00 00 	cmp    BYTE PTR [rbx+0x264],0x0
  81139d:	74 0a                	je     8113a9 <CCharacter::interrupt(bool)+0x179>
  81139f:	c7 83 78 02 00 00 00 00 20 41 	mov    DWORD PTR [rbx+0x278],0x41200000
  8113a9:	8b 83 84 00 00 00    	mov    eax,DWORD PTR [rbx+0x84]
  8113af:	48 8b bb 98 06 00 00 	mov    rdi,QWORD PTR [rbx+0x698]
  8113b6:	c6 83 64 02 00 00 00 	mov    BYTE PTR [rbx+0x264],0x0
  8113bd:	89 83 1c 02 00 00    	mov    DWORD PTR [rbx+0x21c],eax
  8113c3:	8b 83 88 00 00 00    	mov    eax,DWORD PTR [rbx+0x88]
  8113c9:	48 85 ff             	test   rdi,rdi
  8113cc:	89 83 20 02 00 00    	mov    DWORD PTR [rbx+0x220],eax
  8113d2:	8b 83 8c 00 00 00    	mov    eax,DWORD PTR [rbx+0x8c]
  8113d8:	89 83 24 02 00 00    	mov    DWORD PTR [rbx+0x224],eax
  8113de:	74 15                	je     8113f5 <CCharacter::interrupt(bool)+0x1c5>
  8113e0:	31 f6                	xor    esi,esi
  8113e2:	e8 39 8c 23 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  8113e7:	48 8b bb 98 06 00 00 	mov    rdi,QWORD PTR [rbx+0x698]
  8113ee:	31 f6                	xor    esi,esi
  8113f0:	e8 0b 8b 23 00       	call   a49f00 <CWeaponTrail::setVisible(bool)>
  8113f5:	48 8b bb a0 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a0]
  8113fc:	48 85 ff             	test   rdi,rdi
  8113ff:	0f 84 65 fe ff ff    	je     81126a <CCharacter::interrupt(bool)+0x3a>
  811405:	31 f6                	xor    esi,esi
  811407:	e8 14 8c 23 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  81140c:	48 8b bb a0 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a0]
  811413:	31 f6                	xor    esi,esi
  811415:	e8 e6 8a 23 00       	call   a49f00 <CWeaponTrail::setVisible(bool)>
  81141a:	e9 4b fe ff ff       	jmp    81126a <CCharacter::interrupt(bool)+0x3a>
  81141f:	90                   	nop
  811420:	4c 8d 6c 24 30       	lea    r13,[rsp+0x30]
  811425:	48 8d 54 24 5d       	lea    rdx,[rsp+0x5d]
  81142a:	be 04 99 fc 00       	mov    esi,0xfc9904
  81142f:	4c 89 ef             	mov    rdi,r13
  811432:	e8 c1 4e d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811437:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  81143e:	4c 89 ee             	mov    rsi,r13
  811441:	41 bc 01 00 00 00    	mov    r12d,0x1
  811447:	e8 74 11 09 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  81144c:	84 c0                	test   al,al
  81144e:	4c 89 ef             	mov    rdi,r13
  811451:	41 0f 94 c4          	sete   r12b
  811455:	e8 2e 4e d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  81145a:	45 84 e4             	test   r12b,r12b
  81145d:	0f 85 07 fe ff ff    	jne    81126a <CCharacter::interrupt(bool)+0x3a>
  811463:	e9 c0 fe ff ff       	jmp    811328 <CCharacter::interrupt(bool)+0xf8>
  811468:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  811470:	48 8d 6c 24 40       	lea    rbp,[rsp+0x40]
  811475:	48 8d 54 24 5e       	lea    rdx,[rsp+0x5e]
  81147a:	be 3a 99 fc 00       	mov    esi,0xfc993a
  81147f:	48 89 ef             	mov    rdi,rbp
  811482:	e8 71 4e d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811487:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  81148e:	48 89 ee             	mov    rsi,rbp
  811491:	e8 4a 19 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  811496:	f3 0f 10 15 c2 72 79 00 	movss  xmm2,DWORD PTR [rip+0x7972c2]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  81149e:	ba 01 00 00 00       	mov    edx,0x1
  8114a3:	f3 0f 10 0d 51 33 79 00 	movss  xmm1,DWORD PTR [rip+0x793351]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8114ab:	89 c6                	mov    esi,eax
  8114ad:	f3 0f 10 05 33 72 79 00 	movss  xmm0,DWORD PTR [rip+0x797233]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  8114b5:	48 89 df             	mov    rdi,rbx
  8114b8:	e8 73 fc ff ff       	call   811130 <CCharacter::blendAnimation(int, bool, float, float, float)>
  8114bd:	48 89 ef             	mov    rdi,rbp
  8114c0:	e8 c3 4d d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8114c5:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8114c8:	31 f6                	xor    esi,esi
  8114ca:	48 89 df             	mov    rdi,rbx
  8114cd:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8114d3:	e9 4e fe ff ff       	jmp    811326 <CCharacter::interrupt(bool)+0xf6>
  8114d8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  8114e0:	48 8d 6c 24 20       	lea    rbp,[rsp+0x20]
  8114e5:	48 8d 54 24 5c       	lea    rdx,[rsp+0x5c]
  8114ea:	be 04 99 fc 00       	mov    esi,0xfc9904
  8114ef:	48 89 ef             	mov    rdi,rbp
  8114f2:	e8 01 4e d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8114f7:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8114fe:	48 89 ee             	mov    rsi,rbp
  811501:	e8 ba 10 09 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  811506:	48 89 ef             	mov    rdi,rbp
  811509:	41 89 c4             	mov    r12d,eax
  81150c:	e8 77 4d d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811511:	45 84 e4             	test   r12b,r12b
  811514:	74 52                	je     811568 <CCharacter::interrupt(bool)+0x338>
  811516:	48 8d 6c 24 10       	lea    rbp,[rsp+0x10]
  81151b:	48 8d 54 24 5b       	lea    rdx,[rsp+0x5b]
  811520:	be 04 99 fc 00       	mov    esi,0xfc9904
  811525:	48 89 ef             	mov    rdi,rbp
  811528:	e8 cb 4d d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  81152d:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  811534:	48 89 ee             	mov    rsi,rbp
  811537:	e8 a4 18 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  81153c:	f3 0f 10 15 1c 72 79 00 	movss  xmm2,DWORD PTR [rip+0x79721c]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  811544:	31 d2                	xor    edx,edx
  811546:	f3 0f 10 0d ae 32 79 00 	movss  xmm1,DWORD PTR [rip+0x7932ae]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  81154e:	89 c6                	mov    esi,eax
  811550:	f3 0f 10 05 90 71 79 00 	movss  xmm0,DWORD PTR [rip+0x797190]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  811558:	48 89 df             	mov    rdi,rbx
  81155b:	e8 d0 fb ff ff       	call   811130 <CCharacter::blendAnimation(int, bool, float, float, float)>
  811560:	48 89 ef             	mov    rdi,rbp
  811563:	e8 20 4d d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811568:	48 8d 54 24 5a       	lea    rdx,[rsp+0x5a]
  81156d:	be 3a 99 fc 00       	mov    esi,0xfc993a
  811572:	48 89 e7             	mov    rdi,rsp
  811575:	e8 7e 4d d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  81157a:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  811581:	f3 0f 10 0d 73 32 79 00 	movss  xmm1,DWORD PTR [rip+0x793273]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  811589:	f3 0f 10 05 57 71 79 00 	movss  xmm0,DWORD PTR [rip+0x797157]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  811591:	ba 01 00 00 00       	mov    edx,0x1
  811596:	48 89 e6             	mov    rsi,rsp
  811599:	e8 22 2d 09 00       	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  81159e:	48 89 e7             	mov    rdi,rsp
  8115a1:	e8 e2 4c d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8115a6:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8115a9:	be 1d 00 00 00       	mov    esi,0x1d
  8115ae:	48 89 df             	mov    rdi,rbx
  8115b1:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8115b7:	e9 da fd ff ff       	jmp    811396 <CCharacter::interrupt(bool)+0x166>
  8115bc:	48 89 ef             	mov    rdi,rbp
  8115bf:	48 89 c3             	mov    rbx,rax
  8115c2:	e8 c1 4c d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8115c7:	48 89 df             	mov    rdi,rbx
  8115ca:	e8 c9 2e d4 ff       	call   554498 <_Unwind_Resume@plt>
  8115cf:	48 89 c3             	mov    rbx,rax
  8115d2:	eb f3                	jmp    8115c7 <CCharacter::interrupt(bool)+0x397>
  8115d4:	48 89 e7             	mov    rdi,rsp
  8115d7:	48 89 c3             	mov    rbx,rax
  8115da:	e8 a9 4c d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8115df:	eb e6                	jmp    8115c7 <CCharacter::interrupt(bool)+0x397>
  8115e1:	eb ec                	jmp    8115cf <CCharacter::interrupt(bool)+0x39f>
  8115e3:	4c 89 e7             	mov    rdi,r12
  8115e6:	48 89 c3             	mov    rbx,rax
  8115e9:	e8 9a 4c d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8115ee:	66 90                	xchg   ax,ax
  8115f0:	eb d5                	jmp    8115c7 <CCharacter::interrupt(bool)+0x397>
  8115f2:	eb db                	jmp    8115cf <CCharacter::interrupt(bool)+0x39f>
  8115f4:	eb d9                	jmp    8115cf <CCharacter::interrupt(bool)+0x39f>
  8115f6:	45 84 e4             	test   r12b,r12b
  8115f9:	48 89 c3             	mov    rbx,rax
  8115fc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  811600:	74 c5                	je     8115c7 <CCharacter::interrupt(bool)+0x397>
  811602:	4c 89 ef             	mov    rdi,r13
  811605:	e8 7e 4c d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  81160a:	eb bb                	jmp    8115c7 <CCharacter::interrupt(bool)+0x397>
  81160c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  811610:	eb aa                	jmp    8115bc <CCharacter::interrupt(bool)+0x38c>
  811612:	eb bb                	jmp    8115cf <CCharacter::interrupt(bool)+0x39f>
  811614:	eb a6                	jmp    8115bc <CCharacter::interrupt(bool)+0x38c>
  811616:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  811620:	eb ad                	jmp    8115cf <CCharacter::interrupt(bool)+0x39f>
  811622:	66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]

