
/mnt/data/original12/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000a7632d <_ZN11CSpawnClass17addSpawnClassDataEP10CDataGroupP15CSpawnClassData+0x22d>:
  a7632d:	8b 45 10             	mov    0x10(%rbp),%eax
  a76330:	ba ff ff ff ff       	mov    $0xffffffff,%edx
  a76335:	4c 8d 6c 24 40       	lea    0x40(%rsp),%r13
  a7633a:	be b0 3e fe 00       	mov    $0xfe3eb0,%esi
  a7633f:	4c 89 ef             	mov    %r13,%rdi
  a76342:	85 c0                	test   %eax,%eax
  a76344:	0f 44 c2             	cmove  %edx,%eax
  a76347:	48 8d 94 24 b9 00 00 	lea    0xb9(%rsp),%rdx
  a7634e:	00
  a7634f:	89 45 10             	mov    %eax,0x10(%rbp)
