
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     формат файла elf64-x86-64


Дизассемблирование раздела .text:

0000000000b4f570 <_ZN14CInventoryMenu7onClickE15ELayoutFunction>:
  b4f570:	push   %rbp
  b4f571:	push   %rbx
  b4f572:	mov    %rdi,%rbx
  b4f575:	sub    $0x218,%rsp
  b4f57c:	cmpb   $0x0,0x60(%rdi)
  b4f580:	je     b4f599 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x29>
  b4f582:	cmp    $0xf,%esi
  b4f585:	je     b4f5b0 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x40>
  b4f587:	cmp    $0x10,%esi
  b4f58a:	je     b4f858 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x2e8>
  b4f590:	cmp    $0xe,%esi
  b4f593:	je     b4f710 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x1a0>
  b4f599:	add    $0x218,%rsp
  b4f5a0:	mov    $0x1,%eax
  b4f5a5:	pop    %rbx
  b4f5a6:	pop    %rbp
  b4f5a7:	ret
  b4f5a8:	nopl   0x0(%rax,%rax,1)
  b4f5b0:	mov    0x9120(%rdi),%rdi
  b4f5b7:	xor    %esi,%esi
  b4f5b9:	lea    0xb0(%rsp),%rbp
  b4f5c1:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f5c6:	mov    0x9128(%rbx),%rdi
  b4f5cd:	mov    $0x1,%esi
  b4f5d2:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f5d7:	mov    0x9130(%rbx),%rdi
  b4f5de:	xor    %esi,%esi
  b4f5e0:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f5e5:	mov    0x9108(%rbx),%rdi
  b4f5ec:	xor    %esi,%esi
  b4f5ee:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f5f3:	mov    0x9110(%rbx),%rdi
  b4f5fa:	mov    $0x1,%esi
  b4f5ff:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f604:	mov    0x9118(%rbx),%rdi
  b4f60b:	xor    %esi,%esi
  b4f60d:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f612:	movb   $0x0,0x91a9(%rbx)
  b4f619:	mov    $0xf,%esi
  b4f61e:	mov    %rbp,%rdi
  b4f621:	movq   $0x20,0xb8(%rsp)
  b4f62d:	movq   $0x0,0xc0(%rsp)
  b4f639:	movq   $0x0,0xd0(%rsp)
  b4f645:	movq   $0x0,0xc8(%rsp)
  b4f651:	movq   $0x0,0x158(%rsp)
  b4f65d:	movq   $0x0,0xb0(%rsp)
  b4f669:	movl   $0x0,0xd8(%rsp)
  b4f674:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b4f679:	cmpq   $0x20,0xb8(%rsp)
  b4f682:	lea    0x28(%rbp),%rdx
  b4f686:	jbe    b4f690 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x120>
  b4f688:	mov    0x158(%rsp),%rdx
  b4f690:	mov    $0xfef75c,%eax
  b4f695:	nopl   (%rax)
  b4f698:	movzbl (%rax),%ecx
  b4f69b:	add    $0x1,%rax
  b4f69f:	mov    %ecx,(%rdx)
  b4f6a1:	add    $0x4,%rdx
  b4f6a5:	cmp    $0xfef76b,%rax
  b4f6ab:	jne    b4f698 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x128>
  b4f6ad:	cmpq   $0x20,0xb8(%rsp)
  b4f6b6:	movq   $0xf,0xb0(%rsp)
  b4f6c2:	lea    0x64(%rbp),%rax
  b4f6c6:	jbe    b4f6d4 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x164>
  b4f6c8:	mov    0x158(%rsp),%rax
  b4f6d0:	add    $0x3c,%rax
  b4f6d4:	movl   $0x0,(%rax)
  b4f6da:	mov    0x9128(%rbx),%rdi
  b4f6e1:	lea    0x9260(%rbx),%rdx
  b4f6e8:	mov    %rbp,%rsi
  b4f6eb:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b4f6f0:	mov    %rbp,%rdi
  b4f6f3:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f6f8:	mov    (%rbx),%rax
  b4f6fb:	mov    %rbx,%rdi
  b4f6fe:	call   *0x48(%rax)
  b4f701:	add    $0x218,%rsp
  b4f708:	mov    $0x1,%eax
  b4f70d:	pop    %rbx
  b4f70e:	pop    %rbp
  b4f70f:	ret
  b4f710:	mov    0x9120(%rdi),%rdi
  b4f717:	mov    $0x1,%sil
  b4f71a:	lea    0x160(%rsp),%rbp
  b4f722:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f727:	mov    0x9128(%rbx),%rdi
  b4f72e:	xor    %esi,%esi
  b4f730:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f735:	mov    0x9130(%rbx),%rdi
  b4f73c:	xor    %esi,%esi
  b4f73e:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f743:	mov    0x9108(%rbx),%rdi
  b4f74a:	mov    $0x1,%esi
  b4f74f:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f754:	mov    0x9110(%rbx),%rdi
  b4f75b:	xor    %esi,%esi
  b4f75d:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f762:	mov    0x9118(%rbx),%rdi
  b4f769:	xor    %esi,%esi
  b4f76b:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f770:	movb   $0x0,0x91a8(%rbx)
  b4f777:	mov    $0xf,%esi
  b4f77c:	mov    %rbp,%rdi
  b4f77f:	movq   $0x20,0x168(%rsp)
  b4f78b:	movq   $0x0,0x170(%rsp)
  b4f797:	movq   $0x0,0x180(%rsp)
  b4f7a3:	movq   $0x0,0x178(%rsp)
  b4f7af:	movq   $0x0,0x208(%rsp)
  b4f7bb:	movq   $0x0,0x160(%rsp)
  b4f7c7:	movl   $0x0,0x188(%rsp)
  b4f7d2:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b4f7d7:	cmpq   $0x20,0x168(%rsp)
  b4f7e0:	lea    0x28(%rbp),%rdx
  b4f7e4:	jbe    b4f7ee <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x27e>
  b4f7e6:	mov    0x208(%rsp),%rdx
  b4f7ee:	mov    $0xfef75c,%eax
  b4f7f3:	nopl   0x0(%rax,%rax,1)
  b4f7f8:	movzbl (%rax),%ecx
  b4f7fb:	add    $0x1,%rax
  b4f7ff:	mov    %ecx,(%rdx)
  b4f801:	add    $0x4,%rdx
  b4f805:	cmp    $0xfef76b,%rax
  b4f80b:	jne    b4f7f8 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x288>
  b4f80d:	cmpq   $0x20,0x168(%rsp)
  b4f816:	movq   $0xf,0x160(%rsp)
  b4f822:	lea    0x64(%rbp),%rax
  b4f826:	jbe    b4f834 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x2c4>
  b4f828:	mov    0x208(%rsp),%rax
  b4f830:	add    $0x3c,%rax
  b4f834:	movl   $0x0,(%rax)
  b4f83a:	mov    0x9120(%rbx),%rdi
  b4f841:	lea    0x91b0(%rbx),%rdx
  b4f848:	mov    %rbp,%rsi
  b4f84b:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b4f850:	jmp    b4f6f0 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x180>
  b4f855:	nopl   (%rax)
  b4f858:	mov    0x9120(%rdi),%rdi
  b4f85f:	xor    %esi,%esi
  b4f861:	mov    %rsp,%rbp
  b4f864:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f869:	mov    0x9128(%rbx),%rdi
  b4f870:	xor    %esi,%esi
  b4f872:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f877:	mov    0x9130(%rbx),%rdi
  b4f87e:	mov    $0x1,%esi
  b4f883:	call   554dc8 <_ZN5CEGUI11RadioButton11setSelectedEb@plt>
  b4f888:	mov    0x9108(%rbx),%rdi
  b4f88f:	xor    %esi,%esi
  b4f891:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f896:	mov    0x9110(%rbx),%rdi
  b4f89d:	xor    %esi,%esi
  b4f89f:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f8a4:	mov    0x9118(%rbx),%rdi
  b4f8ab:	mov    $0x1,%esi
  b4f8b0:	call   554718 <_ZN5CEGUI6Window10setVisibleEb@plt>
  b4f8b5:	movb   $0x0,0x91aa(%rbx)
  b4f8bc:	mov    $0xf,%esi
  b4f8c1:	mov    %rsp,%rdi
  b4f8c4:	movq   $0x20,0x8(%rsp)
  b4f8cd:	movq   $0x0,0x10(%rsp)
  b4f8d6:	movq   $0x0,0x20(%rsp)
  b4f8df:	movq   $0x0,0x18(%rsp)
  b4f8e8:	movq   $0x0,0xa8(%rsp)
  b4f8f4:	movq   $0x0,(%rsp)
  b4f8fc:	movl   $0x0,0x28(%rsp)
  b4f904:	call   5558f8 <_ZN5CEGUI6String4growEm@plt>
  b4f909:	cmpq   $0x20,0x8(%rsp)
  b4f90f:	lea    0x28(%rsp),%rdx
  b4f914:	jbe    b4f91e <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x3ae>
  b4f916:	mov    0xa8(%rsp),%rdx
  b4f91e:	mov    $0xfef75c,%eax
  b4f923:	nopl   0x0(%rax,%rax,1)
  b4f928:	movzbl (%rax),%ecx
  b4f92b:	add    $0x1,%rax
  b4f92f:	mov    %ecx,(%rdx)
  b4f931:	add    $0x4,%rdx
  b4f935:	cmp    $0xfef76b,%rax
  b4f93b:	jne    b4f928 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x3b8>
  b4f93d:	cmpq   $0x20,0x8(%rsp)
  b4f943:	movq   $0xf,(%rsp)
  b4f94b:	lea    0x64(%rbp),%rax
  b4f94f:	jbe    b4f95d <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x3ed>
  b4f951:	mov    0xa8(%rsp),%rax
  b4f959:	add    $0x3c,%rax
  b4f95d:	movl   $0x0,(%rax)
  b4f963:	mov    0x9130(%rbx),%rdi
  b4f96a:	lea    0x9310(%rbx),%rdx
  b4f971:	mov    %rsp,%rsi
  b4f974:	call   5532d8 <_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_@plt>
  b4f979:	mov    %rsp,%rdi
  b4f97c:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f981:	mov    (%rbx),%rax
  b4f984:	mov    %rbx,%rdi
  b4f987:	call   *0x48(%rax)
  b4f98a:	add    $0x218,%rsp
  b4f991:	mov    $0x1,%eax
  b4f996:	pop    %rbx
  b4f997:	pop    %rbp
  b4f998:	ret
  b4f999:	mov    %rax,%rbx
  b4f99c:	mov    %rbp,%rdi
  b4f99f:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f9a4:	mov    %rbx,%rdi
  b4f9a7:	call   554498 <_Unwind_Resume@plt>
  b4f9ac:	mov    %rax,%rbx
  b4f9af:	mov    %rsp,%rdi
  b4f9b2:	call   555fe8 <_ZN5CEGUI6StringD1Ev@plt>
  b4f9b7:	mov    %rbx,%rdi
  b4f9ba:	call   554498 <_Unwind_Resume@plt>
  b4f9bf:	jmp    b4f999 <_ZN14CInventoryMenu7onClickE15ELayoutFunction+0x429>
  b4f9c1:	nop
  b4f9c2:	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
