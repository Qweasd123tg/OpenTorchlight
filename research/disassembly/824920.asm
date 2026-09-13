
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000824920 <CCharacter::setTargetItem(CItem*)>:
  824920:	mov    %rbx,-0x18(%rsp)
  824925:	mov    %rbp,-0x10(%rsp)
  82492a:	mov    %rdi,%rbx
  82492d:	mov    %r12,-0x8(%rsp)
  824932:	sub    $0x18,%rsp
  824936:	mov    0x330(%rdi),%eax
  82493c:	mov    %rsi,%rbp
  82493f:	cmp    $0x5,%eax
  824942:	je     8249e0 <CCharacter::setTargetItem(CItem*)+0xc0>
  824948:	cmp    $0x6,%eax
  82494b:	je     8249e0 <CCharacter::setTargetItem(CItem*)+0xc0>
  824951:	test   %rsi,%rsi
  824954:	je     8249e5 <CCharacter::setTargetItem(CItem*)+0xc5>
  82495a:	mov    0x350(%rbx),%rdi
  824961:	cmp    %rdi,%rbp
  824964:	je     8249a3 <CCharacter::setTargetItem(CItem*)+0x83>
  824966:	test   %rdi,%rdi
  824969:	lea    0x350(%rbx),%r12
  824970:	je     824980 <CCharacter::setTargetItem(CItem*)+0x60>
  824972:	mov    0x358(%rbx),%edx
  824978:	mov    %r12,%rsi
  82497b:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  824980:	movq   $0x0,0x350(%rbx)
  82498b:	mov    %r12,%rsi
  82498e:	mov    %rbp,%rdi
  824991:	call   d797c0 <CRunicCore::addSafePointer(TSafePointer<void*>*)>
  824996:	mov    %rbp,0x350(%rbx)
  82499d:	mov    %eax,0x358(%rbx)
  8249a3:	mov    0x340(%rbx),%rdi
  8249aa:	test   %rdi,%rdi
  8249ad:	je     8249cc <CCharacter::setTargetItem(CItem*)+0xac>
  8249af:	mov    0x348(%rbx),%edx
  8249b5:	lea    0x340(%rbx),%rsi
  8249bc:	call   d796e0 <CRunicCore::removeSafePointer(TSafePointer<void*>*, unsigned int)>
  8249c1:	movq   $0x0,0x340(%rbx)
  8249cc:	mov    (%rsp),%rbx
  8249d0:	mov    0x8(%rsp),%rbp
  8249d5:	mov    0x10(%rsp),%r12
  8249da:	add    $0x18,%rsp
  8249de:	ret
  8249df:	nop
  8249e0:	test   %rbp,%rbp
  8249e3:	jne    8249cc <CCharacter::setTargetItem(CItem*)+0xac>
  8249e5:	lea    0x350(%rbx),%rdi
  8249ec:	mov    0x8(%rsp),%rbp
  8249f1:	mov    (%rsp),%rbx
  8249f5:	mov    0x10(%rsp),%r12
  8249fa:	xor    %esi,%esi
  8249fc:	add    $0x18,%rsp
  824a00:	jmp    591b80 <TSafePointer<CItem>::setObject(CItem*)>
