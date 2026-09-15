0000000000606a30 <CMissileDescriptor::Set_setFriction(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:
  606a30:	48 85 ff             	test   rdi,rdi
  606a33:	74 14                	je     606a49 <CMissileDescriptor::Set_setFriction(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)+0x19>
  606a35:	f3 0f 10 05 bf dd 99 00 	movss  xmm0,DWORD PTR [rip+0x99ddbf]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  606a3d:	f3 0f 5c 06          	subss  xmm0,DWORD PTR [rsi]
  606a41:	f3 0f 11 87 5c 01 00 00 	movss  DWORD PTR [rdi+0x15c],xmm0
  606a49:	f3 c3                	repz ret
  606a4b:	90                   	nop
  606a4c:	90                   	nop
  606a4d:	90                   	nop
  606a4e:	90                   	nop
  606a4f:	90                   	nop

