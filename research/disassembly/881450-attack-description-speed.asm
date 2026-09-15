
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000881450 <CEquipment::calculateCombatStats(bool)+0xb00>:
  881450:	00 00                	add    %al,(%rax)
  881452:	00 48 8b             	add    %cl,-0x75(%rax)
  881455:	bb a0 02 00 00       	mov    $0x2a0,%ebx
  88145a:	48 85 ff             	test   %rdi,%rdi
  88145d:	74 11                	je     881470 <CEquipment::calculateCombatStats(bool)+0xb20>
  88145f:	48 8b 07             	mov    (%rdi),%rax
  881462:	ff 50 08             	call   *0x8(%rax)
  881465:	48 c7 83 a0 02 00 00 	movq   $0x0,0x2a0(%rbx)
  88146c:	00 00 00 00 
  881470:	f3 0f 2a 44 24 3c    	cvtsi2ssl 0x3c(%rsp),%xmm0
  881476:	f3 0f 5e 05 be 33 72 	divss  0x7233be(%rip),%xmm0        # fa483c <vtable for Ogre::FrameListener+0x7c>
  88147d:	00 
  88147e:	be 24 00 00 00       	mov    $0x24,%esi
  881483:	48 89 df             	mov    %rbx,%rdi
  881486:	f3 0f 11 44 24 28    	movss  %xmm0,0x28(%rsp)
  88148c:	e8 0f 4e f7 ff       	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  881491:	84 c0                	test   %al,%al
  881493:	0f 84 97 01 00 00    	je     881630 <CEquipment::calculateCombatStats(bool)+0xce0>
  881499:	4c 8d a4 24 d0 00 00 	lea    0xd0(%rsp),%r12
  8814a0:	00 
  8814a1:	48 8d 94 24 a6 02 00 	lea    0x2a6(%rsp),%rdx
  8814a8:	00 
  8814a9:	be bd 0b fd 00       	mov    $0xfd0bbd,%esi
  8814ae:	4c 89 e7             	mov    %r12,%rdi
  8814b1:	e8 42 4e cd ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8814b6:	31 c9                	xor    %ecx,%ecx
  8814b8:	31 d2                	xor    %edx,%edx
  8814ba:	31 f6                	xor    %esi,%esi
  8814bc:	bf 80 00 00 00       	mov    $0x80,%edi
  8814c1:	e8 52 1e cd ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  8814c6:	48 89 c7             	mov    %rax,%rdi
  8814c9:	48 89 c5             	mov    %rax,%rbp
  8814cc:	44 8b ab 34 03 00 00 	mov    0x334(%rbx),%r13d
  8814d3:	44 8b b3 30 03 00 00 	mov    0x330(%rbx),%r14d
  8814da:	e8 e1 81 4f 00       	call   d796c0 <CRunicCore::CRunicCore()>
  8814df:	48 8d 7d 10          	lea    0x10(%rbp),%rdi
  8814e3:	48 c7 45 00 90 e3 fc 	movq   $0xfce390,0x0(%rbp)
  8814ea:	00 
  8814eb:	4c 89 e6             	mov    %r12,%rsi
  8814ee:	e8 b5 14 cd ff       	call   5529a8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&)@plt>
  8814f3:	c6 45 18 01          	movb   $0x1,0x18(%rbp)
  8814f7:	c7 45 5c 00 00 00 00 	movl   $0x0,0x5c(%rbp)
  8814fe:	c7 45 60 00 00 00 00 	movl   $0x0,0x60(%rbp)
  881505:	c7 45 64 00 00 00 00 	movl   $0x0,0x64(%rbp)
  88150c:	f3 0f 10 44 24 38    	movss  0x38(%rsp),%xmm0
  881512:	f3 0f 11 45 68       	movss  %xmm0,0x68(%rbp)
  881517:	f3 0f 10 44 24 34    	movss  0x34(%rsp),%xmm0
  88151d:	f3 0f 11 45 6c       	movss  %xmm0,0x6c(%rbp)
  881522:	f3 0f 10 44 24 28    	movss  0x28(%rsp),%xmm0
  881528:	f3 0f 11 45 70       	movss  %xmm0,0x70(%rbp)
  88152d:	8b 44 24 30          	mov    0x30(%rsp),%eax
  881531:	c7 45 78 00 00 00 00 	movl   $0x0,0x78(%rbp)
  881538:	89 45 74             	mov    %eax,0x74(%rbp)
  88153b:	31 c0                	xor    %eax,%eax
  88153d:	0f 1f 00             	nopl   (%rax)
