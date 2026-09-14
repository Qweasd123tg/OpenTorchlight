
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000825310 <CCharacter::setTarget(CCharacter*)>:
  825310:	mov    %rbx,-0x20(%rsp)
  825315:	mov    %rbp,-0x18(%rsp)
  82531a:	mov    %rdi,%rbx
  82531d:	mov    %r12,-0x10(%rsp)
  825322:	mov    %r13,-0x8(%rsp)
  825327:	sub    $0x28,%rsp
  82532b:	cmpl   $0x6,0x330(%rdi)
  825332:	mov    %rsi,%rbp
  825335:	je     825430 <CCharacter::setTarget(CCharacter*)+0x120>
  82533b:	cmpb   $0x0,0x70c(%rdi)
  825342:	jne    825460 <CCharacter::setTarget(CCharacter*)+0x150>
  825348:	mov    0x340(%rdi),%r12
  82534f:	test   %r12,%r12
  825352:	je     8254a0 <CCharacter::setTarget(CCharacter*)+0x190>
  825358:	mov    0x718(%rdi),%rdi
  82535f:	test   %rdi,%rdi
  825362:	je     8254a0 <CCharacter::setTarget(CCharacter*)+0x190>
  825368:	mov    $0x5,%esi
  82536d:	call   d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>
  825372:	test   %al,%al
  825374:	jne    825480 <CCharacter::setTarget(CCharacter*)+0x170>
  82537a:	mov    0x340(%rbx),%rdi
  825381:	cmp    %rdi,%rbp
  825384:	je     8253c8 <CCharacter::setTarget(CCharacter*)+0xb8>
  825386:	test   %rdi,%rdi
  825389:	lea    0x340(%rbx),%r13
  825390:	je     8253a0 <CCharacter::setTarget(CCharacter*)+0x90>
  825392:	mov    0x348(%rbx),%edx
  825398:	mov    %r13,%rsi
  82539b:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  8253a0:	test   %rbp,%rbp
  8253a3:	movq   $0x0,0x340(%rbx)
  8253ae:	je     8253c1 <CCharacter::setTarget(CCharacter*)+0xb1>
  8253b0:	mov    %r13,%rsi
  8253b3:	mov    %rbp,%rdi
  8253b6:	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  8253bb:	mov    %eax,0x348(%rbx)
  8253c1:	mov    %rbp,0x340(%rbx)
  8253c8:	mov    0x350(%rbx),%rdi
  8253cf:	test   %rdi,%rdi
  8253d2:	je     8253f1 <CCharacter::setTarget(CCharacter*)+0xe1>
  8253d4:	mov    0x358(%rbx),%edx
  8253da:	lea    0x350(%rbx),%rsi
  8253e1:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  8253e6:	movq   $0x0,0x350(%rbx)
  8253f1:	cmpb   $0x0,0x1d0(%rbx)
  8253f8:	je     825460 <CCharacter::setTarget(CCharacter*)+0x150>
  8253fa:	cmp    %r12,%rbp
  8253fd:	je     825460 <CCharacter::setTarget(CCharacter*)+0x150>
  8253ff:	test   %rbp,%rbp
  825402:	je     825460 <CCharacter::setTarget(CCharacter*)+0x150>
  825404:	mov    %rbp,%rdi
  825407:	call   85acb0 <CBaseUnit::isPlayer()>
  82540c:	test   %al,%al
  82540e:	je     825460 <CCharacter::setTarget(CCharacter*)+0x150>
  825410:	mov    %rbx,%rdi
  825413:	mov    0x10(%rsp),%rbp
  825418:	mov    0x8(%rsp),%rbx
  82541d:	mov    0x18(%rsp),%r12
  825422:	mov    0x20(%rsp),%r13
  825427:	add    $0x28,%rsp
  82542b:	jmp    7f6970 <CBaseUnit::broadcastAlerted()>
  825430:	test   %rsi,%rsi
  825433:	jne    825460 <CCharacter::setTarget(CCharacter*)+0x150>
  825435:	mov    0x340(%rdi),%rdi
  82543c:	test   %rdi,%rdi
  82543f:	je     825460 <CCharacter::setTarget(CCharacter*)+0x150>
  825441:	mov    0x348(%rbx),%edx
  825447:	lea    0x340(%rbx),%rsi
  82544e:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  825453:	movq   $0x0,0x340(%rbx)
  82545e:	xchg   %ax,%ax
  825460:	mov    0x8(%rsp),%rbx
  825465:	mov    0x10(%rsp),%rbp
  82546a:	mov    0x18(%rsp),%r12
  82546f:	mov    0x20(%rsp),%r13
  825474:	add    $0x28,%rsp
  825478:	ret
  825479:	nopl   0x0(%rax)
  825480:	mov    0x340(%rbx),%rdi
  825487:	mov    0x330(%rdi),%eax
  82548d:	cmp    $0x5,%eax
  825490:	je     825381 <CCharacter::setTarget(CCharacter*)+0x71>
  825496:	cmp    $0x6,%eax
  825499:	jne    825460 <CCharacter::setTarget(CCharacter*)+0x150>
  82549b:	jmp    825381 <CCharacter::setTarget(CCharacter*)+0x71>
  8254a0:	mov    %r12,%rdi
  8254a3:	jmp    825381 <CCharacter::setTarget(CCharacter*)+0x71>
