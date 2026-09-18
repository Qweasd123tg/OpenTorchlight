
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b4f9d0 <_ZN14CInventoryMenu6updateEf>:
  b4f9d0:	push   %r15
  b4f9d2:	push   %r14
  b4f9d4:	push   %r13
  b4f9d6:	push   %r12
  b4f9d8:	push   %rbp
  b4f9d9:	push   %rbx
  b4f9da:	mov    %rdi,%rbx
  b4f9dd:	sub    $0x1248,%rsp
  b4f9e4:	movss  %xmm0,0x4c(%rsp)
  b4f9ea:	addss  0x91ac(%rdi),%xmm0
  b4f9f2:	ucomiss 0x454e03(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4f9f9:	movss  %xmm0,0x91ac(%rdi)
  b4fa01:	jb     b4fa21 <_ZN14CInventoryMenu6updateEf+0x51>
  b4fa03:	nopl   0x0(%rax,%rax,1)
  b4fa08:	subss  0x454dec(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4fa10:	ucomiss 0x454de5(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4fa17:	jae    b4fa08 <_ZN14CInventoryMenu6updateEf+0x38>
  b4fa19:	movss  %xmm0,0x91ac(%rbx)
  b4fa21:	lea    0x91b0(%rbx),%rax
  b4fa28:	lea    0xc60(%rsp),%r14
  b4fa30:	lea    0xe70(%rsp),%r13
  b4fa38:	lea    0xf20(%rsp),%r15
  b4fa40:	mov    %rbx,%rbp
  b4fa43:	mov    $0x1,%r12d
  b4fa49:	mov    %rax,0x50(%rsp)
  b4fa4e:	lea    0x93c0(%rbx),%rax
  b4fa55:	mov    %rax,0x58(%rsp)
  b4fa5a:	lea    0x9260(%rbx),%rax
  b4fa61:	mov    %rax,0x80(%rsp)
  b4fa69:	lea    0x9470(%rbx),%rax
  b4fa70:	mov    %rax,0x90(%rsp)
  b4fa78:	lea    0x9310(%rbx),%rax
  b4fa7f:	mov    %rax,0x78(%rsp)
  b4fa84:	lea    0x9520(%rbx),%rax
  b4fa8b:	mov    %rax,0x88(%rsp)
  b4fa93:	lea    0x64(%r14),%rax
  b4fa97:	mov    %rax,0x60(%rsp)
  b4fa9c:	lea    0x64(%r13),%rax
  b4faa0:	mov    %rax,0x68(%rsp)
  b4faa5:	lea    0x64(%r15),%rax
  b4faa9:	mov    %rax,0x70(%rsp)
  b4faae:	cmpb   $0x0,0x91a8(%rbp)
  b4fab5:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b4fabb:	mov    %ebp,%eax
  b4fabd:	sub    %ebx,%eax
  b4fabf:	je     b50340 <_ZN14CInventoryMenu6updateEf+0x970>
  b4fac5:	cmp    $0x1,%eax
  b4fac8:	je     b513c8 <_ZN14CInventoryMenu6updateEf+0x19f8>
  b4face:	mov    0x9118(%rbx),%rdi
  b4fad5:	xor    %esi,%esi
  b4fad7:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  b4fadc:	test   %al,%al
  b4fade:	jne    b516f2 <_ZN14CInventoryMenu6updateEf+0x1d22>
  b4fae4:	movss  0x91ac(%rbx),%xmm0
  b4faec:	ucomiss 0x454d1d(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b4faf3:	jbe    b51646 <_ZN14CInventoryMenu6updateEf+0x1c76>
  b4faf9:	lea    0x4d0(%rsp),%rdi
  b4fb01:	mov    $0xfef75c,%esi
  b4fb06:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b4fb0b:	mov    0x9130(%rbx),%rsi
  b4fb12:	lea    0x4d0(%rsp),%rdx
  b4fb1a:	lea    0x420(%rsp),%rdi
  b4fb22:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b4fb27:	mov    0x88(%rsp),%rsi
  b4fb2f:	lea    0x420(%rsp),%rdi
  b4fb37:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b4fb3c:	lea    0x420(%rsp),%rdi
  b4fb44:	mov    %al,0x9f(%rsp)
  b4fb4b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4fb50:	lea    0x4d0(%rsp),%rdi
  b4fb58:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4fb5d:	cmpb   $0x0,0x9f(%rsp)
  b4fb65:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b4fb67:	lea    0x370(%rsp),%rdi
  b4fb6f:	mov    $0xfef75c,%esi
  b4fb74:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b4fb79:	mov    0x9130(%rbx),%rdi
  b4fb80:	mov    0x88(%rsp),%rdx
  b4fb88:	lea    0x370(%rsp),%rsi
  b4fb90:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b4fb95:	lea    0x370(%rsp),%rdi
  b4fb9d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4fba2:	nopw   0x0(%rax,%rax,1)
  b4fba8:	cmp    $0x2,%r12d
  b4fbac:	ja     b4fbc0 <_ZN14CInventoryMenu6updateEf+0x1f0>
  b4fbae:	add    $0x1,%rbp
  b4fbb2:	add    $0x1,%r12d
  b4fbb6:	jmp    b4faae <_ZN14CInventoryMenu6updateEf+0xde>
  b4fbbb:	nopl   0x0(%rax,%rax,1)
  b4fbc0:	mov    0x68(%rbx),%rdi
  b4fbc4:	mov    0x9bb89a(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  b4fbca:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b4fbcf:	mov    0x9bb893(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  b4fbd5:	mov    %eax,0x50(%rsp)
  b4fbd9:	mov    0x68(%rbx),%rdi
  b4fbdd:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b4fbe2:	mov    %eax,0x58(%rsp)
  b4fbe6:	cmpq   $0x0,0x50(%rbx)
  b4fbeb:	je     b4fd7a <_ZN14CInventoryMenu6updateEf+0x3aa>
  b4fbf1:	cmpb   $0x0,0x977748(%rip)        # 14c7340 <_ZGVZN14CInventoryMenu6updateEfE4g_GP>
  b4fbf8:	je     b50b20 <_ZN14CInventoryMenu6updateEf+0x1150>
  b4fbfe:	mov    0x977743(%rip),%rax        # 14c7348 <_ZZN14CInventoryMenu6updateEfE4g_GP>
  b4fc05:	cmpq   $0x0,-0x18(%rax)
  b4fc0a:	je     b50290 <_ZN14CInventoryMenu6updateEf+0x8c0>
  b4fc10:	mov    0x50(%rbx),%rax
  b4fc14:	lea    0x11f0(%rsp),%r12
  b4fc1c:	lea    0x1200(%rsp),%rbp
  b4fc24:	mov    %r12,%rdi
  b4fc27:	mov    0x444(%rax),%esi
  b4fc2d:	call   c913a0 <_ZN7STRINGS17GetValueAsWStringEi>
  b4fc32:	mov    $0x14c7348,%esi
  b4fc37:	mov    %rbp,%rdi
  b4fc3a:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  b4fc3f:	mov    $0xfe4ec0,%edi
  b4fc44:	call   554608 <wcslen@plt>
  b4fc49:	mov    $0xfe4ec0,%esi
  b4fc4e:	mov    %rax,%rdx
  b4fc51:	mov    %rbp,%rdi
  b4fc54:	call   553bc8 <_ZNSbIwSt11char_traitsIwESaIwEE6appendEPKwm@plt>
  b4fc59:	lea    0x1210(%rsp),%r15
  b4fc61:	mov    %r12,%rdx
  b4fc64:	mov    %rbp,%rsi
  b4fc67:	mov    %r15,%rdi
  b4fc6a:	call   7017d0 <_ZStplIwSt11char_traitsIwESaIwEESbIT_T0_T1_ERKS6_S8_>
  b4fc6f:	mov    0x1200(%rsp),%rdi
  b4fc77:	mov    $0x1424540,%r12d
  b4fc7d:	sub    $0x18,%rdi
  b4fc81:	cmp    %r12,%rdi
  b4fc84:	jne    b51a1c <_ZN14CInventoryMenu6updateEf+0x204c>
  b4fc8a:	mov    0x11f0(%rsp),%rdi
  b4fc92:	sub    $0x18,%rdi
  b4fc96:	cmp    %rdi,%r12
  b4fc99:	jne    b518fa <_ZN14CInventoryMenu6updateEf+0x1f2a>
  b4fc9f:	lea    0x11e0(%rsp),%r13
  b4fca7:	mov    0x1210(%rsp),%rsi
  b4fcaf:	lea    0x123f(%rsp),%rdx
  b4fcb7:	mov    %r13,%rdi
  b4fcba:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  b4fcbf:	lea    0x11d0(%rsp),%r14
  b4fcc7:	mov    %r13,%rsi
  b4fcca:	mov    %r14,%rdi
  b4fccd:	call   c8dc90 <_ZN7STRINGS19StringConvertToUTF8ERKSbIwSt11char_traitsIwESaIwEE>
  b4fcd2:	lea    0xb0(%rsp),%rbp
  b4fcda:	mov    0x11d0(%rsp),%rsi
  b4fce2:	mov    %rbp,%rdi
  b4fce5:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b4fcea:	mov    0x11d0(%rsp),%rdi
  b4fcf2:	sub    $0x18,%rdi
  b4fcf6:	cmp    $0x1423a20,%rdi
  b4fcfd:	jne    b51989 <_ZN14CInventoryMenu6updateEf+0x1fb9>
  b4fd03:	mov    0x11e0(%rsp),%rdi
  b4fd0b:	sub    $0x18,%rdi
  b4fd0f:	cmp    %rdi,%r12
  b4fd12:	jne    b51944 <_ZN14CInventoryMenu6updateEf+0x1f74>
  b4fd18:	mov    0x9190(%rbx),%rdi
  b4fd1f:	mov    %rbp,%rsi
  b4fd22:	add    $0xc0,%rdi
  b4fd29:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b4fd2e:	test   %al,%al
  b4fd30:	jne    b50b60 <_ZN14CInventoryMenu6updateEf+0x1190>
  b4fd36:	mov    0x9198(%rbx),%rax
  b4fd3d:	mov    0x50(%rbx),%rdi
  b4fd41:	movzbl 0x732(%rax),%eax
  b4fd48:	cmp    0x70e(%rdi),%al
  b4fd4e:	je     b4fd5d <_ZN14CInventoryMenu6updateEf+0x38d>
  b4fd50:	call   80e850 <_ZN10CCharacter5aliveEv>
  b4fd55:	test   %al,%al
  b4fd57:	jne    b512d8 <_ZN14CInventoryMenu6updateEf+0x1908>
  b4fd5d:	mov    %rbp,%rdi
  b4fd60:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4fd65:	mov    0x1210(%rsp),%rdi
  b4fd6d:	sub    $0x18,%rdi
  b4fd71:	cmp    %rdi,%r12
  b4fd74:	jne    b519d0 <_ZN14CInventoryMenu6updateEf+0x2000>
  b4fd7a:	cmpb   $0x0,0x9162(%rbx)
  b4fd81:	jne    b50530 <_ZN14CInventoryMenu6updateEf+0xb60>
  b4fd87:	cmpb   $0x0,0x9163(%rbx)
  b4fd8e:	jne    b50b90 <_ZN14CInventoryMenu6updateEf+0x11c0>
  b4fd94:	cmpb   $0x0,0x60(%rbx)
  b4fd98:	je     b504c8 <_ZN14CInventoryMenu6updateEf+0xaf8>
  b4fd9e:	mov    0x9170(%rbx),%rdi
  b4fda5:	xor    %esi,%esi
  b4fda7:	lea    0x11c0(%rsp),%r12
  b4fdaf:	movss  0x4c(%rsp),%xmm0
  b4fdb5:	call   8aa4b0 <_ZN13CGenericModel15updateAnimationEfb>
  b4fdba:	mov    0x9170(%rbx),%rax
  b4fdc1:	mov    0x60(%rax),%rdi
  b4fdc5:	call   5536f8 <_ZN4Ogre6Entity16_updateAnimationEv@plt>
  b4fdca:	mov    0x9170(%rbx),%rax
  b4fdd1:	lea    0x123e(%rsp),%rdx
  b4fdd9:	mov    $0xfef76c,%esi
  b4fdde:	mov    %r12,%rdi
  b4fde1:	mov    0x130(%rax),%rbp
  b4fde8:	mov    0x0(%rbp),%rax
  b4fdec:	mov    0x1b0(%rax),%r13
  b4fdf3:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4fdf8:	mov    %r12,%rsi
  b4fdfb:	mov    %rbp,%rdi
  b4fdfe:	call   *%r13
  b4fe01:	mov    0x11c0(%rsp),%rdi
  b4fe09:	mov    %rax,%rbp
  b4fe0c:	sub    $0x18,%rdi
  b4fe10:	cmp    $0x1423a20,%rdi
  b4fe17:	jne    b5187a <_ZN14CInventoryMenu6updateEf+0x1eaa>
  b4fe1d:	cvtsi2ssl 0x50(%rsp),%xmm0
  b4fe23:	cvtsi2ssl 0x58(%rsp),%xmm2
  b4fe29:	movss  %xmm0,0x50(%rsp)
  b4fe2f:	movss  %xmm2,0x60(%rsp)
  b4fe35:	mov    0x9170(%rbx),%rdi
  b4fe3c:	xor    %esi,%esi
  b4fe3e:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  b4fe43:	movq   %xmm0,0x8(%rsp)
  b4fe49:	mov    0x8(%rsp),%rax
  b4fe4e:	mov    %rbp,%rdi
  b4fe51:	movss  %xmm1,0xa8(%rsp)
  b4fe5a:	mov    %rax,0xa0(%rsp)
  b4fe62:	mov    %rax,0x1180(%rsp)
  b4fe6a:	mov    0xa8(%rsp),%eax
  b4fe71:	mov    %eax,0x1188(%rsp)
  b4fe78:	mov    0x0(%rbp),%rax
  b4fe7c:	call   *0x200(%rax)
  b4fe82:	movss  0x4(%rax),%xmm2
  b4fe87:	mov    0x70(%rbx),%rdi
  b4fe8b:	movss  (%rax),%xmm0
  b4fe8f:	addss  0x1184(%rsp),%xmm2
  b4fe98:	addss  0x1180(%rsp),%xmm0
  b4fea1:	movss  %xmm2,0x30(%rsp)
  b4fea7:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4feac:	movss  0x50(%rsp),%xmm6
  b4feb2:	mulss  0x454956(%rip),%xmm6        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b4feba:	movaps %xmm0,%xmm1
  b4febd:	movss  0x30(%rsp),%xmm2
  b4fec3:	movaps %xmm2,%xmm0
  b4fec6:	addss  %xmm6,%xmm1
  b4feca:	movss  %xmm6,0x68(%rsp)
  b4fed0:	mov    0x70(%rbx),%rdi
  b4fed4:	movss  %xmm1,0x20(%rsp)
  b4feda:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4fedf:	movss  %xmm0,0x4c(%rsp)
  b4fee5:	lea    0x1160(%rsp),%rsi
  b4feed:	movss  0x60(%rsp),%xmm0
  b4fef3:	mulss  0x4587f9(%rip),%xmm0        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b4fefb:	movss  0x20(%rsp),%xmm1
  b4ff01:	addss  0x4c(%rsp),%xmm0
  b4ff07:	movss  %xmm0,0x4c(%rsp)
  b4ff0d:	movss  0x45886b(%rip),%xmm0        # fa8780 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xe0>
  b4ff15:	movss  0x4c(%rsp),%xmm14
  b4ff1c:	xorps  %xmm0,%xmm14
  b4ff20:	movss  %xmm14,0x4c(%rsp)
  b4ff27:	movss  %xmm1,0x9184(%rbx)
  b4ff2f:	movl   $0x0,0x1160(%rsp)
  b4ff3a:	movl   $0x0,0x1168(%rsp)
  b4ff45:	movss  %xmm1,0x1164(%rsp)
  b4ff4e:	movss  %xmm14,0x116c(%rsp)
  b4ff58:	mov    0x28(%rbx),%rdi
  b4ff5c:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b4ff61:	mov    0x9170(%rbx),%rax
  b4ff68:	lea    0x11b0(%rsp),%r12
  b4ff70:	lea    0x123d(%rsp),%rdx
  b4ff78:	mov    $0xfef77d,%esi
  b4ff7d:	mov    %r12,%rdi
  b4ff80:	mov    0x130(%rax),%rbp
  b4ff87:	mov    0x0(%rbp),%rax
  b4ff8b:	mov    0x1b0(%rax),%r13
  b4ff92:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4ff97:	mov    %r12,%rsi
  b4ff9a:	mov    %rbp,%rdi
  b4ff9d:	call   *%r13
  b4ffa0:	mov    0x11b0(%rsp),%rdi
  b4ffa8:	mov    %rax,%rbp
  b4ffab:	mov    $0x1423a20,%eax
  b4ffb0:	sub    $0x18,%rdi
  b4ffb4:	cmp    %rdi,%rax
  b4ffb7:	jne    b517c2 <_ZN14CInventoryMenu6updateEf+0x1df2>
  b4ffbd:	mov    0x9170(%rbx),%rdi
  b4ffc4:	xor    %esi,%esi
  b4ffc6:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  b4ffcb:	movq   %xmm0,0x8(%rsp)
  b4ffd1:	mov    0x8(%rsp),%rax
  b4ffd6:	mov    %rbp,%rdi
  b4ffd9:	movss  %xmm1,0xa8(%rsp)
  b4ffe2:	mov    %rax,0xa0(%rsp)
  b4ffea:	mov    %rax,0x1170(%rsp)
  b4fff2:	mov    0xa8(%rsp),%eax
  b4fff9:	mov    %eax,0x1178(%rsp)
  b50000:	mov    0x0(%rbp),%rax
  b50004:	call   *0x200(%rax)
  b5000a:	movss  (%rax),%xmm0
  b5000e:	mov    0x70(%rbx),%rdi
  b50012:	addss  0x1170(%rsp),%xmm0
  b5001b:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b50020:	movss  0x68(%rsp),%xmm2
  b50026:	movl   $0x0,0x1150(%rsp)
  b50031:	addss  %xmm0,%xmm2
  b50035:	movss  0x4c(%rsp),%xmm6
  b5003b:	movss  %xmm6,0x115c(%rsp)
  b50044:	movl   $0x0,0x1158(%rsp)
  b5004f:	lea    0x1150(%rsp),%rsi
  b50057:	movss  %xmm2,0x58(%rsp)
  b5005d:	movss  %xmm2,0x1154(%rsp)
  b50066:	mov    0x48(%rbx),%rdi
  b5006a:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5006f:	mov    0x70(%rbx),%rdi
  b50073:	movss  0x4586bd(%rip),%xmm0        # fa8738 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x98>
  b5007b:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b50080:	addss  0x58(%rsp),%xmm0
  b50086:	cmpq   $0x0,0x9158(%rbx)
  b5008e:	minss  0x50(%rsp),%xmm0
  b50094:	movss  %xmm0,0x9180(%rbx)
  b5009c:	je     b5020c <_ZN14CInventoryMenu6updateEf+0x83c>
  b500a2:	mov    0x70(%rbx),%rdi
  b500a6:	movss  0x9184(%rbx),%xmm4
  b500ae:	movss  0x49fc9a(%rip),%xmm0        # fefd50 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x30>
  b500b6:	movss  %xmm4,0x10(%rsp)
  b500bc:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b500c1:	movss  0x10(%rsp),%xmm4
  b500c7:	addss  %xmm0,%xmm4
  b500cb:	mov    0x70(%rbx),%rdi
  b500cf:	movss  0x49fc7d(%rip),%xmm0        # fefd54 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x34>
  b500d7:	divss  0x50(%rsp),%xmm4
  b500dd:	movss  %xmm4,0x10(%rsp)
  b500e3:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b500e8:	movaps %xmm0,%xmm1
  b500eb:	mov    0x70(%rbx),%rdi
  b500ef:	movss  0x49fc61(%rip),%xmm0        # fefd58 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x38>
  b500f7:	divss  0x60(%rsp),%xmm1
  b500fd:	movss  %xmm1,0x20(%rsp)
  b50103:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b50108:	movaps %xmm0,%xmm5
  b5010b:	mov    0x70(%rbx),%rdi
  b5010f:	movss  0x49fc45(%rip),%xmm0        # fefd5c <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x3c>
  b50117:	divss  0x50(%rsp),%xmm5
  b5011d:	movss  %xmm5,0x30(%rsp)
  b50123:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b50128:	movss  0x10(%rsp),%xmm4
  b5012e:	movaps %xmm0,%xmm3
  b50131:	movaps %xmm4,%xmm0
  b50134:	movss  0x30(%rsp),%xmm5
  b5013a:	addss  %xmm5,%xmm0
  b5013e:	divss  0x60(%rsp),%xmm3
  b50144:	movss  0x20(%rsp),%xmm1
  b5014a:	ucomiss 0x4546ab(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b50151:	jbe    b5015f <_ZN14CInventoryMenu6updateEf+0x78f>
  b50153:	movss  0x4546a1(%rip),%xmm5        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b5015b:	subss  %xmm4,%xmm5
  b5015f:	movaps %xmm1,%xmm0
  b50162:	addss  %xmm3,%xmm0
  b50166:	ucomiss 0x45468f(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b5016d:	jbe    b5017b <_ZN14CInventoryMenu6updateEf+0x7ab>
  b5016f:	movss  0x454685(%rip),%xmm3        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b50177:	subss  %xmm1,%xmm3
  b5017b:	xorps  %xmm14,%xmm14
  b5017f:	movaps %xmm4,%xmm0
  b50182:	movaps %xmm4,%xmm2
  b50185:	cmpnltss %xmm14,%xmm0
  b5018b:	movaps %xmm0,%xmm4
  b5018e:	andps  %xmm0,%xmm2
  b50191:	andnps %xmm14,%xmm4
  b50195:	maxss  %xmm1,%xmm14
  b5019a:	orps   %xmm2,%xmm4
  b5019d:	movss  0x454657(%rip),%xmm2        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b501a5:	movaps %xmm14,%xmm1
  b501a9:	divss  0x50(%rsp),%xmm2
  b501af:	ucomiss %xmm5,%xmm2
  b501b2:	ja     b50b78 <_ZN14CInventoryMenu6updateEf+0x11a8>
  b501b8:	movaps %xmm5,%xmm2
  b501bb:	mov    0x9158(%rbx),%rdi
  b501c2:	movaps %xmm4,%xmm0
  b501c5:	call   552ba8 <_ZN4Ogre8Viewport13setDimensionsEffff@plt>
  b501ca:	mov    0x9148(%rbx),%rax
  b501d1:	mov    0x9158(%rbx),%rdi
  b501d8:	mov    (%rax),%rax
  b501db:	mov    0x278(%rax),%rbp
  b501e2:	call   553978 <_ZNK4Ogre8Viewport14getActualWidthEv@plt>
  b501e7:	mov    0x9158(%rbx),%rdi
  b501ee:	mov    %eax,%r12d
  b501f1:	call   554968 <_ZNK4Ogre8Viewport15getActualHeightEv@plt>
  b501f6:	cvtsi2ss %r12d,%xmm0
  b501fb:	mov    0x9148(%rbx),%rdi
  b50202:	cvtsi2ss %eax,%xmm1
  b50206:	divss  %xmm1,%xmm0
  b5020a:	call   *%rbp
  b5020c:	cmpb   $0x0,0x60(%rbx)
  b50210:	jne    b5021c <_ZN14CInventoryMenu6updateEf+0x84c>
  b50212:	cmpb   $0x0,0x61(%rbx)
  b50216:	je     b5132c <_ZN14CInventoryMenu6updateEf+0x195c>
  b5021c:	cmpb   $0x0,0x9161(%rbx)
  b50223:	je     b50308 <_ZN14CInventoryMenu6updateEf+0x938>
  b50229:	mov    0x50(%rbx),%rax
  b5022d:	test   %rax,%rax
  b50230:	je     b50308 <_ZN14CInventoryMenu6updateEf+0x938>
  b50236:	mov    0x1c8(%rax),%rdi
  b5023d:	mov    0x9168(%rbx),%rsi
  b50244:	test   %rdi,%rdi
  b50247:	je     b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b5024d:	call   cca620 <_ZN13CSkillManager14getSkillByGuidEx>
  b50252:	test   %rax,%rax
  b50255:	je     b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b5025b:	mov    0x70(%rbx),%rdx
  b5025f:	mov    0x50(%rbx),%rsi
  b50263:	mov    0x91a0(%rbx),%rdi
  b5026a:	cvtsi2ssq 0x12d0(%rdx),%xmm0
  b50273:	cvtsi2ssq 0x12d8(%rdx),%xmm1
  b5027c:	mov    %rax,%rdx
  b5027f:	call   aaeeb0 <_ZN13CSkillTooltip11showTooltipEP9CBaseUnitP6CSkillff>
  b50284:	jmp    b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b50289:	nopl   0x0(%rax)
  b50290:	lea    0x1220(%rsp),%rbp
  b50298:	call   e16d60 <_ZN16CStringTranslate11getSingltonEv>
  b5029d:	mov    %rbp,%rdi
  b502a0:	mov    %rax,%rsi
  b502a3:	mov    $0xfefb4c,%edx
  b502a8:	call   e16ef0 <_ZN16CStringTranslate18getTranslateStringEPKw>
  b502ad:	mov    %rbp,%rsi
  b502b0:	mov    $0x14c7348,%edi
  b502b5:	call   556038 <_ZNSbIwSt11char_traitsIwESaIwEE6assignERKS2_@plt>
  b502ba:	mov    0x1220(%rsp),%rdi
  b502c2:	sub    $0x18,%rdi
  b502c6:	cmp    $0x1424540,%rdi
  b502cd:	je     b4fc10 <_ZN14CInventoryMenu6updateEf+0x240>
  b502d3:	mov    $0x5541c8,%eax
  b502d8:	test   %rax,%rax
  b502db:	je     b51970 <_ZN14CInventoryMenu6updateEf+0x1fa0>
  b502e1:	or     $0xffffffff,%eax
  b502e4:	lock xadd %eax,0x10(%rdi)
  b502e9:	test   %eax,%eax
  b502eb:	jg     b4fc10 <_ZN14CInventoryMenu6updateEf+0x240>
  b502f1:	lea    0x123a(%rsp),%rsi
  b502f9:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b502fe:	jmp    b4fc10 <_ZN14CInventoryMenu6updateEf+0x240>
  b50303:	nopl   0x0(%rax,%rax,1)
  b50308:	mov    0x91a0(%rbx),%rax
  b5030f:	mov    0x30(%rax),%rsi
  b50313:	mov    0xb0(%rsi),%rdi
  b5031a:	test   %rdi,%rdi
  b5031d:	je     b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b5031f:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b50324:	add    $0x1248,%rsp
  b5032b:	pop    %rbx
  b5032c:	pop    %rbp
  b5032d:	pop    %r12
  b5032f:	pop    %r13
  b50331:	pop    %r14
  b50333:	pop    %r15
  b50335:	ret
  b50336:	cs nopw 0x0(%rax,%rax,1)
  b50340:	mov    0x9108(%rbx),%rdi
  b50347:	xor    %esi,%esi
  b50349:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  b5034e:	test   %al,%al
  b50350:	jne    b514a8 <_ZN14CInventoryMenu6updateEf+0x1ad8>
  b50356:	movss  0x91ac(%rbx),%xmm0
  b5035e:	ucomiss 0x4544ab(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b50365:	jbe    b51180 <_ZN14CInventoryMenu6updateEf+0x17b0>
  b5036b:	mov    $0xf,%esi
  b50370:	mov    %r13,%rdi
  b50373:	movq   $0x20,0xe78(%rsp)
  b5037f:	movq   $0x0,0xe80(%rsp)
  b5038b:	movq   $0x0,0xe90(%rsp)
  b50397:	movq   $0x0,0xe88(%rsp)
  b503a3:	movq   $0x0,0xf18(%rsp)
  b503af:	movq   $0x0,0xe70(%rsp)
  b503bb:	movl   $0x0,0xe98(%rsp)
  b503c6:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b503cb:	cmpq   $0x20,0xe78(%rsp)
  b503d4:	lea    0x28(%r13),%rdx
  b503d8:	jbe    b503e2 <_ZN14CInventoryMenu6updateEf+0xa12>
  b503da:	mov    0xf18(%rsp),%rdx
  b503e2:	mov    $0xfef75c,%eax
  b503e7:	nopw   0x0(%rax,%rax,1)
  b503f0:	movzbl (%rax),%ecx
  b503f3:	add    $0x1,%rax
  b503f7:	mov    %ecx,(%rdx)
  b503f9:	add    $0x4,%rdx
  b503fd:	cmp    $0xfef76b,%rax
  b50403:	jne    b503f0 <_ZN14CInventoryMenu6updateEf+0xa20>
  b50405:	cmpq   $0x20,0xe78(%rsp)
  b5040e:	movq   $0xf,0xe70(%rsp)
  b5041a:	mov    0x68(%rsp),%rax
  b5041f:	jbe    b5042d <_ZN14CInventoryMenu6updateEf+0xa5d>
  b50421:	mov    0xf18(%rsp),%rax
  b50429:	add    $0x3c,%rax
  b5042d:	movl   $0x0,(%rax)
  b50433:	mov    0x9120(%rbx),%rsi
  b5043a:	lea    0xdc0(%rsp),%rdi
  b50442:	mov    %r13,%rdx
  b50445:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5044a:	mov    0x58(%rsp),%rsi
  b5044f:	lea    0xdc0(%rsp),%rdi
  b50457:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b5045c:	lea    0xdc0(%rsp),%rdi
  b50464:	mov    %al,0x9f(%rsp)
  b5046b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b50470:	mov    %r13,%rdi
  b50473:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b50478:	cmpb   $0x0,0x9f(%rsp)
  b50480:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b50486:	lea    0xd10(%rsp),%rdi
  b5048e:	mov    $0xfef75c,%esi
  b50493:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b50498:	mov    0x9120(%rbx),%rdi
  b5049f:	mov    0x58(%rsp),%rdx
  b504a4:	lea    0xd10(%rsp),%rsi
  b504ac:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b504b1:	lea    0xd10(%rsp),%rdi
  b504b9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b504be:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b504c3:	nopl   0x0(%rax,%rax,1)
  b504c8:	mov    0x30(%rbx),%rdi
  b504cc:	xor    %esi,%esi
  b504ce:	movq   $0x0,0x1020(%rbx)
  b504d9:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b504de:	mov    0x38(%rbx),%rdi
  b504e2:	xor    %esi,%esi
  b504e4:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b504e9:	cmpb   $0x0,0x60(%rbx)
  b504ed:	jne    b4fd9e <_ZN14CInventoryMenu6updateEf+0x3ce>
  b504f3:	cmpb   $0x0,0x61(%rbx)
  b504f7:	je     b4fd9e <_ZN14CInventoryMenu6updateEf+0x3ce>
  b504fd:	mov    0x91a0(%rbx),%rax
  b50504:	test   %rax,%rax
  b50507:	je     b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b5050d:	mov    0x30(%rax),%rsi
  b50511:	mov    0xb0(%rsi),%rdi
  b50518:	test   %rdi,%rdi
  b5051b:	jne    b5031f <_ZN14CInventoryMenu6updateEf+0x94f>
  b50521:	jmp    b50324 <_ZN14CInventoryMenu6updateEf+0x954>
  b50526:	cs nopw 0x0(%rax,%rax,1)
  b50530:	mov    0x50(%rbx),%rax
  b50534:	mov    0x208(%rax),%rdi
  b5053b:	mov    (%rdi),%rax
  b5053e:	call   *0xe8(%rax)
  b50544:	mov    (%rax),%rdx
  b50547:	movss  0x4c(%rsp),%xmm0
  b5054d:	mulss  0x49f80b(%rip),%xmm0        # fefd60 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x40>
  b50555:	lea    0x10d0(%rsp),%rdi
  b5055d:	mov    %rdx,0x1110(%rsp)
  b50565:	mov    0x8(%rax),%rdx
  b50569:	mov    %rdx,0x1118(%rsp)
  b50571:	mov    0x10(%rax),%rdx
  b50575:	mov    %rdx,0x1120(%rsp)
  b5057d:	mov    0x18(%rax),%rdx
  b50581:	mov    %rdx,0x1128(%rsp)
  b50589:	mov    0x20(%rax),%rdx
  b5058d:	mov    %rdx,0x1130(%rsp)
  b50595:	mov    0x28(%rax),%rdx
  b50599:	mov    %rdx,0x1138(%rsp)
  b505a1:	mov    0x30(%rax),%rdx
  b505a5:	mov    %rdx,0x1140(%rsp)
  b505ad:	mov    0x38(%rax),%rax
  b505b1:	mov    %rax,0x1148(%rsp)
  b505b9:	call   c7a2a0 <_ZN4MATH15matrixRotationYERN4Ogre7Matrix4Ef>
  b505be:	movss  0x1110(%rsp),%xmm0
  b505c7:	lea    0x1110(%rsp),%rsi
  b505cf:	movss  0x1114(%rsp),%xmm13
  b505d9:	xor    %edx,%edx
  b505db:	movaps %xmm0,%xmm1
  b505de:	movaps %xmm13,%xmm2
  b505e2:	movss  0x10d0(%rsp),%xmm10
  b505ec:	movss  0x10e0(%rsp),%xmm9
  b505f6:	mulss  %xmm10,%xmm1
  b505fb:	mulss  %xmm9,%xmm2
  b50600:	movss  0x1118(%rsp),%xmm12
  b5060a:	movss  0x10f0(%rsp),%xmm8
  b50614:	movss  0x111c(%rsp),%xmm11
  b5061e:	movaps %xmm0,%xmm14
  b50622:	movss  0x1100(%rsp),%xmm7
  b5062b:	addss  %xmm2,%xmm1
  b5062f:	movaps %xmm12,%xmm2
  b50633:	movss  0x10d4(%rsp),%xmm6
  b5063c:	mulss  %xmm8,%xmm2
  b50641:	movss  0x10e4(%rsp),%xmm5
  b5064a:	movss  0x10f4(%rsp),%xmm4
  b50653:	movss  0x1104(%rsp),%xmm3
  b5065c:	movaps %xmm13,%xmm15
  b50660:	addss  %xmm2,%xmm1
  b50664:	movaps %xmm11,%xmm2
  b50668:	mulss  %xmm7,%xmm2
  b5066c:	addss  %xmm2,%xmm1
  b50670:	movaps %xmm13,%xmm2
  b50674:	mulss  0x10ec(%rsp),%xmm13
  b5067e:	mulss  %xmm5,%xmm2
  b50682:	movss  %xmm1,0x1010(%rsp)
  b5068b:	movaps %xmm0,%xmm1
  b5068e:	mulss  0x10dc(%rsp),%xmm0
  b50697:	mulss  %xmm6,%xmm1
  b5069b:	addss  %xmm2,%xmm1
  b5069f:	movaps %xmm12,%xmm2
  b506a3:	addss  %xmm13,%xmm0
  b506a8:	movss  0x1124(%rsp),%xmm13
  b506b2:	mulss  %xmm4,%xmm2
  b506b6:	addss  %xmm2,%xmm1
  b506ba:	movaps %xmm11,%xmm2
  b506be:	mulss  %xmm3,%xmm2
  b506c2:	addss  %xmm2,%xmm1
  b506c6:	movss  0x10d8(%rsp),%xmm2
  b506cf:	mulss  %xmm2,%xmm14
  b506d4:	movss  %xmm1,0x1014(%rsp)
  b506dd:	movss  0x10e8(%rsp),%xmm1
  b506e6:	mulss  %xmm1,%xmm15
  b506eb:	addss  %xmm15,%xmm14
  b506f0:	movss  0x10f8(%rsp),%xmm15
  b506fa:	mulss  %xmm12,%xmm15
  b506ff:	mulss  0x10fc(%rsp),%xmm12
  b50709:	addss  %xmm15,%xmm14
  b5070e:	movss  0x1108(%rsp),%xmm15
  b50718:	mulss  %xmm11,%xmm15
  b5071d:	mulss  0x110c(%rsp),%xmm11
  b50727:	addss  %xmm12,%xmm0
  b5072c:	movss  0x1128(%rsp),%xmm12
  b50736:	addss  %xmm15,%xmm14
  b5073b:	movaps %xmm9,%xmm15
  b5073f:	mulss  %xmm13,%xmm15
  b50744:	addss  %xmm11,%xmm0
  b50749:	movss  0x112c(%rsp),%xmm11
  b50753:	movss  %xmm14,0x1018(%rsp)
  b5075d:	movss  0x1120(%rsp),%xmm14
  b50767:	movss  %xmm0,0x101c(%rsp)
  b50770:	movaps %xmm10,%xmm0
  b50774:	mulss  %xmm14,%xmm0
  b50779:	addss  %xmm15,%xmm0
  b5077e:	movaps %xmm8,%xmm15
  b50782:	mulss  %xmm12,%xmm15
  b50787:	addss  %xmm15,%xmm0
  b5078c:	movaps %xmm7,%xmm15
  b50790:	mulss  %xmm11,%xmm15
  b50795:	addss  %xmm15,%xmm0
  b5079a:	movaps %xmm5,%xmm15
  b5079e:	mulss  %xmm13,%xmm15
  b507a3:	movss  %xmm0,0x1020(%rsp)
  b507ac:	movaps %xmm6,%xmm0
  b507af:	mulss  %xmm14,%xmm0
  b507b4:	addss  %xmm15,%xmm0
  b507b9:	movaps %xmm4,%xmm15
  b507bd:	mulss  %xmm12,%xmm15
  b507c2:	addss  %xmm15,%xmm0
  b507c7:	movaps %xmm3,%xmm15
  b507cb:	mulss  %xmm11,%xmm15
  b507d0:	addss  %xmm15,%xmm0
  b507d5:	movaps %xmm1,%xmm15
  b507d9:	mulss  %xmm13,%xmm15
  b507de:	mulss  0x10ec(%rsp),%xmm13
  b507e8:	movss  %xmm0,0x1024(%rsp)
  b507f1:	movaps %xmm2,%xmm0
  b507f4:	mulss  %xmm14,%xmm0
  b507f9:	mulss  0x10dc(%rsp),%xmm14
  b50803:	addss  %xmm15,%xmm0
  b50808:	movss  0x10f8(%rsp),%xmm15
  b50812:	mulss  %xmm12,%xmm15
  b50817:	mulss  0x10fc(%rsp),%xmm12
  b50821:	addss  %xmm13,%xmm14
  b50826:	addss  %xmm15,%xmm0
  b5082b:	movss  0x1108(%rsp),%xmm15
  b50835:	mulss  %xmm11,%xmm15
  b5083a:	mulss  0x110c(%rsp),%xmm11
  b50844:	addss  %xmm12,%xmm14
  b50849:	addss  %xmm15,%xmm0
  b5084e:	movaps %xmm9,%xmm15
  b50852:	addss  %xmm11,%xmm14
  b50857:	movss  %xmm0,0x1028(%rsp)
  b50860:	movaps %xmm10,%xmm0
  b50864:	movss  %xmm14,0x102c(%rsp)
  b5086e:	mov    0x1010(%rsp),%rax
  b50876:	movss  0x1130(%rsp),%xmm14
  b50880:	movss  0x1134(%rsp),%xmm13
  b5088a:	mulss  %xmm14,%xmm0
  b5088f:	mulss  %xmm13,%xmm15
  b50894:	movss  0x1138(%rsp),%xmm12
  b5089e:	movss  0x113c(%rsp),%xmm11
  b508a8:	mov    %rax,0x1110(%rsp)
  b508b0:	mov    0x1018(%rsp),%rax
  b508b8:	addss  %xmm15,%xmm0
  b508bd:	movaps %xmm8,%xmm15
  b508c1:	mov    %rax,0x1118(%rsp)
  b508c9:	mov    0x1020(%rsp),%rax
  b508d1:	mulss  %xmm12,%xmm15
  b508d6:	addss  %xmm15,%xmm0
  b508db:	movaps %xmm7,%xmm15
  b508df:	mulss  %xmm11,%xmm15
  b508e4:	addss  %xmm15,%xmm0
  b508e9:	movaps %xmm5,%xmm15
  b508ed:	mulss  %xmm13,%xmm15
  b508f2:	movss  %xmm0,0x1030(%rsp)
  b508fb:	movaps %xmm6,%xmm0
  b508fe:	mulss  %xmm14,%xmm0
  b50903:	addss  %xmm15,%xmm0
  b50908:	movaps %xmm4,%xmm15
  b5090c:	mulss  %xmm12,%xmm15
  b50911:	addss  %xmm15,%xmm0
  b50916:	movaps %xmm3,%xmm15
  b5091a:	mulss  %xmm11,%xmm15
  b5091f:	addss  %xmm15,%xmm0
  b50924:	movaps %xmm1,%xmm15
  b50928:	mulss  %xmm13,%xmm15
  b5092d:	mulss  0x10ec(%rsp),%xmm13
  b50937:	movss  %xmm0,0x1034(%rsp)
  b50940:	movaps %xmm2,%xmm0
  b50943:	mulss  %xmm14,%xmm0
  b50948:	mulss  0x10dc(%rsp),%xmm14
  b50952:	addss  %xmm15,%xmm0
  b50957:	movss  0x10f8(%rsp),%xmm15
  b50961:	mulss  %xmm12,%xmm15
  b50966:	mulss  0x10fc(%rsp),%xmm12
  b50970:	addss  %xmm13,%xmm14
  b50975:	movss  0x1140(%rsp),%xmm13
  b5097f:	mulss  %xmm13,%xmm2
  b50984:	addss  %xmm15,%xmm0
  b50989:	movss  0x1108(%rsp),%xmm15
  b50993:	mulss  %xmm11,%xmm15
  b50998:	mulss  0x110c(%rsp),%xmm11
  b509a2:	addss  %xmm12,%xmm14
  b509a7:	movss  0x1144(%rsp),%xmm12
  b509b1:	mulss  %xmm12,%xmm1
  b509b6:	mulss  %xmm12,%xmm9
  b509bb:	addss  %xmm15,%xmm0
  b509c0:	mulss  %xmm12,%xmm5
  b509c5:	mulss  %xmm13,%xmm10
  b509ca:	mulss  0x10ec(%rsp),%xmm12
  b509d4:	addss  %xmm11,%xmm14
  b509d9:	mulss  %xmm13,%xmm6
  b509de:	movss  0x1148(%rsp),%xmm11
  b509e8:	mulss  0x10dc(%rsp),%xmm13
  b509f2:	addss  %xmm1,%xmm2
  b509f6:	movss  %xmm0,0x1038(%rsp)
  b509ff:	movss  0x10f8(%rsp),%xmm1
  b50a08:	mulss  %xmm11,%xmm8
  b50a0d:	mulss  %xmm11,%xmm1
  b50a12:	addss  %xmm9,%xmm10
  b50a17:	movss  %xmm14,0x103c(%rsp)
  b50a21:	mulss  %xmm11,%xmm4
  b50a26:	addss  %xmm5,%xmm6
  b50a2a:	mulss  0x10fc(%rsp),%xmm11
  b50a34:	movss  0x114c(%rsp),%xmm0
  b50a3d:	addss  %xmm12,%xmm13
  b50a42:	mulss  %xmm0,%xmm7
  b50a46:	addss  %xmm1,%xmm2
  b50a4a:	movss  0x1108(%rsp),%xmm1
  b50a53:	mulss  %xmm0,%xmm3
  b50a57:	addss  %xmm8,%xmm10
  b50a5c:	mulss  %xmm0,%xmm1
  b50a60:	addss  %xmm4,%xmm6
  b50a64:	mulss  0x110c(%rsp),%xmm0
  b50a6d:	addss  %xmm11,%xmm13
  b50a72:	addss  %xmm7,%xmm10
  b50a77:	addss  %xmm3,%xmm6
  b50a7b:	addss  %xmm1,%xmm2
  b50a7f:	addss  %xmm0,%xmm13
  b50a84:	movss  %xmm10,0x1040(%rsp)
  b50a8e:	movss  %xmm6,0x1044(%rsp)
  b50a97:	movss  %xmm2,0x1048(%rsp)
  b50aa0:	movss  %xmm13,0x104c(%rsp)
  b50aaa:	mov    %rax,0x1120(%rsp)
  b50ab2:	mov    0x1028(%rsp),%rax
  b50aba:	mov    %rax,0x1128(%rsp)
  b50ac2:	mov    0x1030(%rsp),%rax
  b50aca:	mov    %rax,0x1130(%rsp)
  b50ad2:	mov    0x1038(%rsp),%rax
  b50ada:	mov    %rax,0x1138(%rsp)
  b50ae2:	mov    0x1040(%rsp),%rax
  b50aea:	mov    %rax,0x1140(%rsp)
  b50af2:	mov    0x1048(%rsp),%rax
  b50afa:	mov    %rax,0x1148(%rsp)
  b50b02:	mov    0x50(%rbx),%rax
  b50b06:	mov    0x208(%rax),%rdi
  b50b0d:	mov    (%rdi),%rax
  b50b10:	call   *0x118(%rax)
  b50b16:	jmp    b4fd94 <_ZN14CInventoryMenu6updateEf+0x3c4>
  b50b1b:	nopl   0x0(%rax,%rax,1)
  b50b20:	mov    $0x14c7340,%edi
  b50b25:	call   553558 <__cxa_guard_acquire@plt>
  b50b2a:	test   %eax,%eax
  b50b2c:	je     b4fbfe <_ZN14CInventoryMenu6updateEf+0x22e>
  b50b32:	mov    $0x14c7340,%edi
  b50b37:	movq   $0x1424558,0x976806(%rip)        # 14c7348 <_ZZN14CInventoryMenu6updateEfE4g_GP>
  b50b42:	call   553fc8 <__cxa_guard_release@plt>
  b50b47:	mov    $0xf9f788,%edx
  b50b4c:	mov    $0x14c7348,%esi
  b50b51:	mov    $0x5548d8,%edi
  b50b56:	call   5551e8 <__cxa_atexit@plt>
  b50b5b:	jmp    b4fbfe <_ZN14CInventoryMenu6updateEf+0x22e>
  b50b60:	mov    0x9190(%rbx),%rdi
  b50b67:	mov    %rbp,%rsi
  b50b6a:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  b50b6f:	jmp    b4fd36 <_ZN14CInventoryMenu6updateEf+0x366>
  b50b74:	nopl   0x0(%rax)
  b50b78:	movss  0x453c7c(%rip),%xmm4        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b50b80:	subss  %xmm2,%xmm4
  b50b84:	jmp    b501bb <_ZN14CInventoryMenu6updateEf+0x7eb>
  b50b89:	nopl   0x0(%rax)
  b50b90:	mov    0x50(%rbx),%rax
  b50b94:	mov    0x208(%rax),%rdi
  b50b9b:	mov    (%rdi),%rax
  b50b9e:	call   *0xe8(%rax)
  b50ba4:	mov    (%rax),%rdx
  b50ba7:	movss  0x4c(%rsp),%xmm0
  b50bad:	mulss  0x49f1af(%rip),%xmm0        # fefd64 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x44>
  b50bb5:	lea    0x1050(%rsp),%rdi
  b50bbd:	mov    %rdx,0x1090(%rsp)
  b50bc5:	mov    0x8(%rax),%rdx
  b50bc9:	mov    %rdx,0x1098(%rsp)
  b50bd1:	mov    0x10(%rax),%rdx
  b50bd5:	mov    %rdx,0x10a0(%rsp)
  b50bdd:	mov    0x18(%rax),%rdx
  b50be1:	mov    %rdx,0x10a8(%rsp)
  b50be9:	mov    0x20(%rax),%rdx
  b50bed:	mov    %rdx,0x10b0(%rsp)
  b50bf5:	mov    0x28(%rax),%rdx
  b50bf9:	mov    %rdx,0x10b8(%rsp)
  b50c01:	mov    0x30(%rax),%rdx
  b50c05:	mov    %rdx,0x10c0(%rsp)
  b50c0d:	mov    0x38(%rax),%rax
  b50c11:	mov    %rax,0x10c8(%rsp)
  b50c19:	call   c7a2a0 <_ZN4MATH15matrixRotationYERN4Ogre7Matrix4Ef>
  b50c1e:	movss  0x1090(%rsp),%xmm0
  b50c27:	lea    0x1090(%rsp),%rsi
  b50c2f:	movss  0x1094(%rsp),%xmm13
  b50c39:	xor    %edx,%edx
  b50c3b:	movaps %xmm0,%xmm1
  b50c3e:	movaps %xmm13,%xmm2
  b50c42:	movss  0x1050(%rsp),%xmm10
  b50c4c:	movss  0x1060(%rsp),%xmm9
  b50c56:	mulss  %xmm10,%xmm1
  b50c5b:	mulss  %xmm9,%xmm2
  b50c60:	movss  0x1098(%rsp),%xmm12
  b50c6a:	movss  0x1070(%rsp),%xmm8
  b50c74:	movss  0x109c(%rsp),%xmm11
  b50c7e:	movaps %xmm0,%xmm14
  b50c82:	movss  0x1080(%rsp),%xmm7
  b50c8b:	addss  %xmm2,%xmm1
  b50c8f:	movaps %xmm12,%xmm2
  b50c93:	movss  0x1054(%rsp),%xmm6
  b50c9c:	mulss  %xmm8,%xmm2
  b50ca1:	movss  0x1064(%rsp),%xmm5
  b50caa:	movss  0x1074(%rsp),%xmm4
  b50cb3:	movss  0x1084(%rsp),%xmm3
  b50cbc:	movaps %xmm13,%xmm15
  b50cc0:	addss  %xmm2,%xmm1
  b50cc4:	movaps %xmm11,%xmm2
  b50cc8:	mulss  %xmm7,%xmm2
  b50ccc:	addss  %xmm2,%xmm1
  b50cd0:	movaps %xmm13,%xmm2
  b50cd4:	mulss  0x106c(%rsp),%xmm13
  b50cde:	mulss  %xmm5,%xmm2
  b50ce2:	movss  %xmm1,0xfd0(%rsp)
  b50ceb:	movaps %xmm0,%xmm1
  b50cee:	mulss  0x105c(%rsp),%xmm0
  b50cf7:	mulss  %xmm6,%xmm1
  b50cfb:	addss  %xmm2,%xmm1
  b50cff:	movaps %xmm12,%xmm2
  b50d03:	addss  %xmm13,%xmm0
  b50d08:	movss  0x10a4(%rsp),%xmm13
  b50d12:	mulss  %xmm4,%xmm2
  b50d16:	addss  %xmm2,%xmm1
  b50d1a:	movaps %xmm11,%xmm2
  b50d1e:	mulss  %xmm3,%xmm2
  b50d22:	addss  %xmm2,%xmm1
  b50d26:	movss  0x1058(%rsp),%xmm2
  b50d2f:	mulss  %xmm2,%xmm14
  b50d34:	movss  %xmm1,0xfd4(%rsp)
  b50d3d:	movss  0x1068(%rsp),%xmm1
  b50d46:	mulss  %xmm1,%xmm15
  b50d4b:	addss  %xmm15,%xmm14
  b50d50:	movss  0x1078(%rsp),%xmm15
  b50d5a:	mulss  %xmm12,%xmm15
  b50d5f:	mulss  0x107c(%rsp),%xmm12
  b50d69:	addss  %xmm15,%xmm14
  b50d6e:	movss  0x1088(%rsp),%xmm15
  b50d78:	mulss  %xmm11,%xmm15
  b50d7d:	mulss  0x108c(%rsp),%xmm11
  b50d87:	addss  %xmm12,%xmm0
  b50d8c:	movss  0x10a8(%rsp),%xmm12
  b50d96:	addss  %xmm15,%xmm14
  b50d9b:	movaps %xmm9,%xmm15
  b50d9f:	mulss  %xmm13,%xmm15
  b50da4:	addss  %xmm11,%xmm0
  b50da9:	movss  0x10ac(%rsp),%xmm11
  b50db3:	movss  %xmm14,0xfd8(%rsp)
  b50dbd:	movss  0x10a0(%rsp),%xmm14
  b50dc7:	movss  %xmm0,0xfdc(%rsp)
  b50dd0:	movaps %xmm10,%xmm0
  b50dd4:	mulss  %xmm14,%xmm0
  b50dd9:	addss  %xmm15,%xmm0
  b50dde:	movaps %xmm8,%xmm15
  b50de2:	mulss  %xmm12,%xmm15
  b50de7:	addss  %xmm15,%xmm0
  b50dec:	movaps %xmm7,%xmm15
  b50df0:	mulss  %xmm11,%xmm15
  b50df5:	addss  %xmm15,%xmm0
  b50dfa:	movaps %xmm5,%xmm15
  b50dfe:	mulss  %xmm13,%xmm15
  b50e03:	movss  %xmm0,0xfe0(%rsp)
  b50e0c:	movaps %xmm6,%xmm0
  b50e0f:	mulss  %xmm14,%xmm0
  b50e14:	addss  %xmm15,%xmm0
  b50e19:	movaps %xmm4,%xmm15
  b50e1d:	mulss  %xmm12,%xmm15
  b50e22:	addss  %xmm15,%xmm0
  b50e27:	movaps %xmm3,%xmm15
  b50e2b:	mulss  %xmm11,%xmm15
  b50e30:	addss  %xmm15,%xmm0
  b50e35:	movaps %xmm1,%xmm15
  b50e39:	mulss  %xmm13,%xmm15
  b50e3e:	mulss  0x106c(%rsp),%xmm13
  b50e48:	movss  %xmm0,0xfe4(%rsp)
  b50e51:	movaps %xmm2,%xmm0
  b50e54:	mulss  %xmm14,%xmm0
  b50e59:	mulss  0x105c(%rsp),%xmm14
  b50e63:	addss  %xmm15,%xmm0
  b50e68:	movss  0x1078(%rsp),%xmm15
  b50e72:	mulss  %xmm12,%xmm15
  b50e77:	mulss  0x107c(%rsp),%xmm12
  b50e81:	addss  %xmm13,%xmm14
  b50e86:	addss  %xmm15,%xmm0
  b50e8b:	movss  0x1088(%rsp),%xmm15
  b50e95:	mulss  %xmm11,%xmm15
  b50e9a:	mulss  0x108c(%rsp),%xmm11
  b50ea4:	addss  %xmm12,%xmm14
  b50ea9:	addss  %xmm15,%xmm0
  b50eae:	movaps %xmm9,%xmm15
  b50eb2:	addss  %xmm11,%xmm14
  b50eb7:	movss  %xmm0,0xfe8(%rsp)
  b50ec0:	movaps %xmm10,%xmm0
  b50ec4:	movss  %xmm14,0xfec(%rsp)
  b50ece:	mov    0xfd0(%rsp),%rax
  b50ed6:	movss  0x10b0(%rsp),%xmm14
  b50ee0:	movss  0x10b4(%rsp),%xmm13
  b50eea:	mulss  %xmm14,%xmm0
  b50eef:	mulss  %xmm13,%xmm15
  b50ef4:	movss  0x10b8(%rsp),%xmm12
  b50efe:	movss  0x10bc(%rsp),%xmm11
  b50f08:	mov    %rax,0x1090(%rsp)
  b50f10:	mov    0xfd8(%rsp),%rax
  b50f18:	addss  %xmm15,%xmm0
  b50f1d:	movaps %xmm8,%xmm15
  b50f21:	mov    %rax,0x1098(%rsp)
  b50f29:	mov    0xfe0(%rsp),%rax
  b50f31:	mulss  %xmm12,%xmm15
  b50f36:	addss  %xmm15,%xmm0
  b50f3b:	movaps %xmm7,%xmm15
  b50f3f:	mulss  %xmm11,%xmm15
  b50f44:	addss  %xmm15,%xmm0
  b50f49:	movaps %xmm5,%xmm15
  b50f4d:	mulss  %xmm13,%xmm15
  b50f52:	movss  %xmm0,0xff0(%rsp)
  b50f5b:	movaps %xmm6,%xmm0
  b50f5e:	mulss  %xmm14,%xmm0
  b50f63:	addss  %xmm15,%xmm0
  b50f68:	movaps %xmm4,%xmm15
  b50f6c:	mulss  %xmm12,%xmm15
  b50f71:	addss  %xmm15,%xmm0
  b50f76:	movaps %xmm3,%xmm15
  b50f7a:	mulss  %xmm11,%xmm15
  b50f7f:	addss  %xmm15,%xmm0
  b50f84:	movaps %xmm1,%xmm15
  b50f88:	mulss  %xmm13,%xmm15
  b50f8d:	mulss  0x106c(%rsp),%xmm13
  b50f97:	movss  %xmm0,0xff4(%rsp)
  b50fa0:	movaps %xmm2,%xmm0
  b50fa3:	mulss  %xmm14,%xmm0
  b50fa8:	mulss  0x105c(%rsp),%xmm14
  b50fb2:	addss  %xmm15,%xmm0
  b50fb7:	movss  0x1078(%rsp),%xmm15
  b50fc1:	mulss  %xmm12,%xmm15
  b50fc6:	mulss  0x107c(%rsp),%xmm12
  b50fd0:	addss  %xmm13,%xmm14
  b50fd5:	movss  0x10c0(%rsp),%xmm13
  b50fdf:	mulss  %xmm13,%xmm2
  b50fe4:	addss  %xmm15,%xmm0
  b50fe9:	movss  0x1088(%rsp),%xmm15
  b50ff3:	mulss  %xmm11,%xmm15
  b50ff8:	mulss  0x108c(%rsp),%xmm11
  b51002:	addss  %xmm12,%xmm14
  b51007:	movss  0x10c4(%rsp),%xmm12
  b51011:	mulss  %xmm12,%xmm1
  b51016:	mulss  %xmm12,%xmm9
  b5101b:	addss  %xmm15,%xmm0
  b51020:	mulss  %xmm12,%xmm5
  b51025:	mulss  %xmm13,%xmm10
  b5102a:	mulss  0x106c(%rsp),%xmm12
  b51034:	addss  %xmm11,%xmm14
  b51039:	mulss  %xmm13,%xmm6
  b5103e:	movss  0x10c8(%rsp),%xmm11
  b51048:	mulss  0x105c(%rsp),%xmm13
  b51052:	addss  %xmm1,%xmm2
  b51056:	movss  %xmm0,0xff8(%rsp)
  b5105f:	movss  0x1078(%rsp),%xmm1
  b51068:	mulss  %xmm11,%xmm8
  b5106d:	mulss  %xmm11,%xmm1
  b51072:	addss  %xmm9,%xmm10
  b51077:	movss  %xmm14,0xffc(%rsp)
  b51081:	mulss  %xmm11,%xmm4
  b51086:	addss  %xmm5,%xmm6
  b5108a:	mulss  0x107c(%rsp),%xmm11
  b51094:	movss  0x10cc(%rsp),%xmm0
  b5109d:	addss  %xmm12,%xmm13
  b510a2:	mulss  %xmm0,%xmm7
  b510a6:	addss  %xmm1,%xmm2
  b510aa:	movss  0x1088(%rsp),%xmm1
  b510b3:	mulss  %xmm0,%xmm3
  b510b7:	addss  %xmm8,%xmm10
  b510bc:	mulss  %xmm0,%xmm1
  b510c0:	addss  %xmm4,%xmm6
  b510c4:	mulss  0x108c(%rsp),%xmm0
  b510cd:	addss  %xmm11,%xmm13
  b510d2:	addss  %xmm7,%xmm10
  b510d7:	addss  %xmm3,%xmm6
  b510db:	addss  %xmm1,%xmm2
  b510df:	addss  %xmm0,%xmm13
  b510e4:	movss  %xmm10,0x1000(%rsp)
  b510ee:	movss  %xmm6,0x1004(%rsp)
  b510f7:	movss  %xmm2,0x1008(%rsp)
  b51100:	movss  %xmm13,0x100c(%rsp)
  b5110a:	mov    %rax,0x10a0(%rsp)
  b51112:	mov    0xfe8(%rsp),%rax
  b5111a:	mov    %rax,0x10a8(%rsp)
  b51122:	mov    0xff0(%rsp),%rax
  b5112a:	mov    %rax,0x10b0(%rsp)
  b51132:	mov    0xff8(%rsp),%rax
  b5113a:	mov    %rax,0x10b8(%rsp)
  b51142:	mov    0x1000(%rsp),%rax
  b5114a:	mov    %rax,0x10c0(%rsp)
  b51152:	mov    0x1008(%rsp),%rax
  b5115a:	mov    %rax,0x10c8(%rsp)
  b51162:	mov    0x50(%rbx),%rax
  b51166:	mov    0x208(%rax),%rdi
  b5116d:	mov    (%rdi),%rax
  b51170:	call   *0x118(%rax)
  b51176:	jmp    b4fd94 <_ZN14CInventoryMenu6updateEf+0x3c4>
  b5117b:	nopl   0x0(%rax,%rax,1)
  b51180:	mov    $0xf,%esi
  b51185:	mov    %r14,%rdi
  b51188:	movq   $0x20,0xc68(%rsp)
  b51194:	movq   $0x0,0xc70(%rsp)
  b511a0:	movq   $0x0,0xc80(%rsp)
  b511ac:	movq   $0x0,0xc78(%rsp)
  b511b8:	movq   $0x0,0xd08(%rsp)
  b511c4:	movq   $0x0,0xc60(%rsp)
  b511d0:	movl   $0x0,0xc88(%rsp)
  b511db:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b511e0:	cmpq   $0x20,0xc68(%rsp)
  b511e9:	lea    0x28(%r14),%rdx
  b511ed:	jbe    b511f7 <_ZN14CInventoryMenu6updateEf+0x1827>
  b511ef:	mov    0xd08(%rsp),%rdx
  b511f7:	mov    $0xfef75c,%eax
  b511fc:	nopl   0x0(%rax)
  b51200:	movzbl (%rax),%ecx
  b51203:	add    $0x1,%rax
  b51207:	mov    %ecx,(%rdx)
  b51209:	add    $0x4,%rdx
  b5120d:	cmp    $0xfef76b,%rax
  b51213:	jne    b51200 <_ZN14CInventoryMenu6updateEf+0x1830>
  b51215:	cmpq   $0x20,0xc68(%rsp)
  b5121e:	movq   $0xf,0xc60(%rsp)
  b5122a:	mov    0x60(%rsp),%rax
  b5122f:	jbe    b5123d <_ZN14CInventoryMenu6updateEf+0x186d>
  b51231:	mov    0xd08(%rsp),%rax
  b51239:	add    $0x3c,%rax
  b5123d:	movl   $0x0,(%rax)
  b51243:	mov    0x9120(%rbx),%rsi
  b5124a:	lea    0xbb0(%rsp),%rdi
  b51252:	mov    %r14,%rdx
  b51255:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5125a:	mov    0x50(%rsp),%rsi
  b5125f:	lea    0xbb0(%rsp),%rdi
  b51267:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b5126c:	lea    0xbb0(%rsp),%rdi
  b51274:	mov    %al,0x9f(%rsp)
  b5127b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51280:	mov    %r14,%rdi
  b51283:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51288:	cmpb   $0x0,0x9f(%rsp)
  b51290:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b51296:	lea    0xb00(%rsp),%rdi
  b5129e:	mov    $0xfef75c,%esi
  b512a3:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b512a8:	mov    0x9120(%rbx),%rdi
  b512af:	mov    0x50(%rsp),%rdx
  b512b4:	lea    0xb00(%rsp),%rsi
  b512bc:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b512c1:	lea    0xb00(%rsp),%rdi
  b512c9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b512ce:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b512d3:	nopl   0x0(%rax,%rax,1)
  b512d8:	mov    0x50(%rbx),%rdi
  b512dc:	call   80e910 <_ZN10CCharacter21performingAttackLooseEv>
  b512e1:	test   %al,%al
  b512e3:	jne    b4fd5d <_ZN14CInventoryMenu6updateEf+0x38d>
  b512e9:	mov    0x50(%rbx),%rdi
  b512ed:	call   80e9b0 <_ZN10CCharacter20performingSkillLooseEv>
  b512f2:	test   %al,%al
  b512f4:	jne    b4fd5d <_ZN14CInventoryMenu6updateEf+0x38d>
  b512fa:	xorps  %xmm1,%xmm1
  b512fd:	mov    0x9188(%rbx),%rdi
  b51304:	xor    %ecx,%ecx
  b51306:	xor    %edx,%edx
  b51308:	mov    $0x12,%esi
  b5130d:	movaps %xmm1,%xmm0
  b51310:	call   a698a0 <_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb>
  b51315:	mov    0x50(%rbx),%rdi
  b51319:	call   8133f0 <_ZN10CCharacter24toggleSecondaryWeaponSetEv>
  b5131e:	mov    (%rbx),%rax
  b51321:	mov    %rbx,%rdi
  b51324:	call   *0x48(%rax)
  b51327:	jmp    b4fd5d <_ZN14CInventoryMenu6updateEf+0x38d>
  b5132c:	lea    0x11a0(%rsp),%rbp
  b51334:	lea    0x123c(%rsp),%rdx
  b5133c:	mov    $0xfe6008,%esi
  b51341:	xor    %r13d,%r13d
  b51344:	xor    %r14d,%r14d
  b51347:	mov    %rbp,%rdi
  b5134a:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5134f:	mov    0x9170(%rbx),%rdi
  b51356:	mov    %rbp,%rsi
  b51359:	mov    $0x1,%r13d
  b5135f:	call   8a7860 <_ZNK13CGenericModel16animationPlayingERKSs>
  b51364:	xor    %r12d,%r12d
  b51367:	test   %al,%al
  b51369:	je     b5177d <_ZN14CInventoryMenu6updateEf+0x1dad>
  b5136f:	mov    %rbp,%rdi
  b51372:	call   556288 <_ZNSsD1Ev@plt>
  b51377:	test   %r12b,%r12b
  b5137a:	je     b5021c <_ZN14CInventoryMenu6updateEf+0x84c>
  b51380:	mov    0x9170(%rbx),%rdi
  b51387:	xor    %esi,%esi
  b51389:	mov    (%rdi),%rax
  b5138c:	call   *0x50(%rax)
  b5138f:	mov    0x9150(%rbx),%rdi
  b51396:	movb   $0x1,0x61(%rbx)
  b5139a:	mov    $0x3,%esi
  b5139f:	mov    (%rdi),%rax
  b513a2:	call   *0x60(%rax)
  b513a5:	mov    0x20(%rbx),%rsi
  b513a9:	mov    0x18(%rbx),%rdi
  b513ad:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b513b2:	movq   $0x0,0x9158(%rbx)
  b513bd:	jmp    b5021c <_ZN14CInventoryMenu6updateEf+0x84c>
  b513c2:	nopw   0x0(%rax,%rax,1)
  b513c8:	mov    0x9110(%rbx),%rdi
  b513cf:	xor    %esi,%esi
  b513d1:	call   5561d8 <_ZNK5CEGUI6Window9isVisibleEb@plt>
  b513d6:	test   %al,%al
  b513d8:	jne    b51736 <_ZN14CInventoryMenu6updateEf+0x1d66>
  b513de:	movss  0x91ac(%rbx),%xmm0
  b513e6:	ucomiss 0x453423(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b513ed:	jbe    b51594 <_ZN14CInventoryMenu6updateEf+0x1bc4>
  b513f3:	lea    0x9a0(%rsp),%rdi
  b513fb:	mov    $0xfef75c,%esi
  b51400:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b51405:	mov    0x9128(%rbx),%rsi
  b5140c:	lea    0x9a0(%rsp),%rdx
  b51414:	lea    0x8f0(%rsp),%rdi
  b5141c:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b51421:	mov    0x90(%rsp),%rsi
  b51429:	lea    0x8f0(%rsp),%rdi
  b51431:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b51436:	lea    0x8f0(%rsp),%rdi
  b5143e:	mov    %al,0x9f(%rsp)
  b51445:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5144a:	lea    0x9a0(%rsp),%rdi
  b51452:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51457:	cmpb   $0x0,0x9f(%rsp)
  b5145f:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b51465:	lea    0x840(%rsp),%rdi
  b5146d:	mov    $0xfef75c,%esi
  b51472:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b51477:	mov    0x9128(%rbx),%rdi
  b5147e:	mov    0x90(%rsp),%rdx
  b51486:	lea    0x840(%rsp),%rsi
  b5148e:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b51493:	lea    0x840(%rsp),%rdi
  b5149b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b514a0:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b514a5:	nopl   (%rax)
  b514a8:	movb   $0x1,0x91a8(%rbx)
  b514af:	mov    $0xf,%esi
  b514b4:	mov    %r15,%rdi
  b514b7:	movq   $0x20,0xf28(%rsp)
  b514c3:	movq   $0x0,0xf30(%rsp)
  b514cf:	movq   $0x0,0xf40(%rsp)
  b514db:	movq   $0x0,0xf38(%rsp)
  b514e7:	movq   $0x0,0xfc8(%rsp)
  b514f3:	movq   $0x0,0xf20(%rsp)
  b514ff:	movl   $0x0,0xf48(%rsp)
  b5150a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5150f:	cmpq   $0x20,0xf28(%rsp)
  b51518:	lea    0x28(%r15),%rdx
  b5151c:	jbe    b51526 <_ZN14CInventoryMenu6updateEf+0x1b56>
  b5151e:	mov    0xfc8(%rsp),%rdx
  b51526:	mov    $0xfef75c,%eax
  b5152b:	nopl   0x0(%rax,%rax,1)
  b51530:	movzbl (%rax),%ecx
  b51533:	add    $0x1,%rax
  b51537:	mov    %ecx,(%rdx)
  b51539:	add    $0x4,%rdx
  b5153d:	cmp    $0xfef76b,%rax
  b51543:	jne    b51530 <_ZN14CInventoryMenu6updateEf+0x1b60>
  b51545:	cmpq   $0x20,0xf28(%rsp)
  b5154e:	movq   $0xf,0xf20(%rsp)
  b5155a:	mov    0x70(%rsp),%rax
  b5155f:	jbe    b5156d <_ZN14CInventoryMenu6updateEf+0x1b9d>
  b51561:	mov    0xfc8(%rsp),%rax
  b51569:	add    $0x3c,%rax
  b5156d:	movl   $0x0,(%rax)
  b51573:	mov    0x9120(%rbx),%rdi
  b5157a:	mov    %r15,%rsi
  b5157d:	mov    0x50(%rsp),%rdx
  b51582:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b51587:	mov    %r15,%rdi
  b5158a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5158f:	jmp    b4fbae <_ZN14CInventoryMenu6updateEf+0x1de>
  b51594:	lea    0x790(%rsp),%rdi
  b5159c:	mov    $0xfef75c,%esi
  b515a1:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b515a6:	mov    0x9128(%rbx),%rsi
  b515ad:	lea    0x790(%rsp),%rdx
  b515b5:	lea    0x6e0(%rsp),%rdi
  b515bd:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b515c2:	mov    0x80(%rsp),%rsi
  b515ca:	lea    0x6e0(%rsp),%rdi
  b515d2:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b515d7:	lea    0x6e0(%rsp),%rdi
  b515df:	mov    %al,0x9f(%rsp)
  b515e6:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b515eb:	lea    0x790(%rsp),%rdi
  b515f3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b515f8:	cmpb   $0x0,0x9f(%rsp)
  b51600:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b51606:	lea    0x630(%rsp),%rdi
  b5160e:	mov    $0xfef75c,%esi
  b51613:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b51618:	mov    0x9128(%rbx),%rdi
  b5161f:	mov    0x80(%rsp),%rdx
  b51627:	lea    0x630(%rsp),%rsi
  b5162f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b51634:	lea    0x630(%rsp),%rdi
  b5163c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51641:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b51646:	lea    0x2c0(%rsp),%rdi
  b5164e:	mov    $0xfef75c,%esi
  b51653:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b51658:	mov    0x9130(%rbx),%rsi
  b5165f:	lea    0x2c0(%rsp),%rdx
  b51667:	lea    0x210(%rsp),%rdi
  b5166f:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b51674:	mov    0x78(%rsp),%rsi
  b51679:	lea    0x210(%rsp),%rdi
  b51681:	call   556208 <_ZN5CEGUIneERKNS_6StringES2_@plt>
  b51686:	lea    0x210(%rsp),%rdi
  b5168e:	mov    %al,0x9f(%rsp)
  b51695:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5169a:	lea    0x2c0(%rsp),%rdi
  b516a2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b516a7:	cmpb   $0x0,0x9f(%rsp)
  b516af:	je     b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b516b5:	lea    0x160(%rsp),%rdi
  b516bd:	mov    $0xfef75c,%esi
  b516c2:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b516c7:	mov    0x9130(%rbx),%rdi
  b516ce:	mov    0x78(%rsp),%rdx
  b516d3:	lea    0x160(%rsp),%rsi
  b516db:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b516e0:	lea    0x160(%rsp),%rdi
  b516e8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b516ed:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b516f2:	lea    0x580(%rsp),%rdi
  b516fa:	mov    $0xfef75c,%esi
  b516ff:	movb   $0x1,0x91aa(%rbx)
  b51706:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b5170b:	mov    0x9130(%rbx),%rdi
  b51712:	mov    0x78(%rsp),%rdx
  b51717:	lea    0x580(%rsp),%rsi
  b5171f:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b51724:	lea    0x580(%rsp),%rdi
  b5172c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51731:	jmp    b4fba8 <_ZN14CInventoryMenu6updateEf+0x1d8>
  b51736:	lea    0xa50(%rsp),%rdi
  b5173e:	mov    $0xfef75c,%esi
  b51743:	movb   $0x1,0x91a9(%rbx)
  b5174a:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b5174f:	mov    0x9128(%rbx),%rdi
  b51756:	mov    0x80(%rsp),%rdx
  b5175e:	lea    0xa50(%rsp),%rsi
  b51766:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5176b:	lea    0xa50(%rsp),%rdi
  b51773:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51778:	jmp    b4fbae <_ZN14CInventoryMenu6updateEf+0x1de>
  b5177d:	lea    0x1190(%rsp),%r15
  b51785:	lea    0x123b(%rsp),%rdx
  b5178d:	mov    $0xfe6008,%esi
  b51792:	mov    %r15,%rdi
  b51795:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5179a:	mov    0x9170(%rbx),%rdi
  b517a1:	mov    %r15,%rsi
  b517a4:	mov    $0x1,%r14d
  b517aa:	call   8a5530 <_ZNK13CGenericModel15animationQueuedERKSs>
  b517af:	test   %al,%al
  b517b1:	mov    %r15,%rdi
  b517b4:	sete   %r12b
  b517b8:	call   556288 <_ZNSsD1Ev@plt>
  b517bd:	jmp    b5136f <_ZN14CInventoryMenu6updateEf+0x199f>
  b517c2:	mov    $0x5541c8,%eax
  b517c7:	test   %rax,%rax
  b517ca:	je     b5180e <_ZN14CInventoryMenu6updateEf+0x1e3e>
  b517cc:	or     $0xffffffff,%eax
  b517cf:	lock xadd %eax,0x10(%rdi)
  b517d4:	test   %eax,%eax
  b517d6:	jg     b4ffbd <_ZN14CInventoryMenu6updateEf+0x5ed>
  b517dc:	lea    0x1233(%rsp),%rsi
  b517e4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b517e9:	jmp    b4ffbd <_ZN14CInventoryMenu6updateEf+0x5ed>
  b517ee:	mov    %r12,%rdi
  b517f1:	mov    %rax,%rbx
  b517f4:	call   556288 <_ZNSsD1Ev@plt>
  b517f9:	mov    %rbx,%rdi
  b517fc:	call   554498 <_Unwind_Resume@plt>
  b51801:	mov    %rax,%rbx
  b51804:	mov    %rbp,%rdi
  b51807:	call   556288 <_ZNSsD1Ev@plt>
  b5180c:	jmp    b517f9 <_ZN14CInventoryMenu6updateEf+0x1e29>
  b5180e:	mov    0x10(%rdi),%eax
  b51811:	lea    -0x1(%rax),%edx
  b51814:	mov    %edx,0x10(%rdi)
  b51817:	jmp    b517d4 <_ZN14CInventoryMenu6updateEf+0x1e04>
  b51819:	lea    0x210(%rsp),%rdi
  b51821:	mov    %rax,%rbx
  b51824:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51829:	lea    0x2c0(%rsp),%rdi
  b51831:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51836:	mov    %rbx,%rdi
  b51839:	call   554498 <_Unwind_Resume@plt>
  b5183e:	mov    %rax,%rbx
  b51841:	jmp    b51829 <_ZN14CInventoryMenu6updateEf+0x1e59>
  b51843:	lea    0x160(%rsp),%rdi
  b5184b:	mov    %rax,%rbx
  b5184e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51853:	mov    %rbx,%rdi
  b51856:	call   554498 <_Unwind_Resume@plt>
  b5185b:	lea    0x580(%rsp),%rdi
  b51863:	mov    %rax,%rbx
  b51866:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5186b:	mov    %rbx,%rdi
  b5186e:	call   554498 <_Unwind_Resume@plt>
  b51873:	mov    %rax,%rbx
  b51876:	jmp    b517f9 <_ZN14CInventoryMenu6updateEf+0x1e29>
  b51878:	jmp    b51873 <_ZN14CInventoryMenu6updateEf+0x1ea3>
  b5187a:	mov    $0x5541c8,%eax
  b5187f:	test   %rax,%rax
  b51882:	je     b518ab <_ZN14CInventoryMenu6updateEf+0x1edb>
  b51884:	or     $0xffffffff,%eax
  b51887:	lock xadd %eax,0x10(%rdi)
  b5188c:	test   %eax,%eax
  b5188e:	jg     b4fe1d <_ZN14CInventoryMenu6updateEf+0x44d>
  b51894:	lea    0x1234(%rsp),%rsi
  b5189c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b518a1:	jmp    b4fe1d <_ZN14CInventoryMenu6updateEf+0x44d>
  b518a6:	jmp    b517ee <_ZN14CInventoryMenu6updateEf+0x1e1e>
  b518ab:	mov    0x10(%rdi),%eax
  b518ae:	lea    -0x1(%rax),%edx
  b518b1:	mov    %edx,0x10(%rdi)
  b518b4:	jmp    b5188c <_ZN14CInventoryMenu6updateEf+0x1ebc>
  b518b6:	jmp    b51873 <_ZN14CInventoryMenu6updateEf+0x1ea3>
  b518b8:	mov    %rax,%rbx
  b518bb:	mov    %r12,%rdi
  b518be:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b518c3:	mov    %rbx,%rdi
  b518c6:	call   554498 <_Unwind_Resume@plt>
  b518cb:	mov    %rbp,%rdi
  b518ce:	mov    %rax,%rbx
  b518d1:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b518d6:	jmp    b518bb <_ZN14CInventoryMenu6updateEf+0x1eeb>
  b518d8:	jmp    b518cb <_ZN14CInventoryMenu6updateEf+0x1efb>
  b518da:	mov    %rax,%rbx
  b518dd:	mov    %r13,%rdi
  b518e0:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b518e5:	mov    %r15,%rdi
  b518e8:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b518ed:	mov    %rbx,%rdi
  b518f0:	call   554498 <_Unwind_Resume@plt>
  b518f5:	mov    %rax,%rbx
  b518f8:	jmp    b518e5 <_ZN14CInventoryMenu6updateEf+0x1f15>
  b518fa:	mov    $0x5541c8,%eax
  b518ff:	test   %rax,%rax
  b51902:	je     b51939 <_ZN14CInventoryMenu6updateEf+0x1f69>
  b51904:	or     $0xffffffff,%eax
  b51907:	lock xadd %eax,0x10(%rdi)
  b5190c:	test   %eax,%eax
  b5190e:	jg     b4fc9f <_ZN14CInventoryMenu6updateEf+0x2cf>
  b51914:	lea    0x1238(%rsp),%rsi
  b5191c:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b51921:	jmp    b4fc9f <_ZN14CInventoryMenu6updateEf+0x2cf>
  b51926:	mov    %rax,%rbx
  b51929:	mov    %rbp,%rdi
  b5192c:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b51931:	mov    %rbx,%rdi
  b51934:	call   554498 <_Unwind_Resume@plt>
  b51939:	mov    0x10(%rdi),%eax
  b5193c:	lea    -0x1(%rax),%edx
  b5193f:	mov    %edx,0x10(%rdi)
  b51942:	jmp    b5190c <_ZN14CInventoryMenu6updateEf+0x1f3c>
  b51944:	mov    $0x5541c8,%eax
  b51949:	test   %rax,%rax
  b5194c:	je     b5197e <_ZN14CInventoryMenu6updateEf+0x1fae>
  b5194e:	or     $0xffffffff,%eax
  b51951:	lock xadd %eax,0x10(%rdi)
  b51956:	test   %eax,%eax
  b51958:	jg     b4fd18 <_ZN14CInventoryMenu6updateEf+0x348>
  b5195e:	lea    0x1236(%rsp),%rsi
  b51966:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5196b:	jmp    b4fd18 <_ZN14CInventoryMenu6updateEf+0x348>
  b51970:	mov    0x10(%rdi),%eax
  b51973:	lea    -0x1(%rax),%edx
  b51976:	mov    %edx,0x10(%rdi)
  b51979:	jmp    b502e9 <_ZN14CInventoryMenu6updateEf+0x919>
  b5197e:	mov    0x10(%rdi),%eax
  b51981:	lea    -0x1(%rax),%edx
  b51984:	mov    %edx,0x10(%rdi)
  b51987:	jmp    b51956 <_ZN14CInventoryMenu6updateEf+0x1f86>
  b51989:	mov    $0x5541c8,%eax
  b5198e:	test   %rax,%rax
  b51991:	je     b519c5 <_ZN14CInventoryMenu6updateEf+0x1ff5>
  b51993:	or     $0xffffffff,%eax
  b51996:	lock xadd %eax,0x10(%rdi)
  b5199b:	test   %eax,%eax
  b5199d:	jg     b4fd03 <_ZN14CInventoryMenu6updateEf+0x333>
  b519a3:	lea    0x1237(%rsp),%rsi
  b519ab:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b519b0:	jmp    b4fd03 <_ZN14CInventoryMenu6updateEf+0x333>
  b519b5:	mov    %r14,%rdi
  b519b8:	mov    %rax,%rbx
  b519bb:	call   556288 <_ZNSsD1Ev@plt>
  b519c0:	jmp    b518dd <_ZN14CInventoryMenu6updateEf+0x1f0d>
  b519c5:	mov    0x10(%rdi),%eax
  b519c8:	lea    -0x1(%rax),%edx
  b519cb:	mov    %edx,0x10(%rdi)
  b519ce:	jmp    b5199b <_ZN14CInventoryMenu6updateEf+0x1fcb>
  b519d0:	mov    $0x5541c8,%eax
  b519d5:	test   %rax,%rax
  b519d8:	je     b51a01 <_ZN14CInventoryMenu6updateEf+0x2031>
  b519da:	or     $0xffffffff,%eax
  b519dd:	lock xadd %eax,0x10(%rdi)
  b519e2:	test   %eax,%eax
  b519e4:	jg     b4fd7a <_ZN14CInventoryMenu6updateEf+0x3aa>
  b519ea:	lea    0x1235(%rsp),%rsi
  b519f2:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b519f7:	jmp    b4fd7a <_ZN14CInventoryMenu6updateEf+0x3aa>
  b519fc:	jmp    b51873 <_ZN14CInventoryMenu6updateEf+0x1ea3>
  b51a01:	mov    0x10(%rdi),%eax
  b51a04:	lea    -0x1(%rax),%edx
  b51a07:	mov    %edx,0x10(%rdi)
  b51a0a:	jmp    b519e2 <_ZN14CInventoryMenu6updateEf+0x2012>
  b51a0c:	mov    %rbp,%rdi
  b51a0f:	mov    %rax,%rbx
  b51a12:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51a17:	jmp    b518e5 <_ZN14CInventoryMenu6updateEf+0x1f15>
  b51a1c:	mov    $0x5541c8,%eax
  b51a21:	test   %rax,%rax
  b51a24:	je     b51a9d <_ZN14CInventoryMenu6updateEf+0x20cd>
  b51a26:	or     $0xffffffff,%eax
  b51a29:	lock xadd %eax,0x10(%rdi)
  b51a2e:	test   %eax,%eax
  b51a30:	jg     b4fc8a <_ZN14CInventoryMenu6updateEf+0x2ba>
  b51a36:	lea    0x1239(%rsp),%rsi
  b51a3e:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b51a43:	jmp    b4fc8a <_ZN14CInventoryMenu6updateEf+0x2ba>
  b51a48:	mov    %rax,%rbx
  b51a4b:	lea    0x790(%rsp),%rdi
  b51a53:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51a58:	mov    %rbx,%rdi
  b51a5b:	call   554498 <_Unwind_Resume@plt>
  b51a60:	lea    0x6e0(%rsp),%rdi
  b51a68:	mov    %rax,%rbx
  b51a6b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51a70:	jmp    b51a4b <_ZN14CInventoryMenu6updateEf+0x207b>
  b51a72:	lea    0x840(%rsp),%rdi
  b51a7a:	mov    %rax,%rbx
  b51a7d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51a82:	mov    %rbx,%rdi
  b51a85:	call   554498 <_Unwind_Resume@plt>
  b51a8a:	mov    %rax,%rbx
  b51a8d:	mov    %r15,%rdi
  b51a90:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51a95:	mov    %rbx,%rdi
  b51a98:	call   554498 <_Unwind_Resume@plt>
  b51a9d:	mov    0x10(%rdi),%eax
  b51aa0:	lea    -0x1(%rax),%edx
  b51aa3:	mov    %edx,0x10(%rdi)
  b51aa6:	jmp    b51a2e <_ZN14CInventoryMenu6updateEf+0x205e>
  b51aa8:	lea    0xdc0(%rsp),%rdi
  b51ab0:	mov    %rax,%rbx
  b51ab3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51ab8:	mov    %r13,%rdi
  b51abb:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51ac0:	mov    %rbx,%rdi
  b51ac3:	call   554498 <_Unwind_Resume@plt>
  b51ac8:	lea    0x370(%rsp),%rdi
  b51ad0:	mov    %rax,%rbx
  b51ad3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51ad8:	mov    %rbx,%rdi
  b51adb:	call   554498 <_Unwind_Resume@plt>
  b51ae0:	lea    0x420(%rsp),%rdi
  b51ae8:	mov    %rax,%rbx
  b51aeb:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51af0:	lea    0x4d0(%rsp),%rdi
  b51af8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51afd:	mov    %rbx,%rdi
  b51b00:	call   554498 <_Unwind_Resume@plt>
  b51b05:	mov    %rax,%rbx
  b51b08:	jmp    b51af0 <_ZN14CInventoryMenu6updateEf+0x2120>
  b51b0a:	lea    0xbb0(%rsp),%rdi
  b51b12:	mov    %rax,%rbx
  b51b15:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b1a:	mov    %r14,%rdi
  b51b1d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b22:	mov    %rbx,%rdi
  b51b25:	call   554498 <_Unwind_Resume@plt>
  b51b2a:	mov    %rax,%rbx
  b51b2d:	jmp    b51b1a <_ZN14CInventoryMenu6updateEf+0x214a>
  b51b2f:	mov    %rax,%rbx
  b51b32:	jmp    b51ab8 <_ZN14CInventoryMenu6updateEf+0x20e8>
  b51b34:	lea    0xd10(%rsp),%rdi
  b51b3c:	mov    %rax,%rbx
  b51b3f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b44:	mov    %rbx,%rdi
  b51b47:	call   554498 <_Unwind_Resume@plt>
  b51b4c:	jmp    b518f5 <_ZN14CInventoryMenu6updateEf+0x1f25>
  b51b51:	lea    0x8f0(%rsp),%rdi
  b51b59:	mov    %rax,%rbx
  b51b5c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b61:	lea    0x9a0(%rsp),%rdi
  b51b69:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b6e:	mov    %rbx,%rdi
  b51b71:	call   554498 <_Unwind_Resume@plt>
  b51b76:	mov    %rax,%rbx
  b51b79:	jmp    b51b61 <_ZN14CInventoryMenu6updateEf+0x2191>
  b51b7b:	lea    0x630(%rsp),%rdi
  b51b83:	mov    %rax,%rbx
  b51b86:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51b8b:	mov    %rbx,%rdi
  b51b8e:	call   554498 <_Unwind_Resume@plt>
  b51b93:	test   %r14b,%r14b
  b51b96:	mov    %rax,%rbx
  b51b99:	je     b51ba8 <_ZN14CInventoryMenu6updateEf+0x21d8>
  b51b9b:	lea    0x1190(%rsp),%rdi
  b51ba3:	call   556288 <_ZNSsD1Ev@plt>
  b51ba8:	test   %r13b,%r13b
  b51bab:	je     b517f9 <_ZN14CInventoryMenu6updateEf+0x1e29>
  b51bb1:	jmp    b51804 <_ZN14CInventoryMenu6updateEf+0x1e34>
  b51bb6:	lea    0xb00(%rsp),%rdi
  b51bbe:	mov    %rax,%rbx
  b51bc1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51bc6:	mov    %rbx,%rdi
  b51bc9:	call   554498 <_Unwind_Resume@plt>
  b51bce:	jmp    b51873 <_ZN14CInventoryMenu6updateEf+0x1ea3>
  b51bd3:	lea    0xa50(%rsp),%rdi
  b51bdb:	mov    %rax,%rbx
  b51bde:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b51be3:	mov    %rbx,%rdi
  b51be6:	call   554498 <_Unwind_Resume@plt>
  b51beb:	nop
  b51bec:	nopl   0x0(%rax)
