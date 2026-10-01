# Pinned original ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Instruction-aligned windows selected from complete disassembly; partial large-function review.

# createRandomLayout bounded windows
  973388:	cmpl   $0x0,0x1a0(%rdi)
  97338f:	je     97466d <CLevelTemplateData::createRandomLayout(int)+0x12fd>
  973395:	cmpl   $0x0,0x3c(%rsp)
  97339a:	je     9733a5 <CLevelTemplateData::createRandomLayout(int)+0x35>
  97339c:	mov    0x3c(%rsp),%edi
  9733a0:	call   c92c70 <UTILITIES::setSeed(int)>
  9733a5:	lea    0x170(%rbx),%rax
  9733ac:	lea    0x108(%rbx),%rdx
  9733b3:	movb   $0x1,0x762(%rbx)
  97348e:	call   c8aa10 <CRandomizer::getRandom()>
  973493:	xor    %ecx,%ecx
  973495:	xor    %edx,%edx
  973497:	xor    %esi,%esi
  973499:	mov    $0x48,%edi
  97349e:	mov    %eax,%r12d
  9734a1:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  9734a6:	mov    %rax,%rdi
  9734a9:	mov    %rax,%rbp
  9734ac:	call   d796c0 <CRunicCore::CRunicCore()>
  9734b1:	lea    0x18(%rbp),%rdi
  9734b5:	movq   $0xfd7cb0,0x0(%rbp)
  9734bd:	mov    %r12d,0x10(%rbp)
  9734c1:	mov    $0x1495cc8,%esi
  9734c6:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9734cb:	movl   $0x0,0x28(%rbp)
  9734d2:	movl   $0x0,0x24(%rbp)
  9734d9:	movl   $0x0,0x20(%rbp)
  9734e0:	movq   $0x0,0x30(%rbp)
  9734e8:	movq   $0x0,0x38(%rbp)
  9734f0:	movq   $0x0,0x40(%rbp)
  9735bf:	mov    0x78(%rbx),%esi
  9735c2:	mov    0x74(%rbx),%edi
  9735c5:	call   c92b10 <UTILITIES::randomIntegerBetween(int, int)>
  9735ca:	mov    %eax,0x5c(%rsp)
  9735ce:	movl   $0x0,0x4c(%rsp)
  9735d6:	movl   $0x0,0x38(%rsp)
  9735de:	cmpl   $0x3e7,0x4c(%rsp)
  9735e6:	jg     974a6e <CLevelTemplateData::createRandomLayout(int)+0x16fe>
  9735ec:	mov    0x5c(%rsp),%edx
  9735f0:	cmp    %edx,0x38(%rsp)
  9735f4:	jge    973b90 <CLevelTemplateData::createRandomLayout(int)+0x820>
  9735fa:	mov    0xa0(%rsp),%rdi
  973602:	call   c8aa10 <CRandomizer::getRandom()>
  973607:	mov    %eax,0x1c(%rsp)
  973b90:	cmpb   $0x0,0x59(%rbx)
  973b94:	je     973f80 <CLevelTemplateData::createRandomLayout(int)+0xc10>
  973b9a:	lea    0xf0(%rsp),%r14
  973ba2:	movq   $0x0,0x10(%rsp)
  9745d9:	mov    0x48(%rbx),%r10d
  9745dd:	xor    %esi,%esi
  9745df:	xor    %ecx,%ecx
  9745e1:	cmp    %r10d,%ecx
  9745e4:	jae    974b06 <CLevelTemplateData::createRandomLayout(int)+0x1796>
  9745ea:	xor    %r8d,%r8d
  9745ed:	xor    %edi,%edi
  9745ef:	cmp    %ebp,%edi
  9745f1:	jge    974b00 <CLevelTemplateData::createRandomLayout(int)+0x1790>
  9745f7:	mov    (%rdx,%r8,1),%r9
  974b06:	lea    0xd0(%rsp),%r14
  974b0e:	xor    %r12d,%r12d
  974b11:	xor    %r13d,%r13d
  974b14:	sub    %rdx,%rax
  974b17:	sar    $0x3,%rax
  974b1b:	cmp    %eax,%r13d
  974b1e:	jge    97471b <CLevelTemplateData::createRandomLayout(int)+0x13ab>
  974b24:	mov    (%rdx,%r12,1),%rbp
  974b28:	mov    0x10(%rbp),%eax
  974b2b:	cmp    0xfc(%rbx),%eax
  974b31:	jb     974c54 <CLevelTemplateData::createRandomLayout(int)+0x18e4>
  974b37:	mov    0xf0(%rbx),%rax
  974b3e:	mov    (%rax),%rdi
  974b41:	call   c8ab10 <CRandomizer::hasValidChoices()>
  974b46:	test   %al,%al
  974b48:	je     974715 <CLevelTemplateData::createRandomLayout(int)+0x13a5>
  974b6f:	lea    0x0(,%rcx,4),%rdx
  974b77:	add    0xb0(%rsp),%rdx
  974b7f:	addl   $0x1,(%rdx)
  974b82:	cmp    0x34(%rbx),%eax
  974b85:	jb     974c33 <CLevelTemplateData::createRandomLayout(int)+0x18c3>
  974b8b:	mov    0x28(%rbx),%rdx
  974b8f:	mov    (%rdx),%rdx
  974b92:	mov    0xb0(%rsp),%rsi
  974b9a:	mov    %rdx,0x108(%rsp)
  974ba2:	mov    (%rsi,%rcx,4),%ecx
  974ba5:	cmp    0x18(%rdx),%ecx
  974ba8:	jb     974bcc <CLevelTemplateData::createRandomLayout(int)+0x185c>
  974baa:	mov    0x10(%rbp),%edx
  974bad:	cmp    0xfc(%rbx),%edx
  974bb3:	jb     974c66 <CLevelTemplateData::createRandomLayout(int)+0x18f6>
  974bb9:	mov    0xf0(%rbx),%rcx
  974bc0:	mov    (%rcx),%rdi
  974bc3:	xor    %edx,%edx
  974bc5:	mov    %eax,%esi
  974bc7:	call   c8a240 <CRandomizer::setChoiceOdds(int, int)>
  974bcc:	mov    0xd8(%rsp),%rsi
  974bd4:	cmp    0xe0(%rsp),%rsi
  974bdc:	je     974c21 <CLevelTemplateData::createRandomLayout(int)+0x18b1>
  974bde:	xor    %eax,%eax
  974be0:	test   %rsi,%rsi
  974be3:	je     974bf8 <CLevelTemplateData::createRandomLayout(int)+0x1888>
  974be5:	mov    0x108(%rsp),%rax
  974bed:	mov    %rax,(%rsi)
  974bf0:	mov    0xd8(%rsp),%rax
  974bf8:	add    $0x8,%rax
  974bfc:	mov    %rax,0xd8(%rsp)
  974c04:	add    $0x1,%r13d
  974c08:	mov    0xf8(%rsp),%rax
  974c10:	mov    0xf0(%rsp),%rdx
  974c18:	add    $0x8,%r12
  974c1c:	jmp    974b14 <CLevelTemplateData::createRandomLayout(int)+0x17a4>
  974c21:	lea    0x108(%rsp),%rdx
  974c29:	mov    %r14,%rdi
  974c2c:	call   9682c0 <std::vector<CChunk*, std::allocator<CChunk*> >::_M_insert_aux(__gnu_cxx::__normal_iterator<CChunk**, std::vector<CChunk*, std::allocator<CChunk*> > >, CChunk* const&)>
  974c31:	jmp    974c04 <CLevelTemplateData::createRandomLayout(int)+0x1894>
  974c33:	mov    %eax,%edx
  974c35:	shl    $0x3,%rdx
  974c39:	add    0x28(%rbx),%rdx
  974c3d:	jmp    974b8f <CLevelTemplateData::createRandomLayout(int)+0x181f>
  974c42:	mov    %eax,%eax
  974c44:	shl    $0x3,%rax
  974c48:	add    0xf0(%rbx),%rax
  974c4f:	jmp    974b64 <CLevelTemplateData::createRandomLayout(int)+0x17f4>
  974c54:	mov    %eax,%eax
  974c82:	mov    0xe8(%rbx),%rdi
  974c89:	mov    $0x1,%edx
  974c8e:	call   c8a470 <CRandomizer::addChoice(int, int)>
  974c93:	xor    %ecx,%ecx
  974c95:	xor    %edx,%edx
  974c97:	xor    %esi,%esi
  974c99:	mov    $0x48,%edi
  974c9e:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  974ca3:	mov    %rax,%rdi
  974ca6:	mov    %rax,%rbp
  974ca9:	call   d796c0 <CRunicCore::CRunicCore()>

# loadRoomLayout bounded windows
  95fe07:	mov    0x1d8(%rbx),%rax
  95fe0e:	cmpb   $0x0,0x762(%rax)
  95fe15:	jne    960ff8 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1ea8>
  95fe1b:	cmpb   $0x0,0x58(%rax)
  95fe1f:	je     960ff8 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1ea8>
  960fce:	mov    0x1d8(%rbx),%rdi
  960fd5:	xor    %esi,%esi
  960fd7:	call   973370 <CLevelTemplateData::createRandomLayout(int)>
  960fdc:	add    $0x1,%r12d
  960fe0:	cmp    $0xa,%r12d
  960fe4:	jne    960fce <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1e7e>
  960fe6:	lea    0xc0(%rsp),%rdi
  960fee:	mov    $0xfd5c18,%esi
  960ff3:	call   754210 <CTimerStatics::popTime(wchar_t const*)>
  960ff8:	mov    0x220(%rbx),%rax
  960fff:	mov    0x228(%rbx),%edi
  961005:	mov    0x38d8(%rax),%rdx
  96100c:	xor    %eax,%eax
  96100e:	test   %rdx,%rdx
  961011:	je     961016 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1ec6>
  961013:	mov    0x58(%rdx),%eax
  961016:	add    0x1a4(%rbx),%edi
  96101c:	add    %eax,%edi
  96101e:	call   c92c70 <UTILITIES::setSeed(int)>
  961023:	mov    0x1d8(%rbx),%rdi
  96102a:	call   9713c0 <CLevelTemplateData::getRandomLayout()>
  96102f:	test   %rax,%rax
  961032:	mov    %rax,0x218(%rbx)
  961039:	je     9618b6 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x2766>

# load bounded windows
  977fe4:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  977fe9:	mov    0x40(%rsp),%rdi
  977fee:	xor    %edx,%edx
  977ff0:	mov    %rbx,%rsi
  977ff3:	call   c5f340 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)>
  977ff8:	mov    %al,0x10(%r12)
  978ba0:	jne    978bd0 <CLevelTemplateData::load(wchar_t const*)+0x28e0>
  978ba2:	cmpb   $0x0,0x10(%r13)
  978ba7:	movb   $0x1,0x12(%r13)
  978bac:	jne    979578 <CLevelTemplateData::load(wchar_t const*)+0x3288>
  978bb2:	cmpb   $0x0,0x11(%r13)
  978bb7:	je     9795a0 <CLevelTemplateData::load(wchar_t const*)+0x32b0>
  978bbd:	cmpl   $0x1,0x50(%r13)
  978bc2:	je     979630 <CLevelTemplateData::load(wchar_t const*)+0x3340>
  978bc8:	nopl   0x0(%rax,%rax,1)
  978c7e:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  978c83:	xor    %esi,%esi
  978c85:	mov    %rax,%rdi
  978c88:	mov    %rax,%rbx
  978c8b:	call   c8a600 <CRandomizer::CRandomizer(ERANDOMIZER_TYPE)>
  978c90:	cmpl   $0x0,0x30(%rbp)
  978c94:	mov    %rbx,0xe8(%rbp)
  978c9b:	je     97853d <CLevelTemplateData::load(wchar_t const*)+0x224d>
  978ca1:	lea    0x230(%rsp),%rbx
  978ca9:	lea    0x83f(%rsp),%rdx
  978cb1:	mov    $0xfc5724,%esi
  978cb6:	mov    %rbx,%rdi
  978cb9:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  978cbe:	lea    0x1b0(%rsp),%rdx
  978cc6:	lea    0x90(%rsp),%rdi
  978cce:	mov    %rbx,%rsi
  978cd1:	call   c5f910 <CDataGroup::GetDataGroupsMatchingName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::vector<CDataGroup*, std::allocator<CDataGroup*> >*)>
  978cd6:	mov    %rbx,%rdi
  978cd9:	mov    %eax,0x68(%rsp)
  978cdd:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  978ce2:	cmpl   $0x0,0x68(%rsp)
  978ce7:	je     97945b <CLevelTemplateData::load(wchar_t const*)+0x316b>
  978ced:	lea    0xb8(%rbp),%rdx
  978cf4:	lea    0xd0(%rbp),%rax
  978cfb:	movq   $0x0,0x60(%rsp)
  978d04:	movl   $0x0,0x58(%rsp)
  978d0c:	mov    %rdx,0x78(%rsp)
  978d11:	mov    %rax,0x70(%rsp)
  978d16:	mov    0xe8(%rbp),%rdi
  978d1d:	mov    0x58(%rsp),%esi
  978d21:	mov    $0x1,%edx
  978d26:	call   c8a470 <CRandomizer::addChoice(int, int)>
  979578:	mov    0x20(%rsp),%esi
  97957c:	mov    0x38(%rsp),%rdi
  979581:	mov    $0x1,%edx
  979586:	lea    0x170(%rsp),%r15
  97958e:	call   c8a470 <CRandomizer::addChoice(int, int)>
  979593:	jmp    978bd0 <CLevelTemplateData::load(wchar_t const*)+0x28e0>

# getRandomLayout full body

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009713c0 <CLevelTemplateData::getRandomLayout()>:
  9713c0:	push   %rbx
  9713c1:	mov    %rdi,%rbx
  9713c4:	mov    0xe8(%rdi),%rdi
  9713cb:	test   %rdi,%rdi
  9713ce:	je     9713f0 <CLevelTemplateData::getRandomLayout()+0x30>
  9713d0:	mov    0x30(%rdi),%eax
  9713d3:	test   %eax,%eax
  9713d5:	je     9713f0 <CLevelTemplateData::getRandomLayout()+0x30>
  9713d7:	call   c8aa10 <CRandomizer::getRandom()>
  9713dc:	cmp    0xc4(%rbx),%eax
  9713e2:	jb     9713f8 <CLevelTemplateData::getRandomLayout()+0x38>
  9713e4:	mov    0xb8(%rbx),%rax
  9713eb:	mov    (%rax),%rax
  9713ee:	pop    %rbx
  9713ef:	ret
  9713f0:	xor    %eax,%eax
  9713f2:	pop    %rbx
  9713f3:	ret
  9713f4:	nopl   0x0(%rax)
  9713f8:	mov    %eax,%eax
  9713fa:	shl    $0x3,%rax
  9713fe:	add    0xb8(%rbx),%rax
  971405:	mov    (%rax),%rax
  971408:	jmp    9713ee <CLevelTemplateData::getRandomLayout()+0x2e>

