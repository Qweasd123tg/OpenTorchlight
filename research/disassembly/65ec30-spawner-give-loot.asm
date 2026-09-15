000000000065ec30 <CUnitSpawnerDescriptor::Set_setUnitsGiveLoot(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:
  65ec30:	48 85 ff             	test   rdi,rdi
  65ec33:	74 09                	je     65ec3e <CUnitSpawnerDescriptor::Set_setUnitsGiveLoot(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)+0xe>
  65ec35:	0f b6 06             	movzx  eax,BYTE PTR [rsi]
  65ec38:	88 87 79 01 00 00    	mov    BYTE PTR [rdi+0x179],al
  65ec3e:	f3 c3                	repz ret

