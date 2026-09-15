
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

00000000009b1050 <CWarper::CWarper(CResourceManager*)>:
  9b1050:	48 89 5c 24 e8       	mov    %rbx,-0x18(%rsp)
  9b1055:	48 89 fb             	mov    %rdi,%rbx
  9b1058:	4c 89 64 24 f8       	mov    %r12,-0x8(%rsp)
  9b105d:	4c 8d a3 10 01 00 00 	lea    0x110(%rbx),%r12
  9b1064:	48 89 6c 24 f0       	mov    %rbp,-0x10(%rsp)
  9b1069:	31 d2                	xor    %edx,%edx
  9b106b:	48 83 ec 18          	sub    $0x18,%rsp
  9b106f:	48 89 f5             	mov    %rsi,%rbp
  9b1072:	e8 d9 69 03 00       	call   9e7a50 <CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*)>
  9b1077:	48 c7 03 30 8c fd 00 	movq   $0xfd8c30,(%rbx)
  9b107e:	c7 83 00 01 00 00 01 	movl   $0x1,0x100(%rbx)
  9b1085:	00 00 00 
  9b1088:	be 48 eb 49 01       	mov    $0x149eb48,%esi
  9b108d:	c7 83 04 01 00 00 00 	movl   $0x0,0x104(%rbx)
  9b1094:	00 00 00 
  9b1097:	c6 83 08 01 00 00 01 	movb   $0x1,0x108(%rbx)
  9b109e:	4c 89 e7             	mov    %r12,%rdi
  9b10a1:	c6 83 09 01 00 00 00 	movb   $0x0,0x109(%rbx)
  9b10a8:	e8 db 21 ba ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9b10ad:	48 8d bb 18 01 00 00 	lea    0x118(%rbx),%rdi
  9b10b4:	be 48 eb 49 01       	mov    $0x149eb48,%esi
  9b10b9:	e8 ca 21 ba ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  9b10be:	48 89 ab 20 01 00 00 	mov    %rbp,0x120(%rbx)
  9b10c5:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  9b10ca:	48 8b 1c 24          	mov    (%rsp),%rbx
  9b10ce:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  9b10d3:	48 83 c4 18          	add    $0x18,%rsp
  9b10d7:	c3                   	ret
  9b10d8:	48 89 c5             	mov    %rax,%rbp
  9b10db:	48 89 df             	mov    %rbx,%rdi
  9b10de:	e8 7d 60 03 00       	call   9e7160 <CPositionableObject::~CPositionableObject()>
  9b10e3:	48 89 ef             	mov    %rbp,%rdi
  9b10e6:	e8 ad 33 ba ff       	call   554498 <_Unwind_Resume@plt>
  9b10eb:	4c 89 e7             	mov    %r12,%rdi
  9b10ee:	48 89 c5             	mov    %rax,%rbp
  9b10f1:	e8 e2 37 ba ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  9b10f6:	eb e3                	jmp    9b10db <CWarper::CWarper(CResourceManager*)+0x8b>
