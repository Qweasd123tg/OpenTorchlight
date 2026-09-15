# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000813930 <CCharacter::strength()>:
  813930:	55                   	push   rbp
  813931:	ba 07 00 00 00       	mov    edx,0x7
  813936:	be 47 00 00 00       	mov    esi,0x47
  81393b:	53                   	push   rbx
  81393c:	48 89 fb             	mov    rbx,rdi
  81393f:	48 83 ec 18          	sub    rsp,0x18
  813943:	8b af 2c 04 00 00    	mov    ebp,DWORD PTR [rdi+0x42c]
  813949:	e8 92 fe ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  81394e:	0f 28 c8             	movaps xmm1,xmm0
  813951:	f3 0f 2a c5          	cvtsi2ss xmm0,ebp
  813955:	f3 0f 59 c1          	mulss  xmm0,xmm1
  813959:	f3 0f 5e 05 db 0e 79 00 	divss  xmm0,DWORD PTR [rip+0x790edb]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  813961:	e8 12 fd d3 ff       	call   553678 <ceilf@plt>
  813966:	ba 07 00 00 00       	mov    edx,0x7
  81396b:	48 89 df             	mov    rdi,rbx
  81396e:	be 45 00 00 00       	mov    esi,0x45
  813973:	f3 0f 11 04 24       	movss  DWORD PTR [rsp],xmm0
  813978:	e8 63 fe ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  81397d:	e8 f6 fc d3 ff       	call   553678 <ceilf@plt>
  813982:	f3 0f 2c 14 24       	cvttss2si edx,DWORD PTR [rsp]
  813987:	f3 0f 2c c0          	cvttss2si eax,xmm0
  81398b:	48 83 c4 18          	add    rsp,0x18
  81398f:	5b                   	pop    rbx
  813990:	8d 04 02             	lea    eax,[rdx+rax*1]
  813993:	01 e8                	add    eax,ebp
  813995:	5d                   	pop    rbp
  813996:	c3                   	ret
  813997:	90                   	nop
  813998:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

