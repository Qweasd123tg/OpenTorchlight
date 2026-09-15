# Original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address-scoped excerpt of the user-supplied archive (2),
# original-analysis/full-intel-disassembly.asm; not a fresh ELF export.

# Range [0x95f150, 0x95f177)
  95f150:	41 57                	push   r15
  95f152:	41 56                	push   r14
  95f154:	41 55                	push   r13
  95f156:	41 54                	push   r12
  95f158:	55                   	push   rbp
  95f159:	53                   	push   rbx
  95f15a:	48 89 fb             	mov    rbx,rdi
  95f15d:	48 81 ec 88 03 00 00 	sub    rsp,0x388
  95f164:	48 89 74 24 40       	mov    QWORD PTR [rsp+0x40],rsi
  95f169:	89 4c 24 4c          	mov    DWORD PTR [rsp+0x4c],ecx
  95f16d:	4c 89 44 24 50       	mov    QWORD PTR [rsp+0x50],r8
  95f172:	4c 89 4c 24 68       	mov    QWORD PTR [rsp+0x68],r9
