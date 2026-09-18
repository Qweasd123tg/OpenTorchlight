
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000d02720 <_ZN8CMissile24updatePositionByVelocityEf>:
  d02720:	41 54                	push   %r12
  d02722:	55                   	push   %rbp
  d02723:	53                   	push   %rbx
  d02724:	48 89 fb             	mov    %rdi,%rbx
  d02727:	48 81 ec f0 00 00 00 	sub    $0xf0,%rsp
  d0272e:	f3 0f 11 44 24 24    	movss  %xmm0,0x24(%rsp)
  d02734:	48 8b 07             	mov    (%rdi),%rax
  d02737:	ff 90 30 01 00 00    	call   *0x130(%rax)
  d0273d:	f3 0f 10 93 54 01 00 	movss  0x154(%rbx),%xmm2
  d02744:	00 
  d02745:	48 89 df             	mov    %rbx,%rdi
  d02748:	f3 0f 10 40 08       	movss  0x8(%rax),%xmm0
  d0274d:	f3 0f 10 48 04       	movss  0x4(%rax),%xmm1
  d02752:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  d02756:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  d0275a:	f3 0f 59 10          	mulss  (%rax),%xmm2
  d0275e:	48 8b 03             	mov    (%rbx),%rax
  d02761:	f3 0f 59 44 24 24    	mulss  0x24(%rsp),%xmm0
  d02767:	f3 0f 59 4c 24 24    	mulss  0x24(%rsp),%xmm1
  d0276d:	f3 0f 59 54 24 24    	mulss  0x24(%rsp),%xmm2
  d02773:	f3 0f 58 83 50 01 00 	addss  0x150(%rbx),%xmm0
  d0277a:	00 
  d0277b:	f3 0f 58 8b 4c 01 00 	addss  0x14c(%rbx),%xmm1
  d02782:	00 
  d02783:	f3 0f 58 93 48 01 00 	addss  0x148(%rbx),%xmm2
  d0278a:	00 
  d0278b:	f3 0f 11 83 50 01 00 	movss  %xmm0,0x150(%rbx)
  d02792:	00 
  d02793:	f3 0f 11 8b 4c 01 00 	movss  %xmm1,0x14c(%rbx)
  d0279a:	00 
  d0279b:	f3 0f 11 93 48 01 00 	movss  %xmm2,0x148(%rbx)
  d027a2:	00 
  d027a3:	ff 90 38 01 00 00    	call   *0x138(%rax)
  d027a9:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d027af:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d027b4:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d027ba:	f3 0f 10 93 54 01 00 	movss  0x154(%rbx),%xmm2
  d027c1:	00 
  d027c2:	48 89 84 24 e0 00 00 	mov    %rax,0xe0(%rsp)
  d027c9:	00 
  d027ca:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d027cf:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d027d3:	f3 0f 10 8c 24 e4 00 	movss  0xe4(%rsp),%xmm1
  d027da:	00 00 
  d027dc:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  d027e0:	89 84 24 e8 00 00 00 	mov    %eax,0xe8(%rsp)
  d027e7:	f3 0f 10 84 24 e8 00 	movss  0xe8(%rsp),%xmm0
  d027ee:	00 00 
  d027f0:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  d027f4:	f3 0f 59 94 24 e0 00 	mulss  0xe0(%rsp),%xmm2
  d027fb:	00 00 
  d027fd:	f3 0f 59 4c 24 24    	mulss  0x24(%rsp),%xmm1
  d02803:	f3 0f 59 44 24 24    	mulss  0x24(%rsp),%xmm0
  d02809:	f3 0f 59 54 24 24    	mulss  0x24(%rsp),%xmm2
  d0280f:	f3 0f 58 8b 4c 01 00 	addss  0x14c(%rbx),%xmm1
  d02816:	00 
  d02817:	f3 0f 58 83 50 01 00 	addss  0x150(%rbx),%xmm0
  d0281e:	00 
  d0281f:	f3 0f 58 93 48 01 00 	addss  0x148(%rbx),%xmm2
  d02826:	00 
  d02827:	0f 28 e1             	movaps %xmm1,%xmm4
  d0282a:	f3 0f 11 8b 4c 01 00 	movss  %xmm1,0x14c(%rbx)
  d02831:	00 
  d02832:	f3 0f 59 e1          	mulss  %xmm1,%xmm4
  d02836:	f3 0f 11 83 50 01 00 	movss  %xmm0,0x150(%rbx)
  d0283d:	00 
  d0283e:	0f 28 da             	movaps %xmm2,%xmm3
  d02841:	f3 0f 11 93 48 01 00 	movss  %xmm2,0x148(%rbx)
  d02848:	00 
  d02849:	f3 0f 59 da          	mulss  %xmm2,%xmm3
  d0284d:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d02851:	0f 28 e0             	movaps %xmm0,%xmm4
  d02854:	f3 0f 59 e0          	mulss  %xmm0,%xmm4
  d02858:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d0285c:	f3 0f 51 db          	sqrtss %xmm3,%xmm3
  d02860:	f3 0f 11 5c 24 28    	movss  %xmm3,0x28(%rsp)
  d02866:	0f 14 db             	unpcklps %xmm3,%xmm3
  d02869:	0f 5a db             	cvtps2pd %xmm3,%xmm3
  d0286c:	66 0f 2e 1d 2c 5f 2a 	ucomisd 0x2a5f2c(%rip),%xmm3        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d02873:	00 
  d02874:	76 32                	jbe    d028a8 <_ZN8CMissile24updatePositionByVelocityEf+0x188>
  d02876:	f3 0f 10 1d 7e 1f 2a 	movss  0x2a1f7e(%rip),%xmm3        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d0287d:	00 
  d0287e:	f3 0f 5e 5c 24 28    	divss  0x28(%rsp),%xmm3
  d02884:	f3 0f 59 d3          	mulss  %xmm3,%xmm2
  d02888:	f3 0f 59 cb          	mulss  %xmm3,%xmm1
  d0288c:	f3 0f 59 c3          	mulss  %xmm3,%xmm0
  d02890:	f3 0f 11 93 48 01 00 	movss  %xmm2,0x148(%rbx)
  d02897:	00 
  d02898:	f3 0f 11 8b 4c 01 00 	movss  %xmm1,0x14c(%rbx)
  d0289f:	00 
  d028a0:	f3 0f 11 83 50 01 00 	movss  %xmm0,0x150(%rbx)
  d028a7:	00 
  d028a8:	f3 0f 10 83 58 02 00 	movss  0x258(%rbx),%xmm0
  d028af:	00 
  d028b0:	48 8b bb 40 02 00 00 	mov    0x240(%rbx),%rdi
  d028b7:	f3 0f 5c 44 24 24    	subss  0x24(%rsp),%xmm0
  d028bd:	48 85 ff             	test   %rdi,%rdi
  d028c0:	f3 0f 11 83 58 02 00 	movss  %xmm0,0x258(%rbx)
  d028c7:	00 
  d028c8:	0f 84 f6 00 00 00    	je     d029c4 <_ZN8CMissile24updatePositionByVelocityEf+0x2a4>
  d028ce:	e8 7d bf b0 ff       	call   80e850 <_ZN10CCharacter5aliveEv>
  d028d3:	84 c0                	test   %al,%al
  d028d5:	74 59                	je     d02930 <_ZN8CMissile24updatePositionByVelocityEf+0x210>
  d028d7:	8b b3 a0 02 00 00    	mov    0x2a0(%rbx),%esi
  d028dd:	85 f6                	test   %esi,%esi
  d028df:	0f 84 d7 00 00 00    	je     d029bc <_ZN8CMissile24updatePositionByVelocityEf+0x29c>
  d028e5:	48 8b ab 40 02 00 00 	mov    0x240(%rbx),%rbp
  d028ec:	8b bb a4 02 00 00    	mov    0x2a4(%rbx),%edi
  d028f2:	31 d2                	xor    %edx,%edx
  d028f4:	31 c0                	xor    %eax,%eax
  d028f6:	eb 23                	jmp    d0291b <_ZN8CMissile24updatePositionByVelocityEf+0x1fb>
  d028f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  d028ff:	00 
  d02900:	48 8b 8b 98 02 00 00 	mov    0x298(%rbx),%rcx
  d02907:	48 39 29             	cmp    %rbp,(%rcx)
  d0290a:	74 24                	je     d02930 <_ZN8CMissile24updatePositionByVelocityEf+0x210>
  d0290c:	83 c0 01             	add    $0x1,%eax
  d0290f:	48 83 c2 08          	add    $0x8,%rdx
  d02913:	39 f0                	cmp    %esi,%eax
  d02915:	0f 83 a1 00 00 00    	jae    d029bc <_ZN8CMissile24updatePositionByVelocityEf+0x29c>
  d0291b:	39 f8                	cmp    %edi,%eax
  d0291d:	73 e1                	jae    d02900 <_ZN8CMissile24updatePositionByVelocityEf+0x1e0>
  d0291f:	48 89 d1             	mov    %rdx,%rcx
  d02922:	48 03 8b 98 02 00 00 	add    0x298(%rbx),%rcx
  d02929:	48 39 29             	cmp    %rbp,(%rcx)
  d0292c:	75 de                	jne    d0290c <_ZN8CMissile24updatePositionByVelocityEf+0x1ec>
  d0292e:	66 90                	xchg   %ax,%ax
  d02930:	be 01 00 00 00       	mov    $0x1,%esi
  d02935:	48 89 df             	mov    %rbx,%rdi
  d02938:	e8 43 47 ce ff       	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  d0293d:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d02943:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d02948:	48 89 df             	mov    %rbx,%rdi
  d0294b:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d02951:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d02956:	48 89 84 24 d0 00 00 	mov    %rax,0xd0(%rsp)
  d0295d:	00 
  d0295e:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d02962:	89 84 24 d8 00 00 00 	mov    %eax,0xd8(%rsp)
  d02969:	48 8b 03             	mov    (%rbx),%rax
  d0296c:	ff 90 f0 00 00 00    	call   *0xf0(%rax)
  d02972:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d02978:	48 8b 54 24 08       	mov    0x8(%rsp),%rdx
  d0297d:	48 8d 74 24 40       	lea    0x40(%rsp),%rsi
  d02982:	66 0f d6 4c 24 08    	movq   %xmm1,0x8(%rsp)
  d02988:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d0298d:	48 89 df             	mov    %rbx,%rdi
  d02990:	48 89 54 24 30       	mov    %rdx,0x30(%rsp)
  d02995:	48 89 54 24 40       	mov    %rdx,0x40(%rsp)
  d0299a:	48 8d 94 24 d0 00 00 	lea    0xd0(%rsp),%rdx
  d029a1:	00 
  d029a2:	48 89 44 24 38       	mov    %rax,0x38(%rsp)
  d029a7:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  d029ac:	e8 2f 68 ff ff       	call   cf91e0 <_ZN8CMissile16getClosestTargetERKN4Ogre10QuaternionERKNS0_7Vector3E>
  d029b1:	48 89 df             	mov    %rbx,%rdi
  d029b4:	48 89 c6             	mov    %rax,%rsi
  d029b7:	e8 c4 db ff ff       	call   d00580 <_ZN8CMissile9setTargetEP19CPositionableObject>
  d029bc:	f3 0f 10 83 58 02 00 	movss  0x258(%rbx),%xmm0
  d029c3:	00 
  d029c4:	0f 2e 05 2d 1e 2a 00 	ucomiss 0x2a1e2d(%rip),%xmm0        # fa47f8 <_ZTVN4Ogre13FrameListenerE+0x38>
  d029cb:	0f 87 31 02 00 00    	ja     d02c02 <_ZN8CMissile24updatePositionByVelocityEf+0x4e2>
  d029d1:	0f 8a 2b 02 00 00    	jp     d02c02 <_ZN8CMissile24updatePositionByVelocityEf+0x4e2>
  d029d7:	48 83 bb 30 02 00 00 	cmpq   $0x0,0x230(%rbx)
  d029de:	00 
  d029df:	0f 84 1d 02 00 00    	je     d02c02 <_ZN8CMissile24updatePositionByVelocityEf+0x4e2>
  d029e5:	f3 0f 10 83 50 02 00 	movss  0x250(%rbx),%xmm0
  d029ec:	00 
  d029ed:	0f 2e 05 04 1e 2a 00 	ucomiss 0x2a1e04(%rip),%xmm0        # fa47f8 <_ZTVN4Ogre13FrameListenerE+0x38>
  d029f4:	0f 86 08 02 00 00    	jbe    d02c02 <_ZN8CMissile24updatePositionByVelocityEf+0x4e2>
  d029fa:	f3 0f 10 44 24 24    	movss  0x24(%rsp),%xmm0
  d02a00:	bd 00 00 80 3f       	mov    $0x3f800000,%ebp
  d02a05:	f3 0f 58 83 5c 02 00 	addss  0x25c(%rbx),%xmm0
  d02a0c:	00 
  d02a0d:	f3 0f 11 83 5c 02 00 	movss  %xmm0,0x25c(%rbx)
  d02a14:	00 
  d02a15:	e9 db 01 00 00       	jmp    d02bf5 <_ZN8CMissile24updatePositionByVelocityEf+0x4d5>
  d02a1a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  d02a20:	f3 0f 5c 05 30 3e 2f 	subss  0x2f3e30(%rip),%xmm0        # ff6858 <_ZTI8CMissile+0x18>
  d02a27:	00 
  d02a28:	48 8b bb 30 02 00 00 	mov    0x230(%rbx),%rdi
  d02a2f:	be 01 00 00 00       	mov    $0x1,%esi
  d02a34:	f3 0f 11 83 5c 02 00 	movss  %xmm0,0x25c(%rbx)
  d02a3b:	00 
  d02a3c:	e8 3f 46 ce ff       	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  d02a41:	f3 0f 10 93 78 01 00 	movss  0x178(%rbx),%xmm2
  d02a48:	00 
  d02a49:	be 01 00 00 00       	mov    $0x1,%esi
  d02a4e:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d02a54:	f3 0f 58 d2          	addss  %xmm2,%xmm2
  d02a58:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d02a5d:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d02a63:	48 89 df             	mov    %rbx,%rdi
  d02a66:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  d02a6b:	f3 0f 58 54 24 74    	addss  0x74(%rsp),%xmm2
  d02a71:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d02a76:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d02a7a:	89 44 24 78          	mov    %eax,0x78(%rsp)
  d02a7e:	f3 0f 11 54 24 10    	movss  %xmm2,0x10(%rsp)
  d02a84:	e8 f7 45 ce ff       	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  d02a89:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d02a8f:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d02a94:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d02a9a:	89 6c 24 04          	mov    %ebp,0x4(%rsp)
  d02a9e:	f3 0f 10 54 24 10    	movss  0x10(%rsp),%xmm2
  d02aa4:	48 89 84 24 c0 00 00 	mov    %rax,0xc0(%rsp)
  d02aab:	00 
  d02aac:	f3 0f 10 4c 24 70    	movss  0x70(%rsp),%xmm1
  d02ab2:	f3 0f 5c 94 24 c4 00 	subss  0xc4(%rsp),%xmm2
  d02ab9:	00 00 
  d02abb:	f3 0f 5c 8c 24 c0 00 	subss  0xc0(%rsp),%xmm1
  d02ac2:	00 00 
  d02ac4:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d02ac9:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d02acd:	f3 0f 10 44 24 78    	movss  0x78(%rsp),%xmm0
  d02ad3:	f3 0f 10 74 24 04    	movss  0x4(%rsp),%xmm6
  d02ad9:	89 84 24 c8 00 00 00 	mov    %eax,0xc8(%rsp)
  d02ae0:	f3 0f 5c 84 24 c8 00 	subss  0xc8(%rsp),%xmm0
  d02ae7:	00 00 
  d02ae9:	0f 28 e2             	movaps %xmm2,%xmm4
  d02aec:	0f 28 d9             	movaps %xmm1,%xmm3
  d02aef:	f3 0f 59 e2          	mulss  %xmm2,%xmm4
  d02af3:	f3 0f 59 d9          	mulss  %xmm1,%xmm3
  d02af7:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d02afb:	0f 28 e0             	movaps %xmm0,%xmm4
  d02afe:	f3 0f 59 e0          	mulss  %xmm0,%xmm4
  d02b02:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d02b06:	f3 0f 51 db          	sqrtss %xmm3,%xmm3
  d02b0a:	0f 14 db             	unpcklps %xmm3,%xmm3
  d02b0d:	0f 5a e3             	cvtps2pd %xmm3,%xmm4
  d02b10:	66 0f 2e 25 88 5c 2a 	ucomisd 0x2a5c88(%rip),%xmm4        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d02b17:	00 
  d02b18:	76 1b                	jbe    d02b35 <_ZN8CMissile24updatePositionByVelocityEf+0x415>
  d02b1a:	f3 0f 10 35 da 1c 2a 	movss  0x2a1cda(%rip),%xmm6        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d02b21:	00 
  d02b22:	0f 28 e6             	movaps %xmm6,%xmm4
  d02b25:	f3 0f 5e e3          	divss  %xmm3,%xmm4
  d02b29:	f3 0f 59 cc          	mulss  %xmm4,%xmm1
  d02b2d:	f3 0f 59 d4          	mulss  %xmm4,%xmm2
  d02b31:	f3 0f 59 c4          	mulss  %xmm4,%xmm0
  d02b35:	0f 28 ee             	movaps %xmm6,%xmm5
  d02b38:	f3 0f 10 a3 50 02 00 	movss  0x250(%rbx),%xmm4
  d02b3f:	00 
  d02b40:	f3 0f 5c ec          	subss  %xmm4,%xmm5
  d02b44:	f3 0f 10 bb 48 01 00 	movss  0x148(%rbx),%xmm7
  d02b4b:	00 
  d02b4c:	f3 0f 10 9b 4c 01 00 	movss  0x14c(%rbx),%xmm3
  d02b53:	00 
  d02b54:	f3 0f 59 cc          	mulss  %xmm4,%xmm1
  d02b58:	f3 0f 59 d4          	mulss  %xmm4,%xmm2
  d02b5c:	f3 0f 59 c4          	mulss  %xmm4,%xmm0
  d02b60:	f3 0f 59 dd          	mulss  %xmm5,%xmm3
  d02b64:	f3 0f 59 fd          	mulss  %xmm5,%xmm7
  d02b68:	f3 0f 59 ab 50 01 00 	mulss  0x150(%rbx),%xmm5
  d02b6f:	00 
  d02b70:	f3 0f 58 d3          	addss  %xmm3,%xmm2
  d02b74:	f3 0f 58 cf          	addss  %xmm7,%xmm1
  d02b78:	0f 28 e2             	movaps %xmm2,%xmm4
  d02b7b:	f3 0f 11 93 4c 01 00 	movss  %xmm2,0x14c(%rbx)
  d02b82:	00 
  d02b83:	0f 28 d9             	movaps %xmm1,%xmm3
  d02b86:	f3 0f 11 8b 48 01 00 	movss  %xmm1,0x148(%rbx)
  d02b8d:	00 
  d02b8e:	f3 0f 58 c5          	addss  %xmm5,%xmm0
  d02b92:	f3 0f 59 e2          	mulss  %xmm2,%xmm4
  d02b96:	f3 0f 59 d9          	mulss  %xmm1,%xmm3
  d02b9a:	f3 0f 11 83 50 01 00 	movss  %xmm0,0x150(%rbx)
  d02ba1:	00 
  d02ba2:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d02ba6:	0f 28 e0             	movaps %xmm0,%xmm4
  d02ba9:	f3 0f 59 e0          	mulss  %xmm0,%xmm4
  d02bad:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d02bb1:	f3 0f 51 db          	sqrtss %xmm3,%xmm3
  d02bb5:	0f 14 db             	unpcklps %xmm3,%xmm3
  d02bb8:	0f 5a e3             	cvtps2pd %xmm3,%xmm4
  d02bbb:	66 0f 2e 25 dd 5b 2a 	ucomisd 0x2a5bdd(%rip),%xmm4        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d02bc2:	00 
  d02bc3:	76 28                	jbe    d02bed <_ZN8CMissile24updatePositionByVelocityEf+0x4cd>
  d02bc5:	f3 0f 5e f3          	divss  %xmm3,%xmm6
  d02bc9:	f3 0f 59 ce          	mulss  %xmm6,%xmm1
  d02bcd:	f3 0f 59 d6          	mulss  %xmm6,%xmm2
  d02bd1:	f3 0f 59 c6          	mulss  %xmm6,%xmm0
  d02bd5:	f3 0f 11 8b 48 01 00 	movss  %xmm1,0x148(%rbx)
  d02bdc:	00 
  d02bdd:	f3 0f 11 93 4c 01 00 	movss  %xmm2,0x14c(%rbx)
  d02be4:	00 
  d02be5:	f3 0f 11 83 50 01 00 	movss  %xmm0,0x150(%rbx)
  d02bec:	00 
  d02bed:	f3 0f 10 83 5c 02 00 	movss  0x25c(%rbx),%xmm0
  d02bf4:	00 
  d02bf5:	0f 2e 05 5c 3c 2f 00 	ucomiss 0x2f3c5c(%rip),%xmm0        # ff6858 <_ZTI8CMissile+0x18>
  d02bfc:	0f 83 1e fe ff ff    	jae    d02a20 <_ZN8CMissile24updatePositionByVelocityEf+0x300>
  d02c02:	f3 0f 10 54 24 24    	movss  0x24(%rsp),%xmm2
  d02c08:	f3 0f 10 44 24 24    	movss  0x24(%rsp),%xmm0
  d02c0e:	f3 0f 59 93 68 02 00 	mulss  0x268(%rbx),%xmm2
  d02c15:	00 
  d02c16:	f3 0f 58 83 78 02 00 	addss  0x278(%rbx),%xmm0
  d02c1d:	00 
  d02c1e:	f3 0f 58 93 74 02 00 	addss  0x274(%rbx),%xmm2
  d02c25:	00 
  d02c26:	0f 2e 83 70 02 00 00 	ucomiss 0x270(%rbx),%xmm0
  d02c2d:	f3 0f 11 83 78 02 00 	movss  %xmm0,0x278(%rbx)
  d02c34:	00 
  d02c35:	f3 0f 11 93 74 02 00 	movss  %xmm2,0x274(%rbx)
  d02c3c:	00 
  d02c3d:	0f 87 3d 03 00 00    	ja     d02f80 <_ZN8CMissile24updatePositionByVelocityEf+0x860>
  d02c43:	f3 0f 10 0d 45 5b 2a 	movss  0x2a5b45(%rip),%xmm1        # fa8790 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xf0>
  d02c4a:	00 
  d02c4b:	0f 28 da             	movaps %xmm2,%xmm3
  d02c4e:	f3 0f 10 83 64 02 00 	movss  0x264(%rbx),%xmm0
  d02c55:	00 
  d02c56:	0f 54 d9             	andps  %xmm1,%xmm3
  d02c59:	0f 54 c8             	andps  %xmm0,%xmm1
  d02c5c:	0f 2e d9             	ucomiss %xmm1,%xmm3
  d02c5f:	0f 87 fb 02 00 00    	ja     d02f60 <_ZN8CMissile24updatePositionByVelocityEf+0x840>
  d02c65:	0f 28 c2             	movaps %xmm2,%xmm0
  d02c68:	f3 0f 59 44 24 24    	mulss  0x24(%rsp),%xmm0
  d02c6e:	48 8d bb 48 01 00 00 	lea    0x148(%rbx),%rdi
  d02c75:	0f 14 c0             	unpcklps %xmm0,%xmm0
  d02c78:	0f 5a c0             	cvtps2pd %xmm0,%xmm0
  d02c7b:	f2 0f 59 05 05 19 2c 	mulsd  0x2c1905(%rip),%xmm0        # fc4588 <_ZTI7CEditor+0x38>
  d02c82:	00 
  d02c83:	66 0f 14 c0          	unpcklpd %xmm0,%xmm0
  d02c87:	66 0f 5a c0          	cvtpd2ps %xmm0,%xmm0
  d02c8b:	e8 70 77 f7 ff       	call   c7a400 <_ZN4MATH7rotateYEPN4Ogre7Vector3Ef>
  d02c90:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  d02c97:	f3 0f 10 4c 24 28    	movss  0x28(%rsp),%xmm1
  d02c9d:	f3 0f 59 8b 5c 01 00 	mulss  0x15c(%rbx),%xmm1
  d02ca4:	00 
  d02ca5:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  d02caa:	8b 83 50 01 00 00    	mov    0x150(%rbx),%eax
  d02cb0:	f3 0f 10 6c 24 70    	movss  0x70(%rsp),%xmm5
  d02cb6:	f3 0f 10 64 24 74    	movss  0x74(%rsp),%xmm4
  d02cbc:	0f 28 c5             	movaps %xmm5,%xmm0
  d02cbf:	0f 28 d4             	movaps %xmm4,%xmm2
  d02cc2:	89 44 24 78          	mov    %eax,0x78(%rsp)
  d02cc6:	f3 0f 59 c5          	mulss  %xmm5,%xmm0
  d02cca:	f3 0f 10 5c 24 78    	movss  0x78(%rsp),%xmm3
  d02cd0:	f3 0f 59 d4          	mulss  %xmm4,%xmm2
  d02cd4:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  d02cd8:	0f 28 d3             	movaps %xmm3,%xmm2
  d02cdb:	f3 0f 59 d3          	mulss  %xmm3,%xmm2
  d02cdf:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  d02ce3:	f3 0f 51 c0          	sqrtss %xmm0,%xmm0
  d02ce7:	0f 14 c0             	unpcklps %xmm0,%xmm0
  d02cea:	0f 5a d0             	cvtps2pd %xmm0,%xmm2
  d02ced:	66 0f 2e 15 ab 5a 2a 	ucomisd 0x2a5aab(%rip),%xmm2        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d02cf4:	00 
  d02cf5:	76 2a                	jbe    d02d21 <_ZN8CMissile24updatePositionByVelocityEf+0x601>
  d02cf7:	f3 0f 10 15 fd 1a 2a 	movss  0x2a1afd(%rip),%xmm2        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d02cfe:	00 
  d02cff:	f3 0f 5e d0          	divss  %xmm0,%xmm2
  d02d03:	f3 0f 59 ea          	mulss  %xmm2,%xmm5
  d02d07:	f3 0f 59 e2          	mulss  %xmm2,%xmm4
  d02d0b:	f3 0f 59 d3          	mulss  %xmm3,%xmm2
  d02d0f:	f3 0f 11 6c 24 70    	movss  %xmm5,0x70(%rsp)
  d02d15:	f3 0f 11 64 24 74    	movss  %xmm4,0x74(%rsp)
  d02d1b:	f3 0f 11 54 24 78    	movss  %xmm2,0x78(%rsp)
  d02d21:	48 8b 05 0c 1e 72 00 	mov    0x721e0c(%rip),%rax        # 1424b34 <_ZN4Ogre7Vector36UNIT_YE>
  d02d28:	4c 8d 64 24 60       	lea    0x60(%rsp),%r12
  d02d2d:	48 8d 6c 24 70       	lea    0x70(%rsp),%rbp
  d02d32:	48 89 df             	mov    %rbx,%rdi
  d02d35:	f3 0f 11 4c 24 10    	movss  %xmm1,0x10(%rsp)
  d02d3b:	4c 89 e2             	mov    %r12,%rdx
  d02d3e:	48 89 ee             	mov    %rbp,%rsi
  d02d41:	48 89 44 24 60       	mov    %rax,0x60(%rsp)
  d02d46:	8b 05 f0 1d 72 00    	mov    0x721df0(%rip),%eax        # 1424b3c <_ZN4Ogre7Vector36UNIT_YE+0x8>
  d02d4c:	89 44 24 68          	mov    %eax,0x68(%rsp)
  d02d50:	48 8b 03             	mov    (%rbx),%rax
  d02d53:	ff 90 28 01 00 00    	call   *0x128(%rax)
  d02d59:	f3 0f 10 4c 24 10    	movss  0x10(%rsp),%xmm1
  d02d5f:	be 01 00 00 00       	mov    $0x1,%esi
  d02d64:	f3 0f 10 83 48 01 00 	movss  0x148(%rbx),%xmm0
  d02d6b:	00 
  d02d6c:	48 89 df             	mov    %rbx,%rdi
  d02d6f:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  d02d73:	f3 0f 11 83 48 01 00 	movss  %xmm0,0x148(%rbx)
  d02d7a:	00 
  d02d7b:	f3 0f 10 83 4c 01 00 	movss  0x14c(%rbx),%xmm0
  d02d82:	00 
  d02d83:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  d02d87:	f3 0f 59 8b 50 01 00 	mulss  0x150(%rbx),%xmm1
  d02d8e:	00 
  d02d8f:	f3 0f 11 83 4c 01 00 	movss  %xmm0,0x14c(%rbx)
  d02d96:	00 
  d02d97:	f3 0f 11 8b 50 01 00 	movss  %xmm1,0x150(%rbx)
  d02d9e:	00 
  d02d9f:	e8 dc 42 ce ff       	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  d02da4:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d02daa:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d02daf:	48 83 bb 10 02 00 00 	cmpq   $0x0,0x210(%rbx)
  d02db6:	00 
  d02db7:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d02dbd:	48 89 84 24 b0 00 00 	mov    %rax,0xb0(%rsp)
  d02dc4:	00 
  d02dc5:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d02dca:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d02dce:	f3 0f 10 8c 24 b4 00 	movss  0xb4(%rsp),%xmm1
  d02dd5:	00 00 
  d02dd7:	f3 0f 10 94 24 b0 00 	movss  0xb0(%rsp),%xmm2
  d02dde:	00 00 
  d02de0:	89 84 24 b8 00 00 00 	mov    %eax,0xb8(%rsp)
  d02de7:	f3 0f 10 84 24 b8 00 	movss  0xb8(%rsp),%xmm0
  d02dee:	00 00 
  d02df0:	74 15                	je     d02e07 <_ZN8CMissile24updatePositionByVelocityEf+0x6e7>
  d02df2:	f3 0f 10 9b 9c 01 00 	movss  0x19c(%rbx),%xmm3
  d02df9:	00 
  d02dfa:	0f 2e 1d f7 19 2a 00 	ucomiss 0x2a19f7(%rip),%xmm3        # fa47f8 <_ZTVN4Ogre13FrameListenerE+0x38>
  d02e01:	0f 87 b9 01 00 00    	ja     d02fc0 <_ZN8CMissile24updatePositionByVelocityEf+0x8a0>
  d02e07:	f3 0f 10 64 24 24    	movss  0x24(%rsp),%xmm4
  d02e0d:	48 83 bb 08 01 00 00 	cmpq   $0x0,0x108(%rbx)
  d02e14:	00 
  d02e15:	f3 0f 59 a3 4c 01 00 	mulss  0x14c(%rbx),%xmm4
  d02e1c:	00 
  d02e1d:	f3 0f 10 5c 24 24    	movss  0x24(%rsp),%xmm3
  d02e23:	f3 0f 59 9b 48 01 00 	mulss  0x148(%rbx),%xmm3
  d02e2a:	00 
  d02e2b:	f3 0f 58 cc          	addss  %xmm4,%xmm1
  d02e2f:	f3 0f 58 d3          	addss  %xmm3,%xmm2
  d02e33:	f3 0f 11 4c 24 2c    	movss  %xmm1,0x2c(%rsp)
  d02e39:	f3 0f 10 4c 24 24    	movss  0x24(%rsp),%xmm1
  d02e3f:	f3 0f 59 8b 50 01 00 	mulss  0x150(%rbx),%xmm1
  d02e46:	00 
  d02e47:	f3 0f 11 54 24 28    	movss  %xmm2,0x28(%rsp)
  d02e4d:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  d02e51:	f3 0f 11 44 24 24    	movss  %xmm0,0x24(%rsp)
  d02e57:	0f 84 af 00 00 00    	je     d02f0c <_ZN8CMissile24updatePositionByVelocityEf+0x7ec>
  d02e5d:	48 8b 83 48 01 00 00 	mov    0x148(%rbx),%rax
  d02e64:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  d02e69:	8b 83 50 01 00 00    	mov    0x150(%rbx),%eax
  d02e6f:	f3 0f 10 64 24 70    	movss  0x70(%rsp),%xmm4
  d02e75:	f3 0f 10 5c 24 74    	movss  0x74(%rsp),%xmm3
  d02e7b:	0f 28 c4             	movaps %xmm4,%xmm0
  d02e7e:	0f 28 cb             	movaps %xmm3,%xmm1
  d02e81:	89 44 24 78          	mov    %eax,0x78(%rsp)
  d02e85:	f3 0f 59 c4          	mulss  %xmm4,%xmm0
  d02e89:	f3 0f 10 54 24 78    	movss  0x78(%rsp),%xmm2
  d02e8f:	f3 0f 59 cb          	mulss  %xmm3,%xmm1
  d02e93:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  d02e97:	0f 28 ca             	movaps %xmm2,%xmm1
  d02e9a:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  d02e9e:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  d02ea2:	f3 0f 51 c0          	sqrtss %xmm0,%xmm0
  d02ea6:	0f 14 c0             	unpcklps %xmm0,%xmm0
  d02ea9:	0f 5a c8             	cvtps2pd %xmm0,%xmm1
  d02eac:	66 0f 2e 0d ec 58 2a 	ucomisd 0x2a58ec(%rip),%xmm1        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d02eb3:	00 
  d02eb4:	76 2a                	jbe    d02ee0 <_ZN8CMissile24updatePositionByVelocityEf+0x7c0>
  d02eb6:	f3 0f 10 0d 3e 19 2a 	movss  0x2a193e(%rip),%xmm1        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d02ebd:	00 
  d02ebe:	f3 0f 5e c8          	divss  %xmm0,%xmm1
  d02ec2:	f3 0f 59 e1          	mulss  %xmm1,%xmm4
  d02ec6:	f3 0f 59 d9          	mulss  %xmm1,%xmm3
  d02eca:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  d02ece:	f3 0f 11 64 24 70    	movss  %xmm4,0x70(%rsp)
  d02ed4:	f3 0f 11 5c 24 74    	movss  %xmm3,0x74(%rsp)
  d02eda:	f3 0f 11 4c 24 78    	movss  %xmm1,0x78(%rsp)
  d02ee0:	48 8b 05 4d 1c 72 00 	mov    0x721c4d(%rip),%rax        # 1424b34 <_ZN4Ogre7Vector36UNIT_YE>
  d02ee7:	48 8b bb 08 01 00 00 	mov    0x108(%rbx),%rdi
  d02eee:	4c 89 e2             	mov    %r12,%rdx
  d02ef1:	48 89 ee             	mov    %rbp,%rsi
  d02ef4:	48 89 44 24 60       	mov    %rax,0x60(%rsp)
  d02ef9:	8b 05 3d 1c 72 00    	mov    0x721c3d(%rip),%eax        # 1424b3c <_ZN4Ogre7Vector36UNIT_YE+0x8>
  d02eff:	89 44 24 68          	mov    %eax,0x68(%rsp)
  d02f03:	48 8b 07             	mov    (%rdi),%rax
  d02f06:	ff 90 28 01 00 00    	call   *0x128(%rax)
  d02f0c:	8b 2d 62 86 80 00    	mov    0x808662(%rip),%ebp        # 150b574 <KSETTINGS_SHOW_MISSILE_TRAILS>
  d02f12:	e8 79 15 d5 ff       	call   a54490 <_ZN22CMasterResourceManager12getSingletonEv>
  d02f17:	48 8b b8 90 00 00 00 	mov    0x90(%rax),%rdi
  d02f1e:	89 ee                	mov    %ebp,%esi
  d02f20:	e8 1b b5 f6 ff       	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  d02f25:	83 f8 01             	cmp    $0x1,%eax
  d02f28:	0f 84 fa 02 00 00    	je     d03228 <_ZN8CMissile24updatePositionByVelocityEf+0xb08>
  d02f2e:	f3 0f 10 44 24 2c    	movss  0x2c(%rsp),%xmm0
  d02f34:	f3 0f 10 4c 24 28    	movss  0x28(%rsp),%xmm1
  d02f3a:	f3 0f 11 4c 24 50    	movss  %xmm1,0x50(%rsp)
  d02f40:	f3 0f 11 44 24 54    	movss  %xmm0,0x54(%rsp)
  d02f46:	f3 0f 10 4c 24 24    	movss  0x24(%rsp),%xmm1
  d02f4c:	f3 0f 7e 44 24 50    	movq   0x50(%rsp),%xmm0
  d02f52:	48 81 c4 f0 00 00 00 	add    $0xf0,%rsp
  d02f59:	5b                   	pop    %rbx
  d02f5a:	5d                   	pop    %rbp
  d02f5b:	41 5c                	pop    %r12
  d02f5d:	c3                   	ret
  d02f5e:	66 90                	xchg   %ax,%ax
  d02f60:	0f 57 c9             	xorps  %xmm1,%xmm1
  d02f63:	0f 2e ca             	ucomiss %xmm2,%xmm1
  d02f66:	76 0b                	jbe    d02f73 <_ZN8CMissile24updatePositionByVelocityEf+0x853>
  d02f68:	f3 0f 10 0d 10 58 2a 	movss  0x2a5810(%rip),%xmm1        # fa8780 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xe0>
  d02f6f:	00 
  d02f70:	0f 57 c1             	xorps  %xmm1,%xmm0
  d02f73:	f3 0f 11 83 74 02 00 	movss  %xmm0,0x274(%rbx)
  d02f7a:	00 
  d02f7b:	e9 e8 fc ff ff       	jmp    d02c68 <_ZN8CMissile24updatePositionByVelocityEf+0x548>
  d02f80:	f3 0f 10 05 f8 57 2a 	movss  0x2a57f8(%rip),%xmm0        # fa8780 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xe0>
  d02f87:	00 
  d02f88:	f3 0f 10 8b 6c 02 00 	movss  0x26c(%rbx),%xmm1
  d02f8f:	00 
  d02f90:	f3 0f 11 54 24 10    	movss  %xmm2,0x10(%rsp)
  d02f96:	0f 57 c1             	xorps  %xmm1,%xmm0
  d02f99:	e8 b2 fb f8 ff       	call   c92b50 <_ZN9UTILITIES21randomBetweenVolatileEff>
  d02f9e:	f3 0f 10 54 24 10    	movss  0x10(%rsp),%xmm2
  d02fa4:	c7 83 78 02 00 00 00 	movl   $0x0,0x278(%rbx)
  d02fab:	00 00 00 
  d02fae:	f3 0f 58 d0          	addss  %xmm0,%xmm2
  d02fb2:	f3 0f 11 93 74 02 00 	movss  %xmm2,0x274(%rbx)
  d02fb9:	00 
  d02fba:	e9 84 fc ff ff       	jmp    d02c43 <_ZN8CMissile24updatePositionByVelocityEf+0x523>
  d02fbf:	90                   	nop
  d02fc0:	f3 0f 10 83 48 01 00 	movss  0x148(%rbx),%xmm0
  d02fc7:	00 
  d02fc8:	48 8b bb 10 02 00 00 	mov    0x210(%rbx),%rdi
  d02fcf:	f3 0f 10 93 4c 01 00 	movss  0x14c(%rbx),%xmm2
  d02fd6:	00 
  d02fd7:	f3 0f 59 c0          	mulss  %xmm0,%xmm0
  d02fdb:	f3 0f 59 d2          	mulss  %xmm2,%xmm2
  d02fdf:	f3 0f 10 8b 50 01 00 	movss  0x150(%rbx),%xmm1
  d02fe6:	00 
  d02fe7:	f3 0f 59 c9          	mulss  %xmm1,%xmm1
  d02feb:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  d02fef:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  d02ff3:	f3 0f 51 c8          	sqrtss %xmm0,%xmm1
  d02ff7:	f3 0f 59 4c 24 24    	mulss  0x24(%rsp),%xmm1
  d02ffd:	f3 0f 58 8b c4 01 00 	addss  0x1c4(%rbx),%xmm1
  d03004:	00 
  d03005:	f3 0f 11 8b c4 01 00 	movss  %xmm1,0x1c4(%rbx)
  d0300c:	00 
  d0300d:	f3 0f 10 47 18       	movss  0x18(%rdi),%xmm0
  d03012:	f3 0f 5d c1          	minss  %xmm1,%xmm0
  d03016:	f3 0f 11 83 c4 01 00 	movss  %xmm0,0x1c4(%rbx)
  d0301d:	00 
  d0301e:	e8 bd 49 f8 ff       	call   c879e0 <_ZN5CPath27GetSplinePositionAtDistanceEf>
  d03023:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d03029:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d0302e:	48 8b bb 10 02 00 00 	mov    0x210(%rbx),%rdi
  d03035:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d0303b:	f3 0f 10 83 c4 01 00 	movss  0x1c4(%rbx),%xmm0
  d03042:	00 
  d03043:	48 89 84 24 a0 00 00 	mov    %rax,0xa0(%rsp)
  d0304a:	00 
  d0304b:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d03050:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d03054:	f3 0f 10 94 24 a0 00 	movss  0xa0(%rsp),%xmm2
  d0305b:	00 00 
  d0305d:	f3 0f 10 9c 24 a4 00 	movss  0xa4(%rsp),%xmm3
  d03064:	00 00 
  d03066:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%rsp)
  d0306d:	f3 0f 11 54 24 28    	movss  %xmm2,0x28(%rsp)
  d03073:	f3 0f 10 a4 24 a8 00 	movss  0xa8(%rsp),%xmm4
  d0307a:	00 00 
  d0307c:	f3 0f 11 5c 24 2c    	movss  %xmm3,0x2c(%rsp)
  d03082:	f3 0f 11 64 24 24    	movss  %xmm4,0x24(%rsp)
  d03088:	f3 0f 10 57 18       	movss  0x18(%rdi),%xmm2
  d0308d:	0f 2e c2             	ucomiss %xmm2,%xmm0
  d03090:	72 1d                	jb     d030af <_ZN8CMissile24updatePositionByVelocityEf+0x98f>
  d03092:	8b 83 b8 01 00 00    	mov    0x1b8(%rbx),%eax
  d03098:	89 83 c0 01 00 00    	mov    %eax,0x1c0(%rbx)
  d0309e:	8b 83 98 01 00 00    	mov    0x198(%rbx),%eax
  d030a4:	89 83 bc 01 00 00    	mov    %eax,0x1bc(%rbx)
  d030aa:	f3 0f 10 57 18       	movss  0x18(%rdi),%xmm2
  d030af:	f3 0f 58 05 31 37 2c 	addss  0x2c3731(%rip),%xmm0        # fc67e8 <_ZTI4CPOV+0x18>
  d030b6:	00 
  d030b7:	0f 57 c9             	xorps  %xmm1,%xmm1
  d030ba:	f3 0f 5d d0          	minss  %xmm0,%xmm2
  d030be:	0f 28 c2             	movaps %xmm2,%xmm0
  d030c1:	f3 0f 11 54 24 10    	movss  %xmm2,0x10(%rsp)
  d030c7:	f3 0f 5c 05 31 b4 2c 	subss  0x2cb431(%rip),%xmm0        # fce500 <_ZTV18iInventoryListener+0xc0>
  d030ce:	00 
  d030cf:	f3 0f 5f c8          	maxss  %xmm0,%xmm1
  d030d3:	0f 28 c1             	movaps %xmm1,%xmm0
  d030d6:	e8 05 49 f8 ff       	call   c879e0 <_ZN5CPath27GetSplinePositionAtDistanceEf>
  d030db:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d030e1:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d030e6:	48 8b bb 10 02 00 00 	mov    0x210(%rbx),%rdi
  d030ed:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d030f3:	f3 0f 10 54 24 10    	movss  0x10(%rsp),%xmm2
  d030f9:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d030fe:	0f 28 c2             	movaps %xmm2,%xmm0
  d03101:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  d03108:	00 
  d03109:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d0310d:	89 84 24 88 00 00 00 	mov    %eax,0x88(%rsp)
  d03114:	e8 c7 48 f8 ff       	call   c879e0 <_ZN5CPath27GetSplinePositionAtDistanceEf>
  d03119:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  d0311f:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  d03124:	f3 0f 11 4c 24 38    	movss  %xmm1,0x38(%rsp)
  d0312a:	48 89 84 24 90 00 00 	mov    %rax,0x90(%rsp)
  d03131:	00 
  d03132:	f3 0f 10 8c 24 94 00 	movss  0x94(%rsp),%xmm1
  d03139:	00 00 
  d0313b:	48 89 44 24 30       	mov    %rax,0x30(%rsp)
  d03140:	f3 0f 10 94 24 90 00 	movss  0x90(%rsp),%xmm2
  d03147:	00 00 
  d03149:	f3 0f 5c 8c 24 84 00 	subss  0x84(%rsp),%xmm1
  d03150:	00 00 
  d03152:	f3 0f 5c 94 24 80 00 	subss  0x80(%rsp),%xmm2
  d03159:	00 00 
  d0315b:	8b 44 24 38          	mov    0x38(%rsp),%eax
  d0315f:	89 84 24 98 00 00 00 	mov    %eax,0x98(%rsp)
  d03166:	f3 0f 10 84 24 98 00 	movss  0x98(%rsp),%xmm0
  d0316d:	00 00 
  d0316f:	f3 0f 5c 84 24 88 00 	subss  0x88(%rsp),%xmm0
  d03176:	00 00 
  d03178:	0f 28 e1             	movaps %xmm1,%xmm4
  d0317b:	0f 28 da             	movaps %xmm2,%xmm3
  d0317e:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  d03184:	f3 0f 59 e1          	mulss  %xmm1,%xmm4
  d03188:	f3 0f 11 4c 24 64    	movss  %xmm1,0x64(%rsp)
  d0318e:	f3 0f 59 da          	mulss  %xmm2,%xmm3
  d03192:	f3 0f 11 44 24 68    	movss  %xmm0,0x68(%rsp)
  d03198:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d0319c:	0f 28 e0             	movaps %xmm0,%xmm4
  d0319f:	f3 0f 59 e0          	mulss  %xmm0,%xmm4
  d031a3:	f3 0f 58 dc          	addss  %xmm4,%xmm3
  d031a7:	f3 0f 51 db          	sqrtss %xmm3,%xmm3
  d031ab:	0f 14 db             	unpcklps %xmm3,%xmm3
  d031ae:	0f 5a e3             	cvtps2pd %xmm3,%xmm4
  d031b1:	66 0f 2e 25 e7 55 2a 	ucomisd 0x2a55e7(%rip),%xmm4        # fa87a0 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x100>
  d031b8:	00 
  d031b9:	76 2a                	jbe    d031e5 <_ZN8CMissile24updatePositionByVelocityEf+0xac5>
  d031bb:	f3 0f 10 25 39 16 2a 	movss  0x2a1639(%rip),%xmm4        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d031c2:	00 
  d031c3:	f3 0f 5e e3          	divss  %xmm3,%xmm4
  d031c7:	f3 0f 59 d4          	mulss  %xmm4,%xmm2
  d031cb:	f3 0f 59 cc          	mulss  %xmm4,%xmm1
  d031cf:	f3 0f 59 c4          	mulss  %xmm4,%xmm0
  d031d3:	f3 0f 11 54 24 60    	movss  %xmm2,0x60(%rsp)
  d031d9:	f3 0f 11 4c 24 64    	movss  %xmm1,0x64(%rsp)
  d031df:	f3 0f 11 44 24 68    	movss  %xmm0,0x68(%rsp)
  d031e5:	48 83 bb 08 01 00 00 	cmpq   $0x0,0x108(%rbx)
  d031ec:	00 
  d031ed:	0f 84 19 fd ff ff    	je     d02f0c <_ZN8CMissile24updatePositionByVelocityEf+0x7ec>
  d031f3:	48 8b 05 3a 19 72 00 	mov    0x72193a(%rip),%rax        # 1424b34 <_ZN4Ogre7Vector36UNIT_YE>
  d031fa:	48 8b bb 08 01 00 00 	mov    0x108(%rbx),%rdi
  d03201:	48 89 ea             	mov    %rbp,%rdx
  d03204:	4c 89 e6             	mov    %r12,%rsi
  d03207:	48 89 44 24 70       	mov    %rax,0x70(%rsp)
  d0320c:	8b 05 2a 19 72 00    	mov    0x72192a(%rip),%eax        # 1424b3c <_ZN4Ogre7Vector36UNIT_YE+0x8>
  d03212:	89 44 24 78          	mov    %eax,0x78(%rsp)
  d03216:	48 8b 07             	mov    (%rdi),%rax
  d03219:	ff 90 28 01 00 00    	call   *0x128(%rax)
  d0321f:	e9 e8 fc ff ff       	jmp    d02f0c <_ZN8CMissile24updatePositionByVelocityEf+0x7ec>
  d03224:	0f 1f 40 00          	nopl   0x0(%rax)
  d03228:	f3 0f 10 54 24 2c    	movss  0x2c(%rsp),%xmm2
  d0322e:	f3 0f 10 44 24 28    	movss  0x28(%rsp),%xmm0
  d03234:	f3 0f 5c 93 e4 01 00 	subss  0x1e4(%rbx),%xmm2
  d0323b:	00 
  d0323c:	f3 0f 5c 83 e0 01 00 	subss  0x1e0(%rbx),%xmm0
  d03243:	00 
  d03244:	f3 0f 10 4c 24 24    	movss  0x24(%rsp),%xmm1
  d0324a:	f3 0f 5c 8b e8 01 00 	subss  0x1e8(%rbx),%xmm1
  d03251:	00 
  d03252:	f3 0f 59 d2          	mulss  %xmm2,%xmm2
  d03256:	f3 0f 59 c0          	mulss  %xmm0,%xmm0
  d0325a:	f3 0f 59 c9          	mulss  %xmm1,%xmm1
  d0325e:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  d03262:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  d03266:	f3 0f 51 c0          	sqrtss %xmm0,%xmm0
  d0326a:	0f 2e 05 8b 15 2a 00 	ucomiss 0x2a158b(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  d03271:	0f 86 b7 fc ff ff    	jbe    d02f2e <_ZN8CMissile24updatePositionByVelocityEf+0x80e>
  d03277:	f3 0f 10 54 24 28    	movss  0x28(%rsp),%xmm2
  d0327d:	48 89 df             	mov    %rbx,%rdi
  d03280:	f3 0f 10 5c 24 2c    	movss  0x2c(%rsp),%xmm3
  d03286:	f3 0f 10 64 24 24    	movss  0x24(%rsp),%xmm4
  d0328c:	f3 0f 11 93 e0 01 00 	movss  %xmm2,0x1e0(%rbx)
  d03293:	00 
  d03294:	f3 0f 11 9b e4 01 00 	movss  %xmm3,0x1e4(%rbx)
  d0329b:	00 
  d0329c:	f3 0f 11 a3 e8 01 00 	movss  %xmm4,0x1e8(%rbx)
  d032a3:	00 
  d032a4:	e8 e7 5c ff ff       	call   cf8f90 <_ZN8CMissile11placeSphereEv>
  d032a9:	e9 80 fc ff ff       	jmp    d02f2e <_ZN8CMissile24updatePositionByVelocityEf+0x80e>
