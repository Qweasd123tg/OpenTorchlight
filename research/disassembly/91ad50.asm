
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ad50 <CMouseManager::buttonDoubleClick(EMouseButton)>:
  91ad50:	movslq %esi,%rsi
  91ad53:	cmpb   $0x1,0x16(%rdi,%rsi,1)
  91ad58:	sete   %al
  91ad5b:	ret
