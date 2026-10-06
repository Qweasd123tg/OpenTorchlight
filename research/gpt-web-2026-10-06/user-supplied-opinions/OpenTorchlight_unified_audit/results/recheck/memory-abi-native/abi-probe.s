	.file	"abi_probe.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.p2align 4
	.globl	get_v3
	.type	get_v3, @function
get_v3:
.LFB3230:
	.cfi_startproc
	movl	8(%rdi), %eax
	movq	(%rdi), %xmm0
	movl	%eax, -12(%rsp)
	movss	-12(%rsp), %xmm1
	ret
	.cfi_endproc
.LFE3230:
	.size	get_v3, .-get_v3
	.p2align 4
	.globl	get_quat
	.type	get_quat, @function
get_quat:
.LFB3231:
	.cfi_startproc
	movq	8(%rdi), %xmm1
	movq	(%rdi), %xmm0
	ret
	.cfi_endproc
.LFE3231:
	.size	get_quat, .-get_quat
	.p2align 4
	.globl	get_mixed
	.type	get_mixed, @function
get_mixed:
.LFB3232:
	.cfi_startproc
	movsd	8(%rdi), %xmm0
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE3232:
	.size	get_mixed, .-get_mixed
	.p2align 4
	.globl	get_big
	.type	get_big, @function
get_big:
.LFB3233:
	.cfi_startproc
	movdqu	(%rsi), %xmm0
	movq	16(%rsi), %rdx
	movq	%rdi, %rax
	movq	%rdx, 16(%rdi)
	movups	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE3233:
	.size	get_big, .-get_big
	.p2align 4
	.globl	get_small
	.type	get_small, @function
get_small:
.LFB3234:
	.cfi_startproc
	movq	(%rsi), %rdx
	movq	%rdi, %rax
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE3234:
	.size	get_small, .-get_small
	.align 2
	.p2align 4
	.type	_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0, @function
_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0:
.LFB3331:
	.cfi_startproc
	leaq	-24(%rdi), %rax
	leaq	_ZNSbIwSt11char_traitsIwESaIwEE4_Rep20_S_empty_rep_storageE(%rip), %rdx
	cmpq	%rdx, %rax
	jne	.L17
.L14:
	ret
.L17:
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L10
	movl	-8(%rdi), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, -8(%rdi)
.L11:
	testl	%edx, %edx
	jg	.L14
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rax, %rdi
	leaq	15(%rsp), %rsi
	call	_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
.L10:
	orl	$-1, %edx
	lock xaddl	%edx, -8(%rdi)
	jmp	.L11
	.cfi_endproc
.LFE3331:
	.size	_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0, .-_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0
	.p2align 4
	.globl	get_text
	.type	get_text, @function
get_text:
.LFB3235:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rsi), %rax
	movl	-8(%rax), %edx
	leaq	-24(%rax), %rdi
	testl	%edx, %edx
	js	.L19
	leaq	_ZNSbIwSt11char_traitsIwESaIwEE4_Rep20_S_empty_rep_storageE(%rip), %rdx
	cmpq	%rdx, %rdi
	jne	.L24
.L22:
	movq	%rax, (%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L19:
	.cfi_restore_state
	leaq	15(%rsp), %rsi
	xorl	%edx, %edx
	call	_ZNSbIwSt11char_traitsIwESaIwEE4_Rep8_M_cloneERKS1_m@PLT
	movq	%rax, (%rbx)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L24:
	.cfi_restore_state
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L21
	addl	$1, -8(%rax)
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L21:
	leaq	-8(%rax), %rcx
	lock addl	$1, (%rcx)
	jmp	.L22
	.cfi_endproc
.LFE3235:
	.size	get_text, .-get_text
	.p2align 4
	.globl	take_v3
	.type	take_v3, @function
take_v3:
.LFB3236:
	.cfi_startproc
	movq	%xmm0, -16(%rsp)
	movss	-16(%rsp), %xmm0
	movq	%rdi, argument_integer(%rip)
	movq	%rsi, 8+argument_integer(%rip)
	movss	%xmm0, argument_float(%rip)
	movss	-12(%rsp), %xmm0
	movss	%xmm0, 4+argument_float(%rip)
	movss	%xmm1, 8+argument_float(%rip)
	ret
	.cfi_endproc
.LFE3236:
	.size	take_v3, .-take_v3
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"true"
.LC1:
	.string	"false"
	.section	.rodata.str4.4,"aMS",@progbits,4
	.align 4
.LC8:
	.string	"A"
	.string	""
	.string	""
	.string	"B"
	.string	""
	.string	""
	.string	"I"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC9:
	.string	"{\"scope\":\"six synthetic return probes; real archive Ogre headers; system compiler\",\"types\":["
	.align 8
.LC10:
	.string	"{\"name\":\"Ogre::Vector3\",\"size\":%lu,\"observed\":\"XMM0 low 64 + XMM1 low 32\",\"pass\":%s},"
	.align 8
.LC11:
	.string	"{\"name\":\"Ogre::Quaternion\",\"size\":%lu,\"observed\":\"XMM0 low 64 + XMM1 low 64\",\"pass\":%s},"
	.align 8
.LC12:
	.string	"{\"name\":\"Mixed\",\"size\":%lu,\"observed\":\"RAX + XMM0 low 64\",\"pass\":%s},"
	.align 8
.LC13:
	.string	"{\"name\":\"Big\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s},"
	.align 8
.LC14:
	.string	"{\"name\":\"Small nontrivial\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s},"
	.align 8
.LC15:
	.string	"{\"name\":\"old ABI std::wstring\",\"size\":%lu,\"observed\":\"hidden RDI result, source RSI, result pointer RAX\",\"pass\":%s}],\"failures\":%d}\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB16:
	.section	.text.startup,"ax",@progbits
.LHOTB16:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB3238:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3238
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	leaq	get_v3(%rip), %rdi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$504, %rsp
	.cfi_def_cfa_offset 560
	movq	.LC2(%rip), %rax
	leaq	32(%rsp), %rsi
	movl	$0x40d80000, 40(%rsp)
	movq	%rax, 32(%rsp)
.LEHB0:
	call	capture_return@PLT
	movq	32(%rsp), %rax
	cmpq	%rax, 16+capture(%rip)
	jne	.L27
	movl	40(%rsp), %eax
	cmpl	%eax, 32+capture(%rip)
	sete	%r13b
.L27:
	movaps	.LC4(%rip), %xmm0
	movl	%r13d, %ebx
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	xorl	$1, %ebx
	leaq	48(%rsp), %rsi
	leaq	get_quat(%rip), %rdi
	xorl	%r12d, %r12d
	movaps	%xmm0, 48(%rsp)
	movzbl	%bl, %ebx
	call	capture_return@PLT
	movq	16+capture(%rip), %rax
	cmpq	%rax, 48(%rsp)
	jne	.L28
	movq	32+capture(%rip), %rax
	cmpq	%rax, 56(%rsp)
	sete	%r12b
.L28:
	cmpb	$1, %r12b
	leaq	64(%rsp), %rsi
	movabsq	$1311768467463790320, %rax
	movq	%rax, 64(%rsp)
	movq	.LC5(%rip), %rax
	adcl	$0, %ebx
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	leaq	get_mixed(%rip), %rdi
	xorl	%ebp, %ebp
	movq	%rax, 72(%rsp)
	call	capture_return@PLT
	movq	capture(%rip), %rax
	cmpq	%rax, 64(%rsp)
	jne	.L29
	movq	16+capture(%rip), %rax
	cmpq	%rax, 72(%rsp)
	sete	%bpl
.L29:
	movq	.LC7(%rip), %rax
	movapd	.LC6(%rip), %xmm0
	leaq	112(%rsp), %r14
	cmpb	$1, %bpl
	movq	%r14, %rdx
	leaq	80(%rsp), %rsi
	movl	$1, %ecx
	adcl	$0, %ebx
	leaq	get_big(%rip), %rdi
	movq	%rax, 96(%rsp)
	movaps	%xmm0, 80(%rsp)
	call	capture_return@PLT
	movq	112(%rsp), %rax
	movq	120(%rsp), %rdx
	xorq	80(%rsp), %rax
	xorq	88(%rsp), %rdx
	orq	%rdx, %rax
	je	.L64
.L30:
	movb	$0, 3(%rsp)
.L32:
	cmpb	$1, 3(%rsp)
	leaq	16(%rsp), %rsi
	leaq	240(%rsp), %r14
	movabsq	$1311768467463790320, %rax
	movl	$1, %ecx
	movq	%r14, %rdx
	movq	%rax, 16(%rsp)
	adcl	$0, %ebx
	leaq	get_small(%rip), %rdi
	xorl	%r15d, %r15d
	call	capture_return@PLT
	movq	16(%rsp), %rax
	cmpq	%rax, 240(%rsp)
	jne	.L33
	cmpq	%r14, capture(%rip)
	sete	%r15b
.L33:
	cmpb	$1, %r15b
	leaq	368(%rsp), %r14
	leaq	.LC8(%rip), %rsi
	adcl	$0, %ebx
	movq	%r14, %rdx
	movl	%ebx, 4(%rsp)
	leaq	24(%rsp), %rbx
	movq	%rbx, %rdi
	call	_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@PLT
.LEHE0:
	movl	$1, %ecx
	movq	%r14, %rdx
	movq	%rbx, %rsi
	leaq	get_text(%rip), %rdi
.LEHB1:
	call	capture_return@PLT
	movq	368(%rsp), %rdi
	movq	24(%rsp), %rsi
	xorl	%ebx, %ebx
	movq	-24(%rdi), %rdx
	cmpq	-24(%rsi), %rdx
	je	.L65
.L34:
	movl	4(%rsp), %r14d
	cmpb	$1, %bl
	adcl	$0, %r14d
	call	_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0
	leaq	.LC9(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	testb	%r13b, %r13b
	leaq	.LC0(%rip), %rax
	leaq	.LC1(%rip), %rdx
	movl	$12, %esi
	cmovne	%rax, %rdx
	leaq	.LC10(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	testb	%r12b, %r12b
	leaq	.LC0(%rip), %rax
	leaq	.LC1(%rip), %rdx
	movl	$16, %esi
	cmovne	%rax, %rdx
	leaq	.LC11(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	testb	%bpl, %bpl
	leaq	.LC0(%rip), %rax
	leaq	.LC1(%rip), %rdx
	movl	$16, %esi
	cmovne	%rax, %rdx
	leaq	.LC12(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	cmpb	$0, 3(%rsp)
	leaq	.LC0(%rip), %rax
	leaq	.LC1(%rip), %rdx
	movl	$24, %esi
	cmovne	%rax, %rdx
	leaq	.LC13(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	testb	%r15b, %r15b
	leaq	.LC0(%rip), %rax
	leaq	.LC1(%rip), %rdx
	movl	$8, %esi
	cmovne	%rax, %rdx
	leaq	.LC14(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
	testb	%bl, %bl
	leaq	.LC0(%rip), %rax
	movl	%r14d, %ecx
	movl	$8, %esi
	leaq	.LC1(%rip), %rdx
	leaq	.LC15(%rip), %rdi
	cmovne	%rax, %rdx
	xorl	%eax, %eax
	call	printf@PLT
.LEHE1:
	movq	24(%rsp), %rdi
	call	_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0
	xorl	%eax, %eax
	testl	%r14d, %r14d
	setne	%al
	addq	$504, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L64:
	.cfi_restore_state
	movq	96(%rsp), %rax
	cmpq	%rax, 128(%rsp)
	jne	.L30
	cmpq	%r14, capture(%rip)
	sete	3(%rsp)
	jmp	.L32
.L65:
	testq	%rdx, %rdx
	je	.L35
	movq	%rdi, 8(%rsp)
	call	wmemcmp@PLT
	movq	8(%rsp), %rdi
	testl	%eax, %eax
	jne	.L34
.L35:
	cmpq	%r14, capture(%rip)
	sete	%bl
	jmp	.L34
.L56:
	movq	%rax, %rbx
	jmp	.L42
	.section	.gcc_except_table,"a",@progbits
.LLSDA3238:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3238-.LLSDACSB3238
.LLSDACSB3238:
	.uleb128 .LEHB0-.LFB3238
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB3238
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L56-.LFB3238
	.uleb128 0
.LLSDACSE3238:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC3238
	.type	main.cold, @function
main.cold:
.LFSB3238:
.L42:
	.cfi_def_cfa_offset 560
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	24(%rsp), %rdi
	call	_ZNSbIwSt11char_traitsIwESaIwEED2Ev.isra.0
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE3238:
	.section	.gcc_except_table
.LLSDAC3238:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC3238-.LLSDACSBC3238
.LLSDACSBC3238:
	.uleb128 .LEHB2-.LCOLDB16
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSEC3238:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE16:
	.section	.text.startup
.LHOTE16:
	.globl	argument_integer
	.bss
	.align 16
	.type	argument_integer, @object
	.size	argument_integer, 16
argument_integer:
	.zero	16
	.globl	argument_float
	.align 16
	.type	argument_float, @object
	.size	argument_float, 16
argument_float:
	.zero	16
	.globl	capture
	.align 32
	.type	capture, @object
	.size	capture, 64
capture:
	.zero	64
	.set	.LC2,.LC4
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC4:
	.long	1067450368
	.long	-1071644672
	.long	1087897600
	.long	1090519040
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC5:
	.long	0
	.long	-1071841280
	.section	.rodata.cst16
	.align 16
.LC6:
	.long	0
	.long	1072955392
	.long	0
	.long	-1073479680
	.section	.rodata.cst8
	.align 8
.LC7:
	.long	0
	.long	1075511296
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.globl	__gxx_personality_v0
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
