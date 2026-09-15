# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
000000000082b550 <CCharacter::attack()>:
  82b550:	48 89 5c 24 e8       	mov    QWORD PTR [rsp-0x18],rbx
  82b555:	48 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],rbp
  82b55a:	48 89 fb             	mov    rbx,rdi
  82b55d:	4c 89 64 24 f8       	mov    QWORD PTR [rsp-0x8],r12
  82b562:	48 81 ec f8 00 00 00 	sub    rsp,0xf8
  82b569:	48 8b bf 40 03 00 00 	mov    rdi,QWORD PTR [rdi+0x340]
  82b570:	48 85 ff             	test   rdi,rdi
  82b573:	0f 84 9f 05 00 00    	je     82bb18 <CCharacter::attack()+0x5c8>
  82b579:	48 83 bb 90 04 00 00 00 	cmp    QWORD PTR [rbx+0x490],0x0
  82b581:	74 16                	je     82b599 <CCharacter::attack()+0x49>
  82b583:	48 8b 83 00 04 00 00 	mov    rax,QWORD PTR [rbx+0x400]
  82b58a:	48 2b 83 f8 03 00 00 	sub    rax,QWORD PTR [rbx+0x3f8]
  82b591:	48 c1 e8 03          	shr    rax,0x3
  82b595:	85 c0                	test   eax,eax
  82b597:	75 27                	jne    82b5c0 <CCharacter::attack()+0x70>
  82b599:	31 c0                	xor    eax,eax
  82b59b:	48 8b 9c 24 e0 00 00 00 	mov    rbx,QWORD PTR [rsp+0xe0]
  82b5a3:	48 8b ac 24 e8 00 00 00 	mov    rbp,QWORD PTR [rsp+0xe8]
  82b5ab:	4c 8b a4 24 f0 00 00 00 	mov    r12,QWORD PTR [rsp+0xf0]
  82b5b3:	48 81 c4 f8 00 00 00 	add    rsp,0xf8
  82b5ba:	c3                   	ret
  82b5bb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  82b5c0:	80 bb f5 01 00 00 00 	cmp    BYTE PTR [rbx+0x1f5],0x0
  82b5c7:	75 d0                	jne    82b599 <CCharacter::attack()+0x49>
  82b5c9:	48 83 bb 98 03 00 00 00 	cmp    QWORD PTR [rbx+0x398],0x0
  82b5d1:	74 23                	je     82b5f6 <CCharacter::attack()+0xa6>
  82b5d3:	80 bb 67 02 00 00 00 	cmp    BYTE PTR [rbx+0x267],0x0
  82b5da:	75 bd                	jne    82b599 <CCharacter::attack()+0x49>
  82b5dc:	f3 0f 10 83 80 03 00 00 	movss  xmm0,DWORD PTR [rbx+0x380]
  82b5e4:	0f 2e 05 0d 92 77 00 	ucomiss xmm0,DWORD PTR [rip+0x77920d]        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  82b5eb:	76 09                	jbe    82b5f6 <CCharacter::attack()+0xa6>
  82b5ed:	80 bb 7d 03 00 00 00 	cmp    BYTE PTR [rbx+0x37d],0x0
  82b5f4:	74 a3                	je     82b599 <CCharacter::attack()+0x49>
  82b5f6:	45 31 e4             	xor    r12d,r12d
  82b5f9:	48 85 ff             	test   rdi,rdi
  82b5fc:	74 12                	je     82b610 <CCharacter::attack()+0xc0>
  82b5fe:	be a7 00 00 00       	mov    esi,0xa7
  82b603:	e8 98 ac fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b608:	84 c0                	test   al,al
  82b60a:	0f 85 30 05 00 00    	jne    82bb40 <CCharacter::attack()+0x5f0>
  82b610:	48 89 df             	mov    rdi,rbx
  82b613:	e8 68 6f fe ff       	call   812580 <CCharacter::attackRange()>
  82b618:	f3 0f 11 44 24 3c    	movss  DWORD PTR [rsp+0x3c],xmm0
  82b61e:	be 01 00 00 00       	mov    esi,0x1
  82b623:	f3 0f 10 9b dc 04 00 00 	movss  xmm3,DWORD PTR [rbx+0x4dc]
  82b62b:	f3 0f 11 5c 24 38    	movss  DWORD PTR [rsp+0x38],xmm3
  82b631:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  82b638:	e8 23 fe 0e 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  82b63d:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  82b644:	31 f6                	xor    esi,esi
  82b646:	48 89 c5             	mov    rbp,rax
  82b649:	e8 12 fe 0e 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  82b64e:	48 85 c0             	test   rax,rax
  82b651:	49 89 c4             	mov    r12,rax
  82b654:	0f 84 96 02 00 00    	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b65a:	48 85 ed             	test   rbp,rbp
  82b65d:	0f 84 8d 02 00 00    	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b663:	be 08 00 00 00       	mov    esi,0x8
  82b668:	48 89 ef             	mov    rdi,rbp
  82b66b:	e8 30 ac fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b670:	84 c0                	test   al,al
  82b672:	0f 84 78 02 00 00    	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b678:	be 23 00 00 00       	mov    esi,0x23
  82b67d:	48 89 ef             	mov    rdi,rbp
  82b680:	e8 1b ac fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b685:	84 c0                	test   al,al
  82b687:	0f 85 53 01 00 00    	jne    82b7e0 <CCharacter::attack()+0x290>
  82b68d:	be 23 00 00 00       	mov    esi,0x23
  82b692:	4c 89 e7             	mov    rdi,r12
  82b695:	e8 06 ac fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b69a:	84 c0                	test   al,al
  82b69c:	0f 85 16 06 00 00    	jne    82bcb8 <CCharacter::attack()+0x768>
  82b6a2:	f3 0f 10 54 24 3c    	movss  xmm2,DWORD PTR [rsp+0x3c]
  82b6a8:	f3 0f 59 54 24 38    	mulss  xmm2,DWORD PTR [rsp+0x38]
  82b6ae:	0f 28 ca             	movaps xmm1,xmm2
  82b6b1:	0f 2e d1             	ucomiss xmm2,xmm1
  82b6b4:	7a 06                	jp     82b6bc <CCharacter::attack()+0x16c>
  82b6b6:	0f 84 64 01 00 00    	je     82b820 <CCharacter::attack()+0x2d0>
  82b6bc:	48 83 bb 40 03 00 00 00 	cmp    QWORD PTR [rbx+0x340],0x0
  82b6c4:	0f 84 56 01 00 00    	je     82b820 <CCharacter::attack()+0x2d0>
  82b6ca:	be 01 00 00 00       	mov    esi,0x1
  82b6cf:	48 89 df             	mov    rdi,rbx
  82b6d2:	f3 0f 11 54 24 10    	movss  DWORD PTR [rsp+0x10],xmm2
  82b6d8:	e8 a3 b9 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b6dd:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82b6e3:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82b6e8:	be 01 00 00 00       	mov    esi,0x1
  82b6ed:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82b6f3:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82b6f8:	48 89 84 24 80 00 00 00 	mov    QWORD PTR [rsp+0x80],rax
  82b700:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82b704:	89 84 24 88 00 00 00 	mov    DWORD PTR [rsp+0x88],eax
  82b70b:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  82b712:	e8 69 b9 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b717:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82b71d:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82b722:	48 8d 7c 24 70       	lea    rdi,[rsp+0x70]
  82b727:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82b72d:	0f 57 db             	xorps  xmm3,xmm3
  82b730:	48 89 84 24 90 00 00 00 	mov    QWORD PTR [rsp+0x90],rax
  82b738:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82b73d:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82b741:	f3 0f 11 5c 24 74    	movss  DWORD PTR [rsp+0x74],xmm3
  82b747:	f3 0f 10 84 24 90 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x90]
  82b750:	f3 0f 5c 84 24 80 00 00 00 	subss  xmm0,DWORD PTR [rsp+0x80]
  82b759:	f3 0f 11 5c 24 20    	movss  DWORD PTR [rsp+0x20],xmm3
  82b75f:	89 84 24 98 00 00 00 	mov    DWORD PTR [rsp+0x98],eax
  82b766:	f3 0f 10 8c 24 98 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x98]
  82b76f:	f3 0f 5c 8c 24 88 00 00 00 	subss  xmm1,DWORD PTR [rsp+0x88]
  82b778:	f3 0f 11 44 24 70    	movss  DWORD PTR [rsp+0x70],xmm0
  82b77e:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  82b784:	e8 c7 ea d7 ff       	call   5aa250 <Ogre::Vector3::length() const>
  82b789:	48 8b 83 40 03 00 00 	mov    rax,QWORD PTR [rbx+0x340]
  82b790:	f3 0f 10 88 94 01 00 00 	movss  xmm1,DWORD PTR [rax+0x194]
  82b798:	0f 28 e1             	movaps xmm4,xmm1
  82b79b:	f3 0f 10 5c 24 20    	movss  xmm3,DWORD PTR [rsp+0x20]
  82b7a1:	f3 0f 10 54 24 10    	movss  xmm2,DWORD PTR [rsp+0x10]
  82b7a7:	f3 0f c2 e3 05       	cmpnltss xmm4,xmm3
  82b7ac:	0f 54 cc             	andps  xmm1,xmm4
  82b7af:	0f 28 e3             	movaps xmm4,xmm3
  82b7b2:	f3 0f 5f 9b 94 01 00 00 	maxss  xmm3,DWORD PTR [rbx+0x194]
  82b7ba:	0f 56 e1             	orps   xmm4,xmm1
  82b7bd:	f3 0f 5c c4          	subss  xmm0,xmm4
  82b7c1:	f3 0f 5c c3          	subss  xmm0,xmm3
  82b7c5:	0f 2e d0             	ucomiss xmm2,xmm0
  82b7c8:	0f 82 d2 04 00 00    	jb     82bca0 <CCharacter::attack()+0x750>
  82b7ce:	be 01 00 00 00       	mov    esi,0x1
  82b7d3:	48 89 df             	mov    rdi,rbx
  82b7d6:	e8 e5 63 fe ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82b7db:	e9 1a 01 00 00       	jmp    82b8fa <CCharacter::attack()+0x3aa>
  82b7e0:	be 23 00 00 00       	mov    esi,0x23
  82b7e5:	4c 89 e7             	mov    rdi,r12
  82b7e8:	e8 b3 aa fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b7ed:	84 c0                	test   al,al
  82b7ef:	0f 85 98 fe ff ff    	jne    82b68d <CCharacter::attack()+0x13d>
  82b7f5:	48 89 df             	mov    rdi,rbx
  82b7f8:	e8 63 6b fe ff       	call   812360 <CCharacter::rangedRange()>
  82b7fd:	48 89 df             	mov    rdi,rbx
  82b800:	f3 0f 11 44 24 10    	movss  DWORD PTR [rsp+0x10],xmm0
  82b806:	e8 65 6c fe ff       	call   812470 <CCharacter::meleeRange()>
  82b80b:	f3 0f 10 4c 24 10    	movss  xmm1,DWORD PTR [rsp+0x10]
  82b811:	0f 28 d0             	movaps xmm2,xmm0
  82b814:	e9 98 fe ff ff       	jmp    82b6b1 <CCharacter::attack()+0x161>
  82b819:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  82b820:	48 83 bb 50 03 00 00 00 	cmp    QWORD PTR [rbx+0x350],0x0
  82b828:	0f 84 61 04 00 00    	je     82bc8f <CCharacter::attack()+0x73f>
  82b82e:	48 83 bb 40 03 00 00 00 	cmp    QWORD PTR [rbx+0x340],0x0
  82b836:	0f 85 8e fe ff ff    	jne    82b6ca <CCharacter::attack()+0x17a>
  82b83c:	be 01 00 00 00       	mov    esi,0x1
  82b841:	48 89 df             	mov    rdi,rbx
  82b844:	f3 0f 11 54 24 10    	movss  DWORD PTR [rsp+0x10],xmm2
  82b84a:	e8 31 b8 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b84f:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82b855:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82b85a:	be 01 00 00 00       	mov    esi,0x1
  82b85f:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82b865:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82b86a:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
  82b86f:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82b873:	89 44 24 58          	mov    DWORD PTR [rsp+0x58],eax
  82b877:	48 8b bb 50 03 00 00 	mov    rdi,QWORD PTR [rbx+0x350]
  82b87e:	e8 fd b7 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b883:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82b889:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82b88e:	48 8d 7c 24 70       	lea    rdi,[rsp+0x70]
  82b893:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82b899:	0f 57 db             	xorps  xmm3,xmm3
  82b89c:	48 89 44 24 60       	mov    QWORD PTR [rsp+0x60],rax
  82b8a1:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82b8a6:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82b8aa:	f3 0f 11 5c 24 74    	movss  DWORD PTR [rsp+0x74],xmm3
  82b8b0:	f3 0f 10 44 24 60    	movss  xmm0,DWORD PTR [rsp+0x60]
  82b8b6:	f3 0f 5c 44 24 50    	subss  xmm0,DWORD PTR [rsp+0x50]
  82b8bc:	f3 0f 11 5c 24 20    	movss  DWORD PTR [rsp+0x20],xmm3
  82b8c2:	89 44 24 68          	mov    DWORD PTR [rsp+0x68],eax
  82b8c6:	f3 0f 10 4c 24 68    	movss  xmm1,DWORD PTR [rsp+0x68]
  82b8cc:	f3 0f 5c 4c 24 58    	subss  xmm1,DWORD PTR [rsp+0x58]
  82b8d2:	f3 0f 11 44 24 70    	movss  DWORD PTR [rsp+0x70],xmm0
  82b8d8:	f3 0f 11 4c 24 78    	movss  DWORD PTR [rsp+0x78],xmm1
  82b8de:	e8 6d e9 d7 ff       	call   5aa250 <Ogre::Vector3::length() const>
  82b8e3:	48 8b 83 50 03 00 00 	mov    rax,QWORD PTR [rbx+0x350]
  82b8ea:	e9 a1 fe ff ff       	jmp    82b790 <CCharacter::attack()+0x240>
  82b8ef:	90                   	nop
  82b8f0:	31 f6                	xor    esi,esi
  82b8f2:	48 89 df             	mov    rdi,rbx
  82b8f5:	e8 c6 62 fe ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82b8fa:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  82b901:	48 85 c0             	test   rax,rax
  82b904:	0f 84 8f fc ff ff    	je     82b599 <CCharacter::attack()+0x49>
  82b90a:	83 78 64 ff          	cmp    DWORD PTR [rax+0x64],0xffffffff
  82b90e:	0f 84 85 fc ff ff    	je     82b599 <CCharacter::attack()+0x49>
  82b914:	0f 57 db             	xorps  xmm3,xmm3
  82b917:	f3 0f 10 83 78 03 00 00 	movss  xmm0,DWORD PTR [rbx+0x378]
  82b91f:	0f 2e c3             	ucomiss xmm0,xmm3
  82b922:	0f 87 b0 01 00 00    	ja     82bad8 <CCharacter::attack()+0x588>
  82b928:	48 83 bb 98 03 00 00 00 	cmp    QWORD PTR [rbx+0x398],0x0
  82b930:	74 1e                	je     82b950 <CCharacter::attack()+0x400>
  82b932:	80 bb 67 02 00 00 00 	cmp    BYTE PTR [rbx+0x267],0x0
  82b939:	0f 85 99 01 00 00    	jne    82bad8 <CCharacter::attack()+0x588>
  82b93f:	f3 0f 10 83 80 03 00 00 	movss  xmm0,DWORD PTR [rbx+0x380]
  82b947:	0f 2e c3             	ucomiss xmm0,xmm3
  82b94a:	0f 87 88 03 00 00    	ja     82bcd8 <CCharacter::attack()+0x788>
  82b950:	c6 83 d0 04 00 00 01 	mov    BYTE PTR [rbx+0x4d0],0x1
  82b957:	c6 83 7c 03 00 00 00 	mov    BYTE PTR [rbx+0x37c],0x0
  82b95e:	ba 07 00 00 00       	mov    edx,0x7
  82b963:	be 16 00 00 00       	mov    esi,0x16
  82b968:	48 89 df             	mov    rdi,rbx
  82b96b:	f3 0f 11 5c 24 20    	movss  DWORD PTR [rsp+0x20],xmm3
  82b971:	e8 6a 7e fe ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  82b976:	f3 0f 10 5c 24 20    	movss  xmm3,DWORD PTR [rsp+0x20]
  82b97c:	0f 28 c8             	movaps xmm1,xmm0
  82b97f:	0f 2e d8             	ucomiss xmm3,xmm0
  82b982:	0f 87 62 03 00 00    	ja     82bcea <CCharacter::attack()+0x79a>
  82b988:	f3 0f 10 25 ac 8e 77 00 	movss  xmm4,DWORD PTR [rip+0x778eac]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  82b990:	f3 0f 10 15 64 8e 77 00 	movss  xmm2,DWORD PTR [rip+0x778e64]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82b998:	f3 0f 5e cc          	divss  xmm1,xmm4
  82b99c:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  82b9a3:	48 8b bb 18 07 00 00 	mov    rdi,QWORD PTR [rbx+0x718]
  82b9aa:	f3 0f 10 05 36 cd 77 00 	movss  xmm0,DWORD PTR [rip+0x77cd36]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82b9b2:	48 85 ff             	test   rdi,rdi
  82b9b5:	f3 0f 58 ca          	addss  xmm1,xmm2
  82b9b9:	f3 0f 5e 48 70       	divss  xmm1,DWORD PTR [rax+0x70]
  82b9be:	f3 0f 5f c1          	maxss  xmm0,xmm1
  82b9c2:	0f 28 c8             	movaps xmm1,xmm0
  82b9c5:	74 29                	je     82b9f0 <CCharacter::attack()+0x4a0>
  82b9c7:	be 01 00 00 00       	mov    esi,0x1
  82b9cc:	f3 0f 11 44 24 10    	movss  DWORD PTR [rsp+0x10],xmm0
  82b9d2:	e8 69 52 52 00       	call   d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>
  82b9d7:	84 c0                	test   al,al
  82b9d9:	f3 0f 10 4c 24 10    	movss  xmm1,DWORD PTR [rsp+0x10]
  82b9df:	74 08                	je     82b9e9 <CCharacter::attack()+0x499>
  82b9e1:	f3 0f 59 0d af 2a 7a 00 	mulss  xmm1,DWORD PTR [rip+0x7a2aaf]        # fce498 <vtable for iInventoryListener+0x58>
  82b9e9:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  82b9f0:	8b 70 64             	mov    esi,DWORD PTR [rax+0x64]
  82b9f3:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  82b9fa:	f3 0f 11 4c 24 10    	movss  DWORD PTR [rsp+0x10],xmm1
  82ba00:	48 8d ac 24 c0 00 00 00 	lea    rbp,[rsp+0xc0]
  82ba08:	e8 53 f1 06 00       	call   89ab60 <CGenericModel::getAnimationLengthSeconds(int) const>
  82ba0d:	f3 0f 10 4c 24 10    	movss  xmm1,DWORD PTR [rsp+0x10]
  82ba13:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  82ba1a:	f3 0f 5e c1          	divss  xmm0,xmm1
  82ba1e:	f3 0f 11 83 78 03 00 00 	movss  DWORD PTR [rbx+0x378],xmm0
  82ba26:	f3 0f 11 4c 24 10    	movss  DWORD PTR [rsp+0x10],xmm1
  82ba2c:	e8 af ae 07 00       	call   8a68e0 <CGenericModel::clearQueuedAnimations()>
  82ba31:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  82ba38:	31 d2                	xor    edx,edx
  82ba3a:	48 89 df             	mov    rdi,rbx
  82ba3d:	f3 0f 10 15 1b cd 77 00 	movss  xmm2,DWORD PTR [rip+0x77cd1b]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  82ba45:	f3 0f 10 4c 24 10    	movss  xmm1,DWORD PTR [rsp+0x10]
  82ba4b:	8b 70 64             	mov    esi,DWORD PTR [rax+0x64]
  82ba4e:	f3 0f 10 05 92 cc 77 00 	movss  xmm0,DWORD PTR [rip+0x77cc92]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82ba56:	e8 d5 56 fe ff       	call   811130 <CCharacter::blendAnimation(int, bool, float, float, float)>
  82ba5b:	48 8d 94 24 de 00 00 00 	lea    rdx,[rsp+0xde]
  82ba63:	be 3a 99 fc 00       	mov    esi,0xfc993a
  82ba68:	48 89 ef             	mov    rdi,rbp
  82ba6b:	e8 88 a8 d2 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  82ba70:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  82ba77:	f3 0f 10 0d 7d 8d 77 00 	movss  xmm1,DWORD PTR [rip+0x778d7d]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82ba7f:	f3 0f 10 05 61 cc 77 00 	movss  xmm0,DWORD PTR [rip+0x77cc61]        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82ba87:	ba 01 00 00 00       	mov    edx,0x1
  82ba8c:	48 89 ee             	mov    rsi,rbp
  82ba8f:	e8 2c 88 07 00       	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  82ba94:	48 89 ef             	mov    rdi,rbp
  82ba97:	e8 ec a7 d2 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  82ba9c:	48 8b 83 90 03 00 00 	mov    rax,QWORD PTR [rbx+0x390]
  82baa3:	80 78 18 00          	cmp    BYTE PTR [rax+0x18],0x0
  82baa7:	74 2f                	je     82bad8 <CCharacter::attack()+0x588>
  82baa9:	48 83 bb 98 04 00 00 00 	cmp    QWORD PTR [rbx+0x498],0x0
  82bab1:	74 25                	je     82bad8 <CCharacter::attack()+0x588>
  82bab3:	48 8b bb 98 02 00 00 	mov    rdi,QWORD PTR [rbx+0x298]
  82baba:	48 85 ff             	test   rdi,rdi
  82babd:	74 19                	je     82bad8 <CCharacter::attack()+0x588>
  82babf:	0f 57 c9             	xorps  xmm1,xmm1
  82bac2:	48 8b 53 58          	mov    rdx,QWORD PTR [rbx+0x58]
  82bac6:	31 c9                	xor    ecx,ecx
  82bac8:	be 1a 00 00 00       	mov    esi,0x1a
  82bacd:	0f 28 c1             	movaps xmm0,xmm1
  82bad0:	e8 cb dd 23 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  82bad5:	0f 1f 00             	nop    DWORD PTR [rax]
  82bad8:	f3 0f 10 0d f0 cb 77 00 	movss  xmm1,DWORD PTR [rip+0x77cbf0]        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  82bae0:	b8 01 00 00 00       	mov    eax,0x1
  82bae5:	0f 28 d1             	movaps xmm2,xmm1
  82bae8:	f3 0f 10 83 84 02 00 00 	movss  xmm0,DWORD PTR [rbx+0x284]
  82baf0:	f3 0f c2 d0 05       	cmpnltss xmm2,xmm0
  82baf5:	0f 28 d8             	movaps xmm3,xmm0
  82baf8:	0f 28 c2             	movaps xmm0,xmm2
  82bafb:	0f 54 da             	andps  xmm3,xmm2
  82bafe:	0f 55 c1             	andnps xmm0,xmm1
  82bb01:	0f 56 c3             	orps   xmm0,xmm3
  82bb04:	f3 0f 11 83 84 02 00 00 	movss  DWORD PTR [rbx+0x284],xmm0
  82bb0c:	e9 8a fa ff ff       	jmp    82b59b <CCharacter::attack()+0x4b>
  82bb11:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  82bb18:	48 83 bb 50 03 00 00 00 	cmp    QWORD PTR [rbx+0x350],0x0
  82bb20:	0f 85 53 fa ff ff    	jne    82b579 <CCharacter::attack()+0x29>
  82bb26:	80 bb 66 02 00 00 00 	cmp    BYTE PTR [rbx+0x266],0x0
  82bb2d:	0f 84 66 fa ff ff    	je     82b599 <CCharacter::attack()+0x49>
  82bb33:	e9 41 fa ff ff       	jmp    82b579 <CCharacter::attack()+0x29>
  82bb38:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  82bb40:	48 8d ac 24 d0 00 00 00 	lea    rbp,[rsp+0xd0]
  82bb48:	48 8d 94 24 df 00 00 00 	lea    rdx,[rsp+0xdf]
  82bb50:	be c8 7d fa 00       	mov    esi,0xfa7dc8
  82bb55:	48 89 ef             	mov    rdi,rbp
  82bb58:	e8 fb a2 d2 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  82bb5d:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  82bb64:	48 89 ee             	mov    rsi,rbp
  82bb67:	41 bc 01 00 00 00    	mov    r12d,0x1
  82bb6d:	e8 1e 38 fd ff       	call   7ff390 <CBaseUnit::hasUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  82bb72:	84 c0                	test   al,al
  82bb74:	48 89 ef             	mov    rdi,rbp
  82bb77:	41 0f 95 c4          	setne  r12b
  82bb7b:	e8 58 8d d2 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  82bb80:	45 84 e4             	test   r12b,r12b
  82bb83:	0f 84 87 fa ff ff    	je     82b610 <CCharacter::attack()+0xc0>
  82bb89:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  82bb90:	48 85 ff             	test   rdi,rdi
  82bb93:	0f 84 d7 00 00 00    	je     82bc70 <CCharacter::attack()+0x720>
  82bb99:	be 23 00 00 00       	mov    esi,0x23
  82bb9e:	e8 fd a6 fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82bba3:	84 c0                	test   al,al
  82bba5:	0f 84 c5 00 00 00    	je     82bc70 <CCharacter::attack()+0x720>
  82bbab:	80 bb 66 02 00 00 00 	cmp    BYTE PTR [rbx+0x266],0x0
  82bbb2:	0f 85 58 fa ff ff    	jne    82b610 <CCharacter::attack()+0xc0>
  82bbb8:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  82bbbf:	be 01 00 00 00       	mov    esi,0x1
  82bbc4:	e8 b7 b4 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82bbc9:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82bbcf:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82bbd4:	be 01 00 00 00       	mov    esi,0x1
  82bbd9:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82bbdf:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82bbe4:	48 89 84 24 a0 00 00 00 	mov    QWORD PTR [rsp+0xa0],rax
  82bbec:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82bbf0:	89 84 24 a8 00 00 00 	mov    DWORD PTR [rsp+0xa8],eax
  82bbf7:	f3 0f 10 84 24 a8 00 00 00 	movss  xmm0,DWORD PTR [rsp+0xa8]
  82bc00:	f3 0f 11 44 24 38    	movss  DWORD PTR [rsp+0x38],xmm0
  82bc06:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  82bc0d:	e8 6e b4 1b 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  82bc12:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  82bc18:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  82bc1d:	31 f6                	xor    esi,esi
  82bc1f:	f3 0f 11 4c 24 48    	movss  DWORD PTR [rsp+0x48],xmm1
  82bc25:	48 89 84 24 b0 00 00 00 	mov    QWORD PTR [rsp+0xb0],rax
  82bc2d:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  82bc32:	8b 44 24 48          	mov    eax,DWORD PTR [rsp+0x48]
  82bc36:	f3 0f 10 84 24 b0 00 00 00 	movss  xmm0,DWORD PTR [rsp+0xb0]
  82bc3f:	89 84 24 b8 00 00 00 	mov    DWORD PTR [rsp+0xb8],eax
  82bc46:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  82bc4a:	48 85 c0             	test   rax,rax
  82bc4d:	74 04                	je     82bc53 <CCharacter::attack()+0x703>
  82bc4f:	48 8b 70 18          	mov    rsi,QWORD PTR [rax+0x18]
  82bc53:	f3 0f 10 4c 24 38    	movss  xmm1,DWORD PTR [rsp+0x38]
  82bc59:	48 89 df             	mov    rdi,rbx
  82bc5c:	e8 cf ef ff ff       	call   82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  82bc61:	31 c0                	xor    eax,eax
  82bc63:	e9 33 f9 ff ff       	jmp    82b59b <CCharacter::attack()+0x4b>
  82bc68:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  82bc70:	48 8b bb 40 03 00 00 	mov    rdi,QWORD PTR [rbx+0x340]
  82bc77:	ba 01 00 00 00       	mov    edx,0x1
  82bc7c:	48 89 de             	mov    rsi,rbx
  82bc7f:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  82bc82:	ff 90 50 03 00 00    	call   QWORD PTR [rax+0x350]
  82bc88:	31 c0                	xor    eax,eax
  82bc8a:	e9 0c f9 ff ff       	jmp    82b59b <CCharacter::attack()+0x4b>
  82bc8f:	0f 2e d1             	ucomiss xmm2,xmm1
  82bc92:	7a 0c                	jp     82bca0 <CCharacter::attack()+0x750>
  82bc94:	0f 84 60 fc ff ff    	je     82b8fa <CCharacter::attack()+0x3aa>
  82bc9a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  82bca0:	be 02 00 00 00       	mov    esi,0x2
  82bca5:	48 89 df             	mov    rdi,rbx
  82bca8:	e8 13 5f fe ff       	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82bcad:	e9 48 fc ff ff       	jmp    82b8fa <CCharacter::attack()+0x3aa>
  82bcb2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  82bcb8:	be 23 00 00 00       	mov    esi,0x23
  82bcbd:	48 89 ef             	mov    rdi,rbp
  82bcc0:	e8 db a5 fc ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82bcc5:	84 c0                	test   al,al
  82bcc7:	0f 85 d5 f9 ff ff    	jne    82b6a2 <CCharacter::attack()+0x152>
  82bccd:	e9 23 fb ff ff       	jmp    82b7f5 <CCharacter::attack()+0x2a5>
  82bcd2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  82bcd8:	80 bb 7d 03 00 00 00 	cmp    BYTE PTR [rbx+0x37d],0x0
  82bcdf:	0f 84 f3 fd ff ff    	je     82bad8 <CCharacter::attack()+0x588>
  82bce5:	e9 66 fc ff ff       	jmp    82b950 <CCharacter::attack()+0x400>
  82bcea:	ba 07 00 00 00       	mov    edx,0x7
  82bcef:	be 8c 00 00 00       	mov    esi,0x8c
  82bcf4:	48 89 df             	mov    rdi,rbx
  82bcf7:	f3 0f 11 5c 24 20    	movss  DWORD PTR [rsp+0x20],xmm3
  82bcfd:	f3 0f 11 44 24 10    	movss  DWORD PTR [rsp+0x10],xmm0
  82bd03:	e8 d8 7a fe ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  82bd08:	f3 0f 10 25 2c 8b 77 00 	movss  xmm4,DWORD PTR [rip+0x778b2c]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  82bd10:	f3 0f 5e c4          	divss  xmm0,xmm4
  82bd14:	f3 0f 10 15 e0 8a 77 00 	movss  xmm2,DWORD PTR [rip+0x778ae0]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82bd1c:	f3 0f 10 4c 24 10    	movss  xmm1,DWORD PTR [rsp+0x10]
  82bd22:	f3 0f 10 5c 24 20    	movss  xmm3,DWORD PTR [rsp+0x20]
  82bd28:	0f 2e d0             	ucomiss xmm2,xmm0
  82bd2b:	77 13                	ja     82bd40 <CCharacter::attack()+0x7f0>
  82bd2d:	0f 28 c2             	movaps xmm0,xmm2
  82bd30:	0f 28 da             	movaps xmm3,xmm2
  82bd33:	f3 0f 5c d8          	subss  xmm3,xmm0
  82bd37:	f3 0f 59 cb          	mulss  xmm1,xmm3
  82bd3b:	e9 58 fc ff ff       	jmp    82b998 <CCharacter::attack()+0x448>
  82bd40:	f3 0f 5f c3          	maxss  xmm0,xmm3
  82bd44:	eb ea                	jmp    82bd30 <CCharacter::attack()+0x7e0>
  82bd46:	48 89 c7             	mov    rdi,rax
  82bd49:	e8 4a 87 d2 ff       	call   554498 <_Unwind_Resume@plt>
  82bd4e:	45 84 e4             	test   r12b,r12b
  82bd51:	48 89 c3             	mov    rbx,rax
  82bd54:	74 0d                	je     82bd63 <CCharacter::attack()+0x813>
  82bd56:	48 8d bc 24 d0 00 00 00 	lea    rdi,[rsp+0xd0]
  82bd5e:	e8 75 8b d2 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  82bd63:	48 89 d8             	mov    rax,rbx
  82bd66:	eb de                	jmp    82bd46 <CCharacter::attack()+0x7f6>
  82bd68:	48 89 ef             	mov    rdi,rbp
  82bd6b:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  82bd70:	e8 13 a5 d2 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  82bd75:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  82bd7a:	eb ca                	jmp    82bd46 <CCharacter::attack()+0x7f6>
  82bd7c:	eb c8                	jmp    82bd46 <CCharacter::attack()+0x7f6>
  82bd7e:	66 90                	xchg   ax,ax

