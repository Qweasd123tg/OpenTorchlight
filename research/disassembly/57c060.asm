
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000057c060 <CGameClient::processIngameInput(void*, float, bool)>:
  57c060:	push   %r15
  57c062:	xor    %eax,%eax
  57c064:	mov    %edx,%r15d
  57c067:	push   %r14
  57c069:	push   %r13
  57c06b:	mov    %rsi,%r13
  57c06e:	push   %r12
  57c070:	push   %rbp
  57c071:	push   %rbx
  57c072:	mov    %rdi,%rbx
  57c075:	sub    $0x38,%rsp
  57c079:	movss  %xmm0,0x1c(%rsp)
  57c07f:	mov    0x78(%rdi),%rdi
  57c083:	test   %rdi,%rdi
  57c086:	je     57c28f <CGameClient::processIngameInput(void*, float, bool)+0x22f>
  57c08c:	call   a83520 <CGameUI::isCinematicMenuOpen()>
  57c091:	test   %al,%al
  57c093:	je     57c2a0 <CGameClient::processIngameInput(void*, float, bool)+0x240>
  57c099:	mov    %rbx,%rdi
  57c09c:	mov    $0x1,%r12d
  57c0a2:	call   56e570 <CGameClient::getIsPaused()>
  57c0a7:	mov    0x78(%rbx),%rdi
  57c0ab:	mov    %al,0x10(%rsp)
  57c0af:	xor    %eax,%eax
  57c0b1:	test   %rdi,%rdi
  57c0b4:	je     57c0d2 <CGameClient::processIngameInput(void*, float, bool)+0x72>
  57c0b6:	movzbl %r15b,%ecx
  57c0ba:	movss  0x1c(%rsp),%xmm0
  57c0c0:	mov    %r13,%rdx
  57c0c3:	mov    %rbx,%rsi
  57c0c6:	call   ab80c0 <CGameUI::processInput(CGameClient*, void*, float, bool)>
  57c0cb:	mov    %eax,%r12d
  57c0ce:	mov    0x78(%rbx),%rax
  57c0d2:	mov    %rax,%rdi
  57c0d5:	call   a83580 <CGameUI::getUIIsInCinematic()>
  57c0da:	test   %al,%al
  57c0dc:	jne    57c3f0 <CGameClient::processIngameInput(void*, float, bool)+0x390>
  57c0e2:	test   %r12b,%r12b
  57c0e5:	lea    0xfe8(%rbx),%r14
  57c0ec:	je     57c468 <CGameClient::processIngameInput(void*, float, bool)+0x408>
  57c0f2:	mov    %r13,%rsi
  57c0f5:	mov    %r14,%rdi
  57c0f8:	call   91aec0 <CMouseManager::update(void*)>
  57c0fd:	cmpb   $0x0,0x10(%rsp)
  57c102:	je     57c300 <CGameClient::processIngameInput(void*, float, bool)+0x2a0>
  57c108:	mov    0x78(%rbx),%rax
  57c10c:	mov    0x58(%rax),%rdi
  57c110:	test   %rdi,%rdi
  57c113:	je     57c830 <CGameClient::processIngameInput(void*, float, bool)+0x7d0>
  57c119:	mov    (%rdi),%rax
  57c11c:	xor    %esi,%esi
  57c11e:	call   *0x208(%rax)
  57c124:	mov    0x1e8(%rbx),%rdi
  57c12b:	test   %rdi,%rdi
  57c12e:	je     57c14d <CGameClient::processIngameInput(void*, float, bool)+0xed>
  57c130:	mov    0x1f0(%rbx),%edx
  57c136:	lea    0x1e8(%rbx),%rsi
  57c13d:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57c142:	movq   $0x0,0x1e8(%rbx)
  57c14d:	mov    0x1d8(%rbx),%rdi
  57c154:	test   %rdi,%rdi
  57c157:	je     57c176 <CGameClient::processIngameInput(void*, float, bool)+0x116>
  57c159:	mov    0x1e0(%rbx),%edx
  57c15f:	lea    0x1d8(%rbx),%rsi
  57c166:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57c16b:	movq   $0x0,0x1d8(%rbx)
  57c176:	mov    0x78(%rbx),%rdi
  57c17a:	xor    %edx,%edx
  57c17c:	xor    %esi,%esi
  57c17e:	call   a8f390 <CGameUI::setMouseOverItem(CItem*, bool)>
  57c183:	mov    0x78(%rbx),%rbp
  57c187:	mov    0x58(%rbp),%rdi
  57c18b:	test   %rdi,%rdi
  57c18e:	je     57c1a4 <CGameClient::processIngameInput(void*, float, bool)+0x144>
  57c190:	mov    0x60(%rbp),%edx
  57c193:	lea    0x58(%rbp),%rsi
  57c197:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57c19c:	movq   $0x0,0x58(%rbp)
  57c1a4:	test   %r12b,%r12b
  57c1a7:	jne    57c328 <CGameClient::processIngameInput(void*, float, bool)+0x2c8>
  57c1ad:	mov    0x58(%rbx),%rax
  57c1b1:	test   %rax,%rax
  57c1b4:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c1b6:	cmpl   $0x21,0x330(%rax)
  57c1bd:	je     57c328 <CGameClient::processIngameInput(void*, float, bool)+0x2c8>
  57c1c3:	mov    0x2b8(%rbx),%rdi
  57c1ca:	test   %rdi,%rdi
  57c1cd:	je     57c280 <CGameClient::processIngameInput(void*, float, bool)+0x220>
  57c1d3:	call   d6f4e0 <CResourceManager::getEditorIsRunning()>
  57c1d8:	test   %al,%al
  57c1da:	jne    57c280 <CGameClient::processIngameInput(void*, float, bool)+0x220>
  57c1e0:	lea    0x2d0(%rbx),%rbp
  57c1e7:	mov    $0x11,%esi
  57c1ec:	mov    %rbp,%rdi
  57c1ef:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c1f4:	test   %al,%al
  57c1f6:	je     57c450 <CGameClient::processIngameInput(void*, float, bool)+0x3f0>
  57c1fc:	mov    $0xbb,%esi
  57c201:	mov    %rbp,%rdi
  57c204:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c209:	test   %al,%al
  57c20b:	je     57c709 <CGameClient::processIngameInput(void*, float, bool)+0x6a9>
  57c211:	movss  0x1c(%rsp),%xmm0
  57c217:	mulss  0xa2c4c9(%rip),%xmm0        # fa86e8 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x48>
  57c21f:	addss  0x38c0(%rbx),%xmm0
  57c227:	ucomiss 0xa285ca(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  57c22e:	jbe    57c748 <CGameClient::processIngameInput(void*, float, bool)+0x6e8>
  57c234:	ucomiss 0xa2c495(%rip),%xmm0        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  57c23b:	jbe    57c245 <CGameClient::processIngameInput(void*, float, bool)+0x1e5>
  57c23d:	movss  0xa2c48b(%rip),%xmm0        # fa86d0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x30>
  57c245:	movss  %xmm0,0x38c0(%rbx)
  57c24d:	mov    $0xbb,%esi
  57c252:	mov    %rbp,%rdi
  57c255:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c25a:	test   %al,%al
  57c25c:	je     57c450 <CGameClient::processIngameInput(void*, float, bool)+0x3f0>
  57c262:	mov    $0xbd,%esi
  57c267:	mov    %rbp,%rdi
  57c26a:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c26f:	test   %al,%al
  57c271:	je     57c450 <CGameClient::processIngameInput(void*, float, bool)+0x3f0>
  57c277:	nopw   0x0(%rax,%rax,1)
  57c280:	movl   $0x3f800000,0x38c0(%rbx)
  57c28a:	mov    $0x1,%eax
  57c28f:	add    $0x38,%rsp
  57c293:	pop    %rbx
  57c294:	pop    %rbp
  57c295:	pop    %r12
  57c297:	pop    %r13
  57c299:	pop    %r14
  57c29b:	pop    %r15
  57c29d:	ret
  57c29e:	xchg   %ax,%ax
  57c2a0:	mov    0x58(%rbx),%rdi
  57c2a4:	test   %rdi,%rdi
  57c2a7:	je     57c2b7 <CGameClient::processIngameInput(void*, float, bool)+0x257>
  57c2a9:	mov    (%rdi),%rax
  57c2ac:	call   *0x48(%rax)
  57c2af:	test   %al,%al
  57c2b1:	je     57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c2b7:	lea    0x2d0(%rbx),%rbp
  57c2be:	mov    $0x1b,%esi
  57c2c3:	mov    %rbp,%rdi
  57c2c6:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  57c2cb:	test   %al,%al
  57c2cd:	je     57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c2d3:	mov    0x78(%rbx),%rdi
  57c2d7:	call   a83580 <CGameUI::getUIIsInCinematic()>
  57c2dc:	test   %al,%al
  57c2de:	jne    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c2e4:	mov    0x78(%rbx),%rdi
  57c2e8:	cmpb   $0x0,0x1999(%rdi)
  57c2ef:	je     57c756 <CGameClient::processIngameInput(void*, float, bool)+0x6f6>
  57c2f5:	call   a8e2d0 <CGameUI::togglePause()>
  57c2fa:	jmp    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c2ff:	nop
  57c300:	mov    0x58(%rbx),%rdi
  57c304:	test   %rdi,%rdi
  57c307:	je     57c1a4 <CGameClient::processIngameInput(void*, float, bool)+0x144>
  57c30d:	mov    (%rdi),%rax
  57c310:	call   *0x48(%rax)
  57c313:	test   %al,%al
  57c315:	jne    57c1a4 <CGameClient::processIngameInput(void*, float, bool)+0x144>
  57c31b:	nopl   0x0(%rax,%rax,1)
  57c320:	jmp    57c108 <CGameClient::processIngameInput(void*, float, bool)+0xa8>
  57c325:	nopl   (%rax)
  57c328:	mov    0x20(%rbx),%rdi
  57c32c:	test   %rdi,%rdi
  57c32f:	je     57c35c <CGameClient::processIngameInput(void*, float, bool)+0x2fc>
  57c331:	lea    0x2d0(%rbx),%rbp
  57c338:	mov    0x50(%rbx),%rdx
  57c33c:	movzbl %r15b,%r9d
  57c340:	movss  0x1c(%rsp),%xmm0
  57c346:	mov    %r14,%r8
  57c349:	mov    %rbp,%rcx
  57c34c:	mov    %r13,%rsi
  57c34f:	call   ceb230 <CCameraControl::processInput(void*, CSettings*, CKeyManager*, CMouseManager*, float, bool)>
  57c354:	test   %al,%al
  57c356:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c35c:	test   %r12b,%r12b
  57c35f:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c365:	mov    0x78(%rbx),%rdi
  57c369:	test   %rdi,%rdi
  57c36c:	je     57c37b <CGameClient::processIngameInput(void*, float, bool)+0x31b>
  57c36e:	call   a829f0 <CGameUI::modalDialogOpen()>
  57c373:	test   %al,%al
  57c375:	jne    57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c37b:	test   %r15b,%r15b
  57c37e:	xchg   %ax,%ax
  57c380:	jne    57c4b0 <CGameClient::processIngameInput(void*, float, bool)+0x450>
  57c386:	cs nopw 0x0(%rax,%rax,1)
  57c390:	mov    0x1d8(%rbx),%rdi
  57c397:	test   %rdi,%rdi
  57c39a:	je     57c3b9 <CGameClient::processIngameInput(void*, float, bool)+0x359>
  57c39c:	mov    0x1e0(%rbx),%edx
  57c3a2:	lea    0x1d8(%rbx),%rsi
  57c3a9:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57c3ae:	movq   $0x0,0x1d8(%rbx)
  57c3b9:	mov    0x1e8(%rbx),%rdi
  57c3c0:	test   %rdi,%rdi
  57c3c3:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c3c9:	mov    0x1f0(%rbx),%edx
  57c3cf:	lea    0x1e8(%rbx),%rsi
  57c3d6:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  57c3db:	movq   $0x0,0x1e8(%rbx)
  57c3e6:	jmp    57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c3eb:	nopl   0x0(%rax,%rax,1)
  57c3f0:	lea    0xfe8(%rbx),%rdi
  57c3f7:	call   91ae70 <CMouseManager::flushAll()>
  57c3fc:	mov    0x58(%rbx),%rdi
  57c400:	movb   $0x0,0x99(%rbx)
  57c407:	movb   $0x0,0x9a(%rbx)
  57c40e:	movb   $0x1,0x98(%rbx)
  57c415:	test   %rdi,%rdi
  57c418:	je     57c450 <CGameClient::processIngameInput(void*, float, bool)+0x3f0>
  57c41a:	call   80e930 <CCharacter::performingSkill()>
  57c41f:	test   %al,%al
  57c421:	je     57c440 <CGameClient::processIngameInput(void*, float, bool)+0x3e0>
  57c423:	mov    0x58(%rbx),%rdi
  57c427:	mov    $0x2,%esi
  57c42c:	mov    (%rdi),%rax
  57c42f:	call   *0x348(%rax)
  57c435:	mov    $0x1,%eax
  57c43a:	jmp    57c28f <CGameClient::processIngameInput(void*, float, bool)+0x22f>
  57c43f:	nop
  57c440:	mov    0x58(%rbx),%rdi
  57c444:	call   80e8f0 <CCharacter::performingAttack()>
  57c449:	test   %al,%al
  57c44b:	jne    57c423 <CGameClient::processIngameInput(void*, float, bool)+0x3c3>
  57c44d:	nopl   (%rax)
  57c450:	add    $0x38,%rsp
  57c454:	mov    $0x1,%eax
  57c459:	pop    %rbx
  57c45a:	pop    %rbp
  57c45b:	pop    %r12
  57c45d:	pop    %r13
  57c45f:	pop    %r14
  57c461:	pop    %r15
  57c463:	ret
  57c464:	nopl   0x0(%rax)
  57c468:	xor    %esi,%esi
  57c46a:	mov    %r14,%rdi
  57c46d:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c472:	test   %al,%al
  57c474:	je     57c47d <CGameClient::processIngameInput(void*, float, bool)+0x41d>
  57c476:	movb   $0x1,0x99(%rbx)
  57c47d:	mov    $0x1,%esi
  57c482:	mov    %r14,%rdi
  57c485:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c48a:	test   %al,%al
  57c48c:	je     57c495 <CGameClient::processIngameInput(void*, float, bool)+0x435>
  57c48e:	movb   $0x1,0x9a(%rbx)
  57c495:	movb   $0x1,0x98(%rbx)
  57c49c:	mov    %r14,%rdi
  57c49f:	call   91ae70 <CMouseManager::flushAll()>
  57c4a4:	jmp    57c0f2 <CGameClient::processIngameInput(void*, float, bool)+0x92>
  57c4a9:	nopl   0x0(%rax)
  57c4b0:	mov    0x58(%rbx),%rdi
  57c4b4:	test   %rdi,%rdi
  57c4b7:	je     57c390 <CGameClient::processIngameInput(void*, float, bool)+0x330>
  57c4bd:	call   80e850 <CCharacter::alive()>
  57c4c2:	test   %al,%al
  57c4c4:	je     57c390 <CGameClient::processIngameInput(void*, float, bool)+0x330>
  57c4ca:	mov    0x58(%rbx),%rdi
  57c4ce:	mov    (%rdi),%rax
  57c4d1:	call   *0x48(%rax)
  57c4d4:	test   %al,%al
  57c4d6:	je     57c390 <CGameClient::processIngameInput(void*, float, bool)+0x330>
  57c4dc:	mov    %rbx,%rdi
  57c4df:	call   57b0b0 <CGameClient::mouseOverCharacter()>
  57c4e4:	movss  0x80(%rbx),%xmm0
  57c4ec:	ucomiss 0xa28305(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  57c4f3:	jbe    57c503 <CGameClient::processIngameInput(void*, float, bool)+0x4a3>
  57c4f5:	subss  0x1c(%rsp),%xmm0
  57c4fb:	movss  %xmm0,0x80(%rbx)
  57c503:	cmpq   $0x0,0x58(%rbx)
  57c508:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c50e:	cmpb   $0x0,0x10(%rsp)
  57c513:	lea    0x2d0(%rbx),%rbp
  57c51a:	je     57c908 <CGameClient::processIngameInput(void*, float, bool)+0x8a8>
  57c520:	xor    %esi,%esi
  57c522:	mov    %r14,%rdi
  57c525:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  57c52a:	test   %al,%al
  57c52c:	je     57c860 <CGameClient::processIngameInput(void*, float, bool)+0x800>
  57c532:	cmpb   $0x0,0x99(%rbx)
  57c539:	jne    57c553 <CGameClient::processIngameInput(void*, float, bool)+0x4f3>
  57c53b:	mov    0x58(%rbx),%rax
  57c53f:	movl   $0x0,0x80(%rbx)
  57c549:	movl   $0x41200000,0x278(%rax)
  57c553:	mov    0x58(%rbx),%r8
  57c557:	lea    0x1c8(%rbx),%r12
  57c55e:	lea    0x1f8(%rbx),%r13
  57c565:	movq   $0x1428660,0x10(%rsp)
  57c56e:	xor    %r15d,%r15d
  57c571:	jmp    57c620 <CGameClient::processIngameInput(void*, float, bool)+0x5c0>
  57c576:	cs nopw 0x0(%rax,%rax,1)
  57c580:	mov    0x1c8(%r8),%rdi
  57c587:	mov    %rdx,0x8(%rsp)
  57c58c:	mov    %rcx,(%rsp)
  57c590:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57c595:	test   %rax,%rax
  57c598:	mov    0x8(%rsp),%rdx
  57c59d:	mov    (%rsp),%rcx
  57c5a1:	je     57c770 <CGameClient::processIngameInput(void*, float, bool)+0x710>
  57c5a7:	mov    0x10(%rsp),%rax
  57c5ac:	mov    0x50(%rbx),%rdi
  57c5b0:	mov    (%rax),%esi
  57c5b2:	mov    %rdx,0x8(%rsp)
  57c5b7:	mov    %rcx,(%rsp)
  57c5bb:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57c5c0:	mov    %rbp,%rdi
  57c5c3:	mov    %eax,%esi
  57c5c5:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c5ca:	test   %al,%al
  57c5cc:	mov    0x8(%rsp),%rdx
  57c5d1:	jne    57ca10 <CGameClient::processIngameInput(void*, float, bool)+0x9b0>
  57c5d7:	mov    0x10(%rsp),%rdx
  57c5dc:	mov    0x50(%rbx),%rdi
  57c5e0:	mov    (%rdx),%esi
  57c5e2:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57c5e7:	mov    %rbp,%rdi
  57c5ea:	mov    %eax,%esi
  57c5ec:	call   91a6a0 <CKeyManager::keyReleased(unsigned int)>
  57c5f1:	test   %al,%al
  57c5f3:	je     57c608 <CGameClient::processIngameInput(void*, float, bool)+0x5a8>
  57c5f5:	cmpb   $0x0,0x9a(%rbx)
  57c5fc:	je     57c7a0 <CGameClient::processIngameInput(void*, float, bool)+0x740>
  57c602:	nopw   0x0(%rax,%rax,1)
  57c608:	add    $0x1,%r15d
  57c60c:	addq   $0x4,0x10(%rsp)
  57c612:	cmp    $0xa,%r15d
  57c616:	je     57c7c0 <CGameClient::processIngameInput(void*, float, bool)+0x760>
  57c61c:	mov    0x58(%rbx),%r8
  57c620:	mov    %r15d,%edx
  57c623:	lea    0x116(%rdx),%rcx
  57c62a:	mov    (%r8,%rcx,8),%rsi
  57c62e:	cmp    $0xffffffffffffffff,%rsi
  57c632:	jne    57c580 <CGameClient::processIngameInput(void*, float, bool)+0x520>
  57c638:	cmpq   $0xffffffffffffffff,0x900(%r8,%rdx,8)
  57c641:	je     57c608 <CGameClient::processIngameInput(void*, float, bool)+0x5a8>
  57c643:	mov    0x10(%rsp),%rax
  57c648:	mov    0x50(%rbx),%rdi
  57c64c:	mov    (%rax),%esi
  57c64e:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57c653:	mov    %rbp,%rdi
  57c656:	mov    %eax,%esi
  57c658:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  57c65d:	test   %al,%al
  57c65f:	je     57c608 <CGameClient::processIngameInput(void*, float, bool)+0x5a8>
  57c661:	mov    0x78(%rbx),%rdi
  57c665:	mov    $0x1,%edx
  57c66a:	mov    %r15d,%esi
  57c66d:	call   a83cf0 <CGameUI::activateItemSlot(int, bool)>
  57c672:	xor    %esi,%esi
  57c674:	mov    %r14,%rdi
  57c677:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c67c:	test   %al,%al
  57c67e:	jne    57c8a0 <CGameClient::processIngameInput(void*, float, bool)+0x840>
  57c684:	cmpb   $0x0,0x98(%rbx)
  57c68b:	je     57c694 <CGameClient::processIngameInput(void*, float, bool)+0x634>
  57c68d:	movb   $0x0,0x98(%rbx)
  57c694:	cmpb   $0x0,0x99(%rbx)
  57c69b:	jne    57c940 <CGameClient::processIngameInput(void*, float, bool)+0x8e0>
  57c6a1:	movb   $0x0,0x99(%rbx)
  57c6a8:	mov    0x1c8(%rbx),%rdi
  57c6af:	test   %rdi,%rdi
  57c6b2:	je     57c6d2 <CGameClient::processIngameInput(void*, float, bool)+0x672>
  57c6b4:	call   80e850 <CCharacter::alive()>
  57c6b9:	test   %al,%al
  57c6bb:	jne    57c6d2 <CGameClient::processIngameInput(void*, float, bool)+0x672>
  57c6bd:	xor    %esi,%esi
  57c6bf:	mov    %r12,%rdi
  57c6c2:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57c6c7:	mov    0x58(%rbx),%rdi
  57c6cb:	xor    %esi,%esi
  57c6cd:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57c6d2:	mov    0x1f8(%rbx),%rax
  57c6d9:	test   %rax,%rax
  57c6dc:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c6e2:	cmpb   $0x0,0x1f0(%rax)
  57c6e9:	jne    57c7f0 <CGameClient::processIngameInput(void*, float, bool)+0x790>
  57c6ef:	xor    %esi,%esi
  57c6f1:	mov    %r13,%rdi
  57c6f4:	call   591b80 <TSafePointer<CItem>::setObject(CItem*)>
  57c6f9:	mov    0x58(%rbx),%rdi
  57c6fd:	xor    %esi,%esi
  57c6ff:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57c704:	jmp    57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c709:	mov    $0xbd,%esi
  57c70e:	mov    %rbp,%rdi
  57c711:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c716:	test   %al,%al
  57c718:	je     57c24d <CGameClient::processIngameInput(void*, float, bool)+0x1ed>
  57c71e:	movss  0x1c(%rsp),%xmm0
  57c724:	mulss  0xa2bfc0(%rip),%xmm0        # fa86ec <vtable for Ogre::SharedPtr<Ogre::Texture>+0x4c>
  57c72c:	addss  0x38c0(%rbx),%xmm0
  57c734:	ucomiss 0xa280bd(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  57c73b:	ja     57c234 <CGameClient::processIngameInput(void*, float, bool)+0x1d4>
  57c741:	nopl   0x0(%rax)
  57c748:	jp     57c234 <CGameClient::processIngameInput(void*, float, bool)+0x1d4>
  57c74e:	xorps  %xmm0,%xmm0
  57c751:	jmp    57c245 <CGameClient::processIngameInput(void*, float, bool)+0x1e5>
  57c756:	call   a84140 <CGameUI::getConsoleIsOpen()>
  57c75b:	test   %al,%al
  57c75d:	nopl   (%rax)
  57c760:	je     57c780 <CGameClient::processIngameInput(void*, float, bool)+0x720>
  57c762:	mov    0x78(%rbx),%rdi
  57c766:	call   a8e560 <CGameUI::toggleConsole()>
  57c76b:	jmp    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c770:	mov    0x58(%rbx),%r8
  57c774:	jmp    57c638 <CGameClient::processIngameInput(void*, float, bool)+0x5d8>
  57c779:	nopl   0x0(%rax)
  57c780:	mov    0x78(%rbx),%rdi
  57c784:	call   a82c00 <CGameUI::eitherCoveredPartial()>
  57c789:	test   %al,%al
  57c78b:	je     57c808 <CGameClient::processIngameInput(void*, float, bool)+0x7a8>
  57c78d:	mov    0x78(%rbx),%rdi
  57c791:	call   a8e0d0 <CGameUI::closeAll()>
  57c796:	jmp    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c79b:	nopl   0x0(%rax,%rax,1)
  57c7a0:	xor    %esi,%esi
  57c7a2:	mov    %r12,%rdi
  57c7a5:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57c7aa:	xor    %esi,%esi
  57c7ac:	mov    %r13,%rdi
  57c7af:	call   591b80 <TSafePointer<CItem>::setObject(CItem*)>
  57c7b4:	jmp    57c608 <CGameClient::processIngameInput(void*, float, bool)+0x5a8>
  57c7b9:	nopl   0x0(%rax)
  57c7c0:	mov    $0x1,%esi
  57c7c5:	mov    %r14,%rdi
  57c7c8:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c7cd:	test   %al,%al
  57c7cf:	jne    57ca54 <CGameClient::processIngameInput(void*, float, bool)+0x9f4>
  57c7d5:	cmpb   $0x0,0x9a(%rbx)
  57c7dc:	jne    57caad <CGameClient::processIngameInput(void*, float, bool)+0xa4d>
  57c7e2:	movb   $0x0,0x9a(%rbx)
  57c7e9:	jmp    57c672 <CGameClient::processIngameInput(void*, float, bool)+0x612>
  57c7ee:	xchg   %ax,%ax
  57c7f0:	cmpb   $0x0,0x1f1(%rax)
  57c7f7:	je     57c1c3 <CGameClient::processIngameInput(void*, float, bool)+0x163>
  57c7fd:	jmp    57c6ef <CGameClient::processIngameInput(void*, float, bool)+0x68f>
  57c802:	nopw   0x0(%rax,%rax,1)
  57c808:	mov    0x78(%rbx),%rdi
  57c80c:	call   a82950 <CGameUI::getDieMenuIsOpen()>
  57c811:	test   %al,%al
  57c813:	jne    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c819:	mov    0x78(%rbx),%rdi
  57c81d:	call   a8e0d0 <CGameUI::closeAll()>
  57c822:	mov    0x78(%rbx),%rdi
  57c826:	call   a8eb90 <CGameUI::toggleOptions()>
  57c82b:	jmp    57c099 <CGameClient::processIngameInput(void*, float, bool)+0x39>
  57c830:	mov    %rax,%rdi
  57c833:	call   a832f0 <CGameUI::getMouseOverItem()>
  57c838:	test   %rax,%rax
  57c83b:	je     57c124 <CGameClient::processIngameInput(void*, float, bool)+0xc4>
  57c841:	mov    0x78(%rbx),%rdi
  57c845:	call   a832f0 <CGameUI::getMouseOverItem()>
  57c84a:	mov    (%rax),%rdx
  57c84d:	xor    %esi,%esi
  57c84f:	mov    %rax,%rdi
  57c852:	call   *0x208(%rdx)
  57c858:	jmp    57c124 <CGameClient::processIngameInput(void*, float, bool)+0xc4>
  57c85d:	nopl   (%rax)
  57c860:	mov    $0x1,%esi
  57c865:	mov    %r14,%rdi
  57c868:	call   91ad20 <CMouseManager::buttonPressed(EMouseButton)>
  57c86d:	test   %al,%al
  57c86f:	jne    57c532 <CGameClient::processIngameInput(void*, float, bool)+0x4d2>
  57c875:	mov    0x58(%rbx),%rdi
  57c879:	cmpq   $0x0,0x398(%rdi)
  57c881:	je     57c894 <CGameClient::processIngameInput(void*, float, bool)+0x834>
  57c883:	call   80e930 <CCharacter::performingSkill()>
  57c888:	test   %al,%al
  57c88a:	jne    57c959 <CGameClient::processIngameInput(void*, float, bool)+0x8f9>
  57c890:	mov    0x58(%rbx),%rdi
  57c894:	mov    %rdi,%r8
  57c897:	jmp    57c557 <CGameClient::processIngameInput(void*, float, bool)+0x4f7>
  57c89c:	nopl   0x0(%rax)
  57c8a0:	mov    $0x1,%esi
  57c8a5:	mov    %r14,%rdi
  57c8a8:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c8ad:	test   %al,%al
  57c8af:	jne    57c8f9 <CGameClient::processIngameInput(void*, float, bool)+0x899>
  57c8b1:	mov    0x58(%rbx),%rax
  57c8b5:	mov    0x3c0(%rax),%rsi
  57c8bc:	cmp    $0xffffffffffffffff,%rsi
  57c8c0:	je     57c8f1 <CGameClient::processIngameInput(void*, float, bool)+0x891>
  57c8c2:	mov    0x1c8(%rax),%rdi
  57c8c9:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57c8ce:	test   %rax,%rax
  57c8d1:	mov    %rax,%r14
  57c8d4:	je     57c8f1 <CGameClient::processIngameInput(void*, float, bool)+0x891>
  57c8d6:	mov    0x58(%rbx),%rax
  57c8da:	mov    %r14,%rsi
  57c8dd:	mov    0x1c8(%rax),%rdi
  57c8e4:	call   cca8c0 <CSkillManager::getSkillIsCooling(CSkill*)>
  57c8e9:	test   %al,%al
  57c8eb:	je     57caff <CGameClient::processIngameInput(void*, float, bool)+0xa9f>
  57c8f1:	mov    %rbx,%rdi
  57c8f4:	call   57a9f0 <CGameClient::clickLeft()>
  57c8f9:	movb   $0x1,0x99(%rbx)
  57c900:	jmp    57c6a8 <CGameClient::processIngameInput(void*, float, bool)+0x648>
  57c905:	nopl   (%rax)
  57c908:	mov    0x50(%rbx),%rdi
  57c90c:	mov    0xf8ed0e(%rip),%esi        # 150b620 <KSETTINGS_KEYMAP_HOLDPOS>
  57c912:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57c917:	mov    %rbp,%rdi
  57c91a:	mov    %eax,%esi
  57c91c:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c921:	test   %al,%al
  57c923:	jne    57ca76 <CGameClient::processIngameInput(void*, float, bool)+0xa16>
  57c929:	mov    0x58(%rbx),%rax
  57c92d:	movb   $0x0,0x266(%rax)
  57c934:	jmp    57c520 <CGameClient::processIngameInput(void*, float, bool)+0x4c0>
  57c939:	nopl   0x0(%rax)
  57c940:	xor    %esi,%esi
  57c942:	mov    %r12,%rdi
  57c945:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57c94a:	xor    %esi,%esi
  57c94c:	mov    %r13,%rdi
  57c94f:	call   591b80 <TSafePointer<CItem>::setObject(CItem*)>
  57c954:	jmp    57c6a1 <CGameClient::processIngameInput(void*, float, bool)+0x641>
  57c959:	mov    $0x1,%esi
  57c95e:	mov    %r14,%rdi
  57c961:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  57c966:	test   %al,%al
  57c968:	je     57ca4b <CGameClient::processIngameInput(void*, float, bool)+0x9eb>
  57c96e:	mov    0x58(%rbx),%rdi
  57c972:	mov    0x398(%rdi),%rax
  57c979:	mov    0x3b0(%rdi),%rdx
  57c980:	cmp    %rdx,0x150(%rax)
  57c987:	je     57cba2 <CGameClient::processIngameInput(void*, float, bool)+0xb42>
  57c98d:	movb   $0x1,0x10(%rsp)
  57c992:	mov    $0x1428660,%r13d
  57c998:	xor    %r12d,%r12d
  57c99b:	nopl   0x0(%rax,%rax,1)
  57c9a0:	mov    %r12d,%r15d
  57c9a3:	add    $0x116,%r15
  57c9aa:	cmpq   $0xffffffffffffffff,(%rdi,%r15,8)
  57c9af:	je     57c9d4 <CGameClient::processIngameInput(void*, float, bool)+0x974>
  57c9b1:	mov    0x50(%rbx),%rdi
  57c9b5:	mov    0x0(%r13),%esi
  57c9b9:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57c9be:	mov    %rbp,%rdi
  57c9c1:	mov    %eax,%esi
  57c9c3:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57c9c8:	test   %al,%al
  57c9ca:	jne    57cac6 <CGameClient::processIngameInput(void*, float, bool)+0xa66>
  57c9d0:	mov    0x58(%rbx),%rdi
  57c9d4:	add    $0x1,%r12d
  57c9d8:	add    $0x4,%r13
  57c9dc:	cmp    $0xa,%r12d
  57c9e0:	jne    57c9a0 <CGameClient::processIngameInput(void*, float, bool)+0x940>
  57c9e2:	cmpb   $0x0,0x10(%rsp)
  57c9e7:	mov    %rdi,%r8
  57c9ea:	je     57c557 <CGameClient::processIngameInput(void*, float, bool)+0x4f7>
  57c9f0:	movzbl 0x99(%rbx),%eax
  57c9f7:	xor    $0x1,%eax
  57c9fa:	movzbl %al,%esi
  57c9fd:	call   8f0bd0 <CPlayer::attemptToStopPlayerSkill(bool)>
  57ca02:	mov    0x58(%rbx),%r8
  57ca06:	jmp    57c557 <CGameClient::processIngameInput(void*, float, bool)+0x4f7>
  57ca0b:	nopl   0x0(%rax,%rax,1)
  57ca10:	mov    0x1428660(,%rdx,4),%esi
  57ca17:	mov    0x50(%rbx),%rdi
  57ca1b:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57ca20:	mov    %rbp,%rdi
  57ca23:	mov    %eax,%esi
  57ca25:	call   91a670 <CKeyManager::keyPressed(unsigned int)>
  57ca2a:	xor    $0x1,%eax
  57ca2d:	mov    (%rsp),%rcx
  57ca31:	mov    %rbx,%rdi
  57ca34:	movzbl %al,%edx
  57ca37:	mov    0x58(%rbx),%rax
  57ca3b:	mov    (%rax,%rcx,8),%rsi
  57ca3f:	xor    %ecx,%ecx
  57ca41:	call   57b6a0 <CGameClient::clickRight(long long, bool, bool)>
  57ca46:	jmp    57c672 <CGameClient::processIngameInput(void*, float, bool)+0x612>
  57ca4b:	mov    0x58(%rbx),%rdi
  57ca4f:	jmp    57c98d <CGameClient::processIngameInput(void*, float, bool)+0x92d>
  57ca54:	movzbl 0x9a(%rbx),%edx
  57ca5b:	xor    %ecx,%ecx
  57ca5d:	mov    $0xffffffff,%esi
  57ca62:	mov    %rbx,%rdi
  57ca65:	call   57b6a0 <CGameClient::clickRight(long long, bool, bool)>
  57ca6a:	movb   $0x1,0x9a(%rbx)
  57ca71:	jmp    57c672 <CGameClient::processIngameInput(void*, float, bool)+0x612>
  57ca76:	mov    0x58(%rbx),%rax
  57ca7a:	lea    0x20(%rsp),%rsi
  57ca7f:	mov    %rbx,%rdi
  57ca82:	mov    $0x1,%edx
  57ca87:	movb   $0x1,0x266(%rax)
  57ca8e:	call   579e90 <CGameClient::findWorldLocation(Ogre::Vector3&, bool)>
  57ca93:	mov    0x58(%rbx),%rdi
  57ca97:	movss  0x28(%rsp),%xmm1
  57ca9d:	movss  0x20(%rsp),%xmm0
  57caa3:	call   827230 <CCharacter::setTargetDirection(float, float)>
  57caa8:	jmp    57c520 <CGameClient::processIngameInput(void*, float, bool)+0x4c0>
  57caad:	xor    %esi,%esi
  57caaf:	mov    %r12,%rdi
  57cab2:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57cab7:	xor    %esi,%esi
  57cab9:	mov    %r13,%rdi
  57cabc:	call   591b80 <TSafePointer<CItem>::setObject(CItem*)>
  57cac1:	jmp    57c7e2 <CGameClient::processIngameInput(void*, float, bool)+0x782>
  57cac6:	mov    0x58(%rbx),%rdi
  57caca:	mov    0x1c8(%rdi),%rax
  57cad1:	mov    (%rdi,%r15,8),%rsi
  57cad5:	test   %rax,%rax
  57cad8:	je     57c9e2 <CGameClient::processIngameInput(void*, float, bool)+0x982>
  57cade:	mov    %rax,%rdi
  57cae1:	call   cca620 <CSkillManager::getSkillByGuid(long long)>
  57cae6:	mov    0x58(%rbx),%rdi
  57caea:	cmp    0x398(%rdi),%rax
  57caf1:	mov    %rdi,%r8
  57caf4:	jne    57c9e2 <CGameClient::processIngameInput(void*, float, bool)+0x982>
  57cafa:	jmp    57c557 <CGameClient::processIngameInput(void*, float, bool)+0x4f7>
  57caff:	mov    0x58(%rbx),%rdi
  57cb03:	call   80f7c0 <CCharacter::mana()>
  57cb08:	mov    %r14,%rdi
  57cb0b:	mov    %eax,%r15d
  57cb0e:	call   c9cd90 <CSkill::getManaCost()>
  57cb13:	cmp    %eax,%r15d
  57cb16:	jl     57c8f1 <CGameClient::processIngameInput(void*, float, bool)+0x891>
  57cb1c:	mov    0x58(%rbx),%rdi
  57cb20:	call   80f7c0 <CCharacter::mana()>
  57cb25:	mov    %r14,%rdi
  57cb28:	mov    %eax,%r15d
  57cb2b:	call   c9cdf0 <CSkill::getManaCostOT()>
  57cb30:	cmp    %eax,%r15d
  57cb33:	jl     57c8f1 <CGameClient::processIngameInput(void*, float, bool)+0x891>
  57cb39:	mov    0x50(%rbx),%rdi
  57cb3d:	mov    0xf8eadd(%rip),%esi        # 150b620 <KSETTINGS_KEYMAP_HOLDPOS>
  57cb43:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57cb48:	mov    %rbp,%rdi
  57cb4b:	mov    %eax,%esi
  57cb4d:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57cb52:	test   %al,%al
  57cb54:	je     57cb70 <CGameClient::processIngameInput(void*, float, bool)+0xb10>
  57cb56:	mov    0x1f8(%rbx),%rdi
  57cb5d:	test   %rdi,%rdi
  57cb60:	je     57cb9c <CGameClient::processIngameInput(void*, float, bool)+0xb3c>
  57cb62:	mov    $0x1f,%esi
  57cb67:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  57cb6c:	test   %al,%al
  57cb6e:	je     57cb9c <CGameClient::processIngameInput(void*, float, bool)+0xb3c>
  57cb70:	mov    $0x1,%ecx
  57cb75:	mov    0x58(%rbx),%rax
  57cb79:	movzbl 0x99(%rbx),%edx
  57cb80:	mov    %rbx,%rdi
  57cb83:	mov    0x3c0(%rax),%rsi
  57cb8a:	call   57b6a0 <CGameClient::clickRight(long long, bool, bool)>
  57cb8f:	test   %al,%al
  57cb91:	jne    57c8f9 <CGameClient::processIngameInput(void*, float, bool)+0x899>
  57cb97:	jmp    57c8f1 <CGameClient::processIngameInput(void*, float, bool)+0x891>
  57cb9c:	xor    %ecx,%ecx
  57cb9e:	xchg   %ax,%ax
  57cba0:	jmp    57cb75 <CGameClient::processIngameInput(void*, float, bool)+0xb15>
  57cba2:	movb   $0x0,0x10(%rsp)
  57cba7:	jmp    57c992 <CGameClient::processIngameInput(void*, float, bool)+0x932>
