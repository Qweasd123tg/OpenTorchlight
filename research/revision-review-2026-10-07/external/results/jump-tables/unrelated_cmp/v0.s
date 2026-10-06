.text
.globl probe
.type probe,@function
probe:
 .cfi_startproc
 cmpl $1,%edi
 ja .Ldefault
 movl %edi,%edi
 cmpl $0,%esi
 sete %al
 movb %al,saved_flag(%rip)
 jmp *.Ltable(,%rdi,8)
.Lzero:
 movl $11,%eax
 ret
.Lone:
 movl $22,%eax
 ret
.Ltwo:
 movl $33,%eax
 ret
.Ldefault:
 movl $-1,%eax
 ret
 .cfi_endproc
.size probe,.-probe
.section .rodata
.p2align 3
.Ltable:
 .quad .Lzero
 .quad .Lone
.data
.globl saved_flag
.type saved_flag,@object
.size saved_flag,1
saved_flag: .byte 0
.section .note.GNU-stack,"",@progbits
