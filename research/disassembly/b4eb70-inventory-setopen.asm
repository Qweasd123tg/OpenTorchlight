
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b4eb70 <_ZN14CInventoryMenu7setOpenEb>:
  b4eb70:	mov    %rbx,-0x28(%rsp)
  b4eb75:	mov    %rbp,-0x20(%rsp)
  b4eb7a:	mov    %rdi,%rbx
  b4eb7d:	mov    %r12,-0x18(%rsp)
  b4eb82:	mov    %r13,-0x10(%rsp)
  b4eb87:	mov    %esi,%ebp
  b4eb89:	mov    %r14,-0x8(%rsp)
  b4eb8e:	sub    $0xc8,%rsp
  b4eb95:	cmpb   $0x0,0x60(%rdi)
  b4eb99:	je     b4ec50 <_ZN14CInventoryMenu7setOpenEb+0xe0>
  b4eb9f:	test   %sil,%sil
  b4eba2:	jne    b4ee64 <_ZN14CInventoryMenu7setOpenEb+0x2f4>
  b4eba8:	mov    0x91a0(%rdi),%rax
  b4ebaf:	test   %rax,%rax
  b4ebb2:	je     b4ebc9 <_ZN14CInventoryMenu7setOpenEb+0x59>
  b4ebb4:	mov    0x30(%rax),%rsi
  b4ebb8:	mov    0xb0(%rsi),%rdi
  b4ebbf:	test   %rdi,%rdi
  b4ebc2:	je     b4ebc9 <_ZN14CInventoryMenu7setOpenEb+0x59>
  b4ebc4:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b4ebc9:	xorps  %xmm1,%xmm1
  b4ebcc:	mov    0x9188(%rbx),%rdi
  b4ebd3:	xor    %edx,%edx
  b4ebd5:	mov    $0x42,%esi
  b4ebda:	xor    %ecx,%ecx
  b4ebdc:	lea    0x50(%rsp),%rbp
  b4ebe1:	movaps %xmm1,%xmm0
  b4ebe4:	call   a698a0 <_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb>
  b4ebe9:	lea    0x9b(%rsp),%rdx
  b4ebf1:	mov    $0xfe6008,%esi
  b4ebf6:	mov    %rbp,%rdi
  b4ebf9:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4ebfe:	mov    0x9170(%rbx),%rdi
  b4ec05:	movss  0x459b53(%rip),%xmm2        # fa8760 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xc0>
  b4ec0d:	movss  0x455c0f(%rip),%xmm1        # fa4824 <_ZTVN4Ogre13FrameListenerE+0x64>
  b4ec15:	xor    %edx,%edx
  b4ec17:	movss  0x455bed(%rip),%xmm0        # fa480c <_ZTVN4Ogre13FrameListenerE+0x4c>
  b4ec1f:	mov    %rbp,%rsi
  b4ec22:	call   8a71d0 <_ZN13CGenericModel14blendAnimationERKSsbfff>
  b4ec27:	mov    0x50(%rsp),%rdi
  b4ec2c:	sub    $0x18,%rdi
  b4ec30:	cmp    $0x1423a20,%rdi
  b4ec37:	jne    b4f114 <_ZN14CInventoryMenu7setOpenEb+0x5a4>
  b4ec3d:	movb   $0x0,0x61(%rbx)
  b4ec41:	movb   $0x0,0x60(%rbx)
  b4ec45:	jmp    b4ec59 <_ZN14CInventoryMenu7setOpenEb+0xe9>
  b4ec47:	nopw   0x0(%rax,%rax,1)
  b4ec50:	test   %sil,%sil
  b4ec53:	jne    b4ec90 <_ZN14CInventoryMenu7setOpenEb+0x120>
  b4ec55:	movb   $0x0,0x60(%rdi)
  b4ec59:	mov    0xa0(%rsp),%rbx
  b4ec61:	mov    0xa8(%rsp),%rbp
  b4ec69:	mov    0xb0(%rsp),%r12
  b4ec71:	mov    0xb8(%rsp),%r13
  b4ec79:	mov    0xc0(%rsp),%r14
  b4ec81:	add    $0xc8,%rsp
  b4ec88:	ret
  b4ec89:	nopl   0x0(%rax)
  b4ec90:	xorps  %xmm1,%xmm1
  b4ec93:	mov    0x9188(%rdi),%rdi
  b4ec9a:	xor    %edx,%edx
  b4ec9c:	xor    %ecx,%ecx
  b4ec9e:	mov    $0x16,%esi
  b4eca3:	lea    0x90(%rsp),%r12
  b4ecab:	movaps %xmm1,%xmm0
  b4ecae:	call   a698a0 <_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb>
  b4ecb3:	mov    0x68(%rbx),%rdi
  b4ecb7:	mov    0x9bc7a7(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  b4ecbd:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b4ecc2:	cvtsi2ss %eax,%xmm0
  b4ecc6:	mov    0x9bc79c(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  b4eccc:	movss  %xmm0,0x38(%rsp)
  b4ecd2:	mov    0x68(%rbx),%rdi
  b4ecd6:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b4ecdb:	cvtsi2ss %eax,%xmm6
  b4ecdf:	mov    $0x1,%esi
  b4ece4:	movss  %xmm6,0x3c(%rsp)
  b4ecea:	mov    0x9170(%rbx),%rdi
  b4ecf1:	mov    (%rdi),%rax
  b4ecf4:	call   *0x50(%rax)
  b4ecf7:	lea    0x9f(%rsp),%rdx
  b4ecff:	mov    $0xfe6008,%esi
  b4ed04:	mov    %r12,%rdi
  b4ed07:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4ed0c:	mov    0x9170(%rbx),%rdi
  b4ed13:	mov    %r12,%rsi
  b4ed16:	call   8a7860 <_ZNK13CGenericModel16animationPlayingERKSs>
  b4ed1b:	mov    0x90(%rsp),%rdi
  b4ed23:	sub    $0x18,%rdi
  b4ed27:	cmp    $0x1423a20,%rdi
  b4ed2e:	jne    b4f0db <_ZN14CInventoryMenu7setOpenEb+0x56b>
  b4ed34:	test   %al,%al
  b4ed36:	je     b4ee80 <_ZN14CInventoryMenu7setOpenEb+0x310>
  b4ed3c:	lea    0x80(%rsp),%r12
  b4ed44:	lea    0x9e(%rsp),%rdx
  b4ed4c:	mov    $0xfe600e,%esi
  b4ed51:	mov    %r12,%rdi
  b4ed54:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4ed59:	mov    0x9170(%rbx),%rdi
  b4ed60:	movss  0x4599f8(%rip),%xmm2        # fa8760 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xc0>
  b4ed68:	movss  0x455ab4(%rip),%xmm1        # fa4824 <_ZTVN4Ogre13FrameListenerE+0x64>
  b4ed70:	xor    %edx,%edx
  b4ed72:	movss  0x455a92(%rip),%xmm0        # fa480c <_ZTVN4Ogre13FrameListenerE+0x4c>
  b4ed7a:	mov    %r12,%rsi
  b4ed7d:	call   8a71d0 <_ZN13CGenericModel14blendAnimationERKSsbfff>
  b4ed82:	mov    %r12,%rdi
  b4ed85:	call   556288 <_ZNSsD1Ev@plt>
  b4ed8a:	lea    0x60(%rsp),%r12
  b4ed8f:	lea    0x9c(%rsp),%rdx
  b4ed97:	mov    $0xfc993a,%esi
  b4ed9c:	mov    %r12,%rdi
  b4ed9f:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4eda4:	mov    0x9170(%rbx),%rdi
  b4edab:	movss  0x455a49(%rip),%xmm1        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4edb3:	movss  0x455a51(%rip),%xmm0        # fa480c <_ZTVN4Ogre13FrameListenerE+0x4c>
  b4edbb:	mov    $0x1,%edx
  b4edc0:	mov    %r12,%rsi
  b4edc3:	call   8a42c0 <_ZN13CGenericModel19queueBlendAnimationERKSsbff>
  b4edc8:	mov    0x60(%rsp),%rdi
  b4edcd:	mov    $0x1423a20,%eax
  b4edd2:	sub    $0x18,%rdi
  b4edd6:	cmp    %rdi,%rax
  b4edd9:	jne    b4f0ab <_ZN14CInventoryMenu7setOpenEb+0x53b>
  b4eddf:	mov    0x20(%rbx),%rsi
  b4ede3:	mov    0x18(%rbx),%rdi
  b4ede7:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b4edec:	mov    0x20(%rbx),%rdi
  b4edf0:	call   553a38 <_ZN5CEGUI6Window10moveToBackEv@plt>
  b4edf5:	mov    0x9120(%rbx),%rdi
  b4edfc:	mov    $0x1,%esi
  b4ee01:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4ee06:	mov    0x9128(%rbx),%rdi
  b4ee0d:	xor    %esi,%esi
  b4ee0f:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4ee14:	mov    0x9130(%rbx),%rdi
  b4ee1b:	xor    %esi,%esi
  b4ee1d:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4ee22:	mov    0x9108(%rbx),%rdi
  b4ee29:	mov    $0x1,%esi
  b4ee2e:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4ee33:	mov    0x9110(%rbx),%rdi
  b4ee3a:	xor    %esi,%esi
  b4ee3c:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4ee41:	mov    0x9118(%rbx),%rdi
  b4ee48:	xor    %esi,%esi
  b4ee4a:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4ee4f:	cmpq   $0x0,0x9158(%rbx)
  b4ee57:	je     b4eec8 <_ZN14CInventoryMenu7setOpenEb+0x358>
  b4ee59:	mov    0x70(%rbx),%rdi
  b4ee5d:	xor    %esi,%esi
  b4ee5f:	call   a8f450 <_ZN7CGameUI8queueTipE11EContextTip>
  b4ee64:	mov    (%rbx),%rax
  b4ee67:	mov    %bpl,0x60(%rbx)
  b4ee6b:	mov    %rbx,%rdi
  b4ee6e:	call   *0x48(%rax)
  b4ee71:	jmp    b4ec59 <_ZN14CInventoryMenu7setOpenEb+0xe9>
  b4ee76:	cs nopw 0x0(%rax,%rax,1)
  b4ee80:	lea    0x70(%rsp),%r12
  b4ee85:	lea    0x9d(%rsp),%rdx
  b4ee8d:	mov    $0xfe600e,%esi
  b4ee92:	mov    %r12,%rdi
  b4ee95:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b4ee9a:	mov    0x9170(%rbx),%rdi
  b4eea1:	movss  0x4598b7(%rip),%xmm1        # fa8760 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0xc0>
  b4eea9:	movss  0x455973(%rip),%xmm0        # fa4824 <_ZTVN4Ogre13FrameListenerE+0x64>
  b4eeb1:	xor    %edx,%edx
  b4eeb3:	mov    %r12,%rsi
  b4eeb6:	call   8a5cf0 <_ZN13CGenericModel13playAnimationERKSsbff>
  b4eebb:	mov    %r12,%rdi
  b4eebe:	call   556288 <_ZNSsD1Ev@plt>
  b4eec3:	jmp    b4ed8a <_ZN14CInventoryMenu7setOpenEb+0x21a>
  b4eec8:	mov    0x9150(%rbx),%rdi
  b4eecf:	xorps  %xmm1,%xmm1
  b4eed2:	movss  0x455922(%rip),%xmm3        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4eeda:	mov    0x9148(%rbx),%rsi
  b4eee1:	movaps %xmm3,%xmm2
  b4eee4:	mov    $0x3,%edx
  b4eee9:	mov    (%rdi),%rax
  b4eeec:	movaps %xmm1,%xmm0
  b4eeef:	call   *0x48(%rax)
  b4eef2:	mov    0x70(%rbx),%rdi
  b4eef6:	mov    %rax,0x9158(%rbx)
  b4eefd:	mov    %rax,%r12
  b4ef00:	movss  0x9184(%rbx),%xmm4
  b4ef08:	movss  0x4a0e40(%rip),%xmm0        # fefd50 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x30>
  b4ef10:	movss  %xmm4,(%rsp)
  b4ef15:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4ef1a:	movss  (%rsp),%xmm4
  b4ef1f:	addss  %xmm0,%xmm4
  b4ef23:	mov    0x70(%rbx),%rdi
  b4ef27:	movss  0x4a0e25(%rip),%xmm0        # fefd54 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x34>
  b4ef2f:	divss  0x38(%rsp),%xmm4
  b4ef35:	movss  %xmm4,(%rsp)
  b4ef3a:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4ef3f:	movaps %xmm0,%xmm1
  b4ef42:	mov    0x70(%rbx),%rdi
  b4ef46:	movss  0x4a0e0a(%rip),%xmm0        # fefd58 <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x38>
  b4ef4e:	divss  0x3c(%rsp),%xmm1
  b4ef54:	movss  %xmm1,0x10(%rsp)
  b4ef5a:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4ef5f:	movaps %xmm0,%xmm5
  b4ef62:	mov    0x70(%rbx),%rdi
  b4ef66:	movss  0x4a0dee(%rip),%xmm0        # fefd5c <_ZTSN5CEGUI18MemberFunctionSlotI14CInventoryMenuEE+0x3c>
  b4ef6e:	divss  0x38(%rsp),%xmm5
  b4ef74:	movss  %xmm5,0x20(%rsp)
  b4ef7a:	call   a83e70 <_ZN7CGameUI7scaledYEf>
  b4ef7f:	movss  (%rsp),%xmm4
  b4ef84:	movaps %xmm4,%xmm2
  b4ef87:	movss  0x20(%rsp),%xmm5
  b4ef8d:	movaps %xmm0,%xmm3
  b4ef90:	addss  %xmm5,%xmm2
  b4ef94:	movss  0x455860(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b4ef9c:	divss  0x3c(%rsp),%xmm3
  b4efa2:	movss  0x10(%rsp),%xmm1
  b4efa8:	ucomiss %xmm0,%xmm2
  b4efab:	jbe    b4efb4 <_ZN14CInventoryMenu7setOpenEb+0x444>
  b4efad:	movaps %xmm0,%xmm5
  b4efb0:	subss  %xmm4,%xmm5
  b4efb4:	movaps %xmm1,%xmm2
  b4efb7:	addss  %xmm3,%xmm2
  b4efbb:	ucomiss %xmm0,%xmm2
  b4efbe:	jbe    b4efc7 <_ZN14CInventoryMenu7setOpenEb+0x457>
  b4efc0:	movaps %xmm0,%xmm3
  b4efc3:	subss  %xmm1,%xmm3
  b4efc7:	xorps  %xmm2,%xmm2
  b4efca:	movaps %xmm4,%xmm6
  b4efcd:	cmpnltss %xmm2,%xmm6
  b4efd2:	andps  %xmm6,%xmm4
  b4efd5:	movaps %xmm2,%xmm6
  b4efd8:	maxss  %xmm1,%xmm2
  b4efdc:	orps   %xmm4,%xmm6
  b4efdf:	movaps %xmm2,%xmm1
  b4efe2:	movaps %xmm0,%xmm2
  b4efe5:	movaps %xmm6,%xmm4
  b4efe8:	divss  0x38(%rsp),%xmm2
  b4efee:	ucomiss %xmm5,%xmm2
  b4eff1:	ja     b4f09f <_ZN14CInventoryMenu7setOpenEb+0x52f>
  b4eff7:	movaps %xmm5,%xmm2
  b4effa:	mov    0x9158(%rbx),%rdi
  b4f001:	movaps %xmm4,%xmm0
  b4f004:	call   552ba8 <_ZN4Ogre8Viewport13setDimensionsEffff@plt>
  b4f009:	movl   $0x0,0x40(%rsp)
  b4f011:	movl   $0x0,0x44(%rsp)
  b4f019:	lea    0x40(%rsp),%rsi
  b4f01e:	movl   $0x0,0x48(%rsp)
  b4f026:	movl   $0x3f800000,0x4c(%rsp)
  b4f02e:	mov    0x9158(%rbx),%rdi
  b4f035:	call   553c18 <_ZN4Ogre8Viewport19setBackgroundColourERKNS_11ColourValueE@plt>
  b4f03a:	mov    0x9158(%rbx),%rdi
  b4f041:	mov    $0x3,%edx
  b4f046:	mov    $0x1,%esi
  b4f04b:	call   553898 <_ZN4Ogre8Viewport18setClearEveryFrameEbj@plt>
  b4f050:	mov    0x9148(%rbx),%rax
  b4f057:	mov    %r12,%rdi
  b4f05a:	mov    (%rax),%rax
  b4f05d:	mov    0x278(%rax),%r13
  b4f064:	call   553978 <_ZNK4Ogre8Viewport14getActualWidthEv@plt>
  b4f069:	mov    %r12,%rdi
  b4f06c:	mov    %eax,%r14d
  b4f06f:	call   554968 <_ZNK4Ogre8Viewport15getActualHeightEv@plt>
  b4f074:	cvtsi2ss %r14d,%xmm0
  b4f079:	mov    0x9148(%rbx),%rdi
  b4f080:	cvtsi2ss %eax,%xmm1
  b4f084:	divss  %xmm1,%xmm0
  b4f088:	call   *%r13
  b4f08b:	mov    0x9148(%rbx),%rsi
  b4f092:	mov    %r12,%rdi
  b4f095:	call   555e18 <_ZN4Ogre8Viewport9setCameraEPNS_6CameraE@plt>
  b4f09a:	jmp    b4ee59 <_ZN14CInventoryMenu7setOpenEb+0x2e9>
  b4f09f:	movaps %xmm0,%xmm4
  b4f0a2:	subss  %xmm2,%xmm4
  b4f0a6:	jmp    b4effa <_ZN14CInventoryMenu7setOpenEb+0x48a>
  b4f0ab:	mov    $0x5541c8,%eax
  b4f0b0:	test   %rax,%rax
  b4f0b3:	je     b4f17e <_ZN14CInventoryMenu7setOpenEb+0x60e>
  b4f0b9:	or     $0xffffffff,%eax
  b4f0bc:	lock xadd %eax,0x10(%rdi)
  b4f0c1:	test   %eax,%eax
  b4f0c3:	jg     b4eddf <_ZN14CInventoryMenu7setOpenEb+0x26f>
  b4f0c9:	lea    0x99(%rsp),%rsi
  b4f0d1:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b4f0d6:	jmp    b4eddf <_ZN14CInventoryMenu7setOpenEb+0x26f>
  b4f0db:	mov    $0x5541c8,%edx
  b4f0e0:	test   %rdx,%rdx
  b4f0e3:	je     b4f194 <_ZN14CInventoryMenu7setOpenEb+0x624>
  b4f0e9:	or     $0xffffffff,%edx
  b4f0ec:	lock xadd %edx,0x10(%rdi)
  b4f0f1:	test   %edx,%edx
  b4f0f3:	jg     b4ed34 <_ZN14CInventoryMenu7setOpenEb+0x1c4>
  b4f0f9:	lea    0x9a(%rsp),%rsi
  b4f101:	mov    %al,0x30(%rsp)
  b4f105:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b4f10a:	movzbl 0x30(%rsp),%eax
  b4f10f:	jmp    b4ed34 <_ZN14CInventoryMenu7setOpenEb+0x1c4>
  b4f114:	mov    $0x5541c8,%eax
  b4f119:	test   %rax,%rax
  b4f11c:	je     b4f162 <_ZN14CInventoryMenu7setOpenEb+0x5f2>
  b4f11e:	or     $0xffffffff,%eax
  b4f121:	lock xadd %eax,0x10(%rdi)
  b4f126:	test   %eax,%eax
  b4f128:	jg     b4ec3d <_ZN14CInventoryMenu7setOpenEb+0xcd>
  b4f12e:	lea    0x98(%rsp),%rsi
  b4f136:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b4f13b:	jmp    b4ec3d <_ZN14CInventoryMenu7setOpenEb+0xcd>
  b4f140:	mov    %r12,%rdi
  b4f143:	mov    %rax,%rbx
  b4f146:	call   556288 <_ZNSsD1Ev@plt>
  b4f14b:	mov    %rbx,%rdi
  b4f14e:	call   554498 <_Unwind_Resume@plt>
  b4f153:	jmp    b4f140 <_ZN14CInventoryMenu7setOpenEb+0x5d0>
  b4f155:	mov    %rax,%rbx
  b4f158:	jmp    b4f14b <_ZN14CInventoryMenu7setOpenEb+0x5db>
  b4f15a:	nopw   0x0(%rax,%rax,1)
  b4f160:	jmp    b4f155 <_ZN14CInventoryMenu7setOpenEb+0x5e5>
  b4f162:	mov    0x10(%rdi),%eax
  b4f165:	lea    -0x1(%rax),%edx
  b4f168:	mov    %edx,0x10(%rdi)
  b4f16b:	jmp    b4f126 <_ZN14CInventoryMenu7setOpenEb+0x5b6>
  b4f16d:	jmp    b4f155 <_ZN14CInventoryMenu7setOpenEb+0x5e5>
  b4f16f:	mov    %rbp,%rdi
  b4f172:	mov    %rax,%rbx
  b4f175:	call   556288 <_ZNSsD1Ev@plt>
  b4f17a:	jmp    b4f14b <_ZN14CInventoryMenu7setOpenEb+0x5db>
  b4f17c:	jmp    b4f140 <_ZN14CInventoryMenu7setOpenEb+0x5d0>
  b4f17e:	mov    0x10(%rdi),%eax
  b4f181:	lea    -0x1(%rax),%edx
  b4f184:	mov    %edx,0x10(%rdi)
  b4f187:	jmp    b4f0c1 <_ZN14CInventoryMenu7setOpenEb+0x551>
  b4f18c:	jmp    b4f140 <_ZN14CInventoryMenu7setOpenEb+0x5d0>
  b4f18e:	xchg   %ax,%ax
  b4f190:	jmp    b4f155 <_ZN14CInventoryMenu7setOpenEb+0x5e5>
  b4f192:	jmp    b4f155 <_ZN14CInventoryMenu7setOpenEb+0x5e5>
  b4f194:	mov    0x10(%rdi),%edx
  b4f197:	lea    -0x1(%rdx),%ecx
  b4f19a:	mov    %ecx,0x10(%rdi)
  b4f19d:	jmp    b4f0f1 <_ZN14CInventoryMenu7setOpenEb+0x581>
  b4f1a2:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)

