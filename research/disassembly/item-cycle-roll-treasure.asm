# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x95d0b0, 0x95d21f); source instructions unchanged.
  95d0b0:	41 57                	push   r15
  95d0b2:	49 89 d7             	mov    r15,rdx
  95d0b5:	41 56                	push   r14
  95d0b7:	41 55                	push   r13
  95d0b9:	49 89 f5             	mov    r13,rsi
  95d0bc:	be 10 5b fd 00       	mov    esi,0xfd5b10
  95d0c1:	41 54                	push   r12
  95d0c3:	49 89 cc             	mov    r12,rcx
  95d0c6:	55                   	push   rbp
  95d0c7:	48 89 fd             	mov    rbp,rdi
  95d0ca:	53                   	push   rbx
  95d0cb:	48 83 ec 48          	sub    rsp,0x48
  95d0cf:	48 8d 5c 24 30       	lea    rbx,[rsp+0x30]
  95d0d4:	48 8d 54 24 3f       	lea    rdx,[rsp+0x3f]
  95d0d9:	48 c7 44 24 10 00 00 00 00 	mov    QWORD PTR [rsp+0x10],0x0
  95d0e2:	c7 44 24 18 00 00 00 00 	mov    DWORD PTR [rsp+0x18],0x0
  95d0ea:	c7 44 24 1c 00 00 00 00 	mov    DWORD PTR [rsp+0x1c],0x0
  95d0f2:	c7 44 24 20 01 00 00 00 	mov    DWORD PTR [rsp+0x20],0x1
  95d0fa:	44 8b b7 a8 01 00 00 	mov    r14d,DWORD PTR [rdi+0x1a8]
  95d101:	48 89 df             	mov    rdi,rbx
  95d104:	e8 4f 8d bf ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  95d109:	48 8b bd 38 01 00 00 	mov    rdi,QWORD PTR [rbp+0x138]
  95d110:	48 8d 54 24 10       	lea    rdx,[rsp+0x10]
  95d115:	4d 89 e9             	mov    r9,r13
  95d118:	45 31 c0             	xor    r8d,r8d
  95d11b:	b9 01 00 00 00       	mov    ecx,0x1
  95d120:	48 89 de             	mov    rsi,rbx
  95d123:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  95d12b:	44 89 34 24          	mov    DWORD PTR [rsp],r14d
  95d12f:	e8 5c c0 41 00       	call   d79190 <CResourceManager::createUnitsBySpawnClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, TArrayList<CBaseUnit*>&, unsigned int, CCharacter*, CCharacter*, int, int)>
  95d134:	48 8b 7c 24 30       	mov    rdi,QWORD PTR [rsp+0x30]
  95d139:	48 83 ef 18          	sub    rdi,0x18
  95d13d:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  95d144:	0f 85 94 00 00 00    	jne    95d1de <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x12e>
  95d14a:	8b 74 24 18          	mov    esi,DWORD PTR [rsp+0x18]
  95d14e:	31 db                	xor    ebx,ebx
  95d150:	85 f6                	test   esi,esi
  95d152:	75 28                	jne    95d17c <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0xcc>
  95d154:	eb 3a                	jmp    95d190 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0xe0>
  95d156:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  95d160:	48 8b 44 24 10       	mov    rax,QWORD PTR [rsp+0x10]
  95d165:	48 8b 30             	mov    rsi,QWORD PTR [rax]
  95d168:	4c 89 e2             	mov    rdx,r12
  95d16b:	48 89 ef             	mov    rdi,rbp
  95d16e:	e8 3d fc ff ff       	call   95cdb0 <CLevel::addUnit(CBaseUnit*, Ogre::Vector3 const&)>
  95d173:	83 c3 01             	add    ebx,0x1
  95d176:	3b 5c 24 18          	cmp    ebx,DWORD PTR [rsp+0x18]
  95d17a:	73 14                	jae    95d190 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0xe0>
  95d17c:	39 5c 24 1c          	cmp    DWORD PTR [rsp+0x1c],ebx
  95d180:	76 de                	jbe    95d160 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0xb0>
  95d182:	89 d8                	mov    eax,ebx
  95d184:	48 c1 e0 03          	shl    rax,0x3
  95d188:	48 03 44 24 10       	add    rax,QWORD PTR [rsp+0x10]
  95d18d:	eb d6                	jmp    95d165 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0xb5>
  95d18f:	90                   	nop
  95d190:	45 31 c0             	xor    r8d,r8d
  95d193:	4c 89 e1             	mov    rcx,r12
  95d196:	4c 89 fa             	mov    rdx,r15
  95d199:	4c 89 ee             	mov    rsi,r13
  95d19c:	48 89 ef             	mov    rdi,rbp
  95d19f:	e8 cc fc ff ff       	call   95ce70 <CLevel::rollMoney(CCharacter*, CCharacter*, Ogre::Vector3 const&, bool)>
  95d1a4:	48 8b 7c 24 10       	mov    rdi,QWORD PTR [rsp+0x10]
  95d1a9:	48 85 ff             	test   rdi,rdi
  95d1ac:	74 05                	je     95d1b3 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x103>
  95d1ae:	e8 85 64 bf ff       	call   553638 <operator delete[](void*)@plt>
  95d1b3:	48 83 c4 48          	add    rsp,0x48
  95d1b7:	5b                   	pop    rbx
  95d1b8:	5d                   	pop    rbp
  95d1b9:	41 5c                	pop    r12
  95d1bb:	41 5d                	pop    r13
  95d1bd:	41 5e                	pop    r14
  95d1bf:	41 5f                	pop    r15
  95d1c1:	c3                   	ret
  95d1c2:	48 89 c5             	mov    rbp,rax
  95d1c5:	48 8b 7c 24 10       	mov    rdi,QWORD PTR [rsp+0x10]
  95d1ca:	48 85 ff             	test   rdi,rdi
  95d1cd:	74 05                	je     95d1d4 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x124>
  95d1cf:	e8 64 64 bf ff       	call   553638 <operator delete[](void*)@plt>
  95d1d4:	48 89 ef             	mov    rdi,rbp
  95d1d7:	e8 bc 72 bf ff       	call   554498 <_Unwind_Resume@plt>
  95d1dc:	eb e4                	jmp    95d1c2 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x112>
  95d1de:	b8 c8 41 55 00       	mov    eax,0x5541c8
  95d1e3:	48 85 c0             	test   rax,rax
  95d1e6:	74 2c                	je     95d214 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x164>
  95d1e8:	83 c8 ff             	or     eax,0xffffffff
  95d1eb:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  95d1f0:	85 c0                	test   eax,eax
  95d1f2:	0f 8f 52 ff ff ff    	jg     95d14a <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x9a>
  95d1f8:	48 8d 74 24 3e       	lea    rsi,[rsp+0x3e]
  95d1fd:	e8 46 63 bf ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  95d202:	e9 43 ff ff ff       	jmp    95d14a <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x9a>
  95d207:	48 89 df             	mov    rdi,rbx
  95d20a:	48 89 c5             	mov    rbp,rax
  95d20d:	e8 c6 76 bf ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  95d212:	eb b1                	jmp    95d1c5 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x115>
  95d214:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  95d217:	8d 50 ff             	lea    edx,[rax-0x1]
  95d21a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  95d21d:	eb d1                	jmp    95d1f0 <CLevel::rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&)+0x140>
