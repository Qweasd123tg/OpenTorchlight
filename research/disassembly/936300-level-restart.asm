0000000000936300 <CLevel::restartLevel()>:
  936300:	53                   	push   rbx
  936301:	48 8b 87 98 00 00 00 	mov    rax,QWORD PTR [rdi+0x98]
  936308:	48 8b 18             	mov    rbx,QWORD PTR [rax]
  93630b:	48 85 db             	test   rbx,rbx
  93630e:	74 15                	je     936325 <CLevel::restartLevel()+0x25>
  936310:	48 8b 3b             	mov    rdi,QWORD PTR [rbx]
  936313:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  936316:	ff 90 f8 01 00 00    	call   QWORD PTR [rax+0x1f8]
  93631c:	48 8b 5b 08          	mov    rbx,QWORD PTR [rbx+0x8]
  936320:	48 85 db             	test   rbx,rbx
  936323:	75 eb                	jne    936310 <CLevel::restartLevel()+0x10>
  936325:	5b                   	pop    rbx
  936326:	c3                   	ret
  936327:	90                   	nop
  936328:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

