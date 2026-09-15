# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0xc61d30, 0xc61e00); source instructions unchanged.
  c61d30:	41 55                	push   r13
  c61d32:	41 89 d5             	mov    r13d,edx
  c61d35:	41 54                	push   r12
  c61d37:	49 89 f4             	mov    r12,rsi
  c61d3a:	55                   	push   rbp
  c61d3b:	48 89 fd             	mov    rbp,rdi
  c61d3e:	53                   	push   rbx
  c61d3f:	48 83 ec 08          	sub    rsp,0x8
  c61d43:	8b 47 40             	mov    eax,DWORD PTR [rdi+0x40]
  c61d46:	85 c0                	test   eax,eax
  c61d48:	74 0e                	je     c61d58 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x28>
  c61d4a:	31 db                	xor    ebx,ebx
  c61d4c:	83 f8 ff             	cmp    eax,0xffffffff
  c61d4f:	75 24                	jne    c61d75 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x45>
  c61d51:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  c61d58:	31 c0                	xor    eax,eax
  c61d5a:	45 84 ed             	test   r13b,r13b
  c61d5d:	75 49                	jne    c61da8 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x78>
  c61d5f:	48 83 c4 08          	add    rsp,0x8
  c61d63:	5b                   	pop    rbx
  c61d64:	5d                   	pop    rbp
  c61d65:	41 5c                	pop    r12
  c61d67:	41 5d                	pop    r13
  c61d69:	c3                   	ret
  c61d6a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  c61d70:	83 f8 ff             	cmp    eax,0xffffffff
  c61d73:	74 e3                	je     c61d58 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x28>
  c61d75:	39 5d 44             	cmp    DWORD PTR [rbp+0x44],ebx
  c61d78:	77 46                	ja     c61dc0 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x90>
  c61d7a:	48 8b 45 38          	mov    rax,QWORD PTR [rbp+0x38]
  c61d7e:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  c61d81:	e8 9a d0 ff ff       	call   c5ee20 <CDataGroup::GetGroupName()>
  c61d86:	49 8b 34 24          	mov    rsi,QWORD PTR [r12]
  c61d8a:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  c61d8d:	48 8b 57 e8          	mov    rdx,QWORD PTR [rdi-0x18]
  c61d91:	48 3b 56 e8          	cmp    rdx,QWORD PTR [rsi-0x18]
  c61d95:	74 39                	je     c61dd0 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0xa0>
  c61d97:	8b 45 40             	mov    eax,DWORD PTR [rbp+0x40]
  c61d9a:	83 c3 01             	add    ebx,0x1
  c61d9d:	39 c3                	cmp    ebx,eax
  c61d9f:	72 cf                	jb     c61d70 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x40>
  c61da1:	31 c0                	xor    eax,eax
  c61da3:	45 84 ed             	test   r13b,r13b
  c61da6:	74 b7                	je     c61d5f <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x2f>
  c61da8:	48 83 c4 08          	add    rsp,0x8
  c61dac:	48 89 ef             	mov    rdi,rbp
  c61daf:	4c 89 e6             	mov    rsi,r12
  c61db2:	5b                   	pop    rbx
  c61db3:	5d                   	pop    rbp
  c61db4:	41 5c                	pop    r12
  c61db6:	41 5d                	pop    r13
  c61db8:	e9 43 fe ff ff       	jmp    c61c00 <CDataGroup::AddDataGroup(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  c61dbd:	0f 1f 00             	nop    DWORD PTR [rax]
  c61dc0:	89 d8                	mov    eax,ebx
  c61dc2:	48 c1 e0 03          	shl    rax,0x3
  c61dc6:	48 03 45 38          	add    rax,QWORD PTR [rbp+0x38]
  c61dca:	eb b2                	jmp    c61d7e <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x4e>
  c61dcc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  c61dd0:	e8 13 36 8f ff       	call   5553e8 <wmemcmp@plt>
  c61dd5:	85 c0                	test   eax,eax
  c61dd7:	75 be                	jne    c61d97 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0x67>
  c61dd9:	39 5d 44             	cmp    DWORD PTR [rbp+0x44],ebx
  c61ddc:	77 12                	ja     c61df0 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0xc0>
  c61dde:	48 8b 5d 38          	mov    rbx,QWORD PTR [rbp+0x38]
  c61de2:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  c61de5:	48 83 c4 08          	add    rsp,0x8
  c61de9:	5b                   	pop    rbx
  c61dea:	5d                   	pop    rbp
  c61deb:	41 5c                	pop    r12
  c61ded:	41 5d                	pop    r13
  c61def:	c3                   	ret
  c61df0:	89 db                	mov    ebx,ebx
  c61df2:	48 c1 e3 03          	shl    rbx,0x3
  c61df6:	48 03 5d 38          	add    rbx,QWORD PTR [rbp+0x38]
  c61dfa:	eb e6                	jmp    c61de2 <CDataGroup::GetDataGroupByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)+0xb2>
  c61dfc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
