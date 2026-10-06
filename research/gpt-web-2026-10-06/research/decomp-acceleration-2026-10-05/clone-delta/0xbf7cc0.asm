
../game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000bf7cc0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii>:
  bf7cc0:	push   %r15
  bf7cc2:	movslq %edx,%rdx
  bf7cc5:	push   %r14
  bf7cc7:	push   %r13
  bf7cc9:	mov    %rsi,%r13
  bf7ccc:	push   %r12
  bf7cce:	mov    %ecx,%r12d
  bf7cd1:	push   %rbp
  bf7cd2:	mov    %rdi,%rbp
  bf7cd5:	push   %rbx
  bf7cd6:	mov    %rdx,%rbx
  bf7cd9:	add    $0x4de,%rbx
  bf7ce0:	sub    $0x1638,%rsp
  bf7ce7:	mov    %rdx,0x40(%rsp)
  bf7cec:	mov    0x8(%rdi,%rbx,8),%rdi
  bf7cf1:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  bf7cf6:	xorps  %xmm0,%xmm0
  bf7cf9:	movss  0x3acb0f(%rip),%xmm3        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  bf7d01:	movaps %xmm3,%xmm1
  bf7d04:	movss  0x3b09e8(%rip),%xmm2        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  bf7d0c:	movss  %xmm0,0x2c(%rsp)
  bf7d12:	mulss  0x8(%rax),%xmm0
  bf7d17:	movss  %xmm0,0x38(%rsp)
  bf7d1d:	movss  0x2c(%rsp),%xmm0
  bf7d23:	cmpltss 0x38(%rsp),%xmm0
  bf7d2a:	andps  %xmm0,%xmm1
  bf7d2d:	andnps %xmm2,%xmm0
  bf7d30:	orps   %xmm1,%xmm0
  bf7d33:	movss  %xmm0,0x30(%rsp)
  bf7d39:	movss  0xc(%rax),%xmm0
  bf7d3e:	movss  %xmm0,0x4c(%rsp)
  bf7d44:	mov    0x8(%rbp,%rbx,8),%rdi
  bf7d49:	movss  %xmm2,(%rsp)
  bf7d4e:	movss  %xmm3,0x10(%rsp)
  bf7d54:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  bf7d59:	movss  0x2c(%rsp),%xmm1
  bf7d5f:	mulss  (%rax),%xmm1
  bf7d63:	movss  0x2c(%rsp),%xmm0
  bf7d69:	movss  0x10(%rsp),%xmm3
  bf7d6f:	mov    0x2c8(%r13),%rbx
  bf7d76:	movss  (%rsp),%xmm2
  bf7d7b:	test   %rbx,%rbx
  bf7d7e:	cmpltss %xmm1,%xmm0
  bf7d83:	andps  %xmm0,%xmm3
  bf7d86:	andnps %xmm2,%xmm0
  bf7d89:	orps   %xmm3,%xmm0
  bf7d8c:	addss  %xmm1,%xmm0
  bf7d90:	cvttss2si %xmm0,%edx
  bf7d94:	cvtsi2ss %edx,%xmm0
  bf7d98:	addss  0x4(%rax),%xmm0
  bf7d9d:	cvttss2si %xmm0,%r15
  bf7da2:	je     bf9204 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1544>
  bf7da8:	mov    0xb0(%rbx),%rdi
  bf7daf:	test   %rdi,%rdi
  bf7db2:	je     bf7dbc <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xfc>
  bf7db4:	mov    %rbx,%rsi
  bf7db7:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  bf7dbc:	mov    0x40(%rsp),%rax
  bf7dc1:	mov    %rbx,%rsi
  bf7dc4:	mov    0x26f8(%rbp,%rax,8),%rdi
  bf7dcc:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  bf7dd1:	lea    0x1600(%rsp),%rsi
  bf7dd9:	mov    %rbx,%rdi
  bf7ddc:	movl   $0x0,0x1604(%rsp)
  bf7de7:	movl   $0x0,0x1600(%rsp)
  bf7df2:	movl   $0x3f800000,0x160c(%rsp)
  bf7dfd:	movl   $0x0,0x1608(%rsp)
  bf7e08:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  bf7e0d:	lea    0x15f0(%rsp),%rsi
  bf7e15:	mov    %rbx,%rdi
  bf7e18:	movl   $0x0,0x15f4(%rsp)
  bf7e23:	movl   $0x0,0x15f0(%rsp)
  bf7e2e:	movl   $0x0,0x15fc(%rsp)
  bf7e39:	movl   $0x0,0x15f8(%rsp)
  bf7e44:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  bf7e49:	mov    0x40(%rsp),%rax
  bf7e4e:	lea    0x15e0(%rsp),%r14
  bf7e56:	mov    %r14,%rdi
  bf7e59:	mov    0x26f8(%rbp,%rax,8),%rsi
  bf7e61:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  bf7e66:	mov    %r14,%rsi
  bf7e69:	mov    %rbx,%rdi
  bf7e6c:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  bf7e71:	mov    %rbx,%rdi
  bf7e74:	movslq %r12d,%r12
  bf7e77:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  bf7e7c:	lea    0xb0(%rbp,%r12,4),%rax
  bf7e84:	mov    %rax,0x1d8(%rbx)
  bf7e8b:	cmpb   $0x0,0x348(%r13)
  bf7e93:	je     bf8230 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x570>
  bf7e99:	mov    0x3e0(%r13),%eax
  bf7ea0:	test   %eax,%eax
  bf7ea2:	je     bf8230 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x570>
  bf7ea8:	cmp    $0x1,%eax
  bf7eab:	jbe    bf92b5 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x15f5>
  bf7eb1:	lea    0x14f0(%rsp),%r12
  bf7eb9:	mov    $0xd,%esi
  bf7ebe:	movq   $0x20,0x14f8(%rsp)
  bf7eca:	movq   $0x0,0x1500(%rsp)
  bf7ed6:	movq   $0x0,0x1510(%rsp)
  bf7ee2:	mov    %r12,%rdi
  bf7ee5:	movq   $0x0,0x1508(%rsp)
  bf7ef1:	movq   $0x0,0x1598(%rsp)
  bf7efd:	movq   $0x0,0x14f0(%rsp)
  bf7f09:	movl   $0x0,0x1518(%rsp)
  bf7f14:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf7f19:	cmpq   $0x20,0x14f8(%rsp)
  bf7f22:	lea    0x28(%r12),%rdx
  bf7f27:	ja     bf8fa8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12e8>
  bf7f2d:	mov    $0xfe60c3,%eax
  bf7f32:	nopw   0x0(%rax,%rax,1)
  bf7f38:	movzbl (%rax),%ecx
  bf7f3b:	add    $0x1,%rax
  bf7f3f:	mov    %ecx,(%rdx)
  bf7f41:	add    $0x4,%rdx
  bf7f45:	cmp    $0xfe60d0,%rax
  bf7f4b:	jne    bf7f38 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x278>
  bf7f4d:	cmpq   $0x20,0x14f8(%rsp)
  bf7f56:	movq   $0xd,0x14f0(%rsp)
  bf7f62:	lea    0x5c(%r12),%rax
  bf7f67:	jbe    bf7f75 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x2b5>
  bf7f69:	mov    0x1598(%rsp),%rax
  bf7f71:	add    $0x34,%rax
  bf7f75:	movl   $0x0,(%rax)
  bf7f7b:	mov    0x3410(%rbp),%rdi
  bf7f82:	mov    %r12,%rsi
  bf7f85:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf7f8a:	lea    0x1440(%rsp),%r14
  bf7f92:	mov    %rax,%rsi
  bf7f95:	mov    %r14,%rdi
  bf7f98:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf7f9d:	lea    0x1390(%rsp),%rbx
  bf7fa5:	mov    $0x5,%esi
  bf7faa:	movq   $0x20,0x1398(%rsp)
  bf7fb6:	movq   $0x0,0x13a0(%rsp)
  bf7fc2:	movq   $0x0,0x13b0(%rsp)
  bf7fce:	mov    %rbx,%rdi
  bf7fd1:	movq   $0x0,0x13a8(%rsp)
  bf7fdd:	movq   $0x0,0x1438(%rsp)
  bf7fe9:	movq   $0x0,0x1390(%rsp)
  bf7ff5:	movl   $0x0,0x13b8(%rsp)
  bf8000:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8005:	cmpq   $0x20,0x1398(%rsp)
  bf800e:	lea    0x28(%rbx),%rdx
  bf8012:	ja     bf8f9b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12db>
  bf8018:	mov    $0xfd0c0d,%eax
  bf801d:	nopl   (%rax)
  bf8020:	movzbl (%rax),%ecx
  bf8023:	add    $0x1,%rax
  bf8027:	mov    %ecx,(%rdx)
  bf8029:	add    $0x4,%rdx
  bf802d:	cmp    $0xfd0c12,%rax
  bf8033:	jne    bf8020 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x360>
  bf8035:	cmpq   $0x20,0x1398(%rsp)
  bf803e:	movq   $0x5,0x1390(%rsp)
  bf804a:	lea    0x3c(%rbx),%rax
  bf804e:	jbe    bf805c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x39c>
  bf8050:	mov    0x1438(%rsp),%rax
  bf8058:	add    $0x14,%rax
  bf805c:	movl   $0x0,(%rax)
  bf8062:	mov    0x40(%rsp),%rax
  bf8067:	mov    %r14,%rdx
  bf806a:	mov    %rbx,%rsi
  bf806d:	mov    0x2ea8(%rbp,%rax,8),%rdi
  bf8075:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf807a:	mov    %rbx,%rdi
  bf807d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8082:	mov    %r14,%rdi
  bf8085:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf808a:	mov    %r12,%rdi
  bf808d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8092:	mov    0x40(%rsp),%rax
  bf8097:	mov    0x2ea8(%rbp,%rax,8),%rdi
  bf809f:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  bf80a4:	cmpb   $0x0,0x348(%r13)
  bf80ac:	je     bf83b1 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x6f1>
  bf80b2:	lea    0xcb0(%rsp),%r12
  bf80ba:	xor    %esi,%esi
  bf80bc:	movq   $0x20,0xcb8(%rsp)
  bf80c8:	movq   $0x0,0xcc0(%rsp)
  bf80d4:	movq   $0x0,0xcd0(%rsp)
  bf80e0:	mov    %r12,%rdi
  bf80e3:	movq   $0x0,0xcc8(%rsp)
  bf80ef:	movq   $0x0,0xd58(%rsp)
  bf80fb:	movq   $0x0,0xcb0(%rsp)
  bf8107:	movl   $0x0,0xcd8(%rsp)
  bf8112:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8117:	cmpq   $0x20,0xcb8(%rsp)
  bf8120:	movq   $0x0,0xcb0(%rsp)
  bf812c:	lea    0x28(%r12),%rax
  bf8131:	jbe    bf813b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x47b>
  bf8133:	mov    0xd58(%rsp),%rax
  bf813b:	lea    0xd60(%rsp),%rbx
  bf8143:	movl   $0x0,(%rax)
  bf8149:	mov    $0x5,%esi
  bf814e:	movq   $0x20,0xd68(%rsp)
  bf815a:	movq   $0x0,0xd70(%rsp)
  bf8166:	mov    %rbx,%rdi
  bf8169:	movq   $0x0,0xd80(%rsp)
  bf8175:	movq   $0x0,0xd78(%rsp)
  bf8181:	movq   $0x0,0xe08(%rsp)
  bf818d:	movq   $0x0,0xd60(%rsp)
  bf8199:	movl   $0x0,0xd88(%rsp)
  bf81a4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf81a9:	cmpq   $0x20,0xd68(%rsp)
  bf81b2:	lea    0x28(%rbx),%rdx
  bf81b6:	jbe    bf81c0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x500>
  bf81b8:	mov    0xe08(%rsp),%rdx
  bf81c0:	mov    $0xfd0c0d,%eax
  bf81c5:	nopl   (%rax)
  bf81c8:	movzbl (%rax),%ecx
  bf81cb:	add    $0x1,%rax
  bf81cf:	mov    %ecx,(%rdx)
  bf81d1:	add    $0x4,%rdx
  bf81d5:	cmp    $0xfd0c12,%rax
  bf81db:	jne    bf81c8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x508>
  bf81dd:	cmpq   $0x20,0xd68(%rsp)
  bf81e6:	movq   $0x5,0xd60(%rsp)
  bf81f2:	lea    0x3c(%rbx),%rax
  bf81f6:	jbe    bf8204 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x544>
  bf81f8:	mov    0xe08(%rsp),%rax
  bf8200:	add    $0x14,%rax
  bf8204:	movl   $0x0,(%rax)
  bf820a:	mov    0x40(%rsp),%rax
  bf820f:	mov    %r12,%rdx
  bf8212:	mov    %rbx,%rsi
  bf8215:	mov    0x2988(%rbp,%rax,8),%rdi
  bf821d:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8222:	mov    %rbx,%rdi
  bf8225:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf822a:	jmp    bf859a <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x8da>
  bf822f:	nop
  bf8230:	lea    0x1020(%rsp),%rbx
  bf8238:	xor    %esi,%esi
  bf823a:	movq   $0x20,0x1028(%rsp)
  bf8246:	movq   $0x0,0x1030(%rsp)
  bf8252:	movq   $0x0,0x1040(%rsp)
  bf825e:	mov    %rbx,%rdi
  bf8261:	movq   $0x0,0x1038(%rsp)
  bf826d:	movq   $0x0,0x10c8(%rsp)
  bf8279:	movq   $0x0,0x1020(%rsp)
  bf8285:	movl   $0x0,0x1048(%rsp)
  bf8290:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8295:	cmpq   $0x20,0x1028(%rsp)
  bf829e:	movq   $0x0,0x1020(%rsp)
  bf82aa:	lea    0x28(%rbx),%rax
  bf82ae:	ja     bf8f8e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12ce>
  bf82b4:	lea    0x10d0(%rsp),%r12
  bf82bc:	movl   $0x0,(%rax)
  bf82c2:	mov    $0x5,%esi
  bf82c7:	movq   $0x20,0x10d8(%rsp)
  bf82d3:	movq   $0x0,0x10e0(%rsp)
  bf82df:	mov    %r12,%rdi
  bf82e2:	movq   $0x0,0x10f0(%rsp)
  bf82ee:	movq   $0x0,0x10e8(%rsp)
  bf82fa:	movq   $0x0,0x1178(%rsp)
  bf8306:	movq   $0x0,0x10d0(%rsp)
  bf8312:	movl   $0x0,0x10f8(%rsp)
  bf831d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8322:	cmpq   $0x20,0x10d8(%rsp)
  bf832b:	lea    0x28(%r12),%rdx
  bf8330:	ja     bf8fb5 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12f5>
  bf8336:	mov    $0xfd0c0d,%eax
  bf833b:	nopl   0x0(%rax,%rax,1)
  bf8340:	movzbl (%rax),%ecx
  bf8343:	add    $0x1,%rax
  bf8347:	mov    %ecx,(%rdx)
  bf8349:	add    $0x4,%rdx
  bf834d:	cmp    $0xfd0c12,%rax
  bf8353:	jne    bf8340 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x680>
  bf8355:	cmpq   $0x20,0x10d8(%rsp)
  bf835e:	movq   $0x5,0x10d0(%rsp)
  bf836a:	lea    0x3c(%r12),%rax
  bf836f:	ja     bf918d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14cd>
  bf8375:	movl   $0x0,(%rax)
  bf837b:	mov    0x40(%rsp),%rax
  bf8380:	mov    %rbx,%rdx
  bf8383:	mov    %r12,%rsi
  bf8386:	mov    0x2ea8(%rbp,%rax,8),%rdi
  bf838e:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8393:	mov    %r12,%rdi
  bf8396:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf839b:	mov    %rbx,%rdi
  bf839e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf83a3:	cmpb   $0x0,0x348(%r13)
  bf83ab:	jne    bf80b2 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x3f2>
  bf83b1:	lea    0xf70(%rsp),%r12
  bf83b9:	mov    $0xc,%esi
  bf83be:	movq   $0x20,0xf78(%rsp)
  bf83ca:	movq   $0x0,0xf80(%rsp)
  bf83d6:	movq   $0x0,0xf90(%rsp)
  bf83e2:	mov    %r12,%rdi
  bf83e5:	movq   $0x0,0xf88(%rsp)
  bf83f1:	movq   $0x0,0x1018(%rsp)
  bf83fd:	movq   $0x0,0xf70(%rsp)
  bf8409:	movl   $0x0,0xf98(%rsp)
  bf8414:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8419:	cmpq   $0x20,0xf78(%rsp)
  bf8422:	lea    0x28(%r12),%rdx
  bf8427:	jbe    bf8431 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x771>
  bf8429:	mov    0x1018(%rsp),%rdx
  bf8431:	mov    $0xfef791,%eax
  bf8436:	cs nopw 0x0(%rax,%rax,1)
  bf8440:	movzbl (%rax),%ecx
  bf8443:	add    $0x1,%rax
  bf8447:	mov    %ecx,(%rdx)
  bf8449:	add    $0x4,%rdx
  bf844d:	cmp    $0xfef79d,%rax
  bf8453:	jne    bf8440 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x780>
  bf8455:	cmpq   $0x20,0xf78(%rsp)
  bf845e:	movq   $0xc,0xf70(%rsp)
  bf846a:	lea    0x58(%r12),%rax
  bf846f:	jbe    bf847d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x7bd>
  bf8471:	mov    0x1018(%rsp),%rax
  bf8479:	add    $0x30,%rax
  bf847d:	movl   $0x0,(%rax)
  bf8483:	mov    0x3410(%rbp),%rdi
  bf848a:	mov    %r12,%rsi
  bf848d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf8492:	lea    0xec0(%rsp),%r14
  bf849a:	mov    %rax,%rsi
  bf849d:	mov    %r14,%rdi
  bf84a0:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf84a5:	lea    0xe10(%rsp),%rbx
  bf84ad:	mov    $0x5,%esi
  bf84b2:	movq   $0x20,0xe18(%rsp)
  bf84be:	movq   $0x0,0xe20(%rsp)
  bf84ca:	movq   $0x0,0xe30(%rsp)
  bf84d6:	mov    %rbx,%rdi
  bf84d9:	movq   $0x0,0xe28(%rsp)
  bf84e5:	movq   $0x0,0xeb8(%rsp)
  bf84f1:	movq   $0x0,0xe10(%rsp)
  bf84fd:	movl   $0x0,0xe38(%rsp)
  bf8508:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf850d:	cmpq   $0x20,0xe18(%rsp)
  bf8516:	lea    0x28(%rbx),%rdx
  bf851a:	jbe    bf8524 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x864>
  bf851c:	mov    0xeb8(%rsp),%rdx
  bf8524:	mov    $0xfd0c0d,%eax
  bf8529:	nopl   0x0(%rax)
  bf8530:	movzbl (%rax),%ecx
  bf8533:	add    $0x1,%rax
  bf8537:	mov    %ecx,(%rdx)
  bf8539:	add    $0x4,%rdx
  bf853d:	cmp    $0xfd0c12,%rax
  bf8543:	jne    bf8530 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x870>
  bf8545:	cmpq   $0x20,0xe18(%rsp)
  bf854e:	movq   $0x5,0xe10(%rsp)
  bf855a:	lea    0x3c(%rbx),%rax
  bf855e:	jbe    bf856c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x8ac>
  bf8560:	mov    0xeb8(%rsp),%rax
  bf8568:	add    $0x14,%rax
  bf856c:	movl   $0x0,(%rax)
  bf8572:	mov    0x40(%rsp),%rax
  bf8577:	mov    %r14,%rdx
  bf857a:	mov    %rbx,%rsi
  bf857d:	mov    0x2988(%rbp,%rax,8),%rdi
  bf8585:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf858a:	mov    %rbx,%rdi
  bf858d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8592:	mov    %r14,%rdi
  bf8595:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf859a:	mov    %r12,%rdi
  bf859d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf85a2:	movss  0x38(%rsp),%xmm0
  bf85a8:	cmpl   $0x1,0x3e0(%r13)
  bf85b0:	addss  0x30(%rsp),%xmm0
  bf85b6:	cvttss2si %xmm0,%eax
  bf85ba:	cvtsi2ss %eax,%xmm0
  bf85be:	addss  0x4c(%rsp),%xmm0
  bf85c4:	cvttss2si %xmm0,%r14
  bf85c9:	jbe    bf8646 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x986>
  bf85cb:	mov    0x40(%rsp),%rax
  bf85d0:	lea    0x15d0(%rsp),%rdi
  bf85d8:	mov    %r14d,%r14d
  bf85db:	mov    0x26f8(%rbp,%rax,8),%rsi
  bf85e3:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  bf85e8:	movss  0x2c(%rsp),%xmm2
  bf85ee:	mulss  0x15d8(%rsp),%xmm2
  bf85f7:	movss  0x2c(%rsp),%xmm0
  bf85fd:	movss  0x3ac20b(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  bf8605:	movss  0x3b00e7(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  bf860d:	cmpltss %xmm2,%xmm0
  bf8612:	andps  %xmm0,%xmm1
  bf8615:	andnps %xmm3,%xmm0
  bf8618:	orps   %xmm1,%xmm0
  bf861b:	cvtsi2ss %r14,%xmm1
  bf8620:	addss  %xmm2,%xmm0
  bf8624:	cvttss2si %xmm0,%eax
  bf8628:	cvtsi2ss %eax,%xmm0
  bf862c:	addss  0x15dc(%rsp),%xmm0
  bf8635:	mulss  0x3edee3(%rip),%xmm0        # fe6520 <_ZTV8CSubMenu+0x80>
  bf863d:	addss  %xmm0,%xmm1
  bf8641:	cvttss2si %xmm1,%r14
  bf8646:	mov    0x3f0(%r13),%r8d
  bf864d:	test   %r8d,%r8d
  bf8650:	je     bf8840 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xb80>
  bf8656:	mov    %r15d,%r15d
  bf8659:	mov    0x40(%rsp),%rax
  bf865e:	xor    %r12d,%r12d
  bf8661:	mov    %r15,0x38(%rsp)
  bf8666:	mov    0x40(%rsp),%r15
  bf866b:	add    $0x3bc,%rax
  bf8671:	mov    %rax,0x30(%rsp)
  bf8676:	add    $0x4de,%r15
  bf867d:	jmp    bf87cf <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xb0f>
  bf8682:	nopw   0x0(%rax,%rax,1)
  bf8688:	mov    0x3e8(%r13),%rax
  bf868f:	mov    (%rax),%rax
  bf8692:	mov    0x2c8(%rax),%rbx
  bf8699:	test   %rbx,%rbx
  bf869c:	je     bf87fd <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xb3d>
  bf86a2:	mov    0xb0(%rbx),%rdi
  bf86a9:	test   %rdi,%rdi
  bf86ac:	je     bf86b6 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x9f6>
  bf86ae:	mov    %rbx,%rsi
  bf86b1:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  bf86b6:	mov    0x30(%rbp),%rdi
  bf86ba:	mov    %rbx,%rsi
  bf86bd:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  bf86c2:	cvtsi2ssq 0x38(%rsp),%xmm0
  bf86c9:	mov    %r14d,%eax
  bf86cc:	movss  %xmm0,0x15c4(%rsp)
  bf86d5:	lea    0x15c0(%rsp),%rsi
  bf86dd:	cvtsi2ss %rax,%xmm0
  bf86e2:	mov    %rbx,%rdi
  bf86e5:	movl   $0x0,0x15c0(%rsp)
  bf86f0:	movl   $0x0,0x2c(%rsp)
  bf86f8:	movl   $0x0,0x15c8(%rsp)
  bf8703:	movss  %xmm0,0x15cc(%rsp)
  bf870c:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  bf8711:	mov    0x30(%rsp),%rax
  bf8716:	lea    0x15b0(%rsp),%rdi
  bf871e:	mov    0x8(%rbp,%rax,8),%rsi
  bf8723:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  bf8728:	lea    0x15b0(%rsp),%rsi
  bf8730:	mov    %rbx,%rdi
  bf8733:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  bf8738:	mov    %rbx,%rdi
  bf873b:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  bf8740:	movb   $0x1,0x3e2(%rbx)
  bf8747:	mov    0x8(%rbp,%r15,8),%rsi
  bf874c:	lea    0x15a0(%rsp),%rdi
  bf8754:	add    $0x1,%r12d
  bf8758:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  bf875d:	movss  0x2c(%rsp),%xmm2
  bf8763:	cmp    0x3f0(%r13),%r12d
  bf876a:	mulss  0x15a8(%rsp),%xmm2
  bf8773:	movss  0x2c(%rsp),%xmm0
  bf8779:	movss  0x3aff73(%rip),%xmm3        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  bf8781:	movss  0x3ac087(%rip),%xmm1        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  bf8789:	cmpltss %xmm2,%xmm0
  bf878e:	andps  %xmm0,%xmm1
  bf8791:	andnps %xmm3,%xmm0
  bf8794:	movss  0x15ac(%rsp),%xmm3
  bf879d:	orps   %xmm1,%xmm0
  bf87a0:	jae    bf8840 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xb80>
  bf87a6:	addss  %xmm2,%xmm0
  bf87aa:	mov    %r14d,%r14d
  bf87ad:	cvtsi2ss %r14,%xmm1
  bf87b2:	cvttss2si %xmm0,%eax
  bf87b6:	cvtsi2ss %eax,%xmm0
  bf87ba:	addss  %xmm3,%xmm0
  bf87be:	mulss  0x3ac06a(%rip),%xmm0        # fa4830 <_ZTVN4Ogre13FrameListenerE+0x70>
  bf87c6:	addss  %xmm0,%xmm1
  bf87ca:	cvttss2si %xmm1,%r14
  bf87cf:	cmp    %r12d,0x3f4(%r13)
  bf87d6:	jbe    bf8688 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x9c8>
  bf87dc:	mov    %r12d,%eax
  bf87df:	shl    $0x3,%rax
  bf87e3:	add    0x3e8(%r13),%rax
  bf87ea:	mov    (%rax),%rax
  bf87ed:	mov    0x2c8(%rax),%rbx
  bf87f4:	test   %rbx,%rbx
  bf87f7:	jne    bf86a2 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x9e2>
  bf87fd:	mov    0x70(%rbp),%rsi
  bf8801:	xor    %edx,%edx
  bf8803:	mov    %rax,%rdi
  bf8806:	mov    %rax,0x10(%rsp)
  bf880b:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  bf8810:	mov    0x10(%rsp),%rax
  bf8815:	mov    0x2c8(%rax),%rbx
  bf881c:	test   %rbx,%rbx
  bf881f:	je     bf8747 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xa87>
  bf8825:	lea    0x38(%rbx),%rdi
  bf8829:	mov    $0x1,%esi
  bf882e:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  bf8833:	movb   $0x1,0x3e2(%rbx)
  bf883a:	jmp    bf86a2 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x9e2>
  bf883f:	nop
  bf8840:	mov    0x0(%r13),%rax
  bf8844:	xor    %edx,%edx
  bf8846:	mov    0x58(%rbp),%rsi
  bf884a:	mov    %r13,%rdi
  bf884d:	call   *0x2f8(%rax)
  bf8853:	test   %al,%al
  bf8855:	je     bf8b20 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe60>
  bf885b:	mov    $0x36,%esi
  bf8860:	mov    %r13,%rdi
  bf8863:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  bf8868:	test   %al,%al
  bf886a:	je     bf8ed7 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1217>
  bf8870:	lea    0xc00(%rsp),%r12
  bf8878:	mov    $0xc,%esi
  bf887d:	movq   $0x20,0xc08(%rsp)
  bf8889:	movq   $0x0,0xc10(%rsp)
  bf8895:	movq   $0x0,0xc20(%rsp)
  bf88a1:	mov    %r12,%rdi
  bf88a4:	movq   $0x0,0xc18(%rsp)
  bf88b0:	movq   $0x0,0xca8(%rsp)
  bf88bc:	movq   $0x0,0xc00(%rsp)
  bf88c8:	movl   $0x0,0xc28(%rsp)
  bf88d3:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf88d8:	cmpq   $0x20,0xc08(%rsp)
  bf88e1:	lea    0x28(%r12),%rdx
  bf88e6:	ja     bf914c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x148c>
  bf88ec:	mov    $0xfe609b,%eax
  bf88f1:	nopl   0x0(%rax)
  bf88f8:	movzbl (%rax),%ecx
  bf88fb:	add    $0x1,%rax
  bf88ff:	mov    %ecx,(%rdx)
  bf8901:	add    $0x4,%rdx
  bf8905:	cmp    $0xfe60a7,%rax
  bf890b:	jne    bf88f8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xc38>
  bf890d:	cmpq   $0x20,0xc08(%rsp)
  bf8916:	movq   $0xc,0xc00(%rsp)
  bf8922:	lea    0x58(%r12),%rax
  bf8927:	ja     bf919e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14de>
  bf892d:	movl   $0x0,(%rax)
  bf8933:	mov    0x3410(%rbp),%rdi
  bf893a:	mov    %r12,%rsi
  bf893d:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf8942:	lea    0xb50(%rsp),%r14
  bf894a:	mov    %rax,%rsi
  bf894d:	mov    %r14,%rdi
  bf8950:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf8955:	lea    0xaa0(%rsp),%rbx
  bf895d:	mov    $0x5,%esi
  bf8962:	movq   $0x20,0xaa8(%rsp)
  bf896e:	movq   $0x0,0xab0(%rsp)
  bf897a:	movq   $0x0,0xac0(%rsp)
  bf8986:	mov    %rbx,%rdi
  bf8989:	movq   $0x0,0xab8(%rsp)
  bf8995:	movq   $0x0,0xb48(%rsp)
  bf89a1:	movq   $0x0,0xaa0(%rsp)
  bf89ad:	movl   $0x0,0xac8(%rsp)
  bf89b8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf89bd:	cmpq   $0x20,0xaa8(%rsp)
  bf89c6:	lea    0x28(%rbx),%rdx
  bf89ca:	ja     bf913f <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x147f>
  bf89d0:	mov    $0xfd0c0d,%eax
  bf89d5:	nopl   (%rax)
  bf89d8:	movzbl (%rax),%ecx
  bf89db:	add    $0x1,%rax
  bf89df:	mov    %ecx,(%rdx)
  bf89e1:	add    $0x4,%rdx
  bf89e5:	cmp    $0xfd0c12,%rax
  bf89eb:	jne    bf89d8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd18>
  bf89ed:	cmpq   $0x20,0xaa8(%rsp)
  bf89f6:	movq   $0x5,0xaa0(%rsp)
  bf8a02:	lea    0x3c(%rbx),%rax
  bf8a06:	ja     bf91c0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1500>
  bf8a0c:	movl   $0x0,(%rax)
  bf8a12:	mov    0x40(%rsp),%rax
  bf8a17:	mov    %r14,%rdx
  bf8a1a:	mov    %rbx,%rsi
  bf8a1d:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf8a25:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8a2a:	mov    %rbx,%rdi
  bf8a2d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8a32:	mov    %r14,%rdi
  bf8a35:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8a3a:	mov    %r12,%rdi
  bf8a3d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8a42:	mov    0x40(%rsp),%rax
  bf8a47:	mov    0x3138(%rbp,%rax,8),%rdi
  bf8a4f:	test   %rdi,%rdi
  bf8a52:	je     bf8b04 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  bf8a58:	cmpl   $0x1,0x238(%r13)
  bf8a60:	jle    bf8f82 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12c2>
  bf8a66:	mov    $0x1,%esi
  bf8a6b:	lea    0x1610(%rsp),%rbx
  bf8a73:	lea    0x1620(%rsp),%r12
  bf8a7b:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  bf8a80:	mov    0x238(%r13),%esi
  bf8a87:	mov    %rbx,%rdi
  bf8a8a:	call   c8e810 <_ZN7STRINGS16GetValueAsStringEi>
  bf8a8f:	mov    %rbx,%rdx
  bf8a92:	mov    $0x103f7f3,%esi
  bf8a97:	mov    %r12,%rdi
  bf8a9a:	call   56aee0 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_>
  bf8a9f:	mov    0x1610(%rsp),%rdi
  bf8aa7:	sub    $0x18,%rdi
  bf8aab:	cmp    $0x1423a20,%rdi
  bf8ab2:	jne    bf9392 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16d2>
  bf8ab8:	lea    0x50(%rsp),%rbx
  bf8abd:	mov    0x1620(%rsp),%rsi
  bf8ac5:	mov    %rbx,%rdi
  bf8ac8:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  bf8acd:	mov    0x40(%rsp),%rax
  bf8ad2:	mov    %rbx,%rsi
  bf8ad5:	mov    0x3138(%rbp,%rax,8),%rdi
  bf8add:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  bf8ae2:	mov    %rbx,%rdi
  bf8ae5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8aea:	mov    0x1620(%rsp),%rdi
  bf8af2:	mov    $0x1423a20,%eax
  bf8af7:	sub    $0x18,%rdi
  bf8afb:	cmp    %rdi,%rax
  bf8afe:	jne    bf93e9 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1729>
  bf8b04:	add    $0x1638,%rsp
  bf8b0b:	pop    %rbx
  bf8b0c:	pop    %rbp
  bf8b0d:	pop    %r12
  bf8b0f:	pop    %r13
  bf8b11:	pop    %r14
  bf8b13:	pop    %r15
  bf8b15:	ret
  bf8b16:	cs nopw 0x0(%rax,%rax,1)
  bf8b20:	mov    0x0(%r13),%rax
  bf8b24:	mov    %r13,%rdi
  bf8b27:	call   *0x2b0(%rax)
  bf8b2d:	test   %al,%al
  bf8b2f:	je     bf8d07 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1047>
  bf8b35:	lea    0x470(%rsp),%r12
  bf8b3d:	mov    $0xf,%esi
  bf8b42:	movq   $0x20,0x478(%rsp)
  bf8b4e:	movq   $0x0,0x480(%rsp)
  bf8b5a:	movq   $0x0,0x490(%rsp)
  bf8b66:	mov    %r12,%rdi
  bf8b69:	movq   $0x0,0x488(%rsp)
  bf8b75:	movq   $0x0,0x518(%rsp)
  bf8b81:	movq   $0x0,0x470(%rsp)
  bf8b8d:	movl   $0x0,0x498(%rsp)
  bf8b98:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8b9d:	cmpq   $0x20,0x478(%rsp)
  bf8ba6:	lea    0x28(%r12),%rdx
  bf8bab:	ja     bf9173 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14b3>
  bf8bb1:	mov    $0xfe60df,%eax
  bf8bb6:	cs nopw 0x0(%rax,%rax,1)
  bf8bc0:	movzbl (%rax),%ecx
  bf8bc3:	add    $0x1,%rax
  bf8bc7:	mov    %ecx,(%rdx)
  bf8bc9:	add    $0x4,%rdx
  bf8bcd:	cmp    $0xfe60ee,%rax
  bf8bd3:	jne    bf8bc0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xf00>
  bf8bd5:	cmpq   $0x20,0x478(%rsp)
  bf8bde:	movq   $0xf,0x470(%rsp)
  bf8bea:	lea    0x64(%r12),%rax
  bf8bef:	ja     bf91e2 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1522>
  bf8bf5:	movl   $0x0,(%rax)
  bf8bfb:	mov    0x3410(%rbp),%rdi
  bf8c02:	mov    %r12,%rsi
  bf8c05:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf8c0a:	lea    0x3c0(%rsp),%r14
  bf8c12:	mov    %rax,%rsi
  bf8c15:	mov    %r14,%rdi
  bf8c18:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf8c1d:	lea    0x310(%rsp),%rbx
  bf8c25:	mov    $0x5,%esi
  bf8c2a:	movq   $0x20,0x318(%rsp)
  bf8c36:	movq   $0x0,0x320(%rsp)
  bf8c42:	movq   $0x0,0x330(%rsp)
  bf8c4e:	mov    %rbx,%rdi
  bf8c51:	movq   $0x0,0x328(%rsp)
  bf8c5d:	movq   $0x0,0x3b8(%rsp)
  bf8c69:	movq   $0x0,0x310(%rsp)
  bf8c75:	movl   $0x0,0x338(%rsp)
  bf8c80:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8c85:	cmpq   $0x20,0x318(%rsp)
  bf8c8e:	lea    0x28(%rbx),%rdx
  bf8c92:	ja     bf9166 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14a6>
  bf8c98:	mov    $0xfd0c0d,%eax
  bf8c9d:	nopl   (%rax)
  bf8ca0:	movzbl (%rax),%ecx
  bf8ca3:	add    $0x1,%rax
  bf8ca7:	mov    %ecx,(%rdx)
  bf8ca9:	add    $0x4,%rdx
  bf8cad:	cmp    $0xfd0c12,%rax
  bf8cb3:	jne    bf8ca0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xfe0>
  bf8cb5:	cmpq   $0x20,0x318(%rsp)
  bf8cbe:	movq   $0x5,0x310(%rsp)
  bf8cca:	lea    0x3c(%rbx),%rax
  bf8cce:	ja     bf91f3 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1533>
  bf8cd4:	movl   $0x0,(%rax)
  bf8cda:	mov    0x40(%rsp),%rax
  bf8cdf:	mov    %r14,%rdx
  bf8ce2:	mov    %rbx,%rsi
  bf8ce5:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf8ced:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8cf2:	mov    %rbx,%rdi
  bf8cf5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8cfa:	mov    %r14,%rdi
  bf8cfd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8d02:	jmp    bf8a3a <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  bf8d07:	lea    0x260(%rsp),%r12
  bf8d0f:	mov    $0xb,%esi
  bf8d14:	movq   $0x20,0x268(%rsp)
  bf8d20:	movq   $0x0,0x270(%rsp)
  bf8d2c:	movq   $0x0,0x280(%rsp)
  bf8d38:	mov    %r12,%rdi
  bf8d3b:	movq   $0x0,0x278(%rsp)
  bf8d47:	movq   $0x0,0x308(%rsp)
  bf8d53:	movq   $0x0,0x260(%rsp)
  bf8d5f:	movl   $0x0,0x288(%rsp)
  bf8d6a:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8d6f:	cmpq   $0x20,0x268(%rsp)
  bf8d78:	lea    0x28(%r12),%rdx
  bf8d7d:	ja     bf9180 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14c0>
  bf8d83:	mov    $0xfe60e3,%eax
  bf8d88:	nopl   0x0(%rax,%rax,1)
  bf8d90:	movzbl (%rax),%ecx
  bf8d93:	add    $0x1,%rax
  bf8d97:	mov    %ecx,(%rdx)
  bf8d99:	add    $0x4,%rdx
  bf8d9d:	cmp    $0xfe60ee,%rax
  bf8da3:	jne    bf8d90 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x10d0>
  bf8da5:	cmpq   $0x20,0x268(%rsp)
  bf8dae:	movq   $0xb,0x260(%rsp)
  bf8dba:	lea    0x54(%r12),%rax
  bf8dbf:	ja     bf91d1 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1511>
  bf8dc5:	movl   $0x0,(%rax)
  bf8dcb:	mov    0x3410(%rbp),%rdi
  bf8dd2:	mov    %r12,%rsi
  bf8dd5:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf8dda:	lea    0x1b0(%rsp),%r14
  bf8de2:	mov    %rax,%rsi
  bf8de5:	mov    %r14,%rdi
  bf8de8:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf8ded:	lea    0x100(%rsp),%rbx
  bf8df5:	mov    $0x5,%esi
  bf8dfa:	movq   $0x20,0x108(%rsp)
  bf8e06:	movq   $0x0,0x110(%rsp)
  bf8e12:	movq   $0x0,0x120(%rsp)
  bf8e1e:	mov    %rbx,%rdi
  bf8e21:	movq   $0x0,0x118(%rsp)
  bf8e2d:	movq   $0x0,0x1a8(%rsp)
  bf8e39:	movq   $0x0,0x100(%rsp)
  bf8e45:	movl   $0x0,0x128(%rsp)
  bf8e50:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf8e55:	cmpq   $0x20,0x108(%rsp)
  bf8e5e:	lea    0x28(%rbx),%rdx
  bf8e62:	ja     bf9159 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1499>
  bf8e68:	mov    $0xfd0c0d,%eax
  bf8e6d:	nopl   (%rax)
  bf8e70:	movzbl (%rax),%ecx
  bf8e73:	add    $0x1,%rax
  bf8e77:	mov    %ecx,(%rdx)
  bf8e79:	add    $0x4,%rdx
  bf8e7d:	cmp    $0xfd0c12,%rax
  bf8e83:	jne    bf8e70 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x11b0>
  bf8e85:	cmpq   $0x20,0x108(%rsp)
  bf8e8e:	movq   $0x5,0x100(%rsp)
  bf8e9a:	lea    0x3c(%rbx),%rax
  bf8e9e:	ja     bf91af <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x14ef>
  bf8ea4:	movl   $0x0,(%rax)
  bf8eaa:	mov    0x40(%rsp),%rax
  bf8eaf:	mov    %r14,%rdx
  bf8eb2:	mov    %rbx,%rsi
  bf8eb5:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf8ebd:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8ec2:	mov    %rbx,%rdi
  bf8ec5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8eca:	mov    %r14,%rdi
  bf8ecd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8ed2:	jmp    bf8a3a <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  bf8ed7:	mov    0x0(%r13),%rax
  bf8edb:	mov    %r13,%rdi
  bf8ede:	call   *0x2b0(%rax)
  bf8ee4:	test   %al,%al
  bf8ee6:	je     bf8fc2 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1302>
  bf8eec:	mov    $0x37,%esi
  bf8ef1:	mov    %r13,%rdi
  bf8ef4:	call   7f62a0 <_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE>
  bf8ef9:	test   %al,%al
  bf8efb:	je     bf923c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x157c>
  bf8f01:	lea    0x9f0(%rsp),%r14
  bf8f09:	mov    $0xfe60a8,%esi
  bf8f0e:	mov    %r14,%rdi
  bf8f11:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf8f16:	mov    0x3410(%rbp),%rdi
  bf8f1d:	mov    %r14,%rsi
  bf8f20:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf8f25:	lea    0x940(%rsp),%r12
  bf8f2d:	mov    %rax,%rsi
  bf8f30:	mov    %r12,%rdi
  bf8f33:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf8f38:	lea    0x890(%rsp),%rbx
  bf8f40:	mov    $0xfd0c0d,%esi
  bf8f45:	mov    %rbx,%rdi
  bf8f48:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf8f4d:	mov    0x40(%rsp),%rax
  bf8f52:	mov    %r12,%rdx
  bf8f55:	mov    %rbx,%rsi
  bf8f58:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf8f60:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf8f65:	mov    %rbx,%rdi
  bf8f68:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8f6d:	mov    %r12,%rdi
  bf8f70:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8f75:	mov    %r14,%rdi
  bf8f78:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf8f7d:	jmp    bf8a42 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd82>
  bf8f82:	xor    %esi,%esi
  bf8f84:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  bf8f89:	jmp    bf8b04 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  bf8f8e:	mov    0x10c8(%rsp),%rax
  bf8f96:	jmp    bf82b4 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x5f4>
  bf8f9b:	mov    0x1438(%rsp),%rdx
  bf8fa3:	jmp    bf8018 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x358>
  bf8fa8:	mov    0x1598(%rsp),%rdx
  bf8fb0:	jmp    bf7f2d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x26d>
  bf8fb5:	mov    0x1178(%rsp),%rdx
  bf8fbd:	jmp    bf8336 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x676>
  bf8fc2:	lea    0x520(%rsp),%r12
  bf8fca:	xor    %esi,%esi
  bf8fcc:	movq   $0x20,0x528(%rsp)
  bf8fd8:	movq   $0x0,0x530(%rsp)
  bf8fe4:	movq   $0x0,0x540(%rsp)
  bf8ff0:	mov    %r12,%rdi
  bf8ff3:	movq   $0x0,0x538(%rsp)
  bf8fff:	movq   $0x0,0x5c8(%rsp)
  bf900b:	movq   $0x0,0x520(%rsp)
  bf9017:	movl   $0x0,0x548(%rsp)
  bf9022:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf9027:	cmpq   $0x20,0x528(%rsp)
  bf9030:	movq   $0x0,0x520(%rsp)
  bf903c:	lea    0x28(%r12),%rax
  bf9041:	jbe    bf904b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x138b>
  bf9043:	mov    0x5c8(%rsp),%rax
  bf904b:	lea    0x5d0(%rsp),%rbx
  bf9053:	movl   $0x0,(%rax)
  bf9059:	mov    $0x5,%esi
  bf905e:	movq   $0x20,0x5d8(%rsp)
  bf906a:	movq   $0x0,0x5e0(%rsp)
  bf9076:	mov    %rbx,%rdi
  bf9079:	movq   $0x0,0x5f0(%rsp)
  bf9085:	movq   $0x0,0x5e8(%rsp)
  bf9091:	movq   $0x0,0x678(%rsp)
  bf909d:	movq   $0x0,0x5d0(%rsp)
  bf90a9:	movl   $0x0,0x5f8(%rsp)
  bf90b4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  bf90b9:	cmpq   $0x20,0x5d8(%rsp)
  bf90c2:	lea    0x28(%rbx),%rdx
  bf90c6:	jbe    bf90d0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1410>
  bf90c8:	mov    0x678(%rsp),%rdx
  bf90d0:	mov    $0xfd0c0d,%eax
  bf90d5:	nopl   (%rax)
  bf90d8:	movzbl (%rax),%ecx
  bf90db:	add    $0x1,%rax
  bf90df:	mov    %ecx,(%rdx)
  bf90e1:	add    $0x4,%rdx
  bf90e5:	cmp    $0xfd0c12,%rax
  bf90eb:	jne    bf90d8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1418>
  bf90ed:	cmpq   $0x20,0x5d8(%rsp)
  bf90f6:	movq   $0x5,0x5d0(%rsp)
  bf9102:	lea    0x3c(%rbx),%rax
  bf9106:	jbe    bf9114 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1454>
  bf9108:	mov    0x678(%rsp),%rax
  bf9110:	add    $0x14,%rax
  bf9114:	movl   $0x0,(%rax)
  bf911a:	mov    0x40(%rsp),%rax
  bf911f:	mov    %r12,%rdx
  bf9122:	mov    %rbx,%rsi
  bf9125:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf912d:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf9132:	mov    %rbx,%rdi
  bf9135:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf913a:	jmp    bf8a3a <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd7a>
  bf913f:	mov    0xb48(%rsp),%rdx
  bf9147:	jmp    bf89d0 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd10>
  bf914c:	mov    0xca8(%rsp),%rdx
  bf9154:	jmp    bf88ec <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xc2c>
  bf9159:	mov    0x1a8(%rsp),%rdx
  bf9161:	jmp    bf8e68 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x11a8>
  bf9166:	mov    0x3b8(%rsp),%rdx
  bf916e:	jmp    bf8c98 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xfd8>
  bf9173:	mov    0x518(%rsp),%rdx
  bf917b:	jmp    bf8bb1 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xef1>
  bf9180:	mov    0x308(%rsp),%rdx
  bf9188:	jmp    bf8d83 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x10c3>
  bf918d:	mov    0x1178(%rsp),%rax
  bf9195:	add    $0x14,%rax
  bf9199:	jmp    bf8375 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x6b5>
  bf919e:	mov    0xca8(%rsp),%rax
  bf91a6:	add    $0x30,%rax
  bf91aa:	jmp    bf892d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xc6d>
  bf91af:	mov    0x1a8(%rsp),%rax
  bf91b7:	add    $0x14,%rax
  bf91bb:	jmp    bf8ea4 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x11e4>
  bf91c0:	mov    0xb48(%rsp),%rax
  bf91c8:	add    $0x14,%rax
  bf91cc:	jmp    bf8a0c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xd4c>
  bf91d1:	mov    0x308(%rsp),%rax
  bf91d9:	add    $0x2c,%rax
  bf91dd:	jmp    bf8dc5 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1105>
  bf91e2:	mov    0x518(%rsp),%rax
  bf91ea:	add    $0x3c,%rax
  bf91ee:	jmp    bf8bf5 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xf35>
  bf91f3:	mov    0x3b8(%rsp),%rax
  bf91fb:	add    $0x14,%rax
  bf91ff:	jmp    bf8cd4 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1014>
  bf9204:	mov    0x70(%rbp),%rsi
  bf9208:	xor    %edx,%edx
  bf920a:	mov    %r13,%rdi
  bf920d:	call   882e30 <_ZN10CEquipment10createIconER7CGameUIb>
  bf9212:	mov    0x2c8(%r13),%rbx
  bf9219:	test   %rbx,%rbx
  bf921c:	je     bf7e8b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1cb>
  bf9222:	lea    0x38(%rbx),%rdi
  bf9226:	mov    $0x1,%esi
  bf922b:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  bf9230:	movb   $0x1,0x3e2(%rbx)
  bf9237:	jmp    bf7da8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe8>
  bf923c:	lea    0x7e0(%rsp),%r14
  bf9244:	mov    $0xfe60b5,%esi
  bf9249:	mov    %r14,%rdi
  bf924c:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf9251:	mov    0x3410(%rbp),%rdi
  bf9258:	mov    %r14,%rsi
  bf925b:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf9260:	lea    0x730(%rsp),%r12
  bf9268:	mov    %rax,%rsi
  bf926b:	mov    %r12,%rdi
  bf926e:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf9273:	lea    0x680(%rsp),%rbx
  bf927b:	mov    $0xfd0c0d,%esi
  bf9280:	mov    %rbx,%rdi
  bf9283:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf9288:	mov    0x40(%rsp),%rax
  bf928d:	mov    %r12,%rdx
  bf9290:	mov    %rbx,%rsi
  bf9293:	mov    0x2c18(%rbp,%rax,8),%rdi
  bf929b:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf92a0:	mov    %rbx,%rdi
  bf92a3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf92a8:	mov    %r12,%rdi
  bf92ab:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf92b0:	jmp    bf8f75 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x12b5>
  bf92b5:	lea    0x12e0(%rsp),%r14
  bf92bd:	mov    $0xfe60d1,%esi
  bf92c2:	mov    %r14,%rdi
  bf92c5:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf92ca:	mov    0x3410(%rbp),%rdi
  bf92d1:	mov    %r14,%rsi
  bf92d4:	call   554ff8 <_ZNK5CEGUI8Imageset8getImageERKNS_6StringE@plt>
  bf92d9:	lea    0x1230(%rsp),%r12
  bf92e1:	mov    %rax,%rsi
  bf92e4:	mov    %r12,%rdi
  bf92e7:	call   554178 <_ZN5CEGUI14PropertyHelper13imageToStringEPKNS_5ImageE@plt>
  bf92ec:	lea    0x1180(%rsp),%rbx
  bf92f4:	mov    $0xfd0c0d,%esi
  bf92f9:	mov    %rbx,%rdi
  bf92fc:	call   899620 <_ZN5CEGUI6StringC1EPKc>
  bf9301:	mov    0x40(%rsp),%rax
  bf9306:	mov    %r12,%rdx
  bf9309:	mov    %rbx,%rsi
  bf930c:	mov    0x2ea8(%rbp,%rax,8),%rdi
  bf9314:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  bf9319:	mov    %rbx,%rdi
  bf931c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9321:	mov    %r12,%rdi
  bf9324:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9329:	mov    %r14,%rdi
  bf932c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9331:	jmp    bf8092 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x3d2>
  bf9336:	mov    %rbx,%rdi
  bf9339:	mov    %rax,%rbp
  bf933c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9341:	mov    %r12,%rdi
  bf9344:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9349:	mov    %r14,%rdi
  bf934c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9351:	mov    %rbp,%rdi
  bf9354:	call   554498 <_Unwind_Resume@plt>
  bf9359:	jmp    bf9336 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1676>
  bf935b:	mov    %rax,%rbp
  bf935e:	xchg   %ax,%ax
  bf9360:	jmp    bf9341 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1681>
  bf9362:	mov    %rax,%rbp
  bf9365:	jmp    bf9349 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1689>
  bf9367:	jmp    bf935b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x169b>
  bf9369:	nopl   0x0(%rax)
  bf9370:	jmp    bf9362 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16a2>
  bf9372:	mov    %rbx,%rdi
  bf9375:	mov    %rax,%rbp
  bf9378:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf937d:	mov    %r12,%rdi
  bf9380:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9385:	mov    %rbp,%rdi
  bf9388:	call   554498 <_Unwind_Resume@plt>
  bf938d:	mov    %rax,%rbp
  bf9390:	jmp    bf937d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16bd>
  bf9392:	mov    $0x5541c8,%eax
  bf9397:	test   %rax,%rax
  bf939a:	je     bf93d1 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1711>
  bf939c:	or     $0xffffffff,%eax
  bf939f:	lock xadd %eax,0x10(%rdi)
  bf93a4:	test   %eax,%eax
  bf93a6:	jg     bf8ab8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xdf8>
  bf93ac:	lea    0x162f(%rsp),%rsi
  bf93b4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  bf93b9:	jmp    bf8ab8 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xdf8>
  bf93be:	mov    %rax,%rbp
  bf93c1:	mov    %r12,%rdi
  bf93c4:	call   556288 <_ZNSsD1Ev@plt>
  bf93c9:	mov    %rbp,%rdi
  bf93cc:	call   554498 <_Unwind_Resume@plt>
  bf93d1:	mov    0x10(%rdi),%eax
  bf93d4:	lea    -0x1(%rax),%edx
  bf93d7:	mov    %edx,0x10(%rdi)
  bf93da:	jmp    bf93a4 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16e4>
  bf93dc:	mov    %rbx,%rdi
  bf93df:	mov    %rax,%rbp
  bf93e2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf93e7:	jmp    bf93c1 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1701>
  bf93e9:	mov    $0x5541c8,%eax
  bf93ee:	test   %rax,%rax
  bf93f1:	je     bf943c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x177c>
  bf93f3:	or     $0xffffffff,%eax
  bf93f6:	lock xadd %eax,0x10(%rdi)
  bf93fb:	test   %eax,%eax
  bf93fd:	jg     bf8b04 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  bf9403:	lea    0x162e(%rsp),%rsi
  bf940b:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  bf9410:	jmp    bf8b04 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0xe44>
  bf9415:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf941a:	nopw   0x0(%rax,%rax,1)
  bf9420:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf9425:	mov    %rax,%rbp
  bf9428:	mov    %r14,%rdi
  bf942b:	nopl   0x0(%rax,%rax,1)
  bf9430:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9435:	jmp    bf937d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16bd>
  bf943a:	jmp    bf9425 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  bf943c:	mov    0x10(%rdi),%eax
  bf943f:	lea    -0x1(%rax),%edx
  bf9442:	mov    %edx,0x10(%rdi)
  bf9445:	jmp    bf93fb <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x173b>
  bf9447:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf944c:	jmp    bf9425 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  bf944e:	mov    %rbx,%rdi
  bf9451:	mov    %rax,%rbp
  bf9454:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf9459:	jmp    bf9428 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1768>
  bf945b:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf9460:	jmp    bf944e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  bf9462:	mov    %rax,%rbp
  bf9465:	mov    %rbx,%rdi
  bf9468:	call   556288 <_ZNSsD1Ev@plt>
  bf946d:	mov    %rbp,%rdi
  bf9470:	call   554498 <_Unwind_Resume@plt>
  bf9475:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf947a:	jmp    bf9425 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  bf947c:	mov    %rax,%rdi
  bf947f:	nop
  bf9480:	call   554498 <_Unwind_Resume@plt>
  bf9485:	jmp    bf947c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  bf9487:	jmp    bf944e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  bf9489:	nopl   0x0(%rax)
  bf9490:	jmp    bf947c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  bf9492:	mov    %rax,%rbp
  bf9495:	mov    %rbx,%rdi
  bf9498:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf949d:	mov    %rbp,%rdi
  bf94a0:	call   554498 <_Unwind_Resume@plt>
  bf94a5:	jmp    bf947c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  bf94a7:	jmp    bf944e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  bf94a9:	mov    %r12,%rdi
  bf94ac:	mov    %rax,%rbp
  bf94af:	nop
  bf94b0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  bf94b5:	jmp    bf9495 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x17d5>
  bf94b7:	jmp    bf9372 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16b2>
  bf94bc:	nopl   0x0(%rax)
  bf94c0:	jmp    bf9425 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1765>
  bf94c5:	data16 cs nopw 0x0(%rax,%rax,1)
  bf94d0:	jmp    bf938d <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16cd>
  bf94d5:	data16 cs nopw 0x0(%rax,%rax,1)
  bf94e0:	jmp    bf947c <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x17bc>
  bf94e2:	jmp    bf944e <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x178e>
  bf94e7:	nopw   0x0(%rax,%rax,1)
  bf94f0:	jmp    bf9336 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x1676>
  bf94f5:	data16 cs nopw 0x0(%rax,%rax,1)
  bf9500:	jmp    bf935b <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x169b>
  bf9505:	data16 cs nopw 0x0(%rax,%rax,1)
  bf9510:	jmp    bf9362 <_ZN10CStashMenu14setPetSlotIconEP10CEquipmentii+0x16a2>
