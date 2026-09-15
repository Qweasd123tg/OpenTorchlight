
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000977760 <CLevelTemplateData::load(wchar_t const*)+0x1470>:
  977760:	63 00                	movsxd (%rax),%eax
  977762:	f3 0f 11 85 24 07 00 	movss  %xmm0,0x724(%rbp)
  977769:	00 
  97776a:	f3 41 0f 2a c5       	cvtsi2ss %r13d,%xmm0
  97776f:	f3 0f 5e 05 c9 0f 63 	divss  0x630fc9(%rip),%xmm0        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  977776:	00 
  977777:	f3 0f 11 85 20 07 00 	movss  %xmm0,0x720(%rbp)
  97777e:	00 
  97777f:	e8 d4 e6 bd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  977784:	48 8d bc 24 90 00 00 	lea    0x90(%rsp),%rdi
  97778b:	00 
  97778c:	ba 5c 00 00 00       	mov    $0x5c,%edx
  977791:	48 89 de             	mov    %rbx,%rsi
  977794:	e8 77 7b 2e 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  977799:	48 8b bc 24 a0 04 00 	mov    0x4a0(%rsp),%rdi
  9777a0:	00 
  9777a1:	ba 40 45 42 01       	mov    $0x1424540,%edx
  9777a6:	41 89 c5             	mov    %eax,%r13d
  9777a9:	48 83 ef 18          	sub    $0x18,%rdi
  9777ad:	48 39 fa             	cmp    %rdi,%rdx
  9777b0:	0f 85 92 37 00 00    	jne    97af48 <CLevelTemplateData::load(wchar_t const*)+0x4c58>
  9777b6:	48 8d 9c 24 90 04 00 	lea    0x490(%rsp),%rbx
  9777bd:	00 
  9777be:	48 8d 94 24 5f 08 00 	lea    0x85f(%rsp),%rdx
  9777c5:	00 
  9777c6:	be b8 74 fd 00       	mov    $0xfd74b8,%esi
  9777cb:	48 89 df             	mov    %rbx,%rdi
  9777ce:	e8 85 e6 bd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  9777d3:	48 8d bc 24 90 00 00 	lea    0x90(%rsp),%rdi
  9777da:	00 
  9777db:	ba 5c 00 00 00       	mov    $0x5c,%edx
  9777e0:	48 89 de             	mov    %rbx,%rsi
  9777e3:	e8 28 7b 2e 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  9777e8:	48 8b bc 24 90 04 00 	mov    0x490(%rsp),%rdi
  9777ef:	00 
  9777f0:	41 89 c4             	mov    %eax,%r12d
  9777f3:	b8 40 45 42 01       	mov    $0x1424540,%eax
  9777f8:	48 83 ef 18          	sub    $0x18,%rdi
  9777fc:	48 39 f8             	cmp    %rdi,%rax
  9777ff:	0f 85 fb 36 00 00    	jne    97af00 <CLevelTemplateData::load(wchar_t const*)+0x4c10>
  977805:	48 8d 9c 24 80 04 00 	lea    0x480(%rsp),%rbx
  97780c:	00 
  97780d:	48 8d 94 24 5e 08 00 	lea    0x85e(%rsp),%rdx
  977814:	00 
  977815:	be 18 75 fd 00       	mov    $0xfd7518,%esi
  97781a:	48 89 df             	mov    %rbx,%rdi
  97781d:	e8 36 e6 bd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  977822:	48 8d bc 24 90 00 00 	lea    0x90(%rsp),%rdi
  977829:	00 
  97782a:	ba 5c 00 00 00       	mov    $0x5c,%edx
  97782f:	48 89 de             	mov    %rbx,%rsi
  977832:	e8 d9 7a 2e 00       	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  977837:	48 8b bc 24 80 04 00 	mov    0x480(%rsp),%rdi
  97783e:	00 
  97783f:	ba 40 45 42 01       	mov    $0x1424540,%edx
  977844:	89 c3                	mov    %eax,%ebx
  977846:	48 83 ef 18          	sub    $0x18,%rdi
  97784a:	48 39 fa             	cmp    %rdi,%rdx
  97784d:	0f 85 5e 36 00 00    	jne    97aeb1 <CLevelTemplateData::load(wchar_t const*)+0x4bc1>
  977853:	f3 0f 2a c3          	cvtsi2ss %ebx,%xmm0
  977857:	48 8d 9c 24 70 04 00 	lea    0x470(%rsp),%rbx
  97785e:	00 
  97785f:	48 8d 94 24 5d 08 00 	lea    0x85d(%rsp),%rdx
  977866:	00 
  977867:	c7 85 3c 07 00 00 00 	movl   $0x3f800000,0x73c(%rbp)
  97786e:	00 80 3f 
  977871:	be 70 75 fd 00       	mov    $0xfd7570,%esi
  977876:	48 89 df             	mov    %rbx,%rdi
  977879:	f3 0f 5e 05 bf 0e 63 	divss  0x630ebf(%rip),%xmm0        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  977880:	00 
  977881:	f3 0f 11 85 38 07 00 	movss  %xmm0,0x738(%rbp)
  977888:	00 
  977889:	f3 41 0f 2a c4       	cvtsi2ss %r12d,%xmm0
  97788e:	f3 0f 5e 05 aa 0e 63 	divss  0x630eaa(%rip),%xmm0        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  977895:	00 
  977896:	f3 0f 11 85 34 07 00 	movss  %xmm0,0x734(%rbp)
  97789d:	00 
  97789e:	f3 41 0f 2a c5       	cvtsi2ss %r13d,%xmm0
  9778a3:	f3 0f 5e 05 95 0e 63 	divss  0x630e95(%rip),%xmm0        # fa8740 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xa0>
  9778aa:	00 
  9778ab:	f3 0f 11 85 30 07 00 	movss  %xmm0,0x730(%rbp)
  9778b2:	00 
  9778b3:	e8 a0 e5 bd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  9778b8:	48 8d bc 24 90 00 00 	lea    0x90(%rsp),%rdi
  9778bf:	00 
