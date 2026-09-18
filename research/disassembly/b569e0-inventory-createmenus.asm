
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b569e0 <_ZN14CInventoryMenu11createMenusEv>:
  b569e0:	push   %r15
  b569e2:	push   %r14
  b569e4:	push   %r13
  b569e6:	push   %r12
  b569e8:	push   %rbp
  b569e9:	push   %rbx
  b569ea:	mov    %rdi,%rbx
  b569ed:	sub    $0x44d8,%rsp
  b569f4:	mov    0x68(%rdi),%rdi
  b569f8:	mov    0x9b4a66(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  b569fe:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b56a03:	cvtsi2ss %eax,%xmm0
  b56a07:	mov    0x9b4a5b(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  b56a0d:	movss  %xmm0,0x10(%rsp)
  b56a13:	mov    0x68(%rbx),%rdi
  b56a17:	call   c6e440 <_ZN20CDynamicPropertyFile6GetIntEj>
  b56a1c:	cvtsi2ss %eax,%xmm1
  b56a20:	xor    %r9d,%r9d
  b56a23:	xor    %r8d,%r8d
  b56a26:	mov    $0x1001608,%ecx
  b56a2b:	mov    $0xfef988,%edx
  b56a30:	movss  %xmm1,0x18(%rsp)
  b56a36:	mov    0x9138(%rbx),%rsi
  b56a3d:	mov    0x9178(%rbx),%rdi
  b56a44:	movl   $0x0,(%rsp)
  b56a4b:	call   d77e40 <_ZN16CResourceManager18createGenericModelEPN4Ogre12SceneManagerEPKwS4_bbb>
  b56a50:	mov    $0x1,%edx
  b56a55:	mov    %rax,%rdi
  b56a58:	mov    %rax,0x9170(%rbx)
  b56a5f:	mov    $0x5,%esi
  b56a64:	call   8a17d0 <_ZN13CGenericModel16generateExtremesEmb>
  b56a69:	movq   $0x0,0x3e70(%rsp)
  b56a75:	movl   $0x1,0x3e68(%rsp)
  b56a80:	movl   $0xc7c35000,0x3e50(%rsp)
  b56a8b:	movl   $0xc7c35000,0x3e54(%rsp)
  b56a96:	movl   $0xc7c35000,0x3e58(%rsp)
  b56aa1:	movl   $0x47c35000,0x3e5c(%rsp)
  b56aac:	movl   $0x47c35000,0x3e60(%rsp)
  b56ab7:	movl   $0x47c35000,0x3e64(%rsp)
  b56ac2:	mov    0x9170(%rbx),%rax
  b56ac9:	mov    0x60(%rax),%rdi
  b56acd:	call   555158 <_ZNK4Ogre6Entity7getMeshEv@plt>
  b56ad2:	mov    0x8(%rax),%rdi
  b56ad6:	lea    0x3e50(%rsp),%rsi
  b56ade:	mov    $0x1,%edx
  b56ae3:	call   5557c8 <_ZN4Ogre4Mesh10_setBoundsERKNS_14AxisAlignedBoxEb@plt>
  b56ae8:	movss  0x18(%rsp),%xmm0
  b56aee:	mov    0x9170(%rbx),%rax
  b56af5:	divss  0x46fc77(%rip),%xmm0        # fc6774 <_ZTS10iCollision+0x24>
  b56afd:	movss  0x10(%rsp),%xmm1
  b56b03:	mov    0x9b4967(%rip),%esi        # 150b470 <KSETTINGS_YRATIO>
  b56b09:	mov    (%rax),%rax
  b56b0c:	mov    0x58(%rax),%rbp
  b56b10:	subss  %xmm0,%xmm1
  b56b14:	movss  %xmm1,0x10(%rsp)
  b56b1a:	mov    0x68(%rbx),%rdi
  b56b1e:	call   c6e410 <_ZN20CDynamicPropertyFile8GetFloatEj>
  b56b23:	movss  0x10(%rsp),%xmm1
  b56b29:	mov    0x9170(%rbx),%rdi
  b56b30:	divss  %xmm0,%xmm1
  b56b34:	movss  0x44dcd4(%rip),%xmm0        # fa4810 <_ZTVN4Ogre13FrameListenerE+0x50>
  b56b3c:	xorps  %xmm2,%xmm2
  b56b3f:	mulss  %xmm1,%xmm0
  b56b43:	movaps %xmm2,%xmm1
  b56b46:	call   *%rbp
  b56b48:	mov    0x9170(%rbx),%rdi
  b56b4f:	xor    %esi,%esi
  b56b51:	mov    (%rdi),%rax
  b56b54:	call   *0x50(%rax)
  b56b57:	xor    %ebp,%ebp
  b56b59:	cmpb   $0x0,0x48de7d(%rip)        # fe49dd <_ZTI17CSpawnClassParser+0x6dd>
  b56b60:	mov    $0xfe49de,%r13d
  b56b66:	movq   $0x20,0x3d78(%rsp)
  b56b72:	movq   $0x0,0x3d80(%rsp)
  b56b7e:	mov    %r13,%rax
  b56b81:	movq   $0x0,0x3d90(%rsp)
  b56b8d:	movq   $0x0,0x3d88(%rsp)
  b56b99:	movq   $0x0,0x3e18(%rsp)
  b56ba5:	movq   $0x0,0x3d70(%rsp)
  b56bb1:	movl   $0x0,0x3d98(%rsp)
  b56bbc:	je     b56bd5 <_ZN14CInventoryMenu11createMenusEv+0x1f5>
  b56bbe:	xchg   %ax,%ax
  b56bc0:	movzbl (%rax),%edx
  b56bc3:	mov    %rax,%rbp
  b56bc6:	add    $0x1,%rax
  b56bca:	sub    $0xfe49dd,%rbp
  b56bd1:	test   %dl,%dl
  b56bd3:	jne    b56bc0 <_ZN14CInventoryMenu11createMenusEv+0x1e0>
  b56bd5:	cmp    0x8cd844(%rip),%rbp        # 1424420 <_ZN5CEGUI6String4nposE>
  b56bdc:	je     b5e7c6 <_ZN14CInventoryMenu11createMenusEv+0x7de6>
  b56be2:	mov    %rbp,%rax
  b56be5:	mov    $0xfe49dd,%edx
  b56bea:	xor    %r12d,%r12d
  b56bed:	jmp    b56bf4 <_ZN14CInventoryMenu11createMenusEv+0x214>
  b56bef:	nop
  b56bf0:	add    $0x1,%r12
  b56bf4:	test   %rax,%rax
  b56bf7:	je     b56c38 <_ZN14CInventoryMenu11createMenusEv+0x258>
  b56bf9:	movzbl (%rdx),%ecx
  b56bfc:	sub    $0x1,%rax
  b56c00:	add    $0x1,%rdx
  b56c04:	test   %cl,%cl
  b56c06:	jns    b56bf0 <_ZN14CInventoryMenu11createMenusEv+0x210>
  b56c08:	cmp    $0xdf,%cl
  b56c0b:	ja     b56c20 <_ZN14CInventoryMenu11createMenusEv+0x240>
  b56c0d:	sub    $0x1,%rax
  b56c11:	add    $0x1,%rdx
  b56c15:	jmp    b56bf0 <_ZN14CInventoryMenu11createMenusEv+0x210>
  b56c17:	nopw   0x0(%rax,%rax,1)
  b56c20:	cmp    $0xef,%cl
  b56c23:	ja     b56e80 <_ZN14CInventoryMenu11createMenusEv+0x4a0>
  b56c29:	sub    $0x2,%rax
  b56c2d:	add    $0x2,%rdx
  b56c31:	jmp    b56bf0 <_ZN14CInventoryMenu11createMenusEv+0x210>
  b56c33:	nopl   0x0(%rax,%rax,1)
  b56c38:	lea    0x3d70(%rsp),%r14
  b56c40:	mov    %r12,%rsi
  b56c43:	mov    %r14,%rdi
  b56c46:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b56c4b:	mov    0x3d78(%rsp),%rcx
  b56c53:	lea    0x28(%r14),%rsi
  b56c57:	cmp    $0x20,%rcx
  b56c5b:	ja     b56e90 <_ZN14CInventoryMenu11createMenusEv+0x4b0>
  b56c61:	test   %rbp,%rbp
  b56c64:	je     b56ea1 <_ZN14CInventoryMenu11createMenusEv+0x4c1>
  b56c6a:	test   %rcx,%rcx
  b56c6d:	setne  %al
  b56c70:	test   %al,%al
  b56c72:	je     b56ce0 <_ZN14CInventoryMenu11createMenusEv+0x300>
  b56c74:	xor    %edx,%edx
  b56c76:	xor    %eax,%eax
  b56c78:	jmp    b56c99 <_ZN14CInventoryMenu11createMenusEv+0x2b9>
  b56c7a:	nopw   0x0(%rax,%rax,1)
  b56c80:	movzbl %dl,%edx
  b56c83:	mov    %edx,(%rsi)
  b56c85:	mov    %eax,%edx
  b56c87:	sub    $0x1,%rcx
  b56c8b:	cmp    %rbp,%rdx
  b56c8e:	jae    b56ce0 <_ZN14CInventoryMenu11createMenusEv+0x300>
  b56c90:	test   %rcx,%rcx
  b56c93:	je     b56ce0 <_ZN14CInventoryMenu11createMenusEv+0x300>
  b56c95:	add    $0x4,%rsi
  b56c99:	movzbl 0xfe49dd(%rdx),%edx
  b56ca0:	add    $0x1,%eax
  b56ca3:	test   %dl,%dl
  b56ca5:	jns    b56c80 <_ZN14CInventoryMenu11createMenusEv+0x2a0>
  b56ca7:	cmp    $0xdf,%dl
  b56caa:	ja     b56ee0 <_ZN14CInventoryMenu11createMenusEv+0x500>
  b56cb0:	mov    $0x1f,%edi
  b56cb5:	sub    $0x1,%rcx
  b56cb9:	and    %edx,%edi
  b56cbb:	mov    %eax,%edx
  b56cbd:	add    $0x1,%eax
  b56cc0:	movzbl 0xfe49dd(%rdx),%edx
  b56cc7:	shl    $0x6,%edi
  b56cca:	and    $0x3f,%edx
  b56ccd:	or     %edi,%edx
  b56ccf:	mov    %edx,(%rsi)
  b56cd1:	mov    %eax,%edx
  b56cd3:	cmp    %rbp,%rdx
  b56cd6:	jb     b56c90 <_ZN14CInventoryMenu11createMenusEv+0x2b0>
  b56cd8:	nopl   0x0(%rax,%rax,1)
  b56ce0:	cmpq   $0x20,0x3d78(%rsp)
  b56ce9:	mov    %r12,0x3d70(%rsp)
  b56cf1:	lea    0x28(%r14),%rax
  b56cf5:	jbe    b56cff <_ZN14CInventoryMenu11createMenusEv+0x31f>
  b56cf7:	mov    0x3e18(%rsp),%rax
  b56cff:	movl   $0x0,(%rax,%r12,4)
  b56d07:	mov    0x8cdb82(%rip),%rdi        # 1424890 <_ZN5CEGUI9SingletonINS_15ImagesetManagerEE12ms_SingletonE>
  b56d0e:	mov    %r14,%rsi
  b56d11:	call   556508 <_ZNK5CEGUI15ImagesetManager11getImagesetERKNS_6StringE@plt>
  b56d16:	mov    %rax,0x1cf8(%rbx)
  b56d1d:	mov    %r14,%rdi
  b56d20:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b56d25:	lea    0x3b60(%rsp),%rdi
  b56d2d:	xor    %esi,%esi
  b56d2f:	movq   $0x20,0x3b68(%rsp)
  b56d3b:	movq   $0x0,0x3b70(%rsp)
  b56d47:	movq   $0x0,0x3b80(%rsp)
  b56d53:	movq   $0x0,0x3b78(%rsp)
  b56d5f:	movq   $0x0,0x3c08(%rsp)
  b56d6b:	movq   $0x0,0x3b60(%rsp)
  b56d77:	movl   $0x0,0x3b88(%rsp)
  b56d82:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b56d87:	cmpq   $0x20,0x3b68(%rsp)
  b56d90:	movq   $0x0,0x3b60(%rsp)
  b56d9c:	ja     b5b120 <_ZN14CInventoryMenu11createMenusEv+0x4740>
  b56da2:	lea    0x3b60(%rsp),%rax
  b56daa:	add    $0x28,%rax
  b56dae:	movl   $0x0,(%rax)
  b56db4:	xor    %ebp,%ebp
  b56db6:	cmpb   $0x0,0x498a69(%rip)        # fef826 <_ZTI16CInteractiveMenu+0xe6>
  b56dbd:	mov    $0xfef827,%r13d
  b56dc3:	movq   $0x20,0x3c18(%rsp)
  b56dcf:	movq   $0x0,0x3c20(%rsp)
  b56ddb:	movq   $0x0,0x3c30(%rsp)
  b56de7:	movq   $0x0,0x3c28(%rsp)
  b56df3:	mov    %r13,%rax
  b56df6:	movq   $0x0,0x3cb8(%rsp)
  b56e02:	movq   $0x0,0x3c10(%rsp)
  b56e0e:	movl   $0x0,0x3c38(%rsp)
  b56e19:	je     b56e35 <_ZN14CInventoryMenu11createMenusEv+0x455>
  b56e1b:	nopl   0x0(%rax,%rax,1)
  b56e20:	movzbl (%rax),%edx
  b56e23:	mov    %rax,%rbp
  b56e26:	add    $0x1,%rax
  b56e2a:	sub    $0xfef826,%rbp
  b56e31:	test   %dl,%dl
  b56e33:	jne    b56e20 <_ZN14CInventoryMenu11createMenusEv+0x440>
  b56e35:	cmp    0x8cd5e4(%rip),%rbp        # 1424420 <_ZN5CEGUI6String4nposE>
  b56e3c:	je     b5e888 <_ZN14CInventoryMenu11createMenusEv+0x7ea8>
  b56e42:	mov    %rbp,%rax
  b56e45:	mov    $0xfef826,%edx
  b56e4a:	xor    %r12d,%r12d
  b56e4d:	jmp    b56e54 <_ZN14CInventoryMenu11createMenusEv+0x474>
  b56e4f:	nop
  b56e50:	add    $0x1,%r12
  b56e54:	test   %rax,%rax
  b56e57:	je     b56f40 <_ZN14CInventoryMenu11createMenusEv+0x560>
  b56e5d:	movzbl (%rdx),%ecx
  b56e60:	sub    $0x1,%rax
  b56e64:	add    $0x1,%rdx
  b56e68:	test   %cl,%cl
  b56e6a:	jns    b56e50 <_ZN14CInventoryMenu11createMenusEv+0x470>
  b56e6c:	cmp    $0xdf,%cl
  b56e6f:	ja     b56f20 <_ZN14CInventoryMenu11createMenusEv+0x540>
  b56e75:	sub    $0x1,%rax
  b56e79:	add    $0x1,%rdx
  b56e7d:	jmp    b56e50 <_ZN14CInventoryMenu11createMenusEv+0x470>
  b56e7f:	nop
  b56e80:	sub    $0x2,%rax
  b56e84:	add    $0x3,%rdx
  b56e88:	jmp    b56bf0 <_ZN14CInventoryMenu11createMenusEv+0x210>
  b56e8d:	nopl   (%rax)
  b56e90:	test   %rbp,%rbp
  b56e93:	mov    0x3e18(%rsp),%rsi
  b56e9b:	jne    b56c6a <_ZN14CInventoryMenu11createMenusEv+0x28a>
  b56ea1:	cmpb   $0x0,0x48db35(%rip)        # fe49dd <_ZTI17CSpawnClassParser+0x6dd>
  b56ea8:	je     b56ce0 <_ZN14CInventoryMenu11createMenusEv+0x300>
  b56eae:	xchg   %ax,%ax
  b56eb0:	movzbl 0x0(%r13),%eax
  b56eb5:	mov    %r13,%rbp
  b56eb8:	add    $0x1,%r13
  b56ebc:	sub    $0xfe49dd,%rbp
  b56ec3:	test   %al,%al
  b56ec5:	jne    b56eb0 <_ZN14CInventoryMenu11createMenusEv+0x4d0>
  b56ec7:	test   %rbp,%rbp
  b56eca:	setne  %al
  b56ecd:	test   %rcx,%rcx
  b56ed0:	setne  %dl
  b56ed3:	and    %edx,%eax
  b56ed5:	jmp    b56c70 <_ZN14CInventoryMenu11createMenusEv+0x290>
  b56eda:	nopw   0x0(%rax,%rax,1)
  b56ee0:	cmp    $0xef,%dl
  b56ee3:	ja     b58490 <_ZN14CInventoryMenu11createMenusEv+0x1ab0>
  b56ee9:	mov    %edx,%edi
  b56eeb:	lea    0x1(%rax),%edx
  b56eee:	shl    $0xc,%edi
  b56ef1:	movzbl 0xfe49dd(%rdx),%edx
  b56ef8:	and    $0xf000,%edi
  b56efe:	and    $0x3f,%edx
  b56f01:	or     %edi,%edx
  b56f03:	mov    %eax,%edi
  b56f05:	add    $0x2,%eax
  b56f08:	movzbl 0xfe49dd(%rdi),%edi
  b56f0f:	and    $0x3f,%edi
  b56f12:	shl    $0x6,%edi
  b56f15:	or     %edi,%edx
  b56f17:	jmp    b56c83 <_ZN14CInventoryMenu11createMenusEv+0x2a3>
  b56f1c:	nopl   0x0(%rax)
  b56f20:	cmp    $0xef,%cl
  b56f23:	ja     b589f0 <_ZN14CInventoryMenu11createMenusEv+0x2010>
  b56f29:	sub    $0x2,%rax
  b56f2d:	add    $0x2,%rdx
  b56f31:	jmp    b56e50 <_ZN14CInventoryMenu11createMenusEv+0x470>
  b56f36:	cs nopw 0x0(%rax,%rax,1)
  b56f40:	lea    0x3c10(%rsp),%r14
  b56f48:	mov    %r12,%rsi
  b56f4b:	mov    %r14,%rdi
  b56f4e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b56f53:	mov    0x3c18(%rsp),%rcx
  b56f5b:	lea    0x28(%r14),%rsi
  b56f5f:	cmp    $0x20,%rcx
  b56f63:	jbe    b56f6d <_ZN14CInventoryMenu11createMenusEv+0x58d>
  b56f65:	mov    0x3cb8(%rsp),%rsi
  b56f6d:	test   %rbp,%rbp
  b56f70:	je     b5b0e0 <_ZN14CInventoryMenu11createMenusEv+0x4700>
  b56f76:	test   %rcx,%rcx
  b56f79:	setne  %al
  b56f7c:	test   %al,%al
  b56f7e:	je     b56ff0 <_ZN14CInventoryMenu11createMenusEv+0x610>
  b56f80:	xor    %edx,%edx
  b56f82:	xor    %eax,%eax
  b56f84:	jmp    b56fa9 <_ZN14CInventoryMenu11createMenusEv+0x5c9>
  b56f86:	cs nopw 0x0(%rax,%rax,1)
  b56f90:	movzbl %dl,%edx
  b56f93:	mov    %edx,(%rsi)
  b56f95:	mov    %eax,%edx
  b56f97:	sub    $0x1,%rcx
  b56f9b:	cmp    %rbp,%rdx
  b56f9e:	jae    b56ff0 <_ZN14CInventoryMenu11createMenusEv+0x610>
  b56fa0:	test   %rcx,%rcx
  b56fa3:	je     b56ff0 <_ZN14CInventoryMenu11createMenusEv+0x610>
  b56fa5:	add    $0x4,%rsi
  b56fa9:	movzbl 0xfef826(%rdx),%edx
  b56fb0:	add    $0x1,%eax
  b56fb3:	test   %dl,%dl
  b56fb5:	jns    b56f90 <_ZN14CInventoryMenu11createMenusEv+0x5b0>
  b56fb7:	cmp    $0xdf,%dl
  b56fba:	ja     b570e0 <_ZN14CInventoryMenu11createMenusEv+0x700>
  b56fc0:	mov    $0x1f,%edi
  b56fc5:	sub    $0x1,%rcx
  b56fc9:	and    %edx,%edi
  b56fcb:	mov    %eax,%edx
  b56fcd:	add    $0x1,%eax
  b56fd0:	movzbl 0xfef826(%rdx),%edx
  b56fd7:	shl    $0x6,%edi
  b56fda:	and    $0x3f,%edx
  b56fdd:	or     %edi,%edx
  b56fdf:	mov    %edx,(%rsi)
  b56fe1:	mov    %eax,%edx
  b56fe3:	cmp    %rbp,%rdx
  b56fe6:	jb     b56fa0 <_ZN14CInventoryMenu11createMenusEv+0x5c0>
  b56fe8:	nopl   0x0(%rax,%rax,1)
  b56ff0:	cmpq   $0x20,0x3c18(%rsp)
  b56ff9:	mov    %r12,0x3c10(%rsp)
  b57001:	lea    0x28(%r14),%rax
  b57005:	jbe    b5700f <_ZN14CInventoryMenu11createMenusEv+0x62f>
  b57007:	mov    0x3cb8(%rsp),%rax
  b5700f:	movl   $0x0,(%rax,%r12,4)
  b57017:	xor    %ebp,%ebp
  b57019:	cmpb   $0x0,0x48d97d(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b57020:	mov    $0xfe499e,%r15d
  b57026:	movq   $0x20,0x3cc8(%rsp)
  b57032:	movq   $0x0,0x3cd0(%rsp)
  b5703e:	movq   $0x0,0x3ce0(%rsp)
  b5704a:	movq   $0x0,0x3cd8(%rsp)
  b57056:	mov    %r15,%rax
  b57059:	movq   $0x0,0x3d68(%rsp)
  b57065:	movq   $0x0,0x3cc0(%rsp)
  b57071:	movl   $0x0,0x3ce8(%rsp)
  b5707c:	je     b57095 <_ZN14CInventoryMenu11createMenusEv+0x6b5>
  b5707e:	xchg   %ax,%ax
  b57080:	movzbl (%rax),%edx
  b57083:	mov    %rax,%rbp
  b57086:	add    $0x1,%rax
  b5708a:	sub    $0xfe499d,%rbp
  b57091:	test   %dl,%dl
  b57093:	jne    b57080 <_ZN14CInventoryMenu11createMenusEv+0x6a0>
  b57095:	cmp    0x8cd384(%rip),%rbp        # 1424420 <_ZN5CEGUI6String4nposE>
  b5709c:	je     b5e9a5 <_ZN14CInventoryMenu11createMenusEv+0x7fc5>
  b570a2:	mov    %rbp,%rax
  b570a5:	mov    $0xfe499d,%edx
  b570aa:	xor    %r12d,%r12d
  b570ad:	jmp    b570b4 <_ZN14CInventoryMenu11createMenusEv+0x6d4>
  b570af:	nop
  b570b0:	add    $0x1,%r12
  b570b4:	test   %rax,%rax
  b570b7:	je     b57140 <_ZN14CInventoryMenu11createMenusEv+0x760>
  b570bd:	movzbl (%rdx),%ecx
  b570c0:	sub    $0x1,%rax
  b570c4:	add    $0x1,%rdx
  b570c8:	test   %cl,%cl
  b570ca:	jns    b570b0 <_ZN14CInventoryMenu11createMenusEv+0x6d0>
  b570cc:	cmp    $0xdf,%cl
  b570cf:	ja     b57120 <_ZN14CInventoryMenu11createMenusEv+0x740>
  b570d1:	sub    $0x1,%rax
  b570d5:	add    $0x1,%rdx
  b570d9:	jmp    b570b0 <_ZN14CInventoryMenu11createMenusEv+0x6d0>
  b570db:	nopl   0x0(%rax,%rax,1)
  b570e0:	cmp    $0xef,%dl
  b570e3:	ja     b58a00 <_ZN14CInventoryMenu11createMenusEv+0x2020>
  b570e9:	mov    %edx,%edi
  b570eb:	lea    0x1(%rax),%edx
  b570ee:	shl    $0xc,%edi
  b570f1:	movzbl 0xfef826(%rdx),%edx
  b570f8:	and    $0xf000,%edi
  b570fe:	and    $0x3f,%edx
  b57101:	or     %edi,%edx
  b57103:	mov    %eax,%edi
  b57105:	add    $0x2,%eax
  b57108:	movzbl 0xfef826(%rdi),%edi
  b5710f:	and    $0x3f,%edi
  b57112:	shl    $0x6,%edi
  b57115:	or     %edi,%edx
  b57117:	jmp    b56f93 <_ZN14CInventoryMenu11createMenusEv+0x5b3>
  b5711c:	nopl   0x0(%rax)
  b57120:	cmp    $0xef,%cl
  b57123:	ja     b58ca0 <_ZN14CInventoryMenu11createMenusEv+0x22c0>
  b57129:	sub    $0x2,%rax
  b5712d:	add    $0x2,%rdx
  b57131:	jmp    b570b0 <_ZN14CInventoryMenu11createMenusEv+0x6d0>
  b57136:	cs nopw 0x0(%rax,%rax,1)
  b57140:	lea    0x3cc0(%rsp),%r13
  b57148:	mov    %r12,%rsi
  b5714b:	mov    %r13,%rdi
  b5714e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57153:	mov    0x3cc8(%rsp),%rcx
  b5715b:	lea    0x28(%r13),%rsi
  b5715f:	cmp    $0x20,%rcx
  b57163:	jbe    b5716d <_ZN14CInventoryMenu11createMenusEv+0x78d>
  b57165:	mov    0x3d68(%rsp),%rsi
  b5716d:	test   %rbp,%rbp
  b57170:	je     b5b1f0 <_ZN14CInventoryMenu11createMenusEv+0x4810>
  b57176:	test   %rcx,%rcx
  b57179:	setne  %al
  b5717c:	test   %al,%al
  b5717e:	je     b571f0 <_ZN14CInventoryMenu11createMenusEv+0x810>
  b57180:	xor    %edx,%edx
  b57182:	xor    %eax,%eax
  b57184:	jmp    b571a9 <_ZN14CInventoryMenu11createMenusEv+0x7c9>
  b57186:	cs nopw 0x0(%rax,%rax,1)
  b57190:	movzbl %dl,%edx
  b57193:	mov    %edx,(%rsi)
  b57195:	mov    %eax,%edx
  b57197:	sub    $0x1,%rcx
  b5719b:	cmp    %rbp,%rdx
  b5719e:	jae    b571f0 <_ZN14CInventoryMenu11createMenusEv+0x810>
  b571a0:	test   %rcx,%rcx
  b571a3:	je     b571f0 <_ZN14CInventoryMenu11createMenusEv+0x810>
  b571a5:	add    $0x4,%rsi
  b571a9:	movzbl 0xfe499d(%rdx),%edx
  b571b0:	add    $0x1,%eax
  b571b3:	test   %dl,%dl
  b571b5:	jns    b57190 <_ZN14CInventoryMenu11createMenusEv+0x7b0>
  b571b7:	cmp    $0xdf,%dl
  b571ba:	ja     b58430 <_ZN14CInventoryMenu11createMenusEv+0x1a50>
  b571c0:	mov    $0x1f,%edi
  b571c5:	sub    $0x1,%rcx
  b571c9:	and    %edx,%edi
  b571cb:	mov    %eax,%edx
  b571cd:	add    $0x1,%eax
  b571d0:	movzbl 0xfe499d(%rdx),%edx
  b571d7:	shl    $0x6,%edi
  b571da:	and    $0x3f,%edx
  b571dd:	or     %edi,%edx
  b571df:	mov    %edx,(%rsi)
  b571e1:	mov    %eax,%edx
  b571e3:	cmp    %rbp,%rdx
  b571e6:	jb     b571a0 <_ZN14CInventoryMenu11createMenusEv+0x7c0>
  b571e8:	nopl   0x0(%rax,%rax,1)
  b571f0:	cmpq   $0x20,0x3cc8(%rsp)
  b571f9:	mov    %r12,0x3cc0(%rsp)
  b57201:	lea    0x28(%r13),%rax
  b57205:	jbe    b5720f <_ZN14CInventoryMenu11createMenusEv+0x82f>
  b57207:	mov    0x3d68(%rsp),%rax
  b5720f:	movl   $0x0,(%rax,%r12,4)
  b57217:	mov    0x8cd442(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5721e:	lea    0x3b60(%rsp),%rcx
  b57226:	mov    %r14,%rdx
  b57229:	mov    %r13,%rsi
  b5722c:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b57231:	mov    %rax,0x20(%rbx)
  b57235:	mov    %r13,%rdi
  b57238:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5723d:	mov    %r14,%rdi
  b57240:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57245:	lea    0x3b60(%rsp),%rdi
  b5724d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57252:	movl   $0x0,0x40e4(%rsp)
  b5725d:	movl   $0x3f800000,0x40e0(%rsp)
  b57268:	lea    0x40e0(%rsp),%rsi
  b57270:	movl   $0x0,0x40ec(%rsp)
  b5727b:	movl   $0x3f800000,0x40e8(%rsp)
  b57286:	mov    0x20(%rbx),%rdi
  b5728a:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5728f:	lea    0x3a00(%rsp),%r13
  b57297:	mov    $0x5,%esi
  b5729c:	movq   $0x20,0x3a08(%rsp)
  b572a8:	movq   $0x0,0x3a10(%rsp)
  b572b4:	movq   $0x0,0x3a20(%rsp)
  b572c0:	mov    %r13,%rdi
  b572c3:	movq   $0x0,0x3a18(%rsp)
  b572cf:	movq   $0x0,0x3aa8(%rsp)
  b572db:	movq   $0x0,0x3a00(%rsp)
  b572e7:	movl   $0x0,0x3a28(%rsp)
  b572f2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b572f7:	cmpq   $0x20,0x3a08(%rsp)
  b57300:	lea    0x28(%r13),%rdx
  b57304:	jbe    b5730e <_ZN14CInventoryMenu11createMenusEv+0x92e>
  b57306:	mov    0x3aa8(%rsp),%rdx
  b5730e:	mov    $0xfe603a,%eax
  b57313:	nopl   0x0(%rax,%rax,1)
  b57318:	movzbl (%rax),%ecx
  b5731b:	add    $0x1,%rax
  b5731f:	mov    %ecx,(%rdx)
  b57321:	add    $0x4,%rdx
  b57325:	cmp    $0xfe603f,%rax
  b5732b:	jne    b57318 <_ZN14CInventoryMenu11createMenusEv+0x938>
  b5732d:	cmpq   $0x20,0x3a08(%rsp)
  b57336:	movq   $0x5,0x3a00(%rsp)
  b57342:	lea    0x3c(%r13),%rax
  b57346:	jbe    b57354 <_ZN14CInventoryMenu11createMenusEv+0x974>
  b57348:	mov    0x3aa8(%rsp),%rax
  b57350:	add    $0x14,%rax
  b57354:	lea    0x3ab0(%rsp),%r12
  b5735c:	movl   $0x0,(%rax)
  b57362:	mov    $0xb,%esi
  b57367:	movq   $0x20,0x3ab8(%rsp)
  b57373:	movq   $0x0,0x3ac0(%rsp)
  b5737f:	mov    %r12,%rdi
  b57382:	movq   $0x0,0x3ad0(%rsp)
  b5738e:	movq   $0x0,0x3ac8(%rsp)
  b5739a:	movq   $0x0,0x3b58(%rsp)
  b573a6:	movq   $0x0,0x3ab0(%rsp)
  b573b2:	movl   $0x0,0x3ad8(%rsp)
  b573bd:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b573c2:	cmpq   $0x20,0x3ab8(%rsp)
  b573cb:	lea    0x28(%r12),%rdx
  b573d0:	jbe    b573da <_ZN14CInventoryMenu11createMenusEv+0x9fa>
  b573d2:	mov    0x3b58(%rsp),%rdx
  b573da:	mov    $0xfe6039,%ebp
  b573df:	mov    $0xfe602e,%eax
  b573e4:	nopl   0x0(%rax)
  b573e8:	movzbl (%rax),%ecx
  b573eb:	add    $0x1,%rax
  b573ef:	mov    %ecx,(%rdx)
  b573f1:	add    $0x4,%rdx
  b573f5:	cmp    $0xfe6039,%rax
  b573fb:	jne    b573e8 <_ZN14CInventoryMenu11createMenusEv+0xa08>
  b573fd:	cmpq   $0x20,0x3ab8(%rsp)
  b57406:	movq   $0xb,0x3ab0(%rsp)
  b57412:	lea    0x54(%r12),%rax
  b57417:	jbe    b57425 <_ZN14CInventoryMenu11createMenusEv+0xa45>
  b57419:	mov    0x3b58(%rsp),%rax
  b57421:	add    $0x2c,%rax
  b57425:	movl   $0x0,(%rax)
  b5742b:	mov    0x20(%rbx),%rdi
  b5742f:	mov    %r13,%rdx
  b57432:	mov    %r12,%rsi
  b57435:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5743a:	mov    %r12,%rdi
  b5743d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57442:	mov    %r13,%rdi
  b57445:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5744a:	movl   $0x0,0x40d4(%rsp)
  b57455:	movl   $0x0,0x40d0(%rsp)
  b57460:	lea    0x40d0(%rsp),%rsi
  b57468:	movl   $0x0,0x40dc(%rsp)
  b57473:	movl   $0x0,0x40d8(%rsp)
  b5747e:	mov    0x20(%rbx),%rdi
  b57482:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b57487:	mov    0x20(%rbx),%rax
  b5748b:	xor    %esi,%esi
  b5748d:	movb   $0x1,0x3e2(%rax)
  b57494:	mov    0x20(%rbx),%rdi
  b57498:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b5749d:	mov    0x20(%rbx),%rax
  b574a1:	mov    $0x20,%edi
  b574a6:	mov    0x38(%rax),%rax
  b574aa:	mov    0x10(%rax),%r13
  b574ae:	call   552d68 <_Znwm@plt>
  b574b3:	movq   $0xfefcd0,(%rax)
  b574ba:	movq   $0x0,0x10(%rax)
  b574c2:	lea    0x4480(%rsp),%r12
  b574ca:	movq   $0xb458a0,0x8(%rax)
  b574d2:	mov    %rbx,0x18(%rax)
  b574d6:	lea    0x40c0(%rsp),%rdi
  b574de:	mov    %rax,0x4480(%rsp)
  b574e6:	mov    0x20(%rbx),%rsi
  b574ea:	mov    %r12,%rcx
  b574ed:	mov    $0x1424020,%edx
  b574f2:	add    $0x38,%rsi
  b574f6:	call   *%r13
  b574f9:	cmpq   $0x0,0x40c0(%rsp)
  b57502:	je     b57559 <_ZN14CInventoryMenu11createMenusEv+0xb79>
  b57504:	mov    0x40c8(%rsp),%rdx
  b5750c:	mov    (%rdx),%eax
  b5750e:	sub    $0x1,%eax
  b57511:	test   %eax,%eax
  b57513:	mov    %eax,(%rdx)
  b57515:	jne    b57559 <_ZN14CInventoryMenu11createMenusEv+0xb79>
  b57517:	mov    0x40c0(%rsp),%r13
  b5751f:	test   %r13,%r13
  b57522:	je     b57534 <_ZN14CInventoryMenu11createMenusEv+0xb54>
  b57524:	mov    %r13,%rdi
  b57527:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5752c:	mov    %r13,%rdi
  b5752f:	call   553f18 <_ZdlPv@plt>
  b57534:	mov    0x40c8(%rsp),%rdi
  b5753c:	call   553f18 <_ZdlPv@plt>
  b57541:	movq   $0x0,0x40c0(%rsp)
  b5754d:	movq   $0x0,0x40c8(%rsp)
  b57559:	mov    %r12,%rdi
  b5755c:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b57561:	lea    0x3e20(%rsp),%rdi
  b57569:	mov    $0x14c5c40,%esi
  b5756e:	movq   $0x1423a38,0x3e20(%rsp)
  b5757a:	add    $0x8,%rdi
  b5757e:	call   5529a8 <_ZNSsC1ERKSs@plt>
  b57583:	lea    0x3e20(%rsp),%rdi
  b5758b:	mov    $0x14c5c48,%esi
  b57590:	add    $0x10,%rdi
  b57594:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  b57599:	lea    0x4470(%rsp),%r12
  b575a1:	lea    0x44cf(%rsp),%rdx
  b575a9:	mov    $0xfefa30,%esi
  b575ae:	movl   $0x4,0x3e38(%rsp)
  b575b9:	movl   $0x3,0x3e3c(%rsp)
  b575c4:	mov    %r12,%rdi
  b575c7:	movq   $0x1423a38,0x3e40(%rsp)
  b575d3:	movb   $0x0,0x3e48(%rsp)
  b575db:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  b575e0:	call   e4d250 <_ZN11CFileSystem12getSingletonEv>
  b575e5:	lea    0x3e20(%rsp),%rdx
  b575ed:	xor    %r9d,%r9d
  b575f0:	mov    $0x1,%r8d
  b575f6:	xor    %ecx,%ecx
  b575f8:	mov    %r12,%rsi
  b575fb:	mov    %rax,%rdi
  b575fe:	call   e4e3a0 <_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb>
  b57603:	mov    0x4470(%rsp),%rdi
  b5760b:	sub    $0x18,%rdi
  b5760f:	cmp    $0x1424540,%rdi
  b57616:	jne    b5fe6a <_ZN14CInventoryMenu11createMenusEv+0x948a>
  b5761c:	mov    0x3e28(%rsp),%rax
  b57624:	movq   $0x20,0x3958(%rsp)
  b57630:	lea    0x3950(%rsp),%r13
  b57638:	movq   $0x0,0x3960(%rsp)
  b57644:	movq   $0x0,0x3970(%rsp)
  b57650:	movq   $0x0,0x3968(%rsp)
  b5765c:	movq   $0x0,0x39f8(%rsp)
  b57668:	mov    %r13,%rdi
  b5766b:	movq   $0x0,0x3950(%rsp)
  b57677:	movl   $0x0,0x3978(%rsp)
  b57682:	mov    -0x18(%rax),%r12
  b57686:	mov    %r12,%rsi
  b57689:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5768e:	cmpq   $0x20,0x3958(%rsp)
  b57697:	mov    %r12,0x3950(%rsp)
  b5769f:	lea    0x28(%r13),%rax
  b576a3:	jbe    b576ad <_ZN14CInventoryMenu11createMenusEv+0xccd>
  b576a5:	mov    0x39f8(%rsp),%rax
  b576ad:	test   %r12,%r12
  b576b0:	movl   $0x0,(%rax,%r12,4)
  b576b8:	je     b576f7 <_ZN14CInventoryMenu11createMenusEv+0xd17>
  b576ba:	sub    $0x1,%r12
  b576be:	lea    0x28(%r13),%rcx
  b576c2:	jmp    b576cc <_ZN14CInventoryMenu11createMenusEv+0xcec>
  b576c4:	nopl   0x0(%rax)
  b576c8:	sub    $0x1,%r12
  b576cc:	mov    0x3e28(%rsp),%rdx
  b576d4:	cmpq   $0x21,0x3958(%rsp)
  b576dd:	mov    %rcx,%rax
  b576e0:	cmovae 0x39f8(%rsp),%rax
  b576e9:	test   %r12,%r12
  b576ec:	movzbl (%rdx,%r12,1),%edx
  b576f1:	mov    %edx,(%rax,%r12,4)
  b576f5:	jne    b576c8 <_ZN14CInventoryMenu11createMenusEv+0xce8>
  b576f7:	mov    0x8ccf62(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b576fe:	mov    $0x1,%edx
  b57703:	mov    %r13,%rsi
  b57706:	call   5564e8 <_ZN5CEGUI13WindowManager16loadWindowLayoutERKNS_6StringEb@plt>
  b5770b:	mov    %r13,%rdi
  b5770e:	mov    %rax,0x10(%rsp)
  b57713:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57718:	mov    0x70(%rbx),%rdi
  b5771c:	mov    0x10(%rsp),%rsi
  b57721:	xor    %edx,%edx
  b57723:	call   a83ed0 <_ZN7CGameUI20convertToScreenScaleEPN5CEGUI6WindowEb>
  b57728:	mov    0x70(%rbx),%rdi
  b5772c:	mov    0x10(%rsp),%rsi
  b57731:	call   a980e0 <_ZN7CGameUI14mapToFunctionsEPN5CEGUI6WindowE>
  b57736:	mov    0x10(%rsp),%rsi
  b5773b:	mov    %rbx,%rdi
  b5773e:	call   b4f1b0 <_ZN14CInventoryMenu16mapEventHandlersEPN5CEGUI6WindowE>
  b57743:	lea    0x38a0(%rsp),%r13
  b5774b:	mov    $0x7,%esi
  b57750:	movq   $0x20,0x38a8(%rsp)
  b5775c:	movq   $0x0,0x38b0(%rsp)
  b57768:	movq   $0x0,0x38c0(%rsp)
  b57774:	mov    %r13,%rdi
  b57777:	movq   $0x0,0x38b8(%rsp)
  b57783:	movq   $0x0,0x3948(%rsp)
  b5778f:	movq   $0x0,0x38a0(%rsp)
  b5779b:	movl   $0x0,0x38c8(%rsp)
  b577a6:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b577ab:	cmpq   $0x20,0x38a8(%rsp)
  b577b4:	lea    0x28(%r13),%rdx
  b577b8:	jbe    b577c2 <_ZN14CInventoryMenu11createMenusEv+0xde2>
  b577ba:	mov    0x3948(%rsp),%rdx
  b577c2:	mov    $0xfe4a28,%eax
  b577c7:	nopw   0x0(%rax,%rax,1)
  b577d0:	movzbl (%rax),%ecx
  b577d3:	add    $0x1,%rax
  b577d7:	mov    %ecx,(%rdx)
  b577d9:	add    $0x4,%rdx
  b577dd:	cmp    $0xfe4a2f,%rax
  b577e3:	jne    b577d0 <_ZN14CInventoryMenu11createMenusEv+0xdf0>
  b577e5:	cmpq   $0x20,0x38a8(%rsp)
  b577ee:	movq   $0x7,0x38a0(%rsp)
  b577fa:	lea    0x44(%r13),%rax
  b577fe:	jbe    b5780c <_ZN14CInventoryMenu11createMenusEv+0xe2c>
  b57800:	mov    0x3948(%rsp),%rax
  b57808:	add    $0x1c,%rax
  b5780c:	movl   $0x0,(%rax)
  b57812:	mov    0x10(%rsp),%rdi
  b57817:	mov    %r13,%rsi
  b5781a:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5781f:	mov    %r13,%rdi
  b57822:	mov    %rax,%r12
  b57825:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5782a:	mov    0xb0(%r12),%rdi
  b57832:	mov    %r12,%rsi
  b57835:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b5783a:	mov    0x20(%rbx),%rdi
  b5783e:	mov    %r12,%rsi
  b57841:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b57846:	lea    0x3740(%rsp),%r14
  b5784e:	mov    $0x5,%esi
  b57853:	movq   $0x20,0x3748(%rsp)
  b5785f:	movq   $0x0,0x3750(%rsp)
  b5786b:	movq   $0x0,0x3760(%rsp)
  b57877:	mov    %r14,%rdi
  b5787a:	movq   $0x0,0x3758(%rsp)
  b57886:	movq   $0x0,0x37e8(%rsp)
  b57892:	movq   $0x0,0x3740(%rsp)
  b5789e:	movl   $0x0,0x3768(%rsp)
  b578a9:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b578ae:	cmpq   $0x20,0x3748(%rsp)
  b578b7:	lea    0x28(%r14),%rdx
  b578bb:	jbe    b578c5 <_ZN14CInventoryMenu11createMenusEv+0xee5>
  b578bd:	mov    0x37e8(%rsp),%rdx
  b578c5:	mov    $0xfe603a,%eax
  b578ca:	nopw   0x0(%rax,%rax,1)
  b578d0:	movzbl (%rax),%ecx
  b578d3:	add    $0x1,%rax
  b578d7:	mov    %ecx,(%rdx)
  b578d9:	add    $0x4,%rdx
  b578dd:	cmp    $0xfe603f,%rax
  b578e3:	jne    b578d0 <_ZN14CInventoryMenu11createMenusEv+0xef0>
  b578e5:	cmpq   $0x20,0x3748(%rsp)
  b578ee:	movq   $0x5,0x3740(%rsp)
  b578fa:	lea    0x3c(%r14),%rax
  b578fe:	jbe    b5790c <_ZN14CInventoryMenu11createMenusEv+0xf2c>
  b57900:	mov    0x37e8(%rsp),%rax
  b57908:	add    $0x14,%rax
  b5790c:	lea    0x37f0(%rsp),%r13
  b57914:	movl   $0x0,(%rax)
  b5791a:	mov    $0xb,%esi
  b5791f:	movq   $0x20,0x37f8(%rsp)
  b5792b:	movq   $0x0,0x3800(%rsp)
  b57937:	mov    %r13,%rdi
  b5793a:	movq   $0x0,0x3810(%rsp)
  b57946:	movq   $0x0,0x3808(%rsp)
  b57952:	movq   $0x0,0x3898(%rsp)
  b5795e:	movq   $0x0,0x37f0(%rsp)
  b5796a:	movl   $0x0,0x3818(%rsp)
  b57975:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5797a:	cmpq   $0x20,0x37f8(%rsp)
  b57983:	lea    0x28(%r13),%rdx
  b57987:	jbe    b57991 <_ZN14CInventoryMenu11createMenusEv+0xfb1>
  b57989:	mov    0x3898(%rsp),%rdx
  b57991:	mov    $0xfe602e,%eax
  b57996:	cs nopw 0x0(%rax,%rax,1)
  b579a0:	movzbl (%rax),%ecx
  b579a3:	add    $0x1,%rax
  b579a7:	mov    %ecx,(%rdx)
  b579a9:	add    $0x4,%rdx
  b579ad:	cmp    %rax,%rbp
  b579b0:	jne    b579a0 <_ZN14CInventoryMenu11createMenusEv+0xfc0>
  b579b2:	cmpq   $0x20,0x37f8(%rsp)
  b579bb:	movq   $0xb,0x37f0(%rsp)
  b579c7:	lea    0x54(%r13),%rax
  b579cb:	jbe    b579d9 <_ZN14CInventoryMenu11createMenusEv+0xff9>
  b579cd:	mov    0x3898(%rsp),%rax
  b579d5:	add    $0x2c,%rax
  b579d9:	movl   $0x0,(%rax)
  b579df:	mov    %r14,%rdx
  b579e2:	mov    %r13,%rsi
  b579e5:	mov    %r12,%rdi
  b579e8:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b579ed:	mov    %r13,%rdi
  b579f0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b579f5:	mov    %r14,%rdi
  b579f8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b579fd:	mov    %r12,%rdi
  b57a00:	call   553a38 <_ZN5CEGUI6Window10moveToBackEv@plt>
  b57a05:	xor    %esi,%esi
  b57a07:	mov    %r12,%rdi
  b57a0a:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b57a0f:	lea    0x3690(%rsp),%r12
  b57a17:	mov    $0xb,%esi
  b57a1c:	movq   $0x20,0x3698(%rsp)
  b57a28:	movq   $0x0,0x36a0(%rsp)
  b57a34:	movq   $0x0,0x36b0(%rsp)
  b57a40:	mov    %r12,%rdi
  b57a43:	movq   $0x0,0x36a8(%rsp)
  b57a4f:	movq   $0x0,0x3738(%rsp)
  b57a5b:	movq   $0x0,0x3690(%rsp)
  b57a67:	movl   $0x0,0x36b8(%rsp)
  b57a72:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57a77:	cmpq   $0x20,0x3698(%rsp)
  b57a80:	lea    0x28(%r12),%rdx
  b57a85:	jbe    b57a8f <_ZN14CInventoryMenu11createMenusEv+0x10af>
  b57a87:	mov    0x3738(%rsp),%rdx
  b57a8f:	mov    $0xfef81a,%eax
  b57a94:	nopl   0x0(%rax)
  b57a98:	movzbl (%rax),%ecx
  b57a9b:	add    $0x1,%rax
  b57a9f:	mov    %ecx,(%rdx)
  b57aa1:	add    $0x4,%rdx
  b57aa5:	cmp    $0xfef825,%rax
  b57aab:	jne    b57a98 <_ZN14CInventoryMenu11createMenusEv+0x10b8>
  b57aad:	cmpq   $0x20,0x3698(%rsp)
  b57ab6:	movq   $0xb,0x3690(%rsp)
  b57ac2:	lea    0x54(%r12),%rax
  b57ac7:	jbe    b57ad5 <_ZN14CInventoryMenu11createMenusEv+0x10f5>
  b57ac9:	mov    0x3738(%rsp),%rax
  b57ad1:	add    $0x2c,%rax
  b57ad5:	movl   $0x0,(%rax)
  b57adb:	mov    0x10(%rsp),%rdi
  b57ae0:	mov    %r12,%rsi
  b57ae3:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b57ae8:	mov    %rax,0x48(%rbx)
  b57aec:	mov    %r12,%rdi
  b57aef:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57af4:	mov    0x48(%rbx),%rsi
  b57af8:	mov    0xb0(%rsi),%rdi
  b57aff:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b57b04:	mov    0x48(%rbx),%rsi
  b57b08:	mov    0x20(%rbx),%rdi
  b57b0c:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b57b11:	lea    0x3530(%rsp),%r13
  b57b19:	mov    $0x5,%esi
  b57b1e:	movq   $0x20,0x3538(%rsp)
  b57b2a:	movq   $0x0,0x3540(%rsp)
  b57b36:	movq   $0x0,0x3550(%rsp)
  b57b42:	mov    %r13,%rdi
  b57b45:	movq   $0x0,0x3548(%rsp)
  b57b51:	movq   $0x0,0x35d8(%rsp)
  b57b5d:	movq   $0x0,0x3530(%rsp)
  b57b69:	movl   $0x0,0x3558(%rsp)
  b57b74:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57b79:	cmpq   $0x20,0x3538(%rsp)
  b57b82:	lea    0x28(%r13),%rdx
  b57b86:	jbe    b57b90 <_ZN14CInventoryMenu11createMenusEv+0x11b0>
  b57b88:	mov    0x35d8(%rsp),%rdx
  b57b90:	mov    $0xfe603a,%eax
  b57b95:	nopl   (%rax)
  b57b98:	movzbl (%rax),%ecx
  b57b9b:	add    $0x1,%rax
  b57b9f:	mov    %ecx,(%rdx)
  b57ba1:	add    $0x4,%rdx
  b57ba5:	cmp    $0xfe603f,%rax
  b57bab:	jne    b57b98 <_ZN14CInventoryMenu11createMenusEv+0x11b8>
  b57bad:	cmpq   $0x20,0x3538(%rsp)
  b57bb6:	movq   $0x5,0x3530(%rsp)
  b57bc2:	lea    0x3c(%r13),%rax
  b57bc6:	jbe    b57bd4 <_ZN14CInventoryMenu11createMenusEv+0x11f4>
  b57bc8:	mov    0x35d8(%rsp),%rax
  b57bd0:	add    $0x14,%rax
  b57bd4:	lea    0x35e0(%rsp),%r12
  b57bdc:	movl   $0x0,(%rax)
  b57be2:	mov    $0xb,%esi
  b57be7:	movq   $0x20,0x35e8(%rsp)
  b57bf3:	movq   $0x0,0x35f0(%rsp)
  b57bff:	mov    %r12,%rdi
  b57c02:	movq   $0x0,0x3600(%rsp)
  b57c0e:	movq   $0x0,0x35f8(%rsp)
  b57c1a:	movq   $0x0,0x3688(%rsp)
  b57c26:	movq   $0x0,0x35e0(%rsp)
  b57c32:	movl   $0x0,0x3608(%rsp)
  b57c3d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57c42:	cmpq   $0x20,0x35e8(%rsp)
  b57c4b:	lea    0x28(%r12),%rdx
  b57c50:	jbe    b57c5a <_ZN14CInventoryMenu11createMenusEv+0x127a>
  b57c52:	mov    0x3688(%rsp),%rdx
  b57c5a:	mov    $0xfe602e,%eax
  b57c5f:	nop
  b57c60:	movzbl (%rax),%ecx
  b57c63:	add    $0x1,%rax
  b57c67:	mov    %ecx,(%rdx)
  b57c69:	add    $0x4,%rdx
  b57c6d:	cmp    %rax,%rbp
  b57c70:	jne    b57c60 <_ZN14CInventoryMenu11createMenusEv+0x1280>
  b57c72:	cmpq   $0x20,0x35e8(%rsp)
  b57c7b:	movq   $0xb,0x35e0(%rsp)
  b57c87:	lea    0x54(%r12),%rax
  b57c8c:	jbe    b57c9a <_ZN14CInventoryMenu11createMenusEv+0x12ba>
  b57c8e:	mov    0x3688(%rsp),%rax
  b57c96:	add    $0x2c,%rax
  b57c9a:	movl   $0x0,(%rax)
  b57ca0:	mov    0x48(%rbx),%rdi
  b57ca4:	mov    %r13,%rdx
  b57ca7:	mov    %r12,%rsi
  b57caa:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b57caf:	mov    %r12,%rdi
  b57cb2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57cb7:	mov    %r13,%rdi
  b57cba:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57cbf:	mov    0x48(%rbx),%rdi
  b57cc3:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b57cc8:	mov    0x48(%rbx),%rdi
  b57ccc:	xor    %esi,%esi
  b57cce:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b57cd3:	lea    0x3480(%rsp),%r12
  b57cdb:	mov    $0x8,%esi
  b57ce0:	movq   $0x20,0x3488(%rsp)
  b57cec:	movq   $0x0,0x3490(%rsp)
  b57cf8:	movq   $0x0,0x34a0(%rsp)
  b57d04:	mov    %r12,%rdi
  b57d07:	movq   $0x0,0x3498(%rsp)
  b57d13:	movq   $0x0,0x3528(%rsp)
  b57d1f:	movq   $0x0,0x3480(%rsp)
  b57d2b:	movl   $0x0,0x34a8(%rsp)
  b57d36:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57d3b:	cmpq   $0x20,0x3488(%rsp)
  b57d44:	lea    0x28(%r12),%rdx
  b57d49:	jbe    b57d53 <_ZN14CInventoryMenu11createMenusEv+0x1373>
  b57d4b:	mov    0x3528(%rsp),%rdx
  b57d53:	mov    $0xfef811,%eax
  b57d58:	nopl   0x0(%rax,%rax,1)
  b57d60:	movzbl (%rax),%ecx
  b57d63:	add    $0x1,%rax
  b57d67:	mov    %ecx,(%rdx)
  b57d69:	add    $0x4,%rdx
  b57d6d:	cmp    $0xfef819,%rax
  b57d73:	jne    b57d60 <_ZN14CInventoryMenu11createMenusEv+0x1380>
  b57d75:	cmpq   $0x20,0x3488(%rsp)
  b57d7e:	movq   $0x8,0x3480(%rsp)
  b57d8a:	lea    0x48(%r12),%rax
  b57d8f:	jbe    b57d9d <_ZN14CInventoryMenu11createMenusEv+0x13bd>
  b57d91:	mov    0x3528(%rsp),%rax
  b57d99:	add    $0x20,%rax
  b57d9d:	movl   $0x0,(%rax)
  b57da3:	mov    0x10(%rsp),%rdi
  b57da8:	mov    %r12,%rsi
  b57dab:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b57db0:	mov    %rax,0x28(%rbx)
  b57db4:	mov    %r12,%rdi
  b57db7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57dbc:	mov    0x28(%rbx),%rsi
  b57dc0:	mov    0xb0(%rsi),%rdi
  b57dc7:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b57dcc:	mov    0x28(%rbx),%rsi
  b57dd0:	mov    0x20(%rbx),%rdi
  b57dd4:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b57dd9:	lea    0x3320(%rsp),%r13
  b57de1:	mov    $0x5,%esi
  b57de6:	movq   $0x20,0x3328(%rsp)
  b57df2:	movq   $0x0,0x3330(%rsp)
  b57dfe:	movq   $0x0,0x3340(%rsp)
  b57e0a:	mov    %r13,%rdi
  b57e0d:	movq   $0x0,0x3338(%rsp)
  b57e19:	movq   $0x0,0x33c8(%rsp)
  b57e25:	movq   $0x0,0x3320(%rsp)
  b57e31:	movl   $0x0,0x3348(%rsp)
  b57e3c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57e41:	cmpq   $0x20,0x3328(%rsp)
  b57e4a:	lea    0x28(%r13),%rdx
  b57e4e:	jbe    b57e58 <_ZN14CInventoryMenu11createMenusEv+0x1478>
  b57e50:	mov    0x33c8(%rsp),%rdx
  b57e58:	mov    $0xfe603a,%eax
  b57e5d:	nopl   (%rax)
  b57e60:	movzbl (%rax),%ecx
  b57e63:	add    $0x1,%rax
  b57e67:	mov    %ecx,(%rdx)
  b57e69:	add    $0x4,%rdx
  b57e6d:	cmp    $0xfe603f,%rax
  b57e73:	jne    b57e60 <_ZN14CInventoryMenu11createMenusEv+0x1480>
  b57e75:	cmpq   $0x20,0x3328(%rsp)
  b57e7e:	movq   $0x5,0x3320(%rsp)
  b57e8a:	lea    0x3c(%r13),%rax
  b57e8e:	jbe    b57e9c <_ZN14CInventoryMenu11createMenusEv+0x14bc>
  b57e90:	mov    0x33c8(%rsp),%rax
  b57e98:	add    $0x14,%rax
  b57e9c:	lea    0x33d0(%rsp),%r12
  b57ea4:	movl   $0x0,(%rax)
  b57eaa:	mov    $0xb,%esi
  b57eaf:	movq   $0x20,0x33d8(%rsp)
  b57ebb:	movq   $0x0,0x33e0(%rsp)
  b57ec7:	mov    %r12,%rdi
  b57eca:	movq   $0x0,0x33f0(%rsp)
  b57ed6:	movq   $0x0,0x33e8(%rsp)
  b57ee2:	movq   $0x0,0x3478(%rsp)
  b57eee:	movq   $0x0,0x33d0(%rsp)
  b57efa:	movl   $0x0,0x33f8(%rsp)
  b57f05:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b57f0a:	cmpq   $0x20,0x33d8(%rsp)
  b57f13:	lea    0x28(%r12),%rdx
  b57f18:	jbe    b57f22 <_ZN14CInventoryMenu11createMenusEv+0x1542>
  b57f1a:	mov    0x3478(%rsp),%rdx
  b57f22:	mov    $0xfe602e,%eax
  b57f27:	nopw   0x0(%rax,%rax,1)
  b57f30:	movzbl (%rax),%ecx
  b57f33:	add    $0x1,%rax
  b57f37:	mov    %ecx,(%rdx)
  b57f39:	add    $0x4,%rdx
  b57f3d:	cmp    %rax,%rbp
  b57f40:	jne    b57f30 <_ZN14CInventoryMenu11createMenusEv+0x1550>
  b57f42:	cmpq   $0x20,0x33d8(%rsp)
  b57f4b:	movq   $0xb,0x33d0(%rsp)
  b57f57:	lea    0x54(%r12),%rax
  b57f5c:	jbe    b57f6a <_ZN14CInventoryMenu11createMenusEv+0x158a>
  b57f5e:	mov    0x3478(%rsp),%rax
  b57f66:	add    $0x2c,%rax
  b57f6a:	movl   $0x0,(%rax)
  b57f70:	mov    0x28(%rbx),%rdi
  b57f74:	mov    %r13,%rdx
  b57f77:	mov    %r12,%rsi
  b57f7a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b57f7f:	mov    %r12,%rdi
  b57f82:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57f87:	mov    %r13,%rdi
  b57f8a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b57f8f:	mov    0x28(%rbx),%rdi
  b57f93:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b57f98:	mov    0x28(%rbx),%rdi
  b57f9c:	xor    %esi,%esi
  b57f9e:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b57fa3:	lea    0x3110(%rsp),%r12
  b57fab:	xor    %esi,%esi
  b57fad:	movq   $0x20,0x3118(%rsp)
  b57fb9:	movq   $0x0,0x3120(%rsp)
  b57fc5:	movq   $0x0,0x3130(%rsp)
  b57fd1:	mov    %r12,%rdi
  b57fd4:	movq   $0x0,0x3128(%rsp)
  b57fe0:	movq   $0x0,0x31b8(%rsp)
  b57fec:	movq   $0x0,0x3110(%rsp)
  b57ff8:	movl   $0x0,0x3138(%rsp)
  b58003:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58008:	cmpq   $0x20,0x3118(%rsp)
  b58011:	movq   $0x0,0x3110(%rsp)
  b5801d:	lea    0x28(%r12),%rax
  b58022:	jbe    b5802c <_ZN14CInventoryMenu11createMenusEv+0x164c>
  b58024:	mov    0x31b8(%rsp),%rax
  b5802c:	lea    0x31c0(%rsp),%r14
  b58034:	movl   $0x0,(%rax)
  b5803a:	mov    $0xfef835,%esi
  b5803f:	mov    %r14,%rdi
  b58042:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b58047:	lea    0x3270(%rsp),%r13
  b5804f:	mov    $0xfe499d,%esi
  b58054:	mov    %r13,%rdi
  b58057:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b5805c:	mov    0x8cc5fd(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b58063:	mov    %r12,%rcx
  b58066:	mov    %r14,%rdx
  b58069:	mov    %r13,%rsi
  b5806c:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b58071:	mov    %rax,0x30(%rbx)
  b58075:	mov    %r13,%rdi
  b58078:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5807d:	mov    %r14,%rdi
  b58080:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58085:	mov    %r12,%rdi
  b58088:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5808d:	mov    0x30(%rbx),%rsi
  b58091:	mov    0x28(%rbx),%rdi
  b58095:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5809a:	lea    0x40b0(%rsp),%r12
  b580a2:	mov    0x28(%rbx),%rsi
  b580a6:	mov    %r12,%rdi
  b580a9:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b580ae:	mov    0x30(%rbx),%rdi
  b580b2:	mov    %r12,%rsi
  b580b5:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b580ba:	lea    0x2fb0(%rsp),%r13
  b580c2:	mov    $0x5,%esi
  b580c7:	movq   $0x20,0x2fb8(%rsp)
  b580d3:	movq   $0x0,0x2fc0(%rsp)
  b580df:	movq   $0x0,0x2fd0(%rsp)
  b580eb:	mov    %r13,%rdi
  b580ee:	movq   $0x0,0x2fc8(%rsp)
  b580fa:	movq   $0x0,0x3058(%rsp)
  b58106:	movq   $0x0,0x2fb0(%rsp)
  b58112:	movl   $0x0,0x2fd8(%rsp)
  b5811d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58122:	cmpq   $0x20,0x2fb8(%rsp)
  b5812b:	lea    0x28(%r13),%rdx
  b5812f:	jbe    b58139 <_ZN14CInventoryMenu11createMenusEv+0x1759>
  b58131:	mov    0x3058(%rsp),%rdx
  b58139:	mov    $0xfe603a,%eax
  b5813e:	xchg   %ax,%ax
  b58140:	movzbl (%rax),%ecx
  b58143:	add    $0x1,%rax
  b58147:	mov    %ecx,(%rdx)
  b58149:	add    $0x4,%rdx
  b5814d:	cmp    $0xfe603f,%rax
  b58153:	jne    b58140 <_ZN14CInventoryMenu11createMenusEv+0x1760>
  b58155:	cmpq   $0x20,0x2fb8(%rsp)
  b5815e:	movq   $0x5,0x2fb0(%rsp)
  b5816a:	lea    0x3c(%r13),%rax
  b5816e:	jbe    b5817c <_ZN14CInventoryMenu11createMenusEv+0x179c>
  b58170:	mov    0x3058(%rsp),%rax
  b58178:	add    $0x14,%rax
  b5817c:	lea    0x3060(%rsp),%r12
  b58184:	movl   $0x0,(%rax)
  b5818a:	mov    $0xb,%esi
  b5818f:	movq   $0x20,0x3068(%rsp)
  b5819b:	movq   $0x0,0x3070(%rsp)
  b581a7:	mov    %r12,%rdi
  b581aa:	movq   $0x0,0x3080(%rsp)
  b581b6:	movq   $0x0,0x3078(%rsp)
  b581c2:	movq   $0x0,0x3108(%rsp)
  b581ce:	movq   $0x0,0x3060(%rsp)
  b581da:	movl   $0x0,0x3088(%rsp)
  b581e5:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b581ea:	cmpq   $0x20,0x3068(%rsp)
  b581f3:	lea    0x28(%r12),%rdx
  b581f8:	jbe    b58202 <_ZN14CInventoryMenu11createMenusEv+0x1822>
  b581fa:	mov    0x3108(%rsp),%rdx
  b58202:	mov    $0xfe602e,%eax
  b58207:	nopw   0x0(%rax,%rax,1)
  b58210:	movzbl (%rax),%ecx
  b58213:	add    $0x1,%rax
  b58217:	mov    %ecx,(%rdx)
  b58219:	add    $0x4,%rdx
  b5821d:	cmp    %rax,%rbp
  b58220:	jne    b58210 <_ZN14CInventoryMenu11createMenusEv+0x1830>
  b58222:	cmpq   $0x20,0x3068(%rsp)
  b5822b:	movq   $0xb,0x3060(%rsp)
  b58237:	lea    0x54(%r12),%rax
  b5823c:	jbe    b5824a <_ZN14CInventoryMenu11createMenusEv+0x186a>
  b5823e:	mov    0x3108(%rsp),%rax
  b58246:	add    $0x2c,%rax
  b5824a:	movl   $0x0,(%rax)
  b58250:	mov    0x30(%rbx),%rdi
  b58254:	mov    %r13,%rdx
  b58257:	mov    %r12,%rsi
  b5825a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5825f:	mov    %r12,%rdi
  b58262:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58267:	mov    %r13,%rdi
  b5826a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5826f:	movl   $0x0,0x40a4(%rsp)
  b5827a:	movl   $0x0,0x40a0(%rsp)
  b58285:	lea    0x40a0(%rsp),%rsi
  b5828d:	movl   $0x0,0x40ac(%rsp)
  b58298:	movl   $0x0,0x40a8(%rsp)
  b582a3:	mov    0x30(%rbx),%rdi
  b582a7:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b582ac:	mov    0x30(%rbx),%rax
  b582b0:	movb   $0x1,0x3e2(%rax)
  b582b7:	mov    0x30(%rbx),%rdi
  b582bb:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b582c0:	lea    0x2da0(%rsp),%rdi
  b582c8:	xor    %esi,%esi
  b582ca:	movq   $0x20,0x2da8(%rsp)
  b582d6:	movq   $0x0,0x2db0(%rsp)
  b582e2:	movq   $0x0,0x2dc0(%rsp)
  b582ee:	movq   $0x0,0x2db8(%rsp)
  b582fa:	movq   $0x0,0x2e48(%rsp)
  b58306:	movq   $0x0,0x2da0(%rsp)
  b58312:	movl   $0x0,0x2dc8(%rsp)
  b5831d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58322:	cmpq   $0x20,0x2da8(%rsp)
  b5832b:	movq   $0x0,0x2da0(%rsp)
  b58337:	ja     b5b430 <_ZN14CInventoryMenu11createMenusEv+0x4a50>
  b5833d:	lea    0x2da0(%rsp),%rax
  b58345:	add    $0x28,%rax
  b58349:	lea    0x2e50(%rsp),%rdi
  b58351:	movl   $0x0,(%rax)
  b58357:	mov    $0xfef83e,%esi
  b5835c:	call   899960 <_ZN5CEGUI6StringC1EPKh>
  b58361:	xor    %r12d,%r12d
  b58364:	cmpb   $0x0,0x48c632(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b5836b:	movq   $0x20,0x2f08(%rsp)
  b58377:	movq   $0x0,0x2f10(%rsp)
  b58383:	movq   $0x0,0x2f20(%rsp)
  b5838f:	mov    $0xfe499e,%eax
  b58394:	movq   $0x0,0x2f18(%rsp)
  b583a0:	movq   $0x0,0x2fa8(%rsp)
  b583ac:	movq   $0x0,0x2f00(%rsp)
  b583b8:	movl   $0x0,0x2f28(%rsp)
  b583c3:	je     b583dd <_ZN14CInventoryMenu11createMenusEv+0x19fd>
  b583c5:	nopl   (%rax)
  b583c8:	movzbl (%rax),%edx
  b583cb:	mov    %rax,%r12
  b583ce:	add    $0x1,%rax
  b583d2:	sub    $0xfe499d,%r12
  b583d9:	test   %dl,%dl
  b583db:	jne    b583c8 <_ZN14CInventoryMenu11createMenusEv+0x19e8>
  b583dd:	cmp    0x8cc03c(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b583e4:	je     b5eac0 <_ZN14CInventoryMenu11createMenusEv+0x80e0>
  b583ea:	mov    %r12,%rax
  b583ed:	mov    $0xfe499d,%edx
  b583f2:	xor    %r13d,%r13d
  b583f5:	jmp    b58404 <_ZN14CInventoryMenu11createMenusEv+0x1a24>
  b583f7:	nopw   0x0(%rax,%rax,1)
  b58400:	add    $0x1,%r13
  b58404:	test   %rax,%rax
  b58407:	je     b584e0 <_ZN14CInventoryMenu11createMenusEv+0x1b00>
  b5840d:	movzbl (%rdx),%ecx
  b58410:	sub    $0x1,%rax
  b58414:	add    $0x1,%rdx
  b58418:	test   %cl,%cl
  b5841a:	jns    b58400 <_ZN14CInventoryMenu11createMenusEv+0x1a20>
  b5841c:	cmp    $0xdf,%cl
  b5841f:	ja     b58470 <_ZN14CInventoryMenu11createMenusEv+0x1a90>
  b58421:	sub    $0x1,%rax
  b58425:	add    $0x1,%rdx
  b58429:	jmp    b58400 <_ZN14CInventoryMenu11createMenusEv+0x1a20>
  b5842b:	nopl   0x0(%rax,%rax,1)
  b58430:	cmp    $0xef,%dl
  b58433:	ja     b58c50 <_ZN14CInventoryMenu11createMenusEv+0x2270>
  b58439:	mov    %edx,%edi
  b5843b:	lea    0x1(%rax),%edx
  b5843e:	shl    $0xc,%edi
  b58441:	movzbl 0xfe499d(%rdx),%edx
  b58448:	and    $0xf000,%edi
  b5844e:	and    $0x3f,%edx
  b58451:	or     %edi,%edx
  b58453:	mov    %eax,%edi
  b58455:	add    $0x2,%eax
  b58458:	movzbl 0xfe499d(%rdi),%edi
  b5845f:	and    $0x3f,%edi
  b58462:	shl    $0x6,%edi
  b58465:	or     %edi,%edx
  b58467:	jmp    b57193 <_ZN14CInventoryMenu11createMenusEv+0x7b3>
  b5846c:	nopl   0x0(%rax)
  b58470:	cmp    $0xef,%cl
  b58473:	ja     b5b070 <_ZN14CInventoryMenu11createMenusEv+0x4690>
  b58479:	sub    $0x2,%rax
  b5847d:	add    $0x2,%rdx
  b58481:	jmp    b58400 <_ZN14CInventoryMenu11createMenusEv+0x1a20>
  b58486:	cs nopw 0x0(%rax,%rax,1)
  b58490:	mov    $0x7,%edi
  b58495:	lea    0x2(%rax),%r8d
  b58499:	and    %edx,%edi
  b5849b:	mov    %eax,%edx
  b5849d:	movzbl 0xfe49dd(%rdx),%edx
  b584a4:	movzbl 0xfe49dd(%r8),%r8d
  b584ac:	shl    $0x12,%edi
  b584af:	and    $0x3f,%edx
  b584b2:	and    $0x3f,%r8d
  b584b6:	shl    $0xc,%edx
  b584b9:	or     %r8d,%edx
  b584bc:	or     %edi,%edx
  b584be:	lea    0x1(%rax),%edi
  b584c1:	add    $0x3,%eax
  b584c4:	movzbl 0xfe49dd(%rdi),%edi
  b584cb:	and    $0x3f,%edi
  b584ce:	shl    $0x6,%edi
  b584d1:	or     %edi,%edx
  b584d3:	jmp    b56c83 <_ZN14CInventoryMenu11createMenusEv+0x2a3>
  b584d8:	nopl   0x0(%rax,%rax,1)
  b584e0:	lea    0x2f00(%rsp),%r14
  b584e8:	mov    %r13,%rsi
  b584eb:	mov    %r14,%rdi
  b584ee:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b584f3:	mov    0x2f08(%rsp),%rcx
  b584fb:	lea    0x28(%r14),%rsi
  b584ff:	cmp    $0x20,%rcx
  b58503:	jbe    b5850d <_ZN14CInventoryMenu11createMenusEv+0x1b2d>
  b58505:	mov    0x2fa8(%rsp),%rsi
  b5850d:	test   %r12,%r12
  b58510:	je     b5b3a0 <_ZN14CInventoryMenu11createMenusEv+0x49c0>
  b58516:	test   %rcx,%rcx
  b58519:	setne  %al
  b5851c:	test   %al,%al
  b5851e:	je     b58590 <_ZN14CInventoryMenu11createMenusEv+0x1bb0>
  b58520:	xor    %edx,%edx
  b58522:	xor    %eax,%eax
  b58524:	jmp    b58549 <_ZN14CInventoryMenu11createMenusEv+0x1b69>
  b58526:	cs nopw 0x0(%rax,%rax,1)
  b58530:	movzbl %dl,%edx
  b58533:	mov    %edx,(%rsi)
  b58535:	mov    %eax,%edx
  b58537:	sub    $0x1,%rcx
  b5853b:	cmp    %r12,%rdx
  b5853e:	jae    b58590 <_ZN14CInventoryMenu11createMenusEv+0x1bb0>
  b58540:	test   %rcx,%rcx
  b58543:	je     b58590 <_ZN14CInventoryMenu11createMenusEv+0x1bb0>
  b58545:	add    $0x4,%rsi
  b58549:	movzbl 0xfe499d(%rdx),%edx
  b58550:	add    $0x1,%eax
  b58553:	test   %dl,%dl
  b58555:	jns    b58530 <_ZN14CInventoryMenu11createMenusEv+0x1b50>
  b58557:	cmp    $0xdf,%dl
  b5855a:	ja     b58990 <_ZN14CInventoryMenu11createMenusEv+0x1fb0>
  b58560:	mov    $0x1f,%edi
  b58565:	sub    $0x1,%rcx
  b58569:	and    %edx,%edi
  b5856b:	mov    %eax,%edx
  b5856d:	add    $0x1,%eax
  b58570:	movzbl 0xfe499d(%rdx),%edx
  b58577:	shl    $0x6,%edi
  b5857a:	and    $0x3f,%edx
  b5857d:	or     %edi,%edx
  b5857f:	mov    %edx,(%rsi)
  b58581:	mov    %eax,%edx
  b58583:	cmp    %r12,%rdx
  b58586:	jb     b58540 <_ZN14CInventoryMenu11createMenusEv+0x1b60>
  b58588:	nopl   0x0(%rax,%rax,1)
  b58590:	cmpq   $0x20,0x2f08(%rsp)
  b58599:	mov    %r13,0x2f00(%rsp)
  b585a1:	lea    0x28(%r14),%rax
  b585a5:	jbe    b585af <_ZN14CInventoryMenu11createMenusEv+0x1bcf>
  b585a7:	mov    0x2fa8(%rsp),%rax
  b585af:	movl   $0x0,(%rax,%r13,4)
  b585b7:	mov    0x8cc0a2(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b585be:	lea    0x2da0(%rsp),%rcx
  b585c6:	lea    0x2e50(%rsp),%rdx
  b585ce:	mov    %r14,%rsi
  b585d1:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b585d6:	mov    %rax,0x38(%rbx)
  b585da:	mov    %r14,%rdi
  b585dd:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b585e2:	lea    0x2e50(%rsp),%rdi
  b585ea:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b585ef:	lea    0x2da0(%rsp),%rdi
  b585f7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b585fc:	mov    0x38(%rbx),%rsi
  b58600:	mov    0x28(%rbx),%rdi
  b58604:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b58609:	lea    0x4090(%rsp),%r12
  b58611:	mov    0x28(%rbx),%rsi
  b58615:	mov    %r12,%rdi
  b58618:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5861d:	mov    0x38(%rbx),%rdi
  b58621:	mov    %r12,%rsi
  b58624:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b58629:	lea    0x2c40(%rsp),%r13
  b58631:	mov    $0x5,%esi
  b58636:	movq   $0x20,0x2c48(%rsp)
  b58642:	movq   $0x0,0x2c50(%rsp)
  b5864e:	movq   $0x0,0x2c60(%rsp)
  b5865a:	mov    %r13,%rdi
  b5865d:	movq   $0x0,0x2c58(%rsp)
  b58669:	movq   $0x0,0x2ce8(%rsp)
  b58675:	movq   $0x0,0x2c40(%rsp)
  b58681:	movl   $0x0,0x2c68(%rsp)
  b5868c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58691:	cmpq   $0x20,0x2c48(%rsp)
  b5869a:	lea    0x28(%r13),%rdx
  b5869e:	jbe    b586a8 <_ZN14CInventoryMenu11createMenusEv+0x1cc8>
  b586a0:	mov    0x2ce8(%rsp),%rdx
  b586a8:	mov    $0xfe603a,%eax
  b586ad:	nopl   (%rax)
  b586b0:	movzbl (%rax),%ecx
  b586b3:	add    $0x1,%rax
  b586b7:	mov    %ecx,(%rdx)
  b586b9:	add    $0x4,%rdx
  b586bd:	cmp    $0xfe603f,%rax
  b586c3:	jne    b586b0 <_ZN14CInventoryMenu11createMenusEv+0x1cd0>
  b586c5:	cmpq   $0x20,0x2c48(%rsp)
  b586ce:	movq   $0x5,0x2c40(%rsp)
  b586da:	lea    0x3c(%r13),%rax
  b586de:	jbe    b586ec <_ZN14CInventoryMenu11createMenusEv+0x1d0c>
  b586e0:	mov    0x2ce8(%rsp),%rax
  b586e8:	add    $0x14,%rax
  b586ec:	lea    0x2cf0(%rsp),%r12
  b586f4:	movl   $0x0,(%rax)
  b586fa:	mov    $0xb,%esi
  b586ff:	movq   $0x20,0x2cf8(%rsp)
  b5870b:	movq   $0x0,0x2d00(%rsp)
  b58717:	mov    %r12,%rdi
  b5871a:	movq   $0x0,0x2d10(%rsp)
  b58726:	movq   $0x0,0x2d08(%rsp)
  b58732:	movq   $0x0,0x2d98(%rsp)
  b5873e:	movq   $0x0,0x2cf0(%rsp)
  b5874a:	movl   $0x0,0x2d18(%rsp)
  b58755:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5875a:	cmpq   $0x20,0x2cf8(%rsp)
  b58763:	lea    0x28(%r12),%rdx
  b58768:	jbe    b58772 <_ZN14CInventoryMenu11createMenusEv+0x1d92>
  b5876a:	mov    0x2d98(%rsp),%rdx
  b58772:	mov    $0xfe602e,%eax
  b58777:	nopw   0x0(%rax,%rax,1)
  b58780:	movzbl (%rax),%ecx
  b58783:	add    $0x1,%rax
  b58787:	mov    %ecx,(%rdx)
  b58789:	add    $0x4,%rdx
  b5878d:	cmp    %rax,%rbp
  b58790:	jne    b58780 <_ZN14CInventoryMenu11createMenusEv+0x1da0>
  b58792:	cmpq   $0x20,0x2cf8(%rsp)
  b5879b:	movq   $0xb,0x2cf0(%rsp)
  b587a7:	lea    0x54(%r12),%rax
  b587ac:	jbe    b587ba <_ZN14CInventoryMenu11createMenusEv+0x1dda>
  b587ae:	mov    0x2d98(%rsp),%rax
  b587b6:	add    $0x2c,%rax
  b587ba:	movl   $0x0,(%rax)
  b587c0:	mov    0x38(%rbx),%rdi
  b587c4:	mov    %r13,%rdx
  b587c7:	mov    %r12,%rsi
  b587ca:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b587cf:	mov    %r12,%rdi
  b587d2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b587d7:	mov    %r13,%rdi
  b587da:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b587df:	movl   $0x0,0x4084(%rsp)
  b587ea:	movl   $0x0,0x4080(%rsp)
  b587f5:	lea    0x4080(%rsp),%rsi
  b587fd:	movl   $0x0,0x408c(%rsp)
  b58808:	movl   $0x0,0x4088(%rsp)
  b58813:	mov    0x38(%rbx),%rdi
  b58817:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5881c:	mov    0x38(%rbx),%rax
  b58820:	movb   $0x1,0x3e2(%rax)
  b58827:	mov    0x38(%rbx),%rdi
  b5882b:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b58830:	lea    0x2a30(%rsp),%rdi
  b58838:	xor    %esi,%esi
  b5883a:	movq   $0x20,0x2a38(%rsp)
  b58846:	movq   $0x0,0x2a40(%rsp)
  b58852:	movq   $0x0,0x2a50(%rsp)
  b5885e:	movq   $0x0,0x2a48(%rsp)
  b5886a:	movq   $0x0,0x2ad8(%rsp)
  b58876:	movq   $0x0,0x2a30(%rsp)
  b58882:	movl   $0x0,0x2a58(%rsp)
  b5888d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58892:	cmpq   $0x20,0x2a38(%rsp)
  b5889b:	movq   $0x0,0x2a30(%rsp)
  b588a7:	ja     b5b510 <_ZN14CInventoryMenu11createMenusEv+0x4b30>
  b588ad:	lea    0x2a30(%rsp),%rax
  b588b5:	add    $0x28,%rax
  b588b9:	movl   $0x0,(%rax)
  b588bf:	xor    %r12d,%r12d
  b588c2:	cmpb   $0x0,0x48c115(%rip)        # fe49de <_ZTI17CSpawnClassParser+0x6de>
  b588c9:	mov    $0xfe49df,%r14d
  b588cf:	movq   $0x20,0x2ae8(%rsp)
  b588db:	movq   $0x0,0x2af0(%rsp)
  b588e7:	movq   $0x0,0x2b00(%rsp)
  b588f3:	movq   $0x0,0x2af8(%rsp)
  b588ff:	mov    %r14,%rax
  b58902:	movq   $0x0,0x2b88(%rsp)
  b5890e:	movq   $0x0,0x2ae0(%rsp)
  b5891a:	movl   $0x0,0x2b08(%rsp)
  b58925:	je     b58945 <_ZN14CInventoryMenu11createMenusEv+0x1f65>
  b58927:	nopw   0x0(%rax,%rax,1)
  b58930:	movzbl (%rax),%edx
  b58933:	mov    %rax,%r12
  b58936:	add    $0x1,%rax
  b5893a:	sub    $0xfe49de,%r12
  b58941:	test   %dl,%dl
  b58943:	jne    b58930 <_ZN14CInventoryMenu11createMenusEv+0x1f50>
  b58945:	cmp    0x8cbad4(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5894c:	je     b5ebe6 <_ZN14CInventoryMenu11createMenusEv+0x8206>
  b58952:	mov    %r12,%rax
  b58955:	mov    $0xfe49de,%edx
  b5895a:	xor    %r13d,%r13d
  b5895d:	jmp    b58964 <_ZN14CInventoryMenu11createMenusEv+0x1f84>
  b5895f:	nop
  b58960:	add    $0x1,%r13
  b58964:	test   %rax,%rax
  b58967:	je     b58a50 <_ZN14CInventoryMenu11createMenusEv+0x2070>
  b5896d:	movzbl (%rdx),%ecx
  b58970:	sub    $0x1,%rax
  b58974:	add    $0x1,%rdx
  b58978:	test   %cl,%cl
  b5897a:	jns    b58960 <_ZN14CInventoryMenu11createMenusEv+0x1f80>
  b5897c:	cmp    $0xdf,%cl
  b5897f:	ja     b589d0 <_ZN14CInventoryMenu11createMenusEv+0x1ff0>
  b58981:	sub    $0x1,%rax
  b58985:	add    $0x1,%rdx
  b58989:	jmp    b58960 <_ZN14CInventoryMenu11createMenusEv+0x1f80>
  b5898b:	nopl   0x0(%rax,%rax,1)
  b58990:	cmp    $0xef,%dl
  b58993:	ja     b5b028 <_ZN14CInventoryMenu11createMenusEv+0x4648>
  b58999:	mov    %edx,%edi
  b5899b:	lea    0x1(%rax),%edx
  b5899e:	shl    $0xc,%edi
  b589a1:	movzbl 0xfe499d(%rdx),%edx
  b589a8:	and    $0xf000,%edi
  b589ae:	and    $0x3f,%edx
  b589b1:	or     %edi,%edx
  b589b3:	mov    %eax,%edi
  b589b5:	add    $0x2,%eax
  b589b8:	movzbl 0xfe499d(%rdi),%edi
  b589bf:	and    $0x3f,%edi
  b589c2:	shl    $0x6,%edi
  b589c5:	or     %edi,%edx
  b589c7:	jmp    b58533 <_ZN14CInventoryMenu11createMenusEv+0x1b53>
  b589cc:	nopl   0x0(%rax)
  b589d0:	cmp    $0xef,%cl
  b589d3:	ja     b5b130 <_ZN14CInventoryMenu11createMenusEv+0x4750>
  b589d9:	sub    $0x2,%rax
  b589dd:	add    $0x2,%rdx
  b589e1:	jmp    b58960 <_ZN14CInventoryMenu11createMenusEv+0x1f80>
  b589e6:	cs nopw 0x0(%rax,%rax,1)
  b589f0:	sub    $0x2,%rax
  b589f4:	add    $0x3,%rdx
  b589f8:	jmp    b56e50 <_ZN14CInventoryMenu11createMenusEv+0x470>
  b589fd:	nopl   (%rax)
  b58a00:	mov    $0x7,%edi
  b58a05:	lea    0x2(%rax),%r8d
  b58a09:	and    %edx,%edi
  b58a0b:	mov    %eax,%edx
  b58a0d:	movzbl 0xfef826(%rdx),%edx
  b58a14:	movzbl 0xfef826(%r8),%r8d
  b58a1c:	shl    $0x12,%edi
  b58a1f:	and    $0x3f,%edx
  b58a22:	and    $0x3f,%r8d
  b58a26:	shl    $0xc,%edx
  b58a29:	or     %r8d,%edx
  b58a2c:	or     %edi,%edx
  b58a2e:	lea    0x1(%rax),%edi
  b58a31:	add    $0x3,%eax
  b58a34:	movzbl 0xfef826(%rdi),%edi
  b58a3b:	and    $0x3f,%edi
  b58a3e:	shl    $0x6,%edi
  b58a41:	or     %edi,%edx
  b58a43:	jmp    b56f93 <_ZN14CInventoryMenu11createMenusEv+0x5b3>
  b58a48:	nopl   0x0(%rax,%rax,1)
  b58a50:	lea    0x2ae0(%rsp),%rdi
  b58a58:	mov    %r13,%rsi
  b58a5b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58a60:	mov    0x2ae8(%rsp),%rcx
  b58a68:	cmp    $0x20,%rcx
  b58a6c:	ja     b5b468 <_ZN14CInventoryMenu11createMenusEv+0x4a88>
  b58a72:	lea    0x2ae0(%rsp),%rsi
  b58a7a:	add    $0x28,%rsi
  b58a7e:	test   %r12,%r12
  b58a81:	je     b5b479 <_ZN14CInventoryMenu11createMenusEv+0x4a99>
  b58a87:	test   %rcx,%rcx
  b58a8a:	setne  %al
  b58a8d:	test   %al,%al
  b58a8f:	je     b58b00 <_ZN14CInventoryMenu11createMenusEv+0x2120>
  b58a91:	xor    %edx,%edx
  b58a93:	xor    %eax,%eax
  b58a95:	jmp    b58ab9 <_ZN14CInventoryMenu11createMenusEv+0x20d9>
  b58a97:	nopw   0x0(%rax,%rax,1)
  b58aa0:	movzbl %dl,%edx
  b58aa3:	mov    %edx,(%rsi)
  b58aa5:	mov    %eax,%edx
  b58aa7:	sub    $0x1,%rcx
  b58aab:	cmp    %r12,%rdx
  b58aae:	jae    b58b00 <_ZN14CInventoryMenu11createMenusEv+0x2120>
  b58ab0:	test   %rcx,%rcx
  b58ab3:	je     b58b00 <_ZN14CInventoryMenu11createMenusEv+0x2120>
  b58ab5:	add    $0x4,%rsi
  b58ab9:	movzbl 0xfe49de(%rdx),%edx
  b58ac0:	add    $0x1,%eax
  b58ac3:	test   %dl,%dl
  b58ac5:	jns    b58aa0 <_ZN14CInventoryMenu11createMenusEv+0x20c0>
  b58ac7:	cmp    $0xdf,%dl
  b58aca:	ja     b58bf0 <_ZN14CInventoryMenu11createMenusEv+0x2210>
  b58ad0:	mov    $0x1f,%edi
  b58ad5:	sub    $0x1,%rcx
  b58ad9:	and    %edx,%edi
  b58adb:	mov    %eax,%edx
  b58add:	add    $0x1,%eax
  b58ae0:	movzbl 0xfe49de(%rdx),%edx
  b58ae7:	shl    $0x6,%edi
  b58aea:	and    $0x3f,%edx
  b58aed:	or     %edi,%edx
  b58aef:	mov    %edx,(%rsi)
  b58af1:	mov    %eax,%edx
  b58af3:	cmp    %r12,%rdx
  b58af6:	jb     b58ab0 <_ZN14CInventoryMenu11createMenusEv+0x20d0>
  b58af8:	nopl   0x0(%rax,%rax,1)
  b58b00:	cmpq   $0x20,0x2ae8(%rsp)
  b58b09:	mov    %r13,0x2ae0(%rsp)
  b58b11:	ja     b5b5f0 <_ZN14CInventoryMenu11createMenusEv+0x4c10>
  b58b17:	lea    0x2ae0(%rsp),%rax
  b58b1f:	add    $0x28,%rax
  b58b23:	movl   $0x0,(%rax,%r13,4)
  b58b2b:	xor    %r12d,%r12d
  b58b2e:	cmpb   $0x0,0x48be68(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b58b35:	movq   $0x20,0x2b98(%rsp)
  b58b41:	movq   $0x0,0x2ba0(%rsp)
  b58b4d:	mov    $0xfe499e,%eax
  b58b52:	movq   $0x0,0x2bb0(%rsp)
  b58b5e:	movq   $0x0,0x2ba8(%rsp)
  b58b6a:	movq   $0x0,0x2c38(%rsp)
  b58b76:	movq   $0x0,0x2b90(%rsp)
  b58b82:	movl   $0x0,0x2bb8(%rsp)
  b58b8d:	je     b58ba5 <_ZN14CInventoryMenu11createMenusEv+0x21c5>
  b58b8f:	nop
  b58b90:	movzbl (%rax),%edx
  b58b93:	mov    %rax,%r12
  b58b96:	add    $0x1,%rax
  b58b9a:	sub    $0xfe499d,%r12
  b58ba1:	test   %dl,%dl
  b58ba3:	jne    b58b90 <_ZN14CInventoryMenu11createMenusEv+0x21b0>
  b58ba5:	cmp    0x8cb874(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b58bac:	je     b5ecc0 <_ZN14CInventoryMenu11createMenusEv+0x82e0>
  b58bb2:	mov    %r12,%rax
  b58bb5:	mov    $0xfe499d,%edx
  b58bba:	xor    %r13d,%r13d
  b58bbd:	jmp    b58bc4 <_ZN14CInventoryMenu11createMenusEv+0x21e4>
  b58bbf:	nop
  b58bc0:	add    $0x1,%r13
  b58bc4:	test   %rax,%rax
  b58bc7:	je     b58cb0 <_ZN14CInventoryMenu11createMenusEv+0x22d0>
  b58bcd:	movzbl (%rdx),%ecx
  b58bd0:	sub    $0x1,%rax
  b58bd4:	add    $0x1,%rdx
  b58bd8:	test   %cl,%cl
  b58bda:	jns    b58bc0 <_ZN14CInventoryMenu11createMenusEv+0x21e0>
  b58bdc:	cmp    $0xdf,%cl
  b58bdf:	ja     b58c30 <_ZN14CInventoryMenu11createMenusEv+0x2250>
  b58be1:	sub    $0x1,%rax
  b58be5:	add    $0x1,%rdx
  b58be9:	jmp    b58bc0 <_ZN14CInventoryMenu11createMenusEv+0x21e0>
  b58beb:	nopl   0x0(%rax,%rax,1)
  b58bf0:	cmp    $0xef,%dl
  b58bf3:	ja     b5b140 <_ZN14CInventoryMenu11createMenusEv+0x4760>
  b58bf9:	mov    %edx,%edi
  b58bfb:	lea    0x1(%rax),%edx
  b58bfe:	shl    $0xc,%edi
  b58c01:	movzbl 0xfe49de(%rdx),%edx
  b58c08:	and    $0xf000,%edi
  b58c0e:	and    $0x3f,%edx
  b58c11:	or     %edi,%edx
  b58c13:	mov    %eax,%edi
  b58c15:	add    $0x2,%eax
  b58c18:	movzbl 0xfe49de(%rdi),%edi
  b58c1f:	and    $0x3f,%edi
  b58c22:	shl    $0x6,%edi
  b58c25:	or     %edi,%edx
  b58c27:	jmp    b58aa3 <_ZN14CInventoryMenu11createMenusEv+0x20c3>
  b58c2c:	nopl   0x0(%rax)
  b58c30:	cmp    $0xef,%cl
  b58c33:	ja     b5b2e0 <_ZN14CInventoryMenu11createMenusEv+0x4900>
  b58c39:	sub    $0x2,%rax
  b58c3d:	add    $0x2,%rdx
  b58c41:	jmp    b58bc0 <_ZN14CInventoryMenu11createMenusEv+0x21e0>
  b58c46:	cs nopw 0x0(%rax,%rax,1)
  b58c50:	mov    $0x7,%edi
  b58c55:	lea    0x2(%rax),%r8d
  b58c59:	and    %edx,%edi
  b58c5b:	mov    %eax,%edx
  b58c5d:	movzbl 0xfe499d(%rdx),%edx
  b58c64:	movzbl 0xfe499d(%r8),%r8d
  b58c6c:	shl    $0x12,%edi
  b58c6f:	and    $0x3f,%edx
  b58c72:	and    $0x3f,%r8d
  b58c76:	shl    $0xc,%edx
  b58c79:	or     %r8d,%edx
  b58c7c:	or     %edi,%edx
  b58c7e:	lea    0x1(%rax),%edi
  b58c81:	add    $0x3,%eax
  b58c84:	movzbl 0xfe499d(%rdi),%edi
  b58c8b:	and    $0x3f,%edi
  b58c8e:	shl    $0x6,%edi
  b58c91:	or     %edi,%edx
  b58c93:	jmp    b57193 <_ZN14CInventoryMenu11createMenusEv+0x7b3>
  b58c98:	nopl   0x0(%rax,%rax,1)
  b58ca0:	sub    $0x2,%rax
  b58ca4:	add    $0x3,%rdx
  b58ca8:	jmp    b570b0 <_ZN14CInventoryMenu11createMenusEv+0x6d0>
  b58cad:	nopl   (%rax)
  b58cb0:	lea    0x2b90(%rsp),%r14
  b58cb8:	mov    %r13,%rsi
  b58cbb:	mov    %r14,%rdi
  b58cbe:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58cc3:	mov    0x2b98(%rsp),%rcx
  b58ccb:	lea    0x28(%r14),%rsi
  b58ccf:	cmp    $0x20,%rcx
  b58cd3:	jbe    b58cdd <_ZN14CInventoryMenu11createMenusEv+0x22fd>
  b58cd5:	mov    0x2c38(%rsp),%rsi
  b58cdd:	test   %r12,%r12
  b58ce0:	je     b5b540 <_ZN14CInventoryMenu11createMenusEv+0x4b60>
  b58ce6:	test   %rcx,%rcx
  b58ce9:	setne  %al
  b58cec:	test   %al,%al
  b58cee:	je     b58d60 <_ZN14CInventoryMenu11createMenusEv+0x2380>
  b58cf0:	xor    %edx,%edx
  b58cf2:	xor    %eax,%eax
  b58cf4:	jmp    b58d19 <_ZN14CInventoryMenu11createMenusEv+0x2339>
  b58cf6:	cs nopw 0x0(%rax,%rax,1)
  b58d00:	movzbl %dl,%edx
  b58d03:	mov    %edx,(%rsi)
  b58d05:	mov    %eax,%edx
  b58d07:	sub    $0x1,%rcx
  b58d0b:	cmp    %r12,%rdx
  b58d0e:	jae    b58d60 <_ZN14CInventoryMenu11createMenusEv+0x2380>
  b58d10:	test   %rcx,%rcx
  b58d13:	je     b58d60 <_ZN14CInventoryMenu11createMenusEv+0x2380>
  b58d15:	add    $0x4,%rsi
  b58d19:	movzbl 0xfe499d(%rdx),%edx
  b58d20:	add    $0x1,%eax
  b58d23:	test   %dl,%dl
  b58d25:	jns    b58d00 <_ZN14CInventoryMenu11createMenusEv+0x2320>
  b58d27:	cmp    $0xdf,%dl
  b58d2a:	ja     b5a490 <_ZN14CInventoryMenu11createMenusEv+0x3ab0>
  b58d30:	mov    $0x1f,%edi
  b58d35:	sub    $0x1,%rcx
  b58d39:	and    %edx,%edi
  b58d3b:	mov    %eax,%edx
  b58d3d:	add    $0x1,%eax
  b58d40:	movzbl 0xfe499d(%rdx),%edx
  b58d47:	shl    $0x6,%edi
  b58d4a:	and    $0x3f,%edx
  b58d4d:	or     %edi,%edx
  b58d4f:	mov    %edx,(%rsi)
  b58d51:	mov    %eax,%edx
  b58d53:	cmp    %r12,%rdx
  b58d56:	jb     b58d10 <_ZN14CInventoryMenu11createMenusEv+0x2330>
  b58d58:	nopl   0x0(%rax,%rax,1)
  b58d60:	cmpq   $0x20,0x2b98(%rsp)
  b58d69:	mov    %r13,0x2b90(%rsp)
  b58d71:	lea    0x28(%r14),%rax
  b58d75:	jbe    b58d7f <_ZN14CInventoryMenu11createMenusEv+0x239f>
  b58d77:	mov    0x2c38(%rsp),%rax
  b58d7f:	movl   $0x0,(%rax,%r13,4)
  b58d87:	mov    0x8cb8d2(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b58d8e:	lea    0x2a30(%rsp),%rcx
  b58d96:	lea    0x2ae0(%rsp),%rdx
  b58d9e:	mov    %r14,%rsi
  b58da1:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b58da6:	mov    %rax,0x40(%rbx)
  b58daa:	mov    %r14,%rdi
  b58dad:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58db2:	lea    0x2ae0(%rsp),%rdi
  b58dba:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58dbf:	lea    0x2a30(%rsp),%rdi
  b58dc7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58dcc:	mov    0x40(%rbx),%rsi
  b58dd0:	mov    0x28(%rbx),%rdi
  b58dd4:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b58dd9:	lea    0x4070(%rsp),%r12
  b58de1:	mov    0x28(%rbx),%rsi
  b58de5:	mov    %r12,%rdi
  b58de8:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b58ded:	mov    0x40(%rbx),%rdi
  b58df1:	mov    %r12,%rsi
  b58df4:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b58df9:	lea    0x28d0(%rsp),%r13
  b58e01:	mov    $0x5,%esi
  b58e06:	movq   $0x20,0x28d8(%rsp)
  b58e12:	movq   $0x0,0x28e0(%rsp)
  b58e1e:	movq   $0x0,0x28f0(%rsp)
  b58e2a:	mov    %r13,%rdi
  b58e2d:	movq   $0x0,0x28e8(%rsp)
  b58e39:	movq   $0x0,0x2978(%rsp)
  b58e45:	movq   $0x0,0x28d0(%rsp)
  b58e51:	movl   $0x0,0x28f8(%rsp)
  b58e5c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58e61:	cmpq   $0x20,0x28d8(%rsp)
  b58e6a:	lea    0x28(%r13),%rdx
  b58e6e:	jbe    b58e78 <_ZN14CInventoryMenu11createMenusEv+0x2498>
  b58e70:	mov    0x2978(%rsp),%rdx
  b58e78:	mov    $0xfe603a,%eax
  b58e7d:	nopl   (%rax)
  b58e80:	movzbl (%rax),%ecx
  b58e83:	add    $0x1,%rax
  b58e87:	mov    %ecx,(%rdx)
  b58e89:	add    $0x4,%rdx
  b58e8d:	cmp    $0xfe603f,%rax
  b58e93:	jne    b58e80 <_ZN14CInventoryMenu11createMenusEv+0x24a0>
  b58e95:	cmpq   $0x20,0x28d8(%rsp)
  b58e9e:	movq   $0x5,0x28d0(%rsp)
  b58eaa:	lea    0x3c(%r13),%rax
  b58eae:	jbe    b58ebc <_ZN14CInventoryMenu11createMenusEv+0x24dc>
  b58eb0:	mov    0x2978(%rsp),%rax
  b58eb8:	add    $0x14,%rax
  b58ebc:	lea    0x2980(%rsp),%r12
  b58ec4:	movl   $0x0,(%rax)
  b58eca:	mov    $0xb,%esi
  b58ecf:	movq   $0x20,0x2988(%rsp)
  b58edb:	movq   $0x0,0x2990(%rsp)
  b58ee7:	mov    %r12,%rdi
  b58eea:	movq   $0x0,0x29a0(%rsp)
  b58ef6:	movq   $0x0,0x2998(%rsp)
  b58f02:	movq   $0x0,0x2a28(%rsp)
  b58f0e:	movq   $0x0,0x2980(%rsp)
  b58f1a:	movl   $0x0,0x29a8(%rsp)
  b58f25:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b58f2a:	cmpq   $0x20,0x2988(%rsp)
  b58f33:	lea    0x28(%r12),%rdx
  b58f38:	jbe    b58f42 <_ZN14CInventoryMenu11createMenusEv+0x2562>
  b58f3a:	mov    0x2a28(%rsp),%rdx
  b58f42:	mov    $0xfe602e,%eax
  b58f47:	nopw   0x0(%rax,%rax,1)
  b58f50:	movzbl (%rax),%ecx
  b58f53:	add    $0x1,%rax
  b58f57:	mov    %ecx,(%rdx)
  b58f59:	add    $0x4,%rdx
  b58f5d:	cmp    %rax,%rbp
  b58f60:	jne    b58f50 <_ZN14CInventoryMenu11createMenusEv+0x2570>
  b58f62:	cmpq   $0x20,0x2988(%rsp)
  b58f6b:	movq   $0xb,0x2980(%rsp)
  b58f77:	lea    0x54(%r12),%rax
  b58f7c:	jbe    b58f8a <_ZN14CInventoryMenu11createMenusEv+0x25aa>
  b58f7e:	mov    0x2a28(%rsp),%rax
  b58f86:	add    $0x2c,%rax
  b58f8a:	movl   $0x0,(%rax)
  b58f90:	mov    0x40(%rbx),%rdi
  b58f94:	mov    %r13,%rdx
  b58f97:	mov    %r12,%rsi
  b58f9a:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b58f9f:	mov    %r12,%rdi
  b58fa2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58fa7:	mov    %r13,%rdi
  b58faa:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b58faf:	movl   $0x0,0x4064(%rsp)
  b58fba:	movl   $0x0,0x4060(%rsp)
  b58fc5:	lea    0x4060(%rsp),%rsi
  b58fcd:	movl   $0x0,0x406c(%rsp)
  b58fd8:	movl   $0x0,0x4068(%rsp)
  b58fe3:	mov    0x40(%rbx),%rdi
  b58fe7:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b58fec:	mov    0x40(%rbx),%rax
  b58ff0:	movb   $0x1,0x3e2(%rax)
  b58ff7:	mov    0x40(%rbx),%rdi
  b58ffb:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b59000:	lea    0x2820(%rsp),%rbp
  b59008:	mov    $0x8,%esi
  b5900d:	movq   $0x20,0x2828(%rsp)
  b59019:	movq   $0x0,0x2830(%rsp)
  b59025:	movq   $0x0,0x2840(%rsp)
  b59031:	mov    %rbp,%rdi
  b59034:	movq   $0x0,0x2838(%rsp)
  b59040:	movq   $0x0,0x28c8(%rsp)
  b5904c:	movq   $0x0,0x2820(%rsp)
  b59058:	movl   $0x0,0x2848(%rsp)
  b59063:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b59068:	cmpq   $0x20,0x2828(%rsp)
  b59071:	lea    0x28(%rbp),%rdx
  b59075:	jbe    b5907f <_ZN14CInventoryMenu11createMenusEv+0x269f>
  b59077:	mov    0x28c8(%rsp),%rdx
  b5907f:	mov    $0xfef808,%eax
  b59084:	nopl   0x0(%rax)
  b59088:	movzbl (%rax),%ecx
  b5908b:	add    $0x1,%rax
  b5908f:	mov    %ecx,(%rdx)
  b59091:	add    $0x4,%rdx
  b59095:	cmp    $0xfef810,%rax
  b5909b:	jne    b59088 <_ZN14CInventoryMenu11createMenusEv+0x26a8>
  b5909d:	cmpq   $0x20,0x2828(%rsp)
  b590a6:	movq   $0x8,0x2820(%rsp)
  b590b2:	lea    0x48(%rbp),%rax
  b590b6:	jbe    b590c4 <_ZN14CInventoryMenu11createMenusEv+0x26e4>
  b590b8:	mov    0x28c8(%rsp),%rax
  b590c0:	add    $0x20,%rax
  b590c4:	movl   $0x0,(%rax)
  b590ca:	mov    0x28(%rbx),%rdi
  b590ce:	mov    %rbp,%rsi
  b590d1:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b590d6:	mov    %rax,0x1d00(%rbx)
  b590dd:	mov    %rbp,%rdi
  b590e0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b590e5:	mov    0x1d00(%rbx),%rdi
  b590ec:	mov    $0x1,%esi
  b590f1:	add    $0x38,%rdi
  b590f5:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b590fa:	mov    0x1d00(%rbx),%rax
  b59101:	movb   $0x1,0x3e2(%rax)
  b59108:	mov    0x1d00(%rbx),%rax
  b5910f:	movb   $0x0,0x213(%rax)
  b59116:	mov    0x1d00(%rbx),%rsi
  b5911d:	mov    0xb0(%rsi),%rdi
  b59124:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  b59129:	lea    0x2770(%rsp),%r12
  b59131:	mov    $0x5,%esi
  b59136:	movq   $0x20,0x2778(%rsp)
  b59142:	movq   $0x0,0x2780(%rsp)
  b5914e:	movq   $0x0,0x2790(%rsp)
  b5915a:	mov    %r12,%rdi
  b5915d:	movq   $0x0,0x2788(%rsp)
  b59169:	movq   $0x0,0x2818(%rsp)
  b59175:	movq   $0x0,0x2770(%rsp)
  b59181:	movl   $0x0,0x2798(%rsp)
  b5918c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b59191:	cmpq   $0x20,0x2778(%rsp)
  b5919a:	lea    0x28(%r12),%rdx
  b5919f:	jbe    b591a9 <_ZN14CInventoryMenu11createMenusEv+0x27c9>
  b591a1:	mov    0x2818(%rsp),%rdx
  b591a9:	mov    $0xfef802,%eax
  b591ae:	xchg   %ax,%ax
  b591b0:	movzbl (%rax),%ecx
  b591b3:	add    $0x1,%rax
  b591b7:	mov    %ecx,(%rdx)
  b591b9:	add    $0x4,%rdx
  b591bd:	cmp    $0xfef807,%rax
  b591c3:	jne    b591b0 <_ZN14CInventoryMenu11createMenusEv+0x27d0>
  b591c5:	cmpq   $0x20,0x2778(%rsp)
  b591ce:	movq   $0x5,0x2770(%rsp)
  b591da:	lea    0x3c(%r12),%rax
  b591df:	jbe    b591ed <_ZN14CInventoryMenu11createMenusEv+0x280d>
  b591e1:	mov    0x2818(%rsp),%rax
  b591e9:	add    $0x14,%rax
  b591ed:	movl   $0x0,(%rax)
  b591f3:	mov    0x28(%rbx),%rdi
  b591f7:	mov    %r12,%rsi
  b591fa:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b591ff:	mov    %r12,%rdi
  b59202:	mov    %rax,%rbp
  b59205:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5920a:	movb   $0x0,0x213(%rbp)
  b59211:	mov    %rbp,%rdi
  b59214:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b59219:	mov    0x38(%rbp),%rax
  b5921d:	mov    $0x20,%edi
  b59222:	mov    0x10(%rax),%r13
  b59226:	call   552d68 <_Znwm@plt>
  b5922b:	lea    0x4460(%rsp),%r12
  b59233:	movq   $0xfefcd0,(%rax)
  b5923a:	movq   $0x0,0x10(%rax)
  b59242:	movq   $0xb4d920,0x8(%rax)
  b5924a:	mov    %rbx,0x18(%rax)
  b5924e:	lea    0x38(%rbp),%rsi
  b59252:	mov    %rax,0x4460(%rsp)
  b5925a:	lea    0x4050(%rsp),%rdi
  b59262:	mov    %r12,%rcx
  b59265:	mov    $0x14247e0,%edx
  b5926a:	call   *%r13
  b5926d:	cmpq   $0x0,0x4050(%rsp)
  b59276:	je     b592cd <_ZN14CInventoryMenu11createMenusEv+0x28ed>
  b59278:	mov    0x4058(%rsp),%rdx
  b59280:	mov    (%rdx),%eax
  b59282:	sub    $0x1,%eax
  b59285:	test   %eax,%eax
  b59287:	mov    %eax,(%rdx)
  b59289:	jne    b592cd <_ZN14CInventoryMenu11createMenusEv+0x28ed>
  b5928b:	mov    0x4050(%rsp),%rbp
  b59293:	test   %rbp,%rbp
  b59296:	je     b592a8 <_ZN14CInventoryMenu11createMenusEv+0x28c8>
  b59298:	mov    %rbp,%rdi
  b5929b:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b592a0:	mov    %rbp,%rdi
  b592a3:	call   553f18 <_ZdlPv@plt>
  b592a8:	mov    0x4058(%rsp),%rdi
  b592b0:	call   553f18 <_ZdlPv@plt>
  b592b5:	movq   $0x0,0x4050(%rsp)
  b592c1:	movq   $0x0,0x4058(%rsp)
  b592cd:	mov    %r12,%rdi
  b592d0:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b592d5:	lea    0x26c0(%rsp),%r12
  b592dd:	mov    $0xe,%esi
  b592e2:	movq   $0x20,0x26c8(%rsp)
  b592ee:	movq   $0x0,0x26d0(%rsp)
  b592fa:	movq   $0x0,0x26e0(%rsp)
  b59306:	mov    %r12,%rdi
  b59309:	movq   $0x0,0x26d8(%rsp)
  b59315:	movq   $0x0,0x2768(%rsp)
  b59321:	movq   $0x0,0x26c0(%rsp)
  b5932d:	movl   $0x0,0x26e8(%rsp)
  b59338:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5933d:	cmpq   $0x20,0x26c8(%rsp)
  b59346:	lea    0x28(%r12),%rdx
  b5934b:	jbe    b59355 <_ZN14CInventoryMenu11createMenusEv+0x2975>
  b5934d:	mov    0x2768(%rsp),%rdx
  b59355:	mov    $0xfef7f3,%eax
  b5935a:	nopw   0x0(%rax,%rax,1)
  b59360:	movzbl (%rax),%ecx
  b59363:	add    $0x1,%rax
  b59367:	mov    %ecx,(%rdx)
  b59369:	add    $0x4,%rdx
  b5936d:	cmp    $0xfef801,%rax
  b59373:	jne    b59360 <_ZN14CInventoryMenu11createMenusEv+0x2980>
  b59375:	cmpq   $0x20,0x26c8(%rsp)
  b5937e:	movq   $0xe,0x26c0(%rsp)
  b5938a:	lea    0x60(%r12),%rax
  b5938f:	jbe    b5939d <_ZN14CInventoryMenu11createMenusEv+0x29bd>
  b59391:	mov    0x2768(%rsp),%rax
  b59399:	add    $0x38,%rax
  b5939d:	movl   $0x0,(%rax)
  b593a3:	mov    0x28(%rbx),%rdi
  b593a7:	mov    %r12,%rsi
  b593aa:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b593af:	mov    %r12,%rdi
  b593b2:	mov    %rax,%rbp
  b593b5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b593ba:	mov    %rbp,%rdi
  b593bd:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b593c2:	movb   $0x0,0x213(%rbp)
  b593c9:	xor    %esi,%esi
  b593cb:	mov    %rbp,%rdi
  b593ce:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b593d3:	lea    0x101c(%rbx),%rax
  b593da:	mov    $0x20,%edi
  b593df:	mov    %rax,0x1d8(%rbp)
  b593e6:	mov    0x38(%rbp),%rax
  b593ea:	mov    0x10(%rax),%r13
  b593ee:	call   552d68 <_Znwm@plt>
  b593f3:	lea    0x4450(%rsp),%r12
  b593fb:	movq   $0xfefcd0,(%rax)
  b59402:	movq   $0x0,0x10(%rax)
  b5940a:	movq   $0xb45810,0x8(%rax)
  b59412:	mov    %rbx,0x18(%rax)
  b59416:	lea    0x38(%rbp),%rsi
  b5941a:	mov    %rax,0x4450(%rsp)
  b59422:	lea    0x4040(%rsp),%rdi
  b5942a:	mov    %r12,%rcx
  b5942d:	mov    $0x14247e0,%edx
  b59432:	call   *%r13
  b59435:	cmpq   $0x0,0x4040(%rsp)
  b5943e:	je     b59495 <_ZN14CInventoryMenu11createMenusEv+0x2ab5>
  b59440:	mov    0x4048(%rsp),%rdx
  b59448:	mov    (%rdx),%eax
  b5944a:	sub    $0x1,%eax
  b5944d:	test   %eax,%eax
  b5944f:	mov    %eax,(%rdx)
  b59451:	jne    b59495 <_ZN14CInventoryMenu11createMenusEv+0x2ab5>
  b59453:	mov    0x4040(%rsp),%rbp
  b5945b:	test   %rbp,%rbp
  b5945e:	je     b59470 <_ZN14CInventoryMenu11createMenusEv+0x2a90>
  b59460:	mov    %rbp,%rdi
  b59463:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59468:	mov    %rbp,%rdi
  b5946b:	call   553f18 <_ZdlPv@plt>
  b59470:	mov    0x4048(%rsp),%rdi
  b59478:	call   553f18 <_ZdlPv@plt>
  b5947d:	movq   $0x0,0x4040(%rsp)
  b59489:	movq   $0x0,0x4048(%rsp)
  b59495:	mov    %r12,%rdi
  b59498:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5949d:	lea    0x2610(%rsp),%r12
  b594a5:	mov    $0xa,%esi
  b594aa:	movq   $0x20,0x2618(%rsp)
  b594b6:	movq   $0x0,0x2620(%rsp)
  b594c2:	movq   $0x0,0x2630(%rsp)
  b594ce:	mov    %r12,%rdi
  b594d1:	movq   $0x0,0x2628(%rsp)
  b594dd:	movq   $0x0,0x26b8(%rsp)
  b594e9:	movq   $0x0,0x2610(%rsp)
  b594f5:	movl   $0x0,0x2638(%rsp)
  b59500:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b59505:	cmpq   $0x20,0x2618(%rsp)
  b5950e:	lea    0x28(%r12),%rdx
  b59513:	jbe    b5951d <_ZN14CInventoryMenu11createMenusEv+0x2b3d>
  b59515:	mov    0x26b8(%rsp),%rdx
  b5951d:	mov    $0xfef7e8,%eax
  b59522:	nopw   0x0(%rax,%rax,1)
  b59528:	movzbl (%rax),%ecx
  b5952b:	add    $0x1,%rax
  b5952f:	mov    %ecx,(%rdx)
  b59531:	add    $0x4,%rdx
  b59535:	cmp    $0xfef7f2,%rax
  b5953b:	jne    b59528 <_ZN14CInventoryMenu11createMenusEv+0x2b48>
  b5953d:	cmpq   $0x20,0x2618(%rsp)
  b59546:	movq   $0xa,0x2610(%rsp)
  b59552:	lea    0x50(%r12),%rax
  b59557:	jbe    b59565 <_ZN14CInventoryMenu11createMenusEv+0x2b85>
  b59559:	mov    0x26b8(%rsp),%rax
  b59561:	add    $0x28,%rax
  b59565:	movl   $0x0,(%rax)
  b5956b:	mov    0x28(%rbx),%rdi
  b5956f:	mov    %r12,%rsi
  b59572:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b59577:	mov    %r12,%rdi
  b5957a:	mov    %rax,%rbp
  b5957d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b59582:	movb   $0x0,0x213(%rbp)
  b59589:	mov    %rbp,%rdi
  b5958c:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b59591:	mov    0x38(%rbp),%rax
  b59595:	mov    $0x20,%edi
  b5959a:	mov    0x10(%rax),%r14
  b5959e:	call   552d68 <_Znwm@plt>
  b595a3:	lea    0x38(%rbp),%r12
  b595a7:	lea    0x4440(%rsp),%r13
  b595af:	movq   $0xfefcd0,(%rax)
  b595b6:	movq   $0x0,0x10(%rax)
  b595be:	movq   $0xb45860,0x8(%rax)
  b595c6:	lea    0x4030(%rsp),%rdi
  b595ce:	mov    %rbx,0x18(%rax)
  b595d2:	mov    %r13,%rcx
  b595d5:	mov    %rax,0x4440(%rsp)
  b595dd:	mov    $0x14247e0,%edx
  b595e2:	mov    %r12,%rsi
  b595e5:	call   *%r14
  b595e8:	cmpq   $0x0,0x4030(%rsp)
  b595f1:	je     b59648 <_ZN14CInventoryMenu11createMenusEv+0x2c68>
  b595f3:	mov    0x4038(%rsp),%rdx
  b595fb:	mov    (%rdx),%eax
  b595fd:	sub    $0x1,%eax
  b59600:	test   %eax,%eax
  b59602:	mov    %eax,(%rdx)
  b59604:	jne    b59648 <_ZN14CInventoryMenu11createMenusEv+0x2c68>
  b59606:	mov    0x4030(%rsp),%r14
  b5960e:	test   %r14,%r14
  b59611:	je     b59623 <_ZN14CInventoryMenu11createMenusEv+0x2c43>
  b59613:	mov    %r14,%rdi
  b59616:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5961b:	mov    %r14,%rdi
  b5961e:	call   553f18 <_ZdlPv@plt>
  b59623:	mov    0x4038(%rsp),%rdi
  b5962b:	call   553f18 <_ZdlPv@plt>
  b59630:	movq   $0x0,0x4030(%rsp)
  b5963c:	movq   $0x0,0x4038(%rsp)
  b59648:	mov    %r13,%rdi
  b5964b:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59650:	mov    0x38(%rbp),%rax
  b59654:	mov    $0x20,%edi
  b59659:	mov    0x10(%rax),%r14
  b5965d:	call   552d68 <_Znwm@plt>
  b59662:	lea    0x4430(%rsp),%r13
  b5966a:	movq   $0xfefcd0,(%rax)
  b59671:	movq   $0x0,0x10(%rax)
  b59679:	movq   $0xb45870,0x8(%rax)
  b59681:	mov    %rbx,0x18(%rax)
  b59685:	lea    0x4020(%rsp),%rdi
  b5968d:	mov    %rax,0x4430(%rsp)
  b59695:	mov    %r13,%rcx
  b59698:	mov    $0x14241c0,%edx
  b5969d:	mov    %r12,%rsi
  b596a0:	call   *%r14
  b596a3:	cmpq   $0x0,0x4020(%rsp)
  b596ac:	je     b59703 <_ZN14CInventoryMenu11createMenusEv+0x2d23>
  b596ae:	mov    0x4028(%rsp),%rdx
  b596b6:	mov    (%rdx),%eax
  b596b8:	sub    $0x1,%eax
  b596bb:	test   %eax,%eax
  b596bd:	mov    %eax,(%rdx)
  b596bf:	jne    b59703 <_ZN14CInventoryMenu11createMenusEv+0x2d23>
  b596c1:	mov    0x4020(%rsp),%r14
  b596c9:	test   %r14,%r14
  b596cc:	je     b596de <_ZN14CInventoryMenu11createMenusEv+0x2cfe>
  b596ce:	mov    %r14,%rdi
  b596d1:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b596d6:	mov    %r14,%rdi
  b596d9:	call   553f18 <_ZdlPv@plt>
  b596de:	mov    0x4028(%rsp),%rdi
  b596e6:	call   553f18 <_ZdlPv@plt>
  b596eb:	movq   $0x0,0x4020(%rsp)
  b596f7:	movq   $0x0,0x4028(%rsp)
  b59703:	mov    %r13,%rdi
  b59706:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5970b:	mov    0x38(%rbp),%rax
  b5970f:	mov    $0x20,%edi
  b59714:	mov    0x10(%rax),%r13
  b59718:	call   552d68 <_Znwm@plt>
  b5971d:	lea    0x4420(%rsp),%rbp
  b59725:	movq   $0xfefcd0,(%rax)
  b5972c:	movq   $0x0,0x10(%rax)
  b59734:	movq   $0xb45870,0x8(%rax)
  b5973c:	mov    %rbx,0x18(%rax)
  b59740:	lea    0x4010(%rsp),%rdi
  b59748:	mov    %rax,0x4420(%rsp)
  b59750:	mov    %rbp,%rcx
  b59753:	mov    $0x1423700,%edx
  b59758:	mov    %r12,%rsi
  b5975b:	call   *%r13
  b5975e:	cmpq   $0x0,0x4010(%rsp)
  b59767:	je     b597be <_ZN14CInventoryMenu11createMenusEv+0x2dde>
  b59769:	mov    0x4018(%rsp),%rdx
  b59771:	mov    (%rdx),%eax
  b59773:	sub    $0x1,%eax
  b59776:	test   %eax,%eax
  b59778:	mov    %eax,(%rdx)
  b5977a:	jne    b597be <_ZN14CInventoryMenu11createMenusEv+0x2dde>
  b5977c:	mov    0x4010(%rsp),%r12
  b59784:	test   %r12,%r12
  b59787:	je     b59799 <_ZN14CInventoryMenu11createMenusEv+0x2db9>
  b59789:	mov    %r12,%rdi
  b5978c:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59791:	mov    %r12,%rdi
  b59794:	call   553f18 <_ZdlPv@plt>
  b59799:	mov    0x4018(%rsp),%rdi
  b597a1:	call   553f18 <_ZdlPv@plt>
  b597a6:	movq   $0x0,0x4010(%rsp)
  b597b2:	movq   $0x0,0x4018(%rsp)
  b597be:	mov    %rbp,%rdi
  b597c1:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b597c6:	lea    0x2560(%rsp),%r12
  b597ce:	mov    $0xb,%esi
  b597d3:	movq   $0x20,0x2568(%rsp)
  b597df:	movq   $0x0,0x2570(%rsp)
  b597eb:	movq   $0x0,0x2580(%rsp)
  b597f7:	mov    %r12,%rdi
  b597fa:	movq   $0x0,0x2578(%rsp)
  b59806:	movq   $0x0,0x2608(%rsp)
  b59812:	movq   $0x0,0x2560(%rsp)
  b5981e:	movl   $0x0,0x2588(%rsp)
  b59829:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5982e:	cmpq   $0x20,0x2568(%rsp)
  b59837:	lea    0x28(%r12),%rdx
  b5983c:	jbe    b59846 <_ZN14CInventoryMenu11createMenusEv+0x2e66>
  b5983e:	mov    0x2608(%rsp),%rdx
  b59846:	mov    $0xfef7dc,%eax
  b5984b:	nopl   0x0(%rax,%rax,1)
  b59850:	movzbl (%rax),%ecx
  b59853:	add    $0x1,%rax
  b59857:	mov    %ecx,(%rdx)
  b59859:	add    $0x4,%rdx
  b5985d:	cmp    $0xfef7e7,%rax
  b59863:	jne    b59850 <_ZN14CInventoryMenu11createMenusEv+0x2e70>
  b59865:	cmpq   $0x20,0x2568(%rsp)
  b5986e:	movq   $0xb,0x2560(%rsp)
  b5987a:	lea    0x54(%r12),%rax
  b5987f:	jbe    b5988d <_ZN14CInventoryMenu11createMenusEv+0x2ead>
  b59881:	mov    0x2608(%rsp),%rax
  b59889:	add    $0x2c,%rax
  b5988d:	movl   $0x0,(%rax)
  b59893:	mov    0x28(%rbx),%rdi
  b59897:	mov    %r12,%rsi
  b5989a:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5989f:	mov    %r12,%rdi
  b598a2:	mov    %rax,%rbp
  b598a5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b598aa:	movb   $0x0,0x213(%rbp)
  b598b1:	mov    %rbp,%rdi
  b598b4:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b598b9:	mov    0x38(%rbp),%rax
  b598bd:	mov    $0x20,%edi
  b598c2:	mov    0x10(%rax),%r14
  b598c6:	call   552d68 <_Znwm@plt>
  b598cb:	lea    0x38(%rbp),%r12
  b598cf:	lea    0x4410(%rsp),%r13
  b598d7:	movq   $0xfefcd0,(%rax)
  b598de:	movq   $0x0,0x10(%rax)
  b598e6:	movq   $0xb45880,0x8(%rax)
  b598ee:	lea    0x4000(%rsp),%rdi
  b598f6:	mov    %rbx,0x18(%rax)
  b598fa:	mov    %r13,%rcx
  b598fd:	mov    %rax,0x4410(%rsp)
  b59905:	mov    $0x14247e0,%edx
  b5990a:	mov    %r12,%rsi
  b5990d:	call   *%r14
  b59910:	cmpq   $0x0,0x4000(%rsp)
  b59919:	je     b59970 <_ZN14CInventoryMenu11createMenusEv+0x2f90>
  b5991b:	mov    0x4008(%rsp),%rdx
  b59923:	mov    (%rdx),%eax
  b59925:	sub    $0x1,%eax
  b59928:	test   %eax,%eax
  b5992a:	mov    %eax,(%rdx)
  b5992c:	jne    b59970 <_ZN14CInventoryMenu11createMenusEv+0x2f90>
  b5992e:	mov    0x4000(%rsp),%r14
  b59936:	test   %r14,%r14
  b59939:	je     b5994b <_ZN14CInventoryMenu11createMenusEv+0x2f6b>
  b5993b:	mov    %r14,%rdi
  b5993e:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59943:	mov    %r14,%rdi
  b59946:	call   553f18 <_ZdlPv@plt>
  b5994b:	mov    0x4008(%rsp),%rdi
  b59953:	call   553f18 <_ZdlPv@plt>
  b59958:	movq   $0x0,0x4000(%rsp)
  b59964:	movq   $0x0,0x4008(%rsp)
  b59970:	mov    %r13,%rdi
  b59973:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59978:	mov    0x38(%rbp),%rax
  b5997c:	mov    $0x20,%edi
  b59981:	mov    0x10(%rax),%r14
  b59985:	call   552d68 <_Znwm@plt>
  b5998a:	lea    0x4400(%rsp),%r13
  b59992:	movq   $0xfefcd0,(%rax)
  b59999:	movq   $0x0,0x10(%rax)
  b599a1:	movq   $0xb45890,0x8(%rax)
  b599a9:	mov    %rbx,0x18(%rax)
  b599ad:	lea    0x3ff0(%rsp),%rdi
  b599b5:	mov    %rax,0x4400(%rsp)
  b599bd:	mov    %r13,%rcx
  b599c0:	mov    $0x14241c0,%edx
  b599c5:	mov    %r12,%rsi
  b599c8:	call   *%r14
  b599cb:	cmpq   $0x0,0x3ff0(%rsp)
  b599d4:	je     b59a2b <_ZN14CInventoryMenu11createMenusEv+0x304b>
  b599d6:	mov    0x3ff8(%rsp),%rdx
  b599de:	mov    (%rdx),%eax
  b599e0:	sub    $0x1,%eax
  b599e3:	test   %eax,%eax
  b599e5:	mov    %eax,(%rdx)
  b599e7:	jne    b59a2b <_ZN14CInventoryMenu11createMenusEv+0x304b>
  b599e9:	mov    0x3ff0(%rsp),%r14
  b599f1:	test   %r14,%r14
  b599f4:	je     b59a06 <_ZN14CInventoryMenu11createMenusEv+0x3026>
  b599f6:	mov    %r14,%rdi
  b599f9:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b599fe:	mov    %r14,%rdi
  b59a01:	call   553f18 <_ZdlPv@plt>
  b59a06:	mov    0x3ff8(%rsp),%rdi
  b59a0e:	call   553f18 <_ZdlPv@plt>
  b59a13:	movq   $0x0,0x3ff0(%rsp)
  b59a1f:	movq   $0x0,0x3ff8(%rsp)
  b59a2b:	mov    %r13,%rdi
  b59a2e:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59a33:	mov    0x38(%rbp),%rax
  b59a37:	mov    $0x20,%edi
  b59a3c:	mov    0x10(%rax),%r13
  b59a40:	call   552d68 <_Znwm@plt>
  b59a45:	lea    0x43f0(%rsp),%rbp
  b59a4d:	movq   $0xfefcd0,(%rax)
  b59a54:	movq   $0x0,0x10(%rax)
  b59a5c:	movq   $0xb45890,0x8(%rax)
  b59a64:	mov    %rbx,0x18(%rax)
  b59a68:	lea    0x3fe0(%rsp),%rdi
  b59a70:	mov    %rax,0x43f0(%rsp)
  b59a78:	mov    %rbp,%rcx
  b59a7b:	mov    $0x1423700,%edx
  b59a80:	mov    %r12,%rsi
  b59a83:	call   *%r13
  b59a86:	cmpq   $0x0,0x3fe0(%rsp)
  b59a8f:	je     b59ae6 <_ZN14CInventoryMenu11createMenusEv+0x3106>
  b59a91:	mov    0x3fe8(%rsp),%rdx
  b59a99:	mov    (%rdx),%eax
  b59a9b:	sub    $0x1,%eax
  b59a9e:	test   %eax,%eax
  b59aa0:	mov    %eax,(%rdx)
  b59aa2:	jne    b59ae6 <_ZN14CInventoryMenu11createMenusEv+0x3106>
  b59aa4:	mov    0x3fe0(%rsp),%r12
  b59aac:	test   %r12,%r12
  b59aaf:	je     b59ac1 <_ZN14CInventoryMenu11createMenusEv+0x30e1>
  b59ab1:	mov    %r12,%rdi
  b59ab4:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59ab9:	mov    %r12,%rdi
  b59abc:	call   553f18 <_ZdlPv@plt>
  b59ac1:	mov    0x3fe8(%rsp),%rdi
  b59ac9:	call   553f18 <_ZdlPv@plt>
  b59ace:	movq   $0x0,0x3fe0(%rsp)
  b59ada:	movq   $0x0,0x3fe8(%rsp)
  b59ae6:	mov    %rbp,%rdi
  b59ae9:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59aee:	lea    0x1dd0(%rsp),%rax
  b59af6:	mov    %rbx,0x38(%rsp)
  b59afb:	mov    %rbx,%r15
  b59afe:	xor    %ebp,%ebp
  b59b00:	movl   $0x0,0x10(%rsp)
  b59b08:	add    $0x28,%rax
  b59b0c:	mov    %rax,0x30(%rsp)
  b59b11:	lea    0x1fe0(%rsp),%rax
  b59b19:	add    $0x28,%rax
  b59b1d:	mov    %rax,0x28(%rsp)
  b59b22:	lea    0x21f0(%rsp),%rax
  b59b2a:	add    $0x28,%rax
  b59b2e:	mov    %rax,0x20(%rsp)
  b59b33:	jmp    b59b53 <_ZN14CInventoryMenu11createMenusEv+0x3173>
  b59b35:	nopl   (%rax)
  b59b38:	addl   $0x1,0x10(%rsp)
  b59b3d:	add    $0x8,%rbp
  b59b41:	add    $0xb0,%r15
  b59b48:	cmpl   $0xc,0x10(%rsp)
  b59b4d:	je     b5b600 <_ZN14CInventoryMenu11createMenusEv+0x4c20>
  b59b53:	movq   $0x0,0x1028(%rbx,%rbp,1)
  b59b5f:	movq   $0x0,0x12b8(%rbx,%rbp,1)
  b59b6b:	movq   $0x0,0x17d8(%rbx,%rbp,1)
  b59b77:	movq   $0x0,0x1548(%rbx,%rbp,1)
  b59b83:	mov    0x14c6b20(%rbp),%rax
  b59b8a:	cmpq   $0x0,-0x18(%rax)
  b59b8f:	je     b59b38 <_ZN14CInventoryMenu11createMenusEv+0x3158>
  b59b91:	mov    0x10(%rsp),%r14d
  b59b96:	movq   $0x20,0x24b8(%rsp)
  b59ba2:	lea    0x24b0(%rsp),%rdi
  b59baa:	movq   $0x0,0x24c0(%rsp)
  b59bb6:	movq   $0x0,0x24d0(%rsp)
  b59bc2:	movq   $0x0,0x24c8(%rsp)
  b59bce:	movq   $0x0,0x2558(%rsp)
  b59bda:	movq   $0x0,0x24b0(%rsp)
  b59be6:	movl   $0x0,0x24d8(%rsp)
  b59bf1:	mov    -0x18(%rax),%r13
  b59bf5:	lea    0x14c6b20(,%r14,8),%r12
  b59bfd:	mov    %r13,%rsi
  b59c00:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b59c05:	cmpq   $0x20,0x24b8(%rsp)
  b59c0e:	mov    %r13,0x24b0(%rsp)
  b59c16:	ja     b5b2d0 <_ZN14CInventoryMenu11createMenusEv+0x48f0>
  b59c1c:	lea    0x24b0(%rsp),%rax
  b59c24:	add    $0x28,%rax
  b59c28:	test   %r13,%r13
  b59c2b:	movl   $0x0,(%rax,%r13,4)
  b59c33:	je     b59c7b <_ZN14CInventoryMenu11createMenusEv+0x329b>
  b59c35:	lea    0x24b0(%rsp),%rcx
  b59c3d:	sub    $0x1,%r13
  b59c41:	add    $0x28,%rcx
  b59c45:	jmp    b59c54 <_ZN14CInventoryMenu11createMenusEv+0x3274>
  b59c47:	nopw   0x0(%rax,%rax,1)
  b59c50:	sub    $0x1,%r13
  b59c54:	mov    (%r12),%rdx
  b59c58:	cmpq   $0x21,0x24b8(%rsp)
  b59c61:	mov    %rcx,%rax
  b59c64:	cmovae 0x2558(%rsp),%rax
  b59c6d:	test   %r13,%r13
  b59c70:	movzbl (%rdx,%r13,1),%edx
  b59c75:	mov    %edx,(%rax,%r13,4)
  b59c79:	jne    b59c50 <_ZN14CInventoryMenu11createMenusEv+0x3270>
  b59c7b:	mov    0x28(%rbx),%rdi
  b59c7f:	lea    0x24b0(%rsp),%rsi
  b59c87:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b59c8c:	lea    0x24b0(%rsp),%rdi
  b59c94:	mov    %rax,%r13
  b59c97:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b59c9c:	movb   $0x0,0x213(%r13)
  b59ca4:	xor    %esi,%esi
  b59ca6:	mov    %r13,%rdi
  b59ca9:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b59cae:	lea    0x80(%rbx,%r14,4),%rax
  b59cb6:	mov    $0x20,%edi
  b59cbb:	mov    %rax,0x1d8(%r13)
  b59cc2:	mov    0x38(%r13),%rax
  b59cc6:	mov    0x10(%rax),%rax
  b59cca:	mov    %rax,0x18(%rsp)
  b59ccf:	call   552d68 <_Znwm@plt>
  b59cd4:	lea    0x38(%r13),%r12
  b59cd8:	movq   $0xfefcd0,(%rax)
  b59cdf:	movq   $0x0,0x10(%rax)
  b59ce7:	movq   $0xb45810,0x8(%rax)
  b59cef:	mov    %rbx,0x18(%rax)
  b59cf3:	lea    0x3fd0(%rsp),%rdi
  b59cfb:	mov    %rax,0x43e0(%rsp)
  b59d03:	lea    0x43e0(%rsp),%rcx
  b59d0b:	mov    $0x14247e0,%edx
  b59d10:	mov    %r12,%rsi
  b59d13:	call   *0x18(%rsp)
  b59d17:	cmpq   $0x0,0x3fd0(%rsp)
  b59d20:	je     b59d7e <_ZN14CInventoryMenu11createMenusEv+0x339e>
  b59d22:	mov    0x3fd8(%rsp),%rdx
  b59d2a:	mov    (%rdx),%eax
  b59d2c:	sub    $0x1,%eax
  b59d2f:	test   %eax,%eax
  b59d31:	mov    %eax,(%rdx)
  b59d33:	jne    b59d7e <_ZN14CInventoryMenu11createMenusEv+0x339e>
  b59d35:	mov    0x3fd0(%rsp),%rax
  b59d3d:	test   %rax,%rax
  b59d40:	mov    %rax,0x18(%rsp)
  b59d45:	je     b59d59 <_ZN14CInventoryMenu11createMenusEv+0x3379>
  b59d47:	mov    %rax,%rdi
  b59d4a:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59d4f:	mov    0x18(%rsp),%rdi
  b59d54:	call   553f18 <_ZdlPv@plt>
  b59d59:	mov    0x3fd8(%rsp),%rdi
  b59d61:	call   553f18 <_ZdlPv@plt>
  b59d66:	movq   $0x0,0x3fd0(%rsp)
  b59d72:	movq   $0x0,0x3fd8(%rsp)
  b59d7e:	lea    0x43e0(%rsp),%rdi
  b59d86:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59d8b:	mov    0x38(%r13),%rax
  b59d8f:	mov    $0x20,%edi
  b59d94:	mov    0x10(%rax),%rax
  b59d98:	mov    %rax,0x18(%rsp)
  b59d9d:	call   552d68 <_Znwm@plt>
  b59da2:	movq   $0xfefcd0,(%rax)
  b59da9:	movq   $0x0,0x10(%rax)
  b59db1:	lea    0x3fc0(%rsp),%rdi
  b59db9:	movq   $0xb4d590,0x8(%rax)
  b59dc1:	mov    %rbx,0x18(%rax)
  b59dc5:	lea    0x43d0(%rsp),%rcx
  b59dcd:	mov    %rax,0x43d0(%rsp)
  b59dd5:	mov    $0x1423b80,%edx
  b59dda:	mov    %r12,%rsi
  b59ddd:	call   *0x18(%rsp)
  b59de1:	cmpq   $0x0,0x3fc0(%rsp)
  b59dea:	je     b59e48 <_ZN14CInventoryMenu11createMenusEv+0x3468>
  b59dec:	mov    0x3fc8(%rsp),%rdx
  b59df4:	mov    (%rdx),%eax
  b59df6:	sub    $0x1,%eax
  b59df9:	test   %eax,%eax
  b59dfb:	mov    %eax,(%rdx)
  b59dfd:	jne    b59e48 <_ZN14CInventoryMenu11createMenusEv+0x3468>
  b59dff:	mov    0x3fc0(%rsp),%rax
  b59e07:	test   %rax,%rax
  b59e0a:	mov    %rax,0x18(%rsp)
  b59e0f:	je     b59e23 <_ZN14CInventoryMenu11createMenusEv+0x3443>
  b59e11:	mov    %rax,%rdi
  b59e14:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59e19:	mov    0x18(%rsp),%rdi
  b59e1e:	call   553f18 <_ZdlPv@plt>
  b59e23:	mov    0x3fc8(%rsp),%rdi
  b59e2b:	call   553f18 <_ZdlPv@plt>
  b59e30:	movq   $0x0,0x3fc0(%rsp)
  b59e3c:	movq   $0x0,0x3fc8(%rsp)
  b59e48:	lea    0x43d0(%rsp),%rdi
  b59e50:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59e55:	mov    0x38(%r13),%rax
  b59e59:	mov    $0x20,%edi
  b59e5e:	mov    0x10(%rax),%rax
  b59e62:	mov    %rax,0x18(%rsp)
  b59e67:	call   552d68 <_Znwm@plt>
  b59e6c:	movq   $0xfefcd0,(%rax)
  b59e73:	movq   $0x0,0x10(%rax)
  b59e7b:	lea    0x3fb0(%rsp),%rdi
  b59e83:	movq   $0xb4d590,0x8(%rax)
  b59e8b:	mov    %rbx,0x18(%rax)
  b59e8f:	lea    0x43c0(%rsp),%rcx
  b59e97:	mov    %rax,0x43c0(%rsp)
  b59e9f:	mov    $0x1424020,%edx
  b59ea4:	mov    %r12,%rsi
  b59ea7:	call   *0x18(%rsp)
  b59eab:	cmpq   $0x0,0x3fb0(%rsp)
  b59eb4:	je     b59f12 <_ZN14CInventoryMenu11createMenusEv+0x3532>
  b59eb6:	mov    0x3fb8(%rsp),%rdx
  b59ebe:	mov    (%rdx),%eax
  b59ec0:	sub    $0x1,%eax
  b59ec3:	test   %eax,%eax
  b59ec5:	mov    %eax,(%rdx)
  b59ec7:	jne    b59f12 <_ZN14CInventoryMenu11createMenusEv+0x3532>
  b59ec9:	mov    0x3fb0(%rsp),%rax
  b59ed1:	test   %rax,%rax
  b59ed4:	mov    %rax,0x18(%rsp)
  b59ed9:	je     b59eed <_ZN14CInventoryMenu11createMenusEv+0x350d>
  b59edb:	mov    %rax,%rdi
  b59ede:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59ee3:	mov    0x18(%rsp),%rdi
  b59ee8:	call   553f18 <_ZdlPv@plt>
  b59eed:	mov    0x3fb8(%rsp),%rdi
  b59ef5:	call   553f18 <_ZdlPv@plt>
  b59efa:	movq   $0x0,0x3fb0(%rsp)
  b59f06:	movq   $0x0,0x3fb8(%rsp)
  b59f12:	lea    0x43c0(%rsp),%rdi
  b59f1a:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59f1f:	mov    0x38(%r13),%rax
  b59f23:	mov    $0x20,%edi
  b59f28:	mov    0x10(%rax),%rax
  b59f2c:	mov    %rax,0x18(%rsp)
  b59f31:	call   552d68 <_Znwm@plt>
  b59f36:	movq   $0xfefcd0,(%rax)
  b59f3d:	movq   $0x0,0x10(%rax)
  b59f45:	lea    0x3fa0(%rsp),%rdi
  b59f4d:	movq   $0xb45d30,0x8(%rax)
  b59f55:	mov    %rbx,0x18(%rax)
  b59f59:	lea    0x43b0(%rsp),%rcx
  b59f61:	mov    %rax,0x43b0(%rsp)
  b59f69:	mov    $0x1423700,%edx
  b59f6e:	mov    %r12,%rsi
  b59f71:	call   *0x18(%rsp)
  b59f75:	cmpq   $0x0,0x3fa0(%rsp)
  b59f7e:	je     b59fd5 <_ZN14CInventoryMenu11createMenusEv+0x35f5>
  b59f80:	mov    0x3fa8(%rsp),%rdx
  b59f88:	mov    (%rdx),%eax
  b59f8a:	sub    $0x1,%eax
  b59f8d:	test   %eax,%eax
  b59f8f:	mov    %eax,(%rdx)
  b59f91:	jne    b59fd5 <_ZN14CInventoryMenu11createMenusEv+0x35f5>
  b59f93:	mov    0x3fa0(%rsp),%r12
  b59f9b:	test   %r12,%r12
  b59f9e:	je     b59fb0 <_ZN14CInventoryMenu11createMenusEv+0x35d0>
  b59fa0:	mov    %r12,%rdi
  b59fa3:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b59fa8:	mov    %r12,%rdi
  b59fab:	call   553f18 <_ZdlPv@plt>
  b59fb0:	mov    0x3fa8(%rsp),%rdi
  b59fb8:	call   553f18 <_ZdlPv@plt>
  b59fbd:	movq   $0x0,0x3fa0(%rsp)
  b59fc9:	movq   $0x0,0x3fa8(%rsp)
  b59fd5:	lea    0x43b0(%rsp),%rdi
  b59fdd:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b59fe2:	mov    %r13,%rdi
  b59fe5:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b59fea:	lea    0x2400(%rsp),%rdi
  b59ff2:	mov    %r13,0x1028(%rbx,%rbp,1)
  b59ffa:	mov    $0x5,%esi
  b59fff:	movq   $0x20,0x2408(%rsp)
  b5a00b:	movq   $0x0,0x2410(%rsp)
  b5a017:	movq   $0x0,0x2420(%rsp)
  b5a023:	movq   $0x0,0x2418(%rsp)
  b5a02f:	movq   $0x0,0x24a8(%rsp)
  b5a03b:	movq   $0x0,0x2400(%rsp)
  b5a047:	movl   $0x0,0x2428(%rsp)
  b5a052:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a057:	cmpq   $0x20,0x2408(%rsp)
  b5a060:	ja     b5b2c0 <_ZN14CInventoryMenu11createMenusEv+0x48e0>
  b5a066:	lea    0x2400(%rsp),%rdx
  b5a06e:	add    $0x28,%rdx
  b5a072:	mov    $0xfd0c0d,%eax
  b5a077:	nopw   0x0(%rax,%rax,1)
  b5a080:	movzbl (%rax),%ecx
  b5a083:	add    $0x1,%rax
  b5a087:	mov    %ecx,(%rdx)
  b5a089:	add    $0x4,%rdx
  b5a08d:	cmp    $0xfd0c12,%rax
  b5a093:	jne    b5a080 <_ZN14CInventoryMenu11createMenusEv+0x36a0>
  b5a095:	cmpq   $0x20,0x2408(%rsp)
  b5a09e:	movq   $0x5,0x2400(%rsp)
  b5a0aa:	ja     b5b440 <_ZN14CInventoryMenu11createMenusEv+0x4a60>
  b5a0b0:	lea    0x2400(%rsp),%rax
  b5a0b8:	add    $0x3c,%rax
  b5a0bc:	lea    0x2400(%rsp),%rdx
  b5a0c4:	lea    0x2350(%rsp),%rdi
  b5a0cc:	movl   $0x0,(%rax)
  b5a0d2:	mov    %r13,%rsi
  b5a0d5:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5a0da:	lea    (%r14,%r14,4),%rax
  b5a0de:	mov    0x2350(%rsp),%r12
  b5a0e6:	lea    (%r14,%rax,2),%rax
  b5a0ea:	mov    %r12,%rsi
  b5a0ed:	shl    $0x4,%rax
  b5a0f1:	lea    0x1d08(%rbx,%rax,1),%rdi
  b5a0f9:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a0fe:	cmpq   $0x20,0x1d10(%r15)
  b5a106:	mov    %r12,0x1d08(%r15)
  b5a10d:	jbe    b5b2a0 <_ZN14CInventoryMenu11createMenusEv+0x48c0>
  b5a113:	mov    0x1db0(%r15),%rax
  b5a11a:	movl   $0x0,(%rax,%r12,4)
  b5a122:	cmpq   $0x20,0x2358(%rsp)
  b5a12b:	lea    0x0(,%r12,4),%rdx
  b5a133:	ja     b5b278 <_ZN14CInventoryMenu11createMenusEv+0x4898>
  b5a139:	lea    0x2350(%rsp),%rsi
  b5a141:	add    $0x28,%rsi
  b5a145:	cmpq   $0x20,0x1d10(%r15)
  b5a14d:	ja     b5b28e <_ZN14CInventoryMenu11createMenusEv+0x48ae>
  b5a153:	lea    (%r14,%r14,4),%rax
  b5a157:	lea    (%r14,%rax,2),%rax
  b5a15b:	shl    $0x4,%rax
  b5a15f:	lea    0x1d30(%rbx,%rax,1),%rdi
  b5a167:	call   555ab8 <memcpy@plt>
  b5a16c:	lea    0x2350(%rsp),%rdi
  b5a174:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5a179:	lea    0x2400(%rsp),%rdi
  b5a181:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5a186:	mov    %r13,%rdi
  b5a189:	call   552e38 <_ZNK5CEGUI6Window14getTooltipTextEv@plt>
  b5a18e:	mov    %rax,0x18(%rsp)
  b5a193:	mov    (%rax),%r12
  b5a196:	lea    (%r14,%r14,4),%rax
  b5a19a:	lea    (%r14,%rax,2),%rax
  b5a19e:	mov    %r12,%rsi
  b5a1a1:	shl    $0x4,%rax
  b5a1a5:	lea    0x5568(%rbx,%rax,1),%rdi
  b5a1ad:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a1b2:	cmpq   $0x20,0x5570(%r15)
  b5a1ba:	mov    %r12,0x5568(%r15)
  b5a1c1:	jbe    b5b258 <_ZN14CInventoryMenu11createMenusEv+0x4878>
  b5a1c7:	mov    0x5610(%r15),%rax
  b5a1ce:	movl   $0x0,(%rax,%r12,4)
  b5a1d6:	mov    0x18(%rsp),%rax
  b5a1db:	lea    0x0(,%r12,4),%rdx
  b5a1e3:	cmpq   $0x20,0x8(%rax)
  b5a1e8:	jbe    b5b230 <_ZN14CInventoryMenu11createMenusEv+0x4850>
  b5a1ee:	cmpq   $0x20,0x5570(%r15)
  b5a1f6:	mov    0xa8(%rax),%rsi
  b5a1fd:	ja     b5b247 <_ZN14CInventoryMenu11createMenusEv+0x4867>
  b5a203:	lea    (%r14,%r14,4),%rax
  b5a207:	lea    (%r14,%rax,2),%rax
  b5a20b:	shl    $0x4,%rax
  b5a20f:	lea    0x5590(%rbx,%rax,1),%rdi
  b5a217:	call   555ab8 <memcpy@plt>
  b5a21c:	lea    0x2140(%rsp),%rdi
  b5a224:	movq   $0x0,0x17d8(%rbx,%rbp,1)
  b5a230:	xor    %esi,%esi
  b5a232:	movq   $0x20,0x2148(%rsp)
  b5a23e:	movq   $0x0,0x2150(%rsp)
  b5a24a:	movq   $0x0,0x2160(%rsp)
  b5a256:	movq   $0x0,0x2158(%rsp)
  b5a262:	movq   $0x0,0x21e8(%rsp)
  b5a26e:	movq   $0x0,0x2140(%rsp)
  b5a27a:	movl   $0x0,0x2168(%rsp)
  b5a285:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a28a:	cmpq   $0x20,0x2148(%rsp)
  b5a293:	movq   $0x0,0x2140(%rsp)
  b5a29f:	ja     b5b458 <_ZN14CInventoryMenu11createMenusEv+0x4a78>
  b5a2a5:	lea    0x2140(%rsp),%rax
  b5a2ad:	add    $0x28,%rax
  b5a2b1:	lea    0x44ce(%rsp),%rdx
  b5a2b9:	lea    0x43a0(%rsp),%rdi
  b5a2c1:	movl   $0x0,(%rax)
  b5a2c7:	mov    $0xfe468a,%esi
  b5a2cc:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5a2d1:	lea    0x43a0(%rsp),%rsi
  b5a2d9:	lea    0x4390(%rsp),%rdi
  b5a2e1:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5a2e6:	mov    0x4390(%rsp),%rax
  b5a2ee:	movq   $0x20,0x21f8(%rsp)
  b5a2fa:	lea    0x21f0(%rsp),%rdi
  b5a302:	movq   $0x0,0x2200(%rsp)
  b5a30e:	movq   $0x0,0x2210(%rsp)
  b5a31a:	movq   $0x0,0x2208(%rsp)
  b5a326:	movq   $0x0,0x2298(%rsp)
  b5a332:	movq   $0x0,0x21f0(%rsp)
  b5a33e:	movl   $0x0,0x2218(%rsp)
  b5a349:	mov    -0x18(%rax),%r12
  b5a34d:	mov    %r12,%rsi
  b5a350:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a355:	cmpq   $0x21,0x21f8(%rsp)
  b5a35e:	mov    0x20(%rsp),%rax
  b5a363:	cmovae 0x2298(%rsp),%rax
  b5a36c:	test   %r12,%r12
  b5a36f:	mov    %r12,0x21f0(%rsp)
  b5a377:	movl   $0x0,(%rax,%r12,4)
  b5a37f:	je     b5a3bf <_ZN14CInventoryMenu11createMenusEv+0x39df>
  b5a381:	sub    $0x1,%r12
  b5a385:	mov    0x20(%rsp),%rcx
  b5a38a:	jmp    b5a394 <_ZN14CInventoryMenu11createMenusEv+0x39b4>
  b5a38c:	nopl   0x0(%rax)
  b5a390:	sub    $0x1,%r12
  b5a394:	mov    0x4390(%rsp),%rdx
  b5a39c:	cmpq   $0x21,0x21f8(%rsp)
  b5a3a5:	mov    %rcx,%rax
  b5a3a8:	cmovae 0x2298(%rsp),%rax
  b5a3b1:	test   %r12,%r12
  b5a3b4:	movzbl (%rdx,%r12,1),%edx
  b5a3b9:	mov    %edx,(%rax,%r12,4)
  b5a3bd:	jne    b5a390 <_ZN14CInventoryMenu11createMenusEv+0x39b0>
  b5a3bf:	xor    %r12d,%r12d
  b5a3c2:	cmpb   $0x0,0x476836(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5a3c9:	movq   $0x20,0x22a8(%rsp)
  b5a3d5:	movq   $0x0,0x22b0(%rsp)
  b5a3e1:	movq   $0x0,0x22c0(%rsp)
  b5a3ed:	mov    $0xfd0c00,%eax
  b5a3f2:	movq   $0x0,0x22b8(%rsp)
  b5a3fe:	movq   $0x0,0x2348(%rsp)
  b5a40a:	movq   $0x0,0x22a0(%rsp)
  b5a416:	movl   $0x0,0x22c8(%rsp)
  b5a421:	movq   $0xfd0c00,0x18(%rsp)
  b5a42a:	je     b5a445 <_ZN14CInventoryMenu11createMenusEv+0x3a65>
  b5a42c:	nopl   0x0(%rax)
  b5a430:	movzbl (%rax),%edx
  b5a433:	mov    %rax,%r12
  b5a436:	add    $0x1,%rax
  b5a43a:	sub    $0xfd0bff,%r12
  b5a441:	test   %dl,%dl
  b5a443:	jne    b5a430 <_ZN14CInventoryMenu11createMenusEv+0x3a50>
  b5a445:	cmp    0x8c9fd4(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5a44c:	je     b5ea60 <_ZN14CInventoryMenu11createMenusEv+0x8080>
  b5a452:	mov    %r12,%rax
  b5a455:	mov    $0xfd0bff,%edx
  b5a45a:	xor    %r14d,%r14d
  b5a45d:	jmp    b5a464 <_ZN14CInventoryMenu11createMenusEv+0x3a84>
  b5a45f:	nop
  b5a460:	add    $0x1,%r14
  b5a464:	test   %rax,%rax
  b5a467:	je     b5a4f0 <_ZN14CInventoryMenu11createMenusEv+0x3b10>
  b5a46d:	movzbl (%rdx),%ecx
  b5a470:	sub    $0x1,%rax
  b5a474:	add    $0x1,%rdx
  b5a478:	test   %cl,%cl
  b5a47a:	jns    b5a460 <_ZN14CInventoryMenu11createMenusEv+0x3a80>
  b5a47c:	cmp    $0xdf,%cl
  b5a47f:	ja     b5a4d0 <_ZN14CInventoryMenu11createMenusEv+0x3af0>
  b5a481:	sub    $0x1,%rax
  b5a485:	add    $0x1,%rdx
  b5a489:	jmp    b5a460 <_ZN14CInventoryMenu11createMenusEv+0x3a80>
  b5a48b:	nopl   0x0(%rax,%rax,1)
  b5a490:	cmp    $0xef,%dl
  b5a493:	ja     b5b2f0 <_ZN14CInventoryMenu11createMenusEv+0x4910>
  b5a499:	mov    %edx,%edi
  b5a49b:	lea    0x1(%rax),%edx
  b5a49e:	shl    $0xc,%edi
  b5a4a1:	movzbl 0xfe499d(%rdx),%edx
  b5a4a8:	and    $0xf000,%edi
  b5a4ae:	and    $0x3f,%edx
  b5a4b1:	or     %edi,%edx
  b5a4b3:	mov    %eax,%edi
  b5a4b5:	add    $0x2,%eax
  b5a4b8:	movzbl 0xfe499d(%rdi),%edi
  b5a4bf:	and    $0x3f,%edi
  b5a4c2:	shl    $0x6,%edi
  b5a4c5:	or     %edi,%edx
  b5a4c7:	jmp    b58d03 <_ZN14CInventoryMenu11createMenusEv+0x2323>
  b5a4cc:	nopl   0x0(%rax)
  b5a4d0:	cmp    $0xef,%cl
  b5a4d3:	ja     b5b0d0 <_ZN14CInventoryMenu11createMenusEv+0x46f0>
  b5a4d9:	sub    $0x2,%rax
  b5a4dd:	add    $0x2,%rdx
  b5a4e1:	jmp    b5a460 <_ZN14CInventoryMenu11createMenusEv+0x3a80>
  b5a4e6:	cs nopw 0x0(%rax,%rax,1)
  b5a4f0:	lea    0x22a0(%rsp),%rdi
  b5a4f8:	mov    %r14,%rsi
  b5a4fb:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a500:	mov    0x22a8(%rsp),%rcx
  b5a508:	cmp    $0x20,%rcx
  b5a50c:	ja     b5b420 <_ZN14CInventoryMenu11createMenusEv+0x4a40>
  b5a512:	lea    0x22a0(%rsp),%rsi
  b5a51a:	add    $0x28,%rsi
  b5a51e:	test   %r12,%r12
  b5a521:	je     b5b3e0 <_ZN14CInventoryMenu11createMenusEv+0x4a00>
  b5a527:	test   %rcx,%rcx
  b5a52a:	setne  %al
  b5a52d:	test   %al,%al
  b5a52f:	je     b5a5a0 <_ZN14CInventoryMenu11createMenusEv+0x3bc0>
  b5a531:	xor    %edx,%edx
  b5a533:	xor    %eax,%eax
  b5a535:	jmp    b5a559 <_ZN14CInventoryMenu11createMenusEv+0x3b79>
  b5a537:	nopw   0x0(%rax,%rax,1)
  b5a540:	movzbl %dl,%edx
  b5a543:	mov    %edx,(%rsi)
  b5a545:	mov    %eax,%edx
  b5a547:	sub    $0x1,%rcx
  b5a54b:	cmp    %r12,%rdx
  b5a54e:	jae    b5a5a0 <_ZN14CInventoryMenu11createMenusEv+0x3bc0>
  b5a550:	test   %rcx,%rcx
  b5a553:	je     b5a5a0 <_ZN14CInventoryMenu11createMenusEv+0x3bc0>
  b5a555:	add    $0x4,%rsi
  b5a559:	movzbl 0xfd0bff(%rdx),%edx
  b5a560:	add    $0x1,%eax
  b5a563:	test   %dl,%dl
  b5a565:	jns    b5a540 <_ZN14CInventoryMenu11createMenusEv+0x3b60>
  b5a567:	cmp    $0xdf,%dl
  b5a56a:	ja     b5a920 <_ZN14CInventoryMenu11createMenusEv+0x3f40>
  b5a570:	mov    $0x1f,%edi
  b5a575:	sub    $0x1,%rcx
  b5a579:	and    %edx,%edi
  b5a57b:	mov    %eax,%edx
  b5a57d:	add    $0x1,%eax
  b5a580:	movzbl 0xfd0bff(%rdx),%edx
  b5a587:	shl    $0x6,%edi
  b5a58a:	and    $0x3f,%edx
  b5a58d:	or     %edi,%edx
  b5a58f:	mov    %edx,(%rsi)
  b5a591:	mov    %eax,%edx
  b5a593:	cmp    %r12,%rdx
  b5a596:	jb     b5a550 <_ZN14CInventoryMenu11createMenusEv+0x3b70>
  b5a598:	nopl   0x0(%rax,%rax,1)
  b5a5a0:	cmpq   $0x20,0x22a8(%rsp)
  b5a5a9:	mov    %r14,0x22a0(%rsp)
  b5a5b1:	ja     b5b530 <_ZN14CInventoryMenu11createMenusEv+0x4b50>
  b5a5b7:	lea    0x22a0(%rsp),%rax
  b5a5bf:	add    $0x28,%rax
  b5a5c3:	movl   $0x0,(%rax,%r14,4)
  b5a5cb:	mov    0x8ca08e(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5a5d2:	lea    0x2140(%rsp),%rcx
  b5a5da:	lea    0x21f0(%rsp),%rdx
  b5a5e2:	lea    0x22a0(%rsp),%rsi
  b5a5ea:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5a5ef:	lea    0x22a0(%rsp),%rdi
  b5a5f7:	mov    %rax,%r12
  b5a5fa:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5a5ff:	lea    0x21f0(%rsp),%rdi
  b5a607:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5a60c:	mov    0x4390(%rsp),%rdi
  b5a614:	sub    $0x18,%rdi
  b5a618:	cmp    $0x1423a20,%rdi
  b5a61f:	jne    b602db <_ZN14CInventoryMenu11createMenusEv+0x98fb>
  b5a625:	mov    0x43a0(%rsp),%rdi
  b5a62d:	mov    $0x1423a20,%eax
  b5a632:	sub    $0x18,%rdi
  b5a636:	cmp    %rdi,%rax
  b5a639:	jne    b6027a <_ZN14CInventoryMenu11createMenusEv+0x989a>
  b5a63f:	lea    0x2140(%rsp),%rdi
  b5a647:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5a64c:	mov    0x28(%rbx),%rdi
  b5a650:	mov    %r12,%rsi
  b5a653:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5a658:	movb   $0x0,0x213(%r12)
  b5a661:	xor    %esi,%esi
  b5a663:	mov    %r12,%rdi
  b5a666:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5a66b:	lea    0x38(%r12),%rdi
  b5a670:	movb   $0x1,0x3e2(%r12)
  b5a679:	mov    $0x1,%esi
  b5a67e:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5a683:	mov    %r13,%rdi
  b5a686:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5a68b:	mov    %rax,%rsi
  b5a68e:	mov    %r12,%rdi
  b5a691:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5a696:	lea    0x3f90(%rsp),%r14
  b5a69e:	mov    %r13,%rsi
  b5a6a1:	mov    %r14,%rdi
  b5a6a4:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5a6a9:	mov    %r14,%rsi
  b5a6ac:	mov    %r12,%rdi
  b5a6af:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5a6b4:	lea    0x1f30(%rsp),%rdi
  b5a6bc:	mov    %r12,0x12b8(%rbx,%rbp,1)
  b5a6c4:	xor    %esi,%esi
  b5a6c6:	movq   $0x20,0x1f38(%rsp)
  b5a6d2:	movq   $0x0,0x1f40(%rsp)
  b5a6de:	movq   $0x0,0x1f50(%rsp)
  b5a6ea:	movq   $0x0,0x1f48(%rsp)
  b5a6f6:	movq   $0x0,0x1fd8(%rsp)
  b5a702:	movq   $0x0,0x1f30(%rsp)
  b5a70e:	movl   $0x0,0x1f58(%rsp)
  b5a719:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a71e:	cmpq   $0x20,0x1f38(%rsp)
  b5a727:	movq   $0x0,0x1f30(%rsp)
  b5a733:	ja     b5b520 <_ZN14CInventoryMenu11createMenusEv+0x4b40>
  b5a739:	lea    0x1f30(%rsp),%rax
  b5a741:	add    $0x28,%rax
  b5a745:	lea    0x44cd(%rsp),%rdx
  b5a74d:	lea    0x4380(%rsp),%rdi
  b5a755:	movl   $0x0,(%rax)
  b5a75b:	mov    $0xfe468a,%esi
  b5a760:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5a765:	lea    0x4380(%rsp),%rsi
  b5a76d:	lea    0x4370(%rsp),%rdi
  b5a775:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5a77a:	mov    0x4370(%rsp),%rax
  b5a782:	movq   $0x20,0x1fe8(%rsp)
  b5a78e:	lea    0x1fe0(%rsp),%rdi
  b5a796:	movq   $0x0,0x1ff0(%rsp)
  b5a7a2:	movq   $0x0,0x2000(%rsp)
  b5a7ae:	movq   $0x0,0x1ff8(%rsp)
  b5a7ba:	movq   $0x0,0x2088(%rsp)
  b5a7c6:	movq   $0x0,0x1fe0(%rsp)
  b5a7d2:	movl   $0x0,0x2008(%rsp)
  b5a7dd:	mov    -0x18(%rax),%r12
  b5a7e1:	mov    %r12,%rsi
  b5a7e4:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a7e9:	cmpq   $0x21,0x1fe8(%rsp)
  b5a7f2:	mov    0x28(%rsp),%rax
  b5a7f7:	cmovae 0x2088(%rsp),%rax
  b5a800:	test   %r12,%r12
  b5a803:	mov    %r12,0x1fe0(%rsp)
  b5a80b:	movl   $0x0,(%rax,%r12,4)
  b5a813:	je     b5a84f <_ZN14CInventoryMenu11createMenusEv+0x3e6f>
  b5a815:	sub    $0x1,%r12
  b5a819:	mov    0x28(%rsp),%rcx
  b5a81e:	jmp    b5a824 <_ZN14CInventoryMenu11createMenusEv+0x3e44>
  b5a820:	sub    $0x1,%r12
  b5a824:	mov    0x4370(%rsp),%rdx
  b5a82c:	cmpq   $0x21,0x1fe8(%rsp)
  b5a835:	mov    %rcx,%rax
  b5a838:	cmovae 0x2088(%rsp),%rax
  b5a841:	test   %r12,%r12
  b5a844:	movzbl (%rdx,%r12,1),%edx
  b5a849:	mov    %edx,(%rax,%r12,4)
  b5a84d:	jne    b5a820 <_ZN14CInventoryMenu11createMenusEv+0x3e40>
  b5a84f:	xor    %r12d,%r12d
  b5a852:	cmpb   $0x0,0x4763a6(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5a859:	movq   $0x20,0x2098(%rsp)
  b5a865:	movq   $0x0,0x20a0(%rsp)
  b5a871:	movq   $0x0,0x20b0(%rsp)
  b5a87d:	mov    $0xfd0c00,%eax
  b5a882:	movq   $0x0,0x20a8(%rsp)
  b5a88e:	movq   $0x0,0x2138(%rsp)
  b5a89a:	movq   $0x0,0x2090(%rsp)
  b5a8a6:	movl   $0x0,0x20b8(%rsp)
  b5a8b1:	je     b5a8cd <_ZN14CInventoryMenu11createMenusEv+0x3eed>
  b5a8b3:	nopl   0x0(%rax,%rax,1)
  b5a8b8:	movzbl (%rax),%edx
  b5a8bb:	mov    %rax,%r12
  b5a8be:	add    $0x1,%rax
  b5a8c2:	sub    $0xfd0bff,%r12
  b5a8c9:	test   %dl,%dl
  b5a8cb:	jne    b5a8b8 <_ZN14CInventoryMenu11createMenusEv+0x3ed8>
  b5a8cd:	cmp    0x8c9b4c(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5a8d4:	je     b5eb86 <_ZN14CInventoryMenu11createMenusEv+0x81a6>
  b5a8da:	mov    %r12,%rax
  b5a8dd:	mov    $0xfd0bff,%edx
  b5a8e2:	xor    %r14d,%r14d
  b5a8e5:	jmp    b5a8f4 <_ZN14CInventoryMenu11createMenusEv+0x3f14>
  b5a8e7:	nopw   0x0(%rax,%rax,1)
  b5a8f0:	add    $0x1,%r14
  b5a8f4:	test   %rax,%rax
  b5a8f7:	je     b5a980 <_ZN14CInventoryMenu11createMenusEv+0x3fa0>
  b5a8fd:	movzbl (%rdx),%ecx
  b5a900:	sub    $0x1,%rax
  b5a904:	add    $0x1,%rdx
  b5a908:	test   %cl,%cl
  b5a90a:	jns    b5a8f0 <_ZN14CInventoryMenu11createMenusEv+0x3f10>
  b5a90c:	cmp    $0xdf,%cl
  b5a90f:	ja     b5a960 <_ZN14CInventoryMenu11createMenusEv+0x3f80>
  b5a911:	sub    $0x1,%rax
  b5a915:	add    $0x1,%rdx
  b5a919:	jmp    b5a8f0 <_ZN14CInventoryMenu11createMenusEv+0x3f10>
  b5a91b:	nopl   0x0(%rax,%rax,1)
  b5a920:	cmp    $0xef,%dl
  b5a923:	ja     b5b080 <_ZN14CInventoryMenu11createMenusEv+0x46a0>
  b5a929:	mov    %edx,%edi
  b5a92b:	lea    0x1(%rax),%edx
  b5a92e:	shl    $0xc,%edi
  b5a931:	movzbl 0xfd0bff(%rdx),%edx
  b5a938:	and    $0xf000,%edi
  b5a93e:	and    $0x3f,%edx
  b5a941:	or     %edi,%edx
  b5a943:	mov    %eax,%edi
  b5a945:	add    $0x2,%eax
  b5a948:	movzbl 0xfd0bff(%rdi),%edi
  b5a94f:	and    $0x3f,%edi
  b5a952:	shl    $0x6,%edi
  b5a955:	or     %edi,%edx
  b5a957:	jmp    b5a543 <_ZN14CInventoryMenu11createMenusEv+0x3b63>
  b5a95c:	nopl   0x0(%rax)
  b5a960:	cmp    $0xef,%cl
  b5a963:	ja     b5b1e0 <_ZN14CInventoryMenu11createMenusEv+0x4800>
  b5a969:	sub    $0x2,%rax
  b5a96d:	add    $0x2,%rdx
  b5a971:	jmp    b5a8f0 <_ZN14CInventoryMenu11createMenusEv+0x3f10>
  b5a976:	cs nopw 0x0(%rax,%rax,1)
  b5a980:	lea    0x2090(%rsp),%rdi
  b5a988:	mov    %r14,%rsi
  b5a98b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5a990:	mov    0x2098(%rsp),%rcx
  b5a998:	cmp    $0x20,%rcx
  b5a99c:	ja     b5b500 <_ZN14CInventoryMenu11createMenusEv+0x4b20>
  b5a9a2:	lea    0x2090(%rsp),%rsi
  b5a9aa:	add    $0x28,%rsi
  b5a9ae:	test   %r12,%r12
  b5a9b1:	je     b5b4c0 <_ZN14CInventoryMenu11createMenusEv+0x4ae0>
  b5a9b7:	test   %rcx,%rcx
  b5a9ba:	setne  %al
  b5a9bd:	test   %al,%al
  b5a9bf:	je     b5aa30 <_ZN14CInventoryMenu11createMenusEv+0x4050>
  b5a9c1:	xor    %edx,%edx
  b5a9c3:	xor    %eax,%eax
  b5a9c5:	jmp    b5a9e9 <_ZN14CInventoryMenu11createMenusEv+0x4009>
  b5a9c7:	nopw   0x0(%rax,%rax,1)
  b5a9d0:	movzbl %dl,%edx
  b5a9d3:	mov    %edx,(%rsi)
  b5a9d5:	mov    %eax,%edx
  b5a9d7:	sub    $0x1,%rcx
  b5a9db:	cmp    %r12,%rdx
  b5a9de:	jae    b5aa30 <_ZN14CInventoryMenu11createMenusEv+0x4050>
  b5a9e0:	test   %rcx,%rcx
  b5a9e3:	je     b5aa30 <_ZN14CInventoryMenu11createMenusEv+0x4050>
  b5a9e5:	add    $0x4,%rsi
  b5a9e9:	movzbl 0xfd0bff(%rdx),%edx
  b5a9f0:	add    $0x1,%eax
  b5a9f3:	test   %dl,%dl
  b5a9f5:	jns    b5a9d0 <_ZN14CInventoryMenu11createMenusEv+0x3ff0>
  b5a9f7:	cmp    $0xdf,%dl
  b5a9fa:	ja     b5adb0 <_ZN14CInventoryMenu11createMenusEv+0x43d0>
  b5aa00:	mov    $0x1f,%edi
  b5aa05:	sub    $0x1,%rcx
  b5aa09:	and    %edx,%edi
  b5aa0b:	mov    %eax,%edx
  b5aa0d:	add    $0x1,%eax
  b5aa10:	movzbl 0xfd0bff(%rdx),%edx
  b5aa17:	shl    $0x6,%edi
  b5aa1a:	and    $0x3f,%edx
  b5aa1d:	or     %edi,%edx
  b5aa1f:	mov    %edx,(%rsi)
  b5aa21:	mov    %eax,%edx
  b5aa23:	cmp    %r12,%rdx
  b5aa26:	jb     b5a9e0 <_ZN14CInventoryMenu11createMenusEv+0x4000>
  b5aa28:	nopl   0x0(%rax,%rax,1)
  b5aa30:	cmpq   $0x20,0x2098(%rsp)
  b5aa39:	mov    %r14,0x2090(%rsp)
  b5aa41:	ja     b5b5e0 <_ZN14CInventoryMenu11createMenusEv+0x4c00>
  b5aa47:	lea    0x2090(%rsp),%rax
  b5aa4f:	add    $0x28,%rax
  b5aa53:	movl   $0x0,(%rax,%r14,4)
  b5aa5b:	mov    0x8c9bfe(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5aa62:	lea    0x1f30(%rsp),%rcx
  b5aa6a:	lea    0x1fe0(%rsp),%rdx
  b5aa72:	lea    0x2090(%rsp),%rsi
  b5aa7a:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5aa7f:	lea    0x2090(%rsp),%rdi
  b5aa87:	mov    %rax,%r12
  b5aa8a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5aa8f:	lea    0x1fe0(%rsp),%rdi
  b5aa97:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5aa9c:	mov    0x4370(%rsp),%rdi
  b5aaa4:	mov    $0x1423a20,%eax
  b5aaa9:	sub    $0x18,%rdi
  b5aaad:	cmp    %rdi,%rax
  b5aab0:	jne    b6023a <_ZN14CInventoryMenu11createMenusEv+0x985a>
  b5aab6:	mov    0x4380(%rsp),%rdi
  b5aabe:	mov    $0x1423a20,%eax
  b5aac3:	sub    $0x18,%rdi
  b5aac7:	cmp    %rdi,%rax
  b5aaca:	jne    b601b5 <_ZN14CInventoryMenu11createMenusEv+0x97d5>
  b5aad0:	lea    0x1f30(%rsp),%rdi
  b5aad8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5aadd:	mov    0x38(%rbx),%rdi
  b5aae1:	mov    %r12,%rsi
  b5aae4:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5aae9:	movb   $0x0,0x213(%r12)
  b5aaf2:	xor    %esi,%esi
  b5aaf4:	mov    %r12,%rdi
  b5aaf7:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5aafc:	lea    0x38(%r12),%rdi
  b5ab01:	movb   $0x1,0x3e2(%r12)
  b5ab0a:	mov    $0x1,%esi
  b5ab0f:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5ab14:	mov    %r13,%rdi
  b5ab17:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5ab1c:	mov    %rax,%rsi
  b5ab1f:	mov    %r12,%rdi
  b5ab22:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5ab27:	lea    0x3f80(%rsp),%r14
  b5ab2f:	mov    %r13,%rsi
  b5ab32:	mov    %r14,%rdi
  b5ab35:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5ab3a:	mov    %r14,%rsi
  b5ab3d:	mov    %r12,%rdi
  b5ab40:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5ab45:	lea    0x1d20(%rsp),%rdi
  b5ab4d:	mov    %r12,0x1548(%rbx,%rbp,1)
  b5ab55:	xor    %esi,%esi
  b5ab57:	movq   $0x20,0x1d28(%rsp)
  b5ab63:	movq   $0x0,0x1d30(%rsp)
  b5ab6f:	movq   $0x0,0x1d40(%rsp)
  b5ab7b:	movq   $0x0,0x1d38(%rsp)
  b5ab87:	movq   $0x0,0x1dc8(%rsp)
  b5ab93:	movq   $0x0,0x1d20(%rsp)
  b5ab9f:	movl   $0x0,0x1d48(%rsp)
  b5abaa:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5abaf:	cmpq   $0x20,0x1d28(%rsp)
  b5abb8:	movq   $0x0,0x1d20(%rsp)
  b5abc4:	ja     b5b5d0 <_ZN14CInventoryMenu11createMenusEv+0x4bf0>
  b5abca:	lea    0x1d20(%rsp),%rax
  b5abd2:	add    $0x28,%rax
  b5abd6:	lea    0x44cc(%rsp),%rdx
  b5abde:	lea    0x4360(%rsp),%rdi
  b5abe6:	movl   $0x0,(%rax)
  b5abec:	mov    $0xfe468a,%esi
  b5abf1:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5abf6:	lea    0x4360(%rsp),%rsi
  b5abfe:	lea    0x4350(%rsp),%rdi
  b5ac06:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5ac0b:	mov    0x4350(%rsp),%rax
  b5ac13:	movq   $0x20,0x1dd8(%rsp)
  b5ac1f:	lea    0x1dd0(%rsp),%rdi
  b5ac27:	movq   $0x0,0x1de0(%rsp)
  b5ac33:	movq   $0x0,0x1df0(%rsp)
  b5ac3f:	movq   $0x0,0x1de8(%rsp)
  b5ac4b:	movq   $0x0,0x1e78(%rsp)
  b5ac57:	movq   $0x0,0x1dd0(%rsp)
  b5ac63:	movl   $0x0,0x1df8(%rsp)
  b5ac6e:	mov    -0x18(%rax),%r12
  b5ac72:	mov    %r12,%rsi
  b5ac75:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ac7a:	cmpq   $0x21,0x1dd8(%rsp)
  b5ac83:	mov    0x30(%rsp),%rax
  b5ac88:	cmovae 0x1e78(%rsp),%rax
  b5ac91:	test   %r12,%r12
  b5ac94:	mov    %r12,0x1dd0(%rsp)
  b5ac9c:	movl   $0x0,(%rax,%r12,4)
  b5aca4:	je     b5ace7 <_ZN14CInventoryMenu11createMenusEv+0x4307>
  b5aca6:	sub    $0x1,%r12
  b5acaa:	mov    0x30(%rsp),%rcx
  b5acaf:	jmp    b5acbc <_ZN14CInventoryMenu11createMenusEv+0x42dc>
  b5acb1:	nopl   0x0(%rax)
  b5acb8:	sub    $0x1,%r12
  b5acbc:	mov    0x4350(%rsp),%rdx
  b5acc4:	cmpq   $0x21,0x1dd8(%rsp)
  b5accd:	mov    %rcx,%rax
  b5acd0:	cmovae 0x1e78(%rsp),%rax
  b5acd9:	test   %r12,%r12
  b5acdc:	movzbl (%rdx,%r12,1),%edx
  b5ace1:	mov    %edx,(%rax,%r12,4)
  b5ace5:	jne    b5acb8 <_ZN14CInventoryMenu11createMenusEv+0x42d8>
  b5ace7:	xor    %r12d,%r12d
  b5acea:	cmpb   $0x0,0x475f0e(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5acf1:	movq   $0x20,0x1e88(%rsp)
  b5acfd:	movq   $0x0,0x1e90(%rsp)
  b5ad09:	movq   $0x0,0x1ea0(%rsp)
  b5ad15:	mov    $0xfd0c00,%eax
  b5ad1a:	movq   $0x0,0x1e98(%rsp)
  b5ad26:	movq   $0x0,0x1f28(%rsp)
  b5ad32:	movq   $0x0,0x1e80(%rsp)
  b5ad3e:	movl   $0x0,0x1ea8(%rsp)
  b5ad49:	je     b5ad65 <_ZN14CInventoryMenu11createMenusEv+0x4385>
  b5ad4b:	nopl   0x0(%rax,%rax,1)
  b5ad50:	movzbl (%rax),%edx
  b5ad53:	mov    %rax,%r12
  b5ad56:	add    $0x1,%rax
  b5ad5a:	sub    $0xfd0bff,%r12
  b5ad61:	test   %dl,%dl
  b5ad63:	jne    b5ad50 <_ZN14CInventoryMenu11createMenusEv+0x4370>
  b5ad65:	cmp    0x8c96b4(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5ad6c:	je     b5ec60 <_ZN14CInventoryMenu11createMenusEv+0x8280>
  b5ad72:	mov    %r12,%rax
  b5ad75:	mov    $0xfd0bff,%edx
  b5ad7a:	xor    %r14d,%r14d
  b5ad7d:	jmp    b5ad84 <_ZN14CInventoryMenu11createMenusEv+0x43a4>
  b5ad7f:	nop
  b5ad80:	add    $0x1,%r14
  b5ad84:	test   %rax,%rax
  b5ad87:	je     b5ae10 <_ZN14CInventoryMenu11createMenusEv+0x4430>
  b5ad8d:	movzbl (%rdx),%ecx
  b5ad90:	sub    $0x1,%rax
  b5ad94:	add    $0x1,%rdx
  b5ad98:	test   %cl,%cl
  b5ad9a:	jns    b5ad80 <_ZN14CInventoryMenu11createMenusEv+0x43a0>
  b5ad9c:	cmp    $0xdf,%cl
  b5ad9f:	ja     b5adf0 <_ZN14CInventoryMenu11createMenusEv+0x4410>
  b5ada1:	sub    $0x1,%rax
  b5ada5:	add    $0x1,%rdx
  b5ada9:	jmp    b5ad80 <_ZN14CInventoryMenu11createMenusEv+0x43a0>
  b5adab:	nopl   0x0(%rax,%rax,1)
  b5adb0:	cmp    $0xef,%dl
  b5adb3:	ja     b5b190 <_ZN14CInventoryMenu11createMenusEv+0x47b0>
  b5adb9:	mov    %edx,%edi
  b5adbb:	lea    0x1(%rax),%edx
  b5adbe:	shl    $0xc,%edi
  b5adc1:	movzbl 0xfd0bff(%rdx),%edx
  b5adc8:	and    $0xf000,%edi
  b5adce:	and    $0x3f,%edx
  b5add1:	or     %edi,%edx
  b5add3:	mov    %eax,%edi
  b5add5:	add    $0x2,%eax
  b5add8:	movzbl 0xfd0bff(%rdi),%edi
  b5addf:	and    $0x3f,%edi
  b5ade2:	shl    $0x6,%edi
  b5ade5:	or     %edi,%edx
  b5ade7:	jmp    b5a9d3 <_ZN14CInventoryMenu11createMenusEv+0x3ff3>
  b5adec:	nopl   0x0(%rax)
  b5adf0:	cmp    $0xef,%cl
  b5adf3:	ja     b5b340 <_ZN14CInventoryMenu11createMenusEv+0x4960>
  b5adf9:	sub    $0x2,%rax
  b5adfd:	add    $0x2,%rdx
  b5ae01:	jmp    b5ad80 <_ZN14CInventoryMenu11createMenusEv+0x43a0>
  b5ae06:	cs nopw 0x0(%rax,%rax,1)
  b5ae10:	lea    0x1e80(%rsp),%rdi
  b5ae18:	mov    %r14,%rsi
  b5ae1b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ae20:	mov    0x1e88(%rsp),%rcx
  b5ae28:	cmp    $0x20,%rcx
  b5ae2c:	ja     b5b5c0 <_ZN14CInventoryMenu11createMenusEv+0x4be0>
  b5ae32:	lea    0x1e80(%rsp),%rsi
  b5ae3a:	add    $0x28,%rsi
  b5ae3e:	test   %r12,%r12
  b5ae41:	je     b5b580 <_ZN14CInventoryMenu11createMenusEv+0x4ba0>
  b5ae47:	test   %rcx,%rcx
  b5ae4a:	setne  %al
  b5ae4d:	test   %al,%al
  b5ae4f:	je     b5aec0 <_ZN14CInventoryMenu11createMenusEv+0x44e0>
  b5ae51:	xor    %edx,%edx
  b5ae53:	xor    %eax,%eax
  b5ae55:	jmp    b5ae79 <_ZN14CInventoryMenu11createMenusEv+0x4499>
  b5ae57:	nopw   0x0(%rax,%rax,1)
  b5ae60:	movzbl %dl,%edx
  b5ae63:	mov    %edx,(%rsi)
  b5ae65:	mov    %eax,%edx
  b5ae67:	sub    $0x1,%rcx
  b5ae6b:	cmp    %r12,%rdx
  b5ae6e:	jae    b5aec0 <_ZN14CInventoryMenu11createMenusEv+0x44e0>
  b5ae70:	test   %rcx,%rcx
  b5ae73:	je     b5aec0 <_ZN14CInventoryMenu11createMenusEv+0x44e0>
  b5ae75:	add    $0x4,%rsi
  b5ae79:	movzbl 0xfd0bff(%rdx),%edx
  b5ae80:	add    $0x1,%eax
  b5ae83:	test   %dl,%dl
  b5ae85:	jns    b5ae60 <_ZN14CInventoryMenu11createMenusEv+0x4480>
  b5ae87:	cmp    $0xdf,%dl
  b5ae8a:	ja     b5afe8 <_ZN14CInventoryMenu11createMenusEv+0x4608>
  b5ae90:	mov    $0x1f,%edi
  b5ae95:	sub    $0x1,%rcx
  b5ae99:	and    %edx,%edi
  b5ae9b:	mov    %eax,%edx
  b5ae9d:	add    $0x1,%eax
  b5aea0:	movzbl 0xfd0bff(%rdx),%edx
  b5aea7:	shl    $0x6,%edi
  b5aeaa:	and    $0x3f,%edx
  b5aead:	or     %edi,%edx
  b5aeaf:	mov    %edx,(%rsi)
  b5aeb1:	mov    %eax,%edx
  b5aeb3:	cmp    %r12,%rdx
  b5aeb6:	jb     b5ae70 <_ZN14CInventoryMenu11createMenusEv+0x4490>
  b5aeb8:	nopl   0x0(%rax,%rax,1)
  b5aec0:	cmpq   $0x20,0x1e88(%rsp)
  b5aec9:	mov    %r14,0x1e80(%rsp)
  b5aed1:	ja     b5e71c <_ZN14CInventoryMenu11createMenusEv+0x7d3c>
  b5aed7:	lea    0x1e80(%rsp),%rax
  b5aedf:	add    $0x28,%rax
  b5aee3:	movl   $0x0,(%rax,%r14,4)
  b5aeeb:	mov    0x8c976e(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5aef2:	lea    0x1d20(%rsp),%rcx
  b5aefa:	lea    0x1dd0(%rsp),%rdx
  b5af02:	lea    0x1e80(%rsp),%rsi
  b5af0a:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5af0f:	lea    0x1e80(%rsp),%rdi
  b5af17:	mov    %rax,%r12
  b5af1a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5af1f:	lea    0x1dd0(%rsp),%rdi
  b5af27:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5af2c:	mov    0x4350(%rsp),%rdi
  b5af34:	mov    $0x1423a20,%eax
  b5af39:	sub    $0x18,%rdi
  b5af3d:	cmp    %rdi,%rax
  b5af40:	jne    b60335 <_ZN14CInventoryMenu11createMenusEv+0x9955>
  b5af46:	mov    0x4360(%rsp),%rdi
  b5af4e:	mov    $0x1423a20,%eax
  b5af53:	sub    $0x18,%rdi
  b5af57:	cmp    %rdi,%rax
  b5af5a:	jne    b60361 <_ZN14CInventoryMenu11createMenusEv+0x9981>
  b5af60:	lea    0x1d20(%rsp),%rdi
  b5af68:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5af6d:	mov    0x40(%rbx),%rdi
  b5af71:	mov    %r12,%rsi
  b5af74:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5af79:	movb   $0x0,0x213(%r12)
  b5af82:	xor    %esi,%esi
  b5af84:	mov    %r12,%rdi
  b5af87:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5af8c:	lea    0x38(%r12),%rdi
  b5af91:	movb   $0x1,0x3e2(%r12)
  b5af9a:	mov    $0x1,%esi
  b5af9f:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5afa4:	mov    %r13,%rdi
  b5afa7:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5afac:	mov    %rax,%rsi
  b5afaf:	mov    %r12,%rdi
  b5afb2:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5afb7:	lea    0x3f70(%rsp),%r14
  b5afbf:	mov    %r13,%rsi
  b5afc2:	mov    %r14,%rdi
  b5afc5:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5afca:	mov    %r14,%rsi
  b5afcd:	mov    %r12,%rdi
  b5afd0:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5afd5:	mov    %r12,0x1a68(%rbx,%rbp,1)
  b5afdd:	jmp    b59b38 <_ZN14CInventoryMenu11createMenusEv+0x3158>
  b5afe2:	nopw   0x0(%rax,%rax,1)
  b5afe8:	cmp    $0xef,%dl
  b5afeb:	ja     b5b350 <_ZN14CInventoryMenu11createMenusEv+0x4970>
  b5aff1:	mov    %edx,%edi
  b5aff3:	lea    0x1(%rax),%edx
  b5aff6:	shl    $0xc,%edi
  b5aff9:	movzbl 0xfd0bff(%rdx),%edx
  b5b000:	and    $0xf000,%edi
  b5b006:	and    $0x3f,%edx
  b5b009:	or     %edi,%edx
  b5b00b:	mov    %eax,%edi
  b5b00d:	add    $0x2,%eax
  b5b010:	movzbl 0xfd0bff(%rdi),%edi
  b5b017:	and    $0x3f,%edi
  b5b01a:	shl    $0x6,%edi
  b5b01d:	or     %edi,%edx
  b5b01f:	jmp    b5ae63 <_ZN14CInventoryMenu11createMenusEv+0x4483>
  b5b024:	nopl   0x0(%rax)
  b5b028:	mov    $0x7,%edi
  b5b02d:	lea    0x2(%rax),%r8d
  b5b031:	and    %edx,%edi
  b5b033:	mov    %eax,%edx
  b5b035:	movzbl 0xfe499d(%rdx),%edx
  b5b03c:	movzbl 0xfe499d(%r8),%r8d
  b5b044:	shl    $0x12,%edi
  b5b047:	and    $0x3f,%edx
  b5b04a:	and    $0x3f,%r8d
  b5b04e:	shl    $0xc,%edx
  b5b051:	or     %r8d,%edx
  b5b054:	or     %edi,%edx
  b5b056:	lea    0x1(%rax),%edi
  b5b059:	add    $0x3,%eax
  b5b05c:	movzbl 0xfe499d(%rdi),%edi
  b5b063:	and    $0x3f,%edi
  b5b066:	shl    $0x6,%edi
  b5b069:	or     %edi,%edx
  b5b06b:	jmp    b58533 <_ZN14CInventoryMenu11createMenusEv+0x1b53>
  b5b070:	sub    $0x2,%rax
  b5b074:	add    $0x3,%rdx
  b5b078:	jmp    b58400 <_ZN14CInventoryMenu11createMenusEv+0x1a20>
  b5b07d:	nopl   (%rax)
  b5b080:	mov    $0x7,%edi
  b5b085:	lea    0x2(%rax),%r8d
  b5b089:	and    %edx,%edi
  b5b08b:	mov    %eax,%edx
  b5b08d:	movzbl 0xfd0bff(%rdx),%edx
  b5b094:	movzbl 0xfd0bff(%r8),%r8d
  b5b09c:	shl    $0x12,%edi
  b5b09f:	and    $0x3f,%edx
  b5b0a2:	and    $0x3f,%r8d
  b5b0a6:	shl    $0xc,%edx
  b5b0a9:	or     %r8d,%edx
  b5b0ac:	or     %edi,%edx
  b5b0ae:	lea    0x1(%rax),%edi
  b5b0b1:	add    $0x3,%eax
  b5b0b4:	movzbl 0xfd0bff(%rdi),%edi
  b5b0bb:	and    $0x3f,%edi
  b5b0be:	shl    $0x6,%edi
  b5b0c1:	or     %edi,%edx
  b5b0c3:	jmp    b5a543 <_ZN14CInventoryMenu11createMenusEv+0x3b63>
  b5b0c8:	nopl   0x0(%rax,%rax,1)
  b5b0d0:	sub    $0x2,%rax
  b5b0d4:	add    $0x3,%rdx
  b5b0d8:	jmp    b5a460 <_ZN14CInventoryMenu11createMenusEv+0x3a80>
  b5b0dd:	nopl   (%rax)
  b5b0e0:	cmpb   $0x0,0x49473f(%rip)        # fef826 <_ZTI16CInteractiveMenu+0xe6>
  b5b0e7:	je     b56ff0 <_ZN14CInventoryMenu11createMenusEv+0x610>
  b5b0ed:	nopl   (%rax)
  b5b0f0:	movzbl 0x0(%r13),%eax
  b5b0f5:	mov    %r13,%rbp
  b5b0f8:	add    $0x1,%r13
  b5b0fc:	sub    $0xfef826,%rbp
  b5b103:	test   %al,%al
  b5b105:	jne    b5b0f0 <_ZN14CInventoryMenu11createMenusEv+0x4710>
  b5b107:	test   %rbp,%rbp
  b5b10a:	setne  %al
  b5b10d:	test   %rcx,%rcx
  b5b110:	setne  %dl
  b5b113:	and    %edx,%eax
  b5b115:	jmp    b56f7c <_ZN14CInventoryMenu11createMenusEv+0x59c>
  b5b11a:	nopw   0x0(%rax,%rax,1)
  b5b120:	mov    0x3c08(%rsp),%rax
  b5b128:	jmp    b56dae <_ZN14CInventoryMenu11createMenusEv+0x3ce>
  b5b12d:	nopl   (%rax)
  b5b130:	sub    $0x2,%rax
  b5b134:	add    $0x3,%rdx
  b5b138:	jmp    b58960 <_ZN14CInventoryMenu11createMenusEv+0x1f80>
  b5b13d:	nopl   (%rax)
  b5b140:	mov    $0x7,%edi
  b5b145:	lea    0x2(%rax),%r8d
  b5b149:	and    %edx,%edi
  b5b14b:	mov    %eax,%edx
  b5b14d:	movzbl 0xfe49de(%rdx),%edx
  b5b154:	movzbl 0xfe49de(%r8),%r8d
  b5b15c:	shl    $0x12,%edi
  b5b15f:	and    $0x3f,%edx
  b5b162:	and    $0x3f,%r8d
  b5b166:	shl    $0xc,%edx
  b5b169:	or     %r8d,%edx
  b5b16c:	or     %edi,%edx
  b5b16e:	lea    0x1(%rax),%edi
  b5b171:	add    $0x3,%eax
  b5b174:	movzbl 0xfe49de(%rdi),%edi
  b5b17b:	and    $0x3f,%edi
  b5b17e:	shl    $0x6,%edi
  b5b181:	or     %edi,%edx
  b5b183:	jmp    b58aa3 <_ZN14CInventoryMenu11createMenusEv+0x20c3>
  b5b188:	nopl   0x0(%rax,%rax,1)
  b5b190:	mov    $0x7,%edi
  b5b195:	lea    0x2(%rax),%r8d
  b5b199:	and    %edx,%edi
  b5b19b:	mov    %eax,%edx
  b5b19d:	movzbl 0xfd0bff(%rdx),%edx
  b5b1a4:	movzbl 0xfd0bff(%r8),%r8d
  b5b1ac:	shl    $0x12,%edi
  b5b1af:	and    $0x3f,%edx
  b5b1b2:	and    $0x3f,%r8d
  b5b1b6:	shl    $0xc,%edx
  b5b1b9:	or     %r8d,%edx
  b5b1bc:	or     %edi,%edx
  b5b1be:	lea    0x1(%rax),%edi
  b5b1c1:	add    $0x3,%eax
  b5b1c4:	movzbl 0xfd0bff(%rdi),%edi
  b5b1cb:	and    $0x3f,%edi
  b5b1ce:	shl    $0x6,%edi
  b5b1d1:	or     %edi,%edx
  b5b1d3:	jmp    b5a9d3 <_ZN14CInventoryMenu11createMenusEv+0x3ff3>
  b5b1d8:	nopl   0x0(%rax,%rax,1)
  b5b1e0:	sub    $0x2,%rax
  b5b1e4:	add    $0x3,%rdx
  b5b1e8:	jmp    b5a8f0 <_ZN14CInventoryMenu11createMenusEv+0x3f10>
  b5b1ed:	nopl   (%rax)
  b5b1f0:	cmpb   $0x0,0x4897a6(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b5b1f7:	mov    $0xfe499e,%eax
  b5b1fc:	je     b571f0 <_ZN14CInventoryMenu11createMenusEv+0x810>
  b5b202:	nopw   0x0(%rax,%rax,1)
  b5b208:	movzbl (%rax),%edx
  b5b20b:	mov    %rax,%rbp
  b5b20e:	add    $0x1,%rax
  b5b212:	sub    $0xfe499d,%rbp
  b5b219:	test   %dl,%dl
  b5b21b:	jne    b5b208 <_ZN14CInventoryMenu11createMenusEv+0x4828>
  b5b21d:	test   %rbp,%rbp
  b5b220:	setne  %al
  b5b223:	test   %rcx,%rcx
  b5b226:	setne  %dl
  b5b229:	and    %edx,%eax
  b5b22b:	jmp    b5717c <_ZN14CInventoryMenu11createMenusEv+0x79c>
  b5b230:	mov    0x18(%rsp),%rsi
  b5b235:	add    $0x28,%rsi
  b5b239:	cmpq   $0x20,0x5570(%r15)
  b5b241:	jbe    b5a203 <_ZN14CInventoryMenu11createMenusEv+0x3823>
  b5b247:	mov    0x5610(%r15),%rdi
  b5b24e:	jmp    b5a217 <_ZN14CInventoryMenu11createMenusEv+0x3837>
  b5b253:	nopl   0x0(%rax,%rax,1)
  b5b258:	lea    (%r14,%r14,4),%rax
  b5b25c:	lea    (%r14,%rax,2),%rax
  b5b260:	shl    $0x4,%rax
  b5b264:	lea    0x5590(%rbx,%rax,1),%rax
  b5b26c:	jmp    b5a1ce <_ZN14CInventoryMenu11createMenusEv+0x37ee>
  b5b271:	nopl   0x0(%rax)
  b5b278:	cmpq   $0x20,0x1d10(%r15)
  b5b280:	mov    0x23f8(%rsp),%rsi
  b5b288:	jbe    b5a153 <_ZN14CInventoryMenu11createMenusEv+0x3773>
  b5b28e:	mov    0x1db0(%r15),%rdi
  b5b295:	jmp    b5a167 <_ZN14CInventoryMenu11createMenusEv+0x3787>
  b5b29a:	nopw   0x0(%rax,%rax,1)
  b5b2a0:	lea    (%r14,%r14,4),%rax
  b5b2a4:	lea    (%r14,%rax,2),%rax
  b5b2a8:	shl    $0x4,%rax
  b5b2ac:	lea    0x1d30(%rbx,%rax,1),%rax
  b5b2b4:	jmp    b5a11a <_ZN14CInventoryMenu11createMenusEv+0x373a>
  b5b2b9:	nopl   0x0(%rax)
  b5b2c0:	mov    0x24a8(%rsp),%rdx
  b5b2c8:	jmp    b5a072 <_ZN14CInventoryMenu11createMenusEv+0x3692>
  b5b2cd:	nopl   (%rax)
  b5b2d0:	mov    0x2558(%rsp),%rax
  b5b2d8:	jmp    b59c28 <_ZN14CInventoryMenu11createMenusEv+0x3248>
  b5b2dd:	nopl   (%rax)
  b5b2e0:	sub    $0x2,%rax
  b5b2e4:	add    $0x3,%rdx
  b5b2e8:	jmp    b58bc0 <_ZN14CInventoryMenu11createMenusEv+0x21e0>
  b5b2ed:	nopl   (%rax)
  b5b2f0:	mov    $0x7,%edi
  b5b2f5:	lea    0x2(%rax),%r8d
  b5b2f9:	and    %edx,%edi
  b5b2fb:	mov    %eax,%edx
  b5b2fd:	movzbl 0xfe499d(%rdx),%edx
  b5b304:	movzbl 0xfe499d(%r8),%r8d
  b5b30c:	shl    $0x12,%edi
  b5b30f:	and    $0x3f,%edx
  b5b312:	and    $0x3f,%r8d
  b5b316:	shl    $0xc,%edx
  b5b319:	or     %r8d,%edx
  b5b31c:	or     %edi,%edx
  b5b31e:	lea    0x1(%rax),%edi
  b5b321:	add    $0x3,%eax
  b5b324:	movzbl 0xfe499d(%rdi),%edi
  b5b32b:	and    $0x3f,%edi
  b5b32e:	shl    $0x6,%edi
  b5b331:	or     %edi,%edx
  b5b333:	jmp    b58d03 <_ZN14CInventoryMenu11createMenusEv+0x2323>
  b5b338:	nopl   0x0(%rax,%rax,1)
  b5b340:	sub    $0x2,%rax
  b5b344:	add    $0x3,%rdx
  b5b348:	jmp    b5ad80 <_ZN14CInventoryMenu11createMenusEv+0x43a0>
  b5b34d:	nopl   (%rax)
  b5b350:	mov    $0x7,%edi
  b5b355:	lea    0x2(%rax),%r8d
  b5b359:	and    %edx,%edi
  b5b35b:	mov    %eax,%edx
  b5b35d:	movzbl 0xfd0bff(%rdx),%edx
  b5b364:	movzbl 0xfd0bff(%r8),%r8d
  b5b36c:	shl    $0x12,%edi
  b5b36f:	and    $0x3f,%edx
  b5b372:	and    $0x3f,%r8d
  b5b376:	shl    $0xc,%edx
  b5b379:	or     %r8d,%edx
  b5b37c:	or     %edi,%edx
  b5b37e:	lea    0x1(%rax),%edi
  b5b381:	add    $0x3,%eax
  b5b384:	movzbl 0xfd0bff(%rdi),%edi
  b5b38b:	and    $0x3f,%edi
  b5b38e:	shl    $0x6,%edi
  b5b391:	or     %edi,%edx
  b5b393:	jmp    b5ae63 <_ZN14CInventoryMenu11createMenusEv+0x4483>
  b5b398:	nopl   0x0(%rax,%rax,1)
  b5b3a0:	cmpb   $0x0,0x4895f6(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b5b3a7:	mov    $0xfe499e,%eax
  b5b3ac:	je     b58590 <_ZN14CInventoryMenu11createMenusEv+0x1bb0>
  b5b3b2:	nopw   0x0(%rax,%rax,1)
  b5b3b8:	movzbl (%rax),%edx
  b5b3bb:	mov    %rax,%r12
  b5b3be:	add    $0x1,%rax
  b5b3c2:	sub    $0xfe499d,%r12
  b5b3c9:	test   %dl,%dl
  b5b3cb:	jne    b5b3b8 <_ZN14CInventoryMenu11createMenusEv+0x49d8>
  b5b3cd:	test   %r12,%r12
  b5b3d0:	setne  %al
  b5b3d3:	test   %rcx,%rcx
  b5b3d6:	setne  %dl
  b5b3d9:	and    %edx,%eax
  b5b3db:	jmp    b5851c <_ZN14CInventoryMenu11createMenusEv+0x1b3c>
  b5b3e0:	cmpb   $0x0,0x475818(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5b3e7:	mov    $0xfd0c00,%eax
  b5b3ec:	je     b5a5a0 <_ZN14CInventoryMenu11createMenusEv+0x3bc0>
  b5b3f2:	nopw   0x0(%rax,%rax,1)
  b5b3f8:	movzbl (%rax),%edx
  b5b3fb:	mov    %rax,%r12
  b5b3fe:	add    $0x1,%rax
  b5b402:	sub    $0xfd0bff,%r12
  b5b409:	test   %dl,%dl
  b5b40b:	jne    b5b3f8 <_ZN14CInventoryMenu11createMenusEv+0x4a18>
  b5b40d:	test   %r12,%r12
  b5b410:	setne  %al
  b5b413:	test   %rcx,%rcx
  b5b416:	setne  %dl
  b5b419:	and    %edx,%eax
  b5b41b:	jmp    b5a52d <_ZN14CInventoryMenu11createMenusEv+0x3b4d>
  b5b420:	mov    0x2348(%rsp),%rsi
  b5b428:	jmp    b5a51e <_ZN14CInventoryMenu11createMenusEv+0x3b3e>
  b5b42d:	nopl   (%rax)
  b5b430:	mov    0x2e48(%rsp),%rax
  b5b438:	jmp    b58349 <_ZN14CInventoryMenu11createMenusEv+0x1969>
  b5b43d:	nopl   (%rax)
  b5b440:	mov    0x24a8(%rsp),%rax
  b5b448:	add    $0x14,%rax
  b5b44c:	jmp    b5a0bc <_ZN14CInventoryMenu11createMenusEv+0x36dc>
  b5b451:	nopl   0x0(%rax)
  b5b458:	mov    0x21e8(%rsp),%rax
  b5b460:	jmp    b5a2b1 <_ZN14CInventoryMenu11createMenusEv+0x38d1>
  b5b465:	nopl   (%rax)
  b5b468:	test   %r12,%r12
  b5b46b:	mov    0x2b88(%rsp),%rsi
  b5b473:	jne    b58a87 <_ZN14CInventoryMenu11createMenusEv+0x20a7>
  b5b479:	cmpb   $0x0,0x48955e(%rip)        # fe49de <_ZTI17CSpawnClassParser+0x6de>
  b5b480:	je     b58b00 <_ZN14CInventoryMenu11createMenusEv+0x2120>
  b5b486:	cs nopw 0x0(%rax,%rax,1)
  b5b490:	movzbl (%r14),%eax
  b5b494:	mov    %r14,%r12
  b5b497:	add    $0x1,%r14
  b5b49b:	sub    $0xfe49de,%r12
  b5b4a2:	test   %al,%al
  b5b4a4:	jne    b5b490 <_ZN14CInventoryMenu11createMenusEv+0x4ab0>
  b5b4a6:	test   %r12,%r12
  b5b4a9:	setne  %al
  b5b4ac:	test   %rcx,%rcx
  b5b4af:	setne  %dl
  b5b4b2:	and    %edx,%eax
  b5b4b4:	jmp    b58a8d <_ZN14CInventoryMenu11createMenusEv+0x20ad>
  b5b4b9:	nopl   0x0(%rax)
  b5b4c0:	cmpb   $0x0,0x475738(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5b4c7:	mov    $0xfd0c00,%eax
  b5b4cc:	je     b5aa30 <_ZN14CInventoryMenu11createMenusEv+0x4050>
  b5b4d2:	nopw   0x0(%rax,%rax,1)
  b5b4d8:	movzbl (%rax),%edx
  b5b4db:	mov    %rax,%r12
  b5b4de:	add    $0x1,%rax
  b5b4e2:	sub    $0xfd0bff,%r12
  b5b4e9:	test   %dl,%dl
  b5b4eb:	jne    b5b4d8 <_ZN14CInventoryMenu11createMenusEv+0x4af8>
  b5b4ed:	test   %r12,%r12
  b5b4f0:	setne  %al
  b5b4f3:	test   %rcx,%rcx
  b5b4f6:	setne  %dl
  b5b4f9:	and    %edx,%eax
  b5b4fb:	jmp    b5a9bd <_ZN14CInventoryMenu11createMenusEv+0x3fdd>
  b5b500:	mov    0x2138(%rsp),%rsi
  b5b508:	jmp    b5a9ae <_ZN14CInventoryMenu11createMenusEv+0x3fce>
  b5b50d:	nopl   (%rax)
  b5b510:	mov    0x2ad8(%rsp),%rax
  b5b518:	jmp    b588b9 <_ZN14CInventoryMenu11createMenusEv+0x1ed9>
  b5b51d:	nopl   (%rax)
  b5b520:	mov    0x1fd8(%rsp),%rax
  b5b528:	jmp    b5a745 <_ZN14CInventoryMenu11createMenusEv+0x3d65>
  b5b52d:	nopl   (%rax)
  b5b530:	mov    0x2348(%rsp),%rax
  b5b538:	jmp    b5a5c3 <_ZN14CInventoryMenu11createMenusEv+0x3be3>
  b5b53d:	nopl   (%rax)
  b5b540:	cmpb   $0x0,0x489456(%rip)        # fe499d <_ZTI17CSpawnClassParser+0x69d>
  b5b547:	je     b58d60 <_ZN14CInventoryMenu11createMenusEv+0x2380>
  b5b54d:	nopl   (%rax)
  b5b550:	movzbl (%r15),%eax
  b5b554:	mov    %r15,%r12
  b5b557:	add    $0x1,%r15
  b5b55b:	sub    $0xfe499d,%r12
  b5b562:	test   %al,%al
  b5b564:	jne    b5b550 <_ZN14CInventoryMenu11createMenusEv+0x4b70>
  b5b566:	test   %r12,%r12
  b5b569:	setne  %al
  b5b56c:	test   %rcx,%rcx
  b5b56f:	setne  %dl
  b5b572:	and    %edx,%eax
  b5b574:	jmp    b58cec <_ZN14CInventoryMenu11createMenusEv+0x230c>
  b5b579:	nopl   0x0(%rax)
  b5b580:	cmpb   $0x0,0x475678(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5b587:	je     b5aec0 <_ZN14CInventoryMenu11createMenusEv+0x44e0>
  b5b58d:	mov    0x18(%rsp),%rax
  b5b592:	nopw   0x0(%rax,%rax,1)
  b5b598:	movzbl (%rax),%edx
  b5b59b:	mov    %rax,%r12
  b5b59e:	add    $0x1,%rax
  b5b5a2:	sub    $0xfd0bff,%r12
  b5b5a9:	test   %dl,%dl
  b5b5ab:	jne    b5b598 <_ZN14CInventoryMenu11createMenusEv+0x4bb8>
  b5b5ad:	test   %r12,%r12
  b5b5b0:	setne  %al
  b5b5b3:	test   %rcx,%rcx
  b5b5b6:	setne  %dl
  b5b5b9:	and    %edx,%eax
  b5b5bb:	jmp    b5ae4d <_ZN14CInventoryMenu11createMenusEv+0x446d>
  b5b5c0:	mov    0x1f28(%rsp),%rsi
  b5b5c8:	jmp    b5ae3e <_ZN14CInventoryMenu11createMenusEv+0x445e>
  b5b5cd:	nopl   (%rax)
  b5b5d0:	mov    0x1dc8(%rsp),%rax
  b5b5d8:	jmp    b5abd6 <_ZN14CInventoryMenu11createMenusEv+0x41f6>
  b5b5dd:	nopl   (%rax)
  b5b5e0:	mov    0x2138(%rsp),%rax
  b5b5e8:	jmp    b5aa53 <_ZN14CInventoryMenu11createMenusEv+0x4073>
  b5b5ed:	nopl   (%rax)
  b5b5f0:	mov    0x2b88(%rsp),%rax
  b5b5f8:	jmp    b58b23 <_ZN14CInventoryMenu11createMenusEv+0x2143>
  b5b5fd:	nopl   (%rax)
  b5b600:	mov    %rbx,%rdx
  b5b603:	xor    %eax,%eax
  b5b605:	nopl   (%rax)
  b5b608:	mov    %eax,0x80(%rdx)
  b5b60e:	add    $0x1,%eax
  b5b611:	add    $0x4,%rdx
  b5b615:	cmp    $0x3e8,%eax
  b5b61a:	jne    b5b608 <_ZN14CInventoryMenu11createMenusEv+0x4c28>
  b5b61c:	mov    $0x64,%edx
  b5b621:	xor    %ax,%ax
  b5b624:	nopl   0x0(%rax)
  b5b628:	movslq %eax,%rcx
  b5b62b:	add    $0x1,%eax
  b5b62e:	sub    $0x1,%edx
  b5b631:	mov    %rcx,0x8de8(%rbx,%rcx,8)
  b5b639:	jne    b5b628 <_ZN14CInventoryMenu11createMenusEv+0x4c48>
  b5b63b:	lea    0x1c70(%rsp),%rbp
  b5b643:	mov    $0xb,%esi
  b5b648:	movq   $0x20,0x1c78(%rsp)
  b5b654:	movq   $0x0,0x1c80(%rsp)
  b5b660:	movq   $0x0,0x1c90(%rsp)
  b5b66c:	mov    %rbp,%rdi
  b5b66f:	movq   $0x0,0x1c88(%rsp)
  b5b67b:	movq   $0x0,0x1d18(%rsp)
  b5b687:	movq   $0x0,0x1c70(%rsp)
  b5b693:	movl   $0x0,0x1c98(%rsp)
  b5b69e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5b6a3:	cmpq   $0x20,0x1c78(%rsp)
  b5b6ac:	lea    0x28(%rbp),%rdx
  b5b6b0:	jbe    b5b6ba <_ZN14CInventoryMenu11createMenusEv+0x4cda>
  b5b6b2:	mov    0x1d18(%rsp),%rdx
  b5b6ba:	mov    $0xfef7d0,%eax
  b5b6bf:	nop
  b5b6c0:	movzbl (%rax),%ecx
  b5b6c3:	add    $0x1,%rax
  b5b6c7:	mov    %ecx,(%rdx)
  b5b6c9:	add    $0x4,%rdx
  b5b6cd:	cmp    $0xfef7db,%rax
  b5b6d3:	jne    b5b6c0 <_ZN14CInventoryMenu11createMenusEv+0x4ce0>
  b5b6d5:	cmpq   $0x20,0x1c78(%rsp)
  b5b6de:	movq   $0xb,0x1c70(%rsp)
  b5b6ea:	lea    0x54(%rbp),%rax
  b5b6ee:	jbe    b5b6fc <_ZN14CInventoryMenu11createMenusEv+0x4d1c>
  b5b6f0:	mov    0x1d18(%rsp),%rax
  b5b6f8:	add    $0x2c,%rax
  b5b6fc:	movl   $0x0,(%rax)
  b5b702:	mov    0x48(%rbx),%rdi
  b5b706:	mov    %rbp,%rsi
  b5b709:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5b70e:	mov    %rax,0x9120(%rbx)
  b5b715:	mov    %rbp,%rdi
  b5b718:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5b71d:	lea    0x1bc0(%rsp),%r13
  b5b725:	mov    $0xf,%esi
  b5b72a:	movq   $0x20,0x1bc8(%rsp)
  b5b736:	movq   $0x0,0x1bd0(%rsp)
  b5b742:	movq   $0x0,0x1be0(%rsp)
  b5b74e:	mov    %r13,%rdi
  b5b751:	movq   $0x0,0x1bd8(%rsp)
  b5b75d:	movq   $0x0,0x1c68(%rsp)
  b5b769:	movq   $0x0,0x1bc0(%rsp)
  b5b775:	movl   $0x0,0x1be8(%rsp)
  b5b780:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5b785:	cmpq   $0x20,0x1bc8(%rsp)
  b5b78e:	lea    0x28(%r13),%rdx
  b5b792:	jbe    b5b79c <_ZN14CInventoryMenu11createMenusEv+0x4dbc>
  b5b794:	mov    0x1c68(%rsp),%rdx
  b5b79c:	mov    $0xfef76b,%ebp
  b5b7a1:	mov    $0xfef75c,%eax
  b5b7a6:	cs nopw 0x0(%rax,%rax,1)
  b5b7b0:	movzbl (%rax),%ecx
  b5b7b3:	add    $0x1,%rax
  b5b7b7:	mov    %ecx,(%rdx)
  b5b7b9:	add    $0x4,%rdx
  b5b7bd:	cmp    $0xfef76b,%rax
  b5b7c3:	jne    b5b7b0 <_ZN14CInventoryMenu11createMenusEv+0x4dd0>
  b5b7c5:	cmpq   $0x20,0x1bc8(%rsp)
  b5b7ce:	movq   $0xf,0x1bc0(%rsp)
  b5b7da:	lea    0x64(%r13),%rax
  b5b7de:	jbe    b5b7ec <_ZN14CInventoryMenu11createMenusEv+0x4e0c>
  b5b7e0:	mov    0x1c68(%rsp),%rax
  b5b7e8:	add    $0x3c,%rax
  b5b7ec:	movl   $0x0,(%rax)
  b5b7f2:	lea    0x1b10(%rsp),%r14
  b5b7fa:	mov    0x9120(%rbx),%rsi
  b5b801:	mov    %r13,%rdx
  b5b804:	mov    %r14,%rdi
  b5b807:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5b80c:	mov    0x1b10(%rsp),%r12
  b5b814:	lea    0x91b0(%rbx),%rdi
  b5b81b:	mov    %r12,%rsi
  b5b81e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5b823:	cmpq   $0x20,0x91b8(%rbx)
  b5b82b:	mov    %r12,0x91b0(%rbx)
  b5b832:	lea    0x91d8(%rbx),%rax
  b5b839:	jbe    b5b842 <_ZN14CInventoryMenu11createMenusEv+0x4e62>
  b5b83b:	mov    0x9258(%rbx),%rax
  b5b842:	movl   $0x0,(%rax,%r12,4)
  b5b84a:	cmpq   $0x20,0x1b18(%rsp)
  b5b853:	lea    0x0(,%r12,4),%rdx
  b5b85b:	lea    0x28(%r14),%rsi
  b5b85f:	jbe    b5b869 <_ZN14CInventoryMenu11createMenusEv+0x4e89>
  b5b861:	mov    0x1bb8(%rsp),%rsi
  b5b869:	cmpq   $0x20,0x91b8(%rbx)
  b5b871:	lea    0x91d8(%rbx),%rdi
  b5b878:	jbe    b5b881 <_ZN14CInventoryMenu11createMenusEv+0x4ea1>
  b5b87a:	mov    0x9258(%rbx),%rdi
  b5b881:	call   555ab8 <memcpy@plt>
  b5b886:	mov    %r14,%rdi
  b5b889:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5b88e:	mov    %r13,%rdi
  b5b891:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5b896:	lea    0x1a60(%rsp),%r14
  b5b89e:	mov    $0xd,%esi
  b5b8a3:	movq   $0x20,0x1a68(%rsp)
  b5b8af:	movq   $0x0,0x1a70(%rsp)
  b5b8bb:	movq   $0x0,0x1a80(%rsp)
  b5b8c7:	mov    %r14,%rdi
  b5b8ca:	movq   $0x0,0x1a78(%rsp)
  b5b8d6:	movq   $0x0,0x1b08(%rsp)
  b5b8e2:	movq   $0x0,0x1a60(%rsp)
  b5b8ee:	movl   $0x0,0x1a88(%rsp)
  b5b8f9:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5b8fe:	cmpq   $0x20,0x1a68(%rsp)
  b5b907:	lea    0x28(%r14),%rdx
  b5b90b:	jbe    b5b915 <_ZN14CInventoryMenu11createMenusEv+0x4f35>
  b5b90d:	mov    0x1b08(%rsp),%rdx
  b5b915:	mov    $0xfef7be,%r12d
  b5b91b:	mov    $0xfef7b1,%eax
  b5b920:	movzbl (%rax),%ecx
  b5b923:	add    $0x1,%rax
  b5b927:	mov    %ecx,(%rdx)
  b5b929:	add    $0x4,%rdx
  b5b92d:	cmp    $0xfef7be,%rax
  b5b933:	jne    b5b920 <_ZN14CInventoryMenu11createMenusEv+0x4f40>
  b5b935:	cmpq   $0x20,0x1a68(%rsp)
  b5b93e:	movq   $0xd,0x1a60(%rsp)
  b5b94a:	lea    0x5c(%r14),%rax
  b5b94e:	jbe    b5b95c <_ZN14CInventoryMenu11createMenusEv+0x4f7c>
  b5b950:	mov    0x1b08(%rsp),%rax
  b5b958:	add    $0x34,%rax
  b5b95c:	movl   $0x0,(%rax)
  b5b962:	lea    0x19b0(%rsp),%r15
  b5b96a:	mov    0x9120(%rbx),%rsi
  b5b971:	mov    %r14,%rdx
  b5b974:	mov    %r15,%rdi
  b5b977:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5b97c:	mov    0x19b0(%rsp),%r13
  b5b984:	lea    0x93c0(%rbx),%rdi
  b5b98b:	mov    %r13,%rsi
  b5b98e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5b993:	cmpq   $0x20,0x93c8(%rbx)
  b5b99b:	mov    %r13,0x93c0(%rbx)
  b5b9a2:	lea    0x93e8(%rbx),%rax
  b5b9a9:	jbe    b5b9b2 <_ZN14CInventoryMenu11createMenusEv+0x4fd2>
  b5b9ab:	mov    0x9468(%rbx),%rax
  b5b9b2:	movl   $0x0,(%rax,%r13,4)
  b5b9ba:	cmpq   $0x20,0x19b8(%rsp)
  b5b9c3:	lea    0x0(,%r13,4),%rdx
  b5b9cb:	lea    0x28(%r15),%rsi
  b5b9cf:	jbe    b5b9d9 <_ZN14CInventoryMenu11createMenusEv+0x4ff9>
  b5b9d1:	mov    0x1a58(%rsp),%rsi
  b5b9d9:	cmpq   $0x20,0x93c8(%rbx)
  b5b9e1:	lea    0x93e8(%rbx),%rdi
  b5b9e8:	jbe    b5b9f1 <_ZN14CInventoryMenu11createMenusEv+0x5011>
  b5b9ea:	mov    0x9468(%rbx),%rdi
  b5b9f1:	call   555ab8 <memcpy@plt>
  b5b9f6:	mov    %r15,%rdi
  b5b9f9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5b9fe:	mov    %r14,%rdi
  b5ba01:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ba06:	lea    0x1900(%rsp),%r13
  b5ba0e:	mov    $0x8,%esi
  b5ba13:	movq   $0x20,0x1908(%rsp)
  b5ba1f:	movq   $0x0,0x1910(%rsp)
  b5ba2b:	movq   $0x0,0x1920(%rsp)
  b5ba37:	mov    %r13,%rdi
  b5ba3a:	movq   $0x0,0x1918(%rsp)
  b5ba46:	movq   $0x0,0x19a8(%rsp)
  b5ba52:	movq   $0x0,0x1900(%rsp)
  b5ba5e:	movl   $0x0,0x1928(%rsp)
  b5ba69:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ba6e:	cmpq   $0x20,0x1908(%rsp)
  b5ba77:	lea    0x28(%r13),%rdx
  b5ba7b:	jbe    b5ba85 <_ZN14CInventoryMenu11createMenusEv+0x50a5>
  b5ba7d:	mov    0x19a8(%rsp),%rdx
  b5ba85:	mov    $0xfef7c7,%eax
  b5ba8a:	nopw   0x0(%rax,%rax,1)
  b5ba90:	movzbl (%rax),%ecx
  b5ba93:	add    $0x1,%rax
  b5ba97:	mov    %ecx,(%rdx)
  b5ba99:	add    $0x4,%rdx
  b5ba9d:	cmp    $0xfef7cf,%rax
  b5baa3:	jne    b5ba90 <_ZN14CInventoryMenu11createMenusEv+0x50b0>
  b5baa5:	cmpq   $0x20,0x1908(%rsp)
  b5baae:	movq   $0x8,0x1900(%rsp)
  b5baba:	lea    0x48(%r13),%rax
  b5babe:	jbe    b5bacc <_ZN14CInventoryMenu11createMenusEv+0x50ec>
  b5bac0:	mov    0x19a8(%rsp),%rax
  b5bac8:	add    $0x20,%rax
  b5bacc:	movl   $0x0,(%rax)
  b5bad2:	mov    0x48(%rbx),%rdi
  b5bad6:	mov    %r13,%rsi
  b5bad9:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5bade:	mov    %rax,0x9128(%rbx)
  b5bae5:	mov    %r13,%rdi
  b5bae8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5baed:	lea    0x1850(%rsp),%r14
  b5baf5:	mov    $0xf,%esi
  b5bafa:	movq   $0x20,0x1858(%rsp)
  b5bb06:	movq   $0x0,0x1860(%rsp)
  b5bb12:	movq   $0x0,0x1870(%rsp)
  b5bb1e:	mov    %r14,%rdi
  b5bb21:	movq   $0x0,0x1868(%rsp)
  b5bb2d:	movq   $0x0,0x18f8(%rsp)
  b5bb39:	movq   $0x0,0x1850(%rsp)
  b5bb45:	movl   $0x0,0x1878(%rsp)
  b5bb50:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bb55:	cmpq   $0x20,0x1858(%rsp)
  b5bb5e:	lea    0x28(%r14),%rdx
  b5bb62:	jbe    b5bb6c <_ZN14CInventoryMenu11createMenusEv+0x518c>
  b5bb64:	mov    0x18f8(%rsp),%rdx
  b5bb6c:	mov    $0xfef75c,%eax
  b5bb71:	nopl   0x0(%rax)
  b5bb78:	movzbl (%rax),%ecx
  b5bb7b:	add    $0x1,%rax
  b5bb7f:	mov    %ecx,(%rdx)
  b5bb81:	add    $0x4,%rdx
  b5bb85:	cmp    %rax,%rbp
  b5bb88:	jne    b5bb78 <_ZN14CInventoryMenu11createMenusEv+0x5198>
  b5bb8a:	cmpq   $0x20,0x1858(%rsp)
  b5bb93:	movq   $0xf,0x1850(%rsp)
  b5bb9f:	lea    0x64(%r14),%rax
  b5bba3:	jbe    b5bbb1 <_ZN14CInventoryMenu11createMenusEv+0x51d1>
  b5bba5:	mov    0x18f8(%rsp),%rax
  b5bbad:	add    $0x3c,%rax
  b5bbb1:	movl   $0x0,(%rax)
  b5bbb7:	lea    0x17a0(%rsp),%r15
  b5bbbf:	mov    0x9128(%rbx),%rsi
  b5bbc6:	mov    %r14,%rdx
  b5bbc9:	mov    %r15,%rdi
  b5bbcc:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5bbd1:	mov    0x17a0(%rsp),%r13
  b5bbd9:	lea    0x9260(%rbx),%rdi
  b5bbe0:	mov    %r13,%rsi
  b5bbe3:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bbe8:	cmpq   $0x20,0x9268(%rbx)
  b5bbf0:	mov    %r13,0x9260(%rbx)
  b5bbf7:	lea    0x9288(%rbx),%rax
  b5bbfe:	jbe    b5bc07 <_ZN14CInventoryMenu11createMenusEv+0x5227>
  b5bc00:	mov    0x9308(%rbx),%rax
  b5bc07:	movl   $0x0,(%rax,%r13,4)
  b5bc0f:	cmpq   $0x20,0x17a8(%rsp)
  b5bc18:	lea    0x0(,%r13,4),%rdx
  b5bc20:	lea    0x28(%r15),%rsi
  b5bc24:	jbe    b5bc2e <_ZN14CInventoryMenu11createMenusEv+0x524e>
  b5bc26:	mov    0x1848(%rsp),%rsi
  b5bc2e:	cmpq   $0x20,0x9268(%rbx)
  b5bc36:	lea    0x9288(%rbx),%rdi
  b5bc3d:	jbe    b5bc46 <_ZN14CInventoryMenu11createMenusEv+0x5266>
  b5bc3f:	mov    0x9308(%rbx),%rdi
  b5bc46:	call   555ab8 <memcpy@plt>
  b5bc4b:	mov    %r15,%rdi
  b5bc4e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5bc53:	mov    %r14,%rdi
  b5bc56:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5bc5b:	lea    0x16f0(%rsp),%r14
  b5bc63:	mov    $0xd,%esi
  b5bc68:	movq   $0x20,0x16f8(%rsp)
  b5bc74:	movq   $0x0,0x1700(%rsp)
  b5bc80:	movq   $0x0,0x1710(%rsp)
  b5bc8c:	mov    %r14,%rdi
  b5bc8f:	movq   $0x0,0x1708(%rsp)
  b5bc9b:	movq   $0x0,0x1798(%rsp)
  b5bca7:	movq   $0x0,0x16f0(%rsp)
  b5bcb3:	movl   $0x0,0x1718(%rsp)
  b5bcbe:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bcc3:	cmpq   $0x20,0x16f8(%rsp)
  b5bccc:	lea    0x28(%r14),%rdx
  b5bcd0:	jbe    b5bcda <_ZN14CInventoryMenu11createMenusEv+0x52fa>
  b5bcd2:	mov    0x1798(%rsp),%rdx
  b5bcda:	mov    $0xfef7b1,%eax
  b5bcdf:	nop
  b5bce0:	movzbl (%rax),%ecx
  b5bce3:	add    $0x1,%rax
  b5bce7:	mov    %ecx,(%rdx)
  b5bce9:	add    $0x4,%rdx
  b5bced:	cmp    %rax,%r12
  b5bcf0:	jne    b5bce0 <_ZN14CInventoryMenu11createMenusEv+0x5300>
  b5bcf2:	cmpq   $0x20,0x16f8(%rsp)
  b5bcfb:	movq   $0xd,0x16f0(%rsp)
  b5bd07:	lea    0x5c(%r14),%rax
  b5bd0b:	jbe    b5bd19 <_ZN14CInventoryMenu11createMenusEv+0x5339>
  b5bd0d:	mov    0x1798(%rsp),%rax
  b5bd15:	add    $0x34,%rax
  b5bd19:	movl   $0x0,(%rax)
  b5bd1f:	lea    0x1640(%rsp),%r15
  b5bd27:	mov    0x9128(%rbx),%rsi
  b5bd2e:	mov    %r14,%rdx
  b5bd31:	mov    %r15,%rdi
  b5bd34:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5bd39:	mov    0x1640(%rsp),%r13
  b5bd41:	lea    0x9470(%rbx),%rdi
  b5bd48:	mov    %r13,%rsi
  b5bd4b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bd50:	cmpq   $0x20,0x9478(%rbx)
  b5bd58:	mov    %r13,0x9470(%rbx)
  b5bd5f:	lea    0x9498(%rbx),%rax
  b5bd66:	jbe    b5bd6f <_ZN14CInventoryMenu11createMenusEv+0x538f>
  b5bd68:	mov    0x9518(%rbx),%rax
  b5bd6f:	movl   $0x0,(%rax,%r13,4)
  b5bd77:	cmpq   $0x20,0x1648(%rsp)
  b5bd80:	lea    0x0(,%r13,4),%rdx
  b5bd88:	lea    0x28(%r15),%rsi
  b5bd8c:	jbe    b5bd96 <_ZN14CInventoryMenu11createMenusEv+0x53b6>
  b5bd8e:	mov    0x16e8(%rsp),%rsi
  b5bd96:	cmpq   $0x20,0x9478(%rbx)
  b5bd9e:	lea    0x9498(%rbx),%rdi
  b5bda5:	jbe    b5bdae <_ZN14CInventoryMenu11createMenusEv+0x53ce>
  b5bda7:	mov    0x9518(%rbx),%rdi
  b5bdae:	call   555ab8 <memcpy@plt>
  b5bdb3:	mov    %r15,%rdi
  b5bdb6:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5bdbb:	mov    %r14,%rdi
  b5bdbe:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5bdc3:	lea    0x1590(%rsp),%r13
  b5bdcb:	mov    $0x7,%esi
  b5bdd0:	movq   $0x20,0x1598(%rsp)
  b5bddc:	movq   $0x0,0x15a0(%rsp)
  b5bde8:	movq   $0x0,0x15b0(%rsp)
  b5bdf4:	mov    %r13,%rdi
  b5bdf7:	movq   $0x0,0x15a8(%rsp)
  b5be03:	movq   $0x0,0x1638(%rsp)
  b5be0f:	movq   $0x0,0x1590(%rsp)
  b5be1b:	movl   $0x0,0x15b8(%rsp)
  b5be26:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5be2b:	cmpq   $0x20,0x1598(%rsp)
  b5be34:	lea    0x28(%r13),%rdx
  b5be38:	jbe    b5be42 <_ZN14CInventoryMenu11createMenusEv+0x5462>
  b5be3a:	mov    0x1638(%rsp),%rdx
  b5be42:	mov    $0xfef7bf,%eax
  b5be47:	nopw   0x0(%rax,%rax,1)
  b5be50:	movzbl (%rax),%ecx
  b5be53:	add    $0x1,%rax
  b5be57:	mov    %ecx,(%rdx)
  b5be59:	add    $0x4,%rdx
  b5be5d:	cmp    $0xfef7c6,%rax
  b5be63:	jne    b5be50 <_ZN14CInventoryMenu11createMenusEv+0x5470>
  b5be65:	cmpq   $0x20,0x1598(%rsp)
  b5be6e:	movq   $0x7,0x1590(%rsp)
  b5be7a:	lea    0x44(%r13),%rax
  b5be7e:	jbe    b5be8c <_ZN14CInventoryMenu11createMenusEv+0x54ac>
  b5be80:	mov    0x1638(%rsp),%rax
  b5be88:	add    $0x1c,%rax
  b5be8c:	movl   $0x0,(%rax)
  b5be92:	mov    0x48(%rbx),%rdi
  b5be96:	mov    %r13,%rsi
  b5be99:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5be9e:	mov    %rax,0x9130(%rbx)
  b5bea5:	mov    %r13,%rdi
  b5bea8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5bead:	lea    0x14e0(%rsp),%r13
  b5beb5:	mov    $0xf,%esi
  b5beba:	movq   $0x20,0x14e8(%rsp)
  b5bec6:	movq   $0x0,0x14f0(%rsp)
  b5bed2:	movq   $0x0,0x1500(%rsp)
  b5bede:	mov    %r13,%rdi
  b5bee1:	movq   $0x0,0x14f8(%rsp)
  b5beed:	movq   $0x0,0x1588(%rsp)
  b5bef9:	movq   $0x0,0x14e0(%rsp)
  b5bf05:	movl   $0x0,0x1508(%rsp)
  b5bf10:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bf15:	cmpq   $0x20,0x14e8(%rsp)
  b5bf1e:	lea    0x28(%r13),%rdx
  b5bf22:	jbe    b5bf2c <_ZN14CInventoryMenu11createMenusEv+0x554c>
  b5bf24:	mov    0x1588(%rsp),%rdx
  b5bf2c:	mov    $0xfef75c,%eax
  b5bf31:	nopl   0x0(%rax)
  b5bf38:	movzbl (%rax),%ecx
  b5bf3b:	add    $0x1,%rax
  b5bf3f:	mov    %ecx,(%rdx)
  b5bf41:	add    $0x4,%rdx
  b5bf45:	cmp    %rax,%rbp
  b5bf48:	jne    b5bf38 <_ZN14CInventoryMenu11createMenusEv+0x5558>
  b5bf4a:	cmpq   $0x20,0x14e8(%rsp)
  b5bf53:	movq   $0xf,0x14e0(%rsp)
  b5bf5f:	lea    0x64(%r13),%rax
  b5bf63:	jbe    b5bf71 <_ZN14CInventoryMenu11createMenusEv+0x5591>
  b5bf65:	mov    0x1588(%rsp),%rax
  b5bf6d:	add    $0x3c,%rax
  b5bf71:	movl   $0x0,(%rax)
  b5bf77:	lea    0x1430(%rsp),%r14
  b5bf7f:	mov    0x9130(%rbx),%rsi
  b5bf86:	mov    %r13,%rdx
  b5bf89:	mov    %r14,%rdi
  b5bf8c:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5bf91:	mov    0x1430(%rsp),%rbp
  b5bf99:	lea    0x9310(%rbx),%rdi
  b5bfa0:	mov    %rbp,%rsi
  b5bfa3:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5bfa8:	cmpq   $0x20,0x9318(%rbx)
  b5bfb0:	mov    %rbp,0x9310(%rbx)
  b5bfb7:	lea    0x9338(%rbx),%rax
  b5bfbe:	jbe    b5bfc7 <_ZN14CInventoryMenu11createMenusEv+0x55e7>
  b5bfc0:	mov    0x93b8(%rbx),%rax
  b5bfc7:	movl   $0x0,(%rax,%rbp,4)
  b5bfce:	cmpq   $0x20,0x1438(%rsp)
  b5bfd7:	lea    0x0(,%rbp,4),%rdx
  b5bfdf:	lea    0x28(%r14),%rsi
  b5bfe3:	jbe    b5bfed <_ZN14CInventoryMenu11createMenusEv+0x560d>
  b5bfe5:	mov    0x14d8(%rsp),%rsi
  b5bfed:	cmpq   $0x20,0x9318(%rbx)
  b5bff5:	lea    0x9338(%rbx),%rdi
  b5bffc:	jbe    b5c005 <_ZN14CInventoryMenu11createMenusEv+0x5625>
  b5bffe:	mov    0x93b8(%rbx),%rdi
  b5c005:	call   555ab8 <memcpy@plt>
  b5c00a:	mov    %r14,%rdi
  b5c00d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c012:	mov    %r13,%rdi
  b5c015:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c01a:	lea    0x1380(%rsp),%r13
  b5c022:	mov    $0xd,%esi
  b5c027:	movq   $0x20,0x1388(%rsp)
  b5c033:	movq   $0x0,0x1390(%rsp)
  b5c03f:	movq   $0x0,0x13a0(%rsp)
  b5c04b:	mov    %r13,%rdi
  b5c04e:	movq   $0x0,0x1398(%rsp)
  b5c05a:	movq   $0x0,0x1428(%rsp)
  b5c066:	movq   $0x0,0x1380(%rsp)
  b5c072:	movl   $0x0,0x13a8(%rsp)
  b5c07d:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c082:	cmpq   $0x20,0x1388(%rsp)
  b5c08b:	lea    0x28(%r13),%rdx
  b5c08f:	jbe    b5c099 <_ZN14CInventoryMenu11createMenusEv+0x56b9>
  b5c091:	mov    0x1428(%rsp),%rdx
  b5c099:	mov    $0xfef7b1,%eax
  b5c09e:	xchg   %ax,%ax
  b5c0a0:	movzbl (%rax),%ecx
  b5c0a3:	add    $0x1,%rax
  b5c0a7:	mov    %ecx,(%rdx)
  b5c0a9:	add    $0x4,%rdx
  b5c0ad:	cmp    %rax,%r12
  b5c0b0:	jne    b5c0a0 <_ZN14CInventoryMenu11createMenusEv+0x56c0>
  b5c0b2:	cmpq   $0x20,0x1388(%rsp)
  b5c0bb:	movq   $0xd,0x1380(%rsp)
  b5c0c7:	lea    0x5c(%r13),%rax
  b5c0cb:	jbe    b5c0d9 <_ZN14CInventoryMenu11createMenusEv+0x56f9>
  b5c0cd:	mov    0x1428(%rsp),%rax
  b5c0d5:	add    $0x34,%rax
  b5c0d9:	movl   $0x0,(%rax)
  b5c0df:	lea    0x12d0(%rsp),%r12
  b5c0e7:	mov    0x9130(%rbx),%rsi
  b5c0ee:	mov    %r13,%rdx
  b5c0f1:	mov    %r12,%rdi
  b5c0f4:	call   554418 <_ZNK5CEGUI11PropertySet11getPropertyERKNS_6StringE@plt>
  b5c0f9:	mov    0x12d0(%rsp),%rbp
  b5c101:	lea    0x9520(%rbx),%rdi
  b5c108:	mov    %rbp,%rsi
  b5c10b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c110:	cmpq   $0x20,0x9528(%rbx)
  b5c118:	mov    %rbp,0x9520(%rbx)
  b5c11f:	lea    0x9548(%rbx),%rax
  b5c126:	jbe    b5c12f <_ZN14CInventoryMenu11createMenusEv+0x574f>
  b5c128:	mov    0x95c8(%rbx),%rax
  b5c12f:	movl   $0x0,(%rax,%rbp,4)
  b5c136:	cmpq   $0x20,0x12d8(%rsp)
  b5c13f:	lea    0x0(,%rbp,4),%rdx
  b5c147:	lea    0x28(%r12),%rsi
  b5c14c:	jbe    b5c156 <_ZN14CInventoryMenu11createMenusEv+0x5776>
  b5c14e:	mov    0x1378(%rsp),%rsi
  b5c156:	cmpq   $0x20,0x9528(%rbx)
  b5c15e:	lea    0x9548(%rbx),%rdi
  b5c165:	jbe    b5c16e <_ZN14CInventoryMenu11createMenusEv+0x578e>
  b5c167:	mov    0x95c8(%rbx),%rdi
  b5c16e:	call   555ab8 <memcpy@plt>
  b5c173:	mov    %r12,%rdi
  b5c176:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c17b:	mov    %r13,%rdi
  b5c17e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c183:	mov    0x9120(%rbx),%rdi
  b5c18a:	xor    %esi,%esi
  b5c18c:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b5c191:	mov    0x9128(%rbx),%rdi
  b5c198:	xor    %esi,%esi
  b5c19a:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b5c19f:	mov    0x9130(%rbx),%rdi
  b5c1a6:	xor    %esi,%esi
  b5c1a8:	call   553f48 <_ZN5CEGUI6Window19setZOrderingEnabledEb@plt>
  b5c1ad:	lea    0x1220(%rsp),%rbp
  b5c1b5:	mov    $0xe,%esi
  b5c1ba:	movq   $0x20,0x1228(%rsp)
  b5c1c6:	movq   $0x0,0x1230(%rsp)
  b5c1d2:	movq   $0x0,0x1240(%rsp)
  b5c1de:	mov    %rbp,%rdi
  b5c1e1:	movq   $0x0,0x1238(%rsp)
  b5c1ed:	movq   $0x0,0x12c8(%rsp)
  b5c1f9:	movq   $0x0,0x1220(%rsp)
  b5c205:	movl   $0x0,0x1248(%rsp)
  b5c210:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c215:	cmpq   $0x20,0x1228(%rsp)
  b5c21e:	lea    0x28(%rbp),%rdx
  b5c222:	jbe    b5c22c <_ZN14CInventoryMenu11createMenusEv+0x584c>
  b5c224:	mov    0x12c8(%rsp),%rdx
  b5c22c:	mov    $0xfeff6a,%eax
  b5c231:	nopl   0x0(%rax)
  b5c238:	movzbl (%rax),%ecx
  b5c23b:	add    $0x1,%rax
  b5c23f:	mov    %ecx,(%rdx)
  b5c241:	add    $0x4,%rdx
  b5c245:	cmp    $0xfeff78,%rax
  b5c24b:	jne    b5c238 <_ZN14CInventoryMenu11createMenusEv+0x5858>
  b5c24d:	cmpq   $0x20,0x1228(%rsp)
  b5c256:	movq   $0xe,0x1220(%rsp)
  b5c262:	lea    0x60(%rbp),%rax
  b5c266:	jbe    b5c274 <_ZN14CInventoryMenu11createMenusEv+0x5894>
  b5c268:	mov    0x12c8(%rsp),%rax
  b5c270:	add    $0x38,%rax
  b5c274:	movl   $0x0,(%rax)
  b5c27a:	mov    0x48(%rbx),%rdi
  b5c27e:	mov    %rbp,%rsi
  b5c281:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5c286:	mov    %rax,0x9108(%rbx)
  b5c28d:	mov    %rbp,%rdi
  b5c290:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c295:	lea    0x1170(%rsp),%rbp
  b5c29d:	mov    $0xb,%esi
  b5c2a2:	movq   $0x20,0x1178(%rsp)
  b5c2ae:	movq   $0x0,0x1180(%rsp)
  b5c2ba:	movq   $0x0,0x1190(%rsp)
  b5c2c6:	mov    %rbp,%rdi
  b5c2c9:	movq   $0x0,0x1188(%rsp)
  b5c2d5:	movq   $0x0,0x1218(%rsp)
  b5c2e1:	movq   $0x0,0x1170(%rsp)
  b5c2ed:	movl   $0x0,0x1198(%rsp)
  b5c2f8:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c2fd:	cmpq   $0x20,0x1178(%rsp)
  b5c306:	lea    0x28(%rbp),%rdx
  b5c30a:	jbe    b5c314 <_ZN14CInventoryMenu11createMenusEv+0x5934>
  b5c30c:	mov    0x1218(%rsp),%rdx
  b5c314:	mov    $0xfeff5b,%eax
  b5c319:	nopl   0x0(%rax)
  b5c320:	movzbl (%rax),%ecx
  b5c323:	add    $0x1,%rax
  b5c327:	mov    %ecx,(%rdx)
  b5c329:	add    $0x4,%rdx
  b5c32d:	cmp    $0xfeff66,%rax
  b5c333:	jne    b5c320 <_ZN14CInventoryMenu11createMenusEv+0x5940>
  b5c335:	cmpq   $0x20,0x1178(%rsp)
  b5c33e:	movq   $0xb,0x1170(%rsp)
  b5c34a:	lea    0x54(%rbp),%rax
  b5c34e:	jbe    b5c35c <_ZN14CInventoryMenu11createMenusEv+0x597c>
  b5c350:	mov    0x1218(%rsp),%rax
  b5c358:	add    $0x2c,%rax
  b5c35c:	movl   $0x0,(%rax)
  b5c362:	mov    0x48(%rbx),%rdi
  b5c366:	mov    %rbp,%rsi
  b5c369:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5c36e:	mov    %rax,0x9110(%rbx)
  b5c375:	mov    %rbp,%rdi
  b5c378:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c37d:	mov    0x9110(%rbx),%rdi
  b5c384:	xor    %esi,%esi
  b5c386:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b5c38b:	lea    0x10c0(%rsp),%rbp
  b5c393:	mov    $0x9,%esi
  b5c398:	movq   $0x20,0x10c8(%rsp)
  b5c3a4:	movq   $0x0,0x10d0(%rsp)
  b5c3b0:	movq   $0x0,0x10e0(%rsp)
  b5c3bc:	mov    %rbp,%rdi
  b5c3bf:	movq   $0x0,0x10d8(%rsp)
  b5c3cb:	movq   $0x0,0x1168(%rsp)
  b5c3d7:	movq   $0x0,0x10c0(%rsp)
  b5c3e3:	movl   $0x0,0x10e8(%rsp)
  b5c3ee:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c3f3:	cmpq   $0x20,0x10c8(%rsp)
  b5c3fc:	lea    0x28(%rbp),%rdx
  b5c400:	jbe    b5c40a <_ZN14CInventoryMenu11createMenusEv+0x5a2a>
  b5c402:	mov    0x1168(%rsp),%rdx
  b5c40a:	mov    $0xfeff4e,%eax
  b5c40f:	nop
  b5c410:	movzbl (%rax),%ecx
  b5c413:	add    $0x1,%rax
  b5c417:	mov    %ecx,(%rdx)
  b5c419:	add    $0x4,%rdx
  b5c41d:	cmp    $0xfeff57,%rax
  b5c423:	jne    b5c410 <_ZN14CInventoryMenu11createMenusEv+0x5a30>
  b5c425:	cmpq   $0x20,0x10c8(%rsp)
  b5c42e:	movq   $0x9,0x10c0(%rsp)
  b5c43a:	lea    0x4c(%rbp),%rax
  b5c43e:	jbe    b5c44c <_ZN14CInventoryMenu11createMenusEv+0x5a6c>
  b5c440:	mov    0x1168(%rsp),%rax
  b5c448:	add    $0x24,%rax
  b5c44c:	movl   $0x0,(%rax)
  b5c452:	mov    0x48(%rbx),%rdi
  b5c456:	mov    %rbp,%rsi
  b5c459:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5c45e:	mov    %rax,0x9118(%rbx)
  b5c465:	mov    %rbp,%rdi
  b5c468:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c46d:	mov    0x9118(%rbx),%rdi
  b5c474:	xor    %esi,%esi
  b5c476:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b5c47b:	lea    0x1010(%rsp),%rax
  b5c483:	mov    %rbx,%rbp
  b5c486:	movl   $0x1,0x10(%rsp)
  b5c48e:	add    $0x28,%rax
  b5c492:	mov    %rax,0x18(%rsp)
  b5c497:	lea    0xeb0(%rsp),%rax
  b5c49f:	add    $0x28,%rax
  b5c4a3:	mov    %rax,0x20(%rsp)
  b5c4a8:	lea    0x720(%rsp),%rax
  b5c4b0:	add    $0x28,%rax
  b5c4b4:	mov    %rax,0x28(%rsp)
  b5c4b9:	mov    0x10(%rsp),%r13d
  b5c4be:	mov    0x10(%rsp),%esi
  b5c4c2:	lea    0x4340(%rsp),%rdi
  b5c4ca:	add    $0x12,%r13d
  b5c4ce:	call   c91f60 <_ZN7STRINGS16GetValueAsStringEj>
  b5c4d3:	lea    0x4340(%rsp),%rdx
  b5c4db:	lea    0x4330(%rsp),%rdi
  b5c4e3:	mov    $0xff0cc3,%esi
  b5c4e8:	call   56aee0 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_>
  b5c4ed:	mov    0x4330(%rsp),%rax
  b5c4f5:	movq   $0x20,0x1018(%rsp)
  b5c501:	lea    0x1010(%rsp),%rdi
  b5c509:	movq   $0x0,0x1020(%rsp)
  b5c515:	movq   $0x0,0x1030(%rsp)
  b5c521:	movq   $0x0,0x1028(%rsp)
  b5c52d:	movq   $0x0,0x10b8(%rsp)
  b5c539:	movq   $0x0,0x1010(%rsp)
  b5c545:	movl   $0x0,0x1038(%rsp)
  b5c550:	mov    -0x18(%rax),%r12
  b5c554:	mov    %r12,%rsi
  b5c557:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c55c:	cmpq   $0x21,0x1018(%rsp)
  b5c565:	mov    0x18(%rsp),%rax
  b5c56a:	cmovae 0x10b8(%rsp),%rax
  b5c573:	test   %r12,%r12
  b5c576:	mov    %r12,0x1010(%rsp)
  b5c57e:	movl   $0x0,(%rax,%r12,4)
  b5c586:	je     b5c5c7 <_ZN14CInventoryMenu11createMenusEv+0x5be7>
  b5c588:	sub    $0x1,%r12
  b5c58c:	mov    0x18(%rsp),%rcx
  b5c591:	jmp    b5c59c <_ZN14CInventoryMenu11createMenusEv+0x5bbc>
  b5c593:	nopl   0x0(%rax,%rax,1)
  b5c598:	sub    $0x1,%r12
  b5c59c:	mov    0x4330(%rsp),%rdx
  b5c5a4:	cmpq   $0x21,0x1018(%rsp)
  b5c5ad:	mov    %rcx,%rax
  b5c5b0:	cmovae 0x10b8(%rsp),%rax
  b5c5b9:	test   %r12,%r12
  b5c5bc:	movzbl (%rdx,%r12,1),%edx
  b5c5c1:	mov    %edx,(%rax,%r12,4)
  b5c5c5:	jne    b5c598 <_ZN14CInventoryMenu11createMenusEv+0x5bb8>
  b5c5c7:	mov    0x48(%rbx),%rdi
  b5c5cb:	lea    0x1010(%rsp),%rsi
  b5c5d3:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5c5d8:	lea    0x1010(%rsp),%rdi
  b5c5e0:	mov    %rax,%r15
  b5c5e3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5c5e8:	mov    0x4330(%rsp),%rdi
  b5c5f0:	sub    $0x18,%rdi
  b5c5f4:	cmp    $0x1423a20,%rdi
  b5c5fb:	jne    b5faa2 <_ZN14CInventoryMenu11createMenusEv+0x90c2>
  b5c601:	mov    0x4340(%rsp),%rdi
  b5c609:	mov    $0x1423a20,%eax
  b5c60e:	sub    $0x18,%rdi
  b5c612:	cmp    %rdi,%rax
  b5c615:	jne    b5fa72 <_ZN14CInventoryMenu11createMenusEv+0x9092>
  b5c61b:	mov    %r15,%rdi
  b5c61e:	call   5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  b5c623:	movb   $0x0,0x213(%r15)
  b5c62b:	xor    %esi,%esi
  b5c62d:	mov    %r15,%rdi
  b5c630:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5c635:	mov    %r13d,%r13d
  b5c638:	mov    $0x20,%edi
  b5c63d:	lea    0x80(%rbx,%r13,4),%rax
  b5c645:	mov    %rax,0x1d8(%r15)
  b5c64c:	mov    0x38(%r15),%rax
  b5c650:	mov    0x10(%rax),%r14
  b5c654:	call   552d68 <_Znwm@plt>
  b5c659:	lea    0x38(%r15),%r12
  b5c65d:	lea    0x4320(%rsp),%r13
  b5c665:	movq   $0xfefcd0,(%rax)
  b5c66c:	movq   $0x0,0x10(%rax)
  b5c674:	movq   $0xb45810,0x8(%rax)
  b5c67c:	lea    0x3f60(%rsp),%rdi
  b5c684:	mov    %rbx,0x18(%rax)
  b5c688:	mov    %r13,%rcx
  b5c68b:	mov    %rax,0x4320(%rsp)
  b5c693:	mov    $0x14247e0,%edx
  b5c698:	mov    %r12,%rsi
  b5c69b:	call   *%r14
  b5c69e:	cmpq   $0x0,0x3f60(%rsp)
  b5c6a7:	je     b5c6fe <_ZN14CInventoryMenu11createMenusEv+0x5d1e>
  b5c6a9:	mov    0x3f68(%rsp),%rdx
  b5c6b1:	mov    (%rdx),%eax
  b5c6b3:	sub    $0x1,%eax
  b5c6b6:	test   %eax,%eax
  b5c6b8:	mov    %eax,(%rdx)
  b5c6ba:	jne    b5c6fe <_ZN14CInventoryMenu11createMenusEv+0x5d1e>
  b5c6bc:	mov    0x3f60(%rsp),%r14
  b5c6c4:	test   %r14,%r14
  b5c6c7:	je     b5c6d9 <_ZN14CInventoryMenu11createMenusEv+0x5cf9>
  b5c6c9:	mov    %r14,%rdi
  b5c6cc:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5c6d1:	mov    %r14,%rdi
  b5c6d4:	call   553f18 <_ZdlPv@plt>
  b5c6d9:	mov    0x3f68(%rsp),%rdi
  b5c6e1:	call   553f18 <_ZdlPv@plt>
  b5c6e6:	movq   $0x0,0x3f60(%rsp)
  b5c6f2:	movq   $0x0,0x3f68(%rsp)
  b5c6fe:	mov    %r13,%rdi
  b5c701:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5c706:	mov    0x38(%r15),%rax
  b5c70a:	mov    $0x20,%edi
  b5c70f:	mov    0x10(%rax),%r14
  b5c713:	call   552d68 <_Znwm@plt>
  b5c718:	lea    0x4310(%rsp),%r13
  b5c720:	movq   $0xfefcd0,(%rax)
  b5c727:	movq   $0x0,0x10(%rax)
  b5c72f:	movq   $0xb4d590,0x8(%rax)
  b5c737:	mov    %rbx,0x18(%rax)
  b5c73b:	lea    0x3f50(%rsp),%rdi
  b5c743:	mov    %rax,0x4310(%rsp)
  b5c74b:	mov    %r13,%rcx
  b5c74e:	mov    $0x1423b80,%edx
  b5c753:	mov    %r12,%rsi
  b5c756:	call   *%r14
  b5c759:	cmpq   $0x0,0x3f50(%rsp)
  b5c762:	je     b5c7b9 <_ZN14CInventoryMenu11createMenusEv+0x5dd9>
  b5c764:	mov    0x3f58(%rsp),%rdx
  b5c76c:	mov    (%rdx),%eax
  b5c76e:	sub    $0x1,%eax
  b5c771:	test   %eax,%eax
  b5c773:	mov    %eax,(%rdx)
  b5c775:	jne    b5c7b9 <_ZN14CInventoryMenu11createMenusEv+0x5dd9>
  b5c777:	mov    0x3f50(%rsp),%r14
  b5c77f:	test   %r14,%r14
  b5c782:	je     b5c794 <_ZN14CInventoryMenu11createMenusEv+0x5db4>
  b5c784:	mov    %r14,%rdi
  b5c787:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5c78c:	mov    %r14,%rdi
  b5c78f:	call   553f18 <_ZdlPv@plt>
  b5c794:	mov    0x3f58(%rsp),%rdi
  b5c79c:	call   553f18 <_ZdlPv@plt>
  b5c7a1:	movq   $0x0,0x3f50(%rsp)
  b5c7ad:	movq   $0x0,0x3f58(%rsp)
  b5c7b9:	mov    %r13,%rdi
  b5c7bc:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5c7c1:	mov    0x38(%r15),%rax
  b5c7c5:	mov    $0x20,%edi
  b5c7ca:	mov    0x10(%rax),%r14
  b5c7ce:	call   552d68 <_Znwm@plt>
  b5c7d3:	lea    0x4300(%rsp),%r13
  b5c7db:	movq   $0xfefcd0,(%rax)
  b5c7e2:	movq   $0x0,0x10(%rax)
  b5c7ea:	movq   $0xb4d590,0x8(%rax)
  b5c7f2:	mov    %rbx,0x18(%rax)
  b5c7f6:	lea    0x3f40(%rsp),%rdi
  b5c7fe:	mov    %rax,0x4300(%rsp)
  b5c806:	mov    %r13,%rcx
  b5c809:	mov    $0x1424020,%edx
  b5c80e:	mov    %r12,%rsi
  b5c811:	call   *%r14
  b5c814:	cmpq   $0x0,0x3f40(%rsp)
  b5c81d:	je     b5c874 <_ZN14CInventoryMenu11createMenusEv+0x5e94>
  b5c81f:	mov    0x3f48(%rsp),%rdx
  b5c827:	mov    (%rdx),%eax
  b5c829:	sub    $0x1,%eax
  b5c82c:	test   %eax,%eax
  b5c82e:	mov    %eax,(%rdx)
  b5c830:	jne    b5c874 <_ZN14CInventoryMenu11createMenusEv+0x5e94>
  b5c832:	mov    0x3f40(%rsp),%r14
  b5c83a:	test   %r14,%r14
  b5c83d:	je     b5c84f <_ZN14CInventoryMenu11createMenusEv+0x5e6f>
  b5c83f:	mov    %r14,%rdi
  b5c842:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5c847:	mov    %r14,%rdi
  b5c84a:	call   553f18 <_ZdlPv@plt>
  b5c84f:	mov    0x3f48(%rsp),%rdi
  b5c857:	call   553f18 <_ZdlPv@plt>
  b5c85c:	movq   $0x0,0x3f40(%rsp)
  b5c868:	movq   $0x0,0x3f48(%rsp)
  b5c874:	mov    %r13,%rdi
  b5c877:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5c87c:	mov    0x38(%r15),%rax
  b5c880:	mov    $0x20,%edi
  b5c885:	mov    0x10(%rax),%r14
  b5c889:	call   552d68 <_Znwm@plt>
  b5c88e:	lea    0x42f0(%rsp),%r13
  b5c896:	movq   $0xfefcd0,(%rax)
  b5c89d:	movq   $0x0,0x10(%rax)
  b5c8a5:	movq   $0xb45d30,0x8(%rax)
  b5c8ad:	mov    %rbx,0x18(%rax)
  b5c8b1:	lea    0x3f30(%rsp),%rdi
  b5c8b9:	mov    %rax,0x42f0(%rsp)
  b5c8c1:	mov    %r13,%rcx
  b5c8c4:	mov    $0x1423700,%edx
  b5c8c9:	mov    %r12,%rsi
  b5c8cc:	call   *%r14
  b5c8cf:	cmpq   $0x0,0x3f30(%rsp)
  b5c8d8:	je     b5c92f <_ZN14CInventoryMenu11createMenusEv+0x5f4f>
  b5c8da:	mov    0x3f38(%rsp),%rdx
  b5c8e2:	mov    (%rdx),%eax
  b5c8e4:	sub    $0x1,%eax
  b5c8e7:	test   %eax,%eax
  b5c8e9:	mov    %eax,(%rdx)
  b5c8eb:	jne    b5c92f <_ZN14CInventoryMenu11createMenusEv+0x5f4f>
  b5c8ed:	mov    0x3f30(%rsp),%r12
  b5c8f5:	test   %r12,%r12
  b5c8f8:	je     b5c90a <_ZN14CInventoryMenu11createMenusEv+0x5f2a>
  b5c8fa:	mov    %r12,%rdi
  b5c8fd:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5c902:	mov    %r12,%rdi
  b5c905:	call   553f18 <_ZdlPv@plt>
  b5c90a:	mov    0x3f38(%rsp),%rdi
  b5c912:	call   553f18 <_ZdlPv@plt>
  b5c917:	movq   $0x0,0x3f30(%rsp)
  b5c923:	movq   $0x0,0x3f38(%rsp)
  b5c92f:	mov    %r13,%rdi
  b5c932:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5c937:	lea    0xe00(%rsp),%rdi
  b5c93f:	mov    %r15,0x10c0(%rbp)
  b5c946:	xor    %esi,%esi
  b5c948:	movq   $0x20,0xe08(%rsp)
  b5c954:	movq   $0x0,0xe10(%rsp)
  b5c960:	movq   $0x0,0xe20(%rsp)
  b5c96c:	movq   $0x0,0xe18(%rsp)
  b5c978:	movq   $0x0,0xea8(%rsp)
  b5c984:	movq   $0x0,0xe00(%rsp)
  b5c990:	movl   $0x0,0xe28(%rsp)
  b5c99b:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5c9a0:	cmpq   $0x20,0xe08(%rsp)
  b5c9a9:	movq   $0x0,0xe00(%rsp)
  b5c9b5:	ja     b5e826 <_ZN14CInventoryMenu11createMenusEv+0x7e46>
  b5c9bb:	lea    0xe00(%rsp),%rax
  b5c9c3:	add    $0x28,%rax
  b5c9c7:	lea    0x44cb(%rsp),%rdx
  b5c9cf:	lea    0x42e0(%rsp),%rdi
  b5c9d7:	movl   $0x0,(%rax)
  b5c9dd:	mov    $0xfe468a,%esi
  b5c9e2:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5c9e7:	lea    0x42e0(%rsp),%rsi
  b5c9ef:	lea    0x42d0(%rsp),%rdi
  b5c9f7:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5c9fc:	mov    0x42d0(%rsp),%rax
  b5ca04:	movq   $0x20,0xeb8(%rsp)
  b5ca10:	lea    0xeb0(%rsp),%rdi
  b5ca18:	movq   $0x0,0xec0(%rsp)
  b5ca24:	movq   $0x0,0xed0(%rsp)
  b5ca30:	movq   $0x0,0xec8(%rsp)
  b5ca3c:	movq   $0x0,0xf58(%rsp)
  b5ca48:	movq   $0x0,0xeb0(%rsp)
  b5ca54:	movl   $0x0,0xed8(%rsp)
  b5ca5f:	mov    -0x18(%rax),%r12
  b5ca63:	mov    %r12,%rsi
  b5ca66:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ca6b:	cmpq   $0x21,0xeb8(%rsp)
  b5ca74:	mov    0x20(%rsp),%rax
  b5ca79:	cmovae 0xf58(%rsp),%rax
  b5ca82:	test   %r12,%r12
  b5ca85:	mov    %r12,0xeb0(%rsp)
  b5ca8d:	movl   $0x0,(%rax,%r12,4)
  b5ca95:	je     b5cad7 <_ZN14CInventoryMenu11createMenusEv+0x60f7>
  b5ca97:	sub    $0x1,%r12
  b5ca9b:	mov    0x20(%rsp),%rcx
  b5caa0:	jmp    b5caac <_ZN14CInventoryMenu11createMenusEv+0x60cc>
  b5caa2:	nopw   0x0(%rax,%rax,1)
  b5caa8:	sub    $0x1,%r12
  b5caac:	mov    0x42d0(%rsp),%rdx
  b5cab4:	cmpq   $0x21,0xeb8(%rsp)
  b5cabd:	mov    %rcx,%rax
  b5cac0:	cmovae 0xf58(%rsp),%rax
  b5cac9:	test   %r12,%r12
  b5cacc:	movzbl (%rdx,%r12,1),%edx
  b5cad1:	mov    %edx,(%rax,%r12,4)
  b5cad5:	jne    b5caa8 <_ZN14CInventoryMenu11createMenusEv+0x60c8>
  b5cad7:	xor    %r12d,%r12d
  b5cada:	cmpb   $0x0,0x487d91(%rip)        # fe4872 <_ZTI17CSpawnClassParser+0x572>
  b5cae1:	mov    $0xfe4873,%r14d
  b5cae7:	movq   $0x20,0xf68(%rsp)
  b5caf3:	movq   $0x0,0xf70(%rsp)
  b5caff:	mov    %r14,%rax
  b5cb02:	movq   $0x0,0xf80(%rsp)
  b5cb0e:	movq   $0x0,0xf78(%rsp)
  b5cb1a:	movq   $0x0,0x1008(%rsp)
  b5cb26:	movq   $0x0,0xf60(%rsp)
  b5cb32:	movl   $0x0,0xf88(%rsp)
  b5cb3d:	je     b5cb55 <_ZN14CInventoryMenu11createMenusEv+0x6175>
  b5cb3f:	nop
  b5cb40:	movzbl (%rax),%edx
  b5cb43:	mov    %rax,%r12
  b5cb46:	add    $0x1,%rax
  b5cb4a:	sub    $0xfe4872,%r12
  b5cb51:	test   %dl,%dl
  b5cb53:	jne    b5cb40 <_ZN14CInventoryMenu11createMenusEv+0x6160>
  b5cb55:	cmp    0x8c78c4(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5cb5c:	je     b5ed2d <_ZN14CInventoryMenu11createMenusEv+0x834d>
  b5cb62:	mov    %r12,%rax
  b5cb65:	mov    $0xfe4872,%edx
  b5cb6a:	xor    %r13d,%r13d
  b5cb6d:	jmp    b5cb74 <_ZN14CInventoryMenu11createMenusEv+0x6194>
  b5cb6f:	nop
  b5cb70:	add    $0x1,%r13
  b5cb74:	test   %rax,%rax
  b5cb77:	je     b5cbb8 <_ZN14CInventoryMenu11createMenusEv+0x61d8>
  b5cb79:	movzbl (%rdx),%ecx
  b5cb7c:	sub    $0x1,%rax
  b5cb80:	add    $0x1,%rdx
  b5cb84:	test   %cl,%cl
  b5cb86:	jns    b5cb70 <_ZN14CInventoryMenu11createMenusEv+0x6190>
  b5cb88:	cmp    $0xdf,%cl
  b5cb8b:	ja     b5cba0 <_ZN14CInventoryMenu11createMenusEv+0x61c0>
  b5cb8d:	sub    $0x1,%rax
  b5cb91:	add    $0x1,%rdx
  b5cb95:	jmp    b5cb70 <_ZN14CInventoryMenu11createMenusEv+0x6190>
  b5cb97:	nopw   0x0(%rax,%rax,1)
  b5cba0:	cmp    $0xef,%cl
  b5cba3:	ja     b5db40 <_ZN14CInventoryMenu11createMenusEv+0x7160>
  b5cba9:	sub    $0x2,%rax
  b5cbad:	add    $0x2,%rdx
  b5cbb1:	jmp    b5cb70 <_ZN14CInventoryMenu11createMenusEv+0x6190>
  b5cbb3:	nopl   0x0(%rax,%rax,1)
  b5cbb8:	lea    0xf60(%rsp),%rdi
  b5cbc0:	mov    %r13,%rsi
  b5cbc3:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5cbc8:	mov    0xf68(%rsp),%rcx
  b5cbd0:	cmp    $0x20,%rcx
  b5cbd4:	ja     b5e7b9 <_ZN14CInventoryMenu11createMenusEv+0x7dd9>
  b5cbda:	lea    0xf60(%rsp),%rsi
  b5cbe2:	add    $0x28,%rsi
  b5cbe6:	test   %r12,%r12
  b5cbe9:	je     b5e77e <_ZN14CInventoryMenu11createMenusEv+0x7d9e>
  b5cbef:	test   %rcx,%rcx
  b5cbf2:	setne  %al
  b5cbf5:	test   %al,%al
  b5cbf7:	je     b5cc60 <_ZN14CInventoryMenu11createMenusEv+0x6280>
  b5cbf9:	xor    %edx,%edx
  b5cbfb:	xor    %eax,%eax
  b5cbfd:	jmp    b5cc19 <_ZN14CInventoryMenu11createMenusEv+0x6239>
  b5cbff:	nop
  b5cc00:	movzbl %dl,%edx
  b5cc03:	mov    %edx,(%rsi)
  b5cc05:	mov    %eax,%edx
  b5cc07:	sub    $0x1,%rcx
  b5cc0b:	cmp    %r12,%rdx
  b5cc0e:	jae    b5cc60 <_ZN14CInventoryMenu11createMenusEv+0x6280>
  b5cc10:	test   %rcx,%rcx
  b5cc13:	je     b5cc60 <_ZN14CInventoryMenu11createMenusEv+0x6280>
  b5cc15:	add    $0x4,%rsi
  b5cc19:	movzbl 0xfe4872(%rdx),%edx
  b5cc20:	add    $0x1,%eax
  b5cc23:	test   %dl,%dl
  b5cc25:	jns    b5cc00 <_ZN14CInventoryMenu11createMenusEv+0x6220>
  b5cc27:	cmp    $0xdf,%dl
  b5cc2a:	ja     b5d640 <_ZN14CInventoryMenu11createMenusEv+0x6c60>
  b5cc30:	mov    $0x1f,%edi
  b5cc35:	sub    $0x1,%rcx
  b5cc39:	and    %edx,%edi
  b5cc3b:	mov    %eax,%edx
  b5cc3d:	add    $0x1,%eax
  b5cc40:	movzbl 0xfe4872(%rdx),%edx
  b5cc47:	shl    $0x6,%edi
  b5cc4a:	and    $0x3f,%edx
  b5cc4d:	or     %edi,%edx
  b5cc4f:	mov    %edx,(%rsi)
  b5cc51:	mov    %eax,%edx
  b5cc53:	cmp    %r12,%rdx
  b5cc56:	jb     b5cc10 <_ZN14CInventoryMenu11createMenusEv+0x6230>
  b5cc58:	nopl   0x0(%rax,%rax,1)
  b5cc60:	cmpq   $0x20,0xf68(%rsp)
  b5cc69:	mov    %r13,0xf60(%rsp)
  b5cc71:	ja     b5e8e8 <_ZN14CInventoryMenu11createMenusEv+0x7f08>
  b5cc77:	lea    0xf60(%rsp),%rax
  b5cc7f:	add    $0x28,%rax
  b5cc83:	movl   $0x0,(%rax,%r13,4)
  b5cc8b:	mov    0x8c79ce(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5cc92:	lea    0xe00(%rsp),%rcx
  b5cc9a:	lea    0xeb0(%rsp),%rdx
  b5cca2:	lea    0xf60(%rsp),%rsi
  b5ccaa:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5ccaf:	lea    0xf60(%rsp),%rdi
  b5ccb7:	mov    %rax,0x1870(%rbp)
  b5ccbe:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ccc3:	lea    0xeb0(%rsp),%rdi
  b5cccb:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ccd0:	mov    0x42d0(%rsp),%rdi
  b5ccd8:	mov    $0x1423a20,%eax
  b5ccdd:	sub    $0x18,%rdi
  b5cce1:	cmp    %rdi,%rax
  b5cce4:	jne    b5f482 <_ZN14CInventoryMenu11createMenusEv+0x8aa2>
  b5ccea:	mov    0x42e0(%rsp),%rdi
  b5ccf2:	mov    $0x1423a20,%eax
  b5ccf7:	sub    $0x18,%rdi
  b5ccfb:	cmp    %rdi,%rax
  b5ccfe:	jne    b5fbe5 <_ZN14CInventoryMenu11createMenusEv+0x9205>
  b5cd04:	lea    0xe00(%rsp),%rdi
  b5cd0c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5cd11:	lea    0xd50(%rsp),%r12
  b5cd19:	mov    $0x5,%esi
  b5cd1e:	movq   $0x20,0xd58(%rsp)
  b5cd2a:	movq   $0x0,0xd60(%rsp)
  b5cd36:	movq   $0x0,0xd70(%rsp)
  b5cd42:	mov    %r12,%rdi
  b5cd45:	movq   $0x0,0xd68(%rsp)
  b5cd51:	movq   $0x0,0xdf8(%rsp)
  b5cd5d:	movq   $0x0,0xd50(%rsp)
  b5cd69:	movl   $0x0,0xd78(%rsp)
  b5cd74:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5cd79:	cmpq   $0x20,0xd58(%rsp)
  b5cd82:	lea    0x28(%r12),%rdx
  b5cd87:	jbe    b5cd91 <_ZN14CInventoryMenu11createMenusEv+0x63b1>
  b5cd89:	mov    0xdf8(%rsp),%rdx
  b5cd91:	mov    $0xfe4944,%eax
  b5cd96:	cs nopw 0x0(%rax,%rax,1)
  b5cda0:	movzbl (%rax),%ecx
  b5cda3:	add    $0x1,%rax
  b5cda7:	mov    %ecx,(%rdx)
  b5cda9:	add    $0x4,%rdx
  b5cdad:	cmp    $0xfe4949,%rax
  b5cdb3:	jne    b5cda0 <_ZN14CInventoryMenu11createMenusEv+0x63c0>
  b5cdb5:	cmpq   $0x20,0xd58(%rsp)
  b5cdbe:	movq   $0x5,0xd50(%rsp)
  b5cdca:	lea    0x3c(%r12),%rax
  b5cdcf:	jbe    b5cddd <_ZN14CInventoryMenu11createMenusEv+0x63fd>
  b5cdd1:	mov    0xdf8(%rsp),%rax
  b5cdd9:	add    $0x14,%rax
  b5cddd:	movl   $0x0,(%rax)
  b5cde3:	mov    0x1870(%rbp),%rdi
  b5cdea:	mov    %r12,%rsi
  b5cded:	call   555288 <_ZN5CEGUI6Window7setFontERKNS_6StringE@plt>
  b5cdf2:	mov    %r12,%rdi
  b5cdf5:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5cdfa:	lea    0x3f20(%rsp),%r12
  b5ce02:	mov    %r15,%rsi
  b5ce05:	mov    %r12,%rdi
  b5ce08:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5ce0d:	mov    0x1870(%rbp),%rdi
  b5ce14:	mov    %r12,%rsi
  b5ce17:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5ce1c:	mov    %r15,%rdi
  b5ce1f:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5ce24:	mov    (%rax),%rdx
  b5ce27:	lea    0xbf0(%rsp),%r13
  b5ce2f:	mov    $0xc,%esi
  b5ce34:	mov    %r13,%rdi
  b5ce37:	mov    %rdx,0x3f10(%rsp)
  b5ce3f:	mov    0x8(%rax),%rax
  b5ce43:	movq   $0x20,0xbf8(%rsp)
  b5ce4f:	movq   $0x0,0xc00(%rsp)
  b5ce5b:	movq   $0x0,0xc10(%rsp)
  b5ce67:	movq   $0x0,0xc08(%rsp)
  b5ce73:	mov    %rax,0x3f18(%rsp)
  b5ce7b:	movq   $0x0,0xc98(%rsp)
  b5ce87:	movq   $0x0,0xbf0(%rsp)
  b5ce93:	movl   $0x0,0xc18(%rsp)
  b5ce9e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5cea3:	cmpq   $0x20,0xbf8(%rsp)
  b5ceac:	lea    0x28(%r13),%rdx
  b5ceb0:	jbe    b5ceba <_ZN14CInventoryMenu11createMenusEv+0x64da>
  b5ceb2:	mov    0xc98(%rsp),%rdx
  b5ceba:	mov    $0xfe6021,%eax
  b5cebf:	nop
  b5cec0:	movzbl (%rax),%ecx
  b5cec3:	add    $0x1,%rax
  b5cec7:	mov    %ecx,(%rdx)
  b5cec9:	add    $0x4,%rdx
  b5cecd:	cmp    $0xfe602d,%rax
  b5ced3:	jne    b5cec0 <_ZN14CInventoryMenu11createMenusEv+0x64e0>
  b5ced5:	cmpq   $0x20,0xbf8(%rsp)
  b5cede:	movq   $0xc,0xbf0(%rsp)
  b5ceea:	lea    0x58(%r13),%rax
  b5ceee:	jbe    b5cefc <_ZN14CInventoryMenu11createMenusEv+0x651c>
  b5cef0:	mov    0xc98(%rsp),%rax
  b5cef8:	add    $0x30,%rax
  b5cefc:	lea    0xca0(%rsp),%r12
  b5cf04:	movl   $0x0,(%rax)
  b5cf0a:	mov    $0x12,%esi
  b5cf0f:	movq   $0x20,0xca8(%rsp)
  b5cf1b:	movq   $0x0,0xcb0(%rsp)
  b5cf27:	mov    %r12,%rdi
  b5cf2a:	movq   $0x0,0xcc0(%rsp)
  b5cf36:	movq   $0x0,0xcb8(%rsp)
  b5cf42:	movq   $0x0,0xd48(%rsp)
  b5cf4e:	movq   $0x0,0xca0(%rsp)
  b5cf5a:	movl   $0x0,0xcc8(%rsp)
  b5cf65:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5cf6a:	cmpq   $0x20,0xca8(%rsp)
  b5cf73:	lea    0x28(%r12),%rdx
  b5cf78:	jbe    b5cf82 <_ZN14CInventoryMenu11createMenusEv+0x65a2>
  b5cf7a:	mov    0xd48(%rsp),%rdx
  b5cf82:	mov    $0xfe48bd,%eax
  b5cf87:	nopw   0x0(%rax,%rax,1)
  b5cf90:	movzbl (%rax),%ecx
  b5cf93:	add    $0x1,%rax
  b5cf97:	mov    %ecx,(%rdx)
  b5cf99:	add    $0x4,%rdx
  b5cf9d:	cmp    $0xfe48cf,%rax
  b5cfa3:	jne    b5cf90 <_ZN14CInventoryMenu11createMenusEv+0x65b0>
  b5cfa5:	cmpq   $0x20,0xca8(%rsp)
  b5cfae:	movq   $0x12,0xca0(%rsp)
  b5cfba:	lea    0x70(%r12),%rax
  b5cfbf:	jbe    b5cfcd <_ZN14CInventoryMenu11createMenusEv+0x65ed>
  b5cfc1:	mov    0xd48(%rsp),%rax
  b5cfc9:	add    $0x48,%rax
  b5cfcd:	movl   $0x0,(%rax)
  b5cfd3:	mov    0x1870(%rbp),%rdi
  b5cfda:	mov    %r13,%rdx
  b5cfdd:	mov    %r12,%rsi
  b5cfe0:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5cfe5:	mov    %r12,%rdi
  b5cfe8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5cfed:	mov    %r13,%rdi
  b5cff0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5cff5:	lea    0xa90(%rsp),%r13
  b5cffd:	mov    $0xd,%esi
  b5d002:	movq   $0x20,0xa98(%rsp)
  b5d00e:	movq   $0x0,0xaa0(%rsp)
  b5d01a:	movq   $0x0,0xab0(%rsp)
  b5d026:	mov    %r13,%rdi
  b5d029:	movq   $0x0,0xaa8(%rsp)
  b5d035:	movq   $0x0,0xb38(%rsp)
  b5d041:	movq   $0x0,0xa90(%rsp)
  b5d04d:	movl   $0x0,0xab8(%rsp)
  b5d058:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d05d:	cmpq   $0x20,0xa98(%rsp)
  b5d066:	lea    0x28(%r13),%rdx
  b5d06a:	jbe    b5d074 <_ZN14CInventoryMenu11createMenusEv+0x6694>
  b5d06c:	mov    0xb38(%rsp),%rdx
  b5d074:	mov    $0xfe6013,%eax
  b5d079:	nopl   0x0(%rax)
  b5d080:	movzbl (%rax),%ecx
  b5d083:	add    $0x1,%rax
  b5d087:	mov    %ecx,(%rdx)
  b5d089:	add    $0x4,%rdx
  b5d08d:	cmp    $0xfe6020,%rax
  b5d093:	jne    b5d080 <_ZN14CInventoryMenu11createMenusEv+0x66a0>
  b5d095:	cmpq   $0x20,0xa98(%rsp)
  b5d09e:	movq   $0xd,0xa90(%rsp)
  b5d0aa:	lea    0x5c(%r13),%rax
  b5d0ae:	jbe    b5d0bc <_ZN14CInventoryMenu11createMenusEv+0x66dc>
  b5d0b0:	mov    0xb38(%rsp),%rax
  b5d0b8:	add    $0x34,%rax
  b5d0bc:	lea    0xb40(%rsp),%r12
  b5d0c4:	movl   $0x0,(%rax)
  b5d0ca:	mov    $0xe,%esi
  b5d0cf:	movq   $0x20,0xb48(%rsp)
  b5d0db:	movq   $0x0,0xb50(%rsp)
  b5d0e7:	mov    %r12,%rdi
  b5d0ea:	movq   $0x0,0xb60(%rsp)
  b5d0f6:	movq   $0x0,0xb58(%rsp)
  b5d102:	movq   $0x0,0xbe8(%rsp)
  b5d10e:	movq   $0x0,0xb40(%rsp)
  b5d11a:	movl   $0x0,0xb68(%rsp)
  b5d125:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d12a:	cmpq   $0x20,0xb48(%rsp)
  b5d133:	lea    0x28(%r12),%rdx
  b5d138:	jbe    b5d142 <_ZN14CInventoryMenu11createMenusEv+0x6762>
  b5d13a:	mov    0xbe8(%rsp),%rdx
  b5d142:	mov    $0xfe48a0,%eax
  b5d147:	nopw   0x0(%rax,%rax,1)
  b5d150:	movzbl (%rax),%ecx
  b5d153:	add    $0x1,%rax
  b5d157:	mov    %ecx,(%rdx)
  b5d159:	add    $0x4,%rdx
  b5d15d:	cmp    $0xfe48ae,%rax
  b5d163:	jne    b5d150 <_ZN14CInventoryMenu11createMenusEv+0x6770>
  b5d165:	cmpq   $0x20,0xb48(%rsp)
  b5d16e:	movq   $0xe,0xb40(%rsp)
  b5d17a:	lea    0x60(%r12),%rax
  b5d17f:	jbe    b5d18d <_ZN14CInventoryMenu11createMenusEv+0x67ad>
  b5d181:	mov    0xbe8(%rsp),%rax
  b5d189:	add    $0x38,%rax
  b5d18d:	movl   $0x0,(%rax)
  b5d193:	mov    0x1870(%rbp),%rdi
  b5d19a:	mov    %r13,%rdx
  b5d19d:	mov    %r12,%rsi
  b5d1a0:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5d1a5:	mov    %r12,%rdi
  b5d1a8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d1ad:	mov    %r13,%rdi
  b5d1b0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d1b5:	mov    0x1870(%rbp),%rax
  b5d1bc:	lea    0x3f10(%rsp),%rsi
  b5d1c4:	movb   $0x1,0x3e2(%rax)
  b5d1cb:	mov    0x1870(%rbp),%rdi
  b5d1d2:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5d1d7:	mov    0x10c0(%rbp),%rax
  b5d1de:	mov    0x1870(%rbp),%rsi
  b5d1e5:	mov    0xb0(%rax),%rdi
  b5d1ec:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5d1f1:	cmpq   $0x0,0x8c7227(%rip)        # 1424420 <_ZN5CEGUI6String4nposE>
  b5d1f9:	movq   $0x20,0x9e8(%rsp)
  b5d205:	movq   $0x0,0x9f0(%rsp)
  b5d211:	movq   $0x0,0xa00(%rsp)
  b5d21d:	movq   $0x0,0x9f8(%rsp)
  b5d229:	movq   $0x0,0xa88(%rsp)
  b5d235:	movq   $0x0,0x9e0(%rsp)
  b5d241:	movl   $0x0,0xa08(%rsp)
  b5d24c:	je     b5ed8e <_ZN14CInventoryMenu11createMenusEv+0x83ae>
  b5d252:	lea    0x9e0(%rsp),%r12
  b5d25a:	xor    %esi,%esi
  b5d25c:	mov    %r12,%rdi
  b5d25f:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d264:	cmpq   $0x20,0x9e8(%rsp)
  b5d26d:	movq   $0x0,0x9e0(%rsp)
  b5d279:	lea    0x28(%r12),%rax
  b5d27e:	jbe    b5d288 <_ZN14CInventoryMenu11createMenusEv+0x68a8>
  b5d280:	mov    0xa88(%rsp),%rax
  b5d288:	movl   $0x0,(%rax)
  b5d28e:	mov    0x1870(%rbp),%rdi
  b5d295:	mov    %r12,%rsi
  b5d298:	call   555c08 <_ZN5CEGUI6Window7setTextERKNS_6StringE@plt>
  b5d29d:	mov    %r12,%rdi
  b5d2a0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d2a5:	movss  0x44754f(%rip),%xmm3        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  b5d2ad:	lea    0x3e80(%rsp),%r12
  b5d2b5:	movaps %xmm3,%xmm2
  b5d2b8:	movaps %xmm3,%xmm1
  b5d2bb:	movaps %xmm3,%xmm0
  b5d2be:	mov    %r12,%rdi
  b5d2c1:	call   554118 <_ZN5CEGUI6colourC1Effff@plt>
  b5d2c6:	lea    0x930(%rsp),%r13
  b5d2ce:	mov    %r12,%rsi
  b5d2d1:	mov    %r13,%rdi
  b5d2d4:	call   555fc8 <_ZN5CEGUI14PropertyHelper14colourToStringERKNS_6colourE@plt>
  b5d2d9:	lea    0x880(%rsp),%r12
  b5d2e1:	mov    $0xa,%esi
  b5d2e6:	movq   $0x20,0x888(%rsp)
  b5d2f2:	movq   $0x0,0x890(%rsp)
  b5d2fe:	movq   $0x0,0x8a0(%rsp)
  b5d30a:	mov    %r12,%rdi
  b5d30d:	movq   $0x0,0x898(%rsp)
  b5d319:	movq   $0x0,0x928(%rsp)
  b5d325:	movq   $0x0,0x880(%rsp)
  b5d331:	movl   $0x0,0x8a8(%rsp)
  b5d33c:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d341:	cmpq   $0x20,0x888(%rsp)
  b5d34a:	lea    0x28(%r12),%rdx
  b5d34f:	jbe    b5d359 <_ZN14CInventoryMenu11createMenusEv+0x6979>
  b5d351:	mov    0x928(%rsp),%rdx
  b5d359:	mov    $0xfe4654,%eax
  b5d35e:	xchg   %ax,%ax
  b5d360:	movzbl (%rax),%ecx
  b5d363:	add    $0x1,%rax
  b5d367:	mov    %ecx,(%rdx)
  b5d369:	add    $0x4,%rdx
  b5d36d:	cmp    $0xfe465e,%rax
  b5d373:	jne    b5d360 <_ZN14CInventoryMenu11createMenusEv+0x6980>
  b5d375:	cmpq   $0x20,0x888(%rsp)
  b5d37e:	movq   $0xa,0x880(%rsp)
  b5d38a:	lea    0x50(%r12),%rax
  b5d38f:	jbe    b5d39d <_ZN14CInventoryMenu11createMenusEv+0x69bd>
  b5d391:	mov    0x928(%rsp),%rax
  b5d399:	add    $0x28,%rax
  b5d39d:	movl   $0x0,(%rax)
  b5d3a3:	mov    0x1870(%rbp),%rdi
  b5d3aa:	mov    %r13,%rdx
  b5d3ad:	mov    %r12,%rsi
  b5d3b0:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b5d3b5:	mov    %r12,%rdi
  b5d3b8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d3bd:	mov    %r13,%rdi
  b5d3c0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d3c5:	mov    0x1870(%rbp),%rdi
  b5d3cc:	mov    $0x1,%esi
  b5d3d1:	call   5554d8 <_ZN5CEGUI6Window14setAlwaysOnTopEb@plt>
  b5d3d6:	lea    0x670(%rsp),%rdi
  b5d3de:	xor    %esi,%esi
  b5d3e0:	movq   $0x20,0x678(%rsp)
  b5d3ec:	movq   $0x0,0x680(%rsp)
  b5d3f8:	movq   $0x0,0x690(%rsp)
  b5d404:	movq   $0x0,0x688(%rsp)
  b5d410:	movq   $0x0,0x718(%rsp)
  b5d41c:	movq   $0x0,0x670(%rsp)
  b5d428:	movl   $0x0,0x698(%rsp)
  b5d433:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d438:	cmpq   $0x20,0x678(%rsp)
  b5d441:	movq   $0x0,0x670(%rsp)
  b5d44d:	ja     b5ea05 <_ZN14CInventoryMenu11createMenusEv+0x8025>
  b5d453:	lea    0x670(%rsp),%rax
  b5d45b:	add    $0x28,%rax
  b5d45f:	lea    0x44ca(%rsp),%rdx
  b5d467:	lea    0x42c0(%rsp),%rdi
  b5d46f:	movl   $0x0,(%rax)
  b5d475:	mov    $0xfe468a,%esi
  b5d47a:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5d47f:	lea    0x42c0(%rsp),%rsi
  b5d487:	lea    0x42b0(%rsp),%rdi
  b5d48f:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5d494:	mov    0x42b0(%rsp),%rax
  b5d49c:	movq   $0x20,0x728(%rsp)
  b5d4a8:	lea    0x720(%rsp),%rdi
  b5d4b0:	movq   $0x0,0x730(%rsp)
  b5d4bc:	movq   $0x0,0x740(%rsp)
  b5d4c8:	movq   $0x0,0x738(%rsp)
  b5d4d4:	movq   $0x0,0x7c8(%rsp)
  b5d4e0:	movq   $0x0,0x720(%rsp)
  b5d4ec:	movl   $0x0,0x748(%rsp)
  b5d4f7:	mov    -0x18(%rax),%r12
  b5d4fb:	mov    %r12,%rsi
  b5d4fe:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d503:	cmpq   $0x21,0x728(%rsp)
  b5d50c:	mov    0x28(%rsp),%rax
  b5d511:	cmovae 0x7c8(%rsp),%rax
  b5d51a:	test   %r12,%r12
  b5d51d:	mov    %r12,0x720(%rsp)
  b5d525:	movl   $0x0,(%rax,%r12,4)
  b5d52d:	je     b5d56f <_ZN14CInventoryMenu11createMenusEv+0x6b8f>
  b5d52f:	sub    $0x1,%r12
  b5d533:	mov    0x28(%rsp),%rcx
  b5d538:	jmp    b5d544 <_ZN14CInventoryMenu11createMenusEv+0x6b64>
  b5d53a:	nopw   0x0(%rax,%rax,1)
  b5d540:	sub    $0x1,%r12
  b5d544:	mov    0x42b0(%rsp),%rdx
  b5d54c:	cmpq   $0x21,0x728(%rsp)
  b5d555:	mov    %rcx,%rax
  b5d558:	cmovae 0x7c8(%rsp),%rax
  b5d561:	test   %r12,%r12
  b5d564:	movzbl (%rdx,%r12,1),%edx
  b5d569:	mov    %edx,(%rax,%r12,4)
  b5d56d:	jne    b5d540 <_ZN14CInventoryMenu11createMenusEv+0x6b60>
  b5d56f:	xor    %r12d,%r12d
  b5d572:	cmpb   $0x0,0x473686(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5d579:	mov    $0xfd0c00,%r14d
  b5d57f:	movq   $0x20,0x7d8(%rsp)
  b5d58b:	movq   $0x0,0x7e0(%rsp)
  b5d597:	mov    %r14,%rax
  b5d59a:	movq   $0x0,0x7f0(%rsp)
  b5d5a6:	movq   $0x0,0x7e8(%rsp)
  b5d5b2:	movq   $0x0,0x878(%rsp)
  b5d5be:	movq   $0x0,0x7d0(%rsp)
  b5d5ca:	movl   $0x0,0x7f8(%rsp)
  b5d5d5:	je     b5d5f5 <_ZN14CInventoryMenu11createMenusEv+0x6c15>
  b5d5d7:	nopw   0x0(%rax,%rax,1)
  b5d5e0:	movzbl (%rax),%edx
  b5d5e3:	mov    %rax,%r12
  b5d5e6:	add    $0x1,%rax
  b5d5ea:	sub    $0xfd0bff,%r12
  b5d5f1:	test   %dl,%dl
  b5d5f3:	jne    b5d5e0 <_ZN14CInventoryMenu11createMenusEv+0x6c00>
  b5d5f5:	cmp    0x8c6e24(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5d5fc:	je     b5edef <_ZN14CInventoryMenu11createMenusEv+0x840f>
  b5d602:	mov    %r12,%rax
  b5d605:	mov    $0xfd0bff,%edx
  b5d60a:	xor    %r13d,%r13d
  b5d60d:	jmp    b5d614 <_ZN14CInventoryMenu11createMenusEv+0x6c34>
  b5d60f:	nop
  b5d610:	add    $0x1,%r13
  b5d614:	test   %rax,%rax
  b5d617:	je     b5d6a0 <_ZN14CInventoryMenu11createMenusEv+0x6cc0>
  b5d61d:	movzbl (%rdx),%ecx
  b5d620:	sub    $0x1,%rax
  b5d624:	add    $0x1,%rdx
  b5d628:	test   %cl,%cl
  b5d62a:	jns    b5d610 <_ZN14CInventoryMenu11createMenusEv+0x6c30>
  b5d62c:	cmp    $0xdf,%cl
  b5d62f:	ja     b5d680 <_ZN14CInventoryMenu11createMenusEv+0x6ca0>
  b5d631:	sub    $0x1,%rax
  b5d635:	add    $0x1,%rdx
  b5d639:	jmp    b5d610 <_ZN14CInventoryMenu11createMenusEv+0x6c30>
  b5d63b:	nopl   0x0(%rax,%rax,1)
  b5d640:	cmp    $0xef,%dl
  b5d643:	ja     b5db50 <_ZN14CInventoryMenu11createMenusEv+0x7170>
  b5d649:	mov    %edx,%edi
  b5d64b:	lea    0x1(%rax),%edx
  b5d64e:	shl    $0xc,%edi
  b5d651:	movzbl 0xfe4872(%rdx),%edx
  b5d658:	and    $0xf000,%edi
  b5d65e:	and    $0x3f,%edx
  b5d661:	or     %edi,%edx
  b5d663:	mov    %eax,%edi
  b5d665:	add    $0x2,%eax
  b5d668:	movzbl 0xfe4872(%rdi),%edi
  b5d66f:	and    $0x3f,%edi
  b5d672:	shl    $0x6,%edi
  b5d675:	or     %edi,%edx
  b5d677:	jmp    b5cc03 <_ZN14CInventoryMenu11createMenusEv+0x6223>
  b5d67c:	nopl   0x0(%rax)
  b5d680:	cmp    $0xef,%cl
  b5d683:	ja     b5e729 <_ZN14CInventoryMenu11createMenusEv+0x7d49>
  b5d689:	sub    $0x2,%rax
  b5d68d:	add    $0x2,%rdx
  b5d691:	jmp    b5d610 <_ZN14CInventoryMenu11createMenusEv+0x6c30>
  b5d696:	cs nopw 0x0(%rax,%rax,1)
  b5d6a0:	lea    0x7d0(%rsp),%rdi
  b5d6a8:	mov    %r13,%rsi
  b5d6ab:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d6b0:	mov    0x7d8(%rsp),%rcx
  b5d6b8:	cmp    $0x20,%rcx
  b5d6bc:	ja     b5e94a <_ZN14CInventoryMenu11createMenusEv+0x7f6a>
  b5d6c2:	lea    0x7d0(%rsp),%rsi
  b5d6ca:	add    $0x28,%rsi
  b5d6ce:	test   %r12,%r12
  b5d6d1:	je     b5e95b <_ZN14CInventoryMenu11createMenusEv+0x7f7b>
  b5d6d7:	test   %rcx,%rcx
  b5d6da:	setne  %al
  b5d6dd:	test   %al,%al
  b5d6df:	je     b5d750 <_ZN14CInventoryMenu11createMenusEv+0x6d70>
  b5d6e1:	xor    %edx,%edx
  b5d6e3:	xor    %eax,%eax
  b5d6e5:	jmp    b5d709 <_ZN14CInventoryMenu11createMenusEv+0x6d29>
  b5d6e7:	nopw   0x0(%rax,%rax,1)
  b5d6f0:	movzbl %dl,%edx
  b5d6f3:	mov    %edx,(%rsi)
  b5d6f5:	mov    %eax,%edx
  b5d6f7:	sub    $0x1,%rcx
  b5d6fb:	cmp    %r12,%rdx
  b5d6fe:	jae    b5d750 <_ZN14CInventoryMenu11createMenusEv+0x6d70>
  b5d700:	test   %rcx,%rcx
  b5d703:	je     b5d750 <_ZN14CInventoryMenu11createMenusEv+0x6d70>
  b5d705:	add    $0x4,%rsi
  b5d709:	movzbl 0xfd0bff(%rdx),%edx
  b5d710:	add    $0x1,%eax
  b5d713:	test   %dl,%dl
  b5d715:	jns    b5d6f0 <_ZN14CInventoryMenu11createMenusEv+0x6d10>
  b5d717:	cmp    $0xdf,%dl
  b5d71a:	ja     b5dae0 <_ZN14CInventoryMenu11createMenusEv+0x7100>
  b5d720:	mov    $0x1f,%edi
  b5d725:	sub    $0x1,%rcx
  b5d729:	and    %edx,%edi
  b5d72b:	mov    %eax,%edx
  b5d72d:	add    $0x1,%eax
  b5d730:	movzbl 0xfd0bff(%rdx),%edx
  b5d737:	shl    $0x6,%edi
  b5d73a:	and    $0x3f,%edx
  b5d73d:	or     %edi,%edx
  b5d73f:	mov    %edx,(%rsi)
  b5d741:	mov    %eax,%edx
  b5d743:	cmp    %r12,%rdx
  b5d746:	jb     b5d700 <_ZN14CInventoryMenu11createMenusEv+0x6d20>
  b5d748:	nopl   0x0(%rax,%rax,1)
  b5d750:	cmpq   $0x20,0x7d8(%rsp)
  b5d759:	mov    %r13,0x7d0(%rsp)
  b5d761:	ja     b5eb2d <_ZN14CInventoryMenu11createMenusEv+0x814d>
  b5d767:	lea    0x7d0(%rsp),%rax
  b5d76f:	add    $0x28,%rax
  b5d773:	movl   $0x0,(%rax,%r13,4)
  b5d77b:	mov    0x8c6ede(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5d782:	lea    0x670(%rsp),%rcx
  b5d78a:	lea    0x720(%rsp),%rdx
  b5d792:	lea    0x7d0(%rsp),%rsi
  b5d79a:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5d79f:	lea    0x7d0(%rsp),%rdi
  b5d7a7:	mov    %rax,%r12
  b5d7aa:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d7af:	lea    0x720(%rsp),%rdi
  b5d7b7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d7bc:	mov    0x42b0(%rsp),%rdi
  b5d7c4:	mov    $0x1423a20,%eax
  b5d7c9:	sub    $0x18,%rdi
  b5d7cd:	cmp    %rdi,%rax
  b5d7d0:	jne    b5f745 <_ZN14CInventoryMenu11createMenusEv+0x8d65>
  b5d7d6:	mov    0x42c0(%rsp),%rdi
  b5d7de:	mov    $0x1423a20,%eax
  b5d7e3:	sub    $0x18,%rdi
  b5d7e7:	cmp    %rdi,%rax
  b5d7ea:	jne    b5f719 <_ZN14CInventoryMenu11createMenusEv+0x8d39>
  b5d7f0:	lea    0x670(%rsp),%rdi
  b5d7f8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5d7fd:	mov    0x10c0(%rbp),%rax
  b5d804:	mov    %r12,%rsi
  b5d807:	mov    0xb0(%rax),%rdi
  b5d80e:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5d813:	movb   $0x0,0x213(%r12)
  b5d81c:	xor    %esi,%esi
  b5d81e:	mov    %r12,%rdi
  b5d821:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5d826:	lea    0x38(%r12),%rdi
  b5d82b:	movb   $0x1,0x3e2(%r12)
  b5d834:	mov    $0x1,%esi
  b5d839:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5d83e:	mov    %r15,%rdi
  b5d841:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5d846:	mov    %rax,%rsi
  b5d849:	mov    %r12,%rdi
  b5d84c:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5d851:	lea    0x3f00(%rsp),%r13
  b5d859:	mov    %r15,%rsi
  b5d85c:	mov    %r13,%rdi
  b5d85f:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5d864:	mov    %r13,%rsi
  b5d867:	mov    %r12,%rdi
  b5d86a:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5d86f:	lea    0x460(%rsp),%rdi
  b5d877:	mov    %r12,0x1350(%rbp)
  b5d87e:	xor    %esi,%esi
  b5d880:	movq   $0x20,0x468(%rsp)
  b5d88c:	movq   $0x0,0x470(%rsp)
  b5d898:	movq   $0x0,0x480(%rsp)
  b5d8a4:	movq   $0x0,0x478(%rsp)
  b5d8b0:	movq   $0x0,0x508(%rsp)
  b5d8bc:	movq   $0x0,0x460(%rsp)
  b5d8c8:	movl   $0x0,0x488(%rsp)
  b5d8d3:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d8d8:	cmpq   $0x20,0x468(%rsp)
  b5d8e1:	movq   $0x0,0x460(%rsp)
  b5d8ed:	ja     b5eb20 <_ZN14CInventoryMenu11createMenusEv+0x8140>
  b5d8f3:	lea    0x460(%rsp),%rax
  b5d8fb:	add    $0x28,%rax
  b5d8ff:	lea    0x44c9(%rsp),%rdx
  b5d907:	lea    0x42a0(%rsp),%rdi
  b5d90f:	movl   $0x0,(%rax)
  b5d915:	mov    $0xfe468a,%esi
  b5d91a:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5d91f:	lea    0x42a0(%rsp),%rsi
  b5d927:	lea    0x4290(%rsp),%rdi
  b5d92f:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5d934:	mov    0x4290(%rsp),%rax
  b5d93c:	movq   $0x20,0x518(%rsp)
  b5d948:	lea    0x510(%rsp),%rdi
  b5d950:	movq   $0x0,0x520(%rsp)
  b5d95c:	movq   $0x0,0x530(%rsp)
  b5d968:	movq   $0x0,0x528(%rsp)
  b5d974:	movq   $0x0,0x5b8(%rsp)
  b5d980:	movq   $0x0,0x510(%rsp)
  b5d98c:	movl   $0x0,0x538(%rsp)
  b5d997:	mov    -0x18(%rax),%r12
  b5d99b:	mov    %r12,%rsi
  b5d99e:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5d9a3:	cmpq   $0x20,0x518(%rsp)
  b5d9ac:	mov    %r12,0x510(%rsp)
  b5d9b4:	ja     b5e998 <_ZN14CInventoryMenu11createMenusEv+0x7fb8>
  b5d9ba:	lea    0x510(%rsp),%rax
  b5d9c2:	add    $0x28,%rax
  b5d9c6:	test   %r12,%r12
  b5d9c9:	movl   $0x0,(%rax,%r12,4)
  b5d9d1:	je     b5da17 <_ZN14CInventoryMenu11createMenusEv+0x7037>
  b5d9d3:	lea    0x510(%rsp),%rcx
  b5d9db:	sub    $0x1,%r12
  b5d9df:	add    $0x28,%rcx
  b5d9e3:	jmp    b5d9ec <_ZN14CInventoryMenu11createMenusEv+0x700c>
  b5d9e5:	nopl   (%rax)
  b5d9e8:	sub    $0x1,%r12
  b5d9ec:	mov    0x4290(%rsp),%rdx
  b5d9f4:	cmpq   $0x21,0x518(%rsp)
  b5d9fd:	mov    %rcx,%rax
  b5da00:	cmovae 0x5b8(%rsp),%rax
  b5da09:	test   %r12,%r12
  b5da0c:	movzbl (%rdx,%r12,1),%edx
  b5da11:	mov    %edx,(%rax,%r12,4)
  b5da15:	jne    b5d9e8 <_ZN14CInventoryMenu11createMenusEv+0x7008>
  b5da17:	xor    %r12d,%r12d
  b5da1a:	cmpb   $0x0,0x4731de(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5da21:	movq   $0x20,0x5c8(%rsp)
  b5da2d:	movq   $0x0,0x5d0(%rsp)
  b5da39:	movq   $0x0,0x5e0(%rsp)
  b5da45:	mov    $0xfd0c00,%eax
  b5da4a:	movq   $0x0,0x5d8(%rsp)
  b5da56:	movq   $0x0,0x668(%rsp)
  b5da62:	movq   $0x0,0x5c0(%rsp)
  b5da6e:	movl   $0x0,0x5e8(%rsp)
  b5da79:	je     b5da95 <_ZN14CInventoryMenu11createMenusEv+0x70b5>
  b5da7b:	nopl   0x0(%rax,%rax,1)
  b5da80:	movzbl (%rax),%edx
  b5da83:	mov    %rax,%r12
  b5da86:	add    $0x1,%rax
  b5da8a:	sub    $0xfd0bff,%r12
  b5da91:	test   %dl,%dl
  b5da93:	jne    b5da80 <_ZN14CInventoryMenu11createMenusEv+0x70a0>
  b5da95:	cmp    0x8c6984(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5da9c:	je     b5ee50 <_ZN14CInventoryMenu11createMenusEv+0x8470>
  b5daa2:	mov    %r12,%rax
  b5daa5:	mov    $0xfd0bff,%edx
  b5daaa:	xor    %r13d,%r13d
  b5daad:	jmp    b5dab4 <_ZN14CInventoryMenu11createMenusEv+0x70d4>
  b5daaf:	nop
  b5dab0:	add    $0x1,%r13
  b5dab4:	test   %rax,%rax
  b5dab7:	je     b5dba0 <_ZN14CInventoryMenu11createMenusEv+0x71c0>
  b5dabd:	movzbl (%rdx),%ecx
  b5dac0:	sub    $0x1,%rax
  b5dac4:	add    $0x1,%rdx
  b5dac8:	test   %cl,%cl
  b5daca:	jns    b5dab0 <_ZN14CInventoryMenu11createMenusEv+0x70d0>
  b5dacc:	cmp    $0xdf,%cl
  b5dacf:	ja     b5db20 <_ZN14CInventoryMenu11createMenusEv+0x7140>
  b5dad1:	sub    $0x1,%rax
  b5dad5:	add    $0x1,%rdx
  b5dad9:	jmp    b5dab0 <_ZN14CInventoryMenu11createMenusEv+0x70d0>
  b5dadb:	nopl   0x0(%rax,%rax,1)
  b5dae0:	cmp    $0xef,%dl
  b5dae3:	ja     b5e736 <_ZN14CInventoryMenu11createMenusEv+0x7d56>
  b5dae9:	mov    %edx,%edi
  b5daeb:	lea    0x1(%rax),%edx
  b5daee:	shl    $0xc,%edi
  b5daf1:	movzbl 0xfd0bff(%rdx),%edx
  b5daf8:	and    $0xf000,%edi
  b5dafe:	and    $0x3f,%edx
  b5db01:	or     %edi,%edx
  b5db03:	mov    %eax,%edi
  b5db05:	add    $0x2,%eax
  b5db08:	movzbl 0xfd0bff(%rdi),%edi
  b5db0f:	and    $0x3f,%edi
  b5db12:	shl    $0x6,%edi
  b5db15:	or     %edi,%edx
  b5db17:	jmp    b5d6f3 <_ZN14CInventoryMenu11createMenusEv+0x6d13>
  b5db1c:	nopl   0x0(%rax)
  b5db20:	cmp    $0xef,%cl
  b5db23:	ja     b5e87b <_ZN14CInventoryMenu11createMenusEv+0x7e9b>
  b5db29:	sub    $0x2,%rax
  b5db2d:	add    $0x2,%rdx
  b5db31:	jmp    b5dab0 <_ZN14CInventoryMenu11createMenusEv+0x70d0>
  b5db36:	cs nopw 0x0(%rax,%rax,1)
  b5db40:	sub    $0x2,%rax
  b5db44:	add    $0x3,%rdx
  b5db48:	jmp    b5cb70 <_ZN14CInventoryMenu11createMenusEv+0x6190>
  b5db4d:	nopl   (%rax)
  b5db50:	mov    $0x7,%edi
  b5db55:	lea    0x2(%rax),%r8d
  b5db59:	and    %edx,%edi
  b5db5b:	mov    %eax,%edx
  b5db5d:	movzbl 0xfe4872(%rdx),%edx
  b5db64:	movzbl 0xfe4872(%r8),%r8d
  b5db6c:	shl    $0x12,%edi
  b5db6f:	and    $0x3f,%edx
  b5db72:	and    $0x3f,%r8d
  b5db76:	shl    $0xc,%edx
  b5db79:	or     %r8d,%edx
  b5db7c:	or     %edi,%edx
  b5db7e:	lea    0x1(%rax),%edi
  b5db81:	add    $0x3,%eax
  b5db84:	movzbl 0xfe4872(%rdi),%edi
  b5db8b:	and    $0x3f,%edi
  b5db8e:	shl    $0x6,%edi
  b5db91:	or     %edi,%edx
  b5db93:	jmp    b5cc03 <_ZN14CInventoryMenu11createMenusEv+0x6223>
  b5db98:	nopl   0x0(%rax,%rax,1)
  b5dba0:	lea    0x5c0(%rsp),%rdi
  b5dba8:	mov    %r13,%rsi
  b5dbab:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5dbb0:	mov    0x5c8(%rsp),%rcx
  b5dbb8:	cmp    $0x20,%rcx
  b5dbbc:	ja     b5ea12 <_ZN14CInventoryMenu11createMenusEv+0x8032>
  b5dbc2:	lea    0x5c0(%rsp),%rsi
  b5dbca:	add    $0x28,%rsi
  b5dbce:	test   %r12,%r12
  b5dbd1:	je     b5ea1f <_ZN14CInventoryMenu11createMenusEv+0x803f>
  b5dbd7:	test   %rcx,%rcx
  b5dbda:	setne  %al
  b5dbdd:	test   %al,%al
  b5dbdf:	je     b5dc50 <_ZN14CInventoryMenu11createMenusEv+0x7270>
  b5dbe1:	xor    %edx,%edx
  b5dbe3:	xor    %eax,%eax
  b5dbe5:	jmp    b5dc09 <_ZN14CInventoryMenu11createMenusEv+0x7229>
  b5dbe7:	nopw   0x0(%rax,%rax,1)
  b5dbf0:	movzbl %dl,%edx
  b5dbf3:	mov    %edx,(%rsi)
  b5dbf5:	mov    %eax,%edx
  b5dbf7:	sub    $0x1,%rcx
  b5dbfb:	cmp    %r12,%rdx
  b5dbfe:	jae    b5dc50 <_ZN14CInventoryMenu11createMenusEv+0x7270>
  b5dc00:	test   %rcx,%rcx
  b5dc03:	je     b5dc50 <_ZN14CInventoryMenu11createMenusEv+0x7270>
  b5dc05:	add    $0x4,%rsi
  b5dc09:	movzbl 0xfd0bff(%rdx),%edx
  b5dc10:	add    $0x1,%eax
  b5dc13:	test   %dl,%dl
  b5dc15:	jns    b5dbf0 <_ZN14CInventoryMenu11createMenusEv+0x7210>
  b5dc17:	cmp    $0xdf,%dl
  b5dc1a:	ja     b5dfd0 <_ZN14CInventoryMenu11createMenusEv+0x75f0>
  b5dc20:	mov    $0x1f,%edi
  b5dc25:	sub    $0x1,%rcx
  b5dc29:	and    %edx,%edi
  b5dc2b:	mov    %eax,%edx
  b5dc2d:	add    $0x1,%eax
  b5dc30:	movzbl 0xfd0bff(%rdx),%edx
  b5dc37:	shl    $0x6,%edi
  b5dc3a:	and    $0x3f,%edx
  b5dc3d:	or     %edi,%edx
  b5dc3f:	mov    %edx,(%rsi)
  b5dc41:	mov    %eax,%edx
  b5dc43:	cmp    %r12,%rdx
  b5dc46:	jb     b5dc00 <_ZN14CInventoryMenu11createMenusEv+0x7220>
  b5dc48:	nopl   0x0(%rax,%rax,1)
  b5dc50:	cmpq   $0x20,0x5c8(%rsp)
  b5dc59:	mov    %r13,0x5c0(%rsp)
  b5dc61:	ja     b5ec53 <_ZN14CInventoryMenu11createMenusEv+0x8273>
  b5dc67:	lea    0x5c0(%rsp),%rax
  b5dc6f:	add    $0x28,%rax
  b5dc73:	movl   $0x0,(%rax,%r13,4)
  b5dc7b:	mov    0x8c69de(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5dc82:	lea    0x460(%rsp),%rcx
  b5dc8a:	lea    0x510(%rsp),%rdx
  b5dc92:	lea    0x5c0(%rsp),%rsi
  b5dc9a:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5dc9f:	lea    0x5c0(%rsp),%rdi
  b5dca7:	mov    %rax,%r12
  b5dcaa:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5dcaf:	lea    0x510(%rsp),%rdi
  b5dcb7:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5dcbc:	mov    0x4290(%rsp),%rdi
  b5dcc4:	mov    $0x1423a20,%eax
  b5dcc9:	sub    $0x18,%rdi
  b5dccd:	cmp    %rdi,%rax
  b5dcd0:	jne    b5f639 <_ZN14CInventoryMenu11createMenusEv+0x8c59>
  b5dcd6:	mov    0x42a0(%rsp),%rdi
  b5dcde:	mov    $0x1423a20,%eax
  b5dce3:	sub    $0x18,%rdi
  b5dce7:	cmp    %rdi,%rax
  b5dcea:	jne    b5f8ba <_ZN14CInventoryMenu11createMenusEv+0x8eda>
  b5dcf0:	lea    0x460(%rsp),%rdi
  b5dcf8:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5dcfd:	mov    0x38(%rbx),%rdi
  b5dd01:	mov    %r12,%rsi
  b5dd04:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5dd09:	movb   $0x0,0x213(%r12)
  b5dd12:	xor    %esi,%esi
  b5dd14:	mov    %r12,%rdi
  b5dd17:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5dd1c:	lea    0x38(%r12),%rdi
  b5dd21:	movb   $0x1,0x3e2(%r12)
  b5dd2a:	mov    $0x1,%esi
  b5dd2f:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5dd34:	mov    %r15,%rdi
  b5dd37:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5dd3c:	mov    %rax,%rsi
  b5dd3f:	mov    %r12,%rdi
  b5dd42:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5dd47:	lea    0x3ef0(%rsp),%r13
  b5dd4f:	mov    %r15,%rsi
  b5dd52:	mov    %r13,%rdi
  b5dd55:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5dd5a:	mov    %r13,%rsi
  b5dd5d:	mov    %r12,%rdi
  b5dd60:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5dd65:	lea    0x250(%rsp),%rdi
  b5dd6d:	mov    %r12,0x15e0(%rbp)
  b5dd74:	xor    %esi,%esi
  b5dd76:	movq   $0x20,0x258(%rsp)
  b5dd82:	movq   $0x0,0x260(%rsp)
  b5dd8e:	movq   $0x0,0x270(%rsp)
  b5dd9a:	movq   $0x0,0x268(%rsp)
  b5dda6:	movq   $0x0,0x2f8(%rsp)
  b5ddb2:	movq   $0x0,0x250(%rsp)
  b5ddbe:	movl   $0x0,0x278(%rsp)
  b5ddc9:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ddce:	cmpq   $0x20,0x258(%rsp)
  b5ddd7:	movq   $0x0,0x250(%rsp)
  b5dde3:	ja     b5ec46 <_ZN14CInventoryMenu11createMenusEv+0x8266>
  b5dde9:	lea    0x250(%rsp),%rax
  b5ddf1:	add    $0x28,%rax
  b5ddf5:	lea    0x44c8(%rsp),%rdx
  b5ddfd:	lea    0x4280(%rsp),%rdi
  b5de05:	movl   $0x0,(%rax)
  b5de0b:	mov    $0xfe468a,%esi
  b5de10:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5de15:	lea    0x4280(%rsp),%rsi
  b5de1d:	lea    0x4270(%rsp),%rdi
  b5de25:	call   c8ea50 <_ZN7STRINGS10uniqueNameERKSs>
  b5de2a:	mov    0x4270(%rsp),%rax
  b5de32:	movq   $0x20,0x308(%rsp)
  b5de3e:	lea    0x300(%rsp),%r15
  b5de46:	movq   $0x0,0x310(%rsp)
  b5de52:	movq   $0x0,0x320(%rsp)
  b5de5e:	movq   $0x0,0x318(%rsp)
  b5de6a:	movq   $0x0,0x3a8(%rsp)
  b5de76:	mov    %r15,%rdi
  b5de79:	movq   $0x0,0x300(%rsp)
  b5de85:	movl   $0x0,0x328(%rsp)
  b5de90:	mov    -0x18(%rax),%r12
  b5de94:	mov    %r12,%rsi
  b5de97:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5de9c:	cmpq   $0x20,0x308(%rsp)
  b5dea5:	mov    %r12,0x300(%rsp)
  b5dead:	lea    0x28(%r15),%rax
  b5deb1:	jbe    b5debb <_ZN14CInventoryMenu11createMenusEv+0x74db>
  b5deb3:	mov    0x3a8(%rsp),%rax
  b5debb:	test   %r12,%r12
  b5debe:	movl   $0x0,(%rax,%r12,4)
  b5dec6:	je     b5df07 <_ZN14CInventoryMenu11createMenusEv+0x7527>
  b5dec8:	sub    $0x1,%r12
  b5decc:	lea    0x28(%r15),%rcx
  b5ded0:	jmp    b5dedc <_ZN14CInventoryMenu11createMenusEv+0x74fc>
  b5ded2:	nopw   0x0(%rax,%rax,1)
  b5ded8:	sub    $0x1,%r12
  b5dedc:	mov    0x4270(%rsp),%rdx
  b5dee4:	cmpq   $0x21,0x308(%rsp)
  b5deed:	mov    %rcx,%rax
  b5def0:	cmovae 0x3a8(%rsp),%rax
  b5def9:	test   %r12,%r12
  b5defc:	movzbl (%rdx,%r12,1),%edx
  b5df01:	mov    %edx,(%rax,%r12,4)
  b5df05:	jne    b5ded8 <_ZN14CInventoryMenu11createMenusEv+0x74f8>
  b5df07:	xor    %r12d,%r12d
  b5df0a:	cmpb   $0x0,0x472cee(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5df11:	movq   $0x20,0x3b8(%rsp)
  b5df1d:	movq   $0x0,0x3c0(%rsp)
  b5df29:	movq   $0x0,0x3d0(%rsp)
  b5df35:	mov    $0xfd0c00,%eax
  b5df3a:	movq   $0x0,0x3c8(%rsp)
  b5df46:	movq   $0x0,0x458(%rsp)
  b5df52:	movq   $0x0,0x3b0(%rsp)
  b5df5e:	movl   $0x0,0x3d8(%rsp)
  b5df69:	je     b5df85 <_ZN14CInventoryMenu11createMenusEv+0x75a5>
  b5df6b:	nopl   0x0(%rax,%rax,1)
  b5df70:	movzbl (%rax),%edx
  b5df73:	mov    %rax,%r12
  b5df76:	add    $0x1,%rax
  b5df7a:	sub    $0xfd0bff,%r12
  b5df81:	test   %dl,%dl
  b5df83:	jne    b5df70 <_ZN14CInventoryMenu11createMenusEv+0x7590>
  b5df85:	cmp    0x8c6494(%rip),%r12        # 1424420 <_ZN5CEGUI6String4nposE>
  b5df8c:	je     b5eeb1 <_ZN14CInventoryMenu11createMenusEv+0x84d1>
  b5df92:	mov    %r12,%rax
  b5df95:	mov    $0xfd0bff,%edx
  b5df9a:	xor    %r13d,%r13d
  b5df9d:	jmp    b5dfa4 <_ZN14CInventoryMenu11createMenusEv+0x75c4>
  b5df9f:	nop
  b5dfa0:	add    $0x1,%r13
  b5dfa4:	test   %rax,%rax
  b5dfa7:	je     b5e026 <_ZN14CInventoryMenu11createMenusEv+0x7646>
  b5dfa9:	movzbl (%rdx),%ecx
  b5dfac:	sub    $0x1,%rax
  b5dfb0:	add    $0x1,%rdx
  b5dfb4:	test   %cl,%cl
  b5dfb6:	jns    b5dfa0 <_ZN14CInventoryMenu11createMenusEv+0x75c0>
  b5dfb8:	cmp    $0xdf,%cl
  b5dfbb:	ja     b5e010 <_ZN14CInventoryMenu11createMenusEv+0x7630>
  b5dfbd:	sub    $0x1,%rax
  b5dfc1:	add    $0x1,%rdx
  b5dfc5:	jmp    b5dfa0 <_ZN14CInventoryMenu11createMenusEv+0x75c0>
  b5dfc7:	nopw   0x0(%rax,%rax,1)
  b5dfd0:	cmp    $0xef,%dl
  b5dfd3:	ja     b5e833 <_ZN14CInventoryMenu11createMenusEv+0x7e53>
  b5dfd9:	mov    %edx,%edi
  b5dfdb:	lea    0x1(%rax),%edx
  b5dfde:	shl    $0xc,%edi
  b5dfe1:	movzbl 0xfd0bff(%rdx),%edx
  b5dfe8:	and    $0xf000,%edi
  b5dfee:	and    $0x3f,%edx
  b5dff1:	or     %edi,%edx
  b5dff3:	mov    %eax,%edi
  b5dff5:	add    $0x2,%eax
  b5dff8:	movzbl 0xfd0bff(%rdi),%edi
  b5dfff:	and    $0x3f,%edi
  b5e002:	shl    $0x6,%edi
  b5e005:	or     %edi,%edx
  b5e007:	jmp    b5dbf3 <_ZN14CInventoryMenu11createMenusEv+0x7213>
  b5e00c:	nopl   0x0(%rax)
  b5e010:	cmp    $0xef,%cl
  b5e013:	ja     b5e8f5 <_ZN14CInventoryMenu11createMenusEv+0x7f15>
  b5e019:	sub    $0x2,%rax
  b5e01d:	add    $0x2,%rdx
  b5e021:	jmp    b5dfa0 <_ZN14CInventoryMenu11createMenusEv+0x75c0>
  b5e026:	lea    0x3b0(%rsp),%rdi
  b5e02e:	mov    %r13,%rsi
  b5e031:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5e036:	mov    0x3b8(%rsp),%rcx
  b5e03e:	cmp    $0x20,%rcx
  b5e042:	ja     b5eb79 <_ZN14CInventoryMenu11createMenusEv+0x8199>
  b5e048:	lea    0x3b0(%rsp),%rsi
  b5e050:	add    $0x28,%rsi
  b5e054:	test   %r12,%r12
  b5e057:	je     b5eb3a <_ZN14CInventoryMenu11createMenusEv+0x815a>
  b5e05d:	test   %rcx,%rcx
  b5e060:	setne  %al
  b5e063:	test   %al,%al
  b5e065:	je     b5e0d0 <_ZN14CInventoryMenu11createMenusEv+0x76f0>
  b5e067:	xor    %edx,%edx
  b5e069:	xor    %eax,%eax
  b5e06b:	jmp    b5e089 <_ZN14CInventoryMenu11createMenusEv+0x76a9>
  b5e06d:	nopl   (%rax)
  b5e070:	movzbl %dl,%edx
  b5e073:	mov    %edx,(%rsi)
  b5e075:	mov    %eax,%edx
  b5e077:	sub    $0x1,%rcx
  b5e07b:	cmp    %r12,%rdx
  b5e07e:	jae    b5e0d0 <_ZN14CInventoryMenu11createMenusEv+0x76f0>
  b5e080:	test   %rcx,%rcx
  b5e083:	je     b5e0d0 <_ZN14CInventoryMenu11createMenusEv+0x76f0>
  b5e085:	add    $0x4,%rsi
  b5e089:	movzbl 0xfd0bff(%rdx),%edx
  b5e090:	add    $0x1,%eax
  b5e093:	test   %dl,%dl
  b5e095:	jns    b5e070 <_ZN14CInventoryMenu11createMenusEv+0x7690>
  b5e097:	cmp    $0xdf,%dl
  b5e09a:	ja     b5e6e0 <_ZN14CInventoryMenu11createMenusEv+0x7d00>
  b5e0a0:	mov    $0x1f,%edi
  b5e0a5:	sub    $0x1,%rcx
  b5e0a9:	and    %edx,%edi
  b5e0ab:	mov    %eax,%edx
  b5e0ad:	add    $0x1,%eax
  b5e0b0:	movzbl 0xfd0bff(%rdx),%edx
  b5e0b7:	shl    $0x6,%edi
  b5e0ba:	and    $0x3f,%edx
  b5e0bd:	or     %edi,%edx
  b5e0bf:	mov    %edx,(%rsi)
  b5e0c1:	mov    %eax,%edx
  b5e0c3:	cmp    %r12,%rdx
  b5e0c6:	jb     b5e080 <_ZN14CInventoryMenu11createMenusEv+0x76a0>
  b5e0c8:	nopl   0x0(%rax,%rax,1)
  b5e0d0:	cmpq   $0x20,0x3b8(%rsp)
  b5e0d9:	mov    %r13,0x3b0(%rsp)
  b5e0e1:	ja     b5ed20 <_ZN14CInventoryMenu11createMenusEv+0x8340>
  b5e0e7:	lea    0x3b0(%rsp),%rax
  b5e0ef:	add    $0x28,%rax
  b5e0f3:	movl   $0x0,(%rax,%r13,4)
  b5e0fb:	mov    0x8c655e(%rip),%rdi        # 1424660 <_ZN5CEGUI9SingletonINS_13WindowManagerEE12ms_SingletonE>
  b5e102:	lea    0x250(%rsp),%rcx
  b5e10a:	lea    0x3b0(%rsp),%rsi
  b5e112:	mov    %r15,%rdx
  b5e115:	call   5530d8 <_ZN5CEGUI13WindowManager12createWindowERKNS_6StringES3_S3_@plt>
  b5e11a:	lea    0x3b0(%rsp),%rdi
  b5e122:	mov    %rax,%r12
  b5e125:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5e12a:	mov    %r15,%rdi
  b5e12d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5e132:	mov    0x4270(%rsp),%rdi
  b5e13a:	mov    $0x1423a20,%eax
  b5e13f:	sub    $0x18,%rdi
  b5e143:	cmp    %rdi,%rax
  b5e146:	jne    b5f9a3 <_ZN14CInventoryMenu11createMenusEv+0x8fc3>
  b5e14c:	mov    0x4280(%rsp),%rdi
  b5e154:	mov    $0x1423a20,%eax
  b5e159:	sub    $0x18,%rdi
  b5e15d:	cmp    %rdi,%rax
  b5e160:	jne    b5f977 <_ZN14CInventoryMenu11createMenusEv+0x8f97>
  b5e166:	lea    0x250(%rsp),%rdi
  b5e16e:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5e173:	mov    0x10c0(%rbp),%rax
  b5e17a:	mov    %r12,%rsi
  b5e17d:	mov    0xb0(%rax),%rdi
  b5e184:	call   5561f8 <_ZN5CEGUI6Window14addChildWindowEPS0_@plt>
  b5e189:	movb   $0x0,0x213(%r12)
  b5e192:	xor    %esi,%esi
  b5e194:	mov    %r12,%rdi
  b5e197:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5e19c:	lea    0x38(%r12),%rdi
  b5e1a1:	movb   $0x1,0x3e2(%r12)
  b5e1aa:	mov    $0x1,%esi
  b5e1af:	call   552a98 <_ZN5CEGUI8EventSet13setMutedStateEb@plt>
  b5e1b4:	mov    0x10c0(%rbp),%rdi
  b5e1bb:	call   555518 <_ZNK5CEGUI6Window11getPositionEv@plt>
  b5e1c0:	mov    %rax,%rsi
  b5e1c3:	mov    %r12,%rdi
  b5e1c6:	call   5548a8 <_ZN5CEGUI6Window11setPositionERKNS_8UVector2E@plt>
  b5e1cb:	lea    0x3ee0(%rsp),%r13
  b5e1d3:	mov    0x10c0(%rbp),%rsi
  b5e1da:	mov    %r13,%rdi
  b5e1dd:	call   5532a8 <_ZNK5CEGUI6Window7getSizeEv@plt>
  b5e1e2:	mov    %r13,%rsi
  b5e1e5:	mov    %r12,%rdi
  b5e1e8:	call   555178 <_ZN5CEGUI6Window7setSizeERKNS_8UVector2E@plt>
  b5e1ed:	mov    $0x1,%esi
  b5e1f2:	mov    %r12,%rdi
  b5e1f5:	call   5554d8 <_ZN5CEGUI6Window14setAlwaysOnTopEb@plt>
  b5e1fa:	mov    %r12,0x1b00(%rbp)
  b5e201:	addl   $0x1,0x10(%rsp)
  b5e206:	add    $0x8,%rbp
  b5e20a:	cmpl   $0x40,0x10(%rsp)
  b5e20f:	jne    b5c4b9 <_ZN14CInventoryMenu11createMenusEv+0x5ad9>
  b5e215:	lea    0x1a0(%rsp),%r13
  b5e21d:	xor    %r14d,%r14d
  b5e220:	lea    0x28(%r13),%r12
  b5e224:	lea    0x1(%r14),%eax
  b5e228:	lea    0x4260(%rsp),%rdi
  b5e230:	mov    %eax,%esi
  b5e232:	mov    %eax,0x18(%rsp)
  b5e236:	call   c91f60 <_ZN7STRINGS16GetValueAsStringEj>
  b5e23b:	lea    0x4260(%rsp),%rdx
  b5e243:	lea    0x4250(%rsp),%rdi
  b5e24b:	mov    $0xfef7ca,%esi
  b5e250:	call   56aee0 <_ZStplIcSt11char_traitsIcESaIcEESbIT_T0_T1_EPKS3_RKS6_>
  b5e255:	mov    0x4250(%rsp),%rax
  b5e25d:	movq   $0x20,0x1a8(%rsp)
  b5e269:	mov    %r13,%rdi
  b5e26c:	movq   $0x0,0x1b0(%rsp)
  b5e278:	movq   $0x0,0x1c0(%rsp)
  b5e284:	movq   $0x0,0x1b8(%rsp)
  b5e290:	movq   $0x0,0x248(%rsp)
  b5e29c:	movq   $0x0,0x1a0(%rsp)
  b5e2a8:	movl   $0x0,0x1c8(%rsp)
  b5e2b3:	mov    -0x18(%rax),%rbp
  b5e2b7:	mov    %rbp,%rsi
  b5e2ba:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5e2bf:	cmpq   $0x21,0x1a8(%rsp)
  b5e2c8:	mov    %r12,%rax
  b5e2cb:	mov    %rbp,0x1a0(%rsp)
  b5e2d3:	cmovae 0x248(%rsp),%rax
  b5e2dc:	test   %rbp,%rbp
  b5e2df:	movl   $0x0,(%rax,%rbp,4)
  b5e2e6:	je     b5e31d <_ZN14CInventoryMenu11createMenusEv+0x793d>
  b5e2e8:	nopl   0x0(%rax,%rax,1)
  b5e2f0:	mov    0x4250(%rsp),%rdx
  b5e2f8:	sub    $0x1,%rbp
  b5e2fc:	cmpq   $0x21,0x1a8(%rsp)
  b5e305:	mov    %r12,%rax
  b5e308:	cmovae 0x248(%rsp),%rax
  b5e311:	test   %rbp,%rbp
  b5e314:	movzbl (%rdx,%rbp,1),%edx
  b5e318:	mov    %edx,(%rax,%rbp,4)
  b5e31b:	jne    b5e2f0 <_ZN14CInventoryMenu11createMenusEv+0x7910>
  b5e31d:	mov    0x28(%rbx),%rdi
  b5e321:	mov    %r13,%rsi
  b5e324:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5e329:	mov    %r13,%rdi
  b5e32c:	mov    %rax,%rbp
  b5e32f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5e334:	mov    0x4250(%rsp),%rdi
  b5e33c:	mov    $0x1423a20,%eax
  b5e341:	sub    $0x18,%rdi
  b5e345:	cmp    %rdi,%rax
  b5e348:	jne    b5f582 <_ZN14CInventoryMenu11createMenusEv+0x8ba2>
  b5e34e:	mov    0x4260(%rsp),%rdi
  b5e356:	mov    $0x1423a20,%eax
  b5e35b:	sub    $0x18,%rdi
  b5e35f:	cmp    %rdi,%rax
  b5e362:	jne    b5f556 <_ZN14CInventoryMenu11createMenusEv+0x8b76>
  b5e368:	movb   $0x0,0x213(%rbp)
  b5e36f:	xor    %esi,%esi
  b5e371:	mov    %rbp,%rdi
  b5e374:	call   555ef8 <_ZN5CEGUI6Window24setWantsMultiClickEventsEb@plt>
  b5e379:	mov    0x38(%rbp),%rax
  b5e37d:	mov    $0x20,%edi
  b5e382:	mov    0x10(%rax),%rax
  b5e386:	mov    %rax,0x10(%rsp)
  b5e38b:	call   552d68 <_Znwm@plt>
  b5e390:	lea    0x38(%rbp),%r15
  b5e394:	movq   $0xfefcd0,(%rax)
  b5e39b:	movq   $0x0,0x10(%rax)
  b5e3a3:	movq   $0xb45900,0x8(%rax)
  b5e3ab:	mov    %rbx,0x18(%rax)
  b5e3af:	lea    0x4240(%rsp),%rcx
  b5e3b7:	mov    %rax,0x4240(%rsp)
  b5e3bf:	mov    $0x1423b80,%edx
  b5e3c4:	mov    %r15,%rsi
  b5e3c7:	lea    0x3ed0(%rsp),%rdi
  b5e3cf:	call   *0x10(%rsp)
  b5e3d3:	cmpq   $0x0,0x3ed0(%rsp)
  b5e3dc:	je     b5e43a <_ZN14CInventoryMenu11createMenusEv+0x7a5a>
  b5e3de:	mov    0x3ed8(%rsp),%rax
  b5e3e6:	mov    (%rax),%edx
  b5e3e8:	sub    $0x1,%edx
  b5e3eb:	test   %edx,%edx
  b5e3ed:	mov    %edx,(%rax)
  b5e3ef:	jne    b5e43a <_ZN14CInventoryMenu11createMenusEv+0x7a5a>
  b5e3f1:	mov    0x3ed0(%rsp),%rax
  b5e3f9:	test   %rax,%rax
  b5e3fc:	mov    %rax,0x10(%rsp)
  b5e401:	je     b5e415 <_ZN14CInventoryMenu11createMenusEv+0x7a35>
  b5e403:	mov    %rax,%rdi
  b5e406:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5e40b:	mov    0x10(%rsp),%rdi
  b5e410:	call   553f18 <_ZdlPv@plt>
  b5e415:	mov    0x3ed8(%rsp),%rdi
  b5e41d:	call   553f18 <_ZdlPv@plt>
  b5e422:	movq   $0x0,0x3ed0(%rsp)
  b5e42e:	movq   $0x0,0x3ed8(%rsp)
  b5e43a:	lea    0x4240(%rsp),%rdi
  b5e442:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5e447:	mov    0x38(%rbp),%rax
  b5e44b:	mov    $0x20,%edi
  b5e450:	mov    0x10(%rax),%rax
  b5e454:	mov    %rax,0x10(%rsp)
  b5e459:	call   552d68 <_Znwm@plt>
  b5e45e:	movq   $0xfefcd0,(%rax)
  b5e465:	movq   $0x0,0x10(%rax)
  b5e46d:	lea    0x4230(%rsp),%rcx
  b5e475:	movq   $0xb45900,0x8(%rax)
  b5e47d:	mov    %rbx,0x18(%rax)
  b5e481:	mov    $0x1424020,%edx
  b5e486:	mov    %rax,0x4230(%rsp)
  b5e48e:	mov    %r15,%rsi
  b5e491:	lea    0x3ec0(%rsp),%rdi
  b5e499:	call   *0x10(%rsp)
  b5e49d:	cmpq   $0x0,0x3ec0(%rsp)
  b5e4a6:	je     b5e504 <_ZN14CInventoryMenu11createMenusEv+0x7b24>
  b5e4a8:	mov    0x3ec8(%rsp),%rax
  b5e4b0:	mov    (%rax),%edx
  b5e4b2:	sub    $0x1,%edx
  b5e4b5:	test   %edx,%edx
  b5e4b7:	mov    %edx,(%rax)
  b5e4b9:	jne    b5e504 <_ZN14CInventoryMenu11createMenusEv+0x7b24>
  b5e4bb:	mov    0x3ec0(%rsp),%rax
  b5e4c3:	test   %rax,%rax
  b5e4c6:	mov    %rax,0x10(%rsp)
  b5e4cb:	je     b5e4df <_ZN14CInventoryMenu11createMenusEv+0x7aff>
  b5e4cd:	mov    %rax,%rdi
  b5e4d0:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5e4d5:	mov    0x10(%rsp),%rdi
  b5e4da:	call   553f18 <_ZdlPv@plt>
  b5e4df:	mov    0x3ec8(%rsp),%rdi
  b5e4e7:	call   553f18 <_ZdlPv@plt>
  b5e4ec:	movq   $0x0,0x3ec0(%rsp)
  b5e4f8:	movq   $0x0,0x3ec8(%rsp)
  b5e504:	lea    0x4230(%rsp),%rdi
  b5e50c:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5e511:	mov    0x38(%rbp),%rax
  b5e515:	mov    $0x20,%edi
  b5e51a:	mov    0x10(%rax),%rax
  b5e51e:	mov    %rax,0x10(%rsp)
  b5e523:	call   552d68 <_Znwm@plt>
  b5e528:	movq   $0xfefcd0,(%rax)
  b5e52f:	movq   $0x0,0x10(%rax)
  b5e537:	lea    0x3eb0(%rsp),%rdi
  b5e53f:	movq   $0xb45930,0x8(%rax)
  b5e547:	mov    %rbx,0x18(%rax)
  b5e54b:	lea    0x4220(%rsp),%rcx
  b5e553:	mov    %rax,0x4220(%rsp)
  b5e55b:	mov    $0x1423700,%edx
  b5e560:	mov    %r15,%rsi
  b5e563:	call   *0x10(%rsp)
  b5e567:	cmpq   $0x0,0x3eb0(%rsp)
  b5e570:	je     b5e5ce <_ZN14CInventoryMenu11createMenusEv+0x7bee>
  b5e572:	mov    0x3eb8(%rsp),%rax
  b5e57a:	mov    (%rax),%edx
  b5e57c:	sub    $0x1,%edx
  b5e57f:	test   %edx,%edx
  b5e581:	mov    %edx,(%rax)
  b5e583:	jne    b5e5ce <_ZN14CInventoryMenu11createMenusEv+0x7bee>
  b5e585:	mov    0x3eb0(%rsp),%rax
  b5e58d:	test   %rax,%rax
  b5e590:	mov    %rax,0x10(%rsp)
  b5e595:	je     b5e5a9 <_ZN14CInventoryMenu11createMenusEv+0x7bc9>
  b5e597:	mov    %rax,%rdi
  b5e59a:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5e59f:	mov    0x10(%rsp),%rdi
  b5e5a4:	call   553f18 <_ZdlPv@plt>
  b5e5a9:	mov    0x3eb8(%rsp),%rdi
  b5e5b1:	call   553f18 <_ZdlPv@plt>
  b5e5b6:	movq   $0x0,0x3eb0(%rsp)
  b5e5c2:	movq   $0x0,0x3eb8(%rsp)
  b5e5ce:	lea    0x4220(%rsp),%rdi
  b5e5d6:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5e5db:	mov    0x38(%rbp),%rax
  b5e5df:	mov    $0x20,%edi
  b5e5e4:	mov    0x10(%rax),%rax
  b5e5e8:	mov    %rax,0x10(%rsp)
  b5e5ed:	call   552d68 <_Znwm@plt>
  b5e5f2:	movq   $0xfefcd0,(%rax)
  b5e5f9:	movq   $0x0,0x10(%rax)
  b5e601:	lea    0x3ea0(%rsp),%rdi
  b5e609:	movq   $0xb45940,0x8(%rax)
  b5e611:	mov    %rbx,0x18(%rax)
  b5e615:	lea    0x4210(%rsp),%rcx
  b5e61d:	mov    %rax,0x4210(%rsp)
  b5e625:	mov    $0x14247e0,%edx
  b5e62a:	mov    %r15,%rsi
  b5e62d:	call   *0x10(%rsp)
  b5e631:	cmpq   $0x0,0x3ea0(%rsp)
  b5e63a:	je     b5e691 <_ZN14CInventoryMenu11createMenusEv+0x7cb1>
  b5e63c:	mov    0x3ea8(%rsp),%rax
  b5e644:	mov    (%rax),%edx
  b5e646:	sub    $0x1,%edx
  b5e649:	test   %edx,%edx
  b5e64b:	mov    %edx,(%rax)
  b5e64d:	jne    b5e691 <_ZN14CInventoryMenu11createMenusEv+0x7cb1>
  b5e64f:	mov    0x3ea0(%rsp),%r15
  b5e657:	test   %r15,%r15
  b5e65a:	je     b5e66c <_ZN14CInventoryMenu11createMenusEv+0x7c8c>
  b5e65c:	mov    %r15,%rdi
  b5e65f:	call   556578 <_ZN5CEGUI9BoundSlotD1Ev@plt>
  b5e664:	mov    %r15,%rdi
  b5e667:	call   553f18 <_ZdlPv@plt>
  b5e66c:	mov    0x3ea8(%rsp),%rdi
  b5e674:	call   553f18 <_ZdlPv@plt>
  b5e679:	movq   $0x0,0x3ea0(%rsp)
  b5e685:	movq   $0x0,0x3ea8(%rsp)
  b5e691:	lea    0x4210(%rsp),%rdi
  b5e699:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5e69e:	mov    %r14d,%esi
  b5e6a1:	mov    %rbp,%rdi
  b5e6a4:	call   554ce8 <_ZN5CEGUI6Window5setIDEj@plt>
  b5e6a9:	mov    0x38(%rsp),%rax
  b5e6ae:	mov    %r14d,%esi
  b5e6b1:	mov    %rbp,%rdi
  b5e6b4:	mov    %rbp,0x8dc8(%rax)
  b5e6bb:	call   554ce8 <_ZN5CEGUI6Window5setIDEj@plt>
  b5e6c0:	addq   $0x8,0x38(%rsp)
  b5e6c6:	cmpl   $0x4,0x18(%rsp)
  b5e6cb:	je     b5ef12 <_ZN14CInventoryMenu11createMenusEv+0x8532>
  b5e6d1:	mov    0x18(%rsp),%r14d
  b5e6d6:	jmp    b5e224 <_ZN14CInventoryMenu11createMenusEv+0x7844>
  b5e6db:	nopl   0x0(%rax,%rax,1)
  b5e6e0:	cmp    $0xef,%dl
  b5e6e3:	ja     b5e902 <_ZN14CInventoryMenu11createMenusEv+0x7f22>
  b5e6e9:	mov    %edx,%edi
  b5e6eb:	lea    0x1(%rax),%edx
  b5e6ee:	shl    $0xc,%edi
  b5e6f1:	movzbl 0xfd0bff(%rdx),%edx
  b5e6f8:	and    $0xf000,%edi
  b5e6fe:	and    $0x3f,%edx
  b5e701:	or     %edi,%edx
  b5e703:	mov    %eax,%edi
  b5e705:	add    $0x2,%eax
  b5e708:	movzbl 0xfd0bff(%rdi),%edi
  b5e70f:	and    $0x3f,%edi
  b5e712:	shl    $0x6,%edi
  b5e715:	or     %edi,%edx
  b5e717:	jmp    b5e073 <_ZN14CInventoryMenu11createMenusEv+0x7693>
  b5e71c:	mov    0x1f28(%rsp),%rax
  b5e724:	jmp    b5aee3 <_ZN14CInventoryMenu11createMenusEv+0x4503>
  b5e729:	sub    $0x2,%rax
  b5e72d:	add    $0x3,%rdx
  b5e731:	jmp    b5d610 <_ZN14CInventoryMenu11createMenusEv+0x6c30>
  b5e736:	mov    $0x7,%edi
  b5e73b:	lea    0x2(%rax),%r8d
  b5e73f:	and    %edx,%edi
  b5e741:	mov    %eax,%edx
  b5e743:	movzbl 0xfd0bff(%rdx),%edx
  b5e74a:	movzbl 0xfd0bff(%r8),%r8d
  b5e752:	shl    $0x12,%edi
  b5e755:	and    $0x3f,%edx
  b5e758:	and    $0x3f,%r8d
  b5e75c:	shl    $0xc,%edx
  b5e75f:	or     %r8d,%edx
  b5e762:	or     %edi,%edx
  b5e764:	lea    0x1(%rax),%edi
  b5e767:	add    $0x3,%eax
  b5e76a:	movzbl 0xfd0bff(%rdi),%edi
  b5e771:	and    $0x3f,%edi
  b5e774:	shl    $0x6,%edi
  b5e777:	or     %edi,%edx
  b5e779:	jmp    b5d6f3 <_ZN14CInventoryMenu11createMenusEv+0x6d13>
  b5e77e:	cmpb   $0x0,0x4860ed(%rip)        # fe4872 <_ZTI17CSpawnClassParser+0x572>
  b5e785:	je     b5cc60 <_ZN14CInventoryMenu11createMenusEv+0x6280>
  b5e78b:	nopl   0x0(%rax,%rax,1)
  b5e790:	movzbl (%r14),%eax
  b5e794:	mov    %r14,%r12
  b5e797:	add    $0x1,%r14
  b5e79b:	sub    $0xfe4872,%r12
  b5e7a2:	test   %al,%al
  b5e7a4:	jne    b5e790 <_ZN14CInventoryMenu11createMenusEv+0x7db0>
  b5e7a6:	test   %r12,%r12
  b5e7a9:	setne  %al
  b5e7ac:	test   %rcx,%rcx
  b5e7af:	setne  %dl
  b5e7b2:	and    %edx,%eax
  b5e7b4:	jmp    b5cbf5 <_ZN14CInventoryMenu11createMenusEv+0x6215>
  b5e7b9:	mov    0x1008(%rsp),%rsi
  b5e7c1:	jmp    b5cbe6 <_ZN14CInventoryMenu11createMenusEv+0x6206>
  b5e7c6:	lea    0x41e0(%rsp),%rbp
  b5e7ce:	lea    0x44c5(%rsp),%rdx
  b5e7d6:	mov    $0xfaa820,%esi
  b5e7db:	mov    %rbp,%rdi
  b5e7de:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5e7e3:	mov    $0x10,%edi
  b5e7e8:	call   553738 <__cxa_allocate_exception@plt>
  b5e7ed:	mov    %rbp,%rsi
  b5e7f0:	mov    %rax,%rdi
  b5e7f3:	mov    %rax,%r12
  b5e7f6:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5e7fb:	mov    0x41e0(%rsp),%rdi
  b5e803:	sub    $0x18,%rdi
  b5e807:	cmp    $0x1423a20,%rdi
  b5e80e:	jne    b6071b <_ZN14CInventoryMenu11createMenusEv+0x9d3b>
  b5e814:	mov    $0x5a6ce0,%edx
  b5e819:	mov    $0xfaaa70,%esi
  b5e81e:	mov    %r12,%rdi
  b5e821:	call   5542b8 <__cxa_throw@plt>
  b5e826:	mov    0xea8(%rsp),%rax
  b5e82e:	jmp    b5c9c7 <_ZN14CInventoryMenu11createMenusEv+0x5fe7>
  b5e833:	mov    $0x7,%edi
  b5e838:	lea    0x2(%rax),%r8d
  b5e83c:	and    %edx,%edi
  b5e83e:	mov    %eax,%edx
  b5e840:	movzbl 0xfd0bff(%rdx),%edx
  b5e847:	movzbl 0xfd0bff(%r8),%r8d
  b5e84f:	shl    $0x12,%edi
  b5e852:	and    $0x3f,%edx
  b5e855:	and    $0x3f,%r8d
  b5e859:	shl    $0xc,%edx
  b5e85c:	or     %r8d,%edx
  b5e85f:	or     %edi,%edx
  b5e861:	lea    0x1(%rax),%edi
  b5e864:	add    $0x3,%eax
  b5e867:	movzbl 0xfd0bff(%rdi),%edi
  b5e86e:	and    $0x3f,%edi
  b5e871:	shl    $0x6,%edi
  b5e874:	or     %edi,%edx
  b5e876:	jmp    b5dbf3 <_ZN14CInventoryMenu11createMenusEv+0x7213>
  b5e87b:	sub    $0x2,%rax
  b5e87f:	add    $0x3,%rdx
  b5e883:	jmp    b5dab0 <_ZN14CInventoryMenu11createMenusEv+0x70d0>
  b5e888:	lea    0x41d0(%rsp),%rbp
  b5e890:	lea    0x44c3(%rsp),%rdx
  b5e898:	mov    $0xfaa820,%esi
  b5e89d:	mov    %rbp,%rdi
  b5e8a0:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5e8a5:	mov    $0x10,%edi
  b5e8aa:	call   553738 <__cxa_allocate_exception@plt>
  b5e8af:	mov    %rbp,%rsi
  b5e8b2:	mov    %rax,%rdi
  b5e8b5:	mov    %rax,%r12
  b5e8b8:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5e8bd:	mov    0x41d0(%rsp),%rdi
  b5e8c5:	sub    $0x18,%rdi
  b5e8c9:	cmp    $0x1423a20,%rdi
  b5e8d0:	jne    b60677 <_ZN14CInventoryMenu11createMenusEv+0x9c97>
  b5e8d6:	mov    $0x5a6ce0,%edx
  b5e8db:	mov    $0xfaaa70,%esi
  b5e8e0:	mov    %r12,%rdi
  b5e8e3:	call   5542b8 <__cxa_throw@plt>
  b5e8e8:	mov    0x1008(%rsp),%rax
  b5e8f0:	jmp    b5cc83 <_ZN14CInventoryMenu11createMenusEv+0x62a3>
  b5e8f5:	sub    $0x2,%rax
  b5e8f9:	add    $0x3,%rdx
  b5e8fd:	jmp    b5dfa0 <_ZN14CInventoryMenu11createMenusEv+0x75c0>
  b5e902:	mov    $0x7,%edi
  b5e907:	lea    0x2(%rax),%r8d
  b5e90b:	and    %edx,%edi
  b5e90d:	mov    %eax,%edx
  b5e90f:	movzbl 0xfd0bff(%rdx),%edx
  b5e916:	movzbl 0xfd0bff(%r8),%r8d
  b5e91e:	shl    $0x12,%edi
  b5e921:	and    $0x3f,%edx
  b5e924:	and    $0x3f,%r8d
  b5e928:	shl    $0xc,%edx
  b5e92b:	or     %r8d,%edx
  b5e92e:	or     %edi,%edx
  b5e930:	lea    0x1(%rax),%edi
  b5e933:	add    $0x3,%eax
  b5e936:	movzbl 0xfd0bff(%rdi),%edi
  b5e93d:	and    $0x3f,%edi
  b5e940:	shl    $0x6,%edi
  b5e943:	or     %edi,%edx
  b5e945:	jmp    b5e073 <_ZN14CInventoryMenu11createMenusEv+0x7693>
  b5e94a:	test   %r12,%r12
  b5e94d:	mov    0x878(%rsp),%rsi
  b5e955:	jne    b5d6d7 <_ZN14CInventoryMenu11createMenusEv+0x6cf7>
  b5e95b:	cmpb   $0x0,0x47229d(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5e962:	mov    $0xfd0c00,%eax
  b5e967:	je     b5d750 <_ZN14CInventoryMenu11createMenusEv+0x6d70>
  b5e96d:	nopl   (%rax)
  b5e970:	movzbl (%rax),%edx
  b5e973:	mov    %rax,%r12
  b5e976:	add    $0x1,%rax
  b5e97a:	sub    $0xfd0bff,%r12
  b5e981:	test   %dl,%dl
  b5e983:	jne    b5e970 <_ZN14CInventoryMenu11createMenusEv+0x7f90>
  b5e985:	test   %r12,%r12
  b5e988:	setne  %al
  b5e98b:	test   %rcx,%rcx
  b5e98e:	setne  %dl
  b5e991:	and    %edx,%eax
  b5e993:	jmp    b5d6dd <_ZN14CInventoryMenu11createMenusEv+0x6cfd>
  b5e998:	mov    0x5b8(%rsp),%rax
  b5e9a0:	jmp    b5d9c6 <_ZN14CInventoryMenu11createMenusEv+0x6fe6>
  b5e9a5:	lea    0x41c0(%rsp),%rbp
  b5e9ad:	lea    0x44c1(%rsp),%rdx
  b5e9b5:	mov    $0xfaa820,%esi
  b5e9ba:	mov    %rbp,%rdi
  b5e9bd:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5e9c2:	mov    $0x10,%edi
  b5e9c7:	call   553738 <__cxa_allocate_exception@plt>
  b5e9cc:	mov    %rbp,%rsi
  b5e9cf:	mov    %rax,%rdi
  b5e9d2:	mov    %rax,%r12
  b5e9d5:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5e9da:	mov    0x41c0(%rsp),%rdi
  b5e9e2:	sub    $0x18,%rdi
  b5e9e6:	cmp    $0x1423a20,%rdi
  b5e9ed:	jne    b6062a <_ZN14CInventoryMenu11createMenusEv+0x9c4a>
  b5e9f3:	mov    $0x5a6ce0,%edx
  b5e9f8:	mov    $0xfaaa70,%esi
  b5e9fd:	mov    %r12,%rdi
  b5ea00:	call   5542b8 <__cxa_throw@plt>
  b5ea05:	mov    0x718(%rsp),%rax
  b5ea0d:	jmp    b5d45f <_ZN14CInventoryMenu11createMenusEv+0x6a7f>
  b5ea12:	mov    0x668(%rsp),%rsi
  b5ea1a:	jmp    b5dbce <_ZN14CInventoryMenu11createMenusEv+0x71ee>
  b5ea1f:	cmpb   $0x0,0x4721d9(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5ea26:	mov    $0xfd0c00,%eax
  b5ea2b:	je     b5dc50 <_ZN14CInventoryMenu11createMenusEv+0x7270>
  b5ea31:	nopl   0x0(%rax)
  b5ea38:	movzbl (%rax),%edx
  b5ea3b:	mov    %rax,%r12
  b5ea3e:	add    $0x1,%rax
  b5ea42:	sub    $0xfd0bff,%r12
  b5ea49:	test   %dl,%dl
  b5ea4b:	jne    b5ea38 <_ZN14CInventoryMenu11createMenusEv+0x8058>
  b5ea4d:	test   %r12,%r12
  b5ea50:	setne  %al
  b5ea53:	test   %rcx,%rcx
  b5ea56:	setne  %dl
  b5ea59:	and    %edx,%eax
  b5ea5b:	jmp    b5dbdd <_ZN14CInventoryMenu11createMenusEv+0x71fd>
  b5ea60:	lea    0x4180(%rsp),%rbp
  b5ea68:	lea    0x44b8(%rsp),%rdx
  b5ea70:	mov    $0xfaa820,%esi
  b5ea75:	mov    %rbp,%rdi
  b5ea78:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ea7d:	mov    $0x10,%edi
  b5ea82:	call   553738 <__cxa_allocate_exception@plt>
  b5ea87:	mov    %rbp,%rsi
  b5ea8a:	mov    %rax,%rdi
  b5ea8d:	mov    %rax,%r12
  b5ea90:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ea95:	mov    0x4180(%rsp),%rdi
  b5ea9d:	sub    $0x18,%rdi
  b5eaa1:	cmp    $0x1423a20,%rdi
  b5eaa8:	jne    b605c4 <_ZN14CInventoryMenu11createMenusEv+0x9be4>
  b5eaae:	mov    $0x5a6ce0,%edx
  b5eab3:	mov    $0xfaaa70,%esi
  b5eab8:	mov    %r12,%rdi
  b5eabb:	call   5542b8 <__cxa_throw@plt>
  b5eac0:	lea    0x41b0(%rsp),%rbp
  b5eac8:	lea    0x44be(%rsp),%rdx
  b5ead0:	mov    $0xfaa820,%esi
  b5ead5:	mov    %rbp,%rdi
  b5ead8:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5eadd:	mov    $0x10,%edi
  b5eae2:	call   553738 <__cxa_allocate_exception@plt>
  b5eae7:	mov    %rbp,%rsi
  b5eaea:	mov    %rax,%rdi
  b5eaed:	mov    %rax,%r12
  b5eaf0:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5eaf5:	mov    0x41b0(%rsp),%rdi
  b5eafd:	sub    $0x18,%rdi
  b5eb01:	cmp    $0x1423a20,%rdi
  b5eb08:	jne    b6055d <_ZN14CInventoryMenu11createMenusEv+0x9b7d>
  b5eb0e:	mov    $0x5a6ce0,%edx
  b5eb13:	mov    $0xfaaa70,%esi
  b5eb18:	mov    %r12,%rdi
  b5eb1b:	call   5542b8 <__cxa_throw@plt>
  b5eb20:	mov    0x508(%rsp),%rax
  b5eb28:	jmp    b5d8ff <_ZN14CInventoryMenu11createMenusEv+0x6f1f>
  b5eb2d:	mov    0x878(%rsp),%rax
  b5eb35:	jmp    b5d773 <_ZN14CInventoryMenu11createMenusEv+0x6d93>
  b5eb3a:	cmpb   $0x0,0x4720be(%rip)        # fd0bff <_ZTSN4Ogre28HardwareIndexBufferSharedPtrE+0x19df>
  b5eb41:	je     b5e0d0 <_ZN14CInventoryMenu11createMenusEv+0x76f0>
  b5eb47:	nopw   0x0(%rax,%rax,1)
  b5eb50:	movzbl (%r14),%eax
  b5eb54:	mov    %r14,%r12
  b5eb57:	add    $0x1,%r14
  b5eb5b:	sub    $0xfd0bff,%r12
  b5eb62:	test   %al,%al
  b5eb64:	jne    b5eb50 <_ZN14CInventoryMenu11createMenusEv+0x8170>
  b5eb66:	test   %r12,%r12
  b5eb69:	setne  %al
  b5eb6c:	test   %rcx,%rcx
  b5eb6f:	setne  %dl
  b5eb72:	and    %edx,%eax
  b5eb74:	jmp    b5e063 <_ZN14CInventoryMenu11createMenusEv+0x7683>
  b5eb79:	mov    0x458(%rsp),%rsi
  b5eb81:	jmp    b5e054 <_ZN14CInventoryMenu11createMenusEv+0x7674>
  b5eb86:	lea    0x4170(%rsp),%rbp
  b5eb8e:	lea    0x44b4(%rsp),%rdx
  b5eb96:	mov    $0xfaa820,%esi
  b5eb9b:	mov    %rbp,%rdi
  b5eb9e:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5eba3:	mov    $0x10,%edi
  b5eba8:	call   553738 <__cxa_allocate_exception@plt>
  b5ebad:	mov    %rbp,%rsi
  b5ebb0:	mov    %rax,%rdi
  b5ebb3:	mov    %rax,%r12
  b5ebb6:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ebbb:	mov    0x4170(%rsp),%rdi
  b5ebc3:	sub    $0x18,%rdi
  b5ebc7:	cmp    $0x1423a20,%rdi
  b5ebce:	jne    b604d2 <_ZN14CInventoryMenu11createMenusEv+0x9af2>
  b5ebd4:	mov    $0x5a6ce0,%edx
  b5ebd9:	mov    $0xfaaa70,%esi
  b5ebde:	mov    %r12,%rdi
  b5ebe1:	call   5542b8 <__cxa_throw@plt>
  b5ebe6:	lea    0x41a0(%rsp),%rbp
  b5ebee:	lea    0x44bc(%rsp),%rdx
  b5ebf6:	mov    $0xfaa820,%esi
  b5ebfb:	mov    %rbp,%rdi
  b5ebfe:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ec03:	mov    $0x10,%edi
  b5ec08:	call   553738 <__cxa_allocate_exception@plt>
  b5ec0d:	mov    %rbp,%rsi
  b5ec10:	mov    %rax,%rdi
  b5ec13:	mov    %rax,%r12
  b5ec16:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ec1b:	mov    0x41a0(%rsp),%rdi
  b5ec23:	sub    $0x18,%rdi
  b5ec27:	cmp    $0x1423a20,%rdi
  b5ec2e:	jne    b6048a <_ZN14CInventoryMenu11createMenusEv+0x9aaa>
  b5ec34:	mov    $0x5a6ce0,%edx
  b5ec39:	mov    $0xfaaa70,%esi
  b5ec3e:	mov    %r12,%rdi
  b5ec41:	call   5542b8 <__cxa_throw@plt>
  b5ec46:	mov    0x2f8(%rsp),%rax
  b5ec4e:	jmp    b5ddf5 <_ZN14CInventoryMenu11createMenusEv+0x7415>
  b5ec53:	mov    0x668(%rsp),%rax
  b5ec5b:	jmp    b5dc73 <_ZN14CInventoryMenu11createMenusEv+0x7293>
  b5ec60:	lea    0x4160(%rsp),%rbp
  b5ec68:	lea    0x44b0(%rsp),%rdx
  b5ec70:	mov    $0xfaa820,%esi
  b5ec75:	mov    %rbp,%rdi
  b5ec78:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ec7d:	mov    $0x10,%edi
  b5ec82:	call   553738 <__cxa_allocate_exception@plt>
  b5ec87:	mov    %rbp,%rsi
  b5ec8a:	mov    %rax,%rdi
  b5ec8d:	mov    %rax,%r12
  b5ec90:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ec95:	mov    0x4160(%rsp),%rdi
  b5ec9d:	sub    $0x18,%rdi
  b5eca1:	cmp    $0x1423a20,%rdi
  b5eca8:	jne    b60424 <_ZN14CInventoryMenu11createMenusEv+0x9a44>
  b5ecae:	mov    $0x5a6ce0,%edx
  b5ecb3:	mov    $0xfaaa70,%esi
  b5ecb8:	mov    %r12,%rdi
  b5ecbb:	call   5542b8 <__cxa_throw@plt>
  b5ecc0:	lea    0x4190(%rsp),%rbp
  b5ecc8:	lea    0x44ba(%rsp),%rdx
  b5ecd0:	mov    $0xfaa820,%esi
  b5ecd5:	mov    %rbp,%rdi
  b5ecd8:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ecdd:	mov    $0x10,%edi
  b5ece2:	call   553738 <__cxa_allocate_exception@plt>
  b5ece7:	mov    %rbp,%rsi
  b5ecea:	mov    %rax,%rdi
  b5eced:	mov    %rax,%r12
  b5ecf0:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ecf5:	mov    0x4190(%rsp),%rdi
  b5ecfd:	sub    $0x18,%rdi
  b5ed01:	cmp    $0x1423a20,%rdi
  b5ed08:	jne    b603b8 <_ZN14CInventoryMenu11createMenusEv+0x99d8>
  b5ed0e:	mov    $0x5a6ce0,%edx
  b5ed13:	mov    $0xfaaa70,%esi
  b5ed18:	mov    %r12,%rdi
  b5ed1b:	call   5542b8 <__cxa_throw@plt>
  b5ed20:	mov    0x458(%rsp),%rax
  b5ed28:	jmp    b5e0f3 <_ZN14CInventoryMenu11createMenusEv+0x7713>
  b5ed2d:	lea    0x4150(%rsp),%rbp
  b5ed35:	lea    0x44aa(%rsp),%rdx
  b5ed3d:	mov    $0xfaa820,%esi
  b5ed42:	mov    %rbp,%rdi
  b5ed45:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ed4a:	mov    $0x10,%edi
  b5ed4f:	call   553738 <__cxa_allocate_exception@plt>
  b5ed54:	mov    %rbp,%rsi
  b5ed57:	mov    %rax,%rdi
  b5ed5a:	mov    %rax,%r12
  b5ed5d:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ed62:	mov    0x4150(%rsp),%rdi
  b5ed6a:	mov    $0x1423a20,%eax
  b5ed6f:	sub    $0x18,%rdi
  b5ed73:	cmp    %rdi,%rax
  b5ed76:	jne    b5f7cb <_ZN14CInventoryMenu11createMenusEv+0x8deb>
  b5ed7c:	mov    $0x5a6ce0,%edx
  b5ed81:	mov    $0xfaaa70,%esi
  b5ed86:	mov    %r12,%rdi
  b5ed89:	call   5542b8 <__cxa_throw@plt>
  b5ed8e:	lea    0x4140(%rsp),%rbp
  b5ed96:	lea    0x44a6(%rsp),%rdx
  b5ed9e:	mov    $0xfaa820,%esi
  b5eda3:	mov    %rbp,%rdi
  b5eda6:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5edab:	mov    $0x10,%edi
  b5edb0:	call   553738 <__cxa_allocate_exception@plt>
  b5edb5:	mov    %rbp,%rsi
  b5edb8:	mov    %rax,%rdi
  b5edbb:	mov    %rax,%r12
  b5edbe:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5edc3:	mov    0x4140(%rsp),%rdi
  b5edcb:	mov    $0x1423a20,%eax
  b5edd0:	sub    $0x18,%rdi
  b5edd4:	cmp    %rdi,%rax
  b5edd7:	jne    b5f83c <_ZN14CInventoryMenu11createMenusEv+0x8e5c>
  b5eddd:	mov    $0x5a6ce0,%edx
  b5ede2:	mov    $0xfaaa70,%esi
  b5ede7:	mov    %r12,%rdi
  b5edea:	call   5542b8 <__cxa_throw@plt>
  b5edef:	lea    0x4130(%rsp),%rbp
  b5edf7:	lea    0x44a4(%rsp),%rdx
  b5edff:	mov    $0xfaa820,%esi
  b5ee04:	mov    %rbp,%rdi
  b5ee07:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ee0c:	mov    $0x10,%edi
  b5ee11:	call   553738 <__cxa_allocate_exception@plt>
  b5ee16:	mov    %rbp,%rsi
  b5ee19:	mov    %rax,%rdi
  b5ee1c:	mov    %rax,%r12
  b5ee1f:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ee24:	mov    0x4130(%rsp),%rdi
  b5ee2c:	mov    $0x1423a20,%eax
  b5ee31:	sub    $0x18,%rdi
  b5ee35:	cmp    %rdi,%rax
  b5ee38:	jne    b5f925 <_ZN14CInventoryMenu11createMenusEv+0x8f45>
  b5ee3e:	mov    $0x5a6ce0,%edx
  b5ee43:	mov    $0xfaaa70,%esi
  b5ee48:	mov    %r12,%rdi
  b5ee4b:	call   5542b8 <__cxa_throw@plt>
  b5ee50:	lea    0x4120(%rsp),%rbp
  b5ee58:	lea    0x44a0(%rsp),%rdx
  b5ee60:	mov    $0xfaa820,%esi
  b5ee65:	mov    %rbp,%rdi
  b5ee68:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5ee6d:	mov    $0x10,%edi
  b5ee72:	call   553738 <__cxa_allocate_exception@plt>
  b5ee77:	mov    %rbp,%rsi
  b5ee7a:	mov    %rax,%rdi
  b5ee7d:	mov    %rax,%r12
  b5ee80:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5ee85:	mov    0x4120(%rsp),%rdi
  b5ee8d:	mov    $0x1423a20,%eax
  b5ee92:	sub    $0x18,%rdi
  b5ee96:	cmp    %rdi,%rax
  b5ee99:	jne    b5f9ed <_ZN14CInventoryMenu11createMenusEv+0x900d>
  b5ee9f:	mov    $0x5a6ce0,%edx
  b5eea4:	mov    $0xfaaa70,%esi
  b5eea9:	mov    %r12,%rdi
  b5eeac:	call   5542b8 <__cxa_throw@plt>
  b5eeb1:	lea    0x4110(%rsp),%rbp
  b5eeb9:	lea    0x449c(%rsp),%rdx
  b5eec1:	mov    $0xfaa820,%esi
  b5eec6:	mov    %rbp,%rdi
  b5eec9:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5eece:	mov    $0x10,%edi
  b5eed3:	call   553738 <__cxa_allocate_exception@plt>
  b5eed8:	mov    %rbp,%rsi
  b5eedb:	mov    %rax,%rdi
  b5eede:	mov    %rax,%r12
  b5eee1:	call   554e78 <_ZNSt12length_errorC1ERKSs@plt>
  b5eee6:	mov    0x4110(%rsp),%rdi
  b5eeee:	mov    $0x1423a20,%eax
  b5eef3:	sub    $0x18,%rdi
  b5eef7:	cmp    %rdi,%rax
  b5eefa:	jne    b5fc25 <_ZN14CInventoryMenu11createMenusEv+0x9245>
  b5ef00:	mov    $0x5a6ce0,%edx
  b5ef05:	mov    $0xfaaa70,%esi
  b5ef0a:	mov    %r12,%rdi
  b5ef0d:	call   5542b8 <__cxa_throw@plt>
  b5ef12:	lea    0xf0(%rsp),%rbp
  b5ef1a:	mov    $0x5,%esi
  b5ef1f:	movq   $0x20,0xf8(%rsp)
  b5ef2b:	movq   $0x0,0x100(%rsp)
  b5ef37:	movq   $0x0,0x110(%rsp)
  b5ef43:	mov    %rbp,%rdi
  b5ef46:	movq   $0x0,0x108(%rsp)
  b5ef52:	movq   $0x0,0x198(%rsp)
  b5ef5e:	movq   $0x0,0xf0(%rsp)
  b5ef6a:	movl   $0x0,0x118(%rsp)
  b5ef75:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5ef7a:	cmpq   $0x20,0xf8(%rsp)
  b5ef83:	lea    0x28(%rbp),%rdx
  b5ef87:	jbe    b5ef91 <_ZN14CInventoryMenu11createMenusEv+0x85b1>
  b5ef89:	mov    0x198(%rsp),%rdx
  b5ef91:	mov    $0xfef7ab,%eax
  b5ef96:	movzbl (%rax),%ecx
  b5ef99:	add    $0x1,%rax
  b5ef9d:	mov    %ecx,(%rdx)
  b5ef9f:	add    $0x4,%rdx
  b5efa3:	cmp    $0xfef7b0,%rax
  b5efa9:	jne    b5ef96 <_ZN14CInventoryMenu11createMenusEv+0x85b6>
  b5efab:	cmpq   $0x20,0xf8(%rsp)
  b5efb4:	movq   $0x5,0xf0(%rsp)
  b5efc0:	lea    0x3c(%rbp),%rax
  b5efc4:	jbe    b5efd2 <_ZN14CInventoryMenu11createMenusEv+0x85f2>
  b5efc6:	mov    0x198(%rsp),%rax
  b5efce:	add    $0x14,%rax
  b5efd2:	movl   $0x0,(%rax)
  b5efd8:	mov    0x48(%rbx),%rdi
  b5efdc:	mov    %rbp,%rsi
  b5efdf:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5efe4:	mov    %rax,0x9190(%rbx)
  b5efeb:	mov    %rbp,%rdi
  b5efee:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5eff3:	lea    0x40(%rsp),%rbp
  b5eff8:	mov    $0xc,%esi
  b5effd:	movq   $0x20,0x48(%rsp)
  b5f006:	movq   $0x0,0x50(%rsp)
  b5f00f:	movq   $0x0,0x60(%rsp)
  b5f018:	mov    %rbp,%rdi
  b5f01b:	movq   $0x0,0x58(%rsp)
  b5f024:	movq   $0x0,0xe8(%rsp)
  b5f030:	movq   $0x0,0x40(%rsp)
  b5f039:	movl   $0x0,0x68(%rsp)
  b5f041:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b5f046:	cmpq   $0x20,0x48(%rsp)
  b5f04c:	lea    0x28(%rbp),%rdx
  b5f050:	jbe    b5f05a <_ZN14CInventoryMenu11createMenusEv+0x867a>
  b5f052:	mov    0xe8(%rsp),%rdx
  b5f05a:	mov    $0xfef79e,%eax
  b5f05f:	movzbl (%rax),%ecx
  b5f062:	add    $0x1,%rax
  b5f066:	mov    %ecx,(%rdx)
  b5f068:	add    $0x4,%rdx
  b5f06c:	cmp    $0xfef7aa,%rax
  b5f072:	jne    b5f05f <_ZN14CInventoryMenu11createMenusEv+0x867f>
  b5f074:	cmpq   $0x20,0x48(%rsp)
  b5f07a:	movq   $0xc,0x40(%rsp)
  b5f083:	lea    0x58(%rbp),%rax
  b5f087:	jbe    b5f095 <_ZN14CInventoryMenu11createMenusEv+0x86b5>
  b5f089:	mov    0xe8(%rsp),%rax
  b5f091:	add    $0x30,%rax
  b5f095:	movl   $0x0,(%rax)
  b5f09b:	mov    0x28(%rbx),%rdi
  b5f09f:	mov    %rbp,%rsi
  b5f0a2:	call   554408 <_ZNK5CEGUI6Window20recursiveChildSearchERKNS_6StringE@plt>
  b5f0a7:	mov    %rax,0x9198(%rbx)
  b5f0ae:	mov    %rbp,%rdi
  b5f0b1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f0b6:	mov    0x9140(%rbx),%rax
  b5f0bd:	lea    0x4200(%rsp),%rbp
  b5f0c5:	lea    0x44c7(%rsp),%rdx
  b5f0cd:	mov    $0xff0561,%esi
  b5f0d2:	mov    %rbp,%rdi
  b5f0d5:	mov    (%rax),%rax
  b5f0d8:	mov    0x1a8(%rax),%r12
  b5f0df:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  b5f0e4:	mov    0x9140(%rbx),%rdi
  b5f0eb:	mov    %rbp,%rsi
  b5f0ee:	call   *%r12
  b5f0f1:	mov    %rax,0x9148(%rbx)
  b5f0f8:	mov    0x4200(%rsp),%rdi
  b5f100:	sub    $0x18,%rdi
  b5f104:	cmp    $0x1423a20,%rdi
  b5f10b:	jne    b5f425 <_ZN14CInventoryMenu11createMenusEv+0x8a45>
  b5f111:	movl   $0x0,0x4100(%rsp)
  b5f11c:	movl   $0x3f800000,0x4104(%rsp)
  b5f127:	lea    0x4100(%rsp),%rsi
  b5f12f:	movl   $0x40600000,0x4108(%rsp)
  b5f13a:	mov    0x9148(%rbx),%rdi
  b5f141:	call   5560f8 <_ZN4Ogre6Camera11setPositionERKNS_7Vector3E@plt>
  b5f146:	movl   $0x0,0x40f0(%rsp)
  b5f151:	movl   $0x3f800000,0x40f4(%rsp)
  b5f15c:	lea    0x40f0(%rsp),%rsi
  b5f164:	movl   $0x0,0x40f8(%rsp)
  b5f16f:	mov    0x9148(%rbx),%rdi
  b5f176:	call   556358 <_ZN4Ogre6Camera6lookAtERKNS_7Vector3E@plt>
  b5f17b:	mov    0x9148(%rbx),%rdi
  b5f182:	movss  0x445682(%rip),%xmm0        # fa480c <_ZTVN4Ogre13FrameListenerE+0x4c>
  b5f18a:	mov    (%rdi),%rax
  b5f18d:	call   *0x258(%rax)
  b5f193:	mov    0x9148(%rbx),%rdi
  b5f19a:	movss  0x453a36(%rip),%xmm0        # fb2bd8 <_ZTI18CMonsterDescriptor+0x18>
  b5f1a2:	mov    (%rdi),%rax
  b5f1a5:	call   *0x268(%rax)
  b5f1ab:	mov    0x70(%rbx),%rax
  b5f1af:	xor    %ecx,%ecx
  b5f1b1:	xor    %edx,%edx
  b5f1b3:	xor    %esi,%esi
  b5f1b5:	mov    $0x178,%edi
  b5f1ba:	mov    0x488(%rax),%r13
  b5f1c1:	call   553318 <_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_@plt>
  b5f1c6:	mov    %rax,%rdi
  b5f1c9:	mov    %rax,%rbp
  b5f1cc:	mov    0x70(%rbx),%r12
  b5f1d0:	call   d796c0 <_ZN10CRunicCoreC1Ev>
  b5f1d5:	lea    0x18(%rbp),%rdi
  b5f1d9:	movq   $0xfe5f30,0x0(%rbp)
  b5f1e1:	mov    %r12,0x10(%rbp)
  b5f1e5:	mov    $0x14c5c48,%esi
  b5f1ea:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  b5f1ef:	movl   $0xffffffff,0x20(%rbp)
  b5f1f6:	mov    %r13,0x28(%rbp)
  b5f1fa:	lea    0x44c6(%rsp),%rdx
  b5f202:	mov    %rbp,0x91a0(%rbx)
  b5f209:	lea    0x41f0(%rsp),%rbp
  b5f211:	mov    $0xfe5528,%esi
  b5f216:	mov    %rbp,%rdi
  b5f219:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  b5f21e:	mov    0x70(%rbx),%rsi
  b5f222:	mov    0x91a0(%rbx),%rdi
  b5f229:	mov    %rbp,%rdx
  b5f22c:	call   a96270 <_ZN13CSkillTooltip4loadEP7CGameUISbIwSt11char_traitsIwESaIwEE>
  b5f231:	mov    0x41f0(%rsp),%rdi
  b5f239:	mov    $0x1424540,%eax
  b5f23e:	sub    $0x18,%rdi
  b5f242:	cmp    %rdi,%rax
  b5f245:	jne    b5f39d <_ZN14CInventoryMenu11createMenusEv+0x89bd>
  b5f24b:	mov    0x3e40(%rsp),%rdi
  b5f253:	sub    $0x18,%rdi
  b5f257:	cmp    $0x1423a20,%rdi
  b5f25e:	jne    b5f35b <_ZN14CInventoryMenu11createMenusEv+0x897b>
  b5f264:	mov    0x3e30(%rsp),%rdi
  b5f26c:	mov    $0x1424540,%eax
  b5f271:	sub    $0x18,%rdi
  b5f275:	cmp    %rdi,%rax
  b5f278:	jne    b5f32f <_ZN14CInventoryMenu11createMenusEv+0x894f>
  b5f27e:	mov    0x3e28(%rsp),%rdi
  b5f286:	sub    $0x18,%rdi
  b5f28a:	cmp    $0x1423a20,%rdi
  b5f291:	jne    b5f2f1 <_ZN14CInventoryMenu11createMenusEv+0x8911>
  b5f293:	mov    0x3e20(%rsp),%rdi
  b5f29b:	sub    $0x18,%rdi
  b5f29f:	cmp    $0x1423a20,%rdi
  b5f2a6:	jne    b5f2cc <_ZN14CInventoryMenu11createMenusEv+0x88ec>
  b5f2a8:	mov    0x3e70(%rsp),%rdi
  b5f2b0:	test   %rdi,%rdi
  b5f2b3:	je     b5f2ba <_ZN14CInventoryMenu11createMenusEv+0x88da>
  b5f2b5:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  b5f2ba:	add    $0x44d8,%rsp
  b5f2c1:	pop    %rbx
  b5f2c2:	pop    %rbp
  b5f2c3:	pop    %r12
  b5f2c5:	pop    %r13
  b5f2c7:	pop    %r14
  b5f2c9:	pop    %r15
  b5f2cb:	ret
  b5f2cc:	mov    $0x5541c8,%eax
  b5f2d1:	test   %rax,%rax
  b5f2d4:	je     b5f319 <_ZN14CInventoryMenu11createMenusEv+0x8939>
  b5f2d6:	or     $0xffffffff,%eax
  b5f2d9:	lock xadd %eax,0x10(%rdi)
  b5f2de:	test   %eax,%eax
  b5f2e0:	jg     b5f2a8 <_ZN14CInventoryMenu11createMenusEv+0x88c8>
  b5f2e2:	lea    0x4491(%rsp),%rsi
  b5f2ea:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f2ef:	jmp    b5f2a8 <_ZN14CInventoryMenu11createMenusEv+0x88c8>
  b5f2f1:	mov    $0x5541c8,%eax
  b5f2f6:	test   %rax,%rax
  b5f2f9:	je     b5f324 <_ZN14CInventoryMenu11createMenusEv+0x8944>
  b5f2fb:	or     $0xffffffff,%eax
  b5f2fe:	lock xadd %eax,0x10(%rdi)
  b5f303:	test   %eax,%eax
  b5f305:	jg     b5f293 <_ZN14CInventoryMenu11createMenusEv+0x88b3>
  b5f307:	lea    0x4492(%rsp),%rsi
  b5f30f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f314:	jmp    b5f293 <_ZN14CInventoryMenu11createMenusEv+0x88b3>
  b5f319:	mov    0x10(%rdi),%eax
  b5f31c:	lea    -0x1(%rax),%edx
  b5f31f:	mov    %edx,0x10(%rdi)
  b5f322:	jmp    b5f2de <_ZN14CInventoryMenu11createMenusEv+0x88fe>
  b5f324:	mov    0x10(%rdi),%eax
  b5f327:	lea    -0x1(%rax),%edx
  b5f32a:	mov    %edx,0x10(%rdi)
  b5f32d:	jmp    b5f303 <_ZN14CInventoryMenu11createMenusEv+0x8923>
  b5f32f:	mov    $0x5541c8,%eax
  b5f334:	test   %rax,%rax
  b5f337:	je     b5f387 <_ZN14CInventoryMenu11createMenusEv+0x89a7>
  b5f339:	or     $0xffffffff,%eax
  b5f33c:	lock xadd %eax,0x10(%rdi)
  b5f341:	test   %eax,%eax
  b5f343:	jg     b5f27e <_ZN14CInventoryMenu11createMenusEv+0x889e>
  b5f349:	lea    0x4493(%rsp),%rsi
  b5f351:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5f356:	jmp    b5f27e <_ZN14CInventoryMenu11createMenusEv+0x889e>
  b5f35b:	mov    $0x5541c8,%eax
  b5f360:	test   %rax,%rax
  b5f363:	je     b5f392 <_ZN14CInventoryMenu11createMenusEv+0x89b2>
  b5f365:	or     $0xffffffff,%eax
  b5f368:	lock xadd %eax,0x10(%rdi)
  b5f36d:	test   %eax,%eax
  b5f36f:	jg     b5f264 <_ZN14CInventoryMenu11createMenusEv+0x8884>
  b5f375:	lea    0x4494(%rsp),%rsi
  b5f37d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f382:	jmp    b5f264 <_ZN14CInventoryMenu11createMenusEv+0x8884>
  b5f387:	mov    0x10(%rdi),%eax
  b5f38a:	lea    -0x1(%rax),%edx
  b5f38d:	mov    %edx,0x10(%rdi)
  b5f390:	jmp    b5f341 <_ZN14CInventoryMenu11createMenusEv+0x8961>
  b5f392:	mov    0x10(%rdi),%eax
  b5f395:	lea    -0x1(%rax),%edx
  b5f398:	mov    %edx,0x10(%rdi)
  b5f39b:	jmp    b5f36d <_ZN14CInventoryMenu11createMenusEv+0x898d>
  b5f39d:	mov    $0x5541c8,%eax
  b5f3a2:	test   %rax,%rax
  b5f3a5:	je     b5f3fb <_ZN14CInventoryMenu11createMenusEv+0x8a1b>
  b5f3a7:	or     $0xffffffff,%eax
  b5f3aa:	lock xadd %eax,0x10(%rdi)
  b5f3af:	test   %eax,%eax
  b5f3b1:	jg     b5f24b <_ZN14CInventoryMenu11createMenusEv+0x886b>
  b5f3b7:	lea    0x4495(%rsp),%rsi
  b5f3bf:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5f3c4:	jmp    b5f24b <_ZN14CInventoryMenu11createMenusEv+0x886b>
  b5f3c9:	mov    %rbp,%rdi
  b5f3cc:	mov    %rax,%rbx
  b5f3cf:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b5f3d4:	lea    0x3e20(%rsp),%rdi
  b5f3dc:	call   73d660 <_ZN9CFileInfoD1Ev>
  b5f3e1:	mov    0x3e70(%rsp),%rdi
  b5f3e9:	test   %rdi,%rdi
  b5f3ec:	je     b5f3f3 <_ZN14CInventoryMenu11createMenusEv+0x8a13>
  b5f3ee:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  b5f3f3:	mov    %rbx,%rdi
  b5f3f6:	call   554498 <_Unwind_Resume@plt>
  b5f3fb:	mov    0x10(%rdi),%eax
  b5f3fe:	lea    -0x1(%rax),%edx
  b5f401:	mov    %edx,0x10(%rdi)
  b5f404:	jmp    b5f3af <_ZN14CInventoryMenu11createMenusEv+0x89cf>
  b5f406:	mov    %rax,%rbx
  b5f409:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f40b:	mov    %rbp,%rdi
  b5f40e:	mov    %rax,%rbx
  b5f411:	call   d79920 <_ZN10CRunicCoreD1Ev>
  b5f416:	mov    %rbp,%rdi
  b5f419:	call   555268 <_ZN4Ogre12NedAllocImpl12deallocBytesEPv@plt>
  b5f41e:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f420:	mov    %rax,%rbx
  b5f423:	jmp    b5f416 <_ZN14CInventoryMenu11createMenusEv+0x8a36>
  b5f425:	mov    $0x5541c8,%eax
  b5f42a:	test   %rax,%rax
  b5f42d:	je     b5f463 <_ZN14CInventoryMenu11createMenusEv+0x8a83>
  b5f42f:	or     $0xffffffff,%eax
  b5f432:	lock xadd %eax,0x10(%rdi)
  b5f437:	test   %eax,%eax
  b5f439:	jg     b5f111 <_ZN14CInventoryMenu11createMenusEv+0x8731>
  b5f43f:	lea    0x4496(%rsp),%rsi
  b5f447:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f44c:	jmp    b5f111 <_ZN14CInventoryMenu11createMenusEv+0x8731>
  b5f451:	mov    %rbp,%rdi
  b5f454:	mov    %rax,%rbx
  b5f457:	call   556288 <_ZNSsD1Ev@plt>
  b5f45c:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f461:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5f463:	mov    0x10(%rdi),%eax
  b5f466:	lea    -0x1(%rax),%edx
  b5f469:	mov    %edx,0x10(%rdi)
  b5f46c:	jmp    b5f437 <_ZN14CInventoryMenu11createMenusEv+0x8a57>
  b5f46e:	mov    %rbp,%rdi
  b5f471:	mov    %rax,%rbx
  b5f474:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f479:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f47e:	xchg   %ax,%ax
  b5f480:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5f482:	mov    $0x5541c8,%eax
  b5f487:	test   %rax,%rax
  b5f48a:	je     b5f4f7 <_ZN14CInventoryMenu11createMenusEv+0x8b17>
  b5f48c:	or     $0xffffffff,%eax
  b5f48f:	lock xadd %eax,0x10(%rdi)
  b5f494:	test   %eax,%eax
  b5f496:	jg     b5ccea <_ZN14CInventoryMenu11createMenusEv+0x630a>
  b5f49c:	lea    0x44a8(%rsp),%rsi
  b5f4a4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f4a9:	jmp    b5ccea <_ZN14CInventoryMenu11createMenusEv+0x630a>
  b5f4ae:	lea    0xf60(%rsp),%rdi
  b5f4b6:	mov    %rax,%rbx
  b5f4b9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f4be:	lea    0xeb0(%rsp),%rdi
  b5f4c6:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f4cb:	lea    0x42d0(%rsp),%rdi
  b5f4d3:	call   556288 <_ZNSsD1Ev@plt>
  b5f4d8:	lea    0x42e0(%rsp),%rdi
  b5f4e0:	call   556288 <_ZNSsD1Ev@plt>
  b5f4e5:	lea    0xe00(%rsp),%rdi
  b5f4ed:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f4f2:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f4f7:	mov    0x10(%rdi),%eax
  b5f4fa:	lea    -0x1(%rax),%edx
  b5f4fd:	mov    %edx,0x10(%rdi)
  b5f500:	jmp    b5f494 <_ZN14CInventoryMenu11createMenusEv+0x8ab4>
  b5f502:	lea    0x4210(%rsp),%rdi
  b5f50a:	mov    %rax,%rbx
  b5f50d:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5f512:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f517:	lea    0x4220(%rsp),%rdi
  b5f51f:	mov    %rax,%rbx
  b5f522:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5f527:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f52c:	lea    0x4230(%rsp),%rdi
  b5f534:	mov    %rax,%rbx
  b5f537:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5f53c:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f541:	lea    0x4240(%rsp),%rdi
  b5f549:	mov    %rax,%rbx
  b5f54c:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5f551:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f556:	mov    $0x5541c8,%eax
  b5f55b:	test   %rax,%rax
  b5f55e:	je     b5f5ae <_ZN14CInventoryMenu11createMenusEv+0x8bce>
  b5f560:	or     $0xffffffff,%eax
  b5f563:	lock xadd %eax,0x10(%rdi)
  b5f568:	test   %eax,%eax
  b5f56a:	jg     b5e368 <_ZN14CInventoryMenu11createMenusEv+0x7988>
  b5f570:	lea    0x4497(%rsp),%rsi
  b5f578:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f57d:	jmp    b5e368 <_ZN14CInventoryMenu11createMenusEv+0x7988>
  b5f582:	mov    $0x5541c8,%eax
  b5f587:	test   %rax,%rax
  b5f58a:	je     b5f5b9 <_ZN14CInventoryMenu11createMenusEv+0x8bd9>
  b5f58c:	or     $0xffffffff,%eax
  b5f58f:	lock xadd %eax,0x10(%rdi)
  b5f594:	test   %eax,%eax
  b5f596:	jg     b5e34e <_ZN14CInventoryMenu11createMenusEv+0x796e>
  b5f59c:	lea    0x4498(%rsp),%rsi
  b5f5a4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f5a9:	jmp    b5e34e <_ZN14CInventoryMenu11createMenusEv+0x796e>
  b5f5ae:	mov    0x10(%rdi),%eax
  b5f5b1:	lea    -0x1(%rax),%edx
  b5f5b4:	mov    %edx,0x10(%rdi)
  b5f5b7:	jmp    b5f568 <_ZN14CInventoryMenu11createMenusEv+0x8b88>
  b5f5b9:	mov    0x10(%rdi),%eax
  b5f5bc:	lea    -0x1(%rax),%edx
  b5f5bf:	mov    %edx,0x10(%rdi)
  b5f5c2:	jmp    b5f594 <_ZN14CInventoryMenu11createMenusEv+0x8bb4>
  b5f5c4:	mov    %r13,%rdi
  b5f5c7:	mov    %rax,%rbx
  b5f5ca:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f5cf:	lea    0x4250(%rsp),%rdi
  b5f5d7:	call   556288 <_ZNSsD1Ev@plt>
  b5f5dc:	lea    0x4260(%rsp),%rdi
  b5f5e4:	call   556288 <_ZNSsD1Ev@plt>
  b5f5e9:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f5ee:	mov    %rax,%rbx
  b5f5f1:	jmp    b5f5cf <_ZN14CInventoryMenu11createMenusEv+0x8bef>
  b5f5f3:	mov    %r12,%rdi
  b5f5f6:	mov    %rax,%rbx
  b5f5f9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f5fe:	mov    %r13,%rdi
  b5f601:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f606:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f60b:	mov    %rax,%rbx
  b5f60e:	xchg   %ax,%ax
  b5f610:	jmp    b5f5fe <_ZN14CInventoryMenu11createMenusEv+0x8c1e>
  b5f612:	mov    %rax,%rbx
  b5f615:	lea    0x42c0(%rsp),%rdi
  b5f61d:	call   556288 <_ZNSsD1Ev@plt>
  b5f622:	lea    0x670(%rsp),%rdi
  b5f62a:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f62f:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f634:	mov    %rax,%rbx
  b5f637:	jmp    b5f622 <_ZN14CInventoryMenu11createMenusEv+0x8c42>
  b5f639:	mov    $0x5541c8,%eax
  b5f63e:	test   %rax,%rax
  b5f641:	je     b5f6ae <_ZN14CInventoryMenu11createMenusEv+0x8cce>
  b5f643:	or     $0xffffffff,%eax
  b5f646:	lock xadd %eax,0x10(%rdi)
  b5f64b:	test   %eax,%eax
  b5f64d:	jg     b5dcd6 <_ZN14CInventoryMenu11createMenusEv+0x72f6>
  b5f653:	lea    0x449e(%rsp),%rsi
  b5f65b:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f660:	jmp    b5dcd6 <_ZN14CInventoryMenu11createMenusEv+0x72f6>
  b5f665:	lea    0x5c0(%rsp),%rdi
  b5f66d:	mov    %rax,%rbx
  b5f670:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f675:	lea    0x510(%rsp),%rdi
  b5f67d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f682:	lea    0x4290(%rsp),%rdi
  b5f68a:	call   556288 <_ZNSsD1Ev@plt>
  b5f68f:	lea    0x42a0(%rsp),%rdi
  b5f697:	call   556288 <_ZNSsD1Ev@plt>
  b5f69c:	lea    0x460(%rsp),%rdi
  b5f6a4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f6a9:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f6ae:	mov    0x10(%rdi),%eax
  b5f6b1:	lea    -0x1(%rax),%edx
  b5f6b4:	mov    %edx,0x10(%rdi)
  b5f6b7:	jmp    b5f64b <_ZN14CInventoryMenu11createMenusEv+0x8c6b>
  b5f6b9:	lea    0x3b0(%rsp),%rdi
  b5f6c1:	mov    %rax,%rbx
  b5f6c4:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f6c9:	mov    %r15,%rdi
  b5f6cc:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f6d1:	lea    0x4270(%rsp),%rdi
  b5f6d9:	call   556288 <_ZNSsD1Ev@plt>
  b5f6de:	lea    0x4280(%rsp),%rdi
  b5f6e6:	call   556288 <_ZNSsD1Ev@plt>
  b5f6eb:	lea    0x250(%rsp),%rdi
  b5f6f3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f6f8:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f6fd:	mov    %rax,%rbx
  b5f700:	jmp    b5f6c9 <_ZN14CInventoryMenu11createMenusEv+0x8ce9>
  b5f702:	mov    %rax,%rbx
  b5f705:	jmp    b5f682 <_ZN14CInventoryMenu11createMenusEv+0x8ca2>
  b5f70a:	mov    %rax,%rbx
  b5f70d:	jmp    b5f68f <_ZN14CInventoryMenu11createMenusEv+0x8caf>
  b5f70f:	mov    %rax,%rbx
  b5f712:	jmp    b5f69c <_ZN14CInventoryMenu11createMenusEv+0x8cbc>
  b5f714:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5f719:	mov    $0x5541c8,%eax
  b5f71e:	test   %rax,%rax
  b5f721:	je     b5f771 <_ZN14CInventoryMenu11createMenusEv+0x8d91>
  b5f723:	or     $0xffffffff,%eax
  b5f726:	lock xadd %eax,0x10(%rdi)
  b5f72b:	test   %eax,%eax
  b5f72d:	jg     b5d7f0 <_ZN14CInventoryMenu11createMenusEv+0x6e10>
  b5f733:	lea    0x44a1(%rsp),%rsi
  b5f73b:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f740:	jmp    b5d7f0 <_ZN14CInventoryMenu11createMenusEv+0x6e10>
  b5f745:	mov    $0x5541c8,%eax
  b5f74a:	test   %rax,%rax
  b5f74d:	je     b5f77c <_ZN14CInventoryMenu11createMenusEv+0x8d9c>
  b5f74f:	or     $0xffffffff,%eax
  b5f752:	lock xadd %eax,0x10(%rdi)
  b5f757:	test   %eax,%eax
  b5f759:	jg     b5d7d6 <_ZN14CInventoryMenu11createMenusEv+0x6df6>
  b5f75f:	lea    0x44a2(%rsp),%rsi
  b5f767:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f76c:	jmp    b5d7d6 <_ZN14CInventoryMenu11createMenusEv+0x6df6>
  b5f771:	mov    0x10(%rdi),%eax
  b5f774:	lea    -0x1(%rax),%edx
  b5f777:	mov    %edx,0x10(%rdi)
  b5f77a:	jmp    b5f72b <_ZN14CInventoryMenu11createMenusEv+0x8d4b>
  b5f77c:	mov    0x10(%rdi),%eax
  b5f77f:	lea    -0x1(%rax),%edx
  b5f782:	mov    %edx,0x10(%rdi)
  b5f785:	jmp    b5f757 <_ZN14CInventoryMenu11createMenusEv+0x8d77>
  b5f787:	lea    0x7d0(%rsp),%rdi
  b5f78f:	mov    %rax,%rbx
  b5f792:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f797:	lea    0x720(%rsp),%rdi
  b5f79f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f7a4:	lea    0x42b0(%rsp),%rdi
  b5f7ac:	call   556288 <_ZNSsD1Ev@plt>
  b5f7b1:	jmp    b5f615 <_ZN14CInventoryMenu11createMenusEv+0x8c35>
  b5f7b6:	mov    %rax,%rbx
  b5f7b9:	jmp    b5f797 <_ZN14CInventoryMenu11createMenusEv+0x8db7>
  b5f7bb:	mov    %rax,%rbx
  b5f7be:	mov    %r12,%rdi
  b5f7c1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5f7c6:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f7cb:	mov    $0x5541c8,%eax
  b5f7d0:	test   %rax,%rax
  b5f7d3:	je     b5f817 <_ZN14CInventoryMenu11createMenusEv+0x8e37>
  b5f7d5:	or     $0xffffffff,%eax
  b5f7d8:	lock xadd %eax,0x10(%rdi)
  b5f7dd:	test   %eax,%eax
  b5f7df:	jg     b5ed7c <_ZN14CInventoryMenu11createMenusEv+0x839c>
  b5f7e5:	lea    0x44a9(%rsp),%rsi
  b5f7ed:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f7f2:	jmp    b5ed7c <_ZN14CInventoryMenu11createMenusEv+0x839c>
  b5f7f7:	mov    %r12,%rdi
  b5f7fa:	mov    %rax,%rbx
  b5f7fd:	call   5552b8 <__cxa_free_exception@plt>
  b5f802:	mov    %rbp,%rdi
  b5f805:	call   556288 <_ZNSsD1Ev@plt>
  b5f80a:	jmp    b5f4be <_ZN14CInventoryMenu11createMenusEv+0x8ade>
  b5f80f:	mov    %rax,%rbx
  b5f812:	jmp    b5f4be <_ZN14CInventoryMenu11createMenusEv+0x8ade>
  b5f817:	mov    0x10(%rdi),%eax
  b5f81a:	lea    -0x1(%rax),%edx
  b5f81d:	mov    %edx,0x10(%rdi)
  b5f820:	jmp    b5f7dd <_ZN14CInventoryMenu11createMenusEv+0x8dfd>
  b5f822:	cmp    $0xffffffffffffffff,%rdx
  b5f826:	mov    %rax,%rbx
  b5f829:	jne    b5f4be <_ZN14CInventoryMenu11createMenusEv+0x8ade>
  b5f82f:	call   555f88 <_ZSt9terminatev@plt>
  b5f834:	mov    %rax,%rbx
  b5f837:	jmp    b5f7a4 <_ZN14CInventoryMenu11createMenusEv+0x8dc4>
  b5f83c:	mov    $0x5541c8,%eax
  b5f841:	test   %rax,%rax
  b5f844:	je     b5f885 <_ZN14CInventoryMenu11createMenusEv+0x8ea5>
  b5f846:	or     $0xffffffff,%eax
  b5f849:	lock xadd %eax,0x10(%rdi)
  b5f84e:	test   %eax,%eax
  b5f850:	jg     b5eddd <_ZN14CInventoryMenu11createMenusEv+0x83fd>
  b5f856:	lea    0x44a5(%rsp),%rsi
  b5f85e:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f863:	jmp    b5eddd <_ZN14CInventoryMenu11createMenusEv+0x83fd>
  b5f868:	mov    %r12,%rdi
  b5f86b:	mov    %rax,%rbx
  b5f86e:	call   5552b8 <__cxa_free_exception@plt>
  b5f873:	mov    %rbp,%rdi
  b5f876:	call   556288 <_ZNSsD1Ev@plt>
  b5f87b:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f880:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5f885:	mov    0x10(%rdi),%eax
  b5f888:	lea    -0x1(%rax),%edx
  b5f88b:	mov    %edx,0x10(%rdi)
  b5f88e:	xchg   %ax,%ax
  b5f890:	jmp    b5f84e <_ZN14CInventoryMenu11createMenusEv+0x8e6e>
  b5f892:	cmp    $0xffffffffffffffff,%rdx
  b5f896:	mov    %rax,%rbx
  b5f899:	jne    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5f89f:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b5f8a1:	mov    %rax,%rbx
  b5f8a4:	jmp    b5f6de <_ZN14CInventoryMenu11createMenusEv+0x8cfe>
  b5f8a9:	mov    %rax,%rbx
  b5f8ac:	nopl   0x0(%rax)
  b5f8b0:	jmp    b5f6eb <_ZN14CInventoryMenu11createMenusEv+0x8d0b>
  b5f8b5:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5f8ba:	mov    $0x5541c8,%eax
  b5f8bf:	test   %rax,%rax
  b5f8c2:	je     b5f951 <_ZN14CInventoryMenu11createMenusEv+0x8f71>
  b5f8c8:	or     $0xffffffff,%eax
  b5f8cb:	lock xadd %eax,0x10(%rdi)
  b5f8d0:	test   %eax,%eax
  b5f8d2:	jg     b5dcf0 <_ZN14CInventoryMenu11createMenusEv+0x7310>
  b5f8d8:	lea    0x449d(%rsp),%rsi
  b5f8e0:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f8e5:	jmp    b5dcf0 <_ZN14CInventoryMenu11createMenusEv+0x7310>
  b5f8ea:	mov    %rax,%rbx
  b5f8ed:	jmp    b5f675 <_ZN14CInventoryMenu11createMenusEv+0x8c95>
  b5f8f2:	mov    %r12,%rdi
  b5f8f5:	mov    %rax,%rbx
  b5f8f8:	call   5552b8 <__cxa_free_exception@plt>
  b5f8fd:	mov    %rbp,%rdi
  b5f900:	call   556288 <_ZNSsD1Ev@plt>
  b5f905:	jmp    b5f797 <_ZN14CInventoryMenu11createMenusEv+0x8db7>
  b5f90a:	jmp    b5f7b6 <_ZN14CInventoryMenu11createMenusEv+0x8dd6>
  b5f90f:	cmp    $0xffffffffffffffff,%rdx
  b5f913:	mov    %rax,%rbx
  b5f916:	jne    b5f797 <_ZN14CInventoryMenu11createMenusEv+0x8db7>
  b5f91c:	nopl   0x0(%rax)
  b5f920:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b5f925:	mov    $0x5541c8,%eax
  b5f92a:	test   %rax,%rax
  b5f92d:	je     b5f95f <_ZN14CInventoryMenu11createMenusEv+0x8f7f>
  b5f92f:	or     $0xffffffff,%eax
  b5f932:	lock xadd %eax,0x10(%rdi)
  b5f937:	test   %eax,%eax
  b5f939:	jg     b5ee3e <_ZN14CInventoryMenu11createMenusEv+0x845e>
  b5f93f:	lea    0x44a3(%rsp),%rsi
  b5f947:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f94c:	jmp    b5ee3e <_ZN14CInventoryMenu11createMenusEv+0x845e>
  b5f951:	mov    0x10(%rdi),%eax
  b5f954:	lea    -0x1(%rax),%edx
  b5f957:	mov    %edx,0x10(%rdi)
  b5f95a:	jmp    b5f8d0 <_ZN14CInventoryMenu11createMenusEv+0x8ef0>
  b5f95f:	mov    0x10(%rdi),%eax
  b5f962:	lea    -0x1(%rax),%edx
  b5f965:	mov    %edx,0x10(%rdi)
  b5f968:	jmp    b5f937 <_ZN14CInventoryMenu11createMenusEv+0x8f57>
  b5f96a:	mov    %rax,%rbx
  b5f96d:	jmp    b5f5dc <_ZN14CInventoryMenu11createMenusEv+0x8bfc>
  b5f972:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5f977:	mov    $0x5541c8,%eax
  b5f97c:	test   %rax,%rax
  b5f97f:	je     b5f9cf <_ZN14CInventoryMenu11createMenusEv+0x8fef>
  b5f981:	or     $0xffffffff,%eax
  b5f984:	lock xadd %eax,0x10(%rdi)
  b5f989:	test   %eax,%eax
  b5f98b:	jg     b5e166 <_ZN14CInventoryMenu11createMenusEv+0x7786>
  b5f991:	lea    0x4499(%rsp),%rsi
  b5f999:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f99e:	jmp    b5e166 <_ZN14CInventoryMenu11createMenusEv+0x7786>
  b5f9a3:	mov    $0x5541c8,%eax
  b5f9a8:	test   %rax,%rax
  b5f9ab:	je     b5f9da <_ZN14CInventoryMenu11createMenusEv+0x8ffa>
  b5f9ad:	or     $0xffffffff,%eax
  b5f9b0:	lock xadd %eax,0x10(%rdi)
  b5f9b5:	test   %eax,%eax
  b5f9b7:	jg     b5e14c <_ZN14CInventoryMenu11createMenusEv+0x776c>
  b5f9bd:	lea    0x449a(%rsp),%rsi
  b5f9c5:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5f9ca:	jmp    b5e14c <_ZN14CInventoryMenu11createMenusEv+0x776c>
  b5f9cf:	mov    0x10(%rdi),%eax
  b5f9d2:	lea    -0x1(%rax),%edx
  b5f9d5:	mov    %edx,0x10(%rdi)
  b5f9d8:	jmp    b5f989 <_ZN14CInventoryMenu11createMenusEv+0x8fa9>
  b5f9da:	mov    0x10(%rdi),%eax
  b5f9dd:	lea    -0x1(%rax),%edx
  b5f9e0:	mov    %edx,0x10(%rdi)
  b5f9e3:	jmp    b5f9b5 <_ZN14CInventoryMenu11createMenusEv+0x8fd5>
  b5f9e5:	mov    %rax,%rbx
  b5f9e8:	jmp    b5f6d1 <_ZN14CInventoryMenu11createMenusEv+0x8cf1>
  b5f9ed:	mov    $0x5541c8,%eax
  b5f9f2:	test   %rax,%rax
  b5f9f5:	je     b5fa36 <_ZN14CInventoryMenu11createMenusEv+0x9056>
  b5f9f7:	or     $0xffffffff,%eax
  b5f9fa:	lock xadd %eax,0x10(%rdi)
  b5f9ff:	test   %eax,%eax
  b5fa01:	jg     b5ee9f <_ZN14CInventoryMenu11createMenusEv+0x84bf>
  b5fa07:	lea    0x449f(%rsp),%rsi
  b5fa0f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5fa14:	jmp    b5ee9f <_ZN14CInventoryMenu11createMenusEv+0x84bf>
  b5fa19:	mov    %r12,%rdi
  b5fa1c:	mov    %rax,%rbx
  b5fa1f:	call   5552b8 <__cxa_free_exception@plt>
  b5fa24:	mov    %rbp,%rdi
  b5fa27:	call   556288 <_ZNSsD1Ev@plt>
  b5fa2c:	jmp    b5f675 <_ZN14CInventoryMenu11createMenusEv+0x8c95>
  b5fa31:	jmp    b5f8ea <_ZN14CInventoryMenu11createMenusEv+0x8f0a>
  b5fa36:	mov    0x10(%rdi),%eax
  b5fa39:	lea    -0x1(%rax),%edx
  b5fa3c:	mov    %edx,0x10(%rdi)
  b5fa3f:	nop
  b5fa40:	jmp    b5f9ff <_ZN14CInventoryMenu11createMenusEv+0x901f>
  b5fa42:	cmp    $0xffffffffffffffff,%rdx
  b5fa46:	mov    %rax,%rbx
  b5fa49:	jne    b5f675 <_ZN14CInventoryMenu11createMenusEv+0x8c95>
  b5fa4f:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b5fa54:	mov    %r13,%rdi
  b5fa57:	mov    %rax,%rbx
  b5fa5a:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5fa5f:	nop
  b5fa60:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5fa65:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b5fa67:	nopw   0x0(%rax,%rax,1)
  b5fa70:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b5fa72:	mov    $0x5541c8,%eax
  b5fa77:	test   %rax,%rax
  b5fa7a:	je     b5fb02 <_ZN14CInventoryMenu11createMenusEv+0x9122>
  b5fa80:	or     $0xffffffff,%eax
  b5fa83:	lock xadd %eax,0x10(%rdi)
  b5fa88:	test   %eax,%eax
  b5fa8a:	jg     b5c61b <_ZN14CInventoryMenu11createMenusEv+0x5c3b>
  b5fa90:	lea    0x44ab(%rsp),%rsi
  b5fa98:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5fa9d:	jmp    b5c61b <_ZN14CInventoryMenu11createMenusEv+0x5c3b>
  b5faa2:	mov    $0x5541c8,%eax
  b5faa7:	test   %rax,%rax
  b5faaa:	je     b5fb15 <_ZN14CInventoryMenu11createMenusEv+0x9135>
  b5faac:	or     $0xffffffff,%eax
  b5faaf:	lock xadd %eax,0x10(%rdi)
  b5fab4:	test   %eax,%eax
  b5fab6:	jg     b5c601 <_ZN14CInventoryMenu11createMenusEv+0x5c21>
  b5fabc:	lea    0x44ac(%rsp),%rsi
  b5fac4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5fac9:	jmp    b5c601 <_ZN14CInventoryMenu11createMenusEv+0x5c21>
  b5face:	mov    %rax,%rbx
  b5fad1:	lea    0x4330(%rsp),%rdi
  b5fad9:	call   556288 <_ZNSsD1Ev@plt>
  b5fade:	lea    0x4340(%rsp),%rdi
  b5fae6:	call   556288 <_ZNSsD1Ev@plt>
  b5faeb:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5faf0:	lea    0x1010(%rsp),%rdi
  b5faf8:	mov    %rax,%rbx
  b5fafb:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fb00:	jmp    b5fad1 <_ZN14CInventoryMenu11createMenusEv+0x90f1>
  b5fb02:	mov    0x10(%rdi),%eax
  b5fb05:	lea    -0x1(%rax),%edx
  b5fb08:	mov    %edx,0x10(%rdi)
  b5fb0b:	jmp    b5fa88 <_ZN14CInventoryMenu11createMenusEv+0x90a8>
  b5fb10:	mov    %rax,%rbx
  b5fb13:	jmp    b5fade <_ZN14CInventoryMenu11createMenusEv+0x90fe>
  b5fb15:	mov    0x10(%rdi),%eax
  b5fb18:	lea    -0x1(%rax),%edx
  b5fb1b:	mov    %edx,0x10(%rdi)
  b5fb1e:	jmp    b5fab4 <_ZN14CInventoryMenu11createMenusEv+0x90d4>
  b5fb20:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5fb25:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5fb2a:	nopw   0x0(%rax,%rax,1)
  b5fb30:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5fb35:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fb40:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5fb45:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fb50:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fb55:	mov    %r14,%rdi
  b5fb58:	mov    %rax,%rbx
  b5fb5b:	nopl   0x0(%rax,%rax,1)
  b5fb60:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fb65:	jmp    b5f5fe <_ZN14CInventoryMenu11createMenusEv+0x8c1e>
  b5fb6a:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fb6f:	nop
  b5fb70:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fb75:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fb80:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5fb85:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fb90:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fb95:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fba0:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5fba5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fbb0:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fbb5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fbc0:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5fbc5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fbd0:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5fbd5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fbe0:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5fbe5:	mov    $0x5541c8,%eax
  b5fbea:	test   %rax,%rax
  b5fbed:	nopl   (%rax)
  b5fbf0:	je     b5fca5 <_ZN14CInventoryMenu11createMenusEv+0x92c5>
  b5fbf6:	or     $0xffffffff,%eax
  b5fbf9:	lock xadd %eax,0x10(%rdi)
  b5fbfe:	test   %eax,%eax
  b5fc00:	jg     b5cd04 <_ZN14CInventoryMenu11createMenusEv+0x6324>
  b5fc06:	lea    0x44a7(%rsp),%rsi
  b5fc0e:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5fc13:	jmp    b5cd04 <_ZN14CInventoryMenu11createMenusEv+0x6324>
  b5fc18:	mov    %rax,%rbx
  b5fc1b:	jmp    b5f4cb <_ZN14CInventoryMenu11createMenusEv+0x8aeb>
  b5fc20:	jmp    b5f80f <_ZN14CInventoryMenu11createMenusEv+0x8e2f>
  b5fc25:	mov    $0x5541c8,%eax
  b5fc2a:	test   %rax,%rax
  b5fc2d:	je     b5fc6e <_ZN14CInventoryMenu11createMenusEv+0x928e>
  b5fc2f:	or     $0xffffffff,%eax
  b5fc32:	lock xadd %eax,0x10(%rdi)
  b5fc37:	test   %eax,%eax
  b5fc39:	jg     b5ef00 <_ZN14CInventoryMenu11createMenusEv+0x8520>
  b5fc3f:	lea    0x449b(%rsp),%rsi
  b5fc47:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b5fc4c:	jmp    b5ef00 <_ZN14CInventoryMenu11createMenusEv+0x8520>
  b5fc51:	mov    %r12,%rdi
  b5fc54:	mov    %rax,%rbx
  b5fc57:	call   5552b8 <__cxa_free_exception@plt>
  b5fc5c:	mov    %rbp,%rdi
  b5fc5f:	call   556288 <_ZNSsD1Ev@plt>
  b5fc64:	jmp    b5f6c9 <_ZN14CInventoryMenu11createMenusEv+0x8ce9>
  b5fc69:	jmp    b5f6fd <_ZN14CInventoryMenu11createMenusEv+0x8d1d>
  b5fc6e:	mov    0x10(%rdi),%eax
  b5fc71:	lea    -0x1(%rax),%edx
  b5fc74:	mov    %edx,0x10(%rdi)
  b5fc77:	jmp    b5fc37 <_ZN14CInventoryMenu11createMenusEv+0x9257>
  b5fc79:	cmp    $0xffffffffffffffff,%rdx
  b5fc7d:	mov    %rax,%rbx
  b5fc80:	jne    b5f6c9 <_ZN14CInventoryMenu11createMenusEv+0x8ce9>
  b5fc86:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b5fc8b:	mov    %rax,%rbx
  b5fc8e:	jmp    b5f4e5 <_ZN14CInventoryMenu11createMenusEv+0x8b05>
  b5fc93:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b5fc98:	mov    %rax,%rbx
  b5fc9b:	nopl   0x0(%rax,%rax,1)
  b5fca0:	jmp    b5f4d8 <_ZN14CInventoryMenu11createMenusEv+0x8af8>
  b5fca5:	mov    0x10(%rdi),%eax
  b5fca8:	lea    -0x1(%rax),%edx
  b5fcab:	mov    %edx,0x10(%rdi)
  b5fcae:	jmp    b5fbfe <_ZN14CInventoryMenu11createMenusEv+0x921e>
  b5fcb3:	mov    %r15,%rdi
  b5fcb6:	mov    %rax,%rbx
  b5fcb9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fcbe:	mov    %r14,%rdi
  b5fcc1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fcc6:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5fccb:	mov    %rax,%rbx
  b5fcce:	xchg   %ax,%ax
  b5fcd0:	jmp    b5fcbe <_ZN14CInventoryMenu11createMenusEv+0x92de>
  b5fcd2:	jmp    b5fcb3 <_ZN14CInventoryMenu11createMenusEv+0x92d3>
  b5fcd4:	jmp    b5fccb <_ZN14CInventoryMenu11createMenusEv+0x92eb>
  b5fcd6:	cs nopw 0x0(%rax,%rax,1)
  b5fce0:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fce5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fcf0:	jmp    b5fcb3 <_ZN14CInventoryMenu11createMenusEv+0x92d3>
  b5fcf2:	jmp    b5fccb <_ZN14CInventoryMenu11createMenusEv+0x92eb>
  b5fcf4:	jmp    b5fb55 <_ZN14CInventoryMenu11createMenusEv+0x9175>
  b5fcf9:	nopl   0x0(%rax)
  b5fd00:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fd05:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd10:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5fd15:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd20:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5fd25:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd30:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fd35:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd40:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fd45:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd50:	jmp    b5fccb <_ZN14CInventoryMenu11createMenusEv+0x92eb>
  b5fd55:	mov    %r13,%rdi
  b5fd58:	mov    %rax,%rbx
  b5fd5b:	nopl   0x0(%rax,%rax,1)
  b5fd60:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fd65:	jmp    b5fcbe <_ZN14CInventoryMenu11createMenusEv+0x92de>
  b5fd6a:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5fd6f:	nop
  b5fd70:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fd75:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd80:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5fd85:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fd90:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5fd95:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fda0:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fda5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fdb0:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5fdb5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fdc0:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5fdc5:	mov    %rax,%rbx
  b5fdc8:	mov    %r14,%rdi
  b5fdcb:	nopl   0x0(%rax,%rax,1)
  b5fdd0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fdd5:	jmp    b5f7be <_ZN14CInventoryMenu11createMenusEv+0x8dde>
  b5fdda:	mov    %r13,%rdi
  b5fddd:	mov    %rax,%rbx
  b5fde0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fde5:	jmp    b5fdc8 <_ZN14CInventoryMenu11createMenusEv+0x93e8>
  b5fde7:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5fdec:	nopl   0x0(%rax)
  b5fdf0:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5fdf5:	mov    %r12,%rdi
  b5fdf8:	mov    %rax,%rbx
  b5fdfb:	nopl   0x0(%rax,%rax,1)
  b5fe00:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fe05:	mov    %r13,%rdi
  b5fe08:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fe0d:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b5fe12:	mov    %rax,%rbx
  b5fe15:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b5fe1a:	mov    %r12,%rdi
  b5fe1d:	mov    %rax,%rbx
  b5fe20:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5fe25:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b5fe2a:	mov    %rax,%rbx
  b5fe2d:	lea    0x3e20(%rsp),%rdi
  b5fe35:	call   556288 <_ZNSsD1Ev@plt>
  b5fe3a:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b5fe3f:	lea    0x3e20(%rsp),%rdi
  b5fe47:	mov    %rax,%rbx
  b5fe4a:	add    $0x8,%rdi
  b5fe4e:	call   556288 <_ZNSsD1Ev@plt>
  b5fe53:	jmp    b5fe2d <_ZN14CInventoryMenu11createMenusEv+0x944d>
  b5fe55:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5fe5a:	mov    %r12,%rdi
  b5fe5d:	mov    %rax,%rbx
  b5fe60:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  b5fe65:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5fe6a:	mov    $0x5541c8,%eax
  b5fe6f:	test   %rax,%rax
  b5fe72:	je     b5fec2 <_ZN14CInventoryMenu11createMenusEv+0x94e2>
  b5fe74:	or     $0xffffffff,%eax
  b5fe77:	lock xadd %eax,0x10(%rdi)
  b5fe7c:	test   %eax,%eax
  b5fe7e:	jg     b5761c <_ZN14CInventoryMenu11createMenusEv+0xc3c>
  b5fe84:	lea    0x44bf(%rsp),%rsi
  b5fe8c:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  b5fe91:	jmp    b5761c <_ZN14CInventoryMenu11createMenusEv+0xc3c>
  b5fe96:	mov    %rax,%rbx
  b5fe99:	mov    %r14,%rdi
  b5fe9c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5fea1:	lea    0x3b60(%rsp),%rdi
  b5fea9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5feae:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b5feb3:	mov    %r13,%rdi
  b5feb6:	mov    %rax,%rbx
  b5feb9:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5febe:	xchg   %ax,%ax
  b5fec0:	jmp    b5fe99 <_ZN14CInventoryMenu11createMenusEv+0x94b9>
  b5fec2:	mov    0x10(%rdi),%eax
  b5fec5:	lea    -0x1(%rax),%edx
  b5fec8:	mov    %edx,0x10(%rdi)
  b5fecb:	jmp    b5fe7c <_ZN14CInventoryMenu11createMenusEv+0x949c>
  b5fecd:	jmp    b5fe12 <_ZN14CInventoryMenu11createMenusEv+0x9432>
  b5fed2:	mov    %rax,%rbx
  b5fed5:	jmp    b5fe05 <_ZN14CInventoryMenu11createMenusEv+0x9425>
  b5feda:	lea    0x43b0(%rsp),%rdi
  b5fee2:	mov    %rax,%rbx
  b5fee5:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5feea:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5feef:	mov    %rax,%rbx
  b5fef2:	lea    0x2400(%rsp),%rdi
  b5fefa:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5feff:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff04:	lea    0x2350(%rsp),%rdi
  b5ff0c:	mov    %rax,%rbx
  b5ff0f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ff14:	jmp    b5fef2 <_ZN14CInventoryMenu11createMenusEv+0x9512>
  b5ff16:	mov    %rax,%rbx
  b5ff19:	lea    0x2140(%rsp),%rdi
  b5ff21:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ff26:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff2b:	lea    0x24b0(%rsp),%rdi
  b5ff33:	mov    %rax,%rbx
  b5ff36:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b5ff3b:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff40:	lea    0x43e0(%rsp),%rdi
  b5ff48:	mov    %rax,%rbx
  b5ff4b:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5ff50:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff55:	lea    0x43d0(%rsp),%rdi
  b5ff5d:	mov    %rax,%rbx
  b5ff60:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5ff65:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff6a:	lea    0x43c0(%rsp),%rdi
  b5ff72:	mov    %rax,%rbx
  b5ff75:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5ff7a:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff7f:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5ff84:	mov    %r12,%rdi
  b5ff87:	mov    %rax,%rbx
  b5ff8a:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b5ff8f:	nop
  b5ff90:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b5ff95:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b5ff9a:	nopw   0x0(%rax,%rax,1)
  b5ffa0:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b5ffa5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5ffb0:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5ffb5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5ffc0:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b5ffc5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5ffd0:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b5ffd5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5ffe0:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b5ffe5:	data16 cs nopw 0x0(%rax,%rax,1)
  b5fff0:	jmp    b5f46e <_ZN14CInventoryMenu11createMenusEv+0x8a8e>
  b5fff5:	data16 cs nopw 0x0(%rax,%rax,1)
  b60000:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b60005:	data16 cs nopw 0x0(%rax,%rax,1)
  b60010:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b60015:	mov    %rbp,%rdi
  b60018:	mov    %rax,%rbx
  b6001b:	nopl   0x0(%rax,%rax,1)
  b60020:	call   554b78 <_ZN5CEGUI14SubscriberSlotD1Ev@plt>
  b60025:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b6002a:	mov    %rax,%rbx
  b6002d:	lea    0x2e50(%rsp),%rdi
  b60035:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6003a:	lea    0x2da0(%rsp),%rdi
  b60042:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60047:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b6004c:	mov    %r14,%rdi
  b6004f:	mov    %rax,%rbx
  b60052:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60057:	jmp    b6002d <_ZN14CInventoryMenu11createMenusEv+0x964d>
  b60059:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b6005e:	xchg   %ax,%ax
  b60060:	jmp    b5f60b <_ZN14CInventoryMenu11createMenusEv+0x8c2b>
  b60065:	data16 cs nopw 0x0(%rax,%rax,1)
  b60070:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b60075:	data16 cs nopw 0x0(%rax,%rax,1)
  b60080:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b60085:	mov    %rax,%rbx
  b60088:	nopl   0x0(%rax,%rax,1)
  b60090:	jmp    b6003a <_ZN14CInventoryMenu11createMenusEv+0x965a>
  b60092:	mov    %rax,%rbx
  b60095:	lea    0x21f0(%rsp),%rdi
  b6009d:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b600a2:	lea    0x4390(%rsp),%rdi
  b600aa:	call   556288 <_ZNSsD1Ev@plt>
  b600af:	lea    0x43a0(%rsp),%rdi
  b600b7:	call   556288 <_ZNSsD1Ev@plt>
  b600bc:	jmp    b5ff19 <_ZN14CInventoryMenu11createMenusEv+0x9539>
  b600c1:	jmp    b5f5f3 <_ZN14CInventoryMenu11createMenusEv+0x8c13>
  b600c6:	cs nopw 0x0(%rax,%rax,1)
  b600d0:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b600d5:	mov    %rax,%rbx
  b600d8:	lea    0x2a30(%rsp),%rdi
  b600e0:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b600e5:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b600ea:	mov    %rax,%rbx
  b600ed:	lea    0x4370(%rsp),%rdi
  b600f5:	call   556288 <_ZNSsD1Ev@plt>
  b600fa:	lea    0x4380(%rsp),%rdi
  b60102:	call   556288 <_ZNSsD1Ev@plt>
  b60107:	lea    0x1f30(%rsp),%rdi
  b6010f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60114:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b60119:	mov    %rax,%rbx
  b6011c:	lea    0x2ae0(%rsp),%rdi
  b60124:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60129:	jmp    b600d8 <_ZN14CInventoryMenu11createMenusEv+0x96f8>
  b6012b:	mov    %r14,%rdi
  b6012e:	mov    %rax,%rbx
  b60131:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60136:	jmp    b6011c <_ZN14CInventoryMenu11createMenusEv+0x973c>
  b60138:	mov    %rax,%rbx
  b6013b:	lea    0x1fe0(%rsp),%rdi
  b60143:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60148:	jmp    b600ed <_ZN14CInventoryMenu11createMenusEv+0x970d>
  b6014a:	mov    %rax,%rbx
  b6014d:	lea    0x1dd0(%rsp),%rdi
  b60155:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b6015a:	lea    0x4350(%rsp),%rdi
  b60162:	call   556288 <_ZNSsD1Ev@plt>
  b60167:	lea    0x4360(%rsp),%rdi
  b6016f:	call   556288 <_ZNSsD1Ev@plt>
  b60174:	lea    0x1d20(%rsp),%rdi
  b6017c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60181:	jmp    b5f3d4 <_ZN14CInventoryMenu11createMenusEv+0x89f4>
  b60186:	jmp    b5f7bb <_ZN14CInventoryMenu11createMenusEv+0x8ddb>
  b6018b:	nopl   0x0(%rax,%rax,1)
  b60190:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b60195:	data16 cs nopw 0x0(%rax,%rax,1)
  b601a0:	jmp    b5fa54 <_ZN14CInventoryMenu11createMenusEv+0x9074>
  b601a5:	data16 cs nopw 0x0(%rax,%rax,1)
  b601b0:	jmp    b60015 <_ZN14CInventoryMenu11createMenusEv+0x9635>
  b601b5:	mov    $0x5541c8,%eax
  b601ba:	test   %rax,%rax
  b601bd:	nopl   (%rax)
  b601c0:	je     b601e9 <_ZN14CInventoryMenu11createMenusEv+0x9809>
  b601c2:	or     $0xffffffff,%eax
  b601c5:	lock xadd %eax,0x10(%rdi)
  b601ca:	test   %eax,%eax
  b601cc:	jg     b5aad0 <_ZN14CInventoryMenu11createMenusEv+0x40f0>
  b601d2:	lea    0x44b1(%rsp),%rsi
  b601da:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b601df:	jmp    b5aad0 <_ZN14CInventoryMenu11createMenusEv+0x40f0>
  b601e4:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b601e9:	mov    0x10(%rdi),%eax
  b601ec:	lea    -0x1(%rax),%edx
  b601ef:	mov    %edx,0x10(%rdi)
  b601f2:	jmp    b601ca <_ZN14CInventoryMenu11createMenusEv+0x97ea>
  b601f4:	mov    %rax,%rbx
  b601f7:	jmp    b60174 <_ZN14CInventoryMenu11createMenusEv+0x9794>
  b601fc:	jmp    b5ff84 <_ZN14CInventoryMenu11createMenusEv+0x95a4>
  b60201:	mov    %rax,%rbx
  b60204:	jmp    b60167 <_ZN14CInventoryMenu11createMenusEv+0x9787>
  b60209:	mov    %rax,%rbx
  b6020c:	nopl   0x0(%rax)
  b60210:	jmp    b6015a <_ZN14CInventoryMenu11createMenusEv+0x977a>
  b60215:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b6021a:	mov    %rax,%rbx
  b6021d:	nopl   (%rax)
  b60220:	jmp    b5fea1 <_ZN14CInventoryMenu11createMenusEv+0x94c1>
  b60225:	lea    0x2090(%rsp),%rdi
  b6022d:	mov    %rax,%rbx
  b60230:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60235:	jmp    b6013b <_ZN14CInventoryMenu11createMenusEv+0x975b>
  b6023a:	mov    $0x5541c8,%eax
  b6023f:	test   %rax,%rax
  b60242:	je     b6030c <_ZN14CInventoryMenu11createMenusEv+0x992c>
  b60248:	or     $0xffffffff,%eax
  b6024b:	lock xadd %eax,0x10(%rdi)
  b60250:	test   %eax,%eax
  b60252:	jg     b5aab6 <_ZN14CInventoryMenu11createMenusEv+0x40d6>
  b60258:	lea    0x44b2(%rsp),%rsi
  b60260:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60265:	jmp    b5aab6 <_ZN14CInventoryMenu11createMenusEv+0x40d6>
  b6026a:	mov    %r14,%rdi
  b6026d:	mov    %rax,%rbx
  b60270:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b60275:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b6027a:	mov    $0x5541c8,%eax
  b6027f:	test   %rax,%rax
  b60282:	je     b602ab <_ZN14CInventoryMenu11createMenusEv+0x98cb>
  b60284:	or     $0xffffffff,%eax
  b60287:	lock xadd %eax,0x10(%rdi)
  b6028c:	test   %eax,%eax
  b6028e:	jg     b5a63f <_ZN14CInventoryMenu11createMenusEv+0x3c5f>
  b60294:	lea    0x44b5(%rsp),%rsi
  b6029c:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b602a1:	jmp    b5a63f <_ZN14CInventoryMenu11createMenusEv+0x3c5f>
  b602a6:	jmp    b5f406 <_ZN14CInventoryMenu11createMenusEv+0x8a26>
  b602ab:	mov    0x10(%rdi),%eax
  b602ae:	lea    -0x1(%rax),%edx
  b602b1:	mov    %edx,0x10(%rdi)
  b602b4:	jmp    b6028c <_ZN14CInventoryMenu11createMenusEv+0x98ac>
  b602b6:	mov    %rax,%rbx
  b602b9:	jmp    b60107 <_ZN14CInventoryMenu11createMenusEv+0x9727>
  b602be:	mov    %rax,%rbx
  b602c1:	jmp    b600fa <_ZN14CInventoryMenu11createMenusEv+0x971a>
  b602c6:	lea    0x22a0(%rsp),%rdi
  b602ce:	mov    %rax,%rbx
  b602d1:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b602d6:	jmp    b60095 <_ZN14CInventoryMenu11createMenusEv+0x96b5>
  b602db:	mov    $0x5541c8,%eax
  b602e0:	test   %rax,%rax
  b602e3:	je     b6031a <_ZN14CInventoryMenu11createMenusEv+0x993a>
  b602e5:	or     $0xffffffff,%eax
  b602e8:	lock xadd %eax,0x10(%rdi)
  b602ed:	test   %eax,%eax
  b602ef:	jg     b5a625 <_ZN14CInventoryMenu11createMenusEv+0x3c45>
  b602f5:	lea    0x44b6(%rsp),%rsi
  b602fd:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60302:	jmp    b5a625 <_ZN14CInventoryMenu11createMenusEv+0x3c45>
  b60307:	jmp    b5fe12 <_ZN14CInventoryMenu11createMenusEv+0x9432>
  b6030c:	mov    0x10(%rdi),%eax
  b6030f:	lea    -0x1(%rax),%edx
  b60312:	mov    %edx,0x10(%rdi)
  b60315:	jmp    b60250 <_ZN14CInventoryMenu11createMenusEv+0x9870>
  b6031a:	mov    0x10(%rdi),%eax
  b6031d:	lea    -0x1(%rax),%edx
  b60320:	mov    %edx,0x10(%rdi)
  b60323:	jmp    b602ed <_ZN14CInventoryMenu11createMenusEv+0x990d>
  b60325:	mov    %rax,%rbx
  b60328:	jmp    b600af <_ZN14CInventoryMenu11createMenusEv+0x96cf>
  b6032d:	mov    %rax,%rbx
  b60330:	jmp    b600a2 <_ZN14CInventoryMenu11createMenusEv+0x96c2>
  b60335:	mov    $0x5541c8,%eax
  b6033a:	test   %rax,%rax
  b6033d:	je     b6038d <_ZN14CInventoryMenu11createMenusEv+0x99ad>
  b6033f:	or     $0xffffffff,%eax
  b60342:	lock xadd %eax,0x10(%rdi)
  b60347:	test   %eax,%eax
  b60349:	jg     b5af46 <_ZN14CInventoryMenu11createMenusEv+0x4566>
  b6034f:	lea    0x44ae(%rsp),%rsi
  b60357:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b6035c:	jmp    b5af46 <_ZN14CInventoryMenu11createMenusEv+0x4566>
  b60361:	mov    $0x5541c8,%eax
  b60366:	test   %rax,%rax
  b60369:	je     b60398 <_ZN14CInventoryMenu11createMenusEv+0x99b8>
  b6036b:	or     $0xffffffff,%eax
  b6036e:	lock xadd %eax,0x10(%rdi)
  b60373:	test   %eax,%eax
  b60375:	jg     b5af60 <_ZN14CInventoryMenu11createMenusEv+0x4580>
  b6037b:	lea    0x44ad(%rsp),%rsi
  b60383:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60388:	jmp    b5af60 <_ZN14CInventoryMenu11createMenusEv+0x4580>
  b6038d:	mov    0x10(%rdi),%eax
  b60390:	lea    -0x1(%rax),%edx
  b60393:	mov    %edx,0x10(%rdi)
  b60396:	jmp    b60347 <_ZN14CInventoryMenu11createMenusEv+0x9967>
  b60398:	mov    0x10(%rdi),%eax
  b6039b:	lea    -0x1(%rax),%edx
  b6039e:	mov    %edx,0x10(%rdi)
  b603a1:	jmp    b60373 <_ZN14CInventoryMenu11createMenusEv+0x9993>
  b603a3:	lea    0x1e80(%rsp),%rdi
  b603ab:	mov    %rax,%rbx
  b603ae:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b603b3:	jmp    b6014d <_ZN14CInventoryMenu11createMenusEv+0x976d>
  b603b8:	mov    $0x5541c8,%eax
  b603bd:	test   %rax,%rax
  b603c0:	je     b60405 <_ZN14CInventoryMenu11createMenusEv+0x9a25>
  b603c2:	or     $0xffffffff,%eax
  b603c5:	lock xadd %eax,0x10(%rdi)
  b603ca:	test   %eax,%eax
  b603cc:	jg     b5ed0e <_ZN14CInventoryMenu11createMenusEv+0x832e>
  b603d2:	lea    0x44b9(%rsp),%rsi
  b603da:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b603df:	jmp    b5ed0e <_ZN14CInventoryMenu11createMenusEv+0x832e>
  b603e4:	mov    %r12,%rdi
  b603e7:	mov    %rax,%rbx
  b603ea:	call   5552b8 <__cxa_free_exception@plt>
  b603ef:	mov    %rbp,%rdi
  b603f2:	call   556288 <_ZNSsD1Ev@plt>
  b603f7:	jmp    b6011c <_ZN14CInventoryMenu11createMenusEv+0x973c>
  b603fc:	nopl   0x0(%rax)
  b60400:	jmp    b60119 <_ZN14CInventoryMenu11createMenusEv+0x9739>
  b60405:	mov    0x10(%rdi),%eax
  b60408:	lea    -0x1(%rax),%edx
  b6040b:	mov    %edx,0x10(%rdi)
  b6040e:	xchg   %ax,%ax
  b60410:	jmp    b603ca <_ZN14CInventoryMenu11createMenusEv+0x99ea>
  b60412:	cmp    $0xffffffffffffffff,%rdx
  b60416:	mov    %rax,%rbx
  b60419:	jne    b6011c <_ZN14CInventoryMenu11createMenusEv+0x973c>
  b6041f:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b60424:	mov    $0x5541c8,%eax
  b60429:	test   %rax,%rax
  b6042c:	je     b60468 <_ZN14CInventoryMenu11createMenusEv+0x9a88>
  b6042e:	or     $0xffffffff,%eax
  b60431:	lock xadd %eax,0x10(%rdi)
  b60436:	test   %eax,%eax
  b60438:	jg     b5ecae <_ZN14CInventoryMenu11createMenusEv+0x82ce>
  b6043e:	lea    0x44af(%rsp),%rsi
  b60446:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b6044b:	jmp    b5ecae <_ZN14CInventoryMenu11createMenusEv+0x82ce>
  b60450:	mov    %r12,%rdi
  b60453:	mov    %rax,%rbx
  b60456:	call   5552b8 <__cxa_free_exception@plt>
  b6045b:	mov    %rbp,%rdi
  b6045e:	call   556288 <_ZNSsD1Ev@plt>
  b60463:	jmp    b6014d <_ZN14CInventoryMenu11createMenusEv+0x976d>
  b60468:	mov    0x10(%rdi),%eax
  b6046b:	lea    -0x1(%rax),%edx
  b6046e:	mov    %edx,0x10(%rdi)
  b60471:	jmp    b60436 <_ZN14CInventoryMenu11createMenusEv+0x9a56>
  b60473:	cmp    $0xffffffffffffffff,%rdx
  b60477:	mov    %rax,%rbx
  b6047a:	jne    b6014d <_ZN14CInventoryMenu11createMenusEv+0x976d>
  b60480:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b60485:	jmp    b6014a <_ZN14CInventoryMenu11createMenusEv+0x976a>
  b6048a:	mov    $0x5541c8,%eax
  b6048f:	test   %rax,%rax
  b60492:	je     b6053f <_ZN14CInventoryMenu11createMenusEv+0x9b5f>
  b60498:	or     $0xffffffff,%eax
  b6049b:	lock xadd %eax,0x10(%rdi)
  b604a0:	test   %eax,%eax
  b604a2:	jg     b5ec34 <_ZN14CInventoryMenu11createMenusEv+0x8254>
  b604a8:	lea    0x44bb(%rsp),%rsi
  b604b0:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b604b5:	jmp    b5ec34 <_ZN14CInventoryMenu11createMenusEv+0x8254>
  b604ba:	mov    %r12,%rdi
  b604bd:	mov    %rax,%rbx
  b604c0:	call   5552b8 <__cxa_free_exception@plt>
  b604c5:	mov    %rbp,%rdi
  b604c8:	call   556288 <_ZNSsD1Ev@plt>
  b604cd:	jmp    b600d8 <_ZN14CInventoryMenu11createMenusEv+0x96f8>
  b604d2:	mov    $0x5541c8,%eax
  b604d7:	test   %rax,%rax
  b604da:	je     b6054d <_ZN14CInventoryMenu11createMenusEv+0x9b6d>
  b604dc:	or     $0xffffffff,%eax
  b604df:	lock xadd %eax,0x10(%rdi)
  b604e4:	test   %eax,%eax
  b604e6:	jg     b5ebd4 <_ZN14CInventoryMenu11createMenusEv+0x81f4>
  b604ec:	lea    0x44b3(%rsp),%rsi
  b604f4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b604f9:	jmp    b5ebd4 <_ZN14CInventoryMenu11createMenusEv+0x81f4>
  b604fe:	jmp    b600d5 <_ZN14CInventoryMenu11createMenusEv+0x96f5>
  b60503:	mov    %r12,%rdi
  b60506:	mov    %rax,%rbx
  b60509:	call   5552b8 <__cxa_free_exception@plt>
  b6050e:	mov    %rbp,%rdi
  b60511:	call   556288 <_ZNSsD1Ev@plt>
  b60516:	jmp    b6013b <_ZN14CInventoryMenu11createMenusEv+0x975b>
  b6051b:	cmp    $0xffffffffffffffff,%rdx
  b6051f:	mov    %rax,%rbx
  b60522:	jne    b600d8 <_ZN14CInventoryMenu11createMenusEv+0x96f8>
  b60528:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b6052d:	cmp    $0xffffffffffffffff,%rdx
  b60531:	mov    %rax,%rbx
  b60534:	jne    b6013b <_ZN14CInventoryMenu11createMenusEv+0x975b>
  b6053a:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b6053f:	mov    0x10(%rdi),%eax
  b60542:	lea    -0x1(%rax),%edx
  b60545:	mov    %edx,0x10(%rdi)
  b60548:	jmp    b604a0 <_ZN14CInventoryMenu11createMenusEv+0x9ac0>
  b6054d:	mov    0x10(%rdi),%eax
  b60550:	lea    -0x1(%rax),%edx
  b60553:	mov    %edx,0x10(%rdi)
  b60556:	jmp    b604e4 <_ZN14CInventoryMenu11createMenusEv+0x9b04>
  b60558:	jmp    b60138 <_ZN14CInventoryMenu11createMenusEv+0x9758>
  b6055d:	mov    $0x5541c8,%eax
  b60562:	test   %rax,%rax
  b60565:	je     b605a6 <_ZN14CInventoryMenu11createMenusEv+0x9bc6>
  b60567:	or     $0xffffffff,%eax
  b6056a:	lock xadd %eax,0x10(%rdi)
  b6056f:	test   %eax,%eax
  b60571:	jg     b5eb0e <_ZN14CInventoryMenu11createMenusEv+0x812e>
  b60577:	lea    0x44bd(%rsp),%rsi
  b6057f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60584:	jmp    b5eb0e <_ZN14CInventoryMenu11createMenusEv+0x812e>
  b60589:	mov    %r12,%rdi
  b6058c:	mov    %rax,%rbx
  b6058f:	call   5552b8 <__cxa_free_exception@plt>
  b60594:	mov    %rbp,%rdi
  b60597:	call   556288 <_ZNSsD1Ev@plt>
  b6059c:	jmp    b6002d <_ZN14CInventoryMenu11createMenusEv+0x964d>
  b605a1:	jmp    b6002a <_ZN14CInventoryMenu11createMenusEv+0x964a>
  b605a6:	mov    0x10(%rdi),%eax
  b605a9:	lea    -0x1(%rax),%edx
  b605ac:	mov    %edx,0x10(%rdi)
  b605af:	nop
  b605b0:	jmp    b6056f <_ZN14CInventoryMenu11createMenusEv+0x9b8f>
  b605b2:	cmp    $0xffffffffffffffff,%rdx
  b605b6:	mov    %rax,%rbx
  b605b9:	jne    b6002d <_ZN14CInventoryMenu11createMenusEv+0x964d>
  b605bf:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b605c4:	mov    $0x5541c8,%eax
  b605c9:	test   %rax,%rax
  b605cc:	je     b60608 <_ZN14CInventoryMenu11createMenusEv+0x9c28>
  b605ce:	or     $0xffffffff,%eax
  b605d1:	lock xadd %eax,0x10(%rdi)
  b605d6:	test   %eax,%eax
  b605d8:	jg     b5eaae <_ZN14CInventoryMenu11createMenusEv+0x80ce>
  b605de:	lea    0x44b7(%rsp),%rsi
  b605e6:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b605eb:	jmp    b5eaae <_ZN14CInventoryMenu11createMenusEv+0x80ce>
  b605f0:	mov    %r12,%rdi
  b605f3:	mov    %rax,%rbx
  b605f6:	call   5552b8 <__cxa_free_exception@plt>
  b605fb:	mov    %rbp,%rdi
  b605fe:	call   556288 <_ZNSsD1Ev@plt>
  b60603:	jmp    b60095 <_ZN14CInventoryMenu11createMenusEv+0x96b5>
  b60608:	mov    0x10(%rdi),%eax
  b6060b:	lea    -0x1(%rax),%edx
  b6060e:	mov    %edx,0x10(%rdi)
  b60611:	jmp    b605d6 <_ZN14CInventoryMenu11createMenusEv+0x9bf6>
  b60613:	cmp    $0xffffffffffffffff,%rdx
  b60617:	mov    %rax,%rbx
  b6061a:	jne    b60095 <_ZN14CInventoryMenu11createMenusEv+0x96b5>
  b60620:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b60625:	jmp    b60092 <_ZN14CInventoryMenu11createMenusEv+0x96b2>
  b6062a:	mov    $0x5541c8,%eax
  b6062f:	test   %rax,%rax
  b60632:	je     b606de <_ZN14CInventoryMenu11createMenusEv+0x9cfe>
  b60638:	or     $0xffffffff,%eax
  b6063b:	lock xadd %eax,0x10(%rdi)
  b60640:	test   %eax,%eax
  b60642:	jg     b5e9f3 <_ZN14CInventoryMenu11createMenusEv+0x8013>
  b60648:	lea    0x44c0(%rsp),%rsi
  b60650:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60655:	jmp    b5e9f3 <_ZN14CInventoryMenu11createMenusEv+0x8013>
  b6065a:	mov    %r12,%rdi
  b6065d:	mov    %rax,%rbx
  b60660:	call   5552b8 <__cxa_free_exception@plt>
  b60665:	mov    %rbp,%rdi
  b60668:	call   556288 <_ZNSsD1Ev@plt>
  b6066d:	jmp    b5fe99 <_ZN14CInventoryMenu11createMenusEv+0x94b9>
  b60672:	jmp    b6021a <_ZN14CInventoryMenu11createMenusEv+0x983a>
  b60677:	mov    $0x5541c8,%eax
  b6067c:	test   %rax,%rax
  b6067f:	nop
  b60680:	je     b606bc <_ZN14CInventoryMenu11createMenusEv+0x9cdc>
  b60682:	or     $0xffffffff,%eax
  b60685:	lock xadd %eax,0x10(%rdi)
  b6068a:	test   %eax,%eax
  b6068c:	jg     b5e8d6 <_ZN14CInventoryMenu11createMenusEv+0x7ef6>
  b60692:	lea    0x44c2(%rsp),%rsi
  b6069a:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b6069f:	jmp    b5e8d6 <_ZN14CInventoryMenu11createMenusEv+0x7ef6>
  b606a4:	mov    %r12,%rdi
  b606a7:	mov    %rax,%rbx
  b606aa:	call   5552b8 <__cxa_free_exception@plt>
  b606af:	mov    %rbp,%rdi
  b606b2:	call   556288 <_ZNSsD1Ev@plt>
  b606b7:	jmp    b5fea1 <_ZN14CInventoryMenu11createMenusEv+0x94c1>
  b606bc:	mov    0x10(%rdi),%eax
  b606bf:	lea    -0x1(%rax),%edx
  b606c2:	mov    %edx,0x10(%rdi)
  b606c5:	jmp    b6068a <_ZN14CInventoryMenu11createMenusEv+0x9caa>
  b606c7:	cmp    $0xffffffffffffffff,%rdx
  b606cb:	mov    %rax,%rbx
  b606ce:	jne    b5fea1 <_ZN14CInventoryMenu11createMenusEv+0x94c1>
  b606d4:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b606d9:	jmp    b5fe96 <_ZN14CInventoryMenu11createMenusEv+0x94b6>
  b606de:	mov    0x10(%rdi),%eax
  b606e1:	lea    -0x1(%rax),%edx
  b606e4:	mov    %edx,0x10(%rdi)
  b606e7:	jmp    b60640 <_ZN14CInventoryMenu11createMenusEv+0x9c60>
  b606ec:	mov    %r12,%rdi
  b606ef:	mov    %rax,%rbx
  b606f2:	call   5552b8 <__cxa_free_exception@plt>
  b606f7:	mov    %rbp,%rdi
  b606fa:	call   556288 <_ZNSsD1Ev@plt>
  b606ff:	jmp    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b60704:	jmp    b5fe12 <_ZN14CInventoryMenu11createMenusEv+0x9432>
  b60709:	cmp    $0xffffffffffffffff,%rdx
  b6070d:	mov    %rax,%rbx
  b60710:	jne    b5f3e1 <_ZN14CInventoryMenu11createMenusEv+0x8a01>
  b60716:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b6071b:	mov    $0x5541c8,%eax
  b60720:	test   %rax,%rax
  b60723:	je     b60759 <_ZN14CInventoryMenu11createMenusEv+0x9d79>
  b60725:	or     $0xffffffff,%eax
  b60728:	lock xadd %eax,0x10(%rdi)
  b6072d:	test   %eax,%eax
  b6072f:	jg     b5e814 <_ZN14CInventoryMenu11createMenusEv+0x7e34>
  b60735:	lea    0x44c4(%rsp),%rsi
  b6073d:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  b60742:	jmp    b5e814 <_ZN14CInventoryMenu11createMenusEv+0x7e34>
  b60747:	cmp    $0xffffffffffffffff,%rdx
  b6074b:	mov    %rax,%rbx
  b6074e:	jne    b5fe99 <_ZN14CInventoryMenu11createMenusEv+0x94b9>
  b60754:	jmp    b5f82f <_ZN14CInventoryMenu11createMenusEv+0x8e4f>
  b60759:	mov    0x10(%rdi),%eax
  b6075c:	lea    -0x1(%rax),%edx
  b6075f:	mov    %edx,0x10(%rdi)
  b60762:	jmp    b6072d <_ZN14CInventoryMenu11createMenusEv+0x9d4d>
  b60764:	data16 data16 cs nopw 0x0(%rax,%rax,1)

