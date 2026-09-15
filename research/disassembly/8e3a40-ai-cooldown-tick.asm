# Source: earlier supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Declared original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Verified source text SHA-256: 59d876125b21e8e1a3e6b0f2f242632966b705218907de1ed5172baebc30d196
# Targeted Intel-syntax excerpt; the ELF is not included. See ../monster-ai-cooldown.md.

# Range: 0x8e3a40 <= instruction address < 0x8e3b68
  8e3a40:	41 54                	push   r12
  8e3a42:	55                   	push   rbp
  8e3a43:	89 f5                	mov    ebp,esi
  8e3a45:	53                   	push   rbx
  8e3a46:	48 89 fb             	mov    rbx,rdi
  8e3a49:	48 83 ec 10          	sub    rsp,0x10
  8e3a4d:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8e3a53:	48 83 bf c8 01 00 00 00 	cmp    QWORD PTR [rdi+0x1c8],0x0
  8e3a5b:	f3 0f 10 8f e8 07 00 00 	movss  xmm1,DWORD PTR [rdi+0x7e8]
  8e3a63:	f3 0f 5c c8          	subss  xmm1,xmm0
  8e3a67:	f3 0f 11 8f e8 07 00 00 	movss  DWORD PTR [rdi+0x7e8],xmm1
  8e3a6f:	74 0d                	je     8e3a7e <CMonster::updateAI(float, bool)+0x3e>
  8e3a71:	e8 ba ae f2 ff       	call   80e930 <CCharacter::performingSkill()>
  8e3a76:	84 c0                	test   al,al
  8e3a78:	0f 85 ea 00 00 00    	jne    8e3b68 <CMonster::updateAI(float, bool)+0x128>
  8e3a7e:	8b 83 30 03 00 00    	mov    eax,DWORD PTR [rbx+0x330]
  8e3a84:	83 f8 2c             	cmp    eax,0x2c
  8e3a87:	74 13                	je     8e3a9c <CMonster::updateAI(float, bool)+0x5c>
  8e3a89:	83 f8 23             	cmp    eax,0x23
  8e3a8c:	74 0e                	je     8e3a9c <CMonster::updateAI(float, bool)+0x5c>
  8e3a8e:	48 83 bb 50 07 00 00 00 	cmp    QWORD PTR [rbx+0x750],0x0
  8e3a96:	0f 84 84 00 00 00    	je     8e3b20 <CMonster::updateAI(float, bool)+0xe0>
  8e3a9c:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  8e3aa2:	bd 01 00 00 00       	mov    ebp,0x1
  8e3aa7:	f3 0f 58 83 24 05 00 00 	addss  xmm0,DWORD PTR [rbx+0x524]
  8e3aaf:	f3 0f 11 83 24 05 00 00 	movss  DWORD PTR [rbx+0x524],xmm0
  8e3ab7:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  8e3abe:	c7 83 24 05 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x524],0x0
  8e3ac8:	48 85 ff             	test   rdi,rdi
  8e3acb:	74 1b                	je     8e3ae8 <CMonster::updateAI(float, bool)+0xa8>
  8e3acd:	e8 7e ad f2 ff       	call   80e850 <CCharacter::alive()>
  8e3ad2:	84 c0                	test   al,al
  8e3ad4:	0f 85 c6 00 00 00    	jne    8e3ba0 <CMonster::updateAI(float, bool)+0x160>
  8e3ada:	31 f6                	xor    esi,esi
  8e3adc:	48 89 df             	mov    rdi,rbx
  8e3adf:	e8 2c 18 f4 ff       	call   825310 <CCharacter::setTarget(CCharacter*)>
  8e3ae4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8e3ae8:	31 ff                	xor    edi,edi
  8e3aea:	48 83 7b 68 00       	cmp    QWORD PTR [rbx+0x68],0x0
  8e3aef:	44 8b 25 f6 79 c2 00 	mov    r12d,DWORD PTR [rip+0xc279f6]        # 150b4ec <KSETTINGS_AI_FREEZE>
  8e3af6:	74 0c                	je     8e3b04 <CMonster::updateAI(float, bool)+0xc4>
  8e3af8:	e8 93 09 17 00       	call   a54490 <CMasterResourceManager::getSingleton()>
  8e3afd:	48 8b b8 90 00 00 00 	mov    rdi,QWORD PTR [rax+0x90]
  8e3b04:	44 89 e6             	mov    esi,r12d
  8e3b07:	e8 34 a9 38 00       	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  8e3b0c:	85 c0                	test   eax,eax
  8e3b0e:	0f 8e b4 00 00 00    	jle    8e3bc8 <CMonster::updateAI(float, bool)+0x188>
  8e3b14:	48 83 c4 10          	add    rsp,0x10
  8e3b18:	5b                   	pop    rbx
  8e3b19:	5d                   	pop    rbp
  8e3b1a:	41 5c                	pop    r12
  8e3b1c:	c3                   	ret
  8e3b1d:	0f 1f 00             	nop    DWORD PTR [rax]
  8e3b20:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  8e3b26:	40 84 ed             	test   bpl,bpl
  8e3b29:	f3 0f 58 83 24 05 00 00 	addss  xmm0,DWORD PTR [rbx+0x524]
  8e3b31:	f3 0f 11 83 24 05 00 00 	movss  DWORD PTR [rbx+0x524],xmm0
  8e3b39:	0f 85 78 ff ff ff    	jne    8e3ab7 <CMonster::updateAI(float, bool)+0x77>
  8e3b3f:	48 63 83 20 05 00 00 	movsxd rax,DWORD PTR [rbx+0x520]
  8e3b46:	0f 2e 04 85 70 26 fd 00 	ucomiss xmm0,DWORD PTR [rax*4+0xfd2670]
  8e3b4e:	0f 83 63 ff ff ff    	jae    8e3ab7 <CMonster::updateAI(float, bool)+0x77>
  8e3b54:	80 bb 80 06 00 00 00 	cmp    BYTE PTR [rbx+0x680],0x0
  8e3b5b:	0f 85 56 ff ff ff    	jne    8e3ab7 <CMonster::updateAI(float, bool)+0x77>
  8e3b61:	eb b1                	jmp    8e3b14 <CMonster::updateAI(float, bool)+0xd4>
  8e3b63:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
