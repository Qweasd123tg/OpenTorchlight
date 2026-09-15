# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
00000000008a2de0 <CGenericModel::findRandomAnimation(std::string const&)>:
  8a2de0:	41 57                	push   r15
  8a2de2:	49 89 f7             	mov    r15,rsi
  8a2de5:	41 56                	push   r14
  8a2de7:	41 55                	push   r13
  8a2de9:	49 89 fd             	mov    r13,rdi
  8a2dec:	41 54                	push   r12
  8a2dee:	55                   	push   rbp
  8a2def:	53                   	push   rbx
  8a2df0:	48 83 ec 38          	sub    rsp,0x38
  8a2df4:	48 8b 06             	mov    rax,QWORD PTR [rsi]
  8a2df7:	48 8b 68 e8          	mov    rbp,QWORD PTR [rax-0x18]
  8a2dfb:	48 8b 87 e0 01 00 00 	mov    rax,QWORD PTR [rdi+0x1e0]
  8a2e02:	48 85 c0             	test   rax,rax
  8a2e05:	0f 84 03 01 00 00    	je     8a2f0e <CGenericModel::findRandomAnimation(std::string const&)+0x12e>
  8a2e0b:	8b 58 20             	mov    ebx,DWORD PTR [rax+0x20]
  8a2e0e:	85 db                	test   ebx,ebx
  8a2e10:	0f 84 f8 00 00 00    	je     8a2f0e <CGenericModel::findRandomAnimation(std::string const&)+0x12e>
  8a2e16:	89 ed                	mov    ebp,ebp
  8a2e18:	31 db                	xor    ebx,ebx
  8a2e1a:	41 bc ff ff ff ff    	mov    r12d,0xffffffff
  8a2e20:	4c 8d 74 24 20       	lea    r14,[rsp+0x20]
  8a2e25:	eb 32                	jmp    8a2e59 <CGenericModel::findRandomAnimation(std::string const&)+0x79>
  8a2e27:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  8a2e30:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  8a2e37:	0f 85 ed 00 00 00    	jne    8a2f2a <CGenericModel::findRandomAnimation(std::string const&)+0x14a>
  8a2e3d:	49 8b 85 e0 01 00 00 	mov    rax,QWORD PTR [r13+0x1e0]
  8a2e44:	48 85 c0             	test   rax,rax
  8a2e47:	0f 84 cb 00 00 00    	je     8a2f18 <CGenericModel::findRandomAnimation(std::string const&)+0x138>
  8a2e4d:	83 c3 01             	add    ebx,0x1
  8a2e50:	3b 58 20             	cmp    ebx,DWORD PTR [rax+0x20]
  8a2e53:	0f 83 bf 00 00 00    	jae    8a2f18 <CGenericModel::findRandomAnimation(std::string const&)+0x138>
  8a2e59:	89 de                	mov    esi,ebx
  8a2e5b:	4c 89 f7             	mov    rdi,r14
  8a2e5e:	48 c1 e6 03          	shl    rsi,0x3
  8a2e62:	48 03 70 28          	add    rsi,QWORD PTR [rax+0x28]
  8a2e66:	e8 75 b2 3e 00       	call   c8e0e0 <STRINGS::StringUpper(std::string const&)>
  8a2e6b:	48 8b 44 24 20       	mov    rax,QWORD PTR [rsp+0x20]
  8a2e70:	48 39 68 e8          	cmp    QWORD PTR [rax-0x18],rbp
  8a2e74:	48 8d 78 e8          	lea    rdi,[rax-0x18]
  8a2e78:	72 b6                	jb     8a2e30 <CGenericModel::findRandomAnimation(std::string const&)+0x50>
  8a2e7a:	48 8d 7c 24 10       	lea    rdi,[rsp+0x10]
  8a2e7f:	48 89 e9             	mov    rcx,rbp
  8a2e82:	31 d2                	xor    edx,edx
  8a2e84:	4c 89 f6             	mov    rsi,r14
  8a2e87:	e8 4c 2e cb ff       	call   555cd8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&, unsigned long, unsigned long)@plt>
  8a2e8c:	48 8b 44 24 10       	mov    rax,QWORD PTR [rsp+0x10]
  8a2e91:	49 8b 3f             	mov    rdi,QWORD PTR [r15]
  8a2e94:	45 31 c0             	xor    r8d,r8d
  8a2e97:	48 8b 48 e8          	mov    rcx,QWORD PTR [rax-0x18]
  8a2e9b:	48 3b 4f e8          	cmp    rcx,QWORD PTR [rdi-0x18]
  8a2e9f:	48 8d 50 e8          	lea    rdx,[rax-0x18]
  8a2ea3:	74 5b                	je     8a2f00 <CGenericModel::findRandomAnimation(std::string const&)+0x120>
  8a2ea5:	48 81 fa 20 3a 42 01 	cmp    rdx,0x1423a20
  8a2eac:	0f 85 a1 00 00 00    	jne    8a2f53 <CGenericModel::findRandomAnimation(std::string const&)+0x173>
  8a2eb2:	45 84 c0             	test   r8b,r8b
  8a2eb5:	74 39                	je     8a2ef0 <CGenericModel::findRandomAnimation(std::string const&)+0x110>
  8a2eb7:	41 83 fc ff          	cmp    r12d,0xffffffff
  8a2ebb:	75 13                	jne    8a2ed0 <CGenericModel::findRandomAnimation(std::string const&)+0xf0>
  8a2ebd:	48 8b 7c 24 20       	mov    rdi,QWORD PTR [rsp+0x20]
  8a2ec2:	41 89 dc             	mov    r12d,ebx
  8a2ec5:	48 83 ef 18          	sub    rdi,0x18
  8a2ec9:	e9 62 ff ff ff       	jmp    8a2e30 <CGenericModel::findRandomAnimation(std::string const&)+0x50>
  8a2ece:	66 90                	xchg   ax,ax
  8a2ed0:	0f 57 c0             	xorps  xmm0,xmm0
  8a2ed3:	f3 0f 10 0d 41 58 70 00 	movss  xmm1,DWORD PTR [rip+0x705841]        # fa871c <vtable for Ogre::SharedPtr<Ogre::Texture>+0x7c>
  8a2edb:	e8 70 fc 3e 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8a2ee0:	f3 0f 10 0d 4c eb 72 00 	movss  xmm1,DWORD PTR [rip+0x72eb4c]        # fd1a34 <vtable for iRandomWeight+0x34>
  8a2ee8:	0f 2e c8             	ucomiss xmm1,xmm0
  8a2eeb:	76 03                	jbe    8a2ef0 <CGenericModel::findRandomAnimation(std::string const&)+0x110>
  8a2eed:	41 89 dc             	mov    r12d,ebx
  8a2ef0:	48 8b 7c 24 20       	mov    rdi,QWORD PTR [rsp+0x20]
  8a2ef5:	48 83 ef 18          	sub    rdi,0x18
  8a2ef9:	e9 32 ff ff ff       	jmp    8a2e30 <CGenericModel::findRandomAnimation(std::string const&)+0x50>
  8a2efe:	66 90                	xchg   ax,ax
  8a2f00:	48 39 c9             	cmp    rcx,rcx
  8a2f03:	48 89 c6             	mov    rsi,rax
  8a2f06:	f3 a6                	repz cmps BYTE PTR [rsi],BYTE PTR [rdi]
  8a2f08:	41 0f 94 c0          	sete   r8b
  8a2f0c:	eb 97                	jmp    8a2ea5 <CGenericModel::findRandomAnimation(std::string const&)+0xc5>
  8a2f0e:	41 83 cc ff          	or     r12d,0xffffffff
  8a2f12:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  8a2f18:	48 83 c4 38          	add    rsp,0x38
  8a2f1c:	44 89 e0             	mov    eax,r12d
  8a2f1f:	5b                   	pop    rbx
  8a2f20:	5d                   	pop    rbp
  8a2f21:	41 5c                	pop    r12
  8a2f23:	41 5d                	pop    r13
  8a2f25:	41 5e                	pop    r14
  8a2f27:	41 5f                	pop    r15
  8a2f29:	c3                   	ret
  8a2f2a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8a2f2f:	48 85 c0             	test   rax,rax
  8a2f32:	74 69                	je     8a2f9d <CGenericModel::findRandomAnimation(std::string const&)+0x1bd>
  8a2f34:	83 c8 ff             	or     eax,0xffffffff
  8a2f37:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8a2f3c:	85 c0                	test   eax,eax
  8a2f3e:	0f 8f f9 fe ff ff    	jg     8a2e3d <CGenericModel::findRandomAnimation(std::string const&)+0x5d>
  8a2f44:	48 8d 74 24 2e       	lea    rsi,[rsp+0x2e]
  8a2f49:	e8 8a 28 cb ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  8a2f4e:	e9 ea fe ff ff       	jmp    8a2e3d <CGenericModel::findRandomAnimation(std::string const&)+0x5d>
  8a2f53:	b9 c8 41 55 00       	mov    ecx,0x5541c8
  8a2f58:	48 85 c9             	test   rcx,rcx
  8a2f5b:	74 4d                	je     8a2faa <CGenericModel::findRandomAnimation(std::string const&)+0x1ca>
  8a2f5d:	83 c9 ff             	or     ecx,0xffffffff
  8a2f60:	f0 0f c1 4a 10       	lock xadd DWORD PTR [rdx+0x10],ecx
  8a2f65:	85 c9                	test   ecx,ecx
  8a2f67:	0f 8f 45 ff ff ff    	jg     8a2eb2 <CGenericModel::findRandomAnimation(std::string const&)+0xd2>
  8a2f6d:	48 8d 74 24 2f       	lea    rsi,[rsp+0x2f]
  8a2f72:	48 89 d7             	mov    rdi,rdx
  8a2f75:	44 88 44 24 08       	mov    BYTE PTR [rsp+0x8],r8b
  8a2f7a:	e8 59 28 cb ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  8a2f7f:	44 0f b6 44 24 08    	movzx  r8d,BYTE PTR [rsp+0x8]
  8a2f85:	e9 28 ff ff ff       	jmp    8a2eb2 <CGenericModel::findRandomAnimation(std::string const&)+0xd2>
  8a2f8a:	48 89 c3             	mov    rbx,rax
  8a2f8d:	4c 89 f7             	mov    rdi,r14
  8a2f90:	e8 f3 32 cb ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8a2f95:	48 89 df             	mov    rdi,rbx
  8a2f98:	e8 fb 14 cb ff       	call   554498 <_Unwind_Resume@plt>
  8a2f9d:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8a2fa0:	8d 50 ff             	lea    edx,[rax-0x1]
  8a2fa3:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8a2fa6:	eb 94                	jmp    8a2f3c <CGenericModel::findRandomAnimation(std::string const&)+0x15c>
  8a2fa8:	eb e0                	jmp    8a2f8a <CGenericModel::findRandomAnimation(std::string const&)+0x1aa>
  8a2faa:	8b 48 f8             	mov    ecx,DWORD PTR [rax-0x8]
  8a2fad:	8d 71 ff             	lea    esi,[rcx-0x1]
  8a2fb0:	89 70 f8             	mov    DWORD PTR [rax-0x8],esi
  8a2fb3:	eb b0                	jmp    8a2f65 <CGenericModel::findRandomAnimation(std::string const&)+0x185>
  8a2fb5:	90                   	nop
  8a2fb6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]

