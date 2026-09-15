# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000880950 <CEquipment::calculateCombatStats(bool)>:
  880950:	41 57                	push   r15
  880952:	41 56                	push   r14
  880954:	41 55                	push   r13
  880956:	41 54                	push   r12
  880958:	55                   	push   rbp
  880959:	53                   	push   rbx
  88095a:	48 89 fb             	mov    rbx,rdi
  88095d:	48 81 ec c8 02 00 00 	sub    rsp,0x2c8
  880964:	48 8d ac 24 70 02 00 00 	lea    rbp,[rsp+0x270]
  88096c:	48 8d 94 24 bf 02 00 00 	lea    rdx,[rsp+0x2bf]
  880974:	40 88 74 24 2f       	mov    BYTE PTR [rsp+0x2f],sil
  880979:	be 38 af fc 00       	mov    esi,0xfcaf38
  88097e:	48 89 ef             	mov    rdi,rbp
  880981:	e8 d2 54 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880986:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  88098d:	31 d2                	xor    edx,edx
  88098f:	48 89 ee             	mov    rsi,rbp
  880992:	e8 79 e9 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880997:	89 83 30 03 00 00    	mov    DWORD PTR [rbx+0x330],eax
  88099d:	48 8b bc 24 70 02 00 00 	mov    rdi,QWORD PTR [rsp+0x270]
  8809a5:	bd 40 45 42 01       	mov    ebp,0x1424540
  8809aa:	48 83 ef 18          	sub    rdi,0x18
  8809ae:	48 39 ef             	cmp    rdi,rbp
  8809b1:	0f 85 36 14 00 00    	jne    881ded <CEquipment::calculateCombatStats(bool)+0x149d>
  8809b7:	4c 8d a4 24 60 02 00 00 	lea    r12,[rsp+0x260]
  8809bf:	48 8d 94 24 be 02 00 00 	lea    rdx,[rsp+0x2be]
  8809c7:	be 60 af fc 00       	mov    esi,0xfcaf60
  8809cc:	4c 89 e7             	mov    rdi,r12
  8809cf:	e8 84 54 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8809d4:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  8809db:	31 d2                	xor    edx,edx
  8809dd:	4c 89 e6             	mov    rsi,r12
  8809e0:	e8 2b e9 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8809e5:	89 83 34 03 00 00    	mov    DWORD PTR [rbx+0x334],eax
  8809eb:	48 8b bc 24 60 02 00 00 	mov    rdi,QWORD PTR [rsp+0x260]
  8809f3:	48 83 ef 18          	sub    rdi,0x18
  8809f7:	48 39 fd             	cmp    rbp,rdi
  8809fa:	0f 85 73 14 00 00    	jne    881e73 <CEquipment::calculateCombatStats(bool)+0x1523>
  880a00:	4c 8d a4 24 50 02 00 00 	lea    r12,[rsp+0x250]
  880a08:	48 8d 94 24 bd 02 00 00 	lea    rdx,[rsp+0x2bd]
  880a10:	be f0 08 fd 00       	mov    esi,0xfd08f0
  880a15:	4c 89 e7             	mov    rdi,r12
  880a18:	e8 3b 54 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880a1d:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880a24:	f3 0f 10 05 dc 06 75 00 	movss  xmm0,DWORD PTR [rip+0x7506dc]        # fd1108 <typeinfo for CEquipment+0x48>
  880a2c:	4c 89 e6             	mov    rsi,r12
  880a2f:	e8 4c e8 3d 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  880a34:	48 8b bc 24 50 02 00 00 	mov    rdi,QWORD PTR [rsp+0x250]
  880a3c:	f3 0f 11 44 24 38    	movss  DWORD PTR [rsp+0x38],xmm0
  880a42:	48 83 ef 18          	sub    rdi,0x18
  880a46:	48 39 fd             	cmp    rbp,rdi
  880a49:	0f 85 b6 14 00 00    	jne    881f05 <CEquipment::calculateCombatStats(bool)+0x15b5>
  880a4f:	4c 8d a4 24 40 02 00 00 	lea    r12,[rsp+0x240]
  880a57:	48 8d 94 24 bc 02 00 00 	lea    rdx,[rsp+0x2bc]
  880a5f:	be 70 f8 fc 00       	mov    esi,0xfcf870
  880a64:	4c 89 e7             	mov    rdi,r12
  880a67:	e8 ec 53 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880a6c:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880a73:	f3 0f 10 05 bd 3d 72 00 	movss  xmm0,DWORD PTR [rip+0x723dbd]        # fa4838 <vtable for Ogre::FrameListener+0x78>
  880a7b:	4c 89 e6             	mov    rsi,r12
  880a7e:	e8 fd e7 3d 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  880a83:	48 8b bc 24 40 02 00 00 	mov    rdi,QWORD PTR [rsp+0x240]
  880a8b:	f3 0f 11 44 24 34    	movss  DWORD PTR [rsp+0x34],xmm0
  880a91:	48 83 ef 18          	sub    rdi,0x18
  880a95:	48 39 fd             	cmp    rbp,rdi
  880a98:	0f 85 25 14 00 00    	jne    881ec3 <CEquipment::calculateCombatStats(bool)+0x1573>
  880a9e:	4c 8d a4 24 30 02 00 00 	lea    r12,[rsp+0x230]
  880aa6:	48 8d 94 24 bb 02 00 00 	lea    rdx,[rsp+0x2bb]
  880aae:	be 08 09 fd 00       	mov    esi,0xfd0908
  880ab3:	4c 89 e7             	mov    rdi,r12
  880ab6:	e8 9d 53 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880abb:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880ac2:	31 d2                	xor    edx,edx
  880ac4:	4c 89 e6             	mov    rsi,r12
  880ac7:	e8 44 e8 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880acc:	48 8b bc 24 30 02 00 00 	mov    rdi,QWORD PTR [rsp+0x230]
  880ad4:	89 44 24 30          	mov    DWORD PTR [rsp+0x30],eax
  880ad8:	48 83 ef 18          	sub    rdi,0x18
  880adc:	48 39 fd             	cmp    rbp,rdi
  880adf:	0f 85 4d 13 00 00    	jne    881e32 <CEquipment::calculateCombatStats(bool)+0x14e2>
  880ae5:	4c 8d ac 24 20 02 00 00 	lea    r13,[rsp+0x220]
  880aed:	48 8d 94 24 ba 02 00 00 	lea    rdx,[rsp+0x2ba]
  880af5:	be f8 ff fa 00       	mov    esi,0xfafff8
  880afa:	4c 89 ef             	mov    rdi,r13
  880afd:	e8 56 53 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880b02:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880b09:	ba 48 0a 48 01       	mov    edx,0x1480a48
  880b0e:	4c 89 ee             	mov    rsi,r13
  880b11:	e8 5a e8 3d 00       	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  880b16:	4c 8d a4 24 10 02 00 00 	lea    r12,[rsp+0x210]
  880b1e:	48 89 c6             	mov    rsi,rax
  880b21:	4c 89 e7             	mov    rdi,r12
  880b24:	e8 67 d6 40 00       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  880b29:	48 8d bb 00 04 00 00 	lea    rdi,[rbx+0x400]
  880b30:	4c 89 e6             	mov    rsi,r12
  880b33:	e8 00 55 cd ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  880b38:	48 8b bc 24 10 02 00 00 	mov    rdi,QWORD PTR [rsp+0x210]
  880b40:	48 83 ef 18          	sub    rdi,0x18
  880b44:	48 39 fd             	cmp    rbp,rdi
  880b47:	0f 85 01 15 00 00    	jne    88204e <CEquipment::calculateCombatStats(bool)+0x16fe>
  880b4d:	48 8b bc 24 20 02 00 00 	mov    rdi,QWORD PTR [rsp+0x220]
  880b55:	48 83 ef 18          	sub    rdi,0x18
  880b59:	48 39 fd             	cmp    rbp,rdi
  880b5c:	0f 85 c0 14 00 00    	jne    882022 <CEquipment::calculateCombatStats(bool)+0x16d2>
  880b62:	4c 8d a4 24 00 02 00 00 	lea    r12,[rsp+0x200]
  880b6a:	48 8d 94 24 b9 02 00 00 	lea    rdx,[rsp+0x2b9]
  880b72:	be a0 f8 fc 00       	mov    esi,0xfcf8a0
  880b77:	4c 89 e7             	mov    rdi,r12
  880b7a:	e8 d9 52 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880b7f:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880b86:	0f 57 c0             	xorps  xmm0,xmm0
  880b89:	4c 89 e6             	mov    rsi,r12
  880b8c:	e8 ef e6 3d 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  880b91:	f3 0f 11 83 08 04 00 00 	movss  DWORD PTR [rbx+0x408],xmm0
  880b99:	48 8b bc 24 00 02 00 00 	mov    rdi,QWORD PTR [rsp+0x200]
  880ba1:	48 83 ef 18          	sub    rdi,0x18
  880ba5:	48 39 fd             	cmp    rbp,rdi
  880ba8:	0f 85 2c 14 00 00    	jne    881fda <CEquipment::calculateCombatStats(bool)+0x168a>
  880bae:	4c 8d a4 24 f0 01 00 00 	lea    r12,[rsp+0x1f0]
  880bb6:	48 8d 94 24 b8 02 00 00 	lea    rdx,[rsp+0x2b8]
  880bbe:	be d0 e9 fa 00       	mov    esi,0xfae9d0
  880bc3:	4c 89 e7             	mov    rdi,r12
  880bc6:	e8 8d 52 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880bcb:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880bd2:	ba 64 00 00 00       	mov    edx,0x64
  880bd7:	4c 89 e6             	mov    rsi,r12
  880bda:	e8 31 e7 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880bdf:	48 8b bc 24 f0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1f0]
  880be7:	89 44 24 3c          	mov    DWORD PTR [rsp+0x3c],eax
  880beb:	48 83 ef 18          	sub    rdi,0x18
  880bef:	48 39 fd             	cmp    rbp,rdi
  880bf2:	0f 85 a1 13 00 00    	jne    881f99 <CEquipment::calculateCombatStats(bool)+0x1649>
  880bf8:	4c 8d a4 24 e0 01 00 00 	lea    r12,[rsp+0x1e0]
  880c00:	48 8d 94 24 b7 02 00 00 	lea    rdx,[rsp+0x2b7]
  880c08:	be e8 f8 fc 00       	mov    esi,0xfcf8e8
  880c0d:	4c 89 e7             	mov    rdi,r12
  880c10:	e8 43 52 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880c15:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880c1c:	ba 64 00 00 00       	mov    edx,0x64
  880c21:	4c 89 e6             	mov    rsi,r12
  880c24:	e8 e7 e6 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880c29:	48 8b bc 24 e0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1e0]
  880c31:	41 89 c7             	mov    r15d,eax
  880c34:	48 83 ef 18          	sub    rdi,0x18
  880c38:	48 39 fd             	cmp    rbp,rdi
  880c3b:	0f 85 04 13 00 00    	jne    881f45 <CEquipment::calculateCombatStats(bool)+0x15f5>
  880c41:	4c 8d a4 24 d0 01 00 00 	lea    r12,[rsp+0x1d0]
  880c49:	48 8d 94 24 b6 02 00 00 	lea    rdx,[rsp+0x2b6]
  880c51:	be 28 f9 fc 00       	mov    esi,0xfcf928
  880c56:	4c 89 e7             	mov    rdi,r12
  880c59:	e8 fa 51 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880c5e:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880c65:	ba 64 00 00 00       	mov    edx,0x64
  880c6a:	4c 89 e6             	mov    rsi,r12
  880c6d:	e8 9e e6 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880c72:	48 8b bc 24 d0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1d0]
  880c7a:	41 89 c6             	mov    r14d,eax
  880c7d:	48 83 ef 18          	sub    rdi,0x18
  880c81:	48 39 fd             	cmp    rbp,rdi
  880c84:	0f 85 e8 10 00 00    	jne    881d72 <CEquipment::calculateCombatStats(bool)+0x1422>
  880c8a:	4c 8d a4 24 c0 01 00 00 	lea    r12,[rsp+0x1c0]
  880c92:	48 8d 94 24 b5 02 00 00 	lea    rdx,[rsp+0x2b5]
  880c9a:	be 00 d2 fc 00       	mov    esi,0xfcd200
  880c9f:	4c 89 e7             	mov    rdi,r12
  880ca2:	e8 b1 51 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880ca7:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880cae:	31 d2                	xor    edx,edx
  880cb0:	4c 89 e6             	mov    rsi,r12
  880cb3:	e8 58 e6 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880cb8:	89 83 38 03 00 00    	mov    DWORD PTR [rbx+0x338],eax
  880cbe:	48 8b bc 24 c0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1c0]
  880cc6:	48 83 ef 18          	sub    rdi,0x18
  880cca:	48 39 fd             	cmp    rbp,rdi
  880ccd:	0f 85 52 10 00 00    	jne    881d25 <CEquipment::calculateCombatStats(bool)+0x13d5>
  880cd3:	4c 8d a4 24 b0 01 00 00 	lea    r12,[rsp+0x1b0]
  880cdb:	48 8d 94 24 b4 02 00 00 	lea    rdx,[rsp+0x2b4]
  880ce3:	be 68 f9 fc 00       	mov    esi,0xfcf968
  880ce8:	4c 89 e7             	mov    rdi,r12
  880ceb:	e8 68 51 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880cf0:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880cf7:	31 d2                	xor    edx,edx
  880cf9:	4c 89 e6             	mov    rsi,r12
  880cfc:	e8 0f e6 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880d01:	48 8b bc 24 b0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1b0]
  880d09:	41 89 c5             	mov    r13d,eax
  880d0c:	48 83 ef 18          	sub    rdi,0x18
  880d10:	48 39 fd             	cmp    rbp,rdi
  880d13:	0f 85 f5 0e 00 00    	jne    881c0e <CEquipment::calculateCombatStats(bool)+0x12be>
  880d19:	4c 8d a4 24 a0 01 00 00 	lea    r12,[rsp+0x1a0]
  880d21:	48 8d 94 24 b3 02 00 00 	lea    rdx,[rsp+0x2b3]
  880d29:	be 90 f9 fc 00       	mov    esi,0xfcf990
  880d2e:	4c 89 e7             	mov    rdi,r12
  880d31:	e8 22 51 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880d36:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880d3d:	31 d2                	xor    edx,edx
  880d3f:	4c 89 e6             	mov    rsi,r12
  880d42:	e8 c9 e5 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880d47:	48 8b bc 24 a0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1a0]
  880d4f:	48 83 ef 18          	sub    rdi,0x18
  880d53:	48 39 fd             	cmp    rbp,rdi
  880d56:	0f 85 d8 0d 00 00    	jne    881b34 <CEquipment::calculateCombatStats(bool)+0x11e4>
  880d5c:	f3 41 0f 2a cf       	cvtsi2ss xmm1,r15d
  880d61:	8b 93 38 03 00 00    	mov    edx,DWORD PTR [rbx+0x338]
  880d67:	f3 41 0f 2a c6       	cvtsi2ss xmm0,r14d
  880d6c:	85 d2                	test   edx,edx
  880d6e:	f3 0f 5e 0d c6 3a 72 00 	divss  xmm1,DWORD PTR [rip+0x723ac6]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  880d76:	f3 0f 5e 05 be 3a 72 00 	divss  xmm0,DWORD PTR [rip+0x723abe]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  880d7e:	0f 85 34 08 00 00    	jne    8815b8 <CEquipment::calculateCombatStats(bool)+0xc68>
  880d84:	85 c0                	test   eax,eax
  880d86:	0f 85 4c 04 00 00    	jne    8811d8 <CEquipment::calculateCombatStats(bool)+0x888>
  880d8c:	4c 8d a4 24 90 01 00 00 	lea    r12,[rsp+0x190]
  880d94:	48 8d 94 24 b2 02 00 00 	lea    rdx,[rsp+0x2b2]
  880d9c:	be b8 f9 fc 00       	mov    esi,0xfcf9b8
  880da1:	4c 89 e7             	mov    rdi,r12
  880da4:	e8 af 50 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880da9:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880db0:	ba 64 00 00 00       	mov    edx,0x64
  880db5:	4c 89 e6             	mov    rsi,r12
  880db8:	e8 53 e5 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880dbd:	48 8b bc 24 90 01 00 00 	mov    rdi,QWORD PTR [rsp+0x190]
  880dc5:	41 89 c5             	mov    r13d,eax
  880dc8:	48 83 ef 18          	sub    rdi,0x18
  880dcc:	48 39 fd             	cmp    rbp,rdi
  880dcf:	0f 85 f3 0d 00 00    	jne    881bc8 <CEquipment::calculateCombatStats(bool)+0x1278>
  880dd5:	4c 8d a4 24 80 01 00 00 	lea    r12,[rsp+0x180]
  880ddd:	48 8d 94 24 b1 02 00 00 	lea    rdx,[rsp+0x2b1]
  880de5:	be f8 f9 fc 00       	mov    esi,0xfcf9f8
  880dea:	4c 89 e7             	mov    rdi,r12
  880ded:	e8 66 50 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880df2:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880df9:	ba 64 00 00 00       	mov    edx,0x64
  880dfe:	4c 89 e6             	mov    rsi,r12
  880e01:	e8 0a e5 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880e06:	48 8b bc 24 80 01 00 00 	mov    rdi,QWORD PTR [rsp+0x180]
  880e0e:	41 89 c4             	mov    r12d,eax
  880e11:	48 83 ef 18          	sub    rdi,0x18
  880e15:	48 39 fd             	cmp    rbp,rdi
  880e18:	0f 85 5f 0d 00 00    	jne    881b7d <CEquipment::calculateCombatStats(bool)+0x122d>
  880e1e:	8b b3 34 03 00 00    	mov    esi,DWORD PTR [rbx+0x334]
  880e24:	85 f6                	test   esi,esi
  880e26:	0f 85 ac 07 00 00    	jne    8815d8 <CEquipment::calculateCombatStats(bool)+0xc88>
  880e2c:	be 0d 00 00 00       	mov    esi,0xd
  880e31:	48 89 df             	mov    rdi,rbx
  880e34:	e8 67 54 f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  880e39:	84 c0                	test   al,al
  880e3b:	0f 84 1a 03 00 00    	je     88115b <CEquipment::calculateCombatStats(bool)+0x80b>
  880e41:	80 7c 24 2f 00       	cmp    BYTE PTR [rsp+0x2f],0x0
  880e46:	f3 0f 2a 83 38 03 00 00 	cvtsi2ss xmm0,DWORD PTR [rbx+0x338]
  880e4e:	f3 0f 11 44 24 28    	movss  DWORD PTR [rsp+0x28],xmm0
  880e54:	0f 85 8c 02 00 00    	jne    8810e6 <CEquipment::calculateCombatStats(bool)+0x796>
  880e5a:	4c 8d a4 24 70 01 00 00 	lea    r12,[rsp+0x170]
  880e62:	48 8d 94 24 b0 02 00 00 	lea    rdx,[rsp+0x2b0]
  880e6a:	be 30 fa fc 00       	mov    esi,0xfcfa30
  880e6f:	4c 89 e7             	mov    rdi,r12
  880e72:	e8 e1 4f cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880e77:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880e7e:	31 d2                	xor    edx,edx
  880e80:	4c 89 e6             	mov    rsi,r12
  880e83:	e8 88 e4 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880e88:	48 8b bc 24 70 01 00 00 	mov    rdi,QWORD PTR [rsp+0x170]
  880e90:	41 89 c4             	mov    r12d,eax
  880e93:	48 83 ef 18          	sub    rdi,0x18
  880e97:	48 39 fd             	cmp    rbp,rdi
  880e9a:	0f 85 77 13 00 00    	jne    882217 <CEquipment::calculateCombatStats(bool)+0x18c7>
  880ea0:	45 85 e4             	test   r12d,r12d
  880ea3:	7e 58                	jle    880efd <CEquipment::calculateCombatStats(bool)+0x5ad>
  880ea5:	31 c9                	xor    ecx,ecx
  880ea7:	31 d2                	xor    edx,edx
  880ea9:	31 f6                	xor    esi,esi
  880eab:	bf 38 01 00 00       	mov    edi,0x138
  880eb0:	e8 63 24 cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  880eb5:	f3 41 0f 2a cc       	cvtsi2ss xmm1,r12d
  880eba:	45 31 c0             	xor    r8d,r8d
  880ebd:	f3 0f 10 15 37 39 72 00 	movss  xmm2,DWORD PTR [rip+0x723937]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  880ec5:	31 c9                	xor    ecx,ecx
  880ec7:	f3 0f 10 05 ed 7a 74 00 	movss  xmm0,DWORD PTR [rip+0x747aed]        # fc89bc <typeinfo name for CEffectDisplayValues+0x1c>
  880ecf:	ba 01 00 00 00       	mov    edx,0x1
  880ed4:	be 27 00 00 00       	mov    esi,0x27
  880ed9:	48 89 c7             	mov    rdi,rax
  880edc:	49 89 c5             	mov    r13,rax
  880edf:	f3 0f 5e 0d 55 39 72 00 	divss  xmm1,DWORD PTR [rip+0x723955]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  880ee7:	f3 0f 59 4c 24 28    	mulss  xmm1,DWORD PTR [rsp+0x28]
  880eed:	e8 fe c7 f5 ff       	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  880ef2:	4c 89 ee             	mov    rsi,r13
  880ef5:	48 89 df             	mov    rdi,rbx
  880ef8:	e8 d3 e1 f7 ff       	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  880efd:	4c 8d a4 24 60 01 00 00 	lea    r12,[rsp+0x160]
  880f05:	48 8d 94 24 af 02 00 00 	lea    rdx,[rsp+0x2af]
  880f0d:	be 70 fa fc 00       	mov    esi,0xfcfa70
  880f12:	4c 89 e7             	mov    rdi,r12
  880f15:	e8 3e 4f cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880f1a:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880f21:	31 d2                	xor    edx,edx
  880f23:	4c 89 e6             	mov    rsi,r12
  880f26:	e8 e5 e3 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880f2b:	48 8b bc 24 60 01 00 00 	mov    rdi,QWORD PTR [rsp+0x160]
  880f33:	41 89 c4             	mov    r12d,eax
  880f36:	48 83 ef 18          	sub    rdi,0x18
  880f3a:	48 39 fd             	cmp    rbp,rdi
  880f3d:	0f 85 9e 13 00 00    	jne    8822e1 <CEquipment::calculateCombatStats(bool)+0x1991>
  880f43:	45 85 e4             	test   r12d,r12d
  880f46:	7e 58                	jle    880fa0 <CEquipment::calculateCombatStats(bool)+0x650>
  880f48:	31 c9                	xor    ecx,ecx
  880f4a:	31 d2                	xor    edx,edx
  880f4c:	31 f6                	xor    esi,esi
  880f4e:	bf 38 01 00 00       	mov    edi,0x138
  880f53:	e8 c0 23 cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  880f58:	f3 41 0f 2a cc       	cvtsi2ss xmm1,r12d
  880f5d:	45 31 c0             	xor    r8d,r8d
  880f60:	f3 0f 10 15 94 38 72 00 	movss  xmm2,DWORD PTR [rip+0x723894]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  880f68:	31 c9                	xor    ecx,ecx
  880f6a:	f3 0f 10 05 4a 7a 74 00 	movss  xmm0,DWORD PTR [rip+0x747a4a]        # fc89bc <typeinfo name for CEffectDisplayValues+0x1c>
  880f72:	ba 01 00 00 00       	mov    edx,0x1
  880f77:	be 25 00 00 00       	mov    esi,0x25
  880f7c:	48 89 c7             	mov    rdi,rax
  880f7f:	49 89 c5             	mov    r13,rax
  880f82:	f3 0f 5e 0d b2 38 72 00 	divss  xmm1,DWORD PTR [rip+0x7238b2]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  880f8a:	f3 0f 59 4c 24 28    	mulss  xmm1,DWORD PTR [rsp+0x28]
  880f90:	e8 5b c7 f5 ff       	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  880f95:	4c 89 ee             	mov    rsi,r13
  880f98:	48 89 df             	mov    rdi,rbx
  880f9b:	e8 30 e1 f7 ff       	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  880fa0:	4c 8d a4 24 50 01 00 00 	lea    r12,[rsp+0x150]
  880fa8:	48 8d 94 24 ae 02 00 00 	lea    rdx,[rsp+0x2ae]
  880fb0:	be a0 fa fc 00       	mov    esi,0xfcfaa0
  880fb5:	4c 89 e7             	mov    rdi,r12
  880fb8:	e8 9b 4e cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880fbd:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880fc4:	31 d2                	xor    edx,edx
  880fc6:	4c 89 e6             	mov    rsi,r12
  880fc9:	e8 42 e3 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  880fce:	48 8b bc 24 50 01 00 00 	mov    rdi,QWORD PTR [rsp+0x150]
  880fd6:	41 89 c4             	mov    r12d,eax
  880fd9:	48 83 ef 18          	sub    rdi,0x18
  880fdd:	48 39 fd             	cmp    rbp,rdi
  880fe0:	0f 85 6e 12 00 00    	jne    882254 <CEquipment::calculateCombatStats(bool)+0x1904>
  880fe6:	45 85 e4             	test   r12d,r12d
  880fe9:	7e 58                	jle    881043 <CEquipment::calculateCombatStats(bool)+0x6f3>
  880feb:	31 c9                	xor    ecx,ecx
  880fed:	31 d2                	xor    edx,edx
  880fef:	31 f6                	xor    esi,esi
  880ff1:	bf 38 01 00 00       	mov    edi,0x138
  880ff6:	e8 1d 23 cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  880ffb:	f3 41 0f 2a cc       	cvtsi2ss xmm1,r12d
  881000:	45 31 c0             	xor    r8d,r8d
  881003:	f3 0f 10 15 f1 37 72 00 	movss  xmm2,DWORD PTR [rip+0x7237f1]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  88100b:	31 c9                	xor    ecx,ecx
  88100d:	f3 0f 10 05 a7 79 74 00 	movss  xmm0,DWORD PTR [rip+0x7479a7]        # fc89bc <typeinfo name for CEffectDisplayValues+0x1c>
  881015:	ba 01 00 00 00       	mov    edx,0x1
  88101a:	be 26 00 00 00       	mov    esi,0x26
  88101f:	48 89 c7             	mov    rdi,rax
  881022:	49 89 c5             	mov    r13,rax
  881025:	f3 0f 5e 0d 0f 38 72 00 	divss  xmm1,DWORD PTR [rip+0x72380f]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  88102d:	f3 0f 59 4c 24 28    	mulss  xmm1,DWORD PTR [rsp+0x28]
  881033:	e8 b8 c6 f5 ff       	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  881038:	4c 89 ee             	mov    rsi,r13
  88103b:	48 89 df             	mov    rdi,rbx
  88103e:	e8 8d e0 f7 ff       	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  881043:	4c 8d a4 24 40 01 00 00 	lea    r12,[rsp+0x140]
  88104b:	48 8d 94 24 ad 02 00 00 	lea    rdx,[rsp+0x2ad]
  881053:	be c8 fa fc 00       	mov    esi,0xfcfac8
  881058:	4c 89 e7             	mov    rdi,r12
  88105b:	e8 f8 4d cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  881060:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  881067:	31 d2                	xor    edx,edx
  881069:	4c 89 e6             	mov    rsi,r12
  88106c:	e8 9f e2 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  881071:	48 8b bc 24 40 01 00 00 	mov    rdi,QWORD PTR [rsp+0x140]
  881079:	41 89 c4             	mov    r12d,eax
  88107c:	48 83 ef 18          	sub    rdi,0x18
  881080:	48 39 fd             	cmp    rbp,rdi
  881083:	0f 85 48 11 00 00    	jne    8821d1 <CEquipment::calculateCombatStats(bool)+0x1881>
  881089:	45 85 e4             	test   r12d,r12d
  88108c:	7e 58                	jle    8810e6 <CEquipment::calculateCombatStats(bool)+0x796>
  88108e:	31 c9                	xor    ecx,ecx
  881090:	31 d2                	xor    edx,edx
  881092:	31 f6                	xor    esi,esi
  881094:	bf 38 01 00 00       	mov    edi,0x138
  881099:	e8 7a 22 cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  88109e:	f3 41 0f 2a cc       	cvtsi2ss xmm1,r12d
  8810a3:	45 31 c0             	xor    r8d,r8d
  8810a6:	f3 0f 10 15 4e 37 72 00 	movss  xmm2,DWORD PTR [rip+0x72374e]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8810ae:	31 c9                	xor    ecx,ecx
  8810b0:	f3 0f 10 05 04 79 74 00 	movss  xmm0,DWORD PTR [rip+0x747904]        # fc89bc <typeinfo name for CEffectDisplayValues+0x1c>
  8810b8:	ba 01 00 00 00       	mov    edx,0x1
  8810bd:	be 28 00 00 00       	mov    esi,0x28
  8810c2:	48 89 c7             	mov    rdi,rax
  8810c5:	49 89 c5             	mov    r13,rax
  8810c8:	f3 0f 5e 0d 6c 37 72 00 	divss  xmm1,DWORD PTR [rip+0x72376c]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8810d0:	f3 0f 59 4c 24 28    	mulss  xmm1,DWORD PTR [rsp+0x28]
  8810d6:	e8 15 c6 f5 ff       	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  8810db:	4c 89 ee             	mov    rsi,r13
  8810de:	48 89 df             	mov    rdi,rbx
  8810e1:	e8 ea df f7 ff       	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  8810e6:	4c 8d a4 24 30 01 00 00 	lea    r12,[rsp+0x130]
  8810ee:	48 8d 94 24 ac 02 00 00 	lea    rdx,[rsp+0x2ac]
  8810f6:	be 00 fb fc 00       	mov    esi,0xfcfb00
  8810fb:	4c 89 e7             	mov    rdi,r12
  8810fe:	e8 55 4d cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  881103:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  88110a:	ba ff ff ff ff       	mov    edx,0xffffffff
  88110f:	4c 89 e6             	mov    rsi,r12
  881112:	e8 f9 e1 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  881117:	48 8b bc 24 30 01 00 00 	mov    rdi,QWORD PTR [rsp+0x130]
  88111f:	48 83 ef 18          	sub    rdi,0x18
  881123:	48 39 fd             	cmp    rbp,rdi
  881126:	0f 85 72 0c 00 00    	jne    881d9e <CEquipment::calculateCombatStats(bool)+0x144e>
  88112c:	83 f8 ff             	cmp    eax,0xffffffff
  88112f:	74 2a                	je     88115b <CEquipment::calculateCombatStats(bool)+0x80b>
  881131:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  881135:	f3 0f 5e 05 ff 36 72 00 	divss  xmm0,DWORD PTR [rip+0x7236ff]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  88113d:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  881143:	f3 0f 2c c0          	cvttss2si eax,xmm0
  881147:	85 c0                	test   eax,eax
  881149:	89 83 38 03 00 00    	mov    DWORD PTR [rbx+0x338],eax
  88114f:	0f 8e 81 06 00 00    	jle    8817d6 <CEquipment::calculateCombatStats(bool)+0xe86>
  881155:	89 83 3c 03 00 00    	mov    DWORD PTR [rbx+0x33c],eax
  88115b:	48 8b 83 58 03 00 00 	mov    rax,QWORD PTR [rbx+0x358]
  881162:	48 2b 83 50 03 00 00 	sub    rax,QWORD PTR [rbx+0x350]
  881169:	48 c1 f8 02          	sar    rax,0x2
  88116d:	48 85 c0             	test   rax,rax
  881170:	74 38                	je     8811aa <CEquipment::calculateCombatStats(bool)+0x85a>
  881172:	31 c9                	xor    ecx,ecx
  881174:	31 d2                	xor    edx,edx
  881176:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881180:	48 8b 83 80 03 00 00 	mov    rax,QWORD PTR [rbx+0x380]
  881187:	83 c2 01             	add    edx,0x1
  88118a:	c7 04 88 00 00 00 00 	mov    DWORD PTR [rax+rcx*4],0x0
  881191:	48 8b 83 58 03 00 00 	mov    rax,QWORD PTR [rbx+0x358]
  881198:	89 d1                	mov    ecx,edx
  88119a:	48 2b 83 50 03 00 00 	sub    rax,QWORD PTR [rbx+0x350]
  8811a1:	48 c1 f8 02          	sar    rax,0x2
  8811a5:	48 39 c1             	cmp    rcx,rax
  8811a8:	72 d6                	jb     881180 <CEquipment::calculateCombatStats(bool)+0x830>
  8811aa:	48 89 df             	mov    rdi,rbx
  8811ad:	e8 ee 55 03 00       	call   8b67a0 <CItem::destroyItemText()>
  8811b2:	be 08 00 00 00       	mov    esi,0x8
  8811b7:	48 89 df             	mov    rdi,rbx
  8811ba:	e8 e1 50 f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8811bf:	84 c0                	test   al,al
  8811c1:	75 65                	jne    881228 <CEquipment::calculateCombatStats(bool)+0x8d8>
  8811c3:	48 81 c4 c8 02 00 00 	add    rsp,0x2c8
  8811ca:	5b                   	pop    rbx
  8811cb:	5d                   	pop    rbp
  8811cc:	41 5c                	pop    r12
  8811ce:	41 5d                	pop    r13
  8811d0:	41 5e                	pop    r14
  8811d2:	41 5f                	pop    r15
  8811d4:	c3                   	ret
  8811d5:	0f 1f 00             	nop    DWORD PTR [rax]
  8811d8:	45 85 ed             	test   r13d,r13d
  8811db:	0f 84 ab fb ff ff    	je     880d8c <CEquipment::calculateCombatStats(bool)+0x43c>
  8811e1:	44 39 e8             	cmp    eax,r13d
  8811e4:	44 89 ee             	mov    esi,r13d
  8811e7:	44 89 ef             	mov    edi,r13d
  8811ea:	0f 4d f0             	cmovge esi,eax
  8811ed:	f3 0f 11 44 24 10    	movss  DWORD PTR [rsp+0x10],xmm0
  8811f3:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  8811f8:	e8 f3 19 41 00       	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8811fd:	f3 0f 2a d0          	cvtsi2ss xmm2,eax
  881201:	48 89 df             	mov    rdi,rbx
  881204:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  881209:	f3 0f 10 44 24 10    	movss  xmm0,DWORD PTR [rsp+0x10]
  88120f:	f3 0f 59 d1          	mulss  xmm2,xmm1
  881213:	f3 0f 59 d0          	mulss  xmm2,xmm0
  881217:	f3 0f 2c f2          	cvttss2si esi,xmm2
  88121b:	e8 a0 ce ff ff       	call   87e0c0 <CEquipment::setGraphAC(unsigned int)>
  881220:	e9 67 fb ff ff       	jmp    880d8c <CEquipment::calculateCombatStats(bool)+0x43c>
  881225:	0f 1f 00             	nop    DWORD PTR [rax]
  881228:	f3 0f 2a 83 34 03 00 00 	cvtsi2ss xmm0,DWORD PTR [rbx+0x334]
  881230:	f3 0f 5e 05 04 36 72 00 	divss  xmm0,DWORD PTR [rip+0x723604]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  881238:	4c 8d a4 24 20 01 00 00 	lea    r12,[rsp+0x120]
  881240:	48 8d 94 24 ab 02 00 00 	lea    rdx,[rsp+0x2ab]
  881248:	be 40 fb fc 00       	mov    esi,0xfcfb40
  88124d:	4c 89 e7             	mov    rdi,r12
  881250:	f3 0f 11 44 24 28    	movss  DWORD PTR [rsp+0x28],xmm0
  881256:	e8 fd 4b cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88125b:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  881262:	31 d2                	xor    edx,edx
  881264:	4c 89 e6             	mov    rsi,r12
  881267:	e8 a4 e0 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  88126c:	48 8b bc 24 20 01 00 00 	mov    rdi,QWORD PTR [rsp+0x120]
  881274:	48 83 ef 18          	sub    rdi,0x18
  881278:	48 39 fd             	cmp    rbp,rdi
  88127b:	0f 85 02 0f 00 00    	jne    882183 <CEquipment::calculateCombatStats(bool)+0x1833>
  881281:	85 c0                	test   eax,eax
  881283:	7e 1b                	jle    8812a0 <CEquipment::calculateCombatStats(bool)+0x950>
  881285:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  881289:	be 04 00 00 00       	mov    esi,0x4
  88128e:	48 89 df             	mov    rdi,rbx
  881291:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  881297:	f3 0f 2c d0          	cvttss2si edx,xmm0
  88129b:	e8 70 8b ff ff       	call   879e10 <CEquipment::addInherentDamage(EDAMAGE_TYPES, int)>
  8812a0:	4c 8d a4 24 10 01 00 00 	lea    r12,[rsp+0x110]
  8812a8:	48 8d 94 24 aa 02 00 00 	lea    rdx,[rsp+0x2aa]
  8812b0:	be 80 fb fc 00       	mov    esi,0xfcfb80
  8812b5:	4c 89 e7             	mov    rdi,r12
  8812b8:	e8 9b 4b cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8812bd:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  8812c4:	31 d2                	xor    edx,edx
  8812c6:	4c 89 e6             	mov    rsi,r12
  8812c9:	e8 42 e0 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8812ce:	48 8b bc 24 10 01 00 00 	mov    rdi,QWORD PTR [rsp+0x110]
  8812d6:	48 83 ef 18          	sub    rdi,0x18
  8812da:	48 39 fd             	cmp    rbp,rdi
  8812dd:	0f 85 c5 0d 00 00    	jne    8820a8 <CEquipment::calculateCombatStats(bool)+0x1758>
  8812e3:	85 c0                	test   eax,eax
  8812e5:	7e 1b                	jle    881302 <CEquipment::calculateCombatStats(bool)+0x9b2>
  8812e7:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8812eb:	be 02 00 00 00       	mov    esi,0x2
  8812f0:	48 89 df             	mov    rdi,rbx
  8812f3:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  8812f9:	f3 0f 2c d0          	cvttss2si edx,xmm0
  8812fd:	e8 0e 8b ff ff       	call   879e10 <CEquipment::addInherentDamage(EDAMAGE_TYPES, int)>
  881302:	4c 8d a4 24 00 01 00 00 	lea    r12,[rsp+0x100]
  88130a:	48 8d 94 24 a9 02 00 00 	lea    rdx,[rsp+0x2a9]
  881312:	be b0 fb fc 00       	mov    esi,0xfcfbb0
  881317:	4c 89 e7             	mov    rdi,r12
  88131a:	e8 39 4b cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88131f:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  881326:	31 d2                	xor    edx,edx
  881328:	4c 89 e6             	mov    rsi,r12
  88132b:	e8 e0 df 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  881330:	48 8b bc 24 00 01 00 00 	mov    rdi,QWORD PTR [rsp+0x100]
  881338:	48 83 ef 18          	sub    rdi,0x18
  88133c:	48 39 fd             	cmp    rbp,rdi
  88133f:	0f 85 9c 0d 00 00    	jne    8820e1 <CEquipment::calculateCombatStats(bool)+0x1791>
  881345:	85 c0                	test   eax,eax
  881347:	7e 1b                	jle    881364 <CEquipment::calculateCombatStats(bool)+0xa14>
  881349:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  88134d:	be 03 00 00 00       	mov    esi,0x3
  881352:	48 89 df             	mov    rdi,rbx
  881355:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  88135b:	f3 0f 2c d0          	cvttss2si edx,xmm0
  88135f:	e8 ac 8a ff ff       	call   879e10 <CEquipment::addInherentDamage(EDAMAGE_TYPES, int)>
  881364:	4c 8d a4 24 f0 00 00 00 	lea    r12,[rsp+0xf0]
  88136c:	48 8d 94 24 a8 02 00 00 	lea    rdx,[rsp+0x2a8]
  881374:	be e0 fb fc 00       	mov    esi,0xfcfbe0
  881379:	4c 89 e7             	mov    rdi,r12
  88137c:	e8 d7 4a cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  881381:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  881388:	31 d2                	xor    edx,edx
  88138a:	4c 89 e6             	mov    rsi,r12
  88138d:	e8 7e df 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  881392:	48 8b bc 24 f0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xf0]
  88139a:	48 83 ef 18          	sub    rdi,0x18
  88139e:	48 39 fd             	cmp    rbp,rdi
  8813a1:	0f 85 93 0d 00 00    	jne    88213a <CEquipment::calculateCombatStats(bool)+0x17ea>
  8813a7:	85 c0                	test   eax,eax
  8813a9:	7e 1b                	jle    8813c6 <CEquipment::calculateCombatStats(bool)+0xa76>
  8813ab:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8813af:	be 05 00 00 00       	mov    esi,0x5
  8813b4:	48 89 df             	mov    rdi,rbx
  8813b7:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  8813bd:	f3 0f 2c d0          	cvttss2si edx,xmm0
  8813c1:	e8 4a 8a ff ff       	call   879e10 <CEquipment::addInherentDamage(EDAMAGE_TYPES, int)>
  8813c6:	4c 8d a4 24 e0 00 00 00 	lea    r12,[rsp+0xe0]
  8813ce:	48 8d 94 24 a7 02 00 00 	lea    rdx,[rsp+0x2a7]
  8813d6:	be 18 fc fc 00       	mov    esi,0xfcfc18
  8813db:	4c 89 e7             	mov    rdi,r12
  8813de:	e8 75 4a cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8813e3:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  8813ea:	ba ff ff ff ff       	mov    edx,0xffffffff
  8813ef:	4c 89 e6             	mov    rsi,r12
  8813f2:	e8 19 df 3d 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8813f7:	48 8b bc 24 e0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xe0]
  8813ff:	48 83 ef 18          	sub    rdi,0x18
  881403:	48 39 fd             	cmp    rbp,rdi
  881406:	0f 85 91 0e 00 00    	jne    88229d <CEquipment::calculateCombatStats(bool)+0x194d>
  88140c:	85 c0                	test   eax,eax
  88140e:	0f 88 ac 02 00 00    	js     8816c0 <CEquipment::calculateCombatStats(bool)+0xd70>
  881414:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  881418:	f3 0f 59 44 24 28    	mulss  xmm0,DWORD PTR [rsp+0x28]
  88141e:	f3 0f 2c c0          	cvttss2si eax,xmm0
  881422:	89 83 34 03 00 00    	mov    DWORD PTR [rbx+0x334],eax
  881428:	89 c2                	mov    edx,eax
  88142a:	48 8b bb a8 02 00 00 	mov    rdi,QWORD PTR [rbx+0x2a8]
  881431:	89 83 30 03 00 00    	mov    DWORD PTR [rbx+0x330],eax
  881437:	89 93 40 03 00 00    	mov    DWORD PTR [rbx+0x340],edx
  88143d:	48 85 ff             	test   rdi,rdi
  881440:	74 11                	je     881453 <CEquipment::calculateCombatStats(bool)+0xb03>
  881442:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  881445:	ff 50 08             	call   QWORD PTR [rax+0x8]
  881448:	48 c7 83 a8 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x2a8],0x0
  881453:	48 8b bb a0 02 00 00 	mov    rdi,QWORD PTR [rbx+0x2a0]
  88145a:	48 85 ff             	test   rdi,rdi
  88145d:	74 11                	je     881470 <CEquipment::calculateCombatStats(bool)+0xb20>
  88145f:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  881462:	ff 50 08             	call   QWORD PTR [rax+0x8]
  881465:	48 c7 83 a0 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x2a0],0x0
  881470:	f3 0f 2a 44 24 3c    	cvtsi2ss xmm0,DWORD PTR [rsp+0x3c]
  881476:	f3 0f 5e 05 be 33 72 00 	divss  xmm0,DWORD PTR [rip+0x7233be]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  88147e:	be 24 00 00 00       	mov    esi,0x24
  881483:	48 89 df             	mov    rdi,rbx
  881486:	f3 0f 11 44 24 28    	movss  DWORD PTR [rsp+0x28],xmm0
  88148c:	e8 0f 4e f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  881491:	84 c0                	test   al,al
  881493:	0f 84 97 01 00 00    	je     881630 <CEquipment::calculateCombatStats(bool)+0xce0>
  881499:	4c 8d a4 24 d0 00 00 00 	lea    r12,[rsp+0xd0]
  8814a1:	48 8d 94 24 a6 02 00 00 	lea    rdx,[rsp+0x2a6]
  8814a9:	be bd 0b fd 00       	mov    esi,0xfd0bbd
  8814ae:	4c 89 e7             	mov    rdi,r12
  8814b1:	e8 42 4e cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8814b6:	31 c9                	xor    ecx,ecx
  8814b8:	31 d2                	xor    edx,edx
  8814ba:	31 f6                	xor    esi,esi
  8814bc:	bf 80 00 00 00       	mov    edi,0x80
  8814c1:	e8 52 1e cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  8814c6:	48 89 c7             	mov    rdi,rax
  8814c9:	48 89 c5             	mov    rbp,rax
  8814cc:	44 8b ab 34 03 00 00 	mov    r13d,DWORD PTR [rbx+0x334]
  8814d3:	44 8b b3 30 03 00 00 	mov    r14d,DWORD PTR [rbx+0x330]
  8814da:	e8 e1 81 4f 00       	call   d796c0 <CRunicCore::CRunicCore()>
  8814df:	48 8d 7d 10          	lea    rdi,[rbp+0x10]
  8814e3:	48 c7 45 00 90 e3 fc 00 	mov    QWORD PTR [rbp+0x0],0xfce390
  8814eb:	4c 89 e6             	mov    rsi,r12
  8814ee:	e8 b5 14 cd ff       	call   5529a8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&)@plt>
  8814f3:	c6 45 18 01          	mov    BYTE PTR [rbp+0x18],0x1
  8814f7:	c7 45 5c 00 00 00 00 	mov    DWORD PTR [rbp+0x5c],0x0
  8814fe:	c7 45 60 00 00 00 00 	mov    DWORD PTR [rbp+0x60],0x0
  881505:	c7 45 64 00 00 00 00 	mov    DWORD PTR [rbp+0x64],0x0
  88150c:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  881512:	f3 0f 11 45 68       	movss  DWORD PTR [rbp+0x68],xmm0
  881517:	f3 0f 10 44 24 34    	movss  xmm0,DWORD PTR [rsp+0x34]
  88151d:	f3 0f 11 45 6c       	movss  DWORD PTR [rbp+0x6c],xmm0
  881522:	f3 0f 10 44 24 28    	movss  xmm0,DWORD PTR [rsp+0x28]
  881528:	f3 0f 11 45 70       	movss  DWORD PTR [rbp+0x70],xmm0
  88152d:	8b 44 24 30          	mov    eax,DWORD PTR [rsp+0x30]
  881531:	c7 45 78 00 00 00 00 	mov    DWORD PTR [rbp+0x78],0x0
  881538:	89 45 74             	mov    DWORD PTR [rbp+0x74],eax
  88153b:	31 c0                	xor    eax,eax
  88153d:	0f 1f 00             	nop    DWORD PTR [rax]
  881540:	c7 44 05 24 00 00 00 00 	mov    DWORD PTR [rbp+rax*1+0x24],0x0
  881548:	c7 44 05 40 00 00 00 00 	mov    DWORD PTR [rbp+rax*1+0x40],0x0
  881550:	48 83 c0 04          	add    rax,0x4
  881554:	48 83 f8 1c          	cmp    rax,0x1c
  881558:	75 e6                	jne    881540 <CEquipment::calculateCombatStats(bool)+0xbf0>
  88155a:	44 89 6d 24          	mov    DWORD PTR [rbp+0x24],r13d
  88155e:	44 89 75 40          	mov    DWORD PTR [rbp+0x40],r14d
  881562:	48 89 ab a8 02 00 00 	mov    QWORD PTR [rbx+0x2a8],rbp
  881569:	48 8b bc 24 d0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xd0]
  881571:	48 83 ef 18          	sub    rdi,0x18
  881575:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  88157c:	0f 84 41 fc ff ff    	je     8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  881582:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881587:	48 85 c0             	test   rax,rax
  88158a:	0f 84 12 07 00 00    	je     881ca2 <CEquipment::calculateCombatStats(bool)+0x1352>
  881590:	83 c8 ff             	or     eax,0xffffffff
  881593:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881598:	85 c0                	test   eax,eax
  88159a:	0f 8f 23 fc ff ff    	jg     8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  8815a0:	48 8d b4 24 82 02 00 00 	lea    rsi,[rsp+0x282]
  8815a8:	e8 2b 42 cd ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  8815ad:	e9 11 fc ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  8815b2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  8815b8:	f3 0f 2a d2          	cvtsi2ss xmm2,edx
  8815bc:	48 89 df             	mov    rdi,rbx
  8815bf:	f3 0f 59 d1          	mulss  xmm2,xmm1
  8815c3:	f3 0f 59 d0          	mulss  xmm2,xmm0
  8815c7:	f3 0f 2c f2          	cvttss2si esi,xmm2
  8815cb:	e8 f0 ca ff ff       	call   87e0c0 <CEquipment::setGraphAC(unsigned int)>
  8815d0:	e9 b7 f7 ff ff       	jmp    880d8c <CEquipment::calculateCombatStats(bool)+0x43c>
  8815d5:	0f 1f 00             	nop    DWORD PTR [rax]
  8815d8:	8b bb 30 03 00 00    	mov    edi,DWORD PTR [rbx+0x330]
  8815de:	e8 0d 16 41 00       	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8815e3:	8b b3 8c 02 00 00    	mov    esi,DWORD PTR [rbx+0x28c]
  8815e9:	85 f6                	test   esi,esi
  8815eb:	7e 06                	jle    8815f3 <CEquipment::calculateCombatStats(bool)+0xca3>
  8815ed:	8b 83 34 03 00 00    	mov    eax,DWORD PTR [rbx+0x334]
  8815f3:	f3 41 0f 2a cd       	cvtsi2ss xmm1,r13d
  8815f8:	48 89 df             	mov    rdi,rbx
  8815fb:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8815ff:	f3 0f 5e 0d 35 32 72 00 	divss  xmm1,DWORD PTR [rip+0x723235]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  881607:	f3 0f 59 c1          	mulss  xmm0,xmm1
  88160b:	f3 41 0f 2a cc       	cvtsi2ss xmm1,r12d
  881610:	f3 0f 5e 0d 24 32 72 00 	divss  xmm1,DWORD PTR [rip+0x723224]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  881618:	f3 0f 59 c1          	mulss  xmm0,xmm1
  88161c:	f3 0f 2c f0          	cvttss2si esi,xmm0
  881620:	e8 7b c9 ff ff       	call   87dfa0 <CEquipment::setGraphDamage(unsigned int)>
  881625:	e9 02 f8 ff ff       	jmp    880e2c <CEquipment::calculateCombatStats(bool)+0x4dc>
  88162a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  881630:	be 6e 00 00 00       	mov    esi,0x6e
  881635:	48 89 df             	mov    rdi,rbx
  881638:	e8 63 4c f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  88163d:	84 c0                	test   al,al
  88163f:	0f 84 88 00 00 00    	je     8816cd <CEquipment::calculateCombatStats(bool)+0xd7d>
  881645:	48 8d ac 24 c0 00 00 00 	lea    rbp,[rsp+0xc0]
  88164d:	48 8d 94 24 a5 02 00 00 	lea    rdx,[rsp+0x2a5]
  881655:	be b8 0b fd 00       	mov    esi,0xfd0bb8
  88165a:	48 89 ef             	mov    rdi,rbp
  88165d:	e8 96 4c cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881662:	bf 80 00 00 00       	mov    edi,0x80
  881667:	e8 54 96 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  88166c:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881672:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  881677:	ba 01 00 00 00       	mov    edx,0x1
  88167c:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881683:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  881689:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  88168f:	48 89 ee             	mov    rsi,rbp
  881692:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  881698:	48 89 c7             	mov    rdi,rax
  88169b:	49 89 c4             	mov    r12,rax
  88169e:	e8 3d 80 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  8816a3:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  8816aa:	48 89 ef             	mov    rdi,rbp
  8816ad:	e8 d6 4b cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8816b2:	e9 0c fb ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  8816b7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  8816c0:	8b 93 34 03 00 00    	mov    edx,DWORD PTR [rbx+0x334]
  8816c6:	89 d0                	mov    eax,edx
  8816c8:	e9 5d fd ff ff       	jmp    88142a <CEquipment::calculateCombatStats(bool)+0xada>
  8816cd:	be 74 00 00 00       	mov    esi,0x74
  8816d2:	48 89 df             	mov    rdi,rbx
  8816d5:	e8 c6 4b f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8816da:	84 c0                	test   al,al
  8816dc:	0f 85 08 01 00 00    	jne    8817ea <CEquipment::calculateCombatStats(bool)+0xe9a>
  8816e2:	be 5a 00 00 00       	mov    esi,0x5a
  8816e7:	48 89 df             	mov    rdi,rbx
  8816ea:	e8 b1 4b f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8816ef:	84 c0                	test   al,al
  8816f1:	0f 84 65 01 00 00    	je     88185c <CEquipment::calculateCombatStats(bool)+0xf0c>
  8816f7:	48 8d ac 24 a0 00 00 00 	lea    rbp,[rsp+0xa0]
  8816ff:	48 8d 94 24 a3 02 00 00 	lea    rdx,[rsp+0x2a3]
  881707:	be c7 0b fd 00       	mov    esi,0xfd0bc7
  88170c:	48 89 ef             	mov    rdi,rbp
  88170f:	e8 e4 4b cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881714:	bf 80 00 00 00       	mov    edi,0x80
  881719:	e8 a2 95 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  88171e:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881724:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  881729:	ba 01 00 00 00       	mov    edx,0x1
  88172e:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881735:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  88173b:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  881741:	48 89 ee             	mov    rsi,rbp
  881744:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  88174a:	48 89 c7             	mov    rdi,rax
  88174d:	49 89 c4             	mov    r12,rax
  881750:	e8 8b 7f 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  881755:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  88175c:	48 89 ef             	mov    rdi,rbp
  88175f:	e8 24 4b cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881764:	48 8d ac 24 90 00 00 00 	lea    rbp,[rsp+0x90]
  88176c:	48 8d 94 24 a2 02 00 00 	lea    rdx,[rsp+0x2a2]
  881774:	be cf 0b fd 00       	mov    esi,0xfd0bcf
  881779:	48 89 ef             	mov    rdi,rbp
  88177c:	e8 77 4b cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881781:	bf 80 00 00 00       	mov    edi,0x80
  881786:	e8 35 95 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  88178b:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881791:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  881796:	ba 01 00 00 00       	mov    edx,0x1
  88179b:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  8817a2:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  8817a8:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  8817ae:	48 89 ee             	mov    rsi,rbp
  8817b1:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  8817b7:	48 89 c7             	mov    rdi,rax
  8817ba:	49 89 c4             	mov    r12,rax
  8817bd:	e8 1e 7f 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  8817c2:	4c 89 a3 a8 02 00 00 	mov    QWORD PTR [rbx+0x2a8],r12
  8817c9:	48 89 ef             	mov    rdi,rbp
  8817cc:	e8 b7 4a cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8817d1:	e9 ed f9 ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  8817d6:	c7 83 38 03 00 00 01 00 00 00 	mov    DWORD PTR [rbx+0x338],0x1
  8817e0:	b8 01 00 00 00       	mov    eax,0x1
  8817e5:	e9 6b f9 ff ff       	jmp    881155 <CEquipment::calculateCombatStats(bool)+0x805>
  8817ea:	48 8d ac 24 b0 00 00 00 	lea    rbp,[rsp+0xb0]
  8817f2:	48 8d 94 24 a4 02 00 00 	lea    rdx,[rsp+0x2a4]
  8817fa:	be c1 0b fd 00       	mov    esi,0xfd0bc1
  8817ff:	48 89 ef             	mov    rdi,rbp
  881802:	e8 f1 4a cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881807:	bf 80 00 00 00       	mov    edi,0x80
  88180c:	e8 af 94 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881811:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881817:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  88181c:	ba 01 00 00 00       	mov    edx,0x1
  881821:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881828:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  88182e:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  881834:	48 89 ee             	mov    rsi,rbp
  881837:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  88183d:	48 89 c7             	mov    rdi,rax
  881840:	49 89 c4             	mov    r12,rax
  881843:	e8 98 7e 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  881848:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  88184f:	48 89 ef             	mov    rdi,rbp
  881852:	e8 31 4a cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881857:	e9 67 f9 ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  88185c:	be 62 00 00 00       	mov    esi,0x62
  881861:	48 89 df             	mov    rdi,rbx
  881864:	e8 37 4a f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  881869:	84 c0                	test   al,al
  88186b:	0f 84 dc 00 00 00    	je     88194d <CEquipment::calculateCombatStats(bool)+0xffd>
  881871:	48 8d ac 24 80 00 00 00 	lea    rbp,[rsp+0x80]
  881879:	48 8d 94 24 a1 02 00 00 	lea    rdx,[rsp+0x2a1]
  881881:	be d7 0b fd 00       	mov    esi,0xfd0bd7
  881886:	48 89 ef             	mov    rdi,rbp
  881889:	e8 6a 4a cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  88188e:	bf 80 00 00 00       	mov    edi,0x80
  881893:	e8 28 94 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881898:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  88189e:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  8818a3:	ba 01 00 00 00       	mov    edx,0x1
  8818a8:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  8818af:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  8818b5:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  8818bb:	48 89 ee             	mov    rsi,rbp
  8818be:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  8818c4:	48 89 c7             	mov    rdi,rax
  8818c7:	49 89 c4             	mov    r12,rax
  8818ca:	e8 11 7e 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  8818cf:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  8818d6:	48 89 ef             	mov    rdi,rbp
  8818d9:	e8 aa 49 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8818de:	48 8d 6c 24 70       	lea    rbp,[rsp+0x70]
  8818e3:	48 8d 94 24 a0 02 00 00 	lea    rdx,[rsp+0x2a0]
  8818eb:	be dd 0b fd 00       	mov    esi,0xfd0bdd
  8818f0:	48 89 ef             	mov    rdi,rbp
  8818f3:	e8 00 4a cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8818f8:	bf 80 00 00 00       	mov    edi,0x80
  8818fd:	e8 be 93 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881902:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881908:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  88190d:	ba 01 00 00 00       	mov    edx,0x1
  881912:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881919:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  88191f:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  881925:	48 89 ee             	mov    rsi,rbp
  881928:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  88192e:	48 89 c7             	mov    rdi,rax
  881931:	49 89 c4             	mov    r12,rax
  881934:	e8 a7 7d 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  881939:	4c 89 a3 a8 02 00 00 	mov    QWORD PTR [rbx+0x2a8],r12
  881940:	48 89 ef             	mov    rdi,rbp
  881943:	e8 40 49 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881948:	e9 76 f8 ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  88194d:	be 69 00 00 00       	mov    esi,0x69
  881952:	48 89 df             	mov    rdi,rbx
  881955:	e8 46 49 f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  88195a:	84 c0                	test   al,al
  88195c:	74 6f                	je     8819cd <CEquipment::calculateCombatStats(bool)+0x107d>
  88195e:	48 8d 6c 24 60       	lea    rbp,[rsp+0x60]
  881963:	48 8d 94 24 9f 02 00 00 	lea    rdx,[rsp+0x29f]
  88196b:	be e3 0b fd 00       	mov    esi,0xfd0be3
  881970:	48 89 ef             	mov    rdi,rbp
  881973:	e8 80 49 cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881978:	bf 80 00 00 00       	mov    edi,0x80
  88197d:	e8 3e 93 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881982:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881988:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  88198d:	ba 01 00 00 00       	mov    edx,0x1
  881992:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881999:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  88199f:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  8819a5:	48 89 ee             	mov    rsi,rbp
  8819a8:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  8819ae:	48 89 c7             	mov    rdi,rax
  8819b1:	49 89 c4             	mov    r12,rax
  8819b4:	e8 27 7d 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  8819b9:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  8819c0:	48 89 ef             	mov    rdi,rbp
  8819c3:	e8 c0 48 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8819c8:	e9 f6 f7 ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  8819cd:	be 3d 00 00 00       	mov    esi,0x3d
  8819d2:	48 89 df             	mov    rdi,rbx
  8819d5:	e8 c6 48 f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8819da:	84 c0                	test   al,al
  8819dc:	75 80                	jne    88195e <CEquipment::calculateCombatStats(bool)+0x100e>
  8819de:	48 8d 6c 24 50       	lea    rbp,[rsp+0x50]
  8819e3:	48 8d 94 24 9e 02 00 00 	lea    rdx,[rsp+0x29e]
  8819eb:	be f2 0b fd 00       	mov    esi,0xfd0bf2
  8819f0:	48 89 ef             	mov    rdi,rbp
  8819f3:	e8 00 49 cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8819f8:	bf 80 00 00 00       	mov    edi,0x80
  8819fd:	e8 be 92 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881a02:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881a08:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  881a0d:	ba 01 00 00 00       	mov    edx,0x1
  881a12:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881a19:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  881a1f:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  881a25:	48 89 ee             	mov    rsi,rbp
  881a28:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  881a2e:	48 89 c7             	mov    rdi,rax
  881a31:	49 89 c4             	mov    r12,rax
  881a34:	e8 a7 7c 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  881a39:	4c 89 a3 a0 02 00 00 	mov    QWORD PTR [rbx+0x2a0],r12
  881a40:	48 89 ef             	mov    rdi,rbp
  881a43:	e8 40 48 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881a48:	48 8d 6c 24 40       	lea    rbp,[rsp+0x40]
  881a4d:	48 8d 94 24 9d 02 00 00 	lea    rdx,[rsp+0x29d]
  881a55:	be eb 0b fd 00       	mov    esi,0xfd0beb
  881a5a:	48 89 ef             	mov    rdi,rbp
  881a5d:	e8 96 48 cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  881a62:	bf 80 00 00 00       	mov    edi,0x80
  881a67:	e8 54 92 fd ff       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  881a6c:	8b 8b 30 03 00 00    	mov    ecx,DWORD PTR [rbx+0x330]
  881a72:	44 8b 4c 24 30       	mov    r9d,DWORD PTR [rsp+0x30]
  881a77:	ba 01 00 00 00       	mov    edx,0x1
  881a7c:	44 8b 83 34 03 00 00 	mov    r8d,DWORD PTR [rbx+0x334]
  881a83:	f3 0f 10 54 24 28    	movss  xmm2,DWORD PTR [rsp+0x28]
  881a89:	f3 0f 10 4c 24 34    	movss  xmm1,DWORD PTR [rsp+0x34]
  881a8f:	48 89 ee             	mov    rsi,rbp
  881a92:	f3 0f 10 44 24 38    	movss  xmm0,DWORD PTR [rsp+0x38]
  881a98:	48 89 c7             	mov    rdi,rax
  881a9b:	49 89 c4             	mov    r12,rax
  881a9e:	e8 3d 7c 01 00       	call   8996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>
  881aa3:	4c 89 a3 a8 02 00 00 	mov    QWORD PTR [rbx+0x2a8],r12
  881aaa:	48 89 ef             	mov    rdi,rbp
  881aad:	e8 d6 47 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881ab2:	e9 0c f7 ff ff       	jmp    8811c3 <CEquipment::calculateCombatStats(bool)+0x873>
  881ab7:	4c 89 e7             	mov    rdi,r12
  881aba:	48 89 c3             	mov    rbx,rax
  881abd:	e8 a6 37 cd ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  881ac2:	48 89 ef             	mov    rdi,rbp
  881ac5:	e8 be 47 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881aca:	48 89 df             	mov    rdi,rbx
  881acd:	e8 c6 29 cd ff       	call   554498 <_Unwind_Resume@plt>
  881ad2:	eb e3                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881ad4:	48 89 c3             	mov    rbx,rax
  881ad7:	eb e9                	jmp    881ac2 <CEquipment::calculateCombatStats(bool)+0x1172>
  881ad9:	48 89 c3             	mov    rbx,rax
  881adc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  881ae0:	eb e8                	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  881ae2:	eb d3                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881ae4:	eb ee                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881ae6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881af0:	eb e7                	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881af2:	eb e0                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881af4:	eb e3                	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881af6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881b00:	eb b5                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881b02:	eb d0                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881b04:	eb b1                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881b06:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881b10:	eb c2                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881b12:	eb c5                	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881b14:	eb a1                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881b16:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881b20:	eb b2                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881b22:	eb b5                	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881b24:	eb 91                	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881b26:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881b30:	eb a2                	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881b32:	eb a5                	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881b34:	ba c8 41 55 00       	mov    edx,0x5541c8
  881b39:	48 85 d2             	test   rdx,rdx
  881b3c:	74 6d                	je     881bab <CEquipment::calculateCombatStats(bool)+0x125b>
  881b3e:	83 ca ff             	or     edx,0xffffffff
  881b41:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  881b46:	85 d2                	test   edx,edx
  881b48:	0f 8f 0e f2 ff ff    	jg     880d5c <CEquipment::calculateCombatStats(bool)+0x40c>
  881b4e:	48 8d b4 24 8f 02 00 00 	lea    rsi,[rsp+0x28f]
  881b56:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  881b5a:	e8 e9 19 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881b5f:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  881b63:	e9 f4 f1 ff ff       	jmp    880d5c <CEquipment::calculateCombatStats(bool)+0x40c>
  881b68:	4c 89 e7             	mov    rdi,r12
  881b6b:	48 89 c3             	mov    rbx,rax
  881b6e:	e8 65 2d cd ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  881b73:	e9 52 ff ff ff       	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  881b78:	e9 5c ff ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881b7d:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881b82:	48 85 c0             	test   rax,rax
  881b85:	74 2f                	je     881bb6 <CEquipment::calculateCombatStats(bool)+0x1266>
  881b87:	83 c8 ff             	or     eax,0xffffffff
  881b8a:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881b8f:	85 c0                	test   eax,eax
  881b91:	0f 8f 87 f2 ff ff    	jg     880e1e <CEquipment::calculateCombatStats(bool)+0x4ce>
  881b97:	48 8d b4 24 8d 02 00 00 	lea    rsi,[rsp+0x28d]
  881b9f:	e8 a4 19 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881ba4:	e9 75 f2 ff ff       	jmp    880e1e <CEquipment::calculateCombatStats(bool)+0x4ce>
  881ba9:	eb bd                	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881bab:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  881bae:	8d 4a ff             	lea    ecx,[rdx-0x1]
  881bb1:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  881bb4:	eb 90                	jmp    881b46 <CEquipment::calculateCombatStats(bool)+0x11f6>
  881bb6:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881bb9:	8d 50 ff             	lea    edx,[rax-0x1]
  881bbc:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881bbf:	eb ce                	jmp    881b8f <CEquipment::calculateCombatStats(bool)+0x123f>
  881bc1:	eb a5                	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881bc3:	e9 11 ff ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881bc8:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881bcd:	48 85 c0             	test   rax,rax
  881bd0:	74 27                	je     881bf9 <CEquipment::calculateCombatStats(bool)+0x12a9>
  881bd2:	83 c8 ff             	or     eax,0xffffffff
  881bd5:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881bda:	85 c0                	test   eax,eax
  881bdc:	0f 8f f3 f1 ff ff    	jg     880dd5 <CEquipment::calculateCombatStats(bool)+0x485>
  881be2:	48 8d b4 24 8e 02 00 00 	lea    rsi,[rsp+0x28e]
  881bea:	e8 59 19 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881bef:	e9 e1 f1 ff ff       	jmp    880dd5 <CEquipment::calculateCombatStats(bool)+0x485>
  881bf4:	e9 6f ff ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881bf9:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881bfc:	8d 50 ff             	lea    edx,[rax-0x1]
  881bff:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881c02:	eb d6                	jmp    881bda <CEquipment::calculateCombatStats(bool)+0x128a>
  881c04:	e9 d0 fe ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881c09:	e9 cb fe ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881c0e:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881c13:	48 85 c0             	test   rax,rax
  881c16:	74 27                	je     881c3f <CEquipment::calculateCombatStats(bool)+0x12ef>
  881c18:	83 c8 ff             	or     eax,0xffffffff
  881c1b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881c20:	85 c0                	test   eax,eax
  881c22:	0f 8f f1 f0 ff ff    	jg     880d19 <CEquipment::calculateCombatStats(bool)+0x3c9>
  881c28:	48 8d b4 24 90 02 00 00 	lea    rsi,[rsp+0x290]
  881c30:	e8 13 19 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881c35:	e9 df f0 ff ff       	jmp    880d19 <CEquipment::calculateCombatStats(bool)+0x3c9>
  881c3a:	e9 29 ff ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881c3f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881c42:	8d 50 ff             	lea    edx,[rax-0x1]
  881c45:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881c48:	eb d6                	jmp    881c20 <CEquipment::calculateCombatStats(bool)+0x12d0>
  881c4a:	48 89 c3             	mov    rbx,rax
  881c4d:	4c 89 ef             	mov    rdi,r13
  881c50:	e8 13 36 cd ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  881c55:	48 89 df             	mov    rdi,rbx
  881c58:	e8 3b 28 cd ff       	call   554498 <_Unwind_Resume@plt>
  881c5d:	4c 89 ef             	mov    rdi,r13
  881c60:	48 89 c3             	mov    rbx,rax
  881c63:	e8 00 36 cd ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  881c68:	e9 5d fe ff ff       	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  881c6d:	eb ee                	jmp    881c5d <CEquipment::calculateCombatStats(bool)+0x130d>
  881c6f:	48 89 ef             	mov    rdi,rbp
  881c72:	48 89 c3             	mov    rbx,rax
  881c75:	e8 a6 7c 4f 00       	call   d79920 <CRunicCore::~CRunicCore()>
  881c7a:	48 89 ef             	mov    rdi,rbp
  881c7d:	e8 e6 35 cd ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  881c82:	4c 89 e7             	mov    rdi,r12
  881c85:	e8 fe 45 cd ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  881c8a:	e9 3b fe ff ff       	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  881c8f:	48 89 c3             	mov    rbx,rax
  881c92:	eb ee                	jmp    881c82 <CEquipment::calculateCombatStats(bool)+0x1332>
  881c94:	e9 40 fe ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881c99:	48 89 c3             	mov    rbx,rax
  881c9c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  881ca0:	eb d8                	jmp    881c7a <CEquipment::calculateCombatStats(bool)+0x132a>
  881ca2:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881ca5:	8d 50 ff             	lea    edx,[rax-0x1]
  881ca8:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881cab:	e9 e8 f8 ff ff       	jmp    881598 <CEquipment::calculateCombatStats(bool)+0xc48>
  881cb0:	eb ab                	jmp    881c5d <CEquipment::calculateCombatStats(bool)+0x130d>
  881cb2:	e9 00 fe ff ff       	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881cb7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  881cc0:	e9 0f fe ff ff       	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881cc5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881cd0:	e9 04 fe ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881cd5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881ce0:	e9 f4 fd ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881ce5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881cf0:	e9 c2 fd ff ff       	jmp    881ab7 <CEquipment::calculateCombatStats(bool)+0x1167>
  881cf5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881d00:	e9 cf fd ff ff       	jmp    881ad4 <CEquipment::calculateCombatStats(bool)+0x1184>
  881d05:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881d10:	e9 c4 fd ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881d15:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  881d20:	e9 b4 fd ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881d25:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881d2a:	48 85 c0             	test   rax,rax
  881d2d:	0f 1f 00             	nop    DWORD PTR [rax]
  881d30:	74 33                	je     881d65 <CEquipment::calculateCombatStats(bool)+0x1415>
  881d32:	83 c8 ff             	or     eax,0xffffffff
  881d35:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881d3a:	85 c0                	test   eax,eax
  881d3c:	0f 8f 91 ef ff ff    	jg     880cd3 <CEquipment::calculateCombatStats(bool)+0x383>
  881d42:	48 8d b4 24 91 02 00 00 	lea    rsi,[rsp+0x291]
  881d4a:	e8 f9 17 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881d4f:	e9 7f ef ff ff       	jmp    880cd3 <CEquipment::calculateCombatStats(bool)+0x383>
  881d54:	e9 0f fe ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881d59:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  881d60:	e9 74 fd ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881d65:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881d68:	8d 50 ff             	lea    edx,[rax-0x1]
  881d6b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881d6e:	66 90                	xchg   ax,ax
  881d70:	eb c8                	jmp    881d3a <CEquipment::calculateCombatStats(bool)+0x13ea>
  881d72:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881d77:	48 85 c0             	test   rax,rax
  881d7a:	74 56                	je     881dd2 <CEquipment::calculateCombatStats(bool)+0x1482>
  881d7c:	83 c8 ff             	or     eax,0xffffffff
  881d7f:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881d84:	85 c0                	test   eax,eax
  881d86:	0f 8f fe ee ff ff    	jg     880c8a <CEquipment::calculateCombatStats(bool)+0x33a>
  881d8c:	48 8d b4 24 92 02 00 00 	lea    rsi,[rsp+0x292]
  881d94:	e8 af 17 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881d99:	e9 ec ee ff ff       	jmp    880c8a <CEquipment::calculateCombatStats(bool)+0x33a>
  881d9e:	ba c8 41 55 00       	mov    edx,0x5541c8
  881da3:	48 85 d2             	test   rdx,rdx
  881da6:	74 35                	je     881ddd <CEquipment::calculateCombatStats(bool)+0x148d>
  881da8:	83 ca ff             	or     edx,0xffffffff
  881dab:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  881db0:	85 d2                	test   edx,edx
  881db2:	0f 8f 74 f3 ff ff    	jg     88112c <CEquipment::calculateCombatStats(bool)+0x7dc>
  881db8:	48 8d b4 24 88 02 00 00 	lea    rsi,[rsp+0x288]
  881dc0:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  881dc4:	e8 7f 17 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881dc9:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  881dcd:	e9 5a f3 ff ff       	jmp    88112c <CEquipment::calculateCombatStats(bool)+0x7dc>
  881dd2:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881dd5:	8d 50 ff             	lea    edx,[rax-0x1]
  881dd8:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881ddb:	eb a7                	jmp    881d84 <CEquipment::calculateCombatStats(bool)+0x1434>
  881ddd:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  881de0:	8d 4a ff             	lea    ecx,[rdx-0x1]
  881de3:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  881de6:	eb c8                	jmp    881db0 <CEquipment::calculateCombatStats(bool)+0x1460>
  881de8:	e9 ec fc ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881ded:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881df2:	48 85 c0             	test   rax,rax
  881df5:	0f 84 ba 00 00 00    	je     881eb5 <CEquipment::calculateCombatStats(bool)+0x1565>
  881dfb:	83 c8 ff             	or     eax,0xffffffff
  881dfe:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881e03:	85 c0                	test   eax,eax
  881e05:	0f 8f ac eb ff ff    	jg     8809b7 <CEquipment::calculateCombatStats(bool)+0x67>
  881e0b:	48 8d b4 24 9c 02 00 00 	lea    rsi,[rsp+0x29c]
  881e13:	e8 30 17 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881e18:	e9 9a eb ff ff       	jmp    8809b7 <CEquipment::calculateCombatStats(bool)+0x67>
  881e1d:	48 89 ef             	mov    rdi,rbp
  881e20:	48 89 c3             	mov    rbx,rax
  881e23:	e8 b0 2a cd ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  881e28:	e9 9d fc ff ff       	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  881e2d:	e9 a7 fc ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881e32:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881e37:	48 85 c0             	test   rax,rax
  881e3a:	74 2c                	je     881e68 <CEquipment::calculateCombatStats(bool)+0x1518>
  881e3c:	83 c8 ff             	or     eax,0xffffffff
  881e3f:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881e44:	85 c0                	test   eax,eax
  881e46:	0f 8f 99 ec ff ff    	jg     880ae5 <CEquipment::calculateCombatStats(bool)+0x195>
  881e4c:	48 8d b4 24 98 02 00 00 	lea    rsi,[rsp+0x298]
  881e54:	e8 ef 16 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881e59:	e9 87 ec ff ff       	jmp    880ae5 <CEquipment::calculateCombatStats(bool)+0x195>
  881e5e:	e9 05 fd ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881e63:	e9 71 fc ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881e68:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881e6b:	8d 50 ff             	lea    edx,[rax-0x1]
  881e6e:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881e71:	eb d1                	jmp    881e44 <CEquipment::calculateCombatStats(bool)+0x14f4>
  881e73:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881e78:	48 85 c0             	test   rax,rax
  881e7b:	74 27                	je     881ea4 <CEquipment::calculateCombatStats(bool)+0x1554>
  881e7d:	83 c8 ff             	or     eax,0xffffffff
  881e80:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881e85:	85 c0                	test   eax,eax
  881e87:	0f 8f 73 eb ff ff    	jg     880a00 <CEquipment::calculateCombatStats(bool)+0xb0>
  881e8d:	48 8d b4 24 9b 02 00 00 	lea    rsi,[rsp+0x29b]
  881e95:	e8 ae 16 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881e9a:	e9 61 eb ff ff       	jmp    880a00 <CEquipment::calculateCombatStats(bool)+0xb0>
  881e9f:	e9 c4 fc ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881ea4:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881ea7:	8d 50 ff             	lea    edx,[rax-0x1]
  881eaa:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881ead:	eb d6                	jmp    881e85 <CEquipment::calculateCombatStats(bool)+0x1535>
  881eaf:	90                   	nop
  881eb0:	e9 24 fc ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881eb5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881eb8:	8d 50 ff             	lea    edx,[rax-0x1]
  881ebb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881ebe:	e9 40 ff ff ff       	jmp    881e03 <CEquipment::calculateCombatStats(bool)+0x14b3>
  881ec3:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881ec8:	48 85 c0             	test   rax,rax
  881ecb:	74 27                	je     881ef4 <CEquipment::calculateCombatStats(bool)+0x15a4>
  881ecd:	83 c8 ff             	or     eax,0xffffffff
  881ed0:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881ed5:	85 c0                	test   eax,eax
  881ed7:	0f 8f c1 eb ff ff    	jg     880a9e <CEquipment::calculateCombatStats(bool)+0x14e>
  881edd:	48 8d b4 24 99 02 00 00 	lea    rsi,[rsp+0x299]
  881ee5:	e8 5e 16 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881eea:	e9 af eb ff ff       	jmp    880a9e <CEquipment::calculateCombatStats(bool)+0x14e>
  881eef:	e9 74 fc ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881ef4:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881ef7:	8d 50 ff             	lea    edx,[rax-0x1]
  881efa:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881efd:	eb d6                	jmp    881ed5 <CEquipment::calculateCombatStats(bool)+0x1585>
  881eff:	90                   	nop
  881f00:	e9 d4 fb ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881f05:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881f0a:	48 85 c0             	test   rax,rax
  881f0d:	74 6a                	je     881f79 <CEquipment::calculateCombatStats(bool)+0x1629>
  881f0f:	83 c8 ff             	or     eax,0xffffffff
  881f12:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881f17:	85 c0                	test   eax,eax
  881f19:	0f 8f 30 eb ff ff    	jg     880a4f <CEquipment::calculateCombatStats(bool)+0xff>
  881f1f:	48 8d b4 24 9a 02 00 00 	lea    rsi,[rsp+0x29a]
  881f27:	e8 1c 16 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881f2c:	e9 1e eb ff ff       	jmp    880a4f <CEquipment::calculateCombatStats(bool)+0xff>
  881f31:	e9 32 fc ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881f36:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  881f40:	e9 94 fb ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881f45:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881f4a:	48 85 c0             	test   rax,rax
  881f4d:	0f 1f 00             	nop    DWORD PTR [rax]
  881f50:	74 32                	je     881f84 <CEquipment::calculateCombatStats(bool)+0x1634>
  881f52:	83 c8 ff             	or     eax,0xffffffff
  881f55:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881f5a:	85 c0                	test   eax,eax
  881f5c:	0f 8f df ec ff ff    	jg     880c41 <CEquipment::calculateCombatStats(bool)+0x2f1>
  881f62:	48 8d b4 24 93 02 00 00 	lea    rsi,[rsp+0x293]
  881f6a:	e8 d9 15 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881f6f:	e9 cd ec ff ff       	jmp    880c41 <CEquipment::calculateCombatStats(bool)+0x2f1>
  881f74:	e9 ef fb ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881f79:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881f7c:	8d 50 ff             	lea    edx,[rax-0x1]
  881f7f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881f82:	eb 93                	jmp    881f17 <CEquipment::calculateCombatStats(bool)+0x15c7>
  881f84:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881f87:	8d 50 ff             	lea    edx,[rax-0x1]
  881f8a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881f8d:	eb cb                	jmp    881f5a <CEquipment::calculateCombatStats(bool)+0x160a>
  881f8f:	e9 d4 fb ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881f94:	e9 40 fb ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881f99:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881f9e:	48 85 c0             	test   rax,rax
  881fa1:	74 27                	je     881fca <CEquipment::calculateCombatStats(bool)+0x167a>
  881fa3:	83 c8 ff             	or     eax,0xffffffff
  881fa6:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881fab:	85 c0                	test   eax,eax
  881fad:	0f 8f 45 ec ff ff    	jg     880bf8 <CEquipment::calculateCombatStats(bool)+0x2a8>
  881fb3:	48 8d b4 24 94 02 00 00 	lea    rsi,[rsp+0x294]
  881fbb:	e8 88 15 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  881fc0:	e9 33 ec ff ff       	jmp    880bf8 <CEquipment::calculateCombatStats(bool)+0x2a8>
  881fc5:	e9 9e fb ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  881fca:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  881fcd:	8d 50 ff             	lea    edx,[rax-0x1]
  881fd0:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  881fd3:	eb d6                	jmp    881fab <CEquipment::calculateCombatStats(bool)+0x165b>
  881fd5:	e9 ff fa ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  881fda:	b8 c8 41 55 00       	mov    eax,0x5541c8
  881fdf:	48 85 c0             	test   rax,rax
  881fe2:	74 31                	je     882015 <CEquipment::calculateCombatStats(bool)+0x16c5>
  881fe4:	83 c8 ff             	or     eax,0xffffffff
  881fe7:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  881fec:	85 c0                	test   eax,eax
  881fee:	0f 8f ba eb ff ff    	jg     880bae <CEquipment::calculateCombatStats(bool)+0x25e>
  881ff4:	48 8d b4 24 95 02 00 00 	lea    rsi,[rsp+0x295]
  881ffc:	e8 47 15 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  882001:	e9 a8 eb ff ff       	jmp    880bae <CEquipment::calculateCombatStats(bool)+0x25e>
  882006:	e9 5d fb ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  88200b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  882010:	e9 c4 fa ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882015:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  882018:	8d 50 ff             	lea    edx,[rax-0x1]
  88201b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  88201e:	66 90                	xchg   ax,ax
  882020:	eb ca                	jmp    881fec <CEquipment::calculateCombatStats(bool)+0x169c>
  882022:	b8 c8 41 55 00       	mov    eax,0x5541c8
  882027:	48 85 c0             	test   rax,rax
  88202a:	74 4e                	je     88207a <CEquipment::calculateCombatStats(bool)+0x172a>
  88202c:	83 c8 ff             	or     eax,0xffffffff
  88202f:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  882034:	85 c0                	test   eax,eax
  882036:	0f 8f 26 eb ff ff    	jg     880b62 <CEquipment::calculateCombatStats(bool)+0x212>
  88203c:	48 8d b4 24 96 02 00 00 	lea    rsi,[rsp+0x296]
  882044:	e8 ff 14 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  882049:	e9 14 eb ff ff       	jmp    880b62 <CEquipment::calculateCombatStats(bool)+0x212>
  88204e:	b8 c8 41 55 00       	mov    eax,0x5541c8
  882053:	48 85 c0             	test   rax,rax
  882056:	74 2d                	je     882085 <CEquipment::calculateCombatStats(bool)+0x1735>
  882058:	83 c8 ff             	or     eax,0xffffffff
  88205b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  882060:	85 c0                	test   eax,eax
  882062:	0f 8f e5 ea ff ff    	jg     880b4d <CEquipment::calculateCombatStats(bool)+0x1fd>
  882068:	48 8d b4 24 97 02 00 00 	lea    rsi,[rsp+0x297]
  882070:	e8 d3 14 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  882075:	e9 d3 ea ff ff       	jmp    880b4d <CEquipment::calculateCombatStats(bool)+0x1fd>
  88207a:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  88207d:	8d 50 ff             	lea    edx,[rax-0x1]
  882080:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  882083:	eb af                	jmp    882034 <CEquipment::calculateCombatStats(bool)+0x16e4>
  882085:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  882088:	8d 50 ff             	lea    edx,[rax-0x1]
  88208b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  88208e:	eb d0                	jmp    882060 <CEquipment::calculateCombatStats(bool)+0x1710>
  882090:	4c 89 e7             	mov    rdi,r12
  882093:	48 89 c3             	mov    rbx,rax
  882096:	e8 3d 28 cd ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88209b:	4c 89 ef             	mov    rdi,r13
  88209e:	e8 35 28 cd ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8820a3:	e9 22 fa ff ff       	jmp    881aca <CEquipment::calculateCombatStats(bool)+0x117a>
  8820a8:	ba c8 41 55 00       	mov    edx,0x5541c8
  8820ad:	48 85 d2             	test   rdx,rdx
  8820b0:	74 78                	je     88212a <CEquipment::calculateCombatStats(bool)+0x17da>
  8820b2:	83 ca ff             	or     edx,0xffffffff
  8820b5:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  8820ba:	85 d2                	test   edx,edx
  8820bc:	0f 8f 21 f2 ff ff    	jg     8812e3 <CEquipment::calculateCombatStats(bool)+0x993>
  8820c2:	48 8d b4 24 86 02 00 00 	lea    rsi,[rsp+0x286]
  8820ca:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  8820ce:	e8 75 14 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8820d3:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  8820d7:	e9 07 f2 ff ff       	jmp    8812e3 <CEquipment::calculateCombatStats(bool)+0x993>
  8820dc:	e9 f8 f9 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  8820e1:	ba c8 41 55 00       	mov    edx,0x5541c8
  8820e6:	48 85 d2             	test   rdx,rdx
  8820e9:	74 2f                	je     88211a <CEquipment::calculateCombatStats(bool)+0x17ca>
  8820eb:	83 ca ff             	or     edx,0xffffffff
  8820ee:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  8820f3:	85 d2                	test   edx,edx
  8820f5:	0f 8f 4a f2 ff ff    	jg     881345 <CEquipment::calculateCombatStats(bool)+0x9f5>
  8820fb:	48 8d b4 24 85 02 00 00 	lea    rsi,[rsp+0x285]
  882103:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  882107:	e8 3c 14 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88210c:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  882110:	e9 30 f2 ff ff       	jmp    881345 <CEquipment::calculateCombatStats(bool)+0x9f5>
  882115:	e9 bf f9 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  88211a:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  88211d:	8d 4a ff             	lea    ecx,[rdx-0x1]
  882120:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  882123:	eb ce                	jmp    8820f3 <CEquipment::calculateCombatStats(bool)+0x17a3>
  882125:	e9 3e fa ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  88212a:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  88212d:	8d 4a ff             	lea    ecx,[rdx-0x1]
  882130:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  882133:	eb 85                	jmp    8820ba <CEquipment::calculateCombatStats(bool)+0x176a>
  882135:	e9 2e fa ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  88213a:	ba c8 41 55 00       	mov    edx,0x5541c8
  88213f:	48 85 d2             	test   rdx,rdx
  882142:	74 34                	je     882178 <CEquipment::calculateCombatStats(bool)+0x1828>
  882144:	83 ca ff             	or     edx,0xffffffff
  882147:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  88214c:	85 d2                	test   edx,edx
  88214e:	0f 8f 53 f2 ff ff    	jg     8813a7 <CEquipment::calculateCombatStats(bool)+0xa57>
  882154:	48 8d b4 24 84 02 00 00 	lea    rsi,[rsp+0x284]
  88215c:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  882160:	e8 e3 13 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  882165:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  882169:	e9 39 f2 ff ff       	jmp    8813a7 <CEquipment::calculateCombatStats(bool)+0xa57>
  88216e:	e9 66 f9 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882173:	e9 f0 f9 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  882178:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  88217b:	8d 4a ff             	lea    ecx,[rdx-0x1]
  88217e:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  882181:	eb c9                	jmp    88214c <CEquipment::calculateCombatStats(bool)+0x17fc>
  882183:	ba c8 41 55 00       	mov    edx,0x5541c8
  882188:	48 85 d2             	test   rdx,rdx
  88218b:	74 2f                	je     8821bc <CEquipment::calculateCombatStats(bool)+0x186c>
  88218d:	83 ca ff             	or     edx,0xffffffff
  882190:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  882195:	85 d2                	test   edx,edx
  882197:	0f 8f e4 f0 ff ff    	jg     881281 <CEquipment::calculateCombatStats(bool)+0x931>
  88219d:	48 8d b4 24 87 02 00 00 	lea    rsi,[rsp+0x287]
  8821a5:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  8821a9:	e8 9a 13 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8821ae:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  8821b2:	e9 ca f0 ff ff       	jmp    881281 <CEquipment::calculateCombatStats(bool)+0x931>
  8821b7:	e9 1d f9 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  8821bc:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  8821bf:	8d 4a ff             	lea    ecx,[rdx-0x1]
  8821c2:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  8821c5:	eb ce                	jmp    882195 <CEquipment::calculateCombatStats(bool)+0x1845>
  8821c7:	e9 9c f9 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  8821cc:	e9 97 f9 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  8821d1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8821d6:	48 85 c0             	test   rax,rax
  8821d9:	74 27                	je     882202 <CEquipment::calculateCombatStats(bool)+0x18b2>
  8821db:	83 c8 ff             	or     eax,0xffffffff
  8821de:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8821e3:	85 c0                	test   eax,eax
  8821e5:	0f 8f 9e ee ff ff    	jg     881089 <CEquipment::calculateCombatStats(bool)+0x739>
  8821eb:	48 8d b4 24 89 02 00 00 	lea    rsi,[rsp+0x289]
  8821f3:	e8 50 13 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8821f8:	e9 8c ee ff ff       	jmp    881089 <CEquipment::calculateCombatStats(bool)+0x739>
  8821fd:	e9 d7 f8 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882202:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  882205:	8d 50 ff             	lea    edx,[rax-0x1]
  882208:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  88220b:	eb d6                	jmp    8821e3 <CEquipment::calculateCombatStats(bool)+0x1893>
  88220d:	e9 c7 f8 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882212:	e9 51 f9 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  882217:	b8 c8 41 55 00       	mov    eax,0x5541c8
  88221c:	48 85 c0             	test   rax,rax
  88221f:	90                   	nop
  882220:	74 27                	je     882249 <CEquipment::calculateCombatStats(bool)+0x18f9>
  882222:	83 c8 ff             	or     eax,0xffffffff
  882225:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  88222a:	85 c0                	test   eax,eax
  88222c:	0f 8f 6e ec ff ff    	jg     880ea0 <CEquipment::calculateCombatStats(bool)+0x550>
  882232:	48 8d b4 24 8c 02 00 00 	lea    rsi,[rsp+0x28c]
  88223a:	e8 09 13 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88223f:	e9 5c ec ff ff       	jmp    880ea0 <CEquipment::calculateCombatStats(bool)+0x550>
  882244:	e9 1f f9 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  882249:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  88224c:	8d 50 ff             	lea    edx,[rax-0x1]
  88224f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  882252:	eb d6                	jmp    88222a <CEquipment::calculateCombatStats(bool)+0x18da>
  882254:	b8 c8 41 55 00       	mov    eax,0x5541c8
  882259:	48 85 c0             	test   rax,rax
  88225c:	74 2a                	je     882288 <CEquipment::calculateCombatStats(bool)+0x1938>
  88225e:	83 c8 ff             	or     eax,0xffffffff
  882261:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  882266:	85 c0                	test   eax,eax
  882268:	0f 8f 78 ed ff ff    	jg     880fe6 <CEquipment::calculateCombatStats(bool)+0x696>
  88226e:	48 8d b4 24 8a 02 00 00 	lea    rsi,[rsp+0x28a]
  882276:	e8 cd 12 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88227b:	e9 66 ed ff ff       	jmp    880fe6 <CEquipment::calculateCombatStats(bool)+0x696>
  882280:	48 89 c3             	mov    rbx,rax
  882283:	e9 13 fe ff ff       	jmp    88209b <CEquipment::calculateCombatStats(bool)+0x174b>
  882288:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  88228b:	8d 50 ff             	lea    edx,[rax-0x1]
  88228e:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  882291:	eb d3                	jmp    882266 <CEquipment::calculateCombatStats(bool)+0x1916>
  882293:	e9 41 f8 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882298:	e9 cb f8 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  88229d:	ba c8 41 55 00       	mov    edx,0x5541c8
  8822a2:	48 85 d2             	test   rdx,rdx
  8822a5:	74 2f                	je     8822d6 <CEquipment::calculateCombatStats(bool)+0x1986>
  8822a7:	83 ca ff             	or     edx,0xffffffff
  8822aa:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  8822af:	85 d2                	test   edx,edx
  8822b1:	0f 8f 55 f1 ff ff    	jg     88140c <CEquipment::calculateCombatStats(bool)+0xabc>
  8822b7:	48 8d b4 24 83 02 00 00 	lea    rsi,[rsp+0x283]
  8822bf:	89 44 24 20          	mov    DWORD PTR [rsp+0x20],eax
  8822c3:	e8 80 12 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8822c8:	8b 44 24 20          	mov    eax,DWORD PTR [rsp+0x20]
  8822cc:	e9 3b f1 ff ff       	jmp    88140c <CEquipment::calculateCombatStats(bool)+0xabc>
  8822d1:	e9 92 f8 ff ff       	jmp    881b68 <CEquipment::calculateCombatStats(bool)+0x1218>
  8822d6:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  8822d9:	8d 4a ff             	lea    ecx,[rdx-0x1]
  8822dc:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  8822df:	eb ce                	jmp    8822af <CEquipment::calculateCombatStats(bool)+0x195f>
  8822e1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8822e6:	48 85 c0             	test   rax,rax
  8822e9:	74 27                	je     882312 <CEquipment::calculateCombatStats(bool)+0x19c2>
  8822eb:	83 c8 ff             	or     eax,0xffffffff
  8822ee:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8822f3:	85 c0                	test   eax,eax
  8822f5:	0f 8f 48 ec ff ff    	jg     880f43 <CEquipment::calculateCombatStats(bool)+0x5f3>
  8822fb:	48 8d b4 24 8b 02 00 00 	lea    rsi,[rsp+0x28b]
  882303:	e8 40 12 cd ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  882308:	e9 36 ec ff ff       	jmp    880f43 <CEquipment::calculateCombatStats(bool)+0x5f3>
  88230d:	e9 c7 f7 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882312:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  882315:	8d 50 ff             	lea    edx,[rax-0x1]
  882318:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  88231b:	eb d6                	jmp    8822f3 <CEquipment::calculateCombatStats(bool)+0x19a3>
  88231d:	e9 b7 f7 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882322:	e9 b2 f7 ff ff       	jmp    881ad9 <CEquipment::calculateCombatStats(bool)+0x1189>
  882327:	90                   	nop
  882328:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

