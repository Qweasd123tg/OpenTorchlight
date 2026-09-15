
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000950a40 <CLevel::updateMaterialAmbient()>:
  950a40:	41 57                	push   %r15
  950a42:	41 56                	push   %r14
  950a44:	41 55                	push   %r13
  950a46:	49 89 fd             	mov    %rdi,%r13
  950a49:	41 54                	push   %r12
  950a4b:	55                   	push   %rbp
  950a4c:	53                   	push   %rbx
  950a4d:	48 81 ec 88 00 00 00 	sub    $0x88,%rsp
  950a54:	48 8b 87 d8 01 00 00 	mov    0x1d8(%rdi),%rax
  950a5b:	8b 98 38 07 00 00    	mov    0x738(%rax),%ebx
  950a61:	8b 88 34 07 00 00    	mov    0x734(%rax),%ecx
  950a67:	8b 90 30 07 00 00    	mov    0x730(%rax),%edx
  950a6d:	8b 80 3c 07 00 00    	mov    0x73c(%rax),%eax
  950a73:	89 5c 24 58          	mov    %ebx,0x58(%rsp)
  950a77:	89 4c 24 54          	mov    %ecx,0x54(%rsp)
  950a7b:	89 44 24 5c          	mov    %eax,0x5c(%rsp)
  950a7f:	89 54 24 50          	mov    %edx,0x50(%rsp)
  950a83:	8b 47 18             	mov    0x18(%rdi),%eax
  950a86:	85 c0                	test   %eax,%eax
  950a88:	89 44 24 04          	mov    %eax,0x4(%rsp)
  950a8c:	0f 8e 99 01 00 00    	jle    950c2b <CLevel::updateMaterialAmbient()+0x1eb>
  950a92:	4c 8d 7c 24 70       	lea    0x70(%rsp),%r15
  950a97:	48 8d 6c 24 50       	lea    0x50(%rsp),%rbp
  950a9c:	45 31 f6             	xor    %r14d,%r14d
  950a9f:	45 31 e4             	xor    %r12d,%r12d
  950aa2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  950aa8:	45 3b 65 1c          	cmp    0x1c(%r13),%r12d
  950aac:	0f 82 8e 01 00 00    	jb     950c40 <CLevel::updateMaterialAmbient()+0x200>
  950ab2:	49 8b 45 10          	mov    0x10(%r13),%rax
  950ab6:	48 8d 54 24 7f       	lea    0x7f(%rsp),%rdx
  950abb:	be 48 56 fd 00       	mov    $0xfd5648,%esi
  950ac0:	4c 89 ff             	mov    %r15,%rdi
  950ac3:	48 8b 18             	mov    (%rax),%rbx
  950ac6:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  950acd:	00 00 
  950acf:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%rsp)
  950ad6:	00 
  950ad7:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%rsp)
  950ade:	00 
  950adf:	c7 44 24 40 0a 00 00 	movl   $0xa,0x40(%rsp)
  950ae6:	00 
  950ae7:	e8 6c 53 c0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  950aec:	48 8d 54 24 30       	lea    0x30(%rsp),%rdx
  950af1:	4c 89 fe             	mov    %r15,%rsi
  950af4:	48 89 df             	mov    %rbx,%rdi
  950af7:	e8 f4 b0 df ff       	call   74bbf0 <CEditorScene::GetObjectsCreatedByADescriptor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, TArrayList<CEditorBaseObject*>*)>
  950afc:	48 8b 7c 24 70       	mov    0x70(%rsp),%rdi
  950b01:	48 83 ef 18          	sub    $0x18,%rdi
  950b05:	48 81 ff 40 45 42 01 	cmp    $0x1424540,%rdi
  950b0c:	0f 85 3a 01 00 00    	jne    950c4c <CLevel::updateMaterialAmbient()+0x20c>
  950b12:	8b 54 24 38          	mov    0x38(%rsp),%edx
  950b16:	85 d2                	test   %edx,%edx
  950b18:	0f 85 e2 00 00 00    	jne    950c00 <CLevel::updateMaterialAmbient()+0x1c0>
  950b1e:	48 8d 54 24 7e       	lea    0x7e(%rsp),%rdx
  950b23:	48 8d 7c 24 60       	lea    0x60(%rsp),%rdi
  950b28:	be 88 d9 fa 00       	mov    $0xfad988,%esi
  950b2d:	48 c7 44 24 10 00 00 	movq   $0x0,0x10(%rsp)
  950b34:	00 00 
  950b36:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%rsp)
  950b3d:	00 
  950b3e:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%rsp)
  950b45:	00 
  950b46:	c7 44 24 20 0a 00 00 	movl   $0xa,0x20(%rsp)
  950b4d:	00 
  950b4e:	e8 05 53 c0 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  950b53:	48 8d 44 24 10       	lea    0x10(%rsp),%rax
  950b58:	48 8d 74 24 60       	lea    0x60(%rsp),%rsi
  950b5d:	48 89 df             	mov    %rbx,%rdi
  950b60:	48 89 c2             	mov    %rax,%rdx
  950b63:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  950b68:	e8 83 b0 df ff       	call   74bbf0 <CEditorScene::GetObjectsCreatedByADescriptor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, TArrayList<CEditorBaseObject*>*)>
  950b6d:	48 8b 7c 24 60       	mov    0x60(%rsp),%rdi
  950b72:	b8 40 45 42 01       	mov    $0x1424540,%eax
  950b77:	48 83 ef 18          	sub    $0x18,%rdi
  950b7b:	48 39 f8             	cmp    %rdi,%rax
  950b7e:	0f 85 2d 01 00 00    	jne    950cb1 <CLevel::updateMaterialAmbient()+0x271>
  950b84:	8b 44 24 18          	mov    0x18(%rsp),%eax
  950b88:	85 c0                	test   %eax,%eax
  950b8a:	74 5c                	je     950be8 <CLevel::updateMaterialAmbient()+0x1a8>
  950b8c:	31 db                	xor    %ebx,%ebx
  950b8e:	eb 40                	jmp    950bd0 <CLevel::updateMaterialAmbient()+0x190>
  950b90:	48 8b 44 24 10       	mov    0x10(%rsp),%rax
  950b95:	48 8b 38             	mov    (%rax),%rdi
  950b98:	48 85 ff             	test   %rdi,%rdi
  950b9b:	74 2a                	je     950bc7 <CLevel::updateMaterialAmbient()+0x187>
  950b9d:	31 c9                	xor    %ecx,%ecx
  950b9f:	ba 00 a7 fd 00       	mov    $0xfda700,%edx
  950ba4:	be 10 46 fc 00       	mov    $0xfc4610,%esi
  950ba9:	e8 aa 4b c0 ff       	call   555758 <__dynamic_cast@plt>
  950bae:	48 85 c0             	test   %rax,%rax
  950bb1:	74 14                	je     950bc7 <CLevel::updateMaterialAmbient()+0x187>
  950bb3:	48 8b b8 20 01 00 00 	mov    0x120(%rax),%rdi
  950bba:	48 85 ff             	test   %rdi,%rdi
  950bbd:	74 08                	je     950bc7 <CLevel::updateMaterialAmbient()+0x187>
  950bbf:	48 89 ee             	mov    %rbp,%rsi
  950bc2:	e8 29 a3 f4 ff       	call   89aef0 <CGenericModel::setAmbient(Ogre::ColourValue&)>
  950bc7:	83 c3 01             	add    $0x1,%ebx
  950bca:	3b 5c 24 18          	cmp    0x18(%rsp),%ebx
  950bce:	73 18                	jae    950be8 <CLevel::updateMaterialAmbient()+0x1a8>
  950bd0:	39 5c 24 1c          	cmp    %ebx,0x1c(%rsp)
  950bd4:	76 ba                	jbe    950b90 <CLevel::updateMaterialAmbient()+0x150>
  950bd6:	89 d8                	mov    %ebx,%eax
  950bd8:	48 c1 e0 03          	shl    $0x3,%rax
  950bdc:	48 03 44 24 10       	add    0x10(%rsp),%rax
  950be1:	eb b2                	jmp    950b95 <CLevel::updateMaterialAmbient()+0x155>
  950be3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  950be8:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  950bed:	48 85 ff             	test   %rdi,%rdi
  950bf0:	74 0e                	je     950c00 <CLevel::updateMaterialAmbient()+0x1c0>
  950bf2:	e8 41 2a c0 ff       	call   553638 <operator delete[](void*)@plt>
  950bf7:	48 c7 44 24 10 00 00 	movq   $0x0,0x10(%rsp)
  950bfe:	00 00 
  950c00:	48 8b 7c 24 30       	mov    0x30(%rsp),%rdi
  950c05:	48 85 ff             	test   %rdi,%rdi
  950c08:	74 0e                	je     950c18 <CLevel::updateMaterialAmbient()+0x1d8>
  950c0a:	e8 29 2a c0 ff       	call   553638 <operator delete[](void*)@plt>
  950c0f:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  950c16:	00 00 
  950c18:	41 83 c4 01          	add    $0x1,%r12d
  950c1c:	49 83 c6 08          	add    $0x8,%r14
  950c20:	44 39 64 24 04       	cmp    %r12d,0x4(%rsp)
  950c25:	0f 8f 7d fe ff ff    	jg     950aa8 <CLevel::updateMaterialAmbient()+0x68>
  950c2b:	48 81 c4 88 00 00 00 	add    $0x88,%rsp
  950c32:	5b                   	pop    %rbx
  950c33:	5d                   	pop    %rbp
  950c34:	41 5c                	pop    %r12
  950c36:	41 5d                	pop    %r13
  950c38:	41 5e                	pop    %r14
  950c3a:	41 5f                	pop    %r15
  950c3c:	c3                   	ret
  950c3d:	0f 1f 00             	nopl   (%rax)
  950c40:	4c 89 f0             	mov    %r14,%rax
  950c43:	49 03 45 10          	add    0x10(%r13),%rax
  950c47:	e9 6a fe ff ff       	jmp    950ab6 <CLevel::updateMaterialAmbient()+0x76>
  950c4c:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  950c51:	48 85 c0             	test   %rax,%rax
  950c54:	74 1f                	je     950c75 <CLevel::updateMaterialAmbient()+0x235>
  950c56:	83 c8 ff             	or     $0xffffffff,%eax
  950c59:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  950c5e:	85 c0                	test   %eax,%eax
  950c60:	0f 8f ac fe ff ff    	jg     950b12 <CLevel::updateMaterialAmbient()+0xd2>
  950c66:	48 8d 74 24 7d       	lea    0x7d(%rsp),%rsi
  950c6b:	e8 d8 28 c0 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  950c70:	e9 9d fe ff ff       	jmp    950b12 <CLevel::updateMaterialAmbient()+0xd2>
  950c75:	8b 47 10             	mov    0x10(%rdi),%eax
  950c78:	8d 50 ff             	lea    -0x1(%rax),%edx
  950c7b:	89 57 10             	mov    %edx,0x10(%rdi)
  950c7e:	eb de                	jmp    950c5e <CLevel::updateMaterialAmbient()+0x21e>
  950c80:	4c 89 ff             	mov    %r15,%rdi
  950c83:	48 89 c3             	mov    %rax,%rbx
  950c86:	e8 4d 3c c0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  950c8b:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  950c90:	e8 fb fe de ff       	call   740b90 <TArrayList<CEditorBaseObject*>::~TArrayList()>
  950c95:	48 89 df             	mov    %rbx,%rdi
  950c98:	e8 fb 37 c0 ff       	call   554498 <_Unwind_Resume@plt>
  950c9d:	48 89 c3             	mov    %rax,%rbx
  950ca0:	eb e9                	jmp    950c8b <CLevel::updateMaterialAmbient()+0x24b>
  950ca2:	48 89 c3             	mov    %rax,%rbx
  950ca5:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  950caa:	e8 e1 fe de ff       	call   740b90 <TArrayList<CEditorBaseObject*>::~TArrayList()>
  950caf:	eb da                	jmp    950c8b <CLevel::updateMaterialAmbient()+0x24b>
  950cb1:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  950cb6:	48 85 c0             	test   %rax,%rax
  950cb9:	74 2e                	je     950ce9 <CLevel::updateMaterialAmbient()+0x2a9>
  950cbb:	83 c8 ff             	or     $0xffffffff,%eax
  950cbe:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  950cc3:	85 c0                	test   %eax,%eax
  950cc5:	0f 8f b9 fe ff ff    	jg     950b84 <CLevel::updateMaterialAmbient()+0x144>
  950ccb:	48 8d 74 24 7c       	lea    0x7c(%rsp),%rsi
  950cd0:	e8 73 28 c0 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  950cd5:	e9 aa fe ff ff       	jmp    950b84 <CLevel::updateMaterialAmbient()+0x144>
  950cda:	48 8d 7c 24 60       	lea    0x60(%rsp),%rdi
  950cdf:	48 89 c3             	mov    %rax,%rbx
  950ce2:	e8 f1 3b c0 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  950ce7:	eb bc                	jmp    950ca5 <CLevel::updateMaterialAmbient()+0x265>
  950ce9:	8b 47 10             	mov    0x10(%rdi),%eax
  950cec:	8d 50 ff             	lea    -0x1(%rax),%edx
  950cef:	89 57 10             	mov    %edx,0x10(%rdi)
  950cf2:	eb cf                	jmp    950cc3 <CLevel::updateMaterialAmbient()+0x283>
  950cf4:	48 89 c3             	mov    %rax,%rbx
  950cf7:	48 8d 44 24 10       	lea    0x10(%rsp),%rax
  950cfc:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  950d01:	eb a2                	jmp    950ca5 <CLevel::updateMaterialAmbient()+0x265>
