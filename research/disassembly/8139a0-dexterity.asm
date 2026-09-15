# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
00000000008139a0 <CCharacter::dexterity()>:
  8139a0:	55                   	push   rbp
  8139a1:	ba 07 00 00 00       	mov    edx,0x7
  8139a6:	be 48 00 00 00       	mov    esi,0x48
  8139ab:	53                   	push   rbx
  8139ac:	48 89 fb             	mov    rbx,rdi
  8139af:	48 83 ec 18          	sub    rsp,0x18
  8139b3:	8b af 28 04 00 00    	mov    ebp,DWORD PTR [rdi+0x428]
  8139b9:	e8 22 fe ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8139be:	0f 28 c8             	movaps xmm1,xmm0
  8139c1:	f3 0f 2a c5          	cvtsi2ss xmm0,ebp
  8139c5:	f3 0f 59 c1          	mulss  xmm0,xmm1
  8139c9:	f3 0f 5e 05 6b 0e 79 00 	divss  xmm0,DWORD PTR [rip+0x790e6b]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8139d1:	e8 a2 fc d3 ff       	call   553678 <ceilf@plt>
  8139d6:	ba 07 00 00 00       	mov    edx,0x7
  8139db:	48 89 df             	mov    rdi,rbx
  8139de:	be 46 00 00 00       	mov    esi,0x46
  8139e3:	f3 0f 11 04 24       	movss  DWORD PTR [rsp],xmm0
  8139e8:	e8 f3 fd ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8139ed:	e8 86 fc d3 ff       	call   553678 <ceilf@plt>
  8139f2:	f3 0f 2c 14 24       	cvttss2si edx,DWORD PTR [rsp]
  8139f7:	f3 0f 2c c0          	cvttss2si eax,xmm0
  8139fb:	48 83 c4 18          	add    rsp,0x18
  8139ff:	5b                   	pop    rbx
  813a00:	8d 04 02             	lea    eax,[rdx+rax*1]
  813a03:	01 e8                	add    eax,ebp
  813a05:	5d                   	pop    rbp
  813a06:	c3                   	ret
  813a07:	90                   	nop
  813a08:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

