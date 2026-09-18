
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000c8ea50 <_ZN7STRINGS10uniqueNameERKSs>:
  c8ea50:	48 89 5c 24 e0       	mov    %rbx,-0x20(%rsp)
  c8ea55:	48 89 6c 24 e8       	mov    %rbp,-0x18(%rsp)
  c8ea5a:	45 31 c0             	xor    %r8d,%r8d
  c8ea5d:	4c 89 6c 24 f8       	mov    %r13,-0x8(%rsp)
  c8ea62:	4c 89 64 24 f0       	mov    %r12,-0x10(%rsp)
  c8ea67:	49 89 f5             	mov    %rsi,%r13
  c8ea6a:	48 83 ec 48          	sub    $0x48,%rsp
  c8ea6e:	8b 35 a0 7e 85 00    	mov    0x857ea0(%rip),%esi        # 14e6914 <_ZZN7STRINGS10uniqueNameERKSsE16gUniqueNameValue>
  c8ea74:	48 89 fd             	mov    %rdi,%rbp
  c8ea77:	48 8d 5c 24 10       	lea    0x10(%rsp),%rbx
  c8ea7c:	48 89 e7             	mov    %rsp,%rdi
  c8ea7f:	b9 20 00 00 00       	mov    $0x20,%ecx
  c8ea84:	31 d2                	xor    %edx,%edx
  c8ea86:	83 c6 01             	add    $0x1,%esi
  c8ea89:	89 35 85 7e 85 00    	mov    %esi,0x857e85(%rip)        # 14e6914 <_ZZN7STRINGS10uniqueNameERKSsE16gUniqueNameValue>
  c8ea8f:	e8 e4 5f 8c ff       	call   554a78 <_ZN4Ogre15StringConverter8toStringEjtcSt13_Ios_Fmtflags@plt>
  c8ea94:	4c 89 ee             	mov    %r13,%rsi
  c8ea97:	48 89 df             	mov    %rbx,%rdi
  c8ea9a:	e8 09 3f 8c ff       	call   5529a8 <_ZNSsC1ERKSs@plt>
  c8ea9f:	ba 01 00 00 00       	mov    $0x1,%edx
  c8eaa4:	be 73 3a fd 00       	mov    $0xfd3a73,%esi
  c8eaa9:	48 89 df             	mov    %rbx,%rdi
  c8eaac:	e8 77 56 8c ff       	call   554128 <_ZNSs6appendEPKcm@plt>
  c8eab1:	48 89 de             	mov    %rbx,%rsi
  c8eab4:	48 89 ef             	mov    %rbp,%rdi
  c8eab7:	e8 ec 3e 8c ff       	call   5529a8 <_ZNSsC1ERKSs@plt>
  c8eabc:	48 89 e6             	mov    %rsp,%rsi
  c8eabf:	48 89 ef             	mov    %rbp,%rdi
  c8eac2:	e8 01 65 8c ff       	call   554fc8 <_ZNSs6appendERKSs@plt>
  c8eac7:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  c8eacc:	48 83 ef 18          	sub    $0x18,%rdi
  c8ead0:	48 81 ff 20 3a 42 01 	cmp    $0x1423a20,%rdi
  c8ead7:	75 2e                	jne    c8eb07 <_ZN7STRINGS10uniqueNameERKSs+0xb7>
  c8ead9:	48 8b 3c 24          	mov    (%rsp),%rdi
  c8eadd:	b8 20 3a 42 01       	mov    $0x1423a20,%eax
  c8eae2:	48 83 ef 18          	sub    $0x18,%rdi
  c8eae6:	48 39 f8             	cmp    %rdi,%rax
  c8eae9:	75 42                	jne    c8eb2d <_ZN7STRINGS10uniqueNameERKSs+0xdd>
  c8eaeb:	48 89 e8             	mov    %rbp,%rax
  c8eaee:	48 8b 5c 24 28       	mov    0x28(%rsp),%rbx
  c8eaf3:	48 8b 6c 24 30       	mov    0x30(%rsp),%rbp
  c8eaf8:	4c 8b 64 24 38       	mov    0x38(%rsp),%r12
  c8eafd:	4c 8b 6c 24 40       	mov    0x40(%rsp),%r13
  c8eb02:	48 83 c4 48          	add    $0x48,%rsp
  c8eb06:	c3                   	ret
  c8eb07:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  c8eb0c:	48 85 c0             	test   %rax,%rax
  c8eb0f:	0f 84 7f 00 00 00    	je     c8eb94 <_ZN7STRINGS10uniqueNameERKSs+0x144>
  c8eb15:	83 c8 ff             	or     $0xffffffff,%eax
  c8eb18:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  c8eb1d:	85 c0                	test   %eax,%eax
  c8eb1f:	7f b8                	jg     c8ead9 <_ZN7STRINGS10uniqueNameERKSs+0x89>
  c8eb21:	48 8d 74 24 1f       	lea    0x1f(%rsp),%rsi
  c8eb26:	e8 ad 6c 8c ff       	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  c8eb2b:	eb ac                	jmp    c8ead9 <_ZN7STRINGS10uniqueNameERKSs+0x89>
  c8eb2d:	b8 c8 41 55 00       	mov    $0x5541c8,%eax
  c8eb32:	48 85 c0             	test   %rax,%rax
  c8eb35:	74 2b                	je     c8eb62 <_ZN7STRINGS10uniqueNameERKSs+0x112>
  c8eb37:	83 c8 ff             	or     $0xffffffff,%eax
  c8eb3a:	f0 0f c1 47 10       	lock xadd %eax,0x10(%rdi)
  c8eb3f:	85 c0                	test   %eax,%eax
  c8eb41:	7f a8                	jg     c8eaeb <_ZN7STRINGS10uniqueNameERKSs+0x9b>
  c8eb43:	48 8d 74 24 1e       	lea    0x1e(%rsp),%rsi
  c8eb48:	e8 8b 6c 8c ff       	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  c8eb4d:	eb 9c                	jmp    c8eaeb <_ZN7STRINGS10uniqueNameERKSs+0x9b>
  c8eb4f:	49 89 c5             	mov    %rax,%r13
  c8eb52:	48 89 e7             	mov    %rsp,%rdi
  c8eb55:	e8 2e 77 8c ff       	call   556288 <_ZNSsD1Ev@plt>
  c8eb5a:	4c 89 ef             	mov    %r13,%rdi
  c8eb5d:	e8 36 59 8c ff       	call   554498 <_Unwind_Resume@plt>
  c8eb62:	8b 47 10             	mov    0x10(%rdi),%eax
  c8eb65:	8d 50 ff             	lea    -0x1(%rax),%edx
  c8eb68:	89 57 10             	mov    %edx,0x10(%rdi)
  c8eb6b:	eb d2                	jmp    c8eb3f <_ZN7STRINGS10uniqueNameERKSs+0xef>
  c8eb6d:	49 89 c5             	mov    %rax,%r13
  c8eb70:	48 89 df             	mov    %rbx,%rdi
  c8eb73:	e8 10 77 8c ff       	call   556288 <_ZNSsD1Ev@plt>
  c8eb78:	eb d8                	jmp    c8eb52 <_ZN7STRINGS10uniqueNameERKSs+0x102>
  c8eb7a:	48 89 ef             	mov    %rbp,%rdi
  c8eb7d:	49 89 c5             	mov    %rax,%r13
  c8eb80:	e8 03 77 8c ff       	call   556288 <_ZNSsD1Ev@plt>
  c8eb85:	eb e9                	jmp    c8eb70 <_ZN7STRINGS10uniqueNameERKSs+0x120>
  c8eb87:	48 89 df             	mov    %rbx,%rdi
  c8eb8a:	49 89 c5             	mov    %rax,%r13
  c8eb8d:	e8 f6 76 8c ff       	call   556288 <_ZNSsD1Ev@plt>
  c8eb92:	eb be                	jmp    c8eb52 <_ZN7STRINGS10uniqueNameERKSs+0x102>
  c8eb94:	8b 47 10             	mov    0x10(%rdi),%eax
  c8eb97:	8d 50 ff             	lea    -0x1(%rax),%edx
  c8eb9a:	89 57 10             	mov    %edx,0x10(%rdi)
  c8eb9d:	e9 7b ff ff ff       	jmp    c8eb1d <_ZN7STRINGS10uniqueNameERKSs+0xcd>
