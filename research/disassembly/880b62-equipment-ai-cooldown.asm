# Source: earlier supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Declared original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Verified source text SHA-256: 59d876125b21e8e1a3e6b0f2f242632966b705218907de1ed5172baebc30d196
# Targeted Intel-syntax excerpt; the ELF is not included. See ../monster-ai-cooldown.md.

# Range: 0x880b62 <= instruction address < 0x880bae
  880b62:	4c 8d a4 24 00 02 00 00 	lea    r12,[rsp+0x200]
  880b6a:	48 8d 94 24 b9 02 00 00 	lea    rdx,[rsp+0x2b9]
  880b72:	be a0 f8 fc 00       	mov    esi,0xfcf8a0
  880b77:	4c 89 e7             	mov    rdi,r12
  880b7a:	e8 d9 52 cd ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  880b7f:	48 8b bb b0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b0]
  880b86:	0f 57 c0             	xorps  xmm0,xmm0
  880b89:	4c 89 e6             	mov    rsi,r12
  880b8c:	e8 ef e6 3d 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  880b91:	f3 0f 11 83 08 04 00 00 	movss  DWORD PTR [rbx+0x408],xmm0
  880b99:	48 8b bc 24 00 02 00 00 	mov    rdi,QWORD PTR [rsp+0x200]
  880ba1:	48 83 ef 18          	sub    rdi,0x18
  880ba5:	48 39 fd             	cmp    rbp,rdi
  880ba8:	0f 85 2c 14 00 00    	jne    881fda <CEquipment::calculateCombatStats(bool)+0x168a>
