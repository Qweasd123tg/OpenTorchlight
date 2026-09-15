# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000824a50 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)>:
  824a50:	41 55                	push   r13
  824a52:	49 89 cd             	mov    r13,rcx
  824a55:	41 54                	push   r12
  824a57:	49 89 d4             	mov    r12,rdx
  824a5a:	55                   	push   rbp
  824a5b:	48 89 f5             	mov    rbp,rsi
  824a5e:	53                   	push   rbx
  824a5f:	48 89 fb             	mov    rbx,rdi
  824a62:	48 81 ec c8 00 00 00 	sub    rsp,0xc8
  824a69:	48 83 bf 90 03 00 00 00 	cmp    QWORD PTR [rdi+0x390],0x0
  824a71:	0f 84 71 03 00 00    	je     824de8 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x398>
  824a77:	48 85 c9             	test   rcx,rcx
  824a7a:	0f 84 50 03 00 00    	je     824dd0 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x380>
  824a80:	be 23 00 00 00       	mov    esi,0x23
  824a85:	4c 89 ef             	mov    rdi,r13
  824a88:	e8 13 18 fd ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  824a8d:	84 c0                	test   al,al
  824a8f:	0f 85 ab 01 00 00    	jne    824c40 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x1f0>
  824a95:	0f 57 c0             	xorps  xmm0,xmm0
  824a98:	48 85 ed             	test   rbp,rbp
  824a9b:	f3 0f 11 44 24 5c    	movss  DWORD PTR [rsp+0x5c],xmm0
  824aa1:	0f 84 ba 01 00 00    	je     824c61 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x211>
  824aa7:	be 01 00 00 00       	mov    esi,0x1
  824aac:	48 89 df             	mov    rdi,rbx
  824aaf:	e8 cc 25 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  824ab4:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  824aba:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  824abf:	be 01 00 00 00       	mov    esi,0x1
  824ac4:	f3 0f 11 4c 24 68    	movss  DWORD PTR [rsp+0x68],xmm1
  824aca:	48 89 ef             	mov    rdi,rbp
  824acd:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  824ad2:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  824ada:	8b 44 24 68          	mov    eax,DWORD PTR [rsp+0x68]
  824ade:	89 84 24 a8 00 00 00 	mov    DWORD PTR [rsp+0xa8],eax
  824ae5:	e8 96 25 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  824aea:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  824af0:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  824af5:	f3 0f 10 1d 93 3c 78 00 	movss  xmm3,DWORD PTR [rip+0x783c93]        # fa8790 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xf0>
  824afd:	f3 0f 11 4c 24 68    	movss  DWORD PTR [rsp+0x68],xmm1
  824b03:	f3 0f 10 a4 24 a8 00 00 00 	movss  xmm4,DWORD PTR [rsp+0xa8]
  824b0c:	48 89 84 24 b0 00 00 00 	mov    QWORD PTR [rsp+0xb0],rax
  824b14:	f3 0f 10 8c 24 b4 00 00 00 	movss  xmm1,DWORD PTR [rsp+0xb4]
  824b1d:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  824b22:	f3 0f 5c 8c 24 a4 00 00 00 	subss  xmm1,DWORD PTR [rsp+0xa4]
  824b2b:	8b 44 24 68          	mov    eax,DWORD PTR [rsp+0x68]
  824b2f:	f3 0f 10 84 24 b0 00 00 00 	movss  xmm0,DWORD PTR [rsp+0xb0]
  824b38:	f3 0f 10 ac 24 a0 00 00 00 	movss  xmm5,DWORD PTR [rsp+0xa0]
  824b41:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  824b48:	f3 0f 10 94 24 b8 00 00 00 	movss  xmm2,DWORD PTR [rsp+0xb8]
  824b51:	0f 54 cb             	andps  xmm1,xmm3
  824b54:	0f 2e 0d 69 99 7a 00 	ucomiss xmm1,DWORD PTR [rip+0x7a9969]        # fce4c4 <vtable for iInventoryListener+0x84>
  824b5b:	76 4e                	jbe    824bab <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x15b>
  824b5d:	4d 85 ed             	test   r13,r13
  824b60:	0f 84 ac 01 00 00    	je     824d12 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x2c2>
  824b66:	be 23 00 00 00       	mov    esi,0x23
  824b6b:	4c 89 ef             	mov    rdi,r13
  824b6e:	f3 0f 11 44 24 20    	movss  DWORD PTR [rsp+0x20],xmm0
  824b74:	f3 0f 11 54 24 40    	movss  DWORD PTR [rsp+0x40],xmm2
  824b7a:	f3 0f 11 64 24 30    	movss  DWORD PTR [rsp+0x30],xmm4
  824b80:	f3 0f 11 6c 24 10    	movss  DWORD PTR [rsp+0x10],xmm5
  824b86:	e8 15 17 fd ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  824b8b:	84 c0                	test   al,al
  824b8d:	f3 0f 10 44 24 20    	movss  xmm0,DWORD PTR [rsp+0x20]
  824b93:	f3 0f 10 54 24 40    	movss  xmm2,DWORD PTR [rsp+0x40]
  824b99:	f3 0f 10 64 24 30    	movss  xmm4,DWORD PTR [rsp+0x30]
  824b9f:	f3 0f 10 6c 24 10    	movss  xmm5,DWORD PTR [rsp+0x10]
  824ba5:	0f 84 67 01 00 00    	je     824d12 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x2c2>
  824bab:	f3 0f 5c c5          	subss  xmm0,xmm5
  824baf:	0f 57 c9             	xorps  xmm1,xmm1
  824bb2:	f3 0f 5c d4          	subss  xmm2,xmm4
  824bb6:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  824bbd:	f3 0f 59 c0          	mulss  xmm0,xmm0
  824bc1:	f3 0f 59 d2          	mulss  xmm2,xmm2
  824bc5:	f3 0f 58 c1          	addss  xmm0,xmm1
  824bc9:	f3 0f 58 c2          	addss  xmm0,xmm2
  824bcd:	f3 0f 51 d0          	sqrtss xmm2,xmm0
  824bd1:	f3 0f 10 85 94 01 00 00 	movss  xmm0,DWORD PTR [rbp+0x194]
  824bd9:	0f 28 d8             	movaps xmm3,xmm0
  824bdc:	f3 0f c2 d9 05       	cmpnltss xmm3,xmm1
  824be1:	0f 54 c3             	andps  xmm0,xmm3
  824be4:	0f 28 d9             	movaps xmm3,xmm1
  824be7:	f3 0f 5f 8b 94 01 00 00 	maxss  xmm1,DWORD PTR [rbx+0x194]
  824bef:	0f 56 d8             	orps   xmm3,xmm0
  824bf2:	f3 0f 10 83 e0 04 00 00 	movss  xmm0,DWORD PTR [rbx+0x4e0]
  824bfa:	f3 0f 59 83 98 00 00 00 	mulss  xmm0,DWORD PTR [rbx+0x98]
  824c02:	f3 0f 5c d3          	subss  xmm2,xmm3
  824c06:	f3 0f 58 05 da 3a 78 00 	addss  xmm0,DWORD PTR [rip+0x783ada]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  824c0e:	f3 0f 5c d1          	subss  xmm2,xmm1
  824c12:	f3 0f 58 40 6c       	addss  xmm0,DWORD PTR [rax+0x6c]
  824c17:	f3 0f 59 83 dc 04 00 00 	mulss  xmm0,DWORD PTR [rbx+0x4dc]
  824c1f:	f3 0f 58 44 24 5c    	addss  xmm0,DWORD PTR [rsp+0x5c]
  824c25:	0f 2e d0             	ucomiss xmm2,xmm0
  824c28:	0f 96 c0             	setbe  al
  824c2b:	48 81 c4 c8 00 00 00 	add    rsp,0xc8
  824c32:	5b                   	pop    rbx
  824c33:	5d                   	pop    rbp
  824c34:	41 5c                	pop    r12
  824c36:	41 5d                	pop    r13
  824c38:	c3                   	ret
  824c39:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  824c40:	ba 07 00 00 00       	mov    edx,0x7
  824c45:	be 4e 00 00 00       	mov    esi,0x4e
  824c4a:	48 89 df             	mov    rdi,rbx
  824c4d:	e8 8e eb fe ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  824c52:	48 85 ed             	test   rbp,rbp
  824c55:	f3 0f 11 44 24 5c    	movss  DWORD PTR [rsp+0x5c],xmm0
  824c5b:	0f 85 46 fe ff ff    	jne    824aa7 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x57>
  824c61:	4d 85 e4             	test   r12,r12
  824c64:	b8 01 00 00 00       	mov    eax,0x1
  824c69:	74 c0                	je     824c2b <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x1db>
  824c6b:	be 01 00 00 00       	mov    esi,0x1
  824c70:	48 89 df             	mov    rdi,rbx
  824c73:	e8 08 24 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  824c78:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  824c7e:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  824c83:	be 01 00 00 00       	mov    esi,0x1
  824c88:	f3 0f 11 4c 24 68    	movss  DWORD PTR [rsp+0x68],xmm1
  824c8e:	4c 89 e7             	mov    rdi,r12
  824c91:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  824c96:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  824c9b:	8b 44 24 68          	mov    eax,DWORD PTR [rsp+0x68]
  824c9f:	89 44 24 78          	mov    DWORD PTR [rsp+0x78],eax
  824ca3:	e8 d8 23 1c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  824ca8:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  824cae:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  824cb3:	f3 0f 11 4c 24 68    	movss  DWORD PTR [rsp+0x68],xmm1
  824cb9:	f3 0f 10 0d cf 3a 78 00 	movss  xmm1,DWORD PTR [rip+0x783acf]        # fa8790 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xf0>
  824cc1:	f3 0f 10 64 24 78    	movss  xmm4,DWORD PTR [rsp+0x78]
  824cc7:	48 89 84 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rax
  824ccf:	f3 0f 10 84 24 84 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x84]
  824cd8:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  824cdd:	f3 0f 5c 44 24 74    	subss  xmm0,DWORD PTR [rsp+0x74]
  824ce3:	8b 44 24 68          	mov    eax,DWORD PTR [rsp+0x68]
  824ce7:	f3 0f 10 9c 24 80 00 00 00 	movss  xmm3,DWORD PTR [rsp+0x80]
  824cf0:	f3 0f 10 54 24 70    	movss  xmm2,DWORD PTR [rsp+0x70]
  824cf6:	89 84 24 88 00 00 00 	mov    DWORD PTR [rsp+0x88],eax
  824cfd:	f3 0f 10 ac 24 88 00 00 00 	movss  xmm5,DWORD PTR [rsp+0x88]
  824d06:	0f 54 c1             	andps  xmm0,xmm1
  824d09:	0f 2e 05 b4 97 7a 00 	ucomiss xmm0,DWORD PTR [rip+0x7a97b4]        # fce4c4 <vtable for iInventoryListener+0x84>
  824d10:	76 16                	jbe    824d28 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x2d8>
  824d12:	48 81 c4 c8 00 00 00 	add    rsp,0xc8
  824d19:	31 c0                	xor    eax,eax
  824d1b:	5b                   	pop    rbx
  824d1c:	5d                   	pop    rbp
  824d1d:	41 5c                	pop    r12
  824d1f:	41 5d                	pop    r13
  824d21:	c3                   	ret
  824d22:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  824d28:	f3 0f 5c da          	subss  xmm3,xmm2
  824d2c:	0f 57 c9             	xorps  xmm1,xmm1
  824d2f:	f3 0f 5c ec          	subss  xmm5,xmm4
  824d33:	48 8d bc 24 90 00 00 00 	lea    rdi,[rsp+0x90]
  824d3b:	f3 0f 11 8c 24 94 00 00 00 	movss  DWORD PTR [rsp+0x94],xmm1
  824d44:	f3 0f 11 9c 24 90 00 00 00 	movss  DWORD PTR [rsp+0x90],xmm3
  824d4d:	f3 0f 11 4c 24 40    	movss  DWORD PTR [rsp+0x40],xmm1
  824d53:	f3 0f 11 ac 24 98 00 00 00 	movss  DWORD PTR [rsp+0x98],xmm5
  824d5c:	e8 ef 54 d8 ff       	call   5aa250 <Ogre::Vector3::length() const>
  824d61:	f3 41 0f 10 94 24 94 01 00 00 	movss  xmm2,DWORD PTR [r12+0x194]
  824d6b:	0f 28 da             	movaps xmm3,xmm2
  824d6e:	f3 0f 10 4c 24 40    	movss  xmm1,DWORD PTR [rsp+0x40]
  824d74:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  824d7b:	f3 0f c2 d9 05       	cmpnltss xmm3,xmm1
  824d80:	0f 54 d3             	andps  xmm2,xmm3
  824d83:	0f 28 d9             	movaps xmm3,xmm1
  824d86:	f3 0f 5f 8b 94 01 00 00 	maxss  xmm1,DWORD PTR [rbx+0x194]
  824d8e:	0f 56 da             	orps   xmm3,xmm2
  824d91:	f3 0f 10 93 e0 04 00 00 	movss  xmm2,DWORD PTR [rbx+0x4e0]
  824d99:	f3 0f 59 93 98 00 00 00 	mulss  xmm2,DWORD PTR [rbx+0x98]
  824da1:	f3 0f 5c c3          	subss  xmm0,xmm3
  824da5:	f3 0f 58 15 3b 39 78 00 	addss  xmm2,DWORD PTR [rip+0x78393b]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  824dad:	f3 0f 5c c1          	subss  xmm0,xmm1
  824db1:	f3 0f 58 50 6c       	addss  xmm2,DWORD PTR [rax+0x6c]
  824db6:	f3 0f 59 93 dc 04 00 00 	mulss  xmm2,DWORD PTR [rbx+0x4dc]
  824dbe:	f3 0f 58 54 24 5c    	addss  xmm2,DWORD PTR [rsp+0x5c]
  824dc4:	0f 2e c2             	ucomiss xmm0,xmm2
  824dc7:	0f 96 c0             	setbe  al
  824dca:	e9 5c fe ff ff       	jmp    824c2b <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x1db>
  824dcf:	90                   	nop
  824dd0:	4c 8b af 98 04 00 00 	mov    r13,QWORD PTR [rdi+0x498]
  824dd7:	4d 85 ed             	test   r13,r13
  824dda:	0f 84 b5 fc ff ff    	je     824a95 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x45>
  824de0:	e9 9b fc ff ff       	jmp    824a80 <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x30>
  824de5:	0f 1f 00             	nop    DWORD PTR [rax]
  824de8:	31 f6                	xor    esi,esi
  824dea:	e8 d1 cd fe ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  824def:	31 c0                	xor    eax,eax
  824df1:	e9 35 fe ff ff       	jmp    824c2b <CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)+0x1db>
  824df6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]

