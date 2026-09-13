
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091aaa0 <CKeyManager::flushAll()>:
  91aaa0:	movb   $0x0,0x911(%rdi)
  91aaa7:	movw   $0x0,0x912(%rdi)
  91aab0:	mov    %rdi,%rdx
  91aab3:	movl   $0x0,0x914(%rdi)
  91aabd:	lea    0x918(%rdi),%rdi
  91aac4:	xor    %eax,%eax
  91aac6:	mov    $0x3f,%ecx
  91aacb:	rep stos %rax,(%rdi)
  91aace:	movb   $0x0,(%rdi)
  91aad1:	lea    0x718(%rdx),%rdi
  91aad8:	mov    $0x3f,%cl
  91aada:	movb   $0x0,0x711(%rdx)
  91aae1:	movw   $0x0,0x712(%rdx)
  91aaea:	movl   $0x0,0x714(%rdx)
  91aaf4:	rep stos %rax,(%rdi)
  91aaf7:	movb   $0x0,(%rdi)
  91aafa:	lea    0xb18(%rdx),%rdi
  91ab01:	mov    $0x3f,%cl
  91ab03:	movb   $0x0,0xb11(%rdx)
  91ab0a:	movw   $0x0,0xb12(%rdx)
  91ab13:	movl   $0x0,0xb14(%rdx)
  91ab1d:	rep stos %rax,(%rdi)
  91ab20:	movb   $0x0,(%rdi)
  91ab23:	ret
