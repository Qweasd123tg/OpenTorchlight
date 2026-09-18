
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b4f1b0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE>:
  b4f1b0:	push   %r15
  b4f1b2:	push   %r14
  b4f1b4:	push   %r13
  b4f1b6:	push   %r12
  b4f1b8:	push   %rbp
  b4f1b9:	mov    %rdi,%rbp
  b4f1bc:	push   %rbx
  b4f1bd:	mov    %rsi,%rbx
  b4f1c0:	sub    $0x238,%rsp
  b4f1c7:	mov    0x78(%rsi),%rax
  b4f1cb:	mov    0x80(%rsi),%r14
  b4f1d2:	sub    %rax,%r14
  b4f1d5:	shr    $0x3,%r14
  b4f1d9:	test   %r14d,%r14d
  b4f1dc:	jle    b4f20d <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x5d>
  b4f1de:	xor    %r13d,%r13d
  b4f1e1:	xor    %r12d,%r12d
  b4f1e4:	jmp    b4f1f4 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x44>
  b4f1e6:	cs nopw 0x0(%rax,%rax,1)
  b4f1f0:	mov    0x78(%rbx),%rax
  b4f1f4:	mov    (%rax,%r13,1),%rsi
  b4f1f8:	mov    %rbp,%rdi
  b4f1fb:	add    $0x1,%r12d
  b4f1ff:	add    $0x8,%r13
  b4f203:	call   b4f1b0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE>
  b4f208:	cmp    %r12d,%r14d
  b4f20b:	jg     b4f1f0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x40>
  b4f20d:	lea    0x160(%rsp),%r12
  b4f215:	mov    $0x7,%esi
  b4f21a:	xor    %r14d,%r14d
  b4f21d:	xor    %r15d,%r15d
  b4f220:	movq   $0x20,0x168(%rsp)
  b4f22c:	movq   $0x0,0x170(%rsp)
  b4f238:	mov    %r12,%rdi
  b4f23b:	movq   $0x0,0x180(%rsp)
  b4f247:	movq   $0x0,0x178(%rsp)
  b4f253:	movq   $0x0,0x208(%rsp)
  b4f25f:	movq   $0x0,0x160(%rsp)
  b4f26b:	movl   $0x0,0x188(%rsp)
  b4f276:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b4f27b:	cmpq   $0x20,0x168(%rsp)
  b4f284:	lea    0x28(%r12),%rdx
  b4f289:	jbe    b4f293 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0xe3>
  b4f28b:	mov    0x208(%rsp),%rdx
  b4f293:	mov    $0xfe4840,%eax
  b4f298:	nopl   0x0(%rax,%rax,1)
  b4f2a0:	movzbl (%rax),%ecx
  b4f2a3:	add    $0x1,%rax
  b4f2a7:	mov    %ecx,(%rdx)
  b4f2a9:	add    $0x4,%rdx
  b4f2ad:	cmp    $0xfe4847,%rax
  b4f2b3:	jne    b4f2a0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0xf0>
  b4f2b5:	cmpq   $0x20,0x168(%rsp)
  b4f2be:	movq   $0x7,0x160(%rsp)
  b4f2ca:	lea    0x44(%r12),%rax
  b4f2cf:	jbe    b4f2dd <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x12d>
  b4f2d1:	mov    0x208(%rsp),%rax
  b4f2d9:	add    $0x1c,%rax
  b4f2dd:	movl   $0x0,(%rax)
  b4f2e3:	mov    %r12,%rsi
  b4f2e6:	mov    %rbx,%rdi
  b4f2e9:	mov    $0x1,%r14d
  b4f2ef:	call   553e18 <_ZNK5CEGUI11PropertySet17isPropertyPresentERKNS_6StringE@plt>
  b4f2f4:	xor    %r13d,%r13d
  b4f2f7:	test   %al,%al
  b4f2f9:	jne    b4f3e8 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x238>
  b4f2ff:	mov    %r12,%rdi
  b4f302:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f307:	test   %r13b,%r13b
  b4f30a:	jne    b4f320 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x170>
  b4f30c:	add    $0x238,%rsp
  b4f313:	pop    %rbx
  b4f314:	pop    %rbp
  b4f315:	pop    %r12
  b4f317:	pop    %r13
  b4f319:	pop    %r14
  b4f31b:	pop    %r15
  b4f31d:	ret
  b4f31e:	xchg   %ax,%ax
  b4f320:	mov    0x38(%rbx),%rax
  b4f324:	mov    $0x20,%edi
  b4f329:	mov    0x10(%rax),%r12
  b4f32d:	call   552d68 <_Znwm@plt>
  b4f332:	mov    %rbp,0x18(%rax)
  b4f336:	lea    0x220(%rsp),%rbp
  b4f33e:	movq   $0xfefcd0,(%rax)
  b4f345:	movq   $0x0,0x10(%rax)
  b4f34d:	movq   $0x59,0x8(%rax)
  b4f355:	lea    0x38(%rbx),%rsi
  b4f359:	mov    %rax,0x220(%rsp)
  b4f361:	lea    0x210(%rsp),%rdi
  b4f369:	mov    %rbp,%rcx
  b4f36c:	mov    $0x14247e0,%edx
  b4f371:	call   *%r12
  b4f374:	cmpq   $0x0,0x210(%rsp)
  b4f37d:	je     b4f3d4 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x224>
  b4f37f:	mov    0x218(%rsp),%rdx
  b4f387:	mov    (%rdx),%eax
  b4f389:	sub    $0x1,%eax
  b4f38c:	test   %eax,%eax
  b4f38e:	mov    %eax,(%rdx)
  b4f390:	jne    b4f3d4 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x224>
  b4f392:	mov    0x210(%rsp),%rbx
  b4f39a:	test   %rbx,%rbx
  b4f39d:	je     b4f3af <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x1ff>
  b4f39f:	mov    %rbx,%rdi
  b4f3a2:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b4f3a7:	mov    %rbx,%rdi
  b4f3aa:	call   553f18 <_ZdlPv@plt>
  b4f3af:	mov    0x218(%rsp),%rdi
  b4f3b7:	call   553f18 <_ZdlPv@plt>
  b4f3bc:	movq   $0x0,0x210(%rsp)
  b4f3c8:	movq   $0x0,0x218(%rsp)
  b4f3d4:	mov    %rbp,%rdi
  b4f3d7:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b4f3dc:	jmp    b4f30c <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x15c>
  b4f3e1:	nopl   0x0(%rax)
  b4f3e8:	lea    0xb0(%rsp),%rdi
  b4f3f0:	mov    $0x7,%esi
  b4f3f5:	movq   $0x20,0xb8(%rsp)
  b4f401:	movq   $0x0,0xc0(%rsp)
  b4f40d:	movq   $0x0,0xd0(%rsp)
  b4f419:	movq   $0x0,0xc8(%rsp)
  b4f425:	movq   $0x0,0x158(%rsp)
  b4f431:	movq   $0x0,0xb0(%rsp)
  b4f43d:	movl   $0x0,0xd8(%rsp)
  b4f448:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b4f44d:	cmpq   $0x20,0xb8(%rsp)
  b4f456:	ja     b4f4f0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x340>
  b4f45c:	lea    0xb0(%rsp),%rdx
  b4f464:	add    $0x28,%rdx
  b4f468:	mov    $0xfe4840,%eax
  b4f46d:	nopl   (%rax)
  b4f470:	movzbl (%rax),%ecx
  b4f473:	add    $0x1,%rax
  b4f477:	mov    %ecx,(%rdx)
  b4f479:	add    $0x4,%rdx
  b4f47d:	cmp    $0xfe4847,%rax
  b4f483:	jne    b4f470 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x2c0>
  b4f485:	cmpq   $0x20,0xb8(%rsp)
  b4f48e:	movq   $0x7,0xb0(%rsp)
  b4f49a:	ja     b4f500 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x350>
  b4f49c:	lea    0xb0(%rsp),%rax
  b4f4a4:	add    $0x44,%rax
  b4f4a8:	lea    0xb0(%rsp),%rdx
  b4f4b0:	movl   $0x0,(%rax)
  b4f4b6:	mov    %rbx,%rsi
  b4f4b9:	mov    %rsp,%rdi
  b4f4bc:	mov    $0x1,%r15d
  b4f4c2:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b4f4c7:	cmpq   $0x0,(%rsp)
  b4f4cc:	mov    %rsp,%rdi
  b4f4cf:	setne  %r13b
  b4f4d3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f4d8:	lea    0xb0(%rsp),%rdi
  b4f4e0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f4e5:	jmp    b4f2ff <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x14f>
  b4f4ea:	nopw   0x0(%rax,%rax,1)
  b4f4f0:	mov    0x158(%rsp),%rdx
  b4f4f8:	jmp    b4f468 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x2b8>
  b4f4fd:	nopl   (%rax)
  b4f500:	mov    0x158(%rsp),%rax
  b4f508:	add    $0x1c,%rax
  b4f50c:	jmp    b4f4a8 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x2f8>
  b4f50e:	mov    %rax,%rbx
  b4f511:	lea    0xb0(%rsp),%rdi
  b4f519:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f51e:	test   %r14b,%r14b
  b4f521:	jne    b4f54a <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x39a>
  b4f523:	mov    %rbx,%rdi
  b4f526:	call   552938 <__cxa_begin_catch@plt>
  b4f52b:	call   554bd8 <__cxa_end_catch@plt>
  b4f530:	jmp    b4f30c <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x15c>
  b4f535:	mov    %rax,%rbx
  b4f538:	jmp    b4f523 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x373>
  b4f53a:	mov    %rbp,%rdi
  b4f53d:	mov    %rax,%rbx
  b4f540:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b4f545:	jmp    b4f523 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x373>
  b4f547:	mov    %rax,%rbx
  b4f54a:	mov    %r12,%rdi
  b4f54d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f552:	jmp    b4f523 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x373>
  b4f554:	test   %r15b,%r15b
  b4f557:	mov    %rax,%rbx
  b4f55a:	je     b4f51e <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x36e>
  b4f55c:	nopl   0x0(%rax)
  b4f560:	jmp    b4f511 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE+0x361>
  b4f562:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
