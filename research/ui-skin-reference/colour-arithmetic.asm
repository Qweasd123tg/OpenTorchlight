
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000000c7000 <CEGUI::ColourRect::getColourAtPoint(float, float) const>:
   c7000:	push   %rbp
   c7001:	movaps %xmm1,%xmm5
   c7004:	movaps %xmm0,%xmm4
   c7007:	mov    %rsi,%rbp
   c700a:	push   %rbx
   c700b:	mov    %rdi,%rbx
   c700e:	sub    $0x128,%rsp
   c7015:	movss  0x18(%rsi),%xmm3
   c701a:	lea    0xe0(%rsp),%rdi
   c7022:	movss  0x24(%rsi),%xmm2
   c7027:	subss  (%rsi),%xmm3
   c702b:	movss  0x20(%rsi),%xmm1
   c7030:	subss  0xc(%rsi),%xmm2
   c7035:	movss  0x1c(%rsi),%xmm0
   c703a:	subss  0x8(%rsi),%xmm1
   c703f:	subss  0x4(%rsi),%xmm0
   c7044:	movss  %xmm5,(%rsp)
   c7049:	movss  %xmm4,0x10(%rsp)
   c704f:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c7054:	movss  0x10(%rsp),%xmm4
   c705a:	lea    0xc0(%rsp),%rdi
   c7062:	movss  0xe4(%rsp),%xmm0
   c706b:	movss  0xe0(%rsp),%xmm3
   c7074:	mulss  %xmm4,%xmm0
   c7078:	movss  0xec(%rsp),%xmm2
   c7081:	mulss  %xmm4,%xmm3
   c7085:	movss  0xe8(%rsp),%xmm1
   c708e:	mulss  %xmm4,%xmm2
   c7092:	mulss  %xmm4,%xmm1
   c7096:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c709b:	movss  0xc4(%rsp),%xmm0
   c70a4:	lea    0x100(%rsp),%rdi
   c70ac:	movss  0xc0(%rsp),%xmm3
   c70b5:	addss  0x4(%rbp),%xmm0
   c70ba:	movss  0xcc(%rsp),%xmm2
   c70c3:	addss  0x0(%rbp),%xmm3
   c70c8:	movss  0xc8(%rsp),%xmm1
   c70d1:	addss  0xc(%rbp),%xmm2
   c70d6:	addss  0x8(%rbp),%xmm1
   c70db:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c70e0:	movss  0x48(%rbp),%xmm3
   c70e5:	lea    0x80(%rsp),%rdi
   c70ed:	movss  0x54(%rbp),%xmm2
   c70f2:	subss  0x30(%rbp),%xmm3
   c70f7:	movss  0x50(%rbp),%xmm1
   c70fc:	subss  0x3c(%rbp),%xmm2
   c7101:	movss  0x4c(%rbp),%xmm0
   c7106:	subss  0x38(%rbp),%xmm1
   c710b:	subss  0x34(%rbp),%xmm0
   c7110:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c7115:	movss  0x10(%rsp),%xmm4
   c711b:	lea    0x60(%rsp),%rdi
   c7120:	movss  0x84(%rsp),%xmm0
   c7129:	movss  0x80(%rsp),%xmm3
   c7132:	mulss  %xmm4,%xmm0
   c7136:	movss  0x8c(%rsp),%xmm2
   c713f:	mulss  %xmm4,%xmm3
   c7143:	movss  0x88(%rsp),%xmm1
   c714c:	mulss  %xmm4,%xmm2
   c7150:	mulss  %xmm4,%xmm1
   c7154:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c7159:	movss  0x64(%rsp),%xmm0
   c715f:	lea    0xa0(%rsp),%rdi
   c7167:	movss  0x60(%rsp),%xmm3
   c716d:	addss  0x34(%rbp),%xmm0
   c7172:	movss  0x6c(%rsp),%xmm2
   c7178:	addss  0x30(%rbp),%xmm3
   c717d:	movss  0x68(%rsp),%xmm1
   c7183:	addss  0x3c(%rbp),%xmm2
   c7188:	addss  0x38(%rbp),%xmm1
   c718d:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c7192:	movss  0xa4(%rsp),%xmm0
   c719b:	lea    0x40(%rsp),%rdi
   c71a0:	movss  0xa0(%rsp),%xmm3
   c71a9:	subss  0x104(%rsp),%xmm0
   c71b2:	movss  0xac(%rsp),%xmm2
   c71bb:	subss  0x100(%rsp),%xmm3
   c71c4:	movss  0xa8(%rsp),%xmm1
   c71cd:	subss  0x10c(%rsp),%xmm2
   c71d6:	subss  0x108(%rsp),%xmm1
   c71df:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c71e4:	movss  (%rsp),%xmm5
   c71e9:	lea    0x20(%rsp),%rdi
   c71ee:	movss  0x44(%rsp),%xmm0
   c71f4:	movss  0x40(%rsp),%xmm3
   c71fa:	mulss  %xmm5,%xmm0
   c71fe:	movss  0x4c(%rsp),%xmm2
   c7204:	mulss  %xmm5,%xmm3
   c7208:	movss  0x48(%rsp),%xmm1
   c720e:	mulss  %xmm5,%xmm2
   c7212:	mulss  %xmm5,%xmm1
   c7216:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c721b:	movss  0x24(%rsp),%xmm0
   c7221:	mov    %rbx,%rdi
   c7224:	movss  0x20(%rsp),%xmm3
   c722a:	addss  0x104(%rsp),%xmm0
   c7233:	movss  0x2c(%rsp),%xmm2
   c7239:	addss  0x100(%rsp),%xmm3
   c7242:	movss  0x28(%rsp),%xmm1
   c7248:	addss  0x10c(%rsp),%xmm2
   c7251:	addss  0x108(%rsp),%xmm1
   c725a:	call   c3bc8 <CEGUI::colour::colour(float, float, float, float)@plt>
   c725f:	mov    %rbx,%rax
   c7262:	add    $0x128,%rsp
   c7269:	pop    %rbx
   c726a:	pop    %rbp
   c726b:	ret
   c726c:	nopl   0x0(%rax)

00000000000c7270 <CEGUI::ColourRect::ColourRect()>:
   c7270:	push   %rbx
   c7271:	mov    %rdi,%rbx
   c7274:	call   c0ff8 <CEGUI::colour::colour()@plt>
   c7279:	lea    0x18(%rbx),%rdi
   c727d:	call   c0ff8 <CEGUI::colour::colour()@plt>
   c7282:	lea    0x30(%rbx),%rdi
   c7286:	call   c0ff8 <CEGUI::colour::colour()@plt>
   c728b:	lea    0x48(%rbx),%rdi
   c728f:	pop    %rbx
   c7290:	jmp    c0ff8 <CEGUI::colour::colour()@plt>
   c7295:	nop
   c7296:	cs nopw 0x0(%rax,%rax,1)

00000000000c72a0 <CEGUI::ColourRect::ColourRect(CEGUI::colour const&)>:
   c72a0:	mov    %rbx,-0x10(%rsp)
   c72a5:	mov    %rbp,-0x8(%rsp)
   c72aa:	sub    $0x18,%rsp
   c72ae:	mov    %rdi,%rbp
   c72b1:	mov    %rsi,%rbx
   c72b4:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c72b9:	lea    0x18(%rbp),%rdi
   c72bd:	mov    %rbx,%rsi
   c72c0:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c72c5:	lea    0x30(%rbp),%rdi
   c72c9:	mov    %rbx,%rsi
   c72cc:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c72d1:	lea    0x48(%rbp),%rdi
   c72d5:	mov    %rbx,%rsi
   c72d8:	mov    0x10(%rsp),%rbp
   c72dd:	mov    0x8(%rsp),%rbx
   c72e2:	add    $0x18,%rsp
   c72e6:	jmp    c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c72eb:	nop
   c72ec:	nopl   0x0(%rax)

00000000000c72f0 <CEGUI::ColourRect::ColourRect(CEGUI::colour const&, CEGUI::colour const&, CEGUI::colour const&, CEGUI::colour const&)>:
   c72f0:	mov    %rbx,-0x20(%rsp)
   c72f5:	mov    %rbp,-0x18(%rsp)
   c72fa:	mov    %rdi,%rbx
   c72fd:	mov    %r12,-0x10(%rsp)
   c7302:	mov    %r13,-0x8(%rsp)
   c7307:	sub    $0x28,%rsp
   c730b:	mov    %rdx,%rbp
   c730e:	mov    %rcx,%r12
   c7311:	mov    %r8,%r13
   c7314:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c7319:	lea    0x18(%rbx),%rdi
   c731d:	mov    %rbp,%rsi
   c7320:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c7325:	lea    0x30(%rbx),%rdi
   c7329:	mov    %r12,%rsi
   c732c:	call   c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c7331:	lea    0x48(%rbx),%rdi
   c7335:	mov    %r13,%rsi
   c7338:	mov    0x8(%rsp),%rbx
   c733d:	mov    0x10(%rsp),%rbp
   c7342:	mov    0x18(%rsp),%r12
   c7347:	mov    0x20(%rsp),%r13
   c734c:	add    $0x28,%rsp
   c7350:	jmp    c3a58 <CEGUI::colour::colour(CEGUI::colour const&)@plt>
   c7355:	nop
   c7356:	cs nopw 0x0(%rax,%rax,1)

00000000000c7360 <CEGUI::ColourRect::getSubRectangle(float, float, float, float) const>:
   c7360:	movaps %xmm1,%xmm4
   c7363:	mov    %rbx,-0x30(%rsp)
   c7368:	mov    %rbp,-0x28(%rsp)
   c736d:	mov    %r12,-0x20(%rsp)
   c7372:	mov    %rdi,%rbx
   c7375:	mov    %r13,-0x18(%rsp)
   c737a:	mov    %r14,-0x10(%rsp)
   c737f:	mov    %rsi,%r14
   c7382:	mov    %r15,-0x8(%rsp)
   c7387:	sub    $0xe8,%rsp
   c738e:	lea    0x30(%rsp),%r15
   c7393:	movss  %xmm0,0x28(%rsp)
   c7399:	lea    0x50(%rsp),%r13
   c739e:	movaps %xmm4,%xmm0
   c73a1:	movss  %xmm2,0x2c(%rsp)
   c73a7:	movaps %xmm3,%xmm1
   c73aa:	mov    %r15,%rdi
   c73ad:	movss  %xmm4,(%rsp)
   c73b2:	lea    0x70(%rsp),%r12
   c73b7:	lea    0x90(%rsp),%rbp
   c73bf:	movss  %xmm3,0x10(%rsp)
   c73c5:	call   c5c98 <CEGUI::ColourRect::getColourAtPoint(float, float) const@plt>
   c73ca:	movss  0x10(%rsp),%xmm3
   c73d0:	mov    %r14,%rsi
   c73d3:	movaps %xmm3,%xmm1
   c73d6:	mov    %r13,%rdi
   c73d9:	movss  0x28(%rsp),%xmm0
   c73df:	call   c5c98 <CEGUI::ColourRect::getColourAtPoint(float, float) const@plt>
   c73e4:	movss  (%rsp),%xmm4
   c73e9:	mov    %r14,%rsi
   c73ec:	movaps %xmm4,%xmm0
   c73ef:	mov    %r12,%rdi
   c73f2:	movss  0x2c(%rsp),%xmm1
   c73f8:	call   c5c98 <CEGUI::ColourRect::getColourAtPoint(float, float) const@plt>
   c73fd:	movss  0x2c(%rsp),%xmm1
   c7403:	mov    %r14,%rsi
   c7406:	movss  0x28(%rsp),%xmm0
   c740c:	mov    %rbp,%rdi
   c740f:	call   c5c98 <CEGUI::ColourRect::getColourAtPoint(float, float) const@plt>
   c7414:	mov    %r15,%r8
   c7417:	mov    %r13,%rcx
   c741a:	mov    %r12,%rdx
   c741d:	mov    %rbp,%rsi
   c7420:	mov    %rbx,%rdi
   c7423:	call   c57e8 <CEGUI::ColourRect::ColourRect(CEGUI::colour const&, CEGUI::colour const&, CEGUI::colour const&, CEGUI::colour const&)@plt>
   c7428:	mov    %rbx,%rax
   c742b:	mov    0xc0(%rsp),%rbp
   c7433:	mov    0xb8(%rsp),%rbx
   c743b:	mov    0xc8(%rsp),%r12
   c7443:	mov    0xd0(%rsp),%r13
   c744b:	mov    0xd8(%rsp),%r14
   c7453:	mov    0xe0(%rsp),%r15
   c745b:	add    $0xe8,%rsp
   c7462:	ret
   c7463:	nop
   c7464:	nop
   c7465:	nop
   c7466:	nop
   c7467:	nop
   c7468:	nop
   c7469:	nop
   c746a:	nop
   c746b:	nop
   c746c:	nop
   c746d:	nop
   c746e:	nop
   c746f:	nop

00000000000c7470 <global constructors keyed to CEGUIConfig_xmlHandler.cpp>:
   c7470:	push   %rbx
   c7471:	mov    0x376220(%rip),%rbx        # 43d698 <CEGUI::Config_xmlHandler::CEGUIConfigElement@@Base-0x4e68>
   c7478:	mov    $0xb,%esi
   c747d:	movq   $0x20,0x8(%rbx)
   c7485:	movq   $0x0,0x10(%rbx)
   c748d:	mov    %rbx,%rdi
   c7490:	movq   $0x0,0x20(%rbx)
   c7498:	movq   $0x0,0x18(%rbx)
   c74a0:	movq   $0x0,0xa8(%rbx)
   c74ab:	movq   $0x0,(%rbx)
   c74b2:	movl   $0x0,0x28(%rbx)
   c74b9:	call   c61d8 <CEGUI::String::grow(unsigned long)@plt>
   c74be:	cmpq   $0x20,0x8(%rbx)
   c74c3:	lea    0x28(%rbx),%rdx
   c74c7:	lea    0x10f6b1(%rip),%rsi        # 1d6b7f <_fini+0xc7>
   c74ce:	cmova  0xa8(%rbx),%rdx
   c74d6:	lea    0x10f697(%rip),%rax        # 1d6b74 <_fini+0xbc>
   c74dd:	nopl   (%rax)
   c74e0:	movzbl (%rax),%ecx
   c74e3:	add    $0x1,%rax
   c74e7:	mov    %ecx,(%rdx)
   c74e9:	add    $0x4,%rdx
   c74ed:	cmp    %rsi,%rax
   c74f0:	jne    c74e0 <global constructors keyed to CEGUIConfig_xmlHandler.cpp+0x70>
   c74f2:	cmpq   $0x20,0x8(%rbx)
   c74f7:	movq   $0xb,(%rbx)
   c74fe:	lea    0x54(%rbx),%rax
   c7502:	jbe    c750f <global constructors keyed to CEGUIConfig_xmlHandler.cpp+0x9f>
   c7504:	mov    0xa8(%rbx),%rax
   c750b:	add    $0x2c,%rax
   c750f:	movl   $0x0,(%rax)
   c7515:	mov    %rbx,%rsi
   c7518:	mov    0x3753c1(%rip),%rdx        # 43c8e0 <.got+0xae8>
   c751f:	pop    %rbx
   c7520:	mov    0x374d89(%rip),%rdi        # 43c2b0 <CEGUI::String::~String()@@Base+0x337300>
   c7527:	jmp    c2538 <__cxa_atexit@plt>
   c752c:	nopl   0x0(%rax)

00000000000c7530 <CEGUI::Config_xmlHandler::elementStart(CEGUI::String const&, CEGUI::XMLAttributes const&)>:
   c7530:	push   %r15
   c7532:	push   %r14
   c7534:	push   %r13
   c7536:	push   %r12
   c7538:	push   %rbp
   c7539:	mov    %rsi,%rbp
   c753c:	push   %rbx
   c753d:	mov    %rdi,%rbx
   c7540:	mov    %rbp,%rdi
   c7543:	sub    $0xc78,%rsp
   c754a:	mov    0x376147(%rip),%rsi        # 43d698 <CEGUI::Config_xmlHandler::CEGUIConfigElement@@Base-0x4e68>
   c7551:	mov    %rdx,0x8(%rsp)
   c7556:	call   c4528 <CEGUI::operator==(CEGUI::String const&, CEGUI::String const&)@plt>
   c755b:	test   %al,%al
   c755d:	.byte 0xf
   c755e:	.byte 0x84
   c755f:	.byte 0x5
