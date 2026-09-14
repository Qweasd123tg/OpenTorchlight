
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000ed6700 <SDLEventHandler::ProcessEvent(SDL_Event const&)>:
  ed6700:	push   %r12
  ed6702:	push   %rbp
  ed6703:	mov    %rsi,%rbp
  ed6706:	push   %rbx
  ed6707:	mov    %rdi,%rbx
  ed670a:	mov    0x8(%rdi),%rdi
  ed670e:	test   %rdi,%rdi
  ed6711:	je     ed686f <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x16f>
  ed6717:	mov    (%rsi),%eax
  ed6719:	cmp    $0x400,%eax
  ed671e:	je     ed6750 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x50>
  ed6720:	jbe    ed6878 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x178>
  ed6726:	cmp    $0x402,%eax
  ed672b:	ja     ed68a8 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x1a8>
  ed6731:	movzbl 0xc(%rsi),%eax
  ed6735:	cmp    $0x2,%al
  ed6737:	je     ed6960 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x260>
  ed673d:	cmp    $0x3,%al
  ed673f:	je     ed6940 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x240>
  ed6745:	cmp    $0x1,%al
  ed6747:	je     ed690e <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x20e>
  ed674d:	nopl   (%rax)
  ed6750:	pop    %rbx
  ed6751:	movslq 0x14(%rbp),%rsi
  ed6755:	movslq 0x10(%rbp),%rdi
  ed6759:	pop    %rbp
  ed675a:	pop    %r12
  ed675c:	jmp    f63210 <UpdateCursorPos(long, long)>
  ed6761:	nopl   0x0(%rax)
  ed6768:	cmp    %rdi,%r8
  ed676b:	je     ed679a <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x9a>
  ed676d:	mov    0x10(%rbp),%eax
  ed6770:	cmp    0x20(%rdi),%eax
  ed6773:	jl     ed679a <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x9a>
  ed6775:	movzwl 0x24(%rdi),%r12d
  ed677a:	mov    0x8(%rbx),%rdi
  ed677e:	xor    %ecx,%ecx
  ed6780:	mov    %r12d,%edx
  ed6783:	call   56e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>
  ed6788:	xor    %esi,%esi
  ed678a:	cmpb   $0x1,0xc(%rbp)
  ed678e:	mov    %r12d,%edi
  ed6791:	sete   %sil
  ed6795:	call   f63250 <UpdateKeyState(unsigned int, bool)>
  ed679a:	call   555558 <SDL_GetModState@plt>
  ed679f:	test   $0x3,%al
  ed67a1:	mov    %eax,%ebp
  ed67a3:	movzwl 0x10(%rbx),%eax
  ed67a7:	setne  %r12b
  ed67ab:	test   $0x3,%al
  ed67ad:	setne  %dl
  ed67b0:	cmp    %r12b,%dl
  ed67b3:	je     ed67e6 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0xe6>
  ed67b5:	mov    %r12d,%esi
  ed67b8:	mov    0x8(%rbx),%rdi
  ed67bc:	xor    %ecx,%ecx
  ed67be:	shl    $0x1f,%esi
  ed67c1:	mov    $0x10,%edx
  ed67c6:	sar    $0x1f,%esi
  ed67c9:	add    $0x101,%esi
  ed67cf:	call   56e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>
  ed67d4:	movzbl %r12b,%esi
  ed67d8:	mov    $0x10,%edi
  ed67dd:	call   f63250 <UpdateKeyState(unsigned int, bool)>
  ed67e2:	movzwl 0x10(%rbx),%eax
  ed67e6:	test   $0xc0,%bpl
  ed67ea:	setne  %r12b
  ed67ee:	test   $0xc0,%al
  ed67f0:	setne  %dl
  ed67f3:	cmp    %r12b,%dl
  ed67f6:	je     ed6829 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x129>
  ed67f8:	mov    %r12d,%esi
  ed67fb:	mov    0x8(%rbx),%rdi
  ed67ff:	xor    %ecx,%ecx
  ed6801:	shl    $0x1f,%esi
  ed6804:	mov    $0x11,%edx
  ed6809:	sar    $0x1f,%esi
  ed680c:	add    $0x101,%esi
  ed6812:	call   56e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>
  ed6817:	movzbl %r12b,%esi
  ed681b:	mov    $0x11,%edi
  ed6820:	call   f63250 <UpdateKeyState(unsigned int, bool)>
  ed6825:	movzwl 0x10(%rbx),%eax
  ed6829:	test   $0x300,%ebp
  ed682f:	setne  %r12b
  ed6833:	test   $0x3,%ah
  ed6836:	setne  %al
  ed6839:	cmp    %r12b,%al
  ed683c:	je     ed686b <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x16b>
  ed683e:	mov    %r12d,%esi
  ed6841:	mov    0x8(%rbx),%rdi
  ed6845:	xor    %ecx,%ecx
  ed6847:	shl    $0x1f,%esi
  ed684a:	mov    $0x12,%edx
  ed684f:	sar    $0x1f,%esi
  ed6852:	add    $0x101,%esi
  ed6858:	call   56e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>
  ed685d:	movzbl %r12b,%esi
  ed6861:	mov    $0x12,%edi
  ed6866:	call   f63250 <UpdateKeyState(unsigned int, bool)>
  ed686b:	mov    %bp,0x10(%rbx)
  ed686f:	pop    %rbx
  ed6870:	pop    %rbp
  ed6871:	pop    %r12
  ed6873:	ret
  ed6874:	nopl   0x0(%rax)
  ed6878:	cmp    $0x300,%eax
  ed687d:	jb     ed686f <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x16f>
  ed687f:	cmp    $0x301,%eax
  ed6884:	jbe    ed68c5 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x1c5>
  ed6886:	cmp    $0x303,%eax
  ed688b:	jne    ed686f <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x16f>
  ed688d:	pop    %rbx
  ed688e:	pop    %rbp
  ed688f:	movsbl 0xc(%rsi),%edx
  ed6893:	xor    %ecx,%ecx
  ed6895:	mov    $0x102,%esi
  ed689a:	pop    %r12
  ed689c:	jmp    56e650 <CGameClient::keyEvent(unsigned int, unsigned int, long)>
  ed68a1:	nopl   0x0(%rax)
  ed68a8:	cmp    $0x403,%eax
  ed68ad:	jne    ed686f <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x16f>
  ed68af:	mov    0xc(%rsi),%eax
  ed68b2:	test   %eax,%eax
  ed68b4:	je     ed68c5 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x1c5>
  ed68b6:	mov    %eax,%edx
  ed68b8:	mov    $0x20a,%esi
  ed68bd:	shl    $0x10,%edx
  ed68c0:	call   56e600 <CGameClient::mouseEvent(unsigned int, unsigned int)>
  ed68c5:	xor    %esi,%esi
  ed68c7:	cmpb   $0x1,0xc(%rbp)
  ed68cb:	mov    0x28(%rbx),%rax
  ed68cf:	lea    0x20(%rbx),%r8
  ed68d3:	mov    %r8,%rdi
  ed68d6:	setne  %sil
  ed68da:	add    $0x100,%esi
  ed68e0:	test   %rax,%rax
  ed68e3:	je     ed6768 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x68>
  ed68e9:	mov    0x10(%rbp),%ecx
  ed68ec:	jmp    ed6903 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x203>
  ed68ee:	xchg   %ax,%ax
  ed68f0:	mov    0x10(%rax),%rdx
  ed68f4:	mov    %rax,%rdi
  ed68f7:	test   %rdx,%rdx
  ed68fa:	je     ed6768 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x68>
  ed6900:	mov    %rdx,%rax
  ed6903:	cmp    %ecx,0x20(%rax)
  ed6906:	jge    ed68f0 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x1f0>
  ed6908:	mov    0x18(%rax),%rdx
  ed690c:	jmp    ed68f7 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x1f7>
  ed690e:	xor    %esi,%esi
  ed6910:	cmpb   $0x1,0xd(%rbp)
  ed6914:	mov    $0x1,%ebx
  ed6919:	setne  %sil
  ed691d:	add    $0x201,%esi
  ed6923:	xor    %edx,%edx
  ed6925:	call   56e600 <CGameClient::mouseEvent(unsigned int, unsigned int)>
  ed692a:	xor    %esi,%esi
  ed692c:	cmpb   $0x1,0xd(%rbp)
  ed6930:	mov    %ebx,%edi
  ed6932:	sete   %sil
  ed6936:	call   f63250 <UpdateKeyState(unsigned int, bool)>
  ed693b:	jmp    ed6750 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x50>
  ed6940:	xor    %esi,%esi
  ed6942:	cmpb   $0x1,0xd(%rbp)
  ed6946:	mov    $0x2,%ebx
  ed694b:	setne  %sil
  ed694f:	add    $0x204,%esi
  ed6955:	jmp    ed6923 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x223>
  ed6957:	nopw   0x0(%rax,%rax,1)
  ed6960:	xor    %esi,%esi
  ed6962:	cmpb   $0x1,0xd(%rbp)
  ed6966:	mov    $0x4,%ebx
  ed696b:	setne  %sil
  ed696f:	add    $0x207,%esi
  ed6975:	jmp    ed6923 <SDLEventHandler::ProcessEvent(SDL_Event const&)+0x223>
