# Source: earlier supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Declared original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Verified source text SHA-256: 59d876125b21e8e1a3e6b0f2f242632966b705218907de1ed5172baebc30d196
# Targeted Intel-syntax excerpt; the ELF is not included. See ../monster-ai-cooldown.md.

# Range: 0x8dfd80 <= instruction address < 0x8e02a8
  8dfd80:	41 54                	push   r12
  8dfd82:	0f 57 c9             	xorps  xmm1,xmm1
  8dfd85:	55                   	push   rbp
  8dfd86:	48 89 f5             	mov    rbp,rsi
  8dfd89:	53                   	push   rbx
  8dfd8a:	48 89 fb             	mov    rbx,rdi
  8dfd8d:	48 81 ec a0 00 00 00 	sub    rsp,0xa0
  8dfd94:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8dfd9a:	f3 0f 10 87 e8 07 00 00 	movss  xmm0,DWORD PTR [rdi+0x7e8]
  8dfda2:	0f 2e c1             	ucomiss xmm0,xmm1
  8dfda5:	77 51                	ja     8dfdf8 <CMonster::attackAI(float, CLevel&)+0x78>
  8dfda7:	48 83 bf 50 03 00 00 00 	cmp    QWORD PTR [rdi+0x350],0x0
  8dfdaf:	74 07                	je     8dfdb8 <CMonster::attackAI(float, CLevel&)+0x38>
  8dfdb1:	31 f6                	xor    esi,esi
  8dfdb3:	e8 68 4b f4 ff       	call   824920 <CCharacter::setTargetItem(CItem*)>
  8dfdb8:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8dfdbf:	48 85 ff             	test   rdi,rdi
  8dfdc2:	74 09                	je     8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfdc4:	e8 87 ea f2 ff       	call   80e850 <CCharacter::alive()>
  8dfdc9:	84 c0                	test   al,al
  8dfdcb:	75 33                	jne    8dfe00 <CMonster::attackAI(float, CLevel&)+0x80>
  8dfdcd:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8dfdd0:	be 02 00 00 00       	mov    esi,0x2
  8dfdd5:	48 89 df             	mov    rdi,rbx
  8dfdd8:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8dfdde:	31 f6                	xor    esi,esi
  8dfde0:	48 89 df             	mov    rdi,rbx
  8dfde3:	e8 28 55 f4 ff       	call   825310 <CCharacter::setTarget(CCharacter*)>
  8dfde8:	48 81 c4 a0 00 00 00 	add    rsp,0xa0
  8dfdef:	5b                   	pop    rbx
  8dfdf0:	5d                   	pop    rbp
  8dfdf1:	41 5c                	pop    r12
  8dfdf3:	c3                   	ret
  8dfdf4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8dfdf8:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8dfdfb:	31 f6                	xor    esi,esi
  8dfdfd:	eb d6                	jmp    8dfdd5 <CMonster::attackAI(float, CLevel&)+0x55>
  8dfdff:	90                   	nop
  8dfe00:	48 89 df             	mov    rdi,rbx
  8dfe03:	e8 38 46 f3 ff       	call   814440 <CCharacter::isPetNearDeath()>
  8dfe08:	84 c0                	test   al,al
  8dfe0a:	75 c1                	jne    8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfe0c:	4c 8b a3 40 03 00 00 	mov    r12,QWORD PTR [rbx+0x340]
  8dfe13:	4c 89 e7             	mov    rdi,r12
  8dfe16:	e8 25 46 f3 ff       	call   814440 <CCharacter::isPetNearDeath()>
  8dfe1b:	84 c0                	test   al,al
  8dfe1d:	75 ae                	jne    8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfe1f:	4c 89 e7             	mov    rdi,r12
  8dfe22:	e8 29 ea f2 ff       	call   80e850 <CCharacter::alive()>
  8dfe27:	84 c0                	test   al,al
  8dfe29:	74 a2                	je     8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfe2b:	41 8b 84 24 30 03 00 00 	mov    eax,DWORD PTR [r12+0x330]
  8dfe33:	83 f8 2a             	cmp    eax,0x2a
  8dfe36:	74 95                	je     8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfe38:	83 f8 29             	cmp    eax,0x29
  8dfe3b:	74 90                	je     8dfdcd <CMonster::attackAI(float, CLevel&)+0x4d>
  8dfe3d:	48 8b b3 40 03 00 00 	mov    rsi,QWORD PTR [rbx+0x340]
  8dfe44:	48 89 df             	mov    rdi,rbx
  8dfe47:	e8 84 04 f3 ff       	call   8102d0 <CCharacter::isFriend(CCharacter*)>
  8dfe4c:	84 c0                	test   al,al
  8dfe4e:	75 a8                	jne    8dfdf8 <CMonster::attackAI(float, CLevel&)+0x78>
  8dfe50:	48 83 bb 90 03 00 00 00 	cmp    QWORD PTR [rbx+0x390],0x0
  8dfe58:	74 09                	je     8dfe63 <CMonster::attackAI(float, CLevel&)+0xe3>
  8dfe5a:	80 bb f5 01 00 00 00 	cmp    BYTE PTR [rbx+0x1f5],0x0
  8dfe61:	74 75                	je     8dfed8 <CMonster::attackAI(float, CLevel&)+0x158>
  8dfe63:	31 f6                	xor    esi,esi
  8dfe65:	48 89 df             	mov    rdi,rbx
  8dfe68:	e8 53 1d f3 ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  8dfe6d:	48 83 bb 90 03 00 00 00 	cmp    QWORD PTR [rbx+0x390],0x0
  8dfe75:	74 09                	je     8dfe80 <CMonster::attackAI(float, CLevel&)+0x100>
  8dfe77:	80 bb f5 01 00 00 00 	cmp    BYTE PTR [rbx+0x1f5],0x0
  8dfe7e:	74 58                	je     8dfed8 <CMonster::attackAI(float, CLevel&)+0x158>
  8dfe80:	31 d2                	xor    edx,edx
  8dfe82:	31 f6                	xor    esi,esi
  8dfe84:	48 89 df             	mov    rdi,rbx
  8dfe87:	e8 84 f5 f2 ff       	call   80f410 <CCharacter::setActiveSkill(CSkill*, bool)>
  8dfe8c:	be 01 00 00 00       	mov    esi,0x1
  8dfe91:	48 89 df             	mov    rdi,rbx
  8dfe94:	e8 c7 50 ff ff       	call   8d4f60 <CMonster::selectOffensiveSkill(bool)>
  8dfe99:	48 83 bb 98 03 00 00 00 	cmp    QWORD PTR [rbx+0x398],0x0
  8dfea1:	0f 84 41 ff ff ff    	je     8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8dfea7:	31 d2                	xor    edx,edx
  8dfea9:	48 c7 c6 ff ff ff ff 	mov    rsi,0xffffffffffffffff
  8dfeb0:	48 89 df             	mov    rdi,rbx
  8dfeb3:	e8 b8 65 f4 ff       	call   826470 <CCharacter::inSkillRange(long long, bool)>
  8dfeb8:	85 c0                	test   eax,eax
  8dfeba:	0f 85 28 ff ff ff    	jne    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8dfec0:	48 c7 c6 ff ff ff ff 	mov    rsi,0xffffffffffffffff
  8dfec7:	48 89 df             	mov    rdi,rbx
  8dfeca:	e8 e1 7f f4 ff       	call   827eb0 <CCharacter::castSkill(long long)>
  8dfecf:	e9 14 ff ff ff       	jmp    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8dfed4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8dfed8:	be 01 00 00 00       	mov    esi,0x1
  8dfedd:	48 89 df             	mov    rdi,rbx
  8dfee0:	e8 9b 71 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8dfee5:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8dfeeb:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8dfef0:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8dfef7:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8dfefd:	be 01 00 00 00       	mov    esi,0x1
  8dff02:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8dff07:	48 89 84 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rax
  8dff0f:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8dff13:	89 84 24 88 00 00 00 	mov    DWORD PTR [rsp+0x88],eax
  8dff1a:	e8 61 71 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8dff1f:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8dff25:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8dff2a:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8dff30:	0f 57 d2             	xorps  xmm2,xmm2
  8dff33:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  8dff3b:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8dff40:	f3 0f 10 84 24 90 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x90]
  8dff49:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8dff4d:	f3 0f 5c 84 24 80 00 00 00 	subss  xmm0,DWORD PTR [rsp+0x80]
  8dff56:	89 84 24 98 00 00 00 	mov    DWORD PTR [rsp+0x98],eax
  8dff5d:	f3 0f 10 8c 24 98 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x98]
  8dff66:	f3 0f 5c 8c 24 88 00 00 00 	subss  xmm1,DWORD PTR [rsp+0x88]
  8dff6f:	f3 0f 59 c0          	mulss  xmm0,xmm0
  8dff73:	f3 0f 58 c2          	addss  xmm0,xmm2
  8dff77:	f3 0f 59 c9          	mulss  xmm1,xmm1
  8dff7b:	f3 0f 58 c1          	addss  xmm0,xmm1
  8dff7f:	f3 0f 51 c0          	sqrtss xmm0,xmm0
  8dff83:	0f 2e 83 70 03 00 00 	ucomiss xmm0,DWORD PTR [rbx+0x370]
  8dff8a:	0f 83 c8 00 00 00    	jae    8e0058 <CMonster::attackAI(float, CLevel&)+0x2d8>
  8dff90:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8dff97:	be 01 00 00 00       	mov    esi,0x1
  8dff9c:	e8 df 70 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8dffa1:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8dffa7:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8dffac:	48 8d 74 24 70       	lea    rsi,[rsp+0x70]
  8dffb1:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8dffb7:	48 89 df             	mov    rdi,rbx
  8dffba:	f3 0f 10 44 24 18    	movss  xmm0,DWORD PTR [rsp+0x18]
  8dffc0:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8dffc5:	48 89 44 24 70       	mov    QWORD PTR [rsp+0x70],rax
  8dffca:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8dffce:	89 44 24 78          	mov    DWORD PTR [rsp+0x78],eax
  8dffd2:	e8 69 6f f4 ff       	call   826f40 <CCharacter::turnTowardPosition(Ogre::Vector3 const&, float)>
  8dffd7:	48 89 df             	mov    rdi,rbx
  8dffda:	e8 11 77 f4 ff       	call   8276f0 <CCharacter::facingTarget()>
  8dffdf:	84 c0                	test   al,al
  8dffe1:	74 3c                	je     8e001f <CMonster::attackAI(float, CLevel&)+0x29f>
  8dffe3:	31 d2                	xor    edx,edx
  8dffe5:	31 f6                	xor    esi,esi
  8dffe7:	48 89 df             	mov    rdi,rbx
  8dffea:	e8 21 f4 f2 ff       	call   80f410 <CCharacter::setActiveSkill(CSkill*, bool)>
  8dffef:	be 01 00 00 00       	mov    esi,0x1
  8dfff4:	48 89 df             	mov    rdi,rbx
  8dfff7:	e8 64 4f ff ff       	call   8d4f60 <CMonster::selectOffensiveSkill(bool)>
  8dfffc:	48 83 bb 98 03 00 00 00 	cmp    QWORD PTR [rbx+0x398],0x0
  8e0004:	74 19                	je     8e001f <CMonster::attackAI(float, CLevel&)+0x29f>
  8e0006:	31 d2                	xor    edx,edx
  8e0008:	48 c7 c6 ff ff ff ff 	mov    rsi,0xffffffffffffffff
  8e000f:	48 89 df             	mov    rdi,rbx
  8e0012:	e8 59 64 f4 ff       	call   826470 <CCharacter::inSkillRange(long long, bool)>
  8e0017:	85 c0                	test   eax,eax
  8e0019:	0f 84 a1 fe ff ff    	je     8dfec0 <CMonster::attackAI(float, CLevel&)+0x140>
  8e001f:	31 f6                	xor    esi,esi
  8e0021:	48 89 df             	mov    rdi,rbx
  8e0024:	e8 17 61 f4 ff       	call   826140 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)>
  8e0029:	84 c0                	test   al,al
  8e002b:	75 43                	jne    8e0070 <CMonster::attackAI(float, CLevel&)+0x2f0>
  8e002d:	48 89 df             	mov    rdi,rbx
  8e0030:	e8 bb e8 f2 ff       	call   80e8f0 <CCharacter::performingAttack()>
  8e0035:	84 c0                	test   al,al
  8e0037:	0f 85 ab fd ff ff    	jne    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8e003d:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e0040:	be 04 00 00 00       	mov    esi,0x4
  8e0045:	48 89 df             	mov    rdi,rbx
  8e0048:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8e004e:	e9 95 fd ff ff       	jmp    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8e0053:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8e0058:	48 89 df             	mov    rdi,rbx
  8e005b:	e8 50 e8 f2 ff       	call   80e8b0 <CCharacter::stopPathing()>
  8e0060:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e0063:	be 02 00 00 00       	mov    esi,0x2
  8e0068:	e9 68 fd ff ff       	jmp    8dfdd5 <CMonster::attackAI(float, CLevel&)+0x55>
  8e006d:	0f 1f 00             	nop    DWORD PTR [rax]
  8e0070:	31 d2                	xor    edx,edx
  8e0072:	48 89 ee             	mov    rsi,rbp
  8e0075:	48 89 df             	mov    rdi,rbx
  8e0078:	e8 e3 4d f4 ff       	call   824e60 <CCharacter::validLineOfSight(CLevel&, bool)>
  8e007d:	84 c0                	test   al,al
  8e007f:	74 ac                	je     8e002d <CMonster::attackAI(float, CLevel&)+0x2ad>
  8e0081:	48 89 df             	mov    rdi,rbx
  8e0084:	e8 67 e8 f2 ff       	call   80e8f0 <CCharacter::performingAttack()>
  8e0089:	84 c0                	test   al,al
  8e008b:	75 19                	jne    8e00a6 <CMonster::attackAI(float, CLevel&)+0x326>
  8e008d:	83 bb 34 03 00 00 04 	cmp    DWORD PTR [rbx+0x334],0x4
  8e0094:	0f 84 a8 00 00 00    	je     8e0142 <CMonster::attackAI(float, CLevel&)+0x3c2>
  8e009a:	48 89 df             	mov    rdi,rbx
  8e009d:	e8 4e 76 f4 ff       	call   8276f0 <CCharacter::facingTarget()>
  8e00a2:	84 c0                	test   al,al
  8e00a4:	75 2a                	jne    8e00d0 <CMonster::attackAI(float, CLevel&)+0x350>
  8e00a6:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e00a9:	48 89 df             	mov    rdi,rbx
  8e00ac:	ff 90 f8 03 00 00    	call   QWORD PTR [rax+0x3f8]
  8e00b2:	84 c0                	test   al,al
  8e00b4:	0f 85 2e fd ff ff    	jne    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8e00ba:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e00bd:	be 0a 00 00 00       	mov    esi,0xa
  8e00c2:	48 89 df             	mov    rdi,rbx
  8e00c5:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8e00cb:	e9 18 fd ff ff       	jmp    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
  8e00d0:	31 f6                	xor    esi,esi
  8e00d2:	48 89 df             	mov    rdi,rbx
  8e00d5:	e8 e6 1a f3 ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  8e00da:	48 89 df             	mov    rdi,rbx
  8e00dd:	e8 6e b4 f4 ff       	call   82b550 <CCharacter::attack()>
  8e00e2:	84 c0                	test   al,al
  8e00e4:	74 c0                	je     8e00a6 <CMonster::attackAI(float, CLevel&)+0x326>
  8e00e6:	48 8b 83 98 04 00 00 	mov    rax,QWORD PTR [rbx+0x498]
  8e00ed:	48 85 c0             	test   rax,rax
  8e00f0:	74 2c                	je     8e011e <CMonster::attackAI(float, CLevel&)+0x39e>
  8e00f2:	0f 57 c0             	xorps  xmm0,xmm0
  8e00f5:	f3 0f 10 8b e8 07 00 00 	movss  xmm1,DWORD PTR [rbx+0x7e8]
  8e00fd:	0f 57 d2             	xorps  xmm2,xmm2
  8e0100:	f3 0f c2 c1 01       	cmpltss xmm0,xmm1
  8e0105:	0f 54 c8             	andps  xmm1,xmm0
  8e0108:	0f 55 c2             	andnps xmm0,xmm2
  8e010b:	0f 56 c1             	orps   xmm0,xmm1
  8e010e:	f3 0f 58 80 08 04 00 00 	addss  xmm0,DWORD PTR [rax+0x408]
  8e0116:	f3 0f 11 83 e8 07 00 00 	movss  DWORD PTR [rbx+0x7e8],xmm0
  8e011e:	0f 57 c9             	xorps  xmm1,xmm1
  8e0121:	f3 0f 10 83 e8 07 00 00 	movss  xmm0,DWORD PTR [rbx+0x7e8]
  8e0129:	f3 0f 5f c1          	maxss  xmm0,xmm1
  8e012d:	f3 0f 58 83 ec 07 00 00 	addss  xmm0,DWORD PTR [rbx+0x7ec]
  8e0135:	f3 0f 11 83 e8 07 00 00 	movss  DWORD PTR [rbx+0x7e8],xmm0
  8e013d:	e9 64 ff ff ff       	jmp    8e00a6 <CMonster::attackAI(float, CLevel&)+0x326>
  8e0142:	31 ff                	xor    edi,edi
  8e0144:	be 64 00 00 00       	mov    esi,0x64
  8e0149:	e8 a2 2a 3b 00       	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8e014e:	83 f8 18             	cmp    eax,0x18
  8e0151:	0f 8f 43 ff ff ff    	jg     8e009a <CMonster::attackAI(float, CLevel&)+0x31a>
  8e0157:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e015a:	48 89 df             	mov    rdi,rbx
  8e015d:	be 0b 00 00 00       	mov    esi,0xb
  8e0162:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8e0168:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8e016f:	31 f6                	xor    esi,esi
  8e0171:	e8 0a 6f 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8e0176:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8e017c:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8e0181:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8e0188:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8e018e:	be 01 00 00 00       	mov    esi,0x1
  8e0193:	f3 0f 10 05 39 85 6c 00 	movss  xmm0,DWORD PTR [rip+0x6c8539]        # fa86d4 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x34>
  8e019b:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8e01a0:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  8e01a5:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8e01a9:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  8e01ad:	f3 0f 58 44 24 38    	addss  xmm0,DWORD PTR [rsp+0x38]
  8e01b3:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8e01b9:	e8 c2 6e 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8e01be:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8e01c4:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8e01c9:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8e01cf:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8e01d5:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8e01da:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  8e01df:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8e01e3:	89 44 24 48          	mov    DWORD PTR [rsp+0x48],eax
  8e01e7:	f3 0f 10 44 24 48    	movss  xmm0,DWORD PTR [rsp+0x48]
  8e01ed:	f3 0f 5c 05 df 84 6c 00 	subss  xmm0,DWORD PTR [rip+0x6c84df]        # fa86d4 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x34>
  8e01f5:	e8 56 29 3b 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8e01fa:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8e0201:	31 f6                	xor    esi,esi
  8e0203:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  8e0209:	e8 72 6e 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8e020e:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8e0214:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8e0219:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8e0220:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8e0226:	be 01 00 00 00       	mov    esi,0x1
  8e022b:	f3 0f 10 0d a1 84 6c 00 	movss  xmm1,DWORD PTR [rip+0x6c84a1]        # fa86d4 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x34>
  8e0233:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  8e0238:	f3 0f 58 4c 24 50    	addss  xmm1,DWORD PTR [rsp+0x50]
  8e023e:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8e0243:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8e0247:	89 44 24 58          	mov    DWORD PTR [rsp+0x58],eax
  8e024b:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  8e0251:	e8 2a 6e 10 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8e0256:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  8e025c:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8e0261:	f3 0f 11 4c 24 28    	movss  DWORD PTR [rsp+0x28],xmm1
  8e0267:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8e026d:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  8e0272:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  8e0278:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  8e027d:	f3 0f 5c 05 4f 84 6c 00 	subss  xmm0,DWORD PTR [rip+0x6c844f]        # fa86d4 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x34>
  8e0285:	8b 44 24 28          	mov    eax,DWORD PTR [rsp+0x28]
  8e0289:	89 44 24 68          	mov    DWORD PTR [rsp+0x68],eax
  8e028d:	e8 be 28 3b 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8e0292:	f3 0f 10 4c 24 1c    	movss  xmm1,DWORD PTR [rsp+0x1c]
  8e0298:	48 89 ee             	mov    rsi,rbp
  8e029b:	48 89 df             	mov    rdi,rbx
  8e029e:	e8 8d a9 f4 ff       	call   82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  8e02a3:	e9 40 fb ff ff       	jmp    8dfde8 <CMonster::attackAI(float, CLevel&)+0x68>
