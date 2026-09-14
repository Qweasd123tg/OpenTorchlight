
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000091ab90 <CKeyManager::keyEvent(unsigned int, unsigned int)>:
  91ab90:	cmp    $0x101,%esi
  91ab96:	push   %rbx
  91ab97:	mov    %rdi,%rbx
  91ab9a:	je     91abae <CKeyManager::keyEvent(unsigned int, unsigned int)+0x1e>
  91ab9c:	jbe    91abd0 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x40>
  91ab9e:	cmp    $0x104,%esi
  91aba4:	je     91abf0 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x60>
  91aba6:	cmp    $0x105,%esi
  91abac:	jne    91abd8 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x48>
  91abae:	mov    %edx,%edx
  91abb0:	cmpb   $0x0,0x911(%rbx,%rdx,1)
  91abb8:	je     91abc2 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x32>
  91abba:	movb   $0x1,0xb11(%rbx,%rdx,1)
  91abc2:	movb   $0x0,0x911(%rbx,%rdx,1)
  91abca:	jmp    91abd8 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x48>
  91abcc:	nopl   0x0(%rax)
  91abd0:	cmp    $0x100,%esi
  91abd6:	je     91abf0 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x60>
  91abd8:	xor    %edi,%edi
  91abda:	call   5563a8 <SDL_GetKeyboardState@plt>
  91abdf:	cmpb   $0x0,0x39(%rax)
  91abe3:	setne  0x10(%rbx)
  91abe7:	pop    %rbx
  91abe8:	ret
  91abe9:	nopl   0x0(%rax)
  91abf0:	mov    %edx,%edx
  91abf2:	cmpb   $0x0,0x911(%rbx,%rdx,1)
  91abfa:	jne    91ac04 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x74>
  91abfc:	movb   $0x1,0x711(%rbx,%rdx,1)
  91ac04:	movb   $0x1,0x911(%rbx,%rdx,1)
  91ac0c:	jmp    91abd8 <CKeyManager::keyEvent(unsigned int, unsigned int)+0x48>
