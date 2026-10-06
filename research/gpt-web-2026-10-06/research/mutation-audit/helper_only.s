	.file	"helper_only.cpp"
	.text
	.p2align 4
	.globl	_Z6helperi
	.type	_Z6helperi, @function
_Z6helperi:
.LFB14:
	.cfi_startproc
	leal	20(%rdi), %eax
	ret
	.cfi_endproc
.LFE14:
	.size	_Z6helperi, .-_Z6helperi
	.p2align 4
	.globl	_Z6calleri
	.type	_Z6calleri, @function
_Z6calleri:
.LFB15:
	.cfi_startproc
	testl	%edi, %edi
	je	.L4
	jmp	*dispatch(%rip)
	.p2align 4,,10
	.p2align 3
.L4:
	movl	$7, %eax
	ret
	.cfi_endproc
.LFE15:
	.size	_Z6calleri, .-_Z6calleri
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB16:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$1, %edi
	call	_Z6helperi
	movl	%eax, %ebx
	call	_Z6calleri
	movl	%ebx, %edx
	leaq	.LC0(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
	call	printf@PLT
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.globl	dispatch
	.section	.data.rel.local,"aw"
	.align 8
	.type	dispatch, @object
	.size	dispatch, 8
dispatch:
	.quad	_Z6helperi
	.ident	"GCC: (Debian 14.2.0-19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
