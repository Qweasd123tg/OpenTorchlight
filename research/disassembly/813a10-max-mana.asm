0000000000813a10 <CCharacter::maxMana()>:
  813a10:	55                   	push   rbp
  813a11:	b8 01 00 00 00       	mov    eax,0x1
  813a16:	ba 07 00 00 00       	mov    edx,0x7
  813a1b:	be 13 00 00 00       	mov    esi,0x13
  813a20:	48 89 fd             	mov    rbp,rdi
  813a23:	53                   	push   rbx
  813a24:	48 83 ec 18          	sub    rsp,0x18
  813a28:	f3 0f 2a 87 3c 04 00 00 	cvtsi2ss xmm0,DWORD PTR [rdi+0x43c]
  813a30:	f3 0f 58 87 40 04 00 00 	addss  xmm0,DWORD PTR [rdi+0x440]
  813a38:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  813a3c:	85 db                	test   ebx,ebx
  813a3e:	0f 4e d8             	cmovle ebx,eax
  813a41:	e8 9a fd ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  813a46:	0f 28 c8             	movaps xmm1,xmm0
  813a49:	f3 0f 2a c3          	cvtsi2ss xmm0,ebx
  813a4d:	f3 0f 59 c1          	mulss  xmm0,xmm1
  813a51:	f3 0f 5e 05 e3 0d 79 00 	divss  xmm0,DWORD PTR [rip+0x790de3]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  813a59:	e8 1a fc d3 ff       	call   553678 <ceilf@plt>
  813a5e:	ba 07 00 00 00       	mov    edx,0x7
  813a63:	48 89 ef             	mov    rdi,rbp
  813a66:	be 04 00 00 00       	mov    esi,0x4
  813a6b:	f3 0f 11 04 24       	movss  DWORD PTR [rsp],xmm0
  813a70:	e8 6b fd ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  813a75:	e8 fe fb d3 ff       	call   553678 <ceilf@plt>
  813a7a:	f3 0f 2c 14 24       	cvttss2si edx,DWORD PTR [rsp]
  813a7f:	f3 0f 2c c0          	cvttss2si eax,xmm0
  813a83:	48 83 c4 18          	add    rsp,0x18
  813a87:	8d 04 02             	lea    eax,[rdx+rax*1]
  813a8a:	01 d8                	add    eax,ebx
  813a8c:	5b                   	pop    rbx
  813a8d:	5d                   	pop    rbp
  813a8e:	c3                   	ret
  813a8f:	90                   	nop

