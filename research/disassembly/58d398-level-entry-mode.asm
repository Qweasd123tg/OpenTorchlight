# Original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address-scoped excerpt of the user-supplied archive (2),
# original-analysis/full-intel-disassembly.asm; not a fresh ELF export.

# Range [0x58d398, 0x58d3ba)
  58d398:	80 7c 24 33 00       	cmp    BYTE PTR [rsp+0x33],0x0
  58d39d:	75 1b                	jne    58d3ba <CGameClient::performWarp()+0x2aa>
  58d39f:	48 83 bd a0 10 00 00 00 	cmp    QWORD PTR [rbp+0x10a0],0x0
  58d3a7:	41 b4 01             	mov    r12b,0x1
  58d3aa:	74 0e                	je     58d3ba <CGameClient::performWarp()+0x2aa>
  58d3ac:	45 31 e4             	xor    r12d,r12d
  58d3af:	83 bd a0 10 00 00 00 	cmp    DWORD PTR [rbp+0x10a0],0x0
  58d3b6:	41 0f 9f c4          	setg   r12b

# Range [0x58d555, 0x58d576)
  58d555:	44 8b 44 24 34       	mov    r8d,DWORD PTR [rsp+0x34]
  58d55a:	48 8d 94 24 70 01 00 00 	lea    rdx,[rsp+0x170]
  58d562:	45 89 e1             	mov    r9d,r12d
  58d565:	31 c9                	xor    ecx,ecx
  58d567:	4c 89 ee             	mov    rsi,r13
  58d56a:	48 89 ef             	mov    rdi,rbp
  58d56d:	48 89 1c 24          	mov    QWORD PTR [rsp],rbx
  58d571:	e8 fa 81 ff ff       	call   585770 <CGameClient::loadLevel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool, int, ELevelEntryType, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
