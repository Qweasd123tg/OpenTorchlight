
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000848790 <CCharacter::updateAttack(CLevel&)>:
  848790:	push   %rbp
  848791:	mov    %rdi,%rbp
  848794:	push   %rbx
  848795:	sub    $0x8,%rsp
  848799:	cmpq   $0x0,0x390(%rdi)
  8487a1:	je     848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  8487a7:	movss  0x378(%rdi),%xmm0
  8487af:	ucomiss 0x75c042(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  8487b6:	jbe    848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  8487bc:	mov    0x330(%rdi),%eax
  8487c2:	cmp    $0x5,%eax
  8487c5:	je     848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  8487cb:	cmp    $0x6,%eax
  8487ce:	je     848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  8487d4:	mov    0x200(%rdi),%rcx
  8487db:	mov    0x1b0(%rcx),%rdx
  8487e2:	mov    0x1b8(%rcx),%rax
  8487e9:	sub    %rdx,%rax
  8487ec:	shr    $0x3,%rax
  8487f0:	test   %eax,%eax
  8487f2:	je     848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  8487f4:	xor    %ebx,%ebx
  8487f6:	jmp    84881c <CCharacter::updateAttack(CLevel&)+0x8c>
  8487f8:	nopl   0x0(%rax,%rax,1)
  848800:	mov    0x1b0(%rcx),%rdx
  848807:	mov    0x1b8(%rcx),%rax
  84880e:	add    $0x1,%ebx
  848811:	sub    %rdx,%rax
  848814:	sar    $0x3,%rax
  848818:	cmp    %eax,%ebx
  84881a:	jae    848860 <CCharacter::updateAttack(CLevel&)+0xd0>
  84881c:	mov    %ebx,%eax
  84881e:	mov    (%rdx,%rax,8),%rax
  848822:	mov    0x58(%rax),%r9d
  848826:	test   %r9d,%r9d
  848829:	jne    848800 <CCharacter::updateAttack(CLevel&)+0x70>
  84882b:	movss  0x75bfc9(%rip),%xmm1        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  848833:	mov    $0x7,%ecx
  848838:	movaps %xmm1,%xmm0
  84883b:	movb   $0x1,0x37c(%rbp)
  848842:	xor    %edx,%edx
  848844:	xor    %esi,%esi
  848846:	mov    %rbp,%rdi
  848849:	call   847280 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)>
  84884e:	mov    0x200(%rbp),%rcx
  848855:	jmp    848800 <CCharacter::updateAttack(CLevel&)+0x70>
  848857:	nopw   0x0(%rax,%rax,1)
  848860:	add    $0x8,%rsp
  848864:	pop    %rbx
  848865:	pop    %rbp
  848866:	ret
