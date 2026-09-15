0000000000847280 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)>:
  847280:	41 57                	push   r15
  847282:	41 56                	push   r14
  847284:	41 89 d6             	mov    r14d,edx
  847287:	41 55                	push   r13
  847289:	49 89 f5             	mov    r13,rsi
  84728c:	41 54                	push   r12
  84728e:	55                   	push   rbp
  84728f:	53                   	push   rbx
  847290:	48 89 fb             	mov    rbx,rdi
  847293:	48 81 ec 68 02 00 00 	sub    rsp,0x268
  84729a:	f3 0f 11 84 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm0
  8472a3:	89 8c 24 8c 00 00 00 	mov    DWORD PTR [rsp+0x8c],ecx
  8472aa:	f3 0f 11 8c 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm1
  8472b3:	80 b7 7e 03 00 00 01 	xor    BYTE PTR [rdi+0x37e],0x1
  8472ba:	48 85 f6             	test   rsi,rsi
  8472bd:	0f 84 75 0c 00 00    	je     847f38 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xcb8>
  8472c3:	e8 58 89 fc ff       	call   80fc20 <CCharacter::getWeaponInLeftHand()>
  8472c8:	49 39 c5             	cmp    r13,rax
  8472cb:	0f 84 5f 07 00 00    	je     847a30 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7b0>
  8472d1:	48 89 df             	mov    rdi,rbx
  8472d4:	e8 77 89 fc ff       	call   80fc50 <CCharacter::getWeaponInRightHand()>
  8472d9:	49 39 c5             	cmp    r13,rax
  8472dc:	0f 84 f6 07 00 00    	je     847ad8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x858>
  8472e2:	49 8b 85 a0 02 00 00 	mov    rax,QWORD PTR [r13+0x2a0]
  8472e9:	48 85 c0             	test   rax,rax
  8472ec:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  8472f1:	0f 84 39 07 00 00    	je     847a30 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7b0>
  8472f7:	4d 89 ef             	mov    r15,r13
  8472fa:	48 8b bb 50 03 00 00 	mov    rdi,QWORD PTR [rbx+0x350]
  847301:	31 ed                	xor    ebp,ebp
  847303:	48 85 ff             	test   rdi,rdi
  847306:	74 1f                	je     847327 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa7>
  847308:	be 1e 00 00 00       	mov    esi,0x1e
  84730d:	e8 8e ef fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  847312:	84 c0                	test   al,al
  847314:	75 0a                	jne    847320 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa0>
  847316:	31 f6                	xor    esi,esi
  847318:	48 89 df             	mov    rdi,rbx
  84731b:	e8 00 d6 fd ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  847320:	48 8b ab 50 03 00 00 	mov    rbp,QWORD PTR [rbx+0x350]
  847327:	4c 8b a3 40 03 00 00 	mov    r12,QWORD PTR [rbx+0x340]
  84732e:	4d 85 e4             	test   r12,r12
  847331:	74 0a                	je     84733d <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xbd>
  847333:	41 f6 c6 40          	test   r14b,0x40
  847337:	0f 84 13 07 00 00    	je     847a50 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7d0>
  84733d:	41 f6 c6 10          	test   r14b,0x10
  847341:	0f 84 99 06 00 00    	je     8479e0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x760>
  847347:	4d 85 ff             	test   r15,r15
  84734a:	74 15                	je     847361 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe1>
  84734c:	be 23 00 00 00       	mov    esi,0x23
  847351:	4c 89 ff             	mov    rdi,r15
  847354:	e8 47 ef fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  847359:	84 c0                	test   al,al
  84735b:	0f 85 0f 07 00 00    	jne    847a70 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7f0>
  847361:	0f 57 c0             	xorps  xmm0,xmm0
  847364:	4d 85 e4             	test   r12,r12
  847367:	41 0f 94 c2          	sete   r10b
  84736b:	48 85 ed             	test   rbp,rbp
  84736e:	f3 0f 11 84 24 98 00 00 00 	movss  DWORD PTR [rsp+0x98],xmm0
  847377:	f3 0f 10 05 f9 13 76 00 	movss  xmm0,DWORD PTR [rip+0x7613f9]        # fa8778 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xd8>
  84737f:	f3 0f 11 44 24 78    	movss  DWORD PTR [rsp+0x78],xmm0
  847385:	0f 85 1e 07 00 00    	jne    847aa9 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x829>
  84738b:	45 84 d2             	test   r10b,r10b
  84738e:	0f 84 15 07 00 00    	je     847aa9 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x829>
  847394:	48 8b 83 c0 00 00 00 	mov    rax,QWORD PTR [rbx+0xc0]
  84739b:	48 89 df             	mov    rdi,rbx
  84739e:	48 89 84 24 b0 00 00 00 	mov    QWORD PTR [rsp+0xb0],rax
  8473a6:	48 8b 83 c8 00 00 00 	mov    rax,QWORD PTR [rbx+0xc8]
  8473ad:	48 89 84 24 b8 00 00 00 	mov    QWORD PTR [rsp+0xb8],rax
  8473b5:	48 8b 83 d0 00 00 00 	mov    rax,QWORD PTR [rbx+0xd0]
  8473bc:	48 89 84 24 c0 00 00 00 	mov    QWORD PTR [rsp+0xc0],rax
  8473c4:	48 8b 83 d8 00 00 00 	mov    rax,QWORD PTR [rbx+0xd8]
  8473cb:	48 89 84 24 c8 00 00 00 	mov    QWORD PTR [rsp+0xc8],rax
  8473d3:	48 8b 83 e0 00 00 00 	mov    rax,QWORD PTR [rbx+0xe0]
  8473da:	48 89 84 24 d0 00 00 00 	mov    QWORD PTR [rsp+0xd0],rax
  8473e2:	48 8b 83 e8 00 00 00 	mov    rax,QWORD PTR [rbx+0xe8]
  8473e9:	48 89 84 24 d8 00 00 00 	mov    QWORD PTR [rsp+0xd8],rax
  8473f1:	48 8b 83 f0 00 00 00 	mov    rax,QWORD PTR [rbx+0xf0]
  8473f8:	48 89 84 24 e0 00 00 00 	mov    QWORD PTR [rsp+0xe0],rax
  847400:	48 8b 83 f8 00 00 00 	mov    rax,QWORD PTR [rbx+0xf8]
  847407:	48 89 84 24 e8 00 00 00 	mov    QWORD PTR [rsp+0xe8],rax
  84740f:	8b 83 84 00 00 00    	mov    eax,DWORD PTR [rbx+0x84]
  847415:	89 84 24 bc 00 00 00 	mov    DWORD PTR [rsp+0xbc],eax
  84741c:	8b 83 88 00 00 00    	mov    eax,DWORD PTR [rbx+0x88]
  847422:	89 84 24 cc 00 00 00 	mov    DWORD PTR [rsp+0xcc],eax
  847429:	8b 83 8c 00 00 00    	mov    eax,DWORD PTR [rbx+0x8c]
  84742f:	89 84 24 dc 00 00 00 	mov    DWORD PTR [rsp+0xdc],eax
  847436:	48 8b 44 24 70       	mov    rax,QWORD PTR [rsp+0x70]
  84743b:	f3 0f 10 9b e0 04 00 00 	movss  xmm3,DWORD PTR [rbx+0x4e0]
  847443:	f3 0f 10 93 98 00 00 00 	movss  xmm2,DWORD PTR [rbx+0x98]
  84744b:	f3 0f 10 40 6c       	movss  xmm0,DWORD PTR [rax+0x6c]
  847450:	f3 0f 10 8b dc 04 00 00 	movss  xmm1,DWORD PTR [rbx+0x4dc]
  847458:	44 88 54 24 68       	mov    BYTE PTR [rsp+0x68],r10b
  84745d:	f3 0f 11 44 24 50    	movss  DWORD PTR [rsp+0x50],xmm0
  847463:	f3 0f 11 4c 24 20    	movss  DWORD PTR [rsp+0x20],xmm1
  847469:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  84746f:	f3 0f 11 5c 24 30    	movss  DWORD PTR [rsp+0x30],xmm3
  847475:	e8 46 8d fc ff       	call   8101c0 <CCharacter::getTargetAlignment()>
  84747a:	89 c2                	mov    edx,eax
  84747c:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  847480:	31 ff                	xor    edi,edi
  847482:	f3 0f 10 44 24 50    	movss  xmm0,DWORD PTR [rsp+0x50]
  847488:	44 0f b6 54 24 68    	movzx  r10d,BYTE PTR [rsp+0x68]
  84748e:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  847494:	48 85 c0             	test   rax,rax
  847497:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  84749d:	f3 0f 10 5c 24 30    	movss  xmm3,DWORD PTR [rsp+0x30]
  8474a3:	74 04                	je     8474a9 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x229>
  8474a5:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  8474a9:	f3 0f 59 d3          	mulss  xmm2,xmm3
  8474ad:	f3 0f 58 84 24 98 00 00 00 	addss  xmm0,DWORD PTR [rsp+0x98]
  8474b6:	48 8d 84 24 b0 00 00 00 	lea    rax,[rsp+0xb0]
  8474be:	f3 0f 10 25 22 12 76 00 	movss  xmm4,DWORD PTR [rip+0x761222]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  8474c6:	45 31 c9             	xor    r9d,r9d
  8474c9:	f3 0f 10 1d 2b d3 75 00 	movss  xmm3,DWORD PTR [rip+0x75d32b]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8474d1:	45 31 c0             	xor    r8d,r8d
  8474d4:	b9 01 00 00 00       	mov    ecx,0x1
  8474d9:	48 89 c6             	mov    rsi,rax
  8474dc:	f3 0f 11 5c 24 30    	movss  DWORD PTR [rsp+0x30],xmm3
  8474e2:	f3 0f 58 d4          	addss  xmm2,xmm4
  8474e6:	f3 0f 11 64 24 50    	movss  DWORD PTR [rsp+0x50],xmm4
  8474ec:	44 88 54 24 68       	mov    BYTE PTR [rsp+0x68],r10b
  8474f1:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  8474f9:	f3 0f 58 d0          	addss  xmm2,xmm0
  8474fd:	0f 57 c0             	xorps  xmm0,xmm0
  847500:	f3 0f 59 d1          	mulss  xmm2,xmm1
  847504:	f3 0f 10 4c 24 78    	movss  xmm1,DWORD PTR [rsp+0x78]
  84750a:	f3 0f 58 d3          	addss  xmm2,xmm3
  84750e:	e8 ed ae 10 00       	call   952400 <CLevel::findCharacterWithinView(Ogre::Matrix4 const&, EAlignment, float, float, float, bool, CCharacter*, CSkill*)>
  847513:	48 85 c0             	test   rax,rax
  847516:	f3 0f 10 5c 24 30    	movss  xmm3,DWORD PTR [rsp+0x30]
  84751c:	f3 0f 10 64 24 50    	movss  xmm4,DWORD PTR [rsp+0x50]
  847522:	44 0f b6 54 24 68    	movzx  r10d,BYTE PTR [rsp+0x68]
  847528:	0f 84 ba 10 00 00    	je     8485e8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1368>
  84752e:	49 89 c4             	mov    r12,rax
  847531:	41 f6 c6 04          	test   r14b,0x4
  847535:	0f 85 cd 09 00 00    	jne    847f08 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc88>
  84753b:	4d 85 ff             	test   r15,r15
  84753e:	0f 84 ac 05 00 00    	je     847af0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x870>
  847544:	be 23 00 00 00       	mov    esi,0x23
  847549:	4c 89 ff             	mov    rdi,r15
  84754c:	e8 4f ed fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  847551:	84 c0                	test   al,al
  847553:	0f 84 97 05 00 00    	je     847af0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x870>
  847559:	be 24 00 00 00       	mov    esi,0x24
  84755e:	4c 89 ff             	mov    rdi,r15
  847561:	e8 3a ed fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  847566:	84 c0                	test   al,al
  847568:	0f 84 f2 0f 00 00    	je     848560 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x12e0>
  84756e:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  847575:	48 85 ff             	test   rdi,rdi
  847578:	0f 84 0b 0b 00 00    	je     848089 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe09>
  84757e:	be 01 00 00 00       	mov    esi,0x1
  847583:	e8 98 2a 20 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  847588:	c6 84 24 90 00 00 00 01 	mov    BYTE PTR [rsp+0x90],0x1
  847590:	49 8b 07             	mov    rax,QWORD PTR [r15]
  847593:	4c 89 ff             	mov    rdi,r15
  847596:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  84759c:	48 8b 78 60          	mov    rdi,QWORD PTR [rax+0x60]
  8475a0:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  8475a3:	ff 90 98 00 00 00    	call   QWORD PTR [rax+0x98]
  8475a9:	48 8b 10             	mov    rdx,QWORD PTR [rax]
  8475ac:	48 89 c7             	mov    rdi,rax
  8475af:	ff 92 00 02 00 00    	call   QWORD PTR [rdx+0x200]
  8475b5:	48 8b 10             	mov    rdx,QWORD PTR [rax]
  8475b8:	48 89 94 24 00 02 00 00 	mov    QWORD PTR [rsp+0x200],rdx
  8475c0:	8b 40 08             	mov    eax,DWORD PTR [rax+0x8]
  8475c3:	89 84 24 08 02 00 00 	mov    DWORD PTR [rsp+0x208],eax
  8475ca:	44 89 f0             	mov    eax,r14d
  8475cd:	83 e0 20             	and    eax,0x20
  8475d0:	89 84 24 9c 00 00 00 	mov    DWORD PTR [rsp+0x9c],eax
  8475d7:	0f 85 83 0d 00 00    	jne    848360 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x10e0>
  8475dd:	48 8b 84 24 00 02 00 00 	mov    rax,QWORD PTR [rsp+0x200]
  8475e5:	48 85 ed             	test   rbp,rbp
  8475e8:	48 89 84 24 b0 00 00 00 	mov    QWORD PTR [rsp+0xb0],rax
  8475f0:	8b 84 24 08 02 00 00 	mov    eax,DWORD PTR [rsp+0x208]
  8475f7:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  8475fe:	0f 84 1c 0c 00 00    	je     848220 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfa0>
  847604:	be 01 00 00 00       	mov    esi,0x1
  847609:	48 89 ef             	mov    rdi,rbp
  84760c:	e8 6f fa 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  847611:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  847617:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  84761c:	be 01 00 00 00       	mov    esi,0x1
  847621:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  84762a:	48 89 ef             	mov    rdi,rbp
  84762d:	f3 0f 10 84 24 04 02 00 00 	movss  xmm0,DWORD PTR [rsp+0x204]
  847636:	48 89 84 24 e0 01 00 00 	mov    QWORD PTR [rsp+0x1e0],rax
  84763e:	f3 0f 11 44 24 78    	movss  DWORD PTR [rsp+0x78],xmm0
  847644:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  84764c:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  847653:	89 84 24 e8 01 00 00 	mov    DWORD PTR [rsp+0x1e8],eax
  84765a:	8b 84 24 e0 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e0]
  847661:	89 84 24 b0 00 00 00 	mov    DWORD PTR [rsp+0xb0],eax
  847668:	8b 84 24 e4 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e4]
  84766f:	89 84 24 b4 00 00 00 	mov    DWORD PTR [rsp+0xb4],eax
  847676:	8b 84 24 e8 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e8]
  84767d:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  847684:	e8 f7 f9 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  847689:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  84768f:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  847694:	be 01 00 00 00       	mov    esi,0x1
  847699:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  8476a2:	48 89 df             	mov    rdi,rbx
  8476a5:	48 89 84 24 d0 01 00 00 	mov    QWORD PTR [rsp+0x1d0],rax
  8476ad:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  8476b5:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  8476bc:	f3 0f 10 94 24 d4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1d4]
  8476c5:	89 84 24 d8 01 00 00 	mov    DWORD PTR [rsp+0x1d8],eax
  8476cc:	f3 0f 5c 95 94 01 00 00 	subss  xmm2,DWORD PTR [rbp+0x194]
  8476d4:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  8476da:	e8 a1 f9 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8476df:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  8476e5:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  8476ea:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  8476f3:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  8476f9:	48 89 84 24 c0 01 00 00 	mov    QWORD PTR [rsp+0x1c0],rax
  847701:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  847709:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  847710:	f3 0f 10 84 24 c4 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x1c4]
  847719:	89 84 24 c8 01 00 00 	mov    DWORD PTR [rsp+0x1c8],eax
  847720:	f3 0f 5c 83 94 01 00 00 	subss  xmm0,DWORD PTR [rbx+0x194]
  847728:	f3 0f 5c d0          	subss  xmm2,xmm0
  84772c:	f3 0f 58 54 24 78    	addss  xmm2,DWORD PTR [rsp+0x78]
  847732:	f3 0f 10 84 24 04 02 00 00 	movss  xmm0,DWORD PTR [rsp+0x204]
  84773b:	31 ff                	xor    edi,edi
  84773d:	f3 0f 10 a4 24 b0 00 00 00 	movss  xmm4,DWORD PTR [rsp+0xb0]
  847746:	f3 0f 5c d0          	subss  xmm2,xmm0
  84774a:	0f 28 cc             	movaps xmm1,xmm4
  84774d:	0f 28 e8             	movaps xmm5,xmm0
  847750:	f3 0f 10 9c 24 b8 00 00 00 	movss  xmm3,DWORD PTR [rsp+0xb8]
  847759:	f3 0f 59 cc          	mulss  xmm1,xmm4
  84775d:	f3 0f 59 e8          	mulss  xmm5,xmm0
  847761:	f3 0f 58 cd          	addss  xmm1,xmm5
  847765:	0f 28 eb             	movaps xmm5,xmm3
  847768:	f3 0f 59 eb          	mulss  xmm5,xmm3
  84776c:	f3 0f 58 cd          	addss  xmm1,xmm5
  847770:	f3 0f 10 2d 08 10 76 00 	movss  xmm5,DWORD PTR [rip+0x761008]        # fa8780 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xe0>
  847778:	f3 0f 51 c9          	sqrtss xmm1,xmm1
  84777c:	f3 0f 5e 0d 4c 0f 76 00 	divss  xmm1,DWORD PTR [rip+0x760f4c]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  847784:	f3 0f 5d d1          	minss  xmm2,xmm1
  847788:	0f 57 cd             	xorps  xmm1,xmm5
  84778b:	f3 0f 5f d1          	maxss  xmm2,xmm1
  84778f:	0f 57 c9             	xorps  xmm1,xmm1
  847792:	f3 0f 58 d9          	addss  xmm3,xmm1
  847796:	f3 0f 58 d0          	addss  xmm2,xmm0
  84779a:	f3 0f 58 e1          	addss  xmm4,xmm1
  84779e:	f3 0f 11 9c 24 78 01 00 00 	movss  DWORD PTR [rsp+0x178],xmm3
  8477a7:	f3 0f 10 1d bd ef 77 00 	movss  xmm3,DWORD PTR [rip+0x77efbd]        # fc676c <typeinfo name for iCollision+0x1c>
  8477af:	f3 0f 11 94 24 b4 00 00 00 	movss  DWORD PTR [rsp+0xb4],xmm2
  8477b8:	f3 0f 58 d3          	addss  xmm2,xmm3
  8477bc:	f3 0f 58 c3          	addss  xmm0,xmm3
  8477c0:	f3 0f 10 9c 24 08 02 00 00 	movss  xmm3,DWORD PTR [rsp+0x208]
  8477c9:	f3 0f 58 d9          	addss  xmm3,xmm1
  8477cd:	f3 0f 11 a4 24 70 01 00 00 	movss  DWORD PTR [rsp+0x170],xmm4
  8477d6:	f3 0f 11 94 24 74 01 00 00 	movss  DWORD PTR [rsp+0x174],xmm2
  8477df:	f3 0f 10 94 24 00 02 00 00 	movss  xmm2,DWORD PTR [rsp+0x200]
  8477e8:	f3 0f 58 d1          	addss  xmm2,xmm1
  8477ec:	f3 0f 11 9c 24 88 01 00 00 	movss  DWORD PTR [rsp+0x188],xmm3
  8477f5:	f3 0f 11 84 24 84 01 00 00 	movss  DWORD PTR [rsp+0x184],xmm0
  8477fe:	f3 0f 11 94 24 80 01 00 00 	movss  DWORD PTR [rsp+0x180],xmm2
  847807:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  84780b:	48 85 c0             	test   rax,rax
  84780e:	74 04                	je     847814 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x594>
  847810:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  847814:	48 8d 84 24 50 01 00 00 	lea    rax,[rsp+0x150]
  84781c:	48 8d 8c 24 10 01 00 00 	lea    rcx,[rsp+0x110]
  847824:	48 8d 94 24 70 01 00 00 	lea    rdx,[rsp+0x170]
  84782c:	48 8d b4 24 80 01 00 00 	lea    rsi,[rsp+0x180]
  847834:	4c 8d 8c 24 58 02 00 00 	lea    r9,[rsp+0x258]
  84783c:	4c 8d 84 24 20 01 00 00 	lea    r8,[rsp+0x120]
  847844:	f3 0f 11 4c 24 20    	movss  DWORD PTR [rsp+0x20],xmm1
  84784a:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  847852:	48 89 04 24          	mov    QWORD PTR [rsp],rax
  847856:	e8 f5 69 10 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  84785b:	84 c0                	test   al,al
  84785d:	c6 44 24 78 00       	mov    BYTE PTR [rsp+0x78],0x0
  847862:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  847868:	74 2f                	je     847899 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x619>
  84786a:	8b 84 24 10 01 00 00 	mov    eax,DWORD PTR [rsp+0x110]
  847871:	c6 44 24 78 01       	mov    BYTE PTR [rsp+0x78],0x1
  847876:	89 84 24 b0 00 00 00 	mov    DWORD PTR [rsp+0xb0],eax
  84787d:	8b 84 24 18 01 00 00 	mov    eax,DWORD PTR [rsp+0x118]
  847884:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  84788b:	8b 84 24 04 02 00 00 	mov    eax,DWORD PTR [rsp+0x204]
  847892:	89 84 24 b4 00 00 00 	mov    DWORD PTR [rsp+0xb4],eax
  847899:	80 bc 24 90 00 00 00 00 	cmp    BYTE PTR [rsp+0x90],0x0
  8478a1:	0f 85 31 0b 00 00    	jne    8483d8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1158>
  8478a7:	41 f6 c6 01          	test   r14b,0x1
  8478ab:	0f 84 66 06 00 00    	je     847f17 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc97>
  8478b1:	41 f6 c6 02          	test   r14b,0x2
  8478b5:	0f 84 c5 06 00 00    	je     847f80 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd00>
  8478bb:	48 85 ed             	test   rbp,rbp
  8478be:	0f 84 eb 06 00 00    	je     847faf <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd2f>
  8478c4:	80 bd f0 01 00 00 00 	cmp    BYTE PTR [rbp+0x1f0],0x0
  8478cb:	0f 84 cf 06 00 00    	je     847fa0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd20>
  8478d1:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  8478d5:	48 89 de             	mov    rsi,rbx
  8478d8:	48 89 ef             	mov    rdi,rbp
  8478db:	ff 90 80 02 00 00    	call   QWORD PTR [rax+0x280]
  8478e1:	ba 01 00 00 00       	mov    edx,0x1
  8478e6:	be 0b 00 00 00       	mov    esi,0xb
  8478eb:	48 89 df             	mov    rdi,rbx
  8478ee:	e8 ed a0 fc ff       	call   8119e0 <CCharacter::incrementJournalStatistic(EJournalStatistic, int)>
  8478f3:	be 01 00 00 00       	mov    esi,0x1
  8478f8:	48 89 ef             	mov    rdi,rbp
  8478fb:	e8 80 f7 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  847900:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  847906:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  84790b:	be 01 00 00 00       	mov    esi,0x1
  847910:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  847919:	48 89 df             	mov    rdi,rbx
  84791c:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  847924:	48 89 84 24 f0 00 00 00 	mov    QWORD PTR [rsp+0xf0],rax
  84792c:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  847933:	89 84 24 f8 00 00 00 	mov    DWORD PTR [rsp+0xf8],eax
  84793a:	e8 41 f7 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  84793f:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  847945:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  84794a:	48 8d 94 24 f0 00 00 00 	lea    rdx,[rsp+0xf0]
  847952:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  84795b:	48 8d b4 24 00 01 00 00 	lea    rsi,[rsp+0x100]
  847963:	45 31 c0             	xor    r8d,r8d
  847966:	31 c9                	xor    ecx,ecx
  847968:	f3 0f 10 05 c8 ce 75 00 	movss  xmm0,DWORD PTR [rip+0x75cec8]        # fa4838 <vtable for Ogre::FrameListener+0x78>
  847970:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  847978:	48 89 df             	mov    rdi,rbx
  84797b:	48 89 84 24 00 01 00 00 	mov    QWORD PTR [rsp+0x100],rax
  847983:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  84798a:	89 84 24 08 01 00 00 	mov    DWORD PTR [rsp+0x108],eax
  847991:	e8 8a fd fd ff       	call   827720 <CCharacter::playStrikeParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float, bool, bool)>
  847996:	80 7c 24 78 00       	cmp    BYTE PTR [rsp+0x78],0x0
  84799b:	0f 84 df 07 00 00    	je     848180 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf00>
  8479a1:	48 8b bb 98 02 00 00 	mov    rdi,QWORD PTR [rbx+0x298]
  8479a8:	48 85 ff             	test   rdi,rdi
  8479ab:	74 1b                	je     8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  8479ad:	0f 57 c9             	xorps  xmm1,xmm1
  8479b0:	48 8b 53 58          	mov    rdx,QWORD PTR [rbx+0x58]
  8479b4:	31 c9                	xor    ecx,ecx
  8479b6:	be 0f 00 00 00       	mov    esi,0xf
  8479bb:	0f 28 c1             	movaps xmm0,xmm1
  8479be:	e8 dd 1e 22 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  8479c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8479c8:	48 81 c4 68 02 00 00 	add    rsp,0x268
  8479cf:	5b                   	pop    rbx
  8479d0:	5d                   	pop    rbp
  8479d1:	41 5c                	pop    r12
  8479d3:	41 5d                	pop    r13
  8479d5:	41 5e                	pop    r14
  8479d7:	41 5f                	pop    r15
  8479d9:	c3                   	ret
  8479da:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  8479e0:	4d 85 e4             	test   r12,r12
  8479e3:	48 89 ea             	mov    rdx,rbp
  8479e6:	be 4a 00 00 00       	mov    esi,0x4a
  8479eb:	49 0f 45 d4          	cmovne rdx,r12
  8479ef:	48 89 df             	mov    rdi,rbx
  8479f2:	e8 39 8d fc ff       	call   810730 <CCharacter::executeProcs(EEFFECT_TYPE, CBaseUnit*)>
  8479f7:	4d 85 ff             	test   r15,r15
  8479fa:	0f 84 61 f9 ff ff    	je     847361 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe1>
  847a00:	4c 89 fe             	mov    rsi,r15
  847a03:	48 89 df             	mov    rdi,rbx
  847a06:	e8 b5 cb fd ff       	call   8245c0 <CCharacter::doWeaponSkill(CEquipment*)>
  847a0b:	84 c0                	test   al,al
  847a0d:	75 b9                	jne    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847a0f:	4c 89 e2             	mov    rdx,r12
  847a12:	48 89 de             	mov    rsi,rbx
  847a15:	4c 89 ff             	mov    rdi,r15
  847a18:	e8 03 77 03 00       	call   87f120 <CEquipment::fireMissiles(CCharacter*, CCharacter*)>
  847a1d:	84 c0                	test   al,al
  847a1f:	0f 84 22 f9 ff ff    	je     847347 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc7>
  847a25:	eb a1                	jmp    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847a27:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  847a30:	49 8b 85 a8 02 00 00 	mov    rax,QWORD PTR [r13+0x2a8]
  847a37:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  847a3c:	48 83 7c 24 70 00    	cmp    QWORD PTR [rsp+0x70],0x0
  847a42:	0f 85 af f8 ff ff    	jne    8472f7 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x77>
  847a48:	4d 89 ef             	mov    r15,r13
  847a4b:	e9 ef 04 00 00       	jmp    847f3f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xcbf>
  847a50:	4c 89 e6             	mov    rsi,r12
  847a53:	48 89 df             	mov    rdi,rbx
  847a56:	e8 a5 87 fc ff       	call   810200 <CCharacter::isEnemy(CCharacter*)>
  847a5b:	84 c0                	test   al,al
  847a5d:	0f 84 65 ff ff ff    	je     8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847a63:	31 ed                	xor    ebp,ebp
  847a65:	e9 d3 f8 ff ff       	jmp    84733d <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xbd>
  847a6a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  847a70:	ba 07 00 00 00       	mov    edx,0x7
  847a75:	be 4e 00 00 00       	mov    esi,0x4e
  847a7a:	48 89 df             	mov    rdi,rbx
  847a7d:	e8 5e bd fc ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  847a82:	4d 85 e4             	test   r12,r12
  847a85:	f3 0f 11 84 24 98 00 00 00 	movss  DWORD PTR [rsp+0x98],xmm0
  847a8e:	41 0f 94 c2          	sete   r10b
  847a92:	f3 0f 10 05 46 0c 76 00 	movss  xmm0,DWORD PTR [rip+0x760c46]        # fa86e0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x40>
  847a9a:	48 85 ed             	test   rbp,rbp
  847a9d:	f3 0f 11 44 24 78    	movss  DWORD PTR [rsp+0x78],xmm0
  847aa3:	0f 84 e2 f8 ff ff    	je     84738b <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x10b>
  847aa9:	4c 89 f9             	mov    rcx,r15
  847aac:	48 89 ea             	mov    rdx,rbp
  847aaf:	4c 89 e6             	mov    rsi,r12
  847ab2:	48 89 df             	mov    rdi,rbx
  847ab5:	44 88 54 24 68       	mov    BYTE PTR [rsp+0x68],r10b
  847aba:	e8 91 cf fd ff       	call   824a50 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)>
  847abf:	84 c0                	test   al,al
  847ac1:	44 0f b6 54 24 68    	movzx  r10d,BYTE PTR [rsp+0x68]
  847ac7:	0f 85 64 fa ff ff    	jne    847531 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2b1>
  847acd:	e9 c2 f8 ff ff       	jmp    847394 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x114>
  847ad2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  847ad8:	49 8b 85 a0 02 00 00 	mov    rax,QWORD PTR [r13+0x2a0]
  847adf:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  847ae4:	e9 53 ff ff ff       	jmp    847a3c <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7bc>
  847ae9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  847af0:	be 01 00 00 00       	mov    esi,0x1
  847af5:	48 89 df             	mov    rdi,rbx
  847af8:	e8 83 f5 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  847afd:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  847b03:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  847b08:	48 85 ed             	test   rbp,rbp
  847b0b:	f3 0f 10 05 bd 0b 76 00 	movss  xmm0,DWORD PTR [rip+0x760bbd]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  847b13:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  847b1c:	8b 94 24 a8 00 00 00 	mov    edx,DWORD PTR [rsp+0xa8]
  847b23:	48 89 84 24 60 01 00 00 	mov    QWORD PTR [rsp+0x160],rax
  847b2b:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  847b33:	f3 0f 58 84 24 64 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x164]
  847b3c:	89 94 24 68 01 00 00 	mov    DWORD PTR [rsp+0x168],edx
  847b43:	48 89 84 24 50 01 00 00 	mov    QWORD PTR [rsp+0x150],rax
  847b4b:	89 94 24 58 01 00 00 	mov    DWORD PTR [rsp+0x158],edx
  847b52:	f3 0f 11 84 24 64 01 00 00 	movss  DWORD PTR [rsp+0x164],xmm0
  847b5b:	0f 84 47 06 00 00    	je     8481a8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf28>
  847b61:	be 01 00 00 00       	mov    esi,0x1
  847b66:	48 89 ef             	mov    rdi,rbp
  847b69:	e8 12 f5 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  847b6e:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  847b74:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  847b79:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  847b82:	f3 0f 10 84 24 64 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x164]
  847b8b:	48 89 84 24 40 01 00 00 	mov    QWORD PTR [rsp+0x140],rax
  847b93:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  847b9b:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  847ba2:	89 84 24 48 01 00 00 	mov    DWORD PTR [rsp+0x148],eax
  847ba9:	8b 84 24 40 01 00 00 	mov    eax,DWORD PTR [rsp+0x140]
  847bb0:	89 84 24 50 01 00 00 	mov    DWORD PTR [rsp+0x150],eax
  847bb7:	8b 84 24 48 01 00 00 	mov    eax,DWORD PTR [rsp+0x148]
  847bbe:	89 84 24 58 01 00 00 	mov    DWORD PTR [rsp+0x158],eax
  847bc5:	f3 0f 11 84 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm0
  847bce:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  847bd2:	31 ff                	xor    edi,edi
  847bd4:	48 85 c0             	test   rax,rax
  847bd7:	74 04                	je     847bdd <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x95d>
  847bd9:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  847bdd:	48 8d 84 24 b0 00 00 00 	lea    rax,[rsp+0xb0]
  847be5:	4c 8d 8c 24 58 02 00 00 	lea    r9,[rsp+0x258]
  847bed:	4c 8d 84 24 10 01 00 00 	lea    r8,[rsp+0x110]
  847bf5:	48 8d 8c 24 20 01 00 00 	lea    rcx,[rsp+0x120]
  847bfd:	48 8d 94 24 50 01 00 00 	lea    rdx,[rsp+0x150]
  847c05:	48 8d b4 24 60 01 00 00 	lea    rsi,[rsp+0x160]
  847c0d:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  847c15:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  847c1d:	48 89 04 24          	mov    QWORD PTR [rsp],rax
  847c21:	e8 2a 66 10 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  847c26:	84 c0                	test   al,al
  847c28:	0f 84 da 02 00 00    	je     847f08 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc88>
  847c2e:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  847c31:	48 89 df             	mov    rdi,rbx
  847c34:	ff 90 30 01 00 00    	call   QWORD PTR [rax+0x130]
  847c3a:	f3 0f 10 0d 8a 68 78 00 	movss  xmm1,DWORD PTR [rip+0x78688a]        # fce4cc <vtable for iInventoryListener+0x8c>
  847c42:	48 89 df             	mov    rdi,rbx
  847c45:	f3 0f 10 20          	movss  xmm4,DWORD PTR [rax]
  847c49:	f3 0f 59 e1          	mulss  xmm4,xmm1
  847c4d:	f3 0f 10 84 24 60 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x160]
  847c56:	f3 0f 10 58 04       	movss  xmm3,DWORD PTR [rax+0x4]
  847c5b:	f3 0f 59 d9          	mulss  xmm3,xmm1
  847c5f:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  847c64:	f3 0f 59 d1          	mulss  xmm2,xmm1
  847c68:	f3 0f 5c c4          	subss  xmm0,xmm4
  847c6c:	f3 0f 11 84 24 60 01 00 00 	movss  DWORD PTR [rsp+0x160],xmm0
  847c75:	f3 0f 10 84 24 64 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x164]
  847c7e:	f3 0f 5c c3          	subss  xmm0,xmm3
  847c82:	f3 0f 11 84 24 64 01 00 00 	movss  DWORD PTR [rsp+0x164],xmm0
  847c8b:	f3 0f 10 84 24 68 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x168]
  847c94:	f3 0f 5c c2          	subss  xmm0,xmm2
  847c98:	f3 0f 11 84 24 68 01 00 00 	movss  DWORD PTR [rsp+0x168],xmm0
  847ca1:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  847ca4:	f3 0f 11 4c 24 20    	movss  DWORD PTR [rsp+0x20],xmm1
  847caa:	ff 90 58 01 00 00    	call   QWORD PTR [rax+0x158]
  847cb0:	f3 0f 10 05 bc ea 77 00 	movss  xmm0,DWORD PTR [rip+0x77eabc]        # fc6774 <typeinfo name for iCollision+0x24>
  847cb8:	48 89 df             	mov    rdi,rbx
  847cbb:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  847cc0:	f3 0f 10 58 04       	movss  xmm3,DWORD PTR [rax+0x4]
  847cc5:	f3 0f 59 d0          	mulss  xmm2,xmm0
  847cc9:	f3 0f 10 20          	movss  xmm4,DWORD PTR [rax]
  847ccd:	f3 0f 59 d8          	mulss  xmm3,xmm0
  847cd1:	f3 0f 59 e0          	mulss  xmm4,xmm0
  847cd5:	f3 0f 58 94 24 68 01 00 00 	addss  xmm2,DWORD PTR [rsp+0x168]
  847cde:	f3 0f 58 9c 24 64 01 00 00 	addss  xmm3,DWORD PTR [rsp+0x164]
  847ce7:	f3 0f 58 a4 24 60 01 00 00 	addss  xmm4,DWORD PTR [rsp+0x160]
  847cf0:	f3 0f 11 94 24 68 01 00 00 	movss  DWORD PTR [rsp+0x168],xmm2
  847cf9:	f3 0f 11 9c 24 64 01 00 00 	movss  DWORD PTR [rsp+0x164],xmm3
  847d02:	f3 0f 11 a4 24 60 01 00 00 	movss  DWORD PTR [rsp+0x160],xmm4
  847d0b:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  847d0e:	f3 0f 11 44 24 50    	movss  DWORD PTR [rsp+0x50],xmm0
  847d14:	ff 90 58 01 00 00    	call   QWORD PTR [rax+0x158]
  847d1a:	f3 0f 10 44 24 50    	movss  xmm0,DWORD PTR [rsp+0x50]
  847d20:	31 ff                	xor    edi,edi
  847d22:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  847d27:	f3 0f 10 58 04       	movss  xmm3,DWORD PTR [rax+0x4]
  847d2c:	f3 0f 59 d0          	mulss  xmm2,xmm0
  847d30:	f3 0f 59 d8          	mulss  xmm3,xmm0
  847d34:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  847d3a:	f3 0f 59 00          	mulss  xmm0,DWORD PTR [rax]
  847d3e:	f3 0f 58 94 24 58 01 00 00 	addss  xmm2,DWORD PTR [rsp+0x158]
  847d47:	f3 0f 58 9c 24 54 01 00 00 	addss  xmm3,DWORD PTR [rsp+0x154]
  847d50:	f3 0f 58 84 24 50 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x150]
  847d59:	f3 0f 11 94 24 58 01 00 00 	movss  DWORD PTR [rsp+0x158],xmm2
  847d62:	f3 0f 11 9c 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm3
  847d6b:	f3 0f 11 84 24 50 01 00 00 	movss  DWORD PTR [rsp+0x150],xmm0
  847d74:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  847d78:	48 85 c0             	test   rax,rax
  847d7b:	74 04                	je     847d81 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb01>
  847d7d:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  847d81:	48 8b 84 24 90 00 00 00 	mov    rax,QWORD PTR [rsp+0x90]
  847d89:	4c 8d 8c 24 58 02 00 00 	lea    r9,[rsp+0x258]
  847d91:	4c 8d 84 24 10 01 00 00 	lea    r8,[rsp+0x110]
  847d99:	48 8d 8c 24 20 01 00 00 	lea    rcx,[rsp+0x120]
  847da1:	48 8d 94 24 50 01 00 00 	lea    rdx,[rsp+0x150]
  847da9:	48 8d b4 24 60 01 00 00 	lea    rsi,[rsp+0x160]
  847db1:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  847db9:	f3 0f 11 4c 24 20    	movss  DWORD PTR [rsp+0x20],xmm1
  847dbf:	48 89 04 24          	mov    QWORD PTR [rsp],rax
  847dc3:	e8 88 64 10 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  847dc8:	84 c0                	test   al,al
  847dca:	0f 84 38 01 00 00    	je     847f08 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc88>
  847dd0:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  847dd3:	48 89 df             	mov    rdi,rbx
  847dd6:	ff 90 58 01 00 00    	call   QWORD PTR [rax+0x158]
  847ddc:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  847de2:	48 89 df             	mov    rdi,rbx
  847de5:	f3 0f 10 20          	movss  xmm4,DWORD PTR [rax]
  847de9:	f3 0f 59 e1          	mulss  xmm4,xmm1
  847ded:	f3 0f 10 84 24 60 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x160]
  847df6:	f3 0f 10 58 04       	movss  xmm3,DWORD PTR [rax+0x4]
  847dfb:	f3 0f 59 d9          	mulss  xmm3,xmm1
  847dff:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  847e04:	f3 0f 59 d1          	mulss  xmm2,xmm1
  847e08:	f3 0f 5c c4          	subss  xmm0,xmm4
  847e0c:	f3 0f 11 84 24 60 01 00 00 	movss  DWORD PTR [rsp+0x160],xmm0
  847e15:	f3 0f 10 84 24 64 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x164]
  847e1e:	f3 0f 5c c3          	subss  xmm0,xmm3
  847e22:	f3 0f 11 84 24 64 01 00 00 	movss  DWORD PTR [rsp+0x164],xmm0
  847e2b:	f3 0f 10 84 24 68 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x168]
  847e34:	f3 0f 5c c2          	subss  xmm0,xmm2
  847e38:	f3 0f 11 84 24 68 01 00 00 	movss  DWORD PTR [rsp+0x168],xmm0
  847e41:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  847e44:	ff 90 58 01 00 00    	call   QWORD PTR [rax+0x158]
  847e4a:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  847e50:	31 ff                	xor    edi,edi
  847e52:	f3 0f 10 50 08       	movss  xmm2,DWORD PTR [rax+0x8]
  847e57:	f3 0f 10 58 04       	movss  xmm3,DWORD PTR [rax+0x4]
  847e5c:	f3 0f 59 d1          	mulss  xmm2,xmm1
  847e60:	f3 0f 59 d9          	mulss  xmm3,xmm1
  847e64:	f3 0f 10 84 24 50 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x150]
  847e6d:	f3 0f 59 08          	mulss  xmm1,DWORD PTR [rax]
  847e71:	f3 0f 5c c1          	subss  xmm0,xmm1
  847e75:	f3 0f 11 84 24 50 01 00 00 	movss  DWORD PTR [rsp+0x150],xmm0
  847e7e:	f3 0f 10 84 24 54 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x154]
  847e87:	f3 0f 5c c3          	subss  xmm0,xmm3
  847e8b:	f3 0f 11 84 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm0
  847e94:	f3 0f 10 84 24 58 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x158]
  847e9d:	f3 0f 5c c2          	subss  xmm0,xmm2
  847ea1:	f3 0f 11 84 24 58 01 00 00 	movss  DWORD PTR [rsp+0x158],xmm0
  847eaa:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  847eae:	48 85 c0             	test   rax,rax
  847eb1:	74 04                	je     847eb7 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc37>
  847eb3:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  847eb7:	48 8b 84 24 90 00 00 00 	mov    rax,QWORD PTR [rsp+0x90]
  847ebf:	4c 8d 8c 24 58 02 00 00 	lea    r9,[rsp+0x258]
  847ec7:	4c 8d 84 24 10 01 00 00 	lea    r8,[rsp+0x110]
  847ecf:	48 8d 8c 24 20 01 00 00 	lea    rcx,[rsp+0x120]
  847ed7:	48 8d 94 24 50 01 00 00 	lea    rdx,[rsp+0x150]
  847edf:	48 8d b4 24 60 01 00 00 	lea    rsi,[rsp+0x160]
  847ee7:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  847eef:	48 89 04 24          	mov    QWORD PTR [rsp],rax
  847ef3:	e8 58 63 10 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  847ef8:	84 c0                	test   al,al
  847efa:	c6 44 24 78 01       	mov    BYTE PTR [rsp+0x78],0x1
  847eff:	0f 85 a2 f9 ff ff    	jne    8478a7 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x627>
  847f05:	0f 1f 00             	nop    DWORD PTR [rax]
  847f08:	41 f6 c6 01          	test   r14b,0x1
  847f0c:	c6 44 24 78 00       	mov    BYTE PTR [rsp+0x78],0x0
  847f11:	0f 85 9a f9 ff ff    	jne    8478b1 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x631>
  847f17:	31 c9                	xor    ecx,ecx
  847f19:	48 89 ea             	mov    rdx,rbp
  847f1c:	4c 89 e6             	mov    rsi,r12
  847f1f:	48 89 df             	mov    rdi,rbx
  847f22:	e8 29 cb fd ff       	call   824a50 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)>
  847f27:	84 c0                	test   al,al
  847f29:	0f 84 99 fa ff ff    	je     8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847f2f:	e9 7d f9 ff ff       	jmp    8478b1 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x631>
  847f34:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  847f38:	4c 8b bf 98 04 00 00 	mov    r15,QWORD PTR [rdi+0x498]
  847f3f:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  847f46:	48 85 c0             	test   rax,rax
  847f49:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  847f4e:	0f 85 a6 f3 ff ff    	jne    8472fa <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7a>
  847f54:	31 f6                	xor    esi,esi
  847f56:	48 89 df             	mov    rdi,rbx
  847f59:	e8 62 9c fc ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  847f5e:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  847f65:	48 85 c0             	test   rax,rax
  847f68:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  847f6d:	0f 85 87 f3 ff ff    	jne    8472fa <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7a>
  847f73:	e9 50 fa ff ff       	jmp    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847f78:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  847f80:	48 89 ea             	mov    rdx,rbp
  847f83:	4c 89 e6             	mov    rsi,r12
  847f86:	48 89 df             	mov    rdi,rbx
  847f89:	e8 52 f5 fd ff       	call   8274e0 <CCharacter::facingTarget(CCharacter*, CItem*)>
  847f8e:	84 c0                	test   al,al
  847f90:	0f 84 32 fa ff ff    	je     8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847f96:	e9 20 f9 ff ff       	jmp    8478bb <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x63b>
  847f9b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  847fa0:	31 f6                	xor    esi,esi
  847fa2:	48 89 df             	mov    rdi,rbx
  847fa5:	e8 76 c9 fd ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  847faa:	e9 19 fa ff ff       	jmp    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  847faf:	4d 85 e4             	test   r12,r12
  847fb2:	0f 84 e9 f9 ff ff    	je     8479a1 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x721>
  847fb8:	80 7c 24 78 00       	cmp    BYTE PTR [rsp+0x78],0x0
  847fbd:	0f 1f 00             	nop    DWORD PTR [rax]
  847fc0:	0f 85 db f9 ff ff    	jne    8479a1 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x721>
  847fc6:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  847fca:	31 f6                	xor    esi,esi
  847fcc:	48 85 c0             	test   rax,rax
  847fcf:	74 04                	je     847fd5 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd55>
  847fd1:	48 8b 70 18          	mov    rsi,QWORD PTR [rax+0x18]
  847fd5:	44 8b 8c 24 8c 00 00 00 	mov    r9d,DWORD PTR [rsp+0x8c]
  847fdd:	f3 0f 10 8c 24 88 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x88]
  847fe6:	f3 0f 10 84 24 84 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x84]
  847fef:	45 89 f0             	mov    r8d,r14d
  847ff2:	4c 89 e9             	mov    rcx,r13
  847ff5:	4c 89 e2             	mov    rdx,r12
  847ff8:	48 89 df             	mov    rdi,rbx
  847ffb:	e8 d0 be ff ff       	call   843ed0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)>
  848000:	84 c0                	test   al,al
  848002:	0f 84 99 f9 ff ff    	je     8479a1 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x721>
  848008:	4c 89 e2             	mov    rdx,r12
  84800b:	be 4b 00 00 00       	mov    esi,0x4b
  848010:	48 89 df             	mov    rdi,rbx
  848013:	4d 89 e5             	mov    r13,r12
  848016:	e8 15 87 fc ff       	call   810730 <CCharacter::executeProcs(EEFFECT_TYPE, CBaseUnit*)>
  84801b:	4c 89 ea             	mov    rdx,r13
  84801e:	be 4c 00 00 00       	mov    esi,0x4c
  848023:	48 89 df             	mov    rdi,rbx
  848026:	e8 05 87 fc ff       	call   810730 <CCharacter::executeProcs(EEFFECT_TYPE, CBaseUnit*)>
  84802b:	4d 85 ff             	test   r15,r15
  84802e:	74 1f                	je     84804f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xdcf>
  848030:	48 85 ed             	test   rbp,rbp
  848033:	0f 84 97 05 00 00    	je     8485d0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1350>
  848039:	4d 85 e4             	test   r12,r12
  84803c:	48 89 ea             	mov    rdx,rbp
  84803f:	74 03                	je     848044 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xdc4>
  848041:	4c 89 e2             	mov    rdx,r12
  848044:	4c 89 fe             	mov    rsi,r15
  848047:	48 89 df             	mov    rdi,rbx
  84804a:	e8 c1 ef fd ff       	call   827010 <CCharacter::doWeaponProcs(CEquipment*, CBaseUnit*)>
  84804f:	48 8b 44 24 70       	mov    rax,QWORD PTR [rsp+0x70]
  848054:	80 78 18 00          	cmp    BYTE PTR [rax+0x18],0x0
  848058:	0f 85 52 05 00 00    	jne    8485b0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1330>
  84805e:	48 8b bb 98 02 00 00 	mov    rdi,QWORD PTR [rbx+0x298]
  848065:	48 85 ff             	test   rdi,rdi
  848068:	0f 84 42 05 00 00    	je     8485b0 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1330>
  84806e:	0f 57 c9             	xorps  xmm1,xmm1
  848071:	48 8b 53 58          	mov    rdx,QWORD PTR [rbx+0x58]
  848075:	31 c9                	xor    ecx,ecx
  848077:	be 01 00 00 00       	mov    esi,0x1
  84807c:	0f 28 c1             	movaps xmm0,xmm1
  84807f:	e8 1c 18 22 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  848084:	e9 3f f9 ff ff       	jmp    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  848089:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  84808d:	48 c7 84 24 90 00 00 00 00 00 00 00 	mov    QWORD PTR [rsp+0x90],0x0
  848099:	48 85 c0             	test   rax,rax
  84809c:	74 0c                	je     8480aa <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe2a>
  84809e:	48 8b 40 10          	mov    rax,QWORD PTR [rax+0x10]
  8480a2:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  8480aa:	48 8d 94 24 5f 02 00 00 	lea    rdx,[rsp+0x25f]
  8480b2:	48 8d bc 24 50 02 00 00 	lea    rdi,[rsp+0x250]
  8480ba:	be 08 99 fc 00       	mov    esi,0xfc9908
  8480bf:	e8 34 e2 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8480c4:	48 8d b4 24 50 02 00 00 	lea    rsi,[rsp+0x250]
  8480cc:	48 8d bc 24 40 02 00 00 	lea    rdi,[rsp+0x240]
  8480d4:	e8 77 69 44 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  8480d9:	bf a0 00 00 00       	mov    edi,0xa0
  8480de:	e8 dd 2b 01 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  8480e3:	48 8b b4 24 90 00 00 00 	mov    rsi,QWORD PTR [rsp+0x90]
  8480eb:	48 8d 94 24 40 02 00 00 	lea    rdx,[rsp+0x240]
  8480f3:	b9 02 00 00 00       	mov    ecx,0x2
  8480f8:	f3 0f 10 05 30 c7 75 00 	movss  xmm0,DWORD PTR [rip+0x75c730]        # fa4830 <vtable for Ogre::FrameListener+0x70>
  848100:	48 89 c7             	mov    rdi,rax
  848103:	48 89 44 24 78       	mov    QWORD PTR [rsp+0x78],rax
  848108:	e8 13 4a 20 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  84810d:	48 8b 44 24 78       	mov    rax,QWORD PTR [rsp+0x78]
  848112:	48 8d bc 24 40 02 00 00 	lea    rdi,[rsp+0x240]
  84811a:	48 89 83 a8 06 00 00 	mov    QWORD PTR [rbx+0x6a8],rax
  848121:	e8 62 e1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848126:	48 8d bc 24 50 02 00 00 	lea    rdi,[rsp+0x250]
  84812e:	e8 55 e1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848133:	48 8d 94 24 5e 02 00 00 	lea    rdx,[rsp+0x25e]
  84813b:	48 8d bc 24 30 02 00 00 	lea    rdi,[rsp+0x230]
  848143:	be 50 05 fa 00       	mov    esi,0xfa0550
  848148:	e8 ab e1 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84814d:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  848154:	48 8d b4 24 30 02 00 00 	lea    rsi,[rsp+0x230]
  84815c:	e8 2f 1f 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  848161:	48 8d bc 24 30 02 00 00 	lea    rdi,[rsp+0x230]
  848169:	e8 1a e1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84816e:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  848175:	e9 04 f4 ff ff       	jmp    84757e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2fe>
  84817a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  848180:	4d 85 e4             	test   r12,r12
  848183:	0f 85 7f fe ff ff    	jne    848008 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd88>
  848189:	48 89 ea             	mov    rdx,rbp
  84818c:	be 4b 00 00 00       	mov    esi,0x4b
  848191:	48 89 df             	mov    rdi,rbx
  848194:	49 89 ed             	mov    r13,rbp
  848197:	e8 94 85 fc ff       	call   810730 <CCharacter::executeProcs(EEFFECT_TYPE, CBaseUnit*)>
  84819c:	e9 7a fe ff ff       	jmp    84801b <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xd9b>
  8481a1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8481a8:	4d 85 e4             	test   r12,r12
  8481ab:	0f 84 14 fa ff ff    	je     847bc5 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x945>
  8481b1:	be 01 00 00 00       	mov    esi,0x1
  8481b6:	4c 89 e7             	mov    rdi,r12
  8481b9:	e8 c2 ee 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8481be:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  8481c4:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  8481c9:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  8481d2:	f3 0f 10 84 24 64 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x164]
  8481db:	48 89 84 24 30 01 00 00 	mov    QWORD PTR [rsp+0x130],rax
  8481e3:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  8481eb:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  8481f2:	89 84 24 38 01 00 00 	mov    DWORD PTR [rsp+0x138],eax
  8481f9:	8b 84 24 30 01 00 00 	mov    eax,DWORD PTR [rsp+0x130]
  848200:	89 84 24 50 01 00 00 	mov    DWORD PTR [rsp+0x150],eax
  848207:	8b 84 24 38 01 00 00 	mov    eax,DWORD PTR [rsp+0x138]
  84820e:	89 84 24 58 01 00 00 	mov    DWORD PTR [rsp+0x158],eax
  848215:	e9 ab f9 ff ff       	jmp    847bc5 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x945>
  84821a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  848220:	4d 85 e4             	test   r12,r12
  848223:	0f 84 6f 04 00 00    	je     848698 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1418>
  848229:	be 01 00 00 00       	mov    esi,0x1
  84822e:	4c 89 e7             	mov    rdi,r12
  848231:	e8 4a ee 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  848236:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  84823c:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  848241:	be 01 00 00 00       	mov    esi,0x1
  848246:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  84824f:	4c 89 e7             	mov    rdi,r12
  848252:	f3 0f 10 84 24 04 02 00 00 	movss  xmm0,DWORD PTR [rsp+0x204]
  84825b:	48 89 84 24 b0 01 00 00 	mov    QWORD PTR [rsp+0x1b0],rax
  848263:	f3 0f 11 44 24 78    	movss  DWORD PTR [rsp+0x78],xmm0
  848269:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  848271:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  848278:	89 84 24 b8 01 00 00 	mov    DWORD PTR [rsp+0x1b8],eax
  84827f:	8b 84 24 b0 01 00 00 	mov    eax,DWORD PTR [rsp+0x1b0]
  848286:	89 84 24 b0 00 00 00 	mov    DWORD PTR [rsp+0xb0],eax
  84828d:	8b 84 24 b4 01 00 00 	mov    eax,DWORD PTR [rsp+0x1b4]
  848294:	89 84 24 b4 00 00 00 	mov    DWORD PTR [rsp+0xb4],eax
  84829b:	8b 84 24 b8 01 00 00 	mov    eax,DWORD PTR [rsp+0x1b8]
  8482a2:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  8482a9:	e8 d2 ed 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8482ae:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  8482b4:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  8482b9:	be 01 00 00 00       	mov    esi,0x1
  8482be:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  8482c7:	48 89 df             	mov    rdi,rbx
  8482ca:	48 89 84 24 a0 01 00 00 	mov    QWORD PTR [rsp+0x1a0],rax
  8482d2:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  8482da:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  8482e1:	f3 0f 10 94 24 a4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1a4]
  8482ea:	89 84 24 a8 01 00 00 	mov    DWORD PTR [rsp+0x1a8],eax
  8482f1:	f3 41 0f 5c 94 24 94 01 00 00 	subss  xmm2,DWORD PTR [r12+0x194]
  8482fb:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  848301:	e8 7a ed 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  848306:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  84830c:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  848311:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  84831a:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  848320:	48 89 84 24 90 01 00 00 	mov    QWORD PTR [rsp+0x190],rax
  848328:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  848330:	8b 84 24 a8 00 00 00 	mov    eax,DWORD PTR [rsp+0xa8]
  848337:	f3 0f 10 84 24 94 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x194]
  848340:	89 84 24 98 01 00 00 	mov    DWORD PTR [rsp+0x198],eax
  848347:	f3 0f 5c 83 94 01 00 00 	subss  xmm0,DWORD PTR [rbx+0x194]
  84834f:	f3 0f 5c d0          	subss  xmm2,xmm0
  848353:	f3 0f 58 54 24 78    	addss  xmm2,DWORD PTR [rsp+0x78]
  848359:	e9 d4 f3 ff ff       	jmp    847732 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x4b2>
  84835e:	66 90                	xchg   ax,ax
  848360:	8b 84 24 04 02 00 00 	mov    eax,DWORD PTR [rsp+0x204]
  848367:	31 f6                	xor    esi,esi
  848369:	48 89 df             	mov    rdi,rbx
  84836c:	89 44 24 68          	mov    DWORD PTR [rsp+0x68],eax
  848370:	e8 0b ed 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  848375:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  84837b:	48 8b 54 24 18       	mov    rdx,QWORD PTR [rsp+0x18]
  848380:	8b 44 24 68          	mov    eax,DWORD PTR [rsp+0x68]
  848384:	f3 0f 11 8c 24 a8 00 00 00 	movss  DWORD PTR [rsp+0xa8],xmm1
  84838d:	48 89 94 24 f0 01 00 00 	mov    QWORD PTR [rsp+0x1f0],rdx
  848395:	48 89 94 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rdx
  84839d:	8b 94 24 a8 00 00 00 	mov    edx,DWORD PTR [rsp+0xa8]
  8483a4:	89 84 24 04 02 00 00 	mov    DWORD PTR [rsp+0x204],eax
  8483ab:	89 94 24 f8 01 00 00 	mov    DWORD PTR [rsp+0x1f8],edx
  8483b2:	8b 94 24 f0 01 00 00 	mov    edx,DWORD PTR [rsp+0x1f0]
  8483b9:	89 94 24 00 02 00 00 	mov    DWORD PTR [rsp+0x200],edx
  8483c0:	8b 94 24 f8 01 00 00 	mov    edx,DWORD PTR [rsp+0x1f8]
  8483c7:	89 94 24 08 02 00 00 	mov    DWORD PTR [rsp+0x208],edx
  8483ce:	e9 0a f2 ff ff       	jmp    8475dd <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x35d>
  8483d3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8483d8:	f3 0f 10 84 24 b0 00 00 00 	movss  xmm0,DWORD PTR [rsp+0xb0]
  8483e1:	48 8d bc 24 60 01 00 00 	lea    rdi,[rsp+0x160]
  8483e9:	f3 0f 10 94 24 b8 00 00 00 	movss  xmm2,DWORD PTR [rsp+0xb8]
  8483f2:	f3 0f 5c 84 24 00 02 00 00 	subss  xmm0,DWORD PTR [rsp+0x200]
  8483fb:	f3 0f 5c 94 24 08 02 00 00 	subss  xmm2,DWORD PTR [rsp+0x208]
  848404:	f3 0f 11 4c 24 20    	movss  DWORD PTR [rsp+0x20],xmm1
  84840a:	c7 84 24 64 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x164],0x0
  848415:	f3 0f 11 84 24 60 01 00 00 	movss  DWORD PTR [rsp+0x160],xmm0
  84841e:	f3 0f 11 94 24 68 01 00 00 	movss  DWORD PTR [rsp+0x168],xmm2
  848427:	e8 54 1e d6 ff       	call   5aa280 <Ogre::Vector3::normalise()>
  84842c:	f3 0f 10 ac 24 64 01 00 00 	movss  xmm5,DWORD PTR [rsp+0x164]
  848435:	48 8d b4 24 00 02 00 00 	lea    rsi,[rsp+0x200]
  84843d:	f3 0f 10 05 f3 c6 bd 00 	movss  xmm0,DWORD PTR [rip+0xbdc6f3]        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  848445:	48 8d 94 24 60 01 00 00 	lea    rdx,[rsp+0x160]
  84844d:	0f 28 dd             	movaps xmm3,xmm5
  848450:	45 31 c0             	xor    r8d,r8d
  848453:	44 0f 28 c0          	movaps xmm8,xmm0
  848457:	31 c9                	xor    ecx,ecx
  848459:	f3 0f 10 b4 24 60 01 00 00 	movss  xmm6,DWORD PTR [rsp+0x160]
  848462:	f3 0f 10 94 24 68 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x168]
  84846b:	f3 0f 59 c6          	mulss  xmm0,xmm6
  84846f:	f3 0f 10 25 bd c6 bd 00 	movss  xmm4,DWORD PTR [rip+0xbdc6bd]        # 1424b34 <Ogre::Vector3::UNIT_Y>
  848477:	f3 44 0f 59 c2       	mulss  xmm8,xmm2
  84847c:	f3 0f 10 3d b8 c6 bd 00 	movss  xmm7,DWORD PTR [rip+0xbdc6b8]        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  848484:	f3 0f 59 d4          	mulss  xmm2,xmm4
  848488:	f3 0f 59 df          	mulss  xmm3,xmm7
  84848c:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  848492:	f3 0f 59 fe          	mulss  xmm7,xmm6
  848496:	f3 0f 59 e5          	mulss  xmm4,xmm5
  84849a:	f3 41 0f 5c d8       	subss  xmm3,xmm8
  84849f:	f3 0f 5c d7          	subss  xmm2,xmm7
  8484a3:	f3 0f 5c c4          	subss  xmm0,xmm4
  8484a7:	f3 0f 11 9c 24 60 01 00 00 	movss  DWORD PTR [rsp+0x160],xmm3
  8484b0:	f3 0f 11 94 24 64 01 00 00 	movss  DWORD PTR [rsp+0x164],xmm2
  8484b9:	f3 0f 11 84 24 68 01 00 00 	movss  DWORD PTR [rsp+0x168],xmm0
  8484c2:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  8484c9:	0f 28 c1             	movaps xmm0,xmm1
  8484cc:	e8 9f 1f 20 00       	call   a4a470 <CWeaponTrail::update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*)>
  8484d1:	f3 0f 10 4c 24 20    	movss  xmm1,DWORD PTR [rsp+0x20]
  8484d7:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  8484de:	48 8d b4 24 b0 00 00 00 	lea    rsi,[rsp+0xb0]
  8484e6:	48 8d 94 24 60 01 00 00 	lea    rdx,[rsp+0x160]
  8484ee:	45 31 c0             	xor    r8d,r8d
  8484f1:	0f 28 c1             	movaps xmm0,xmm1
  8484f4:	31 c9                	xor    ecx,ecx
  8484f6:	e8 75 1f 20 00       	call   a4a470 <CWeaponTrail::update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*)>
  8484fb:	48 8b 83 a8 06 00 00 	mov    rax,QWORD PTR [rbx+0x6a8]
  848502:	c6 80 88 00 00 00 01 	mov    BYTE PTR [rax+0x88],0x1
  848509:	44 8b 84 24 9c 00 00 00 	mov    r8d,DWORD PTR [rsp+0x9c]
  848511:	45 85 c0             	test   r8d,r8d
  848514:	0f 84 3e 01 00 00    	je     848658 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x13d8>
  84851a:	48 8d 94 24 5d 02 00 00 	lea    rdx,[rsp+0x25d]
  848522:	48 8d bc 24 20 02 00 00 	lea    rdi,[rsp+0x220]
  84852a:	be 5b 05 fa 00       	mov    esi,0xfa055b
  84852f:	e8 c4 dd d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  848534:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  84853b:	48 8d b4 24 20 02 00 00 	lea    rsi,[rsp+0x220]
  848543:	e8 48 1b 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  848548:	48 8d bc 24 20 02 00 00 	lea    rdi,[rsp+0x220]
  848550:	e8 33 dd d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848555:	e9 4d f3 ff ff       	jmp    8478a7 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x627>
  84855a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  848560:	be 6e 00 00 00       	mov    esi,0x6e
  848565:	4c 89 ff             	mov    rdi,r15
  848568:	e8 33 dd fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84856d:	84 c0                	test   al,al
  84856f:	0f 85 f9 ef ff ff    	jne    84756e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2ee>
  848575:	be 74 00 00 00       	mov    esi,0x74
  84857a:	4c 89 ff             	mov    rdi,r15
  84857d:	e8 1e dd fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  848582:	84 c0                	test   al,al
  848584:	0f 85 e4 ef ff ff    	jne    84756e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2ee>
  84858a:	be 5a 00 00 00       	mov    esi,0x5a
  84858f:	4c 89 ff             	mov    rdi,r15
  848592:	e8 09 dd fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  848597:	84 c0                	test   al,al
  848599:	c6 84 24 90 00 00 00 00 	mov    BYTE PTR [rsp+0x90],0x0
  8485a1:	0f 84 e9 ef ff ff    	je     847590 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x310>
  8485a7:	e9 c2 ef ff ff       	jmp    84756e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2ee>
  8485ac:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8485b0:	4d 85 ff             	test   r15,r15
  8485b3:	0f 84 0f f4 ff ff    	je     8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  8485b9:	49 8b bf d8 01 00 00 	mov    rdi,QWORD PTR [r15+0x1d8]
  8485c0:	48 85 ff             	test   rdi,rdi
  8485c3:	0f 85 a5 fa ff ff    	jne    84806e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xdee>
  8485c9:	e9 fa f3 ff ff       	jmp    8479c8 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x748>
  8485ce:	66 90                	xchg   ax,ax
  8485d0:	4d 85 e4             	test   r12,r12
  8485d3:	0f 84 76 fa ff ff    	je     84804f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xdcf>
  8485d9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8485e0:	e9 5c fa ff ff       	jmp    848041 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xdc1>
  8485e5:	0f 1f 00             	nop    DWORD PTR [rax]
  8485e8:	45 84 d2             	test   r10b,r10b
  8485eb:	0f 84 40 ef ff ff    	je     847531 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2b1>
  8485f1:	48 8b 44 24 70       	mov    rax,QWORD PTR [rsp+0x70]
  8485f6:	31 ff                	xor    edi,edi
  8485f8:	f3 0f 10 ab e0 04 00 00 	movss  xmm5,DWORD PTR [rbx+0x4e0]
  848600:	f3 0f 10 8b 98 00 00 00 	movss  xmm1,DWORD PTR [rbx+0x98]
  848608:	f3 0f 10 50 6c       	movss  xmm2,DWORD PTR [rax+0x6c]
  84860d:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  848611:	f3 0f 10 83 dc 04 00 00 	movss  xmm0,DWORD PTR [rbx+0x4dc]
  848619:	48 85 c0             	test   rax,rax
  84861c:	74 04                	je     848622 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x13a2>
  84861e:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  848622:	f3 0f 59 cd          	mulss  xmm1,xmm5
  848626:	48 8b b4 24 90 00 00 00 	mov    rsi,QWORD PTR [rsp+0x90]
  84862e:	f3 0f 58 cc          	addss  xmm1,xmm4
  848632:	f3 0f 58 ca          	addss  xmm1,xmm2
  848636:	f3 0f 59 c8          	mulss  xmm1,xmm0
  84863a:	f3 0f 10 44 24 78    	movss  xmm0,DWORD PTR [rsp+0x78]
  848640:	f3 0f 58 cb          	addss  xmm1,xmm3
  848644:	e8 e7 63 10 00       	call   94ea30 <CLevel::findItemWithinView(Ogre::Matrix4 const&, float, float)>
  848649:	48 85 c0             	test   rax,rax
  84864c:	48 0f 45 e8          	cmovne rbp,rax
  848650:	45 31 e4             	xor    r12d,r12d
  848653:	e9 d9 ee ff ff       	jmp    847531 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2b1>
  848658:	48 8d 94 24 5c 02 00 00 	lea    rdx,[rsp+0x25c]
  848660:	48 8d bc 24 10 02 00 00 	lea    rdi,[rsp+0x210]
  848668:	be 50 05 fa 00       	mov    esi,0xfa0550
  84866d:	e8 86 dc d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  848672:	48 8b bb a8 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a8]
  848679:	48 8d b4 24 10 02 00 00 	lea    rsi,[rsp+0x210]
  848681:	e8 0a 1a 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  848686:	48 8d bc 24 10 02 00 00 	lea    rdi,[rsp+0x210]
  84868e:	e8 f5 db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848693:	e9 0f f2 ff ff       	jmp    8478a7 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x627>
  848698:	48 8b 44 24 70       	mov    rax,QWORD PTR [rsp+0x70]
  84869d:	f3 0f 10 83 dc 04 00 00 	movss  xmm0,DWORD PTR [rbx+0x4dc]
  8486a5:	f3 0f 10 8b bc 00 00 00 	movss  xmm1,DWORD PTR [rbx+0xbc]
  8486ad:	f3 0f 10 93 b8 00 00 00 	movss  xmm2,DWORD PTR [rbx+0xb8]
  8486b5:	f3 0f 59 40 6c       	mulss  xmm0,DWORD PTR [rax+0x6c]
  8486ba:	f3 0f 58 84 24 98 00 00 00 	addss  xmm0,DWORD PTR [rsp+0x98]
  8486c3:	f3 0f 59 c8          	mulss  xmm1,xmm0
  8486c7:	f3 0f 59 d0          	mulss  xmm2,xmm0
  8486cb:	f3 0f 59 83 b4 00 00 00 	mulss  xmm0,DWORD PTR [rbx+0xb4]
  8486d3:	f3 0f 58 8c 24 08 02 00 00 	addss  xmm1,DWORD PTR [rsp+0x208]
  8486dc:	f3 0f 58 94 24 04 02 00 00 	addss  xmm2,DWORD PTR [rsp+0x204]
  8486e5:	f3 0f 58 84 24 00 02 00 00 	addss  xmm0,DWORD PTR [rsp+0x200]
  8486ee:	f3 0f 11 8c 24 b8 00 00 00 	movss  DWORD PTR [rsp+0xb8],xmm1
  8486f7:	f3 0f 11 84 24 b0 00 00 00 	movss  DWORD PTR [rsp+0xb0],xmm0
  848700:	e9 2d f0 ff ff       	jmp    847732 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x4b2>
  848705:	48 8d bc 24 20 02 00 00 	lea    rdi,[rsp+0x220]
  84870d:	48 89 c3             	mov    rbx,rax
  848710:	e8 73 db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848715:	48 89 df             	mov    rdi,rbx
  848718:	e8 7b bd d0 ff       	call   554498 <_Unwind_Resume@plt>
  84871d:	48 8d bc 24 30 02 00 00 	lea    rdi,[rsp+0x230]
  848725:	48 89 c3             	mov    rbx,rax
  848728:	e8 5b db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84872d:	eb e6                	jmp    848715 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1495>
  84872f:	48 89 c3             	mov    rbx,rax
  848732:	eb e1                	jmp    848715 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1495>
  848734:	48 8b 7c 24 78       	mov    rdi,QWORD PTR [rsp+0x78]
  848739:	48 89 c3             	mov    rbx,rax
  84873c:	e8 27 cb d0 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  848741:	48 8d bc 24 40 02 00 00 	lea    rdi,[rsp+0x240]
  848749:	e8 3a db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84874e:	48 8d bc 24 50 02 00 00 	lea    rdi,[rsp+0x250]
  848756:	e8 2d db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84875b:	eb b8                	jmp    848715 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1495>
  84875d:	48 89 c3             	mov    rbx,rax
  848760:	eb df                	jmp    848741 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x14c1>
  848762:	48 89 c3             	mov    rbx,rax
  848765:	eb e7                	jmp    84874e <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x14ce>
  848767:	eb c6                	jmp    84872f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x14af>
  848769:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  848770:	eb bd                	jmp    84872f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x14af>
  848772:	48 8d bc 24 10 02 00 00 	lea    rdi,[rsp+0x210]
  84877a:	48 89 c3             	mov    rbx,rax
  84877d:	e8 06 db d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  848782:	eb 91                	jmp    848715 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1495>
  848784:	eb a9                	jmp    84872f <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x14af>
  848786:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]

