
/workspace/scratch/3ba0fff8d310/otl-recovery-1518/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a06b30 <_ZN6CShape12updateVisualEbf>:
  a06b30:	push   %r15
  a06b32:	push   %r14
  a06b34:	push   %r13
  a06b36:	push   %r12
  a06b38:	push   %rbp
  a06b39:	mov    %esi,%ebp
  a06b3b:	push   %rbx
  a06b3c:	mov    %rdi,%rbx
  a06b3f:	sub    $0x228,%rsp
  a06b46:	movss  %xmm0,0x34(%rsp)
  a06b4c:	mov    0x148(%rdi),%rdi
  a06b53:	test   %rdi,%rdi
  a06b56:	je     a06f50 <_ZN6CShape12updateVisualEbf+0x420>
  a06b5c:	mov    (%rdi),%rax
  a06b5f:	xor    %esi,%esi
  a06b61:	call   *0x50(%rax)
  a06b64:	mov    0x150(%rbx),%rdi
  a06b6b:	xor    %esi,%esi
  a06b6d:	mov    (%rdi),%rax
  a06b70:	call   *0x50(%rax)
  a06b73:	mov    0x158(%rbx),%rdi
  a06b7a:	xor    %esi,%esi
  a06b7c:	mov    (%rdi),%rax
  a06b7f:	call   *0x50(%rax)
  a06b82:	mov    0x160(%rbx),%rdi
  a06b89:	xor    %esi,%esi
  a06b8b:	mov    (%rdi),%rax
  a06b8e:	call   *0x50(%rax)
  a06b91:	test   %bpl,%bpl
  a06b94:	jne    a06bb0 <_ZN6CShape12updateVisualEbf+0x80>
  a06b96:	add    $0x228,%rsp
  a06b9d:	pop    %rbx
  a06b9e:	pop    %rbp
  a06b9f:	pop    %r12
  a06ba1:	pop    %r13
  a06ba3:	pop    %r14
  a06ba5:	pop    %r15
  a06ba7:	ret
  a06ba8:	nopl   0x0(%rax,%rax,1)
  a06bb0:	mov    0x68(%rbx),%rdi
  a06bb4:	call   d6f4e0 <_ZN16CResourceManager18getEditorIsRunningEv>
  a06bb9:	test   %al,%al
  a06bbb:	jne    a078f8 <_ZN6CShape12updateVisualEbf+0xdc8>
  a06bc1:	mov    0x104(%rbx),%eax
  a06bc7:	cmp    $0x1,%eax
  a06bca:	je     a06c68 <_ZN6CShape12updateVisualEbf+0x138>
  a06bd0:	jb     a07590 <_ZN6CShape12updateVisualEbf+0xa60>
  a06bd6:	cmp    $0x2,%eax
  a06bd9:	je     a074f0 <_ZN6CShape12updateVisualEbf+0x9c0>
  a06bdf:	cmp    $0x4,%eax
  a06be2:	je     a06e9b <_ZN6CShape12updateVisualEbf+0x36b>
  a06be8:	mov    0x150(%rbx),%rdi
  a06bef:	mov    $0x1,%esi
  a06bf4:	mov    (%rdi),%rax
  a06bf7:	call   *0x50(%rax)
  a06bfa:	mov    0x150(%rbx),%rdi
  a06c01:	movss  0x5c7917(%rip),%xmm0        # fce520 <_ZTV18iInventoryListener+0xe0>
  a06c09:	mov    (%rdi),%rax
  a06c0c:	call   *0x90(%rax)
  a06c12:	mov    %rbx,%rdi
  a06c15:	mov    $0x1,%esi
  a06c1a:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  a06c1f:	movq   %xmm0,0x8(%rsp)
  a06c25:	mov    0x8(%rsp),%rax
  a06c2a:	lea    0xc0(%rsp),%rsi
  a06c32:	movss  %xmm1,0x48(%rsp)
  a06c38:	mov    %rax,0x40(%rsp)
  a06c3d:	mov    %rax,0xc0(%rsp)
  a06c45:	mov    0x48(%rsp),%eax
  a06c49:	mov    %eax,0xc8(%rsp)
  a06c50:	mov    0x150(%rbx),%rdi
  a06c57:	call   9e70e0 <_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E>
  a06c5c:	jmp    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a06c61:	nopl   0x0(%rax)
  a06c68:	mov    0x158(%rbx),%rdi
  a06c6f:	mov    $0x1,%esi
  a06c74:	mov    (%rdi),%rax
  a06c77:	call   *0x50(%rax)
  a06c7a:	lea    0xf0(%rsp),%rdx
  a06c82:	lea    0x100(%rsp),%rsi
  a06c8a:	mov    %rbx,%rdi
  a06c8d:	movss  0x34(%rsp),%xmm0
  a06c93:	movl   $0x0,0x100(%rsp)
  a06c9e:	movl   $0x0,0x104(%rsp)
  a06ca9:	movl   $0x0,0x108(%rsp)
  a06cb4:	movl   $0x0,0xf0(%rsp)
  a06cbf:	movl   $0x0,0xf4(%rsp)
  a06cca:	movl   $0x0,0xf8(%rsp)
  a06cd5:	call   a04e50 <_ZN6CShape21calculateLineSequmentEfRN4Ogre7Vector3ES2_>
  a06cda:	movss  0x100(%rsp),%xmm2
  a06ce3:	movss  0xf0(%rsp),%xmm3
  a06cec:	ucomiss %xmm3,%xmm2
  a06cef:	jp     a06cf7 <_ZN6CShape12updateVisualEbf+0x1c7>
  a06cf1:	je     a07918 <_ZN6CShape12updateVisualEbf+0xde8>
  a06cf7:	movss  0x108(%rsp),%xmm0
  a06d00:	movss  0xf8(%rsp),%xmm5
  a06d09:	movss  0x104(%rsp),%xmm1
  a06d12:	movss  0xf4(%rsp),%xmm4
  a06d1b:	subss  %xmm4,%xmm1
  a06d1f:	mov    0x158(%rbx),%rdi
  a06d26:	lea    0x70(%rsp),%rbp
  a06d2b:	subss  %xmm3,%xmm2
  a06d2f:	subss  %xmm5,%xmm0
  a06d33:	mov    (%rdi),%rax
  a06d36:	mulss  %xmm1,%xmm1
  a06d3a:	mulss  %xmm2,%xmm2
  a06d3e:	mulss  %xmm0,%xmm0
  a06d42:	addss  %xmm1,%xmm2
  a06d46:	movss  0x59daae(%rip),%xmm1        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  a06d4e:	addss  %xmm0,%xmm2
  a06d52:	movss  0x5c7782(%rip),%xmm0        # fce4dc <_ZTV18iInventoryListener+0x9c>
  a06d5a:	sqrtss %xmm2,%xmm2
  a06d5e:	call   *0x98(%rax)
  a06d64:	movss  0xf4(%rsp),%xmm1
  a06d6d:	subss  0x104(%rsp),%xmm1
  a06d76:	movss  0xf0(%rsp),%xmm0
  a06d7f:	subss  0x100(%rsp),%xmm0
  a06d88:	movss  %xmm1,0xf4(%rsp)
  a06d91:	movss  0xf8(%rsp),%xmm1
  a06d9a:	subss  0x108(%rsp),%xmm1
  a06da3:	movss  %xmm0,0xf0(%rsp)
  a06dac:	unpcklps %xmm0,%xmm0
  a06daf:	cvtps2pd %xmm0,%xmm0
  a06db2:	movss  %xmm1,0xf8(%rsp)
  a06dbb:	unpcklps %xmm1,%xmm1
  a06dbe:	cvtps2pd %xmm1,%xmm1
  a06dc1:	call   5533d8 <atan2@plt>
  a06dc6:	unpcklpd %xmm0,%xmm0
  a06dca:	lea    0x120(%rsp),%rsi
  a06dd2:	mov    $0x1424b34,%edx
  a06dd7:	mov    %rbp,%rdi
  a06dda:	cvtpd2ps %xmm0,%xmm0
  a06dde:	movss  %xmm0,0x120(%rsp)
  a06de7:	mov    0x158(%rbx),%rax
  a06dee:	mov    (%rax),%rax
  a06df1:	mov    0x108(%rax),%r12
  a06df8:	call   5541e8 <_ZN4Ogre10Quaternion13FromAngleAxisERKNS_6RadianERKNS_7Vector3E@plt>
  a06dfd:	mov    0x158(%rbx),%rdi
  a06e04:	mov    %rbp,%rsi
  a06e07:	call   *%r12
  a06e0a:	movss  0x59d9fe(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  a06e12:	lea    0x50(%rsp),%rsi
  a06e17:	movss  0xf4(%rsp),%xmm1
  a06e20:	mulss  %xmm0,%xmm1
  a06e24:	movss  0xf0(%rsp),%xmm3
  a06e2d:	movss  0xf8(%rsp),%xmm2
  a06e36:	mulss  %xmm0,%xmm3
  a06e3a:	mulss  %xmm0,%xmm2
  a06e3e:	movss  %xmm1,0xf4(%rsp)
  a06e47:	addss  0x104(%rsp),%xmm1
  a06e50:	movss  %xmm3,0xf0(%rsp)
  a06e59:	addss  0x100(%rsp),%xmm3
  a06e62:	movss  %xmm2,0xf8(%rsp)
  a06e6b:	addss  0x108(%rsp),%xmm2
  a06e74:	addss  %xmm0,%xmm1
  a06e78:	movss  %xmm3,0x50(%rsp)
  a06e7e:	movss  %xmm2,0x58(%rsp)
  a06e84:	movss  %xmm1,0x54(%rsp)
  a06e8a:	mov    0x158(%rbx),%rdi
  a06e91:	call   9e70e0 <_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E>
  a06e96:	jmp    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a06e9b:	mov    0x160(%rbx),%rdi
  a06ea2:	mov    $0x1,%esi
  a06ea7:	mov    (%rdi),%rax
  a06eaa:	call   *0x50(%rax)
  a06ead:	mov    %rbx,%rdi
  a06eb0:	mov    $0x1,%esi
  a06eb5:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  a06eba:	movq   %xmm0,0x8(%rsp)
  a06ec0:	mov    0x8(%rsp),%rax
  a06ec5:	lea    0x110(%rsp),%rsi
  a06ecd:	movss  %xmm1,0x48(%rsp)
  a06ed3:	mov    %rax,0x40(%rsp)
  a06ed8:	mov    %rax,0x110(%rsp)
  a06ee0:	mov    0x48(%rsp),%eax
  a06ee4:	mov    %eax,0x118(%rsp)
  a06eeb:	mov    0x160(%rbx),%rdi
  a06ef2:	call   9e70e0 <_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E>
  a06ef7:	mov    0x160(%rbx),%rax
  a06efe:	mov    0x58(%rbx),%rdi
  a06f02:	mov    (%rax),%rax
  a06f05:	mov    0x108(%rax),%rbp
  a06f0c:	mov    (%rdi),%rax
  a06f0f:	call   *0x1f8(%rax)
  a06f15:	mov    0x160(%rbx),%rdi
  a06f1c:	mov    %rax,%rsi
  a06f1f:	call   *%rbp
  a06f21:	mov    0x160(%rbx),%rdi
  a06f28:	movss  0x138(%rbx),%xmm0
  a06f30:	movss  0x140(%rbx),%xmm2
  a06f38:	movss  0x13c(%rbx),%xmm1
  a06f40:	mov    (%rdi),%rax
  a06f43:	call   *0x98(%rax)
  a06f49:	jmp    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a06f4e:	xchg   %ax,%ax
  a06f50:	mov    0x68(%rbx),%rax
  a06f54:	lea    0x1f0(%rsp),%r14
  a06f5c:	lea    0x21f(%rsp),%rdx
  a06f64:	mov    $0xfda888,%esi
  a06f69:	mov    %r14,%rdi
  a06f6c:	mov    0x10(%rax),%r15
  a06f70:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  a06f75:	lea    0x1e0(%rsp),%r13
  a06f7d:	mov    $0x14ab1a8,%esi
  a06f82:	mov    %r13,%rdi
  a06f85:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  a06f8a:	xor    %ecx,%ecx
  a06f8c:	xor    %edx,%edx
  a06f8e:	xor    %esi,%esi
  a06f90:	mov    $0x250,%edi
  a06f95:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  a06f9a:	mov    0x68(%rbx),%rsi
  a06f9e:	xor    %r9d,%r9d
  a06fa1:	mov    %r13,%r8
  a06fa4:	mov    %r14,%rcx
  a06fa7:	mov    %r15,%rdx
  a06faa:	mov    %rax,%rdi
  a06fad:	mov    %rax,%r12
  a06fb0:	call   8b0b30 <_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b>
  a06fb5:	mov    %r12,0x148(%rbx)
  a06fbc:	mov    0x1e0(%rsp),%rdi
  a06fc4:	mov    $0x1424540,%r12d
  a06fca:	sub    $0x18,%rdi
  a06fce:	cmp    %r12,%rdi
  a06fd1:	jne    a07a67 <_ZN6CShape12updateVisualEbf+0xf37>
  a06fd7:	mov    0x1f0(%rsp),%rdi
  a06fdf:	sub    $0x18,%rdi
  a06fe3:	cmp    %rdi,%r12
  a06fe6:	jne    a07a37 <_ZN6CShape12updateVisualEbf+0xf07>
  a06fec:	mov    0x148(%rbx),%rdi
  a06ff3:	mov    $0x8,%esi
  a06ff8:	lea    0x1d0(%rsp),%r14
  a07000:	call   899e20 <_ZN13CGenericModel12setQueryMaskEN14OGRE_UTILITIES10EQUERYMASKE>
  a07005:	lea    0x21e(%rsp),%rdx
  a0700d:	mov    $0x10177d4,%esi
  a07012:	mov    %r14,%rdi
  a07015:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  a0701a:	lea    0x1c0(%rsp),%r13
  a07022:	mov    %r14,%rsi
  a07025:	mov    %r13,%rdi
  a07028:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  a0702d:	mov    0x148(%rbx),%rax
  a07034:	xor    %esi,%esi
  a07036:	mov    0x60(%rax),%rdi
  a0703a:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a0703f:	mov    (%rax),%rdx
  a07042:	mov    %rax,%rdi
  a07045:	call   *0x10(%rdx)
  a07048:	mov    0x8(%rax),%rsi
  a0704c:	lea    0x50(%rsp),%rdi
  a07051:	mov    $0x1423540,%r8d
  a07057:	xor    %ecx,%ecx
  a07059:	mov    %r13,%rdx
  a0705c:	call   556448 <_ZNK4Ogre8Material5cloneERKSsbS2_@plt>
  a07061:	mov    0x1c0(%rsp),%rdi
  a07069:	sub    $0x18,%rdi
  a0706d:	cmp    $0x1423a20,%rdi
  a07074:	jne    a07bb7 <_ZN6CShape12updateVisualEbf+0x1087>
  a0707a:	mov    0x1d0(%rsp),%rdi
  a07082:	mov    $0x1423a20,%eax
  a07087:	sub    $0x18,%rdi
  a0708b:	cmp    %rdi,%rax
  a0708e:	jne    a07af7 <_ZN6CShape12updateVisualEbf+0xfc7>
  a07094:	mov    0x58(%rsp),%rdi
  a07099:	xor    %esi,%esi
  a0709b:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  a070a0:	xor    %esi,%esi
  a070a2:	mov    %rax,%rdi
  a070a5:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  a070aa:	movss  0x59d74a(%rip),%xmm2        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  a070b2:	mov    %rax,%rdi
  a070b5:	movaps %xmm2,%xmm1
  a070b8:	mov    %rax,%r13
  a070bb:	movaps %xmm2,%xmm0
  a070be:	call   554cd8 <_ZN4Ogre4Pass19setSelfIlluminationEfff@plt>
  a070c3:	lea    0xb0(%rsp),%rsi
  a070cb:	mov    %r13,%rdi
  a070ce:	movl   $0x3f800000,0xb0(%rsp)
  a070d9:	movl   $0x3f800000,0xb4(%rsp)
  a070e4:	movl   $0x3f800000,0xb8(%rsp)
  a070ef:	movl   $0x3e800000,0xbc(%rsp)
  a070fa:	call   556058 <_ZN4Ogre4Pass10setAmbientERKNS_11ColourValueE@plt>
  a070ff:	lea    0xa0(%rsp),%rsi
  a07107:	mov    %r13,%rdi
  a0710a:	movl   $0x3f800000,0xa0(%rsp)
  a07115:	movl   $0x3f800000,0xa4(%rsp)
  a07120:	movl   $0x3f800000,0xa8(%rsp)
  a0712b:	movl   $0x3e800000,0xac(%rsp)
  a07136:	call   555c58 <_ZN4Ogre4Pass10setDiffuseERKNS_11ColourValueE@plt>
  a0713b:	xor    %esi,%esi
  a0713d:	mov    %r13,%rdi
  a07140:	call   5544a8 <_ZN4Ogre4Pass20setDepthWriteEnabledEb@plt>
  a07145:	mov    0x58(%rsp),%rdi
  a0714a:	xor    %esi,%esi
  a0714c:	call   555e78 <_ZN4Ogre8Material16setSceneBlendingENS_14SceneBlendTypeE@plt>
  a07151:	mov    0x58(%rsp),%rdi
  a07156:	mov    (%rdi),%rax
  a07159:	call   *0xc8(%rax)
  a0715f:	mov    %rax,%r13
  a07162:	mov    0x148(%rbx),%rax
  a07169:	xor    %esi,%esi
  a0716b:	mov    0x60(%rax),%rdi
  a0716f:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a07174:	mov    %r13,%rsi
  a07177:	mov    %rax,%rdi
  a0717a:	call   552bc8 <_ZN4Ogre9SubEntity15setMaterialNameERKSs@plt>
  a0717f:	mov    0x148(%rbx),%rax
  a07186:	lea    0x1b0(%rsp),%r15
  a0718e:	lea    0x21d(%rsp),%rdx
  a07196:	mov    $0xfda938,%esi
  a0719b:	mov    %r15,%rdi
  a0719e:	mov    0x60(%rax),%rax
  a071a2:	movb   $0x0,0xc0(%rax)
  a071a9:	mov    0x68(%rbx),%rax
  a071ad:	mov    0x10(%rax),%rax
  a071b1:	mov    %rax,0x38(%rsp)
  a071b6:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  a071bb:	lea    0x1a0(%rsp),%r14
  a071c3:	mov    $0x14ab1a8,%esi
  a071c8:	mov    %r14,%rdi
  a071cb:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  a071d0:	xor    %ecx,%ecx
  a071d2:	xor    %edx,%edx
  a071d4:	xor    %esi,%esi
  a071d6:	mov    $0x250,%edi
  a071db:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  a071e0:	mov    0x68(%rbx),%rsi
  a071e4:	mov    0x38(%rsp),%rdx
  a071e9:	xor    %r9d,%r9d
  a071ec:	mov    %r14,%r8
  a071ef:	mov    %r15,%rcx
  a071f2:	mov    %rax,%rdi
  a071f5:	mov    %rax,%r13
  a071f8:	call   8b0b30 <_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b>
  a071fd:	mov    %r13,0x150(%rbx)
  a07204:	mov    0x1a0(%rsp),%rdi
  a0720c:	sub    $0x18,%rdi
  a07210:	cmp    %rdi,%r12
  a07213:	jne    a07c47 <_ZN6CShape12updateVisualEbf+0x1117>
  a07219:	mov    0x1b0(%rsp),%rdi
  a07221:	sub    $0x18,%rdi
  a07225:	cmp    %rdi,%r12
  a07228:	jne    a07be7 <_ZN6CShape12updateVisualEbf+0x10b7>
  a0722e:	mov    0x150(%rbx),%rdi
  a07235:	mov    $0x8,%esi
  a0723a:	call   899e20 <_ZN13CGenericModel12setQueryMaskEN14OGRE_UTILITIES10EQUERYMASKE>
  a0723f:	lea    0x190(%rsp),%r13
  a07247:	lea    0x21c(%rsp),%rdx
  a0724f:	mov    $0xfa056d,%esi
  a07254:	mov    %r13,%rdi
  a07257:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  a0725c:	mov    0x150(%rbx),%rax
  a07263:	mov    %r13,%rsi
  a07266:	mov    0x60(%rax),%rdi
  a0726a:	call   554648 <_ZN4Ogre6Entity15setMaterialNameERKSs@plt>
  a0726f:	mov    0x190(%rsp),%rdi
  a07277:	mov    $0x1423a20,%eax
  a0727c:	sub    $0x18,%rdi
  a07280:	cmp    %rdi,%rax
  a07283:	jne    a07b27 <_ZN6CShape12updateVisualEbf+0xff7>
  a07289:	mov    0x150(%rbx),%rax
  a07290:	lea    0x180(%rsp),%r15
  a07298:	lea    0x21b(%rsp),%rdx
  a072a0:	mov    $0xfda9c8,%esi
  a072a5:	mov    %r15,%rdi
  a072a8:	mov    0x60(%rax),%rax
  a072ac:	movb   $0x0,0xc0(%rax)
  a072b3:	mov    0x68(%rbx),%rax
  a072b7:	mov    0x10(%rax),%rax
  a072bb:	mov    %rax,0x38(%rsp)
  a072c0:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  a072c5:	lea    0x170(%rsp),%r14
  a072cd:	mov    $0x14ab1a8,%esi
  a072d2:	mov    %r14,%rdi
  a072d5:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  a072da:	xor    %ecx,%ecx
  a072dc:	xor    %edx,%edx
  a072de:	xor    %esi,%esi
  a072e0:	mov    $0x250,%edi
  a072e5:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  a072ea:	mov    0x68(%rbx),%rsi
  a072ee:	mov    0x38(%rsp),%rdx
  a072f3:	xor    %r9d,%r9d
  a072f6:	mov    %r14,%r8
  a072f9:	mov    %r15,%rcx
  a072fc:	mov    %rax,%rdi
  a072ff:	mov    %rax,%r13
  a07302:	call   8b0b30 <_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b>
  a07307:	mov    %r13,0x158(%rbx)
  a0730e:	mov    0x170(%rsp),%rdi
  a07316:	sub    $0x18,%rdi
  a0731a:	cmp    %rdi,%r12
  a0731d:	jne    a07b87 <_ZN6CShape12updateVisualEbf+0x1057>
  a07323:	mov    0x180(%rsp),%rdi
  a0732b:	sub    $0x18,%rdi
  a0732f:	cmp    %rdi,%r12
  a07332:	jne    a07c17 <_ZN6CShape12updateVisualEbf+0x10e7>
  a07338:	mov    0x158(%rbx),%rdi
  a0733f:	mov    $0x8,%esi
  a07344:	call   899e20 <_ZN13CGenericModel12setQueryMaskEN14OGRE_UTILITIES10EQUERYMASKE>
  a07349:	lea    0x160(%rsp),%r13
  a07351:	lea    0x21a(%rsp),%rdx
  a07359:	mov    $0xfa056d,%esi
  a0735e:	mov    %r13,%rdi
  a07361:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  a07366:	mov    0x158(%rbx),%rax
  a0736d:	mov    %r13,%rsi
  a07370:	mov    0x60(%rax),%rdi
  a07374:	call   554648 <_ZN4Ogre6Entity15setMaterialNameERKSs@plt>
  a07379:	mov    0x160(%rsp),%rdi
  a07381:	mov    $0x1423a20,%eax
  a07386:	sub    $0x18,%rdi
  a0738a:	cmp    %rdi,%rax
  a0738d:	jne    a07ac7 <_ZN6CShape12updateVisualEbf+0xf97>
  a07393:	mov    0x158(%rbx),%rax
  a0739a:	lea    0x150(%rsp),%r15
  a073a2:	lea    0x219(%rsp),%rdx
  a073aa:	mov    $0xfda9c8,%esi
  a073af:	mov    %r15,%rdi
  a073b2:	mov    0x60(%rax),%rax
  a073b6:	movb   $0x0,0xc0(%rax)
  a073bd:	mov    0x68(%rbx),%rax
  a073c1:	mov    0x10(%rax),%rax
  a073c5:	mov    %rax,0x38(%rsp)
  a073ca:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  a073cf:	lea    0x140(%rsp),%r14
  a073d7:	mov    $0x14ab1a8,%esi
  a073dc:	mov    %r14,%rdi
  a073df:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  a073e4:	xor    %ecx,%ecx
  a073e6:	xor    %edx,%edx
  a073e8:	xor    %esi,%esi
  a073ea:	mov    $0x250,%edi
  a073ef:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  a073f4:	mov    0x68(%rbx),%rsi
  a073f8:	mov    0x38(%rsp),%rdx
  a073fd:	xor    %r9d,%r9d
  a07400:	mov    %r14,%r8
  a07403:	mov    %r15,%rcx
  a07406:	mov    %rax,%rdi
  a07409:	mov    %rax,%r13
  a0740c:	call   8b0b30 <_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b>
  a07411:	mov    %r13,0x160(%rbx)
  a07418:	mov    0x140(%rsp),%rdi
  a07420:	sub    $0x18,%rdi
  a07424:	cmp    %rdi,%r12
  a07427:	jne    a07b57 <_ZN6CShape12updateVisualEbf+0x1027>
  a0742d:	mov    0x150(%rsp),%rdi
  a07435:	sub    $0x18,%rdi
  a07439:	cmp    %rdi,%r12
  a0743c:	jne    a07a97 <_ZN6CShape12updateVisualEbf+0xf67>
  a07442:	mov    0x160(%rbx),%rdi
  a07449:	mov    $0x8,%esi
  a0744e:	call   899e20 <_ZN13CGenericModel12setQueryMaskEN14OGRE_UTILITIES10EQUERYMASKE>
  a07453:	lea    0x130(%rsp),%r12
  a0745b:	lea    0x218(%rsp),%rdx
  a07463:	mov    $0xfa056d,%esi
  a07468:	mov    %r12,%rdi
  a0746b:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  a07470:	mov    0x160(%rbx),%rax
  a07477:	mov    %r12,%rsi
  a0747a:	mov    0x60(%rax),%rdi
  a0747e:	call   554648 <_ZN4Ogre6Entity15setMaterialNameERKSs@plt>
  a07483:	mov    0x130(%rsp),%rdi
  a0748b:	mov    $0x1423a20,%eax
  a07490:	sub    $0x18,%rdi
  a07494:	cmp    %rdi,%rax
  a07497:	jne    a07a07 <_ZN6CShape12updateVisualEbf+0xed7>
  a0749d:	mov    0x160(%rbx),%rax
  a074a4:	mov    0x60(%rax),%rax
  a074a8:	movb   $0x0,0xc0(%rax)
  a074af:	mov    0x60(%rsp),%rax
  a074b4:	movq   $0xfa4590,0x50(%rsp)
  a074bd:	test   %rax,%rax
  a074c0:	je     a074da <_ZN6CShape12updateVisualEbf+0x9aa>
  a074c2:	mov    (%rax),%edx
  a074c4:	sub    $0x1,%edx
  a074c7:	test   %edx,%edx
  a074c9:	mov    %edx,(%rax)
  a074cb:	jne    a074da <_ZN6CShape12updateVisualEbf+0x9aa>
  a074cd:	mov    0x50(%rsp),%rax
  a074d2:	lea    0x50(%rsp),%rdi
  a074d7:	call   *0x10(%rax)
  a074da:	mov    0x148(%rbx),%rdi
  a074e1:	jmp    a06b5c <_ZN6CShape12updateVisualEbf+0x2c>
  a074e6:	cs nopw 0x0(%rax,%rax,1)
  a074f0:	mov    0x150(%rbx),%rdi
  a074f7:	mov    $0x1,%esi
  a074fc:	mov    (%rdi),%rax
  a074ff:	call   *0x50(%rax)
  a07502:	mov    %rbx,%rdi
  a07505:	movss  0x34(%rsp),%xmm0
  a0750b:	call   a02bb0 <_ZN6CShape21getMaxRadiusAtPercentEf>
  a07510:	movss  0x59d2f4(%rip),%xmm1        # fa480c <_ZTVN4Ogre13FrameListenerE+0x4c>
  a07518:	mov    0x150(%rbx),%rdi
  a0751f:	movaps %xmm1,%xmm2
  a07522:	movaps %xmm0,%xmm3
  a07525:	cmpltss %xmm0,%xmm2
  a0752a:	mov    (%rdi),%rax
  a0752d:	movaps %xmm2,%xmm0
  a07530:	andps  %xmm2,%xmm3
  a07533:	andnps %xmm1,%xmm0
  a07536:	orps   %xmm3,%xmm0
  a07539:	call   *0x90(%rax)
  a0753f:	mov    %rbx,%rdi
  a07542:	mov    $0x1,%esi
  a07547:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  a0754c:	movq   %xmm0,0x8(%rsp)
  a07552:	mov    0x8(%rsp),%rax
  a07557:	lea    0xd0(%rsp),%rsi
  a0755f:	movss  %xmm1,0x48(%rsp)
  a07565:	mov    %rax,0x40(%rsp)
  a0756a:	mov    %rax,0xd0(%rsp)
  a07572:	mov    0x48(%rsp),%eax
  a07576:	mov    %eax,0xd8(%rsp)
  a0757d:	mov    0x150(%rbx),%rdi
  a07584:	call   9e70e0 <_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E>
  a07589:	jmp    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a0758e:	xchg   %ax,%ax
  a07590:	mov    0x148(%rbx),%rdi
  a07597:	mov    $0x1,%esi
  a0759c:	mov    (%rdi),%rax
  a0759f:	call   *0x50(%rax)
  a075a2:	mov    0x148(%rbx),%rax
  a075a9:	mov    %rbx,%rdi
  a075ac:	movss  0x34(%rsp),%xmm0
  a075b2:	mov    (%rax),%rax
  a075b5:	mov    0x90(%rax),%rbp
  a075bc:	call   a02bb0 <_ZN6CShape21getMaxRadiusAtPercentEf>
  a075c1:	movaps %xmm0,%xmm1
  a075c4:	mov    %rbx,%rdi
  a075c7:	movss  0x34(%rsp),%xmm0
  a075cd:	movss  %xmm1,0x10(%rsp)
  a075d3:	call   a02bf0 <_ZN6CShape21getMinRadiusAtPercentEf>
  a075d8:	movss  0x10(%rsp),%xmm1
  a075de:	maxss  %xmm0,%xmm1
  a075e2:	mov    0x148(%rbx),%rdi
  a075e9:	movaps %xmm1,%xmm0
  a075ec:	call   *%rbp
  a075ee:	mov    %rbx,%rdi
  a075f1:	movss  0x34(%rsp),%xmm0
  a075f7:	call   a02bb0 <_ZN6CShape21getMaxRadiusAtPercentEf>
  a075fc:	movaps %xmm0,%xmm1
  a075ff:	mov    %rbx,%rdi
  a07602:	movss  0x34(%rsp),%xmm0
  a07608:	movss  %xmm1,0x10(%rsp)
  a0760e:	call   a02bf0 <_ZN6CShape21getMinRadiusAtPercentEf>
  a07613:	movss  0x10(%rsp),%xmm1
  a07619:	mov    %rbx,%rdi
  a0761c:	minss  %xmm0,%xmm1
  a07620:	movss  0x34(%rsp),%xmm0
  a07626:	movss  %xmm1,0x10(%rsp)
  a0762c:	call   a02bb0 <_ZN6CShape21getMaxRadiusAtPercentEf>
  a07631:	movaps %xmm0,%xmm2
  a07634:	mov    %rbx,%rdi
  a07637:	movss  0x34(%rsp),%xmm0
  a0763d:	movss  %xmm2,0x20(%rsp)
  a07643:	call   a02bf0 <_ZN6CShape21getMinRadiusAtPercentEf>
  a07648:	movss  0x20(%rsp),%xmm2
  a0764e:	mov    %rbx,%rdi
  a07651:	maxss  %xmm0,%xmm2
  a07655:	movss  0x10(%rsp),%xmm1
  a0765b:	movss  0x5c6e79(%rip),%xmm0        # fce4dc <_ZTV18iInventoryListener+0x9c>
  a07663:	divss  %xmm2,%xmm1
  a07667:	movaps %xmm0,%xmm2
  a0766a:	cmpltss %xmm1,%xmm2
  a0766f:	movaps %xmm1,%xmm3
  a07672:	movaps %xmm2,%xmm1
  a07675:	andps  %xmm2,%xmm3
  a07678:	andnps %xmm0,%xmm1
  a0767b:	movss  0x34(%rsp),%xmm0
  a07681:	orps   %xmm3,%xmm1
  a07684:	movss  %xmm1,0x10(%rsp)
  a0768a:	call   a02c30 <_ZN6CShape26getAngleOfReleaseAtPercentEf>
  a0768f:	movss  %xmm0,0x38(%rsp)
  a07695:	mov    0x148(%rbx),%rax
  a0769c:	xor    %esi,%esi
  a0769e:	mov    0x60(%rax),%rdi
  a076a2:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a076a7:	test   %rax,%rax
  a076aa:	je     a077d0 <_ZN6CShape12updateVisualEbf+0xca0>
  a076b0:	mov    0x148(%rbx),%rax
  a076b7:	xor    %esi,%esi
  a076b9:	mov    0x60(%rax),%rdi
  a076bd:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a076c2:	mov    (%rax),%rdx
  a076c5:	mov    %rax,%rdi
  a076c8:	call   *0x10(%rdx)
  a076cb:	mov    0x8(%rax),%rdi
  a076cf:	xor    %esi,%esi
  a076d1:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  a076d6:	test   %rax,%rax
  a076d9:	je     a077d0 <_ZN6CShape12updateVisualEbf+0xca0>
  a076df:	mov    0x148(%rbx),%rax
  a076e6:	xor    %esi,%esi
  a076e8:	mov    0x60(%rax),%rdi
  a076ec:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a076f1:	mov    (%rax),%rdx
  a076f4:	mov    %rax,%rdi
  a076f7:	call   *0x10(%rdx)
  a076fa:	mov    0x8(%rax),%rdi
  a076fe:	xor    %esi,%esi
  a07700:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  a07705:	xor    %esi,%esi
  a07707:	mov    %rax,%rdi
  a0770a:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  a0770f:	test   %rax,%rax
  a07712:	je     a077d0 <_ZN6CShape12updateVisualEbf+0xca0>
  a07718:	mov    0x148(%rbx),%rax
  a0771f:	xor    %esi,%esi
  a07721:	mov    0x60(%rax),%rdi
  a07725:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a0772a:	mov    (%rax),%rdx
  a0772d:	mov    %rax,%rdi
  a07730:	call   *0x10(%rdx)
  a07733:	mov    0x8(%rax),%rdi
  a07737:	xor    %esi,%esi
  a07739:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  a0773e:	xor    %esi,%esi
  a07740:	mov    %rax,%rdi
  a07743:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  a07748:	mov    0xf0(%rax),%rdx
  a0774f:	sub    0xe8(%rax),%rdx
  a07756:	shr    $0x3,%rdx
  a0775a:	test   %dx,%dx
  a0775d:	je     a077d0 <_ZN6CShape12updateVisualEbf+0xca0>
  a0775f:	mov    0x148(%rbx),%rax
  a07766:	xor    %esi,%esi
  a07768:	mov    0x60(%rax),%rdi
  a0776c:	call   554238 <_ZNK4Ogre6Entity12getSubEntityEj@plt>
  a07771:	mov    (%rax),%rdx
  a07774:	mov    %rax,%rdi
  a07777:	call   *0x10(%rdx)
  a0777a:	mov    0x8(%rax),%rdi
  a0777e:	xor    %esi,%esi
  a07780:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  a07785:	xor    %esi,%esi
  a07787:	mov    %rax,%rdi
  a0778a:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  a0778f:	xor    %esi,%esi
  a07791:	mov    %rax,%rdi
  a07794:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  a07799:	movss  0x38(%rsp),%xmm0
  a0779f:	mov    %rax,%rdi
  a077a2:	divss  0x5d34de(%rip),%xmm0        # fdac88 <_ZTI6CShape+0x18>
  a077aa:	movss  0x10(%rsp),%xmm1
  a077b0:	mulss  0x5a0f3c(%rip),%xmm1        # fa86f4 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x54>
  a077b8:	addss  0x59d03c(%rip),%xmm0        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  a077c0:	mulss  0x59d048(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  a077c8:	call   553038 <_ZN4Ogre16TextureUnitState16setTextureScrollEff@plt>
  a077cd:	nopl   (%rax)
  a077d0:	mov    %rbx,%rdi
  a077d3:	movss  0x34(%rsp),%xmm0
  a077d9:	call   a02c60 <_ZN6CShape23getAngleOffsetAtPercentEf>
  a077de:	movaps %xmm0,%xmm1
  a077e1:	mov    0x148(%rbx),%rax
  a077e8:	movss  0x5a0f34(%rip),%xmm0        # fa8724 <_ZTVN4Ogre9SharedPtrINS_7TextureEEE+0x84>
  a077f0:	lea    0x90(%rsp),%rbp
  a077f8:	subss  %xmm1,%xmm0
  a077fc:	mov    (%rax),%rax
  a077ff:	subss  0x38(%rsp),%xmm0
  a07805:	mov    0x108(%rax),%r12
  a0780c:	call   554058 <_ZN4Ogre4Math19AngleUnitsToRadiansEf@plt>
  a07811:	lea    0x200(%rsp),%rsi
  a07819:	mov    $0x1424b34,%edx
  a0781e:	mov    %rbp,%rdi
  a07821:	movss  %xmm0,0x200(%rsp)
  a0782a:	call   5541e8 <_ZN4Ogre10Quaternion13FromAngleAxisERKNS_6RadianERKNS_7Vector3E@plt>
  a0782f:	mov    0x58(%rbx),%rdi
  a07833:	mov    (%rdi),%rax
  a07836:	call   *0x1f8(%rax)
  a0783c:	mov    %rbp,%rsi
  a0783f:	mov    %rax,%rdi
  a07842:	call   552bd8 <_ZNK4Ogre10QuaternionmlERKS0_@plt>
  a07847:	movq   %xmm0,0x8(%rsp)
  a0784d:	mov    0x8(%rsp),%rdx
  a07852:	lea    0x80(%rsp),%rsi
  a0785a:	movq   %xmm1,0x8(%rsp)
  a07860:	mov    0x8(%rsp),%rax
  a07865:	mov    %rdx,0x40(%rsp)
  a0786a:	mov    %rax,0x48(%rsp)
  a0786f:	mov    %rax,0x88(%rsp)
  a07877:	mov    %rdx,0x80(%rsp)
  a0787f:	mov    0x148(%rbx),%rdi
  a07886:	call   *%r12
  a07889:	mov    %rbx,%rdi
  a0788c:	mov    $0x1,%esi
  a07891:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  a07896:	movq   %xmm0,0x8(%rsp)
  a0789c:	mov    0x8(%rsp),%rax
  a078a1:	lea    0x120(%rsp),%rsi
  a078a9:	movss  0x5c6c6f(%rip),%xmm0        # fce520 <_ZTV18iInventoryListener+0xe0>
  a078b1:	movss  %xmm1,0x48(%rsp)
  a078b7:	mov    %rax,0x120(%rsp)
  a078bf:	mov    %rax,0x40(%rsp)
  a078c4:	addss  0x124(%rsp),%xmm0
  a078cd:	mov    0x48(%rsp),%eax
  a078d1:	mov    %eax,0x128(%rsp)
  a078d8:	movss  %xmm0,0x124(%rsp)
  a078e1:	mov    0x148(%rbx),%rdi
  a078e8:	call   9e70e0 <_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E>
  a078ed:	jmp    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a078f2:	nopw   0x0(%rax,%rax,1)
  a078f8:	mov    $0x8,%esi
  a078fd:	mov    %rbx,%rdi
  a07900:	call   71e6f0 <_ZN17CEditorBaseObject17HasBaseObjectFlagE18EEDITOROBJECT_FLAG>
  a07905:	test   %al,%al
  a07907:	jne    a06b96 <_ZN6CShape12updateVisualEbf+0x66>
  a0790d:	jmp    a06bc1 <_ZN6CShape12updateVisualEbf+0x91>
  a07912:	nopw   0x0(%rax,%rax,1)
  a07918:	movss  0x104(%rsp),%xmm1
  a07921:	movss  0xf4(%rsp),%xmm4
  a0792a:	ucomiss %xmm4,%xmm1
  a0792d:	jp     a079f0 <_ZN6CShape12updateVisualEbf+0xec0>
  a07933:	jne    a079f0 <_ZN6CShape12updateVisualEbf+0xec0>
  a07939:	movss  0x108(%rsp),%xmm0
  a07942:	movss  0xf8(%rsp),%xmm5
  a0794b:	ucomiss %xmm5,%xmm0
  a0794e:	jne    a06d1b <_ZN6CShape12updateVisualEbf+0x1eb>
  a07954:	jp     a06d1b <_ZN6CShape12updateVisualEbf+0x1eb>
  a0795a:	mov    $0x1,%esi
  a0795f:	mov    %rbx,%rdi
  a07962:	call   9e7080 <_ZN19CPositionableObject11getPositionEb>
  a07967:	movq   %xmm0,0x8(%rsp)
  a0796d:	mov    0x8(%rsp),%rax
  a07972:	movss  %xmm1,0x48(%rsp)
  a07978:	movss  0xf8(%rsp),%xmm5
  a07981:	mov    %rax,0xe0(%rsp)
  a07989:	mov    %rax,0x40(%rsp)
  a0798e:	mov    0x48(%rsp),%eax
  a07992:	movss  0xe0(%rsp),%xmm2
  a0799b:	movss  0xe4(%rsp),%xmm1
  a079a4:	mov    %eax,0xe8(%rsp)
  a079ab:	movss  %xmm2,0x100(%rsp)
  a079b4:	movss  0xe8(%rsp),%xmm0
  a079bd:	movss  %xmm1,0x104(%rsp)
  a079c6:	movss  %xmm0,0x108(%rsp)
  a079cf:	movss  0xf4(%rsp),%xmm4
  a079d8:	movss  0xf0(%rsp),%xmm3
  a079e1:	jmp    a06d1b <_ZN6CShape12updateVisualEbf+0x1eb>
  a079e6:	cs nopw 0x0(%rax,%rax,1)
  a079f0:	movss  0x108(%rsp),%xmm0
  a079f9:	movss  0xf8(%rsp),%xmm5
  a07a02:	jmp    a06d1b <_ZN6CShape12updateVisualEbf+0x1eb>
  a07a07:	mov    $0x5541c8,%eax
  a07a0c:	test   %rax,%rax
  a07a0f:	je     a07cb2 <_ZN6CShape12updateVisualEbf+0x1182>
  a07a15:	or     $0xffffffff,%eax
  a07a18:	lock xadd %eax,0x10(%rdi)
  a07a1d:	test   %eax,%eax
  a07a1f:	jg     a0749d <_ZN6CShape12updateVisualEbf+0x96d>
  a07a25:	lea    0x20b(%rsp),%rsi
  a07a2d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  a07a32:	jmp    a0749d <_ZN6CShape12updateVisualEbf+0x96d>
  a07a37:	mov    $0x5541c8,%eax
  a07a3c:	test   %rax,%rax
  a07a3f:	je     a07cc0 <_ZN6CShape12updateVisualEbf+0x1190>
  a07a45:	or     $0xffffffff,%eax
  a07a48:	lock xadd %eax,0x10(%rdi)
  a07a4d:	test   %eax,%eax
  a07a4f:	jg     a06fec <_ZN6CShape12updateVisualEbf+0x4bc>
  a07a55:	lea    0x216(%rsp),%rsi
  a07a5d:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07a62:	jmp    a06fec <_ZN6CShape12updateVisualEbf+0x4bc>
  a07a67:	mov    $0x5541c8,%eax
  a07a6c:	test   %rax,%rax
  a07a6f:	je     a07d16 <_ZN6CShape12updateVisualEbf+0x11e6>
  a07a75:	or     $0xffffffff,%eax
  a07a78:	lock xadd %eax,0x10(%rdi)
  a07a7d:	test   %eax,%eax
  a07a7f:	jg     a06fd7 <_ZN6CShape12updateVisualEbf+0x4a7>
  a07a85:	lea    0x217(%rsp),%rsi
  a07a8d:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07a92:	jmp    a06fd7 <_ZN6CShape12updateVisualEbf+0x4a7>
  a07a97:	mov    $0x5541c8,%eax
  a07a9c:	test   %rax,%rax
  a07a9f:	je     a07db5 <_ZN6CShape12updateVisualEbf+0x1285>
  a07aa5:	or     $0xffffffff,%eax
  a07aa8:	lock xadd %eax,0x10(%rdi)
  a07aad:	test   %eax,%eax
  a07aaf:	jg     a07442 <_ZN6CShape12updateVisualEbf+0x912>
  a07ab5:	lea    0x20c(%rsp),%rsi
  a07abd:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07ac2:	jmp    a07442 <_ZN6CShape12updateVisualEbf+0x912>
  a07ac7:	mov    $0x5541c8,%eax
  a07acc:	test   %rax,%rax
  a07acf:	je     a07d42 <_ZN6CShape12updateVisualEbf+0x1212>
  a07ad5:	or     $0xffffffff,%eax
  a07ad8:	lock xadd %eax,0x10(%rdi)
  a07add:	test   %eax,%eax
  a07adf:	jg     a07393 <_ZN6CShape12updateVisualEbf+0x863>
  a07ae5:	lea    0x20e(%rsp),%rsi
  a07aed:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  a07af2:	jmp    a07393 <_ZN6CShape12updateVisualEbf+0x863>
  a07af7:	mov    $0x5541c8,%eax
  a07afc:	test   %rax,%rax
  a07aff:	je     a07de5 <_ZN6CShape12updateVisualEbf+0x12b5>
  a07b05:	or     $0xffffffff,%eax
  a07b08:	lock xadd %eax,0x10(%rdi)
  a07b0d:	test   %eax,%eax
  a07b0f:	jg     a07094 <_ZN6CShape12updateVisualEbf+0x564>
  a07b15:	lea    0x214(%rsp),%rsi
  a07b1d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  a07b22:	jmp    a07094 <_ZN6CShape12updateVisualEbf+0x564>
  a07b27:	mov    $0x5541c8,%eax
  a07b2c:	test   %rax,%rax
  a07b2f:	je     a07d25 <_ZN6CShape12updateVisualEbf+0x11f5>
  a07b35:	or     $0xffffffff,%eax
  a07b38:	lock xadd %eax,0x10(%rdi)
  a07b3d:	test   %eax,%eax
  a07b3f:	jg     a07289 <_ZN6CShape12updateVisualEbf+0x759>
  a07b45:	lea    0x211(%rsp),%rsi
  a07b4d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  a07b52:	jmp    a07289 <_ZN6CShape12updateVisualEbf+0x759>
  a07b57:	mov    $0x5541c8,%eax
  a07b5c:	test   %rax,%rax
  a07b5f:	je     a07d95 <_ZN6CShape12updateVisualEbf+0x1265>
  a07b65:	or     $0xffffffff,%eax
  a07b68:	lock xadd %eax,0x10(%rdi)
  a07b6d:	test   %eax,%eax
  a07b6f:	jg     a0742d <_ZN6CShape12updateVisualEbf+0x8fd>
  a07b75:	lea    0x20d(%rsp),%rsi
  a07b7d:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07b82:	jmp    a0742d <_ZN6CShape12updateVisualEbf+0x8fd>
  a07b87:	mov    $0x5541c8,%eax
  a07b8c:	test   %rax,%rax
  a07b8f:	je     a07d77 <_ZN6CShape12updateVisualEbf+0x1247>
  a07b95:	or     $0xffffffff,%eax
  a07b98:	lock xadd %eax,0x10(%rdi)
  a07b9d:	test   %eax,%eax
  a07b9f:	jg     a07323 <_ZN6CShape12updateVisualEbf+0x7f3>
  a07ba5:	lea    0x210(%rsp),%rsi
  a07bad:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07bb2:	jmp    a07323 <_ZN6CShape12updateVisualEbf+0x7f3>
  a07bb7:	mov    $0x5541c8,%eax
  a07bbc:	test   %rax,%rax
  a07bbf:	je     a07dff <_ZN6CShape12updateVisualEbf+0x12cf>
  a07bc5:	or     $0xffffffff,%eax
  a07bc8:	lock xadd %eax,0x10(%rdi)
  a07bcd:	test   %eax,%eax
  a07bcf:	jg     a0707a <_ZN6CShape12updateVisualEbf+0x54a>
  a07bd5:	lea    0x215(%rsp),%rsi
  a07bdd:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  a07be2:	jmp    a0707a <_ZN6CShape12updateVisualEbf+0x54a>
  a07be7:	mov    $0x5541c8,%eax
  a07bec:	test   %rax,%rax
  a07bef:	je     a07dc8 <_ZN6CShape12updateVisualEbf+0x1298>
  a07bf5:	or     $0xffffffff,%eax
  a07bf8:	lock xadd %eax,0x10(%rdi)
  a07bfd:	test   %eax,%eax
  a07bff:	jg     a0722e <_ZN6CShape12updateVisualEbf+0x6fe>
  a07c05:	lea    0x212(%rsp),%rsi
  a07c0d:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07c12:	jmp    a0722e <_ZN6CShape12updateVisualEbf+0x6fe>
  a07c17:	mov    $0x5541c8,%eax
  a07c1c:	test   %rax,%rax
  a07c1f:	je     a07e0d <_ZN6CShape12updateVisualEbf+0x12dd>
  a07c25:	or     $0xffffffff,%eax
  a07c28:	lock xadd %eax,0x10(%rdi)
  a07c2d:	test   %eax,%eax
  a07c2f:	jg     a07338 <_ZN6CShape12updateVisualEbf+0x808>
  a07c35:	lea    0x20f(%rsp),%rsi
  a07c3d:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07c42:	jmp    a07338 <_ZN6CShape12updateVisualEbf+0x808>
  a07c47:	mov    $0x5541c8,%eax
  a07c4c:	test   %rax,%rax
  a07c4f:	je     a07c8b <_ZN6CShape12updateVisualEbf+0x115b>
  a07c51:	or     $0xffffffff,%eax
  a07c54:	lock xadd %eax,0x10(%rdi)
  a07c59:	test   %eax,%eax
  a07c5b:	jg     a07219 <_ZN6CShape12updateVisualEbf+0x6e9>
  a07c61:	lea    0x213(%rsp),%rsi
  a07c69:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  a07c6e:	jmp    a07219 <_ZN6CShape12updateVisualEbf+0x6e9>
  a07c73:	mov    %rax,%rbx
  a07c76:	mov    %r14,%rdi
  a07c79:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  a07c7e:	mov    %rbx,%rdi
  a07c81:	call   554498 <_Unwind_Resume@plt>
  a07c86:	mov    %rax,%rbx
  a07c89:	jmp    a07c7e <_ZN6CShape12updateVisualEbf+0x114e>
  a07c8b:	mov    0x10(%rdi),%eax
  a07c8e:	lea    -0x1(%rax),%edx
  a07c91:	mov    %edx,0x10(%rdi)
  a07c94:	jmp    a07c59 <_ZN6CShape12updateVisualEbf+0x1129>
  a07c96:	mov    %r12,%rdi
  a07c99:	mov    %rax,%rbx
  a07c9c:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  a07ca1:	mov    %r13,%rdi
  a07ca4:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  a07ca9:	jmp    a07c76 <_ZN6CShape12updateVisualEbf+0x1146>
  a07cab:	mov    %rax,%rbx
  a07cae:	xchg   %ax,%ax
  a07cb0:	jmp    a07ca1 <_ZN6CShape12updateVisualEbf+0x1171>
  a07cb2:	mov    0x10(%rdi),%eax
  a07cb5:	lea    -0x1(%rax),%edx
  a07cb8:	mov    %edx,0x10(%rdi)
  a07cbb:	jmp    a07a1d <_ZN6CShape12updateVisualEbf+0xeed>
  a07cc0:	mov    0x10(%rdi),%eax
  a07cc3:	lea    -0x1(%rax),%edx
  a07cc6:	mov    %edx,0x10(%rdi)
  a07cc9:	jmp    a07a4d <_ZN6CShape12updateVisualEbf+0xf1d>
  a07cce:	mov    %r13,%rdi
  a07cd1:	mov    %rax,%rbx
  a07cd4:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  a07cd9:	mov    %r14,%rdi
  a07cdc:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  a07ce1:	mov    %r15,%rdi
  a07ce4:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  a07ce9:	lea    0x50(%rsp),%rdi
  a07cee:	call   56b110 <_ZN4Ogre11MaterialPtrD1Ev>
  a07cf3:	jmp    a07c7e <_ZN6CShape12updateVisualEbf+0x114e>
  a07cf5:	mov    %rax,%rbx
  a07cf8:	jmp    a07cd9 <_ZN6CShape12updateVisualEbf+0x11a9>
  a07cfa:	mov    %rax,%rbx
  a07cfd:	nopl   (%rax)
  a07d00:	jmp    a07ce1 <_ZN6CShape12updateVisualEbf+0x11b1>
  a07d02:	mov    %rax,%rbx
  a07d05:	jmp    a07ce9 <_ZN6CShape12updateVisualEbf+0x11b9>
  a07d07:	mov    %r12,%rdi
  a07d0a:	mov    %rax,%rbx
  a07d0d:	call   556288 <_ZNSsD1Ev@plt>
  a07d12:	jmp    a07ce9 <_ZN6CShape12updateVisualEbf+0x11b9>
  a07d14:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07d16:	mov    0x10(%rdi),%eax
  a07d19:	lea    -0x1(%rax),%edx
  a07d1c:	mov    %edx,0x10(%rdi)
  a07d1f:	nop
  a07d20:	jmp    a07a7d <_ZN6CShape12updateVisualEbf+0xf4d>
  a07d25:	mov    0x10(%rdi),%eax
  a07d28:	lea    -0x1(%rax),%edx
  a07d2b:	mov    %edx,0x10(%rdi)
  a07d2e:	jmp    a07b3d <_ZN6CShape12updateVisualEbf+0x100d>
  a07d33:	jmp    a07cfa <_ZN6CShape12updateVisualEbf+0x11ca>
  a07d35:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07d37:	nopw   0x0(%rax,%rax,1)
  a07d40:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07d42:	mov    0x10(%rdi),%eax
  a07d45:	lea    -0x1(%rax),%edx
  a07d48:	mov    %edx,0x10(%rdi)
  a07d4b:	jmp    a07add <_ZN6CShape12updateVisualEbf+0xfad>
  a07d50:	mov    %rax,%rbx
  a07d53:	mov    %r14,%rdi
  a07d56:	call   556288 <_ZNSsD1Ev@plt>
  a07d5b:	jmp    a07c7e <_ZN6CShape12updateVisualEbf+0x114e>
  a07d60:	jmp    a07c86 <_ZN6CShape12updateVisualEbf+0x1156>
  a07d65:	mov    %r13,%rdi
  a07d68:	mov    %rax,%rbx
  a07d6b:	nopl   0x0(%rax,%rax,1)
  a07d70:	call   556288 <_ZNSsD1Ev@plt>
  a07d75:	jmp    a07d53 <_ZN6CShape12updateVisualEbf+0x1223>
  a07d77:	mov    0x10(%rdi),%eax
  a07d7a:	lea    -0x1(%rax),%edx
  a07d7d:	mov    %edx,0x10(%rdi)
  a07d80:	jmp    a07b9d <_ZN6CShape12updateVisualEbf+0x106d>
  a07d85:	jmp    a07cf5 <_ZN6CShape12updateVisualEbf+0x11c5>
  a07d8a:	jmp    a07cfa <_ZN6CShape12updateVisualEbf+0x11ca>
  a07d8f:	nop
  a07d90:	jmp    a07cce <_ZN6CShape12updateVisualEbf+0x119e>
  a07d95:	mov    0x10(%rdi),%eax
  a07d98:	lea    -0x1(%rax),%edx
  a07d9b:	mov    %edx,0x10(%rdi)
  a07d9e:	xchg   %ax,%ax
  a07da0:	jmp    a07b6d <_ZN6CShape12updateVisualEbf+0x103d>
  a07da5:	mov    %r13,%rdi
  a07da8:	mov    %rax,%rbx
  a07dab:	call   556288 <_ZNSsD1Ev@plt>
  a07db0:	jmp    a07ce9 <_ZN6CShape12updateVisualEbf+0x11b9>
  a07db5:	mov    0x10(%rdi),%eax
  a07db8:	lea    -0x1(%rax),%edx
  a07dbb:	mov    %edx,0x10(%rdi)
  a07dbe:	jmp    a07aad <_ZN6CShape12updateVisualEbf+0xf7d>
  a07dc3:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07dc8:	mov    0x10(%rdi),%eax
  a07dcb:	lea    -0x1(%rax),%edx
  a07dce:	mov    %edx,0x10(%rdi)
  a07dd1:	jmp    a07bfd <_ZN6CShape12updateVisualEbf+0x10cd>
  a07dd6:	jmp    a07da5 <_ZN6CShape12updateVisualEbf+0x1275>
  a07dd8:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07ddd:	nopl   (%rax)
  a07de0:	jmp    a07d02 <_ZN6CShape12updateVisualEbf+0x11d2>
  a07de5:	mov    0x10(%rdi),%eax
  a07de8:	lea    -0x1(%rax),%edx
  a07deb:	mov    %edx,0x10(%rdi)
  a07dee:	xchg   %ax,%ax
  a07df0:	jmp    a07b0d <_ZN6CShape12updateVisualEbf+0xfdd>
  a07df5:	jmp    a07cce <_ZN6CShape12updateVisualEbf+0x119e>
  a07dfa:	jmp    a07cf5 <_ZN6CShape12updateVisualEbf+0x11c5>
  a07dff:	mov    0x10(%rdi),%eax
  a07e02:	lea    -0x1(%rax),%edx
  a07e05:	mov    %edx,0x10(%rdi)
  a07e08:	jmp    a07bcd <_ZN6CShape12updateVisualEbf+0x109d>
  a07e0d:	mov    0x10(%rdi),%eax
  a07e10:	lea    -0x1(%rax),%edx
  a07e13:	mov    %edx,0x10(%rdi)
  a07e16:	jmp    a07c2d <_ZN6CShape12updateVisualEbf+0x10fd>
