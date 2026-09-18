
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000001d0a20 <CEGUI::Falagard_xmlHandler::elementAnyDimEnd()>:
  1d0a20:	mov    %rbx,-0x18(%rsp)
  1d0a25:	mov    %rbp,-0x10(%rsp)
  1d0a2a:	mov    %rdi,%rbx
  1d0a2d:	mov    %r12,-0x8(%rsp)
  1d0a32:	sub    $0x18,%rsp
  1d0a36:	mov    0xe0(%rdi),%rax
  1d0a3d:	cmp    0xd8(%rdi),%rax
  1d0a44:	je     1d0a90 <CEGUI::Falagard_xmlHandler::elementAnyDimEnd()+0x70>
  1d0a46:	lea    -0x8(%rax),%rdx
  1d0a4a:	cmp    0xd8(%rdi),%rdx
  1d0a51:	mov    -0x8(%rax),%rbp
  1d0a55:	mov    %rdx,0xe0(%rdi)
  1d0a5c:	je     1d0aa8 <CEGUI::Falagard_xmlHandler::elementAnyDimEnd()+0x88>
  1d0a5e:	mov    -0x8(%rdx),%rdi
  1d0a62:	mov    %rbp,%rsi
  1d0a65:	call   bff68 <CEGUI::BaseDim::setOperand(CEGUI::BaseDim const&)@plt>
  1d0a6a:	test   %rbp,%rbp
  1d0a6d:	je     1d0a90 <CEGUI::Falagard_xmlHandler::elementAnyDimEnd()+0x70>
  1d0a6f:	mov    0x0(%rbp),%rax
  1d0a73:	mov    %rbp,%rdi
  1d0a76:	mov    (%rsp),%rbx
  1d0a7a:	mov    0x8(%rsp),%rbp
  1d0a7f:	mov    0x10(%rsp),%r12
  1d0a84:	mov    0x8(%rax),%rax
  1d0a88:	add    $0x18,%rsp
  1d0a8c:	jmp    *%rax
  1d0a8e:	xchg   %ax,%ax
  1d0a90:	mov    (%rsp),%rbx
  1d0a94:	mov    0x8(%rsp),%rbp
  1d0a99:	mov    0x10(%rsp),%r12
  1d0a9e:	add    $0x18,%rsp
  1d0aa2:	ret
  1d0aa3:	nopl   0x0(%rax,%rax,1)
  1d0aa8:	lea    0xb0(%rdi),%r12
  1d0aaf:	mov    %rbp,%rsi
  1d0ab2:	mov    %r12,%rdi
  1d0ab5:	call   c4938 <CEGUI::Dimension::setBaseDimension(CEGUI::BaseDim const&)@plt>
  1d0aba:	mov    %r12,%rsi
  1d0abd:	mov    %rbx,%rdi
  1d0ac0:	call   c2778 <CEGUI::Falagard_xmlHandler::assignAreaDimension(CEGUI::Dimension&)@plt>
  1d0ac5:	jmp    1d0a6a <CEGUI::Falagard_xmlHandler::elementAnyDimEnd()+0x4a>
  1d0ac7:	nop
  1d0ac8:	nopl   0x0(%rax,%rax,1)

00000000001d0ad0 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()>:
  1d0ad0:	push   %rbp
  1d0ad1:	push   %rbx
  1d0ad2:	mov    %rdi,%rbx
  1d0ad5:	sub    $0x8,%rsp
  1d0ad9:	mov    0x26c0d8(%rip),%rax        # 43cbb8 <vtable for CEGUI::Falagard_xmlHandler@@Base+0x1058>
  1d0ae0:	add    $0x10,%rax
  1d0ae4:	mov    %rax,(%rdi)
  1d0ae7:	mov    0xd8(%rdi),%rdi
  1d0aee:	test   %rdi,%rdi
  1d0af1:	je     1d0af8 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()+0x28>
  1d0af3:	call   c2a58 <operator delete(void*)@plt>
  1d0af8:	lea    0xb0(%rbx),%rdi
  1d0aff:	call   c4158 <CEGUI::Dimension::~Dimension()@plt>
  1d0b04:	mov    0x50(%rbx),%rsi
  1d0b08:	lea    0x40(%rbx),%rdi
  1d0b0c:	call   c5a88 <std::_Rb_tree<CEGUI::String, std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()>, std::_Select1st<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> >, CEGUI::String::FastLessCompare, std::allocator<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> > >::_M_erase(std::_Rb_tree_node<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> >*)@plt>
  1d0b11:	mov    0x20(%rbx),%rsi
  1d0b15:	lea    0x10(%rbx),%rdi
  1d0b19:	call   c5718 <std::_Rb_tree<CEGUI::String, std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)>, std::_Select1st<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> >, CEGUI::String::FastLessCompare, std::allocator<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> > >::_M_erase(std::_Rb_tree_node<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> >*)@plt>
  1d0b1e:	add    $0x8,%rsp
  1d0b22:	mov    %rbx,%rdi
  1d0b25:	pop    %rbx
  1d0b26:	pop    %rbp
  1d0b27:	jmp    c46f8 <CEGUI::XMLHandler::~XMLHandler()@plt>
  1d0b2c:	mov    0x50(%rbx),%rsi
  1d0b30:	lea    0x40(%rbx),%rdi
  1d0b34:	mov    %rax,%rbp
  1d0b37:	call   c5a88 <std::_Rb_tree<CEGUI::String, std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()>, std::_Select1st<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> >, CEGUI::String::FastLessCompare, std::allocator<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> > >::_M_erase(std::_Rb_tree_node<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)()> >*)@plt>
  1d0b3c:	mov    0x20(%rbx),%rsi
  1d0b40:	lea    0x10(%rbx),%rdi
  1d0b44:	call   c5718 <std::_Rb_tree<CEGUI::String, std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)>, std::_Select1st<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> >, CEGUI::String::FastLessCompare, std::allocator<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> > >::_M_erase(std::_Rb_tree_node<std::pair<CEGUI::String const, void (CEGUI::Falagard_xmlHandler::*)(CEGUI::XMLAttributes const&)> >*)@plt>
  1d0b49:	mov    %rbx,%rdi
  1d0b4c:	call   c46f8 <CEGUI::XMLHandler::~XMLHandler()@plt>
  1d0b51:	mov    %rbp,%rdi
  1d0b54:	call   c5cf8 <_Unwind_Resume@plt>
  1d0b59:	mov    %rax,%rbp
  1d0b5c:	jmp    1d0b49 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()+0x79>
  1d0b5e:	mov    %rax,%rbp
  1d0b61:	jmp    1d0b3c <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()+0x6c>
  1d0b63:	jmp    1d0b59 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()+0x89>
  1d0b65:	jmp    1d0b5e <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()+0x8e>
  1d0b67:	nop
  1d0b68:	nopl   0x0(%rax,%rax,1)

00000000001d0b70 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()>:
  1d0b70:	push   %rbx
  1d0b71:	mov    %rdi,%rbx
  1d0b74:	call   c49e8 <CEGUI::Falagard_xmlHandler::~Falagard_xmlHandler()@plt>
  1d0b79:	mov    %rbx,%rdi
  1d0b7c:	pop    %rbx
  1d0b7d:	jmp    c2a58 <operator delete(void*)@plt>
  1d0b82:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)

00000000001d0b90 <global constructors keyed to CEGUIFalagard_xmlHandler.cpp>:
  1d0b90:	push   %r12
  1d0b92:	mov    0x26dce7(%rip),%r12        # 43e880 <CEGUI::Falagard_xmlHandler::FalagardElement@@Base-0x2f2c0>
  1d0b99:	lea    0x15e40(%rip),%rsi        # 1e69e0 <typeinfo name for CEGUI::TextComponent+0x2a0>
  1d0ba0:	push   %rbp
  1d0ba1:	mov    %r12,%rdi
  1d0ba4:	push   %rbx
  1d0ba5:	call   bf408 <CEGUI::String::String(char const*)@plt>
  1d0baa:	mov    0x26b6ff(%rip),%rbx        # 43c2b0 <CEGUI::String::~String()@@Base+0x337300>
  1d0bb1:	mov    0x26bd28(%rip),%rbp        # 43c8e0 <.got+0xae8>
  1d0bb8:	mov    %r12,%rsi
  1d0bbb:	mov    %rbp,%rdx
  1d0bbe:	mov    %rbx,%rdi
  1d0bc1:	call   c2538 <__cxa_atexit@plt>
  1d0bc6:	mov    0x26b81b(%rip),%r12        # 43c3e8 <CEGUI::Falagard_xmlHandler::WidgetLookElement@@Base-0x31818>
  1d0bcd:	lea    0x15de8(%rip),%rsi        # 1e69bc <typeinfo name for CEGUI::TextComponent+0x27c>
  1d0bd4:	mov    %r12,%rdi
  1d0bd7:	call   bf408 <CEGUI::String::String(char const*)@plt>
  1d0bdc:	mov    %rbp,%rdx
  1d0bdf:	mov    %r12,%rsi
  1d0be2:	mov    %rbx,%rdi
  1d0be5:	call   c2538 <__cxa_atexit@plt>
  1d0bea:	mov    0x26bf77(%rip),%r12        # 43cb68 <CEGUI::Falagard_xmlHandler::ChildElement@@Base-0x31158>
  1d0bf1:	lea    0x9971(%rip),%rsi        # 1da569 <typeinfo name for CEGUI::MemberFunctionSlot<CEGUI::System>+0x489>
  1d0bf8:	mov    %r12,%rdi
  1d0bfb:	call   bf408 <CEGUI::String::String(char const*)@plt>
  1d0c00:	mov    %rbp,%rdx
  1d0c03:	mov    %r12,%rsi
  1d0c06:	mov    %rbx,%rdi
  1d0c09:	call   c2538 <__cxa_atexit@plt>
  1d0c0e:	mov    0x26b82b(%rip),%r12        # 43c440 <CEGUI::Falagard_xmlHandler::ImagerySectionElement@@Base-0x31940>
  1d0c15:	lea    0x158ef(%rip),%rsi        # 1e650b <typeinfo name for CEGUI::ImageryComponent+0x1b>
  1d0c1c:	mov    %r12,%rdi
  1d0c1f:	.byte 0xe8
