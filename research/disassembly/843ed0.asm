
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000843ed0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)>:
  843ed0:	push   %r15
  843ed2:	push   %r14
  843ed4:	push   %r13
  843ed6:	mov    %r9d,%r13d
  843ed9:	push   %r12
  843edb:	mov    %rcx,%r12
  843ede:	push   %rbp
  843edf:	mov    %rdx,%rbp
  843ee2:	push   %rbx
  843ee3:	mov    %rdi,%rbx
  843ee6:	sub    $0x788,%rsp
  843eed:	test   %rdx,%rdx
  843ef0:	mov    %rsi,0x68(%rsp)
  843ef5:	mov    %r8d,0x78(%rsp)
  843efa:	movss  %xmm0,0x64(%rsp)
  843f00:	movss  %xmm1,0x74(%rsp)
  843f06:	je     8440d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x200>
  843f0c:	mov    0x330(%rdx),%eax
  843f12:	cmp    $0x5,%eax
  843f15:	je     8440d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x200>
  843f1b:	cmp    $0x6,%eax
  843f1e:	je     8440d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x200>
  843f24:	mov    $0xa7,%esi
  843f29:	xor    %r14d,%r14d
  843f2c:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  843f31:	test   %al,%al
  843f33:	jne    844070 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a0>
  843f39:	test   %r12,%r12
  843f3c:	mov    0x390(%rbx),%r14
  843f43:	je     8440f1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x221>
  843f49:	mov    %rbx,%rdi
  843f4c:	call   80fc20 <CCharacter::getWeaponInLeftHand()>
  843f51:	cmp    %rax,%r12
  843f54:	je     8440e4 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x214>
  843f5a:	mov    %rbx,%rdi
  843f5d:	call   80fc50 <CCharacter::getWeaponInRightHand()>
  843f62:	cmp    %rax,%r12
  843f65:	je     8458da <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a0a>
  843f6b:	mov    0x2a8(%r12),%r14
  843f73:	test   %r14,%r14
  843f76:	je     8458da <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a0a>
  843f7c:	mov    %rbp,%rdi
  843f7f:	call   8163a0 <CCharacter::getDmgToReflectFromMissile()>
  843f84:	test   %r12,%r12
  843f87:	movss  %xmm0,0x50(%rsp)
  843f8d:	setne  0x9f(%rsp)
  843f95:	je     844111 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x241>
  843f9b:	xorps  %xmm0,%xmm0
  843f9e:	movss  0x50(%rsp),%xmm1
  843fa4:	ucomiss %xmm0,%xmm1
  843fa7:	jbe    844111 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x241>
  843fad:	mov    $0x23,%esi
  843fb2:	mov    %r12,%rdi
  843fb5:	movss  %xmm0,0x30(%rsp)
  843fbb:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  843fc0:	test   %al,%al
  843fc2:	movss  0x30(%rsp),%xmm0
  843fc8:	je     844111 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x241>
  843fce:	mov    0x298(%rbx),%rdi
  843fd5:	test   %rdi,%rdi
  843fd8:	je     843fed <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x11d>
  843fda:	mov    0x58(%rbp),%rdx
  843fde:	movaps %xmm0,%xmm1
  843fe1:	xor    %ecx,%ecx
  843fe3:	mov    $0x22,%esi
  843fe8:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  843fed:	xor    %ecx,%ecx
  843fef:	xor    %edx,%edx
  843ff1:	xor    %esi,%esi
  843ff3:	mov    $0x138,%edi
  843ff8:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  843ffd:	xorps  %xmm2,%xmm2
  844000:	xor    %r8d,%r8d
  844003:	movss  0x7607f1(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84400b:	xor    %ecx,%ecx
  84400d:	movss  0x7646c3(%rip),%xmm0        # fa86d8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x38>
  844015:	mov    $0x1,%edx
  84401a:	mov    $0x3d,%esi
  84401f:	mov    %rax,%rdi
  844022:	mov    %rax,%r12
  844025:	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  84402a:	movss  0x50(%rsp),%xmm2
  844030:	xor    %esi,%esi
  844032:	movss  %xmm2,0xcc(%r12)
  84403c:	mov    %r12,%rdi
  84403f:	call   7dc9f0 <CEffect::calculateBaseValue(CEffect::ECALCULATETYPES)>
  844044:	mov    (%rbx),%rax
  844047:	mov    %r12,%rcx
  84404a:	mov    %rbp,%rdx
  84404d:	mov    %rbp,%rsi
  844050:	mov    %rbx,%rdi
  844053:	call   *0x240(%rax)
  844059:	mov    (%r12),%rax
  84405d:	mov    %r12,%rdi
  844060:	call   *0x8(%rax)
  844063:	xor    %eax,%eax
  844065:	jmp    8440d2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x202>
  844067:	nopw   0x0(%rax,%rax,1)
  844070:	lea    0x770(%rsp),%r15
  844078:	lea    0x77f(%rsp),%rdx
  844080:	mov    $0xfa7dc8,%esi
  844085:	mov    %r15,%rdi
  844088:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  84408d:	mov    %r15,%rsi
  844090:	mov    %rbx,%rdi
  844093:	mov    $0x1,%r14d
  844099:	call   7ff390 <CBaseUnit::hasUnitTheme(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  84409e:	mov    0x770(%rsp),%rdi
  8440a6:	test   %al,%al
  8440a8:	setne  %r14b
  8440ac:	sub    $0x18,%rdi
  8440b0:	cmp    $0x1424540,%rdi
  8440b7:	jne    846ea7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2fd7>
  8440bd:	test   %r14b,%r14b
  8440c0:	je     843f39 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x69>
  8440c6:	cs nopw 0x0(%rax,%rax,1)
  8440d0:	xor    %eax,%eax
  8440d2:	add    $0x788,%rsp
  8440d9:	pop    %rbx
  8440da:	pop    %rbp
  8440db:	pop    %r12
  8440dd:	pop    %r13
  8440df:	pop    %r14
  8440e1:	pop    %r15
  8440e3:	ret
  8440e4:	mov    0x2a8(%r12),%r14
  8440ec:	jmp    843f7c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xac>
  8440f1:	mov    0x498(%rbx),%r12
  8440f8:	test   %r12,%r12
  8440fb:	jne    843f49 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x79>
  844101:	mov    %rbp,%rdi
  844104:	call   8163a0 <CCharacter::getDmgToReflectFromMissile()>
  844109:	movb   $0x0,0x9f(%rsp)
  844111:	test   %r14,%r14
  844114:	je     8440d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x200>
  844116:	mov    %rbp,%rsi
  844119:	mov    %rbx,%rdi
  84411c:	call   838410 <CCharacter::rollCritical(CCharacter*)>
  844121:	mov    %al,0x87(%rsp)
  844128:	mov    0x78(%rsp),%eax
  84412c:	mov    %rbp,%rdx
  84412f:	mov    %r14,%rsi
  844132:	mov    %rbx,%rdi
  844135:	shr    $0xa,%eax
  844138:	and    $0x1,%eax
  84413b:	mov    %al,0x8f(%rsp)
  844142:	call   815d40 <CCharacter::maxDamage(CAttackDescription*, CCharacter*)>
  844147:	movss  0x64(%rsp),%xmm1
  84414d:	mov    %eax,%r15d
  844150:	ucomiss 0x7606a5(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  844157:	movss  0x70(%r14),%xmm0
  84415d:	movss  %xmm0,0x98(%rsp)
  844166:	jp     845338 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1468>
  84416c:	jne    845338 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1468>
  844172:	cmpb   $0x0,0x8f(%rsp)
  84417a:	jne    84530f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x143f>
  844180:	cvtsi2ss %r15d,%xmm2
  844185:	movss  0x760683(%rip),%xmm0        # fa4810 <vtable for Ogre::FrameListener+0x50>
  84418d:	mulss  %xmm2,%xmm0
  844191:	movss  %xmm0,0x50(%rsp)
  844197:	call   553678 <ceilf@plt>
  84419c:	cvttss2si %xmm0,%eax
  8441a0:	xor    %edi,%edi
  8441a2:	mov    0xcc72e0(%rip),%esi        # 150b488 <KSETTINGS_COMBAT_LOG>
  8441a8:	mov    %eax,0x54(%rsp)
  8441ac:	cmpq   $0x0,0x68(%rbx)
  8441b1:	je     8441c7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f7>
  8441b3:	mov    %esi,0x48(%rsp)
  8441b7:	call   a54490 <CMasterResourceManager::getSingleton()>
  8441bc:	mov    0x48(%rsp),%esi
  8441c0:	mov    0x90(%rax),%rdi
  8441c7:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  8441cc:	mov    0x54(%rsp),%edi
  8441d0:	test   %eax,%eax
  8441d2:	mov    %r15d,%esi
  8441d5:	setg   0x8e(%rsp)
  8441dd:	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8441e2:	cmpb   $0x0,0x8e(%rsp)
  8441ea:	mov    %eax,0x94(%rsp)
  8441f1:	jne    845a13 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1b43>
  8441f7:	cmpb   $0x0,0x87(%rsp)
  8441ff:	jne    845953 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a83>
  844205:	mov    0x78(%r14),%r14d
  844209:	mov    0x94(%rsp),%ecx
  844210:	cmp    $0x7,%r13d
  844214:	movss  0x74(%rsp),%xmm0
  84421a:	mov    %rbp,%rdi
  84421d:	cmovne %r13d,%r14d
  844221:	mov    %ecx,%esi
  844223:	mov    %r14d,%edx
  844226:	call   837c00 <CCharacter::modifyDamage(int, EDAMAGE_TYPES, int, float)>
  84422b:	cmpb   $0x0,0x8e(%rsp)
  844233:	mov    %eax,0x7c(%rsp)
  844237:	jne    8458e7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a17>
  84423d:	mov    0x7c(%rsp),%eax
  844241:	mov    %r14d,0xb0(%rsp)
  844249:	xor    %r14d,%r14d
  84424c:	mov    %r15d,0x88(%rsp)
  844254:	mov    %rbp,0x58(%rsp)
  844259:	mov    %r13d,0x54(%rsp)
  84425e:	mov    %eax,0xb4(%rsp)
  844265:	jmp    844533 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x663>
  84426a:	nopw   0x0(%rax,%rax,1)
  844270:	mov    %r14d,%esi
  844273:	mov    %r12,%rdi
  844276:	call   86d440 <CEquipment::getDamageBonus(EDAMAGE_TYPES)>
  84427b:	test   %eax,%eax
  84427d:	mov    %eax,%ebp
  84427f:	setle  0x50(%rsp)
  844284:	cmpl   $0x7,0x54(%rsp)
  844289:	mov    0x54(%rsp),%r13d
  84428e:	mov    %r14d,%edx
  844291:	mov    $0xa,%esi
  844296:	mov    %rbx,%rdi
  844299:	cmove  %r14d,%r13d
  84429d:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8442a2:	call   553678 <ceilf@plt>
  8442a7:	cvttss2si %xmm0,%r15d
  8442ac:	test   %r15d,%r15d
  8442af:	jg     8442bc <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3ec>
  8442b1:	cmpb   $0x0,0x50(%rsp)
  8442b6:	jne    844525 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x655>
  8442bc:	movss  0x64(%rsp),%xmm0
  8442c2:	ucomiss 0x760533(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8442c9:	jp     8442cd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3fd>
  8442cb:	je     8442db <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x40b>
  8442cd:	cvtsi2ss %ebp,%xmm0
  8442d1:	mulss  0x64(%rsp),%xmm0
  8442d7:	cvttss2si %xmm0,%ebp
  8442db:	mov    %r13d,%edx
  8442de:	mov    $0x19,%esi
  8442e3:	mov    %rbx,%rdi
  8442e6:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8442eb:	movaps %xmm0,%xmm2
  8442ee:	mov    $0x6,%edx
  8442f3:	mov    $0x19,%esi
  8442f8:	mov    %rbx,%rdi
  8442fb:	divss  0x760539(%rip),%xmm2        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844303:	movss  %xmm2,0x30(%rsp)
  844309:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84430e:	movaps %xmm0,%xmm1
  844311:	test   %r12,%r12
  844314:	movss  0x30(%rsp),%xmm2
  84431a:	divss  0x76051a(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844322:	addss  %xmm2,%xmm1
  844326:	je     8445d8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x708>
  84432c:	mov    $0x23,%esi
  844331:	mov    %r12,%rdi
  844334:	movss  %xmm1,0x30(%rsp)
  84433a:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84433f:	test   %al,%al
  844341:	movss  0x30(%rsp),%xmm1
  844347:	je     844580 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x6b0>
  84434d:	mov    %rbx,%rdi
  844350:	mov    $0x7,%edx
  844355:	mov    $0x10,%esi
  84435a:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84435f:	divss  0x7604d5(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844367:	movss  0x30(%rsp),%xmm1
  84436d:	mov    %rbx,%rdi
  844370:	addss  %xmm1,%xmm0
  844374:	movss  %xmm0,0x30(%rsp)
  84437a:	call   8139a0 <CCharacter::dexterity()>
  84437f:	cvtsi2ss %eax,%xmm1
  844383:	mov    $0xa2,%esi
  844388:	movss  0x30(%rsp),%xmm0
  84438e:	mov    %r12,%rdi
  844391:	divss  0x7604a3(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844399:	addss  %xmm1,%xmm0
  84439d:	movss  %xmm0,0x50(%rsp)
  8443a3:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8443a8:	test   %al,%al
  8443aa:	je     844570 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x6a0>
  8443b0:	mov    $0x7,%edx
  8443b5:	mov    $0x63,%esi
  8443ba:	mov    %rbx,%rdi
  8443bd:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8443c2:	divss  0x760472(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8443ca:	addss  0x50(%rsp),%xmm0
  8443d0:	movss  %xmm0,0x50(%rsp)
  8443d6:	mov    $0xa3,%esi
  8443db:	mov    %r12,%rdi
  8443de:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8443e3:	test   %al,%al
  8443e5:	je     8445c0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x6f0>
  8443eb:	mov    $0x7,%edx
  8443f0:	mov    $0x66,%esi
  8443f5:	mov    %rbx,%rdi
  8443f8:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8443fd:	divss  0x760437(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844405:	addss  0x50(%rsp),%xmm0
  84440b:	movss  %xmm0,0x50(%rsp)
  844411:	mov    $0xa4,%esi
  844416:	mov    %r12,%rdi
  844419:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84441e:	test   %al,%al
  844420:	je     844448 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x578>
  844422:	mov    $0x7,%edx
  844427:	mov    $0x67,%esi
  84442c:	mov    %rbx,%rdi
  84442f:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844434:	divss  0x760400(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84443c:	addss  0x50(%rsp),%xmm0
  844442:	movss  %xmm0,0x50(%rsp)
  844448:	test   %r13d,%r13d
  84444b:	jg     844638 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x768>
  844451:	mov    0x490(%rbx),%rdi
  844458:	mov    $0x1,%esi
  84445d:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  844462:	test   %rax,%rax
  844465:	je     8444c2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x5f2>
  844467:	mov    0x490(%rbx),%rdi
  84446e:	xor    %esi,%esi
  844470:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  844475:	test   %rax,%rax
  844478:	je     8444c2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x5f2>
  84447a:	mov    0x490(%rbx),%rdi
  844481:	mov    $0x1,%esi
  844486:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84448b:	mov    $0x15,%esi
  844490:	mov    %rax,%rdi
  844493:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  844498:	test   %al,%al
  84449a:	jne    8444c2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x5f2>
  84449c:	mov    $0x7,%edx
  8444a1:	mov    $0x58,%esi
  8444a6:	mov    %rbx,%rdi
  8444a9:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8444ae:	divss  0x760386(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8444b6:	addss  0x50(%rsp),%xmm0
  8444bc:	movss  %xmm0,0x50(%rsp)
  8444c2:	cvtsi2ss %ebp,%xmm0
  8444c6:	mulss  0x50(%rsp),%xmm0
  8444cc:	call   553678 <ceilf@plt>
  8444d1:	cvttss2si %xmm0,%eax
  8444d5:	cmpb   $0x0,0x8f(%rsp)
  8444dd:	lea    (%rax,%rbp,1),%ebp
  8444e0:	je     844504 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x634>
  8444e2:	cvtsi2ss %ebp,%xmm0
  8444e6:	movss  0x78a042(%rip),%xmm1        # fce530 <vtable for iInventoryListener+0xf0>
  8444ee:	mulss  0x98(%rsp),%xmm1
  8444f7:	divss  %xmm1,%xmm0
  8444fb:	call   553678 <ceilf@plt>
  844500:	cvttss2si %xmm0,%ebp
  844504:	cmpb   $0x0,0x87(%rsp)
  84450c:	jne    844670 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7a0>
  844512:	add    0x88(%rsp),%r15d
  84451a:	lea    (%r15,%rbp,1),%ebp
  84451e:	mov    %ebp,0x88(%rsp)
  844525:	add    $0x1,%r14d
  844529:	cmp    $0x7,%r14d
  84452d:	je     8446b8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x7e8>
  844533:	test   %r12,%r12
  844536:	jne    844270 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3a0>
  84453c:	xor    %ebp,%ebp
  84453e:	test   %r14d,%r14d
  844541:	movb   $0x1,0x50(%rsp)
  844546:	je     844284 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3b4>
  84454c:	mov    0x3f8(%rbx),%rax
  844553:	movslq %r14d,%rdx
  844556:	mov    (%rax),%rax
  844559:	mov    0x24(%rax,%rdx,4),%ebp
  84455d:	test   %ebp,%ebp
  84455f:	setle  0x50(%rsp)
  844564:	jmp    844284 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3b4>
  844569:	nopl   0x0(%rax)
  844570:	test   %r12,%r12
  844573:	jne    8443d6 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x506>
  844579:	jmp    844448 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x578>
  84457e:	xchg   %ax,%ax
  844580:	mov    %rbx,%rdi
  844583:	mov    $0x7,%edx
  844588:	mov    $0xf,%esi
  84458d:	movss  %xmm1,0x30(%rsp)
  844593:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844598:	divss  0x76029c(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8445a0:	mov    %rbx,%rdi
  8445a3:	movss  0x30(%rsp),%xmm1
  8445a9:	addss  %xmm1,%xmm0
  8445ad:	movss  %xmm0,0x30(%rsp)
  8445b3:	call   813930 <CCharacter::strength()>
  8445b8:	jmp    84437f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x4af>
  8445bd:	nopl   (%rax)
  8445c0:	test   %r12,%r12
  8445c3:	jne    844411 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x541>
  8445c9:	nopl   0x0(%rax)
  8445d0:	jmp    844448 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x578>
  8445d5:	nopl   (%rax)
  8445d8:	mov    $0x7,%edx
  8445dd:	mov    $0xf,%esi
  8445e2:	mov    %rbx,%rdi
  8445e5:	movss  %xmm1,0x30(%rsp)
  8445eb:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8445f0:	divss  0x760244(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8445f8:	mov    %rbx,%rdi
  8445fb:	movss  0x30(%rsp),%xmm1
  844601:	addss  %xmm1,%xmm0
  844605:	movss  %xmm0,0x30(%rsp)
  84460b:	call   813930 <CCharacter::strength()>
  844610:	cvtsi2ss %eax,%xmm1
  844614:	movss  0x30(%rsp),%xmm0
  84461a:	divss  0x76021a(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844622:	addss  %xmm1,%xmm0
  844626:	movss  %xmm0,0x50(%rsp)
  84462c:	jmp    844448 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x578>
  844631:	nopl   0x0(%rax)
  844638:	cmpb   $0x0,0x9f(%rsp)
  844640:	je     844451 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x581>
  844646:	mov    %rbx,%rdi
  844649:	call   8144c0 <CCharacter::magic()>
  84464e:	cvtsi2ss %eax,%xmm0
  844652:	divss  0x7601e2(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84465a:	addss  0x50(%rsp),%xmm0
  844660:	movss  %xmm0,0x50(%rsp)
  844666:	jmp    844451 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x581>
  84466b:	nopl   0x0(%rax,%rax,1)
  844670:	cvtsi2ss %ebp,%xmm0
  844674:	mov    $0x7,%edx
  844679:	mov    $0x59,%esi
  84467e:	mov    %rbx,%rdi
  844681:	mulss  0x760187(%rip),%xmm0        # fa4810 <vtable for Ogre::FrameListener+0x50>
  844689:	cvttss2si %xmm0,%r13d
  84468e:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844693:	divss  0x7601a1(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84469b:	cvtsi2ss %r13d,%xmm1
  8446a0:	lea    0x0(%r13,%rbp,1),%ebp
  8446a5:	mulss  %xmm0,%xmm1
  8446a9:	cvttss2si %xmm1,%eax
  8446ad:	add    %eax,%ebp
  8446af:	jmp    844512 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x642>
  8446b4:	nopl   0x0(%rax)
  8446b8:	mov    0x94(%rsp),%eax
  8446bf:	mov    0x58(%rsp),%rbp
  8446c4:	xor    %r14b,%r14b
  8446c7:	mov    0x54(%rsp),%r13d
  8446cc:	movl   $0x1,0x80(%rsp)
  8446d7:	mov    %eax,0x90(%rsp)
  8446de:	jmp    844a58 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb88>
  8446e3:	nopl   0x0(%rax,%rax,1)
  8446e8:	mov    %r14d,%esi
  8446eb:	mov    %r12,%rdi
  8446ee:	call   86d440 <CEquipment::getDamageBonus(EDAMAGE_TYPES)>
  8446f3:	test   %eax,%eax
  8446f5:	mov    %eax,%r15d
  8446f8:	setle  0x50(%rsp)
  8446fd:	cmp    $0x7,%r13d
  844701:	mov    %r13d,%edx
  844704:	mov    $0xa,%esi
  844709:	cmove  %r14d,%edx
  84470d:	mov    %rbx,%rdi
  844710:	mov    %edx,0x54(%rsp)
  844714:	mov    %r14d,%edx
  844717:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84471c:	call   553678 <ceilf@plt>
  844721:	cvttss2si %xmm0,%eax
  844725:	test   %eax,%eax
  844727:	mov    %eax,0x58(%rsp)
  84472b:	jg     844738 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x868>
  84472d:	cmpb   $0x0,0x50(%rsp)
  844732:	jne    844a4a <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb7a>
  844738:	movss  0x64(%rsp),%xmm0
  84473e:	ucomiss 0x7600b7(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  844745:	jp     844749 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x879>
  844747:	je     844759 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x889>
  844749:	cvtsi2ss %r15d,%xmm0
  84474e:	mulss  0x64(%rsp),%xmm0
  844754:	cvttss2si %xmm0,%r15d
  844759:	mov    0x54(%rsp),%edx
  84475d:	mov    $0x19,%esi
  844762:	mov    %rbx,%rdi
  844765:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84476a:	movaps %xmm0,%xmm2
  84476d:	mov    $0x6,%edx
  844772:	mov    $0x19,%esi
  844777:	mov    %rbx,%rdi
  84477a:	divss  0x7600ba(%rip),%xmm2        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844782:	movss  %xmm2,0x30(%rsp)
  844788:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84478d:	movaps %xmm0,%xmm1
  844790:	test   %r12,%r12
  844793:	movss  0x30(%rsp),%xmm2
  844799:	divss  0x76009b(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8447a1:	addss  %xmm2,%xmm1
  8447a5:	je     844b28 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xc58>
  8447ab:	mov    $0x23,%esi
  8447b0:	mov    %r12,%rdi
  8447b3:	movss  %xmm1,0x30(%rsp)
  8447b9:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  8447be:	test   %al,%al
  8447c0:	movss  0x30(%rsp),%xmm1
  8447c6:	je     844ac8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xbf8>
  8447cc:	mov    $0x7,%edx
  8447d1:	mov    $0x10,%esi
  8447d6:	mov    %rbx,%rdi
  8447d9:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8447de:	divss  0x760056(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8447e6:	movss  0x30(%rsp),%xmm1
  8447ec:	mov    %rbx,%rdi
  8447ef:	addss  %xmm1,%xmm0
  8447f3:	movss  %xmm0,0x30(%rsp)
  8447f9:	call   8139a0 <CCharacter::dexterity()>
  8447fe:	cvtsi2ss %eax,%xmm1
  844802:	movss  0x30(%rsp),%xmm0
  844808:	divss  0x76002c(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844810:	addss  %xmm1,%xmm0
  844814:	movss  %xmm0,0x50(%rsp)
  84481a:	mov    $0xa2,%esi
  84481f:	mov    %r12,%rdi
  844822:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  844827:	test   %al,%al
  844829:	je     844a98 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xbc8>
  84482f:	mov    $0x7,%edx
  844834:	mov    $0x63,%esi
  844839:	mov    %rbx,%rdi
  84483c:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844841:	divss  0x75fff3(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844849:	addss  0x50(%rsp),%xmm0
  84484f:	movss  %xmm0,0x50(%rsp)
  844855:	mov    $0xa3,%esi
  84485a:	mov    %r12,%rdi
  84485d:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  844862:	test   %al,%al
  844864:	je     844ab0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xbe0>
  84486a:	mov    $0x7,%edx
  84486f:	mov    $0x66,%esi
  844874:	mov    %rbx,%rdi
  844877:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  84487c:	divss  0x75ffb8(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844884:	addss  0x50(%rsp),%xmm0
  84488a:	movss  %xmm0,0x50(%rsp)
  844890:	mov    $0xa4,%esi
  844895:	mov    %r12,%rdi
  844898:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84489d:	test   %al,%al
  84489f:	je     8448c7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x9f7>
  8448a1:	mov    $0x7,%edx
  8448a6:	mov    $0x67,%esi
  8448ab:	mov    %rbx,%rdi
  8448ae:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8448b3:	divss  0x75ff81(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8448bb:	addss  0x50(%rsp),%xmm0
  8448c1:	movss  %xmm0,0x50(%rsp)
  8448c7:	mov    0x54(%rsp),%eax
  8448cb:	test   %eax,%eax
  8448cd:	jg     844d60 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe90>
  8448d3:	mov    0x490(%rbx),%rdi
  8448da:	mov    $0x1,%esi
  8448df:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  8448e4:	test   %rax,%rax
  8448e7:	je     844944 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa74>
  8448e9:	mov    0x490(%rbx),%rdi
  8448f0:	xor    %esi,%esi
  8448f2:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  8448f7:	test   %rax,%rax
  8448fa:	je     844944 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa74>
  8448fc:	mov    0x490(%rbx),%rdi
  844903:	mov    $0x1,%esi
  844908:	call   91b460 <CInventory::getEquipmentEquippedAt(EEQUIP_LOCATIONS)>
  84490d:	mov    $0x15,%esi
  844912:	mov    %rax,%rdi
  844915:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  84491a:	test   %al,%al
  84491c:	jne    844944 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa74>
  84491e:	mov    $0x7,%edx
  844923:	mov    $0x58,%esi
  844928:	mov    %rbx,%rdi
  84492b:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844930:	divss  0x75ff04(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844938:	addss  0x50(%rsp),%xmm0
  84493e:	movss  %xmm0,0x50(%rsp)
  844944:	cvtsi2ss %r15d,%xmm0
  844949:	mulss  0x50(%rsp),%xmm0
  84494f:	call   553678 <ceilf@plt>
  844954:	cvttss2si %xmm0,%eax
  844958:	add    0x58(%rsp),%r15d
  84495d:	cmpb   $0x0,0x8f(%rsp)
  844965:	lea    (%r15,%rax,1),%eax
  844969:	mov    %eax,0x50(%rsp)
  84496d:	je     844995 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xac5>
  84496f:	cvtsi2ss %eax,%xmm0
  844973:	movss  0x98(%rsp),%xmm1
  84497c:	mulss  0x789bac(%rip),%xmm1        # fce530 <vtable for iInventoryListener+0xf0>
  844984:	divss  %xmm1,%xmm0
  844988:	call   553678 <ceilf@plt>
  84498d:	cvttss2si %xmm0,%eax
  844991:	mov    %eax,0x50(%rsp)
  844995:	cvtsi2ssl 0x50(%rsp),%xmm1
  84499b:	mulss  0x75fe6d(%rip),%xmm1        # fa4810 <vtable for Ogre::FrameListener+0x50>
  8449a3:	movaps %xmm1,%xmm0
  8449a6:	movss  %xmm1,0x30(%rsp)
  8449ac:	call   553678 <ceilf@plt>
  8449b1:	cvttss2si %xmm0,%edx
  8449b5:	mov    0x50(%rsp),%esi
  8449b9:	mov    %edx,%edi
  8449bb:	mov    %edx,0x58(%rsp)
  8449bf:	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  8449c4:	cmpb   $0x0,0x87(%rsp)
  8449cc:	mov    %eax,%r15d
  8449cf:	movss  0x30(%rsp),%xmm1
  8449d5:	jne    844d20 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xe50>
  8449db:	cmpb   $0x0,0x8e(%rsp)
  8449e3:	jne    844b88 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xcb8>
  8449e9:	test   %r15d,%r15d
  8449ec:	jle    844a23 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb53>
  8449ee:	mov    0x88(%rsp),%ecx
  8449f5:	mov    0x54(%rsp),%edx
  8449f9:	mov    %r15d,%esi
  8449fc:	movss  0x74(%rsp),%xmm0
  844a02:	mov    %rbp,%rdi
  844a05:	add    %r15d,0x90(%rsp)
  844a0d:	call   837c00 <CCharacter::modifyDamage(int, EDAMAGE_TYPES, int, float)>
  844a12:	cmpb   $0x0,0x8e(%rsp)
  844a1a:	mov    %eax,%r15d
  844a1d:	jne    845283 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x13b3>
  844a23:	mov    0x80(%rsp),%eax
  844a2a:	mov    0x54(%rsp),%edx
  844a2e:	add    %r15d,0x7c(%rsp)
  844a33:	addl   $0x1,0x80(%rsp)
  844a3b:	mov    %edx,0xb0(%rsp,%rax,8)
  844a42:	mov    %r15d,0xb4(%rsp,%rax,8)
  844a4a:	add    $0x1,%r14d
  844a4e:	cmp    $0x7,%r14d
  844a52:	je     844d98 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xec8>
  844a58:	test   %r12,%r12
  844a5b:	jne    8446e8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x818>
  844a61:	xor    %r15d,%r15d
  844a64:	test   %r14d,%r14d
  844a67:	movb   $0x1,0x50(%rsp)
  844a6c:	je     8446fd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x82d>
  844a72:	mov    0x3f8(%rbx),%rax
  844a79:	movslq %r14d,%rdx
  844a7c:	mov    (%rax),%rax
  844a7f:	mov    0x24(%rax,%rdx,4),%r15d
  844a84:	test   %r15d,%r15d
  844a87:	setle  0x50(%rsp)
  844a8c:	jmp    8446fd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x82d>
  844a91:	nopl   0x0(%rax)
  844a98:	test   %r12,%r12
  844a9b:	jne    844855 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x985>
  844aa1:	jmp    8448c7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x9f7>
  844aa6:	cs nopw 0x0(%rax,%rax,1)
  844ab0:	test   %r12,%r12
  844ab3:	jne    844890 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x9c0>
  844ab9:	nopl   0x0(%rax)
  844ac0:	jmp    8448c7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x9f7>
  844ac5:	nopl   (%rax)
  844ac8:	mov    $0x7,%edx
  844acd:	mov    $0xf,%esi
  844ad2:	mov    %rbx,%rdi
  844ad5:	movss  %xmm1,0x30(%rsp)
  844adb:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844ae0:	divss  0x75fd54(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844ae8:	mov    %rbx,%rdi
  844aeb:	movss  0x30(%rsp),%xmm1
  844af1:	addss  %xmm1,%xmm0
  844af5:	movss  %xmm0,0x30(%rsp)
  844afb:	call   813930 <CCharacter::strength()>
  844b00:	cvtsi2ss %eax,%xmm2
  844b04:	movss  0x30(%rsp),%xmm0
  844b0a:	divss  0x75fd2a(%rip),%xmm2        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844b12:	addss  %xmm2,%xmm0
  844b16:	movss  %xmm0,0x50(%rsp)
  844b1c:	jmp    84481a <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x94a>
  844b21:	nopl   0x0(%rax)
  844b28:	mov    $0x7,%edx
  844b2d:	mov    $0xf,%esi
  844b32:	mov    %rbx,%rdi
  844b35:	movss  %xmm1,0x30(%rsp)
  844b3b:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844b40:	divss  0x75fcf4(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844b48:	mov    %rbx,%rdi
  844b4b:	movss  0x30(%rsp),%xmm1
  844b51:	addss  %xmm1,%xmm0
  844b55:	movss  %xmm0,0x30(%rsp)
  844b5b:	call   813930 <CCharacter::strength()>
  844b60:	cvtsi2ss %eax,%xmm2
  844b64:	movss  0x30(%rsp),%xmm0
  844b6a:	divss  0x75fcca(%rip),%xmm2        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844b72:	addss  %xmm2,%xmm0
  844b76:	movss  %xmm0,0x50(%rsp)
  844b7c:	jmp    8448c7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x9f7>
  844b81:	nopl   0x0(%rax)
  844b88:	movslq 0x54(%rsp),%rax
  844b8d:	lea    0x6a0(%rsp),%rdi
  844b95:	mov    $0xfcb6a8,%esi
  844b9a:	lea    0x147cb00(,%rax,8),%rdx
  844ba2:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  844ba7:	mov    0x68(%rsp),%rdx
  844bac:	lea    0x6a0(%rsp),%rsi
  844bb4:	mov    0x220(%rdx),%rax
  844bbb:	mov    0x78(%rax),%rax
  844bbf:	mov    0x1690(%rax),%rdi
  844bc6:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  844bcb:	lea    0x6a0(%rsp),%rdi
  844bd3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844bd8:	mov    0x50(%rsp),%esi
  844bdc:	lea    0x660(%rsp),%rdi
  844be4:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  844be9:	mov    0x58(%rsp),%esi
  844bed:	lea    0x690(%rsp),%rdi
  844bf5:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  844bfa:	lea    0x690(%rsp),%rdx
  844c02:	lea    0x680(%rsp),%rdi
  844c0a:	mov    $0xfcb718,%esi
  844c0f:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  844c14:	lea    0x680(%rsp),%rsi
  844c1c:	lea    0x670(%rsp),%rdi
  844c24:	mov    $0xff64d0,%edx
  844c29:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  844c2e:	lea    0x660(%rsp),%rdx
  844c36:	lea    0x670(%rsp),%rsi
  844c3e:	lea    0x650(%rsp),%rdi
  844c46:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  844c4b:	mov    0x68(%rsp),%rdx
  844c50:	lea    0x650(%rsp),%rsi
  844c58:	mov    0x220(%rdx),%rax
  844c5f:	mov    0x78(%rax),%rax
  844c63:	mov    0x1690(%rax),%rdi
  844c6a:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  844c6f:	lea    0x650(%rsp),%rdi
  844c77:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844c7c:	lea    0x670(%rsp),%rdi
  844c84:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844c89:	lea    0x680(%rsp),%rdi
  844c91:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844c96:	lea    0x690(%rsp),%rdi
  844c9e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844ca3:	lea    0x660(%rsp),%rdi
  844cab:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844cb0:	lea    0x640(%rsp),%rdi
  844cb8:	mov    %r15d,%esi
  844cbb:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  844cc0:	lea    0x640(%rsp),%rdx
  844cc8:	lea    0x630(%rsp),%rdi
  844cd0:	mov    $0xfcb780,%esi
  844cd5:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  844cda:	mov    0x68(%rsp),%rdx
  844cdf:	lea    0x630(%rsp),%rsi
  844ce7:	mov    0x220(%rdx),%rax
  844cee:	mov    0x78(%rax),%rax
  844cf2:	mov    0x1690(%rax),%rdi
  844cf9:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  844cfe:	lea    0x630(%rsp),%rdi
  844d06:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844d0b:	lea    0x640(%rsp),%rdi
  844d13:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844d18:	jmp    8449e9 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb19>
  844d1d:	nopl   (%rax)
  844d20:	mov    $0x7,%edx
  844d25:	mov    $0x59,%esi
  844d2a:	mov    %rbx,%rdi
  844d2d:	cvttss2si %xmm1,%r15d
  844d32:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844d37:	divss  0x75fafd(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844d3f:	mov    0x50(%rsp),%eax
  844d43:	cvtsi2ss %r15d,%xmm1
  844d48:	lea    (%r15,%rax,1),%eax
  844d4c:	mulss  %xmm0,%xmm1
  844d50:	cvttss2si %xmm1,%r15d
  844d55:	lea    (%rax,%r15,1),%r15d
  844d59:	jmp    8449db <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb0b>
  844d5e:	xchg   %ax,%ax
  844d60:	cmpb   $0x0,0x9f(%rsp)
  844d68:	je     8448d3 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa03>
  844d6e:	mov    %rbx,%rdi
  844d71:	call   8144c0 <CCharacter::magic()>
  844d76:	cvtsi2ss %eax,%xmm0
  844d7a:	divss  0x75faba(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  844d82:	addss  0x50(%rsp),%xmm0
  844d88:	movss  %xmm0,0x50(%rsp)
  844d8e:	jmp    8448d3 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xa03>
  844d93:	nopl   0x0(%rax,%rax,1)
  844d98:	mov    $0x7,%edx
  844d9d:	mov    $0x38,%esi
  844da2:	mov    %rbx,%rdi
  844da5:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844daa:	cvtsi2ssl 0x90(%rsp),%xmm1
  844db3:	cvtsi2ssl 0x88(%rsp),%xmm2
  844dbc:	divss  %xmm2,%xmm1
  844dc0:	ucomiss 0x7819a5(%rip),%xmm1        # fc676c <typeinfo name for iCollision+0x1c>
  844dc7:	jbe    845bee <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1d1e>
  844dcd:	xorps  %xmm1,%xmm1
  844dd0:	mov    $0x1,%r13d
  844dd6:	movss  %xmm1,0x50(%rsp)
  844ddc:	movss  0x50(%rsp),%xmm1
  844de2:	ucomiss %xmm0,%xmm1
  844de5:	ja     845bb6 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1ce6>
  844deb:	mov    $0x64,%esi
  844df0:	mov    $0x1,%edi
  844df5:	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  844dfa:	mov    $0x7,%edx
  844dff:	mov    %eax,%r14d
  844e02:	mov    $0x88,%esi
  844e07:	mov    %rbp,%rdi
  844e0a:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  844e0f:	cvtsi2ss %r14d,%xmm1
  844e14:	ucomiss %xmm1,%xmm0
  844e17:	jae    844e80 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfb0>
  844e19:	test   %r13b,%r13b
  844e1c:	je     844e80 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfb0>
  844e1e:	mov    $0x1,%esi
  844e23:	mov    %rbp,%rdi
  844e26:	call   811230 <CCharacter::interrupt(bool)>
  844e2b:	cmpb   $0x0,0x8e(%rsp)
  844e33:	je     844e80 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfb0>
  844e35:	lea    0x600(%rsp),%r13
  844e3d:	lea    0x77e(%rsp),%rdx
  844e45:	mov    $0xfcb878,%esi
  844e4a:	mov    %r13,%rdi
  844e4d:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  844e52:	mov    0x68(%rsp),%rdx
  844e57:	mov    %r13,%rsi
  844e5a:	mov    0x220(%rdx),%rax
  844e61:	mov    0x78(%rax),%rax
  844e65:	mov    0x1690(%rax),%rdi
  844e6c:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  844e71:	mov    %r13,%rdi
  844e74:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844e79:	nopl   0x0(%rax)
  844e80:	cmpb   $0x0,0x87(%rsp)
  844e88:	jne    8452ef <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x141f>
  844e8e:	mov    0x78(%rsp),%r13d
  844e93:	and    $0x8,%r13d
  844e97:	je     846343 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2473>
  844e9d:	movss  0x7638c3(%rip),%xmm1        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  844ea5:	movss  0x75f94f(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  844ead:	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  844eb2:	test   %r13d,%r13d
  844eb5:	movss  %xmm0,0x54(%rsp)
  844ebb:	je     844ed1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1001>
  844ebd:	movss  0x54(%rsp),%xmm2
  844ec3:	mulss  0x7895cd(%rip),%xmm2        # fce498 <vtable for iInventoryListener+0x58>
  844ecb:	movss  %xmm2,0x54(%rsp)
  844ed1:	cmpb   $0x0,0x8e(%rsp)
  844ed9:	jne    845ca8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1dd8>
  844edf:	mov    0x7c(%rsp),%eax
  844ee3:	cmp    %eax,0x94(%rsp)
  844eea:	jne    845c8c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1dbc>
  844ef0:	testl  $0x1000,0x78(%rsp)
  844ef8:	je     845e3e <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1f6e>
  844efe:	xor    %r15d,%r15d
  844f01:	mov    %rbp,%rdi
  844f04:	call   816330 <CCharacter::blocked()>
  844f09:	test   %al,%al
  844f0b:	mov    %eax,%r14d
  844f0e:	je     84512e <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x125e>
  844f14:	cmpb   $0x0,0xc3993d(%rip)        # 147e858 <guard variable for CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Blocked>
  844f1b:	je     846380 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x24b0>
  844f21:	mov    0xc39938(%rip),%rax        # 147e860 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Blocked>
  844f28:	cmpq   $0x0,-0x18(%rax)
  844f2d:	jne    844f61 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1091>
  844f2f:	lea    0x410(%rsp),%r13
  844f37:	call   e16d60 <CStringTranslate::getSinglton()>
  844f3c:	mov    %r13,%rdi
  844f3f:	mov    %rax,%rsi
  844f42:	mov    $0xfcb420,%edx
  844f47:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  844f4c:	mov    %r13,%rsi
  844f4f:	mov    $0x147e860,%edi
  844f54:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  844f59:	mov    %r13,%rdi
  844f5c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  844f61:	movss  0x75f893(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  844f69:	lea    0xf0(%rsp),%rdi
  844f71:	movaps %xmm3,%xmm0
  844f74:	lea    0x3f0(%rsp),%r13
  844f7c:	movss  0x789584(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  844f84:	movss  0x789580(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  844f8c:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  844f91:	movss  0x75f863(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  844f99:	lea    0x110(%rsp),%rdi
  844fa1:	movaps %xmm3,%xmm0
  844fa4:	movss  0x78955c(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  844fac:	movss  0x789558(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  844fb4:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  844fb9:	lea    0x400(%rsp),%rdi
  844fc1:	mov    $0x147e860,%esi
  844fc6:	mov    $0xfcd158,%edx
  844fcb:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  844fd0:	lea    0x400(%rsp),%rsi
  844fd8:	mov    %r13,%rdi
  844fdb:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  844fe0:	movss  0x789528(%rip),%xmm0        # fce510 <vtable for iInventoryListener+0xd0>
  844fe8:	mov    $0x1,%esi
  844fed:	movss  0xbdfb47(%rip),%xmm2        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  844ff5:	mov    %rbp,%rdi
  844ff8:	movss  0xbdfb38(%rip),%xmm1        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  845000:	mulss  %xmm0,%xmm2
  845004:	mulss  %xmm0,%xmm1
  845008:	mulss  0xbdfb24(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  845010:	movss  %xmm2,0x64(%rsp)
  845016:	movss  %xmm1,0x58(%rsp)
  84501c:	movss  %xmm0,0x74(%rsp)
  845022:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845027:	movq   %xmm0,0x28(%rsp)
  84502d:	mov    0x28(%rsp),%rax
  845032:	mov    0x68(%rsp),%rdx
  845037:	movss  %xmm1,0xa8(%rsp)
  845040:	lea    0x300(%rsp),%rsi
  845048:	lea    0xf0(%rsp),%r8
  845050:	movss  0x58(%rsp),%xmm1
  845056:	lea    0x110(%rsp),%rcx
  84505e:	mov    %rax,0x310(%rsp)
  845066:	mov    %rax,0xa0(%rsp)
  84506e:	mov    0xa8(%rsp),%eax
  845075:	movss  0x74(%rsp),%xmm0
  84507b:	addss  0x314(%rsp),%xmm1
  845084:	movss  0x64(%rsp),%xmm2
  84508a:	addss  0x310(%rsp),%xmm0
  845093:	mov    %eax,0x318(%rsp)
  84509a:	addss  0x318(%rsp),%xmm2
  8450a3:	movss  %xmm1,0x304(%rsp)
  8450ac:	movss  %xmm0,0x300(%rsp)
  8450b5:	movss  0x763683(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  8450bd:	movss  %xmm2,0x308(%rsp)
  8450c6:	mov    0x220(%rdx),%rax
  8450cd:	mov    %r13,%rdx
  8450d0:	movss  0x75f724(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8450d8:	mov    0x78(%rax),%rdi
  8450dc:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  8450e1:	mov    %r13,%rdi
  8450e4:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8450e9:	lea    0x400(%rsp),%rdi
  8450f1:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8450f6:	mov    0x298(%rbx),%rdi
  8450fd:	test   %rdi,%rdi
  845100:	je     845118 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1248>
  845102:	xorps  %xmm1,%xmm1
  845105:	mov    0x58(%rbx),%rdx
  845109:	xor    %ecx,%ecx
  84510b:	mov    $0x7,%esi
  845110:	movaps %xmm1,%xmm0
  845113:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  845118:	cmpb   $0x0,0x8e(%rsp)
  845120:	movl   $0x0,0x7c(%rsp)
  845128:	jne    8462f2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2422>
  84512e:	test   %r15b,%r15b
  845131:	je     845155 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1285>
  845133:	mov    0x298(%rbx),%rdi
  84513a:	test   %rdi,%rdi
  84513d:	je     845155 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1285>
  84513f:	xorps  %xmm1,%xmm1
  845142:	mov    0x58(%rbx),%rdx
  845146:	xor    %ecx,%ecx
  845148:	mov    $0x8,%esi
  84514d:	movaps %xmm1,%xmm0
  845150:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  845155:	mov    %rbp,%rdi
  845158:	cvtsi2ssl 0x7c(%rsp),%xmm0
  84515e:	movss  %xmm0,0x64(%rsp)
  845164:	call   80f7e0 <CCharacter::HP()>
  845169:	cvtsi2ss %eax,%xmm1
  84516d:	movss  0x64(%rsp),%xmm0
  845173:	ucomiss %xmm1,%xmm0
  845176:	ja     845ba5 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1cd5>
  84517c:	mov    %rbp,%rdi
  84517f:	movss  %xmm0,0x30(%rsp)
  845185:	call   80f7e0 <CCharacter::HP()>
  84518a:	movzbl 0x87(%rsp),%eax
  845192:	lea    0xb0(%rsp),%rdx
  84519a:	mov    %rbx,%rsi
  84519d:	mov    0x80(%rsp),%ecx
  8451a4:	movss  0x30(%rsp),%xmm0
  8451aa:	mov    %rbp,%rdi
  8451ad:	mov    %eax,%r8d
  8451b0:	mov    %eax,0x58(%rsp)
  8451b4:	call   810b30 <CCharacter::applyDamageEffects(CCharacter*, float, int (*) [2], unsigned int, bool)>
  8451b9:	mov    $0x7,%edx
  8451be:	mov    $0xc,%esi
  8451c3:	mov    %rbx,%rdi
  8451c6:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  8451cb:	test   %r12,%r12
  8451ce:	movaps %xmm0,%xmm2
  8451d1:	je     845350 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1480>
  8451d7:	mov    (%r12),%rax
  8451db:	mov    $0x7,%ecx
  8451e0:	movss  %xmm2,0x30(%rsp)
  8451e6:	xorps  %xmm0,%xmm0
  8451e9:	mov    $0xc,%edx
  8451ee:	mov    $0x1,%esi
  8451f3:	mov    %r12,%rdi
  8451f6:	call   *0x248(%rax)
  8451fc:	mov    0x3f0(%r12),%r13d
  845204:	movss  0x30(%rsp),%xmm2
  84520a:	addss  %xmm0,%xmm2
  84520e:	test   %r13d,%r13d
  845211:	je     845350 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1480>
  845217:	xor    %r13d,%r13d
  84521a:	jmp    845268 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1398>
  84521c:	nopl   0x0(%rax)
  845220:	mov    0x3e8(%r12),%rax
  845228:	mov    (%rax),%rdi
  84522b:	mov    $0x7,%ecx
  845230:	mov    $0xc,%edx
  845235:	xorps  %xmm0,%xmm0
  845238:	mov    $0x1,%esi
  84523d:	add    $0x1,%r13d
  845241:	mov    (%rdi),%rax
  845244:	movss  %xmm2,0x30(%rsp)
  84524a:	call   *0x248(%rax)
  845250:	cmp    0x3f0(%r12),%r13d
  845258:	movss  0x30(%rsp),%xmm2
  84525e:	addss  %xmm0,%xmm2
  845262:	jae    845350 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1480>
  845268:	cmp    %r13d,0x3f4(%r12)
  845270:	jbe    845220 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1350>
  845272:	mov    %r13d,%eax
  845275:	shl    $0x3,%rax
  845279:	add    0x3e8(%r12),%rax
  845281:	jmp    845228 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1358>
  845283:	lea    0x620(%rsp),%rdi
  84528b:	mov    %eax,%esi
  84528d:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  845292:	lea    0x620(%rsp),%rdx
  84529a:	lea    0x610(%rsp),%rdi
  8452a2:	mov    $0xfcb7e8,%esi
  8452a7:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8452ac:	mov    0x68(%rsp),%rdx
  8452b1:	lea    0x610(%rsp),%rsi
  8452b9:	mov    0x220(%rdx),%rax
  8452c0:	mov    0x78(%rax),%rax
  8452c4:	mov    0x1690(%rax),%rdi
  8452cb:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  8452d0:	lea    0x610(%rsp),%rdi
  8452d8:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8452dd:	lea    0x620(%rsp),%rdi
  8452e5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8452ea:	jmp    844a23 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xb53>
  8452ef:	movss  0x763471(%rip),%xmm1        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  8452f7:	movss  0x75f4fd(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8452ff:	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  845304:	movss  %xmm0,0x54(%rsp)
  84530a:	jmp    844ebd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfed>
  84530f:	cvtsi2ss %r15d,%xmm0
  845314:	movss  0x98(%rsp),%xmm1
  84531d:	mulss  0x78920b(%rip),%xmm1        # fce530 <vtable for iInventoryListener+0xf0>
  845325:	divss  %xmm1,%xmm0
  845329:	call   553678 <ceilf@plt>
  84532e:	cvttss2si %xmm0,%r15d
  845333:	jmp    844180 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2b0>
  845338:	cvtsi2ss %r15d,%xmm0
  84533d:	mulss  %xmm1,%xmm0
  845341:	cvttss2si %xmm0,%r15d
  845346:	jmp    844172 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2a2>
  84534b:	nopl   0x0(%rax,%rax,1)
  845350:	ucomiss 0x50(%rsp),%xmm2
  845355:	jbe    8454f2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1622>
  84535b:	mov    $0x138,%edi
  845360:	movss  %xmm2,0x30(%rsp)
  845366:	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  84536b:	movss  0x30(%rsp),%xmm2
  845371:	mov    %rax,%r12
  845374:	movss  0x75f494(%rip),%xmm0        # fa4810 <vtable for Ogre::FrameListener+0x50>
  84537c:	xor    %r8d,%r8d
  84537f:	mulss  %xmm2,%xmm0
  845383:	movss  0x75f499(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  84538b:	movss  0x75f479(%rip),%xmm3        # fa480c <vtable for Ogre::FrameListener+0x4c>
  845393:	mov    $0x1,%ecx
  845398:	mulss  %xmm2,%xmm3
  84539c:	xor    %edx,%edx
  84539e:	mov    $0x2b,%esi
  8453a3:	xorps  %xmm2,%xmm2
  8453a6:	mov    %r12,%rdi
  8453a9:	addss  %xmm1,%xmm0
  8453ad:	addss  %xmm3,%xmm1
  8453b1:	cvttss2si %xmm0,%eax
  8453b5:	cvtsi2ss %eax,%xmm0
  8453b9:	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  8453be:	lea    0x3d0(%rsp),%r13
  8453c6:	lea    0x77c(%rsp),%rdx
  8453ce:	mov    $0xfcb910,%esi
  8453d3:	mov    %r13,%rdi
  8453d6:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8453db:	mov    %r13,%rsi
  8453de:	mov    %r12,%rdi
  8453e1:	call   85b970 <CEffect::setName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8453e6:	mov    %r13,%rdi
  8453e9:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8453ee:	mov    $0x1,%esi
  8453f3:	mov    %rbx,%rdi
  8453f6:	call   9e7080 <CPositionableObject::getPosition(bool)>
  8453fb:	movq   %xmm0,0x28(%rsp)
  845401:	mov    0x28(%rsp),%rax
  845406:	mov    $0x1,%esi
  84540b:	movss  %xmm1,0xa8(%rsp)
  845414:	mov    %rbp,%rdi
  845417:	mov    %rax,0xa0(%rsp)
  84541f:	mov    %rax,0x2d0(%rsp)
  845427:	mov    0xa8(%rsp),%eax
  84542e:	mov    %eax,0x2d8(%rsp)
  845435:	call   9e7080 <CPositionableObject::getPosition(bool)>
  84543a:	movq   %xmm0,0x28(%rsp)
  845440:	mov    0x28(%rsp),%rax
  845445:	lea    0x2f0(%rsp),%rdi
  84544d:	movss  %xmm1,0xa8(%rsp)
  845456:	movl   $0x0,0x2f4(%rsp)
  845461:	mov    %rax,0x2e0(%rsp)
  845469:	mov    %rax,0xa0(%rsp)
  845471:	mov    0xa8(%rsp),%eax
  845478:	movss  0x2e0(%rsp),%xmm0
  845481:	subss  0x2d0(%rsp),%xmm0
  84548a:	mov    %eax,0x2e8(%rsp)
  845491:	movss  0x2e8(%rsp),%xmm1
  84549a:	subss  0x2d8(%rsp),%xmm1
  8454a3:	movss  %xmm0,0x2f0(%rsp)
  8454ac:	movss  %xmm1,0x2f8(%rsp)
  8454b5:	call   5aa280 <Ogre::Vector3::normalise()>
  8454ba:	mov    0x2f0(%rsp),%eax
  8454c1:	mov    %r12,%rsi
  8454c4:	mov    %rbp,%rdi
  8454c7:	mov    %eax,0x98(%r12)
  8454cf:	mov    0x2f4(%rsp),%eax
  8454d6:	mov    %eax,0x9c(%r12)
  8454de:	mov    0x2f8(%rsp),%eax
  8454e5:	mov    %eax,0xa0(%r12)
  8454ed:	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  8454f2:	mov    $0x7,%edx
  8454f7:	mov    $0x36,%esi
  8454fc:	mov    %rbx,%rdi
  8454ff:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845504:	ucomiss 0x50(%rsp),%xmm0
  845509:	ja     846273 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x23a3>
  84550f:	mov    0x1b8(%rbx),%rdi
  845516:	test   %rdi,%rdi
  845519:	je     845583 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x16b3>
  84551b:	xor    %r12d,%r12d
  84551e:	jmp    845527 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1657>
  845520:	mov    0x1b8(%rbx),%rdi
  845527:	mov    %r12d,%ecx
  84552a:	mov    $0x2,%edx
  84552f:	mov    %rbp,%rsi
  845532:	call   7ec7a0 <CEffectManager::transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE)>
  845537:	mov    0x490(%rbx),%rdi
  84553e:	test   %rdi,%rdi
  845541:	je     845576 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x16a6>
  845543:	mov    0x18(%rdi),%rax
  845547:	test   %rax,%rax
  84554a:	je     845566 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1696>
  84554c:	mov    %rax,%rdi
  84554f:	mov    %r12d,%ecx
  845552:	mov    $0x2,%edx
  845557:	mov    %rbp,%rsi
  84555a:	call   7ec7a0 <CEffectManager::transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE)>
  84555f:	mov    0x490(%rbx),%rdi
  845566:	mov    %r12d,%ecx
  845569:	mov    $0x2,%edx
  84556e:	mov    %rbp,%rsi
  845571:	call   91cd60 <CInventory::transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE)>
  845576:	add    $0x1,%r12d
  84557a:	cmp    $0x91,%r12d
  845581:	jne    845520 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1650>
  845583:	mov    0x330(%rbp),%eax
  845589:	xor    %r12d,%r12d
  84558c:	cmp    $0x5,%eax
  84558f:	je     845598 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x16c8>
  845591:	cmp    $0x6,%eax
  845594:	setne  %r12b
  845598:	mov    $0x1,%esi
  84559d:	mov    %rbx,%rdi
  8455a0:	lea    0x2c0(%rsp),%r13
  8455a8:	call   9e7080 <CPositionableObject::getPosition(bool)>
  8455ad:	movq   %xmm0,0x28(%rsp)
  8455b3:	mov    0x28(%rsp),%rax
  8455b8:	mov    $0x1,%esi
  8455bd:	movss  %xmm1,0xa8(%rsp)
  8455c6:	mov    %rbp,%rdi
  8455c9:	mov    %rax,0xa0(%rsp)
  8455d1:	mov    %rax,0x2a0(%rsp)
  8455d9:	mov    0xa8(%rsp),%eax
  8455e0:	mov    %eax,0x2a8(%rsp)
  8455e7:	call   9e7080 <CPositionableObject::getPosition(bool)>
  8455ec:	movq   %xmm0,0x28(%rsp)
  8455f2:	mov    0x28(%rsp),%rax
  8455f7:	mov    %r13,%rdi
  8455fa:	movss  %xmm1,0xa8(%rsp)
  845603:	movl   $0x0,0x2c4(%rsp)
  84560e:	mov    %rax,0x2b0(%rsp)
  845616:	mov    %rax,0xa0(%rsp)
  84561e:	mov    0xa8(%rsp),%eax
  845625:	movss  0x2b0(%rsp),%xmm0
  84562e:	subss  0x2a0(%rsp),%xmm0
  845637:	mov    %eax,0x2b8(%rsp)
  84563e:	movss  0x2b8(%rsp),%xmm1
  845647:	subss  0x2a8(%rsp),%xmm1
  845650:	movss  %xmm0,0x2c0(%rsp)
  845659:	movss  %xmm1,0x2c8(%rsp)
  845662:	call   5aa280 <Ogre::Vector3::normalise()>
  845667:	movss  0x763071(%rip),%xmm1        # fa86e0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x40>
  84566f:	movss  0x781175(%rip),%xmm0        # fc67ec <typeinfo for CPOV+0x1c>
  845677:	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  84567c:	unpcklps %xmm0,%xmm0
  84567f:	mov    %r13,%rdi
  845682:	cvtps2pd %xmm0,%xmm0
  845685:	mulsd  0x77eefb(%rip),%xmm0        # fc4588 <typeinfo for CEditor+0x38>
  84568d:	unpcklpd %xmm0,%xmm0
  845691:	cvtpd2ps %xmm0,%xmm0
  845695:	call   c7a400 <MATH::rotateY(Ogre::Vector3*, float)>
  84569a:	mov    $0x1,%esi
  84569f:	mov    %rbx,%rdi
  8456a2:	call   9e7080 <CPositionableObject::getPosition(bool)>
  8456a7:	movq   %xmm0,0x28(%rsp)
  8456ad:	mov    0x28(%rsp),%rax
  8456b2:	mov    0x68(%rsp),%rsi
  8456b7:	movss  %xmm1,0xa8(%rsp)
  8456c0:	lea    0x290(%rsp),%rdx
  8456c8:	mov    $0x1,%r9d
  8456ce:	and    %r15d,%r9d
  8456d1:	mov    %rbx,%r8
  8456d4:	mov    %r13,%rcx
  8456d7:	mov    %rax,0xa0(%rsp)
  8456df:	mov    %rbp,%rdi
  8456e2:	mov    %rax,0x290(%rsp)
  8456ea:	mov    0xa8(%rsp),%eax
  8456f1:	movss  0x54(%rsp),%xmm1
  8456f7:	movl   $0x1,0x8(%rsp)
  8456ff:	movss  0x64(%rsp),%xmm0
  845705:	movl   $0x1,(%rsp)
  84570c:	mov    %eax,0x298(%rsp)
  845713:	mov    0x78(%rsp),%eax
  845717:	mov    %eax,0x18(%rsp)
  84571b:	mov    0x58(%rsp),%eax
  84571f:	mov    %eax,0x10(%rsp)
  845723:	call   83cfe0 <CCharacter::applyDamage(CLevel&, Ogre::Vector3 const&, float, Ogre::Vector3 const&, float, CCharacter*, bool, bool, bool, bool, unsigned int)>
  845728:	testl  $0x800,0x78(%rsp)
  845730:	je     84580b <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x193b>
  845736:	cmpb   $0x0,0x87(%rsp)
  84573e:	jne    845d08 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1e38>
  845744:	test   %r14b,%r14b
  845747:	je     8458d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a00>
  84574d:	movss  0x194(%rbp),%xmm2
  845755:	mov    $0x1,%esi
  84575a:	mov    %rbp,%rdi
  84575d:	movss  %xmm2,0x50(%rsp)
  845763:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845768:	movq   %xmm0,0x28(%rsp)
  84576e:	mov    0x28(%rsp),%rax
  845773:	mov    $0x1,%esi
  845778:	movss  %xmm1,0xa8(%rsp)
  845781:	mov    %rbx,%rdi
  845784:	mov    %rax,0xa0(%rsp)
  84578c:	mov    %rax,0x270(%rsp)
  845794:	mov    0xa8(%rsp),%eax
  84579b:	mov    %eax,0x278(%rsp)
  8457a2:	call   9e7080 <CPositionableObject::getPosition(bool)>
  8457a7:	movq   %xmm0,0x28(%rsp)
  8457ad:	mov    0x28(%rsp),%rax
  8457b2:	mov    0x58(%rsp),%ecx
  8457b6:	movss  %xmm1,0xa8(%rsp)
  8457bf:	lea    0x270(%rsp),%rdx
  8457c7:	lea    0x280(%rsp),%rsi
  8457cf:	mov    $0x1,%r8d
  8457d5:	movss  0x50(%rsp),%xmm0
  8457db:	mov    %rax,0xa0(%rsp)
  8457e3:	mov    %rbx,%rdi
  8457e6:	mov    %rax,0x280(%rsp)
  8457ee:	mov    0xa8(%rsp),%eax
  8457f5:	mov    %eax,0x288(%rsp)
  8457fc:	call   827720 <CCharacter::playStrikeParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float, bool, bool)>
  845801:	mov    $0x1,%eax
  845806:	jmp    8440d2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x202>
  84580b:	movss  0x194(%rbp),%xmm0
  845813:	mov    $0x1,%esi
  845818:	mov    %rbp,%rdi
  84581b:	movss  %xmm0,0x50(%rsp)
  845821:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845826:	movq   %xmm0,0x28(%rsp)
  84582c:	mov    0x28(%rsp),%rax
  845831:	mov    $0x1,%esi
  845836:	movss  %xmm1,0xa8(%rsp)
  84583f:	mov    %rbx,%rdi
  845842:	mov    %rax,0xa0(%rsp)
  84584a:	mov    %rax,0x270(%rsp)
  845852:	mov    0xa8(%rsp),%eax
  845859:	mov    %eax,0x278(%rsp)
  845860:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845865:	movq   %xmm0,0x28(%rsp)
  84586b:	mov    0x28(%rsp),%rax
  845870:	mov    0x58(%rsp),%ecx
  845874:	movss  %xmm1,0xa8(%rsp)
  84587d:	lea    0x270(%rsp),%rdx
  845885:	lea    0x280(%rsp),%rsi
  84588d:	movzbl %r14b,%r8d
  845891:	movss  0x50(%rsp),%xmm0
  845897:	mov    %rax,0xa0(%rsp)
  84589f:	mov    %rbx,%rdi
  8458a2:	mov    %rax,0x280(%rsp)
  8458aa:	mov    0xa8(%rsp),%eax
  8458b1:	mov    %eax,0x288(%rsp)
  8458b8:	call   827720 <CCharacter::playStrikeParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float, bool, bool)>
  8458bd:	cmpb   $0x0,0x87(%rsp)
  8458c5:	jne    845dba <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1eea>
  8458cb:	nopl   0x0(%rax,%rax,1)
  8458d0:	mov    $0x1,%eax
  8458d5:	jmp    8440d2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x202>
  8458da:	mov    0x2a0(%r12),%r14
  8458e2:	jmp    843f7c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xac>
  8458e7:	lea    0x6c0(%rsp),%rdi
  8458ef:	mov    %eax,%esi
  8458f1:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8458f6:	lea    0x6c0(%rsp),%rdx
  8458fe:	lea    0x6b0(%rsp),%rdi
  845906:	mov    $0xfcb628,%esi
  84590b:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845910:	mov    0x68(%rsp),%rdx
  845915:	lea    0x6b0(%rsp),%rsi
  84591d:	mov    0x220(%rdx),%rax
  845924:	mov    0x78(%rax),%rax
  845928:	mov    0x1690(%rax),%rdi
  84592f:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  845934:	lea    0x6b0(%rsp),%rdi
  84593c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845941:	lea    0x6c0(%rsp),%rdi
  845949:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84594e:	jmp    84423d <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x36d>
  845953:	movss  0x50(%rsp),%xmm0
  845959:	mov    $0x7,%edx
  84595e:	cvttss2si %xmm0,%eax
  845962:	mov    $0x59,%esi
  845967:	mov    %rbx,%rdi
  84596a:	mov    %eax,0x48(%rsp)
  84596e:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845973:	divss  0x75eec1(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  84597b:	mov    0x48(%rsp),%eax
  84597f:	cmpb   $0x0,0x8e(%rsp)
  845987:	cvtsi2ss %eax,%xmm1
  84598b:	lea    (%rax,%r15,1),%edx
  84598f:	mulss  %xmm0,%xmm1
  845993:	cvttss2si %xmm1,%eax
  845997:	lea    (%rdx,%rax,1),%eax
  84599a:	mov    %eax,0x94(%rsp)
  8459a1:	je     844205 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x335>
  8459a7:	lea    0x6e0(%rsp),%rdi
  8459af:	mov    %eax,%esi
  8459b1:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8459b6:	lea    0x6e0(%rsp),%rdx
  8459be:	lea    0x6d0(%rsp),%rdi
  8459c6:	mov    $0xfcb5b0,%esi
  8459cb:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8459d0:	mov    0x68(%rsp),%rdx
  8459d5:	lea    0x6d0(%rsp),%rsi
  8459dd:	mov    0x220(%rdx),%rax
  8459e4:	mov    0x78(%rax),%rax
  8459e8:	mov    0x1690(%rax),%rdi
  8459ef:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  8459f4:	lea    0x6d0(%rsp),%rdi
  8459fc:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845a01:	lea    0x6e0(%rsp),%rdi
  845a09:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845a0e:	jmp    844205 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x335>
  845a13:	lea    0x4c0(%rbx),%rdx
  845a1a:	lea    0x760(%rsp),%rdi
  845a22:	mov    $0xfcb468,%esi
  845a27:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845a2c:	mov    0x68(%rsp),%rdx
  845a31:	lea    0x760(%rsp),%rsi
  845a39:	mov    0x220(%rdx),%rax
  845a40:	mov    0x78(%rax),%rax
  845a44:	mov    0x1690(%rax),%rdi
  845a4b:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  845a50:	lea    0x760(%rsp),%rdi
  845a58:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845a5d:	lea    0x720(%rsp),%rdi
  845a65:	mov    %r15d,%esi
  845a68:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  845a6d:	mov    0x54(%rsp),%esi
  845a71:	lea    0x750(%rsp),%rdi
  845a79:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  845a7e:	lea    0x750(%rsp),%rdx
  845a86:	lea    0x740(%rsp),%rdi
  845a8e:	mov    $0xfcb4e0,%esi
  845a93:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845a98:	lea    0x740(%rsp),%rsi
  845aa0:	lea    0x730(%rsp),%rdi
  845aa8:	mov    $0xff64d0,%edx
  845aad:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  845ab2:	lea    0x720(%rsp),%rdx
  845aba:	lea    0x730(%rsp),%rsi
  845ac2:	lea    0x710(%rsp),%rdi
  845aca:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845acf:	mov    0x68(%rsp),%rdx
  845ad4:	lea    0x710(%rsp),%rsi
  845adc:	mov    0x220(%rdx),%rax
  845ae3:	mov    0x78(%rax),%rax
  845ae7:	mov    0x1690(%rax),%rdi
  845aee:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  845af3:	lea    0x710(%rsp),%rdi
  845afb:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b00:	lea    0x730(%rsp),%rdi
  845b08:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b0d:	lea    0x740(%rsp),%rdi
  845b15:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b1a:	lea    0x750(%rsp),%rdi
  845b22:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b27:	lea    0x720(%rsp),%rdi
  845b2f:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b34:	mov    0x94(%rsp),%esi
  845b3b:	lea    0x700(%rsp),%rdi
  845b43:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  845b48:	lea    0x700(%rsp),%rdx
  845b50:	lea    0x6f0(%rsp),%rdi
  845b58:	mov    $0xfcb550,%esi
  845b5d:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845b62:	mov    0x68(%rsp),%rdx
  845b67:	lea    0x6f0(%rsp),%rsi
  845b6f:	mov    0x220(%rdx),%rax
  845b76:	mov    0x78(%rax),%rax
  845b7a:	mov    0x1690(%rax),%rdi
  845b81:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  845b86:	lea    0x6f0(%rsp),%rdi
  845b8e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845b93:	lea    0x700(%rsp),%rdi
  845b9b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845ba0:	jmp    8441f7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x327>
  845ba5:	mov    %rbp,%rdi
  845ba8:	call   80f7e0 <CCharacter::HP()>
  845bad:	cvtsi2ss %eax,%xmm0
  845bb1:	jmp    84517c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x12ac>
  845bb6:	xor    %edi,%edi
  845bb8:	mov    $0x64,%esi
  845bbd:	movss  %xmm0,0x30(%rsp)
  845bc3:	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  845bc8:	cvtsi2ss %eax,%xmm1
  845bcc:	movss  0x762bac(%rip),%xmm2        # fa8780 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xe0>
  845bd4:	movss  0x30(%rsp),%xmm0
  845bda:	mov    $0x0,%eax
  845bdf:	xorps  %xmm2,%xmm0
  845be2:	ucomiss %xmm1,%xmm0
  845be5:	cmova  %eax,%r13d
  845be9:	jmp    844deb <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf1b>
  845bee:	mov    %rbp,%rdi
  845bf1:	movss  %xmm0,0x30(%rsp)
  845bf7:	call   813e60 <CCharacter::maxHP()>
  845bfc:	cvtsi2ssl 0x7c(%rsp),%xmm2
  845c02:	cvtsi2ss %eax,%xmm1
  845c06:	movss  0x30(%rsp),%xmm0
  845c0c:	mulss  0x75ebfc(%rip),%xmm1        # fa4810 <vtable for Ogre::FrameListener+0x50>
  845c14:	ucomiss %xmm1,%xmm2
  845c17:	ja     844dcd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xefd>
  845c1d:	mov    $0x64,%esi
  845c22:	mov    $0x1,%edi
  845c27:	call   c92bf0 <UTILITIES::randomIntegerBetweenVolatile(int, int)>
  845c2c:	cvtsi2ss %eax,%xmm1
  845c30:	movss  0x30(%rsp),%xmm0
  845c36:	ucomiss %xmm1,%xmm0
  845c39:	ja     844dcd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xefd>
  845c3f:	cmpb   $0x0,0x87(%rsp)
  845c47:	jne    846feb <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x311b>
  845c4d:	cmpq   $0x0,0x398(%rbp)
  845c55:	je     846406 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2536>
  845c5b:	cmpb   $0x0,0x267(%rbp)
  845c62:	je     845e12 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1f42>
  845c68:	xorps  %xmm1,%xmm1
  845c6b:	movss  %xmm1,0x50(%rsp)
  845c71:	cmpb   $0x0,0x3a8(%rbp)
  845c78:	mov    $0x1,%r13d
  845c7e:	jne    844ddc <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf0c>
  845c84:	xor    %r13d,%r13d
  845c87:	jmp    844ddc <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf0c>
  845c8c:	cmp    $0x1,%eax
  845c8f:	jne    844ef0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1020>
  845c95:	mov    $0x1,%r15d
  845c9b:	movb   $0x0,0x87(%rsp)
  845ca3:	jmp    844f01 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1031>
  845ca8:	lea    0x5f0(%rsp),%r14
  845cb0:	mov    0x7c(%rsp),%esi
  845cb4:	lea    0x5e0(%rsp),%r13
  845cbc:	mov    %r14,%rdi
  845cbf:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  845cc4:	mov    %r14,%rdx
  845cc7:	mov    $0xfcb8c8,%esi
  845ccc:	mov    %r13,%rdi
  845ccf:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  845cd4:	mov    0x68(%rsp),%rdx
  845cd9:	mov    %r13,%rsi
  845cdc:	mov    0x220(%rdx),%rax
  845ce3:	mov    0x78(%rax),%rax
  845ce7:	mov    0x1690(%rax),%rdi
  845cee:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  845cf3:	mov    %r13,%rdi
  845cf6:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845cfb:	mov    %r14,%rdi
  845cfe:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  845d03:	jmp    844edf <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x100f>
  845d08:	movss  0x194(%rbp),%xmm0
  845d10:	mov    $0x1,%esi
  845d15:	mov    %rbp,%rdi
  845d18:	movss  %xmm0,0x50(%rsp)
  845d1e:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845d23:	movq   %xmm0,0x28(%rsp)
  845d29:	mov    0x28(%rsp),%rax
  845d2e:	mov    $0x1,%esi
  845d33:	movss  %xmm1,0xa8(%rsp)
  845d3c:	mov    %rbx,%rdi
  845d3f:	mov    %rax,0xa0(%rsp)
  845d47:	mov    %rax,0x270(%rsp)
  845d4f:	mov    0xa8(%rsp),%eax
  845d56:	mov    %eax,0x278(%rsp)
  845d5d:	call   9e7080 <CPositionableObject::getPosition(bool)>
  845d62:	movq   %xmm0,0x28(%rsp)
  845d68:	mov    0x28(%rsp),%rax
  845d6d:	mov    0x58(%rsp),%ecx
  845d71:	movss  %xmm1,0xa8(%rsp)
  845d7a:	lea    0x270(%rsp),%rdx
  845d82:	lea    0x280(%rsp),%rsi
  845d8a:	movzbl %r14b,%r8d
  845d8e:	movss  0x50(%rsp),%xmm0
  845d94:	mov    %rax,0xa0(%rsp)
  845d9c:	mov    %rbx,%rdi
  845d9f:	mov    %rax,0x280(%rsp)
  845da7:	mov    0xa8(%rsp),%eax
  845dae:	mov    %eax,0x288(%rsp)
  845db5:	call   827720 <CCharacter::playStrikeParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float, bool, bool)>
  845dba:	test   %r12b,%r12b
  845dbd:	je     8458d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a00>
  845dc3:	mov    0x330(%rbp),%eax
  845dc9:	cmp    $0x5,%eax
  845dcc:	je     845dd7 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1f07>
  845dce:	cmp    $0x6,%eax
  845dd1:	jne    8458d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a00>
  845dd7:	mov    $0x1c,%esi
  845ddc:	mov    %rbx,%rdi
  845ddf:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  845de4:	test   %al,%al
  845de6:	je     8458d0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1a00>
  845dec:	call   c77c20 <CGameSpeed::getSingleton()>
  845df1:	movss  0x75ea03(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  845df9:	xor    %edi,%edi
  845dfb:	movss  0x75ea0d(%rip),%xmm0        # fa4810 <vtable for Ogre::FrameListener+0x50>
  845e03:	call   c77ea0 <CGameSpeed::addSpeedModifier(EGAMESPEED_TYPE, float, float)>
  845e08:	mov    $0x1,%eax
  845e0d:	jmp    8440d2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x202>
  845e12:	xorps  %xmm2,%xmm2
  845e15:	movss  %xmm2,0x50(%rsp)
  845e1b:	movss  0x380(%rbp),%xmm1
  845e23:	ucomiss %xmm2,%xmm1
  845e26:	jbe    845c84 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1db4>
  845e2c:	cmpb   $0x0,0x37d(%rbp)
  845e33:	je     845c71 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1da1>
  845e39:	jmp    845c84 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1db4>
  845e3e:	mov    $0x7,%edx
  845e43:	mov    $0x1e,%esi
  845e48:	mov    %rbx,%rdi
  845e4b:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845e50:	ucomiss 0x75e9e5(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845e57:	movss  %xmm0,0x64(%rsp)
  845e5d:	jbe    8463d4 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2504>
  845e63:	movss  0x75e9d1(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845e6b:	movss  %xmm0,0x64(%rsp)
  845e71:	mov    $0x7,%edx
  845e76:	mov    $0x31,%esi
  845e7b:	mov    %rbx,%rdi
  845e7e:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845e83:	cmpb   $0x0,0xc389b6(%rip)        # 147e840 <guard variable for CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  845e8a:	movss  %xmm0,0x74(%rsp)
  845e90:	je     84666b <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x279b>
  845e96:	mov    0xc389db(%rip),%rax        # 147e878 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  845e9d:	cmpq   $0x0,-0x18(%rax)
  845ea2:	je     846634 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2764>
  845ea8:	movss  0x64(%rsp),%xmm4
  845eae:	cvtsi2ssl 0x7c(%rsp),%xmm1
  845eb4:	mulss  %xmm1,%xmm4
  845eb8:	movss  %xmm1,0x58(%rsp)
  845ebe:	divss  0x75e976(%rip),%xmm4        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845ec6:	addss  0x74(%rsp),%xmm4
  845ecc:	ucomiss 0x50(%rsp),%xmm4
  845ed1:	ja     846414 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2544>
  845ed7:	movss  0x50(%rsp),%xmm0
  845edd:	ucomiss %xmm4,%xmm0
  845ee0:	ja     84694a <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2a7a>
  845ee6:	cmpq   $0x0,0x640(%rbx)
  845eee:	je     845f8c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x20bc>
  845ef4:	mov    $0x7,%edx
  845ef9:	mov    $0x7e,%esi
  845efe:	mov    %rbx,%rdi
  845f01:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845f06:	ucomiss 0x75e92f(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845f0d:	movss  %xmm0,0x64(%rsp)
  845f13:	jbe    8463ed <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x251d>
  845f19:	movl   $0x42c80000,0x64(%rsp)
  845f21:	mov    $0x7,%edx
  845f26:	mov    $0x7d,%esi
  845f2b:	mov    %rbx,%rdi
  845f2e:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845f33:	cmpb   $0x0,0xc3890e(%rip)        # 147e848 <guard variable for CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  845f3a:	movss  %xmm0,0x74(%rsp)
  845f40:	je     8466ab <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x27db>
  845f46:	mov    0xc38923(%rip),%rax        # 147e870 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  845f4d:	cmpq   $0x0,-0x18(%rax)
  845f52:	je     846913 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2a43>
  845f58:	movss  0x64(%rsp),%xmm4
  845f5e:	mulss  0x58(%rsp),%xmm4
  845f64:	divss  0x75e8d0(%rip),%xmm4        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845f6c:	addss  0x74(%rsp),%xmm4
  845f72:	ucomiss 0x50(%rsp),%xmm4
  845f77:	ja     8466eb <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x281b>
  845f7d:	movss  0x50(%rsp),%xmm0
  845f83:	ucomiss %xmm4,%xmm0
  845f86:	ja     846b6a <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2c9a>
  845f8c:	mov    $0x7,%edx
  845f91:	mov    $0x1f,%esi
  845f96:	mov    %rbx,%rdi
  845f99:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845f9e:	ucomiss 0x75e897(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845fa5:	jbe    8463c0 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x24f0>
  845fab:	movss  0x75e889(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845fb3:	movss  0x58(%rsp),%xmm1
  845fb9:	mov    $0x7,%edx
  845fbe:	mulss  %xmm0,%xmm1
  845fc2:	mov    $0x32,%esi
  845fc7:	mov    %rbx,%rdi
  845fca:	divss  0x75e86a(%rip),%xmm1        # fa483c <vtable for Ogre::FrameListener+0x7c>
  845fd2:	movss  %xmm1,0x30(%rsp)
  845fd8:	call   8137e0 <CCharacter::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)>
  845fdd:	movss  0x30(%rsp),%xmm1
  845fe3:	addss  %xmm0,%xmm1
  845fe7:	ucomiss 0x50(%rsp),%xmm1
  845fec:	movss  %xmm1,0x64(%rsp)
  845ff2:	jp     845ffa <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x212a>
  845ff4:	je     844efe <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x102e>
  845ffa:	cmpb   $0x0,0xc3884f(%rip)        # 147e850 <guard variable for CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Mana>
  846001:	je     846d92 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2ec2>
  846007:	mov    0xc3885a(%rip),%rax        # 147e868 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Mana>
  84600e:	cmpq   $0x0,-0x18(%rax)
  846013:	jne    846047 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2177>
  846015:	lea    0x470(%rsp),%r13
  84601d:	call   e16d60 <CStringTranslate::getSinglton()>
  846022:	mov    %r13,%rdi
  846025:	mov    %rax,%rsi
  846028:	mov    $0xfcd234,%edx
  84602d:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  846032:	mov    %r13,%rsi
  846035:	mov    $0x147e868,%edi
  84603a:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  84603f:	mov    %r13,%rdi
  846042:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846047:	movss  0x64(%rsp),%xmm0
  84604d:	mov    %rbx,%rdi
  846050:	call   813af0 <CCharacter::modifyMana(float)>
  846055:	movss  0x75e79f(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84605d:	lea    0x130(%rsp),%rdi
  846065:	movss  0x7884c7(%rip),%xmm1        # fce534 <vtable for iInventoryListener+0xf4>
  84606d:	movaps %xmm3,%xmm2
  846070:	movaps %xmm1,%xmm0
  846073:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846078:	movss  0x75e77c(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846080:	lea    0x150(%rsp),%rdi
  846088:	movss  0x7884a4(%rip),%xmm1        # fce534 <vtable for iInventoryListener+0xf4>
  846090:	movaps %xmm1,%xmm0
  846093:	movaps %xmm3,%xmm2
  846096:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  84609b:	movss  0x64(%rsp),%xmm0
  8460a1:	call   553678 <ceilf@plt>
  8460a6:	cvttss2si %xmm0,%esi
  8460aa:	lea    0x460(%rsp),%rdi
  8460b2:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8460b7:	lea    0x460(%rsp),%rdx
  8460bf:	lea    0x450(%rsp),%rdi
  8460c7:	mov    $0xfd0b3c,%esi
  8460cc:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8460d1:	lea    0x440(%rsp),%r15
  8460d9:	lea    0x450(%rsp),%rsi
  8460e1:	mov    $0xfd0b98,%edx
  8460e6:	mov    %r15,%rdi
  8460e9:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  8460ee:	lea    0x430(%rsp),%r14
  8460f6:	mov    $0x147e868,%edx
  8460fb:	mov    %r15,%rsi
  8460fe:	mov    %r14,%rdi
  846101:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846106:	lea    0x420(%rsp),%r13
  84610e:	mov    %r14,%rsi
  846111:	mov    %r13,%rdi
  846114:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846119:	movss  0x788377(%rip),%xmm0        # fce498 <vtable for iInventoryListener+0x58>
  846121:	mov    $0x1,%esi
  846126:	movss  0xbdea0e(%rip),%xmm1        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  84612e:	mov    %rbx,%rdi
  846131:	movss  0xbde9ff(%rip),%xmm2        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  846139:	mulss  %xmm0,%xmm1
  84613d:	mulss  %xmm0,%xmm2
  846141:	mulss  0xbde9eb(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  846149:	movss  %xmm1,0x58(%rsp)
  84614f:	movss  %xmm2,0x74(%rsp)
  846155:	movss  %xmm0,0x88(%rsp)
  84615e:	call   9e7080 <CPositionableObject::getPosition(bool)>
  846163:	movq   %xmm0,0x28(%rsp)
  846169:	mov    0x28(%rsp),%rax
  84616e:	mov    0x68(%rsp),%rdx
  846173:	movss  %xmm1,0xa8(%rsp)
  84617c:	lea    0x320(%rsp),%rsi
  846184:	lea    0x130(%rsp),%r8
  84618c:	movss  0x74(%rsp),%xmm1
  846192:	lea    0x150(%rsp),%rcx
  84619a:	mov    %rax,0x330(%rsp)
  8461a2:	mov    %rax,0xa0(%rsp)
  8461aa:	mov    0xa8(%rsp),%eax
  8461b1:	movss  0x88(%rsp),%xmm0
  8461ba:	addss  0x334(%rsp),%xmm1
  8461c3:	movss  0x58(%rsp),%xmm2
  8461c9:	addss  0x330(%rsp),%xmm0
  8461d2:	mov    %eax,0x338(%rsp)
  8461d9:	addss  0x338(%rsp),%xmm2
  8461e2:	movss  %xmm1,0x324(%rsp)
  8461eb:	movss  %xmm0,0x320(%rsp)
  8461f4:	movss  0x762544(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  8461fc:	movss  %xmm2,0x328(%rsp)
  846205:	mov    0x220(%rdx),%rax
  84620c:	mov    %r13,%rdx
  84620f:	movss  0x75e5e5(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846217:	mov    0x78(%rax),%rdi
  84621b:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  846220:	mov    %r13,%rdi
  846223:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846228:	mov    %r14,%rdi
  84622b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846230:	mov    %r15,%rdi
  846233:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846238:	lea    0x450(%rsp),%rdi
  846240:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846245:	lea    0x460(%rsp),%rdi
  84624d:	xor    %r15d,%r15d
  846250:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846255:	movss  0x762523(%rip),%xmm0        # fa8780 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xe0>
  84625d:	movss  0x64(%rsp),%xmm1
  846263:	mov    %rbp,%rdi
  846266:	xorps  %xmm1,%xmm0
  846269:	call   813af0 <CCharacter::modifyMana(float)>
  84626e:	jmp    844f01 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1031>
  846273:	mov    $0x138,%edi
  846278:	movss  %xmm0,0x30(%rsp)
  84627e:	call   85acc0 <Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0> >::operator new(unsigned long)>
  846283:	mov    %rax,%r13
  846286:	cvttss2si 0x30(%rsp),%eax
  84628c:	cvtsi2ss %eax,%xmm0
  846290:	xorps  %xmm2,%xmm2
  846293:	xor    %r8d,%r8d
  846296:	movss  0x762442(%rip),%xmm1        # fa86e0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x40>
  84629e:	mov    $0x1,%ecx
  8462a3:	xor    %edx,%edx
  8462a5:	mov    $0x42,%esi
  8462aa:	mov    %r13,%rdi
  8462ad:	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  8462b2:	lea    0x3c0(%rsp),%r12
  8462ba:	lea    0x77b(%rsp),%rdx
  8462c2:	mov    $0xfcb938,%esi
  8462c7:	mov    %r12,%rdi
  8462ca:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8462cf:	mov    %r12,%rsi
  8462d2:	mov    %r13,%rdi
  8462d5:	call   85b970 <CEffect::setName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8462da:	mov    %r12,%rdi
  8462dd:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8462e2:	mov    %r13,%rsi
  8462e5:	mov    %rbp,%rdi
  8462e8:	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  8462ed:	jmp    84550f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x163f>
  8462f2:	lea    0x3e0(%rsp),%r13
  8462fa:	lea    0x77d(%rsp),%rdx
  846302:	mov    $0xfcb440,%esi
  846307:	mov    %r13,%rdi
  84630a:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  84630f:	mov    0x68(%rsp),%rdx
  846314:	mov    %r13,%rsi
  846317:	mov    0x220(%rdx),%rax
  84631e:	mov    0x78(%rax),%rax
  846322:	mov    0x1690(%rax),%rdi
  846329:	call   af05e0 <CConsole::addTextNoHistory(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  84632e:	mov    %r13,%rdi
  846331:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846336:	movl   $0x0,0x7c(%rsp)
  84633e:	jmp    84512e <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x125e>
  846343:	xorps  %xmm0,%xmm0
  846346:	movss  0x75e4ae(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84634e:	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  846353:	ucomiss 0x7881aa(%rip),%xmm0        # fce504 <vtable for iInventoryListener+0xc4>
  84635a:	movss  0x50(%rsp),%xmm1
  846360:	movss  %xmm1,0x54(%rsp)
  846366:	jae    844ed1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1001>
  84636c:	jnp    844e9d <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xfcd>
  846372:	jmp    844ed1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1001>
  846377:	nopw   0x0(%rax,%rax,1)
  846380:	mov    $0x147e858,%edi
  846385:	call   553558 <__cxa_guard_acquire@plt>
  84638a:	test   %eax,%eax
  84638c:	je     844f21 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1051>
  846392:	mov    $0x147e858,%edi
  846397:	movq   $0x1424558,0xc384be(%rip)        # 147e860 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Blocked>
  8463a2:	call   553fc8 <__cxa_guard_release@plt>
  8463a7:	mov    $0xf9f788,%edx
  8463ac:	mov    $0x147e860,%esi
  8463b1:	mov    $0x5548d8,%edi
  8463b6:	call   5551e8 <__cxa_atexit@plt>
  8463bb:	jmp    844f21 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1051>
  8463c0:	movss  0x7880c8(%rip),%xmm1        # fce490 <vtable for iInventoryListener+0x50>
  8463c8:	maxss  %xmm0,%xmm1
  8463cc:	movaps %xmm1,%xmm0
  8463cf:	jmp    845fb3 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x20e3>
  8463d4:	movss  0x7880b4(%rip),%xmm0        # fce490 <vtable for iInventoryListener+0x50>
  8463dc:	maxss  0x64(%rsp),%xmm0
  8463e2:	movss  %xmm0,0x64(%rsp)
  8463e8:	jmp    845e71 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1fa1>
  8463ed:	movss  0x78809b(%rip),%xmm0        # fce490 <vtable for iInventoryListener+0x50>
  8463f5:	maxss  0x64(%rsp),%xmm0
  8463fb:	movss  %xmm0,0x64(%rsp)
  846401:	jmp    845f21 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2051>
  846406:	xorps  %xmm2,%xmm2
  846409:	movss  %xmm2,0x50(%rsp)
  84640f:	jmp    845c84 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1db4>
  846414:	movaps %xmm4,%xmm0
  846417:	mov    %rbx,%rdi
  84641a:	movss  %xmm4,0x30(%rsp)
  846420:	call   838a50 <CCharacter::modifyHP(float)>
  846425:	movss  0x7880db(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  84642d:	lea    0x230(%rsp),%rdi
  846435:	movaps %xmm2,%xmm0
  846438:	movss  0x75e3bc(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846440:	movss  0x75e3f0(%rip),%xmm1        # fa4838 <vtable for Ogre::FrameListener+0x78>
  846448:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  84644d:	movss  0x7880b3(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846455:	lea    0x250(%rsp),%rdi
  84645d:	movaps %xmm2,%xmm0
  846460:	movss  0x75e394(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846468:	movss  0x75e3c8(%rip),%xmm1        # fa4838 <vtable for Ogre::FrameListener+0x78>
  846470:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846475:	movss  0x30(%rsp),%xmm4
  84647b:	movaps %xmm4,%xmm0
  84647e:	call   553678 <ceilf@plt>
  846483:	cvttss2si %xmm0,%esi
  846487:	lea    0x5c0(%rsp),%rdi
  84648f:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  846494:	lea    0x5c0(%rsp),%rdx
  84649c:	lea    0x5b0(%rsp),%rdi
  8464a4:	mov    $0xfd0b3c,%esi
  8464a9:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8464ae:	lea    0x5a0(%rsp),%r15
  8464b6:	lea    0x5b0(%rsp),%rsi
  8464be:	mov    $0xfd0b98,%edx
  8464c3:	mov    %r15,%rdi
  8464c6:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  8464cb:	lea    0x590(%rsp),%r14
  8464d3:	mov    $0x147e878,%edx
  8464d8:	mov    %r15,%rsi
  8464db:	mov    %r14,%rdi
  8464de:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8464e3:	lea    0x580(%rsp),%r13
  8464eb:	mov    %r14,%rsi
  8464ee:	mov    %r13,%rdi
  8464f1:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8464f6:	movss  0x788012(%rip),%xmm0        # fce510 <vtable for iInventoryListener+0xd0>
  8464fe:	mov    $0x1,%esi
  846503:	movss  0xbde631(%rip),%xmm2        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  84650b:	mov    %rbx,%rdi
  84650e:	movss  0xbde622(%rip),%xmm1        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  846516:	mulss  %xmm0,%xmm2
  84651a:	mulss  %xmm0,%xmm1
  84651e:	mulss  0xbde60e(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  846526:	movss  %xmm2,0x64(%rsp)
  84652c:	movss  %xmm1,0x74(%rsp)
  846532:	movss  %xmm0,0x88(%rsp)
  84653b:	call   9e7080 <CPositionableObject::getPosition(bool)>
  846540:	movq   %xmm0,0x28(%rsp)
  846546:	mov    0x28(%rsp),%rax
  84654b:	mov    0x68(%rsp),%rdx
  846550:	movss  %xmm1,0xa8(%rsp)
  846559:	lea    0x3a0(%rsp),%rsi
  846561:	lea    0x230(%rsp),%r8
  846569:	movss  0x74(%rsp),%xmm1
  84656f:	lea    0x250(%rsp),%rcx
  846577:	mov    %rax,0x3b0(%rsp)
  84657f:	mov    %rax,0xa0(%rsp)
  846587:	mov    0xa8(%rsp),%eax
  84658e:	movss  0x88(%rsp),%xmm0
  846597:	addss  0x3b4(%rsp),%xmm1
  8465a0:	movss  0x64(%rsp),%xmm2
  8465a6:	addss  0x3b0(%rsp),%xmm0
  8465af:	mov    %eax,0x3b8(%rsp)
  8465b6:	addss  0x3b8(%rsp),%xmm2
  8465bf:	movss  %xmm1,0x3a4(%rsp)
  8465c8:	movss  %xmm0,0x3a0(%rsp)
  8465d1:	movss  0x762167(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  8465d9:	movss  %xmm2,0x3a8(%rsp)
  8465e2:	mov    0x220(%rdx),%rax
  8465e9:	mov    %r13,%rdx
  8465ec:	movss  0x75e208(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8465f4:	mov    0x78(%rax),%rdi
  8465f8:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  8465fd:	mov    %r13,%rdi
  846600:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846605:	mov    %r14,%rdi
  846608:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84660d:	mov    %r15,%rdi
  846610:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846615:	lea    0x5b0(%rsp),%rdi
  84661d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846622:	lea    0x5c0(%rsp),%rdi
  84662a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84662f:	jmp    845ee6 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2016>
  846634:	lea    0x5d0(%rsp),%r13
  84663c:	call   e16d60 <CStringTranslate::getSinglton()>
  846641:	mov    %r13,%rdi
  846644:	mov    %rax,%rsi
  846647:	mov    $0xfcd1f4,%edx
  84664c:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  846651:	mov    %r13,%rsi
  846654:	mov    $0x147e878,%edi
  846659:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  84665e:	mov    %r13,%rdi
  846661:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846666:	jmp    845ea8 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1fd8>
  84666b:	mov    $0x147e840,%edi
  846670:	call   553558 <__cxa_guard_acquire@plt>
  846675:	test   %eax,%eax
  846677:	je     845e96 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1fc6>
  84667d:	mov    $0x147e840,%edi
  846682:	movq   $0x1424558,0xc381eb(%rip)        # 147e878 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  84668d:	call   553fc8 <__cxa_guard_release@plt>
  846692:	mov    $0xf9f788,%edx
  846697:	mov    $0x147e878,%esi
  84669c:	mov    $0x5548d8,%edi
  8466a1:	call   5551e8 <__cxa_atexit@plt>
  8466a6:	jmp    845e96 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1fc6>
  8466ab:	mov    $0x147e848,%edi
  8466b0:	call   553558 <__cxa_guard_acquire@plt>
  8466b5:	test   %eax,%eax
  8466b7:	je     845f46 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2076>
  8466bd:	mov    $0x147e848,%edi
  8466c2:	movq   $0x1424558,0xc381a3(%rip)        # 147e870 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_HP>
  8466cd:	call   553fc8 <__cxa_guard_release@plt>
  8466d2:	mov    $0xf9f788,%edx
  8466d7:	mov    $0x147e870,%esi
  8466dc:	mov    $0x5548d8,%edi
  8466e1:	call   5551e8 <__cxa_atexit@plt>
  8466e6:	jmp    845f46 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2076>
  8466eb:	mov    0x640(%rbx),%rdi
  8466f2:	movaps %xmm4,%xmm0
  8466f5:	movss  %xmm4,0x30(%rsp)
  8466fb:	call   838a50 <CCharacter::modifyHP(float)>
  846700:	movss  0x787e00(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846708:	lea    0x1b0(%rsp),%rdi
  846710:	movaps %xmm2,%xmm0
  846713:	movss  0x75e0e1(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84671b:	movss  0x75e115(%rip),%xmm1        # fa4838 <vtable for Ogre::FrameListener+0x78>
  846723:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846728:	movss  0x787dd8(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846730:	lea    0x1d0(%rsp),%rdi
  846738:	movaps %xmm2,%xmm0
  84673b:	movss  0x75e0b9(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846743:	movss  0x75e0ed(%rip),%xmm1        # fa4838 <vtable for Ogre::FrameListener+0x78>
  84674b:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846750:	movss  0x30(%rsp),%xmm4
  846756:	movaps %xmm4,%xmm0
  846759:	call   553678 <ceilf@plt>
  84675e:	cvttss2si %xmm0,%esi
  846762:	lea    0x510(%rsp),%rdi
  84676a:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  84676f:	lea    0x510(%rsp),%rdx
  846777:	lea    0x500(%rsp),%rdi
  84677f:	mov    $0xfd0b3c,%esi
  846784:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846789:	lea    0x4f0(%rsp),%r15
  846791:	lea    0x500(%rsp),%rsi
  846799:	mov    $0xfd0b98,%edx
  84679e:	mov    %r15,%rdi
  8467a1:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  8467a6:	lea    0x4e0(%rsp),%r14
  8467ae:	mov    $0x147e870,%edx
  8467b3:	mov    %r15,%rsi
  8467b6:	mov    %r14,%rdi
  8467b9:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8467be:	lea    0x4d0(%rsp),%r13
  8467c6:	mov    %r14,%rsi
  8467c9:	mov    %r13,%rdi
  8467cc:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8467d1:	movss  0x787d37(%rip),%xmm0        # fce510 <vtable for iInventoryListener+0xd0>
  8467d9:	mov    $0x1,%esi
  8467de:	movss  0xbde356(%rip),%xmm1        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  8467e6:	movss  0xbde34a(%rip),%xmm2        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  8467ee:	mulss  %xmm0,%xmm1
  8467f2:	mulss  %xmm0,%xmm2
  8467f6:	mulss  0xbde336(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  8467fe:	movss  %xmm1,0x64(%rsp)
  846804:	movss  %xmm2,0x74(%rsp)
  84680a:	movss  %xmm0,0x88(%rsp)
  846813:	mov    0x640(%rbx),%rdi
  84681a:	call   9e7080 <CPositionableObject::getPosition(bool)>
  84681f:	movq   %xmm0,0x28(%rsp)
  846825:	mov    0x28(%rsp),%rax
  84682a:	mov    0x68(%rsp),%rdx
  84682f:	movss  %xmm1,0xa8(%rsp)
  846838:	lea    0x360(%rsp),%rsi
  846840:	lea    0x1b0(%rsp),%r8
  846848:	movss  0x74(%rsp),%xmm1
  84684e:	lea    0x1d0(%rsp),%rcx
  846856:	mov    %rax,0x370(%rsp)
  84685e:	mov    %rax,0xa0(%rsp)
  846866:	mov    0xa8(%rsp),%eax
  84686d:	movss  0x88(%rsp),%xmm0
  846876:	addss  0x374(%rsp),%xmm1
  84687f:	movss  0x64(%rsp),%xmm2
  846885:	addss  0x370(%rsp),%xmm0
  84688e:	mov    %eax,0x378(%rsp)
  846895:	addss  0x378(%rsp),%xmm2
  84689e:	movss  %xmm1,0x364(%rsp)
  8468a7:	movss  %xmm0,0x360(%rsp)
  8468b0:	movss  0x761e88(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  8468b8:	movss  %xmm2,0x368(%rsp)
  8468c1:	mov    0x220(%rdx),%rax
  8468c8:	mov    %r13,%rdx
  8468cb:	movss  0x75df29(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8468d3:	mov    0x78(%rax),%rdi
  8468d7:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  8468dc:	mov    %r13,%rdi
  8468df:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8468e4:	mov    %r14,%rdi
  8468e7:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8468ec:	mov    %r15,%rdi
  8468ef:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8468f4:	lea    0x500(%rsp),%rdi
  8468fc:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846901:	lea    0x510(%rsp),%rdi
  846909:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84690e:	jmp    845f8c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x20bc>
  846913:	lea    0x520(%rsp),%r13
  84691b:	call   e16d60 <CStringTranslate::getSinglton()>
  846920:	mov    %r13,%rdi
  846923:	mov    %rax,%rsi
  846926:	mov    $0xfcd1f4,%edx
  84692b:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  846930:	mov    %r13,%rsi
  846933:	mov    $0x147e870,%edi
  846938:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  84693d:	mov    %r13,%rdi
  846940:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846945:	jmp    845f58 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2088>
  84694a:	movaps %xmm4,%xmm0
  84694d:	mov    %rbx,%rdi
  846950:	movss  %xmm4,0x30(%rsp)
  846956:	call   838a50 <CCharacter::modifyHP(float)>
  84695b:	movss  0x75de99(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846963:	lea    0x1f0(%rsp),%rdi
  84696b:	movaps %xmm3,%xmm0
  84696e:	movss  0x787b92(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846976:	movss  0x787b8e(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  84697e:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846983:	movss  0x75de71(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84698b:	lea    0x210(%rsp),%rdi
  846993:	movaps %xmm3,%xmm0
  846996:	movss  0x787b6a(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  84699e:	movss  0x787b66(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  8469a6:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  8469ab:	movss  0x30(%rsp),%xmm4
  8469b1:	movaps %xmm4,%xmm0
  8469b4:	call   553678 <ceilf@plt>
  8469b9:	cvttss2si %xmm0,%esi
  8469bd:	lea    0x570(%rsp),%rdi
  8469c5:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8469ca:	lea    0x570(%rsp),%rdx
  8469d2:	lea    0x560(%rsp),%rdi
  8469da:	mov    $0xff64d0,%esi
  8469df:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8469e4:	lea    0x550(%rsp),%r15
  8469ec:	lea    0x560(%rsp),%rsi
  8469f4:	mov    $0xfd0b98,%edx
  8469f9:	mov    %r15,%rdi
  8469fc:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  846a01:	lea    0x540(%rsp),%r14
  846a09:	mov    $0x147e878,%edx
  846a0e:	mov    %r15,%rsi
  846a11:	mov    %r14,%rdi
  846a14:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846a19:	lea    0x530(%rsp),%r13
  846a21:	mov    %r14,%rsi
  846a24:	mov    %r13,%rdi
  846a27:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846a2c:	movss  0x787adc(%rip),%xmm0        # fce510 <vtable for iInventoryListener+0xd0>
  846a34:	mov    $0x1,%esi
  846a39:	movss  0xbde0fb(%rip),%xmm1        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  846a41:	mov    %rbx,%rdi
  846a44:	movss  0xbde0ec(%rip),%xmm2        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  846a4c:	mulss  %xmm0,%xmm1
  846a50:	mulss  %xmm0,%xmm2
  846a54:	mulss  0xbde0d8(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  846a5c:	movss  %xmm1,0x64(%rsp)
  846a62:	movss  %xmm2,0x74(%rsp)
  846a68:	movss  %xmm0,0x88(%rsp)
  846a71:	call   9e7080 <CPositionableObject::getPosition(bool)>
  846a76:	movq   %xmm0,0x28(%rsp)
  846a7c:	mov    0x28(%rsp),%rax
  846a81:	mov    0x68(%rsp),%rdx
  846a86:	movss  %xmm1,0xa8(%rsp)
  846a8f:	lea    0x380(%rsp),%rsi
  846a97:	lea    0x1f0(%rsp),%r8
  846a9f:	movss  0x74(%rsp),%xmm1
  846aa5:	lea    0x210(%rsp),%rcx
  846aad:	mov    %rax,0x390(%rsp)
  846ab5:	mov    %rax,0xa0(%rsp)
  846abd:	mov    0xa8(%rsp),%eax
  846ac4:	movss  0x88(%rsp),%xmm0
  846acd:	addss  0x394(%rsp),%xmm1
  846ad6:	movss  0x64(%rsp),%xmm2
  846adc:	addss  0x390(%rsp),%xmm0
  846ae5:	mov    %eax,0x398(%rsp)
  846aec:	addss  0x398(%rsp),%xmm2
  846af5:	movss  %xmm1,0x384(%rsp)
  846afe:	movss  %xmm0,0x380(%rsp)
  846b07:	movss  0x761c31(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  846b0f:	movss  %xmm2,0x388(%rsp)
  846b18:	mov    0x220(%rdx),%rax
  846b1f:	mov    %r13,%rdx
  846b22:	movss  0x75dcd2(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846b2a:	mov    0x78(%rax),%rdi
  846b2e:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  846b33:	mov    %r13,%rdi
  846b36:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846b3b:	mov    %r14,%rdi
  846b3e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846b43:	mov    %r15,%rdi
  846b46:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846b4b:	lea    0x560(%rsp),%rdi
  846b53:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846b58:	lea    0x570(%rsp),%rdi
  846b60:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846b65:	jmp    845ee6 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2016>
  846b6a:	mov    0x640(%rbx),%rdi
  846b71:	movaps %xmm4,%xmm0
  846b74:	movss  %xmm4,0x30(%rsp)
  846b7a:	call   838a50 <CCharacter::modifyHP(float)>
  846b7f:	movss  0x75dc75(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846b87:	lea    0x170(%rsp),%rdi
  846b8f:	movaps %xmm3,%xmm0
  846b92:	movss  0x78796e(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846b9a:	movss  0x78796a(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  846ba2:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846ba7:	movss  0x75dc4d(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846baf:	lea    0x190(%rsp),%rdi
  846bb7:	movaps %xmm3,%xmm0
  846bba:	movss  0x787946(%rip),%xmm2        # fce508 <vtable for iInventoryListener+0xc8>
  846bc2:	movss  0x787942(%rip),%xmm1        # fce50c <vtable for iInventoryListener+0xcc>
  846bca:	call   554118 <CEGUI::colour::colour(float, float, float, float)@plt>
  846bcf:	movss  0x30(%rsp),%xmm4
  846bd5:	movaps %xmm4,%xmm0
  846bd8:	call   553678 <ceilf@plt>
  846bdd:	cvttss2si %xmm0,%esi
  846be1:	lea    0x4c0(%rsp),%rdi
  846be9:	call   c913a0 <STRINGS::GetValueAsWString(int)>
  846bee:	lea    0x4c0(%rsp),%rdx
  846bf6:	lea    0x4b0(%rsp),%rdi
  846bfe:	mov    $0xff64d0,%esi
  846c03:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846c08:	lea    0x4a0(%rsp),%r15
  846c10:	lea    0x4b0(%rsp),%rsi
  846c18:	mov    $0xfd0b98,%edx
  846c1d:	mov    %r15,%rdi
  846c20:	call   7014b0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  846c25:	lea    0x490(%rsp),%r14
  846c2d:	mov    $0x147e870,%edx
  846c32:	mov    %r15,%rsi
  846c35:	mov    %r14,%rdi
  846c38:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846c3d:	lea    0x480(%rsp),%r13
  846c45:	mov    %r14,%rsi
  846c48:	mov    %r13,%rdi
  846c4b:	call   c8dc90 <STRINGS::StringConvertToUTF8(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  846c50:	movss  0x7878b8(%rip),%xmm0        # fce510 <vtable for iInventoryListener+0xd0>
  846c58:	mov    $0x1,%esi
  846c5d:	movss  0xbdded7(%rip),%xmm1        # 1424b3c <Ogre::Vector3::UNIT_Y+0x8>
  846c65:	movss  0xbddecb(%rip),%xmm2        # 1424b38 <Ogre::Vector3::UNIT_Y+0x4>
  846c6d:	mulss  %xmm0,%xmm1
  846c71:	mulss  %xmm0,%xmm2
  846c75:	mulss  0xbddeb7(%rip),%xmm0        # 1424b34 <Ogre::Vector3::UNIT_Y>
  846c7d:	movss  %xmm1,0x64(%rsp)
  846c83:	movss  %xmm2,0x74(%rsp)
  846c89:	movss  %xmm0,0x88(%rsp)
  846c92:	mov    0x640(%rbx),%rdi
  846c99:	call   9e7080 <CPositionableObject::getPosition(bool)>
  846c9e:	movq   %xmm0,0x28(%rsp)
  846ca4:	mov    0x28(%rsp),%rax
  846ca9:	mov    0x68(%rsp),%rdx
  846cae:	movss  %xmm1,0xa8(%rsp)
  846cb7:	lea    0x340(%rsp),%rsi
  846cbf:	lea    0x170(%rsp),%r8
  846cc7:	movss  0x74(%rsp),%xmm1
  846ccd:	lea    0x190(%rsp),%rcx
  846cd5:	mov    %rax,0x350(%rsp)
  846cdd:	mov    %rax,0xa0(%rsp)
  846ce5:	mov    0xa8(%rsp),%eax
  846cec:	movss  0x88(%rsp),%xmm0
  846cf5:	addss  0x354(%rsp),%xmm1
  846cfe:	movss  0x64(%rsp),%xmm2
  846d04:	addss  0x350(%rsp),%xmm0
  846d0d:	mov    %eax,0x358(%rsp)
  846d14:	addss  0x358(%rsp),%xmm2
  846d1d:	movss  %xmm1,0x344(%rsp)
  846d26:	movss  %xmm0,0x340(%rsp)
  846d2f:	movss  0x761a09(%rip),%xmm1        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  846d37:	movss  %xmm2,0x348(%rsp)
  846d40:	mov    0x220(%rdx),%rax
  846d47:	mov    %r13,%rdx
  846d4a:	movss  0x75daaa(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  846d52:	mov    0x78(%rax),%rdi
  846d56:	call   a9c2a0 <CGameUI::addTextEvent(Ogre::Vector3 const&, std::string const&, float, float, CEGUI::colour, CEGUI::colour)>
  846d5b:	mov    %r13,%rdi
  846d5e:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846d63:	mov    %r14,%rdi
  846d66:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846d6b:	mov    %r15,%rdi
  846d6e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846d73:	lea    0x4b0(%rsp),%rdi
  846d7b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846d80:	lea    0x4c0(%rsp),%rdi
  846d88:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846d8d:	jmp    845f8c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x20bc>
  846d92:	mov    $0x147e850,%edi
  846d97:	call   553558 <__cxa_guard_acquire@plt>
  846d9c:	test   %eax,%eax
  846d9e:	je     846007 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2137>
  846da4:	mov    $0x147e850,%edi
  846da9:	movq   $0x1424558,0xc37ab4(%rip)        # 147e868 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)::g_Mana>
  846db4:	call   553fc8 <__cxa_guard_release@plt>
  846db9:	mov    $0xf9f788,%edx
  846dbe:	mov    $0x147e868,%esi
  846dc3:	mov    $0x5548d8,%edi
  846dc8:	call   5551e8 <__cxa_atexit@plt>
  846dcd:	jmp    846007 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2137>
  846dd2:	mov    %r13,%rdi
  846dd5:	mov    %rax,%rbx
  846dd8:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846ddd:	mov    %r14,%rdi
  846de0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846de5:	mov    %r15,%rdi
  846de8:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846ded:	lea    0x500(%rsp),%rdi
  846df5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846dfa:	lea    0x510(%rsp),%rdi
  846e02:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e07:	mov    %rbx,%rdi
  846e0a:	call   554498 <_Unwind_Resume@plt>
  846e0f:	mov    %rax,%rbx
  846e12:	lea    0x680(%rsp),%rdi
  846e1a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e1f:	lea    0x690(%rsp),%rdi
  846e27:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e2c:	lea    0x660(%rsp),%rdi
  846e34:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e39:	mov    %rbx,%rdi
  846e3c:	call   554498 <_Unwind_Resume@plt>
  846e41:	mov    %rax,%rbx
  846e44:	jmp    846e1f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f4f>
  846e46:	mov    %rax,%rbx
  846e49:	jmp    846e2c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f5c>
  846e4b:	lea    0x6a0(%rsp),%rdi
  846e53:	mov    %rax,%rbx
  846e56:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e5b:	mov    %rbx,%rdi
  846e5e:	call   554498 <_Unwind_Resume@plt>
  846e63:	mov    %rax,%rbx
  846e66:	mov    %r14,%rdi
  846e69:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e6e:	mov    %r15,%rdi
  846e71:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e76:	lea    0x5b0(%rsp),%rdi
  846e7e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e83:	lea    0x5c0(%rsp),%rdi
  846e8b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846e90:	mov    %rbx,%rdi
  846e93:	call   554498 <_Unwind_Resume@plt>
  846e98:	mov    %rax,%rbx
  846e9b:	jmp    846e6e <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f9e>
  846e9d:	mov    %rax,%rbx
  846ea0:	jmp    846e76 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2fa6>
  846ea2:	mov    %rax,%rbx
  846ea5:	jmp    846e83 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2fb3>
  846ea7:	mov    $0x5541c8,%eax
  846eac:	test   %rax,%rax
  846eaf:	je     846ee6 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3016>
  846eb1:	or     $0xffffffff,%eax
  846eb4:	lock xadd %eax,0x10(%rdi)
  846eb9:	test   %eax,%eax
  846ebb:	jg     8440bd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1ed>
  846ec1:	lea    0x77a(%rsp),%rsi
  846ec9:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  846ece:	jmp    8440bd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x1ed>
  846ed3:	mov    %r12,%rdi
  846ed6:	mov    %rax,%rbx
  846ed9:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846ede:	mov    %rbx,%rdi
  846ee1:	call   554498 <_Unwind_Resume@plt>
  846ee6:	mov    0x10(%rdi),%eax
  846ee9:	lea    -0x1(%rax),%edx
  846eec:	mov    %edx,0x10(%rdi)
  846eef:	jmp    846eb9 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2fe9>
  846ef1:	mov    %rax,%rbx
  846ef4:	jmp    846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  846ef6:	mov    %r13,%rdi
  846ef9:	mov    %rax,%rbx
  846efc:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  846f01:	jmp    846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  846f03:	mov    %rax,%rbx
  846f06:	jmp    846ddd <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f0d>
  846f0b:	mov    %rax,%rbx
  846f0e:	xchg   %ax,%ax
  846f10:	jmp    846de5 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f15>
  846f15:	mov    %rax,%rbx
  846f18:	jmp    846ded <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f1d>
  846f1d:	mov    %rax,%rbx
  846f20:	jmp    846dfa <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f2a>
  846f25:	mov    %r13,%rdi
  846f28:	mov    %rax,%rbx
  846f2b:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  846f30:	jmp    846e66 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f96>
  846f35:	mov    %r13,%rdi
  846f38:	mov    %rax,%rbx
  846f3b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846f40:	jmp    846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  846f42:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  846f44:	jmp    846ef1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3021>
  846f46:	lea    0x6b0(%rsp),%rdi
  846f4e:	mov    %rax,%rbx
  846f51:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846f56:	lea    0x6c0(%rsp),%rdi
  846f5e:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846f63:	mov    %rbx,%rdi
  846f66:	call   554498 <_Unwind_Resume@plt>
  846f6b:	mov    %rax,%rbx
  846f6e:	jmp    846f56 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3086>
  846f70:	lea    0x6d0(%rsp),%rdi
  846f78:	mov    %rax,%rbx
  846f7b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846f80:	lea    0x6e0(%rsp),%rdi
  846f88:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846f8d:	mov    %rbx,%rdi
  846f90:	call   554498 <_Unwind_Resume@plt>
  846f95:	mov    %rax,%rbx
  846f98:	jmp    846f80 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x30b0>
  846f9a:	lea    0x630(%rsp),%rdi
  846fa2:	mov    %rax,%rbx
  846fa5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846faa:	lea    0x640(%rsp),%rdi
  846fb2:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846fb7:	mov    %rbx,%rdi
  846fba:	call   554498 <_Unwind_Resume@plt>
  846fbf:	mov    %rax,%rbx
  846fc2:	jmp    846faa <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x30da>
  846fc4:	lea    0x650(%rsp),%rdi
  846fcc:	mov    %rax,%rbx
  846fcf:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846fd4:	lea    0x670(%rsp),%rdi
  846fdc:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  846fe1:	jmp    846e12 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x2f42>
  846fe6:	mov    %rax,%rbx
  846fe9:	jmp    846fd4 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3104>
  846feb:	xorps  %xmm1,%xmm1
  846fee:	movzbl 0x87(%rsp),%r13d
  846ff7:	movss  %xmm1,0x50(%rsp)
  846ffd:	jmp    844ddc <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0xf0c>
  847002:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  847007:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  84700c:	mov    %r13,%rdi
  84700f:	mov    %rax,%rbx
  847012:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  847017:	mov    %r14,%rdi
  84701a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84701f:	mov    %r15,%rdi
  847022:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847027:	lea    0x560(%rsp),%rdi
  84702f:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847034:	lea    0x570(%rsp),%rdi
  84703c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847041:	mov    %rbx,%rdi
  847044:	call   554498 <_Unwind_Resume@plt>
  847049:	mov    %rax,%rbx
  84704c:	jmp    847017 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3147>
  84704e:	mov    %rax,%rbx
  847051:	jmp    84701f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x314f>
  847053:	mov    %rax,%rbx
  847056:	jmp    847027 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3157>
  847058:	mov    %rax,%rbx
  84705b:	jmp    847034 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3164>
  84705d:	nopl   (%rax)
  847060:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  847065:	mov    %rax,%rbx
  847068:	lea    0x400(%rsp),%rdi
  847070:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847075:	mov    %rbx,%rdi
  847078:	call   554498 <_Unwind_Resume@plt>
  84707d:	mov    %r13,%rdi
  847080:	mov    %rax,%rbx
  847083:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  847088:	jmp    847068 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3198>
  84708a:	mov    %r13,%rdi
  84708d:	mov    %rax,%rbx
  847090:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  847095:	mov    %r14,%rdi
  847098:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84709d:	mov    %r15,%rdi
  8470a0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8470a5:	lea    0x450(%rsp),%rdi
  8470ad:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8470b2:	lea    0x460(%rsp),%rdi
  8470ba:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8470bf:	mov    %rbx,%rdi
  8470c2:	call   554498 <_Unwind_Resume@plt>
  8470c7:	mov    %rax,%rbx
  8470ca:	jmp    847095 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x31c5>
  8470cc:	mov    %rax,%rbx
  8470cf:	jmp    84709d <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x31cd>
  8470d1:	mov    %rax,%rbx
  8470d4:	jmp    8470a5 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x31d5>
  8470d6:	mov    %rax,%rbx
  8470d9:	jmp    8470b2 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x31e2>
  8470db:	lea    0x6f0(%rsp),%rdi
  8470e3:	mov    %rax,%rbx
  8470e6:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8470eb:	lea    0x700(%rsp),%rdi
  8470f3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8470f8:	mov    %rbx,%rdi
  8470fb:	call   554498 <_Unwind_Resume@plt>
  847100:	mov    %rax,%rbx
  847103:	jmp    8470eb <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x321b>
  847105:	lea    0x710(%rsp),%rdi
  84710d:	mov    %rax,%rbx
  847110:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847115:	lea    0x730(%rsp),%rdi
  84711d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847122:	lea    0x740(%rsp),%rdi
  84712a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84712f:	lea    0x750(%rsp),%rdi
  847137:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84713c:	lea    0x720(%rsp),%rdi
  847144:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847149:	mov    %rbx,%rdi
  84714c:	call   554498 <_Unwind_Resume@plt>
  847151:	mov    %rax,%rbx
  847154:	jmp    847115 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3245>
  847156:	mov    %rax,%rbx
  847159:	jmp    847122 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3252>
  84715b:	mov    %rax,%rbx
  84715e:	xchg   %ax,%ax
  847160:	jmp    84712f <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x325f>
  847162:	mov    %rax,%rbx
  847165:	jmp    84713c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x326c>
  847167:	lea    0x760(%rsp),%rdi
  84716f:	mov    %rax,%rbx
  847172:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847177:	mov    %rbx,%rdi
  84717a:	call   554498 <_Unwind_Resume@plt>
  84717f:	test   %r14b,%r14b
  847182:	mov    %rax,%rbx
  847185:	je     846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  84718b:	lea    0x770(%rsp),%rdi
  847193:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847198:	jmp    846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  84719d:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  8471a2:	jmp    846ef1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3021>
  8471a7:	mov    %r12,%rdi
  8471aa:	mov    %rax,%rbx
  8471ad:	nopl   (%rax)
  8471b0:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  8471b5:	jmp    846ede <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x300e>
  8471ba:	lea    0x610(%rsp),%rdi
  8471c2:	mov    %rax,%rbx
  8471c5:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8471ca:	lea    0x620(%rsp),%rdi
  8471d2:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8471d7:	mov    %rbx,%rdi
  8471da:	call   554498 <_Unwind_Resume@plt>
  8471df:	mov    %rax,%rbx
  8471e2:	jmp    8471ca <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x32fa>
  8471e4:	mov    %r13,%rdi
  8471e7:	mov    %rax,%rbx
  8471ea:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8471ef:	mov    %r14,%rdi
  8471f2:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8471f7:	mov    %rbx,%rdi
  8471fa:	call   554498 <_Unwind_Resume@plt>
  8471ff:	mov    %rax,%rbx
  847202:	jmp    8471ef <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x331f>
  847204:	jmp    846ef1 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3021>
  847209:	mov    %rax,%rbx
  84720c:	mov    %r12,%rdi
  84720f:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  847214:	mov    %rbx,%rdi
  847217:	call   554498 <_Unwind_Resume@plt>
  84721c:	jmp    846f35 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3065>
  847221:	mov    %r13,%rdi
  847224:	mov    %rax,%rbx
  847227:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84722c:	mov    %r14,%rdi
  84722f:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847234:	mov    %r15,%rdi
  847237:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  84723c:	lea    0x4b0(%rsp),%rdi
  847244:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847249:	lea    0x4c0(%rsp),%rdi
  847251:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  847256:	mov    %rbx,%rdi
  847259:	call   554498 <_Unwind_Resume@plt>
  84725e:	mov    %rax,%rbx
  847261:	jmp    84722c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x335c>
  847263:	mov    %rax,%rbx
  847266:	jmp    847234 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3364>
  847268:	mov    %rax,%rbx
  84726b:	jmp    84723c <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x336c>
  84726d:	mov    %rax,%rbx
  847270:	jmp    847249 <CCharacter::rollAttack(CLevel&, CCharacter*, CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)+0x3379>
