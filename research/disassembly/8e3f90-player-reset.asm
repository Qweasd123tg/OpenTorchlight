00000000008e3f90 <CPlayer::resetLevel()>:
  8e3f90:	53                   	push   rbx
  8e3f91:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  8e3f94:	48 89 fb             	mov    rbx,rdi
  8e3f97:	c7 87 00 01 00 00 01 00 00 00 	mov    DWORD PTR [rdi+0x100],0x1
  8e3fa1:	c7 87 48 04 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0x448],0x0
  8e3fab:	c7 87 4c 04 00 00 00 00 00 00 	mov    DWORD PTR [rdi+0x44c],0x0
  8e3fb5:	ff 90 18 04 00 00    	call   QWORD PTR [rax+0x418]
  8e3fbb:	f3 0f 2a 83 18 04 00 00 	cvtsi2ss xmm0,DWORD PTR [rbx+0x418]
  8e3fc3:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8e3fc6:	f3 0f 11 83 14 04 00 00 	movss  DWORD PTR [rbx+0x414],xmm0
  8e3fce:	48 89 df             	mov    rdi,rbx
  8e3fd1:	ff 90 10 04 00 00    	call   QWORD PTR [rax+0x410]
  8e3fd7:	f3 0f 2a 83 3c 04 00 00 	cvtsi2ss xmm0,DWORD PTR [rbx+0x43c]
  8e3fdf:	f3 0f 11 83 38 04 00 00 	movss  DWORD PTR [rbx+0x438],xmm0
  8e3fe7:	5b                   	pop    rbx
  8e3fe8:	c3                   	ret
  8e3fe9:	90                   	nop
  8e3fea:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

