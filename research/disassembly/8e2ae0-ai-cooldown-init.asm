# Source: earlier supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Declared original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Verified source text SHA-256: 59d876125b21e8e1a3e6b0f2f242632966b705218907de1ed5172baebc30d196
# Targeted Intel-syntax excerpt; the ELF is not included. See ../monster-ai-cooldown.md.

# Range: 0x8e2ae0 <= instruction address < 0x8e2bba
  8e2ae0:	48 89 5c 24 e8       	mov    QWORD PTR [rsp-0x18],rbx
  8e2ae5:	4c 89 64 24 f8       	mov    QWORD PTR [rsp-0x8],r12
  8e2aea:	0f b6 d2             	movzx  edx,dl
  8e2aed:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
  8e2af2:	48 83 ec 28          	sub    rsp,0x28
  8e2af6:	48 89 fb             	mov    rbx,rdi
  8e2af9:	49 89 f4             	mov    r12,rsi
  8e2afc:	e8 9f fe f6 ff       	call   8529a0 <CCharacter::unitInit(CDataGroup*, bool)>
  8e2b01:	48 8d 54 24 0f       	lea    rdx,[rsp+0xf]
  8e2b06:	be a0 f8 fc 00       	mov    esi,0xfcf8a0
  8e2b0b:	48 89 e7             	mov    rdi,rsp
  8e2b0e:	e8 45 33 c7 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8e2b13:	0f 57 c0             	xorps  xmm0,xmm0
  8e2b16:	48 89 e6             	mov    rsi,rsp
  8e2b19:	4c 89 e7             	mov    rdi,r12
  8e2b1c:	e8 5f c7 37 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  8e2b21:	f3 0f 11 83 ec 07 00 00 	movss  DWORD PTR [rbx+0x7ec],xmm0
  8e2b29:	48 8b 3c 24          	mov    rdi,QWORD PTR [rsp]
  8e2b2d:	48 83 ef 18          	sub    rdi,0x18
  8e2b31:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  8e2b38:	75 3b                	jne    8e2b75 <CMonster::unitInit(CDataGroup*, bool)+0x95>
  8e2b3a:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e2b3d:	48 89 df             	mov    rdi,rbx
  8e2b40:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  8e2b46:	48 85 c0             	test   rax,rax
  8e2b49:	74 16                	je     8e2b61 <CMonster::unitInit(CDataGroup*, bool)+0x81>
  8e2b4b:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e2b4e:	48 89 df             	mov    rdi,rbx
  8e2b51:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  8e2b57:	c7 80 4c 02 00 00 0a d7 23 3c 	mov    DWORD PTR [rax+0x24c],0x3c23d70a
  8e2b61:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
  8e2b66:	48 8b 6c 24 18       	mov    rbp,QWORD PTR [rsp+0x18]
  8e2b6b:	4c 8b 64 24 20       	mov    r12,QWORD PTR [rsp+0x20]
  8e2b70:	48 83 c4 28          	add    rsp,0x28
  8e2b74:	c3                   	ret
  8e2b75:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8e2b7a:	48 85 c0             	test   rax,rax
  8e2b7d:	74 30                	je     8e2baf <CMonster::unitInit(CDataGroup*, bool)+0xcf>
  8e2b7f:	83 c8 ff             	or     eax,0xffffffff
  8e2b82:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8e2b87:	85 c0                	test   eax,eax
  8e2b89:	7f af                	jg     8e2b3a <CMonster::unitInit(CDataGroup*, bool)+0x5a>
  8e2b8b:	48 8d 74 24 0e       	lea    rsi,[rsp+0xe]
  8e2b90:	e8 b3 09 c7 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8e2b95:	eb a3                	jmp    8e2b3a <CMonster::unitInit(CDataGroup*, bool)+0x5a>
  8e2b97:	48 89 e7             	mov    rdi,rsp
  8e2b9a:	48 89 c3             	mov    rbx,rax
  8e2b9d:	e8 36 1d c7 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8e2ba2:	48 89 df             	mov    rdi,rbx
  8e2ba5:	e8 ee 18 c7 ff       	call   554498 <_Unwind_Resume@plt>
  8e2baa:	48 89 c3             	mov    rbx,rax
  8e2bad:	eb f3                	jmp    8e2ba2 <CMonster::unitInit(CDataGroup*, bool)+0xc2>
  8e2baf:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8e2bb2:	8d 50 ff             	lea    edx,[rax-0x1]
  8e2bb5:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8e2bb8:	eb cd                	jmp    8e2b87 <CMonster::unitInit(CDataGroup*, bool)+0xa7>
