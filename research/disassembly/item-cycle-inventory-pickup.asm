# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0x924bd0, 0x9251b0); source instructions unchanged.
  924bd0:	48 89 5c 24 d0       	mov    QWORD PTR [rsp-0x30],rbx
  924bd5:	48 89 6c 24 d8       	mov    QWORD PTR [rsp-0x28],rbp
  924bda:	48 89 fb             	mov    rbx,rdi
  924bdd:	4c 89 64 24 e0       	mov    QWORD PTR [rsp-0x20],r12
  924be2:	4c 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],r13
  924be7:	49 89 f4             	mov    r12,rsi
  924bea:	4c 89 74 24 f0       	mov    QWORD PTR [rsp-0x10],r14
  924bef:	4c 89 7c 24 f8       	mov    QWORD PTR [rsp-0x8],r15
  924bf4:	48 81 ec 88 00 00 00 	sub    rsp,0x88
  924bfb:	83 fa ff             	cmp    edx,0xffffffff
  924bfe:	89 d5                	mov    ebp,edx
  924c00:	0f 84 82 02 00 00    	je     924e88 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b8>
  924c06:	81 fa e7 03 00 00    	cmp    edx,0x3e7
  924c0c:	0f 84 76 02 00 00    	je     924e88 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b8>
  924c12:	83 fa 13             	cmp    edx,0x13
  924c15:	0f 8f 3d 04 00 00    	jg     925058 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x488>
  924c1b:	83 fd 0b             	cmp    ebp,0xb
  924c1e:	0f 86 f4 01 00 00    	jbe    924e18 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x248>
  924c24:	48 8b 7b 20          	mov    rdi,QWORD PTR [rbx+0x20]
  924c28:	48 85 ff             	test   rdi,rdi
  924c2b:	74 44                	je     924c71 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xa1>
  924c2d:	be 1c 00 00 00       	mov    esi,0x1c
  924c32:	e8 69 16 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924c37:	84 c0                	test   al,al
  924c39:	74 36                	je     924c71 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xa1>
  924c3b:	48 8b 73 20          	mov    rsi,QWORD PTR [rbx+0x20]
  924c3f:	4c 8d 6c 24 40       	lea    r13,[rsp+0x40]
  924c44:	4c 89 ef             	mov    rdi,r13
  924c47:	48 83 c6 40          	add    rsi,0x40
  924c4b:	e8 38 e6 c2 ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  924c50:	4c 89 ee             	mov    rsi,r13
  924c53:	4c 89 e7             	mov    rdi,r12
  924c56:	e8 c5 3c f6 ff       	call   888920 <CEquipment::reskinByClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  924c5b:	48 8b 7c 24 40       	mov    rdi,QWORD PTR [rsp+0x40]
  924c60:	48 83 ef 18          	sub    rdi,0x18
  924c64:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  924c6b:	0f 85 5c 03 00 00    	jne    924fcd <CInventory::pickupEquipment(CEquipment*, int, bool)+0x3fd>
  924c71:	be 0a 00 00 00       	mov    esi,0xa
  924c76:	4c 89 e7             	mov    rdi,r12
  924c79:	e8 22 16 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924c7e:	84 c0                	test   al,al
  924c80:	0f 85 42 01 00 00    	jne    924dc8 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1f8>
  924c86:	85 ed                	test   ebp,ebp
  924c88:	41 b8 01 00 00 00    	mov    r8d,0x1
  924c8e:	74 0c                	je     924c9c <CInventory::pickupEquipment(CEquipment*, int, bool)+0xcc>
  924c90:	45 30 c0             	xor    r8b,r8b
  924c93:	83 fd 01             	cmp    ebp,0x1
  924c96:	0f 85 2c 01 00 00    	jne    924dc8 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1f8>
  924c9c:	8b 73 38             	mov    esi,DWORD PTR [rbx+0x38]
  924c9f:	85 f6                	test   esi,esi
  924ca1:	0f 84 29 02 00 00    	je     924ed0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x300>
  924ca7:	8b 7b 3c             	mov    edi,DWORD PTR [rbx+0x3c]
  924caa:	31 c9                	xor    ecx,ecx
  924cac:	31 c0                	xor    eax,eax
  924cae:	eb 21                	jmp    924cd1 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x101>
  924cb0:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
  924cb4:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  924cb7:	48 85 d2             	test   rdx,rdx
  924cba:	74 06                	je     924cc2 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xf2>
  924cbc:	44 3b 42 18          	cmp    r8d,DWORD PTR [rdx+0x18]
  924cc0:	74 1e                	je     924ce0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x110>
  924cc2:	83 c0 01             	add    eax,0x1
  924cc5:	48 83 c1 08          	add    rcx,0x8
  924cc9:	39 f0                	cmp    eax,esi
  924ccb:	0f 83 fa 00 00 00    	jae    924dcb <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1fb>
  924cd1:	39 c7                	cmp    edi,eax
  924cd3:	76 db                	jbe    924cb0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xe0>
  924cd5:	48 89 ca             	mov    rdx,rcx
  924cd8:	48 03 53 30          	add    rdx,QWORD PTR [rbx+0x30]
  924cdc:	eb d6                	jmp    924cb4 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xe4>
  924cde:	66 90                	xchg   ax,ax
  924ce0:	4c 8b 6a 10          	mov    r13,QWORD PTR [rdx+0x10]
  924ce4:	4d 85 ed             	test   r13,r13
  924ce7:	0f 84 de 00 00 00    	je     924dcb <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1fb>
  924ced:	be 0a 00 00 00       	mov    esi,0xa
  924cf2:	4c 89 ef             	mov    rdi,r13
  924cf5:	e8 a6 15 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924cfa:	84 c0                	test   al,al
  924cfc:	0f 84 c6 00 00 00    	je     924dc8 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1f8>
  924d02:	4c 89 ee             	mov    rsi,r13
  924d05:	48 89 df             	mov    rdi,rbx
  924d08:	e8 03 fb ff ff       	call   924810 <CInventory::removeEquipment(CEquipment*)>
  924d0d:	ba 01 00 00 00       	mov    edx,0x1
  924d12:	4c 89 ee             	mov    rsi,r13
  924d15:	48 89 df             	mov    rdi,rbx
  924d18:	e8 93 04 00 00       	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  924d1d:	48 85 c0             	test   rax,rax
  924d20:	0f 85 a2 00 00 00    	jne    924dc8 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x1f8>
  924d26:	48 8b 7b 20          	mov    rdi,QWORD PTR [rbx+0x20]
  924d2a:	be 01 00 00 00       	mov    esi,0x1
  924d2f:	e8 4c 23 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  924d34:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  924d3a:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  924d3f:	31 ff                	xor    edi,edi
  924d41:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  924d47:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  924d4c:	48 89 44 24 30       	mov    QWORD PTR [rsp+0x30],rax
  924d51:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  924d55:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  924d59:	49 8b 45 68          	mov    rax,QWORD PTR [r13+0x68]
  924d5d:	48 85 c0             	test   rax,rax
  924d60:	74 04                	je     924d66 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x196>
  924d62:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  924d66:	48 8d 54 24 30       	lea    rdx,[rsp+0x30]
  924d6b:	b9 01 00 00 00       	mov    ecx,0x1
  924d70:	4c 89 ee             	mov    rsi,r13
  924d73:	e8 f8 7b 03 00       	call   95c970 <CLevel::addItem(CItem*, Ogre::Vector3 const&, bool)>
  924d78:	48 8b 7b 20          	mov    rdi,QWORD PTR [rbx+0x20]
  924d7c:	be 01 00 00 00       	mov    esi,0x1
  924d81:	e8 fa 22 0c 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  924d86:	66 0f d6 44 24 08    	movq   QWORD PTR [rsp+0x8],xmm0
  924d8c:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  924d91:	48 8d 74 24 20       	lea    rsi,[rsp+0x20]
  924d96:	f3 0f 11 4c 24 18    	movss  DWORD PTR [rsp+0x18],xmm1
  924d9c:	4c 89 ef             	mov    rdi,r13
  924d9f:	48 89 44 24 10       	mov    QWORD PTR [rsp+0x10],rax
  924da4:	48 89 44 24 20       	mov    QWORD PTR [rsp+0x20],rax
  924da9:	8b 44 24 18          	mov    eax,DWORD PTR [rsp+0x18]
  924dad:	89 44 24 28          	mov    DWORD PTR [rsp+0x28],eax
  924db1:	e8 2a 23 0c 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  924db6:	49 8b 45 00          	mov    rax,QWORD PTR [r13+0x0]
  924dba:	4c 89 ef             	mov    rdi,r13
  924dbd:	ff 90 60 03 00 00    	call   QWORD PTR [rax+0x360]
  924dc3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  924dc8:	8b 73 38             	mov    esi,DWORD PTR [rbx+0x38]
  924dcb:	85 f6                	test   esi,esi
  924dcd:	0f 84 fd 00 00 00    	je     924ed0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x300>
  924dd3:	8b 7b 3c             	mov    edi,DWORD PTR [rbx+0x3c]
  924dd6:	31 c9                	xor    ecx,ecx
  924dd8:	31 c0                	xor    eax,eax
  924dda:	eb 28                	jmp    924e04 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x234>
  924ddc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  924de0:	48 8b 53 30          	mov    rdx,QWORD PTR [rbx+0x30]
  924de4:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  924de7:	48 85 d2             	test   rdx,rdx
  924dea:	74 09                	je     924df5 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x225>
  924dec:	3b 6a 18             	cmp    ebp,DWORD PTR [rdx+0x18]
  924def:	0f 84 53 02 00 00    	je     925048 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x478>
  924df5:	83 c0 01             	add    eax,0x1
  924df8:	48 83 c1 08          	add    rcx,0x8
  924dfc:	39 f0                	cmp    eax,esi
  924dfe:	0f 83 cc 00 00 00    	jae    924ed0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x300>
  924e04:	39 f8                	cmp    eax,edi
  924e06:	73 d8                	jae    924de0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x210>
  924e08:	48 89 ca             	mov    rdx,rcx
  924e0b:	48 03 53 30          	add    rdx,QWORD PTR [rbx+0x30]
  924e0f:	eb d3                	jmp    924de4 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x214>
  924e11:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  924e18:	4c 63 ed             	movsxd r13,ebp
  924e1b:	4c 89 e7             	mov    rdi,r12
  924e1e:	42 8b 34 ed c0 49 fd 00 	mov    esi,DWORD PTR [r13*8+0xfd49c0]
  924e26:	e8 75 14 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924e2b:	84 c0                	test   al,al
  924e2d:	0f 85 f1 fd ff ff    	jne    924c24 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x54>
  924e33:	4f 8d 74 2d 01       	lea    r14,[r13+r13*1+0x1]
  924e38:	4c 89 e7             	mov    rdi,r12
  924e3b:	42 8b 34 b5 c0 49 fd 00 	mov    esi,DWORD PTR [r14*4+0xfd49c0]
  924e43:	e8 58 14 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924e48:	84 c0                	test   al,al
  924e4a:	0f 85 d4 fd ff ff    	jne    924c24 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x54>
  924e50:	42 8b 34 ed 20 4a fd 00 	mov    esi,DWORD PTR [r13*8+0xfd4a20]
  924e58:	4c 89 e7             	mov    rdi,r12
  924e5b:	e8 40 14 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924e60:	84 c0                	test   al,al
  924e62:	0f 85 bc fd ff ff    	jne    924c24 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x54>
  924e68:	42 8b 34 b5 20 4a fd 00 	mov    esi,DWORD PTR [r14*4+0xfd4a20]
  924e70:	4c 89 e7             	mov    rdi,r12
  924e73:	e8 28 14 ed ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  924e78:	84 c0                	test   al,al
  924e7a:	0f 85 a4 fd ff ff    	jne    924c24 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x54>
  924e80:	45 31 ed             	xor    r13d,r13d
  924e83:	eb 16                	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  924e85:	0f 1f 00             	nop    DWORD PTR [rax]
  924e88:	ba 01 00 00 00       	mov    edx,0x1
  924e8d:	4c 89 e6             	mov    rsi,r12
  924e90:	48 89 df             	mov    rdi,rbx
  924e93:	e8 18 03 00 00       	call   9251b0 <CInventory::pickupEquipment(CEquipment*, bool)>
  924e98:	49 89 c5             	mov    r13,rax
  924e9b:	4c 89 e8             	mov    rax,r13
  924e9e:	48 8b 5c 24 58       	mov    rbx,QWORD PTR [rsp+0x58]
  924ea3:	48 8b 6c 24 60       	mov    rbp,QWORD PTR [rsp+0x60]
  924ea8:	4c 8b 64 24 68       	mov    r12,QWORD PTR [rsp+0x68]
  924ead:	4c 8b 6c 24 70       	mov    r13,QWORD PTR [rsp+0x70]
  924eb2:	4c 8b 74 24 78       	mov    r14,QWORD PTR [rsp+0x78]
  924eb7:	4c 8b bc 24 80 00 00 00 	mov    r15,QWORD PTR [rsp+0x80]
  924ebf:	48 81 c4 88 00 00 00 	add    rsp,0x88
  924ec6:	c3                   	ret
  924ec7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  924ed0:	45 31 ed             	xor    r13d,r13d
  924ed3:	4d 39 ec             	cmp    r12,r13
  924ed6:	74 a8                	je     924e80 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b0>
  924ed8:	80 7b 14 00          	cmp    BYTE PTR [rbx+0x14],0x0
  924edc:	0f 84 4e 01 00 00    	je     925030 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x460>
  924ee2:	41 83 bc 24 3c 02 00 00 01 	cmp    DWORD PTR [r12+0x23c],0x1
  924eeb:	0f 8e 3f 01 00 00    	jle    925030 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x460>
  924ef1:	4d 85 ed             	test   r13,r13
  924ef4:	74 3e                	je     924f34 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x364>
  924ef6:	49 8b 85 a0 01 00 00 	mov    rax,QWORD PTR [r13+0x1a0]
  924efd:	49 39 84 24 a0 01 00 00 	cmp    QWORD PTR [r12+0x1a0],rax
  924f05:	0f 85 75 ff ff ff    	jne    924e80 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b0>
  924f0b:	41 8b 85 38 02 00 00 	mov    eax,DWORD PTR [r13+0x238]
  924f12:	41 8b b4 24 38 02 00 00 	mov    esi,DWORD PTR [r12+0x238]
  924f1a:	41 8b 95 3c 02 00 00 	mov    edx,DWORD PTR [r13+0x23c]
  924f21:	8d 0c 06             	lea    ecx,[rsi+rax*1]
  924f24:	39 d1                	cmp    ecx,edx
  924f26:	0f 8e c5 01 00 00    	jle    9250f1 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x521>
  924f2c:	39 d0                	cmp    eax,edx
  924f2e:	0f 8c 1b 02 00 00    	jl     92514f <CInventory::pickupEquipment(CEquipment*, int, bool)+0x57f>
  924f34:	bf 28 00 00 00       	mov    edi,0x28
  924f39:	31 c9                	xor    ecx,ecx
  924f3b:	31 d2                	xor    edx,edx
  924f3d:	31 f6                	xor    esi,esi
  924f3f:	e8 d4 e3 c2 ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  924f44:	48 89 c7             	mov    rdi,rax
  924f47:	49 89 c6             	mov    r14,rax
  924f4a:	e8 71 47 45 00       	call   d796c0 <CRunicCore::CRunicCore()>
  924f4f:	48 8d 7b 30          	lea    rdi,[rbx+0x30]
  924f53:	49 c7 06 b0 4a fd 00 	mov    QWORD PTR [r14],0xfd4ab0
  924f5a:	4d 89 66 10          	mov    QWORD PTR [r14+0x10],r12
  924f5e:	41 89 6e 18          	mov    DWORD PTR [r14+0x18],ebp
  924f62:	41 89 6e 1c          	mov    DWORD PTR [r14+0x1c],ebp
  924f66:	4c 89 f6             	mov    rsi,r14
  924f69:	41 c6 46 20 00       	mov    BYTE PTR [r14+0x20],0x0
  924f6e:	41 c6 46 21 01       	mov    BYTE PTR [r14+0x21],0x1
  924f73:	45 31 f6             	xor    r14d,r14d
  924f76:	e8 e5 12 00 00       	call   926260 <TArrayList<CEquipmentRef*>::add(CEquipmentRef*)>
  924f7b:	49 8b 04 24          	mov    rax,QWORD PTR [r12]
  924f7f:	48 8b 53 20          	mov    rdx,QWORD PTR [rbx+0x20]
  924f83:	48 89 de             	mov    rsi,rbx
  924f86:	4c 89 e7             	mov    rdi,r12
  924f89:	ff 90 10 03 00 00    	call   QWORD PTR [rax+0x310]
  924f8f:	44 8b 53 50          	mov    r10d,DWORD PTR [rbx+0x50]
  924f93:	45 85 d2             	test   r10d,r10d
  924f96:	74 68                	je     925000 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x430>
  924f98:	45 31 ff             	xor    r15d,r15d
  924f9b:	eb 1d                	jmp    924fba <CInventory::pickupEquipment(CEquipment*, int, bool)+0x3ea>
  924f9d:	0f 1f 00             	nop    DWORD PTR [rax]
  924fa0:	48 8b 43 48          	mov    rax,QWORD PTR [rbx+0x48]
  924fa4:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  924fa7:	4c 89 e6             	mov    rsi,r12
  924faa:	41 83 c7 01          	add    r15d,0x1
  924fae:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  924fb1:	ff 50 10             	call   QWORD PTR [rax+0x10]
  924fb4:	44 3b 7b 50          	cmp    r15d,DWORD PTR [rbx+0x50]
  924fb8:	73 46                	jae    925000 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x430>
  924fba:	44 3b 7b 54          	cmp    r15d,DWORD PTR [rbx+0x54]
  924fbe:	73 e0                	jae    924fa0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x3d0>
  924fc0:	44 89 f8             	mov    eax,r15d
  924fc3:	48 c1 e0 03          	shl    rax,0x3
  924fc7:	48 03 43 48          	add    rax,QWORD PTR [rbx+0x48]
  924fcb:	eb d7                	jmp    924fa4 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x3d4>
  924fcd:	b8 c8 41 55 00       	mov    eax,0x5541c8
  924fd2:	48 85 c0             	test   rax,rax
  924fd5:	0f 84 c6 01 00 00    	je     9251a1 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x5d1>
  924fdb:	83 c8 ff             	or     eax,0xffffffff
  924fde:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  924fe3:	85 c0                	test   eax,eax
  924fe5:	0f 8f 86 fc ff ff    	jg     924c71 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xa1>
  924feb:	48 8d 74 24 4f       	lea    rsi,[rsp+0x4f]
  924ff0:	e8 53 e5 c2 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  924ff5:	e9 77 fc ff ff       	jmp    924c71 <CInventory::pickupEquipment(CEquipment*, int, bool)+0xa1>
  924ffa:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  925000:	45 84 f6             	test   r14b,r14b
  925003:	74 7b                	je     925080 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x4b0>
  925005:	49 8b 44 24 68       	mov    rax,QWORD PTR [r12+0x68]
  92500a:	48 85 c0             	test   rax,rax
  92500d:	0f 84 2d 01 00 00    	je     925140 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x570>
  925013:	48 8b 78 18          	mov    rdi,QWORD PTR [rax+0x18]
  925017:	48 85 ff             	test   rdi,rdi
  92501a:	0f 84 20 01 00 00    	je     925140 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x570>
  925020:	4c 89 e6             	mov    rsi,r12
  925023:	e8 e8 4e 02 00       	call   949f10 <CLevel::deleteItem(CItem*)>
  925028:	e9 6e fe ff ff       	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  92502d:	0f 1f 00             	nop    DWORD PTR [rax]
  925030:	4d 85 ed             	test   r13,r13
  925033:	0f 85 47 fe ff ff    	jne    924e80 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b0>
  925039:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  925040:	e9 ef fe ff ff       	jmp    924f34 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x364>
  925045:	0f 1f 00             	nop    DWORD PTR [rax]
  925048:	4c 8b 6a 10          	mov    r13,QWORD PTR [rdx+0x10]
  92504c:	e9 82 fe ff ff       	jmp    924ed3 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x303>
  925051:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  925058:	e8 63 69 ff ff       	call   91b9c0 <CInventory::getRequiredPane(CEquipment*)>
  92505d:	48 89 df             	mov    rdi,rbx
  925060:	89 c6                	mov    esi,eax
  925062:	e8 e9 5f ff ff       	call   91b050 <CInventory::getPaneIndex(EINVENTORY_PANES)>
  925067:	89 ea                	mov    edx,ebp
  925069:	89 c6                	mov    esi,eax
  92506b:	48 89 df             	mov    rdi,rbx
  92506e:	e8 7d 60 ff ff       	call   91b0f0 <CInventory::slotIsInPane(unsigned int, int)>
  925073:	84 c0                	test   al,al
  925075:	0f 85 a0 fb ff ff    	jne    924c1b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x4b>
  92507b:	e9 00 fe ff ff       	jmp    924e80 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2b0>
  925080:	83 fd 0b             	cmp    ebp,0xb
  925083:	0f 8f 97 00 00 00    	jg     925120 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x550>
  925089:	49 8b 04 24          	mov    rax,QWORD PTR [r12]
  92508d:	48 8b 53 20          	mov    rdx,QWORD PTR [rbx+0x20]
  925091:	89 e9                	mov    ecx,ebp
  925093:	48 89 de             	mov    rsi,rbx
  925096:	4c 89 e7             	mov    rdi,r12
  925099:	ff 90 20 03 00 00    	call   QWORD PTR [rax+0x320]
  92509f:	48 89 df             	mov    rdi,rbx
  9250a2:	e8 39 5f ff ff       	call   91afe0 <CInventory::updateBonuses()>
  9250a7:	48 89 df             	mov    rdi,rbx
  9250aa:	e8 91 f3 ff ff       	call   924440 <CInventory::calculateEffectValues()>
  9250af:	48 89 df             	mov    rdi,rbx
  9250b2:	e8 f9 f9 ff ff       	call   924ab0 <CInventory::verifyEquipment()>
  9250b7:	44 8b 4b 50          	mov    r9d,DWORD PTR [rbx+0x50]
  9250bb:	45 85 c9             	test   r9d,r9d
  9250be:	74 50                	je     925110 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x540>
  9250c0:	31 ed                	xor    ebp,ebp
  9250c2:	eb 1c                	jmp    9250e0 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x510>
  9250c4:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  9250c8:	48 8b 43 48          	mov    rax,QWORD PTR [rbx+0x48]
  9250cc:	48 8b 38             	mov    rdi,QWORD PTR [rax]
  9250cf:	4c 89 e6             	mov    rsi,r12
  9250d2:	83 c5 01             	add    ebp,0x1
  9250d5:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  9250d8:	ff 50 20             	call   QWORD PTR [rax+0x20]
  9250db:	3b 6b 50             	cmp    ebp,DWORD PTR [rbx+0x50]
  9250de:	73 30                	jae    925110 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x540>
  9250e0:	39 6b 54             	cmp    DWORD PTR [rbx+0x54],ebp
  9250e3:	76 e3                	jbe    9250c8 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x4f8>
  9250e5:	89 e8                	mov    eax,ebp
  9250e7:	48 c1 e0 03          	shl    rax,0x3
  9250eb:	48 03 43 48          	add    rax,QWORD PTR [rbx+0x48]
  9250ef:	eb db                	jmp    9250cc <CInventory::pickupEquipment(CEquipment*, int, bool)+0x4fc>
  9250f1:	49 8b 45 00          	mov    rax,QWORD PTR [r13+0x0]
  9250f5:	4c 89 ef             	mov    rdi,r13
  9250f8:	41 be 01 00 00 00    	mov    r14d,0x1
  9250fe:	ff 90 38 03 00 00    	call   QWORD PTR [rax+0x338]
  925104:	e9 72 fe ff ff       	jmp    924f7b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x3ab>
  925109:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  925110:	4d 89 e5             	mov    r13,r12
  925113:	e9 83 fd ff ff       	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  925118:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  925120:	48 89 df             	mov    rdi,rbx
  925123:	4d 89 e5             	mov    r13,r12
  925126:	e8 b5 5e ff ff       	call   91afe0 <CInventory::updateBonuses()>
  92512b:	48 89 df             	mov    rdi,rbx
  92512e:	e8 0d f3 ff ff       	call   924440 <CInventory::calculateEffectValues()>
  925133:	48 89 df             	mov    rdi,rbx
  925136:	e8 75 f9 ff ff       	call   924ab0 <CInventory::verifyEquipment()>
  92513b:	e9 5b fd ff ff       	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  925140:	49 8b 04 24          	mov    rax,QWORD PTR [r12]
  925144:	4c 89 e7             	mov    rdi,r12
  925147:	ff 50 08             	call   QWORD PTR [rax+0x8]
  92514a:	e9 4c fd ff ff       	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  92514f:	89 d3                	mov    ebx,edx
  925151:	4c 89 ef             	mov    rdi,r13
  925154:	29 c3                	sub    ebx,eax
  925156:	49 8b 45 00          	mov    rax,QWORD PTR [r13+0x0]
  92515a:	45 31 ed             	xor    r13d,r13d
  92515d:	89 de                	mov    esi,ebx
  92515f:	ff 90 38 03 00 00    	call   QWORD PTR [rax+0x338]
  925165:	49 8b 04 24          	mov    rax,QWORD PTR [r12]
  925169:	89 de                	mov    esi,ebx
  92516b:	4c 89 e7             	mov    rdi,r12
  92516e:	f7 de                	neg    esi
  925170:	ff 90 38 03 00 00    	call   QWORD PTR [rax+0x338]
  925176:	e9 20 fd ff ff       	jmp    924e9b <CInventory::pickupEquipment(CEquipment*, int, bool)+0x2cb>
  92517b:	48 89 c3             	mov    rbx,rax
  92517e:	4c 89 ef             	mov    rdi,r13
  925181:	e8 52 f7 c2 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  925186:	48 89 df             	mov    rdi,rbx
  925189:	e8 0a f3 c2 ff       	call   554498 <_Unwind_Resume@plt>
  92518e:	48 89 c3             	mov    rbx,rax
  925191:	4c 89 f7             	mov    rdi,r14
  925194:	e8 cf 00 c3 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  925199:	48 89 df             	mov    rdi,rbx
  92519c:	e8 f7 f2 c2 ff       	call   554498 <_Unwind_Resume@plt>
  9251a1:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  9251a4:	8d 50 ff             	lea    edx,[rax-0x1]
  9251a7:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  9251aa:	e9 34 fe ff ff       	jmp    924fe3 <CInventory::pickupEquipment(CEquipment*, int, bool)+0x413>
  9251af:	90                   	nop
