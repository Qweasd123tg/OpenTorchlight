0000000000d50c70 <CAIManager::update(float)>:
  d50c70:	55                   	push   rbp
  d50c71:	48 89 fd             	mov    rbp,rdi
  d50c74:	53                   	push   rbx
  d50c75:	48 83 ec 18          	sub    rsp,0x18
  d50c79:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  d50c7f:	48 8b 7f 18          	mov    rdi,QWORD PTR [rdi+0x18]
  d50c83:	e8 f8 95 ff ff       	call   d4a280 <CAIFlagManager::updateAIFlags(float)>
  d50c88:	48 8b 7d 20          	mov    rdi,QWORD PTR [rbp+0x20]
  d50c8c:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  d50c92:	e8 f9 d6 03 00       	call   d8e390 <CAISkillManager::updateAISkills(float)>
  d50c97:	8b 55 30             	mov    edx,DWORD PTR [rbp+0x30]
  d50c9a:	85 d2                	test   edx,edx
  d50c9c:	74 3a                	je     d50cd8 <CAIManager::update(float)+0x68>
  d50c9e:	31 db                	xor    ebx,ebx
  d50ca0:	eb 20                	jmp    d50cc2 <CAIManager::update(float)+0x52>
  d50ca2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  d50ca8:	48 8b 45 28          	mov    rax,QWORD PTR [rbp+0x28]
  d50cac:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d50caf:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  d50cb5:	83 c3 01             	add    ebx,0x1
  d50cb8:	e8 33 f4 00 00       	call   d600f0 <CAIStatWatcher::update(float)>
  d50cbd:	3b 5d 30             	cmp    ebx,DWORD PTR [rbp+0x30]
  d50cc0:	73 16                	jae    d50cd8 <CAIManager::update(float)+0x68>
  d50cc2:	39 5d 34             	cmp    DWORD PTR [rbp+0x34],ebx
  d50cc5:	76 e1                	jbe    d50ca8 <CAIManager::update(float)+0x38>
  d50cc7:	89 d8                	mov    eax,ebx
  d50cc9:	48 c1 e0 03          	shl    rax,0x3
  d50ccd:	48 03 45 28          	add    rax,QWORD PTR [rbp+0x28]
  d50cd1:	eb d9                	jmp    d50cac <CAIManager::update(float)+0x3c>
  d50cd3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  d50cd8:	48 83 c4 18          	add    rsp,0x18
  d50cdc:	5b                   	pop    rbx
  d50cdd:	5d                   	pop    rbp
  d50cde:	c3                   	ret
  d50cdf:	90                   	nop

