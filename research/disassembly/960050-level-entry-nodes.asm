# Original ELF SHA-256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address-scoped excerpt of the user-supplied archive (2),
# original-analysis/full-intel-disassembly.asm; not a fresh ELF export.

# Range [0x960050, 0x960197)
  960052:	c7 83 5c 01 00 00 00 00 80 bf 	mov    DWORD PTR [rbx+0x15c],0xbf800000
  96005c:	c7 83 60 01 00 00 00 00 80 bf 	mov    DWORD PTR [rbx+0x160],0xbf800000
  960066:	44 8b 8c 24 a4 00 00 00 	mov    r9d,DWORD PTR [rsp+0xa4]
  96006e:	45 85 c9             	test   r9d,r9d
  960071:	0f 8e 7f 1e 00 00    	jle    961ef6 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x2da6>
  960077:	48 8d 83 d8 00 00 00 	lea    rax,[rbx+0xd8]
  96007e:	4c 8d bb 08 01 00 00 	lea    r15,[rbx+0x108]
  960085:	4c 8d b3 f0 00 00 00 	lea    r14,[rbx+0xf0]
  96008c:	48 c7 84 24 98 00 00 00 00 00 00 00 	mov    QWORD PTR [rsp+0x98],0x0
  960098:	c7 44 24 78 00 00 00 00 	mov    DWORD PTR [rsp+0x78],0x0
  9600a0:	48 89 84 24 a8 00 00 00 	mov    QWORD PTR [rsp+0xa8],rax
  9600a8:	c7 84 24 94 00 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x94],0x0
  9600b3:	c7 84 24 90 00 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x90],0x0
  9600be:	c7 84 24 8c 00 00 00 00 00 80 3f 	mov    DWORD PTR [rsp+0x8c],0x3f800000
  9600c9:	c7 84 24 88 00 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x88],0x0
  9600d4:	c7 84 24 84 00 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x84],0x0
  9600df:	c7 44 24 74 00 00 00 00 	mov    DWORD PTR [rsp+0x74],0x0
  9600e7:	c6 44 24 67 00       	mov    BYTE PTR [rsp+0x67],0x0
  9600ec:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  9600f0:	8b 54 24 74          	mov    edx,DWORD PTR [rsp+0x74]
  9600f4:	39 53 1c             	cmp    DWORD PTR [rbx+0x1c],edx
  9600f7:	0f 87 3b 0e 00 00    	ja     960f38 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1de8>
  9600fd:	48 8b 43 10          	mov    rax,QWORD PTR [rbx+0x10]
  960101:	48 8b 00             	mov    rax,QWORD PTR [rax]
  960104:	48 8d 94 24 7d 03 00 00 	lea    rdx,[rsp+0x37d]
  96010c:	48 8d bc 24 70 02 00 00 	lea    rdi,[rsp+0x270]
  960114:	be 00 76 fa 00       	mov    esi,0xfa7600
  960119:	48 c7 84 24 c0 01 00 00 00 00 00 00 	mov    QWORD PTR [rsp+0x1c0],0x0
  960125:	c7 84 24 c8 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x1c8],0x0
  960130:	c7 84 24 cc 01 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x1cc],0x0
  96013b:	c7 84 24 d0 01 00 00 e8 03 00 00 	mov    DWORD PTR [rsp+0x1d0],0x3e8
  960146:	48 89 44 24 40       	mov    QWORD PTR [rsp+0x40],rax
  96014b:	e8 08 5d bf ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  960150:	48 8b 7c 24 40       	mov    rdi,QWORD PTR [rsp+0x40]
  960155:	48 8d 94 24 c0 01 00 00 	lea    rdx,[rsp+0x1c0]
  96015d:	48 8d b4 24 70 02 00 00 	lea    rsi,[rsp+0x270]
  960165:	e8 86 ba de ff       	call   74bbf0 <CEditorScene::GetObjectsCreatedByADescriptor(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, TArrayList<CEditorBaseObject*>*)>
  96016a:	48 8d bc 24 70 02 00 00 	lea    rdi,[rsp+0x270]
  960172:	e8 61 47 bf ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  960177:	8b 8c 24 c8 01 00 00 	mov    ecx,DWORD PTR [rsp+0x1c8]
  96017e:	83 f9 00             	cmp    ecx,0x0
  960181:	89 4c 24 30          	mov    DWORD PTR [rsp+0x30],ecx
  960185:	0f 84 e5 01 00 00    	je     960370 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1220>
  96018b:	0f 8e df 01 00 00    	jle    960370 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1220>
  960191:	45 31 ed             	xor    r13d,r13d
  960194:	31 ed                	xor    ebp,ebp
  960196:	e9 62 01 00 00       	jmp    9602fd <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11ad>

# Range [0x9602f0, 0x960330)
  9602f0:	83 c5 01             	add    ebp,0x1
  9602f3:	49 83 c5 08          	add    r13,0x8
  9602f7:	39 6c 24 30          	cmp    DWORD PTR [rsp+0x30],ebp
  9602fb:	7e 73                	jle    960370 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1220>
  9602fd:	39 ac 24 cc 01 00 00 	cmp    DWORD PTR [rsp+0x1cc],ebp
  960304:	0f 86 96 fe ff ff    	jbe    9601a0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1050>
  96030a:	4c 89 e8             	mov    rax,r13
  96030d:	48 03 84 24 c0 01 00 00 	add    rax,QWORD PTR [rsp+0x1c0]
  960315:	e9 8e fe ff ff       	jmp    9601a8 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1058>
  96031a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  960320:	41 8b 84 24 0c 01 00 00 	mov    eax,DWORD PTR [r12+0x10c]
  960328:	ff 24 c5 d0 6a fd 00 	jmp    QWORD PTR [rax*8+0xfd6ad0]
  96032f:	90                   	nop

# Range [0x960910, 0x960a78)
  960910:	8b 74 24 4c          	mov    esi,DWORD PTR [rsp+0x4c]
  960914:	85 f6                	test   esi,esi
  960916:	75 44                	jne    96095c <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x180c>
  960918:	8b 84 24 10 02 00 00 	mov    eax,DWORD PTR [rsp+0x210]
  96091f:	89 83 40 01 00 00    	mov    DWORD PTR [rbx+0x140],eax
  960925:	8b 84 24 14 02 00 00 	mov    eax,DWORD PTR [rsp+0x214]
  96092c:	89 83 44 01 00 00    	mov    DWORD PTR [rbx+0x144],eax
  960932:	8b 84 24 18 02 00 00 	mov    eax,DWORD PTR [rsp+0x218]
  960939:	f3 0f 11 93 64 01 00 00 	movss  DWORD PTR [rbx+0x164],xmm2
  960941:	f3 0f 11 a3 68 01 00 00 	movss  DWORD PTR [rbx+0x168],xmm4
  960949:	f3 0f 11 8b 6c 01 00 00 	movss  DWORD PTR [rbx+0x16c],xmm1
  960951:	89 83 48 01 00 00    	mov    DWORD PTR [rbx+0x148],eax
  960957:	c6 44 24 67 01       	mov    BYTE PTR [rsp+0x67],0x1
  96095c:	48 83 bb e0 01 00 00 00 	cmp    QWORD PTR [rbx+0x1e0],0x0
  960964:	0f 84 86 f9 ff ff    	je     9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  96096a:	c7 84 24 30 02 00 00 00 00 80 3f 	mov    DWORD PTR [rsp+0x230],0x3f800000
  960975:	c7 84 24 34 02 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x234],0x0
  960980:	48 8d 8c 24 30 02 00 00 	lea    rcx,[rsp+0x230]
  960988:	c7 84 24 38 02 00 00 00 00 80 bf 	mov    DWORD PTR [rsp+0x238],0xbf800000
  960993:	48 8b bb e0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1e0]
  96099a:	48 8d 94 24 10 02 00 00 	lea    rdx,[rsp+0x210]
  9609a2:	45 31 c9             	xor    r9d,r9d
  9609a5:	41 b8 01 00 00 00    	mov    r8d,0x1
  9609ab:	be 15 00 00 00       	mov    esi,0x15
  9609b0:	e8 5b 7f fc ff       	call   928910 <CAutomap::addTile(int, Ogre::Vector3 const&, Ogre::Vector3 const&, bool, bool)>
  9609b5:	e9 36 f9 ff ff       	jmp    9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  9609ba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
  9609c0:	83 7c 24 4c 03       	cmp    DWORD PTR [rsp+0x4c],0x3
  9609c5:	74 0e                	je     9609d5 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1885>
  9609c7:	83 7c 24 4c 01       	cmp    DWORD PTR [rsp+0x4c],0x1
  9609cc:	74 07                	je     9609d5 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1885>
  9609ce:	80 7c 24 67 00       	cmp    BYTE PTR [rsp+0x67],0x0
  9609d3:	75 44                	jne    960a19 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x18c9>
  9609d5:	8b 84 24 10 02 00 00 	mov    eax,DWORD PTR [rsp+0x210]
  9609dc:	89 83 40 01 00 00    	mov    DWORD PTR [rbx+0x140],eax
  9609e2:	8b 84 24 14 02 00 00 	mov    eax,DWORD PTR [rsp+0x214]
  9609e9:	89 83 44 01 00 00    	mov    DWORD PTR [rbx+0x144],eax
  9609ef:	8b 84 24 18 02 00 00 	mov    eax,DWORD PTR [rsp+0x218]
  9609f6:	f3 0f 11 93 64 01 00 00 	movss  DWORD PTR [rbx+0x164],xmm2
  9609fe:	f3 0f 11 a3 68 01 00 00 	movss  DWORD PTR [rbx+0x168],xmm4
  960a06:	f3 0f 11 8b 6c 01 00 00 	movss  DWORD PTR [rbx+0x16c],xmm1
  960a0e:	89 83 48 01 00 00    	mov    DWORD PTR [rbx+0x148],eax
  960a14:	c6 44 24 67 01       	mov    BYTE PTR [rsp+0x67],0x1
  960a19:	48 83 bb e0 01 00 00 00 	cmp    QWORD PTR [rbx+0x1e0],0x0
  960a21:	0f 84 c9 f8 ff ff    	je     9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  960a27:	c7 84 24 40 02 00 00 00 00 80 3f 	mov    DWORD PTR [rsp+0x240],0x3f800000
  960a32:	c7 84 24 44 02 00 00 00 00 00 00 	mov    DWORD PTR [rsp+0x244],0x0
  960a3d:	48 8d 8c 24 40 02 00 00 	lea    rcx,[rsp+0x240]
  960a45:	c7 84 24 48 02 00 00 00 00 80 bf 	mov    DWORD PTR [rsp+0x248],0xbf800000
  960a50:	48 8b bb e0 01 00 00 	mov    rdi,QWORD PTR [rbx+0x1e0]
  960a57:	48 8d 94 24 10 02 00 00 	lea    rdx,[rsp+0x210]
  960a5f:	45 31 c9             	xor    r9d,r9d
  960a62:	41 b8 01 00 00 00    	mov    r8d,0x1
  960a68:	be 14 00 00 00       	mov    esi,0x14
  960a6d:	e8 9e 7e fc ff       	call   928910 <CAutomap::addTile(int, Ogre::Vector3 const&, Ogre::Vector3 const&, bool, bool)>
  960a72:	e9 79 f8 ff ff       	jmp    9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>
  960a77:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]

# Range [0x960ad8, 0x960b2a)
  960ad8:	83 7c 24 4c 03       	cmp    DWORD PTR [rsp+0x4c],0x3
  960add:	0f 84 b5 03 00 00    	je     960e98 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1d48>
  960ae3:	8b 8c 24 10 02 00 00 	mov    ecx,DWORD PTR [rsp+0x210]
  960aea:	8b 94 24 14 02 00 00 	mov    edx,DWORD PTR [rsp+0x214]
  960af1:	8b 84 24 18 02 00 00 	mov    eax,DWORD PTR [rsp+0x218]
  960af8:	89 4c 24 78          	mov    DWORD PTR [rsp+0x78],ecx
  960afc:	89 94 24 90 00 00 00 	mov    DWORD PTR [rsp+0x90],edx
  960b03:	f3 0f 11 94 24 84 00 00 00 	movss  DWORD PTR [rsp+0x84],xmm2
  960b0c:	89 84 24 94 00 00 00 	mov    DWORD PTR [rsp+0x94],eax
  960b13:	f3 0f 11 a4 24 88 00 00 00 	movss  DWORD PTR [rsp+0x88],xmm4
  960b1c:	f3 0f 11 8c 24 8c 00 00 00 	movss  DWORD PTR [rsp+0x8c],xmm1
  960b25:	e9 c6 f7 ff ff       	jmp    9602f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x11a0>

# Range [0x960c7c, 0x960d1b)
  960c85:	83 44 24 74 01       	add    DWORD PTR [rsp+0x74],0x1
  960c8a:	48 83 84 24 98 00 00 00 08 	add    QWORD PTR [rsp+0x98],0x8
  960c93:	8b 44 24 74          	mov    eax,DWORD PTR [rsp+0x74]
  960c97:	39 84 24 a4 00 00 00 	cmp    DWORD PTR [rsp+0xa4],eax
  960c9e:	0f 8f 4c f4 ff ff    	jg     9600f0 <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0xfa0>
  960ca4:	be 88 5d fd 00       	mov    esi,0xfd5d88
  960ca9:	48 89 df             	mov    rdi,rbx
  960cac:	e8 7f e1 ff ff       	call   95ee30 <CLevel::popTime(wchar_t const*)>
  960cb1:	80 7c 24 67 00       	cmp    BYTE PTR [rsp+0x67],0x0
  960cb6:	75 63                	jne    960d1b <CLevel::loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::allocator<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > >*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)+0x1bcb>
  960cb8:	f3 0f 10 44 24 78    	movss  xmm0,DWORD PTR [rsp+0x78]
  960cbe:	f3 0f 11 83 40 01 00 00 	movss  DWORD PTR [rbx+0x140],xmm0
  960cc6:	f3 0f 10 8c 24 90 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x90]
  960ccf:	f3 0f 11 8b 44 01 00 00 	movss  DWORD PTR [rbx+0x144],xmm1
  960cd7:	f3 0f 10 9c 24 94 00 00 00 	movss  xmm3,DWORD PTR [rsp+0x94]
  960ce0:	f3 0f 11 9b 48 01 00 00 	movss  DWORD PTR [rbx+0x148],xmm3
  960ce8:	f3 0f 10 84 24 84 00 00 00 	movss  xmm0,DWORD PTR [rsp+0x84]
  960cf1:	f3 0f 11 83 64 01 00 00 	movss  DWORD PTR [rbx+0x164],xmm0
  960cf9:	f3 0f 10 8c 24 88 00 00 00 	movss  xmm1,DWORD PTR [rsp+0x88]
  960d02:	f3 0f 11 8b 68 01 00 00 	movss  DWORD PTR [rbx+0x168],xmm1
  960d0a:	f3 0f 10 9c 24 8c 00 00 00 	movss  xmm3,DWORD PTR [rsp+0x8c]
  960d13:	f3 0f 11 9b 6c 01 00 00 	movss  DWORD PTR [rbx+0x16c],xmm3
