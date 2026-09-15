# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000826140 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)>:
  826140:	55                   	push   rbp
  826141:	53                   	push   rbx
  826142:	48 89 fb             	mov    rbx,rdi
  826145:	48 81 ec 88 00 00 00 	sub    rsp,0x88
  82614c:	48 83 bf 40 03 00 00 00 	cmp    QWORD PTR [rdi+0x340],0x0
  826154:	0f 84 d6 02 00 00    	je     826430 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x2f0>
  82615a:	48 83 bb 90 03 00 00 00 	cmp    QWORD PTR [rbx+0x390],0x0
  826162:	0f 84 e8 02 00 00    	je     826450 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x310>
  826168:	48 89 df             	mov    rdi,rbx
  82616b:	e8 b0 9a fe ff       	call   80fc20 <CCharacter::getWeaponInLeftHand()>
  826170:	48 85 c0             	test   rax,rax
  826173:	0f 84 17 01 00 00    	je     826290 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x150>
  826179:	48 89 df             	mov    rdi,rbx
  82617c:	e8 9f 9a fe ff       	call   80fc20 <CCharacter::getWeaponInLeftHand()>
  826181:	be 23 00 00 00       	mov    esi,0x23
  826186:	48 89 c7             	mov    rdi,rax
  826189:	e8 12 01 fd ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82618e:	84 c0                	test   al,al
  826190:	0f 84 fa 00 00 00    	je     826290 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x150>
  826196:	ba 07 00 00 00       	mov    edx,0x7
  82619b:	be 4e 00 00 00       	mov    esi,0x4e
  8261a0:	48 89 df             	mov    rdi,rbx
  8261a3:	e8 38 d6 fe ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8261a8:	f3 0f 11 44 24 2c    	movss  DWORD PTR [rsp+0x2c],xmm0
  8261ae:	bd 01 00 00 00       	mov    ebp,0x1
  8261b3:	48 89 df             	mov    rdi,rbx
  8261b6:	e8 c5 c3 fe ff       	call   812580 <CCharacter::attackRange()>
  8261bb:	48 83 bb 40 03 00 00 00 	cmp    QWORD PTR [rbx+0x340],0x0
  8261c3:	f3 0f 10 93 dc 04 00 00 	movss  xmm2,DWORD PTR [rbx+0x4dc]
  8261cb:	f3 0f 59 d0          	mulss  xmm2,xmm0
  8261cf:	0f 84 63 01 00 00    	je     826338 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x1f8>
  8261d5:	be 01 00 00 00       	mov    esi,0x1
  8261da:	48 89 df             	mov    rdi,rbx
  8261dd:	f3 0f 11 54 24 10    	movss  DWORD PTR [rsp+0x10],xmm2
  8261e3:	e8 98 0e 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8261e8:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8261ee:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8261f3:	be 01 00 00 00       	mov    esi,0x1
  8261f8:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  8261fe:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  826205:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  82620a:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  82620f:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  826213:	89 44 24 68          	mov    DWORD PTR [rsp+0x68],eax
  826217:	e8 64 0e 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82621c:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  826222:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  826227:	f3 0f 10 25 61 25 78 00 	movss  xmm4,DWORD PTR [rip+0x782561]        # fa8790 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xf0>
  82622f:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  826235:	f3 0f 10 6c 24 68    	movss  xmm5,DWORD PTR [rsp+0x68]
  82623b:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  826240:	f3 0f 10 4c 24 74    	movss  xmm1,DWORD PTR [rsp+0x74]
  826246:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  82624b:	f3 0f 5c 4c 24 64    	subss  xmm1,DWORD PTR [rsp+0x64]
  826251:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  826255:	f3 0f 10 44 24 70    	movss  xmm0,DWORD PTR [rsp+0x70]
  82625b:	f3 0f 10 74 24 60    	movss  xmm6,DWORD PTR [rsp+0x60]
  826261:	89 44 24 78          	mov    DWORD PTR [rsp+0x78],eax
  826265:	f3 0f 10 54 24 10    	movss  xmm2,DWORD PTR [rsp+0x10]
  82626b:	f3 0f 10 5c 24 78    	movss  xmm3,DWORD PTR [rsp+0x78]
  826271:	0f 54 cc             	andps  xmm1,xmm4
  826274:	0f 2e 0d 49 82 7a 00 	ucomiss xmm1,DWORD PTR [rip+0x7a8249]        # fce4c4 <vtable for iInventoryListener+0x84>
  82627b:	76 53                	jbe    8262d0 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x190>
  82627d:	40 84 ed             	test   bpl,bpl
  826280:	75 4e                	jne    8262d0 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x190>
  826282:	31 c0                	xor    eax,eax
  826284:	48 81 c4 88 00 00 00 	add    rsp,0x88
  82628b:	5b                   	pop    rbx
  82628c:	5d                   	pop    rbp
  82628d:	c3                   	ret
  82628e:	66 90                	xchg   ax,ax
  826290:	48 89 df             	mov    rdi,rbx
  826293:	e8 b8 99 fe ff       	call   80fc50 <CCharacter::getWeaponInRightHand()>
  826298:	48 85 c0             	test   rax,rax
  82629b:	74 1d                	je     8262ba <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x17a>
  82629d:	48 89 df             	mov    rdi,rbx
  8262a0:	e8 ab 99 fe ff       	call   80fc50 <CCharacter::getWeaponInRightHand()>
  8262a5:	be 23 00 00 00       	mov    esi,0x23
  8262aa:	48 89 c7             	mov    rdi,rax
  8262ad:	e8 ee ff fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8262b2:	84 c0                	test   al,al
  8262b4:	0f 85 dc fe ff ff    	jne    826196 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x56>
  8262ba:	0f 57 c0             	xorps  xmm0,xmm0
  8262bd:	31 ed                	xor    ebp,ebp
  8262bf:	f3 0f 11 44 24 2c    	movss  DWORD PTR [rsp+0x2c],xmm0
  8262c5:	e9 e9 fe ff ff       	jmp    8261b3 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x73>
  8262ca:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  8262d0:	f3 0f 5c c6          	subss  xmm0,xmm6
  8262d4:	0f 57 c9             	xorps  xmm1,xmm1
  8262d7:	f3 0f 5c dd          	subss  xmm3,xmm5
  8262db:	48 8b 83 40 03 00 00 	mov    rax,QWORD PTR [rbx+0x340]
  8262e2:	f3 0f 58 54 24 2c    	addss  xmm2,DWORD PTR [rsp+0x2c]
  8262e8:	f3 0f 59 c0          	mulss  xmm0,xmm0
  8262ec:	f3 0f 59 db          	mulss  xmm3,xmm3
  8262f0:	f3 0f 58 c1          	addss  xmm0,xmm1
  8262f4:	f3 0f 58 c3          	addss  xmm0,xmm3
  8262f8:	f3 0f 10 98 94 01 00 00 	movss  xmm3,DWORD PTR [rax+0x194]
  826300:	0f 28 e3             	movaps xmm4,xmm3
  826303:	f3 0f c2 e1 05       	cmpnltss xmm4,xmm1
  826308:	f3 0f 51 c0          	sqrtss xmm0,xmm0
  82630c:	0f 54 dc             	andps  xmm3,xmm4
  82630f:	0f 28 e1             	movaps xmm4,xmm1
  826312:	f3 0f 5f 8b 94 01 00 00 	maxss  xmm1,DWORD PTR [rbx+0x194]
  82631a:	0f 56 e3             	orps   xmm4,xmm3
  82631d:	f3 0f 5c c4          	subss  xmm0,xmm4
  826321:	f3 0f 5c c1          	subss  xmm0,xmm1
  826325:	0f 2e c2             	ucomiss xmm0,xmm2
  826328:	0f 96 c0             	setbe  al
  82632b:	48 81 c4 88 00 00 00 	add    rsp,0x88
  826332:	5b                   	pop    rbx
  826333:	5d                   	pop    rbp
  826334:	c3                   	ret
  826335:	0f 1f 00             	nop    DWORD PTR [rax]
  826338:	48 83 bb 50 03 00 00 00 	cmp    QWORD PTR [rbx+0x350],0x0
  826340:	b8 01 00 00 00       	mov    eax,0x1
  826345:	0f 84 39 ff ff ff    	je     826284 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x144>
  82634b:	48 89 df             	mov    rdi,rbx
  82634e:	be 01 00 00 00       	mov    esi,0x1
  826353:	f3 0f 11 54 24 10    	movss  DWORD PTR [rsp+0x10],xmm2
  826359:	e8 22 0d 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82635e:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  826364:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  826369:	be 01 00 00 00       	mov    esi,0x1
  82636e:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  826374:	48 8b bb 50 03 00 00 	mov    rdi,QWORD PTR [rbx+0x350]
  82637b:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  826380:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  826385:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  826389:	89 44 24 48          	mov    DWORD PTR [rsp+0x48],eax
  82638d:	e8 ee 0c 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  826392:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  826398:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82639d:	f3 0f 11 4c 24 38    	movss  DWORD PTR [rsp+0x38],xmm1
  8263a3:	0f 57 c9             	xorps  xmm1,xmm1
  8263a6:	f3 0f 10 54 24 10    	movss  xmm2,DWORD PTR [rsp+0x10]
  8263ac:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  8263b1:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  8263b6:	f3 0f 10 44 24 50    	movss  xmm0,DWORD PTR [rsp+0x50]
  8263bc:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  8263c0:	f3 0f 5c 44 24 40    	subss  xmm0,DWORD PTR [rsp+0x40]
  8263c6:	f3 0f 58 54 24 2c    	addss  xmm2,DWORD PTR [rsp+0x2c]
  8263cc:	89 44 24 58          	mov    DWORD PTR [rsp+0x58],eax
  8263d0:	48 8b 83 50 03 00 00 	mov    rax,QWORD PTR [rbx+0x350]
  8263d7:	f3 0f 10 5c 24 58    	movss  xmm3,DWORD PTR [rsp+0x58]
  8263dd:	f3 0f 5c 5c 24 48    	subss  xmm3,DWORD PTR [rsp+0x48]
  8263e3:	f3 0f 59 c0          	mulss  xmm0,xmm0
  8263e7:	f3 0f 58 c1          	addss  xmm0,xmm1
  8263eb:	f3 0f 59 db          	mulss  xmm3,xmm3
  8263ef:	f3 0f 58 c3          	addss  xmm0,xmm3
  8263f3:	f3 0f 10 98 94 01 00 00 	movss  xmm3,DWORD PTR [rax+0x194]
  8263fb:	0f 28 e3             	movaps xmm4,xmm3
  8263fe:	f3 0f c2 e1 05       	cmpnltss xmm4,xmm1
  826403:	f3 0f 51 c0          	sqrtss xmm0,xmm0
  826407:	0f 54 dc             	andps  xmm3,xmm4
  82640a:	0f 28 e1             	movaps xmm4,xmm1
  82640d:	f3 0f 5f 8b 94 01 00 00 	maxss  xmm1,DWORD PTR [rbx+0x194]
  826415:	0f 56 e3             	orps   xmm4,xmm3
  826418:	f3 0f 5c c4          	subss  xmm0,xmm4
  82641c:	f3 0f 5c c1          	subss  xmm0,xmm1
  826420:	0f 2e c2             	ucomiss xmm0,xmm2
  826423:	0f 96 c0             	setbe  al
  826426:	48 81 c4 88 00 00 00 	add    rsp,0x88
  82642d:	5b                   	pop    rbx
  82642e:	5d                   	pop    rbp
  82642f:	c3                   	ret
  826430:	48 83 bf 50 03 00 00 00 	cmp    QWORD PTR [rdi+0x350],0x0
  826438:	0f 84 44 fe ff ff    	je     826282 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x142>
  82643e:	48 83 bb 90 03 00 00 00 	cmp    QWORD PTR [rbx+0x390],0x0
  826446:	0f 85 1c fd ff ff    	jne    826168 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x28>
  82644c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  826450:	31 f6                	xor    esi,esi
  826452:	48 89 df             	mov    rdi,rbx
  826455:	e8 66 b7 fe ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82645a:	48 83 bb 90 03 00 00 00 	cmp    QWORD PTR [rbx+0x390],0x0
  826462:	0f 85 00 fd ff ff    	jne    826168 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x28>
  826468:	e9 15 fe ff ff       	jmp    826282 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)+0x142>
  82646d:	90                   	nop
  82646e:	66 90                	xchg   ax,ax

