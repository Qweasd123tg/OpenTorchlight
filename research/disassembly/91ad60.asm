
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ad60 <CMouseManager::virtualMousePosition(float, float, float, float)>:
  91ad60:	divss  %xmm0,%xmm2
  91ad64:	cvtsi2ssq 0x28(%rdi),%xmm4
  91ad6a:	cvtsi2ssq 0x30(%rdi),%xmm0
  91ad70:	divss  %xmm1,%xmm3
  91ad74:	mulss  %xmm2,%xmm4
  91ad78:	mulss  %xmm3,%xmm0
  91ad7c:	cvttss2si %xmm4,%eax
  91ad80:	cltq
  91ad82:	mov    %rax,0x38(%rdi)
  91ad86:	cvttss2si %xmm0,%eax
  91ad8a:	cltq
  91ad8c:	mov    %rax,0x40(%rdi)
  91ad90:	lea    0x38(%rdi),%rax
  91ad94:	ret
