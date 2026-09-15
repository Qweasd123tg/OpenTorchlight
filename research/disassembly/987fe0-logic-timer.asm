
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000987fe0 <CLogicTimer::resetTimer()>:
  987fe0:	48 83 ec 18          	sub    $0x18,%rsp
  987fe4:	f3 0f 10 4f 5c       	movss  0x5c(%rdi),%xmm1
  987fe9:	f3 0f 10 47 58       	movss  0x58(%rdi),%xmm0
  987fee:	0f 2e c8             	ucomiss %xmm0,%xmm1
  987ff1:	77 0d                	ja     988000 <CLogicTimer::resetTimer()+0x20>
  987ff3:	f3 0f 11 47 60       	movss  %xmm0,0x60(%rdi)
  987ff8:	48 83 c4 18          	add    $0x18,%rsp
  987ffc:	c3                   	ret
  987ffd:	0f 1f 00             	nopl   (%rax)
  988000:	48 89 7c 24 08       	mov    %rdi,0x8(%rsp)
  988005:	e8 46 ab 30 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  98800a:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  98800f:	f3 0f 11 47 60       	movss  %xmm0,0x60(%rdi)
  988014:	48 83 c4 18          	add    $0x18,%rsp
  988018:	c3                   	ret
  988019:	90                   	nop
  98801a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000988020 <CLogicTimer::update(float)>:
  988020:	53                   	push   %rbx
  988021:	48 89 fb             	mov    %rdi,%rbx
  988024:	48 83 ec 10          	sub    $0x10,%rsp
  988028:	f3 0f 11 44 24 0c    	movss  %xmm0,0xc(%rsp)
  98802e:	48 8b 7f 70          	mov    0x70(%rdi),%rdi
  988032:	48 85 ff             	test   %rdi,%rdi
  988035:	74 71                	je     9880a8 <CLogicTimer::update(float)+0x88>
  988037:	e8 a4 74 3e 00       	call   d6f4e0 <CResourceManager::getEditorIsRunning()>
  98803c:	84 c0                	test   %al,%al
  98803e:	75 68                	jne    9880a8 <CLogicTimer::update(float)+0x88>
  988040:	80 7b 6d 00          	cmpb   $0x0,0x6d(%rbx)
  988044:	75 07                	jne    98804d <CLogicTimer::update(float)+0x2d>
  988046:	8b 43 68             	mov    0x68(%rbx),%eax
  988049:	85 c0                	test   %eax,%eax
  98804b:	7e 5b                	jle    9880a8 <CLogicTimer::update(float)+0x88>
  98804d:	48 83 7b 70 00       	cmpq   $0x0,0x70(%rbx)
  988052:	74 54                	je     9880a8 <CLogicTimer::update(float)+0x88>
  988054:	80 7b 6c 00          	cmpb   $0x0,0x6c(%rbx)
  988058:	74 4e                	je     9880a8 <CLogicTimer::update(float)+0x88>
  98805a:	f3 0f 10 43 60       	movss  0x60(%rbx),%xmm0
  98805f:	f3 0f 5c 44 24 0c    	subss  0xc(%rsp),%xmm0
  988065:	0f 2e 05 8c c7 61 00 	ucomiss 0x61c78c(%rip),%xmm0        # fa47f8 <vtable for Ogre::FrameListener+0x38>
  98806c:	f3 0f 11 43 60       	movss  %xmm0,0x60(%rbx)
  988071:	77 35                	ja     9880a8 <CLogicTimer::update(float)+0x88>
  988073:	7a 33                	jp     9880a8 <CLogicTimer::update(float)+0x88>
  988075:	48 8b 03             	mov    (%rbx),%rax
  988078:	be 08 00 00 00       	mov    $0x8,%esi
  98807d:	48 89 df             	mov    %rbx,%rdi
  988080:	ff 50 30             	call   *0x30(%rax)
  988083:	80 7b 6d 00          	cmpb   $0x0,0x6d(%rbx)
  988087:	75 0d                	jne    988096 <CLogicTimer::update(float)+0x76>
  988089:	8b 43 68             	mov    0x68(%rbx),%eax
  98808c:	83 e8 01             	sub    $0x1,%eax
  98808f:	85 c0                	test   %eax,%eax
  988091:	89 43 68             	mov    %eax,0x68(%rbx)
  988094:	7e 12                	jle    9880a8 <CLogicTimer::update(float)+0x88>
  988096:	48 89 df             	mov    %rbx,%rdi
  988099:	48 83 c4 10          	add    $0x10,%rsp
  98809d:	5b                   	pop    %rbx
  98809e:	e9 3d ff ff ff       	jmp    987fe0 <CLogicTimer::resetTimer()>
  9880a3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  9880a8:	48 83 c4 10          	add    $0x10,%rsp
  9880ac:	5b                   	pop    %rbx
  9880ad:	c3                   	ret
  9880ae:	66 90                	xchg   %ax,%ax

00000000009880b0 <CLogicTimer::setEnabled(bool)>:
  9880b0:	53                   	push   %rbx
  9880b1:	40 88 77 6c          	mov    %sil,0x6c(%rdi)
  9880b5:	48 89 fb             	mov    %rdi,%rbx
  9880b8:	48 8b 7f 70          	mov    0x70(%rdi),%rdi
  9880bc:	e8 1f 74 3e 00       	call   d6f4e0 <CResourceManager::getEditorIsRunning()>
  9880c1:	84 c0                	test   %al,%al
  9880c3:	74 0b                	je     9880d0 <CLogicTimer::setEnabled(bool)+0x20>
  9880c5:	5b                   	pop    %rbx
  9880c6:	c3                   	ret
  9880c7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  9880ce:	00 00 
  9880d0:	48 89 df             	mov    %rbx,%rdi
  9880d3:	e8 08 ff ff ff       	call   987fe0 <CLogicTimer::resetTimer()>
  9880d8:	80 7b 6c 00          	cmpb   $0x0,0x6c(%rbx)
  9880dc:	74 22                	je     988100 <CLogicTimer::setEnabled(bool)+0x50>
  9880de:	48 8b 03             	mov    (%rbx),%rax
  9880e1:	be 06 00 00 00       	mov    $0x6,%esi
  9880e6:	48 89 df             	mov    %rbx,%rdi
  9880e9:	ff 50 30             	call   *0x30(%rax)
  9880ec:	8b 53 68             	mov    0x68(%rbx),%edx
  9880ef:	85 d2                	test   %edx,%edx
  9880f1:	7f d2                	jg     9880c5 <CLogicTimer::setEnabled(bool)+0x15>
  9880f3:	c7 43 68 01 00 00 00 	movl   $0x1,0x68(%rbx)
  9880fa:	5b                   	pop    %rbx
  9880fb:	c3                   	ret
  9880fc:	0f 1f 40 00          	nopl   0x0(%rax)
  988100:	48 8b 03             	mov    (%rbx),%rax
  988103:	48 89 df             	mov    %rbx,%rdi
  988106:	be 07 00 00 00       	mov    $0x7,%esi
  98810b:	5b                   	pop    %rbx
  98810c:	48 8b 40 30          	mov    0x30(%rax),%rax
  988110:	ff e0                	jmp    *%rax
