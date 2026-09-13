
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091a980 <CKeyManager::capture()>:
  91a980:	movzbl 0x711(%rdi),%eax
  91a987:	mov    %rdi,%rdx
  91a98a:	lea    0x718(%rdx),%rsi
  91a991:	mov    %al,0x11(%rdi)
  91a994:	movzwl 0x712(%rdi),%eax
  91a99b:	mov    %ax,0x12(%rdi)
  91a99f:	mov    0x714(%rdi),%eax
  91a9a5:	mov    %eax,0x14(%rdi)
  91a9a8:	mov    $0x3f,%eax
  91a9ad:	lea    0x18(%rdi),%rdi
  91a9b1:	mov    %rax,%rcx
  91a9b4:	rep movsq (%rsi),(%rdi)
  91a9b7:	mov    %rcx,%rax
  91a9ba:	movzbl (%rsi),%ecx
  91a9bd:	lea    0xb18(%rdx),%rsi
  91a9c4:	mov    %cl,(%rdi)
  91a9c6:	movzbl 0xb11(%rdx),%ecx
  91a9cd:	lea    0x418(%rdx),%rdi
  91a9d4:	mov    %cl,0x411(%rdx)
  91a9da:	movzwl 0xb12(%rdx),%ecx
  91a9e1:	mov    %cx,0x412(%rdx)
  91a9e8:	mov    0xb14(%rdx),%ecx
  91a9ee:	mov    %ecx,0x414(%rdx)
  91a9f4:	mov    $0x3f,%ecx
  91a9f9:	rep movsq (%rsi),(%rdi)
  91a9fc:	movzbl (%rsi),%ecx
  91a9ff:	lea    0x918(%rdx),%rsi
  91aa06:	mov    %cl,(%rdi)
  91aa08:	movzbl 0x911(%rdx),%ecx
  91aa0f:	lea    0x218(%rdx),%rdi
  91aa16:	mov    %cl,0x211(%rdx)
  91aa1c:	movzwl 0x912(%rdx),%ecx
  91aa23:	mov    %cx,0x212(%rdx)
  91aa2a:	mov    0x914(%rdx),%ecx
  91aa30:	mov    %ecx,0x214(%rdx)
  91aa36:	mov    $0x3f,%ecx
  91aa3b:	rep movsq (%rsi),(%rdi)
  91aa3e:	movzbl (%rsi),%ecx
  91aa41:	mov    %cl,(%rdi)
  91aa43:	lea    0x718(%rdx),%rdi
  91aa4a:	mov    $0x3f,%ecx
  91aa4f:	movb   $0x0,0x711(%rdx)
  91aa56:	movw   $0x0,0x712(%rdx)
  91aa5f:	movl   $0x0,0x714(%rdx)
  91aa69:	rep stos %rax,(%rdi)
  91aa6c:	movb   $0x0,(%rdi)
  91aa6f:	lea    0xb18(%rdx),%rdi
  91aa76:	mov    $0x3f,%cl
  91aa78:	movb   $0x0,0xb11(%rdx)
  91aa7f:	movw   $0x0,0xb12(%rdx)
  91aa88:	movl   $0x0,0xb14(%rdx)
  91aa92:	rep stos %rax,(%rdi)
  91aa95:	movb   $0x0,(%rdi)
  91aa98:	ret
