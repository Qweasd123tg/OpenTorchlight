# Targeted export from user-provided OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm.
# Recorded ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
# ELF not present; text-export provenance is not independently verified.
00000000008996e0 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)>:
  8996e0:	48 89 5c 24 d0       	mov    QWORD PTR [rsp-0x30],rbx
  8996e5:	48 89 6c 24 d8       	mov    QWORD PTR [rsp-0x28],rbp
  8996ea:	48 89 fb             	mov    rbx,rdi
  8996ed:	4c 89 64 24 e0       	mov    QWORD PTR [rsp-0x20],r12
  8996f2:	4c 89 6c 24 e8       	mov    QWORD PTR [rsp-0x18],r13
  8996f7:	45 89 cc             	mov    r12d,r9d
  8996fa:	4c 89 74 24 f0       	mov    QWORD PTR [rsp-0x10],r14
  8996ff:	4c 89 7c 24 f8       	mov    QWORD PTR [rsp-0x8],r15
  899704:	48 83 ec 48          	sub    rsp,0x48
  899708:	49 89 f6             	mov    r14,rsi
  89970b:	f3 0f 11 44 24 04    	movss  DWORD PTR [rsp+0x4],xmm0
  899711:	41 89 cf             	mov    r15d,ecx
  899714:	f3 0f 11 4c 24 08    	movss  DWORD PTR [rsp+0x8],xmm1
  89971a:	45 89 c5             	mov    r13d,r8d
  89971d:	89 d5                	mov    ebp,edx
  89971f:	f3 0f 11 54 24 0c    	movss  DWORD PTR [rsp+0xc],xmm2
  899725:	e8 96 ff 4d 00       	call   d796c0 <CRunicCore::CRunicCore()>
  89972a:	48 8d 7b 10          	lea    rdi,[rbx+0x10]
  89972e:	48 c7 03 90 e3 fc 00 	mov    QWORD PTR [rbx],0xfce390
  899735:	4c 89 f6             	mov    rsi,r14
  899738:	e8 6b 92 cb ff       	call   5529a8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(std::string const&)@plt>
  89973d:	f3 0f 10 44 24 04    	movss  xmm0,DWORD PTR [rsp+0x4]
  899743:	40 88 6b 18          	mov    BYTE PTR [rbx+0x18],bpl
  899747:	f3 0f 11 43 68       	movss  DWORD PTR [rbx+0x68],xmm0
  89974c:	c7 43 5c 00 00 00 00 	mov    DWORD PTR [rbx+0x5c],0x0
  899753:	c7 43 60 00 00 00 00 	mov    DWORD PTR [rbx+0x60],0x0
  89975a:	f3 0f 10 44 24 08    	movss  xmm0,DWORD PTR [rsp+0x8]
  899760:	c7 43 64 00 00 00 00 	mov    DWORD PTR [rbx+0x64],0x0
  899767:	f3 0f 11 43 6c       	movss  DWORD PTR [rbx+0x6c],xmm0
  89976c:	44 89 63 74          	mov    DWORD PTR [rbx+0x74],r12d
  899770:	31 c0                	xor    eax,eax
  899772:	f3 0f 10 44 24 0c    	movss  xmm0,DWORD PTR [rsp+0xc]
  899778:	c7 43 78 00 00 00 00 	mov    DWORD PTR [rbx+0x78],0x0
  89977f:	f3 0f 11 43 70       	movss  DWORD PTR [rbx+0x70],xmm0
  899784:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  899788:	c7 44 03 24 00 00 00 00 	mov    DWORD PTR [rbx+rax*1+0x24],0x0
  899790:	c7 44 03 40 00 00 00 00 	mov    DWORD PTR [rbx+rax*1+0x40],0x0
  899798:	48 83 c0 04          	add    rax,0x4
  89979c:	48 83 f8 1c          	cmp    rax,0x1c
  8997a0:	75 e6                	jne    899788 <CAttackDescription::CAttackDescription(std::string const&, bool, float, float, unsigned int, unsigned int, int, float)+0xa8>
  8997a2:	44 89 6b 24          	mov    DWORD PTR [rbx+0x24],r13d
  8997a6:	44 89 7b 40          	mov    DWORD PTR [rbx+0x40],r15d
  8997aa:	48 8b 6c 24 20       	mov    rbp,QWORD PTR [rsp+0x20]
  8997af:	48 8b 5c 24 18       	mov    rbx,QWORD PTR [rsp+0x18]
  8997b4:	4c 8b 64 24 28       	mov    r12,QWORD PTR [rsp+0x28]
  8997b9:	4c 8b 6c 24 30       	mov    r13,QWORD PTR [rsp+0x30]
  8997be:	4c 8b 74 24 38       	mov    r14,QWORD PTR [rsp+0x38]
  8997c3:	4c 8b 7c 24 40       	mov    r15,QWORD PTR [rsp+0x40]
  8997c8:	48 83 c4 48          	add    rsp,0x48
  8997cc:	c3                   	ret
  8997cd:	48 89 c5             	mov    rbp,rax
  8997d0:	48 89 df             	mov    rdi,rbx
  8997d3:	e8 48 01 4e 00       	call   d79920 <CRunicCore::~CRunicCore()>
  8997d8:	48 89 ef             	mov    rdi,rbp
  8997db:	e8 b8 ac cb ff       	call   554498 <_Unwind_Resume@plt>

