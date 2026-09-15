00000000007f6ae0 <CBaseUnit::levelResetting()>:
  7f6ae0:	48 8b bf c8 01 00 00 	mov    rdi,QWORD PTR [rdi+0x1c8]
  7f6ae7:	48 85 ff             	test   rdi,rdi
  7f6aea:	74 14                	je     7f6b00 <CBaseUnit::levelResetting()+0x20>
  7f6aec:	31 c9                	xor    ecx,ecx
  7f6aee:	31 d2                	xor    edx,edx
  7f6af0:	be 01 00 00 00       	mov    esi,0x1
  7f6af5:	e9 c6 42 4d 00       	jmp    ccadc0 <CSkillManager::stopAllSkills(bool, bool, bool)>
  7f6afa:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  7f6b00:	f3 c3                	repz ret
  7f6b02:	66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	data16 data16 data16 data16 cs nop WORD PTR [rax+rax*1+0x0]

