
/workspace/scratch/3ba0fff8d310/otl-recovery-1518/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000008ac190 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb>:
  8ac190:	push   %r15
  8ac192:	push   %r14
  8ac194:	push   %r13
  8ac196:	push   %r12
  8ac198:	push   %rbp
  8ac199:	mov    %edx,%ebp
  8ac19b:	push   %rbx
  8ac19c:	mov    %rdi,%rbx
  8ac19f:	mov    %rsi,%rdi
  8ac1a2:	sub    $0x488,%rsp
  8ac1a9:	mov    %rsi,0x30(%rsp)
  8ac1ae:	call   554b18 <_ZNK4Ogre6Entity17getNumSubEntitiesEv@plt>
  8ac1b3:	test   %bpl,%bpl
  8ac1b6:	mov    %eax,0x3c(%rsp)
  8ac1ba:	jne    8ac69b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x50b>
  8ac1c0:	mov    0x60(%rbx),%rax
  8ac1c4:	cmp    0x30(%rsp),%rax
  8ac1c9:	je     8ac1e1 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x51>
  8ac1cb:	cmpq   $0x0,0x230(%rbx)
  8ac1d3:	je     8adfcf <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1e3f>
  8ac1d9:	movq   $0x0,0x60(%rbx)
  8ac1e1:	mov    0x30(%rsp),%rsi
  8ac1e6:	mov    %rbx,%rdi
  8ac1e9:	call   a01b20 <_ZN16CSceneNodeObject21sceneNodeAttachEntityEPN4Ogre6EntityE>
  8ac1ee:	cmpq   $0x0,0x130(%rbx)
  8ac1f6:	je     8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac1fc:	mov    0x30(%rsp),%rdx
  8ac201:	mov    0x150(%rbx),%r12d
  8ac208:	mov    0x2e8(%rdx),%rax
  8ac20f:	test   %r12d,%r12d
  8ac212:	mov    %rax,0x130(%rbx)
  8ac219:	jne    8ac3a1 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211>
  8ac21f:	mov    0x1e0(%rbx),%rax
  8ac226:	test   %rax,%rax
  8ac229:	je     8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac22f:	mov    0x20(%rax),%r11d
  8ac233:	test   %r11d,%r11d
  8ac236:	je     8ac316 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x186>
  8ac23c:	xor    %ebp,%ebp
  8ac23e:	mov    %rdx,%r12
  8ac241:	jmp    8ac26f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xdf>
  8ac243:	nopl   0x0(%rax,%rax,1)
  8ac248:	mov    0x148(%rbx),%r15
  8ac24f:	mov    %eax,%eax
  8ac251:	add    $0x1,%ebp
  8ac254:	mov    %r13,(%r15,%rax,8)
  8ac258:	mov    0x1e0(%rbx),%rax
  8ac25f:	addl   $0x1,0x150(%rbx)
  8ac266:	cmp    %ebp,0x20(%rax)
  8ac269:	jbe    8ac316 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x186>
  8ac26f:	mov    %ebp,%esi
  8ac271:	mov    %r12,%rdi
  8ac274:	shl    $0x3,%rsi
  8ac278:	add    0x28(%rax),%rsi
  8ac27c:	call   5536a8 <_ZNK4Ogre6Entity17getAnimationStateERKSs@plt>
  8ac281:	mov    0x154(%rbx),%r14d
  8ac288:	mov    %rax,%r13
  8ac28b:	mov    0x150(%rbx),%eax
  8ac291:	cmp    %r14d,%eax
  8ac294:	jb     8ac248 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xb8>
  8ac296:	cmpq   $0x0,0x148(%rbx)
  8ac29e:	je     8ac65d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x4cd>
  8ac2a4:	add    0x158(%rbx),%r14d
  8ac2ab:	mov    %r14d,%edi
  8ac2ae:	shl    $0x3,%rdi
  8ac2b2:	call   553ae8 <_Znam@plt>
  8ac2b7:	mov    0x154(%rbx),%r10d
  8ac2be:	mov    %rax,%r15
  8ac2c1:	test   %r10d,%r10d
  8ac2c4:	je     8ac2ec <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x15c>
  8ac2c6:	xor    %eax,%eax
  8ac2c8:	nopl   0x0(%rax,%rax,1)
  8ac2d0:	mov    0x148(%rbx),%rcx
  8ac2d7:	mov    %eax,%edx
  8ac2d9:	add    $0x1,%eax
  8ac2dc:	mov    (%rcx,%rdx,8),%rcx
  8ac2e0:	mov    %rcx,(%r15,%rdx,8)
  8ac2e4:	cmp    0x154(%rbx),%eax
  8ac2ea:	jb     8ac2d0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x140>
  8ac2ec:	mov    0x148(%rbx),%rdi
  8ac2f3:	test   %rdi,%rdi
  8ac2f6:	je     8ac2fd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x16d>
  8ac2f8:	call   553638 <_ZdaPv@plt>
  8ac2fd:	mov    %r15,0x148(%rbx)
  8ac304:	mov    %r14d,0x154(%rbx)
  8ac30b:	mov    0x150(%rbx),%eax
  8ac311:	jmp    8ac24f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xbf>
  8ac316:	lea    0x220(%rsp),%rbp
  8ac31e:	lea    0x463(%rsp),%rdx
  8ac326:	mov    $0xfc993a,%esi
  8ac32b:	mov    %rbp,%rdi
  8ac32e:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ac333:	movss  0x6fc425(%rip),%xmm1        # fa8760 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xc0>
  8ac33b:	mov    $0x1,%edx
  8ac340:	movss  0x6f84b4(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  8ac348:	mov    %rbp,%rsi
  8ac34b:	mov    %rbx,%rdi
  8ac34e:	call   8a5cf0 <_ZN13CGenericModel13playAnimationERKSsbff>
  8ac353:	mov    0x220(%rsp),%rdi
  8ac35b:	sub    $0x18,%rdi
  8ac35f:	cmp    $0x1423a20,%rdi
  8ac366:	je     8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac368:	mov    $0x5541c8,%eax
  8ac36d:	test   %rax,%rax
  8ac370:	je     8aeb6e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x29de>
  8ac376:	or     $0xffffffff,%eax
  8ac379:	lock xadd %eax,0x10(%rdi)
  8ac37e:	test   %eax,%eax
  8ac380:	jg     8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac382:	lea    0x440(%rsp),%rsi
  8ac38a:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ac38f:	add    $0x488,%rsp
  8ac396:	pop    %rbx
  8ac397:	pop    %rbp
  8ac398:	pop    %r12
  8ac39a:	pop    %r13
  8ac39c:	pop    %r14
  8ac39e:	pop    %r15
  8ac3a0:	ret
  8ac3a1:	mov    0x1e0(%rbx),%rax
  8ac3a8:	test   %rax,%rax
  8ac3ab:	je     8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac3ad:	mov    0x20(%rax),%r9d
  8ac3b1:	test   %r9d,%r9d
  8ac3b4:	je     8ac409 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x279>
  8ac3b6:	xor    %ebp,%ebp
  8ac3b8:	mov    0x30(%rsp),%r13
  8ac3bd:	jmp    8ac3ef <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x25f>
  8ac3bf:	nop
  8ac3c0:	mov    0x148(%rbx),%r12
  8ac3c7:	mov    %ebp,%edx
  8ac3c9:	shl    $0x3,%rdx
  8ac3cd:	mov    %rdx,%rsi
  8ac3d0:	add    0x28(%rax),%rsi
  8ac3d4:	mov    %r13,%rdi
  8ac3d7:	add    $0x1,%ebp
  8ac3da:	call   5536a8 <_ZNK4Ogre6Entity17getAnimationStateERKSs@plt>
  8ac3df:	mov    %rax,(%r12)
  8ac3e3:	mov    0x1e0(%rbx),%rax
  8ac3ea:	cmp    %ebp,0x20(%rax)
  8ac3ed:	jbe    8ac409 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x279>
  8ac3ef:	cmp    %ebp,0x154(%rbx)
  8ac3f5:	jbe    8ac3c0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x230>
  8ac3f7:	mov    %ebp,%edx
  8ac3f9:	shl    $0x3,%rdx
  8ac3fd:	mov    %rdx,%r12
  8ac400:	add    0x148(%rbx),%r12
  8ac407:	jmp    8ac3cd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x23d>
  8ac409:	mov    0x180(%rbx),%rdi
  8ac410:	mov    0x190(%rbx),%r8
  8ac417:	mov    0x170(%rbx),%rcx
  8ac41e:	mov    0x198(%rbx),%r9
  8ac425:	mov    0x1a8(%rbx),%r10
  8ac42c:	mov    0x188(%rbx),%rsi
  8ac433:	mov    %rdi,%rdx
  8ac436:	mov    %r8,%rax
  8ac439:	sub    %rcx,%rdx
  8ac43c:	sub    %r9,%rax
  8ac43f:	sar    $0x3,%rax
  8ac443:	sar    $0x3,%rdx
  8ac447:	add    %rax,%rdx
  8ac44a:	mov    %r10,%rax
  8ac44d:	sub    %rsi,%rax
  8ac450:	sar    $0x3,%rax
  8ac454:	shl    $0x6,%rax
  8ac458:	lea    -0x40(%rax,%rdx,1),%rax
  8ac45d:	test   %eax,%eax
  8ac45f:	jle    8ac648 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x4b8>
  8ac465:	xor    %r12d,%r12d
  8ac468:	jmp    8ac584 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x3f4>
  8ac46d:	nopl   (%rax)
  8ac470:	mov    (%rcx,%rbp,8),%rax
  8ac474:	mov    0x10(%rax),%r13d
  8ac478:	lea    (%rcx,%rbp,8),%rax
  8ac47c:	mov    (%rax),%rax
  8ac47f:	cmpb   $0x0,0x28(%rax)
  8ac483:	jne    8ac54d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x3bd>
  8ac489:	cmp    %r13d,0x154(%rbx)
  8ac490:	ja     8ac5e1 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x451>
  8ac496:	mov    0x148(%rbx),%rax
  8ac49d:	mov    (%rax),%rdi
  8ac4a0:	mov    $0x1,%esi
  8ac4a5:	call   555f78 <_ZN4Ogre14AnimationState10setEnabledEb@plt>
  8ac4aa:	mov    0x170(%rbx),%rdx
  8ac4b1:	mov    0x188(%rbx),%rsi
  8ac4b8:	mov    %rdx,%rax
  8ac4bb:	sub    0x178(%rbx),%rax
  8ac4c2:	sar    $0x3,%rax
  8ac4c6:	add    %rbp,%rax
  8ac4c9:	js     8ac689 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x4f9>
  8ac4cf:	cmp    $0x3f,%rax
  8ac4d3:	lea    (%rdx,%rbp,8),%rdx
  8ac4d7:	jle    8ac4ff <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x36f>
  8ac4d9:	test   %rax,%rax
  8ac4dc:	jle    8ac689 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x4f9>
  8ac4e2:	mov    %rax,%rcx
  8ac4e5:	sar    $0x6,%rcx
  8ac4e9:	mov    %rcx,%rdx
  8ac4ec:	shl    $0x6,%rdx
  8ac4f0:	sub    %rdx,%rax
  8ac4f3:	lea    0x0(,%rax,8),%rdx
  8ac4fb:	add    (%rsi,%rcx,8),%rdx
  8ac4ff:	cmp    %r13d,0x154(%rbx)
  8ac506:	mov    (%rdx),%rax
  8ac509:	movss  0x20(%rax),%xmm0
  8ac50e:	ja     8ac5f4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x464>
  8ac514:	mov    0x148(%rbx),%rax
  8ac51b:	mov    (%rax),%rdi
  8ac51e:	call   5550c8 <_ZN4Ogre14AnimationState15setTimePositionEf@plt>
  8ac523:	mov    0x188(%rbx),%rsi
  8ac52a:	mov    0x170(%rbx),%rcx
  8ac531:	mov    0x180(%rbx),%rdi
  8ac538:	mov    0x198(%rbx),%r9
  8ac53f:	mov    0x190(%rbx),%r8
  8ac546:	mov    0x1a8(%rbx),%r10
  8ac54d:	mov    %rdi,%rdx
  8ac550:	mov    %r8,%rax
  8ac553:	add    $0x1,%r12d
  8ac557:	sub    %rcx,%rdx
  8ac55a:	sub    %r9,%rax
  8ac55d:	sar    $0x3,%rax
  8ac561:	sar    $0x3,%rdx
  8ac565:	add    %rax,%rdx
  8ac568:	mov    %r10,%rax
  8ac56b:	sub    %rsi,%rax
  8ac56e:	sar    $0x3,%rax
  8ac572:	shl    $0x6,%rax
  8ac576:	lea    -0x40(%rax,%rdx,1),%rax
  8ac57b:	cmp    %eax,%r12d
  8ac57e:	jge    8ac648 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x4b8>
  8ac584:	mov    %rcx,%rax
  8ac587:	sub    0x178(%rbx),%rax
  8ac58e:	movslq %r12d,%rbp
  8ac591:	sar    $0x3,%rax
  8ac595:	add    %rbp,%rax
  8ac598:	js     8ac607 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x477>
  8ac59a:	cmp    $0x3f,%rax
  8ac59e:	jle    8ac470 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2e0>
  8ac5a4:	test   %rax,%rax
  8ac5a7:	jle    8ac607 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x477>
  8ac5a9:	mov    %rax,%rdx
  8ac5ac:	mov    %rax,%r11
  8ac5af:	sar    $0x6,%rdx
  8ac5b3:	and    $0x3f,%r11d
  8ac5b7:	mov    (%rsi,%rdx,8),%rdx
  8ac5bb:	mov    (%rdx,%r11,8),%rdx
  8ac5bf:	mov    0x10(%rdx),%r13d
  8ac5c3:	mov    %rax,%rdx
  8ac5c6:	sar    $0x6,%rdx
  8ac5ca:	mov    %rdx,%r11
  8ac5cd:	shl    $0x6,%r11
  8ac5d1:	sub    %r11,%rax
  8ac5d4:	shl    $0x3,%rax
  8ac5d8:	add    (%rsi,%rdx,8),%rax
  8ac5dc:	jmp    8ac47c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2ec>
  8ac5e1:	mov    %r13d,%eax
  8ac5e4:	shl    $0x3,%rax
  8ac5e8:	add    0x148(%rbx),%rax
  8ac5ef:	jmp    8ac49d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x30d>
  8ac5f4:	mov    %r13d,%eax
  8ac5f7:	shl    $0x3,%rax
  8ac5fb:	add    0x148(%rbx),%rax
  8ac602:	jmp    8ac51b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x38b>
  8ac607:	mov    %rax,%rdx
  8ac60a:	mov    %rax,%r11
  8ac60d:	not    %rdx
  8ac610:	shr    $0x6,%rdx
  8ac614:	not    %rdx
  8ac617:	mov    %rdx,%r13
  8ac61a:	shl    $0x6,%r13
  8ac61e:	sub    %r13,%r11
  8ac621:	test   %rax,%rax
  8ac624:	mov    %r11,%r13
  8ac627:	mov    (%rsi,%rdx,8),%r11
  8ac62b:	mov    (%r11,%r13,8),%r11
  8ac62f:	mov    0x10(%r11),%r13d
  8ac633:	js     8ac5ca <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x43a>
  8ac635:	cmp    $0x3f,%rax
  8ac639:	jle    8ac478 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2e8>
  8ac63f:	jmp    8ac5c3 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x433>
  8ac641:	nopl   0x0(%rax)
  8ac648:	xorps  %xmm0,%xmm0
  8ac64b:	mov    $0x1,%esi
  8ac650:	mov    %rbx,%rdi
  8ac653:	call   8aa4b0 <_ZN13CGenericModel15updateAnimationEfb>
  8ac658:	jmp    8ac38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ff>
  8ac65d:	mov    0x158(%rbx),%eax
  8ac663:	mov    %eax,%edi
  8ac665:	mov    %eax,0x154(%rbx)
  8ac66b:	shl    $0x3,%rdi
  8ac66f:	call   553ae8 <_Znam@plt>
  8ac674:	mov    %rax,%r15
  8ac677:	mov    %rax,0x148(%rbx)
  8ac67e:	mov    0x150(%rbx),%eax
  8ac684:	jmp    8ac24f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xbf>
  8ac689:	mov    %rax,%rcx
  8ac68c:	not    %rcx
  8ac68f:	shr    $0x6,%rcx
  8ac693:	not    %rcx
  8ac696:	jmp    8ac4e9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x359>
  8ac69b:	movb   $0x0,0x238(%rbx)
  8ac6a2:	mov    %rbx,%rdi
  8ac6a5:	call   89a900 <_ZN13CGenericModel22releaseUniqueMaterialsEv>
  8ac6aa:	mov    0x208(%rbx),%r12
  8ac6b1:	mov    0x210(%rbx),%r13
  8ac6b8:	cmp    %r13,%r12
  8ac6bb:	mov    %r12,%rcx
  8ac6be:	je     8ac705 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x575>
  8ac6c0:	lea    0x462(%rsp),%r15
  8ac6c8:	mov    %r12,%rbp
  8ac6cb:	mov    $0x5541c8,%eax
  8ac6d0:	mov    $0xffffffff,%r14d
  8ac6d6:	cs nopw 0x0(%rax,%rax,1)
  8ac6e0:	mov    0x38(%rbp),%rdi
  8ac6e4:	sub    $0x18,%rdi
  8ac6e8:	cmp    $0x1423a20,%rdi
  8ac6ef:	jne    8aeaaf <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x291f>
  8ac6f5:	add    $0x40,%rbp
  8ac6f9:	cmp    %rbp,%r13
  8ac6fc:	jne    8ac6e0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x550>
  8ac6fe:	mov    0x208(%rbx),%rcx
  8ac705:	mov    %r12,0x210(%rbx)
  8ac70c:	mov    0x3c(%rsp),%edx
  8ac710:	mov    %r12,%rax
  8ac713:	sub    %rcx,%rax
  8ac716:	movb   $0x1,0x50(%rsp)
  8ac71b:	movb   $0x0,0x51(%rsp)
  8ac720:	sar    $0x6,%rax
  8ac724:	movb   $0x0,0x52(%rsp)
  8ac729:	movb   $0x0,0x53(%rsp)
  8ac72e:	movb   $0x0,0x54(%rsp)
  8ac733:	movq   $0x0,0x58(%rsp)
  8ac73c:	cmp    %rax,%rdx
  8ac73f:	movq   $0x0,0x60(%rsp)
  8ac748:	movq   $0x0,0x68(%rsp)
  8ac751:	movq   $0x0,0x70(%rsp)
  8ac75a:	movw   $0xffff,0x78(%rsp)
  8ac761:	movw   $0x1,0x7a(%rsp)
  8ac768:	movw   $0x0,0x7c(%rsp)
  8ac76f:	movb   $0x0,0x7e(%rsp)
  8ac774:	movb   $0x0,0x7f(%rsp)
  8ac779:	movb   $0x0,0x80(%rsp)
  8ac781:	movb   $0x1,0x81(%rsp)
  8ac789:	movl   $0x3f800000,0x84(%rsp)
  8ac794:	movq   $0x1423a38,0x88(%rsp)
  8ac7a0:	jae    8adfdb <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1e4b>
  8ac7a6:	shl    $0x6,%rdx
  8ac7aa:	lea    (%rcx,%rdx,1),%r13
  8ac7ae:	cmp    %r13,%r12
  8ac7b1:	mov    %r13,%rbp
  8ac7b4:	je     8ac7ee <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x65e>
  8ac7b6:	lea    0x461(%rsp),%r15
  8ac7be:	mov    $0x5541c8,%eax
  8ac7c3:	mov    $0xffffffff,%r14d
  8ac7c9:	nopl   0x0(%rax)
  8ac7d0:	mov    0x38(%rbp),%rdi
  8ac7d4:	sub    $0x18,%rdi
  8ac7d8:	cmp    $0x1423a20,%rdi
  8ac7df:	jne    8aeb42 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x29b2>
  8ac7e5:	add    $0x40,%rbp
  8ac7e9:	cmp    %rbp,%r12
  8ac7ec:	jne    8ac7d0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x640>
  8ac7ee:	mov    %r13,0x210(%rbx)
  8ac7f5:	mov    0x88(%rsp),%rdi
  8ac7fd:	sub    $0x18,%rdi
  8ac801:	cmp    $0x1423a20,%rdi
  8ac808:	jne    8aeafb <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x296b>
  8ac80e:	mov    0x3c(%rsp),%r13d
  8ac813:	test   %r13d,%r13d
  8ac816:	je     8ac1c0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x30>
  8ac81c:	lea    0xc0(%rsp),%rax
  8ac824:	lea    0x90(%rsp),%rdx
  8ac82c:	lea    0x2b0(%rsp),%r15
  8ac834:	xor    %ebp,%ebp
  8ac836:	movl   $0x0,0x24(%rsp)
  8ac83e:	add    $0x8,%rax
  8ac842:	add    $0x8,%rdx
  8ac846:	mov    %rax,0x48(%rsp)
  8ac84b:	mov    %rdx,0x40(%rsp)
  8ac850:	mov    0x24(%rsp),%esi
  8ac854:	mov    0x30(%rsp),%rdi
  8ac859:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  8ac85e:	mov    %rax,%r13
  8ac861:	mov    (%rax),%rax
  8ac864:	xor    %ecx,%ecx
  8ac866:	xor    %edx,%edx
  8ac868:	xor    %esi,%esi
  8ac86a:	mov    $0x10,%edi
  8ac86f:	mov    0x208(%rbx),%r14
  8ac876:	mov    0x78(%rax),%r12
  8ac87a:	movq   $0xfceab0,0x210(%rsp)
  8ac886:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  8ac88b:	test   %rax,%rax
  8ac88e:	je     8ac89e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x70e>
  8ac890:	add    %rbp,%r14
  8ac893:	movq   $0xfd18b0,(%rax)
  8ac89a:	mov    %r14,0x8(%rax)
  8ac89e:	mov    %rax,0x218(%rsp)
  8ac8a6:	lea    0x210(%rsp),%rsi
  8ac8ae:	mov    %r13,%rdi
  8ac8b1:	call   *%r12
  8ac8b4:	mov    0x218(%rsp),%rdi
  8ac8bc:	movq   $0xfceab0,0x210(%rsp)
  8ac8c8:	test   %rdi,%rdi
  8ac8cb:	je     8ac8df <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x74f>
  8ac8cd:	mov    (%rdi),%rax
  8ac8d0:	call   *(%rax)
  8ac8d2:	mov    0x218(%rsp),%rdi
  8ac8da:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  8ac8df:	mov    0x0(%r13),%rax
  8ac8e3:	mov    %rbp,%r12
  8ac8e6:	add    0x208(%rbx),%r12
  8ac8ed:	mov    %r13,%rdi
  8ac8f0:	call   *0x10(%rax)
  8ac8f3:	mov    0x8(%rax),%rax
  8ac8f7:	xor    %edx,%edx
  8ac8f9:	xor    %esi,%esi
  8ac8fb:	mov    %rax,0x10(%r12)
  8ac900:	mov    0x208(%rbx),%rax
  8ac907:	mov    0x10(%rax,%rbp,1),%rdi
  8ac90c:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ac911:	xor    %esi,%esi
  8ac913:	mov    %rax,%rdi
  8ac916:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ac91b:	mov    0xf0(%rax),%r12
  8ac922:	sub    0xe8(%rax),%r12
  8ac929:	sar    $0x3,%r12
  8ac92d:	movzwl %r12w,%r12d
  8ac931:	cmp    $0x1,%r12d
  8ac935:	jle    8ac98a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x7fa>
  8ac937:	mov    %r13,0x18(%rsp)
  8ac93c:	mov    %rbx,0x28(%rsp)
  8ac941:	mov    %rbp,%r13
  8ac944:	mov    $0x1,%r14d
  8ac94a:	mov    %rax,%rbp
  8ac94d:	mov    %r12d,%ebx
  8ac950:	movzwl %r14w,%esi
  8ac954:	mov    %rbp,%rdi
  8ac957:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  8ac95c:	lea    0x160(%rax),%rdi
  8ac963:	mov    $0xfd1114,%esi
  8ac968:	call   555d18 <_ZNKSs7compareEPKc@plt>
  8ac96d:	cmp    $0x1,%eax
  8ac970:	sbb    $0x0,%r12d
  8ac974:	add    $0x1,%r14d
  8ac978:	cmp    %r14d,%ebx
  8ac97b:	jg     8ac950 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x7c0>
  8ac97d:	mov    %r13,%rbp
  8ac980:	mov    0x28(%rsp),%rbx
  8ac985:	mov    0x18(%rsp),%r13
  8ac98a:	mov    0x208(%rbx),%rax
  8ac991:	mov    %r12w,0x2a(%rax,%rbp,1)
  8ac997:	mov    0x208(%rbx),%rax
  8ac99e:	mov    0x10(%rax,%rbp,1),%rdi
  8ac9a3:	mov    (%rdi),%rax
  8ac9a6:	call   *0xc8(%rax)
  8ac9ac:	mov    %rbp,%rdi
  8ac9af:	add    0x208(%rbx),%rdi
  8ac9b6:	mov    %rax,%rsi
  8ac9b9:	add    $0x38,%rdi
  8ac9bd:	call   554d18 <_ZNSs6assignERKSs@plt>
  8ac9c2:	cmpb   $0x0,0x224(%rbx)
  8ac9c9:	je     8acc90 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xb00>
  8ac9cf:	mov    0x208(%rbx),%rax
  8ac9d6:	mov    0x10(%rax,%rbp,1),%rdi
  8ac9db:	mov    (%rdi),%rax
  8ac9de:	call   *0xc8(%rax)
  8ac9e4:	mov    %r15,%rdi
  8ac9e7:	mov    %rax,%rsi
  8ac9ea:	call   5529a8 <_ZNSsC1ERKSs@plt>
  8ac9ef:	lea    0x47f(%rsp),%rdx
  8ac9f7:	lea    0x430(%rsp),%rdi
  8ac9ff:	mov    $0xfd1150,%esi
  8aca04:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8aca09:	lea    0x420(%rsp),%r14
  8aca11:	lea    0x430(%rsp),%rsi
  8aca19:	mov    %r14,%rdi
  8aca1c:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  8aca21:	mov    %r14,%rsi
  8aca24:	mov    %r15,%rdi
  8aca27:	call   554d18 <_ZNSs6assignERKSs@plt>
  8aca2c:	mov    0x420(%rsp),%rdi
  8aca34:	sub    $0x18,%rdi
  8aca38:	cmp    $0x1423a20,%rdi
  8aca3f:	jne    8ae430 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x22a0>
  8aca45:	mov    0x430(%rsp),%rdi
  8aca4d:	sub    $0x18,%rdi
  8aca51:	cmp    $0x1423a20,%rdi
  8aca58:	jne    8ae45c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x22cc>
  8aca5e:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  8aca63:	mov    (%rax),%rdx
  8aca66:	mov    %r15,%rsi
  8aca69:	mov    %rax,%rdi
  8aca6c:	call   *0xb0(%rdx)
  8aca72:	test   %al,%al
  8aca74:	jne    8ad4b8 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1328>
  8aca7a:	mov    0x208(%rbx),%rax
  8aca81:	lea    0x1d0(%rsp),%rdi
  8aca89:	mov    $0x1423540,%r8d
  8aca8f:	xor    %ecx,%ecx
  8aca91:	mov    %r15,%rdx
  8aca94:	mov    0x10(%rax,%rbp,1),%rsi
  8aca99:	call   556448 <_ZNK4Ogre8Material5cloneERKSsbS2_@plt>
  8aca9e:	mov    0x1e0(%rsp),%rax
  8acaa6:	mov    0x1d8(%rsp),%r14
  8acaae:	movq   $0xfa4590,0x1d0(%rsp)
  8acaba:	test   %rax,%rax
  8acabd:	je     8acadd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x94d>
  8acabf:	mov    (%rax),%edx
  8acac1:	sub    $0x1,%edx
  8acac4:	test   %edx,%edx
  8acac6:	mov    %edx,(%rax)
  8acac8:	jne    8acadd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x94d>
  8acaca:	mov    0x1d0(%rsp),%rax
  8acad2:	lea    0x1d0(%rsp),%rdi
  8acada:	call   *0x10(%rax)
  8acadd:	mov    0x208(%rbx),%rax
  8acae4:	xor    %edx,%edx
  8acae6:	xor    %esi,%esi
  8acae8:	mov    %r14,%rdi
  8acaeb:	mov    %r14,0x18(%rax,%rbp,1)
  8acaf0:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8acaf5:	xor    %esi,%esi
  8acaf7:	mov    %rax,%rdi
  8acafa:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8acaff:	mov    0xf0(%rax),%rdx
  8acb06:	sub    0xe8(%rax),%rdx
  8acb0d:	shr    $0x3,%rdx
  8acb11:	test   %dx,%dx
  8acb14:	jne    8ad73f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x15af>
  8acb1a:	movb   $0x1,0x18(%rsp)
  8acb1f:	mov    0x2b0(%rsp),%rdi
  8acb27:	sub    $0x18,%rdi
  8acb2b:	cmp    $0x1423a20,%rdi
  8acb32:	jne    8ae3d5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2245>
  8acb38:	mov    0x208(%rbx),%rax
  8acb3f:	xor    %edx,%edx
  8acb41:	xor    %esi,%esi
  8acb43:	mov    0x10(%rax,%rbp,1),%rdi
  8acb48:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8acb4d:	test   %rax,%rax
  8acb50:	je     8acc12 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa82>
  8acb56:	mov    0x208(%rbx),%rax
  8acb5d:	lea    0x47c(%rsp),%rdx
  8acb65:	lea    0x3f0(%rsp),%rdi
  8acb6d:	mov    0x38(%rax,%rbp,1),%rsi
  8acb72:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8acb77:	lea    0x3e0(%rsp),%r14
  8acb7f:	lea    0x3f0(%rsp),%rsi
  8acb87:	mov    %r14,%rdi
  8acb8a:	call   c8e0e0 <_ZN7STRINGS11StringUpperERKSs>
  8acb8f:	mov    $0x8,%ecx
  8acb94:	xor    %edx,%edx
  8acb96:	mov    $0xfd115e,%esi
  8acb9b:	mov    %r14,%rdi
  8acb9e:	call   555138 <_ZNKSs4findEPKcmm@plt>
  8acba3:	mov    0x3e0(%rsp),%rdi
  8acbab:	sub    $0x18,%rdi
  8acbaf:	cmp    $0x1423a20,%rdi
  8acbb6:	jne    8ae516 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2386>
  8acbbc:	mov    0x3f0(%rsp),%rdi
  8acbc4:	sub    $0x18,%rdi
  8acbc8:	cmp    $0x1423a20,%rdi
  8acbcf:	jne    8ae54c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x23bc>
  8acbd5:	cmp    $0xffffffffffffffff,%rax
  8acbd9:	je     8acbee <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa5e>
  8acbdb:	mov    0x208(%rbx),%rax
  8acbe2:	movb   $0x1,0x2f(%rax,%rbp,1)
  8acbe7:	movb   $0x1,0x23a(%rbx)
  8acbee:	mov    0xc5e8e7(%rip),%r14d        # 150b4dc <KSETTINGS_ALLOW_HWSKINNING>
  8acbf5:	call   a54490 <_ZN22CMasterResourceManager12getSingletonEv>
  8acbfa:	mov    0x90(%rax),%rdi
  8acc01:	mov    %r14d,%esi
  8acc04:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  8acc09:	cmp    $0x1,%eax
  8acc0c:	je     8ad52d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x139d>
  8acc12:	mov    %rbp,%rax
  8acc15:	add    0x208(%rbx),%rax
  8acc1c:	cmpb   $0x0,0x224(%rbx)
  8acc23:	je     8acdd0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xc40>
  8acc29:	movb   $0x1,0x1(%rax)
  8acc2d:	cmpq   $0x0,0x30(%rsp)
  8acc33:	je     8acc4b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xabb>
  8acc35:	mov    0x30(%rsp),%r11
  8acc3a:	mov    $0x4,%esi
  8acc3f:	mov    (%r11),%rax
  8acc42:	mov    %r11,%rdi
  8acc45:	call   *0x178(%rax)
  8acc4b:	mov    %rbp,%rax
  8acc4e:	add    0x208(%rbx),%rax
  8acc55:	mov    0x10(%rax),%rdx
  8acc59:	mov    %rdx,0x8(%rax)
  8acc5d:	cmpb   $0x0,0x224(%rbx)
  8acc64:	jne    8ace80 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xcf0>
  8acc6a:	addl   $0x1,0x24(%rsp)
  8acc6f:	add    $0x40,%rbp
  8acc73:	mov    0x24(%rsp),%eax
  8acc77:	cmp    %eax,0x3c(%rsp)
  8acc7b:	ja     8ac850 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x6c0>
  8acc81:	jmp    8ac1c0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x30>
  8acc86:	cs nopw 0x0(%rax,%rax,1)
  8acc90:	mov    0x208(%rbx),%rax
  8acc97:	mov    0x10(%rax,%rbp,1),%rdi
  8acc9c:	mov    (%rdi),%rax
  8acc9f:	call   *0xc8(%rax)
  8acca5:	mov    $0xfd1150,%esi
  8accaa:	mov    %rax,%rdx
  8accad:	mov    %r15,%rdi
  8accb0:	call   56aee0 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_>
  8accb5:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  8accba:	mov    (%rax),%rdx
  8accbd:	mov    %r15,%rsi
  8accc0:	mov    %rax,%rdi
  8accc3:	call   *0xb0(%rdx)
  8accc9:	test   %al,%al
  8acccb:	jne    8ad448 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x12b8>
  8accd1:	mov    0x208(%rbx),%rax
  8accd8:	lea    0x190(%rsp),%rdi
  8acce0:	mov    $0x1423540,%r8d
  8acce6:	xor    %ecx,%ecx
  8acce8:	mov    %r15,%rdx
  8acceb:	mov    0x10(%rax,%rbp,1),%rsi
  8accf0:	call   556448 <_ZNK4Ogre8Material5cloneERKSsbS2_@plt>
  8accf5:	mov    0x1a0(%rsp),%rax
  8accfd:	mov    0x198(%rsp),%r14
  8acd05:	movq   $0xfa4590,0x190(%rsp)
  8acd11:	test   %rax,%rax
  8acd14:	je     8acd34 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xba4>
  8acd16:	mov    (%rax),%edx
  8acd18:	sub    $0x1,%edx
  8acd1b:	test   %edx,%edx
  8acd1d:	mov    %edx,(%rax)
  8acd1f:	jne    8acd34 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xba4>
  8acd21:	mov    0x190(%rsp),%rax
  8acd29:	lea    0x190(%rsp),%rdi
  8acd31:	call   *0x10(%rax)
  8acd34:	mov    0x208(%rbx),%rax
  8acd3b:	xor    %esi,%esi
  8acd3d:	mov    %r14,%rdi
  8acd40:	mov    %r14,0x18(%rax,%rbp,1)
  8acd45:	call   552da8 <_ZN4Ogre8Material18setLightingEnabledEb@plt>
  8acd4a:	xor    %edx,%edx
  8acd4c:	xor    %esi,%esi
  8acd4e:	mov    %r14,%rdi
  8acd51:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8acd56:	xor    %esi,%esi
  8acd58:	mov    %rax,%rdi
  8acd5b:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8acd60:	mov    0xf0(%rax),%rdx
  8acd67:	sub    0xe8(%rax),%rdx
  8acd6e:	movb   $0x1,0x18(%rsp)
  8acd73:	shr    $0x3,%rdx
  8acd77:	test   %dx,%dx
  8acd7a:	jne    8ada48 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x18b8>
  8acd80:	mov    0x2b0(%rsp),%rdi
  8acd88:	sub    $0x18,%rdi
  8acd8c:	cmp    $0x1423a20,%rdi
  8acd93:	je     8acb38 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x9a8>
  8acd99:	mov    $0x5541c8,%eax
  8acd9e:	test   %rax,%rax
  8acda1:	je     8ae5ec <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x245c>
  8acda7:	or     $0xffffffff,%eax
  8acdaa:	lock xadd %eax,0x10(%rdi)
  8acdaf:	test   %eax,%eax
  8acdb1:	jg     8acb38 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x9a8>
  8acdb7:	lea    0x456(%rsp),%rsi
  8acdbf:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8acdc4:	jmp    8acb38 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x9a8>
  8acdc9:	nopl   0x0(%rax)
  8acdd0:	mov    0x10(%rax),%rdi
  8acdd4:	mov    (%rdi),%rax
  8acdd7:	call   *0xc8(%rax)
  8acddd:	mov    %r15,%rdi
  8acde0:	mov    %rax,%rsi
  8acde3:	call   5529a8 <_ZNSsC1ERKSs@plt>
  8acde8:	mov    $0x6,%ecx
  8acded:	xor    %edx,%edx
  8acdef:	mov    $0xfd11ca,%esi
  8acdf4:	mov    %r15,%rdi
  8acdf7:	call   555138 <_ZNKSs4findEPKcmm@plt>
  8acdfc:	cmp    $0xffffffffffffffff,%rax
  8ace00:	je     8ace0e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xc7e>
  8ace02:	mov    0x208(%rbx),%rax
  8ace09:	movb   $0x1,0x30(%rax,%rbp,1)
  8ace0e:	mov    $0x7,%ecx
  8ace13:	xor    %edx,%edx
  8ace15:	mov    $0xfd11d1,%esi
  8ace1a:	mov    %r15,%rdi
  8ace1d:	call   555138 <_ZNKSs4findEPKcmm@plt>
  8ace22:	cmp    $0xffffffffffffffff,%rax
  8ace26:	je     8ace34 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xca4>
  8ace28:	mov    0x208(%rbx),%rax
  8ace2f:	movb   $0x0,0x31(%rax,%rbp,1)
  8ace34:	mov    0x2b0(%rsp),%rdi
  8ace3c:	sub    $0x18,%rdi
  8ace40:	cmp    $0x1423a20,%rdi
  8ace47:	je     8acc4b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xabb>
  8ace4d:	mov    $0x5541c8,%eax
  8ace52:	test   %rax,%rax
  8ace55:	je     8ae5bf <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x242f>
  8ace5b:	or     $0xffffffff,%eax
  8ace5e:	lock xadd %eax,0x10(%rdi)
  8ace63:	test   %eax,%eax
  8ace65:	jg     8acc4b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xabb>
  8ace6b:	lea    0x44e(%rsp),%rsi
  8ace73:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ace78:	jmp    8acc4b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xabb>
  8ace7d:	nopl   (%rax)
  8ace80:	mov    0x208(%rbx),%rax
  8ace87:	lea    0x2a0(%rsp),%r12
  8ace8f:	mov    0x10(%rax,%rbp,1),%rdi
  8ace94:	mov    (%rdi),%rax
  8ace97:	call   *0xc8(%rax)
  8ace9d:	mov    %r12,%rdi
  8acea0:	mov    %rax,%rsi
  8acea3:	call   5529a8 <_ZNSsC1ERKSs@plt>
  8acea8:	mov    $0x7,%edx
  8acead:	mov    $0xfd11d9,%esi
  8aceb2:	mov    %r12,%rdi
  8aceb5:	call   554128 <_ZNSs6appendEPKcm@plt>
  8aceba:	mov    %r12,%rsi
  8acebd:	mov    %r15,%rdi
  8acec0:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  8acec5:	mov    0x2a0(%rsp),%rdi
  8acecd:	sub    $0x18,%rdi
  8aced1:	cmp    $0x1423a20,%rdi
  8aced8:	jne    8ae5fa <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x246a>
  8acede:	mov    %rbp,%r12
  8acee1:	add    0x208(%rbx),%r12
  8acee8:	lea    0x110(%rsp),%r14
  8acef0:	mov    $0x1423540,%r8d
  8acef6:	xor    %ecx,%ecx
  8acef8:	mov    %r15,%rdx
  8acefb:	mov    %r14,%rdi
  8acefe:	mov    0x10(%r12),%rsi
  8acf03:	call   556448 <_ZNK4Ogre8Material5cloneERKSsbS2_@plt>
  8acf08:	mov    0x118(%rsp),%rax
  8acf10:	mov    %rax,0x10(%r12)
  8acf15:	mov    0x120(%rsp),%rax
  8acf1d:	movq   $0xfa4590,0x110(%rsp)
  8acf29:	test   %rax,%rax
  8acf2c:	je     8acf47 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xdb7>
  8acf2e:	mov    (%rax),%edx
  8acf30:	sub    $0x1,%edx
  8acf33:	test   %edx,%edx
  8acf35:	mov    %edx,(%rax)
  8acf37:	jne    8acf47 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xdb7>
  8acf39:	mov    0x110(%rsp),%rax
  8acf41:	mov    %r14,%rdi
  8acf44:	call   *0x10(%rax)
  8acf47:	mov    %r15,%rsi
  8acf4a:	mov    %r13,%rdi
  8acf4d:	call   552bc8 <_ZN4Ogre9SubEntity15setMaterialNameERKSs@plt>
  8acf52:	mov    0x208(%rbx),%rax
  8acf59:	xor    %edx,%edx
  8acf5b:	xor    %esi,%esi
  8acf5d:	mov    0x10(%rax,%rbp,1),%rdi
  8acf62:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8acf67:	test   %rax,%rax
  8acf6a:	je     8acf85 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xdf5>
  8acf6c:	mov    %rbp,%r12
  8acf6f:	add    0x208(%rbx),%r12
  8acf76:	mov    0x10(%r12),%rdi
  8acf7b:	call   5540e8 <_ZNK4Ogre8Material13isTransparentEv@plt>
  8acf80:	mov    %al,0x2e(%r12)
  8acf85:	lea    0x290(%rsp),%r13
  8acf8d:	lea    0x469(%rsp),%rdx
  8acf95:	mov    $0xfd11e1,%esi
  8acf9a:	mov    %r13,%rdi
  8acf9d:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8acfa2:	lea    0x280(%rsp),%r12
  8acfaa:	mov    %r13,%rsi
  8acfad:	mov    %r12,%rdi
  8acfb0:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  8acfb5:	mov    %r12,%rsi
  8acfb8:	mov    %r15,%rdi
  8acfbb:	call   554d18 <_ZNSs6assignERKSs@plt>
  8acfc0:	mov    0x280(%rsp),%rdi
  8acfc8:	sub    $0x18,%rdi
  8acfcc:	cmp    $0x1423a20,%rdi
  8acfd3:	jne    8ae702 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2572>
  8acfd9:	mov    0x290(%rsp),%rdi
  8acfe1:	sub    $0x18,%rdi
  8acfe5:	cmp    $0x1423a20,%rdi
  8acfec:	jne    8ae6c6 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2536>
  8acff2:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  8acff7:	mov    (%rax),%r10
  8acffa:	lea    0xf0(%rsp),%r12
  8ad002:	movq   $0x0,(%rsp)
  8ad00a:	xor    %r9d,%r9d
  8ad00d:	xor    %r8d,%r8d
  8ad010:	mov    $0x1424440,%ecx
  8ad015:	mov    %r15,%rdx
  8ad018:	mov    %rax,%rsi
  8ad01b:	mov    %r12,%rdi
  8ad01e:	call   *0x28(%r10)
  8ad022:	mov    0xf8(%rsp),%rax
  8ad02a:	movl   $0x0,0xd8(%rsp)
  8ad035:	movq   $0xfa44d0,0xc0(%rsp)
  8ad041:	mov    %rax,0xc8(%rsp)
  8ad049:	mov    0x100(%rsp),%rax
  8ad051:	test   %rax,%rax
  8ad054:	mov    %rax,0xd0(%rsp)
  8ad05c:	je     8ad069 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xed9>
  8ad05e:	addl   $0x1,(%rax)
  8ad061:	mov    0x100(%rsp),%rax
  8ad069:	test   %rax,%rax
  8ad06c:	movq   $0xfa45d0,0xf0(%rsp)
  8ad078:	je     8ad08d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xefd>
  8ad07a:	mov    (%rax),%edx
  8ad07c:	sub    $0x1,%edx
  8ad07f:	test   %edx,%edx
  8ad081:	mov    %edx,(%rax)
  8ad083:	jne    8ad08d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xefd>
  8ad085:	mov    %r12,%rdi
  8ad088:	call   56ab70 <_ZN4Ogre9SharedPtrINS_8ResourceEE7destroyEv>
  8ad08d:	mov    0x208(%rbx),%rax
  8ad094:	mov    0xc8(%rsp),%rdx
  8ad09c:	xor    %esi,%esi
  8ad09e:	mov    %rdx,0x20(%rax,%rbp,1)
  8ad0a3:	mov    0x208(%rbx),%rax
  8ad0aa:	mov    0x20(%rax,%rbp,1),%rax
  8ad0af:	movb   $0x0,0xf0(%rax)
  8ad0b6:	mov    0x208(%rbx),%rax
  8ad0bd:	mov    0x20(%rax,%rbp,1),%rdi
  8ad0c2:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  8ad0c7:	xor    %esi,%esi
  8ad0c9:	mov    %rax,%rdi
  8ad0cc:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad0d1:	xorps  %xmm2,%xmm2
  8ad0d4:	mov    %rax,%rdi
  8ad0d7:	mov    %rax,%r12
  8ad0da:	movaps %xmm2,%xmm1
  8ad0dd:	movaps %xmm2,%xmm0
  8ad0e0:	call   554cd8 <_ZN4Ogre4Pass19setSelfIlluminationEfff@plt>
  8ad0e5:	lea    0x200(%rsp),%rsi
  8ad0ed:	mov    %r12,%rdi
  8ad0f0:	movl   $0x0,0x200(%rsp)
  8ad0fb:	movl   $0x0,0x204(%rsp)
  8ad106:	movl   $0x0,0x208(%rsp)
  8ad111:	movl   $0x3f800000,0x20c(%rsp)
  8ad11c:	call   556058 <_ZN4Ogre4Pass10setAmbientERKNS_11ColourValueE@plt>
  8ad121:	lea    0x1f0(%rsp),%rsi
  8ad129:	mov    %r12,%rdi
  8ad12c:	movl   $0x0,0x1f0(%rsp)
  8ad137:	movl   $0x0,0x1f4(%rsp)
  8ad142:	movl   $0x0,0x1f8(%rsp)
  8ad14d:	movl   $0x3f800000,0x1fc(%rsp)
  8ad158:	call   555c58 <_ZN4Ogre4Pass10setDiffuseERKNS_11ColourValueE@plt>
  8ad15d:	xor    %esi,%esi
  8ad15f:	mov    %r12,%rdi
  8ad162:	call   5544a8 <_ZN4Ogre4Pass20setDepthWriteEnabledEb@plt>
  8ad167:	mov    0x40(%rsp),%rdi
  8ad16c:	mov    $0x1482e00,%esi
  8ad171:	movq   $0x1423a38,0x90(%rsp)
  8ad17d:	call   5529a8 <_ZNSsC1ERKSs@plt>
  8ad182:	lea    0x90(%rsp),%rdi
  8ad18a:	mov    $0x1482e08,%esi
  8ad18f:	add    $0x10,%rdi
  8ad193:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  8ad198:	lea    0x270(%rsp),%r13
  8ad1a0:	lea    0x468(%rsp),%rdx
  8ad1a8:	mov    $0xfd1230,%esi
  8ad1ad:	movl   $0x4,0xa8(%rsp)
  8ad1b8:	movl   $0x3,0xac(%rsp)
  8ad1c3:	mov    %r13,%rdi
  8ad1c6:	movq   $0x1423a38,0xb0(%rsp)
  8ad1d2:	movb   $0x0,0xb8(%rsp)
  8ad1da:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  8ad1df:	call   e4d250 <_ZN11CFileSystem12getSingletonEv>
  8ad1e4:	lea    0x90(%rsp),%rdx
  8ad1ec:	xor    %r9d,%r9d
  8ad1ef:	mov    $0x1,%r8d
  8ad1f5:	xor    %ecx,%ecx
  8ad1f7:	mov    %r13,%rsi
  8ad1fa:	mov    %rax,%rdi
  8ad1fd:	call   e4e3a0 <_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb>
  8ad202:	mov    0x270(%rsp),%rdi
  8ad20a:	sub    $0x18,%rdi
  8ad20e:	cmp    $0x1424540,%rdi
  8ad215:	jne    8ae747 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x25b7>
  8ad21b:	mov    0x40(%rsp),%rsi
  8ad220:	xor    %edx,%edx
  8ad222:	mov    %r12,%rdi
  8ad225:	call   553b18 <_ZN4Ogre4Pass22createTextureUnitStateERKSst@plt>
  8ad22a:	xor    %esi,%esi
  8ad22c:	mov    %r12,%rdi
  8ad22f:	call   556488 <_ZN4Ogre4Pass24setMaxSimultaneousLightsEt@plt>
  8ad234:	xorps  %xmm1,%xmm1
  8ad237:	mov    $0x1423620,%ecx
  8ad23c:	movss  0x6f75b8(%rip),%xmm2        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  8ad244:	xor    %edx,%edx
  8ad246:	movss  0x6f75da(%rip),%xmm0        # fa4828 <_ZTVN4Ogre13FrameListenerE+0x68>
  8ad24e:	mov    $0x1,%esi
  8ad253:	mov    %r12,%rdi
  8ad256:	call   555258 <_ZN4Ogre4Pass6setFogEbNS_7FogModeERKNS_11ColourValueEfff@plt>
  8ad25b:	xor    %esi,%esi
  8ad25d:	mov    %r12,%rdi
  8ad260:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  8ad265:	mov    $0x1,%edx
  8ad26a:	mov    $0x1,%esi
  8ad26f:	mov    %rax,%rdi
  8ad272:	call   554778 <_ZN4Ogre16TextureUnitState17setEnvironmentMapEbNS0_10EnvMapTypeE@plt>
  8ad277:	mov    0x208(%rbx),%rax
  8ad27e:	xor    %esi,%esi
  8ad280:	mov    0x20(%rax,%rbp,1),%rdi
  8ad285:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  8ad28a:	mov    $0x7,%esi
  8ad28f:	mov    %rax,%rdi
  8ad292:	call   553368 <_ZN4Ogre9Technique16setDepthFunctionENS_15CompareFunctionE@plt>
  8ad297:	mov    0x208(%rbx),%rax
  8ad29e:	xor    %esi,%esi
  8ad2a0:	mov    0x20(%rax,%rbp,1),%rdi
  8ad2a5:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  8ad2aa:	xor    %esi,%esi
  8ad2ac:	mov    %rax,%rdi
  8ad2af:	call   555538 <_ZN4Ogre9Technique20setDepthWriteEnabledEb@plt>
  8ad2b4:	mov    0x208(%rbx),%rax
  8ad2bb:	mov    $0x2,%esi
  8ad2c0:	mov    0x20(%rax,%rbp,1),%rdi
  8ad2c5:	call   555e78 <_ZN4Ogre8Material16setSceneBlendingENS_14SceneBlendTypeE@plt>
  8ad2ca:	mov    %rbp,%rax
  8ad2cd:	add    0x208(%rbx),%rax
  8ad2d4:	cmpb   $0x0,0x2(%rax)
  8ad2d8:	je     8ad351 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11c1>
  8ad2da:	movzwl 0x2c(%rax),%edx
  8ad2de:	test   %dx,%dx
  8ad2e1:	je     8ad351 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11c1>
  8ad2e3:	cmp    $0x2,%dx
  8ad2e7:	je     8add20 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1b90>
  8ad2ed:	cmp    $0x3,%dx
  8ad2f1:	je     8adca0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1b10>
  8ad2f7:	cmp    $0x1,%dx
  8ad2fb:	je     8adc20 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1a90>
  8ad301:	lea    0x230(%rsp),%r13
  8ad309:	lea    0x464(%rsp),%rdx
  8ad311:	mov    $0xfd11e8,%esi
  8ad316:	mov    %r13,%rdi
  8ad319:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ad31e:	mov    $0x1,%edx
  8ad323:	mov    %r13,%rsi
  8ad326:	mov    %r12,%rdi
  8ad329:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ad32e:	mov    0x230(%rsp),%rdi
  8ad336:	sub    $0x18,%rdi
  8ad33a:	cmp    $0x1423a20,%rdi
  8ad341:	jne    8ae944 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x27b4>
  8ad347:	mov    %rbp,%rax
  8ad34a:	add    0x208(%rbx),%rax
  8ad351:	mov    0x20(%rax),%rdi
  8ad355:	mov    $0x1,%esi
  8ad35a:	call   5556d8 <_ZN4Ogre8Material7compileEb@plt>
  8ad35f:	mov    0xb0(%rsp),%rdi
  8ad367:	sub    $0x18,%rdi
  8ad36b:	cmp    $0x1423a20,%rdi
  8ad372:	jne    8aea44 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28b4>
  8ad378:	mov    0xa0(%rsp),%rdi
  8ad380:	mov    $0x1424540,%eax
  8ad385:	sub    $0x18,%rdi
  8ad389:	cmp    %rdi,%rax
  8ad38c:	jne    8ae9d6 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2846>
  8ad392:	mov    0x98(%rsp),%rdi
  8ad39a:	sub    $0x18,%rdi
  8ad39e:	cmp    $0x1423a20,%rdi
  8ad3a5:	jne    8aea02 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2872>
  8ad3ab:	mov    0x90(%rsp),%rdi
  8ad3b3:	sub    $0x18,%rdi
  8ad3b7:	cmp    $0x1423a20,%rdi
  8ad3be:	jne    8ae914 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2784>
  8ad3c4:	mov    0xd0(%rsp),%rax
  8ad3cc:	movq   $0xfa4590,0xc0(%rsp)
  8ad3d8:	test   %rax,%rax
  8ad3db:	je     8ad3fb <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x126b>
  8ad3dd:	mov    (%rax),%edx
  8ad3df:	sub    $0x1,%edx
  8ad3e2:	test   %edx,%edx
  8ad3e4:	mov    %edx,(%rax)
  8ad3e6:	jne    8ad3fb <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x126b>
  8ad3e8:	mov    0xc0(%rsp),%rax
  8ad3f0:	lea    0xc0(%rsp),%rdi
  8ad3f8:	call   *0x10(%rax)
  8ad3fb:	mov    0x2b0(%rsp),%rdi
  8ad403:	sub    $0x18,%rdi
  8ad407:	cmp    $0x1423a20,%rdi
  8ad40e:	je     8acc6a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xada>
  8ad414:	mov    $0x5541c8,%eax
  8ad419:	test   %rax,%rax
  8ad41c:	je     8ae995 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2805>
  8ad422:	or     $0xffffffff,%eax
  8ad425:	lock xadd %eax,0x10(%rdi)
  8ad42a:	test   %eax,%eax
  8ad42c:	jg     8acc6a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xada>
  8ad432:	lea    0x441(%rsp),%rsi
  8ad43a:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ad43f:	jmp    8acc6a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xada>
  8ad444:	nopl   0x0(%rax)
  8ad448:	mov    %rbp,%r14
  8ad44b:	add    0x208(%rbx),%r14
  8ad452:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  8ad457:	mov    (%rax),%rcx
  8ad45a:	mov    %r15,%rdx
  8ad45d:	mov    %rax,%rsi
  8ad460:	lea    0x170(%rsp),%rdi
  8ad468:	call   *0xa0(%rcx)
  8ad46e:	mov    0x178(%rsp),%rax
  8ad476:	mov    %rax,0x18(%r14)
  8ad47a:	mov    0x180(%rsp),%rax
  8ad482:	movq   $0xfa45d0,0x170(%rsp)
  8ad48e:	test   %rax,%rax
  8ad491:	je     8ad4ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x131b>
  8ad493:	mov    (%rax),%edx
  8ad495:	sub    $0x1,%edx
  8ad498:	test   %edx,%edx
  8ad49a:	mov    %edx,(%rax)
  8ad49c:	jne    8ad4ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x131b>
  8ad49e:	lea    0x170(%rsp),%rdi
  8ad4a6:	call   56ab70 <_ZN4Ogre9SharedPtrINS_8ResourceEE7destroyEv>
  8ad4ab:	movb   $0x0,0x18(%rsp)
  8ad4b0:	jmp    8acd80 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xbf0>
  8ad4b5:	nopl   (%rax)
  8ad4b8:	mov    0x208(%rbx),%r11
  8ad4bf:	add    %rbp,%r11
  8ad4c2:	mov    %r11,0x18(%rsp)
  8ad4c7:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  8ad4cc:	mov    (%rax),%rcx
  8ad4cf:	lea    0x1b0(%rsp),%r14
  8ad4d7:	mov    %r15,%rdx
  8ad4da:	mov    %rax,%rsi
  8ad4dd:	mov    %r14,%rdi
  8ad4e0:	call   *0xa0(%rcx)
  8ad4e6:	mov    0x1b8(%rsp),%rax
  8ad4ee:	mov    0x18(%rsp),%rdx
  8ad4f3:	mov    %rax,0x18(%rdx)
  8ad4f7:	mov    0x1c0(%rsp),%rax
  8ad4ff:	movq   $0xfa45d0,0x1b0(%rsp)
  8ad50b:	test   %rax,%rax
  8ad50e:	je     8ad523 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1393>
  8ad510:	mov    (%rax),%edx
  8ad512:	sub    $0x1,%edx
  8ad515:	test   %edx,%edx
  8ad517:	mov    %edx,(%rax)
  8ad519:	jne    8ad523 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1393>
  8ad51b:	mov    %r14,%rdi
  8ad51e:	call   56ab70 <_ZN4Ogre9SharedPtrINS_8ResourceEE7destroyEv>
  8ad523:	movb   $0x0,0x18(%rsp)
  8ad528:	jmp    8acb1f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x98f>
  8ad52d:	mov    0x208(%rbx),%rax
  8ad534:	xor    %edx,%edx
  8ad536:	xor    %esi,%esi
  8ad538:	mov    0x10(%rax,%rbp,1),%rdi
  8ad53d:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad542:	xor    %esi,%esi
  8ad544:	mov    %rax,%rdi
  8ad547:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad54c:	mov    %rax,%r14
  8ad54f:	mov    0x208(%rbx),%rax
  8ad556:	movzbl 0x2(%rax,%rbp,1),%eax
  8ad55b:	mov    %al,0x28(%rsp)
  8ad55f:	cmpq   $0x0,0x100(%r14)
  8ad567:	je     8ada92 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1902>
  8ad56d:	mov    %r14,%rdi
  8ad570:	call   552fa8 <_ZNK4Ogre4Pass16getVertexProgramEv@plt>
  8ad575:	mov    0x8(%rax),%rdi
  8ad579:	mov    (%rdi),%rax
  8ad57c:	call   *0x1c8(%rax)
  8ad582:	test   %al,%al
  8ad584:	je     8ada92 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1902>
  8ad58a:	mov    0x208(%rbx),%rax
  8ad591:	movb   $0x1,0x2(%rax,%rbp,1)
  8ad596:	mov    0x30(%rsp),%rdi
  8ad59b:	call   555158 <_ZNK4Ogre6Entity7getMeshEv@plt>
  8ad5a0:	mov    0x8(%rax),%rdi
  8ad5a4:	call   555468 <_ZNK4Ogre4Mesh21getMaxBoneAssignmentsEv@plt>
  8ad5a9:	mov    0x208(%rbx),%rdx
  8ad5b0:	mov    %ax,0x2c(%rdx,%rbp,1)
  8ad5b5:	mov    %rbp,%rax
  8ad5b8:	add    0x208(%rbx),%rax
  8ad5bf:	cmpb   $0x0,0x2(%rax)
  8ad5c3:	je     8acc1c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa8c>
  8ad5c9:	cmpb   $0x0,0x18(%rsp)
  8ad5ce:	je     8acc1c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa8c>
  8ad5d4:	movzwl 0x2c(%rax),%edx
  8ad5d8:	test   %dx,%dx
  8ad5db:	je     8acc1c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa8c>
  8ad5e1:	cmpb   $0x0,0x28(%rsp)
  8ad5e6:	jne    8acc1c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa8c>
  8ad5ec:	cmp    $0x2,%dx
  8ad5f0:	je     8adf30 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1da0>
  8ad5f6:	cmp    $0x3,%dx
  8ad5fa:	je     8ade88 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1cf8>
  8ad600:	cmp    $0x1,%dx
  8ad604:	je     8adde5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1c55>
  8ad60a:	cmp    $0x1,%r12d
  8ad60e:	jle    8ae0ac <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1f1c>
  8ad614:	lea    0x2e0(%rsp),%r12
  8ad61c:	lea    0x46c(%rsp),%rdx
  8ad624:	mov    $0xfd13c0,%esi
  8ad629:	mov    %r12,%rdi
  8ad62c:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ad631:	mov    0x208(%rbx),%rax
  8ad638:	xor    %edx,%edx
  8ad63a:	xor    %esi,%esi
  8ad63c:	mov    0x18(%rax,%rbp,1),%rdi
  8ad641:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad646:	xor    %esi,%esi
  8ad648:	mov    %rax,%rdi
  8ad64b:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad650:	mov    $0x1,%edx
  8ad655:	mov    %r12,%rsi
  8ad658:	mov    %rax,%rdi
  8ad65b:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ad660:	mov    0x2e0(%rsp),%rdi
  8ad668:	sub    $0x18,%rdi
  8ad66c:	cmp    $0x1423a20,%rdi
  8ad673:	jne    8aec7e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2aee>
  8ad679:	lea    0x2c0(%rsp),%r12
  8ad681:	lea    0x46a(%rsp),%rdx
  8ad689:	mov    $0xfd111e,%esi
  8ad68e:	mov    %r12,%rdi
  8ad691:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ad696:	mov    0x208(%rbx),%rax
  8ad69d:	xor    %edx,%edx
  8ad69f:	xor    %esi,%esi
  8ad6a1:	mov    0x18(%rax,%rbp,1),%rdi
  8ad6a6:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad6ab:	xor    %esi,%esi
  8ad6ad:	mov    %rax,%rdi
  8ad6b0:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad6b5:	lea    0x130(%rsp),%r14
  8ad6bd:	mov    %rax,%rsi
  8ad6c0:	mov    %r14,%rdi
  8ad6c3:	call   552cb8 <_ZNK4Ogre4Pass26getVertexProgramParametersEv@plt>
  8ad6c8:	mov    0x138(%rsp),%rdi
  8ad6d0:	xor    %ecx,%ecx
  8ad6d2:	mov    $0x79,%edx
  8ad6d7:	mov    %r12,%rsi
  8ad6da:	call   554468 <_ZN4Ogre20GpuProgramParameters20setNamedAutoConstantERKSsNS0_16AutoConstantTypeEm@plt>
  8ad6df:	mov    0x140(%rsp),%rax
  8ad6e7:	movq   $0xfd1950,0x130(%rsp)
  8ad6f3:	test   %rax,%rax
  8ad6f6:	je     8ad70b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x157b>
  8ad6f8:	mov    (%rax),%edx
  8ad6fa:	sub    $0x1,%edx
  8ad6fd:	test   %edx,%edx
  8ad6ff:	mov    %edx,(%rax)
  8ad701:	jne    8ad70b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x157b>
  8ad703:	mov    %r14,%rdi
  8ad706:	call   8b2a00 <_ZN4Ogre9SharedPtrINS_20GpuProgramParametersEE7destroyEv>
  8ad70b:	mov    0x2c0(%rsp),%rdi
  8ad713:	sub    $0x18,%rdi
  8ad717:	cmp    $0x1423a20,%rdi
  8ad71e:	jne    8aec2d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2a9d>
  8ad724:	mov    0x208(%rbx),%rax
  8ad72b:	mov    $0x1,%esi
  8ad730:	mov    0x18(%rax,%rbp,1),%rdi
  8ad735:	call   5556d8 <_ZN4Ogre8Material7compileEb@plt>
  8ad73a:	jmp    8acc12 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa82>
  8ad73f:	xor    %edx,%edx
  8ad741:	xor    %esi,%esi
  8ad743:	mov    %r14,%rdi
  8ad746:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad74b:	xor    %esi,%esi
  8ad74d:	mov    %rax,%rdi
  8ad750:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad755:	cmpq   $0x0,0x100(%rax)
  8ad75d:	je     8ad7bd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x162d>
  8ad75f:	lea    0x47e(%rsp),%rdx
  8ad767:	lea    0x410(%rsp),%rdi
  8ad76f:	mov    $0x10257f7,%esi
  8ad774:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ad779:	xor    %edx,%edx
  8ad77b:	xor    %esi,%esi
  8ad77d:	mov    %r14,%rdi
  8ad780:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad785:	xor    %esi,%esi
  8ad787:	mov    %rax,%rdi
  8ad78a:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad78f:	lea    0x410(%rsp),%rsi
  8ad797:	mov    $0x1,%edx
  8ad79c:	mov    %rax,%rdi
  8ad79f:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ad7a4:	mov    0x410(%rsp),%rdi
  8ad7ac:	sub    $0x18,%rdi
  8ad7b0:	cmp    $0x1423a20,%rdi
  8ad7b7:	jne    8ae798 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2608>
  8ad7bd:	mov    0x208(%rbx),%rax
  8ad7c4:	cmpb   $0x0,0x2f(%rax,%rbp,1)
  8ad7c9:	jne    8adda0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1c10>
  8ad7cf:	cmpb   $0x0,0x238(%rbx)
  8ad7d6:	je     8ad889 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x16f9>
  8ad7dc:	lea    -0x1(%r12),%eax
  8ad7e1:	movl   $0x1,0x28(%rsp)
  8ad7e9:	test   %eax,%eax
  8ad7eb:	cmovle 0x28(%rsp),%eax
  8ad7f0:	mov    %eax,0x28(%rsp)
  8ad7f4:	jmp    8ad854 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x16c4>
  8ad7f6:	cs nopw 0x0(%rax,%rax,1)
  8ad800:	xor    %edx,%edx
  8ad802:	xor    %esi,%esi
  8ad804:	mov    %r14,%rdi
  8ad807:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad80c:	xor    %esi,%esi
  8ad80e:	mov    %rax,%rdi
  8ad811:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad816:	mov    0xf0(%rax),%rdx
  8ad81d:	sub    0xe8(%rax),%rdx
  8ad824:	xor    %esi,%esi
  8ad826:	mov    %r14,%rdi
  8ad829:	sar    $0x3,%rdx
  8ad82d:	sub    $0x1,%edx
  8ad830:	movzwl %dx,%edx
  8ad833:	mov    %edx,0x18(%rsp)
  8ad837:	xor    %edx,%edx
  8ad839:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad83e:	xor    %esi,%esi
  8ad840:	mov    %rax,%rdi
  8ad843:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad848:	mov    0x18(%rsp),%esi
  8ad84c:	mov    %rax,%rdi
  8ad84f:	call   552998 <_ZN4Ogre4Pass22removeTextureUnitStateEt@plt>
  8ad854:	xor    %edx,%edx
  8ad856:	xor    %esi,%esi
  8ad858:	mov    %r14,%rdi
  8ad85b:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad860:	xor    %esi,%esi
  8ad862:	mov    %rax,%rdi
  8ad865:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad86a:	mov    0xf0(%rax),%rdx
  8ad871:	sub    0xe8(%rax),%rdx
  8ad878:	sar    $0x3,%rdx
  8ad87c:	movzwl %dx,%edx
  8ad87f:	cmp    0x28(%rsp),%edx
  8ad883:	jg     8ad800 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1670>
  8ad889:	xor    %edx,%edx
  8ad88b:	xor    %esi,%esi
  8ad88d:	mov    %r14,%rdi
  8ad890:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ad895:	xor    %esi,%esi
  8ad897:	mov    %rax,%rdi
  8ad89a:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ad89f:	mov    %rax,%rdi
  8ad8a2:	call   553878 <_ZN4Ogre4Pass22createTextureUnitStateEv@plt>
  8ad8a7:	mov    0x48(%rsp),%rdi
  8ad8ac:	mov    $0x1482e00,%esi
  8ad8b1:	mov    %rax,%r14
  8ad8b4:	movq   $0x1423a38,0xc0(%rsp)
  8ad8c0:	call   5529a8 <_ZNSsC1ERKSs@plt>
  8ad8c5:	lea    0xc0(%rsp),%rdi
  8ad8cd:	mov    $0x1482e08,%esi
  8ad8d2:	add    $0x10,%rdi
  8ad8d6:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  8ad8db:	lea    0x47d(%rsp),%rdx
  8ad8e3:	lea    0x400(%rsp),%rdi
  8ad8eb:	mov    $0xfcb208,%esi
  8ad8f0:	movl   $0x4,0xd8(%rsp)
  8ad8fb:	movl   $0x3,0xdc(%rsp)
  8ad906:	movq   $0x1423a38,0xe0(%rsp)
  8ad912:	movb   $0x0,0xe8(%rsp)
  8ad91a:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  8ad91f:	call   e4d250 <_ZN11CFileSystem12getSingletonEv>
  8ad924:	lea    0xc0(%rsp),%rdx
  8ad92c:	lea    0x400(%rsp),%rsi
  8ad934:	xor    %r9d,%r9d
  8ad937:	mov    $0x1,%r8d
  8ad93d:	xor    %ecx,%ecx
  8ad93f:	mov    %rax,%rdi
  8ad942:	call   e4e3a0 <_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb>
  8ad947:	mov    0x400(%rsp),%rdi
  8ad94f:	sub    $0x18,%rdi
  8ad953:	cmp    $0x1424540,%rdi
  8ad95a:	jne    8ae821 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2691>
  8ad960:	mov    0x48(%rsp),%rsi
  8ad965:	mov    $0x1,%edx
  8ad96a:	mov    %r14,%rdi
  8ad96d:	call   553b98 <_ZN4Ogre16TextureUnitState19setCubicTextureNameERKSsb@plt>
  8ad972:	mov    $0x1,%esi
  8ad977:	mov    %r14,%rdi
  8ad97a:	call   554a08 <_ZN4Ogre16TextureUnitState18setTextureCoordSetEj@plt>
  8ad97f:	mov    $0x2,%esi
  8ad984:	mov    %r14,%rdi
  8ad987:	call   553d28 <_ZN4Ogre16TextureUnitState24setTextureAddressingModeENS0_21TextureAddressingModeE@plt>
  8ad98c:	mov    $0x3,%edx
  8ad991:	mov    $0x1,%esi
  8ad996:	mov    %r14,%rdi
  8ad999:	call   554778 <_ZN4Ogre16TextureUnitState17setEnvironmentMapEbNS0_10EnvMapTypeE@plt>
  8ad99e:	mov    $0x1,%esi
  8ad9a3:	mov    %r14,%rdi
  8ad9a6:	call   5563b8 <_ZN4Ogre16TextureUnitState18setColourOperationENS_19LayerBlendOperationE@plt>
  8ad9ab:	mov    0xe0(%rsp),%rdi
  8ad9b3:	sub    $0x18,%rdi
  8ad9b7:	cmp    $0x1423a20,%rdi
  8ad9be:	jne    8ae85a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x26ca>
  8ad9c4:	mov    0xd0(%rsp),%rdi
  8ad9cc:	mov    $0x1424540,%eax
  8ad9d1:	sub    $0x18,%rdi
  8ad9d5:	cmp    %rdi,%rax
  8ad9d8:	jne    8ae886 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x26f6>
  8ad9de:	mov    0xc8(%rsp),%rdi
  8ad9e6:	sub    $0x18,%rdi
  8ad9ea:	cmp    $0x1423a20,%rdi
  8ad9f1:	jne    8ae8c8 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2738>
  8ad9f7:	mov    0xc0(%rsp),%rdi
  8ad9ff:	sub    $0x18,%rdi
  8ada03:	cmp    $0x1423a20,%rdi
  8ada0a:	je     8acb1a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x98a>
  8ada10:	mov    $0x5541c8,%eax
  8ada15:	test   %rax,%rax
  8ada18:	je     8aea8e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28fe>
  8ada1e:	or     $0xffffffff,%eax
  8ada21:	lock xadd %eax,0x10(%rdi)
  8ada26:	test   %eax,%eax
  8ada28:	jg     8acb1a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x98a>
  8ada2e:	lea    0x458(%rsp),%rsi
  8ada36:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ada3b:	movb   $0x1,0x18(%rsp)
  8ada40:	jmp    8acb1f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x98f>
  8ada45:	nopl   (%rax)
  8ada48:	xor    %edx,%edx
  8ada4a:	xor    %esi,%esi
  8ada4c:	mov    %r14,%rdi
  8ada4f:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ada54:	xor    %esi,%esi
  8ada56:	mov    %rax,%rdi
  8ada59:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ada5e:	xor    %esi,%esi
  8ada60:	mov    %rax,%rdi
  8ada63:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  8ada68:	xorps  %xmm0,%xmm0
  8ada6b:	mov    $0x1423620,%r9d
  8ada71:	mov    %r9,%r8
  8ada74:	xor    %ecx,%ecx
  8ada76:	mov    $0x1,%edx
  8ada7b:	mov    $0x3,%esi
  8ada80:	mov    %rax,%rdi
  8ada83:	call   554a58 <_ZN4Ogre16TextureUnitState20setColourOperationExENS_21LayerBlendOperationExENS_16LayerBlendSourceES2_RKNS_11ColourValueES5_f@plt>
  8ada88:	movb   $0x1,0x18(%rsp)
  8ada8d:	jmp    8acd80 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xbf0>
  8ada92:	cmpq   $0x0,0x130(%rbx)
  8ada9a:	je     8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adaa0:	cmpb   $0x0,0x1e9(%rbx)
  8adaa7:	je     8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adaad:	cmpb   $0x0,0x28(%rsp)
  8adab2:	jne    8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adab8:	mov    0x30(%rsp),%rdi
  8adabd:	call   555158 <_ZNK4Ogre6Entity7getMeshEv@plt>
  8adac2:	mov    0x8(%rax),%rdi
  8adac6:	call   555468 <_ZNK4Ogre4Mesh21getMaxBoneAssignmentsEv@plt>
  8adacb:	mov    %eax,%edx
  8adacd:	mov    0x208(%rbx),%rax
  8adad4:	test   %dx,%dx
  8adad7:	mov    %dx,0x2c(%rax,%rbp,1)
  8adadc:	je     8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adae2:	cmp    $0x2,%dx
  8adae6:	je     8ae1f4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2064>
  8adaec:	cmp    $0x3,%dx
  8adaf0:	je     8ae1a9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2019>
  8adaf6:	cmp    $0x1,%dx
  8adafa:	je     8ae15e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1fce>
  8adb00:	cmp    $0x1,%r12d
  8adb04:	jle    8ae38f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x21ff>
  8adb0a:	lea    0x475(%rsp),%rdx
  8adb12:	lea    0x370(%rsp),%rdi
  8adb1a:	mov    $0xfd13c0,%esi
  8adb1f:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adb24:	lea    0x370(%rsp),%rsi
  8adb2c:	mov    $0x1,%edx
  8adb31:	mov    %r14,%rdi
  8adb34:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8adb39:	lea    0x370(%rsp),%rdi
  8adb41:	call   556288 <_ZNSsD1Ev@plt>
  8adb46:	lea    0x473(%rsp),%rdx
  8adb4e:	lea    0x350(%rsp),%rdi
  8adb56:	mov    $0xfd111e,%esi
  8adb5b:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adb60:	lea    0x150(%rsp),%rdi
  8adb68:	mov    %r14,%rsi
  8adb6b:	call   552cb8 <_ZNK4Ogre4Pass26getVertexProgramParametersEv@plt>
  8adb70:	mov    0x158(%rsp),%rdi
  8adb78:	lea    0x350(%rsp),%rsi
  8adb80:	xor    %ecx,%ecx
  8adb82:	mov    $0x79,%edx
  8adb87:	call   554468 <_ZN4Ogre20GpuProgramParameters20setNamedAutoConstantERKSsNS0_16AutoConstantTypeEm@plt>
  8adb8c:	lea    0x150(%rsp),%rdi
  8adb94:	call   8b1040 <_ZN4Ogre9SharedPtrINS_20GpuProgramParametersEED1Ev>
  8adb99:	lea    0x350(%rsp),%rdi
  8adba1:	call   556288 <_ZNSsD1Ev@plt>
  8adba6:	mov    0x208(%rbx),%rax
  8adbad:	mov    $0x1,%esi
  8adbb2:	mov    0x10(%rax,%rbp,1),%rdi
  8adbb7:	call   5556d8 <_ZN4Ogre8Material7compileEb@plt>
  8adbbc:	mov    0x208(%rbx),%rax
  8adbc3:	xor    %edx,%edx
  8adbc5:	xor    %esi,%esi
  8adbc7:	mov    0x10(%rax,%rbp,1),%rdi
  8adbcc:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8adbd1:	xor    %esi,%esi
  8adbd3:	mov    %rax,%rdi
  8adbd6:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8adbdb:	cmpq   $0x0,0x100(%rax)
  8adbe3:	je     8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adbe9:	mov    %rax,%rdi
  8adbec:	call   552fa8 <_ZNK4Ogre4Pass16getVertexProgramEv@plt>
  8adbf1:	mov    0x8(%rax),%rdi
  8adbf5:	mov    (%rdi),%rax
  8adbf8:	call   *0x1c8(%rax)
  8adbfe:	test   %al,%al
  8adc00:	je     8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adc06:	mov    0x208(%rbx),%rax
  8adc0d:	movb   $0x1,0x2(%rax,%rbp,1)
  8adc12:	jmp    8ad5b5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1425>
  8adc17:	nopw   0x0(%rax,%rax,1)
  8adc20:	lea    0x240(%rsp),%r13
  8adc28:	lea    0x465(%rsp),%rdx
  8adc30:	mov    $0xfd1428,%esi
  8adc35:	mov    %r13,%rdi
  8adc38:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adc3d:	mov    $0x1,%edx
  8adc42:	mov    %r13,%rsi
  8adc45:	mov    %r12,%rdi
  8adc48:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8adc4d:	mov    0x240(%rsp),%rdi
  8adc55:	sub    $0x18,%rdi
  8adc59:	cmp    $0x1423a20,%rdi
  8adc60:	je     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8adc66:	mov    $0x5541c8,%eax
  8adc6b:	test   %rax,%rax
  8adc6e:	je     8ae9a5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2815>
  8adc74:	or     $0xffffffff,%eax
  8adc77:	lock xadd %eax,0x10(%rdi)
  8adc7c:	test   %eax,%eax
  8adc7e:	jg     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8adc84:	lea    0x447(%rsp),%rsi
  8adc8c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8adc91:	mov    %rbp,%rax
  8adc94:	add    0x208(%rbx),%rax
  8adc9b:	jmp    8ad351 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11c1>
  8adca0:	lea    0x260(%rsp),%r13
  8adca8:	lea    0x467(%rsp),%rdx
  8adcb0:	mov    $0xfd13e0,%esi
  8adcb5:	mov    %r13,%rdi
  8adcb8:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adcbd:	mov    $0x1,%edx
  8adcc2:	mov    %r13,%rsi
  8adcc5:	mov    %r12,%rdi
  8adcc8:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8adccd:	mov    0x260(%rsp),%rdi
  8adcd5:	sub    $0x18,%rdi
  8adcd9:	cmp    $0x1423a20,%rdi
  8adce0:	je     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8adce6:	mov    $0x5541c8,%eax
  8adceb:	test   %rax,%rax
  8adcee:	je     8aeaa1 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2911>
  8adcf4:	or     $0xffffffff,%eax
  8adcf7:	lock xadd %eax,0x10(%rdi)
  8adcfc:	test   %eax,%eax
  8adcfe:	jg     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8add04:	lea    0x449(%rsp),%rsi
  8add0c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8add11:	mov    %rbp,%rax
  8add14:	add    0x208(%rbx),%rax
  8add1b:	jmp    8ad351 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11c1>
  8add20:	lea    0x250(%rsp),%r13
  8add28:	lea    0x466(%rsp),%rdx
  8add30:	mov    $0xfd1408,%esi
  8add35:	mov    %r13,%rdi
  8add38:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8add3d:	mov    $0x1,%edx
  8add42:	mov    %r13,%rsi
  8add45:	mov    %r12,%rdi
  8add48:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8add4d:	mov    0x250(%rsp),%rdi
  8add55:	sub    $0x18,%rdi
  8add59:	cmp    $0x1423a20,%rdi
  8add60:	je     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8add66:	mov    $0x5541c8,%eax
  8add6b:	test   %rax,%rax
  8add6e:	je     8ae9c8 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2838>
  8add74:	or     $0xffffffff,%eax
  8add77:	lock xadd %eax,0x10(%rdi)
  8add7c:	test   %eax,%eax
  8add7e:	jg     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8add84:	lea    0x448(%rsp),%rsi
  8add8c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8add91:	mov    %rbp,%rax
  8add94:	add    0x208(%rbx),%rax
  8add9b:	jmp    8ad351 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11c1>
  8adda0:	xor    %edx,%edx
  8adda2:	xor    %esi,%esi
  8adda4:	mov    %r14,%rdi
  8adda7:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8addac:	xor    %esi,%esi
  8addae:	mov    %rax,%rdi
  8addb1:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8addb6:	xor    %esi,%esi
  8addb8:	mov    %rax,%rdi
  8addbb:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  8addc0:	xorps  %xmm0,%xmm0
  8addc3:	mov    $0x1423620,%r9d
  8addc9:	mov    %r9,%r8
  8addcc:	xor    %ecx,%ecx
  8addce:	mov    $0x1,%edx
  8addd3:	mov    $0x4,%esi
  8addd8:	mov    %rax,%rdi
  8adddb:	call   554a58 <_ZN4Ogre16TextureUnitState20setColourOperationExENS_21LayerBlendOperationExENS_16LayerBlendSourceES2_RKNS_11ColourValueES5_f@plt>
  8adde0:	jmp    8acb1a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x98a>
  8adde5:	cmp    $0x1,%r12d
  8adde9:	jle    8adffa <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1e6a>
  8addef:	lea    0x300(%rsp),%r12
  8addf7:	lea    0x46e(%rsp),%rdx
  8addff:	mov    $0xfd1398,%esi
  8ade04:	mov    %r12,%rdi
  8ade07:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ade0c:	mov    0x208(%rbx),%rax
  8ade13:	xor    %edx,%edx
  8ade15:	xor    %esi,%esi
  8ade17:	mov    0x18(%rax,%rbp,1),%rdi
  8ade1c:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ade21:	xor    %esi,%esi
  8ade23:	mov    %rax,%rdi
  8ade26:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ade2b:	mov    $0x1,%edx
  8ade30:	mov    %r12,%rsi
  8ade33:	mov    %rax,%rdi
  8ade36:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ade3b:	mov    0x300(%rsp),%rdi
  8ade43:	sub    $0x18,%rdi
  8ade47:	cmp    $0x1423a20,%rdi
  8ade4e:	je     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ade54:	mov    $0x5541c8,%eax
  8ade59:	test   %rax,%rax
  8ade5c:	je     8aec05 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2a75>
  8ade62:	or     $0xffffffff,%eax
  8ade65:	lock xadd %eax,0x10(%rdi)
  8ade6a:	test   %eax,%eax
  8ade6c:	jg     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ade72:	lea    0x451(%rsp),%rsi
  8ade7a:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ade7f:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ade84:	nopl   0x0(%rax)
  8ade88:	cmp    $0x1,%r12d
  8ade8c:	jle    8ae053 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ec3>
  8ade92:	lea    0x340(%rsp),%r12
  8ade9a:	lea    0x472(%rsp),%rdx
  8adea2:	mov    $0xfd1348,%esi
  8adea7:	mov    %r12,%rdi
  8adeaa:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adeaf:	mov    0x208(%rbx),%rax
  8adeb6:	xor    %edx,%edx
  8adeb8:	xor    %esi,%esi
  8adeba:	mov    0x18(%rax,%rbp,1),%rdi
  8adebf:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8adec4:	xor    %esi,%esi
  8adec6:	mov    %rax,%rdi
  8adec9:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8adece:	mov    $0x1,%edx
  8aded3:	mov    %r12,%rsi
  8aded6:	mov    %rax,%rdi
  8aded9:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8adede:	mov    0x340(%rsp),%rdi
  8adee6:	sub    $0x18,%rdi
  8adeea:	cmp    $0x1423a20,%rdi
  8adef1:	je     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adef7:	mov    $0x5541c8,%eax
  8adefc:	test   %rax,%rax
  8adeff:	je     8aec1a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2a8a>
  8adf05:	or     $0xffffffff,%eax
  8adf08:	lock xadd %eax,0x10(%rdi)
  8adf0d:	test   %eax,%eax
  8adf0f:	jg     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adf15:	lea    0x453(%rsp),%rsi
  8adf1d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8adf22:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adf27:	nopw   0x0(%rax,%rax,1)
  8adf30:	cmp    $0x1,%r12d
  8adf34:	jle    8ae105 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1f75>
  8adf3a:	lea    0x320(%rsp),%r12
  8adf42:	lea    0x470(%rsp),%rdx
  8adf4a:	mov    $0xfd1370,%esi
  8adf4f:	mov    %r12,%rdi
  8adf52:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8adf57:	mov    0x208(%rbx),%rax
  8adf5e:	xor    %edx,%edx
  8adf60:	xor    %esi,%esi
  8adf62:	mov    0x18(%rax,%rbp,1),%rdi
  8adf67:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8adf6c:	xor    %esi,%esi
  8adf6e:	mov    %rax,%rdi
  8adf71:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8adf76:	mov    $0x1,%edx
  8adf7b:	mov    %r12,%rsi
  8adf7e:	mov    %rax,%rdi
  8adf81:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8adf86:	mov    0x320(%rsp),%rdi
  8adf8e:	sub    $0x18,%rdi
  8adf92:	cmp    $0x1423a20,%rdi
  8adf99:	je     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adf9f:	mov    $0x5541c8,%eax
  8adfa4:	test   %rax,%rax
  8adfa7:	je     8aebde <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2a4e>
  8adfad:	or     $0xffffffff,%eax
  8adfb0:	lock xadd %eax,0x10(%rdi)
  8adfb5:	test   %eax,%eax
  8adfb7:	jg     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adfbd:	lea    0x452(%rsp),%rsi
  8adfc5:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8adfca:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8adfcf:	mov    %rax,0x230(%rbx)
  8adfd6:	jmp    8ac1d9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x49>
  8adfdb:	lea    0x50(%rsp),%rbp
  8adfe0:	lea    0x208(%rbx),%rdi
  8adfe7:	sub    %rax,%rdx
  8adfea:	mov    %r12,%rsi
  8adfed:	mov    %rbp,%rcx
  8adff0:	call   8b4f20 <_ZNSt6vectorI17CRenderableStatesSaIS0_EE14_M_fill_insertEN9__gnu_cxx17__normal_iteratorIPS0_S2_EEmRKS0_>
  8adff5:	jmp    8ac7f5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x665>
  8adffa:	lea    0x2f0(%rsp),%r12
  8ae002:	lea    0x46d(%rsp),%rdx
  8ae00a:	mov    $0xfd119b,%esi
  8ae00f:	mov    %r12,%rdi
  8ae012:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae017:	mov    0x208(%rbx),%rax
  8ae01e:	xor    %edx,%edx
  8ae020:	xor    %esi,%esi
  8ae022:	mov    0x18(%rax,%rbp,1),%rdi
  8ae027:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ae02c:	xor    %esi,%esi
  8ae02e:	mov    %rax,%rdi
  8ae031:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ae036:	mov    $0x1,%edx
  8ae03b:	mov    %r12,%rsi
  8ae03e:	mov    %rax,%rdi
  8ae041:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae046:	mov    %r12,%rdi
  8ae049:	call   556288 <_ZNSsD1Ev@plt>
  8ae04e:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ae053:	lea    0x330(%rsp),%r12
  8ae05b:	lea    0x471(%rsp),%rdx
  8ae063:	mov    $0xfd1167,%esi
  8ae068:	mov    %r12,%rdi
  8ae06b:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae070:	mov    0x208(%rbx),%rax
  8ae077:	xor    %edx,%edx
  8ae079:	xor    %esi,%esi
  8ae07b:	mov    0x18(%rax,%rbp,1),%rdi
  8ae080:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ae085:	xor    %esi,%esi
  8ae087:	mov    %rax,%rdi
  8ae08a:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ae08f:	mov    $0x1,%edx
  8ae094:	mov    %r12,%rsi
  8ae097:	mov    %rax,%rdi
  8ae09a:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae09f:	mov    %r12,%rdi
  8ae0a2:	call   556288 <_ZNSsD1Ev@plt>
  8ae0a7:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ae0ac:	lea    0x2d0(%rsp),%r12
  8ae0b4:	lea    0x46b(%rsp),%rdx
  8ae0bc:	mov    $0xfd11b4,%esi
  8ae0c1:	mov    %r12,%rdi
  8ae0c4:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae0c9:	mov    0x208(%rbx),%rax
  8ae0d0:	xor    %edx,%edx
  8ae0d2:	xor    %esi,%esi
  8ae0d4:	mov    0x18(%rax,%rbp,1),%rdi
  8ae0d9:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ae0de:	xor    %esi,%esi
  8ae0e0:	mov    %rax,%rdi
  8ae0e3:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ae0e8:	mov    $0x1,%edx
  8ae0ed:	mov    %r12,%rsi
  8ae0f0:	mov    %rax,%rdi
  8ae0f3:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae0f8:	mov    %r12,%rdi
  8ae0fb:	call   556288 <_ZNSsD1Ev@plt>
  8ae100:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ae105:	lea    0x310(%rsp),%r12
  8ae10d:	lea    0x46f(%rsp),%rdx
  8ae115:	mov    $0xfd1182,%esi
  8ae11a:	mov    %r12,%rdi
  8ae11d:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae122:	mov    0x208(%rbx),%rax
  8ae129:	xor    %edx,%edx
  8ae12b:	xor    %esi,%esi
  8ae12d:	mov    0x18(%rax,%rbp,1),%rdi
  8ae132:	call   552f48 <_ZN4Ogre8Material16getBestTechniqueEtPKNS_10RenderableE@plt>
  8ae137:	xor    %esi,%esi
  8ae139:	mov    %rax,%rdi
  8ae13c:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  8ae141:	mov    $0x1,%edx
  8ae146:	mov    %r12,%rsi
  8ae149:	mov    %rax,%rdi
  8ae14c:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae151:	mov    %r12,%rdi
  8ae154:	call   556288 <_ZNSsD1Ev@plt>
  8ae159:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8ae15e:	cmp    $0x1,%r12d
  8ae162:	jle    8ae2e3 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2153>
  8ae168:	lea    0x477(%rsp),%rdx
  8ae170:	lea    0x390(%rsp),%rdi
  8ae178:	mov    $0xfd1398,%esi
  8ae17d:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae182:	lea    0x390(%rsp),%rsi
  8ae18a:	mov    $0x1,%edx
  8ae18f:	mov    %r14,%rdi
  8ae192:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae197:	lea    0x390(%rsp),%rdi
  8ae19f:	call   556288 <_ZNSsD1Ev@plt>
  8ae1a4:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae1a9:	cmp    $0x1,%r12d
  8ae1ad:	jle    8ae4d5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2345>
  8ae1b3:	lea    0x47b(%rsp),%rdx
  8ae1bb:	lea    0x3d0(%rsp),%rdi
  8ae1c3:	mov    $0xfd1348,%esi
  8ae1c8:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae1cd:	lea    0x3d0(%rsp),%rsi
  8ae1d5:	mov    $0x1,%edx
  8ae1da:	mov    %r14,%rdi
  8ae1dd:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae1e2:	lea    0x3d0(%rsp),%rdi
  8ae1ea:	call   556288 <_ZNSsD1Ev@plt>
  8ae1ef:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae1f4:	cmp    $0x1,%r12d
  8ae1f8:	jle    8ae26a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20da>
  8ae1fa:	lea    0x479(%rsp),%rdx
  8ae202:	lea    0x3b0(%rsp),%rdi
  8ae20a:	mov    $0xfd1370,%esi
  8ae20f:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae214:	lea    0x3b0(%rsp),%rsi
  8ae21c:	mov    $0x1,%edx
  8ae221:	mov    %r14,%rdi
  8ae224:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae229:	lea    0x3b0(%rsp),%rdi
  8ae231:	call   556288 <_ZNSsD1Ev@plt>
  8ae236:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae23b:	lea    0x390(%rsp),%rdi
  8ae243:	mov    %rax,%rbx
  8ae246:	call   556288 <_ZNSsD1Ev@plt>
  8ae24b:	mov    %rbx,%rdi
  8ae24e:	call   554498 <_Unwind_Resume@plt>
  8ae253:	lea    0x3b0(%rsp),%rdi
  8ae25b:	mov    %rax,%rbx
  8ae25e:	call   556288 <_ZNSsD1Ev@plt>
  8ae263:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae265:	mov    %rax,%rbx
  8ae268:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae26a:	lea    0x478(%rsp),%rdx
  8ae272:	lea    0x3a0(%rsp),%rdi
  8ae27a:	mov    $0xfd1182,%esi
  8ae27f:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae284:	lea    0x3a0(%rsp),%rsi
  8ae28c:	mov    $0x1,%edx
  8ae291:	mov    %r14,%rdi
  8ae294:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae299:	lea    0x3a0(%rsp),%rdi
  8ae2a1:	call   556288 <_ZNSsD1Ev@plt>
  8ae2a6:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae2ab:	mov    %rax,%rbx
  8ae2ae:	mov    %r15,%rdi
  8ae2b1:	call   556288 <_ZNSsD1Ev@plt>
  8ae2b6:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae2b8:	mov    %rax,%rbx
  8ae2bb:	lea    0x430(%rsp),%rdi
  8ae2c3:	call   556288 <_ZNSsD1Ev@plt>
  8ae2c8:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae2ca:	lea    0x3a0(%rsp),%rdi
  8ae2d2:	mov    %rax,%rbx
  8ae2d5:	call   556288 <_ZNSsD1Ev@plt>
  8ae2da:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae2df:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae2e1:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae2e3:	lea    0x476(%rsp),%rdx
  8ae2eb:	lea    0x380(%rsp),%rdi
  8ae2f3:	mov    $0xfd119b,%esi
  8ae2f8:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae2fd:	lea    0x380(%rsp),%rsi
  8ae305:	mov    $0x1,%edx
  8ae30a:	mov    %r14,%rdi
  8ae30d:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae312:	lea    0x380(%rsp),%rdi
  8ae31a:	call   556288 <_ZNSsD1Ev@plt>
  8ae31f:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae324:	lea    0x150(%rsp),%rdi
  8ae32c:	mov    %rax,%rbx
  8ae32f:	call   8b1040 <_ZN4Ogre9SharedPtrINS_20GpuProgramParametersEED1Ev>
  8ae334:	lea    0x350(%rsp),%rdi
  8ae33c:	call   556288 <_ZNSsD1Ev@plt>
  8ae341:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae346:	mov    %rax,%rbx
  8ae349:	jmp    8ae334 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x21a4>
  8ae34b:	lea    0x380(%rsp),%rdi
  8ae353:	mov    %rax,%rbx
  8ae356:	call   556288 <_ZNSsD1Ev@plt>
  8ae35b:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae360:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae365:	data16 cs nopw 0x0(%rax,%rax,1)
  8ae370:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae375:	lea    0x370(%rsp),%rdi
  8ae37d:	mov    %rax,%rbx
  8ae380:	call   556288 <_ZNSsD1Ev@plt>
  8ae385:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae38a:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae38f:	lea    0x474(%rsp),%rdx
  8ae397:	lea    0x360(%rsp),%rdi
  8ae39f:	mov    $0xfd11b4,%esi
  8ae3a4:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae3a9:	lea    0x360(%rsp),%rsi
  8ae3b1:	mov    $0x1,%edx
  8ae3b6:	mov    %r14,%rdi
  8ae3b9:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae3be:	lea    0x360(%rsp),%rdi
  8ae3c6:	call   556288 <_ZNSsD1Ev@plt>
  8ae3cb:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae3d0:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae3d5:	mov    $0x5541c8,%eax
  8ae3da:	test   %rax,%rax
  8ae3dd:	nopl   (%rax)
  8ae3e0:	je     8ae72e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x259e>
  8ae3e6:	or     $0xffffffff,%eax
  8ae3e9:	lock xadd %eax,0x10(%rdi)
  8ae3ee:	test   %eax,%eax
  8ae3f0:	jg     8acb38 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x9a8>
  8ae3f6:	lea    0x457(%rsp),%rsi
  8ae3fe:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae403:	jmp    8acb38 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x9a8>
  8ae408:	mov    %r12,%rdi
  8ae40b:	mov    %rax,%rbx
  8ae40e:	call   556288 <_ZNSsD1Ev@plt>
  8ae413:	mov    %r13,%rdi
  8ae416:	call   556288 <_ZNSsD1Ev@plt>
  8ae41b:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae420:	mov    %r14,%rdi
  8ae423:	mov    %rax,%rbx
  8ae426:	call   556288 <_ZNSsD1Ev@plt>
  8ae42b:	jmp    8ae2bb <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x212b>
  8ae430:	mov    $0x5541c8,%eax
  8ae435:	test   %rax,%rax
  8ae438:	je     8ae48d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x22fd>
  8ae43a:	or     $0xffffffff,%eax
  8ae43d:	lock xadd %eax,0x10(%rdi)
  8ae442:	test   %eax,%eax
  8ae444:	jg     8aca45 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x8b5>
  8ae44a:	lea    0x45f(%rsp),%rsi
  8ae452:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae457:	jmp    8aca45 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x8b5>
  8ae45c:	mov    $0x5541c8,%eax
  8ae461:	test   %rax,%rax
  8ae464:	je     8ae498 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2308>
  8ae466:	or     $0xffffffff,%eax
  8ae469:	lock xadd %eax,0x10(%rdi)
  8ae46e:	test   %eax,%eax
  8ae470:	jg     8aca5e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x8ce>
  8ae476:	lea    0x45e(%rsp),%rsi
  8ae47e:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae483:	jmp    8aca5e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x8ce>
  8ae488:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae48d:	mov    0x10(%rdi),%eax
  8ae490:	lea    -0x1(%rax),%edx
  8ae493:	mov    %edx,0x10(%rdi)
  8ae496:	jmp    8ae442 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x22b2>
  8ae498:	mov    0x10(%rdi),%eax
  8ae49b:	lea    -0x1(%rax),%edx
  8ae49e:	mov    %edx,0x10(%rdi)
  8ae4a1:	jmp    8ae46e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x22de>
  8ae4a3:	lea    0x210(%rsp),%rdi
  8ae4ab:	mov    %rax,%rbx
  8ae4ae:	call   86bc00 <_ZN4Ogre3AnyD1Ev>
  8ae4b3:	mov    %rbx,%rdi
  8ae4b6:	call   554498 <_Unwind_Resume@plt>
  8ae4bb:	lea    0x3d0(%rsp),%rdi
  8ae4c3:	mov    %rax,%rbx
  8ae4c6:	call   556288 <_ZNSsD1Ev@plt>
  8ae4cb:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae4d0:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae4d5:	lea    0x47a(%rsp),%rdx
  8ae4dd:	lea    0x3c0(%rsp),%rdi
  8ae4e5:	mov    $0xfd1167,%esi
  8ae4ea:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  8ae4ef:	lea    0x3c0(%rsp),%rsi
  8ae4f7:	mov    $0x1,%edx
  8ae4fc:	mov    %r14,%rdi
  8ae4ff:	call   555608 <_ZN4Ogre4Pass16setVertexProgramERKSsb@plt>
  8ae504:	lea    0x3c0(%rsp),%rdi
  8ae50c:	call   556288 <_ZNSsD1Ev@plt>
  8ae511:	jmp    8adb46 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x19b6>
  8ae516:	mov    $0x5541c8,%edx
  8ae51b:	test   %rdx,%rdx
  8ae51e:	je     8ae582 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x23f2>
  8ae520:	or     $0xffffffff,%edx
  8ae523:	lock xadd %edx,0x10(%rdi)
  8ae528:	test   %edx,%edx
  8ae52a:	jg     8acbbc <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa2c>
  8ae530:	lea    0x455(%rsp),%rsi
  8ae538:	mov    %rax,0x10(%rsp)
  8ae53d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae542:	mov    0x10(%rsp),%rax
  8ae547:	jmp    8acbbc <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa2c>
  8ae54c:	mov    $0x5541c8,%edx
  8ae551:	test   %rdx,%rdx
  8ae554:	je     8ae58d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x23fd>
  8ae556:	or     $0xffffffff,%edx
  8ae559:	lock xadd %edx,0x10(%rdi)
  8ae55e:	test   %edx,%edx
  8ae560:	jg     8acbd5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa45>
  8ae566:	lea    0x454(%rsp),%rsi
  8ae56e:	mov    %rax,0x10(%rsp)
  8ae573:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae578:	mov    0x10(%rsp),%rax
  8ae57d:	jmp    8acbd5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xa45>
  8ae582:	mov    0x10(%rdi),%edx
  8ae585:	lea    -0x1(%rdx),%ecx
  8ae588:	mov    %ecx,0x10(%rdi)
  8ae58b:	jmp    8ae528 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2398>
  8ae58d:	mov    0x10(%rdi),%edx
  8ae590:	lea    -0x1(%rdx),%ecx
  8ae593:	mov    %ecx,0x10(%rdi)
  8ae596:	jmp    8ae55e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x23ce>
  8ae598:	mov    %rax,%rbx
  8ae59b:	lea    0x3f0(%rsp),%rdi
  8ae5a3:	call   556288 <_ZNSsD1Ev@plt>
  8ae5a8:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae5ad:	mov    %r14,%rdi
  8ae5b0:	mov    %rax,%rbx
  8ae5b3:	call   556288 <_ZNSsD1Ev@plt>
  8ae5b8:	jmp    8ae59b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x240b>
  8ae5ba:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae5bf:	mov    0x10(%rdi),%eax
  8ae5c2:	lea    -0x1(%rax),%edx
  8ae5c5:	mov    %edx,0x10(%rdi)
  8ae5c8:	jmp    8ace63 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xcd3>
  8ae5cd:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae5d2:	lea    0x3c0(%rsp),%rdi
  8ae5da:	mov    %rax,%rbx
  8ae5dd:	call   556288 <_ZNSsD1Ev@plt>
  8ae5e2:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae5e7:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae5ec:	mov    0x10(%rdi),%eax
  8ae5ef:	lea    -0x1(%rax),%edx
  8ae5f2:	mov    %edx,0x10(%rdi)
  8ae5f5:	jmp    8acdaf <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xc1f>
  8ae5fa:	mov    $0x5541c8,%eax
  8ae5ff:	test   %rax,%rax
  8ae602:	je     8ae62b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x249b>
  8ae604:	or     $0xffffffff,%eax
  8ae607:	lock xadd %eax,0x10(%rdi)
  8ae60c:	test   %eax,%eax
  8ae60e:	jg     8acede <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xd4e>
  8ae614:	lea    0x44d(%rsp),%rsi
  8ae61c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae621:	jmp    8acede <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xd4e>
  8ae626:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae62b:	mov    0x10(%rdi),%eax
  8ae62e:	lea    -0x1(%rax),%edx
  8ae631:	mov    %edx,0x10(%rdi)
  8ae634:	jmp    8ae60c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x247c>
  8ae636:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae63b:	mov    %rax,%rbx
  8ae63e:	jmp    8ae413 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2283>
  8ae643:	mov    %r12,%rdi
  8ae646:	mov    %rax,%rbx
  8ae649:	call   556288 <_ZNSsD1Ev@plt>
  8ae64e:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae653:	jmp    8ae643 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x24b3>
  8ae655:	lea    0x360(%rsp),%rdi
  8ae65d:	mov    %rax,%rbx
  8ae660:	call   556288 <_ZNSsD1Ev@plt>
  8ae665:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8ae66a:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8ae66f:	mov    %rax,%rbx
  8ae672:	lea    0x90(%rsp),%rdi
  8ae67a:	call   556288 <_ZNSsD1Ev@plt>
  8ae67f:	lea    0xc0(%rsp),%rdi
  8ae687:	call   56b110 <_ZN4Ogre11MaterialPtrD1Ev>
  8ae68c:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae691:	lea    0x90(%rsp),%rdi
  8ae699:	mov    %rax,%rbx
  8ae69c:	add    $0x8,%rdi
  8ae6a0:	call   556288 <_ZNSsD1Ev@plt>
  8ae6a5:	jmp    8ae672 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x24e2>
  8ae6a7:	mov    %rax,%rbx
  8ae6aa:	lea    0x90(%rsp),%rdi
  8ae6b2:	call   73d660 <_ZN9CFileInfoD1Ev>
  8ae6b7:	jmp    8ae67f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x24ef>
  8ae6b9:	mov    %r13,%rdi
  8ae6bc:	mov    %rax,%rbx
  8ae6bf:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  8ae6c4:	jmp    8ae6aa <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x251a>
  8ae6c6:	mov    $0x5541c8,%eax
  8ae6cb:	test   %rax,%rax
  8ae6ce:	je     8ae6f7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2567>
  8ae6d0:	or     $0xffffffff,%eax
  8ae6d3:	lock xadd %eax,0x10(%rdi)
  8ae6d8:	test   %eax,%eax
  8ae6da:	jg     8acff2 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xe62>
  8ae6e0:	lea    0x44b(%rsp),%rsi
  8ae6e8:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae6ed:	jmp    8acff2 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xe62>
  8ae6f2:	mov    %rax,%rbx
  8ae6f5:	jmp    8ae67f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x24ef>
  8ae6f7:	mov    0x10(%rdi),%eax
  8ae6fa:	lea    -0x1(%rax),%edx
  8ae6fd:	mov    %edx,0x10(%rdi)
  8ae700:	jmp    8ae6d8 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2548>
  8ae702:	mov    $0x5541c8,%eax
  8ae707:	test   %rax,%rax
  8ae70a:	je     8ae73c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x25ac>
  8ae70c:	or     $0xffffffff,%eax
  8ae70f:	lock xadd %eax,0x10(%rdi)
  8ae714:	test   %eax,%eax
  8ae716:	jg     8acfd9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xe49>
  8ae71c:	lea    0x44c(%rsp),%rsi
  8ae724:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae729:	jmp    8acfd9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0xe49>
  8ae72e:	mov    0x10(%rdi),%eax
  8ae731:	lea    -0x1(%rax),%edx
  8ae734:	mov    %edx,0x10(%rdi)
  8ae737:	jmp    8ae3ee <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x225e>
  8ae73c:	mov    0x10(%rdi),%eax
  8ae73f:	lea    -0x1(%rax),%edx
  8ae742:	mov    %edx,0x10(%rdi)
  8ae745:	jmp    8ae714 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2584>
  8ae747:	mov    $0x5541c8,%eax
  8ae74c:	test   %rax,%rax
  8ae74f:	je     8ae778 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x25e8>
  8ae751:	or     $0xffffffff,%eax
  8ae754:	lock xadd %eax,0x10(%rdi)
  8ae759:	test   %eax,%eax
  8ae75b:	jg     8ad21b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x108b>
  8ae761:	lea    0x44a(%rsp),%rsi
  8ae769:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  8ae76e:	jmp    8ad21b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x108b>
  8ae773:	jmp    8ae2ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211b>
  8ae778:	mov    0x10(%rdi),%eax
  8ae77b:	lea    -0x1(%rax),%edx
  8ae77e:	mov    %edx,0x10(%rdi)
  8ae781:	jmp    8ae759 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x25c9>
  8ae783:	lea    0x410(%rsp),%rdi
  8ae78b:	mov    %rax,%rbx
  8ae78e:	call   556288 <_ZNSsD1Ev@plt>
  8ae793:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae798:	mov    $0x5541c8,%eax
  8ae79d:	test   %rax,%rax
  8ae7a0:	je     8ae816 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2686>
  8ae7a2:	or     $0xffffffff,%eax
  8ae7a5:	lock xadd %eax,0x10(%rdi)
  8ae7aa:	test   %eax,%eax
  8ae7ac:	jg     8ad7bd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x162d>
  8ae7b2:	lea    0x45d(%rsp),%rsi
  8ae7ba:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae7bf:	jmp    8ad7bd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x162d>
  8ae7c4:	mov    %rax,%rbx
  8ae7c7:	lea    0xc0(%rsp),%rdi
  8ae7cf:	call   556288 <_ZNSsD1Ev@plt>
  8ae7d4:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae7d9:	mov    %rax,%rbx
  8ae7dc:	lea    0xc0(%rsp),%rdi
  8ae7e4:	call   73d660 <_ZN9CFileInfoD1Ev>
  8ae7e9:	jmp    8ae2ae <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x211e>
  8ae7ee:	lea    0x400(%rsp),%rdi
  8ae7f6:	mov    %rax,%rbx
  8ae7f9:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  8ae7fe:	jmp    8ae7dc <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x264c>
  8ae800:	lea    0xc0(%rsp),%rdi
  8ae808:	mov    %rax,%rbx
  8ae80b:	add    $0x8,%rdi
  8ae80f:	call   556288 <_ZNSsD1Ev@plt>
  8ae814:	jmp    8ae7c7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2637>
  8ae816:	mov    0x10(%rdi),%eax
  8ae819:	lea    -0x1(%rax),%edx
  8ae81c:	mov    %edx,0x10(%rdi)
  8ae81f:	jmp    8ae7aa <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x261a>
  8ae821:	mov    $0x5541c8,%eax
  8ae826:	test   %rax,%rax
  8ae829:	je     8ae84f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x26bf>
  8ae82b:	or     $0xffffffff,%eax
  8ae82e:	lock xadd %eax,0x10(%rdi)
  8ae833:	test   %eax,%eax
  8ae835:	jg     8ad960 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x17d0>
  8ae83b:	lea    0x45c(%rsp),%rsi
  8ae843:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  8ae848:	jmp    8ad960 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x17d0>
  8ae84d:	jmp    8ae7d9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2649>
  8ae84f:	mov    0x10(%rdi),%eax
  8ae852:	lea    -0x1(%rax),%edx
  8ae855:	mov    %edx,0x10(%rdi)
  8ae858:	jmp    8ae833 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x26a3>
  8ae85a:	mov    $0x5541c8,%eax
  8ae85f:	test   %rax,%rax
  8ae862:	je     8ae8b2 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2722>
  8ae864:	or     $0xffffffff,%eax
  8ae867:	lock xadd %eax,0x10(%rdi)
  8ae86c:	test   %eax,%eax
  8ae86e:	jg     8ad9c4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1834>
  8ae874:	lea    0x45b(%rsp),%rsi
  8ae87c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae881:	jmp    8ad9c4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1834>
  8ae886:	mov    $0x5541c8,%eax
  8ae88b:	test   %rax,%rax
  8ae88e:	je     8ae8bd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x272d>
  8ae890:	or     $0xffffffff,%eax
  8ae893:	lock xadd %eax,0x10(%rdi)
  8ae898:	test   %eax,%eax
  8ae89a:	jg     8ad9de <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x184e>
  8ae8a0:	lea    0x45a(%rsp),%rsi
  8ae8a8:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  8ae8ad:	jmp    8ad9de <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x184e>
  8ae8b2:	mov    0x10(%rdi),%eax
  8ae8b5:	lea    -0x1(%rax),%edx
  8ae8b8:	mov    %edx,0x10(%rdi)
  8ae8bb:	jmp    8ae86c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x26dc>
  8ae8bd:	mov    0x10(%rdi),%eax
  8ae8c0:	lea    -0x1(%rax),%edx
  8ae8c3:	mov    %edx,0x10(%rdi)
  8ae8c6:	jmp    8ae898 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2708>
  8ae8c8:	mov    $0x5541c8,%eax
  8ae8cd:	test   %rax,%rax
  8ae8d0:	je     8ae8f9 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2769>
  8ae8d2:	or     $0xffffffff,%eax
  8ae8d5:	lock xadd %eax,0x10(%rdi)
  8ae8da:	test   %eax,%eax
  8ae8dc:	jg     8ad9f7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1867>
  8ae8e2:	lea    0x459(%rsp),%rsi
  8ae8ea:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae8ef:	jmp    8ad9f7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1867>
  8ae8f4:	jmp    8ae6a7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2517>
  8ae8f9:	mov    0x10(%rdi),%eax
  8ae8fc:	lea    -0x1(%rax),%edx
  8ae8ff:	mov    %edx,0x10(%rdi)
  8ae902:	jmp    8ae8da <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x274a>
  8ae904:	mov    %r13,%rdi
  8ae907:	mov    %rax,%rbx
  8ae90a:	call   556288 <_ZNSsD1Ev@plt>
  8ae90f:	jmp    8ae6aa <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x251a>
  8ae914:	mov    $0x5541c8,%eax
  8ae919:	test   %rax,%rax
  8ae91c:	je     8aea70 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28e0>
  8ae922:	or     $0xffffffff,%eax
  8ae925:	lock xadd %eax,0x10(%rdi)
  8ae92a:	test   %eax,%eax
  8ae92c:	jg     8ad3c4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1234>
  8ae932:	lea    0x442(%rsp),%rsi
  8ae93a:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae93f:	jmp    8ad3c4 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1234>
  8ae944:	mov    $0x5541c8,%eax
  8ae949:	test   %rax,%rax
  8ae94c:	je     8ae9bd <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x282d>
  8ae94e:	or     $0xffffffff,%eax
  8ae951:	lock xadd %eax,0x10(%rdi)
  8ae956:	test   %eax,%eax
  8ae958:	jg     8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8ae95e:	lea    0x446(%rsp),%rsi
  8ae966:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8ae96b:	jmp    8ad347 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11b7>
  8ae970:	jmp    8ae6a7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2517>
  8ae975:	data16 cs nopw 0x0(%rax,%rax,1)
  8ae980:	jmp    8ae6a7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2517>
  8ae985:	data16 cs nopw 0x0(%rax,%rax,1)
  8ae990:	jmp    8ae904 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2774>
  8ae995:	mov    0x10(%rdi),%eax
  8ae998:	lea    -0x1(%rax),%edx
  8ae99b:	mov    %edx,0x10(%rdi)
  8ae99e:	xchg   %ax,%ax
  8ae9a0:	jmp    8ad42a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x129a>
  8ae9a5:	mov    0x10(%rdi),%eax
  8ae9a8:	lea    -0x1(%rax),%edx
  8ae9ab:	mov    %edx,0x10(%rdi)
  8ae9ae:	jmp    8adc7c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1aec>
  8ae9b3:	jmp    8ae904 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2774>
  8ae9b8:	jmp    8ae6a7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2517>
  8ae9bd:	mov    0x10(%rdi),%eax
  8ae9c0:	lea    -0x1(%rax),%edx
  8ae9c3:	mov    %edx,0x10(%rdi)
  8ae9c6:	jmp    8ae956 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x27c6>
  8ae9c8:	mov    0x10(%rdi),%eax
  8ae9cb:	lea    -0x1(%rax),%edx
  8ae9ce:	mov    %edx,0x10(%rdi)
  8ae9d1:	jmp    8add7c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1bec>
  8ae9d6:	mov    $0x5541c8,%eax
  8ae9db:	test   %rax,%rax
  8ae9de:	je     8aea2e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x289e>
  8ae9e0:	or     $0xffffffff,%eax
  8ae9e3:	lock xadd %eax,0x10(%rdi)
  8ae9e8:	test   %eax,%eax
  8ae9ea:	jg     8ad392 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1202>
  8ae9f0:	lea    0x444(%rsp),%rsi
  8ae9f8:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  8ae9fd:	jmp    8ad392 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1202>
  8aea02:	mov    $0x5541c8,%eax
  8aea07:	test   %rax,%rax
  8aea0a:	je     8aea39 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28a9>
  8aea0c:	or     $0xffffffff,%eax
  8aea0f:	lock xadd %eax,0x10(%rdi)
  8aea14:	test   %eax,%eax
  8aea16:	jg     8ad3ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x121b>
  8aea1c:	lea    0x443(%rsp),%rsi
  8aea24:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aea29:	jmp    8ad3ab <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x121b>
  8aea2e:	mov    0x10(%rdi),%eax
  8aea31:	lea    -0x1(%rax),%edx
  8aea34:	mov    %edx,0x10(%rdi)
  8aea37:	jmp    8ae9e8 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2858>
  8aea39:	mov    0x10(%rdi),%eax
  8aea3c:	lea    -0x1(%rax),%edx
  8aea3f:	mov    %edx,0x10(%rdi)
  8aea42:	jmp    8aea14 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2884>
  8aea44:	mov    $0x5541c8,%eax
  8aea49:	test   %rax,%rax
  8aea4c:	je     8aea7e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28ee>
  8aea4e:	or     $0xffffffff,%eax
  8aea51:	lock xadd %eax,0x10(%rdi)
  8aea56:	test   %eax,%eax
  8aea58:	jg     8ad378 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11e8>
  8aea5e:	lea    0x445(%rsp),%rsi
  8aea66:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aea6b:	jmp    8ad378 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x11e8>
  8aea70:	mov    0x10(%rdi),%eax
  8aea73:	lea    -0x1(%rax),%edx
  8aea76:	mov    %edx,0x10(%rdi)
  8aea79:	jmp    8ae92a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x279a>
  8aea7e:	mov    0x10(%rdi),%eax
  8aea81:	lea    -0x1(%rax),%edx
  8aea84:	mov    %edx,0x10(%rdi)
  8aea87:	jmp    8aea56 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x28c6>
  8aea89:	jmp    8ae6a7 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2517>
  8aea8e:	mov    0x10(%rdi),%eax
  8aea91:	lea    -0x1(%rax),%edx
  8aea94:	mov    %edx,0x10(%rdi)
  8aea97:	jmp    8ada26 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1896>
  8aea9c:	jmp    8ae904 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2774>
  8aeaa1:	mov    0x10(%rdi),%eax
  8aeaa4:	lea    -0x1(%rax),%edx
  8aeaa7:	mov    %edx,0x10(%rdi)
  8aeaaa:	jmp    8adcfc <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1b6c>
  8aeaaf:	test   %rax,%rax
  8aeab2:	je     8aeae0 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2950>
  8aeab4:	mov    %r14d,%edx
  8aeab7:	lock xadd %edx,0x10(%rdi)
  8aeabc:	test   %edx,%edx
  8aeabe:	jg     8ac6f5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x565>
  8aeac4:	mov    %r15,%rsi
  8aeac7:	mov    %rax,0x10(%rsp)
  8aeacc:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aead1:	mov    0x10(%rsp),%rax
  8aead6:	jmp    8ac6f5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x565>
  8aeadb:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aeae0:	mov    0x10(%rdi),%edx
  8aeae3:	lea    -0x1(%rdx),%ecx
  8aeae6:	mov    %ecx,0x10(%rdi)
  8aeae9:	jmp    8aeabc <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x292c>
  8aeaeb:	mov    %rbp,%rdi
  8aeaee:	mov    %rax,%rbx
  8aeaf1:	call   556288 <_ZNSsD1Ev@plt>
  8aeaf6:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8aeafb:	mov    $0x5541c8,%eax
  8aeb00:	test   %rax,%rax
  8aeb03:	je     8aeb37 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x29a7>
  8aeb05:	or     $0xffffffff,%eax
  8aeb08:	lock xadd %eax,0x10(%rdi)
  8aeb0d:	test   %eax,%eax
  8aeb0f:	jg     8ac80e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x67e>
  8aeb15:	lea    0x460(%rsp),%rsi
  8aeb1d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aeb22:	jmp    8ac80e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x67e>
  8aeb27:	mov    %rax,%rbx
  8aeb2a:	mov    %r12,%rdi
  8aeb2d:	call   556288 <_ZNSsD1Ev@plt>
  8aeb32:	jmp    8ae24b <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20bb>
  8aeb37:	mov    0x10(%rdi),%eax
  8aeb3a:	lea    -0x1(%rax),%edx
  8aeb3d:	mov    %edx,0x10(%rdi)
  8aeb40:	jmp    8aeb0d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x297d>
  8aeb42:	test   %rax,%rax
  8aeb45:	je     8aeb7c <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x29ec>
  8aeb47:	mov    %r14d,%edx
  8aeb4a:	lock xadd %edx,0x10(%rdi)
  8aeb4f:	test   %edx,%edx
  8aeb51:	jg     8ac7e5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x655>
  8aeb57:	mov    %r15,%rsi
  8aeb5a:	mov    %rax,0x10(%rsp)
  8aeb5f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aeb64:	mov    0x10(%rsp),%rax
  8aeb69:	jmp    8ac7e5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x655>
  8aeb6e:	mov    0x10(%rdi),%eax
  8aeb71:	lea    -0x1(%rax),%edx
  8aeb74:	mov    %edx,0x10(%rdi)
  8aeb77:	jmp    8ac37e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1ee>
  8aeb7c:	mov    0x10(%rdi),%edx
  8aeb7f:	lea    -0x1(%rdx),%ecx
  8aeb82:	mov    %ecx,0x10(%rdi)
  8aeb85:	jmp    8aeb4f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x29bf>
  8aeb87:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aeb8c:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aeb8e:	xchg   %ax,%ax
  8aeb90:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aeb95:	data16 cs nopw 0x0(%rax,%rax,1)
  8aeba0:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aeba2:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aeba7:	nopw   0x0(%rax,%rax,1)
  8aebb0:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aebb5:	data16 cs nopw 0x0(%rax,%rax,1)
  8aebc0:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aebc5:	lea    0x38(%rbp),%rdi
  8aebc9:	mov    %rax,%rbx
  8aebcc:	call   556288 <_ZNSsD1Ev@plt>
  8aebd1:	mov    %rbx,%rdi
  8aebd4:	call   554498 <_Unwind_Resume@plt>
  8aebd9:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aebde:	mov    0x10(%rdi),%eax
  8aebe1:	lea    -0x1(%rax),%edx
  8aebe4:	mov    %edx,0x10(%rdi)
  8aebe7:	jmp    8adfb5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1e25>
  8aebec:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aebf1:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aebf6:	cs nopw 0x0(%rax,%rax,1)
  8aec00:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aec05:	mov    0x10(%rdi),%eax
  8aec08:	lea    -0x1(%rax),%edx
  8aec0b:	mov    %edx,0x10(%rdi)
  8aec0e:	xchg   %ax,%ax
  8aec10:	jmp    8ade6a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1cda>
  8aec15:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aec1a:	mov    0x10(%rdi),%eax
  8aec1d:	lea    -0x1(%rax),%edx
  8aec20:	mov    %edx,0x10(%rdi)
  8aec23:	jmp    8adf0d <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1d7d>
  8aec28:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aec2d:	mov    $0x5541c8,%eax
  8aec32:	test   %rax,%rax
  8aec35:	je     8aec6e <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2ade>
  8aec37:	or     $0xffffffff,%eax
  8aec3a:	lock xadd %eax,0x10(%rdi)
  8aec3f:	test   %eax,%eax
  8aec41:	jg     8ad724 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1594>
  8aec47:	lea    0x44f(%rsp),%rsi
  8aec4f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aec54:	jmp    8ad724 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x1594>
  8aec59:	mov    %r14,%rdi
  8aec5c:	mov    %rax,%rbx
  8aec5f:	call   8b1040 <_ZN4Ogre9SharedPtrINS_20GpuProgramParametersEED1Ev>
  8aec64:	jmp    8aeb2a <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x299a>
  8aec69:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aec6e:	mov    0x10(%rdi),%eax
  8aec71:	lea    -0x1(%rax),%edx
  8aec74:	mov    %edx,0x10(%rdi)
  8aec77:	jmp    8aec3f <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2aaf>
  8aec79:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aec7e:	mov    $0x5541c8,%eax
  8aec83:	test   %rax,%rax
  8aec86:	je     8aecb5 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2b25>
  8aec88:	or     $0xffffffff,%eax
  8aec8b:	lock xadd %eax,0x10(%rdi)
  8aec90:	test   %eax,%eax
  8aec92:	jg     8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8aec98:	lea    0x450(%rsp),%rsi
  8aeca0:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  8aeca5:	jmp    8ad679 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x14e9>
  8aecaa:	jmp    8aeb27 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2997>
  8aecaf:	nop
  8aecb0:	jmp    8ae265 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x20d5>
  8aecb5:	mov    0x10(%rdi),%eax
  8aecb8:	lea    -0x1(%rax),%edx
  8aecbb:	mov    %edx,0x10(%rdi)
  8aecbe:	xchg   %ax,%ax
  8aecc0:	jmp    8aec90 <_ZN13CGenericModel12reInitializeEPN4Ogre6EntityEb+0x2b00>
