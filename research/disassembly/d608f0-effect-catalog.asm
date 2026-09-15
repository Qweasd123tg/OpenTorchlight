# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000d608f0 <parseEffects()>:
  d608f0:	41 57                	push   r15
  d608f2:	be 08 16 00 01       	mov    esi,0x1001608
  d608f7:	41 56                	push   r14
  d608f9:	41 55                	push   r13
  d608fb:	41 54                	push   r12
  d608fd:	55                   	push   rbp
  d608fe:	53                   	push   rbx
  d608ff:	48 81 ec f8 01 00 00 	sub    rsp,0x1f8
  d60906:	48 8d 9c 24 b0 01 00 00 	lea    rbx,[rsp+0x1b0]
  d6090e:	48 8d 94 24 ef 01 00 00 	lea    rdx,[rsp+0x1ef]
  d60916:	48 89 df             	mov    rdi,rbx
  d60919:	e8 3a 55 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d6091e:	45 31 c9             	xor    r9d,r9d
  d60921:	41 b8 0a 00 00 00    	mov    r8d,0xa
  d60927:	b9 14 00 00 00       	mov    ecx,0x14
  d6092c:	31 d2                	xor    edx,edx
  d6092e:	48 89 de             	mov    rsi,rbx
  d60931:	48 89 e7             	mov    rdi,rsp
  d60934:	e8 97 11 f0 ff       	call   c61ad0 <CDataGroup::CDataGroup(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, CDataGroup*, unsigned int, unsigned int, TRepository<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >*)>
  d60939:	48 8b bc 24 b0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1b0]
  d60941:	41 bc 40 45 42 01    	mov    r12d,0x1424540
  d60947:	48 83 ef 18          	sub    rdi,0x18
  d6094b:	4c 39 e7             	cmp    rdi,r12
  d6094e:	0f 85 73 0f 00 00    	jne    d618c7 <parseEffects()+0xfd7>
  d60954:	48 8d 9c 24 a0 01 00 00 	lea    rbx,[rsp+0x1a0]
  d6095c:	48 8d 94 24 ee 01 00 00 	lea    rdx,[rsp+0x1ee]
  d60964:	be c8 82 ff 00       	mov    esi,0xff82c8
  d60969:	48 89 df             	mov    rdi,rbx
  d6096c:	e8 e7 54 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60971:	31 d2                	xor    edx,edx
  d60973:	48 89 de             	mov    rsi,rbx
  d60976:	48 89 e7             	mov    rdi,rsp
  d60979:	e8 12 17 f0 ff       	call   c62090 <CDataGroup::LoadFile(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, CTimerStatics*)>
  d6097e:	48 8b bc 24 a0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1a0]
  d60986:	48 83 ef 18          	sub    rdi,0x18
  d6098a:	49 39 fc             	cmp    r12,rdi
  d6098d:	0f 85 e8 0e 00 00    	jne    d6187b <parseEffects()+0xf8b>
  d60993:	81 7c 24 40 91 00 00 00 	cmp    DWORD PTR [rsp+0x40],0x91
  d6099b:	74 59                	je     d609f6 <parseEffects()+0x106>
  d6099d:	48 8d 9c 24 90 01 00 00 	lea    rbx,[rsp+0x190]
  d609a5:	48 8d 94 24 ed 01 00 00 	lea    rdx,[rsp+0x1ed]
  d609ad:	be 90 83 ff 00       	mov    esi,0xff8390
  d609b2:	48 89 df             	mov    rdi,rbx
  d609b5:	e8 3e 59 7f ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  d609ba:	e8 59 3f 7f ff       	call   554918 <Ogre::LogManager::getSingleton()@plt>
  d609bf:	31 c9                	xor    ecx,ecx
  d609c1:	ba 03 00 00 00       	mov    edx,0x3
  d609c6:	48 89 de             	mov    rsi,rbx
  d609c9:	48 89 c7             	mov    rdi,rax
  d609cc:	e8 97 44 7f ff       	call   554e68 <Ogre::LogManager::logMessage(std::string const&, Ogre::LogMessageLevel, bool)@plt>
  d609d1:	48 8b bc 24 90 01 00 00 	mov    rdi,QWORD PTR [rsp+0x190]
  d609d9:	48 83 ef 18          	sub    rdi,0x18
  d609dd:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  d609e4:	0f 85 45 0e 00 00    	jne    d6182f <parseEffects()+0xf3f>
  d609ea:	8b 44 24 40          	mov    eax,DWORD PTR [rsp+0x40]
  d609ee:	85 c0                	test   eax,eax
  d609f0:	0f 84 5a 07 00 00    	je     d61150 <parseEffects()+0x860>
  d609f6:	45 31 ed             	xor    r13d,r13d
  d609f9:	45 31 ff             	xor    r15d,r15d
  d609fc:	31 ed                	xor    ebp,ebp
  d609fe:	e9 12 07 00 00       	jmp    d61115 <parseEffects()+0x825>
  d60a03:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  d60a08:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60a0d:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60a10:	48 8d b4 24 80 01 00 00 	lea    rsi,[rsp+0x180]
  d60a18:	ba 90 89 50 01       	mov    edx,0x1508990
  d60a1d:	e8 4e e9 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60a22:	89 eb                	mov    ebx,ebp
  d60a24:	48 89 c6             	mov    rsi,rax
  d60a27:	48 8d 3c dd e0 3d 50 01 	lea    rdi,[rbx*8+0x1503de0]
  d60a2f:	e8 04 56 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60a34:	48 8b bc 24 80 01 00 00 	mov    rdi,QWORD PTR [rsp+0x180]
  d60a3c:	48 83 ef 18          	sub    rdi,0x18
  d60a40:	49 39 fc             	cmp    r12,rdi
  d60a43:	0f 85 58 08 00 00    	jne    d612a1 <parseEffects()+0x9b1>
  d60a49:	48 8d 94 24 eb 01 00 00 	lea    rdx,[rsp+0x1eb]
  d60a51:	48 8d bc 24 70 01 00 00 	lea    rdi,[rsp+0x170]
  d60a59:	be 20 83 ff 00       	mov    esi,0xff8320
  d60a5e:	e8 f5 53 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60a63:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60a67:	0f 87 03 08 00 00    	ja     d61270 <parseEffects()+0x980>
  d60a6d:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60a72:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60a75:	48 8d b4 24 70 01 00 00 	lea    rsi,[rsp+0x170]
  d60a7d:	ba 90 89 50 01       	mov    edx,0x1508990
  d60a82:	e8 e9 e8 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60a87:	48 8d 3c dd 80 42 50 01 	lea    rdi,[rbx*8+0x1504280]
  d60a8f:	48 89 c6             	mov    rsi,rax
  d60a92:	e8 a1 55 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60a97:	48 8b bc 24 70 01 00 00 	mov    rdi,QWORD PTR [rsp+0x170]
  d60a9f:	48 83 ef 18          	sub    rdi,0x18
  d60aa3:	49 39 fc             	cmp    r12,rdi
  d60aa6:	0f 85 55 0b 00 00    	jne    d61601 <parseEffects()+0xd11>
  d60aac:	48 8d 94 24 ea 01 00 00 	lea    rdx,[rsp+0x1ea]
  d60ab4:	48 8d bc 24 60 01 00 00 	lea    rdi,[rsp+0x160]
  d60abc:	be 40 83 ff 00       	mov    esi,0xff8340
  d60ac1:	e8 92 53 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60ac6:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60aca:	0f 87 90 07 00 00    	ja     d61260 <parseEffects()+0x970>
  d60ad0:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60ad5:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60ad8:	48 8d b4 24 60 01 00 00 	lea    rsi,[rsp+0x160]
  d60ae0:	ba 90 89 50 01       	mov    edx,0x1508990
  d60ae5:	e8 86 e8 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60aea:	48 8d 3c dd 20 47 50 01 	lea    rdi,[rbx*8+0x1504720]
  d60af2:	48 89 c6             	mov    rsi,rax
  d60af5:	e8 3e 55 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60afa:	48 8b bc 24 60 01 00 00 	mov    rdi,QWORD PTR [rsp+0x160]
  d60b02:	48 83 ef 18          	sub    rdi,0x18
  d60b06:	49 39 fc             	cmp    r12,rdi
  d60b09:	0f 85 72 09 00 00    	jne    d61481 <parseEffects()+0xb91>
  d60b0f:	48 8d 94 24 e9 01 00 00 	lea    rdx,[rsp+0x1e9]
  d60b17:	48 8d bc 24 50 01 00 00 	lea    rdi,[rsp+0x150]
  d60b1f:	be 58 81 ff 00       	mov    esi,0xff8158
  d60b24:	e8 2f 53 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60b29:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60b2d:	0f 87 1d 07 00 00    	ja     d61250 <parseEffects()+0x960>
  d60b33:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60b38:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60b3b:	48 8d b4 24 50 01 00 00 	lea    rsi,[rsp+0x150]
  d60b43:	ba 90 89 50 01       	mov    edx,0x1508990
  d60b48:	e8 23 e8 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60b4d:	48 8d 3c dd c0 4b 50 01 	lea    rdi,[rbx*8+0x1504bc0]
  d60b55:	48 89 c6             	mov    rsi,rax
  d60b58:	e8 db 54 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60b5d:	48 8b bc 24 50 01 00 00 	mov    rdi,QWORD PTR [rsp+0x150]
  d60b65:	48 83 ef 18          	sub    rdi,0x18
  d60b69:	49 39 fc             	cmp    r12,rdi
  d60b6c:	0f 85 cf 09 00 00    	jne    d61541 <parseEffects()+0xc51>
  d60b72:	4c 8d b4 24 40 01 00 00 	lea    r14,[rsp+0x140]
  d60b7a:	48 8d 94 24 e8 01 00 00 	lea    rdx,[rsp+0x1e8]
  d60b82:	be 68 83 ff 00       	mov    esi,0xff8368
  d60b87:	4c 89 f7             	mov    rdi,r14
  d60b8a:	e8 c9 52 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60b8f:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60b93:	0f 87 a7 06 00 00    	ja     d61240 <parseEffects()+0x950>
  d60b99:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60b9e:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60ba1:	ba 90 89 50 01       	mov    edx,0x1508990
  d60ba6:	4c 89 f6             	mov    rsi,r14
  d60ba9:	e8 c2 e7 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60bae:	48 8d 3c dd 60 50 50 01 	lea    rdi,[rbx*8+0x1505060]
  d60bb6:	48 89 c6             	mov    rsi,rax
  d60bb9:	e8 7a 54 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60bbe:	48 8b bc 24 40 01 00 00 	mov    rdi,QWORD PTR [rsp+0x140]
  d60bc6:	48 83 ef 18          	sub    rdi,0x18
  d60bca:	49 39 fc             	cmp    r12,rdi
  d60bcd:	0f 85 ee 07 00 00    	jne    d613c1 <parseEffects()+0xad1>
  d60bd3:	4c 8d b4 24 30 01 00 00 	lea    r14,[rsp+0x130]
  d60bdb:	48 8d 94 24 e7 01 00 00 	lea    rdx,[rsp+0x1e7]
  d60be3:	be 74 81 ff 00       	mov    esi,0xff8174
  d60be8:	4c 89 f7             	mov    rdi,r14
  d60beb:	e8 68 52 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60bf0:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60bf4:	0f 87 36 06 00 00    	ja     d61230 <parseEffects()+0x940>
  d60bfa:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60bff:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60c02:	ba 90 89 50 01       	mov    edx,0x1508990
  d60c07:	4c 89 f6             	mov    rsi,r14
  d60c0a:	e8 61 e7 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60c0f:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60c13:	48 89 c6             	mov    rsi,rax
  d60c16:	48 8d 3c d5 20 5c 50 01 	lea    rdi,[rdx*8+0x1505c20]
  d60c1e:	e8 15 54 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60c23:	48 8b bc 24 30 01 00 00 	mov    rdi,QWORD PTR [rsp+0x130]
  d60c2b:	48 83 ef 18          	sub    rdi,0x18
  d60c2f:	49 39 fc             	cmp    r12,rdi
  d60c32:	0f 85 69 09 00 00    	jne    d615a1 <parseEffects()+0xcb1>
  d60c38:	4c 8d b4 24 20 01 00 00 	lea    r14,[rsp+0x120]
  d60c40:	48 8d 94 24 e6 01 00 00 	lea    rdx,[rsp+0x1e6]
  d60c48:	be 90 81 ff 00       	mov    esi,0xff8190
  d60c4d:	4c 89 f7             	mov    rdi,r14
  d60c50:	e8 03 52 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60c55:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60c59:	0f 87 c1 05 00 00    	ja     d61220 <parseEffects()+0x930>
  d60c5f:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60c64:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60c67:	ba 90 89 50 01       	mov    edx,0x1508990
  d60c6c:	4c 89 f6             	mov    rsi,r14
  d60c6f:	e8 fc e6 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60c74:	48 8d 54 9b 01       	lea    rdx,[rbx+rbx*4+0x1]
  d60c79:	48 89 c6             	mov    rsi,rax
  d60c7c:	48 8d 3c d5 20 5c 50 01 	lea    rdi,[rdx*8+0x1505c20]
  d60c84:	e8 af 53 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60c89:	48 8b bc 24 20 01 00 00 	mov    rdi,QWORD PTR [rsp+0x120]
  d60c91:	48 83 ef 18          	sub    rdi,0x18
  d60c95:	49 39 fc             	cmp    r12,rdi
  d60c98:	0f 85 83 07 00 00    	jne    d61421 <parseEffects()+0xb31>
  d60c9e:	4c 8d b4 24 10 01 00 00 	lea    r14,[rsp+0x110]
  d60ca6:	48 8d 94 24 e5 01 00 00 	lea    rdx,[rsp+0x1e5]
  d60cae:	be ac 81 ff 00       	mov    esi,0xff81ac
  d60cb3:	4c 89 f7             	mov    rdi,r14
  d60cb6:	e8 9d 51 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60cbb:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60cbf:	0f 87 4b 05 00 00    	ja     d61210 <parseEffects()+0x920>
  d60cc5:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60cca:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60ccd:	ba 90 89 50 01       	mov    edx,0x1508990
  d60cd2:	4c 89 f6             	mov    rsi,r14
  d60cd5:	e8 96 e6 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60cda:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60cde:	48 89 c6             	mov    rsi,rax
  d60ce1:	48 8d 3c d5 30 5c 50 01 	lea    rdi,[rdx*8+0x1505c30]
  d60ce9:	e8 4a 53 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60cee:	48 8b bc 24 10 01 00 00 	mov    rdi,QWORD PTR [rsp+0x110]
  d60cf6:	48 83 ef 18          	sub    rdi,0x18
  d60cfa:	49 39 fc             	cmp    r12,rdi
  d60cfd:	0f 85 de 07 00 00    	jne    d614e1 <parseEffects()+0xbf1>
  d60d03:	4c 8d b4 24 00 01 00 00 	lea    r14,[rsp+0x100]
  d60d0b:	48 8d 94 24 e4 01 00 00 	lea    rdx,[rsp+0x1e4]
  d60d13:	be c8 81 ff 00       	mov    esi,0xff81c8
  d60d18:	4c 89 f7             	mov    rdi,r14
  d60d1b:	e8 38 51 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60d20:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60d24:	0f 87 d6 04 00 00    	ja     d61200 <parseEffects()+0x910>
  d60d2a:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60d2f:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60d32:	ba 90 89 50 01       	mov    edx,0x1508990
  d60d37:	4c 89 f6             	mov    rsi,r14
  d60d3a:	e8 31 e6 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60d3f:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60d43:	48 89 c6             	mov    rsi,rax
  d60d46:	48 8d 3c d5 38 5c 50 01 	lea    rdi,[rdx*8+0x1505c38]
  d60d4e:	e8 e5 52 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60d53:	48 8b bc 24 00 01 00 00 	mov    rdi,QWORD PTR [rsp+0x100]
  d60d5b:	48 83 ef 18          	sub    rdi,0x18
  d60d5f:	49 39 fc             	cmp    r12,rdi
  d60d62:	0f 85 f9 05 00 00    	jne    d61361 <parseEffects()+0xa71>
  d60d68:	4c 8d b4 24 f0 00 00 00 	lea    r14,[rsp+0xf0]
  d60d70:	48 8d 94 24 e3 01 00 00 	lea    rdx,[rsp+0x1e3]
  d60d78:	be e4 81 ff 00       	mov    esi,0xff81e4
  d60d7d:	4c 89 f7             	mov    rdi,r14
  d60d80:	e8 d3 50 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60d85:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60d89:	0f 87 61 04 00 00    	ja     d611f0 <parseEffects()+0x900>
  d60d8f:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60d94:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60d97:	ba 90 89 50 01       	mov    edx,0x1508990
  d60d9c:	4c 89 f6             	mov    rsi,r14
  d60d9f:	e8 cc e5 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60da4:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60da8:	48 89 c6             	mov    rsi,rax
  d60dab:	48 8d 3c d5 40 5c 50 01 	lea    rdi,[rdx*8+0x1505c40]
  d60db3:	e8 80 52 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60db8:	48 8b bc 24 f0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xf0]
  d60dc0:	48 83 ef 18          	sub    rdi,0x18
  d60dc4:	49 39 fc             	cmp    r12,rdi
  d60dc7:	0f 85 04 08 00 00    	jne    d615d1 <parseEffects()+0xce1>
  d60dcd:	4c 8d b4 24 e0 00 00 00 	lea    r14,[rsp+0xe0]
  d60dd5:	48 8d 94 24 e2 01 00 00 	lea    rdx,[rsp+0x1e2]
  d60ddd:	be 00 82 ff 00       	mov    esi,0xff8200
  d60de2:	4c 89 f7             	mov    rdi,r14
  d60de5:	e8 6e 50 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60dea:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60dee:	0f 87 ec 03 00 00    	ja     d611e0 <parseEffects()+0x8f0>
  d60df4:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60df9:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60dfc:	ba 90 89 50 01       	mov    edx,0x1508990
  d60e01:	4c 89 f6             	mov    rsi,r14
  d60e04:	e8 67 e5 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60e09:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60e0d:	48 89 c6             	mov    rsi,rax
  d60e10:	48 8d 3c d5 e0 72 50 01 	lea    rdi,[rdx*8+0x15072e0]
  d60e18:	e8 1b 52 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60e1d:	48 8b bc 24 e0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xe0]
  d60e25:	48 83 ef 18          	sub    rdi,0x18
  d60e29:	49 39 fc             	cmp    r12,rdi
  d60e2c:	0f 85 1f 06 00 00    	jne    d61451 <parseEffects()+0xb61>
  d60e32:	4c 8d b4 24 d0 00 00 00 	lea    r14,[rsp+0xd0]
  d60e3a:	48 8d 94 24 e1 01 00 00 	lea    rdx,[rsp+0x1e1]
  d60e42:	be 1c 82 ff 00       	mov    esi,0xff821c
  d60e47:	4c 89 f7             	mov    rdi,r14
  d60e4a:	e8 09 50 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60e4f:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60e53:	0f 87 77 03 00 00    	ja     d611d0 <parseEffects()+0x8e0>
  d60e59:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60e5e:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60e61:	ba 90 89 50 01       	mov    edx,0x1508990
  d60e66:	4c 89 f6             	mov    rsi,r14
  d60e69:	e8 02 e5 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60e6e:	48 8d 54 9b 01       	lea    rdx,[rbx+rbx*4+0x1]
  d60e73:	48 89 c6             	mov    rsi,rax
  d60e76:	48 8d 3c d5 e0 72 50 01 	lea    rdi,[rdx*8+0x15072e0]
  d60e7e:	e8 b5 51 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60e83:	48 8b bc 24 d0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xd0]
  d60e8b:	48 83 ef 18          	sub    rdi,0x18
  d60e8f:	49 39 fc             	cmp    r12,rdi
  d60e92:	0f 85 79 06 00 00    	jne    d61511 <parseEffects()+0xc21>
  d60e98:	4c 8d b4 24 c0 00 00 00 	lea    r14,[rsp+0xc0]
  d60ea0:	48 8d 94 24 e0 01 00 00 	lea    rdx,[rsp+0x1e0]
  d60ea8:	be 38 82 ff 00       	mov    esi,0xff8238
  d60ead:	4c 89 f7             	mov    rdi,r14
  d60eb0:	e8 a3 4f 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60eb5:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60eb9:	0f 87 01 03 00 00    	ja     d611c0 <parseEffects()+0x8d0>
  d60ebf:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60ec4:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60ec7:	ba 90 89 50 01       	mov    edx,0x1508990
  d60ecc:	4c 89 f6             	mov    rsi,r14
  d60ecf:	e8 9c e4 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60ed4:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60ed8:	48 89 c6             	mov    rsi,rax
  d60edb:	48 8d 3c d5 f0 72 50 01 	lea    rdi,[rdx*8+0x15072f0]
  d60ee3:	e8 50 51 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60ee8:	48 8b bc 24 c0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xc0]
  d60ef0:	48 83 ef 18          	sub    rdi,0x18
  d60ef4:	49 39 fc             	cmp    r12,rdi
  d60ef7:	0f 85 94 04 00 00    	jne    d61391 <parseEffects()+0xaa1>
  d60efd:	4c 8d b4 24 b0 00 00 00 	lea    r14,[rsp+0xb0]
  d60f05:	48 8d 94 24 df 01 00 00 	lea    rdx,[rsp+0x1df]
  d60f0d:	be 54 82 ff 00       	mov    esi,0xff8254
  d60f12:	4c 89 f7             	mov    rdi,r14
  d60f15:	e8 3e 4f 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60f1a:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60f1e:	0f 87 8c 02 00 00    	ja     d611b0 <parseEffects()+0x8c0>
  d60f24:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60f29:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60f2c:	ba 90 89 50 01       	mov    edx,0x1508990
  d60f31:	4c 89 f6             	mov    rsi,r14
  d60f34:	e8 37 e4 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60f39:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60f3d:	48 89 c6             	mov    rsi,rax
  d60f40:	48 8d 3c d5 f8 72 50 01 	lea    rdi,[rdx*8+0x15072f8]
  d60f48:	e8 eb 50 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60f4d:	48 8b bc 24 b0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xb0]
  d60f55:	48 83 ef 18          	sub    rdi,0x18
  d60f59:	49 39 fc             	cmp    r12,rdi
  d60f5c:	0f 85 0f 06 00 00    	jne    d61571 <parseEffects()+0xc81>
  d60f62:	4c 8d b4 24 a0 00 00 00 	lea    r14,[rsp+0xa0]
  d60f6a:	48 8d 94 24 de 01 00 00 	lea    rdx,[rsp+0x1de]
  d60f72:	be 70 82 ff 00       	mov    esi,0xff8270
  d60f77:	4c 89 f7             	mov    rdi,r14
  d60f7a:	e8 d9 4e 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60f7f:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60f83:	0f 87 17 02 00 00    	ja     d611a0 <parseEffects()+0x8b0>
  d60f89:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60f8e:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60f91:	ba 90 89 50 01       	mov    edx,0x1508990
  d60f96:	4c 89 f6             	mov    rsi,r14
  d60f99:	e8 d2 e3 ef ff       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d60f9e:	48 8d 14 9b          	lea    rdx,[rbx+rbx*4]
  d60fa2:	48 89 c6             	mov    rsi,rax
  d60fa5:	48 8d 3c d5 00 73 50 01 	lea    rdi,[rdx*8+0x1507300]
  d60fad:	e8 86 50 7f ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  d60fb2:	48 8b bc 24 a0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xa0]
  d60fba:	48 83 ef 18          	sub    rdi,0x18
  d60fbe:	49 39 fc             	cmp    r12,rdi
  d60fc1:	0f 85 2a 04 00 00    	jne    d613f1 <parseEffects()+0xb01>
  d60fc7:	48 8d 9c 24 80 00 00 00 	lea    rbx,[rsp+0x80]
  d60fcf:	48 8d 94 24 dd 01 00 00 	lea    rdx,[rsp+0x1dd]
  d60fd7:	be 6c d2 fc 00       	mov    esi,0xfcd26c
  d60fdc:	48 89 df             	mov    rdi,rbx
  d60fdf:	e8 74 4e 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d60fe4:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d60fe8:	0f 87 a2 01 00 00    	ja     d61190 <parseEffects()+0x8a0>
  d60fee:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d60ff3:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d60ff6:	ba a4 36 fc 00       	mov    edx,0xfc36a4
  d60ffb:	48 89 de             	mov    rsi,rbx
  d60ffe:	e8 9d e3 ef ff       	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  d61003:	4c 8d b4 24 90 00 00 00 	lea    r14,[rsp+0x90]
  d6100b:	48 89 c6             	mov    rsi,rax
  d6100e:	4c 89 f7             	mov    rdi,r14
  d61011:	e8 7a d1 f2 ff       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  d61016:	48 8b bc 24 80 00 00 00 	mov    rdi,QWORD PTR [rsp+0x80]
  d6101e:	48 83 ef 18          	sub    rdi,0x18
  d61022:	49 39 fc             	cmp    r12,rdi
  d61025:	0f 85 86 04 00 00    	jne    d614b1 <parseEffects()+0xbc1>
  d6102b:	be 08 75 fc 00       	mov    esi,0xfc7508
  d61030:	4c 89 f7             	mov    rdi,r14
  d61033:	e8 c0 3e 7f ff       	call   554ef8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::compare(wchar_t const*) const@plt>
  d61038:	85 c0                	test   eax,eax
  d6103a:	0f 85 40 02 00 00    	jne    d61280 <parseEffects()+0x990>
  d61040:	41 c7 87 c0 59 50 01 01 00 00 00 	mov    DWORD PTR [r15+0x15059c0],0x1
  d6104b:	48 8d 5c 24 70       	lea    rbx,[rsp+0x70]
  d61050:	48 8d 94 24 dc 01 00 00 	lea    rdx,[rsp+0x1dc]
  d61058:	be 8c 82 ff 00       	mov    esi,0xff828c
  d6105d:	48 89 df             	mov    rdi,rbx
  d61060:	e8 f3 4d 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d61065:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d61069:	0f 87 11 01 00 00    	ja     d61180 <parseEffects()+0x890>
  d6106f:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d61074:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d61077:	ba ff ff ff ff       	mov    edx,0xffffffff
  d6107c:	48 89 de             	mov    rsi,rbx
  d6107f:	e8 8c e2 ef ff       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  d61084:	48 8b 7c 24 70       	mov    rdi,QWORD PTR [rsp+0x70]
  d61089:	41 89 87 00 55 50 01 	mov    DWORD PTR [r15+0x1505500],eax
  d61090:	48 83 ef 18          	sub    rdi,0x18
  d61094:	49 39 fc             	cmp    r12,rdi
  d61097:	0f 85 64 02 00 00    	jne    d61301 <parseEffects()+0xa11>
  d6109d:	48 8d 5c 24 60       	lea    rbx,[rsp+0x60]
  d610a2:	48 8d 94 24 db 01 00 00 	lea    rdx,[rsp+0x1db]
  d610aa:	be a8 82 ff 00       	mov    esi,0xff82a8
  d610af:	48 89 df             	mov    rdi,rbx
  d610b2:	e8 a1 4d 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d610b7:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d610bb:	0f 87 af 00 00 00    	ja     d61170 <parseEffects()+0x880>
  d610c1:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  d610c6:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d610c9:	ba 01 00 00 00       	mov    edx,0x1
  d610ce:	48 89 de             	mov    rsi,rbx
  d610d1:	e8 3a e2 ef ff       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  d610d6:	48 8b 7c 24 60       	mov    rdi,QWORD PTR [rsp+0x60]
  d610db:	41 89 87 60 57 50 01 	mov    DWORD PTR [r15+0x1505760],eax
  d610e2:	48 83 ef 18          	sub    rdi,0x18
  d610e6:	49 39 fc             	cmp    r12,rdi
  d610e9:	0f 85 42 02 00 00    	jne    d61331 <parseEffects()+0xa41>
  d610ef:	48 8b bc 24 90 00 00 00 	mov    rdi,QWORD PTR [rsp+0x90]
  d610f7:	48 83 ef 18          	sub    rdi,0x18
  d610fb:	49 39 fc             	cmp    r12,rdi
  d610fe:	0f 85 cd 01 00 00    	jne    d612d1 <parseEffects()+0x9e1>
  d61104:	83 c5 01             	add    ebp,0x1
  d61107:	49 83 c7 04          	add    r15,0x4
  d6110b:	49 83 c5 08          	add    r13,0x8
  d6110f:	3b 6c 24 40          	cmp    ebp,DWORD PTR [rsp+0x40]
  d61113:	73 3b                	jae    d61150 <parseEffects()+0x860>
  d61115:	48 8d 94 24 ec 01 00 00 	lea    rdx,[rsp+0x1ec]
  d6111d:	48 8d bc 24 80 01 00 00 	lea    rdi,[rsp+0x180]
  d61125:	be 98 f0 fa 00       	mov    esi,0xfaf098
  d6112a:	e8 29 4d 7f ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  d6112f:	39 6c 24 44          	cmp    DWORD PTR [rsp+0x44],ebp
  d61133:	0f 86 cf f8 ff ff    	jbe    d60a08 <parseEffects()+0x118>
  d61139:	4c 89 e8             	mov    rax,r13
  d6113c:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61141:	e9 c7 f8 ff ff       	jmp    d60a0d <parseEffects()+0x11d>
  d61146:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  d61150:	48 89 e7             	mov    rdi,rsp
  d61153:	e8 f8 03 f0 ff       	call   c61550 <CDataGroup::~CDataGroup()>
  d61158:	48 81 c4 f8 01 00 00 	add    rsp,0x1f8
  d6115f:	5b                   	pop    rbx
  d61160:	5d                   	pop    rbp
  d61161:	41 5c                	pop    r12
  d61163:	41 5d                	pop    r13
  d61165:	41 5e                	pop    r14
  d61167:	41 5f                	pop    r15
  d61169:	c3                   	ret
  d6116a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  d61170:	4c 89 e8             	mov    rax,r13
  d61173:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61178:	e9 49 ff ff ff       	jmp    d610c6 <parseEffects()+0x7d6>
  d6117d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61180:	4c 89 e8             	mov    rax,r13
  d61183:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61188:	e9 e7 fe ff ff       	jmp    d61074 <parseEffects()+0x784>
  d6118d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61190:	4c 89 e8             	mov    rax,r13
  d61193:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61198:	e9 56 fe ff ff       	jmp    d60ff3 <parseEffects()+0x703>
  d6119d:	0f 1f 00             	nop    DWORD PTR [rax]
  d611a0:	4c 89 e8             	mov    rax,r13
  d611a3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611a8:	e9 e1 fd ff ff       	jmp    d60f8e <parseEffects()+0x69e>
  d611ad:	0f 1f 00             	nop    DWORD PTR [rax]
  d611b0:	4c 89 e8             	mov    rax,r13
  d611b3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611b8:	e9 6c fd ff ff       	jmp    d60f29 <parseEffects()+0x639>
  d611bd:	0f 1f 00             	nop    DWORD PTR [rax]
  d611c0:	4c 89 e8             	mov    rax,r13
  d611c3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611c8:	e9 f7 fc ff ff       	jmp    d60ec4 <parseEffects()+0x5d4>
  d611cd:	0f 1f 00             	nop    DWORD PTR [rax]
  d611d0:	4c 89 e8             	mov    rax,r13
  d611d3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611d8:	e9 81 fc ff ff       	jmp    d60e5e <parseEffects()+0x56e>
  d611dd:	0f 1f 00             	nop    DWORD PTR [rax]
  d611e0:	4c 89 e8             	mov    rax,r13
  d611e3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611e8:	e9 0c fc ff ff       	jmp    d60df9 <parseEffects()+0x509>
  d611ed:	0f 1f 00             	nop    DWORD PTR [rax]
  d611f0:	4c 89 e8             	mov    rax,r13
  d611f3:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d611f8:	e9 97 fb ff ff       	jmp    d60d94 <parseEffects()+0x4a4>
  d611fd:	0f 1f 00             	nop    DWORD PTR [rax]
  d61200:	4c 89 e8             	mov    rax,r13
  d61203:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61208:	e9 22 fb ff ff       	jmp    d60d2f <parseEffects()+0x43f>
  d6120d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61210:	4c 89 e8             	mov    rax,r13
  d61213:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61218:	e9 ad fa ff ff       	jmp    d60cca <parseEffects()+0x3da>
  d6121d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61220:	4c 89 e8             	mov    rax,r13
  d61223:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61228:	e9 37 fa ff ff       	jmp    d60c64 <parseEffects()+0x374>
  d6122d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61230:	4c 89 e8             	mov    rax,r13
  d61233:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61238:	e9 c2 f9 ff ff       	jmp    d60bff <parseEffects()+0x30f>
  d6123d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61240:	4c 89 e8             	mov    rax,r13
  d61243:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61248:	e9 51 f9 ff ff       	jmp    d60b9e <parseEffects()+0x2ae>
  d6124d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61250:	4c 89 e8             	mov    rax,r13
  d61253:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61258:	e9 db f8 ff ff       	jmp    d60b38 <parseEffects()+0x248>
  d6125d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61260:	4c 89 e8             	mov    rax,r13
  d61263:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61268:	e9 68 f8 ff ff       	jmp    d60ad5 <parseEffects()+0x1e5>
  d6126d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61270:	4c 89 e8             	mov    rax,r13
  d61273:	48 03 44 24 38       	add    rax,QWORD PTR [rsp+0x38]
  d61278:	e9 f5 f7 ff ff       	jmp    d60a72 <parseEffects()+0x182>
  d6127d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61280:	be 4c 3d fa 00       	mov    esi,0xfa3d4c
  d61285:	4c 89 f7             	mov    rdi,r14
  d61288:	e8 6b 3c 7f ff       	call   554ef8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::compare(wchar_t const*) const@plt>
  d6128d:	83 f8 01             	cmp    eax,0x1
  d61290:	19 c0                	sbb    eax,eax
  d61292:	83 e0 02             	and    eax,0x2
  d61295:	41 89 87 c0 59 50 01 	mov    DWORD PTR [r15+0x15059c0],eax
  d6129c:	e9 aa fd ff ff       	jmp    d6104b <parseEffects()+0x75b>
  d612a1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d612a6:	48 85 c0             	test   rax,rax
  d612a9:	0f 84 ff 03 00 00    	je     d616ae <parseEffects()+0xdbe>
  d612af:	83 c8 ff             	or     eax,0xffffffff
  d612b2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d612b7:	85 c0                	test   eax,eax
  d612b9:	0f 8f 8a f7 ff ff    	jg     d60a49 <parseEffects()+0x159>
  d612bf:	48 8d b4 24 d7 01 00 00 	lea    rsi,[rsp+0x1d7]
  d612c7:	e8 7c 22 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d612cc:	e9 78 f7 ff ff       	jmp    d60a49 <parseEffects()+0x159>
  d612d1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d612d6:	48 85 c0             	test   rax,rax
  d612d9:	0f 84 eb 03 00 00    	je     d616ca <parseEffects()+0xdda>
  d612df:	83 c8 ff             	or     eax,0xffffffff
  d612e2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d612e7:	85 c0                	test   eax,eax
  d612e9:	0f 8f 15 fe ff ff    	jg     d61104 <parseEffects()+0x814>
  d612ef:	48 8d b4 24 c5 01 00 00 	lea    rsi,[rsp+0x1c5]
  d612f7:	e8 4c 22 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d612fc:	e9 03 fe ff ff       	jmp    d61104 <parseEffects()+0x814>
  d61301:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61306:	48 85 c0             	test   rax,rax
  d61309:	0f 84 ad 03 00 00    	je     d616bc <parseEffects()+0xdcc>
  d6130f:	83 c8 ff             	or     eax,0xffffffff
  d61312:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61317:	85 c0                	test   eax,eax
  d61319:	0f 8f 7e fd ff ff    	jg     d6109d <parseEffects()+0x7ad>
  d6131f:	48 8d b4 24 c7 01 00 00 	lea    rsi,[rsp+0x1c7]
  d61327:	e8 1c 22 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6132c:	e9 6c fd ff ff       	jmp    d6109d <parseEffects()+0x7ad>
  d61331:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61336:	48 85 c0             	test   rax,rax
  d61339:	0f 84 fb 03 00 00    	je     d6173a <parseEffects()+0xe4a>
  d6133f:	83 c8 ff             	or     eax,0xffffffff
  d61342:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61347:	85 c0                	test   eax,eax
  d61349:	0f 8f a0 fd ff ff    	jg     d610ef <parseEffects()+0x7ff>
  d6134f:	48 8d b4 24 c6 01 00 00 	lea    rsi,[rsp+0x1c6]
  d61357:	e8 ec 21 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6135c:	e9 8e fd ff ff       	jmp    d610ef <parseEffects()+0x7ff>
  d61361:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61366:	48 85 c0             	test   rax,rax
  d61369:	0f 84 93 03 00 00    	je     d61702 <parseEffects()+0xe12>
  d6136f:	83 c8 ff             	or     eax,0xffffffff
  d61372:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61377:	85 c0                	test   eax,eax
  d61379:	0f 8f e9 f9 ff ff    	jg     d60d68 <parseEffects()+0x478>
  d6137f:	48 8d b4 24 cf 01 00 00 	lea    rsi,[rsp+0x1cf]
  d61387:	e8 bc 21 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6138c:	e9 d7 f9 ff ff       	jmp    d60d68 <parseEffects()+0x478>
  d61391:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61396:	48 85 c0             	test   rax,rax
  d61399:	0f 84 d3 03 00 00    	je     d61772 <parseEffects()+0xe82>
  d6139f:	83 c8 ff             	or     eax,0xffffffff
  d613a2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d613a7:	85 c0                	test   eax,eax
  d613a9:	0f 8f 4e fb ff ff    	jg     d60efd <parseEffects()+0x60d>
  d613af:	48 8d b4 24 cb 01 00 00 	lea    rsi,[rsp+0x1cb]
  d613b7:	e8 8c 21 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d613bc:	e9 3c fb ff ff       	jmp    d60efd <parseEffects()+0x60d>
  d613c1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d613c6:	48 85 c0             	test   rax,rax
  d613c9:	0f 84 17 03 00 00    	je     d616e6 <parseEffects()+0xdf6>
  d613cf:	83 c8 ff             	or     eax,0xffffffff
  d613d2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d613d7:	85 c0                	test   eax,eax
  d613d9:	0f 8f f4 f7 ff ff    	jg     d60bd3 <parseEffects()+0x2e3>
  d613df:	48 8d b4 24 d3 01 00 00 	lea    rsi,[rsp+0x1d3]
  d613e7:	e8 5c 21 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d613ec:	e9 e2 f7 ff ff       	jmp    d60bd3 <parseEffects()+0x2e3>
  d613f1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d613f6:	48 85 c0             	test   rax,rax
  d613f9:	0f 84 57 03 00 00    	je     d61756 <parseEffects()+0xe66>
  d613ff:	83 c8 ff             	or     eax,0xffffffff
  d61402:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61407:	85 c0                	test   eax,eax
  d61409:	0f 8f b8 fb ff ff    	jg     d60fc7 <parseEffects()+0x6d7>
  d6140f:	48 8d b4 24 c9 01 00 00 	lea    rsi,[rsp+0x1c9]
  d61417:	e8 2c 21 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6141c:	e9 a6 fb ff ff       	jmp    d60fc7 <parseEffects()+0x6d7>
  d61421:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61426:	48 85 c0             	test   rax,rax
  d61429:	0f 84 ef 02 00 00    	je     d6171e <parseEffects()+0xe2e>
  d6142f:	83 c8 ff             	or     eax,0xffffffff
  d61432:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61437:	85 c0                	test   eax,eax
  d61439:	0f 8f 5f f8 ff ff    	jg     d60c9e <parseEffects()+0x3ae>
  d6143f:	48 8d b4 24 d1 01 00 00 	lea    rsi,[rsp+0x1d1]
  d61447:	e8 fc 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6144c:	e9 4d f8 ff ff       	jmp    d60c9e <parseEffects()+0x3ae>
  d61451:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61456:	48 85 c0             	test   rax,rax
  d61459:	0f 84 2f 03 00 00    	je     d6178e <parseEffects()+0xe9e>
  d6145f:	83 c8 ff             	or     eax,0xffffffff
  d61462:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61467:	85 c0                	test   eax,eax
  d61469:	0f 8f c3 f9 ff ff    	jg     d60e32 <parseEffects()+0x542>
  d6146f:	48 8d b4 24 cd 01 00 00 	lea    rsi,[rsp+0x1cd]
  d61477:	e8 cc 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6147c:	e9 b1 f9 ff ff       	jmp    d60e32 <parseEffects()+0x542>
  d61481:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61486:	48 85 c0             	test   rax,rax
  d61489:	0f 84 49 02 00 00    	je     d616d8 <parseEffects()+0xde8>
  d6148f:	83 c8 ff             	or     eax,0xffffffff
  d61492:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61497:	85 c0                	test   eax,eax
  d61499:	0f 8f 70 f6 ff ff    	jg     d60b0f <parseEffects()+0x21f>
  d6149f:	48 8d b4 24 d5 01 00 00 	lea    rsi,[rsp+0x1d5]
  d614a7:	e8 9c 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d614ac:	e9 5e f6 ff ff       	jmp    d60b0f <parseEffects()+0x21f>
  d614b1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d614b6:	48 85 c0             	test   rax,rax
  d614b9:	0f 84 89 02 00 00    	je     d61748 <parseEffects()+0xe58>
  d614bf:	83 c8 ff             	or     eax,0xffffffff
  d614c2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d614c7:	85 c0                	test   eax,eax
  d614c9:	0f 8f 5c fb ff ff    	jg     d6102b <parseEffects()+0x73b>
  d614cf:	48 8d b4 24 c8 01 00 00 	lea    rsi,[rsp+0x1c8]
  d614d7:	e8 6c 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d614dc:	e9 4a fb ff ff       	jmp    d6102b <parseEffects()+0x73b>
  d614e1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d614e6:	48 85 c0             	test   rax,rax
  d614e9:	0f 84 21 02 00 00    	je     d61710 <parseEffects()+0xe20>
  d614ef:	83 c8 ff             	or     eax,0xffffffff
  d614f2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d614f7:	85 c0                	test   eax,eax
  d614f9:	0f 8f 04 f8 ff ff    	jg     d60d03 <parseEffects()+0x413>
  d614ff:	48 8d b4 24 d0 01 00 00 	lea    rsi,[rsp+0x1d0]
  d61507:	e8 3c 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6150c:	e9 f2 f7 ff ff       	jmp    d60d03 <parseEffects()+0x413>
  d61511:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61516:	48 85 c0             	test   rax,rax
  d61519:	0f 84 61 02 00 00    	je     d61780 <parseEffects()+0xe90>
  d6151f:	83 c8 ff             	or     eax,0xffffffff
  d61522:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61527:	85 c0                	test   eax,eax
  d61529:	0f 8f 69 f9 ff ff    	jg     d60e98 <parseEffects()+0x5a8>
  d6152f:	48 8d b4 24 cc 01 00 00 	lea    rsi,[rsp+0x1cc]
  d61537:	e8 0c 20 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6153c:	e9 57 f9 ff ff       	jmp    d60e98 <parseEffects()+0x5a8>
  d61541:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61546:	48 85 c0             	test   rax,rax
  d61549:	0f 84 a5 01 00 00    	je     d616f4 <parseEffects()+0xe04>
  d6154f:	83 c8 ff             	or     eax,0xffffffff
  d61552:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61557:	85 c0                	test   eax,eax
  d61559:	0f 8f 13 f6 ff ff    	jg     d60b72 <parseEffects()+0x282>
  d6155f:	48 8d b4 24 d4 01 00 00 	lea    rsi,[rsp+0x1d4]
  d61567:	e8 dc 1f 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6156c:	e9 01 f6 ff ff       	jmp    d60b72 <parseEffects()+0x282>
  d61571:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61576:	48 85 c0             	test   rax,rax
  d61579:	0f 84 e5 01 00 00    	je     d61764 <parseEffects()+0xe74>
  d6157f:	83 c8 ff             	or     eax,0xffffffff
  d61582:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61587:	85 c0                	test   eax,eax
  d61589:	0f 8f d3 f9 ff ff    	jg     d60f62 <parseEffects()+0x672>
  d6158f:	48 8d b4 24 ca 01 00 00 	lea    rsi,[rsp+0x1ca]
  d61597:	e8 ac 1f 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6159c:	e9 c1 f9 ff ff       	jmp    d60f62 <parseEffects()+0x672>
  d615a1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d615a6:	48 85 c0             	test   rax,rax
  d615a9:	0f 84 7d 01 00 00    	je     d6172c <parseEffects()+0xe3c>
  d615af:	83 c8 ff             	or     eax,0xffffffff
  d615b2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d615b7:	85 c0                	test   eax,eax
  d615b9:	0f 8f 79 f6 ff ff    	jg     d60c38 <parseEffects()+0x348>
  d615bf:	48 8d b4 24 d2 01 00 00 	lea    rsi,[rsp+0x1d2]
  d615c7:	e8 7c 1f 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d615cc:	e9 67 f6 ff ff       	jmp    d60c38 <parseEffects()+0x348>
  d615d1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d615d6:	48 85 c0             	test   rax,rax
  d615d9:	0f 84 bd 01 00 00    	je     d6179c <parseEffects()+0xeac>
  d615df:	83 c8 ff             	or     eax,0xffffffff
  d615e2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d615e7:	85 c0                	test   eax,eax
  d615e9:	0f 8f de f7 ff ff    	jg     d60dcd <parseEffects()+0x4dd>
  d615ef:	48 8d b4 24 ce 01 00 00 	lea    rsi,[rsp+0x1ce]
  d615f7:	e8 4c 1f 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d615fc:	e9 cc f7 ff ff       	jmp    d60dcd <parseEffects()+0x4dd>
  d61601:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61606:	48 85 c0             	test   rax,rax
  d61609:	0f 84 a6 03 00 00    	je     d619b5 <parseEffects()+0x10c5>
  d6160f:	83 c8 ff             	or     eax,0xffffffff
  d61612:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61617:	85 c0                	test   eax,eax
  d61619:	0f 8f 8d f4 ff ff    	jg     d60aac <parseEffects()+0x1bc>
  d6161f:	48 8d b4 24 d6 01 00 00 	lea    rsi,[rsp+0x1d6]
  d61627:	e8 1c 1f 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d6162c:	e9 7b f4 ff ff       	jmp    d60aac <parseEffects()+0x1bc>
  d61631:	48 89 c5             	mov    rbp,rax
  d61634:	4c 89 f7             	mov    rdi,r14
  d61637:	e8 9c 32 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d6163c:	48 89 e7             	mov    rdi,rsp
  d6163f:	e8 0c ff ef ff       	call   c61550 <CDataGroup::~CDataGroup()>
  d61644:	48 89 ef             	mov    rdi,rbp
  d61647:	e8 4c 2e 7f ff       	call   554498 <_Unwind_Resume@plt>
  d6164c:	eb e3                	jmp    d61631 <parseEffects()+0xd41>
  d6164e:	48 89 c5             	mov    rbp,rax
  d61651:	eb e9                	jmp    d6163c <parseEffects()+0xd4c>
  d61653:	eb dc                	jmp    d61631 <parseEffects()+0xd41>
  d61655:	eb f7                	jmp    d6164e <parseEffects()+0xd5e>
  d61657:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  d61660:	eb cf                	jmp    d61631 <parseEffects()+0xd41>
  d61662:	eb ea                	jmp    d6164e <parseEffects()+0xd5e>
  d61664:	eb cb                	jmp    d61631 <parseEffects()+0xd41>
  d61666:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  d61670:	eb dc                	jmp    d6164e <parseEffects()+0xd5e>
  d61672:	48 8d bc 24 60 01 00 00 	lea    rdi,[rsp+0x160]
  d6167a:	48 89 c5             	mov    rbp,rax
  d6167d:	e8 56 32 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d61682:	eb b8                	jmp    d6163c <parseEffects()+0xd4c>
  d61684:	eb c8                	jmp    d6164e <parseEffects()+0xd5e>
  d61686:	48 8d bc 24 70 01 00 00 	lea    rdi,[rsp+0x170]
  d6168e:	48 89 c5             	mov    rbp,rax
  d61691:	e8 42 32 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d61696:	eb a4                	jmp    d6163c <parseEffects()+0xd4c>
  d61698:	eb b4                	jmp    d6164e <parseEffects()+0xd5e>
  d6169a:	48 8d bc 24 50 01 00 00 	lea    rdi,[rsp+0x150]
  d616a2:	48 89 c5             	mov    rbp,rax
  d616a5:	e8 2e 32 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d616aa:	eb 90                	jmp    d6163c <parseEffects()+0xd4c>
  d616ac:	eb a0                	jmp    d6164e <parseEffects()+0xd5e>
  d616ae:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616b1:	8d 50 ff             	lea    edx,[rax-0x1]
  d616b4:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616b7:	e9 fb fb ff ff       	jmp    d612b7 <parseEffects()+0x9c7>
  d616bc:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616bf:	8d 50 ff             	lea    edx,[rax-0x1]
  d616c2:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616c5:	e9 4d fc ff ff       	jmp    d61317 <parseEffects()+0xa27>
  d616ca:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616cd:	8d 50 ff             	lea    edx,[rax-0x1]
  d616d0:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616d3:	e9 0f fc ff ff       	jmp    d612e7 <parseEffects()+0x9f7>
  d616d8:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616db:	8d 50 ff             	lea    edx,[rax-0x1]
  d616de:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616e1:	e9 b1 fd ff ff       	jmp    d61497 <parseEffects()+0xba7>
  d616e6:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616e9:	8d 50 ff             	lea    edx,[rax-0x1]
  d616ec:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616ef:	e9 e3 fc ff ff       	jmp    d613d7 <parseEffects()+0xae7>
  d616f4:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d616f7:	8d 50 ff             	lea    edx,[rax-0x1]
  d616fa:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d616fd:	e9 55 fe ff ff       	jmp    d61557 <parseEffects()+0xc67>
  d61702:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61705:	8d 50 ff             	lea    edx,[rax-0x1]
  d61708:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d6170b:	e9 67 fc ff ff       	jmp    d61377 <parseEffects()+0xa87>
  d61710:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61713:	8d 50 ff             	lea    edx,[rax-0x1]
  d61716:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61719:	e9 d9 fd ff ff       	jmp    d614f7 <parseEffects()+0xc07>
  d6171e:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61721:	8d 50 ff             	lea    edx,[rax-0x1]
  d61724:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61727:	e9 0b fd ff ff       	jmp    d61437 <parseEffects()+0xb47>
  d6172c:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d6172f:	8d 50 ff             	lea    edx,[rax-0x1]
  d61732:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61735:	e9 7d fe ff ff       	jmp    d615b7 <parseEffects()+0xcc7>
  d6173a:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d6173d:	8d 50 ff             	lea    edx,[rax-0x1]
  d61740:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61743:	e9 ff fb ff ff       	jmp    d61347 <parseEffects()+0xa57>
  d61748:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d6174b:	8d 50 ff             	lea    edx,[rax-0x1]
  d6174e:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61751:	e9 71 fd ff ff       	jmp    d614c7 <parseEffects()+0xbd7>
  d61756:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61759:	8d 50 ff             	lea    edx,[rax-0x1]
  d6175c:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d6175f:	e9 a3 fc ff ff       	jmp    d61407 <parseEffects()+0xb17>
  d61764:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61767:	8d 50 ff             	lea    edx,[rax-0x1]
  d6176a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d6176d:	e9 15 fe ff ff       	jmp    d61587 <parseEffects()+0xc97>
  d61772:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61775:	8d 50 ff             	lea    edx,[rax-0x1]
  d61778:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d6177b:	e9 27 fc ff ff       	jmp    d613a7 <parseEffects()+0xab7>
  d61780:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61783:	8d 50 ff             	lea    edx,[rax-0x1]
  d61786:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61789:	e9 99 fd ff ff       	jmp    d61527 <parseEffects()+0xc37>
  d6178e:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61791:	8d 50 ff             	lea    edx,[rax-0x1]
  d61794:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61797:	e9 cb fc ff ff       	jmp    d61467 <parseEffects()+0xb77>
  d6179c:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d6179f:	8d 50 ff             	lea    edx,[rax-0x1]
  d617a2:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d617a5:	e9 3d fe ff ff       	jmp    d615e7 <parseEffects()+0xcf7>
  d617aa:	e9 82 fe ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d617af:	90                   	nop
  d617b0:	e9 99 fe ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d617b5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d617c0:	e9 6c fe ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d617c5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d617d0:	e9 79 fe ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d617d5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d617e0:	e9 4c fe ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d617e5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d617f0:	e9 59 fe ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d617f5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61800:	e9 2c fe ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d61805:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61810:	e9 39 fe ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d61815:	48 8d bc 24 80 01 00 00 	lea    rdi,[rsp+0x180]
  d6181d:	48 89 c5             	mov    rbp,rax
  d61820:	e8 b3 30 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d61825:	e9 12 fe ff ff       	jmp    d6163c <parseEffects()+0xd4c>
  d6182a:	e9 1f fe ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d6182f:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61834:	48 85 c0             	test   rax,rax
  d61837:	74 32                	je     d6186b <parseEffects()+0xf7b>
  d61839:	83 c8 ff             	or     eax,0xffffffff
  d6183c:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d61841:	85 c0                	test   eax,eax
  d61843:	0f 8f a1 f1 ff ff    	jg     d609ea <parseEffects()+0xfa>
  d61849:	48 8d b4 24 d8 01 00 00 	lea    rsi,[rsp+0x1d8]
  d61851:	e8 82 3f 7f ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  d61856:	e9 8f f1 ff ff       	jmp    d609ea <parseEffects()+0xfa>
  d6185b:	48 89 df             	mov    rdi,rbx
  d6185e:	48 89 c5             	mov    rbp,rax
  d61861:	e8 22 4a 7f ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  d61866:	e9 d1 fd ff ff       	jmp    d6163c <parseEffects()+0xd4c>
  d6186b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d6186e:	8d 50 ff             	lea    edx,[rax-0x1]
  d61871:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d61874:	eb cb                	jmp    d61841 <parseEffects()+0xf51>
  d61876:	e9 d3 fd ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d6187b:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d61880:	48 85 c0             	test   rax,rax
  d61883:	74 37                	je     d618bc <parseEffects()+0xfcc>
  d61885:	83 c8 ff             	or     eax,0xffffffff
  d61888:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d6188d:	85 c0                	test   eax,eax
  d6188f:	0f 8f fe f0 ff ff    	jg     d60993 <parseEffects()+0xa3>
  d61895:	48 8d b4 24 d9 01 00 00 	lea    rsi,[rsp+0x1d9]
  d6189d:	e8 a6 1c 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d618a2:	e9 ec f0 ff ff       	jmp    d60993 <parseEffects()+0xa3>
  d618a7:	48 89 df             	mov    rdi,rbx
  d618aa:	48 89 c5             	mov    rbp,rax
  d618ad:	e8 26 30 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d618b2:	e9 85 fd ff ff       	jmp    d6163c <parseEffects()+0xd4c>
  d618b7:	e9 92 fd ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d618bc:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d618bf:	8d 50 ff             	lea    edx,[rax-0x1]
  d618c2:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d618c5:	eb c6                	jmp    d6188d <parseEffects()+0xf9d>
  d618c7:	b8 c8 41 55 00       	mov    eax,0x5541c8
  d618cc:	48 85 c0             	test   rax,rax
  d618cf:	74 34                	je     d61905 <parseEffects()+0x1015>
  d618d1:	83 c8 ff             	or     eax,0xffffffff
  d618d4:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  d618d9:	85 c0                	test   eax,eax
  d618db:	0f 8f 73 f0 ff ff    	jg     d60954 <parseEffects()+0x64>
  d618e1:	48 8d b4 24 da 01 00 00 	lea    rsi,[rsp+0x1da]
  d618e9:	e8 5a 1c 7f ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  d618ee:	e9 61 f0 ff ff       	jmp    d60954 <parseEffects()+0x64>
  d618f3:	48 89 df             	mov    rdi,rbx
  d618f6:	48 89 c5             	mov    rbp,rax
  d618f9:	e8 da 2f 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d618fe:	66 90                	xchg   ax,ax
  d61900:	e9 3f fd ff ff       	jmp    d61644 <parseEffects()+0xd54>
  d61905:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d61908:	8d 50 ff             	lea    edx,[rax-0x1]
  d6190b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d6190e:	eb c9                	jmp    d618d9 <parseEffects()+0xfe9>
  d61910:	48 89 c5             	mov    rbp,rax
  d61913:	e9 2c fd ff ff       	jmp    d61644 <parseEffects()+0xd54>
  d61918:	48 89 df             	mov    rdi,rbx
  d6191b:	48 89 c5             	mov    rbp,rax
  d6191e:	e8 b5 2f 7f ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d61923:	e9 0c fd ff ff       	jmp    d61634 <parseEffects()+0xd44>
  d61928:	e9 04 fd ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d6192d:	0f 1f 00             	nop    DWORD PTR [rax]
  d61930:	e9 fc fc ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d61935:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61940:	eb d6                	jmp    d61918 <parseEffects()+0x1028>
  d61942:	e9 ea fc ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d61947:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  d61950:	e9 dc fc ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d61955:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61960:	e9 e9 fc ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d61965:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61970:	e9 bc fc ff ff       	jmp    d61631 <parseEffects()+0xd41>
  d61975:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61980:	e9 c9 fc ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d61985:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d61990:	e9 12 ff ff ff       	jmp    d618a7 <parseEffects()+0xfb7>
  d61995:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d619a0:	e9 a9 fc ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d619a5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  d619b0:	e9 99 fc ff ff       	jmp    d6164e <parseEffects()+0xd5e>
  d619b5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  d619b8:	8d 50 ff             	lea    edx,[rax-0x1]
  d619bb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  d619be:	66 90                	xchg   ax,ax
  d619c0:	e9 52 fc ff ff       	jmp    d61617 <parseEffects()+0xd27>
  d619c5:	90                   	nop
  d619c6:	90                   	nop
  d619c7:	90                   	nop
  d619c8:	90                   	nop
  d619c9:	90                   	nop
  d619ca:	90                   	nop
  d619cb:	90                   	nop
  d619cc:	90                   	nop
  d619cd:	90                   	nop
  d619ce:	90                   	nop
  d619cf:	90                   	nop

