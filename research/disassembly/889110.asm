
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000889110 <CEquipment::unitInit(CDataGroup*, bool)>:
  889110:	push   %r15
  889112:	push   %r14
  889114:	push   %r13
  889116:	push   %r12
  889118:	push   %rbp
  889119:	mov    %rdi,%rbp
  88911c:	push   %rbx
  88911d:	sub    $0x3c8,%rsp
  889124:	test   %rsi,%rsi
  889127:	mov    %rsi,0x10(%rsp)
  88912c:	mov    %dl,0x1b(%rsp)
  889130:	je     889d5c <CEquipment::unitInit(CDataGroup*, bool)+0xc4c>
  889136:	movzbl %dl,%eax
  889139:	lea    0x360(%rsp),%rbx
  889141:	mov    %eax,%edx
  889143:	mov    %eax,0x1c(%rsp)
  889147:	call   8c2250 <CItem::unitInit(CDataGroup*, bool)>
  88914c:	lea    0x3bf(%rsp),%rdx
  889154:	mov    $0xfd0448,%esi
  889159:	mov    %rbx,%rdi
  88915c:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889161:	mov    0x1b0(%rbp),%rdi
  889168:	mov    $0x1480a48,%edx
  88916d:	mov    %rbx,%rsi
  889170:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889175:	lea    0x2d0(%rbp),%r12
  88917c:	mov    %rax,%rsi
  88917f:	mov    %r12,%rdi
  889182:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889187:	mov    0x360(%rsp),%rdi
  88918f:	mov    $0x1424540,%ebx
  889194:	sub    $0x18,%rdi
  889198:	cmp    %rbx,%rdi
  88919b:	jne    88a6e5 <CEquipment::unitInit(CDataGroup*, bool)+0x15d5>
  8891a1:	mov    $0xfa3b9c,%edi
  8891a6:	call   554608 <wcslen@plt>
  8891ab:	xor    %edx,%edx
  8891ad:	mov    %rax,%rcx
  8891b0:	mov    $0xfa3b9c,%esi
  8891b5:	mov    %r12,%rdi
  8891b8:	call   555b58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::find(wchar_t const*, unsigned long, unsigned long) const@plt>
  8891bd:	mov    $0xfa3bac,%edi
  8891c2:	movslq %eax,%r14
  8891c5:	mov    %eax,%r13d
  8891c8:	call   554608 <wcslen@plt>
  8891cd:	mov    %r14,%rdx
  8891d0:	mov    %rax,%rcx
  8891d3:	mov    $0xfa3bac,%esi
  8891d8:	mov    %r12,%rdi
  8891db:	call   555b58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::find(wchar_t const*, unsigned long, unsigned long) const@plt>
  8891e0:	cmp    $0xffffffff,%eax
  8891e3:	mov    %eax,%r15d
  8891e6:	jne    889db8 <CEquipment::unitInit(CDataGroup*, bool)+0xca8>
  8891ec:	lea    0x350(%rsp),%r13
  8891f4:	lea    0x3be(%rsp),%rdx
  8891fc:	mov    $0xfaf098,%esi
  889201:	mov    %r13,%rdi
  889204:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889209:	mov    0x1b0(%rbp),%rdi
  889210:	mov    $0x1480a48,%edx
  889215:	mov    %r13,%rsi
  889218:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88921d:	lea    0x2d8(%rbp),%r12
  889224:	mov    %rax,%rsi
  889227:	mov    %r12,%rdi
  88922a:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88922f:	mov    0x350(%rsp),%rdi
  889237:	sub    $0x18,%rdi
  88923b:	cmp    %rdi,%rbx
  88923e:	jne    88a732 <CEquipment::unitInit(CDataGroup*, bool)+0x1622>
  889244:	lea    0x340(%rsp),%r13
  88924c:	lea    0x3bd(%rsp),%rdx
  889254:	mov    $0xfc84a8,%esi
  889259:	mov    %r13,%rdi
  88925c:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889261:	mov    0x1b0(%rbp),%rdi
  889268:	mov    %r12,%rdx
  88926b:	mov    %r13,%rsi
  88926e:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889273:	mov    %rax,%rsi
  889276:	mov    %r12,%rdi
  889279:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88927e:	mov    0x340(%rsp),%rdi
  889286:	sub    $0x18,%rdi
  88928a:	cmp    %rdi,%rbx
  88928d:	jne    88a8cd <CEquipment::unitInit(CDataGroup*, bool)+0x17bd>
  889293:	mov    $0xfa3b9c,%edi
  889298:	call   554608 <wcslen@plt>
  88929d:	xor    %edx,%edx
  88929f:	mov    %rax,%rcx
  8892a2:	mov    $0xfa3b9c,%esi
  8892a7:	mov    %r12,%rdi
  8892aa:	call   555b58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::find(wchar_t const*, unsigned long, unsigned long) const@plt>
  8892af:	mov    $0xfa3bac,%edi
  8892b4:	movslq %eax,%r14
  8892b7:	mov    %eax,%r13d
  8892ba:	call   554608 <wcslen@plt>
  8892bf:	mov    %r14,%rdx
  8892c2:	mov    %rax,%rcx
  8892c5:	mov    $0xfa3bac,%esi
  8892ca:	mov    %r12,%rdi
  8892cd:	call   555b58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::find(wchar_t const*, unsigned long, unsigned long) const@plt>
  8892d2:	cmp    $0xffffffff,%eax
  8892d5:	mov    %eax,%r15d
  8892d8:	jne    889d70 <CEquipment::unitInit(CDataGroup*, bool)+0xc60>
  8892de:	lea    0x320(%rsp),%r12
  8892e6:	lea    0x3bc(%rsp),%rdx
  8892ee:	mov    $0xfc93a0,%esi
  8892f3:	mov    %r12,%rdi
  8892f6:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8892fb:	mov    0x10(%rsp),%rdi
  889300:	mov    $0x1480a48,%edx
  889305:	mov    %r12,%rsi
  889308:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88930d:	lea    0x330(%rsp),%rdi
  889315:	mov    %rax,%rsi
  889318:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88931d:	mov    0x320(%rsp),%rdi
  889325:	sub    $0x18,%rdi
  889329:	cmp    %rdi,%rbx
  88932c:	jne    88ab31 <CEquipment::unitInit(CDataGroup*, bool)+0x1a21>
  889332:	mov    0x330(%rsp),%rdi
  88933a:	mov    0xbf7707(%rip),%rsi        # 1480a48 <EMPTY_WSTRING>
  889341:	mov    -0x18(%rdi),%rdx
  889345:	cmp    -0x18(%rsi),%rdx
  889349:	je     889f20 <CEquipment::unitInit(CDataGroup*, bool)+0xe10>
  88934f:	lea    0x300(%rsp),%r12
  889357:	lea    0x3bb(%rsp),%rdx
  88935f:	mov    $0xfc9358,%esi
  889364:	mov    %r12,%rdi
  889367:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88936c:	mov    0x10(%rsp),%rdi
  889371:	mov    $0x1480a48,%edx
  889376:	mov    %r12,%rsi
  889379:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88937e:	lea    0x310(%rsp),%rdi
  889386:	mov    %rax,%rsi
  889389:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88938e:	mov    0x300(%rsp),%rdi
  889396:	sub    $0x18,%rdi
  88939a:	cmp    %rdi,%rbx
  88939d:	jne    88ab78 <CEquipment::unitInit(CDataGroup*, bool)+0x1a68>
  8893a3:	lea    0x2f0(%rsp),%r13
  8893ab:	lea    0x310(%rsp),%rsi
  8893b3:	mov    %r13,%rdi
  8893b6:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8893bb:	mov    $0xfff8b8,%edi
  8893c0:	call   554608 <wcslen@plt>
  8893c5:	mov    $0xfff8b8,%esi
  8893ca:	mov    %rax,%rdx
  8893cd:	mov    %r13,%rdi
  8893d0:	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  8893d5:	lea    0x2e0(%rsp),%r15
  8893dd:	lea    0x330(%rsp),%rdx
  8893e5:	mov    %r13,%rsi
  8893e8:	mov    %r15,%rdi
  8893eb:	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8893f0:	lea    0x2d0(%rsp),%r12
  8893f8:	mov    %r15,%rsi
  8893fb:	mov    %r12,%rdi
  8893fe:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889403:	mov    $0xfafb04,%edi
  889408:	call   554608 <wcslen@plt>
  88940d:	mov    $0xfafb04,%esi
  889412:	mov    %rax,%rdx
  889415:	mov    %r12,%rdi
  889418:	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  88941d:	lea    0x2c0(%rsp),%r14
  889425:	mov    %r12,%rsi
  889428:	mov    %r14,%rdi
  88942b:	call   c73b60 <FILESYSTEM::CleanPath(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889430:	lea    0x310(%rsp),%rdi
  889438:	mov    %r14,%rsi
  88943b:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889440:	mov    0x2c0(%rsp),%rdi
  889448:	sub    $0x18,%rdi
  88944c:	cmp    %rdi,%rbx
  88944f:	jne    88af3f <CEquipment::unitInit(CDataGroup*, bool)+0x1e2f>
  889455:	mov    0x2d0(%rsp),%rdi
  88945d:	sub    $0x18,%rdi
  889461:	cmp    %rdi,%rbx
  889464:	jne    88af6f <CEquipment::unitInit(CDataGroup*, bool)+0x1e5f>
  88946a:	mov    0x2e0(%rsp),%rdi
  889472:	sub    $0x18,%rdi
  889476:	cmp    %rdi,%rbx
  889479:	jne    88b0f5 <CEquipment::unitInit(CDataGroup*, bool)+0x1fe5>
  88947f:	mov    0x2f0(%rsp),%rdi
  889487:	sub    $0x18,%rdi
  88948b:	cmp    %rdi,%rbx
  88948e:	jne    88afd5 <CEquipment::unitInit(CDataGroup*, bool)+0x1ec5>
  889494:	mov    0x68(%rbp),%rax
  889498:	mov    0x30(%rax),%r9d
  88949c:	test   %r9d,%r9d
  88949f:	jne    889fd8 <CEquipment::unitInit(CDataGroup*, bool)+0xec8>
  8894a5:	lea    0x230(%rsp),%r13
  8894ad:	mov    $0x1480a48,%esi
  8894b2:	mov    %r13,%rdi
  8894b5:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8894ba:	lea    0x240(%rsp),%r12
  8894c2:	lea    0x310(%rsp),%rsi
  8894ca:	mov    %r12,%rdi
  8894cd:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8894d2:	mov    %r13,%rdx
  8894d5:	mov    %r12,%rsi
  8894d8:	mov    %rbp,%rdi
  8894db:	call   887b30 <CEquipment::loadModel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  8894e0:	mov    0x240(%rsp),%rdi
  8894e8:	sub    $0x18,%rdi
  8894ec:	cmp    %rdi,%rbx
  8894ef:	jne    88b13a <CEquipment::unitInit(CDataGroup*, bool)+0x202a>
  8894f5:	mov    0x230(%rsp),%rdi
  8894fd:	sub    $0x18,%rdi
  889501:	cmp    %rdi,%rbx
  889504:	jne    88aaa3 <CEquipment::unitInit(CDataGroup*, bool)+0x1993>
  88950a:	mov    0x310(%rsp),%rdi
  889512:	sub    $0x18,%rdi
  889516:	cmp    %rdi,%rbx
  889519:	jne    88aacf <CEquipment::unitInit(CDataGroup*, bool)+0x19bf>
  88951f:	lea    0x1f0(%rsp),%r12
  889527:	lea    0x3b6(%rsp),%rdx
  88952f:	mov    $0xfd0948,%esi
  889534:	mov    %r12,%rdi
  889537:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88953c:	mov    0x10(%rsp),%rdi
  889541:	mov    $0xfa3a20,%edx
  889546:	mov    %r12,%rsi
  889549:	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  88954e:	lea    0x200(%rsp),%rdi
  889556:	mov    %rax,%rsi
  889559:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88955e:	mov    0x1f0(%rsp),%rdi
  889566:	sub    $0x18,%rdi
  88956a:	cmp    %rdi,%rbx
  88956d:	jne    88abb4 <CEquipment::unitInit(CDataGroup*, bool)+0x1aa4>
  889573:	lea    0x200(%rsp),%rdi
  88957b:	mov    $0xfd0510,%esi
  889580:	call   554ef8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::compare(wchar_t const*) const@plt>
  889585:	test   %eax,%eax
  889587:	jne    889e60 <CEquipment::unitInit(CDataGroup*, bool)+0xd50>
  88958d:	movl   $0xffffd8f1,0x248(%rbp)
  889597:	lea    0x1d0(%rsp),%r12
  88959f:	lea    0x3b5(%rsp),%rdx
  8895a7:	mov    $0xfd0538,%esi
  8895ac:	mov    %r12,%rdi
  8895af:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8895b4:	mov    0x10(%rsp),%rdi
  8895b9:	mov    $0xfa3890,%edx
  8895be:	mov    %r12,%rsi
  8895c1:	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  8895c6:	lea    0x1e0(%rsp),%rdi
  8895ce:	mov    %rax,%rsi
  8895d1:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8895d6:	mov    0x1d0(%rsp),%rdi
  8895de:	sub    $0x18,%rdi
  8895e2:	cmp    %rdi,%rbx
  8895e5:	jne    88ac05 <CEquipment::unitInit(CDataGroup*, bool)+0x1af5>
  8895eb:	lea    0x1c0(%rsp),%r13
  8895f3:	xor    %r12d,%r12d
  8895f6:	mov    %r12d,%eax
  8895f9:	mov    %r13,%rdi
  8895fc:	lea    0x14812a0(,%rax,8),%rsi
  889604:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889609:	mov    0x1c0(%rsp),%r14
  889611:	mov    0x1e0(%rsp),%rdi
  889619:	xor    %eax,%eax
  88961b:	mov    -0x18(%rdi),%rdx
  88961f:	cmp    -0x18(%r14),%rdx
  889623:	lea    -0x18(%r14),%r15
  889627:	je     889e00 <CEquipment::unitInit(CDataGroup*, bool)+0xcf0>
  88962d:	cmp    %r15,%rbx
  889630:	jne    88ac42 <CEquipment::unitInit(CDataGroup*, bool)+0x1b32>
  889636:	test   %al,%al
  889638:	jne    88a359 <CEquipment::unitInit(CDataGroup*, bool)+0x1249>
  88963e:	add    $0x1,%r12d
  889642:	cmp    $0x2,%r12d
  889646:	jne    8895f6 <CEquipment::unitInit(CDataGroup*, bool)+0x4e6>
  889648:	lea    0x1b0(%rsp),%r12
  889650:	lea    0x3b4(%rsp),%rdx
  889658:	mov    $0xfd0568,%esi
  88965d:	movzbl 0x25f(%rbp),%r13d
  889665:	mov    %r12,%rdi
  889668:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88966d:	mov    0x10(%rsp),%rdi
  889672:	mov    %r13d,%edx
  889675:	mov    %r12,%rsi
  889678:	call   c5f340 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)>
  88967d:	mov    %al,0x25f(%rbp)
  889683:	mov    0x1b0(%rsp),%rdi
  88968b:	sub    $0x18,%rdi
  88968f:	cmp    %rdi,%rbx
  889692:	jne    88a773 <CEquipment::unitInit(CDataGroup*, bool)+0x1663>
  889698:	lea    0x1a0(%rsp),%r12
  8896a0:	lea    0x3b3(%rsp),%rdx
  8896a8:	mov    $0xfd05b0,%esi
  8896ad:	mov    %r12,%rdi
  8896b0:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8896b5:	mov    0x10(%rsp),%rdi
  8896ba:	mov    $0x1,%edx
  8896bf:	mov    %r12,%rsi
  8896c2:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8896c7:	mov    %eax,0x23c(%rbp)
  8896cd:	mov    0x1a0(%rsp),%rdi
  8896d5:	sub    $0x18,%rdi
  8896d9:	cmp    %rdi,%rbx
  8896dc:	jne    88a7b5 <CEquipment::unitInit(CDataGroup*, bool)+0x16a5>
  8896e2:	lea    0x190(%rsp),%r14
  8896ea:	lea    0x3b2(%rsp),%rdx
  8896f2:	mov    $0xfd05e8,%esi
  8896f7:	mov    %r14,%rdi
  8896fa:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8896ff:	mov    0x10(%rsp),%rdi
  889704:	mov    $0x1480a48,%edx
  889709:	mov    %r14,%rsi
  88970c:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889711:	lea    0x180(%rsp),%r13
  889719:	mov    %rax,%rsi
  88971c:	mov    %r13,%rdi
  88971f:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889724:	lea    0x3d8(%rbp),%r12
  88972b:	mov    %r13,%rsi
  88972e:	mov    %r12,%rdi
  889731:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889736:	mov    0x180(%rsp),%rdi
  88973e:	sub    $0x18,%rdi
  889742:	cmp    %rdi,%rbx
  889745:	jne    88a802 <CEquipment::unitInit(CDataGroup*, bool)+0x16f2>
  88974b:	mov    0x190(%rsp),%rdi
  889753:	sub    $0x18,%rdi
  889757:	cmp    %rdi,%rbx
  88975a:	jne    88a9ee <CEquipment::unitInit(CDataGroup*, bool)+0x18de>
  889760:	lea    0x170(%rsp),%r13
  889768:	mov    %r12,%rsi
  88976b:	mov    %r13,%rdi
  88976e:	call   c73b60 <FILESYSTEM::CleanPath(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889773:	mov    %r13,%rsi
  889776:	mov    %r12,%rdi
  889779:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88977e:	mov    0x170(%rsp),%rdi
  889786:	sub    $0x18,%rdi
  88978a:	cmp    %rdi,%rbx
  88978d:	jne    88aa35 <CEquipment::unitInit(CDataGroup*, bool)+0x1925>
  889793:	lea    0x160(%rsp),%r12
  88979b:	lea    0x3b1(%rsp),%rdx
  8897a3:	mov    $0xfa3c78,%esi
  8897a8:	mov    %r12,%rdi
  8897ab:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8897b0:	mov    0x10(%rsp),%rdi
  8897b5:	mov    $0x1,%edx
  8897ba:	mov    %r12,%rsi
  8897bd:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  8897c2:	mov    %eax,0x274(%rbp)
  8897c8:	mov    0x160(%rsp),%rdi
  8897d0:	sub    $0x18,%rdi
  8897d4:	cmp    %rdi,%rbx
  8897d7:	jne    88aa77 <CEquipment::unitInit(CDataGroup*, bool)+0x1967>
  8897dd:	lea    0x150(%rsp),%r12
  8897e5:	lea    0x3b0(%rsp),%rdx
  8897ed:	mov    $0xfcf528,%esi
  8897f2:	mov    %r12,%rdi
  8897f5:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8897fa:	mov    0x10(%rsp),%rdi
  8897ff:	xor    %edx,%edx
  889801:	mov    %r12,%rsi
  889804:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  889809:	mov    0x150(%rsp),%rdi
  889811:	sub    $0x18,%rdi
  889815:	cmp    %rdi,%rbx
  889818:	jne    88af9f <CEquipment::unitInit(CDataGroup*, bool)+0x1e8f>
  88981e:	mov    $0x2,%edx
  889823:	cmp    $0x2,%eax
  889826:	lea    0x140(%rsp),%r12
  88982e:	cmovl  %eax,%edx
  889831:	mov    $0xfd0620,%esi
  889836:	mov    %edx,0x3e0(%rbp)
  88983c:	lea    0x3af(%rsp),%rdx
  889844:	mov    %r12,%rdi
  889847:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88984c:	mov    0x10(%rsp),%rdi
  889851:	xor    %edx,%edx
  889853:	mov    %r12,%rsi
  889856:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  88985b:	mov    0x140(%rsp),%rdi
  889863:	sub    $0x18,%rdi
  889867:	cmp    %rdi,%rbx
  88986a:	jne    88b025 <CEquipment::unitInit(CDataGroup*, bool)+0x1f15>
  889870:	cmpb   $0x0,0x1b(%rsp)
  889875:	jne    889893 <CEquipment::unitInit(CDataGroup*, bool)+0x783>
  889877:	cvtsi2ss %eax,%xmm0
  88987b:	xorps  %xmm1,%xmm1
  88987e:	movss  %xmm0,0xc(%rsp)
  889884:	ucomiss %xmm1,%xmm0
  889887:	jp     88a300 <CEquipment::unitInit(CDataGroup*, bool)+0x11f0>
  88988d:	jne    88a300 <CEquipment::unitInit(CDataGroup*, bool)+0x11f0>
  889893:	mov    0x1c(%rsp),%esi
  889897:	mov    %rbp,%rdi
  88989a:	call   880950 <CEquipment::calculateCombatStats(bool)>
  88989f:	mov    %rbp,%rdi
  8898a2:	call   880030 <CEquipment::setRequirements()>
  8898a7:	cmpb   $0x0,0x1b(%rsp)
  8898ac:	je     889e80 <CEquipment::unitInit(CDataGroup*, bool)+0xd70>
  8898b2:	mov    0x1b8(%rbp),%rdi
  8898b9:	test   %rdi,%rdi
  8898bc:	je     8898c3 <CEquipment::unitInit(CDataGroup*, bool)+0x7b3>
  8898be:	call   7ebf30 <CEffectManager::calculateEffectValues()>
  8898c3:	mov    %rbp,%rdi
  8898c6:	call   886240 <CEquipment::createElementalDamages()>
  8898cb:	mov    %rbp,%rdi
  8898ce:	call   883e20 <CEquipment::recalculatePrice()>
  8898d3:	cmpq   $0x0,0x1d8(%rbp)
  8898db:	je     889e18 <CEquipment::unitInit(CDataGroup*, bool)+0xd08>
  8898e1:	call   a54490 <CMasterResourceManager::getSingleton()>
  8898e6:	lea    0x110(%rsp),%r14
  8898ee:	lea    0x3ad(%rsp),%rdx
  8898f6:	mov    $0xfa0aa8,%esi
  8898fb:	mov    0x100(%rax),%r13
  889902:	mov    %r14,%rdi
  889905:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88990a:	mov    0x1b0(%rbp),%rdi
  889911:	mov    $0x1480a48,%edx
  889916:	mov    %r14,%rsi
  889919:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88991e:	lea    0x120(%rsp),%r12
  889926:	mov    %rax,%rsi
  889929:	mov    %r12,%rdi
  88992c:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889931:	mov    0x110(%rsp),%rdi
  889939:	sub    $0x18,%rdi
  88993d:	cmp    %rdi,%rbx
  889940:	jne    88a960 <CEquipment::unitInit(CDataGroup*, bool)+0x1850>
  889946:	lea    0x100(%rsp),%r14
  88994e:	mov    %r12,%rsi
  889951:	mov    %r14,%rdi
  889954:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889959:	mov    %r14,%rsi
  88995c:	mov    %r13,%rdi
  88995f:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889964:	mov    0x100(%rsp),%rdi
  88996c:	sub    $0x18,%rdi
  889970:	cmp    %rdi,%rbx
  889973:	jne    88a855 <CEquipment::unitInit(CDataGroup*, bool)+0x1745>
  889979:	test   %rax,%rax
  88997c:	je     889993 <CEquipment::unitInit(CDataGroup*, bool)+0x883>
  88997e:	mov    0x20(%rax),%rdx
  889982:	mov    0x1d8(%rbp),%rdi
  889989:	mov    $0x10,%esi
  88998e:	call   a69570 <CSoundBank::addSample(int, long long)>
  889993:	lea    0xf0(%rsp),%r14
  88999b:	lea    0x3ac(%rsp),%rdx
  8899a3:	mov    $0xfa0ad8,%esi
  8899a8:	mov    %r14,%rdi
  8899ab:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8899b0:	mov    0x1b0(%rbp),%rdi
  8899b7:	mov    $0x1480a48,%edx
  8899bc:	mov    %r14,%rsi
  8899bf:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8899c4:	mov    %rax,%rsi
  8899c7:	mov    %r12,%rdi
  8899ca:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8899cf:	mov    0xf0(%rsp),%rdi
  8899d7:	sub    $0x18,%rdi
  8899db:	cmp    %rdi,%rbx
  8899de:	jne    88a8a1 <CEquipment::unitInit(CDataGroup*, bool)+0x1791>
  8899e4:	lea    0xe0(%rsp),%r14
  8899ec:	mov    %r12,%rsi
  8899ef:	mov    %r14,%rdi
  8899f2:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8899f7:	mov    %r14,%rsi
  8899fa:	mov    %r13,%rdi
  8899fd:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889a02:	mov    0xe0(%rsp),%rdi
  889a0a:	sub    $0x18,%rdi
  889a0e:	cmp    %rdi,%rbx
  889a11:	jne    88a5c8 <CEquipment::unitInit(CDataGroup*, bool)+0x14b8>
  889a17:	test   %rax,%rax
  889a1a:	je     889a31 <CEquipment::unitInit(CDataGroup*, bool)+0x921>
  889a1c:	mov    0x20(%rax),%rdx
  889a20:	mov    0x1d8(%rbp),%rdi
  889a27:	mov    $0x11,%esi
  889a2c:	call   a69570 <CSoundBank::addSample(int, long long)>
  889a31:	lea    0xd0(%rsp),%r14
  889a39:	lea    0x3ab(%rsp),%rdx
  889a41:	mov    $0xfa0b08,%esi
  889a46:	mov    %r14,%rdi
  889a49:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889a4e:	mov    0x1b0(%rbp),%rdi
  889a55:	mov    $0x1480a48,%edx
  889a5a:	mov    %r14,%rsi
  889a5d:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889a62:	mov    %rax,%rsi
  889a65:	mov    %r12,%rdi
  889a68:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889a6d:	mov    0xd0(%rsp),%rdi
  889a75:	sub    $0x18,%rdi
  889a79:	cmp    %rdi,%rbx
  889a7c:	jne    88a621 <CEquipment::unitInit(CDataGroup*, bool)+0x1511>
  889a82:	lea    0xc0(%rsp),%r14
  889a8a:	mov    %r12,%rsi
  889a8d:	mov    %r14,%rdi
  889a90:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889a95:	mov    %r14,%rsi
  889a98:	mov    %r13,%rdi
  889a9b:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889aa0:	mov    0xc0(%rsp),%rdi
  889aa8:	sub    $0x18,%rdi
  889aac:	cmp    %rdi,%rbx
  889aaf:	jne    88a65d <CEquipment::unitInit(CDataGroup*, bool)+0x154d>
  889ab5:	test   %rax,%rax
  889ab8:	je     889acf <CEquipment::unitInit(CDataGroup*, bool)+0x9bf>
  889aba:	mov    0x20(%rax),%rdx
  889abe:	mov    0x1d8(%rbp),%rdi
  889ac5:	mov    $0x12,%esi
  889aca:	call   a69570 <CSoundBank::addSample(int, long long)>
  889acf:	lea    0xb0(%rsp),%r14
  889ad7:	lea    0x3aa(%rsp),%rdx
  889adf:	mov    $0xfa0980,%esi
  889ae4:	mov    %r14,%rdi
  889ae7:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889aec:	mov    0x1b0(%rbp),%rdi
  889af3:	mov    $0x1480a48,%edx
  889af8:	mov    %r14,%rsi
  889afb:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889b00:	mov    %rax,%rsi
  889b03:	mov    %r12,%rdi
  889b06:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889b0b:	mov    0xb0(%rsp),%rdi
  889b13:	sub    $0x18,%rdi
  889b17:	cmp    %rdi,%rbx
  889b1a:	jne    88a6a5 <CEquipment::unitInit(CDataGroup*, bool)+0x1595>
  889b20:	lea    0xa0(%rsp),%r14
  889b28:	mov    %r12,%rsi
  889b2b:	mov    %r14,%rdi
  889b2e:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889b33:	mov    %r14,%rsi
  889b36:	mov    %r13,%rdi
  889b39:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889b3e:	mov    0xa0(%rsp),%rdi
  889b46:	sub    $0x18,%rdi
  889b4a:	cmp    %rdi,%rbx
  889b4d:	jne    88a991 <CEquipment::unitInit(CDataGroup*, bool)+0x1881>
  889b53:	test   %rax,%rax
  889b56:	je     889b6d <CEquipment::unitInit(CDataGroup*, bool)+0xa5d>
  889b58:	mov    0x20(%rax),%rdx
  889b5c:	mov    0x1d8(%rbp),%rdi
  889b63:	mov    $0xa,%esi
  889b68:	call   a69570 <CSoundBank::addSample(int, long long)>
  889b6d:	lea    0x90(%rsp),%r14
  889b75:	lea    0x3a9(%rsp),%rdx
  889b7d:	mov    $0xfa0798,%esi
  889b82:	mov    %r14,%rdi
  889b85:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889b8a:	mov    0x1b0(%rbp),%rdi
  889b91:	mov    $0x1480a48,%edx
  889b96:	mov    %r14,%rsi
  889b99:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889b9e:	mov    %rax,%rsi
  889ba1:	mov    %r12,%rdi
  889ba4:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889ba9:	mov    0x90(%rsp),%rdi
  889bb1:	sub    $0x18,%rdi
  889bb5:	cmp    %rdi,%rbx
  889bb8:	jne    88a91f <CEquipment::unitInit(CDataGroup*, bool)+0x180f>
  889bbe:	lea    0x80(%rsp),%r14
  889bc6:	mov    %r12,%rsi
  889bc9:	mov    %r14,%rdi
  889bcc:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889bd1:	mov    %r14,%rsi
  889bd4:	mov    %r13,%rdi
  889bd7:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889bdc:	mov    0x80(%rsp),%rdi
  889be4:	sub    $0x18,%rdi
  889be8:	cmp    %rdi,%rbx
  889beb:	jne    88ac8b <CEquipment::unitInit(CDataGroup*, bool)+0x1b7b>
  889bf1:	test   %rax,%rax
  889bf4:	je     889c0b <CEquipment::unitInit(CDataGroup*, bool)+0xafb>
  889bf6:	mov    0x20(%rax),%rdx
  889bfa:	mov    0x1d8(%rbp),%rdi
  889c01:	mov    $0x1,%esi
  889c06:	call   a69570 <CSoundBank::addSample(int, long long)>
  889c0b:	lea    0x70(%rsp),%r14
  889c10:	lea    0x3a8(%rsp),%rdx
  889c18:	mov    $0xfa0b68,%esi
  889c1d:	mov    %r14,%rdi
  889c20:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889c25:	mov    0x1b0(%rbp),%rdi
  889c2c:	mov    $0x1480a48,%edx
  889c31:	mov    %r14,%rsi
  889c34:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889c39:	mov    %rax,%rsi
  889c3c:	mov    %r12,%rdi
  889c3f:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889c44:	mov    0x70(%rsp),%rdi
  889c49:	sub    $0x18,%rdi
  889c4d:	cmp    %rdi,%rbx
  889c50:	jne    88acd5 <CEquipment::unitInit(CDataGroup*, bool)+0x1bc5>
  889c56:	lea    0x60(%rsp),%r14
  889c5b:	mov    %r12,%rsi
  889c5e:	mov    %r14,%rdi
  889c61:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889c66:	mov    %r14,%rsi
  889c69:	mov    %r13,%rdi
  889c6c:	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889c71:	mov    0x60(%rsp),%rdi
  889c76:	sub    $0x18,%rdi
  889c7a:	cmp    %rdi,%rbx
  889c7d:	jne    88ad06 <CEquipment::unitInit(CDataGroup*, bool)+0x1bf6>
  889c83:	test   %rax,%rax
  889c86:	je     889c9d <CEquipment::unitInit(CDataGroup*, bool)+0xb8d>
  889c88:	mov    0x20(%rax),%rdx
  889c8c:	mov    0x1d8(%rbp),%rdi
  889c93:	mov    $0x14,%esi
  889c98:	call   a69570 <CSoundBank::addSample(int, long long)>
  889c9d:	lea    0x40(%rsp),%r13
  889ca2:	lea    0x3a7(%rsp),%rdx
  889caa:	mov    $0xfcf248,%esi
  889caf:	mov    %r13,%rdi
  889cb2:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889cb7:	mov    0x10(%rsp),%rdi
  889cbc:	mov    $0x1001608,%edx
  889cc1:	mov    %r13,%rsi
  889cc4:	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  889cc9:	lea    0x50(%rsp),%rdi
  889cce:	mov    %rax,%rsi
  889cd1:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  889cd6:	mov    0x40(%rsp),%rdi
  889cdb:	sub    $0x18,%rdi
  889cdf:	cmp    %rdi,%rbx
  889ce2:	jne    88ad67 <CEquipment::unitInit(CDataGroup*, bool)+0x1c57>
  889ce8:	mov    0x50(%rsp),%rax
  889ced:	cmpq   $0x0,-0x18(%rax)
  889cf2:	lea    -0x18(%rax),%rdi
  889cf6:	je     889cff <CEquipment::unitInit(CDataGroup*, bool)+0xbef>
  889cf8:	movb   $0x1,0x430(%rbp)
  889cff:	cmp    %rdi,%rbx
  889d02:	jne    88ad93 <CEquipment::unitInit(CDataGroup*, bool)+0x1c83>
  889d08:	mov    0x120(%rsp),%rdi
  889d10:	sub    $0x18,%rdi
  889d14:	cmp    %rdi,%rbx
  889d17:	jne    88add5 <CEquipment::unitInit(CDataGroup*, bool)+0x1cc5>
  889d1d:	mov    0x1e0(%rsp),%rdi
  889d25:	sub    $0x18,%rdi
  889d29:	cmp    %rdi,%rbx
  889d2c:	jne    88ae01 <CEquipment::unitInit(CDataGroup*, bool)+0x1cf1>
  889d32:	mov    0x200(%rsp),%rdi
  889d3a:	sub    $0x18,%rdi
  889d3e:	cmp    %rdi,%rbx
  889d41:	jne    88ae43 <CEquipment::unitInit(CDataGroup*, bool)+0x1d33>
  889d47:	mov    0x330(%rsp),%rdi
  889d4f:	sub    $0x18,%rdi
  889d53:	cmp    %rdi,%rbx
  889d56:	jne    88ae6f <CEquipment::unitInit(CDataGroup*, bool)+0x1d5f>
  889d5c:	add    $0x3c8,%rsp
  889d63:	pop    %rbx
  889d64:	pop    %rbp
  889d65:	pop    %r12
  889d67:	pop    %r13
  889d69:	pop    %r14
  889d6b:	pop    %r15
  889d6d:	ret
  889d6e:	xchg   %ax,%ax
  889d70:	cmp    $0xffffffff,%r13d
  889d74:	je     8892de <CEquipment::unitInit(CDataGroup*, bool)+0x1ce>
  889d7a:	lea    0x1(%r13),%eax
  889d7e:	cmp    %eax,%r15d
  889d81:	jle    8892de <CEquipment::unitInit(CDataGroup*, bool)+0x1ce>
  889d87:	mov    $0x1001608,%edi
  889d8c:	call   554608 <wcslen@plt>
  889d91:	lea    0x1(%r15),%edx
  889d95:	mov    %rax,%r8
  889d98:	mov    $0x1001608,%ecx
  889d9d:	mov    %r14,%rsi
  889da0:	mov    %r12,%rdi
  889da3:	sub    %r13d,%edx
  889da6:	movslq %edx,%rdx
  889da9:	call   554158 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::replace(unsigned long, unsigned long, wchar_t const*, unsigned long)@plt>
  889dae:	jmp    8892de <CEquipment::unitInit(CDataGroup*, bool)+0x1ce>
  889db3:	nopl   0x0(%rax,%rax,1)
  889db8:	cmp    $0xffffffff,%r13d
  889dbc:	je     8891ec <CEquipment::unitInit(CDataGroup*, bool)+0xdc>
  889dc2:	lea    0x1(%r13),%eax
  889dc6:	cmp    %eax,%r15d
  889dc9:	jle    8891ec <CEquipment::unitInit(CDataGroup*, bool)+0xdc>
  889dcf:	mov    $0x1001608,%edi
  889dd4:	call   554608 <wcslen@plt>
  889dd9:	lea    0x1(%r15),%edx
  889ddd:	mov    %rax,%r8
  889de0:	mov    $0x1001608,%ecx
  889de5:	mov    %r14,%rsi
  889de8:	mov    %r12,%rdi
  889deb:	sub    %r13d,%edx
  889dee:	movslq %edx,%rdx
  889df1:	call   554158 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::replace(unsigned long, unsigned long, wchar_t const*, unsigned long)@plt>
  889df6:	jmp    8891ec <CEquipment::unitInit(CDataGroup*, bool)+0xdc>
  889dfb:	nopl   0x0(%rax,%rax,1)
  889e00:	mov    %r14,%rsi
  889e03:	call   5553e8 <wmemcmp@plt>
  889e08:	test   %eax,%eax
  889e0a:	sete   %al
  889e0d:	jmp    88962d <CEquipment::unitInit(CDataGroup*, bool)+0x51d>
  889e12:	nopw   0x0(%rax,%rax,1)
  889e18:	xor    %r13d,%r13d
  889e1b:	cmpq   $0x0,0x68(%rbp)
  889e20:	je     889e2e <CEquipment::unitInit(CDataGroup*, bool)+0xd1e>
  889e22:	call   a54490 <CMasterResourceManager::getSingleton()>
  889e27:	mov    0x98(%rax),%r13
  889e2e:	xor    %ecx,%ecx
  889e30:	xor    %edx,%edx
  889e32:	xor    %esi,%esi
  889e34:	mov    $0xd0,%edi
  889e39:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  889e3e:	xor    %edx,%edx
  889e40:	mov    %r13,%rsi
  889e43:	mov    %rax,%rdi
  889e46:	mov    %rax,%r12
  889e49:	call   a68be0 <CSoundBank::CSoundBank(CSoundManager&, bool)>
  889e4e:	mov    %r12,0x1d8(%rbp)
  889e55:	jmp    8898e1 <CEquipment::unitInit(CDataGroup*, bool)+0x7d1>
  889e5a:	nopw   0x0(%rax,%rax,1)
  889e60:	lea    0x200(%rsp),%rdi
  889e68:	call   c8ddf0 <STRINGS::GetInt(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889e6d:	mov    %eax,0x248(%rbp)
  889e73:	jmp    889597 <CEquipment::unitInit(CDataGroup*, bool)+0x487>
  889e78:	nopl   0x0(%rax,%rax,1)
  889e80:	mov    $0x36,%esi
  889e85:	mov    %rbp,%rdi
  889e88:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  889e8d:	test   %al,%al
  889e8f:	jne    88a1e7 <CEquipment::unitInit(CDataGroup*, bool)+0x10d7>
  889e95:	xor    %esi,%esi
  889e97:	mov    %rbp,%rdi
  889e9a:	call   8845c0 <CEquipment::enchant(bool)>
  889e9f:	mov    $0x78,%esi
  889ea4:	mov    %rbp,%rdi
  889ea7:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  889eac:	test   %al,%al
  889eae:	jne    889f0b <CEquipment::unitInit(CDataGroup*, bool)+0xdfb>
  889eb0:	xor    %r13d,%r13d
  889eb3:	cmpb   $0x0,0x348(%rbp)
  889eba:	jne    8898b2 <CEquipment::unitInit(CDataGroup*, bool)+0x7a2>
  889ec0:	lea    0x130(%rsp),%r12
  889ec8:	lea    0x3ae(%rsp),%rdx
  889ed0:	mov    $0xfcffb8,%esi
  889ed5:	mov    %r12,%rdi
  889ed8:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  889edd:	mov    0x1b0(%rbp),%rdi
  889ee4:	xor    %edx,%edx
  889ee6:	mov    %r12,%rsi
  889ee9:	mov    $0x1,%r13d
  889eef:	call   c5f340 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)>
  889ef4:	test   %al,%al
  889ef6:	mov    %r12,%rdi
  889ef9:	setne  %r13b
  889efd:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  889f02:	test   %r13b,%r13b
  889f05:	je     8898b2 <CEquipment::unitInit(CDataGroup*, bool)+0x7a2>
  889f0b:	movb   $0x1,0x348(%rbp)
  889f12:	jmp    8898b2 <CEquipment::unitInit(CDataGroup*, bool)+0x7a2>
  889f17:	nopw   0x0(%rax,%rax,1)
  889f20:	call   5553e8 <wmemcmp@plt>
  889f25:	test   %eax,%eax
  889f27:	jne    88934f <CEquipment::unitInit(CDataGroup*, bool)+0x23f>
  889f2d:	lea    0x220(%rsp),%r13
  889f35:	lea    0x40(%rbp),%rdx
  889f39:	mov    $0xfd0490,%esi
  889f3e:	mov    %r13,%rdi
  889f41:	call   56b060 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(wchar_t const*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  889f46:	lea    0x210(%rsp),%r12
  889f4e:	mov    0x220(%rsp),%rsi
  889f56:	mov    %r12,%rdi
  889f59:	call   c8e350 <STRINGS::StringConvertToNarrow(wchar_t const*)>
  889f5e:	call   554918 <Ogre::LogManager::getSingleton()@plt>
  889f63:	xor    %ecx,%ecx
  889f65:	mov    $0x2,%edx
  889f6a:	mov    %r12,%rsi
  889f6d:	mov    %rax,%rdi
  889f70:	call   554e68 <Ogre::LogManager::logMessage(std::string const&, Ogre::LogMessageLevel, bool)@plt>
  889f75:	mov    0x210(%rsp),%rdi
  889f7d:	sub    $0x18,%rdi
  889f81:	cmp    $0x1423a20,%rdi
  889f88:	jne    88a476 <CEquipment::unitInit(CDataGroup*, bool)+0x1366>
  889f8e:	mov    0x220(%rsp),%rdi
  889f96:	sub    $0x18,%rdi
  889f9a:	cmp    %rdi,%rbx
  889f9d:	je     88951f <CEquipment::unitInit(CDataGroup*, bool)+0x40f>
  889fa3:	mov    $0x5541c8,%eax
  889fa8:	test   %rax,%rax
  889fab:	je     88a468 <CEquipment::unitInit(CDataGroup*, bool)+0x1358>
  889fb1:	or     $0xffffffff,%eax
  889fb4:	lock xadd %eax,0x10(%rdi)
  889fb9:	test   %eax,%eax
  889fbb:	jg     88951f <CEquipment::unitInit(CDataGroup*, bool)+0x40f>
  889fc1:	lea    0x392(%rsp),%rsi
  889fc9:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  889fce:	jmp    88951f <CEquipment::unitInit(CDataGroup*, bool)+0x40f>
  889fd3:	nopl   0x0(%rax,%rax,1)
  889fd8:	mov    0x28(%rax),%rax
  889fdc:	mov    (%rax),%rax
  889fdf:	test   %rax,%rax
  889fe2:	je     8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  889fe8:	mov    0x78(%rax),%rax
  889fec:	test   %rax,%rax
  889fef:	je     8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  889ff5:	mov    0x38(%rax),%rax
  889ff9:	test   %rax,%rax
  889ffc:	je     8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  88a002:	lea    0x40(%rax),%rsi
  88a006:	lea    0x2b0(%rsp),%rdi
  88a00e:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88a013:	lea    0x2a0(%rsp),%r12
  88a01b:	lea    0x3ba(%rsp),%rdx
  88a023:	mov    $0xfb2460,%esi
  88a028:	movq   $0x0,0x20(%rsp)
  88a031:	movq   $0x0,0x28(%rsp)
  88a03a:	mov    %r12,%rdi
  88a03d:	movq   $0x0,0x30(%rsp)
  88a046:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88a04b:	mov    0x1b0(%rbp),%rdi
  88a052:	lea    0x20(%rsp),%rdx
  88a057:	mov    %r12,%rsi
  88a05a:	call   c5f910 <CDataGroup::GetDataGroupsMatchingName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::vector<CDataGroup*, std::allocator<CDataGroup*> >*)>
  88a05f:	mov    0x2a0(%rsp),%rdi
  88a067:	mov    %eax,0xc(%rsp)
  88a06b:	sub    $0x18,%rdi
  88a06f:	cmp    %rdi,%rbx
  88a072:	jne    88a57c <CEquipment::unitInit(CDataGroup*, bool)+0x146c>
  88a078:	lea    0x290(%rsp),%rdi
  88a080:	mov    $0x1480a48,%esi
  88a085:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88a08a:	mov    0xc(%rsp),%r8d
  88a08f:	test   %r8d,%r8d
  88a092:	je     88a290 <CEquipment::unitInit(CDataGroup*, bool)+0x1180>
  88a098:	xor    %r12d,%r12d
  88a09b:	xor    %r13d,%r13d
  88a09e:	lea    0x270(%rsp),%r15
  88a0a6:	jmp    88a13e <CEquipment::unitInit(CDataGroup*, bool)+0x102e>
  88a0ab:	nopl   0x0(%rax,%rax,1)
  88a0b0:	lea    0x3b8(%rsp),%rdx
  88a0b8:	lea    0x260(%rsp),%rdi
  88a0c0:	mov    $0xfd03d0,%esi
  88a0c5:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88a0ca:	lea    0x260(%rsp),%rsi
  88a0d2:	mov    $0x1480a48,%edx
  88a0d7:	mov    %r14,%rdi
  88a0da:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88a0df:	mov    (%rax),%rdi
  88a0e2:	mov    0xbf695f(%rip),%rsi        # 1480a48 <EMPTY_WSTRING>
  88a0e9:	xor    %eax,%eax
  88a0eb:	mov    -0x18(%rdi),%rdx
  88a0ef:	cmp    -0x18(%rsi),%rdx
  88a0f3:	je     88a280 <CEquipment::unitInit(CDataGroup*, bool)+0x1170>
  88a0f9:	mov    0x260(%rsp),%rdi
  88a101:	sub    $0x18,%rdi
  88a105:	cmp    %rdi,%rbx
  88a108:	jne    88a3c8 <CEquipment::unitInit(CDataGroup*, bool)+0x12b8>
  88a10e:	test   %al,%al
  88a110:	je     88a1f8 <CEquipment::unitInit(CDataGroup*, bool)+0x10e8>
  88a116:	mov    0x280(%rsp),%rcx
  88a11e:	sub    $0x18,%rcx
  88a122:	cmp    %rcx,%rbx
  88a125:	jne    88a365 <CEquipment::unitInit(CDataGroup*, bool)+0x1255>
  88a12b:	add    $0x1,%r13d
  88a12f:	add    $0x8,%r12
  88a133:	cmp    %r13d,0xc(%rsp)
  88a138:	jbe    88a290 <CEquipment::unitInit(CDataGroup*, bool)+0x1180>
  88a13e:	mov    0x20(%rsp),%rax
  88a143:	lea    0x3b9(%rsp),%rdx
  88a14b:	mov    $0xfb3b74,%esi
  88a150:	mov    %r15,%rdi
  88a153:	mov    (%rax,%r12,1),%r14
  88a157:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88a15c:	mov    $0x1001608,%edx
  88a161:	mov    %r15,%rsi
  88a164:	mov    %r14,%rdi
  88a167:	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  88a16c:	lea    0x280(%rsp),%rdi
  88a174:	mov    %rax,%rsi
  88a177:	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88a17c:	mov    0x270(%rsp),%rdi
  88a184:	sub    $0x18,%rdi
  88a188:	cmp    %rdi,%rbx
  88a18b:	jne    88a398 <CEquipment::unitInit(CDataGroup*, bool)+0x1288>
  88a191:	lea    0x2b0(%rsp),%rdi
  88a199:	mov    $0x1001608,%esi
  88a19e:	call   554ef8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::compare(wchar_t const*) const@plt>
  88a1a3:	test   %eax,%eax
  88a1a5:	je     88a0b0 <CEquipment::unitInit(CDataGroup*, bool)+0xfa0>
  88a1ab:	mov    0x280(%rsp),%rdi
  88a1b3:	mov    0x2b0(%rsp),%rsi
  88a1bb:	mov    -0x18(%rdi),%rdx
  88a1bf:	cmp    -0x18(%rsi),%rdx
  88a1c3:	lea    -0x18(%rdi),%rcx
  88a1c7:	jne    88a122 <CEquipment::unitInit(CDataGroup*, bool)+0x1012>
  88a1cd:	mov    %rcx,(%rsp)
  88a1d1:	call   5553e8 <wmemcmp@plt>
  88a1d6:	test   %eax,%eax
  88a1d8:	mov    (%rsp),%rcx
  88a1dc:	jne    88a122 <CEquipment::unitInit(CDataGroup*, bool)+0x1012>
  88a1e2:	jmp    88a0b0 <CEquipment::unitInit(CDataGroup*, bool)+0xfa0>
  88a1e7:	movb   $0x0,0x348(%rbp)
  88a1ee:	jmp    889e95 <CEquipment::unitInit(CDataGroup*, bool)+0xd85>
  88a1f3:	nopl   0x0(%rax,%rax,1)
  88a1f8:	lea    0x3b7(%rsp),%rdx
  88a200:	lea    0x250(%rsp),%rdi
  88a208:	mov    $0xfd03d0,%esi
  88a20d:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  88a212:	lea    0x250(%rsp),%rsi
  88a21a:	mov    $0x1480a48,%edx
  88a21f:	mov    %r14,%rdi
  88a222:	call   c5f370 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  88a227:	lea    0x310(%rsp),%rdi
  88a22f:	mov    %rax,%rsi
  88a232:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  88a237:	mov    0x250(%rsp),%rdi
  88a23f:	sub    $0x18,%rdi
  88a243:	cmp    %rdi,%rbx
  88a246:	je     88a116 <CEquipment::unitInit(CDataGroup*, bool)+0x1006>
  88a24c:	mov    $0x5541c8,%eax
  88a251:	test   %rax,%rax
  88a254:	je     88b07a <CEquipment::unitInit(CDataGroup*, bool)+0x1f6a>
  88a25a:	or     $0xffffffff,%eax
  88a25d:	lock xadd %eax,0x10(%rdi)
  88a262:	test   %eax,%eax
  88a264:	jg     88a116 <CEquipment::unitInit(CDataGroup*, bool)+0x1006>
  88a26a:	lea    0x39a(%rsp),%rsi
  88a272:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a277:	jmp    88a116 <CEquipment::unitInit(CDataGroup*, bool)+0x1006>
  88a27c:	nopl   0x0(%rax)
  88a280:	call   5553e8 <wmemcmp@plt>
  88a285:	test   %eax,%eax
  88a287:	sete   %al
  88a28a:	jmp    88a0f9 <CEquipment::unitInit(CDataGroup*, bool)+0xfe9>
  88a28f:	nop
  88a290:	mov    0x290(%rsp),%rdi
  88a298:	sub    $0x18,%rdi
  88a29c:	cmp    %rdi,%rbx
  88a29f:	jne    88b088 <CEquipment::unitInit(CDataGroup*, bool)+0x1f78>
  88a2a5:	mov    0x20(%rsp),%rdi
  88a2aa:	test   %rdi,%rdi
  88a2ad:	je     88a2b4 <CEquipment::unitInit(CDataGroup*, bool)+0x11a4>
  88a2af:	call   553f18 <operator delete(void*)@plt>
  88a2b4:	mov    0x2b0(%rsp),%rdi
  88a2bc:	sub    $0x18,%rdi
  88a2c0:	cmp    %rdi,%rbx
  88a2c3:	je     8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  88a2c9:	mov    $0x5541c8,%eax
  88a2ce:	test   %rax,%rax
  88a2d1:	je     88b166 <CEquipment::unitInit(CDataGroup*, bool)+0x2056>
  88a2d7:	or     $0xffffffff,%eax
  88a2da:	lock xadd %eax,0x10(%rdi)
  88a2df:	test   %eax,%eax
  88a2e1:	jg     8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  88a2e7:	lea    0x397(%rsp),%rsi
  88a2ef:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a2f4:	jmp    8894a5 <CEquipment::unitInit(CDataGroup*, bool)+0x395>
  88a2f9:	nopl   0x0(%rax)
  88a300:	xor    %ecx,%ecx
  88a302:	xor    %edx,%edx
  88a304:	xor    %esi,%esi
  88a306:	mov    $0x138,%edi
  88a30b:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  88a310:	xorps  %xmm1,%xmm1
  88a313:	xor    %edx,%edx
  88a315:	movss  0xc(%rsp),%xmm0
  88a31b:	mov    $0x3e,%esi
  88a320:	movss  0x71a4d4(%rip),%xmm2        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  88a328:	mov    %rax,%rdi
  88a32b:	ucomiss %xmm1,%xmm0
  88a32e:	movaps %xmm0,%xmm1
  88a331:	seta   %dl
  88a334:	movss  0x73e680(%rip),%xmm0        # fc89bc <typeinfo name for CEffectDisplayValues+0x1c>
  88a33c:	xor    %r8d,%r8d
  88a33f:	xor    %ecx,%ecx
  88a341:	mov    %rax,%r12
  88a344:	call   7dd6f0 <CEffect::CEffect(EEFFECT_TYPE, bool, EEFFECT_ACTIVATION, float, float, float, bool)>
  88a349:	mov    %r12,%rsi
  88a34c:	mov    %rbp,%rdi
  88a34f:	call   7ff0d0 <CBaseUnit::addNewEffect(CEffect*)>
  88a354:	jmp    889893 <CEquipment::unitInit(CDataGroup*, bool)+0x783>
  88a359:	mov    %r12d,0x260(%rbp)
  88a360:	jmp    889648 <CEquipment::unitInit(CDataGroup*, bool)+0x538>
  88a365:	mov    $0x5541c8,%eax
  88a36a:	test   %rax,%rax
  88a36d:	je     88a4f5 <CEquipment::unitInit(CDataGroup*, bool)+0x13e5>
  88a373:	or     $0xffffffff,%eax
  88a376:	lock xadd %eax,0x10(%rcx)
  88a37b:	test   %eax,%eax
  88a37d:	jg     88a12b <CEquipment::unitInit(CDataGroup*, bool)+0x101b>
  88a383:	lea    0x399(%rsp),%rsi
  88a38b:	mov    %rcx,%rdi
  88a38e:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a393:	jmp    88a12b <CEquipment::unitInit(CDataGroup*, bool)+0x101b>
  88a398:	mov    $0x5541c8,%eax
  88a39d:	test   %rax,%rax
  88a3a0:	je     88a54e <CEquipment::unitInit(CDataGroup*, bool)+0x143e>
  88a3a6:	or     $0xffffffff,%eax
  88a3a9:	lock xadd %eax,0x10(%rdi)
  88a3ae:	test   %eax,%eax
  88a3b0:	jg     88a191 <CEquipment::unitInit(CDataGroup*, bool)+0x1081>
  88a3b6:	lea    0x39c(%rsp),%rsi
  88a3be:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a3c3:	jmp    88a191 <CEquipment::unitInit(CDataGroup*, bool)+0x1081>
  88a3c8:	mov    $0x5541c8,%edx
  88a3cd:	test   %rdx,%rdx
  88a3d0:	je     88a45a <CEquipment::unitInit(CDataGroup*, bool)+0x134a>
  88a3d6:	or     $0xffffffff,%edx
  88a3d9:	lock xadd %edx,0x10(%rdi)
  88a3de:	test   %edx,%edx
  88a3e0:	jg     88a10e <CEquipment::unitInit(CDataGroup*, bool)+0xffe>
  88a3e6:	lea    0x39b(%rsp),%rsi
  88a3ee:	mov    %al,(%rsp)
  88a3f1:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a3f6:	movzbl (%rsp),%eax
  88a3fa:	jmp    88a10e <CEquipment::unitInit(CDataGroup*, bool)+0xffe>
  88a3ff:	mov    %rax,%rbp
  88a402:	lea    0x280(%rsp),%rdi
  88a40a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a40f:	lea    0x290(%rsp),%rdi
  88a417:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a41c:	mov    0x20(%rsp),%rdi
  88a421:	test   %rdi,%rdi
  88a424:	je     88a42b <CEquipment::unitInit(CDataGroup*, bool)+0x131b>
  88a426:	call   553f18 <operator delete(void*)@plt>
  88a42b:	lea    0x2b0(%rsp),%rdi
  88a433:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a438:	lea    0x310(%rsp),%rdi
  88a440:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a445:	lea    0x330(%rsp),%rdi
  88a44d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a452:	mov    %rbp,%rdi
  88a455:	call   554498 <_Unwind_Resume@plt>
  88a45a:	mov    0x10(%rdi),%edx
  88a45d:	lea    -0x1(%rdx),%ecx
  88a460:	mov    %ecx,0x10(%rdi)
  88a463:	jmp    88a3de <CEquipment::unitInit(CDataGroup*, bool)+0x12ce>
  88a468:	mov    0x10(%rdi),%eax
  88a46b:	lea    -0x1(%rax),%edx
  88a46e:	mov    %edx,0x10(%rdi)
  88a471:	jmp    889fb9 <CEquipment::unitInit(CDataGroup*, bool)+0xea9>
  88a476:	mov    $0x5541c8,%eax
  88a47b:	test   %rax,%rax
  88a47e:	je     88a4b7 <CEquipment::unitInit(CDataGroup*, bool)+0x13a7>
  88a480:	or     $0xffffffff,%eax
  88a483:	lock xadd %eax,0x10(%rdi)
  88a488:	test   %eax,%eax
  88a48a:	jg     889f8e <CEquipment::unitInit(CDataGroup*, bool)+0xe7e>
  88a490:	lea    0x393(%rsp),%rsi
  88a498:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  88a49d:	jmp    889f8e <CEquipment::unitInit(CDataGroup*, bool)+0xe7e>
  88a4a2:	mov    %r12,%rdi
  88a4a5:	mov    %rax,%rbp
  88a4a8:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  88a4ad:	mov    %r13,%rdi
  88a4b0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a4b5:	jmp    88a445 <CEquipment::unitInit(CDataGroup*, bool)+0x1335>
  88a4b7:	mov    0x10(%rdi),%eax
  88a4ba:	lea    -0x1(%rax),%edx
  88a4bd:	mov    %edx,0x10(%rdi)
  88a4c0:	jmp    88a488 <CEquipment::unitInit(CDataGroup*, bool)+0x1378>
  88a4c2:	mov    %rax,%rbp
  88a4c5:	jmp    88a4ad <CEquipment::unitInit(CDataGroup*, bool)+0x139d>
  88a4c7:	mov    %rax,%rbp
  88a4ca:	jmp    88a445 <CEquipment::unitInit(CDataGroup*, bool)+0x1335>
  88a4cf:	lea    0x260(%rsp),%rdi
  88a4d7:	mov    %rax,%rbp
  88a4da:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a4df:	jmp    88a402 <CEquipment::unitInit(CDataGroup*, bool)+0x12f2>
  88a4e4:	jmp    88a3ff <CEquipment::unitInit(CDataGroup*, bool)+0x12ef>
  88a4e9:	nopl   0x0(%rax)
  88a4f0:	jmp    88a3ff <CEquipment::unitInit(CDataGroup*, bool)+0x12ef>
  88a4f5:	mov    0x10(%rcx),%eax
  88a4f8:	lea    -0x1(%rax),%edx
  88a4fb:	mov    %edx,0x10(%rcx)
  88a4fe:	xchg   %ax,%ax
  88a500:	jmp    88a37b <CEquipment::unitInit(CDataGroup*, bool)+0x126b>
  88a505:	mov    %rax,%rbp
  88a508:	lea    0x1e0(%rsp),%rdi
  88a510:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a515:	lea    0x200(%rsp),%rdi
  88a51d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a522:	jmp    88a445 <CEquipment::unitInit(CDataGroup*, bool)+0x1335>
  88a527:	test   %r13b,%r13b
  88a52a:	mov    %rax,%rbp
  88a52d:	je     88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88a52f:	mov    %r12,%rdi
  88a532:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a537:	jmp    88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88a539:	lea    0x250(%rsp),%rdi
  88a541:	mov    %rax,%rbp
  88a544:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a549:	jmp    88a402 <CEquipment::unitInit(CDataGroup*, bool)+0x12f2>
  88a54e:	mov    0x10(%rdi),%eax
  88a551:	lea    -0x1(%rax),%edx
  88a554:	mov    %edx,0x10(%rdi)
  88a557:	jmp    88a3ae <CEquipment::unitInit(CDataGroup*, bool)+0x129e>
  88a55c:	mov    %r15,%rdi
  88a55f:	mov    %rax,%rbp
  88a562:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a567:	jmp    88a40f <CEquipment::unitInit(CDataGroup*, bool)+0x12ff>
  88a56c:	mov    %rax,%rbp
  88a56f:	jmp    88a40f <CEquipment::unitInit(CDataGroup*, bool)+0x12ff>
  88a574:	mov    %rax,%rbp
  88a577:	jmp    88a41c <CEquipment::unitInit(CDataGroup*, bool)+0x130c>
  88a57c:	mov    $0x5541c8,%eax
  88a581:	test   %rax,%rax
  88a584:	je     88a601 <CEquipment::unitInit(CDataGroup*, bool)+0x14f1>
  88a586:	or     $0xffffffff,%eax
  88a589:	lock xadd %eax,0x10(%rdi)
  88a58e:	test   %eax,%eax
  88a590:	jg     88a078 <CEquipment::unitInit(CDataGroup*, bool)+0xf68>
  88a596:	lea    0x39d(%rsp),%rsi
  88a59e:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a5a3:	jmp    88a078 <CEquipment::unitInit(CDataGroup*, bool)+0xf68>
  88a5a8:	mov    %r12,%rdi
  88a5ab:	mov    %rax,%rbp
  88a5ae:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a5b3:	jmp    88a41c <CEquipment::unitInit(CDataGroup*, bool)+0x130c>
  88a5b8:	mov    %r14,%rdi
  88a5bb:	mov    %rax,%rbp
  88a5be:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a5c3:	jmp    88a52f <CEquipment::unitInit(CDataGroup*, bool)+0x141f>
  88a5c8:	mov    $0x5541c8,%edx
  88a5cd:	test   %rdx,%rdx
  88a5d0:	je     88a60c <CEquipment::unitInit(CDataGroup*, bool)+0x14fc>
  88a5d2:	or     $0xffffffff,%edx
  88a5d5:	lock xadd %edx,0x10(%rdi)
  88a5da:	test   %edx,%edx
  88a5dc:	jg     889a17 <CEquipment::unitInit(CDataGroup*, bool)+0x907>
  88a5e2:	lea    0x383(%rsp),%rsi
  88a5ea:	mov    %rax,(%rsp)
  88a5ee:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a5f3:	mov    (%rsp),%rax
  88a5f7:	jmp    889a17 <CEquipment::unitInit(CDataGroup*, bool)+0x907>
  88a5fc:	jmp    88a574 <CEquipment::unitInit(CDataGroup*, bool)+0x1464>
  88a601:	mov    0x10(%rdi),%eax
  88a604:	lea    -0x1(%rax),%edx
  88a607:	mov    %edx,0x10(%rdi)
  88a60a:	jmp    88a58e <CEquipment::unitInit(CDataGroup*, bool)+0x147e>
  88a60c:	mov    0x10(%rdi),%edx
  88a60f:	lea    -0x1(%rdx),%ecx
  88a612:	mov    %ecx,0x10(%rdi)
  88a615:	jmp    88a5da <CEquipment::unitInit(CDataGroup*, bool)+0x14ca>
  88a617:	mov    %rax,%rbp
  88a61a:	jmp    88a52f <CEquipment::unitInit(CDataGroup*, bool)+0x141f>
  88a61f:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a621:	mov    $0x5541c8,%eax
  88a626:	test   %rax,%rax
  88a629:	je     88a652 <CEquipment::unitInit(CDataGroup*, bool)+0x1542>
  88a62b:	or     $0xffffffff,%eax
  88a62e:	lock xadd %eax,0x10(%rdi)
  88a633:	test   %eax,%eax
  88a635:	jg     889a82 <CEquipment::unitInit(CDataGroup*, bool)+0x972>
  88a63b:	lea    0x382(%rsp),%rsi
  88a643:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a648:	jmp    889a82 <CEquipment::unitInit(CDataGroup*, bool)+0x972>
  88a64d:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a652:	mov    0x10(%rdi),%eax
  88a655:	lea    -0x1(%rax),%edx
  88a658:	mov    %edx,0x10(%rdi)
  88a65b:	jmp    88a633 <CEquipment::unitInit(CDataGroup*, bool)+0x1523>
  88a65d:	mov    $0x5541c8,%edx
  88a662:	test   %rdx,%rdx
  88a665:	je     88a693 <CEquipment::unitInit(CDataGroup*, bool)+0x1583>
  88a667:	or     $0xffffffff,%edx
  88a66a:	lock xadd %edx,0x10(%rdi)
  88a66f:	test   %edx,%edx
  88a671:	jg     889ab5 <CEquipment::unitInit(CDataGroup*, bool)+0x9a5>
  88a677:	lea    0x381(%rsp),%rsi
  88a67f:	mov    %rax,(%rsp)
  88a683:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a688:	mov    (%rsp),%rax
  88a68c:	jmp    889ab5 <CEquipment::unitInit(CDataGroup*, bool)+0x9a5>
  88a691:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a693:	mov    0x10(%rdi),%edx
  88a696:	lea    -0x1(%rdx),%ecx
  88a699:	mov    %ecx,0x10(%rdi)
  88a69c:	jmp    88a66f <CEquipment::unitInit(CDataGroup*, bool)+0x155f>
  88a69e:	xchg   %ax,%ax
  88a6a0:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a6a5:	mov    $0x5541c8,%eax
  88a6aa:	test   %rax,%rax
  88a6ad:	je     88a9c5 <CEquipment::unitInit(CDataGroup*, bool)+0x18b5>
  88a6b3:	or     $0xffffffff,%eax
  88a6b6:	lock xadd %eax,0x10(%rdi)
  88a6bb:	test   %eax,%eax
  88a6bd:	jg     889b20 <CEquipment::unitInit(CDataGroup*, bool)+0xa10>
  88a6c3:	lea    0x380(%rsp),%rsi
  88a6cb:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a6d0:	jmp    889b20 <CEquipment::unitInit(CDataGroup*, bool)+0xa10>
  88a6d5:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a6da:	mov    %rax,%rbp
  88a6dd:	nopl   (%rax)
  88a6e0:	jmp    88a452 <CEquipment::unitInit(CDataGroup*, bool)+0x1342>
  88a6e5:	mov    $0x5541c8,%eax
  88a6ea:	test   %rax,%rax
  88a6ed:	je     88a723 <CEquipment::unitInit(CDataGroup*, bool)+0x1613>
  88a6ef:	or     $0xffffffff,%eax
  88a6f2:	lock xadd %eax,0x10(%rdi)
  88a6f7:	test   %eax,%eax
  88a6f9:	jg     8891a1 <CEquipment::unitInit(CDataGroup*, bool)+0x91>
  88a6ff:	lea    0x3a6(%rsp),%rsi
  88a707:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a70c:	jmp    8891a1 <CEquipment::unitInit(CDataGroup*, bool)+0x91>
  88a711:	mov    %rbx,%rdi
  88a714:	mov    %rax,%rbp
  88a717:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a71c:	jmp    88a452 <CEquipment::unitInit(CDataGroup*, bool)+0x1342>
  88a721:	jmp    88a6da <CEquipment::unitInit(CDataGroup*, bool)+0x15ca>
  88a723:	mov    0x10(%rdi),%eax
  88a726:	lea    -0x1(%rax),%edx
  88a729:	mov    %edx,0x10(%rdi)
  88a72c:	jmp    88a6f7 <CEquipment::unitInit(CDataGroup*, bool)+0x15e7>
  88a72e:	xchg   %ax,%ax
  88a730:	jmp    88a6da <CEquipment::unitInit(CDataGroup*, bool)+0x15ca>
  88a732:	mov    $0x5541c8,%eax
  88a737:	test   %rax,%rax
  88a73a:	je     88a768 <CEquipment::unitInit(CDataGroup*, bool)+0x1658>
  88a73c:	or     $0xffffffff,%eax
  88a73f:	lock xadd %eax,0x10(%rdi)
  88a744:	test   %eax,%eax
  88a746:	jg     889244 <CEquipment::unitInit(CDataGroup*, bool)+0x134>
  88a74c:	lea    0x3a5(%rsp),%rsi
  88a754:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a759:	jmp    889244 <CEquipment::unitInit(CDataGroup*, bool)+0x134>
  88a75e:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88a763:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a768:	mov    0x10(%rdi),%eax
  88a76b:	lea    -0x1(%rax),%edx
  88a76e:	mov    %edx,0x10(%rdi)
  88a771:	jmp    88a744 <CEquipment::unitInit(CDataGroup*, bool)+0x1634>
  88a773:	mov    $0x5541c8,%eax
  88a778:	test   %rax,%rax
  88a77b:	je     88a7a4 <CEquipment::unitInit(CDataGroup*, bool)+0x1694>
  88a77d:	or     $0xffffffff,%eax
  88a780:	lock xadd %eax,0x10(%rdi)
  88a785:	test   %eax,%eax
  88a787:	jg     889698 <CEquipment::unitInit(CDataGroup*, bool)+0x588>
  88a78d:	lea    0x38e(%rsp),%rsi
  88a795:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a79a:	jmp    889698 <CEquipment::unitInit(CDataGroup*, bool)+0x588>
  88a79f:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88a7a4:	mov    0x10(%rdi),%eax
  88a7a7:	lea    -0x1(%rax),%edx
  88a7aa:	mov    %edx,0x10(%rdi)
  88a7ad:	jmp    88a785 <CEquipment::unitInit(CDataGroup*, bool)+0x1675>
  88a7af:	nop
  88a7b0:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a7b5:	mov    $0x5541c8,%eax
  88a7ba:	test   %rax,%rax
  88a7bd:	je     88a833 <CEquipment::unitInit(CDataGroup*, bool)+0x1723>
  88a7bf:	or     $0xffffffff,%eax
  88a7c2:	lock xadd %eax,0x10(%rdi)
  88a7c7:	test   %eax,%eax
  88a7c9:	jg     8896e2 <CEquipment::unitInit(CDataGroup*, bool)+0x5d2>
  88a7cf:	lea    0x38d(%rsp),%rsi
  88a7d7:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a7dc:	jmp    8896e2 <CEquipment::unitInit(CDataGroup*, bool)+0x5d2>
  88a7e1:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88a7e6:	mov    %r13,%rdi
  88a7e9:	mov    %rax,%rbp
  88a7ec:	nopl   0x0(%rax)
  88a7f0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a7f5:	mov    %r14,%rdi
  88a7f8:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a7fd:	jmp    88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88a802:	mov    $0x5541c8,%eax
  88a807:	test   %rax,%rax
  88a80a:	je     88a83e <CEquipment::unitInit(CDataGroup*, bool)+0x172e>
  88a80c:	or     $0xffffffff,%eax
  88a80f:	lock xadd %eax,0x10(%rdi)
  88a814:	test   %eax,%eax
  88a816:	jg     88974b <CEquipment::unitInit(CDataGroup*, bool)+0x63b>
  88a81c:	lea    0x38c(%rsp),%rsi
  88a824:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a829:	jmp    88974b <CEquipment::unitInit(CDataGroup*, bool)+0x63b>
  88a82e:	mov    %rax,%rbp
  88a831:	jmp    88a7f5 <CEquipment::unitInit(CDataGroup*, bool)+0x16e5>
  88a833:	mov    0x10(%rdi),%eax
  88a836:	lea    -0x1(%rax),%edx
  88a839:	mov    %edx,0x10(%rdi)
  88a83c:	jmp    88a7c7 <CEquipment::unitInit(CDataGroup*, bool)+0x16b7>
  88a83e:	mov    0x10(%rdi),%eax
  88a841:	lea    -0x1(%rax),%edx
  88a844:	mov    %edx,0x10(%rdi)
  88a847:	jmp    88a814 <CEquipment::unitInit(CDataGroup*, bool)+0x1704>
  88a849:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a84e:	xchg   %ax,%ax
  88a850:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a855:	mov    $0x5541c8,%edx
  88a85a:	test   %rdx,%rdx
  88a85d:	nopl   (%rax)
  88a860:	je     88a891 <CEquipment::unitInit(CDataGroup*, bool)+0x1781>
  88a862:	or     $0xffffffff,%edx
  88a865:	lock xadd %edx,0x10(%rdi)
  88a86a:	test   %edx,%edx
  88a86c:	jg     889979 <CEquipment::unitInit(CDataGroup*, bool)+0x869>
  88a872:	lea    0x385(%rsp),%rsi
  88a87a:	mov    %rax,(%rsp)
  88a87e:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a883:	mov    (%rsp),%rax
  88a887:	jmp    889979 <CEquipment::unitInit(CDataGroup*, bool)+0x869>
  88a88c:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a891:	mov    0x10(%rdi),%edx
  88a894:	lea    -0x1(%rdx),%ecx
  88a897:	mov    %ecx,0x10(%rdi)
  88a89a:	jmp    88a86a <CEquipment::unitInit(CDataGroup*, bool)+0x175a>
  88a89c:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a8a1:	mov    $0x5541c8,%eax
  88a8a6:	test   %rax,%rax
  88a8a9:	je     88a909 <CEquipment::unitInit(CDataGroup*, bool)+0x17f9>
  88a8ab:	or     $0xffffffff,%eax
  88a8ae:	lock xadd %eax,0x10(%rdi)
  88a8b3:	test   %eax,%eax
  88a8b5:	jg     8899e4 <CEquipment::unitInit(CDataGroup*, bool)+0x8d4>
  88a8bb:	lea    0x384(%rsp),%rsi
  88a8c3:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a8c8:	jmp    8899e4 <CEquipment::unitInit(CDataGroup*, bool)+0x8d4>
  88a8cd:	mov    $0x5541c8,%eax
  88a8d2:	test   %rax,%rax
  88a8d5:	je     88a914 <CEquipment::unitInit(CDataGroup*, bool)+0x1804>
  88a8d7:	or     $0xffffffff,%eax
  88a8da:	lock xadd %eax,0x10(%rdi)
  88a8df:	test   %eax,%eax
  88a8e1:	jg     889293 <CEquipment::unitInit(CDataGroup*, bool)+0x183>
  88a8e7:	lea    0x3a4(%rsp),%rsi
  88a8ef:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a8f4:	jmp    889293 <CEquipment::unitInit(CDataGroup*, bool)+0x183>
  88a8f9:	mov    %r13,%rdi
  88a8fc:	mov    %rax,%rbp
  88a8ff:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88a904:	jmp    88a452 <CEquipment::unitInit(CDataGroup*, bool)+0x1342>
  88a909:	mov    0x10(%rdi),%eax
  88a90c:	lea    -0x1(%rax),%edx
  88a90f:	mov    %edx,0x10(%rdi)
  88a912:	jmp    88a8b3 <CEquipment::unitInit(CDataGroup*, bool)+0x17a3>
  88a914:	mov    0x10(%rdi),%eax
  88a917:	lea    -0x1(%rax),%edx
  88a91a:	mov    %edx,0x10(%rdi)
  88a91d:	jmp    88a8df <CEquipment::unitInit(CDataGroup*, bool)+0x17cf>
  88a91f:	mov    $0x5541c8,%eax
  88a924:	test   %rax,%rax
  88a927:	je     88a950 <CEquipment::unitInit(CDataGroup*, bool)+0x1840>
  88a929:	or     $0xffffffff,%eax
  88a92c:	lock xadd %eax,0x10(%rdi)
  88a931:	test   %eax,%eax
  88a933:	jg     889bbe <CEquipment::unitInit(CDataGroup*, bool)+0xaae>
  88a939:	lea    0x37e(%rsp),%rsi
  88a941:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a946:	jmp    889bbe <CEquipment::unitInit(CDataGroup*, bool)+0xaae>
  88a94b:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a950:	mov    0x10(%rdi),%eax
  88a953:	lea    -0x1(%rax),%edx
  88a956:	mov    %edx,0x10(%rdi)
  88a959:	jmp    88a931 <CEquipment::unitInit(CDataGroup*, bool)+0x1821>
  88a95b:	jmp    88a82e <CEquipment::unitInit(CDataGroup*, bool)+0x171e>
  88a960:	mov    $0x5541c8,%eax
  88a965:	test   %rax,%rax
  88a968:	je     88a9e3 <CEquipment::unitInit(CDataGroup*, bool)+0x18d3>
  88a96a:	or     $0xffffffff,%eax
  88a96d:	lock xadd %eax,0x10(%rdi)
  88a972:	test   %eax,%eax
  88a974:	jg     889946 <CEquipment::unitInit(CDataGroup*, bool)+0x836>
  88a97a:	lea    0x386(%rsp),%rsi
  88a982:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a987:	jmp    889946 <CEquipment::unitInit(CDataGroup*, bool)+0x836>
  88a98c:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88a991:	mov    $0x5541c8,%edx
  88a996:	test   %rdx,%rdx
  88a999:	je     88a9d3 <CEquipment::unitInit(CDataGroup*, bool)+0x18c3>
  88a99b:	or     $0xffffffff,%edx
  88a99e:	lock xadd %edx,0x10(%rdi)
  88a9a3:	test   %edx,%edx
  88a9a5:	jg     889b53 <CEquipment::unitInit(CDataGroup*, bool)+0xa43>
  88a9ab:	lea    0x37f(%rsp),%rsi
  88a9b3:	mov    %rax,(%rsp)
  88a9b7:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88a9bc:	mov    (%rsp),%rax
  88a9c0:	jmp    889b53 <CEquipment::unitInit(CDataGroup*, bool)+0xa43>
  88a9c5:	mov    0x10(%rdi),%eax
  88a9c8:	lea    -0x1(%rax),%edx
  88a9cb:	mov    %edx,0x10(%rdi)
  88a9ce:	jmp    88a6bb <CEquipment::unitInit(CDataGroup*, bool)+0x15ab>
  88a9d3:	mov    0x10(%rdi),%edx
  88a9d6:	lea    -0x1(%rdx),%ecx
  88a9d9:	mov    %ecx,0x10(%rdi)
  88a9dc:	jmp    88a9a3 <CEquipment::unitInit(CDataGroup*, bool)+0x1893>
  88a9de:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88a9e3:	mov    0x10(%rdi),%eax
  88a9e6:	lea    -0x1(%rax),%edx
  88a9e9:	mov    %edx,0x10(%rdi)
  88a9ec:	jmp    88a972 <CEquipment::unitInit(CDataGroup*, bool)+0x1862>
  88a9ee:	mov    $0x5541c8,%eax
  88a9f3:	test   %rax,%rax
  88a9f6:	je     88aa2a <CEquipment::unitInit(CDataGroup*, bool)+0x191a>
  88a9f8:	or     $0xffffffff,%eax
  88a9fb:	lock xadd %eax,0x10(%rdi)
  88aa00:	test   %eax,%eax
  88aa02:	jg     889760 <CEquipment::unitInit(CDataGroup*, bool)+0x650>
  88aa08:	lea    0x38b(%rsp),%rsi
  88aa10:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88aa15:	jmp    889760 <CEquipment::unitInit(CDataGroup*, bool)+0x650>
  88aa1a:	mov    %r13,%rdi
  88aa1d:	mov    %rax,%rbp
  88aa20:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88aa25:	jmp    88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88aa2a:	mov    0x10(%rdi),%eax
  88aa2d:	lea    -0x1(%rax),%edx
  88aa30:	mov    %edx,0x10(%rdi)
  88aa33:	jmp    88aa00 <CEquipment::unitInit(CDataGroup*, bool)+0x18f0>
  88aa35:	mov    $0x5541c8,%eax
  88aa3a:	test   %rax,%rax
  88aa3d:	je     88aa66 <CEquipment::unitInit(CDataGroup*, bool)+0x1956>
  88aa3f:	or     $0xffffffff,%eax
  88aa42:	lock xadd %eax,0x10(%rdi)
  88aa47:	test   %eax,%eax
  88aa49:	jg     889793 <CEquipment::unitInit(CDataGroup*, bool)+0x683>
  88aa4f:	lea    0x38a(%rsp),%rsi
  88aa57:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88aa5c:	jmp    889793 <CEquipment::unitInit(CDataGroup*, bool)+0x683>
  88aa61:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88aa66:	mov    0x10(%rdi),%eax
  88aa69:	lea    -0x1(%rax),%edx
  88aa6c:	mov    %edx,0x10(%rdi)
  88aa6f:	nop
  88aa70:	jmp    88aa47 <CEquipment::unitInit(CDataGroup*, bool)+0x1937>
  88aa72:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88aa77:	mov    $0x5541c8,%eax
  88aa7c:	test   %rax,%rax
  88aa7f:	je     88aafb <CEquipment::unitInit(CDataGroup*, bool)+0x19eb>
  88aa81:	or     $0xffffffff,%eax
  88aa84:	lock xadd %eax,0x10(%rdi)
  88aa89:	test   %eax,%eax
  88aa8b:	jg     8897dd <CEquipment::unitInit(CDataGroup*, bool)+0x6cd>
  88aa91:	lea    0x389(%rsp),%rsi
  88aa99:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88aa9e:	jmp    8897dd <CEquipment::unitInit(CDataGroup*, bool)+0x6cd>
  88aaa3:	mov    $0x5541c8,%eax
  88aaa8:	test   %rax,%rax
  88aaab:	je     88ab06 <CEquipment::unitInit(CDataGroup*, bool)+0x19f6>
  88aaad:	or     $0xffffffff,%eax
  88aab0:	lock xadd %eax,0x10(%rdi)
  88aab5:	test   %eax,%eax
  88aab7:	jg     88950a <CEquipment::unitInit(CDataGroup*, bool)+0x3fa>
  88aabd:	lea    0x395(%rsp),%rsi
  88aac5:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88aaca:	jmp    88950a <CEquipment::unitInit(CDataGroup*, bool)+0x3fa>
  88aacf:	mov    $0x5541c8,%eax
  88aad4:	test   %rax,%rax
  88aad7:	je     88ab11 <CEquipment::unitInit(CDataGroup*, bool)+0x1a01>
  88aad9:	or     $0xffffffff,%eax
  88aadc:	lock xadd %eax,0x10(%rdi)
  88aae1:	test   %eax,%eax
  88aae3:	jg     88951f <CEquipment::unitInit(CDataGroup*, bool)+0x40f>
  88aae9:	lea    0x394(%rsp),%rsi
  88aaf1:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88aaf6:	jmp    88951f <CEquipment::unitInit(CDataGroup*, bool)+0x40f>
  88aafb:	mov    0x10(%rdi),%eax
  88aafe:	lea    -0x1(%rax),%edx
  88ab01:	mov    %edx,0x10(%rdi)
  88ab04:	jmp    88aa89 <CEquipment::unitInit(CDataGroup*, bool)+0x1979>
  88ab06:	mov    0x10(%rdi),%eax
  88ab09:	lea    -0x1(%rax),%edx
  88ab0c:	mov    %edx,0x10(%rdi)
  88ab0f:	jmp    88aab5 <CEquipment::unitInit(CDataGroup*, bool)+0x19a5>
  88ab11:	mov    0x10(%rdi),%eax
  88ab14:	lea    -0x1(%rax),%edx
  88ab17:	mov    %edx,0x10(%rdi)
  88ab1a:	jmp    88aae1 <CEquipment::unitInit(CDataGroup*, bool)+0x19d1>
  88ab1c:	jmp    88a4c7 <CEquipment::unitInit(CDataGroup*, bool)+0x13b7>
  88ab21:	mov    %r12,%rdi
  88ab24:	mov    %rax,%rbp
  88ab27:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88ab2c:	jmp    88a445 <CEquipment::unitInit(CDataGroup*, bool)+0x1335>
  88ab31:	mov    $0x5541c8,%eax
  88ab36:	test   %rax,%rax
  88ab39:	je     88ab6d <CEquipment::unitInit(CDataGroup*, bool)+0x1a5d>
  88ab3b:	or     $0xffffffff,%eax
  88ab3e:	lock xadd %eax,0x10(%rdi)
  88ab43:	test   %eax,%eax
  88ab45:	jg     889332 <CEquipment::unitInit(CDataGroup*, bool)+0x222>
  88ab4b:	lea    0x3a3(%rsp),%rsi
  88ab53:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ab58:	jmp    889332 <CEquipment::unitInit(CDataGroup*, bool)+0x222>
  88ab5d:	mov    %r12,%rdi
  88ab60:	mov    %rax,%rbp
  88ab63:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88ab68:	jmp    88a452 <CEquipment::unitInit(CDataGroup*, bool)+0x1342>
  88ab6d:	mov    0x10(%rdi),%eax
  88ab70:	lea    -0x1(%rax),%edx
  88ab73:	mov    %edx,0x10(%rdi)
  88ab76:	jmp    88ab43 <CEquipment::unitInit(CDataGroup*, bool)+0x1a33>
  88ab78:	mov    $0x5541c8,%eax
  88ab7d:	test   %rax,%rax
  88ab80:	je     88aba9 <CEquipment::unitInit(CDataGroup*, bool)+0x1a99>
  88ab82:	or     $0xffffffff,%eax
  88ab85:	lock xadd %eax,0x10(%rdi)
  88ab8a:	test   %eax,%eax
  88ab8c:	jg     8893a3 <CEquipment::unitInit(CDataGroup*, bool)+0x293>
  88ab92:	lea    0x3a2(%rsp),%rsi
  88ab9a:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ab9f:	jmp    8893a3 <CEquipment::unitInit(CDataGroup*, bool)+0x293>
  88aba4:	jmp    88ab21 <CEquipment::unitInit(CDataGroup*, bool)+0x1a11>
  88aba9:	mov    0x10(%rdi),%eax
  88abac:	lea    -0x1(%rax),%edx
  88abaf:	mov    %edx,0x10(%rdi)
  88abb2:	jmp    88ab8a <CEquipment::unitInit(CDataGroup*, bool)+0x1a7a>
  88abb4:	mov    $0x5541c8,%eax
  88abb9:	test   %rax,%rax
  88abbc:	je     88abe8 <CEquipment::unitInit(CDataGroup*, bool)+0x1ad8>
  88abbe:	or     $0xffffffff,%eax
  88abc1:	lock xadd %eax,0x10(%rdi)
  88abc6:	test   %eax,%eax
  88abc8:	jg     889573 <CEquipment::unitInit(CDataGroup*, bool)+0x463>
  88abce:	lea    0x391(%rsp),%rsi
  88abd6:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88abdb:	jmp    889573 <CEquipment::unitInit(CDataGroup*, bool)+0x463>
  88abe0:	mov    %rax,%rbp
  88abe3:	jmp    88a515 <CEquipment::unitInit(CDataGroup*, bool)+0x1405>
  88abe8:	mov    0x10(%rdi),%eax
  88abeb:	lea    -0x1(%rax),%edx
  88abee:	mov    %edx,0x10(%rdi)
  88abf1:	jmp    88abc6 <CEquipment::unitInit(CDataGroup*, bool)+0x1ab6>
  88abf3:	jmp    88abe0 <CEquipment::unitInit(CDataGroup*, bool)+0x1ad0>
  88abf5:	mov    %r12,%rdi
  88abf8:	mov    %rax,%rbp
  88abfb:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88ac00:	jmp    88a515 <CEquipment::unitInit(CDataGroup*, bool)+0x1405>
  88ac05:	mov    $0x5541c8,%eax
  88ac0a:	test   %rax,%rax
  88ac0d:	je     88ac36 <CEquipment::unitInit(CDataGroup*, bool)+0x1b26>
  88ac0f:	or     $0xffffffff,%eax
  88ac12:	lock xadd %eax,0x10(%rdi)
  88ac17:	test   %eax,%eax
  88ac19:	jg     8895eb <CEquipment::unitInit(CDataGroup*, bool)+0x4db>
  88ac1f:	lea    0x390(%rsp),%rsi
  88ac27:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ac2c:	jmp    8895eb <CEquipment::unitInit(CDataGroup*, bool)+0x4db>
  88ac31:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88ac36:	mov    0x10(%rdi),%eax
  88ac39:	lea    -0x1(%rax),%edx
  88ac3c:	mov    %edx,0x10(%rdi)
  88ac3f:	nop
  88ac40:	jmp    88ac17 <CEquipment::unitInit(CDataGroup*, bool)+0x1b07>
  88ac42:	mov    $0x5541c8,%edx
  88ac47:	test   %rdx,%rdx
  88ac4a:	je     88ac7e <CEquipment::unitInit(CDataGroup*, bool)+0x1b6e>
  88ac4c:	or     $0xffffffff,%edx
  88ac4f:	lock xadd %edx,0x10(%r15)
  88ac55:	test   %edx,%edx
  88ac57:	jg     889636 <CEquipment::unitInit(CDataGroup*, bool)+0x526>
  88ac5d:	lea    0x38f(%rsp),%rsi
  88ac65:	mov    %r15,%rdi
  88ac68:	mov    %al,(%rsp)
  88ac6b:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ac70:	movzbl (%rsp),%eax
  88ac74:	jmp    889636 <CEquipment::unitInit(CDataGroup*, bool)+0x526>
  88ac79:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88ac7e:	mov    -0x8(%r14),%edx
  88ac82:	lea    -0x1(%rdx),%ecx
  88ac85:	mov    %ecx,-0x8(%r14)
  88ac89:	jmp    88ac55 <CEquipment::unitInit(CDataGroup*, bool)+0x1b45>
  88ac8b:	mov    $0x5541c8,%edx
  88ac90:	test   %rdx,%rdx
  88ac93:	je     88acc4 <CEquipment::unitInit(CDataGroup*, bool)+0x1bb4>
  88ac95:	or     $0xffffffff,%edx
  88ac98:	lock xadd %edx,0x10(%rdi)
  88ac9d:	test   %edx,%edx
  88ac9f:	jg     889bf1 <CEquipment::unitInit(CDataGroup*, bool)+0xae1>
  88aca5:	lea    0x37d(%rsp),%rsi
  88acad:	mov    %rax,(%rsp)
  88acb1:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88acb6:	mov    (%rsp),%rax
  88acba:	jmp    889bf1 <CEquipment::unitInit(CDataGroup*, bool)+0xae1>
  88acbf:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88acc4:	mov    0x10(%rdi),%edx
  88acc7:	lea    -0x1(%rdx),%ecx
  88acca:	mov    %ecx,0x10(%rdi)
  88accd:	jmp    88ac9d <CEquipment::unitInit(CDataGroup*, bool)+0x1b8d>
  88accf:	nop
  88acd0:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88acd5:	mov    $0x5541c8,%eax
  88acda:	test   %rax,%rax
  88acdd:	je     88ad3c <CEquipment::unitInit(CDataGroup*, bool)+0x1c2c>
  88acdf:	or     $0xffffffff,%eax
  88ace2:	lock xadd %eax,0x10(%rdi)
  88ace7:	test   %eax,%eax
  88ace9:	jg     889c56 <CEquipment::unitInit(CDataGroup*, bool)+0xb46>
  88acef:	lea    0x37c(%rsp),%rsi
  88acf7:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88acfc:	jmp    889c56 <CEquipment::unitInit(CDataGroup*, bool)+0xb46>
  88ad01:	jmp    88a5b8 <CEquipment::unitInit(CDataGroup*, bool)+0x14a8>
  88ad06:	mov    $0x5541c8,%edx
  88ad0b:	test   %rdx,%rdx
  88ad0e:	xchg   %ax,%ax
  88ad10:	je     88ad47 <CEquipment::unitInit(CDataGroup*, bool)+0x1c37>
  88ad12:	or     $0xffffffff,%edx
  88ad15:	lock xadd %edx,0x10(%rdi)
  88ad1a:	test   %edx,%edx
  88ad1c:	jg     889c83 <CEquipment::unitInit(CDataGroup*, bool)+0xb73>
  88ad22:	lea    0x37b(%rsp),%rsi
  88ad2a:	mov    %rax,(%rsp)
  88ad2e:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ad33:	mov    (%rsp),%rax
  88ad37:	jmp    889c83 <CEquipment::unitInit(CDataGroup*, bool)+0xb73>
  88ad3c:	mov    0x10(%rdi),%eax
  88ad3f:	lea    -0x1(%rax),%edx
  88ad42:	mov    %edx,0x10(%rdi)
  88ad45:	jmp    88ace7 <CEquipment::unitInit(CDataGroup*, bool)+0x1bd7>
  88ad47:	mov    0x10(%rdi),%edx
  88ad4a:	lea    -0x1(%rdx),%ecx
  88ad4d:	mov    %ecx,0x10(%rdi)
  88ad50:	jmp    88ad1a <CEquipment::unitInit(CDataGroup*, bool)+0x1c0a>
  88ad52:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88ad57:	mov    %r13,%rdi
  88ad5a:	mov    %rax,%rbp
  88ad5d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88ad62:	jmp    88a52f <CEquipment::unitInit(CDataGroup*, bool)+0x141f>
  88ad67:	mov    $0x5541c8,%eax
  88ad6c:	test   %rax,%rax
  88ad6f:	je     88adbf <CEquipment::unitInit(CDataGroup*, bool)+0x1caf>
  88ad71:	or     $0xffffffff,%eax
  88ad74:	lock xadd %eax,0x10(%rdi)
  88ad79:	test   %eax,%eax
  88ad7b:	jg     889ce8 <CEquipment::unitInit(CDataGroup*, bool)+0xbd8>
  88ad81:	lea    0x37a(%rsp),%rsi
  88ad89:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ad8e:	jmp    889ce8 <CEquipment::unitInit(CDataGroup*, bool)+0xbd8>
  88ad93:	mov    $0x5541c8,%eax
  88ad98:	test   %rax,%rax
  88ad9b:	je     88adca <CEquipment::unitInit(CDataGroup*, bool)+0x1cba>
  88ad9d:	or     $0xffffffff,%eax
  88ada0:	lock xadd %eax,0x10(%rdi)
  88ada5:	test   %eax,%eax
  88ada7:	jg     889d08 <CEquipment::unitInit(CDataGroup*, bool)+0xbf8>
  88adad:	lea    0x379(%rsp),%rsi
  88adb5:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88adba:	jmp    889d08 <CEquipment::unitInit(CDataGroup*, bool)+0xbf8>
  88adbf:	mov    0x10(%rdi),%eax
  88adc2:	lea    -0x1(%rax),%edx
  88adc5:	mov    %edx,0x10(%rdi)
  88adc8:	jmp    88ad79 <CEquipment::unitInit(CDataGroup*, bool)+0x1c69>
  88adca:	mov    0x10(%rdi),%eax
  88adcd:	lea    -0x1(%rax),%edx
  88add0:	mov    %edx,0x10(%rdi)
  88add3:	jmp    88ada5 <CEquipment::unitInit(CDataGroup*, bool)+0x1c95>
  88add5:	mov    $0x5541c8,%eax
  88adda:	test   %rax,%rax
  88addd:	je     88ae2d <CEquipment::unitInit(CDataGroup*, bool)+0x1d1d>
  88addf:	or     $0xffffffff,%eax
  88ade2:	lock xadd %eax,0x10(%rdi)
  88ade7:	test   %eax,%eax
  88ade9:	jg     889d1d <CEquipment::unitInit(CDataGroup*, bool)+0xc0d>
  88adef:	lea    0x378(%rsp),%rsi
  88adf7:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88adfc:	jmp    889d1d <CEquipment::unitInit(CDataGroup*, bool)+0xc0d>
  88ae01:	mov    $0x5541c8,%eax
  88ae06:	test   %rax,%rax
  88ae09:	je     88ae38 <CEquipment::unitInit(CDataGroup*, bool)+0x1d28>
  88ae0b:	or     $0xffffffff,%eax
  88ae0e:	lock xadd %eax,0x10(%rdi)
  88ae13:	test   %eax,%eax
  88ae15:	jg     889d32 <CEquipment::unitInit(CDataGroup*, bool)+0xc22>
  88ae1b:	lea    0x377(%rsp),%rsi
  88ae23:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ae28:	jmp    889d32 <CEquipment::unitInit(CDataGroup*, bool)+0xc22>
  88ae2d:	mov    0x10(%rdi),%eax
  88ae30:	lea    -0x1(%rax),%edx
  88ae33:	mov    %edx,0x10(%rdi)
  88ae36:	jmp    88ade7 <CEquipment::unitInit(CDataGroup*, bool)+0x1cd7>
  88ae38:	mov    0x10(%rdi),%eax
  88ae3b:	lea    -0x1(%rax),%edx
  88ae3e:	mov    %edx,0x10(%rdi)
  88ae41:	jmp    88ae13 <CEquipment::unitInit(CDataGroup*, bool)+0x1d03>
  88ae43:	mov    $0x5541c8,%eax
  88ae48:	test   %rax,%rax
  88ae4b:	je     88ae9b <CEquipment::unitInit(CDataGroup*, bool)+0x1d8b>
  88ae4d:	or     $0xffffffff,%eax
  88ae50:	lock xadd %eax,0x10(%rdi)
  88ae55:	test   %eax,%eax
  88ae57:	jg     889d47 <CEquipment::unitInit(CDataGroup*, bool)+0xc37>
  88ae5d:	lea    0x376(%rsp),%rsi
  88ae65:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ae6a:	jmp    889d47 <CEquipment::unitInit(CDataGroup*, bool)+0xc37>
  88ae6f:	mov    $0x5541c8,%eax
  88ae74:	test   %rax,%rax
  88ae77:	je     88aea6 <CEquipment::unitInit(CDataGroup*, bool)+0x1d96>
  88ae79:	or     $0xffffffff,%eax
  88ae7c:	lock xadd %eax,0x10(%rdi)
  88ae81:	test   %eax,%eax
  88ae83:	jg     889d5c <CEquipment::unitInit(CDataGroup*, bool)+0xc4c>
  88ae89:	lea    0x375(%rsp),%rsi
  88ae91:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88ae96:	jmp    889d5c <CEquipment::unitInit(CDataGroup*, bool)+0xc4c>
  88ae9b:	mov    0x10(%rdi),%eax
  88ae9e:	lea    -0x1(%rax),%edx
  88aea1:	mov    %edx,0x10(%rdi)
  88aea4:	jmp    88ae55 <CEquipment::unitInit(CDataGroup*, bool)+0x1d45>
  88aea6:	mov    0x10(%rdi),%eax
  88aea9:	lea    -0x1(%rax),%edx
  88aeac:	mov    %edx,0x10(%rdi)
  88aeaf:	jmp    88ae81 <CEquipment::unitInit(CDataGroup*, bool)+0x1d71>
  88aeb1:	mov    %r12,%rdi
  88aeb4:	mov    %rax,%rbp
  88aeb7:	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  88aebc:	jmp    88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88aec1:	mov    %rax,%rbp
  88aec4:	mov    %r13,%rdi
  88aec7:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88aecc:	jmp    88a438 <CEquipment::unitInit(CDataGroup*, bool)+0x1328>
  88aed1:	jmp    88a8f9 <CEquipment::unitInit(CDataGroup*, bool)+0x17e9>
  88aed6:	cs nopw 0x0(%rax,%rax,1)
  88aee0:	jmp    88a6da <CEquipment::unitInit(CDataGroup*, bool)+0x15ca>
  88aee5:	mov    %rax,%rbp
  88aee8:	nopl   0x0(%rax,%rax,1)
  88aef0:	jmp    88a438 <CEquipment::unitInit(CDataGroup*, bool)+0x1328>
  88aef5:	mov    %r13,%rdi
  88aef8:	mov    %rax,%rbp
  88aefb:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88af00:	jmp    88a438 <CEquipment::unitInit(CDataGroup*, bool)+0x1328>
  88af05:	jmp    88aec1 <CEquipment::unitInit(CDataGroup*, bool)+0x1db1>
  88af07:	mov    %rax,%rbp
  88af0a:	mov    %r15,%rdi
  88af0d:	nopl   (%rax)
  88af10:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88af15:	jmp    88aec4 <CEquipment::unitInit(CDataGroup*, bool)+0x1db4>
  88af17:	mov    %r12,%rdi
  88af1a:	mov    %rax,%rbp
  88af1d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88af22:	jmp    88af0a <CEquipment::unitInit(CDataGroup*, bool)+0x1dfa>
  88af24:	mov    %rax,%rbp
  88af27:	mov    %r12,%rdi
  88af2a:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88af2f:	nop
  88af30:	jmp    88af0a <CEquipment::unitInit(CDataGroup*, bool)+0x1dfa>
  88af32:	mov    %r14,%rdi
  88af35:	mov    %rax,%rbp
  88af38:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88af3d:	jmp    88af27 <CEquipment::unitInit(CDataGroup*, bool)+0x1e17>
  88af3f:	mov    $0x5541c8,%eax
  88af44:	test   %rax,%rax
  88af47:	je     88b121 <CEquipment::unitInit(CDataGroup*, bool)+0x2011>
  88af4d:	or     $0xffffffff,%eax
  88af50:	lock xadd %eax,0x10(%rdi)
  88af55:	test   %eax,%eax
  88af57:	jg     889455 <CEquipment::unitInit(CDataGroup*, bool)+0x345>
  88af5d:	lea    0x3a1(%rsp),%rsi
  88af65:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88af6a:	jmp    889455 <CEquipment::unitInit(CDataGroup*, bool)+0x345>
  88af6f:	mov    $0x5541c8,%eax
  88af74:	test   %rax,%rax
  88af77:	je     88b05c <CEquipment::unitInit(CDataGroup*, bool)+0x1f4c>
  88af7d:	or     $0xffffffff,%eax
  88af80:	lock xadd %eax,0x10(%rdi)
  88af85:	test   %eax,%eax
  88af87:	jg     88946a <CEquipment::unitInit(CDataGroup*, bool)+0x35a>
  88af8d:	lea    0x3a0(%rsp),%rsi
  88af95:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88af9a:	jmp    88946a <CEquipment::unitInit(CDataGroup*, bool)+0x35a>
  88af9f:	mov    $0x5541c8,%edx
  88afa4:	test   %rdx,%rdx
  88afa7:	je     88b0e5 <CEquipment::unitInit(CDataGroup*, bool)+0x1fd5>
  88afad:	or     $0xffffffff,%edx
  88afb0:	lock xadd %edx,0x10(%rdi)
  88afb5:	test   %edx,%edx
  88afb7:	jg     88981e <CEquipment::unitInit(CDataGroup*, bool)+0x70e>
  88afbd:	lea    0x388(%rsp),%rsi
  88afc5:	mov    %eax,(%rsp)
  88afc8:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88afcd:	mov    (%rsp),%eax
  88afd0:	jmp    88981e <CEquipment::unitInit(CDataGroup*, bool)+0x70e>
  88afd5:	mov    $0x5541c8,%eax
  88afda:	test   %rax,%rax
  88afdd:	je     88b0b4 <CEquipment::unitInit(CDataGroup*, bool)+0x1fa4>
  88afe3:	or     $0xffffffff,%eax
  88afe6:	lock xadd %eax,0x10(%rdi)
  88afeb:	test   %eax,%eax
  88afed:	jg     889494 <CEquipment::unitInit(CDataGroup*, bool)+0x384>
  88aff3:	lea    0x39e(%rsp),%rsi
  88affb:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88b000:	jmp    889494 <CEquipment::unitInit(CDataGroup*, bool)+0x384>
  88b005:	mov    %r12,%rdi
  88b008:	mov    %rax,%rbp
  88b00b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88b010:	jmp    88aec4 <CEquipment::unitInit(CDataGroup*, bool)+0x1db4>
  88b015:	mov    %r12,%rdi
  88b018:	mov    %rax,%rbp
  88b01b:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  88b020:	jmp    88a508 <CEquipment::unitInit(CDataGroup*, bool)+0x13f8>
  88b025:	mov    $0x5541c8,%edx
  88b02a:	test   %rdx,%rdx
  88b02d:	je     88b06a <CEquipment::unitInit(CDataGroup*, bool)+0x1f5a>
  88b02f:	or     $0xffffffff,%edx
  88b032:	lock xadd %edx,0x10(%rdi)
  88b037:	test   %edx,%edx
  88b039:	jg     889870 <CEquipment::unitInit(CDataGroup*, bool)+0x760>
  88b03f:	lea    0x387(%rsp),%rsi
  88b047:	mov    %eax,(%rsp)
  88b04a:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88b04f:	mov    (%rsp),%eax
  88b052:	jmp    889870 <CEquipment::unitInit(CDataGroup*, bool)+0x760>
  88b057:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88b05c:	mov    0x10(%rdi),%eax
  88b05f:	lea    -0x1(%rax),%edx
  88b062:	mov    %edx,0x10(%rdi)
  88b065:	jmp    88af85 <CEquipment::unitInit(CDataGroup*, bool)+0x1e75>
  88b06a:	mov    0x10(%rdi),%edx
  88b06d:	lea    -0x1(%rdx),%ecx
  88b070:	mov    %ecx,0x10(%rdi)
  88b073:	jmp    88b037 <CEquipment::unitInit(CDataGroup*, bool)+0x1f27>
  88b075:	jmp    88aeb1 <CEquipment::unitInit(CDataGroup*, bool)+0x1da1>
  88b07a:	mov    0x10(%rdi),%eax
  88b07d:	lea    -0x1(%rax),%edx
  88b080:	mov    %edx,0x10(%rdi)
  88b083:	jmp    88a262 <CEquipment::unitInit(CDataGroup*, bool)+0x1152>
  88b088:	mov    $0x5541c8,%eax
  88b08d:	test   %rax,%rax
  88b090:	je     88b0c2 <CEquipment::unitInit(CDataGroup*, bool)+0x1fb2>
  88b092:	or     $0xffffffff,%eax
  88b095:	lock xadd %eax,0x10(%rdi)
  88b09a:	test   %eax,%eax
  88b09c:	jg     88a2a5 <CEquipment::unitInit(CDataGroup*, bool)+0x1195>
  88b0a2:	lea    0x398(%rsp),%rsi
  88b0aa:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88b0af:	jmp    88a2a5 <CEquipment::unitInit(CDataGroup*, bool)+0x1195>
  88b0b4:	mov    0x10(%rdi),%eax
  88b0b7:	lea    -0x1(%rax),%edx
  88b0ba:	mov    %edx,0x10(%rdi)
  88b0bd:	jmp    88afeb <CEquipment::unitInit(CDataGroup*, bool)+0x1edb>
  88b0c2:	mov    0x10(%rdi),%eax
  88b0c5:	lea    -0x1(%rax),%edx
  88b0c8:	mov    %edx,0x10(%rdi)
  88b0cb:	jmp    88b09a <CEquipment::unitInit(CDataGroup*, bool)+0x1f8a>
  88b0cd:	jmp    88a505 <CEquipment::unitInit(CDataGroup*, bool)+0x13f5>
  88b0d2:	jmp    88a617 <CEquipment::unitInit(CDataGroup*, bool)+0x1507>
  88b0d7:	nopw   0x0(%rax,%rax,1)
  88b0e0:	jmp    88a4c7 <CEquipment::unitInit(CDataGroup*, bool)+0x13b7>
  88b0e5:	mov    0x10(%rdi),%edx
  88b0e8:	lea    -0x1(%rdx),%ecx
  88b0eb:	mov    %ecx,0x10(%rdi)
  88b0ee:	xchg   %ax,%ax
  88b0f0:	jmp    88afb5 <CEquipment::unitInit(CDataGroup*, bool)+0x1ea5>
  88b0f5:	mov    $0x5541c8,%eax
  88b0fa:	test   %rax,%rax
  88b0fd:	je     88b12f <CEquipment::unitInit(CDataGroup*, bool)+0x201f>
  88b0ff:	or     $0xffffffff,%eax
  88b102:	lock xadd %eax,0x10(%rdi)
  88b107:	test   %eax,%eax
  88b109:	jg     88947f <CEquipment::unitInit(CDataGroup*, bool)+0x36f>
  88b10f:	lea    0x39f(%rsp),%rsi
  88b117:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88b11c:	jmp    88947f <CEquipment::unitInit(CDataGroup*, bool)+0x36f>
  88b121:	mov    0x10(%rdi),%eax
  88b124:	lea    -0x1(%rax),%edx
  88b127:	mov    %edx,0x10(%rdi)
  88b12a:	jmp    88af55 <CEquipment::unitInit(CDataGroup*, bool)+0x1e45>
  88b12f:	mov    0x10(%rdi),%eax
  88b132:	lea    -0x1(%rax),%edx
  88b135:	mov    %edx,0x10(%rdi)
  88b138:	jmp    88b107 <CEquipment::unitInit(CDataGroup*, bool)+0x1ff7>
  88b13a:	mov    $0x5541c8,%eax
  88b13f:	test   %rax,%rax
  88b142:	je     88b174 <CEquipment::unitInit(CDataGroup*, bool)+0x2064>
  88b144:	or     $0xffffffff,%eax
  88b147:	lock xadd %eax,0x10(%rdi)
  88b14c:	test   %eax,%eax
  88b14e:	jg     8894f5 <CEquipment::unitInit(CDataGroup*, bool)+0x3e5>
  88b154:	lea    0x396(%rsp),%rsi
  88b15c:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  88b161:	jmp    8894f5 <CEquipment::unitInit(CDataGroup*, bool)+0x3e5>
  88b166:	mov    0x10(%rdi),%eax
  88b169:	lea    -0x1(%rax),%edx
  88b16c:	mov    %edx,0x10(%rdi)
  88b16f:	jmp    88a2df <CEquipment::unitInit(CDataGroup*, bool)+0x11cf>
  88b174:	mov    0x10(%rdi),%eax
  88b177:	lea    -0x1(%rax),%edx
  88b17a:	mov    %edx,0x10(%rdi)
  88b17d:	jmp    88b14c <CEquipment::unitInit(CDataGroup*, bool)+0x203c>
