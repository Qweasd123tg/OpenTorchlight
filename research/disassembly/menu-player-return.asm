# Accepted instruction-aligned windows from full-function disassembly.
# CGameClient::setGameState remains partial. ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b

# Window 0x58fa90..0x58fb4b
  58fa90:	push   %r15
  58fa92:	push   %r14
  58fa94:	push   %r13
  58fa96:	mov    %edx,%r13d
  58fa99:	push   %r12
  58fa9b:	push   %rbp
  58fa9c:	push   %rbx
  58fa9d:	mov    %rdi,%rbx
  58faa0:	sub    $0x2c8,%rsp
  58faa7:	mov    %esi,0x24(%rsp)
  58faab:	mov    0x2b8(%rdi),%rdi
  58fab2:	call   d6f4e0 <CResourceManager::getEditorIsRunning()>
  58fab7:	test   %al,%al
  58fab9:	jne    590010 <CGameClient::setGameState(EGameState, EMenu)+0x580>
  58fabf:	mov    0x78(%rbx),%rdi
  58fac3:	test   %rdi,%rdi
  58fac6:	je     590010 <CGameClient::setGameState(EGameState, EMenu)+0x580>
  58facc:	mov    $0x1,%esi
  58fad1:	call   a83e00 <CGameUI::setCursorState(ECursorState)>
  58fad6:	mov    0x24(%rsp),%eax
  58fada:	cmp    %eax,0x38d0(%rbx)
  58fae0:	je     590028 <CGameClient::setGameState(EGameState, EMenu)+0x598>
  58fae6:	mov    0x78(%rbx),%rdi
  58faea:	mov    $0x1,%esi
  58faef:	call   a9c3b0 <CGameUI::setLoadingVisible(bool)>
  58faf4:	cmpq   $0x0,0x70(%rbx)
  58faf9:	mov    0x24(%rsp),%eax
  58fafd:	sete   %r14b
  58fb01:	cmp    %eax,0x38d0(%rbx)
  58fb07:	je     58fb21 <CGameClient::setGameState(EGameState, EMenu)+0x91>
  58fb09:	cmp    $0x5,%eax
  58fb0c:	je     58fb21 <CGameClient::setGameState(EGameState, EMenu)+0x91>
  58fb0e:	mov    $0x1,%esi
  58fb13:	mov    %rbx,%rdi
  58fb16:	mov    $0x1,%r14d
  58fb1c:	call   579b10 <CGameClient::unloadCurrentLevel(bool)>
  58fb21:	cmpl   $0x2,0x24(%rsp)
  58fb26:	movq   $0x1424558,0x2a0(%rsp)
  58fb32:	je     590259 <CGameClient::setGameState(EGameState, EMenu)+0x7c9>
  58fb38:	mov    0x24(%rsp),%eax
  58fb3c:	xor    %r12d,%r12d
  58fb3f:	sub    $0x3,%eax
  58fb42:	cmp    $0x1,%eax
  58fb45:	jbe    590036 <CGameClient::setGameState(EGameState, EMenu)+0x5a6>

# Window 0x58fb4b..0x58fc23
  58fb4b:	cmpl   $0x1,0x24(%rsp)
  58fb50:	je     5900db <CGameClient::setGameState(EGameState, EMenu)+0x64b>
  58fb56:	cmpl   $0x5,0x24(%rsp)
  58fb5b:	je     58fc23 <CGameClient::setGameState(EGameState, EMenu)+0x193>
  58fb61:	mov    0x24(%rsp),%r11d
  58fb66:	movb   $0x0,0x28(%rsp)
  58fb6b:	test   %r11d,%r11d
  58fb6e:	jne    58fc6d <CGameClient::setGameState(EGameState, EMenu)+0x1dd>
  58fb74:	test   %r14b,%r14b
  58fb77:	movl   $0x0,0x38d0(%rbx)
  58fb81:	je     58fbe5 <CGameClient::setGameState(EGameState, EMenu)+0x155>
  58fb83:	mov    0x78(%rbx),%rdi
  58fb87:	lea    0x2a0(%rsp),%rbp
  58fb8f:	call   a84d40 <CGameUI::reloadMenuCharacters()>
  58fb94:	cmpq   $0x0,0x58(%rbx)
  58fb99:	je     590717 <CGameClient::setGameState(EGameState, EMenu)+0xc87>
  58fb9f:	lea    0xf0(%rsp),%r14
  58fba7:	lea    0x1098(%rbx),%rsi
  58fbae:	lea    0x2a0(%rsp),%rbp
  58fbb6:	mov    %r14,%rdi
  58fbb9:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  58fbbe:	mov    0x1094(%rbx),%edx
  58fbc4:	mov    0x1090(%rbx),%esi
  58fbca:	mov    %r14,%rcx
  58fbcd:	mov    %rbx,%rdi
  58fbd0:	call   584b80 <CGameClient::loadMenuLevel(int, int, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  58fbd5:	mov    %r14,%rdi
  58fbd8:	lea    0x2a0(%rsp),%rbp
  58fbe0:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  58fbe5:	mov    0x58(%rbx),%rsi
  58fbe9:	mov    0x68(%rbx),%rdi
  58fbed:	lea    0x2a0(%rsp),%rbp
  58fbf5:	call   d264b0 <CQuestManager::setPlayer(CPlayer*)>
  58fbfa:	mov    0x78(%rbx),%rdi
  58fbfe:	mov    %r13d,%esi
  58fc01:	lea    0x2a0(%rsp),%rbp
  58fc09:	call   a84c80 <CGameUI::setActiveMenu(EMenu)>
  58fc0e:	mov    0x78(%rbx),%rdi
  58fc12:	xor    %esi,%esi
  58fc14:	lea    0x2a0(%rsp),%rbp
  58fc1c:	call   a84870 <CGameUI::setIngameUIVisible(bool)>
  58fc21:	jmp    58fc68 <CGameClient::setGameState(EGameState, EMenu)+0x1d8>

# Window 0x590717..0x590822
  590717:	mov    0x78(%rbx),%rax
  59071b:	lea    0x130(%rsp),%r14
  590723:	lea    0x2a0(%rsp),%rbp
  59072b:	mov    %r14,%rdi
  59072e:	add    $0x16c0,%rax
  590734:	mov    %rax,0x28(%rsp)
  590739:	call   c76730 <FILESYSTEM::GetSaveDataPath()>
  59073e:	lea    0x140(%rsp),%r15
  590746:	mov    0x28(%rsp),%rdx
  59074b:	mov    %r14,%rsi
  59074e:	mov    %r15,%rdi
  590751:	call   c73aa0 <FILESYSTEM::AssembleAbsolutePath(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  590756:	mov    %r14,%rdi
  590759:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  59075e:	lea    0x40(%rsp),%rcx
  590763:	lea    0x60(%rsp),%rdx
  590768:	xor    %r8d,%r8d
  59076b:	mov    %r15,%rsi
  59076e:	mov    %rbx,%rdi
  590771:	movq   $0x0,0x60(%rsp)
  59077a:	movq   $0x0,0x68(%rsp)
  590783:	movq   $0x0,0x70(%rsp)
  59078c:	movq   $0x0,0x40(%rsp)
  590795:	movq   $0x0,0x48(%rsp)
  59079e:	movq   $0x0,0x50(%rsp)
  5907a7:	call   581ce0 <CGameClient::loadCharacter(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::vector<CCharacter*, std::allocator<CCharacter*> >&, std::vector<CCharacterSaveState*, std::allocator<CCharacterSaveState*> >&, bool)>
  5907ac:	test   %rax,%rax
  5907af:	mov    %rax,0x58(%rbx)
  5907b3:	je     590c1a <CGameClient::setGameState(EGameState, EMenu)+0x118a>
  5907b9:	lea    0x1a8(%rbx),%rdi
  5907c0:	mov    $0x1001608,%esi
  5907c5:	call   552fb8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(wchar_t const*)@plt>
  5907ca:	lea    0x100(%rsp),%rbp
  5907d2:	lea    0x1098(%rbx),%rsi
  5907d9:	mov    %rbp,%rdi
  5907dc:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  5907e1:	mov    0x1094(%rbx),%edx
  5907e7:	mov    0x1090(%rbx),%esi
  5907ed:	mov    %rbp,%rcx
  5907f0:	mov    %rbx,%rdi
  5907f3:	call   584b80 <CGameClient::loadMenuLevel(int, int, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  5907f8:	mov    %rbp,%rdi
  5907fb:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  590800:	mov    $0x1,%ebp
  590805:	mov    0x58(%rbx),%rsi
  590809:	test   %rsi,%rsi
  59080c:	je     590942 <CGameClient::setGameState(EGameState, EMenu)+0xeb2>
  590812:	mov    0x70(%rbx),%rdi
  590816:	xor    %ecx,%ecx
  590818:	lea    0x140(%rdi),%rdx
  59081f:	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>

# Window 0x590810..0x590862
  590812:	mov    0x70(%rbx),%rdi
  590816:	xor    %ecx,%ecx
  590818:	lea    0x140(%rdi),%rdx
  59081f:	call   95aeb0 <CLevel::addCharacter(CCharacter*, Ogre::Vector3 const&, bool)>
  590824:	mov    0x70(%rbx),%rsi
  590828:	mov    0x58(%rbx),%rdi
  59082c:	add    $0x164,%rsi
  590833:	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
  590838:	cmpq   $0x0,0x58(%rbx)
  59083d:	je     590942 <CGameClient::setGameState(EGameState, EMenu)+0xeb2>
  590843:	test   %bpl,%bpl
  590846:	je     590942 <CGameClient::setGameState(EGameState, EMenu)+0xeb2>
  59084c:	mov    0x68(%rsp),%rsi
  590851:	mov    0x60(%rsp),%rcx
  590856:	mov    %rsi,%rax
  590859:	sub    %rcx,%rax
  59085c:	sar    $0x3,%rax
  590860:	test   %rax,%rax

# unloadCurrentLevel window 0x579b10..0x579b7b
  579b10:	push   %rbp
  579b11:	mov    %esi,%ebp
  579b13:	push   %rbx
  579b14:	mov    %rdi,%rbx
  579b17:	sub    $0x18,%rsp
  579b1b:	call   c77c20 <CGameSpeed::getSingleton()>
  579b20:	call   c78030 <CGameSpeed::clear()>
  579b25:	mov    0x78(%rbx),%rdi
  579b29:	test   %rdi,%rdi
  579b2c:	je     579b33 <CGameClient::unloadCurrentLevel(bool)+0x23>
  579b2e:	call   a8ee40 <CGameUI::hideTextEvents()>
  579b33:	mov    0x68(%rbx),%rdi
  579b37:	xor    %esi,%esi
  579b39:	call   d264b0 <CQuestManager::setPlayer(CPlayer*)>
  579b3e:	test   %bpl,%bpl
  579b41:	je     579b7b <CGameClient::unloadCurrentLevel(bool)+0x6b>
  579b43:	mov    0x58(%rbx),%rsi
  579b47:	test   %rsi,%rsi
  579b4a:	je     579b5f <CGameClient::unloadCurrentLevel(bool)+0x4f>
  579b4c:	mov    0x70(%rbx),%rdi
  579b50:	test   %rdi,%rdi
  579b53:	je     579b5f <CGameClient::unloadCurrentLevel(bool)+0x4f>
  579b55:	mov    $0x1,%edx
  579b5a:	call   949770 <CLevel::removeCharacter(CCharacter*, bool)>
  579b5f:	mov    0x60(%rbx),%rsi
  579b63:	test   %rsi,%rsi
  579b66:	je     579b7b <CGameClient::unloadCurrentLevel(bool)+0x6b>
  579b68:	mov    0x70(%rbx),%rdi
  579b6c:	test   %rdi,%rdi
  579b6f:	je     579b7b <CGameClient::unloadCurrentLevel(bool)+0x6b>
  579b71:	mov    $0x1,%edx
  579b76:	call   949770 <CLevel::removeCharacter(CCharacter*, bool)>

# unloadCurrentLevel window 0x579e2c..0x579e86
  579e2c:	test   %bpl,%bpl
  579e2f:	je     579e5f <CGameClient::unloadCurrentLevel(bool)+0x34f>
  579e31:	mov    0x58(%rbx),%rdi
  579e35:	test   %rdi,%rdi
  579e38:	je     579e48 <CGameClient::unloadCurrentLevel(bool)+0x338>
  579e3a:	mov    (%rdi),%rax
  579e3d:	call   *0x8(%rax)
  579e40:	movq   $0x0,0x58(%rbx)
  579e48:	mov    0x60(%rbx),%rdi
  579e4c:	test   %rdi,%rdi
  579e4f:	je     579e5f <CGameClient::unloadCurrentLevel(bool)+0x34f>
  579e51:	mov    (%rdi),%rax
  579e54:	call   *0x8(%rax)
  579e57:	movq   $0x0,0x60(%rbx)
  579e5f:	mov    0x68(%rbx),%rdi
  579e63:	movq   $0x0,0x58(%rbx)
  579e6b:	xor    %esi,%esi
  579e6d:	movq   $0x0,0x60(%rbx)
  579e75:	call   d264b0 <CQuestManager::setPlayer(CPlayer*)>
  579e7a:	add    $0x18,%rsp
  579e7e:	mov    $0x1,%eax
  579e83:	pop    %rbx
  579e84:	pop    %rbp
  579e85:	ret
