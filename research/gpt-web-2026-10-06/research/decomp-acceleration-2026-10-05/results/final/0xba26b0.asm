
/workspace/scratch/3ba0fff8d310/otl-recovery-1518/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000ba26b0 <_ZN8CPetMenu12updateLayoutEv>:
  ba26b0:	push   %r15
  ba26b2:	mov    %rdi,%r15
  ba26b5:	push   %r14
  ba26b7:	push   %r13
  ba26b9:	push   %r12
  ba26bb:	push   %rbp
  ba26bc:	push   %rbx
  ba26bd:	sub    $0x22b8,%rsp
  ba26c4:	mov    0x58(%rdi),%rax
  ba26c8:	test   %rax,%rax
  ba26cb:	je     ba38c8 <_ZN8CPetMenu12updateLayoutEv+0x1218>
  ba26d1:	cmpb   $0x0,0x68(%rdi)
  ba26d5:	je     ba38c8 <_ZN8CPetMenu12updateLayoutEv+0x1218>
  ba26db:	mov    0x490(%rax),%rax
  ba26e2:	test   %rax,%rax
  ba26e5:	mov    %rax,0x50(%rsp)
  ba26ea:	jne    ba2700 <_ZN8CPetMenu12updateLayoutEv+0x50>
  ba26ec:	jmp    ba38c8 <_ZN8CPetMenu12updateLayoutEv+0x1218>
  ba26f1:	nopl   0x0(%rax)
  ba26f8:	mov    (%rdx),%rsi
  ba26fb:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  ba2700:	mov    0x30(%r15),%rdi
  ba2704:	mov    0x78(%rdi),%rdx
  ba2708:	mov    0x80(%rdi),%rax
  ba270f:	sub    %rdx,%rax
  ba2712:	sar    $0x3,%rax
  ba2716:	test   %rax,%rax
  ba2719:	jne    ba26f8 <_ZN8CPetMenu12updateLayoutEv+0x48>
  ba271b:	xor    %ebx,%ebx
  ba271d:	jmp    ba272a <_ZN8CPetMenu12updateLayoutEv+0x7a>
  ba271f:	nop
  ba2720:	add    $0x8,%rbx
  ba2724:	cmp    $0x60,%rbx
  ba2728:	je     ba2760 <_ZN8CPetMenu12updateLayoutEv+0xb0>
  ba272a:	mov    0x1378(%r15,%rbx,1),%rdi
  ba2732:	test   %rdi,%rdi
  ba2735:	je     ba2720 <_ZN8CPetMenu12updateLayoutEv+0x70>
  ba2737:	mov    0x78(%rdi),%rdx
  ba273b:	mov    0x80(%rdi),%rax
  ba2742:	sub    %rdx,%rax
  ba2745:	sar    $0x3,%rax
  ba2749:	test   %rax,%rax
  ba274c:	je     ba2720 <_ZN8CPetMenu12updateLayoutEv+0x70>
  ba274e:	mov    (%rdx),%rsi
  ba2751:	add    $0x8,%rbx
  ba2755:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  ba275a:	cmp    $0x60,%rbx
  ba275e:	jne    ba272a <_ZN8CPetMenu12updateLayoutEv+0x7a>
  ba2760:	lea    0xd90(%rsp),%rax
  ba2768:	lea    0x1c00(%rsp),%rdx
  ba2770:	mov    %r15,%r14
  ba2773:	mov    %r15,%rbp
  ba2776:	movl   $0x0,0x38(%rsp)
  ba277e:	add    $0x28,%rax
  ba2782:	add    $0x28,%rdx
  ba2786:	mov    %rax,0x78(%rsp)
  ba278b:	lea    0x1cb0(%rsp),%rax
  ba2793:	mov    %rdx,0x68(%rsp)
  ba2798:	lea    0x1050(%rsp),%rdx
  ba27a0:	add    $0x3c,%rax
  ba27a4:	mov    %rax,0x70(%rsp)
  ba27a9:	lea    0xfa0(%rsp),%rax
  ba27b1:	add    $0x3c,%rdx
  ba27b5:	mov    %rdx,0x58(%rsp)
  ba27ba:	add    $0x28,%rax
  ba27be:	mov    %rax,0x60(%rsp)
  ba27c3:	nopl   0x0(%rax,%rax,1)
  ba27c8:	cmpq   $0x0,0x1378(%rbp)
  ba27d0:	je     ba313c <_ZN8CPetMenu12updateLayoutEv+0xa8c>
  ba27d6:	mov    0x38(%rsp),%esi
  ba27da:	mov    0x50(%rsp),%rdi
  ba27df:	call   91b3a0 <_ZN10CInventory21getEquipmentRefInSlotEj>
  ba27e4:	test   %rax,%rax
  ba27e7:	je     ba2ef7 <_ZN8CPetMenu12updateLayoutEv+0x847>
  ba27ed:	mov    0x10(%rax),%r13
  ba27f1:	mov    0x2c8(%r13),%rdx
  ba27f8:	test   %rdx,%rdx
  ba27fb:	mov    %rdx,0x30(%rsp)
  ba2800:	je     ba4b23 <_ZN8CPetMenu12updateLayoutEv+0x2473>
  ba2806:	mov    0x30(%rsp),%rax
  ba280b:	mov    0xb0(%rax),%rdi
  ba2812:	test   %rdi,%rdi
  ba2815:	je     ba281f <_ZN8CPetMenu12updateLayoutEv+0x16f>
  ba2817:	mov    %rax,%rsi
  ba281a:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  ba281f:	mov    0x1378(%rbp),%rdi
  ba2826:	mov    0x30(%rsp),%rsi
  ba282b:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  ba2830:	mov    0x1378(%rbp),%rdi
  ba2837:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  ba283c:	xorps  %xmm3,%xmm3
  ba283f:	xorps  %xmm0,%xmm0
  ba2842:	movss  0x401fc6(%rip),%xmm2        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  ba284a:	movaps %xmm2,%xmm4
  ba284d:	mulss  (%rax),%xmm3
  ba2851:	movss  0x405e9b(%rip),%xmm1        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  ba2859:	cmpltss %xmm3,%xmm0
  ba285e:	andps  %xmm0,%xmm4
  ba2861:	andnps %xmm1,%xmm0
  ba2864:	orps   %xmm4,%xmm0
  ba2867:	addss  %xmm3,%xmm0
  ba286b:	cvttss2si %xmm0,%edx
  ba286f:	cvtsi2ss %edx,%xmm0
  ba2873:	addss  0x4(%rax),%xmm0
  ba2878:	movss  %xmm0,0x28(%rsp)
  ba287e:	mov    0x1378(%rbp),%rdi
  ba2885:	movss  %xmm1,(%rsp)
  ba288a:	movss  %xmm2,0x10(%rsp)
  ba2890:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  ba2895:	xorps  %xmm3,%xmm3
  ba2898:	xorps  %xmm0,%xmm0
  ba289b:	movss  0x10(%rsp),%xmm2
  ba28a1:	movss  (%rsp),%xmm1
  ba28a6:	mulss  0x8(%rax),%xmm3
  ba28ab:	cmpltss %xmm3,%xmm0
  ba28b0:	movss  %xmm3,0x40(%rsp)
  ba28b6:	andps  %xmm0,%xmm2
  ba28b9:	andnps %xmm1,%xmm0
  ba28bc:	orps   %xmm2,%xmm0
  ba28bf:	movss  %xmm0,0x20(%rsp)
  ba28c5:	movss  0xc(%rax),%xmm0
  ba28ca:	movss  %xmm0,0x48(%rsp)
  ba28d0:	cmpb   $0x0,0x348(%r13)
  ba28d8:	je     ba28e9 <_ZN8CPetMenu12updateLayoutEv+0x239>
  ba28da:	mov    0x3e0(%r13),%esi
  ba28e1:	test   %esi,%esi
  ba28e3:	jne    ba432e <_ZN8CPetMenu12updateLayoutEv+0x1c7e>
  ba28e9:	lea    0x1c00(%rsp),%rdi
  ba28f1:	xor    %esi,%esi
  ba28f3:	movq   $0x20,0x1c08(%rsp)
  ba28ff:	movq   $0x0,0x1c10(%rsp)
  ba290b:	movq   $0x0,0x1c20(%rsp)
  ba2917:	movq   $0x0,0x1c18(%rsp)
  ba2923:	movq   $0x0,0x1ca8(%rsp)
  ba292f:	movq   $0x0,0x1c00(%rsp)
  ba293b:	movl   $0x0,0x1c28(%rsp)
  ba2946:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba294b:	cmpq   $0x20,0x1c08(%rsp)
  ba2954:	movq   $0x0,0x1c00(%rsp)
  ba2960:	mov    0x68(%rsp),%rax
  ba2965:	ja     ba49f5 <_ZN8CPetMenu12updateLayoutEv+0x2345>
  ba296b:	lea    0x1cb0(%rsp),%rdi
  ba2973:	movl   $0x0,(%rax)
  ba2979:	mov    $0x5,%esi
  ba297e:	movq   $0x20,0x1cb8(%rsp)
  ba298a:	movq   $0x0,0x1cc0(%rsp)
  ba2996:	movq   $0x0,0x1cd0(%rsp)
  ba29a2:	movq   $0x0,0x1cc8(%rsp)
  ba29ae:	movq   $0x0,0x1d58(%rsp)
  ba29ba:	movq   $0x0,0x1cb0(%rsp)
  ba29c6:	movl   $0x0,0x1cd8(%rsp)
  ba29d1:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba29d6:	cmpq   $0x20,0x1cb8(%rsp)
  ba29df:	ja     ba4321 <_ZN8CPetMenu12updateLayoutEv+0x1c71>
  ba29e5:	lea    0x1cb0(%rsp),%rdx
  ba29ed:	add    $0x28,%rdx
  ba29f1:	mov    $0xfd0c0d,%eax
  ba29f6:	cs nopw 0x0(%rax,%rax,1)
  ba2a00:	movzbl (%rax),%ecx
  ba2a03:	add    $0x1,%rax
  ba2a07:	mov    %ecx,(%rdx)
  ba2a09:	add    $0x4,%rdx
  ba2a0d:	cmp    $0xfd0c12,%rax
  ba2a13:	jne    ba2a00 <_ZN8CPetMenu12updateLayoutEv+0x350>
  ba2a15:	cmpq   $0x20,0x1cb8(%rsp)
  ba2a1e:	movq   $0x5,0x1cb0(%rsp)
  ba2a2a:	mov    0x70(%rsp),%rax
  ba2a2f:	jbe    ba2a3d <_ZN8CPetMenu12updateLayoutEv+0x38d>
  ba2a31:	mov    0x1d58(%rsp),%rax
  ba2a39:	add    $0x14,%rax
  ba2a3d:	movl   $0x0,(%rax)
  ba2a43:	mov    0x1b28(%rbp),%rdi
  ba2a4a:	lea    0x1c00(%rsp),%rdx
  ba2a52:	lea    0x1cb0(%rsp),%rsi
  ba2a5a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba2a5f:	lea    0x1cb0(%rsp),%rdi
  ba2a67:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2a6c:	lea    0x1c00(%rsp),%rdi
  ba2a74:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2a79:	cmpb   $0x0,0x348(%r13)
  ba2a81:	jne    ba4019 <_ZN8CPetMenu12updateLayoutEv+0x1969>
  ba2a87:	lea    0x1b50(%rsp),%r12
  ba2a8f:	mov    $0xc,%esi
  ba2a94:	movq   $0x20,0x1b58(%rsp)
  ba2aa0:	movq   $0x0,0x1b60(%rsp)
  ba2aac:	movq   $0x0,0x1b70(%rsp)
  ba2ab8:	mov    %r12,%rdi
  ba2abb:	movq   $0x0,0x1b68(%rsp)
  ba2ac7:	movq   $0x0,0x1bf8(%rsp)
  ba2ad3:	movq   $0x0,0x1b50(%rsp)
  ba2adf:	movl   $0x0,0x1b78(%rsp)
  ba2aea:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba2aef:	cmpq   $0x20,0x1b58(%rsp)
  ba2af8:	lea    0x28(%r12),%rdx
  ba2afd:	jbe    ba2b07 <_ZN8CPetMenu12updateLayoutEv+0x457>
  ba2aff:	mov    0x1bf8(%rsp),%rdx
  ba2b07:	mov    $0xfef791,%eax
  ba2b0c:	nopl   0x0(%rax)
  ba2b10:	movzbl (%rax),%ecx
  ba2b13:	add    $0x1,%rax
  ba2b17:	mov    %ecx,(%rdx)
  ba2b19:	add    $0x4,%rdx
  ba2b1d:	cmp    $0xfef79d,%rax
  ba2b23:	jne    ba2b10 <_ZN8CPetMenu12updateLayoutEv+0x460>
  ba2b25:	cmpq   $0x20,0x1b58(%rsp)
  ba2b2e:	movq   $0xc,0x1b50(%rsp)
  ba2b3a:	lea    0x58(%r12),%rax
  ba2b3f:	jbe    ba2b4d <_ZN8CPetMenu12updateLayoutEv+0x49d>
  ba2b41:	mov    0x1bf8(%rsp),%rax
  ba2b49:	add    $0x30,%rax
  ba2b4d:	movl   $0x0,(%rax)
  ba2b53:	mov    0x9108(%r15),%rdi
  ba2b5a:	mov    %r12,%rsi
  ba2b5d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba2b62:	lea    0x1aa0(%rsp),%rdi
  ba2b6a:	mov    %rax,%rsi
  ba2b6d:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba2b72:	lea    0x19f0(%rsp),%rbx
  ba2b7a:	mov    $0x5,%esi
  ba2b7f:	movq   $0x20,0x19f8(%rsp)
  ba2b8b:	movq   $0x0,0x1a00(%rsp)
  ba2b97:	movq   $0x0,0x1a10(%rsp)
  ba2ba3:	mov    %rbx,%rdi
  ba2ba6:	movq   $0x0,0x1a08(%rsp)
  ba2bb2:	movq   $0x0,0x1a98(%rsp)
  ba2bbe:	movq   $0x0,0x19f0(%rsp)
  ba2bca:	movl   $0x0,0x1a18(%rsp)
  ba2bd5:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba2bda:	cmpq   $0x20,0x19f8(%rsp)
  ba2be3:	lea    0x28(%rbx),%rdx
  ba2be7:	jbe    ba2bf1 <_ZN8CPetMenu12updateLayoutEv+0x541>
  ba2be9:	mov    0x1a98(%rsp),%rdx
  ba2bf1:	mov    $0xfd0c0d,%eax
  ba2bf6:	cs nopw 0x0(%rax,%rax,1)
  ba2c00:	movzbl (%rax),%ecx
  ba2c03:	add    $0x1,%rax
  ba2c07:	mov    %ecx,(%rdx)
  ba2c09:	add    $0x4,%rdx
  ba2c0d:	cmp    $0xfd0c12,%rax
  ba2c13:	jne    ba2c00 <_ZN8CPetMenu12updateLayoutEv+0x550>
  ba2c15:	cmpq   $0x20,0x19f8(%rsp)
  ba2c1e:	movq   $0x5,0x19f0(%rsp)
  ba2c2a:	lea    0x3c(%rbx),%rax
  ba2c2e:	jbe    ba2c3c <_ZN8CPetMenu12updateLayoutEv+0x58c>
  ba2c30:	mov    0x1a98(%rsp),%rax
  ba2c38:	add    $0x14,%rax
  ba2c3c:	movl   $0x0,(%rax)
  ba2c42:	mov    0x1608(%rbp),%rdi
  ba2c49:	lea    0x1aa0(%rsp),%rdx
  ba2c51:	mov    %rbx,%rsi
  ba2c54:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba2c59:	mov    %rbx,%rdi
  ba2c5c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2c61:	lea    0x1aa0(%rsp),%rdi
  ba2c69:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2c6e:	mov    %r12,%rdi
  ba2c71:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2c76:	movss  0x40(%rsp),%xmm0
  ba2c7c:	addss  0x20(%rsp),%xmm0
  ba2c82:	cvttss2si %xmm0,%eax
  ba2c86:	cvtsi2ss %eax,%xmm1
  ba2c8a:	addss  0x48(%rsp),%xmm1
  ba2c90:	movss  %xmm1,0x20(%rsp)
  ba2c96:	cmpl   $0x1,0x3e0(%r13)
  ba2c9e:	jbe    ba2d0a <_ZN8CPetMenu12updateLayoutEv+0x65a>
  ba2ca0:	mov    0x1378(%rbp),%rsi
  ba2ca7:	lea    0x2200(%rsp),%rdi
  ba2caf:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba2cb4:	xorps  %xmm2,%xmm2
  ba2cb7:	xorps  %xmm0,%xmm0
  ba2cba:	movss  0x401b4e(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  ba2cc2:	movss  0x405a2a(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  ba2cca:	mulss  0x2208(%rsp),%xmm2
  ba2cd3:	cmpltss %xmm2,%xmm0
  ba2cd8:	andps  %xmm0,%xmm1
  ba2cdb:	andnps %xmm3,%xmm0
  ba2cde:	orps   %xmm1,%xmm0
  ba2ce1:	addss  %xmm2,%xmm0
  ba2ce5:	cvttss2si %xmm0,%eax
  ba2ce9:	cvtsi2ss %eax,%xmm0
  ba2ced:	addss  0x220c(%rsp),%xmm0
  ba2cf6:	mulss  0x443822(%rip),%xmm0        # fe6520 <_ZTV8CSubMenu+0x80>
  ba2cfe:	addss  0x20(%rsp),%xmm0
  ba2d04:	movss  %xmm0,0x20(%rsp)
  ba2d0a:	mov    0x1378(%rbp),%rax
  ba2d11:	xor    %esi,%esi
  ba2d13:	mov    0xb0(%rax),%rdi
  ba2d1a:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  ba2d1f:	test   %al,%al
  ba2d21:	je     ba3900 <_ZN8CPetMenu12updateLayoutEv+0x1250>
  ba2d27:	mov    0x3f0(%r13),%ebx
  ba2d2e:	test   %ebx,%ebx
  ba2d30:	je     ba3900 <_ZN8CPetMenu12updateLayoutEv+0x1250>
  ba2d36:	xor    %r12d,%r12d
  ba2d39:	jmp    ba2e84 <_ZN8CPetMenu12updateLayoutEv+0x7d4>
  ba2d3e:	xchg   %ax,%ax
  ba2d40:	mov    0x3e8(%r13),%rax
  ba2d47:	mov    (%rax),%rax
  ba2d4a:	mov    0x2c8(%rax),%rbx
  ba2d51:	test   %rbx,%rbx
  ba2d54:	je     ba2eb2 <_ZN8CPetMenu12updateLayoutEv+0x802>
  ba2d5a:	mov    0xb0(%rbx),%rdi
  ba2d61:	test   %rdi,%rdi
  ba2d64:	je     ba2d6e <_ZN8CPetMenu12updateLayoutEv+0x6be>
  ba2d66:	mov    %rbx,%rsi
  ba2d69:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  ba2d6e:	mov    0x30(%r15),%rdi
  ba2d72:	mov    %rbx,%rsi
  ba2d75:	call   553088 <_ZNK5CEGUI6Window7isChildEPKS0_@plt>
  ba2d7a:	test   %al,%al
  ba2d7c:	jne    ba38e0 <_ZN8CPetMenu12updateLayoutEv+0x1230>
  ba2d82:	mov    0x30(%r15),%rdi
  ba2d86:	mov    %rbx,%rsi
  ba2d89:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  ba2d8e:	lea    0x21f0(%rsp),%rsi
  ba2d96:	movss  0x28(%rsp),%xmm3
  ba2d9c:	movss  0x20(%rsp),%xmm0
  ba2da2:	mov    %rbx,%rdi
  ba2da5:	movss  %xmm3,0x21f4(%rsp)
  ba2dae:	movl   $0x0,0x21f0(%rsp)
  ba2db9:	movl   $0x0,0x21f8(%rsp)
  ba2dc4:	movss  %xmm0,0x21fc(%rsp)
  ba2dcd:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  ba2dd2:	mov    0x1378(%rbp),%rsi
  ba2dd9:	lea    0x21e0(%rsp),%rdi
  ba2de1:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba2de6:	lea    0x21e0(%rsp),%rsi
  ba2dee:	mov    %rbx,%rdi
  ba2df1:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  ba2df6:	mov    %rbx,%rdi
  ba2df9:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba2dfe:	movb   $0x1,0x3e2(%rbx)
  ba2e05:	mov    0x1378(%rbp),%rsi
  ba2e0c:	lea    0x21d0(%rsp),%rdi
  ba2e14:	add    $0x1,%r12d
  ba2e18:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba2e1d:	xorps  %xmm1,%xmm1
  ba2e20:	cmp    0x3f0(%r13),%r12d
  ba2e27:	xorps  %xmm0,%xmm0
  ba2e2a:	movss  0x4019de(%rip),%xmm2        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  ba2e32:	mulss  0x21d8(%rsp),%xmm1
  ba2e3b:	movss  0x4058b1(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  ba2e43:	cmpltss %xmm1,%xmm0
  ba2e48:	andps  %xmm0,%xmm2
  ba2e4b:	andnps %xmm3,%xmm0
  ba2e4e:	orps   %xmm2,%xmm0
  ba2e51:	movss  0x21dc(%rsp),%xmm2
  ba2e5a:	jae    ba3900 <_ZN8CPetMenu12updateLayoutEv+0x1250>
  ba2e60:	addss  %xmm1,%xmm0
  ba2e64:	cvttss2si %xmm0,%eax
  ba2e68:	cvtsi2ss %eax,%xmm0
  ba2e6c:	addss  %xmm2,%xmm0
  ba2e70:	mulss  0x4019b8(%rip),%xmm0        # fa4830 <_ZTVN4Ogre13FrameListenerE+0x70>
  ba2e78:	addss  0x20(%rsp),%xmm0
  ba2e7e:	movss  %xmm0,0x20(%rsp)
  ba2e84:	cmp    %r12d,0x3f4(%r13)
  ba2e8b:	jbe    ba2d40 <_ZN8CPetMenu12updateLayoutEv+0x690>
  ba2e91:	mov    %r12d,%eax
  ba2e94:	shl    $0x3,%rax
  ba2e98:	add    0x3e8(%r13),%rax
  ba2e9f:	mov    (%rax),%rax
  ba2ea2:	mov    0x2c8(%rax),%rbx
  ba2ea9:	test   %rbx,%rbx
  ba2eac:	jne    ba2d5a <_ZN8CPetMenu12updateLayoutEv+0x6aa>
  ba2eb2:	mov    0x90(%r15),%rsi
  ba2eb9:	xor    %edx,%edx
  ba2ebb:	mov    %rax,%rdi
  ba2ebe:	mov    %rax,0x10(%rsp)
  ba2ec3:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  ba2ec8:	mov    0x10(%rsp),%rax
  ba2ecd:	mov    0x2c8(%rax),%rbx
  ba2ed4:	test   %rbx,%rbx
  ba2ed7:	je     ba2e05 <_ZN8CPetMenu12updateLayoutEv+0x755>
  ba2edd:	lea    0x38(%rbx),%rdi
  ba2ee1:	mov    $0x1,%esi
  ba2ee6:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  ba2eeb:	movb   $0x1,0x3e2(%rbx)
  ba2ef2:	jmp    ba2d5a <_ZN8CPetMenu12updateLayoutEv+0x6aa>
  ba2ef7:	cmpq   $0x0,0x1378(%rbp)
  ba2eff:	je     ba313c <_ZN8CPetMenu12updateLayoutEv+0xa8c>
  ba2f05:	lea    0xd90(%rsp),%rdi
  ba2f0d:	xor    %esi,%esi
  ba2f0f:	movq   $0x20,0xd98(%rsp)
  ba2f1b:	movq   $0x0,0xda0(%rsp)
  ba2f27:	movq   $0x0,0xdb0(%rsp)
  ba2f33:	lea    0xe40(%rsp),%rbx
  ba2f3b:	movq   $0x0,0xda8(%rsp)
  ba2f47:	movq   $0x0,0xe38(%rsp)
  ba2f53:	movq   $0x0,0xd90(%rsp)
  ba2f5f:	movl   $0x0,0xdb8(%rsp)
  ba2f6a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba2f6f:	cmpq   $0x21,0xd98(%rsp)
  ba2f78:	mov    0x78(%rsp),%rax
  ba2f7d:	mov    $0xfd0c0d,%esi
  ba2f82:	cmovae 0xe38(%rsp),%rax
  ba2f8b:	movq   $0x0,0xd90(%rsp)
  ba2f97:	mov    %rbx,%rdi
  ba2f9a:	movl   $0x0,(%rax)
  ba2fa0:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba2fa5:	mov    0x1608(%rbp),%rdi
  ba2fac:	lea    0xd90(%rsp),%rdx
  ba2fb4:	mov    %rbx,%rsi
  ba2fb7:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba2fbc:	mov    %rbx,%rdi
  ba2fbf:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2fc4:	lea    0xd90(%rsp),%rdi
  ba2fcc:	lea    0xc30(%rsp),%r12
  ba2fd4:	lea    0xce0(%rsp),%rbx
  ba2fdc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba2fe1:	mov    $0x10257f7,%esi
  ba2fe6:	mov    %r12,%rdi
  ba2fe9:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba2fee:	mov    $0xfd0c0d,%esi
  ba2ff3:	mov    %rbx,%rdi
  ba2ff6:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba2ffb:	mov    0x1b28(%rbp),%rdi
  ba3002:	mov    %r12,%rdx
  ba3005:	mov    %rbx,%rsi
  ba3008:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba300d:	mov    %rbx,%rdi
  ba3010:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3015:	mov    %r12,%rdi
  ba3018:	lea    0x2190(%rsp),%rbx
  ba3020:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3025:	mov    0x1378(%rbp),%rsi
  ba302c:	mov    %rbx,%rdi
  ba302f:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba3034:	mov    0x1b28(%rbp),%rdi
  ba303b:	mov    %rbx,%rsi
  ba303e:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  ba3043:	lea    0xad0(%rsp),%r12
  ba304b:	lea    0xb80(%rsp),%rbx
  ba3053:	mov    $0x10257f7,%esi
  ba3058:	mov    %r12,%rdi
  ba305b:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba3060:	mov    $0xfd0c0d,%esi
  ba3065:	mov    %rbx,%rdi
  ba3068:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba306d:	mov    0x1898(%rbp),%rdi
  ba3074:	mov    %r12,%rdx
  ba3077:	mov    %rbx,%rsi
  ba307a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba307f:	mov    %rbx,%rdi
  ba3082:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3087:	mov    %r12,%rdi
  ba308a:	lea    0x2180(%rsp),%rbx
  ba3092:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3097:	mov    0x1378(%rbp),%rsi
  ba309e:	mov    %rbx,%rdi
  ba30a1:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba30a6:	mov    0x1898(%rbp),%rdi
  ba30ad:	mov    %rbx,%rsi
  ba30b0:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  ba30b5:	mov    0x38(%rsp),%ebx
  ba30b9:	lea    0xa20(%rsp),%r12
  ba30c1:	lea    (%rbx,%rbx,4),%rax
  ba30c5:	lea    (%rbx,%rax,2),%rax
  ba30c9:	shl    $0x4,%rax
  ba30cd:	lea    0x58a8(%r15,%rax,1),%rdi
  ba30d5:	call   556378 <_ZNK5CEGUI6String15build_utf8_buffEv@plt>
  ba30da:	mov    %r12,%rdi
  ba30dd:	mov    %rax,%rsi
  ba30e0:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  ba30e5:	mov    0x1378(%rbp),%rdi
  ba30ec:	mov    %r12,%rsi
  ba30ef:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  ba30f4:	mov    %r12,%rdi
  ba30f7:	lea    0x970(%rsp),%r12
  ba30ff:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3104:	mov    $0xfd0c0d,%esi
  ba3109:	mov    %r12,%rdi
  ba310c:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba3111:	lea    (%rbx,%rbx,4),%rax
  ba3115:	mov    0x1378(%rbp),%rdi
  ba311c:	mov    %r12,%rsi
  ba311f:	lea    (%rbx,%rax,2),%rax
  ba3123:	shl    $0x4,%rax
  ba3127:	lea    0x2048(%r15,%rax,1),%rdx
  ba312f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba3134:	mov    %r12,%rdi
  ba3137:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba313c:	addl   $0x1,0x38(%rsp)
  ba3141:	add    $0x8,%rbp
  ba3145:	cmpl   $0xc,0x38(%rsp)
  ba314a:	jne    ba27c8 <_ZN8CPetMenu12updateLayoutEv+0x118>
  ba3150:	lea    0x1368(%r15),%rax
  ba3157:	lea    0x2220(%rsp),%r13
  ba315f:	mov    %r15,%rbx
  ba3162:	xor    %ebp,%ebp
  ba3164:	mov    %rax,0x20(%rsp)
  ba3169:	cmpq   $0x0,0x1040(%rbx)
  ba3171:	je     ba3333 <_ZN8CPetMenu12updateLayoutEv+0xc83>
  ba3177:	cmpb   $0x0,0x929e7a(%rip)        # 14ccff8 <_ZGVZN8CPetMenu12updateLayoutEvE14g_RemoveASpell>
  ba317e:	je     ba4ae3 <_ZN8CPetMenu12updateLayoutEv+0x2433>
  ba3184:	mov    0x929e95(%rip),%rax        # 14cd020 <_ZZN8CPetMenu12updateLayoutEvE14g_RemoveASpell>
  ba318b:	cmpq   $0x0,-0x18(%rax)
  ba3190:	je     ba4a42 <_ZN8CPetMenu12updateLayoutEv+0x2392>
  ba3196:	cmpb   $0x0,0x929e63(%rip)        # 14cd000 <_ZGVZN8CPetMenu12updateLayoutEvE15g_RemoveASpell2>
  ba319d:	je     ba4a02 <_ZN8CPetMenu12updateLayoutEv+0x2352>
  ba31a3:	mov    0x929e6e(%rip),%rax        # 14cd018 <_ZZN8CPetMenu12updateLayoutEvE15g_RemoveASpell2>
  ba31aa:	cmpq   $0x0,-0x18(%rax)
  ba31af:	je     ba4ba9 <_ZN8CPetMenu12updateLayoutEv+0x24f9>
  ba31b5:	cmpb   $0x0,0x929e4c(%rip)        # 14cd008 <_ZGVZN8CPetMenu12updateLayoutEvE12g_DragASpell>
  ba31bc:	je     ba4b69 <_ZN8CPetMenu12updateLayoutEv+0x24b9>
  ba31c2:	mov    0x929e47(%rip),%rax        # 14cd010 <_ZZN8CPetMenu12updateLayoutEvE12g_DragASpell>
  ba31c9:	cmpq   $0x0,-0x18(%rax)
  ba31ce:	jne    ba3268 <_ZN8CPetMenu12updateLayoutEv+0xbb8>
  ba31d4:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  ba31d9:	lea    0x2250(%rsp),%rdi
  ba31e1:	mov    %rax,%rsi
  ba31e4:	mov    $0xfef910,%edx
  ba31e9:	lea    0x2240(%rsp),%r12
  ba31f1:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  ba31f6:	mov    0x2250(%rsp),%rsi
  ba31fe:	mov    %r12,%rdi
  ba3201:	call   c8e350 <_ZN7STRINGS21StringConvertToNarrowEPKw>
  ba3206:	mov    %r12,%rsi
  ba3209:	mov    $0x14cd010,%edi
  ba320e:	call   554d18 <_ZNSs6assignERKSs@plt>
  ba3213:	mov    0x2240(%rsp),%rdi
  ba321b:	sub    $0x18,%rdi
  ba321f:	cmp    $0x1423a20,%rdi
  ba3226:	jne    ba4faa <_ZN8CPetMenu12updateLayoutEv+0x28fa>
  ba322c:	mov    0x2250(%rsp),%rdi
  ba3234:	sub    $0x18,%rdi
  ba3238:	cmp    $0x1424540,%rdi
  ba323f:	je     ba3268 <_ZN8CPetMenu12updateLayoutEv+0xbb8>
  ba3241:	mov    $0x5541c8,%eax
  ba3246:	test   %rax,%rax
  ba3249:	je     ba501d <_ZN8CPetMenu12updateLayoutEv+0x296d>
  ba324f:	or     $0xffffffff,%eax
  ba3252:	lock xadd %eax,0x10(%rdi)
  ba3257:	test   %eax,%eax
  ba3259:	jg     ba3268 <_ZN8CPetMenu12updateLayoutEv+0xbb8>
  ba325b:	lea    0x22aa(%rsp),%rsi
  ba3263:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  ba3268:	mov    0x58(%r15),%rdi
  ba326c:	mov    %ebp,%esi
  ba326e:	call   80f800 <_ZN10CCharacter13getKnownSpellEj>
  ba3273:	test   %rax,%rax
  ba3276:	mov    %rax,%r12
  ba3279:	je     ba3291 <_ZN8CPetMenu12updateLayoutEv+0xbe1>
  ba327b:	mov    %rax,%rdi
  ba327e:	call   c9ce10 <_ZN6CSkill12getSkillIconEv>
  ba3283:	mov    (%rax),%rax
  ba3286:	cmpq   $0x0,-0x18(%rax)
  ba328b:	jne    ba47aa <_ZN8CPetMenu12updateLayoutEv+0x20fa>
  ba3291:	lea    0x600(%rsp),%rdi
  ba3299:	mov    $0x10257f7,%esi
  ba329e:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba32a3:	lea    0x6b0(%rsp),%rdi
  ba32ab:	mov    $0xfd0c0d,%esi
  ba32b0:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba32b5:	mov    0x1040(%rbx),%rdi
  ba32bc:	lea    0x600(%rsp),%rdx
  ba32c4:	lea    0x6b0(%rsp),%rsi
  ba32cc:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba32d1:	lea    0x6b0(%rsp),%rdi
  ba32d9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba32de:	lea    0x600(%rsp),%rdi
  ba32e6:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba32eb:	mov    0x1040(%rbx),%rax
  ba32f2:	mov    0x20(%rsp),%rdx
  ba32f7:	lea    0x550(%rsp),%rdi
  ba32ff:	mov    %rdx,0x1d8(%rax)
  ba3306:	mov    0x929d03(%rip),%rsi        # 14cd010 <_ZZN8CPetMenu12updateLayoutEvE12g_DragASpell>
  ba330d:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  ba3312:	mov    0x1040(%rbx),%rdi
  ba3319:	lea    0x550(%rsp),%rsi
  ba3321:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  ba3326:	lea    0x550(%rsp),%rdi
  ba332e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3333:	add    $0x1,%ebp
  ba3336:	add    $0x8,%rbx
  ba333a:	cmp    $0x2,%ebp
  ba333d:	jne    ba3169 <_ZN8CPetMenu12updateLayoutEv+0xab9>
  ba3343:	lea    0x3f0(%rsp),%rax
  ba334b:	lea    0x290(%rsp),%rdx
  ba3353:	lea    0x340(%rsp),%r13
  ba335b:	lea    0x1e0(%rsp),%r12
  ba3363:	lea    0x4a0(%rsp),%rbp
  ba336b:	movl   $0x13,0x20(%rsp)
  ba3373:	add    $0x28,%rax
  ba3377:	add    $0x28,%rdx
  ba337b:	mov    %rax,0x28(%rsp)
  ba3380:	lea    0x28(%r13),%rax
  ba3384:	mov    %rdx,0x30(%rsp)
  ba3389:	lea    0x130(%rsp),%rdx
  ba3391:	mov    %rax,0x38(%rsp)
  ba3396:	lea    0x28(%r12),%rax
  ba339b:	add    $0x28,%rdx
  ba339f:	mov    %rdx,0x40(%rsp)
  ba33a4:	mov    %rax,0x48(%rsp)
  ba33a9:	nopl   0x0(%rax)
  ba33b0:	lea    0x3f0(%rsp),%rdi
  ba33b8:	xor    %esi,%esi
  ba33ba:	movq   $0x20,0x3f8(%rsp)
  ba33c6:	movq   $0x0,0x400(%rsp)
  ba33d2:	movq   $0x0,0x410(%rsp)
  ba33de:	movq   $0x0,0x408(%rsp)
  ba33ea:	movq   $0x0,0x498(%rsp)
  ba33f6:	movq   $0x0,0x3f0(%rsp)
  ba3402:	movl   $0x0,0x418(%rsp)
  ba340d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3412:	cmpq   $0x21,0x3f8(%rsp)
  ba341b:	mov    0x28(%rsp),%rax
  ba3420:	mov    $0x5,%esi
  ba3425:	cmovae 0x498(%rsp),%rax
  ba342e:	movq   $0x0,0x3f0(%rsp)
  ba343a:	mov    %rbp,%rdi
  ba343d:	movl   $0x0,(%rax)
  ba3443:	movq   $0x20,0x4a8(%rsp)
  ba344f:	movq   $0x0,0x4b0(%rsp)
  ba345b:	movq   $0x0,0x4c0(%rsp)
  ba3467:	movq   $0x0,0x4b8(%rsp)
  ba3473:	movq   $0x0,0x548(%rsp)
  ba347f:	movq   $0x0,0x4a0(%rsp)
  ba348b:	movl   $0x0,0x4c8(%rsp)
  ba3496:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba349b:	cmpq   $0x20,0x4a8(%rsp)
  ba34a4:	lea    0x28(%rbp),%rdx
  ba34a8:	jbe    ba34b2 <_ZN8CPetMenu12updateLayoutEv+0xe02>
  ba34aa:	mov    0x548(%rsp),%rdx
  ba34b2:	mov    $0xfd0c12,%ebx
  ba34b7:	mov    $0xfd0c0d,%eax
  ba34bc:	nopl   0x0(%rax)
  ba34c0:	movzbl (%rax),%ecx
  ba34c3:	add    $0x1,%rax
  ba34c7:	mov    %ecx,(%rdx)
  ba34c9:	add    $0x4,%rdx
  ba34cd:	cmp    $0xfd0c12,%rax
  ba34d3:	jne    ba34c0 <_ZN8CPetMenu12updateLayoutEv+0xe10>
  ba34d5:	cmpq   $0x20,0x4a8(%rsp)
  ba34de:	movq   $0x5,0x4a0(%rsp)
  ba34ea:	lea    0x3c(%rbp),%rax
  ba34ee:	jbe    ba34fc <_ZN8CPetMenu12updateLayoutEv+0xe4c>
  ba34f0:	mov    0x548(%rsp),%rax
  ba34f8:	add    $0x14,%rax
  ba34fc:	movl   $0x0,(%rax)
  ba3502:	mov    0x1930(%r14),%rdi
  ba3509:	lea    0x3f0(%rsp),%rdx
  ba3511:	mov    %rbp,%rsi
  ba3514:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba3519:	mov    %rbp,%rdi
  ba351c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3521:	lea    0x3f0(%rsp),%rdi
  ba3529:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba352e:	lea    0x290(%rsp),%rdi
  ba3536:	xor    %esi,%esi
  ba3538:	movq   $0x20,0x298(%rsp)
  ba3544:	movq   $0x0,0x2a0(%rsp)
  ba3550:	movq   $0x0,0x2b0(%rsp)
  ba355c:	movq   $0x0,0x2a8(%rsp)
  ba3568:	movq   $0x0,0x338(%rsp)
  ba3574:	movq   $0x0,0x290(%rsp)
  ba3580:	movl   $0x0,0x2b8(%rsp)
  ba358b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3590:	cmpq   $0x21,0x298(%rsp)
  ba3599:	mov    0x30(%rsp),%rax
  ba359e:	mov    $0x5,%esi
  ba35a3:	cmovae 0x338(%rsp),%rax
  ba35ac:	movq   $0x0,0x290(%rsp)
  ba35b8:	mov    %r13,%rdi
  ba35bb:	movl   $0x0,(%rax)
  ba35c1:	movq   $0x20,0x348(%rsp)
  ba35cd:	movq   $0x0,0x350(%rsp)
  ba35d9:	movq   $0x0,0x360(%rsp)
  ba35e5:	movq   $0x0,0x358(%rsp)
  ba35f1:	movq   $0x0,0x3e8(%rsp)
  ba35fd:	movq   $0x0,0x340(%rsp)
  ba3609:	movl   $0x0,0x368(%rsp)
  ba3614:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3619:	cmpq   $0x21,0x348(%rsp)
  ba3622:	mov    0x38(%rsp),%rdx
  ba3627:	mov    $0xfd0c0d,%eax
  ba362c:	cmovae 0x3e8(%rsp),%rdx
  ba3635:	nopl   (%rax)
  ba3638:	movzbl (%rax),%ecx
  ba363b:	add    $0x1,%rax
  ba363f:	mov    %ecx,(%rdx)
  ba3641:	add    $0x4,%rdx
  ba3645:	cmp    %rax,%rbx
  ba3648:	jne    ba3638 <_ZN8CPetMenu12updateLayoutEv+0xf88>
  ba364a:	cmpq   $0x20,0x348(%rsp)
  ba3653:	movq   $0x5,0x340(%rsp)
  ba365f:	lea    0x3c(%r13),%rax
  ba3663:	jbe    ba3671 <_ZN8CPetMenu12updateLayoutEv+0xfc1>
  ba3665:	mov    0x3e8(%rsp),%rax
  ba366d:	add    $0x14,%rax
  ba3671:	movl   $0x0,(%rax)
  ba3677:	mov    0x1bc0(%r14),%rdi
  ba367e:	lea    0x290(%rsp),%rdx
  ba3686:	mov    %r13,%rsi
  ba3689:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba368e:	mov    %r13,%rdi
  ba3691:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3696:	lea    0x290(%rsp),%rdi
  ba369e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba36a3:	lea    0x130(%rsp),%rdi
  ba36ab:	xor    %esi,%esi
  ba36ad:	movq   $0x20,0x138(%rsp)
  ba36b9:	movq   $0x0,0x140(%rsp)
  ba36c5:	movq   $0x0,0x150(%rsp)
  ba36d1:	movq   $0x0,0x148(%rsp)
  ba36dd:	movq   $0x0,0x1d8(%rsp)
  ba36e9:	movq   $0x0,0x130(%rsp)
  ba36f5:	movl   $0x0,0x158(%rsp)
  ba3700:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3705:	cmpq   $0x21,0x138(%rsp)
  ba370e:	mov    0x40(%rsp),%rax
  ba3713:	mov    $0x5,%esi
  ba3718:	cmovae 0x1d8(%rsp),%rax
  ba3721:	movq   $0x0,0x130(%rsp)
  ba372d:	mov    %r12,%rdi
  ba3730:	movl   $0x0,(%rax)
  ba3736:	movq   $0x20,0x1e8(%rsp)
  ba3742:	movq   $0x0,0x1f0(%rsp)
  ba374e:	movq   $0x0,0x200(%rsp)
  ba375a:	movq   $0x0,0x1f8(%rsp)
  ba3766:	movq   $0x0,0x288(%rsp)
  ba3772:	movq   $0x0,0x1e0(%rsp)
  ba377e:	movl   $0x0,0x208(%rsp)
  ba3789:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba378e:	cmpq   $0x21,0x1e8(%rsp)
  ba3797:	mov    0x48(%rsp),%rdx
  ba379c:	mov    $0xfd0c0d,%eax
  ba37a1:	cmovae 0x288(%rsp),%rdx
  ba37aa:	nopw   0x0(%rax,%rax,1)
  ba37b0:	movzbl (%rax),%ecx
  ba37b3:	add    $0x1,%rax
  ba37b7:	mov    %ecx,(%rdx)
  ba37b9:	add    $0x4,%rdx
  ba37bd:	cmp    %rax,%rbx
  ba37c0:	jne    ba37b0 <_ZN8CPetMenu12updateLayoutEv+0x1100>
  ba37c2:	cmpq   $0x20,0x1e8(%rsp)
  ba37cb:	movq   $0x5,0x1e0(%rsp)
  ba37d7:	lea    0x3c(%r12),%rax
  ba37dc:	jbe    ba37ea <_ZN8CPetMenu12updateLayoutEv+0x113a>
  ba37de:	mov    0x288(%rsp),%rax
  ba37e6:	add    $0x14,%rax
  ba37ea:	movl   $0x0,(%rax)
  ba37f0:	mov    0x16a0(%r14),%rdi
  ba37f7:	lea    0x130(%rsp),%rdx
  ba37ff:	mov    %r12,%rsi
  ba3802:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba3807:	mov    %r12,%rdi
  ba380a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba380f:	lea    0x130(%rsp),%rdi
  ba3817:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba381c:	cmpq   $0x0,0x1e50(%r14)
  ba3824:	je     ba3859 <_ZN8CPetMenu12updateLayoutEv+0x11a9>
  ba3826:	lea    0x80(%rsp),%rdi
  ba382e:	mov    $0x10257f7,%esi
  ba3833:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  ba3838:	mov    0x1e50(%r14),%rdi
  ba383f:	lea    0x80(%rsp),%rsi
  ba3847:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  ba384c:	lea    0x80(%rsp),%rdi
  ba3854:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3859:	mov    0x1410(%r14),%rdi
  ba3860:	mov    0x78(%rdi),%rdx
  ba3864:	mov    0x80(%rdi),%rax
  ba386b:	sub    %rdx,%rax
  ba386e:	sar    $0x3,%rax
  ba3872:	test   %rax,%rax
  ba3875:	jne    ba38f0 <_ZN8CPetMenu12updateLayoutEv+0x1240>
  ba3877:	addl   $0x1,0x20(%rsp)
  ba387c:	add    $0x8,%r14
  ba3880:	cmpl   $0x52,0x20(%rsp)
  ba3885:	jne    ba33b0 <_ZN8CPetMenu12updateLayoutEv+0xd00>
  ba388b:	mov    0x50(%rsp),%rdx
  ba3890:	mov    0x38(%rdx),%ecx
  ba3893:	test   %ecx,%ecx
  ba3895:	jne    ba4749 <_ZN8CPetMenu12updateLayoutEv+0x2099>
  ba389b:	mov    0x20(%r15),%rdi
  ba389f:	call   553a38 <_ZN5CEGUI6Window10moveToBackEv@plt>
  ba38a4:	mov    0x48(%r15),%rdi
  ba38a8:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba38ad:	mov    0x28(%r15),%rdi
  ba38b1:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba38b6:	mov    0x30(%r15),%rdi
  ba38ba:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba38bf:	mov    0x40(%r15),%rdi
  ba38c3:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba38c8:	add    $0x22b8,%rsp
  ba38cf:	pop    %rbx
  ba38d0:	pop    %rbp
  ba38d1:	pop    %r12
  ba38d3:	pop    %r13
  ba38d5:	pop    %r14
  ba38d7:	pop    %r15
  ba38d9:	ret
  ba38da:	nopw   0x0(%rax,%rax,1)
  ba38e0:	test   %rbx,%rbx
  ba38e3:	jne    ba2d8e <_ZN8CPetMenu12updateLayoutEv+0x6de>
  ba38e9:	jmp    ba2e05 <_ZN8CPetMenu12updateLayoutEv+0x755>
  ba38ee:	xchg   %ax,%ax
  ba38f0:	mov    (%rdx),%rsi
  ba38f3:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  ba38f8:	jmp    ba3877 <_ZN8CPetMenu12updateLayoutEv+0x11c7>
  ba38fd:	nopl   (%rax)
  ba3900:	mov    $0x36,%esi
  ba3905:	mov    %r13,%rdi
  ba3908:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  ba390d:	test   %al,%al
  ba390f:	je     ba3e10 <_ZN8CPetMenu12updateLayoutEv+0x1760>
  ba3915:	lea    0x17e0(%rsp),%r12
  ba391d:	mov    $0xc,%esi
  ba3922:	movq   $0x20,0x17e8(%rsp)
  ba392e:	movq   $0x0,0x17f0(%rsp)
  ba393a:	movq   $0x0,0x1800(%rsp)
  ba3946:	mov    %r12,%rdi
  ba3949:	movq   $0x0,0x17f8(%rsp)
  ba3955:	movq   $0x0,0x1888(%rsp)
  ba3961:	movq   $0x0,0x17e0(%rsp)
  ba396d:	movl   $0x0,0x1808(%rsp)
  ba3978:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba397d:	cmpq   $0x20,0x17e8(%rsp)
  ba3986:	lea    0x28(%r12),%rdx
  ba398b:	jbe    ba3995 <_ZN8CPetMenu12updateLayoutEv+0x12e5>
  ba398d:	mov    0x1888(%rsp),%rdx
  ba3995:	mov    $0xfe609b,%eax
  ba399a:	nopw   0x0(%rax,%rax,1)
  ba39a0:	movzbl (%rax),%ecx
  ba39a3:	add    $0x1,%rax
  ba39a7:	mov    %ecx,(%rdx)
  ba39a9:	add    $0x4,%rdx
  ba39ad:	cmp    $0xfe60a7,%rax
  ba39b3:	jne    ba39a0 <_ZN8CPetMenu12updateLayoutEv+0x12f0>
  ba39b5:	cmpq   $0x20,0x17e8(%rsp)
  ba39be:	movq   $0xc,0x17e0(%rsp)
  ba39ca:	lea    0x58(%r12),%rax
  ba39cf:	jbe    ba39dd <_ZN8CPetMenu12updateLayoutEv+0x132d>
  ba39d1:	mov    0x1888(%rsp),%rax
  ba39d9:	add    $0x30,%rax
  ba39dd:	movl   $0x0,(%rax)
  ba39e3:	mov    0x9108(%r15),%rdi
  ba39ea:	mov    %r12,%rsi
  ba39ed:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba39f2:	lea    0x1730(%rsp),%r13
  ba39fa:	mov    %rax,%rsi
  ba39fd:	mov    %r13,%rdi
  ba3a00:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba3a05:	lea    0x1680(%rsp),%rbx
  ba3a0d:	mov    $0x5,%esi
  ba3a12:	movq   $0x20,0x1688(%rsp)
  ba3a1e:	movq   $0x0,0x1690(%rsp)
  ba3a2a:	movq   $0x0,0x16a0(%rsp)
  ba3a36:	mov    %rbx,%rdi
  ba3a39:	movq   $0x0,0x1698(%rsp)
  ba3a45:	movq   $0x0,0x1728(%rsp)
  ba3a51:	movq   $0x0,0x1680(%rsp)
  ba3a5d:	movl   $0x0,0x16a8(%rsp)
  ba3a68:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3a6d:	cmpq   $0x20,0x1688(%rsp)
  ba3a76:	lea    0x28(%rbx),%rdx
  ba3a7a:	jbe    ba3a84 <_ZN8CPetMenu12updateLayoutEv+0x13d4>
  ba3a7c:	mov    0x1728(%rsp),%rdx
  ba3a84:	mov    $0xfd0c0d,%eax
  ba3a89:	nopl   0x0(%rax)
  ba3a90:	movzbl (%rax),%ecx
  ba3a93:	add    $0x1,%rax
  ba3a97:	mov    %ecx,(%rdx)
  ba3a99:	add    $0x4,%rdx
  ba3a9d:	cmp    $0xfd0c12,%rax
  ba3aa3:	jne    ba3a90 <_ZN8CPetMenu12updateLayoutEv+0x13e0>
  ba3aa5:	cmpq   $0x20,0x1688(%rsp)
  ba3aae:	movq   $0x5,0x1680(%rsp)
  ba3aba:	lea    0x3c(%rbx),%rax
  ba3abe:	jbe    ba3acc <_ZN8CPetMenu12updateLayoutEv+0x141c>
  ba3ac0:	mov    0x1728(%rsp),%rax
  ba3ac8:	add    $0x14,%rax
  ba3acc:	movl   $0x0,(%rax)
  ba3ad2:	mov    0x1898(%rbp),%rdi
  ba3ad9:	mov    %r13,%rdx
  ba3adc:	mov    %rbx,%rsi
  ba3adf:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba3ae4:	mov    %rbx,%rdi
  ba3ae7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3aec:	mov    %r13,%rdi
  ba3aef:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3af4:	mov    %r12,%rdi
  ba3af7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3afc:	lea    0xfa0(%rsp),%rdi
  ba3b04:	xor    %esi,%esi
  ba3b06:	movq   $0x20,0xfa8(%rsp)
  ba3b12:	movq   $0x0,0xfb0(%rsp)
  ba3b1e:	movq   $0x0,0xfc0(%rsp)
  ba3b2a:	movq   $0x0,0xfb8(%rsp)
  ba3b36:	movq   $0x0,0x1048(%rsp)
  ba3b42:	movq   $0x0,0xfa0(%rsp)
  ba3b4e:	movl   $0x0,0xfc8(%rsp)
  ba3b59:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3b5e:	cmpq   $0x21,0xfa8(%rsp)
  ba3b67:	mov    0x60(%rsp),%rax
  ba3b6c:	lea    0x1050(%rsp),%rdi
  ba3b74:	cmovae 0x1048(%rsp),%rax
  ba3b7d:	movq   $0x0,0xfa0(%rsp)
  ba3b89:	mov    $0x5,%esi
  ba3b8e:	movl   $0x0,(%rax)
  ba3b94:	movq   $0x20,0x1058(%rsp)
  ba3ba0:	movq   $0x0,0x1060(%rsp)
  ba3bac:	movq   $0x0,0x1070(%rsp)
  ba3bb8:	movq   $0x0,0x1068(%rsp)
  ba3bc4:	movq   $0x0,0x10f8(%rsp)
  ba3bd0:	movq   $0x0,0x1050(%rsp)
  ba3bdc:	movl   $0x0,0x1078(%rsp)
  ba3be7:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3bec:	cmpq   $0x20,0x1058(%rsp)
  ba3bf5:	ja     ba3e03 <_ZN8CPetMenu12updateLayoutEv+0x1753>
  ba3bfb:	lea    0x1050(%rsp),%rdx
  ba3c03:	add    $0x28,%rdx
  ba3c07:	mov    $0xfd0c0d,%eax
  ba3c0c:	nopl   0x0(%rax)
  ba3c10:	movzbl (%rax),%ecx
  ba3c13:	add    $0x1,%rax
  ba3c17:	mov    %ecx,(%rdx)
  ba3c19:	add    $0x4,%rdx
  ba3c1d:	cmp    $0xfd0c12,%rax
  ba3c23:	jne    ba3c10 <_ZN8CPetMenu12updateLayoutEv+0x1560>
  ba3c25:	cmpq   $0x20,0x1058(%rsp)
  ba3c2e:	movq   $0x5,0x1050(%rsp)
  ba3c3a:	mov    0x58(%rsp),%rax
  ba3c3f:	jbe    ba3c4d <_ZN8CPetMenu12updateLayoutEv+0x159d>
  ba3c41:	mov    0x10f8(%rsp),%rax
  ba3c49:	add    $0x14,%rax
  ba3c4d:	movl   $0x0,(%rax)
  ba3c53:	mov    0x1378(%rbp),%rdi
  ba3c5a:	lea    0xfa0(%rsp),%rdx
  ba3c62:	lea    0x1050(%rsp),%rsi
  ba3c6a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba3c6f:	lea    0x1050(%rsp),%rdi
  ba3c77:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3c7c:	lea    0xfa0(%rsp),%rdi
  ba3c84:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3c89:	cmpq   $0x0,0x30(%rsp)
  ba3c8f:	je     ba3dbe <_ZN8CPetMenu12updateLayoutEv+0x170e>
  ba3c95:	mov    0x30(%rsp),%rdi
  ba3c9a:	lea    0x21c0(%rsp),%rsi
  ba3ca2:	movl   $0x0,0x21c4(%rsp)
  ba3cad:	movl   $0x0,0x21c0(%rsp)
  ba3cb8:	movl   $0x3f800000,0x21cc(%rsp)
  ba3cc3:	movl   $0x0,0x21c8(%rsp)
  ba3cce:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  ba3cd3:	mov    0x30(%rsp),%rdi
  ba3cd8:	lea    0x21b0(%rsp),%rsi
  ba3ce0:	movl   $0x0,0x21b4(%rsp)
  ba3ceb:	movl   $0x0,0x21b0(%rsp)
  ba3cf6:	movl   $0x0,0x21bc(%rsp)
  ba3d01:	movl   $0x0,0x21b8(%rsp)
  ba3d0c:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  ba3d11:	lea    0x21a0(%rsp),%rbx
  ba3d19:	mov    0x1378(%rbp),%rsi
  ba3d20:	mov    %rbx,%rdi
  ba3d23:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  ba3d28:	xorps  %xmm0,%xmm0
  ba3d2b:	xorps  %xmm1,%xmm1
  ba3d2e:	mulss  0x21a0(%rsp),%xmm0
  ba3d37:	ucomiss %xmm1,%xmm0
  ba3d3a:	ja     ba4191 <_ZN8CPetMenu12updateLayoutEv+0x1ae1>
  ba3d40:	movss  0x21a4(%rsp),%xmm2
  ba3d49:	movss  0x4049a3(%rip),%xmm1        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  ba3d51:	addss  %xmm1,%xmm0
  ba3d55:	movss  0x42a73b(%rip),%xmm1        # fce498 <_ZTV18iInventoryListener+0x58>
  ba3d5d:	mov    0x30(%rsp),%rdi
  ba3d62:	mov    %rbx,%rsi
  ba3d65:	movl   $0x0,0x21a8(%rsp)
  ba3d70:	movl   $0x0,0x21a0(%rsp)
  ba3d7b:	cvttss2si %xmm0,%eax
  ba3d7f:	cvtsi2ss %eax,%xmm0
  ba3d83:	addss  %xmm2,%xmm0
  ba3d87:	mulss  %xmm0,%xmm1
  ba3d8b:	movss  %xmm0,0x21a4(%rsp)
  ba3d94:	movss  %xmm1,0x21ac(%rsp)
  ba3d9d:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  ba3da2:	mov    0x30(%rsp),%rdi
  ba3da7:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba3dac:	mov    0x30(%rsp),%rdi
  ba3db1:	movss  0x400a6f(%rip),%xmm0        # fa4828 <_ZTVN4Ogre13FrameListenerE+0x68>
  ba3db9:	call   553278 <_ZN5CEGUI6Window6updateEf@plt>
  ba3dbe:	lea    0xef0(%rsp),%rbx
  ba3dc6:	mov    $0x10257f7,%esi
  ba3dcb:	mov    %rbx,%rdi
  ba3dce:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  ba3dd3:	mov    0x1378(%rbp),%rdi
  ba3dda:	mov    %rbx,%rsi
  ba3ddd:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  ba3de2:	mov    %rbx,%rdi
  ba3de5:	add    $0x8,%rbp
  ba3de9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba3dee:	addl   $0x1,0x38(%rsp)
  ba3df3:	cmpl   $0xc,0x38(%rsp)
  ba3df8:	jne    ba27c8 <_ZN8CPetMenu12updateLayoutEv+0x118>
  ba3dfe:	jmp    ba3150 <_ZN8CPetMenu12updateLayoutEv+0xaa0>
  ba3e03:	mov    0x10f8(%rsp),%rdx
  ba3e0b:	jmp    ba3c07 <_ZN8CPetMenu12updateLayoutEv+0x1557>
  ba3e10:	mov    0x0(%r13),%rax
  ba3e14:	mov    %r13,%rdi
  ba3e17:	call   *0x2b0(%rax)
  ba3e1d:	test   %al,%al
  ba3e1f:	je     ba41a7 <_ZN8CPetMenu12updateLayoutEv+0x1af7>
  ba3e25:	mov    $0x37,%esi
  ba3e2a:	mov    %r13,%rdi
  ba3e2d:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  ba3e32:	test   %al,%al
  ba3e34:	je     ba4564 <_ZN8CPetMenu12updateLayoutEv+0x1eb4>
  ba3e3a:	lea    0x15d0(%rsp),%r12
  ba3e42:	mov    $0xc,%esi
  ba3e47:	movq   $0x20,0x15d8(%rsp)
  ba3e53:	movq   $0x0,0x15e0(%rsp)
  ba3e5f:	movq   $0x0,0x15f0(%rsp)
  ba3e6b:	mov    %r12,%rdi
  ba3e6e:	movq   $0x0,0x15e8(%rsp)
  ba3e7a:	movq   $0x0,0x1678(%rsp)
  ba3e86:	movq   $0x0,0x15d0(%rsp)
  ba3e92:	movl   $0x0,0x15f8(%rsp)
  ba3e9d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3ea2:	cmpq   $0x20,0x15d8(%rsp)
  ba3eab:	lea    0x28(%r12),%rdx
  ba3eb0:	jbe    ba3eba <_ZN8CPetMenu12updateLayoutEv+0x180a>
  ba3eb2:	mov    0x1678(%rsp),%rdx
  ba3eba:	mov    $0xfe60a8,%eax
  ba3ebf:	nop
  ba3ec0:	movzbl (%rax),%ecx
  ba3ec3:	add    $0x1,%rax
  ba3ec7:	mov    %ecx,(%rdx)
  ba3ec9:	add    $0x4,%rdx
  ba3ecd:	cmp    $0xfe60b4,%rax
  ba3ed3:	jne    ba3ec0 <_ZN8CPetMenu12updateLayoutEv+0x1810>
  ba3ed5:	cmpq   $0x20,0x15d8(%rsp)
  ba3ede:	movq   $0xc,0x15d0(%rsp)
  ba3eea:	lea    0x58(%r12),%rax
  ba3eef:	jbe    ba3efd <_ZN8CPetMenu12updateLayoutEv+0x184d>
  ba3ef1:	mov    0x1678(%rsp),%rax
  ba3ef9:	add    $0x30,%rax
  ba3efd:	movl   $0x0,(%rax)
  ba3f03:	mov    0x9108(%r15),%rdi
  ba3f0a:	mov    %r12,%rsi
  ba3f0d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba3f12:	lea    0x1520(%rsp),%r13
  ba3f1a:	mov    %rax,%rsi
  ba3f1d:	mov    %r13,%rdi
  ba3f20:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba3f25:	lea    0x1470(%rsp),%rbx
  ba3f2d:	mov    $0x5,%esi
  ba3f32:	movq   $0x20,0x1478(%rsp)
  ba3f3e:	movq   $0x0,0x1480(%rsp)
  ba3f4a:	movq   $0x0,0x1490(%rsp)
  ba3f56:	mov    %rbx,%rdi
  ba3f59:	movq   $0x0,0x1488(%rsp)
  ba3f65:	movq   $0x0,0x1518(%rsp)
  ba3f71:	movq   $0x0,0x1470(%rsp)
  ba3f7d:	movl   $0x0,0x1498(%rsp)
  ba3f88:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba3f8d:	cmpq   $0x20,0x1478(%rsp)
  ba3f96:	lea    0x28(%rbx),%rdx
  ba3f9a:	jbe    ba3fa4 <_ZN8CPetMenu12updateLayoutEv+0x18f4>
  ba3f9c:	mov    0x1518(%rsp),%rdx
  ba3fa4:	mov    $0xfd0c0d,%eax
  ba3fa9:	nopl   0x0(%rax)
  ba3fb0:	movzbl (%rax),%ecx
  ba3fb3:	add    $0x1,%rax
  ba3fb7:	mov    %ecx,(%rdx)
  ba3fb9:	add    $0x4,%rdx
  ba3fbd:	cmp    $0xfd0c12,%rax
  ba3fc3:	jne    ba3fb0 <_ZN8CPetMenu12updateLayoutEv+0x1900>
  ba3fc5:	cmpq   $0x20,0x1478(%rsp)
  ba3fce:	movq   $0x5,0x1470(%rsp)
  ba3fda:	lea    0x3c(%rbx),%rax
  ba3fde:	jbe    ba3fec <_ZN8CPetMenu12updateLayoutEv+0x193c>
  ba3fe0:	mov    0x1518(%rsp),%rax
  ba3fe8:	add    $0x14,%rax
  ba3fec:	movl   $0x0,(%rax)
  ba3ff2:	mov    0x1898(%rbp),%rdi
  ba3ff9:	mov    %r13,%rdx
  ba3ffc:	mov    %rbx,%rsi
  ba3fff:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4004:	mov    %rbx,%rdi
  ba4007:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba400c:	mov    %r13,%rdi
  ba400f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4014:	jmp    ba3af4 <_ZN8CPetMenu12updateLayoutEv+0x1444>
  ba4019:	lea    0x1890(%rsp),%r12
  ba4021:	xor    %esi,%esi
  ba4023:	movq   $0x20,0x1898(%rsp)
  ba402f:	movq   $0x0,0x18a0(%rsp)
  ba403b:	movq   $0x0,0x18b0(%rsp)
  ba4047:	mov    %r12,%rdi
  ba404a:	movq   $0x0,0x18a8(%rsp)
  ba4056:	movq   $0x0,0x1938(%rsp)
  ba4062:	movq   $0x0,0x1890(%rsp)
  ba406e:	movl   $0x0,0x18b8(%rsp)
  ba4079:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba407e:	cmpq   $0x20,0x1898(%rsp)
  ba4087:	movq   $0x0,0x1890(%rsp)
  ba4093:	lea    0x28(%r12),%rax
  ba4098:	jbe    ba40a2 <_ZN8CPetMenu12updateLayoutEv+0x19f2>
  ba409a:	mov    0x1938(%rsp),%rax
  ba40a2:	lea    0x1940(%rsp),%rbx
  ba40aa:	movl   $0x0,(%rax)
  ba40b0:	mov    $0x5,%esi
  ba40b5:	movq   $0x20,0x1948(%rsp)
  ba40c1:	movq   $0x0,0x1950(%rsp)
  ba40cd:	mov    %rbx,%rdi
  ba40d0:	movq   $0x0,0x1960(%rsp)
  ba40dc:	movq   $0x0,0x1958(%rsp)
  ba40e8:	movq   $0x0,0x19e8(%rsp)
  ba40f4:	movq   $0x0,0x1940(%rsp)
  ba4100:	movl   $0x0,0x1968(%rsp)
  ba410b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba4110:	cmpq   $0x20,0x1948(%rsp)
  ba4119:	lea    0x28(%rbx),%rdx
  ba411d:	jbe    ba4127 <_ZN8CPetMenu12updateLayoutEv+0x1a77>
  ba411f:	mov    0x19e8(%rsp),%rdx
  ba4127:	mov    $0xfd0c0d,%eax
  ba412c:	nopl   0x0(%rax)
  ba4130:	movzbl (%rax),%ecx
  ba4133:	add    $0x1,%rax
  ba4137:	mov    %ecx,(%rdx)
  ba4139:	add    $0x4,%rdx
  ba413d:	cmp    $0xfd0c12,%rax
  ba4143:	jne    ba4130 <_ZN8CPetMenu12updateLayoutEv+0x1a80>
  ba4145:	cmpq   $0x20,0x1948(%rsp)
  ba414e:	movq   $0x5,0x1940(%rsp)
  ba415a:	lea    0x3c(%rbx),%rax
  ba415e:	jbe    ba416c <_ZN8CPetMenu12updateLayoutEv+0x1abc>
  ba4160:	mov    0x19e8(%rsp),%rax
  ba4168:	add    $0x14,%rax
  ba416c:	movl   $0x0,(%rax)
  ba4172:	mov    0x1608(%rbp),%rdi
  ba4179:	mov    %r12,%rdx
  ba417c:	mov    %rbx,%rsi
  ba417f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4184:	mov    %rbx,%rdi
  ba4187:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba418c:	jmp    ba2c6e <_ZN8CPetMenu12updateLayoutEv+0x5be>
  ba4191:	movss  0x21a4(%rsp),%xmm2
  ba419a:	movss  0x40066e(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  ba41a2:	jmp    ba3d51 <_ZN8CPetMenu12updateLayoutEv+0x16a1>
  ba41a7:	lea    0x1100(%rsp),%r12
  ba41af:	xor    %esi,%esi
  ba41b1:	movq   $0x20,0x1108(%rsp)
  ba41bd:	movq   $0x0,0x1110(%rsp)
  ba41c9:	movq   $0x0,0x1120(%rsp)
  ba41d5:	mov    %r12,%rdi
  ba41d8:	movq   $0x0,0x1118(%rsp)
  ba41e4:	movq   $0x0,0x11a8(%rsp)
  ba41f0:	movq   $0x0,0x1100(%rsp)
  ba41fc:	movl   $0x0,0x1128(%rsp)
  ba4207:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba420c:	cmpq   $0x20,0x1108(%rsp)
  ba4215:	movq   $0x0,0x1100(%rsp)
  ba4221:	lea    0x28(%r12),%rax
  ba4226:	jbe    ba4230 <_ZN8CPetMenu12updateLayoutEv+0x1b80>
  ba4228:	mov    0x11a8(%rsp),%rax
  ba4230:	lea    0x11b0(%rsp),%rbx
  ba4238:	movl   $0x0,(%rax)
  ba423e:	mov    $0x5,%esi
  ba4243:	movq   $0x20,0x11b8(%rsp)
  ba424f:	movq   $0x0,0x11c0(%rsp)
  ba425b:	mov    %rbx,%rdi
  ba425e:	movq   $0x0,0x11d0(%rsp)
  ba426a:	movq   $0x0,0x11c8(%rsp)
  ba4276:	movq   $0x0,0x1258(%rsp)
  ba4282:	movq   $0x0,0x11b0(%rsp)
  ba428e:	movl   $0x0,0x11d8(%rsp)
  ba4299:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba429e:	cmpq   $0x20,0x11b8(%rsp)
  ba42a7:	lea    0x28(%rbx),%rdx
  ba42ab:	ja     ba4557 <_ZN8CPetMenu12updateLayoutEv+0x1ea7>
  ba42b1:	mov    $0xfd0c0d,%eax
  ba42b6:	cs nopw 0x0(%rax,%rax,1)
  ba42c0:	movzbl (%rax),%ecx
  ba42c3:	add    $0x1,%rax
  ba42c7:	mov    %ecx,(%rdx)
  ba42c9:	add    $0x4,%rdx
  ba42cd:	cmp    $0xfd0c12,%rax
  ba42d3:	jne    ba42c0 <_ZN8CPetMenu12updateLayoutEv+0x1c10>
  ba42d5:	cmpq   $0x20,0x11b8(%rsp)
  ba42de:	movq   $0x5,0x11b0(%rsp)
  ba42ea:	lea    0x3c(%rbx),%rax
  ba42ee:	jbe    ba42fc <_ZN8CPetMenu12updateLayoutEv+0x1c4c>
  ba42f0:	mov    0x1258(%rsp),%rax
  ba42f8:	add    $0x14,%rax
  ba42fc:	movl   $0x0,(%rax)
  ba4302:	mov    0x1898(%rbp),%rdi
  ba4309:	mov    %r12,%rdx
  ba430c:	mov    %rbx,%rsi
  ba430f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4314:	mov    %rbx,%rdi
  ba4317:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba431c:	jmp    ba3af4 <_ZN8CPetMenu12updateLayoutEv+0x1444>
  ba4321:	mov    0x1d58(%rsp),%rdx
  ba4329:	jmp    ba29f1 <_ZN8CPetMenu12updateLayoutEv+0x341>
  ba432e:	mov    0x1378(%rbp),%rax
  ba4335:	xor    %esi,%esi
  ba4337:	mov    0xb0(%rax),%rdi
  ba433e:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  ba4343:	test   %al,%al
  ba4345:	je     ba28e9 <_ZN8CPetMenu12updateLayoutEv+0x239>
  ba434b:	cmpl   $0x1,0x3e0(%r13)
  ba4353:	jbe    ba4940 <_ZN8CPetMenu12updateLayoutEv+0x2290>
  ba4359:	lea    0x20d0(%rsp),%r12
  ba4361:	mov    $0xd,%esi
  ba4366:	movq   $0x20,0x20d8(%rsp)
  ba4372:	movq   $0x0,0x20e0(%rsp)
  ba437e:	movq   $0x0,0x20f0(%rsp)
  ba438a:	mov    %r12,%rdi
  ba438d:	movq   $0x0,0x20e8(%rsp)
  ba4399:	movq   $0x0,0x2178(%rsp)
  ba43a5:	movq   $0x0,0x20d0(%rsp)
  ba43b1:	movl   $0x0,0x20f8(%rsp)
  ba43bc:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba43c1:	cmpq   $0x20,0x20d8(%rsp)
  ba43ca:	lea    0x28(%r12),%rdx
  ba43cf:	jbe    ba43d9 <_ZN8CPetMenu12updateLayoutEv+0x1d29>
  ba43d1:	mov    0x2178(%rsp),%rdx
  ba43d9:	mov    $0xfe60c3,%eax
  ba43de:	xchg   %ax,%ax
  ba43e0:	movzbl (%rax),%ecx
  ba43e3:	add    $0x1,%rax
  ba43e7:	mov    %ecx,(%rdx)
  ba43e9:	add    $0x4,%rdx
  ba43ed:	cmp    $0xfe60d0,%rax
  ba43f3:	jne    ba43e0 <_ZN8CPetMenu12updateLayoutEv+0x1d30>
  ba43f5:	cmpq   $0x20,0x20d8(%rsp)
  ba43fe:	movq   $0xd,0x20d0(%rsp)
  ba440a:	lea    0x5c(%r12),%rax
  ba440f:	jbe    ba441d <_ZN8CPetMenu12updateLayoutEv+0x1d6d>
  ba4411:	mov    0x2178(%rsp),%rax
  ba4419:	add    $0x34,%rax
  ba441d:	movl   $0x0,(%rax)
  ba4423:	mov    0x9108(%r15),%rdi
  ba442a:	mov    %r12,%rsi
  ba442d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba4432:	lea    0x2020(%rsp),%rdi
  ba443a:	mov    %rax,%rsi
  ba443d:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba4442:	lea    0x1f70(%rsp),%rbx
  ba444a:	mov    $0x5,%esi
  ba444f:	movq   $0x20,0x1f78(%rsp)
  ba445b:	movq   $0x0,0x1f80(%rsp)
  ba4467:	movq   $0x0,0x1f90(%rsp)
  ba4473:	mov    %rbx,%rdi
  ba4476:	movq   $0x0,0x1f88(%rsp)
  ba4482:	movq   $0x0,0x2018(%rsp)
  ba448e:	movq   $0x0,0x1f70(%rsp)
  ba449a:	movl   $0x0,0x1f98(%rsp)
  ba44a5:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba44aa:	cmpq   $0x20,0x1f78(%rsp)
  ba44b3:	lea    0x28(%rbx),%rdx
  ba44b7:	jbe    ba44c1 <_ZN8CPetMenu12updateLayoutEv+0x1e11>
  ba44b9:	mov    0x2018(%rsp),%rdx
  ba44c1:	mov    $0xfd0c0d,%eax
  ba44c6:	cs nopw 0x0(%rax,%rax,1)
  ba44d0:	movzbl (%rax),%ecx
  ba44d3:	add    $0x1,%rax
  ba44d7:	mov    %ecx,(%rdx)
  ba44d9:	add    $0x4,%rdx
  ba44dd:	cmp    $0xfd0c12,%rax
  ba44e3:	jne    ba44d0 <_ZN8CPetMenu12updateLayoutEv+0x1e20>
  ba44e5:	cmpq   $0x20,0x1f78(%rsp)
  ba44ee:	movq   $0x5,0x1f70(%rsp)
  ba44fa:	lea    0x3c(%rbx),%rax
  ba44fe:	jbe    ba450c <_ZN8CPetMenu12updateLayoutEv+0x1e5c>
  ba4500:	mov    0x2018(%rsp),%rax
  ba4508:	add    $0x14,%rax
  ba450c:	movl   $0x0,(%rax)
  ba4512:	mov    0x1b28(%rbp),%rdi
  ba4519:	lea    0x2020(%rsp),%rdx
  ba4521:	mov    %rbx,%rsi
  ba4524:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4529:	mov    %rbx,%rdi
  ba452c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4531:	lea    0x2020(%rsp),%rdi
  ba4539:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba453e:	mov    %r12,%rdi
  ba4541:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4546:	mov    0x1b28(%rbp),%rdi
  ba454d:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  ba4552:	jmp    ba2a79 <_ZN8CPetMenu12updateLayoutEv+0x3c9>
  ba4557:	mov    0x1258(%rsp),%rdx
  ba455f:	jmp    ba42b1 <_ZN8CPetMenu12updateLayoutEv+0x1c01>
  ba4564:	lea    0x13c0(%rsp),%r12
  ba456c:	mov    $0xd,%esi
  ba4571:	movq   $0x20,0x13c8(%rsp)
  ba457d:	movq   $0x0,0x13d0(%rsp)
  ba4589:	movq   $0x0,0x13e0(%rsp)
  ba4595:	mov    %r12,%rdi
  ba4598:	movq   $0x0,0x13d8(%rsp)
  ba45a4:	movq   $0x0,0x1468(%rsp)
  ba45b0:	movq   $0x0,0x13c0(%rsp)
  ba45bc:	movl   $0x0,0x13e8(%rsp)
  ba45c7:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba45cc:	cmpq   $0x20,0x13c8(%rsp)
  ba45d5:	lea    0x28(%r12),%rdx
  ba45da:	jbe    ba45e4 <_ZN8CPetMenu12updateLayoutEv+0x1f34>
  ba45dc:	mov    0x1468(%rsp),%rdx
  ba45e4:	mov    $0xfe60b5,%eax
  ba45e9:	nopl   0x0(%rax)
  ba45f0:	movzbl (%rax),%ecx
  ba45f3:	add    $0x1,%rax
  ba45f7:	mov    %ecx,(%rdx)
  ba45f9:	add    $0x4,%rdx
  ba45fd:	cmp    $0xfe60c2,%rax
  ba4603:	jne    ba45f0 <_ZN8CPetMenu12updateLayoutEv+0x1f40>
  ba4605:	cmpq   $0x20,0x13c8(%rsp)
  ba460e:	movq   $0xd,0x13c0(%rsp)
  ba461a:	lea    0x5c(%r12),%rax
  ba461f:	jbe    ba462d <_ZN8CPetMenu12updateLayoutEv+0x1f7d>
  ba4621:	mov    0x1468(%rsp),%rax
  ba4629:	add    $0x34,%rax
  ba462d:	movl   $0x0,(%rax)
  ba4633:	mov    0x9108(%r15),%rdi
  ba463a:	mov    %r12,%rsi
  ba463d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba4642:	lea    0x1310(%rsp),%r13
  ba464a:	mov    %rax,%rsi
  ba464d:	mov    %r13,%rdi
  ba4650:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba4655:	lea    0x1260(%rsp),%rbx
  ba465d:	mov    $0x5,%esi
  ba4662:	movq   $0x20,0x1268(%rsp)
  ba466e:	movq   $0x0,0x1270(%rsp)
  ba467a:	movq   $0x0,0x1280(%rsp)
  ba4686:	mov    %rbx,%rdi
  ba4689:	movq   $0x0,0x1278(%rsp)
  ba4695:	movq   $0x0,0x1308(%rsp)
  ba46a1:	movq   $0x0,0x1260(%rsp)
  ba46ad:	movl   $0x0,0x1288(%rsp)
  ba46b8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  ba46bd:	cmpq   $0x20,0x1268(%rsp)
  ba46c6:	lea    0x28(%rbx),%rdx
  ba46ca:	jbe    ba46d4 <_ZN8CPetMenu12updateLayoutEv+0x2024>
  ba46cc:	mov    0x1308(%rsp),%rdx
  ba46d4:	mov    $0xfd0c0d,%eax
  ba46d9:	nopl   0x0(%rax)
  ba46e0:	movzbl (%rax),%ecx
  ba46e3:	add    $0x1,%rax
  ba46e7:	mov    %ecx,(%rdx)
  ba46e9:	add    $0x4,%rdx
  ba46ed:	cmp    $0xfd0c12,%rax
  ba46f3:	jne    ba46e0 <_ZN8CPetMenu12updateLayoutEv+0x2030>
  ba46f5:	cmpq   $0x20,0x1268(%rsp)
  ba46fe:	movq   $0x5,0x1260(%rsp)
  ba470a:	lea    0x3c(%rbx),%rax
  ba470e:	jbe    ba471c <_ZN8CPetMenu12updateLayoutEv+0x206c>
  ba4710:	mov    0x1308(%rsp),%rax
  ba4718:	add    $0x14,%rax
  ba471c:	movl   $0x0,(%rax)
  ba4722:	mov    0x1898(%rbp),%rdi
  ba4729:	mov    %r13,%rdx
  ba472c:	mov    %rbx,%rsi
  ba472f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4734:	mov    %rbx,%rdi
  ba4737:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba473c:	mov    %r13,%rdi
  ba473f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4744:	jmp    ba3af4 <_ZN8CPetMenu12updateLayoutEv+0x1444>
  ba4749:	xor    %ebx,%ebx
  ba474b:	mov    %rdx,%rbp
  ba474e:	jmp    ba4793 <_ZN8CPetMenu12updateLayoutEv+0x20e3>
  ba4750:	mov    0x30(%rbp),%rcx
  ba4754:	mov    (%rcx),%rax
  ba4757:	mov    0x10(%rax),%r12
  ba475b:	cmpl   $0x12,0x18(%rax)
  ba475f:	jle    ba4787 <_ZN8CPetMenu12updateLayoutEv+0x20d7>
  ba4761:	cmp    %ebx,%edx
  ba4763:	jbe    ba476f <_ZN8CPetMenu12updateLayoutEv+0x20bf>
  ba4765:	mov    %ebx,%ecx
  ba4767:	shl    $0x3,%rcx
  ba476b:	add    0x30(%rbp),%rcx
  ba476f:	mov    (%rcx),%rax
  ba4772:	mov    %rbp,%rdi
  ba4775:	mov    0x18(%rax),%esi
  ba4778:	call   91b1c0 <_ZN10CInventory11getItemPaneEj>
  ba477d:	cmp    0x6c(%r15),%eax
  ba4781:	je     ba49c8 <_ZN8CPetMenu12updateLayoutEv+0x2318>
  ba4787:	add    $0x1,%ebx
  ba478a:	cmp    0x38(%rbp),%ebx
  ba478d:	jae    ba389b <_ZN8CPetMenu12updateLayoutEv+0x11eb>
  ba4793:	mov    0x3c(%rbp),%edx
  ba4796:	cmp    %ebx,%edx
  ba4798:	jbe    ba4750 <_ZN8CPetMenu12updateLayoutEv+0x20a0>
  ba479a:	mov    0x30(%rbp),%rcx
  ba479e:	mov    %ebx,%eax
  ba47a0:	mov    (%rcx,%rax,8),%rax
  ba47a4:	mov    0x10(%rax),%r12
  ba47a8:	jmp    ba475b <_ZN8CPetMenu12updateLayoutEv+0x20ab>
  ba47aa:	mov    %r12,%rdi
  ba47ad:	call   c9ce10 <_ZN6CSkill12getSkillIconEv>
  ba47b2:	mov    (%rax),%rsi
  ba47b5:	lea    0x2230(%rsp),%rdi
  ba47bd:	call   c8e350 <_ZN7STRINGS21StringConvertToNarrowEPKw>
  ba47c2:	mov    0x90(%r15),%rdi
  ba47c9:	mov    0x2230(%rsp),%rsi
  ba47d1:	call   a98630 <_ZN7CGameUI20getImageFromImageSetEPKh>
  ba47d6:	lea    0x8c0(%rsp),%rdi
  ba47de:	mov    %rax,%rsi
  ba47e1:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba47e6:	lea    0x810(%rsp),%rdi
  ba47ee:	mov    $0xfd0c0d,%esi
  ba47f3:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba47f8:	mov    0x1040(%rbx),%rdi
  ba47ff:	lea    0x8c0(%rsp),%rdx
  ba4807:	lea    0x810(%rsp),%rsi
  ba480f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba4814:	lea    0x810(%rsp),%rdi
  ba481c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4821:	lea    0x8c0(%rsp),%rdi
  ba4829:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba482e:	mov    0x2230(%rsp),%rdi
  ba4836:	sub    $0x18,%rdi
  ba483a:	cmp    $0x1423a20,%rdi
  ba4841:	jne    ba502b <_ZN8CPetMenu12updateLayoutEv+0x297b>
  ba4847:	mov    0x150(%r12),%rax
  ba484f:	mov    0x1040(%rbx),%rdx
  ba4856:	mov    $0x14cd020,%esi
  ba485b:	mov    %r13,%rdi
  ba485e:	mov    %rax,0x1050(%rbx)
  ba4865:	mov    %ebp,%eax
  ba4867:	lea    0x1050(%r15,%rax,8),%rax
  ba486f:	mov    %rax,0x1d8(%rdx)
  ba4876:	call   5529a8 <_ZNSsC1ERKSs@plt>
  ba487b:	mov    $0x1,%edx
  ba4880:	mov    $0xfa04e8,%esi
  ba4885:	mov    %r13,%rdi
  ba4888:	call   554128 <_ZNSs6appendEPKcm@plt>
  ba488d:	lea    0x2210(%rsp),%rdi
  ba4895:	mov    $0x14cd018,%edx
  ba489a:	mov    %r13,%rsi
  ba489d:	call   56af70 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_ERKS6_S8_>
  ba48a2:	mov    0x2210(%rsp),%rsi
  ba48aa:	lea    0x760(%rsp),%rdi
  ba48b2:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  ba48b7:	mov    0x1040(%rbx),%rdi
  ba48be:	lea    0x760(%rsp),%rsi
  ba48c6:	call   554b48 <_ZN5CEGUI6Window14setTooltipTextERKNS_6StringE@plt>
  ba48cb:	lea    0x760(%rsp),%rdi
  ba48d3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba48d8:	mov    0x2210(%rsp),%rdi
  ba48e0:	mov    $0x1423a20,%edx
  ba48e5:	sub    $0x18,%rdi
  ba48e9:	cmp    %rdi,%rdx
  ba48ec:	jne    ba50ac <_ZN8CPetMenu12updateLayoutEv+0x29fc>
  ba48f2:	mov    0x2220(%rsp),%rdi
  ba48fa:	mov    $0x1423a20,%eax
  ba48ff:	sub    $0x18,%rdi
  ba4903:	cmp    %rdi,%rax
  ba4906:	je     ba3333 <_ZN8CPetMenu12updateLayoutEv+0xc83>
  ba490c:	mov    $0x5541c8,%eax
  ba4911:	test   %rax,%rax
  ba4914:	je     ba50e8 <_ZN8CPetMenu12updateLayoutEv+0x2a38>
  ba491a:	or     $0xffffffff,%eax
  ba491d:	lock xadd %eax,0x10(%rdi)
  ba4922:	test   %eax,%eax
  ba4924:	jg     ba3333 <_ZN8CPetMenu12updateLayoutEv+0xc83>
  ba492a:	lea    0x22a7(%rsp),%rsi
  ba4932:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba4937:	jmp    ba3333 <_ZN8CPetMenu12updateLayoutEv+0xc83>
  ba493c:	nopl   0x0(%rax)
  ba4940:	jne    ba4546 <_ZN8CPetMenu12updateLayoutEv+0x1e96>
  ba4946:	lea    0x1ec0(%rsp),%rdi
  ba494e:	mov    $0xfe60d1,%esi
  ba4953:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba4958:	mov    0x9108(%r15),%rdi
  ba495f:	lea    0x1ec0(%rsp),%rsi
  ba4967:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  ba496c:	lea    0x1e10(%rsp),%r12
  ba4974:	mov    %rax,%rsi
  ba4977:	mov    %r12,%rdi
  ba497a:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  ba497f:	lea    0x1d60(%rsp),%rbx
  ba4987:	mov    $0xfd0c0d,%esi
  ba498c:	mov    %rbx,%rdi
  ba498f:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  ba4994:	mov    0x1b28(%rbp),%rdi
  ba499b:	mov    %r12,%rdx
  ba499e:	mov    %rbx,%rsi
  ba49a1:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  ba49a6:	mov    %rbx,%rdi
  ba49a9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba49ae:	mov    %r12,%rdi
  ba49b1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba49b6:	lea    0x1ec0(%rsp),%rdi
  ba49be:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba49c3:	jmp    ba4546 <_ZN8CPetMenu12updateLayoutEv+0x1e96>
  ba49c8:	cmp    %ebx,0x3c(%rbp)
  ba49cb:	ja     ba49e9 <_ZN8CPetMenu12updateLayoutEv+0x2339>
  ba49cd:	mov    0x30(%rbp),%rax
  ba49d1:	mov    (%rax),%rax
  ba49d4:	mov    %r12,%rsi
  ba49d7:	mov    %r15,%rdi
  ba49da:	mov    0x18(%rax),%edx
  ba49dd:	mov    %edx,%ecx
  ba49df:	call   ba16b0 <_ZN8CPetMenu11setSlotIconEP10CEquipmentii>
  ba49e4:	jmp    ba4787 <_ZN8CPetMenu12updateLayoutEv+0x20d7>
  ba49e9:	mov    %ebx,%eax
  ba49eb:	shl    $0x3,%rax
  ba49ef:	add    0x30(%rbp),%rax
  ba49f3:	jmp    ba49d1 <_ZN8CPetMenu12updateLayoutEv+0x2321>
  ba49f5:	mov    0x1ca8(%rsp),%rax
  ba49fd:	jmp    ba296b <_ZN8CPetMenu12updateLayoutEv+0x2bb>
  ba4a02:	mov    $0x14cd000,%edi
  ba4a07:	call   553558 <__cxa_guard_acquire@plt>
  ba4a0c:	test   %eax,%eax
  ba4a0e:	je     ba31a3 <_ZN8CPetMenu12updateLayoutEv+0xaf3>
  ba4a14:	mov    $0x14cd000,%edi
  ba4a19:	movq   $0x1423a38,0x9285f4(%rip)        # 14cd018 <_ZZN8CPetMenu12updateLayoutEvE15g_RemoveASpell2>
  ba4a24:	call   553fc8 <__cxa_guard_release@plt>
  ba4a29:	mov    $0xf9f788,%edx
  ba4a2e:	mov    $0x14cd018,%esi
  ba4a33:	mov    $0x556288,%edi
  ba4a38:	call   5551e8 <__cxa_atexit@plt>
  ba4a3d:	jmp    ba31a3 <_ZN8CPetMenu12updateLayoutEv+0xaf3>
  ba4a42:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  ba4a47:	lea    0x2290(%rsp),%rdi
  ba4a4f:	mov    %rax,%rsi
  ba4a52:	mov    $0xfef848,%edx
  ba4a57:	lea    0x2280(%rsp),%r12
  ba4a5f:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  ba4a64:	mov    0x2290(%rsp),%rsi
  ba4a6c:	mov    %r12,%rdi
  ba4a6f:	call   c8e350 <_ZN7STRINGS21StringConvertToNarrowEPKw>
  ba4a74:	mov    %r12,%rsi
  ba4a77:	mov    $0x14cd020,%edi
  ba4a7c:	call   554d18 <_ZNSs6assignERKSs@plt>
  ba4a81:	mov    0x2280(%rsp),%rdi
  ba4a89:	sub    $0x18,%rdi
  ba4a8d:	cmp    $0x1423a20,%rdi
  ba4a94:	jne    ba4c4a <_ZN8CPetMenu12updateLayoutEv+0x259a>
  ba4a9a:	mov    0x2290(%rsp),%rdi
  ba4aa2:	sub    $0x18,%rdi
  ba4aa6:	cmp    $0x1424540,%rdi
  ba4aad:	je     ba3196 <_ZN8CPetMenu12updateLayoutEv+0xae6>
  ba4ab3:	mov    $0x5541c8,%eax
  ba4ab8:	test   %rax,%rax
  ba4abb:	je     ba516f <_ZN8CPetMenu12updateLayoutEv+0x2abf>
  ba4ac1:	or     $0xffffffff,%eax
  ba4ac4:	lock xadd %eax,0x10(%rdi)
  ba4ac9:	test   %eax,%eax
  ba4acb:	jg     ba3196 <_ZN8CPetMenu12updateLayoutEv+0xae6>
  ba4ad1:	lea    0x22ae(%rsp),%rsi
  ba4ad9:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  ba4ade:	jmp    ba3196 <_ZN8CPetMenu12updateLayoutEv+0xae6>
  ba4ae3:	mov    $0x14ccff8,%edi
  ba4ae8:	call   553558 <__cxa_guard_acquire@plt>
  ba4aed:	test   %eax,%eax
  ba4aef:	je     ba3184 <_ZN8CPetMenu12updateLayoutEv+0xad4>
  ba4af5:	mov    $0x14ccff8,%edi
  ba4afa:	movq   $0x1423a38,0x92851b(%rip)        # 14cd020 <_ZZN8CPetMenu12updateLayoutEvE14g_RemoveASpell>
  ba4b05:	call   553fc8 <__cxa_guard_release@plt>
  ba4b0a:	mov    $0xf9f788,%edx
  ba4b0f:	mov    $0x14cd020,%esi
  ba4b14:	mov    $0x556288,%edi
  ba4b19:	call   5551e8 <__cxa_atexit@plt>
  ba4b1e:	jmp    ba3184 <_ZN8CPetMenu12updateLayoutEv+0xad4>
  ba4b23:	mov    0x90(%r15),%rsi
  ba4b2a:	mov    %r13,%rdi
  ba4b2d:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  ba4b32:	mov    0x2c8(%r13),%rax
  ba4b39:	test   %rax,%rax
  ba4b3c:	mov    %rax,0x30(%rsp)
  ba4b41:	je     ba2830 <_ZN8CPetMenu12updateLayoutEv+0x180>
  ba4b47:	mov    %rax,%rdi
  ba4b4a:	mov    $0x1,%esi
  ba4b4f:	add    $0x38,%rdi
  ba4b53:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  ba4b58:	mov    0x30(%rsp),%rdx
  ba4b5d:	movb   $0x1,0x3e2(%rdx)
  ba4b64:	jmp    ba2806 <_ZN8CPetMenu12updateLayoutEv+0x156>
  ba4b69:	mov    $0x14cd008,%edi
  ba4b6e:	call   553558 <__cxa_guard_acquire@plt>
  ba4b73:	test   %eax,%eax
  ba4b75:	je     ba31c2 <_ZN8CPetMenu12updateLayoutEv+0xb12>
  ba4b7b:	mov    $0x14cd008,%edi
  ba4b80:	movq   $0x1423a38,0x928485(%rip)        # 14cd010 <_ZZN8CPetMenu12updateLayoutEvE12g_DragASpell>
  ba4b8b:	call   553fc8 <__cxa_guard_release@plt>
  ba4b90:	mov    $0xf9f788,%edx
  ba4b95:	mov    $0x14cd010,%esi
  ba4b9a:	mov    $0x556288,%edi
  ba4b9f:	call   5551e8 <__cxa_atexit@plt>
  ba4ba4:	jmp    ba31c2 <_ZN8CPetMenu12updateLayoutEv+0xb12>
  ba4ba9:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  ba4bae:	lea    0x2270(%rsp),%rdi
  ba4bb6:	mov    %rax,%rsi
  ba4bb9:	mov    $0xfef8c0,%edx
  ba4bbe:	lea    0x2260(%rsp),%r12
  ba4bc6:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  ba4bcb:	mov    0x2270(%rsp),%rsi
  ba4bd3:	mov    %r12,%rdi
  ba4bd6:	call   c8e350 <_ZN7STRINGS21StringConvertToNarrowEPKw>
  ba4bdb:	mov    %r12,%rsi
  ba4bde:	mov    $0x14cd018,%edi
  ba4be3:	call   554d18 <_ZNSs6assignERKSs@plt>
  ba4be8:	mov    0x2260(%rsp),%rdi
  ba4bf0:	sub    $0x18,%rdi
  ba4bf4:	cmp    $0x1423a20,%rdi
  ba4bfb:	jne    ba4ca6 <_ZN8CPetMenu12updateLayoutEv+0x25f6>
  ba4c01:	mov    0x2270(%rsp),%rdi
  ba4c09:	sub    $0x18,%rdi
  ba4c0d:	cmp    $0x1424540,%rdi
  ba4c14:	je     ba31b5 <_ZN8CPetMenu12updateLayoutEv+0xb05>
  ba4c1a:	mov    $0x5541c8,%eax
  ba4c1f:	test   %rax,%rax
  ba4c22:	je     ba4cf8 <_ZN8CPetMenu12updateLayoutEv+0x2648>
  ba4c28:	or     $0xffffffff,%eax
  ba4c2b:	lock xadd %eax,0x10(%rdi)
  ba4c30:	test   %eax,%eax
  ba4c32:	jg     ba31b5 <_ZN8CPetMenu12updateLayoutEv+0xb05>
  ba4c38:	lea    0x22ac(%rsp),%rsi
  ba4c40:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  ba4c45:	jmp    ba31b5 <_ZN8CPetMenu12updateLayoutEv+0xb05>
  ba4c4a:	mov    $0x5541c8,%eax
  ba4c4f:	test   %rax,%rax
  ba4c52:	je     ba4c8e <_ZN8CPetMenu12updateLayoutEv+0x25de>
  ba4c54:	or     $0xffffffff,%eax
  ba4c57:	lock xadd %eax,0x10(%rdi)
  ba4c5c:	test   %eax,%eax
  ba4c5e:	jg     ba4a9a <_ZN8CPetMenu12updateLayoutEv+0x23ea>
  ba4c64:	lea    0x22af(%rsp),%rsi
  ba4c6c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba4c71:	jmp    ba4a9a <_ZN8CPetMenu12updateLayoutEv+0x23ea>
  ba4c76:	mov    %rax,%r14
  ba4c79:	lea    0x2270(%rsp),%rdi
  ba4c81:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  ba4c86:	mov    %r14,%rdi
  ba4c89:	call   554498 <_Unwind_Resume@plt>
  ba4c8e:	mov    0x10(%rdi),%eax
  ba4c91:	lea    -0x1(%rax),%edx
  ba4c94:	mov    %edx,0x10(%rdi)
  ba4c97:	jmp    ba4c5c <_ZN8CPetMenu12updateLayoutEv+0x25ac>
  ba4c99:	mov    %r12,%rdi
  ba4c9c:	mov    %rax,%r14
  ba4c9f:	call   556288 <_ZNSsD1Ev@plt>
  ba4ca4:	jmp    ba4c79 <_ZN8CPetMenu12updateLayoutEv+0x25c9>
  ba4ca6:	mov    $0x5541c8,%eax
  ba4cab:	test   %rax,%rax
  ba4cae:	je     ba4ced <_ZN8CPetMenu12updateLayoutEv+0x263d>
  ba4cb0:	or     $0xffffffff,%eax
  ba4cb3:	lock xadd %eax,0x10(%rdi)
  ba4cb8:	test   %eax,%eax
  ba4cba:	jg     ba4c01 <_ZN8CPetMenu12updateLayoutEv+0x2551>
  ba4cc0:	lea    0x22ad(%rsp),%rsi
  ba4cc8:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba4ccd:	jmp    ba4c01 <_ZN8CPetMenu12updateLayoutEv+0x2551>
  ba4cd2:	mov    %rbx,%rdi
  ba4cd5:	mov    %rax,%r14
  ba4cd8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4cdd:	mov    %r12,%rdi
  ba4ce0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4ce5:	mov    %r14,%rdi
  ba4ce8:	call   554498 <_Unwind_Resume@plt>
  ba4ced:	mov    0x10(%rdi),%eax
  ba4cf0:	lea    -0x1(%rax),%edx
  ba4cf3:	mov    %edx,0x10(%rdi)
  ba4cf6:	jmp    ba4cb8 <_ZN8CPetMenu12updateLayoutEv+0x2608>
  ba4cf8:	mov    0x10(%rdi),%eax
  ba4cfb:	lea    -0x1(%rax),%edx
  ba4cfe:	mov    %edx,0x10(%rdi)
  ba4d01:	jmp    ba4c30 <_ZN8CPetMenu12updateLayoutEv+0x2580>
  ba4d06:	mov    %rax,%r14
  ba4d09:	jmp    ba4cdd <_ZN8CPetMenu12updateLayoutEv+0x262d>
  ba4d0b:	mov    %rax,%r14
  ba4d0e:	mov    %rbx,%rdi
  ba4d11:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4d16:	mov    %r14,%rdi
  ba4d19:	call   554498 <_Unwind_Resume@plt>
  ba4d1e:	mov    %rax,%rdi
  ba4d21:	call   554498 <_Unwind_Resume@plt>
  ba4d26:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4d28:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4d2a:	nopw   0x0(%rax,%rax,1)
  ba4d30:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4d32:	jmp    ba4cd2 <_ZN8CPetMenu12updateLayoutEv+0x2622>
  ba4d34:	lea    0x1cb0(%rsp),%rdi
  ba4d3c:	mov    %rax,%r14
  ba4d3f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4d44:	lea    0x1c00(%rsp),%rdi
  ba4d4c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4d51:	mov    %r14,%rdi
  ba4d54:	call   554498 <_Unwind_Resume@plt>
  ba4d59:	mov    %rax,%r14
  ba4d5c:	jmp    ba4d44 <_ZN8CPetMenu12updateLayoutEv+0x2694>
  ba4d5e:	xchg   %ax,%ax
  ba4d60:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4d62:	mov    %rbx,%rdi
  ba4d65:	mov    %rax,%r14
  ba4d68:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4d6d:	lea    0x1aa0(%rsp),%rdi
  ba4d75:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4d7a:	jmp    ba4cdd <_ZN8CPetMenu12updateLayoutEv+0x262d>
  ba4d7f:	mov    %rax,%r14
  ba4d82:	jmp    ba4d6d <_ZN8CPetMenu12updateLayoutEv+0x26bd>
  ba4d84:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4d86:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4d8b:	nopl   0x0(%rax,%rax,1)
  ba4d90:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4d95:	lea    0x80(%rsp),%rdi
  ba4d9d:	mov    %rax,%r14
  ba4da0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4da5:	mov    %r14,%rdi
  ba4da8:	call   554498 <_Unwind_Resume@plt>
  ba4dad:	mov    %r12,%rdi
  ba4db0:	mov    %rax,%r14
  ba4db3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4db8:	lea    0x130(%rsp),%rdi
  ba4dc0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4dc5:	mov    %r14,%rdi
  ba4dc8:	call   554498 <_Unwind_Resume@plt>
  ba4dcd:	lea    0x1050(%rsp),%rdi
  ba4dd5:	mov    %rax,%r14
  ba4dd8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4ddd:	lea    0xfa0(%rsp),%rdi
  ba4de5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4dea:	mov    %r14,%rdi
  ba4ded:	call   554498 <_Unwind_Resume@plt>
  ba4df2:	mov    %rax,%r14
  ba4df5:	jmp    ba4ddd <_ZN8CPetMenu12updateLayoutEv+0x272d>
  ba4df7:	mov    %rbx,%rdi
  ba4dfa:	mov    %rax,%r14
  ba4dfd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e02:	mov    %r13,%rdi
  ba4e05:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e0a:	jmp    ba4cdd <_ZN8CPetMenu12updateLayoutEv+0x262d>
  ba4e0f:	mov    %rax,%r14
  ba4e12:	jmp    ba4e02 <_ZN8CPetMenu12updateLayoutEv+0x2752>
  ba4e14:	mov    %rax,%r14
  ba4e17:	jmp    ba4db8 <_ZN8CPetMenu12updateLayoutEv+0x2708>
  ba4e19:	mov    %r13,%rdi
  ba4e1c:	mov    %rax,%r14
  ba4e1f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e24:	lea    0x290(%rsp),%rdi
  ba4e2c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e31:	mov    %r14,%rdi
  ba4e34:	call   554498 <_Unwind_Resume@plt>
  ba4e39:	mov    %rax,%r14
  ba4e3c:	jmp    ba4e24 <_ZN8CPetMenu12updateLayoutEv+0x2774>
  ba4e3e:	mov    %rbp,%rdi
  ba4e41:	mov    %rax,%r14
  ba4e44:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e49:	lea    0x3f0(%rsp),%rdi
  ba4e51:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e56:	mov    %r14,%rdi
  ba4e59:	call   554498 <_Unwind_Resume@plt>
  ba4e5e:	mov    %rax,%r14
  ba4e61:	jmp    ba4e49 <_ZN8CPetMenu12updateLayoutEv+0x2799>
  ba4e63:	lea    0x550(%rsp),%rdi
  ba4e6b:	mov    %rax,%r14
  ba4e6e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e73:	mov    %r14,%rdi
  ba4e76:	call   554498 <_Unwind_Resume@plt>
  ba4e7b:	lea    0x6b0(%rsp),%rdi
  ba4e83:	mov    %rax,%r14
  ba4e86:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e8b:	lea    0x600(%rsp),%rdi
  ba4e93:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4e98:	mov    %r14,%rdi
  ba4e9b:	call   554498 <_Unwind_Resume@plt>
  ba4ea0:	mov    %rax,%r14
  ba4ea3:	jmp    ba4e8b <_ZN8CPetMenu12updateLayoutEv+0x27db>
  ba4ea5:	mov    %rax,%r14
  ba4ea8:	lea    0xd90(%rsp),%rdi
  ba4eb0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4eb5:	mov    %r14,%rdi
  ba4eb8:	call   554498 <_Unwind_Resume@plt>
  ba4ebd:	mov    %rbx,%rdi
  ba4ec0:	mov    %rax,%r14
  ba4ec3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4ec8:	jmp    ba4ea8 <_ZN8CPetMenu12updateLayoutEv+0x27f8>
  ba4eca:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4ecf:	nop
  ba4ed0:	jmp    ba4cd2 <_ZN8CPetMenu12updateLayoutEv+0x2622>
  ba4ed5:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4ee0:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4ee5:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4ef0:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4ef5:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f00:	jmp    ba4cd2 <_ZN8CPetMenu12updateLayoutEv+0x2622>
  ba4f05:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f10:	jmp    ba4d1e <_ZN8CPetMenu12updateLayoutEv+0x266e>
  ba4f15:	mov    %rax,%r14
  ba4f18:	mov    %r12,%rdi
  ba4f1b:	nopl   0x0(%rax,%rax,1)
  ba4f20:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4f25:	mov    %r14,%rdi
  ba4f28:	call   554498 <_Unwind_Resume@plt>
  ba4f2d:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4f32:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4f37:	nopw   0x0(%rax,%rax,1)
  ba4f40:	jmp    ba4e0f <_ZN8CPetMenu12updateLayoutEv+0x275f>
  ba4f45:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f50:	jmp    ba4df7 <_ZN8CPetMenu12updateLayoutEv+0x2747>
  ba4f55:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f60:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba4f65:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f70:	jmp    ba4e0f <_ZN8CPetMenu12updateLayoutEv+0x275f>
  ba4f75:	data16 cs nopw 0x0(%rax,%rax,1)
  ba4f80:	jmp    ba4df7 <_ZN8CPetMenu12updateLayoutEv+0x2747>
  ba4f85:	mov    %rax,%r14
  ba4f88:	lea    0x2250(%rsp),%rdi
  ba4f90:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  ba4f95:	mov    %r14,%rdi
  ba4f98:	call   554498 <_Unwind_Resume@plt>
  ba4f9d:	mov    %r12,%rdi
  ba4fa0:	mov    %rax,%r14
  ba4fa3:	call   556288 <_ZNSsD1Ev@plt>
  ba4fa8:	jmp    ba4f88 <_ZN8CPetMenu12updateLayoutEv+0x28d8>
  ba4faa:	mov    $0x5541c8,%eax
  ba4faf:	test   %rax,%rax
  ba4fb2:	je     ba5000 <_ZN8CPetMenu12updateLayoutEv+0x2950>
  ba4fb4:	or     $0xffffffff,%eax
  ba4fb7:	lock xadd %eax,0x10(%rdi)
  ba4fbc:	test   %eax,%eax
  ba4fbe:	jg     ba322c <_ZN8CPetMenu12updateLayoutEv+0xb7c>
  ba4fc4:	lea    0x22ab(%rsp),%rsi
  ba4fcc:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba4fd1:	jmp    ba322c <_ZN8CPetMenu12updateLayoutEv+0xb7c>
  ba4fd6:	mov    %rax,%r14
  ba4fd9:	lea    0x8c0(%rsp),%rdi
  ba4fe1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba4fe6:	lea    0x2230(%rsp),%rdi
  ba4fee:	call   556288 <_ZNSsD1Ev@plt>
  ba4ff3:	mov    %r14,%rdi
  ba4ff6:	call   554498 <_Unwind_Resume@plt>
  ba4ffb:	mov    %rax,%r14
  ba4ffe:	jmp    ba4fe6 <_ZN8CPetMenu12updateLayoutEv+0x2936>
  ba5000:	mov    0x10(%rdi),%eax
  ba5003:	lea    -0x1(%rax),%edx
  ba5006:	mov    %edx,0x10(%rdi)
  ba5009:	jmp    ba4fbc <_ZN8CPetMenu12updateLayoutEv+0x290c>
  ba500b:	lea    0x810(%rsp),%rdi
  ba5013:	mov    %rax,%r14
  ba5016:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba501b:	jmp    ba4fd9 <_ZN8CPetMenu12updateLayoutEv+0x2929>
  ba501d:	mov    0x10(%rdi),%eax
  ba5020:	lea    -0x1(%rax),%edx
  ba5023:	mov    %edx,0x10(%rdi)
  ba5026:	jmp    ba3257 <_ZN8CPetMenu12updateLayoutEv+0xba7>
  ba502b:	mov    $0x5541c8,%eax
  ba5030:	test   %rax,%rax
  ba5033:	je     ba506a <_ZN8CPetMenu12updateLayoutEv+0x29ba>
  ba5035:	or     $0xffffffff,%eax
  ba5038:	lock xadd %eax,0x10(%rdi)
  ba503d:	test   %eax,%eax
  ba503f:	jg     ba4847 <_ZN8CPetMenu12updateLayoutEv+0x2197>
  ba5045:	lea    0x22a9(%rsp),%rsi
  ba504d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba5052:	jmp    ba4847 <_ZN8CPetMenu12updateLayoutEv+0x2197>
  ba5057:	mov    %rax,%r14
  ba505a:	mov    %r13,%rdi
  ba505d:	call   556288 <_ZNSsD1Ev@plt>
  ba5062:	mov    %r14,%rdi
  ba5065:	call   554498 <_Unwind_Resume@plt>
  ba506a:	mov    0x10(%rdi),%eax
  ba506d:	lea    -0x1(%rax),%edx
  ba5070:	mov    %edx,0x10(%rdi)
  ba5073:	jmp    ba503d <_ZN8CPetMenu12updateLayoutEv+0x298d>
  ba5075:	mov    %rax,%r14
  ba5078:	mov    %r13,%rdi
  ba507b:	call   556288 <_ZNSsD1Ev@plt>
  ba5080:	mov    %r14,%rdi
  ba5083:	call   554498 <_Unwind_Resume@plt>
  ba5088:	mov    %rax,%r14
  ba508b:	lea    0x2210(%rsp),%rdi
  ba5093:	call   556288 <_ZNSsD1Ev@plt>
  ba5098:	jmp    ba5078 <_ZN8CPetMenu12updateLayoutEv+0x29c8>
  ba509a:	lea    0x760(%rsp),%rdi
  ba50a2:	mov    %rax,%r14
  ba50a5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba50aa:	jmp    ba508b <_ZN8CPetMenu12updateLayoutEv+0x29db>
  ba50ac:	mov    $0x5541c8,%eax
  ba50b1:	test   %rax,%rax
  ba50b4:	je     ba50dd <_ZN8CPetMenu12updateLayoutEv+0x2a2d>
  ba50b6:	or     $0xffffffff,%eax
  ba50b9:	lock xadd %eax,0x10(%rdi)
  ba50be:	test   %eax,%eax
  ba50c0:	jg     ba48f2 <_ZN8CPetMenu12updateLayoutEv+0x2242>
  ba50c6:	lea    0x22a8(%rsp),%rsi
  ba50ce:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  ba50d3:	jmp    ba48f2 <_ZN8CPetMenu12updateLayoutEv+0x2242>
  ba50d8:	jmp    ba4d06 <_ZN8CPetMenu12updateLayoutEv+0x2656>
  ba50dd:	mov    0x10(%rdi),%eax
  ba50e0:	lea    -0x1(%rax),%edx
  ba50e3:	mov    %edx,0x10(%rdi)
  ba50e6:	jmp    ba50be <_ZN8CPetMenu12updateLayoutEv+0x2a0e>
  ba50e8:	mov    0x10(%rdi),%eax
  ba50eb:	lea    -0x1(%rax),%edx
  ba50ee:	mov    %edx,0x10(%rdi)
  ba50f1:	jmp    ba4922 <_ZN8CPetMenu12updateLayoutEv+0x2272>
  ba50f6:	mov    %rax,%r14
  ba50f9:	lea    0x2020(%rsp),%rdi
  ba5101:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba5106:	jmp    ba4cdd <_ZN8CPetMenu12updateLayoutEv+0x262d>
  ba510b:	mov    %rbx,%rdi
  ba510e:	mov    %rax,%r14
  ba5111:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba5116:	jmp    ba50f9 <_ZN8CPetMenu12updateLayoutEv+0x2a49>
  ba5118:	mov    %rax,%r14
  ba511b:	lea    0x1ec0(%rsp),%rdi
  ba5123:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba5128:	mov    %r14,%rdi
  ba512b:	call   554498 <_Unwind_Resume@plt>
  ba5130:	mov    %rax,%r14
  ba5133:	mov    %r12,%rdi
  ba5136:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba513b:	jmp    ba511b <_ZN8CPetMenu12updateLayoutEv+0x2a6b>
  ba513d:	mov    %rbx,%rdi
  ba5140:	mov    %rax,%r14
  ba5143:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  ba5148:	jmp    ba5133 <_ZN8CPetMenu12updateLayoutEv+0x2a83>
  ba514a:	mov    %rax,%r14
  ba514d:	lea    0x2290(%rsp),%rdi
  ba5155:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  ba515a:	mov    %r14,%rdi
  ba515d:	call   554498 <_Unwind_Resume@plt>
  ba5162:	mov    %r12,%rdi
  ba5165:	mov    %rax,%r14
  ba5168:	call   556288 <_ZNSsD1Ev@plt>
  ba516d:	jmp    ba514d <_ZN8CPetMenu12updateLayoutEv+0x2a9d>
  ba516f:	mov    0x10(%rdi),%eax
  ba5172:	lea    -0x1(%rax),%edx
  ba5175:	mov    %edx,0x10(%rdi)
  ba5178:	jmp    ba4ac9 <_ZN8CPetMenu12updateLayoutEv+0x2419>
