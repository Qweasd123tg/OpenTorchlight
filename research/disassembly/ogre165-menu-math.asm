# Shipped OGRE 1.6.5; bounded source-contract review.
# SHA256 bef109bfdc1210ede92731ead4a2b3fae76a8905f10bac14d5fdb54ae5474c31


/home/qweasd123tg/Games/Torchlight/game/lib64/libOgreMain-1.6.5.so:     file format elf64-x86-64


Disassembly of section .text:

000000000023ca30 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)>:
  23ca30:	mov    %rbx,-0x30(%rsp)
  23ca35:	mov    %rbp,-0x28(%rsp)
  23ca3a:	lea    0xc(%rsi),%rbp
  23ca3e:	mov    %r12,-0x20(%rsp)
  23ca43:	mov    %r13,-0x18(%rsp)
  23ca48:	lea    0x18(%rsi),%r12
  23ca4c:	mov    %r14,-0x10(%rsp)
  23ca51:	mov    %r15,-0x8(%rsp)
  23ca56:	sub    $0x68,%rsp
  23ca5a:	movss  (%rsi),%xmm2
  23ca5e:	mov    %rdi,%rbx
  23ca61:	movaps %xmm2,%xmm0
  23ca64:	movss  0x4(%rbp),%xmm3
  23ca69:	addss  %xmm3,%xmm0
  23ca6d:	movss  0x8(%r12),%xmm1
  23ca74:	addss  %xmm1,%xmm0
  23ca78:	ucomiss 0x11ce91(%rip),%xmm0        # 359910 <typeinfo name for Ogre::ItemIdentityException+0x20>
  23ca7f:	ja     23cbe0 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x1b0>
  23ca85:	xor    %ebp,%ebp
  23ca87:	ucomiss %xmm2,%xmm3
  23ca8a:	seta   %bpl
  23ca8e:	lea    0x0(%rbp,%rbp,1),%rax
  23ca93:	lea    0x0(,%rbp,4),%r14
  23ca9b:	add    %rbp,%rax
  23ca9e:	lea    (%rsi,%rax,4),%rax
  23caa2:	ucomiss (%rax,%rbp,4),%xmm1
  23caa6:	ja     23cba8 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x178>
  23caac:	lea    0x12c21d(%rip),%rax        # 368cd0 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)::s_iNext>
  23cab3:	mov    (%rax,%rbp,8),%r12
  23cab7:	mov    (%rax,%r12,8),%r13
  23cabb:	lea    0x0(%rbp,%rbp,2),%rax
  23cac0:	lea    (%rsi,%rax,4),%r15
  23cac4:	lea    (%r12,%r12,2),%rax
  23cac8:	lea    (%rsi,%rax,4),%rdx
  23cacc:	movss  (%r15,%r14,1),%xmm0
  23cad2:	lea    0x0(%r13,%r13,2),%rax
  23cad7:	subss  (%rdx,%r12,4),%xmm0
  23cadd:	lea    (%rsi,%rax,4),%rax
  23cae1:	subss  (%rax,%r13,4),%xmm0
  23cae7:	addss  0x11d4e1(%rip),%xmm0        # 359fd0 <typeinfo name for Ogre::Any+0xc>
  23caef:	sqrtss %xmm0,%xmm1
  23caf3:	ucomiss %xmm1,%xmm1
  23caf6:	jp     23cbc0 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x190>
  23cafc:	jne    23cbc0 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x190>
  23cb02:	movaps %xmm1,%xmm2
  23cb05:	lea    0x4(%rbx),%rcx
  23cb09:	movss  0x11d65f(%rip),%xmm0        # 35a170 <typeinfo name for Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)3> >+0x50>
  23cb11:	mulss  %xmm0,%xmm2
  23cb15:	mov    %rcx,0x10(%rsp)
  23cb1a:	lea    0x8(%rbx),%rcx
  23cb1e:	divss  %xmm1,%xmm0
  23cb22:	mov    %rcx,0x18(%rsp)
  23cb27:	lea    0xc(%rbx),%rcx
  23cb2b:	mov    %rcx,0x20(%rsp)
  23cb30:	mov    0x10(%rsp,%rbp,8),%rcx
  23cb35:	movss  %xmm2,(%rcx)
  23cb39:	mov    0x10(%rsp,%r12,8),%rcx
  23cb3e:	movss  (%rax,%r12,4),%xmm1
  23cb44:	subss  (%rdx,%r13,4),%xmm1
  23cb4a:	mulss  %xmm0,%xmm1
  23cb4e:	movss  %xmm1,(%rbx)
  23cb52:	movss  (%rdx,%r14,1),%xmm1
  23cb58:	addss  (%r15,%r12,4),%xmm1
  23cb5e:	mov    0x10(%rsp,%r13,8),%rdx
  23cb63:	mulss  %xmm0,%xmm1
  23cb67:	movss  %xmm1,(%rcx)
  23cb6b:	movss  (%rax,%r14,1),%xmm1
  23cb71:	addss  (%r15,%r13,4),%xmm1
  23cb77:	mulss  %xmm0,%xmm1
  23cb7b:	movss  %xmm1,(%rdx)
  23cb7f:	mov    0x38(%rsp),%rbx
  23cb84:	mov    0x40(%rsp),%rbp
  23cb89:	mov    0x48(%rsp),%r12
  23cb8e:	mov    0x50(%rsp),%r13
  23cb93:	mov    0x58(%rsp),%r14
  23cb98:	mov    0x60(%rsp),%r15
  23cb9d:	add    $0x68,%rsp
  23cba1:	ret
  23cba2:	nopw   0x0(%rax,%rax,1)
  23cba8:	mov    $0x8,%r14d
  23cbae:	mov    $0x2,%ebp
  23cbb3:	jmp    23caac <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x7c>
  23cbb8:	nopl   0x0(%rax,%rax,1)
  23cbc0:	mov    %rax,0x8(%rsp)
  23cbc5:	mov    %rdx,(%rsp)
  23cbc9:	call   108fb8 <sqrtf@plt>
  23cbce:	mov    (%rsp),%rdx
  23cbd2:	movaps %xmm0,%xmm1
  23cbd5:	mov    0x8(%rsp),%rax
  23cbda:	jmp    23cb02 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0xd2>
  23cbdf:	nop
  23cbe0:	addss  0x11d3e8(%rip),%xmm0        # 359fd0 <typeinfo name for Ogre::Any+0xc>
  23cbe8:	sqrtss %xmm0,%xmm1
  23cbec:	ucomiss %xmm1,%xmm1
  23cbef:	jp     23cc50 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x220>
  23cbf1:	jne    23cc50 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x220>
  23cbf3:	movaps %xmm1,%xmm2
  23cbf6:	movss  0x11d572(%rip),%xmm0        # 35a170 <typeinfo name for Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)3> >+0x50>
  23cbfe:	mulss  %xmm0,%xmm2
  23cc02:	divss  %xmm1,%xmm0
  23cc06:	movss  %xmm2,(%rbx)
  23cc0a:	movss  0x4(%r12),%xmm1
  23cc11:	subss  0x8(%rbp),%xmm1
  23cc16:	mulss  %xmm0,%xmm1
  23cc1a:	movss  %xmm1,0x4(%rbx)
  23cc1f:	movss  0x8(%rsi),%xmm1
  23cc24:	subss  0x18(%rsi),%xmm1
  23cc29:	mulss  %xmm0,%xmm1
  23cc2d:	movss  %xmm1,0x8(%rbx)
  23cc32:	movss  0xc(%rsi),%xmm1
  23cc37:	subss  0x4(%rsi),%xmm1
  23cc3c:	mulss  %xmm0,%xmm1
  23cc40:	movss  %xmm1,0xc(%rbx)
  23cc45:	jmp    23cb7f <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x14f>
  23cc4a:	nopw   0x0(%rax,%rax,1)
  23cc50:	mov    %rsi,0x8(%rsp)
  23cc55:	call   108fb8 <sqrtf@plt>
  23cc5a:	mov    0x8(%rsp),%rsi
  23cc5f:	movaps %xmm0,%xmm1
  23cc62:	jmp    23cbf3 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)+0x1c3>
  23cc64:	data16 data16 cs nopw 0x0(%rax,%rax,1)

000000000023cc70 <Ogre::Quaternion::FromAxes(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&)>:
  23cc70:	sub    $0x38,%rsp
  23cc74:	mov    (%rsi),%r8d
  23cc77:	lea    0xc(%rsp),%r9
  23cc7c:	mov    %r8d,(%rsp)
  23cc80:	mov    0x4(%rsi),%r8d
  23cc84:	mov    %r8d,0xc(%rsp)
  23cc89:	mov    0x8(%rsi),%esi
  23cc8c:	lea    0x18(%rsp),%r8
  23cc91:	mov    %esi,0x18(%rsp)
  23cc95:	mov    (%rdx),%esi
  23cc97:	mov    %esi,0x4(%rsp)
  23cc9b:	mov    0x4(%rdx),%esi
  23cc9e:	mov    %esi,0x4(%r9)
  23cca2:	mov    0x8(%rdx),%edx
  23cca5:	mov    %rsp,%rsi
  23cca8:	mov    %edx,0x4(%r8)
  23ccac:	mov    (%rcx),%edx
  23ccae:	mov    %edx,0x8(%rsp)
  23ccb2:	mov    0x4(%rcx),%edx
  23ccb5:	mov    %edx,0x8(%r9)
  23ccb9:	mov    0x8(%rcx),%edx
  23ccbc:	mov    %edx,0x8(%r8)
  23ccc0:	call   104d78 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)@plt>
  23ccc5:	add    $0x38,%rsp
  23ccc9:	ret
  23ccca:	nopw   0x0(%rax,%rax,1)

000000000023ccd0 <Ogre::Quaternion::FromAxes(Ogre::Vector3 const*)>:
  23ccd0:	sub    $0x38,%rsp
  23ccd4:	lea    0xc(%rsp),%r8
  23ccd9:	mov    %rsp,%rax
  23ccdc:	mov    (%rsi),%edx
  23ccde:	mov    %edx,(%rax)
  23cce0:	mov    0x4(%rsi),%edx
  23cce3:	mov    %edx,0xc(%rax)
  23cce6:	mov    0x8(%rsi),%edx
  23cce9:	add    $0xc,%rsi
  23cced:	mov    %edx,0x18(%rax)
  23ccf0:	add    $0x4,%rax
  23ccf4:	cmp    %r8,%rax
  23ccf7:	jne    23ccdc <Ogre::Quaternion::FromAxes(Ogre::Vector3 const*)+0xc>
  23ccf9:	mov    %rsp,%rsi
  23ccfc:	call   104d78 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)@plt>
  23cd01:	add    $0x38,%rsp
  23cd05:	ret
  23cd06:	cs nopw 0x0(%rax,%rax,1)

000000000023cd10 <Ogre::Quaternion::Log() const>:
  23cd10:	sub    $0x58,%rsp
  23cd14:	movss  (%rdi),%xmm0
  23cd18:	movss  0x11d470(%rip),%xmm1        # 35a190 <typeinfo name for Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)3> >+0x70>
  23cd20:	movaps %xmm0,%xmm2
  23cd23:	andps  %xmm1,%xmm2
  23cd26:	ucomiss 0x11d2a3(%rip),%xmm2        # 359fd0 <typeinfo name for Ogre::Any+0xc>
  23cd2d:	jb     23cd70 <Ogre::Quaternion::Log() const+0x60>
  23cd2f:	movss  0x4(%rdi),%xmm1
  23cd34:	movss  0x8(%rdi),%xmm3
  23cd39:	movss  0xc(%rdi),%xmm2
  23cd3e:	movss  %xmm1,0x44(%rsp)
  23cd44:	movl   $0x0,0x40(%rsp)
  23cd4c:	movss  %xmm2,0x4c(%rsp)
  23cd52:	movss  %xmm3,0x48(%rsp)
  23cd58:	movq   0x40(%rsp),%xmm0
  23cd5e:	movq   0x48(%rsp),%xmm1
  23cd64:	add    $0x58,%rsp
  23cd68:	ret
  23cd69:	nopl   0x0(%rax)
  23cd70:	jp     23cd2f <Ogre::Quaternion::Log() const+0x1f>
  23cd72:	mov    %rdi,0x18(%rsp)
  23cd77:	movaps %xmm1,(%rsp)
  23cd7b:	call   105a98 <Ogre::Math::ACos(float)@plt>
  23cd80:	movaps %xmm0,%xmm2
  23cd83:	movss  %xmm2,0x20(%rsp)
  23cd89:	call   102358 <sinf@plt>
  23cd8e:	mov    0x18(%rsp),%rdi
  23cd93:	movaps (%rsp),%xmm1
  23cd97:	andps  %xmm0,%xmm1
  23cd9a:	movss  0x20(%rsp),%xmm2
  23cda0:	ucomiss 0x11d22d(%rip),%xmm1        # 359fd4 <typeinfo name for Ogre::Any+0x10>
  23cda7:	jb     23cd2f <Ogre::Quaternion::Log() const+0x1f>
  23cda9:	divss  %xmm0,%xmm2
  23cdad:	movss  0x4(%rdi),%xmm1
  23cdb2:	movss  0x8(%rdi),%xmm3
  23cdb7:	mulss  %xmm2,%xmm1
  23cdbb:	mulss  %xmm2,%xmm3
  23cdbf:	mulss  0xc(%rdi),%xmm2
  23cdc4:	jmp    23cd3e <Ogre::Quaternion::Log() const+0x2e>
  23cdc9:	nop
  23cdca:	nopw   0x0(%rax,%rax,1)

000000000023cdd0 <Ogre::Quaternion::equals(Ogre::Quaternion const&, Ogre::Radian const&) const>:
  23cdd0:	push   %rbx
  23cdd1:	mov    %rdx,%rbx
  23cdd4:	call   109878 <Ogre::Quaternion::Dot(Ogre::Quaternion const&) const@plt>
  23cdd9:	call   105a98 <Ogre::Math::ACos(float)@plt>
  23cdde:	movss  0x11d3aa(%rip),%xmm1        # 35a190 <typeinfo name for Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)3> >+0x70>
  23cde6:	movss  (%rbx),%xmm2
  23cdea:	andps  %xmm0,%xmm1
  23cded:	ucomiss %xmm1,%xmm2
  23cdf0:	jb     23ce00 <Ogre::Quaternion::equals(Ogre::Quaternion const&, Ogre::Radian const&) const+0x30>
  23cdf2:	mov    $0x1,%eax
  23cdf7:	pop    %rbx
  23cdf8:	ret
  23cdf9:	nopl   0x0(%rax)
  23ce00:	mov    0x3e3101(%rip),%rax        # 61ff08 <Ogre::Math::PI@@Base+0x2bc220>
  23ce07:	pop    %rbx
  23ce08:	movss  (%rax),%xmm1
  23ce0c:	jmp    109c18 <Ogre::Math::RealEqual(float, float, float)@plt>
  23ce11:	nop
  23ce12:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)


/home/qweasd123tg/Games/Torchlight/game/lib64/libOgreMain-1.6.5.so:     file format elf64-x86-64


Disassembly of section .text:

000000000023be90 <Ogre::Quaternion::zAxis() const>:
  23be90:	movss  0x4(%rdi),%xmm1
  23be95:	movss  0x8(%rdi),%xmm3
  23be9a:	movaps %xmm1,%xmm6
  23be9d:	movaps %xmm3,%xmm5
  23bea0:	movss  0xc(%rdi),%xmm0
  23bea5:	addss  %xmm1,%xmm6
  23bea9:	addss  %xmm3,%xmm5
  23bead:	movaps %xmm1,%xmm2
  23beb0:	addss  %xmm0,%xmm0
  23beb4:	movss  (%rdi),%xmm4
  23beb8:	movaps %xmm3,%xmm7
  23bebb:	mulss  %xmm6,%xmm2
  23bebf:	mulss  %xmm4,%xmm6
  23bec3:	mulss  %xmm0,%xmm3
  23bec7:	mulss  %xmm5,%xmm4
  23becb:	mulss  %xmm1,%xmm0
  23becf:	movss  0x11e0f9(%rip),%xmm1        # 359fd0 <typeinfo name for Ogre::Any+0xc>
  23bed7:	mulss  %xmm5,%xmm7
  23bedb:	subss  %xmm6,%xmm3
  23bedf:	addss  %xmm4,%xmm0
  23bee3:	addss  %xmm7,%xmm2
  23bee7:	movss  %xmm3,-0x14(%rsp)
  23beed:	movss  %xmm0,-0x18(%rsp)
  23bef3:	subss  %xmm2,%xmm1
  23bef7:	movq   -0x18(%rsp),%xmm0
  23befd:	ret
  23befe:	xchg   %ax,%ax


/home/qweasd123tg/Games/Torchlight/game/lib64/libOgreMain-1.6.5.so:     file format elf64-x86-64


Disassembly of section .text:

000000000023c710 <Ogre::Quaternion::normalise()>:
  23c710:	push   %rbx
  23c711:	mov    %rdi,%rbx
  23c714:	sub    $0x30,%rsp
  23c718:	call   1022c8 <Ogre::Quaternion::Norm() const@plt>
  23c71d:	sqrtss %xmm0,%xmm1
  23c721:	ucomiss %xmm1,%xmm1
  23c724:	movaps %xmm0,%xmm2
  23c727:	jp     23c72b <Ogre::Quaternion::normalise()+0x1b>
  23c729:	je     23c740 <Ogre::Quaternion::normalise()+0x30>
  23c72b:	movaps %xmm2,%xmm0
  23c72e:	movss  %xmm2,(%rsp)
  23c733:	call   108fb8 <sqrtf@plt>
  23c738:	movaps %xmm0,%xmm1
  23c73b:	movss  (%rsp),%xmm2
  23c740:	movss  0x11d888(%rip),%xmm0        # 359fd0 <typeinfo name for Ogre::Any+0xc>
  23c748:	mov    %rbx,%rdi
  23c74b:	divss  %xmm1,%xmm0
  23c74f:	movss  %xmm2,(%rsp)
  23c754:	call   103ad8 <Ogre::Quaternion::operator*(float) const@plt>
  23c759:	movq   %xmm0,0x20(%rsp)
  23c75f:	mov    0x20(%rsp),%eax
  23c763:	movq   %xmm1,0x28(%rsp)
  23c769:	movss  (%rsp),%xmm2
  23c76e:	mov    %eax,(%rbx)
  23c770:	movaps %xmm2,%xmm0
  23c773:	mov    0x24(%rsp),%eax
  23c777:	mov    %eax,0x4(%rbx)
  23c77a:	mov    0x28(%rsp),%eax
  23c77e:	mov    %eax,0x8(%rbx)
  23c781:	mov    0x2c(%rsp),%eax
  23c785:	mov    %eax,0xc(%rbx)
  23c788:	add    $0x30,%rsp
  23c78c:	pop    %rbx
  23c78d:	ret
  23c78e:	xchg   %ax,%ax


/home/qweasd123tg/Games/Torchlight/game/lib64/libOgreMain-1.6.5.so:     file format elf64-x86-64


Disassembly of section .text:

00000000001f9410 <Ogre::Node::setOrientation(Ogre::Quaternion const&)>:
  1f9410:	push   %rbx
  1f9411:	mov    (%rsi),%eax
  1f9413:	mov    %rdi,%rbx
  1f9416:	mov    %eax,0xd0(%rdi)
  1f941c:	mov    0x4(%rsi),%eax
  1f941f:	mov    %eax,0xd4(%rdi)
  1f9425:	mov    0x8(%rsi),%eax
  1f9428:	mov    %eax,0xd8(%rdi)
  1f942e:	mov    0xc(%rsi),%eax
  1f9431:	mov    %eax,0xdc(%rdi)
  1f9437:	lea    0xd0(%rdi),%rdi
  1f943e:	call   ff1a8 <Ogre::Quaternion::normalise()@plt>
  1f9443:	mov    (%rbx),%rax
  1f9446:	mov    %rbx,%rdi
  1f9449:	xor    %esi,%esi
  1f944b:	pop    %rbx
  1f944c:	mov    0x258(%rax),%rax
  1f9453:	jmp    *%rax


/home/qweasd123tg/Games/Torchlight/game/lib64/libOgreMain-1.6.5.so:     file format elf64-x86-64


Disassembly of section .text:

00000000001f9ad0 <Ogre::Node::updateFromParentImpl() const>:
  1f9ad0:	push   %rbp
  1f9ad1:	push   %rbx
  1f9ad2:	mov    %rdi,%rbx
  1f9ad5:	sub    $0x68,%rsp
  1f9ad9:	mov    0x58(%rdi),%rdi
  1f9add:	test   %rdi,%rdi
  1f9ae0:	je     1f9d10 <Ogre::Node::updateFromParentImpl() const+0x240>
  1f9ae6:	mov    (%rdi),%rax
  1f9ae9:	call   *0x1f8(%rax)
  1f9aef:	cmpb   $0x0,0xf8(%rbx)
  1f9af6:	mov    %rax,%rbp
  1f9af9:	jne    1f9c70 <Ogre::Node::updateFromParentImpl() const+0x1a0>
  1f9aff:	mov    0xd0(%rbx),%eax
  1f9b05:	mov    %eax,0x120(%rbx)
  1f9b0b:	mov    0xd4(%rbx),%eax
  1f9b11:	mov    %eax,0x124(%rbx)
  1f9b17:	mov    0xd8(%rbx),%eax
  1f9b1d:	mov    %eax,0x128(%rbx)
  1f9b23:	mov    0xdc(%rbx),%eax
  1f9b29:	mov    %eax,0x12c(%rbx)
  1f9b2f:	mov    0x58(%rbx),%rdi
  1f9b33:	mov    (%rdi),%rax
  1f9b36:	call   *0x208(%rax)
  1f9b3c:	cmpb   $0x0,0xf9(%rbx)
  1f9b43:	je     1f9ce0 <Ogre::Node::updateFromParentImpl() const+0x210>
  1f9b49:	movss  0x8(%rax),%xmm0
  1f9b4e:	movss  0x4(%rax),%xmm1
  1f9b53:	mulss  0xf4(%rbx),%xmm0
  1f9b5b:	movss  (%rax),%xmm2
  1f9b5f:	mulss  0xf0(%rbx),%xmm1
  1f9b67:	mulss  0xec(%rbx),%xmm2
  1f9b6f:	movss  %xmm0,0x144(%rbx)
  1f9b77:	movss  %xmm1,0x140(%rbx)
  1f9b7f:	movss  %xmm2,0x13c(%rbx)
  1f9b87:	movss  0x4(%rax),%xmm1
  1f9b8c:	lea    0x50(%rsp),%rsi
  1f9b91:	movss  (%rax),%xmm0
  1f9b95:	mulss  0xe4(%rbx),%xmm1
  1f9b9d:	movss  0x8(%rax),%xmm2
  1f9ba2:	mulss  0xe0(%rbx),%xmm0
  1f9baa:	mulss  0xe8(%rbx),%xmm2
  1f9bb2:	mov    %rbp,%rdi
  1f9bb5:	movss  %xmm1,0x54(%rsp)
  1f9bbb:	movss  %xmm0,0x50(%rsp)
  1f9bc1:	movss  %xmm2,0x58(%rsp)
  1f9bc7:	call   109fa8 <Ogre::Quaternion::operator*(Ogre::Vector3 const&) const@plt>
  1f9bcc:	movq   %xmm0,0x8(%rsp)
  1f9bd2:	mov    0x8(%rsp),%rax
  1f9bd7:	movss  %xmm1,0x18(%rsp)
  1f9bdd:	mov    0x58(%rbx),%rdi
  1f9be1:	mov    %rax,0x40(%rsp)
  1f9be6:	mov    %rax,0x10(%rsp)
  1f9beb:	mov    0x18(%rsp),%eax
  1f9bef:	mov    %eax,0x48(%rsp)
  1f9bf3:	mov    0x40(%rsp),%eax
  1f9bf7:	mov    %eax,0x130(%rbx)
  1f9bfd:	mov    0x44(%rsp),%eax
  1f9c01:	mov    %eax,0x134(%rbx)
  1f9c07:	mov    0x48(%rsp),%eax
  1f9c0b:	mov    %eax,0x138(%rbx)
  1f9c11:	mov    (%rdi),%rax
  1f9c14:	call   *0x200(%rax)
  1f9c1a:	movss  0x130(%rbx),%xmm0
  1f9c22:	addss  (%rax),%xmm0
  1f9c26:	movss  %xmm0,0x130(%rbx)
  1f9c2e:	movss  0x134(%rbx),%xmm0
  1f9c36:	addss  0x4(%rax),%xmm0
  1f9c3b:	movss  %xmm0,0x134(%rbx)
  1f9c43:	movss  0x138(%rbx),%xmm0
  1f9c4b:	addss  0x8(%rax),%xmm0
  1f9c50:	movss  %xmm0,0x138(%rbx)
  1f9c58:	movb   $0x1,0x1b0(%rbx)
  1f9c5f:	movb   $0x0,0xc0(%rbx)
  1f9c66:	add    $0x68,%rsp
  1f9c6a:	pop    %rbx
  1f9c6b:	pop    %rbp
  1f9c6c:	ret
  1f9c6d:	nopl   (%rax)
  1f9c70:	lea    0xd0(%rbx),%rsi
  1f9c77:	mov    %rax,%rdi
  1f9c7a:	call   fe968 <Ogre::Quaternion::operator*(Ogre::Quaternion const&) const@plt>
  1f9c7f:	movq   %xmm0,0x8(%rsp)
  1f9c85:	mov    0x8(%rsp),%rdx
  1f9c8a:	movq   %xmm1,0x8(%rsp)
  1f9c90:	mov    0x8(%rsp),%rax
  1f9c95:	mov    %rdx,0x30(%rsp)
  1f9c9a:	mov    %rax,0x38(%rsp)
  1f9c9f:	mov    %rax,0x28(%rsp)
  1f9ca4:	mov    0x30(%rsp),%eax
  1f9ca8:	mov    %rdx,0x20(%rsp)
  1f9cad:	mov    %eax,0x120(%rbx)
  1f9cb3:	mov    0x34(%rsp),%eax
  1f9cb7:	mov    %eax,0x124(%rbx)
  1f9cbd:	mov    0x38(%rsp),%eax
  1f9cc1:	mov    %eax,0x128(%rbx)
  1f9cc7:	mov    0x3c(%rsp),%eax
  1f9ccb:	mov    %eax,0x12c(%rbx)
  1f9cd1:	jmp    1f9b2f <Ogre::Node::updateFromParentImpl() const+0x5f>
  1f9cd6:	cs nopw 0x0(%rax,%rax,1)
  1f9ce0:	mov    0xec(%rbx),%edx
  1f9ce6:	mov    %edx,0x13c(%rbx)
  1f9cec:	mov    0xf0(%rbx),%edx
  1f9cf2:	mov    %edx,0x140(%rbx)
  1f9cf8:	mov    0xf4(%rbx),%edx
  1f9cfe:	mov    %edx,0x144(%rbx)
  1f9d04:	jmp    1f9b87 <Ogre::Node::updateFromParentImpl() const+0xb7>
  1f9d09:	nopl   0x0(%rax)
  1f9d10:	mov    0xd0(%rbx),%eax
  1f9d16:	mov    %eax,0x120(%rbx)
  1f9d1c:	mov    0xd4(%rbx),%eax
  1f9d22:	mov    %eax,0x124(%rbx)
  1f9d28:	mov    0xd8(%rbx),%eax
  1f9d2e:	mov    %eax,0x128(%rbx)
  1f9d34:	mov    0xdc(%rbx),%eax
  1f9d3a:	mov    %eax,0x12c(%rbx)
  1f9d40:	mov    0xe0(%rbx),%eax
  1f9d46:	mov    %eax,0x130(%rbx)
  1f9d4c:	mov    0xe4(%rbx),%eax
  1f9d52:	mov    %eax,0x134(%rbx)
  1f9d58:	mov    0xe8(%rbx),%eax
  1f9d5e:	mov    %eax,0x138(%rbx)
  1f9d64:	mov    0xec(%rbx),%eax
  1f9d6a:	mov    %eax,0x13c(%rbx)
  1f9d70:	mov    0xf0(%rbx),%eax
  1f9d76:	mov    %eax,0x140(%rbx)
  1f9d7c:	mov    0xf4(%rbx),%eax
  1f9d82:	mov    %eax,0x144(%rbx)
  1f9d88:	jmp    1f9c58 <Ogre::Node::updateFromParentImpl() const+0x188>
  1f9d8d:	nop
  1f9d8e:	xchg   %ax,%ax

00000000001f9d90 <Ogre::Node::_getFullTransform() const>:
  1f9d90:	mov    %rbx,-0x20(%rsp)
  1f9d95:	mov    %rbp,-0x18(%rsp)
  1f9d9a:	mov    %rdi,%rbx
  1f9d9d:	mov    %r12,-0x10(%rsp)
  1f9da2:	mov    %r13,-0x8(%rsp)
  1f9da7:	sub    $0x28,%rsp
  1f9dab:	cmpb   $0x0,0x1b0(%rdi)
  1f9db2:	lea    0x170(%rdi),%rbp
  1f9db9:	je     1f9dfa <Ogre::Node::_getFullTransform() const+0x6a>
  1f9dbb:	mov    (%rdi),%rax
  1f9dbe:	call   *0x1f8(%rax)
  1f9dc4:	mov    %rax,%r13
  1f9dc7:	mov    (%rbx),%rax
  1f9dca:	mov    %rbx,%rdi
  1f9dcd:	call   *0x208(%rax)
  1f9dd3:	mov    %rax,%r12
  1f9dd6:	mov    (%rbx),%rax
  1f9dd9:	mov    %rbx,%rdi
  1f9ddc:	call   *0x200(%rax)
  1f9de2:	mov    %r13,%rcx
  1f9de5:	mov    %rax,%rsi
  1f9de8:	mov    %r12,%rdx
  1f9deb:	mov    %rbp,%rdi
  1f9dee:	call   10a0a8 <Ogre::Matrix4::makeTransform(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Quaternion const&)@plt>
  1f9df3:	movb   $0x0,0x1b0(%rbx)
  1f9dfa:	mov    %rbp,%rax
  1f9dfd:	mov    0x8(%rsp),%rbx
  1f9e02:	mov    0x10(%rsp),%rbp
  1f9e07:	mov    0x18(%rsp),%r12
  1f9e0c:	rex.WR
  1f9e0d:	.byte 0x8b
  1f9e0e:	insb   (%dx),(%rdi)
  1f9e0f:	.byte 0x24
