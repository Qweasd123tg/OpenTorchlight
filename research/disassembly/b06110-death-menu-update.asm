0000000000b06110 <CDieMenu::update(float)>:
  b06110:	48 89 5c 24 f0       	mov    QWORD PTR [rsp-0x10],rbx
  b06115:	48 89 6c 24 f8       	mov    QWORD PTR [rsp-0x8],rbp
  b0611a:	48 83 ec 18          	sub    rsp,0x18
  b0611e:	80 7f 30 00          	cmp    BYTE PTR [rdi+0x30],0x0
  b06122:	48 89 fb             	mov    rbx,rdi
  b06125:	75 20                	jne    b06147 <CDieMenu::update(float)+0x37>
  b06127:	80 7f 31 00          	cmp    BYTE PTR [rdi+0x31],0x0
  b0612b:	75 1a                	jne    b06147 <CDieMenu::update(float)+0x37>
  b0612d:	80 bf c0 00 00 00 00 	cmp    BYTE PTR [rdi+0xc0],0x0
  b06134:	c6 47 31 01          	mov    BYTE PTR [rdi+0x31],0x1
  b06138:	0f 85 c2 00 00 00    	jne    b06200 <CDieMenu::update(float)+0xf0>
  b0613e:	80 bb c1 00 00 00 00 	cmp    BYTE PTR [rbx+0xc1],0x0
  b06145:	75 19                	jne    b06160 <CDieMenu::update(float)+0x50>
  b06147:	48 8b 5c 24 08       	mov    rbx,QWORD PTR [rsp+0x8]
  b0614c:	48 8b 6c 24 10       	mov    rbp,QWORD PTR [rsp+0x10]
  b06151:	48 83 c4 18          	add    rsp,0x18
  b06155:	c3                   	ret
  b06156:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  b06160:	48 8b 43 40          	mov    rax,QWORD PTR [rbx+0x40]
  b06164:	8b b3 00 01 00 00    	mov    esi,DWORD PTR [rbx+0x100]
  b0616a:	48 8b 80 20 19 00 00 	mov    rax,QWORD PTR [rax+0x1920]
  b06171:	f7 de                	neg    esi
  b06173:	48 8b 68 58          	mov    rbp,QWORD PTR [rax+0x58]
  b06177:	48 89 ef             	mov    rdi,rbp
  b0617a:	e8 f1 b8 d0 ff       	call   811a70 <CCharacter::giveGold(int)>
  b0617f:	48 8b 45 68          	mov    rax,QWORD PTR [rbp+0x68]
  b06183:	31 f6                	xor    esi,esi
  b06185:	8b 8b f8 00 00 00    	mov    ecx,DWORD PTR [rbx+0xf8]
  b0618b:	48 85 c0             	test   rax,rax
  b0618e:	74 04                	je     b06194 <CDieMenu::update(float)+0x84>
  b06190:	48 8b 70 18          	mov    rsi,QWORD PTR [rax+0x18]
  b06194:	f7 d9                	neg    ecx
  b06196:	45 31 c0             	xor    r8d,r8d
  b06199:	31 d2                	xor    edx,edx
  b0619b:	48 89 ef             	mov    rdi,rbp
  b0619e:	e8 1d 68 d3 ff       	call   83c9c0 <CCharacter::awardFame(CLevel&, CCharacter*, int, bool)>
  b061a3:	48 8b 45 68          	mov    rax,QWORD PTR [rbp+0x68]
  b061a7:	31 f6                	xor    esi,esi
  b061a9:	8b 8b fc 00 00 00    	mov    ecx,DWORD PTR [rbx+0xfc]
  b061af:	48 85 c0             	test   rax,rax
  b061b2:	74 04                	je     b061b8 <CDieMenu::update(float)+0xa8>
  b061b4:	48 8b 70 18          	mov    rsi,QWORD PTR [rax+0x18]
  b061b8:	48 89 ef             	mov    rdi,rbp
  b061bb:	31 d2                	xor    edx,edx
  b061bd:	f7 d9                	neg    ecx
  b061bf:	45 31 c0             	xor    r8d,r8d
  b061c2:	e8 89 c6 d1 ff       	call   822850 <CCharacter::awardExperience(CLevel&, CCharacter*, int, bool)>
  b061c7:	8b 93 c4 00 00 00    	mov    edx,DWORD PTR [rbx+0xc4]
  b061cd:	48 8b 43 40          	mov    rax,QWORD PTR [rbx+0x40]
  b061d1:	be 05 00 00 00       	mov    esi,0x5
  b061d6:	89 90 28 19 00 00    	mov    DWORD PTR [rax+0x1928],edx
  b061dc:	48 8b 7b 40          	mov    rdi,QWORD PTR [rbx+0x40]
  b061e0:	31 d2                	xor    edx,edx
  b061e2:	c6 83 c1 00 00 00 00 	mov    BYTE PTR [rbx+0xc1],0x0
  b061e9:	48 8b 6c 24 10       	mov    rbp,QWORD PTR [rsp+0x10]
  b061ee:	48 8b 5c 24 08       	mov    rbx,QWORD PTR [rsp+0x8]
  b061f3:	48 83 c4 18          	add    rsp,0x18
  b061f7:	e9 f4 c6 f7 ff       	jmp    a828f0 <CGameUI::requestSetGameState(EGameState, EMenu)>
  b061fc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  b06200:	c6 87 c0 00 00 00 00 	mov    BYTE PTR [rdi+0xc0],0x0
  b06207:	48 8b 7f 40          	mov    rdi,QWORD PTR [rdi+0x40]
  b0620b:	31 d2                	xor    edx,edx
  b0620d:	31 f6                	xor    esi,esi
  b0620f:	e8 dc c6 f7 ff       	call   a828f0 <CGameUI::requestSetGameState(EGameState, EMenu)>
  b06214:	e9 25 ff ff ff       	jmp    b0613e <CDieMenu::update(float)+0x2e>
  b06219:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]

