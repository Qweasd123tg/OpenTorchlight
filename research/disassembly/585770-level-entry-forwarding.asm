# Original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address-scoped excerpt of the user-supplied archive (2),
# original-analysis/full-intel-disassembly.asm; not a fresh ELF export.

# Range [0x585770, 0x58579a)
  585770:	41 57                	push   r15
  585772:	41 56                	push   r14
  585774:	49 89 fe             	mov    r14,rdi
  585777:	41 55                	push   r13
  585779:	41 54                	push   r12
  58577b:	55                   	push   rbp
  58577c:	53                   	push   rbx
  58577d:	48 89 f3             	mov    rbx,rsi
  585780:	48 81 ec f8 03 00 00 	sub    rsp,0x3f8
  585787:	48 89 54 24 48       	mov    QWORD PTR [rsp+0x48],rdx
  58578c:	44 89 44 24 40       	mov    DWORD PTR [rsp+0x40],r8d
  585791:	44 89 4c 24 44       	mov    DWORD PTR [rsp+0x44],r9d
  585796:	88 4c 24 57          	mov    BYTE PTR [rsp+0x57],cl

# Range [0x58608f, 0x5860c4)
  58608f:	48 8d 9c 24 10 02 00 00 	lea    rbx,[rsp+0x210]
  586097:	48 8b b4 24 30 04 00 00 	mov    rsi,QWORD PTR [rsp+0x430]
  58609f:	48 89 df             	mov    rdi,rbx
  5860a2:	e8 e1 d1 fc ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  5860a7:	0f b6 54 24 57       	movzx  edx,BYTE PTR [rsp+0x57]
  5860ac:	49 8b 7e 70          	mov    rdi,QWORD PTR [r14+0x70]
  5860b0:	49 89 d9             	mov    r9,rbx
  5860b3:	8b 4c 24 44          	mov    ecx,DWORD PTR [rsp+0x44]
  5860b7:	48 8b 74 24 38       	mov    rsi,QWORD PTR [rsp+0x38]
  5860bc:	4d 89 e0             	mov    r8,r12
  5860bf:	e8 8c 90 3d 00       	call   95f150 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>

# Range [0x5862f7, 0x586363)
  5862fb:	49 8b 46 70          	mov    rax,QWORD PTR [r14+0x70]
  5862ff:	83 7c 24 44 04       	cmp    DWORD PTR [rsp+0x44],0x4
  586304:	48 8b 90 40 01 00 00 	mov    rdx,QWORD PTR [rax+0x140]
  58630b:	48 89 c7             	mov    rdi,rax
  58630e:	48 89 94 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rdx
  586316:	8b 90 48 01 00 00    	mov    edx,DWORD PTR [rax+0x148]
  58631c:	89 94 24 a8 00 00 00 	mov    DWORD PTR [rsp+0xa8],edx
  586323:	0f 84 0c 05 00 00    	je     586835 <CGameClient::loadLevel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool, int, ELevelEntryType, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x10c5>
  586329:	48 8d 9c 24 a0 00 00 00 	lea    rbx,[rsp+0xa0]
  586331:	49 8b 76 58          	mov    rsi,QWORD PTR [r14+0x58]
  586335:	31 c9                	xor    ecx,ecx
  586337:	48 89 da             	mov    rdx,rbx
  58633a:	e8 71 4b 3d 00       	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>
  58633f:	49 8b 7e 58          	mov    rdi,QWORD PTR [r14+0x58]
  586343:	be 20 03 00 00       	mov    esi,0x320
  586348:	48 89 c5             	mov    rbp,rax
  58634b:	e8 40 85 28 00       	call   80e890 <CCharacter::setMaximumTreeDepth(unsigned int)>
  586350:	49 8b 76 70          	mov    rsi,QWORD PTR [r14+0x70]
  586354:	48 89 ef             	mov    rdi,rbp
  586357:	48 81 c6 64 01 00 00 	add    rsi,0x164
  58635e:	e8 7d c3 28 00       	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
