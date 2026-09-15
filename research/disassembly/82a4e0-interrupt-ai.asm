000000000082a4e0 <CCharacter::interruptAI(float, CLevel&)>:
  82a4e0:	48 89 5c 24 f0       	mov    QWORD PTR [rsp-0x10],rbx
  82a4e5:	48 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],rbp
  82a4ea:	48 83 ec 38          	sub    rsp,0x38
  82a4ee:	48 8d 6c 24 10       	lea    rbp,[rsp+0x10]
  82a4f3:	48 8d 54 24 1f       	lea    rdx,[rsp+0x1f]
  82a4f8:	48 89 fb             	mov    rbx,rdi
  82a4fb:	be 04 99 fc 00       	mov    esi,0xfc9904
  82a500:	48 89 ef             	mov    rdi,rbp
  82a503:	e8 f0 bd d2 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  82a508:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  82a50f:	48 89 ee             	mov    rsi,rbp
  82a512:	e8 49 c0 07 00       	call   8a6560 <CGenericModel::animationPlayingSubstring(std::string const&) const>
  82a517:	48 8b 7c 24 10       	mov    rdi,QWORD PTR [rsp+0x10]
  82a51c:	48 83 ef 18          	sub    rdi,0x18
  82a520:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  82a527:	75 21                	jne    82a54a <CCharacter::interruptAI(float, CLevel&)+0x6a>
  82a529:	84 c0                	test   al,al
  82a52b:	75 0e                	jne    82a53b <CCharacter::interruptAI(float, CLevel&)+0x5b>
  82a52d:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  82a530:	31 f6                	xor    esi,esi
  82a532:	48 89 df             	mov    rdi,rbx
  82a535:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  82a53b:	48 8b 5c 24 28       	mov    rbx,QWORD PTR [rsp+0x28]
  82a540:	48 8b 6c 24 30       	mov    rbp,QWORD PTR [rsp+0x30]
  82a545:	48 83 c4 38          	add    rsp,0x38
  82a549:	c3                   	ret
  82a54a:	ba c8 41 55 00       	mov    edx,0x5541c8
  82a54f:	48 85 d2             	test   rdx,rdx
  82a552:	74 39                	je     82a58d <CCharacter::interruptAI(float, CLevel&)+0xad>
  82a554:	83 ca ff             	or     edx,0xffffffff
  82a557:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  82a55c:	85 d2                	test   edx,edx
  82a55e:	7f c9                	jg     82a529 <CCharacter::interruptAI(float, CLevel&)+0x49>
  82a560:	48 8d 74 24 1e       	lea    rsi,[rsp+0x1e]
  82a565:	88 44 24 08          	mov    BYTE PTR [rsp+0x8],al
  82a569:	e8 6a b2 d2 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  82a56e:	0f b6 44 24 08       	movzx  eax,BYTE PTR [rsp+0x8]
  82a573:	eb b4                	jmp    82a529 <CCharacter::interruptAI(float, CLevel&)+0x49>
  82a575:	48 89 ef             	mov    rdi,rbp
  82a578:	48 89 c3             	mov    rbx,rax
  82a57b:	e8 08 bd d2 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  82a580:	48 89 df             	mov    rdi,rbx
  82a583:	e8 10 9f d2 ff       	call   554498 <_Unwind_Resume@plt>
  82a588:	48 89 c3             	mov    rbx,rax
  82a58b:	eb f3                	jmp    82a580 <CCharacter::interruptAI(float, CLevel&)+0xa0>
  82a58d:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  82a590:	8d 4a ff             	lea    ecx,[rdx-0x1]
  82a593:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  82a596:	eb c4                	jmp    82a55c <CCharacter::interruptAI(float, CLevel&)+0x7c>
  82a598:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

