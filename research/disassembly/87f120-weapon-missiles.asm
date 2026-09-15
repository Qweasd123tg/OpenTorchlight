000000000087f120 <CEquipment::fireMissiles(CCharacter*, CCharacter*)>:
  87f120:	41 57                	push   r15
  87f122:	41 56                	push   r14
  87f124:	41 55                	push   r13
  87f126:	41 54                	push   r12
  87f128:	49 89 d4             	mov    r12,rdx
  87f12b:	55                   	push   rbp
  87f12c:	48 89 f5             	mov    rbp,rsi
  87f12f:	53                   	push   rbx
  87f130:	48 89 fb             	mov    rbx,rdi
  87f133:	48 81 ec b8 00 00 00 	sub    rsp,0xb8
  87f13a:	48 8b 87 00 04 00 00 	mov    rax,QWORD PTR [rdi+0x400]
  87f141:	48 83 78 e8 00       	cmp    QWORD PTR [rax-0x18],0x0
  87f146:	0f 84 8c 04 00 00    	je     87f5d8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4b8>
  87f14c:	48 85 f6             	test   rsi,rsi
  87f14f:	0f 84 83 04 00 00    	je     87f5d8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4b8>
  87f155:	48 89 f7             	mov    rdi,rsi
  87f158:	e8 c3 0a f9 ff       	call   80fc20 <CCharacter::getWeaponInLeftHand()>
  87f15d:	48 39 c3             	cmp    rbx,rax
  87f160:	0f 84 a2 05 00 00    	je     87f708 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x5e8>
  87f166:	48 8b bd e8 02 00 00 	mov    rdi,QWORD PTR [rbp+0x2e8]
  87f16d:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  87f170:	ff 90 00 02 00 00    	call   QWORD PTR [rax+0x200]
  87f176:	f3 0f 10 10          	movss  xmm2,DWORD PTR [rax]
  87f17a:	f3 0f 11 54 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm2
  87f180:	f3 0f 10 40 04       	movss  xmm0,DWORD PTR [rax+0x4]
  87f185:	f3 0f 11 44 24 2c    	movss  DWORD PTR [rsp+0x2c],xmm0
  87f18b:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  87f190:	f3 0f 11 54 24 28    	movss  DWORD PTR [rsp+0x28],xmm2
  87f196:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  87f19a:	48 89 ef             	mov    rdi,rbp
  87f19d:	ff 90 38 01 00 00    	call   QWORD PTR [rax+0x138]
  87f1a3:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  87f1a9:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  87f1ae:	4d 85 e4             	test   r12,r12
  87f1b1:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  87f1b7:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  87f1bc:	48 89 84 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rax
  87f1c4:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  87f1c8:	89 84 24 88 00 00 00 	mov    DWORD PTR [rsp+0x88],eax
  87f1cf:	0f 84 d3 00 00 00    	je     87f2a8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x188>
  87f1d5:	be 01 00 00 00       	mov    esi,0x1
  87f1da:	4c 89 e7             	mov    rdi,r12
  87f1dd:	e8 9e 7e 16 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  87f1e2:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  87f1e8:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  87f1ed:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  87f1f3:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  87f1f8:	f3 0f 10 4c 24 74    	movss  xmm1,DWORD PTR [rsp+0x74]
  87f1fe:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  87f203:	f3 0f 10 54 24 70    	movss  xmm2,DWORD PTR [rsp+0x70]
  87f209:	f3 0f 5c 4c 24 2c    	subss  xmm1,DWORD PTR [rsp+0x2c]
  87f20f:	f3 0f 5c 54 24 1c    	subss  xmm2,DWORD PTR [rsp+0x1c]
  87f215:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  87f219:	89 44 24 78          	mov    DWORD PTR [rsp+0x78],eax
  87f21d:	f3 0f 10 44 24 78    	movss  xmm0,DWORD PTR [rsp+0x78]
  87f223:	f3 0f 5c 44 24 28    	subss  xmm0,DWORD PTR [rsp+0x28]
  87f229:	0f 28 e1             	movaps xmm4,xmm1
  87f22c:	0f 28 da             	movaps xmm3,xmm2
  87f22f:	f3 0f 11 94 24 80 00 00 00 	movss  DWORD PTR [rsp+0x80],xmm2
  87f238:	f3 0f 59 e1          	mulss  xmm4,xmm1
  87f23c:	f3 0f 11 8c 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm1
  87f245:	f3 0f 59 da          	mulss  xmm3,xmm2
  87f249:	f3 0f 11 84 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm0
  87f252:	f3 0f 58 dc          	addss  xmm3,xmm4
  87f256:	0f 28 e0             	movaps xmm4,xmm0
  87f259:	f3 0f 59 e0          	mulss  xmm4,xmm0
  87f25d:	f3 0f 58 dc          	addss  xmm3,xmm4
  87f261:	f3 0f 51 db          	sqrtss xmm3,xmm3
  87f265:	0f 14 db             	unpcklps xmm3,xmm3
  87f268:	0f 5a e3             	cvtps2pd xmm4,xmm3
  87f26b:	66 0f 2e 25 2d 95 72 00 	ucomisd xmm4,QWORD PTR [rip+0x72952d]        # fa87a0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x100>
  87f273:	76 33                	jbe    87f2a8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x188>
  87f275:	f3 0f 10 25 7f 55 72 00 	movss  xmm4,DWORD PTR [rip+0x72557f]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  87f27d:	f3 0f 5e e3          	divss  xmm4,xmm3
  87f281:	f3 0f 59 d4          	mulss  xmm2,xmm4
  87f285:	f3 0f 59 cc          	mulss  xmm1,xmm4
  87f289:	f3 0f 59 c4          	mulss  xmm0,xmm4
  87f28d:	f3 0f 11 94 24 80 00 00 00 	movss  DWORD PTR [rsp+0x80],xmm2
  87f296:	f3 0f 11 8c 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm1
  87f29f:	f3 0f 11 84 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm0
  87f2a8:	4c 8d ac 24 a0 00 00 00 	lea    r13,[rsp+0xa0]
  87f2b0:	48 8d 94 24 af 00 00 00 	lea    rdx,[rsp+0xaf]
  87f2b8:	be 70 b9 fc 00       	mov    esi,0xfcb970
  87f2bd:	4c 89 ef             	mov    rdi,r13
  87f2c0:	e8 93 6b cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  87f2c5:	48 8b bd b0 01 00 00 	mov    rdi,QWORD PTR [rbp+0x1b0]
  87f2cc:	f3 0f 10 05 28 55 72 00 	movss  xmm0,DWORD PTR [rip+0x725528]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  87f2d4:	4c 89 ee             	mov    rsi,r13
  87f2d7:	e8 a4 ff 3d 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  87f2dc:	48 8b bc 24 a0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xa0]
  87f2e4:	f3 0f 11 44 24 20    	movss  DWORD PTR [rsp+0x20],xmm0
  87f2ea:	48 83 ef 18          	sub    rdi,0x18
  87f2ee:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  87f2f5:	0f 85 47 05 00 00    	jne    87f842 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x722>
  87f2fb:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  87f2fe:	48 89 df             	mov    rdi,rbx
  87f301:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  87f307:	48 85 c0             	test   rax,rax
  87f30a:	0f 84 a0 03 00 00    	je     87f6b0 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x590>
  87f310:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  87f313:	48 89 df             	mov    rdi,rbx
  87f316:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  87f31c:	48 8b 78 60          	mov    rdi,QWORD PTR [rax+0x60]
  87f320:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  87f323:	ff 90 d8 00 00 00    	call   QWORD PTR [rax+0xd8]
  87f329:	8b 50 18             	mov    edx,DWORD PTR [rax+0x18]
  87f32c:	83 fa 01             	cmp    edx,0x1
  87f32f:	0f 84 bb 02 00 00    	je     87f5f0 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4d0>
  87f335:	83 fa 02             	cmp    edx,0x2
  87f338:	0f 84 ba 03 00 00    	je     87f6f8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x5d8>
  87f33e:	f3 0f 10 0d 6a 4e ba 00 	movss  xmm1,DWORD PTR [rip+0xba4e6a]        # 14241b0 <Ogre::Vector3::ZERO+0x4>
  87f346:	f3 0f 10 44 24 20    	movss  xmm0,DWORD PTR [rsp+0x20]
  87f34c:	f3 0f 59 05 18 74 74 00 	mulss  xmm0,DWORD PTR [rip+0x747418]        # fc676c <typeinfo name for iCollision+0x1c>
  87f354:	f3 0f 10 94 24 80 00 00 00 	movss  xmm2,DWORD PTR [rsp+0x80]
  87f35d:	f3 0f 59 d1          	mulss  xmm2,xmm1
  87f361:	f3 0f 59 d0          	mulss  xmm2,xmm0
  87f365:	f3 0f 58 54 24 1c    	addss  xmm2,DWORD PTR [rsp+0x1c]
  87f36b:	f3 0f 11 54 24 24    	movss  DWORD PTR [rsp+0x24],xmm2
  87f371:	f3 0f 10 94 24 84 00 00 00 	movss  xmm2,DWORD PTR [rsp+0x84]
  87f37a:	f3 0f 59 d1          	mulss  xmm2,xmm1
  87f37e:	f3 0f 59 8c 24 88 00 00 00 	mulss  xmm1,DWORD PTR [rsp+0x88]
  87f387:	f3 0f 59 d0          	mulss  xmm2,xmm0
  87f38b:	f3 0f 59 c1          	mulss  xmm0,xmm1
  87f38f:	f3 0f 11 54 24 20    	movss  DWORD PTR [rsp+0x20],xmm2
  87f395:	f3 0f 10 54 24 2c    	movss  xmm2,DWORD PTR [rsp+0x2c]
  87f39b:	f3 0f 58 54 24 20    	addss  xmm2,DWORD PTR [rsp+0x20]
  87f3a1:	f3 0f 11 54 24 20    	movss  DWORD PTR [rsp+0x20],xmm2
  87f3a7:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  87f3ad:	f3 0f 58 d0          	addss  xmm2,xmm0
  87f3b1:	f3 0f 11 54 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm2
  87f3b7:	48 8b 6b 68          	mov    rbp,QWORD PTR [rbx+0x68]
  87f3bb:	48 89 ef             	mov    rdi,rbp
  87f3be:	e8 4d 01 4f 00       	call   d6f510 <CResourceManager::getMissilePreloader()>
  87f3c3:	48 8d 93 00 04 00 00 	lea    rdx,[rbx+0x400]
  87f3ca:	48 89 ee             	mov    rsi,rbp
  87f3cd:	48 89 c7             	mov    rdi,rax
  87f3d0:	e8 fb bc 48 00       	call   d0b0d0 <CMissilePreloader::createNewMissileRef(CResourceManager*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  87f3d5:	48 85 c0             	test   rax,rax
  87f3d8:	48 89 c5             	mov    rbp,rax
  87f3db:	0f 84 f7 01 00 00    	je     87f5d8 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4b8>
  87f3e1:	8b b0 d0 01 00 00    	mov    esi,DWORD PTR [rax+0x1d0]
  87f3e7:	4c 8d ab 30 02 00 00 	lea    r13,[rbx+0x230]
  87f3ee:	85 f6                	test   esi,esi
  87f3f0:	0f 84 ee 03 00 00    	je     87f7e4 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x6c4>
  87f3f6:	48 8b b8 c8 01 00 00 	mov    rdi,QWORD PTR [rax+0x1c8]
  87f3fd:	31 c0                	xor    eax,eax
  87f3ff:	4c 3b 2f             	cmp    r13,QWORD PTR [rdi]
  87f402:	48 89 fa             	mov    rdx,rdi
  87f405:	75 1a                	jne    87f421 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x301>
  87f407:	eb 3f                	jmp    87f448 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x328>
  87f409:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  87f410:	48 8b 4a 08          	mov    rcx,QWORD PTR [rdx+0x8]
  87f414:	48 83 c2 08          	add    rdx,0x8
  87f418:	49 39 cd             	cmp    r13,rcx
  87f41b:	0f 84 5f 02 00 00    	je     87f680 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x560>
  87f421:	83 c0 01             	add    eax,0x1
  87f424:	39 f0                	cmp    eax,esi
  87f426:	72 e8                	jb     87f410 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x2f0>
  87f428:	44 8b b5 d4 01 00 00 	mov    r14d,DWORD PTR [rbp+0x1d4]
  87f42f:	49 89 ff             	mov    r15,rdi
  87f432:	41 39 f6             	cmp    r14d,esi
  87f435:	0f 86 05 03 00 00    	jbe    87f740 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x620>
  87f43b:	89 f6                	mov    esi,esi
  87f43d:	4d 89 2c f7          	mov    QWORD PTR [r15+rsi*8],r13
  87f441:	83 85 d0 01 00 00 01 	add    DWORD PTR [rbp+0x1d0],0x1
  87f448:	4d 85 e4             	test   r12,r12
  87f44b:	0f 84 41 02 00 00    	je     87f692 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x572>
  87f451:	be 01 00 00 00       	mov    esi,0x1
  87f456:	4c 89 e7             	mov    rdi,r12
  87f459:	e8 22 7c 16 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  87f45e:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  87f464:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  87f469:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  87f46f:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  87f474:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  87f479:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  87f47d:	89 44 24 58          	mov    DWORD PTR [rsp+0x58],eax
  87f481:	f3 0f 10 2d af 56 ba 00 	movss  xmm5,DWORD PTR [rip+0xba56af]        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  87f489:	4c 8d 6c 24 40       	lea    r13,[rsp+0x40]
  87f48e:	f3 0f 10 35 9e 56 ba 00 	movss  xmm6,DWORD PTR [rip+0xba569e]        # 1424b34 <Ogre::Vector3::UNIT_Y>
  87f496:	48 8d 8c 24 80 00 00 00 	lea    rcx,[rsp+0x80]
  87f49e:	0f 28 fd             	movaps xmm7,xmm5
  87f4a1:	48 8d 74 24 60       	lea    rsi,[rsp+0x60]
  87f4a6:	0f 28 d6             	movaps xmm2,xmm6
  87f4a9:	ba 34 4b 42 01       	mov    edx,0x1424b34
  87f4ae:	f3 0f 10 a4 24 84 00 00 00 	movss  xmm4,DWORD PTR [rsp+0x84]
  87f4b7:	4c 89 ef             	mov    rdi,r13
  87f4ba:	f3 0f 10 8c 24 80 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x80]
  87f4c3:	f3 0f 59 d4          	mulss  xmm2,xmm4
  87f4c7:	f3 0f 10 1d 6d 56 ba 00 	movss  xmm3,DWORD PTR [rip+0xba566d]        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  87f4cf:	f3 0f 59 f9          	mulss  xmm7,xmm1
  87f4d3:	f3 0f 10 84 24 88 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x88]
  87f4dc:	f3 0f 59 cb          	mulss  xmm1,xmm3
  87f4e0:	f3 0f 59 f0          	mulss  xmm6,xmm0
  87f4e4:	f3 0f 59 dc          	mulss  xmm3,xmm4
  87f4e8:	f3 0f 59 c5          	mulss  xmm0,xmm5
  87f4ec:	f3 0f 5c d7          	subss  xmm2,xmm7
  87f4f0:	f3 0f 5c ce          	subss  xmm1,xmm6
  87f4f4:	f3 0f 5c c3          	subss  xmm0,xmm3
  87f4f8:	f3 0f 11 54 24 68    	movss  DWORD PTR [rsp+0x68],xmm2
  87f4fe:	f3 0f 11 4c 24 64    	movss  DWORD PTR [rsp+0x64],xmm1
  87f504:	f3 0f 11 44 24 60    	movss  DWORD PTR [rsp+0x60],xmm0
  87f50a:	e8 69 4d cd ff       	call   554278 <Ogre::Quaternion::FromAxes(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&)@plt>
  87f50f:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  87f512:	48 89 df             	mov    rdi,rbx
  87f515:	ff 90 40 03 00 00    	call   QWORD PTR [rax+0x340]
  87f51b:	f3 0f 10 54 24 1c    	movss  xmm2,DWORD PTR [rsp+0x1c]
  87f521:	4c 89 e1             	mov    rcx,r12
  87f524:	f3 0f 10 44 24 20    	movss  xmm0,DWORD PTR [rsp+0x20]
  87f52a:	48 89 c6             	mov    rsi,rax
  87f52d:	f3 0f 11 94 24 98 00 00 00 	movss  DWORD PTR [rsp+0x98],xmm2
  87f536:	4c 89 ea             	mov    rdx,r13
  87f539:	48 89 ef             	mov    rdi,rbp
  87f53c:	f3 0f 10 54 24 24    	movss  xmm2,DWORD PTR [rsp+0x24]
  87f542:	f3 0f 11 94 24 90 00 00 00 	movss  DWORD PTR [rsp+0x90],xmm2
  87f54b:	f3 0f 11 84 24 94 00 00 00 	movss  DWORD PTR [rsp+0x94],xmm0
  87f554:	f3 0f 7e 54 24 50    	movq   xmm2,QWORD PTR [rsp+0x50]
  87f55a:	f3 0f 10 5c 24 58    	movss  xmm3,DWORD PTR [rsp+0x58]
  87f560:	f3 0f 7e 84 24 90 00 00 00 	movq   xmm0,QWORD PTR [rsp+0x90]
  87f569:	f3 0f 10 4c 24 1c    	movss  xmm1,DWORD PTR [rsp+0x1c]
  87f56f:	e8 9c 50 48 00       	call   d04610 <CMissile::fireMissile(CBaseUnit*, Ogre::Vector3, Ogre::Quaternion const&, CPositionableObject*, Ogre::Vector3)>
  87f574:	31 f6                	xor    esi,esi
  87f576:	bf 10 00 00 00       	mov    edi,0x10
  87f57b:	31 c9                	xor    ecx,ecx
  87f57d:	31 d2                	xor    edx,edx
  87f57f:	e8 94 3d cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  87f584:	48 89 ef             	mov    rdi,rbp
  87f587:	c7 40 08 ff ff ff ff 	mov    DWORD PTR [rax+0x8],0xffffffff
  87f58e:	48 c7 00 00 00 00 00 	mov    QWORD PTR [rax],0x0
  87f595:	48 89 c6             	mov    rsi,rax
  87f598:	49 89 c4             	mov    r12,rax
  87f59b:	e8 20 a2 4f 00       	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  87f5a0:	41 89 44 24 08       	mov    DWORD PTR [r12+0x8],eax
  87f5a5:	49 89 2c 24          	mov    QWORD PTR [r12],rbp
  87f5a9:	8b 83 18 04 00 00    	mov    eax,DWORD PTR [rbx+0x418]
  87f5af:	8b ab 1c 04 00 00    	mov    ebp,DWORD PTR [rbx+0x41c]
  87f5b5:	39 e8                	cmp    eax,ebp
  87f5b7:	73 47                	jae    87f600 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4e0>
  87f5b9:	4c 8b ab 10 04 00 00 	mov    r13,QWORD PTR [rbx+0x410]
  87f5c0:	89 c0                	mov    eax,eax
  87f5c2:	4d 89 64 c5 00       	mov    QWORD PTR [r13+rax*8+0x0],r12
  87f5c7:	b8 01 00 00 00       	mov    eax,0x1
  87f5cc:	83 83 18 04 00 00 01 	add    DWORD PTR [rbx+0x418],0x1
  87f5d3:	eb 05                	jmp    87f5da <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4ba>
  87f5d5:	0f 1f 00             	nop    DWORD PTR [rax]
  87f5d8:	31 c0                	xor    eax,eax
  87f5da:	48 81 c4 b8 00 00 00 	add    rsp,0xb8
  87f5e1:	5b                   	pop    rbx
  87f5e2:	5d                   	pop    rbp
  87f5e3:	41 5c                	pop    r12
  87f5e5:	41 5d                	pop    r13
  87f5e7:	41 5e                	pop    r14
  87f5e9:	41 5f                	pop    r15
  87f5eb:	c3                   	ret
  87f5ec:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  87f5f0:	f3 0f 10 48 10       	movss  xmm1,DWORD PTR [rax+0x10]
  87f5f5:	f3 0f 5c 48 04       	subss  xmm1,DWORD PTR [rax+0x4]
  87f5fa:	e9 47 fd ff ff       	jmp    87f346 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x226>
  87f5ff:	90                   	nop
  87f600:	48 83 bb 10 04 00 00 00 	cmp    QWORD PTR [rbx+0x410],0x0
  87f608:	0f 84 a8 01 00 00    	je     87f7b6 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x696>
  87f60e:	03 ab 20 04 00 00    	add    ebp,DWORD PTR [rbx+0x420]
  87f614:	89 ef                	mov    edi,ebp
  87f616:	48 c1 e7 03          	shl    rdi,0x3
  87f61a:	e8 c9 44 cd ff       	call   553ae8 <operator new[](unsigned long)@plt>
  87f61f:	44 8b b3 1c 04 00 00 	mov    r14d,DWORD PTR [rbx+0x41c]
  87f626:	49 89 c5             	mov    r13,rax
  87f629:	45 85 f6             	test   r14d,r14d
  87f62c:	74 1f                	je     87f64d <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x52d>
  87f62e:	31 c0                	xor    eax,eax
  87f630:	48 8b 8b 10 04 00 00 	mov    rcx,QWORD PTR [rbx+0x410]
  87f637:	89 c2                	mov    edx,eax
  87f639:	83 c0 01             	add    eax,0x1
  87f63c:	48 8b 0c d1          	mov    rcx,QWORD PTR [rcx+rdx*8]
  87f640:	49 89 4c d5 00       	mov    QWORD PTR [r13+rdx*8+0x0],rcx
  87f645:	3b 83 1c 04 00 00    	cmp    eax,DWORD PTR [rbx+0x41c]
  87f64b:	72 e3                	jb     87f630 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x510>
  87f64d:	48 8b bb 10 04 00 00 	mov    rdi,QWORD PTR [rbx+0x410]
  87f654:	48 85 ff             	test   rdi,rdi
  87f657:	74 05                	je     87f65e <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x53e>
  87f659:	e8 da 3f cd ff       	call   553638 <operator delete[](void*)@plt>
  87f65e:	4c 89 ab 10 04 00 00 	mov    QWORD PTR [rbx+0x410],r13
  87f665:	89 ab 1c 04 00 00    	mov    DWORD PTR [rbx+0x41c],ebp
  87f66b:	8b 83 18 04 00 00    	mov    eax,DWORD PTR [rbx+0x418]
  87f671:	e9 4a ff ff ff       	jmp    87f5c0 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4a0>
  87f676:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  87f680:	83 f8 ff             	cmp    eax,0xffffffff
  87f683:	0f 84 9f fd ff ff    	je     87f428 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x308>
  87f689:	4d 85 e4             	test   r12,r12
  87f68c:	0f 85 bf fd ff ff    	jne    87f451 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x331>
  87f692:	48 8b 05 13 4b ba 00 	mov    rax,QWORD PTR [rip+0xba4b13]        # 14241ac <Ogre::Vector3::ZERO>
  87f699:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  87f69e:	8b 05 10 4b ba 00    	mov    eax,DWORD PTR [rip+0xba4b10]        # 14241b4 <Ogre::Vector3::ZERO+0x8>
  87f6a4:	89 44 24 58          	mov    DWORD PTR [rsp+0x58],eax
  87f6a8:	e9 d4 fd ff ff       	jmp    87f481 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x361>
  87f6ad:	0f 1f 00             	nop    DWORD PTR [rax]
  87f6b0:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  87f6b6:	f3 0f 58 84 24 80 00 00 00 	addss  xmm0,DWORD PTR [rsp+0x80]
  87f6bf:	f3 0f 10 54 24 2c    	movss  xmm2,DWORD PTR [rsp+0x2c]
  87f6c5:	f3 0f 58 94 24 84 00 00 00 	addss  xmm2,DWORD PTR [rsp+0x84]
  87f6ce:	f3 0f 11 44 24 24    	movss  DWORD PTR [rsp+0x24],xmm0
  87f6d4:	f3 0f 10 44 24 28    	movss  xmm0,DWORD PTR [rsp+0x28]
  87f6da:	f3 0f 58 84 24 88 00 00 00 	addss  xmm0,DWORD PTR [rsp+0x88]
  87f6e3:	f3 0f 11 54 24 20    	movss  DWORD PTR [rsp+0x20],xmm2
  87f6e9:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  87f6ef:	e9 c3 fc ff ff       	jmp    87f3b7 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x297>
  87f6f4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  87f6f8:	f3 0f 10 0d a8 4a ba 00 	movss  xmm1,DWORD PTR [rip+0xba4aa8]        # 14241a8 <Ogre::Math::POS_INFINITY>
  87f700:	e9 41 fc ff ff       	jmp    87f346 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x226>
  87f705:	0f 1f 00             	nop    DWORD PTR [rax]
  87f708:	48 8b bd f8 02 00 00 	mov    rdi,QWORD PTR [rbp+0x2f8]
  87f70f:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  87f712:	ff 90 00 02 00 00    	call   QWORD PTR [rax+0x200]
  87f718:	f3 0f 10 00          	movss  xmm0,DWORD PTR [rax]
  87f71c:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  87f722:	f3 0f 10 50 04       	movss  xmm2,DWORD PTR [rax+0x4]
  87f727:	f3 0f 11 54 24 2c    	movss  DWORD PTR [rsp+0x2c],xmm2
  87f72d:	f3 0f 10 40 08       	movss  xmm0,DWORD PTR [rax+0x8]
  87f732:	f3 0f 11 44 24 28    	movss  DWORD PTR [rsp+0x28],xmm0
  87f738:	e9 59 fa ff ff       	jmp    87f196 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x76>
  87f73d:	0f 1f 00             	nop    DWORD PTR [rax]
  87f740:	48 85 ff             	test   rdi,rdi
  87f743:	0f 84 a7 00 00 00    	je     87f7f0 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x6d0>
  87f749:	44 03 b5 d8 01 00 00 	add    r14d,DWORD PTR [rbp+0x1d8]
  87f750:	44 89 f7             	mov    edi,r14d
  87f753:	48 c1 e7 03          	shl    rdi,0x3
  87f757:	e8 8c 43 cd ff       	call   553ae8 <operator new[](unsigned long)@plt>
  87f75c:	49 89 c7             	mov    r15,rax
  87f75f:	8b 85 d4 01 00 00    	mov    eax,DWORD PTR [rbp+0x1d4]
  87f765:	85 c0                	test   eax,eax
  87f767:	74 23                	je     87f78c <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x66c>
  87f769:	31 c0                	xor    eax,eax
  87f76b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  87f770:	48 8b 8d c8 01 00 00 	mov    rcx,QWORD PTR [rbp+0x1c8]
  87f777:	89 c2                	mov    edx,eax
  87f779:	83 c0 01             	add    eax,0x1
  87f77c:	48 8b 0c d1          	mov    rcx,QWORD PTR [rcx+rdx*8]
  87f780:	49 89 0c d7          	mov    QWORD PTR [r15+rdx*8],rcx
  87f784:	3b 85 d4 01 00 00    	cmp    eax,DWORD PTR [rbp+0x1d4]
  87f78a:	72 e4                	jb     87f770 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x650>
  87f78c:	48 8b bd c8 01 00 00 	mov    rdi,QWORD PTR [rbp+0x1c8]
  87f793:	48 85 ff             	test   rdi,rdi
  87f796:	74 05                	je     87f79d <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x67d>
  87f798:	e8 9b 3e cd ff       	call   553638 <operator delete[](void*)@plt>
  87f79d:	4c 89 bd c8 01 00 00 	mov    QWORD PTR [rbp+0x1c8],r15
  87f7a4:	44 89 b5 d4 01 00 00 	mov    DWORD PTR [rbp+0x1d4],r14d
  87f7ab:	8b b5 d0 01 00 00    	mov    esi,DWORD PTR [rbp+0x1d0]
  87f7b1:	e9 85 fc ff ff       	jmp    87f43b <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x31b>
  87f7b6:	8b 83 20 04 00 00    	mov    eax,DWORD PTR [rbx+0x420]
  87f7bc:	48 8d 3c c5 00 00 00 00 	lea    rdi,[rax*8+0x0]
  87f7c4:	89 83 1c 04 00 00    	mov    DWORD PTR [rbx+0x41c],eax
  87f7ca:	e8 19 43 cd ff       	call   553ae8 <operator new[](unsigned long)@plt>
  87f7cf:	49 89 c5             	mov    r13,rax
  87f7d2:	48 89 83 10 04 00 00 	mov    QWORD PTR [rbx+0x410],rax
  87f7d9:	8b 83 18 04 00 00    	mov    eax,DWORD PTR [rbx+0x418]
  87f7df:	e9 dc fd ff ff       	jmp    87f5c0 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x4a0>
  87f7e4:	48 8b b8 c8 01 00 00 	mov    rdi,QWORD PTR [rax+0x1c8]
  87f7eb:	e9 38 fc ff ff       	jmp    87f428 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x308>
  87f7f0:	8b 85 d8 01 00 00    	mov    eax,DWORD PTR [rbp+0x1d8]
  87f7f6:	89 c7                	mov    edi,eax
  87f7f8:	89 85 d4 01 00 00    	mov    DWORD PTR [rbp+0x1d4],eax
  87f7fe:	48 c1 e7 03          	shl    rdi,0x3
  87f802:	e8 e1 42 cd ff       	call   553ae8 <operator new[](unsigned long)@plt>
  87f807:	8b b5 d0 01 00 00    	mov    esi,DWORD PTR [rbp+0x1d0]
  87f80d:	49 89 c7             	mov    r15,rax
  87f810:	48 89 85 c8 01 00 00 	mov    QWORD PTR [rbp+0x1c8],rax
  87f817:	e9 1f fc ff ff       	jmp    87f43b <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x31b>
  87f81c:	48 89 c3             	mov    rbx,rax
  87f81f:	48 89 df             	mov    rdi,rbx
  87f822:	e8 71 4c cd ff       	call   554498 <_Unwind_Resume@plt>
  87f827:	4c 89 e7             	mov    rdi,r12
  87f82a:	48 89 c3             	mov    rbx,rax
  87f82d:	e8 36 5a cd ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  87f832:	eb eb                	jmp    87f81f <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x6ff>
  87f834:	4c 89 ef             	mov    rdi,r13
  87f837:	48 89 c3             	mov    rbx,rax
  87f83a:	e8 99 50 cd ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  87f83f:	90                   	nop
  87f840:	eb dd                	jmp    87f81f <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x6ff>
  87f842:	b8 c8 41 55 00       	mov    eax,0x5541c8
  87f847:	48 85 c0             	test   rax,rax
  87f84a:	74 22                	je     87f86e <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x74e>
  87f84c:	83 c8 ff             	or     eax,0xffffffff
  87f84f:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  87f854:	85 c0                	test   eax,eax
  87f856:	0f 8f 9f fa ff ff    	jg     87f2fb <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x1db>
  87f85c:	48 8d b4 24 ae 00 00 00 	lea    rsi,[rsp+0xae]
  87f864:	e8 df 3c cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  87f869:	e9 8d fa ff ff       	jmp    87f2fb <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x1db>
  87f86e:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  87f871:	8d 50 ff             	lea    edx,[rax-0x1]
  87f874:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  87f877:	eb db                	jmp    87f854 <CEquipment::fireMissiles(CCharacter*, CCharacter*)+0x734>
  87f879:	90                   	nop
  87f87a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

