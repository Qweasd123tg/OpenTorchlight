
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ad20 <CMouseManager::buttonPressed(EMouseButton)>:
  91ad20:	movslq %esi,%rsi
  91ad23:	cmpb   $0x1,0x10(%rdi,%rsi,1)
  91ad28:	sete   %al
  91ad2b:	ret
