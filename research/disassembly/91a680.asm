
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091a680 <CKeyManager::keyHeld(unsigned int)>:
  91a680:	mov    %esi,%esi
  91a682:	mov    $0x1,%eax
  91a687:	cmpb   $0x1,0x211(%rdi,%rsi,1)
  91a68f:	je     91a699 <CKeyManager::keyHeld(unsigned int)+0x19>
  91a691:	cmpb   $0x1,0x11(%rdi,%rsi,1)
  91a696:	sete   %al
  91a699:	repz ret
