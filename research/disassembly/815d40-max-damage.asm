# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000815d40 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)>:
  815d40:	41 55                	push   r13
  815d42:	41 54                	push   r12
  815d44:	49 89 f4             	mov    r12,rsi
  815d47:	55                   	push   rbp
  815d48:	53                   	push   rbx
  815d49:	48 89 fb             	mov    rbx,rdi
  815d4c:	48 83 ec 28          	sub    rsp,0x28
  815d50:	48 85 f6             	test   rsi,rsi
  815d53:	0f 84 67 04 00 00    	je     8161c0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x480>
  815d59:	48 85 d2             	test   rdx,rdx
  815d5c:	74 15                	je     815d73 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x33>
  815d5e:	be 1b 00 00 00       	mov    esi,0x1b
  815d63:	48 89 d7             	mov    rdi,rdx
  815d66:	e8 35 05 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  815d6b:	84 c0                	test   al,al
  815d6d:	0f 85 65 02 00 00    	jne    815fd8 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x298>
  815d73:	80 bb a0 04 00 00 00 	cmp    BYTE PTR [rbx+0x4a0],0x0
  815d7a:	0f 85 30 02 00 00    	jne    815fb0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x270>
  815d80:	48 8b 93 f8 03 00 00 	mov    rdx,QWORD PTR [rbx+0x3f8]
  815d87:	48 8b 83 00 04 00 00 	mov    rax,QWORD PTR [rbx+0x400]
  815d8e:	31 ed                	xor    ebp,ebp
  815d90:	48 29 d0             	sub    rax,rdx
  815d93:	48 c1 f8 03          	sar    rax,0x3
  815d97:	48 85 c0             	test   rax,rax
  815d9a:	74 0a                	je     815da6 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x66>
  815d9c:	48 8b 02             	mov    rax,QWORD PTR [rdx]
  815d9f:	8b 68 24             	mov    ebp,DWORD PTR [rax+0x24]
  815da2:	44 8b 68 78          	mov    r13d,DWORD PTR [rax+0x78]
  815da6:	4c 8b a3 98 04 00 00 	mov    r12,QWORD PTR [rbx+0x498]
  815dad:	4d 85 e4             	test   r12,r12
  815db0:	0f 84 14 02 00 00    	je     815fca <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x28a>
  815db6:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  815dbd:	be 01 00 00 00       	mov    esi,0x1
  815dc2:	e8 99 56 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  815dc7:	49 39 c4             	cmp    r12,rax
  815dca:	0f 84 90 04 00 00    	je     816260 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x520>
  815dd0:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  815dd7:	41 bc 01 00 00 00    	mov    r12d,0x1
  815ddd:	48 85 ff             	test   rdi,rdi
  815de0:	0f 84 0a 02 00 00    	je     815ff0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x2b0>
  815de6:	be 23 00 00 00       	mov    esi,0x23
  815deb:	e8 b0 04 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  815df0:	84 c0                	test   al,al
  815df2:	0f 84 f8 01 00 00    	je     815ff0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x2b0>
  815df8:	ba 07 00 00 00       	mov    edx,0x7
  815dfd:	be 10 00 00 00       	mov    esi,0x10
  815e02:	48 89 df             	mov    rdi,rbx
  815e05:	e8 d6 d9 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  815e0a:	f3 0f 10 0d 2a ea 78 00 	movss  xmm1,DWORD PTR [rip+0x78ea2a]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  815e12:	48 89 df             	mov    rdi,rbx
  815e15:	f3 0f 5e c1          	divss  xmm0,xmm1
  815e19:	f3 0f 11 4c 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm1
  815e1f:	f3 0f 11 04 24       	movss  DWORD PTR [rsp],xmm0
  815e24:	e8 77 db ff ff       	call   8139a0 <CCharacter::dexterity()>
  815e29:	f3 0f 2a c8          	cvtsi2ss xmm1,eax
  815e2d:	be 01 00 00 00       	mov    esi,0x1
  815e32:	f3 0f 10 04 24       	movss  xmm0,DWORD PTR [rsp]
  815e37:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  815e3e:	f3 0f 5e 4c 24 1c    	divss  xmm1,DWORD PTR [rsp+0x1c]
  815e44:	f3 0f 58 c1          	addss  xmm0,xmm1
  815e48:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  815e4e:	e8 0d 56 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  815e53:	48 85 c0             	test   rax,rax
  815e56:	74 39                	je     815e91 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x151>
  815e58:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  815e5f:	31 f6                	xor    esi,esi
  815e61:	e8 fa 55 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  815e66:	48 85 c0             	test   rax,rax
  815e69:	74 26                	je     815e91 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x151>
  815e6b:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  815e72:	be 01 00 00 00       	mov    esi,0x1
  815e77:	e8 e4 55 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  815e7c:	be 15 00 00 00       	mov    esi,0x15
  815e81:	48 89 c7             	mov    rdi,rax
  815e84:	e8 17 04 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  815e89:	84 c0                	test   al,al
  815e8b:	0f 84 ff 02 00 00    	je     816190 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x450>
  815e91:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  815e98:	be a3 00 00 00       	mov    esi,0xa3
  815e9d:	e8 fe 03 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  815ea2:	84 c0                	test   al,al
  815ea4:	0f 85 86 03 00 00    	jne    816230 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x4f0>
  815eaa:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  815eb1:	be a4 00 00 00       	mov    esi,0xa4
  815eb6:	e8 e5 03 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  815ebb:	84 c0                	test   al,al
  815ebd:	0f 85 3d 03 00 00    	jne    816200 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x4c0>
  815ec3:	44 89 e9             	mov    ecx,r13d
  815ec6:	44 89 e2             	mov    edx,r12d
  815ec9:	be 19 00 00 00       	mov    esi,0x19
  815ece:	48 89 df             	mov    rdi,rbx
  815ed1:	e8 3a d8 ff ff       	call   813710 <CCharacter::getEffectValue(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>
  815ed6:	0f 28 d0             	movaps xmm2,xmm0
  815ed9:	48 89 df             	mov    rdi,rbx
  815edc:	ba 06 00 00 00       	mov    edx,0x6
  815ee1:	be 19 00 00 00       	mov    esi,0x19
  815ee6:	f3 0f 5e 54 24 1c    	divss  xmm2,DWORD PTR [rsp+0x1c]
  815eec:	f3 0f 58 54 24 18    	addss  xmm2,DWORD PTR [rsp+0x18]
  815ef2:	f3 0f 11 14 24       	movss  DWORD PTR [rsp],xmm2
  815ef7:	e8 e4 d8 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  815efc:	0f 28 c8             	movaps xmm1,xmm0
  815eff:	48 8b bb 40 06 00 00 	mov    rdi,QWORD PTR [rbx+0x640]
  815f06:	f3 0f 10 14 24       	movss  xmm2,DWORD PTR [rsp]
  815f0b:	f3 0f 5e 4c 24 1c    	divss  xmm1,DWORD PTR [rsp+0x1c]
  815f11:	48 85 ff             	test   rdi,rdi
  815f14:	f3 0f 58 ca          	addss  xmm1,xmm2
  815f18:	74 23                	je     815f3d <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x1fd>
  815f1a:	ba 07 00 00 00       	mov    edx,0x7
  815f1f:	be 5b 00 00 00       	mov    esi,0x5b
  815f24:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  815f29:	e8 b2 d8 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  815f2e:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  815f34:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  815f39:	f3 0f 58 c8          	addss  xmm1,xmm0
  815f3d:	f3 0f 2a c5          	cvtsi2ss xmm0,ebp
  815f41:	f3 0f 59 c1          	mulss  xmm0,xmm1
  815f45:	e8 2e d7 d3 ff       	call   553678 <ceilf@plt>
  815f4a:	0f 28 c8             	movaps xmm1,xmm0
  815f4d:	ba 07 00 00 00       	mov    edx,0x7
  815f52:	be 01 00 00 00       	mov    esi,0x1
  815f57:	48 89 df             	mov    rdi,rbx
  815f5a:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  815f5f:	e8 7c d8 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  815f64:	e8 0f d7 d3 ff       	call   553678 <ceilf@plt>
  815f69:	f3 0f 2c 14 24       	cvttss2si edx,DWORD PTR [rsp]
  815f6e:	f3 0f 2c c0          	cvttss2si eax,xmm0
  815f72:	44 89 e9             	mov    ecx,r13d
  815f75:	be 0a 00 00 00       	mov    esi,0xa
  815f7a:	48 89 df             	mov    rdi,rbx
  815f7d:	8d 04 02             	lea    eax,[rdx+rax*1]
  815f80:	44 89 e2             	mov    edx,r12d
  815f83:	8d 2c 28             	lea    ebp,[rax+rbp*1]
  815f86:	e8 85 d7 ff ff       	call   813710 <CCharacter::getEffectValue(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>
  815f8b:	f3 0f 2c c0          	cvttss2si eax,xmm0
  815f8f:	8d 2c 28             	lea    ebp,[rax+rbp*1]
  815f92:	f3 0f 2a c5          	cvtsi2ss xmm0,ebp
  815f96:	f3 0f 59 83 20 07 00 00 	mulss  xmm0,DWORD PTR [rbx+0x720]
  815f9e:	f3 0f 2c c0          	cvttss2si eax,xmm0
  815fa2:	48 83 c4 28          	add    rsp,0x28
  815fa6:	5b                   	pop    rbx
  815fa7:	5d                   	pop    rbp
  815fa8:	41 5c                	pop    r12
  815faa:	41 5d                	pop    r13
  815fac:	c3                   	ret
  815fad:	0f 1f 00             	nop    DWORD PTR [rax]
  815fb0:	41 8b 6c 24 24       	mov    ebp,DWORD PTR [r12+0x24]
  815fb5:	45 8b 6c 24 78       	mov    r13d,DWORD PTR [r12+0x78]
  815fba:	4c 8b a3 98 04 00 00 	mov    r12,QWORD PTR [rbx+0x498]
  815fc1:	4d 85 e4             	test   r12,r12
  815fc4:	0f 85 ec fd ff ff    	jne    815db6 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x76>
  815fca:	31 ff                	xor    edi,edi
  815fcc:	e9 06 fe ff ff       	jmp    815dd7 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x97>
  815fd1:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  815fd8:	48 89 df             	mov    rdi,rbx
  815fdb:	e8 90 a1 ff ff       	call   810170 <CCharacter::alignment()>
  815fe0:	80 bb a0 04 00 00 00 	cmp    BYTE PTR [rbx+0x4a0],0x0
  815fe7:	0f 84 93 fd ff ff    	je     815d80 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x40>
  815fed:	eb c1                	jmp    815fb0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x270>
  815fef:	90                   	nop
  815ff0:	ba 07 00 00 00       	mov    edx,0x7
  815ff5:	be 0f 00 00 00       	mov    esi,0xf
  815ffa:	48 89 df             	mov    rdi,rbx
  815ffd:	e8 de d7 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  816002:	f3 0f 10 0d 32 e8 78 00 	movss  xmm1,DWORD PTR [rip+0x78e832]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  81600a:	48 89 df             	mov    rdi,rbx
  81600d:	f3 0f 5e c1          	divss  xmm0,xmm1
  816011:	f3 0f 11 4c 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm1
  816017:	f3 0f 11 04 24       	movss  DWORD PTR [rsp],xmm0
  81601c:	e8 0f d9 ff ff       	call   813930 <CCharacter::strength()>
  816021:	f3 0f 2a c8          	cvtsi2ss xmm1,eax
  816025:	be 01 00 00 00       	mov    esi,0x1
  81602a:	f3 0f 10 04 24       	movss  xmm0,DWORD PTR [rsp]
  81602f:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  816036:	f3 0f 5e 4c 24 1c    	divss  xmm1,DWORD PTR [rsp+0x1c]
  81603c:	f3 0f 58 c1          	addss  xmm0,xmm1
  816040:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  816046:	e8 15 54 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  81604b:	48 85 c0             	test   rax,rax
  81604e:	74 39                	je     816089 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x349>
  816050:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  816057:	31 f6                	xor    esi,esi
  816059:	e8 02 54 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  81605e:	48 85 c0             	test   rax,rax
  816061:	74 26                	je     816089 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x349>
  816063:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  81606a:	be 01 00 00 00       	mov    esi,0x1
  81606f:	e8 ec 53 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  816074:	be 15 00 00 00       	mov    esi,0x15
  816079:	48 89 c7             	mov    rdi,rax
  81607c:	e8 1f 02 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  816081:	84 c0                	test   al,al
  816083:	0f 84 d7 00 00 00    	je     816160 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x420>
  816089:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  816090:	48 85 ff             	test   rdi,rdi
  816093:	74 2b                	je     8160c0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x380>
  816095:	be a2 00 00 00       	mov    esi,0xa2
  81609a:	e8 01 02 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  81609f:	84 c0                	test   al,al
  8160a1:	0f 85 f9 01 00 00    	jne    8162a0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x560>
  8160a7:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  8160ae:	be a4 00 00 00       	mov    esi,0xa4
  8160b3:	e8 e8 01 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8160b8:	84 c0                	test   al,al
  8160ba:	0f 85 b0 01 00 00    	jne    816270 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x530>
  8160c0:	44 89 e9             	mov    ecx,r13d
  8160c3:	44 89 e2             	mov    edx,r12d
  8160c6:	be 19 00 00 00       	mov    esi,0x19
  8160cb:	48 89 df             	mov    rdi,rbx
  8160ce:	e8 3d d6 ff ff       	call   813710 <CCharacter::getEffectValue(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>
  8160d3:	0f 28 d0             	movaps xmm2,xmm0
  8160d6:	48 89 df             	mov    rdi,rbx
  8160d9:	ba 06 00 00 00       	mov    edx,0x6
  8160de:	be 19 00 00 00       	mov    esi,0x19
  8160e3:	f3 0f 5e 54 24 1c    	divss  xmm2,DWORD PTR [rsp+0x1c]
  8160e9:	f3 0f 58 54 24 18    	addss  xmm2,DWORD PTR [rsp+0x18]
  8160ef:	f3 0f 11 14 24       	movss  DWORD PTR [rsp],xmm2
  8160f4:	e8 e7 d6 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8160f9:	0f 28 c8             	movaps xmm1,xmm0
  8160fc:	48 8b bb 40 06 00 00 	mov    rdi,QWORD PTR [rbx+0x640]
  816103:	f3 0f 10 14 24       	movss  xmm2,DWORD PTR [rsp]
  816108:	f3 0f 5e 4c 24 1c    	divss  xmm1,DWORD PTR [rsp+0x1c]
  81610e:	48 85 ff             	test   rdi,rdi
  816111:	f3 0f 58 ca          	addss  xmm1,xmm2
  816115:	74 23                	je     81613a <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x3fa>
  816117:	ba 07 00 00 00       	mov    edx,0x7
  81611c:	be 5b 00 00 00       	mov    esi,0x5b
  816121:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  816126:	e8 b5 d6 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  81612b:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  816131:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  816136:	f3 0f 58 c8          	addss  xmm1,xmm0
  81613a:	f3 0f 2a c5          	cvtsi2ss xmm0,ebp
  81613e:	f3 0f 59 c1          	mulss  xmm0,xmm1
  816142:	e8 31 d5 d3 ff       	call   553678 <ceilf@plt>
  816147:	ba 07 00 00 00       	mov    edx,0x7
  81614c:	0f 28 c8             	movaps xmm1,xmm0
  81614f:	31 f6                	xor    esi,esi
  816151:	e9 01 fe ff ff       	jmp    815f57 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x217>
  816156:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  816160:	ba 07 00 00 00       	mov    edx,0x7
  816165:	be 58 00 00 00       	mov    esi,0x58
  81616a:	48 89 df             	mov    rdi,rbx
  81616d:	e8 6e d6 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  816172:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  816178:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  81617e:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  816184:	e9 00 ff ff ff       	jmp    816089 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x349>
  816189:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  816190:	ba 07 00 00 00       	mov    edx,0x7
  816195:	be 58 00 00 00       	mov    esi,0x58
  81619a:	48 89 df             	mov    rdi,rbx
  81619d:	e8 3e d6 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8161a2:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  8161a8:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  8161ae:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8161b4:	e9 d8 fc ff ff       	jmp    815e91 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x151>
  8161b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8161c0:	4c 8b a7 90 03 00 00 	mov    r12,QWORD PTR [rdi+0x390]
  8161c7:	4d 85 e4             	test   r12,r12
  8161ca:	0f 85 89 fb ff ff    	jne    815d59 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x19>
  8161d0:	31 f6                	xor    esi,esi
  8161d2:	48 89 54 24 10       	mov    QWORD PTR [rsp+0x10],rdx
  8161d7:	e8 e4 b9 ff ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  8161dc:	4c 8b a3 90 03 00 00 	mov    r12,QWORD PTR [rbx+0x390]
  8161e3:	31 c0                	xor    eax,eax
  8161e5:	48 8b 54 24 10       	mov    rdx,QWORD PTR [rsp+0x10]
  8161ea:	4d 85 e4             	test   r12,r12
  8161ed:	0f 85 66 fb ff ff    	jne    815d59 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x19>
  8161f3:	e9 aa fd ff ff       	jmp    815fa2 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x262>
  8161f8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  816200:	ba 07 00 00 00       	mov    edx,0x7
  816205:	be 67 00 00 00       	mov    esi,0x67
  81620a:	48 89 df             	mov    rdi,rbx
  81620d:	e8 ce d5 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  816212:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  816218:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  81621e:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  816224:	e9 9a fc ff ff       	jmp    815ec3 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x183>
  816229:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  816230:	ba 07 00 00 00       	mov    edx,0x7
  816235:	be 66 00 00 00       	mov    esi,0x66
  81623a:	48 89 df             	mov    rdi,rbx
  81623d:	e8 9e d5 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  816242:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  816248:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  81624e:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  816254:	e9 51 fc ff ff       	jmp    815eaa <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x16a>
  816259:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  816260:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  816267:	45 31 e4             	xor    r12d,r12d
  81626a:	e9 6e fb ff ff       	jmp    815ddd <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x9d>
  81626f:	90                   	nop
  816270:	ba 07 00 00 00       	mov    edx,0x7
  816275:	be 67 00 00 00       	mov    esi,0x67
  81627a:	48 89 df             	mov    rdi,rbx
  81627d:	e8 5e d5 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  816282:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  816288:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  81628e:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  816294:	e9 27 fe ff ff       	jmp    8160c0 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x380>
  816299:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8162a0:	ba 07 00 00 00       	mov    edx,0x7
  8162a5:	be 63 00 00 00       	mov    esi,0x63
  8162aa:	48 89 df             	mov    rdi,rbx
  8162ad:	e8 2e d5 ff ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8162b2:	f3 0f 5e 44 24 1c    	divss  xmm0,DWORD PTR [rsp+0x1c]
  8162b8:	f3 0f 58 44 24 18    	addss  xmm0,DWORD PTR [rsp+0x18]
  8162be:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8162c4:	e9 de fd ff ff       	jmp    8160a7 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)+0x367>
  8162c9:	90                   	nop
  8162ca:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

