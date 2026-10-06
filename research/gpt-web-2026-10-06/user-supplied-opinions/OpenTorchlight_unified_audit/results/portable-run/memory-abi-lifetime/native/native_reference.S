.text
.att_syntax prefix
.globl ref_capture
.type ref_capture,@function
ref_capture:
.org ref_capture+0,0x90
.L_ref_capture_91a980:
    movzbl 0x711(%rdi),%eax
.org ref_capture+7,0x90
.L_ref_capture_91a987:
    mov    %rdi,%rdx
.org ref_capture+10,0x90
.L_ref_capture_91a98a:
    lea    0x718(%rdx),%rsi
.org ref_capture+17,0x90
.L_ref_capture_91a991:
    mov    %al,0x11(%rdi)
.org ref_capture+20,0x90
.L_ref_capture_91a994:
    movzwl 0x712(%rdi),%eax
.org ref_capture+27,0x90
.L_ref_capture_91a99b:
    mov    %ax,0x12(%rdi)
.org ref_capture+31,0x90
.L_ref_capture_91a99f:
    mov    0x714(%rdi),%eax
.org ref_capture+37,0x90
.L_ref_capture_91a9a5:
    mov    %eax,0x14(%rdi)
.org ref_capture+40,0x90
.L_ref_capture_91a9a8:
    mov    $0x3f,%eax
.org ref_capture+45,0x90
.L_ref_capture_91a9ad:
    lea    0x18(%rdi),%rdi
.org ref_capture+49,0x90
.L_ref_capture_91a9b1:
    mov    %rax,%rcx
.org ref_capture+52,0x90
.L_ref_capture_91a9b4:
    rep movsq (%rsi),(%rdi)
.org ref_capture+55,0x90
.L_ref_capture_91a9b7:
    mov    %rcx,%rax
.org ref_capture+58,0x90
.L_ref_capture_91a9ba:
    movzbl (%rsi),%ecx
.org ref_capture+61,0x90
.L_ref_capture_91a9bd:
    lea    0xb18(%rdx),%rsi
.org ref_capture+68,0x90
.L_ref_capture_91a9c4:
    mov    %cl,(%rdi)
.org ref_capture+70,0x90
.L_ref_capture_91a9c6:
    movzbl 0xb11(%rdx),%ecx
.org ref_capture+77,0x90
.L_ref_capture_91a9cd:
    lea    0x418(%rdx),%rdi
.org ref_capture+84,0x90
.L_ref_capture_91a9d4:
    mov    %cl,0x411(%rdx)
.org ref_capture+90,0x90
.L_ref_capture_91a9da:
    movzwl 0xb12(%rdx),%ecx
.org ref_capture+97,0x90
.L_ref_capture_91a9e1:
    mov    %cx,0x412(%rdx)
.org ref_capture+104,0x90
.L_ref_capture_91a9e8:
    mov    0xb14(%rdx),%ecx
.org ref_capture+110,0x90
.L_ref_capture_91a9ee:
    mov    %ecx,0x414(%rdx)
.org ref_capture+116,0x90
.L_ref_capture_91a9f4:
    mov    $0x3f,%ecx
.org ref_capture+121,0x90
.L_ref_capture_91a9f9:
    rep movsq (%rsi),(%rdi)
.org ref_capture+124,0x90
.L_ref_capture_91a9fc:
    movzbl (%rsi),%ecx
.org ref_capture+127,0x90
.L_ref_capture_91a9ff:
    lea    0x918(%rdx),%rsi
.org ref_capture+134,0x90
.L_ref_capture_91aa06:
    mov    %cl,(%rdi)
.org ref_capture+136,0x90
.L_ref_capture_91aa08:
    movzbl 0x911(%rdx),%ecx
.org ref_capture+143,0x90
.L_ref_capture_91aa0f:
    lea    0x218(%rdx),%rdi
.org ref_capture+150,0x90
.L_ref_capture_91aa16:
    mov    %cl,0x211(%rdx)
.org ref_capture+156,0x90
.L_ref_capture_91aa1c:
    movzwl 0x912(%rdx),%ecx
.org ref_capture+163,0x90
.L_ref_capture_91aa23:
    mov    %cx,0x212(%rdx)
.org ref_capture+170,0x90
.L_ref_capture_91aa2a:
    mov    0x914(%rdx),%ecx
.org ref_capture+176,0x90
.L_ref_capture_91aa30:
    mov    %ecx,0x214(%rdx)
.org ref_capture+182,0x90
.L_ref_capture_91aa36:
    mov    $0x3f,%ecx
.org ref_capture+187,0x90
.L_ref_capture_91aa3b:
    rep movsq (%rsi),(%rdi)
.org ref_capture+190,0x90
.L_ref_capture_91aa3e:
    movzbl (%rsi),%ecx
.org ref_capture+193,0x90
.L_ref_capture_91aa41:
    mov    %cl,(%rdi)
.org ref_capture+195,0x90
.L_ref_capture_91aa43:
    lea    0x718(%rdx),%rdi
.org ref_capture+202,0x90
.L_ref_capture_91aa4a:
    mov    $0x3f,%ecx
.org ref_capture+207,0x90
.L_ref_capture_91aa4f:
    movb   $0x0,0x711(%rdx)
.org ref_capture+214,0x90
.L_ref_capture_91aa56:
    movw   $0x0,0x712(%rdx)
.org ref_capture+223,0x90
.L_ref_capture_91aa5f:
    movl   $0x0,0x714(%rdx)
.org ref_capture+233,0x90
.L_ref_capture_91aa69:
    rep stos %rax,(%rdi)
.org ref_capture+236,0x90
.L_ref_capture_91aa6c:
    movb   $0x0,(%rdi)
.org ref_capture+239,0x90
.L_ref_capture_91aa6f:
    lea    0xb18(%rdx),%rdi
.org ref_capture+246,0x90
.L_ref_capture_91aa76:
    mov    $0x3f,%cl
.org ref_capture+248,0x90
.L_ref_capture_91aa78:
    movb   $0x0,0xb11(%rdx)
.org ref_capture+255,0x90
.L_ref_capture_91aa7f:
    movw   $0x0,0xb12(%rdx)
.org ref_capture+264,0x90
.L_ref_capture_91aa88:
    movl   $0x0,0xb14(%rdx)
.org ref_capture+274,0x90
.L_ref_capture_91aa92:
    rep stos %rax,(%rdi)
.org ref_capture+277,0x90
.L_ref_capture_91aa95:
    movb   $0x0,(%rdi)
.org ref_capture+280,0x90
.L_ref_capture_91aa98:
    ret
.size ref_capture,.-ref_capture
.att_syntax prefix

.text
.att_syntax prefix
.globl ref_keyheld
.type ref_keyheld,@function
ref_keyheld:
.org ref_keyheld+0,0x90
.L_ref_keyheld_91a680:
    mov    %esi,%esi
.org ref_keyheld+2,0x90
.L_ref_keyheld_91a682:
    mov    $0x1,%eax
.org ref_keyheld+7,0x90
.L_ref_keyheld_91a687:
    cmpb   $0x1,0x211(%rdi,%rsi,1)
.org ref_keyheld+15,0x90
.L_ref_keyheld_91a68f:
    je .L_ref_keyheld_91a699
.org ref_keyheld+17,0x90
.L_ref_keyheld_91a691:
    cmpb   $0x1,0x11(%rdi,%rsi,1)
.org ref_keyheld+22,0x90
.L_ref_keyheld_91a696:
    sete   %al
.org ref_keyheld+25,0x90
.L_ref_keyheld_91a699:
    repz ret
.size ref_keyheld,.-ref_keyheld
.att_syntax prefix

.text
.intel_syntax noprefix
.globl ref_getodds
.type ref_getodds,@function
ref_getodds:
.org ref_getodds+0,0x90
.L_ref_getodds_c8a210:
    cmp    esi,DWORD PTR [rdi+0x34]
.org ref_getodds+3,0x90
.L_ref_getodds_c8a213:
    jae .L_ref_getodds_c8a230
.org ref_getodds+5,0x90
.L_ref_getodds_c8a215:
    mov    esi,esi
.org ref_getodds+7,0x90
.L_ref_getodds_c8a217:
    shl    rsi,0x2
.org ref_getodds+11,0x90
.L_ref_getodds_c8a21b:
    add    rsi,QWORD PTR [rdi+0x28]
.org ref_getodds+15,0x90
.L_ref_getodds_c8a21f:
    movss  xmm0,DWORD PTR [rsi]
.org ref_getodds+19,0x90
.L_ref_getodds_c8a223:
    cvttss2si eax,xmm0
.org ref_getodds+23,0x90
.L_ref_getodds_c8a227:
    ret
.org ref_getodds+24,0x90
.L_ref_getodds_c8a228:
    nop    DWORD PTR [rax+rax*1+0x0]
.org ref_getodds+32,0x90
.L_ref_getodds_c8a230:
    mov    rsi,QWORD PTR [rdi+0x28]
.org ref_getodds+36,0x90
.L_ref_getodds_c8a234:
    movss  xmm0,DWORD PTR [rsi]
.org ref_getodds+40,0x90
.L_ref_getodds_c8a238:
    cvttss2si eax,xmm0
.org ref_getodds+44,0x90
.L_ref_getodds_c8a23c:
    ret
.size ref_getodds,.-ref_getodds
.att_syntax prefix

.text
.intel_syntax noprefix
.globl ref_setodds
.type ref_setodds,@function
ref_setodds:
.org ref_setodds+0,0x90
.L_ref_setodds_c8a240:
    mov    r9d,DWORD PTR [rdi+0x18]
.org ref_setodds+4,0x90
.L_ref_setodds_c8a244:
    test   r9d,r9d
.org ref_setodds+7,0x90
.L_ref_setodds_c8a247:
    je .L_ref_setodds_c8a298
.org ref_setodds+9,0x90
.L_ref_setodds_c8a249:
    mov    r10d,DWORD PTR [rdi+0x1c]
.org ref_setodds+13,0x90
.L_ref_setodds_c8a24d:
    xor    ecx,ecx
.org ref_setodds+15,0x90
.L_ref_setodds_c8a24f:
    xor    eax,eax
.org ref_setodds+17,0x90
.L_ref_setodds_c8a251:
    jmp .L_ref_setodds_c8a26d
.org ref_setodds+19,0x90
.L_ref_setodds_c8a253:
    nop    DWORD PTR [rax+rax*1+0x0]
.org ref_setodds+24,0x90
.L_ref_setodds_c8a258:
    mov    r8,QWORD PTR [rdi+0x10]
.org ref_setodds+28,0x90
.L_ref_setodds_c8a25c:
    cmp    DWORD PTR [r8],esi
.org ref_setodds+31,0x90
.L_ref_setodds_c8a25f:
    je .L_ref_setodds_c8a27e
.org ref_setodds+33,0x90
.L_ref_setodds_c8a261:
    add    eax,0x1
.org ref_setodds+36,0x90
.L_ref_setodds_c8a264:
    add    rcx,0x4
.org ref_setodds+40,0x90
.L_ref_setodds_c8a268:
    cmp    eax,r9d
.org ref_setodds+43,0x90
.L_ref_setodds_c8a26b:
    jae .L_ref_setodds_c8a298
.org ref_setodds+45,0x90
.L_ref_setodds_c8a26d:
    cmp    r10d,eax
.org ref_setodds+48,0x90
.L_ref_setodds_c8a270:
    jbe .L_ref_setodds_c8a258
.org ref_setodds+50,0x90
.L_ref_setodds_c8a272:
    mov    r8,rcx
.org ref_setodds+53,0x90
.L_ref_setodds_c8a275:
    add    r8,QWORD PTR [rdi+0x10]
.org ref_setodds+57,0x90
.L_ref_setodds_c8a279:
    cmp    DWORD PTR [r8],esi
.org ref_setodds+60,0x90
.L_ref_setodds_c8a27c:
    jne .L_ref_setodds_c8a261
.org ref_setodds+62,0x90
.L_ref_setodds_c8a27e:
    cmp    DWORD PTR [rdi+0x34],eax
.org ref_setodds+65,0x90
.L_ref_setodds_c8a281:
    ja .L_ref_setodds_c8a2a0
.org ref_setodds+67,0x90
.L_ref_setodds_c8a283:
    cvtsi2ss xmm0,edx
.org ref_setodds+71,0x90
.L_ref_setodds_c8a287:
    mov    rax,QWORD PTR [rdi+0x28]
.org ref_setodds+75,0x90
.L_ref_setodds_c8a28b:
    movss  DWORD PTR [rax],xmm0
.org ref_setodds+79,0x90
.L_ref_setodds_c8a28f:
    mov    BYTE PTR [rdi+0x60],0x1
.org ref_setodds+83,0x90
.L_ref_setodds_c8a293:
    ret
.org ref_setodds+84,0x90
.L_ref_setodds_c8a294:
    nop    DWORD PTR [rax+0x0]
.org ref_setodds+88,0x90
.L_ref_setodds_c8a298:
    repz ret
.org ref_setodds+90,0x90
.L_ref_setodds_c8a29a:
    nop    WORD PTR [rax+rax*1+0x0]
.org ref_setodds+96,0x90
.L_ref_setodds_c8a2a0:
    cvtsi2ss xmm0,edx
.org ref_setodds+100,0x90
.L_ref_setodds_c8a2a4:
    mov    eax,eax
.org ref_setodds+102,0x90
.L_ref_setodds_c8a2a6:
    shl    rax,0x2
.org ref_setodds+106,0x90
.L_ref_setodds_c8a2aa:
    add    rax,QWORD PTR [rdi+0x28]
.org ref_setodds+110,0x90
.L_ref_setodds_c8a2ae:
    movss  DWORD PTR [rax],xmm0
.org ref_setodds+114,0x90
.L_ref_setodds_c8a2b2:
    mov    BYTE PTR [rdi+0x60],0x1
.org ref_setodds+118,0x90
.L_ref_setodds_c8a2b6:
    ret
.size ref_setodds,.-ref_setodds
.att_syntax prefix

.text
.intel_syntax noprefix
.globl ref_removechoice
.type ref_removechoice,@function
ref_removechoice:
.org ref_removechoice+0,0x90
.L_ref_removechoice_c8a2c0:
    mov    r8d,DWORD PTR [rdi+0x18]
.org ref_removechoice+4,0x90
.L_ref_removechoice_c8a2c4:
    test   r8d,r8d
.org ref_removechoice+7,0x90
.L_ref_removechoice_c8a2c7:
    je .L_ref_removechoice_c8a360
.org ref_removechoice+13,0x90
.L_ref_removechoice_c8a2cd:
    mov    r9d,DWORD PTR [rdi+0x1c]
.org ref_removechoice+17,0x90
.L_ref_removechoice_c8a2d1:
    xor    edx,edx
.org ref_removechoice+19,0x90
.L_ref_removechoice_c8a2d3:
    xor    eax,eax
.org ref_removechoice+21,0x90
.L_ref_removechoice_c8a2d5:
    jmp .L_ref_removechoice_c8a2f4
.org ref_removechoice+23,0x90
.L_ref_removechoice_c8a2d7:
    nop    WORD PTR [rax+rax*1+0x0]
.org ref_removechoice+32,0x90
.L_ref_removechoice_c8a2e0:
    mov    rcx,QWORD PTR [rdi+0x10]
.org ref_removechoice+36,0x90
.L_ref_removechoice_c8a2e4:
    cmp    DWORD PTR [rcx],esi
.org ref_removechoice+38,0x90
.L_ref_removechoice_c8a2e6:
    je .L_ref_removechoice_c8a304
.org ref_removechoice+40,0x90
.L_ref_removechoice_c8a2e8:
    add    eax,0x1
.org ref_removechoice+43,0x90
.L_ref_removechoice_c8a2eb:
    add    rdx,0x4
.org ref_removechoice+47,0x90
.L_ref_removechoice_c8a2ef:
    cmp    eax,r8d
.org ref_removechoice+50,0x90
.L_ref_removechoice_c8a2f2:
    jae .L_ref_removechoice_c8a360
.org ref_removechoice+52,0x90
.L_ref_removechoice_c8a2f4:
    cmp    r9d,eax
.org ref_removechoice+55,0x90
.L_ref_removechoice_c8a2f7:
    jbe .L_ref_removechoice_c8a2e0
.org ref_removechoice+57,0x90
.L_ref_removechoice_c8a2f9:
    mov    rcx,rdx
.org ref_removechoice+60,0x90
.L_ref_removechoice_c8a2fc:
    add    rcx,QWORD PTR [rdi+0x10]
.org ref_removechoice+64,0x90
.L_ref_removechoice_c8a300:
    cmp    DWORD PTR [rcx],esi
.org ref_removechoice+66,0x90
.L_ref_removechoice_c8a302:
    jne .L_ref_removechoice_c8a2e8
.org ref_removechoice+68,0x90
.L_ref_removechoice_c8a304:
    mov    edx,DWORD PTR [rdi+0x30]
.org ref_removechoice+71,0x90
.L_ref_removechoice_c8a307:
    cmp    edx,eax
.org ref_removechoice+73,0x90
.L_ref_removechoice_c8a309:
    jbe .L_ref_removechoice_c8a323
.org ref_removechoice+75,0x90
.L_ref_removechoice_c8a30b:
    mov    rcx,QWORD PTR [rdi+0x28]
.org ref_removechoice+79,0x90
.L_ref_removechoice_c8a30f:
    sub    edx,0x1
.org ref_removechoice+82,0x90
.L_ref_removechoice_c8a312:
    mov    esi,eax
.org ref_removechoice+84,0x90
.L_ref_removechoice_c8a314:
    mov    DWORD PTR [rdi+0x30],edx
.org ref_removechoice+87,0x90
.L_ref_removechoice_c8a317:
    mov    edx,edx
.org ref_removechoice+89,0x90
.L_ref_removechoice_c8a319:
    mov    edx,DWORD PTR [rcx+rdx*4]
.org ref_removechoice+92,0x90
.L_ref_removechoice_c8a31c:
    mov    DWORD PTR [rcx+rsi*4],edx
.org ref_removechoice+95,0x90
.L_ref_removechoice_c8a31f:
    mov    r8d,DWORD PTR [rdi+0x18]
.org ref_removechoice+99,0x90
.L_ref_removechoice_c8a323:
    cmp    eax,r8d
.org ref_removechoice+102,0x90
.L_ref_removechoice_c8a326:
    jae .L_ref_removechoice_c8a340
.org ref_removechoice+104,0x90
.L_ref_removechoice_c8a328:
    mov    rdx,QWORD PTR [rdi+0x10]
.org ref_removechoice+108,0x90
.L_ref_removechoice_c8a32c:
    sub    r8d,0x1
.org ref_removechoice+112,0x90
.L_ref_removechoice_c8a330:
    mov    ecx,eax
.org ref_removechoice+114,0x90
.L_ref_removechoice_c8a332:
    mov    DWORD PTR [rdi+0x18],r8d
.org ref_removechoice+118,0x90
.L_ref_removechoice_c8a336:
    mov    r8d,r8d
.org ref_removechoice+121,0x90
.L_ref_removechoice_c8a339:
    mov    esi,DWORD PTR [rdx+r8*4]
.org ref_removechoice+125,0x90
.L_ref_removechoice_c8a33d:
    mov    DWORD PTR [rdx+rcx*4],esi
.org ref_removechoice+128,0x90
.L_ref_removechoice_c8a340:
    mov    edx,DWORD PTR [rdi+0x48]
.org ref_removechoice+131,0x90
.L_ref_removechoice_c8a343:
    cmp    edx,eax
.org ref_removechoice+133,0x90
.L_ref_removechoice_c8a345:
    jbe .L_ref_removechoice_c8a35b
.org ref_removechoice+135,0x90
.L_ref_removechoice_c8a347:
    mov    rcx,QWORD PTR [rdi+0x40]
.org ref_removechoice+139,0x90
.L_ref_removechoice_c8a34b:
    sub    edx,0x1
.org ref_removechoice+142,0x90
.L_ref_removechoice_c8a34e:
    mov    eax,eax
.org ref_removechoice+144,0x90
.L_ref_removechoice_c8a350:
    mov    DWORD PTR [rdi+0x48],edx
.org ref_removechoice+147,0x90
.L_ref_removechoice_c8a353:
    mov    edx,edx
.org ref_removechoice+149,0x90
.L_ref_removechoice_c8a355:
    mov    edx,DWORD PTR [rcx+rdx*4]
.org ref_removechoice+152,0x90
.L_ref_removechoice_c8a358:
    mov    DWORD PTR [rcx+rax*4],edx
.org ref_removechoice+155,0x90
.L_ref_removechoice_c8a35b:
    mov    BYTE PTR [rdi+0x60],0x1
.org ref_removechoice+159,0x90
.L_ref_removechoice_c8a35f:
    ret
.org ref_removechoice+160,0x90
.L_ref_removechoice_c8a360:
    repz ret
.size ref_removechoice,.-ref_removechoice
.att_syntax prefix

.section .note.GNU-stack,"",@progbits
