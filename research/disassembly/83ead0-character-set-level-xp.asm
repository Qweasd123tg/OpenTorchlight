000000000083ecea <CCharacter::setLevel XP reward span>:
  83ecea:	0f 28 c8             	movaps xmm1,xmm0
  83eced:	f3 0f 5e 0d 47 5b 76 00 	divss  xmm1,DWORD PTR [rip+0x765b47]        # fa483c
  83ecf5:	f3 0f 59 c8          	mulss  xmm1,xmm0
  83ecf9:	f3 0f 2c c1          	cvttss2si eax,xmm1
