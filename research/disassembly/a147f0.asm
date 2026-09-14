
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a147f0 <CUnitSpawner::destroyUnits()>:
  a147f0:	41 57                	push   %r15
  a147f2:	41 56                	push   %r14
  a147f4:	41 55                	push   %r13
  a147f6:	41 54                	push   %r12
  a147f8:	55                   	push   %rbp
  a147f9:	48 89 fd             	mov    %rdi,%rbp
  a147fc:	53                   	push   %rbx
  a147fd:	48 83 ec 08          	sub    $0x8,%rsp
  a14801:	c6 87 c0 01 00 00 00 	movb   $0x0,0x1c0(%rdi)
  a14808:	c6 87 c1 01 00 00 00 	movb   $0x0,0x1c1(%rdi)
  a1480f:	8b bf 08 02 00 00    	mov    0x208(%rdi),%edi
  a14815:	85 ff                	test   %edi,%edi
  a14817:	74 57                	je     a14870 <CUnitSpawner::destroyUnits()+0x80>
  a14819:	31 db                	xor    %ebx,%ebx
  a1481b:	eb 32                	jmp    a1484f <CUnitSpawner::destroyUnits()+0x5f>
  a1481d:	0f 1f 00             	nopl   (%rax)
  a14820:	48 8b 85 00 02 00 00 	mov    0x200(%rbp),%rax
  a14827:	48 8b 00             	mov    (%rax),%rax
  a1482a:	48 8b 38             	mov    (%rax),%rdi
  a1482d:	48 85 ff             	test   %rdi,%rdi
  a14830:	74 12                	je     a14844 <CUnitSpawner::destroyUnits()+0x54>
  a14832:	48 8b 07             	mov    (%rdi),%rax
  a14835:	31 c9                	xor    %ecx,%ecx
  a14837:	31 d2                	xor    %edx,%edx
  a14839:	0f 57 c0             	xorps  %xmm0,%xmm0
  a1483c:	31 f6                	xor    %esi,%esi
  a1483e:	ff 90 30 03 00 00    	call   *0x330(%rax)
  a14844:	83 c3 01             	add    $0x1,%ebx
  a14847:	3b 9d 08 02 00 00    	cmp    0x208(%rbp),%ebx
  a1484d:	73 21                	jae    a14870 <CUnitSpawner::destroyUnits()+0x80>
  a1484f:	39 9d 0c 02 00 00    	cmp    %ebx,0x20c(%rbp)
  a14855:	76 c9                	jbe    a14820 <CUnitSpawner::destroyUnits()+0x30>
  a14857:	89 d8                	mov    %ebx,%eax
  a14859:	48 c1 e0 03          	shl    $0x3,%rax
  a1485d:	48 03 85 00 02 00 00 	add    0x200(%rbp),%rax
  a14864:	eb c1                	jmp    a14827 <CUnitSpawner::destroyUnits()+0x37>
  a14866:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  a1486d:	00 00 00
  a14870:	8b b5 d8 01 00 00    	mov    0x1d8(%rbp),%esi
  a14876:	85 f6                	test   %esi,%esi
  a14878:	74 66                	je     a148e0 <CUnitSpawner::destroyUnits()+0xf0>
  a1487a:	31 db                	xor    %ebx,%ebx
  a1487c:	eb 38                	jmp    a148b6 <CUnitSpawner::destroyUnits()+0xc6>
  a1487e:	66 90                	xchg   %ax,%ax
  a14880:	48 8b 85 d0 01 00 00 	mov    0x1d0(%rbp),%rax
  a14887:	48 8b 38             	mov    (%rax),%rdi
  a1488a:	31 f6                	xor    %esi,%esi
  a1488c:	e8 0f 9a fc ff       	call   9de2a0 <CLayout::stop(bool)>
  a14891:	39 9d dc 01 00 00    	cmp    %ebx,0x1dc(%rbp)
  a14897:	77 37                	ja     a148d0 <CUnitSpawner::destroyUnits()+0xe0>
  a14899:	48 8b 85 d0 01 00 00 	mov    0x1d0(%rbp),%rax
  a148a0:	48 8b 38             	mov    (%rax),%rdi
  a148a3:	31 f6                	xor    %esi,%esi
  a148a5:	83 c3 01             	add    $0x1,%ebx
  a148a8:	48 8b 07             	mov    (%rdi),%rax
  a148ab:	ff 50 50             	call   *0x50(%rax)
  a148ae:	3b 9d d8 01 00 00    	cmp    0x1d8(%rbp),%ebx
  a148b4:	73 2a                	jae    a148e0 <CUnitSpawner::destroyUnits()+0xf0>
  a148b6:	39 9d dc 01 00 00    	cmp    %ebx,0x1dc(%rbp)
  a148bc:	76 c2                	jbe    a14880 <CUnitSpawner::destroyUnits()+0x90>
  a148be:	89 d8                	mov    %ebx,%eax
  a148c0:	48 c1 e0 03          	shl    $0x3,%rax
  a148c4:	48 03 85 d0 01 00 00 	add    0x1d0(%rbp),%rax
  a148cb:	eb ba                	jmp    a14887 <CUnitSpawner::destroyUnits()+0x97>
  a148cd:	0f 1f 00             	nopl   (%rax)
  a148d0:	89 d8                	mov    %ebx,%eax
  a148d2:	48 c1 e0 03          	shl    $0x3,%rax
  a148d6:	48 03 85 d0 01 00 00 	add    0x1d0(%rbp),%rax
  a148dd:	eb c1                	jmp    a148a0 <CUnitSpawner::destroyUnits()+0xb0>
  a148df:	90                   	nop
  a148e0:	8b 9d 08 02 00 00    	mov    0x208(%rbp),%ebx
  a148e6:	4c 8d a5 00 02 00 00 	lea    0x200(%rbp),%r12
  a148ed:	85 db                	test   %ebx,%ebx
  a148ef:	74 6f                	je     a14960 <CUnitSpawner::destroyUnits()+0x170>
  a148f1:	45 31 ed             	xor    %r13d,%r13d
  a148f4:	0f 1f 40 00          	nopl   0x0(%rax)
  a148f8:	45 89 ee             	mov    %r13d,%r14d
  a148fb:	4e 8d 3c f5 00 00 00 	lea    0x0(,%r14,8),%r15
  a14902:	00
  a14903:	4c 89 f8             	mov    %r15,%rax
  a14906:	49 03 04 24          	add    (%r12),%rax
  a1490a:	48 8b 18             	mov    (%rax),%rbx
  a1490d:	48 85 db             	test   %rbx,%rbx
  a14910:	74 3c                	je     a1494e <CUnitSpawner::destroyUnits()+0x15e>
  a14912:	48 8b 3b             	mov    (%rbx),%rdi
  a14915:	48 85 ff             	test   %rdi,%rdi
  a14918:	74 0b                	je     a14925 <CUnitSpawner::destroyUnits()+0x135>
  a1491a:	8b 53 08             	mov    0x8(%rbx),%edx
  a1491d:	48 89 de             	mov    %rbx,%rsi
  a14920:	e8 bb 4d 36 00       	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  a14925:	48 c7 03 00 00 00 00 	movq   $0x0,(%rbx)
  a1492c:	c7 43 08 ff ff ff ff 	movl   $0xffffffff,0x8(%rbx)
  a14933:	48 89 df             	mov    %rbx,%rdi
  a14936:	e8 2d 09 b4 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  a1493b:	49 8b 04 24          	mov    (%r12),%rax
  a1493f:	4a c7 04 f0 00 00 00 	movq   $0x0,(%rax,%r14,8)
  a14946:	00
  a14947:	4c 89 f8             	mov    %r15,%rax
  a1494a:	49 03 04 24          	add    (%r12),%rax
  a1494e:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  a14955:	41 83 c5 01          	add    $0x1,%r13d
  a14959:	45 3b 6c 24 08       	cmp    0x8(%r12),%r13d
  a1495e:	72 98                	jb     a148f8 <CUnitSpawner::destroyUnits()+0x108>
  a14960:	48 8b bd 00 02 00 00 	mov    0x200(%rbp),%rdi
  a14967:	c7 85 08 02 00 00 00 	movl   $0x0,0x208(%rbp)
  a1496e:	00 00 00
  a14971:	c7 85 0c 02 00 00 00 	movl   $0x0,0x20c(%rbp)
  a14978:	00 00 00
  a1497b:	48 85 ff             	test   %rdi,%rdi
  a1497e:	74 05                	je     a14985 <CUnitSpawner::destroyUnits()+0x195>
  a14980:	e8 b3 ec b3 ff       	call   553638 <operator delete[](void*)@plt>
  a14985:	8b 8d f0 01 00 00    	mov    0x1f0(%rbp),%ecx
  a1498b:	48 c7 85 00 02 00 00 	movq   $0x0,0x200(%rbp)
  a14992:	00 00 00 00
  a14996:	4c 8d a5 e8 01 00 00 	lea    0x1e8(%rbp),%r12
  a1499d:	85 c9                	test   %ecx,%ecx
  a1499f:	74 6f                	je     a14a10 <CUnitSpawner::destroyUnits()+0x220>
  a149a1:	45 31 ed             	xor    %r13d,%r13d
  a149a4:	0f 1f 40 00          	nopl   0x0(%rax)
  a149a8:	45 89 ee             	mov    %r13d,%r14d
  a149ab:	4e 8d 3c f5 00 00 00 	lea    0x0(,%r14,8),%r15
  a149b2:	00
  a149b3:	4c 89 f8             	mov    %r15,%rax
  a149b6:	49 03 04 24          	add    (%r12),%rax
  a149ba:	48 8b 18             	mov    (%rax),%rbx
  a149bd:	48 85 db             	test   %rbx,%rbx
  a149c0:	74 3c                	je     a149fe <CUnitSpawner::destroyUnits()+0x20e>
  a149c2:	48 8b 3b             	mov    (%rbx),%rdi
  a149c5:	48 85 ff             	test   %rdi,%rdi
  a149c8:	74 0b                	je     a149d5 <CUnitSpawner::destroyUnits()+0x1e5>
  a149ca:	8b 53 08             	mov    0x8(%rbx),%edx
  a149cd:	48 89 de             	mov    %rbx,%rsi
  a149d0:	e8 0b 4d 36 00       	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  a149d5:	48 c7 03 00 00 00 00 	movq   $0x0,(%rbx)
  a149dc:	c7 43 08 ff ff ff ff 	movl   $0xffffffff,0x8(%rbx)
  a149e3:	48 89 df             	mov    %rbx,%rdi
  a149e6:	e8 7d 08 b4 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  a149eb:	49 8b 04 24          	mov    (%r12),%rax
  a149ef:	4a c7 04 f0 00 00 00 	movq   $0x0,(%rax,%r14,8)
  a149f6:	00
  a149f7:	4c 89 f8             	mov    %r15,%rax
  a149fa:	49 03 04 24          	add    (%r12),%rax
  a149fe:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  a14a05:	41 83 c5 01          	add    $0x1,%r13d
  a14a09:	45 3b 6c 24 08       	cmp    0x8(%r12),%r13d
  a14a0e:	72 98                	jb     a149a8 <CUnitSpawner::destroyUnits()+0x1b8>
  a14a10:	48 8b bd e8 01 00 00 	mov    0x1e8(%rbp),%rdi
  a14a17:	c7 85 f0 01 00 00 00 	movl   $0x0,0x1f0(%rbp)
  a14a1e:	00 00 00
  a14a21:	c7 85 f4 01 00 00 00 	movl   $0x0,0x1f4(%rbp)
  a14a28:	00 00 00
  a14a2b:	48 85 ff             	test   %rdi,%rdi
  a14a2e:	74 05                	je     a14a35 <CUnitSpawner::destroyUnits()+0x245>
  a14a30:	e8 03 ec b3 ff       	call   553638 <operator delete[](void*)@plt>
  a14a35:	48 c7 85 e8 01 00 00 	movq   $0x0,0x1e8(%rbp)
  a14a3c:	00 00 00 00
  a14a40:	48 83 c4 08          	add    $0x8,%rsp
  a14a44:	5b                   	pop    %rbx
  a14a45:	5d                   	pop    %rbp
  a14a46:	41 5c                	pop    %r12
  a14a48:	41 5d                	pop    %r13
  a14a4a:	41 5e                	pop    %r14
  a14a4c:	41 5f                	pop    %r15
  a14a4e:	c3                   	ret
  a14a4f:	48 89 c7             	mov    %rax,%rdi
  a14a52:	e8 41 fa b3 ff       	call   554498 <_Unwind_Resume@plt>
  a14a57:	eb f6                	jmp    a14a4f <CUnitSpawner::destroyUnits()+0x25f>
