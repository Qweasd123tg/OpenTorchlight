# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
000000000091cbb0 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>:
  91cbb0:	41 55                	push   r13
  91cbb2:	41 89 cd             	mov    r13d,ecx
  91cbb5:	41 54                	push   r12
  91cbb7:	41 89 f4             	mov    r12d,esi
  91cbba:	55                   	push   rbp
  91cbbb:	53                   	push   rbx
  91cbbc:	48 83 ec 18          	sub    rsp,0x18
  91cbc0:	83 fa 0c             	cmp    edx,0xc
  91cbc3:	74 43                	je     91cc08 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x58>
  91cbc5:	8b 77 38             	mov    esi,DWORD PTR [rdi+0x38]
  91cbc8:	85 f6                	test   esi,esi
  91cbca:	74 3c                	je     91cc08 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x58>
  91cbcc:	8b 6f 3c             	mov    ebp,DWORD PTR [rdi+0x3c]
  91cbcf:	31 db                	xor    ebx,ebx
  91cbd1:	31 c0                	xor    eax,eax
  91cbd3:	eb 1f                	jmp    91cbf4 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x44>
  91cbd5:	0f 1f 00             	nop    DWORD PTR [rax]
  91cbd8:	48 8b 4f 30          	mov    rcx,QWORD PTR [rdi+0x30]
  91cbdc:	48 8b 09             	mov    rcx,QWORD PTR [rcx]
  91cbdf:	48 85 c9             	test   rcx,rcx
  91cbe2:	74 05                	je     91cbe9 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x39>
  91cbe4:	3b 51 18             	cmp    edx,DWORD PTR [rcx+0x18]
  91cbe7:	74 37                	je     91cc20 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x70>
  91cbe9:	83 c0 01             	add    eax,0x1
  91cbec:	48 83 c3 08          	add    rbx,0x8
  91cbf0:	39 f0                	cmp    eax,esi
  91cbf2:	73 14                	jae    91cc08 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x58>
  91cbf4:	39 e8                	cmp    eax,ebp
  91cbf6:	73 e0                	jae    91cbd8 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x28>
  91cbf8:	48 89 d9             	mov    rcx,rbx
  91cbfb:	48 03 4f 30          	add    rcx,QWORD PTR [rdi+0x30]
  91cbff:	eb db                	jmp    91cbdc <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x2c>
  91cc01:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  91cc08:	48 83 c4 18          	add    rsp,0x18
  91cc0c:	0f 57 c0             	xorps  xmm0,xmm0
  91cc0f:	5b                   	pop    rbx
  91cc10:	5d                   	pop    rbp
  91cc11:	41 5c                	pop    r12
  91cc13:	41 5d                	pop    r13
  91cc15:	c3                   	ret
  91cc16:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  91cc20:	48 8b 69 10          	mov    rbp,QWORD PTR [rcx+0x10]
  91cc24:	48 85 ed             	test   rbp,rbp
  91cc27:	74 df                	je     91cc08 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x58>
  91cc29:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  91cc2d:	44 89 e9             	mov    ecx,r13d
  91cc30:	31 f6                	xor    esi,esi
  91cc32:	44 89 e2             	mov    edx,r12d
  91cc35:	48 89 ef             	mov    rdi,rbp
  91cc38:	0f 57 c0             	xorps  xmm0,xmm0
  91cc3b:	ff 90 48 02 00 00    	call   QWORD PTR [rax+0x248]
  91cc41:	e8 32 6a c3 ff       	call   553678 <ceilf@plt>
  91cc46:	8b 8d f0 03 00 00    	mov    ecx,DWORD PTR [rbp+0x3f0]
  91cc4c:	0f 28 c8             	movaps xmm1,xmm0
  91cc4f:	85 c9                	test   ecx,ecx
  91cc51:	74 65                	je     91ccb8 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x108>
  91cc53:	31 db                	xor    ebx,ebx
  91cc55:	eb 45                	jmp    91cc9c <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0xec>
  91cc57:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  91cc60:	48 8b 85 e8 03 00 00 	mov    rax,QWORD PTR [rbp+0x3e8]
  91cc67:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  91cc6a:	31 f6                	xor    esi,esi
  91cc6c:	44 89 e9             	mov    ecx,r13d
  91cc6f:	44 89 e2             	mov    edx,r12d
  91cc72:	0f 57 c0             	xorps  xmm0,xmm0
  91cc75:	83 c3 01             	add    ebx,0x1
  91cc78:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  91cc7b:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  91cc80:	ff 90 48 02 00 00    	call   QWORD PTR [rax+0x248]
  91cc86:	e8 ed 69 c3 ff       	call   553678 <ceilf@plt>
  91cc8b:	3b 9d f0 03 00 00    	cmp    ebx,DWORD PTR [rbp+0x3f0]
  91cc91:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  91cc96:	f3 0f 58 c8          	addss  xmm1,xmm0
  91cc9a:	73 1c                	jae    91ccb8 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x108>
  91cc9c:	39 9d f4 03 00 00    	cmp    DWORD PTR [rbp+0x3f4],ebx
  91cca2:	76 bc                	jbe    91cc60 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0xb0>
  91cca4:	89 d8                	mov    eax,ebx
  91cca6:	48 c1 e0 03          	shl    rax,0x3
  91ccaa:	48 03 85 e8 03 00 00 	add    rax,QWORD PTR [rbp+0x3e8]
  91ccb1:	eb b4                	jmp    91cc67 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0xb7>
  91ccb3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  91ccb8:	48 83 c4 18          	add    rsp,0x18
  91ccbc:	0f 28 c1             	movaps xmm0,xmm1
  91ccbf:	5b                   	pop    rbx
  91ccc0:	5d                   	pop    rbp
  91ccc1:	41 5c                	pop    r12
  91ccc3:	41 5d                	pop    r13
  91ccc5:	e9 ae 69 c3 ff       	jmp    553678 <ceilf@plt>
  91ccca:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

