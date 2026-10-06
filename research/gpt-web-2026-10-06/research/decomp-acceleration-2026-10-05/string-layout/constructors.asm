
research/decomp-acceleration-2026-10-05/string-layout/constructors.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <ctor_default>:
   0:	48 85 ff             	test   %rdi,%rdi
   3:	74 39                	je     3e <ctor_default+0x3e>
   5:	48 c7 47 08 20 00 00 	movq   $0x20,0x8(%rdi)
   c:	00 
   d:	48 c7 47 10 00 00 00 	movq   $0x0,0x10(%rdi)
  14:	00 
  15:	48 c7 47 20 00 00 00 	movq   $0x0,0x20(%rdi)
  1c:	00 
  1d:	48 c7 47 18 00 00 00 	movq   $0x0,0x18(%rdi)
  24:	00 
  25:	48 c7 87 a8 00 00 00 	movq   $0x0,0xa8(%rdi)
  2c:	00 00 00 00 
  30:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
  37:	c7 47 28 00 00 00 00 	movl   $0x0,0x28(%rdi)
  3e:	f3 c3                	repz ret

0000000000000040 <sdk_string_size>:
  40:	b8 b0 00 00 00       	mov    $0xb0,%eax
  45:	c3                   	ret
  46:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  4d:	00 00 00 

0000000000000050 <width_probe>:
  50:	48 89 f8             	mov    %rdi,%rax
  53:	48 c1 f8 28          	sar    $0x28,%rax
  57:	c3                   	ret
  58:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  5f:	00 

0000000000000060 <ctor_empty_span>:
  60:	48 89 6c 24 f8       	mov    %rbp,-0x8(%rsp)
  65:	48 89 5c 24 f0       	mov    %rbx,-0x10(%rsp)
  6a:	48 83 ec 18          	sub    $0x18,%rsp
  6e:	48 85 ff             	test   %rdi,%rdi
  71:	48 89 fd             	mov    %rdi,%rbp
  74:	74 59                	je     cf <ctor_empty_span+0x6f>
  76:	48 c7 47 08 20 00 00 	movq   $0x20,0x8(%rdi)
  7d:	00 
  7e:	48 c7 47 10 00 00 00 	movq   $0x0,0x10(%rdi)
  85:	00 
  86:	31 f6                	xor    %esi,%esi
  88:	48 c7 47 20 00 00 00 	movq   $0x0,0x20(%rdi)
  8f:	00 
  90:	48 c7 47 18 00 00 00 	movq   $0x0,0x18(%rdi)
  97:	00 
  98:	48 8d 5f 28          	lea    0x28(%rdi),%rbx
  9c:	48 c7 87 a8 00 00 00 	movq   $0x0,0xa8(%rdi)
  a3:	00 00 00 00 
  a7:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
  ae:	c7 47 28 00 00 00 00 	movl   $0x0,0x28(%rdi)
  b5:	e8 00 00 00 00       	call   ba <ctor_empty_span+0x5a>
			b6: R_X86_64_PC32	CEGUI::String::grow(unsigned long)-0x4
  ba:	48 83 7d 08 20       	cmpq   $0x20,0x8(%rbp)
  bf:	48 c7 45 00 00 00 00 	movq   $0x0,0x0(%rbp)
  c6:	00 
  c7:	77 17                	ja     e0 <ctor_empty_span+0x80>
  c9:	c7 03 00 00 00 00    	movl   $0x0,(%rbx)
  cf:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  d4:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  d9:	48 83 c4 18          	add    $0x18,%rsp
  dd:	c3                   	ret
  de:	66 90                	xchg   %ax,%ax
  e0:	48 8b 9d a8 00 00 00 	mov    0xa8(%rbp),%rbx
  e7:	eb e0                	jmp    c9 <ctor_empty_span+0x69>
  e9:	48 89 c7             	mov    %rax,%rdi
  ec:	e8 00 00 00 00       	call   f1 <ctor_empty_span+0x91>
			ed: R_X86_64_PC32	_Unwind_Resume-0x4
  f1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  f8:	0f 1f 84 00 00 00 00 
  ff:	00 

0000000000000100 <ctor_empty_chars>:
 100:	48 89 6c 24 f8       	mov    %rbp,-0x8(%rsp)
 105:	48 89 5c 24 f0       	mov    %rbx,-0x10(%rsp)
 10a:	48 83 ec 18          	sub    $0x18,%rsp
 10e:	48 85 ff             	test   %rdi,%rdi
 111:	48 89 fd             	mov    %rdi,%rbp
 114:	74 59                	je     16f <ctor_empty_chars+0x6f>
 116:	48 c7 47 08 20 00 00 	movq   $0x20,0x8(%rdi)
 11d:	00 
 11e:	48 c7 47 10 00 00 00 	movq   $0x0,0x10(%rdi)
 125:	00 
 126:	31 f6                	xor    %esi,%esi
 128:	48 c7 47 20 00 00 00 	movq   $0x0,0x20(%rdi)
 12f:	00 
 130:	48 c7 47 18 00 00 00 	movq   $0x0,0x18(%rdi)
 137:	00 
 138:	48 8d 5f 28          	lea    0x28(%rdi),%rbx
 13c:	48 c7 87 a8 00 00 00 	movq   $0x0,0xa8(%rdi)
 143:	00 00 00 00 
 147:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
 14e:	c7 47 28 00 00 00 00 	movl   $0x0,0x28(%rdi)
 155:	e8 00 00 00 00       	call   15a <ctor_empty_chars+0x5a>
			156: R_X86_64_PC32	CEGUI::String::grow(unsigned long)-0x4
 15a:	48 83 7d 08 20       	cmpq   $0x20,0x8(%rbp)
 15f:	48 c7 45 00 00 00 00 	movq   $0x0,0x0(%rbp)
 166:	00 
 167:	77 17                	ja     180 <ctor_empty_chars+0x80>
 169:	c7 03 00 00 00 00    	movl   $0x0,(%rbx)
 16f:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
 174:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
 179:	48 83 c4 18          	add    $0x18,%rsp
 17d:	c3                   	ret
 17e:	66 90                	xchg   %ax,%ax
 180:	48 8b 9d a8 00 00 00 	mov    0xa8(%rbp),%rbx
 187:	eb e0                	jmp    169 <ctor_empty_chars+0x69>
 189:	48 89 c7             	mov    %rax,%rdi
 18c:	e8 00 00 00 00       	call   191 <ctor_empty_chars+0x91>
			18d: R_X86_64_PC32	_Unwind_Resume-0x4
 191:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
 198:	0f 1f 84 00 00 00 00 
 19f:	00 

00000000000001a0 <ctor_zero_count>:
 1a0:	48 89 5c 24 e8       	mov    %rbx,-0x18(%rsp)
 1a5:	48 89 6c 24 f0       	mov    %rbp,-0x10(%rsp)
 1aa:	48 89 fb             	mov    %rdi,%rbx
 1ad:	4c 89 64 24 f8       	mov    %r12,-0x8(%rsp)
 1b2:	48 83 ec 28          	sub    $0x28,%rsp
 1b6:	48 85 ff             	test   %rdi,%rdi
 1b9:	0f 84 b0 00 00 00    	je     26f <ctor_zero_count+0xcf>
 1bf:	48 83 3d 00 00 00 00 	cmpq   $0x0,0x0(%rip)        # 1c7 <ctor_zero_count+0x27>
 1c6:	00 
			1c2: R_X86_64_PC32	CEGUI::String::npos-0x5
 1c7:	48 c7 47 08 20 00 00 	movq   $0x20,0x8(%rdi)
 1ce:	00 
 1cf:	48 c7 47 10 00 00 00 	movq   $0x0,0x10(%rdi)
 1d6:	00 
 1d7:	48 c7 47 20 00 00 00 	movq   $0x0,0x20(%rdi)
 1de:	00 
 1df:	48 c7 47 18 00 00 00 	movq   $0x0,0x18(%rdi)
 1e6:	00 
 1e7:	48 c7 87 a8 00 00 00 	movq   $0x0,0xa8(%rdi)
 1ee:	00 00 00 00 
 1f2:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
 1f9:	c7 47 28 00 00 00 00 	movl   $0x0,0x28(%rdi)
 200:	75 4e                	jne    250 <ctor_zero_count+0xb0>
 202:	48 8d 54 24 0f       	lea    0xf(%rsp),%rdx
 207:	be 00 00 00 00       	mov    $0x0,%esi
			208: R_X86_64_32	.rodata.str1.8
 20c:	48 89 e7             	mov    %rsp,%rdi
 20f:	e8 00 00 00 00       	call   214 <ctor_zero_count+0x74>
			210: R_X86_64_PC32	std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)-0x4
 214:	bf 10 00 00 00       	mov    $0x10,%edi
 219:	e8 00 00 00 00       	call   21e <ctor_zero_count+0x7e>
			21a: R_X86_64_PC32	__cxa_allocate_exception-0x4
 21e:	48 89 e6             	mov    %rsp,%rsi
 221:	48 89 c7             	mov    %rax,%rdi
 224:	48 89 c5             	mov    %rax,%rbp
 227:	e8 00 00 00 00       	call   22c <ctor_zero_count+0x8c>
			228: R_X86_64_PC32	std::length_error::length_error(std::string const&)-0x4
 22c:	48 8b 3c 24          	mov    (%rsp),%rdi
 230:	48 83 ef 18          	sub    $0x18,%rdi
 234:	48 81 ff 00 00 00 00 	cmp    $0x0,%rdi
			237: R_X86_64_32S	std::string::_Rep::_S_empty_rep_storage
 23b:	75 54                	jne    291 <ctor_zero_count+0xf1>
 23d:	ba 00 00 00 00       	mov    $0x0,%edx
			23e: R_X86_64_32	std::length_error::~length_error()
 242:	be 00 00 00 00       	mov    $0x0,%esi
			243: R_X86_64_32	typeinfo for std::length_error
 247:	48 89 ef             	mov    %rbp,%rdi
 24a:	e8 00 00 00 00       	call   24f <ctor_zero_count+0xaf>
			24b: R_X86_64_PC32	__cxa_throw-0x4
 24f:	90                   	nop
 250:	31 f6                	xor    %esi,%esi
 252:	e8 00 00 00 00       	call   257 <ctor_zero_count+0xb7>
			253: R_X86_64_PC32	CEGUI::String::grow(unsigned long)-0x4
 257:	48 83 7b 08 20       	cmpq   $0x20,0x8(%rbx)
 25c:	48 c7 03 00 00 00 00 	movq   $0x0,(%rbx)
 263:	77 23                	ja     288 <ctor_zero_count+0xe8>
 265:	48 83 c3 28          	add    $0x28,%rbx
 269:	c7 03 00 00 00 00    	movl   $0x0,(%rbx)
 26f:	48 8b 5c 24 10       	mov    0x10(%rsp),%rbx
 274:	48 8b 6c 24 18       	mov    0x18(%rsp),%rbp
 279:	4c 8b 64 24 20       	mov    0x20(%rsp),%r12
 27e:	48 83 c4 28          	add    $0x28,%rsp
 282:	c3                   	ret
 283:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
 288:	48 8b 9b a8 00 00 00 	mov    0xa8(%rbx),%rbx
 28f:	eb d8                	jmp    269 <ctor_zero_count+0xc9>
 291:	b8 00 00 00 00       	mov    $0x0,%eax
			292: R_X86_64_32	pthread_cancel
 296:	48 85 c0             	test   %rax,%rax
 299:	74 23                	je     2be <ctor_zero_count+0x11e>
 29b:	83 c8 ff             	or     $0xffffffff,%eax
 29e:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
 2a3:	85 c0                	test   %eax,%eax
 2a5:	7f 96                	jg     23d <ctor_zero_count+0x9d>
 2a7:	48 8d 74 24 0e       	lea    0xe(%rsp),%rsi
 2ac:	e8 00 00 00 00       	call   2b1 <ctor_zero_count+0x111>
			2ad: R_X86_64_PC32	std::string::_Rep::_M_destroy(std::allocator<char> const&)-0x4
 2b1:	eb 8a                	jmp    23d <ctor_zero_count+0x9d>
 2b3:	49 89 c4             	mov    %rax,%r12
 2b6:	4c 89 e7             	mov    %r12,%rdi
 2b9:	e8 00 00 00 00       	call   2be <ctor_zero_count+0x11e>
			2ba: R_X86_64_PC32	_Unwind_Resume-0x4
 2be:	8b 47 10             	mov    0x10(%rdi),%eax
 2c1:	8d 50 ff             	lea    -0x1(%rax),%edx
 2c4:	89 57 10             	mov    %edx,0x10(%rdi)
 2c7:	eb da                	jmp    2a3 <ctor_zero_count+0x103>
 2c9:	eb e8                	jmp    2b3 <ctor_zero_count+0x113>
 2cb:	48 89 ef             	mov    %rbp,%rdi
 2ce:	49 89 c4             	mov    %rax,%r12
 2d1:	e8 00 00 00 00       	call   2d6 <ctor_zero_count+0x136>
			2d2: R_X86_64_PC32	__cxa_free_exception-0x4
 2d6:	48 89 e7             	mov    %rsp,%rdi
 2d9:	e8 00 00 00 00       	call   2de <ctor_zero_count+0x13e>
			2da: R_X86_64_PC32	std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()-0x4
 2de:	eb d6                	jmp    2b6 <ctor_zero_count+0x116>
 2e0:	48 83 fa ff          	cmp    $0xffffffffffffffff,%rdx
 2e4:	49 89 c4             	mov    %rax,%r12
 2e7:	75 cd                	jne    2b6 <ctor_zero_count+0x116>
 2e9:	e8 00 00 00 00       	call   2ee <ctor_zero_count+0x14e>
			2ea: R_X86_64_PC32	std::terminate()-0x4

Disassembly of section .text._ZNSt12length_errorD2Ev:

0000000000000000 <std::length_error::~length_error()>:
   0:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
			3: R_X86_64_32S	vtable for std::length_error+0x10
   7:	e9 00 00 00 00       	jmp    c <std::length_error::~length_error()+0xc>
			8: R_X86_64_PC32	std::logic_error::~logic_error()-0x4

Disassembly of section .text._ZNSt12length_errorD0Ev:

0000000000000000 <std::length_error::~length_error()>:
   0:	53                   	push   %rbx
   1:	48 89 fb             	mov    %rdi,%rbx
   4:	48 c7 07 00 00 00 00 	movq   $0x0,(%rdi)
			7: R_X86_64_32S	vtable for std::length_error+0x10
   b:	e8 00 00 00 00       	call   10 <std::length_error::~length_error()+0x10>
			c: R_X86_64_PC32	std::logic_error::~logic_error()-0x4
  10:	48 89 df             	mov    %rbx,%rdi
  13:	5b                   	pop    %rbx
  14:	e9 00 00 00 00       	jmp    19 <std::length_error::~length_error()+0x19>
			15: R_X86_64_PC32	operator delete(void*)-0x4
