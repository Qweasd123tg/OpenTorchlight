
/home/qweasd123tg/Документы/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000057a900 <CGameClient::moveToMouse(bool)>:
  57a900:	push   %rbx
  57a901:	mov    %rdi,%rbx
  57a904:	sub    $0x40,%rsp
  57a908:	mov    0x58(%rdi),%rax
  57a90c:	lea    0x30(%rsp),%rsi
  57a911:	movzbl 0x266(%rax),%edx
  57a918:	call   579e90 <CGameClient::findWorldLocation(Ogre::Vector3&, bool)>
  57a91d:	test   %al,%al
  57a91f:	jne    57a930 <CGameClient::moveToMouse(bool)+0x30>
  57a921:	add    $0x40,%rsp
  57a925:	pop    %rbx
  57a926:	ret
  57a927:	nopw   0x0(%rax,%rax,1)
  57a930:	mov    0x58(%rbx),%rdi
  57a934:	mov    $0x1,%esi
  57a939:	call   9e7080 <CPositionableObject::getPosition(bool)>
  57a93e:	movq   %xmm0,0x8(%rsp)
  57a944:	mov    0x8(%rsp),%rax
  57a949:	movss  0x30(%rsp),%xmm0
  57a94f:	movss  %xmm1,0x18(%rsp)
  57a955:	mov    %rax,0x20(%rsp)
  57a95a:	mov    %rax,0x10(%rsp)
  57a95f:	ucomiss 0x20(%rsp),%xmm0
  57a964:	mov    0x18(%rsp),%eax
  57a968:	mov    %eax,0x28(%rsp)
  57a96c:	jne    57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a96e:	jp     57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a970:	movss  0x34(%rsp),%xmm1
  57a976:	ucomiss 0x24(%rsp),%xmm1
  57a97b:	jne    57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a97d:	jp     57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a97f:	movss  0x38(%rsp),%xmm1
  57a985:	ucomiss 0x28(%rsp),%xmm1
  57a98a:	jne    57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a98c:	jp     57a9b0 <CGameClient::moveToMouse(bool)+0xb0>
  57a98e:	mov    0x70(%rbx),%rsi
  57a992:	mov    0x58(%rbx),%rdi
  57a996:	call   82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  57a99b:	movl   $0x3dcccccd,0x80(%rbx)
  57a9a5:	jmp    57a921 <CGameClient::moveToMouse(bool)+0x21>
  57a9aa:	nopw   0x0(%rax,%rax,1)
  57a9b0:	xorps  %xmm1,%xmm1
  57a9b3:	ucomiss 0x80(%rbx),%xmm1
  57a9ba:	jb     57a921 <CGameClient::moveToMouse(bool)+0x21>
  57a9c0:	mov    0x70(%rbx),%rsi
  57a9c4:	mov    0x58(%rbx),%rdi
  57a9c8:	movss  0x38(%rsp),%xmm1
  57a9ce:	call   82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  57a9d3:	movl   $0x3dcccccd,0x80(%rbx)
  57a9dd:	add    $0x40,%rsp
  57a9e1:	pop    %rbx
  57a9e2:	ret
