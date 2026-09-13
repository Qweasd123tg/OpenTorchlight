
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ae10 <CMouseManager::capture()>:
  91ae10:	movzwl 0x1c(%rdi),%eax
  91ae14:	lea    0x19(%rdi),%rdx
  91ae18:	movzwl 0x1f(%rdi),%ecx
  91ae1c:	mov    %ax,0x13(%rdi)
  91ae20:	movzbl 0x1e(%rdi),%eax
  91ae24:	mov    %al,0x15(%rdi)
  91ae27:	movzwl 0x19(%rdi),%eax
  91ae2b:	mov    %ax,0x10(%rdi)
  91ae2f:	movzbl 0x2(%rdx),%eax
  91ae33:	mov    %cx,0x16(%rdi)
  91ae37:	mov    %al,0x12(%rdi)
  91ae3a:	lea    0x1f(%rdi),%rax
  91ae3e:	movzbl 0x2(%rax),%ecx
  91ae42:	movw   $0x0,0x19(%rdi)
  91ae48:	mov    %cl,0x18(%rdi)
  91ae4b:	movb   $0x0,0x2(%rdx)
  91ae4f:	movw   $0x0,0x1f(%rdi)
  91ae55:	movb   $0x0,0x2(%rax)
  91ae59:	mov    0x4c(%rdi),%eax
  91ae5c:	movl   $0x0,0x4c(%rdi)
  91ae63:	mov    %eax,0x48(%rdi)
  91ae66:	ret
