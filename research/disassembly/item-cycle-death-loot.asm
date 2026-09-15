# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x838ed0, 0x83a9b0); source instructions unchanged.
  838ed0:	41 57                	push   r15
  838ed2:	41 56                	push   r14
  838ed4:	41 55                	push   r13
  838ed6:	49 89 d5             	mov    r13,rdx
  838ed9:	41 54                	push   r12
  838edb:	49 89 f4             	mov    r12,rsi
  838ede:	55                   	push   rbp
  838edf:	89 cd                	mov    ebp,ecx
  838ee1:	53                   	push   rbx
  838ee2:	48 89 fb             	mov    rbx,rdi
  838ee5:	48 81 ec 28 03 00 00 	sub    rsp,0x328
  838eec:	f3 0f 11 44 24 60    	movss  DWORD PTR [rsp+0x60],xmm0
  838ef2:	44 8b b7 00 01 00 00 	mov    r14d,DWORD PTR [rdi+0x100]
  838ef9:	45 85 f6             	test   r14d,r14d
  838efc:	0f 84 1b 05 00 00    	je     83941d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x54d>
  838f02:	48 8b bf 40 06 00 00 	mov    rdi,QWORD PTR [rdi+0x640]
  838f09:	48 85 ff             	test   rdi,rdi
  838f0c:	74 08                	je     838f16 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x46>
  838f0e:	48 89 de             	mov    rsi,rbx
  838f11:	e8 5a 5d fd ff       	call   80ec70 <CCharacter::removePet(CCharacter*)>
  838f16:	8b 83 30 03 00 00    	mov    eax,DWORD PTR [rbx+0x330]
  838f1c:	83 f8 05             	cmp    eax,0x5
  838f1f:	0f 84 f8 04 00 00    	je     83941d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x54d>
  838f25:	83 f8 06             	cmp    eax,0x6
  838f28:	0f 84 ef 04 00 00    	je     83941d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x54d>
  838f2e:	4c 8d b4 24 00 03 00 00 	lea    r14,[rsp+0x300]
  838f36:	48 8d 94 24 1f 03 00 00 	lea    rdx,[rsp+0x31f]
  838f3e:	be f0 9c fc 00       	mov    esi,0xfc9cf0
  838f43:	4c 89 f7             	mov    rdi,r14
  838f46:	e8 0d cf d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  838f4b:	4c 89 f6             	mov    rsi,r14
  838f4e:	48 89 df             	mov    rdi,rbx
  838f51:	e8 3a 64 fc ff       	call   7ff390 <CBaseUnit::hasUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  838f56:	48 8b bc 24 00 03 00 00 	mov    rdi,QWORD PTR [rsp+0x300]
  838f5e:	48 83 ef 18          	sub    rdi,0x18
  838f62:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  838f69:	0f 85 c6 19 00 00    	jne    83a935 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1a65>
  838f6f:	84 c0                	test   al,al
  838f71:	0f 85 d9 04 00 00    	jne    839450 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x580>
  838f77:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  838f7e:	c6 83 99 01 00 00 01 	mov    BYTE PTR [rbx+0x199],0x1
  838f85:	c6 83 9a 01 00 00 01 	mov    BYTE PTR [rbx+0x19a],0x1
  838f8c:	48 85 ff             	test   rdi,rdi
  838f8f:	0f 84 9b 00 00 00    	je     839030 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x160>
  838f95:	be 81 00 00 00       	mov    esi,0x81
  838f9a:	e8 e1 25 fb ff       	call   7eb580 <CEffectManager::hasEffect(EEFFECT_TYPE)>
  838f9f:	84 c0                	test   al,al
  838fa1:	0f 84 89 00 00 00    	je     839030 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x160>
  838fa7:	be 01 00 00 00       	mov    esi,0x1
  838fac:	48 89 df             	mov    rdi,rbx
  838faf:	e8 cc e0 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  838fb4:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  838fba:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  838fbf:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  838fc5:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  838fca:	48 89 84 24 20 02 00 00 	mov    QWORD PTR [rsp+0x220],rax
  838fd2:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  838fd6:	89 84 24 28 02 00 00 	mov    DWORD PTR [rsp+0x228],eax
  838fdd:	83 bb b4 04 00 00 08 	cmp    DWORD PTR [rbx+0x4b4],0x8
  838fe4:	0f 86 ee 04 00 00    	jbe    8394d8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x608>
  838fea:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  838ff1:	48 83 c0 40          	add    rax,0x40
  838ff5:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  838ff8:	48 8d b4 24 20 02 00 00 	lea    rsi,[rsp+0x220]
  839000:	e8 db e0 1a 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  839005:	83 bb b4 04 00 00 08 	cmp    DWORD PTR [rbx+0x4b4],0x8
  83900c:	0f 87 4e 06 00 00    	ja     839660 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x790>
  839012:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  839019:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  83901c:	e8 ff 15 1f 00       	call   a2a620 <CParticle::Start()>
  839021:	ba 01 00 00 00       	mov    edx,0x1
  839026:	31 f6                	xor    esi,esi
  839028:	48 89 df             	mov    rdi,rbx
  83902b:	e8 40 a2 fd ff       	call   813270 <CCharacter::setMeshVisible(bool, bool)>
  839030:	ba 01 00 00 00       	mov    edx,0x1
  839035:	be 05 00 00 00       	mov    esi,0x5
  83903a:	48 89 df             	mov    rdi,rbx
  83903d:	e8 9e 89 fd ff       	call   8119e0 <CCharacter::incrementJournalStatistic(EJournalStatistic, int)>
  839042:	80 bb 64 02 00 00 00 	cmp    BYTE PTR [rbx+0x264],0x0
  839049:	74 0a                	je     839055 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x185>
  83904b:	c7 83 78 02 00 00 00 00 20 41 	mov    DWORD PTR [rbx+0x278],0x41200000
  839055:	8b 83 84 00 00 00    	mov    eax,DWORD PTR [rbx+0x84]
  83905b:	80 bb 8d 01 00 00 00 	cmp    BYTE PTR [rbx+0x18d],0x0
  839062:	c6 83 64 02 00 00 00 	mov    BYTE PTR [rbx+0x264],0x0
  839069:	89 83 1c 02 00 00    	mov    DWORD PTR [rbx+0x21c],eax
  83906f:	8b 83 88 00 00 00    	mov    eax,DWORD PTR [rbx+0x88]
  839075:	89 83 20 02 00 00    	mov    DWORD PTR [rbx+0x220],eax
  83907b:	8b 83 8c 00 00 00    	mov    eax,DWORD PTR [rbx+0x8c]
  839081:	89 83 24 02 00 00    	mov    DWORD PTR [rbx+0x224],eax
  839087:	74 07                	je     839090 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1c0>
  839089:	c6 83 9c 01 00 00 00 	mov    BYTE PTR [rbx+0x19c],0x0
  839090:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  839093:	be 05 00 00 00       	mov    esi,0x5
  839098:	48 89 df             	mov    rdi,rbx
  83909b:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8390a1:	c7 83 78 03 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x378],0x0
  8390ab:	c7 83 80 03 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x380],0x0
  8390b5:	48 89 df             	mov    rdi,rbx
  8390b8:	c6 83 67 02 00 00 00 	mov    BYTE PTR [rbx+0x267],0x0
  8390bf:	e8 1c 67 fd ff       	call   80f7e0 <CCharacter::HP()>
  8390c4:	85 c0                	test   eax,eax
  8390c6:	7e 16                	jle    8390de <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x20e>
  8390c8:	48 89 df             	mov    rdi,rbx
  8390cb:	e8 10 67 fd ff       	call   80f7e0 <CCharacter::HP()>
  8390d0:	f7 d8                	neg    eax
  8390d2:	48 89 df             	mov    rdi,rbx
  8390d5:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8390d9:	e8 72 f9 ff ff       	call   838a50 <CCharacter::modifyHP(float)>
  8390de:	48 8b bb c8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1c8]
  8390e5:	48 85 ff             	test   rdi,rdi
  8390e8:	0f 84 fe 00 00 00    	je     8391ec <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x31c>
  8390ee:	31 c9                	xor    ecx,ecx
  8390f0:	ba 01 00 00 00       	mov    edx,0x1
  8390f5:	be 01 00 00 00       	mov    esi,0x1
  8390fa:	e8 c1 1c 49 00       	call   ccadc0 <CSkillManager::stopAllSkills(bool, bool, bool)>
  8390ff:	48 83 bb c8 01 00 00 00 	cmp    QWORD PTR [rbx+0x1c8],0x0
  839107:	0f 84 df 00 00 00    	je     8391ec <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x31c>
  83910d:	be 01 00 00 00       	mov    esi,0x1
  839112:	48 89 df             	mov    rdi,rbx
  839115:	4c 8b b3 40 03 00 00 	mov    r14,QWORD PTR [rbx+0x340]
  83911c:	e8 5f df 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  839121:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  839127:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83912c:	48 89 df             	mov    rdi,rbx
  83912f:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  839135:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83913a:	48 89 84 24 00 02 00 00 	mov    QWORD PTR [rsp+0x200],rax
  839142:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  839146:	89 84 24 08 02 00 00 	mov    DWORD PTR [rsp+0x208],eax
  83914d:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  839150:	ff 90 f0 00 00 00    	call   QWORD PTR [rax+0xf0]
  839156:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83915c:	48 8b 54 24 28       	mov    rdx,QWORD PTR [rsp+0x28]
  839161:	be 01 00 00 00       	mov    esi,0x1
  839166:	66 0f d6 4c 24 28    	movq   QWORD PTR [rsp+0x28],xmm1
  83916c:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  839171:	48 89 df             	mov    rdi,rbx
  839174:	48 89 54 24 70       	mov    QWORD PTR [rsp+0x70],rdx
  839179:	48 89 44 24 78       	mov    QWORD PTR [rsp+0x78],rax
  83917e:	48 89 94 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rdx
  839186:	48 89 84 24 88 00 00 00 	mov    QWORD PTR [rsp+0x88],rax
  83918e:	e8 ed de 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  839193:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  839199:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83919e:	48 8d 8c 24 10 02 00 00 	lea    rcx,[rsp+0x210]
  8391a6:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  8391ac:	4c 8d 8c 24 00 02 00 00 	lea    r9,[rsp+0x200]
  8391b4:	4c 8d 84 24 80 00 00 00 	lea    r8,[rsp+0x80]
  8391bc:	ba 03 00 00 00       	mov    edx,0x3
  8391c1:	48 89 de             	mov    rsi,rbx
  8391c4:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  8391c9:	48 89 84 24 10 02 00 00 	mov    QWORD PTR [rsp+0x210],rax
  8391d1:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  8391d5:	89 84 24 18 02 00 00 	mov    DWORD PTR [rsp+0x218],eax
  8391dc:	48 8b bb c8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1c8]
  8391e3:	4c 89 34 24          	mov    QWORD PTR [rsp],r14
  8391e7:	e8 74 c0 49 00       	call   cd5260 <CSkillManager::fireSkillsOnDeath(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&, Ogre::Quaternion const&, Ogre::Vector3 const&, CCharacter*)>
  8391ec:	48 89 df             	mov    rdi,rbx
  8391ef:	4c 89 e2             	mov    rdx,r12
  8391f2:	be 69 00 00 00       	mov    esi,0x69
  8391f7:	e8 34 75 fd ff       	call   810730 <CCharacter::executeProcs(EEFFECT_TYPE, CBaseUnit*)>
  8391fc:	31 ff                	xor    edi,edi
  8391fe:	48 83 7b 68 00       	cmp    QWORD PTR [rbx+0x68],0x0
  839203:	44 8b 35 82 23 cd 00 	mov    r14d,DWORD PTR [rip+0xcd2382]        # 150b58c <KSETTINGS_SHOW_BLOOD>
  83920a:	74 0c                	je     839218 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x348>
  83920c:	e8 7f b2 21 00       	call   a54490 <CMasterResourceManager::getSingleton()>
  839211:	48 8b b8 90 00 00 00 	mov    rdi,QWORD PTR [rax+0x90]
  839218:	44 89 f6             	mov    esi,r14d
  83921b:	e8 20 52 43 00       	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  839220:	83 f8 01             	cmp    eax,0x1
  839223:	41 0f 94 c7          	sete   r15b
  839227:	0f 84 03 02 00 00    	je     839430 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x560>
  83922d:	83 bb b4 04 00 00 04 	cmp    DWORD PTR [rbx+0x4b4],0x4
  839234:	0f 86 8e 02 00 00    	jbe    8394c8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x5f8>
  83923a:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  839241:	48 83 c0 20          	add    rax,0x20
  839245:	4c 8b 30             	mov    r14,QWORD PTR [rax]
  839248:	4d 85 f6             	test   r14,r14
  83924b:	74 17                	je     839264 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x394>
  83924d:	48 8d b3 10 02 00 00 	lea    rsi,[rbx+0x210]
  839254:	4c 89 f7             	mov    rdi,r14
  839257:	e8 84 de 1a 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  83925c:	4c 89 f7             	mov    rdi,r14
  83925f:	e8 bc 13 1f 00       	call   a2a620 <CParticle::Start()>
  839264:	44 8b 9b 40 07 00 00 	mov    r11d,DWORD PTR [rbx+0x740]
  83926b:	45 85 db             	test   r11d,r11d
  83926e:	0f 84 8c 00 00 00    	je     839300 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x430>
  839274:	45 31 f6             	xor    r14d,r14d
  839277:	eb 68                	jmp    8392e1 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x411>
  839279:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  839280:	48 8b 83 38 07 00 00 	mov    rax,QWORD PTR [rbx+0x738]
  839287:	48 8b 00             	mov    rax,QWORD PTR [rax]
  83928a:	80 78 20 00          	cmp    BYTE PTR [rax+0x20],0x0
  83928e:	74 44                	je     8392d4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x404>
  839290:	41 39 d6             	cmp    r14d,edx
  839293:	0f 82 17 02 00 00    	jb     8394b0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x5e0>
  839299:	48 8b 83 38 07 00 00 	mov    rax,QWORD PTR [rbx+0x738]
  8392a0:	48 8b 00             	mov    rax,QWORD PTR [rax]
  8392a3:	48 83 78 18 00       	cmp    QWORD PTR [rax+0x18],0x0
  8392a8:	74 2a                	je     8392d4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x404>
  8392aa:	41 39 d6             	cmp    r14d,edx
  8392ad:	0f 82 d5 01 00 00    	jb     839488 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x5b8>
  8392b3:	48 8b 83 38 07 00 00 	mov    rax,QWORD PTR [rbx+0x738]
  8392ba:	48 8b 00             	mov    rax,QWORD PTR [rax]
  8392bd:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  8392c1:	0f b6 b7 81 00 00 00 	movzx  esi,BYTE PTR [rdi+0x81]
  8392c8:	83 f6 01             	xor    esi,0x1
  8392cb:	40 0f b6 f6          	movzx  esi,sil
  8392cf:	e8 bc 0f 1f 00       	call   a2a290 <CParticle::Stop(bool)>
  8392d4:	41 83 c6 01          	add    r14d,0x1
  8392d8:	44 3b b3 40 07 00 00 	cmp    r14d,DWORD PTR [rbx+0x740]
  8392df:	73 1f                	jae    839300 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x430>
  8392e1:	8b 93 44 07 00 00    	mov    edx,DWORD PTR [rbx+0x744]
  8392e7:	41 39 d6             	cmp    r14d,edx
  8392ea:	73 94                	jae    839280 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x3b0>
  8392ec:	44 89 f0             	mov    eax,r14d
  8392ef:	48 c1 e0 03          	shl    rax,0x3
  8392f3:	48 03 83 38 07 00 00 	add    rax,QWORD PTR [rbx+0x738]
  8392fa:	eb 8b                	jmp    839287 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x3b7>
  8392fc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  839300:	48 8b bb 98 02 00 00 	mov    rdi,QWORD PTR [rbx+0x298]
  839307:	48 85 ff             	test   rdi,rdi
  83930a:	74 16                	je     839322 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x452>
  83930c:	0f 57 c9             	xorps  xmm1,xmm1
  83930f:	48 8b 53 58          	mov    rdx,QWORD PTR [rbx+0x58]
  839313:	31 c9                	xor    ecx,ecx
  839315:	be 0c 00 00 00       	mov    esi,0xc
  83931a:	0f 28 c1             	movaps xmm0,xmm1
  83931d:	e8 7e 05 23 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  839322:	31 f6                	xor    esi,esi
  839324:	48 89 df             	mov    rdi,rbx
  839327:	48 c7 83 90 03 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x390],0x0
  839332:	e8 d9 bf fe ff       	call   825310 <CCharacter::setTarget(CCharacter*)>
  839337:	48 8b bb 70 06 00 00 	mov    rdi,QWORD PTR [rbx+0x670]
  83933e:	48 85 ff             	test   rdi,rdi
  839341:	74 0c                	je     83934f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x47f>
  839343:	e8 78 e2 44 00       	call   c875c0 <CPath::Clear()>
  839348:	c6 83 80 06 00 00 00 	mov    BYTE PTR [rbx+0x680],0x0
  83934f:	45 31 f6             	xor    r14d,r14d
  839352:	48 83 bb b8 01 00 00 00 	cmp    QWORD PTR [rbx+0x1b8],0x0
  83935a:	74 1e                	je     83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83935c:	be 1c 00 00 00       	mov    esi,0x1c
  839361:	48 89 df             	mov    rdi,rbx
  839364:	e8 37 cf fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  839369:	84 c0                	test   al,al
  83936b:	75 0d                	jne    83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83936d:	80 bb 02 07 00 00 00 	cmp    BYTE PTR [rbx+0x702],0x0
  839374:	0f 84 a5 0c 00 00    	je     83a01f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x114f>
  83937a:	31 ed                	xor    ebp,ebp
  83937c:	4d 85 ed             	test   r13,r13
  83937f:	74 12                	je     839393 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4c3>
  839381:	0f 57 c9             	xorps  xmm1,xmm1
  839384:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  83938a:	0f 2e c1             	ucomiss xmm0,xmm1
  83938d:	0f 87 dd 02 00 00    	ja     839670 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x7a0>
  839393:	48 8d ac 24 40 02 00 00 	lea    rbp,[rsp+0x240]
  83939b:	48 8d 94 24 13 03 00 00 	lea    rdx,[rsp+0x313]
  8393a3:	be 8c 99 fc 00       	mov    esi,0xfc998c
  8393a8:	48 89 ef             	mov    rdi,rbp
  8393ab:	e8 48 cf d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8393b0:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8393b7:	48 89 ee             	mov    rsi,rbp
  8393ba:	e8 51 af 06 00       	call   8a4310 <CGenericModel::animationExistsSubstring(std::string const&) const>
  8393bf:	48 89 ef             	mov    rdi,rbp
  8393c2:	41 89 c5             	mov    r13d,eax
  8393c5:	e8 be ce d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8393ca:	45 84 ed             	test   r13b,r13b
  8393cd:	0f 85 11 01 00 00    	jne    8394e4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x614>
  8393d3:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8393da:	e8 b1 c2 06 00       	call   8a5690 <CGenericModel::clearAnimations()>
  8393df:	90                   	nop
  8393e0:	be 1c 00 00 00       	mov    esi,0x1c
  8393e5:	48 89 df             	mov    rdi,rbx
  8393e8:	e8 b3 ce fb ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8393ed:	84 c0                	test   al,al
  8393ef:	0f 84 53 01 00 00    	je     839548 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x678>
  8393f5:	be 01 00 00 00       	mov    esi,0x1
  8393fa:	48 89 df             	mov    rdi,rbx
  8393fd:	e8 7e d6 fb ff       	call   7f6a80 <CBaseUnit::broadcastUnitState(EUNIT_STATES)>
  839402:	48 89 df             	mov    rdi,rbx
  839405:	e8 96 d5 fb ff       	call   7f69a0 <CBaseUnit::broadcastKilled()>
  83940a:	48 89 d9             	mov    rcx,rbx
  83940d:	4c 89 e2             	mov    rdx,r12
  839410:	be 01 00 00 00       	mov    esi,0x1
  839415:	48 89 df             	mov    rdi,rbx
  839418:	e8 93 d6 fb ff       	call   7f6ab0 <CBaseUnit::questEventFire(EQUEST_EVENTS, CCharacter*, CBaseUnit*)>
  83941d:	48 81 c4 28 03 00 00 	add    rsp,0x328
  839424:	5b                   	pop    rbx
  839425:	5d                   	pop    rbp
  839426:	41 5c                	pop    r12
  839428:	41 5d                	pop    r13
  83942a:	41 5e                	pop    r14
  83942c:	41 5f                	pop    r15
  83942e:	c3                   	ret
  83942f:	90                   	nop
  839430:	83 bb b4 04 00 00 03 	cmp    DWORD PTR [rbx+0x4b4],0x3
  839437:	0f 86 8b 00 00 00    	jbe    8394c8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x5f8>
  83943d:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  839444:	48 83 c0 18          	add    rax,0x18
  839448:	e9 f8 fd ff ff       	jmp    839245 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x375>
  83944d:	0f 1f 00             	nop    DWORD PTR [rax]
  839450:	4c 8d b4 24 f0 02 00 00 	lea    r14,[rsp+0x2f0]
  839458:	48 8d 94 24 1e 03 00 00 	lea    rdx,[rsp+0x31e]
  839460:	be f0 9c fc 00       	mov    esi,0xfc9cf0
  839465:	4c 89 f7             	mov    rdi,r14
  839468:	e8 eb c9 d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  83946d:	4c 89 f6             	mov    rsi,r14
  839470:	48 89 df             	mov    rdi,rbx
  839473:	e8 e8 68 fc ff       	call   7ffd60 <CBaseUnit::removeUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  839478:	4c 89 f7             	mov    rdi,r14
  83947b:	e8 58 b4 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  839480:	e9 f2 fa ff ff       	jmp    838f77 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xa7>
  839485:	0f 1f 00             	nop    DWORD PTR [rax]
  839488:	48 8b 83 38 07 00 00 	mov    rax,QWORD PTR [rbx+0x738]
  83948f:	44 89 f2             	mov    edx,r14d
  839492:	48 8b 04 d0          	mov    rax,QWORD PTR [rax+rdx*8]
  839496:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  83949a:	0f b6 b7 81 00 00 00 	movzx  esi,BYTE PTR [rdi+0x81]
  8394a1:	83 f6 01             	xor    esi,0x1
  8394a4:	40 0f b6 f6          	movzx  esi,sil
  8394a8:	e9 22 fe ff ff       	jmp    8392cf <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x3ff>
  8394ad:	0f 1f 00             	nop    DWORD PTR [rax]
  8394b0:	44 89 f0             	mov    eax,r14d
  8394b3:	48 c1 e0 03          	shl    rax,0x3
  8394b7:	48 03 83 38 07 00 00 	add    rax,QWORD PTR [rbx+0x738]
  8394be:	e9 dd fd ff ff       	jmp    8392a0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x3d0>
  8394c3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8394c8:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  8394cf:	e9 71 fd ff ff       	jmp    839245 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x375>
  8394d4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8394d8:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  8394df:	e9 11 fb ff ff       	jmp    838ff5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x125>
  8394e4:	48 8d ac 24 30 02 00 00 	lea    rbp,[rsp+0x230]
  8394ec:	48 8d 94 24 12 03 00 00 	lea    rdx,[rsp+0x312]
  8394f4:	be 8c 99 fc 00       	mov    esi,0xfc998c
  8394f9:	48 89 ef             	mov    rdi,rbp
  8394fc:	e8 f7 cd d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  839501:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  839508:	48 89 ee             	mov    rsi,rbp
  83950b:	e8 d0 98 06 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  839510:	f3 0f 10 15 48 f2 76 00 	movss  xmm2,DWORD PTR [rip+0x76f248]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  839518:	31 d2                	xor    edx,edx
  83951a:	f3 0f 10 0d da b2 76 00 	movss  xmm1,DWORD PTR [rip+0x76b2da]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  839522:	89 c6                	mov    esi,eax
  839524:	f3 0f 10 05 bc f1 76 00 	movss  xmm0,DWORD PTR [rip+0x76f1bc]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  83952c:	48 89 df             	mov    rdi,rbx
  83952f:	e8 fc 7b fd ff       	call   811130 <CCharacter::blendAnimation(int, bool, float, float, float)>
  839534:	48 89 ef             	mov    rdi,rbp
  839537:	e8 4c cd d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  83953c:	e9 9f fe ff ff       	jmp    8393e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x510>
  839541:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  839548:	48 89 df             	mov    rdi,rbx
  83954b:	e8 20 6c fd ff       	call   810170 <CCharacter::alignment()>
  839550:	83 f8 01             	cmp    eax,0x1
  839553:	0f 84 9c fe ff ff    	je     8393f5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x525>
  839559:	4d 85 e4             	test   r12,r12
  83955c:	0f 84 93 fe ff ff    	je     8393f5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x525>
  839562:	80 bb 04 07 00 00 00 	cmp    BYTE PTR [rbx+0x704],0x0
  839569:	0f 85 86 fe ff ff    	jne    8393f5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x525>
  83956f:	48 83 bb c0 06 00 00 00 	cmp    QWORD PTR [rbx+0x6c0],0x0
  839577:	0f 84 95 11 00 00    	je     83a712 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1842>
  83957d:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  839581:	31 ed                	xor    ebp,ebp
  839583:	48 85 c0             	test   rax,rax
  839586:	74 04                	je     83958c <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x6bc>
  839588:	48 8b 68 18          	mov    rbp,QWORD PTR [rax+0x18]
  83958c:	be 01 00 00 00       	mov    esi,0x1
  839591:	48 89 df             	mov    rdi,rbx
  839594:	e8 e7 da 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  839599:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83959f:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  8395a4:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  8395aa:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  8395af:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  8395b7:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  8395bb:	89 84 24 a8 00 00 00 	mov    DWORD PTR [rsp+0xa8],eax
  8395c2:	8b b3 cc 06 00 00    	mov    esi,DWORD PTR [rbx+0x6cc]
  8395c8:	8b bb c8 06 00 00    	mov    edi,DWORD PTR [rbx+0x6c8]
  8395ce:	e8 1d 96 45 00       	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8395d3:	48 8b b3 c0 06 00 00 	mov    rsi,QWORD PTR [rbx+0x6c0]
  8395da:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8395de:	48 8d 8c 24 a0 00 00 00 	lea    rcx,[rsp+0xa0]
  8395e6:	89 c2                	mov    edx,eax
  8395e8:	49 89 d9             	mov    r9,rbx
  8395eb:	49 89 e8             	mov    r8,rbp
  8395ee:	c7 44 24 08 ff ff ff ff 	mov    DWORD PTR [rsp+0x8],0xffffffff
  8395f6:	4c 89 24 24          	mov    QWORD PTR [rsp],r12
  8395fa:	e8 91 fc 53 00       	call   d79290 <CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int, Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int)>
  8395ff:	48 89 df             	mov    rdi,rbx
  839602:	be 01 00 00 00       	mov    esi,0x1
  839607:	e8 74 da 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83960c:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  839612:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  839617:	31 ff                	xor    edi,edi
  839619:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83961f:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  839624:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  83962c:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  839630:	89 84 24 98 00 00 00 	mov    DWORD PTR [rsp+0x98],eax
  839637:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  83963b:	48 85 c0             	test   rax,rax
  83963e:	74 04                	je     839644 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x774>
  839640:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  839644:	48 8d 8c 24 90 00 00 00 	lea    rcx,[rsp+0x90]
  83964c:	45 31 c0             	xor    r8d,r8d
  83964f:	48 89 da             	mov    rdx,rbx
  839652:	4c 89 e6             	mov    rsi,r12
  839655:	e8 16 38 12 00       	call   95ce70 <CLevel::rollMoney(CCharacter*, CCharacter*, Ogre::Vector3 const&, bool)>
  83965a:	e9 96 fd ff ff       	jmp    8393f5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x525>
  83965f:	90                   	nop
  839660:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  839667:	48 83 c0 40          	add    rax,0x40
  83966b:	e9 a9 f9 ff ff       	jmp    839019 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x149>
  839670:	4c 8d b4 24 a0 02 00 00 	lea    r14,[rsp+0x2a0]
  839678:	48 8d 94 24 19 03 00 00 	lea    rdx,[rsp+0x319]
  839680:	be 74 99 fc 00       	mov    esi,0xfc9974
  839685:	4c 89 f7             	mov    rdi,r14
  839688:	e8 6b cc d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  83968d:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  839694:	4c 89 f6             	mov    rsi,r14
  839697:	bd 01 00 00 00       	mov    ebp,0x1
  83969c:	e8 1f 8f 06 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  8396a1:	84 c0                	test   al,al
  8396a3:	4c 89 f7             	mov    rdi,r14
  8396a6:	40 0f 95 c5          	setne  bpl
  8396aa:	e8 d9 cb d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8396af:	40 84 ed             	test   bpl,bpl
  8396b2:	0f 84 db fc ff ff    	je     839393 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4c3>
  8396b8:	48 83 bb 70 06 00 00 00 	cmp    QWORD PTR [rbx+0x670],0x0
  8396c0:	0f 84 07 0d 00 00    	je     83a3cd <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x14fd>
  8396c6:	48 8b bb 70 06 00 00 	mov    rdi,QWORD PTR [rbx+0x670]
  8396cd:	c6 83 80 06 00 00 01 	mov    BYTE PTR [rbx+0x680],0x1
  8396d4:	c7 83 78 06 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x678],0x0
  8396de:	e8 dd de 44 00       	call   c875c0 <CPath::Clear()>
  8396e3:	be 01 00 00 00       	mov    esi,0x1
  8396e8:	48 89 df             	mov    rdi,rbx
  8396eb:	e8 90 d9 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8396f0:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  8396f6:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  8396fb:	48 c7 84 24 88 02 00 00 00 00 00 00 	mov    QWORD PTR [rsp+0x288],0x0
  839707:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83970d:	8b 54 24 78          	mov    edx,DWORD PTR [rsp+0x78]
  839711:	48 8d bc 24 40 01 00 00 	lea    rdi,[rsp+0x140]
  839719:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  83971f:	48 8d b4 24 30 01 00 00 	lea    rsi,[rsp+0x130]
  839727:	48 89 84 24 50 01 00 00 	mov    QWORD PTR [rsp+0x150],rax
  83972f:	89 94 24 58 01 00 00 	mov    DWORD PTR [rsp+0x158],edx
  839736:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83973b:	48 89 84 24 a0 01 00 00 	mov    QWORD PTR [rsp+0x1a0],rax
  839743:	89 94 24 a8 01 00 00 	mov    DWORD PTR [rsp+0x1a8],edx
  83974a:	f3 0f 10 54 24 60    	movss  xmm2,DWORD PTR [rsp+0x60]
  839750:	f3 41 0f 59 45 04    	mulss  xmm0,DWORD PTR [r13+0x4]
  839756:	f3 41 0f 59 55 00    	mulss  xmm2,DWORD PTR [r13+0x0]
  83975c:	f3 0f 10 4c 24 60    	movss  xmm1,DWORD PTR [rsp+0x60]
  839762:	f3 41 0f 59 4d 08    	mulss  xmm1,DWORD PTR [r13+0x8]
  839768:	48 89 84 24 40 01 00 00 	mov    QWORD PTR [rsp+0x140],rax
  839770:	48 89 84 24 30 01 00 00 	mov    QWORD PTR [rsp+0x130],rax
  839778:	89 94 24 48 01 00 00 	mov    DWORD PTR [rsp+0x148],edx
  83977f:	89 94 24 38 01 00 00 	mov    DWORD PTR [rsp+0x138],edx
  839786:	f3 0f 58 84 24 54 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x154]
  83978f:	f3 0f 58 94 24 50 01 00 00 	addss  xmm2,DWORD PTR [rsp+0x150]
  839798:	f3 0f 58 8c 24 58 01 00 00 	addss  xmm1,DWORD PTR [rsp+0x158]
  8397a1:	f3 0f 11 84 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm0
  8397aa:	f3 0f 11 94 24 50 01 00 00 	movss  DWORD PTR [rsp+0x150],xmm2
  8397b3:	f3 0f 11 8c 24 58 01 00 00 	movss  DWORD PTR [rsp+0x158],xmm1
  8397bc:	f3 0f 7e 84 24 50 01 00 00 	movq   xmm0,QWORD PTR [rsp+0x150]
  8397c5:	e8 86 00 44 00       	call   c79850 <MATH::expandBounds(Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3)>
  8397ca:	f3 0f 10 83 94 01 00 00 	movss  xmm0,DWORD PTR [rbx+0x194]
  8397d2:	31 ff                	xor    edi,edi
  8397d4:	f3 0f 10 0d 8c ad 78 00 	movss  xmm1,DWORD PTR [rip+0x78ad8c]        # fc4568 <typeinfo for CEditor+0x18>
  8397dc:	f3 0f 59 c8          	mulss  xmm1,xmm0
  8397e0:	f3 0f 10 94 24 40 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x140]
  8397e9:	f3 0f 58 c0          	addss  xmm0,xmm0
  8397ed:	f3 0f 58 d1          	addss  xmm2,xmm1
  8397f1:	f3 0f 11 94 24 40 01 00 00 	movss  DWORD PTR [rsp+0x140],xmm2
  8397fa:	f3 0f 10 94 24 44 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x144]
  839803:	f3 0f 58 d1          	addss  xmm2,xmm1
  839807:	f3 0f 58 8c 24 48 01 00 00 	addss  xmm1,DWORD PTR [rsp+0x148]
  839810:	f3 0f 11 94 24 44 01 00 00 	movss  DWORD PTR [rsp+0x144],xmm2
  839819:	f3 0f 11 8c 24 48 01 00 00 	movss  DWORD PTR [rsp+0x148],xmm1
  839822:	f3 0f 10 8c 24 30 01 00 00 	movss  xmm1,DWORD PTR [rsp+0x130]
  83982b:	f3 0f 58 c8          	addss  xmm1,xmm0
  83982f:	f3 0f 11 8c 24 30 01 00 00 	movss  DWORD PTR [rsp+0x130],xmm1
  839838:	f3 0f 10 8c 24 34 01 00 00 	movss  xmm1,DWORD PTR [rsp+0x134]
  839841:	f3 0f 58 c8          	addss  xmm1,xmm0
  839845:	f3 0f 58 84 24 38 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x138]
  83984e:	f3 0f 11 8c 24 34 01 00 00 	movss  DWORD PTR [rsp+0x134],xmm1
  839857:	f3 0f 11 84 24 38 01 00 00 	movss  DWORD PTR [rsp+0x138],xmm0
  839860:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  839864:	48 85 c0             	test   rax,rax
  839867:	74 04                	je     83986d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x99d>
  839869:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  83986d:	48 8d 94 24 30 01 00 00 	lea    rdx,[rsp+0x130]
  839875:	48 8d b4 24 40 01 00 00 	lea    rsi,[rsp+0x140]
  83987d:	e8 3e 46 11 00       	call   94dec0 <CLevel::sortForCollision(Ogre::Vector3 const&, Ogre::Vector3 const&)>
  839882:	0f 57 c9             	xorps  xmm1,xmm1
  839885:	31 ff                	xor    edi,edi
  839887:	f3 0f 10 05 35 4c 79 00 	movss  xmm0,DWORD PTR [rip+0x794c35]        # fce4c4 <vtable for iInventoryListener+0x84>
  83988f:	f3 0f 10 94 24 54 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x154]
  839898:	0f 57 db             	xorps  xmm3,xmm3
  83989b:	f3 0f 58 8c 24 50 01 00 00 	addss  xmm1,DWORD PTR [rsp+0x150]
  8398a4:	f3 0f 58 d0          	addss  xmm2,xmm0
  8398a8:	f3 0f 58 9c 24 58 01 00 00 	addss  xmm3,DWORD PTR [rsp+0x158]
  8398b1:	f3 0f 58 84 24 a4 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x1a4]
  8398ba:	f3 0f 11 94 24 14 01 00 00 	movss  DWORD PTR [rsp+0x114],xmm2
  8398c3:	0f 57 d2             	xorps  xmm2,xmm2
  8398c6:	f3 0f 11 8c 24 10 01 00 00 	movss  DWORD PTR [rsp+0x110],xmm1
  8398cf:	0f 57 c9             	xorps  xmm1,xmm1
  8398d2:	f3 0f 58 94 24 a8 01 00 00 	addss  xmm2,DWORD PTR [rsp+0x1a8]
  8398db:	f3 0f 11 9c 24 18 01 00 00 	movss  DWORD PTR [rsp+0x118],xmm3
  8398e4:	f3 0f 58 8c 24 a0 01 00 00 	addss  xmm1,DWORD PTR [rsp+0x1a0]
  8398ed:	f3 0f 11 84 24 24 01 00 00 	movss  DWORD PTR [rsp+0x124],xmm0
  8398f6:	f3 0f 11 94 24 28 01 00 00 	movss  DWORD PTR [rsp+0x128],xmm2
  8398ff:	f3 0f 11 8c 24 20 01 00 00 	movss  DWORD PTR [rsp+0x120],xmm1
  839908:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  83990c:	48 85 c0             	test   rax,rax
  83990f:	74 04                	je     839915 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xa45>
  839911:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  839915:	48 8d 84 24 88 02 00 00 	lea    rax,[rsp+0x288]
  83991d:	48 8d 8c 24 70 01 00 00 	lea    rcx,[rsp+0x170]
  839925:	48 8d 94 24 10 01 00 00 	lea    rdx,[rsp+0x110]
  83992d:	48 8d b4 24 20 01 00 00 	lea    rsi,[rsp+0x120]
  839935:	4c 8d b4 24 60 01 00 00 	lea    r14,[rsp+0x160]
  83993d:	4c 8d bc 24 08 03 00 00 	lea    r15,[rsp+0x308]
  839945:	4c 8d 8c 24 80 01 00 00 	lea    r9,[rsp+0x180]
  83994d:	4c 8d 84 24 90 01 00 00 	lea    r8,[rsp+0x190]
  839955:	c7 44 24 18 00 00 00 00 	mov    DWORD PTR [rsp+0x18],0x0
  83995d:	f3 0f 10 05 cb ae 76 00 	movss  xmm0,DWORD PTR [rip+0x76aecb]        # fa4830 <vtable for Ogre::FrameListener+0x70>
  839965:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  83996a:	4c 89 74 24 08       	mov    QWORD PTR [rsp+0x8],r14
  83996f:	4c 89 3c 24          	mov    QWORD PTR [rsp],r15
  839973:	e8 c8 f1 10 00       	call   948b40 <CLevel::preSortedSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, CBaseUnit**, bool)>
  839978:	84 c0                	test   al,al
  83997a:	c6 44 24 6f 00       	mov    BYTE PTR [rsp+0x6f],0x0
  83997f:	74 21                	je     8399a2 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xad2>
  839981:	8b 84 24 70 01 00 00 	mov    eax,DWORD PTR [rsp+0x170]
  839988:	c6 44 24 6f 01       	mov    BYTE PTR [rsp+0x6f],0x1
  83998d:	89 84 24 50 01 00 00 	mov    DWORD PTR [rsp+0x150],eax
  839994:	8b 84 24 78 01 00 00 	mov    eax,DWORD PTR [rsp+0x178]
  83999b:	89 84 24 58 01 00 00 	mov    DWORD PTR [rsp+0x158],eax
  8399a2:	c6 83 81 06 00 00 01 	mov    BYTE PTR [rbx+0x681],0x1
  8399a9:	80 3d 20 4e c4 00 00 	cmp    BYTE PTR [rip+0xc44e20],0x0        # 147e7d0 <guard variable for CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors>
  8399b0:	0f 84 b2 05 00 00    	je     839f68 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1098>
  8399b6:	8b 84 24 54 01 00 00 	mov    eax,DWORD PTR [rsp+0x154]
  8399bd:	f3 0f 10 9c 24 50 01 00 00 	movss  xmm3,DWORD PTR [rsp+0x150]
  8399c6:	f3 0f 10 84 24 58 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x158]
  8399cf:	31 ed                	xor    ebp,ebp
  8399d1:	f3 0f 10 0d c7 4a 79 00 	movss  xmm1,DWORD PTR [rip+0x794ac7]        # fce4a0 <vtable for iInventoryListener+0x60>
  8399d9:	f3 0f 11 5c 24 64    	movss  DWORD PTR [rsp+0x64],xmm3
  8399df:	89 84 24 04 01 00 00 	mov    DWORD PTR [rsp+0x104],eax
  8399e6:	f3 0f 11 44 24 60    	movss  DWORD PTR [rsp+0x60],xmm0
  8399ec:	f3 0f 11 9c 24 00 01 00 00 	movss  DWORD PTR [rsp+0x100],xmm3
  8399f5:	f3 0f 11 84 24 08 01 00 00 	movss  DWORD PTR [rsp+0x108],xmm0
  8399fe:	f3 0f 11 4c 24 68    	movss  DWORD PTR [rsp+0x68],xmm1
  839a04:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  839a0a:	c7 84 24 04 01 00 00 00 00 c8 42 	mov    DWORD PTR [rsp+0x104],0x42c80000
  839a15:	f3 0f 10 4c 24 64    	movss  xmm1,DWORD PTR [rsp+0x64]
  839a1b:	f3 0f 58 85 e8 e7 47 01 	addss  xmm0,DWORD PTR [rbp+0x147e7e8]
  839a23:	f3 0f 58 8d e0 e7 47 01 	addss  xmm1,DWORD PTR [rbp+0x147e7e0]
  839a2b:	c7 84 24 f4 00 00 00 00 00 c8 c2 	mov    DWORD PTR [rsp+0xf4],0xc2c80000
  839a36:	31 ff                	xor    edi,edi
  839a38:	f3 0f 11 84 24 08 01 00 00 	movss  DWORD PTR [rsp+0x108],xmm0
  839a41:	f3 0f 11 8c 24 00 01 00 00 	movss  DWORD PTR [rsp+0x100],xmm1
  839a4a:	f3 0f 11 8c 24 f0 00 00 00 	movss  DWORD PTR [rsp+0xf0],xmm1
  839a53:	f3 0f 11 84 24 f8 00 00 00 	movss  DWORD PTR [rsp+0xf8],xmm0
  839a5c:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  839a60:	48 85 c0             	test   rax,rax
  839a63:	74 04                	je     839a69 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xb99>
  839a65:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  839a69:	4c 8d 84 24 80 01 00 00 	lea    r8,[rsp+0x180]
  839a71:	48 8d 8c 24 90 01 00 00 	lea    rcx,[rsp+0x190]
  839a79:	48 8d 94 24 f0 00 00 00 	lea    rdx,[rsp+0xf0]
  839a81:	48 8d b4 24 00 01 00 00 	lea    rsi,[rsp+0x100]
  839a89:	4d 89 f9             	mov    r9,r15
  839a8c:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  839a94:	4c 89 34 24          	mov    QWORD PTR [rsp],r14
  839a98:	e8 b3 47 11 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  839a9d:	84 c0                	test   al,al
  839a9f:	0f 84 fc 03 00 00    	je     839ea1 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xfd1>
  839aa5:	f3 0f 10 94 24 a4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1a4]
  839aae:	0f 28 c2             	movaps xmm0,xmm2
  839ab1:	f3 0f 10 8c 24 94 01 00 00 	movss  xmm1,DWORD PTR [rsp+0x194]
  839aba:	f3 0f 10 1d a6 ec 76 00 	movss  xmm3,DWORD PTR [rip+0x76eca6]        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  839ac2:	f3 0f 5c c1          	subss  xmm0,xmm1
  839ac6:	0f 2e d8             	ucomiss xmm3,xmm0
  839ac9:	76 58                	jbe    839b23 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc53>
  839acb:	0f 2e 44 24 68       	ucomiss xmm0,DWORD PTR [rsp+0x68]
  839ad0:	76 51                	jbe    839b23 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc53>
  839ad2:	0f 57 e4             	xorps  xmm4,xmm4
  839ad5:	f3 0f 10 9b 94 01 00 00 	movss  xmm3,DWORD PTR [rbx+0x194]
  839add:	f3 0f 10 ac 24 98 01 00 00 	movss  xmm5,DWORD PTR [rsp+0x198]
  839ae6:	f3 0f 58 cb          	addss  xmm1,xmm3
  839aea:	f3 0f 59 e3          	mulss  xmm4,xmm3
  839aee:	f3 0f 11 8c 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm1
  839af7:	f3 0f 58 ec          	addss  xmm5,xmm4
  839afb:	f3 0f 58 a4 24 90 01 00 00 	addss  xmm4,DWORD PTR [rsp+0x190]
  839b04:	f3 0f 11 ac 24 58 01 00 00 	movss  DWORD PTR [rsp+0x158],xmm5
  839b0d:	f3 0f 11 a4 24 50 01 00 00 	movss  DWORD PTR [rsp+0x150],xmm4
  839b16:	c6 83 81 06 00 00 00 	mov    BYTE PTR [rbx+0x681],0x0
  839b1d:	f3 0f 11 44 24 68    	movss  DWORD PTR [rsp+0x68],xmm0
  839b23:	48 83 c5 0c          	add    rbp,0xc
  839b27:	48 83 fd 3c          	cmp    rbp,0x3c
  839b2b:	0f 85 d3 fe ff ff    	jne    839a04 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xb34>
  839b31:	80 bb 81 06 00 00 00 	cmp    BYTE PTR [rbx+0x681],0x0
  839b38:	0f 85 73 03 00 00    	jne    839eb1 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xfe1>
  839b3e:	80 7c 24 6f 00       	cmp    BYTE PTR [rsp+0x6f],0x0
  839b43:	0f 84 f8 08 00 00    	je     83a441 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1571>
  839b49:	f3 0f 10 9c 24 58 01 00 00 	movss  xmm3,DWORD PTR [rsp+0x158]
  839b52:	f3 0f 10 a4 24 50 01 00 00 	movss  xmm4,DWORD PTR [rsp+0x150]
  839b5b:	f3 0f 5c 9c 24 a8 01 00 00 	subss  xmm3,DWORD PTR [rsp+0x1a8]
  839b64:	f3 0f 10 05 a4 ac 76 00 	movss  xmm0,DWORD PTR [rip+0x76aca4]        # fa4810 <vtable for Ogre::FrameListener+0x50>
  839b6c:	f3 0f 5c a4 24 a0 01 00 00 	subss  xmm4,DWORD PTR [rsp+0x1a0]
  839b75:	f3 0f 10 0d ab 49 79 00 	movss  xmm1,DWORD PTR [rip+0x7949ab]        # fce528 <vtable for iInventoryListener+0xe8>
  839b7d:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  839b83:	f3 0f 59 d8          	mulss  xmm3,xmm0
  839b87:	f3 0f 59 e0          	mulss  xmm4,xmm0
  839b8b:	0f 57 c0             	xorps  xmm0,xmm0
  839b8e:	f3 0f 58 9c 24 a8 01 00 00 	addss  xmm3,DWORD PTR [rsp+0x1a8]
  839b97:	f3 0f 58 a4 24 a0 01 00 00 	addss  xmm4,DWORD PTR [rsp+0x1a0]
  839ba0:	f3 0f 58 c2          	addss  xmm0,xmm2
  839ba4:	f3 0f 11 84 24 d4 00 00 00 	movss  DWORD PTR [rsp+0xd4],xmm0
  839bad:	f3 0f 10 05 6f ac 76 00 	movss  xmm0,DWORD PTR [rip+0x76ac6f]        # fa4824 <vtable for Ogre::FrameListener+0x64>
  839bb5:	f3 0f 11 a4 24 d0 00 00 00 	movss  DWORD PTR [rsp+0xd0],xmm4
  839bbe:	f3 0f 11 9c 24 d8 00 00 00 	movss  DWORD PTR [rsp+0xd8],xmm3
  839bc7:	e8 84 8f 45 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  839bcc:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  839bd2:	48 8d b4 24 a0 01 00 00 	lea    rsi,[rsp+0x1a0]
  839bda:	f3 0f 58 c2          	addss  xmm0,xmm2
  839bde:	f3 0f 10 0d 92 eb 76 00 	movss  xmm1,DWORD PTR [rip+0x76eb92]        # fa8778 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xd8>
  839be6:	f3 0f 11 84 24 d4 00 00 00 	movss  DWORD PTR [rsp+0xd4],xmm0
  839bef:	48 8b bb 70 06 00 00 	mov    rdi,QWORD PTR [rbx+0x670]
  839bf6:	f3 0f 10 05 d6 48 79 00 	movss  xmm0,DWORD PTR [rip+0x7948d6]        # fce4d4 <vtable for iInventoryListener+0x94>
  839bfe:	e8 8d f1 44 00       	call   c88d90 <CPath::AddPoint(Ogre::Vector3 const&, float, float)>
  839c03:	48 8b bb 70 06 00 00 	mov    rdi,QWORD PTR [rbx+0x670]
  839c0a:	48 8d b4 24 d0 00 00 00 	lea    rsi,[rsp+0xd0]
  839c12:	f3 0f 10 0d 5e eb 76 00 	movss  xmm1,DWORD PTR [rip+0x76eb5e]        # fa8778 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xd8>
  839c1a:	f3 0f 10 05 b2 48 79 00 	movss  xmm0,DWORD PTR [rip+0x7948b2]        # fce4d4 <vtable for iInventoryListener+0x94>
  839c22:	e8 69 f1 44 00       	call   c88d90 <CPath::AddPoint(Ogre::Vector3 const&, float, float)>
  839c27:	48 8b bb 70 06 00 00 	mov    rdi,QWORD PTR [rbx+0x670]
  839c2e:	48 8d b4 24 50 01 00 00 	lea    rsi,[rsp+0x150]
  839c36:	f3 0f 10 05 96 48 79 00 	movss  xmm0,DWORD PTR [rip+0x794896]        # fce4d4 <vtable for iInventoryListener+0x94>
  839c3e:	f3 0f 10 0d 32 eb 76 00 	movss  xmm1,DWORD PTR [rip+0x76eb32]        # fa8778 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xd8>
  839c46:	e8 45 f1 44 00       	call   c88d90 <CPath::AddPoint(Ogre::Vector3 const&, float, float)>
  839c4b:	f3 0f 10 05 8d ea 76 00 	movss  xmm0,DWORD PTR [rip+0x76ea8d]        # fa86e0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x40>
  839c53:	48 8b 83 70 06 00 00 	mov    rax,QWORD PTR [rbx+0x670]
  839c5a:	f3 0f 11 83 7c 06 00 00 	movss  DWORD PTR [rbx+0x67c],xmm0
  839c62:	f3 0f 10 15 fe ea 76 00 	movss  xmm2,DWORD PTR [rip+0x76eafe]        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  839c6a:	f3 0f 5e 50 18       	divss  xmm2,DWORD PTR [rax+0x18]
  839c6f:	b8 00 00 10 41       	mov    eax,0x41100000
  839c74:	f3 0f 59 d0          	mulss  xmm2,xmm0
  839c78:	0f 2e 15 69 48 79 00 	ucomiss xmm2,DWORD PTR [rip+0x794869]        # fce4e8 <vtable for iInventoryListener+0xa8>
  839c7f:	f3 0f 11 93 7c 06 00 00 	movss  DWORD PTR [rbx+0x67c],xmm2
  839c87:	0f 83 73 02 00 00    	jae    839f00 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1030>
  839c8d:	0f 8a 6d 02 00 00    	jp     839f00 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1030>
  839c93:	89 83 7c 06 00 00    	mov    DWORD PTR [rbx+0x67c],eax
  839c99:	89 44 24 24          	mov    DWORD PTR [rsp+0x24],eax
  839c9d:	f3 0f 10 54 24 24    	movss  xmm2,DWORD PTR [rsp+0x24]
  839ca3:	80 bb 81 06 00 00 00 	cmp    BYTE PTR [rbx+0x681],0x0
  839caa:	0f 85 38 02 00 00    	jne    839ee8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1018>
  839cb0:	f3 0f 10 93 7c 06 00 00 	movss  xmm2,DWORD PTR [rbx+0x67c]
  839cb8:	0f 57 c0             	xorps  xmm0,xmm0
  839cbb:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  839cc1:	f3 0f 10 0d 5b ab 76 00 	movss  xmm1,DWORD PTR [rip+0x76ab5b]        # fa4824 <vtable for Ogre::FrameListener+0x64>
  839cc9:	48 8d ac 24 80 02 00 00 	lea    rbp,[rsp+0x280]
  839cd1:	e8 7a 8e 45 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  839cd6:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  839cdc:	48 8d 94 24 17 03 00 00 	lea    rdx,[rsp+0x317]
  839ce4:	f3 0f 58 c2          	addss  xmm0,xmm2
  839ce8:	be 74 99 fc 00       	mov    esi,0xfc9974
  839ced:	48 89 ef             	mov    rdi,rbp
  839cf0:	f3 0f 11 83 7c 06 00 00 	movss  DWORD PTR [rbx+0x67c],xmm0
  839cf8:	e8 fb c5 d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  839cfd:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  839d04:	48 89 ee             	mov    rsi,rbp
  839d07:	e8 44 8a 06 00       	call   8a2750 <CGenericModel::getAnimationLengthSeconds(std::string const&) const>
  839d0c:	48 8b bc 24 80 02 00 00 	mov    rdi,QWORD PTR [rsp+0x280]
  839d14:	48 83 ef 18          	sub    rdi,0x18
  839d18:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  839d1f:	0f 85 1a 0b 00 00    	jne    83a83f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x196f>
  839d25:	48 8b 83 70 06 00 00 	mov    rax,QWORD PTR [rbx+0x670]
  839d2c:	48 8d ac 24 70 02 00 00 	lea    rbp,[rsp+0x270]
  839d34:	48 8d 94 24 16 03 00 00 	lea    rdx,[rsp+0x316]
  839d3c:	be 74 99 fc 00       	mov    esi,0xfc9974
  839d41:	48 89 ef             	mov    rdi,rbp
  839d44:	f3 0f 10 48 18       	movss  xmm1,DWORD PTR [rax+0x18]
  839d49:	f3 0f 5e 8b 7c 06 00 00 	divss  xmm1,DWORD PTR [rbx+0x67c]
  839d51:	f3 0f 5e c1          	divss  xmm0,xmm1
  839d55:	f3 0f 11 44 24 60    	movss  DWORD PTR [rsp+0x60],xmm0
  839d5b:	e8 98 c5 d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  839d60:	f3 0f 10 15 f8 e9 76 00 	movss  xmm2,DWORD PTR [rip+0x76e9f8]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  839d68:	31 d2                	xor    edx,edx
  839d6a:	f3 0f 10 4c 24 60    	movss  xmm1,DWORD PTR [rsp+0x60]
  839d70:	48 89 ee             	mov    rsi,rbp
  839d73:	f3 0f 10 05 61 47 79 00 	movss  xmm0,DWORD PTR [rip+0x794761]        # fce4dc <vtable for iInventoryListener+0x9c>
  839d7b:	48 89 df             	mov    rdi,rbx
  839d7e:	e8 ad 8a fd ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  839d83:	48 8b bc 24 70 02 00 00 	mov    rdi,QWORD PTR [rsp+0x270]
  839d8b:	b8 20 3a 42 01       	mov    eax,0x1423a20
  839d90:	48 83 ef 18          	sub    rdi,0x18
  839d94:	48 39 f8             	cmp    rax,rdi
  839d97:	0f 85 25 0a 00 00    	jne    83a7c2 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18f2>
  839d9d:	80 bb 81 06 00 00 00 	cmp    BYTE PTR [rbx+0x681],0x0
  839da4:	0f 84 76 01 00 00    	je     839f20 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1050>
  839daa:	4d 85 e4             	test   r12,r12
  839dad:	0f 84 2d f6 ff ff    	je     8393e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x510>
  839db3:	4c 89 e7             	mov    rdi,r12
  839db6:	e8 f5 0e 02 00       	call   85acb0 <CBaseUnit::isPlayer()>
  839dbb:	84 c0                	test   al,al
  839dbd:	0f 84 1d f6 ff ff    	je     8393e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x510>
  839dc3:	4c 8d ac 24 50 02 00 00 	lea    r13,[rsp+0x250]
  839dcb:	48 8d 94 24 14 03 00 00 	lea    rdx,[rsp+0x314]
  839dd3:	be e4 7f fa 00       	mov    esi,0xfa7fe4
  839dd8:	4c 89 ef             	mov    rdi,r13
  839ddb:	e8 78 c0 d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  839de0:	bf a0 00 00 00       	mov    edi,0xa0
  839de5:	e8 d6 0e 02 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  839dea:	f3 0f 7e 83 9c 00 00 00 	movq   xmm0,QWORD PTR [rbx+0x9c]
  839df2:	4c 89 ee             	mov    rsi,r13
  839df5:	f3 0f 10 15 eb e8 76 00 	movss  xmm2,DWORD PTR [rip+0x76e8eb]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  839dfd:	48 89 c7             	mov    rdi,rax
  839e00:	f3 0f 10 8b a4 00 00 00 	movss  xmm1,DWORD PTR [rbx+0xa4]
  839e08:	48 89 c5             	mov    rbp,rax
  839e0b:	e8 e0 eb 4b 00       	call   cf89f0 <CCameraShake::CCameraShake(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, Ogre::Vector3, float)>
  839e10:	4c 89 ef             	mov    rdi,r13
  839e13:	e8 c0 aa d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  839e18:	be 01 00 00 00       	mov    esi,0x1
  839e1d:	48 89 df             	mov    rdi,rbx
  839e20:	c7 45 60 00 00 00 3f 	mov    DWORD PTR [rbp+0x60],0x3f000000
  839e27:	e8 54 d2 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  839e2c:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  839e32:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  839e37:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  839e3d:	48 89 84 24 c0 00 00 00 	mov    QWORD PTR [rsp+0xc0],rax
  839e45:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  839e4a:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  839e4e:	89 84 24 c8 00 00 00 	mov    DWORD PTR [rsp+0xc8],eax
  839e55:	8b 84 24 c0 00 00 00 	mov    eax,DWORD PTR [rsp+0xc0]
  839e5c:	89 85 8c 00 00 00    	mov    DWORD PTR [rbp+0x8c],eax
  839e62:	8b 84 24 c4 00 00 00 	mov    eax,DWORD PTR [rsp+0xc4]
  839e69:	89 85 90 00 00 00    	mov    DWORD PTR [rbp+0x90],eax
  839e6f:	8b 84 24 c8 00 00 00 	mov    eax,DWORD PTR [rsp+0xc8]
  839e76:	c6 85 98 00 00 00 01 	mov    BYTE PTR [rbp+0x98],0x1
  839e7d:	89 85 94 00 00 00    	mov    DWORD PTR [rbp+0x94],eax
  839e83:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  839e87:	e8 d4 58 53 00       	call   d6f760 <CResourceManager::getCameraControl()>
  839e8c:	ba 01 00 00 00       	mov    edx,0x1
  839e91:	48 89 ee             	mov    rsi,rbp
  839e94:	48 89 c7             	mov    rdi,rax
  839e97:	e8 34 12 02 00       	call   85b0d0 <CCameraControl::addCameraShake(CCameraShake*, bool)>
  839e9c:	e9 3f f5 ff ff       	jmp    8393e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x510>
  839ea1:	c6 83 81 06 00 00 01 	mov    BYTE PTR [rbx+0x681],0x1
  839ea8:	f3 0f 10 94 24 a4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1a4]
  839eb1:	f3 0f 10 84 24 54 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x154]
  839eba:	f3 0f 5c 05 0e e8 76 00 	subss  xmm0,DWORD PTR [rip+0x76e80e]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  839ec2:	f3 0f 10 9c 24 58 01 00 00 	movss  xmm3,DWORD PTR [rsp+0x158]
  839ecb:	f3 0f 10 a4 24 50 01 00 00 	movss  xmm4,DWORD PTR [rsp+0x150]
  839ed4:	f3 0f 11 84 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm0
  839edd:	e9 79 fc ff ff       	jmp    839b5b <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc8b>
  839ee2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  839ee8:	f3 0f 59 15 a8 45 79 00 	mulss  xmm2,DWORD PTR [rip+0x7945a8]        # fce498 <vtable for iInventoryListener+0x58>
  839ef0:	f3 0f 11 93 7c 06 00 00 	movss  DWORD PTR [rbx+0x67c],xmm2
  839ef8:	e9 bb fd ff ff       	jmp    839cb8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xde8>
  839efd:	0f 1f 00             	nop    DWORD PTR [rax]
  839f00:	0f 2e 15 25 46 79 00 	ucomiss xmm2,DWORD PTR [rip+0x794625]        # fce52c <vtable for iInventoryListener+0xec>
  839f07:	0f 86 96 fd ff ff    	jbe    839ca3 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xdd3>
  839f0d:	b8 00 00 40 41       	mov    eax,0x41400000
  839f12:	e9 7c fd ff ff       	jmp    839c93 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xdc3>
  839f17:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  839f20:	48 8d ac 24 60 02 00 00 	lea    rbp,[rsp+0x260]
  839f28:	48 8d 94 24 15 03 00 00 	lea    rdx,[rsp+0x315]
  839f30:	be 81 99 fc 00       	mov    esi,0xfc9981
  839f35:	48 89 ef             	mov    rdi,rbp
  839f38:	e8 bb c3 d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  839f3d:	0f 57 c0             	xorps  xmm0,xmm0
  839f40:	31 d2                	xor    edx,edx
  839f42:	f3 0f 10 0d b2 a8 76 00 	movss  xmm1,DWORD PTR [rip+0x76a8b2]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  839f4a:	48 89 ee             	mov    rsi,rbp
  839f4d:	48 89 df             	mov    rdi,rbx
  839f50:	e8 2b 5e fd ff       	call   80fd80 <CCharacter::queueBlendAnimation(std::string const&, bool, float, float)>
  839f55:	48 89 ef             	mov    rdi,rbp
  839f58:	e8 2b c3 d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  839f5d:	e9 48 fe ff ff       	jmp    839daa <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xeda>
  839f62:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  839f68:	bf d0 e7 47 01       	mov    edi,0x147e7d0
  839f6d:	e8 e6 95 d1 ff       	call   553558 <__cxa_guard_acquire@plt>
  839f72:	85 c0                	test   eax,eax
  839f74:	0f 84 3c fa ff ff    	je     8399b6 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xae6>
  839f7a:	bf d0 e7 47 01       	mov    edi,0x147e7d0
  839f7f:	c7 05 57 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44857],0x0        # 147e7e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors>
  839f89:	c7 05 51 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44851],0x0        # 147e7e4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x4>
  839f93:	c7 05 4b 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc4484b],0x0        # 147e7e8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x8>
  839f9d:	c7 05 45 48 c4 00 00 00 80 3e 	mov    DWORD PTR [rip+0xc44845],0x3e800000        # 147e7ec <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0xc>
  839fa7:	c7 05 3f 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc4483f],0x0        # 147e7f0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x10>
  839fb1:	c7 05 39 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44839],0x0        # 147e7f4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x14>
  839fbb:	c7 05 33 48 c4 00 00 00 80 be 	mov    DWORD PTR [rip+0xc44833],0xbe800000        # 147e7f8 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x18>
  839fc5:	c7 05 2d 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc4482d],0x0        # 147e7fc <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x1c>
  839fcf:	c7 05 27 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44827],0x0        # 147e800 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x20>
  839fd9:	c7 05 21 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44821],0x0        # 147e804 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x24>
  839fe3:	c7 05 1b 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc4481b],0x0        # 147e808 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x28>
  839fed:	c7 05 15 48 c4 00 00 00 80 3e 	mov    DWORD PTR [rip+0xc44815],0x3e800000        # 147e80c <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x2c>
  839ff7:	c7 05 0f 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc4480f],0x0        # 147e810 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x30>
  83a001:	c7 05 09 48 c4 00 00 00 00 00 	mov    DWORD PTR [rip+0xc44809],0x0        # 147e814 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x34>
  83a00b:	c7 05 03 48 c4 00 00 00 80 be 	mov    DWORD PTR [rip+0xc44803],0xbe800000        # 147e818 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)::KDropVectors+0x38>
  83a015:	e8 ae 9f d1 ff       	call   553fc8 <__cxa_guard_release@plt>
  83a01a:	e9 97 f9 ff ff       	jmp    8399b6 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xae6>
  83a01f:	48 8d 94 24 1d 03 00 00 	lea    rdx,[rsp+0x31d]
  83a027:	48 8d bc 24 e0 02 00 00 	lea    rdi,[rsp+0x2e0]
  83a02f:	be 98 9a fc 00       	mov    esi,0xfc9a98
  83a034:	e8 1f be d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  83a039:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  83a040:	48 8d b4 24 e0 02 00 00 	lea    rsi,[rsp+0x2e0]
  83a048:	41 be 01 00 00 00    	mov    r14d,0x1
  83a04e:	e8 1d 8b fb ff       	call   7f2b70 <CEffectManager::getAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  83a053:	48 85 c0             	test   rax,rax
  83a056:	0f 84 13 07 00 00    	je     83a76f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x189f>
  83a05c:	41 be 01 00 00 00    	mov    r14d,0x1
  83a062:	48 8d bc 24 e0 02 00 00 	lea    rdi,[rsp+0x2e0]
  83a06a:	e8 69 a8 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a06f:	45 84 f6             	test   r14b,r14b
  83a072:	0f 84 02 f3 ff ff    	je     83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83a078:	48 8d ac 24 d0 02 00 00 	lea    rbp,[rsp+0x2d0]
  83a080:	48 8d 94 24 1c 03 00 00 	lea    rdx,[rsp+0x31c]
  83a088:	be 98 9a fc 00       	mov    esi,0xfc9a98
  83a08d:	48 89 ef             	mov    rdi,rbp
  83a090:	e8 c3 bd d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  83a095:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  83a09c:	48 89 ee             	mov    rsi,rbp
  83a09f:	e8 cc 8a fb ff       	call   7f2b70 <CEffectManager::getAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  83a0a4:	48 89 ef             	mov    rdi,rbp
  83a0a7:	49 89 c6             	mov    r14,rax
  83a0aa:	e8 29 a8 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a0af:	4d 85 f6             	test   r14,r14
  83a0b2:	0f 84 b2 01 00 00    	je     83a26a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x139a>
  83a0b8:	be 01 00 00 00       	mov    esi,0x1
  83a0bd:	48 89 df             	mov    rdi,rbx
  83a0c0:	e8 bb cf 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83a0c5:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83a0cb:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83a0d0:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83a0d6:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83a0db:	48 89 84 24 f0 01 00 00 	mov    QWORD PTR [rsp+0x1f0],rax
  83a0e3:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  83a0e7:	89 84 24 f8 01 00 00 	mov    DWORD PTR [rsp+0x1f8],eax
  83a0ee:	83 bb b4 04 00 00 09 	cmp    DWORD PTR [rbx+0x4b4],0x9
  83a0f5:	0f 87 5f 01 00 00    	ja     83a25a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x138a>
  83a0fb:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a102:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  83a105:	48 8d b4 24 f0 01 00 00 	lea    rsi,[rsp+0x1f0]
  83a10d:	e8 ce cf 1a 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  83a112:	83 bb b4 04 00 00 09 	cmp    DWORD PTR [rbx+0x4b4],0x9
  83a119:	0f 87 2b 01 00 00    	ja     83a24a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x137a>
  83a11f:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a126:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  83a129:	4c 8d ac 24 c0 02 00 00 	lea    r13,[rsp+0x2c0]
  83a131:	e8 ea 04 1f 00       	call   a2a620 <CParticle::Start()>
  83a136:	48 8d 94 24 1b 03 00 00 	lea    rdx,[rsp+0x31b]
  83a13e:	be 78 a3 fc 00       	mov    esi,0xfca378
  83a143:	4c 89 ef             	mov    rdi,r13
  83a146:	e8 0d bd d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  83a14b:	bf a0 00 00 00       	mov    edi,0xa0
  83a150:	e8 6b 0b 02 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  83a155:	f3 0f 7e 83 9c 00 00 00 	movq   xmm0,QWORD PTR [rbx+0x9c]
  83a15d:	4c 89 ee             	mov    rsi,r13
  83a160:	f3 0f 10 15 80 e5 76 00 	movss  xmm2,DWORD PTR [rip+0x76e580]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  83a168:	48 89 c7             	mov    rdi,rax
  83a16b:	f3 0f 10 8b a4 00 00 00 	movss  xmm1,DWORD PTR [rbx+0xa4]
  83a173:	48 89 c5             	mov    rbp,rax
  83a176:	e8 75 e8 4b 00       	call   cf89f0 <CCameraShake::CCameraShake(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, Ogre::Vector3, float)>
  83a17b:	4c 89 ef             	mov    rdi,r13
  83a17e:	e8 55 a7 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a183:	c6 85 99 00 00 00 01 	mov    BYTE PTR [rbp+0x99],0x1
  83a18a:	be 01 00 00 00       	mov    esi,0x1
  83a18f:	48 89 df             	mov    rdi,rbx
  83a192:	e8 e9 ce 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83a197:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83a19d:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83a1a2:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83a1a8:	48 89 84 24 e0 01 00 00 	mov    QWORD PTR [rsp+0x1e0],rax
  83a1b0:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83a1b5:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  83a1b9:	89 84 24 e8 01 00 00 	mov    DWORD PTR [rsp+0x1e8],eax
  83a1c0:	8b 84 24 e0 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e0]
  83a1c7:	89 85 8c 00 00 00    	mov    DWORD PTR [rbp+0x8c],eax
  83a1cd:	8b 84 24 e4 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e4]
  83a1d4:	89 85 90 00 00 00    	mov    DWORD PTR [rbp+0x90],eax
  83a1da:	8b 84 24 e8 01 00 00 	mov    eax,DWORD PTR [rsp+0x1e8]
  83a1e1:	89 85 94 00 00 00    	mov    DWORD PTR [rbp+0x94],eax
  83a1e7:	c6 85 98 00 00 00 01 	mov    BYTE PTR [rbp+0x98],0x1
  83a1ee:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  83a1f2:	e8 69 55 53 00       	call   d6f760 <CResourceManager::getCameraControl()>
  83a1f7:	ba 01 00 00 00       	mov    edx,0x1
  83a1fc:	48 89 c7             	mov    rdi,rax
  83a1ff:	48 89 ee             	mov    rsi,rbp
  83a202:	e8 c9 0e 02 00       	call   85b0d0 <CCameraControl::addCameraShake(CCameraShake*, bool)>
  83a207:	31 f6                	xor    esi,esi
  83a209:	48 89 df             	mov    rdi,rbx
  83a20c:	ba 01 00 00 00       	mov    edx,0x1
  83a211:	e8 3a 87 fd ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  83a216:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  83a21d:	48 85 ff             	test   rdi,rdi
  83a220:	74 05                	je     83a227 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1357>
  83a222:	e8 69 b4 06 00       	call   8a5690 <CGenericModel::clearAnimations()>
  83a227:	c6 83 0d 07 00 00 01 	mov    BYTE PTR [rbx+0x70d],0x1
  83a22e:	e8 fd 41 69 00       	call   ece430 <CSteamStats::getSingleton()>
  83a233:	ba 01 00 00 00       	mov    edx,0x1
  83a238:	be 18 00 00 00       	mov    esi,0x18
  83a23d:	48 89 c7             	mov    rdi,rax
  83a240:	e8 fb 40 69 00       	call   ece340 <CSteamStats::incrementStat(ESTATS, int)>
  83a245:	e9 96 f1 ff ff       	jmp    8393e0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x510>
  83a24a:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a251:	48 83 c0 48          	add    rax,0x48
  83a255:	e9 cc fe ff ff       	jmp    83a126 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1256>
  83a25a:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a261:	48 83 c0 48          	add    rax,0x48
  83a265:	e9 98 fe ff ff       	jmp    83a102 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1232>
  83a26a:	8b 93 b4 04 00 00    	mov    edx,DWORD PTR [rbx+0x4b4]
  83a270:	83 fa 0a             	cmp    edx,0xa
  83a273:	0f 87 5b 04 00 00    	ja     83a6d4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1804>
  83a279:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a280:	48 89 c1             	mov    rcx,rax
  83a283:	48 83 39 00          	cmp    QWORD PTR [rcx],0x0
  83a287:	0f 84 ed f0 ff ff    	je     83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83a28d:	45 84 ff             	test   r15b,r15b
  83a290:	0f 84 e4 f0 ff ff    	je     83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83a296:	48 8d 48 50          	lea    rcx,[rax+0x50]
  83a29a:	83 fa 0a             	cmp    edx,0xa
  83a29d:	48 0f 46 c8          	cmovbe rcx,rax
  83a2a1:	48 8b 29             	mov    rbp,QWORD PTR [rcx]
  83a2a4:	48 85 ed             	test   rbp,rbp
  83a2a7:	0f 84 cd f0 ff ff    	je     83937a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x4aa>
  83a2ad:	be 01 00 00 00       	mov    esi,0x1
  83a2b2:	48 89 df             	mov    rdi,rbx
  83a2b5:	4c 8d ac 24 b0 02 00 00 	lea    r13,[rsp+0x2b0]
  83a2bd:	e8 be cd 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83a2c2:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83a2c8:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83a2cd:	48 8d b4 24 d0 01 00 00 	lea    rsi,[rsp+0x1d0]
  83a2d5:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83a2db:	48 89 ef             	mov    rdi,rbp
  83a2de:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83a2e3:	48 89 84 24 d0 01 00 00 	mov    QWORD PTR [rsp+0x1d0],rax
  83a2eb:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  83a2ef:	89 84 24 d8 01 00 00 	mov    DWORD PTR [rsp+0x1d8],eax
  83a2f6:	e8 e5 cd 1a 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  83a2fb:	48 89 ef             	mov    rdi,rbp
  83a2fe:	e8 1d 03 1f 00       	call   a2a620 <CParticle::Start()>
  83a303:	48 8d 94 24 1a 03 00 00 	lea    rdx,[rsp+0x31a]
  83a30b:	be b8 a3 fc 00       	mov    esi,0xfca3b8
  83a310:	4c 89 ef             	mov    rdi,r13
  83a313:	e8 40 bb d1 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  83a318:	bf a0 00 00 00       	mov    edi,0xa0
  83a31d:	e8 9e 09 02 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  83a322:	f3 0f 7e 83 9c 00 00 00 	movq   xmm0,QWORD PTR [rbx+0x9c]
  83a32a:	4c 89 ee             	mov    rsi,r13
  83a32d:	f3 0f 10 15 a3 e3 76 00 	movss  xmm2,DWORD PTR [rip+0x76e3a3]        # fa86d8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x38>
  83a335:	48 89 c7             	mov    rdi,rax
  83a338:	f3 0f 10 8b a4 00 00 00 	movss  xmm1,DWORD PTR [rbx+0xa4]
  83a340:	48 89 c5             	mov    rbp,rax
  83a343:	e8 a8 e6 4b 00       	call   cf89f0 <CCameraShake::CCameraShake(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, Ogre::Vector3, float)>
  83a348:	4c 89 ef             	mov    rdi,r13
  83a34b:	e8 88 a5 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a350:	f3 0f 10 0d 1c c4 78 00 	movss  xmm1,DWORD PTR [rip+0x78c41c]        # fc6774 <typeinfo name for iCollision+0x24>
  83a358:	f3 0f 10 05 b0 a4 76 00 	movss  xmm0,DWORD PTR [rip+0x76a4b0]        # fa4810 <vtable for Ogre::FrameListener+0x50>
  83a360:	e8 eb 87 45 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  83a365:	f3 0f 11 45 60       	movss  DWORD PTR [rbp+0x60],xmm0
  83a36a:	c6 85 99 00 00 00 01 	mov    BYTE PTR [rbp+0x99],0x1
  83a371:	be 01 00 00 00       	mov    esi,0x1
  83a376:	48 89 df             	mov    rdi,rbx
  83a379:	e8 02 cd 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83a37e:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83a384:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83a389:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83a38f:	48 89 84 24 c0 01 00 00 	mov    QWORD PTR [rsp+0x1c0],rax
  83a397:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83a39c:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  83a3a0:	89 84 24 c8 01 00 00 	mov    DWORD PTR [rsp+0x1c8],eax
  83a3a7:	8b 84 24 c0 01 00 00 	mov    eax,DWORD PTR [rsp+0x1c0]
  83a3ae:	89 85 8c 00 00 00    	mov    DWORD PTR [rbp+0x8c],eax
  83a3b4:	8b 84 24 c4 01 00 00 	mov    eax,DWORD PTR [rsp+0x1c4]
  83a3bb:	89 85 90 00 00 00    	mov    DWORD PTR [rbp+0x90],eax
  83a3c1:	8b 84 24 c8 01 00 00 	mov    eax,DWORD PTR [rsp+0x1c8]
  83a3c8:	e9 14 fe ff ff       	jmp    83a1e1 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1311>
  83a3cd:	48 8d ac 24 90 02 00 00 	lea    rbp,[rsp+0x290]
  83a3d5:	48 8d 94 24 18 03 00 00 	lea    rdx,[rsp+0x318]
  83a3dd:	be 49 99 fc 00       	mov    esi,0xfc9949
  83a3e2:	48 89 ef             	mov    rdi,rbp
  83a3e5:	e8 0e bf d1 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  83a3ea:	bf c8 00 00 00       	mov    edi,0xc8
  83a3ef:	c7 84 24 b0 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x1b0],0x0
  83a3fa:	c7 84 24 b4 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x1b4],0x0
  83a405:	c7 84 24 b8 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x1b8],0x0
  83a410:	e8 ab 08 02 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  83a415:	48 8d 8c 24 b0 01 00 00 	lea    rcx,[rsp+0x1b0]
  83a41d:	31 d2                	xor    edx,edx
  83a41f:	48 89 ee             	mov    rsi,rbp
  83a422:	48 89 c7             	mov    rdi,rax
  83a425:	49 89 c6             	mov    r14,rax
  83a428:	e8 23 f1 44 00       	call   c89550 <CPath::CPath(std::string, bool, Ogre::Vector3 const&)>
  83a42d:	4c 89 b3 70 06 00 00 	mov    QWORD PTR [rbx+0x670],r14
  83a434:	48 89 ef             	mov    rdi,rbp
  83a437:	e8 4c be d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  83a43c:	e9 85 f2 ff ff       	jmp    8396c6 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x7f6>
  83a441:	f3 0f 10 0d 87 e2 76 00 	movss  xmm1,DWORD PTR [rip+0x76e287]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  83a449:	8b 84 24 a8 01 00 00 	mov    eax,DWORD PTR [rsp+0x1a8]
  83a450:	f3 41 0f 59 4d 04    	mulss  xmm1,DWORD PTR [r13+0x4]
  83a456:	f3 0f 10 25 72 e2 76 00 	movss  xmm4,DWORD PTR [rip+0x76e272]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  83a45e:	f3 41 0f 59 65 00    	mulss  xmm4,DWORD PTR [r13+0x0]
  83a464:	f3 0f 10 1d 64 e2 76 00 	movss  xmm3,DWORD PTR [rip+0x76e264]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  83a46c:	f3 0f 10 84 24 a0 01 00 00 	movss  xmm0,DWORD PTR [rsp+0x1a0]
  83a475:	48 8d bc 24 40 01 00 00 	lea    rdi,[rsp+0x140]
  83a47d:	48 8d b4 24 30 01 00 00 	lea    rsi,[rsp+0x130]
  83a485:	f3 0f 58 8c 24 a4 01 00 00 	addss  xmm1,DWORD PTR [rsp+0x1a4]
  83a48e:	f3 0f 58 e0          	addss  xmm4,xmm0
  83a492:	f3 0f 11 4c 24 60    	movss  DWORD PTR [rsp+0x60],xmm1
  83a498:	f3 41 0f 59 5d 08    	mulss  xmm3,DWORD PTR [r13+0x8]
  83a49e:	f3 0f 11 8c 24 e4 00 00 00 	movss  DWORD PTR [rsp+0xe4],xmm1
  83a4a7:	f3 0f 11 a4 24 e0 00 00 00 	movss  DWORD PTR [rsp+0xe0],xmm4
  83a4b0:	89 84 24 48 01 00 00 	mov    DWORD PTR [rsp+0x148],eax
  83a4b7:	89 84 24 38 01 00 00 	mov    DWORD PTR [rsp+0x138],eax
  83a4be:	f3 0f 11 84 24 40 01 00 00 	movss  DWORD PTR [rsp+0x140],xmm0
  83a4c7:	f3 0f 11 84 24 30 01 00 00 	movss  DWORD PTR [rsp+0x130],xmm0
  83a4d0:	f3 0f 7e 84 24 e0 00 00 00 	movq   xmm0,QWORD PTR [rsp+0xe0]
  83a4d9:	f3 0f 11 94 24 44 01 00 00 	movss  DWORD PTR [rsp+0x144],xmm2
  83a4e2:	f3 0f 58 9c 24 a8 01 00 00 	addss  xmm3,DWORD PTR [rsp+0x1a8]
  83a4eb:	f3 0f 11 94 24 34 01 00 00 	movss  DWORD PTR [rsp+0x134],xmm2
  83a4f4:	f3 0f 11 64 24 30    	movss  DWORD PTR [rsp+0x30],xmm4
  83a4fa:	0f 28 cb             	movaps xmm1,xmm3
  83a4fd:	f3 0f 11 9c 24 e8 00 00 00 	movss  DWORD PTR [rsp+0xe8],xmm3
  83a506:	f3 0f 11 5c 24 40    	movss  DWORD PTR [rsp+0x40],xmm3
  83a50c:	e8 3f f3 43 00       	call   c79850 <MATH::expandBounds(Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3)>
  83a511:	f3 0f 10 8b 94 01 00 00 	movss  xmm1,DWORD PTR [rbx+0x194]
  83a519:	31 ff                	xor    edi,edi
  83a51b:	f3 0f 10 05 45 a0 78 00 	movss  xmm0,DWORD PTR [rip+0x78a045]        # fc4568 <typeinfo for CEditor+0x18>
  83a523:	f3 0f 59 c1          	mulss  xmm0,xmm1
  83a527:	f3 0f 10 94 24 40 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x140]
  83a530:	f3 0f 10 5c 24 40    	movss  xmm3,DWORD PTR [rsp+0x40]
  83a536:	f3 0f 10 64 24 30    	movss  xmm4,DWORD PTR [rsp+0x30]
  83a53c:	f3 0f 58 d0          	addss  xmm2,xmm0
  83a540:	f3 0f 11 94 24 40 01 00 00 	movss  DWORD PTR [rsp+0x140],xmm2
  83a549:	f3 0f 10 94 24 44 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x144]
  83a552:	f3 0f 58 d0          	addss  xmm2,xmm0
  83a556:	f3 0f 58 84 24 48 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x148]
  83a55f:	f3 0f 11 94 24 44 01 00 00 	movss  DWORD PTR [rsp+0x144],xmm2
  83a568:	f3 0f 11 84 24 48 01 00 00 	movss  DWORD PTR [rsp+0x148],xmm0
  83a571:	0f 28 c1             	movaps xmm0,xmm1
  83a574:	f3 0f 58 c1          	addss  xmm0,xmm1
  83a578:	f3 0f 10 8c 24 30 01 00 00 	movss  xmm1,DWORD PTR [rsp+0x130]
  83a581:	f3 0f 58 c8          	addss  xmm1,xmm0
  83a585:	f3 0f 11 8c 24 30 01 00 00 	movss  DWORD PTR [rsp+0x130],xmm1
  83a58e:	f3 0f 10 8c 24 34 01 00 00 	movss  xmm1,DWORD PTR [rsp+0x134]
  83a597:	f3 0f 58 c8          	addss  xmm1,xmm0
  83a59b:	f3 0f 58 84 24 38 01 00 00 	addss  xmm0,DWORD PTR [rsp+0x138]
  83a5a4:	f3 0f 11 8c 24 34 01 00 00 	movss  DWORD PTR [rsp+0x134],xmm1
  83a5ad:	f3 0f 11 84 24 38 01 00 00 	movss  DWORD PTR [rsp+0x138],xmm0
  83a5b6:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  83a5ba:	48 85 c0             	test   rax,rax
  83a5bd:	74 04                	je     83a5c3 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x16f3>
  83a5bf:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  83a5c3:	48 8d 94 24 30 01 00 00 	lea    rdx,[rsp+0x130]
  83a5cb:	48 8d b4 24 40 01 00 00 	lea    rsi,[rsp+0x140]
  83a5d3:	f3 0f 11 5c 24 40    	movss  DWORD PTR [rsp+0x40],xmm3
  83a5d9:	f3 0f 11 64 24 30    	movss  DWORD PTR [rsp+0x30],xmm4
  83a5df:	e8 dc 38 11 00       	call   94dec0 <CLevel::sortForCollision(Ogre::Vector3 const&, Ogre::Vector3 const&)>
  83a5e4:	f3 0f 10 64 24 30    	movss  xmm4,DWORD PTR [rsp+0x30]
  83a5ea:	31 ff                	xor    edi,edi
  83a5ec:	f3 0f 10 5c 24 40    	movss  xmm3,DWORD PTR [rsp+0x40]
  83a5f2:	c7 84 24 04 01 00 00 00 00 c8 42 	mov    DWORD PTR [rsp+0x104],0x42c80000
  83a5fd:	f3 0f 11 a4 24 00 01 00 00 	movss  DWORD PTR [rsp+0x100],xmm4
  83a606:	c7 84 24 f4 00 00 00 00 00 c8 c2 	mov    DWORD PTR [rsp+0xf4],0xc2c80000
  83a611:	f3 0f 11 9c 24 08 01 00 00 	movss  DWORD PTR [rsp+0x108],xmm3
  83a61a:	f3 0f 11 a4 24 f0 00 00 00 	movss  DWORD PTR [rsp+0xf0],xmm4
  83a623:	f3 0f 11 9c 24 f8 00 00 00 	movss  DWORD PTR [rsp+0xf8],xmm3
  83a62c:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  83a630:	c6 83 81 06 00 00 01 	mov    BYTE PTR [rbx+0x681],0x1
  83a637:	48 85 c0             	test   rax,rax
  83a63a:	74 04                	je     83a640 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1770>
  83a63c:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  83a640:	4c 8d 84 24 80 01 00 00 	lea    r8,[rsp+0x180]
  83a648:	48 8d 8c 24 90 01 00 00 	lea    rcx,[rsp+0x190]
  83a650:	48 8d 94 24 f0 00 00 00 	lea    rdx,[rsp+0xf0]
  83a658:	48 8d b4 24 00 01 00 00 	lea    rsi,[rsp+0x100]
  83a660:	4d 89 f9             	mov    r9,r15
  83a663:	f3 0f 11 5c 24 40    	movss  DWORD PTR [rsp+0x40],xmm3
  83a669:	f3 0f 11 64 24 30    	movss  DWORD PTR [rsp+0x30],xmm4
  83a66f:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  83a677:	4c 89 34 24          	mov    QWORD PTR [rsp],r14
  83a67b:	e8 d0 3b 11 00       	call   94e250 <CLevel::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool)>
  83a680:	84 c0                	test   al,al
  83a682:	f3 0f 10 5c 24 40    	movss  xmm3,DWORD PTR [rsp+0x40]
  83a688:	f3 0f 10 64 24 30    	movss  xmm4,DWORD PTR [rsp+0x30]
  83a68e:	75 54                	jne    83a6e4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1814>
  83a690:	f3 0f 10 94 24 a4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1a4]
  83a699:	80 bb 81 06 00 00 00 	cmp    BYTE PTR [rbx+0x681],0x0
  83a6a0:	0f 84 a3 f4 ff ff    	je     839b49 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc79>
  83a6a6:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  83a6ac:	f3 0f 5c 05 1c e0 76 00 	subss  xmm0,DWORD PTR [rip+0x76e01c]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  83a6b4:	f3 0f 11 a4 24 50 01 00 00 	movss  DWORD PTR [rsp+0x150],xmm4
  83a6bd:	f3 0f 11 9c 24 58 01 00 00 	movss  DWORD PTR [rsp+0x158],xmm3
  83a6c6:	f3 0f 11 84 24 54 01 00 00 	movss  DWORD PTR [rsp+0x154],xmm0
  83a6cf:	e9 87 f4 ff ff       	jmp    839b5b <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc8b>
  83a6d4:	48 8b 83 a8 04 00 00 	mov    rax,QWORD PTR [rbx+0x4a8]
  83a6db:	48 8d 48 50          	lea    rcx,[rax+0x50]
  83a6df:	e9 9f fb ff ff       	jmp    83a283 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x13b3>
  83a6e4:	f3 0f 10 94 24 a4 01 00 00 	movss  xmm2,DWORD PTR [rsp+0x1a4]
  83a6ed:	0f 28 c2             	movaps xmm0,xmm2
  83a6f0:	f3 0f 10 0d 70 e0 76 00 	movss  xmm1,DWORD PTR [rip+0x76e070]        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  83a6f8:	f3 0f 5c 84 24 94 01 00 00 	subss  xmm0,DWORD PTR [rsp+0x194]
  83a701:	0f 2e c8             	ucomiss xmm1,xmm0
  83a704:	76 93                	jbe    83a699 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x17c9>
  83a706:	c6 83 81 06 00 00 00 	mov    BYTE PTR [rbx+0x681],0x0
  83a70d:	e9 37 f4 ff ff       	jmp    839b49 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xc79>
  83a712:	48 89 df             	mov    rdi,rbx
  83a715:	be 01 00 00 00       	mov    esi,0x1
  83a71a:	e8 61 c9 1a 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  83a71f:	66 0f d6 44 24 28    	movq   QWORD PTR [rsp+0x28],xmm0
  83a725:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  83a72a:	31 ff                	xor    edi,edi
  83a72c:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  83a732:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  83a737:	48 89 84 24 b0 00 00 00 	mov    QWORD PTR [rsp+0xb0],rax
  83a73f:	8b 44 24 78          	mov    eax,DWORD PTR [rsp+0x78]
  83a743:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  83a74a:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  83a74e:	48 85 c0             	test   rax,rax
  83a751:	74 04                	je     83a757 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1887>
  83a753:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  83a757:	48 8d 8c 24 b0 00 00 00 	lea    rcx,[rsp+0xb0]
  83a75f:	48 89 da             	mov    rdx,rbx
  83a762:	4c 89 e6             	mov    rsi,r12
  83a765:	e8 46 29 12 00       	call   95d0b0 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)>
  83a76a:	e9 86 ec ff ff       	jmp    8393f5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x525>
  83a76f:	45 31 f6             	xor    r14d,r14d
  83a772:	40 84 ed             	test   bpl,bpl
  83a775:	0f 84 e7 f8 ff ff    	je     83a062 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1192>
  83a77b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  83a780:	e9 d7 f8 ff ff       	jmp    83a05c <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x118c>
  83a785:	48 89 c3             	mov    rbx,rax
  83a788:	48 89 df             	mov    rdi,rbx
  83a78b:	e8 08 9d d1 ff       	call   554498 <_Unwind_Resume@plt>
  83a790:	45 84 f6             	test   r14b,r14b
  83a793:	48 89 c3             	mov    rbx,rax
  83a796:	74 f0                	je     83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a798:	48 8d bc 24 e0 02 00 00 	lea    rdi,[rsp+0x2e0]
  83a7a0:	e8 33 a1 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a7a5:	eb e1                	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a7a7:	4c 89 f7             	mov    rdi,r14
  83a7aa:	48 89 c3             	mov    rbx,rax
  83a7ad:	e8 26 a1 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a7b2:	eb d4                	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a7b4:	48 89 ef             	mov    rdi,rbp
  83a7b7:	48 89 c3             	mov    rbx,rax
  83a7ba:	e8 19 a1 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a7bf:	90                   	nop
  83a7c0:	eb c6                	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a7c2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83a7c7:	48 85 c0             	test   rax,rax
  83a7ca:	74 31                	je     83a7fd <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x192d>
  83a7cc:	83 c8 ff             	or     eax,0xffffffff
  83a7cf:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83a7d4:	85 c0                	test   eax,eax
  83a7d6:	0f 8f c1 f5 ff ff    	jg     839d9d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xecd>
  83a7dc:	48 8d b4 24 0f 03 00 00 	lea    rsi,[rsp+0x30f]
  83a7e4:	e8 ef af d1 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  83a7e9:	e9 af f5 ff ff       	jmp    839d9d <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xecd>
  83a7ee:	48 89 c3             	mov    rbx,rax
  83a7f1:	4c 89 ef             	mov    rdi,r13
  83a7f4:	e8 df a0 d1 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  83a7f9:	eb 8d                	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a7fb:	eb 88                	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a7fd:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83a800:	8d 50 ff             	lea    edx,[rax-0x1]
  83a803:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83a806:	eb cc                	jmp    83a7d4 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1904>
  83a808:	eb e4                	jmp    83a7ee <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x191e>
  83a80a:	e9 76 ff ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a80f:	90                   	nop
  83a810:	e9 70 ff ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a815:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  83a820:	e9 60 ff ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a825:	48 89 c3             	mov    rbx,rax
  83a828:	48 89 ef             	mov    rdi,rbp
  83a82b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  83a830:	e8 53 ba d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  83a835:	e9 4e ff ff ff       	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a83a:	e9 46 ff ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a83f:	b8 c8 41 55 00       	mov    eax,0x5541c8
  83a844:	48 85 c0             	test   rax,rax
  83a847:	74 30                	je     83a879 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x19a9>
  83a849:	83 c8 ff             	or     eax,0xffffffff
  83a84c:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  83a851:	85 c0                	test   eax,eax
  83a853:	0f 8f cc f4 ff ff    	jg     839d25 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xe55>
  83a859:	48 8d b4 24 10 03 00 00 	lea    rsi,[rsp+0x310]
  83a861:	f3 0f 11 44 24 40    	movss  DWORD PTR [rsp+0x40],xmm0
  83a867:	e8 6c af d1 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  83a86c:	f3 0f 10 44 24 40    	movss  xmm0,DWORD PTR [rsp+0x40]
  83a872:	e9 ae f4 ff ff       	jmp    839d25 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xe55>
  83a877:	eb ac                	jmp    83a825 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1955>
  83a879:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  83a87c:	8d 50 ff             	lea    edx,[rax-0x1]
  83a87f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  83a882:	eb cd                	jmp    83a851 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1981>
  83a884:	e9 fc fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a889:	4c 89 f7             	mov    rdi,r14
  83a88c:	48 89 c3             	mov    rbx,rax
  83a88f:	e8 d4 a9 d1 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  83a894:	eb 92                	jmp    83a828 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1958>
  83a896:	eb 8d                	jmp    83a825 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1955>
  83a898:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  83a8a0:	e9 e0 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a8a5:	48 89 ef             	mov    rdi,rbp
  83a8a8:	48 89 c3             	mov    rbx,rax
  83a8ab:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  83a8b0:	e8 b3 a9 d1 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  83a8b5:	e9 37 ff ff ff       	jmp    83a7f1 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1921>
  83a8ba:	eb e9                	jmp    83a8a5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x19d5>
  83a8bc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  83a8c0:	eb e3                	jmp    83a8a5 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x19d5>
  83a8c2:	e9 27 ff ff ff       	jmp    83a7ee <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x191e>
  83a8c7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  83a8d0:	e9 b0 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a8d5:	40 84 ed             	test   bpl,bpl
  83a8d8:	48 89 c3             	mov    rbx,rax
  83a8db:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  83a8e0:	0f 84 a2 fe ff ff    	je     83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a8e6:	4c 89 f7             	mov    rdi,r14
  83a8e9:	e8 9a b9 d1 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  83a8ee:	e9 95 fe ff ff       	jmp    83a788 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b8>
  83a8f3:	e9 2d ff ff ff       	jmp    83a825 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1955>
  83a8f8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  83a900:	e9 80 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a905:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  83a910:	e9 70 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a915:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  83a920:	e9 60 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a925:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  83a930:	e9 72 fe ff ff       	jmp    83a7a7 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18d7>
  83a935:	ba c8 41 55 00       	mov    edx,0x5541c8
  83a93a:	48 85 d2             	test   rdx,rdx
  83a93d:	0f 1f 00             	nop    DWORD PTR [rax]
  83a940:	74 53                	je     83a995 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1ac5>
  83a942:	83 ca ff             	or     edx,0xffffffff
  83a945:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  83a94a:	85 d2                	test   edx,edx
  83a94c:	0f 8f 1d e6 ff ff    	jg     838f6f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x9f>
  83a952:	48 8d b4 24 11 03 00 00 	lea    rsi,[rsp+0x311]
  83a95a:	88 44 24 58          	mov    BYTE PTR [rsp+0x58],al
  83a95e:	e8 e5 8b d1 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  83a963:	0f b6 44 24 58       	movzx  eax,BYTE PTR [rsp+0x58]
  83a968:	e9 02 e6 ff ff       	jmp    838f6f <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x9f>
  83a96d:	e9 b3 fe ff ff       	jmp    83a825 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1955>
  83a972:	e9 ae fe ff ff       	jmp    83a825 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1955>
  83a977:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  83a980:	e9 00 fe ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a985:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  83a990:	e9 f0 fd ff ff       	jmp    83a785 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x18b5>
  83a995:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  83a998:	8d 4a ff             	lea    ecx,[rdx-0x1]
  83a99b:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  83a99e:	66 90                	xchg   ax,ax
  83a9a0:	eb a8                	jmp    83a94a <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x1a7a>
  83a9a2:	66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]
