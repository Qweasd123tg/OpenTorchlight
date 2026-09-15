# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
00000000008137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>:
  8137e0:	48 89 5c 24 e8       	mov    QWORD PTR [rsp-0x18],rbx
  8137e5:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
  8137ea:	48 89 fb             	mov    rbx,rdi
  8137ed:	4c 89 64 24 f8       	mov    QWORD PTR [rsp-0x8],r12
  8137f2:	48 83 ec 28          	sub    rsp,0x28
  8137f6:	48 8b bf b8 01 00 00 	mov    rdi,QWORD PTR [rdi+0x1b8]
  8137fd:	89 f5                	mov    ebp,esi
  8137ff:	41 89 d4             	mov    r12d,edx
  813802:	48 85 ff             	test   rdi,rdi
  813805:	74 49                	je     813850 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)+0x70>
  813807:	48 83 bb 90 04 00 00 00 	cmp    QWORD PTR [rbx+0x490],0x0
  81380f:	74 6f                	je     813880 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)+0xa0>
  813811:	e8 da 7d fd ff       	call   7eb5f0 <CEffectManager::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  813816:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  81381d:	44 89 e2             	mov    edx,r12d
  813820:	89 ee                	mov    esi,ebp
  813822:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  813828:	e8 13 8e 10 00       	call   91c640 <CInventory::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  81382d:	f3 0f 58 44 24 0c    	addss  xmm0,DWORD PTR [rsp+0xc]
  813833:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
  813838:	48 8b 6c 24 18       	mov    rbp,QWORD PTR [rsp+0x18]
  81383d:	4c 8b 64 24 20       	mov    r12,QWORD PTR [rsp+0x20]
  813842:	48 83 c4 28          	add    rsp,0x28
  813846:	c3                   	ret
  813847:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  813850:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  813857:	0f 57 c0             	xorps  xmm0,xmm0
  81385a:	48 85 ff             	test   rdi,rdi
  81385d:	74 d4                	je     813833 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)+0x53>
  81385f:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
  813864:	48 8b 6c 24 18       	mov    rbp,QWORD PTR [rsp+0x18]
  813869:	4c 8b 64 24 20       	mov    r12,QWORD PTR [rsp+0x20]
  81386e:	48 83 c4 28          	add    rsp,0x28
  813872:	e9 c9 8d 10 00       	jmp    91c640 <CInventory::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  813877:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  813880:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
  813885:	48 8b 6c 24 18       	mov    rbp,QWORD PTR [rsp+0x18]
  81388a:	4c 8b 64 24 20       	mov    r12,QWORD PTR [rsp+0x20]
  81388f:	48 83 c4 28          	add    rsp,0x28
  813893:	e9 58 7d fd ff       	jmp    7eb5f0 <CEffectManager::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  813898:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

