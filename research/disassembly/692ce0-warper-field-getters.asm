
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000692ce0 <CWarperDescriptor::Get_getWarpName(CEditorBaseObject*, unsigned int&)>:
  692ce0:	48 89 6c 24 f0       	mov    %rbp,-0x10(%rsp)
  692ce5:	48 89 5c 24 e8       	mov    %rbx,-0x18(%rsp)
  692cea:	31 c0                	xor    %eax,%eax
  692cec:	4c 89 64 24 f8       	mov    %r12,-0x8(%rsp)
  692cf1:	48 83 ec 18          	sub    $0x18,%rsp
  692cf5:	48 85 ff             	test   %rdi,%rdi
  692cf8:	48 89 f5             	mov    %rsi,%rbp
  692cfb:	74 1b                	je     692d18 <CWarperDescriptor::Get_getWarpName(CEditorBaseObject*, unsigned int&)+0x38>
  692cfd:	48 8b b7 18 01 00 00 	mov    0x118(%rdi),%rsi
  692d04:	31 db                	xor    %ebx,%ebx
  692d06:	8b 46 e8             	mov    -0x18(%rsi),%eax
  692d09:	3d 3f 42 0f 00       	cmp    $0xf423f,%eax
  692d0e:	76 20                	jbe    692d30 <CWarperDescriptor::Get_getWarpName(CEditorBaseObject*, unsigned int&)+0x50>
  692d10:	89 5d 00             	mov    %ebx,0x0(%rbp)
  692d13:	b8 20 e6 45 01       	mov    $0x145e620,%eax
  692d18:	48 8b 1c 24          	mov    (%rsp),%rbx
  692d1c:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  692d21:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  692d26:	48 83 c4 18          	add    $0x18,%rsp
  692d2a:	c3                   	ret
  692d2b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  692d30:	8d 1c 85 00 00 00 00 	lea    0x0(,%rax,4),%ebx
  692d37:	bf 20 e6 45 01       	mov    $0x145e620,%edi
  692d3c:	41 89 dc             	mov    %ebx,%r12d
  692d3f:	4c 89 e2             	mov    %r12,%rdx
  692d42:	e8 71 2d ec ff       	call   555ab8 <memcpy@plt>
  692d47:	41 c7 84 24 20 e6 45 	movl   $0x0,0x145e620(%r12)
  692d4e:	01 00 00 00 00 
  692d53:	eb bb                	jmp    692d10 <CWarperDescriptor::Get_getWarpName(CEditorBaseObject*, unsigned int&)+0x30>
  692d55:	90                   	nop
  692d56:	90                   	nop
  692d57:	90                   	nop
  692d58:	90                   	nop
  692d59:	90                   	nop
  692d5a:	90                   	nop
  692d5b:	90                   	nop
  692d5c:	90                   	nop
  692d5d:	90                   	nop
  692d5e:	90                   	nop
  692d5f:	90                   	nop

0000000000692d60 <CWarperDescriptor::Get_getDungeon(CEditorBaseObject*, unsigned int&)>:
  692d60:	48 89 6c 24 f0       	mov    %rbp,-0x10(%rsp)
  692d65:	48 89 5c 24 e8       	mov    %rbx,-0x18(%rsp)
  692d6a:	31 c0                	xor    %eax,%eax
  692d6c:	4c 89 64 24 f8       	mov    %r12,-0x8(%rsp)
  692d71:	48 83 ec 18          	sub    $0x18,%rsp
  692d75:	48 85 ff             	test   %rdi,%rdi
  692d78:	48 89 f5             	mov    %rsi,%rbp
  692d7b:	74 1b                	je     692d98 <CWarperDescriptor::Get_getDungeon(CEditorBaseObject*, unsigned int&)+0x38>
  692d7d:	48 8b b7 10 01 00 00 	mov    0x110(%rdi),%rsi
  692d84:	31 db                	xor    %ebx,%ebx
  692d86:	8b 46 e8             	mov    -0x18(%rsi),%eax
  692d89:	3d 3f 42 0f 00       	cmp    $0xf423f,%eax
  692d8e:	76 20                	jbe    692db0 <CWarperDescriptor::Get_getDungeon(CEditorBaseObject*, unsigned int&)+0x50>
  692d90:	89 5d 00             	mov    %ebx,0x0(%rbp)
  692d93:	b8 20 e6 45 01       	mov    $0x145e620,%eax
  692d98:	48 8b 1c 24          	mov    (%rsp),%rbx
  692d9c:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  692da1:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  692da6:	48 83 c4 18          	add    $0x18,%rsp
  692daa:	c3                   	ret
  692dab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  692db0:	8d 1c 85 00 00 00 00 	lea    0x0(,%rax,4),%ebx
  692db7:	bf 20 e6 45 01       	mov    $0x145e620,%edi
  692dbc:	41 89 dc             	mov    %ebx,%r12d
  692dbf:	4c 89 e2             	mov    %r12,%rdx
  692dc2:	e8 f1 2c ec ff       	call   555ab8 <memcpy@plt>
  692dc7:	41 c7 84 24 20 e6 45 	movl   $0x0,0x145e620(%r12)
  692dce:	01 00 00 00 00 
  692dd3:	eb bb                	jmp    692d90 <CWarperDescriptor::Get_getDungeon(CEditorBaseObject*, unsigned int&)+0x30>
