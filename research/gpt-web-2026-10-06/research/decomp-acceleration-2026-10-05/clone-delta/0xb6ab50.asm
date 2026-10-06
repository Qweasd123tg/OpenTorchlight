
../game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000b6ab50 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii>:
  b6ab50:	push   %r15
  b6ab52:	movslq %edx,%rdx
  b6ab55:	push   %r14
  b6ab57:	push   %r13
  b6ab59:	mov    %rsi,%r13
  b6ab5c:	push   %r12
  b6ab5e:	mov    %ecx,%r12d
  b6ab61:	push   %rbp
  b6ab62:	mov    %rdi,%rbp
  b6ab65:	push   %rbx
  b6ab66:	mov    %rdx,%rbx
  b6ab69:	add    $0x4de,%rbx
  b6ab70:	sub    $0x1638,%rsp
  b6ab77:	mov    %rdx,0x40(%rsp)
  b6ab7c:	mov    0x8(%rdi,%rbx,8),%rdi
  b6ab81:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b6ab86:	xorps  %xmm0,%xmm0
  b6ab89:	movss  0x439c7f(%rip),%xmm3        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b6ab91:	movaps %xmm3,%xmm1
  b6ab94:	movss  0x43db58(%rip),%xmm2        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b6ab9c:	movss  %xmm0,0x2c(%rsp)
  b6aba2:	mulss  0x8(%rax),%xmm0
  b6aba7:	movss  %xmm0,0x38(%rsp)
  b6abad:	movss  0x2c(%rsp),%xmm0
  b6abb3:	cmpltss 0x38(%rsp),%xmm0
  b6abba:	andps  %xmm0,%xmm1
  b6abbd:	andnps %xmm2,%xmm0
  b6abc0:	orps   %xmm1,%xmm0
  b6abc3:	movss  %xmm0,0x30(%rsp)
  b6abc9:	movss  0xc(%rax),%xmm0
  b6abce:	movss  %xmm0,0x4c(%rsp)
  b6abd4:	mov    0x8(%rbp,%rbx,8),%rdi
  b6abd9:	movss  %xmm2,(%rsp)
  b6abde:	movss  %xmm3,0x10(%rsp)
  b6abe4:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b6abe9:	movss  0x2c(%rsp),%xmm1
  b6abef:	mulss  (%rax),%xmm1
  b6abf3:	movss  0x2c(%rsp),%xmm0
  b6abf9:	movss  0x10(%rsp),%xmm3
  b6abff:	mov    0x2c8(%r13),%rbx
  b6ac06:	movss  (%rsp),%xmm2
  b6ac0b:	test   %rbx,%rbx
  b6ac0e:	cmpltss %xmm1,%xmm0
  b6ac13:	andps  %xmm0,%xmm3
  b6ac16:	andnps %xmm2,%xmm0
  b6ac19:	orps   %xmm3,%xmm0
  b6ac1c:	addss  %xmm1,%xmm0
  b6ac20:	cvttss2si %xmm0,%edx
  b6ac24:	cvtsi2ss %edx,%xmm0
  b6ac28:	addss  0x4(%rax),%xmm0
  b6ac2d:	cvttss2si %xmm0,%r15
  b6ac32:	je     b6c094 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1544>
  b6ac38:	mov    0xb0(%rbx),%rdi
  b6ac3f:	test   %rdi,%rdi
  b6ac42:	je     b6ac4c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xfc>
  b6ac44:	mov    %rbx,%rsi
  b6ac47:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b6ac4c:	mov    0x40(%rsp),%rax
  b6ac51:	mov    %rbx,%rsi
  b6ac54:	mov    0x26f8(%rbp,%rax,8),%rdi
  b6ac5c:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b6ac61:	lea    0x1600(%rsp),%rsi
  b6ac69:	mov    %rbx,%rdi
  b6ac6c:	movl   $0x0,0x1604(%rsp)
  b6ac77:	movl   $0x0,0x1600(%rsp)
  b6ac82:	movl   $0x3f800000,0x160c(%rsp)
  b6ac8d:	movl   $0x0,0x1608(%rsp)
  b6ac98:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b6ac9d:	lea    0x15f0(%rsp),%rsi
  b6aca5:	mov    %rbx,%rdi
  b6aca8:	movl   $0x0,0x15f4(%rsp)
  b6acb3:	movl   $0x0,0x15f0(%rsp)
  b6acbe:	movl   $0x0,0x15fc(%rsp)
  b6acc9:	movl   $0x0,0x15f8(%rsp)
  b6acd4:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b6acd9:	mov    0x40(%rsp),%rax
  b6acde:	lea    0x15e0(%rsp),%r14
  b6ace6:	mov    %r14,%rdi
  b6ace9:	mov    0x26f8(%rbp,%rax,8),%rsi
  b6acf1:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b6acf6:	mov    %r14,%rsi
  b6acf9:	mov    %rbx,%rdi
  b6acfc:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b6ad01:	mov    %rbx,%rdi
  b6ad04:	movslq %r12d,%r12
  b6ad07:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b6ad0c:	lea    0xb0(%rbp,%r12,4),%rax
  b6ad14:	mov    %rax,0x1d8(%rbx)
  b6ad1b:	cmpb   $0x0,0x348(%r13)
  b6ad23:	je     b6b0c0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x570>
  b6ad29:	mov    0x3e0(%r13),%eax
  b6ad30:	test   %eax,%eax
  b6ad32:	je     b6b0c0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x570>
  b6ad38:	cmp    $0x1,%eax
  b6ad3b:	jbe    b6c145 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x15f5>
  b6ad41:	lea    0x14f0(%rsp),%r12
  b6ad49:	mov    $0xd,%esi
  b6ad4e:	movq   $0x20,0x14f8(%rsp)
  b6ad5a:	movq   $0x0,0x1500(%rsp)
  b6ad66:	movq   $0x0,0x1510(%rsp)
  b6ad72:	mov    %r12,%rdi
  b6ad75:	movq   $0x0,0x1508(%rsp)
  b6ad81:	movq   $0x0,0x1598(%rsp)
  b6ad8d:	movq   $0x0,0x14f0(%rsp)
  b6ad99:	movl   $0x0,0x1518(%rsp)
  b6ada4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6ada9:	cmpq   $0x20,0x14f8(%rsp)
  b6adb2:	lea    0x28(%r12),%rdx
  b6adb7:	ja     b6be38 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12e8>
  b6adbd:	mov    $0xfe60c3,%eax
  b6adc2:	nopw   0x0(%rax,%rax,1)
  b6adc8:	movzbl (%rax),%ecx
  b6adcb:	add    $0x1,%rax
  b6adcf:	mov    %ecx,(%rdx)
  b6add1:	add    $0x4,%rdx
  b6add5:	cmp    $0xfe60d0,%rax
  b6addb:	jne    b6adc8 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x278>
  b6addd:	cmpq   $0x20,0x14f8(%rsp)
  b6ade6:	movq   $0xd,0x14f0(%rsp)
  b6adf2:	lea    0x5c(%r12),%rax
  b6adf7:	jbe    b6ae05 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x2b5>
  b6adf9:	mov    0x1598(%rsp),%rax
  b6ae01:	add    $0x34,%rax
  b6ae05:	movl   $0x0,(%rax)
  b6ae0b:	mov    0x3440(%rbp),%rdi
  b6ae12:	mov    %r12,%rsi
  b6ae15:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6ae1a:	lea    0x1440(%rsp),%r14
  b6ae22:	mov    %rax,%rsi
  b6ae25:	mov    %r14,%rdi
  b6ae28:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6ae2d:	lea    0x1390(%rsp),%rbx
  b6ae35:	mov    $0x5,%esi
  b6ae3a:	movq   $0x20,0x1398(%rsp)
  b6ae46:	movq   $0x0,0x13a0(%rsp)
  b6ae52:	movq   $0x0,0x13b0(%rsp)
  b6ae5e:	mov    %rbx,%rdi
  b6ae61:	movq   $0x0,0x13a8(%rsp)
  b6ae6d:	movq   $0x0,0x1438(%rsp)
  b6ae79:	movq   $0x0,0x1390(%rsp)
  b6ae85:	movl   $0x0,0x13b8(%rsp)
  b6ae90:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6ae95:	cmpq   $0x20,0x1398(%rsp)
  b6ae9e:	lea    0x28(%rbx),%rdx
  b6aea2:	ja     b6be2b <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12db>
  b6aea8:	mov    $0xfd0c0d,%eax
  b6aead:	nopl   (%rax)
  b6aeb0:	movzbl (%rax),%ecx
  b6aeb3:	add    $0x1,%rax
  b6aeb7:	mov    %ecx,(%rdx)
  b6aeb9:	add    $0x4,%rdx
  b6aebd:	cmp    $0xfd0c12,%rax
  b6aec3:	jne    b6aeb0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x360>
  b6aec5:	cmpq   $0x20,0x1398(%rsp)
  b6aece:	movq   $0x5,0x1390(%rsp)
  b6aeda:	lea    0x3c(%rbx),%rax
  b6aede:	jbe    b6aeec <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x39c>
  b6aee0:	mov    0x1438(%rsp),%rax
  b6aee8:	add    $0x14,%rax
  b6aeec:	movl   $0x0,(%rax)
  b6aef2:	mov    0x40(%rsp),%rax
  b6aef7:	mov    %r14,%rdx
  b6aefa:	mov    %rbx,%rsi
  b6aefd:	mov    0x2ea8(%rbp,%rax,8),%rdi
  b6af05:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6af0a:	mov    %rbx,%rdi
  b6af0d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6af12:	mov    %r14,%rdi
  b6af15:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6af1a:	mov    %r12,%rdi
  b6af1d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6af22:	mov    0x40(%rsp),%rax
  b6af27:	mov    0x2ea8(%rbp,%rax,8),%rdi
  b6af2f:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b6af34:	cmpb   $0x0,0x348(%r13)
  b6af3c:	je     b6b241 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x6f1>
  b6af42:	lea    0xcb0(%rsp),%r12
  b6af4a:	xor    %esi,%esi
  b6af4c:	movq   $0x20,0xcb8(%rsp)
  b6af58:	movq   $0x0,0xcc0(%rsp)
  b6af64:	movq   $0x0,0xcd0(%rsp)
  b6af70:	mov    %r12,%rdi
  b6af73:	movq   $0x0,0xcc8(%rsp)
  b6af7f:	movq   $0x0,0xd58(%rsp)
  b6af8b:	movq   $0x0,0xcb0(%rsp)
  b6af97:	movl   $0x0,0xcd8(%rsp)
  b6afa2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6afa7:	cmpq   $0x20,0xcb8(%rsp)
  b6afb0:	movq   $0x0,0xcb0(%rsp)
  b6afbc:	lea    0x28(%r12),%rax
  b6afc1:	jbe    b6afcb <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x47b>
  b6afc3:	mov    0xd58(%rsp),%rax
  b6afcb:	lea    0xd60(%rsp),%rbx
  b6afd3:	movl   $0x0,(%rax)
  b6afd9:	mov    $0x5,%esi
  b6afde:	movq   $0x20,0xd68(%rsp)
  b6afea:	movq   $0x0,0xd70(%rsp)
  b6aff6:	mov    %rbx,%rdi
  b6aff9:	movq   $0x0,0xd80(%rsp)
  b6b005:	movq   $0x0,0xd78(%rsp)
  b6b011:	movq   $0x0,0xe08(%rsp)
  b6b01d:	movq   $0x0,0xd60(%rsp)
  b6b029:	movl   $0x0,0xd88(%rsp)
  b6b034:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b039:	cmpq   $0x20,0xd68(%rsp)
  b6b042:	lea    0x28(%rbx),%rdx
  b6b046:	jbe    b6b050 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x500>
  b6b048:	mov    0xe08(%rsp),%rdx
  b6b050:	mov    $0xfd0c0d,%eax
  b6b055:	nopl   (%rax)
  b6b058:	movzbl (%rax),%ecx
  b6b05b:	add    $0x1,%rax
  b6b05f:	mov    %ecx,(%rdx)
  b6b061:	add    $0x4,%rdx
  b6b065:	cmp    $0xfd0c12,%rax
  b6b06b:	jne    b6b058 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x508>
  b6b06d:	cmpq   $0x20,0xd68(%rsp)
  b6b076:	movq   $0x5,0xd60(%rsp)
  b6b082:	lea    0x3c(%rbx),%rax
  b6b086:	jbe    b6b094 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x544>
  b6b088:	mov    0xe08(%rsp),%rax
  b6b090:	add    $0x14,%rax
  b6b094:	movl   $0x0,(%rax)
  b6b09a:	mov    0x40(%rsp),%rax
  b6b09f:	mov    %r12,%rdx
  b6b0a2:	mov    %rbx,%rsi
  b6b0a5:	mov    0x2988(%rbp,%rax,8),%rdi
  b6b0ad:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6b0b2:	mov    %rbx,%rdi
  b6b0b5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b0ba:	jmp    b6b42a <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x8da>
  b6b0bf:	nop
  b6b0c0:	lea    0x1020(%rsp),%rbx
  b6b0c8:	xor    %esi,%esi
  b6b0ca:	movq   $0x20,0x1028(%rsp)
  b6b0d6:	movq   $0x0,0x1030(%rsp)
  b6b0e2:	movq   $0x0,0x1040(%rsp)
  b6b0ee:	mov    %rbx,%rdi
  b6b0f1:	movq   $0x0,0x1038(%rsp)
  b6b0fd:	movq   $0x0,0x10c8(%rsp)
  b6b109:	movq   $0x0,0x1020(%rsp)
  b6b115:	movl   $0x0,0x1048(%rsp)
  b6b120:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b125:	cmpq   $0x20,0x1028(%rsp)
  b6b12e:	movq   $0x0,0x1020(%rsp)
  b6b13a:	lea    0x28(%rbx),%rax
  b6b13e:	ja     b6be1e <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12ce>
  b6b144:	lea    0x10d0(%rsp),%r12
  b6b14c:	movl   $0x0,(%rax)
  b6b152:	mov    $0x5,%esi
  b6b157:	movq   $0x20,0x10d8(%rsp)
  b6b163:	movq   $0x0,0x10e0(%rsp)
  b6b16f:	mov    %r12,%rdi
  b6b172:	movq   $0x0,0x10f0(%rsp)
  b6b17e:	movq   $0x0,0x10e8(%rsp)
  b6b18a:	movq   $0x0,0x1178(%rsp)
  b6b196:	movq   $0x0,0x10d0(%rsp)
  b6b1a2:	movl   $0x0,0x10f8(%rsp)
  b6b1ad:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b1b2:	cmpq   $0x20,0x10d8(%rsp)
  b6b1bb:	lea    0x28(%r12),%rdx
  b6b1c0:	ja     b6be45 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12f5>
  b6b1c6:	mov    $0xfd0c0d,%eax
  b6b1cb:	nopl   0x0(%rax,%rax,1)
  b6b1d0:	movzbl (%rax),%ecx
  b6b1d3:	add    $0x1,%rax
  b6b1d7:	mov    %ecx,(%rdx)
  b6b1d9:	add    $0x4,%rdx
  b6b1dd:	cmp    $0xfd0c12,%rax
  b6b1e3:	jne    b6b1d0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x680>
  b6b1e5:	cmpq   $0x20,0x10d8(%rsp)
  b6b1ee:	movq   $0x5,0x10d0(%rsp)
  b6b1fa:	lea    0x3c(%r12),%rax
  b6b1ff:	ja     b6c01d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14cd>
  b6b205:	movl   $0x0,(%rax)
  b6b20b:	mov    0x40(%rsp),%rax
  b6b210:	mov    %rbx,%rdx
  b6b213:	mov    %r12,%rsi
  b6b216:	mov    0x2ea8(%rbp,%rax,8),%rdi
  b6b21e:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6b223:	mov    %r12,%rdi
  b6b226:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b22b:	mov    %rbx,%rdi
  b6b22e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b233:	cmpb   $0x0,0x348(%r13)
  b6b23b:	jne    b6af42 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x3f2>
  b6b241:	lea    0xf70(%rsp),%r12
  b6b249:	mov    $0xc,%esi
  b6b24e:	movq   $0x20,0xf78(%rsp)
  b6b25a:	movq   $0x0,0xf80(%rsp)
  b6b266:	movq   $0x0,0xf90(%rsp)
  b6b272:	mov    %r12,%rdi
  b6b275:	movq   $0x0,0xf88(%rsp)
  b6b281:	movq   $0x0,0x1018(%rsp)
  b6b28d:	movq   $0x0,0xf70(%rsp)
  b6b299:	movl   $0x0,0xf98(%rsp)
  b6b2a4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b2a9:	cmpq   $0x20,0xf78(%rsp)
  b6b2b2:	lea    0x28(%r12),%rdx
  b6b2b7:	jbe    b6b2c1 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x771>
  b6b2b9:	mov    0x1018(%rsp),%rdx
  b6b2c1:	mov    $0xfef791,%eax
  b6b2c6:	cs nopw 0x0(%rax,%rax,1)
  b6b2d0:	movzbl (%rax),%ecx
  b6b2d3:	add    $0x1,%rax
  b6b2d7:	mov    %ecx,(%rdx)
  b6b2d9:	add    $0x4,%rdx
  b6b2dd:	cmp    $0xfef79d,%rax
  b6b2e3:	jne    b6b2d0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x780>
  b6b2e5:	cmpq   $0x20,0xf78(%rsp)
  b6b2ee:	movq   $0xc,0xf70(%rsp)
  b6b2fa:	lea    0x58(%r12),%rax
  b6b2ff:	jbe    b6b30d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x7bd>
  b6b301:	mov    0x1018(%rsp),%rax
  b6b309:	add    $0x30,%rax
  b6b30d:	movl   $0x0,(%rax)
  b6b313:	mov    0x3440(%rbp),%rdi
  b6b31a:	mov    %r12,%rsi
  b6b31d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6b322:	lea    0xec0(%rsp),%r14
  b6b32a:	mov    %rax,%rsi
  b6b32d:	mov    %r14,%rdi
  b6b330:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6b335:	lea    0xe10(%rsp),%rbx
  b6b33d:	mov    $0x5,%esi
  b6b342:	movq   $0x20,0xe18(%rsp)
  b6b34e:	movq   $0x0,0xe20(%rsp)
  b6b35a:	movq   $0x0,0xe30(%rsp)
  b6b366:	mov    %rbx,%rdi
  b6b369:	movq   $0x0,0xe28(%rsp)
  b6b375:	movq   $0x0,0xeb8(%rsp)
  b6b381:	movq   $0x0,0xe10(%rsp)
  b6b38d:	movl   $0x0,0xe38(%rsp)
  b6b398:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b39d:	cmpq   $0x20,0xe18(%rsp)
  b6b3a6:	lea    0x28(%rbx),%rdx
  b6b3aa:	jbe    b6b3b4 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x864>
  b6b3ac:	mov    0xeb8(%rsp),%rdx
  b6b3b4:	mov    $0xfd0c0d,%eax
  b6b3b9:	nopl   0x0(%rax)
  b6b3c0:	movzbl (%rax),%ecx
  b6b3c3:	add    $0x1,%rax
  b6b3c7:	mov    %ecx,(%rdx)
  b6b3c9:	add    $0x4,%rdx
  b6b3cd:	cmp    $0xfd0c12,%rax
  b6b3d3:	jne    b6b3c0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x870>
  b6b3d5:	cmpq   $0x20,0xe18(%rsp)
  b6b3de:	movq   $0x5,0xe10(%rsp)
  b6b3ea:	lea    0x3c(%rbx),%rax
  b6b3ee:	jbe    b6b3fc <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x8ac>
  b6b3f0:	mov    0xeb8(%rsp),%rax
  b6b3f8:	add    $0x14,%rax
  b6b3fc:	movl   $0x0,(%rax)
  b6b402:	mov    0x40(%rsp),%rax
  b6b407:	mov    %r14,%rdx
  b6b40a:	mov    %rbx,%rsi
  b6b40d:	mov    0x2988(%rbp,%rax,8),%rdi
  b6b415:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6b41a:	mov    %rbx,%rdi
  b6b41d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b422:	mov    %r14,%rdi
  b6b425:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b42a:	mov    %r12,%rdi
  b6b42d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b432:	movss  0x38(%rsp),%xmm0
  b6b438:	cmpl   $0x1,0x3e0(%r13)
  b6b440:	addss  0x30(%rsp),%xmm0
  b6b446:	cvttss2si %xmm0,%eax
  b6b44a:	cvtsi2ss %eax,%xmm0
  b6b44e:	addss  0x4c(%rsp),%xmm0
  b6b454:	cvttss2si %xmm0,%r14
  b6b459:	jbe    b6b4d6 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x986>
  b6b45b:	mov    0x40(%rsp),%rax
  b6b460:	lea    0x15d0(%rsp),%rdi
  b6b468:	mov    %r14d,%r14d
  b6b46b:	mov    0x26f8(%rbp,%rax,8),%rsi
  b6b473:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b6b478:	movss  0x2c(%rsp),%xmm2
  b6b47e:	mulss  0x15d8(%rsp),%xmm2
  b6b487:	movss  0x2c(%rsp),%xmm0
  b6b48d:	movss  0x43937b(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b6b495:	movss  0x43d257(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b6b49d:	cmpltss %xmm2,%xmm0
  b6b4a2:	andps  %xmm0,%xmm1
  b6b4a5:	andnps %xmm3,%xmm0
  b6b4a8:	orps   %xmm1,%xmm0
  b6b4ab:	cvtsi2ss %r14,%xmm1
  b6b4b0:	addss  %xmm2,%xmm0
  b6b4b4:	cvttss2si %xmm0,%eax
  b6b4b8:	cvtsi2ss %eax,%xmm0
  b6b4bc:	addss  0x15dc(%rsp),%xmm0
  b6b4c5:	mulss  0x47b053(%rip),%xmm0        # fe6520 <_ZTV8CSubMenu+0x80>
  b6b4cd:	addss  %xmm0,%xmm1
  b6b4d1:	cvttss2si %xmm1,%r14
  b6b4d6:	mov    0x3f0(%r13),%r8d
  b6b4dd:	test   %r8d,%r8d
  b6b4e0:	je     b6b6d0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xb80>
  b6b4e6:	mov    %r15d,%r15d
  b6b4e9:	mov    0x40(%rsp),%rax
  b6b4ee:	xor    %r12d,%r12d
  b6b4f1:	mov    %r15,0x38(%rsp)
  b6b4f6:	mov    0x40(%rsp),%r15
  b6b4fb:	add    $0x3bc,%rax
  b6b501:	mov    %rax,0x30(%rsp)
  b6b506:	add    $0x4de,%r15
  b6b50d:	jmp    b6b65f <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xb0f>
  b6b512:	nopw   0x0(%rax,%rax,1)
  b6b518:	mov    0x3e8(%r13),%rax
  b6b51f:	mov    (%rax),%rax
  b6b522:	mov    0x2c8(%rax),%rbx
  b6b529:	test   %rbx,%rbx
  b6b52c:	je     b6b68d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xb3d>
  b6b532:	mov    0xb0(%rbx),%rdi
  b6b539:	test   %rdi,%rdi
  b6b53c:	je     b6b546 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x9f6>
  b6b53e:	mov    %rbx,%rsi
  b6b541:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b6b546:	mov    0x30(%rbp),%rdi
  b6b54a:	mov    %rbx,%rsi
  b6b54d:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b6b552:	cvtsi2ssq 0x38(%rsp),%xmm0
  b6b559:	mov    %r14d,%eax
  b6b55c:	movss  %xmm0,0x15c4(%rsp)
  b6b565:	lea    0x15c0(%rsp),%rsi
  b6b56d:	cvtsi2ss %rax,%xmm0
  b6b572:	mov    %rbx,%rdi
  b6b575:	movl   $0x0,0x15c0(%rsp)
  b6b580:	movl   $0x0,0x2c(%rsp)
  b6b588:	movl   $0x0,0x15c8(%rsp)
  b6b593:	movss  %xmm0,0x15cc(%rsp)
  b6b59c:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b6b5a1:	mov    0x30(%rsp),%rax
  b6b5a6:	lea    0x15b0(%rsp),%rdi
  b6b5ae:	mov    0x8(%rbp,%rax,8),%rsi
  b6b5b3:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b6b5b8:	lea    0x15b0(%rsp),%rsi
  b6b5c0:	mov    %rbx,%rdi
  b6b5c3:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b6b5c8:	mov    %rbx,%rdi
  b6b5cb:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b6b5d0:	movb   $0x1,0x3e2(%rbx)
  b6b5d7:	mov    0x8(%rbp,%r15,8),%rsi
  b6b5dc:	lea    0x15a0(%rsp),%rdi
  b6b5e4:	add    $0x1,%r12d
  b6b5e8:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b6b5ed:	movss  0x2c(%rsp),%xmm2
  b6b5f3:	cmp    0x3f0(%r13),%r12d
  b6b5fa:	mulss  0x15a8(%rsp),%xmm2
  b6b603:	movss  0x2c(%rsp),%xmm0
  b6b609:	movss  0x43d0e3(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  b6b611:	movss  0x4391f7(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b6b619:	cmpltss %xmm2,%xmm0
  b6b61e:	andps  %xmm0,%xmm1
  b6b621:	andnps %xmm3,%xmm0
  b6b624:	movss  0x15ac(%rsp),%xmm3
  b6b62d:	orps   %xmm1,%xmm0
  b6b630:	jae    b6b6d0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xb80>
  b6b636:	addss  %xmm2,%xmm0
  b6b63a:	mov    %r14d,%r14d
  b6b63d:	cvtsi2ss %r14,%xmm1
  b6b642:	cvttss2si %xmm0,%eax
  b6b646:	cvtsi2ss %eax,%xmm0
  b6b64a:	addss  %xmm3,%xmm0
  b6b64e:	mulss  0x4391da(%rip),%xmm0        # fa4830 <_ZTVN4Ogre13FrameListenerE+0x70>
  b6b656:	addss  %xmm0,%xmm1
  b6b65a:	cvttss2si %xmm1,%r14
  b6b65f:	cmp    %r12d,0x3f4(%r13)
  b6b666:	jbe    b6b518 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x9c8>
  b6b66c:	mov    %r12d,%eax
  b6b66f:	shl    $0x3,%rax
  b6b673:	add    0x3e8(%r13),%rax
  b6b67a:	mov    (%rax),%rax
  b6b67d:	mov    0x2c8(%rax),%rbx
  b6b684:	test   %rbx,%rbx
  b6b687:	jne    b6b532 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x9e2>
  b6b68d:	mov    0x70(%rbp),%rsi
  b6b691:	xor    %edx,%edx
  b6b693:	mov    %rax,%rdi
  b6b696:	mov    %rax,0x10(%rsp)
  b6b69b:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  b6b6a0:	mov    0x10(%rsp),%rax
  b6b6a5:	mov    0x2c8(%rax),%rbx
  b6b6ac:	test   %rbx,%rbx
  b6b6af:	je     b6b5d7 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xa87>
  b6b6b5:	lea    0x38(%rbx),%rdi
  b6b6b9:	mov    $0x1,%esi
  b6b6be:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b6b6c3:	movb   $0x1,0x3e2(%rbx)
  b6b6ca:	jmp    b6b532 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x9e2>
  b6b6cf:	nop
  b6b6d0:	mov    0x0(%r13),%rax
  b6b6d4:	xor    %edx,%edx
  b6b6d6:	mov    0x58(%rbp),%rsi
  b6b6da:	mov    %r13,%rdi
  b6b6dd:	call   *0x2f8(%rax)
  b6b6e3:	test   %al,%al
  b6b6e5:	je     b6b9b0 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe60>
  b6b6eb:	mov    $0x36,%esi
  b6b6f0:	mov    %r13,%rdi
  b6b6f3:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  b6b6f8:	test   %al,%al
  b6b6fa:	je     b6bd67 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1217>
  b6b700:	lea    0xc00(%rsp),%r12
  b6b708:	mov    $0xc,%esi
  b6b70d:	movq   $0x20,0xc08(%rsp)
  b6b719:	movq   $0x0,0xc10(%rsp)
  b6b725:	movq   $0x0,0xc20(%rsp)
  b6b731:	mov    %r12,%rdi
  b6b734:	movq   $0x0,0xc18(%rsp)
  b6b740:	movq   $0x0,0xca8(%rsp)
  b6b74c:	movq   $0x0,0xc00(%rsp)
  b6b758:	movl   $0x0,0xc28(%rsp)
  b6b763:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b768:	cmpq   $0x20,0xc08(%rsp)
  b6b771:	lea    0x28(%r12),%rdx
  b6b776:	ja     b6bfdc <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x148c>
  b6b77c:	mov    $0xfe609b,%eax
  b6b781:	nopl   0x0(%rax)
  b6b788:	movzbl (%rax),%ecx
  b6b78b:	add    $0x1,%rax
  b6b78f:	mov    %ecx,(%rdx)
  b6b791:	add    $0x4,%rdx
  b6b795:	cmp    $0xfe60a7,%rax
  b6b79b:	jne    b6b788 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xc38>
  b6b79d:	cmpq   $0x20,0xc08(%rsp)
  b6b7a6:	movq   $0xc,0xc00(%rsp)
  b6b7b2:	lea    0x58(%r12),%rax
  b6b7b7:	ja     b6c02e <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14de>
  b6b7bd:	movl   $0x0,(%rax)
  b6b7c3:	mov    0x3440(%rbp),%rdi
  b6b7ca:	mov    %r12,%rsi
  b6b7cd:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6b7d2:	lea    0xb50(%rsp),%r14
  b6b7da:	mov    %rax,%rsi
  b6b7dd:	mov    %r14,%rdi
  b6b7e0:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6b7e5:	lea    0xaa0(%rsp),%rbx
  b6b7ed:	mov    $0x5,%esi
  b6b7f2:	movq   $0x20,0xaa8(%rsp)
  b6b7fe:	movq   $0x0,0xab0(%rsp)
  b6b80a:	movq   $0x0,0xac0(%rsp)
  b6b816:	mov    %rbx,%rdi
  b6b819:	movq   $0x0,0xab8(%rsp)
  b6b825:	movq   $0x0,0xb48(%rsp)
  b6b831:	movq   $0x0,0xaa0(%rsp)
  b6b83d:	movl   $0x0,0xac8(%rsp)
  b6b848:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6b84d:	cmpq   $0x20,0xaa8(%rsp)
  b6b856:	lea    0x28(%rbx),%rdx
  b6b85a:	ja     b6bfcf <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x147f>
  b6b860:	mov    $0xfd0c0d,%eax
  b6b865:	nopl   (%rax)
  b6b868:	movzbl (%rax),%ecx
  b6b86b:	add    $0x1,%rax
  b6b86f:	mov    %ecx,(%rdx)
  b6b871:	add    $0x4,%rdx
  b6b875:	cmp    $0xfd0c12,%rax
  b6b87b:	jne    b6b868 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd18>
  b6b87d:	cmpq   $0x20,0xaa8(%rsp)
  b6b886:	movq   $0x5,0xaa0(%rsp)
  b6b892:	lea    0x3c(%rbx),%rax
  b6b896:	ja     b6c050 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1500>
  b6b89c:	movl   $0x0,(%rax)
  b6b8a2:	mov    0x40(%rsp),%rax
  b6b8a7:	mov    %r14,%rdx
  b6b8aa:	mov    %rbx,%rsi
  b6b8ad:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6b8b5:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6b8ba:	mov    %rbx,%rdi
  b6b8bd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b8c2:	mov    %r14,%rdi
  b6b8c5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b8ca:	mov    %r12,%rdi
  b6b8cd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b8d2:	mov    0x40(%rsp),%rax
  b6b8d7:	mov    0x3138(%rbp,%rax,8),%rdi
  b6b8df:	test   %rdi,%rdi
  b6b8e2:	je     b6b994 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  b6b8e8:	cmpl   $0x1,0x238(%r13)
  b6b8f0:	jle    b6be12 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12c2>
  b6b8f6:	mov    $0x1,%esi
  b6b8fb:	lea    0x1610(%rsp),%rbx
  b6b903:	lea    0x1620(%rsp),%r12
  b6b90b:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b6b910:	mov    0x238(%r13),%esi
  b6b917:	mov    %rbx,%rdi
  b6b91a:	call   c8e810 <_ZN7STRINGS16GetValueAsStringEi>
  b6b91f:	mov    %rbx,%rdx
  b6b922:	mov    $0x103f7f3,%esi
  b6b927:	mov    %r12,%rdi
  b6b92a:	call   56aee0 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_>
  b6b92f:	mov    0x1610(%rsp),%rdi
  b6b937:	sub    $0x18,%rdi
  b6b93b:	cmp    $0x1423a20,%rdi
  b6b942:	jne    b6c222 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16d2>
  b6b948:	lea    0x50(%rsp),%rbx
  b6b94d:	mov    0x1620(%rsp),%rsi
  b6b955:	mov    %rbx,%rdi
  b6b958:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b6b95d:	mov    0x40(%rsp),%rax
  b6b962:	mov    %rbx,%rsi
  b6b965:	mov    0x3138(%rbp,%rax,8),%rdi
  b6b96d:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  b6b972:	mov    %rbx,%rdi
  b6b975:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6b97a:	mov    0x1620(%rsp),%rdi
  b6b982:	mov    $0x1423a20,%eax
  b6b987:	sub    $0x18,%rdi
  b6b98b:	cmp    %rdi,%rax
  b6b98e:	jne    b6c279 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1729>
  b6b994:	add    $0x1638,%rsp
  b6b99b:	pop    %rbx
  b6b99c:	pop    %rbp
  b6b99d:	pop    %r12
  b6b99f:	pop    %r13
  b6b9a1:	pop    %r14
  b6b9a3:	pop    %r15
  b6b9a5:	ret
  b6b9a6:	cs nopw 0x0(%rax,%rax,1)
  b6b9b0:	mov    0x0(%r13),%rax
  b6b9b4:	mov    %r13,%rdi
  b6b9b7:	call   *0x2b0(%rax)
  b6b9bd:	test   %al,%al
  b6b9bf:	je     b6bb97 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1047>
  b6b9c5:	lea    0x470(%rsp),%r12
  b6b9cd:	mov    $0xf,%esi
  b6b9d2:	movq   $0x20,0x478(%rsp)
  b6b9de:	movq   $0x0,0x480(%rsp)
  b6b9ea:	movq   $0x0,0x490(%rsp)
  b6b9f6:	mov    %r12,%rdi
  b6b9f9:	movq   $0x0,0x488(%rsp)
  b6ba05:	movq   $0x0,0x518(%rsp)
  b6ba11:	movq   $0x0,0x470(%rsp)
  b6ba1d:	movl   $0x0,0x498(%rsp)
  b6ba28:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6ba2d:	cmpq   $0x20,0x478(%rsp)
  b6ba36:	lea    0x28(%r12),%rdx
  b6ba3b:	ja     b6c003 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14b3>
  b6ba41:	mov    $0xfe60df,%eax
  b6ba46:	cs nopw 0x0(%rax,%rax,1)
  b6ba50:	movzbl (%rax),%ecx
  b6ba53:	add    $0x1,%rax
  b6ba57:	mov    %ecx,(%rdx)
  b6ba59:	add    $0x4,%rdx
  b6ba5d:	cmp    $0xfe60ee,%rax
  b6ba63:	jne    b6ba50 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xf00>
  b6ba65:	cmpq   $0x20,0x478(%rsp)
  b6ba6e:	movq   $0xf,0x470(%rsp)
  b6ba7a:	lea    0x64(%r12),%rax
  b6ba7f:	ja     b6c072 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1522>
  b6ba85:	movl   $0x0,(%rax)
  b6ba8b:	mov    0x3440(%rbp),%rdi
  b6ba92:	mov    %r12,%rsi
  b6ba95:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6ba9a:	lea    0x3c0(%rsp),%r14
  b6baa2:	mov    %rax,%rsi
  b6baa5:	mov    %r14,%rdi
  b6baa8:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6baad:	lea    0x310(%rsp),%rbx
  b6bab5:	mov    $0x5,%esi
  b6baba:	movq   $0x20,0x318(%rsp)
  b6bac6:	movq   $0x0,0x320(%rsp)
  b6bad2:	movq   $0x0,0x330(%rsp)
  b6bade:	mov    %rbx,%rdi
  b6bae1:	movq   $0x0,0x328(%rsp)
  b6baed:	movq   $0x0,0x3b8(%rsp)
  b6baf9:	movq   $0x0,0x310(%rsp)
  b6bb05:	movl   $0x0,0x338(%rsp)
  b6bb10:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6bb15:	cmpq   $0x20,0x318(%rsp)
  b6bb1e:	lea    0x28(%rbx),%rdx
  b6bb22:	ja     b6bff6 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14a6>
  b6bb28:	mov    $0xfd0c0d,%eax
  b6bb2d:	nopl   (%rax)
  b6bb30:	movzbl (%rax),%ecx
  b6bb33:	add    $0x1,%rax
  b6bb37:	mov    %ecx,(%rdx)
  b6bb39:	add    $0x4,%rdx
  b6bb3d:	cmp    $0xfd0c12,%rax
  b6bb43:	jne    b6bb30 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xfe0>
  b6bb45:	cmpq   $0x20,0x318(%rsp)
  b6bb4e:	movq   $0x5,0x310(%rsp)
  b6bb5a:	lea    0x3c(%rbx),%rax
  b6bb5e:	ja     b6c083 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1533>
  b6bb64:	movl   $0x0,(%rax)
  b6bb6a:	mov    0x40(%rsp),%rax
  b6bb6f:	mov    %r14,%rdx
  b6bb72:	mov    %rbx,%rsi
  b6bb75:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6bb7d:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6bb82:	mov    %rbx,%rdi
  b6bb85:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bb8a:	mov    %r14,%rdi
  b6bb8d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bb92:	jmp    b6b8ca <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  b6bb97:	lea    0x260(%rsp),%r12
  b6bb9f:	mov    $0xb,%esi
  b6bba4:	movq   $0x20,0x268(%rsp)
  b6bbb0:	movq   $0x0,0x270(%rsp)
  b6bbbc:	movq   $0x0,0x280(%rsp)
  b6bbc8:	mov    %r12,%rdi
  b6bbcb:	movq   $0x0,0x278(%rsp)
  b6bbd7:	movq   $0x0,0x308(%rsp)
  b6bbe3:	movq   $0x0,0x260(%rsp)
  b6bbef:	movl   $0x0,0x288(%rsp)
  b6bbfa:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6bbff:	cmpq   $0x20,0x268(%rsp)
  b6bc08:	lea    0x28(%r12),%rdx
  b6bc0d:	ja     b6c010 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14c0>
  b6bc13:	mov    $0xfe60e3,%eax
  b6bc18:	nopl   0x0(%rax,%rax,1)
  b6bc20:	movzbl (%rax),%ecx
  b6bc23:	add    $0x1,%rax
  b6bc27:	mov    %ecx,(%rdx)
  b6bc29:	add    $0x4,%rdx
  b6bc2d:	cmp    $0xfe60ee,%rax
  b6bc33:	jne    b6bc20 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x10d0>
  b6bc35:	cmpq   $0x20,0x268(%rsp)
  b6bc3e:	movq   $0xb,0x260(%rsp)
  b6bc4a:	lea    0x54(%r12),%rax
  b6bc4f:	ja     b6c061 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1511>
  b6bc55:	movl   $0x0,(%rax)
  b6bc5b:	mov    0x3440(%rbp),%rdi
  b6bc62:	mov    %r12,%rsi
  b6bc65:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6bc6a:	lea    0x1b0(%rsp),%r14
  b6bc72:	mov    %rax,%rsi
  b6bc75:	mov    %r14,%rdi
  b6bc78:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6bc7d:	lea    0x100(%rsp),%rbx
  b6bc85:	mov    $0x5,%esi
  b6bc8a:	movq   $0x20,0x108(%rsp)
  b6bc96:	movq   $0x0,0x110(%rsp)
  b6bca2:	movq   $0x0,0x120(%rsp)
  b6bcae:	mov    %rbx,%rdi
  b6bcb1:	movq   $0x0,0x118(%rsp)
  b6bcbd:	movq   $0x0,0x1a8(%rsp)
  b6bcc9:	movq   $0x0,0x100(%rsp)
  b6bcd5:	movl   $0x0,0x128(%rsp)
  b6bce0:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6bce5:	cmpq   $0x20,0x108(%rsp)
  b6bcee:	lea    0x28(%rbx),%rdx
  b6bcf2:	ja     b6bfe9 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1499>
  b6bcf8:	mov    $0xfd0c0d,%eax
  b6bcfd:	nopl   (%rax)
  b6bd00:	movzbl (%rax),%ecx
  b6bd03:	add    $0x1,%rax
  b6bd07:	mov    %ecx,(%rdx)
  b6bd09:	add    $0x4,%rdx
  b6bd0d:	cmp    $0xfd0c12,%rax
  b6bd13:	jne    b6bd00 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x11b0>
  b6bd15:	cmpq   $0x20,0x108(%rsp)
  b6bd1e:	movq   $0x5,0x100(%rsp)
  b6bd2a:	lea    0x3c(%rbx),%rax
  b6bd2e:	ja     b6c03f <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x14ef>
  b6bd34:	movl   $0x0,(%rax)
  b6bd3a:	mov    0x40(%rsp),%rax
  b6bd3f:	mov    %r14,%rdx
  b6bd42:	mov    %rbx,%rsi
  b6bd45:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6bd4d:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6bd52:	mov    %rbx,%rdi
  b6bd55:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bd5a:	mov    %r14,%rdi
  b6bd5d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bd62:	jmp    b6b8ca <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  b6bd67:	mov    0x0(%r13),%rax
  b6bd6b:	mov    %r13,%rdi
  b6bd6e:	call   *0x2b0(%rax)
  b6bd74:	test   %al,%al
  b6bd76:	je     b6be52 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1302>
  b6bd7c:	mov    $0x37,%esi
  b6bd81:	mov    %r13,%rdi
  b6bd84:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  b6bd89:	test   %al,%al
  b6bd8b:	je     b6c0cc <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x157c>
  b6bd91:	lea    0x9f0(%rsp),%r14
  b6bd99:	mov    $0xfe60a8,%esi
  b6bd9e:	mov    %r14,%rdi
  b6bda1:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6bda6:	mov    0x3440(%rbp),%rdi
  b6bdad:	mov    %r14,%rsi
  b6bdb0:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6bdb5:	lea    0x940(%rsp),%r12
  b6bdbd:	mov    %rax,%rsi
  b6bdc0:	mov    %r12,%rdi
  b6bdc3:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6bdc8:	lea    0x890(%rsp),%rbx
  b6bdd0:	mov    $0xfd0c0d,%esi
  b6bdd5:	mov    %rbx,%rdi
  b6bdd8:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6bddd:	mov    0x40(%rsp),%rax
  b6bde2:	mov    %r12,%rdx
  b6bde5:	mov    %rbx,%rsi
  b6bde8:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6bdf0:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6bdf5:	mov    %rbx,%rdi
  b6bdf8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bdfd:	mov    %r12,%rdi
  b6be00:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6be05:	mov    %r14,%rdi
  b6be08:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6be0d:	jmp    b6b8d2 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd82>
  b6be12:	xor    %esi,%esi
  b6be14:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b6be19:	jmp    b6b994 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  b6be1e:	mov    0x10c8(%rsp),%rax
  b6be26:	jmp    b6b144 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x5f4>
  b6be2b:	mov    0x1438(%rsp),%rdx
  b6be33:	jmp    b6aea8 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x358>
  b6be38:	mov    0x1598(%rsp),%rdx
  b6be40:	jmp    b6adbd <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x26d>
  b6be45:	mov    0x1178(%rsp),%rdx
  b6be4d:	jmp    b6b1c6 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x676>
  b6be52:	lea    0x520(%rsp),%r12
  b6be5a:	xor    %esi,%esi
  b6be5c:	movq   $0x20,0x528(%rsp)
  b6be68:	movq   $0x0,0x530(%rsp)
  b6be74:	movq   $0x0,0x540(%rsp)
  b6be80:	mov    %r12,%rdi
  b6be83:	movq   $0x0,0x538(%rsp)
  b6be8f:	movq   $0x0,0x5c8(%rsp)
  b6be9b:	movq   $0x0,0x520(%rsp)
  b6bea7:	movl   $0x0,0x548(%rsp)
  b6beb2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6beb7:	cmpq   $0x20,0x528(%rsp)
  b6bec0:	movq   $0x0,0x520(%rsp)
  b6becc:	lea    0x28(%r12),%rax
  b6bed1:	jbe    b6bedb <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x138b>
  b6bed3:	mov    0x5c8(%rsp),%rax
  b6bedb:	lea    0x5d0(%rsp),%rbx
  b6bee3:	movl   $0x0,(%rax)
  b6bee9:	mov    $0x5,%esi
  b6beee:	movq   $0x20,0x5d8(%rsp)
  b6befa:	movq   $0x0,0x5e0(%rsp)
  b6bf06:	mov    %rbx,%rdi
  b6bf09:	movq   $0x0,0x5f0(%rsp)
  b6bf15:	movq   $0x0,0x5e8(%rsp)
  b6bf21:	movq   $0x0,0x678(%rsp)
  b6bf2d:	movq   $0x0,0x5d0(%rsp)
  b6bf39:	movl   $0x0,0x5f8(%rsp)
  b6bf44:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b6bf49:	cmpq   $0x20,0x5d8(%rsp)
  b6bf52:	lea    0x28(%rbx),%rdx
  b6bf56:	jbe    b6bf60 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1410>
  b6bf58:	mov    0x678(%rsp),%rdx
  b6bf60:	mov    $0xfd0c0d,%eax
  b6bf65:	nopl   (%rax)
  b6bf68:	movzbl (%rax),%ecx
  b6bf6b:	add    $0x1,%rax
  b6bf6f:	mov    %ecx,(%rdx)
  b6bf71:	add    $0x4,%rdx
  b6bf75:	cmp    $0xfd0c12,%rax
  b6bf7b:	jne    b6bf68 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1418>
  b6bf7d:	cmpq   $0x20,0x5d8(%rsp)
  b6bf86:	movq   $0x5,0x5d0(%rsp)
  b6bf92:	lea    0x3c(%rbx),%rax
  b6bf96:	jbe    b6bfa4 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1454>
  b6bf98:	mov    0x678(%rsp),%rax
  b6bfa0:	add    $0x14,%rax
  b6bfa4:	movl   $0x0,(%rax)
  b6bfaa:	mov    0x40(%rsp),%rax
  b6bfaf:	mov    %r12,%rdx
  b6bfb2:	mov    %rbx,%rsi
  b6bfb5:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6bfbd:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6bfc2:	mov    %rbx,%rdi
  b6bfc5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6bfca:	jmp    b6b8ca <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  b6bfcf:	mov    0xb48(%rsp),%rdx
  b6bfd7:	jmp    b6b860 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd10>
  b6bfdc:	mov    0xca8(%rsp),%rdx
  b6bfe4:	jmp    b6b77c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xc2c>
  b6bfe9:	mov    0x1a8(%rsp),%rdx
  b6bff1:	jmp    b6bcf8 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x11a8>
  b6bff6:	mov    0x3b8(%rsp),%rdx
  b6bffe:	jmp    b6bb28 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xfd8>
  b6c003:	mov    0x518(%rsp),%rdx
  b6c00b:	jmp    b6ba41 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xef1>
  b6c010:	mov    0x308(%rsp),%rdx
  b6c018:	jmp    b6bc13 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x10c3>
  b6c01d:	mov    0x1178(%rsp),%rax
  b6c025:	add    $0x14,%rax
  b6c029:	jmp    b6b205 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x6b5>
  b6c02e:	mov    0xca8(%rsp),%rax
  b6c036:	add    $0x30,%rax
  b6c03a:	jmp    b6b7bd <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xc6d>
  b6c03f:	mov    0x1a8(%rsp),%rax
  b6c047:	add    $0x14,%rax
  b6c04b:	jmp    b6bd34 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x11e4>
  b6c050:	mov    0xb48(%rsp),%rax
  b6c058:	add    $0x14,%rax
  b6c05c:	jmp    b6b89c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xd4c>
  b6c061:	mov    0x308(%rsp),%rax
  b6c069:	add    $0x2c,%rax
  b6c06d:	jmp    b6bc55 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1105>
  b6c072:	mov    0x518(%rsp),%rax
  b6c07a:	add    $0x3c,%rax
  b6c07e:	jmp    b6ba85 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xf35>
  b6c083:	mov    0x3b8(%rsp),%rax
  b6c08b:	add    $0x14,%rax
  b6c08f:	jmp    b6bb64 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1014>
  b6c094:	mov    0x70(%rbp),%rsi
  b6c098:	xor    %edx,%edx
  b6c09a:	mov    %r13,%rdi
  b6c09d:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  b6c0a2:	mov    0x2c8(%r13),%rbx
  b6c0a9:	test   %rbx,%rbx
  b6c0ac:	je     b6ad1b <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1cb>
  b6c0b2:	lea    0x38(%rbx),%rdi
  b6c0b6:	mov    $0x1,%esi
  b6c0bb:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b6c0c0:	movb   $0x1,0x3e2(%rbx)
  b6c0c7:	jmp    b6ac38 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe8>
  b6c0cc:	lea    0x7e0(%rsp),%r14
  b6c0d4:	mov    $0xfe60b5,%esi
  b6c0d9:	mov    %r14,%rdi
  b6c0dc:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6c0e1:	mov    0x3440(%rbp),%rdi
  b6c0e8:	mov    %r14,%rsi
  b6c0eb:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6c0f0:	lea    0x730(%rsp),%r12
  b6c0f8:	mov    %rax,%rsi
  b6c0fb:	mov    %r12,%rdi
  b6c0fe:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6c103:	lea    0x680(%rsp),%rbx
  b6c10b:	mov    $0xfd0c0d,%esi
  b6c110:	mov    %rbx,%rdi
  b6c113:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6c118:	mov    0x40(%rsp),%rax
  b6c11d:	mov    %r12,%rdx
  b6c120:	mov    %rbx,%rsi
  b6c123:	mov    0x2c18(%rbp,%rax,8),%rdi
  b6c12b:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6c130:	mov    %rbx,%rdi
  b6c133:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c138:	mov    %r12,%rdi
  b6c13b:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c140:	jmp    b6be05 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x12b5>
  b6c145:	lea    0x12e0(%rsp),%r14
  b6c14d:	mov    $0xfe60d1,%esi
  b6c152:	mov    %r14,%rdi
  b6c155:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6c15a:	mov    0x3440(%rbp),%rdi
  b6c161:	mov    %r14,%rsi
  b6c164:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  b6c169:	lea    0x1230(%rsp),%r12
  b6c171:	mov    %rax,%rsi
  b6c174:	mov    %r12,%rdi
  b6c177:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  b6c17c:	lea    0x1180(%rsp),%rbx
  b6c184:	mov    $0xfd0c0d,%esi
  b6c189:	mov    %rbx,%rdi
  b6c18c:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  b6c191:	mov    0x40(%rsp),%rax
  b6c196:	mov    %r12,%rdx
  b6c199:	mov    %rbx,%rsi
  b6c19c:	mov    0x2ea8(%rbp,%rax,8),%rdi
  b6c1a4:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b6c1a9:	mov    %rbx,%rdi
  b6c1ac:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1b1:	mov    %r12,%rdi
  b6c1b4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1b9:	mov    %r14,%rdi
  b6c1bc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1c1:	jmp    b6af22 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x3d2>
  b6c1c6:	mov    %rbx,%rdi
  b6c1c9:	mov    %rax,%rbp
  b6c1cc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1d1:	mov    %r12,%rdi
  b6c1d4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1d9:	mov    %r14,%rdi
  b6c1dc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c1e1:	mov    %rbp,%rdi
  b6c1e4:	call   554498 <_Unwind_Resume@plt>
  b6c1e9:	jmp    b6c1c6 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1676>
  b6c1eb:	mov    %rax,%rbp
  b6c1ee:	xchg   %ax,%ax
  b6c1f0:	jmp    b6c1d1 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1681>
  b6c1f2:	mov    %rax,%rbp
  b6c1f5:	jmp    b6c1d9 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1689>
  b6c1f7:	jmp    b6c1eb <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x169b>
  b6c1f9:	nopl   0x0(%rax)
  b6c200:	jmp    b6c1f2 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16a2>
  b6c202:	mov    %rbx,%rdi
  b6c205:	mov    %rax,%rbp
  b6c208:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c20d:	mov    %r12,%rdi
  b6c210:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c215:	mov    %rbp,%rdi
  b6c218:	call   554498 <_Unwind_Resume@plt>
  b6c21d:	mov    %rax,%rbp
  b6c220:	jmp    b6c20d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16bd>
  b6c222:	mov    $0x5541c8,%eax
  b6c227:	test   %rax,%rax
  b6c22a:	je     b6c261 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1711>
  b6c22c:	or     $0xffffffff,%eax
  b6c22f:	lock xadd %eax,0x10(%rdi)
  b6c234:	test   %eax,%eax
  b6c236:	jg     b6b948 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xdf8>
  b6c23c:	lea    0x162f(%rsp),%rsi
  b6c244:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b6c249:	jmp    b6b948 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xdf8>
  b6c24e:	mov    %rax,%rbp
  b6c251:	mov    %r12,%rdi
  b6c254:	call   556288 <_ZNSsD1Ev@plt>
  b6c259:	mov    %rbp,%rdi
  b6c25c:	call   554498 <_Unwind_Resume@plt>
  b6c261:	mov    0x10(%rdi),%eax
  b6c264:	lea    -0x1(%rax),%edx
  b6c267:	mov    %edx,0x10(%rdi)
  b6c26a:	jmp    b6c234 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16e4>
  b6c26c:	mov    %rbx,%rdi
  b6c26f:	mov    %rax,%rbp
  b6c272:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c277:	jmp    b6c251 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1701>
  b6c279:	mov    $0x5541c8,%eax
  b6c27e:	test   %rax,%rax
  b6c281:	je     b6c2cc <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x177c>
  b6c283:	or     $0xffffffff,%eax
  b6c286:	lock xadd %eax,0x10(%rdi)
  b6c28b:	test   %eax,%eax
  b6c28d:	jg     b6b994 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  b6c293:	lea    0x162e(%rsp),%rsi
  b6c29b:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b6c2a0:	jmp    b6b994 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  b6c2a5:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c2aa:	nopw   0x0(%rax,%rax,1)
  b6c2b0:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c2b5:	mov    %rax,%rbp
  b6c2b8:	mov    %r14,%rdi
  b6c2bb:	nopl   0x0(%rax,%rax,1)
  b6c2c0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c2c5:	jmp    b6c20d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16bd>
  b6c2ca:	jmp    b6c2b5 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  b6c2cc:	mov    0x10(%rdi),%eax
  b6c2cf:	lea    -0x1(%rax),%edx
  b6c2d2:	mov    %edx,0x10(%rdi)
  b6c2d5:	jmp    b6c28b <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x173b>
  b6c2d7:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c2dc:	jmp    b6c2b5 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  b6c2de:	mov    %rbx,%rdi
  b6c2e1:	mov    %rax,%rbp
  b6c2e4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c2e9:	jmp    b6c2b8 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1768>
  b6c2eb:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c2f0:	jmp    b6c2de <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  b6c2f2:	mov    %rax,%rbp
  b6c2f5:	mov    %rbx,%rdi
  b6c2f8:	call   556288 <_ZNSsD1Ev@plt>
  b6c2fd:	mov    %rbp,%rdi
  b6c300:	call   554498 <_Unwind_Resume@plt>
  b6c305:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c30a:	jmp    b6c2b5 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  b6c30c:	mov    %rax,%rdi
  b6c30f:	nop
  b6c310:	call   554498 <_Unwind_Resume@plt>
  b6c315:	jmp    b6c30c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  b6c317:	jmp    b6c2de <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  b6c319:	nopl   0x0(%rax)
  b6c320:	jmp    b6c30c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  b6c322:	mov    %rax,%rbp
  b6c325:	mov    %rbx,%rdi
  b6c328:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c32d:	mov    %rbp,%rdi
  b6c330:	call   554498 <_Unwind_Resume@plt>
  b6c335:	jmp    b6c30c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  b6c337:	jmp    b6c2de <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  b6c339:	mov    %r12,%rdi
  b6c33c:	mov    %rax,%rbp
  b6c33f:	nop
  b6c340:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6c345:	jmp    b6c325 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x17d5>
  b6c347:	jmp    b6c202 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16b2>
  b6c34c:	nopl   0x0(%rax)
  b6c350:	jmp    b6c2b5 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  b6c355:	data16 cs nopw 0x0(%rax,%rax,1)
  b6c360:	jmp    b6c21d <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  b6c365:	data16 cs nopw 0x0(%rax,%rax,1)
  b6c370:	jmp    b6c30c <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  b6c372:	jmp    b6c2de <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  b6c377:	nopw   0x0(%rax,%rax,1)
  b6c380:	jmp    b6c1c6 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x1676>
  b6c385:	data16 cs nopw 0x0(%rax,%rax,1)
  b6c390:	jmp    b6c1eb <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x169b>
  b6c395:	data16 cs nopw 0x0(%rax,%rax,1)
  b6c3a0:	jmp    b6c1f2 <_ZN13CMerchantMenu14setPetSlotIconEP10CEquipmentii+0x16a2>
