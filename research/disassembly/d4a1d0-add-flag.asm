0000000000d4a1d0 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)>:
  d4a1d0:	55                   	push   rbp
  d4a1d1:	89 f5                	mov    ebp,esi
  d4a1d3:	53                   	push   rbx
  d4a1d4:	48 89 fb             	mov    rbx,rdi
  d4a1d7:	48 83 ec 08          	sub    rsp,0x8
  d4a1db:	8b 47 1c             	mov    eax,DWORD PTR [rdi+0x1c]
  d4a1de:	39 c6                	cmp    esi,eax
  d4a1e0:	72 4e                	jb     d4a230 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x60>
  d4a1e2:	48 8b 57 10          	mov    rdx,QWORD PTR [rdi+0x10]
  d4a1e6:	48 8b 0a             	mov    rcx,QWORD PTR [rdx]
  d4a1e9:	f3 0f 10 49 10       	movss  xmm1,DWORD PTR [rcx+0x10]
  d4a1ee:	0f 2e 0d 03 a6 25 00 	ucomiss xmm1,DWORD PTR [rip+0x25a603]        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  d4a1f5:	0f 97 c1             	seta   cl
  d4a1f8:	0f 2e c1             	ucomiss xmm0,xmm1
  d4a1fb:	76 0c                	jbe    d4a209 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x39>
  d4a1fd:	39 c5                	cmp    ebp,eax
  d4a1ff:	72 4f                	jb     d4a250 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x80>
  d4a201:	48 8b 02             	mov    rax,QWORD PTR [rdx]
  d4a204:	f3 0f 11 40 10       	movss  DWORD PTR [rax+0x10],xmm0
  d4a209:	84 c9                	test   cl,cl
  d4a20b:	74 63                	je     d4a270 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0xa0>
  d4a20d:	3b 6b 1c             	cmp    ebp,DWORD PTR [rbx+0x1c]
  d4a210:	73 4e                	jae    d4a260 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x90>
  d4a212:	89 ed                	mov    ebp,ebp
  d4a214:	48 c1 e5 03          	shl    rbp,0x3
  d4a218:	48 03 6b 10          	add    rbp,QWORD PTR [rbx+0x10]
  d4a21c:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  d4a220:	48 83 c4 08          	add    rsp,0x8
  d4a224:	5b                   	pop    rbx
  d4a225:	5d                   	pop    rbp
  d4a226:	c3                   	ret
  d4a227:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  d4a230:	48 8b 57 10          	mov    rdx,QWORD PTR [rdi+0x10]
  d4a234:	89 f1                	mov    ecx,esi
  d4a236:	48 8b 0c ca          	mov    rcx,QWORD PTR [rdx+rcx*8]
  d4a23a:	f3 0f 10 49 10       	movss  xmm1,DWORD PTR [rcx+0x10]
  d4a23f:	0f 2e 0d b2 a5 25 00 	ucomiss xmm1,DWORD PTR [rip+0x25a5b2]        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  d4a246:	0f 97 c1             	seta   cl
  d4a249:	eb ad                	jmp    d4a1f8 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x28>
  d4a24b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  d4a250:	89 ea                	mov    edx,ebp
  d4a252:	48 c1 e2 03          	shl    rdx,0x3
  d4a256:	48 03 53 10          	add    rdx,QWORD PTR [rbx+0x10]
  d4a25a:	eb a5                	jmp    d4a201 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x31>
  d4a25c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  d4a260:	48 8b 6b 10          	mov    rbp,QWORD PTR [rbx+0x10]
  d4a264:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  d4a268:	48 83 c4 08          	add    rsp,0x8
  d4a26c:	5b                   	pop    rbx
  d4a26d:	5d                   	pop    rbp
  d4a26e:	c3                   	ret
  d4a26f:	90                   	nop
  d4a270:	89 ee                	mov    esi,ebp
  d4a272:	48 89 df             	mov    rdi,rbx
  d4a275:	e8 76 fe ff ff       	call   d4a0f0 <CAIFlagManager::flagSet(EAIFLAG_TYPES)>
  d4a27a:	eb 91                	jmp    d4a20d <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)+0x3d>
  d4a27c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

