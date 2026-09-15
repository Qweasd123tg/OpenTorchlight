# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0xd79290, 0xd796c0); source instructions unchanged.
  d79290:	41 57                	push   r15
  d79292:	41 56                	push   r14
  d79294:	4d 89 ce             	mov    r14,r9
  d79297:	41 55                	push   r13
  d79299:	4d 89 c5             	mov    r13,r8
  d7929c:	41 54                	push   r12
  d7929e:	49 89 cc             	mov    r12,rcx
  d792a1:	55                   	push   rbp
  d792a2:	53                   	push   rbx
  d792a3:	48 81 ec a8 00 00 00 	sub    rsp,0xa8
  d792aa:	48 85 f6             	test   rsi,rsi
  d792ad:	8b 8c 24 e8 00 00 00 	mov    ecx,DWORD PTR [rsp+0xe8]
  d792b4:	0f 84 c5 03 00 00    	je     d7967f <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3ef>
  d792ba:	4d 85 c0             	test   r8,r8
  d792bd:	0f 84 bc 03 00 00    	je     d7967f <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3ef>
  d792c3:	83 f9 ff             	cmp    ecx,0xffffffff
  d792c6:	48 c7 44 24 30 00 00 00 00 	mov    QWORD PTR [rsp+0x30],0x0
  d792cf:	c7 44 24 38 00 00 00 00 	mov    DWORD PTR [rsp+0x38],0x0
  d792d7:	c7 44 24 3c 00 00 00 00 	mov    DWORD PTR [rsp+0x3c],0x0
  d792df:	c7 44 24 40 0a 00 00 00 	mov    DWORD PTR [rsp+0x40],0xa
  d792e7:	0f 84 a4 03 00 00    	je     d79691 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x401>
  d792ed:	48 8d 44 24 30       	lea    rax,[rsp+0x30]
  d792f2:	4c 8b 8c 24 e0 00 00 00 	mov    r9,QWORD PTR [rsp+0xe0]
  d792fa:	89 0c 24             	mov    DWORD PTR [rsp],ecx
  d792fd:	4d 89 f0             	mov    r8,r14
  d79300:	89 d1                	mov    ecx,edx
  d79302:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  d7930a:	48 89 c2             	mov    rdx,rax
  d7930d:	e8 ce fb ff ff       	call   d78ee0 <CResourceManager::createUnitsBySpawnClass(CSpawnClass*, TArrayList<CBaseUnit*>&, unsigned int, CCharacter*, CCharacter*, int, int)>
  d79312:	8b 7c 24 38          	mov    edi,DWORD PTR [rsp+0x38]
  d79316:	85 ff                	test   edi,edi
  d79318:	0f 84 52 03 00 00    	je     d79670 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3e0>
  d7931e:	31 ed                	xor    ebp,ebp
  d79320:	4c 8d bc 24 90 00 00 00 	lea    r15,[rsp+0x90]
  d79328:	e9 62 02 00 00       	jmp    d7958f <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x2ff>
  d7932d:	0f 1f 00             	nop    DWORD PTR [rax]
  d79330:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  d79335:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d79338:	be 1f 00 00 00       	mov    esi,0x1f
  d7933d:	e8 5e cf a7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  d79342:	84 c0                	test   al,al
  d79344:	74 43                	je     d79389 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0xf9>
  d79346:	39 6c 24 3c          	cmp    DWORD PTR [rsp+0x3c],ebp
  d7934a:	0f 87 08 03 00 00    	ja     d79658 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3c8>
  d79350:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  d79355:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d79358:	be 22 00 00 00       	mov    esi,0x22
  d7935d:	e8 3e cf a7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  d79362:	84 c0                	test   al,al
  d79364:	75 23                	jne    d79389 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0xf9>
  d79366:	41 8b 04 24          	mov    eax,DWORD PTR [r12]
  d7936a:	89 84 24 90 00 00 00 	mov    DWORD PTR [rsp+0x90],eax
  d79371:	41 8b 44 24 04       	mov    eax,DWORD PTR [r12+0x4]
  d79376:	89 84 24 94 00 00 00 	mov    DWORD PTR [rsp+0x94],eax
  d7937d:	41 8b 44 24 08       	mov    eax,DWORD PTR [r12+0x8]
  d79382:	89 84 24 98 00 00 00 	mov    DWORD PTR [rsp+0x98],eax
  d79389:	39 6c 24 3c          	cmp    DWORD PTR [rsp+0x3c],ebp
  d7938d:	0f 87 ad 02 00 00    	ja     d79640 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3b0>
  d79393:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  d79398:	48 8b 30             	mov    rsi,QWORD PTR [rax]
  d7939b:	4c 89 fa             	mov    rdx,r15
  d7939e:	4c 89 ef             	mov    rdi,r13
  d793a1:	e8 0a 3a be ff       	call   95cdb0 <CLevel::addUnit(CBaseUnit*, Ogre::Vector3 const&)>
  d793a6:	39 6c 24 3c          	cmp    DWORD PTR [rsp+0x3c],ebp
  d793aa:	0f 87 80 02 00 00    	ja     d79630 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3a0>
  d793b0:	48 8b 5c 24 30       	mov    rbx,QWORD PTR [rsp+0x30]
  d793b5:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
  d793b8:	48 85 ff             	test   rdi,rdi
  d793bb:	0f 84 c1 01 00 00    	je     d79582 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x2f2>
  d793c1:	31 c9                	xor    ecx,ecx
  d793c3:	ba 80 e2 fc 00       	mov    edx,0xfce280
  d793c8:	be 60 92 fc 00       	mov    esi,0xfc9260
  d793cd:	e8 86 c3 7d ff       	call   555758 <__dynamic_cast@plt>
  d793d2:	48 85 c0             	test   rax,rax
  d793d5:	48 89 c3             	mov    rbx,rax
  d793d8:	0f 84 a4 01 00 00    	je     d79582 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x2f2>
  d793de:	4d 85 f6             	test   r14,r14
  d793e1:	0f 84 93 01 00 00    	je     d7957a <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x2ea>
  d793e7:	be 01 00 00 00       	mov    esi,0x1
  d793ec:	48 89 c7             	mov    rdi,rax
  d793ef:	e8 8c dc c6 ff       	call   9e7080 <CPositionableObject::getPosition(bool)>
  d793f4:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  d793fa:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  d793ff:	be 01 00 00 00       	mov    esi,0x1
  d79404:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  d7940a:	4c 89 f7             	mov    rdi,r14
  d7940d:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  d79412:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  d79417:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  d7941b:	89 44 24 68          	mov    DWORD PTR [rsp+0x68],eax
  d7941f:	e8 5c dc c6 ff       	call   9e7080 <CPositionableObject::getPosition(bool)>
  d79424:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  d7942a:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  d7942f:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  d79435:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  d7943a:	f3 0f 10 54 24 74    	movss  xmm2,DWORD PTR [rsp+0x74]
  d79440:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  d79445:	f3 0f 10 4c 24 70    	movss  xmm1,DWORD PTR [rsp+0x70]
  d7944b:	f3 0f 5c 54 24 64    	subss  xmm2,DWORD PTR [rsp+0x64]
  d79451:	f3 0f 5c 4c 24 60    	subss  xmm1,DWORD PTR [rsp+0x60]
  d79457:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  d7945b:	89 44 24 78          	mov    DWORD PTR [rsp+0x78],eax
  d7945f:	f3 0f 10 44 24 78    	movss  xmm0,DWORD PTR [rsp+0x78]
  d79465:	f3 0f 5c 44 24 68    	subss  xmm0,DWORD PTR [rsp+0x68]
  d7946b:	0f 28 e2             	movaps xmm4,xmm2
  d7946e:	0f 28 d9             	movaps xmm3,xmm1
  d79471:	f3 0f 11 94 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm2
  d7947a:	f3 0f 59 e2          	mulss  xmm4,xmm2
  d7947e:	f3 0f 11 8c 24 80 00 00 00 	movss  DWORD PTR [rsp+0x80],xmm1
  d79487:	f3 0f 59 d9          	mulss  xmm3,xmm1
  d7948b:	f3 0f 11 84 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm0
  d79494:	f3 0f 58 dc          	addss  xmm3,xmm4
  d79498:	0f 28 e0             	movaps xmm4,xmm0
  d7949b:	f3 0f 59 e0          	mulss  xmm4,xmm0
  d7949f:	f3 0f 58 dc          	addss  xmm3,xmm4
  d794a3:	f3 0f 51 db          	sqrtss xmm3,xmm3
  d794a7:	0f 14 db             	unpcklps xmm3,xmm3
  d794aa:	0f 5a e3             	cvtps2pd xmm4,xmm3
  d794ad:	66 0f 2e 25 eb f2 22 00 	ucomisd xmm4,QWORD PTR [rip+0x22f2eb]        # fa87a0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x100>
  d794b5:	76 4a                	jbe    d79501 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x271>
  d794b7:	f3 0f 10 05 3d b3 22 00 	movss  xmm0,DWORD PTR [rip+0x22b33d]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  d794bf:	f3 0f 5e c3          	divss  xmm0,xmm3
  d794c3:	f3 0f 10 8c 24 80 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x80]
  d794cc:	f3 0f 10 94 24 84 00 00 00 	movss  xmm2,DWORD PTR [rsp+0x84]
  d794d5:	f3 0f 59 c8          	mulss  xmm1,xmm0
  d794d9:	f3 0f 59 d0          	mulss  xmm2,xmm0
  d794dd:	f3 0f 59 84 24 88 00 00 00 	mulss  xmm0,DWORD PTR [rsp+0x88]
  d794e6:	f3 0f 11 8c 24 80 00 00 00 	movss  DWORD PTR [rsp+0x80],xmm1
  d794ef:	f3 0f 11 94 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm2
  d794f8:	f3 0f 11 84 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm0
  d79501:	f3 0f 10 1d 2f b6 6a 00 	movss  xmm3,DWORD PTR [rip+0x6ab62f]        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  d79509:	48 8d b4 24 80 00 00 00 	lea    rsi,[rsp+0x80]
  d79511:	0f 28 e2             	movaps xmm4,xmm2
  d79514:	48 89 df             	mov    rdi,rbx
  d79517:	0f 28 fb             	movaps xmm7,xmm3
  d7951a:	f3 0f 10 35 12 b6 6a 00 	movss  xmm6,DWORD PTR [rip+0x6ab612]        # 1424b34 <Ogre::Vector3::UNIT_Y>
  d79522:	f3 0f 10 2d 12 b6 6a 00 	movss  xmm5,DWORD PTR [rip+0x6ab612]        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  d7952a:	f3 0f 59 e6          	mulss  xmm4,xmm6
  d7952e:	f3 0f 59 f9          	mulss  xmm7,xmm1
  d79532:	f3 0f 59 f0          	mulss  xmm6,xmm0
  d79536:	f3 0f 59 cd          	mulss  xmm1,xmm5
  d7953a:	f3 0f 59 c3          	mulss  xmm0,xmm3
  d7953e:	f3 0f 59 d5          	mulss  xmm2,xmm5
  d79542:	f3 0f 5c e7          	subss  xmm4,xmm7
  d79546:	f3 0f 5c ce          	subss  xmm1,xmm6
  d7954a:	f3 0f 5c c2          	subss  xmm0,xmm2
  d7954e:	f3 0f 11 64 24 58    	movss  DWORD PTR [rsp+0x58],xmm4
  d79554:	f3 0f 11 4c 24 54    	movss  DWORD PTR [rsp+0x54],xmm1
  d7955a:	f3 0f 11 44 24 50    	movss  DWORD PTR [rsp+0x50],xmm0
  d79560:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  d79563:	ff 90 48 01 00 00    	call   QWORD PTR [rax+0x148]
  d79569:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  d7956c:	48 8d 74 24 50       	lea    rsi,[rsp+0x50]
  d79571:	48 89 df             	mov    rdi,rbx
  d79574:	ff 90 70 01 00 00    	call   QWORD PTR [rax+0x170]
  d7957a:	48 89 df             	mov    rdi,rbx
  d7957d:	e8 5e c1 ab ff       	call   8356e0 <CCharacter::spawn()>
  d79582:	83 c5 01             	add    ebp,0x1
  d79585:	3b 6c 24 38          	cmp    ebp,DWORD PTR [rsp+0x38]
  d79589:	0f 83 e1 00 00 00    	jae    d79670 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3e0>
  d7958f:	89 eb                	mov    ebx,ebp
  d79591:	f3 0f 10 0d 77 b2 22 00 	movss  xmm1,DWORD PTR [rip+0x22b277]        # fa4810 <vtable for Ogre::FrameListener+0x50>
  d79599:	f3 48 0f 2a c3       	cvtsi2ss xmm0,rbx
  d7959e:	31 d2                	xor    edx,edx
  d795a0:	f3 0f 10 1d 68 b2 22 00 	movss  xmm3,DWORD PTR [rip+0x22b268]        # fa4810 <vtable for Ogre::FrameListener+0x50>
  d795a8:	4c 89 e6             	mov    rsi,r12
  d795ab:	4c 89 ef             	mov    rdi,r13
  d795ae:	f3 0f 5e 05 1e f1 22 00 	divss  xmm0,DWORD PTR [rip+0x22f11e]        # fa86d4 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x34>
  d795b6:	f3 0f c2 c8 01       	cmpltss xmm1,xmm0
  d795bb:	0f 28 d0             	movaps xmm2,xmm0
  d795be:	0f 28 c1             	movaps xmm0,xmm1
  d795c1:	0f 54 d1             	andps  xmm2,xmm1
  d795c4:	0f 55 c3             	andnps xmm0,xmm3
  d795c7:	0f 56 c2             	orps   xmm0,xmm2
  d795ca:	e8 d1 c3 bc ff       	call   9459a0 <CLevel::randomOpenPosition(Ogre::Vector3 const&, float, bool)>
  d795cf:	66 0f d6 44 24 18    	movq   QWORD PTR [rsp+0x18],xmm0
  d795d5:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  d795da:	39 6c 24 3c          	cmp    DWORD PTR [rsp+0x3c],ebp
  d795de:	f3 0f 10 05 2a b2 22 00 	movss  xmm0,DWORD PTR [rip+0x22b22a]        # fa4810 <vtable for Ogre::FrameListener+0x50>
  d795e6:	f3 41 0f 58 44 24 04 	addss  xmm0,DWORD PTR [r12+0x4]
  d795ed:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  d795f3:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  d795fb:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  d79600:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  d79604:	89 84 24 98 00 00 00 	mov    DWORD PTR [rsp+0x98],eax
  d7960b:	f3 0f 11 84 24 94 00 00 00 	movss  DWORD PTR [rsp+0x94],xmm0
  d79614:	0f 86 16 fd ff ff    	jbe    d79330 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0xa0>
  d7961a:	48 8d 04 dd 00 00 00 00 	lea    rax,[rbx*8+0x0]
  d79622:	48 03 44 24 30       	add    rax,QWORD PTR [rsp+0x30]
  d79627:	e9 09 fd ff ff       	jmp    d79335 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0xa5>
  d7962c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  d79630:	48 c1 e3 03          	shl    rbx,0x3
  d79634:	48 03 5c 24 30       	add    rbx,QWORD PTR [rsp+0x30]
  d79639:	e9 77 fd ff ff       	jmp    d793b5 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x125>
  d7963e:	66 90                	xchg   ax,ax
  d79640:	48 8d 04 dd 00 00 00 00 	lea    rax,[rbx*8+0x0]
  d79648:	48 03 44 24 30       	add    rax,QWORD PTR [rsp+0x30]
  d7964d:	e9 46 fd ff ff       	jmp    d79398 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x108>
  d79652:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  d79658:	48 8d 04 dd 00 00 00 00 	lea    rax,[rbx*8+0x0]
  d79660:	48 03 44 24 30       	add    rax,QWORD PTR [rsp+0x30]
  d79665:	e9 eb fc ff ff       	jmp    d79355 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0xc5>
  d7966a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  d79670:	48 8b 7c 24 30       	mov    rdi,QWORD PTR [rsp+0x30]
  d79675:	48 85 ff             	test   rdi,rdi
  d79678:	74 05                	je     d7967f <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x3ef>
  d7967a:	e8 b9 9f 7d ff       	call   553638 <operator delete[](void*)@plt>
  d7967f:	48 81 c4 a8 00 00 00 	add    rsp,0xa8
  d79686:	5b                   	pop    rbx
  d79687:	5d                   	pop    rbp
  d79688:	41 5c                	pop    r12
  d7968a:	41 5d                	pop    r13
  d7968c:	41 5e                	pop    r14
  d7968e:	41 5f                	pop    r15
  d79690:	c3                   	ret
  d79691:	41 8b 88 a8 01 00 00 	mov    ecx,DWORD PTR [r8+0x1a8]
  d79698:	e9 50 fc ff ff       	jmp    d792ed <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x5d>
  d7969d:	48 8b 7c 24 30       	mov    rdi,QWORD PTR [rsp+0x30]
  d796a2:	48 89 c3             	mov    rbx,rax
  d796a5:	48 85 ff             	test   rdi,rdi
  d796a8:	74 05                	je     d796af <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)+0x41f>
  d796aa:	e8 89 9f 7d ff       	call   553638 <operator delete[](void*)@plt>
  d796af:	48 89 df             	mov    rdi,rbx
  d796b2:	e8 e1 ad 7d ff       	call   554498 <_Unwind_Resume@plt>
  d796b7:	90                   	nop
  d796b8:	90                   	nop
  d796b9:	90                   	nop
  d796ba:	90                   	nop
  d796bb:	90                   	nop
  d796bc:	90                   	nop
  d796bd:	90                   	nop
  d796be:	90                   	nop
  d796bf:	90                   	nop
