
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000082b550 <CCharacter::attack()>:
  82b550:	mov    %rbx,-0x18(%rsp)
  82b555:	mov    %rbp,-0x10(%rsp)
  82b55a:	mov    %rdi,%rbx
  82b55d:	mov    %r12,-0x8(%rsp)
  82b562:	sub    $0xf8,%rsp
  82b569:	mov    0x340(%rdi),%rdi
  82b570:	test   %rdi,%rdi
  82b573:	je     82bb18 <CCharacter::attack()+0x5c8>
  82b579:	cmpq   $0x0,0x490(%rbx)
  82b581:	je     82b599 <CCharacter::attack()+0x49>
  82b583:	mov    0x400(%rbx),%rax
  82b58a:	sub    0x3f8(%rbx),%rax
  82b591:	shr    $0x3,%rax
  82b595:	test   %eax,%eax
  82b597:	jne    82b5c0 <CCharacter::attack()+0x70>
  82b599:	xor    %eax,%eax
  82b59b:	mov    0xe0(%rsp),%rbx
  82b5a3:	mov    0xe8(%rsp),%rbp
  82b5ab:	mov    0xf0(%rsp),%r12
  82b5b3:	add    $0xf8,%rsp
  82b5ba:	ret
  82b5bb:	nopl   0x0(%rax,%rax,1)
  82b5c0:	cmpb   $0x0,0x1f5(%rbx)
  82b5c7:	jne    82b599 <CCharacter::attack()+0x49>
  82b5c9:	cmpq   $0x0,0x398(%rbx)
  82b5d1:	je     82b5f6 <CCharacter::attack()+0xa6>
  82b5d3:	cmpb   $0x0,0x267(%rbx)
  82b5da:	jne    82b599 <CCharacter::attack()+0x49>
  82b5dc:	movss  0x380(%rbx),%xmm0
  82b5e4:	ucomiss 0x77920d(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  82b5eb:	jbe    82b5f6 <CCharacter::attack()+0xa6>
  82b5ed:	cmpb   $0x0,0x37d(%rbx)
  82b5f4:	je     82b599 <CCharacter::attack()+0x49>
  82b5f6:	xor    %r12d,%r12d
  82b5f9:	test   %rdi,%rdi
  82b5fc:	je     82b610 <CCharacter::attack()+0xc0>
  82b5fe:	mov    $0xa7,%esi
  82b603:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b608:	test   %al,%al
  82b60a:	jne    82bb40 <CCharacter::attack()+0x5f0>
  82b610:	mov    %rbx,%rdi
  82b613:	call   812580 <CCharacter::attackRange()>
  82b618:	movss  %xmm0,0x3c(%rsp)
  82b61e:	mov    $0x1,%esi
  82b623:	movss  0x4dc(%rbx),%xmm3
  82b62b:	movss  %xmm3,0x38(%rsp)
  82b631:	mov    0x490(%rbx),%rdi
  82b638:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  82b63d:	mov    0x490(%rbx),%rdi
  82b644:	xor    %esi,%esi
  82b646:	mov    %rax,%rbp
  82b649:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  82b64e:	test   %rax,%rax
  82b651:	mov    %rax,%r12
  82b654:	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b65a:	test   %rbp,%rbp
  82b65d:	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b663:	mov    $0x8,%esi
  82b668:	mov    %rbp,%rdi
  82b66b:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b670:	test   %al,%al
  82b672:	je     82b8f0 <CCharacter::attack()+0x3a0>
  82b678:	mov    $0x23,%esi
  82b67d:	mov    %rbp,%rdi
  82b680:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b685:	test   %al,%al
  82b687:	jne    82b7e0 <CCharacter::attack()+0x290>
  82b68d:	mov    $0x23,%esi
  82b692:	mov    %r12,%rdi
  82b695:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b69a:	test   %al,%al
  82b69c:	jne    82bcb8 <CCharacter::attack()+0x768>
  82b6a2:	movss  0x3c(%rsp),%xmm2
  82b6a8:	mulss  0x38(%rsp),%xmm2
  82b6ae:	movaps %xmm2,%xmm1
  82b6b1:	ucomiss %xmm1,%xmm2
  82b6b4:	jp     82b6bc <CCharacter::attack()+0x16c>
  82b6b6:	je     82b820 <CCharacter::attack()+0x2d0>
  82b6bc:	cmpq   $0x0,0x340(%rbx)
  82b6c4:	je     82b820 <CCharacter::attack()+0x2d0>
  82b6ca:	mov    $0x1,%esi
  82b6cf:	mov    %rbx,%rdi
  82b6d2:	movss  %xmm2,0x10(%rsp)
  82b6d8:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b6dd:	movq   %xmm0,0x8(%rsp)
  82b6e3:	mov    0x8(%rsp),%rax
  82b6e8:	mov    $0x1,%esi
  82b6ed:	movss  %xmm1,0x48(%rsp)
  82b6f3:	mov    %rax,0x40(%rsp)
  82b6f8:	mov    %rax,0x80(%rsp)
  82b700:	mov    0x48(%rsp),%eax
  82b704:	mov    %eax,0x88(%rsp)
  82b70b:	mov    0x340(%rbx),%rdi
  82b712:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b717:	movq   %xmm0,0x8(%rsp)
  82b71d:	mov    0x8(%rsp),%rax
  82b722:	lea    0x70(%rsp),%rdi
  82b727:	movss  %xmm1,0x48(%rsp)
  82b72d:	xorps  %xmm3,%xmm3
  82b730:	mov    %rax,0x90(%rsp)
  82b738:	mov    %rax,0x40(%rsp)
  82b73d:	mov    0x48(%rsp),%eax
  82b741:	movss  %xmm3,0x74(%rsp)
  82b747:	movss  0x90(%rsp),%xmm0
  82b750:	subss  0x80(%rsp),%xmm0
  82b759:	movss  %xmm3,0x20(%rsp)
  82b75f:	mov    %eax,0x98(%rsp)
  82b766:	movss  0x98(%rsp),%xmm1
  82b76f:	subss  0x88(%rsp),%xmm1
  82b778:	movss  %xmm0,0x70(%rsp)
  82b77e:	movss  %xmm1,0x78(%rsp)
  82b784:	call   5aa250 <Ogre::Vector3::length() const>
  82b789:	mov    0x340(%rbx),%rax
  82b790:	movss  0x194(%rax),%xmm1
  82b798:	movaps %xmm1,%xmm4
  82b79b:	movss  0x20(%rsp),%xmm3
  82b7a1:	movss  0x10(%rsp),%xmm2
  82b7a7:	cmpnltss %xmm3,%xmm4
  82b7ac:	andps  %xmm4,%xmm1
  82b7af:	movaps %xmm3,%xmm4
  82b7b2:	maxss  0x194(%rbx),%xmm3
  82b7ba:	orps   %xmm1,%xmm4
  82b7bd:	subss  %xmm4,%xmm0
  82b7c1:	subss  %xmm3,%xmm0
  82b7c5:	ucomiss %xmm0,%xmm2
  82b7c8:	jb     82bca0 <CCharacter::attack()+0x750>
  82b7ce:	mov    $0x1,%esi
  82b7d3:	mov    %rbx,%rdi
  82b7d6:	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82b7db:	jmp    82b8fa <CCharacter::attack()+0x3aa>
  82b7e0:	mov    $0x23,%esi
  82b7e5:	mov    %r12,%rdi
  82b7e8:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82b7ed:	test   %al,%al
  82b7ef:	jne    82b68d <CCharacter::attack()+0x13d>
  82b7f5:	mov    %rbx,%rdi
  82b7f8:	call   812360 <CCharacter::rangedRange()>
  82b7fd:	mov    %rbx,%rdi
  82b800:	movss  %xmm0,0x10(%rsp)
  82b806:	call   812470 <CCharacter::meleeRange()>
  82b80b:	movss  0x10(%rsp),%xmm1
  82b811:	movaps %xmm0,%xmm2
  82b814:	jmp    82b6b1 <CCharacter::attack()+0x161>
  82b819:	nopl   0x0(%rax)
  82b820:	cmpq   $0x0,0x350(%rbx)
  82b828:	je     82bc8f <CCharacter::attack()+0x73f>
  82b82e:	cmpq   $0x0,0x340(%rbx)
  82b836:	jne    82b6ca <CCharacter::attack()+0x17a>
  82b83c:	mov    $0x1,%esi
  82b841:	mov    %rbx,%rdi
  82b844:	movss  %xmm2,0x10(%rsp)
  82b84a:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b84f:	movq   %xmm0,0x8(%rsp)
  82b855:	mov    0x8(%rsp),%rax
  82b85a:	mov    $0x1,%esi
  82b85f:	movss  %xmm1,0x48(%rsp)
  82b865:	mov    %rax,0x40(%rsp)
  82b86a:	mov    %rax,0x50(%rsp)
  82b86f:	mov    0x48(%rsp),%eax
  82b873:	mov    %eax,0x58(%rsp)
  82b877:	mov    0x350(%rbx),%rdi
  82b87e:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82b883:	movq   %xmm0,0x8(%rsp)
  82b889:	mov    0x8(%rsp),%rax
  82b88e:	lea    0x70(%rsp),%rdi
  82b893:	movss  %xmm1,0x48(%rsp)
  82b899:	xorps  %xmm3,%xmm3
  82b89c:	mov    %rax,0x60(%rsp)
  82b8a1:	mov    %rax,0x40(%rsp)
  82b8a6:	mov    0x48(%rsp),%eax
  82b8aa:	movss  %xmm3,0x74(%rsp)
  82b8b0:	movss  0x60(%rsp),%xmm0
  82b8b6:	subss  0x50(%rsp),%xmm0
  82b8bc:	movss  %xmm3,0x20(%rsp)
  82b8c2:	mov    %eax,0x68(%rsp)
  82b8c6:	movss  0x68(%rsp),%xmm1
  82b8cc:	subss  0x58(%rsp),%xmm1
  82b8d2:	movss  %xmm0,0x70(%rsp)
  82b8d8:	movss  %xmm1,0x78(%rsp)
  82b8de:	call   5aa250 <Ogre::Vector3::length() const>
  82b8e3:	mov    0x350(%rbx),%rax
  82b8ea:	jmp    82b790 <CCharacter::attack()+0x240>
  82b8ef:	nop
  82b8f0:	xor    %esi,%esi
  82b8f2:	mov    %rbx,%rdi
  82b8f5:	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82b8fa:	mov    0x390(%rbx),%rax
  82b901:	test   %rax,%rax
  82b904:	je     82b599 <CCharacter::attack()+0x49>
  82b90a:	cmpl   $0xffffffff,0x64(%rax)
  82b90e:	je     82b599 <CCharacter::attack()+0x49>
  82b914:	xorps  %xmm3,%xmm3
  82b917:	movss  0x378(%rbx),%xmm0
  82b91f:	ucomiss %xmm3,%xmm0
  82b922:	ja     82bad8 <CCharacter::attack()+0x588>
  82b928:	cmpq   $0x0,0x398(%rbx)
  82b930:	je     82b950 <CCharacter::attack()+0x400>
  82b932:	cmpb   $0x0,0x267(%rbx)
  82b939:	jne    82bad8 <CCharacter::attack()+0x588>
  82b93f:	movss  0x380(%rbx),%xmm0
  82b947:	ucomiss %xmm3,%xmm0
  82b94a:	ja     82bcd8 <CCharacter::attack()+0x788>
  82b950:	movb   $0x1,0x4d0(%rbx)
  82b957:	movb   $0x0,0x37c(%rbx)
  82b95e:	mov    $0x7,%edx
  82b963:	mov    $0x16,%esi
  82b968:	mov    %rbx,%rdi
  82b96b:	movss  %xmm3,0x20(%rsp)
  82b971:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  82b976:	movss  0x20(%rsp),%xmm3
  82b97c:	movaps %xmm0,%xmm1
  82b97f:	ucomiss %xmm0,%xmm3
  82b982:	ja     82bcea <CCharacter::attack()+0x79a>
  82b988:	movss  0x778eac(%rip),%xmm4        # fa483c <vtable for Ogre::FrameListener+0x7c>
  82b990:	movss  0x778e64(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82b998:	divss  %xmm4,%xmm1
  82b99c:	mov    0x390(%rbx),%rax
  82b9a3:	mov    0x718(%rbx),%rdi
  82b9aa:	movss  0x77cd36(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82b9b2:	test   %rdi,%rdi
  82b9b5:	addss  %xmm2,%xmm1
  82b9b9:	divss  0x70(%rax),%xmm1
  82b9be:	maxss  %xmm1,%xmm0
  82b9c2:	movaps %xmm0,%xmm1
  82b9c5:	je     82b9f0 <CCharacter::attack()+0x4a0>
  82b9c7:	mov    $0x1,%esi
  82b9cc:	movss  %xmm0,0x10(%rsp)
  82b9d2:	call   d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>
  82b9d7:	test   %al,%al
  82b9d9:	movss  0x10(%rsp),%xmm1
  82b9df:	je     82b9e9 <CCharacter::attack()+0x499>
  82b9e1:	mulss  0x7a2aaf(%rip),%xmm1        # fce498 <vtable for iInventoryListener+0x58>
  82b9e9:	mov    0x390(%rbx),%rax
  82b9f0:	mov    0x64(%rax),%esi
  82b9f3:	mov    0x200(%rbx),%rdi
  82b9fa:	movss  %xmm1,0x10(%rsp)
  82ba00:	lea    0xc0(%rsp),%rbp
  82ba08:	call   89ab60 <CGenericModel::getAnimationLengthSeconds(int) const>
  82ba0d:	movss  0x10(%rsp),%xmm1
  82ba13:	mov    0x200(%rbx),%rdi
  82ba1a:	divss  %xmm1,%xmm0
  82ba1e:	movss  %xmm0,0x378(%rbx)
  82ba26:	movss  %xmm1,0x10(%rsp)
  82ba2c:	call   8a68e0 <CGenericModel::clearQueuedAnimations()>
  82ba31:	mov    0x390(%rbx),%rax
  82ba38:	xor    %edx,%edx
  82ba3a:	mov    %rbx,%rdi
  82ba3d:	movss  0x77cd1b(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  82ba45:	movss  0x10(%rsp),%xmm1
  82ba4b:	mov    0x64(%rax),%esi
  82ba4e:	movss  0x77cc92(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82ba56:	call   811130 <CCharacter::blendAnimation(int, bool, float, float, float)>
  82ba5b:	lea    0xde(%rsp),%rdx
  82ba63:	mov    $0xfc993a,%esi
  82ba68:	mov    %rbp,%rdi
  82ba6b:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  82ba70:	mov    0x200(%rbx),%rdi
  82ba77:	movss  0x778d7d(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82ba7f:	movss  0x77cc61(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  82ba87:	mov    $0x1,%edx
  82ba8c:	mov    %rbp,%rsi
  82ba8f:	call   8a42c0 <CGenericModel::queueBlendAnimation(std::string const&, bool, float, float)>
  82ba94:	mov    %rbp,%rdi
  82ba97:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  82ba9c:	mov    0x390(%rbx),%rax
  82baa3:	cmpb   $0x0,0x18(%rax)
  82baa7:	je     82bad8 <CCharacter::attack()+0x588>
  82baa9:	cmpq   $0x0,0x498(%rbx)
  82bab1:	je     82bad8 <CCharacter::attack()+0x588>
  82bab3:	mov    0x298(%rbx),%rdi
  82baba:	test   %rdi,%rdi
  82babd:	je     82bad8 <CCharacter::attack()+0x588>
  82babf:	xorps  %xmm1,%xmm1
  82bac2:	mov    0x58(%rbx),%rdx
  82bac6:	xor    %ecx,%ecx
  82bac8:	mov    $0x1a,%esi
  82bacd:	movaps %xmm1,%xmm0
  82bad0:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  82bad5:	nopl   (%rax)
  82bad8:	movss  0x77cbf0(%rip),%xmm1        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  82bae0:	mov    $0x1,%eax
  82bae5:	movaps %xmm1,%xmm2
  82bae8:	movss  0x284(%rbx),%xmm0
  82baf0:	cmpnltss %xmm0,%xmm2
  82baf5:	movaps %xmm0,%xmm3
  82baf8:	movaps %xmm2,%xmm0
  82bafb:	andps  %xmm2,%xmm3
  82bafe:	andnps %xmm1,%xmm0
  82bb01:	orps   %xmm3,%xmm0
  82bb04:	movss  %xmm0,0x284(%rbx)
  82bb0c:	jmp    82b59b <CCharacter::attack()+0x4b>
  82bb11:	nopl   0x0(%rax)
  82bb18:	cmpq   $0x0,0x350(%rbx)
  82bb20:	jne    82b579 <CCharacter::attack()+0x29>
  82bb26:	cmpb   $0x0,0x266(%rbx)
  82bb2d:	je     82b599 <CCharacter::attack()+0x49>
  82bb33:	jmp    82b579 <CCharacter::attack()+0x29>
  82bb38:	nopl   0x0(%rax,%rax,1)
  82bb40:	lea    0xd0(%rsp),%rbp
  82bb48:	lea    0xdf(%rsp),%rdx
  82bb50:	mov    $0xfa7dc8,%esi
  82bb55:	mov    %rbp,%rdi
  82bb58:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  82bb5d:	mov    0x340(%rbx),%rdi
  82bb64:	mov    %rbp,%rsi
  82bb67:	mov    $0x1,%r12d
  82bb6d:	call   7ff390 <CBaseUnit::hasUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  82bb72:	test   %al,%al
  82bb74:	mov    %rbp,%rdi
  82bb77:	setne  %r12b
  82bb7b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  82bb80:	test   %r12b,%r12b
  82bb83:	je     82b610 <CCharacter::attack()+0xc0>
  82bb89:	mov    0x498(%rbx),%rdi
  82bb90:	test   %rdi,%rdi
  82bb93:	je     82bc70 <CCharacter::attack()+0x720>
  82bb99:	mov    $0x23,%esi
  82bb9e:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82bba3:	test   %al,%al
  82bba5:	je     82bc70 <CCharacter::attack()+0x720>
  82bbab:	cmpb   $0x0,0x266(%rbx)
  82bbb2:	jne    82b610 <CCharacter::attack()+0xc0>
  82bbb8:	mov    0x340(%rbx),%rdi
  82bbbf:	mov    $0x1,%esi
  82bbc4:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82bbc9:	movq   %xmm0,0x8(%rsp)
  82bbcf:	mov    0x8(%rsp),%rax
  82bbd4:	mov    $0x1,%esi
  82bbd9:	movss  %xmm1,0x48(%rsp)
  82bbdf:	mov    %rax,0x40(%rsp)
  82bbe4:	mov    %rax,0xa0(%rsp)
  82bbec:	mov    0x48(%rsp),%eax
  82bbf0:	mov    %eax,0xa8(%rsp)
  82bbf7:	movss  0xa8(%rsp),%xmm0
  82bc00:	movss  %xmm0,0x38(%rsp)
  82bc06:	mov    0x340(%rbx),%rdi
  82bc0d:	call   9e7080 <CPositionableObject::getPosition(bool)>
  82bc12:	movq   %xmm0,0x8(%rsp)
  82bc18:	mov    0x8(%rsp),%rax
  82bc1d:	xor    %esi,%esi
  82bc1f:	movss  %xmm1,0x48(%rsp)
  82bc25:	mov    %rax,0xb0(%rsp)
  82bc2d:	mov    %rax,0x40(%rsp)
  82bc32:	mov    0x48(%rsp),%eax
  82bc36:	movss  0xb0(%rsp),%xmm0
  82bc3f:	mov    %eax,0xb8(%rsp)
  82bc46:	mov    0x68(%rbx),%rax
  82bc4a:	test   %rax,%rax
  82bc4d:	je     82bc53 <CCharacter::attack()+0x703>
  82bc4f:	mov    0x18(%rax),%rsi
  82bc53:	movss  0x38(%rsp),%xmm1
  82bc59:	mov    %rbx,%rdi
  82bc5c:	call   82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  82bc61:	xor    %eax,%eax
  82bc63:	jmp    82b59b <CCharacter::attack()+0x4b>
  82bc68:	nopl   0x0(%rax,%rax,1)
  82bc70:	mov    0x340(%rbx),%rdi
  82bc77:	mov    $0x1,%edx
  82bc7c:	mov    %rbx,%rsi
  82bc7f:	mov    (%rdi),%rax
  82bc82:	call   *0x350(%rax)
  82bc88:	xor    %eax,%eax
  82bc8a:	jmp    82b59b <CCharacter::attack()+0x4b>
  82bc8f:	ucomiss %xmm1,%xmm2
  82bc92:	jp     82bca0 <CCharacter::attack()+0x750>
  82bc94:	je     82b8fa <CCharacter::attack()+0x3aa>
  82bc9a:	nopw   0x0(%rax,%rax,1)
  82bca0:	mov    $0x2,%esi
  82bca5:	mov    %rbx,%rdi
  82bca8:	call   811bc0 <CCharacter::selectAttack(EATTACK_RANGE_TYPE)>
  82bcad:	jmp    82b8fa <CCharacter::attack()+0x3aa>
  82bcb2:	nopw   0x0(%rax,%rax,1)
  82bcb8:	mov    $0x23,%esi
  82bcbd:	mov    %rbp,%rdi
  82bcc0:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  82bcc5:	test   %al,%al
  82bcc7:	jne    82b6a2 <CCharacter::attack()+0x152>
  82bccd:	jmp    82b7f5 <CCharacter::attack()+0x2a5>
  82bcd2:	nopw   0x0(%rax,%rax,1)
  82bcd8:	cmpb   $0x0,0x37d(%rbx)
  82bcdf:	je     82bad8 <CCharacter::attack()+0x588>
  82bce5:	jmp    82b950 <CCharacter::attack()+0x400>
  82bcea:	mov    $0x7,%edx
  82bcef:	mov    $0x8c,%esi
  82bcf4:	mov    %rbx,%rdi
  82bcf7:	movss  %xmm3,0x20(%rsp)
  82bcfd:	movss  %xmm0,0x10(%rsp)
  82bd03:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  82bd08:	movss  0x778b2c(%rip),%xmm4        # fa483c <vtable for Ogre::FrameListener+0x7c>
  82bd10:	divss  %xmm4,%xmm0
  82bd14:	movss  0x778ae0(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82bd1c:	movss  0x10(%rsp),%xmm1
  82bd22:	movss  0x20(%rsp),%xmm3
  82bd28:	ucomiss %xmm0,%xmm2
  82bd2b:	ja     82bd40 <CCharacter::attack()+0x7f0>
  82bd2d:	movaps %xmm2,%xmm0
  82bd30:	movaps %xmm2,%xmm3
  82bd33:	subss  %xmm0,%xmm3
  82bd37:	mulss  %xmm3,%xmm1
  82bd3b:	jmp    82b998 <CCharacter::attack()+0x448>
  82bd40:	maxss  %xmm3,%xmm0
  82bd44:	jmp    82bd30 <CCharacter::attack()+0x7e0>
  82bd46:	mov    %rax,%rdi
  82bd49:	call   554498 <_Unwind_Resume@plt>
  82bd4e:	test   %r12b,%r12b
  82bd51:	mov    %rax,%rbx
  82bd54:	je     82bd63 <CCharacter::attack()+0x813>
  82bd56:	lea    0xd0(%rsp),%rdi
  82bd5e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  82bd63:	mov    %rbx,%rax
  82bd66:	jmp    82bd46 <CCharacter::attack()+0x7f6>
  82bd68:	mov    %rbp,%rdi
  82bd6b:	mov    %rax,0x30(%rsp)
  82bd70:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  82bd75:	mov    0x30(%rsp),%rax
  82bd7a:	jmp    82bd46 <CCharacter::attack()+0x7f6>
  82bd7c:	jmp    82bd46 <CCharacter::attack()+0x7f6>
