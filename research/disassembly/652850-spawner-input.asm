
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000652850 <CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)>:
  652850:	48 85 f6             	test   %rsi,%rsi
  652853:	53                   	push   %rbx
  652854:	48 89 f7             	mov    %rsi,%rdi
  652857:	89 d3                	mov    %edx,%ebx
  652859:	74 1e                	je     652879 <CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)+0x29>
  65285b:	31 c9                	xor    %ecx,%ecx
  65285d:	ba 00 b2 fd 00       	mov    $0xfdb200,%edx
  652862:	be 10 46 fc 00       	mov    $0xfc4610,%esi
  652867:	e8 ec 2e f0 ff       	call   555758 <__dynamic_cast@plt>
  65286c:	48 85 c0             	test   %rax,%rax
  65286f:	74 08                	je     652879 <CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)+0x29>
  652871:	83 eb 0a             	sub    $0xa,%ebx
  652874:	83 fb 1a             	cmp    $0x1a,%ebx
  652877:	76 07                	jbe    652880 <CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)+0x30>
  652879:	5b                   	pop    %rbx
  65287a:	c3                   	ret
  65287b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  652880:	89 db                	mov    %ebx,%ebx
  652882:	ff 24 dd b8 6a fb 00 	jmp    *0xfb6ab8(,%rbx,8)
  652889:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  652890:	83 a8 a4 01 00 00 01 	subl   $0x1,0x1a4(%rax)
  652897:	5b                   	pop    %rbx
  652898:	c3                   	ret
  652899:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  6528a0:	83 80 a4 01 00 00 01 	addl   $0x1,0x1a4(%rax)
  6528a7:	5b                   	pop    %rbx
  6528a8:	c3                   	ret
  6528a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  6528b0:	5b                   	pop    %rbx
  6528b1:	be 01 00 00 00       	mov    $0x1,%esi
  6528b6:	48 89 c7             	mov    %rax,%rdi
  6528b9:	e9 f2 85 3b 00       	jmp    a0aeb0 <CUnitSpawner::hideAndDisableUnits(bool)>
  6528be:	66 90                	xchg   %ax,%ax
  6528c0:	5b                   	pop    %rbx
  6528c1:	48 89 c7             	mov    %rax,%rdi
  6528c4:	e9 27 1f 3c 00       	jmp    a147f0 <CUnitSpawner::destroyUnits()>
  6528c9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  6528d0:	5b                   	pop    %rbx
  6528d1:	48 89 c7             	mov    %rax,%rdi
  6528d4:	e9 a7 4e 3c 00       	jmp    a17780 <CUnitSpawner::spawn()>
  6528d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  6528e0:	5b                   	pop    %rbx
  6528e1:	48 89 c7             	mov    %rax,%rdi
  6528e4:	e9 d7 7c 3b 00       	jmp    a0a5c0 <CUnitSpawner::stop()>
