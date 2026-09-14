
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000848870 <CCharacter::updateAnimation(float)>:
  848870:	41 57                	push   %r15
  848872:	41 56                	push   %r14
  848874:	41 55                	push   %r13
  848876:	41 54                	push   %r12
  848878:	55                   	push   %rbp
  848879:	53                   	push   %rbx
  84887a:	48 89 fb             	mov    %rdi,%rbx
  84887d:	48 81 ec 48 04 00 00 	sub    $0x448,%rsp
  848884:	f3 0f 11 44 24 60    	movss  %xmm0,0x60(%rsp)
  84888a:	48 8b bf 08 02 00 00 	mov    0x208(%rdi),%rdi
  848891:	48 85 ff             	test   %rdi,%rdi
  848894:	74 07                	je     84889d <CCharacter::updateAnimation(float)+0x2d>
  848896:	31 f6                	xor    %esi,%esi
  848898:	e8 13 1c 06 00       	call   8aa4b0 <CGenericModel::updateAnimation(float, bool)>
  84889d:	48 83 bb 00 02 00 00 	cmpq   $0x0,0x200(%rbx)
  8488a4:	00
  8488a5:	0f 84 0d 01 00 00    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  8488ab:	80 bb 99 01 00 00 00 	cmpb   $0x0,0x199(%rbx)
  8488b2:	0f 84 18 01 00 00    	je     8489d0 <CCharacter::updateAnimation(float)+0x160>
  8488b8:	48 89 df             	mov    %rbx,%rdi
  8488bb:	e8 40 76 fb ff       	call   7fff00 <CBaseUnit::updateCullingBounds()>
  8488c0:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  8488c7:	31 f6                	xor    %esi,%esi
  8488c9:	e8 b2 e7 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8488ce:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  8488d4:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  8488d9:	be 01 00 00 00       	mov    $0x1,%esi
  8488de:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  8488e5:	00 00
  8488e7:	48 89 df             	mov    %rbx,%rdi
  8488ea:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  8488f1:	00
  8488f2:	48 89 84 24 50 01 00 	mov    %rax,0x150(%rsp)
  8488f9:	00
  8488fa:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  848901:	89 84 24 58 01 00 00 	mov    %eax,0x158(%rsp)
  848908:	e8 73 e7 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  84890d:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  848913:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  848918:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  84891f:	00 00
  848921:	48 89 84 24 60 01 00 	mov    %rax,0x160(%rsp)
  848928:	00
  848929:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  848930:	00
  848931:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  848938:	f3 0f 10 8c 24 64 01 	movss  0x164(%rsp),%xmm1
  84893f:	00 00
  848941:	f3 0f 10 94 24 60 01 	movss  0x160(%rsp),%xmm2
  848948:	00 00
  84894a:	f3 0f 58 8c 24 54 01 	addss  0x154(%rsp),%xmm1
  848951:	00 00
  848953:	89 84 24 68 01 00 00 	mov    %eax,0x168(%rsp)
  84895a:	f3 0f 58 94 24 50 01 	addss  0x150(%rsp),%xmm2
  848961:	00 00
  848963:	f3 0f 10 84 24 68 01 	movss  0x168(%rsp),%xmm0
  84896a:	00 00
  84896c:	8b 83 30 03 00 00    	mov    0x330(%rbx),%eax
  848972:	f3 0f 58 84 24 58 01 	addss  0x158(%rsp),%xmm0
  848979:	00 00
  84897b:	83 f8 0c             	cmp    $0xc,%eax
  84897e:	f3 0f 11 8b 14 02 00 	movss  %xmm1,0x214(%rbx)
  848985:	00
  848986:	f3 0f 11 93 10 02 00 	movss  %xmm2,0x210(%rbx)
  84898d:	00
  84898e:	f3 0f 11 83 18 02 00 	movss  %xmm0,0x218(%rbx)
  848995:	00
  848996:	74 58                	je     8489f0 <CCharacter::updateAnimation(float)+0x180>
  848998:	83 f8 05             	cmp    $0x5,%eax
  84899b:	74 53                	je     8489f0 <CCharacter::updateAnimation(float)+0x180>
  84899d:	80 bb 81 00 00 00 00 	cmpb   $0x0,0x81(%rbx)
  8489a4:	75 4a                	jne    8489f0 <CCharacter::updateAnimation(float)+0x180>
  8489a6:	80 bb 0d 07 00 00 00 	cmpb   $0x0,0x70d(%rbx)
  8489ad:	0f 85 5a 10 00 00    	jne    849a0d <CCharacter::updateAnimation(float)+0x119d>
  8489b3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8489b8:	48 81 c4 48 04 00 00 	add    $0x448,%rsp
  8489bf:	5b                   	pop    %rbx
  8489c0:	5d                   	pop    %rbp
  8489c1:	41 5c                	pop    %r12
  8489c3:	41 5d                	pop    %r13
  8489c5:	41 5e                	pop    %r14
  8489c7:	41 5f                	pop    %r15
  8489c9:	c3                   	ret
  8489ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8489d0:	48 8b 03             	mov    (%rbx),%rax
  8489d3:	31 f6                	xor    %esi,%esi
  8489d5:	48 89 df             	mov    %rbx,%rdi
  8489d8:	ff 50 50             	call   *0x50(%rax)
  8489db:	8b 83 30 03 00 00    	mov    0x330(%rbx),%eax
  8489e1:	83 f8 0c             	cmp    $0xc,%eax
  8489e4:	75 b2                	jne    848998 <CCharacter::updateAnimation(float)+0x128>
  8489e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  8489ed:	00 00 00
  8489f0:	48 89 df             	mov    %rbx,%rdi
  8489f3:	e8 e8 d5 fa ff       	call   7f5fe0 <CBaseUnit::getCastsShadows()>
  8489f8:	84 c0                	test   %al,%al
  8489fa:	74 0d                	je     848a09 <CCharacter::updateAnimation(float)+0x199>
  8489fc:	80 bb 99 01 00 00 00 	cmpb   $0x0,0x199(%rbx)
  848a03:	0f 85 4c 0f 00 00    	jne    849955 <CCharacter::updateAnimation(float)+0x10e5>
  848a09:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  848a10:	48 85 ff             	test   %rdi,%rdi
  848a13:	74 0d                	je     848a22 <CCharacter::updateAnimation(float)+0x1b2>
  848a15:	31 f6                	xor    %esi,%esi
  848a17:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848a1d:	e8 8e 1a 06 00       	call   8aa4b0 <CGenericModel::updateAnimation(float, bool)>
  848a22:	48 89 df             	mov    %rbx,%rdi
  848a25:	e8 86 a5 fd ff       	call   822fb0 <CCharacter::updateBonePositions()>
  848a2a:	48 8b 43 68          	mov    0x68(%rbx),%rax
  848a2e:	31 f6                	xor    %esi,%esi
  848a30:	48 85 c0             	test   %rax,%rax
  848a33:	74 04                	je     848a39 <CCharacter::updateAnimation(float)+0x1c9>
  848a35:	48 8b 70 18          	mov    0x18(%rax),%rsi
  848a39:	48 89 df             	mov    %rbx,%rdi
  848a3c:	e8 4f fd ff ff       	call   848790 <CCharacter::updateAttack(CLevel&)>
  848a41:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848a47:	48 89 df             	mov    %rbx,%rdi
  848a4a:	e8 01 8c fc ff       	call   811650 <CCharacter::updateSkillKeys(float)>
  848a4f:	48 89 df             	mov    %rbx,%rdi
  848a52:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848a58:	e8 93 90 fc ff       	call   811af0 <CCharacter::updateSkill(float)>
  848a5d:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  848a64:	48 85 ff             	test   %rdi,%rdi
  848a67:	74 14                	je     848a7d <CCharacter::updateAnimation(float)+0x20d>
  848a69:	49 89 d8             	mov    %rbx,%r8
  848a6c:	31 c9                	xor    %ecx,%ecx
  848a6e:	31 d2                	xor    %edx,%edx
  848a70:	31 f6                	xor    %esi,%esi
  848a72:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848a78:	e8 f3 19 20 00       	call   a4a470 <CWeaponTrail::update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*)>
  848a7d:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  848a84:	48 85 ff             	test   %rdi,%rdi
  848a87:	74 14                	je     848a9d <CCharacter::updateAnimation(float)+0x22d>
  848a89:	49 89 d8             	mov    %rbx,%r8
  848a8c:	31 c9                	xor    %ecx,%ecx
  848a8e:	31 d2                	xor    %edx,%edx
  848a90:	31 f6                	xor    %esi,%esi
  848a92:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848a98:	e8 d3 19 20 00       	call   a4a470 <CWeaponTrail::update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*)>
  848a9d:	48 8b bb a8 06 00 00 	mov    0x6a8(%rbx),%rdi
  848aa4:	48 85 ff             	test   %rdi,%rdi
  848aa7:	74 14                	je     848abd <CCharacter::updateAnimation(float)+0x24d>
  848aa9:	45 31 c0             	xor    %r8d,%r8d
  848aac:	31 c9                	xor    %ecx,%ecx
  848aae:	31 d2                	xor    %edx,%edx
  848ab0:	31 f6                	xor    %esi,%esi
  848ab2:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848ab8:	e8 b3 19 20 00       	call   a4a470 <CWeaponTrail::update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*)>
  848abd:	0f 57 c9             	xorps  %xmm1,%xmm1
  848ac0:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  848ac6:	0f 2e c1             	ucomiss %xmm1,%xmm0
  848ac9:	7a 06                	jp     848ad1 <CCharacter::updateAnimation(float)+0x261>
  848acb:	0f 84 e7 fe ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  848ad1:	48 8b 03             	mov    (%rbx),%rax
  848ad4:	48 89 df             	mov    %rbx,%rdi
  848ad7:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  848add:	48 85 c0             	test   %rax,%rax
  848ae0:	0f 84 d2 fe ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  848ae6:	4c 8d bc 24 00 01 00 	lea    0x100(%rsp),%r15
  848aed:	00
  848aee:	45 31 e4             	xor    %r12d,%r12d
  848af1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  848af8:	48 8b 03             	mov    (%rbx),%rax
  848afb:	48 89 df             	mov    %rbx,%rdi
  848afe:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  848b04:	48 8b 90 b8 01 00 00 	mov    0x1b8(%rax),%rdx
  848b0b:	48 2b 90 b0 01 00 00 	sub    0x1b0(%rax),%rdx
  848b12:	48 c1 fa 03          	sar    $0x3,%rdx
  848b16:	41 39 d4             	cmp    %edx,%r12d
  848b19:	0f 83 41 12 00 00    	jae    849d60 <CCharacter::updateAnimation(float)+0x14f0>
  848b1f:	48 8b 03             	mov    (%rbx),%rax
  848b22:	48 89 df             	mov    %rbx,%rdi
  848b25:	44 89 e5             	mov    %r12d,%ebp
  848b28:	4c 8d 34 ed 00 00 00 	lea    0x0(,%rbp,8),%r14
  848b2f:	00
  848b30:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  848b36:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  848b3d:	4c 8b 2c e8          	mov    (%rax,%rbp,8),%r13
  848b41:	4d 85 ed             	test   %r13,%r13
  848b44:	0f 84 ee 00 00 00    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848b4a:	49 8b 75 40          	mov    0x40(%r13),%rsi
  848b4e:	48 85 f6             	test   %rsi,%rsi
  848b51:	74 10                	je     848b63 <CCharacter::updateAnimation(float)+0x2f3>
  848b53:	48 89 df             	mov    %rbx,%rdi
  848b56:	e8 e5 d3 fa ff       	call   7f5f40 <CBaseUnit::hasUnitTheme(CUnitTheme*)>
  848b5b:	84 c0                	test   %al,%al
  848b5d:	0f 84 d5 00 00 00    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848b63:	41 8b 45 58          	mov    0x58(%r13),%eax
  848b67:	83 e8 03             	sub    $0x3,%eax
  848b6a:	83 f8 18             	cmp    $0x18,%eax
  848b6d:	0f 87 c5 00 00 00    	ja     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848b73:	89 c0                	mov    %eax,%eax
  848b75:	ff 24 c5 78 dc fc 00 	jmp    *0xfcdc78(,%rax,8)
  848b7c:	0f 1f 40 00          	nopl   0x0(%rax)
  848b80:	48 83 bb e8 02 00 00 	cmpq   $0x0,0x2e8(%rbx)
  848b87:	00
  848b88:	c6 83 05 07 00 00 00 	movb   $0x0,0x705(%rbx)
  848b8f:	74 48                	je     848bd9 <CCharacter::updateAnimation(float)+0x369>
  848b91:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848b98:	31 f6                	xor    %esi,%esi
  848b9a:	e8 c1 28 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848b9f:	48 85 c0             	test   %rax,%rax
  848ba2:	74 1b                	je     848bbf <CCharacter::updateAnimation(float)+0x34f>
  848ba4:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848bab:	31 f6                	xor    %esi,%esi
  848bad:	e8 ae 28 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848bb2:	be 01 00 00 00       	mov    $0x1,%esi
  848bb7:	48 89 c7             	mov    %rax,%rdi
  848bba:	e8 21 62 02 00       	call   86ede0 <CEquipment::setElementalParticlesEnabled(bool)>
  848bbf:	48 8b bb e8 02 00 00 	mov    0x2e8(%rbx),%rdi
  848bc6:	ba 01 00 00 00       	mov    $0x1,%edx
  848bcb:	be 01 00 00 00       	mov    $0x1,%esi
  848bd0:	48 8b 07             	mov    (%rdi),%rax
  848bd3:	ff 90 78 03 00 00    	call   *0x378(%rax)
  848bd9:	48 83 bb f8 02 00 00 	cmpq   $0x0,0x2f8(%rbx)
  848be0:	00
  848be1:	74 55                	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848be3:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848bea:	be 01 00 00 00       	mov    $0x1,%esi
  848bef:	e8 6c 28 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848bf4:	48 85 c0             	test   %rax,%rax
  848bf7:	74 1e                	je     848c17 <CCharacter::updateAnimation(float)+0x3a7>
  848bf9:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848c00:	be 01 00 00 00       	mov    $0x1,%esi
  848c05:	e8 56 28 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848c0a:	be 01 00 00 00       	mov    $0x1,%esi
  848c0f:	48 89 c7             	mov    %rax,%rdi
  848c12:	e8 c9 61 02 00       	call   86ede0 <CEquipment::setElementalParticlesEnabled(bool)>
  848c17:	48 8b bb f8 02 00 00 	mov    0x2f8(%rbx),%rdi
  848c1e:	ba 01 00 00 00       	mov    $0x1,%edx
  848c23:	be 01 00 00 00       	mov    $0x1,%esi
  848c28:	48 8b 07             	mov    (%rdi),%rax
  848c2b:	ff 90 78 03 00 00    	call   *0x378(%rax)
  848c31:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  848c38:	41 83 c4 01          	add    $0x1,%r12d
  848c3c:	e9 b7 fe ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848c41:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  848c48:	48 83 bb a0 02 00 00 	cmpq   $0x0,0x2a0(%rbx)
  848c4f:	00
  848c50:	74 e6                	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848c52:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  848c59:	48 8b 87 b0 01 00 00 	mov    0x1b0(%rdi),%rax
  848c60:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  848c64:	8b 72 28             	mov    0x28(%rdx),%esi
  848c67:	e8 44 12 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  848c6c:	44 8b 70 08          	mov    0x8(%rax),%r14d
  848c70:	45 85 f6             	test   %r14d,%r14d
  848c73:	74 c3                	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848c75:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  848c7c:	41 83 c4 01          	add    $0x1,%r12d
  848c80:	48 8b 87 b0 01 00 00 	mov    0x1b0(%rdi),%rax
  848c87:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  848c8b:	8b 72 28             	mov    0x28(%rdx),%esi
  848c8e:	e8 1d 12 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  848c93:	48 8b 00             	mov    (%rax),%rax
  848c96:	0f 57 c9             	xorps  %xmm1,%xmm1
  848c99:	48 8b bb a0 02 00 00 	mov    0x2a0(%rbx),%rdi
  848ca0:	31 c9                	xor    %ecx,%ecx
  848ca2:	31 d2                	xor    %edx,%edx
  848ca4:	8b 30                	mov    (%rax),%esi
  848ca6:	0f 28 c1             	movaps %xmm1,%xmm0
  848ca9:	e8 f2 0b 22 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  848cae:	e9 45 fe ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848cb3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  848cb8:	c6 83 0d 07 00 00 00 	movb   $0x0,0x70d(%rbx)
  848cbf:	31 d2                	xor    %edx,%edx
  848cc1:	be 01 00 00 00       	mov    $0x1,%esi
  848cc6:	48 89 df             	mov    %rbx,%rdi
  848cc9:	41 83 c4 01          	add    $0x1,%r12d
  848ccd:	e8 7e 9c fc ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  848cd2:	e9 21 fe ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848cd7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  848cde:	00 00
  848ce0:	31 d2                	xor    %edx,%edx
  848ce2:	31 f6                	xor    %esi,%esi
  848ce4:	48 89 df             	mov    %rbx,%rdi
  848ce7:	e8 64 9c fc ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  848cec:	41 83 c4 01          	add    $0x1,%r12d
  848cf0:	c6 83 0d 07 00 00 01 	movb   $0x1,0x70d(%rbx)
  848cf7:	e9 fc fd ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848cfc:	0f 1f 40 00          	nopl   0x0(%rax)
  848d00:	c6 83 0d 07 00 00 00 	movb   $0x0,0x70d(%rbx)
  848d07:	ba 01 00 00 00       	mov    $0x1,%edx
  848d0c:	be 01 00 00 00       	mov    $0x1,%esi
  848d11:	48 89 df             	mov    %rbx,%rdi
  848d14:	41 83 c4 01          	add    $0x1,%r12d
  848d18:	e8 33 9c fc ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  848d1d:	e9 d6 fd ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848d22:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  848d28:	ba 01 00 00 00       	mov    $0x1,%edx
  848d2d:	31 f6                	xor    %esi,%esi
  848d2f:	48 89 df             	mov    %rbx,%rdi
  848d32:	e8 19 9c fc ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  848d37:	41 83 c4 01          	add    $0x1,%r12d
  848d3b:	c6 83 0d 07 00 00 01 	movb   $0x1,0x70d(%rbx)
  848d42:	e9 b1 fd ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848d47:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  848d4e:	00 00
  848d50:	48 8b bb e8 02 00 00 	mov    0x2e8(%rbx),%rdi
  848d57:	c6 83 05 07 00 00 01 	movb   $0x1,0x705(%rbx)
  848d5e:	48 85 ff             	test   %rdi,%rdi
  848d61:	74 3b                	je     848d9e <CCharacter::updateAnimation(float)+0x52e>
  848d63:	48 8b 07             	mov    (%rdi),%rax
  848d66:	31 f6                	xor    %esi,%esi
  848d68:	ba 01 00 00 00       	mov    $0x1,%edx
  848d6d:	ff 90 78 03 00 00    	call   *0x378(%rax)
  848d73:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848d7a:	31 f6                	xor    %esi,%esi
  848d7c:	e8 df 26 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848d81:	48 85 c0             	test   %rax,%rax
  848d84:	74 18                	je     848d9e <CCharacter::updateAnimation(float)+0x52e>
  848d86:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848d8d:	31 f6                	xor    %esi,%esi
  848d8f:	e8 cc 26 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848d94:	31 f6                	xor    %esi,%esi
  848d96:	48 89 c7             	mov    %rax,%rdi
  848d99:	e8 42 60 02 00       	call   86ede0 <CEquipment::setElementalParticlesEnabled(bool)>
  848d9e:	48 8b bb f8 02 00 00 	mov    0x2f8(%rbx),%rdi
  848da5:	48 85 ff             	test   %rdi,%rdi
  848da8:	0f 84 8a fe ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848dae:	48 8b 07             	mov    (%rdi),%rax
  848db1:	31 f6                	xor    %esi,%esi
  848db3:	ba 01 00 00 00       	mov    $0x1,%edx
  848db8:	ff 90 78 03 00 00    	call   *0x378(%rax)
  848dbe:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848dc5:	be 01 00 00 00       	mov    $0x1,%esi
  848dca:	e8 91 26 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848dcf:	48 85 c0             	test   %rax,%rax
  848dd2:	0f 84 60 fe ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848dd8:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  848ddf:	be 01 00 00 00       	mov    $0x1,%esi
  848de4:	41 83 c4 01          	add    $0x1,%r12d
  848de8:	e8 73 26 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  848ded:	31 f6                	xor    %esi,%esi
  848def:	48 89 c7             	mov    %rax,%rdi
  848df2:	e8 e9 5f 02 00       	call   86ede0 <CEquipment::setElementalParticlesEnabled(bool)>
  848df7:	e9 fc fc ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848dfc:	0f 1f 40 00          	nopl   0x0(%rax)
  848e00:	c7 83 58 02 00 00 00 	movl   $0x3f800000,0x258(%rbx)
  848e07:	00 80 3f
  848e0a:	41 83 c4 01          	add    $0x1,%r12d
  848e0e:	e9 e5 fc ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848e13:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  848e18:	0f 57 c0             	xorps  %xmm0,%xmm0
  848e1b:	c7 83 58 02 00 00 00 	movl   $0x0,0x258(%rbx)
  848e22:	00 00 00
  848e25:	41 83 c4 01          	add    $0x1,%r12d
  848e29:	f3 0f 59 83 4c 02 00 	mulss  0x24c(%rbx),%xmm0
  848e30:	00
  848e31:	f3 0f 11 83 4c 02 00 	movss  %xmm0,0x24c(%rbx)
  848e38:	00
  848e39:	0f 57 c0             	xorps  %xmm0,%xmm0
  848e3c:	f3 0f 59 83 50 02 00 	mulss  0x250(%rbx),%xmm0
  848e43:	00
  848e44:	f3 0f 11 83 50 02 00 	movss  %xmm0,0x250(%rbx)
  848e4b:	00
  848e4c:	0f 57 c0             	xorps  %xmm0,%xmm0
  848e4f:	f3 0f 59 83 54 02 00 	mulss  0x254(%rbx),%xmm0
  848e56:	00
  848e57:	f3 0f 11 83 54 02 00 	movss  %xmm0,0x254(%rbx)
  848e5e:	00
  848e5f:	e9 94 fc ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848e64:	0f 1f 40 00          	nopl   0x0(%rax)
  848e68:	c6 83 31 05 00 00 01 	movb   $0x1,0x531(%rbx)
  848e6f:	41 83 c4 01          	add    $0x1,%r12d
  848e73:	e9 80 fc ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848e78:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  848e7f:	00
  848e80:	c6 83 31 05 00 00 00 	movb   $0x0,0x531(%rbx)
  848e87:	41 83 c4 01          	add    $0x1,%r12d
  848e8b:	e9 68 fc ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  848e90:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  848e97:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  848e9e:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  848ea2:	48 83 78 50 00       	cmpq   $0x0,0x50(%rax)
  848ea7:	0f 84 8b fd ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  848ead:	48 8b 53 68          	mov    0x68(%rbx),%rdx
  848eb1:	31 c0                	xor    %eax,%eax
  848eb3:	48 85 d2             	test   %rdx,%rdx
  848eb6:	74 04                	je     848ebc <CCharacter::updateAnimation(float)+0x64c>
  848eb8:	48 8b 42 18          	mov    0x18(%rdx),%rax
  848ebc:	be 01 00 00 00       	mov    $0x1,%esi
  848ec1:	48 89 df             	mov    %rbx,%rdi
  848ec4:	4c 8b a8 20 02 00 00 	mov    0x220(%rax),%r13
  848ecb:	e8 b0 e1 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  848ed0:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  848ed6:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  848edb:	48 89 df             	mov    %rbx,%rdi
  848ede:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  848ee5:	00 00
  848ee7:	0f 57 db             	xorps  %xmm3,%xmm3
  848eea:	48 89 84 24 40 01 00 	mov    %rax,0x140(%rsp)
  848ef1:	00
  848ef2:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  848ef9:	00
  848efa:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  848f01:	f3 0f 10 94 24 44 01 	movss  0x144(%rsp),%xmm2
  848f08:	00 00
  848f0a:	f3 0f 10 84 24 40 01 	movss  0x140(%rsp),%xmm0
  848f11:	00 00
  848f13:	89 84 24 48 01 00 00 	mov    %eax,0x148(%rsp)
  848f1a:	48 8b 03             	mov    (%rbx),%rax
  848f1d:	f3 41 0f 5c 95 c4 02 	subss  0x2c4(%r13),%xmm2
  848f24:	00 00
  848f26:	f3 0f 10 8c 24 48 01 	movss  0x148(%rsp),%xmm1
  848f2d:	00 00
  848f2f:	f3 41 0f 5c 85 c0 02 	subss  0x2c0(%r13),%xmm0
  848f36:	00 00
  848f38:	f3 41 0f 5c 8d c8 02 	subss  0x2c8(%r13),%xmm1
  848f3f:	00 00
  848f41:	f3 0f 59 d2          	mulss  %xmm2,%xmm2
  848f45:	f3 0f 59 c0          	mulss  %xmm0,%xmm0
  848f49:	f3 0f 59 c9          	mulss  %xmm1,%xmm1
  848f4d:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  848f51:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  848f55:	0f 57 c9             	xorps  %xmm1,%xmm1
  848f58:	f3 0f 51 c0          	sqrtss %xmm0,%xmm0
  848f5c:	f3 0f 5e 05 d4 55 78 	divss  0x7855d4(%rip),%xmm0        # fce538 <vtable for iInventoryListener+0xf8>
  848f63:	00
  848f64:	f3 0f 58 05 90 b8 75 	addss  0x75b890(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  848f6b:	00
  848f6c:	f3 0f 58 05 98 b8 75 	addss  0x75b898(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  848f73:	00
  848f74:	f3 0f c2 c8 01       	cmpltss %xmm0,%xmm1
  848f79:	0f 28 d0             	movaps %xmm0,%xmm2
  848f7c:	0f 28 c1             	movaps %xmm1,%xmm0
  848f7f:	0f 54 d1             	andps  %xmm1,%xmm2
  848f82:	0f 55 c3             	andnps %xmm3,%xmm0
  848f85:	0f 56 c2             	orps   %xmm2,%xmm0
  848f88:	f3 0f 11 44 24 40    	movss  %xmm0,0x40(%rsp)
  848f8e:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  848f94:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  848f9b:	f3 0f 10 44 24 40    	movss  0x40(%rsp),%xmm0
  848fa1:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  848fa5:	83 78 58 1a          	cmpl   $0x1a,0x58(%rax)
  848fa9:	0f 84 f2 10 00 00    	je     84a0a1 <CCharacter::updateAnimation(float)+0x1831>
  848faf:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  848fb6:	be 01 00 00 00       	mov    $0x1,%esi
  848fbb:	48 89 df             	mov    %rbx,%rdi
  848fbe:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  848fc5:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  848fc9:	48 8b 40 50          	mov    0x50(%rax),%rax
  848fcd:	f3 0f 11 40 60       	movss  %xmm0,0x60(%rax)
  848fd2:	e8 a9 e0 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  848fd7:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  848fdd:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  848fe2:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  848fe9:	00 00
  848feb:	48 89 84 24 30 01 00 	mov    %rax,0x130(%rsp)
  848ff2:	00
  848ff3:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  848ffa:	00
  848ffb:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  849002:	8b 94 24 30 01 00 00 	mov    0x130(%rsp),%edx
  849009:	89 84 24 38 01 00 00 	mov    %eax,0x138(%rsp)
  849010:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  849017:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84901e:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  849022:	48 8b 40 50          	mov    0x50(%rax),%rax
  849026:	89 90 8c 00 00 00    	mov    %edx,0x8c(%rax)
  84902c:	8b 94 24 34 01 00 00 	mov    0x134(%rsp),%edx
  849033:	89 90 90 00 00 00    	mov    %edx,0x90(%rax)
  849039:	8b 94 24 38 01 00 00 	mov    0x138(%rsp),%edx
  849040:	c6 80 98 00 00 00 01 	movb   $0x1,0x98(%rax)
  849047:	89 90 94 00 00 00    	mov    %edx,0x94(%rax)
  84904d:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  849054:	48 8b 7b 68          	mov    0x68(%rbx),%rdi
  849058:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84905f:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  849063:	4c 8b 70 50          	mov    0x50(%rax),%r14
  849067:	e8 f4 66 52 00       	call   d6f760 <CResourceManager::getCameraControl()>
  84906c:	31 c9                	xor    %ecx,%ecx
  84906e:	31 d2                	xor    %edx,%edx
  849070:	31 f6                	xor    %esi,%esi
  849072:	bf 10 00 00 00       	mov    $0x10,%edi
  849077:	48 89 c5             	mov    %rax,%rbp
  84907a:	e8 99 a2 d0 ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  84907f:	4d 85 f6             	test   %r14,%r14
  849082:	49 89 c5             	mov    %rax,%r13
  849085:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  84908c:	c7 40 08 ff ff ff ff 	movl   $0xffffffff,0x8(%rax)
  849093:	74 13                	je     8490a8 <CCharacter::updateAnimation(float)+0x838>
  849095:	48 89 c6             	mov    %rax,%rsi
  849098:	4c 89 f7             	mov    %r14,%rdi
  84909b:	e8 20 07 53 00       	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  8490a0:	41 89 45 08          	mov    %eax,0x8(%r13)
  8490a4:	4d 89 75 00          	mov    %r14,0x0(%r13)
  8490a8:	8b 55 78             	mov    0x78(%rbp),%edx
  8490ab:	8b 45 7c             	mov    0x7c(%rbp),%eax
  8490ae:	4c 8d 75 70          	lea    0x70(%rbp),%r14
  8490b2:	39 c2                	cmp    %eax,%edx
  8490b4:	0f 82 e8 0e 00 00    	jb     849fa2 <CCharacter::updateAnimation(float)+0x1732>
  8490ba:	48 83 7d 70 00       	cmpq   $0x0,0x70(%rbp)
  8490bf:	0f 84 1e 19 00 00    	je     84a9e3 <CCharacter::updateAnimation(float)+0x2173>
  8490c5:	03 85 80 00 00 00    	add    0x80(%rbp),%eax
  8490cb:	89 c7                	mov    %eax,%edi
  8490cd:	89 44 24 60          	mov    %eax,0x60(%rsp)
  8490d1:	48 c1 e7 03          	shl    $0x3,%rdi
  8490d5:	e8 0e aa d0 ff       	call   553ae8 <operator new[](unsigned long)@plt>
  8490da:	8b 55 7c             	mov    0x7c(%rbp),%edx
  8490dd:	85 d2                	test   %edx,%edx
  8490df:	74 1d                	je     8490fe <CCharacter::updateAnimation(float)+0x88e>
  8490e1:	31 d2                	xor    %edx,%edx
  8490e3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8490e8:	49 8b 36             	mov    (%r14),%rsi
  8490eb:	89 d1                	mov    %edx,%ecx
  8490ed:	83 c2 01             	add    $0x1,%edx
  8490f0:	48 8b 34 ce          	mov    (%rsi,%rcx,8),%rsi
  8490f4:	48 89 34 c8          	mov    %rsi,(%rax,%rcx,8)
  8490f8:	41 3b 56 0c          	cmp    0xc(%r14),%edx
  8490fc:	72 ea                	jb     8490e8 <CCharacter::updateAnimation(float)+0x878>
  8490fe:	48 8b 7d 70          	mov    0x70(%rbp),%rdi
  849102:	48 85 ff             	test   %rdi,%rdi
  849105:	74 0f                	je     849116 <CCharacter::updateAnimation(float)+0x8a6>
  849107:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  84910c:	e8 27 a5 d0 ff       	call   553638 <operator delete[](void*)@plt>
  849111:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
  849116:	48 89 45 70          	mov    %rax,0x70(%rbp)
  84911a:	8b 54 24 60          	mov    0x60(%rsp),%edx
  84911e:	89 55 7c             	mov    %edx,0x7c(%rbp)
  849121:	8b 55 78             	mov    0x78(%rbp),%edx
  849124:	89 d2                	mov    %edx,%edx
  849126:	41 83 c4 01          	add    $0x1,%r12d
  84912a:	4c 89 2c d0          	mov    %r13,(%rax,%rdx,8)
  84912e:	83 45 78 01          	addl   $0x1,0x78(%rbp)
  849132:	e9 c1 f9 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  849137:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  84913e:	00 00
  849140:	8b 8b 40 07 00 00    	mov    0x740(%rbx),%ecx
  849146:	31 ed                	xor    %ebp,%ebp
  849148:	85 c9                	test   %ecx,%ecx
  84914a:	75 43                	jne    84918f <CCharacter::updateAnimation(float)+0x91f>
  84914c:	e9 e7 fa ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849151:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  849158:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  84915f:	48 8b 08             	mov    (%rax),%rcx
  849162:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  849169:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  849170:	8b 49 24             	mov    0x24(%rcx),%ecx
  849173:	4a 8b 04 30          	mov    (%rax,%r14,1),%rax
  849177:	3b 48 28             	cmp    0x28(%rax),%ecx
  84917a:	0f 84 a8 08 00 00    	je     849a28 <CCharacter::updateAnimation(float)+0x11b8>
  849180:	83 c5 01             	add    $0x1,%ebp
  849183:	3b ab 40 07 00 00    	cmp    0x740(%rbx),%ebp
  849189:	0f 83 a9 fa ff ff    	jae    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84918f:	8b 93 44 07 00 00    	mov    0x744(%rbx),%edx
  849195:	39 d5                	cmp    %edx,%ebp
  849197:	73 bf                	jae    849158 <CCharacter::updateAnimation(float)+0x8e8>
  849199:	89 e8                	mov    %ebp,%eax
  84919b:	48 c1 e0 03          	shl    $0x3,%rax
  84919f:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  8491a6:	eb b7                	jmp    84915f <CCharacter::updateAnimation(float)+0x8ef>
  8491a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  8491af:	00
  8491b0:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  8491b7:	48 85 ff             	test   %rdi,%rdi
  8491ba:	0f 84 78 fa ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  8491c0:	48 8b 83 c8 01 00 00 	mov    0x1c8(%rbx),%rax
  8491c7:	48 85 c0             	test   %rax,%rax
  8491ca:	74 0f                	je     8491db <CCharacter::updateAnimation(float)+0x96b>
  8491cc:	48 89 c7             	mov    %rax,%rdi
  8491cf:	e8 3c 15 48 00       	call   cca710 <CSkillManager::hideWeaponTrailsOnCurrentSkill()>
  8491d4:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  8491db:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  8491e2:	be 01 00 00 00       	mov    $0x1,%esi
  8491e7:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  8491ee:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  8491f2:	8b 68 48             	mov    0x48(%rax),%ebp
  8491f5:	e8 66 22 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  8491fa:	4c 8b ab 98 04 00 00 	mov    0x498(%rbx),%r13
  849201:	4d 85 ed             	test   %r13,%r13
  849204:	0f 84 f6 0f 00 00    	je     84a200 <CCharacter::updateAnimation(float)+0x1990>
  84920a:	83 fd 01             	cmp    $0x1,%ebp
  84920d:	0f 8e b8 0e 00 00    	jle    84a0cb <CCharacter::updateAnimation(float)+0x185b>
  849213:	83 fd 02             	cmp    $0x2,%ebp
  849216:	0f 85 1c fa ff ff    	jne    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84921c:	48 85 c0             	test   %rax,%rax
  84921f:	90                   	nop
  849220:	0f 84 12 fa ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849226:	48 83 bb a0 06 00 00 	cmpq   $0x0,0x6a0(%rbx)
  84922d:	00
  84922e:	0f 84 04 fa ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849234:	be 66 00 00 00       	mov    $0x66,%esi
  849239:	48 89 c7             	mov    %rax,%rdi
  84923c:	e8 5f d0 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  849241:	84 c0                	test   %al,%al
  849243:	0f 85 ef f9 ff ff    	jne    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849249:	e9 d8 0f 00 00       	jmp    84a226 <CCharacter::updateAnimation(float)+0x19b6>
  84924e:	66 90                	xchg   %ax,%ax
  849250:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  849257:	48 83 bb 98 04 00 00 	cmpq   $0x0,0x498(%rbx)
  84925e:	00
  84925f:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  849266:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  84926a:	44 8b 68 48          	mov    0x48(%rax),%r13d
  84926e:	0f 84 2c 0f 00 00    	je     84a1a0 <CCharacter::updateAnimation(float)+0x1930>
  849274:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  84927b:	48 85 ff             	test   %rdi,%rdi
  84927e:	74 41                	je     8492c1 <CCharacter::updateAnimation(float)+0xa51>
  849280:	be 01 00 00 00       	mov    $0x1,%esi
  849285:	e8 d6 21 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84928a:	41 83 fd 01          	cmp    $0x1,%r13d
  84928e:	49 89 c6             	mov    %rax,%r14
  849291:	0f 8e 79 0e 00 00    	jle    84a110 <CCharacter::updateAnimation(float)+0x18a0>
  849297:	48 83 bb a0 06 00 00 	cmpq   $0x0,0x6a0(%rbx)
  84929e:	00
  84929f:	0f 84 3d 16 00 00    	je     84a8e2 <CCharacter::updateAnimation(float)+0x2072>
  8492a5:	41 83 fd 02          	cmp    $0x2,%r13d
  8492a9:	0f 84 98 0f 00 00    	je     84a247 <CCharacter::updateAnimation(float)+0x19d7>
  8492af:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  8492b6:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  8492bd:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  8492c1:	48 8b 70 18          	mov    0x18(%rax),%rsi
  8492c5:	4c 8d ac 24 70 03 00 	lea    0x370(%rsp),%r13
  8492cc:	00
  8492cd:	4c 89 ef             	mov    %r13,%rdi
  8492d0:	e8 7b 50 44 00       	call   c8e350 <STRINGS::StringConvertToNarrow(wchar_t const*)>
  8492d5:	48 8b 84 24 70 03 00 	mov    0x370(%rsp),%rax
  8492dc:	00
  8492dd:	48 83 78 e8 00       	cmpq   $0x0,-0x18(%rax)
  8492e2:	0f 85 c3 0c 00 00    	jne    849fab <CCharacter::updateAnimation(float)+0x173b>
  8492e8:	48 83 bb 98 06 00 00 	cmpq   $0x0,0x698(%rbx)
  8492ef:	00
  8492f0:	74 59                	je     84934b <CCharacter::updateAnimation(float)+0xadb>
  8492f2:	48 89 df             	mov    %rbx,%rdi
  8492f5:	e8 76 6e fc ff       	call   810170 <CCharacter::alignment()>
  8492fa:	48 8d ac 24 60 03 00 	lea    0x360(%rsp),%rbp
  849301:	00
  849302:	83 f8 01             	cmp    $0x1,%eax
  849305:	be 34 05 fa 00       	mov    $0xfa0534,%esi
  84930a:	b8 40 05 fa 00       	mov    $0xfa0540,%eax
  84930f:	48 8d 94 24 39 04 00 	lea    0x439(%rsp),%rdx
  849316:	00
  849317:	48 0f 45 f0          	cmovne %rax,%rsi
  84931b:	48 89 ef             	mov    %rbp,%rdi
  84931e:	e8 d5 cf d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  849323:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84932a:	48 89 ee             	mov    %rbp,%rsi
  84932d:	e8 5e 0d 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  849332:	48 8b bc 24 60 03 00 	mov    0x360(%rsp),%rdi
  849339:	00
  84933a:	48 83 ef 18          	sub    $0x18,%rdi
  84933e:	48 81 ff 20 3a 42 01 	cmp    $0x1423a20,%rdi
  849345:	0f 85 ca 23 00 00    	jne    84b715 <CCharacter::updateAnimation(float)+0x2ea5>
  84934b:	48 83 bb a0 06 00 00 	cmpq   $0x0,0x6a0(%rbx)
  849352:	00
  849353:	74 59                	je     8493ae <CCharacter::updateAnimation(float)+0xb3e>
  849355:	48 89 df             	mov    %rbx,%rdi
  849358:	e8 13 6e fc ff       	call   810170 <CCharacter::alignment()>
  84935d:	48 8d ac 24 50 03 00 	lea    0x350(%rsp),%rbp
  849364:	00
  849365:	83 f8 01             	cmp    $0x1,%eax
  849368:	be 34 05 fa 00       	mov    $0xfa0534,%esi
  84936d:	b8 40 05 fa 00       	mov    $0xfa0540,%eax
  849372:	48 8d 94 24 38 04 00 	lea    0x438(%rsp),%rdx
  849379:	00
  84937a:	48 0f 45 f0          	cmovne %rax,%rsi
  84937e:	48 89 ef             	mov    %rbp,%rdi
  849381:	e8 72 cf d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  849386:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84938d:	48 89 ee             	mov    %rbp,%rsi
  849390:	e8 fb 0c 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  849395:	48 8b bc 24 50 03 00 	mov    0x350(%rsp),%rdi
  84939c:	00
  84939d:	48 83 ef 18          	sub    $0x18,%rdi
  8493a1:	48 81 ff 20 3a 42 01 	cmp    $0x1423a20,%rdi
  8493a8:	0f 85 21 23 00 00    	jne    84b6cf <CCharacter::updateAnimation(float)+0x2e5f>
  8493ae:	48 8b bc 24 70 03 00 	mov    0x370(%rsp),%rdi
  8493b5:	00
  8493b6:	48 83 ef 18          	sub    $0x18,%rdi
  8493ba:	48 81 ff 20 3a 42 01 	cmp    $0x1423a20,%rdi
  8493c1:	0f 84 71 f8 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  8493c7:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  8493cc:	48 85 c0             	test   %rax,%rax
  8493cf:	0f 84 9d 21 00 00    	je     84b572 <CCharacter::updateAnimation(float)+0x2d02>
  8493d5:	83 c8 ff             	or     $0xffffffff,%eax
  8493d8:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  8493dd:	85 c0                	test   %eax,%eax
  8493df:	0f 8f 53 f8 ff ff    	jg     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  8493e5:	48 8d b4 24 17 04 00 	lea    0x417(%rsp),%rsi
  8493ec:	00
  8493ed:	e8 e6 c3 d0 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  8493f2:	e9 41 f8 ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  8493f7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8493fe:	00 00
  849400:	48 89 df             	mov    %rbx,%rdi
  849403:	ba 01 00 00 00       	mov    $0x1,%edx
  849408:	be 03 00 00 00       	mov    $0x3,%esi
  84940d:	e8 ce 85 fc ff       	call   8119e0 <CCharacter::incrementJournalStatistic(EJournalStatistic, int)>
  849412:	48 8b bb 98 02 00 00 	mov    0x298(%rbx),%rdi
  849419:	48 85 ff             	test   %rdi,%rdi
  84941c:	0f 84 16 f8 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849422:	0f 57 c9             	xorps  %xmm1,%xmm1
  849425:	48 8b 53 58          	mov    0x58(%rbx),%rdx
  849429:	31 c9                	xor    %ecx,%ecx
  84942b:	31 f6                	xor    %esi,%esi
  84942d:	41 83 c4 01          	add    $0x1,%r12d
  849431:	0f 28 c1             	movaps %xmm1,%xmm0
  849434:	e8 67 04 22 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  849439:	e9 ba f6 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  84943e:	66 90                	xchg   %ax,%ax
  849440:	41 8b 75 28          	mov    0x28(%r13),%esi
  849444:	31 ed                	xor    %ebp,%ebp
  849446:	83 fe ff             	cmp    $0xffffffff,%esi
  849449:	0f 85 c9 02 00 00    	jne    849718 <CCharacter::updateAnimation(float)+0xea8>
  84944f:	90                   	nop
  849450:	e9 e3 f7 ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849455:	0f 1f 00             	nopl   (%rax)
  849458:	48 8b 10             	mov    (%rax),%rdx
  84945b:	44 8b 32             	mov    (%rdx),%r14d
  84945e:	44 3b b3 40 07 00 00 	cmp    0x740(%rbx),%r14d
  849465:	0f 83 a6 02 00 00    	jae    849711 <CCharacter::updateAnimation(float)+0xea1>
  84946b:	8b 93 44 07 00 00    	mov    0x744(%rbx),%edx
  849471:	41 39 d6             	cmp    %edx,%r14d
  849474:	0f 82 7e 08 00 00    	jb     849cf8 <CCharacter::updateAnimation(float)+0x1488>
  84947a:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849481:	48 8b 00             	mov    (%rax),%rax
  849484:	48 83 78 18 00       	cmpq   $0x0,0x18(%rax)
  849489:	0f 84 82 02 00 00    	je     849711 <CCharacter::updateAnimation(float)+0xea1>
  84948f:	41 39 d6             	cmp    %edx,%r14d
  849492:	0f 82 48 08 00 00    	jb     849ce0 <CCharacter::updateAnimation(float)+0x1470>
  849498:	48 8b 8b 38 07 00 00 	mov    0x738(%rbx),%rcx
  84949f:	48 89 c8             	mov    %rcx,%rax
  8494a2:	48 8b 09             	mov    (%rcx),%rcx
  8494a5:	80 79 58 00          	cmpb   $0x0,0x58(%rcx)
  8494a9:	0f 84 b1 05 00 00    	je     849a60 <CCharacter::updateAnimation(float)+0x11f0>
  8494af:	41 39 d6             	cmp    %edx,%r14d
  8494b2:	48 89 c1             	mov    %rax,%rcx
  8494b5:	73 07                	jae    8494be <CCharacter::updateAnimation(float)+0xc4e>
  8494b7:	44 89 f1             	mov    %r14d,%ecx
  8494ba:	48 8d 0c c8          	lea    (%rax,%rcx,8),%rcx
  8494be:	48 8b 09             	mov    (%rcx),%rcx
  8494c1:	80 79 59 00          	cmpb   $0x0,0x59(%rcx)
  8494c5:	0f 85 95 05 00 00    	jne    849a60 <CCharacter::updateAnimation(float)+0x11f0>
  8494cb:	41 39 d6             	cmp    %edx,%r14d
  8494ce:	48 89 c1             	mov    %rax,%rcx
  8494d1:	73 07                	jae    8494da <CCharacter::updateAnimation(float)+0xc6a>
  8494d3:	44 89 f1             	mov    %r14d,%ecx
  8494d6:	48 8d 0c c8          	lea    (%rax,%rcx,8),%rcx
  8494da:	48 8b 09             	mov    (%rcx),%rcx
  8494dd:	80 79 58 00          	cmpb   $0x0,0x58(%rcx)
  8494e1:	0f 85 81 0a 00 00    	jne    849f68 <CCharacter::updateAnimation(float)+0x16f8>
  8494e7:	41 39 d6             	cmp    %edx,%r14d
  8494ea:	73 07                	jae    8494f3 <CCharacter::updateAnimation(float)+0xc83>
  8494ec:	44 89 f2             	mov    %r14d,%edx
  8494ef:	48 8d 04 d0          	lea    (%rax,%rdx,8),%rax
  8494f3:	48 8b 10             	mov    (%rax),%rdx
  8494f6:	48 8b 03             	mov    (%rbx),%rax
  8494f9:	48 89 df             	mov    %rbx,%rdi
  8494fc:	48 89 54 24 58       	mov    %rdx,0x58(%rsp)
  849501:	ff 90 e8 00 00 00    	call   *0xe8(%rax)
  849507:	48 8b 54 24 58       	mov    0x58(%rsp),%rdx
  84950c:	f3 0f 10 40 30       	movss  0x30(%rax),%xmm0
  849511:	f3 0f 10 58 34       	movss  0x34(%rax),%xmm3
  849516:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84951d:	f3 0f 10 60 04       	movss  0x4(%rax),%xmm4
  849522:	31 f6                	xor    %esi,%esi
  849524:	f3 0f 10 52 28       	movss  0x28(%rdx),%xmm2
  849529:	f3 0f 10 6a 2c       	movss  0x2c(%rdx),%xmm5
  84952e:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  849532:	f3 0f 59 dd          	mulss  %xmm5,%xmm3
  849536:	f3 0f 10 4a 30       	movss  0x30(%rdx),%xmm1
  84953b:	f3 0f 59 e5          	mulss  %xmm5,%xmm4
  84953f:	f3 0f 10 70 14       	movss  0x14(%rax),%xmm6
  849544:	f3 0f 59 f5          	mulss  %xmm5,%xmm6
  849548:	f3 0f 59 68 24       	mulss  0x24(%rax),%xmm5
  84954d:	f3 0f 58 c3          	addss  %xmm3,%xmm0
  849551:	f3 0f 10 58 38       	movss  0x38(%rax),%xmm3
  849556:	f3 0f 59 d9          	mulss  %xmm1,%xmm3
  84955a:	f3 0f 58 c3          	addss  %xmm3,%xmm0
  84955e:	f3 0f 10 1d 96 b2 75 	movss  0x75b296(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  849565:	00
  849566:	f3 0f 58 40 3c       	addss  0x3c(%rax),%xmm0
  84956b:	f3 0f 5e d8          	divss  %xmm0,%xmm3
  84956f:	0f 28 c3             	movaps %xmm3,%xmm0
  849572:	f3 0f 10 18          	movss  (%rax),%xmm3
  849576:	f3 0f 59 da          	mulss  %xmm2,%xmm3
  84957a:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  84957e:	f3 0f 10 60 08       	movss  0x8(%rax),%xmm4
  849583:	f3 0f 59 e1          	mulss  %xmm1,%xmm4
  849587:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  84958b:	f3 0f 10 60 10       	movss  0x10(%rax),%xmm4
  849590:	f3 0f 59 e2          	mulss  %xmm2,%xmm4
  849594:	f3 0f 59 50 20       	mulss  0x20(%rax),%xmm2
  849599:	f3 0f 58 58 0c       	addss  0xc(%rax),%xmm3
  84959e:	f3 0f 58 e6          	addss  %xmm6,%xmm4
  8495a2:	f3 0f 10 70 18       	movss  0x18(%rax),%xmm6
  8495a7:	f3 0f 59 f1          	mulss  %xmm1,%xmm6
  8495ab:	f3 0f 59 48 28       	mulss  0x28(%rax),%xmm1
  8495b0:	f3 0f 58 d5          	addss  %xmm5,%xmm2
  8495b4:	f3 0f 58 e6          	addss  %xmm6,%xmm4
  8495b8:	f3 0f 59 d8          	mulss  %xmm0,%xmm3
  8495bc:	f3 0f 58 d1          	addss  %xmm1,%xmm2
  8495c0:	f3 0f 58 60 1c       	addss  0x1c(%rax),%xmm4
  8495c5:	f3 0f 58 50 2c       	addss  0x2c(%rax),%xmm2
  8495ca:	f3 0f 11 5c 24 30    	movss  %xmm3,0x30(%rsp)
  8495d0:	f3 0f 59 e0          	mulss  %xmm0,%xmm4
  8495d4:	f3 0f 59 d0          	mulss  %xmm0,%xmm2
  8495d8:	f3 0f 11 64 24 40    	movss  %xmm4,0x40(%rsp)
  8495de:	f3 0f 11 54 24 20    	movss  %xmm2,0x20(%rsp)
  8495e4:	e8 97 da 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  8495e9:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  8495ef:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  8495f4:	be 01 00 00 00       	mov    $0x1,%esi
  8495f9:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  849600:	00 00
  849602:	48 89 df             	mov    %rbx,%rdi
  849605:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  84960c:	00
  84960d:	48 89 84 24 e0 00 00 	mov    %rax,0xe0(%rsp)
  849614:	00
  849615:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  84961c:	89 84 24 e8 00 00 00 	mov    %eax,0xe8(%rsp)
  849623:	e8 58 da 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  849628:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  84962e:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  849633:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  84963a:	00 00
  84963c:	f3 0f 10 5c 24 30    	movss  0x30(%rsp),%xmm3
  849642:	48 89 84 24 f0 00 00 	mov    %rax,0xf0(%rsp)
  849649:	00
  84964a:	f3 0f 10 84 24 f0 00 	movss  0xf0(%rsp),%xmm0
  849651:	00 00
  849653:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  84965a:	00
  84965b:	f3 0f 58 84 24 e0 00 	addss  0xe0(%rsp),%xmm0
  849662:	00 00
  849664:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  84966b:	f3 0f 10 8c 24 f4 00 	movss  0xf4(%rsp),%xmm1
  849672:	00 00
  849674:	f3 0f 58 8c 24 e4 00 	addss  0xe4(%rsp),%xmm1
  84967b:	00 00
  84967d:	f3 0f 10 64 24 40    	movss  0x40(%rsp),%xmm4
  849683:	89 84 24 f8 00 00 00 	mov    %eax,0xf8(%rsp)
  84968a:	f3 0f 10 54 24 20    	movss  0x20(%rsp),%xmm2
  849690:	f3 0f 58 c3          	addss  %xmm3,%xmm0
  849694:	f3 0f 10 9c 24 f8 00 	movss  0xf8(%rsp),%xmm3
  84969b:	00 00
  84969d:	f3 0f 58 9c 24 e8 00 	addss  0xe8(%rsp),%xmm3
  8496a4:	00 00
  8496a6:	f3 0f 58 cc          	addss  %xmm4,%xmm1
  8496aa:	f3 0f 11 84 24 d0 00 	movss  %xmm0,0xd0(%rsp)
  8496b1:	00 00
  8496b3:	f3 0f 11 8c 24 d4 00 	movss  %xmm1,0xd4(%rsp)
  8496ba:	00 00
  8496bc:	f3 0f 58 da          	addss  %xmm2,%xmm3
  8496c0:	f3 0f 11 9c 24 d8 00 	movss  %xmm3,0xd8(%rsp)
  8496c7:	00 00
  8496c9:	44 3b b3 44 07 00 00 	cmp    0x744(%rbx),%r14d
  8496d0:	0f 82 ac 08 00 00    	jb     849f82 <CCharacter::updateAnimation(float)+0x1712>
  8496d6:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  8496dd:	48 8b 00             	mov    (%rax),%rax
  8496e0:	48 8d b4 24 d0 00 00 	lea    0xd0(%rsp),%rsi
  8496e7:	00
  8496e8:	48 8b 78 18          	mov    0x18(%rax),%rdi
  8496ec:	e8 ef d9 19 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  8496f1:	44 3b b3 44 07 00 00 	cmp    0x744(%rbx),%r14d
  8496f8:	0f 82 ce 05 00 00    	jb     849ccc <CCharacter::updateAnimation(float)+0x145c>
  8496fe:	4c 8b b3 38 07 00 00 	mov    0x738(%rbx),%r14
  849705:	49 8b 06             	mov    (%r14),%rax
  849708:	48 8b 78 18          	mov    0x18(%rax),%rdi
  84970c:	e8 0f 0f 1e 00       	call   a2a620 <CParticle::Start()>
  849711:	41 8b 75 28          	mov    0x28(%r13),%esi
  849715:	83 c5 01             	add    $0x1,%ebp
  849718:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84971f:	4c 89 ea             	mov    %r13,%rdx
  849722:	e8 89 07 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  849727:	3b 68 08             	cmp    0x8(%rax),%ebp
  84972a:	0f 83 08 f5 ff ff    	jae    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849730:	41 8b 75 28          	mov    0x28(%r13),%esi
  849734:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84973b:	4c 89 ea             	mov    %r13,%rdx
  84973e:	e8 6d 07 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  849743:	3b 68 0c             	cmp    0xc(%rax),%ebp
  849746:	0f 83 0c fd ff ff    	jae    849458 <CCharacter::updateAnimation(float)+0xbe8>
  84974c:	89 ea                	mov    %ebp,%edx
  84974e:	48 c1 e2 02          	shl    $0x2,%rdx
  849752:	48 03 10             	add    (%rax),%rdx
  849755:	e9 01 fd ff ff       	jmp    84945b <CCharacter::updateAnimation(float)+0xbeb>
  84975a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  849760:	48 83 bb a0 02 00 00 	cmpq   $0x0,0x2a0(%rbx)
  849767:	00
  849768:	0f 84 ca f4 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84976e:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  849775:	48 8b 87 b0 01 00 00 	mov    0x1b0(%rdi),%rax
  84977c:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  849780:	8b 72 28             	mov    0x28(%rdx),%esi
  849783:	e8 28 07 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  849788:	44 8b 68 08          	mov    0x8(%rax),%r13d
  84978c:	45 85 ed             	test   %r13d,%r13d
  84978f:	0f 84 a3 f4 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849795:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84979c:	4c 8b 6b 58          	mov    0x58(%rbx),%r13
  8497a0:	41 83 c4 01          	add    $0x1,%r12d
  8497a4:	48 8b 87 b0 01 00 00 	mov    0x1b0(%rdi),%rax
  8497ab:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  8497af:	8b 72 28             	mov    0x28(%rdx),%esi
  8497b2:	e8 f9 06 05 00       	call   899eb0 <CGenericModel::getValueIndexes(int, CKeyframe*)>
  8497b7:	48 8b 00             	mov    (%rax),%rax
  8497ba:	0f 57 c9             	xorps  %xmm1,%xmm1
  8497bd:	48 8b bb a0 02 00 00 	mov    0x2a0(%rbx),%rdi
  8497c4:	31 c9                	xor    %ecx,%ecx
  8497c6:	4c 89 ea             	mov    %r13,%rdx
  8497c9:	8b 30                	mov    (%rax),%esi
  8497cb:	0f 28 c1             	movaps %xmm1,%xmm0
  8497ce:	e8 cd 00 22 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  8497d3:	e9 20 f3 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  8497d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  8497df:	00
  8497e0:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  8497e7:	48 8b 3d 52 2b c3 00 	mov    0xc32b52(%rip),%rdi        # 147c340 <EMPTY_STRING>
  8497ee:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  8497f5:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  8497f9:	48 8b 50 20          	mov    0x20(%rax),%rdx
  8497fd:	48 8b 42 e8          	mov    -0x18(%rdx),%rax
  849801:	48 3b 47 e8          	cmp    -0x18(%rdi),%rax
  849805:	0f 84 ed 07 00 00    	je     849ff8 <CCharacter::updateAnimation(float)+0x1788>
  84980b:	44 8b 9b 40 07 00 00 	mov    0x740(%rbx),%r11d
  849812:	31 ed                	xor    %ebp,%ebp
  849814:	45 85 db             	test   %r11d,%r11d
  849817:	75 44                	jne    84985d <CCharacter::updateAnimation(float)+0xfed>
  849819:	e9 1a f4 ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84981e:	66 90                	xchg   %ax,%ax
  849820:	48 8b 8b 38 07 00 00 	mov    0x738(%rbx),%rcx
  849827:	48 8b 09             	mov    (%rcx),%rcx
  84982a:	48 8b 79 40          	mov    0x40(%rcx),%rdi
  84982e:	48 39 47 e8          	cmp    %rax,-0x18(%rdi)
  849832:	74 4f                	je     849883 <CCharacter::updateAnimation(float)+0x1013>
  849834:	83 c5 01             	add    $0x1,%ebp
  849837:	3b ab 40 07 00 00    	cmp    0x740(%rbx),%ebp
  84983d:	0f 83 f5 f3 ff ff    	jae    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849843:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84984a:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  849851:	4a 8b 04 30          	mov    (%rax,%r14,1),%rax
  849855:	48 8b 50 20          	mov    0x20(%rax),%rdx
  849859:	48 8b 42 e8          	mov    -0x18(%rdx),%rax
  84985d:	44 8b 83 44 07 00 00 	mov    0x744(%rbx),%r8d
  849864:	41 39 e8             	cmp    %ebp,%r8d
  849867:	76 b7                	jbe    849820 <CCharacter::updateAnimation(float)+0xfb0>
  849869:	89 e9                	mov    %ebp,%ecx
  84986b:	48 c1 e1 03          	shl    $0x3,%rcx
  84986f:	48 03 8b 38 07 00 00 	add    0x738(%rbx),%rcx
  849876:	48 8b 09             	mov    (%rcx),%rcx
  849879:	48 8b 79 40          	mov    0x40(%rcx),%rdi
  84987d:	48 39 47 e8          	cmp    %rax,-0x18(%rdi)
  849881:	75 b1                	jne    849834 <CCharacter::updateAnimation(float)+0xfc4>
  849883:	48 39 c0             	cmp    %rax,%rax
  849886:	48 89 d6             	mov    %rdx,%rsi
  849889:	48 89 c1             	mov    %rax,%rcx
  84988c:	f3 a6                	repz cmpsb (%rdi),(%rsi)
  84988e:	75 a4                	jne    849834 <CCharacter::updateAnimation(float)+0xfc4>
  849890:	41 39 e8             	cmp    %ebp,%r8d
  849893:	0f 87 9b 04 00 00    	ja     849d34 <CCharacter::updateAnimation(float)+0x14c4>
  849899:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  8498a0:	48 8b 00             	mov    (%rax),%rax
  8498a3:	48 8b 78 18          	mov    0x18(%rax),%rdi
  8498a7:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  8498ae:	83 f6 01             	xor    $0x1,%esi
  8498b1:	40 0f b6 f6          	movzbl %sil,%esi
  8498b5:	e8 d6 09 1e 00       	call   a2a290 <CParticle::Stop(bool)>
  8498ba:	e9 75 ff ff ff       	jmp    849834 <CCharacter::updateAnimation(float)+0xfc4>
  8498bf:	90                   	nop
  8498c0:	c6 83 8d 01 00 00 00 	movb   $0x0,0x18d(%rbx)
  8498c7:	41 83 c4 01          	add    $0x1,%r12d
  8498cb:	e9 28 f2 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  8498d0:	c6 83 8d 01 00 00 01 	movb   $0x1,0x18d(%rbx)
  8498d7:	c6 83 9c 01 00 00 01 	movb   $0x1,0x19c(%rbx)
  8498de:	41 83 c4 01          	add    $0x1,%r12d
  8498e2:	e9 11 f2 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  8498e7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8498ee:	00 00
  8498f0:	48 8b 83 90 03 00 00 	mov    0x390(%rbx),%rax
  8498f7:	48 85 c0             	test   %rax,%rax
  8498fa:	0f 84 38 f3 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849900:	48 8b bb 98 02 00 00 	mov    0x298(%rbx),%rdi
  849907:	48 85 ff             	test   %rdi,%rdi
  84990a:	0f 84 28 f3 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849910:	80 78 18 00          	cmpb   $0x0,0x18(%rax)
  849914:	74 20                	je     849936 <CCharacter::updateAnimation(float)+0x10c6>
  849916:	48 8b 83 98 04 00 00 	mov    0x498(%rbx),%rax
  84991d:	48 85 c0             	test   %rax,%rax
  849920:	0f 84 12 f3 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849926:	48 8b b8 d8 01 00 00 	mov    0x1d8(%rax),%rdi
  84992d:	48 85 ff             	test   %rdi,%rdi
  849930:	0f 84 02 f3 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  849936:	0f 57 c9             	xorps  %xmm1,%xmm1
  849939:	48 8b 53 58          	mov    0x58(%rbx),%rdx
  84993d:	31 c9                	xor    %ecx,%ecx
  84993f:	be 0a 00 00 00       	mov    $0xa,%esi
  849944:	41 83 c4 01          	add    $0x1,%r12d
  849948:	0f 28 c1             	movaps %xmm1,%xmm0
  84994b:	e8 50 ff 21 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  849950:	e9 a3 f1 ff ff       	jmp    848af8 <CCharacter::updateAnimation(float)+0x288>
  849955:	48 83 bb 90 04 00 00 	cmpq   $0x0,0x490(%rbx)
  84995c:	00
  84995d:	0f 84 a6 f0 ff ff    	je     848a09 <CCharacter::updateAnimation(float)+0x199>
  849963:	0f b6 b3 30 05 00 00 	movzbl 0x530(%rbx),%esi
  84996a:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  849971:	45 31 e4             	xor    %r12d,%r12d
  849974:	e8 d7 06 05 00       	call   89a050 <CGenericModel::setCastsShadows(bool)>
  849979:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  849980:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  849987:	44 89 e6             	mov    %r12d,%esi
  84998a:	e8 d1 1a 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84998f:	48 85 c0             	test   %rax,%rax
  849992:	48 89 c5             	mov    %rax,%rbp
  849995:	74 63                	je     8499fa <CCharacter::updateAnimation(float)+0x118a>
  849997:	48 8b 00             	mov    (%rax),%rax
  84999a:	48 89 ef             	mov    %rbp,%rdi
  84999d:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  8499a3:	48 85 c0             	test   %rax,%rax
  8499a6:	74 20                	je     8499c8 <CCharacter::updateAnimation(float)+0x1158>
  8499a8:	44 0f b6 ab 30 05 00 	movzbl 0x530(%rbx),%r13d
  8499af:	00
  8499b0:	48 8b 45 00          	mov    0x0(%rbp),%rax
  8499b4:	48 89 ef             	mov    %rbp,%rdi
  8499b7:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  8499bd:	44 89 ee             	mov    %r13d,%esi
  8499c0:	48 89 c7             	mov    %rax,%rdi
  8499c3:	e8 88 06 05 00       	call   89a050 <CGenericModel::setCastsShadows(bool)>
  8499c8:	48 8b 45 00          	mov    0x0(%rbp),%rax
  8499cc:	48 89 ef             	mov    %rbp,%rdi
  8499cf:	ff 90 f0 02 00 00    	call   *0x2f0(%rax)
  8499d5:	48 85 c0             	test   %rax,%rax
  8499d8:	74 20                	je     8499fa <CCharacter::updateAnimation(float)+0x118a>
  8499da:	44 0f b6 ab 30 05 00 	movzbl 0x530(%rbx),%r13d
  8499e1:	00
  8499e2:	48 8b 45 00          	mov    0x0(%rbp),%rax
  8499e6:	48 89 ef             	mov    %rbp,%rdi
  8499e9:	ff 90 f0 02 00 00    	call   *0x2f0(%rax)
  8499ef:	44 89 ee             	mov    %r13d,%esi
  8499f2:	48 89 c7             	mov    %rax,%rdi
  8499f5:	e8 56 06 05 00       	call   89a050 <CGenericModel::setCastsShadows(bool)>
  8499fa:	41 83 c4 01          	add    $0x1,%r12d
  8499fe:	41 83 fc 0c          	cmp    $0xc,%r12d
  849a02:	0f 85 78 ff ff ff    	jne    849980 <CCharacter::updateAnimation(float)+0x1110>
  849a08:	e9 fc ef ff ff       	jmp    848a09 <CCharacter::updateAnimation(float)+0x199>
  849a0d:	48 8b 03             	mov    (%rbx),%rax
  849a10:	48 89 df             	mov    %rbx,%rdi
  849a13:	ff 50 48             	call   *0x48(%rax)
  849a16:	84 c0                	test   %al,%al
  849a18:	0f 84 9a ef ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849a1e:	66 90                	xchg   %ax,%ax
  849a20:	e9 cb ef ff ff       	jmp    8489f0 <CCharacter::updateAnimation(float)+0x180>
  849a25:	0f 1f 00             	nopl   (%rax)
  849a28:	39 d5                	cmp    %edx,%ebp
  849a2a:	0f 82 e0 02 00 00    	jb     849d10 <CCharacter::updateAnimation(float)+0x14a0>
  849a30:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849a37:	48 8b 00             	mov    (%rax),%rax
  849a3a:	48 8b 78 18          	mov    0x18(%rax),%rdi
  849a3e:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  849a45:	83 f6 01             	xor    $0x1,%esi
  849a48:	40 0f b6 f6          	movzbl %sil,%esi
  849a4c:	e8 3f 08 1e 00       	call   a2a290 <CParticle::Stop(bool)>
  849a51:	e9 2a f7 ff ff       	jmp    849180 <CCharacter::updateAnimation(float)+0x910>
  849a56:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  849a5d:	00 00 00
  849a60:	41 39 d6             	cmp    %edx,%r14d
  849a63:	48 89 c1             	mov    %rax,%rcx
  849a66:	73 07                	jae    849a6f <CCharacter::updateAnimation(float)+0x11ff>
  849a68:	44 89 f1             	mov    %r14d,%ecx
  849a6b:	48 8d 0c c8          	lea    (%rax,%rcx,8),%rcx
  849a6f:	48 8b 09             	mov    (%rcx),%rcx
  849a72:	48 83 79 48 00       	cmpq   $0x0,0x48(%rcx)
  849a77:	0f 84 4e fa ff ff    	je     8494cb <CCharacter::updateAnimation(float)+0xc5b>
  849a7d:	41 39 d6             	cmp    %edx,%r14d
  849a80:	73 07                	jae    849a89 <CCharacter::updateAnimation(float)+0x1219>
  849a82:	44 89 f2             	mov    %r14d,%edx
  849a85:	48 8d 04 d0          	lea    (%rax,%rdx,8),%rax
  849a89:	48 8b 00             	mov    (%rax),%rax
  849a8c:	48 8b 78 48          	mov    0x48(%rax),%rdi
  849a90:	48 8b 07             	mov    (%rdi),%rax
  849a93:	ff 90 00 02 00 00    	call   *0x200(%rax)
  849a99:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  849aa0:	f3 0f 10 10          	movss  (%rax),%xmm2
  849aa4:	f3 0f 10 58 04       	movss  0x4(%rax),%xmm3
  849aa9:	31 f6                	xor    %esi,%esi
  849aab:	f3 0f 10 60 08       	movss  0x8(%rax),%xmm4
  849ab0:	f3 0f 11 64 24 40    	movss  %xmm4,0x40(%rsp)
  849ab6:	f3 0f 11 54 24 20    	movss  %xmm2,0x20(%rsp)
  849abc:	f3 0f 11 5c 24 30    	movss  %xmm3,0x30(%rsp)
  849ac2:	e8 b9 d5 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  849ac7:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  849acd:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  849ad2:	be 01 00 00 00       	mov    $0x1,%esi
  849ad7:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  849ade:	00 00
  849ae0:	48 89 df             	mov    %rbx,%rdi
  849ae3:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  849aea:	00
  849aeb:	48 89 84 24 10 01 00 	mov    %rax,0x110(%rsp)
  849af2:	00
  849af3:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  849afa:	89 84 24 18 01 00 00 	mov    %eax,0x118(%rsp)
  849b01:	e8 7a d5 19 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  849b06:	66 0f d6 44 24 18    	movq   %xmm0,0x18(%rsp)
  849b0c:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  849b11:	f3 0f 11 8c 24 88 00 	movss  %xmm1,0x88(%rsp)
  849b18:	00 00
  849b1a:	f3 0f 10 54 24 20    	movss  0x20(%rsp),%xmm2
  849b20:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  849b27:	00
  849b28:	48 89 84 24 20 01 00 	mov    %rax,0x120(%rsp)
  849b2f:	00
  849b30:	8b 84 24 88 00 00 00 	mov    0x88(%rsp),%eax
  849b37:	f3 0f 10 5c 24 30    	movss  0x30(%rsp),%xmm3
  849b3d:	f3 0f 10 64 24 40    	movss  0x40(%rsp),%xmm4
  849b43:	89 84 24 28 01 00 00 	mov    %eax,0x128(%rsp)
  849b4a:	44 3b b3 44 07 00 00 	cmp    0x744(%rbx),%r14d
  849b51:	0f 82 f9 03 00 00    	jb     849f50 <CCharacter::updateAnimation(float)+0x16e0>
  849b57:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849b5e:	48 8b 00             	mov    (%rax),%rax
  849b61:	48 89 df             	mov    %rbx,%rdi
  849b64:	f3 0f 58 60 30       	addss  0x30(%rax),%xmm4
  849b69:	f3 0f 58 58 2c       	addss  0x2c(%rax),%xmm3
  849b6e:	f3 0f 58 50 28       	addss  0x28(%rax),%xmm2
  849b73:	48 8b 03             	mov    (%rbx),%rax
  849b76:	f3 0f 11 64 24 40    	movss  %xmm4,0x40(%rsp)
  849b7c:	f3 0f 11 5c 24 30    	movss  %xmm3,0x30(%rsp)
  849b82:	f3 0f 11 54 24 20    	movss  %xmm2,0x20(%rsp)
  849b88:	ff 90 e8 00 00 00    	call   *0xe8(%rax)
  849b8e:	f3 0f 10 54 24 20    	movss  0x20(%rsp),%xmm2
  849b94:	f3 0f 10 40 30       	movss  0x30(%rax),%xmm0
  849b99:	f3 0f 10 5c 24 30    	movss  0x30(%rsp),%xmm3
  849b9f:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  849ba3:	f3 0f 10 48 34       	movss  0x34(%rax),%xmm1
  849ba8:	f3 0f 59 cb          	mulss  %xmm3,%xmm1
  849bac:	f3 0f 10 64 24 40    	movss  0x40(%rsp),%xmm4
  849bb2:	f3 0f 10 2d 42 ac 75 	movss  0x75ac42(%rip),%xmm5        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  849bb9:	00
  849bba:	f3 0f 10 70 04       	movss  0x4(%rax),%xmm6
  849bbf:	f3 0f 59 f3          	mulss  %xmm3,%xmm6
  849bc3:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  849bc7:	f3 0f 10 48 38       	movss  0x38(%rax),%xmm1
  849bcc:	f3 0f 59 cc          	mulss  %xmm4,%xmm1
  849bd0:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  849bd4:	f3 0f 10 48 10       	movss  0x10(%rax),%xmm1
  849bd9:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  849bdd:	f3 0f 58 40 3c       	addss  0x3c(%rax),%xmm0
  849be2:	f3 0f 5e e8          	divss  %xmm0,%xmm5
  849be6:	f3 0f 10 40 14       	movss  0x14(%rax),%xmm0
  849beb:	f3 0f 59 c3          	mulss  %xmm3,%xmm0
  849bef:	f3 0f 59 58 24       	mulss  0x24(%rax),%xmm3
  849bf4:	f3 0f 58 c8          	addss  %xmm0,%xmm1
  849bf8:	f3 0f 10 40 18       	movss  0x18(%rax),%xmm0
  849bfd:	f3 0f 59 c4          	mulss  %xmm4,%xmm0
  849c01:	f3 0f 58 c8          	addss  %xmm0,%xmm1
  849c05:	f3 0f 10 00          	movss  (%rax),%xmm0
  849c09:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  849c0d:	f3 0f 59 50 20       	mulss  0x20(%rax),%xmm2
  849c12:	f3 0f 58 48 1c       	addss  0x1c(%rax),%xmm1
  849c17:	f3 0f 58 c6          	addss  %xmm6,%xmm0
  849c1b:	f3 0f 10 70 08       	movss  0x8(%rax),%xmm6
  849c20:	f3 0f 59 f4          	mulss  %xmm4,%xmm6
  849c24:	f3 0f 59 60 28       	mulss  0x28(%rax),%xmm4
  849c29:	f3 0f 58 d3          	addss  %xmm3,%xmm2
  849c2d:	f3 0f 58 c6          	addss  %xmm6,%xmm0
  849c31:	f3 0f 59 cd          	mulss  %xmm5,%xmm1
  849c35:	f3 0f 58 d4          	addss  %xmm4,%xmm2
  849c39:	f3 0f 58 40 0c       	addss  0xc(%rax),%xmm0
  849c3e:	f3 0f 58 8c 24 24 01 	addss  0x124(%rsp),%xmm1
  849c45:	00 00
  849c47:	f3 0f 58 50 2c       	addss  0x2c(%rax),%xmm2
  849c4c:	f3 0f 59 c5          	mulss  %xmm5,%xmm0
  849c50:	f3 0f 58 8c 24 14 01 	addss  0x114(%rsp),%xmm1
  849c57:	00 00
  849c59:	f3 0f 59 d5          	mulss  %xmm5,%xmm2
  849c5d:	f3 0f 58 84 24 20 01 	addss  0x120(%rsp),%xmm0
  849c64:	00 00
  849c66:	f3 0f 58 94 24 28 01 	addss  0x128(%rsp),%xmm2
  849c6d:	00 00
  849c6f:	f3 0f 11 8c 24 04 01 	movss  %xmm1,0x104(%rsp)
  849c76:	00 00
  849c78:	f3 0f 58 84 24 10 01 	addss  0x110(%rsp),%xmm0
  849c7f:	00 00
  849c81:	f3 0f 58 94 24 18 01 	addss  0x118(%rsp),%xmm2
  849c88:	00 00
  849c8a:	f3 0f 11 84 24 00 01 	movss  %xmm0,0x100(%rsp)
  849c91:	00 00
  849c93:	f3 0f 11 94 24 08 01 	movss  %xmm2,0x108(%rsp)
  849c9a:	00 00
  849c9c:	44 3b b3 44 07 00 00 	cmp    0x744(%rbx),%r14d
  849ca3:	0f 82 8f 02 00 00    	jb     849f38 <CCharacter::updateAnimation(float)+0x16c8>
  849ca9:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849cb0:	48 8b 00             	mov    (%rax),%rax
  849cb3:	4c 89 fe             	mov    %r15,%rsi
  849cb6:	48 8b 78 18          	mov    0x18(%rax),%rdi
  849cba:	e8 21 d4 19 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  849cbf:	44 3b b3 44 07 00 00 	cmp    0x744(%rbx),%r14d
  849cc6:	0f 83 32 fa ff ff    	jae    8496fe <CCharacter::updateAnimation(float)+0xe8e>
  849ccc:	45 89 f6             	mov    %r14d,%r14d
  849ccf:	49 c1 e6 03          	shl    $0x3,%r14
  849cd3:	4c 03 b3 38 07 00 00 	add    0x738(%rbx),%r14
  849cda:	e9 26 fa ff ff       	jmp    849705 <CCharacter::updateAnimation(float)+0xe95>
  849cdf:	90                   	nop
  849ce0:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849ce7:	44 89 f1             	mov    %r14d,%ecx
  849cea:	48 8d 0c c8          	lea    (%rax,%rcx,8),%rcx
  849cee:	e9 af f7 ff ff       	jmp    8494a2 <CCharacter::updateAnimation(float)+0xc32>
  849cf3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  849cf8:	44 89 f0             	mov    %r14d,%eax
  849cfb:	48 c1 e0 03          	shl    $0x3,%rax
  849cff:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  849d06:	e9 76 f7 ff ff       	jmp    849481 <CCharacter::updateAnimation(float)+0xc11>
  849d0b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  849d10:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849d17:	89 ea                	mov    %ebp,%edx
  849d19:	48 8b 04 d0          	mov    (%rax,%rdx,8),%rax
  849d1d:	48 8b 78 18          	mov    0x18(%rax),%rdi
  849d21:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  849d28:	83 f6 01             	xor    $0x1,%esi
  849d2b:	40 0f b6 f6          	movzbl %sil,%esi
  849d2f:	e9 18 fd ff ff       	jmp    849a4c <CCharacter::updateAnimation(float)+0x11dc>
  849d34:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  849d3b:	89 ea                	mov    %ebp,%edx
  849d3d:	48 8b 04 d0          	mov    (%rax,%rdx,8),%rax
  849d41:	48 8b 78 18          	mov    0x18(%rax),%rdi
  849d45:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  849d4c:	83 f6 01             	xor    $0x1,%esi
  849d4f:	40 0f b6 f6          	movzbl %sil,%esi
  849d53:	e9 5d fb ff ff       	jmp    8498b5 <CCharacter::updateAnimation(float)+0x1045>
  849d58:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  849d5f:	00
  849d60:	48 83 bb 90 03 00 00 	cmpq   $0x0,0x390(%rbx)
  849d67:	00
  849d68:	74 15                	je     849d7f <CCharacter::updateAnimation(float)+0x150f>
  849d6a:	f3 0f 10 83 78 03 00 	movss  0x378(%rbx),%xmm0
  849d71:	00
  849d72:	0f 2e 05 6f e9 75 00 	ucomiss 0x75e96f(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  849d79:	0f 87 39 ec ff ff    	ja     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849d7f:	48 83 bb 98 03 00 00 	cmpq   $0x0,0x398(%rbx)
  849d86:	00
  849d87:	74 2a                	je     849db3 <CCharacter::updateAnimation(float)+0x1543>
  849d89:	80 bb 67 02 00 00 00 	cmpb   $0x0,0x267(%rbx)
  849d90:	0f 85 22 ec ff ff    	jne    8489b8 <CCharacter::updateAnimation(float)+0x148>
  849d96:	0f 57 c9             	xorps  %xmm1,%xmm1
  849d99:	f3 0f 10 83 80 03 00 	movss  0x380(%rbx),%xmm0
  849da0:	00
  849da1:	0f 2e c1             	ucomiss %xmm1,%xmm0
  849da4:	76 0d                	jbe    849db3 <CCharacter::updateAnimation(float)+0x1543>
  849da6:	80 bb 7d 03 00 00 00 	cmpb   $0x0,0x37d(%rbx)
  849dad:	0f 84 05 ec ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849db3:	8b 83 30 03 00 00    	mov    0x330(%rbx),%eax
  849db9:	83 f8 05             	cmp    $0x5,%eax
  849dbc:	0f 84 f6 eb ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849dc2:	83 f8 06             	cmp    $0x6,%eax
  849dc5:	0f 84 ed eb ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849dcb:	83 bb 34 03 00 00 06 	cmpl   $0x6,0x334(%rbx)
  849dd2:	0f 84 e0 eb ff ff    	je     8489b8 <CCharacter::updateAnimation(float)+0x148>
  849dd8:	ba 07 00 00 00       	mov    $0x7,%edx
  849ddd:	be 15 00 00 00       	mov    $0x15,%esi
  849de2:	48 89 df             	mov    %rbx,%rdi
  849de5:	e8 f6 99 fc ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  849dea:	0f 2e 05 4b aa 75 00 	ucomiss 0x75aa4b(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  849df1:	f3 0f 11 44 24 6c    	movss  %xmm0,0x6c(%rsp)
  849df7:	0f 86 60 06 00 00    	jbe    84a45d <CCharacter::updateAnimation(float)+0x1bed>
  849dfd:	f3 0f 10 0d 37 aa 75 	movss  0x75aa37(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  849e04:	00
  849e05:	f3 0f 10 15 ef a9 75 	movss  0x75a9ef(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  849e0c:	00
  849e0d:	f3 0f 11 4c 24 6c    	movss  %xmm1,0x6c(%rsp)
  849e13:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  849e19:	f3 0f 10 5c 24 6c    	movss  0x6c(%rsp),%xmm3
  849e1f:	f3 0f 5e d9          	divss  %xmm1,%xmm3
  849e23:	f3 0f 58 5c 24 60    	addss  0x60(%rsp),%xmm3
  849e29:	f3 0f 11 5c 24 70    	movss  %xmm3,0x70(%rsp)
  849e2f:	48 8b bb 18 07 00 00 	mov    0x718(%rbx),%rdi
  849e36:	48 85 ff             	test   %rdi,%rdi
  849e39:	74 22                	je     849e5d <CCharacter::updateAnimation(float)+0x15ed>
  849e3b:	be 01 00 00 00       	mov    $0x1,%esi
  849e40:	e8 fb 6d 50 00       	call   d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>
  849e45:	84 c0                	test   %al,%al
  849e47:	74 14                	je     849e5d <CCharacter::updateAnimation(float)+0x15ed>
  849e49:	f3 0f 10 44 24 70    	movss  0x70(%rsp),%xmm0
  849e4f:	f3 0f 59 05 41 46 78 	mulss  0x784641(%rip),%xmm0        # fce498 <vtable for iInventoryListener+0x58>
  849e56:	00
  849e57:	f3 0f 11 44 24 70    	movss  %xmm0,0x70(%rsp)
  849e5d:	48 83 bb 40 06 00 00 	cmpq   $0x0,0x640(%rbx)
  849e64:	00
  849e65:	0f 84 a5 05 00 00    	je     84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  849e6b:	be a9 00 00 00       	mov    $0xa9,%esi
  849e70:	48 89 df             	mov    %rbx,%rdi
  849e73:	e8 28 c4 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  849e78:	84 c0                	test   %al,%al
  849e7a:	0f 85 90 05 00 00    	jne    84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  849e80:	80 bb 21 03 00 00 00 	cmpb   $0x0,0x321(%rbx)
  849e87:	0f 85 c8 08 00 00    	jne    84a755 <CCharacter::updateAnimation(float)+0x1ee5>
  849e8d:	f3 0f 10 05 77 a9 75 	movss  0x75a977(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  849e94:	00
  849e95:	0f 2e 44 24 70       	ucomiss 0x70(%rsp),%xmm0
  849e9a:	0f 97 c0             	seta   %al
  849e9d:	31 d2                	xor    %edx,%edx
  849e9f:	f3 0f 10 5c 24 70    	movss  0x70(%rsp),%xmm3
  849ea5:	f3 0f 59 9b 28 03 00 	mulss  0x328(%rbx),%xmm3
  849eac:	00
  849ead:	f3 0f 11 5c 24 6c    	movss  %xmm3,0x6c(%rsp)
  849eb3:	84 c0                	test   %al,%al
  849eb5:	74 06                	je     849ebd <CCharacter::updateAnimation(float)+0x164d>
  849eb7:	f3 0f 11 44 24 70    	movss  %xmm0,0x70(%rsp)
  849ebd:	f3 0f 5f 44 24 6c    	maxss  0x6c(%rsp),%xmm0
  849ec3:	f3 0f 11 44 24 6c    	movss  %xmm0,0x6c(%rsp)
  849ec9:	8b 83 30 03 00 00    	mov    0x330(%rbx),%eax
  849ecf:	83 f8 23             	cmp    $0x23,%eax
  849ed2:	74 3c                	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  849ed4:	80 bb 64 02 00 00 00 	cmpb   $0x0,0x264(%rbx)
  849edb:	0f 85 f5 05 00 00    	jne    84a4d6 <CCharacter::updateAnimation(float)+0x1c66>
  849ee1:	8d 50 e0             	lea    -0x20(%rax),%edx
  849ee4:	83 fa 02             	cmp    $0x2,%edx
  849ee7:	0f 87 5d 07 00 00    	ja     84a64a <CCharacter::updateAnimation(float)+0x1dda>
  849eed:	48 8b bb f0 02 00 00 	mov    0x2f0(%rbx),%rdi
  849ef4:	48 85 ff             	test   %rdi,%rdi
  849ef7:	74 17                	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  849ef9:	48 8b 07             	mov    (%rdi),%rax
  849efc:	ba 01 00 00 00       	mov    $0x1,%edx
  849f01:	be 01 00 00 00       	mov    $0x1,%esi
  849f06:	ff 90 78 03 00 00    	call   *0x378(%rax)
  849f0c:	0f 1f 40 00          	nopl   0x0(%rax)
  849f10:	f3 0f 10 44 24 6c    	movss  0x6c(%rsp),%xmm0
  849f16:	f3 0f 11 83 60 02 00 	movss  %xmm0,0x260(%rbx)
  849f1d:	00
  849f1e:	f3 0f 10 4c 24 70    	movss  0x70(%rsp),%xmm1
  849f24:	f3 0f 11 8b 5c 02 00 	movss  %xmm1,0x25c(%rbx)
  849f2b:	00
  849f2c:	e9 87 ea ff ff       	jmp    8489b8 <CCharacter::updateAnimation(float)+0x148>
  849f31:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  849f38:	44 89 f0             	mov    %r14d,%eax
  849f3b:	48 c1 e0 03          	shl    $0x3,%rax
  849f3f:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  849f46:	e9 65 fd ff ff       	jmp    849cb0 <CCharacter::updateAnimation(float)+0x1440>
  849f4b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  849f50:	44 89 f0             	mov    %r14d,%eax
  849f53:	48 c1 e0 03          	shl    $0x3,%rax
  849f57:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  849f5e:	e9 fb fb ff ff       	jmp    849b5e <CCharacter::updateAnimation(float)+0x12ee>
  849f63:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  849f68:	41 39 d6             	cmp    %edx,%r14d
  849f6b:	72 28                	jb     849f95 <CCharacter::updateAnimation(float)+0x1725>
  849f6d:	48 8b 00             	mov    (%rax),%rax
  849f70:	48 8d 70 28          	lea    0x28(%rax),%rsi
  849f74:	48 8b 78 18          	mov    0x18(%rax),%rdi
  849f78:	e8 63 d1 19 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  849f7d:	e9 6f f7 ff ff       	jmp    8496f1 <CCharacter::updateAnimation(float)+0xe81>
  849f82:	44 89 f0             	mov    %r14d,%eax
  849f85:	48 c1 e0 03          	shl    $0x3,%rax
  849f89:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  849f90:	e9 48 f7 ff ff       	jmp    8496dd <CCharacter::updateAnimation(float)+0xe6d>
  849f95:	44 89 f2             	mov    %r14d,%edx
  849f98:	48 8b 04 d0          	mov    (%rax,%rdx,8),%rax
  849f9c:	48 8d 70 28          	lea    0x28(%rax),%rsi
  849fa0:	eb d2                	jmp    849f74 <CCharacter::updateAnimation(float)+0x1704>
  849fa2:	48 8b 45 70          	mov    0x70(%rbp),%rax
  849fa6:	e9 79 f1 ff ff       	jmp    849124 <CCharacter::updateAnimation(float)+0x8b4>
  849fab:	e8 58 97 d0 ff       	call   553708 <Ogre::MaterialManager::getSingleton()@plt>
  849fb0:	48 8b 10             	mov    (%rax),%rdx
  849fb3:	4c 89 ee             	mov    %r13,%rsi
  849fb6:	48 89 c7             	mov    %rax,%rdi
  849fb9:	ff 92 b0 00 00 00    	call   *0xb0(%rdx)
  849fbf:	84 c0                	test   %al,%al
  849fc1:	0f 84 bd 07 00 00    	je     84a784 <CCharacter::updateAnimation(float)+0x1f14>
  849fc7:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  849fce:	48 85 ff             	test   %rdi,%rdi
  849fd1:	74 08                	je     849fdb <CCharacter::updateAnimation(float)+0x176b>
  849fd3:	4c 89 ee             	mov    %r13,%rsi
  849fd6:	e8 b5 00 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  849fdb:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  849fe2:	48 85 ff             	test   %rdi,%rdi
  849fe5:	0f 84 c3 f3 ff ff    	je     8493ae <CCharacter::updateAnimation(float)+0xb3e>
  849feb:	4c 89 ee             	mov    %r13,%rsi
  849fee:	e8 9d 00 20 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  849ff3:	e9 b6 f3 ff ff       	jmp    8493ae <CCharacter::updateAnimation(float)+0xb3e>
  849ff8:	48 39 c0             	cmp    %rax,%rax
  849ffb:	48 89 d6             	mov    %rdx,%rsi
  849ffe:	48 89 c1             	mov    %rax,%rcx
  84a001:	f3 a6                	repz cmpsb (%rdi),(%rsi)
  84a003:	0f 85 02 f8 ff ff    	jne    84980b <CCharacter::updateAnimation(float)+0xf9b>
  84a009:	44 8b 93 40 07 00 00 	mov    0x740(%rbx),%r10d
  84a010:	45 85 d2             	test   %r10d,%r10d
  84a013:	0f 84 1f ec ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a019:	31 ed                	xor    %ebp,%ebp
  84a01b:	eb 47                	jmp    84a064 <CCharacter::updateAnimation(float)+0x17f4>
  84a01d:	0f 1f 00             	nopl   (%rax)
  84a020:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  84a027:	48 8b 00             	mov    (%rax),%rax
  84a02a:	83 78 24 ff          	cmpl   $0xffffffff,0x24(%rax)
  84a02e:	74 25                	je     84a055 <CCharacter::updateAnimation(float)+0x17e5>
  84a030:	39 ea                	cmp    %ebp,%edx
  84a032:	77 4c                	ja     84a080 <CCharacter::updateAnimation(float)+0x1810>
  84a034:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  84a03b:	48 8b 00             	mov    (%rax),%rax
  84a03e:	48 8b 78 18          	mov    0x18(%rax),%rdi
  84a042:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  84a049:	83 f6 01             	xor    $0x1,%esi
  84a04c:	40 0f b6 f6          	movzbl %sil,%esi
  84a050:	e8 3b 02 1e 00       	call   a2a290 <CParticle::Stop(bool)>
  84a055:	83 c5 01             	add    $0x1,%ebp
  84a058:	3b ab 40 07 00 00    	cmp    0x740(%rbx),%ebp
  84a05e:	0f 83 d4 eb ff ff    	jae    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a064:	8b 93 44 07 00 00    	mov    0x744(%rbx),%edx
  84a06a:	39 ea                	cmp    %ebp,%edx
  84a06c:	76 b2                	jbe    84a020 <CCharacter::updateAnimation(float)+0x17b0>
  84a06e:	89 e8                	mov    %ebp,%eax
  84a070:	48 c1 e0 03          	shl    $0x3,%rax
  84a074:	48 03 83 38 07 00 00 	add    0x738(%rbx),%rax
  84a07b:	eb aa                	jmp    84a027 <CCharacter::updateAnimation(float)+0x17b7>
  84a07d:	0f 1f 00             	nopl   (%rax)
  84a080:	48 8b 83 38 07 00 00 	mov    0x738(%rbx),%rax
  84a087:	89 ea                	mov    %ebp,%edx
  84a089:	48 8b 04 d0          	mov    (%rax,%rdx,8),%rax
  84a08d:	48 8b 78 18          	mov    0x18(%rax),%rdi
  84a091:	0f b6 b7 81 00 00 00 	movzbl 0x81(%rdi),%esi
  84a098:	83 f6 01             	xor    $0x1,%esi
  84a09b:	40 0f b6 f6          	movzbl %sil,%esi
  84a09f:	eb af                	jmp    84a050 <CCharacter::updateAnimation(float)+0x17e0>
  84a0a1:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84a0a8:	f3 0f 10 05 4c a7 75 	movss  0x75a74c(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84a0af:	00
  84a0b0:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84a0b7:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  84a0bb:	48 8b 40 50          	mov    0x50(%rax),%rax
  84a0bf:	c6 80 99 00 00 00 00 	movb   $0x0,0x99(%rax)
  84a0c6:	e9 e4 ee ff ff       	jmp    848faf <CCharacter::updateAnimation(float)+0x73f>
  84a0cb:	48 83 bb 98 06 00 00 	cmpq   $0x0,0x698(%rbx)
  84a0d2:	00
  84a0d3:	0f 84 5f eb ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a0d9:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  84a0e0:	31 f6                	xor    %esi,%esi
  84a0e2:	e8 79 13 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84a0e7:	49 39 c5             	cmp    %rax,%r13
  84a0ea:	0f 85 48 eb ff ff    	jne    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a0f0:	48 8b bb 98 04 00 00 	mov    0x498(%rbx),%rdi
  84a0f7:	be 66 00 00 00       	mov    $0x66,%esi
  84a0fc:	e8 9f c1 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84a101:	84 c0                	test   %al,%al
  84a103:	0f 85 2f eb ff ff    	jne    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a109:	e9 e0 02 00 00       	jmp    84a3ee <CCharacter::updateAnimation(float)+0x1b7e>
  84a10e:	66 90                	xchg   %ax,%ax
  84a110:	48 83 bb 98 06 00 00 	cmpq   $0x0,0x698(%rbx)
  84a117:	00
  84a118:	0f 84 91 f1 ff ff    	je     8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a11e:	4c 8b ab 98 04 00 00 	mov    0x498(%rbx),%r13
  84a125:	4d 85 ed             	test   %r13,%r13
  84a128:	0f 84 81 f1 ff ff    	je     8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a12e:	48 8b bb 90 04 00 00 	mov    0x490(%rbx),%rdi
  84a135:	31 f6                	xor    %esi,%esi
  84a137:	e8 24 13 0d 00       	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84a13c:	49 39 c5             	cmp    %rax,%r13
  84a13f:	0f 85 6a f1 ff ff    	jne    8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a145:	48 8b bb 98 04 00 00 	mov    0x498(%rbx),%rdi
  84a14c:	be 66 00 00 00       	mov    $0x66,%esi
  84a151:	e8 4a c1 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84a156:	84 c0                	test   %al,%al
  84a158:	0f 85 51 f1 ff ff    	jne    8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a15e:	48 8b bb 98 04 00 00 	mov    0x498(%rbx),%rdi
  84a165:	48 8b 07             	mov    (%rdi),%rax
  84a168:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  84a16e:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a175:	48 8b 70 60          	mov    0x60(%rax),%rsi
  84a179:	e8 f2 fd 1f 00       	call   a49f70 <CWeaponTrail::setWeaponEntity(Ogre::Entity*)>
  84a17e:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a185:	be 01 00 00 00       	mov    $0x1,%esi
  84a18a:	e8 91 fe 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84a18f:	48 8b 83 98 06 00 00 	mov    0x698(%rbx),%rax
  84a196:	e9 0c 01 00 00       	jmp    84a2a7 <CCharacter::updateAnimation(float)+0x1a37>
  84a19b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  84a1a0:	41 83 fd 01          	cmp    $0x1,%r13d
  84a1a4:	0f 8e 20 01 00 00    	jle    84a2ca <CCharacter::updateAnimation(float)+0x1a5a>
  84a1aa:	48 83 bb a0 06 00 00 	cmpq   $0x0,0x6a0(%rbx)
  84a1b1:	00
  84a1b2:	0f 84 85 0a 00 00    	je     84ac3d <CCharacter::updateAnimation(float)+0x23cd>
  84a1b8:	4c 8d b4 24 b0 00 00 	lea    0xb0(%rsp),%r14
  84a1bf:	00
  84a1c0:	48 8d 70 20          	lea    0x20(%rax),%rsi
  84a1c4:	4c 89 f7             	mov    %r14,%rdi
  84a1c7:	e8 dc 87 d0 ff       	call   5529a8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&)@plt>
  84a1cc:	be f7 57 02 01       	mov    $0x10257f7,%esi
  84a1d1:	4c 89 f7             	mov    %r14,%rdi
  84a1d4:	e8 3f bb d0 ff       	call   555d18 <std::string::compare(char const*) const@plt>
  84a1d9:	85 c0                	test   %eax,%eax
  84a1db:	0f 85 75 09 00 00    	jne    84ab56 <CCharacter::updateAnimation(float)+0x22e6>
  84a1e1:	4c 89 f7             	mov    %r14,%rdi
  84a1e4:	e8 9f c0 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a1e9:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84a1f0:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84a1f7:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  84a1fb:	e9 c1 f0 ff ff       	jmp    8492c1 <CCharacter::updateAnimation(float)+0xa51>
  84a200:	83 fd 01             	cmp    $0x1,%ebp
  84a203:	0f 8e c8 01 00 00    	jle    84a3d1 <CCharacter::updateAnimation(float)+0x1b61>
  84a209:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a210:	48 85 ff             	test   %rdi,%rdi
  84a213:	0f 84 1f ea ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a219:	e8 f2 fd 1f 00       	call   a4a010 <CWeaponTrail::isVisible() const>
  84a21e:	84 c0                	test   %al,%al
  84a220:	0f 84 12 ea ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a226:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a22d:	31 f6                	xor    %esi,%esi
  84a22f:	e8 ec fd 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84a234:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a23b:	31 f6                	xor    %esi,%esi
  84a23d:	e8 be fc 1f 00       	call   a49f00 <CWeaponTrail::setVisible(bool)>
  84a242:	e9 f1 e9 ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a247:	48 83 bb a0 06 00 00 	cmpq   $0x0,0x6a0(%rbx)
  84a24e:	00
  84a24f:	0f 84 5a f0 ff ff    	je     8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a255:	4d 85 f6             	test   %r14,%r14
  84a258:	0f 84 51 f0 ff ff    	je     8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a25e:	be 66 00 00 00       	mov    $0x66,%esi
  84a263:	4c 89 f7             	mov    %r14,%rdi
  84a266:	e8 35 c0 fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84a26b:	84 c0                	test   %al,%al
  84a26d:	0f 85 3c f0 ff ff    	jne    8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a273:	49 8b 06             	mov    (%r14),%rax
  84a276:	4c 89 f7             	mov    %r14,%rdi
  84a279:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  84a27f:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a286:	48 8b 70 60          	mov    0x60(%rax),%rsi
  84a28a:	e8 e1 fc 1f 00       	call   a49f70 <CWeaponTrail::setWeaponEntity(Ogre::Entity*)>
  84a28f:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a296:	be 01 00 00 00       	mov    $0x1,%esi
  84a29b:	e8 80 fd 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84a2a0:	48 8b 83 a0 06 00 00 	mov    0x6a0(%rbx),%rax
  84a2a7:	c7 80 90 00 00 00 00 	movl   $0x0,0x90(%rax)
  84a2ae:	00 00 00
  84a2b1:	c7 80 94 00 00 00 00 	movl   $0x0,0x94(%rax)
  84a2b8:	00 00 00
  84a2bb:	c7 80 98 00 00 00 00 	movl   $0x0,0x98(%rax)
  84a2c2:	00 00 00
  84a2c5:	e9 e5 ef ff ff       	jmp    8492af <CCharacter::updateAnimation(float)+0xa3f>
  84a2ca:	48 83 bb 98 06 00 00 	cmpq   $0x0,0x698(%rbx)
  84a2d1:	00
  84a2d2:	0f 85 e0 fe ff ff    	jne    84a1b8 <CCharacter::updateAnimation(float)+0x1948>
  84a2d8:	48 8b 43 68          	mov    0x68(%rbx),%rax
  84a2dc:	48 c7 44 24 70 00 00 	movq   $0x0,0x70(%rsp)
  84a2e3:	00 00
  84a2e5:	48 85 c0             	test   %rax,%rax
  84a2e8:	74 09                	je     84a2f3 <CCharacter::updateAnimation(float)+0x1a83>
  84a2ea:	48 8b 40 10          	mov    0x10(%rax),%rax
  84a2ee:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  84a2f3:	48 8d 94 24 3d 04 00 	lea    0x43d(%rsp),%rdx
  84a2fa:	00
  84a2fb:	48 8d bc 24 d0 03 00 	lea    0x3d0(%rsp),%rdi
  84a302:	00
  84a303:	be 08 99 fc 00       	mov    $0xfc9908,%esi
  84a308:	e8 eb bf d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a30d:	4c 8d b4 24 c0 03 00 	lea    0x3c0(%rsp),%r14
  84a314:	00
  84a315:	48 8d b4 24 d0 03 00 	lea    0x3d0(%rsp),%rsi
  84a31c:	00
  84a31d:	4c 89 f7             	mov    %r14,%rdi
  84a320:	e8 2b 47 44 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  84a325:	bf a0 00 00 00       	mov    $0xa0,%edi
  84a32a:	e8 91 09 01 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  84a32f:	48 8b 74 24 70       	mov    0x70(%rsp),%rsi
  84a334:	f3 0f 10 05 c0 a4 75 	movss  0x75a4c0(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84a33b:	00
  84a33c:	b9 14 00 00 00       	mov    $0x14,%ecx
  84a341:	4c 89 f2             	mov    %r14,%rdx
  84a344:	48 89 c7             	mov    %rax,%rdi
  84a347:	48 89 44 24 60       	mov    %rax,0x60(%rsp)
  84a34c:	e8 cf 27 20 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  84a351:	48 8b 54 24 60       	mov    0x60(%rsp),%rdx
  84a356:	4c 89 f7             	mov    %r14,%rdi
  84a359:	48 89 93 98 06 00 00 	mov    %rdx,0x698(%rbx)
  84a360:	e8 23 bf d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a365:	48 8d bc 24 d0 03 00 	lea    0x3d0(%rsp),%rdi
  84a36c:	00
  84a36d:	e8 16 bf d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a372:	48 89 df             	mov    %rbx,%rdi
  84a375:	e8 f6 5d fc ff       	call   810170 <CCharacter::alignment()>
  84a37a:	4c 8d b4 24 b0 03 00 	lea    0x3b0(%rsp),%r14
  84a381:	00
  84a382:	83 f8 01             	cmp    $0x1,%eax
  84a385:	be 34 05 fa 00       	mov    $0xfa0534,%esi
  84a38a:	b8 40 05 fa 00       	mov    $0xfa0540,%eax
  84a38f:	48 8d 94 24 3c 04 00 	lea    0x43c(%rsp),%rdx
  84a396:	00
  84a397:	48 0f 45 f0          	cmovne %rax,%rsi
  84a39b:	4c 89 f7             	mov    %r14,%rdi
  84a39e:	e8 55 bf d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a3a3:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a3aa:	4c 89 f6             	mov    %r14,%rsi
  84a3ad:	e8 de fc 1f 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  84a3b2:	4c 89 f7             	mov    %r14,%rdi
  84a3b5:	e8 ce be d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a3ba:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84a3c1:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84a3c8:	48 8b 04 e8          	mov    (%rax,%rbp,8),%rax
  84a3cc:	e9 e7 fd ff ff       	jmp    84a1b8 <CCharacter::updateAnimation(float)+0x1948>
  84a3d1:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a3d8:	48 85 ff             	test   %rdi,%rdi
  84a3db:	0f 84 57 e8 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a3e1:	e8 2a fc 1f 00       	call   a4a010 <CWeaponTrail::isVisible() const>
  84a3e6:	84 c0                	test   %al,%al
  84a3e8:	0f 84 4a e8 ff ff    	je     848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a3ee:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a3f5:	31 f6                	xor    %esi,%esi
  84a3f7:	e8 24 fc 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84a3fc:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a403:	31 f6                	xor    %esi,%esi
  84a405:	e8 f6 fa 1f 00       	call   a49f00 <CWeaponTrail::setVisible(bool)>
  84a40a:	e9 29 e8 ff ff       	jmp    848c38 <CCharacter::updateAnimation(float)+0x3c8>
  84a40f:	90                   	nop
  84a410:	f3 0f 10 05 f4 a3 75 	movss  0x75a3f4(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  84a417:	00
  84a418:	0f b6 93 21 03 00 00 	movzbl 0x321(%rbx),%edx
  84a41f:	0f 2e 44 24 70       	ucomiss 0x70(%rsp),%xmm0
  84a424:	0f 97 c0             	seta   %al
  84a427:	84 d2                	test   %dl,%dl
  84a429:	0f 84 70 fa ff ff    	je     849e9f <CCharacter::updateAnimation(float)+0x162f>
  84a42f:	f3 0f 10 8b 90 02 00 	movss  0x290(%rbx),%xmm1
  84a436:	00
  84a437:	0f 2e 8b 8c 02 00 00 	ucomiss 0x28c(%rbx),%xmm1
  84a43e:	0f 86 5b fa ff ff    	jbe    849e9f <CCharacter::updateAnimation(float)+0x162f>
  84a444:	f3 0f 10 5c 24 70    	movss  0x70(%rsp),%xmm3
  84a44a:	f3 0f 59 9b 2c 03 00 	mulss  0x32c(%rbx),%xmm3
  84a451:	00
  84a452:	f3 0f 11 5c 24 6c    	movss  %xmm3,0x6c(%rsp)
  84a458:	e9 56 fa ff ff       	jmp    849eb3 <CCharacter::updateAnimation(float)+0x1643>
  84a45d:	0f 57 d2             	xorps  %xmm2,%xmm2
  84a460:	0f 2e 54 24 6c       	ucomiss 0x6c(%rsp),%xmm2
  84a465:	0f 86 5c 04 00 00    	jbe    84a8c7 <CCharacter::updateAnimation(float)+0x2057>
  84a46b:	ba 07 00 00 00       	mov    $0x7,%edx
  84a470:	be 8c 00 00 00       	mov    $0x8c,%esi
  84a475:	48 89 df             	mov    %rbx,%rdi
  84a478:	e8 63 93 fc ff       	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84a47d:	f3 0f 10 0d b7 a3 75 	movss  0x75a3b7(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84a484:	00
  84a485:	f3 0f 5e c1          	divss  %xmm1,%xmm0
  84a489:	f3 0f 10 15 6b a3 75 	movss  0x75a36b(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84a490:	00
  84a491:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  84a497:	0f 2e d0             	ucomiss %xmm0,%xmm2
  84a49a:	0f 87 37 05 00 00    	ja     84a9d7 <CCharacter::updateAnimation(float)+0x2167>
  84a4a0:	0f 28 c2             	movaps %xmm2,%xmm0
  84a4a3:	f3 0f 10 54 24 60    	movss  0x60(%rsp),%xmm2
  84a4a9:	f3 0f 5c d0          	subss  %xmm0,%xmm2
  84a4ad:	f3 0f 10 44 24 6c    	movss  0x6c(%rsp),%xmm0
  84a4b3:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  84a4b7:	f3 0f 11 44 24 6c    	movss  %xmm0,0x6c(%rsp)
  84a4bd:	f3 0f 10 05 cb 3f 78 	movss  0x783fcb(%rip),%xmm0        # fce490 <vtable for iInventoryListener+0x50>
  84a4c4:	00
  84a4c5:	f3 0f 5f 44 24 6c    	maxss  0x6c(%rsp),%xmm0
  84a4cb:	f3 0f 11 44 24 6c    	movss  %xmm0,0x6c(%rsp)
  84a4d1:	e9 43 f9 ff ff       	jmp    849e19 <CCharacter::updateAnimation(float)+0x15a9>
  84a4d6:	48 8b 8b 98 03 00 00 	mov    0x398(%rbx),%rcx
  84a4dd:	48 85 c9             	test   %rcx,%rcx
  84a4e0:	0f 84 5a 01 00 00    	je     84a640 <CCharacter::updateAnimation(float)+0x1dd0>
  84a4e6:	80 79 68 00          	cmpb   $0x0,0x68(%rcx)
  84a4ea:	0f 84 50 01 00 00    	je     84a640 <CCharacter::updateAnimation(float)+0x1dd0>
  84a4f0:	83 b9 ec 00 00 00 ff 	cmpl   $0xffffffff,0xec(%rcx)
  84a4f7:	74 0a                	je     84a503 <CCharacter::updateAnimation(float)+0x1c93>
  84a4f9:	80 79 64 00          	cmpb   $0x0,0x64(%rcx)
  84a4fd:	0f 84 3d 01 00 00    	je     84a640 <CCharacter::updateAnimation(float)+0x1dd0>
  84a503:	31 c9                	xor    %ecx,%ecx
  84a505:	80 bb 67 02 00 00 00 	cmpb   $0x0,0x267(%rbx)
  84a50c:	75 11                	jne    84a51f <CCharacter::updateAnimation(float)+0x1caf>
  84a50e:	0f 57 db             	xorps  %xmm3,%xmm3
  84a511:	f3 0f 10 83 80 03 00 	movss  0x380(%rbx),%xmm0
  84a518:	00
  84a519:	0f 2e c3             	ucomiss %xmm3,%xmm0
  84a51c:	0f 96 c1             	setbe  %cl
  84a51f:	83 f8 10             	cmp    $0x10,%eax
  84a522:	0f 84 e8 f9 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a528:	84 c9                	test   %cl,%cl
  84a52a:	0f 84 e0 f9 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a530:	84 d2                	test   %dl,%dl
  84a532:	0f 84 cb 04 00 00    	je     84aa03 <CCharacter::updateAnimation(float)+0x2193>
  84a538:	f3 0f 10 83 90 02 00 	movss  0x290(%rbx),%xmm0
  84a53f:	00
  84a540:	0f 2e 83 8c 02 00 00 	ucomiss 0x28c(%rbx),%xmm0
  84a547:	0f 86 b6 04 00 00    	jbe    84aa03 <CCharacter::updateAnimation(float)+0x2193>
  84a54d:	48 8d ac 24 40 02 00 	lea    0x240(%rsp),%rbp
  84a554:	00
  84a555:	48 8d 94 24 27 04 00 	lea    0x427(%rsp),%rdx
  84a55c:	00
  84a55d:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84a562:	48 89 ef             	mov    %rbp,%rdi
  84a565:	e8 8e bd d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a56a:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84a571:	48 89 ee             	mov    %rbp,%rsi
  84a574:	e8 47 80 05 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  84a579:	48 89 ef             	mov    %rbp,%rdi
  84a57c:	41 89 c4             	mov    %eax,%r12d
  84a57f:	e8 04 bd d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a584:	45 84 e4             	test   %r12b,%r12b
  84a587:	0f 84 97 07 00 00    	je     84ad24 <CCharacter::updateAnimation(float)+0x24b4>
  84a58d:	48 8d ac 24 30 02 00 	lea    0x230(%rsp),%rbp
  84a594:	00
  84a595:	48 8d 94 24 26 04 00 	lea    0x426(%rsp),%rdx
  84a59c:	00
  84a59d:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84a5a2:	48 89 ef             	mov    %rbp,%rdi
  84a5a5:	e8 4e bd d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a5aa:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84a5b1:	48 89 ee             	mov    %rbp,%rsi
  84a5b4:	e8 a7 d2 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84a5b9:	48 89 ef             	mov    %rbp,%rdi
  84a5bc:	41 89 c4             	mov    %eax,%r12d
  84a5bf:	e8 c4 bc d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a5c4:	45 84 e4             	test   %r12b,%r12b
  84a5c7:	0f 84 ad 0a 00 00    	je     84b07a <CCharacter::updateAnimation(float)+0x280a>
  84a5cd:	f3 0f 10 4c 24 6c    	movss  0x6c(%rsp),%xmm1
  84a5d3:	0f 2e 8b 60 02 00 00 	ucomiss 0x260(%rbx),%xmm1
  84a5da:	7a 06                	jp     84a5e2 <CCharacter::updateAnimation(float)+0x1d72>
  84a5dc:	0f 84 2e f9 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a5e2:	f3 0f 10 54 24 60    	movss  0x60(%rsp),%xmm2
  84a5e8:	48 8d ac 24 10 02 00 	lea    0x210(%rsp),%rbp
  84a5ef:	00
  84a5f0:	f3 0f 5e 93 98 00 00 	divss  0x98(%rbx),%xmm2
  84a5f7:	00
  84a5f8:	48 8d 94 24 24 04 00 	lea    0x424(%rsp),%rdx
  84a5ff:	00
  84a600:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84a605:	48 89 ef             	mov    %rbp,%rdi
  84a608:	f3 0f 59 d1          	mulss  %xmm1,%xmm2
  84a60c:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  84a612:	e8 e1 bc d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a617:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84a61e:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84a624:	48 89 ee             	mov    %rbp,%rsi
  84a627:	e8 74 ce 05 00       	call   8a74a0 <CGenericModel::setAnimationSpeed(std::string const&, float)>
  84a62c:	48 89 ef             	mov    %rbp,%rdi
  84a62f:	e8 54 bc d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a634:	e9 d7 f8 ff ff       	jmp    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a639:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  84a640:	b9 01 00 00 00       	mov    $0x1,%ecx
  84a645:	e9 d5 fe ff ff       	jmp    84a51f <CCharacter::updateAnimation(float)+0x1caf>
  84a64a:	83 f8 10             	cmp    $0x10,%eax
  84a64d:	0f 1f 00             	nopl   (%rax)
  84a650:	0f 84 ba f8 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a656:	83 f8 0c             	cmp    $0xc,%eax
  84a659:	0f 84 b1 f8 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a65f:	48 8b 7b 68          	mov    0x68(%rbx),%rdi
  84a663:	e8 78 4e 52 00       	call   d6f4e0 <CResourceManager::getEditorIsRunning()>
  84a668:	84 c0                	test   %al,%al
  84a66a:	0f 85 a0 f8 ff ff    	jne    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a670:	45 31 e4             	xor    %r12d,%r12d
  84a673:	80 bb 65 02 00 00 00 	cmpb   $0x0,0x265(%rbx)
  84a67a:	0f 85 fc 07 00 00    	jne    84ae7c <CCharacter::updateAnimation(float)+0x260c>
  84a680:	45 31 e4             	xor    %r12d,%r12d
  84a683:	83 bb 30 03 00 00 28 	cmpl   $0x28,0x330(%rbx)
  84a68a:	0f 84 ba 0b 00 00    	je     84b24a <CCharacter::updateAnimation(float)+0x29da>
  84a690:	be a7 00 00 00       	mov    $0xa7,%esi
  84a695:	48 89 df             	mov    %rbx,%rdi
  84a698:	45 31 f6             	xor    %r14d,%r14d
  84a69b:	45 31 ed             	xor    %r13d,%r13d
  84a69e:	e8 fd bb fa ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84a6a3:	84 c0                	test   %al,%al
  84a6a5:	0f 85 8e 0c 00 00    	jne    84b339 <CCharacter::updateAnimation(float)+0x2ac9>
  84a6ab:	48 8d ac 24 70 02 00 	lea    0x270(%rsp),%rbp
  84a6b2:	00
  84a6b3:	48 8d 94 24 2a 04 00 	lea    0x42a(%rsp),%rdx
  84a6ba:	00
  84a6bb:	be 3a 99 fc 00       	mov    $0xfc993a,%esi
  84a6c0:	48 89 ef             	mov    %rbp,%rdi
  84a6c3:	e8 30 bc d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a6c8:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84a6cf:	48 89 ee             	mov    %rbp,%rsi
  84a6d2:	e8 89 d1 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84a6d7:	48 89 ef             	mov    %rbp,%rdi
  84a6da:	41 89 c4             	mov    %eax,%r12d
  84a6dd:	e8 a6 bb d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a6e2:	45 84 e4             	test   %r12b,%r12b
  84a6e5:	0f 84 f9 09 00 00    	je     84b0e4 <CCharacter::updateAnimation(float)+0x2874>
  84a6eb:	f3 0f 10 83 80 02 00 	movss  0x280(%rbx),%xmm0
  84a6f2:	00
  84a6f3:	0f 2e 05 e6 df 75 00 	ucomiss 0x75dfe6(%rip),%xmm0        # fa86e0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x40>
  84a6fa:	0f 86 10 f8 ff ff    	jbe    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a700:	48 83 bb 98 02 00 00 	cmpq   $0x0,0x298(%rbx)
  84a707:	00
  84a708:	0f 84 02 f8 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a70e:	e8 25 b1 d0 ff       	call   555838 <rand@plt>
  84a713:	89 c2                	mov    %eax,%edx
  84a715:	b9 e8 03 00 00       	mov    $0x3e8,%ecx
  84a71a:	c1 fa 1f             	sar    $0x1f,%edx
  84a71d:	f7 f9                	idiv   %ecx
  84a71f:	83 fa 04             	cmp    $0x4,%edx
  84a722:	0f 8f e8 f7 ff ff    	jg     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a728:	0f 57 c9             	xorps  %xmm1,%xmm1
  84a72b:	48 8b 53 58          	mov    0x58(%rbx),%rdx
  84a72f:	48 8b bb 98 02 00 00 	mov    0x298(%rbx),%rdi
  84a736:	66 31 c9             	xor    %cx,%cx
  84a739:	be 0b 00 00 00       	mov    $0xb,%esi
  84a73e:	0f 28 c1             	movaps %xmm1,%xmm0
  84a741:	e8 5a f1 21 00       	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  84a746:	c7 83 80 02 00 00 00 	movl   $0x0,0x280(%rbx)
  84a74d:	00 00 00
  84a750:	e9 bb f7 ff ff       	jmp    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84a755:	f3 0f 10 83 90 02 00 	movss  0x290(%rbx),%xmm0
  84a75c:	00
  84a75d:	0f 2e 83 8c 02 00 00 	ucomiss 0x28c(%rbx),%xmm0
  84a764:	0f 87 59 03 00 00    	ja     84aac3 <CCharacter::updateAnimation(float)+0x2253>
  84a76a:	f3 0f 10 05 9a a0 75 	movss  0x75a09a(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  84a771:	00
  84a772:	ba 01 00 00 00       	mov    $0x1,%edx
  84a777:	0f 2e 44 24 70       	ucomiss 0x70(%rsp),%xmm0
  84a77c:	0f 97 c0             	seta   %al
  84a77f:	e9 1b f7 ff ff       	jmp    849e9f <CCharacter::updateAnimation(float)+0x162f>
  84a784:	e8 7f 8f d0 ff       	call   553708 <Ogre::MaterialManager::getSingleton()@plt>
  84a789:	48 8b 28             	mov    (%rax),%rbp
  84a78c:	4c 8d b4 24 90 00 00 	lea    0x90(%rsp),%r14
  84a793:	00
  84a794:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  84a79b:	00
  84a79c:	45 31 c9             	xor    %r9d,%r9d
  84a79f:	45 31 c0             	xor    %r8d,%r8d
  84a7a2:	b9 40 44 42 01       	mov    $0x1424440,%ecx
  84a7a7:	4c 89 ea             	mov    %r13,%rdx
  84a7aa:	48 89 c6             	mov    %rax,%rsi
  84a7ad:	4c 89 f7             	mov    %r14,%rdi
  84a7b0:	ff 55 28             	call   *0x28(%rbp)
  84a7b3:	48 8b 84 24 98 00 00 	mov    0x98(%rsp),%rax
  84a7ba:	00
  84a7bb:	c7 84 24 c8 00 00 00 	movl   $0x0,0xc8(%rsp)
  84a7c2:	00 00 00 00
  84a7c6:	48 c7 84 24 b0 00 00 	movq   $0xfa44d0,0xb0(%rsp)
  84a7cd:	00 d0 44 fa 00
  84a7d2:	48 89 84 24 b8 00 00 	mov    %rax,0xb8(%rsp)
  84a7d9:	00
  84a7da:	48 8b 84 24 a0 00 00 	mov    0xa0(%rsp),%rax
  84a7e1:	00
  84a7e2:	48 85 c0             	test   %rax,%rax
  84a7e5:	48 89 84 24 c0 00 00 	mov    %rax,0xc0(%rsp)
  84a7ec:	00
  84a7ed:	74 03                	je     84a7f2 <CCharacter::updateAnimation(float)+0x1f82>
  84a7ef:	83 00 01             	addl   $0x1,(%rax)
  84a7f2:	4c 89 f7             	mov    %r14,%rdi
  84a7f5:	e8 e6 00 d2 ff       	call   56a8e0 <Ogre::SharedPtr<Ogre::Resource>::~SharedPtr()>
  84a7fa:	48 8b 84 24 b8 00 00 	mov    0xb8(%rsp),%rax
  84a801:	00
  84a802:	31 f6                	xor    %esi,%esi
  84a804:	c6 80 f0 00 00 00 00 	movb   $0x0,0xf0(%rax)
  84a80b:	48 8b bc 24 b8 00 00 	mov    0xb8(%rsp),%rdi
  84a812:	00
  84a813:	e8 90 85 d0 ff       	call   552da8 <Ogre::Material::setLightingEnabled(bool)@plt>
  84a818:	48 8b bc 24 b8 00 00 	mov    0xb8(%rsp),%rdi
  84a81f:	00
  84a820:	31 f6                	xor    %esi,%esi
  84a822:	e8 e1 89 d0 ff       	call   553208 <Ogre::Material::getTechnique(unsigned short)@plt>
  84a827:	31 f6                	xor    %esi,%esi
  84a829:	48 89 c7             	mov    %rax,%rdi
  84a82c:	e8 b7 91 d0 ff       	call   5539e8 <Ogre::Technique::getPass(unsigned short)@plt>
  84a831:	be 01 00 00 00       	mov    $0x1,%esi
  84a836:	48 89 c7             	mov    %rax,%rdi
  84a839:	48 89 c5             	mov    %rax,%rbp
  84a83c:	e8 87 95 d0 ff       	call   553dc8 <Ogre::Pass::setDepthCheckEnabled(bool)@plt>
  84a841:	0f 57 d2             	xorps  %xmm2,%xmm2
  84a844:	48 89 ef             	mov    %rbp,%rdi
  84a847:	0f 28 ca             	movaps %xmm2,%xmm1
  84a84a:	0f 28 c2             	movaps %xmm2,%xmm0
  84a84d:	e8 86 a4 d0 ff       	call   554cd8 <Ogre::Pass::setSelfIllumination(float, float, float)@plt>
  84a852:	31 f6                	xor    %esi,%esi
  84a854:	48 89 ef             	mov    %rbp,%rdi
  84a857:	e8 4c 9c d0 ff       	call   5544a8 <Ogre::Pass::setDepthWriteEnabled(bool)@plt>
  84a85c:	48 8b bc 24 b8 00 00 	mov    0xb8(%rsp),%rdi
  84a863:	00
  84a864:	be 02 00 00 00       	mov    $0x2,%esi
  84a869:	e8 0a b6 d0 ff       	call   555e78 <Ogre::Material::setSceneBlending(Ogre::SceneBlendType)@plt>
  84a86e:	48 8b bc 24 b8 00 00 	mov    0xb8(%rsp),%rdi
  84a875:	00
  84a876:	be 01 00 00 00       	mov    $0x1,%esi
  84a87b:	e8 68 aa d0 ff       	call   5552e8 <Ogre::Material::setCullingMode(Ogre::CullingMode)@plt>
  84a880:	31 d2                	xor    %edx,%edx
  84a882:	4c 89 ee             	mov    %r13,%rsi
  84a885:	48 89 ef             	mov    %rbp,%rdi
  84a888:	e8 8b 92 d0 ff       	call   553b18 <Ogre::Pass::createTextureUnitState(std::string const&, unsigned short)@plt>
  84a88d:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84a894:	48 85 ff             	test   %rdi,%rdi
  84a897:	74 08                	je     84a8a1 <CCharacter::updateAnimation(float)+0x2031>
  84a899:	4c 89 ee             	mov    %r13,%rsi
  84a89c:	e8 ef f7 1f 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  84a8a1:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a8a8:	48 85 ff             	test   %rdi,%rdi
  84a8ab:	74 08                	je     84a8b5 <CCharacter::updateAnimation(float)+0x2045>
  84a8ad:	4c 89 ee             	mov    %r13,%rsi
  84a8b0:	e8 db f7 1f 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  84a8b5:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  84a8bc:	00
  84a8bd:	e8 4e 08 d2 ff       	call   56b110 <Ogre::MaterialPtr::~MaterialPtr()>
  84a8c2:	e9 e7 ea ff ff       	jmp    8493ae <CCharacter::updateAnimation(float)+0xb3e>
  84a8c7:	f3 0f 10 1d 2d 9f 75 	movss  0x759f2d(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84a8ce:	00
  84a8cf:	f3 0f 11 5c 24 60    	movss  %xmm3,0x60(%rsp)
  84a8d5:	f3 0f 10 0d 5f 9f 75 	movss  0x759f5f(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84a8dc:	00
  84a8dd:	e9 db fb ff ff       	jmp    84a4bd <CCharacter::updateAnimation(float)+0x1c4d>
  84a8e2:	48 8b 43 68          	mov    0x68(%rbx),%rax
  84a8e6:	48 c7 44 24 70 00 00 	movq   $0x0,0x70(%rsp)
  84a8ed:	00 00
  84a8ef:	48 85 c0             	test   %rax,%rax
  84a8f2:	74 09                	je     84a8fd <CCharacter::updateAnimation(float)+0x208d>
  84a8f4:	48 8b 40 10          	mov    0x10(%rax),%rax
  84a8f8:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  84a8fd:	48 8d 94 24 3b 04 00 	lea    0x43b(%rsp),%rdx
  84a904:	00
  84a905:	48 8d bc 24 a0 03 00 	lea    0x3a0(%rsp),%rdi
  84a90c:	00
  84a90d:	be 08 99 fc 00       	mov    $0xfc9908,%esi
  84a912:	e8 e1 b9 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a917:	48 8d b4 24 a0 03 00 	lea    0x3a0(%rsp),%rsi
  84a91e:	00
  84a91f:	48 8d bc 24 90 03 00 	lea    0x390(%rsp),%rdi
  84a926:	00
  84a927:	e8 24 41 44 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  84a92c:	bf a0 00 00 00       	mov    $0xa0,%edi
  84a931:	e8 8a 03 01 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  84a936:	48 8b 74 24 70       	mov    0x70(%rsp),%rsi
  84a93b:	48 8d 94 24 90 03 00 	lea    0x390(%rsp),%rdx
  84a942:	00
  84a943:	b9 14 00 00 00       	mov    $0x14,%ecx
  84a948:	f3 0f 10 05 ac 9e 75 	movss  0x759eac(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84a94f:	00
  84a950:	48 89 c7             	mov    %rax,%rdi
  84a953:	48 89 44 24 60       	mov    %rax,0x60(%rsp)
  84a958:	e8 c3 21 20 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  84a95d:	48 8b 4c 24 60       	mov    0x60(%rsp),%rcx
  84a962:	48 8d bc 24 90 03 00 	lea    0x390(%rsp),%rdi
  84a969:	00
  84a96a:	48 89 8b a0 06 00 00 	mov    %rcx,0x6a0(%rbx)
  84a971:	e8 12 b9 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a976:	48 8d bc 24 a0 03 00 	lea    0x3a0(%rsp),%rdi
  84a97d:	00
  84a97e:	e8 05 b9 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a983:	48 89 df             	mov    %rbx,%rdi
  84a986:	e8 e5 57 fc ff       	call   810170 <CCharacter::alignment()>
  84a98b:	83 f8 01             	cmp    $0x1,%eax
  84a98e:	be 34 05 fa 00       	mov    $0xfa0534,%esi
  84a993:	b8 40 05 fa 00       	mov    $0xfa0540,%eax
  84a998:	48 8d 94 24 3a 04 00 	lea    0x43a(%rsp),%rdx
  84a99f:	00
  84a9a0:	48 8d bc 24 80 03 00 	lea    0x380(%rsp),%rdi
  84a9a7:	00
  84a9a8:	48 0f 45 f0          	cmovne %rax,%rsi
  84a9ac:	e8 47 b9 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a9b1:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84a9b8:	48 8d b4 24 80 03 00 	lea    0x380(%rsp),%rsi
  84a9bf:	00
  84a9c0:	e8 cb f6 1f 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  84a9c5:	48 8d bc 24 80 03 00 	lea    0x380(%rsp),%rdi
  84a9cc:	00
  84a9cd:	e8 b6 b8 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a9d2:	e9 ce e8 ff ff       	jmp    8492a5 <CCharacter::updateAnimation(float)+0xa35>
  84a9d7:	0f 57 db             	xorps  %xmm3,%xmm3
  84a9da:	f3 0f 5f c3          	maxss  %xmm3,%xmm0
  84a9de:	e9 c0 fa ff ff       	jmp    84a4a3 <CCharacter::updateAnimation(float)+0x1c33>
  84a9e3:	8b 85 80 00 00 00    	mov    0x80(%rbp),%eax
  84a9e9:	89 c7                	mov    %eax,%edi
  84a9eb:	89 45 7c             	mov    %eax,0x7c(%rbp)
  84a9ee:	48 c1 e7 03          	shl    $0x3,%rdi
  84a9f2:	e8 f1 90 d0 ff       	call   553ae8 <operator new[](unsigned long)@plt>
  84a9f7:	8b 55 78             	mov    0x78(%rbp),%edx
  84a9fa:	48 89 45 70          	mov    %rax,0x70(%rbp)
  84a9fe:	e9 21 e7 ff ff       	jmp    849124 <CCharacter::updateAnimation(float)+0x8b4>
  84aa03:	48 8d ac 24 d0 01 00 	lea    0x1d0(%rsp),%rbp
  84aa0a:	00
  84aa0b:	48 8d 94 24 20 04 00 	lea    0x420(%rsp),%rdx
  84aa12:	00
  84aa13:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84aa18:	48 89 ef             	mov    %rbp,%rdi
  84aa1b:	e8 d8 b8 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84aa20:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84aa27:	48 89 ee             	mov    %rbp,%rsi
  84aa2a:	e8 91 7b 05 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  84aa2f:	48 89 ef             	mov    %rbp,%rdi
  84aa32:	41 89 c4             	mov    %eax,%r12d
  84aa35:	e8 4e b8 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84aa3a:	45 84 e4             	test   %r12b,%r12b
  84aa3d:	0f 85 8d 03 00 00    	jne    84add0 <CCharacter::updateAnimation(float)+0x2560>
  84aa43:	48 8d ac 24 c0 01 00 	lea    0x1c0(%rsp),%rbp
  84aa4a:	00
  84aa4b:	48 8d 94 24 1f 04 00 	lea    0x41f(%rsp),%rdx
  84aa52:	00
  84aa53:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84aa58:	48 89 ef             	mov    %rbp,%rdi
  84aa5b:	e8 98 b8 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84aa60:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84aa67:	48 89 ee             	mov    %rbp,%rsi
  84aa6a:	e8 f1 cd 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84aa6f:	48 89 ef             	mov    %rbp,%rdi
  84aa72:	41 89 c4             	mov    %eax,%r12d
  84aa75:	e8 0e b8 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84aa7a:	45 84 e4             	test   %r12b,%r12b
  84aa7d:	0f 84 5d 07 00 00    	je     84b1e0 <CCharacter::updateAnimation(float)+0x2970>
  84aa83:	f3 0f 10 5c 24 6c    	movss  0x6c(%rsp),%xmm3
  84aa89:	0f 2e 9b 60 02 00 00 	ucomiss 0x260(%rbx),%xmm3
  84aa90:	0f 8a 41 05 00 00    	jp     84afd7 <CCharacter::updateAnimation(float)+0x2767>
  84aa96:	0f 85 3b 05 00 00    	jne    84afd7 <CCharacter::updateAnimation(float)+0x2767>
  84aa9c:	f3 0f 10 83 80 02 00 	movss  0x280(%rbx),%xmm0
  84aaa3:	00
  84aaa4:	0f 2e 05 85 dc 75 00 	ucomiss 0x75dc85(%rip),%xmm0        # fa8730 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x90>
  84aaab:	0f 86 5f f4 ff ff    	jbe    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84aab1:	83 bb 30 03 00 00 02 	cmpl   $0x2,0x330(%rbx)
  84aab8:	0f 85 52 f4 ff ff    	jne    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84aabe:	e9 3d fc ff ff       	jmp    84a700 <CCharacter::updateAnimation(float)+0x1e90>
  84aac3:	48 89 df             	mov    %rbx,%rdi
  84aac6:	e8 05 b0 fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84aacb:	0f 57 c9             	xorps  %xmm1,%xmm1
  84aace:	0f 2e c1             	ucomiss %xmm1,%xmm0
  84aad1:	0f 86 39 f9 ff ff    	jbe    84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  84aad7:	48 89 df             	mov    %rbx,%rdi
  84aada:	e8 f1 af fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84aadf:	f3 0f 11 44 24 7c    	movss  %xmm0,0x7c(%rsp)
  84aae5:	48 8b bb 40 06 00 00 	mov    0x640(%rbx),%rdi
  84aaec:	e8 df af fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84aaf1:	f3 0f 58 05 2b 9d 75 	addss  0x759d2b(%rip),%xmm0        # fa4824 <vtable for Ogre::FrameListener+0x64>
  84aaf8:	00
  84aaf9:	0f 2e 44 24 7c       	ucomiss 0x7c(%rsp),%xmm0
  84aafe:	0f 86 0c f9 ff ff    	jbe    84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  84ab04:	0f 57 db             	xorps  %xmm3,%xmm3
  84ab07:	f3 0f 10 54 24 6c    	movss  0x6c(%rsp),%xmm2
  84ab0d:	0f 2e d3             	ucomiss %xmm3,%xmm2
  84ab10:	0f 82 fa f8 ff ff    	jb     84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  84ab16:	80 bb 64 06 00 00 00 	cmpb   $0x0,0x664(%rbx)
  84ab1d:	0f 84 ed f8 ff ff    	je     84a410 <CCharacter::updateAnimation(float)+0x1ba0>
  84ab23:	48 89 df             	mov    %rbx,%rdi
  84ab26:	e8 a5 af fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84ab2b:	0f 57 c9             	xorps  %xmm1,%xmm1
  84ab2e:	0f 2e c1             	ucomiss %xmm1,%xmm0
  84ab31:	0f 87 f7 04 00 00    	ja     84b02e <CCharacter::updateAnimation(float)+0x27be>
  84ab37:	0f b6 93 21 03 00 00 	movzbl 0x321(%rbx),%edx
  84ab3e:	b8 01 00 00 00       	mov    $0x1,%eax
  84ab43:	f3 0f 11 4c 24 70    	movss  %xmm1,0x70(%rsp)
  84ab49:	f3 0f 10 05 bb 9c 75 	movss  0x759cbb(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  84ab50:	00
  84ab51:	e9 d1 f8 ff ff       	jmp    84a427 <CCharacter::updateAnimation(float)+0x1bb7>
  84ab56:	48 8b 03             	mov    (%rbx),%rax
  84ab59:	48 89 df             	mov    %rbx,%rdi
  84ab5c:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  84ab62:	48 8b b8 30 01 00 00 	mov    0x130(%rax),%rdi
  84ab69:	4c 89 f6             	mov    %r14,%rsi
  84ab6c:	48 8b 07             	mov    (%rdi),%rax
  84ab6f:	ff 90 b8 01 00 00    	call   *0x1b8(%rax)
  84ab75:	84 c0                	test   %al,%al
  84ab77:	0f 84 64 f6 ff ff    	je     84a1e1 <CCharacter::updateAnimation(float)+0x1971>
  84ab7d:	48 8b 03             	mov    (%rbx),%rax
  84ab80:	48 89 df             	mov    %rbx,%rdi
  84ab83:	ff 90 e0 01 00 00    	call   *0x1e0(%rax)
  84ab89:	48 8b b8 30 01 00 00 	mov    0x130(%rax),%rdi
  84ab90:	4c 89 f6             	mov    %r14,%rsi
  84ab93:	48 8b 07             	mov    (%rdi),%rax
  84ab96:	ff 90 b0 01 00 00    	call   *0x1b0(%rax)
  84ab9c:	41 83 fd 01          	cmp    $0x1,%r13d
  84aba0:	48 89 c6             	mov    %rax,%rsi
  84aba3:	7e 5b                	jle    84ac00 <CCharacter::updateAnimation(float)+0x2390>
  84aba5:	48 85 c0             	test   %rax,%rax
  84aba8:	74 0c                	je     84abb6 <CCharacter::updateAnimation(float)+0x2346>
  84abaa:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84abb1:	e8 fa f3 1f 00       	call   a49fb0 <CWeaponTrail::setWeaponNode(Ogre::Node*)>
  84abb6:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84abbd:	be 01 00 00 00       	mov    $0x1,%esi
  84abc2:	e8 59 f4 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84abc7:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84abce:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84abd5:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  84abd9:	48 8b 83 a0 06 00 00 	mov    0x6a0(%rbx),%rax
  84abe0:	8b 4a 2c             	mov    0x2c(%rdx),%ecx
  84abe3:	89 88 90 00 00 00    	mov    %ecx,0x90(%rax)
  84abe9:	8b 4a 30             	mov    0x30(%rdx),%ecx
  84abec:	89 88 94 00 00 00    	mov    %ecx,0x94(%rax)
  84abf2:	8b 52 34             	mov    0x34(%rdx),%edx
  84abf5:	89 90 98 00 00 00    	mov    %edx,0x98(%rax)
  84abfb:	e9 e1 f5 ff ff       	jmp    84a1e1 <CCharacter::updateAnimation(float)+0x1971>
  84ac00:	48 85 c0             	test   %rax,%rax
  84ac03:	74 0c                	je     84ac11 <CCharacter::updateAnimation(float)+0x23a1>
  84ac05:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84ac0c:	e8 9f f3 1f 00       	call   a49fb0 <CWeaponTrail::setWeaponNode(Ogre::Node*)>
  84ac11:	48 8b bb 98 06 00 00 	mov    0x698(%rbx),%rdi
  84ac18:	be 01 00 00 00       	mov    $0x1,%esi
  84ac1d:	e8 fe f3 1f 00       	call   a4a020 <CWeaponTrail::setActive(bool)>
  84ac22:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  84ac29:	48 8b 80 b0 01 00 00 	mov    0x1b0(%rax),%rax
  84ac30:	48 8b 14 e8          	mov    (%rax,%rbp,8),%rdx
  84ac34:	48 8b 83 98 06 00 00 	mov    0x698(%rbx),%rax
  84ac3b:	eb a3                	jmp    84abe0 <CCharacter::updateAnimation(float)+0x2370>
  84ac3d:	48 8b 43 68          	mov    0x68(%rbx),%rax
  84ac41:	48 c7 44 24 70 00 00 	movq   $0x0,0x70(%rsp)
  84ac48:	00 00
  84ac4a:	48 85 c0             	test   %rax,%rax
  84ac4d:	74 09                	je     84ac58 <CCharacter::updateAnimation(float)+0x23e8>
  84ac4f:	48 8b 40 10          	mov    0x10(%rax),%rax
  84ac53:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  84ac58:	48 8d 94 24 3f 04 00 	lea    0x43f(%rsp),%rdx
  84ac5f:	00
  84ac60:	48 8d bc 24 00 04 00 	lea    0x400(%rsp),%rdi
  84ac67:	00
  84ac68:	be 08 99 fc 00       	mov    $0xfc9908,%esi
  84ac6d:	e8 86 b6 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84ac72:	4c 8d b4 24 f0 03 00 	lea    0x3f0(%rsp),%r14
  84ac79:	00
  84ac7a:	48 8d b4 24 00 04 00 	lea    0x400(%rsp),%rsi
  84ac81:	00
  84ac82:	4c 89 f7             	mov    %r14,%rdi
  84ac85:	e8 c6 3d 44 00       	call   c8ea50 <STRINGS::uniqueName(std::string const&)>
  84ac8a:	bf a0 00 00 00       	mov    $0xa0,%edi
  84ac8f:	e8 2c 00 01 00       	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  84ac94:	48 8b 74 24 70       	mov    0x70(%rsp),%rsi
  84ac99:	f3 0f 10 05 5b 9b 75 	movss  0x759b5b(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84aca0:	00
  84aca1:	b9 14 00 00 00       	mov    $0x14,%ecx
  84aca6:	4c 89 f2             	mov    %r14,%rdx
  84aca9:	48 89 c7             	mov    %rax,%rdi
  84acac:	48 89 44 24 60       	mov    %rax,0x60(%rsp)
  84acb1:	e8 6a 1e 20 00       	call   a4cb20 <CWeaponTrail::CWeaponTrail(Ogre::SceneManager*, std::string const&, int, float)>
  84acb6:	48 8b 44 24 60       	mov    0x60(%rsp),%rax
  84acbb:	4c 89 f7             	mov    %r14,%rdi
  84acbe:	48 89 83 a0 06 00 00 	mov    %rax,0x6a0(%rbx)
  84acc5:	e8 be b5 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84acca:	48 8d bc 24 00 04 00 	lea    0x400(%rsp),%rdi
  84acd1:	00
  84acd2:	e8 b1 b5 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84acd7:	48 89 df             	mov    %rbx,%rdi
  84acda:	e8 91 54 fc ff       	call   810170 <CCharacter::alignment()>
  84acdf:	4c 8d b4 24 e0 03 00 	lea    0x3e0(%rsp),%r14
  84ace6:	00
  84ace7:	83 f8 01             	cmp    $0x1,%eax
  84acea:	be 34 05 fa 00       	mov    $0xfa0534,%esi
  84acef:	b8 40 05 fa 00       	mov    $0xfa0540,%eax
  84acf4:	48 8d 94 24 3e 04 00 	lea    0x43e(%rsp),%rdx
  84acfb:	00
  84acfc:	48 0f 45 f0          	cmovne %rax,%rsi
  84ad00:	4c 89 f7             	mov    %r14,%rdi
  84ad03:	e8 f0 b5 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84ad08:	48 8b bb a0 06 00 00 	mov    0x6a0(%rbx),%rdi
  84ad0f:	4c 89 f6             	mov    %r14,%rsi
  84ad12:	e8 79 f3 1f 00       	call   a4a090 <CWeaponTrail::setMaterialName(std::string const&)>
  84ad17:	4c 89 f7             	mov    %r14,%rdi
  84ad1a:	e8 69 b5 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84ad1f:	e9 96 f6 ff ff       	jmp    84a3ba <CCharacter::updateAnimation(float)+0x1b4a>
  84ad24:	48 8d ac 24 00 02 00 	lea    0x200(%rsp),%rbp
  84ad2b:	00
  84ad2c:	48 8d 94 24 23 04 00 	lea    0x423(%rsp),%rdx
  84ad33:	00
  84ad34:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84ad39:	48 89 ef             	mov    %rbp,%rdi
  84ad3c:	e8 b7 b5 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84ad41:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84ad48:	48 89 ee             	mov    %rbp,%rsi
  84ad4b:	e8 10 cb 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84ad50:	48 89 ef             	mov    %rbp,%rdi
  84ad53:	41 89 c4             	mov    %eax,%r12d
  84ad56:	e8 2d b5 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84ad5b:	45 84 e4             	test   %r12b,%r12b
  84ad5e:	0f 84 12 04 00 00    	je     84b176 <CCharacter::updateAnimation(float)+0x2906>
  84ad64:	f3 0f 10 44 24 6c    	movss  0x6c(%rsp),%xmm0
  84ad6a:	0f 2e 83 60 02 00 00 	ucomiss 0x260(%rbx),%xmm0
  84ad71:	7a 06                	jp     84ad79 <CCharacter::updateAnimation(float)+0x2509>
  84ad73:	0f 84 97 f1 ff ff    	je     849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84ad79:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84ad7f:	48 8d ac 24 e0 01 00 	lea    0x1e0(%rsp),%rbp
  84ad86:	00
  84ad87:	f3 0f 5e 8b 98 00 00 	divss  0x98(%rbx),%xmm1
  84ad8e:	00
  84ad8f:	48 8d 94 24 21 04 00 	lea    0x421(%rsp),%rdx
  84ad96:	00
  84ad97:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84ad9c:	48 89 ef             	mov    %rbp,%rdi
  84ad9f:	f3 0f 59 c8          	mulss  %xmm0,%xmm1
  84ada3:	f3 0f 11 4c 24 60    	movss  %xmm1,0x60(%rsp)
  84ada9:	e8 4a b5 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84adae:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84adb5:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84adbb:	48 89 ee             	mov    %rbp,%rsi
  84adbe:	e8 dd c6 05 00       	call   8a74a0 <CGenericModel::setAnimationSpeed(std::string const&, float)>
  84adc3:	48 89 ef             	mov    %rbp,%rdi
  84adc6:	e8 bd b4 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84adcb:	e9 40 f1 ff ff       	jmp    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84add0:	48 8d ac 24 90 01 00 	lea    0x190(%rsp),%rbp
  84add7:	00
  84add8:	48 8d 94 24 1c 04 00 	lea    0x41c(%rsp),%rdx
  84addf:	00
  84ade0:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84ade5:	48 89 ef             	mov    %rbp,%rdi
  84ade8:	e8 0b b5 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84aded:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84adf4:	48 89 ee             	mov    %rbp,%rsi
  84adf7:	e8 64 ca 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84adfc:	48 89 ef             	mov    %rbp,%rdi
  84adff:	41 89 c4             	mov    %eax,%r12d
  84ae02:	e8 81 b4 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84ae07:	45 84 e4             	test   %r12b,%r12b
  84ae0a:	0f 84 21 06 00 00    	je     84b431 <CCharacter::updateAnimation(float)+0x2bc1>
  84ae10:	f3 0f 10 54 24 6c    	movss  0x6c(%rsp),%xmm2
  84ae16:	0f 2e 93 60 02 00 00 	ucomiss 0x260(%rbx),%xmm2
  84ae1d:	7a 06                	jp     84ae25 <CCharacter::updateAnimation(float)+0x25b5>
  84ae1f:	0f 84 77 fc ff ff    	je     84aa9c <CCharacter::updateAnimation(float)+0x222c>
  84ae25:	f3 0f 10 5c 24 60    	movss  0x60(%rsp),%xmm3
  84ae2b:	48 8d ac 24 70 01 00 	lea    0x170(%rsp),%rbp
  84ae32:	00
  84ae33:	f3 0f 5e 9b 98 00 00 	divss  0x98(%rbx),%xmm3
  84ae3a:	00
  84ae3b:	48 8d 94 24 1a 04 00 	lea    0x41a(%rsp),%rdx
  84ae42:	00
  84ae43:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84ae48:	48 89 ef             	mov    %rbp,%rdi
  84ae4b:	f3 0f 59 da          	mulss  %xmm2,%xmm3
  84ae4f:	f3 0f 11 5c 24 60    	movss  %xmm3,0x60(%rsp)
  84ae55:	e8 9e b4 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84ae5a:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84ae61:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84ae67:	48 89 ee             	mov    %rbp,%rsi
  84ae6a:	e8 31 c6 05 00       	call   8a74a0 <CGenericModel::setAnimationSpeed(std::string const&, float)>
  84ae6f:	48 89 ef             	mov    %rbp,%rdi
  84ae72:	e8 11 b4 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84ae77:	e9 20 fc ff ff       	jmp    84aa9c <CCharacter::updateAnimation(float)+0x222c>
  84ae7c:	48 8d ac 24 40 03 00 	lea    0x340(%rsp),%rbp
  84ae83:	00
  84ae84:	48 8d 94 24 37 04 00 	lea    0x437(%rsp),%rdx
  84ae8b:	00
  84ae8c:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84ae91:	48 89 ef             	mov    %rbp,%rdi
  84ae94:	e8 5f b4 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84ae99:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84aea0:	48 89 ee             	mov    %rbp,%rsi
  84aea3:	41 bc 01 00 00 00    	mov    $0x1,%r12d
  84aea9:	e8 12 77 05 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  84aeae:	84 c0                	test   %al,%al
  84aeb0:	48 89 ef             	mov    %rbp,%rdi
  84aeb3:	41 0f 95 c4          	setne  %r12b
  84aeb7:	e8 cc b3 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84aebc:	45 84 e4             	test   %r12b,%r12b
  84aebf:	0f 84 bb f7 ff ff    	je     84a680 <CCharacter::updateAnimation(float)+0x1e10>
  84aec5:	48 8d ac 24 30 03 00 	lea    0x330(%rsp),%rbp
  84aecc:	00
  84aecd:	48 8d 94 24 36 04 00 	lea    0x436(%rsp),%rdx
  84aed4:	00
  84aed5:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84aeda:	48 89 ef             	mov    %rbp,%rdi
  84aedd:	e8 16 b4 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84aee2:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84aee9:	48 89 ee             	mov    %rbp,%rsi
  84aeec:	e8 6f c9 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84aef1:	48 89 ef             	mov    %rbp,%rdi
  84aef4:	41 89 c4             	mov    %eax,%r12d
  84aef7:	e8 8c b3 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84aefc:	45 84 e4             	test   %r12b,%r12b
  84aeff:	74 6c                	je     84af6d <CCharacter::updateAnimation(float)+0x26fd>
  84af01:	f3 0f 10 4c 24 6c    	movss  0x6c(%rsp),%xmm1
  84af07:	0f 2e 8b 60 02 00 00 	ucomiss 0x260(%rbx),%xmm1
  84af0e:	7a 06                	jp     84af16 <CCharacter::updateAnimation(float)+0x26a6>
  84af10:	0f 84 d5 f7 ff ff    	je     84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84af16:	f3 0f 10 54 24 60    	movss  0x60(%rsp),%xmm2
  84af1c:	48 8d ac 24 10 03 00 	lea    0x310(%rsp),%rbp
  84af23:	00
  84af24:	f3 0f 5e 93 98 00 00 	divss  0x98(%rbx),%xmm2
  84af2b:	00
  84af2c:	48 8d 94 24 34 04 00 	lea    0x434(%rsp),%rdx
  84af33:	00
  84af34:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84af39:	48 89 ef             	mov    %rbp,%rdi
  84af3c:	f3 0f 59 d1          	mulss  %xmm1,%xmm2
  84af40:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  84af46:	e8 ad b3 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84af4b:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84af52:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84af58:	48 89 ee             	mov    %rbp,%rsi
  84af5b:	e8 40 c5 05 00       	call   8a74a0 <CGenericModel::setAnimationSpeed(std::string const&, float)>
  84af60:	48 89 ef             	mov    %rbp,%rdi
  84af63:	e8 20 b3 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84af68:	e9 7e f7 ff ff       	jmp    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84af6d:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84af73:	48 8d ac 24 20 03 00 	lea    0x320(%rsp),%rbp
  84af7a:	00
  84af7b:	f3 0f 5e 83 98 00 00 	divss  0x98(%rbx),%xmm0
  84af82:	00
  84af83:	48 8d 94 24 35 04 00 	lea    0x435(%rsp),%rdx
  84af8a:	00
  84af8b:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84af90:	48 89 ef             	mov    %rbp,%rdi
  84af93:	f3 0f 59 44 24 6c    	mulss  0x6c(%rsp),%xmm0
  84af99:	f3 0f 11 44 24 60    	movss  %xmm0,0x60(%rsp)
  84af9f:	e8 54 b3 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84afa4:	f3 0f 10 15 b4 d7 75 	movss  0x75d7b4(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84afab:	00
  84afac:	ba 01 00 00 00       	mov    $0x1,%edx
  84afb1:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84afb7:	48 89 ee             	mov    %rbp,%rsi
  84afba:	f3 0f 10 05 26 d7 75 	movss  0x75d726(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84afc1:	00
  84afc2:	48 89 df             	mov    %rbx,%rdi
  84afc5:	e8 66 78 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84afca:	48 89 ef             	mov    %rbp,%rdi
  84afcd:	e8 b6 b2 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84afd2:	e9 14 f7 ff ff       	jmp    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84afd7:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84afdd:	48 8d ac 24 a0 01 00 	lea    0x1a0(%rsp),%rbp
  84afe4:	00
  84afe5:	f3 0f 5e 83 98 00 00 	divss  0x98(%rbx),%xmm0
  84afec:	00
  84afed:	48 8d 94 24 1d 04 00 	lea    0x41d(%rsp),%rdx
  84aff4:	00
  84aff5:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84affa:	48 89 ef             	mov    %rbp,%rdi
  84affd:	f3 0f 59 c3          	mulss  %xmm3,%xmm0
  84b001:	f3 0f 11 44 24 60    	movss  %xmm0,0x60(%rsp)
  84b007:	e8 ec b2 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b00c:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b013:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84b019:	48 89 ee             	mov    %rbp,%rsi
  84b01c:	e8 7f c4 05 00       	call   8a74a0 <CGenericModel::setAnimationSpeed(std::string const&, float)>
  84b021:	48 89 ef             	mov    %rbp,%rdi
  84b024:	e8 5f b2 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b029:	e9 6e fa ff ff       	jmp    84aa9c <CCharacter::updateAnimation(float)+0x222c>
  84b02e:	48 8b bb 40 06 00 00 	mov    0x640(%rbx),%rdi
  84b035:	e8 96 aa fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84b03a:	48 89 df             	mov    %rbx,%rdi
  84b03d:	f3 0f 11 44 24 70    	movss  %xmm0,0x70(%rsp)
  84b043:	e8 88 aa fc ff       	call   815ad0 <CCharacter::runningSpeed()>
  84b048:	f3 0f 10 15 d4 97 75 	movss  0x7597d4(%rip),%xmm2        # fa4824 <vtable for Ogre::FrameListener+0x64>
  84b04f:	00
  84b050:	f3 0f 58 54 24 70    	addss  0x70(%rsp),%xmm2
  84b056:	f3 0f 5e d0          	divss  %xmm0,%xmm2
  84b05a:	f3 0f 10 05 aa 97 75 	movss  0x7597aa(%rip),%xmm0        # fa480c <vtable for Ogre::FrameListener+0x4c>
  84b061:	00
  84b062:	f3 0f 11 54 24 70    	movss  %xmm2,0x70(%rsp)
  84b068:	0f 2e c2             	ucomiss %xmm2,%xmm0
  84b06b:	0f b6 93 21 03 00 00 	movzbl 0x321(%rbx),%edx
  84b072:	0f 97 c0             	seta   %al
  84b075:	e9 ad f3 ff ff       	jmp    84a427 <CCharacter::updateAnimation(float)+0x1bb7>
  84b07a:	f3 0f 10 44 24 60    	movss  0x60(%rsp),%xmm0
  84b080:	48 8d ac 24 20 02 00 	lea    0x220(%rsp),%rbp
  84b087:	00
  84b088:	f3 0f 5e 83 98 00 00 	divss  0x98(%rbx),%xmm0
  84b08f:	00
  84b090:	48 8d 94 24 25 04 00 	lea    0x425(%rsp),%rdx
  84b097:	00
  84b098:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84b09d:	48 89 ef             	mov    %rbp,%rdi
  84b0a0:	f3 0f 59 44 24 6c    	mulss  0x6c(%rsp),%xmm0
  84b0a6:	f3 0f 11 44 24 60    	movss  %xmm0,0x60(%rsp)
  84b0ac:	e8 47 b2 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b0b1:	f3 0f 10 15 a7 d6 75 	movss  0x75d6a7(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b0b8:	00
  84b0b9:	ba 01 00 00 00       	mov    $0x1,%edx
  84b0be:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84b0c4:	48 89 ee             	mov    %rbp,%rsi
  84b0c7:	f3 0f 10 05 19 d6 75 	movss  0x75d619(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b0ce:	00
  84b0cf:	48 89 df             	mov    %rbx,%rdi
  84b0d2:	e8 59 77 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b0d7:	48 89 ef             	mov    %rbp,%rdi
  84b0da:	e8 a9 b1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b0df:	e9 2c ee ff ff       	jmp    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84b0e4:	48 8d ac 24 60 02 00 	lea    0x260(%rsp),%rbp
  84b0eb:	00
  84b0ec:	48 8d 94 24 29 04 00 	lea    0x429(%rsp),%rdx
  84b0f3:	00
  84b0f4:	be 3a 99 fc 00       	mov    $0xfc993a,%esi
  84b0f9:	48 89 ef             	mov    %rbp,%rdi
  84b0fc:	e8 f7 b1 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b101:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b108:	48 89 ee             	mov    %rbp,%rsi
  84b10b:	e8 20 a4 05 00       	call   8a5530 <CGenericModel::animationQueued(std::string const&) const>
  84b110:	48 89 ef             	mov    %rbp,%rdi
  84b113:	41 89 c4             	mov    %eax,%r12d
  84b116:	e8 6d b1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b11b:	45 84 e4             	test   %r12b,%r12b
  84b11e:	0f 85 c7 f5 ff ff    	jne    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b124:	48 8d ac 24 50 02 00 	lea    0x250(%rsp),%rbp
  84b12b:	00
  84b12c:	48 8d 94 24 28 04 00 	lea    0x428(%rsp),%rdx
  84b133:	00
  84b134:	be 3a 99 fc 00       	mov    $0xfc993a,%esi
  84b139:	48 89 ef             	mov    %rbp,%rdi
  84b13c:	e8 b7 b1 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b141:	f3 0f 10 15 17 d6 75 	movss  0x75d617(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b148:	00
  84b149:	ba 01 00 00 00       	mov    $0x1,%edx
  84b14e:	f3 0f 10 0d a6 96 75 	movss  0x7596a6(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84b155:	00
  84b156:	48 89 ee             	mov    %rbp,%rsi
  84b159:	f3 0f 10 05 87 d5 75 	movss  0x75d587(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b160:	00
  84b161:	48 89 df             	mov    %rbx,%rdi
  84b164:	e8 c7 76 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b169:	48 89 ef             	mov    %rbp,%rdi
  84b16c:	e8 17 b1 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b171:	e9 75 f5 ff ff       	jmp    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b176:	f3 0f 10 5c 24 60    	movss  0x60(%rsp),%xmm3
  84b17c:	48 8d ac 24 f0 01 00 	lea    0x1f0(%rsp),%rbp
  84b183:	00
  84b184:	f3 0f 5e 9b 98 00 00 	divss  0x98(%rbx),%xmm3
  84b18b:	00
  84b18c:	48 8d 94 24 22 04 00 	lea    0x422(%rsp),%rdx
  84b193:	00
  84b194:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84b199:	48 89 ef             	mov    %rbp,%rdi
  84b19c:	f3 0f 59 5c 24 6c    	mulss  0x6c(%rsp),%xmm3
  84b1a2:	f3 0f 11 5c 24 60    	movss  %xmm3,0x60(%rsp)
  84b1a8:	e8 4b b1 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b1ad:	f3 0f 10 15 ab d5 75 	movss  0x75d5ab(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b1b4:	00
  84b1b5:	ba 01 00 00 00       	mov    $0x1,%edx
  84b1ba:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84b1c0:	48 89 ee             	mov    %rbp,%rsi
  84b1c3:	f3 0f 10 05 1d d5 75 	movss  0x75d51d(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b1ca:	00
  84b1cb:	48 89 df             	mov    %rbx,%rdi
  84b1ce:	e8 5d 76 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b1d3:	48 89 ef             	mov    %rbp,%rdi
  84b1d6:	e8 ad b0 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b1db:	e9 30 ed ff ff       	jmp    849f10 <CCharacter::updateAnimation(float)+0x16a0>
  84b1e0:	f3 0f 10 54 24 60    	movss  0x60(%rsp),%xmm2
  84b1e6:	48 8d ac 24 b0 01 00 	lea    0x1b0(%rsp),%rbp
  84b1ed:	00
  84b1ee:	f3 0f 5e 93 98 00 00 	divss  0x98(%rbx),%xmm2
  84b1f5:	00
  84b1f6:	48 8d 94 24 1e 04 00 	lea    0x41e(%rsp),%rdx
  84b1fd:	00
  84b1fe:	be b9 99 fc 00       	mov    $0xfc99b9,%esi
  84b203:	48 89 ef             	mov    %rbp,%rdi
  84b206:	f3 0f 59 54 24 6c    	mulss  0x6c(%rsp),%xmm2
  84b20c:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  84b212:	e8 e1 b0 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b217:	f3 0f 10 15 41 d5 75 	movss  0x75d541(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b21e:	00
  84b21f:	ba 01 00 00 00       	mov    $0x1,%edx
  84b224:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84b22a:	48 89 ee             	mov    %rbp,%rsi
  84b22d:	f3 0f 10 05 b3 d4 75 	movss  0x75d4b3(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b234:	00
  84b235:	48 89 df             	mov    %rbx,%rdi
  84b238:	e8 f3 75 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b23d:	48 89 ef             	mov    %rbp,%rdi
  84b240:	e8 43 b0 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b245:	e9 52 f8 ff ff       	jmp    84aa9c <CCharacter::updateAnimation(float)+0x222c>
  84b24a:	48 8d ac 24 00 03 00 	lea    0x300(%rsp),%rbp
  84b251:	00
  84b252:	48 8d 94 24 33 04 00 	lea    0x433(%rsp),%rdx
  84b259:	00
  84b25a:	be aa 99 fc 00       	mov    $0xfc99aa,%esi
  84b25f:	48 89 ef             	mov    %rbp,%rdi
  84b262:	e8 91 b0 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b267:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b26e:	48 89 ee             	mov    %rbp,%rsi
  84b271:	41 bc 01 00 00 00    	mov    $0x1,%r12d
  84b277:	e8 44 73 05 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  84b27c:	84 c0                	test   %al,%al
  84b27e:	48 89 ef             	mov    %rbp,%rdi
  84b281:	41 0f 95 c4          	setne  %r12b
  84b285:	e8 fe af d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b28a:	45 84 e4             	test   %r12b,%r12b
  84b28d:	0f 84 fd f3 ff ff    	je     84a690 <CCharacter::updateAnimation(float)+0x1e20>
  84b293:	48 8d ac 24 f0 02 00 	lea    0x2f0(%rsp),%rbp
  84b29a:	00
  84b29b:	48 8d 94 24 32 04 00 	lea    0x432(%rsp),%rdx
  84b2a2:	00
  84b2a3:	be aa 99 fc 00       	mov    $0xfc99aa,%esi
  84b2a8:	45 31 f6             	xor    %r14d,%r14d
  84b2ab:	45 31 ed             	xor    %r13d,%r13d
  84b2ae:	48 89 ef             	mov    %rbp,%rdi
  84b2b1:	e8 42 b0 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b2b6:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b2bd:	48 89 ee             	mov    %rbp,%rsi
  84b2c0:	41 be 01 00 00 00    	mov    $0x1,%r14d
  84b2c6:	e8 95 c5 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84b2cb:	45 31 ff             	xor    %r15d,%r15d
  84b2ce:	84 c0                	test   %al,%al
  84b2d0:	0f 84 c5 01 00 00    	je     84b49b <CCharacter::updateAnimation(float)+0x2c2b>
  84b2d6:	48 89 ef             	mov    %rbp,%rdi
  84b2d9:	e8 aa af d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b2de:	45 84 ff             	test   %r15b,%r15b
  84b2e1:	0f 84 04 f4 ff ff    	je     84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b2e7:	48 8d ac 24 d0 02 00 	lea    0x2d0(%rsp),%rbp
  84b2ee:	00
  84b2ef:	48 8d 94 24 30 04 00 	lea    0x430(%rsp),%rdx
  84b2f6:	00
  84b2f7:	be aa 99 fc 00       	mov    $0xfc99aa,%esi
  84b2fc:	48 89 ef             	mov    %rbp,%rdi
  84b2ff:	e8 f4 af d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b304:	f3 0f 10 15 54 d4 75 	movss  0x75d454(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b30b:	00
  84b30c:	ba 01 00 00 00       	mov    $0x1,%edx
  84b311:	f3 0f 10 0d e3 94 75 	movss  0x7594e3(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84b318:	00
  84b319:	48 89 ee             	mov    %rbp,%rsi
  84b31c:	f3 0f 10 05 c4 d3 75 	movss  0x75d3c4(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b323:	00
  84b324:	48 89 df             	mov    %rbx,%rdi
  84b327:	e8 04 75 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b32c:	48 89 ef             	mov    %rbp,%rdi
  84b32f:	e8 54 af d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b334:	e9 b2 f3 ff ff       	jmp    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b339:	48 8d ac 24 c0 02 00 	lea    0x2c0(%rsp),%rbp
  84b340:	00
  84b341:	48 8d 94 24 2f 04 00 	lea    0x42f(%rsp),%rdx
  84b348:	00
  84b349:	be c8 7d fa 00       	mov    $0xfa7dc8,%esi
  84b34e:	48 89 ef             	mov    %rbp,%rdi
  84b351:	e8 02 ab d0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  84b356:	48 89 ee             	mov    %rbp,%rsi
  84b359:	48 89 df             	mov    %rbx,%rdi
  84b35c:	41 be 01 00 00 00    	mov    $0x1,%r14d
  84b362:	e8 29 40 fb ff       	call   7ff390 <CBaseUnit::hasUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  84b367:	84 c0                	test   %al,%al
  84b369:	0f 85 16 06 00 00    	jne    84b985 <CCharacter::updateAnimation(float)+0x3115>
  84b36f:	48 8d ac 24 c0 02 00 	lea    0x2c0(%rsp),%rbp
  84b376:	00
  84b377:	45 31 ed             	xor    %r13d,%r13d
  84b37a:	48 89 ef             	mov    %rbp,%rdi
  84b37d:	e8 56 95 d0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84b382:	45 84 ed             	test   %r13b,%r13b
  84b385:	0f 84 20 f3 ff ff    	je     84a6ab <CCharacter::updateAnimation(float)+0x1e3b>
  84b38b:	48 8d ac 24 a0 02 00 	lea    0x2a0(%rsp),%rbp
  84b392:	00
  84b393:	48 8d 94 24 2d 04 00 	lea    0x42d(%rsp),%rdx
  84b39a:	00
  84b39b:	be b2 99 fc 00       	mov    $0xfc99b2,%esi
  84b3a0:	45 31 f6             	xor    %r14d,%r14d
  84b3a3:	45 31 ed             	xor    %r13d,%r13d
  84b3a6:	48 89 ef             	mov    %rbp,%rdi
  84b3a9:	e8 4a af d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b3ae:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b3b5:	48 89 ee             	mov    %rbp,%rsi
  84b3b8:	41 be 01 00 00 00    	mov    $0x1,%r14d
  84b3be:	e8 9d c4 05 00       	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84b3c3:	45 31 ff             	xor    %r15d,%r15d
  84b3c6:	84 c0                	test   %al,%al
  84b3c8:	0f 84 12 01 00 00    	je     84b4e0 <CCharacter::updateAnimation(float)+0x2c70>
  84b3ce:	48 89 ef             	mov    %rbp,%rdi
  84b3d1:	e8 b2 ae d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b3d6:	45 84 ff             	test   %r15b,%r15b
  84b3d9:	0f 84 0c f3 ff ff    	je     84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b3df:	48 8d ac 24 80 02 00 	lea    0x280(%rsp),%rbp
  84b3e6:	00
  84b3e7:	48 8d 94 24 2b 04 00 	lea    0x42b(%rsp),%rdx
  84b3ee:	00
  84b3ef:	be b2 99 fc 00       	mov    $0xfc99b2,%esi
  84b3f4:	48 89 ef             	mov    %rbp,%rdi
  84b3f7:	e8 fc ae d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b3fc:	f3 0f 10 15 5c d3 75 	movss  0x75d35c(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b403:	00
  84b404:	ba 01 00 00 00       	mov    $0x1,%edx
  84b409:	f3 0f 10 0d eb 93 75 	movss  0x7593eb(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84b410:	00
  84b411:	48 89 ee             	mov    %rbp,%rsi
  84b414:	f3 0f 10 05 cc d2 75 	movss  0x75d2cc(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b41b:	00
  84b41c:	48 89 df             	mov    %rbx,%rdi
  84b41f:	e8 0c 74 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b424:	48 89 ef             	mov    %rbp,%rdi
  84b427:	e8 5c ae d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b42c:	e9 ba f2 ff ff       	jmp    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b431:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84b437:	48 8d ac 24 80 01 00 	lea    0x180(%rsp),%rbp
  84b43e:	00
  84b43f:	f3 0f 5e 8b 98 00 00 	divss  0x98(%rbx),%xmm1
  84b446:	00
  84b447:	48 8d 94 24 1b 04 00 	lea    0x41b(%rsp),%rdx
  84b44e:	00
  84b44f:	be a5 99 fc 00       	mov    $0xfc99a5,%esi
  84b454:	48 89 ef             	mov    %rbp,%rdi
  84b457:	f3 0f 59 4c 24 6c    	mulss  0x6c(%rsp),%xmm1
  84b45d:	f3 0f 11 4c 24 60    	movss  %xmm1,0x60(%rsp)
  84b463:	e8 90 ae d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b468:	f3 0f 10 15 f0 d2 75 	movss  0x75d2f0(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b46f:	00
  84b470:	ba 01 00 00 00       	mov    $0x1,%edx
  84b475:	f3 0f 10 4c 24 60    	movss  0x60(%rsp),%xmm1
  84b47b:	48 89 ee             	mov    %rbp,%rsi
  84b47e:	f3 0f 10 05 62 d2 75 	movss  0x75d262(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b485:	00
  84b486:	48 89 df             	mov    %rbx,%rdi
  84b489:	e8 a2 73 fc ff       	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b48e:	48 89 ef             	mov    %rbp,%rdi
  84b491:	e8 f2 ad d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b496:	e9 01 f6 ff ff       	jmp    84aa9c <CCharacter::updateAnimation(float)+0x222c>
  84b49b:	4c 8d a4 24 e0 02 00 	lea    0x2e0(%rsp),%r12
  84b4a2:	00
  84b4a3:	48 8d 94 24 31 04 00 	lea    0x431(%rsp),%rdx
  84b4aa:	00
  84b4ab:	be aa 99 fc 00       	mov    $0xfc99aa,%esi
  84b4b0:	4c 89 e7             	mov    %r12,%rdi
  84b4b3:	e8 40 ae d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b4b8:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b4bf:	4c 89 e6             	mov    %r12,%rsi
  84b4c2:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  84b4c8:	e8 63 a0 05 00       	call   8a5530 <CGenericModel::animationQueued(std::string const&) const>
  84b4cd:	84 c0                	test   %al,%al
  84b4cf:	4c 89 e7             	mov    %r12,%rdi
  84b4d2:	41 0f 94 c7          	sete   %r15b
  84b4d6:	e8 ad ad d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b4db:	e9 f6 fd ff ff       	jmp    84b2d6 <CCharacter::updateAnimation(float)+0x2a66>
  84b4e0:	4c 8d a4 24 90 02 00 	lea    0x290(%rsp),%r12
  84b4e7:	00
  84b4e8:	48 8d 94 24 2c 04 00 	lea    0x42c(%rsp),%rdx
  84b4ef:	00
  84b4f0:	be b2 99 fc 00       	mov    $0xfc99b2,%esi
  84b4f5:	4c 89 e7             	mov    %r12,%rdi
  84b4f8:	e8 fb ad d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b4fd:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b504:	4c 89 e6             	mov    %r12,%rsi
  84b507:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  84b50d:	e8 1e a0 05 00       	call   8a5530 <CGenericModel::animationQueued(std::string const&) const>
  84b512:	84 c0                	test   %al,%al
  84b514:	4c 89 e7             	mov    %r12,%rdi
  84b517:	41 0f 94 c7          	sete   %r15b
  84b51b:	e8 68 ad d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b520:	e9 a9 fe ff ff       	jmp    84b3ce <CCharacter::updateAnimation(float)+0x2b5e>
  84b525:	45 84 ed             	test   %r13b,%r13b
  84b528:	48 89 c3             	mov    %rax,%rbx
  84b52b:	74 0d                	je     84b53a <CCharacter::updateAnimation(float)+0x2cca>
  84b52d:	48 8d bc 24 e0 02 00 	lea    0x2e0(%rsp),%rdi
  84b534:	00
  84b535:	e8 4e ad d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b53a:	45 84 f6             	test   %r14b,%r14b
  84b53d:	75 0b                	jne    84b54a <CCharacter::updateAnimation(float)+0x2cda>
  84b53f:	48 89 df             	mov    %rbx,%rdi
  84b542:	e8 51 8f d0 ff       	call   554498 <_Unwind_Resume@plt>
  84b547:	48 89 c3             	mov    %rax,%rbx
  84b54a:	48 89 ef             	mov    %rbp,%rdi
  84b54d:	e8 36 ad d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b552:	eb eb                	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b554:	eb f1                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b556:	48 89 c3             	mov    %rax,%rbx
  84b559:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  84b560:	eb dd                	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b562:	eb e3                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b564:	eb f0                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b566:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  84b56d:	00 00 00
  84b570:	eb d5                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b572:	8b 47 10             	mov    0x10(%rdi),%eax
  84b575:	8d 50 ff             	lea    -0x1(%rax),%edx
  84b578:	89 57 10             	mov    %edx,0x10(%rdi)
  84b57b:	e9 5d de ff ff       	jmp    8493dd <CCharacter::updateAnimation(float)+0xb6d>
  84b580:	eb d4                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b582:	eb d2                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b584:	eb c1                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b586:	48 89 c3             	mov    %rax,%rbx
  84b589:	4c 89 ef             	mov    %r13,%rdi
  84b58c:	0f 1f 40 00          	nopl   0x0(%rax)
  84b590:	e8 d3 9c d0 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  84b595:	48 89 df             	mov    %rbx,%rdi
  84b598:	e8 fb 8e d0 ff       	call   554498 <_Unwind_Resume@plt>
  84b59d:	eb a8                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b59f:	45 84 e4             	test   %r12b,%r12b
  84b5a2:	48 89 c3             	mov    %rax,%rbx
  84b5a5:	74 98                	je     84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b5a7:	eb a1                	jmp    84b54a <CCharacter::updateAnimation(float)+0x2cda>
  84b5a9:	eb 9c                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b5ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  84b5b0:	eb a4                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5b2:	eb 93                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b5b4:	eb a0                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5b6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  84b5bd:	00 00 00
  84b5c0:	eb 94                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5c2:	eb 92                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5c4:	eb 81                	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b5c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  84b5cd:	00 00 00
  84b5d0:	eb 84                	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5d2:	e9 70 ff ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b5d7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  84b5de:	00 00
  84b5e0:	e9 71 ff ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5e5:	4c 89 f7             	mov    %r14,%rdi
  84b5e8:	48 89 c3             	mov    %rax,%rbx
  84b5eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  84b5f0:	e8 93 ac d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b5f5:	e9 45 ff ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b5fa:	e9 57 ff ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b5ff:	48 8b 7c 24 60       	mov    0x60(%rsp),%rdi
  84b604:	48 89 c3             	mov    %rax,%rbx
  84b607:	e8 5c 9c d0 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  84b60c:	4c 89 f7             	mov    %r14,%rdi
  84b60f:	e8 74 ac d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b614:	48 8d bc 24 00 04 00 	lea    0x400(%rsp),%rdi
  84b61b:	00
  84b61c:	e8 67 ac d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b621:	e9 19 ff ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b626:	48 89 c3             	mov    %rax,%rbx
  84b629:	eb e1                	jmp    84b60c <CCharacter::updateAnimation(float)+0x2d9c>
  84b62b:	48 89 c3             	mov    %rax,%rbx
  84b62e:	66 90                	xchg   %ax,%ax
  84b630:	eb e2                	jmp    84b614 <CCharacter::updateAnimation(float)+0x2da4>
  84b632:	e9 1f ff ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b637:	e9 0b ff ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b63c:	0f 1f 40 00          	nopl   0x0(%rax)
  84b640:	e9 11 ff ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b645:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b64c:	00 00 00 00
  84b650:	e9 f2 fe ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b655:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b65c:	00 00 00 00
  84b660:	e9 f1 fe ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b665:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b66c:	00 00 00 00
  84b670:	e9 d2 fe ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b675:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b67c:	00 00 00 00
  84b680:	e9 d1 fe ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b685:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b68c:	00 00 00 00
  84b690:	e9 b2 fe ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b695:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b69c:	00 00 00 00
  84b6a0:	e9 b1 fe ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b6a5:	48 89 c3             	mov    %rax,%rbx
  84b6a8:	4c 89 ef             	mov    %r13,%rdi
  84b6ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  84b6b0:	e8 d3 ab d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b6b5:	48 89 df             	mov    %rbx,%rdi
  84b6b8:	e8 db 8d d0 ff       	call   554498 <_Unwind_Resume@plt>
  84b6bd:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  84b6c4:	00
  84b6c5:	48 89 c3             	mov    %rax,%rbx
  84b6c8:	e8 43 fa d1 ff       	call   56b110 <Ogre::MaterialPtr::~MaterialPtr()>
  84b6cd:	eb d9                	jmp    84b6a8 <CCharacter::updateAnimation(float)+0x2e38>
  84b6cf:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  84b6d4:	48 85 c0             	test   %rax,%rax
  84b6d7:	74 2f                	je     84b708 <CCharacter::updateAnimation(float)+0x2e98>
  84b6d9:	83 c8 ff             	or     $0xffffffff,%eax
  84b6dc:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  84b6e1:	85 c0                	test   %eax,%eax
  84b6e3:	0f 8f c5 dc ff ff    	jg     8493ae <CCharacter::updateAnimation(float)+0xb3e>
  84b6e9:	48 8d b4 24 18 04 00 	lea    0x418(%rsp),%rsi
  84b6f0:	00
  84b6f1:	e8 e2 a0 d0 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  84b6f6:	e9 b3 dc ff ff       	jmp    8493ae <CCharacter::updateAnimation(float)+0xb3e>
  84b6fb:	48 89 ef             	mov    %rbp,%rdi
  84b6fe:	48 89 c3             	mov    %rax,%rbx
  84b701:	e8 82 ab d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b706:	eb a0                	jmp    84b6a8 <CCharacter::updateAnimation(float)+0x2e38>
  84b708:	8b 47 10             	mov    0x10(%rdi),%eax
  84b70b:	8d 50 ff             	lea    -0x1(%rax),%edx
  84b70e:	89 57 10             	mov    %edx,0x10(%rdi)
  84b711:	eb ce                	jmp    84b6e1 <CCharacter::updateAnimation(float)+0x2e71>
  84b713:	eb 90                	jmp    84b6a5 <CCharacter::updateAnimation(float)+0x2e35>
  84b715:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  84b71a:	48 85 c0             	test   %rax,%rax
  84b71d:	74 29                	je     84b748 <CCharacter::updateAnimation(float)+0x2ed8>
  84b71f:	83 c8 ff             	or     $0xffffffff,%eax
  84b722:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  84b727:	85 c0                	test   %eax,%eax
  84b729:	0f 8f 1c dc ff ff    	jg     84934b <CCharacter::updateAnimation(float)+0xadb>
  84b72f:	48 8d b4 24 19 04 00 	lea    0x419(%rsp),%rsi
  84b736:	00
  84b737:	e8 9c a0 d0 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  84b73c:	e9 0a dc ff ff       	jmp    84934b <CCharacter::updateAnimation(float)+0xadb>
  84b741:	eb b8                	jmp    84b6fb <CCharacter::updateAnimation(float)+0x2e8b>
  84b743:	e9 5d ff ff ff       	jmp    84b6a5 <CCharacter::updateAnimation(float)+0x2e35>
  84b748:	8b 47 10             	mov    0x10(%rdi),%eax
  84b74b:	8d 50 ff             	lea    -0x1(%rax),%edx
  84b74e:	89 57 10             	mov    %edx,0x10(%rdi)
  84b751:	eb d4                	jmp    84b727 <CCharacter::updateAnimation(float)+0x2eb7>
  84b753:	45 84 ed             	test   %r13b,%r13b
  84b756:	48 89 c3             	mov    %rax,%rbx
  84b759:	74 0d                	je     84b768 <CCharacter::updateAnimation(float)+0x2ef8>
  84b75b:	48 8d bc 24 b0 02 00 	lea    0x2b0(%rsp),%rdi
  84b762:	00
  84b763:	e8 20 ab d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b768:	45 84 f6             	test   %r14b,%r14b
  84b76b:	0f 84 ce fd ff ff    	je     84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b771:	48 8d bc 24 c0 02 00 	lea    0x2c0(%rsp),%rdi
  84b778:	00
  84b779:	e8 5a 91 d0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84b77e:	e9 bc fd ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b783:	e9 bf fd ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b788:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  84b78f:	00
  84b790:	e9 c1 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b795:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b79c:	00 00 00 00
  84b7a0:	e9 b1 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b7a5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b7ac:	00 00 00 00
  84b7b0:	e9 a1 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b7b5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b7bc:	00 00 00 00
  84b7c0:	e9 da fd ff ff       	jmp    84b59f <CCharacter::updateAnimation(float)+0x2d2f>
  84b7c5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b7cc:	00 00 00 00
  84b7d0:	e9 72 fd ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b7d5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b7dc:	00 00 00 00
  84b7e0:	e9 71 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b7e5:	48 8b 7c 24 60       	mov    0x60(%rsp),%rdi
  84b7ea:	48 89 c3             	mov    %rax,%rbx
  84b7ed:	e8 76 9a d0 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  84b7f2:	4c 89 f7             	mov    %r14,%rdi
  84b7f5:	e8 8e aa d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b7fa:	48 8d bc 24 d0 03 00 	lea    0x3d0(%rsp),%rdi
  84b801:	00
  84b802:	e8 81 aa d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b807:	e9 33 fd ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b80c:	48 89 c3             	mov    %rax,%rbx
  84b80f:	eb e1                	jmp    84b7f2 <CCharacter::updateAnimation(float)+0x2f82>
  84b811:	48 89 c3             	mov    %rax,%rbx
  84b814:	eb e4                	jmp    84b7fa <CCharacter::updateAnimation(float)+0x2f8a>
  84b816:	e9 3b fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b81b:	48 8d bc 24 80 03 00 	lea    0x380(%rsp),%rdi
  84b822:	00
  84b823:	48 89 c3             	mov    %rax,%rbx
  84b826:	e8 5d aa d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b82b:	e9 0f fd ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b830:	e9 21 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b835:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b83c:	00 00 00 00
  84b840:	e9 02 fd ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b845:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b84c:	00 00 00 00
  84b850:	e9 01 fd ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b855:	48 8b 7c 24 60       	mov    0x60(%rsp),%rdi
  84b85a:	48 89 c3             	mov    %rax,%rbx
  84b85d:	e8 06 9a d0 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  84b862:	48 8d bc 24 90 03 00 	lea    0x390(%rsp),%rdi
  84b869:	00
  84b86a:	e8 19 aa d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b86f:	48 8d bc 24 a0 03 00 	lea    0x3a0(%rsp),%rdi
  84b876:	00
  84b877:	e8 0c aa d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b87c:	e9 be fc ff ff       	jmp    84b53f <CCharacter::updateAnimation(float)+0x2ccf>
  84b881:	48 89 c3             	mov    %rax,%rbx
  84b884:	eb dc                	jmp    84b862 <CCharacter::updateAnimation(float)+0x2ff2>
  84b886:	48 89 c3             	mov    %rax,%rbx
  84b889:	eb e4                	jmp    84b86f <CCharacter::updateAnimation(float)+0x2fff>
  84b88b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  84b890:	e9 c1 fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b895:	e9 bc fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b89a:	48 89 c3             	mov    %rax,%rbx
  84b89d:	4c 89 f7             	mov    %r14,%rdi
  84b8a0:	e8 e3 a9 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b8a5:	48 89 df             	mov    %rbx,%rdi
  84b8a8:	e8 eb 8b d0 ff       	call   554498 <_Unwind_Resume@plt>
  84b8ad:	e9 95 fc ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b8b2:	e9 9f fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b8b7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  84b8be:	00 00
  84b8c0:	e9 91 fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b8c5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b8cc:	00 00 00 00
  84b8d0:	e9 72 fc ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b8d5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b8dc:	00 00 00 00
  84b8e0:	e9 00 fd ff ff       	jmp    84b5e5 <CCharacter::updateAnimation(float)+0x2d75>
  84b8e5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b8ec:	00 00 00 00
  84b8f0:	e9 61 fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b8f5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b8fc:	00 00 00 00
  84b900:	e9 42 fc ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b905:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b90c:	00 00 00 00
  84b910:	e9 41 fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b915:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b91c:	00 00 00 00
  84b920:	e9 22 fc ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b925:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b92c:	00 00 00 00
  84b930:	e9 21 fc ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b935:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b93c:	00 00 00 00
  84b940:	e9 02 fc ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b945:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b94c:	00 00 00 00
  84b950:	e9 f2 fb ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b955:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b95c:	00 00 00 00
  84b960:	e9 f1 fb ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b965:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b96c:	00 00 00 00
  84b970:	e9 e1 fb ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b975:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  84b97c:	00 00 00 00
  84b980:	e9 d1 fb ff ff       	jmp    84b556 <CCharacter::updateAnimation(float)+0x2ce6>
  84b985:	4c 8d a4 24 b0 02 00 	lea    0x2b0(%rsp),%r12
  84b98c:	00
  84b98d:	48 8d 94 24 2e 04 00 	lea    0x42e(%rsp),%rdx
  84b994:	00
  84b995:	be b2 99 fc 00       	mov    $0xfc99b2,%esi
  84b99a:	4c 89 e7             	mov    %r12,%rdi
  84b99d:	e8 56 a9 d0 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b9a2:	48 8b bb 00 02 00 00 	mov    0x200(%rbx),%rdi
  84b9a9:	4c 89 e6             	mov    %r12,%rsi
  84b9ac:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  84b9b2:	e8 09 6c 05 00       	call   8a25c0 <CGenericModel::animationExists(std::string const&) const>
  84b9b7:	84 c0                	test   %al,%al
  84b9b9:	4c 89 e7             	mov    %r12,%rdi
  84b9bc:	41 0f 95 c5          	setne  %r13b
  84b9c0:	e8 c3 a8 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b9c5:	e9 b0 f9 ff ff       	jmp    84b37a <CCharacter::updateAnimation(float)+0x2b0a>
  84b9ca:	45 84 ed             	test   %r13b,%r13b
  84b9cd:	48 89 c3             	mov    %rax,%rbx
  84b9d0:	0f 84 64 fb ff ff    	je     84b53a <CCharacter::updateAnimation(float)+0x2cca>
  84b9d6:	48 8d bc 24 90 02 00 	lea    0x290(%rsp),%rdi
  84b9dd:	00
  84b9de:	e8 a5 a8 d0 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b9e3:	e9 52 fb ff ff       	jmp    84b53a <CCharacter::updateAnimation(float)+0x2cca>
  84b9e8:	e9 5a fb ff ff       	jmp    84b547 <CCharacter::updateAnimation(float)+0x2cd7>
  84b9ed:	48 89 c3             	mov    %rax,%rbx
  84b9f0:	e9 7c fd ff ff       	jmp    84b771 <CCharacter::updateAnimation(float)+0x2f01>
