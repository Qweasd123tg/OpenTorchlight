# Read-only pinned ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Large functions: bounded windows only, selected from full function disassembly.

# load bounded windows
  584b80:	push   %r14
  584b82:	mov    %edx,%r14d
  584b85:	push   %r13
  584b87:	push   %r12
  584b89:	mov    %rcx,%r12
  584b8c:	push   %rbp
  584b8d:	push   %rbx
  584b8e:	mov    %rdi,%rbx
  584b91:	sub    $0x170,%rsp
  584b98:	lea    0x150(%rsp),%rbp
  584ba0:	call   ece430 <CSteamStats::getSingleton()>
  584ba5:	mov    %rax,%rdi
  584ba8:	call   ece320 <CSteamStats::forceStatsToSave()>
  584bad:	mov    %r12,%rsi
  584bb0:	mov    %rbp,%rdi
  584bb3:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584bb8:	mov    %rbp,%rsi
  584bbb:	mov    %rbx,%rdi
  584bbe:	call   57f6b0 <CGameClient::setCurrentDungeon(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  584bc3:	mov    0x150(%rsp),%rdi
  584bcb:	mov    $0x1424540,%ebp
  584bd0:	sub    $0x18,%rdi
  584bd4:	cmp    %rbp,%rdi
  584bd7:	jne    585501 <CGameClient::loadMenuLevel(int, int, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x981>
  584bdd:	lea    0x140(%rsp),%r13
  584be5:	mov    %r12,%rsi
  584be8:	mov    %r13,%rdi
  584beb:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584bf0:	xor    %ecx,%ecx
  584bf2:	xor    %edx,%edx
  584bf4:	xor    %esi,%esi
  584bf6:	mov    $0x2f0,%edi
  584bfb:	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  584c00:	mov    0x28(%rbx),%r9
  584c04:	mov    0x2b8(%rbx),%r8
  584c0b:	mov    %rax,%r12
  584c0e:	mov    0x50(%rbx),%rdx
  584c12:	movl   $0x0,0x10(%rsp)
  584c1a:	mov    %rbx,%rcx
  584c1d:	mov    0x1090(%rbx),%eax
  584c23:	mov    %r13,%rsi
  584c26:	mov    %r12,%rdi
  584c29:	mov    %eax,0x8(%rsp)
  584c2d:	mov    0x48(%rbx),%rax
  584c31:	mov    %rax,(%rsp)
  584c35:	call   94ab00 <CLevel::CLevel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, CSettings*, CGameClient*, CResourceManager*, Ogre::SceneManager*, CSoundManager*, int, int)>
  584c3a:	mov    %r12,0x70(%rbx)
  584c3e:	mov    0x140(%rsp),%rdi
  584c46:	sub    $0x18,%rdi
  584c4a:	cmp    %rdi,%rbp
  584c4d:	jne    5854d1 <CGameClient::loadMenuLevel(int, int, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x951>
  584c53:	mov    %r14d,%esi
  584c56:	mov    %rbx,%rdi
  584c59:	call   56e710 <CGameClient::resetGameSeed(int)>
  584c5e:	mov    0x38d8(%rbx),%rdi
  584c65:	mov    %r14d,%edx
  584c68:	mov    %rbx,%rsi
  584c6b:	call   9340a0 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)>
  584c70:	test   %rax,%rax
  584c73:	mov    %rax,%r12
  584c76:	je     585330 <CGameClient::loadMenuLevel(int, int, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x7b0>
  584c7c:	lea    0x120(%rsp),%r13
  584c84:	mov    $0x1426490,%esi
  584c89:	mov    %r13,%rdi
  584c8c:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584c91:	lea    0x6f0(%r12),%rsi
  584c99:	lea    0x130(%rsp),%r12
  584ca1:	mov    %r12,%rdi
  584ca4:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  584ca9:	mov    0x70(%rbx),%rdi
  584cad:	mov    %r13,%r9
  584cb0:	xor    %r8d,%r8d
  584cb3:	mov    $0x3,%ecx
  584cb8:	xor    %edx,%edx
  584cba:	mov    %r12,%rsi
  584cbd:	call   9622f0 <CLevel::loadRoomLayout(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  584cc2:	mov    0x130(%rsp),%rdi
  584cca:	sub    $0x18,%rdi
  585330:	lea    0x100(%rsp),%r13
  585338:	mov    $0x1426490,%esi
  58533d:	lea    0x110(%rsp),%r12
  585345:	mov    %r13,%rdi
  585348:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58534d:	lea    0x16f(%rsp),%rdx
  585355:	mov    $0xfa77c8,%esi
  58535a:	mov    %r12,%rdi
  58535d:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  585362:	mov    0x70(%rbx),%rdi
  585366:	mov    %r13,%r9
  585369:	xor    %r8d,%r8d
  58536c:	mov    $0x3,%ecx
  585371:	xor    %edx,%edx
  585373:	mov    %r12,%rsi
  585376:	call   9622f0 <CLevel::loadRoomLayout(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>

# depth full body

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009340a0 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)>:
  9340a0:	push   %rbp
  9340a1:	push   %rbx
  9340a2:	sub    $0x28,%rsp
  9340a6:	mov    0x18(%rdi),%esi
  9340a9:	cmp    %esi,%edx
  9340ab:	jb     934120 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x80>
  9340ad:	sub    $0x1,%esi
  9340b0:	call   9337f0 <CDungeon::getStrataTemplate(unsigned int)>
  9340b5:	mov    %rax,%rbx
  9340b8:	test   %rbx,%rbx
  9340bb:	je     934115 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x75>
  9340bd:	mov    0x60(%rbx),%rdi
  9340c1:	mov    0xb5cd20(%rip),%rsi        # 1490de8 <EMPTY_WSTRING>
  9340c8:	mov    -0x18(%rdi),%rdx
  9340cc:	cmp    -0x18(%rsi),%rdx
  9340d0:	je     934130 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x90>
  9340d2:	lea    0x10(%rsp),%rbp
  9340d7:	lea    0x60(%rbx),%rsi
  9340db:	mov    %rbp,%rdi
  9340de:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9340e3:	call   dff070 <CDungeonManager::getSingleton()>
  9340e8:	mov    %rbp,%rsi
  9340eb:	mov    %rax,%rdi
  9340ee:	call   e03fe0 <CDungeonManager::getDungeonByName(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  9340f3:	mov    0x10(%rsp),%rdi
  9340f8:	sub    $0x18,%rdi
  9340fc:	cmp    $0x1424540,%rdi
  934103:	jne    934143 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0xa3>
  934105:	test   %rax,%rax
  934108:	je     934115 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x75>
  93410a:	mov    %rax,%rdi
  93410d:	call   933fe0 <CDungeon::getRandomLevelTemplateData()>
  934112:	mov    %rax,%rbx
  934115:	mov    %rbx,%rax
  934118:	add    $0x28,%rsp
  93411c:	pop    %rbx
  93411d:	pop    %rbp
  93411e:	ret
  93411f:	nop
  934120:	mov    %edx,%esi
  934122:	call   9337f0 <CDungeon::getStrataTemplate(unsigned int)>
  934127:	mov    %rax,%rbx
  93412a:	jmp    9340b8 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x18>
  93412c:	nopl   0x0(%rax)
  934130:	call   5553e8 <wmemcmp@plt>
  934135:	test   %eax,%eax
  934137:	jne    9340d2 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x32>
  934139:	mov    %rbx,%rax
  93413c:	add    $0x28,%rsp
  934140:	pop    %rbx
  934141:	pop    %rbp
  934142:	ret
  934143:	mov    $0x5541c8,%edx
  934148:	test   %rdx,%rdx
  93414b:	je     934182 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0xe2>
  93414d:	or     $0xffffffff,%edx
  934150:	lock xadd %edx,0x10(%rdi)
  934155:	test   %edx,%edx
  934157:	jg     934105 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x65>
  934159:	lea    0x1f(%rsp),%rsi
  93415e:	mov    %rax,0x8(%rsp)
  934163:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  934168:	mov    0x8(%rsp),%rax
  93416d:	jmp    934105 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0x65>
  93416f:	mov    %rax,%rbx
  934172:	mov    %rbp,%rdi
  934175:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  93417a:	mov    %rbx,%rdi
  93417d:	call   554498 <_Unwind_Resume@plt>
  934182:	mov    0x10(%rdi),%edx
  934185:	lea    -0x1(%rdx),%ecx
  934188:	mov    %ecx,0x10(%rdi)
  93418b:	jmp    934155 <CDungeon::getLevelTemplateDataForDepth(CGameClient*, unsigned int)+0xb5>

# loadDungeon bounded windows
  934c34:	lea    0xc0(%rsp),%rbx
  934c3c:	lea    0x1b5(%rsp),%rdx
  934c44:	mov    $0xfd554c,%esi
  934c49:	mov    %rbx,%rdi
  934c4c:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  934c51:	mov    0x18(%rsp),%rdi
  934c56:	mov    $0x1,%edx
  934c5b:	mov    %rbx,%rsi
  934c5e:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  934c63:	mov    0xc0(%rsp),%rdi
  934c6b:	mov    %eax,%ebx
  934c6d:	sub    $0x18,%rdi
  934c71:	cmp    %rdi,%r12
  934c74:	jne    9359f9 <CDungeon::loadDungeon(wchar_t const*)+0x12d9>
  934c7a:	movl   $0x1,0x28(%rsp)
  934c82:	test   %ebx,%ebx
  934c84:	cmovle 0x28(%rsp),%ebx
  934c89:	lea    0x1b4(%rsp),%rdx
  934c91:	mov    $0xfae940,%esi
  934c96:	mov    %ebx,0x28(%rsp)
  934c9a:	lea    0xb0(%rsp),%rbx
  934ca2:	mov    %rbx,%rdi
  934ca5:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  934caa:	mov    0x18(%rsp),%rdi
  934caf:	mov    $0x1,%edx
  934cb4:	mov    %rbx,%rsi
  934cb7:	call   c5f310 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, int)>
  934cbc:	mov    0xb0(%rsp),%rdi
  934cc4:	mov    %eax,0x2c(%rsp)
  934cc8:	sub    $0x18,%rdi
  934ccc:	cmp    %rdi,%r12
  934ccf:	jne    9359b5 <CDungeon::loadDungeon(wchar_t const*)+0x1295>
  934cd5:	mov    0x28(%rsp),%eax
  934cd9:	mov    $0x1,%edx
  934cde:	add    $0xa,%eax
  934ce1:	cmove  %edx,%eax
  934ce4:	mov    0x8(%rsp),%rdx
  934ce9:	mov    %eax,0x20(%rdx)
  934cec:	movl   $0x0,0x24(%rsp)
  934cf4:	mov    0x8(%rsp),%rcx
  934cf9:	mov    0x108(%rcx),%eax
  934cff:	mov    0x10c(%rcx),%ebp
  934d05:	cmp    %ebp,%eax
  934d07:	jae    9354a5 <CDungeon::loadDungeon(wchar_t const*)+0xd85>
  934d0d:	mov    0x100(%rcx),%rbx
  934d14:	mov    0x18(%rsp),%rcx
  934d19:	mov    %eax,%eax
  934d1b:	mov    %rcx,(%rbx,%rax,8)
  934d1f:	mov    0x8(%rsp),%rax
  934d24:	addl   $0x1,0x108(%rax)
  934d2b:	mov    0x18(%rax),%esi
  934d2e:	mov    0x2c(%rsp),%edx
  934d32:	mov    0x30(%rsp),%rdi
  934d37:	call   c8a470 <CRandomizer::addChoice(int, int)>
  934d3c:	mov    0x8(%rsp),%rdx
  934d41:	mov    0x18(%rdx),%eax
  934d44:	mov    0x1c(%rdx),%ebp
  934d47:	cmp    %ebp,%eax
  934d49:	jae    93542a <CDungeon::loadDungeon(wchar_t const*)+0xd0a>
  934d4f:	mov    0x10(%rdx),%rbx
  934d53:	mov    %eax,%eax
  934d55:	lea    0x1b3(%rsp),%rdx
  934d5d:	lea    0xa0(%rsp),%rdi
  934d65:	movq   $0x0,(%rbx,%rax,8)
  934d6d:	mov    0x8(%rsp),%rax
  934d72:	mov    $0xfd5478,%esi
  934d77:	addl   $0x1,0x18(%rax)
  934d7b:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  935290:	addl   $0x1,0x48(%rcx)
  935294:	addl   $0x1,0x24(%rsp)
  935299:	mov    0x24(%rsp),%edx
  93529d:	cmp    %edx,0x28(%rsp)
  9352a1:	jg     934cf4 <CDungeon::loadDungeon(wchar_t const*)+0x5d4>
  9352a7:	lea    0x80(%rsp),%r13
  9352af:	mov    0x3c(%rsp),%esi

# strata bounded windows
  9337f0:	push   %r15
  9337f2:	push   %r14
  9337f4:	push   %r13
  9337f6:	push   %r12
  9337f8:	push   %rbp
  9337f9:	push   %rbx
  9337fa:	xor    %ebx,%ebx
  9337fc:	sub    $0x148,%rsp
  933803:	mov    %rdi,0x10(%rsp)
  933808:	mov    %esi,0x18(%rsp)
  93380c:	cmp    0x18(%rdi),%esi
  93380f:	jae    933841 <CDungeon::getStrataTemplate(unsigned int)+0x51>
  933811:	mov    0x1c(%rdi),%edx
  933814:	cmp    %edx,%esi
  933816:	jae    933860 <CDungeon::getStrataTemplate(unsigned int)+0x70>
  933818:	mov    0x18(%rsp),%eax
  93381c:	mov    0x10(%rsp),%rcx
  933821:	shl    $0x3,%rax
  933825:	add    0x10(%rcx),%rax
  933829:	cmpq   $0x0,(%rax)
  93382d:	je     933888 <CDungeon::getStrataTemplate(unsigned int)+0x98>
  93382f:	cmp    %edx,0x18(%rsp)
  933833:	jb     933870 <CDungeon::getStrataTemplate(unsigned int)+0x80>
  933835:	mov    0x10(%rsp),%rdx
  93383a:	mov    0x10(%rdx),%rax
  93383e:	mov    (%rax),%rbx
  933841:	add    $0x148,%rsp
  933848:	mov    %rbx,%rax
  93384b:	pop    %rbx
  93384c:	pop    %rbp
  93384d:	pop    %r12
  93384f:	pop    %r13
  933851:	pop    %r14
  933853:	pop    %r15
  933855:	ret
  933856:	cs nopw 0x0(%rax,%rax,1)
  933860:	mov    0x10(%rdi),%rax
  933864:	jmp    933829 <CDungeon::getStrataTemplate(unsigned int)+0x39>
  933866:	cs nopw 0x0(%rax,%rax,1)
  933870:	mov    0x18(%rsp),%eax
  933874:	mov    0x10(%rsp),%rcx
  933879:	shl    $0x3,%rax
  93387d:	add    0x10(%rcx),%rax
  933881:	jmp    93383e <CDungeon::getStrataTemplate(unsigned int)+0x4e>
  933883:	nopl   0x0(%rax,%rax,1)
  933888:	mov    0x10(%rsp),%rax
  93388d:	mov    0x18(%rsp),%edx
  933891:	cmp    0x10c(%rax),%edx
  933897:	jae    933e00 <CDungeon::getStrataTemplate(unsigned int)+0x610>
  93389d:	mov    0x18(%rsp),%eax
  9338a1:	mov    0x10(%rsp),%rdx
  9338a6:	shl    $0x3,%rax
  9338aa:	add    0x100(%rdx),%rax
  9338b1:	lea    0x110(%rsp),%rbx
  9338b9:	lea    0x13f(%rsp),%rdx
  9338c1:	mov    $0xfd50a0,%esi
  9338c6:	mov    (%rax),%r12
  9338c9:	mov    %rbx,%rdi
  9338cc:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  9338d1:	mov    $0xfa7d50,%edx
  9338d6:	mov    %rbx,%rsi
  9338d9:	mov    %r12,%rdi
  9338dc:	call   c5f3a0 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, wchar_t const*)>
  9338e1:	lea    0x120(%rsp),%rdi
  9338e9:	mov    %rax,%rsi
  9338ec:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9338f1:	mov    %rbx,%rdi
  9338f4:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9338f9:	lea    0x100(%rsp),%rbx
  933901:	lea    0x13e(%rsp),%rdx
  933909:	mov    $0xfd50c0,%esi
  93390e:	mov    %rbx,%rdi
  933911:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  933916:	mov    $0x1,%edx
  93391b:	mov    %rbx,%rsi
  93391e:	mov    %r12,%rdi
  933921:	call   c5f340 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, bool)>
  933926:	mov    %rbx,%rdi
  933929:	mov    %al,0x1f(%rsp)
  93392d:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  933932:	lea    0xf0(%rsp),%rbx
  93393a:	lea    0x13d(%rsp),%rdx
  933942:	mov    $0xfd50f8,%esi
  933947:	mov    %rbx,%rdi
  93394a:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  93394f:	mov    $0x1,%edx

# character bounded windows
  581eed:	call   862eb0 <CCharacterSaveState::load(_IO_FILE*, unsigned int)>
  581ef2:	mov    0x10(%rsp),%rdx
  581ef7:	mov    0x60(%rbx),%eax
  581efa:	mov    %eax,0x1090(%rdx)
  581f00:	mov    0x64(%rbx),%eax
  581f03:	mov    0x2b8(%rdx),%rdi
  581f0a:	mov    %eax,0x1094(%rdx)
  581f10:	mov    0xa0(%rsp),%rsi
  5821cf:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  5821d4:	mov    0x10(%rsp),%rdi
  5821d9:	mov    %rbx,%rsi
  5821dc:	call   57f6b0 <CGameClient::setCurrentDungeon(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  5821e1:	mov    0x80(%rsp),%rdi
  5821e9:	sub    $0x18,%rdi
  5821ed:	cmp    $0x1424540,%rdi
  5821f4:	jne    582c22 <CGameClient::loadCharacter(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::vector<CCharacter*, std::allocator<CCharacter*> >&, std::vector<CCharacterSaveState*, std::allocator<CCharacterSaveState*> >&, bool)+0xf42>
  5821fa:	mov    0x10(%rsp),%rdi
  5821ff:	lea    0x90(%rsp),%rsi
  582207:	add    $0x1098,%rdi
  58220e:	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>

# fillSaveState bounded windows
  826918:	mov    0x450(%r13),%eax
  82691f:	mov    %eax,0xd8(%rbp)
  826925:	mov    0x68(%r13),%rdx
  826929:	xor    %eax,%eax
  82692b:	test   %rdx,%rdx
  82692e:	je     826934 <CCharacter::fillSaveState(CCharacterSaveState&)+0x154>
  826930:	mov    0x18(%rdx),%rax
  826934:	mov    0x1a4(%rax),%eax
  82693a:	movq   $0xffffffffffffffff,0x50(%rbp)
  826942:	mov    %eax,0x64(%rbp)

# group-ctor full body

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009f26e0 <CRandomGroup::CRandomGroup(CResourceManager*)>:
  9f26e0:	mov    %rbx,-0x20(%rsp)
  9f26e5:	mov    %rdi,%rbx
  9f26e8:	mov    %r12,-0x10(%rsp)
  9f26ed:	lea    0x180(%rbx),%r12
  9f26f4:	mov    %rbp,-0x18(%rsp)
  9f26f9:	mov    %r13,-0x8(%rsp)
  9f26fe:	xor    %edx,%edx
  9f2700:	sub    $0x28,%rsp
  9f2704:	call   9e7a50 <CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*)>
  9f2709:	movq   $0xfda170,(%rbx)
  9f2710:	movq   $0xfda360,0x100(%rbx)
  9f271b:	mov    $0x14a8a28,%esi
  9f2720:	movb   $0x1,0x108(%rbx)
  9f2727:	movl   $0x0,0x10c(%rbx)
  9f2731:	mov    %r12,%rdi
  9f2734:	movl   $0x0,0x110(%rbx)
  9f273e:	movl   $0x0,0x114(%rbx)
  9f2748:	movl   $0x0,0x118(%rbx)
  9f2752:	movl   $0x0,0x11c(%rbx)
  9f275c:	movl   $0x1,0x120(%rbx)
  9f2766:	movl   $0x1,0x124(%rbx)
  9f2770:	movl   $0x0,0x128(%rbx)
  9f277a:	movl   $0x0,0x12c(%rbx)
  9f2784:	movl   $0x0,0x130(%rbx)
  9f278e:	movq   $0x0,0x138(%rbx)
  9f2799:	movl   $0x0,0x140(%rbx)
  9f27a3:	movl   $0x0,0x144(%rbx)
  9f27ad:	movl   $0xa,0x148(%rbx)
  9f27b7:	movb   $0x1,0x150(%rbx)
  9f27be:	movq   $0x1424558,0x158(%rbx)
  9f27c9:	movq   $0x1424558,0x160(%rbx)
  9f27d4:	movq   $0x1424558,0x168(%rbx)
  9f27df:	movq   $0x1424558,0x170(%rbx)
  9f27ea:	movq   $0x1424558,0x178(%rbx)
  9f27f5:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9f27fa:	lea    0x188(%rbx),%rbp
  9f2801:	mov    $0x14a8a28,%esi
  9f2806:	mov    %rbp,%rdi
  9f2809:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9f280e:	movl   $0xffffffff,0x190(%rbx)
  9f2818:	mov    $0x1,%esi
  9f281d:	mov    %rbx,%rdi
  9f2820:	call   9f1dd0 <CRandomGroup::setVisible(bool)>
  9f2825:	mov    0x8(%rsp),%rbx
  9f282a:	mov    0x10(%rsp),%rbp
  9f282f:	mov    0x18(%rsp),%r12
  9f2834:	mov    0x20(%rsp),%r13
  9f2839:	add    $0x28,%rsp
  9f283d:	ret
  9f283e:	mov    %rax,%r13
  9f2841:	lea    0x178(%rbx),%rdi
  9f2848:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f284d:	lea    0x170(%rbx),%rdi
  9f2854:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f2859:	lea    0x168(%rbx),%rdi
  9f2860:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f2865:	lea    0x160(%rbx),%rdi
  9f286c:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f2871:	lea    0x158(%rbx),%rdi
  9f2878:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f287d:	mov    0x138(%rbx),%rdi
  9f2884:	test   %rdi,%rdi
  9f2887:	je     9f2899 <CRandomGroup::CRandomGroup(CResourceManager*)+0x1b9>
  9f2889:	call   553638 <operator delete[](void*)@plt>
  9f288e:	movq   $0x0,0x138(%rbx)
  9f2899:	mov    %rbx,%rdi
  9f289c:	movq   $0xfd1a10,0x100(%rbx)
  9f28a7:	call   9e7160 <CPositionableObject::~CPositionableObject()>
  9f28ac:	mov    %r13,%rdi
  9f28af:	call   554498 <_Unwind_Resume@plt>
  9f28b4:	mov    %rbp,%rdi
  9f28b7:	mov    %rax,%r13
  9f28ba:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f28bf:	mov    %r12,%rdi
  9f28c2:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9f28c7:	jmp    9f2841 <CRandomGroup::CRandomGroup(CResourceManager*)+0x161>
  9f28cc:	mov    %rax,%r13
  9f28cf:	nop
  9f28d0:	jmp    9f28bf <CRandomGroup::CRandomGroup(CResourceManager*)+0x1df>

# group-type full body

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009f1a60 <CRandomGroup::SetRandomType(unsigned int)>:
  9f1a60:	cmp    $0x2,%esi
  9f1a63:	ja     9f1a6b <CRandomGroup::SetRandomType(unsigned int)+0xb>
  9f1a65:	mov    %esi,0x11c(%rdi)
  9f1a6b:	repz ret

# group-roll bounded windows
  74b328:	mov    (%r12),%rax
  74b32c:	mov    0x20(%r13),%rcx
  74b330:	mov    (%rax),%rax
  74b333:	cmp    %rcx,0x18(%rax)
  74b337:	je     74b367 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0xa7>
  74b339:	add    $0x1,%ebp
  74b33c:	cmp    0x8(%r12),%ebp
  74b341:	jae    74b416 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x156>
  74b347:	mov    0xc(%r12),%edx
  74b34c:	cmp    %ebp,%edx
  74b34e:	jbe    74b328 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x68>
  74b350:	mov    %ebp,%eax
  74b352:	mov    0x20(%r13),%rcx
  74b356:	shl    $0x3,%rax
  74b35a:	add    (%r12),%rax
  74b35e:	mov    (%rax),%rax
  74b361:	cmp    %rcx,0x18(%rax)
  74b365:	jne    74b339 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x79>
  74b367:	cmp    %ebp,%edx
  74b369:	ja     74b560 <rollGroup(CRandomGroup*, TArrayList<CEditorBaseObject*>&, TArrayList<CRandomGroup*>&)+0x2a0>
  74b36f:	mov    (%r12),%rax
  74b373:	mov    0x38(%rsp),%edx
  74b377:	mov    0x3c(%rsp),%r15d
  74b416:	lea    0x10(%rsp),%rax
  74b41b:	lea    0x30(%rsp),%rsi
  74b420:	mov    %r13,%rdi
  74b423:	mov    %rax,%rdx
  74b426:	mov    %rax,0x8(%rsp)
  74b42b:	call   9f9c00 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)>

# group-choice bounded windows
  9f9c00:	push   %r15
  9f9c02:	push   %r14
  9f9c04:	push   %r13
  9f9c06:	push   %r12
  9f9c08:	mov    %rdi,%r12
  9f9c0b:	push   %rbp
  9f9c0c:	mov    %rsi,%rbp
  9f9c0f:	push   %rbx
  9f9c10:	mov    %rdx,%rbx
  9f9c13:	sub    $0x88,%rsp
  9f9c1a:	mov    0x8(%rsi),%r11d
  9f9c1e:	test   %r11d,%r11d
  9f9c21:	jne    9f9c38 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x38>
  9f9c23:	add    $0x88,%rsp
  9f9c2a:	pop    %rbx
  9f9c2b:	pop    %rbp
  9f9c2c:	pop    %r12
  9f9c2e:	pop    %r13
  9f9c30:	pop    %r14
  9f9c32:	pop    %r15
  9f9c34:	ret
  9f9c35:	nopl   (%rax)
  9f9c38:	call   9f1d70 <CRandomGroup::getGroupCanBeCreated()>
  9f9c3d:	test   %al,%al
  9f9c3f:	je     9f9c23 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x23>
  9f9c41:	mov    0x11c(%r12),%r15d
  9f9c49:	test   %r15d,%r15d
  9f9c4c:	je     9f9d70 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x170>
  9f9c52:	mov    0x68(%r12),%rax
  9f9c57:	cmpb   $0x0,0x43(%rax)
  9f9c5b:	jne    9f9d70 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x170>
  9f9c61:	lea    0x10(%rsp),%rdi
  9f9c66:	xor    %esi,%esi
  9f9c68:	call   c8a600 <CRandomizer::CRandomizer(ERANDOMIZER_TYPE)>
  9f9c6d:	mov    0x124(%r12),%r12d
  9f9c75:	mov    %r12d,0xc(%rsp)
  9f9c7a:	mov    0x8(%rbp),%r11d
  9f9c7e:	test   %r11d,%r11d
  9f9c81:	je     9f9d54 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x154>
  9f9c87:	xor    %r13d,%r13d
  9f9c8a:	nopw   0x0(%rax,%rax,1)
  9f9c90:	cmp    %r13d,0xc(%rbp)
  9f9c94:	ja     9f9e48 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x248>
  9f9c9a:	mov    0x0(%rbp),%rax
  9f9c9e:	mov    (%rax),%r12
  9f9ca1:	test   %r12,%r12
  9f9ca4:	je     9f9d46 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x146>
  9f9caa:	mov    (%r12),%rax
  9f9cae:	mov    %r12,%rdi
  9f9cb1:	call   *0x1d0(%rax)
  9f9cb7:	cmp    $0x1,%r15d
  9f9cbb:	mov    %eax,%r14d
  9f9cbe:	je     9f9f10 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x310>
  9f9d70:	mov    0x8(%rbp),%r10d
  9f9d74:	test   %r10d,%r10d
  9f9d77:	je     9f9c23 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x23>
  9f9d7d:	xor    %r12d,%r12d
  9f9d80:	cmp    %r12d,0xc(%rbp)
  9f9d84:	mov    0x8(%rbx),%eax
  9f9d87:	ja     9f9e23 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x223>
  9f9d8d:	nopl   (%rax)
  9f9d90:	mov    0xc(%rbx),%r14d
  9f9d94:	mov    0x0(%rbp),%rdx
  9f9d98:	cmp    %eax,%r14d
  9f9d9b:	mov    (%rdx),%r13
  9f9d9e:	ja     9f9e3e <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x23e>
  9f9da4:	cmpq   $0x0,(%rbx)
  9f9da8:	je     9f9f98 <CRandomGroup::chooseChildrenByRandomChoice(TArrayList<CRandomGroup*>&, TArrayList<CEditorBaseObject*>&)+0x398>

