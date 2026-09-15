# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x9256a0, 0x92596b); source instructions unchanged.
  9256a0:	41 55                	push   r13
  9256a2:	31 c9                	xor    ecx,ecx
  9256a4:	41 54                	push   r12
  9256a6:	41 89 d4             	mov    r12d,edx
  9256a9:	55                   	push   rbp
  9256aa:	48 89 f5             	mov    rbp,rsi
  9256ad:	53                   	push   rbx
  9256ae:	48 89 fb             	mov    rbx,rdi
  9256b1:	48 83 ec 48          	sub    rsp,0x48
  9256b5:	e8 56 66 ff ff       	call   91bd10 <CInventory::canEquipIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS, bool)>
  9256ba:	89 c2                	mov    edx,eax
  9256bc:	31 c0                	xor    eax,eax
  9256be:	84 d2                	test   dl,dl
  9256c0:	75 0e                	jne    9256d0 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x30>
  9256c2:	48 83 c4 48          	add    rsp,0x48
  9256c6:	5b                   	pop    rbx
  9256c7:	5d                   	pop    rbp
  9256c8:	41 5c                	pop    r12
  9256ca:	41 5d                	pop    r13
  9256cc:	c3                   	ret
  9256cd:	0f 1f 00             	nop    DWORD PTR [rax]
  9256d0:	be 09 00 00 00       	mov    esi,0x9
  9256d5:	48 89 ef             	mov    rdi,rbp
  9256d8:	e8 c3 0b ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  9256dd:	84 c0                	test   al,al
  9256df:	0f 85 1b 01 00 00    	jne    925800 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x160>
  9256e5:	8b 73 38             	mov    esi,DWORD PTR [rbx+0x38]
  9256e8:	85 f6                	test   esi,esi
  9256ea:	74 44                	je     925730 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x90>
  9256ec:	8b 7b 3c             	mov    edi,DWORD PTR [rbx+0x3c]
  9256ef:	31 c9                	xor    ecx,ecx
  9256f1:	31 c0                	xor    eax,eax
  9256f3:	eb 24                	jmp    925719 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x79>
  9256f5:	0f 1f 00             	nop    DWORD PTR [rax]
  9256f8:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
  9256fc:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  9256ff:	48 85 d2             	test   rdx,rdx
  925702:	74 0a                	je     92570e <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x6e>
  925704:	48 39 6a 10          	cmp    QWORD PTR [rdx+0x10],rbp
  925708:	0f 84 52 01 00 00    	je     925860 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x1c0>
  92570e:	83 c0 01             	add    eax,0x1
  925711:	48 83 c1 08          	add    rcx,0x8
  925715:	39 c6                	cmp    esi,eax
  925717:	76 17                	jbe    925730 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x90>
  925719:	39 c7                	cmp    edi,eax
  92571b:	76 db                	jbe    9256f8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x58>
  92571d:	48 89 ca             	mov    rdx,rcx
  925720:	48 03 53 30          	add    rdx,QWORD PTR [rbx+0x30]
  925724:	eb d6                	jmp    9256fc <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x5c>
  925726:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  925730:	bf 28 00 00 00       	mov    edi,0x28
  925735:	31 c9                	xor    ecx,ecx
  925737:	31 d2                	xor    edx,edx
  925739:	31 f6                	xor    esi,esi
  92573b:	e8 d8 db c2 ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  925740:	48 89 c7             	mov    rdi,rax
  925743:	49 89 c5             	mov    r13,rax
  925746:	e8 75 3f 45 00       	call   d796c0 <CRunicCore::CRunicCore()>
  92574b:	48 8d 7b 30          	lea    rdi,[rbx+0x30]
  92574f:	49 c7 45 00 b0 4a fd 00 	mov    QWORD PTR [r13+0x0],0xfd4ab0
  925757:	49 89 6d 10          	mov    QWORD PTR [r13+0x10],rbp
  92575b:	45 89 65 18          	mov    DWORD PTR [r13+0x18],r12d
  92575f:	45 89 65 1c          	mov    DWORD PTR [r13+0x1c],r12d
  925763:	4c 89 ee             	mov    rsi,r13
  925766:	41 c6 45 20 00       	mov    BYTE PTR [r13+0x20],0x0
  92576b:	41 c6 45 21 01       	mov    BYTE PTR [r13+0x21],0x1
  925770:	e8 eb 0a 00 00       	call   926260 <TArrayList<CEquipmentRef*>::add(CEquipmentRef*)>
  925775:	48 8b 45 00          	mov    rax,QWORD PTR [rbp+0x0]
  925779:	44 89 e1             	mov    ecx,r12d
  92577c:	48 8b 53 20          	mov    rdx,QWORD PTR [rbx+0x20]
  925780:	48 89 de             	mov    rsi,rbx
  925783:	48 89 ef             	mov    rdi,rbp
  925786:	ff 90 20 03 00 00    	call   QWORD PTR [rax+0x320]
  92578c:	48 89 df             	mov    rdi,rbx
  92578f:	e8 4c 58 ff ff       	call   91afe0 <CInventory::updateBonuses()>
  925794:	48 89 df             	mov    rdi,rbx
  925797:	e8 a4 ec ff ff       	call   924440 <CInventory::calculateEffectValues()>
  92579c:	48 89 df             	mov    rdi,rbx
  92579f:	e8 0c f3 ff ff       	call   924ab0 <CInventory::verifyEquipment()>
  9257a4:	44 8b 63 50          	mov    r12d,DWORD PTR [rbx+0x50]
  9257a8:	45 85 e4             	test   r12d,r12d
  9257ab:	74 3b                	je     9257e8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x148>
  9257ad:	45 31 e4             	xor    r12d,r12d
  9257b0:	eb 20                	jmp    9257d2 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x132>
  9257b2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  9257b8:	48 8b 43 48          	mov    rax,QWORD PTR [rbx+0x48]
  9257bc:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  9257bf:	48 89 ee             	mov    rsi,rbp
  9257c2:	41 83 c4 01          	add    r12d,0x1
  9257c6:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  9257c9:	ff 50 20             	call   QWORD PTR [rax+0x20]
  9257cc:	44 3b 63 50          	cmp    r12d,DWORD PTR [rbx+0x50]
  9257d0:	73 16                	jae    9257e8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x148>
  9257d2:	44 3b 63 54          	cmp    r12d,DWORD PTR [rbx+0x54]
  9257d6:	73 e0                	jae    9257b8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x118>
  9257d8:	44 89 e0             	mov    eax,r12d
  9257db:	48 c1 e0 03          	shl    rax,0x3
  9257df:	48 03 43 48          	add    rax,QWORD PTR [rbx+0x48]
  9257e3:	eb d7                	jmp    9257bc <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x11c>
  9257e5:	0f 1f 00             	nop    DWORD PTR [rax]
  9257e8:	48 83 c4 48          	add    rsp,0x48
  9257ec:	b8 01 00 00 00       	mov    eax,0x1
  9257f1:	5b                   	pop    rbx
  9257f2:	5d                   	pop    rbp
  9257f3:	41 5c                	pop    r12
  9257f5:	41 5d                	pop    r13
  9257f7:	c3                   	ret
  9257f8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  925800:	45 85 e4             	test   r12d,r12d
  925803:	41 b8 01 00 00 00    	mov    r8d,0x1
  925809:	74 0d                	je     925818 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x178>
  92580b:	45 30 c0             	xor    r8b,r8b
  92580e:	41 83 fc 01          	cmp    r12d,0x1
  925812:	0f 85 cd fe ff ff    	jne    9256e5 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x45>
  925818:	8b 73 38             	mov    esi,DWORD PTR [rbx+0x38]
  92581b:	85 f6                	test   esi,esi
  92581d:	0f 84 0d ff ff ff    	je     925730 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x90>
  925823:	8b 7b 3c             	mov    edi,DWORD PTR [rbx+0x3c]
  925826:	31 c9                	xor    ecx,ecx
  925828:	31 c0                	xor    eax,eax
  92582a:	eb 25                	jmp    925851 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x1b1>
  92582c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  925830:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
  925834:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  925837:	48 85 d2             	test   rdx,rdx
  92583a:	74 06                	je     925842 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x1a2>
  92583c:	44 3b 42 18          	cmp    r8d,DWORD PTR [rdx+0x18]
  925840:	74 2e                	je     925870 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x1d0>
  925842:	83 c0 01             	add    eax,0x1
  925845:	48 83 c1 08          	add    rcx,0x8
  925849:	39 f0                	cmp    eax,esi
  92584b:	0f 83 97 fe ff ff    	jae    9256e8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x48>
  925851:	39 c7                	cmp    edi,eax
  925853:	76 db                	jbe    925830 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x190>
  925855:	48 89 ca             	mov    rdx,rcx
  925858:	48 03 53 30          	add    rdx,QWORD PTR [rbx+0x30]
  92585c:	eb d6                	jmp    925834 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x194>
  92585e:	66 90                	xchg   ax,ax
  925860:	44 89 62 18          	mov    DWORD PTR [rdx+0x18],r12d
  925864:	e9 0c ff ff ff       	jmp    925775 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0xd5>
  925869:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  925870:	4c 8b 6a 10          	mov    r13,QWORD PTR [rdx+0x10]
  925874:	4d 85 ed             	test   r13,r13
  925877:	0f 84 6b fe ff ff    	je     9256e8 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x48>
  92587d:	be 0a 00 00 00       	mov    esi,0xa
  925882:	4c 89 ef             	mov    rdi,r13
  925885:	e8 16 0a ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  92588a:	84 c0                	test   al,al
  92588c:	0f 84 53 fe ff ff    	je     9256e5 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x45>
  925892:	4c 89 ee             	mov    rsi,r13
  925895:	48 89 df             	mov    rdi,rbx
  925898:	e8 73 ef ff ff       	call   924810 <CInventory::removeEquipment(CEquipment*)>
  92589d:	ba 01 00 00 00       	mov    edx,0x1
  9258a2:	4c 89 ee             	mov    rsi,r13
  9258a5:	48 89 df             	mov    rdi,rbx
  9258a8:	e8 03 f9 ff ff       	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  9258ad:	48 85 c0             	test   rax,rax
  9258b0:	0f 85 2f fe ff ff    	jne    9256e5 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x45>
  9258b6:	48 8b 7b 20          	mov    rdi,QWORD PTR [rbx+0x20]
  9258ba:	be 01 00 00 00       	mov    esi,0x1
  9258bf:	e8 bc 17 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  9258c4:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  9258ca:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  9258cf:	31 ff                	xor    edi,edi
  9258d1:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  9258d7:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  9258dc:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  9258e1:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  9258e5:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  9258e9:	49 8b 45 68          	mov    rax,QWORD PTR [r13+0x68]
  9258ed:	48 85 c0             	test   rax,rax
  9258f0:	74 04                	je     9258f6 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x256>
  9258f2:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  9258f6:	48 8d 54 24 30       	lea    rdx,[rsp+0x30]
  9258fb:	b9 01 00 00 00       	mov    ecx,0x1
  925900:	4c 89 ee             	mov    rsi,r13
  925903:	e8 68 70 03 00       	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  925908:	48 8b 7b 20          	mov    rdi,QWORD PTR [rbx+0x20]
  92590c:	be 01 00 00 00       	mov    esi,0x1
  925911:	e8 6a 17 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  925916:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  92591c:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  925921:	48 8d 74 24 20       	lea    rsi,[rsp+0x20]
  925926:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  92592c:	4c 89 ef             	mov    rdi,r13
  92592f:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  925934:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  925939:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  92593d:	89 44 24 28          	mov    DWORD PTR [rsp+0x28],eax
  925941:	e8 9a 17 0c 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  925946:	49 8b 45 00          	mov    rax,QWORD PTR [r13+0x0]
  92594a:	4c 89 ef             	mov    rdi,r13
  92594d:	ff 90 60 03 00 00    	call   QWORD PTR [rax+0x360]
  925953:	e9 8d fd ff ff       	jmp    9256e5 <CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)+0x45>
  925958:	48 89 c3             	mov    rbx,rax
  92595b:	4c 89 ef             	mov    rdi,r13
  92595e:	e8 05 f9 c2 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  925963:	48 89 df             	mov    rdi,rbx
  925966:	e8 2d eb c2 ff       	call   554498 <_Unwind_Resume@plt>
