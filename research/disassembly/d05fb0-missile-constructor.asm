0000000000d05fb0 <CMissile::CMissile(CResourceManager*)>:
  d05fb0:	41 55                	push   r13
  d05fb2:	31 d2                	xor    edx,edx
  d05fb4:	41 54                	push   r12
  d05fb6:	55                   	push   rbp
  d05fb7:	53                   	push   rbx
  d05fb8:	48 89 fb             	mov    rbx,rdi
  d05fbb:	48 8d ab 20 01 00 00 	lea    rbp,[rbx+0x120]
  d05fc2:	48 83 ec 08          	sub    rsp,0x8
  d05fc6:	e8 85 1a ce ff       	call   9e7a50 <CPositionableObject::CPositionableObject(CResourceManager*, Ogre::SceneManager*)>
  d05fcb:	48 c7 03 50 66 ff 00 	mov    QWORD PTR [rbx],0xff6650
  d05fd2:	31 c0                	xor    eax,eax
  d05fd4:	48 c7 44 05 00 58 45 42 01 	mov    QWORD PTR [rbp+rax*1+0x0],0x1424558
  d05fdd:	48 83 c0 08          	add    rax,0x8
  d05fe1:	48 83 f8 20          	cmp    rax,0x20
  d05fe5:	75 ed                	jne    d05fd4 <CMissile::CMissile(CResourceManager*)+0x24>
  d05fe7:	c6 83 42 01 00 00 00 	mov    BYTE PTR [rbx+0x142],0x0
  d05fee:	c6 83 43 01 00 00 01 	mov    BYTE PTR [rbx+0x143],0x1
  d05ff5:	48 89 df             	mov    rdi,rbx
  d05ff8:	c6 83 44 01 00 00 00 	mov    BYTE PTR [rbx+0x144],0x0
  d05fff:	c7 83 6c 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x16c],0x0
  d06009:	c7 83 70 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x170],0x0
  d06013:	48 c7 83 c8 01 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x1c8],0x0
  d0601e:	c7 83 d0 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x1d0],0x0
  d06028:	c7 83 d4 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x1d4],0x0
  d06032:	c7 83 d8 01 00 00 0a 00 00 00 	mov    DWORD PTR [rbx+0x1d8],0xa
  d0603c:	48 c7 83 f0 01 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x1f0],0x0
  d06047:	c7 83 f8 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x1f8],0x0
  d06051:	c7 83 fc 01 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x1fc],0x0
  d0605b:	c7 83 00 02 00 00 0a 00 00 00 	mov    DWORD PTR [rbx+0x200],0xa
  d06065:	48 c7 83 10 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x210],0x0
  d06070:	48 c7 83 20 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x220],0x0
  d0607b:	c7 83 28 02 00 00 ff ff ff ff 	mov    DWORD PTR [rbx+0x228],0xffffffff
  d06085:	48 c7 83 30 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x230],0x0
  d06090:	c7 83 38 02 00 00 ff ff ff ff 	mov    DWORD PTR [rbx+0x238],0xffffffff
  d0609a:	48 c7 83 40 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x240],0x0
  d060a5:	c7 83 48 02 00 00 ff ff ff ff 	mov    DWORD PTR [rbx+0x248],0xffffffff
  d060af:	c7 83 64 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x264],0x0
  d060b9:	c7 83 68 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x268],0x0
  d060c3:	c7 83 6c 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x26c],0x0
  d060cd:	c7 83 70 02 00 00 00 00 80 3e 	mov    DWORD PTR [rbx+0x270],0x3e800000
  d060d7:	c7 83 74 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x274],0x0
  d060e1:	c7 83 78 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x278],0x0
  d060eb:	c7 83 84 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x284],0x0
  d060f5:	c7 83 88 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x288],0x0
  d060ff:	c7 83 8c 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x28c],0x0
  d06109:	48 c7 83 98 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x298],0x0
  d06114:	c7 83 a0 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x2a0],0x0
  d0611e:	c7 83 a4 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x2a4],0x0
  d06128:	c7 83 a8 02 00 00 0a 00 00 00 	mov    DWORD PTR [rbx+0x2a8],0xa
  d06132:	48 c7 83 b0 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x2b0],0x0
  d0613d:	c7 83 b8 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x2b8],0x0
  d06147:	c7 83 bc 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x2bc],0x0
  d06151:	c7 83 c0 02 00 00 0a 00 00 00 	mov    DWORD PTR [rbx+0x2c0],0xa
  d0615b:	48 c7 83 c8 02 00 00 58 45 42 01 	mov    QWORD PTR [rbx+0x2c8],0x1424558
  d06166:	c7 83 d0 02 00 00 00 00 00 00 	mov    DWORD PTR [rbx+0x2d0],0x0
  d06170:	e8 db a4 ff ff       	call   d00650 <CMissile::initialize()>
  d06175:	48 83 c4 08          	add    rsp,0x8
  d06179:	5b                   	pop    rbx
  d0617a:	5d                   	pop    rbp
  d0617b:	41 5c                	pop    r12
  d0617d:	41 5d                	pop    r13
  d0617f:	c3                   	ret
  d06180:	48 8d bb c8 02 00 00 	lea    rdi,[rbx+0x2c8]
  d06187:	49 89 c5             	mov    r13,rax
  d0618a:	e8 49 e7 84 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d0618f:	48 8b bb b0 02 00 00 	mov    rdi,QWORD PTR [rbx+0x2b0]
  d06196:	48 85 ff             	test   rdi,rdi
  d06199:	74 10                	je     d061ab <CMissile::CMissile(CResourceManager*)+0x1fb>
  d0619b:	e8 98 d4 84 ff       	call   553638 <operator delete[](void*)@plt>
  d061a0:	48 c7 83 b0 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x2b0],0x0
  d061ab:	48 8b bb 98 02 00 00 	mov    rdi,QWORD PTR [rbx+0x298]
  d061b2:	48 85 ff             	test   rdi,rdi
  d061b5:	74 10                	je     d061c7 <CMissile::CMissile(CResourceManager*)+0x217>
  d061b7:	e8 7c d4 84 ff       	call   553638 <operator delete[](void*)@plt>
  d061bc:	48 c7 83 98 02 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x298],0x0
  d061c7:	48 8d bb 40 02 00 00 	lea    rdi,[rbx+0x240]
  d061ce:	e8 7d b9 88 ff       	call   591b50 <TSafePointer<CCharacter>::~TSafePointer()>
  d061d3:	48 8d bb 30 02 00 00 	lea    rdi,[rbx+0x230]
  d061da:	e8 b1 05 00 00       	call   d06790 <TSafePointer<CPositionableObject>::~TSafePointer()>
  d061df:	48 8d bb 20 02 00 00 	lea    rdi,[rbx+0x220]
  d061e6:	e8 d5 fd ac ff       	call   7d5fc0 <TSafePointer<CBaseUnit>::~TSafePointer()>
  d061eb:	48 8b bb f0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1f0]
  d061f2:	48 85 ff             	test   rdi,rdi
  d061f5:	74 10                	je     d06207 <CMissile::CMissile(CResourceManager*)+0x257>
  d061f7:	e8 3c d4 84 ff       	call   553638 <operator delete[](void*)@plt>
  d061fc:	48 c7 83 f0 01 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x1f0],0x0
  d06207:	48 8b bb c8 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1c8]
  d0620e:	48 85 ff             	test   rdi,rdi
  d06211:	74 10                	je     d06223 <CMissile::CMissile(CResourceManager*)+0x273>
  d06213:	e8 20 d4 84 ff       	call   553638 <operator delete[](void*)@plt>
  d06218:	48 c7 83 c8 01 00 00 00 00 00 00 	mov    QWORD PTR [rbx+0x1c8],0x0
  d06223:	4c 8d 65 20          	lea    r12,[rbp+0x20]
  d06227:	49 39 ec             	cmp    r12,rbp
  d0622a:	74 0e                	je     d0623a <CMissile::CMissile(CResourceManager*)+0x28a>
  d0622c:	49 83 ec 08          	sub    r12,0x8
  d06230:	4c 89 e7             	mov    rdi,r12
  d06233:	e8 a0 e6 84 ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  d06238:	eb ed                	jmp    d06227 <CMissile::CMissile(CResourceManager*)+0x277>
  d0623a:	48 89 df             	mov    rdi,rbx
  d0623d:	e8 1e 0f ce ff       	call   9e7160 <CPositionableObject::~CPositionableObject()>
  d06242:	4c 89 ef             	mov    rdi,r13
  d06245:	e8 4e e2 84 ff       	call   554498 <_Unwind_Resume@plt>
  d0624a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

