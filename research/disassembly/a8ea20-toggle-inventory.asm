
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000a8ea20 <_ZN7CGameUI15toggleInventoryEv>:
  a8ea20:	push   %rbp
  a8ea21:	push   %rbx
  a8ea22:	mov    %rdi,%rbx
  a8ea25:	sub    $0x8,%rsp
  a8ea29:	call   a8e440 <_ZN7CGameUI7unPauseEv>
  a8ea2e:	mov    0x4c0(%rbx),%rax
  a8ea35:	mov    0x348(%rax),%rsi
  a8ea3c:	mov    0xb0(%rsi),%rdi
  a8ea43:	test   %rdi,%rdi
  a8ea46:	je     a8ea4d <_ZN7CGameUI15toggleInventoryEv+0x2d>
  a8ea48:	call   552ae8 <_ZN5CEGUI6Window17removeChildWindowEPS0_@plt>
  a8ea4d:	mov    0x4d8(%rbx),%rdi
  a8ea54:	mov    (%rdi),%rax
  a8ea57:	call   *0x28(%rax)
  a8ea5a:	test   %al,%al
  a8ea5c:	je     a8ead0 <_ZN7CGameUI15toggleInventoryEv+0xb0>
  a8ea5e:	mov    0x4d8(%rbx),%rdi
  a8ea65:	mov    (%rdi),%rax
  a8ea68:	call   *0x20(%rax)
  a8ea6b:	test   %al,%al
  a8ea6d:	jne    a8eb10 <_ZN7CGameUI15toggleInventoryEv+0xf0>
  a8ea73:	mov    0x508(%rbx),%rdi
  a8ea7a:	mov    (%rdi),%rax
  a8ea7d:	call   *0x20(%rax)
  a8ea80:	test   %al,%al
  a8ea82:	jne    a8eae8 <_ZN7CGameUI15toggleInventoryEv+0xc8>
  a8ea84:	mov    0x4d8(%rbx),%rdi
  a8ea8b:	mov    (%rdi),%rax
  a8ea8e:	call   *0x28(%rax)
  a8ea91:	test   %al,%al
  a8ea93:	je     a8eb00 <_ZN7CGameUI15toggleInventoryEv+0xe0>
  a8ea95:	mov    0x4d8(%rbx),%rdi
  a8ea9c:	mov    (%rdi),%rax
  a8ea9f:	mov    0x40(%rax),%rbp
  a8eaa3:	call   *0x28(%rax)
  a8eaa6:	xor    $0x1,%eax
  a8eaa9:	mov    0x4d8(%rbx),%rdi
  a8eab0:	movzbl %al,%esi
  a8eab3:	call   *%rbp
  a8eab5:	mov    0x138(%rbx),%rdi
  a8eabc:	add    $0x8,%rsp
  a8eac0:	pop    %rbx
  a8eac1:	pop    %rbp
  a8eac2:	jmp    5547c8 <_ZN5CEGUI6Window11moveToFrontEv@plt>
  a8eac7:	nopw   0x0(%rax,%rax,1)
  a8ead0:	mov    %rbx,%rdi
  a8ead3:	call   a829f0 <_ZN7CGameUI15modalDialogOpenEv>
  a8ead8:	test   %al,%al
  a8eada:	je     a8ea5e <_ZN7CGameUI15toggleInventoryEv+0x3e>
  a8eadc:	add    $0x8,%rsp
  a8eae0:	pop    %rbx
  a8eae1:	pop    %rbp
  a8eae2:	ret
  a8eae3:	nopl   0x0(%rax,%rax,1)
  a8eae8:	mov    0x508(%rbx),%rdi
  a8eaef:	xor    %esi,%esi
  a8eaf1:	mov    (%rdi),%rax
  a8eaf4:	call   *0x40(%rax)
  a8eaf7:	jmp    a8ea84 <_ZN7CGameUI15toggleInventoryEv+0x64>
  a8eaf9:	nopl   0x0(%rax)
  a8eb00:	mov    %rbx,%rdi
  a8eb03:	call   a83450 <_ZN7CGameUI10closeRightEv>
  a8eb08:	jmp    a8ea95 <_ZN7CGameUI15toggleInventoryEv+0x75>
  a8eb0a:	nopw   0x0(%rax,%rax,1)
  a8eb10:	mov    0x4f0(%rbx),%rdi
  a8eb17:	xor    %esi,%esi
  a8eb19:	mov    (%rdi),%rax
  a8eb1c:	call   *0x40(%rax)
  a8eb1f:	mov    0x4f8(%rbx),%rdi
  a8eb26:	xor    %esi,%esi
  a8eb28:	mov    (%rdi),%rax
  a8eb2b:	call   *0x40(%rax)
  a8eb2e:	mov    0x500(%rbx),%rdi
  a8eb35:	xor    %esi,%esi
  a8eb37:	mov    (%rdi),%rax
  a8eb3a:	call   *0x40(%rax)
  a8eb3d:	jmp    a8ea73 <_ZN7CGameUI15toggleInventoryEv+0x53>
  a8eb42:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
