00000000008f5810 <CPlayer::levelResetting()>:
  8f5810:	41 54                	push   r12
  8f5812:	55                   	push   rbp
  8f5813:	53                   	push   rbx
  8f5814:	48 89 fb             	mov    rbx,rdi
  8f5817:	48 83 ec 60          	sub    rsp,0x60
  8f581b:	e8 e0 08 f3 ff       	call   826100 <CCharacter::levelResetting()>
  8f5820:	48 89 df             	mov    rdi,rbx
  8f5823:	e8 38 e6 f1 ff       	call   813e60 <CCharacter::maxHP()>
  8f5828:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8f582c:	48 89 df             	mov    rdi,rbx
  8f582f:	e8 1c 32 f4 ff       	call   838a50 <CCharacter::modifyHP(float)>
  8f5834:	48 89 df             	mov    rdi,rbx
  8f5837:	e8 d4 e1 f1 ff       	call   813a10 <CCharacter::maxMana()>
  8f583c:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8f5840:	48 89 df             	mov    rdi,rbx
  8f5843:	e8 a8 e2 f1 ff       	call   813af0 <CCharacter::modifyMana(float)>
  8f5848:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8f584c:	48 85 ff             	test   rdi,rdi
  8f584f:	74 19                	je     8f586a <CPlayer::levelResetting()+0x5a>
  8f5851:	48 83 7f 18 00       	cmp    QWORD PTR [rdi+0x18],0x0
  8f5856:	74 12                	je     8f586a <CPlayer::levelResetting()+0x5a>
  8f5858:	e8 e3 9e 47 00       	call   d6f740 <CResourceManager::getGameUI()>
  8f585d:	83 b8 28 19 00 00 01 	cmp    DWORD PTR [rax+0x1928],0x1
  8f5864:	0f 84 1e 02 00 00    	je     8f5a88 <CPlayer::levelResetting()+0x278>
  8f586a:	48 8b 93 48 06 00 00 	mov    rdx,QWORD PTR [rbx+0x648]
  8f5871:	48 8b 83 50 06 00 00 	mov    rax,QWORD PTR [rbx+0x650]
  8f5878:	48 29 d0             	sub    rax,rdx
  8f587b:	48 c1 f8 03          	sar    rax,0x3
  8f587f:	48 85 c0             	test   rax,rax
  8f5882:	0f 84 88 00 00 00    	je     8f5910 <CPlayer::levelResetting()+0x100>
  8f5888:	31 ed                	xor    ebp,ebp
  8f588a:	45 31 e4             	xor    r12d,r12d
  8f588d:	eb 5c                	jmp    8f58eb <CPlayer::levelResetting()+0xdb>
  8f588f:	90                   	nop
  8f5890:	f3 48 0f 2a c0       	cvtsi2ss xmm0,rax
  8f5895:	f3 0f 59 05 83 8c 6d 00 	mulss  xmm0,DWORD PTR [rip+0x6d8c83]        # fce520 <vtable for iInventoryListener+0xe0>
  8f589d:	48 8b 3c 2a          	mov    rdi,QWORD PTR [rdx+rbp*1]
  8f58a1:	41 83 c4 01          	add    r12d,0x1
  8f58a5:	e8 e6 1f f3 ff       	call   827890 <CCharacter::teleportToMaster(float)>
  8f58aa:	48 8b 83 48 06 00 00 	mov    rax,QWORD PTR [rbx+0x648]
  8f58b1:	48 8b 3c 28          	mov    rdi,QWORD PTR [rax+rbp*1]
  8f58b5:	e8 a6 e5 f1 ff       	call   813e60 <CCharacter::maxHP()>
  8f58ba:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8f58be:	48 8b 83 48 06 00 00 	mov    rax,QWORD PTR [rbx+0x648]
  8f58c5:	48 8b 3c 28          	mov    rdi,QWORD PTR [rax+rbp*1]
  8f58c9:	44 89 e5             	mov    ebp,r12d
  8f58cc:	e8 7f 31 f4 ff       	call   838a50 <CCharacter::modifyHP(float)>
  8f58d1:	48 8b 93 48 06 00 00 	mov    rdx,QWORD PTR [rbx+0x648]
  8f58d8:	48 8b 83 50 06 00 00 	mov    rax,QWORD PTR [rbx+0x650]
  8f58df:	48 29 d0             	sub    rax,rdx
  8f58e2:	48 c1 f8 03          	sar    rax,0x3
  8f58e6:	48 39 c5             	cmp    rbp,rax
  8f58e9:	73 25                	jae    8f5910 <CPlayer::levelResetting()+0x100>
  8f58eb:	48 c1 e5 03          	shl    rbp,0x3
  8f58ef:	48 85 c0             	test   rax,rax
  8f58f2:	79 9c                	jns    8f5890 <CPlayer::levelResetting()+0x80>
  8f58f4:	48 89 c1             	mov    rcx,rax
  8f58f7:	83 e0 01             	and    eax,0x1
  8f58fa:	48 d1 e9             	shr    rcx,1
  8f58fd:	48 09 c1             	or     rcx,rax
  8f5900:	f3 48 0f 2a c1       	cvtsi2ss xmm0,rcx
  8f5905:	f3 0f 58 c0          	addss  xmm0,xmm0
  8f5909:	eb 8a                	jmp    8f5895 <CPlayer::levelResetting()+0x85>
  8f590b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8f5910:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8f5913:	48 8d 6c 24 40       	lea    rbp,[rsp+0x40]
  8f5918:	31 f6                	xor    esi,esi
  8f591a:	48 89 df             	mov    rdi,rbx
  8f591d:	ff 90 48 03 00 00    	call   QWORD PTR [rax+0x348]
  8f5923:	48 8d 54 24 5f       	lea    rdx,[rsp+0x5f]
  8f5928:	be 3a 99 fc 00       	mov    esi,0xfc993a
  8f592d:	48 89 ef             	mov    rdi,rbp
  8f5930:	e8 c3 09 c6 ff       	call   5562f8 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string(char const*, std::allocator<char> const&)@plt>
  8f5935:	48 8b bb 00 02 00 00 	mov    rdi,QWORD PTR [rbx+0x200]
  8f593c:	f3 0f 10 0d 1c 2e 6b 00 	movss  xmm1,DWORD PTR [rip+0x6b2e1c]        # fa8760 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc0>
  8f5944:	f3 0f 10 05 b0 ee 6a 00 	movss  xmm0,DWORD PTR [rip+0x6aeeb0]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  8f594c:	ba 01 00 00 00       	mov    edx,0x1
  8f5951:	48 89 ee             	mov    rsi,rbp
  8f5954:	e8 97 03 fb ff       	call   8a5cf0 <CGenericModel::playAnimation(std::string const&, bool, float, float)>
  8f5959:	48 8b 7c 24 40       	mov    rdi,QWORD PTR [rsp+0x40]
  8f595e:	48 83 ef 18          	sub    rdi,0x18
  8f5962:	48 81 ff 20 3a 42 01 	cmp    rdi,0x1423a20
  8f5969:	0f 85 87 02 00 00    	jne    8f5bf6 <CPlayer::levelResetting()+0x3e6>
  8f596f:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8f5972:	be 01 00 00 00       	mov    esi,0x1
  8f5977:	48 89 df             	mov    rdi,rbx
  8f597a:	ff 50 40             	call   QWORD PTR [rax+0x40]
  8f597d:	48 83 bb b8 01 00 00 00 	cmp    QWORD PTR [rbx+0x1b8],0x0
  8f5985:	0f 84 f0 00 00 00    	je     8f5a7b <CPlayer::levelResetting()+0x26b>
  8f598b:	48 8d 6c 24 30       	lea    rbp,[rsp+0x30]
  8f5990:	48 8d 54 24 5e       	lea    rdx,[rsp+0x5e]
  8f5995:	be e8 9a fc 00       	mov    esi,0xfc9ae8
  8f599a:	48 89 ef             	mov    rdi,rbp
  8f599d:	e8 b6 04 c6 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8f59a2:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  8f59a9:	48 89 ee             	mov    rsi,rbp
  8f59ac:	e8 ef d3 ef ff       	call   7f2da0 <CEffectManager::deleteAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8f59b1:	48 8b 7c 24 30       	mov    rdi,QWORD PTR [rsp+0x30]
  8f59b6:	bd 40 45 42 01       	mov    ebp,0x1424540
  8f59bb:	48 83 ef 18          	sub    rdi,0x18
  8f59bf:	48 39 ef             	cmp    rdi,rbp
  8f59c2:	0f 85 f5 01 00 00    	jne    8f5bbd <CPlayer::levelResetting()+0x3ad>
  8f59c8:	4c 8d 64 24 20       	lea    r12,[rsp+0x20]
  8f59cd:	48 8d 54 24 5d       	lea    rdx,[rsp+0x5d]
  8f59d2:	be e0 99 fc 00       	mov    esi,0xfc99e0
  8f59d7:	4c 89 e7             	mov    rdi,r12
  8f59da:	e8 79 04 c6 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8f59df:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  8f59e6:	4c 89 e6             	mov    rsi,r12
  8f59e9:	e8 b2 d3 ef ff       	call   7f2da0 <CEffectManager::deleteAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8f59ee:	48 8b 7c 24 20       	mov    rdi,QWORD PTR [rsp+0x20]
  8f59f3:	48 83 ef 18          	sub    rdi,0x18
  8f59f7:	48 39 fd             	cmp    rbp,rdi
  8f59fa:	0f 85 82 01 00 00    	jne    8f5b82 <CPlayer::levelResetting()+0x372>
  8f5a00:	4c 8d 64 24 10       	lea    r12,[rsp+0x10]
  8f5a05:	48 8d 54 24 5c       	lea    rdx,[rsp+0x5c]
  8f5a0a:	be 50 9b fc 00       	mov    esi,0xfc9b50
  8f5a0f:	4c 89 e7             	mov    rdi,r12
  8f5a12:	e8 41 04 c6 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8f5a17:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  8f5a1e:	4c 89 e6             	mov    rsi,r12
  8f5a21:	e8 7a d3 ef ff       	call   7f2da0 <CEffectManager::deleteAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8f5a26:	48 8b 7c 24 10       	mov    rdi,QWORD PTR [rsp+0x10]
  8f5a2b:	48 83 ef 18          	sub    rdi,0x18
  8f5a2f:	48 39 fd             	cmp    rbp,rdi
  8f5a32:	0f 85 00 01 00 00    	jne    8f5b38 <CPlayer::levelResetting()+0x328>
  8f5a38:	48 8d 54 24 5b       	lea    rdx,[rsp+0x5b]
  8f5a3d:	be 28 9c fc 00       	mov    esi,0xfc9c28
  8f5a42:	48 89 e7             	mov    rdi,rsp
  8f5a45:	e8 0e 04 c6 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8f5a4a:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  8f5a51:	48 89 e6             	mov    rsi,rsp
  8f5a54:	e8 47 d3 ef ff       	call   7f2da0 <CEffectManager::deleteAffix(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8f5a59:	48 8b 3c 24          	mov    rdi,QWORD PTR [rsp]
  8f5a5d:	48 83 ef 18          	sub    rdi,0x18
  8f5a61:	48 39 fd             	cmp    rbp,rdi
  8f5a64:	0f 85 8b 00 00 00    	jne    8f5af5 <CPlayer::levelResetting()+0x2e5>
  8f5a6a:	48 8b bb b8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1b8]
  8f5a71:	48 85 ff             	test   rdi,rdi
  8f5a74:	74 05                	je     8f5a7b <CPlayer::levelResetting()+0x26b>
  8f5a76:	e8 d5 e0 ef ff       	call   7f3b50 <CEffectManager::removeNonSavedEffects()>
  8f5a7b:	48 83 c4 60          	add    rsp,0x60
  8f5a7f:	5b                   	pop    rbx
  8f5a80:	5d                   	pop    rbp
  8f5a81:	41 5c                	pop    r12
  8f5a83:	c3                   	ret
  8f5a84:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8f5a88:	48 8b 53 68          	mov    rdx,QWORD PTR [rbx+0x68]
  8f5a8c:	31 c0                	xor    eax,eax
  8f5a8e:	48 85 d2             	test   rdx,rdx
  8f5a91:	74 04                	je     8f5a97 <CPlayer::levelResetting()+0x287>
  8f5a93:	48 8b 42 18          	mov    rax,QWORD PTR [rdx+0x18]
  8f5a97:	48 8d b0 40 01 00 00 	lea    rsi,[rax+0x140]
  8f5a9e:	48 89 df             	mov    rdi,rbx
  8f5aa1:	e8 3a 16 0f 00       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  8f5aa6:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  8f5aaa:	31 f6                	xor    esi,esi
  8f5aac:	48 85 c0             	test   rax,rax
  8f5aaf:	74 04                	je     8f5ab5 <CPlayer::levelResetting()+0x2a5>
  8f5ab1:	48 8b 70 18          	mov    rsi,QWORD PTR [rax+0x18]
  8f5ab5:	31 d2                	xor    edx,edx
  8f5ab7:	f3 0f 10 05 a9 2c 6b 00 	movss  xmm0,DWORD PTR [rip+0x6b2ca9]        # fa8768 <vtable for Ogre::SharedPtr<Ogre::Texture>+0xc8>
  8f5abf:	48 89 df             	mov    rdi,rbx
  8f5ac2:	e8 e9 a3 f1 ff       	call   80feb0 <CCharacter::dropToGround(CLevel&, float, bool)>
  8f5ac7:	48 8b 53 68          	mov    rdx,QWORD PTR [rbx+0x68]
  8f5acb:	31 c0                	xor    eax,eax
  8f5acd:	48 85 d2             	test   rdx,rdx
  8f5ad0:	74 04                	je     8f5ad6 <CPlayer::levelResetting()+0x2c6>
  8f5ad2:	48 8b 42 18          	mov    rax,QWORD PTR [rdx+0x18]
  8f5ad6:	48 8d b0 64 01 00 00 	lea    rsi,[rax+0x164]
  8f5add:	48 89 df             	mov    rdi,rbx
  8f5ae0:	e8 fb cb f1 ff       	call   8126e0 <CCharacter::setToward(Ogre::Vector3 const&)>
  8f5ae5:	e9 80 fd ff ff       	jmp    8f586a <CPlayer::levelResetting()+0x5a>
  8f5aea:	48 89 c3             	mov    rbx,rax
  8f5aed:	48 89 df             	mov    rdi,rbx
  8f5af0:	e8 a3 e9 c5 ff       	call   554498 <_Unwind_Resume@plt>
  8f5af5:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8f5afa:	48 85 c0             	test   rax,rax
  8f5afd:	74 2c                	je     8f5b2b <CPlayer::levelResetting()+0x31b>
  8f5aff:	83 c8 ff             	or     eax,0xffffffff
  8f5b02:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8f5b07:	85 c0                	test   eax,eax
  8f5b09:	0f 8f 5b ff ff ff    	jg     8f5a6a <CPlayer::levelResetting()+0x25a>
  8f5b0f:	48 8d 74 24 56       	lea    rsi,[rsp+0x56]
  8f5b14:	e8 2f da c5 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8f5b19:	e9 4c ff ff ff       	jmp    8f5a6a <CPlayer::levelResetting()+0x25a>
  8f5b1e:	48 89 e7             	mov    rdi,rsp
  8f5b21:	48 89 c3             	mov    rbx,rax
  8f5b24:	e8 af ed c5 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8f5b29:	eb c2                	jmp    8f5aed <CPlayer::levelResetting()+0x2dd>
  8f5b2b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8f5b2e:	8d 50 ff             	lea    edx,[rax-0x1]
  8f5b31:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8f5b34:	eb d1                	jmp    8f5b07 <CPlayer::levelResetting()+0x2f7>
  8f5b36:	eb b2                	jmp    8f5aea <CPlayer::levelResetting()+0x2da>
  8f5b38:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8f5b3d:	48 85 c0             	test   rax,rax
  8f5b40:	74 34                	je     8f5b76 <CPlayer::levelResetting()+0x366>
  8f5b42:	83 c8 ff             	or     eax,0xffffffff
  8f5b45:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8f5b4a:	85 c0                	test   eax,eax
  8f5b4c:	0f 8f e6 fe ff ff    	jg     8f5a38 <CPlayer::levelResetting()+0x228>
  8f5b52:	48 8d 74 24 57       	lea    rsi,[rsp+0x57]
  8f5b57:	e8 ec d9 c5 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8f5b5c:	e9 d7 fe ff ff       	jmp    8f5a38 <CPlayer::levelResetting()+0x228>
  8f5b61:	4c 89 e7             	mov    rdi,r12
  8f5b64:	48 89 c3             	mov    rbx,rax
  8f5b67:	e8 6c ed c5 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8f5b6c:	e9 7c ff ff ff       	jmp    8f5aed <CPlayer::levelResetting()+0x2dd>
  8f5b71:	e9 74 ff ff ff       	jmp    8f5aea <CPlayer::levelResetting()+0x2da>
  8f5b76:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8f5b79:	8d 50 ff             	lea    edx,[rax-0x1]
  8f5b7c:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8f5b7f:	90                   	nop
  8f5b80:	eb c8                	jmp    8f5b4a <CPlayer::levelResetting()+0x33a>
  8f5b82:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8f5b87:	48 85 c0             	test   rax,rax
  8f5b8a:	74 21                	je     8f5bad <CPlayer::levelResetting()+0x39d>
  8f5b8c:	83 c8 ff             	or     eax,0xffffffff
  8f5b8f:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8f5b94:	85 c0                	test   eax,eax
  8f5b96:	0f 8f 64 fe ff ff    	jg     8f5a00 <CPlayer::levelResetting()+0x1f0>
  8f5b9c:	48 8d 74 24 58       	lea    rsi,[rsp+0x58]
  8f5ba1:	e8 a2 d9 c5 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8f5ba6:	e9 55 fe ff ff       	jmp    8f5a00 <CPlayer::levelResetting()+0x1f0>
  8f5bab:	eb b4                	jmp    8f5b61 <CPlayer::levelResetting()+0x351>
  8f5bad:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8f5bb0:	8d 50 ff             	lea    edx,[rax-0x1]
  8f5bb3:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8f5bb6:	eb dc                	jmp    8f5b94 <CPlayer::levelResetting()+0x384>
  8f5bb8:	e9 2d ff ff ff       	jmp    8f5aea <CPlayer::levelResetting()+0x2da>
  8f5bbd:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8f5bc2:	48 85 c0             	test   rax,rax
  8f5bc5:	74 78                	je     8f5c3f <CPlayer::levelResetting()+0x42f>
  8f5bc7:	83 c8 ff             	or     eax,0xffffffff
  8f5bca:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8f5bcf:	85 c0                	test   eax,eax
  8f5bd1:	0f 8f f1 fd ff ff    	jg     8f59c8 <CPlayer::levelResetting()+0x1b8>
  8f5bd7:	48 8d 74 24 59       	lea    rsi,[rsp+0x59]
  8f5bdc:	e8 67 d9 c5 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8f5be1:	e9 e2 fd ff ff       	jmp    8f59c8 <CPlayer::levelResetting()+0x1b8>
  8f5be6:	48 89 ef             	mov    rdi,rbp
  8f5be9:	48 89 c3             	mov    rbx,rax
  8f5bec:	e8 e7 ec c5 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8f5bf1:	e9 f7 fe ff ff       	jmp    8f5aed <CPlayer::levelResetting()+0x2dd>
  8f5bf6:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8f5bfb:	48 85 c0             	test   rax,rax
  8f5bfe:	74 2f                	je     8f5c2f <CPlayer::levelResetting()+0x41f>
  8f5c00:	83 c8 ff             	or     eax,0xffffffff
  8f5c03:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8f5c08:	85 c0                	test   eax,eax
  8f5c0a:	0f 8f 5f fd ff ff    	jg     8f596f <CPlayer::levelResetting()+0x15f>
  8f5c10:	48 8d 74 24 5a       	lea    rsi,[rsp+0x5a]
  8f5c15:	e8 be fb c5 ff       	call   5557d8 <std::string::_Rep::_M_destroy(std::allocator<char> const&)@plt>
  8f5c1a:	e9 50 fd ff ff       	jmp    8f596f <CPlayer::levelResetting()+0x15f>
  8f5c1f:	48 89 ef             	mov    rdi,rbp
  8f5c22:	48 89 c3             	mov    rbx,rax
  8f5c25:	e8 5e 06 c6 ff       	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  8f5c2a:	e9 be fe ff ff       	jmp    8f5aed <CPlayer::levelResetting()+0x2dd>
  8f5c2f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8f5c32:	8d 50 ff             	lea    edx,[rax-0x1]
  8f5c35:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8f5c38:	eb ce                	jmp    8f5c08 <CPlayer::levelResetting()+0x3f8>
  8f5c3a:	e9 ab fe ff ff       	jmp    8f5aea <CPlayer::levelResetting()+0x2da>
  8f5c3f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8f5c42:	8d 50 ff             	lea    edx,[rax-0x1]
  8f5c45:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8f5c48:	eb 85                	jmp    8f5bcf <CPlayer::levelResetting()+0x3bf>
  8f5c4a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

