
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000000e5b50 <CEGUI::Image::draw(CEGUI::Rect const&, float, CEGUI::Rect const&, CEGUI::ColourRect const&, CEGUI::QuadSplitMode) const>:
   e5b50:	mov    %rbx,-0x28(%rsp)
   e5b55:	mov    %rbp,-0x20(%rsp)
   e5b5a:	mov    %rdi,%rbx
   e5b5d:	mov    %r12,-0x18(%rsp)
   e5b62:	mov    %r13,-0x10(%rsp)
   e5b67:	mov    %rdx,%r12
   e5b6a:	mov    %r14,-0x8(%rsp)
   e5b6f:	sub    $0x48,%rsp
   e5b73:	mov    (%rsi),%rax
   e5b76:	lea    0x10(%rsp),%rbp
   e5b7b:	mov    %rcx,%r13
   e5b7e:	mov    %r8d,%r14d
   e5b81:	movss  %xmm0,(%rsp)
   e5b86:	mov    %rax,0x10(%rsp)
   e5b8b:	mov    0x8(%rsi),%rax
   e5b8f:	lea    0x28(%rdi),%rsi
   e5b93:	mov    %rbp,%rdi
   e5b96:	mov    %rax,0x18(%rsp)
   e5b9b:	call   c3a48 <CEGUI::Rect::offset(CEGUI::Vector2 const&)@plt>
   e5ba0:	mov    (%rbx),%rdi
   e5ba3:	lea    0x8(%rbx),%rsi
   e5ba7:	mov    %r14d,%r9d
   e5baa:	mov    %r13,%r8
   e5bad:	mov    %r12,%rcx
   e5bb0:	mov    %rbp,%rdx
   e5bb3:	movss  (%rsp),%xmm0
   e5bb8:	call   c1038 <CEGUI::Imageset::draw(CEGUI::Rect const&, CEGUI::Rect const&, float, CEGUI::Rect const&, CEGUI::ColourRect const&, CEGUI::QuadSplitMode) const@plt>
   e5bbd:	mov    0x20(%rsp),%rbx
   e5bc2:	mov    0x28(%rsp),%rbp
   e5bc7:	mov    0x30(%rsp),%r12
   e5bcc:	mov    0x38(%rsp),%r13
   e5bd1:	mov    0x40(%rsp),%r14
   e5bd6:	add    $0x48,%rsp
   e5bda:	ret
