
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000000f48a0 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)>:
   f48a0:	push   %r15
   f48a2:	push   %r14
   f48a4:	mov    %rsi,%r14
   f48a7:	push   %r13
   f48a9:	push   %r12
   f48ab:	mov    %rdi,%r12
   f48ae:	push   %rbp
   f48af:	push   %rbx
   f48b0:	sub    $0xa8,%rsp
   f48b7:	mov    %rdx,0x30(%rsp)
   f48bc:	movss  %xmm0,0x24(%rsp)
   f48c2:	call   c0b08 <CEGUI::System::getSingleton()@plt>
   f48c7:	mov    0x40(%rax),%rdi
   f48cb:	mov    (%rdi),%rax
   f48ce:	call   *0xa0(%rax)
   f48d4:	mov    (%r12),%rbx
   f48d8:	cmp    0x8(%r12),%rbx
   f48dd:	movq   %xmm0,0x18(%rsp)
   f48e3:	mov    0x18(%rsp),%rdx
   f48e8:	movq   %xmm1,0x18(%rsp)
   f48ee:	mov    0x18(%rsp),%rax
   f48f3:	mov    %rdx,0x40(%rsp)
   f48f8:	mov    %rax,0x48(%rsp)
   f48fd:	mov    %rdx,0x90(%rsp)
   f4905:	mov    %rax,0x98(%rsp)
   f490d:	je     f4a20 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x180>
   f4913:	lea    0x90(%rsp),%rax
   f491b:	lea    0x70(%rsp),%rbp
   f4920:	lea    0x80(%rsp),%r15
   f4928:	mov    %rax,0x28(%rsp)
   f492d:	lea    0x60(%rsp),%rax
   f4932:	mov    %rax,0x38(%rsp)
   f4937:	jmp    f499b <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0xfb>
   f4939:	nopl   0x0(%rax)
   f4940:	cmpb   $0x0,0x8d(%rbx)
   f4947:	mov    0x28(%rsp),%r13
   f494c:	cmove  0x30(%rsp),%r13
   f4952:	lea    0x8(%rbx),%rsi
   f4956:	mov    %rbp,%rdi
   f4959:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f495e:	mov    %r14,%rsi
   f4961:	mov    %rbp,%rdi
   f4964:	call   c3a48 <CEGUI::Rect::offset(CEGUI::Vector2 const&)@plt>
   f4969:	movss  0x24(%rsp),%xmm0
   f496f:	mov    (%rbx),%rdi
   f4972:	addss  0x18(%rbx),%xmm0
   f4977:	lea    0x1c(%rbx),%rcx
   f497b:	xor    %r8d,%r8d
   f497e:	mov    %r13,%rdx
   f4981:	mov    %rbp,%rsi
   f4984:	add    $0x90,%rbx
   f498b:	call   c1138 <CEGUI::Image::draw(CEGUI::Rect const&, float, CEGUI::Rect const&, CEGUI::ColourRect const&, CEGUI::QuadSplitMode) const@plt>
   f4990:	cmp    0x8(%r12),%rbx
   f4995:	je     f4a20 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x180>
   f499b:	cmpb   $0x0,0x8c(%rbx)
   f49a2:	je     f4940 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0xa0>
   f49a4:	lea    0x7c(%rbx),%rsi
   f49a8:	mov    %r15,%rdi
   f49ab:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f49b0:	mov    %r14,%rsi
   f49b3:	mov    %r15,%rdi
   f49b6:	call   c3a48 <CEGUI::Rect::offset(CEGUI::Vector2 const&)@plt>
   f49bb:	cmpb   $0x0,0x8d(%rbx)
   f49c2:	je     f4a10 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x170>
   f49c4:	mov    0x28(%rsp),%rdi
   f49c9:	mov    %r15,%rsi
   f49cc:	call   c2cc8 <CEGUI::Rect::getIntersection(CEGUI::Rect const&) const@plt>
   f49d1:	mov    0x38(%rsp),%rsi
   f49d6:	movq   %xmm0,0x18(%rsp)
   f49dc:	mov    0x18(%rsp),%rdx
   f49e1:	movq   %xmm1,0x18(%rsp)
   f49e7:	mov    0x18(%rsp),%rax
   f49ec:	mov    %r15,%rdi
   f49ef:	mov    %r15,%r13
   f49f2:	mov    %rdx,0x40(%rsp)
   f49f7:	mov    %rax,0x48(%rsp)
   f49fc:	mov    %rdx,0x60(%rsp)
   f4a01:	mov    %rax,0x68(%rsp)
   f4a06:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f4a0b:	jmp    f4952 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0xb2>
   f4a10:	mov    %r15,%rsi
   f4a13:	mov    0x30(%rsp),%rdi
   f4a18:	jmp    f49cc <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x12c>
   f4a1a:	nopw   0x0(%rax,%rax,1)
   f4a20:	mov    0x18(%r12),%rbx
   f4a25:	cmp    0x20(%r12),%rbx
   f4a2a:	je     f4b70 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x2d0>
   f4a30:	lea    0x90(%rsp),%rax
   f4a38:	lea    0x70(%rsp),%rbp
   f4a3d:	lea    0x80(%rsp),%r15
   f4a45:	mov    %rax,0x28(%rsp)
   f4a4a:	lea    0x50(%rsp),%rax
   f4a4f:	mov    %rax,0x38(%rsp)
   f4a54:	jmp    f4ae1 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x241>
   f4a59:	nopl   0x0(%rax)
   f4a60:	cmpb   $0x0,0x141(%rbx)
   f4a67:	mov    0x28(%rsp),%r13
   f4a6c:	cmove  0x30(%rsp),%r13
   f4a72:	lea    0xbc(%rbx),%rsi
   f4a79:	mov    %rbp,%rdi
   f4a7c:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f4a81:	mov    %r14,%rsi
   f4a84:	mov    %rbp,%rdi
   f4a87:	call   c3a48 <CEGUI::Rect::offset(CEGUI::Vector2 const&)@plt>
   f4a8c:	movss  0x24(%rsp),%xmm0
   f4a92:	mov    0xb8(%rbx),%r8d
   f4a99:	addss  0xcc(%rbx),%xmm0
   f4aa1:	mov    0xb0(%rbx),%rdi
   f4aa8:	lea    0xd0(%rbx),%r9
   f4aaf:	movss  0xe3fd5(%rip),%xmm2        # 1d8a8c <CEGUI::Imageset::ImagesetSchemaName+0xf>
   f4ab7:	mov    %rbx,%rsi
   f4aba:	movaps %xmm2,%xmm1
   f4abd:	mov    %r13,%rcx
   f4ac0:	mov    %rbp,%rdx
   f4ac3:	movl   $0x1,(%rsp)
   f4aca:	add    $0x148,%rbx
   f4ad1:	call   c2f68 <CEGUI::Font::drawText(CEGUI::String const&, CEGUI::Rect const&, float, CEGUI::Rect const&, CEGUI::TextFormatting, CEGUI::ColourRect const&, float, float, bool)@plt>
   f4ad6:	cmp    0x20(%r12),%rbx
   f4adb:	je     f4b70 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x2d0>
   f4ae1:	cmpb   $0x0,0x140(%rbx)
   f4ae8:	je     f4a60 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x1c0>
   f4aee:	lea    0x130(%rbx),%rsi
   f4af5:	mov    %r15,%rdi
   f4af8:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f4afd:	mov    %r14,%rsi
   f4b00:	mov    %r15,%rdi
   f4b03:	call   c3a48 <CEGUI::Rect::offset(CEGUI::Vector2 const&)@plt>
   f4b08:	cmpb   $0x0,0x141(%rbx)
   f4b0f:	je     f4b60 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x2c0>
   f4b11:	mov    0x28(%rsp),%rdi
   f4b16:	mov    %r15,%rsi
   f4b19:	call   c2cc8 <CEGUI::Rect::getIntersection(CEGUI::Rect const&) const@plt>
   f4b1e:	mov    0x38(%rsp),%rsi
   f4b23:	movq   %xmm0,0x18(%rsp)
   f4b29:	mov    0x18(%rsp),%rdx
   f4b2e:	movq   %xmm1,0x18(%rsp)
   f4b34:	mov    0x18(%rsp),%rax
   f4b39:	mov    %r15,%rdi
   f4b3c:	mov    %r15,%r13
   f4b3f:	mov    %rdx,0x40(%rsp)
   f4b44:	mov    %rax,0x48(%rsp)
   f4b49:	mov    %rdx,0x50(%rsp)
   f4b4e:	mov    %rax,0x58(%rsp)
   f4b53:	call   c4448 <CEGUI::Rect::operator=(CEGUI::Rect const&)@plt>
   f4b58:	jmp    f4a72 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x1d2>
   f4b5d:	nopl   (%rax)
   f4b60:	mov    %r15,%rsi
   f4b63:	mov    0x30(%rsp),%rdi
   f4b68:	jmp    f4b19 <CEGUI::RenderCache::render(CEGUI::Vector2 const&, float, CEGUI::Rect const&)+0x279>
   f4b6a:	nopw   0x0(%rax,%rax,1)
   f4b70:	add    $0xa8,%rsp
   f4b77:	pop    %rbx
   f4b78:	pop    %rbp
   f4b79:	pop    %r12
   f4b7b:	pop    %r13
   f4b7d:	pop    %r14
   f4b7f:	pop    %r15
   f4b81:	ret
