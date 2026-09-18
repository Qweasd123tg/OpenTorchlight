
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000001cf760 <CEGUI::Falagard_xmlHandler::elementDimOperatorStart(CEGUI::XMLAttributes const&)>:
  1cf760:	mov    %rbx,-0x18(%rsp)
  1cf765:	mov    %r12,-0x8(%rsp)
  1cf76a:	mov    %rdi,%rbx
  1cf76d:	mov    %rbp,-0x10(%rsp)
  1cf772:	sub    $0xc8,%rsp
  1cf779:	mov    0xd8(%rdi),%rax
  1cf780:	cmp    %rax,0xe0(%rdi)
  1cf787:	mov    %rsi,%r12
  1cf78a:	je     1cf7cf <CEGUI::Falagard_xmlHandler::elementDimOperatorStart(CEGUI::XMLAttributes const&)+0x6f>
  1cf78c:	lea    0x76f7(%rip),%rsi        # 1d6e8a <typeinfo name for std::out_of_range+0x23a>
  1cf793:	mov    %rsp,%rdi
  1cf796:	call   bf408 <CEGUI::String::String(char const*)@plt>
  1cf79b:	mov    0x26d596(%rip),%rsi        # 43cd38 <CEGUI::Falagard_xmlHandler::OperatorAttribute@@Base-0x33bc8>
  1cf7a2:	mov    %rsp,%rdx
  1cf7a5:	mov    %r12,%rdi
  1cf7a8:	call   c20c8 <CEGUI::XMLAttributes::getValueAsString(CEGUI::String const&, CEGUI::String const&) const@plt>
  1cf7ad:	mov    %rax,%rdi
  1cf7b0:	call   c2818 <CEGUI::FalagardXMLHelper::stringToDimensionOperator(CEGUI::String const&)@plt>
  1cf7b5:	mov    0xe0(%rbx),%rdx
  1cf7bc:	mov    %eax,%esi
  1cf7be:	mov    -0x8(%rdx),%rdi
  1cf7c2:	call   c5588 <CEGUI::BaseDim::setDimensionOperator(CEGUI::DimensionOperator)@plt>
  1cf7c7:	mov    %rsp,%rdi
  1cf7ca:	call   bffb8 <CEGUI::String::~String()@plt>
  1cf7cf:	mov    0xb0(%rsp),%rbx
  1cf7d7:	mov    0xb8(%rsp),%rbp
  1cf7df:	mov    0xc0(%rsp),%r12
  1cf7e7:	add    $0xc8,%rsp
  1cf7ee:	ret
  1cf7ef:	mov    %rax,%rbx
  1cf7f2:	mov    %rsp,%rdi
  1cf7f5:	call   bffb8 <CEGUI::String::~String()@plt>
  1cf7fa:	mov    %rbx,%rdi
  1cf7fd:	call   c5cf8 <_Unwind_Resume@plt>
  1cf802:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)

00000000001cf810 <CEGUI::Falagard_xmlHandler::elementColourRectPropertyStart(CEGUI::XMLAttributes const&)>:
  1cf810:	mov    %rbx,-0x18(%rsp)
  1cf815:	mov    %r12,-0x8(%rsp)
  1cf81a:	mov    %rdi,%rbx
  1cf81d:	mov    %rbp,-0x10(%rsp)
  1cf822:	sub    $0x388,%rsp
  1cf829:	cmpq   $0x0,0xd0(%rdi)
  1cf831:	mov    %rsi,%r12
  1cf834:	je     1cf8b0 <CEGUI::Falagard_xmlHandler::elementColourRectPropertyStart(CEGUI::XMLAttributes const&)+0xa0>
  1cf836:	lea    0x2c0(%rsp),%rbp
  1cf83e:	lea    0x7645(%rip),%rsi        # 1d6e8a <typeinfo name for std::out_of_range+0x23a>
  1cf845:	mov    %rbp,%rdi
  1cf848:	call   bf408 <CEGUI::String::String(char const*)@plt>
  1cf84d:	mov    0x26e44c(%rip),%rsi        # 43dca0 <CEGUI::Falagard_xmlHandler::NameAttribute@@Base-0x32120>
  1cf854:	mov    %rbp,%rdx
  1cf857:	mov    %r12,%rdi
  1cf85a:	call   c20c8 <CEGUI::XMLAttributes::getValueAsString(CEGUI::String const&, CEGUI::String const&) const@plt>
  1cf85f:	mov    0xd0(%rbx),%rdi
  1cf866:	mov    %rax,%rsi
  1cf869:	call   bfac8 <CEGUI::FalagardComponentBase::setColoursPropertySource(CEGUI::String const&)@plt>
  1cf86e:	rex.W
  1cf86f:	.byte 0x89
