
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000001bb600 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::Rect const&, CEGUI::ColourRect const*, CEGUI::Rect const*) const>:
  1bb600:	push   %r15
  1bb602:	mov    %rcx,%r15
  1bb605:	push   %r14
  1bb607:	mov    %r8,%r14
  1bb60a:	push   %r13
  1bb60c:	lea    0xb8(%rdi),%r13
  1bb613:	push   %r12
  1bb615:	mov    %rdi,%r12
  1bb618:	push   %rbp
  1bb619:	push   %rbx
  1bb61a:	sub    $0x18,%rsp
  1bb61e:	mov    0xc8(%rdi),%rbx
  1bb625:	mov    %rsi,(%rsp)
  1bb629:	mov    %rdx,0x8(%rsp)
  1bb62e:	cmp    %r13,%rbx
  1bb631:	je     1bb683 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::Rect const&, CEGUI::ColourRect const*, CEGUI::Rect const*) const+0x83>
  1bb633:	nopl   0x0(%rax,%rax,1)
  1bb638:	lea    0x20(%rbx),%rbp
  1bb63c:	mov    %rbp,%rdi
  1bb63f:	call   c0068 <CEGUI::LayerSpecification::getLayerPriority() const@plt>
  1bb644:	mov    %eax,%eax
  1bb646:	movzbl 0xe0(%r12),%r9d
  1bb64f:	mov    0x8(%rsp),%rdx
  1bb654:	cvtsi2ss %rax,%xmm0
  1bb659:	mov    (%rsp),%rsi
  1bb65d:	mov    %r14,%r8
  1bb660:	mov    %r15,%rcx
  1bb663:	mov    %rbp,%rdi
  1bb666:	mulss  0x2b0a2(%rip),%xmm0        # 1e6710 <typeinfo name for CEGUI::PropertyLinkDefinition+0x50>
  1bb66e:	call   c41f8 <CEGUI::LayerSpecification::render(CEGUI::Window&, CEGUI::Rect const&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const@plt>
  1bb673:	mov    %rbx,%rdi
  1bb676:	call   c36d8 <std::_Rb_tree_increment(std::_Rb_tree_node_base const*)@plt>
  1bb67b:	cmp    %r13,%rax
  1bb67e:	mov    %rax,%rbx
  1bb681:	jne    1bb638 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::Rect const&, CEGUI::ColourRect const*, CEGUI::Rect const*) const+0x38>
  1bb683:	add    $0x18,%rsp
  1bb687:	pop    %rbx
  1bb688:	pop    %rbp
  1bb689:	pop    %r12
  1bb68b:	pop    %r13
  1bb68d:	pop    %r14
  1bb68f:	pop    %r15
  1bb691:	ret
  1bb692:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)

00000000001bb6a0 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::ColourRect const*, CEGUI::Rect const*) const>:
  1bb6a0:	push   %r15
  1bb6a2:	mov    %rdx,%r15
  1bb6a5:	push   %r14
  1bb6a7:	mov    %rcx,%r14
  1bb6aa:	push   %r13
  1bb6ac:	lea    0xb8(%rdi),%r13
  1bb6b3:	push   %r12
  1bb6b5:	mov    %rdi,%r12
  1bb6b8:	push   %rbp
  1bb6b9:	push   %rbx
  1bb6ba:	sub    $0x18,%rsp
  1bb6be:	mov    0xc8(%rdi),%rbx
  1bb6c5:	mov    %rsi,0x8(%rsp)
  1bb6ca:	cmp    %r13,%rbx
  1bb6cd:	je     1bb717 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::ColourRect const*, CEGUI::Rect const*) const+0x77>
  1bb6cf:	nop
  1bb6d0:	lea    0x20(%rbx),%rbp
  1bb6d4:	mov    %rbp,%rdi
  1bb6d7:	call   c0068 <CEGUI::LayerSpecification::getLayerPriority() const@plt>
  1bb6dc:	mov    %eax,%eax
  1bb6de:	movzbl 0xe0(%r12),%r8d
  1bb6e7:	mov    0x8(%rsp),%rsi
  1bb6ec:	cvtsi2ss %rax,%xmm0
  1bb6f1:	mov    %r14,%rcx
  1bb6f4:	mov    %r15,%rdx
  1bb6f7:	mov    %rbp,%rdi
  1bb6fa:	mulss  0x2b00e(%rip),%xmm0        # 1e6710 <typeinfo name for CEGUI::PropertyLinkDefinition+0x50>
  1bb702:	call   c2748 <CEGUI::LayerSpecification::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const@plt>
  1bb707:	mov    %rbx,%rdi
  1bb70a:	call   c36d8 <std::_Rb_tree_increment(std::_Rb_tree_node_base const*)@plt>
  1bb70f:	cmp    %r13,%rax
  1bb712:	mov    %rax,%rbx
  1bb715:	jne    1bb6d0 <CEGUI::StateImagery::render(CEGUI::Window&, CEGUI::ColourRect const*, CEGUI::Rect const*) const+0x30>
  1bb717:	add    $0x18,%rsp
  1bb71b:	pop    %rbx
  1bb71c:	pop    %rbp
  1bb71d:	pop    %r12
  1bb71f:	pop    %r13
  1bb721:	pop    %r14
  1bb723:	pop    %r15
  1bb725:	ret
