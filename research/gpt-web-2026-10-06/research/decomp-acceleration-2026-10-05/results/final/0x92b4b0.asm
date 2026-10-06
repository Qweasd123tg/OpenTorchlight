
/workspace/scratch/3ba0fff8d310/otl-recovery-1518/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000092b4b0 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f>:
  92b4b0:	push   %r15
  92b4b2:	mov    %rsi,%r15
  92b4b5:	push   %r14
  92b4b7:	push   %r13
  92b4b9:	mov    %rcx,%r13
  92b4bc:	push   %r12
  92b4be:	push   %rbp
  92b4bf:	push   %rbx
  92b4c0:	mov    %rdi,%rbx
  92b4c3:	sub    $0x158,%rsp
  92b4ca:	mov    %rdx,0x28(%rsp)
  92b4cf:	movss  %xmm0,0x20(%rsp)
  92b4d5:	lea    0x120(%rsp),%r12
  92b4dd:	movss  %xmm1,0x24(%rsp)
  92b4e3:	movss  %xmm2,0x34(%rsp)
  92b4e9:	movb   $0x1,0xa2(%rdi)
  92b4f0:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  92b4f5:	mov    %rax,%rbp
  92b4f8:	mov    (%rax),%rax
  92b4fb:	lea    0x14f(%rsp),%rdx
  92b503:	mov    $0xfd4d0d,%esi
  92b508:	mov    %r12,%rdi
  92b50b:	mov    0xb0(%rax),%r14
  92b512:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  92b517:	mov    %r12,%rsi
  92b51a:	mov    %rbp,%rdi
  92b51d:	call   *%r14
  92b520:	mov    0x120(%rsp),%rdi
  92b528:	mov    $0x1423a20,%r12d
  92b52e:	sub    $0x18,%rdi
  92b532:	cmp    %r12,%rdi
  92b535:	jne    92bd69 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x8b9>
  92b53b:	test   %al,%al
  92b53d:	je     92b908 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x458>
  92b543:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  92b548:	mov    %rax,%rbp
  92b54b:	mov    (%rax),%rax
  92b54e:	lea    0x110(%rsp),%r14
  92b556:	lea    0x14e(%rsp),%rdx
  92b55e:	mov    $0xfd4d0d,%esi
  92b563:	mov    %r14,%rdi
  92b566:	mov    0xa0(%rax),%rax
  92b56d:	mov    %rax,0x38(%rsp)
  92b572:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  92b577:	mov    %r14,%rdx
  92b57a:	mov    %rbp,%rsi
  92b57d:	lea    0xb0(%rsp),%rdi
  92b585:	call   *0x38(%rsp)
  92b589:	mov    0xb8(%rsp),%rax
  92b591:	movl   $0x0,0xa8(%rsp)
  92b59c:	movq   $0xfa44d0,0x90(%rsp)
  92b5a8:	mov    %rax,0x98(%rsp)
  92b5b0:	mov    0xc0(%rsp),%rax
  92b5b8:	test   %rax,%rax
  92b5bb:	mov    %rax,0xa0(%rsp)
  92b5c3:	je     92b5d0 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x120>
  92b5c5:	addl   $0x1,(%rax)
  92b5c8:	mov    0xc0(%rsp),%rax
  92b5d0:	test   %rax,%rax
  92b5d3:	movq   $0xfa45d0,0xb0(%rsp)
  92b5df:	je     92b5f9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x149>
  92b5e1:	mov    (%rax),%edx
  92b5e3:	sub    $0x1,%edx
  92b5e6:	test   %edx,%edx
  92b5e8:	mov    %edx,(%rax)
  92b5ea:	jne    92b5f9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x149>
  92b5ec:	lea    0xb0(%rsp),%rdi
  92b5f4:	call   56ab70 <_ZN4Ogre9SharedPtrINS_8ResourceEE7destroyEv>
  92b5f9:	mov    0x110(%rsp),%rdi
  92b601:	sub    $0x18,%rdi
  92b605:	cmp    %rdi,%r12
  92b608:	jne    92bc79 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x7c9>
  92b60e:	lea    0x40(%rsp),%rbp
  92b613:	mov    $0x1490c00,%esi
  92b618:	movq   $0x1423a38,0x40(%rsp)
  92b621:	lea    0x8(%rbp),%rdi
  92b625:	call   5529a8 <_ZNSsC1ERKSs@plt>
  92b62a:	lea    0x10(%rbp),%rdi
  92b62e:	mov    $0x1490c08,%esi
  92b633:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  92b638:	movl   $0x4,0x58(%rsp)
  92b640:	movl   $0x3,0x5c(%rsp)
  92b648:	movq   $0x1423a38,0x60(%rsp)
  92b651:	movb   $0x0,0x68(%rsp)
  92b656:	call   e4d250 <_ZN11CFileSystem12getSingletonEv>
  92b65b:	xor    %r9d,%r9d
  92b65e:	mov    $0x1,%r8d
  92b664:	xor    %ecx,%ecx
  92b666:	mov    %rbp,%rdx
  92b669:	mov    %r15,%rsi
  92b66c:	mov    %rax,%rdi
  92b66f:	call   e4e3a0 <_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb>
  92b674:	mov    0x98(%rsp),%rdi
  92b67c:	xor    %esi,%esi
  92b67e:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  92b683:	xor    %esi,%esi
  92b685:	mov    %rax,%rdi
  92b688:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  92b68d:	xor    %esi,%esi
  92b68f:	mov    %rax,%rdi
  92b692:	call   555d08 <_ZN4Ogre4Pass19getTextureUnitStateEt@plt>
  92b697:	lea    0x8(%rbp),%rsi
  92b69b:	mov    $0x2,%edx
  92b6a0:	mov    %rax,%rdi
  92b6a3:	call   553168 <_ZN4Ogre16TextureUnitState14setTextureNameERKSsNS_11TextureTypeE@plt>
  92b6a8:	mov    0x60(%rsp),%rdi
  92b6ad:	sub    $0x18,%rdi
  92b6b1:	cmp    %rdi,%r12
  92b6b4:	jne    92bcd9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x829>
  92b6ba:	mov    0x50(%rsp),%rdi
  92b6bf:	sub    $0x18,%rdi
  92b6c3:	cmp    $0x1424540,%rdi
  92b6ca:	jne    92bc19 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x769>
  92b6d0:	mov    0x48(%rsp),%rdi
  92b6d5:	sub    $0x18,%rdi
  92b6d9:	cmp    %rdi,%r12
  92b6dc:	jne    92bbe9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x739>
  92b6e2:	mov    0x40(%rsp),%rdi
  92b6e7:	sub    $0x18,%rdi
  92b6eb:	cmp    %rdi,%r12
  92b6ee:	jne    92bbb9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x709>
  92b6f4:	mov    0xa0(%rsp),%rax
  92b6fc:	movq   $0xfa4590,0x90(%rsp)
  92b708:	test   %rax,%rax
  92b70b:	je     92b71c <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x26c>
  92b70d:	mov    (%rax),%edx
  92b70f:	sub    $0x1,%edx
  92b712:	test   %edx,%edx
  92b714:	mov    %edx,(%rax)
  92b716:	je     92bb60 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x6b0>
  92b71c:	mov    0x28(%rbx),%rax
  92b720:	lea    0xf0(%rsp),%rbp
  92b728:	lea    0x14c(%rsp),%rdx
  92b730:	mov    $0xfd4d0d,%esi
  92b735:	mov    %rbp,%rdi
  92b738:	mov    (%rax),%rax
  92b73b:	mov    0x280(%rax),%r14
  92b742:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  92b747:	mov    0x28(%rbx),%rdi
  92b74b:	mov    %rbp,%rsi
  92b74e:	call   *%r14
  92b751:	mov    0xf0(%rsp),%rdi
  92b759:	sub    $0x18,%rdi
  92b75d:	cmp    %rdi,%r12
  92b760:	jne    92bda2 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x8f2>
  92b766:	mov    0x28(%rbx),%rdi
  92b76a:	movss  0x20(%rsp),%xmm0
  92b770:	mov    (%rdi),%rax
  92b773:	call   *0x260(%rax)
  92b779:	mov    0x28(%rbx),%rdi
  92b77d:	movss  0x24(%rsp),%xmm0
  92b783:	mov    (%rdi),%rax
  92b786:	call   *0x270(%rax)
  92b78c:	mov    0x28(%rsp),%rsi
  92b791:	mov    0x28(%rbx),%rdi
  92b795:	mov    $0x1423620,%edx
  92b79a:	call   552e48 <_ZN4Ogre12BillboardSet15createBillboardERKNS_7Vector3ERKNS_11ColourValueE@plt>
  92b79f:	xorps  %xmm2,%xmm2
  92b7a2:	mov    %rax,%rdi
  92b7a5:	movss  0x67904f(%rip),%xmm3        # fa47fc <_ZTVN4Ogre13FrameListenerE+0x3c>
  92b7ad:	mov    %rax,0xe8(%rsp)
  92b7b5:	movaps %xmm3,%xmm0
  92b7b8:	movaps %xmm2,%xmm1
  92b7bb:	call   554dd8 <_ZN4Ogre9Billboard15setTexcoordRectEffff@plt>
  92b7c0:	mov    0xe8(%rsp),%rdi
  92b7c8:	movss  0x24(%rsp),%xmm1
  92b7ce:	movss  0x20(%rsp),%xmm0
  92b7d4:	call   5564a8 <_ZN4Ogre9Billboard13setDimensionsEff@plt>
  92b7d9:	movss  0x0(%r13),%xmm0
  92b7df:	movss  0x8(%r13),%xmm1
  92b7e5:	cvtps2pd %xmm0,%xmm0
  92b7e8:	cvtps2pd %xmm1,%xmm1
  92b7eb:	call   5533d8 <atan2@plt>
  92b7f0:	movss  0x34(%rsp),%xmm1
  92b7f6:	unpcklpd %xmm0,%xmm0
  92b7fa:	mov    0xe8(%rsp),%rdi
  92b802:	lea    0x130(%rsp),%rsi
  92b80a:	cvtps2pd %xmm1,%xmm1
  92b80d:	mulsd  0x698d73(%rip),%xmm1        # fc4588 <_ZTI7CEditor+0x38>
  92b815:	cvtpd2ps %xmm0,%xmm0
  92b819:	unpcklpd %xmm1,%xmm1
  92b81d:	cvtpd2ps %xmm1,%xmm1
  92b821:	addss  %xmm1,%xmm0
  92b825:	movss  %xmm0,0x130(%rsp)
  92b82e:	call   5529e8 <_ZN4Ogre9Billboard11setRotationERKNS_6RadianE@plt>
  92b833:	mov    0xe8(%rsp),%rdi
  92b83b:	lea    0xd0(%rsp),%rsi
  92b843:	movl   $0x3f800000,0xd0(%rsp)
  92b84e:	movl   $0x3f800000,0xd4(%rsp)
  92b859:	movl   $0x3f800000,0xd8(%rsp)
  92b864:	movl   $0x3f800000,0xdc(%rsp)
  92b86f:	call   553ac8 <_ZN4Ogre9Billboard9setColourERKNS_11ColourValueE@plt>
  92b874:	mov    0xb0(%rbx),%rsi
  92b87b:	cmp    0xb8(%rbx),%rsi
  92b882:	je     92bba0 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x6f0>
  92b888:	xor    %eax,%eax
  92b88a:	test   %rsi,%rsi
  92b88d:	je     92b8a1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x3f1>
  92b88f:	mov    0xe8(%rsp),%rax
  92b897:	mov    %rax,(%rsi)
  92b89a:	mov    0xb0(%rbx),%rax
  92b8a1:	add    $0x8,%rax
  92b8a5:	mov    %rax,0xb0(%rbx)
  92b8ac:	movl   $0x42c80000,0x12c(%rsp)
  92b8b7:	mov    0xc8(%rbx),%rsi
  92b8be:	cmp    0xd0(%rbx),%rsi
  92b8c5:	je     92bb80 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x6d0>
  92b8cb:	xor    %eax,%eax
  92b8cd:	test   %rsi,%rsi
  92b8d0:	je     92b8df <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x42f>
  92b8d2:	movl   $0x42c80000,(%rsi)
  92b8d8:	mov    0xc8(%rbx),%rax
  92b8df:	add    $0x4,%rax
  92b8e3:	mov    %rax,0xc8(%rbx)
  92b8ea:	movb   $0x1,0xa0(%rbx)
  92b8f1:	add    $0x158,%rsp
  92b8f8:	pop    %rbx
  92b8f9:	pop    %rbp
  92b8fa:	pop    %r12
  92b8fc:	pop    %r13
  92b8fe:	pop    %r14
  92b900:	pop    %r15
  92b902:	ret
  92b903:	nopl   0x0(%rax,%rax,1)
  92b908:	call   553708 <_ZN4Ogre15MaterialManager12getSingletonEv@plt>
  92b90d:	mov    %rax,%rbp
  92b910:	mov    (%rax),%rax
  92b913:	lea    0x100(%rsp),%r14
  92b91b:	lea    0x14d(%rsp),%rdx
  92b923:	mov    $0xfd4d0d,%esi
  92b928:	mov    %r14,%rdi
  92b92b:	mov    0x28(%rax),%rax
  92b92f:	mov    %rax,0x38(%rsp)
  92b934:	call   5562f8 <_ZNSsC1EPKcRKSaIcE@plt>
  92b939:	movq   $0x0,(%rsp)
  92b941:	xor    %r9d,%r9d
  92b944:	xor    %r8d,%r8d
  92b947:	mov    $0x1424440,%ecx
  92b94c:	mov    %r14,%rdx
  92b94f:	mov    %rbp,%rsi
  92b952:	lea    0x70(%rsp),%rdi
  92b957:	call   *0x38(%rsp)
  92b95b:	mov    0x78(%rsp),%rax
  92b960:	movl   $0x0,0xa8(%rsp)
  92b96b:	movq   $0xfa44d0,0x90(%rsp)
  92b977:	mov    %rax,0x98(%rsp)
  92b97f:	mov    0x80(%rsp),%rax
  92b987:	test   %rax,%rax
  92b98a:	mov    %rax,0xa0(%rsp)
  92b992:	je     92b99f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x4ef>
  92b994:	addl   $0x1,(%rax)
  92b997:	mov    0x80(%rsp),%rax
  92b99f:	test   %rax,%rax
  92b9a2:	movq   $0xfa45d0,0x70(%rsp)
  92b9ab:	je     92b9c2 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x512>
  92b9ad:	mov    (%rax),%edx
  92b9af:	sub    $0x1,%edx
  92b9b2:	test   %edx,%edx
  92b9b4:	mov    %edx,(%rax)
  92b9b6:	jne    92b9c2 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x512>
  92b9b8:	lea    0x70(%rsp),%rdi
  92b9bd:	call   56ab70 <_ZN4Ogre9SharedPtrINS_8ResourceEE7destroyEv>
  92b9c2:	mov    0x100(%rsp),%rdi
  92b9ca:	sub    $0x18,%rdi
  92b9ce:	cmp    %rdi,%r12
  92b9d1:	jne    92bd39 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x889>
  92b9d7:	mov    0x98(%rsp),%rax
  92b9df:	xor    %esi,%esi
  92b9e1:	movb   $0x0,0xf0(%rax)
  92b9e8:	mov    0x98(%rsp),%rdi
  92b9f0:	call   552da8 <_ZN4Ogre8Material18setLightingEnabledEb@plt>
  92b9f5:	mov    0x98(%rsp),%rdi
  92b9fd:	xor    %esi,%esi
  92b9ff:	call   553208 <_ZN4Ogre8Material12getTechniqueEt@plt>
  92ba04:	xor    %esi,%esi
  92ba06:	mov    %rax,%rdi
  92ba09:	call   5539e8 <_ZN4Ogre9Technique7getPassEt@plt>
  92ba0e:	mov    $0x1,%esi
  92ba13:	mov    %rax,%rdi
  92ba16:	mov    %rax,%r14
  92ba19:	call   553dc8 <_ZN4Ogre4Pass20setDepthCheckEnabledEb@plt>
  92ba1e:	xorps  %xmm2,%xmm2
  92ba21:	mov    %r14,%rdi
  92ba24:	movaps %xmm2,%xmm1
  92ba27:	movaps %xmm2,%xmm0
  92ba2a:	call   554cd8 <_ZN4Ogre4Pass19setSelfIlluminationEfff@plt>
  92ba2f:	xor    %esi,%esi
  92ba31:	mov    %r14,%rdi
  92ba34:	call   5544a8 <_ZN4Ogre4Pass20setDepthWriteEnabledEb@plt>
  92ba39:	mov    0x98(%rsp),%rdi
  92ba41:	xor    %esi,%esi
  92ba43:	call   555e78 <_ZN4Ogre8Material16setSceneBlendingENS_14SceneBlendTypeE@plt>
  92ba48:	mov    0x98(%rsp),%rdi
  92ba50:	mov    $0x1,%esi
  92ba55:	call   5552e8 <_ZN4Ogre8Material14setCullingModeENS_11CullingModeE@plt>
  92ba5a:	lea    0x40(%rsp),%rbp
  92ba5f:	mov    $0x1490c00,%esi
  92ba64:	movq   $0x1423a38,0x40(%rsp)
  92ba6d:	lea    0x8(%rbp),%rdi
  92ba71:	call   5529a8 <_ZNSsC1ERKSs@plt>
  92ba76:	lea    0x10(%rbp),%rdi
  92ba7a:	mov    $0x1490c08,%esi
  92ba7f:	call   553288 <_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_@plt>
  92ba84:	movl   $0x4,0x58(%rsp)
  92ba8c:	movl   $0x3,0x5c(%rsp)
  92ba94:	movq   $0x1423a38,0x60(%rsp)
  92ba9d:	movb   $0x0,0x68(%rsp)
  92baa2:	call   e4d250 <_ZN11CFileSystem12getSingletonEv>
  92baa7:	xor    %r9d,%r9d
  92baaa:	mov    $0x1,%r8d
  92bab0:	xor    %ecx,%ecx
  92bab2:	mov    %rbp,%rdx
  92bab5:	mov    %r15,%rsi
  92bab8:	mov    %rax,%rdi
  92babb:	call   e4e3a0 <_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb>
  92bac0:	lea    0x8(%rbp),%rsi
  92bac4:	xor    %edx,%edx
  92bac6:	mov    %r14,%rdi
  92bac9:	call   553b18 <_ZN4Ogre4Pass22createTextureUnitStateERKSst@plt>
  92bace:	xor    %ecx,%ecx
  92bad0:	mov    $0x2,%edx
  92bad5:	mov    $0x2,%esi
  92bada:	mov    %rax,%rdi
  92badd:	call   553808 <_ZN4Ogre16TextureUnitState19setTextureFilteringENS_13FilterOptionsES1_S1_@plt>
  92bae2:	mov    0x60(%rsp),%rdi
  92bae7:	sub    $0x18,%rdi
  92baeb:	cmp    %rdi,%r12
  92baee:	jne    92bca9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x7f9>
  92baf4:	mov    0x50(%rsp),%rdi
  92baf9:	sub    $0x18,%rdi
  92bafd:	cmp    $0x1424540,%rdi
  92bb04:	jne    92bd09 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x859>
  92bb0a:	mov    0x48(%rsp),%rdi
  92bb0f:	sub    $0x18,%rdi
  92bb13:	cmp    %rdi,%r12
  92bb16:	jne    92bc49 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x799>
  92bb1c:	mov    0x40(%rsp),%rdi
  92bb21:	sub    $0x18,%rdi
  92bb25:	cmp    %rdi,%r12
  92bb28:	je     92b6f4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x244>
  92bb2e:	mov    $0x5541c8,%eax
  92bb33:	test   %rax,%rax
  92bb36:	je     92beb9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0xa09>
  92bb3c:	or     $0xffffffff,%eax
  92bb3f:	lock xadd %eax,0x10(%rdi)
  92bb44:	test   %eax,%eax
  92bb46:	jg     92b6f4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x244>
  92bb4c:	lea    0x141(%rsp),%rsi
  92bb54:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bb59:	jmp    92b6f4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x244>
  92bb5e:	xchg   %ax,%ax
  92bb60:	mov    0x90(%rsp),%rax
  92bb68:	lea    0x90(%rsp),%rdi
  92bb70:	call   *0x10(%rax)
  92bb73:	jmp    92b71c <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x26c>
  92bb78:	nopl   0x0(%rax,%rax,1)
  92bb80:	lea    0x12c(%rsp),%rdx
  92bb88:	lea    0xc0(%rbx),%rdi
  92bb8f:	call   8b2880 <_ZNSt6vectorIfSaIfEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS1_EERKf>
  92bb94:	jmp    92b8ea <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x43a>
  92bb99:	nopl   0x0(%rax)
  92bba0:	lea    0xe8(%rsp),%rdx
  92bba8:	lea    0xa8(%rbx),%rdi
  92bbaf:	call   92bf30 <_ZNSt6vectorIPN4Ogre9BillboardESaIS2_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS2_S4_EERKS2_>
  92bbb4:	jmp    92b8ac <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x3fc>
  92bbb9:	mov    $0x5541c8,%eax
  92bbbe:	test   %rax,%rax
  92bbc1:	je     92bf08 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0xa58>
  92bbc7:	or     $0xffffffff,%eax
  92bbca:	lock xadd %eax,0x10(%rdi)
  92bbcf:	test   %eax,%eax
  92bbd1:	jg     92b6f4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x244>
  92bbd7:	lea    0x146(%rsp),%rsi
  92bbdf:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bbe4:	jmp    92b6f4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x244>
  92bbe9:	mov    $0x5541c8,%eax
  92bbee:	test   %rax,%rax
  92bbf1:	je     92be57 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9a7>
  92bbf7:	or     $0xffffffff,%eax
  92bbfa:	lock xadd %eax,0x10(%rdi)
  92bbff:	test   %eax,%eax
  92bc01:	jg     92b6e2 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x232>
  92bc07:	lea    0x147(%rsp),%rsi
  92bc0f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bc14:	jmp    92b6e2 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x232>
  92bc19:	mov    $0x5541c8,%eax
  92bc1e:	test   %rax,%rax
  92bc21:	je     92be8f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9df>
  92bc27:	or     $0xffffffff,%eax
  92bc2a:	lock xadd %eax,0x10(%rdi)
  92bc2f:	test   %eax,%eax
  92bc31:	jg     92b6d0 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x220>
  92bc37:	lea    0x148(%rsp),%rsi
  92bc3f:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  92bc44:	jmp    92b6d0 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x220>
  92bc49:	mov    $0x5541c8,%eax
  92bc4e:	test   %rax,%rax
  92bc51:	je     92be73 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9c3>
  92bc57:	or     $0xffffffff,%eax
  92bc5a:	lock xadd %eax,0x10(%rdi)
  92bc5f:	test   %eax,%eax
  92bc61:	jg     92bb1c <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x66c>
  92bc67:	lea    0x142(%rsp),%rsi
  92bc6f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bc74:	jmp    92bb1c <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x66c>
  92bc79:	mov    $0x5541c8,%eax
  92bc7e:	test   %rax,%rax
  92bc81:	je     92beab <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9fb>
  92bc87:	or     $0xffffffff,%eax
  92bc8a:	lock xadd %eax,0x10(%rdi)
  92bc8f:	test   %eax,%eax
  92bc91:	jg     92b60e <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x15e>
  92bc97:	lea    0x14a(%rsp),%rsi
  92bc9f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bca4:	jmp    92b60e <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x15e>
  92bca9:	mov    $0x5541c8,%eax
  92bcae:	test   %rax,%rax
  92bcb1:	je     92be65 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9b5>
  92bcb7:	or     $0xffffffff,%eax
  92bcba:	lock xadd %eax,0x10(%rdi)
  92bcbf:	test   %eax,%eax
  92bcc1:	jg     92baf4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x644>
  92bcc7:	lea    0x144(%rsp),%rsi
  92bccf:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bcd4:	jmp    92baf4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x644>
  92bcd9:	mov    $0x5541c8,%eax
  92bcde:	test   %rax,%rax
  92bce1:	je     92be9d <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9ed>
  92bce7:	or     $0xffffffff,%eax
  92bcea:	lock xadd %eax,0x10(%rdi)
  92bcef:	test   %eax,%eax
  92bcf1:	jg     92b6ba <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x20a>
  92bcf7:	lea    0x149(%rsp),%rsi
  92bcff:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bd04:	jmp    92b6ba <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x20a>
  92bd09:	mov    $0x5541c8,%eax
  92bd0e:	test   %rax,%rax
  92bd11:	je     92be81 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x9d1>
  92bd17:	or     $0xffffffff,%eax
  92bd1a:	lock xadd %eax,0x10(%rdi)
  92bd1f:	test   %eax,%eax
  92bd21:	jg     92bb0a <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x65a>
  92bd27:	lea    0x143(%rsp),%rsi
  92bd2f:	call   553548 <_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_@plt>
  92bd34:	jmp    92bb0a <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x65a>
  92bd39:	mov    $0x5541c8,%eax
  92bd3e:	test   %rax,%rax
  92bd41:	je     92befa <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0xa4a>
  92bd47:	or     $0xffffffff,%eax
  92bd4a:	lock xadd %eax,0x10(%rdi)
  92bd4f:	test   %eax,%eax
  92bd51:	jg     92b9d7 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x527>
  92bd57:	lea    0x145(%rsp),%rsi
  92bd5f:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bd64:	jmp    92b9d7 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x527>
  92bd69:	mov    $0x5541c8,%edx
  92bd6e:	test   %rdx,%rdx
  92bd71:	je     92bf16 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0xa66>
  92bd77:	or     $0xffffffff,%edx
  92bd7a:	lock xadd %edx,0x10(%rdi)
  92bd7f:	test   %edx,%edx
  92bd81:	jg     92b53b <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x8b>
  92bd87:	lea    0x14b(%rsp),%rsi
  92bd8f:	mov    %al,0x18(%rsp)
  92bd93:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bd98:	movzbl 0x18(%rsp),%eax
  92bd9d:	jmp    92b53b <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x8b>
  92bda2:	mov    $0x5541c8,%eax
  92bda7:	test   %rax,%rax
  92bdaa:	je     92be0b <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x95b>
  92bdac:	or     $0xffffffff,%eax
  92bdaf:	lock xadd %eax,0x10(%rdi)
  92bdb4:	test   %eax,%eax
  92bdb6:	jg     92b766 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x2b6>
  92bdbc:	lea    0x140(%rsp),%rsi
  92bdc4:	call   5557d8 <_ZNSs4_Rep10_M_destroyERKSaIcE@plt>
  92bdc9:	jmp    92b766 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x2b6>
  92bdce:	mov    %rax,%rbx
  92bdd1:	lea    0x90(%rsp),%rdi
  92bdd9:	call   56b110 <_ZN4Ogre11MaterialPtrD1Ev>
  92bdde:	mov    %rbx,%rdi
  92bde1:	call   554498 <_Unwind_Resume@plt>
  92bde6:	mov    %rax,%rbx
  92bde9:	mov    %r14,%rdi
  92bdec:	call   556288 <_ZNSsD1Ev@plt>
  92bdf1:	mov    %rbx,%rdi
  92bdf4:	call   554498 <_Unwind_Resume@plt>
  92bdf9:	mov    %rax,%rbx
  92bdfc:	jmp    92bdf1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x941>
  92bdfe:	mov    %rbp,%rdi
  92be01:	mov    %rax,%rbx
  92be04:	call   556288 <_ZNSsD1Ev@plt>
  92be09:	jmp    92bdf1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x941>
  92be0b:	mov    0x10(%rdi),%eax
  92be0e:	lea    -0x1(%rax),%edx
  92be11:	mov    %edx,0x10(%rdi)
  92be14:	jmp    92bdb4 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x904>
  92be16:	lea    0x8(%rbp),%rdi
  92be1a:	mov    %rax,%rbx
  92be1d:	call   556288 <_ZNSsD1Ev@plt>
  92be22:	mov    %rbp,%rdi
  92be25:	call   556288 <_ZNSsD1Ev@plt>
  92be2a:	jmp    92bdd1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x921>
  92be2c:	mov    %rax,%rbx
  92be2f:	nop
  92be30:	jmp    92be22 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x972>
  92be32:	jmp    92bde6 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x936>
  92be34:	jmp    92bdf9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x949>
  92be36:	cs nopw 0x0(%rax,%rax,1)
  92be40:	jmp    92bdf9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x949>
  92be42:	jmp    92be2c <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x97c>
  92be44:	mov    %rbp,%rdi
  92be47:	mov    %rax,%rbx
  92be4a:	call   73d660 <_ZN9CFileInfoD1Ev>
  92be4f:	nop
  92be50:	jmp    92bdd1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x921>
  92be55:	jmp    92be16 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x966>
  92be57:	mov    0x10(%rdi),%eax
  92be5a:	lea    -0x1(%rax),%edx
  92be5d:	mov    %edx,0x10(%rdi)
  92be60:	jmp    92bbff <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x74f>
  92be65:	mov    0x10(%rdi),%eax
  92be68:	lea    -0x1(%rax),%edx
  92be6b:	mov    %edx,0x10(%rdi)
  92be6e:	jmp    92bcbf <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x80f>
  92be73:	mov    0x10(%rdi),%eax
  92be76:	lea    -0x1(%rax),%edx
  92be79:	mov    %edx,0x10(%rdi)
  92be7c:	jmp    92bc5f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x7af>
  92be81:	mov    0x10(%rdi),%eax
  92be84:	lea    -0x1(%rax),%edx
  92be87:	mov    %edx,0x10(%rdi)
  92be8a:	jmp    92bd1f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x86f>
  92be8f:	mov    0x10(%rdi),%eax
  92be92:	lea    -0x1(%rax),%edx
  92be95:	mov    %edx,0x10(%rdi)
  92be98:	jmp    92bc2f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x77f>
  92be9d:	mov    0x10(%rdi),%eax
  92bea0:	lea    -0x1(%rax),%edx
  92bea3:	mov    %edx,0x10(%rdi)
  92bea6:	jmp    92bcef <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x83f>
  92beab:	mov    0x10(%rdi),%eax
  92beae:	lea    -0x1(%rax),%edx
  92beb1:	mov    %edx,0x10(%rdi)
  92beb4:	jmp    92bc8f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x7df>
  92beb9:	mov    0x10(%rdi),%eax
  92bebc:	lea    -0x1(%rax),%edx
  92bebf:	mov    %edx,0x10(%rdi)
  92bec2:	jmp    92bb44 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x694>
  92bec7:	jmp    92bdf9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x949>
  92becc:	jmp    92be44 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x994>
  92bed1:	lea    0x90(%rsp),%rdi
  92bed9:	mov    %rax,%rbx
  92bedc:	call   56b110 <_ZN4Ogre11MaterialPtrD1Ev>
  92bee1:	jmp    92bde9 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x939>
  92bee6:	jmp    92bed1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0xa21>
  92bee8:	mov    %r12,%rdi
  92beeb:	mov    %rax,%rbx
  92beee:	xchg   %ax,%ax
  92bef0:	call   556288 <_ZNSsD1Ev@plt>
  92bef5:	jmp    92bdf1 <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x941>
  92befa:	mov    0x10(%rdi),%eax
  92befd:	lea    -0x1(%rax),%edx
  92bf00:	mov    %edx,0x10(%rdi)
  92bf03:	jmp    92bd4f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x89f>
  92bf08:	mov    0x10(%rdi),%eax
  92bf0b:	lea    -0x1(%rax),%edx
  92bf0e:	mov    %edx,0x10(%rdi)
  92bf11:	jmp    92bbcf <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x71f>
  92bf16:	mov    0x10(%rdi),%edx
  92bf19:	lea    -0x1(%rdx),%ecx
  92bf1c:	mov    %ecx,0x10(%rdi)
  92bf1f:	jmp    92bd7f <_ZN8CAutomap10setFullMapESbIwSt11char_traitsIwESaIwEEffRN4Ogre7Vector3ES6_f+0x8cf>
