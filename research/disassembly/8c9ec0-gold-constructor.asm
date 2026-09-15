00000000008c9ec0 <CItemGold::CItemGold(CResourceManager*, int)>:
  8c9ec0:	41 57                	push   r15
  8c9ec2:	49 89 f7             	mov    r15,rsi
  8c9ec5:	41 56                	push   r14
  8c9ec7:	41 55                	push   r13
  8c9ec9:	41 54                	push   r12
  8c9ecb:	55                   	push   rbp
  8c9ecc:	89 d5                	mov    ebp,edx
  8c9ece:	53                   	push   rbx
  8c9ecf:	48 89 fb             	mov    rbx,rdi
  8c9ed2:	48 81 ec 48 01 00 00 	sub    rsp,0x148
  8c9ed9:	e8 02 c9 fe ff       	call   8b67e0 <CItem::CItem(CResourceManager*)>
  8c9ede:	48 c7 03 f0 1f fd 00 	mov    QWORD PTR [rbx],0xfd1ff0
  8c9ee5:	89 ab 2c 02 00 00    	mov    DWORD PTR [rbx+0x22c],ebp
  8c9eeb:	c7 83 30 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x230],0x0
  8c9ef5:	c7 83 34 02 00 00 33 33 b3 3e 	mov    DWORD PTR [rbx+0x234],0x3eb33333
  8c9eff:	48 c7 83 38 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x238],0x0
  8c9f0a:	48 c7 83 80 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x280],0x0
  8c9f15:	c6 83 99 01 00 00 00 	mov    BYTE PTR [rbx+0x199],0x0
  8c9f1c:	c6 83 82 00 00 00 01 	mov    BYTE PTR [rbx+0x82],0x1
  8c9f23:	80 3d 8e d3 bb 00 00 	cmp    BYTE PTR [rip+0xbbd38e],0x0        # 14872b8 <guard variable for CItemGold::CItemGold(CResourceManager*, int)::g_Gold>
  8c9f2a:	0f 84 a8 07 00 00    	je     8ca6d8 <CItemGold::CItemGold(CResourceManager*, int)+0x818>
  8c9f30:	48 8b 05 89 d3 bb 00 	mov    rax,QWORD PTR [rip+0xbbd389]        # 14872c0 <CItemGold::CItemGold(CResourceManager*, int)::g_Gold>
  8c9f37:	48 83 78 e8 00       	cmp    QWORD PTR [rax-0x18],0x0
  8c9f3c:	75 43                	jne    8c9f81 <CItemGold::CItemGold(CResourceManager*, int)+0xc1>
  8c9f3e:	e8 1d ce 54 00       	call   e16d60 <CStringTranslate::getSinglton()>
  8c9f43:	4c 8d a4 24 20 01 00 00 	lea    r12,[rsp+0x120]
  8c9f4b:	ba 8c d1 fc 00       	mov    edx,0xfcd18c
  8c9f50:	48 89 c6             	mov    rsi,rax
  8c9f53:	4c 89 e7             	mov    rdi,r12
  8c9f56:	e8 95 cf 54 00       	call   e16ef0 <CStringTranslate::getTranslateString(wchar_t const*)>
  8c9f5b:	4c 89 e6             	mov    rsi,r12
  8c9f5e:	bf c0 72 48 01       	mov    edi,0x14872c0
  8c9f63:	e8 d0 c0 c8 ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8c9f68:	48 8b bc 24 20 01 00 00 	mov    rdi,QWORD PTR [rsp+0x120]
  8c9f70:	48 83 ef 18          	sub    rdi,0x18
  8c9f74:	48 81 ff 40 45 42 01 	cmp    rdi,0x1424540
  8c9f7b:	0f 85 97 07 00 00    	jne    8ca718 <CItemGold::CItemGold(CResourceManager*, int)+0x858>
  8c9f81:	4c 8d ac 24 10 01 00 00 	lea    r13,[rsp+0x110]
  8c9f89:	89 ee                	mov    esi,ebp
  8c9f8b:	4c 89 ef             	mov    rdi,r13
  8c9f8e:	e8 0d 74 3c 00       	call   c913a0 <STRINGS::GetValueAsWString(int)>
  8c9f93:	48 8d ac 24 00 01 00 00 	lea    rbp,[rsp+0x100]
  8c9f9b:	4c 89 ee             	mov    rsi,r13
  8c9f9e:	48 89 ef             	mov    rdi,rbp
  8c9fa1:	e8 e2 92 c8 ff       	call   553288 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8c9fa6:	bf 98 0b fd 00       	mov    edi,0xfd0b98
  8c9fab:	e8 58 a6 c8 ff       	call   554608 <wcslen@plt>
  8c9fb0:	be 98 0b fd 00       	mov    esi,0xfd0b98
  8c9fb5:	48 89 c2             	mov    rdx,rax
  8c9fb8:	48 89 ef             	mov    rdi,rbp
  8c9fbb:	e8 08 9c c8 ff       	call   553bc8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::append(wchar_t const*, unsigned long)@plt>
  8c9fc0:	4c 8d a4 24 f0 00 00 00 	lea    r12,[rsp+0xf0]
  8c9fc8:	ba c0 72 48 01       	mov    edx,0x14872c0
  8c9fcd:	48 89 ee             	mov    rsi,rbp
  8c9fd0:	4c 89 e7             	mov    rdi,r12
  8c9fd3:	e8 f8 77 e3 ff       	call   7017d0 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > std::operator+<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8c9fd8:	48 8d bb 10 02 00 00 	lea    rdi,[rbx+0x210]
  8c9fdf:	4c 89 e6             	mov    rsi,r12
  8c9fe2:	e8 51 c0 c8 ff       	call   556038 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::assign(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)@plt>
  8c9fe7:	48 8b bc 24 f0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xf0]
  8c9fef:	bd 40 45 42 01       	mov    ebp,0x1424540
  8c9ff4:	48 83 ef 18          	sub    rdi,0x18
  8c9ff8:	48 39 ef             	cmp    rdi,rbp
  8c9ffb:	0f 85 37 08 00 00    	jne    8ca838 <CItemGold::CItemGold(CResourceManager*, int)+0x978>
  8ca001:	48 8b bc 24 00 01 00 00 	mov    rdi,QWORD PTR [rsp+0x100]
  8ca009:	48 83 ef 18          	sub    rdi,0x18
  8ca00d:	48 39 fd             	cmp    rbp,rdi
  8ca010:	0f 85 c2 07 00 00    	jne    8ca7d8 <CItemGold::CItemGold(CResourceManager*, int)+0x918>
  8ca016:	48 8b bc 24 10 01 00 00 	mov    rdi,QWORD PTR [rsp+0x110]
  8ca01e:	48 83 ef 18          	sub    rdi,0x18
  8ca022:	48 39 fd             	cmp    rbp,rdi
  8ca025:	0f 85 dd 07 00 00    	jne    8ca808 <CItemGold::CItemGold(CResourceManager*, int)+0x948>
  8ca02b:	4c 8d a4 24 e0 00 00 00 	lea    r12,[rsp+0xe0]
  8ca033:	48 8d 94 24 3f 01 00 00 	lea    rdx,[rsp+0x13f]
  8ca03b:	c7 83 94 01 00 00 00 00 c0 3e 	mov    DWORD PTR [rbx+0x194],0x3ec00000
  8ca045:	be c0 1d fd 00       	mov    esi,0xfd1dc0
  8ca04a:	4c 89 e7             	mov    rdi,r12
  8ca04d:	e8 06 be c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8ca052:	4c 89 e6             	mov    rsi,r12
  8ca055:	48 89 df             	mov    rdi,rbx
  8ca058:	e8 93 88 ff ff       	call   8c28f0 <CItemGold::loadModel(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>
  8ca05d:	48 8b bc 24 e0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xe0]
  8ca065:	48 83 ef 18          	sub    rdi,0x18
  8ca069:	48 39 fd             	cmp    rbp,rdi
  8ca06c:	0f 85 d6 06 00 00    	jne    8ca748 <CItemGold::CItemGold(CResourceManager*, int)+0x888>
  8ca072:	48 83 bb d8 01 00 00 00 	cmp    QWORD PTR [rbx+0x1d8],0x0
  8ca07a:	c7 83 ac 01 00 00 22 00 00 00 	mov    DWORD PTR [rbx+0x1ac],0x22
  8ca084:	0f 84 06 06 00 00    	je     8ca690 <CItemGold::CItemGold(CResourceManager*, int)+0x7d0>
  8ca08a:	e8 01 a4 18 00       	call   a54490 <CMasterResourceManager::getSingleton()>
  8ca08f:	4c 8d ac 24 d0 00 00 00 	lea    r13,[rsp+0xd0]
  8ca097:	48 8d 94 24 3e 01 00 00 	lea    rdx,[rsp+0x13e]
  8ca09f:	be 30 1e fd 00       	mov    esi,0xfd1e30
  8ca0a4:	4c 8b b0 00 01 00 00 	mov    r14,QWORD PTR [rax+0x100]
  8ca0ab:	4c 89 ef             	mov    rdi,r13
  8ca0ae:	e8 a5 bd c8 ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  8ca0b3:	4c 8d a4 24 c0 00 00 00 	lea    r12,[rsp+0xc0]
  8ca0bb:	4c 89 ee             	mov    rsi,r13
  8ca0be:	4c 89 e7             	mov    rdi,r12
  8ca0c1:	e8 ca 40 3c 00       	call   c8e190 <STRINGS::StringUpper(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8ca0c6:	4c 89 e6             	mov    rsi,r12
  8ca0c9:	4c 89 f7             	mov    rdi,r14
  8ca0cc:	e8 5f 92 19 00       	call   a63330 <CSoundBankDataInformation::getSoundDataObject(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&)>
  8ca0d1:	48 8b bc 24 c0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xc0]
  8ca0d9:	49 89 c4             	mov    r12,rax
  8ca0dc:	48 83 ef 18          	sub    rdi,0x18
  8ca0e0:	48 39 fd             	cmp    rbp,rdi
  8ca0e3:	0f 85 8f 06 00 00    	jne    8ca778 <CItemGold::CItemGold(CResourceManager*, int)+0x8b8>
  8ca0e9:	4d 85 e4             	test   r12,r12
  8ca0ec:	74 2c                	je     8ca11a <CItemGold::CItemGold(CResourceManager*, int)+0x25a>
  8ca0ee:	49 8b 54 24 20       	mov    rdx,QWORD PTR [r12+0x20]
  8ca0f3:	48 8b bb d8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1d8]
  8ca0fa:	be 12 00 00 00       	mov    esi,0x12
  8ca0ff:	e8 6c f4 19 00       	call   a69570 <CSoundBank::addSample(int, long long)>
  8ca104:	49 8b 54 24 20       	mov    rdx,QWORD PTR [r12+0x20]
  8ca109:	48 8b bb d8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1d8]
  8ca110:	be 11 00 00 00       	mov    esi,0x11
  8ca115:	e8 56 f4 19 00       	call   a69570 <CSoundBank::addSample(int, long long)>
  8ca11a:	0f 57 c0             	xorps  xmm0,xmm0
  8ca11d:	f3 0f 10 0d 47 a4 6f 00 	movss  xmm1,DWORD PTR [rip+0x6fa447]        # fc456c <typeinfo for CEditor+0x1c>
  8ca125:	e8 26 8a 3c 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8ca12a:	0f 14 c0             	unpcklps xmm0,xmm0
  8ca12d:	48 8d 7c 24 40       	lea    rdi,[rsp+0x40]
  8ca132:	0f 5a c0             	cvtps2pd xmm0,xmm0
  8ca135:	f2 0f 59 05 4b a4 6f 00 	mulsd  xmm0,QWORD PTR [rip+0x6fa44b]        # fc4588 <typeinfo for CEditor+0x38>
  8ca13d:	66 0f 14 c0          	unpcklpd xmm0,xmm0
  8ca141:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  8ca145:	e8 56 01 3b 00       	call   c7a2a0 <MATH::matrixRotationY(Ogre::Matrix4&, float)>
  8ca14a:	f3 0f 10 83 c0 00 00 00 	movss  xmm0,DWORD PTR [rbx+0xc0]
  8ca152:	f3 44 0f 10 ab c4 00 00 00 	movss  xmm13,DWORD PTR [rbx+0xc4]
  8ca15b:	0f 28 c8             	movaps xmm1,xmm0
  8ca15e:	41 0f 28 d5          	movaps xmm2,xmm13
  8ca162:	f3 44 0f 10 54 24 40 	movss  xmm10,DWORD PTR [rsp+0x40]
  8ca169:	44 0f 28 f0          	movaps xmm14,xmm0
  8ca16d:	f3 44 0f 10 4c 24 50 	movss  xmm9,DWORD PTR [rsp+0x50]
  8ca174:	f3 41 0f 59 ca       	mulss  xmm1,xmm10
  8ca179:	f3 41 0f 59 d1       	mulss  xmm2,xmm9
  8ca17e:	f3 44 0f 10 a3 c8 00 00 00 	movss  xmm12,DWORD PTR [rbx+0xc8]
  8ca187:	f3 44 0f 10 44 24 60 	movss  xmm8,DWORD PTR [rsp+0x60]
  8ca18e:	f3 44 0f 10 9b cc 00 00 00 	movss  xmm11,DWORD PTR [rbx+0xcc]
  8ca197:	45 0f 28 fd          	movaps xmm15,xmm13
  8ca19b:	f3 0f 10 7c 24 70    	movss  xmm7,DWORD PTR [rsp+0x70]
  8ca1a1:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca1a5:	41 0f 28 d4          	movaps xmm2,xmm12
  8ca1a9:	f3 0f 10 74 24 44    	movss  xmm6,DWORD PTR [rsp+0x44]
  8ca1af:	f3 41 0f 59 d0       	mulss  xmm2,xmm8
  8ca1b4:	f3 0f 10 6c 24 54    	movss  xmm5,DWORD PTR [rsp+0x54]
  8ca1ba:	f3 0f 10 64 24 64    	movss  xmm4,DWORD PTR [rsp+0x64]
  8ca1c0:	f3 0f 10 5c 24 74    	movss  xmm3,DWORD PTR [rsp+0x74]
  8ca1c6:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca1ca:	41 0f 28 d3          	movaps xmm2,xmm11
  8ca1ce:	f3 0f 59 d7          	mulss  xmm2,xmm7
  8ca1d2:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca1d6:	41 0f 28 d5          	movaps xmm2,xmm13
  8ca1da:	f3 44 0f 59 6c 24 5c 	mulss  xmm13,DWORD PTR [rsp+0x5c]
  8ca1e1:	f3 0f 59 d5          	mulss  xmm2,xmm5
  8ca1e5:	f3 0f 11 0c 24       	movss  DWORD PTR [rsp],xmm1
  8ca1ea:	0f 28 c8             	movaps xmm1,xmm0
  8ca1ed:	f3 0f 59 44 24 4c    	mulss  xmm0,DWORD PTR [rsp+0x4c]
  8ca1f3:	f3 0f 59 ce          	mulss  xmm1,xmm6
  8ca1f7:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca1fb:	41 0f 28 d4          	movaps xmm2,xmm12
  8ca1ff:	f3 41 0f 58 c5       	addss  xmm0,xmm13
  8ca204:	f3 44 0f 10 ab d4 00 00 00 	movss  xmm13,DWORD PTR [rbx+0xd4]
  8ca20d:	f3 0f 59 d4          	mulss  xmm2,xmm4
  8ca211:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca215:	41 0f 28 d3          	movaps xmm2,xmm11
  8ca219:	f3 0f 59 d3          	mulss  xmm2,xmm3
  8ca21d:	f3 0f 58 ca          	addss  xmm1,xmm2
  8ca221:	f3 0f 10 54 24 48    	movss  xmm2,DWORD PTR [rsp+0x48]
  8ca227:	f3 44 0f 59 f2       	mulss  xmm14,xmm2
  8ca22c:	f3 0f 11 4c 24 04    	movss  DWORD PTR [rsp+0x4],xmm1
  8ca232:	f3 0f 10 4c 24 58    	movss  xmm1,DWORD PTR [rsp+0x58]
  8ca238:	f3 44 0f 59 f9       	mulss  xmm15,xmm1
  8ca23d:	f3 45 0f 58 f7       	addss  xmm14,xmm15
  8ca242:	f3 44 0f 10 7c 24 68 	movss  xmm15,DWORD PTR [rsp+0x68]
  8ca249:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca24e:	f3 44 0f 59 64 24 6c 	mulss  xmm12,DWORD PTR [rsp+0x6c]
  8ca255:	f3 45 0f 58 f7       	addss  xmm14,xmm15
  8ca25a:	f3 44 0f 10 7c 24 78 	movss  xmm15,DWORD PTR [rsp+0x78]
  8ca261:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca266:	f3 44 0f 59 5c 24 7c 	mulss  xmm11,DWORD PTR [rsp+0x7c]
  8ca26d:	f3 41 0f 58 c4       	addss  xmm0,xmm12
  8ca272:	f3 44 0f 10 a3 d8 00 00 00 	movss  xmm12,DWORD PTR [rbx+0xd8]
  8ca27b:	f3 45 0f 58 f7       	addss  xmm14,xmm15
  8ca280:	45 0f 28 f9          	movaps xmm15,xmm9
  8ca284:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca289:	f3 41 0f 58 c3       	addss  xmm0,xmm11
  8ca28e:	f3 44 0f 10 9b dc 00 00 00 	movss  xmm11,DWORD PTR [rbx+0xdc]
  8ca297:	f3 44 0f 11 74 24 08 	movss  DWORD PTR [rsp+0x8],xmm14
  8ca29e:	f3 44 0f 10 b3 d0 00 00 00 	movss  xmm14,DWORD PTR [rbx+0xd0]
  8ca2a7:	f3 0f 11 44 24 0c    	movss  DWORD PTR [rsp+0xc],xmm0
  8ca2ad:	41 0f 28 c2          	movaps xmm0,xmm10
  8ca2b1:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca2b6:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca2bb:	45 0f 28 f8          	movaps xmm15,xmm8
  8ca2bf:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca2c4:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca2c9:	44 0f 28 ff          	movaps xmm15,xmm7
  8ca2cd:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca2d2:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca2d7:	44 0f 28 fd          	movaps xmm15,xmm5
  8ca2db:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca2e0:	f3 0f 11 44 24 10    	movss  DWORD PTR [rsp+0x10],xmm0
  8ca2e6:	0f 28 c6             	movaps xmm0,xmm6
  8ca2e9:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca2ee:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca2f3:	44 0f 28 fc          	movaps xmm15,xmm4
  8ca2f7:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca2fc:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca301:	44 0f 28 fb          	movaps xmm15,xmm3
  8ca305:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca30a:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca30f:	44 0f 28 f9          	movaps xmm15,xmm1
  8ca313:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca318:	f3 44 0f 59 6c 24 5c 	mulss  xmm13,DWORD PTR [rsp+0x5c]
  8ca31f:	f3 0f 11 44 24 14    	movss  DWORD PTR [rsp+0x14],xmm0
  8ca325:	0f 28 c2             	movaps xmm0,xmm2
  8ca328:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca32d:	f3 44 0f 59 74 24 4c 	mulss  xmm14,DWORD PTR [rsp+0x4c]
  8ca334:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca339:	f3 44 0f 10 7c 24 68 	movss  xmm15,DWORD PTR [rsp+0x68]
  8ca340:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca345:	f3 44 0f 59 64 24 6c 	mulss  xmm12,DWORD PTR [rsp+0x6c]
  8ca34c:	f3 45 0f 58 f5       	addss  xmm14,xmm13
  8ca351:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca356:	f3 44 0f 10 7c 24 78 	movss  xmm15,DWORD PTR [rsp+0x78]
  8ca35d:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca362:	f3 44 0f 59 5c 24 7c 	mulss  xmm11,DWORD PTR [rsp+0x7c]
  8ca369:	f3 45 0f 58 f4       	addss  xmm14,xmm12
  8ca36e:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca373:	45 0f 28 f9          	movaps xmm15,xmm9
  8ca377:	f3 45 0f 58 f3       	addss  xmm14,xmm11
  8ca37c:	f3 0f 11 44 24 18    	movss  DWORD PTR [rsp+0x18],xmm0
  8ca382:	41 0f 28 c2          	movaps xmm0,xmm10
  8ca386:	f3 44 0f 11 74 24 1c 	movss  DWORD PTR [rsp+0x1c],xmm14
  8ca38d:	48 8b 04 24          	mov    rax,QWORD PTR [rsp]
  8ca391:	f3 44 0f 10 b3 e0 00 00 00 	movss  xmm14,DWORD PTR [rbx+0xe0]
  8ca39a:	f3 44 0f 10 ab e4 00 00 00 	movss  xmm13,DWORD PTR [rbx+0xe4]
  8ca3a3:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca3a8:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca3ad:	f3 44 0f 10 a3 e8 00 00 00 	movss  xmm12,DWORD PTR [rbx+0xe8]
  8ca3b6:	f3 44 0f 10 9b ec 00 00 00 	movss  xmm11,DWORD PTR [rbx+0xec]
  8ca3bf:	48 89 83 c0 00 00 00 	mov    QWORD PTR [rbx+0xc0],rax
  8ca3c6:	48 8b 44 24 08       	mov    rax,QWORD PTR [rsp+0x8]
  8ca3cb:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca3d0:	45 0f 28 f8          	movaps xmm15,xmm8
  8ca3d4:	48 89 83 c8 00 00 00 	mov    QWORD PTR [rbx+0xc8],rax
  8ca3db:	48 8b 44 24 10       	mov    rax,QWORD PTR [rsp+0x10]
  8ca3e0:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca3e5:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca3ea:	44 0f 28 ff          	movaps xmm15,xmm7
  8ca3ee:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca3f3:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca3f8:	44 0f 28 fd          	movaps xmm15,xmm5
  8ca3fc:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca401:	f3 0f 11 44 24 20    	movss  DWORD PTR [rsp+0x20],xmm0
  8ca407:	0f 28 c6             	movaps xmm0,xmm6
  8ca40a:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca40f:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca414:	44 0f 28 fc          	movaps xmm15,xmm4
  8ca418:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca41d:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca422:	44 0f 28 fb          	movaps xmm15,xmm3
  8ca426:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca42b:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca430:	44 0f 28 f9          	movaps xmm15,xmm1
  8ca434:	f3 45 0f 59 fd       	mulss  xmm15,xmm13
  8ca439:	f3 44 0f 59 6c 24 5c 	mulss  xmm13,DWORD PTR [rsp+0x5c]
  8ca440:	f3 0f 11 44 24 24    	movss  DWORD PTR [rsp+0x24],xmm0
  8ca446:	0f 28 c2             	movaps xmm0,xmm2
  8ca449:	f3 41 0f 59 c6       	mulss  xmm0,xmm14
  8ca44e:	f3 44 0f 59 74 24 4c 	mulss  xmm14,DWORD PTR [rsp+0x4c]
  8ca455:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca45a:	f3 44 0f 10 7c 24 68 	movss  xmm15,DWORD PTR [rsp+0x68]
  8ca461:	f3 45 0f 59 fc       	mulss  xmm15,xmm12
  8ca466:	f3 44 0f 59 64 24 6c 	mulss  xmm12,DWORD PTR [rsp+0x6c]
  8ca46d:	f3 45 0f 58 f5       	addss  xmm14,xmm13
  8ca472:	f3 44 0f 10 ab f0 00 00 00 	movss  xmm13,DWORD PTR [rbx+0xf0]
  8ca47b:	f3 41 0f 59 d5       	mulss  xmm2,xmm13
  8ca480:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca485:	f3 44 0f 10 7c 24 78 	movss  xmm15,DWORD PTR [rsp+0x78]
  8ca48c:	f3 45 0f 59 fb       	mulss  xmm15,xmm11
  8ca491:	f3 44 0f 59 5c 24 7c 	mulss  xmm11,DWORD PTR [rsp+0x7c]
  8ca498:	f3 45 0f 58 f4       	addss  xmm14,xmm12
  8ca49d:	f3 44 0f 10 a3 f4 00 00 00 	movss  xmm12,DWORD PTR [rbx+0xf4]
  8ca4a6:	f3 41 0f 59 cc       	mulss  xmm1,xmm12
  8ca4ab:	f3 45 0f 59 d5       	mulss  xmm10,xmm13
  8ca4b0:	f3 41 0f 58 c7       	addss  xmm0,xmm15
  8ca4b5:	f3 45 0f 59 cc       	mulss  xmm9,xmm12
  8ca4ba:	f3 41 0f 59 f5       	mulss  xmm6,xmm13
  8ca4bf:	f3 41 0f 59 ec       	mulss  xmm5,xmm12
  8ca4c4:	f3 45 0f 58 f3       	addss  xmm14,xmm11
  8ca4c9:	f3 44 0f 59 6c 24 4c 	mulss  xmm13,DWORD PTR [rsp+0x4c]
  8ca4d0:	f3 44 0f 10 9b f8 00 00 00 	movss  xmm11,DWORD PTR [rbx+0xf8]
  8ca4d9:	f3 44 0f 59 64 24 5c 	mulss  xmm12,DWORD PTR [rsp+0x5c]
  8ca4e0:	f3 0f 58 d1          	addss  xmm2,xmm1
  8ca4e4:	f3 0f 11 44 24 28    	movss  DWORD PTR [rsp+0x28],xmm0
  8ca4ea:	f3 0f 10 4c 24 68    	movss  xmm1,DWORD PTR [rsp+0x68]
  8ca4f0:	f3 45 0f 59 c3       	mulss  xmm8,xmm11
  8ca4f5:	f3 41 0f 59 cb       	mulss  xmm1,xmm11
  8ca4fa:	f3 45 0f 58 d1       	addss  xmm10,xmm9
  8ca4ff:	f3 44 0f 11 74 24 2c 	movss  DWORD PTR [rsp+0x2c],xmm14
  8ca506:	f3 41 0f 59 e3       	mulss  xmm4,xmm11
  8ca50b:	f3 0f 58 f5          	addss  xmm6,xmm5
  8ca50f:	f3 44 0f 59 5c 24 6c 	mulss  xmm11,DWORD PTR [rsp+0x6c]
  8ca516:	f3 0f 10 83 fc 00 00 00 	movss  xmm0,DWORD PTR [rbx+0xfc]
  8ca51e:	f3 45 0f 58 ec       	addss  xmm13,xmm12
  8ca523:	f3 0f 59 f8          	mulss  xmm7,xmm0
  8ca527:	f3 0f 58 d1          	addss  xmm2,xmm1
  8ca52b:	f3 0f 10 4c 24 78    	movss  xmm1,DWORD PTR [rsp+0x78]
  8ca531:	f3 0f 59 d8          	mulss  xmm3,xmm0
  8ca535:	f3 45 0f 58 d0       	addss  xmm10,xmm8
  8ca53a:	f3 0f 59 c8          	mulss  xmm1,xmm0
  8ca53e:	f3 0f 58 f4          	addss  xmm6,xmm4
  8ca542:	f3 0f 59 44 24 7c    	mulss  xmm0,DWORD PTR [rsp+0x7c]
  8ca548:	f3 45 0f 58 eb       	addss  xmm13,xmm11
  8ca54d:	f3 44 0f 58 d7       	addss  xmm10,xmm7
  8ca552:	f3 0f 58 f3          	addss  xmm6,xmm3
  8ca556:	f3 0f 58 d1          	addss  xmm2,xmm1
  8ca55a:	f3 44 0f 58 e8       	addss  xmm13,xmm0
  8ca55f:	f3 44 0f 11 54 24 30 	movss  DWORD PTR [rsp+0x30],xmm10
  8ca566:	f3 0f 11 74 24 34    	movss  DWORD PTR [rsp+0x34],xmm6
  8ca56c:	f3 0f 11 54 24 38    	movss  DWORD PTR [rsp+0x38],xmm2
  8ca572:	f3 44 0f 11 6c 24 3c 	movss  DWORD PTR [rsp+0x3c],xmm13
  8ca579:	48 89 83 d0 00 00 00 	mov    QWORD PTR [rbx+0xd0],rax
  8ca580:	48 8b 44 24 18       	mov    rax,QWORD PTR [rsp+0x18]
  8ca585:	48 83 7b 58 00       	cmp    QWORD PTR [rbx+0x58],0x0
  8ca58a:	48 89 83 d8 00 00 00 	mov    QWORD PTR [rbx+0xd8],rax
  8ca591:	48 8b 44 24 20       	mov    rax,QWORD PTR [rsp+0x20]
  8ca596:	48 89 83 e0 00 00 00 	mov    QWORD PTR [rbx+0xe0],rax
  8ca59d:	48 8b 44 24 28       	mov    rax,QWORD PTR [rsp+0x28]
  8ca5a2:	48 89 83 e8 00 00 00 	mov    QWORD PTR [rbx+0xe8],rax
  8ca5a9:	48 8b 44 24 30       	mov    rax,QWORD PTR [rsp+0x30]
  8ca5ae:	48 89 83 f0 00 00 00 	mov    QWORD PTR [rbx+0xf0],rax
  8ca5b5:	48 8b 44 24 38       	mov    rax,QWORD PTR [rsp+0x38]
  8ca5ba:	48 89 83 f8 00 00 00 	mov    QWORD PTR [rbx+0xf8],rax
  8ca5c1:	74 3a                	je     8ca5fd <CItemGold::CItemGold(CResourceManager*, int)+0x73d>
  8ca5c3:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8ca5c6:	4c 8d a4 24 80 00 00 00 	lea    r12,[rsp+0x80]
  8ca5ce:	48 89 df             	mov    rdi,rbx
  8ca5d1:	4c 89 e6             	mov    rsi,r12
  8ca5d4:	ff 90 e0 00 00 00    	call   QWORD PTR [rax+0xe0]
  8ca5da:	4c 8d b4 24 b0 00 00 00 	lea    r14,[rsp+0xb0]
  8ca5e2:	4c 89 e6             	mov    rsi,r12
  8ca5e5:	4c 89 f7             	mov    rdi,r14
  8ca5e8:	e8 bb 8f c8 ff       	call   5535a8 <Ogre::Quaternion::FromRotationMatrix(Ogre::Matrix3 const&)@plt>
  8ca5ed:	48 8b 7b 58          	mov    rdi,QWORD PTR [rbx+0x58]
  8ca5f1:	4c 89 f6             	mov    rsi,r14
  8ca5f4:	48 8b 07             	mov    rax,QWORD PTR [rdi]
  8ca5f7:	ff 90 d0 00 00 00    	call   QWORD PTR [rax+0xd0]
  8ca5fd:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8ca600:	48 89 df             	mov    rdi,rbx
  8ca603:	ff 90 c0 01 00 00    	call   QWORD PTR [rax+0x1c0]
  8ca609:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8ca60c:	48 8d b3 c0 00 00 00 	lea    rsi,[rbx+0xc0]
  8ca613:	48 89 df             	mov    rdi,rbx
  8ca616:	ff 90 b0 01 00 00    	call   QWORD PTR [rax+0x1b0]
  8ca61c:	f3 0f 10 0d ec 3e 70 00 	movss  xmm1,DWORD PTR [rip+0x703eec]        # fce510 <vtable for iInventoryListener+0xd0>
  8ca624:	f3 0f 10 05 40 c1 6f 00 	movss  xmm0,DWORD PTR [rip+0x6fc140]        # fc676c <typeinfo name for iCollision+0x1c>
  8ca62c:	e8 1f 85 3c 00       	call   c92b50 <UTILITIES::randomBetweenVolatile(float, float)>
  8ca631:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  8ca634:	f3 0f 10 15 ac c1 6f 00 	movss  xmm2,DWORD PTR [rip+0x6fc1ac]        # fc67e8 <typeinfo for CPOV+0x18>
  8ca63c:	f3 0f 11 83 30 02 00 00 	movss  DWORD PTR [rbx+0x230],xmm0
  8ca644:	0f 28 ca             	movaps xmm1,xmm2
  8ca647:	0f 28 c2             	movaps xmm0,xmm2
  8ca64a:	48 89 df             	mov    rdi,rbx
  8ca64d:	ff 90 98 00 00 00    	call   QWORD PTR [rax+0x98]
  8ca653:	be 60 1e fd 00       	mov    esi,0xfd1e60
  8ca658:	4c 89 ff             	mov    rdi,r15
  8ca65b:	e8 00 4f 4a 00       	call   d6f560 <CResourceManager::createParticle(wchar_t const*)>
  8ca660:	48 8b bc 24 d0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xd0]
  8ca668:	48 89 83 80 02 00 00 	mov    QWORD PTR [rbx+0x280],rax
  8ca66f:	48 83 ef 18          	sub    rdi,0x18
  8ca673:	48 39 fd             	cmp    rbp,rdi
  8ca676:	0f 85 2c 01 00 00    	jne    8ca7a8 <CItemGold::CItemGold(CResourceManager*, int)+0x8e8>
  8ca67c:	48 81 c4 48 01 00 00 	add    rsp,0x148
  8ca683:	5b                   	pop    rbx
  8ca684:	5d                   	pop    rbp
  8ca685:	41 5c                	pop    r12
  8ca687:	41 5d                	pop    r13
  8ca689:	41 5e                	pop    r14
  8ca68b:	41 5f                	pop    r15
  8ca68d:	c3                   	ret
  8ca68e:	66 90                	xchg   ax,ax
  8ca690:	45 31 ed             	xor    r13d,r13d
  8ca693:	48 83 7b 68 00       	cmp    QWORD PTR [rbx+0x68],0x0
  8ca698:	74 0c                	je     8ca6a6 <CItemGold::CItemGold(CResourceManager*, int)+0x7e6>
  8ca69a:	e8 f1 9d 18 00       	call   a54490 <CMasterResourceManager::getSingleton()>
  8ca69f:	4c 8b a8 98 00 00 00 	mov    r13,QWORD PTR [rax+0x98]
  8ca6a6:	31 c9                	xor    ecx,ecx
  8ca6a8:	31 d2                	xor    edx,edx
  8ca6aa:	31 f6                	xor    esi,esi
  8ca6ac:	bf d0 00 00 00       	mov    edi,0xd0
  8ca6b1:	e8 62 8c c8 ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  8ca6b6:	31 d2                	xor    edx,edx
  8ca6b8:	4c 89 ee             	mov    rsi,r13
  8ca6bb:	48 89 c7             	mov    rdi,rax
  8ca6be:	49 89 c4             	mov    r12,rax
  8ca6c1:	e8 1a e5 19 00       	call   a68be0 <CSoundBank::CSoundBank(CSoundManager&, bool)>
  8ca6c6:	4c 89 a3 d8 01 00 00 	mov    QWORD PTR [rbx+0x1d8],r12
  8ca6cd:	e9 b8 f9 ff ff       	jmp    8ca08a <CItemGold::CItemGold(CResourceManager*, int)+0x1ca>
  8ca6d2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  8ca6d8:	bf b8 72 48 01       	mov    edi,0x14872b8
  8ca6dd:	e8 76 8e c8 ff       	call   553558 <__cxa_guard_acquire@plt>
  8ca6e2:	85 c0                	test   eax,eax
  8ca6e4:	0f 84 46 f8 ff ff    	je     8c9f30 <CItemGold::CItemGold(CResourceManager*, int)+0x70>
  8ca6ea:	bf b8 72 48 01       	mov    edi,0x14872b8
  8ca6ef:	48 c7 05 c6 cb bb 00 58 45 42 01 	mov    QWORD PTR [rip+0xbbcbc6],0x1424558        # 14872c0 <CItemGold::CItemGold(CResourceManager*, int)::g_Gold>
  8ca6fa:	e8 c9 98 c8 ff       	call   553fc8 <__cxa_guard_release@plt>
  8ca6ff:	ba 88 f7 f9 00       	mov    edx,0xf9f788
  8ca704:	be c0 72 48 01       	mov    esi,0x14872c0
  8ca709:	bf d8 48 55 00       	mov    edi,0x5548d8
  8ca70e:	e8 d5 aa c8 ff       	call   5551e8 <__cxa_atexit@plt>
  8ca713:	e9 18 f8 ff ff       	jmp    8c9f30 <CItemGold::CItemGold(CResourceManager*, int)+0x70>
  8ca718:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca71d:	48 85 c0             	test   rax,rax
  8ca720:	0f 84 c1 01 00 00    	je     8ca8e7 <CItemGold::CItemGold(CResourceManager*, int)+0xa27>
  8ca726:	83 c8 ff             	or     eax,0xffffffff
  8ca729:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca72e:	85 c0                	test   eax,eax
  8ca730:	0f 8f 4b f8 ff ff    	jg     8c9f81 <CItemGold::CItemGold(CResourceManager*, int)+0xc1>
  8ca736:	48 8d b4 24 3d 01 00 00 	lea    rsi,[rsp+0x13d]
  8ca73e:	e8 05 8e c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca743:	e9 39 f8 ff ff       	jmp    8c9f81 <CItemGold::CItemGold(CResourceManager*, int)+0xc1>
  8ca748:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca74d:	48 85 c0             	test   rax,rax
  8ca750:	0f 84 ad 01 00 00    	je     8ca903 <CItemGold::CItemGold(CResourceManager*, int)+0xa43>
  8ca756:	83 c8 ff             	or     eax,0xffffffff
  8ca759:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca75e:	85 c0                	test   eax,eax
  8ca760:	0f 8f 0c f9 ff ff    	jg     8ca072 <CItemGold::CItemGold(CResourceManager*, int)+0x1b2>
  8ca766:	48 8d b4 24 39 01 00 00 	lea    rsi,[rsp+0x139]
  8ca76e:	e8 d5 8d c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca773:	e9 fa f8 ff ff       	jmp    8ca072 <CItemGold::CItemGold(CResourceManager*, int)+0x1b2>
  8ca778:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca77d:	48 85 c0             	test   rax,rax
  8ca780:	0f 84 6f 01 00 00    	je     8ca8f5 <CItemGold::CItemGold(CResourceManager*, int)+0xa35>
  8ca786:	83 c8 ff             	or     eax,0xffffffff
  8ca789:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca78e:	85 c0                	test   eax,eax
  8ca790:	0f 8f 53 f9 ff ff    	jg     8ca0e9 <CItemGold::CItemGold(CResourceManager*, int)+0x229>
  8ca796:	48 8d b4 24 38 01 00 00 	lea    rsi,[rsp+0x138]
  8ca79e:	e8 a5 8d c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca7a3:	e9 41 f9 ff ff       	jmp    8ca0e9 <CItemGold::CItemGold(CResourceManager*, int)+0x229>
  8ca7a8:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca7ad:	48 85 c0             	test   rax,rax
  8ca7b0:	0f 84 69 01 00 00    	je     8ca91f <CItemGold::CItemGold(CResourceManager*, int)+0xa5f>
  8ca7b6:	83 c8 ff             	or     eax,0xffffffff
  8ca7b9:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca7be:	85 c0                	test   eax,eax
  8ca7c0:	0f 8f b6 fe ff ff    	jg     8ca67c <CItemGold::CItemGold(CResourceManager*, int)+0x7bc>
  8ca7c6:	48 8d b4 24 37 01 00 00 	lea    rsi,[rsp+0x137]
  8ca7ce:	e8 75 8d c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca7d3:	e9 a4 fe ff ff       	jmp    8ca67c <CItemGold::CItemGold(CResourceManager*, int)+0x7bc>
  8ca7d8:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca7dd:	48 85 c0             	test   rax,rax
  8ca7e0:	0f 84 2b 01 00 00    	je     8ca911 <CItemGold::CItemGold(CResourceManager*, int)+0xa51>
  8ca7e6:	83 c8 ff             	or     eax,0xffffffff
  8ca7e9:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca7ee:	85 c0                	test   eax,eax
  8ca7f0:	0f 8f 20 f8 ff ff    	jg     8ca016 <CItemGold::CItemGold(CResourceManager*, int)+0x156>
  8ca7f6:	48 8d b4 24 3b 01 00 00 	lea    rsi,[rsp+0x13b]
  8ca7fe:	e8 45 8d c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca803:	e9 0e f8 ff ff       	jmp    8ca016 <CItemGold::CItemGold(CResourceManager*, int)+0x156>
  8ca808:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca80d:	48 85 c0             	test   rax,rax
  8ca810:	0f 84 17 01 00 00    	je     8ca92d <CItemGold::CItemGold(CResourceManager*, int)+0xa6d>
  8ca816:	83 c8 ff             	or     eax,0xffffffff
  8ca819:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca81e:	85 c0                	test   eax,eax
  8ca820:	0f 8f 05 f8 ff ff    	jg     8ca02b <CItemGold::CItemGold(CResourceManager*, int)+0x16b>
  8ca826:	48 8d b4 24 3a 01 00 00 	lea    rsi,[rsp+0x13a]
  8ca82e:	e8 15 8d c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca833:	e9 f3 f7 ff ff       	jmp    8ca02b <CItemGold::CItemGold(CResourceManager*, int)+0x16b>
  8ca838:	b8 c8 41 55 00       	mov    eax,0x5541c8
  8ca83d:	48 85 c0             	test   rax,rax
  8ca840:	74 42                	je     8ca884 <CItemGold::CItemGold(CResourceManager*, int)+0x9c4>
  8ca842:	83 c8 ff             	or     eax,0xffffffff
  8ca845:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  8ca84a:	85 c0                	test   eax,eax
  8ca84c:	0f 8f af f7 ff ff    	jg     8ca001 <CItemGold::CItemGold(CResourceManager*, int)+0x141>
  8ca852:	48 8d b4 24 3c 01 00 00 	lea    rsi,[rsp+0x13c]
  8ca85a:	e8 e9 8c c8 ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  8ca85f:	e9 9d f7 ff ff       	jmp    8ca001 <CItemGold::CItemGold(CResourceManager*, int)+0x141>
  8ca864:	49 89 c6             	mov    r14,rax
  8ca867:	4c 89 ef             	mov    rdi,r13
  8ca86a:	e8 69 a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca86f:	48 89 df             	mov    rdi,rbx
  8ca872:	e8 19 77 ff ff       	call   8c1f90 <CItem::~CItem()>
  8ca877:	4c 89 f7             	mov    rdi,r14
  8ca87a:	e8 19 9c c8 ff       	call   554498 <_Unwind_Resume@plt>
  8ca87f:	49 89 c6             	mov    r14,rax
  8ca882:	eb eb                	jmp    8ca86f <CItemGold::CItemGold(CResourceManager*, int)+0x9af>
  8ca884:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca887:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca88a:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca88d:	eb bb                	jmp    8ca84a <CItemGold::CItemGold(CResourceManager*, int)+0x98a>
  8ca88f:	4c 89 e7             	mov    rdi,r12
  8ca892:	49 89 c6             	mov    r14,rax
  8ca895:	e8 3e a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca89a:	eb d3                	jmp    8ca86f <CItemGold::CItemGold(CResourceManager*, int)+0x9af>
  8ca89c:	eb f1                	jmp    8ca88f <CItemGold::CItemGold(CResourceManager*, int)+0x9cf>
  8ca89e:	66 90                	xchg   ax,ax
  8ca8a0:	eb dd                	jmp    8ca87f <CItemGold::CItemGold(CResourceManager*, int)+0x9bf>
  8ca8a2:	4c 89 e7             	mov    rdi,r12
  8ca8a5:	49 89 c6             	mov    r14,rax
  8ca8a8:	e8 2b a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca8ad:	48 89 ef             	mov    rdi,rbp
  8ca8b0:	e8 23 a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca8b5:	eb b0                	jmp    8ca867 <CItemGold::CItemGold(CResourceManager*, int)+0x9a7>
  8ca8b7:	49 89 c6             	mov    r14,rax
  8ca8ba:	eb f1                	jmp    8ca8ad <CItemGold::CItemGold(CResourceManager*, int)+0x9ed>
  8ca8bc:	48 89 ef             	mov    rdi,rbp
  8ca8bf:	49 89 c6             	mov    r14,rax
  8ca8c2:	e8 11 a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca8c7:	eb 9e                	jmp    8ca867 <CItemGold::CItemGold(CResourceManager*, int)+0x9a7>
  8ca8c9:	eb b4                	jmp    8ca87f <CItemGold::CItemGold(CResourceManager*, int)+0x9bf>
  8ca8cb:	4c 89 e7             	mov    rdi,r12
  8ca8ce:	49 89 c6             	mov    r14,rax
  8ca8d1:	e8 02 a0 c8 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  8ca8d6:	eb 8f                	jmp    8ca867 <CItemGold::CItemGold(CResourceManager*, int)+0x9a7>
  8ca8d8:	eb 8a                	jmp    8ca864 <CItemGold::CItemGold(CResourceManager*, int)+0x9a4>
  8ca8da:	4c 89 e7             	mov    rdi,r12
  8ca8dd:	49 89 c6             	mov    r14,rax
  8ca8e0:	e8 83 a9 c8 ff       	call   555268 <Ogre::NedAllocImpl::deallocBytes(void*)@plt>
  8ca8e5:	eb 88                	jmp    8ca86f <CItemGold::CItemGold(CResourceManager*, int)+0x9af>
  8ca8e7:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca8ea:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca8ed:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca8f0:	e9 39 fe ff ff       	jmp    8ca72e <CItemGold::CItemGold(CResourceManager*, int)+0x86e>
  8ca8f5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca8f8:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca8fb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca8fe:	e9 8b fe ff ff       	jmp    8ca78e <CItemGold::CItemGold(CResourceManager*, int)+0x8ce>
  8ca903:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca906:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca909:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca90c:	e9 4d fe ff ff       	jmp    8ca75e <CItemGold::CItemGold(CResourceManager*, int)+0x89e>
  8ca911:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca914:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca917:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca91a:	e9 cf fe ff ff       	jmp    8ca7ee <CItemGold::CItemGold(CResourceManager*, int)+0x92e>
  8ca91f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca922:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca925:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca928:	e9 91 fe ff ff       	jmp    8ca7be <CItemGold::CItemGold(CResourceManager*, int)+0x8fe>
  8ca92d:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  8ca930:	8d 50 ff             	lea    edx,[rax-0x1]
  8ca933:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  8ca936:	e9 e3 fe ff ff       	jmp    8ca81e <CItemGold::CItemGold(CResourceManager*, int)+0x95e>
  8ca93b:	90                   	nop
  8ca93c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

