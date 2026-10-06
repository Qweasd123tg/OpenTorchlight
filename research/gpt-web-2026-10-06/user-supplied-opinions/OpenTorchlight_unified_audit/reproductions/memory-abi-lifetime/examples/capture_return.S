.text
.globl capture_return
.type capture_return,@function
capture_return:
    pushq %rbx
    movq %rdi,%r11
    testl %ecx,%ecx
    jnz .Lhidden
    movq %rsi,%rdi
    jmp .Lcall
.Lhidden:
    movq %rdx,%rdi
.Lcall:
    call *%r11
    movq %rax,capture(%rip)
    movq %rdx,capture+8(%rip)
    movdqu %xmm0,capture+16(%rip)
    movdqu %xmm1,capture+32(%rip)
    popq %rbx
    ret
.size capture_return,.-capture_return
.section .note.GNU-stack,"",@progbits
