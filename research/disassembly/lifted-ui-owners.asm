# original-code: read-only ELF SHA-256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Exact aligned instruction windows from complete symbol disassembly.

# CGameUI::CGameUI(CSettings&, CGameClient&, void*, Ogre::RenderWindow*, Ogre::Camera*, Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CResourceManager*) @0xaa6380, symbol size 2158
  aa66c1:	movq   $0x0,0x578(%rbx)
  aa66cc:	movq   $0x0,0x580(%rbx)
  aa66d7:	movq   $0x0,0x588(%rbx)
  aa66e2:	mov    %rax,0x8(%rsp)
  aa66e7:	call   91ac40 <CKeyManager::CKeyManager()>
  aa6824:	movl   $0x1,0x16c8(%rbx)
  aa682e:	movl   $0x0,0x178c(%rbx)
  aa6838:	movl   $0x6,0x1914(%rbx)
  aa6842:	mov    $0x14b7d08,%esi
  aa6847:	movl   $0x6,0x1918(%rbx)
  aa6851:	mov    %r14,0x1920(%rbx)
  aa6858:	mov    %r12,%rdi

# CGameUI::create() @0xa9e4a0, symbol size 32473
  aa400f:	mov    %rbx,%rdi
  aa4012:	mov    %rax,(%rsp)
  aa4016:	call   c2be40 <CMenuManager::CMenuManager(CGameUI&, CSettings&, Ogre::Camera*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*)>
  aa401b:	lea    0x5460(%rsp),%rdi
  aa4023:	mov    %rbx,0x588(%rbp)
  aa402a:	add    $0x20,%rdi
  aa402e:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>

# CMenuManager::CMenuManager(CGameUI&, CSettings&, Ogre::Camera*, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) @0xc2be40, symbol size 310
  c2befa:	mov    %rax,0xdc0(%rbx)
  c2bf01:	movq   $0x0,0xde0(%rbx)
  c2bf0c:	movq   $0x0,0xde8(%rbx)
  c2bf17:	movl   $0x6,0xdf0(%rbx)
  c2bf21:	call   c2bbb0 <CMenuManager::create()>

# CMenuManager::create() @0xc2bbb0, symbol size 338
  c2bc7e:	mov    %rax,%rbp
  c2bc81:	mov    0xdc8(%rbx),%r8
  c2bc88:	call   c42490 <CContinueGameMenu::CContinueGameMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*)>
  c2bc8d:	mov    %rbp,0xde8(%rbx)
  c2bc94:	xor    %ecx,%ecx
  c2bc96:	xor    %edx,%edx

# CContinueGameMenu::CContinueGameMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) @0xc42490, symbol size 406
  c424b6:	movb   $0x0,0xc1(%rbx)
  c424bd:	movl   $0x0,0xc4(%rbx)
  c424c7:	movl   $0x0,0xc8(%rbx)
  c424d1:	movq   $0x0,0x1a8(%rbx)
  c424dc:	movl   $0x0,0x1b0(%rbx)
  c42511:	movq   $0x0,0x1d8(%rbx)
  c4251c:	movq   $0x0,0x1e0(%rbx)
  c42527:	movq   $0x0,0x1e8(%rbx)
  c42532:	movq   $0x0,0x1f0(%rbx)
  c4253d:	movq   $0x0,0x1f8(%rbx)
  c42548:	movq   $0x0,0x200(%rbx)
  c42553:	movq   $0x0,0x208(%rbx)
