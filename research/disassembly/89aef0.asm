
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000089aef0 <CGenericModel::setAmbient(Ogre::ColourValue&)>:
  89aef0:	41 55                	push   %r13
  89aef2:	49 89 f5             	mov    %rsi,%r13
  89aef5:	41 54                	push   %r12
  89aef7:	49 89 fc             	mov    %rdi,%r12
  89aefa:	55                   	push   %rbp
  89aefb:	53                   	push   %rbx
  89aefc:	48 83 ec 08          	sub    $0x8,%rsp
  89af00:	48 8b 97 08 02 00 00 	mov    0x208(%rdi),%rdx
  89af07:	48 8b 87 10 02 00 00 	mov    0x210(%rdi),%rax
  89af0e:	48 29 d0             	sub    %rdx,%rax
  89af11:	48 c1 e8 06          	shr    $0x6,%rax
  89af15:	85 c0                	test   %eax,%eax
  89af17:	74 46                	je     89af5f <CGenericModel::setAmbient(Ogre::ColourValue&)+0x6f>
  89af19:	31 db                	xor    %ebx,%ebx
  89af1b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  89af20:	89 d8                	mov    %ebx,%eax
  89af22:	4c 89 ee             	mov    %r13,%rsi
  89af25:	83 c3 01             	add    $0x1,%ebx
  89af28:	48 c1 e0 06          	shl    $0x6,%rax
  89af2c:	48 8b 6c 10 10       	mov    0x10(%rax,%rdx,1),%rbp
  89af31:	48 89 ef             	mov    %rbp,%rdi
  89af34:	e8 2f a8 cb ff       	call   555768 <Ogre::Material::setAmbient(Ogre::ColourValue const&)@plt>
  89af39:	4c 89 ee             	mov    %r13,%rsi
  89af3c:	48 89 ef             	mov    %rbp,%rdi
  89af3f:	e8 c4 a0 cb ff       	call   555008 <Ogre::Material::setDiffuse(Ogre::ColourValue const&)@plt>
  89af44:	49 8b 94 24 08 02 00 	mov    0x208(%r12),%rdx
  89af4b:	00 
  89af4c:	49 8b 84 24 10 02 00 	mov    0x210(%r12),%rax
  89af53:	00 
  89af54:	48 29 d0             	sub    %rdx,%rax
  89af57:	48 c1 f8 06          	sar    $0x6,%rax
  89af5b:	39 c3                	cmp    %eax,%ebx
  89af5d:	72 c1                	jb     89af20 <CGenericModel::setAmbient(Ogre::ColourValue&)+0x30>
  89af5f:	48 83 c4 08          	add    $0x8,%rsp
  89af63:	5b                   	pop    %rbx
  89af64:	5d                   	pop    %rbp
  89af65:	41 5c                	pop    %r12
  89af67:	41 5d                	pop    %r13
  89af69:	c3                   	ret
