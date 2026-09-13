
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000057b6a0 <CGameClient::clickRight(long long, bool, bool)>:
  57b6a0:	mov    %rbx,-0x30(%rsp)
  57b6a5:	mov    %rbp,-0x28(%rsp)
  57b6aa:	mov    %rdi,%rbx
  57b6ad:	mov    %r12,-0x20(%rsp)
  57b6b2:	mov    %r13,-0x18(%rsp)
  57b6b7:	mov    %rsi,%rbp
  57b6ba:	mov    %r14,-0x10(%rsp)
  57b6bf:	mov    %r15,-0x8(%rsp)
  57b6c4:	sub    $0x68,%rsp
  57b6c8:	mov    0x58(%rdi),%rdi
  57b6cc:	mov    %edx,%r12d
  57b6cf:	mov    %ecx,%r13d
  57b6d2:	call   80e850 <CCharacter::alive()>
  57b6d7:	test   %al,%al
  57b6d9:	jne    57b700 <CGameClient::clickRight(long long, bool, bool)+0x60>
  57b6db:	xor    %eax,%eax
  57b6dd:	mov    0x38(%rsp),%rbx
  57b6e2:	mov    0x40(%rsp),%rbp
  57b6e7:	mov    0x48(%rsp),%r12
  57b6ec:	mov    0x50(%rsp),%r13
  57b6f1:	mov    0x58(%rsp),%r14
  57b6f6:	mov    0x60(%rsp),%r15
  57b6fb:	add    $0x68,%rsp
  57b6ff:	ret
  57b700:	mov    0x58(%rbx),%rdi
  57b704:	mov    (%rdi),%rax
  57b707:	call   *0x48(%rax)
  57b70a:	test   %al,%al
  57b70c:	je     57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b70e:	test   %r12b,%r12b
  57b711:	jne    57b741 <CGameClient::clickRight(long long, bool, bool)+0xa1>
  57b713:	mov    0x58(%rbx),%rax
  57b717:	movl   $0x41200000,0x278(%rax)
  57b721:	mov    0x1c8(%rbx),%rsi
  57b728:	mov    0x58(%rbx),%rdi
  57b72c:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57b731:	mov    0x1f8(%rbx),%rsi
  57b738:	mov    0x58(%rbx),%rdi
  57b73c:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57b741:	mov    0x58(%rbx),%rax
  57b745:	mov    0x1c8(%rax),%rdi
  57b74c:	test   %rdi,%rdi
  57b74f:	je     57bb30 <CGameClient::clickRight(long long, bool, bool)+0x490>
  57b755:	mov    %rbp,%rsi
  57b758:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57b75d:	test   %rax,%rax
  57b760:	mov    %rax,%r14
  57b763:	je     57bca0 <CGameClient::clickRight(long long, bool, bool)+0x600>
  57b769:	mov    %r14,%rdi
  57b76c:	call   c9d090 <CSkill::getTargetType()>
  57b771:	cmp    $0x7,%eax
  57b774:	jne    57bb10 <CGameClient::clickRight(long long, bool, bool)+0x470>
  57b77a:	test   %r12b,%r12b
  57b77d:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b783:	mov    0x78(%rbx),%rdx
  57b787:	mov    0x12fc(%rdx),%eax
  57b78d:	cmp    $0x4,%eax
  57b790:	je     57bcd0 <CGameClient::clickRight(long long, bool, bool)+0x630>
  57b796:	xor    %r15d,%r15d
  57b799:	cmp    $0x3,%eax
  57b79c:	je     57bcd0 <CGameClient::clickRight(long long, bool, bool)+0x630>
  57b7a2:	mov    %r14,%rdi
  57b7a5:	call   c9d090 <CSkill::getTargetType()>
  57b7aa:	cmp    $0x3,%eax
  57b7ad:	je     57b7d8 <CGameClient::clickRight(long long, bool, bool)+0x138>
  57b7af:	mov    %r14,%rdi
  57b7b2:	call   c9d090 <CSkill::getTargetType()>
  57b7b7:	cmp    $0x9,%eax
  57b7ba:	je     57b7d8 <CGameClient::clickRight(long long, bool, bool)+0x138>
  57b7bc:	mov    %r14,%rdi
  57b7bf:	call   c9d090 <CSkill::getTargetType()>
  57b7c4:	cmp    $0xa,%eax
  57b7c7:	je     57b7d8 <CGameClient::clickRight(long long, bool, bool)+0x138>
  57b7c9:	test   %r15b,%r15b
  57b7cc:	jne    57bb30 <CGameClient::clickRight(long long, bool, bool)+0x490>
  57b7d2:	nopw   0x0(%rax,%rax,1)
  57b7d8:	cmpq   $0x0,0x1d8(%rbx)
  57b7e0:	je     57b84c <CGameClient::clickRight(long long, bool, bool)+0x1ac>
  57b7e2:	mov    0x1c8(%rbx),%rdi
  57b7e9:	test   %rdi,%rdi
  57b7ec:	je     57b84c <CGameClient::clickRight(long long, bool, bool)+0x1ac>
  57b7ee:	call   80e850 <CCharacter::alive()>
  57b7f3:	test   %al,%al
  57b7f5:	jne    57b84c <CGameClient::clickRight(long long, bool, bool)+0x1ac>
  57b7f7:	mov    0x1d8(%rbx),%r14
  57b7fe:	mov    0x1c8(%rbx),%rdi
  57b805:	cmp    %rdi,%r14
  57b808:	je     57b84c <CGameClient::clickRight(long long, bool, bool)+0x1ac>
  57b80a:	test   %rdi,%rdi
  57b80d:	lea    0x1c8(%rbx),%r15
  57b814:	je     57b824 <CGameClient::clickRight(long long, bool, bool)+0x184>
  57b816:	mov    0x1d0(%rbx),%edx
  57b81c:	mov    %r15,%rsi
  57b81f:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57b824:	test   %r14,%r14
  57b827:	movq   $0x0,0x1c8(%rbx)
  57b832:	je     57b845 <CGameClient::clickRight(long long, bool, bool)+0x1a5>
  57b834:	mov    %r15,%rsi
  57b837:	mov    %r14,%rdi
  57b83a:	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  57b83f:	mov    %eax,0x1d0(%rbx)
  57b845:	mov    %r14,0x1c8(%rbx)
  57b84c:	mov    0x1e8(%rbx),%r14
  57b853:	test   %r14,%r14
  57b856:	je     57b866 <CGameClient::clickRight(long long, bool, bool)+0x1c6>
  57b858:	cmpq   $0x0,0x1f8(%rbx)
  57b860:	je     57bc00 <CGameClient::clickRight(long long, bool, bool)+0x560>
  57b866:	cmpq   $0x0,0x1d8(%rbx)
  57b86e:	je     57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57b870:	cmpq   $0x0,0x1c8(%rbx)
  57b878:	je     57bb50 <CGameClient::clickRight(long long, bool, bool)+0x4b0>
  57b87e:	mov    0x58(%rbx),%rax
  57b882:	cmpb   $0x0,0x4d0(%rax)
  57b889:	mov    %rax,%rdi
  57b88c:	je     57baf8 <CGameClient::clickRight(long long, bool, bool)+0x458>
  57b892:	cmpb   $0x0,0x266(%rax)
  57b899:	je     57ba90 <CGameClient::clickRight(long long, bool, bool)+0x3f0>
  57b89f:	movb   $0x0,0x4d1(%rax)
  57b8a6:	mov    0x58(%rbx),%rax
  57b8aa:	movb   $0x0,0x4d0(%rax)
  57b8b1:	mov    0x58(%rbx),%rdi
  57b8b5:	call   80e910 <CCharacter::performingAttackLoose()>
  57b8ba:	test   %al,%al
  57b8bc:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b8c2:	mov    0x58(%rbx),%rax
  57b8c6:	mov    0x1c8(%rax),%rdi
  57b8cd:	test   %rdi,%rdi
  57b8d0:	je     57b938 <CGameClient::clickRight(long long, bool, bool)+0x298>
  57b8d2:	mov    %rbp,%rsi
  57b8d5:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57b8da:	test   %rax,%rax
  57b8dd:	mov    %rax,%r14
  57b8e0:	je     57bced <CGameClient::clickRight(long long, bool, bool)+0x64d>
  57b8e6:	mov    0x78(%rbx),%rdi
  57b8ea:	call   a83650 <CGameUI::equipmentTooltipVisible()>
  57b8ef:	test   %al,%al
  57b8f1:	je     57baa0 <CGameClient::clickRight(long long, bool, bool)+0x400>
  57b8f7:	lea    0xfe8(%rbx),%rdi
  57b8fe:	mov    $0x1,%esi
  57b903:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57b908:	test   %al,%al
  57b90a:	je     57baa0 <CGameClient::clickRight(long long, bool, bool)+0x400>
  57b910:	mov    %rbx,%rdi
  57b913:	call   56e570 <CGameClient::getIsPaused()>
  57b918:	test   %al,%al
  57b91a:	je     57b938 <CGameClient::clickRight(long long, bool, bool)+0x298>
  57b91c:	test   %r14,%r14
  57b91f:	je     57b938 <CGameClient::clickRight(long long, bool, bool)+0x298>
  57b921:	mov    %r14,%rdi
  57b924:	call   c9ceb0 <CSkill::getAnimationIndex()>
  57b929:	cmp    $0xffffffff,%eax
  57b92c:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b932:	nopw   0x0(%rax,%rax,1)
  57b938:	mov    %rbx,%rdi
  57b93b:	call   56e570 <CGameClient::getIsPaused()>
  57b940:	test   %al,%al
  57b942:	je     57b968 <CGameClient::clickRight(long long, bool, bool)+0x2c8>
  57b944:	mov    0x58(%rbx),%rdi
  57b948:	mov    0x398(%rdi),%rdi
  57b94f:	test   %rdi,%rdi
  57b952:	je     57b9c0 <CGameClient::clickRight(long long, bool, bool)+0x320>
  57b954:	call   c9ceb0 <CSkill::getAnimationIndex()>
  57b959:	cmp    $0xffffffff,%eax
  57b95c:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b962:	nopw   0x0(%rax,%rax,1)
  57b968:	mov    0x58(%rbx),%rdi
  57b96c:	mov    0x398(%rdi),%rax
  57b973:	test   %rax,%rax
  57b976:	je     57b9c0 <CGameClient::clickRight(long long, bool, bool)+0x320>
  57b978:	cmpb   $0x0,0x68(%rax)
  57b97c:	je     57b9c0 <CGameClient::clickRight(long long, bool, bool)+0x320>
  57b97e:	call   80e930 <CCharacter::performingSkill()>
  57b983:	test   %al,%al
  57b985:	jne    57bd20 <CGameClient::clickRight(long long, bool, bool)+0x680>
  57b98b:	mov    0x58(%rbx),%rdi
  57b98f:	mov    %rbp,%rsi
  57b992:	call   827eb0 <CCharacter::castSkill(long long)>
  57b997:	test   %al,%al
  57b999:	jne    57b9c0 <CGameClient::clickRight(long long, bool, bool)+0x320>
  57b99b:	mov    0x58(%rbx),%rdi
  57b99f:	cmpl   $0xd,0x330(%rdi)
  57b9a6:	je     57b9c0 <CGameClient::clickRight(long long, bool, bool)+0x320>
  57b9a8:	mov    (%rdi),%rax
  57b9ab:	mov    $0x2,%esi
  57b9b0:	call   *0x348(%rax)
  57b9b6:	cs nopw 0x0(%rax,%rax,1)
  57b9c0:	test   %r13b,%r13b
  57b9c3:	je     57ba10 <CGameClient::clickRight(long long, bool, bool)+0x370>
  57b9c5:	mov    0x1f8(%rbx),%rdi
  57b9cc:	test   %rdi,%rdi
  57b9cf:	je     57bdd8 <CGameClient::clickRight(long long, bool, bool)+0x738>
  57b9d5:	mov    0x1c8(%rbx),%rsi
  57b9dc:	test   %rsi,%rsi
  57b9df:	je     57b9f9 <CGameClient::clickRight(long long, bool, bool)+0x359>
  57b9e1:	mov    0x58(%rbx),%rdi
  57b9e5:	call   810200 <CCharacter::isEnemy(CCharacter*)>
  57b9ea:	test   %al,%al
  57b9ec:	je     57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57b9f2:	mov    0x1f8(%rbx),%rdi
  57b9f9:	test   %rdi,%rdi
  57b9fc:	je     57ba10 <CGameClient::clickRight(long long, bool, bool)+0x370>
  57b9fe:	mov    $0x1d,%esi
  57ba03:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  57ba08:	test   %al,%al
  57ba0a:	je     57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57ba10:	mov    0x58(%rbx),%rdi
  57ba14:	mov    0x350(%rdi),%r14
  57ba1b:	mov    0x340(%rdi),%r15
  57ba22:	call   80e9b0 <CCharacter::performingSkillLoose()>
  57ba27:	test   %al,%al
  57ba29:	je     57be99 <CGameClient::clickRight(long long, bool, bool)+0x7f9>
  57ba2f:	mov    0x1f8(%rbx),%rdi
  57ba36:	test   %rdi,%rdi
  57ba39:	je     57bd37 <CGameClient::clickRight(long long, bool, bool)+0x697>
  57ba3f:	mov    $0x1d,%esi
  57ba44:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  57ba49:	test   %al,%al
  57ba4b:	je     57bd37 <CGameClient::clickRight(long long, bool, bool)+0x697>
  57ba51:	cmp    0x1f8(%rbx),%r14
  57ba58:	je     57ba63 <CGameClient::clickRight(long long, bool, bool)+0x3c3>
  57ba5a:	mov    0x58(%rbx),%rdi
  57ba5e:	call   80e8b0 <CCharacter::stopPathing()>
  57ba63:	mov    0x58(%rbx),%rdi
  57ba67:	call   80e930 <CCharacter::performingSkill()>
  57ba6c:	test   %al,%al
  57ba6e:	je     57bedd <CGameClient::clickRight(long long, bool, bool)+0x83d>
  57ba74:	mov    0x58(%rbx),%rdi
  57ba78:	call   80e930 <CCharacter::performingSkill()>
  57ba7d:	test   %al,%al
  57ba7f:	je     57bf6f <CGameClient::clickRight(long long, bool, bool)+0x8cf>
  57ba85:	mov    $0x1,%eax
  57ba8a:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57ba8f:	nop
  57ba90:	movb   $0x1,0x98(%rbx)
  57ba97:	jmp    57b89f <CGameClient::clickRight(long long, bool, bool)+0x1ff>
  57ba9c:	nopl   0x0(%rax)
  57baa0:	mov    %r14,%rdi
  57baa3:	call   c9d090 <CSkill::getTargetType()>
  57baa8:	cmp    $0x7,%eax
  57baab:	je     57babe <CGameClient::clickRight(long long, bool, bool)+0x41e>
  57baad:	mov    %r14,%rdi
  57bab0:	call   c9d090 <CSkill::getTargetType()>
  57bab5:	cmp    $0x8,%eax
  57bab8:	jne    57b910 <CGameClient::clickRight(long long, bool, bool)+0x270>
  57babe:	mov    0x78(%rbx),%rdi
  57bac2:	mov    $0x4,%esi
  57bac7:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  57bacc:	mov    0x78(%rbx),%rax
  57bad0:	mov    %rbp,0xb0(%rax)
  57bad7:	mov    0x78(%rbx),%rdi
  57badb:	call   a84270 <CGameUI::flushInput()>
  57bae0:	mov    0x78(%rbx),%rdi
  57bae4:	call   a84250 <CGameUI::setRightButtonPressed()>
  57bae9:	mov    $0x1,%eax
  57baee:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57baf3:	nopl   0x0(%rax,%rax,1)
  57baf8:	cmpb   $0x0,0x4d1(%rax)
  57baff:	je     57b8b5 <CGameClient::clickRight(long long, bool, bool)+0x215>
  57bb05:	jmp    57b892 <CGameClient::clickRight(long long, bool, bool)+0x1f2>
  57bb0a:	nopw   0x0(%rax,%rax,1)
  57bb10:	mov    %r14,%rdi
  57bb13:	call   c9d090 <CSkill::getTargetType()>
  57bb18:	cmp    $0x8,%eax
  57bb1b:	je     57b77a <CGameClient::clickRight(long long, bool, bool)+0xda>
  57bb21:	test   %r14,%r14
  57bb24:	mov    $0x1,%r15d
  57bb2a:	jne    57b7a2 <CGameClient::clickRight(long long, bool, bool)+0x102>
  57bb30:	lea    0x20(%rsp),%rsi
  57bb35:	mov    $0x1,%edx
  57bb3a:	mov    %rbx,%rdi
  57bb3d:	call   579e90 <CGameClient::findWorldLocation(Ogre::Vector3&, bool)>
  57bb42:	test   %al,%al
  57bb44:	je     57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57bb4a:	jmp    57b7d8 <CGameClient::clickRight(long long, bool, bool)+0x138>
  57bb4f:	nop
  57bb50:	cmpq   $0x0,0x1f8(%rbx)
  57bb58:	jne    57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bb5e:	cmpb   $0x0,0x99(%rbx)
  57bb65:	jne    57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bb6b:	cmpb   $0x0,0x9a(%rbx)
  57bb72:	jne    57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bb78:	lea    0x2d0(%rbx),%rax
  57bb7f:	mov    $0x1428660,%r15d
  57bb85:	xor    %r14d,%r14d
  57bb88:	mov    %rax,0x8(%rsp)
  57bb8d:	nopl   (%rax)
  57bb90:	mov    0x58(%rbx),%rax
  57bb94:	mov    %r14d,%edx
  57bb97:	add    $0x116,%rdx
  57bb9e:	cmpq   $0xffffffffffffffff,(%rax,%rdx,8)
  57bba3:	je     57bbcd <CGameClient::clickRight(long long, bool, bool)+0x52d>
  57bba5:	mov    (%r15),%esi
  57bba8:	mov    0x50(%rbx),%rdi
  57bbac:	mov    %rdx,(%rsp)
  57bbb0:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57bbb5:	mov    0x8(%rsp),%rdi
  57bbba:	mov    %eax,%esi
  57bbbc:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57bbc1:	test   %al,%al
  57bbc3:	mov    (%rsp),%rdx
  57bbc7:	jne    57bc58 <CGameClient::clickRight(long long, bool, bool)+0x5b8>
  57bbcd:	add    $0x1,%r14d
  57bbd1:	add    $0x4,%r15
  57bbd5:	cmp    $0xa,%r14d
  57bbd9:	jne    57bb90 <CGameClient::clickRight(long long, bool, bool)+0x4f0>
  57bbdb:	mov    0x1d8(%rbx),%rsi
  57bbe2:	cmp    0x1c8(%rbx),%rsi
  57bbe9:	je     57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bbef:	lea    0x1c8(%rbx),%rdi
  57bbf6:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57bbfb:	jmp    57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bc00:	cmpq   $0x0,0x1c8(%rbx)
  57bc08:	jne    57b866 <CGameClient::clickRight(long long, bool, bool)+0x1c6>
  57bc0e:	cmpb   $0x0,0x99(%rbx)
  57bc15:	jne    57b866 <CGameClient::clickRight(long long, bool, bool)+0x1c6>
  57bc1b:	cmpb   $0x0,0x9a(%rbx)
  57bc22:	jne    57b866 <CGameClient::clickRight(long long, bool, bool)+0x1c6>
  57bc28:	lea    0x1f8(%rbx),%rsi
  57bc2f:	movq   $0x0,0x1f8(%rbx)
  57bc3a:	mov    %r14,%rdi
  57bc3d:	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  57bc42:	mov    %r14,0x1f8(%rbx)
  57bc49:	mov    %eax,0x200(%rbx)
  57bc4f:	jmp    57b866 <CGameClient::clickRight(long long, bool, bool)+0x1c6>
  57bc54:	nopl   0x0(%rax)
  57bc58:	mov    0x58(%rbx),%rax
  57bc5c:	mov    0x1c8(%rax),%rdi
  57bc63:	mov    (%rax,%rdx,8),%rsi
  57bc67:	test   %rdi,%rdi
  57bc6a:	je     57bbdb <CGameClient::clickRight(long long, bool, bool)+0x53b>
  57bc70:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57bc75:	mov    0x58(%rbx),%rdi
  57bc79:	cmp    0x398(%rdi),%rax
  57bc80:	jne    57bbdb <CGameClient::clickRight(long long, bool, bool)+0x53b>
  57bc86:	call   80e9b0 <CCharacter::performingSkillLoose()>
  57bc8b:	test   %al,%al
  57bc8d:	jne    57b87e <CGameClient::clickRight(long long, bool, bool)+0x1de>
  57bc93:	jmp    57bbdb <CGameClient::clickRight(long long, bool, bool)+0x53b>
  57bc98:	nopl   0x0(%rax,%rax,1)
  57bca0:	mov    0x58(%rbx),%rax
  57bca4:	mov    0x3b0(%rax),%rsi
  57bcab:	mov    0x1c8(%rax),%rdi
  57bcb2:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57bcb7:	test   %rax,%rax
  57bcba:	mov    %rax,%r14
  57bcbd:	je     57bb30 <CGameClient::clickRight(long long, bool, bool)+0x490>
  57bcc3:	jmp    57b769 <CGameClient::clickRight(long long, bool, bool)+0xc9>
  57bcc8:	nopl   0x0(%rax,%rax,1)
  57bcd0:	movq   $0xffffffffffffffff,0xb0(%rdx)
  57bcdb:	mov    0x78(%rbx),%rdi
  57bcdf:	xor    %esi,%esi
  57bce1:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  57bce6:	xor    %eax,%eax
  57bce8:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57bced:	mov    0x58(%rbx),%rax
  57bcf1:	mov    0x3b0(%rax),%rbp
  57bcf8:	mov    0x1c8(%rax),%rdi
  57bcff:	mov    %rbp,%rsi
  57bd02:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57bd07:	test   %rax,%rax
  57bd0a:	mov    %rax,%r14
  57bd0d:	je     57b910 <CGameClient::clickRight(long long, bool, bool)+0x270>
  57bd13:	jmp    57b8e6 <CGameClient::clickRight(long long, bool, bool)+0x246>
  57bd18:	nopl   0x0(%rax,%rax,1)
  57bd20:	mov    $0x1,%esi
  57bd25:	mov    %rbx,%rdi
  57bd28:	call   57a900 <CGameClient::moveToMouse(bool)>
  57bd2d:	mov    $0x1,%eax
  57bd32:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57bd37:	mov    0x1c8(%rbx),%rsi
  57bd3e:	test   %rsi,%rsi
  57bd41:	je     57bded <CGameClient::clickRight(long long, bool, bool)+0x74d>
  57bd47:	mov    0x58(%rbx),%rdi
  57bd4b:	call   810200 <CCharacter::isEnemy(CCharacter*)>
  57bd50:	test   %al,%al
  57bd52:	je     57bded <CGameClient::clickRight(long long, bool, bool)+0x74d>
  57bd58:	cmp    0x1c8(%rbx),%r15
  57bd5f:	je     57bd6a <CGameClient::clickRight(long long, bool, bool)+0x6ca>
  57bd61:	mov    0x58(%rbx),%rdi
  57bd65:	call   80e8b0 <CCharacter::stopPathing()>
  57bd6a:	mov    0x58(%rbx),%rdi
  57bd6e:	call   80e930 <CCharacter::performingSkill()>
  57bd73:	test   %al,%al
  57bd75:	je     57bf88 <CGameClient::clickRight(long long, bool, bool)+0x8e8>
  57bd7b:	mov    0x58(%rbx),%rdi
  57bd7f:	call   80e930 <CCharacter::performingSkill()>
  57bd84:	test   %al,%al
  57bd86:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bd8c:	mov    0x58(%rbx),%rdi
  57bd90:	mov    %rbp,%rsi
  57bd93:	call   827eb0 <CCharacter::castSkill(long long)>
  57bd98:	test   %al,%al
  57bd9a:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bda0:	mov    0x58(%rbx),%rdi
  57bda4:	cmpl   $0xd,0x330(%rdi)
  57bdab:	je     57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bdb1:	test   %r13b,%r13b
  57bdb4:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57bdba:	mov    (%rdi),%rax
  57bdbd:	mov    $0x2,%esi
  57bdc2:	call   *0x348(%rax)
  57bdc8:	mov    $0x1,%eax
  57bdcd:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57bdd2:	nopw   0x0(%rax,%rax,1)
  57bdd8:	mov    0x1c8(%rbx),%rsi
  57bddf:	test   %rsi,%rsi
  57bde2:	jne    57b9e1 <CGameClient::clickRight(long long, bool, bool)+0x341>
  57bde8:	jmp    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57bded:	test   %r12b,%r12b
  57bdf0:	jne    57be20 <CGameClient::clickRight(long long, bool, bool)+0x780>
  57bdf2:	mov    0x58(%rbx),%rdi
  57bdf6:	xor    %esi,%esi
  57bdf8:	movb   $0x0,0x98(%rbx)
  57bdff:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57be04:	mov    0x58(%rbx),%rdi
  57be08:	xor    %esi,%esi
  57be0a:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57be0f:	mov    0x58(%rbx),%rdi
  57be13:	call   80e9b0 <CCharacter::performingSkillLoose()>
  57be18:	test   %al,%al
  57be1a:	je     57c04a <CGameClient::clickRight(long long, bool, bool)+0x9aa>
  57be20:	lea    0x10(%rsp),%rsi
  57be25:	mov    $0x1,%edx
  57be2a:	mov    %rbx,%rdi
  57be2d:	call   579e90 <CGameClient::findWorldLocation(Ogre::Vector3&, bool)>
  57be32:	mov    0x58(%rbx),%rdi
  57be36:	xor    %esi,%esi
  57be38:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57be3d:	mov    0x58(%rbx),%rdi
  57be41:	xor    %esi,%esi
  57be43:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57be48:	mov    0x58(%rbx),%rdi
  57be4c:	movss  0x18(%rsp),%xmm1
  57be52:	movss  0x10(%rsp),%xmm0
  57be58:	call   827230 <CCharacter::setTargetDirection(float, float)>
  57be5d:	mov    0x58(%rbx),%rdi
  57be61:	mov    %rbp,%rsi
  57be64:	call   827eb0 <CCharacter::castSkill(long long)>
  57be69:	mov    0x58(%rbx),%rdi
  57be6d:	mov    %rbp,%rsi
  57be70:	call   827eb0 <CCharacter::castSkill(long long)>
  57be75:	test   %al,%al
  57be77:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57be7d:	mov    0x58(%rbx),%rax
  57be81:	cmpl   $0xd,0x330(%rax)
  57be88:	je     57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57be8e:	mov    %r13d,%eax
  57be91:	xor    $0x1,%eax
  57be94:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57be99:	mov    0x58(%rbx),%rdi
  57be9d:	call   80e910 <CCharacter::performingAttackLoose()>
  57bea2:	test   %al,%al
  57bea4:	jne    57ba2f <CGameClient::clickRight(long long, bool, bool)+0x38f>
  57beaa:	mov    0x1f8(%rbx),%rsi
  57beb1:	test   %rsi,%rsi
  57beb4:	je     57bebf <CGameClient::clickRight(long long, bool, bool)+0x81f>
  57beb6:	mov    0x58(%rbx),%rdi
  57beba:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57bebf:	mov    0x1c8(%rbx),%rsi
  57bec6:	test   %rsi,%rsi
  57bec9:	je     57ba2f <CGameClient::clickRight(long long, bool, bool)+0x38f>
  57becf:	mov    0x58(%rbx),%rdi
  57bed3:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57bed8:	jmp    57ba2f <CGameClient::clickRight(long long, bool, bool)+0x38f>
  57bedd:	mov    0x58(%rbx),%rdi
  57bee1:	mov    $0x1,%edx
  57bee6:	mov    %rbp,%rsi
  57bee9:	call   826470 <CCharacter::inSkillRange(long long, bool)>
  57beee:	test   %eax,%eax
  57bef0:	je     57ba74 <CGameClient::clickRight(long long, bool, bool)+0x3d4>
  57bef6:	mov    0x1f8(%rbx),%rsi
  57befd:	mov    0x58(%rbx),%rdi
  57bf01:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57bf06:	mov    0x58(%rbx),%rdi
  57bf0a:	mov    $0xf,%esi
  57bf0f:	mov    (%rdi),%rax
  57bf12:	call   *0x348(%rax)
  57bf18:	mov    0x58(%rbx),%rdi
  57bf1c:	mov    0x70(%rbx),%rsi
  57bf20:	mov    %rbp,%rdx
  57bf23:	xorps  %xmm0,%xmm0
  57bf26:	mov    (%rdi),%rax
  57bf29:	call   *0x3c0(%rax)
  57bf2f:	mov    0x58(%rbx),%rdi
  57bf33:	call   80e930 <CCharacter::performingSkill()>
  57bf38:	test   %al,%al
  57bf3a:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bf40:	mov    0x58(%rbx),%rdi
  57bf44:	mov    $0x1,%edx
  57bf49:	mov    %rbp,%rsi
  57bf4c:	call   826470 <CCharacter::inSkillRange(long long, bool)>
  57bf51:	test   %eax,%eax
  57bf53:	je     57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bf59:	mov    0x58(%rbx),%rdi
  57bf5d:	cmpb   $0x0,0x264(%rdi)
  57bf64:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bf6a:	jmp    57bd90 <CGameClient::clickRight(long long, bool, bool)+0x6f0>
  57bf6f:	mov    0x58(%rbx),%rdi
  57bf73:	mov    %rbp,%rsi
  57bf76:	call   827eb0 <CCharacter::castSkill(long long)>
  57bf7b:	test   %al,%al
  57bf7d:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bf83:	jmp    57bda0 <CGameClient::clickRight(long long, bool, bool)+0x700>
  57bf88:	mov    0x58(%rbx),%rdi
  57bf8c:	mov    $0x1,%edx
  57bf91:	mov    %rbp,%rsi
  57bf94:	call   826470 <CCharacter::inSkillRange(long long, bool)>
  57bf99:	test   %eax,%eax
  57bf9b:	je     57bd7b <CGameClient::clickRight(long long, bool, bool)+0x6db>
  57bfa1:	mov    0x1c8(%rbx),%rsi
  57bfa8:	mov    0x58(%rbx),%rdi
  57bfac:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57bfb1:	mov    0x58(%rbx),%rdi
  57bfb5:	mov    $0xf,%esi
  57bfba:	mov    (%rdi),%rax
  57bfbd:	call   *0x348(%rax)
  57bfc3:	mov    0x58(%rbx),%rdi
  57bfc7:	mov    0x70(%rbx),%rsi
  57bfcb:	mov    %rbp,%rdx
  57bfce:	xorps  %xmm0,%xmm0
  57bfd1:	mov    (%rdi),%rax
  57bfd4:	call   *0x3c0(%rax)
  57bfda:	mov    0x58(%rbx),%rdi
  57bfde:	call   80e930 <CCharacter::performingSkill()>
  57bfe3:	test   %al,%al
  57bfe5:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57bfeb:	mov    0x58(%rbx),%rdi
  57bfef:	mov    $0x1,%edx
  57bff4:	mov    %rbp,%rsi
  57bff7:	call   826470 <CCharacter::inSkillRange(long long, bool)>
  57bffc:	test   %eax,%eax
  57bffe:	je     57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57c004:	mov    0x58(%rbx),%rdi
  57c008:	cmpb   $0x0,0x264(%rdi)
  57c00f:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57c015:	mov    %rbp,%rsi
  57c018:	call   827eb0 <CCharacter::castSkill(long long)>
  57c01d:	test   %al,%al
  57c01f:	jne    57ba85 <CGameClient::clickRight(long long, bool, bool)+0x3e5>
  57c025:	test   %r13b,%r13b
  57c028:	jne    57b6db <CGameClient::clickRight(long long, bool, bool)+0x3b>
  57c02e:	mov    0x58(%rbx),%rdi
  57c032:	mov    $0x2,%esi
  57c037:	mov    (%rdi),%rax
  57c03a:	call   *0x348(%rax)
  57c040:	mov    $0x1,%eax
  57c045:	jmp    57b6dd <CGameClient::clickRight(long long, bool, bool)+0x3d>
  57c04a:	mov    0x58(%rbx),%rdi
  57c04e:	xor    %esi,%esi
  57c050:	mov    (%rdi),%rax
  57c053:	call   *0x348(%rax)
  57c059:	jmp    57be20 <CGameClient::clickRight(long long, bool, bool)+0x780>
