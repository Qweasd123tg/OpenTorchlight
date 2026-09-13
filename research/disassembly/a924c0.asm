
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a924c0 <CGameUI::onClick(ELayoutFunction)>:
  a924c0:	mov    %rbx,-0x18(%rsp)
  a924c5:	mov    %rbp,-0x10(%rsp)
  a924ca:	mov    %rdi,%rbx
  a924cd:	mov    %r12,-0x8(%rsp)
  a924d2:	sub    $0x58,%rsp
  a924d6:	mov    0x38(%rdi),%rax
  a924da:	mov    0x648(%rax),%rdx
  a924e1:	mov    0x650(%rax),%rax
  a924e8:	sub    %rdx,%rax
  a924eb:	sar    $0x3,%rax
  a924ef:	test   %eax,%eax
  a924f1:	je     a924fc <CGameUI::onClick(ELayoutFunction)+0x3c>
  a924f3:	test   %rax,%rax
  a924f6:	jne    a92610 <CGameUI::onClick(ELayoutFunction)+0x150>
  a924fc:	xor    %ebp,%ebp
  a924fe:	sub    $0xb,%esi
  a92501:	cmp    $0x54,%esi
  a92504:	ja     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9250a:	mov    %esi,%esi
  a9250c:	jmp    *0xfe4370(,%rsi,8)
  a92513:	nopl   0x0(%rax,%rax,1)
  a92518:	test   %rbp,%rbp
  a9251b:	movb   $0x1,0x1998(%rbx)
  a92522:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92528:	mov    0x40(%rbx),%rax
  a9252c:	mov    0x1d8(%rax),%rax
  a92533:	cmpb   $0x0,0x85(%rax)
  a9253a:	jne    a92a88 <CGameUI::onClick(ELayoutFunction)+0x5c8>
  a92540:	cmpb   $0x0,0xa274f9(%rip)        # 14b9a40 <guard variable for CGameUI::onClick(ELayoutFunction)::g_Pet>
  a92547:	je     a92af6 <CGameUI::onClick(ELayoutFunction)+0x636>
  a9254d:	mov    0xa27504(%rip),%rax        # 14b9a58 <CGameUI::onClick(ELayoutFunction)::g_Pet>
  a92554:	cmpq   $0x0,-0x18(%rax)
  a92559:	je     a92b76 <CGameUI::onClick(ELayoutFunction)+0x6b6>
  a9255f:	cmpb   $0x0,0xa274e2(%rip)        # 14b9a48 <guard variable for CGameUI::onClick(ELayoutFunction)::g_PetCannotDepart>
  a92566:	je     a92b36 <CGameUI::onClick(ELayoutFunction)+0x676>
  a9256c:	mov    0xa274dd(%rip),%rax        # 14b9a50 <CGameUI::onClick(ELayoutFunction)::g_PetCannotDepart>
  a92573:	cmpq   $0x0,-0x18(%rax)
  a92578:	jne    a925a9 <CGameUI::onClick(ELayoutFunction)+0xe9>
  a9257a:	lea    0x20(%rsp),%rbp
  a9257f:	call   e16d60 <CStringTranslate::getSinglton()>
  a92584:	mov    %rbp,%rdi
  a92587:	mov    %rax,%rsi
  a9258a:	mov    $0xfe4fd0,%edx
  a9258f:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  a92594:	mov    %rbp,%rsi
  a92597:	mov    $0x14b9a50,%edi
  a9259c:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  a925a1:	mov    %rbp,%rdi
  a925a4:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a925a9:	lea    0x10(%rsp),%rbp
  a925ae:	mov    $0x14b9a50,%esi
  a925b3:	mov    %rsp,%rdi
  a925b6:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  a925bb:	mov    $0x14b9a58,%esi
  a925c0:	mov    %rbp,%rdi
  a925c3:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  a925c8:	xor    %ecx,%ecx
  a925ca:	mov    %rsp,%rdx
  a925cd:	mov    %rbp,%rsi
  a925d0:	mov    %rbx,%rdi
  a925d3:	call   a8ec90 <CGameUI::openModalDialog(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool)>
  a925d8:	mov    %rbp,%rdi
  a925db:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a925e0:	mov    %rsp,%rdi
  a925e3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a925e8:	nopl   0x0(%rax,%rax,1)
  a925f0:	mov    $0x1,%eax
  a925f5:	mov    0x40(%rsp),%rbx
  a925fa:	mov    0x48(%rsp),%rbp
  a925ff:	mov    0x50(%rsp),%r12
  a92604:	add    $0x58,%rsp
  a92608:	ret
  a92609:	nopl   0x0(%rax)
  a92610:	mov    (%rdx),%rbp
  a92613:	jmp    a924fe <CGameUI::onClick(ELayoutFunction)+0x3e>
  a92618:	nopl   0x0(%rax,%rax,1)
  a92620:	movb   $0x1,0x1998(%rbx)
  a92627:	mov    %rbx,%rdi
  a9262a:	call   a82a80 <CGameUI::modalDialogOpenPartial()>
  a9262f:	test   %al,%al
  a92631:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92633:	mov    0x4e0(%rbx),%rdi
  a9263a:	mov    (%rdi),%rax
  a9263d:	call   *0x28(%rax)
  a92640:	test   %al,%al
  a92642:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92644:	mov    %rbx,%rdi
  a92647:	call   a833d0 <CGameUI::closeLeft()>
  a9264c:	mov    0x4e0(%rbx),%rdi
  a92653:	mov    $0x1,%esi
  a92658:	mov    (%rdi),%rax
  a9265b:	call   *0x40(%rax)
  a9265e:	mov    0x38(%rbx),%rax
  a92662:	mov    0x460(%rax),%eax
  a92668:	test   %eax,%eax
  a9266a:	jle    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9266c:	nopl   0x0(%rax)
  a92670:	mov    0x558(%rbx),%rdi
  a92677:	mov    (%rdi),%rax
  a9267a:	call   *0x28(%rax)
  a9267d:	test   %al,%al
  a9267f:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92685:	mov    %rbx,%rdi
  a92688:	call   a83450 <CGameUI::closeRight()>
  a9268d:	mov    0x558(%rbx),%rdi
  a92694:	mov    $0x1,%esi
  a92699:	mov    (%rdi),%rax
  a9269c:	call   *0x40(%rax)
  a9269f:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a926a4:	nopl   0x0(%rax)
  a926a8:	movb   $0x1,0x1998(%rbx)
  a926af:	mov    %rbx,%rdi
  a926b2:	call   a82a80 <CGameUI::modalDialogOpenPartial()>
  a926b7:	test   %al,%al
  a926b9:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a926bf:	mov    0x4e0(%rbx),%rdi
  a926c6:	mov    (%rdi),%rax
  a926c9:	call   *0x28(%rax)
  a926cc:	test   %al,%al
  a926ce:	jne    a92670 <CGameUI::onClick(ELayoutFunction)+0x1b0>
  a926d0:	mov    %rbx,%rdi
  a926d3:	call   a833d0 <CGameUI::closeLeft()>
  a926d8:	mov    0x4e0(%rbx),%rdi
  a926df:	mov    $0x1,%esi
  a926e4:	mov    (%rdi),%rax
  a926e7:	call   *0x40(%rax)
  a926ea:	jmp    a92670 <CGameUI::onClick(ELayoutFunction)+0x1b0>
  a926ec:	nopl   0x0(%rax)
  a926f0:	movb   $0x1,0x1998(%rbx)
  a926f7:	mov    %rbx,%rdi
  a926fa:	call   a82a80 <CGameUI::modalDialogOpenPartial()>
  a926ff:	test   %al,%al
  a92701:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92707:	mov    0x558(%rbx),%rdi
  a9270e:	mov    (%rdi),%rax
  a92711:	call   *0x28(%rax)
  a92714:	test   %al,%al
  a92716:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9271c:	mov    %rbx,%rdi
  a9271f:	call   a83450 <CGameUI::closeRight()>
  a92724:	mov    0x558(%rbx),%rdi
  a9272b:	mov    $0x1,%esi
  a92730:	mov    (%rdi),%rax
  a92733:	call   *0x40(%rax)
  a92736:	mov    0x38(%rbx),%rax
  a9273a:	mov    0x45c(%rax),%r12d
  a92741:	test   %r12d,%r12d
  a92744:	jle    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9274a:	mov    0x4e0(%rbx),%rdi
  a92751:	mov    (%rdi),%rax
  a92754:	call   *0x28(%rax)
  a92757:	test   %al,%al
  a92759:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9275f:	mov    %rbx,%rdi
  a92762:	call   a833d0 <CGameUI::closeLeft()>
  a92767:	mov    0x4e0(%rbx),%rdi
  a9276e:	mov    $0x1,%esi
  a92773:	mov    (%rdi),%rax
  a92776:	call   *0x40(%rax)
  a92779:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9277e:	xchg   %ax,%ax
  a92780:	mov    0x40(%rbx),%rdi
  a92784:	movb   $0x1,0x1998(%rbx)
  a9278b:	test   %rdi,%rdi
  a9278e:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92794:	cmpb   $0x0,0x1999(%rbx)
  a9279b:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a927a1:	movss  0x515f27(%rip),%xmm0        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  a927a9:	call   938810 <CLevel::zoomAutomap(float)>
  a927ae:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a927b3:	nopl   0x0(%rax,%rax,1)
  a927b8:	mov    0x40(%rbx),%rdi
  a927bc:	movb   $0x1,0x1998(%rbx)
  a927c3:	test   %rdi,%rdi
  a927c6:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a927cc:	cmpb   $0x0,0x1999(%rbx)
  a927d3:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a927d9:	movss  0x5537fb(%rip),%xmm0        # fe5fdc <typeinfo name for CSkillFoldout+0x1c>
  a927e1:	call   938810 <CLevel::zoomAutomap(float)>
  a927e6:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a927eb:	nopl   0x0(%rax,%rax,1)
  a927f0:	mov    0x78(%rbx),%rdi
  a927f4:	mov    0xa78d76(%rip),%esi        # 150b570 <KSETTINGS_TOGGLE_ITEM_NAME>
  a927fa:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  a927ff:	mov    0x78(%rbx),%rdi
  a92803:	mov    0xa78d67(%rip),%esi        # 150b570 <KSETTINGS_TOGGLE_ITEM_NAME>
  a92809:	xor    %edx,%edx
  a9280b:	test   %eax,%eax
  a9280d:	sete   %dl
  a92810:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  a92815:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9281a:	nopw   0x0(%rax,%rax,1)
  a92820:	mov    %rbx,%rdi
  a92823:	call   a8eb90 <CGameUI::toggleOptions()>
  a92828:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9282d:	nopl   (%rax)
  a92830:	mov    0x40(%rbx),%rdi
  a92834:	test   %rdi,%rdi
  a92837:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9283d:	cmpb   $0x0,0x1999(%rbx)
  a92844:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9284a:	call   938830 <CLevel::toggleAutomap()>
  a9284f:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92854:	nopl   0x0(%rax)
  a92858:	mov    %rbx,%rdi
  a9285b:	call   a8e5f0 <CGameUI::togglePet()>
  a92860:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92865:	nopl   (%rax)
  a92868:	mov    %rbx,%rdi
  a9286b:	call   a8e840 <CGameUI::toggleJournal()>
  a92870:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92875:	nopl   (%rax)
  a92878:	mov    %rbx,%rdi
  a9287b:	call   a8e930 <CGameUI::toggleSkill()>
  a92880:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92885:	nopl   (%rax)
  a92888:	mov    %rbx,%rdi
  a9288b:	call   a8e6a0 <CGameUI::toggleStats()>
  a92890:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92895:	nopl   (%rax)
  a92898:	mov    %rbx,%rdi
  a9289b:	call   a8e750 <CGameUI::toggleQuest()>
  a928a0:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a928a5:	nopl   (%rax)
  a928a8:	mov    %rbx,%rdi
  a928ab:	call   a8ea20 <CGameUI::toggleInventory()>
  a928b0:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a928b5:	nopl   (%rax)
  a928b8:	test   %rbp,%rbp
  a928bb:	movb   $0x1,0x1998(%rbx)
  a928c2:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a928c8:	movl   $0x2,0x16c8(%rbx)
  a928d2:	xor    %esi,%esi
  a928d4:	movl   $0x2,0x710(%rbp)
  a928de:	mov    %rbp,%rdi
  a928e1:	call   825310 <CCharacter::setTarget(CCharacter*)>
  a928e6:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a928eb:	nopl   0x0(%rax,%rax,1)
  a928f0:	test   %rbp,%rbp
  a928f3:	movb   $0x1,0x1998(%rbx)
  a928fa:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92900:	movl   $0x1,0x16c8(%rbx)
  a9290a:	xor    %esi,%esi
  a9290c:	movl   $0x1,0x710(%rbp)
  a92916:	mov    %rbp,%rdi
  a92919:	call   825310 <CCharacter::setTarget(CCharacter*)>
  a9291e:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92923:	nopl   0x0(%rax,%rax,1)
  a92928:	test   %rbp,%rbp
  a9292b:	movb   $0x1,0x1998(%rbx)
  a92932:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92938:	movl   $0x0,0x16c8(%rbx)
  a92942:	xor    %esi,%esi
  a92944:	movl   $0x0,0x710(%rbp)
  a9294e:	mov    %rbp,%rdi
  a92951:	call   825310 <CCharacter::setTarget(CCharacter*)>
  a92956:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a9295b:	nopl   0x0(%rax,%rax,1)
  a92960:	mov    0xb8(%rbx),%rdi
  a92967:	movb   $0x1,0x1998(%rbx)
  a9296e:	test   %rdi,%rdi
  a92971:	je     a92bb0 <CGameUI::onClick(ELayoutFunction)+0x6f0>
  a92977:	call   acbbe0 <CItem::isUseable()>
  a9297c:	test   %al,%al
  a9297e:	je     a92a28 <CGameUI::onClick(ELayoutFunction)+0x568>
  a92984:	mov    0x330(%rbp),%eax
  a9298a:	cmp    $0x2a,%eax
  a9298d:	je     a92a28 <CGameUI::onClick(ELayoutFunction)+0x568>
  a92993:	cmp    $0x29,%eax
  a92996:	je     a92a28 <CGameUI::onClick(ELayoutFunction)+0x568>
  a9299c:	mov    0x38(%rbx),%rcx
  a929a0:	mov    0x648(%rcx),%rdx
  a929a7:	mov    0x650(%rcx),%rax
  a929ae:	sub    %rdx,%rax
  a929b1:	sar    $0x3,%rax
  a929b5:	test   %eax,%eax
  a929b7:	je     a929f0 <CGameUI::onClick(ELayoutFunction)+0x530>
  a929b9:	xor    %r9d,%r9d
  a929bc:	test   %rax,%rax
  a929bf:	je     a929c4 <CGameUI::onClick(ELayoutFunction)+0x504>
  a929c1:	mov    (%rdx),%r9
  a929c4:	mov    0xb8(%rbx),%rdx
  a929cb:	mov    0x40(%rbx),%rsi
  a929cf:	mov    %rcx,%r8
  a929d2:	mov    %rbx,%rdi
  a929d5:	call   a92080 <CGameUI::performItemUse(CLevel&, CEquipment*, CCharacter*, CCharacter*, CCharacter*)>
  a929da:	cmpq   $0x0,0xb8(%rbx)
  a929e2:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a929e8:	mov    %rbx,%rdi
  a929eb:	call   a8f4e0 <CGameUI::returnDraggedItem()>
  a929f0:	mov    0xb8(%rbx),%rax
  a929f7:	test   %rax,%rax
  a929fa:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92a00:	mov    0x2c8(%rax),%rdi
  a92a07:	call   5547c8 <CEGUI::Window::moveToFront()@plt>
  a92a0c:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92a11:	nopl   0x0(%rax)
  a92a18:	mov    %rbx,%rdi
  a92a1b:	call   a8e2d0 <CGameUI::togglePause()>
  a92a20:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92a25:	nopl   (%rax)
  a92a28:	cmpq   $0x0,0xb8(%rbx)
  a92a30:	je     a92bb0 <CGameUI::onClick(ELayoutFunction)+0x6f0>
  a92a36:	mov    0x38(%rbx),%rax
  a92a3a:	xorps  %xmm1,%xmm1
  a92a3d:	mov    0x16a8(%rbx),%rdi
  a92a44:	xor    %ecx,%ecx
  a92a46:	mov    $0x18,%esi
  a92a4b:	mov    0x58(%rax),%rdx
  a92a4f:	movaps %xmm1,%xmm0
  a92a52:	call   a698a0 <CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool)>
  a92a57:	mov    0x38(%rbx),%rax
  a92a5b:	mov    0x298(%rax),%rdi
  a92a62:	test   %rdi,%rdi
  a92a65:	je     a929f0 <CGameUI::onClick(ELayoutFunction)+0x530>
  a92a67:	xorps  %xmm0,%xmm0
  a92a6a:	mov    $0x31,%esi
  a92a6f:	movss  0x511d95(%rip),%xmm1        # fa480c <vtable for Ogre::FrameListener+0x4c>
  a92a77:	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  a92a7c:	jmp    a929f0 <CGameUI::onClick(ELayoutFunction)+0x530>
  a92a81:	nopl   0x0(%rax)
  a92a88:	mov    %rbp,%rdi
  a92a8b:	call   814440 <CCharacter::isPetNearDeath()>
  a92a90:	test   %al,%al
  a92a92:	jne    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92a98:	mov    %rbp,%rdi
  a92a9b:	call   80e850 <CCharacter::alive()>
  a92aa0:	test   %al,%al
  a92aa2:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92aa8:	mov    0x330(%rbp),%eax
  a92aae:	cmp    $0x2a,%eax
  a92ab1:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92ab7:	cmp    $0x29,%eax
  a92aba:	je     a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92ac0:	mov    0x38(%rbx),%rax
  a92ac4:	mov    0x298(%rax),%rdi
  a92acb:	test   %rdi,%rdi
  a92ace:	je     a92ae5 <CGameUI::onClick(ELayoutFunction)+0x625>
  a92ad0:	xorps  %xmm0,%xmm0
  a92ad3:	mov    $0x2b,%esi
  a92ad8:	movss  0x511d2c(%rip),%xmm1        # fa480c <vtable for Ogre::FrameListener+0x4c>
  a92ae0:	call   a688a0 <CSoundBank::queueGlobalSample(int, float, float)>
  a92ae5:	mov    0x40(%rbx),%rsi
  a92ae9:	mov    %rbp,%rdi
  a92aec:	call   82c770 <CCharacter::sendToTown(CLevel&)>
  a92af1:	jmp    a925f0 <CGameUI::onClick(ELayoutFunction)+0x130>
  a92af6:	mov    $0x14b9a40,%edi
  a92afb:	call   553558 <__cxa_guard_acquire@plt>
  a92b00:	test   %eax,%eax
  a92b02:	je     a9254d <CGameUI::onClick(ELayoutFunction)+0x8d>
  a92b08:	mov    $0x14b9a40,%edi
  a92b0d:	movq   $0x1424558,0xa26f40(%rip)        # 14b9a58 <CGameUI::onClick(ELayoutFunction)::g_Pet>
  a92b18:	call   553fc8 <__cxa_guard_release@plt>
  a92b1d:	mov    $0xf9f788,%edx
  a92b22:	mov    $0x14b9a58,%esi
  a92b27:	mov    $0x5548d8,%edi
  a92b2c:	call   5551e8 <__cxa_atexit@plt>
  a92b31:	jmp    a9254d <CGameUI::onClick(ELayoutFunction)+0x8d>
  a92b36:	mov    $0x14b9a48,%edi
  a92b3b:	call   553558 <__cxa_guard_acquire@plt>
  a92b40:	test   %eax,%eax
  a92b42:	je     a9256c <CGameUI::onClick(ELayoutFunction)+0xac>
  a92b48:	mov    $0x14b9a48,%edi
  a92b4d:	movq   $0x1424558,0xa26ef8(%rip)        # 14b9a50 <CGameUI::onClick(ELayoutFunction)::g_PetCannotDepart>
  a92b58:	call   553fc8 <__cxa_guard_release@plt>
  a92b5d:	mov    $0xf9f788,%edx
  a92b62:	mov    $0x14b9a50,%esi
  a92b67:	mov    $0x5548d8,%edi
  a92b6c:	call   5551e8 <__cxa_atexit@plt>
  a92b71:	jmp    a9256c <CGameUI::onClick(ELayoutFunction)+0xac>
  a92b76:	lea    0x30(%rsp),%rbp
  a92b7b:	call   e16d60 <CStringTranslate::getSinglton()>
  a92b80:	mov    %rbp,%rdi
  a92b83:	mov    %rax,%rsi
  a92b86:	mov    $0xfcd17c,%edx
  a92b8b:	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  a92b90:	mov    %rbp,%rsi
  a92b93:	mov    $0x14b9a58,%edi
  a92b98:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  a92b9d:	mov    %rbp,%rdi
  a92ba0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a92ba5:	jmp    a9255f <CGameUI::onClick(ELayoutFunction)+0x9f>
  a92baa:	nopw   0x0(%rax,%rax,1)
  a92bb0:	mov    %rbx,%rdi
  a92bb3:	call   a8e5f0 <CGameUI::togglePet()>
  a92bb8:	jmp    a929f0 <CGameUI::onClick(ELayoutFunction)+0x530>
  a92bbd:	mov    %rbp,%rdi
  a92bc0:	mov    %rax,%rbx
  a92bc3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a92bc8:	mov    %rsp,%rdi
  a92bcb:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a92bd0:	mov    %rbx,%rdi
  a92bd3:	call   554498 <_Unwind_Resume@plt>
  a92bd8:	mov    %rax,%rbx
  a92bdb:	jmp    a92bc8 <CGameUI::onClick(ELayoutFunction)+0x708>
  a92bdd:	mov    %rax,%rbx
  a92be0:	mov    %rbp,%rdi
  a92be3:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  a92be8:	mov    %rbx,%rdi
  a92beb:	call   554498 <_Unwind_Resume@plt>
  a92bf0:	jmp    a92bdd <CGameUI::onClick(ELayoutFunction)+0x71d>
