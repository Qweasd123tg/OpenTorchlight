
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b53430 <_ZN14CInventoryMenu12updateLayoutEv>:
  b53430:	push   %r15
  b53432:	push   %r14
  b53434:	mov    %rdi,%r14
  b53437:	push   %r13
  b53439:	push   %r12
  b5343b:	push   %rbp
  b5343c:	push   %rbx
  b5343d:	sub    $0x22f8,%rsp
  b53444:	cmpb   $0x0,0x60(%rdi)
  b53448:	je     b53464 <_ZN14CInventoryMenu12updateLayoutEv+0x34>
  b5344a:	mov    0x50(%rdi),%rax
  b5344e:	test   %rax,%rax
  b53451:	je     b53464 <_ZN14CInventoryMenu12updateLayoutEv+0x34>
  b53453:	mov    0x490(%rax),%rax
  b5345a:	test   %rax,%rax
  b5345d:	mov    %rax,0x58(%rsp)
  b53462:	jne    b53488 <_ZN14CInventoryMenu12updateLayoutEv+0x58>
  b53464:	add    $0x22f8,%rsp
  b5346b:	pop    %rbx
  b5346c:	pop    %rbp
  b5346d:	pop    %r12
  b5346f:	pop    %r13
  b53471:	pop    %r14
  b53473:	pop    %r15
  b53475:	ret
  b53476:	cs nopw 0x0(%rax,%rax,1)
  b53480:	mov    (%rdx),%rsi
  b53483:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b53488:	mov    0x30(%r14),%rdi
  b5348c:	mov    0x78(%rdi),%rdx
  b53490:	mov    0x80(%rdi),%rax
  b53497:	sub    %rdx,%rax
  b5349a:	sar    $0x3,%rax
  b5349e:	test   %rax,%rax
  b534a1:	jne    b53480 <_ZN14CInventoryMenu12updateLayoutEv+0x50>
  b534a3:	xor    %ebx,%ebx
  b534a5:	jmp    b534ba <_ZN14CInventoryMenu12updateLayoutEv+0x8a>
  b534a7:	nopw   0x0(%rax,%rax,1)
  b534b0:	add    $0x8,%rbx
  b534b4:	cmp    $0x60,%rbx
  b534b8:	je     b534f0 <_ZN14CInventoryMenu12updateLayoutEv+0xc0>
  b534ba:	mov    0x1028(%r14,%rbx,1),%rdi
  b534c2:	test   %rdi,%rdi
  b534c5:	je     b534b0 <_ZN14CInventoryMenu12updateLayoutEv+0x80>
  b534c7:	mov    0x78(%rdi),%rdx
  b534cb:	mov    0x80(%rdi),%rax
  b534d2:	sub    %rdx,%rax
  b534d5:	sar    $0x3,%rax
  b534d9:	test   %rax,%rax
  b534dc:	je     b534b0 <_ZN14CInventoryMenu12updateLayoutEv+0x80>
  b534de:	mov    (%rdx),%rsi
  b534e1:	add    $0x8,%rbx
  b534e5:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b534ea:	cmp    $0x60,%rbx
  b534ee:	jne    b534ba <_ZN14CInventoryMenu12updateLayoutEv+0x8a>
  b534f0:	lea    0xa30(%rsp),%rax
  b534f8:	lea    0xb90(%rsp),%rdx
  b53500:	mov    %r14,0x60(%rsp)
  b53505:	mov    %r14,%rbp
  b53508:	movl   $0x0,0x40(%rsp)
  b53510:	add    $0x3c,%rax
  b53514:	add    $0x3c,%rdx
  b53518:	mov    %rax,0x68(%rsp)
  b5351d:	lea    0xae0(%rsp),%rax
  b53525:	mov    %rdx,0x70(%rsp)
  b5352a:	lea    0xcf0(%rsp),%rdx
  b53532:	add    $0x28,%rax
  b53536:	mov    %rax,0x78(%rsp)
  b5353b:	lea    0xc40(%rsp),%rax
  b53543:	add    $0x3c,%rdx
  b53547:	mov    %rdx,0x80(%rsp)
  b5354f:	add    $0x28,%rax
  b53553:	mov    %rax,0x88(%rsp)
  b5355b:	nopl   0x0(%rax,%rax,1)
  b53560:	cmpq   $0x0,0x1028(%rbp)
  b53568:	je     b54212 <_ZN14CInventoryMenu12updateLayoutEv+0xde2>
  b5356e:	mov    0x40(%rsp),%esi
  b53572:	mov    0x58(%rsp),%rdi
  b53577:	call   91b3a0 <_ZN10CInventory21getEquipmentRefInSlotEj>
  b5357c:	test   %rax,%rax
  b5357f:	je     b54de9 <_ZN14CInventoryMenu12updateLayoutEv+0x19b9>
  b53585:	mov    0x10(%rax),%r13
  b53589:	mov    0x2c8(%r13),%rdx
  b53590:	test   %rdx,%rdx
  b53593:	mov    %rdx,0x38(%rsp)
  b53598:	je     b55b89 <_ZN14CInventoryMenu12updateLayoutEv+0x2759>
  b5359e:	mov    0x38(%rsp),%rax
  b535a3:	mov    0xb0(%rax),%rdi
  b535aa:	test   %rdi,%rdi
  b535ad:	je     b535b7 <_ZN14CInventoryMenu12updateLayoutEv+0x187>
  b535af:	mov    %rax,%rsi
  b535b2:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b535b7:	mov    0x1028(%rbp),%rdi
  b535be:	mov    0x38(%rsp),%rsi
  b535c3:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b535c8:	mov    0x1028(%rbp),%rdi
  b535cf:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b535d4:	xorps  %xmm3,%xmm3
  b535d7:	xorps  %xmm0,%xmm0
  b535da:	movss  0x45122e(%rip),%xmm2        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b535e2:	movaps %xmm2,%xmm4
  b535e5:	mulss  (%rax),%xmm3
  b535e9:	movss  0x455103(%rip),%xmm1        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b535f1:	cmpltss %xmm3,%xmm0
  b535f6:	andps  %xmm0,%xmm4
  b535f9:	andnps %xmm1,%xmm0
  b535fc:	orps   %xmm4,%xmm0
  b535ff:	addss  %xmm3,%xmm0
  b53603:	cvttss2si %xmm0,%edx
  b53607:	cvtsi2ss %edx,%xmm0
  b5360b:	addss  0x4(%rax),%xmm0
  b53610:	movss  %xmm0,0x30(%rsp)
  b53616:	mov    0x1028(%rbp),%rdi
  b5361d:	movss  %xmm1,(%rsp)
  b53622:	movss  %xmm2,0x10(%rsp)
  b53628:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5362d:	xorps  %xmm3,%xmm3
  b53630:	xorps  %xmm0,%xmm0
  b53633:	movss  0x10(%rsp),%xmm2
  b53639:	movss  (%rsp),%xmm1
  b5363e:	mulss  0x8(%rax),%xmm3
  b53643:	cmpltss %xmm3,%xmm0
  b53648:	movss  %xmm3,0x48(%rsp)
  b5364e:	andps  %xmm0,%xmm2
  b53651:	andnps %xmm1,%xmm0
  b53654:	orps   %xmm2,%xmm0
  b53657:	movss  %xmm0,0x28(%rsp)
  b5365d:	movss  0xc(%rax),%xmm0
  b53662:	movss  %xmm0,0x54(%rsp)
  b53668:	cmpb   $0x0,0x348(%r13)
  b53670:	je     b53682 <_ZN14CInventoryMenu12updateLayoutEv+0x252>
  b53672:	mov    0x3e0(%r13),%r10d
  b53679:	test   %r10d,%r10d
  b5367c:	jne    b55411 <_ZN14CInventoryMenu12updateLayoutEv+0x1fe1>
  b53682:	lea    0x1c10(%rsp),%rbx
  b5368a:	xor    %esi,%esi
  b5368c:	movq   $0x20,0x1c18(%rsp)
  b53698:	movq   $0x0,0x1c20(%rsp)
  b536a4:	movq   $0x0,0x1c30(%rsp)
  b536b0:	mov    %rbx,%rdi
  b536b3:	movq   $0x0,0x1c28(%rsp)
  b536bf:	movq   $0x0,0x1cb8(%rsp)
  b536cb:	movq   $0x0,0x1c10(%rsp)
  b536d7:	movl   $0x0,0x1c38(%rsp)
  b536e2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b536e7:	cmpq   $0x20,0x1c18(%rsp)
  b536f0:	movq   $0x0,0x1c10(%rsp)
  b536fc:	lea    0x28(%rbx),%rax
  b53700:	ja     b558e0 <_ZN14CInventoryMenu12updateLayoutEv+0x24b0>
  b53706:	lea    0x1cc0(%rsp),%r12
  b5370e:	movl   $0x0,(%rax)
  b53714:	mov    $0x5,%esi
  b53719:	movq   $0x20,0x1cc8(%rsp)
  b53725:	movq   $0x0,0x1cd0(%rsp)
  b53731:	mov    %r12,%rdi
  b53734:	movq   $0x0,0x1ce0(%rsp)
  b53740:	movq   $0x0,0x1cd8(%rsp)
  b5374c:	movq   $0x0,0x1d68(%rsp)
  b53758:	movq   $0x0,0x1cc0(%rsp)
  b53764:	movl   $0x0,0x1ce8(%rsp)
  b5376f:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53774:	cmpq   $0x20,0x1cc8(%rsp)
  b5377d:	lea    0x28(%r12),%rdx
  b53782:	jbe    b5378c <_ZN14CInventoryMenu12updateLayoutEv+0x35c>
  b53784:	mov    0x1d68(%rsp),%rdx
  b5378c:	mov    $0xfd0c0d,%eax
  b53791:	nopl   0x0(%rax)
  b53798:	movzbl (%rax),%ecx
  b5379b:	add    $0x1,%rax
  b5379f:	mov    %ecx,(%rdx)
  b537a1:	add    $0x4,%rdx
  b537a5:	cmp    $0xfd0c12,%rax
  b537ab:	jne    b53798 <_ZN14CInventoryMenu12updateLayoutEv+0x368>
  b537ad:	cmpq   $0x20,0x1cc8(%rsp)
  b537b6:	movq   $0x5,0x1cc0(%rsp)
  b537c2:	lea    0x3c(%r12),%rax
  b537c7:	jbe    b537d5 <_ZN14CInventoryMenu12updateLayoutEv+0x3a5>
  b537c9:	mov    0x1d68(%rsp),%rax
  b537d1:	add    $0x14,%rax
  b537d5:	movl   $0x0,(%rax)
  b537db:	mov    0x1548(%rbp),%rdi
  b537e2:	mov    %rbx,%rdx
  b537e5:	mov    %r12,%rsi
  b537e8:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b537ed:	mov    %r12,%rdi
  b537f0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b537f5:	mov    %rbx,%rdi
  b537f8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b537fd:	cmpb   $0x0,0x348(%r13)
  b53805:	jne    b54a78 <_ZN14CInventoryMenu12updateLayoutEv+0x1648>
  b5380b:	lea    0x1b60(%rsp),%r12
  b53813:	mov    $0xc,%esi
  b53818:	movq   $0x20,0x1b68(%rsp)
  b53824:	movq   $0x0,0x1b70(%rsp)
  b53830:	movq   $0x0,0x1b80(%rsp)
  b5383c:	mov    %r12,%rdi
  b5383f:	movq   $0x0,0x1b78(%rsp)
  b5384b:	movq   $0x0,0x1c08(%rsp)
  b53857:	movq   $0x0,0x1b60(%rsp)
  b53863:	movl   $0x0,0x1b88(%rsp)
  b5386e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53873:	cmpq   $0x20,0x1b68(%rsp)
  b5387c:	lea    0x28(%r12),%rdx
  b53881:	jbe    b5388b <_ZN14CInventoryMenu12updateLayoutEv+0x45b>
  b53883:	mov    0x1c08(%rsp),%rdx
  b5388b:	mov    $0xfef791,%eax
  b53890:	movzbl (%rax),%ecx
  b53893:	add    $0x1,%rax
  b53897:	mov    %ecx,(%rdx)
  b53899:	add    $0x4,%rdx
  b5389d:	cmp    $0xfef79d,%rax
  b538a3:	jne    b53890 <_ZN14CInventoryMenu12updateLayoutEv+0x460>
  b538a5:	cmpq   $0x20,0x1b68(%rsp)
  b538ae:	movq   $0xc,0x1b60(%rsp)
  b538ba:	lea    0x58(%r12),%rax
  b538bf:	jbe    b538cd <_ZN14CInventoryMenu12updateLayoutEv+0x49d>
  b538c1:	mov    0x1c08(%rsp),%rax
  b538c9:	add    $0x30,%rax
  b538cd:	movl   $0x0,(%rax)
  b538d3:	mov    0x1cf8(%r14),%rdi
  b538da:	mov    %r12,%rsi
  b538dd:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b538e2:	lea    0x1ab0(%rsp),%r15
  b538ea:	mov    %rax,%rsi
  b538ed:	mov    %r15,%rdi
  b538f0:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b538f5:	lea    0x1a00(%rsp),%rbx
  b538fd:	mov    $0x5,%esi
  b53902:	movq   $0x20,0x1a08(%rsp)
  b5390e:	movq   $0x0,0x1a10(%rsp)
  b5391a:	movq   $0x0,0x1a20(%rsp)
  b53926:	mov    %rbx,%rdi
  b53929:	movq   $0x0,0x1a18(%rsp)
  b53935:	movq   $0x0,0x1aa8(%rsp)
  b53941:	movq   $0x0,0x1a00(%rsp)
  b5394d:	movl   $0x0,0x1a28(%rsp)
  b53958:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5395d:	cmpq   $0x20,0x1a08(%rsp)
  b53966:	lea    0x28(%rbx),%rdx
  b5396a:	jbe    b53974 <_ZN14CInventoryMenu12updateLayoutEv+0x544>
  b5396c:	mov    0x1aa8(%rsp),%rdx
  b53974:	mov    $0xfd0c0d,%eax
  b53979:	nopl   0x0(%rax)
  b53980:	movzbl (%rax),%ecx
  b53983:	add    $0x1,%rax
  b53987:	mov    %ecx,(%rdx)
  b53989:	add    $0x4,%rdx
  b5398d:	cmp    $0xfd0c12,%rax
  b53993:	jne    b53980 <_ZN14CInventoryMenu12updateLayoutEv+0x550>
  b53995:	cmpq   $0x20,0x1a08(%rsp)
  b5399e:	movq   $0x5,0x1a00(%rsp)
  b539aa:	lea    0x3c(%rbx),%rax
  b539ae:	jbe    b539bc <_ZN14CInventoryMenu12updateLayoutEv+0x58c>
  b539b0:	mov    0x1aa8(%rsp),%rax
  b539b8:	add    $0x14,%rax
  b539bc:	movl   $0x0,(%rax)
  b539c2:	mov    0x1a68(%rbp),%rdi
  b539c9:	mov    %r15,%rdx
  b539cc:	mov    %rbx,%rsi
  b539cf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b539d4:	mov    %rbx,%rdi
  b539d7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b539dc:	mov    %r15,%rdi
  b539df:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b539e4:	mov    %r12,%rdi
  b539e7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b539ec:	movss  0x48(%rsp),%xmm0
  b539f2:	addss  0x28(%rsp),%xmm0
  b539f8:	cvttss2si %xmm0,%eax
  b539fc:	cvtsi2ss %eax,%xmm1
  b53a00:	addss  0x54(%rsp),%xmm1
  b53a06:	movss  %xmm1,0x28(%rsp)
  b53a0c:	cmpl   $0x1,0x3e0(%r13)
  b53a14:	jbe    b53a80 <_ZN14CInventoryMenu12updateLayoutEv+0x650>
  b53a16:	mov    0x1028(%rbp),%rsi
  b53a1d:	lea    0x2210(%rsp),%rdi
  b53a25:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b53a2a:	xorps  %xmm2,%xmm2
  b53a2d:	xorps  %xmm0,%xmm0
  b53a30:	movss  0x450dd8(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b53a38:	movss  0x454cb4(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b53a40:	mulss  0x2218(%rsp),%xmm2
  b53a49:	cmpltss %xmm2,%xmm0
  b53a4e:	andps  %xmm0,%xmm1
  b53a51:	andnps %xmm3,%xmm0
  b53a54:	orps   %xmm1,%xmm0
  b53a57:	addss  %xmm2,%xmm0
  b53a5b:	cvttss2si %xmm0,%eax
  b53a5f:	cvtsi2ss %eax,%xmm0
  b53a63:	addss  0x221c(%rsp),%xmm0
  b53a6c:	mulss  0x492aac(%rip),%xmm0        # fe6520 <_ZTV8CSubMenu+0x80>
  b53a74:	addss  0x28(%rsp),%xmm0
  b53a7a:	movss  %xmm0,0x28(%rsp)
  b53a80:	mov    0x1028(%rbp),%rax
  b53a87:	xor    %esi,%esi
  b53a89:	mov    0xb0(%rax),%rdi
  b53a90:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  b53a95:	test   %al,%al
  b53a97:	je     b53c60 <_ZN14CInventoryMenu12updateLayoutEv+0x830>
  b53a9d:	mov    0x3f0(%r13),%r9d
  b53aa4:	test   %r9d,%r9d
  b53aa7:	je     b53c60 <_ZN14CInventoryMenu12updateLayoutEv+0x830>
  b53aad:	xor    %r12d,%r12d
  b53ab0:	lea    0x21f0(%rsp),%r15
  b53ab8:	jmp    b53be6 <_ZN14CInventoryMenu12updateLayoutEv+0x7b6>
  b53abd:	nopl   (%rax)
  b53ac0:	mov    0x3e8(%r13),%rax
  b53ac7:	mov    (%rax),%rax
  b53aca:	mov    0x2c8(%rax),%rbx
  b53ad1:	test   %rbx,%rbx
  b53ad4:	je     b53c14 <_ZN14CInventoryMenu12updateLayoutEv+0x7e4>
  b53ada:	mov    0xb0(%rbx),%rdi
  b53ae1:	test   %rdi,%rdi
  b53ae4:	je     b53aee <_ZN14CInventoryMenu12updateLayoutEv+0x6be>
  b53ae6:	mov    %rbx,%rsi
  b53ae9:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b53aee:	mov    0x30(%r14),%rdi
  b53af2:	mov    %rbx,%rsi
  b53af5:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b53afa:	lea    0x2200(%rsp),%rsi
  b53b02:	movss  0x30(%rsp),%xmm0
  b53b08:	movss  0x28(%rsp),%xmm1
  b53b0e:	mov    %rbx,%rdi
  b53b11:	movss  %xmm0,0x2204(%rsp)
  b53b1a:	movl   $0x0,0x2200(%rsp)
  b53b25:	movl   $0x0,0x2208(%rsp)
  b53b30:	movss  %xmm1,0x220c(%rsp)
  b53b39:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b53b3e:	mov    0x1028(%rbp),%rsi
  b53b45:	mov    %r15,%rdi
  b53b48:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b53b4d:	mov    %r15,%rsi
  b53b50:	mov    %rbx,%rdi
  b53b53:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b53b58:	mov    %rbx,%rdi
  b53b5b:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b53b60:	movb   $0x1,0x3e2(%rbx)
  b53b67:	mov    0x1028(%rbp),%rsi
  b53b6e:	lea    0x21e0(%rsp),%rdi
  b53b76:	add    $0x1,%r12d
  b53b7a:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b53b7f:	xorps  %xmm1,%xmm1
  b53b82:	cmp    0x3f0(%r13),%r12d
  b53b89:	xorps  %xmm0,%xmm0
  b53b8c:	movss  0x450c7c(%rip),%xmm2        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b53b94:	mulss  0x21e8(%rsp),%xmm1
  b53b9d:	movss  0x454b4f(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b53ba5:	cmpltss %xmm1,%xmm0
  b53baa:	andps  %xmm0,%xmm2
  b53bad:	andnps %xmm3,%xmm0
  b53bb0:	orps   %xmm2,%xmm0
  b53bb3:	movss  0x21ec(%rsp),%xmm2
  b53bbc:	jae    b53c60 <_ZN14CInventoryMenu12updateLayoutEv+0x830>
  b53bc2:	addss  %xmm1,%xmm0
  b53bc6:	cvttss2si %xmm0,%eax
  b53bca:	cvtsi2ss %eax,%xmm0
  b53bce:	addss  %xmm2,%xmm0
  b53bd2:	mulss  0x450c56(%rip),%xmm0        # fa4830 <_ZTVN4Ogre13FrameListenerE+0x70>
  b53bda:	addss  0x28(%rsp),%xmm0
  b53be0:	movss  %xmm0,0x28(%rsp)
  b53be6:	cmp    %r12d,0x3f4(%r13)
  b53bed:	jbe    b53ac0 <_ZN14CInventoryMenu12updateLayoutEv+0x690>
  b53bf3:	mov    %r12d,%eax
  b53bf6:	shl    $0x3,%rax
  b53bfa:	add    0x3e8(%r13),%rax
  b53c01:	mov    (%rax),%rax
  b53c04:	mov    0x2c8(%rax),%rbx
  b53c0b:	test   %rbx,%rbx
  b53c0e:	jne    b53ada <_ZN14CInventoryMenu12updateLayoutEv+0x6aa>
  b53c14:	mov    0x70(%r14),%rsi
  b53c18:	xor    %edx,%edx
  b53c1a:	mov    %rax,%rdi
  b53c1d:	mov    %rax,0x10(%rsp)
  b53c22:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  b53c27:	mov    0x10(%rsp),%rax
  b53c2c:	mov    0x2c8(%rax),%rbx
  b53c33:	test   %rbx,%rbx
  b53c36:	je     b53b67 <_ZN14CInventoryMenu12updateLayoutEv+0x737>
  b53c3c:	lea    0x38(%rbx),%rdi
  b53c40:	mov    $0x1,%esi
  b53c45:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b53c4a:	movb   $0x1,0x3e2(%rbx)
  b53c51:	jmp    b53ada <_ZN14CInventoryMenu12updateLayoutEv+0x6aa>
  b53c56:	cs nopw 0x0(%rax,%rax,1)
  b53c60:	mov    $0x36,%esi
  b53c65:	mov    %r13,%rdi
  b53c68:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  b53c6d:	test   %al,%al
  b53c6f:	je     b54880 <_ZN14CInventoryMenu12updateLayoutEv+0x1450>
  b53c75:	lea    0x17f0(%rsp),%r12
  b53c7d:	mov    $0xc,%esi
  b53c82:	movq   $0x20,0x17f8(%rsp)
  b53c8e:	movq   $0x0,0x1800(%rsp)
  b53c9a:	movq   $0x0,0x1810(%rsp)
  b53ca6:	mov    %r12,%rdi
  b53ca9:	movq   $0x0,0x1808(%rsp)
  b53cb5:	movq   $0x0,0x1898(%rsp)
  b53cc1:	movq   $0x0,0x17f0(%rsp)
  b53ccd:	movl   $0x0,0x1818(%rsp)
  b53cd8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53cdd:	cmpq   $0x20,0x17f8(%rsp)
  b53ce6:	lea    0x28(%r12),%rdx
  b53ceb:	jbe    b53cf5 <_ZN14CInventoryMenu12updateLayoutEv+0x8c5>
  b53ced:	mov    0x1898(%rsp),%rdx
  b53cf5:	mov    $0xfe609b,%eax
  b53cfa:	nopw   0x0(%rax,%rax,1)
  b53d00:	movzbl (%rax),%ecx
  b53d03:	add    $0x1,%rax
  b53d07:	mov    %ecx,(%rdx)
  b53d09:	add    $0x4,%rdx
  b53d0d:	cmp    $0xfe60a7,%rax
  b53d13:	jne    b53d00 <_ZN14CInventoryMenu12updateLayoutEv+0x8d0>
  b53d15:	cmpq   $0x20,0x17f8(%rsp)
  b53d1e:	movq   $0xc,0x17f0(%rsp)
  b53d2a:	lea    0x58(%r12),%rax
  b53d2f:	jbe    b53d3d <_ZN14CInventoryMenu12updateLayoutEv+0x90d>
  b53d31:	mov    0x1898(%rsp),%rax
  b53d39:	add    $0x30,%rax
  b53d3d:	movl   $0x0,(%rax)
  b53d43:	mov    0x1cf8(%r14),%rdi
  b53d4a:	mov    %r12,%rsi
  b53d4d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b53d52:	lea    0x1740(%rsp),%r13
  b53d5a:	mov    %rax,%rsi
  b53d5d:	mov    %r13,%rdi
  b53d60:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b53d65:	lea    0x1690(%rsp),%rbx
  b53d6d:	mov    $0x5,%esi
  b53d72:	movq   $0x20,0x1698(%rsp)
  b53d7e:	movq   $0x0,0x16a0(%rsp)
  b53d8a:	movq   $0x0,0x16b0(%rsp)
  b53d96:	mov    %rbx,%rdi
  b53d99:	movq   $0x0,0x16a8(%rsp)
  b53da5:	movq   $0x0,0x1738(%rsp)
  b53db1:	movq   $0x0,0x1690(%rsp)
  b53dbd:	movl   $0x0,0x16b8(%rsp)
  b53dc8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53dcd:	cmpq   $0x20,0x1698(%rsp)
  b53dd6:	lea    0x28(%rbx),%rdx
  b53dda:	jbe    b53de4 <_ZN14CInventoryMenu12updateLayoutEv+0x9b4>
  b53ddc:	mov    0x1738(%rsp),%rdx
  b53de4:	mov    $0xfd0c0d,%eax
  b53de9:	nopl   0x0(%rax)
  b53df0:	movzbl (%rax),%ecx
  b53df3:	add    $0x1,%rax
  b53df7:	mov    %ecx,(%rdx)
  b53df9:	add    $0x4,%rdx
  b53dfd:	cmp    $0xfd0c12,%rax
  b53e03:	jne    b53df0 <_ZN14CInventoryMenu12updateLayoutEv+0x9c0>
  b53e05:	cmpq   $0x20,0x1698(%rsp)
  b53e0e:	movq   $0x5,0x1690(%rsp)
  b53e1a:	lea    0x3c(%rbx),%rax
  b53e1e:	jbe    b53e2c <_ZN14CInventoryMenu12updateLayoutEv+0x9fc>
  b53e20:	mov    0x1738(%rsp),%rax
  b53e28:	add    $0x14,%rax
  b53e2c:	movl   $0x0,(%rax)
  b53e32:	mov    0x12b8(%rbp),%rdi
  b53e39:	mov    %r13,%rdx
  b53e3c:	mov    %rbx,%rsi
  b53e3f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b53e44:	mov    %rbx,%rdi
  b53e47:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b53e4c:	mov    %r13,%rdi
  b53e4f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b53e54:	mov    %r12,%rdi
  b53e57:	lea    0xfb0(%rsp),%r12
  b53e5f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b53e64:	xor    %esi,%esi
  b53e66:	mov    %r12,%rdi
  b53e69:	movq   $0x20,0xfb8(%rsp)
  b53e75:	movq   $0x0,0xfc0(%rsp)
  b53e81:	movq   $0x0,0xfd0(%rsp)
  b53e8d:	movq   $0x0,0xfc8(%rsp)
  b53e99:	movq   $0x0,0x1058(%rsp)
  b53ea5:	movq   $0x0,0xfb0(%rsp)
  b53eb1:	movl   $0x0,0xfd8(%rsp)
  b53ebc:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53ec1:	cmpq   $0x20,0xfb8(%rsp)
  b53eca:	movq   $0x0,0xfb0(%rsp)
  b53ed6:	lea    0x28(%r12),%rax
  b53edb:	jbe    b53ee5 <_ZN14CInventoryMenu12updateLayoutEv+0xab5>
  b53edd:	mov    0x1058(%rsp),%rax
  b53ee5:	lea    0x1060(%rsp),%rbx
  b53eed:	movl   $0x0,(%rax)
  b53ef3:	mov    $0x5,%esi
  b53ef8:	movq   $0x20,0x1068(%rsp)
  b53f04:	movq   $0x0,0x1070(%rsp)
  b53f10:	mov    %rbx,%rdi
  b53f13:	movq   $0x0,0x1080(%rsp)
  b53f1f:	movq   $0x0,0x1078(%rsp)
  b53f2b:	movq   $0x0,0x1108(%rsp)
  b53f37:	movq   $0x0,0x1060(%rsp)
  b53f43:	movl   $0x0,0x1088(%rsp)
  b53f4e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b53f53:	cmpq   $0x20,0x1068(%rsp)
  b53f5c:	lea    0x28(%rbx),%rdx
  b53f60:	jbe    b53f6a <_ZN14CInventoryMenu12updateLayoutEv+0xb3a>
  b53f62:	mov    0x1108(%rsp),%rdx
  b53f6a:	mov    $0xfd0c0d,%eax
  b53f6f:	nop
  b53f70:	movzbl (%rax),%ecx
  b53f73:	add    $0x1,%rax
  b53f77:	mov    %ecx,(%rdx)
  b53f79:	add    $0x4,%rdx
  b53f7d:	cmp    $0xfd0c12,%rax
  b53f83:	jne    b53f70 <_ZN14CInventoryMenu12updateLayoutEv+0xb40>
  b53f85:	cmpq   $0x20,0x1068(%rsp)
  b53f8e:	movq   $0x5,0x1060(%rsp)
  b53f9a:	lea    0x3c(%rbx),%rax
  b53f9e:	jbe    b53fac <_ZN14CInventoryMenu12updateLayoutEv+0xb7c>
  b53fa0:	mov    0x1108(%rsp),%rax
  b53fa8:	add    $0x14,%rax
  b53fac:	movl   $0x0,(%rax)
  b53fb2:	mov    0x1028(%rbp),%rdi
  b53fb9:	mov    %r12,%rdx
  b53fbc:	mov    %rbx,%rsi
  b53fbf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b53fc4:	mov    %rbx,%rdi
  b53fc7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b53fcc:	mov    %r12,%rdi
  b53fcf:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b53fd4:	cmpq   $0x0,0x38(%rsp)
  b53fda:	je     b54163 <_ZN14CInventoryMenu12updateLayoutEv+0xd33>
  b53fe0:	mov    0x38(%rsp),%rdi
  b53fe5:	lea    0x21d0(%rsp),%rsi
  b53fed:	movl   $0x0,0x21d4(%rsp)
  b53ff8:	movl   $0x0,0x21d0(%rsp)
  b54003:	movl   $0x3f800000,0x21dc(%rsp)
  b5400e:	movl   $0x0,0x21d8(%rsp)
  b54019:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5401e:	lea    0x21c0(%rsp),%rbx
  b54026:	mov    0x1028(%rbp),%rsi
  b5402d:	mov    %rbx,%rdi
  b54030:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b54035:	xorps  %xmm0,%xmm0
  b54038:	xorps  %xmm4,%xmm4
  b5403b:	movss  0x21cc(%rsp),%xmm6
  b54044:	xorps  %xmm1,%xmm1
  b54047:	mulss  0x21c0(%rsp),%xmm0
  b54050:	mulss  0x21c8(%rsp),%xmm4
  b54059:	ucomiss %xmm1,%xmm0
  b5405c:	ja     b54c58 <_ZN14CInventoryMenu12updateLayoutEv+0x1828>
  b54062:	movss  0x21c4(%rsp),%xmm5
  b5406b:	movss  0x454681(%rip),%xmm1        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b54073:	movss  0x450795(%rip),%xmm3        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b5407b:	addss  %xmm1,%xmm0
  b5407f:	xorps  %xmm1,%xmm1
  b54082:	movss  0x45466a(%rip),%xmm7        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b5408a:	mov    0x38(%rsp),%rdi
  b5408f:	lea    0x21b0(%rsp),%rsi
  b54097:	movl   $0x0,0x21c8(%rsp)
  b540a2:	movl   $0x0,0x21c0(%rsp)
  b540ad:	cmpltss %xmm4,%xmm1
  b540b2:	movl   $0x0,0x21b4(%rsp)
  b540bd:	movl   $0x0,0x21b0(%rsp)
  b540c8:	cvttss2si %xmm0,%eax
  b540cc:	movl   $0x0,0x21b8(%rsp)
  b540d7:	movss  0x47a3b9(%rip),%xmm0        # fce498 <_ZTV18iInventoryListener+0x58>
  b540df:	cvtsi2ss %eax,%xmm2
  b540e3:	addss  %xmm5,%xmm2
  b540e7:	movaps %xmm3,%xmm5
  b540ea:	andps  %xmm1,%xmm5
  b540ed:	andnps %xmm7,%xmm1
  b540f0:	mulss  %xmm2,%xmm0
  b540f4:	movss  %xmm2,0x21c4(%rsp)
  b540fd:	orps   %xmm5,%xmm1
  b54100:	movss  %xmm0,0x21cc(%rsp)
  b54109:	addss  %xmm4,%xmm1
  b5410d:	cvttss2si %xmm1,%eax
  b54111:	cvtsi2ss %eax,%xmm1
  b54115:	addss  %xmm6,%xmm1
  b54119:	subss  %xmm1,%xmm0
  b5411d:	movss  0x45465b(%rip),%xmm1        # fa8780 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xe0>
  b54125:	mulss  %xmm3,%xmm0
  b54129:	xorps  %xmm1,%xmm0
  b5412c:	movss  %xmm0,0x21bc(%rsp)
  b54135:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5413a:	mov    0x38(%rsp),%rdi
  b5413f:	mov    %rbx,%rsi
  b54142:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b54147:	mov    0x38(%rsp),%rdi
  b5414c:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b54151:	mov    0x38(%rsp),%rdi
  b54156:	movss  0x4506ca(%rip),%xmm0        # fa4828 <_ZTVN4Ogre13FrameListenerE+0x68>
  b5415e:	call   553278 <_ZN5CEGUI6Window6updateEf@plt>
  b54163:	cmpq   $0x0,0x8d02b5(%rip)        # 1424420 <_ZN5CEGUI6String4nposE>
  b5416b:	movq   $0x20,0xf08(%rsp)
  b54177:	movq   $0x0,0xf10(%rsp)
  b54183:	movq   $0x0,0xf20(%rsp)
  b5418f:	movq   $0x0,0xf18(%rsp)
  b5419b:	movq   $0x0,0xfa8(%rsp)
  b541a7:	movq   $0x0,0xf00(%rsp)
  b541b3:	movl   $0x0,0xf28(%rsp)
  b541be:	je     b55635 <_ZN14CInventoryMenu12updateLayoutEv+0x2205>
  b541c4:	lea    0xf00(%rsp),%rbx
  b541cc:	xor    %esi,%esi
  b541ce:	mov    %rbx,%rdi
  b541d1:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b541d6:	cmpq   $0x20,0xf08(%rsp)
  b541df:	movq   $0x0,0xf00(%rsp)
  b541eb:	lea    0x28(%rbx),%rax
  b541ef:	ja     b54c38 <_ZN14CInventoryMenu12updateLayoutEv+0x1808>
  b541f5:	movl   $0x0,(%rax)
  b541fb:	mov    0x1028(%rbp),%rdi
  b54202:	mov    %rbx,%rsi
  b54205:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  b5420a:	mov    %rbx,%rdi
  b5420d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54212:	addl   $0x1,0x40(%rsp)
  b54217:	add    $0x8,%rbp
  b5421b:	cmpl   $0xc,0x40(%rsp)
  b54220:	jne    b53560 <_ZN14CInventoryMenu12updateLayoutEv+0x130>
  b54226:	lea    0x6c0(%rsp),%rax
  b5422e:	lea    0x770(%rsp),%rdx
  b54236:	lea    0x4b0(%rsp),%r12
  b5423e:	lea    0x8d0(%rsp),%r15
  b54246:	mov    %r14,%rbx
  b54249:	movl   $0x13,0x28(%rsp)
  b54251:	add    $0x28,%rax
  b54255:	add    $0x28,%rdx
  b54259:	lea    0x28(%r12),%r13
  b5425e:	mov    %rax,0x30(%rsp)
  b54263:	mov    %rdx,0x38(%rsp)
  b54268:	lea    0x560(%rsp),%rax
  b54270:	lea    0x610(%rsp),%rdx
  b54278:	add    $0x28,%rax
  b5427c:	add    $0x28,%rdx
  b54280:	mov    %rax,0x40(%rsp)
  b54285:	mov    %rdx,0x48(%rsp)
  b5428a:	nopw   0x0(%rax,%rax,1)
  b54290:	lea    0x820(%rsp),%rdi
  b54298:	xor    %esi,%esi
  b5429a:	movq   $0x20,0x828(%rsp)
  b542a6:	movq   $0x0,0x830(%rsp)
  b542b2:	movq   $0x0,0x840(%rsp)
  b542be:	movq   $0x0,0x838(%rsp)
  b542ca:	movq   $0x0,0x8c8(%rsp)
  b542d6:	movq   $0x0,0x820(%rsp)
  b542e2:	movl   $0x0,0x848(%rsp)
  b542ed:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b542f2:	cmpq   $0x20,0x828(%rsp)
  b542fb:	movq   $0x0,0x820(%rsp)
  b54307:	ja     b54c10 <_ZN14CInventoryMenu12updateLayoutEv+0x17e0>
  b5430d:	lea    0x820(%rsp),%rax
  b54315:	add    $0x28,%rax
  b54319:	movl   $0x0,(%rax)
  b5431f:	mov    $0x5,%esi
  b54324:	mov    %r15,%rdi
  b54327:	movq   $0x20,0x8d8(%rsp)
  b54333:	movq   $0x0,0x8e0(%rsp)
  b5433f:	movq   $0x0,0x8f0(%rsp)
  b5434b:	movq   $0x0,0x8e8(%rsp)
  b54357:	movq   $0x0,0x978(%rsp)
  b54363:	movq   $0x0,0x8d0(%rsp)
  b5436f:	movl   $0x0,0x8f8(%rsp)
  b5437a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5437f:	cmpq   $0x20,0x8d8(%rsp)
  b54388:	lea    0x28(%r15),%rdx
  b5438c:	jbe    b54396 <_ZN14CInventoryMenu12updateLayoutEv+0xf66>
  b5438e:	mov    0x978(%rsp),%rdx
  b54396:	mov    $0xfd0c12,%ebp
  b5439b:	mov    $0xfd0c0d,%eax
  b543a0:	movzbl (%rax),%ecx
  b543a3:	add    $0x1,%rax
  b543a7:	mov    %ecx,(%rdx)
  b543a9:	add    $0x4,%rdx
  b543ad:	cmp    $0xfd0c12,%rax
  b543b3:	jne    b543a0 <_ZN14CInventoryMenu12updateLayoutEv+0xf70>
  b543b5:	cmpq   $0x20,0x8d8(%rsp)
  b543be:	movq   $0x5,0x8d0(%rsp)
  b543ca:	lea    0x3c(%r15),%rax
  b543ce:	jbe    b543dc <_ZN14CInventoryMenu12updateLayoutEv+0xfac>
  b543d0:	mov    0x978(%rsp),%rax
  b543d8:	add    $0x14,%rax
  b543dc:	movl   $0x0,(%rax)
  b543e2:	mov    0x1350(%rbx),%rdi
  b543e9:	lea    0x820(%rsp),%rdx
  b543f1:	mov    %r15,%rsi
  b543f4:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b543f9:	mov    %r15,%rdi
  b543fc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54401:	lea    0x820(%rsp),%rdi
  b54409:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5440e:	lea    0x6c0(%rsp),%rdi
  b54416:	xor    %esi,%esi
  b54418:	movq   $0x20,0x6c8(%rsp)
  b54424:	movq   $0x0,0x6d0(%rsp)
  b54430:	movq   $0x0,0x6e0(%rsp)
  b5443c:	movq   $0x0,0x6d8(%rsp)
  b54448:	movq   $0x0,0x768(%rsp)
  b54454:	movq   $0x0,0x6c0(%rsp)
  b54460:	movl   $0x0,0x6e8(%rsp)
  b5446b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54470:	cmpq   $0x21,0x6c8(%rsp)
  b54479:	mov    0x30(%rsp),%rax
  b5447e:	lea    0x770(%rsp),%rdi
  b54486:	cmovae 0x768(%rsp),%rax
  b5448f:	movq   $0x0,0x6c0(%rsp)
  b5449b:	mov    $0x5,%esi
  b544a0:	movl   $0x0,(%rax)
  b544a6:	movq   $0x20,0x778(%rsp)
  b544b2:	movq   $0x0,0x780(%rsp)
  b544be:	movq   $0x0,0x790(%rsp)
  b544ca:	movq   $0x0,0x788(%rsp)
  b544d6:	movq   $0x0,0x818(%rsp)
  b544e2:	movq   $0x0,0x770(%rsp)
  b544ee:	movl   $0x0,0x798(%rsp)
  b544f9:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b544fe:	cmpq   $0x21,0x778(%rsp)
  b54507:	mov    0x38(%rsp),%rdx
  b5450c:	mov    $0xfd0c0d,%eax
  b54511:	cmovae 0x818(%rsp),%rdx
  b5451a:	nopw   0x0(%rax,%rax,1)
  b54520:	movzbl (%rax),%ecx
  b54523:	add    $0x1,%rax
  b54527:	mov    %ecx,(%rdx)
  b54529:	add    $0x4,%rdx
  b5452d:	cmp    %rax,%rbp
  b54530:	jne    b54520 <_ZN14CInventoryMenu12updateLayoutEv+0x10f0>
  b54532:	cmpq   $0x20,0x778(%rsp)
  b5453b:	movq   $0x5,0x770(%rsp)
  b54547:	ja     b54c20 <_ZN14CInventoryMenu12updateLayoutEv+0x17f0>
  b5454d:	lea    0x770(%rsp),%rax
  b54555:	add    $0x3c,%rax
  b54559:	movl   $0x0,(%rax)
  b5455f:	mov    0x15e0(%rbx),%rdi
  b54566:	lea    0x6c0(%rsp),%rdx
  b5456e:	lea    0x770(%rsp),%rsi
  b54576:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5457b:	lea    0x770(%rsp),%rdi
  b54583:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54588:	lea    0x6c0(%rsp),%rdi
  b54590:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54595:	lea    0x560(%rsp),%rdi
  b5459d:	xor    %esi,%esi
  b5459f:	movq   $0x20,0x568(%rsp)
  b545ab:	movq   $0x0,0x570(%rsp)
  b545b7:	movq   $0x0,0x580(%rsp)
  b545c3:	movq   $0x0,0x578(%rsp)
  b545cf:	movq   $0x0,0x608(%rsp)
  b545db:	movq   $0x0,0x560(%rsp)
  b545e7:	movl   $0x0,0x588(%rsp)
  b545f2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b545f7:	cmpq   $0x21,0x568(%rsp)
  b54600:	mov    0x40(%rsp),%rax
  b54605:	lea    0x610(%rsp),%rdi
  b5460d:	cmovae 0x608(%rsp),%rax
  b54616:	movq   $0x0,0x560(%rsp)
  b54622:	mov    $0x5,%esi
  b54627:	movl   $0x0,(%rax)
  b5462d:	movq   $0x20,0x618(%rsp)
  b54639:	movq   $0x0,0x620(%rsp)
  b54645:	movq   $0x0,0x630(%rsp)
  b54651:	movq   $0x0,0x628(%rsp)
  b5465d:	movq   $0x0,0x6b8(%rsp)
  b54669:	movq   $0x0,0x610(%rsp)
  b54675:	movl   $0x0,0x638(%rsp)
  b54680:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54685:	cmpq   $0x21,0x618(%rsp)
  b5468e:	mov    0x48(%rsp),%rdx
  b54693:	mov    $0xfd0c0d,%eax
  b54698:	cmovae 0x6b8(%rsp),%rdx
  b546a1:	nopl   0x0(%rax)
  b546a8:	movzbl (%rax),%ecx
  b546ab:	add    $0x1,%rax
  b546af:	mov    %ecx,(%rdx)
  b546b1:	add    $0x4,%rdx
  b546b5:	cmp    %rax,%rbp
  b546b8:	jne    b546a8 <_ZN14CInventoryMenu12updateLayoutEv+0x1278>
  b546ba:	cmpq   $0x20,0x618(%rsp)
  b546c3:	movq   $0x5,0x610(%rsp)
  b546cf:	ja     b54bf8 <_ZN14CInventoryMenu12updateLayoutEv+0x17c8>
  b546d5:	lea    0x610(%rsp),%rax
  b546dd:	add    $0x3c,%rax
  b546e1:	movl   $0x0,(%rax)
  b546e7:	mov    0x1b00(%rbx),%rdi
  b546ee:	lea    0x560(%rsp),%rdx
  b546f6:	lea    0x610(%rsp),%rsi
  b546fe:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b54703:	lea    0x610(%rsp),%rdi
  b5470b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54710:	lea    0x560(%rsp),%rdi
  b54718:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5471d:	cmpq   $0x0,0x1870(%rbx)
  b54725:	je     b547d4 <_ZN14CInventoryMenu12updateLayoutEv+0x13a4>
  b5472b:	cmpq   $0x0,0x8cfced(%rip)        # 1424420 <_ZN5CEGUI6String4nposE>
  b54733:	movq   $0x20,0x4b8(%rsp)
  b5473f:	movq   $0x0,0x4c0(%rsp)
  b5474b:	movq   $0x0,0x4d0(%rsp)
  b54757:	movq   $0x0,0x4c8(%rsp)
  b54763:	movq   $0x0,0x558(%rsp)
  b5476f:	movq   $0x0,0x4b0(%rsp)
  b5477b:	movl   $0x0,0x4d8(%rsp)
  b54786:	je     b55861 <_ZN14CInventoryMenu12updateLayoutEv+0x2431>
  b5478c:	xor    %esi,%esi
  b5478e:	mov    %r12,%rdi
  b54791:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54796:	cmpq   $0x21,0x4b8(%rsp)
  b5479f:	mov    %r13,%rax
  b547a2:	movq   $0x0,0x4b0(%rsp)
  b547ae:	cmovae 0x558(%rsp),%rax
  b547b7:	mov    %r12,%rsi
  b547ba:	movl   $0x0,(%rax)
  b547c0:	mov    0x1870(%rbx),%rdi
  b547c7:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  b547cc:	mov    %r12,%rdi
  b547cf:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b547d4:	mov    0x10c0(%rbx),%rdi
  b547db:	mov    0x78(%rdi),%rdx
  b547df:	mov    0x80(%rdi),%rax
  b547e6:	sub    %rdx,%rax
  b547e9:	sar    $0x3,%rax
  b547ed:	test   %rax,%rax
  b547f0:	jne    b54c48 <_ZN14CInventoryMenu12updateLayoutEv+0x1818>
  b547f6:	addl   $0x1,0x28(%rsp)
  b547fb:	add    $0x8,%rbx
  b547ff:	cmpl   $0x52,0x28(%rsp)
  b54804:	jne    b54290 <_ZN14CInventoryMenu12updateLayoutEv+0xe60>
  b5480a:	mov    0x58(%rsp),%rax
  b5480f:	cmpl   $0x0,0x38(%rax)
  b54813:	je     b55be6 <_ZN14CInventoryMenu12updateLayoutEv+0x27b6>
  b54819:	xor    %ebx,%ebx
  b5481b:	mov    %rax,%r12
  b5481e:	jmp    b5485f <_ZN14CInventoryMenu12updateLayoutEv+0x142f>
  b54820:	mov    0x30(%r12),%rcx
  b54825:	mov    (%rcx),%rax
  b54828:	mov    0x10(%rax),%rsi
  b5482c:	cmpl   $0x12,0x18(%rax)
  b54830:	jle    b54851 <_ZN14CInventoryMenu12updateLayoutEv+0x1421>
  b54832:	cmp    %ebx,%edx
  b54834:	jbe    b54841 <_ZN14CInventoryMenu12updateLayoutEv+0x1411>
  b54836:	mov    %ebx,%ecx
  b54838:	shl    $0x3,%rcx
  b5483c:	add    0x30(%r12),%rcx
  b54841:	mov    (%rcx),%rax
  b54844:	mov    %r14,%rdi
  b54847:	mov    0x18(%rax),%edx
  b5484a:	mov    %edx,%ecx
  b5484c:	call   b51bf0 <_ZN14CInventoryMenu11setSlotIconEP10CEquipmentii>
  b54851:	add    $0x1,%ebx
  b54854:	cmp    0x38(%r12),%ebx
  b54859:	jae    b55be6 <_ZN14CInventoryMenu12updateLayoutEv+0x27b6>
  b5485f:	mov    0x3c(%r12),%edx
  b54864:	cmp    %ebx,%edx
  b54866:	jbe    b54820 <_ZN14CInventoryMenu12updateLayoutEv+0x13f0>
  b54868:	mov    0x30(%r12),%rcx
  b5486d:	mov    %ebx,%eax
  b5486f:	mov    (%rcx,%rax,8),%rax
  b54873:	mov    0x10(%rax),%rsi
  b54877:	jmp    b5482c <_ZN14CInventoryMenu12updateLayoutEv+0x13fc>
  b54879:	nopl   0x0(%rax)
  b54880:	mov    0x0(%r13),%rax
  b54884:	mov    %r13,%rdi
  b54887:	call   *0x2b0(%rax)
  b5488d:	test   %al,%al
  b5488f:	je     b54c71 <_ZN14CInventoryMenu12updateLayoutEv+0x1841>
  b54895:	mov    $0x37,%esi
  b5489a:	mov    %r13,%rdi
  b5489d:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  b548a2:	test   %al,%al
  b548a4:	je     b55695 <_ZN14CInventoryMenu12updateLayoutEv+0x2265>
  b548aa:	lea    0x15e0(%rsp),%r12
  b548b2:	mov    $0xc,%esi
  b548b7:	movq   $0x20,0x15e8(%rsp)
  b548c3:	movq   $0x0,0x15f0(%rsp)
  b548cf:	movq   $0x0,0x1600(%rsp)
  b548db:	mov    %r12,%rdi
  b548de:	movq   $0x0,0x15f8(%rsp)
  b548ea:	movq   $0x0,0x1688(%rsp)
  b548f6:	movq   $0x0,0x15e0(%rsp)
  b54902:	movl   $0x0,0x1608(%rsp)
  b5490d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54912:	cmpq   $0x20,0x15e8(%rsp)
  b5491b:	lea    0x28(%r12),%rdx
  b54920:	ja     b5592e <_ZN14CInventoryMenu12updateLayoutEv+0x24fe>
  b54926:	mov    $0xfe60a8,%eax
  b5492b:	nopl   0x0(%rax,%rax,1)
  b54930:	movzbl (%rax),%ecx
  b54933:	add    $0x1,%rax
  b54937:	mov    %ecx,(%rdx)
  b54939:	add    $0x4,%rdx
  b5493d:	cmp    $0xfe60b4,%rax
  b54943:	jne    b54930 <_ZN14CInventoryMenu12updateLayoutEv+0x1500>
  b54945:	cmpq   $0x20,0x15e8(%rsp)
  b5494e:	movq   $0xc,0x15e0(%rsp)
  b5495a:	lea    0x58(%r12),%rax
  b5495f:	ja     b5595d <_ZN14CInventoryMenu12updateLayoutEv+0x252d>
  b54965:	movl   $0x0,(%rax)
  b5496b:	mov    0x1cf8(%r14),%rdi
  b54972:	mov    %r12,%rsi
  b54975:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b5497a:	lea    0x1530(%rsp),%r13
  b54982:	mov    %rax,%rsi
  b54985:	mov    %r13,%rdi
  b54988:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b5498d:	lea    0x1480(%rsp),%rbx
  b54995:	mov    $0x5,%esi
  b5499a:	movq   $0x20,0x1488(%rsp)
  b549a6:	movq   $0x0,0x1490(%rsp)
  b549b2:	movq   $0x0,0x14a0(%rsp)
  b549be:	mov    %rbx,%rdi
  b549c1:	movq   $0x0,0x1498(%rsp)
  b549cd:	movq   $0x0,0x1528(%rsp)
  b549d9:	movq   $0x0,0x1480(%rsp)
  b549e5:	movl   $0x0,0x14a8(%rsp)
  b549f0:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b549f5:	cmpq   $0x20,0x1488(%rsp)
  b549fe:	lea    0x28(%rbx),%rdx
  b54a02:	ja     b55921 <_ZN14CInventoryMenu12updateLayoutEv+0x24f1>
  b54a08:	mov    $0xfd0c0d,%eax
  b54a0d:	nopl   (%rax)
  b54a10:	movzbl (%rax),%ecx
  b54a13:	add    $0x1,%rax
  b54a17:	mov    %ecx,(%rdx)
  b54a19:	add    $0x4,%rdx
  b54a1d:	cmp    $0xfd0c12,%rax
  b54a23:	jne    b54a10 <_ZN14CInventoryMenu12updateLayoutEv+0x15e0>
  b54a25:	cmpq   $0x20,0x1488(%rsp)
  b54a2e:	movq   $0x5,0x1480(%rsp)
  b54a3a:	lea    0x3c(%rbx),%rax
  b54a3e:	ja     b5596e <_ZN14CInventoryMenu12updateLayoutEv+0x253e>
  b54a44:	movl   $0x0,(%rax)
  b54a4a:	mov    0x12b8(%rbp),%rdi
  b54a51:	mov    %r13,%rdx
  b54a54:	mov    %rbx,%rsi
  b54a57:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b54a5c:	mov    %rbx,%rdi
  b54a5f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54a64:	mov    %r13,%rdi
  b54a67:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54a6c:	jmp    b53e54 <_ZN14CInventoryMenu12updateLayoutEv+0xa24>
  b54a71:	nopl   0x0(%rax)
  b54a78:	lea    0x18a0(%rsp),%r12
  b54a80:	xor    %esi,%esi
  b54a82:	movq   $0x20,0x18a8(%rsp)
  b54a8e:	movq   $0x0,0x18b0(%rsp)
  b54a9a:	movq   $0x0,0x18c0(%rsp)
  b54aa6:	mov    %r12,%rdi
  b54aa9:	movq   $0x0,0x18b8(%rsp)
  b54ab5:	movq   $0x0,0x1948(%rsp)
  b54ac1:	movq   $0x0,0x18a0(%rsp)
  b54acd:	movl   $0x0,0x18c8(%rsp)
  b54ad8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54add:	cmpq   $0x20,0x18a8(%rsp)
  b54ae6:	movq   $0x0,0x18a0(%rsp)
  b54af2:	lea    0x28(%r12),%rax
  b54af7:	jbe    b54b01 <_ZN14CInventoryMenu12updateLayoutEv+0x16d1>
  b54af9:	mov    0x1948(%rsp),%rax
  b54b01:	lea    0x1950(%rsp),%rbx
  b54b09:	movl   $0x0,(%rax)
  b54b0f:	mov    $0x5,%esi
  b54b14:	movq   $0x20,0x1958(%rsp)
  b54b20:	movq   $0x0,0x1960(%rsp)
  b54b2c:	mov    %rbx,%rdi
  b54b2f:	movq   $0x0,0x1970(%rsp)
  b54b3b:	movq   $0x0,0x1968(%rsp)
  b54b47:	movq   $0x0,0x19f8(%rsp)
  b54b53:	movq   $0x0,0x1950(%rsp)
  b54b5f:	movl   $0x0,0x1978(%rsp)
  b54b6a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54b6f:	cmpq   $0x20,0x1958(%rsp)
  b54b78:	lea    0x28(%rbx),%rdx
  b54b7c:	jbe    b54b86 <_ZN14CInventoryMenu12updateLayoutEv+0x1756>
  b54b7e:	mov    0x19f8(%rsp),%rdx
  b54b86:	mov    $0xfd0c0d,%eax
  b54b8b:	nopl   0x0(%rax,%rax,1)
  b54b90:	movzbl (%rax),%ecx
  b54b93:	add    $0x1,%rax
  b54b97:	mov    %ecx,(%rdx)
  b54b99:	add    $0x4,%rdx
  b54b9d:	cmp    $0xfd0c12,%rax
  b54ba3:	jne    b54b90 <_ZN14CInventoryMenu12updateLayoutEv+0x1760>
  b54ba5:	cmpq   $0x20,0x1958(%rsp)
  b54bae:	movq   $0x5,0x1950(%rsp)
  b54bba:	lea    0x3c(%rbx),%rax
  b54bbe:	jbe    b54bcc <_ZN14CInventoryMenu12updateLayoutEv+0x179c>
  b54bc0:	mov    0x19f8(%rsp),%rax
  b54bc8:	add    $0x14,%rax
  b54bcc:	movl   $0x0,(%rax)
  b54bd2:	mov    0x1a68(%rbp),%rdi
  b54bd9:	mov    %r12,%rdx
  b54bdc:	mov    %rbx,%rsi
  b54bdf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b54be4:	mov    %rbx,%rdi
  b54be7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54bec:	jmp    b539e4 <_ZN14CInventoryMenu12updateLayoutEv+0x5b4>
  b54bf1:	nopl   0x0(%rax)
  b54bf8:	mov    0x6b8(%rsp),%rax
  b54c00:	add    $0x14,%rax
  b54c04:	jmp    b546e1 <_ZN14CInventoryMenu12updateLayoutEv+0x12b1>
  b54c09:	nopl   0x0(%rax)
  b54c10:	mov    0x8c8(%rsp),%rax
  b54c18:	jmp    b54319 <_ZN14CInventoryMenu12updateLayoutEv+0xee9>
  b54c1d:	nopl   (%rax)
  b54c20:	mov    0x818(%rsp),%rax
  b54c28:	add    $0x14,%rax
  b54c2c:	jmp    b54559 <_ZN14CInventoryMenu12updateLayoutEv+0x1129>
  b54c31:	nopl   0x0(%rax)
  b54c38:	mov    0xfa8(%rsp),%rax
  b54c40:	jmp    b541f5 <_ZN14CInventoryMenu12updateLayoutEv+0xdc5>
  b54c45:	nopl   (%rax)
  b54c48:	mov    (%rdx),%rsi
  b54c4b:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b54c50:	jmp    b547f6 <_ZN14CInventoryMenu12updateLayoutEv+0x13c6>
  b54c55:	nopl   (%rax)
  b54c58:	movss  0x44fbb0(%rip),%xmm3        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b54c60:	movss  0x21c4(%rsp),%xmm5
  b54c69:	movaps %xmm3,%xmm1
  b54c6c:	jmp    b5407b <_ZN14CInventoryMenu12updateLayoutEv+0xc4b>
  b54c71:	lea    0x1110(%rsp),%r12
  b54c79:	xor    %esi,%esi
  b54c7b:	movq   $0x20,0x1118(%rsp)
  b54c87:	movq   $0x0,0x1120(%rsp)
  b54c93:	movq   $0x0,0x1130(%rsp)
  b54c9f:	mov    %r12,%rdi
  b54ca2:	movq   $0x0,0x1128(%rsp)
  b54cae:	movq   $0x0,0x11b8(%rsp)
  b54cba:	movq   $0x0,0x1110(%rsp)
  b54cc6:	movl   $0x0,0x1138(%rsp)
  b54cd1:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54cd6:	cmpq   $0x20,0x1118(%rsp)
  b54cdf:	movq   $0x0,0x1110(%rsp)
  b54ceb:	lea    0x28(%r12),%rax
  b54cf0:	jbe    b54cfa <_ZN14CInventoryMenu12updateLayoutEv+0x18ca>
  b54cf2:	mov    0x11b8(%rsp),%rax
  b54cfa:	lea    0x11c0(%rsp),%rbx
  b54d02:	movl   $0x0,(%rax)
  b54d08:	mov    $0x5,%esi
  b54d0d:	movq   $0x20,0x11c8(%rsp)
  b54d19:	movq   $0x0,0x11d0(%rsp)
  b54d25:	mov    %rbx,%rdi
  b54d28:	movq   $0x0,0x11e0(%rsp)
  b54d34:	movq   $0x0,0x11d8(%rsp)
  b54d40:	movq   $0x0,0x1268(%rsp)
  b54d4c:	movq   $0x0,0x11c0(%rsp)
  b54d58:	movl   $0x0,0x11e8(%rsp)
  b54d63:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54d68:	cmpq   $0x20,0x11c8(%rsp)
  b54d71:	lea    0x28(%rbx),%rdx
  b54d75:	jbe    b54d7f <_ZN14CInventoryMenu12updateLayoutEv+0x194f>
  b54d77:	mov    0x1268(%rsp),%rdx
  b54d7f:	mov    $0xfd0c0d,%eax
  b54d84:	nopl   0x0(%rax)
  b54d88:	movzbl (%rax),%ecx
  b54d8b:	add    $0x1,%rax
  b54d8f:	mov    %ecx,(%rdx)
  b54d91:	add    $0x4,%rdx
  b54d95:	cmp    $0xfd0c12,%rax
  b54d9b:	jne    b54d88 <_ZN14CInventoryMenu12updateLayoutEv+0x1958>
  b54d9d:	cmpq   $0x20,0x11c8(%rsp)
  b54da6:	movq   $0x5,0x11c0(%rsp)
  b54db2:	lea    0x3c(%rbx),%rax
  b54db6:	jbe    b54dc4 <_ZN14CInventoryMenu12updateLayoutEv+0x1994>
  b54db8:	mov    0x1268(%rsp),%rax
  b54dc0:	add    $0x14,%rax
  b54dc4:	movl   $0x0,(%rax)
  b54dca:	mov    0x12b8(%rbp),%rdi
  b54dd1:	mov    %r12,%rdx
  b54dd4:	mov    %rbx,%rsi
  b54dd7:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b54ddc:	mov    %rbx,%rdi
  b54ddf:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54de4:	jmp    b53e54 <_ZN14CInventoryMenu12updateLayoutEv+0xa24>
  b54de9:	cmpq   $0x0,0x1028(%rbp)
  b54df1:	je     b54212 <_ZN14CInventoryMenu12updateLayoutEv+0xde2>
  b54df7:	lea    0xda0(%rsp),%r13
  b54dff:	xor    %esi,%esi
  b54e01:	movq   $0x20,0xda8(%rsp)
  b54e0d:	movq   $0x0,0xdb0(%rsp)
  b54e19:	movq   $0x0,0xdc0(%rsp)
  b54e25:	mov    %r13,%rdi
  b54e28:	movq   $0x0,0xdb8(%rsp)
  b54e34:	movq   $0x0,0xe48(%rsp)
  b54e40:	movq   $0x0,0xda0(%rsp)
  b54e4c:	movl   $0x0,0xdc8(%rsp)
  b54e57:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54e5c:	cmpq   $0x20,0xda8(%rsp)
  b54e65:	movq   $0x0,0xda0(%rsp)
  b54e71:	lea    0x28(%r13),%rax
  b54e75:	ja     b5597f <_ZN14CInventoryMenu12updateLayoutEv+0x254f>
  b54e7b:	lea    0xe50(%rsp),%r12
  b54e83:	movl   $0x0,(%rax)
  b54e89:	mov    $0x5,%esi
  b54e8e:	movq   $0x20,0xe58(%rsp)
  b54e9a:	movq   $0x0,0xe60(%rsp)
  b54ea6:	mov    %r12,%rdi
  b54ea9:	movq   $0x0,0xe70(%rsp)
  b54eb5:	movq   $0x0,0xe68(%rsp)
  b54ec1:	movq   $0x0,0xef8(%rsp)
  b54ecd:	movq   $0x0,0xe50(%rsp)
  b54ed9:	movl   $0x0,0xe78(%rsp)
  b54ee4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54ee9:	cmpq   $0x20,0xe58(%rsp)
  b54ef2:	lea    0x28(%r12),%rdx
  b54ef7:	ja     b558fa <_ZN14CInventoryMenu12updateLayoutEv+0x24ca>
  b54efd:	mov    $0xfd0c12,%ebx
  b54f02:	mov    $0xfd0c0d,%eax
  b54f07:	nopw   0x0(%rax,%rax,1)
  b54f10:	movzbl (%rax),%ecx
  b54f13:	add    $0x1,%rax
  b54f17:	mov    %ecx,(%rdx)
  b54f19:	add    $0x4,%rdx
  b54f1d:	cmp    $0xfd0c12,%rax
  b54f23:	jne    b54f10 <_ZN14CInventoryMenu12updateLayoutEv+0x1ae0>
  b54f25:	cmpq   $0x20,0xe58(%rsp)
  b54f2e:	movq   $0x5,0xe50(%rsp)
  b54f3a:	lea    0x3c(%r12),%rax
  b54f3f:	ja     b5598c <_ZN14CInventoryMenu12updateLayoutEv+0x255c>
  b54f45:	movl   $0x0,(%rax)
  b54f4b:	mov    0x1a68(%rbp),%rdi
  b54f52:	mov    %r13,%rdx
  b54f55:	mov    %r12,%rsi
  b54f58:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b54f5d:	mov    %r12,%rdi
  b54f60:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54f65:	mov    %r13,%rdi
  b54f68:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b54f6d:	lea    0xc40(%rsp),%rdi
  b54f75:	xor    %esi,%esi
  b54f77:	movq   $0x20,0xc48(%rsp)
  b54f83:	movq   $0x0,0xc50(%rsp)
  b54f8f:	movq   $0x0,0xc60(%rsp)
  b54f9b:	movq   $0x0,0xc58(%rsp)
  b54fa7:	movq   $0x0,0xce8(%rsp)
  b54fb3:	movq   $0x0,0xc40(%rsp)
  b54fbf:	movl   $0x0,0xc68(%rsp)
  b54fca:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b54fcf:	cmpq   $0x21,0xc48(%rsp)
  b54fd8:	mov    0x88(%rsp),%rax
  b54fe0:	lea    0xcf0(%rsp),%rdi
  b54fe8:	cmovae 0xce8(%rsp),%rax
  b54ff1:	movq   $0x0,0xc40(%rsp)
  b54ffd:	mov    $0x5,%esi
  b55002:	movl   $0x0,(%rax)
  b55008:	movq   $0x20,0xcf8(%rsp)
  b55014:	movq   $0x0,0xd00(%rsp)
  b55020:	movq   $0x0,0xd10(%rsp)
  b5502c:	movq   $0x0,0xd08(%rsp)
  b55038:	movq   $0x0,0xd98(%rsp)
  b55044:	movq   $0x0,0xcf0(%rsp)
  b55050:	movl   $0x0,0xd18(%rsp)
  b5505b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55060:	cmpq   $0x20,0xcf8(%rsp)
  b55069:	ja     b558ed <_ZN14CInventoryMenu12updateLayoutEv+0x24bd>
  b5506f:	lea    0xcf0(%rsp),%rdx
  b55077:	add    $0x28,%rdx
  b5507b:	mov    $0xfd0c0d,%eax
  b55080:	movzbl (%rax),%ecx
  b55083:	add    $0x1,%rax
  b55087:	mov    %ecx,(%rdx)
  b55089:	add    $0x4,%rdx
  b5508d:	cmp    %rax,%rbx
  b55090:	jne    b55080 <_ZN14CInventoryMenu12updateLayoutEv+0x1c50>
  b55092:	cmpq   $0x20,0xcf8(%rsp)
  b5509b:	movq   $0x5,0xcf0(%rsp)
  b550a7:	mov    0x80(%rsp),%rax
  b550af:	jbe    b550bd <_ZN14CInventoryMenu12updateLayoutEv+0x1c8d>
  b550b1:	mov    0xd98(%rsp),%rax
  b550b9:	add    $0x14,%rax
  b550bd:	movl   $0x0,(%rax)
  b550c3:	mov    0x1548(%rbp),%rdi
  b550ca:	lea    0xc40(%rsp),%rdx
  b550d2:	lea    0xcf0(%rsp),%rsi
  b550da:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b550df:	lea    0xcf0(%rsp),%rdi
  b550e7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b550ec:	lea    0xc40(%rsp),%rdi
  b550f4:	lea    0x21a0(%rsp),%r12
  b550fc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55101:	mov    0x1028(%rbp),%rsi
  b55108:	mov    %r12,%rdi
  b5510b:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b55110:	mov    0x1548(%rbp),%rdi
  b55117:	mov    %r12,%rsi
  b5511a:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5511f:	lea    0xae0(%rsp),%rdi
  b55127:	xor    %esi,%esi
  b55129:	movq   $0x20,0xae8(%rsp)
  b55135:	movq   $0x0,0xaf0(%rsp)
  b55141:	movq   $0x0,0xb00(%rsp)
  b5514d:	movq   $0x0,0xaf8(%rsp)
  b55159:	movq   $0x0,0xb88(%rsp)
  b55165:	movq   $0x0,0xae0(%rsp)
  b55171:	movl   $0x0,0xb08(%rsp)
  b5517c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55181:	cmpq   $0x21,0xae8(%rsp)
  b5518a:	mov    0x78(%rsp),%rax
  b5518f:	lea    0xb90(%rsp),%rdi
  b55197:	cmovae 0xb88(%rsp),%rax
  b551a0:	movq   $0x0,0xae0(%rsp)
  b551ac:	mov    $0x5,%esi
  b551b1:	movl   $0x0,(%rax)
  b551b7:	movq   $0x20,0xb98(%rsp)
  b551c3:	movq   $0x0,0xba0(%rsp)
  b551cf:	movq   $0x0,0xbb0(%rsp)
  b551db:	movq   $0x0,0xba8(%rsp)
  b551e7:	movq   $0x0,0xc38(%rsp)
  b551f3:	movq   $0x0,0xb90(%rsp)
  b551ff:	movl   $0x0,0xbb8(%rsp)
  b5520a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5520f:	cmpq   $0x20,0xb98(%rsp)
  b55218:	ja     b55bd9 <_ZN14CInventoryMenu12updateLayoutEv+0x27a9>
  b5521e:	lea    0xb90(%rsp),%rdx
  b55226:	add    $0x28,%rdx
  b5522a:	mov    $0xfd0c0d,%eax
  b5522f:	nop
  b55230:	movzbl (%rax),%ecx
  b55233:	add    $0x1,%rax
  b55237:	mov    %ecx,(%rdx)
  b55239:	add    $0x4,%rdx
  b5523d:	cmp    %rax,%rbx
  b55240:	jne    b55230 <_ZN14CInventoryMenu12updateLayoutEv+0x1e00>
  b55242:	cmpq   $0x20,0xb98(%rsp)
  b5524b:	movq   $0x5,0xb90(%rsp)
  b55257:	mov    0x70(%rsp),%rax
  b5525c:	jbe    b5526a <_ZN14CInventoryMenu12updateLayoutEv+0x1e3a>
  b5525e:	mov    0xc38(%rsp),%rax
  b55266:	add    $0x14,%rax
  b5526a:	movl   $0x0,(%rax)
  b55270:	mov    0x12b8(%rbp),%rdi
  b55277:	lea    0xae0(%rsp),%rdx
  b5527f:	lea    0xb90(%rsp),%rsi
  b55287:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5528c:	lea    0xb90(%rsp),%rdi
  b55294:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55299:	lea    0xae0(%rsp),%rdi
  b552a1:	lea    0x2190(%rsp),%r12
  b552a9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b552ae:	mov    0x1028(%rbp),%rsi
  b552b5:	mov    %r12,%rdi
  b552b8:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b552bd:	mov    0x12b8(%rbp),%rdi
  b552c4:	mov    %r12,%rsi
  b552c7:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b552cc:	lea    0xa30(%rsp),%rdi
  b552d4:	mov    $0x5,%esi
  b552d9:	movq   $0x20,0xa38(%rsp)
  b552e5:	movq   $0x0,0xa40(%rsp)
  b552f1:	movq   $0x0,0xa50(%rsp)
  b552fd:	movq   $0x0,0xa48(%rsp)
  b55309:	movq   $0x0,0xad8(%rsp)
  b55315:	movq   $0x0,0xa30(%rsp)
  b55321:	movl   $0x0,0xa58(%rsp)
  b5532c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55331:	cmpq   $0x20,0xa38(%rsp)
  b5533a:	ja     b55bcc <_ZN14CInventoryMenu12updateLayoutEv+0x279c>
  b55340:	lea    0xa30(%rsp),%rdx
  b55348:	add    $0x28,%rdx
  b5534c:	mov    $0xfd0c0d,%eax
  b55351:	nopl   0x0(%rax)
  b55358:	movzbl (%rax),%ecx
  b5535b:	add    $0x1,%rax
  b5535f:	mov    %ecx,(%rdx)
  b55361:	add    $0x4,%rdx
  b55365:	cmp    %rax,%rbx
  b55368:	jne    b55358 <_ZN14CInventoryMenu12updateLayoutEv+0x1f28>
  b5536a:	cmpq   $0x20,0xa38(%rsp)
  b55373:	movq   $0x5,0xa30(%rsp)
  b5537f:	mov    0x68(%rsp),%rax
  b55384:	jbe    b55392 <_ZN14CInventoryMenu12updateLayoutEv+0x1f62>
  b55386:	mov    0xad8(%rsp),%rax
  b5538e:	add    $0x14,%rax
  b55392:	movl   $0x0,(%rax)
  b55398:	mov    0x40(%rsp),%ebx
  b5539c:	lea    0xa30(%rsp),%rsi
  b553a4:	mov    0x1028(%rbp),%rdi
  b553ab:	lea    (%rbx,%rbx,4),%rax
  b553af:	lea    (%rbx,%rax,2),%rax
  b553b3:	shl    $0x4,%rax
  b553b7:	lea    0x1d08(%r14,%rax,1),%rdx
  b553bf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b553c4:	lea    0xa30(%rsp),%rdi
  b553cc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b553d1:	lea    (%rbx,%rbx,4),%rax
  b553d5:	lea    (%rbx,%rax,2),%rax
  b553d9:	lea    0x980(%rsp),%rbx
  b553e1:	shl    $0x4,%rax
  b553e5:	lea    0x5568(%r14,%rax,1),%rdi
  b553ed:	call   556378 <_ZNK5CEGUI6String15build_utf8_buffEv@plt>
  b553f2:	mov    %rbx,%rdi
  b553f5:	mov    %rax,%rsi
  b553f8:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b553fd:	mov    0x1028(%rbp),%rdi
  b55404:	mov    %rbx,%rsi
  b55407:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  b5540c:	jmp    b5420a <_ZN14CInventoryMenu12updateLayoutEv+0xdda>
  b55411:	mov    0x1028(%rbp),%rax
  b55418:	xor    %esi,%esi
  b5541a:	mov    0xb0(%rax),%rdi
  b55421:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  b55426:	test   %al,%al
  b55428:	je     b53682 <_ZN14CInventoryMenu12updateLayoutEv+0x252>
  b5542e:	cmpl   $0x1,0x3e0(%r13)
  b55436:	jbe    b5599d <_ZN14CInventoryMenu12updateLayoutEv+0x256d>
  b5543c:	lea    0x20e0(%rsp),%r12
  b55444:	mov    $0xd,%esi
  b55449:	movq   $0x20,0x20e8(%rsp)
  b55455:	movq   $0x0,0x20f0(%rsp)
  b55461:	movq   $0x0,0x2100(%rsp)
  b5546d:	mov    %r12,%rdi
  b55470:	movq   $0x0,0x20f8(%rsp)
  b5547c:	movq   $0x0,0x2188(%rsp)
  b55488:	movq   $0x0,0x20e0(%rsp)
  b55494:	movl   $0x0,0x2108(%rsp)
  b5549f:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b554a4:	cmpq   $0x20,0x20e8(%rsp)
  b554ad:	lea    0x28(%r12),%rdx
  b554b2:	jbe    b554bc <_ZN14CInventoryMenu12updateLayoutEv+0x208c>
  b554b4:	mov    0x2188(%rsp),%rdx
  b554bc:	mov    $0xfe60c3,%eax
  b554c1:	nopl   0x0(%rax)
  b554c8:	movzbl (%rax),%ecx
  b554cb:	add    $0x1,%rax
  b554cf:	mov    %ecx,(%rdx)
  b554d1:	add    $0x4,%rdx
  b554d5:	cmp    $0xfe60d0,%rax
  b554db:	jne    b554c8 <_ZN14CInventoryMenu12updateLayoutEv+0x2098>
  b554dd:	cmpq   $0x20,0x20e8(%rsp)
  b554e6:	movq   $0xd,0x20e0(%rsp)
  b554f2:	lea    0x5c(%r12),%rax
  b554f7:	jbe    b55505 <_ZN14CInventoryMenu12updateLayoutEv+0x20d5>
  b554f9:	mov    0x2188(%rsp),%rax
  b55501:	add    $0x34,%rax
  b55505:	movl   $0x0,(%rax)
  b5550b:	mov    0x1cf8(%r14),%rdi
  b55512:	mov    %r12,%rsi
  b55515:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b5551a:	lea    0x2030(%rsp),%r15
  b55522:	mov    %rax,%rsi
  b55525:	mov    %r15,%rdi
  b55528:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b5552d:	lea    0x1f80(%rsp),%rbx
  b55535:	mov    $0x5,%esi
  b5553a:	movq   $0x20,0x1f88(%rsp)
  b55546:	movq   $0x0,0x1f90(%rsp)
  b55552:	movq   $0x0,0x1fa0(%rsp)
  b5555e:	mov    %rbx,%rdi
  b55561:	movq   $0x0,0x1f98(%rsp)
  b5556d:	movq   $0x0,0x2028(%rsp)
  b55579:	movq   $0x0,0x1f80(%rsp)
  b55585:	movl   $0x0,0x1fa8(%rsp)
  b55590:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55595:	cmpq   $0x20,0x1f88(%rsp)
  b5559e:	lea    0x28(%rbx),%rdx
  b555a2:	jbe    b555ac <_ZN14CInventoryMenu12updateLayoutEv+0x217c>
  b555a4:	mov    0x2028(%rsp),%rdx
  b555ac:	mov    $0xfd0c0d,%eax
  b555b1:	nopl   0x0(%rax)
  b555b8:	movzbl (%rax),%ecx
  b555bb:	add    $0x1,%rax
  b555bf:	mov    %ecx,(%rdx)
  b555c1:	add    $0x4,%rdx
  b555c5:	cmp    $0xfd0c12,%rax
  b555cb:	jne    b555b8 <_ZN14CInventoryMenu12updateLayoutEv+0x2188>
  b555cd:	cmpq   $0x20,0x1f88(%rsp)
  b555d6:	movq   $0x5,0x1f80(%rsp)
  b555e2:	lea    0x3c(%rbx),%rax
  b555e6:	jbe    b555f4 <_ZN14CInventoryMenu12updateLayoutEv+0x21c4>
  b555e8:	mov    0x2028(%rsp),%rax
  b555f0:	add    $0x14,%rax
  b555f4:	movl   $0x0,(%rax)
  b555fa:	mov    0x1548(%rbp),%rdi
  b55601:	mov    %r15,%rdx
  b55604:	mov    %rbx,%rsi
  b55607:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5560c:	mov    %rbx,%rdi
  b5560f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55614:	mov    %r15,%rdi
  b55617:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5561c:	mov    %r12,%rdi
  b5561f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55624:	mov    0x1548(%rbp),%rdi
  b5562b:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b55630:	jmp    b537fd <_ZN14CInventoryMenu12updateLayoutEv+0x3cd>
  b55635:	lea    0x2230(%rsp),%rbx
  b5563d:	lea    0x22ed(%rsp),%rdx
  b55645:	mov    $0xfaa820,%esi
  b5564a:	mov    %rbx,%rdi
  b5564d:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b55652:	mov    $0x10,%edi
  b55657:	call   553738 <__cxa_allocate_exception@plt>
  b5565c:	mov    %rbx,%rsi
  b5565f:	mov    %rax,%rdi
  b55662:	mov    %rax,%r12
  b55665:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5566a:	mov    0x2230(%rsp),%rdi
  b55672:	sub    $0x18,%rdi
  b55676:	cmp    $0x1423a20,%rdi
  b5567d:	jne    b567a5 <_ZN14CInventoryMenu12updateLayoutEv+0x3375>
  b55683:	mov    $0x5a6ce0,%edx
  b55688:	mov    $0xfaaa70,%esi
  b5568d:	mov    %r12,%rdi
  b55690:	call   5542b8 <__cxa_throw@plt>
  b55695:	lea    0x13d0(%rsp),%r12
  b5569d:	mov    $0xd,%esi
  b556a2:	movq   $0x20,0x13d8(%rsp)
  b556ae:	movq   $0x0,0x13e0(%rsp)
  b556ba:	movq   $0x0,0x13f0(%rsp)
  b556c6:	mov    %r12,%rdi
  b556c9:	movq   $0x0,0x13e8(%rsp)
  b556d5:	movq   $0x0,0x1478(%rsp)
  b556e1:	movq   $0x0,0x13d0(%rsp)
  b556ed:	movl   $0x0,0x13f8(%rsp)
  b556f8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b556fd:	cmpq   $0x20,0x13d8(%rsp)
  b55706:	lea    0x28(%r12),%rdx
  b5570b:	ja     b55914 <_ZN14CInventoryMenu12updateLayoutEv+0x24e4>
  b55711:	mov    $0xfe60b5,%eax
  b55716:	cs nopw 0x0(%rax,%rax,1)
  b55720:	movzbl (%rax),%ecx
  b55723:	add    $0x1,%rax
  b55727:	mov    %ecx,(%rdx)
  b55729:	add    $0x4,%rdx
  b5572d:	cmp    $0xfe60c2,%rax
  b55733:	jne    b55720 <_ZN14CInventoryMenu12updateLayoutEv+0x22f0>
  b55735:	cmpq   $0x20,0x13d8(%rsp)
  b5573e:	movq   $0xd,0x13d0(%rsp)
  b5574a:	lea    0x5c(%r12),%rax
  b5574f:	ja     b5593b <_ZN14CInventoryMenu12updateLayoutEv+0x250b>
  b55755:	movl   $0x0,(%rax)
  b5575b:	mov    0x1cf8(%r14),%rdi
  b55762:	mov    %r12,%rsi
  b55765:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b5576a:	lea    0x1320(%rsp),%r13
  b55772:	mov    %rax,%rsi
  b55775:	mov    %r13,%rdi
  b55778:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b5577d:	lea    0x1270(%rsp),%rbx
  b55785:	mov    $0x5,%esi
  b5578a:	movq   $0x20,0x1278(%rsp)
  b55796:	movq   $0x0,0x1280(%rsp)
  b557a2:	movq   $0x0,0x1290(%rsp)
  b557ae:	mov    %rbx,%rdi
  b557b1:	movq   $0x0,0x1288(%rsp)
  b557bd:	movq   $0x0,0x1318(%rsp)
  b557c9:	movq   $0x0,0x1270(%rsp)
  b557d5:	movl   $0x0,0x1298(%rsp)
  b557e0:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b557e5:	cmpq   $0x20,0x1278(%rsp)
  b557ee:	lea    0x28(%rbx),%rdx
  b557f2:	ja     b55907 <_ZN14CInventoryMenu12updateLayoutEv+0x24d7>
  b557f8:	mov    $0xfd0c0d,%eax
  b557fd:	nopl   (%rax)
  b55800:	movzbl (%rax),%ecx
  b55803:	add    $0x1,%rax
  b55807:	mov    %ecx,(%rdx)
  b55809:	add    $0x4,%rdx
  b5580d:	cmp    $0xfd0c12,%rax
  b55813:	jne    b55800 <_ZN14CInventoryMenu12updateLayoutEv+0x23d0>
  b55815:	cmpq   $0x20,0x1278(%rsp)
  b5581e:	movq   $0x5,0x1270(%rsp)
  b5582a:	lea    0x3c(%rbx),%rax
  b5582e:	ja     b5594c <_ZN14CInventoryMenu12updateLayoutEv+0x251c>
  b55834:	movl   $0x0,(%rax)
  b5583a:	mov    0x12b8(%rbp),%rdi
  b55841:	mov    %r13,%rdx
  b55844:	mov    %rbx,%rsi
  b55847:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5584c:	mov    %rbx,%rdi
  b5584f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55854:	mov    %r13,%rdi
  b55857:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5585c:	jmp    b53e54 <_ZN14CInventoryMenu12updateLayoutEv+0xa24>
  b55861:	lea    0x2220(%rsp),%rbx
  b55869:	lea    0x22eb(%rsp),%rdx
  b55871:	mov    $0xfaa820,%esi
  b55876:	mov    %rbx,%rdi
  b55879:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5587e:	mov    $0x10,%edi
  b55883:	call   553738 <__cxa_allocate_exception@plt>
  b55888:	mov    %rbx,%rsi
  b5588b:	mov    %rax,%rdi
  b5588e:	mov    %rax,%r12
  b55891:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b55896:	mov    0x2220(%rsp),%rdi
  b5589e:	sub    $0x18,%rdi
  b558a2:	cmp    $0x1423a20,%rdi
  b558a9:	je     b55683 <_ZN14CInventoryMenu12updateLayoutEv+0x2253>
  b558af:	mov    $0x5541c8,%eax
  b558b4:	test   %rax,%rax
  b558b7:	je     b56905 <_ZN14CInventoryMenu12updateLayoutEv+0x34d5>
  b558bd:	or     $0xffffffff,%eax
  b558c0:	lock xadd %eax,0x10(%rdi)
  b558c5:	test   %eax,%eax
  b558c7:	jg     b55683 <_ZN14CInventoryMenu12updateLayoutEv+0x2253>
  b558cd:	lea    0x22ea(%rsp),%rsi
  b558d5:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b558da:	jmp    b55683 <_ZN14CInventoryMenu12updateLayoutEv+0x2253>
  b558df:	nop
  b558e0:	mov    0x1cb8(%rsp),%rax
  b558e8:	jmp    b53706 <_ZN14CInventoryMenu12updateLayoutEv+0x2d6>
  b558ed:	mov    0xd98(%rsp),%rdx
  b558f5:	jmp    b5507b <_ZN14CInventoryMenu12updateLayoutEv+0x1c4b>
  b558fa:	mov    0xef8(%rsp),%rdx
  b55902:	jmp    b54efd <_ZN14CInventoryMenu12updateLayoutEv+0x1acd>
  b55907:	mov    0x1318(%rsp),%rdx
  b5590f:	jmp    b557f8 <_ZN14CInventoryMenu12updateLayoutEv+0x23c8>
  b55914:	mov    0x1478(%rsp),%rdx
  b5591c:	jmp    b55711 <_ZN14CInventoryMenu12updateLayoutEv+0x22e1>
  b55921:	mov    0x1528(%rsp),%rdx
  b55929:	jmp    b54a08 <_ZN14CInventoryMenu12updateLayoutEv+0x15d8>
  b5592e:	mov    0x1688(%rsp),%rdx
  b55936:	jmp    b54926 <_ZN14CInventoryMenu12updateLayoutEv+0x14f6>
  b5593b:	mov    0x1478(%rsp),%rax
  b55943:	add    $0x34,%rax
  b55947:	jmp    b55755 <_ZN14CInventoryMenu12updateLayoutEv+0x2325>
  b5594c:	mov    0x1318(%rsp),%rax
  b55954:	add    $0x14,%rax
  b55958:	jmp    b55834 <_ZN14CInventoryMenu12updateLayoutEv+0x2404>
  b5595d:	mov    0x1688(%rsp),%rax
  b55965:	add    $0x30,%rax
  b55969:	jmp    b54965 <_ZN14CInventoryMenu12updateLayoutEv+0x1535>
  b5596e:	mov    0x1528(%rsp),%rax
  b55976:	add    $0x14,%rax
  b5597a:	jmp    b54a44 <_ZN14CInventoryMenu12updateLayoutEv+0x1614>
  b5597f:	mov    0xe48(%rsp),%rax
  b55987:	jmp    b54e7b <_ZN14CInventoryMenu12updateLayoutEv+0x1a4b>
  b5598c:	mov    0xef8(%rsp),%rax
  b55994:	add    $0x14,%rax
  b55998:	jmp    b54f45 <_ZN14CInventoryMenu12updateLayoutEv+0x1b15>
  b5599d:	jne    b55624 <_ZN14CInventoryMenu12updateLayoutEv+0x21f4>
  b559a3:	lea    0x1ed0(%rsp),%r12
  b559ab:	mov    $0xd,%esi
  b559b0:	movq   $0x20,0x1ed8(%rsp)
  b559bc:	movq   $0x0,0x1ee0(%rsp)
  b559c8:	movq   $0x0,0x1ef0(%rsp)
  b559d4:	mov    %r12,%rdi
  b559d7:	movq   $0x0,0x1ee8(%rsp)
  b559e3:	movq   $0x0,0x1f78(%rsp)
  b559ef:	movq   $0x0,0x1ed0(%rsp)
  b559fb:	movl   $0x0,0x1ef8(%rsp)
  b55a06:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55a0b:	cmpq   $0x20,0x1ed8(%rsp)
  b55a14:	lea    0x28(%r12),%rdx
  b55a19:	jbe    b55a23 <_ZN14CInventoryMenu12updateLayoutEv+0x25f3>
  b55a1b:	mov    0x1f78(%rsp),%rdx
  b55a23:	mov    $0xfe60d1,%eax
  b55a28:	nopl   0x0(%rax,%rax,1)
  b55a30:	movzbl (%rax),%ecx
  b55a33:	add    $0x1,%rax
  b55a37:	mov    %ecx,(%rdx)
  b55a39:	add    $0x4,%rdx
  b55a3d:	cmp    $0xfe60de,%rax
  b55a43:	jne    b55a30 <_ZN14CInventoryMenu12updateLayoutEv+0x2600>
  b55a45:	cmpq   $0x20,0x1ed8(%rsp)
  b55a4e:	movq   $0xd,0x1ed0(%rsp)
  b55a5a:	lea    0x5c(%r12),%rax
  b55a5f:	jbe    b55a6d <_ZN14CInventoryMenu12updateLayoutEv+0x263d>
  b55a61:	mov    0x1f78(%rsp),%rax
  b55a69:	add    $0x34,%rax
  b55a6d:	movl   $0x0,(%rax)
  b55a73:	mov    0x1cf8(%r14),%rdi
  b55a7a:	mov    %r12,%rsi
  b55a7d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b55a82:	lea    0x1e20(%rsp),%r15
  b55a8a:	mov    %rax,%rsi
  b55a8d:	mov    %r15,%rdi
  b55a90:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b55a95:	lea    0x1d70(%rsp),%rbx
  b55a9d:	mov    $0x5,%esi
  b55aa2:	movq   $0x20,0x1d78(%rsp)
  b55aae:	movq   $0x0,0x1d80(%rsp)
  b55aba:	movq   $0x0,0x1d90(%rsp)
  b55ac6:	mov    %rbx,%rdi
  b55ac9:	movq   $0x0,0x1d88(%rsp)
  b55ad5:	movq   $0x0,0x1e18(%rsp)
  b55ae1:	movq   $0x0,0x1d70(%rsp)
  b55aed:	movl   $0x0,0x1d98(%rsp)
  b55af8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55afd:	cmpq   $0x20,0x1d78(%rsp)
  b55b06:	lea    0x28(%rbx),%rdx
  b55b0a:	jbe    b55b14 <_ZN14CInventoryMenu12updateLayoutEv+0x26e4>
  b55b0c:	mov    0x1e18(%rsp),%rdx
  b55b14:	mov    $0xfd0c0d,%eax
  b55b19:	nopl   0x0(%rax)
  b55b20:	movzbl (%rax),%ecx
  b55b23:	add    $0x1,%rax
  b55b27:	mov    %ecx,(%rdx)
  b55b29:	add    $0x4,%rdx
  b55b2d:	cmp    $0xfd0c12,%rax
  b55b33:	jne    b55b20 <_ZN14CInventoryMenu12updateLayoutEv+0x26f0>
  b55b35:	cmpq   $0x20,0x1d78(%rsp)
  b55b3e:	movq   $0x5,0x1d70(%rsp)
  b55b4a:	lea    0x3c(%rbx),%rax
  b55b4e:	jbe    b55b5c <_ZN14CInventoryMenu12updateLayoutEv+0x272c>
  b55b50:	mov    0x1e18(%rsp),%rax
  b55b58:	add    $0x14,%rax
  b55b5c:	movl   $0x0,(%rax)
  b55b62:	mov    0x1548(%rbp),%rdi
  b55b69:	mov    %r15,%rdx
  b55b6c:	mov    %rbx,%rsi
  b55b6f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b55b74:	mov    %rbx,%rdi
  b55b77:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55b7c:	mov    %r15,%rdi
  b55b7f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55b84:	jmp    b5561c <_ZN14CInventoryMenu12updateLayoutEv+0x21ec>
  b55b89:	mov    0x70(%r14),%rsi
  b55b8d:	mov    %r13,%rdi
  b55b90:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  b55b95:	mov    0x2c8(%r13),%rax
  b55b9c:	test   %rax,%rax
  b55b9f:	mov    %rax,0x38(%rsp)
  b55ba4:	je     b535c8 <_ZN14CInventoryMenu12updateLayoutEv+0x198>
  b55baa:	mov    %rax,%rdi
  b55bad:	mov    $0x1,%esi
  b55bb2:	add    $0x38,%rdi
  b55bb6:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b55bbb:	mov    0x38(%rsp),%rdx
  b55bc0:	movb   $0x1,0x3e2(%rdx)
  b55bc7:	jmp    b5359e <_ZN14CInventoryMenu12updateLayoutEv+0x16e>
  b55bcc:	mov    0xad8(%rsp),%rdx
  b55bd4:	jmp    b5534c <_ZN14CInventoryMenu12updateLayoutEv+0x1f1c>
  b55bd9:	mov    0xc38(%rsp),%rdx
  b55be1:	jmp    b5522a <_ZN14CInventoryMenu12updateLayoutEv+0x1dfa>
  b55be6:	lea    0x140(%rsp),%r15
  b55bee:	lea    0x9100(%r14),%rdx
  b55bf5:	lea    0x350(%rsp),%r13
  b55bfd:	xor    %ebx,%ebx
  b55bff:	lea    0x3c(%r15),%rax
  b55c03:	mov    %rdx,0x28(%rsp)
  b55c08:	lea    0x90(%rsp),%rdx
  b55c10:	mov    %rax,0x30(%rsp)
  b55c15:	lea    0x3c(%r13),%rax
  b55c19:	add    $0x28,%rdx
  b55c1d:	mov    %rdx,0x38(%rsp)
  b55c22:	mov    %rax,0x40(%rsp)
  b55c27:	mov    0x60(%rsp),%rdx
  b55c2c:	cmpq   $0x0,0x8dc8(%rdx)
  b55c34:	je     b55f8b <_ZN14CInventoryMenu12updateLayoutEv+0x2b5b>
  b55c3a:	cmpb   $0x0,0x97170f(%rip)        # 14c7350 <_ZGVZN14CInventoryMenu12updateLayoutEvE14g_RemoveASpell>
  b55c41:	je     b56368 <_ZN14CInventoryMenu12updateLayoutEv+0x2f38>
  b55c47:	mov    0x97172a(%rip),%rax        # 14c7378 <_ZZN14CInventoryMenu12updateLayoutEvE14g_RemoveASpell>
  b55c4e:	cmpq   $0x0,-0x18(%rax)
  b55c53:	je     b562f9 <_ZN14CInventoryMenu12updateLayoutEv+0x2ec9>
  b55c59:	cmpb   $0x0,0x9716f8(%rip)        # 14c7358 <_ZGVZN14CInventoryMenu12updateLayoutEvE15g_RemoveASpell2>
  b55c60:	je     b562b9 <_ZN14CInventoryMenu12updateLayoutEv+0x2e89>
  b55c66:	mov    0x971703(%rip),%rax        # 14c7370 <_ZZN14CInventoryMenu12updateLayoutEvE15g_RemoveASpell2>
  b55c6d:	cmpq   $0x0,-0x18(%rax)
  b55c72:	je     b56246 <_ZN14CInventoryMenu12updateLayoutEv+0x2e16>
  b55c78:	cmpb   $0x0,0x9716e1(%rip)        # 14c7360 <_ZGVZN14CInventoryMenu12updateLayoutEvE12g_DragASpell>
  b55c7f:	je     b56206 <_ZN14CInventoryMenu12updateLayoutEv+0x2dd6>
  b55c85:	mov    0x9716dc(%rip),%rax        # 14c7368 <_ZZN14CInventoryMenu12updateLayoutEvE12g_DragASpell>
  b55c8c:	cmpq   $0x0,-0x18(%rax)
  b55c91:	jne    b55cd6 <_ZN14CInventoryMenu12updateLayoutEv+0x28a6>
  b55c93:	lea    0x22b0(%rsp),%r12
  b55c9b:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  b55ca0:	mov    %r12,%rdi
  b55ca3:	mov    %rax,%rsi
  b55ca6:	mov    $0xfef910,%edx
  b55cab:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  b55cb0:	mov    %r12,%rsi
  b55cb3:	mov    $0x14c7368,%edi
  b55cb8:	call   556038 <_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_@plt>
  b55cbd:	mov    0x22b0(%rsp),%rdi
  b55cc5:	sub    $0x18,%rdi
  b55cc9:	cmp    $0x1424540,%rdi
  b55cd0:	jne    b56480 <_ZN14CInventoryMenu12updateLayoutEv+0x3050>
  b55cd6:	mov    0x50(%r14),%rdi
  b55cda:	mov    %ebx,%esi
  b55cdc:	call   80f800 <_ZN10CCharacter13getKnownSpellEj>
  b55ce1:	test   %rax,%rax
  b55ce4:	mov    %rax,%r12
  b55ce7:	je     b55fcf <_ZN14CInventoryMenu12updateLayoutEv+0x2b9f>
  b55ced:	mov    %rax,%rdi
  b55cf0:	call   c9ce10 <_ZN6CSkill12getSkillIconEv>
  b55cf5:	mov    (%rax),%rax
  b55cf8:	cmpq   $0x0,-0x18(%rax)
  b55cfd:	je     b55fcf <_ZN14CInventoryMenu12updateLayoutEv+0x2b9f>
  b55d03:	mov    %r12,%rdi
  b55d06:	call   c9ce10 <_ZN6CSkill12getSkillIconEv>
  b55d0b:	mov    (%rax),%rsi
  b55d0e:	lea    0x22a0(%rsp),%rdi
  b55d16:	call   c8e350 <_ZN7STRINGS21StringConvertToNarrowEPKw>
  b55d1b:	mov    0x70(%r14),%rdi
  b55d1f:	mov    0x22a0(%rsp),%rsi
  b55d27:	call   a98630 <_ZN7CGameUI20getImageFromImageSetEPKh>
  b55d2c:	lea    0x400(%rsp),%rdi
  b55d34:	mov    %rax,%rsi
  b55d37:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b55d3c:	mov    $0x5,%esi
  b55d41:	mov    %r13,%rdi
  b55d44:	movq   $0x20,0x358(%rsp)
  b55d50:	movq   $0x0,0x360(%rsp)
  b55d5c:	movq   $0x0,0x370(%rsp)
  b55d68:	movq   $0x0,0x368(%rsp)
  b55d74:	movq   $0x0,0x3f8(%rsp)
  b55d80:	movq   $0x0,0x350(%rsp)
  b55d8c:	movl   $0x0,0x378(%rsp)
  b55d97:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b55d9c:	cmpq   $0x20,0x358(%rsp)
  b55da5:	lea    0x28(%r13),%rdx
  b55da9:	jbe    b55db3 <_ZN14CInventoryMenu12updateLayoutEv+0x2983>
  b55dab:	mov    0x3f8(%rsp),%rdx
  b55db3:	mov    $0xfd0c0d,%eax
  b55db8:	nopl   0x0(%rax,%rax,1)
  b55dc0:	movzbl (%rax),%ecx
  b55dc3:	add    $0x1,%rax
  b55dc7:	mov    %ecx,(%rdx)
  b55dc9:	add    $0x4,%rdx
  b55dcd:	cmp    %rax,%rbp
  b55dd0:	jne    b55dc0 <_ZN14CInventoryMenu12updateLayoutEv+0x2990>
  b55dd2:	cmpq   $0x20,0x358(%rsp)
  b55ddb:	movq   $0x5,0x350(%rsp)
  b55de7:	mov    0x40(%rsp),%rax
  b55dec:	jbe    b55dfa <_ZN14CInventoryMenu12updateLayoutEv+0x29ca>
  b55dee:	mov    0x3f8(%rsp),%rax
  b55df6:	add    $0x14,%rax
  b55dfa:	movl   $0x0,(%rax)
  b55e00:	mov    0x60(%rsp),%rax
  b55e05:	lea    0x400(%rsp),%rdx
  b55e0d:	mov    %r13,%rsi
  b55e10:	mov    0x8dc8(%rax),%rdi
  b55e17:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b55e1c:	mov    %r13,%rdi
  b55e1f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55e24:	lea    0x400(%rsp),%rdi
  b55e2c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55e31:	mov    0x22a0(%rsp),%rdi
  b55e39:	sub    $0x18,%rdi
  b55e3d:	cmp    $0x1423a20,%rdi
  b55e44:	jne    b566d8 <_ZN14CInventoryMenu12updateLayoutEv+0x32a8>
  b55e4a:	mov    0x150(%r12),%rax
  b55e52:	mov    0x60(%rsp),%rdx
  b55e57:	lea    0x2290(%rsp),%r12
  b55e5f:	mov    $0x14c7378,%esi
  b55e64:	mov    %r12,%rdi
  b55e67:	mov    %rax,0x8de8(%rdx)
  b55e6e:	mov    0x60(%rsp),%rax
  b55e73:	mov    0x8dc8(%rax),%rdx
  b55e7a:	mov    %ebx,%eax
  b55e7c:	lea    0x8de8(%r14,%rax,8),%rax
  b55e84:	mov    %rax,0x1d8(%rdx)
  b55e8b:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  b55e90:	mov    $0xfd0b48,%edi
  b55e95:	call   554608 <wcslen@plt>
  b55e9a:	mov    $0xfd0b48,%esi
  b55e9f:	mov    %rax,%rdx
  b55ea2:	mov    %r12,%rdi
  b55ea5:	call   553bc8 <_ZNSbIwSt11char_traitsIwESaIwEE6appendEPKwm@plt>
  b55eaa:	lea    0x2280(%rsp),%rdi
  b55eb2:	mov    $0x14c7370,%edx
  b55eb7:	mov    %r12,%rsi
  b55eba:	call   7017d0 <_ZStplIwSt11char_traitsIwESaIwEESbIT_T0_T1_ERKS6_S8_>
  b55ebf:	mov    0x2280(%rsp),%rsi
  b55ec7:	lea    0x22ef(%rsp),%rdx
  b55ecf:	lea    0x2270(%rsp),%rdi
  b55ed7:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  b55edc:	lea    0x2270(%rsp),%rsi
  b55ee4:	lea    0x2260(%rsp),%rdi
  b55eec:	call   c8dc90 <_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE>
  b55ef1:	mov    0x2260(%rsp),%rsi
  b55ef9:	lea    0x2a0(%rsp),%rdi
  b55f01:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b55f06:	mov    0x60(%rsp),%rdx
  b55f0b:	lea    0x2a0(%rsp),%rsi
  b55f13:	mov    0x8dc8(%rdx),%rdi
  b55f1a:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  b55f1f:	lea    0x2a0(%rsp),%rdi
  b55f27:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b55f2c:	mov    0x2260(%rsp),%rdi
  b55f34:	mov    $0x1423a20,%eax
  b55f39:	sub    $0x18,%rdi
  b55f3d:	cmp    %rdi,%rax
  b55f40:	jne    b56634 <_ZN14CInventoryMenu12updateLayoutEv+0x3204>
  b55f46:	mov    0x2270(%rsp),%rdi
  b55f4e:	mov    $0x1424540,%r12d
  b55f54:	sub    $0x18,%rdi
  b55f58:	cmp    %r12,%rdi
  b55f5b:	jne    b565f2 <_ZN14CInventoryMenu12updateLayoutEv+0x31c2>
  b55f61:	mov    0x2280(%rsp),%rdi
  b55f69:	sub    $0x18,%rdi
  b55f6d:	cmp    %rdi,%r12
  b55f70:	jne    b565c6 <_ZN14CInventoryMenu12updateLayoutEv+0x3196>
  b55f76:	mov    0x2290(%rsp),%rdi
  b55f7e:	sub    $0x18,%rdi
  b55f82:	cmp    %rdi,%r12
  b55f85:	jne    b563e1 <_ZN14CInventoryMenu12updateLayoutEv+0x2fb1>
  b55f8b:	add    $0x1,%ebx
  b55f8e:	addq   $0x8,0x60(%rsp)
  b55f94:	cmp    $0x4,%ebx
  b55f97:	jne    b55c27 <_ZN14CInventoryMenu12updateLayoutEv+0x27f7>
  b55f9d:	mov    0x20(%r14),%rdi
  b55fa1:	call   553a38 <_ZN5CEGUI6Window10moveToBackEv@plt>
  b55fa6:	mov    0x48(%r14),%rdi
  b55faa:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b55faf:	mov    0x28(%r14),%rdi
  b55fb3:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b55fb8:	mov    0x30(%r14),%rdi
  b55fbc:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b55fc1:	mov    0x38(%r14),%rdi
  b55fc5:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b55fca:	jmp    b53464 <_ZN14CInventoryMenu12updateLayoutEv+0x34>
  b55fcf:	mov    0x971392(%rip),%rsi        # 14c7368 <_ZZN14CInventoryMenu12updateLayoutEvE12g_DragASpell>
  b55fd6:	lea    0x22ee(%rsp),%rdx
  b55fde:	lea    0x2250(%rsp),%rdi
  b55fe6:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  b55feb:	lea    0x2250(%rsp),%rsi
  b55ff3:	lea    0x2240(%rsp),%rdi
  b55ffb:	call   c8dc90 <_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE>
  b56000:	mov    0x2240(%rsp),%rsi
  b56008:	lea    0x1f0(%rsp),%rdi
  b56010:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b56015:	mov    0x60(%rsp),%rax
  b5601a:	lea    0x1f0(%rsp),%rsi
  b56022:	mov    0x8dc8(%rax),%rdi
  b56029:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  b5602e:	lea    0x1f0(%rsp),%rdi
  b56036:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5603b:	mov    0x2240(%rsp),%rdi
  b56043:	sub    $0x18,%rdi
  b56047:	cmp    $0x1423a20,%rdi
  b5604e:	jne    b564fb <_ZN14CInventoryMenu12updateLayoutEv+0x30cb>
  b56054:	mov    0x2250(%rsp),%rdi
  b5605c:	sub    $0x18,%rdi
  b56060:	cmp    $0x1424540,%rdi
  b56067:	jne    b56544 <_ZN14CInventoryMenu12updateLayoutEv+0x3114>
  b5606d:	lea    0x90(%rsp),%rdi
  b56075:	xor    %esi,%esi
  b56077:	movq   $0x20,0x98(%rsp)
  b56083:	movq   $0x0,0xa0(%rsp)
  b5608f:	movq   $0x0,0xb0(%rsp)
  b5609b:	movq   $0x0,0xa8(%rsp)
  b560a7:	movq   $0x0,0x138(%rsp)
  b560b3:	movq   $0x0,0x90(%rsp)
  b560bf:	movl   $0x0,0xb8(%rsp)
  b560ca:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b560cf:	cmpq   $0x21,0x98(%rsp)
  b560d8:	mov    0x38(%rsp),%rax
  b560dd:	mov    $0x5,%esi
  b560e2:	cmovae 0x138(%rsp),%rax
  b560eb:	movq   $0x0,0x90(%rsp)
  b560f7:	mov    %r15,%rdi
  b560fa:	movl   $0x0,(%rax)
  b56100:	movq   $0x20,0x148(%rsp)
  b5610c:	movq   $0x0,0x150(%rsp)
  b56118:	movq   $0x0,0x160(%rsp)
  b56124:	movq   $0x0,0x158(%rsp)
  b56130:	movq   $0x0,0x1e8(%rsp)
  b5613c:	movq   $0x0,0x140(%rsp)
  b56148:	movl   $0x0,0x168(%rsp)
  b56153:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b56158:	cmpq   $0x20,0x148(%rsp)
  b56161:	lea    0x28(%r15),%rdx
  b56165:	jbe    b5616f <_ZN14CInventoryMenu12updateLayoutEv+0x2d3f>
  b56167:	mov    0x1e8(%rsp),%rdx
  b5616f:	mov    $0xfd0c0d,%eax
  b56174:	nopl   0x0(%rax)
  b56178:	movzbl (%rax),%ecx
  b5617b:	add    $0x1,%rax
  b5617f:	mov    %ecx,(%rdx)
  b56181:	add    $0x4,%rdx
  b56185:	cmp    %rax,%rbp
  b56188:	jne    b56178 <_ZN14CInventoryMenu12updateLayoutEv+0x2d48>
  b5618a:	cmpq   $0x20,0x148(%rsp)
  b56193:	movq   $0x5,0x140(%rsp)
  b5619f:	mov    0x30(%rsp),%rax
  b561a4:	jbe    b561b2 <_ZN14CInventoryMenu12updateLayoutEv+0x2d82>
  b561a6:	mov    0x1e8(%rsp),%rax
  b561ae:	add    $0x14,%rax
  b561b2:	movl   $0x0,(%rax)
  b561b8:	mov    0x60(%rsp),%rdx
  b561bd:	mov    %r15,%rsi
  b561c0:	mov    0x8dc8(%rdx),%rdi
  b561c7:	lea    0x90(%rsp),%rdx
  b561cf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b561d4:	mov    %r15,%rdi
  b561d7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b561dc:	lea    0x90(%rsp),%rdi
  b561e4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b561e9:	mov    0x60(%rsp),%rdx
  b561ee:	mov    0x8dc8(%rdx),%rax
  b561f5:	mov    0x28(%rsp),%rdx
  b561fa:	mov    %rdx,0x1d8(%rax)
  b56201:	jmp    b55f8b <_ZN14CInventoryMenu12updateLayoutEv+0x2b5b>
  b56206:	mov    $0x14c7360,%edi
  b5620b:	call   553558 <__cxa_guard_acquire@plt>
  b56210:	test   %eax,%eax
  b56212:	je     b55c85 <_ZN14CInventoryMenu12updateLayoutEv+0x2855>
  b56218:	mov    $0x14c7360,%edi
  b5621d:	movq   $0x1424558,0x971140(%rip)        # 14c7368 <_ZZN14CInventoryMenu12updateLayoutEvE12g_DragASpell>
  b56228:	call   553fc8 <__cxa_guard_release@plt>
  b5622d:	mov    $0xf9f788,%edx
  b56232:	mov    $0x14c7368,%esi
  b56237:	mov    $0x5548d8,%edi
  b5623c:	call   5551e8 <__cxa_atexit@plt>
  b56241:	jmp    b55c85 <_ZN14CInventoryMenu12updateLayoutEv+0x2855>
  b56246:	lea    0x22c0(%rsp),%r12
  b5624e:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  b56253:	mov    %r12,%rdi
  b56256:	mov    %rax,%rsi
  b56259:	mov    $0xfef8c0,%edx
  b5625e:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  b56263:	mov    %r12,%rsi
  b56266:	mov    $0x14c7370,%edi
  b5626b:	call   556038 <_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_@plt>
  b56270:	mov    0x22c0(%rsp),%rdi
  b56278:	sub    $0x18,%rdi
  b5627c:	cmp    $0x1424540,%rdi
  b56283:	je     b55c78 <_ZN14CInventoryMenu12updateLayoutEv+0x2848>
  b56289:	mov    $0x5541c8,%eax
  b5628e:	test   %rax,%rax
  b56291:	je     b56589 <_ZN14CInventoryMenu12updateLayoutEv+0x3159>
  b56297:	or     $0xffffffff,%eax
  b5629a:	lock xadd %eax,0x10(%rdi)
  b5629f:	test   %eax,%eax
  b562a1:	jg     b55c78 <_ZN14CInventoryMenu12updateLayoutEv+0x2848>
  b562a7:	lea    0x22e8(%rsp),%rsi
  b562af:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b562b4:	jmp    b55c78 <_ZN14CInventoryMenu12updateLayoutEv+0x2848>
  b562b9:	mov    $0x14c7358,%edi
  b562be:	call   553558 <__cxa_guard_acquire@plt>
  b562c3:	test   %eax,%eax
  b562c5:	je     b55c66 <_ZN14CInventoryMenu12updateLayoutEv+0x2836>
  b562cb:	mov    $0x14c7358,%edi
  b562d0:	movq   $0x1424558,0x971095(%rip)        # 14c7370 <_ZZN14CInventoryMenu12updateLayoutEvE15g_RemoveASpell2>
  b562db:	call   553fc8 <__cxa_guard_release@plt>
  b562e0:	mov    $0xf9f788,%edx
  b562e5:	mov    $0x14c7370,%esi
  b562ea:	mov    $0x5548d8,%edi
  b562ef:	call   5551e8 <__cxa_atexit@plt>
  b562f4:	jmp    b55c66 <_ZN14CInventoryMenu12updateLayoutEv+0x2836>
  b562f9:	lea    0x22d0(%rsp),%r12
  b56301:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  b56306:	mov    %r12,%rdi
  b56309:	mov    %rax,%rsi
  b5630c:	mov    $0xfef848,%edx
  b56311:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  b56316:	mov    %r12,%rsi
  b56319:	mov    $0x14c7378,%edi
  b5631e:	call   556038 <_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_@plt>
  b56323:	mov    0x22d0(%rsp),%rdi
  b5632b:	sub    $0x18,%rdi
  b5632f:	cmp    $0x1424540,%rdi
  b56336:	je     b55c59 <_ZN14CInventoryMenu12updateLayoutEv+0x2829>
  b5633c:	mov    $0x5541c8,%eax
  b56341:	test   %rax,%rax
  b56344:	je     b563a8 <_ZN14CInventoryMenu12updateLayoutEv+0x2f78>
  b56346:	or     $0xffffffff,%eax
  b56349:	lock xadd %eax,0x10(%rdi)
  b5634e:	test   %eax,%eax
  b56350:	jg     b55c59 <_ZN14CInventoryMenu12updateLayoutEv+0x2829>
  b56356:	lea    0x22e9(%rsp),%rsi
  b5635e:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b56363:	jmp    b55c59 <_ZN14CInventoryMenu12updateLayoutEv+0x2829>
  b56368:	mov    $0x14c7350,%edi
  b5636d:	call   553558 <__cxa_guard_acquire@plt>
  b56372:	test   %eax,%eax
  b56374:	je     b55c47 <_ZN14CInventoryMenu12updateLayoutEv+0x2817>
  b5637a:	mov    $0x14c7350,%edi
  b5637f:	movq   $0x1424558,0x970fee(%rip)        # 14c7378 <_ZZN14CInventoryMenu12updateLayoutEvE14g_RemoveASpell>
  b5638a:	call   553fc8 <__cxa_guard_release@plt>
  b5638f:	mov    $0xf9f788,%edx
  b56394:	mov    $0x14c7378,%esi
  b56399:	mov    $0x5548d8,%edi
  b5639e:	call   5551e8 <__cxa_atexit@plt>
  b563a3:	jmp    b55c47 <_ZN14CInventoryMenu12updateLayoutEv+0x2817>
  b563a8:	mov    0x10(%rdi),%eax
  b563ab:	lea    -0x1(%rax),%edx
  b563ae:	mov    %edx,0x10(%rdi)
  b563b1:	jmp    b5634e <_ZN14CInventoryMenu12updateLayoutEv+0x2f1e>
  b563b3:	mov    %rax,%rbp
  b563b6:	mov    %r12,%rdi
  b563b9:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b563be:	mov    %rbp,%rdi
  b563c1:	call   554498 <_Unwind_Resume@plt>
  b563c6:	mov    %rax,%rbp
  b563c9:	mov    %r15,%rdi
  b563cc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b563d1:	mov    %r12,%rdi
  b563d4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b563d9:	mov    %rbp,%rdi
  b563dc:	call   554498 <_Unwind_Resume@plt>
  b563e1:	mov    $0x5541c8,%eax
  b563e6:	test   %rax,%rax
  b563e9:	je     b56570 <_ZN14CInventoryMenu12updateLayoutEv+0x3140>
  b563ef:	or     $0xffffffff,%eax
  b563f2:	lock xadd %eax,0x10(%rdi)
  b563f7:	test   %eax,%eax
  b563f9:	jg     b55f8b <_ZN14CInventoryMenu12updateLayoutEv+0x2b5b>
  b563ff:	lea    0x22e2(%rsp),%rsi
  b56407:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5640c:	jmp    b55f8b <_ZN14CInventoryMenu12updateLayoutEv+0x2b5b>
  b56411:	mov    %rax,%rbp
  b56414:	lea    0x90(%rsp),%rdi
  b5641c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56421:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b56423:	mov    %rax,%rbp
  b56426:	jmp    b563d1 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa1>
  b56428:	mov    %rax,%rbp
  b5642b:	mov    %r12,%rdi
  b5642e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56433:	mov    %rbp,%rdi
  b56436:	call   554498 <_Unwind_Resume@plt>
  b5643b:	mov    %rax,%rbp
  b5643e:	mov    %r13,%rdi
  b56441:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56446:	jmp    b5642b <_ZN14CInventoryMenu12updateLayoutEv+0x2ffb>
  b56448:	mov    %rbx,%rdi
  b5644b:	mov    %rax,%rbp
  b5644e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56453:	jmp    b5643e <_ZN14CInventoryMenu12updateLayoutEv+0x300e>
  b56455:	mov    %rax,%rbp
  b56458:	mov    %rbx,%rdi
  b5645b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56460:	mov    %rbp,%rdi
  b56463:	call   554498 <_Unwind_Resume@plt>
  b56468:	lea    0xa30(%rsp),%rdi
  b56470:	mov    %rax,%rbp
  b56473:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56478:	mov    %rbp,%rdi
  b5647b:	call   554498 <_Unwind_Resume@plt>
  b56480:	mov    $0x5541c8,%eax
  b56485:	test   %rax,%rax
  b56488:	je     b564b1 <_ZN14CInventoryMenu12updateLayoutEv+0x3081>
  b5648a:	or     $0xffffffff,%eax
  b5648d:	lock xadd %eax,0x10(%rdi)
  b56492:	test   %eax,%eax
  b56494:	jg     b55cd6 <_ZN14CInventoryMenu12updateLayoutEv+0x28a6>
  b5649a:	lea    0x22e7(%rsp),%rsi
  b564a2:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b564a7:	jmp    b55cd6 <_ZN14CInventoryMenu12updateLayoutEv+0x28a6>
  b564ac:	jmp    b563b3 <_ZN14CInventoryMenu12updateLayoutEv+0x2f83>
  b564b1:	mov    0x10(%rdi),%eax
  b564b4:	lea    -0x1(%rax),%edx
  b564b7:	mov    %edx,0x10(%rdi)
  b564ba:	jmp    b56492 <_ZN14CInventoryMenu12updateLayoutEv+0x3062>
  b564bc:	mov    %rax,%rbp
  b564bf:	lea    0x2240(%rsp),%rdi
  b564c7:	call   556288 <_ZNSsD1Ev@plt>
  b564cc:	lea    0x2250(%rsp),%rdi
  b564d4:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b564d9:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b564de:	mov    %rax,%rbp
  b564e1:	jmp    b564cc <_ZN14CInventoryMenu12updateLayoutEv+0x309c>
  b564e3:	mov    %rax,%rbp
  b564e6:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b564eb:	mov    %r15,%rdi
  b564ee:	mov    %rax,%rbp
  b564f1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b564f6:	jmp    b56414 <_ZN14CInventoryMenu12updateLayoutEv+0x2fe4>
  b564fb:	mov    $0x5541c8,%eax
  b56500:	test   %rax,%rax
  b56503:	je     b56539 <_ZN14CInventoryMenu12updateLayoutEv+0x3109>
  b56505:	or     $0xffffffff,%eax
  b56508:	lock xadd %eax,0x10(%rdi)
  b5650d:	test   %eax,%eax
  b5650f:	jg     b56054 <_ZN14CInventoryMenu12updateLayoutEv+0x2c24>
  b56515:	lea    0x22e1(%rsp),%rsi
  b5651d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b56522:	jmp    b56054 <_ZN14CInventoryMenu12updateLayoutEv+0x2c24>
  b56527:	lea    0x1f0(%rsp),%rdi
  b5652f:	mov    %rax,%rbp
  b56532:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56537:	jmp    b564bf <_ZN14CInventoryMenu12updateLayoutEv+0x308f>
  b56539:	mov    0x10(%rdi),%eax
  b5653c:	lea    -0x1(%rax),%edx
  b5653f:	mov    %edx,0x10(%rdi)
  b56542:	jmp    b5650d <_ZN14CInventoryMenu12updateLayoutEv+0x30dd>
  b56544:	mov    $0x5541c8,%eax
  b56549:	test   %rax,%rax
  b5654c:	je     b5657e <_ZN14CInventoryMenu12updateLayoutEv+0x314e>
  b5654e:	or     $0xffffffff,%eax
  b56551:	lock xadd %eax,0x10(%rdi)
  b56556:	test   %eax,%eax
  b56558:	jg     b5606d <_ZN14CInventoryMenu12updateLayoutEv+0x2c3d>
  b5655e:	lea    0x22e0(%rsp),%rsi
  b56566:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5656b:	jmp    b5606d <_ZN14CInventoryMenu12updateLayoutEv+0x2c3d>
  b56570:	mov    0x10(%rdi),%eax
  b56573:	lea    -0x1(%rax),%edx
  b56576:	mov    %edx,0x10(%rdi)
  b56579:	jmp    b563f7 <_ZN14CInventoryMenu12updateLayoutEv+0x2fc7>
  b5657e:	mov    0x10(%rdi),%eax
  b56581:	lea    -0x1(%rax),%edx
  b56584:	mov    %edx,0x10(%rdi)
  b56587:	jmp    b56556 <_ZN14CInventoryMenu12updateLayoutEv+0x3126>
  b56589:	mov    0x10(%rdi),%eax
  b5658c:	lea    -0x1(%rax),%edx
  b5658f:	mov    %edx,0x10(%rdi)
  b56592:	jmp    b5629f <_ZN14CInventoryMenu12updateLayoutEv+0x2e6f>
  b56597:	jmp    b563b3 <_ZN14CInventoryMenu12updateLayoutEv+0x2f83>
  b5659c:	mov    %rax,%rbp
  b5659f:	lea    0x400(%rsp),%rdi
  b565a7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b565ac:	lea    0x22a0(%rsp),%rdi
  b565b4:	call   556288 <_ZNSsD1Ev@plt>
  b565b9:	mov    %rbp,%rdi
  b565bc:	call   554498 <_Unwind_Resume@plt>
  b565c1:	mov    %rax,%rbp
  b565c4:	jmp    b565ac <_ZN14CInventoryMenu12updateLayoutEv+0x317c>
  b565c6:	mov    $0x5541c8,%eax
  b565cb:	test   %rax,%rax
  b565ce:	je     b5661e <_ZN14CInventoryMenu12updateLayoutEv+0x31ee>
  b565d0:	or     $0xffffffff,%eax
  b565d3:	lock xadd %eax,0x10(%rdi)
  b565d8:	test   %eax,%eax
  b565da:	jg     b55f76 <_ZN14CInventoryMenu12updateLayoutEv+0x2b46>
  b565e0:	lea    0x22e3(%rsp),%rsi
  b565e8:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b565ed:	jmp    b55f76 <_ZN14CInventoryMenu12updateLayoutEv+0x2b46>
  b565f2:	mov    $0x5541c8,%eax
  b565f7:	test   %rax,%rax
  b565fa:	je     b56629 <_ZN14CInventoryMenu12updateLayoutEv+0x31f9>
  b565fc:	or     $0xffffffff,%eax
  b565ff:	lock xadd %eax,0x10(%rdi)
  b56604:	test   %eax,%eax
  b56606:	jg     b55f61 <_ZN14CInventoryMenu12updateLayoutEv+0x2b31>
  b5660c:	lea    0x22e4(%rsp),%rsi
  b56614:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b56619:	jmp    b55f61 <_ZN14CInventoryMenu12updateLayoutEv+0x2b31>
  b5661e:	mov    0x10(%rdi),%eax
  b56621:	lea    -0x1(%rax),%edx
  b56624:	mov    %edx,0x10(%rdi)
  b56627:	jmp    b565d8 <_ZN14CInventoryMenu12updateLayoutEv+0x31a8>
  b56629:	mov    0x10(%rdi),%eax
  b5662c:	lea    -0x1(%rax),%edx
  b5662f:	mov    %edx,0x10(%rdi)
  b56632:	jmp    b56604 <_ZN14CInventoryMenu12updateLayoutEv+0x31d4>
  b56634:	mov    $0x5541c8,%eax
  b56639:	test   %rax,%rax
  b5663c:	je     b566a4 <_ZN14CInventoryMenu12updateLayoutEv+0x3274>
  b5663e:	or     $0xffffffff,%eax
  b56641:	lock xadd %eax,0x10(%rdi)
  b56646:	test   %eax,%eax
  b56648:	jg     b55f46 <_ZN14CInventoryMenu12updateLayoutEv+0x2b16>
  b5664e:	lea    0x22e5(%rsp),%rsi
  b56656:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5665b:	jmp    b55f46 <_ZN14CInventoryMenu12updateLayoutEv+0x2b16>
  b56660:	lea    0x2a0(%rsp),%rdi
  b56668:	mov    %rax,%rbp
  b5666b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56670:	lea    0x2260(%rsp),%rdi
  b56678:	call   556288 <_ZNSsD1Ev@plt>
  b5667d:	lea    0x2270(%rsp),%rdi
  b56685:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b5668a:	lea    0x2280(%rsp),%rdi
  b56692:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b56697:	mov    %r12,%rdi
  b5669a:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b5669f:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b566a4:	mov    0x10(%rdi),%eax
  b566a7:	lea    -0x1(%rax),%edx
  b566aa:	mov    %edx,0x10(%rdi)
  b566ad:	jmp    b56646 <_ZN14CInventoryMenu12updateLayoutEv+0x3216>
  b566af:	mov    %rax,%rbp
  b566b2:	jmp    b56670 <_ZN14CInventoryMenu12updateLayoutEv+0x3240>
  b566b4:	mov    %rax,%rbp
  b566b7:	jmp    b5667d <_ZN14CInventoryMenu12updateLayoutEv+0x324d>
  b566b9:	mov    %rax,%rbp
  b566bc:	jmp    b5668a <_ZN14CInventoryMenu12updateLayoutEv+0x325a>
  b566be:	mov    %rax,%rbp
  b566c1:	jmp    b56697 <_ZN14CInventoryMenu12updateLayoutEv+0x3267>
  b566c3:	mov    %r12,%rdi
  b566c6:	mov    %rax,%rbp
  b566c9:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b566ce:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b566d3:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b566d8:	mov    $0x5541c8,%eax
  b566dd:	test   %rax,%rax
  b566e0:	je     b56715 <_ZN14CInventoryMenu12updateLayoutEv+0x32e5>
  b566e2:	or     $0xffffffff,%eax
  b566e5:	lock xadd %eax,0x10(%rdi)
  b566ea:	test   %eax,%eax
  b566ec:	jg     b55e4a <_ZN14CInventoryMenu12updateLayoutEv+0x2a1a>
  b566f2:	lea    0x22e6(%rsp),%rsi
  b566fa:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b566ff:	jmp    b55e4a <_ZN14CInventoryMenu12updateLayoutEv+0x2a1a>
  b56704:	mov    %r13,%rdi
  b56707:	mov    %rax,%rbp
  b5670a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5670f:	nop
  b56710:	jmp    b5659f <_ZN14CInventoryMenu12updateLayoutEv+0x316f>
  b56715:	mov    0x10(%rdi),%eax
  b56718:	lea    -0x1(%rax),%edx
  b5671b:	mov    %edx,0x10(%rdi)
  b5671e:	jmp    b566ea <_ZN14CInventoryMenu12updateLayoutEv+0x32ba>
  b56720:	jmp    b56428 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff8>
  b56725:	mov    %rbx,%rdi
  b56728:	mov    %rax,%rbp
  b5672b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56730:	jmp    b5642b <_ZN14CInventoryMenu12updateLayoutEv+0x2ffb>
  b56735:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b5673a:	nopw   0x0(%rax,%rax,1)
  b56740:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b56745:	data16 cs nopw 0x0(%rax,%rax,1)
  b56750:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b56755:	data16 cs nopw 0x0(%rax,%rax,1)
  b56760:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b56765:	mov    %r12,%rdi
  b56768:	mov    %rax,%rbp
  b5676b:	nopl   0x0(%rax,%rax,1)
  b56770:	call   5552b8 <__cxa_free_exception@plt>
  b56775:	mov    %rbx,%rdi
  b56778:	call   556288 <_ZNSsD1Ev@plt>
  b5677d:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b56782:	jmp    b56428 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff8>
  b56787:	cmp    $0xffffffffffffffff,%rdx
  b5678b:	mov    %rax,%rbp
  b5678e:	xchg   %ax,%ax
  b56790:	jne    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b56796:	call   555f88 <_ZSt9terminatev@plt>
  b5679b:	jmp    b56448 <_ZN14CInventoryMenu12updateLayoutEv+0x3018>
  b567a0:	jmp    b5643b <_ZN14CInventoryMenu12updateLayoutEv+0x300b>
  b567a5:	mov    $0x5541c8,%eax
  b567aa:	test   %rax,%rax
  b567ad:	nopl   (%rax)
  b567b0:	je     b567d9 <_ZN14CInventoryMenu12updateLayoutEv+0x33a9>
  b567b2:	or     $0xffffffff,%eax
  b567b5:	lock xadd %eax,0x10(%rdi)
  b567ba:	test   %eax,%eax
  b567bc:	jg     b55683 <_ZN14CInventoryMenu12updateLayoutEv+0x2253>
  b567c2:	lea    0x22ec(%rsp),%rsi
  b567ca:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b567cf:	jmp    b55683 <_ZN14CInventoryMenu12updateLayoutEv+0x2253>
  b567d4:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b567d9:	mov    0x10(%rdi),%eax
  b567dc:	lea    -0x1(%rax),%edx
  b567df:	mov    %edx,0x10(%rdi)
  b567e2:	jmp    b567ba <_ZN14CInventoryMenu12updateLayoutEv+0x338a>
  b567e4:	mov    %r12,%rdi
  b567e7:	mov    %rax,%rbp
  b567ea:	call   5552b8 <__cxa_free_exception@plt>
  b567ef:	mov    %rbx,%rdi
  b567f2:	call   556288 <_ZNSsD1Ev@plt>
  b567f7:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b567fc:	mov    %rax,%rbp
  b567ff:	lea    0x820(%rsp),%rdi
  b56807:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5680c:	mov    %rbp,%rdi
  b5680f:	call   554498 <_Unwind_Resume@plt>
  b56814:	jmp    b56787 <_ZN14CInventoryMenu12updateLayoutEv+0x3357>
  b56819:	mov    %r15,%rdi
  b5681c:	mov    %rax,%rbp
  b5681f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56824:	jmp    b567ff <_ZN14CInventoryMenu12updateLayoutEv+0x33cf>
  b56826:	mov    %rax,%rbp
  b56829:	lea    0x6c0(%rsp),%rdi
  b56831:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56836:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b5683b:	lea    0x770(%rsp),%rdi
  b56843:	mov    %rax,%rbp
  b56846:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5684b:	jmp    b56829 <_ZN14CInventoryMenu12updateLayoutEv+0x33f9>
  b5684d:	mov    %rax,%rbp
  b56850:	lea    0x560(%rsp),%rdi
  b56858:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5685d:	mov    %rbp,%rdi
  b56860:	call   554498 <_Unwind_Resume@plt>
  b56865:	lea    0x610(%rsp),%rdi
  b5686d:	mov    %rax,%rbp
  b56870:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56875:	jmp    b56850 <_ZN14CInventoryMenu12updateLayoutEv+0x3420>
  b56877:	jmp    b56423 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff3>
  b5687c:	mov    %r12,%rdi
  b5687f:	mov    %rax,%rbp
  b56882:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56887:	mov    %r13,%rdi
  b5688a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5688f:	mov    %rbp,%rdi
  b56892:	call   554498 <_Unwind_Resume@plt>
  b56897:	jmp    b563c6 <_ZN14CInventoryMenu12updateLayoutEv+0x2f96>
  b5689c:	mov    %rbx,%rdi
  b5689f:	mov    %rax,%rbp
  b568a2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b568a7:	jmp    b563c9 <_ZN14CInventoryMenu12updateLayoutEv+0x2f99>
  b568ac:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b568b1:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b568b6:	mov    %r12,%rdi
  b568b9:	mov    %rax,%rbp
  b568bc:	nopl   0x0(%rax)
  b568c0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b568c5:	mov    %rbx,%rdi
  b568c8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b568cd:	jmp    b563d9 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa9>
  b568d2:	jmp    b56423 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff3>
  b568d7:	mov    %rax,%rbp
  b568da:	nopw   0x0(%rax,%rax,1)
  b568e0:	jmp    b568c5 <_ZN14CInventoryMenu12updateLayoutEv+0x3495>
  b568e2:	mov    %rax,%rbp
  b568e5:	lea    0xc40(%rsp),%rdi
  b568ed:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b568f2:	mov    %rbp,%rdi
  b568f5:	call   554498 <_Unwind_Resume@plt>
  b568fa:	jmp    b56428 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff8>
  b568ff:	nop
  b56900:	jmp    b56423 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff3>
  b56905:	mov    0x10(%rdi),%eax
  b56908:	lea    -0x1(%rax),%edx
  b5690b:	mov    %edx,0x10(%rdi)
  b5690e:	xchg   %ax,%ax
  b56910:	jmp    b558c5 <_ZN14CInventoryMenu12updateLayoutEv+0x2495>
  b56915:	mov    %rbx,%rdi
  b56918:	mov    %rax,%rbp
  b5691b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56920:	jmp    b563d1 <_ZN14CInventoryMenu12updateLayoutEv+0x2fa1>
  b56925:	jmp    b5643b <_ZN14CInventoryMenu12updateLayoutEv+0x300b>
  b5692a:	mov    %rax,%rbp
  b5692d:	nopl   (%rax)
  b56930:	jmp    b56887 <_ZN14CInventoryMenu12updateLayoutEv+0x3457>
  b56935:	jmp    b56428 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff8>
  b5693a:	nopw   0x0(%rax,%rax,1)
  b56940:	jmp    b568d7 <_ZN14CInventoryMenu12updateLayoutEv+0x34a7>
  b56942:	jmp    b56725 <_ZN14CInventoryMenu12updateLayoutEv+0x32f5>
  b56947:	nopw   0x0(%rax,%rax,1)
  b56950:	jmp    b56448 <_ZN14CInventoryMenu12updateLayoutEv+0x3018>
  b56955:	data16 cs nopw 0x0(%rax,%rax,1)
  b56960:	jmp    b5689c <_ZN14CInventoryMenu12updateLayoutEv+0x346c>
  b56965:	data16 cs nopw 0x0(%rax,%rax,1)
  b56970:	jmp    b564e3 <_ZN14CInventoryMenu12updateLayoutEv+0x30b3>
  b56975:	lea    0xb90(%rsp),%rdi
  b5697d:	mov    %rax,%rbp
  b56980:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56985:	lea    0xae0(%rsp),%rdi
  b5698d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56992:	mov    %rbp,%rdi
  b56995:	call   554498 <_Unwind_Resume@plt>
  b5699a:	mov    %rax,%rbp
  b5699d:	jmp    b56985 <_ZN14CInventoryMenu12updateLayoutEv+0x3555>
  b5699f:	mov    %rax,%rdi
  b569a2:	call   554498 <_Unwind_Resume@plt>
  b569a7:	lea    0xcf0(%rsp),%rdi
  b569af:	mov    %rax,%rbp
  b569b2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b569b7:	jmp    b568e5 <_ZN14CInventoryMenu12updateLayoutEv+0x34b5>
  b569bc:	jmp    b5689c <_ZN14CInventoryMenu12updateLayoutEv+0x346c>
  b569c1:	jmp    b563c6 <_ZN14CInventoryMenu12updateLayoutEv+0x2f96>
  b569c6:	cs nopw 0x0(%rax,%rax,1)
  b569d0:	jmp    b56423 <_ZN14CInventoryMenu12updateLayoutEv+0x2ff3>
  b569d5:	nop
  b569d6:	cs nopw 0x0(%rax,%rax,1)
