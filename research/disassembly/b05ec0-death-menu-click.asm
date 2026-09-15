0000000000b05ec0 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:
  b05ec0:	48 89 5c 24 e0       	mov    QWORD PTR [rsp-0x20],rbx
  b05ec5:	48 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],rbp
  b05eca:	48 89 fb             	mov    rbx,rdi
  b05ecd:	4c 89 64 24 f0       	mov    QWORD PTR [rsp-0x10],r12
  b05ed2:	4c 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],r13
  b05ed7:	48 83 ec 28          	sub    rsp,0x28
  b05edb:	80 7f 30 00          	cmp    BYTE PTR [rdi+0x30],0x0
  b05edf:	74 34                	je     b05f15 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x55>
  b05ee1:	48 8b 47 40          	mov    rax,QWORD PTR [rdi+0x40]
  b05ee5:	83 fe 0e             	cmp    esi,0xe
  b05ee8:	48 8b 80 20 19 00 00 	mov    rax,QWORD PTR [rax+0x1920]
  b05eef:	48 8b 68 58          	mov    rbp,QWORD PTR [rax+0x58]
  b05ef3:	0f 84 97 00 00 00    	je     b05f90 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xd0>
  b05ef9:	7f 3d                	jg     b05f38 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x78>
  b05efb:	85 f6                	test   esi,esi
  b05efd:	75 0b                	jne    b05f0a <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4a>
  b05eff:	c6 87 c0 00 00 00 01 	mov    BYTE PTR [rdi+0xc0],0x1
  b05f06:	c6 47 32 01          	mov    BYTE PTR [rdi+0x32],0x1
  b05f0a:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  b05f0d:	31 f6                	xor    esi,esi
  b05f0f:	48 89 df             	mov    rdi,rbx
  b05f12:	ff 50 38             	call   QWORD PTR [rax+0x38]
  b05f15:	b8 01 00 00 00       	mov    eax,0x1
  b05f1a:	48 8b 5c 24 08       	mov    rbx,QWORD PTR [rsp+0x8]
  b05f1f:	48 8b 6c 24 10       	mov    rbp,QWORD PTR [rsp+0x10]
  b05f24:	4c 8b 64 24 18       	mov    r12,QWORD PTR [rsp+0x18]
  b05f29:	4c 8b 6c 24 20       	mov    r13,QWORD PTR [rsp+0x20]
  b05f2e:	48 83 c4 28          	add    rsp,0x28
  b05f32:	c3                   	ret
  b05f33:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  b05f38:	83 fe 0f             	cmp    esi,0xf
  b05f3b:	0f 84 1f 01 00 00    	je     b06060 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1a0>
  b05f41:	83 fe 10             	cmp    esi,0x10
  b05f44:	75 c4                	jne    b05f0a <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4a>
  b05f46:	c7 87 c4 00 00 00 02 00 00 00 	mov    DWORD PTR [rdi+0xc4],0x2
  b05f50:	c6 47 32 01          	mov    BYTE PTR [rdi+0x32],0x1
  b05f54:	31 f6                	xor    esi,esi
  b05f56:	c6 87 c1 00 00 00 01 	mov    BYTE PTR [rdi+0xc1],0x1
  b05f5d:	c7 87 fc 00 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0xfc],0x0
  b05f67:	c7 87 f8 00 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0xf8],0x0
  b05f71:	c7 87 00 01 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0x100],0x0
  b05f7b:	48 89 df             	mov    rdi,rbx
  b05f7e:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  b05f81:	ff 50 38             	call   QWORD PTR [rax+0x38]
  b05f84:	eb 8f                	jmp    b05f15 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x55>
  b05f86:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  b05f90:	c7 87 c4 00 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0xc4],0x0
  b05f9a:	c6 47 32 01          	mov    BYTE PTR [rdi+0x32],0x1
  b05f9e:	c6 87 c1 00 00 00 01 	mov    BYTE PTR [rdi+0xc1],0x1
  b05fa5:	44 8b a5 00 01 00 00 	mov    r12d,DWORD PTR [rbp+0x100]
  b05fac:	e8 df e4 f4 ff       	call   a54490 <CMasterResourceManager::getSingleton()>
  b05fb1:	48 89 c7             	mov    rdi,rax
  b05fb4:	44 89 e6             	mov    esi,r12d
  b05fb7:	e8 14 ea f4 ff       	call   a549d0 <CMasterResourceManager::experienceGate(int)>
  b05fbc:	44 8b ad 00 01 00 00 	mov    r13d,DWORD PTR [rbp+0x100]
  b05fc3:	41 89 c4             	mov    r12d,eax
  b05fc6:	e8 c5 e4 f4 ff       	call   a54490 <CMasterResourceManager::getSingleton()>
  b05fcb:	48 89 c7             	mov    rdi,rax
  b05fce:	41 83 ed 01          	sub    r13d,0x1
  b05fd2:	44 89 ee             	mov    esi,r13d
  b05fd5:	e8 f6 e9 f4 ff       	call   a549d0 <CMasterResourceManager::experienceGate(int)>
  b05fda:	44 89 e1             	mov    ecx,r12d
  b05fdd:	41 bc 67 66 66 66    	mov    r12d,0x66666667
  b05fe3:	29 c1                	sub    ecx,eax
  b05fe5:	89 c8                	mov    eax,ecx
  b05fe7:	c1 f9 1f             	sar    ecx,0x1f
  b05fea:	41 f7 ec             	imul   r12d
  b05fed:	c1 fa 02             	sar    edx,0x2
  b05ff0:	29 ca                	sub    edx,ecx
  b05ff2:	89 93 fc 00 00 00    	mov    DWORD PTR [rbx+0xfc],edx
  b05ff8:	44 8b ad 50 04 00 00 	mov    r13d,DWORD PTR [rbp+0x450]
  b05fff:	e8 8c e4 f4 ff       	call   a54490 <CMasterResourceManager::getSingleton()>
  b06004:	48 89 c7             	mov    rdi,rax
  b06007:	44 89 ee             	mov    esi,r13d
  b0600a:	e8 31 e9 f4 ff       	call   a54940 <CMasterResourceManager::fameGate(int)>
  b0600f:	8b ad 50 04 00 00    	mov    ebp,DWORD PTR [rbp+0x450]
  b06015:	41 89 c5             	mov    r13d,eax
  b06018:	e8 73 e4 f4 ff       	call   a54490 <CMasterResourceManager::getSingleton()>
  b0601d:	48 89 c7             	mov    rdi,rax
  b06020:	83 ed 01             	sub    ebp,0x1
  b06023:	89 ee                	mov    esi,ebp
  b06025:	e8 16 e9 f4 ff       	call   a54940 <CMasterResourceManager::fameGate(int)>
  b0602a:	41 29 c5             	sub    r13d,eax
  b0602d:	c7 83 00 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x100],0x0
  b06037:	31 f6                	xor    esi,esi
  b06039:	44 89 e8             	mov    eax,r13d
  b0603c:	41 c1 fd 1f          	sar    r13d,0x1f
  b06040:	48 89 df             	mov    rdi,rbx
  b06043:	41 f7 ec             	imul   r12d
  b06046:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  b06049:	c1 fa 02             	sar    edx,0x2
  b0604c:	44 29 ea             	sub    edx,r13d
  b0604f:	89 93 f8 00 00 00    	mov    DWORD PTR [rbx+0xf8],edx
  b06055:	ff 50 38             	call   QWORD PTR [rax+0x38]
  b06058:	e9 b8 fe ff ff       	jmp    b05f15 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x55>
  b0605d:	0f 1f 00             	nop    DWORD PTR [rax]
  b06060:	c7 87 c4 00 00 00 01 00 00 00 	mov    DWORD PTR [rdi+0xc4],0x1
  b0606a:	c6 47 32 01          	mov    BYTE PTR [rdi+0x32],0x1
  b0606e:	ba 67 66 66 66       	mov    edx,0x66666667
  b06073:	c6 87 c1 00 00 00 01 	mov    BYTE PTR [rdi+0xc1],0x1
  b0607a:	c7 87 fc 00 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0xfc],0x0
  b06084:	31 f6                	xor    esi,esi
  b06086:	c7 87 f8 00 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0xf8],0x0
  b06090:	8b 8d 44 04 00 00    	mov    ecx,DWORD PTR [rbp+0x444]
  b06096:	89 c8                	mov    eax,ecx
  b06098:	c1 f9 1f             	sar    ecx,0x1f
  b0609b:	f7 ea                	imul   edx
  b0609d:	c1 fa 02             	sar    edx,0x2
  b060a0:	29 ca                	sub    edx,ecx
  b060a2:	89 97 00 01 00 00    	mov    DWORD PTR [rdi+0x100],edx
  b060a8:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  b060ab:	48 89 df             	mov    rdi,rbx
  b060ae:	ff 50 38             	call   QWORD PTR [rax+0x38]
  b060b1:	e9 5f fe ff ff       	jmp    b05f15 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x55>
  b060b6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]

