
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000001b1790 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const>:
  1b1790:	push   %r15
  1b1792:	push   %r14
  1b1794:	push   %r13
  1b1796:	mov    %rdx,%r13
  1b1799:	push   %r12
  1b179b:	mov    %rcx,%r12
  1b179e:	push   %rbp
  1b179f:	mov    %rsi,%rbp
  1b17a2:	push   %rbx
  1b17a3:	mov    %rdi,%rbx
  1b17a6:	sub    $0x78,%rsp
  1b17aa:	lea    0x10(%rsp),%r15
  1b17af:	movss  %xmm0,0x8(%rsp)
  1b17b5:	mov    %r8b,0xf(%rsp)
  1b17ba:	mov    %r15,%rdi
  1b17bd:	call   c4fd8 <CEGUI::ColourRect::ColourRect()@plt>
  1b17c2:	mov    %r15,%rdx
  1b17c5:	mov    %rbp,%rsi
  1b17c8:	mov    %rbx,%rdi
  1b17cb:	call   c62f8 <CEGUI::ImagerySection::initMasterColourRect(CEGUI::Window const&, CEGUI::ColourRect&) const@plt>
  1b17d0:	test   %r13,%r13
  1b17d3:	je     1b17e0 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x50>
  1b17d5:	mov    %r13,%rsi
  1b17d8:	mov    %r15,%rdi
  1b17db:	call   c24a8 <CEGUI::ColourRect::operator*=(CEGUI::ColourRect const&)@plt>
  1b17e0:	mov    %r15,%rdi
  1b17e3:	call   c3c28 <CEGUI::ColourRect::isMonochromatic() const@plt>
  1b17e8:	test   %al,%al
  1b17ea:	je     1b1803 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x73>
  1b17ec:	cmpb   $0x0,0x24(%rsp)
  1b17f1:	je     1b18e0 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x150>
  1b17f7:	mov    0x20(%rsp),%eax
  1b17fb:	xor    %r14d,%r14d
  1b17fe:	cmp    $0xffffffff,%eax
  1b1801:	je     1b1806 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x76>
  1b1803:	mov    %r15,%r14
  1b1806:	mov    0x110(%rbx),%r13
  1b180d:	cmp    0x118(%rbx),%r13
  1b1814:	je     1b184a <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0xba>
  1b1816:	movzbl 0xf(%rsp),%r15d
  1b181c:	nopl   0x0(%rax)
  1b1820:	mov    %r13,%rdi
  1b1823:	mov    %r15d,%r8d
  1b1826:	mov    %r12,%rcx
  1b1829:	mov    %r14,%rdx
  1b182c:	movss  0x8(%rsp),%xmm0
  1b1832:	mov    %rbp,%rsi
  1b1835:	add    $0x3c0,%r13
  1b183c:	call   c3c08 <CEGUI::FalagardComponentBase::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const@plt>
  1b1841:	cmp    0x118(%rbx),%r13
  1b1848:	jne    1b1820 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x90>
  1b184a:	mov    0x128(%rbx),%r13
  1b1851:	cmp    0x130(%rbx),%r13
  1b1858:	je     1b188a <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0xfa>
  1b185a:	movzbl 0xf(%rsp),%r15d
  1b1860:	mov    %r13,%rdi
  1b1863:	mov    %r15d,%r8d
  1b1866:	mov    %r12,%rcx
  1b1869:	mov    %r14,%rdx
  1b186c:	movss  0x8(%rsp),%xmm0
  1b1872:	mov    %rbp,%rsi
  1b1875:	add    $0x430,%r13
  1b187c:	call   c3c08 <CEGUI::FalagardComponentBase::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const@plt>
  1b1881:	cmp    0x130(%rbx),%r13
  1b1888:	jne    1b1860 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0xd0>
  1b188a:	mov    0x140(%rbx),%r13
  1b1891:	cmp    0x148(%rbx),%r13
  1b1898:	je     1b18ca <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x13a>
  1b189a:	movzbl 0xf(%rsp),%r15d
  1b18a0:	mov    %r13,%rdi
  1b18a3:	mov    %r15d,%r8d
  1b18a6:	mov    %r12,%rcx
  1b18a9:	mov    %r14,%rdx
  1b18ac:	movss  0x8(%rsp),%xmm0
  1b18b2:	mov    %rbp,%rsi
  1b18b5:	add    $0x638,%r13
  1b18bc:	call   c3c08 <CEGUI::FalagardComponentBase::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const@plt>
  1b18c1:	cmp    0x148(%rbx),%r13
  1b18c8:	jne    1b18a0 <CEGUI::ImagerySection::render(CEGUI::Window&, float, CEGUI::ColourRect const*, CEGUI::Rect const*, bool) const+0x110>
  1b18ca:	add    $0x78,%rsp
  1b18ce:	pop    %rbx
  1b18cf:	pop    %rbp
  1b18d0:	pop    %r12
  1b18d2:	pop    %r13
  1b18d4:	pop    %r14
  1b18d6:	pop    %r15
  1b18d8:	ret
  1b18d9:	nopl   0x0(%rax)
