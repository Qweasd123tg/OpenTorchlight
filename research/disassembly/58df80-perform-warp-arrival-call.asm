
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000058df80 <CGameClient::performWarp()+0xe70>:
  58df80:	4c 8d a4 24 f0 00 00 	lea    0xf0(%rsp),%r12
  58df87:	00 
  58df88:	48 8d b5 b0 10 00 00 	lea    0x10b0(%rbp),%rsi
  58df8f:	4c 89 e7             	mov    %r12,%rdi
  58df92:	e8 f1 52 fc ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58df97:	45 31 ed             	xor    %r13d,%r13d
  58df9a:	83 7c 24 38 00       	cmpl   $0x0,0x38(%rsp)
  58df9f:	48 8d 9c 24 00 01 00 	lea    0x100(%rsp),%rbx
  58dfa6:	00 
  58dfa7:	48 8d b4 24 d0 01 00 	lea    0x1d0(%rsp),%rsi
  58dfae:	00 
  58dfaf:	48 89 df             	mov    %rbx,%rdi
  58dfb2:	41 0f 94 c5          	sete   %r13b
  58dfb6:	e8 cd 52 fc ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58dfbb:	48 8b 7d 70          	mov    0x70(%rbp),%rdi
  58dfbf:	4d 89 e0             	mov    %r12,%r8
  58dfc2:	44 89 e9             	mov    %r13d,%ecx
  58dfc5:	44 89 f2             	mov    %r14d,%edx
  58dfc8:	48 89 de             	mov    %rbx,%rsi
  58dfcb:	e8 30 50 3c 00       	call   953000 <CLevel::placePlayerAtWarpToDungeonFloor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, int, bool, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  58dfd0:	48 8b bc 24 00 01 00 	mov    0x100(%rsp),%rdi
  58dfd7:	00 
  58dfd8:	89 c3                	mov    %eax,%ebx
  58dfda:	48 83 ef 18          	sub    $0x18,%rdi
  58dfde:	49 39 ff             	cmp    %rdi,%r15
  58dfe1:	0f 85 34 04 00 00    	jne    58e41b <CGameClient::performWarp()+0x130b>
  58dfe7:	48 8b bc 24 f0 00 00 	mov    0xf0(%rsp),%rdi
  58dfee:	00 
  58dfef:	48 83 ef 18          	sub    $0x18,%rdi
  58dff3:	49 39 ff             	cmp    %rdi,%r15
  58dff6:	0f 85 ac 03 00 00    	jne    58e3a8 <CGameClient::performWarp()+0x1298>
  58dffc:	84 db                	test   %bl,%bl
  58dffe:	0f 84 d8 f5 ff ff    	je     58d5dc <CGameClient::performWarp()+0x4cc>
  58e004:	48 8b 75 70          	mov    0x70(%rbp),%rsi
  58e008:	48 8b 7d 58          	mov    0x58(%rbp),%rdi
  58e00c:	31 d2                	xor    %edx,%edx
  58e00e:	f3 0f 10 05 52 a7 a1 	movss  0xa1a752(%rip),%xmm0        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  58e015:	00 
  58e016:	e8 95 1e 28 00       	call   80feb0 <CCharacter::dropToGround(CLevel&, float, bool)>
  58e01b:	e9 bc f5 ff ff       	jmp    58d5dc <CGameClient::performWarp()+0x4cc>
  58e020:	e8 c3 73 fc ff       	call   5553e8 <wmemcmp@plt>
  58e025:	85 c0                	test   %eax,%eax
  58e027:	0f 85 7b f9 ff ff    	jne    58d9a8 <CGameClient::performWarp()+0x898>
  58e02d:	0f 1f 00             	nopl   (%rax)
