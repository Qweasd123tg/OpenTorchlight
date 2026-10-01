# Pinned ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Instruction-aligned window selected from the full loadCharacter body.
# Other writers/readers: full setCreationClass/applyCharacterState in menu-player-preview.asm.
  581de7:	mov    $0x1001608,%edi
  581dec:	call   554608 <wcslen@plt>
  581df1:	mov    0x10(%rsp),%rdi
  581df6:	mov    %rax,%rdx
  581df9:	mov    $0x1001608,%esi
  581dfe:	add    $0x1a8,%rdi
  581e05:	call   555968 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(wchar_t const*, unsigned long)@plt>
