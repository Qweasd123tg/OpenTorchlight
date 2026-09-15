# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x853800, 0x853932); source instructions unchanged.
  853807:	be 98 ca fc 00       	mov    esi,0xfcca98
  85380c:	4c 89 ef             	mov    rdi,r13
  85380f:	e8 44 26 d0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  853814:	31 d2                	xor    edx,edx
  853816:	4c 89 ee             	mov    rsi,r13
  853819:	4c 89 e7             	mov    rdi,r12
  85381c:	e8 0f e5 40 00       	call   c61d30 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)>
  853821:	48 8b bc 24 80 01 00 00 	mov    rdi,QWORD PTR [rsp+0x180]
  853829:	49 89 c5             	mov    r13,rax
  85382c:	48 83 ef 18          	sub    rdi,0x18
  853830:	48 39 fd             	cmp    rbp,rdi
  853833:	0f 85 a0 14 00 00    	jne    854cd9 <CCharacter::unitInit(CDataGroup*, bool)+0x2339>
  853839:	4d 85 ed             	test   r13,r13
  85383c:	0f 84 e5 00 00 00    	je     853927 <CCharacter::unitInit(CDataGroup*, bool)+0xf87>
  853842:	4c 8d b4 24 70 01 00 00 	lea    r14,[rsp+0x170]
  85384a:	48 8d 94 24 04 05 00 00 	lea    rdx,[rsp+0x504]
  853852:	be a0 4a fa 00       	mov    esi,0xfa4aa0
  853857:	4c 89 f7             	mov    rdi,r14
  85385a:	e8 f9 25 d0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  85385f:	ba 48 c3 47 01       	mov    edx,0x147c348
  853864:	4c 89 f6             	mov    rsi,r14
  853867:	4c 89 ef             	mov    rdi,r13
  85386a:	e8 01 bb 40 00       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  85386f:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  853873:	48 89 c6             	mov    rsi,rax
  853876:	e8 f5 be 51 00       	call   d6f770 <CResourceManager::getSpawnClassByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  85387b:	48 89 83 c0 06 00 00 	mov    QWORD PTR [rbx+0x6c0],rax
  853882:	48 8b bc 24 70 01 00 00 	mov    rdi,QWORD PTR [rsp+0x170]
  85388a:	48 83 ef 18          	sub    rdi,0x18
  85388e:	48 39 fd             	cmp    rbp,rdi
  853891:	0f 85 e2 13 00 00    	jne    854c79 <CCharacter::unitInit(CDataGroup*, bool)+0x22d9>
  853897:	4c 8d b4 24 60 01 00 00 	lea    r14,[rsp+0x160]
  85389f:	48 8d 94 24 03 05 00 00 	lea    rdx,[rsp+0x503]
  8538a7:	be 68 c5 fa 00       	mov    esi,0xfac568
  8538ac:	4c 89 f7             	mov    rdi,r14
  8538af:	e8 a4 25 d0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8538b4:	ba 01 00 00 00       	mov    edx,0x1
  8538b9:	4c 89 f6             	mov    rsi,r14
  8538bc:	4c 89 ef             	mov    rdi,r13
  8538bf:	e8 4c ba 40 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8538c4:	89 83 c8 06 00 00    	mov    DWORD PTR [rbx+0x6c8],eax
  8538ca:	48 8b bc 24 60 01 00 00 	mov    rdi,QWORD PTR [rsp+0x160]
  8538d2:	48 83 ef 18          	sub    rdi,0x18
  8538d6:	48 39 fd             	cmp    rbp,rdi
  8538d9:	0f 85 91 10 00 00    	jne    854970 <CCharacter::unitInit(CDataGroup*, bool)+0x1fd0>
  8538df:	4c 8d b4 24 50 01 00 00 	lea    r14,[rsp+0x150]
  8538e7:	48 8d 94 24 02 05 00 00 	lea    rdx,[rsp+0x502]
  8538ef:	be 94 c5 fa 00       	mov    esi,0xfac594
  8538f4:	4c 89 f7             	mov    rdi,r14
  8538f7:	e8 5c 25 d0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8538fc:	ba 01 00 00 00       	mov    edx,0x1
  853901:	4c 89 f6             	mov    rsi,r14
  853904:	4c 89 ef             	mov    rdi,r13
  853907:	e8 04 ba 40 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  85390c:	89 83 cc 06 00 00    	mov    DWORD PTR [rbx+0x6cc],eax
  853912:	48 8b bc 24 50 01 00 00 	mov    rdi,QWORD PTR [rsp+0x150]
  85391a:	48 83 ef 18          	sub    rdi,0x18
  85391e:	48 39 fd             	cmp    rbp,rdi
  853921:	0f 85 69 0e 00 00    	jne    854790 <CCharacter::unitInit(CDataGroup*, bool)+0x1df0>
  853927:	be 29 00 00 00       	mov    esi,0x29
  85392c:	48 89 df             	mov    rdi,rbx
  85392f:	e8 6c 29 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
