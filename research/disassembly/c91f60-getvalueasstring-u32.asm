
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000c91f60 <_ZN7STRINGS16GetValueAsStringEj>:
  c91f60:	41 57                	push   %r15
  c91f62:	41 56                	push   %r14
  c91f64:	49 89 fe             	mov    %rdi,%r14
  c91f67:	41 55                	push   %r13
  c91f69:	41 54                	push   %r12
  c91f6b:	55                   	push   %rbp
  c91f6c:	53                   	push   %rbx
  c91f6d:	48 81 ec 88 01 00 00 	sub    $0x188,%rsp
  c91f74:	48 8d 5c 24 10       	lea    0x10(%rsp),%rbx
  c91f79:	89 74 24 0c          	mov    %esi,0xc(%rsp)
  c91f7d:	48 8d 7b 68          	lea    0x68(%rbx),%rdi
  c91f81:	e8 e2 38 8c ff       	call   555868 <_ZNSt8ios_baseC2Ev@plt>
  c91f86:	48 8b 2d 23 29 79 00 	mov    0x792923(%rip),%rbp        # 14248b0 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x10>
  c91f8d:	48 c7 44 24 78 10 46 	movq   $0x1424610,0x78(%rsp)
  c91f94:	42 01 
  c91f96:	48 89 df             	mov    %rbx,%rdi
  c91f99:	48 c7 84 24 50 01 00 	movq   $0x0,0x150(%rsp)
  c91fa0:	00 00 00 00 00 
  c91fa5:	c6 84 24 58 01 00 00 	movb   $0x0,0x158(%rsp)
  c91fac:	00 
  c91fad:	31 f6                	xor    %esi,%esi
  c91faf:	c6 84 24 59 01 00 00 	movb   $0x0,0x159(%rsp)
  c91fb6:	00 
  c91fb7:	48 c7 84 24 60 01 00 	movq   $0x0,0x160(%rsp)
  c91fbe:	00 00 00 00 00 
  c91fc3:	48 89 6c 24 10       	mov    %rbp,0x10(%rsp)
  c91fc8:	48 c7 84 24 68 01 00 	movq   $0x0,0x168(%rsp)
  c91fcf:	00 00 00 00 00 
  c91fd4:	48 c7 84 24 70 01 00 	movq   $0x0,0x170(%rsp)
  c91fdb:	00 00 00 00 00 
  c91fe0:	48 c7 84 24 78 01 00 	movq   $0x0,0x178(%rsp)
  c91fe7:	00 00 00 00 00 
  c91fec:	4c 8b 3d c5 28 79 00 	mov    0x7928c5(%rip),%r15        # 14248b8 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x18>
  c91ff3:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  c91ff7:	4c 89 7c 04 10       	mov    %r15,0x10(%rsp,%rax,1)
  c91ffc:	48 8b 44 24 10       	mov    0x10(%rsp),%rax
  c92001:	48 c7 44 24 18 00 00 	movq   $0x0,0x18(%rsp)
  c92008:	00 00 
  c9200a:	48 03 78 e8          	add    -0x18(%rax),%rdi
  c9200e:	e8 e5 15 8c ff       	call   5535f8 <_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@plt>
  c92013:	4c 8b 2d a6 28 79 00 	mov    0x7928a6(%rip),%r13        # 14248c0 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x20>
  c9201a:	48 8b 15 a7 28 79 00 	mov    0x7928a7(%rip),%rdx        # 14248c8 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x28>
  c92021:	48 8d 7b 10          	lea    0x10(%rbx),%rdi
  c92025:	31 f6                	xor    %esi,%esi
  c92027:	4c 89 6c 24 20       	mov    %r13,0x20(%rsp)
  c9202c:	49 8b 45 e8          	mov    -0x18(%r13),%rax
  c92030:	48 89 54 04 20       	mov    %rdx,0x20(%rsp,%rax,1)
  c92035:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
  c9203a:	48 03 78 e8          	add    -0x18(%rax),%rdi
  c9203e:	e8 b5 15 8c ff       	call   5535f8 <_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@plt>
  c92043:	4c 8b 25 5e 28 79 00 	mov    0x79285e(%rip),%r12        # 14248a8 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x8>
  c9204a:	48 8b 15 7f 28 79 00 	mov    0x79287f(%rip),%rdx        # 14248d0 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x30>
  c92051:	48 8d 7b 50          	lea    0x50(%rbx),%rdi
  c92055:	4c 89 64 24 10       	mov    %r12,0x10(%rsp)
  c9205a:	49 8b 44 24 e8       	mov    -0x18(%r12),%rax
  c9205f:	48 89 54 04 10       	mov    %rdx,0x10(%rsp,%rax,1)
  c92064:	48 c7 44 24 10 98 46 	movq   $0x1424698,0x10(%rsp)
  c9206b:	42 01 
  c9206d:	48 c7 44 24 78 e8 46 	movq   $0x14246e8,0x78(%rsp)
  c92074:	42 01 
  c92076:	48 c7 44 24 20 c0 46 	movq   $0x14246c0,0x20(%rsp)
  c9207d:	42 01 
  c9207f:	48 c7 44 24 28 70 44 	movq   $0x1424470,0x28(%rsp)
  c92086:	42 01 
  c92088:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  c9208f:	00 00 
  c92091:	48 c7 44 24 38 00 00 	movq   $0x0,0x38(%rsp)
  c92098:	00 00 
  c9209a:	48 c7 44 24 40 00 00 	movq   $0x0,0x40(%rsp)
  c920a1:	00 00 
  c920a3:	48 c7 44 24 48 00 00 	movq   $0x0,0x48(%rsp)
  c920aa:	00 00 
  c920ac:	48 c7 44 24 50 00 00 	movq   $0x0,0x50(%rsp)
  c920b3:	00 00 
  c920b5:	48 c7 44 24 58 00 00 	movq   $0x0,0x58(%rsp)
  c920bc:	00 00 
  c920be:	e8 65 2b 8c ff       	call   554c28 <_ZNSt6localeC1Ev@plt>
  c920c3:	48 8d 73 18          	lea    0x18(%rbx),%rsi
  c920c7:	48 8d 7b 68          	lea    0x68(%rbx),%rdi
  c920cb:	48 c7 44 24 28 30 39 	movq   $0x1423930,0x28(%rsp)
  c920d2:	42 01 
  c920d4:	c7 44 24 68 18 00 00 	movl   $0x18,0x68(%rsp)
  c920db:	00 
  c920dc:	48 c7 44 24 70 38 3a 	movq   $0x1423a38,0x70(%rsp)
  c920e3:	42 01 
  c920e5:	e8 0e 15 8c ff       	call   5535f8 <_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@plt>
  c920ea:	8b 74 24 0c          	mov    0xc(%rsp),%esi
  c920ee:	48 8d 7b 10          	lea    0x10(%rbx),%rdi
  c920f2:	e8 91 1b 8c ff       	call   553c88 <_ZNSo9_M_insertImEERSoT_@plt>
  c920f7:	48 8d 73 18          	lea    0x18(%rbx),%rsi
  c920fb:	4c 89 f7             	mov    %r14,%rdi
  c920fe:	e8 25 1d 8c ff       	call   553e28 <_ZNKSt15basic_stringbufIcSt11char_traitsIcESaIcEE3strEv@plt>
  c92103:	48 8d 7b 60          	lea    0x60(%rbx),%rdi
  c92107:	48 c7 44 24 10 98 46 	movq   $0x1424698,0x10(%rsp)
  c9210e:	42 01 
  c92110:	48 c7 44 24 78 e8 46 	movq   $0x14246e8,0x78(%rsp)
  c92117:	42 01 
  c92119:	48 c7 44 24 20 c0 46 	movq   $0x14246c0,0x20(%rsp)
  c92120:	42 01 
  c92122:	48 c7 44 24 28 30 39 	movq   $0x1423930,0x28(%rsp)
  c92129:	42 01 
  c9212b:	e8 58 41 8c ff       	call   556288 <_ZNSsD1Ev@plt>
  c92130:	48 8d 7b 50          	lea    0x50(%rbx),%rdi
  c92134:	48 c7 44 24 28 70 44 	movq   $0x1424470,0x28(%rsp)
  c9213b:	42 01 
  c9213d:	e8 86 37 8c ff       	call   5558c8 <_ZNSt6localeD1Ev@plt>
  c92142:	4c 89 64 24 10       	mov    %r12,0x10(%rsp)
  c92147:	48 8b 15 82 27 79 00 	mov    0x792782(%rip),%rdx        # 14248d0 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x30>
  c9214e:	48 8d 7b 68          	lea    0x68(%rbx),%rdi
  c92152:	49 8b 44 24 e8       	mov    -0x18(%r12),%rax
  c92157:	48 89 14 03          	mov    %rdx,(%rbx,%rax,1)
  c9215b:	4c 89 6c 24 20       	mov    %r13,0x20(%rsp)
  c92160:	48 8b 15 61 27 79 00 	mov    0x792761(%rip),%rdx        # 14248c8 <_ZTTSt18basic_stringstreamIcSt11char_traitsIcESaIcEE@@GLIBCXX_3.4+0x28>
  c92167:	49 8b 45 e8          	mov    -0x18(%r13),%rax
  c9216b:	48 89 54 03 10       	mov    %rdx,0x10(%rbx,%rax,1)
  c92170:	48 89 6c 24 10       	mov    %rbp,0x10(%rsp)
  c92175:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  c92179:	4c 89 3c 03          	mov    %r15,(%rbx,%rax,1)
  c9217d:	48 c7 44 24 18 00 00 	movq   $0x0,0x18(%rsp)
  c92184:	00 00 
  c92186:	48 c7 44 24 78 10 46 	movq   $0x1424610,0x78(%rsp)
  c9218d:	42 01 
  c9218f:	e8 a4 26 8c ff       	call   554838 <_ZNSt8ios_baseD2Ev@plt>
  c92194:	48 81 c4 88 01 00 00 	add    $0x188,%rsp
  c9219b:	4c 89 f0             	mov    %r14,%rax
  c9219e:	5b                   	pop    %rbx
  c9219f:	5d                   	pop    %rbp
  c921a0:	41 5c                	pop    %r12
  c921a2:	41 5d                	pop    %r13
  c921a4:	41 5e                	pop    %r14
  c921a6:	41 5f                	pop    %r15
  c921a8:	c3                   	ret
  c921a9:	49 89 c4             	mov    %rax,%r12
  c921ac:	48 8d 7b 68          	lea    0x68(%rbx),%rdi
  c921b0:	e8 43 38 8c ff       	call   5559f8 <_ZNSt9basic_iosIcSt11char_traitsIcEED2Ev@plt>
  c921b5:	4c 89 e7             	mov    %r12,%rdi
  c921b8:	e8 db 22 8c ff       	call   554498 <_Unwind_Resume@plt>
  c921bd:	48 8d 7b 18          	lea    0x18(%rbx),%rdi
  c921c1:	49 89 c4             	mov    %rax,%r12
  c921c4:	e8 af 1b 8c ff       	call   553d78 <_ZNSt15basic_streambufIcSt11char_traitsIcEED2Ev@plt>
  c921c9:	48 89 df             	mov    %rbx,%rdi
  c921cc:	e8 bf bc ff ff       	call   c8de90 <_ZNSdD2Ev.clone.0>
  c921d1:	eb d9                	jmp    c921ac <_ZN7STRINGS16GetValueAsStringEj+0x24c>
  c921d3:	49 89 c4             	mov    %rax,%r12
  c921d6:	48 89 df             	mov    %rbx,%rdi
  c921d9:	e8 7a 09 8c ff       	call   552b58 <_ZNSt18basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@plt>
  c921de:	4c 89 e7             	mov    %r12,%rdi
  c921e1:	e8 b2 22 8c ff       	call   554498 <_Unwind_Resume@plt>
  c921e6:	48 8d 7b 18          	lea    0x18(%rbx),%rdi
  c921ea:	49 89 c4             	mov    %rax,%r12
  c921ed:	e8 de 9c 8d ff       	call   56bed0 <_ZNSt15basic_stringbufIcSt11char_traitsIcESaIcEED1Ev>
  c921f2:	48 89 df             	mov    %rbx,%rdi
  c921f5:	e8 96 bc ff ff       	call   c8de90 <_ZNSdD2Ev.clone.0>
  c921fa:	eb b0                	jmp    c921ac <_ZN7STRINGS16GetValueAsStringEj+0x24c>
  c921fc:	48 89 6c 24 10       	mov    %rbp,0x10(%rsp)
  c92201:	49 89 c4             	mov    %rax,%r12
  c92204:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  c92208:	4c 89 3c 03          	mov    %r15,(%rbx,%rax,1)
  c9220c:	48 c7 44 24 18 00 00 	movq   $0x0,0x18(%rsp)
  c92213:	00 00 
  c92215:	eb 95                	jmp    c921ac <_ZN7STRINGS16GetValueAsStringEj+0x24c>
