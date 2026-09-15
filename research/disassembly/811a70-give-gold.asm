0000000000811a70 <CCharacter::giveGold(int)>:
  811a70:	55                   	push   rbp
  811a71:	89 f5                	mov    ebp,esi
  811a73:	53                   	push   rbx
  811a74:	48 89 fb             	mov    rbx,rdi
  811a77:	48 83 ec 08          	sub    rsp,0x8
  811a7b:	eb 06                	jmp    811a83 <CCharacter::giveGold(int)+0x13>
  811a7d:	0f 1f 00             	nop    DWORD PTR [rax]
  811a80:	48 89 c3             	mov    rbx,rax
  811a83:	48 8b 83 40 06 00 00 	mov    rax,QWORD PTR [rbx+0x640]
  811a8a:	48 85 c0             	test   rax,rax
  811a8d:	75 f1                	jne    811a80 <CCharacter::giveGold(int)+0x10>
  811a8f:	85 ed                	test   ebp,ebp
  811a91:	7e 4d                	jle    811ae0 <CCharacter::giveGold(int)+0x70>
  811a93:	89 ea                	mov    edx,ebp
  811a95:	be 01 00 00 00       	mov    esi,0x1
  811a9a:	48 89 df             	mov    rdi,rbx
  811a9d:	e8 3e ff ff ff       	call   8119e0 <CCharacter::incrementJournalStatistic(EJournalStatistic, int)>
  811aa2:	8b 83 44 04 00 00    	mov    eax,DWORD PTR [rbx+0x444]
  811aa8:	01 c5                	add    ebp,eax
  811aaa:	39 e8                	cmp    eax,ebp
  811aac:	7f 1a                	jg     811ac8 <CCharacter::giveGold(int)+0x58>
  811aae:	31 c0                	xor    eax,eax
  811ab0:	85 ed                	test   ebp,ebp
  811ab2:	0f 49 c5             	cmovns eax,ebp
  811ab5:	89 83 44 04 00 00    	mov    DWORD PTR [rbx+0x444],eax
  811abb:	48 83 c4 08          	add    rsp,0x8
  811abf:	5b                   	pop    rbx
  811ac0:	5d                   	pop    rbp
  811ac1:	c3                   	ret
  811ac2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  811ac8:	c7 83 44 04 00 00 ff ff ff 7f 	mov    DWORD PTR [rbx+0x444],0x7fffffff
  811ad2:	48 83 c4 08          	add    rsp,0x8
  811ad6:	5b                   	pop    rbx
  811ad7:	5d                   	pop    rbp
  811ad8:	c3                   	ret
  811ad9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  811ae0:	03 ab 44 04 00 00    	add    ebp,DWORD PTR [rbx+0x444]
  811ae6:	eb c6                	jmp    811aae <CCharacter::giveGold(int)+0x3e>
  811ae8:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

