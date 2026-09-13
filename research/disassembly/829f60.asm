
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000829f60 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)>:
  829f60:	mov    %rbx,-0x28(%rsp)
  829f65:	mov    %rbp,-0x20(%rsp)
  829f6a:	mov    %rsi,%rbp
  829f6d:	mov    %r12,-0x18(%rsp)
  829f72:	mov    %r14,-0x8(%rsp)
  829f77:	mov    %edx,%r14d
  829f7a:	mov    %r13,-0x10(%rsp)
  829f7f:	sub    $0x58,%rsp
  829f83:	mov    0x68(%rdi),%rdx
  829f87:	mov    (%rdi),%rax
  829f8a:	xor    %esi,%esi
  829f8c:	mov    %rdi,%rbx
  829f8f:	mov    %ecx,%r12d
  829f92:	movzbl 0x19b(%rdi),%r13d
  829f9a:	test   %rdx,%rdx
  829f9d:	mov    0x268(%rax),%rax
  829fa4:	je     829faa <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x4a>
  829fa6:	mov    0x18(%rdx),%rsi
  829faa:	mov    %rbx,%rdi
  829fad:	call   *%rax
  829faf:	mov    $0x1,%esi
  829fb4:	mov    %rbx,%rdi
  829fb7:	call   9e7080 <CPositionableObject::getPosition(bool)>
  829fbc:	movq   %xmm0,0x8(%rsp)
  829fc2:	mov    0x8(%rsp),%rax
  829fc7:	test   %r12b,%r12b
  829fca:	movss  %xmm1,0x18(%rsp)
  829fd0:	mov    %rax,0x10(%rsp)
  829fd5:	mov    %rax,0x20(%rsp)
  829fda:	mov    0x18(%rsp),%eax
  829fde:	mov    %eax,0x28(%rsp)
  829fe2:	jne    82a016 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0xb6>
  829fe4:	mov    0x68(%rbx),%rax
  829fe8:	xor    %edi,%edi
  829fea:	movzbl %r14b,%r14d
  829fee:	test   %rax,%rax
  829ff1:	je     829ff7 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x97>
  829ff3:	mov    0x18(%rax),%rdi
  829ff7:	mov    %r14d,%edx
  829ffa:	mov    %rbp,%rsi
  829ffd:	movq   0x20(%rsp),%xmm0
  82a003:	movss  0x28(%rsp),%xmm1
  82a009:	call   948240 <CLevel::passableBetween(Ogre::Vector3, Ogre::Vector3 const&, bool)>
  82a00e:	test   %al,%al
  82a010:	je     82a0d0 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x170>
  82a016:	mov    %rbp,%rsi
  82a019:	mov    %rbx,%rdi
  82a01c:	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  82a021:	mov    0x68(%rbx),%rax
  82a025:	xor    %esi,%esi
  82a027:	test   %rax,%rax
  82a02a:	je     82a030 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0xd0>
  82a02c:	mov    0x18(%rax),%rsi
  82a030:	movss  0x77e730(%rip),%xmm0        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  82a038:	movzbl %r12b,%edx
  82a03c:	mov    %rbx,%rdi
  82a03f:	mov    $0x1,%r14d
  82a045:	call   80feb0 <CCharacter::dropToGround(CLevel&, float, bool)>
  82a04a:	mov    (%rbx),%rax
  82a04d:	mov    %rbx,%rdi
  82a050:	call   *0x130(%rax)
  82a056:	movss  0x8(%rbp),%xmm0
  82a05b:	movss  0x0(%rbp),%xmm1
  82a060:	addss  0x8(%rax),%xmm0
  82a065:	addss  (%rax),%xmm1
  82a069:	movl   $0x0,0x22c(%rbx)
  82a073:	movss  %xmm0,0x230(%rbx)
  82a07b:	movss  %xmm1,0x228(%rbx)
  82a083:	test   %r13b,%r13b
  82a086:	je     82a0a6 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x146>
  82a088:	mov    0x68(%rbx),%rdx
  82a08c:	mov    (%rbx),%rax
  82a08f:	xor    %esi,%esi
  82a091:	test   %rdx,%rdx
  82a094:	mov    0x270(%rax),%rax
  82a09b:	je     82a0a1 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x141>
  82a09d:	mov    0x18(%rdx),%rsi
  82a0a1:	mov    %rbx,%rdi
  82a0a4:	call   *%rax
  82a0a6:	mov    %r14d,%eax
  82a0a9:	mov    0x30(%rsp),%rbx
  82a0ae:	mov    0x38(%rsp),%rbp
  82a0b3:	mov    0x40(%rsp),%r12
  82a0b8:	mov    0x48(%rsp),%r13
  82a0bd:	mov    0x50(%rsp),%r14
  82a0c2:	add    $0x58,%rsp
  82a0c6:	ret
  82a0c7:	nopw   0x0(%rax,%rax,1)
  82a0d0:	movss  0x4(%rbp),%xmm2
  82a0d5:	subss  0x24(%rsp),%xmm2
  82a0db:	movss  0x20(%rsp),%xmm5
  82a0e1:	movss  0x0(%rbp),%xmm3
  82a0e6:	subss  %xmm5,%xmm3
  82a0ea:	movss  0x8(%rbp),%xmm0
  82a0ef:	subss  0x28(%rsp),%xmm0
  82a0f5:	movaps %xmm3,%xmm1
  82a0f8:	movaps %xmm2,%xmm4
  82a0fb:	mulss  %xmm3,%xmm1
  82a0ff:	mulss  %xmm2,%xmm4
  82a103:	addss  %xmm4,%xmm1
  82a107:	movaps %xmm0,%xmm4
  82a10a:	mulss  %xmm0,%xmm4
  82a10e:	addss  %xmm4,%xmm1
  82a112:	sqrtss %xmm1,%xmm1
  82a116:	unpcklps %xmm1,%xmm1
  82a119:	cvtps2pd %xmm1,%xmm4
  82a11c:	ucomisd 0x77e67c(%rip),%xmm4        # fa87a0 <vtable for Ogre::SharedPtr<Ogre::Texture>+0x100>
  82a124:	jbe    82a13e <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x1de>
  82a126:	movss  0x77a6ce(%rip),%xmm4        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  82a12e:	divss  %xmm1,%xmm4
  82a132:	mulss  %xmm4,%xmm3
  82a136:	mulss  %xmm4,%xmm2
  82a13a:	mulss  %xmm4,%xmm0
  82a13e:	movss  0x77a6ea(%rip),%xmm1        # fa4830 <vtable for Ogre::FrameListener+0x70>
  82a146:	mov    0x68(%rbx),%rax
  82a14a:	mulss  %xmm1,%xmm2
  82a14e:	xor    %edi,%edi
  82a150:	mulss  %xmm1,%xmm3
  82a154:	test   %rax,%rax
  82a157:	addss  0x24(%rsp),%xmm2
  82a15d:	addss  %xmm5,%xmm3
  82a161:	movss  %xmm3,0x20(%rsp)
  82a167:	movss  %xmm2,0x24(%rsp)
  82a16d:	movss  0x28(%rsp),%xmm2
  82a173:	je     82a179 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x219>
  82a175:	mov    0x18(%rax),%rdi
  82a179:	mulss  %xmm0,%xmm1
  82a17d:	mov    %r14d,%edx
  82a180:	mov    %rbp,%rsi
  82a183:	movq   0x20(%rsp),%xmm0
  82a189:	xor    %r14d,%r14d
  82a18c:	addss  %xmm2,%xmm1
  82a190:	movss  %xmm1,0x28(%rsp)
  82a196:	call   948240 <CLevel::passableBetween(Ogre::Vector3, Ogre::Vector3 const&, bool)>
  82a19b:	test   %al,%al
  82a19d:	je     82a083 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0x123>
  82a1a3:	jmp    82a016 <CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)+0xb6>
