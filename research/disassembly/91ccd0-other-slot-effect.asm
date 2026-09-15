# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
000000000091ccd0 <CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>:
  91ccd0:	48 89 5c 24 e0       	mov    QWORD PTR [rsp-0x20],rbx
  91ccd5:	48 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],rbp
  91ccda:	48 89 fb             	mov    rbx,rdi
  91ccdd:	4c 89 64 24 f0       	mov    QWORD PTR [rsp-0x10],r12
  91cce2:	4c 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],r13
  91cce7:	41 89 d4             	mov    r12d,edx
  91ccea:	48 83 ec 38          	sub    rsp,0x38
  91ccee:	89 ca                	mov    edx,ecx
  91ccf0:	89 f5                	mov    ebp,esi
  91ccf2:	41 89 cd             	mov    r13d,ecx
  91ccf5:	e8 46 f9 ff ff       	call   91c640 <CInventory::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  91ccfa:	e8 79 69 c3 ff       	call   553678 <ceilf@plt>
  91ccff:	0f 57 d2             	xorps  xmm2,xmm2
  91cd02:	0f 28 c8             	movaps xmm1,xmm0
  91cd05:	0f 28 c2             	movaps xmm0,xmm2
  91cd08:	0f 2e ca             	ucomiss xmm1,xmm2
  91cd0b:	7a 23                	jp     91cd30 <CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x60>
  91cd0d:	75 21                	jne    91cd30 <CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x60>
  91cd0f:	48 8b 5c 24 18       	mov    rbx,QWORD PTR [rsp+0x18]
  91cd14:	48 8b 6c 24 20       	mov    rbp,QWORD PTR [rsp+0x20]
  91cd19:	4c 8b 64 24 28       	mov    r12,QWORD PTR [rsp+0x28]
  91cd1e:	4c 8b 6c 24 30       	mov    r13,QWORD PTR [rsp+0x30]
  91cd23:	48 83 c4 38          	add    rsp,0x38
  91cd27:	c3                   	ret
  91cd28:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  91cd30:	44 89 e9             	mov    ecx,r13d
  91cd33:	44 89 e2             	mov    edx,r12d
  91cd36:	89 ee                	mov    esi,ebp
  91cd38:	48 89 df             	mov    rdi,rbx
  91cd3b:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  91cd40:	e8 6b fe ff ff       	call   91cbb0 <CInventory::getEffectValueFromEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)>
  91cd45:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  91cd4a:	f3 0f 5c c8          	subss  xmm1,xmm0
  91cd4e:	0f 28 c1             	movaps xmm0,xmm1
  91cd51:	eb bc                	jmp    91cd0f <CInventory::getEffectValueMinusEquipmentSlot(EEFFECT_TYPE, EEQUIP_LOCATIONS, EDAMAGE_TYPES)+0x3f>
  91cd53:	90                   	nop
  91cd54:	66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 cs nop WORD PTR [rax+rax*1+0x0]

