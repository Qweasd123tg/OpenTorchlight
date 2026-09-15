00000000008ca940 <CItemGold::unitInit(CDataGroup*, bool)>:
  8ca940:	48 89 5c 24 d8       	mov    QWORD PTR [rsp-0x28],rbx
  8ca945:	48 89 6c 24 e0       	mov    QWORD PTR [rsp-0x20],rbp
  8ca94a:	48 89 fb             	mov    rbx,rdi
  8ca94d:	4c 89 64 24 e8       	mov    QWORD PTR [rsp-0x18],r12
  8ca952:	4c 89 6c 24 f0       	mov    QWORD PTR [rsp-0x10],r13
  8ca957:	41 89 d4             	mov    r12d,edx
  8ca95a:	4c 89 74 24 f8       	mov    QWORD PTR [rsp-0x8],r14
  8ca95f:	0f b6 d2             	movzx  edx,dl
  8ca962:	48 81 ec f8 00 00 00 	sub    rsp,0xf8
  8ca969:	48 89 f5             	mov    rbp,rsi
  8ca96c:	e8 df 78 ff ff       	call   8c2250 <CItem::unitInit(CDataGroup*, bool)>
  8ca971:	45 84 e4             	test   r12b,r12b
  8ca974:	0f 85 01 02 00 00    	jne    8cab7b <CItemGold::unitInit(CDataGroup*, bool)+0x23b>
  8ca97a:	48 85 ed             	test   rbp,rbp
  8ca97d:	0f 84 f8 01 00 00    	je     8cab7b <CItemGold::unitInit(CDataGroup*, bool)+0x23b>
  8ca983:	4c 8d a4 24 b0 00 00 00 	lea    r12,[rsp+0xb0]
  8ca98b:	48 8d 94 24 cf 00 00 00 	lea    rdx,[rsp+0xcf]
  8ca993:	be 98 1e fd 00       	mov    esi,0xfd1e98
  8ca998:	4c 89 e7             	mov    rdi,r12
  8ca99b:	e8 b8 b4 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8ca9a0:	f3 0f 10 05 94 9e 6d 00 	movss  xmm0,DWORD PTR [rip+0x6d9e94]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8ca9a8:	4c 89 e6             	mov    rsi,r12
  8ca9ab:	48 89 ef             	mov    rdi,rbp
  8ca9ae:	e8 cd 48 39 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  8ca9b3:	48 8b bc 24 b0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xb0]
  8ca9bb:	41 bc 40 45 42 01    	mov    r12d,0x1424540
  8ca9c1:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8ca9c7:	48 83 ef 18          	sub    rdi,0x18
  8ca9cb:	4c 39 e7             	cmp    rdi,r12
  8ca9ce:	0f 85 52 04 00 00    	jne    8cae26 <CItemGold::unitInit(CDataGroup*, bool)+0x4e6>
  8ca9d4:	4c 8d ac 24 a0 00 00 00 	lea    r13,[rsp+0xa0]
  8ca9dc:	48 8d 94 24 ce 00 00 00 	lea    rdx,[rsp+0xce]
  8ca9e4:	be c0 1e fd 00       	mov    esi,0xfd1ec0
  8ca9e9:	4c 89 ef             	mov    rdi,r13
  8ca9ec:	e8 67 b4 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8ca9f1:	f3 0f 10 05 43 9e 6d 00 	movss  xmm0,DWORD PTR [rip+0x6d9e43]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8ca9f9:	4c 89 ee             	mov    rsi,r13
  8ca9fc:	48 89 ef             	mov    rdi,rbp
  8ca9ff:	e8 7c 48 39 00       	call   c5f280 <CDataGroup::GetDataValue(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, float)>
  8caa04:	48 8b bc 24 a0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xa0]
  8caa0c:	0f 28 c8             	movaps xmm1,xmm0
  8caa0f:	48 83 ef 18          	sub    rdi,0x18
  8caa13:	49 39 fc             	cmp    r12,rdi
  8caa16:	0f 85 6a 04 00 00    	jne    8cae86 <CItemGold::unitInit(CDataGroup*, bool)+0x546>
  8caa1c:	f3 0f 10 44 24 18    	movss  xmm0,DWORD PTR [rsp+0x18]
  8caa22:	e8 29 81 3c 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8caa27:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8caa2d:	48 8b 43 68          	mov    rax,QWORD PTR [rbx+0x68]
  8caa31:	31 d2                	xor    edx,edx
  8caa33:	8b 48 30             	mov    ecx,DWORD PTR [rax+0x30]
  8caa36:	85 c9                	test   ecx,ecx
  8caa38:	74 07                	je     8caa41 <CItemGold::unitInit(CDataGroup*, bool)+0x101>
  8caa3a:	48 8b 50 28          	mov    rdx,QWORD PTR [rax+0x28]
  8caa3e:	48 8b 12             	mov    rdx,QWORD PTR [rdx]
  8caa41:	8b 92 ec 38 00 00    	mov    edx,DWORD PTR [rdx+0x38ec]
  8caa47:	83 fa 01             	cmp    edx,0x1
  8caa4a:	0f 84 a0 02 00 00    	je     8cacf0 <CItemGold::unitInit(CDataGroup*, bool)+0x3b0>
  8caa50:	0f 8e 1a 03 00 00    	jle    8cad70 <CItemGold::unitInit(CDataGroup*, bool)+0x430>
  8caa56:	83 fa 02             	cmp    edx,0x2
  8caa59:	0f 84 51 01 00 00    	je     8cabb0 <CItemGold::unitInit(CDataGroup*, bool)+0x270>
  8caa5f:	83 fa 03             	cmp    edx,0x3
  8caa62:	0f 84 08 02 00 00    	je     8cac70 <CItemGold::unitInit(CDataGroup*, bool)+0x330>
  8caa68:	80 3d 39 c8 bb 00 00 	cmp    BYTE PTR [rip+0xbbc839],0x0        # 14872a8 <guard variable for CItemGold::unitInit(CDataGroup*, bool)::g_Gold>
  8caa6f:	0f 84 bb 01 00 00    	je     8cac30 <CItemGold::unitInit(CDataGroup*, bool)+0x2f0>
  8caa75:	48 8b 05 34 c8 bb 00 	mov    rax,QWORD PTR [rip+0xbbc834]        # 14872b0 <CItemGold::unitInit(CDataGroup*, bool)::g_Gold>
  8caa7c:	48 83 78 e8 00       	cmp    QWORD PTR [rax-0x18],0x0
  8caa81:	75 39                	jne    8caabc <CItemGold::unitInit(CDataGroup*, bool)+0x17c>
  8caa83:	48 8d 6c 24 50       	lea    rbp,[rsp+0x50]
  8caa88:	e8 d3 c2 54 00       	call   e16d60 <CStringTranslate::getSinglton()>
  8caa8d:	48 89 ef             	mov    rdi,rbp
  8caa90:	48 89 c6             	mov    rsi,rax
  8caa93:	ba 8c d1 fc 00       	mov    edx,0xfcd18c
  8caa98:	e8 53 c4 54 00       	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  8caa9d:	48 89 ee             	mov    rsi,rbp
  8caaa0:	bf b0 72 48 01       	mov    edi,0x14872b0
  8caaa5:	e8 8e b5 c8 ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8caaaa:	48 8b 7c 24 50       	mov    rdi,QWORD PTR [rsp+0x50]
  8caaaf:	48 83 ef 18          	sub    rdi,0x18
  8caab3:	49 39 fc             	cmp    r12,rdi
  8caab6:	0f 85 34 04 00 00    	jne    8caef0 <CItemGold::unitInit(CDataGroup*, bool)+0x5b0>
  8caabc:	4c 8d 74 24 40       	lea    r14,[rsp+0x40]
  8caac1:	8b b3 2c 02 00 00    	mov    esi,DWORD PTR [rbx+0x22c]
  8caac7:	48 8d 6c 24 30       	lea    rbp,[rsp+0x30]
  8caacc:	4c 89 f7             	mov    rdi,r14
  8caacf:	e8 cc 68 3c 00       	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8caad4:	4c 89 f6             	mov    rsi,r14
  8caad7:	48 89 ef             	mov    rdi,rbp
  8caada:	e8 a9 87 c8 ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8caadf:	bf 98 0b fd 00       	mov    edi,0xfd0b98
  8caae4:	e8 1f 9b c8 ff       	call   554608 <wcslen@plt>
  8caae9:	be 98 0b fd 00       	mov    esi,0xfd0b98
  8caaee:	48 89 c2             	mov    rdx,rax
  8caaf1:	48 89 ef             	mov    rdi,rbp
  8caaf4:	e8 cf 90 c8 ff       	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  8caaf9:	4c 8d 6c 24 20       	lea    r13,[rsp+0x20]
  8caafe:	ba b0 72 48 01       	mov    edx,0x14872b0
  8cab03:	48 89 ee             	mov    rsi,rbp
  8cab06:	4c 89 ef             	mov    rdi,r13
  8cab09:	e8 c2 6c e3 ff       	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8cab0e:	48 8d bb 10 02 00 00 	lea    rdi,[rbx+0x210]
  8cab15:	4c 89 ee             	mov    rsi,r13
  8cab18:	e8 1b b5 c8 ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8cab1d:	48 8b 7c 24 20       	mov    rdi,QWORD PTR [rsp+0x20]
  8cab22:	48 83 ef 18          	sub    rdi,0x18
  8cab26:	49 39 fc             	cmp    r12,rdi
  8cab29:	0f 85 c7 02 00 00    	jne    8cadf6 <CItemGold::unitInit(CDataGroup*, bool)+0x4b6>
  8cab2f:	48 8b 7c 24 30       	mov    rdi,QWORD PTR [rsp+0x30]
  8cab34:	48 83 ef 18          	sub    rdi,0x18
  8cab38:	49 39 fc             	cmp    r12,rdi
  8cab3b:	0f 85 7f 03 00 00    	jne    8caec0 <CItemGold::unitInit(CDataGroup*, bool)+0x580>
  8cab41:	48 8b 7c 24 40       	mov    rdi,QWORD PTR [rsp+0x40]
  8cab46:	48 83 ef 18          	sub    rdi,0x18
  8cab4a:	49 39 fc             	cmp    r12,rdi
  8cab4d:	0f 85 03 03 00 00    	jne    8cae56 <CItemGold::unitInit(CDataGroup*, bool)+0x516>
  8cab53:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8cab56:	48 89 df             	mov    rdi,rbx
  8cab59:	ff 90 a8 00 00 00    	call   QWORD PTR [rax+0xa8]
  8cab5f:	8b 00                	mov    eax,DWORD PTR [rax]
  8cab61:	f3 0f 10 05 7f bc 6f 00 	movss  xmm0,DWORD PTR [rip+0x6fbc7f]        # fc67e8 <typeinfo for CPOV+0x18>
  8cab69:	48 89 df             	mov    rdi,rbx
  8cab6c:	89 83 30 02 00 00    	mov    DWORD PTR [rbx+0x230],eax
  8cab72:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8cab75:	ff 90 90 00 00 00    	call   QWORD PTR [rax+0x90]
  8cab7b:	48 8b 9c 24 d0 00 00 00 	mov    rbx,QWORD PTR [rsp+0xd0]
  8cab83:	48 8b ac 24 d8 00 00 00 	mov    rbp,QWORD PTR [rsp+0xd8]
  8cab8b:	4c 8b a4 24 e0 00 00 00 	mov    r12,QWORD PTR [rsp+0xe0]
  8cab93:	4c 8b ac 24 e8 00 00 00 	mov    r13,QWORD PTR [rsp+0xe8]
  8cab9b:	4c 8b b4 24 f0 00 00 00 	mov    r14,QWORD PTR [rsp+0xf0]
  8caba3:	48 81 c4 f8 00 00 00 	add    rsp,0xf8
  8cabaa:	c3                   	ret
  8cabab:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8cabb0:	48 8b 40 18          	mov    rax,QWORD PTR [rax+0x18]
  8cabb4:	48 8d 6c 24 70       	lea    rbp,[rsp+0x70]
  8cabb9:	48 8d 94 24 cb 00 00 00 	lea    rdx,[rsp+0xcb]
  8cabc1:	be 48 1f fd 00       	mov    esi,0xfd1f48
  8cabc6:	48 89 ef             	mov    rdi,rbp
  8cabc9:	8b 80 a8 01 00 00    	mov    eax,DWORD PTR [rax+0x1a8]
  8cabcf:	83 c0 01             	add    eax,0x1
  8cabd2:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8cabd6:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  8cabdc:	e8 77 b2 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8cabe1:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8cabe5:	48 89 ee             	mov    rsi,rbp
  8cabe8:	e8 23 4e 4a 00       	call   d6fa10 <CResourceManager::getGraph(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8cabed:	31 f6                	xor    esi,esi
  8cabef:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  8cabf5:	48 89 c7             	mov    rdi,rax
  8cabf8:	e8 13 d7 3a 00       	call   c78310 <CGraph::getValue(float, unsigned int) const>
  8cabfd:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8cac03:	f3 0f 5e 0d 31 9c 6d 00 	divss  xmm1,DWORD PTR [rip+0x6d9c31]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8cac0b:	f3 0f 59 c1          	mulss  xmm0,xmm1
  8cac0f:	e8 64 8a c8 ff       	call   553678 <ceilf@plt>
  8cac14:	f3 0f 2c c0          	cvttss2si eax,xmm0
  8cac18:	48 89 ef             	mov    rdi,rbp
  8cac1b:	89 83 2c 02 00 00    	mov    DWORD PTR [rbx+0x22c],eax
  8cac21:	e8 b2 9c c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cac26:	e9 3d fe ff ff       	jmp    8caa68 <CItemGold::unitInit(CDataGroup*, bool)+0x128>
  8cac2b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8cac30:	bf a8 72 48 01       	mov    edi,0x14872a8
  8cac35:	e8 1e 89 c8 ff       	call   553558 <__cxa_guard_acquire@plt>
  8cac3a:	85 c0                	test   eax,eax
  8cac3c:	0f 84 33 fe ff ff    	je     8caa75 <CItemGold::unitInit(CDataGroup*, bool)+0x135>
  8cac42:	bf a8 72 48 01       	mov    edi,0x14872a8
  8cac47:	48 c7 05 5e c6 bb 00 58 45 42 01 	mov    QWORD PTR [rip+0xbbc65e],0x1424558        # 14872b0 <CItemGold::unitInit(CDataGroup*, bool)::g_Gold>
  8cac52:	e8 71 93 c8 ff       	call   553fc8 <__cxa_guard_release@plt>
  8cac57:	ba 88 f7 f9 00       	mov    edx,0xf9f788
  8cac5c:	be b0 72 48 01       	mov    esi,0x14872b0
  8cac61:	bf d8 48 55 00       	mov    edi,0x5548d8
  8cac66:	e8 7d a5 c8 ff       	call   5551e8 <__cxa_atexit@plt>
  8cac6b:	e9 05 fe ff ff       	jmp    8caa75 <CItemGold::unitInit(CDataGroup*, bool)+0x135>
  8cac70:	48 8b 40 18          	mov    rax,QWORD PTR [rax+0x18]
  8cac74:	48 8d 6c 24 60       	lea    rbp,[rsp+0x60]
  8cac79:	48 8d 94 24 ca 00 00 00 	lea    rdx,[rsp+0xca]
  8cac81:	be 80 1f fd 00       	mov    esi,0xfd1f80
  8cac86:	48 89 ef             	mov    rdi,rbp
  8cac89:	8b 80 a8 01 00 00    	mov    eax,DWORD PTR [rax+0x1a8]
  8cac8f:	83 c0 01             	add    eax,0x1
  8cac92:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8cac96:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  8cac9c:	e8 b7 b1 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8caca1:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8caca5:	48 89 ee             	mov    rsi,rbp
  8caca8:	e8 63 4d 4a 00       	call   d6fa10 <CResourceManager::getGraph(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8cacad:	31 f6                	xor    esi,esi
  8cacaf:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  8cacb5:	48 89 c7             	mov    rdi,rax
  8cacb8:	e8 53 d6 3a 00       	call   c78310 <CGraph::getValue(float, unsigned int) const>
  8cacbd:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8cacc3:	f3 0f 5e 0d 71 9b 6d 00 	divss  xmm1,DWORD PTR [rip+0x6d9b71]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8caccb:	f3 0f 59 c1          	mulss  xmm0,xmm1
  8caccf:	e8 a4 89 c8 ff       	call   553678 <ceilf@plt>
  8cacd4:	f3 0f 2c c0          	cvttss2si eax,xmm0
  8cacd8:	48 89 ef             	mov    rdi,rbp
  8cacdb:	89 83 2c 02 00 00    	mov    DWORD PTR [rbx+0x22c],eax
  8cace1:	e8 f2 9b c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cace6:	e9 7d fd ff ff       	jmp    8caa68 <CItemGold::unitInit(CDataGroup*, bool)+0x128>
  8caceb:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  8cacf0:	48 8b 40 18          	mov    rax,QWORD PTR [rax+0x18]
  8cacf4:	48 8d ac 24 80 00 00 00 	lea    rbp,[rsp+0x80]
  8cacfc:	48 8d 94 24 cc 00 00 00 	lea    rdx,[rsp+0xcc]
  8cad04:	be 20 1f fd 00       	mov    esi,0xfd1f20
  8cad09:	48 89 ef             	mov    rdi,rbp
  8cad0c:	8b 80 a8 01 00 00    	mov    eax,DWORD PTR [rax+0x1a8]
  8cad12:	83 c0 01             	add    eax,0x1
  8cad15:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8cad19:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  8cad1f:	e8 34 b1 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8cad24:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8cad28:	48 89 ee             	mov    rsi,rbp
  8cad2b:	e8 e0 4c 4a 00       	call   d6fa10 <CResourceManager::getGraph(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8cad30:	31 f6                	xor    esi,esi
  8cad32:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  8cad38:	48 89 c7             	mov    rdi,rax
  8cad3b:	e8 d0 d5 3a 00       	call   c78310 <CGraph::getValue(float, unsigned int) const>
  8cad40:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8cad46:	f3 0f 5e 0d ee 9a 6d 00 	divss  xmm1,DWORD PTR [rip+0x6d9aee]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8cad4e:	f3 0f 59 c1          	mulss  xmm0,xmm1
  8cad52:	e8 21 89 c8 ff       	call   553678 <ceilf@plt>
  8cad57:	f3 0f 2c c0          	cvttss2si eax,xmm0
  8cad5b:	48 89 ef             	mov    rdi,rbp
  8cad5e:	89 83 2c 02 00 00    	mov    DWORD PTR [rbx+0x22c],eax
  8cad64:	e8 6f 9b c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cad69:	e9 fa fc ff ff       	jmp    8caa68 <CItemGold::unitInit(CDataGroup*, bool)+0x128>
  8cad6e:	66 90                	xchg   ax,ax
  8cad70:	85 d2                	test   edx,edx
  8cad72:	0f 85 f0 fc ff ff    	jne    8caa68 <CItemGold::unitInit(CDataGroup*, bool)+0x128>
  8cad78:	48 8b 40 18          	mov    rax,QWORD PTR [rax+0x18]
  8cad7c:	48 8d ac 24 90 00 00 00 	lea    rbp,[rsp+0x90]
  8cad84:	48 8d 94 24 cd 00 00 00 	lea    rdx,[rsp+0xcd]
  8cad8c:	be e8 1e fd 00       	mov    esi,0xfd1ee8
  8cad91:	48 89 ef             	mov    rdi,rbp
  8cad94:	8b 80 a8 01 00 00    	mov    eax,DWORD PTR [rax+0x1a8]
  8cad9a:	83 c0 01             	add    eax,0x1
  8cad9d:	f3 0f 2a c0          	cvtsi2ss xmm0,eax
  8cada1:	f3 0f 11 44 24 1c    	movss  DWORD PTR [rsp+0x1c],xmm0
  8cada7:	e8 ac b0 c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8cadac:	48 8b 7b 68          	mov    rdi,QWORD PTR [rbx+0x68]
  8cadb0:	48 89 ee             	mov    rsi,rbp
  8cadb3:	e8 58 4c 4a 00       	call   d6fa10 <CResourceManager::getGraph(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8cadb8:	31 f6                	xor    esi,esi
  8cadba:	f3 0f 10 44 24 1c    	movss  xmm0,DWORD PTR [rsp+0x1c]
  8cadc0:	48 89 c7             	mov    rdi,rax
  8cadc3:	e8 48 d5 3a 00       	call   c78310 <CGraph::getValue(float, unsigned int) const>
  8cadc8:	f3 0f 10 4c 24 18    	movss  xmm1,DWORD PTR [rsp+0x18]
  8cadce:	f3 0f 5e 0d 66 9a 6d 00 	divss  xmm1,DWORD PTR [rip+0x6d9a66]        # fa483c <vtable for Ogre::FrameListener+0x7c>
  8cadd6:	f3 0f 59 c1          	mulss  xmm0,xmm1
  8cadda:	e8 99 88 c8 ff       	call   553678 <ceilf@plt>
  8caddf:	f3 0f 2c c0          	cvttss2si eax,xmm0
  8cade3:	48 89 ef             	mov    rdi,rbp
  8cade6:	89 83 2c 02 00 00    	mov    DWORD PTR [rbx+0x22c],eax
  8cadec:	e8 e7 9a c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cadf1:	e9 72 fc ff ff       	jmp    8caa68 <CItemGold::unitInit(CDataGroup*, bool)+0x128>
  8cadf6:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8cadfb:	48 85 c0             	test   rax,rax
  8cadfe:	0f 84 b2 01 00 00    	je     8cafb6 <CItemGold::unitInit(CDataGroup*, bool)+0x676>
  8cae04:	83 c8 ff             	or     eax,0xffffffff
  8cae07:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8cae0c:	85 c0                	test   eax,eax
  8cae0e:	0f 8f 1b fd ff ff    	jg     8cab2f <CItemGold::unitInit(CDataGroup*, bool)+0x1ef>
  8cae14:	48 8d b4 24 c6 00 00 00 	lea    rsi,[rsp+0xc6]
  8cae1c:	e8 27 87 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8cae21:	e9 09 fd ff ff       	jmp    8cab2f <CItemGold::unitInit(CDataGroup*, bool)+0x1ef>
  8cae26:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8cae2b:	48 85 c0             	test   rax,rax
  8cae2e:	0f 84 be 01 00 00    	je     8caff2 <CItemGold::unitInit(CDataGroup*, bool)+0x6b2>
  8cae34:	83 c8 ff             	or     eax,0xffffffff
  8cae37:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8cae3c:	85 c0                	test   eax,eax
  8cae3e:	0f 8f 90 fb ff ff    	jg     8ca9d4 <CItemGold::unitInit(CDataGroup*, bool)+0x94>
  8cae44:	48 8d b4 24 c9 00 00 00 	lea    rsi,[rsp+0xc9]
  8cae4c:	e8 f7 86 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8cae51:	e9 7e fb ff ff       	jmp    8ca9d4 <CItemGold::unitInit(CDataGroup*, bool)+0x94>
  8cae56:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8cae5b:	48 85 c0             	test   rax,rax
  8cae5e:	0f 84 61 01 00 00    	je     8cafc5 <CItemGold::unitInit(CDataGroup*, bool)+0x685>
  8cae64:	83 c8 ff             	or     eax,0xffffffff
  8cae67:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8cae6c:	85 c0                	test   eax,eax
  8cae6e:	0f 8f df fc ff ff    	jg     8cab53 <CItemGold::unitInit(CDataGroup*, bool)+0x213>
  8cae74:	48 8d b4 24 c4 00 00 00 	lea    rsi,[rsp+0xc4]
  8cae7c:	e8 c7 86 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8cae81:	e9 cd fc ff ff       	jmp    8cab53 <CItemGold::unitInit(CDataGroup*, bool)+0x213>
  8cae86:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8cae8b:	48 85 c0             	test   rax,rax
  8cae8e:	0f 84 6c 01 00 00    	je     8cb000 <CItemGold::unitInit(CDataGroup*, bool)+0x6c0>
  8cae94:	83 c8 ff             	or     eax,0xffffffff
  8cae97:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8cae9c:	85 c0                	test   eax,eax
  8cae9e:	0f 8f 78 fb ff ff    	jg     8caa1c <CItemGold::unitInit(CDataGroup*, bool)+0xdc>
  8caea4:	48 8d b4 24 c8 00 00 00 	lea    rsi,[rsp+0xc8]
  8caeac:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  8caeb1:	e8 92 86 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8caeb6:	f3 0f 10 0c 24       	movss  xmm1,DWORD PTR [rsp]
  8caebb:	e9 5c fb ff ff       	jmp    8caa1c <CItemGold::unitInit(CDataGroup*, bool)+0xdc>
  8caec0:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8caec5:	48 85 c0             	test   rax,rax
  8caec8:	0f 84 a6 00 00 00    	je     8caf74 <CItemGold::unitInit(CDataGroup*, bool)+0x634>
  8caece:	83 c8 ff             	or     eax,0xffffffff
  8caed1:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8caed6:	85 c0                	test   eax,eax
  8caed8:	0f 8f 63 fc ff ff    	jg     8cab41 <CItemGold::unitInit(CDataGroup*, bool)+0x201>
  8caede:	48 8d b4 24 c5 00 00 00 	lea    rsi,[rsp+0xc5]
  8caee6:	e8 5d 86 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8caeeb:	e9 51 fc ff ff       	jmp    8cab41 <CItemGold::unitInit(CDataGroup*, bool)+0x201>
  8caef0:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8caef5:	48 85 c0             	test   rax,rax
  8caef8:	74 4a                	je     8caf44 <CItemGold::unitInit(CDataGroup*, bool)+0x604>
  8caefa:	83 c8 ff             	or     eax,0xffffffff
  8caefd:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8caf02:	85 c0                	test   eax,eax
  8caf04:	0f 8f b2 fb ff ff    	jg     8caabc <CItemGold::unitInit(CDataGroup*, bool)+0x17c>
  8caf0a:	48 8d b4 24 c7 00 00 00 	lea    rsi,[rsp+0xc7]
  8caf12:	e8 31 86 c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8caf17:	e9 a0 fb ff ff       	jmp    8caabc <CItemGold::unitInit(CDataGroup*, bool)+0x17c>
  8caf1c:	4c 89 ef             	mov    rdi,r13
  8caf1f:	48 89 c3             	mov    rbx,rax
  8caf22:	e8 b1 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf27:	48 89 ef             	mov    rdi,rbp
  8caf2a:	e8 a9 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf2f:	4c 89 f7             	mov    rdi,r14
  8caf32:	e8 a1 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf37:	48 89 df             	mov    rdi,rbx
  8caf3a:	e8 59 95 c8 ff       	call   554498 <_Unwind_Resume@plt>
  8caf3f:	48 89 c3             	mov    rbx,rax
  8caf42:	eb e3                	jmp    8caf27 <CItemGold::unitInit(CDataGroup*, bool)+0x5e7>
  8caf44:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8caf47:	8d 50 ff             	lea    edx,[rax-0x1]
  8caf4a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8caf4d:	eb b3                	jmp    8caf02 <CItemGold::unitInit(CDataGroup*, bool)+0x5c2>
  8caf4f:	48 89 ef             	mov    rdi,rbp
  8caf52:	48 89 c3             	mov    rbx,rax
  8caf55:	e8 7e 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf5a:	eb d3                	jmp    8caf2f <CItemGold::unitInit(CDataGroup*, bool)+0x5ef>
  8caf5c:	48 89 c3             	mov    rbx,rax
  8caf5f:	eb ce                	jmp    8caf2f <CItemGold::unitInit(CDataGroup*, bool)+0x5ef>
  8caf61:	48 89 c3             	mov    rbx,rax
  8caf64:	48 89 ef             	mov    rdi,rbp
  8caf67:	e8 6c 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf6c:	48 89 df             	mov    rdi,rbx
  8caf6f:	e8 24 95 c8 ff       	call   554498 <_Unwind_Resume@plt>
  8caf74:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8caf77:	8d 50 ff             	lea    edx,[rax-0x1]
  8caf7a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8caf7d:	e9 54 ff ff ff       	jmp    8caed6 <CItemGold::unitInit(CDataGroup*, bool)+0x596>
  8caf82:	48 89 c3             	mov    rbx,rax
  8caf85:	eb b0                	jmp    8caf37 <CItemGold::unitInit(CDataGroup*, bool)+0x5f7>
  8caf87:	4c 89 e7             	mov    rdi,r12
  8caf8a:	48 89 c3             	mov    rbx,rax
  8caf8d:	e8 46 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8caf92:	eb a3                	jmp    8caf37 <CItemGold::unitInit(CDataGroup*, bool)+0x5f7>
  8caf94:	eb ec                	jmp    8caf82 <CItemGold::unitInit(CDataGroup*, bool)+0x642>
  8caf96:	4c 89 ef             	mov    rdi,r13
  8caf99:	48 89 c3             	mov    rbx,rax
  8caf9c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  8cafa0:	e8 33 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cafa5:	eb 90                	jmp    8caf37 <CItemGold::unitInit(CDataGroup*, bool)+0x5f7>
  8cafa7:	48 89 ef             	mov    rdi,rbp
  8cafaa:	48 89 c3             	mov    rbx,rax
  8cafad:	e8 26 99 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8cafb2:	eb 83                	jmp    8caf37 <CItemGold::unitInit(CDataGroup*, bool)+0x5f7>
  8cafb4:	eb cc                	jmp    8caf82 <CItemGold::unitInit(CDataGroup*, bool)+0x642>
  8cafb6:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8cafb9:	8d 50 ff             	lea    edx,[rax-0x1]
  8cafbc:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8cafbf:	90                   	nop
  8cafc0:	e9 47 fe ff ff       	jmp    8cae0c <CItemGold::unitInit(CDataGroup*, bool)+0x4cc>
  8cafc5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8cafc8:	8d 50 ff             	lea    edx,[rax-0x1]
  8cafcb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8cafce:	e9 99 fe ff ff       	jmp    8cae6c <CItemGold::unitInit(CDataGroup*, bool)+0x52c>
  8cafd3:	eb d2                	jmp    8cafa7 <CItemGold::unitInit(CDataGroup*, bool)+0x667>
  8cafd5:	eb ab                	jmp    8caf82 <CItemGold::unitInit(CDataGroup*, bool)+0x642>
  8cafd7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  8cafe0:	eb c5                	jmp    8cafa7 <CItemGold::unitInit(CDataGroup*, bool)+0x667>
  8cafe2:	eb 9e                	jmp    8caf82 <CItemGold::unitInit(CDataGroup*, bool)+0x642>
  8cafe4:	eb c1                	jmp    8cafa7 <CItemGold::unitInit(CDataGroup*, bool)+0x667>
  8cafe6:	66 2e 0f 1f 84 00 00 00 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  8caff0:	eb 90                	jmp    8caf82 <CItemGold::unitInit(CDataGroup*, bool)+0x642>
  8caff2:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8caff5:	8d 50 ff             	lea    edx,[rax-0x1]
  8caff8:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8caffb:	e9 3c fe ff ff       	jmp    8cae3c <CItemGold::unitInit(CDataGroup*, bool)+0x4fc>
  8cb000:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8cb003:	8d 50 ff             	lea    edx,[rax-0x1]
  8cb006:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8cb009:	e9 8e fe ff ff       	jmp    8cae9c <CItemGold::unitInit(CDataGroup*, bool)+0x55c>
  8cb00e:	90                   	nop
  8cb00f:	90                   	nop

