
bundled/libCEGUIBase.so.1:     file format elf64-x86-64


Disassembly of section .text:

00000000000e59e0 <CEGUI::Image::setHorzScaling(float)>:
   e59e0:	movss  0x14(%rdi),%xmm1
   e59e5:	subss  0x10(%rdi),%xmm1
   e59ea:	xorps  %xmm2,%xmm2
   e59ed:	mulss  %xmm0,%xmm1
   e59f1:	ucomiss %xmm2,%xmm1
   e59f4:	ja     e5a38 <CEGUI::Image::setHorzScaling(float)+0x58>
   e59f6:	movss  0xf126a(%rip),%xmm3        # 1d6c68 <typeinfo name for std::out_of_range+0x18>
   e59fe:	addss  %xmm3,%xmm1
   e5a02:	mulss  0x18(%rdi),%xmm0
   e5a07:	cvttss2si %xmm1,%eax
   e5a0b:	ucomiss %xmm2,%xmm0
   e5a0e:	cvtsi2ss %eax,%xmm1
   e5a12:	movss  %xmm1,0x20(%rdi)
   e5a17:	ja     e5a48 <CEGUI::Image::setHorzScaling(float)+0x68>
   e5a19:	movss  0xf1247(%rip),%xmm1        # 1d6c68 <typeinfo name for std::out_of_range+0x18>
   e5a21:	addss  %xmm1,%xmm0
   e5a25:	cvttss2si %xmm0,%eax
   e5a29:	cvtsi2ss %eax,%xmm0
   e5a2d:	movss  %xmm0,0x28(%rdi)
   e5a32:	ret
   e5a33:	nopl   0x0(%rax,%rax,1)
   e5a38:	movss  0xf122c(%rip),%xmm3        # 1d6c6c <typeinfo name for std::out_of_range+0x1c>
   e5a40:	jmp    e59fe <CEGUI::Image::setHorzScaling(float)+0x1e>
   e5a42:	nopw   0x0(%rax,%rax,1)
   e5a48:	movss  0xf121c(%rip),%xmm1        # 1d6c6c <typeinfo name for std::out_of_range+0x1c>
   e5a50:	jmp    e5a21 <CEGUI::Image::setHorzScaling(float)+0x41>
   e5a52:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)

00000000000e5a60 <CEGUI::Image::setVertScaling(float)>:
   e5a60:	movss  0xc(%rdi),%xmm1
   e5a65:	subss  0x8(%rdi),%xmm1
   e5a6a:	xorps  %xmm2,%xmm2
   e5a6d:	mulss  %xmm0,%xmm1
   e5a71:	ucomiss %xmm2,%xmm1
   e5a74:	ja     e5ab8 <CEGUI::Image::setVertScaling(float)+0x58>
   e5a76:	movss  0xf11ea(%rip),%xmm3        # 1d6c68 <typeinfo name for std::out_of_range+0x18>
   e5a7e:	addss  %xmm3,%xmm1
   e5a82:	mulss  0x1c(%rdi),%xmm0
   e5a87:	cvttss2si %xmm1,%eax
   e5a8b:	ucomiss %xmm2,%xmm0
   e5a8e:	cvtsi2ss %eax,%xmm1
   e5a92:	movss  %xmm1,0x24(%rdi)
   e5a97:	ja     e5ac8 <CEGUI::Image::setVertScaling(float)+0x68>
   e5a99:	movss  0xf11c7(%rip),%xmm1        # 1d6c68 <typeinfo name for std::out_of_range+0x18>
   e5aa1:	addss  %xmm1,%xmm0
   e5aa5:	cvttss2si %xmm0,%eax
   e5aa9:	cvtsi2ss %eax,%xmm0
   e5aad:	movss  %xmm0,0x2c(%rdi)
   e5ab2:	ret
   e5ab3:	nopl   0x0(%rax,%rax,1)
   e5ab8:	movss  0xf11ac(%rip),%xmm3        # 1d6c6c <typeinfo name for std::out_of_range+0x1c>
   e5ac0:	jmp    e5a7e <CEGUI::Image::setVertScaling(float)+0x1e>
   e5ac2:	nopw   0x0(%rax,%rax,1)
   e5ac8:	movss  0xf119c(%rip),%xmm1        # 1d6c6c <typeinfo name for std::out_of_range+0x1c>
   e5ad0:	jmp    e5aa1 <CEGUI::Image::setVertScaling(float)+0x41>
   e5ad2:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
