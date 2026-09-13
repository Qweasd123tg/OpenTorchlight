
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ac90 <CMouseManager::mouseEvent(unsigned int, unsigned int)>:
  91ac90:	sub    $0x201,%esi
  91ac96:	cmp    $0x9,%esi
  91ac99:	ja     91acb0 <CMouseManager::mouseEvent(unsigned int, unsigned int)+0x20>
  91ac9b:	mov    %esi,%esi
  91ac9d:	jmp    *0xfd48a8(,%rsi,8)
  91aca4:	nopl   0x0(%rax)
  91aca8:	sar    $0x10,%edx
  91acab:	add    %edx,0x4c(%rdi)
  91acae:	xchg   %ax,%ax
  91acb0:	repz ret
  91acb2:	nopw   0x0(%rax,%rax,1)
  91acb8:	cmpb   $0x0,0x1c(%rdi)
  91acbc:	jne    91acc2 <CMouseManager::mouseEvent(unsigned int, unsigned int)+0x32>
  91acbe:	movb   $0x1,0x19(%rdi)
  91acc2:	movb   $0x1,0x1c(%rdi)
  91acc6:	ret
  91acc7:	nopw   0x0(%rax,%rax,1)
  91acd0:	movb   $0x0,0x1c(%rdi)
  91acd4:	ret
  91acd5:	nopl   (%rax)
  91acd8:	movb   $0x1,0x1f(%rdi)
  91acdc:	ret
  91acdd:	nopl   (%rax)
  91ace0:	cmpb   $0x0,0x1d(%rdi)
  91ace4:	jne    91acea <CMouseManager::mouseEvent(unsigned int, unsigned int)+0x5a>
  91ace6:	movb   $0x1,0x1a(%rdi)
  91acea:	movb   $0x1,0x1d(%rdi)
  91acee:	ret
  91acef:	nop
  91acf0:	movb   $0x0,0x1d(%rdi)
  91acf4:	ret
  91acf5:	nopl   (%rax)
  91acf8:	movb   $0x1,0x20(%rdi)
  91acfc:	ret
  91acfd:	nopl   (%rax)
  91ad00:	cmpb   $0x0,0x1e(%rdi)
  91ad04:	jne    91ad0a <CMouseManager::mouseEvent(unsigned int, unsigned int)+0x7a>
  91ad06:	movb   $0x1,0x1b(%rdi)
  91ad0a:	movb   $0x1,0x1e(%rdi)
  91ad0e:	ret
  91ad0f:	nop
  91ad10:	movb   $0x0,0x1e(%rdi)
  91ad14:	ret
