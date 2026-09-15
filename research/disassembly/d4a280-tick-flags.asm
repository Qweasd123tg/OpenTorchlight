0000000000d4a280 <CAIFlagManager::updateAIFlags(float)>:
  d4a280:	55                   	push   rbp
  d4a281:	48 89 fd             	mov    rbp,rdi
  d4a284:	53                   	push   rbx
  d4a285:	48 83 ec 18          	sub    rsp,0x18
  d4a289:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  d4a28f:	8b 57 18             	mov    edx,DWORD PTR [rdi+0x18]
  d4a292:	85 d2                	test   edx,edx
  d4a294:	0f 84 9e 00 00 00    	je     d4a338 <CAIFlagManager::updateAIFlags(float)+0xb8>
  d4a29a:	31 db                	xor    ebx,ebx
  d4a29c:	eb 46                	jmp    d4a2e4 <CAIFlagManager::updateAIFlags(float)+0x64>
  d4a29e:	66 90                	xchg   ax,ax
  d4a2a0:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
  d4a2a4:	48 83 3a 00          	cmp    QWORD PTR [rdx],0x0
  d4a2a8:	74 32                	je     d4a2dc <CAIFlagManager::updateAIFlags(float)+0x5c>
  d4a2aa:	39 d8                	cmp    eax,ebx
  d4a2ac:	77 52                	ja     d4a300 <CAIFlagManager::updateAIFlags(float)+0x80>
  d4a2ae:	48 8b 55 10          	mov    rdx,QWORD PTR [rbp+0x10]
  d4a2b2:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  d4a2b5:	0f 57 c9             	xorps  xmm1,xmm1
  d4a2b8:	f3 0f 10 42 10       	movss  xmm0,DWORD PTR [rdx+0x10]
  d4a2bd:	0f 2e c1             	ucomiss xmm0,xmm1
  d4a2c0:	76 1a                	jbe    d4a2dc <CAIFlagManager::updateAIFlags(float)+0x5c>
  d4a2c2:	39 d8                	cmp    eax,ebx
  d4a2c4:	77 4a                	ja     d4a310 <CAIFlagManager::updateAIFlags(float)+0x90>
  d4a2c6:	48 8b 45 10          	mov    rax,QWORD PTR [rbp+0x10]
  d4a2ca:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  d4a2cd:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  d4a2d3:	e8 88 f6 ff ff       	call   d49960 <CAIFlag::update(float)>
  d4a2d8:	84 c0                	test   al,al
  d4a2da:	74 44                	je     d4a320 <CAIFlagManager::updateAIFlags(float)+0xa0>
  d4a2dc:	83 c3 01             	add    ebx,0x1
  d4a2df:	3b 5d 18             	cmp    ebx,DWORD PTR [rbp+0x18]
  d4a2e2:	73 54                	jae    d4a338 <CAIFlagManager::updateAIFlags(float)+0xb8>
  d4a2e4:	8b 45 1c             	mov    eax,DWORD PTR [rbp+0x1c]
  d4a2e7:	39 d8                	cmp    eax,ebx
  d4a2e9:	76 b5                	jbe    d4a2a0 <CAIFlagManager::updateAIFlags(float)+0x20>
  d4a2eb:	89 da                	mov    edx,ebx
  d4a2ed:	48 c1 e2 03          	shl    rdx,0x3
  d4a2f1:	48 03 55 10          	add    rdx,QWORD PTR [rbp+0x10]
  d4a2f5:	eb ad                	jmp    d4a2a4 <CAIFlagManager::updateAIFlags(float)+0x24>
  d4a2f7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  d4a300:	89 da                	mov    edx,ebx
  d4a302:	48 c1 e2 03          	shl    rdx,0x3
  d4a306:	48 03 55 10          	add    rdx,QWORD PTR [rbp+0x10]
  d4a30a:	eb a6                	jmp    d4a2b2 <CAIFlagManager::updateAIFlags(float)+0x32>
  d4a30c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  d4a310:	89 d8                	mov    eax,ebx
  d4a312:	48 c1 e0 03          	shl    rax,0x3
  d4a316:	48 03 45 10          	add    rax,QWORD PTR [rbp+0x10]
  d4a31a:	eb ae                	jmp    d4a2ca <CAIFlagManager::updateAIFlags(float)+0x4a>
  d4a31c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  d4a320:	89 de                	mov    esi,ebx
  d4a322:	48 89 ef             	mov    rdi,rbp
  d4a325:	83 c3 01             	add    ebx,0x1
  d4a328:	e8 63 fd ff ff       	call   d4a090 <CAIFlagManager::removeAIFlag(EAIFLAG_TYPES)>
  d4a32d:	3b 5d 18             	cmp    ebx,DWORD PTR [rbp+0x18]
  d4a330:	72 b2                	jb     d4a2e4 <CAIFlagManager::updateAIFlags(float)+0x64>
  d4a332:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  d4a338:	48 83 c4 18          	add    rsp,0x18
  d4a33c:	5b                   	pop    rbx
  d4a33d:	5d                   	pop    rbp
  d4a33e:	c3                   	ret
  d4a33f:	90                   	nop

