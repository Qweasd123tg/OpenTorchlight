00000000008e47d0 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)>:
  8e47d0:	48 89 5c 24 e0       	mov    QWORD PTR [rsp-0x20],rbx
  8e47d5:	48 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],rbp
  8e47da:	48 89 fb             	mov    rbx,rdi
  8e47dd:	4c 89 64 24 f0       	mov    QWORD PTR [rsp-0x10],r12
  8e47e2:	4c 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],r13
  8e47e7:	48 83 ec 38          	sub    rsp,0x38
  8e47eb:	48 89 f5             	mov    rbp,rsi
  8e47ee:	49 89 d4             	mov    r12,rdx
  8e47f1:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8e47f7:	41 89 cd             	mov    r13d,ecx
  8e47fa:	e8 51 a0 f2 ff       	call   80e850 <CCharacter::alive()>
  8e47ff:	84 c0                	test   al,al
  8e4801:	74 1d                	je     8e4820 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x50>
  8e4803:	48 8b 53 68          	mov    rdx,QWORD PTR [rbx+0x68]
  8e4807:	31 c0                	xor    eax,eax
  8e4809:	8b 4a 30             	mov    ecx,DWORD PTR [rdx+0x30]
  8e480c:	85 c9                	test   ecx,ecx
  8e480e:	74 07                	je     8e4817 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x47>
  8e4810:	48 8b 42 28          	mov    rax,QWORD PTR [rdx+0x28]
  8e4814:	48 8b 00             	mov    rax,QWORD PTR [rax]
  8e4817:	83 b8 d0 38 00 00 01 	cmp    DWORD PTR [rax+0x38d0],0x1
  8e481e:	74 20                	je     8e4840 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x70>
  8e4820:	48 8b 5c 24 18       	mov    rbx,QWORD PTR [rsp+0x18]
  8e4825:	48 8b 6c 24 20       	mov    rbp,QWORD PTR [rsp+0x20]
  8e482a:	4c 8b 64 24 28       	mov    r12,QWORD PTR [rsp+0x28]
  8e482f:	4c 8b 6c 24 30       	mov    r13,QWORD PTR [rsp+0x30]
  8e4834:	48 83 c4 38          	add    rsp,0x38
  8e4838:	c3                   	ret
  8e4839:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8e4840:	41 0f b6 cd          	movzx  ecx,r13b
  8e4844:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  8e484a:	4c 89 e2             	mov    rdx,r12
  8e484d:	48 89 ee             	mov    rsi,rbp
  8e4850:	48 89 df             	mov    rdi,rbx
  8e4853:	e8 78 46 f5 ff       	call   838ed0 <CCharacter::die(CCharacter*, Ogre::Vector3 const*, float, bool)>
  8e4858:	80 bb 15 0a 00 00 00 	cmp    BYTE PTR [rbx+0xa15],0x0
  8e485f:	74 bf                	je     8e4820 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0x50>
  8e4861:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  8e4865:	31 ff                	xor    edi,edi
  8e4867:	8b 50 30             	mov    edx,DWORD PTR [rax+0x30]
  8e486a:	85 d2                	test   edx,edx
  8e486c:	74 07                	je     8e4875 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)+0xa5>
  8e486e:	48 8b 40 28          	mov    rax,QWORD PTR [rax+0x28]
  8e4872:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  8e4875:	48 8b 5c 24 18       	mov    rbx,QWORD PTR [rsp+0x18]
  8e487a:	48 8b 6c 24 20       	mov    rbp,QWORD PTR [rsp+0x20]
  8e487f:	ba 01 00 00 00       	mov    edx,0x1
  8e4884:	4c 8b 64 24 28       	mov    r12,QWORD PTR [rsp+0x28]
  8e4889:	4c 8b 6c 24 30       	mov    r13,QWORD PTR [rsp+0x30]
  8e488e:	be 01 00 00 00       	mov    esi,0x1
  8e4893:	48 83 c4 38          	add    rsp,0x38
  8e4897:	e9 34 6d ca ff       	jmp    58b5d0 <CGameClient::saveCharacter(bool, bool)>
  8e489c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

