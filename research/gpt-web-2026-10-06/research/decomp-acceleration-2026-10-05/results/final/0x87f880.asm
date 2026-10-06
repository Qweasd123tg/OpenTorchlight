
/workspace/scratch/3ba0fff8d310/otl-recovery-1518/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000087f880 <_ZN10CEquipment13getMaxSocketsEv>:
  87f880:	mov    %rbx,-0x18(%rsp)
  87f885:	mov    %r12,-0x8(%rsp)
  87f88a:	xor    %r12d,%r12d
  87f88d:	mov    %rbp,-0x10(%rsp)
  87f892:	sub    $0x38,%rsp
  87f896:	cmpq   $0x0,0x1b0(%rdi)
  87f89e:	mov    %rdi,%rbx
  87f8a1:	je     87f900 <_ZN10CEquipment13getMaxSocketsEv+0x80>
  87f8a3:	lea    0x10(%rsp),%rbp
  87f8a8:	lea    0x1f(%rsp),%rdx
  87f8ad:	mov    $0xfcf518,%esi
  87f8b2:	mov    %rbp,%rdi
  87f8b5:	call   555e58 <_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_@plt>
  87f8ba:	mov    0x1b0(%rbx),%rdi
  87f8c1:	mov    $0x2,%edx
  87f8c6:	mov    %rbp,%rsi
  87f8c9:	mov    $0x1,%r12d
  87f8cf:	call   c5f310 <_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi>
  87f8d4:	mov    0x10(%rsp),%rdi
  87f8d9:	sub    $0x18,%rdi
  87f8dd:	cmp    $0x1424540,%rdi
  87f8e4:	jne    87f904 <_ZN10CEquipment13getMaxSocketsEv+0x84>
  87f8e6:	mov    0x20(%rsp),%rbx
  87f8eb:	mov    0x28(%rsp),%rbp
  87f8f0:	mov    0x30(%rsp),%r12
  87f8f5:	add    $0x38,%rsp
  87f8f9:	ret
  87f8fa:	nopw   0x0(%rax,%rax,1)
  87f900:	xor    %eax,%eax
  87f902:	jmp    87f8e6 <_ZN10CEquipment13getMaxSocketsEv+0x66>
  87f904:	mov    $0x5541c8,%edx
  87f909:	test   %rdx,%rdx
  87f90c:	je     87f946 <_ZN10CEquipment13getMaxSocketsEv+0xc6>
  87f90e:	or     $0xffffffff,%edx
  87f911:	lock xadd %edx,0x10(%rdi)
  87f916:	test   %edx,%edx
  87f918:	jg     87f8e6 <_ZN10CEquipment13getMaxSocketsEv+0x66>
  87f91a:	lea    0x1e(%rsp),%rsi
  87f91f:	mov    %eax,0x8(%rsp)
  87f923:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  87f928:	mov    0x8(%rsp),%eax
  87f92c:	jmp    87f8e6 <_ZN10CEquipment13getMaxSocketsEv+0x66>
  87f92e:	test   %r12b,%r12b
  87f931:	mov    %rax,%rbx
  87f934:	je     87f93e <_ZN10CEquipment13getMaxSocketsEv+0xbe>
  87f936:	mov    %rbp,%rdi
  87f939:	call   5548d8 <_ZNSbIwSt11char_traitsIwESaIwEED1Ev@plt>
  87f93e:	mov    %rbx,%rdi
  87f941:	call   554498 <_Unwind_Resume@plt>
  87f946:	mov    0x10(%rdi),%edx
  87f949:	lea    -0x1(%rdx),%ecx
  87f94c:	mov    %ecx,0x10(%rdi)
  87f94f:	jmp    87f916 <_ZN10CEquipment13getMaxSocketsEv+0x96>
