# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x9249b0, 0x924ab0); source instructions unchanged.
  9249b0:	48 89 5c 24 f0       	mov    QWORD PTR [rsp-0x10],rbx
  9249b5:	48 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],rbp
  9249ba:	48 89 f3             	mov    rbx,rsi
  9249bd:	48 83 ec 58          	sub    rsp,0x58
  9249c1:	48 89 fd             	mov    rbp,rdi
  9249c4:	e8 47 fe ff ff       	call   924810 <CInventory::removeEquipment(CEquipment*)>
  9249c9:	ba 01 00 00 00       	mov    edx,0x1
  9249ce:	48 89 de             	mov    rsi,rbx
  9249d1:	48 89 ef             	mov    rdi,rbp
  9249d4:	e8 d7 07 00 00       	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  9249d9:	48 89 c2             	mov    rdx,rax
  9249dc:	b8 01 00 00 00       	mov    eax,0x1
  9249e1:	48 85 d2             	test   rdx,rdx
  9249e4:	74 12                	je     9249f8 <CInventory::unequipEquipment(CEquipment*)+0x48>
  9249e6:	48 8b 5c 24 48       	mov    rbx,QWORD PTR [rsp+0x48]
  9249eb:	48 8b 6c 24 50       	mov    rbp,QWORD PTR [rsp+0x50]
  9249f0:	48 83 c4 58          	add    rsp,0x58
  9249f4:	c3                   	ret
  9249f5:	0f 1f 00             	nop    DWORD PTR [rax]
  9249f8:	48 8b 7d 20          	mov    rdi,QWORD PTR [rbp+0x20]
  9249fc:	be 01 00 00 00       	mov    esi,0x1
  924a01:	e8 7a 26 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  924a06:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  924a0c:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  924a11:	31 ff                	xor    edi,edi
  924a13:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  924a19:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  924a1e:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  924a23:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  924a27:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  924a2b:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  924a2f:	48 85 c0             	test   rax,rax
  924a32:	74 04                	je     924a38 <CInventory::unequipEquipment(CEquipment*)+0x88>
  924a34:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  924a38:	48 8d 54 24 30       	lea    rdx,[rsp+0x30]
  924a3d:	b9 01 00 00 00       	mov    ecx,0x1
  924a42:	48 89 de             	mov    rsi,rbx
  924a45:	e8 26 7f 03 00       	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  924a4a:	48 8b 7d 20          	mov    rdi,QWORD PTR [rbp+0x20]
  924a4e:	be 01 00 00 00       	mov    esi,0x1
  924a53:	e8 28 26 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  924a58:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  924a5e:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  924a63:	48 8d 74 24 20       	lea    rsi,[rsp+0x20]
  924a68:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  924a6e:	48 89 df             	mov    rdi,rbx
  924a71:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  924a76:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  924a7b:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  924a7f:	89 44 24 28          	mov    DWORD PTR [rsp+0x28],eax
  924a83:	e8 58 26 0c 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  924a88:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  924a8b:	48 89 df             	mov    rdi,rbx
  924a8e:	ff 90 60 03 00 00    	call   QWORD PTR [rax+0x360]
  924a94:	31 c0                	xor    eax,eax
  924a96:	48 8b 5c 24 48       	mov    rbx,QWORD PTR [rsp+0x48]
  924a9b:	48 8b 6c 24 50       	mov    rbp,QWORD PTR [rsp+0x50]
  924aa0:	48 83 c4 58          	add    rsp,0x58
  924aa4:	c3                   	ret
  924aa5:	90                   	nop
  924aa6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
