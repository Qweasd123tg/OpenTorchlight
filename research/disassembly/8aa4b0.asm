
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000008aa4b0 <CGenericModel::updateAnimation(float, bool)>:
  8aa4b0:	41 57                	push   %r15
  8aa4b2:	41 56                	push   %r14
  8aa4b4:	41 55                	push   %r13
  8aa4b6:	41 54                	push   %r12
  8aa4b8:	55                   	push   %rbp
  8aa4b9:	53                   	push   %rbx
  8aa4ba:	48 89 fb             	mov    %rdi,%rbx
  8aa4bd:	48 81 ec f8 00 00 00 	sub    $0xf8,%rsp
  8aa4c4:	f3 0f 11 44 24 38    	movss  %xmm0,0x38(%rsp)
  8aa4ca:	40 88 74 24 7f       	mov    %sil,0x7f(%rsp)
  8aa4cf:	48 83 7f 60 00       	cmpq   $0x0,0x60(%rdi)
  8aa4d4:	74 29                	je     8aa4ff <CGenericModel::updateAnimation(float, bool)+0x4f>
  8aa4d6:	48 8b 07             	mov    (%rdi),%rax
  8aa4d9:	ff 50 48             	call   *0x48(%rax)
  8aa4dc:	84 c0                	test   %al,%al
  8aa4de:	75 31                	jne    8aa511 <CGenericModel::updateAnimation(float, bool)+0x61>
  8aa4e0:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aa4e6:	0f 2e 05 2f e2 6f 00 	ucomiss 0x6fe22f(%rip),%xmm0        # fa871c <vtable for Ogre::SharedPtr<Ogre::Texture>+0x7c>
  8aa4ed:	7a 02                	jp     8aa4f1 <CGenericModel::updateAnimation(float, bool)+0x41>
  8aa4ef:	74 20                	je     8aa511 <CGenericModel::updateAnimation(float, bool)+0x61>
  8aa4f1:	48 8b 83 b0 01 00 00 	mov    0x1b0(%rbx),%rax
  8aa4f8:	48 89 83 b8 01 00 00 	mov    %rax,0x1b8(%rbx)
  8aa4ff:	48 81 c4 f8 00 00 00 	add    $0xf8,%rsp
  8aa506:	5b                   	pop    %rbx
  8aa507:	5d                   	pop    %rbp
  8aa508:	41 5c                	pop    %r12
  8aa50a:	41 5d                	pop    %r13
  8aa50c:	41 5e                	pop    %r14
  8aa50e:	41 5f                	pop    %r15
  8aa510:	c3                   	ret
  8aa511:	80 bb e8 01 00 00 00 	cmpb   $0x0,0x1e8(%rbx)
  8aa518:	0f 85 2b 08 00 00    	jne    8aad49 <CGenericModel::updateAnimation(float, bool)+0x899>
  8aa51e:	48 8b 83 80 01 00 00 	mov    0x180(%rbx),%rax
  8aa525:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8aa52c:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8aa533:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8aa53a:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8aa541:	48 89 c1             	mov    %rax,%rcx
  8aa544:	48 89 fa             	mov    %rdi,%rdx
  8aa547:	4c 29 f1             	sub    %r14,%rcx
  8aa54a:	48 29 ea             	sub    %rbp,%rdx
  8aa54d:	48 c1 f9 03          	sar    $0x3,%rcx
  8aa551:	48 c1 fa 03          	sar    $0x3,%rdx
  8aa555:	48 8d 34 11          	lea    (%rcx,%rdx,1),%rsi
  8aa559:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8aa560:	48 89 d1             	mov    %rdx,%rcx
  8aa563:	4c 29 f9             	sub    %r15,%rcx
  8aa566:	48 c1 f9 03          	sar    $0x3,%rcx
  8aa56a:	48 c1 e1 06          	shl    $0x6,%rcx
  8aa56e:	48 8d 4c 31 c0       	lea    -0x40(%rcx,%rsi,1),%rcx
  8aa573:	48 85 c9             	test   %rcx,%rcx
  8aa576:	0f 84 75 ff ff ff    	je     8aa4f1 <CGenericModel::updateAnimation(float, bool)+0x41>
  8aa57c:	48 8b 73 68          	mov    0x68(%rbx),%rsi
  8aa580:	80 7e 40 00          	cmpb   $0x0,0x40(%rsi)
  8aa584:	0f 85 cd 07 00 00    	jne    8aad57 <CGenericModel::updateAnimation(float, bool)+0x8a7>
  8aa58a:	80 7c 24 7f 00       	cmpb   $0x0,0x7f(%rsp)
  8aa58f:	75 0a                	jne    8aa59b <CGenericModel::updateAnimation(float, bool)+0xeb>
  8aa591:	48 83 f9 01          	cmp    $0x1,%rcx
  8aa595:	0f 84 60 1b 00 00    	je     8ac0fb <CGenericModel::updateAnimation(float, bool)+0x1c4b>
  8aa59b:	48 8b 8b b0 01 00 00 	mov    0x1b0(%rbx),%rcx
  8aa5a2:	48 89 fe             	mov    %rdi,%rsi
  8aa5a5:	48 29 ee             	sub    %rbp,%rsi
  8aa5a8:	48 c1 fe 03          	sar    $0x3,%rsi
  8aa5ac:	48 89 8b b8 01 00 00 	mov    %rcx,0x1b8(%rbx)
  8aa5b3:	48 89 c1             	mov    %rax,%rcx
  8aa5b6:	48 c7 84 24 b0 00 00 	movq   $0x0,0xb0(%rsp)
  8aa5bd:	00 00 00 00 00
  8aa5c2:	4c 29 f1             	sub    %r14,%rcx
  8aa5c5:	48 c7 84 24 b8 00 00 	movq   $0x0,0xb8(%rsp)
  8aa5cc:	00 00 00 00 00
  8aa5d1:	48 c7 84 24 c0 00 00 	movq   $0x0,0xc0(%rsp)
  8aa5d8:	00 00 00 00 00
  8aa5dd:	48 c1 f9 03          	sar    $0x3,%rcx
  8aa5e1:	48 c7 84 24 90 00 00 	movq   $0x0,0x90(%rsp)
  8aa5e8:	00 00 00 00 00
  8aa5ed:	48 c7 84 24 98 00 00 	movq   $0x0,0x98(%rsp)
  8aa5f4:	00 00 00 00 00
  8aa5f9:	48 01 ce             	add    %rcx,%rsi
  8aa5fc:	48 89 d1             	mov    %rdx,%rcx
  8aa5ff:	48 c7 84 24 a0 00 00 	movq   $0x0,0xa0(%rsp)
  8aa606:	00 00 00 00 00
  8aa60b:	4c 29 f9             	sub    %r15,%rcx
  8aa60e:	48 c1 f9 03          	sar    $0x3,%rcx
  8aa612:	48 c1 e1 06          	shl    $0x6,%rcx
  8aa616:	8d 74 0e c0          	lea    -0x40(%rsi,%rcx,1),%esi
  8aa61a:	85 f6                	test   %esi,%esi
  8aa61c:	0f 8e cf 1a 00 00    	jle    8ac0f1 <CGenericModel::updateAnimation(float, bool)+0x1c41>
  8aa622:	48 8d 83 70 01 00 00 	lea    0x170(%rbx),%rax
  8aa629:	48 8d 93 b0 01 00 00 	lea    0x1b0(%rbx),%rdx
  8aa630:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%rsp)
  8aa637:	00
  8aa638:	c6 44 24 7e 00       	movb   $0x0,0x7e(%rsp)
  8aa63d:	c6 44 24 60 00       	movb   $0x0,0x60(%rsp)
  8aa642:	48 89 84 24 88 00 00 	mov    %rax,0x88(%rsp)
  8aa649:	00
  8aa64a:	48 89 94 24 80 00 00 	mov    %rdx,0x80(%rsp)
  8aa651:	00
  8aa652:	c6 44 24 40 00       	movb   $0x0,0x40(%rsp)
  8aa657:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%rsp)
  8aa65e:	00
  8aa65f:	90                   	nop
  8aa660:	4c 63 44 24 30       	movslq 0x30(%rsp),%r8
  8aa665:	4c 89 f0             	mov    %r14,%rax
  8aa668:	4c 89 44 24 20       	mov    %r8,0x20(%rsp)
  8aa66d:	48 8b bb 78 01 00 00 	mov    0x178(%rbx),%rdi
  8aa674:	4c 89 c2             	mov    %r8,%rdx
  8aa677:	48 29 f8             	sub    %rdi,%rax
  8aa67a:	48 c1 f8 03          	sar    $0x3,%rax
  8aa67e:	48 01 c2             	add    %rax,%rdx
  8aa681:	0f 88 21 0b 00 00    	js     8ab1a8 <CGenericModel::updateAnimation(float, bool)+0xcf8>
  8aa687:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8aa68b:	0f 8f ef 08 00 00    	jg     8aaf80 <CGenericModel::updateAnimation(float, bool)+0xad0>
  8aa691:	4b 8b 14 c6          	mov    (%r14,%r8,8),%rdx
  8aa695:	8b 52 10             	mov    0x10(%rdx),%edx
  8aa698:	89 54 24 2c          	mov    %edx,0x2c(%rsp)
  8aa69c:	48 8b 4c 24 20       	mov    0x20(%rsp),%rcx
  8aa6a1:	49 8d 14 ce          	lea    (%r14,%rcx,8),%rdx
  8aa6a5:	48 8b 12             	mov    (%rdx),%rdx
  8aa6a8:	80 7a 26 00          	cmpb   $0x0,0x26(%rdx)
  8aa6ac:	0f 84 5e 07 00 00    	je     8aae10 <CGenericModel::updateAnimation(float, bool)+0x960>
  8aa6b2:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aa6b5:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aa6bb:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aa6be:	7a 06                	jp     8aa6c6 <CGenericModel::updateAnimation(float, bool)+0x216>
  8aa6c0:	0f 84 4a 07 00 00    	je     8aae10 <CGenericModel::updateAnimation(float, bool)+0x960>
  8aa6c6:	83 ee 01             	sub    $0x1,%esi
  8aa6c9:	3b 74 24 30          	cmp    0x30(%rsp),%esi
  8aa6cd:	0f 8f ea 06 00 00    	jg     8aadbd <CGenericModel::updateAnimation(float, bool)+0x90d>
  8aa6d3:	39 74 24 30          	cmp    %esi,0x30(%rsp)
  8aa6d7:	74 50                	je     8aa729 <CGenericModel::updateAnimation(float, bool)+0x279>
  8aa6d9:	8b 6c 24 30          	mov    0x30(%rsp),%ebp
  8aa6dd:	83 c5 01             	add    $0x1,%ebp
  8aa6e0:	48 63 ed             	movslq %ebp,%rbp
  8aa6e3:	48 01 e8             	add    %rbp,%rax
  8aa6e6:	0f 88 96 19 00 00    	js     8ac082 <CGenericModel::updateAnimation(float, bool)+0x1bd2>
  8aa6ec:	48 83 f8 3f          	cmp    $0x3f,%rax
  8aa6f0:	49 8d 14 ee          	lea    (%r14,%rbp,8),%rdx
  8aa6f4:	7e 26                	jle    8aa71c <CGenericModel::updateAnimation(float, bool)+0x26c>
  8aa6f6:	48 85 c0             	test   %rax,%rax
  8aa6f9:	0f 8e 83 19 00 00    	jle    8ac082 <CGenericModel::updateAnimation(float, bool)+0x1bd2>
  8aa6ff:	48 89 c1             	mov    %rax,%rcx
  8aa702:	48 c1 f9 06          	sar    $0x6,%rcx
  8aa706:	48 89 ca             	mov    %rcx,%rdx
  8aa709:	48 c1 e2 06          	shl    $0x6,%rdx
  8aa70d:	48 29 d0             	sub    %rdx,%rax
  8aa710:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
  8aa717:	00
  8aa718:	49 03 14 cf          	add    (%r15,%rcx,8),%rdx
  8aa71c:	48 8b 02             	mov    (%rdx),%rax
  8aa71f:	80 78 25 00          	cmpb   $0x0,0x25(%rax)
  8aa723:	0f 85 b2 17 00 00    	jne    8abedb <CGenericModel::updateAnimation(float, bool)+0x1a2b>
  8aa729:	4c 89 f0             	mov    %r14,%rax
  8aa72c:	48 29 f8             	sub    %rdi,%rax
  8aa72f:	48 c1 f8 03          	sar    $0x3,%rax
  8aa733:	48 03 44 24 20       	add    0x20(%rsp),%rax
  8aa738:	48 85 c0             	test   %rax,%rax
  8aa73b:	0f 88 68 19 00 00    	js     8ac0a9 <CGenericModel::updateAnimation(float, bool)+0x1bf9>
  8aa741:	48 8b 54 24 20       	mov    0x20(%rsp),%rdx
  8aa746:	48 83 f8 3f          	cmp    $0x3f,%rax
  8aa74a:	49 8d 0c d6          	lea    (%r14,%rdx,8),%rcx
  8aa74e:	7e 25                	jle    8aa775 <CGenericModel::updateAnimation(float, bool)+0x2c5>
  8aa750:	48 85 c0             	test   %rax,%rax
  8aa753:	0f 8e 50 19 00 00    	jle    8ac0a9 <CGenericModel::updateAnimation(float, bool)+0x1bf9>
  8aa759:	48 89 c2             	mov    %rax,%rdx
  8aa75c:	48 c1 fa 06          	sar    $0x6,%rdx
  8aa760:	48 89 d1             	mov    %rdx,%rcx
  8aa763:	48 c1 e1 06          	shl    $0x6,%rcx
  8aa767:	48 29 c8             	sub    %rcx,%rax
  8aa76a:	48 89 c1             	mov    %rax,%rcx
  8aa76d:	48 c1 e1 03          	shl    $0x3,%rcx
  8aa771:	49 03 0c d7          	add    (%r15,%rdx,8),%rcx
  8aa775:	48 8b 01             	mov    (%rcx),%rax
  8aa778:	c6 40 25 01          	movb   $0x1,0x25(%rax)
  8aa77c:	c6 40 26 00          	movb   $0x0,0x26(%rax)
  8aa780:	c7 40 34 00 00 00 00 	movl   $0x0,0x34(%rax)
  8aa787:	8b 4c 24 2c          	mov    0x2c(%rsp),%ecx
  8aa78b:	39 8b 54 01 00 00    	cmp    %ecx,0x154(%rbx)
  8aa791:	0f 87 30 17 00 00    	ja     8abec7 <CGenericModel::updateAnimation(float, bool)+0x1a17>
  8aa797:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8aa79e:	48 8b 38             	mov    (%rax),%rdi
  8aa7a1:	be 01 00 00 00       	mov    $0x1,%esi
  8aa7a6:	e8 cd b7 ca ff       	call   555f78 <Ogre::AnimationState::setEnabled(bool)@plt>
  8aa7ab:	48 8b 93 70 01 00 00 	mov    0x170(%rbx),%rdx
  8aa7b2:	48 8b b3 88 01 00 00 	mov    0x188(%rbx),%rsi
  8aa7b9:	48 89 d0             	mov    %rdx,%rax
  8aa7bc:	48 2b 83 78 01 00 00 	sub    0x178(%rbx),%rax
  8aa7c3:	48 c1 f8 03          	sar    $0x3,%rax
  8aa7c7:	48 03 44 24 20       	add    0x20(%rsp),%rax
  8aa7cc:	0f 88 e9 18 00 00    	js     8ac0bb <CGenericModel::updateAnimation(float, bool)+0x1c0b>
  8aa7d2:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
  8aa7d7:	48 83 f8 3f          	cmp    $0x3f,%rax
  8aa7db:	48 8d 0c fa          	lea    (%rdx,%rdi,8),%rcx
  8aa7df:	7e 25                	jle    8aa806 <CGenericModel::updateAnimation(float, bool)+0x356>
  8aa7e1:	48 85 c0             	test   %rax,%rax
  8aa7e4:	0f 8e d1 18 00 00    	jle    8ac0bb <CGenericModel::updateAnimation(float, bool)+0x1c0b>
  8aa7ea:	48 89 c2             	mov    %rax,%rdx
  8aa7ed:	48 c1 fa 06          	sar    $0x6,%rdx
  8aa7f1:	48 89 d1             	mov    %rdx,%rcx
  8aa7f4:	48 c1 e1 06          	shl    $0x6,%rcx
  8aa7f8:	48 29 c8             	sub    %rcx,%rax
  8aa7fb:	48 89 c1             	mov    %rax,%rcx
  8aa7fe:	48 c1 e1 03          	shl    $0x3,%rcx
  8aa802:	48 03 0c d6          	add    (%rsi,%rdx,8),%rcx
  8aa806:	8b 6c 24 2c          	mov    0x2c(%rsp),%ebp
  8aa80a:	39 ab 54 01 00 00    	cmp    %ebp,0x154(%rbx)
  8aa810:	48 8b 01             	mov    (%rcx),%rax
  8aa813:	f3 0f 10 40 20       	movss  0x20(%rax),%xmm0
  8aa818:	0f 87 95 16 00 00    	ja     8abeb3 <CGenericModel::updateAnimation(float, bool)+0x1a03>
  8aa81e:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8aa825:	48 8b 38             	mov    (%rax),%rdi
  8aa828:	e8 9b a8 ca ff       	call   5550c8 <Ogre::AnimationState::setTimePosition(float)@plt>
  8aa82d:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8aa834:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8aa83b:	31 d2                	xor    %edx,%edx
  8aa83d:	44 8b 44 24 30       	mov    0x30(%rsp),%r8d
  8aa842:	45 85 c0             	test   %r8d,%r8d
  8aa845:	0f 84 d5 05 00 00    	je     8aae20 <CGenericModel::updateAnimation(float, bool)+0x970>
  8aa84b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8aa850:	84 d2                	test   %dl,%dl
  8aa852:	0f 85 d0 05 00 00    	jne    8aae28 <CGenericModel::updateAnimation(float, bool)+0x978>
  8aa858:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aa85b:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aa861:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aa864:	0f 8a 66 0b 00 00    	jp     8ab3d0 <CGenericModel::updateAnimation(float, bool)+0xf20>
  8aa86a:	0f 85 60 0b 00 00    	jne    8ab3d0 <CGenericModel::updateAnimation(float, bool)+0xf20>
  8aa870:	4c 89 f0             	mov    %r14,%rax
  8aa873:	48 2b 83 78 01 00 00 	sub    0x178(%rbx),%rax
  8aa87a:	48 c1 f8 03          	sar    $0x3,%rax
  8aa87e:	48 03 44 24 20       	add    0x20(%rsp),%rax
  8aa883:	0f 88 07 0b 00 00    	js     8ab390 <CGenericModel::updateAnimation(float, bool)+0xee0>
  8aa889:	48 83 f8 3f          	cmp    $0x3f,%rax
  8aa88d:	0f 8f 1d 08 00 00    	jg     8ab0b0 <CGenericModel::updateAnimation(float, bool)+0xc00>
  8aa893:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8aa898:	4b 8b 04 c6          	mov    (%r14,%r8,8),%rax
  8aa89c:	f3 0f 10 40 20       	movss  0x20(%rax),%xmm0
  8aa8a1:	f3 0f 11 44 24 18    	movss  %xmm0,0x18(%rsp)
  8aa8a7:	4c 8b 4c 24 20       	mov    0x20(%rsp),%r9
  8aa8ac:	0f b6 68 25          	movzbl 0x25(%rax),%ebp
  8aa8b0:	4b 8d 04 ce          	lea    (%r14,%r9,8),%rax
  8aa8b4:	48 8b 00             	mov    (%rax),%rax
  8aa8b7:	80 78 25 00          	cmpb   $0x0,0x25(%rax)
  8aa8bb:	c6 40 27 00          	movb   $0x0,0x27(%rax)
  8aa8bf:	0f 85 03 07 00 00    	jne    8aafc8 <CGenericModel::updateAnimation(float, bool)+0xb18>
  8aa8c5:	f3 0f 10 05 2f 9f 6f 	movss  0x6f9f2f(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8aa8cc:	00
  8aa8cd:	f3 0f 11 44 24 5c    	movss  %xmm0,0x5c(%rsp)
  8aa8d3:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8aa8da:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8aa8e1:	4c 89 f0             	mov    %r14,%rax
  8aa8e4:	48 2b 83 78 01 00 00 	sub    0x178(%rbx),%rax
  8aa8eb:	48 c1 f8 03          	sar    $0x3,%rax
  8aa8ef:	48 03 44 24 20       	add    0x20(%rsp),%rax
  8aa8f4:	0f 88 36 0a 00 00    	js     8ab330 <CGenericModel::updateAnimation(float, bool)+0xe80>
  8aa8fa:	48 83 f8 3f          	cmp    $0x3f,%rax
  8aa8fe:	0f 8f 5c 07 00 00    	jg     8ab060 <CGenericModel::updateAnimation(float, bool)+0xbb0>
  8aa904:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8aa909:	4b 8b 04 c6          	mov    (%r14,%r8,8),%rax
  8aa90d:	f3 0f 10 40 20       	movss  0x20(%rax),%xmm0
  8aa912:	f3 0f 11 44 24 10    	movss  %xmm0,0x10(%rsp)
  8aa918:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8aa91d:	4b 8d 04 c6          	lea    (%r14,%r8,8),%rax
  8aa921:	48 8b 00             	mov    (%rax),%rax
  8aa924:	f3 0f 10 44 24 5c    	movss  0x5c(%rsp),%xmm0
  8aa92a:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aa92d:	f3 0f 5c 40 34       	subss  0x34(%rax),%xmm0
  8aa932:	f3 0f 11 84 24 ec 00 	movss  %xmm0,0xec(%rsp)
  8aa939:	00 00
  8aa93b:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aa93e:	0f 8a cc 07 00 00    	jp     8ab110 <CGenericModel::updateAnimation(float, bool)+0xc60>
  8aa944:	0f 85 c6 07 00 00    	jne    8ab110 <CGenericModel::updateAnimation(float, bool)+0xc60>
  8aa94a:	f3 0f 5c 44 24 3c    	subss  0x3c(%rsp),%xmm0
  8aa950:	f3 0f 10 4c 24 3c    	movss  0x3c(%rsp),%xmm1
  8aa956:	80 7c 24 60 00       	cmpb   $0x0,0x60(%rsp)
  8aa95b:	f3 0f 58 c8          	addss  %xmm0,%xmm1
  8aa95f:	f3 0f 11 84 24 ec 00 	movss  %xmm0,0xec(%rsp)
  8aa966:	00 00
  8aa968:	f3 0f 11 4c 24 3c    	movss  %xmm1,0x3c(%rsp)
  8aa96e:	0f 85 d4 04 00 00    	jne    8aae48 <CGenericModel::updateAnimation(float, bool)+0x998>
  8aa974:	0f 57 d2             	xorps  %xmm2,%xmm2
  8aa977:	0f 2e c2             	ucomiss %xmm2,%xmm0
  8aa97a:	7a 06                	jp     8aa982 <CGenericModel::updateAnimation(float, bool)+0x4d2>
  8aa97c:	0f 84 c6 04 00 00    	je     8aae48 <CGenericModel::updateAnimation(float, bool)+0x998>
  8aa982:	80 7c 24 7f 00       	cmpb   $0x0,0x7f(%rsp)
  8aa987:	75 13                	jne    8aa99c <CGenericModel::updateAnimation(float, bool)+0x4ec>
  8aa989:	f3 0f 10 4c 24 18    	movss  0x18(%rsp),%xmm1
  8aa98f:	0f 2e 4c 24 10       	ucomiss 0x10(%rsp),%xmm1
  8aa994:	7a 06                	jp     8aa99c <CGenericModel::updateAnimation(float, bool)+0x4ec>
  8aa996:	0f 84 bc 04 00 00    	je     8aae58 <CGenericModel::updateAnimation(float, bool)+0x9a8>
  8aa99c:	48 8b b4 24 b8 00 00 	mov    0xb8(%rsp),%rsi
  8aa9a3:	00
  8aa9a4:	48 3b b4 24 c0 00 00 	cmp    0xc0(%rsp),%rsi
  8aa9ab:	00
  8aa9ac:	0f 84 b6 16 00 00    	je     8ac068 <CGenericModel::updateAnimation(float, bool)+0x1bb8>
  8aa9b2:	31 c0                	xor    %eax,%eax
  8aa9b4:	48 85 f6             	test   %rsi,%rsi
  8aa9b7:	74 0c                	je     8aa9c5 <CGenericModel::updateAnimation(float, bool)+0x515>
  8aa9b9:	f3 0f 11 06          	movss  %xmm0,(%rsi)
  8aa9bd:	48 8b 84 24 b8 00 00 	mov    0xb8(%rsp),%rax
  8aa9c4:	00
  8aa9c5:	48 83 c0 04          	add    $0x4,%rax
  8aa9c9:	48 89 84 24 b8 00 00 	mov    %rax,0xb8(%rsp)
  8aa9d0:	00
  8aa9d1:	48 8b b4 24 98 00 00 	mov    0x98(%rsp),%rsi
  8aa9d8:	00
  8aa9d9:	48 3b b4 24 a0 00 00 	cmp    0xa0(%rsp),%rsi
  8aa9e0:	00
  8aa9e1:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  8aa9e6:	44 89 84 24 e8 00 00 	mov    %r8d,0xe8(%rsp)
  8aa9ed:	00
  8aa9ee:	0f 84 5a 16 00 00    	je     8ac04e <CGenericModel::updateAnimation(float, bool)+0x1b9e>
  8aa9f4:	31 c0                	xor    %eax,%eax
  8aa9f6:	48 85 f6             	test   %rsi,%rsi
  8aa9f9:	74 0b                	je     8aaa06 <CGenericModel::updateAnimation(float, bool)+0x556>
  8aa9fb:	44 89 06             	mov    %r8d,(%rsi)
  8aa9fe:	48 8b 84 24 98 00 00 	mov    0x98(%rsp),%rax
  8aaa05:	00
  8aaa06:	48 83 c0 04          	add    $0x4,%rax
  8aaa0a:	f3 0f 10 84 24 ec 00 	movss  0xec(%rsp),%xmm0
  8aaa11:	00 00
  8aaa13:	48 89 84 24 98 00 00 	mov    %rax,0x98(%rsp)
  8aaa1a:	00
  8aaa1b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8aaa20:	0f 2e 44 24 5c       	ucomiss 0x5c(%rsp),%xmm0
  8aaa25:	0f 84 d6 04 00 00    	je     8aaf01 <CGenericModel::updateAnimation(float, bool)+0xa51>
  8aaa2b:	40 84 ed             	test   %bpl,%bpl
  8aaa2e:	0f 84 6c 01 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aaa34:	83 7c 24 2c ff       	cmpl   $0xffffffff,0x2c(%rsp)
  8aaa39:	0f 84 61 01 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aaa3f:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aaa42:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aaa48:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aaa4b:	7a 06                	jp     8aaa53 <CGenericModel::updateAnimation(float, bool)+0x5a3>
  8aaa4d:	0f 84 4d 01 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aaa53:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8aaa5a:	4d 85 ed             	test   %r13,%r13
  8aaa5d:	0f 84 3d 01 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aaa63:	8b 44 24 2c          	mov    0x2c(%rsp),%eax
  8aaa67:	4c 8d 24 40          	lea    (%rax,%rax,2),%r12
  8aaa6b:	49 8b 45 58          	mov    0x58(%r13),%rax
  8aaa6f:	49 c1 e4 03          	shl    $0x3,%r12
  8aaa73:	4c 01 e0             	add    %r12,%rax
  8aaa76:	48 8b 10             	mov    (%rax),%rdx
  8aaa79:	48 8b 40 08          	mov    0x8(%rax),%rax
  8aaa7d:	48 29 d0             	sub    %rdx,%rax
  8aaa80:	48 c1 e8 03          	shr    $0x3,%rax
  8aaa84:	85 c0                	test   %eax,%eax
  8aaa86:	0f 84 14 01 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aaa8c:	31 ed                	xor    %ebp,%ebp
  8aaa8e:	e9 8f 00 00 00       	jmp    8aab22 <CGenericModel::updateAnimation(float, bool)+0x672>
  8aaa93:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8aaa98:	f3 0f 10 54 24 10    	movss  0x10(%rsp),%xmm2
  8aaa9e:	0f 2e d0             	ucomiss %xmm0,%xmm2
  8aaaa1:	72 5a                	jb     8aaafd <CGenericModel::updateAnimation(float, bool)+0x64d>
  8aaaa3:	f3 0f 10 44 24 18    	movss  0x18(%rsp),%xmm0
  8aaaa9:	0f 2e 44 24 10       	ucomiss 0x10(%rsp),%xmm0
  8aaaae:	76 4d                	jbe    8aaafd <CGenericModel::updateAnimation(float, bool)+0x64d>
  8aaab0:	8b 74 24 2c          	mov    0x2c(%rsp),%esi
  8aaab4:	89 ea                	mov    %ebp,%edx
  8aaab6:	48 89 df             	mov    %rbx,%rdi
  8aaab9:	e8 d2 f4 fe ff       	call   899f90 <CGenericModel::getKeyFrame(unsigned int, unsigned int)>
  8aaabe:	48 89 84 24 d0 00 00 	mov    %rax,0xd0(%rsp)
  8aaac5:	00
  8aaac6:	48 8b b3 b8 01 00 00 	mov    0x1b8(%rbx),%rsi
  8aaacd:	48 3b b3 c0 01 00 00 	cmp    0x1c0(%rbx),%rsi
  8aaad4:	0f 84 c0 09 00 00    	je     8ab49a <CGenericModel::updateAnimation(float, bool)+0xfea>
  8aaada:	31 d2                	xor    %edx,%edx
  8aaadc:	48 85 f6             	test   %rsi,%rsi
  8aaadf:	74 11                	je     8aaaf2 <CGenericModel::updateAnimation(float, bool)+0x642>
  8aaae1:	48 89 06             	mov    %rax,(%rsi)
  8aaae4:	48 8b 93 b8 01 00 00 	mov    0x1b8(%rbx),%rdx
  8aaaeb:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8aaaf2:	48 83 c2 08          	add    $0x8,%rdx
  8aaaf6:	48 89 93 b8 01 00 00 	mov    %rdx,0x1b8(%rbx)
  8aaafd:	4d 85 ed             	test   %r13,%r13
  8aab00:	0f 84 9a 00 00 00    	je     8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aab06:	49 8b 45 58          	mov    0x58(%r13),%rax
  8aab0a:	83 c5 01             	add    $0x1,%ebp
  8aab0d:	4c 01 e0             	add    %r12,%rax
  8aab10:	48 8b 10             	mov    (%rax),%rdx
  8aab13:	48 8b 40 08          	mov    0x8(%rax),%rax
  8aab17:	48 29 d0             	sub    %rdx,%rax
  8aab1a:	48 c1 f8 03          	sar    $0x3,%rax
  8aab1e:	39 c5                	cmp    %eax,%ebp
  8aab20:	73 7e                	jae    8aaba0 <CGenericModel::updateAnimation(float, bool)+0x6f0>
  8aab22:	89 e8                	mov    %ebp,%eax
  8aab24:	48 8b 04 c2          	mov    (%rdx,%rax,8),%rax
  8aab28:	f3 0f 10 40 10       	movss  0x10(%rax),%xmm0
  8aab2d:	f3 0f 5e 05 eb 9c 6f 	divss  0x6f9ceb(%rip),%xmm0        # fa4820 <vtable for Ogre::FrameListener+0x60>
  8aab34:	00
  8aab35:	0f 2e 44 24 18       	ucomiss 0x18(%rsp),%xmm0
  8aab3a:	0f 82 58 ff ff ff    	jb     8aaa98 <CGenericModel::updateAnimation(float, bool)+0x5e8>
  8aab40:	f3 0f 10 4c 24 10    	movss  0x10(%rsp),%xmm1
  8aab46:	0f 2e c8             	ucomiss %xmm0,%xmm1
  8aab49:	0f 82 19 02 00 00    	jb     8aad68 <CGenericModel::updateAnimation(float, bool)+0x8b8>
  8aab4f:	8b 74 24 2c          	mov    0x2c(%rsp),%esi
  8aab53:	89 ea                	mov    %ebp,%edx
  8aab55:	48 89 df             	mov    %rbx,%rdi
  8aab58:	e8 33 f4 fe ff       	call   899f90 <CGenericModel::getKeyFrame(unsigned int, unsigned int)>
  8aab5d:	48 89 84 24 e0 00 00 	mov    %rax,0xe0(%rsp)
  8aab64:	00
  8aab65:	48 8b b3 b8 01 00 00 	mov    0x1b8(%rbx),%rsi
  8aab6c:	48 3b b3 c0 01 00 00 	cmp    0x1c0(%rbx),%rsi
  8aab73:	0f 85 61 ff ff ff    	jne    8aaada <CGenericModel::updateAnimation(float, bool)+0x62a>
  8aab79:	48 8b bc 24 80 00 00 	mov    0x80(%rsp),%rdi
  8aab80:	00
  8aab81:	48 8d 94 24 e0 00 00 	lea    0xe0(%rsp),%rdx
  8aab88:	00
  8aab89:	e8 32 7f 00 00       	call   8b2ac0 <std::vector<CKeyframe*, std::allocator<CKeyframe*> >::_M_insert_aux(__gnu_cxx::__normal_iterator<CKeyframe**, std::vector<CKeyframe*, std::allocator<CKeyframe*> > >, CKeyframe* const&)>
  8aab8e:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8aab95:	4d 85 ed             	test   %r13,%r13
  8aab98:	0f 85 68 ff ff ff    	jne    8aab06 <CGenericModel::updateAnimation(float, bool)+0x656>
  8aab9e:	66 90                	xchg   %ax,%ax
  8aaba0:	80 7c 24 40 00       	cmpb   $0x0,0x40(%rsp)
  8aaba5:	74 18                	je     8aabbf <CGenericModel::updateAnimation(float, bool)+0x70f>
  8aaba7:	0f 57 d2             	xorps  %xmm2,%xmm2
  8aabaa:	f3 0f 10 4c 24 38    	movss  0x38(%rsp),%xmm1
  8aabb0:	0f 2e ca             	ucomiss %xmm2,%xmm1
  8aabb3:	0f 8a f7 06 00 00    	jp     8ab2b0 <CGenericModel::updateAnimation(float, bool)+0xe00>
  8aabb9:	0f 85 f1 06 00 00    	jne    8ab2b0 <CGenericModel::updateAnimation(float, bool)+0xe00>
  8aabbf:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8aabc6:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8aabcd:	4c 89 f2             	mov    %r14,%rdx
  8aabd0:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8aabd7:	48 c1 fa 03          	sar    $0x3,%rdx
  8aabdb:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8aabe0:	0f 88 92 07 00 00    	js     8ab378 <CGenericModel::updateAnimation(float, bool)+0xec8>
  8aabe6:	4c 8b 4c 24 20       	mov    0x20(%rsp),%r9
  8aabeb:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8aabef:	4b 8d 04 ce          	lea    (%r14,%r9,8),%rax
  8aabf3:	7e 26                	jle    8aac1b <CGenericModel::updateAnimation(float, bool)+0x76b>
  8aabf5:	48 85 d2             	test   %rdx,%rdx
  8aabf8:	0f 8e 7a 07 00 00    	jle    8ab378 <CGenericModel::updateAnimation(float, bool)+0xec8>
  8aabfe:	48 89 d1             	mov    %rdx,%rcx
  8aac01:	48 c1 f9 06          	sar    $0x6,%rcx
  8aac05:	48 89 c8             	mov    %rcx,%rax
  8aac08:	48 c1 e0 06          	shl    $0x6,%rax
  8aac0c:	48 29 c2             	sub    %rax,%rdx
  8aac0f:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8aac16:	00
  8aac17:	49 03 04 cf          	add    (%r15,%rcx,8),%rax
  8aac1b:	48 8b 00             	mov    (%rax),%rax
  8aac1e:	80 78 29 00          	cmpb   $0x0,0x29(%rax)
  8aac22:	74 20                	je     8aac44 <CGenericModel::updateAnimation(float, bool)+0x794>
  8aac24:	0f b6 54 24 40       	movzbl 0x40(%rsp),%edx
  8aac29:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aac2c:	b8 01 00 00 00       	mov    $0x1,%eax
  8aac31:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aac37:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aac3a:	0f 45 d0             	cmovne %eax,%edx
  8aac3d:	0f 4a d0             	cmovp  %eax,%edx
  8aac40:	88 54 24 40          	mov    %dl,0x40(%rsp)
  8aac44:	83 44 24 30 01       	addl   $0x1,0x30(%rsp)
  8aac49:	48 8b 83 80 01 00 00 	mov    0x180(%rbx),%rax
  8aac50:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8aac57:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8aac5e:	48 89 c6             	mov    %rax,%rsi
  8aac61:	48 89 fa             	mov    %rdi,%rdx
  8aac64:	4c 29 f6             	sub    %r14,%rsi
  8aac67:	48 29 ea             	sub    %rbp,%rdx
  8aac6a:	48 c1 fa 03          	sar    $0x3,%rdx
  8aac6e:	48 c1 fe 03          	sar    $0x3,%rsi
  8aac72:	48 01 d6             	add    %rdx,%rsi
  8aac75:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8aac7c:	48 89 d1             	mov    %rdx,%rcx
  8aac7f:	4c 29 f9             	sub    %r15,%rcx
  8aac82:	48 c1 f9 03          	sar    $0x3,%rcx
  8aac86:	48 c1 e1 06          	shl    $0x6,%rcx
  8aac8a:	8d 74 0e c0          	lea    -0x40(%rsi,%rcx,1),%esi
  8aac8e:	3b 74 24 30          	cmp    0x30(%rsp),%esi
  8aac92:	0f 8f c8 f9 ff ff    	jg     8aa660 <CGenericModel::updateAnimation(float, bool)+0x1b0>
  8aac98:	f3 0f 10 44 24 3c    	movss  0x3c(%rsp),%xmm0
  8aac9e:	0f 2e 05 57 9b 6f 00 	ucomiss 0x6f9b57(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8aaca5:	7a 06                	jp     8aacad <CGenericModel::updateAnimation(float, bool)+0x7fd>
  8aaca7:	0f 82 63 13 00 00    	jb     8ac010 <CGenericModel::updateAnimation(float, bool)+0x1b60>
  8aacad:	48 8b 8c 24 90 00 00 	mov    0x90(%rsp),%rcx
  8aacb4:	00
  8aacb5:	48 8b b4 24 98 00 00 	mov    0x98(%rsp),%rsi
  8aacbc:	00
  8aacbd:	f3 0f 10 0d 5f 9b 6f 	movss  0x6f9b5f(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  8aacc4:	00
  8aacc5:	f3 0f 11 4c 24 10    	movss  %xmm1,0x10(%rsp)
  8aaccb:	48 29 ce             	sub    %rcx,%rsi
  8aacce:	48 c1 fe 02          	sar    $0x2,%rsi
  8aacd2:	48 85 f6             	test   %rsi,%rsi
  8aacd5:	0f 84 67 08 00 00    	je     8ab542 <CGenericModel::updateAnimation(float, bool)+0x1092>
  8aacdb:	31 d2                	xor    %edx,%edx
  8aacdd:	31 ed                	xor    %ebp,%ebp
  8aacdf:	eb 41                	jmp    8aad22 <CGenericModel::updateAnimation(float, bool)+0x872>
  8aace1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  8aace8:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8aacef:	f3 0f 59 44 24 10    	mulss  0x10(%rsp),%xmm0
  8aacf5:	48 8b 38             	mov    (%rax),%rdi
  8aacf8:	e8 2b 86 ca ff       	call   553328 <Ogre::AnimationState::setWeight(float)@plt>
  8aacfd:	48 8b 8c 24 90 00 00 	mov    0x90(%rsp),%rcx
  8aad04:	00
  8aad05:	48 8b 84 24 98 00 00 	mov    0x98(%rsp),%rax
  8aad0c:	00
  8aad0d:	83 c5 01             	add    $0x1,%ebp
  8aad10:	89 ea                	mov    %ebp,%edx
  8aad12:	48 29 c8             	sub    %rcx,%rax
  8aad15:	48 c1 f8 02          	sar    $0x2,%rax
  8aad19:	48 39 c2             	cmp    %rax,%rdx
  8aad1c:	0f 83 f6 07 00 00    	jae    8ab518 <CGenericModel::updateAnimation(float, bool)+0x1068>
  8aad22:	48 8b 84 24 b0 00 00 	mov    0xb0(%rsp),%rax
  8aad29:	00
  8aad2a:	f3 0f 10 04 90       	movss  (%rax,%rdx,4),%xmm0
  8aad2f:	8b 04 91             	mov    (%rcx,%rdx,4),%eax
  8aad32:	3b 83 54 01 00 00    	cmp    0x154(%rbx),%eax
  8aad38:	73 ae                	jae    8aace8 <CGenericModel::updateAnimation(float, bool)+0x838>
  8aad3a:	89 c0                	mov    %eax,%eax
  8aad3c:	48 c1 e0 03          	shl    $0x3,%rax
  8aad40:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8aad47:	eb a6                	jmp    8aacef <CGenericModel::updateAnimation(float, bool)+0x83f>
  8aad49:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aad4c:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  8aad52:	e9 c7 f7 ff ff       	jmp    8aa51e <CGenericModel::updateAnimation(float, bool)+0x6e>
  8aad57:	c6 44 24 7f 01       	movb   $0x1,0x7f(%rsp)
  8aad5c:	e9 3a f8 ff ff       	jmp    8aa59b <CGenericModel::updateAnimation(float, bool)+0xeb>
  8aad61:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  8aad68:	f3 0f 10 54 24 18    	movss  0x18(%rsp),%xmm2
  8aad6e:	0f 2e 54 24 10       	ucomiss 0x10(%rsp),%xmm2
  8aad73:	0f 86 84 fd ff ff    	jbe    8aaafd <CGenericModel::updateAnimation(float, bool)+0x64d>
  8aad79:	8b 74 24 2c          	mov    0x2c(%rsp),%esi
  8aad7d:	89 ea                	mov    %ebp,%edx
  8aad7f:	48 89 df             	mov    %rbx,%rdi
  8aad82:	e8 09 f2 fe ff       	call   899f90 <CGenericModel::getKeyFrame(unsigned int, unsigned int)>
  8aad87:	48 89 84 24 d8 00 00 	mov    %rax,0xd8(%rsp)
  8aad8e:	00
  8aad8f:	48 8b b3 b8 01 00 00 	mov    0x1b8(%rbx),%rsi
  8aad96:	48 3b b3 c0 01 00 00 	cmp    0x1c0(%rbx),%rsi
  8aad9d:	0f 85 37 fd ff ff    	jne    8aaada <CGenericModel::updateAnimation(float, bool)+0x62a>
  8aada3:	48 8b bc 24 80 00 00 	mov    0x80(%rsp),%rdi
  8aadaa:	00
  8aadab:	48 8d 94 24 d8 00 00 	lea    0xd8(%rsp),%rdx
  8aadb2:	00
  8aadb3:	e8 08 7d 00 00       	call   8b2ac0 <std::vector<CKeyframe*, std::allocator<CKeyframe*> >::_M_insert_aux(__gnu_cxx::__normal_iterator<CKeyframe**, std::vector<CKeyframe*, std::allocator<CKeyframe*> > >, CKeyframe* const&)>
  8aadb8:	e9 d1 fd ff ff       	jmp    8aab8e <CGenericModel::updateAnimation(float, bool)+0x6de>
  8aadbd:	8b 54 24 30          	mov    0x30(%rsp),%edx
  8aadc1:	83 c2 01             	add    $0x1,%edx
  8aadc4:	48 63 d2             	movslq %edx,%rdx
  8aadc7:	48 89 d1             	mov    %rdx,%rcx
  8aadca:	48 01 c1             	add    %rax,%rcx
  8aadcd:	0f 88 ce 10 00 00    	js     8abea1 <CGenericModel::updateAnimation(float, bool)+0x19f1>
  8aadd3:	48 83 f9 3f          	cmp    $0x3f,%rcx
  8aadd7:	49 8d 14 d6          	lea    (%r14,%rdx,8),%rdx
  8aaddb:	7e 26                	jle    8aae03 <CGenericModel::updateAnimation(float, bool)+0x953>
  8aaddd:	48 85 c9             	test   %rcx,%rcx
  8aade0:	0f 8e bb 10 00 00    	jle    8abea1 <CGenericModel::updateAnimation(float, bool)+0x19f1>
  8aade6:	48 89 cd             	mov    %rcx,%rbp
  8aade9:	48 c1 fd 06          	sar    $0x6,%rbp
  8aaded:	48 89 ea             	mov    %rbp,%rdx
  8aadf0:	48 c1 e2 06          	shl    $0x6,%rdx
  8aadf4:	48 29 d1             	sub    %rdx,%rcx
  8aadf7:	48 8d 14 cd 00 00 00 	lea    0x0(,%rcx,8),%rdx
  8aadfe:	00
  8aadff:	49 03 14 ef          	add    (%r15,%rbp,8),%rdx
  8aae03:	48 8b 12             	mov    (%rdx),%rdx
  8aae06:	80 7a 26 00          	cmpb   $0x0,0x26(%rdx)
  8aae0a:	0f 84 c3 f8 ff ff    	je     8aa6d3 <CGenericModel::updateAnimation(float, bool)+0x223>
  8aae10:	44 8b 44 24 30       	mov    0x30(%rsp),%r8d
  8aae15:	31 d2                	xor    %edx,%edx
  8aae17:	45 85 c0             	test   %r8d,%r8d
  8aae1a:	0f 85 30 fa ff ff    	jne    8aa850 <CGenericModel::updateAnimation(float, bool)+0x3a0>
  8aae20:	84 d2                	test   %dl,%dl
  8aae22:	0f 84 48 fa ff ff    	je     8aa870 <CGenericModel::updateAnimation(float, bool)+0x3c0>
  8aae28:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aae2b:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aae31:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aae34:	0f 85 0a fe ff ff    	jne    8aac44 <CGenericModel::updateAnimation(float, bool)+0x794>
  8aae3a:	0f 8b 30 fa ff ff    	jnp    8aa870 <CGenericModel::updateAnimation(float, bool)+0x3c0>
  8aae40:	e9 ff fd ff ff       	jmp    8aac44 <CGenericModel::updateAnimation(float, bool)+0x794>
  8aae45:	0f 1f 00             	nopl   (%rax)
  8aae48:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aae4b:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aae4e:	66 90                	xchg   %ax,%ax
  8aae50:	7a 06                	jp     8aae58 <CGenericModel::updateAnimation(float, bool)+0x9a8>
  8aae52:	0f 84 c8 fb ff ff    	je     8aaa20 <CGenericModel::updateAnimation(float, bool)+0x570>
  8aae58:	48 8b 8b 70 01 00 00 	mov    0x170(%rbx),%rcx
  8aae5f:	48 8b b3 88 01 00 00 	mov    0x188(%rbx),%rsi
  8aae66:	48 89 ca             	mov    %rcx,%rdx
  8aae69:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8aae70:	48 c1 fa 03          	sar    $0x3,%rdx
  8aae74:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8aae79:	0f 88 75 06 00 00    	js     8ab4f4 <CGenericModel::updateAnimation(float, bool)+0x1044>
  8aae7f:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8aae84:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8aae88:	4a 8d 04 c1          	lea    (%rcx,%r8,8),%rax
  8aae8c:	7e 26                	jle    8aaeb4 <CGenericModel::updateAnimation(float, bool)+0xa04>
  8aae8e:	48 85 d2             	test   %rdx,%rdx
  8aae91:	0f 8e 5d 06 00 00    	jle    8ab4f4 <CGenericModel::updateAnimation(float, bool)+0x1044>
  8aae97:	48 89 d1             	mov    %rdx,%rcx
  8aae9a:	48 c1 f9 06          	sar    $0x6,%rcx
  8aae9e:	48 89 c8             	mov    %rcx,%rax
  8aaea1:	48 c1 e0 06          	shl    $0x6,%rax
  8aaea5:	48 29 c2             	sub    %rax,%rdx
  8aaea8:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8aaeaf:	00
  8aaeb0:	48 03 04 ce          	add    (%rsi,%rcx,8),%rax
  8aaeb4:	48 8b 00             	mov    (%rax),%rax
  8aaeb7:	80 78 25 00          	cmpb   $0x0,0x25(%rax)
  8aaebb:	0f 84 5f fb ff ff    	je     8aaa20 <CGenericModel::updateAnimation(float, bool)+0x570>
  8aaec1:	80 7c 24 7f 00       	cmpb   $0x0,0x7f(%rsp)
  8aaec6:	0f 84 e8 05 00 00    	je     8ab4b4 <CGenericModel::updateAnimation(float, bool)+0x1004>
  8aaecc:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  8aaed1:	44 39 83 54 01 00 00 	cmp    %r8d,0x154(%rbx)
  8aaed8:	0f 87 3a 04 00 00    	ja     8ab318 <CGenericModel::updateAnimation(float, bool)+0xe68>
  8aaede:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8aaee5:	48 8b 38             	mov    (%rax),%rdi
  8aaee8:	e8 3b 84 ca ff       	call   553328 <Ogre::AnimationState::setWeight(float)@plt>
  8aaeed:	f3 0f 10 84 24 ec 00 	movss  0xec(%rsp),%xmm0
  8aaef4:	00 00
  8aaef6:	0f 2e 44 24 5c       	ucomiss 0x5c(%rsp),%xmm0
  8aaefb:	0f 85 2a fb ff ff    	jne    8aaa2b <CGenericModel::updateAnimation(float, bool)+0x57b>
  8aaf01:	0f 8a 24 fb ff ff    	jp     8aaa2b <CGenericModel::updateAnimation(float, bool)+0x57b>
  8aaf07:	48 8b 8b 70 01 00 00 	mov    0x170(%rbx),%rcx
  8aaf0e:	48 8b b3 88 01 00 00 	mov    0x188(%rbx),%rsi
  8aaf15:	48 89 ca             	mov    %rcx,%rdx
  8aaf18:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8aaf1f:	48 c1 fa 03          	sar    $0x3,%rdx
  8aaf23:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8aaf28:	0f 88 a2 05 00 00    	js     8ab4d0 <CGenericModel::updateAnimation(float, bool)+0x1020>
  8aaf2e:	4c 8b 4c 24 20       	mov    0x20(%rsp),%r9
  8aaf33:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8aaf37:	4a 8d 04 c9          	lea    (%rcx,%r9,8),%rax
  8aaf3b:	7e 26                	jle    8aaf63 <CGenericModel::updateAnimation(float, bool)+0xab3>
  8aaf3d:	48 85 d2             	test   %rdx,%rdx
  8aaf40:	0f 8e 8a 05 00 00    	jle    8ab4d0 <CGenericModel::updateAnimation(float, bool)+0x1020>
  8aaf46:	48 89 d1             	mov    %rdx,%rcx
  8aaf49:	48 c1 f9 06          	sar    $0x6,%rcx
  8aaf4d:	48 89 c8             	mov    %rcx,%rax
  8aaf50:	48 c1 e0 06          	shl    $0x6,%rax
  8aaf54:	48 29 c2             	sub    %rax,%rdx
  8aaf57:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8aaf5e:	00
  8aaf5f:	48 03 04 ce          	add    (%rsi,%rcx,8),%rax
  8aaf63:	48 8b 00             	mov    (%rax),%rax
  8aaf66:	0f b6 54 24 60       	movzbl 0x60(%rsp),%edx
  8aaf6b:	80 78 2a 00          	cmpb   $0x0,0x2a(%rax)
  8aaf6f:	b8 01 00 00 00       	mov    $0x1,%eax
  8aaf74:	0f 45 d0             	cmovne %eax,%edx
  8aaf77:	88 54 24 60          	mov    %dl,0x60(%rsp)
  8aaf7b:	e9 ab fa ff ff       	jmp    8aaa2b <CGenericModel::updateAnimation(float, bool)+0x57b>
  8aaf80:	48 85 d2             	test   %rdx,%rdx
  8aaf83:	0f 8e 1f 02 00 00    	jle    8ab1a8 <CGenericModel::updateAnimation(float, bool)+0xcf8>
  8aaf89:	48 89 d1             	mov    %rdx,%rcx
  8aaf8c:	48 89 d5             	mov    %rdx,%rbp
  8aaf8f:	48 c1 f9 06          	sar    $0x6,%rcx
  8aaf93:	83 e5 3f             	and    $0x3f,%ebp
  8aaf96:	49 8b 0c cf          	mov    (%r15,%rcx,8),%rcx
  8aaf9a:	48 8b 0c e9          	mov    (%rcx,%rbp,8),%rcx
  8aaf9e:	8b 49 10             	mov    0x10(%rcx),%ecx
  8aafa1:	89 4c 24 2c          	mov    %ecx,0x2c(%rsp)
  8aafa5:	48 89 d1             	mov    %rdx,%rcx
  8aafa8:	48 c1 f9 06          	sar    $0x6,%rcx
  8aafac:	48 89 cd             	mov    %rcx,%rbp
  8aafaf:	48 c1 e5 06          	shl    $0x6,%rbp
  8aafb3:	48 29 ea             	sub    %rbp,%rdx
  8aafb6:	48 c1 e2 03          	shl    $0x3,%rdx
  8aafba:	49 03 14 cf          	add    (%r15,%rcx,8),%rdx
  8aafbe:	e9 e2 f6 ff ff       	jmp    8aa6a5 <CGenericModel::updateAnimation(float, bool)+0x1f5>
  8aafc3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8aafc8:	0f 57 c9             	xorps  %xmm1,%xmm1
  8aafcb:	f3 0f 10 40 2c       	movss  0x2c(%rax),%xmm0
  8aafd0:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8aafd3:	0f 87 2f 02 00 00    	ja     8ab208 <CGenericModel::updateAnimation(float, bool)+0xd58>
  8aafd9:	f3 0f 10 15 1b 98 6f 	movss  0x6f981b(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8aafe0:	00
  8aafe1:	f3 0f 11 54 24 5c    	movss  %xmm2,0x5c(%rsp)
  8aafe7:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  8aafed:	f3 0f 59 40 38       	mulss  0x38(%rax),%xmm0
  8aaff2:	f3 0f 10 48 18       	movss  0x18(%rax),%xmm1
  8aaff7:	0f 57 d2             	xorps  %xmm2,%xmm2
  8aaffa:	0f 2e ca             	ucomiss %xmm2,%xmm1
  8aaffd:	f3 0f 58 40 20       	addss  0x20(%rax),%xmm0
  8ab002:	f3 0f 11 40 20       	movss  %xmm0,0x20(%rax)
  8ab007:	7a 06                	jp     8ab00f <CGenericModel::updateAnimation(float, bool)+0xb5f>
  8ab009:	0f 84 79 02 00 00    	je     8ab288 <CGenericModel::updateAnimation(float, bool)+0xdd8>
  8ab00f:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8ab012:	0f 86 bb f8 ff ff    	jbe    8aa8d3 <CGenericModel::updateAnimation(float, bool)+0x423>
  8ab018:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  8ab01c:	80 78 24 00          	cmpb   $0x0,0x24(%rax)
  8ab020:	f3 0f 11 40 20       	movss  %xmm0,0x20(%rax)
  8ab025:	75 1c                	jne    8ab043 <CGenericModel::updateAnimation(float, bool)+0xb93>
  8ab027:	e9 58 04 00 00       	jmp    8ab484 <CGenericModel::updateAnimation(float, bool)+0xfd4>
  8ab02c:	0f 1f 40 00          	nopl   0x0(%rax)
  8ab030:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  8ab034:	80 78 24 00          	cmpb   $0x0,0x24(%rax)
  8ab038:	f3 0f 11 40 20       	movss  %xmm0,0x20(%rax)
  8ab03d:	0f 84 3d 04 00 00    	je     8ab480 <CGenericModel::updateAnimation(float, bool)+0xfd0>
  8ab043:	f3 0f 10 40 20       	movss  0x20(%rax),%xmm0
  8ab048:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8ab04b:	77 e3                	ja     8ab030 <CGenericModel::updateAnimation(float, bool)+0xb80>
  8ab04d:	c6 40 27 01          	movb   $0x1,0x27(%rax)
  8ab051:	e9 7d f8 ff ff       	jmp    8aa8d3 <CGenericModel::updateAnimation(float, bool)+0x423>
  8ab056:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  8ab05d:	00 00 00
  8ab060:	48 85 c0             	test   %rax,%rax
  8ab063:	0f 8e c7 02 00 00    	jle    8ab330 <CGenericModel::updateAnimation(float, bool)+0xe80>
  8ab069:	48 89 c2             	mov    %rax,%rdx
  8ab06c:	48 89 c1             	mov    %rax,%rcx
  8ab06f:	48 c1 fa 06          	sar    $0x6,%rdx
  8ab073:	83 e1 3f             	and    $0x3f,%ecx
  8ab076:	49 8b 14 d7          	mov    (%r15,%rdx,8),%rdx
  8ab07a:	48 8b 14 ca          	mov    (%rdx,%rcx,8),%rdx
  8ab07e:	f3 0f 10 4a 20       	movss  0x20(%rdx),%xmm1
  8ab083:	f3 0f 11 4c 24 10    	movss  %xmm1,0x10(%rsp)
  8ab089:	48 89 c2             	mov    %rax,%rdx
  8ab08c:	48 c1 fa 06          	sar    $0x6,%rdx
  8ab090:	48 89 d1             	mov    %rdx,%rcx
  8ab093:	48 c1 e1 06          	shl    $0x6,%rcx
  8ab097:	48 29 c8             	sub    %rcx,%rax
  8ab09a:	48 c1 e0 03          	shl    $0x3,%rax
  8ab09e:	49 03 04 d7          	add    (%r15,%rdx,8),%rax
  8ab0a2:	e9 7a f8 ff ff       	jmp    8aa921 <CGenericModel::updateAnimation(float, bool)+0x471>
  8ab0a7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8ab0ae:	00 00
  8ab0b0:	48 85 c0             	test   %rax,%rax
  8ab0b3:	0f 8e d7 02 00 00    	jle    8ab390 <CGenericModel::updateAnimation(float, bool)+0xee0>
  8ab0b9:	48 89 c2             	mov    %rax,%rdx
  8ab0bc:	48 89 c1             	mov    %rax,%rcx
  8ab0bf:	48 c1 fa 06          	sar    $0x6,%rdx
  8ab0c3:	83 e1 3f             	and    $0x3f,%ecx
  8ab0c6:	49 8b 14 d7          	mov    (%r15,%rdx,8),%rdx
  8ab0ca:	48 8b 14 ca          	mov    (%rdx,%rcx,8),%rdx
  8ab0ce:	f3 0f 10 4a 20       	movss  0x20(%rdx),%xmm1
  8ab0d3:	f3 0f 11 4c 24 18    	movss  %xmm1,0x18(%rsp)
  8ab0d9:	48 89 c2             	mov    %rax,%rdx
  8ab0dc:	48 89 c6             	mov    %rax,%rsi
  8ab0df:	48 c1 fa 06          	sar    $0x6,%rdx
  8ab0e3:	83 e6 3f             	and    $0x3f,%esi
  8ab0e6:	49 8b 0c d7          	mov    (%r15,%rdx,8),%rcx
  8ab0ea:	48 8b 0c f1          	mov    (%rcx,%rsi,8),%rcx
  8ab0ee:	0f b6 69 25          	movzbl 0x25(%rcx),%ebp
  8ab0f2:	48 89 d1             	mov    %rdx,%rcx
  8ab0f5:	48 c1 e1 06          	shl    $0x6,%rcx
  8ab0f9:	48 29 c8             	sub    %rcx,%rax
  8ab0fc:	48 c1 e0 03          	shl    $0x3,%rax
  8ab100:	49 03 04 d7          	add    (%r15,%rdx,8),%rax
  8ab104:	e9 ab f7 ff ff       	jmp    8aa8b4 <CGenericModel::updateAnimation(float, bool)+0x404>
  8ab109:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  8ab110:	4c 89 f2             	mov    %r14,%rdx
  8ab113:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8ab11a:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab11e:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8ab123:	0f 88 b9 03 00 00    	js     8ab4e2 <CGenericModel::updateAnimation(float, bool)+0x1032>
  8ab129:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8ab12e:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8ab132:	4b 8d 04 c6          	lea    (%r14,%r8,8),%rax
  8ab136:	7e 26                	jle    8ab15e <CGenericModel::updateAnimation(float, bool)+0xcae>
  8ab138:	48 85 d2             	test   %rdx,%rdx
  8ab13b:	0f 8e a1 03 00 00    	jle    8ab4e2 <CGenericModel::updateAnimation(float, bool)+0x1032>
  8ab141:	48 89 d1             	mov    %rdx,%rcx
  8ab144:	48 c1 f9 06          	sar    $0x6,%rcx
  8ab148:	48 89 c8             	mov    %rcx,%rax
  8ab14b:	48 c1 e0 06          	shl    $0x6,%rax
  8ab14f:	48 29 c2             	sub    %rax,%rdx
  8ab152:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8ab159:	00
  8ab15a:	49 03 04 cf          	add    (%r15,%rcx,8),%rax
  8ab15e:	48 8b 00             	mov    (%rax),%rax
  8ab161:	80 78 25 00          	cmpb   $0x0,0x25(%rax)
  8ab165:	0f 84 d5 02 00 00    	je     8ab440 <CGenericModel::updateAnimation(float, bool)+0xf90>
  8ab16b:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  8ab170:	44 39 83 54 01 00 00 	cmp    %r8d,0x154(%rbx)
  8ab177:	77 77                	ja     8ab1f0 <CGenericModel::updateAnimation(float, bool)+0xd40>
  8ab179:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8ab180:	48 8b 38             	mov    (%rax),%rdi
  8ab183:	f3 0f 10 44 24 10    	movss  0x10(%rsp),%xmm0
  8ab189:	e8 3a 9f ca ff       	call   5550c8 <Ogre::AnimationState::setTimePosition(float)@plt>
  8ab18e:	f3 0f 10 84 24 ec 00 	movss  0xec(%rsp),%xmm0
  8ab195:	00 00
  8ab197:	c6 44 24 7e 01       	movb   $0x1,0x7e(%rsp)
  8ab19c:	e9 a9 f7 ff ff       	jmp    8aa94a <CGenericModel::updateAnimation(float, bool)+0x49a>
  8ab1a1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  8ab1a8:	48 89 d1             	mov    %rdx,%rcx
  8ab1ab:	49 89 d1             	mov    %rdx,%r9
  8ab1ae:	48 f7 d1             	not    %rcx
  8ab1b1:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab1b5:	48 f7 d1             	not    %rcx
  8ab1b8:	49 8b 2c cf          	mov    (%r15,%rcx,8),%rbp
  8ab1bc:	49 89 c8             	mov    %rcx,%r8
  8ab1bf:	49 c1 e0 06          	shl    $0x6,%r8
  8ab1c3:	4d 29 c1             	sub    %r8,%r9
  8ab1c6:	48 85 d2             	test   %rdx,%rdx
  8ab1c9:	4a 8b 6c cd 00       	mov    0x0(%rbp,%r9,8),%rbp
  8ab1ce:	8b 6d 10             	mov    0x10(%rbp),%ebp
  8ab1d1:	89 6c 24 2c          	mov    %ebp,0x2c(%rsp)
  8ab1d5:	0f 88 d1 fd ff ff    	js     8aafac <CGenericModel::updateAnimation(float, bool)+0xafc>
  8ab1db:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8ab1df:	0f 8e b7 f4 ff ff    	jle    8aa69c <CGenericModel::updateAnimation(float, bool)+0x1ec>
  8ab1e5:	e9 bb fd ff ff       	jmp    8aafa5 <CGenericModel::updateAnimation(float, bool)+0xaf5>
  8ab1ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8ab1f0:	8b 44 24 2c          	mov    0x2c(%rsp),%eax
  8ab1f4:	48 c1 e0 03          	shl    $0x3,%rax
  8ab1f8:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8ab1ff:	e9 7c ff ff ff       	jmp    8ab180 <CGenericModel::updateAnimation(float, bool)+0xcd0>
  8ab204:	0f 1f 40 00          	nopl   0x0(%rax)
  8ab208:	f3 0f 5c 44 24 38    	subss  0x38(%rsp),%xmm0
  8ab20e:	0f 57 d2             	xorps  %xmm2,%xmm2
  8ab211:	f3 0f 11 40 2c       	movss  %xmm0,0x2c(%rax)
  8ab216:	c7 44 24 5c 00 00 80 	movl   $0x3f800000,0x5c(%rsp)
  8ab21d:	3f
  8ab21e:	c7 40 34 00 00 80 3f 	movl   $0x3f800000,0x34(%rax)
  8ab225:	f3 0f 10 48 30       	movss  0x30(%rax),%xmm1
  8ab22a:	0f 2e ca             	ucomiss %xmm2,%xmm1
  8ab22d:	7a 02                	jp     8ab231 <CGenericModel::updateAnimation(float, bool)+0xd81>
  8ab22f:	74 32                	je     8ab263 <CGenericModel::updateAnimation(float, bool)+0xdb3>
  8ab231:	0f 2e c2             	ucomiss %xmm2,%xmm0
  8ab234:	76 2d                	jbe    8ab263 <CGenericModel::updateAnimation(float, bool)+0xdb3>
  8ab236:	0f 28 d0             	movaps %xmm0,%xmm2
  8ab239:	f3 0f 10 1d bb 95 6f 	movss  0x6f95bb(%rip),%xmm3        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8ab240:	00
  8ab241:	f3 0f 5e d1          	divss  %xmm1,%xmm2
  8ab245:	0f 28 ca             	movaps %xmm2,%xmm1
  8ab248:	f3 0f 10 15 ac 95 6f 	movss  0x6f95ac(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8ab24f:	00
  8ab250:	f3 0f c2 d1 05       	cmpnltss %xmm1,%xmm2
  8ab255:	0f 54 ca             	andps  %xmm2,%xmm1
  8ab258:	0f 55 d3             	andnps %xmm3,%xmm2
  8ab25b:	0f 56 d1             	orps   %xmm1,%xmm2
  8ab25e:	f3 0f 11 50 34       	movss  %xmm2,0x34(%rax)
  8ab263:	0f 57 c9             	xorps  %xmm1,%xmm1
  8ab266:	0f 2e c8             	ucomiss %xmm0,%xmm1
  8ab269:	0f 82 78 fd ff ff    	jb     8aafe7 <CGenericModel::updateAnimation(float, bool)+0xb37>
  8ab26f:	c6 40 29 01          	movb   $0x1,0x29(%rax)
  8ab273:	f3 0f 11 48 34       	movss  %xmm1,0x34(%rax)
  8ab278:	f3 0f 11 48 2c       	movss  %xmm1,0x2c(%rax)
  8ab27d:	e9 65 fd ff ff       	jmp    8aafe7 <CGenericModel::updateAnimation(float, bool)+0xb37>
  8ab282:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8ab288:	80 78 24 00          	cmpb   $0x0,0x24(%rax)
  8ab28c:	0f 85 de 01 00 00    	jne    8ab470 <CGenericModel::updateAnimation(float, bool)+0xfc0>
  8ab292:	c7 40 20 00 00 00 00 	movl   $0x0,0x20(%rax)
  8ab299:	c6 40 25 00          	movb   $0x0,0x25(%rax)
  8ab29d:	c6 40 28 01          	movb   $0x1,0x28(%rax)
  8ab2a1:	c6 40 29 01          	movb   $0x1,0x29(%rax)
  8ab2a5:	e9 29 f6 ff ff       	jmp    8aa8d3 <CGenericModel::updateAnimation(float, bool)+0x423>
  8ab2aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8ab2b0:	48 8b 8b 70 01 00 00 	mov    0x170(%rbx),%rcx
  8ab2b7:	48 8b b3 88 01 00 00 	mov    0x188(%rbx),%rsi
  8ab2be:	48 89 ca             	mov    %rcx,%rdx
  8ab2c1:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8ab2c8:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab2cc:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8ab2d1:	0f 88 2f 02 00 00    	js     8ab506 <CGenericModel::updateAnimation(float, bool)+0x1056>
  8ab2d7:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8ab2dc:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8ab2e0:	4a 8d 04 c1          	lea    (%rcx,%r8,8),%rax
  8ab2e4:	7e 26                	jle    8ab30c <CGenericModel::updateAnimation(float, bool)+0xe5c>
  8ab2e6:	48 85 d2             	test   %rdx,%rdx
  8ab2e9:	0f 8e 17 02 00 00    	jle    8ab506 <CGenericModel::updateAnimation(float, bool)+0x1056>
  8ab2ef:	48 89 d1             	mov    %rdx,%rcx
  8ab2f2:	48 c1 f9 06          	sar    $0x6,%rcx
  8ab2f6:	48 89 c8             	mov    %rcx,%rax
  8ab2f9:	48 c1 e0 06          	shl    $0x6,%rax
  8ab2fd:	48 29 c2             	sub    %rax,%rdx
  8ab300:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8ab307:	00
  8ab308:	48 03 04 ce          	add    (%rsi,%rcx,8),%rax
  8ab30c:	48 8b 00             	mov    (%rax),%rax
  8ab30f:	c6 40 28 01          	movb   $0x1,0x28(%rax)
  8ab313:	e9 a7 f8 ff ff       	jmp    8aabbf <CGenericModel::updateAnimation(float, bool)+0x70f>
  8ab318:	8b 44 24 2c          	mov    0x2c(%rsp),%eax
  8ab31c:	48 c1 e0 03          	shl    $0x3,%rax
  8ab320:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8ab327:	e9 b9 fb ff ff       	jmp    8aaee5 <CGenericModel::updateAnimation(float, bool)+0xa35>
  8ab32c:	0f 1f 40 00          	nopl   0x0(%rax)
  8ab330:	48 89 c2             	mov    %rax,%rdx
  8ab333:	49 89 c0             	mov    %rax,%r8
  8ab336:	48 f7 d2             	not    %rdx
  8ab339:	48 c1 ea 06          	shr    $0x6,%rdx
  8ab33d:	48 f7 d2             	not    %rdx
  8ab340:	49 8b 0c d7          	mov    (%r15,%rdx,8),%rcx
  8ab344:	48 89 d6             	mov    %rdx,%rsi
  8ab347:	48 c1 e6 06          	shl    $0x6,%rsi
  8ab34b:	49 29 f0             	sub    %rsi,%r8
  8ab34e:	48 85 c0             	test   %rax,%rax
  8ab351:	4a 8b 0c c1          	mov    (%rcx,%r8,8),%rcx
  8ab355:	f3 0f 10 41 20       	movss  0x20(%rcx),%xmm0
  8ab35a:	f3 0f 11 44 24 10    	movss  %xmm0,0x10(%rsp)
  8ab360:	0f 88 2a fd ff ff    	js     8ab090 <CGenericModel::updateAnimation(float, bool)+0xbe0>
  8ab366:	48 83 f8 3f          	cmp    $0x3f,%rax
  8ab36a:	0f 8e a8 f5 ff ff    	jle    8aa918 <CGenericModel::updateAnimation(float, bool)+0x468>
  8ab370:	e9 14 fd ff ff       	jmp    8ab089 <CGenericModel::updateAnimation(float, bool)+0xbd9>
  8ab375:	0f 1f 00             	nopl   (%rax)
  8ab378:	48 89 d1             	mov    %rdx,%rcx
  8ab37b:	48 f7 d1             	not    %rcx
  8ab37e:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab382:	48 f7 d1             	not    %rcx
  8ab385:	e9 7b f8 ff ff       	jmp    8aac05 <CGenericModel::updateAnimation(float, bool)+0x755>
  8ab38a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8ab390:	48 89 c2             	mov    %rax,%rdx
  8ab393:	49 89 c0             	mov    %rax,%r8
  8ab396:	48 f7 d2             	not    %rdx
  8ab399:	48 c1 ea 06          	shr    $0x6,%rdx
  8ab39d:	48 f7 d2             	not    %rdx
  8ab3a0:	49 8b 0c d7          	mov    (%r15,%rdx,8),%rcx
  8ab3a4:	48 89 d6             	mov    %rdx,%rsi
  8ab3a7:	48 c1 e6 06          	shl    $0x6,%rsi
  8ab3ab:	49 29 f0             	sub    %rsi,%r8
  8ab3ae:	48 85 c0             	test   %rax,%rax
  8ab3b1:	4a 8b 0c c1          	mov    (%rcx,%r8,8),%rcx
  8ab3b5:	f3 0f 10 41 20       	movss  0x20(%rcx),%xmm0
  8ab3ba:	f3 0f 11 44 24 18    	movss  %xmm0,0x18(%rsp)
  8ab3c0:	0f 89 7f 0d 00 00    	jns    8ac145 <CGenericModel::updateAnimation(float, bool)+0x1c95>
  8ab3c6:	0f b6 69 25          	movzbl 0x25(%rcx),%ebp
  8ab3ca:	e9 23 fd ff ff       	jmp    8ab0f2 <CGenericModel::updateAnimation(float, bool)+0xc42>
  8ab3cf:	90                   	nop
  8ab3d0:	4c 89 f2             	mov    %r14,%rdx
  8ab3d3:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8ab3da:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab3de:	48 03 54 24 20       	add    0x20(%rsp),%rdx
  8ab3e3:	0f 88 a6 0a 00 00    	js     8abe8f <CGenericModel::updateAnimation(float, bool)+0x19df>
  8ab3e9:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8ab3ee:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8ab3f2:	4b 8d 04 c6          	lea    (%r14,%r8,8),%rax
  8ab3f6:	7e 26                	jle    8ab41e <CGenericModel::updateAnimation(float, bool)+0xf6e>
  8ab3f8:	48 85 d2             	test   %rdx,%rdx
  8ab3fb:	0f 8e 8e 0a 00 00    	jle    8abe8f <CGenericModel::updateAnimation(float, bool)+0x19df>
  8ab401:	48 89 d1             	mov    %rdx,%rcx
  8ab404:	48 c1 f9 06          	sar    $0x6,%rcx
  8ab408:	48 89 c8             	mov    %rcx,%rax
  8ab40b:	48 c1 e0 06          	shl    $0x6,%rax
  8ab40f:	48 29 c2             	sub    %rax,%rdx
  8ab412:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8ab419:	00
  8ab41a:	49 03 04 cf          	add    (%r15,%rcx,8),%rax
  8ab41e:	48 8b 00             	mov    (%rax),%rax
  8ab421:	c6 40 2a 01          	movb   $0x1,0x2a(%rax)
  8ab425:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8ab42c:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8ab433:	e9 38 f4 ff ff       	jmp    8aa870 <CGenericModel::updateAnimation(float, bool)+0x3c0>
  8ab438:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  8ab43f:	00
  8ab440:	40 84 ed             	test   %bpl,%bpl
  8ab443:	0f 85 22 fd ff ff    	jne    8ab16b <CGenericModel::updateAnimation(float, bool)+0xcbb>
  8ab449:	80 7c 24 7f 00       	cmpb   $0x0,0x7f(%rsp)
  8ab44e:	0f 85 17 fd ff ff    	jne    8ab16b <CGenericModel::updateAnimation(float, bool)+0xcbb>
  8ab454:	f3 0f 10 4c 24 18    	movss  0x18(%rsp),%xmm1
  8ab45a:	0f 2e 4c 24 10       	ucomiss 0x10(%rsp),%xmm1
  8ab45f:	0f 8a 06 fd ff ff    	jp     8ab16b <CGenericModel::updateAnimation(float, bool)+0xcbb>
  8ab465:	0f 84 df f4 ff ff    	je     8aa94a <CGenericModel::updateAnimation(float, bool)+0x49a>
  8ab46b:	e9 fb fc ff ff       	jmp    8ab16b <CGenericModel::updateAnimation(float, bool)+0xcbb>
  8ab470:	c6 40 27 01          	movb   $0x1,0x27(%rax)
  8ab474:	c7 40 20 00 00 00 00 	movl   $0x0,0x20(%rax)
  8ab47b:	e9 53 f4 ff ff       	jmp    8aa8d3 <CGenericModel::updateAnimation(float, bool)+0x423>
  8ab480:	c6 40 27 01          	movb   $0x1,0x27(%rax)
  8ab484:	f3 0f 11 48 20       	movss  %xmm1,0x20(%rax)
  8ab489:	c6 40 28 01          	movb   $0x1,0x28(%rax)
  8ab48d:	c6 40 29 01          	movb   $0x1,0x29(%rax)
  8ab491:	c6 40 25 00          	movb   $0x0,0x25(%rax)
  8ab495:	e9 39 f4 ff ff       	jmp    8aa8d3 <CGenericModel::updateAnimation(float, bool)+0x423>
  8ab49a:	48 8b bc 24 80 00 00 	mov    0x80(%rsp),%rdi
  8ab4a1:	00
  8ab4a2:	48 8d 94 24 d0 00 00 	lea    0xd0(%rsp),%rdx
  8ab4a9:	00
  8ab4aa:	e8 11 76 00 00       	call   8b2ac0 <std::vector<CKeyframe*, std::allocator<CKeyframe*> >::_M_insert_aux(__gnu_cxx::__normal_iterator<CKeyframe**, std::vector<CKeyframe*, std::allocator<CKeyframe*> > >, CKeyframe* const&)>
  8ab4af:	e9 da f6 ff ff       	jmp    8aab8e <CGenericModel::updateAnimation(float, bool)+0x6de>
  8ab4b4:	f3 0f 10 4c 24 18    	movss  0x18(%rsp),%xmm1
  8ab4ba:	0f 2e 4c 24 10       	ucomiss 0x10(%rsp),%xmm1
  8ab4bf:	0f 8a 07 fa ff ff    	jp     8aaecc <CGenericModel::updateAnimation(float, bool)+0xa1c>
  8ab4c5:	0f 84 55 f5 ff ff    	je     8aaa20 <CGenericModel::updateAnimation(float, bool)+0x570>
  8ab4cb:	e9 fc f9 ff ff       	jmp    8aaecc <CGenericModel::updateAnimation(float, bool)+0xa1c>
  8ab4d0:	48 89 d1             	mov    %rdx,%rcx
  8ab4d3:	48 f7 d1             	not    %rcx
  8ab4d6:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab4da:	48 f7 d1             	not    %rcx
  8ab4dd:	e9 6b fa ff ff       	jmp    8aaf4d <CGenericModel::updateAnimation(float, bool)+0xa9d>
  8ab4e2:	48 89 d1             	mov    %rdx,%rcx
  8ab4e5:	48 f7 d1             	not    %rcx
  8ab4e8:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab4ec:	48 f7 d1             	not    %rcx
  8ab4ef:	e9 54 fc ff ff       	jmp    8ab148 <CGenericModel::updateAnimation(float, bool)+0xc98>
  8ab4f4:	48 89 d1             	mov    %rdx,%rcx
  8ab4f7:	48 f7 d1             	not    %rcx
  8ab4fa:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab4fe:	48 f7 d1             	not    %rcx
  8ab501:	e9 98 f9 ff ff       	jmp    8aae9e <CGenericModel::updateAnimation(float, bool)+0x9ee>
  8ab506:	48 89 d1             	mov    %rdx,%rcx
  8ab509:	48 f7 d1             	not    %rcx
  8ab50c:	48 c1 e9 06          	shr    $0x6,%rcx
  8ab510:	48 f7 d1             	not    %rcx
  8ab513:	e9 de fd ff ff       	jmp    8ab2f6 <CGenericModel::updateAnimation(float, bool)+0xe46>
  8ab518:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8ab51f:	48 8b 83 80 01 00 00 	mov    0x180(%rbx),%rax
  8ab526:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8ab52d:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8ab534:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8ab53b:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8ab542:	f3 0f 10 54 24 38    	movss  0x38(%rsp),%xmm2
  8ab548:	0f 2e 15 a9 92 6f 00 	ucomiss 0x6f92a9(%rip),%xmm2        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  8ab54f:	0f 84 d3 08 00 00    	je     8abe28 <CGenericModel::updateAnimation(float, bool)+0x1978>
  8ab555:	48 89 c1             	mov    %rax,%rcx
  8ab558:	48 29 ef             	sub    %rbp,%rdi
  8ab55b:	4c 29 f1             	sub    %r14,%rcx
  8ab55e:	48 c1 ff 03          	sar    $0x3,%rdi
  8ab562:	48 c1 f9 03          	sar    $0x3,%rcx
  8ab566:	48 8d 3c 39          	lea    (%rcx,%rdi,1),%rdi
  8ab56a:	48 89 d1             	mov    %rdx,%rcx
  8ab56d:	4c 29 f9             	sub    %r15,%rcx
  8ab570:	48 c1 f9 03          	sar    $0x3,%rcx
  8ab574:	48 c1 e1 06          	shl    $0x6,%rcx
  8ab578:	8d 4c 0f c0          	lea    -0x40(%rdi,%rcx,1),%ecx
  8ab57c:	83 f9 01             	cmp    $0x1,%ecx
  8ab57f:	0f 8e c9 08 00 00    	jle    8abe4e <CGenericModel::updateAnimation(float, bool)+0x199e>
  8ab585:	4c 8d 83 b0 01 00 00 	lea    0x1b0(%rbx),%r8
  8ab58c:	c7 44 24 20 01 00 00 	movl   $0x1,0x20(%rsp)
  8ab593:	00
  8ab594:	4c 89 44 24 30       	mov    %r8,0x30(%rsp)
  8ab599:	eb 49                	jmp    8ab5e4 <CGenericModel::updateAnimation(float, bool)+0x1134>
  8ab59b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8ab5a0:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8ab5a7:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8ab5ae:	48 89 d1             	mov    %rdx,%rcx
  8ab5b1:	48 89 c6             	mov    %rax,%rsi
  8ab5b4:	48 29 ef             	sub    %rbp,%rdi
  8ab5b7:	4c 29 f9             	sub    %r15,%rcx
  8ab5ba:	4c 29 f6             	sub    %r14,%rsi
  8ab5bd:	48 c1 ff 03          	sar    $0x3,%rdi
  8ab5c1:	48 c1 f9 03          	sar    $0x3,%rcx
  8ab5c5:	48 c1 fe 03          	sar    $0x3,%rsi
  8ab5c9:	48 c1 e1 06          	shl    $0x6,%rcx
  8ab5cd:	83 44 24 20 01       	addl   $0x1,0x20(%rsp)
  8ab5d2:	48 8d 34 37          	lea    (%rdi,%rsi,1),%rsi
  8ab5d6:	8d 4c 0e c0          	lea    -0x40(%rsi,%rcx,1),%ecx
  8ab5da:	3b 4c 24 20          	cmp    0x20(%rsp),%ecx
  8ab5de:	0f 8e 6a 08 00 00    	jle    8abe4e <CGenericModel::updateAnimation(float, bool)+0x199e>
  8ab5e4:	48 8b 8b 78 01 00 00 	mov    0x178(%rbx),%rcx
  8ab5eb:	4c 63 64 24 20       	movslq 0x20(%rsp),%r12
  8ab5f0:	4d 89 f1             	mov    %r14,%r9
  8ab5f3:	49 29 c9             	sub    %rcx,%r9
  8ab5f6:	49 c1 f9 03          	sar    $0x3,%r9
  8ab5fa:	4c 89 ce             	mov    %r9,%rsi
  8ab5fd:	4c 01 e6             	add    %r12,%rsi
  8ab600:	0f 88 5a 06 00 00    	js     8abc60 <CGenericModel::updateAnimation(float, bool)+0x17b0>
  8ab606:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab60a:	4b 8d 3c e6          	lea    (%r14,%r12,8),%rdi
  8ab60e:	7e 28                	jle    8ab638 <CGenericModel::updateAnimation(float, bool)+0x1188>
  8ab610:	48 85 f6             	test   %rsi,%rsi
  8ab613:	0f 8e 47 06 00 00    	jle    8abc60 <CGenericModel::updateAnimation(float, bool)+0x17b0>
  8ab619:	48 89 f5             	mov    %rsi,%rbp
  8ab61c:	48 c1 fd 06          	sar    $0x6,%rbp
  8ab620:	48 89 ef             	mov    %rbp,%rdi
  8ab623:	49 89 f0             	mov    %rsi,%r8
  8ab626:	48 c1 e7 06          	shl    $0x6,%rdi
  8ab62a:	49 29 f8             	sub    %rdi,%r8
  8ab62d:	4c 89 c7             	mov    %r8,%rdi
  8ab630:	48 c1 e7 03          	shl    $0x3,%rdi
  8ab634:	49 03 3c ef          	add    (%r15,%rbp,8),%rdi
  8ab638:	48 8b 3f             	mov    (%rdi),%rdi
  8ab63b:	80 7f 28 00          	cmpb   $0x0,0x28(%rdi)
  8ab63f:	0f 84 5b ff ff ff    	je     8ab5a0 <CGenericModel::updateAnimation(float, bool)+0x10f0>
  8ab645:	49 89 f5             	mov    %rsi,%r13
  8ab648:	4a 8d 04 e5 00 00 00 	lea    0x0(,%r12,8),%rax
  8ab64f:	00
  8ab650:	49 89 f3             	mov    %rsi,%r11
  8ab653:	49 f7 d5             	not    %r13
  8ab656:	4c 89 f7             	mov    %r14,%rdi
  8ab659:	4c 89 74 24 10       	mov    %r14,0x10(%rsp)
  8ab65e:	49 c1 ed 06          	shr    $0x6,%r13
  8ab662:	4d 8d 14 06          	lea    (%r14,%rax,1),%r10
  8ab666:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  8ab66b:	49 c1 fb 06          	sar    $0x6,%r11
  8ab66f:	49 f7 d5             	not    %r13
  8ab672:	4c 89 c8             	mov    %r9,%rax
  8ab675:	44 8b 74 24 20       	mov    0x20(%rsp),%r14d
  8ab67a:	48 89 8c 24 80 00 00 	mov    %rcx,0x80(%rsp)
  8ab681:	00
  8ab682:	eb 4b                	jmp    8ab6cf <CGenericModel::updateAnimation(float, bool)+0x121f>
  8ab684:	0f 1f 40 00          	nopl   0x0(%rax)
  8ab688:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab68c:	4c 89 d2             	mov    %r10,%rdx
  8ab68f:	7e 20                	jle    8ab6b1 <CGenericModel::updateAnimation(float, bool)+0x1201>
  8ab691:	48 85 f6             	test   %rsi,%rsi
  8ab694:	7e 7a                	jle    8ab710 <CGenericModel::updateAnimation(float, bool)+0x1260>
  8ab696:	4d 89 d8             	mov    %r11,%r8
  8ab699:	4c 89 c2             	mov    %r8,%rdx
  8ab69c:	48 89 f1             	mov    %rsi,%rcx
  8ab69f:	48 c1 e2 06          	shl    $0x6,%rdx
  8ab6a3:	48 29 d1             	sub    %rdx,%rcx
  8ab6a6:	48 89 ca             	mov    %rcx,%rdx
  8ab6a9:	48 c1 e2 03          	shl    $0x3,%rdx
  8ab6ad:	4b 03 14 c7          	add    (%r15,%r8,8),%rdx
  8ab6b1:	48 8b 12             	mov    (%rdx),%rdx
  8ab6b4:	3b 6a 10             	cmp    0x10(%rdx),%ebp
  8ab6b7:	0f 84 b3 04 00 00    	je     8abb70 <CGenericModel::updateAnimation(float, bool)+0x16c0>
  8ab6bd:	48 83 c0 01          	add    $0x1,%rax
  8ab6c1:	48 83 c7 08          	add    $0x8,%rdi
  8ab6c5:	89 c2                	mov    %eax,%edx
  8ab6c7:	44 29 ca             	sub    %r9d,%edx
  8ab6ca:	41 39 d6             	cmp    %edx,%r14d
  8ab6cd:	7e 61                	jle    8ab730 <CGenericModel::updateAnimation(float, bool)+0x1280>
  8ab6cf:	48 85 c0             	test   %rax,%rax
  8ab6d2:	78 09                	js     8ab6dd <CGenericModel::updateAnimation(float, bool)+0x122d>
  8ab6d4:	48 83 f8 3f          	cmp    $0x3f,%rax
  8ab6d8:	48 89 fa             	mov    %rdi,%rdx
  8ab6db:	7e 24                	jle    8ab701 <CGenericModel::updateAnimation(float, bool)+0x1251>
  8ab6dd:	48 85 c0             	test   %rax,%rax
  8ab6e0:	7e 36                	jle    8ab718 <CGenericModel::updateAnimation(float, bool)+0x1268>
  8ab6e2:	48 89 c5             	mov    %rax,%rbp
  8ab6e5:	48 c1 fd 06          	sar    $0x6,%rbp
  8ab6e9:	48 89 ea             	mov    %rbp,%rdx
  8ab6ec:	48 89 c1             	mov    %rax,%rcx
  8ab6ef:	48 c1 e2 06          	shl    $0x6,%rdx
  8ab6f3:	48 29 d1             	sub    %rdx,%rcx
  8ab6f6:	48 89 ca             	mov    %rcx,%rdx
  8ab6f9:	48 c1 e2 03          	shl    $0x3,%rdx
  8ab6fd:	49 03 14 ef          	add    (%r15,%rbp,8),%rdx
  8ab701:	48 8b 12             	mov    (%rdx),%rdx
  8ab704:	48 85 f6             	test   %rsi,%rsi
  8ab707:	8b 6a 10             	mov    0x10(%rdx),%ebp
  8ab70a:	0f 89 78 ff ff ff    	jns    8ab688 <CGenericModel::updateAnimation(float, bool)+0x11d8>
  8ab710:	4d 89 e8             	mov    %r13,%r8
  8ab713:	eb 84                	jmp    8ab699 <CGenericModel::updateAnimation(float, bool)+0x11e9>
  8ab715:	0f 1f 00             	nopl   (%rax)
  8ab718:	48 89 c5             	mov    %rax,%rbp
  8ab71b:	48 f7 d5             	not    %rbp
  8ab71e:	48 c1 ed 06          	shr    $0x6,%rbp
  8ab722:	48 f7 d5             	not    %rbp
  8ab725:	eb c2                	jmp    8ab6e9 <CGenericModel::updateAnimation(float, bool)+0x1239>
  8ab727:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8ab72e:	00 00
  8ab730:	48 85 f6             	test   %rsi,%rsi
  8ab733:	78 0d                	js     8ab742 <CGenericModel::updateAnimation(float, bool)+0x1292>
  8ab735:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab739:	7e 1d                	jle    8ab758 <CGenericModel::updateAnimation(float, bool)+0x12a8>
  8ab73b:	48 85 f6             	test   %rsi,%rsi
  8ab73e:	4d 0f 4f eb          	cmovg  %r11,%r13
  8ab742:	4c 89 e8             	mov    %r13,%rax
  8ab745:	48 c1 e0 06          	shl    $0x6,%rax
  8ab749:	48 29 c6             	sub    %rax,%rsi
  8ab74c:	4c 8d 14 f5 00 00 00 	lea    0x0(,%rsi,8),%r10
  8ab753:	00
  8ab754:	4f 03 14 ef          	add    (%r15,%r13,8),%r10
  8ab758:	49 8b 02             	mov    (%r10),%rax
  8ab75b:	8b 40 10             	mov    0x10(%rax),%eax
  8ab75e:	3b 83 54 01 00 00    	cmp    0x154(%rbx),%eax
  8ab764:	0f 82 6e 05 00 00    	jb     8abcd8 <CGenericModel::updateAnimation(float, bool)+0x1828>
  8ab76a:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  8ab771:	48 8b 38             	mov    (%rax),%rdi
  8ab774:	31 f6                	xor    %esi,%esi
  8ab776:	e8 fd a7 ca ff       	call   555f78 <Ogre::AnimationState::setEnabled(bool)@plt>
  8ab77b:	48 8b 8b 78 01 00 00 	mov    0x178(%rbx),%rcx
  8ab782:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8ab789:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8ab790:	4c 89 f2             	mov    %r14,%rdx
  8ab793:	4c 89 f5             	mov    %r14,%rbp
  8ab796:	4d 89 f8             	mov    %r15,%r8
  8ab799:	48 29 ca             	sub    %rcx,%rdx
  8ab79c:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab7a0:	48 89 d6             	mov    %rdx,%rsi
  8ab7a3:	4c 01 e6             	add    %r12,%rsi
  8ab7a6:	0f 88 8c 05 00 00    	js     8abd38 <CGenericModel::updateAnimation(float, bool)+0x1888>
  8ab7ac:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab7b0:	0f 8f 02 04 00 00    	jg     8abbb8 <CGenericModel::updateAnimation(float, bool)+0x1708>
  8ab7b6:	4b 8b 04 e6          	mov    (%r14,%r12,8),%rax
  8ab7ba:	f3 0f 10 48 20       	movss  0x20(%rax),%xmm1
  8ab7bf:	48 8b 7c 24 18       	mov    0x18(%rsp),%rdi
  8ab7c4:	49 8d 3c 3e          	lea    (%r14,%rdi,1),%rdi
  8ab7c8:	48 8b 07             	mov    (%rdi),%rax
  8ab7cb:	f3 0f 10 40 18       	movss  0x18(%rax),%xmm0
  8ab7d0:	0f 2e c1             	ucomiss %xmm1,%xmm0
  8ab7d3:	0f 86 8c 01 00 00    	jbe    8ab965 <CGenericModel::updateAnimation(float, bool)+0x14b5>
  8ab7d9:	48 85 f6             	test   %rsi,%rsi
  8ab7dc:	0f 88 ec 05 00 00    	js     8abdce <CGenericModel::updateAnimation(float, bool)+0x191e>
  8ab7e2:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab7e6:	0f 8f fe 04 00 00    	jg     8abcea <CGenericModel::updateAnimation(float, bool)+0x183a>
  8ab7ec:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  8ab7f1:	49 8d 04 06          	lea    (%r14,%rax,1),%rax
  8ab7f5:	48 8b 00             	mov    (%rax),%rax
  8ab7f8:	8b 40 10             	mov    0x10(%rax),%eax
  8ab7fb:	89 44 24 2c          	mov    %eax,0x2c(%rsp)
  8ab7ff:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8ab806:	4d 85 ed             	test   %r13,%r13
  8ab809:	0f 84 56 01 00 00    	je     8ab965 <CGenericModel::updateAnimation(float, bool)+0x14b5>
  8ab80f:	89 c0                	mov    %eax,%eax
  8ab811:	48 8d 04 40          	lea    (%rax,%rax,2),%rax
  8ab815:	48 c1 e0 03          	shl    $0x3,%rax
  8ab819:	48 89 44 24 10       	mov    %rax,0x10(%rsp)
  8ab81e:	48 89 c7             	mov    %rax,%rdi
  8ab821:	49 03 7d 58          	add    0x58(%r13),%rdi
  8ab825:	48 8b 07             	mov    (%rdi),%rax
  8ab828:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  8ab82c:	48 29 c7             	sub    %rax,%rdi
  8ab82f:	48 c1 ef 03          	shr    $0x3,%rdi
  8ab833:	85 ff                	test   %edi,%edi
  8ab835:	0f 84 2a 01 00 00    	je     8ab965 <CGenericModel::updateAnimation(float, bool)+0x14b5>
  8ab83b:	31 ed                	xor    %ebp,%ebp
  8ab83d:	eb 51                	jmp    8ab890 <CGenericModel::updateAnimation(float, bool)+0x13e0>
  8ab83f:	90                   	nop
  8ab840:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  8ab845:	49 8d 14 16          	lea    (%r14,%rdx,1),%rdx
  8ab849:	89 ee                	mov    %ebp,%esi
  8ab84b:	48 8b 12             	mov    (%rdx),%rdx
  8ab84e:	48 8b 04 f0          	mov    (%rax,%rsi,8),%rax
  8ab852:	f3 0f 10 40 10       	movss  0x10(%rax),%xmm0
  8ab857:	f3 0f 5e 05 c1 8f 6f 	divss  0x6f8fc1(%rip),%xmm0        # fa4820 <vtable for Ogre::FrameListener+0x60>
  8ab85e:	00
  8ab85f:	0f 2e 42 20          	ucomiss 0x20(%rdx),%xmm0
  8ab863:	77 6b                	ja     8ab8d0 <CGenericModel::updateAnimation(float, bool)+0x1420>
  8ab865:	4d 85 ed             	test   %r13,%r13
  8ab868:	0f 84 e3 00 00 00    	je     8ab951 <CGenericModel::updateAnimation(float, bool)+0x14a1>
  8ab86e:	48 8b 54 24 10       	mov    0x10(%rsp),%rdx
  8ab873:	49 03 55 58          	add    0x58(%r13),%rdx
  8ab877:	83 c5 01             	add    $0x1,%ebp
  8ab87a:	48 8b 02             	mov    (%rdx),%rax
  8ab87d:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  8ab881:	48 29 c2             	sub    %rax,%rdx
  8ab884:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab888:	39 d5                	cmp    %edx,%ebp
  8ab88a:	0f 83 c1 00 00 00    	jae    8ab951 <CGenericModel::updateAnimation(float, bool)+0x14a1>
  8ab890:	4c 89 f2             	mov    %r14,%rdx
  8ab893:	48 29 ca             	sub    %rcx,%rdx
  8ab896:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab89a:	4c 01 e2             	add    %r12,%rdx
  8ab89d:	0f 88 5d 02 00 00    	js     8abb00 <CGenericModel::updateAnimation(float, bool)+0x1650>
  8ab8a3:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8ab8a7:	7e 97                	jle    8ab840 <CGenericModel::updateAnimation(float, bool)+0x1390>
  8ab8a9:	48 85 d2             	test   %rdx,%rdx
  8ab8ac:	0f 8e 4e 02 00 00    	jle    8abb00 <CGenericModel::updateAnimation(float, bool)+0x1650>
  8ab8b2:	48 89 d6             	mov    %rdx,%rsi
  8ab8b5:	48 c1 fe 06          	sar    $0x6,%rsi
  8ab8b9:	48 89 f7             	mov    %rsi,%rdi
  8ab8bc:	48 c1 e7 06          	shl    $0x6,%rdi
  8ab8c0:	48 29 fa             	sub    %rdi,%rdx
  8ab8c3:	48 c1 e2 03          	shl    $0x3,%rdx
  8ab8c7:	49 03 14 f7          	add    (%r15,%rsi,8),%rdx
  8ab8cb:	e9 79 ff ff ff       	jmp    8ab849 <CGenericModel::updateAnimation(float, bool)+0x1399>
  8ab8d0:	8b 74 24 2c          	mov    0x2c(%rsp),%esi
  8ab8d4:	89 ea                	mov    %ebp,%edx
  8ab8d6:	48 89 df             	mov    %rbx,%rdi
  8ab8d9:	48 89 4c 24 08       	mov    %rcx,0x8(%rsp)
  8ab8de:	e8 ad e6 fe ff       	call   899f90 <CGenericModel::getKeyFrame(unsigned int, unsigned int)>
  8ab8e3:	8b 50 58             	mov    0x58(%rax),%edx
  8ab8e6:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  8ab8eb:	83 fa 0d             	cmp    $0xd,%edx
  8ab8ee:	0f 85 24 02 00 00    	jne    8abb18 <CGenericModel::updateAnimation(float, bool)+0x1668>
  8ab8f4:	48 89 84 24 c8 00 00 	mov    %rax,0xc8(%rsp)
  8ab8fb:	00
  8ab8fc:	48 8b b3 b8 01 00 00 	mov    0x1b8(%rbx),%rsi
  8ab903:	48 3b b3 c0 01 00 00 	cmp    0x1c0(%rbx),%rsi
  8ab90a:	0f 84 72 02 00 00    	je     8abb82 <CGenericModel::updateAnimation(float, bool)+0x16d2>
  8ab910:	31 d2                	xor    %edx,%edx
  8ab912:	48 85 f6             	test   %rsi,%rsi
  8ab915:	74 26                	je     8ab93d <CGenericModel::updateAnimation(float, bool)+0x148d>
  8ab917:	48 89 06             	mov    %rax,(%rsi)
  8ab91a:	48 8b 93 b8 01 00 00 	mov    0x1b8(%rbx),%rdx
  8ab921:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8ab928:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8ab92f:	48 8b 8b 78 01 00 00 	mov    0x178(%rbx),%rcx
  8ab936:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8ab93d:	48 83 c2 08          	add    $0x8,%rdx
  8ab941:	4d 85 ed             	test   %r13,%r13
  8ab944:	48 89 93 b8 01 00 00 	mov    %rdx,0x1b8(%rbx)
  8ab94b:	0f 85 1d ff ff ff    	jne    8ab86e <CGenericModel::updateAnimation(float, bool)+0x13be>
  8ab951:	4c 89 f2             	mov    %r14,%rdx
  8ab954:	4c 89 f5             	mov    %r14,%rbp
  8ab957:	4d 89 f8             	mov    %r15,%r8
  8ab95a:	48 29 ca             	sub    %rcx,%rdx
  8ab95d:	48 c1 fa 03          	sar    $0x3,%rdx
  8ab961:	49 8d 34 14          	lea    (%r12,%rdx,1),%rsi
  8ab965:	48 85 f6             	test   %rsi,%rsi
  8ab968:	0f 88 12 04 00 00    	js     8abd80 <CGenericModel::updateAnimation(float, bool)+0x18d0>
  8ab96e:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab972:	0f 8f b8 02 00 00    	jg     8abc30 <CGenericModel::updateAnimation(float, bool)+0x1780>
  8ab978:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  8ab97d:	49 8d 04 06          	lea    (%r14,%rax,1),%rax
  8ab981:	48 83 38 00          	cmpq   $0x0,(%rax)
  8ab985:	0f 84 86 00 00 00    	je     8aba11 <CGenericModel::updateAnimation(float, bool)+0x1561>
  8ab98b:	48 85 f6             	test   %rsi,%rsi
  8ab98e:	0f 88 16 04 00 00    	js     8abdaa <CGenericModel::updateAnimation(float, bool)+0x18fa>
  8ab994:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab998:	0f 8f da 02 00 00    	jg     8abc78 <CGenericModel::updateAnimation(float, bool)+0x17c8>
  8ab99e:	4c 03 74 24 18       	add    0x18(%rsp),%r14
  8ab9a3:	49 8b 3e             	mov    (%r14),%rdi
  8ab9a6:	48 85 ff             	test   %rdi,%rdi
  8ab9a9:	74 26                	je     8ab9d1 <CGenericModel::updateAnimation(float, bool)+0x1521>
  8ab9ab:	48 8b 07             	mov    (%rdi),%rax
  8ab9ae:	ff 50 08             	call   *0x8(%rax)
  8ab9b1:	48 8b ab 70 01 00 00 	mov    0x170(%rbx),%rbp
  8ab9b8:	4c 8b 83 88 01 00 00 	mov    0x188(%rbx),%r8
  8ab9bf:	48 89 ee             	mov    %rbp,%rsi
  8ab9c2:	48 2b b3 78 01 00 00 	sub    0x178(%rbx),%rsi
  8ab9c9:	48 c1 fe 03          	sar    $0x3,%rsi
  8ab9cd:	49 8d 34 34          	lea    (%r12,%rsi,1),%rsi
  8ab9d1:	48 85 f6             	test   %rsi,%rsi
  8ab9d4:	0f 88 e2 03 00 00    	js     8abdbc <CGenericModel::updateAnimation(float, bool)+0x190c>
  8ab9da:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8ab9de:	0f 8f c4 02 00 00    	jg     8abca8 <CGenericModel::updateAnimation(float, bool)+0x17f8>
  8ab9e4:	48 03 6c 24 18       	add    0x18(%rsp),%rbp
  8ab9e9:	48 c7 45 00 00 00 00 	movq   $0x0,0x0(%rbp)
  8ab9f0:	00
  8ab9f1:	48 8b ab 70 01 00 00 	mov    0x170(%rbx),%rbp
  8ab9f8:	4c 8b 83 88 01 00 00 	mov    0x188(%rbx),%r8
  8ab9ff:	48 89 ea             	mov    %rbp,%rdx
  8aba02:	48 2b 93 78 01 00 00 	sub    0x178(%rbx),%rdx
  8aba09:	48 c1 fa 03          	sar    $0x3,%rdx
  8aba0d:	49 8d 34 14          	lea    (%r12,%rdx,1),%rsi
  8aba11:	48 85 f6             	test   %rsi,%rsi
  8aba14:	0f 88 06 03 00 00    	js     8abd20 <CGenericModel::updateAnimation(float, bool)+0x1870>
  8aba1a:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8aba1e:	0f 8f dc 01 00 00    	jg     8abc00 <CGenericModel::updateAnimation(float, bool)+0x1750>
  8aba24:	48 8b 74 24 18       	mov    0x18(%rsp),%rsi
  8aba29:	48 8d 74 35 00       	lea    0x0(%rbp,%rsi,1),%rsi
  8aba2e:	48 8b 8b 80 01 00 00 	mov    0x180(%rbx),%rcx
  8aba35:	48 8b 83 90 01 00 00 	mov    0x190(%rbx),%rax
  8aba3c:	48 2b 83 98 01 00 00 	sub    0x198(%rbx),%rax
  8aba43:	48 29 e9             	sub    %rbp,%rcx
  8aba46:	48 c1 f9 03          	sar    $0x3,%rcx
  8aba4a:	48 c1 f8 03          	sar    $0x3,%rax
  8aba4e:	48 01 c1             	add    %rax,%rcx
  8aba51:	48 8b 83 a8 01 00 00 	mov    0x1a8(%rbx),%rax
  8aba58:	4c 29 c0             	sub    %r8,%rax
  8aba5b:	48 c1 f8 03          	sar    $0x3,%rax
  8aba5f:	48 c1 e0 06          	shl    $0x6,%rax
  8aba63:	8d 44 01 bf          	lea    -0x41(%rcx,%rax,1),%eax
  8aba67:	48 98                	cltq
  8aba69:	48 01 c2             	add    %rax,%rdx
  8aba6c:	0f 88 26 03 00 00    	js     8abd98 <CGenericModel::updateAnimation(float, bool)+0x18e8>
  8aba72:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8aba76:	48 8d 44 c5 00       	lea    0x0(%rbp,%rax,8),%rax
  8aba7b:	7e 26                	jle    8abaa3 <CGenericModel::updateAnimation(float, bool)+0x15f3>
  8aba7d:	48 85 d2             	test   %rdx,%rdx
  8aba80:	0f 8e 12 03 00 00    	jle    8abd98 <CGenericModel::updateAnimation(float, bool)+0x18e8>
  8aba86:	48 89 d1             	mov    %rdx,%rcx
  8aba89:	48 c1 f9 06          	sar    $0x6,%rcx
  8aba8d:	48 89 c8             	mov    %rcx,%rax
  8aba90:	48 c1 e0 06          	shl    $0x6,%rax
  8aba94:	48 29 c2             	sub    %rax,%rdx
  8aba97:	48 8d 04 d5 00 00 00 	lea    0x0(,%rdx,8),%rax
  8aba9e:	00
  8aba9f:	49 03 04 c8          	add    (%r8,%rcx,8),%rax
  8abaa3:	48 8b 00             	mov    (%rax),%rax
  8abaa6:	48 89 06             	mov    %rax,(%rsi)
  8abaa9:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8abab0:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8abab7:	48 39 ef             	cmp    %rbp,%rdi
  8ababa:	0f 84 20 03 00 00    	je     8abde0 <CGenericModel::updateAnimation(float, bool)+0x1930>
  8abac0:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8abac7:	48 83 ef 08          	sub    $0x8,%rdi
  8abacb:	48 89 bb 90 01 00 00 	mov    %rdi,0x190(%rbx)
  8abad2:	48 89 d1             	mov    %rdx,%rcx
  8abad5:	83 6c 24 20 01       	subl   $0x1,0x20(%rsp)
  8abada:	c6 44 24 7e 01       	movb   $0x1,0x7e(%rsp)
  8abadf:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8abae6:	48 8b 83 80 01 00 00 	mov    0x180(%rbx),%rax
  8abaed:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8abaf4:	e9 b8 fa ff ff       	jmp    8ab5b1 <CGenericModel::updateAnimation(float, bool)+0x1101>
  8abaf9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  8abb00:	48 89 d6             	mov    %rdx,%rsi
  8abb03:	48 f7 d6             	not    %rsi
  8abb06:	48 c1 ee 06          	shr    $0x6,%rsi
  8abb0a:	48 f7 d6             	not    %rsi
  8abb0d:	e9 a7 fd ff ff       	jmp    8ab8b9 <CGenericModel::updateAnimation(float, bool)+0x1409>
  8abb12:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8abb18:	83 fa 0c             	cmp    $0xc,%edx
  8abb1b:	0f 84 d3 fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb21:	83 fa 17             	cmp    $0x17,%edx
  8abb24:	0f 84 ca fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb2a:	83 fa 19             	cmp    $0x19,%edx
  8abb2d:	0f 84 c1 fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb33:	83 fa 11             	cmp    $0x11,%edx
  8abb36:	0f 84 b8 fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb3c:	83 fa 13             	cmp    $0x13,%edx
  8abb3f:	90                   	nop
  8abb40:	0f 84 ae fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb46:	83 fa 14             	cmp    $0x14,%edx
  8abb49:	0f 84 a5 fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb4f:	83 fa 08             	cmp    $0x8,%edx
  8abb52:	0f 84 9c fd ff ff    	je     8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb58:	83 fa 0a             	cmp    $0xa,%edx
  8abb5b:	0f 85 04 fd ff ff    	jne    8ab865 <CGenericModel::updateAnimation(float, bool)+0x13b5>
  8abb61:	e9 8e fd ff ff       	jmp    8ab8f4 <CGenericModel::updateAnimation(float, bool)+0x1444>
  8abb66:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  8abb6d:	00 00 00
  8abb70:	4c 8b 74 24 10       	mov    0x10(%rsp),%r14
  8abb75:	48 8b 8c 24 80 00 00 	mov    0x80(%rsp),%rcx
  8abb7c:	00
  8abb7d:	e9 0e fc ff ff       	jmp    8ab790 <CGenericModel::updateAnimation(float, bool)+0x12e0>
  8abb82:	48 8b 7c 24 30       	mov    0x30(%rsp),%rdi
  8abb87:	48 8d 94 24 c8 00 00 	lea    0xc8(%rsp),%rdx
  8abb8e:	00
  8abb8f:	e8 2c 6f 00 00       	call   8b2ac0 <std::vector<CKeyframe*, std::allocator<CKeyframe*> >::_M_insert_aux(__gnu_cxx::__normal_iterator<CKeyframe**, std::vector<CKeyframe*, std::allocator<CKeyframe*> > >, CKeyframe* const&)>
  8abb94:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8abb9b:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8abba2:	48 8b 8b 78 01 00 00 	mov    0x178(%rbx),%rcx
  8abba9:	4c 8b ab e0 01 00 00 	mov    0x1e0(%rbx),%r13
  8abbb0:	e9 b0 fc ff ff       	jmp    8ab865 <CGenericModel::updateAnimation(float, bool)+0x13b5>
  8abbb5:	0f 1f 00             	nopl   (%rax)
  8abbb8:	48 85 f6             	test   %rsi,%rsi
  8abbbb:	0f 8e 77 01 00 00    	jle    8abd38 <CGenericModel::updateAnimation(float, bool)+0x1888>
  8abbc1:	48 89 f0             	mov    %rsi,%rax
  8abbc4:	48 89 f7             	mov    %rsi,%rdi
  8abbc7:	48 c1 f8 06          	sar    $0x6,%rax
  8abbcb:	83 e7 3f             	and    $0x3f,%edi
  8abbce:	49 8b 04 c7          	mov    (%r15,%rax,8),%rax
  8abbd2:	48 8b 04 f8          	mov    (%rax,%rdi,8),%rax
  8abbd6:	f3 0f 10 48 20       	movss  0x20(%rax),%xmm1
  8abbdb:	48 89 f0             	mov    %rsi,%rax
  8abbde:	48 c1 f8 06          	sar    $0x6,%rax
  8abbe2:	48 89 c7             	mov    %rax,%rdi
  8abbe5:	49 89 f1             	mov    %rsi,%r9
  8abbe8:	48 c1 e7 06          	shl    $0x6,%rdi
  8abbec:	49 29 f9             	sub    %rdi,%r9
  8abbef:	4c 89 cf             	mov    %r9,%rdi
  8abbf2:	48 c1 e7 03          	shl    $0x3,%rdi
  8abbf6:	49 03 3c c7          	add    (%r15,%rax,8),%rdi
  8abbfa:	e9 c9 fb ff ff       	jmp    8ab7c8 <CGenericModel::updateAnimation(float, bool)+0x1318>
  8abbff:	90                   	nop
  8abc00:	48 85 f6             	test   %rsi,%rsi
  8abc03:	0f 8e 17 01 00 00    	jle    8abd20 <CGenericModel::updateAnimation(float, bool)+0x1870>
  8abc09:	48 89 f0             	mov    %rsi,%rax
  8abc0c:	48 c1 f8 06          	sar    $0x6,%rax
  8abc10:	48 89 c1             	mov    %rax,%rcx
  8abc13:	48 c1 e1 06          	shl    $0x6,%rcx
  8abc17:	48 29 ce             	sub    %rcx,%rsi
  8abc1a:	48 c1 e6 03          	shl    $0x3,%rsi
  8abc1e:	49 03 34 c0          	add    (%r8,%rax,8),%rsi
  8abc22:	e9 07 fe ff ff       	jmp    8aba2e <CGenericModel::updateAnimation(float, bool)+0x157e>
  8abc27:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8abc2e:	00 00
  8abc30:	48 85 f6             	test   %rsi,%rsi
  8abc33:	0f 8e 47 01 00 00    	jle    8abd80 <CGenericModel::updateAnimation(float, bool)+0x18d0>
  8abc39:	48 89 f1             	mov    %rsi,%rcx
  8abc3c:	48 c1 f9 06          	sar    $0x6,%rcx
  8abc40:	48 89 c8             	mov    %rcx,%rax
  8abc43:	48 89 f7             	mov    %rsi,%rdi
  8abc46:	48 c1 e0 06          	shl    $0x6,%rax
  8abc4a:	48 29 c7             	sub    %rax,%rdi
  8abc4d:	48 89 f8             	mov    %rdi,%rax
  8abc50:	48 c1 e0 03          	shl    $0x3,%rax
  8abc54:	49 03 04 cf          	add    (%r15,%rcx,8),%rax
  8abc58:	e9 24 fd ff ff       	jmp    8ab981 <CGenericModel::updateAnimation(float, bool)+0x14d1>
  8abc5d:	0f 1f 00             	nopl   (%rax)
  8abc60:	48 89 f5             	mov    %rsi,%rbp
  8abc63:	48 f7 d5             	not    %rbp
  8abc66:	48 c1 ed 06          	shr    $0x6,%rbp
  8abc6a:	48 f7 d5             	not    %rbp
  8abc6d:	e9 ae f9 ff ff       	jmp    8ab620 <CGenericModel::updateAnimation(float, bool)+0x1170>
  8abc72:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8abc78:	48 85 f6             	test   %rsi,%rsi
  8abc7b:	0f 8e 29 01 00 00    	jle    8abdaa <CGenericModel::updateAnimation(float, bool)+0x18fa>
  8abc81:	48 89 f0             	mov    %rsi,%rax
  8abc84:	48 c1 f8 06          	sar    $0x6,%rax
  8abc88:	49 89 c6             	mov    %rax,%r14
  8abc8b:	49 89 f1             	mov    %rsi,%r9
  8abc8e:	49 c1 e6 06          	shl    $0x6,%r14
  8abc92:	4d 29 f1             	sub    %r14,%r9
  8abc95:	4d 89 ce             	mov    %r9,%r14
  8abc98:	49 c1 e6 03          	shl    $0x3,%r14
  8abc9c:	4d 03 34 c7          	add    (%r15,%rax,8),%r14
  8abca0:	e9 fe fc ff ff       	jmp    8ab9a3 <CGenericModel::updateAnimation(float, bool)+0x14f3>
  8abca5:	0f 1f 00             	nopl   (%rax)
  8abca8:	48 85 f6             	test   %rsi,%rsi
  8abcab:	0f 8e 0b 01 00 00    	jle    8abdbc <CGenericModel::updateAnimation(float, bool)+0x190c>
  8abcb1:	48 89 f0             	mov    %rsi,%rax
  8abcb4:	48 c1 f8 06          	sar    $0x6,%rax
  8abcb8:	48 89 c5             	mov    %rax,%rbp
  8abcbb:	48 c1 e5 06          	shl    $0x6,%rbp
  8abcbf:	48 29 ee             	sub    %rbp,%rsi
  8abcc2:	48 8d 2c f5 00 00 00 	lea    0x0(,%rsi,8),%rbp
  8abcc9:	00
  8abcca:	49 03 2c c0          	add    (%r8,%rax,8),%rbp
  8abcce:	e9 16 fd ff ff       	jmp    8ab9e9 <CGenericModel::updateAnimation(float, bool)+0x1539>
  8abcd3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  8abcd8:	89 c0                	mov    %eax,%eax
  8abcda:	48 c1 e0 03          	shl    $0x3,%rax
  8abcde:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8abce5:	e9 87 fa ff ff       	jmp    8ab771 <CGenericModel::updateAnimation(float, bool)+0x12c1>
  8abcea:	48 85 f6             	test   %rsi,%rsi
  8abced:	0f 8e db 00 00 00    	jle    8abdce <CGenericModel::updateAnimation(float, bool)+0x191e>
  8abcf3:	48 89 f7             	mov    %rsi,%rdi
  8abcf6:	48 c1 ff 06          	sar    $0x6,%rdi
  8abcfa:	48 89 f8             	mov    %rdi,%rax
  8abcfd:	49 89 f1             	mov    %rsi,%r9
  8abd00:	48 c1 e0 06          	shl    $0x6,%rax
  8abd04:	49 29 c1             	sub    %rax,%r9
  8abd07:	4c 89 c8             	mov    %r9,%rax
  8abd0a:	48 c1 e0 03          	shl    $0x3,%rax
  8abd0e:	49 03 04 ff          	add    (%r15,%rdi,8),%rax
  8abd12:	e9 de fa ff ff       	jmp    8ab7f5 <CGenericModel::updateAnimation(float, bool)+0x1345>
  8abd17:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  8abd1e:	00 00
  8abd20:	48 89 f0             	mov    %rsi,%rax
  8abd23:	48 f7 d0             	not    %rax
  8abd26:	48 c1 e8 06          	shr    $0x6,%rax
  8abd2a:	48 f7 d0             	not    %rax
  8abd2d:	e9 de fe ff ff       	jmp    8abc10 <CGenericModel::updateAnimation(float, bool)+0x1760>
  8abd32:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8abd38:	48 89 f0             	mov    %rsi,%rax
  8abd3b:	48 89 f7             	mov    %rsi,%rdi
  8abd3e:	48 f7 d0             	not    %rax
  8abd41:	48 c1 e8 06          	shr    $0x6,%rax
  8abd45:	48 f7 d0             	not    %rax
  8abd48:	49 89 c1             	mov    %rax,%r9
  8abd4b:	49 c1 e1 06          	shl    $0x6,%r9
  8abd4f:	4c 29 cf             	sub    %r9,%rdi
  8abd52:	48 85 f6             	test   %rsi,%rsi
  8abd55:	49 89 f9             	mov    %rdi,%r9
  8abd58:	49 8b 3c c7          	mov    (%r15,%rax,8),%rdi
  8abd5c:	4a 8b 3c cf          	mov    (%rdi,%r9,8),%rdi
  8abd60:	f3 0f 10 4f 20       	movss  0x20(%rdi),%xmm1
  8abd65:	0f 88 77 fe ff ff    	js     8abbe2 <CGenericModel::updateAnimation(float, bool)+0x1732>
  8abd6b:	48 83 fe 3f          	cmp    $0x3f,%rsi
  8abd6f:	0f 8e 4a fa ff ff    	jle    8ab7bf <CGenericModel::updateAnimation(float, bool)+0x130f>
  8abd75:	e9 61 fe ff ff       	jmp    8abbdb <CGenericModel::updateAnimation(float, bool)+0x172b>
  8abd7a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8abd80:	48 89 f1             	mov    %rsi,%rcx
  8abd83:	48 f7 d1             	not    %rcx
  8abd86:	48 c1 e9 06          	shr    $0x6,%rcx
  8abd8a:	48 f7 d1             	not    %rcx
  8abd8d:	e9 ae fe ff ff       	jmp    8abc40 <CGenericModel::updateAnimation(float, bool)+0x1790>
  8abd92:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  8abd98:	48 89 d1             	mov    %rdx,%rcx
  8abd9b:	48 f7 d1             	not    %rcx
  8abd9e:	48 c1 e9 06          	shr    $0x6,%rcx
  8abda2:	48 f7 d1             	not    %rcx
  8abda5:	e9 e3 fc ff ff       	jmp    8aba8d <CGenericModel::updateAnimation(float, bool)+0x15dd>
  8abdaa:	48 89 f0             	mov    %rsi,%rax
  8abdad:	48 f7 d0             	not    %rax
  8abdb0:	48 c1 e8 06          	shr    $0x6,%rax
  8abdb4:	48 f7 d0             	not    %rax
  8abdb7:	e9 cc fe ff ff       	jmp    8abc88 <CGenericModel::updateAnimation(float, bool)+0x17d8>
  8abdbc:	48 89 f0             	mov    %rsi,%rax
  8abdbf:	48 f7 d0             	not    %rax
  8abdc2:	48 c1 e8 06          	shr    $0x6,%rax
  8abdc6:	48 f7 d0             	not    %rax
  8abdc9:	e9 ea fe ff ff       	jmp    8abcb8 <CGenericModel::updateAnimation(float, bool)+0x1808>
  8abdce:	48 89 f7             	mov    %rsi,%rdi
  8abdd1:	48 f7 d7             	not    %rdi
  8abdd4:	48 c1 ef 06          	shr    $0x6,%rdi
  8abdd8:	48 f7 d7             	not    %rdi
  8abddb:	e9 1a ff ff ff       	jmp    8abcfa <CGenericModel::updateAnimation(float, bool)+0x184a>
  8abde0:	48 89 ef             	mov    %rbp,%rdi
  8abde3:	e8 30 81 ca ff       	call   553f18 <operator delete(void*)@plt>
  8abde8:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8abdef:	48 8d 4a f8          	lea    -0x8(%rdx),%rcx
  8abdf3:	48 89 8b a8 01 00 00 	mov    %rcx,0x1a8(%rbx)
  8abdfa:	48 8b 29             	mov    (%rcx),%rbp
  8abdfd:	48 89 ca             	mov    %rcx,%rdx
  8abe00:	48 8d 85 00 02 00 00 	lea    0x200(%rbp),%rax
  8abe07:	48 8d bd f8 01 00 00 	lea    0x1f8(%rbp),%rdi
  8abe0e:	48 89 ab 98 01 00 00 	mov    %rbp,0x198(%rbx)
  8abe15:	48 89 83 a0 01 00 00 	mov    %rax,0x1a0(%rbx)
  8abe1c:	48 89 bb 90 01 00 00 	mov    %rdi,0x190(%rbx)
  8abe23:	e9 ad fc ff ff       	jmp    8abad5 <CGenericModel::updateAnimation(float, bool)+0x1625>
  8abe28:	0f 8a 27 f7 ff ff    	jp     8ab555 <CGenericModel::updateAnimation(float, bool)+0x10a5>
  8abe2e:	48 29 ef             	sub    %rbp,%rdi
  8abe31:	4c 29 f0             	sub    %r14,%rax
  8abe34:	4c 29 fa             	sub    %r15,%rdx
  8abe37:	48 c1 fa 03          	sar    $0x3,%rdx
  8abe3b:	48 c1 f8 03          	sar    $0x3,%rax
  8abe3f:	48 c1 ff 03          	sar    $0x3,%rdi
  8abe43:	48 c1 e2 06          	shl    $0x6,%rdx
  8abe47:	48 01 f8             	add    %rdi,%rax
  8abe4a:	8d 4c 02 c0          	lea    -0x40(%rdx,%rax,1),%ecx
  8abe4e:	80 7c 24 7e 00       	cmpb   $0x0,0x7e(%rsp)
  8abe53:	0f 84 71 01 00 00    	je     8abfca <CGenericModel::updateAnimation(float, bool)+0x1b1a>
  8abe59:	48 8b 7b 60          	mov    0x60(%rbx),%rdi
  8abe5d:	e8 96 78 ca ff       	call   5536f8 <Ogre::Entity::_updateAnimation()@plt>
  8abe62:	48 8b bc 24 90 00 00 	mov    0x90(%rsp),%rdi
  8abe69:	00
  8abe6a:	48 85 ff             	test   %rdi,%rdi
  8abe6d:	74 05                	je     8abe74 <CGenericModel::updateAnimation(float, bool)+0x19c4>
  8abe6f:	e8 a4 80 ca ff       	call   553f18 <operator delete(void*)@plt>
  8abe74:	48 8b bc 24 b0 00 00 	mov    0xb0(%rsp),%rdi
  8abe7b:	00
  8abe7c:	48 85 ff             	test   %rdi,%rdi
  8abe7f:	0f 84 7a e6 ff ff    	je     8aa4ff <CGenericModel::updateAnimation(float, bool)+0x4f>
  8abe85:	e8 8e 80 ca ff       	call   553f18 <operator delete(void*)@plt>
  8abe8a:	e9 70 e6 ff ff       	jmp    8aa4ff <CGenericModel::updateAnimation(float, bool)+0x4f>
  8abe8f:	48 89 d1             	mov    %rdx,%rcx
  8abe92:	48 f7 d1             	not    %rcx
  8abe95:	48 c1 e9 06          	shr    $0x6,%rcx
  8abe99:	48 f7 d1             	not    %rcx
  8abe9c:	e9 67 f5 ff ff       	jmp    8ab408 <CGenericModel::updateAnimation(float, bool)+0xf58>
  8abea1:	48 89 cd             	mov    %rcx,%rbp
  8abea4:	48 f7 d5             	not    %rbp
  8abea7:	48 c1 ed 06          	shr    $0x6,%rbp
  8abeab:	48 f7 d5             	not    %rbp
  8abeae:	e9 3a ef ff ff       	jmp    8aaded <CGenericModel::updateAnimation(float, bool)+0x93d>
  8abeb3:	8b 44 24 2c          	mov    0x2c(%rsp),%eax
  8abeb7:	48 c1 e0 03          	shl    $0x3,%rax
  8abebb:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8abec2:	e9 5e e9 ff ff       	jmp    8aa825 <CGenericModel::updateAnimation(float, bool)+0x375>
  8abec7:	8b 44 24 2c          	mov    0x2c(%rsp),%eax
  8abecb:	48 c1 e0 03          	shl    $0x3,%rax
  8abecf:	48 03 83 48 01 00 00 	add    0x148(%rbx),%rax
  8abed6:	e9 c3 e8 ff ff       	jmp    8aa79e <CGenericModel::updateAnimation(float, bool)+0x2ee>
  8abedb:	48 8b bc 24 88 00 00 	mov    0x88(%rsp),%rdi
  8abee2:	00
  8abee3:	48 89 ee             	mov    %rbp,%rsi
  8abee6:	e8 b5 51 00 00       	call   8b10a0 <std::_Deque_iterator<CActiveAnimation*, CActiveAnimation*&, CActiveAnimation**>::operator[](long) const>
  8abeeb:	48 8b 00             	mov    (%rax),%rax
  8abeee:	0f 57 c0             	xorps  %xmm0,%xmm0
  8abef1:	80 78 27 00          	cmpb   $0x0,0x27(%rax)
  8abef5:	75 0a                	jne    8abf01 <CGenericModel::updateAnimation(float, bool)+0x1a51>
  8abef7:	f3 0f 10 40 18       	movss  0x18(%rax),%xmm0
  8abefc:	f3 0f 5c 40 20       	subss  0x20(%rax),%xmm0
  8abf01:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8abf08:	48 89 ea             	mov    %rbp,%rdx
  8abf0b:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8abf12:	4c 89 f6             	mov    %r14,%rsi
  8abf15:	48 2b b3 78 01 00 00 	sub    0x178(%rbx),%rsi
  8abf1c:	48 c1 fe 03          	sar    $0x3,%rsi
  8abf20:	48 01 f2             	add    %rsi,%rdx
  8abf23:	0f 88 b6 01 00 00    	js     8ac0df <CGenericModel::updateAnimation(float, bool)+0x1c2f>
  8abf29:	48 83 fa 3f          	cmp    $0x3f,%rdx
  8abf2d:	49 8d 0c ee          	lea    (%r14,%rbp,8),%rcx
  8abf31:	7e 25                	jle    8abf58 <CGenericModel::updateAnimation(float, bool)+0x1aa8>
  8abf33:	48 85 d2             	test   %rdx,%rdx
  8abf36:	0f 8e a3 01 00 00    	jle    8ac0df <CGenericModel::updateAnimation(float, bool)+0x1c2f>
  8abf3c:	48 89 d0             	mov    %rdx,%rax
  8abf3f:	48 c1 f8 06          	sar    $0x6,%rax
  8abf43:	48 89 c1             	mov    %rax,%rcx
  8abf46:	48 c1 e1 06          	shl    $0x6,%rcx
  8abf4a:	48 29 ca             	sub    %rcx,%rdx
  8abf4d:	48 89 d1             	mov    %rdx,%rcx
  8abf50:	48 c1 e1 03          	shl    $0x3,%rcx
  8abf54:	49 03 0c c7          	add    (%r15,%rax,8),%rcx
  8abf58:	48 8b 01             	mov    (%rcx),%rax
  8abf5b:	f3 0f 10 48 38       	movss  0x38(%rax),%xmm1
  8abf60:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
  8abf65:	48 01 f0             	add    %rsi,%rax
  8abf68:	0f 88 5f 01 00 00    	js     8ac0cd <CGenericModel::updateAnimation(float, bool)+0x1c1d>
  8abf6e:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8abf73:	48 83 f8 3f          	cmp    $0x3f,%rax
  8abf77:	4b 8d 0c c6          	lea    (%r14,%r8,8),%rcx
  8abf7b:	7e 28                	jle    8abfa5 <CGenericModel::updateAnimation(float, bool)+0x1af5>
  8abf7d:	48 85 c0             	test   %rax,%rax
  8abf80:	0f 8e 47 01 00 00    	jle    8ac0cd <CGenericModel::updateAnimation(float, bool)+0x1c1d>
  8abf86:	48 89 c2             	mov    %rax,%rdx
  8abf89:	48 c1 fa 06          	sar    $0x6,%rdx
  8abf8d:	48 89 d1             	mov    %rdx,%rcx
  8abf90:	49 89 c1             	mov    %rax,%r9
  8abf93:	48 c1 e1 06          	shl    $0x6,%rcx
  8abf97:	49 29 c9             	sub    %rcx,%r9
  8abf9a:	4c 89 c9             	mov    %r9,%rcx
  8abf9d:	48 c1 e1 03          	shl    $0x3,%rcx
  8abfa1:	49 03 0c d7          	add    (%r15,%rdx,8),%rcx
  8abfa5:	f3 0f 5e c1          	divss  %xmm1,%xmm0
  8abfa9:	48 8b 11             	mov    (%rcx),%rdx
  8abfac:	f3 0f 10 4a 30       	movss  0x30(%rdx),%xmm1
  8abfb1:	ba 01 00 00 00       	mov    $0x1,%edx
  8abfb6:	f3 0f 5c 44 24 38    	subss  0x38(%rsp),%xmm0
  8abfbc:	0f 2e c8             	ucomiss %xmm0,%xmm1
  8abfbf:	0f 82 78 e8 ff ff    	jb     8aa83d <CGenericModel::updateAnimation(float, bool)+0x38d>
  8abfc5:	e9 6e e7 ff ff       	jmp    8aa738 <CGenericModel::updateAnimation(float, bool)+0x288>
  8abfca:	80 7c 24 7f 00       	cmpb   $0x0,0x7f(%rsp)
  8abfcf:	0f 85 84 fe ff ff    	jne    8abe59 <CGenericModel::updateAnimation(float, bool)+0x19a9>
  8abfd5:	85 c9                	test   %ecx,%ecx
  8abfd7:	0f 8e 85 fe ff ff    	jle    8abe62 <CGenericModel::updateAnimation(float, bool)+0x19b2>
  8abfdd:	83 f9 01             	cmp    $0x1,%ecx
  8abfe0:	0f 85 73 fe ff ff    	jne    8abe59 <CGenericModel::updateAnimation(float, bool)+0x19a9>
  8abfe6:	48 8d bb 70 01 00 00 	lea    0x170(%rbx),%rdi
  8abfed:	31 f6                	xor    %esi,%esi
  8abfef:	e8 ac 50 00 00       	call   8b10a0 <std::_Deque_iterator<CActiveAnimation*, CActiveAnimation*&, CActiveAnimation**>::operator[](long) const>
  8abff4:	48 8b 00             	mov    (%rax),%rax
  8abff7:	80 78 28 00          	cmpb   $0x0,0x28(%rax)
  8abffb:	0f 85 61 fe ff ff    	jne    8abe62 <CGenericModel::updateAnimation(float, bool)+0x19b2>
  8ac001:	e9 53 fe ff ff       	jmp    8abe59 <CGenericModel::updateAnimation(float, bool)+0x19a9>
  8ac006:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  8ac00d:	00 00 00
  8ac010:	48 8b 8c 24 90 00 00 	mov    0x90(%rsp),%rcx
  8ac017:	00
  8ac018:	48 8b b4 24 98 00 00 	mov    0x98(%rsp),%rsi
  8ac01f:	00
  8ac020:	0f 57 c0             	xorps  %xmm0,%xmm0
  8ac023:	f3 0f 10 54 24 3c    	movss  0x3c(%rsp),%xmm2
  8ac029:	48 29 ce             	sub    %rcx,%rsi
  8ac02c:	48 c1 fe 02          	sar    $0x2,%rsi
  8ac030:	0f 2e d0             	ucomiss %xmm0,%xmm2
  8ac033:	74 5f                	je     8ac094 <CGenericModel::updateAnimation(float, bool)+0x1be4>
  8ac035:	f3 0f 10 05 bf 87 6f 	movss  0x6f87bf(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8ac03c:	00
  8ac03d:	f3 0f 5c 44 24 3c    	subss  0x3c(%rsp),%xmm0
  8ac043:	f3 0f 11 44 24 10    	movss  %xmm0,0x10(%rsp)
  8ac049:	e9 84 ec ff ff       	jmp    8aacd2 <CGenericModel::updateAnimation(float, bool)+0x822>
  8ac04e:	48 8d 94 24 e8 00 00 	lea    0xe8(%rsp),%rdx
  8ac055:	00
  8ac056:	48 8d bc 24 90 00 00 	lea    0x90(%rsp),%rdi
  8ac05d:	00
  8ac05e:	e8 2d f7 fa ff       	call   85b790 <std::vector<int, std::allocator<int> >::_M_insert_aux(__gnu_cxx::__normal_iterator<int*, std::vector<int, std::allocator<int> > >, int const&)>
  8ac063:	e9 85 ee ff ff       	jmp    8aaeed <CGenericModel::updateAnimation(float, bool)+0xa3d>
  8ac068:	48 8d 94 24 ec 00 00 	lea    0xec(%rsp),%rdx
  8ac06f:	00
  8ac070:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  8ac077:	00
  8ac078:	e8 03 68 00 00       	call   8b2880 <std::vector<float, std::allocator<float> >::_M_insert_aux(__gnu_cxx::__normal_iterator<float*, std::vector<float, std::allocator<float> > >, float const&)>
  8ac07d:	e9 4f e9 ff ff       	jmp    8aa9d1 <CGenericModel::updateAnimation(float, bool)+0x521>
  8ac082:	48 89 c1             	mov    %rax,%rcx
  8ac085:	48 f7 d1             	not    %rcx
  8ac088:	48 c1 e9 06          	shr    $0x6,%rcx
  8ac08c:	48 f7 d1             	not    %rcx
  8ac08f:	e9 72 e6 ff ff       	jmp    8aa706 <CGenericModel::updateAnimation(float, bool)+0x256>
  8ac094:	7a 9f                	jp     8ac035 <CGenericModel::updateAnimation(float, bool)+0x1b85>
  8ac096:	f3 0f 10 0d 86 87 6f 	movss  0x6f8786(%rip),%xmm1        # fa4824 <vtable for Ogre::FrameListener+0x64>
  8ac09d:	00
  8ac09e:	f3 0f 11 4c 24 10    	movss  %xmm1,0x10(%rsp)
  8ac0a4:	e9 29 ec ff ff       	jmp    8aacd2 <CGenericModel::updateAnimation(float, bool)+0x822>
  8ac0a9:	48 89 c2             	mov    %rax,%rdx
  8ac0ac:	48 f7 d2             	not    %rdx
  8ac0af:	48 c1 ea 06          	shr    $0x6,%rdx
  8ac0b3:	48 f7 d2             	not    %rdx
  8ac0b6:	e9 a5 e6 ff ff       	jmp    8aa760 <CGenericModel::updateAnimation(float, bool)+0x2b0>
  8ac0bb:	48 89 c2             	mov    %rax,%rdx
  8ac0be:	48 f7 d2             	not    %rdx
  8ac0c1:	48 c1 ea 06          	shr    $0x6,%rdx
  8ac0c5:	48 f7 d2             	not    %rdx
  8ac0c8:	e9 24 e7 ff ff       	jmp    8aa7f1 <CGenericModel::updateAnimation(float, bool)+0x341>
  8ac0cd:	48 89 c2             	mov    %rax,%rdx
  8ac0d0:	48 f7 d2             	not    %rdx
  8ac0d3:	48 c1 ea 06          	shr    $0x6,%rdx
  8ac0d7:	48 f7 d2             	not    %rdx
  8ac0da:	e9 ae fe ff ff       	jmp    8abf8d <CGenericModel::updateAnimation(float, bool)+0x1add>
  8ac0df:	48 89 d0             	mov    %rdx,%rax
  8ac0e2:	48 f7 d0             	not    %rax
  8ac0e5:	48 c1 e8 06          	shr    $0x6,%rax
  8ac0e9:	48 f7 d0             	not    %rax
  8ac0ec:	e9 52 fe ff ff       	jmp    8abf43 <CGenericModel::updateAnimation(float, bool)+0x1a93>
  8ac0f1:	c6 44 24 7e 00       	movb   $0x0,0x7e(%rsp)
  8ac0f6:	e9 47 f4 ff ff       	jmp    8ab542 <CGenericModel::updateAnimation(float, bool)+0x1092>
  8ac0fb:	48 8d bb 70 01 00 00 	lea    0x170(%rbx),%rdi
  8ac102:	31 f6                	xor    %esi,%esi
  8ac104:	e8 97 4f 00 00       	call   8b10a0 <std::_Deque_iterator<CActiveAnimation*, CActiveAnimation*&, CActiveAnimation**>::operator[](long) const>
  8ac109:	48 8b 00             	mov    (%rax),%rax
  8ac10c:	80 78 28 00          	cmpb   $0x0,0x28(%rax)
  8ac110:	0f 85 db e3 ff ff    	jne    8aa4f1 <CGenericModel::updateAnimation(float, bool)+0x41>
  8ac116:	4c 8b b3 70 01 00 00 	mov    0x170(%rbx),%r14
  8ac11d:	48 8b 83 80 01 00 00 	mov    0x180(%rbx),%rax
  8ac124:	48 8b ab 98 01 00 00 	mov    0x198(%rbx),%rbp
  8ac12b:	48 8b bb 90 01 00 00 	mov    0x190(%rbx),%rdi
  8ac132:	4c 8b bb 88 01 00 00 	mov    0x188(%rbx),%r15
  8ac139:	48 8b 93 a8 01 00 00 	mov    0x1a8(%rbx),%rdx
  8ac140:	e9 56 e4 ff ff       	jmp    8aa59b <CGenericModel::updateAnimation(float, bool)+0xeb>
  8ac145:	48 83 f8 3f          	cmp    $0x3f,%rax
  8ac149:	0f 8f 8a ef ff ff    	jg     8ab0d9 <CGenericModel::updateAnimation(float, bool)+0xc29>
  8ac14f:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  8ac154:	4b 8b 04 c6          	mov    (%r14,%r8,8),%rax
  8ac158:	e9 4a e7 ff ff       	jmp    8aa8a7 <CGenericModel::updateAnimation(float, bool)+0x3f7>
  8ac15d:	48 8b bc 24 90 00 00 	mov    0x90(%rsp),%rdi
  8ac164:	00
  8ac165:	48 89 c3             	mov    %rax,%rbx
  8ac168:	48 85 ff             	test   %rdi,%rdi
  8ac16b:	74 05                	je     8ac172 <CGenericModel::updateAnimation(float, bool)+0x1cc2>
  8ac16d:	e8 a6 7d ca ff       	call   553f18 <operator delete(void*)@plt>
  8ac172:	48 8b bc 24 b0 00 00 	mov    0xb0(%rsp),%rdi
  8ac179:	00
  8ac17a:	48 85 ff             	test   %rdi,%rdi
  8ac17d:	74 05                	je     8ac184 <CGenericModel::updateAnimation(float, bool)+0x1cd4>
  8ac17f:	e8 94 7d ca ff       	call   553f18 <operator delete(void*)@plt>
  8ac184:	48 89 df             	mov    %rbx,%rdi
  8ac187:	e8 0c 83 ca ff       	call   554498 <_Unwind_Resume@plt>
