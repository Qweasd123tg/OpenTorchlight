# Targeted Intel-syntax slice; NOT an ELF or a complete function where noted.
# Source: earlier user-supplied OpenTorchlight-gpt-pro(2).zip, original-analysis/full-intel-disassembly.asm
# Original ELF SHA-256 reported by that package (ELF not supplied):
# 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b
# Address interval [0xa17200, 0xa172ac); source instructions unchanged.
  a17203:	4c 89 e6             	mov    rsi,r12
  a17206:	4c 89 f7             	mov    rdi,r14
  a17209:	e8 d2 fe fc ff       	call   9e70e0 <CPositionableObject::setPosition(Ogre::Vector3 const&)>
  a1720e:	49 8b 06             	mov    rax,QWORD PTR [r14]
  a17211:	4c 89 ee             	mov    rsi,r13
  a17214:	4c 89 f7             	mov    rdi,r14
  a17217:	ff 90 08 01 00 00    	call   QWORD PTR [rax+0x108]
  a1721d:	31 c9                	xor    ecx,ecx
  a1721f:	ba 80 e2 fc 00       	mov    edx,0xfce280
  a17224:	be 60 92 fc 00       	mov    esi,0xfc9260
  a17229:	4c 89 f7             	mov    rdi,r14
  a1722c:	e8 27 e5 b3 ff       	call   555758 <__dynamic_cast@plt>
  a17231:	48 85 c0             	test   rax,rax
  a17234:	49 89 c7             	mov    r15,rax
  a17237:	0f 84 bc 03 00 00    	je     a175f9 <CUnitSpawner::spawnUnitByIndex(unsigned int)+0xe59>
  a1723d:	80 bb 78 01 00 00 00 	cmp    BYTE PTR [rbx+0x178],0x0
  a17244:	75 0a                	jne    a17250 <CUnitSpawner::spawnUnitByIndex(unsigned int)+0xab0>
  a17246:	c7 80 54 04 00 00 00 00 00 00 	mov    DWORD PTR [rax+0x454],0x0
  a17250:	80 bb 79 01 00 00 00 	cmp    BYTE PTR [rbx+0x179],0x0
  a17257:	75 10                	jne    a17269 <CUnitSpawner::spawnUnitByIndex(unsigned int)+0xac9>
  a17259:	41 c6 87 03 07 00 00 01 	mov    BYTE PTR [r15+0x703],0x1
  a17261:	41 c6 87 04 07 00 00 01 	mov    BYTE PTR [r15+0x704],0x1
  a17269:	80 bb c4 01 00 00 00 	cmp    BYTE PTR [rbx+0x1c4],0x0
  a17270:	74 53                	je     a172c5 <CUnitSpawner::spawnUnitByIndex(unsigned int)+0xb25>
  a17272:	31 c9                	xor    ecx,ecx
  a17274:	31 d2                	xor    edx,edx
  a17276:	31 f6                	xor    esi,esi
  a17278:	bf 38 01 00 00       	mov    edi,0x138
  a1727d:	e8 96 c0 b3 ff       	call   553318 <Ogre::NedAllocImpl::allocBytes(unsigned long, char const*, int, char const*)@plt>
  a17282:	f3 0f 10 15 72 d5 58 00 	movss  xmm2,DWORD PTR [rip+0x58d572]        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  a1728a:	45 31 c0             	xor    r8d,r8d
  a1728d:	0f 28 ca             	movaps xmm1,xmm2
  a17290:	31 c9                	xor    ecx,ecx
  a17292:	f3 0f 10 05 0e 40 5c 00 	movss  xmm0,DWORD PTR [rip+0x5c400e]        # fdb2a8 <vtable for iUnitObserver+0x28>
  a1729a:	ba 01 00 00 00       	mov    edx,0x1
  a1729f:	be 81 00 00 00       	mov    esi,0x81
  a172a4:	48 89 c7             	mov    rdi,rax
  a172a7:	48 89 44 24 50       	mov    QWORD PTR [rsp+0x50],rax
