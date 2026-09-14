
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a0aeb0 <CUnitSpawner::hideAndDisableUnits(bool)>:
  a0aeb0:	41 56                	push   %r14
  a0aeb2:	41 89 f6             	mov    %esi,%r14d
  a0aeb5:	41 55                	push   %r13
  a0aeb7:	41 54                	push   %r12
  a0aeb9:	55                   	push   %rbp
  a0aeba:	53                   	push   %rbx
  a0aebb:	8b 97 08 02 00 00    	mov    0x208(%rdi),%edx
  a0aec1:	48 89 fb             	mov    %rdi,%rbx
  a0aec4:	85 d2                	test   %edx,%edx
  a0aec6:	74 70                	je     a0af38 <CUnitSpawner::hideAndDisableUnits(bool)+0x88>
  a0aec8:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  a0aece:	31 ed                	xor    %ebp,%ebp
  a0aed0:	45 31 f5             	xor    %r14d,%r13d
  a0aed3:	45 0f b6 ed          	movzbl %r13b,%r13d
  a0aed7:	eb 41                	jmp    a0af1a <CUnitSpawner::hideAndDisableUnits(bool)+0x6a>
  a0aed9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  a0aee0:	48 8b 83 00 02 00 00 	mov    0x200(%rbx),%rax
  a0aee7:	48 8b 00             	mov    (%rax),%rax
  a0aeea:	4c 8b 20             	mov    (%rax),%r12
  a0aeed:	4d 85 e4             	test   %r12,%r12
  a0aef0:	74 1d                	je     a0af0f <CUnitSpawner::hideAndDisableUnits(bool)+0x5f>
  a0aef2:	49 8b 04 24          	mov    (%r12),%rax
  a0aef6:	44 89 ee             	mov    %r13d,%esi
  a0aef9:	4c 89 e7             	mov    %r12,%rdi
  a0aefc:	ff 50 40             	call   *0x40(%rax)
  a0aeff:	ba 01 00 00 00       	mov    $0x1,%edx
  a0af04:	44 89 ee             	mov    %r13d,%esi
  a0af07:	4c 89 e7             	mov    %r12,%rdi
  a0af0a:	e8 41 7a e0 ff       	call   812950 <CCharacter::setVisible(bool, bool)>
  a0af0f:	83 c5 01             	add    $0x1,%ebp
  a0af12:	3b ab 08 02 00 00    	cmp    0x208(%rbx),%ebp
  a0af18:	73 1e                	jae    a0af38 <CUnitSpawner::hideAndDisableUnits(bool)+0x88>
  a0af1a:	39 ab 0c 02 00 00    	cmp    %ebp,0x20c(%rbx)
  a0af20:	76 be                	jbe    a0aee0 <CUnitSpawner::hideAndDisableUnits(bool)+0x30>
  a0af22:	89 e8                	mov    %ebp,%eax
  a0af24:	48 c1 e0 03          	shl    $0x3,%rax
  a0af28:	48 03 83 00 02 00 00 	add    0x200(%rbx),%rax
  a0af2f:	eb b6                	jmp    a0aee7 <CUnitSpawner::hideAndDisableUnits(bool)+0x37>
  a0af31:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  a0af38:	8b 83 d8 01 00 00    	mov    0x1d8(%rbx),%eax
  a0af3e:	85 c0                	test   %eax,%eax
  a0af40:	0f 84 94 00 00 00    	je     a0afda <CUnitSpawner::hideAndDisableUnits(bool)+0x12a>
  a0af46:	31 ed                	xor    %ebp,%ebp
  a0af48:	eb 48                	jmp    a0af92 <CUnitSpawner::hideAndDisableUnits(bool)+0xe2>
  a0af4a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  a0af50:	39 ab dc 01 00 00    	cmp    %ebp,0x1dc(%rbx)
  a0af56:	0f 87 a4 00 00 00    	ja     a0b000 <CUnitSpawner::hideAndDisableUnits(bool)+0x150>
  a0af5c:	48 8b 83 d0 01 00 00 	mov    0x1d0(%rbx),%rax
  a0af63:	48 8b 38             	mov    (%rax),%rdi
  a0af66:	31 f6                	xor    %esi,%esi
  a0af68:	e8 33 33 fd ff       	call   9de2a0 <CLayout::stop(bool)>
  a0af6d:	39 ab dc 01 00 00    	cmp    %ebp,0x1dc(%rbx)
  a0af73:	77 73                	ja     a0afe8 <CUnitSpawner::hideAndDisableUnits(bool)+0x138>
  a0af75:	48 8b 83 d0 01 00 00 	mov    0x1d0(%rbx),%rax
  a0af7c:	48 8b 38             	mov    (%rax),%rdi
  a0af7f:	31 f6                	xor    %esi,%esi
  a0af81:	83 c5 01             	add    $0x1,%ebp
  a0af84:	48 8b 07             	mov    (%rdi),%rax
  a0af87:	ff 50 50             	call   *0x50(%rax)
  a0af8a:	3b ab d8 01 00 00    	cmp    0x1d8(%rbx),%ebp
  a0af90:	73 48                	jae    a0afda <CUnitSpawner::hideAndDisableUnits(bool)+0x12a>
  a0af92:	45 84 f6             	test   %r14b,%r14b
  a0af95:	75 b9                	jne    a0af50 <CUnitSpawner::hideAndDisableUnits(bool)+0xa0>
  a0af97:	39 ab dc 01 00 00    	cmp    %ebp,0x1dc(%rbx)
  a0af9d:	0f 87 8d 00 00 00    	ja     a0b030 <CUnitSpawner::hideAndDisableUnits(bool)+0x180>
  a0afa3:	48 8b 83 d0 01 00 00 	mov    0x1d0(%rbx),%rax
  a0afaa:	48 8b 38             	mov    (%rax),%rdi
  a0afad:	e8 0e 33 fd ff       	call   9de2c0 <CLayout::start()>
  a0afb2:	39 ab dc 01 00 00    	cmp    %ebp,0x1dc(%rbx)
  a0afb8:	77 5e                	ja     a0b018 <CUnitSpawner::hideAndDisableUnits(bool)+0x168>
  a0afba:	48 8b 83 d0 01 00 00 	mov    0x1d0(%rbx),%rax
  a0afc1:	48 8b 38             	mov    (%rax),%rdi
  a0afc4:	be 01 00 00 00       	mov    $0x1,%esi
  a0afc9:	83 c5 01             	add    $0x1,%ebp
  a0afcc:	48 8b 07             	mov    (%rdi),%rax
  a0afcf:	ff 50 50             	call   *0x50(%rax)
  a0afd2:	3b ab d8 01 00 00    	cmp    0x1d8(%rbx),%ebp
  a0afd8:	72 b8                	jb     a0af92 <CUnitSpawner::hideAndDisableUnits(bool)+0xe2>
  a0afda:	5b                   	pop    %rbx
  a0afdb:	5d                   	pop    %rbp
  a0afdc:	41 5c                	pop    %r12
  a0afde:	41 5d                	pop    %r13
  a0afe0:	41 5e                	pop    %r14
  a0afe2:	c3                   	ret
  a0afe3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  a0afe8:	89 e8                	mov    %ebp,%eax
  a0afea:	48 c1 e0 03          	shl    $0x3,%rax
  a0afee:	48 03 83 d0 01 00 00 	add    0x1d0(%rbx),%rax
  a0aff5:	eb 85                	jmp    a0af7c <CUnitSpawner::hideAndDisableUnits(bool)+0xcc>
  a0aff7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  a0affe:	00 00
  a0b000:	89 e8                	mov    %ebp,%eax
  a0b002:	48 c1 e0 03          	shl    $0x3,%rax
  a0b006:	48 03 83 d0 01 00 00 	add    0x1d0(%rbx),%rax
  a0b00d:	e9 51 ff ff ff       	jmp    a0af63 <CUnitSpawner::hideAndDisableUnits(bool)+0xb3>
  a0b012:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  a0b018:	89 e8                	mov    %ebp,%eax
  a0b01a:	48 c1 e0 03          	shl    $0x3,%rax
  a0b01e:	48 03 83 d0 01 00 00 	add    0x1d0(%rbx),%rax
  a0b025:	eb 9a                	jmp    a0afc1 <CUnitSpawner::hideAndDisableUnits(bool)+0x111>
  a0b027:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  a0b02e:	00 00
  a0b030:	89 e8                	mov    %ebp,%eax
  a0b032:	48 c1 e0 03          	shl    $0x3,%rax
  a0b036:	48 03 83 d0 01 00 00 	add    0x1d0(%rbx),%rax
  a0b03d:	e9 68 ff ff ff       	jmp    a0afaa <CUnitSpawner::hideAndDisableUnits(bool)+0xfa>
