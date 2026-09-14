
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000056e4d0 <CGameClient::processMenuInput(void*, float, bool)>:
  56e4d0:	mov    %rbx,-0x18(%rsp)
  56e4d5:	mov    %rbp,-0x10(%rsp)
  56e4da:	mov    %rdi,%rbx
  56e4dd:	mov    %r12,-0x8(%rsp)
  56e4e2:	sub    $0x18,%rsp
  56e4e6:	mov    0x78(%rdi),%rdi
  56e4ea:	mov    %rsi,%r12
  56e4ed:	lea    0xfe8(%rbx),%rbp
  56e4f4:	test   %rdi,%rdi
  56e4f7:	je     56e53f <CGameClient::processMenuInput(void*, float, bool)+0x6f>
  56e4f9:	movzbl %dl,%ecx
  56e4fc:	mov    %rsi,%rdx
  56e4ff:	mov    %rbx,%rsi
  56e502:	call   ab80c0 <CGameUI::processInput(CGameClient*, void*, float, bool)>
  56e507:	test   %al,%al
  56e509:	jne    56e53f <CGameClient::processMenuInput(void*, float, bool)+0x6f>
  56e50b:	xor    %esi,%esi
  56e50d:	mov    %rbp,%rdi
  56e510:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  56e515:	test   %al,%al
  56e517:	je     56e520 <CGameClient::processMenuInput(void*, float, bool)+0x50>
  56e519:	movb   $0x1,0x99(%rbx)
  56e520:	mov    $0x1,%esi
  56e525:	mov    %rbp,%rdi
  56e528:	call   91ad30 <CMouseManager::buttonHeld(EMouseButton)>
  56e52d:	test   %al,%al
  56e52f:	je     56e538 <CGameClient::processMenuInput(void*, float, bool)+0x68>
  56e531:	movb   $0x1,0x9a(%rbx)
  56e538:	movb   $0x1,0x98(%rbx)
  56e53f:	mov    %r12,%rsi
  56e542:	mov    %rbp,%rdi
  56e545:	call   91aec0 <CMouseManager::update(void*)>
  56e54a:	mov    $0x1,%eax
  56e54f:	mov    (%rsp),%rbx
  56e553:	mov    0x8(%rsp),%rbp
  56e558:	mov    0x10(%rsp),%r12
  56e55d:	add    $0x18,%rsp
  56e561:	ret
