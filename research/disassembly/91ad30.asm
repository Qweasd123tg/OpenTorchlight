
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ad30 <CMouseManager::buttonHeld(EMouseButton)>:
  91ad30:	movslq %esi,%rsi
  91ad33:	mov    $0x1,%eax
  91ad38:	cmpb   $0x1,0x13(%rdi,%rsi,1)
  91ad3d:	je     91ad47 <CMouseManager::buttonHeld(EMouseButton)+0x17>
  91ad3f:	cmpb   $0x1,0x10(%rdi,%rsi,1)
  91ad44:	sete   %al
  91ad47:	repz ret
