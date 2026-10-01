# Accepted source evidence; full bodies for the listed small functions.
# ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000582d00 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:
  582d00:	push   %rbp
  582d01:	mov    %rsi,%rbp
  582d04:	push   %rbx
  582d05:	mov    %rdi,%rbx
  582d08:	sub    $0x18,%rsp
  582d0c:	mov    0x1a8(%rdi),%rdi
  582d13:	mov    (%rsi),%rsi
  582d16:	mov    -0x18(%rdi),%rdx
  582d1a:	cmp    -0x18(%rsi),%rdx
  582d1e:	je     582e28 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x128>
  582d24:	lea    0x1a8(%rbx),%rdi
  582d2b:	mov    %rbp,%rsi
  582d2e:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  582d33:	mov    0x78(%rbx),%rdi
  582d37:	xor    %esi,%esi
  582d39:	call   a9b420 <CGameUI::setPlayer(CCharacter*)>
  582d3e:	mov    0x70(%rbx),%rdi
  582d42:	mov    0x58(%rbx),%rsi
  582d46:	mov    $0x1,%edx
  582d4b:	call   949770 <CLevel::removeCharacter(CCharacter*, bool)>
  582d50:	mov    0x58(%rbx),%rdi
  582d54:	test   %rdi,%rdi
  582d57:	je     582d67 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x67>
  582d59:	mov    (%rdi),%rax
  582d5c:	call   *0x8(%rax)
  582d5f:	movq   $0x0,0x58(%rbx)
  582d67:	mov    0x70(%rbx),%rax
  582d6b:	mov    0x1a8(%rbx),%rsi
  582d72:	xor    %edx,%edx
  582d74:	mov    0x138(%rax),%rdi
  582d7b:	call   d78100 <CResourceManager::createPlayer(wchar_t const*, bool)>
  582d80:	mov    $0x1,%esi
  582d85:	mov    %rax,%rdi
  582d88:	mov    %rax,0x58(%rbx)
  582d8c:	call   840470 <CCharacter::setAlignment(EAlignment)>
  582d91:	mov    0x58(%rbx),%rdi
  582d95:	call   8e5020 <CPlayer::firstTimeSetup()>
  582d9a:	mov    0x78(%rbx),%rsi
  582d9e:	mov    %rsp,%rdi
  582da1:	add    $0x16b0,%rsi
  582da8:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  582dad:	mov    0x58(%rbx),%rdi
  582db1:	mov    %rsp,%rsi
  582db4:	add    $0x4c0,%rdi
  582dbb:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  582dc0:	mov    (%rsp),%rdi
  582dc4:	sub    $0x18,%rdi
  582dc8:	cmp    $0x1424540,%rdi
  582dcf:	jne    582e37 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x137>
  582dd1:	mov    0x58(%rbx),%rsi
  582dd5:	xor    %eax,%eax
  582dd7:	test   %rsi,%rsi
  582dda:	je     582e06 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x106>
  582ddc:	mov    0x70(%rbx),%rdi
  582de0:	xor    %ecx,%ecx
  582de2:	lea    0x140(%rdi),%rdx
  582de9:	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>
  582dee:	mov    0x70(%rbx),%rsi
  582df2:	mov    0x58(%rbx),%rdi
  582df6:	add    $0x164,%rsi
  582dfd:	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
  582e02:	mov    0x58(%rbx),%rax
  582e06:	mov    0x78(%rbx),%rdi
  582e0a:	mov    %rax,%rsi
  582e0d:	call   a9b420 <CGameUI::setPlayer(CCharacter*)>
  582e12:	movl   $0x3,0x1038(%rbx)
  582e1c:	add    $0x18,%rsp
  582e20:	pop    %rbx
  582e21:	pop    %rbp
  582e22:	ret
  582e23:	nopl   0x0(%rax,%rax,1)
  582e28:	call   5553e8 <wmemcmp@plt>
  582e2d:	test   %eax,%eax
  582e2f:	jne    582d24 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x24>
  582e35:	jmp    582e12 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x112>
  582e37:	mov    $0x5541c8,%eax
  582e3c:	test   %rax,%rax
  582e3f:	je     582e6f <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x16f>
  582e41:	or     $0xffffffff,%eax
  582e44:	lock xadd %eax,0x10(%rdi)
  582e49:	test   %eax,%eax
  582e4b:	jg     582dd1 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xd1>
  582e4d:	lea    0xf(%rsp),%rsi
  582e52:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  582e57:	jmp    582dd1 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xd1>
  582e5c:	mov    %rax,%rbx
  582e5f:	mov    %rsp,%rdi
  582e62:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  582e67:	mov    %rbx,%rdi
  582e6a:	call   554498 <_Unwind_Resume@plt>
  582e6f:	mov    0x10(%rdi),%eax
  582e72:	lea    -0x1(%rax),%edx
  582e75:	mov    %edx,0x10(%rdi)
  582e78:	jmp    582e49 <CGameClient::setCreationClass(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x149>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000584460 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)>:
  584460:	mov    %rbx,-0x20(%rsp)
  584465:	mov    %rbp,-0x18(%rsp)
  58446a:	mov    %rdi,%rbx
  58446d:	mov    %r12,-0x10(%rsp)
  584472:	mov    %r13,-0x8(%rsp)
  584477:	sub    $0x48,%rsp
  58447b:	test   %rsi,%rsi
  58447e:	mov    %rsi,%r12
  584481:	mov    %rdx,%r13
  584484:	mov    %rcx,%rbp
  584487:	jne    5844b0 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x50>
  584489:	movl   $0x3,0x1038(%rbx)
  584493:	mov    0x28(%rsp),%rbx
  584498:	mov    0x30(%rsp),%rbp
  58449d:	mov    0x38(%rsp),%r12
  5844a2:	mov    0x40(%rsp),%r13
  5844a7:	add    $0x48,%rsp
  5844ab:	ret
  5844ac:	nopl   0x0(%rax)
  5844b0:	cmpq   $0x0,0x58(%rdi)
  5844b5:	je     584489 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x29>
  5844b7:	lea    0x1a8(%rdi),%rdi
  5844be:	mov    %rdx,%rsi
  5844c1:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  5844c6:	mov    0x78(%rbx),%rdi
  5844ca:	xor    %esi,%esi
  5844cc:	call   a9b420 <CGameUI::setPlayer(CCharacter*)>
  5844d1:	mov    0x70(%rbx),%rdi
  5844d5:	mov    0x58(%rbx),%rsi
  5844d9:	mov    $0x1,%edx
  5844de:	call   949770 <CLevel::removeCharacter(CCharacter*, bool)>
  5844e3:	mov    0x58(%rbx),%rdi
  5844e7:	test   %rdi,%rdi
  5844ea:	je     5844fa <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x9a>
  5844ec:	mov    (%rdi),%rax
  5844ef:	call   *0x8(%rax)
  5844f2:	movq   $0x0,0x58(%rbx)
  5844fa:	mov    0x70(%rbx),%rax
  5844fe:	mov    0x0(%r13),%rsi
  584502:	mov    $0x1,%edx
  584507:	mov    0x138(%rax),%rdi
  58450e:	call   d78100 <CResourceManager::createPlayer(wchar_t const*, bool)>
  584513:	mov    %rax,0x58(%rbx)
  584517:	mov    (%rax),%rdx
  58451a:	mov    %r12,%rsi
  58451d:	mov    %rax,%rdi
  584520:	call   *0x2a0(%rdx)
  584526:	lea    0x40(%r12),%rsi
  58452b:	lea    0x10(%rsp),%r12
  584530:	mov    %r12,%rdi
  584533:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584538:	mov    0x58(%rbx),%rdi
  58453c:	mov    %r12,%rsi
  58453f:	add    $0x4c0,%rdi
  584546:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58454b:	mov    0x10(%rsp),%rdi
  584550:	sub    $0x18,%rdi
  584554:	cmp    $0x1424540,%rdi
  58455b:	jne    5846d5 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x275>
  584561:	mov    0x70(%rbx),%rdi
  584565:	mov    0x58(%rbx),%rsi
  584569:	xor    %ecx,%ecx
  58456b:	lea    0x140(%rdi),%rdx
  584572:	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>
  584577:	mov    0x70(%rbx),%rsi
  58457b:	mov    0x58(%rbx),%rdi
  58457f:	add    $0x164,%rsi
  584586:	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
  58458b:	mov    0x58(%rbx),%rsi
  58458f:	mov    0x78(%rbx),%rdi
  584593:	call   a9b420 <CGameUI::setPlayer(CCharacter*)>
  584598:	mov    0x70(%rbx),%rdi
  58459c:	mov    0x60(%rbx),%rsi
  5845a0:	mov    $0x1,%edx
  5845a5:	call   949770 <CLevel::removeCharacter(CCharacter*, bool)>
  5845aa:	mov    0x60(%rbx),%rdi
  5845ae:	test   %rdi,%rdi
  5845b1:	je     5845c1 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x161>
  5845b3:	mov    (%rdi),%rax
  5845b6:	call   *0x8(%rax)
  5845b9:	movq   $0x0,0x60(%rbx)
  5845c1:	test   %rbp,%rbp
  5845c4:	je     584489 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x29>
  5845ca:	mov    0x2b8(%rbx),%rdi
  5845d1:	mov    0xd0(%rbp),%edx
  5845d7:	xor    %r8d,%r8d
  5845da:	mov    0x20(%rbp),%rsi
  5845de:	mov    $0x1,%ecx
  5845e3:	call   d78a80 <CResourceManager::createUnit(long long, int, bool, bool)>
  5845e8:	xor    %edi,%edi
  5845ea:	test   %rax,%rax
  5845ed:	je     584606 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x1a6>
  5845ef:	mov    %rax,%rdi
  5845f2:	xor    %ecx,%ecx
  5845f4:	mov    $0xfce280,%edx
  5845f9:	mov    $0xfc9260,%esi
  5845fe:	call   555758 <__dynamic_cast@plt>
  584603:	mov    %rax,%rdi
  584606:	mov    %rdi,0x60(%rbx)
  58460a:	mov    (%rdi),%rdx
  58460d:	mov    %rbp,%rsi
  584610:	call   *0x2a0(%rdx)
  584616:	mov    0x60(%rbx),%rsi
  58461a:	lea    0x1b0(%rbx),%rdi
  584621:	add    $0x40,%rsi
  584625:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58462a:	mov    0x60(%rbx),%rdi
  58462e:	mov    $0x1,%esi
  584633:	call   840470 <CCharacter::setAlignment(EAlignment)>
  584638:	mov    0x60(%rbx),%rax
  58463c:	xor    %ecx,%ecx
  58463e:	movl   $0x2,0x710(%rax)
  584648:	mov    0x70(%rbx),%rdi
  58464c:	mov    0x60(%rbx),%rsi
  584650:	lea    0x170(%rdi),%rdx
  584657:	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>
  58465c:	mov    0x70(%rbx),%rsi
  584660:	mov    0x60(%rbx),%rdi
  584664:	add    $0x17c,%rsi
  58466b:	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
  584670:	mov    0x78(%rbx),%rsi
  584674:	mov    %rsp,%rdi
  584677:	add    $0x16b8,%rsi
  58467e:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584683:	mov    0x60(%rbx),%rdi
  584687:	mov    %rsp,%rsi
  58468a:	add    $0x4c0,%rdi
  584691:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584696:	mov    (%rsp),%rdi
  58469a:	mov    $0x1424540,%eax
  58469f:	sub    $0x18,%rdi
  5846a3:	cmp    %rdi,%rax
  5846a6:	je     584489 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x29>
  5846ac:	mov    $0x5541c8,%eax
  5846b1:	test   %rax,%rax
  5846b4:	je     58472f <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x2cf>
  5846b6:	or     $0xffffffff,%eax
  5846b9:	lock xadd %eax,0x10(%rdi)
  5846be:	test   %eax,%eax
  5846c0:	jg     584489 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x29>
  5846c6:	lea    0x1e(%rsp),%rsi
  5846cb:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  5846d0:	jmp    584489 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x29>
  5846d5:	mov    $0x5541c8,%eax
  5846da:	test   %rax,%rax
  5846dd:	je     584711 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x2b1>
  5846df:	or     $0xffffffff,%eax
  5846e2:	lock xadd %eax,0x10(%rdi)
  5846e7:	test   %eax,%eax
  5846e9:	jg     584561 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x101>
  5846ef:	lea    0x1f(%rsp),%rsi
  5846f4:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  5846f9:	jmp    584561 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x101>
  5846fe:	mov    %rax,%rbx
  584701:	mov    %r12,%rdi
  584704:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  584709:	mov    %rbx,%rdi
  58470c:	call   554498 <_Unwind_Resume@plt>
  584711:	mov    0x10(%rdi),%eax
  584714:	lea    -0x1(%rax),%edx
  584717:	mov    %edx,0x10(%rdi)
  58471a:	jmp    5846e7 <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x287>
  58471c:	mov    %rax,%rbx
  58471f:	mov    %rsp,%rdi
  584722:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  584727:	mov    %rbx,%rdi
  58472a:	call   554498 <_Unwind_Resume@plt>
  58472f:	mov    0x10(%rdi),%eax
  584732:	lea    -0x1(%rax),%edx
  584735:	mov    %edx,0x10(%rdi)
  584738:	jmp    5846be <CGameClient::applyCharacterState(CCharacterSaveState*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >&, CCharacterSaveState*)+0x25e>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000008126e0 <CCharacter::setToward(Ogre::Vector3 const&)>:
  8126e0:	push   %rbp
  8126e1:	push   %rbx
  8126e2:	mov    %rdi,%rbx
  8126e5:	lea    0xc0(%rbx),%rbp
  8126ec:	sub    $0x8,%rsp
  8126f0:	movss  0x8(%rsi),%xmm1
  8126f5:	movss  (%rsi),%xmm0
  8126f9:	call   553448 <atan2f@plt>
  8126fe:	movss  0x7bbd96(%rip),%xmm1        # fce49c <vtable for iInventoryListener+0x5c>
  812706:	call   c92dd0 <UTILITIES::VerifyFloat(float, float)>
  81270b:	mov    %rbp,%rdi
  81270e:	call   c7a2a0 <MATH::matrixRotationY(Ogre::Matrix4&, float)>
  812713:	mov    (%rbx),%rax
  812716:	mov    %rbx,%rdi
  812719:	mov    %rbp,%rsi
  81271c:	xor    %edx,%edx
  81271e:	call   *0x118(%rax)
  812724:	mov    (%rbx),%rax
  812727:	mov    %rbx,%rdi
  81272a:	mov    0x1c0(%rax),%rax
  812731:	add    $0x8,%rsp
  812735:	pop    %rbx
  812736:	pop    %rbp
  812737:	jmp    *%rax


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c7a2a0 <MATH::matrixRotationY(Ogre::Matrix4&, float)>:
  c7a2a0:	push   %rbx
  c7a2a1:	mov    %rdi,%rbx
  c7a2a4:	sub    $0x10,%rsp
  c7a2a8:	lea    0xc(%rsp),%rdi
  c7a2ad:	lea    0x8(%rsp),%rsi
  c7a2b2:	call   553118 <sincosf@plt>
  c7a2b7:	mov    0x7a9d02(%rip),%rdx        # 1423fc0 <Ogre::Matrix4::IDENTITY>
  c7a2be:	movss  0x32e4ba(%rip),%xmm1        # fa8780 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xe0>
  c7a2c6:	mov    0x8(%rsp),%eax
  c7a2ca:	movss  0xc(%rsp),%xmm0
  c7a2d0:	xorps  %xmm0,%xmm1
  c7a2d3:	mov    %rdx,(%rbx)
  c7a2d6:	mov    0x7a9ceb(%rip),%rdx        # 1423fc8 <Ogre::Matrix4::IDENTITY+0x8>
  c7a2dd:	mov    %rdx,0x8(%rbx)
  c7a2e1:	mov    0x7a9ce8(%rip),%rdx        # 1423fd0 <Ogre::Matrix4::IDENTITY+0x10>
  c7a2e8:	mov    %rdx,0x10(%rbx)
  c7a2ec:	mov    0x7a9ce5(%rip),%rdx        # 1423fd8 <Ogre::Matrix4::IDENTITY+0x18>
  c7a2f3:	mov    %rdx,0x18(%rbx)
  c7a2f7:	mov    0x7a9ce2(%rip),%rdx        # 1423fe0 <Ogre::Matrix4::IDENTITY+0x20>
  c7a2fe:	mov    %rdx,0x20(%rbx)
  c7a302:	mov    0x7a9cdf(%rip),%rdx        # 1423fe8 <Ogre::Matrix4::IDENTITY+0x28>
  c7a309:	mov    %rdx,0x28(%rbx)
  c7a30d:	mov    0x7a9cdc(%rip),%rdx        # 1423ff0 <Ogre::Matrix4::IDENTITY+0x30>
  c7a314:	mov    %rdx,0x30(%rbx)
  c7a318:	mov    0x7a9cd9(%rip),%rdx        # 1423ff8 <Ogre::Matrix4::IDENTITY+0x38>
  c7a31f:	movss  %xmm1,0x20(%rbx)
  c7a324:	mov    %eax,(%rbx)
  c7a326:	movss  %xmm0,0x8(%rbx)
  c7a32b:	mov    %eax,0x28(%rbx)
  c7a32e:	mov    %rdx,0x38(%rbx)
  c7a332:	add    $0x10,%rsp
  c7a336:	pop    %rbx
  c7a337:	ret


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009e8600 <CPropertyNode::CPropertyNode(CResourceManager*)>:
  9e8600:	push   %r12
  9e8602:	xor    %edx,%edx
  9e8604:	push   %rbp
  9e8605:	push   %rbx
  9e8606:	mov    %rdi,%rbx
  9e8609:	call   9e7a50 <CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*)>
  9e860e:	movq   $0xfd9ef0,(%rbx)
  9e8615:	movq   $0xfda0e0,0x100(%rbx)
  9e8620:	xor    %ecx,%ecx
  9e8622:	movl   $0x4,0x108(%rbx)
  9e862c:	movl   $0x1,0x10c(%rbx)
  9e8636:	xor    %edx,%edx
  9e8638:	movb   $0x1,0x110(%rbx)
  9e863f:	movb   $0x0,0x111(%rbx)
  9e8646:	xor    %esi,%esi
  9e8648:	movb   $0x1,0x112(%rbx)
  9e864f:	movl   $0x0,0x114(%rbx)
  9e8659:	mov    $0xb8,%edi
  9e865e:	movb   $0x0,0x118(%rbx)
  9e8665:	movq   $0x0,0x140(%rbx)
  9e8670:	movl   $0x1,0x138(%rbx)
  9e867a:	mov    0xa3bb2c(%rip),%eax        # 14241ac <Ogre::Vector3::ZERO>
  9e8680:	mov    %eax,0x120(%rbx)
  9e8686:	mov    0xa3bb24(%rip),%eax        # 14241b0 <Ogre::Vector3::ZERO+0x4>
  9e868c:	mov    %eax,0x124(%rbx)
  9e8692:	mov    0xa3bb1c(%rip),%eax        # 14241b4 <Ogre::Vector3::ZERO+0x8>
  9e8698:	mov    %eax,0x128(%rbx)
  9e869e:	mov    0xa3bb08(%rip),%eax        # 14241ac <Ogre::Vector3::ZERO>
  9e86a4:	mov    %eax,0x12c(%rbx)
  9e86aa:	mov    0xa3bb00(%rip),%eax        # 14241b0 <Ogre::Vector3::ZERO+0x4>
  9e86b0:	mov    %eax,0x130(%rbx)
  9e86b6:	mov    0xa3baf8(%rip),%eax        # 14241b4 <Ogre::Vector3::ZERO+0x8>
  9e86bc:	movq   $0x0,0x148(%rbx)
  9e86c7:	movb   $0x0,0x150(%rbx)
  9e86ce:	mov    %eax,0x134(%rbx)
  9e86d4:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  9e86d9:	mov    %rax,%rdi
  9e86dc:	mov    %rax,%rbp
  9e86df:	call   d796c0 <CRunicCore::CRunicCore()>
  9e86e4:	movq   $0xfc9310,0x0(%rbp)
  9e86ec:	movl   $0xbf000000,0x18(%rbp)
  9e86f3:	mov    %rbx,%rdi
  9e86f6:	movl   $0x0,0x14(%rbp)
  9e86fd:	movl   $0xbf000000,0x10(%rbp)
  9e8704:	movl   $0x3f000000,0x24(%rbp)
  9e870b:	movl   $0x40000000,0x20(%rbp)
  9e8712:	movl   $0x3f000000,0x1c(%rbp)
  9e8719:	movl   $0xbf000000,0x30(%rbp)
  9e8720:	movl   $0x0,0x2c(%rbp)
  9e8727:	movl   $0xbf000000,0x28(%rbp)
  9e872e:	movl   $0x3f000000,0x3c(%rbp)
  9e8735:	movl   $0x40000000,0x38(%rbp)
  9e873c:	movl   $0x3f000000,0x34(%rbp)
  9e8743:	movl   $0xbf000000,0x48(%rbp)
  9e874a:	movl   $0x0,0x44(%rbp)
  9e8751:	movl   $0xbf000000,0x40(%rbp)
  9e8758:	movl   $0x3f000000,0x54(%rbp)
  9e875f:	movl   $0x40000000,0x50(%rbp)
  9e8766:	movl   $0x3f000000,0x4c(%rbp)
  9e876d:	mov    (%rbx),%rax
  9e8770:	mov    %rbp,0x148(%rbx)
  9e8777:	movss  0x5bc07d(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  9e877f:	call   *0xc8(%rax)
  9e8785:	mov    $0x1,%esi
  9e878a:	mov    %rbx,%rdi
  9e878d:	call   a01cb0 <CSceneNodeObject::setVisible(bool)>
  9e8792:	pop    %rbx
  9e8793:	pop    %rbp
  9e8794:	pop    %r12
  9e8796:	ret
  9e8797:	mov    %rax,%r12
  9e879a:	mov    0x140(%rbx),%rdi
  9e87a1:	test   %rdi,%rdi
  9e87a4:	je     9e87ab <CPropertyNode::CPropertyNode(CResourceManager*)+0x1ab>
  9e87a6:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  9e87ab:	mov    %rbx,%rdi
  9e87ae:	movq   $0xfd93d0,0x100(%rbx)
  9e87b9:	call   9e7160 <CPositionableObject::~CPositionableObject()>
  9e87be:	mov    %r12,%rdi
  9e87c1:	call   554498 <_Unwind_Resume@plt>
  9e87c6:	mov    %rbp,%rdi
  9e87c9:	mov    %rax,%r12
  9e87cc:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  9e87d1:	jmp    9e879a <CPropertyNode::CPropertyNode(CResourceManager*)+0x19a>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009df820 <CLayout::editorObjectCreated(CEditorBaseObject*)>:
  9df820:	mov    %rbx,-0x28(%rsp)
  9df825:	mov    %rbp,-0x20(%rsp)
  9df82a:	mov    %rdi,%rbx
  9df82d:	mov    %r12,-0x18(%rsp)
  9df832:	mov    %r13,-0x10(%rsp)
  9df837:	mov    %rsi,%rbp
  9df83a:	mov    %r14,-0x8(%rsp)
  9df83f:	sub    $0x28,%rsp
  9df843:	mov    0x50(%rsi),%rax
  9df847:	test   %rax,%rax
  9df84a:	je     9df9d8 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x1b8>
  9df850:	cmp    %rax,0x48(%rdi)
  9df854:	je     9df9d8 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x1b8>
  9df85a:	mov    0x1b8(%rbx),%eax
  9df860:	cmp    $0x1,%eax
  9df863:	je     9df890 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x70>
  9df865:	cmp    $0x2,%eax
  9df868:	je     9df8e0 <CLayout::editorObjectCreated(CEditorBaseObject*)+0xc0>
  9df86a:	mov    (%rsp),%rbx
  9df86e:	mov    0x8(%rsp),%rbp
  9df873:	mov    0x10(%rsp),%r12
  9df878:	mov    0x18(%rsp),%r13
  9df87d:	mov    0x20(%rsp),%r14
  9df882:	add    $0x28,%rsp
  9df886:	ret
  9df887:	nopw   0x0(%rax,%rax,1)
  9df890:	xor    %ecx,%ecx
  9df892:	mov    $0xfdea20,%edx
  9df897:	mov    $0xfc4610,%esi
  9df89c:	mov    %rbp,%rdi
  9df89f:	call   555758 <__dynamic_cast@plt>
  9df8a4:	test   %rax,%rax
  9df8a7:	je     9df9f0 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x1d0>
  9df8ad:	lea    0x1d0(%rbx),%rdi
  9df8b4:	mov    %rbp,%rsi
  9df8b7:	mov    (%rsp),%rbx
  9df8bb:	mov    0x8(%rsp),%rbp
  9df8c0:	mov    0x10(%rsp),%r12
  9df8c5:	mov    0x18(%rsp),%r13
  9df8ca:	mov    0x20(%rsp),%r14
  9df8cf:	add    $0x28,%rsp
  9df8d3:	jmp    9e0a30 <TArrayList<CEditorBaseObject*>::add(CEditorBaseObject*)>
  9df8d8:	nopl   0x0(%rax,%rax,1)
  9df8e0:	xor    %ecx,%ecx
  9df8e2:	mov    $0xfc75c0,%edx
  9df8e7:	mov    $0xfc4610,%esi
  9df8ec:	mov    %rbp,%rdi
  9df8ef:	call   555758 <__dynamic_cast@plt>
  9df8f4:	test   %rax,%rax
  9df8f7:	je     9df9b0 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x190>
  9df8fd:	movb   $0x1,0x8c(%rax)
  9df904:	mov    0x1d8(%rbx),%eax
  9df90a:	lea    0x1d0(%rbx),%r12
  9df911:	mov    0x1dc(%rbx),%r13d
  9df918:	cmp    %r13d,%eax
  9df91b:	jb     9dfa20 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x200>
  9df921:	cmpq   $0x0,0x1d0(%rbx)
  9df929:	je     9dfa30 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x210>
  9df92f:	add    0x1e0(%rbx),%r13d
  9df936:	mov    %r13d,%edi
  9df939:	shl    $0x3,%rdi
  9df93d:	call   553ae8 <operator new[](unsigned long)@plt>
  9df942:	mov    0x1dc(%rbx),%r8d
  9df949:	mov    %rax,%r14
  9df94c:	test   %r8d,%r8d
  9df94f:	je     9df970 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x150>
  9df951:	xor    %eax,%eax
  9df953:	nopl   0x0(%rax,%rax,1)
  9df958:	mov    (%r12),%rcx
  9df95c:	mov    %eax,%edx
  9df95e:	add    $0x1,%eax
  9df961:	mov    (%rcx,%rdx,8),%rcx
  9df965:	mov    %rcx,(%r14,%rdx,8)
  9df969:	cmp    0xc(%r12),%eax
  9df96e:	jb     9df958 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x138>
  9df970:	mov    0x1d0(%rbx),%rdi
  9df977:	test   %rdi,%rdi
  9df97a:	je     9df981 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x161>
  9df97c:	call   553638 <operator delete[](void*)@plt>
  9df981:	mov    0x1d8(%rbx),%eax
  9df987:	mov    %r14,0x1d0(%rbx)
  9df98e:	mov    %r13d,0x1dc(%rbx)
  9df995:	mov    %eax,%eax
  9df997:	mov    %rbp,(%r14,%rax,8)
  9df99b:	addl   $0x1,0x1d8(%rbx)
  9df9a2:	jmp    9df86a <CLayout::editorObjectCreated(CEditorBaseObject*)+0x4a>
  9df9a7:	nopw   0x0(%rax,%rax,1)
  9df9b0:	xor    %ecx,%ecx
  9df9b2:	mov    $0xfdaec0,%edx
  9df9b7:	mov    $0xfc4610,%esi
  9df9bc:	mov    %rbp,%rdi
  9df9bf:	call   555758 <__dynamic_cast@plt>
  9df9c4:	test   %rax,%rax
  9df9c7:	jne    9df8ad <CLayout::editorObjectCreated(CEditorBaseObject*)+0x8d>
  9df9cd:	jmp    9df86a <CLayout::editorObjectCreated(CEditorBaseObject*)+0x4a>
  9df9d2:	nopw   0x0(%rax,%rax,1)
  9df9d8:	mov    0x0(%rbp),%rax
  9df9dc:	mov    %rbx,%rsi
  9df9df:	mov    %rbp,%rdi
  9df9e2:	call   *0x10(%rax)
  9df9e5:	jmp    9df85a <CLayout::editorObjectCreated(CEditorBaseObject*)+0x3a>
  9df9ea:	nopw   0x0(%rax,%rax,1)
  9df9f0:	xor    %ecx,%ecx
  9df9f2:	mov    $0xfdaec0,%edx
  9df9f7:	mov    $0xfc4610,%esi
  9df9fc:	mov    %rbp,%rdi
  9df9ff:	call   555758 <__dynamic_cast@plt>
  9dfa04:	test   %rax,%rax
  9dfa07:	jne    9df8ad <CLayout::editorObjectCreated(CEditorBaseObject*)+0x8d>
  9dfa0d:	xor    %ecx,%ecx
  9dfa0f:	mov    $0xff6620,%edx
  9dfa14:	jmp    9df9b7 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x197>
  9dfa16:	cs nopw 0x0(%rax,%rax,1)
  9dfa20:	mov    0x1d0(%rbx),%r14
  9dfa27:	jmp    9df995 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x175>
  9dfa2c:	nopl   0x0(%rax)
  9dfa30:	mov    0x1e0(%rbx),%eax
  9dfa36:	lea    0x0(,%rax,8),%rdi
  9dfa3e:	mov    %eax,0x1dc(%rbx)
  9dfa44:	call   553ae8 <operator new[](unsigned long)@plt>
  9dfa49:	mov    %rax,%r14
  9dfa4c:	mov    %rax,0x1d0(%rbx)
  9dfa53:	mov    0x1d8(%rbx),%eax
  9dfa59:	jmp    9df995 <CLayout::editorObjectCreated(CEditorBaseObject*)+0x175>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000059f070 <CEditorBaseObject::setParentGuid(long long)>:
  59f070:	mov    %rsi,0x18(%rdi)
  59f074:	ret


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000059f870 <CPositionableObject::setOrientation(Ogre::Matrix4 const&, bool)>:
  59f870:	mov    %rbx,-0x20(%rsp)
  59f875:	mov    %r13,-0x8(%rsp)
  59f87a:	mov    %rdi,%rbx
  59f87d:	mov    %rbp,-0x18(%rsp)
  59f882:	mov    %r12,-0x10(%rsp)
  59f887:	sub    $0x68,%rsp
  59f88b:	mov    (%rsi),%rax
  59f88e:	cmpq   $0x0,0x58(%rdi)
  59f893:	mov    %edx,%r13d
  59f896:	mov    %rax,0xc0(%rdi)
  59f89d:	mov    0x8(%rsi),%rax
  59f8a1:	mov    %rax,0xc8(%rdi)
  59f8a8:	mov    0x10(%rsi),%rax
  59f8ac:	mov    %rax,0xd0(%rdi)
  59f8b3:	mov    0x18(%rsi),%rax
  59f8b7:	mov    %rax,0xd8(%rdi)
  59f8be:	mov    0x20(%rsi),%rax
  59f8c2:	mov    %rax,0xe0(%rdi)
  59f8c9:	mov    0x28(%rsi),%rax
  59f8cd:	mov    %rax,0xe8(%rdi)
  59f8d4:	mov    0x30(%rsi),%rax
  59f8d8:	mov    %rax,0xf0(%rdi)
  59f8df:	mov    0x38(%rsi),%rax
  59f8e3:	mov    %rax,0xf8(%rdi)
  59f8ea:	je     59f918 <CPositionableObject::setOrientation(Ogre::Matrix4 const&, bool)+0xa8>
  59f8ec:	mov    (%rdi),%rax
  59f8ef:	lea    0x30(%rsp),%rbp
  59f8f4:	mov    %rsp,%rsi
  59f8f7:	call   *0xe0(%rax)
  59f8fd:	mov    %rsp,%rsi
  59f900:	mov    %rbp,%rdi
  59f903:	call   5535a8 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)@plt>
  59f908:	mov    0x58(%rbx),%rdi
  59f90c:	mov    %rbp,%rsi
  59f90f:	mov    (%rdi),%rax
  59f912:	call   *0xd0(%rax)
  59f918:	test   %r13b,%r13b
  59f91b:	je     59f93e <CPositionableObject::setOrientation(Ogre::Matrix4 const&, bool)+0xce>
  59f91d:	mov    (%rbx),%rax
  59f920:	movss  0xcc(%rbx),%xmm0
  59f928:	movss  0xec(%rbx),%xmm2
  59f930:	mov    %rbx,%rdi
  59f933:	movss  0xdc(%rbx),%xmm1
  59f93b:	call   *0x58(%rax)
  59f93e:	mov    (%rbx),%rax
  59f941:	mov    %rbx,%rdi
  59f944:	call   *0x1c0(%rax)
  59f94a:	mov    (%rbx),%rax
  59f94d:	lea    0xc0(%rbx),%rsi
  59f954:	mov    %rbx,%rdi
  59f957:	call   *0x1b0(%rax)
  59f95d:	mov    0x48(%rsp),%rbx
  59f962:	mov    0x50(%rsp),%rbp
  59f967:	mov    0x58(%rsp),%r12
  59f96c:	mov    0x60(%rsp),%r13
  59f971:	add    $0x68,%rsp
  59f975:	ret


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a01f30 <CSceneNodeObject::setParentPositionableObject(CPositionableObject*)>:
  a01f30:	test   %rsi,%rsi
  a01f33:	mov    %rsi,0x50(%rdi)
  a01f37:	je     a01f3d <CSceneNodeObject::setParentPositionableObject(CPositionableObject*)+0xd>
  a01f39:	mov    0x58(%rsi),%rsi
  a01f3d:	xor    %edx,%edx
  a01f3f:	jmp    a01e10 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)>


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a01e10 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)>:
  a01e10:	mov    %rbx,-0x18(%rsp)
  a01e15:	mov    %rbp,-0x10(%rsp)
  a01e1a:	mov    %rdi,%rbx
  a01e1d:	mov    %r12,-0x8(%rsp)
  a01e22:	sub    $0x18,%rsp
  a01e26:	cmpq   $0x0,0x70(%rdi)
  a01e2b:	mov    %rsi,%rbp
  a01e2e:	je     a01e39 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)+0x29>
  a01e30:	cmpb   $0x0,0x80(%rdi)
  a01e37:	jne    a01e97 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)+0x87>
  a01e39:	cmp    %rbp,0x70(%rbx)
  a01e3d:	mov    %dl,0x80(%rbx)
  a01e43:	je     a01e97 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)+0x87>
  a01e45:	mov    0x58(%rbx),%rdi
  a01e49:	movzbl 0x81(%rbx),%r12d
  a01e51:	test   %rdi,%rdi
  a01e54:	je     a01e62 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)+0x52>
  a01e56:	call   c86c20 <OGRE_UTILITIES::removeChildFromParentNode(Ogre::SceneNode*)>
  a01e5b:	movb   $0x0,0x81(%rbx)
  a01e62:	test   %rbp,%rbp
  a01e65:	mov    %rbp,0x70(%rbx)
  a01e69:	je     a01e90 <CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode*, bool)+0x80>
  a01e6b:	movzbl %r12b,%esi
  a01e6f:	mov    %rbx,%rdi
  a01e72:	mov    0x8(%rsp),%rbp
  a01e77:	mov    (%rsp),%rbx
  a01e7b:	mov    0x10(%rsp),%r12
  a01e80:	add    $0x18,%rsp
  a01e84:	jmp    a01cb0 <CSceneNodeObject::setVisible(bool)>
  a01e89:	nopl   0x0(%rax)
  a01e90:	movb   $0x0,0x80(%rbx)
  a01e97:	mov    (%rsp),%rbx
  a01e9b:	mov    0x8(%rsp),%rbp
  a01ea0:	mov    0x10(%rsp),%r12
  a01ea5:	add    $0x18,%rsp
  a01ea9:	ret


/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000074c660 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)>:
  74c660:	mov    %rbx,-0x30(%rsp)
  74c665:	mov    %rbp,-0x28(%rsp)
  74c66a:	mov    %rdx,%rbx
  74c66d:	mov    %r12,-0x20(%rsp)
  74c672:	mov    %r15,-0x8(%rsp)
  74c677:	mov    %rdi,%rbp
  74c67a:	mov    %r13,-0x18(%rsp)
  74c67f:	mov    %r14,-0x10(%rsp)
  74c684:	sub    $0x68,%rsp
  74c688:	mov    0x14(%rdx),%eax
  74c68b:	cmp    0x10(%rdx),%eax
  74c68e:	mov    %rsi,%r12
  74c691:	mov    %r8d,%r15d
  74c694:	je     74c830 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d0>
  74c69a:	lea    0x2c(%rsp),%rsi
  74c69f:	mov    $0x4,%edx
  74c6a4:	mov    %rbx,%rdi
  74c6a7:	movl   $0xffffffff,0x2c(%rsp)
  74c6af:	call   ea9a30 <COgreReader::read(void*, unsigned int)>
  74c6b4:	mov    0x2c(%rsp),%esi
  74c6b8:	cmp    $0xffffffff,%esi
  74c6bb:	je     74c830 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d0>
  74c6c1:	mov    0x100(%rbp),%rdi
  74c6c8:	mov    $0x1,%edx
  74c6cd:	call   705f80 <CDescriptorManager::GetDescriptorByCreated(unsigned int, bool)>
  74c6d2:	test   %rax,%rax
  74c6d5:	mov    %rax,%r14
  74c6d8:	je     74c828 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1c8>
  74c6de:	mov    0x0(%rbp),%rax
  74c6e2:	xor    %ecx,%ecx
  74c6e4:	xor    %edx,%edx
  74c6e6:	mov    $0x1,%r8d
  74c6ec:	mov    %r14,%rsi
  74c6ef:	mov    %rbp,%rdi
  74c6f2:	call   *0x1d8(%rax)
  74c6f8:	test   %rax,%rax
  74c6fb:	mov    %rax,%r13
  74c6fe:	je     74c828 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1c8>
  74c704:	mov    0x38(%r12),%rdx
  74c709:	test   %rdx,%rdx
  74c70c:	je     74c7a5 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x145>
  74c712:	mov    0x8(%rdx),%ecx
  74c715:	mov    0xc(%rdx),%eax
  74c718:	cmp    %eax,%ecx
  74c71a:	jb     74c8c8 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x268>
  74c720:	cmpq   $0x0,(%rdx)
  74c724:	je     74c8d0 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x270>
  74c72a:	add    0x10(%rdx),%eax
  74c72d:	mov    %rdx,0x8(%rsp)
  74c732:	mov    %eax,%edi
  74c734:	mov    %eax,0x1c(%rsp)
  74c738:	shl    $0x3,%rdi
  74c73c:	call   553ae8 <operator new[](unsigned long)@plt>
  74c741:	mov    0x8(%rsp),%rdx
  74c746:	mov    0xc(%rdx),%r9d
  74c74a:	test   %r9d,%r9d
  74c74d:	je     74c76d <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x10d>
  74c74f:	xor    %ecx,%ecx
  74c751:	nopl   0x0(%rax)
  74c758:	mov    (%rdx),%rdi
  74c75b:	mov    %ecx,%esi
  74c75d:	add    $0x1,%ecx
  74c760:	mov    (%rdi,%rsi,8),%rdi
  74c764:	mov    %rdi,(%rax,%rsi,8)
  74c768:	cmp    0xc(%rdx),%ecx
  74c76b:	jb     74c758 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0xf8>
  74c76d:	mov    (%rdx),%rdi
  74c770:	test   %rdi,%rdi
  74c773:	je     74c78e <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x12e>
  74c775:	mov    %rax,0x10(%rsp)
  74c77a:	mov    %rdx,0x8(%rsp)
  74c77f:	call   553638 <operator delete[](void*)@plt>
  74c784:	mov    0x8(%rsp),%rdx
  74c789:	mov    0x10(%rsp),%rax
  74c78e:	mov    %rax,(%rdx)
  74c791:	mov    0x1c(%rsp),%ecx
  74c795:	mov    %ecx,0xc(%rdx)
  74c798:	mov    0x8(%rdx),%ecx
  74c79b:	mov    %ecx,%ecx
  74c79d:	mov    %r13,(%rax,%rcx,8)
  74c7a1:	addl   $0x1,0x8(%rdx)
  74c7a5:	mov    %r12,%rcx
  74c7a8:	mov    %r13,%rdx
  74c7ab:	mov    %rbx,%rsi
  74c7ae:	mov    %r14,%rdi
  74c7b1:	call   6ff040 <CDescriptor::loadObjectFromBinaryFile(COgreReader&, CEditorBaseObject*, CDescriptorLoadConfiguration&)>
  74c7b6:	test   %al,%al
  74c7b8:	je     74c828 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1c8>
  74c7ba:	test   %r15b,%r15b
  74c7bd:	movl   $0x0,0x28(%rsp)
  74c7c5:	movl   $0x0,0x24(%rsp)
  74c7cd:	movl   $0x0,0x20(%rsp)
  74c7d5:	jne    74c860 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x200>
  74c7db:	lea    0x28(%rsp),%rsi
  74c7e0:	mov    $0x4,%edx
  74c7e5:	mov    %rbx,%rdi
  74c7e8:	call   ea9a30 <COgreReader::read(void*, unsigned int)>
  74c7ed:	mov    0x28(%rsp),%r8d
  74c7f2:	test   %r8d,%r8d
  74c7f5:	je     74c830 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d0>
  74c7f7:	xor    %r14d,%r14d
  74c7fa:	jmp    74c80b <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1ab>
  74c7fc:	nopl   0x0(%rax)
  74c800:	add    $0x1,%r14d
  74c804:	cmp    %r14d,0x28(%rsp)
  74c809:	jbe    74c830 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d0>
  74c80b:	xor    %r8d,%r8d
  74c80e:	mov    %r13,%rcx
  74c811:	mov    %rbx,%rdx
  74c814:	mov    %r12,%rsi
  74c817:	mov    %rbp,%rdi
  74c81a:	call   74c660 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)>
  74c81f:	test   %al,%al
  74c821:	jne    74c800 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1a0>
  74c823:	nopl   0x0(%rax,%rax,1)
  74c828:	xor    %eax,%eax
  74c82a:	jmp    74c835 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d5>
  74c82c:	nopl   0x0(%rax)
  74c830:	mov    $0x1,%eax
  74c835:	mov    0x38(%rsp),%rbx
  74c83a:	mov    0x40(%rsp),%rbp
  74c83f:	mov    0x48(%rsp),%r12
  74c844:	mov    0x50(%rsp),%r13
  74c849:	mov    0x58(%rsp),%r14
  74c84e:	mov    0x60(%rsp),%r15
  74c853:	add    $0x68,%rsp
  74c857:	ret
  74c858:	nopl   0x0(%rax,%rax,1)
  74c860:	lea    0x28(%rsp),%rsi
  74c865:	mov    $0x4,%edx
  74c86a:	mov    %rbx,%rdi
  74c86d:	call   ea9a30 <COgreReader::read(void*, unsigned int)>
  74c872:	lea    0x24(%rsp),%rsi
  74c877:	mov    $0x4,%edx
  74c87c:	mov    %rbx,%rdi
  74c87f:	call   ea9a30 <COgreReader::read(void*, unsigned int)>
  74c884:	lea    0x20(%rsp),%rsi
  74c889:	mov    $0x4,%edx
  74c88e:	mov    %rbx,%rdi
  74c891:	call   ea9a30 <COgreReader::read(void*, unsigned int)>
  74c896:	mov    0x28(%rsp),%eax
  74c89a:	mov    %eax,0x118(%r13)
  74c8a1:	mov    0x20(%rsp),%eax
  74c8a5:	mov    0x24(%rsp),%edx
  74c8a9:	mov    %eax,0x110(%r13)
  74c8b0:	mov    $0x1,%eax
  74c8b5:	mov    %edx,0x10c(%r13)
  74c8bc:	jmp    74c835 <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x1d5>
  74c8c1:	nopl   0x0(%rax)
  74c8c8:	mov    (%rdx),%rax
  74c8cb:	jmp    74c79b <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x13b>
  74c8d0:	mov    0x10(%rdx),%eax
  74c8d3:	mov    %eax,%edi
  74c8d5:	mov    %eax,0xc(%rdx)
  74c8d8:	mov    %rdx,0x8(%rsp)
  74c8dd:	shl    $0x3,%rdi
  74c8e1:	call   553ae8 <operator new[](unsigned long)@plt>
  74c8e6:	mov    0x8(%rsp),%rdx
  74c8eb:	mov    %rax,(%rdx)
  74c8ee:	mov    0x8(%rdx),%ecx
  74c8f1:	jmp    74c79b <loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&, COgreReader&, CEditorBaseObject*, bool)+0x13b>


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000006373b0 <CRandomGroupDescriptor::CRandomGroupDescriptor()>:
  6373b0:	push   %r15
  6373b2:	mov    $0xfb3bd0,%edx
  6373b7:	mov    $0xfa8310,%esi
  6373bc:	xor    %r9d,%r9d
  6373bf:	mov    $0x1,%r8d
  6373c5:	mov    $0xfb3b20,%ecx
  6373ca:	push   %r14
  6373cc:	push   %r13
  6373ce:	push   %r12
  6373d0:	push   %rbp
  6373d1:	mov    %rdi,%rbp
  6373d4:	push   %rbx
  6373d5:	sub    $0x2f8,%rsp
  6373dc:	lea    0x290(%rsp),%r13
  6373e4:	movl   $0x0,0x10(%rsp)
  6373ec:	movl   $0x0,0x8(%rsp)
  6373f4:	movl   $0x0,(%rsp)
  6373fb:	call   624bd0 <CPositionableObjectDescriptor::CPositionableObjectDescriptor(wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool, bool, bool)>


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000074b2c0 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)>:
  74b2c0:	push   %r15
  74b2c2:	push   %r14
  74b2c4:	push   %r13
  74b2c6:	mov    %rdi,%r13
  74b2c9:	push   %r12
  74b2cb:	mov    %rsi,%r12
  74b2ce:	push   %rbp
  74b2cf:	push   %rbx
  74b2d0:	mov    %rdx,%rbx
  74b2d3:	sub    $0x58,%rsp
  74b2d7:	mov    0x8(%rsi),%eax
  74b2da:	movq   $0x0,0x30(%rsp)
  74b2e3:	movl   $0x0,0x38(%rsp)
  74b2eb:	movl   $0x0,0x3c(%rsp)
  74b2f3:	movq   $0x0,0x10(%rsp)
  74b2fc:	mov    %eax,0x40(%rsp)
  74b300:	movl   $0x0,0x18(%rsp)
  74b308:	movl   $0x0,0x1c(%rsp)
  74b310:	mov    %eax,0x20(%rsp)
  74b314:	mov    0x8(%rsi),%ebp
  74b317:	test   %ebp,%ebp
  74b319:	je     74b416 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x156>
  74b31f:	xor    %ebp,%ebp
  74b321:	jmp    74b347 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x87>
  74b323:	nopl   0x0(%rax,%rax,1)
  74b328:	mov    (%r12),%rax
  74b32c:	mov    0x20(%r13),%rcx
  74b330:	mov    (%rax),%rax
  74b333:	cmp    %rcx,0x18(%rax)
  74b337:	je     74b367 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0xa7>
  74b339:	add    $0x1,%ebp
  74b33c:	cmp    0x8(%r12),%ebp
  74b341:	jae    74b416 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x156>
  74b347:	mov    0xc(%r12),%edx
  74b34c:	cmp    %ebp,%edx
  74b34e:	jbe    74b328 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x68>
  74b350:	mov    %ebp,%eax
  74b352:	mov    0x20(%r13),%rcx
  74b356:	shl    $0x3,%rax
  74b35a:	add    (%r12),%rax
  74b35e:	mov    (%rax),%rax
  74b361:	cmp    %rcx,0x18(%rax)
  74b365:	jne    74b339 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x79>


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009601d6 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1086>:
  9601d6:	call   *0x50(%rdx)
  9601d9:	mov    0x268(%rsp),%rdi
  9601e1:	mov    $0x1,%esi
  9601e6:	call   9e7080 <CPositionableObject::getPosition(bool)>
  9601eb:	movq   %xmm0,0x18(%rsp)
  9601f1:	mov    0x18(%rsp),%rax
  9601f6:	movss  %xmm1,0xb8(%rsp)
  9601ff:	mov    %rax,0xb0(%rsp)
  960207:	mov    %rax,0x210(%rsp)
  96020f:	mov    0xb8(%rsp),%eax
  960216:	mov    %eax,0x218(%rsp)
  96021d:	mov    0x268(%rsp),%rax
  960225:	mov    0x58(%rax),%rdi
  960229:	mov    (%rdi),%rax
  96022c:	call   *0x1f8(%rax)
  960232:	mov    %rax,%rdi
  960235:	call   554308 <Ogre::Quaternion::zAxis() const@plt>
  96023a:	movq   %xmm0,0x18(%rsp)
  960240:	mov    0x18(%rsp),%rax
  960245:	movss  %xmm1,0xb8(%rsp)
  96024e:	xorps  %xmm3,%xmm3
  960251:	xorps  %xmm4,%xmm4
  960254:	mov    %rax,0x220(%rsp)
  96025c:	movss  0x220(%rsp),%xmm2
  960265:	mov    %rax,0xb0(%rsp)
  96026d:	movaps %xmm2,%xmm0
  960270:	mov    0xb8(%rsp),%eax
  960277:	mulss  %xmm2,%xmm0
  96027b:	mov    %eax,0x228(%rsp)
  960282:	movss  0x228(%rsp),%xmm1
  96028b:	addss  %xmm3,%xmm0
  96028f:	movaps %xmm1,%xmm3
  960292:	mulss  %xmm1,%xmm3
  960296:	addss  %xmm3,%xmm0
  96029a:	sqrtss %xmm0,%xmm0
  96029e:	unpcklps %xmm0,%xmm0
  9602a1:	cvtps2pd %xmm0,%xmm3
  9602a4:	ucomisd 0x6484f4(%rip),%xmm3        # fa87a0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x100>
  9602ac:	jbe    9602c6 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1176>
  9602ae:	movss  0x644546(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  9602b6:	divss  %xmm0,%xmm3
  9602ba:	mulss  %xmm3,%xmm2
  9602be:	mulss  %xmm3,%xmm4
  9602c2:	mulss  %xmm3,%xmm1
  9602c6:	mov    0x268(%rsp),%r12
  9602ce:	cmpl   $0xf,0x10c(%r12)
  9602d7:	jbe    960320 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11d0>
  9602d9:	cmpb   $0x0,0x110(%r12)
  9602e2:	jne    960e38 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1ce8>
  9602e8:	nopl   0x0(%rax,%rax,1)
  9602f0:	add    $0x1,%ebp
  9602f3:	add    $0x8,%r13
  9602f7:	cmp    %ebp,0x30(%rsp)
  9602fb:	jle    960370 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1220>
  9602fd:	.byte 0x39
  9602fe:	lods   (%rsi),%al
  9602ff:	.byte 0x24


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009609c0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1870>:
  9609c0:	cmpl   $0x3,0x4c(%rsp)
  9609c5:	je     9609d5 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1885>
  9609c7:	cmpl   $0x1,0x4c(%rsp)
  9609cc:	je     9609d5 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1885>
  9609ce:	cmpb   $0x0,0x67(%rsp)
  9609d3:	jne    960a19 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18c9>
  9609d5:	mov    0x210(%rsp),%eax
  9609dc:	mov    %eax,0x140(%rbx)
  9609e2:	mov    0x214(%rsp),%eax
  9609e9:	mov    %eax,0x144(%rbx)
  9609ef:	mov    0x218(%rsp),%eax
  9609f6:	movss  %xmm2,0x164(%rbx)
  9609fe:	movss  %xmm4,0x168(%rbx)
  960a06:	movss  %xmm1,0x16c(%rbx)
  960a0e:	mov    %eax,0x148(%rbx)
  960a14:	movb   $0x1,0x67(%rsp)
  960a19:	cmpq   $0x0,0x1e0(%rbx)
  960a21:	je     9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  960a27:	.byte 0xc7
  960a28:	.byte 0x84


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000960ad8 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1988>:
  960ad8:	cmpl   $0x3,0x4c(%rsp)
  960add:	je     960e98 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1d48>
  960ae3:	mov    0x210(%rsp),%ecx
  960aea:	mov    0x214(%rsp),%edx
  960af1:	mov    0x218(%rsp),%eax
  960af8:	mov    %ecx,0x78(%rsp)
  960afc:	mov    %edx,0x90(%rsp)
  960b03:	movss  %xmm2,0x84(%rsp)
  960b0c:	mov    %eax,0x94(%rsp)
  960b13:	movss  %xmm4,0x88(%rsp)
  960b1c:	movss  %xmm1,0x8c(%rsp)
  960b25:	jmp    9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  960b2a:	nopw   0x0(%rax,%rax,1)


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000960e98 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1d48>:
  960e98:	mov    0x210(%rsp),%ecx
  960e9f:	mov    %ecx,0x140(%rbx)
  960ea5:	mov    0x214(%rsp),%edx
  960eac:	mov    %edx,0x144(%rbx)
  960eb2:	mov    0x218(%rsp),%eax
  960eb9:	movss  %xmm2,0x164(%rbx)
  960ec1:	movss  %xmm4,0x168(%rbx)
  960ec9:	movss  %xmm1,0x16c(%rbx)
  960ed1:	mov    %eax,0x148(%rbx)
  960ed7:	movb   $0x1,0x67(%rsp)
  960edc:	jmp    960af8 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x19a8>
  960ee1:	nopl   0x0(%rax)
  960ee8:	mov    0x210(%rsp),%ecx
  960eef:	mov    %ecx,0x140(%rbx)
  960ef5:	mov    0x214(%rsp),%edx
  960efc:	mov    %edx,0x144(%rbx)
  960f02:	mov    0x218(%rsp),%eax
  960f09:	movss  %xmm2,0x164(%rbx)
  960f11:	repz
  960f12:	.byte 0xf
  960f13:	.byte 0x11
  960f14:	.byte 0xa3
  960f15:	.byte 0x68
  960f16:	add    %eax,(%rax)


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000084a6c3 <CCharacter::updateAnimation(float)+0x1e53>:
  84a6c3:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84a6c8:	mov    0x200(%rbx),%rdi
  84a6cf:	mov    %rbp,%rsi
  84a6d2:	call   8a7860 <CGenericModel::animationPlaying(std::string const&) const>
  84a6d7:	mov    %rbp,%rdi
  84a6da:	mov    %eax,%r12d
  84a6dd:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84a6e2:	test   %r12b,%r12b
  84a6e5:	je     84b0e4 <CCharacter::updateAnimation(float)+0x2874>


# WINDOW only; enclosing function remains partial.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000084b0fc <CCharacter::updateAnimation(float)+0x288c>:
  84b0fc:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b101:	mov    0x200(%rbx),%rdi
  84b108:	mov    %rbp,%rsi
  84b10b:	call   8a5530 <CGenericModel::animationQueued(std::string const&) const>
  84b110:	mov    %rbp,%rdi
  84b113:	mov    %eax,%r12d
  84b116:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b11b:	test   %r12b,%r12b
  84b11e:	jne    84a6eb <CCharacter::updateAnimation(float)+0x1e7b>
  84b124:	lea    0x250(%rsp),%rbp
  84b12c:	lea    0x428(%rsp),%rdx
  84b134:	mov    $0xfc993a,%esi
  84b139:	mov    %rbp,%rdi
  84b13c:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  84b141:	movss  0x75d617(%rip),%xmm2        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  84b149:	mov    $0x1,%edx
  84b14e:	movss  0x7596a6(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  84b156:	mov    %rbp,%rsi
  84b159:	movss  0x75d587(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  84b161:	mov    %rbx,%rdi
  84b164:	call   812830 <CCharacter::blendAnimation(std::string const&, bool, float, float, float)>
  84b169:	mov    %rbp,%rdi
  84b16c:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  84b171:	.byte 0xe9
  84b172:	jne    84b169 <CCharacter::updateAnimation(float)+0x28f9>
  84b174:	.byte 0xff
