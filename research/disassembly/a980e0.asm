
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a980e0 <CGameUI::mapToFunctions(CEGUI::Window*)>:
  a980e0:	push   %r15
  a980e2:	push   %r14
  a980e4:	push   %r13
  a980e6:	push   %r12
  a980e8:	push   %rbp
  a980e9:	mov    %rdi,%rbp
  a980ec:	push   %rbx
  a980ed:	mov    %rsi,%rbx
  a980f0:	sub    $0x3a8,%rsp
  a980f7:	mov    0x78(%rsi),%rax
  a980fb:	mov    0x80(%rsi),%r14
  a98102:	sub    %rax,%r14
  a98105:	shr    $0x3,%r14
  a98109:	test   %r14d,%r14d
  a9810c:	jle    a9813d <CGameUI::mapToFunctions(CEGUI::Window*)+0x5d>
  a9810e:	xor    %r13d,%r13d
  a98111:	xor    %r12d,%r12d
  a98114:	jmp    a98124 <CGameUI::mapToFunctions(CEGUI::Window*)+0x44>
  a98116:	cs nopw 0x0(%rax,%rax,1)
  a98120:	mov    0x78(%rbx),%rax
  a98124:	mov    (%rax,%r13,1),%rsi
  a98128:	mov    %rbp,%rdi
  a9812b:	add    $0x1,%r12d
  a9812f:	add    $0x8,%r13
  a98133:	call   a980e0 <CGameUI::mapToFunctions(CEGUI::Window*)>
  a98138:	cmp    %r12d,%r14d
  a9813b:	jg     a98120 <CGameUI::mapToFunctions(CEGUI::Window*)+0x40>
  a9813d:	lea    0x2d0(%rsp),%r12
  a98145:	mov    $0xfe4840,%esi
  a9814a:	xor    %r14d,%r14d
  a9814d:	xor    %r15d,%r15d
  a98150:	mov    %r12,%rdi
  a98153:	call   899620 <CEGUI::String::String(char const*)>
  a98158:	mov    %r12,%rsi
  a9815b:	mov    %rbx,%rdi
  a9815e:	mov    $0x1,%r14d
  a98164:	call   553e18 <CEGUI::PropertySet::isPropertyPresent(CEGUI::String const&) const@plt>
  a98169:	xor    %r13d,%r13d
  a9816c:	test   %al,%al
  a9816e:	jne    a982e0 <CGameUI::mapToFunctions(CEGUI::Window*)+0x200>
  a98174:	mov    %r12,%rdi
  a98177:	call   555fe8 <CEGUI::String::~String()@plt>
  a9817c:	test   %r13b,%r13b
  a9817f:	jne    a981a8 <CGameUI::mapToFunctions(CEGUI::Window*)+0xc8>
  a98181:	add    $0x1910,%rbp
  a98188:	mov    %rbp,0x1d8(%rbx)
  a9818f:	add    $0x3a8,%rsp
  a98196:	pop    %rbx
  a98197:	pop    %rbp
  a98198:	pop    %r12
  a9819a:	pop    %r13
  a9819c:	pop    %r14
  a9819e:	pop    %r15
  a981a0:	ret
  a981a1:	nopl   0x0(%rax)
  a981a8:	lea    0xc0(%rsp),%r13
  a981b0:	mov    $0xfe4840,%esi
  a981b5:	mov    %r13,%rdi
  a981b8:	call   899620 <CEGUI::String::String(char const*)>
  a981bd:	lea    0x10(%rsp),%r12
  a981c2:	mov    %r13,%rdx
  a981c5:	mov    %rbx,%rsi
  a981c8:	mov    %r12,%rdi
  a981cb:	call   554418 <CEGUI::PropertySet::getProperty(CEGUI::String const&) const@plt>
  a981d0:	mov    %r12,%rdi
  a981d3:	call   556378 <CEGUI::String::build_utf8_buff() const@plt>
  a981d8:	lea    0x380(%rsp),%r14
  a981e0:	lea    0x39f(%rsp),%rdx
  a981e8:	mov    %rax,%rsi
  a981eb:	mov    %r14,%rdi
  a981ee:	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  a981f3:	lea    0x390(%rsp),%r15
  a981fb:	mov    %r14,%rsi
  a981fe:	mov    %r15,%rdi
  a98201:	call   c8e0e0 <STRINGS::StringUpper(std::string const&)>
  a98206:	mov    0x380(%rsp),%rdi
  a9820e:	sub    $0x18,%rdi
  a98212:	cmp    $0x1423a20,%rdi
  a98219:	jne    a98398 <CGameUI::mapToFunctions(CEGUI::Window*)+0x2b8>
  a9821f:	mov    %r12,%rdi
  a98222:	call   555fe8 <CEGUI::String::~String()@plt>
  a98227:	mov    %r13,%rdi
  a9822a:	call   555fe8 <CEGUI::String::~String()@plt>
  a9822f:	mov    0x390(%rsp),%r9
  a98237:	mov    $0x14b7dc0,%edx
  a9823c:	xor    %eax,%eax
  a9823e:	lea    -0x18(%r9),%r8
  a98242:	mov    %r8,%r10
  a98245:	jmp    a9825c <CGameUI::mapToFunctions(CEGUI::Window*)+0x17c>
  a98247:	nopw   0x0(%rax,%rax,1)
  a98250:	add    $0x1,%eax
  a98253:	add    $0x8,%rdx
  a98257:	cmp    $0x61,%eax
  a9825a:	je     a98298 <CGameUI::mapToFunctions(CEGUI::Window*)+0x1b8>
  a9825c:	mov    (%rdx),%rdi
  a9825f:	mov    (%r8),%rcx
  a98262:	cmp    -0x18(%rdi),%rcx
  a98266:	jne    a98250 <CGameUI::mapToFunctions(CEGUI::Window*)+0x170>
  a98268:	cmp    %rcx,%rcx
  a9826b:	mov    %r9,%rsi
  a9826e:	repz cmpsb (%rdi),(%rsi)
  a98270:	jne    a98250 <CGameUI::mapToFunctions(CEGUI::Window*)+0x170>
  a98272:	movslq %eax,%rcx
  a98275:	add    $0x1,%eax
  a98278:	add    $0x8,%rdx
  a9827c:	lea    0x1790(%rbp,%rcx,4),%rcx
  a98284:	cmp    $0x61,%eax
  a98287:	mov    %r10,%r8
  a9828a:	mov    %rcx,0x1d8(%rbx)
  a98291:	jne    a9825c <CGameUI::mapToFunctions(CEGUI::Window*)+0x17c>
  a98293:	nopl   0x0(%rax,%rax,1)
  a98298:	mov    $0x1423a20,%eax
  a9829d:	cmp    %r8,%rax
  a982a0:	je     a9818f <CGameUI::mapToFunctions(CEGUI::Window*)+0xaf>
  a982a6:	mov    $0x5541c8,%eax
  a982ab:	test   %rax,%rax
  a982ae:	je     a98444 <CGameUI::mapToFunctions(CEGUI::Window*)+0x364>
  a982b4:	or     $0xffffffff,%eax
  a982b7:	lock xadd %eax,0x10(%r8)
  a982bd:	test   %eax,%eax
  a982bf:	jg     a9818f <CGameUI::mapToFunctions(CEGUI::Window*)+0xaf>
  a982c5:	lea    0x39d(%rsp),%rsi
  a982cd:	mov    %r8,%rdi
  a982d0:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  a982d5:	jmp    a9818f <CGameUI::mapToFunctions(CEGUI::Window*)+0xaf>
  a982da:	nopw   0x0(%rax,%rax,1)
  a982e0:	lea    0x220(%rsp),%rdi
  a982e8:	mov    $0xfe4840,%esi
  a982ed:	call   899620 <CEGUI::String::String(char const*)>
  a982f2:	lea    0x220(%rsp),%rdx
  a982fa:	lea    0x170(%rsp),%rdi
  a98302:	mov    %rbx,%rsi
  a98305:	mov    $0x1,%r15d
  a9830b:	call   554418 <CEGUI::PropertySet::getProperty(CEGUI::String const&) const@plt>
  a98310:	cmpq   $0x0,0x170(%rsp)
  a98319:	lea    0x170(%rsp),%rdi
  a98321:	setne  %r13b
  a98325:	call   555fe8 <CEGUI::String::~String()@plt>
  a9832a:	lea    0x220(%rsp),%rdi
  a98332:	call   555fe8 <CEGUI::String::~String()@plt>
  a98337:	jmp    a98174 <CGameUI::mapToFunctions(CEGUI::Window*)+0x94>
  a9833c:	mov    %rax,%rdi
  a9833f:	add    $0x1910,%rbp
  a98346:	call   552938 <__cxa_begin_catch@plt>
  a9834b:	mov    %rbp,0x1d8(%rbx)
  a98352:	call   554bd8 <__cxa_end_catch@plt>
  a98357:	jmp    a9818f <CGameUI::mapToFunctions(CEGUI::Window*)+0xaf>
  a9835c:	mov    %r13,%rdi
  a9835f:	mov    %rax,0x8(%rsp)
  a98364:	call   555fe8 <CEGUI::String::~String()@plt>
  a98369:	mov    0x8(%rsp),%rax
  a9836e:	jmp    a9833c <CGameUI::mapToFunctions(CEGUI::Window*)+0x25c>
  a98370:	mov    %r12,%rdi
  a98373:	mov    %rax,0x8(%rsp)
  a98378:	call   555fe8 <CEGUI::String::~String()@plt>
  a9837d:	mov    0x8(%rsp),%rax
  a98382:	jmp    a9835c <CGameUI::mapToFunctions(CEGUI::Window*)+0x27c>
  a98384:	mov    %r14,%rdi
  a98387:	mov    %rax,0x8(%rsp)
  a9838c:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  a98391:	mov    0x8(%rsp),%rax
  a98396:	jmp    a98370 <CGameUI::mapToFunctions(CEGUI::Window*)+0x290>
  a98398:	mov    $0x5541c8,%eax
  a9839d:	test   %rax,%rax
  a983a0:	je     a983d8 <CGameUI::mapToFunctions(CEGUI::Window*)+0x2f8>
  a983a2:	or     $0xffffffff,%eax
  a983a5:	lock xadd %eax,0x10(%rdi)
  a983aa:	test   %eax,%eax
  a983ac:	jg     a9821f <CGameUI::mapToFunctions(CEGUI::Window*)+0x13f>
  a983b2:	lea    0x39e(%rsp),%rsi
  a983ba:	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  a983bf:	jmp    a9821f <CGameUI::mapToFunctions(CEGUI::Window*)+0x13f>
  a983c4:	mov    %r15,%rdi
  a983c7:	mov    %rax,0x8(%rsp)
  a983cc:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  a983d1:	mov    0x8(%rsp),%rax
  a983d6:	jmp    a9835c <CGameUI::mapToFunctions(CEGUI::Window*)+0x27c>
  a983d8:	mov    0x10(%rdi),%eax
  a983db:	lea    -0x1(%rax),%edx
  a983de:	mov    %edx,0x10(%rdi)
  a983e1:	jmp    a983aa <CGameUI::mapToFunctions(CEGUI::Window*)+0x2ca>
  a983e3:	mov    %r15,%rdi
  a983e6:	mov    %rax,0x8(%rsp)
  a983eb:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  a983f0:	mov    0x8(%rsp),%rax
  a983f5:	jmp    a9833c <CGameUI::mapToFunctions(CEGUI::Window*)+0x25c>
  a983fa:	lea    0x220(%rsp),%rdi
  a98402:	mov    %rax,0x8(%rsp)
  a98407:	call   555fe8 <CEGUI::String::~String()@plt>
  a9840c:	mov    0x8(%rsp),%rax
  a98411:	test   %r14b,%r14b
  a98414:	je     a9833c <CGameUI::mapToFunctions(CEGUI::Window*)+0x25c>
  a9841a:	mov    %r12,%rdi
  a9841d:	mov    %rax,0x8(%rsp)
  a98422:	call   555fe8 <CEGUI::String::~String()@plt>
  a98427:	mov    0x8(%rsp),%rax
  a9842c:	jmp    a9833c <CGameUI::mapToFunctions(CEGUI::Window*)+0x25c>
  a98431:	jmp    a9833c <CGameUI::mapToFunctions(CEGUI::Window*)+0x25c>
  a98436:	test   %r15b,%r15b
  a98439:	je     a98411 <CGameUI::mapToFunctions(CEGUI::Window*)+0x331>
  a9843b:	nopl   0x0(%rax,%rax,1)
  a98440:	jmp    a983fa <CGameUI::mapToFunctions(CEGUI::Window*)+0x31a>
  a98442:	jmp    a9841a <CGameUI::mapToFunctions(CEGUI::Window*)+0x33a>
  a98444:	mov    0x10(%r8),%eax
  a98448:	lea    -0x1(%rax),%edx
  a9844b:	mov    %edx,0x10(%r8)
  a9844f:	jmp    a982bd <CGameUI::mapToFunctions(CEGUI::Window*)+0x1dd>
