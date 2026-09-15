
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000953000 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:
  953000:	41 57                	push   %r15
  953002:	41 56                	push   %r14
  953004:	41 55                	push   %r13
  953006:	41 54                	push   %r12
  953008:	49 89 f4             	mov    %rsi,%r12
  95300b:	55                   	push   %rbp
  95300c:	53                   	push   %rbx
  95300d:	48 81 ec f8 00 00 00 	sub    $0xf8,%rsp
  953014:	48 89 7c 24 18       	mov    %rdi,0x18(%rsp)
  953019:	89 54 24 24          	mov    %edx,0x24(%rsp)
  95301d:	4c 89 44 24 30       	mov    %r8,0x30(%rsp)
  953022:	48 8b 87 20 02 00 00 	mov    0x220(%rdi),%rax
  953029:	48 83 78 58 00       	cmpq   $0x0,0x58(%rax)
  95302e:	0f 84 95 04 00 00    	je     9534c9 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4c9>
  953034:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  953039:	8b 9f a4 01 00 00    	mov    0x1a4(%rdi),%ebx
  95303f:	48 8b 3e             	mov    (%rsi),%rdi
  953042:	48 8b b0 80 02 00 00 	mov    0x280(%rax),%rsi
  953049:	48 8b 57 e8          	mov    -0x18(%rdi),%rdx
  95304d:	48 3b 56 e8          	cmp    -0x18(%rsi),%rdx
  953051:	0f 84 76 04 00 00    	je     9534cd <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4cd>
  953057:	c7 44 24 2c 00 00 00 	movl   $0x0,0x2c(%rsp)
  95305e:	00 
  95305f:	c7 44 24 24 00 00 00 	movl   $0x0,0x24(%rsp)
  953066:	00 
  953067:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  95306c:	48 c7 44 24 50 00 00 	movq   $0x0,0x50(%rsp)
  953073:	00 00 
  953075:	c7 44 24 58 00 00 00 	movl   $0x0,0x58(%rsp)
  95307c:	00 
  95307d:	c7 44 24 5c 00 00 00 	movl   $0x0,0x5c(%rsp)
  953084:	00 
  953085:	c7 44 24 60 0a 00 00 	movl   $0xa,0x60(%rsp)
  95308c:	00 
  95308d:	44 8b 50 18          	mov    0x18(%rax),%r10d
  953091:	45 85 d2             	test   %r10d,%r10d
  953094:	0f 84 2f 04 00 00    	je     9534c9 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4c9>
  95309a:	c7 44 24 28 00 00 00 	movl   $0x0,0x28(%rsp)
  9530a1:	00 
  9530a2:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  9530a7:	8b 44 24 28          	mov    0x28(%rsp),%eax
  9530ab:	39 42 1c             	cmp    %eax,0x1c(%rdx)
  9530ae:	0f 87 fc 02 00 00    	ja     9533b0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x3b0>
  9530b4:	48 8b 42 10          	mov    0x10(%rdx),%rax
  9530b8:	48 8b 18             	mov    (%rax),%rbx
  9530bb:	48 85 db             	test   %rbx,%rbx
  9530be:	0f 84 d7 01 00 00    	je     95329b <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x29b>
  9530c4:	48 8b 7c 24 50       	mov    0x50(%rsp),%rdi
  9530c9:	c7 44 24 58 00 00 00 	movl   $0x0,0x58(%rsp)
  9530d0:	00 
  9530d1:	c7 44 24 5c 00 00 00 	movl   $0x0,0x5c(%rsp)
  9530d8:	00 
  9530d9:	48 85 ff             	test   %rdi,%rdi
  9530dc:	74 05                	je     9530e3 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xe3>
  9530de:	e8 55 05 c0 ff       	call   553638 <operator delete[](void*)@plt>
  9530e3:	48 8d ac 24 e0 00 00 	lea    0xe0(%rsp),%rbp
  9530ea:	00 
  9530eb:	48 8d 94 24 ef 00 00 	lea    0xef(%rsp),%rdx
  9530f2:	00 
  9530f3:	be 98 e8 fa 00       	mov    $0xfae898,%esi
  9530f8:	48 c7 44 24 50 00 00 	movq   $0x0,0x50(%rsp)
  9530ff:	00 00 
  953101:	48 89 ef             	mov    %rbp,%rdi
  953104:	e8 4f 2d c0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  953109:	48 8d 44 24 50       	lea    0x50(%rsp),%rax
  95310e:	48 89 ee             	mov    %rbp,%rsi
  953111:	48 89 df             	mov    %rbx,%rdi
  953114:	48 89 c2             	mov    %rax,%rdx
  953117:	48 89 44 24 38       	mov    %rax,0x38(%rsp)
  95311c:	e8 cf 8a df ff       	call   74bbf0 <CEditorScene::GetObjectsCreatedByADescriptor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, TArrayList<CEditorBaseObject*>*)>
  953121:	48 8b bc 24 e0 00 00 	mov    0xe0(%rsp),%rdi
  953128:	00 
  953129:	41 be 40 45 42 01    	mov    $0x1424540,%r14d
  95312f:	48 83 ef 18          	sub    $0x18,%rdi
  953133:	4c 39 f7             	cmp    %r14,%rdi
  953136:	0f 85 2b 05 00 00    	jne    953667 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x667>
  95313c:	44 8b 4c 24 58       	mov    0x58(%rsp),%r9d
  953141:	45 85 c9             	test   %r9d,%r9d
  953144:	0f 84 51 01 00 00    	je     95329b <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x29b>
  95314a:	31 ed                	xor    %ebp,%ebp
  95314c:	0f 1f 40 00          	nopl   0x0(%rax)
  953150:	39 6c 24 5c          	cmp    %ebp,0x5c(%rsp)
  953154:	0f 87 66 01 00 00    	ja     9532c0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x2c0>
  95315a:	48 8b 44 24 50       	mov    0x50(%rsp),%rax
  95315f:	48 8b 38             	mov    (%rax),%rdi
  953162:	48 85 ff             	test   %rdi,%rdi
  953165:	0f 84 23 01 00 00    	je     95328e <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x28e>
  95316b:	31 c9                	xor    %ecx,%ecx
  95316d:	ba 10 8e fd 00       	mov    $0xfd8e10,%edx
  953172:	be 10 46 fc 00       	mov    $0xfc4610,%esi
  953177:	e8 dc 25 c0 ff       	call   555758 <__dynamic_cast@plt>
  95317c:	48 85 c0             	test   %rax,%rax
  95317f:	48 89 c3             	mov    %rax,%rbx
  953182:	0f 84 06 01 00 00    	je     95328e <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x28e>
  953188:	48 8b 78 40          	mov    0x40(%rax),%rdi
  95318c:	48 8b 0d 7d f0 b3 00 	mov    0xb3f07d(%rip),%rcx        # 1492210 <EMPTY_WSTRING>
  953193:	45 31 ed             	xor    %r13d,%r13d
  953196:	4c 8b 79 e8          	mov    -0x18(%rcx),%r15
  95319a:	4c 39 7f e8          	cmp    %r15,-0x18(%rdi)
  95319e:	0f 84 2c 01 00 00    	je     9532d0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x2d0>
  9531a4:	49 8b 3c 24          	mov    (%r12),%rdi
  9531a8:	4c 3b 7f e8          	cmp    -0x18(%rdi),%r15
  9531ac:	0f 84 4e 01 00 00    	je     953300 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x300>
  9531b2:	48 8b 74 24 30       	mov    0x30(%rsp),%rsi
  9531b7:	48 8d bc 24 c0 00 00 	lea    0xc0(%rsp),%rdi
  9531be:	00 
  9531bf:	e8 cc af 33 00       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  9531c4:	48 8d 73 40          	lea    0x40(%rbx),%rsi
  9531c8:	48 8d bc 24 d0 00 00 	lea    0xd0(%rsp),%rdi
  9531cf:	00 
  9531d0:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  9531d6:	e8 b5 af 33 00       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  9531db:	4c 8b ac 24 d0 00 00 	mov    0xd0(%rsp),%r13
  9531e2:	00 
  9531e3:	4c 8b bc 24 c0 00 00 	mov    0xc0(%rsp),%r15
  9531ea:	00 
  9531eb:	49 8b 55 e8          	mov    -0x18(%r13),%rdx
  9531ef:	49 3b 57 e8          	cmp    -0x18(%r15),%rdx
  9531f3:	49 8d 4d e8          	lea    -0x18(%r13),%rcx
  9531f7:	0f 84 a3 02 00 00    	je     9534a0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4a0>
  9531fd:	31 c0                	xor    %eax,%eax
  9531ff:	49 39 ce             	cmp    %rcx,%r14
  953202:	0f 85 03 04 00 00    	jne    95360b <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x60b>
  953208:	49 8d 7f e8          	lea    -0x18(%r15),%rdi
  95320c:	49 39 fe             	cmp    %rdi,%r14
  95320f:	0f 85 bd 03 00 00    	jne    9535d2 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x5d2>
  953215:	84 c0                	test   %al,%al
  953217:	0f 85 d3 02 00 00    	jne    9534f0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x4f0>
  95321d:	48 8d b3 10 01 00 00 	lea    0x110(%rbx),%rsi
  953224:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  95322b:	00 
  95322c:	45 31 ed             	xor    %r13d,%r13d
  95322f:	e8 5c af 33 00       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  953234:	48 8b bc 24 b0 00 00 	mov    0xb0(%rsp),%rdi
  95323b:	00 
  95323c:	49 8b 34 24          	mov    (%r12),%rsi
  953240:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  953246:	48 8b 57 e8          	mov    -0x18(%rdi),%rdx
  95324a:	48 3b 56 e8          	cmp    -0x18(%rsi),%rdx
  95324e:	4c 8d 7f e8          	lea    -0x18(%rdi),%r15
  953252:	0f 84 c8 00 00 00    	je     953320 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x320>
  953258:	be 64 83 fa 00       	mov    $0xfa8364,%esi
  95325d:	4c 89 e7             	mov    %r12,%rdi
  953260:	e8 93 1c c0 ff       	call   554ef8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::compare(wchar_t const*) const@plt>
  953265:	85 c0                	test   %eax,%eax
  953267:	0f 84 03 01 00 00    	je     953370 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x370>
  95326d:	4c 8b bc 24 b0 00 00 	mov    0xb0(%rsp),%r15
  953274:	00 
  953275:	45 31 ed             	xor    %r13d,%r13d
  953278:	49 83 ef 18          	sub    $0x18,%r15
  95327c:	4d 39 fe             	cmp    %r15,%r14
  95327f:	0f 85 19 03 00 00    	jne    95359e <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x59e>
  953285:	45 84 ed             	test   %r13b,%r13b
  953288:	0f 85 42 01 00 00    	jne    9533d0 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x3d0>
  95328e:	83 c5 01             	add    $0x1,%ebp
  953291:	3b 6c 24 58          	cmp    0x58(%rsp),%ebp
  953295:	0f 82 b5 fe ff ff    	jb     953150 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x150>
  95329b:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  9532a0:	83 44 24 28 01       	addl   $0x1,0x28(%rsp)
  9532a5:	8b 54 24 28          	mov    0x28(%rsp),%edx
  9532a9:	3b 50 18             	cmp    0x18(%rax),%edx
  9532ac:	0f 82 f0 fd ff ff    	jb     9530a2 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xa2>
  9532b2:	48 8b 7c 24 50       	mov    0x50(%rsp),%rdi
  9532b7:	31 db                	xor    %ebx,%ebx
  9532b9:	e9 bc 01 00 00       	jmp    95347a <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x47a>
  9532be:	66 90                	xchg   %ax,%ax
  9532c0:	89 e8                	mov    %ebp,%eax
  9532c2:	48 c1 e0 03          	shl    $0x3,%rax
  9532c6:	48 03 44 24 50       	add    0x50(%rsp),%rax
  9532cb:	e9 8f fe ff ff       	jmp    95315f <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x15f>
  9532d0:	48 89 ce             	mov    %rcx,%rsi
  9532d3:	4c 89 fa             	mov    %r15,%rdx
  9532d6:	48 89 4c 24 10       	mov    %rcx,0x10(%rsp)
  9532db:	e8 08 21 c0 ff       	call   5553e8 <wmemcmp@plt>
  9532e0:	85 c0                	test   %eax,%eax
  9532e2:	48 8b 4c 24 10       	mov    0x10(%rsp),%rcx
  9532e7:	0f 84 30 ff ff ff    	je     95321d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x21d>
  9532ed:	49 8b 3c 24          	mov    (%r12),%rdi
  9532f1:	4c 3b 7f e8          	cmp    -0x18(%rdi),%r15
  9532f5:	0f 85 b7 fe ff ff    	jne    9531b2 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1b2>
  9532fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  953300:	4c 89 fa             	mov    %r15,%rdx
  953303:	48 89 ce             	mov    %rcx,%rsi
  953306:	e8 dd 20 c0 ff       	call   5553e8 <wmemcmp@plt>
  95330b:	85 c0                	test   %eax,%eax
  95330d:	0f 85 9f fe ff ff    	jne    9531b2 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1b2>
  953313:	e9 05 ff ff ff       	jmp    95321d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x21d>
  953318:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  95331f:	00 
  953320:	e8 c3 20 c0 ff       	call   5553e8 <wmemcmp@plt>
  953325:	85 c0                	test   %eax,%eax
  953327:	0f 85 2b ff ff ff    	jne    953258 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x258>
  95332d:	8b 83 00 01 00 00    	mov    0x100(%rbx),%eax
  953333:	85 c0                	test   %eax,%eax
  953335:	74 19                	je     953350 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x350>
  953337:	8b 93 04 01 00 00    	mov    0x104(%rbx),%edx
  95333d:	85 d2                	test   %edx,%edx
  95333f:	75 06                	jne    953347 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x347>
  953341:	39 44 24 2c          	cmp    %eax,0x2c(%rsp)
  953345:	74 15                	je     95335c <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x35c>
  953347:	45 31 ed             	xor    %r13d,%r13d
  95334a:	e9 2d ff ff ff       	jmp    95327c <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x27c>
  95334f:	90                   	nop
  953350:	8b 93 04 01 00 00    	mov    0x104(%rbx),%edx
  953356:	39 54 24 24          	cmp    %edx,0x24(%rsp)
  95335a:	75 e1                	jne    95333d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x33d>
  95335c:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  953362:	e9 15 ff ff ff       	jmp    95327c <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x27c>
  953367:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  95336e:	00 00 
  953370:	48 8b bb 10 01 00 00 	mov    0x110(%rbx),%rdi
  953377:	48 8b 35 92 ee b3 00 	mov    0xb3ee92(%rip),%rsi        # 1492210 <EMPTY_WSTRING>
  95337e:	48 8b 57 e8          	mov    -0x18(%rdi),%rdx
  953382:	48 3b 56 e8          	cmp    -0x18(%rsi),%rdx
  953386:	0f 85 e1 fe ff ff    	jne    95326d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x26d>
  95338c:	e8 57 20 c0 ff       	call   5553e8 <wmemcmp@plt>
  953391:	85 c0                	test   %eax,%eax
  953393:	0f 85 d4 fe ff ff    	jne    95326d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x26d>
  953399:	4c 8b bc 24 b0 00 00 	mov    0xb0(%rsp),%r15
  9533a0:	00 
  9533a1:	49 83 ef 18          	sub    $0x18,%r15
  9533a5:	eb 86                	jmp    95332d <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x32d>
  9533a7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  9533ae:	00 00 
  9533b0:	8b 44 24 28          	mov    0x28(%rsp),%eax
  9533b4:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  9533b9:	48 c1 e0 03          	shl    $0x3,%rax
  9533bd:	48 03 42 10          	add    0x10(%rdx),%rax
  9533c1:	e9 f2 fc ff ff       	jmp    9530b8 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xb8>
  9533c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  9533cd:	00 00 00 
  9533d0:	be 01 00 00 00       	mov    $0x1,%esi
  9533d5:	48 89 df             	mov    %rbx,%rdi
  9533d8:	e8 a3 3c 09 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  9533dd:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  9533e3:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  9533e8:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  9533ed:	f3 0f 11 4c 24 48    	movss  %xmm1,0x48(%rsp)
  9533f3:	48 8d b4 24 80 00 00 	lea    0x80(%rsp),%rsi
  9533fa:	00 
  9533fb:	48 89 44 24 40       	mov    %rax,0x40(%rsp)
  953400:	48 89 84 24 80 00 00 	mov    %rax,0x80(%rsp)
  953407:	00 
  953408:	8b 44 24 48          	mov    0x48(%rsp),%eax
  95340c:	89 84 24 88 00 00 00 	mov    %eax,0x88(%rsp)
  953413:	48 8b 82 20 02 00 00 	mov    0x220(%rdx),%rax
  95341a:	48 8b 78 58          	mov    0x58(%rax),%rdi
  95341e:	e8 bd 3c 09 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  953423:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  953428:	48 89 df             	mov    %rbx,%rdi
  95342b:	48 8b 82 20 02 00 00 	mov    0x220(%rdx),%rax
  953432:	48 8b 68 58          	mov    0x58(%rax),%rbp
  953436:	48 8b 45 00          	mov    0x0(%rbp),%rax
  95343a:	4c 8b a0 20 01 00 00 	mov    0x120(%rax),%r12
  953441:	48 8b 03             	mov    (%rbx),%rax
  953444:	ff 90 38 01 00 00    	call   *0x138(%rax)
  95344a:	f3 0f 11 4c 24 48    	movss  %xmm1,0x48(%rsp)
  953450:	8b 44 24 48          	mov    0x48(%rsp),%eax
  953454:	48 89 ef             	mov    %rbp,%rdi
  953457:	66 0f d6 44 24 40    	movq   %xmm0,0x40(%rsp)
  95345d:	66 0f d6 44 24 70    	movq   %xmm0,0x70(%rsp)
  953463:	89 44 24 78          	mov    %eax,0x78(%rsp)
  953467:	f3 0f 10 4c 24 78    	movss  0x78(%rsp),%xmm1
  95346d:	41 ff d4             	call   *%r12
  953470:	48 8b 7c 24 50       	mov    0x50(%rsp),%rdi
  953475:	bb 01 00 00 00       	mov    $0x1,%ebx
  95347a:	48 85 ff             	test   %rdi,%rdi
  95347d:	74 05                	je     953484 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x484>
  95347f:	e8 b4 01 c0 ff       	call   553638 <operator delete[](void*)@plt>
  953484:	48 81 c4 f8 00 00 00 	add    $0xf8,%rsp
  95348b:	89 d8                	mov    %ebx,%eax
  95348d:	5b                   	pop    %rbx
  95348e:	5d                   	pop    %rbp
  95348f:	41 5c                	pop    %r12
  953491:	41 5d                	pop    %r13
  953493:	41 5e                	pop    %r14
  953495:	41 5f                	pop    %r15
  953497:	c3                   	ret
  953498:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  95349f:	00 
  9534a0:	4c 89 fe             	mov    %r15,%rsi
  9534a3:	4c 89 ef             	mov    %r13,%rdi
  9534a6:	48 89 4c 24 10       	mov    %rcx,0x10(%rsp)
  9534ab:	e8 38 1f c0 ff       	call   5553e8 <wmemcmp@plt>
  9534b0:	89 c2                	mov    %eax,%edx
  9534b2:	48 8b 4c 24 10       	mov    0x10(%rsp),%rcx
  9534b7:	b8 01 00 00 00       	mov    $0x1,%eax
  9534bc:	85 d2                	test   %edx,%edx
  9534be:	0f 85 39 fd ff ff    	jne    9531fd <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1fd>
  9534c4:	e9 36 fd ff ff       	jmp    9531ff <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1ff>
  9534c9:	31 db                	xor    %ebx,%ebx
  9534cb:	eb b7                	jmp    953484 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x484>
  9534cd:	0f 1f 00             	nopl   (%rax)
  9534d0:	e8 13 1f c0 ff       	call   5553e8 <wmemcmp@plt>
  9534d5:	85 c0                	test   %eax,%eax
  9534d7:	0f 85 7a fb ff ff    	jne    953057 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x57>
  9534dd:	8b 54 24 24          	mov    0x24(%rsp),%edx
  9534e1:	29 da                	sub    %ebx,%edx
  9534e3:	89 54 24 2c          	mov    %edx,0x2c(%rsp)
  9534e7:	e9 7b fb ff ff       	jmp    953067 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x67>
  9534ec:	0f 1f 40 00          	nopl   0x0(%rax)
  9534f0:	be 01 00 00 00       	mov    $0x1,%esi
  9534f5:	48 89 df             	mov    %rbx,%rdi
  9534f8:	e8 83 3b 09 00       	call   9e7080 <CPositionableObject::getPosition(bool)>
  9534fd:	66 0f d6 44 24 08    	movq   %xmm0,0x8(%rsp)
  953503:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  953508:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  95350d:	f3 0f 11 4c 24 48    	movss  %xmm1,0x48(%rsp)
  953513:	48 8d b4 24 a0 00 00 	lea    0xa0(%rsp),%rsi
  95351a:	00 
  95351b:	48 89 44 24 40       	mov    %rax,0x40(%rsp)
  953520:	48 89 84 24 a0 00 00 	mov    %rax,0xa0(%rsp)
  953527:	00 
  953528:	8b 44 24 48          	mov    0x48(%rsp),%eax
  95352c:	89 84 24 a8 00 00 00 	mov    %eax,0xa8(%rsp)
  953533:	48 8b 82 20 02 00 00 	mov    0x220(%rdx),%rax
  95353a:	48 8b 78 58          	mov    0x58(%rax),%rdi
  95353e:	e8 9d 3b 09 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  953543:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  953548:	48 89 df             	mov    %rbx,%rdi
  95354b:	48 8b 82 20 02 00 00 	mov    0x220(%rdx),%rax
  953552:	48 8b 68 58          	mov    0x58(%rax),%rbp
  953556:	48 8b 45 00          	mov    0x0(%rbp),%rax
  95355a:	4c 8b a0 20 01 00 00 	mov    0x120(%rax),%r12
  953561:	48 8b 03             	mov    (%rbx),%rax
  953564:	ff 90 38 01 00 00    	call   *0x138(%rax)
  95356a:	f3 0f 11 4c 24 48    	movss  %xmm1,0x48(%rsp)
  953570:	8b 44 24 48          	mov    0x48(%rsp),%eax
  953574:	48 89 ef             	mov    %rbp,%rdi
  953577:	66 0f d6 44 24 40    	movq   %xmm0,0x40(%rsp)
  95357d:	66 0f d6 84 24 90 00 	movq   %xmm0,0x90(%rsp)
  953584:	00 00 
  953586:	89 84 24 98 00 00 00 	mov    %eax,0x98(%rsp)
  95358d:	f3 0f 10 8c 24 98 00 	movss  0x98(%rsp),%xmm1
  953594:	00 00 
  953596:	41 ff d4             	call   *%r12
  953599:	e9 d2 fe ff ff       	jmp    953470 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x470>
  95359e:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  9535a3:	48 85 c0             	test   %rax,%rax
  9535a6:	0f 84 35 01 00 00    	je     9536e1 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x6e1>
  9535ac:	83 c8 ff             	or     $0xffffffff,%eax
  9535af:	f0 41 0f c1 47 10    	lock xadd %eax,0x10(%r15)
  9535b5:	85 c0                	test   %eax,%eax
  9535b7:	0f 8f c8 fc ff ff    	jg     953285 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x285>
  9535bd:	48 8d b4 24 eb 00 00 	lea    0xeb(%rsp),%rsi
  9535c4:	00 
  9535c5:	4c 89 ff             	mov    %r15,%rdi
  9535c8:	e8 7b ff bf ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  9535cd:	e9 b3 fc ff ff       	jmp    953285 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x285>
  9535d2:	ba c8 41 55 00       	mov    $0x5541c8,%edx
  9535d7:	48 85 d2             	test   %rdx,%rdx
  9535da:	0f 84 ca 00 00 00    	je     9536aa <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x6aa>
  9535e0:	83 ca ff             	or     $0xffffffff,%edx
  9535e3:	f0 0f c1 57 10       	lock xadd %edx,0x10(%rdi)
  9535e8:	85 d2                	test   %edx,%edx
  9535ea:	0f 8f 25 fc ff ff    	jg     953215 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x215>
  9535f0:	48 8d b4 24 ec 00 00 	lea    0xec(%rsp),%rsi
  9535f7:	00 
  9535f8:	88 44 24 10          	mov    %al,0x10(%rsp)
  9535fc:	e8 47 ff bf ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  953601:	0f b6 44 24 10       	movzbl 0x10(%rsp),%eax
  953606:	e9 0a fc ff ff       	jmp    953215 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x215>
  95360b:	ba c8 41 55 00       	mov    $0x5541c8,%edx
  953610:	48 85 d2             	test   %rdx,%rdx
  953613:	0f 84 fe 00 00 00    	je     953717 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x717>
  953619:	83 ca ff             	or     $0xffffffff,%edx
  95361c:	f0 0f c1 51 10       	lock xadd %edx,0x10(%rcx)
  953621:	85 d2                	test   %edx,%edx
  953623:	0f 8e c8 00 00 00    	jle    9536f1 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x6f1>
  953629:	4c 8b bc 24 c0 00 00 	mov    0xc0(%rsp),%r15
  953630:	00 
  953631:	e9 d2 fb ff ff       	jmp    953208 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x208>
  953636:	48 89 c3             	mov    %rax,%rbx
  953639:	48 8b 7c 24 38       	mov    0x38(%rsp),%rdi
  95363e:	e8 4d d5 de ff       	call   740b90 <TArrayList<CEditorBaseObject*>::~TArrayList()>
  953643:	48 89 df             	mov    %rbx,%rdi
  953646:	e8 4d 0e c0 ff       	call   554498 <_Unwind_Resume@plt>
  95364b:	48 8d 54 24 50       	lea    0x50(%rsp),%rdx
  953650:	48 89 c3             	mov    %rax,%rbx
  953653:	48 89 54 24 38       	mov    %rdx,0x38(%rsp)
  953658:	eb df                	jmp    953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  95365a:	48 89 ef             	mov    %rbp,%rdi
  95365d:	48 89 c3             	mov    %rax,%rbx
  953660:	e8 73 12 c0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  953665:	eb d2                	jmp    953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  953667:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  95366c:	48 85 c0             	test   %rax,%rax
  95366f:	74 47                	je     9536b8 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x6b8>
  953671:	83 c8 ff             	or     $0xffffffff,%eax
  953674:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  953679:	85 c0                	test   %eax,%eax
  95367b:	0f 8f bb fa ff ff    	jg     95313c <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x13c>
  953681:	48 8d b4 24 ee 00 00 	lea    0xee(%rsp),%rsi
  953688:	00 
  953689:	e8 ba fe bf ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  95368e:	e9 a9 fa ff ff       	jmp    95313c <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x13c>
  953693:	45 84 ed             	test   %r13b,%r13b
  953696:	48 89 c3             	mov    %rax,%rbx
  953699:	74 9e                	je     953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  95369b:	48 8d bc 24 b0 00 00 	lea    0xb0(%rsp),%rdi
  9536a2:	00 
  9536a3:	e8 30 12 c0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9536a8:	eb 8f                	jmp    953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  9536aa:	8b 57 10             	mov    0x10(%rdi),%edx
  9536ad:	8d 4a ff             	lea    -0x1(%rdx),%ecx
  9536b0:	89 4f 10             	mov    %ecx,0x10(%rdi)
  9536b3:	e9 30 ff ff ff       	jmp    9535e8 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x5e8>
  9536b8:	8b 47 10             	mov    0x10(%rdi),%eax
  9536bb:	8d 50 ff             	lea    -0x1(%rax),%edx
  9536be:	89 57 10             	mov    %edx,0x10(%rdi)
  9536c1:	eb b6                	jmp    953679 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x679>
  9536c3:	45 84 ed             	test   %r13b,%r13b
  9536c6:	48 89 c3             	mov    %rax,%rbx
  9536c9:	0f 84 6a ff ff ff    	je     953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  9536cf:	48 8d bc 24 c0 00 00 	lea    0xc0(%rsp),%rdi
  9536d6:	00 
  9536d7:	e8 fc 11 c0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9536dc:	e9 58 ff ff ff       	jmp    953639 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x639>
  9536e1:	41 8b 47 10          	mov    0x10(%r15),%eax
  9536e5:	8d 50 ff             	lea    -0x1(%rax),%edx
  9536e8:	41 89 57 10          	mov    %edx,0x10(%r15)
  9536ec:	e9 c4 fe ff ff       	jmp    9535b5 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x5b5>
  9536f1:	48 8d b4 24 ed 00 00 	lea    0xed(%rsp),%rsi
  9536f8:	00 
  9536f9:	48 89 cf             	mov    %rcx,%rdi
  9536fc:	88 44 24 10          	mov    %al,0x10(%rsp)
  953700:	e8 43 fe bf ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  953705:	4c 8b bc 24 c0 00 00 	mov    0xc0(%rsp),%r15
  95370c:	00 
  95370d:	0f b6 44 24 10       	movzbl 0x10(%rsp),%eax
  953712:	e9 f1 fa ff ff       	jmp    953208 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x208>
  953717:	41 8b 55 f8          	mov    -0x8(%r13),%edx
  95371b:	8d 72 ff             	lea    -0x1(%rdx),%esi
  95371e:	41 89 75 f8          	mov    %esi,-0x8(%r13)
  953722:	e9 fa fe ff ff       	jmp    953621 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x621>
