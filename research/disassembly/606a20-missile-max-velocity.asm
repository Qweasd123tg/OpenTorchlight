0000000000606a20 <CMissileDescriptor::Set_setMaxVelocity(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:
  606a20:	48 85 ff             	test   rdi,rdi
  606a23:	74 08                	je     606a2d <CMissileDescriptor::Set_setMaxVelocity(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)+0xd>
  606a25:	8b 06                	mov    eax,DWORD PTR [rsi]
  606a27:	89 87 58 01 00 00    	mov    DWORD PTR [rdi+0x158],eax
  606a2d:	f3 c3                	repz ret
  606a2f:	90                   	nop

