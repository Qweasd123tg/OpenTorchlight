
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ab30 <CKeyManager::flush()>:
  91ab30:	movb   $0x0,0x711(%rdi)
  91ab37:	movw   $0x0,0x712(%rdi)
  91ab40:	mov    %rdi,%rdx
  91ab43:	movl   $0x0,0x714(%rdi)
  91ab4d:	lea    0x718(%rdi),%rdi
  91ab54:	xor    %eax,%eax
  91ab56:	mov    $0x3f,%ecx
  91ab5b:	rep stos %rax,(%rdi)
  91ab5e:	movb   $0x0,(%rdi)
  91ab61:	lea    0xb18(%rdx),%rdi
  91ab68:	mov    $0x3f,%cl
  91ab6a:	movb   $0x0,0xb11(%rdx)
  91ab71:	movw   $0x0,0xb12(%rdx)
  91ab7a:	movl   $0x0,0xb14(%rdx)
  91ab84:	rep stos %rax,(%rdi)
  91ab87:	movb   $0x0,(%rdi)
  91ab8a:	ret
