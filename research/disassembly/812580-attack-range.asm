# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000812580 <CCharacter::attackRange()>:
  812580:	48 89 5c 24 e8       	mov    QWORD PTR [rsp-0x18],rbx
  812585:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
  81258a:	48 89 fb             	mov    rbx,rdi
  81258d:	4c 89 64 24 f8       	mov    QWORD PTR [rsp-0x8],r12
  812592:	48 83 ec 28          	sub    rsp,0x28
  812596:	48 8b 87 90 03 00 00 	mov    rax,QWORD PTR [rdi+0x390]
  81259d:	48 85 c0             	test   rax,rax
  8125a0:	0f 84 2a 01 00 00    	je     8126d0 <CCharacter::attackRange()+0x150>
  8125a6:	f3 0f 10 40 68       	movss  xmm0,DWORD PTR [rax+0x68]
  8125ab:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8125b1:	48 83 bf 98 04 00 00 00 	cmp    QWORD PTR [rdi+0x498],0x0
  8125b9:	0f 84 89 00 00 00    	je     812648 <CCharacter::attackRange()+0xc8>
  8125bf:	48 8b bf 90 04 00 00 	mov    rdi,QWORD PTR [rdi+0x490]
  8125c6:	be 01 00 00 00       	mov    esi,0x1
  8125cb:	e8 90 8e 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  8125d0:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  8125d7:	31 f6                	xor    esi,esi
  8125d9:	48 89 c5             	mov    rbp,rax
  8125dc:	e8 7f 8e 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  8125e1:	48 85 c0             	test   rax,rax
  8125e4:	49 89 c4             	mov    r12,rax
  8125e7:	74 5f                	je     812648 <CCharacter::attackRange()+0xc8>
  8125e9:	48 85 ed             	test   rbp,rbp
  8125ec:	74 5a                	je     812648 <CCharacter::attackRange()+0xc8>
  8125ee:	be 08 00 00 00       	mov    esi,0x8
  8125f3:	48 89 ef             	mov    rdi,rbp
  8125f6:	e8 a5 3c fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8125fb:	84 c0                	test   al,al
  8125fd:	74 49                	je     812648 <CCharacter::attackRange()+0xc8>
  8125ff:	be 23 00 00 00       	mov    esi,0x23
  812604:	48 89 ef             	mov    rdi,rbp
  812607:	e8 94 3c fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  81260c:	84 c0                	test   al,al
  81260e:	74 70                	je     812680 <CCharacter::attackRange()+0x100>
  812610:	48 8b 85 a8 02 00 00 	mov    rax,QWORD PTR [rbp+0x2a8]
  812617:	f3 0f 10 40 68       	movss  xmm0,DWORD PTR [rax+0x68]
  81261c:	f3 0f 5f 44 24 0c    	maxss  xmm0,DWORD PTR [rsp+0xc]
  812622:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  812628:	49 8b 84 24 a0 02 00 00 	mov    rax,QWORD PTR [r12+0x2a0]
  812630:	f3 0f 10 40 68       	movss  xmm0,DWORD PTR [rax+0x68]
  812635:	f3 0f 5f 44 24 0c    	maxss  xmm0,DWORD PTR [rsp+0xc]
  81263b:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  812641:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  812648:	f3 0f 10 83 e0 04 00 00 	movss  xmm0,DWORD PTR [rbx+0x4e0]
  812650:	f3 0f 59 83 98 00 00 00 	mulss  xmm0,DWORD PTR [rbx+0x98]
  812658:	f3 0f 58 05 88 60 79 00 	addss  xmm0,DWORD PTR [rip+0x796088]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  812660:	f3 0f 58 44 24 0c    	addss  xmm0,DWORD PTR [rsp+0xc]
  812666:	48 8b 5c 24 10       	mov    rbx,QWORD PTR [rsp+0x10]
  81266b:	48 8b 6c 24 18       	mov    rbp,QWORD PTR [rsp+0x18]
  812670:	4c 8b 64 24 20       	mov    r12,QWORD PTR [rsp+0x20]
  812675:	48 83 c4 28          	add    rsp,0x28
  812679:	c3                   	ret
  81267a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  812680:	be 23 00 00 00       	mov    esi,0x23
  812685:	4c 89 e7             	mov    rdi,r12
  812688:	e8 13 3c fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  81268d:	84 c0                	test   al,al
  81268f:	0f 85 7b ff ff ff    	jne    812610 <CCharacter::attackRange()+0x90>
  812695:	48 8b 85 a8 02 00 00 	mov    rax,QWORD PTR [rbp+0x2a8]
  81269c:	f3 0f 10 40 68       	movss  xmm0,DWORD PTR [rax+0x68]
  8126a1:	f3 0f 5d 44 24 0c    	minss  xmm0,DWORD PTR [rsp+0xc]
  8126a7:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8126ad:	49 8b 84 24 a0 02 00 00 	mov    rax,QWORD PTR [r12+0x2a0]
  8126b5:	f3 0f 10 40 68       	movss  xmm0,DWORD PTR [rax+0x68]
  8126ba:	f3 0f 5d 44 24 0c    	minss  xmm0,DWORD PTR [rsp+0xc]
  8126c0:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8126c6:	eb 80                	jmp    812648 <CCharacter::attackRange()+0xc8>
  8126c8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  8126d0:	31 f6                	xor    esi,esi
  8126d2:	e8 e9 f4 ff ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  8126d7:	0f 57 c0             	xorps  xmm0,xmm0
  8126da:	eb 8a                	jmp    812666 <CCharacter::attackRange()+0xe6>
  8126dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

