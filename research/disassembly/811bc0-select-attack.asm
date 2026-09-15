# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
0000000000811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>:
  811bc0:	48 89 5c 24 d8       	mov    QWORD PTR [rsp-0x28],rbx
  811bc5:	48 89 6c 24 e0       	mov    QWORD PTR [rsp-0x20],rbp
  811bca:	48 89 fb             	mov    rbx,rdi
  811bcd:	4c 89 64 24 e8       	mov    QWORD PTR [rsp-0x18],r12
  811bd2:	4c 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],r13
  811bd7:	89 f5                	mov    ebp,esi
  811bd9:	4c 89 74 24 f8       	mov    QWORD PTR [rsp-0x8],r14
  811bde:	48 81 ec e8 00 00 00 	sub    rsp,0xe8
  811be5:	48 83 bf 90 03 00 00 00 	cmp    QWORD PTR [rdi+0x390],0x0
  811bed:	74 15                	je     811c04 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x44>
  811bef:	f3 0f 10 87 78 03 00 00 	movss  xmm0,DWORD PTR [rdi+0x378]
  811bf7:	0f 2e 05 fa 2b 79 00 	ucomiss xmm0,DWORD PTR [rip+0x792bfa]        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  811bfe:	0f 87 fc 01 00 00    	ja     811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811c04:	48 83 bb 00 02 00 00 00 	cmp    QWORD PTR [rbx+0x200],0x0
  811c0c:	0f 84 ee 01 00 00    	je     811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811c12:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811c19:	48 c7 83 90 03 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x390],0x0
  811c24:	48 85 ff             	test   rdi,rdi
  811c27:	0f 84 03 02 00 00    	je     811e30 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x270>
  811c2d:	31 f6                	xor    esi,esi
  811c2f:	e8 2c 98 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811c34:	48 85 c0             	test   rax,rax
  811c37:	0f 84 fb 03 00 00    	je     812038 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x478>
  811c3d:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811c44:	be 01 00 00 00       	mov    esi,0x1
  811c49:	e8 12 98 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811c4e:	48 85 c0             	test   rax,rax
  811c51:	0f 84 49 03 00 00    	je     811fa0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3e0>
  811c57:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811c5e:	be 01 00 00 00       	mov    esi,0x1
  811c63:	e8 f8 97 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811c68:	be 08 00 00 00       	mov    esi,0x8
  811c6d:	48 89 c7             	mov    rdi,rax
  811c70:	e8 2b 46 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  811c75:	84 c0                	test   al,al
  811c77:	0f 84 23 03 00 00    	je     811fa0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3e0>
  811c7d:	85 ed                	test   ebp,ebp
  811c7f:	0f 85 db 02 00 00    	jne    811f60 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3a0>
  811c85:	80 bb 7e 03 00 00 00 	cmp    BYTE PTR [rbx+0x37e],0x0
  811c8c:	0f 84 0e 03 00 00    	je     811fa0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3e0>
  811c92:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811c99:	be 01 00 00 00       	mov    esi,0x1
  811c9e:	e8 bd 97 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811ca3:	48 85 c0             	test   rax,rax
  811ca6:	48 89 83 98 04 00 00 	mov    QWORD PTR [rbx+0x498],rax
  811cad:	0f 84 f6 05 00 00    	je     8122a9 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x6e9>
  811cb3:	48 8b b0 a8 02 00 00 	mov    rsi,QWORD PTR [rax+0x2a8]
  811cba:	48 39 b3 90 03 00 00 	cmp    QWORD PTR [rbx+0x390],rsi
  811cc1:	74 07                	je     811cca <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x10a>
  811cc3:	48 89 b3 90 03 00 00 	mov    QWORD PTR [rbx+0x390],rsi
  811cca:	48 85 f6             	test   rsi,rsi
  811ccd:	74 1a                	je     811ce9 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x129>
  811ccf:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  811cd6:	48 83 c6 10          	add    rsi,0x10
  811cda:	e8 01 11 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  811cdf:	48 8b 93 90 03 00 00 	mov    rdx,QWORD PTR [rbx+0x390]
  811ce6:	89 42 64             	mov    DWORD PTR [rdx+0x64],eax
  811ce9:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  811cf0:	be 66 00 00 00       	mov    esi,0x66
  811cf5:	e8 a6 45 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  811cfa:	84 c0                	test   al,al
  811cfc:	0f 85 fe 00 00 00    	jne    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811d02:	48 83 bb a0 06 00 00 00 	cmp    QWORD PTR [rbx+0x6a0],0x0
  811d0a:	0f 85 d0 00 00 00    	jne    811de0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x220>
  811d10:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  811d14:	45 31 f6             	xor    r14d,r14d
  811d17:	48 85 c0             	test   rax,rax
  811d1a:	74 04                	je     811d20 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x160>
  811d1c:	4c 8b 70 10          	mov    r14,QWORD PTR [rax+0x10]
  811d20:	4c 8d a4 24 b0 00 00 00 	lea    r12,[rsp+0xb0]
  811d28:	48 8d 94 24 bf 00 00 00 	lea    rdx,[rsp+0xbf]
  811d30:	be 08 99 fc 00       	mov    esi,0xfc9908
  811d35:	4c 89 e7             	mov    rdi,r12
  811d38:	e8 bb 45 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811d3d:	48 8d ac 24 a0 00 00 00 	lea    rbp,[rsp+0xa0]
  811d45:	4c 89 e6             	mov    rsi,r12
  811d48:	48 89 ef             	mov    rdi,rbp
  811d4b:	e8 00 cd 47 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  811d50:	bf a0 00 00 00       	mov    edi,0xa0
  811d55:	e8 66 8f 04 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  811d5a:	f3 0f 10 05 9a 2a 79 00 	movss  xmm0,DWORD PTR [rip+0x792a9a]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  811d62:	b9 14 00 00 00       	mov    ecx,0x14
  811d67:	48 89 ea             	mov    rdx,rbp
  811d6a:	4c 89 f6             	mov    rsi,r14
  811d6d:	48 89 c7             	mov    rdi,rax
  811d70:	49 89 c5             	mov    r13,rax
  811d73:	e8 a8 ad 23 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  811d78:	4c 89 ab a0 06 00 00 	mov    QWORD PTR [rbx+0x6a0],r13
  811d7f:	48 89 ef             	mov    rdi,rbp
  811d82:	e8 01 45 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811d87:	4c 89 e7             	mov    rdi,r12
  811d8a:	e8 f9 44 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811d8f:	48 89 df             	mov    rdi,rbx
  811d92:	e8 d9 e3 ff ff       	call   810170 <CCharacter::alignment()>
  811d97:	48 8d ac 24 90 00 00 00 	lea    rbp,[rsp+0x90]
  811d9f:	83 f8 01             	cmp    eax,0x1
  811da2:	be 34 05 fa 00       	mov    esi,0xfa0534
  811da7:	b8 40 05 fa 00       	mov    eax,0xfa0540
  811dac:	48 8d 94 24 be 00 00 00 	lea    rdx,[rsp+0xbe]
  811db4:	48 0f 45 f0          	cmovne rsi,rax
  811db8:	48 89 ef             	mov    rdi,rbp
  811dbb:	e8 38 45 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811dc0:	48 8b bb a0 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a0]
  811dc7:	48 89 ee             	mov    rsi,rbp
  811dca:	e8 c1 82 23 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  811dcf:	48 89 ef             	mov    rdi,rbp
  811dd2:	e8 b1 44 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811dd7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  811de0:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  811de7:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  811dea:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  811df0:	48 8b bb a0 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a0]
  811df7:	48 8b 70 60          	mov    rsi,QWORD PTR [rax+0x60]
  811dfb:	e8 70 81 23 00       	call   a49f70 <CWeaponTrail::setWeaponEntity(Ogre::Entity*)>
  811e00:	48 8b 9c 24 c0 00 00 00 	mov    rbx,QWORD PTR [rsp+0xc0]
  811e08:	48 8b ac 24 c8 00 00 00 	mov    rbp,QWORD PTR [rsp+0xc8]
  811e10:	4c 8b a4 24 d0 00 00 00 	mov    r12,QWORD PTR [rsp+0xd0]
  811e18:	4c 8b ac 24 d8 00 00 00 	mov    r13,QWORD PTR [rsp+0xd8]
  811e20:	4c 8b b4 24 e0 00 00 00 	mov    r14,QWORD PTR [rsp+0xe0]
  811e28:	48 81 c4 e8 00 00 00 	add    rsp,0xe8
  811e2f:	c3                   	ret
  811e30:	48 8b b3 00 04 00 00 	mov    rsi,QWORD PTR [rbx+0x400]
  811e37:	48 2b b3 f8 03 00 00 	sub    rsi,QWORD PTR [rbx+0x3f8]
  811e3e:	48 c1 fe 03          	sar    rsi,0x3
  811e42:	85 f6                	test   esi,esi
  811e44:	74 ba                	je     811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811e46:	83 ee 01             	sub    esi,0x1
  811e49:	31 ff                	xor    edi,edi
  811e4b:	48 c7 83 98 04 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x498],0x0
  811e56:	e8 95 0d 48 00       	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  811e5b:	48 8b 93 f8 03 00 00 	mov    rdx,QWORD PTR [rbx+0x3f8]
  811e62:	89 c0                	mov    eax,eax
  811e64:	48 8b 34 c2          	mov    rsi,QWORD PTR [rdx+rax*8]
  811e68:	48 85 f6             	test   rsi,rsi
  811e6b:	48 89 b3 90 03 00 00 	mov    QWORD PTR [rbx+0x390],rsi
  811e72:	74 8c                	je     811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811e74:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  811e7b:	48 83 c6 10          	add    rsi,0x10
  811e7f:	e8 5c 0f 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  811e84:	48 8b 93 90 03 00 00 	mov    rdx,QWORD PTR [rbx+0x390]
  811e8b:	89 42 64             	mov    DWORD PTR [rdx+0x64],eax
  811e8e:	48 83 bb 98 06 00 00 00 	cmp    QWORD PTR [rbx+0x698],0x0
  811e96:	0f 85 64 ff ff ff    	jne    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811e9c:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  811ea0:	45 31 f6             	xor    r14d,r14d
  811ea3:	48 85 c0             	test   rax,rax
  811ea6:	74 04                	je     811eac <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x2ec>
  811ea8:	4c 8b 70 10          	mov    r14,QWORD PTR [rax+0x10]
  811eac:	4c 8d 64 24 20       	lea    r12,[rsp+0x20]
  811eb1:	48 8d 94 24 b9 00 00 00 	lea    rdx,[rsp+0xb9]
  811eb9:	be 08 99 fc 00       	mov    esi,0xfc9908
  811ebe:	4c 89 e7             	mov    rdi,r12
  811ec1:	e8 32 44 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811ec6:	48 8d 6c 24 10       	lea    rbp,[rsp+0x10]
  811ecb:	4c 89 e6             	mov    rsi,r12
  811ece:	48 89 ef             	mov    rdi,rbp
  811ed1:	e8 7a cb 47 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  811ed6:	bf a0 00 00 00       	mov    edi,0xa0
  811edb:	e8 e0 8d 04 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  811ee0:	f3 0f 10 05 14 29 79 00 	movss  xmm0,DWORD PTR [rip+0x792914]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  811ee8:	b9 14 00 00 00       	mov    ecx,0x14
  811eed:	48 89 ea             	mov    rdx,rbp
  811ef0:	4c 89 f6             	mov    rsi,r14
  811ef3:	48 89 c7             	mov    rdi,rax
  811ef6:	49 89 c5             	mov    r13,rax
  811ef9:	e8 22 ac 23 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  811efe:	4c 89 ab 98 06 00 00 	mov    QWORD PTR [rbx+0x698],r13
  811f05:	48 89 ef             	mov    rdi,rbp
  811f08:	e8 7b 43 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811f0d:	4c 89 e7             	mov    rdi,r12
  811f10:	e8 73 43 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811f15:	48 89 df             	mov    rdi,rbx
  811f18:	e8 53 e2 ff ff       	call   810170 <CCharacter::alignment()>
  811f1d:	83 f8 01             	cmp    eax,0x1
  811f20:	be 34 05 fa 00       	mov    esi,0xfa0534
  811f25:	b8 40 05 fa 00       	mov    eax,0xfa0540
  811f2a:	48 8d 94 24 b8 00 00 00 	lea    rdx,[rsp+0xb8]
  811f32:	48 0f 45 f0          	cmovne rsi,rax
  811f36:	48 89 e7             	mov    rdi,rsp
  811f39:	e8 ba 43 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  811f3e:	48 8b bb 98 06 00 00 	mov    rdi,QWORD PTR [rbx+0x698]
  811f45:	48 89 e6             	mov    rsi,rsp
  811f48:	e8 43 81 23 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  811f4d:	48 89 e7             	mov    rdi,rsp
  811f50:	e8 33 43 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  811f55:	e9 a6 fe ff ff       	jmp    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811f5a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  811f60:	83 fd 02             	cmp    ebp,0x2
  811f63:	0f 84 15 03 00 00    	je     81227e <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x6be>
  811f69:	83 fd 01             	cmp    ebp,0x1
  811f6c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  811f70:	75 2e                	jne    811fa0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3e0>
  811f72:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811f79:	be 01 00 00 00       	mov    esi,0x1
  811f7e:	e8 dd 94 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811f83:	be 3c 00 00 00       	mov    esi,0x3c
  811f88:	48 89 c7             	mov    rdi,rax
  811f8b:	e8 10 43 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  811f90:	84 c0                	test   al,al
  811f92:	0f 85 fa fc ff ff    	jne    811c92 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0xd2>
  811f98:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  811fa0:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  811fa7:	31 f6                	xor    esi,esi
  811fa9:	e8 b2 94 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  811fae:	48 89 83 98 04 00 00 	mov    QWORD PTR [rbx+0x498],rax
  811fb5:	48 8b b0 a0 02 00 00 	mov    rsi,QWORD PTR [rax+0x2a0]
  811fbc:	48 85 f6             	test   rsi,rsi
  811fbf:	48 89 b3 90 03 00 00 	mov    QWORD PTR [rbx+0x390],rsi
  811fc6:	74 21                	je     811fe9 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x429>
  811fc8:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  811fcf:	48 83 c6 10          	add    rsi,0x10
  811fd3:	e8 08 0e 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  811fd8:	48 8b 93 90 03 00 00 	mov    rdx,QWORD PTR [rbx+0x390]
  811fdf:	89 42 64             	mov    DWORD PTR [rdx+0x64],eax
  811fe2:	48 8b 83 98 04 00 00 	mov    rax,QWORD PTR [rbx+0x498]
  811fe9:	be 66 00 00 00       	mov    esi,0x66
  811fee:	48 89 c7             	mov    rdi,rax
  811ff1:	e8 aa 42 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  811ff6:	84 c0                	test   al,al
  811ff8:	0f 85 02 fe ff ff    	jne    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  811ffe:	48 83 bb 98 06 00 00 00 	cmp    QWORD PTR [rbx+0x698],0x0
  812006:	0f 84 ac 01 00 00    	je     8121b8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x5f8>
  81200c:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  812013:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  812016:	ff 90 e0 01 00 00    	call   QWORD PTR [rax+0x1e0]
  81201c:	48 8b bb 98 06 00 00 	mov    rdi,QWORD PTR [rbx+0x698]
  812023:	48 8b 70 60          	mov    rsi,QWORD PTR [rax+0x60]
  812027:	e8 44 7f 23 00       	call   a49f70 <CWeaponTrail::setWeaponEntity(Ogre::Entity*)>
  81202c:	e9 cf fd ff ff       	jmp    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  812031:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  812038:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  81203f:	48 85 ff             	test   rdi,rdi
  812042:	0f 84 e8 fd ff ff    	je     811e30 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x270>
  812048:	be 01 00 00 00       	mov    esi,0x1
  81204d:	e8 0e 94 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  812052:	48 85 c0             	test   rax,rax
  812055:	0f 84 d5 fd ff ff    	je     811e30 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x270>
  81205b:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  812062:	be 01 00 00 00       	mov    esi,0x1
  812067:	e8 f4 93 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  81206c:	be 08 00 00 00       	mov    esi,0x8
  812071:	48 89 c7             	mov    rdi,rax
  812074:	e8 27 42 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  812079:	84 c0                	test   al,al
  81207b:	0f 84 af fd ff ff    	je     811e30 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x270>
  812081:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  812088:	be 01 00 00 00       	mov    esi,0x1
  81208d:	e8 ce 93 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  812092:	48 89 83 98 04 00 00 	mov    QWORD PTR [rbx+0x498],rax
  812099:	48 8b b0 a8 02 00 00 	mov    rsi,QWORD PTR [rax+0x2a8]
  8120a0:	48 89 c7             	mov    rdi,rax
  8120a3:	48 85 f6             	test   rsi,rsi
  8120a6:	48 89 b3 90 03 00 00 	mov    QWORD PTR [rbx+0x390],rsi
  8120ad:	74 21                	je     8120d0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x510>
  8120af:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8120b6:	48 83 c6 10          	add    rsi,0x10
  8120ba:	e8 21 0d 09 00       	call   8a2de0 <CGenericModel::findRandomAnimation(std::string const&)>
  8120bf:	48 8b 93 90 03 00 00 	mov    rdx,QWORD PTR [rbx+0x390]
  8120c6:	89 42 64             	mov    DWORD PTR [rdx+0x64],eax
  8120c9:	48 8b bb 98 04 00 00 	mov    rdi,QWORD PTR [rbx+0x498]
  8120d0:	be 66 00 00 00       	mov    esi,0x66
  8120d5:	e8 c6 41 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8120da:	84 c0                	test   al,al
  8120dc:	0f 85 1e fd ff ff    	jne    811e00 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x240>
  8120e2:	48 83 bb a0 06 00 00 00 	cmp    QWORD PTR [rbx+0x6a0],0x0
  8120ea:	0f 85 f0 fc ff ff    	jne    811de0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x220>
  8120f0:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  8120f4:	45 31 f6             	xor    r14d,r14d
  8120f7:	48 85 c0             	test   rax,rax
  8120fa:	74 04                	je     812100 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x540>
  8120fc:	4c 8b 70 10          	mov    r14,QWORD PTR [rax+0x10]
  812100:	4c 8d 64 24 50       	lea    r12,[rsp+0x50]
  812105:	48 8d 94 24 bb 00 00 00 	lea    rdx,[rsp+0xbb]
  81210d:	be 08 99 fc 00       	mov    esi,0xfc9908
  812112:	4c 89 e7             	mov    rdi,r12
  812115:	e8 de 41 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  81211a:	48 8d 6c 24 40       	lea    rbp,[rsp+0x40]
  81211f:	4c 89 e6             	mov    rsi,r12
  812122:	48 89 ef             	mov    rdi,rbp
  812125:	e8 26 c9 47 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  81212a:	bf a0 00 00 00       	mov    edi,0xa0
  81212f:	e8 8c 8b 04 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  812134:	f3 0f 10 05 c0 26 79 00 	movss  xmm0,DWORD PTR [rip+0x7926c0]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  81213c:	b9 14 00 00 00       	mov    ecx,0x14
  812141:	48 89 ea             	mov    rdx,rbp
  812144:	4c 89 f6             	mov    rsi,r14
  812147:	48 89 c7             	mov    rdi,rax
  81214a:	49 89 c5             	mov    r13,rax
  81214d:	e8 ce a9 23 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  812152:	4c 89 ab a0 06 00 00 	mov    QWORD PTR [rbx+0x6a0],r13
  812159:	48 89 ef             	mov    rdi,rbp
  81215c:	e8 27 41 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  812161:	4c 89 e7             	mov    rdi,r12
  812164:	e8 1f 41 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  812169:	48 89 df             	mov    rdi,rbx
  81216c:	e8 ff df ff ff       	call   810170 <CCharacter::alignment()>
  812171:	48 8d 6c 24 30       	lea    rbp,[rsp+0x30]
  812176:	83 f8 01             	cmp    eax,0x1
  812179:	be 34 05 fa 00       	mov    esi,0xfa0534
  81217e:	b8 40 05 fa 00       	mov    eax,0xfa0540
  812183:	48 8d 94 24 ba 00 00 00 	lea    rdx,[rsp+0xba]
  81218b:	48 0f 45 f0          	cmovne rsi,rax
  81218f:	48 89 ef             	mov    rdi,rbp
  812192:	e8 61 41 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  812197:	48 8b bb a0 06 00 00 	mov    rdi,QWORD PTR [rbx+0x6a0]
  81219e:	48 89 ee             	mov    rsi,rbp
  8121a1:	e8 ea 7e 23 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  8121a6:	48 89 ef             	mov    rdi,rbp
  8121a9:	e8 da 40 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8121ae:	e9 2d fc ff ff       	jmp    811de0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x220>
  8121b3:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8121b8:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  8121bc:	45 31 f6             	xor    r14d,r14d
  8121bf:	48 85 c0             	test   rax,rax
  8121c2:	74 04                	je     8121c8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x608>
  8121c4:	4c 8b 70 10          	mov    r14,QWORD PTR [rax+0x10]
  8121c8:	4c 8d a4 24 80 00 00 00 	lea    r12,[rsp+0x80]
  8121d0:	48 8d 94 24 bd 00 00 00 	lea    rdx,[rsp+0xbd]
  8121d8:	be 08 99 fc 00       	mov    esi,0xfc9908
  8121dd:	4c 89 e7             	mov    rdi,r12
  8121e0:	e8 13 41 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8121e5:	48 8d 6c 24 70       	lea    rbp,[rsp+0x70]
  8121ea:	4c 89 e6             	mov    rsi,r12
  8121ed:	48 89 ef             	mov    rdi,rbp
  8121f0:	e8 5b c8 47 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  8121f5:	bf a0 00 00 00       	mov    edi,0xa0
  8121fa:	e8 c1 8a 04 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  8121ff:	f3 0f 10 05 f5 25 79 00 	movss  xmm0,DWORD PTR [rip+0x7925f5]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  812207:	b9 14 00 00 00       	mov    ecx,0x14
  81220c:	48 89 ea             	mov    rdx,rbp
  81220f:	4c 89 f6             	mov    rsi,r14
  812212:	48 89 c7             	mov    rdi,rax
  812215:	49 89 c5             	mov    r13,rax
  812218:	e8 03 a9 23 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  81221d:	4c 89 ab 98 06 00 00 	mov    QWORD PTR [rbx+0x698],r13
  812224:	48 89 ef             	mov    rdi,rbp
  812227:	e8 5c 40 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  81222c:	4c 89 e7             	mov    rdi,r12
  81222f:	e8 54 40 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  812234:	48 89 df             	mov    rdi,rbx
  812237:	e8 34 df ff ff       	call   810170 <CCharacter::alignment()>
  81223c:	48 8d 6c 24 60       	lea    rbp,[rsp+0x60]
  812241:	83 f8 01             	cmp    eax,0x1
  812244:	be 34 05 fa 00       	mov    esi,0xfa0534
  812249:	b8 40 05 fa 00       	mov    eax,0xfa0540
  81224e:	48 8d 94 24 bc 00 00 00 	lea    rdx,[rsp+0xbc]
  812256:	48 0f 45 f0          	cmovne rsi,rax
  81225a:	48 89 ef             	mov    rdi,rbp
  81225d:	e8 96 40 d4 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  812262:	48 8b bb 98 06 00 00 	mov    rdi,QWORD PTR [rbx+0x698]
  812269:	48 89 ee             	mov    rsi,rbp
  81226c:	e8 1f 7e 23 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  812271:	48 89 ef             	mov    rdi,rbp
  812274:	e8 0f 40 d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  812279:	e9 8e fd ff ff       	jmp    81200c <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x44c>
  81227e:	48 8b bb 90 04 00 00 	mov    rdi,QWORD PTR [rbx+0x490]
  812285:	be 01 00 00 00       	mov    esi,0x1
  81228a:	e8 d1 91 10 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  81228f:	be 23 00 00 00       	mov    esi,0x23
  812294:	48 89 c7             	mov    rdi,rax
  812297:	e8 04 40 fe ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  81229c:	84 c0                	test   al,al
  81229e:	0f 85 ee f9 ff ff    	jne    811c92 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0xd2>
  8122a4:	e9 f7 fc ff ff       	jmp    811fa0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x3e0>
  8122a9:	48 8b b3 90 03 00 00 	mov    rsi,QWORD PTR [rbx+0x390]
  8122b0:	e9 15 fa ff ff       	jmp    811cca <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x10a>
  8122b5:	4c 89 ef             	mov    rdi,r13
  8122b8:	48 89 c3             	mov    rbx,rax
  8122bb:	e8 a8 2f d4 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  8122c0:	48 89 ef             	mov    rdi,rbp
  8122c3:	e8 c0 3f d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8122c8:	4c 89 e7             	mov    rdi,r12
  8122cb:	e8 b8 3f d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8122d0:	48 89 df             	mov    rdi,rbx
  8122d3:	e8 c0 21 d4 ff       	call   554498 <_Unwind_Resume@plt>
  8122d8:	48 89 c3             	mov    rbx,rax
  8122db:	eb e3                	jmp    8122c0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x700>
  8122dd:	48 89 c3             	mov    rbx,rax
  8122e0:	eb e6                	jmp    8122c8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x708>
  8122e2:	48 89 c3             	mov    rbx,rax
  8122e5:	eb e9                	jmp    8122d0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x710>
  8122e7:	eb cc                	jmp    8122b5 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x6f5>
  8122e9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  8122f0:	eb e6                	jmp    8122d8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x718>
  8122f2:	eb e9                	jmp    8122dd <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x71d>
  8122f4:	eb ec                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  8122f6:	48 89 ef             	mov    rdi,rbp
  8122f9:	48 89 c3             	mov    rbx,rax
  8122fc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  812300:	e8 83 3f d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  812305:	eb c9                	jmp    8122d0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x710>
  812307:	eb d9                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812309:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  812310:	eb e4                	jmp    8122f6 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x736>
  812312:	eb ce                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812314:	eb 9f                	jmp    8122b5 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x6f5>
  812316:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  812320:	eb b6                	jmp    8122d8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x718>
  812322:	eb b9                	jmp    8122dd <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x71d>
  812324:	eb bc                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812326:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  812330:	eb c4                	jmp    8122f6 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x736>
  812332:	eb ae                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812334:	48 89 e7             	mov    rdi,rsp
  812337:	48 89 c3             	mov    rbx,rax
  81233a:	e8 49 3f d4 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  81233f:	90                   	nop
  812340:	eb 8e                	jmp    8122d0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x710>
  812342:	eb 9e                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812344:	e9 6c ff ff ff       	jmp    8122b5 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x6f5>
  812349:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  812350:	eb 86                	jmp    8122d8 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x718>
  812352:	eb 89                	jmp    8122dd <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x71d>
  812354:	eb 8c                	jmp    8122e2 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)+0x722>
  812356:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]

