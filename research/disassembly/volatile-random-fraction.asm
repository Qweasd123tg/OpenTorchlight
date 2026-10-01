# Pinned ELF SHA256 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Full function body; rodata@0xfc8170 double1.0; process-global state@0x14ecaf8.

/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000c92b50 <UTILITIES::randomBetweenVolatile(float, float)>:
  c92b50:	ucomiss %xmm0,%xmm1
  c92b53:	jp     c92b5b <UTILITIES::randomBetweenVolatile(float, float)+0xb>
  c92b55:	je     c92be5 <UTILITIES::randomBetweenVolatile(float, float)+0x95>
  c92b5b:	mov    0x859f96(%rip),%rdx        # 14ecaf8 <g_RandVolatile>
  c92b62:	subss  %xmm0,%xmm1
  c92b66:	mov    %rdx,%rax
  c92b69:	shr    $0x20,%rdx
  c92b6d:	and    $0xffffffff,%eax
  c92b70:	unpcklps %xmm1,%xmm1
  c92b73:	imul   $0x29777b41,%rax,%rax
  c92b7a:	cvtps2pd %xmm1,%xmm1
  c92b7d:	lea    (%rax,%rdx,1),%rdx
  c92b81:	mov    %rdx,%rax
  c92b84:	mov    %rdx,%rcx
  c92b87:	shl    $0x20,%rdx
  c92b8b:	and    $0xffffffff,%eax
  c92b8e:	shr    $0x20,%rcx
  c92b92:	imul   $0x29777b41,%rax,%rax
  c92b99:	add    %rcx,%rax
  c92b9c:	mov    %rax,0x859f55(%rip)        # 14ecaf8 <g_RandVolatile>
  c92ba3:	mov    %eax,%eax
  c92ba5:	add    %rdx,%rax
  c92ba8:	movabs $0xfffffffffffff,%rdx
  c92bb2:	and    %rdx,%rax
  c92bb5:	movabs $0x3ff0000000000000,%rdx
  c92bbf:	or     %rdx,%rax
  c92bc2:	mov    %rax,-0x8(%rsp)
  c92bc7:	movsd  -0x8(%rsp),%xmm2
  c92bcd:	subsd  0x33559b(%rip),%xmm2        # fc8170 <typeinfo name for CTimelineProperty::CTimelinePoint+0x30>
  c92bd5:	mulsd  %xmm2,%xmm1
  c92bd9:	unpcklpd %xmm1,%xmm1
  c92bdd:	cvtpd2ps %xmm1,%xmm1
  c92be1:	addss  %xmm1,%xmm0
  c92be5:	repz ret
