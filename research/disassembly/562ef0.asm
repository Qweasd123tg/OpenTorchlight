
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000562ef0 <CGame::begin(void*)>:
  562ef0:	push   %r15
  562ef2:	push   %r14
  562ef4:	push   %r13
  562ef6:	push   %r12
  562ef8:	push   %rbp
  562ef9:	push   %rbx
  562efa:	mov    %rdi,%rbx
  562efd:	sub    $0xd8,%rsp
  562f04:	mov    %rsi,0xa8(%rdi)
  562f0b:	mov    $0x1424b98,%esi
  562f10:	lea    0xa0(%rsp),%r12
  562f18:	lea    0xb0(%rsp),%rbp
  562f20:	mov    %r12,%rdi
  562f23:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  562f28:	lea    0xcf(%rsp),%rdx
  562f30:	mov    $0xfa31a0,%esi
  562f35:	mov    %rbp,%rdi
  562f38:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  562f3d:	mov    (%rbx),%rax
  562f40:	mov    %rbx,%rdi
  562f43:	call   *0x18(%rax)
  562f46:	mov    0x140(%rax),%rsi
  562f4d:	lea    0x90(%rsp),%rdi
  562f55:	mov    %r12,%rcx
  562f58:	mov    %rbp,%rdx
  562f5b:	call   c8acf0 <CCmdLineParser::GetStringParam(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  562f60:	mov    0x90(%rsp),%r12
  562f68:	mov    0xec1c29(%rip),%rsi        # 1424b98 <EMPTY_WSTRING>
  562f6f:	xor    %r14d,%r14d
  562f72:	mov    -0x18(%r12),%rdx
  562f77:	cmp    -0x18(%rsi),%rdx
  562f7b:	lea    -0x18(%r12),%r13
  562f80:	je     563233 <CGame::begin(void*)+0x343>
  562f86:	mov    $0x1424540,%ebp
  562f8b:	cmp    %rbp,%r13
  562f8e:	jne    563341 <CGame::begin(void*)+0x451>
  562f94:	mov    0xb0(%rsp),%rdi
  562f9c:	sub    $0x18,%rdi
  562fa0:	cmp    %rdi,%rbp
  562fa3:	jne    56325d <CGame::begin(void*)+0x36d>
  562fa9:	mov    0xa0(%rsp),%rdi
  562fb1:	sub    $0x18,%rdi
  562fb5:	cmp    %rdi,%rbp
  562fb8:	jne    5633c0 <CGame::begin(void*)+0x4d0>
  562fbe:	lea    0x70(%rsp),%r13
  562fc3:	mov    $0x1424b98,%esi
  562fc8:	lea    0x80(%rsp),%r12
  562fd0:	mov    %r13,%rdi
  562fd3:	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  562fd8:	lea    0xce(%rsp),%rdx
  562fe0:	mov    $0xfa31c8,%esi
  562fe5:	mov    %r12,%rdi
  562fe8:	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  562fed:	mov    0xb8(%rbx),%rax
  562ff4:	lea    0x60(%rsp),%rdi
  562ff9:	mov    %r13,%rcx
  562ffc:	mov    %r12,%rdx
  562fff:	mov    0x140(%rax),%rsi
  563006:	call   c8acf0 <CCmdLineParser::GetStringParam(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  56300b:	mov    0x60(%rsp),%r12
  563010:	mov    0xec1b81(%rip),%rsi        # 1424b98 <EMPTY_WSTRING>
  563017:	xor    %r15d,%r15d
  56301a:	mov    -0x18(%r12),%rdx
  56301f:	cmp    -0x18(%rsi),%rdx
  563023:	lea    -0x18(%r12),%r13
  563028:	je     56321d <CGame::begin(void*)+0x32d>
  56302e:	cmp    %r13,%rbp
  563031:	jne    5632f7 <CGame::begin(void*)+0x407>
  563037:	mov    0x80(%rsp),%rdi
  56303f:	sub    $0x18,%rdi
  563043:	cmp    %rdi,%rbp
  563046:	jne    5632cb <CGame::begin(void*)+0x3db>
  56304c:	mov    0x70(%rsp),%rdi
  563051:	sub    $0x18,%rdi
  563055:	cmp    %rdi,%rbp
  563058:	jne    563289 <CGame::begin(void*)+0x399>
  56305e:	mov    (%rbx),%rax
  563061:	mov    %r15d,%esi
  563064:	mov    %rbx,%rdi
  563067:	call   *0x60(%rax)
  56306a:	test   %al,%al
  56306c:	jne    56309f <CGame::begin(void*)+0x1af>
  56306e:	cmpb   $0x0,0xebe02f(%rip)        # 14210a4 <gUseSplash>
  563075:	mov    $0x80004005,%eax
  56307a:	jne    56308e <CGame::begin(void*)+0x19e>
  56307c:	add    $0xd8,%rsp
  563083:	pop    %rbx
  563084:	pop    %rbp
  563085:	pop    %r12
  563087:	pop    %r13
  563089:	pop    %r14
  56308b:	pop    %r15
  56308d:	ret
  56308e:	mov    $0x1424b60,%edi
  563093:	call   eaa0a0 <CSplash::Hide()>
  563098:	mov    $0x80004005,%eax
  56309d:	jmp    56307c <CGame::begin(void*)+0x18c>
  56309f:	test   %r14b,%r14b
  5630a2:	je     563246 <CGame::begin(void*)+0x356>
  5630a8:	mov    0x80(%rbx),%rdi
  5630af:	test   %rdi,%rdi
  5630b2:	je     563149 <CGame::begin(void*)+0x259>
  5630b8:	mov    (%rdi),%rax
  5630bb:	mov    $0x1,%esi
  5630c0:	call   *0x1d0(%rax)
  5630c6:	mov    0xb4(%rbx),%r12d
  5630cd:	mov    0xb0(%rbx),%ebp
  5630d3:	call   a828e0 <CGameUI::getSingleton()>
  5630d8:	test   %rax,%rax
  5630db:	je     563149 <CGame::begin(void*)+0x259>
  5630dd:	lea    0xc4(%rsp),%rcx
  5630e5:	lea    0xc0(%rsp),%r8
  5630ed:	mov    %r12d,%edx
  5630f0:	mov    %ebp,%esi
  5630f2:	mov    $0x1424b60,%edi
  5630f7:	call   eaa020 <CSplash::findCenterForWindow(int, int, int&, int&)>
  5630fc:	cvtsi2ssl 0xc0(%rsp),%xmm1
  563105:	cvtsi2ssl 0xc4(%rsp),%xmm0
  56310e:	movss  %xmm1,0x10(%rsp)
  563114:	movss  %xmm0,(%rsp)
  563119:	call   555678 <CEGUI::System::getSingleton()@plt>
  56311e:	movss  0x10(%rsp),%xmm1
  563124:	mov    %rax,%rdi
  563127:	movss  (%rsp),%xmm0
  56312c:	call   554108 <CEGUI::System::injectMousePosition(float, float)@plt>
  563131:	call   555678 <CEGUI::System::getSingleton()@plt>
  563136:	xorps  %xmm1,%xmm1
  563139:	mov    %rax,%rdi
  56313c:	movss  0xa416b8(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  563144:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  563149:	mov    0x40(%rbx),%rdi
  56314d:	lea    0x2a8(%rbx),%r12
  563154:	lea    0x20(%rsp),%rbp
  563159:	call   555e08 <Ogre::Root::clearEventTimes()@plt>
  56315e:	xchg   %ax,%ax
  563160:	xor    %r13d,%r13d
  563163:	nopl   0x0(%rax,%rax,1)
  563168:	mov    %rbp,%rdi
  56316b:	call   555e98 <SDL_PollEvent@plt>
  563170:	test   %eax,%eax
  563172:	je     56319d <CGame::begin(void*)+0x2ad>
  563174:	mov    0x20(%rsp),%eax
  563178:	cmp    $0x100,%eax
  56317d:	je     5631e0 <CGame::begin(void*)+0x2f0>
  56317f:	cmp    $0x200,%eax
  563184:	je     5631c0 <CGame::begin(void*)+0x2d0>
  563186:	mov    %rbp,%rsi
  563189:	mov    %r12,%rdi
  56318c:	call   ed6700 <SDLEventHandler::ProcessEvent(SDL_Event const&)>
  563191:	mov    %rbp,%rdi
  563194:	call   555e98 <SDL_PollEvent@plt>
  563199:	test   %eax,%eax
  56319b:	jne    563174 <CGame::begin(void*)+0x284>
  56319d:	mov    0x40(%rbx),%rdi
  5631a1:	call   553178 <Ogre::Root::renderOneFrame()@plt>
  5631a6:	test   %al,%al
  5631a8:	je     5631af <CGame::begin(void*)+0x2bf>
  5631aa:	test   %r13b,%r13b
  5631ad:	je     563160 <CGame::begin(void*)+0x270>
  5631af:	mov    %rbx,%rdi
  5631b2:	call   5580e0 <CGame::cleanUpGameObjects()>
  5631b7:	xor    %eax,%eax
  5631b9:	jmp    56307c <CGame::begin(void*)+0x18c>
  5631be:	xchg   %ax,%ax
  5631c0:	movzbl 0x2c(%rsp),%eax
  5631c5:	cmp    $0x4,%al
  5631c7:	je     5631f0 <CGame::begin(void*)+0x300>
  5631c9:	cmp    $0xe,%al
  5631cb:	jne    563186 <CGame::begin(void*)+0x296>
  5631cd:	mov    %rbp,%rdi
  5631d0:	movl   $0x100,0x20(%rsp)
  5631d8:	call   554c88 <SDL_PushEvent@plt>
  5631dd:	jmp    563186 <CGame::begin(void*)+0x296>
  5631df:	nop
  5631e0:	mov    $0x1,%r13d
  5631e6:	jmp    563168 <CGame::begin(void*)+0x278>
  5631e8:	nopl   0x0(%rax,%rax,1)
  5631f0:	mov    0x80(%rbx),%rdi
  5631f7:	mov    0x34(%rsp),%edx
  5631fb:	mov    0x30(%rsp),%esi
  5631ff:	mov    (%rdi),%rax
  563202:	call   *0x1c0(%rax)
  563208:	mov    0x80(%rbx),%rdi
  56320f:	mov    (%rdi),%rax
  563212:	call   *0x1b8(%rax)
  563218:	jmp    563186 <CGame::begin(void*)+0x296>
  56321d:	mov    %r12,%rdi
  563220:	xor    %r15d,%r15d
  563223:	call   5553e8 <wmemcmp@plt>
  563228:	test   %eax,%eax
  56322a:	sete   %r15b
  56322e:	jmp    56302e <CGame::begin(void*)+0x13e>
  563233:	mov    %r12,%rdi
  563236:	call   5553e8 <wmemcmp@plt>
  56323b:	test   %eax,%eax
  56323d:	sete   %r14b
  563241:	jmp    562f86 <CGame::begin(void*)+0x96>
  563246:	mov    %rbx,%rdi
  563249:	call   5621a0 <CGame::convertAssetsToBinary()>
  56324e:	mov    %rbx,%rdi
  563251:	call   5580e0 <CGame::cleanUpGameObjects()>
  563256:	xor    %eax,%eax
  563258:	jmp    56307c <CGame::begin(void*)+0x18c>
  56325d:	mov    $0x5541c8,%eax
  563262:	test   %rax,%rax
  563265:	je     5632b5 <CGame::begin(void*)+0x3c5>
  563267:	or     $0xffffffff,%eax
  56326a:	lock xadd %eax,0x10(%rdi)
  56326f:	test   %eax,%eax
  563271:	jg     562fa9 <CGame::begin(void*)+0xb9>
  563277:	lea    0xcc(%rsp),%rsi
  56327f:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  563284:	jmp    562fa9 <CGame::begin(void*)+0xb9>
  563289:	mov    $0x5541c8,%eax
  56328e:	test   %rax,%rax
  563291:	je     5632c0 <CGame::begin(void*)+0x3d0>
  563293:	or     $0xffffffff,%eax
  563296:	lock xadd %eax,0x10(%rdi)
  56329b:	test   %eax,%eax
  56329d:	jg     56305e <CGame::begin(void*)+0x16e>
  5632a3:	lea    0xc8(%rsp),%rsi
  5632ab:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  5632b0:	jmp    56305e <CGame::begin(void*)+0x16e>
  5632b5:	mov    0x10(%rdi),%eax
  5632b8:	lea    -0x1(%rax),%edx
  5632bb:	mov    %edx,0x10(%rdi)
  5632be:	jmp    56326f <CGame::begin(void*)+0x37f>
  5632c0:	mov    0x10(%rdi),%eax
  5632c3:	lea    -0x1(%rax),%edx
  5632c6:	mov    %edx,0x10(%rdi)
  5632c9:	jmp    56329b <CGame::begin(void*)+0x3ab>
  5632cb:	mov    $0x5541c8,%eax
  5632d0:	test   %rax,%rax
  5632d3:	je     563327 <CGame::begin(void*)+0x437>
  5632d5:	or     $0xffffffff,%eax
  5632d8:	lock xadd %eax,0x10(%rdi)
  5632dd:	test   %eax,%eax
  5632df:	jg     56304c <CGame::begin(void*)+0x15c>
  5632e5:	lea    0xc9(%rsp),%rsi
  5632ed:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  5632f2:	jmp    56304c <CGame::begin(void*)+0x15c>
  5632f7:	mov    $0x5541c8,%eax
  5632fc:	test   %rax,%rax
  5632ff:	je     563332 <CGame::begin(void*)+0x442>
  563301:	or     $0xffffffff,%eax
  563304:	lock xadd %eax,0x10(%r13)
  56330a:	test   %eax,%eax
  56330c:	jg     563037 <CGame::begin(void*)+0x147>
  563312:	lea    0xca(%rsp),%rsi
  56331a:	mov    %r13,%rdi
  56331d:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  563322:	jmp    563037 <CGame::begin(void*)+0x147>
  563327:	mov    0x10(%rdi),%eax
  56332a:	lea    -0x1(%rax),%edx
  56332d:	mov    %edx,0x10(%rdi)
  563330:	jmp    5632dd <CGame::begin(void*)+0x3ed>
  563332:	mov    -0x8(%r12),%eax
  563337:	lea    -0x1(%rax),%edx
  56333a:	mov    %edx,-0x8(%r12)
  56333f:	jmp    56330a <CGame::begin(void*)+0x41a>
  563341:	mov    $0x5541c8,%eax
  563346:	test   %rax,%rax
  563349:	je     56338c <CGame::begin(void*)+0x49c>
  56334b:	or     $0xffffffff,%eax
  56334e:	lock xadd %eax,0x10(%r13)
  563354:	test   %eax,%eax
  563356:	jg     562f94 <CGame::begin(void*)+0xa4>
  56335c:	lea    0xcd(%rsp),%rsi
  563364:	mov    %r13,%rdi
  563367:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  56336c:	jmp    562f94 <CGame::begin(void*)+0xa4>
  563371:	mov    %rbp,%rdi
  563374:	mov    %rax,%rbx
  563377:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  56337c:	mov    %r12,%rdi
  56337f:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  563384:	mov    %rbx,%rdi
  563387:	call   554498 <_Unwind_Resume@plt>
  56338c:	mov    -0x8(%r12),%eax
  563391:	lea    -0x1(%rax),%edx
  563394:	mov    %edx,-0x8(%r12)
  563399:	jmp    563354 <CGame::begin(void*)+0x464>
  56339b:	mov    %rax,%rbx
  56339e:	jmp    56337c <CGame::begin(void*)+0x48c>
  5633a0:	mov    %r12,%rdi
  5633a3:	mov    %rax,%rbx
  5633a6:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  5633ab:	mov    %r13,%rdi
  5633ae:	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  5633b3:	mov    %rbx,%rdi
  5633b6:	call   554498 <_Unwind_Resume@plt>
  5633bb:	mov    %rax,%rbx
  5633be:	jmp    5633ab <CGame::begin(void*)+0x4bb>
  5633c0:	mov    $0x5541c8,%eax
  5633c5:	test   %rax,%rax
  5633c8:	je     5633ec <CGame::begin(void*)+0x4fc>
  5633ca:	or     $0xffffffff,%eax
  5633cd:	lock xadd %eax,0x10(%rdi)
  5633d2:	test   %eax,%eax
  5633d4:	jg     562fbe <CGame::begin(void*)+0xce>
  5633da:	lea    0xcb(%rsp),%rsi
  5633e2:	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  5633e7:	jmp    562fbe <CGame::begin(void*)+0xce>
  5633ec:	mov    0x10(%rdi),%eax
  5633ef:	lea    -0x1(%rax),%edx
  5633f2:	mov    %edx,0x10(%rdi)
  5633f5:	jmp    5633d2 <CGame::begin(void*)+0x4e2>
