000000000065c410 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()>:
  65c410:	41 57                	push   r15
  65c412:	be 60 77 fa 00       	mov    esi,0xfa7760
  65c417:	41 b9 01 00 00 00    	mov    r9d,0x1
  65c41d:	41 b8 01 00 00 00    	mov    r8d,0x1
  65c423:	b9 b8 c2 fa 00       	mov    ecx,0xfac2b8
  65c428:	ba a8 6b fb 00       	mov    edx,0xfb6ba8
  65c42d:	41 56                	push   r14
  65c42f:	41 55                	push   r13
  65c431:	41 54                	push   r12
  65c433:	55                   	push   rbp
  65c434:	48 89 fd             	mov    rbp,rdi
  65c437:	53                   	push   rbx
  65c438:	48 81 ec 18 04 00 00 	sub    rsp,0x418
  65c43f:	c7 04 24 01 00 00 00 	mov    DWORD PTR [rsp],0x1
  65c446:	e8 f5 07 ff ff       	call   64cc40 <CShapeDescriptor::CShapeDescriptor(wchar_t const*, wchar_t const*, wchar_t const*, bool, bool, bool)>
  65c44b:	48 c7 45 00 50 7d fb 00 	mov    QWORD PTR [rbp+0x0],0xfb7d50
  65c453:	be 20 00 00 00       	mov    esi,0x20
  65c458:	48 89 ef             	mov    rdi,rbp
  65c45b:	e8 70 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c460:	be 0a 00 00 00       	mov    esi,0xa
  65c465:	48 89 ef             	mov    rdi,rbp
  65c468:	e8 63 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c46d:	be 21 00 00 00       	mov    esi,0x21
  65c472:	48 89 ef             	mov    rdi,rbp
  65c475:	e8 56 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c47a:	be 22 00 00 00       	mov    esi,0x22
  65c47f:	48 89 ef             	mov    rdi,rbp
  65c482:	e8 49 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c487:	be 23 00 00 00       	mov    esi,0x23
  65c48c:	48 89 ef             	mov    rdi,rbp
  65c48f:	e8 3c 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c494:	be 24 00 00 00       	mov    esi,0x24
  65c499:	48 89 ef             	mov    rdi,rbp
  65c49c:	e8 2f 1e 0a 00       	call   6fe2d0 <CDescriptor::AddInputLogic(EINPUT_EVENTS)>
  65c4a1:	be 1a 00 00 00       	mov    esi,0x1a
  65c4a6:	48 89 ef             	mov    rdi,rbp
  65c4a9:	e8 72 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4ae:	be 18 00 00 00       	mov    esi,0x18
  65c4b3:	48 89 ef             	mov    rdi,rbp
  65c4b6:	e8 65 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4bb:	be 19 00 00 00       	mov    esi,0x19
  65c4c0:	48 89 ef             	mov    rdi,rbp
  65c4c3:	e8 58 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4c8:	be 1b 00 00 00       	mov    esi,0x1b
  65c4cd:	48 89 ef             	mov    rdi,rbp
  65c4d0:	e8 4b 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4d5:	be 1c 00 00 00       	mov    esi,0x1c
  65c4da:	48 89 ef             	mov    rdi,rbp
  65c4dd:	e8 3e 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4e2:	be 1d 00 00 00       	mov    esi,0x1d
  65c4e7:	48 89 ef             	mov    rdi,rbp
  65c4ea:	e8 31 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4ef:	be 1e 00 00 00       	mov    esi,0x1e
  65c4f4:	48 89 ef             	mov    rdi,rbp
  65c4f7:	e8 24 1d 0a 00       	call   6fe220 <CDescriptor::AddOutputLogic(EOUTPUT_EVENTS)>
  65c4fc:	4c 8d ac 24 90 03 00 00 	lea    r13,[rsp+0x390]
  65c504:	48 8d 94 24 0f 04 00 00 	lea    rdx,[rsp+0x40f]
  65c50c:	be 38 6c fb 00       	mov    esi,0xfb6c38
  65c511:	4c 89 ef             	mov    rdi,r13
  65c514:	e8 3f 99 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c519:	4c 8d a4 24 80 03 00 00 	lea    r12,[rsp+0x380]
  65c521:	48 8d 94 24 0e 04 00 00 	lea    rdx,[rsp+0x40e]
  65c529:	be 90 6b fb 00       	mov    esi,0xfb6b90
  65c52e:	4c 89 e7             	mov    rdi,r12
  65c531:	e8 22 99 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c536:	48 8d 9c 24 70 03 00 00 	lea    rbx,[rsp+0x370]
  65c53e:	48 8d 94 24 0d 04 00 00 	lea    rdx,[rsp+0x40d]
  65c546:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c54b:	48 89 df             	mov    rdi,rbx
  65c54e:	e8 05 99 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c553:	41 b9 20 ef 65 00    	mov    r9d,0x65ef20
  65c559:	41 b8 30 eb 65 00    	mov    r8d,0x65eb30
  65c55f:	4c 89 e9             	mov    rcx,r13
  65c562:	4c 89 e2             	mov    rdx,r12
  65c565:	48 89 de             	mov    rsi,rbx
  65c568:	48 89 ef             	mov    rdi,rbp
  65c56b:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c573:	c7 04 24 04 00 00 00 	mov    DWORD PTR [rsp],0x4
  65c57a:	e8 f1 22 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c57f:	48 8b bc 24 70 03 00 00 	mov    rdi,QWORD PTR [rsp+0x370]
  65c587:	bb 40 45 42 01       	mov    ebx,0x1424540
  65c58c:	48 83 ef 18          	sub    rdi,0x18
  65c590:	48 39 df             	cmp    rdi,rbx
  65c593:	0f 85 48 0d 00 00    	jne    65d2e1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xed1>
  65c599:	48 8b bc 24 80 03 00 00 	mov    rdi,QWORD PTR [rsp+0x380]
  65c5a1:	48 83 ef 18          	sub    rdi,0x18
  65c5a5:	48 39 fb             	cmp    rbx,rdi
  65c5a8:	0f 85 34 17 00 00    	jne    65dce2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18d2>
  65c5ae:	48 8b bc 24 90 03 00 00 	mov    rdi,QWORD PTR [rsp+0x390]
  65c5b6:	48 83 ef 18          	sub    rdi,0x18
  65c5ba:	48 39 fb             	cmp    rbx,rdi
  65c5bd:	0f 85 2f 13 00 00    	jne    65d8f2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x14e2>
  65c5c3:	4c 8d b4 24 60 03 00 00 	lea    r14,[rsp+0x360]
  65c5cb:	48 8d 94 24 0c 04 00 00 	lea    rdx,[rsp+0x40c]
  65c5d3:	be c8 6c fb 00       	mov    esi,0xfb6cc8
  65c5d8:	4c 89 f7             	mov    rdi,r14
  65c5db:	e8 78 98 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c5e0:	4c 8d ac 24 50 03 00 00 	lea    r13,[rsp+0x350]
  65c5e8:	48 8d 94 24 0b 04 00 00 	lea    rdx,[rsp+0x40b]
  65c5f0:	be c8 6d fb 00       	mov    esi,0xfb6dc8
  65c5f5:	4c 89 ef             	mov    rdi,r13
  65c5f8:	e8 5b 98 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c5fd:	4c 8d a4 24 40 03 00 00 	lea    r12,[rsp+0x340]
  65c605:	48 8d 94 24 0a 04 00 00 	lea    rdx,[rsp+0x40a]
  65c60d:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c612:	4c 89 e7             	mov    rdi,r12
  65c615:	e8 3e 98 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c61a:	41 b9 00 ef 65 00    	mov    r9d,0x65ef00
  65c620:	41 b8 50 eb 65 00    	mov    r8d,0x65eb50
  65c626:	4c 89 f1             	mov    rcx,r14
  65c629:	4c 89 ea             	mov    rdx,r13
  65c62c:	4c 89 e6             	mov    rsi,r12
  65c62f:	48 89 ef             	mov    rdi,rbp
  65c632:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c63a:	c7 04 24 04 00 00 00 	mov    DWORD PTR [rsp],0x4
  65c641:	e8 2a 22 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c646:	48 8b bc 24 40 03 00 00 	mov    rdi,QWORD PTR [rsp+0x340]
  65c64e:	48 83 ef 18          	sub    rdi,0x18
  65c652:	48 39 fb             	cmp    rbx,rdi
  65c655:	0f 85 07 15 00 00    	jne    65db62 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1752>
  65c65b:	48 8b bc 24 50 03 00 00 	mov    rdi,QWORD PTR [rsp+0x350]
  65c663:	48 83 ef 18          	sub    rdi,0x18
  65c667:	48 39 fb             	cmp    rbx,rdi
  65c66a:	0f 85 82 0f 00 00    	jne    65d5f2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x11e2>
  65c670:	48 8b bc 24 60 03 00 00 	mov    rdi,QWORD PTR [rsp+0x360]
  65c678:	48 83 ef 18          	sub    rdi,0x18
  65c67c:	48 39 fb             	cmp    rbx,rdi
  65c67f:	0f 85 9d 15 00 00    	jne    65dc22 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1812>
  65c685:	4c 8d b4 24 30 03 00 00 	lea    r14,[rsp+0x330]
  65c68d:	48 8d 94 24 09 04 00 00 	lea    rdx,[rsp+0x409]
  65c695:	be f8 6d fb 00       	mov    esi,0xfb6df8
  65c69a:	4c 89 f7             	mov    rdi,r14
  65c69d:	e8 b6 97 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c6a2:	4c 8d ac 24 20 03 00 00 	lea    r13,[rsp+0x320]
  65c6aa:	48 8d 94 24 08 04 00 00 	lea    rdx,[rsp+0x408]
  65c6b2:	be 98 c9 fa 00       	mov    esi,0xfac998
  65c6b7:	4c 89 ef             	mov    rdi,r13
  65c6ba:	e8 99 97 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c6bf:	4c 8d a4 24 10 03 00 00 	lea    r12,[rsp+0x310]
  65c6c7:	48 8d 94 24 07 04 00 00 	lea    rdx,[rsp+0x407]
  65c6cf:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c6d4:	4c 89 e7             	mov    rdi,r12
  65c6d7:	e8 7c 97 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c6dc:	41 b9 d0 ee 65 00    	mov    r9d,0x65eed0
  65c6e2:	41 b8 70 eb 65 00    	mov    r8d,0x65eb70
  65c6e8:	4c 89 f1             	mov    rcx,r14
  65c6eb:	4c 89 ea             	mov    rdx,r13
  65c6ee:	4c 89 e6             	mov    rsi,r12
  65c6f1:	48 89 ef             	mov    rdi,rbp
  65c6f4:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c6fc:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65c703:	e8 68 21 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c708:	48 8b bc 24 10 03 00 00 	mov    rdi,QWORD PTR [rsp+0x310]
  65c710:	48 83 ef 18          	sub    rdi,0x18
  65c714:	48 39 fb             	cmp    rbx,rdi
  65c717:	0f 85 55 10 00 00    	jne    65d772 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1362>
  65c71d:	48 8b bc 24 20 03 00 00 	mov    rdi,QWORD PTR [rsp+0x320]
  65c725:	48 83 ef 18          	sub    rdi,0x18
  65c729:	48 39 fb             	cmp    rbx,rdi
  65c72c:	0f 85 40 13 00 00    	jne    65da72 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1662>
  65c732:	48 8b bc 24 30 03 00 00 	mov    rdi,QWORD PTR [rsp+0x330]
  65c73a:	48 83 ef 18          	sub    rdi,0x18
  65c73e:	48 39 fb             	cmp    rbx,rdi
  65c741:	0f 85 23 0d 00 00    	jne    65d46a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x105a>
  65c747:	4c 8d b4 24 00 03 00 00 	lea    r14,[rsp+0x300]
  65c74f:	48 8d 94 24 06 04 00 00 	lea    rdx,[rsp+0x406]
  65c757:	be b0 6e fb 00       	mov    esi,0xfb6eb0
  65c75c:	4c 89 f7             	mov    rdi,r14
  65c75f:	e8 f4 96 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c764:	4c 8d ac 24 f0 02 00 00 	lea    r13,[rsp+0x2f0]
  65c76c:	48 8d 94 24 05 04 00 00 	lea    rdx,[rsp+0x405]
  65c774:	be 60 6f fb 00       	mov    esi,0xfb6f60
  65c779:	4c 89 ef             	mov    rdi,r13
  65c77c:	e8 d7 96 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c781:	4c 8d a4 24 e0 02 00 00 	lea    r12,[rsp+0x2e0]
  65c789:	48 8d 94 24 04 04 00 00 	lea    rdx,[rsp+0x404]
  65c791:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c796:	4c 89 e7             	mov    rdi,r12
  65c799:	e8 ba 96 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c79e:	41 b9 a0 ee 65 00    	mov    r9d,0x65eea0
  65c7a4:	41 b8 60 eb 65 00    	mov    r8d,0x65eb60
  65c7aa:	4c 89 f1             	mov    rcx,r14
  65c7ad:	4c 89 ea             	mov    rdx,r13
  65c7b0:	4c 89 e6             	mov    rsi,r12
  65c7b3:	48 89 ef             	mov    rdi,rbp
  65c7b6:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c7be:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65c7c5:	e8 a6 20 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c7ca:	48 8b bc 24 e0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2e0]
  65c7d2:	48 83 ef 18          	sub    rdi,0x18
  65c7d6:	48 39 fb             	cmp    rbx,rdi
  65c7d9:	0f 85 a3 14 00 00    	jne    65dc82 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1872>
  65c7df:	48 8b bc 24 f0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2f0]
  65c7e7:	48 83 ef 18          	sub    rdi,0x18
  65c7eb:	48 39 fb             	cmp    rbx,rdi
  65c7ee:	0f 85 3e 10 00 00    	jne    65d832 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1422>
  65c7f4:	48 8b bc 24 00 03 00 00 	mov    rdi,QWORD PTR [rsp+0x300]
  65c7fc:	48 83 ef 18          	sub    rdi,0x18
  65c800:	48 39 fb             	cmp    rbx,rdi
  65c803:	0f 85 f9 12 00 00    	jne    65db02 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x16f2>
  65c809:	4c 8d b4 24 d0 02 00 00 	lea    r14,[rsp+0x2d0]
  65c811:	48 8d 94 24 03 04 00 00 	lea    rdx,[rsp+0x403]
  65c819:	be a0 6f fb 00       	mov    esi,0xfb6fa0
  65c81e:	4c 89 f7             	mov    rdi,r14
  65c821:	e8 32 96 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c826:	4c 8d ac 24 c0 02 00 00 	lea    r13,[rsp+0x2c0]
  65c82e:	48 8d 94 24 02 04 00 00 	lea    rdx,[rsp+0x402]
  65c836:	be 60 70 fb 00       	mov    esi,0xfb7060
  65c83b:	4c 89 ef             	mov    rdi,r13
  65c83e:	e8 15 96 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c843:	4c 8d a4 24 b0 02 00 00 	lea    r12,[rsp+0x2b0]
  65c84b:	48 8d 94 24 01 04 00 00 	lea    rdx,[rsp+0x401]
  65c853:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c858:	4c 89 e7             	mov    rdi,r12
  65c85b:	e8 f8 95 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c860:	41 b9 70 ee 65 00    	mov    r9d,0x65ee70
  65c866:	41 b8 90 eb 65 00    	mov    r8d,0x65eb90
  65c86c:	4c 89 f1             	mov    rcx,r14
  65c86f:	4c 89 ea             	mov    rdx,r13
  65c872:	4c 89 e6             	mov    rsi,r12
  65c875:	48 89 ef             	mov    rdi,rbp
  65c878:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c880:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65c887:	e8 e4 1f 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c88c:	48 8b bc 24 b0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2b0]
  65c894:	48 83 ef 18          	sub    rdi,0x18
  65c898:	48 39 fb             	cmp    rbx,rdi
  65c89b:	0f 85 89 0c 00 00    	jne    65d52a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x111a>
  65c8a1:	48 8b bc 24 c0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2c0]
  65c8a9:	48 83 ef 18          	sub    rdi,0x18
  65c8ad:	48 39 fb             	cmp    rbx,rdi
  65c8b0:	0f 85 0c 13 00 00    	jne    65dbc2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x17b2>
  65c8b6:	48 8b bc 24 d0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2d0]
  65c8be:	48 83 ef 18          	sub    rdi,0x18
  65c8c2:	48 39 fb             	cmp    rbx,rdi
  65c8c5:	0f 85 e7 0d 00 00    	jne    65d6b2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x12a2>
  65c8cb:	4c 8d b4 24 a0 02 00 00 	lea    r14,[rsp+0x2a0]
  65c8d3:	48 8d 94 24 00 04 00 00 	lea    rdx,[rsp+0x400]
  65c8db:	be 98 70 fb 00       	mov    esi,0xfb7098
  65c8e0:	4c 89 f7             	mov    rdi,r14
  65c8e3:	e8 70 95 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c8e8:	4c 8d ac 24 90 02 00 00 	lea    r13,[rsp+0x290]
  65c8f0:	48 8d 94 24 ff 03 00 00 	lea    rdx,[rsp+0x3ff]
  65c8f8:	be f0 55 ff 00       	mov    esi,0xff55f0
  65c8fd:	4c 89 ef             	mov    rdi,r13
  65c900:	e8 53 95 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c905:	4c 8d a4 24 80 02 00 00 	lea    r12,[rsp+0x280]
  65c90d:	48 8d 94 24 fe 03 00 00 	lea    rdx,[rsp+0x3fe]
  65c915:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c91a:	4c 89 e7             	mov    rdi,r12
  65c91d:	e8 36 95 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c922:	41 b9 50 ee 65 00    	mov    r9d,0x65ee50
  65c928:	41 b8 b0 eb 65 00    	mov    r8d,0x65ebb0
  65c92e:	4c 89 f1             	mov    rcx,r14
  65c931:	4c 89 ea             	mov    rdx,r13
  65c934:	4c 89 e6             	mov    rsi,r12
  65c937:	48 89 ef             	mov    rdi,rbp
  65c93a:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65c942:	c7 04 24 03 00 00 00 	mov    DWORD PTR [rsp],0x3
  65c949:	e8 22 1f 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65c94e:	48 8b bc 24 80 02 00 00 	mov    rdi,QWORD PTR [rsp+0x280]
  65c956:	48 83 ef 18          	sub    rdi,0x18
  65c95a:	48 39 fb             	cmp    rbx,rdi
  65c95d:	0f 85 4f 10 00 00    	jne    65d9b2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x15a2>
  65c963:	48 8b bc 24 90 02 00 00 	mov    rdi,QWORD PTR [rsp+0x290]
  65c96b:	48 83 ef 18          	sub    rdi,0x18
  65c96f:	48 39 fb             	cmp    rbx,rdi
  65c972:	0f 85 2a 0a 00 00    	jne    65d3a2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf92>
  65c978:	48 8b bc 24 a0 02 00 00 	mov    rdi,QWORD PTR [rsp+0x2a0]
  65c980:	48 83 ef 18          	sub    rdi,0x18
  65c984:	48 39 fb             	cmp    rbx,rdi
  65c987:	0f 85 25 13 00 00    	jne    65dcb2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18a2>
  65c98d:	4c 8d b4 24 70 02 00 00 	lea    r14,[rsp+0x270]
  65c995:	48 8d 94 24 fd 03 00 00 	lea    rdx,[rsp+0x3fd]
  65c99d:	be 30 71 fb 00       	mov    esi,0xfb7130
  65c9a2:	4c 89 f7             	mov    rdi,r14
  65c9a5:	e8 ae 94 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c9aa:	4c 8d ac 24 60 02 00 00 	lea    r13,[rsp+0x260]
  65c9b2:	48 8d 94 24 fc 03 00 00 	lea    rdx,[rsp+0x3fc]
  65c9ba:	be 90 72 fb 00       	mov    esi,0xfb7290
  65c9bf:	4c 89 ef             	mov    rdi,r13
  65c9c2:	e8 91 94 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c9c7:	4c 8d a4 24 50 02 00 00 	lea    r12,[rsp+0x250]
  65c9cf:	48 8d 94 24 fb 03 00 00 	lea    rdx,[rsp+0x3fb]
  65c9d7:	be 78 20 fc 00       	mov    esi,0xfc2078
  65c9dc:	4c 89 e7             	mov    rdi,r12
  65c9df:	e8 74 94 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65c9e4:	41 b9 30 ee 65 00    	mov    r9d,0x65ee30
  65c9ea:	41 b8 c0 eb 65 00    	mov    r8d,0x65ebc0
  65c9f0:	4c 89 f1             	mov    rcx,r14
  65c9f3:	4c 89 ea             	mov    rdx,r13
  65c9f6:	4c 89 e6             	mov    rsi,r12
  65c9f9:	48 89 ef             	mov    rdi,rbp
  65c9fc:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65ca04:	c7 04 24 04 00 00 00 	mov    DWORD PTR [rsp],0x4
  65ca0b:	e8 60 1e 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65ca10:	48 8b bc 24 50 02 00 00 	mov    rdi,QWORD PTR [rsp+0x250]
  65ca18:	48 83 ef 18          	sub    rdi,0x18
  65ca1c:	48 39 fb             	cmp    rbx,rdi
  65ca1f:	0f 85 6d 0e 00 00    	jne    65d892 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1482>
  65ca25:	48 8b bc 24 60 02 00 00 	mov    rdi,QWORD PTR [rsp+0x260]
  65ca2d:	48 83 ef 18          	sub    rdi,0x18
  65ca31:	48 39 fb             	cmp    rbx,rdi
  65ca34:	0f 85 f8 10 00 00    	jne    65db32 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1722>
  65ca3a:	48 8b bc 24 70 02 00 00 	mov    rdi,QWORD PTR [rsp+0x270]
  65ca42:	48 83 ef 18          	sub    rdi,0x18
  65ca46:	48 39 fb             	cmp    rbx,rdi
  65ca49:	0f 85 43 0b 00 00    	jne    65d592 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1182>
  65ca4f:	4c 8d b4 24 40 02 00 00 	lea    r14,[rsp+0x240]
  65ca57:	48 8d 94 24 fa 03 00 00 	lea    rdx,[rsp+0x3fa]
  65ca5f:	be c0 72 fb 00       	mov    esi,0xfb72c0
  65ca64:	4c 89 f7             	mov    rdi,r14
  65ca67:	e8 ec 93 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ca6c:	4c 8d ac 24 30 02 00 00 	lea    r13,[rsp+0x230]
  65ca74:	48 8d 94 24 f9 03 00 00 	lea    rdx,[rsp+0x3f9]
  65ca7c:	be 08 74 fb 00       	mov    esi,0xfb7408
  65ca81:	4c 89 ef             	mov    rdi,r13
  65ca84:	e8 cf 93 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ca89:	4c 8d a4 24 20 02 00 00 	lea    r12,[rsp+0x220]
  65ca91:	48 8d 94 24 f8 03 00 00 	lea    rdx,[rsp+0x3f8]
  65ca99:	be 78 20 fc 00       	mov    esi,0xfc2078
  65ca9e:	4c 89 e7             	mov    rdi,r12
  65caa1:	e8 b2 93 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65caa6:	41 b9 00 ee 65 00    	mov    r9d,0x65ee00
  65caac:	41 b8 e0 eb 65 00    	mov    r8d,0x65ebe0
  65cab2:	4c 89 f1             	mov    rcx,r14
  65cab5:	4c 89 ea             	mov    rdx,r13
  65cab8:	4c 89 e6             	mov    rsi,r12
  65cabb:	48 89 ef             	mov    rdi,rbp
  65cabe:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cac6:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cacd:	e8 9e 1d 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cad2:	48 8b bc 24 20 02 00 00 	mov    rdi,QWORD PTR [rsp+0x220]
  65cada:	48 83 ef 18          	sub    rdi,0x18
  65cade:	48 39 fb             	cmp    rbx,rdi
  65cae1:	0f 85 0b 11 00 00    	jne    65dbf2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x17e2>
  65cae7:	48 8b bc 24 30 02 00 00 	mov    rdi,QWORD PTR [rsp+0x230]
  65caef:	48 83 ef 18          	sub    rdi,0x18
  65caf3:	48 39 fb             	cmp    rbx,rdi
  65caf6:	0f 85 16 0c 00 00    	jne    65d712 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1302>
  65cafc:	48 8b bc 24 40 02 00 00 	mov    rdi,QWORD PTR [rsp+0x240]
  65cb04:	48 83 ef 18          	sub    rdi,0x18
  65cb08:	48 39 fb             	cmp    rbx,rdi
  65cb0b:	0f 85 01 0f 00 00    	jne    65da12 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1602>
  65cb11:	4c 8d b4 24 10 02 00 00 	lea    r14,[rsp+0x210]
  65cb19:	48 8d 94 24 f7 03 00 00 	lea    rdx,[rsp+0x3f7]
  65cb21:	be 48 74 fb 00       	mov    esi,0xfb7448
  65cb26:	4c 89 f7             	mov    rdi,r14
  65cb29:	e8 2a 93 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cb2e:	4c 8d ac 24 00 02 00 00 	lea    r13,[rsp+0x200]
  65cb36:	48 8d 94 24 f6 03 00 00 	lea    rdx,[rsp+0x3f6]
  65cb3e:	be 30 75 fb 00       	mov    esi,0xfb7530
  65cb43:	4c 89 ef             	mov    rdi,r13
  65cb46:	e8 0d 93 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cb4b:	4c 8d a4 24 f0 01 00 00 	lea    r12,[rsp+0x1f0]
  65cb53:	48 8d 94 24 f5 03 00 00 	lea    rdx,[rsp+0x3f5]
  65cb5b:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cb60:	4c 89 e7             	mov    rdi,r12
  65cb63:	e8 f0 92 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cb68:	41 b9 d0 ed 65 00    	mov    r9d,0x65edd0
  65cb6e:	41 b8 f0 eb 65 00    	mov    r8d,0x65ebf0
  65cb74:	4c 89 f1             	mov    rcx,r14
  65cb77:	4c 89 ea             	mov    rdx,r13
  65cb7a:	4c 89 e6             	mov    rsi,r12
  65cb7d:	48 89 ef             	mov    rdi,rbp
  65cb80:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cb88:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cb8f:	e8 dc 1c 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cb94:	48 8b bc 24 f0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1f0]
  65cb9c:	48 83 ef 18          	sub    rdi,0x18
  65cba0:	48 39 fb             	cmp    rbx,rdi
  65cba3:	0f 85 61 08 00 00    	jne    65d40a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xffa>
  65cba9:	48 8b bc 24 00 02 00 00 	mov    rdi,QWORD PTR [rsp+0x200]
  65cbb1:	48 83 ef 18          	sub    rdi,0x18
  65cbb5:	48 39 fb             	cmp    rbx,rdi
  65cbb8:	0f 85 94 10 00 00    	jne    65dc52 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1842>
  65cbbe:	48 8b bc 24 10 02 00 00 	mov    rdi,QWORD PTR [rsp+0x210]
  65cbc6:	48 83 ef 18          	sub    rdi,0x18
  65cbca:	48 39 fb             	cmp    rbx,rdi
  65cbcd:	0f 85 ff 0b 00 00    	jne    65d7d2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x13c2>
  65cbd3:	4c 8d b4 24 e0 01 00 00 	lea    r14,[rsp+0x1e0]
  65cbdb:	48 8d 94 24 f4 03 00 00 	lea    rdx,[rsp+0x3f4]
  65cbe3:	be 68 75 fb 00       	mov    esi,0xfb7568
  65cbe8:	4c 89 f7             	mov    rdi,r14
  65cbeb:	e8 68 92 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cbf0:	4c 8d ac 24 d0 01 00 00 	lea    r13,[rsp+0x1d0]
  65cbf8:	48 8d 94 24 f3 03 00 00 	lea    rdx,[rsp+0x3f3]
  65cc00:	be 40 76 fb 00       	mov    esi,0xfb7640
  65cc05:	4c 89 ef             	mov    rdi,r13
  65cc08:	e8 4b 92 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cc0d:	4c 8d a4 24 c0 01 00 00 	lea    r12,[rsp+0x1c0]
  65cc15:	48 8d 94 24 f2 03 00 00 	lea    rdx,[rsp+0x3f2]
  65cc1d:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cc22:	4c 89 e7             	mov    rdi,r12
  65cc25:	e8 2e 92 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cc2a:	41 b9 a0 ed 65 00    	mov    r9d,0x65eda0
  65cc30:	41 b8 00 ec 65 00    	mov    r8d,0x65ec00
  65cc36:	4c 89 f1             	mov    rcx,r14
  65cc39:	4c 89 ea             	mov    rdx,r13
  65cc3c:	4c 89 e6             	mov    rsi,r12
  65cc3f:	48 89 ef             	mov    rdi,rbp
  65cc42:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cc4a:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cc51:	e8 1a 1c 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cc56:	48 8b bc 24 c0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1c0]
  65cc5e:	48 83 ef 18          	sub    rdi,0x18
  65cc62:	48 39 fb             	cmp    rbx,rdi
  65cc65:	0f 85 67 0e 00 00    	jne    65dad2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x16c2>
  65cc6b:	48 8b bc 24 d0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1d0]
  65cc73:	48 83 ef 18          	sub    rdi,0x18
  65cc77:	48 39 fb             	cmp    rbx,rdi
  65cc7a:	0f 85 4a 08 00 00    	jne    65d4ca <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x10ba>
  65cc80:	48 8b bc 24 e0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1e0]
  65cc88:	48 83 ef 18          	sub    rdi,0x18
  65cc8c:	48 39 fb             	cmp    rbx,rdi
  65cc8f:	0f 85 fd 0e 00 00    	jne    65db92 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1782>
  65cc95:	4c 8d b4 24 b0 01 00 00 	lea    r14,[rsp+0x1b0]
  65cc9d:	48 8d 94 24 f1 03 00 00 	lea    rdx,[rsp+0x3f1]
  65cca5:	be 70 76 fb 00       	mov    esi,0xfb7670
  65ccaa:	4c 89 f7             	mov    rdi,r14
  65ccad:	e8 a6 91 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ccb2:	4c 8d ac 24 a0 01 00 00 	lea    r13,[rsp+0x1a0]
  65ccba:	48 8d 94 24 f0 03 00 00 	lea    rdx,[rsp+0x3f0]
  65ccc2:	be b8 77 fb 00       	mov    esi,0xfb77b8
  65ccc7:	4c 89 ef             	mov    rdi,r13
  65ccca:	e8 89 91 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cccf:	4c 8d a4 24 90 01 00 00 	lea    r12,[rsp+0x190]
  65ccd7:	48 8d 94 24 ef 03 00 00 	lea    rdx,[rsp+0x3ef]
  65ccdf:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cce4:	4c 89 e7             	mov    rdi,r12
  65cce7:	e8 6c 91 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ccec:	41 b9 70 ed 65 00    	mov    r9d,0x65ed70
  65ccf2:	41 b8 a0 eb 65 00    	mov    r8d,0x65eba0
  65ccf8:	4c 89 f1             	mov    rcx,r14
  65ccfb:	4c 89 ea             	mov    rdx,r13
  65ccfe:	4c 89 e6             	mov    rsi,r12
  65cd01:	48 89 ef             	mov    rdi,rbp
  65cd04:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cd0c:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cd13:	e8 58 1b 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cd18:	48 8b bc 24 90 01 00 00 	mov    rdi,QWORD PTR [rsp+0x190]
  65cd20:	48 83 ef 18          	sub    rdi,0x18
  65cd24:	48 39 fb             	cmp    rbx,rdi
  65cd27:	0f 85 25 09 00 00    	jne    65d652 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1242>
  65cd2d:	48 8b bc 24 a0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1a0]
  65cd35:	48 83 ef 18          	sub    rdi,0x18
  65cd39:	48 39 fb             	cmp    rbx,rdi
  65cd3c:	0f 85 10 0c 00 00    	jne    65d952 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1542>
  65cd42:	48 8b bc 24 b0 01 00 00 	mov    rdi,QWORD PTR [rsp+0x1b0]
  65cd4a:	48 83 ef 18          	sub    rdi,0x18
  65cd4e:	48 39 fb             	cmp    rbx,rdi
  65cd51:	0f 85 eb 05 00 00    	jne    65d342 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf32>
  65cd57:	4c 8d b4 24 80 01 00 00 	lea    r14,[rsp+0x180]
  65cd5f:	48 8d 94 24 ee 03 00 00 	lea    rdx,[rsp+0x3ee]
  65cd67:	be f8 77 fb 00       	mov    esi,0xfb77f8
  65cd6c:	4c 89 f7             	mov    rdi,r14
  65cd6f:	e8 e4 90 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cd74:	4c 8d ac 24 70 01 00 00 	lea    r13,[rsp+0x170]
  65cd7c:	48 8d 94 24 ed 03 00 00 	lea    rdx,[rsp+0x3ed]
  65cd84:	be b8 78 fb 00       	mov    esi,0xfb78b8
  65cd89:	4c 89 ef             	mov    rdi,r13
  65cd8c:	e8 c7 90 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cd91:	4c 8d a4 24 60 01 00 00 	lea    r12,[rsp+0x160]
  65cd99:	48 8d 94 24 ec 03 00 00 	lea    rdx,[rsp+0x3ec]
  65cda1:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cda6:	4c 89 e7             	mov    rdi,r12
  65cda9:	e8 aa 90 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cdae:	41 b9 40 ed 65 00    	mov    r9d,0x65ed40
  65cdb4:	41 b8 10 ec 65 00    	mov    r8d,0x65ec10
  65cdba:	4c 89 f1             	mov    rcx,r14
  65cdbd:	4c 89 ea             	mov    rdx,r13
  65cdc0:	4c 89 e6             	mov    rsi,r12
  65cdc3:	48 89 ef             	mov    rdi,rbp
  65cdc6:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cdce:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cdd5:	e8 96 1a 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cdda:	48 8b bc 24 60 01 00 00 	mov    rdi,QWORD PTR [rsp+0x160]
  65cde2:	48 83 ef 18          	sub    rdi,0x18
  65cde6:	48 39 fb             	cmp    rbx,rdi
  65cde9:	0f 85 b3 0c 00 00    	jne    65daa2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1692>
  65cdef:	48 8b bc 24 70 01 00 00 	mov    rdi,QWORD PTR [rsp+0x170]
  65cdf7:	48 83 ef 18          	sub    rdi,0x18
  65cdfb:	48 39 fb             	cmp    rbx,rdi
  65cdfe:	0f 85 9e 09 00 00    	jne    65d7a2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1392>
  65ce04:	48 8b bc 24 80 01 00 00 	mov    rdi,QWORD PTR [rsp+0x180]
  65ce0c:	48 83 ef 18          	sub    rdi,0x18
  65ce10:	48 39 fb             	cmp    rbx,rdi
  65ce13:	0f 85 09 0b 00 00    	jne    65d922 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1512>
  65ce19:	4c 8d b4 24 50 01 00 00 	lea    r14,[rsp+0x150]
  65ce21:	48 8d 94 24 eb 03 00 00 	lea    rdx,[rsp+0x3eb]
  65ce29:	be f8 78 fb 00       	mov    esi,0xfb78f8
  65ce2e:	4c 89 f7             	mov    rdi,r14
  65ce31:	e8 22 90 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ce36:	4c 8d ac 24 40 01 00 00 	lea    r13,[rsp+0x140]
  65ce3e:	48 8d 94 24 ea 03 00 00 	lea    rdx,[rsp+0x3ea]
  65ce46:	be 40 79 fb 00       	mov    esi,0xfb7940
  65ce4b:	4c 89 ef             	mov    rdi,r13
  65ce4e:	e8 05 90 ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ce53:	4c 8d a4 24 30 01 00 00 	lea    r12,[rsp+0x130]
  65ce5b:	48 8d 94 24 e9 03 00 00 	lea    rdx,[rsp+0x3e9]
  65ce63:	be 78 20 fc 00       	mov    esi,0xfc2078
  65ce68:	4c 89 e7             	mov    rdi,r12
  65ce6b:	e8 e8 8f ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65ce70:	41 b9 10 ed 65 00    	mov    r9d,0x65ed10
  65ce76:	41 b8 20 ec 65 00    	mov    r8d,0x65ec20
  65ce7c:	4c 89 f1             	mov    rcx,r14
  65ce7f:	4c 89 ea             	mov    rdx,r13
  65ce82:	4c 89 e6             	mov    rsi,r12
  65ce85:	48 89 ef             	mov    rdi,rbp
  65ce88:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65ce90:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65ce97:	e8 d4 19 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65ce9c:	48 8b bc 24 30 01 00 00 	mov    rdi,QWORD PTR [rsp+0x130]
  65cea4:	48 83 ef 18          	sub    rdi,0x18
  65cea8:	48 39 fb             	cmp    rbx,rdi
  65ceab:	0f 85 11 07 00 00    	jne    65d5c2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x11b2>
  65ceb1:	48 8b bc 24 40 01 00 00 	mov    rdi,QWORD PTR [rsp+0x140]
  65ceb9:	48 83 ef 18          	sub    rdi,0x18
  65cebd:	48 39 fb             	cmp    rbx,rdi
  65cec0:	0f 85 1c 0b 00 00    	jne    65d9e2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x15d2>
  65cec6:	48 8b bc 24 50 01 00 00 	mov    rdi,QWORD PTR [rsp+0x150]
  65cece:	48 83 ef 18          	sub    rdi,0x18
  65ced2:	48 39 fb             	cmp    rbx,rdi
  65ced5:	0f 85 07 08 00 00    	jne    65d6e2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x12d2>
  65cedb:	4c 8d b4 24 20 01 00 00 	lea    r14,[rsp+0x120]
  65cee3:	48 8d 94 24 e8 03 00 00 	lea    rdx,[rsp+0x3e8]
  65ceeb:	be 60 79 fb 00       	mov    esi,0xfb7960
  65cef0:	4c 89 f7             	mov    rdi,r14
  65cef3:	e8 60 8f ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cef8:	4c 8d ac 24 10 01 00 00 	lea    r13,[rsp+0x110]
  65cf00:	48 8d 94 24 e7 03 00 00 	lea    rdx,[rsp+0x3e7]
  65cf08:	be b0 79 fb 00       	mov    esi,0xfb79b0
  65cf0d:	4c 89 ef             	mov    rdi,r13
  65cf10:	e8 43 8f ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cf15:	4c 8d a4 24 00 01 00 00 	lea    r12,[rsp+0x100]
  65cf1d:	48 8d 94 24 e6 03 00 00 	lea    rdx,[rsp+0x3e6]
  65cf25:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cf2a:	4c 89 e7             	mov    rdi,r12
  65cf2d:	e8 26 8f ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cf32:	41 b9 e0 ec 65 00    	mov    r9d,0x65ece0
  65cf38:	41 b8 30 ec 65 00    	mov    r8d,0x65ec30
  65cf3e:	4c 89 f1             	mov    rcx,r14
  65cf41:	4c 89 ea             	mov    rdx,r13
  65cf44:	4c 89 e6             	mov    rsi,r12
  65cf47:	48 89 ef             	mov    rdi,rbp
  65cf4a:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65cf52:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65cf59:	e8 12 19 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65cf5e:	48 8b bc 24 00 01 00 00 	mov    rdi,QWORD PTR [rsp+0x100]
  65cf66:	48 83 ef 18          	sub    rdi,0x18
  65cf6a:	48 39 fb             	cmp    rbx,rdi
  65cf6d:	0f 85 ef 08 00 00    	jne    65d862 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1452>
  65cf73:	48 8b bc 24 10 01 00 00 	mov    rdi,QWORD PTR [rsp+0x110]
  65cf7b:	48 83 ef 18          	sub    rdi,0x18
  65cf7f:	48 39 fb             	cmp    rbx,rdi
  65cf82:	0f 85 b2 04 00 00    	jne    65d43a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x102a>
  65cf88:	48 8b bc 24 20 01 00 00 	mov    rdi,QWORD PTR [rsp+0x120]
  65cf90:	48 83 ef 18          	sub    rdi,0x18
  65cf94:	48 39 fb             	cmp    rbx,rdi
  65cf97:	0f 85 a5 0a 00 00    	jne    65da42 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1632>
  65cf9d:	4c 8d b4 24 f0 00 00 00 	lea    r14,[rsp+0xf0]
  65cfa5:	48 8d 94 24 e5 03 00 00 	lea    rdx,[rsp+0x3e5]
  65cfad:	be d8 79 fb 00       	mov    esi,0xfb79d8
  65cfb2:	4c 89 f7             	mov    rdi,r14
  65cfb5:	e8 9e 8e ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cfba:	4c 8d ac 24 e0 00 00 00 	lea    r13,[rsp+0xe0]
  65cfc2:	48 8d 94 24 e4 03 00 00 	lea    rdx,[rsp+0x3e4]
  65cfca:	be a8 7a fb 00       	mov    esi,0xfb7aa8
  65cfcf:	4c 89 ef             	mov    rdi,r13
  65cfd2:	e8 81 8e ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cfd7:	4c 8d a4 24 d0 00 00 00 	lea    r12,[rsp+0xd0]
  65cfdf:	48 8d 94 24 e3 03 00 00 	lea    rdx,[rsp+0x3e3]
  65cfe7:	be 78 20 fc 00       	mov    esi,0xfc2078
  65cfec:	4c 89 e7             	mov    rdi,r12
  65cfef:	e8 64 8e ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65cff4:	41 b9 c0 ec 65 00    	mov    r9d,0x65ecc0
  65cffa:	41 b8 40 ec 65 00    	mov    r8d,0x65ec40
  65d000:	4c 89 f1             	mov    rcx,r14
  65d003:	4c 89 ea             	mov    rdx,r13
  65d006:	4c 89 e6             	mov    rsi,r12
  65d009:	48 89 ef             	mov    rdi,rbp
  65d00c:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65d014:	c7 04 24 02 00 00 00 	mov    DWORD PTR [rsp],0x2
  65d01b:	e8 50 18 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65d020:	48 8b bc 24 d0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xd0]
  65d028:	48 83 ef 18          	sub    rdi,0x18
  65d02c:	48 39 fb             	cmp    rbx,rdi
  65d02f:	0f 85 0d 07 00 00    	jne    65d742 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1332>
  65d035:	48 8b bc 24 e0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xe0]
  65d03d:	48 83 ef 18          	sub    rdi,0x18
  65d041:	48 39 fb             	cmp    rbx,rdi
  65d044:	0f 85 78 08 00 00    	jne    65d8c2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x14b2>
  65d04a:	48 8b bc 24 f0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xf0]
  65d052:	48 83 ef 18          	sub    rdi,0x18
  65d056:	48 39 fb             	cmp    rbx,rdi
  65d059:	0f 85 9b 04 00 00    	jne    65d4fa <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x10ea>
  65d05f:	4c 8d b4 24 c0 00 00 00 	lea    r14,[rsp+0xc0]
  65d067:	48 8d 94 24 e2 03 00 00 	lea    rdx,[rsp+0x3e2]
  65d06f:	be f0 7a fb 00       	mov    esi,0xfb7af0
  65d074:	4c 89 f7             	mov    rdi,r14
  65d077:	e8 dc 8d ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d07c:	4c 8d ac 24 b0 00 00 00 	lea    r13,[rsp+0xb0]
  65d084:	48 8d 94 24 e1 03 00 00 	lea    rdx,[rsp+0x3e1]
  65d08c:	be 28 7c fb 00       	mov    esi,0xfb7c28
  65d091:	4c 89 ef             	mov    rdi,r13
  65d094:	e8 bf 8d ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d099:	4c 8d a4 24 a0 00 00 00 	lea    r12,[rsp+0xa0]
  65d0a1:	48 8d 94 24 e0 03 00 00 	lea    rdx,[rsp+0x3e0]
  65d0a9:	be 78 20 fc 00       	mov    esi,0xfc2078
  65d0ae:	4c 89 e7             	mov    rdi,r12
  65d0b1:	e8 a2 8d ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d0b6:	41 b9 90 ec 65 00    	mov    r9d,0x65ec90
  65d0bc:	41 b8 50 ec 65 00    	mov    r8d,0x65ec50
  65d0c2:	4c 89 f1             	mov    rcx,r14
  65d0c5:	4c 89 ea             	mov    rdx,r13
  65d0c8:	4c 89 e6             	mov    rsi,r12
  65d0cb:	48 89 ef             	mov    rdi,rbp
  65d0ce:	c7 44 24 08 00 00 00 00 	mov    DWORD PTR [rsp+0x8],0x0
  65d0d6:	c7 04 24 06 00 00 00 	mov    DWORD PTR [rsp],0x6
  65d0dd:	e8 8e 17 0a 00       	call   6fe870 <CDescriptor::AddProperty(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, EVARIABLE_TYPES, int)>
  65d0e2:	48 8b bc 24 a0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xa0]
  65d0ea:	48 83 ef 18          	sub    rdi,0x18
  65d0ee:	48 39 fb             	cmp    rbx,rdi
  65d0f1:	0f 85 8b 08 00 00    	jne    65d982 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1572>
  65d0f7:	48 8b bc 24 b0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xb0]
  65d0ff:	48 83 ef 18          	sub    rdi,0x18
  65d103:	48 39 fb             	cmp    rbx,rdi
  65d106:	0f 85 76 05 00 00    	jne    65d682 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1272>
  65d10c:	48 8b bc 24 c0 00 00 00 	mov    rdi,QWORD PTR [rsp+0xc0]
  65d114:	48 83 ef 18          	sub    rdi,0x18
  65d118:	48 39 fb             	cmp    rbx,rdi
  65d11b:	0f 85 e1 06 00 00    	jne    65d802 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x13f2>
  65d121:	4c 8d b4 24 90 00 00 00 	lea    r14,[rsp+0x90]
  65d129:	48 8d 94 24 df 03 00 00 	lea    rdx,[rsp+0x3df]
  65d131:	be d8 31 fb 00       	mov    esi,0xfb31d8
  65d136:	4c 89 f7             	mov    rdi,r14
  65d139:	e8 1a 8d ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d13e:	4c 8d ac 24 80 00 00 00 	lea    r13,[rsp+0x80]
  65d146:	48 8d 94 24 de 03 00 00 	lea    rdx,[rsp+0x3de]
  65d14e:	be 1c 2c fb 00       	mov    esi,0xfb2c1c
  65d153:	4c 89 ef             	mov    rdi,r13
  65d156:	e8 fd 8c ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d15b:	4c 8d 64 24 70       	lea    r12,[rsp+0x70]
  65d160:	48 8d 94 24 dd 03 00 00 	lea    rdx,[rsp+0x3dd]
  65d168:	be d0 ea fa 00       	mov    esi,0xfaead0
  65d16d:	4c 89 e7             	mov    rdi,r12
  65d170:	e8 e3 8c ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d175:	41 b9 40 ef 65 00    	mov    r9d,0x65ef40
  65d17b:	41 b8 80 f1 65 00    	mov    r8d,0x65f180
  65d181:	4c 89 f1             	mov    rcx,r14
  65d184:	4c 89 ea             	mov    rdx,r13
  65d187:	4c 89 e6             	mov    rsi,r12
  65d18a:	48 89 ef             	mov    rdi,rbp
  65d18d:	c7 44 24 20 04 00 00 00 	mov    DWORD PTR [rsp+0x20],0x4
  65d195:	c7 44 24 18 05 00 00 00 	mov    DWORD PTR [rsp+0x18],0x5
  65d19d:	48 c7 44 24 10 00 00 00 00 	mov    QWORD PTR [rsp+0x10],0x0
  65d1a6:	48 c7 44 24 08 10 27 65 00 	mov    QWORD PTR [rsp+0x8],0x652710
  65d1af:	48 c7 04 24 c0 b0 65 00 	mov    QWORD PTR [rsp],0x65b0c0
  65d1b7:	e8 24 1c 0a 00       	call   6fede0 <CDescriptor::AddPropertyWithInterpreterFunctions(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, unsigned int (*)(CEditorScene*, CEditorBaseObject*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, void*), std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > (*)(CEditorScene*, CEditorBaseObject*, unsigned int, void*), void*, EVARIABLE_TYPES, int)>
  65d1bc:	48 8b 7c 24 70       	mov    rdi,QWORD PTR [rsp+0x70]
  65d1c1:	41 89 c7             	mov    r15d,eax
  65d1c4:	48 83 ef 18          	sub    rdi,0x18
  65d1c8:	48 39 fb             	cmp    rbx,rdi
  65d1cb:	0f 85 a1 01 00 00    	jne    65d372 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf62>
  65d1d1:	48 8b bc 24 80 00 00 00 	mov    rdi,QWORD PTR [rsp+0x80]
  65d1d9:	48 83 ef 18          	sub    rdi,0x18
  65d1dd:	48 39 fb             	cmp    rbx,rdi
  65d1e0:	0f 85 3c 04 00 00    	jne    65d622 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1212>
  65d1e6:	48 8b bc 24 90 00 00 00 	mov    rdi,QWORD PTR [rsp+0x90]
  65d1ee:	48 83 ef 18          	sub    rdi,0x18
  65d1f2:	48 39 fb             	cmp    rbx,rdi
  65d1f5:	0f 85 9f 02 00 00    	jne    65d49a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x108a>
  65d1fb:	4c 8d 74 24 60       	lea    r14,[rsp+0x60]
  65d200:	48 8d 94 24 dc 03 00 00 	lea    rdx,[rsp+0x3dc]
  65d208:	be 60 7c fb 00       	mov    esi,0xfb7c60
  65d20d:	4c 89 f7             	mov    rdi,r14
  65d210:	e8 43 8c ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d215:	4c 8d 6c 24 50       	lea    r13,[rsp+0x50]
  65d21a:	48 8d 94 24 db 03 00 00 	lea    rdx,[rsp+0x3db]
  65d222:	be c0 7c fb 00       	mov    esi,0xfb7cc0
  65d227:	4c 89 ef             	mov    rdi,r13
  65d22a:	e8 29 8c ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d22f:	4c 8d 64 24 40       	lea    r12,[rsp+0x40]
  65d234:	48 8d 94 24 da 03 00 00 	lea    rdx,[rsp+0x3da]
  65d23c:	be d0 ea fa 00       	mov    esi,0xfaead0
  65d241:	4c 89 e7             	mov    rdi,r12
  65d244:	e8 0f 8c ef ff       	call   555e58 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::basic_string(wchar_t const*, std::allocator<wchar_t> const&)@plt>
  65d249:	41 b9 b0 f0 65 00    	mov    r9d,0x65f0b0
  65d24f:	41 b8 10 f0 65 00    	mov    r8d,0x65f010
  65d255:	4c 89 f1             	mov    rcx,r14
  65d258:	4c 89 ea             	mov    rdx,r13
  65d25b:	4c 89 e6             	mov    rsi,r12
  65d25e:	48 89 ef             	mov    rdi,rbp
  65d261:	c7 44 24 20 04 00 00 00 	mov    DWORD PTR [rsp+0x20],0x4
  65d269:	c7 44 24 18 05 00 00 00 	mov    DWORD PTR [rsp+0x18],0x5
  65d271:	48 c7 44 24 10 00 00 00 00 	mov    QWORD PTR [rsp+0x10],0x0
  65d27a:	48 c7 44 24 08 e0 e3 65 00 	mov    QWORD PTR [rsp+0x8],0x65e3e0
  65d283:	48 c7 04 24 40 27 65 00 	mov    QWORD PTR [rsp],0x652740
  65d28b:	e8 50 1b 0a 00       	call   6fede0 <CDescriptor::AddPropertyWithInterpreterFunctions(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, void*, void*, unsigned int (*)(CEditorScene*, CEditorBaseObject*, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > const&, void*), std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > (*)(CEditorScene*, CEditorBaseObject*, unsigned int, void*), void*, EVARIABLE_TYPES, int)>
  65d290:	48 8b 7c 24 40       	mov    rdi,QWORD PTR [rsp+0x40]
  65d295:	48 83 ef 18          	sub    rdi,0x18
  65d299:	48 39 fb             	cmp    rbx,rdi
  65d29c:	0f 85 b8 02 00 00    	jne    65d55a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x114a>
  65d2a2:	48 8b 7c 24 50       	mov    rdi,QWORD PTR [rsp+0x50]
  65d2a7:	48 83 ef 18          	sub    rdi,0x18
  65d2ab:	48 39 fb             	cmp    rbx,rdi
  65d2ae:	0f 85 1e 01 00 00    	jne    65d3d2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xfc2>
  65d2b4:	48 8b 7c 24 60       	mov    rdi,QWORD PTR [rsp+0x60]
  65d2b9:	48 83 ef 18          	sub    rdi,0x18
  65d2bd:	48 39 fb             	cmp    rbx,rdi
  65d2c0:	75 4f                	jne    65d311 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf01>
  65d2c2:	44 89 fa             	mov    edx,r15d
  65d2c5:	89 c6                	mov    esi,eax
  65d2c7:	48 89 ef             	mov    rdi,rbp
  65d2ca:	e8 f1 bf 09 00       	call   6f92c0 <CDescriptor::LinkProperty(unsigned int, unsigned int)>
  65d2cf:	48 81 c4 18 04 00 00 	add    rsp,0x418
  65d2d6:	5b                   	pop    rbx
  65d2d7:	5d                   	pop    rbp
  65d2d8:	41 5c                	pop    r12
  65d2da:	41 5d                	pop    r13
  65d2dc:	41 5e                	pop    r14
  65d2de:	41 5f                	pop    r15
  65d2e0:	c3                   	ret
  65d2e1:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d2e6:	48 85 c0             	test   rax,rax
  65d2e9:	0f 84 06 0e 00 00    	je     65e0f5 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1ce5>
  65d2ef:	83 c8 ff             	or     eax,0xffffffff
  65d2f2:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d2f7:	85 c0                	test   eax,eax
  65d2f9:	0f 8f 9a f2 ff ff    	jg     65c599 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x189>
  65d2ff:	48 8d b4 24 d9 03 00 00 	lea    rsi,[rsp+0x3d9]
  65d307:	e8 3c 62 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d30c:	e9 88 f2 ff ff       	jmp    65c599 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x189>
  65d311:	ba c8 41 55 00       	mov    edx,0x5541c8
  65d316:	48 85 d2             	test   rdx,rdx
  65d319:	0f 84 fe 0e 00 00    	je     65e21d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e0d>
  65d31f:	83 ca ff             	or     edx,0xffffffff
  65d322:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  65d327:	85 d2                	test   edx,edx
  65d329:	7f 97                	jg     65d2c2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xeb2>
  65d32b:	48 8d b4 24 a4 03 00 00 	lea    rsi,[rsp+0x3a4]
  65d333:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  65d337:	e8 0c 62 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d33c:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  65d340:	eb 80                	jmp    65d2c2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xeb2>
  65d342:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d347:	48 85 c0             	test   rax,rax
  65d34a:	0f 84 ed 0d 00 00    	je     65e13d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d2d>
  65d350:	83 c8 ff             	or     eax,0xffffffff
  65d353:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d358:	85 c0                	test   eax,eax
  65d35a:	0f 8f f7 f9 ff ff    	jg     65cd57 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x947>
  65d360:	48 8d b4 24 b9 03 00 00 	lea    rsi,[rsp+0x3b9]
  65d368:	e8 db 61 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d36d:	e9 e5 f9 ff ff       	jmp    65cd57 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x947>
  65d372:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d377:	48 85 c0             	test   rax,rax
  65d37a:	0f 84 7d 0f 00 00    	je     65e2fd <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1eed>
  65d380:	83 c8 ff             	or     eax,0xffffffff
  65d383:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d388:	85 c0                	test   eax,eax
  65d38a:	0f 8f 41 fe ff ff    	jg     65d1d1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdc1>
  65d390:	48 8d b4 24 a9 03 00 00 	lea    rsi,[rsp+0x3a9]
  65d398:	e8 ab 61 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d39d:	e9 2f fe ff ff       	jmp    65d1d1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdc1>
  65d3a2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d3a7:	48 85 c0             	test   rax,rax
  65d3aa:	0f 84 55 0d 00 00    	je     65e105 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1cf5>
  65d3b0:	83 c8 ff             	or     eax,0xffffffff
  65d3b3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d3b8:	85 c0                	test   eax,eax
  65d3ba:	0f 8f b8 f5 ff ff    	jg     65c978 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x568>
  65d3c0:	48 8d b4 24 c9 03 00 00 	lea    rsi,[rsp+0x3c9]
  65d3c8:	e8 7b 61 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d3cd:	e9 a6 f5 ff ff       	jmp    65c978 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x568>
  65d3d2:	ba c8 41 55 00       	mov    edx,0x5541c8
  65d3d7:	48 85 d2             	test   rdx,rdx
  65d3da:	0f 84 ad 0e 00 00    	je     65e28d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e7d>
  65d3e0:	83 ca ff             	or     edx,0xffffffff
  65d3e3:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  65d3e8:	85 d2                	test   edx,edx
  65d3ea:	0f 8f c4 fe ff ff    	jg     65d2b4 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xea4>
  65d3f0:	48 8d b4 24 a5 03 00 00 	lea    rsi,[rsp+0x3a5]
  65d3f8:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  65d3fc:	e8 47 61 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d401:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  65d405:	e9 aa fe ff ff       	jmp    65d2b4 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xea4>
  65d40a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d40f:	48 85 c0             	test   rax,rax
  65d412:	0f 84 95 0d 00 00    	je     65e1ad <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d9d>
  65d418:	83 c8 ff             	or     eax,0xffffffff
  65d41b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d420:	85 c0                	test   eax,eax
  65d422:	0f 8f 81 f7 ff ff    	jg     65cba9 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x799>
  65d428:	48 8d b4 24 c1 03 00 00 	lea    rsi,[rsp+0x3c1]
  65d430:	e8 13 61 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d435:	e9 6f f7 ff ff       	jmp    65cba9 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x799>
  65d43a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d43f:	48 85 c0             	test   rax,rax
  65d442:	0f 84 25 0f 00 00    	je     65e36d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f5d>
  65d448:	83 c8 ff             	or     eax,0xffffffff
  65d44b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d450:	85 c0                	test   eax,eax
  65d452:	0f 8f 30 fb ff ff    	jg     65cf88 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb78>
  65d458:	48 8d b4 24 b1 03 00 00 	lea    rsi,[rsp+0x3b1]
  65d460:	e8 e3 60 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d465:	e9 1e fb ff ff       	jmp    65cf88 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb78>
  65d46a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d46f:	48 85 c0             	test   rax,rax
  65d472:	0f 84 a9 0c 00 00    	je     65e121 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d11>
  65d478:	83 c8 ff             	or     eax,0xffffffff
  65d47b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d480:	85 c0                	test   eax,eax
  65d482:	0f 8f bf f2 ff ff    	jg     65c747 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x337>
  65d488:	48 8d b4 24 d1 03 00 00 	lea    rsi,[rsp+0x3d1]
  65d490:	e8 b3 60 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d495:	e9 ad f2 ff ff       	jmp    65c747 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x337>
  65d49a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d49f:	48 85 c0             	test   rax,rax
  65d4a2:	0f 84 ad 0d 00 00    	je     65e255 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e45>
  65d4a8:	83 c8 ff             	or     eax,0xffffffff
  65d4ab:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d4b0:	85 c0                	test   eax,eax
  65d4b2:	0f 8f 43 fd ff ff    	jg     65d1fb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdeb>
  65d4b8:	48 8d b4 24 a7 03 00 00 	lea    rsi,[rsp+0x3a7]
  65d4c0:	e8 83 60 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d4c5:	e9 31 fd ff ff       	jmp    65d1fb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdeb>
  65d4ca:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d4cf:	48 85 c0             	test   rax,rax
  65d4d2:	0f 84 9d 0c 00 00    	je     65e175 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d65>
  65d4d8:	83 c8 ff             	or     eax,0xffffffff
  65d4db:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d4e0:	85 c0                	test   eax,eax
  65d4e2:	0f 8f 98 f7 ff ff    	jg     65cc80 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x870>
  65d4e8:	48 8d b4 24 bd 03 00 00 	lea    rsi,[rsp+0x3bd]
  65d4f0:	e8 53 60 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d4f5:	e9 86 f7 ff ff       	jmp    65cc80 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x870>
  65d4fa:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d4ff:	48 85 c0             	test   rax,rax
  65d502:	0f 84 2d 0e 00 00    	je     65e335 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f25>
  65d508:	83 c8 ff             	or     eax,0xffffffff
  65d50b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d510:	85 c0                	test   eax,eax
  65d512:	0f 8f 47 fb ff ff    	jg     65d05f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc4f>
  65d518:	48 8d b4 24 ad 03 00 00 	lea    rsi,[rsp+0x3ad]
  65d520:	e8 23 60 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d525:	e9 35 fb ff ff       	jmp    65d05f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc4f>
  65d52a:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d52f:	48 85 c0             	test   rax,rax
  65d532:	0f 84 db 0b 00 00    	je     65e113 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d03>
  65d538:	83 c8 ff             	or     eax,0xffffffff
  65d53b:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d540:	85 c0                	test   eax,eax
  65d542:	0f 8f 59 f3 ff ff    	jg     65c8a1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x491>
  65d548:	48 8d b4 24 cd 03 00 00 	lea    rsi,[rsp+0x3cd]
  65d550:	e8 f3 5f ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d555:	e9 47 f3 ff ff       	jmp    65c8a1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x491>
  65d55a:	ba c8 41 55 00       	mov    edx,0x5541c8
  65d55f:	48 85 d2             	test   rdx,rdx
  65d562:	0f 84 5d 0d 00 00    	je     65e2c5 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1eb5>
  65d568:	83 ca ff             	or     edx,0xffffffff
  65d56b:	f0 0f c1 57 10       	lock xadd DWORD PTR [rdi+0x10],edx
  65d570:	85 d2                	test   edx,edx
  65d572:	0f 8f 2a fd ff ff    	jg     65d2a2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xe92>
  65d578:	48 8d b4 24 a6 03 00 00 	lea    rsi,[rsp+0x3a6]
  65d580:	89 44 24 38          	mov    DWORD PTR [rsp+0x38],eax
  65d584:	e8 bf 5f ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d589:	8b 44 24 38          	mov    eax,DWORD PTR [rsp+0x38]
  65d58d:	e9 10 fd ff ff       	jmp    65d2a2 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xe92>
  65d592:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d597:	48 85 c0             	test   rax,rax
  65d59a:	0f 84 45 0c 00 00    	je     65e1e5 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1dd5>
  65d5a0:	83 c8 ff             	or     eax,0xffffffff
  65d5a3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d5a8:	85 c0                	test   eax,eax
  65d5aa:	0f 8f 9f f4 ff ff    	jg     65ca4f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x63f>
  65d5b0:	48 8d b4 24 c5 03 00 00 	lea    rsi,[rsp+0x3c5]
  65d5b8:	e8 8b 5f ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d5bd:	e9 8d f4 ff ff       	jmp    65ca4f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x63f>
  65d5c2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d5c7:	48 85 c0             	test   rax,rax
  65d5ca:	0f 84 d5 0d 00 00    	je     65e3a5 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f95>
  65d5d0:	83 c8 ff             	or     eax,0xffffffff
  65d5d3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d5d8:	85 c0                	test   eax,eax
  65d5da:	0f 8f d1 f8 ff ff    	jg     65ceb1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xaa1>
  65d5e0:	48 8d b4 24 b5 03 00 00 	lea    rsi,[rsp+0x3b5]
  65d5e8:	e8 5b 5f ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d5ed:	e9 bf f8 ff ff       	jmp    65ceb1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xaa1>
  65d5f2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d5f7:	48 85 c0             	test   rax,rax
  65d5fa:	0f 84 2f 0b 00 00    	je     65e12f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d1f>
  65d600:	83 c8 ff             	or     eax,0xffffffff
  65d603:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d608:	85 c0                	test   eax,eax
  65d60a:	0f 8f 60 f0 ff ff    	jg     65c670 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x260>
  65d610:	48 8d b4 24 d5 03 00 00 	lea    rsi,[rsp+0x3d5]
  65d618:	e8 2b 5f ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d61d:	e9 4e f0 ff ff       	jmp    65c670 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x260>
  65d622:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d627:	48 85 c0             	test   rax,rax
  65d62a:	0f 84 09 0c 00 00    	je     65e239 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e29>
  65d630:	83 c8 ff             	or     eax,0xffffffff
  65d633:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d638:	85 c0                	test   eax,eax
  65d63a:	0f 8f a6 fb ff ff    	jg     65d1e6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdd6>
  65d640:	48 8d b4 24 a8 03 00 00 	lea    rsi,[rsp+0x3a8]
  65d648:	e8 fb 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d64d:	e9 94 fb ff ff       	jmp    65d1e6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xdd6>
  65d652:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d657:	48 85 c0             	test   rax,rax
  65d65a:	0f 84 f9 0a 00 00    	je     65e159 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d49>
  65d660:	83 c8 ff             	or     eax,0xffffffff
  65d663:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d668:	85 c0                	test   eax,eax
  65d66a:	0f 8f bd f6 ff ff    	jg     65cd2d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x91d>
  65d670:	48 8d b4 24 bb 03 00 00 	lea    rsi,[rsp+0x3bb]
  65d678:	e8 cb 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d67d:	e9 ab f6 ff ff       	jmp    65cd2d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x91d>
  65d682:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d687:	48 85 c0             	test   rax,rax
  65d68a:	0f 84 89 0c 00 00    	je     65e319 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f09>
  65d690:	83 c8 ff             	or     eax,0xffffffff
  65d693:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d698:	85 c0                	test   eax,eax
  65d69a:	0f 8f 6c fa ff ff    	jg     65d10c <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xcfc>
  65d6a0:	48 8d b4 24 ab 03 00 00 	lea    rsi,[rsp+0x3ab]
  65d6a8:	e8 9b 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d6ad:	e9 5a fa ff ff       	jmp    65d10c <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xcfc>
  65d6b2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d6b7:	48 85 c0             	test   rax,rax
  65d6ba:	0f 84 09 0b 00 00    	je     65e1c9 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1db9>
  65d6c0:	83 c8 ff             	or     eax,0xffffffff
  65d6c3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d6c8:	85 c0                	test   eax,eax
  65d6ca:	0f 8f fb f1 ff ff    	jg     65c8cb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x4bb>
  65d6d0:	48 8d b4 24 cb 03 00 00 	lea    rsi,[rsp+0x3cb]
  65d6d8:	e8 6b 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d6dd:	e9 e9 f1 ff ff       	jmp    65c8cb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x4bb>
  65d6e2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d6e7:	48 85 c0             	test   rax,rax
  65d6ea:	0f 84 b9 0b 00 00    	je     65e2a9 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e99>
  65d6f0:	83 c8 ff             	or     eax,0xffffffff
  65d6f3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d6f8:	85 c0                	test   eax,eax
  65d6fa:	0f 8f db f7 ff ff    	jg     65cedb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xacb>
  65d700:	48 8d b4 24 b3 03 00 00 	lea    rsi,[rsp+0x3b3]
  65d708:	e8 3b 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d70d:	e9 c9 f7 ff ff       	jmp    65cedb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xacb>
  65d712:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d717:	48 85 c0             	test   rax,rax
  65d71a:	0f 84 71 0a 00 00    	je     65e191 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d81>
  65d720:	83 c8 ff             	or     eax,0xffffffff
  65d723:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d728:	85 c0                	test   eax,eax
  65d72a:	0f 8f cc f3 ff ff    	jg     65cafc <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x6ec>
  65d730:	48 8d b4 24 c3 03 00 00 	lea    rsi,[rsp+0x3c3]
  65d738:	e8 0b 5e ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d73d:	e9 ba f3 ff ff       	jmp    65cafc <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x6ec>
  65d742:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d747:	48 85 c0             	test   rax,rax
  65d74a:	0f 84 39 0c 00 00    	je     65e389 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f79>
  65d750:	83 c8 ff             	or     eax,0xffffffff
  65d753:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d758:	85 c0                	test   eax,eax
  65d75a:	0f 8f d5 f8 ff ff    	jg     65d035 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc25>
  65d760:	48 8d b4 24 af 03 00 00 	lea    rsi,[rsp+0x3af]
  65d768:	e8 db 5d ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d76d:	e9 c3 f8 ff ff       	jmp    65d035 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc25>
  65d772:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d777:	48 85 c0             	test   rax,rax
  65d77a:	0f 84 81 0a 00 00    	je     65e201 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1df1>
  65d780:	83 c8 ff             	or     eax,0xffffffff
  65d783:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d788:	85 c0                	test   eax,eax
  65d78a:	0f 8f 8d ef ff ff    	jg     65c71d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x30d>
  65d790:	48 8d b4 24 d3 03 00 00 	lea    rsi,[rsp+0x3d3]
  65d798:	e8 ab 5d ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d79d:	e9 7b ef ff ff       	jmp    65c71d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x30d>
  65d7a2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d7a7:	48 85 c0             	test   rax,rax
  65d7aa:	0f 84 c1 0a 00 00    	je     65e271 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e61>
  65d7b0:	83 c8 ff             	or     eax,0xffffffff
  65d7b3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d7b8:	85 c0                	test   eax,eax
  65d7ba:	0f 8f 44 f6 ff ff    	jg     65ce04 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x9f4>
  65d7c0:	48 8d b4 24 b7 03 00 00 	lea    rsi,[rsp+0x3b7]
  65d7c8:	e8 7b 5d ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d7cd:	e9 32 f6 ff ff       	jmp    65ce04 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x9f4>
  65d7d2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d7d7:	48 85 c0             	test   rax,rax
  65d7da:	0f 84 6b 09 00 00    	je     65e14b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d3b>
  65d7e0:	83 c8 ff             	or     eax,0xffffffff
  65d7e3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d7e8:	85 c0                	test   eax,eax
  65d7ea:	0f 8f e3 f3 ff ff    	jg     65cbd3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x7c3>
  65d7f0:	48 8d b4 24 bf 03 00 00 	lea    rsi,[rsp+0x3bf]
  65d7f8:	e8 4b 5d ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d7fd:	e9 d1 f3 ff ff       	jmp    65cbd3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x7c3>
  65d802:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d807:	48 85 c0             	test   rax,rax
  65d80a:	0f 84 41 0b 00 00    	je     65e351 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f41>
  65d810:	83 c8 ff             	or     eax,0xffffffff
  65d813:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d818:	85 c0                	test   eax,eax
  65d81a:	0f 8f 01 f9 ff ff    	jg     65d121 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xd11>
  65d820:	48 8d b4 24 aa 03 00 00 	lea    rsi,[rsp+0x3aa]
  65d828:	e8 1b 5d ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d82d:	e9 ef f8 ff ff       	jmp    65d121 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xd11>
  65d832:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d837:	48 85 c0             	test   rax,rax
  65d83a:	0f 84 7b 09 00 00    	je     65e1bb <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1dab>
  65d840:	83 c8 ff             	or     eax,0xffffffff
  65d843:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d848:	85 c0                	test   eax,eax
  65d84a:	0f 8f a4 ef ff ff    	jg     65c7f4 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3e4>
  65d850:	48 8d b4 24 cf 03 00 00 	lea    rsi,[rsp+0x3cf]
  65d858:	e8 eb 5c ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d85d:	e9 92 ef ff ff       	jmp    65c7f4 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3e4>
  65d862:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d867:	48 85 c0             	test   rax,rax
  65d86a:	0f 84 71 0a 00 00    	je     65e2e1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1ed1>
  65d870:	83 c8 ff             	or     eax,0xffffffff
  65d873:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d878:	85 c0                	test   eax,eax
  65d87a:	0f 8f f3 f6 ff ff    	jg     65cf73 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb63>
  65d880:	48 8d b4 24 b2 03 00 00 	lea    rsi,[rsp+0x3b2]
  65d888:	e8 bb 5c ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d88d:	e9 e1 f6 ff ff       	jmp    65cf73 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb63>
  65d892:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d897:	48 85 c0             	test   rax,rax
  65d89a:	0f 84 e3 08 00 00    	je     65e183 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d73>
  65d8a0:	83 c8 ff             	or     eax,0xffffffff
  65d8a3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d8a8:	85 c0                	test   eax,eax
  65d8aa:	0f 8f 75 f1 ff ff    	jg     65ca25 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x615>
  65d8b0:	48 8d b4 24 c7 03 00 00 	lea    rsi,[rsp+0x3c7]
  65d8b8:	e8 8b 5c ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d8bd:	e9 63 f1 ff ff       	jmp    65ca25 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x615>
  65d8c2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d8c7:	48 85 c0             	test   rax,rax
  65d8ca:	0f 84 f1 0a 00 00    	je     65e3c1 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1fb1>
  65d8d0:	83 c8 ff             	or     eax,0xffffffff
  65d8d3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d8d8:	85 c0                	test   eax,eax
  65d8da:	0f 8f 6a f7 ff ff    	jg     65d04a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc3a>
  65d8e0:	48 8d b4 24 ae 03 00 00 	lea    rsi,[rsp+0x3ae]
  65d8e8:	e8 5b 5c ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d8ed:	e9 58 f7 ff ff       	jmp    65d04a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xc3a>
  65d8f2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d8f7:	48 85 c0             	test   rax,rax
  65d8fa:	0f 84 f3 08 00 00    	je     65e1f3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1de3>
  65d900:	83 c8 ff             	or     eax,0xffffffff
  65d903:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d908:	85 c0                	test   eax,eax
  65d90a:	0f 8f b3 ec ff ff    	jg     65c5c3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1b3>
  65d910:	48 8d b4 24 d7 03 00 00 	lea    rsi,[rsp+0x3d7]
  65d918:	e8 2b 5c ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d91d:	e9 a1 ec ff ff       	jmp    65c5c3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1b3>
  65d922:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d927:	48 85 c0             	test   rax,rax
  65d92a:	0f 84 fb 08 00 00    	je     65e22b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e1b>
  65d930:	83 c8 ff             	or     eax,0xffffffff
  65d933:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d938:	85 c0                	test   eax,eax
  65d93a:	0f 8f d9 f4 ff ff    	jg     65ce19 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xa09>
  65d940:	48 8d b4 24 b6 03 00 00 	lea    rsi,[rsp+0x3b6]
  65d948:	e8 fb 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d94d:	e9 c7 f4 ff ff       	jmp    65ce19 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xa09>
  65d952:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d957:	48 85 c0             	test   rax,rax
  65d95a:	0f 84 07 08 00 00    	je     65e167 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d57>
  65d960:	83 c8 ff             	or     eax,0xffffffff
  65d963:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d968:	85 c0                	test   eax,eax
  65d96a:	0f 8f d2 f3 ff ff    	jg     65cd42 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x932>
  65d970:	48 8d b4 24 ba 03 00 00 	lea    rsi,[rsp+0x3ba]
  65d978:	e8 cb 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d97d:	e9 c0 f3 ff ff       	jmp    65cd42 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x932>
  65d982:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d987:	48 85 c0             	test   rax,rax
  65d98a:	0f 84 7b 09 00 00    	je     65e30b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1efb>
  65d990:	83 c8 ff             	or     eax,0xffffffff
  65d993:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d998:	85 c0                	test   eax,eax
  65d99a:	0f 8f 57 f7 ff ff    	jg     65d0f7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xce7>
  65d9a0:	48 8d b4 24 ac 03 00 00 	lea    rsi,[rsp+0x3ac]
  65d9a8:	e8 9b 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d9ad:	e9 45 f7 ff ff       	jmp    65d0f7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xce7>
  65d9b2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d9b7:	48 85 c0             	test   rax,rax
  65d9ba:	0f 84 17 08 00 00    	je     65e1d7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1dc7>
  65d9c0:	83 c8 ff             	or     eax,0xffffffff
  65d9c3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d9c8:	85 c0                	test   eax,eax
  65d9ca:	0f 8f 93 ef ff ff    	jg     65c963 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x553>
  65d9d0:	48 8d b4 24 ca 03 00 00 	lea    rsi,[rsp+0x3ca]
  65d9d8:	e8 6b 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65d9dd:	e9 81 ef ff ff       	jmp    65c963 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x553>
  65d9e2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65d9e7:	48 85 c0             	test   rax,rax
  65d9ea:	0f 84 ab 08 00 00    	je     65e29b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e8b>
  65d9f0:	83 c8 ff             	or     eax,0xffffffff
  65d9f3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65d9f8:	85 c0                	test   eax,eax
  65d9fa:	0f 8f c6 f4 ff ff    	jg     65cec6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xab6>
  65da00:	48 8d b4 24 b4 03 00 00 	lea    rsi,[rsp+0x3b4]
  65da08:	e8 3b 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65da0d:	e9 b4 f4 ff ff       	jmp    65cec6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xab6>
  65da12:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65da17:	48 85 c0             	test   rax,rax
  65da1a:	0f 84 7f 07 00 00    	je     65e19f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1d8f>
  65da20:	83 c8 ff             	or     eax,0xffffffff
  65da23:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65da28:	85 c0                	test   eax,eax
  65da2a:	0f 8f e1 f0 ff ff    	jg     65cb11 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x701>
  65da30:	48 8d b4 24 c2 03 00 00 	lea    rsi,[rsp+0x3c2]
  65da38:	e8 0b 5b ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65da3d:	e9 cf f0 ff ff       	jmp    65cb11 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x701>
  65da42:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65da47:	48 85 c0             	test   rax,rax
  65da4a:	0f 84 2b 09 00 00    	je     65e37b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f6b>
  65da50:	83 c8 ff             	or     eax,0xffffffff
  65da53:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65da58:	85 c0                	test   eax,eax
  65da5a:	0f 8f 3d f5 ff ff    	jg     65cf9d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb8d>
  65da60:	48 8d b4 24 b0 03 00 00 	lea    rsi,[rsp+0x3b0]
  65da68:	e8 db 5a ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65da6d:	e9 2b f5 ff ff       	jmp    65cf9d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xb8d>
  65da72:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65da77:	48 85 c0             	test   rax,rax
  65da7a:	0f 84 8f 07 00 00    	je     65e20f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1dff>
  65da80:	83 c8 ff             	or     eax,0xffffffff
  65da83:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65da88:	85 c0                	test   eax,eax
  65da8a:	0f 8f a2 ec ff ff    	jg     65c732 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x322>
  65da90:	48 8d b4 24 d2 03 00 00 	lea    rsi,[rsp+0x3d2]
  65da98:	e8 ab 5a ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65da9d:	e9 90 ec ff ff       	jmp    65c732 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x322>
  65daa2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65daa7:	48 85 c0             	test   rax,rax
  65daaa:	0f 84 b3 07 00 00    	je     65e263 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e53>
  65dab0:	83 c8 ff             	or     eax,0xffffffff
  65dab3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dab8:	85 c0                	test   eax,eax
  65daba:	0f 8f 2f f3 ff ff    	jg     65cdef <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x9df>
  65dac0:	48 8d b4 24 b8 03 00 00 	lea    rsi,[rsp+0x3b8]
  65dac8:	e8 7b 5a ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dacd:	e9 1d f3 ff ff       	jmp    65cdef <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x9df>
  65dad2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dad7:	48 85 c0             	test   rax,rax
  65dada:	0f 84 63 08 00 00    	je     65e343 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f33>
  65dae0:	83 c8 ff             	or     eax,0xffffffff
  65dae3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dae8:	85 c0                	test   eax,eax
  65daea:	0f 8f 7b f1 ff ff    	jg     65cc6b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x85b>
  65daf0:	48 8d b4 24 be 03 00 00 	lea    rsi,[rsp+0x3be]
  65daf8:	e8 4b 5a ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dafd:	e9 69 f1 ff ff       	jmp    65cc6b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x85b>
  65db02:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65db07:	48 85 c0             	test   rax,rax
  65db0a:	0f 84 c3 07 00 00    	je     65e2d3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1ec3>
  65db10:	83 c8 ff             	or     eax,0xffffffff
  65db13:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65db18:	85 c0                	test   eax,eax
  65db1a:	0f 8f e9 ec ff ff    	jg     65c809 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3f9>
  65db20:	48 8d b4 24 ce 03 00 00 	lea    rsi,[rsp+0x3ce]
  65db28:	e8 1b 5a ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65db2d:	e9 d7 ec ff ff       	jmp    65c809 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3f9>
  65db32:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65db37:	48 85 c0             	test   rax,rax
  65db3a:	0f 84 73 08 00 00    	je     65e3b3 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1fa3>
  65db40:	83 c8 ff             	or     eax,0xffffffff
  65db43:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65db48:	85 c0                	test   eax,eax
  65db4a:	0f 8f ea ee ff ff    	jg     65ca3a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x62a>
  65db50:	48 8d b4 24 c6 03 00 00 	lea    rsi,[rsp+0x3c6]
  65db58:	e8 eb 59 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65db5d:	e9 d8 ee ff ff       	jmp    65ca3a <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x62a>
  65db62:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65db67:	48 85 c0             	test   rax,rax
  65db6a:	0f 84 d7 06 00 00    	je     65e247 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e37>
  65db70:	83 c8 ff             	or     eax,0xffffffff
  65db73:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65db78:	85 c0                	test   eax,eax
  65db7a:	0f 8f db ea ff ff    	jg     65c65b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x24b>
  65db80:	48 8d b4 24 d6 03 00 00 	lea    rsi,[rsp+0x3d6]
  65db88:	e8 bb 59 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65db8d:	e9 c9 ea ff ff       	jmp    65c65b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x24b>
  65db92:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65db97:	48 85 c0             	test   rax,rax
  65db9a:	0f 84 87 07 00 00    	je     65e327 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f17>
  65dba0:	83 c8 ff             	or     eax,0xffffffff
  65dba3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dba8:	85 c0                	test   eax,eax
  65dbaa:	0f 8f e5 f0 ff ff    	jg     65cc95 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x885>
  65dbb0:	48 8d b4 24 bc 03 00 00 	lea    rsi,[rsp+0x3bc]
  65dbb8:	e8 8b 59 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dbbd:	e9 d3 f0 ff ff       	jmp    65cc95 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x885>
  65dbc2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dbc7:	48 85 c0             	test   rax,rax
  65dbca:	0f 84 e7 06 00 00    	je     65e2b7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1ea7>
  65dbd0:	83 c8 ff             	or     eax,0xffffffff
  65dbd3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dbd8:	85 c0                	test   eax,eax
  65dbda:	0f 8f d6 ec ff ff    	jg     65c8b6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x4a6>
  65dbe0:	48 8d b4 24 cc 03 00 00 	lea    rsi,[rsp+0x3cc]
  65dbe8:	e8 5b 59 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dbed:	e9 c4 ec ff ff       	jmp    65c8b6 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x4a6>
  65dbf2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dbf7:	48 85 c0             	test   rax,rax
  65dbfa:	0f 84 97 07 00 00    	je     65e397 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f87>
  65dc00:	83 c8 ff             	or     eax,0xffffffff
  65dc03:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dc08:	85 c0                	test   eax,eax
  65dc0a:	0f 8f d7 ee ff ff    	jg     65cae7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x6d7>
  65dc10:	48 8d b4 24 c4 03 00 00 	lea    rsi,[rsp+0x3c4]
  65dc18:	e8 2b 59 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dc1d:	e9 c5 ee ff ff       	jmp    65cae7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x6d7>
  65dc22:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dc27:	48 85 c0             	test   rax,rax
  65dc2a:	0f 84 4f 06 00 00    	je     65e27f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1e6f>
  65dc30:	83 c8 ff             	or     eax,0xffffffff
  65dc33:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dc38:	85 c0                	test   eax,eax
  65dc3a:	0f 8f 45 ea ff ff    	jg     65c685 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x275>
  65dc40:	48 8d b4 24 d4 03 00 00 	lea    rsi,[rsp+0x3d4]
  65dc48:	e8 fb 58 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dc4d:	e9 33 ea ff ff       	jmp    65c685 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x275>
  65dc52:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dc57:	48 85 c0             	test   rax,rax
  65dc5a:	0f 84 ff 06 00 00    	je     65e35f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1f4f>
  65dc60:	83 c8 ff             	or     eax,0xffffffff
  65dc63:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dc68:	85 c0                	test   eax,eax
  65dc6a:	0f 8f 4e ef ff ff    	jg     65cbbe <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x7ae>
  65dc70:	48 8d b4 24 c0 03 00 00 	lea    rsi,[rsp+0x3c0]
  65dc78:	e8 cb 58 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dc7d:	e9 3c ef ff ff       	jmp    65cbbe <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x7ae>
  65dc82:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dc87:	48 85 c0             	test   rax,rax
  65dc8a:	0f 84 5f 06 00 00    	je     65e2ef <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1edf>
  65dc90:	83 c8 ff             	or     eax,0xffffffff
  65dc93:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dc98:	85 c0                	test   eax,eax
  65dc9a:	0f 8f 3f eb ff ff    	jg     65c7df <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3cf>
  65dca0:	48 8d b4 24 d0 03 00 00 	lea    rsi,[rsp+0x3d0]
  65dca8:	e8 9b 58 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dcad:	e9 2d eb ff ff       	jmp    65c7df <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x3cf>
  65dcb2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dcb7:	48 85 c0             	test   rax,rax
  65dcba:	0f 84 0f 07 00 00    	je     65e3cf <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1fbf>
  65dcc0:	83 c8 ff             	or     eax,0xffffffff
  65dcc3:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dcc8:	85 c0                	test   eax,eax
  65dcca:	0f 8f bd ec ff ff    	jg     65c98d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x57d>
  65dcd0:	48 8d b4 24 c8 03 00 00 	lea    rsi,[rsp+0x3c8]
  65dcd8:	e8 6b 58 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dcdd:	e9 ab ec ff ff       	jmp    65c98d <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x57d>
  65dce2:	b8 c8 41 55 00       	mov    eax,0x5541c8
  65dce7:	48 85 c0             	test   rax,rax
  65dcea:	74 42                	je     65dd2e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x191e>
  65dcec:	83 c8 ff             	or     eax,0xffffffff
  65dcef:	f0 0f c1 47 10       	lock xadd DWORD PTR [rdi+0x10],eax
  65dcf4:	85 c0                	test   eax,eax
  65dcf6:	0f 8f b2 e8 ff ff    	jg     65c5ae <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x19e>
  65dcfc:	48 8d b4 24 d8 03 00 00 	lea    rsi,[rsp+0x3d8]
  65dd04:	e8 3f 58 ef ff       	call   553548 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::_Rep::_M_destroy(std::allocator<wchar_t> const&)@plt>
  65dd09:	e9 a0 e8 ff ff       	jmp    65c5ae <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x19e>
  65dd0e:	49 89 c7             	mov    r15,rax
  65dd11:	4c 89 f7             	mov    rdi,r14
  65dd14:	e8 bf 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd19:	48 89 ef             	mov    rdi,rbp
  65dd1c:	e8 ef a6 fe ff       	call   648410 <CShapeDescriptor::~CShapeDescriptor()>
  65dd21:	4c 89 ff             	mov    rdi,r15
  65dd24:	e8 6f 67 ef ff       	call   554498 <_Unwind_Resume@plt>
  65dd29:	49 89 c7             	mov    r15,rax
  65dd2c:	eb eb                	jmp    65dd19 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1909>
  65dd2e:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65dd31:	8d 50 ff             	lea    edx,[rax-0x1]
  65dd34:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65dd37:	eb bb                	jmp    65dcf4 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18e4>
  65dd39:	eb ee                	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65dd3b:	4c 89 e7             	mov    rdi,r12
  65dd3e:	49 89 c7             	mov    r15,rax
  65dd41:	e8 92 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd46:	4c 89 ef             	mov    rdi,r13
  65dd49:	e8 8a 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd4e:	eb c1                	jmp    65dd11 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1901>
  65dd50:	49 89 c7             	mov    r15,rax
  65dd53:	eb f1                	jmp    65dd46 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1936>
  65dd55:	eb b7                	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65dd57:	eb e2                	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dd59:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  65dd60:	eb ee                	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65dd62:	eb d7                	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dd64:	eb ea                	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65dd66:	49 89 c7             	mov    r15,rax
  65dd69:	4c 89 ef             	mov    rdi,r13
  65dd6c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  65dd70:	e8 63 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd75:	eb a2                	jmp    65dd19 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1909>
  65dd77:	eb b0                	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65dd79:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  65dd80:	eb 8c                	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65dd82:	eb a5                	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65dd84:	48 89 df             	mov    rdi,rbx
  65dd87:	49 89 c7             	mov    r15,rax
  65dd8a:	e8 49 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd8f:	4c 89 e7             	mov    rdi,r12
  65dd92:	e8 41 6b ef ff       	call   5548d8 <std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >::~basic_string()@plt>
  65dd97:	eb d0                	jmp    65dd69 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1959>
  65dd99:	49 89 c7             	mov    r15,rax
  65dd9c:	eb f1                	jmp    65dd8f <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x197f>
  65dd9e:	66 90                	xchg   ax,ax
  65dda0:	eb ae                	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65dda2:	e9 67 ff ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65dda7:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  65ddb0:	eb 89                	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65ddb2:	eb 9c                	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65ddb4:	e9 55 ff ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65ddb9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  65ddc0:	e9 64 ff ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65ddc5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65ddd0:	e9 54 ff ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65ddd5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dde0:	e9 56 ff ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dde5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65ddf0:	e9 5b ff ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65ddf5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de00:	e9 09 ff ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65de05:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de10:	e9 26 ff ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65de15:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de20:	e9 2b ff ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65de25:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de30:	e9 d9 fe ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65de35:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de40:	e9 e4 fe ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65de45:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de50:	e9 d4 fe ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65de55:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de60:	e9 d6 fe ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65de65:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de70:	e9 99 fe ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65de75:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de80:	e9 a4 fe ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65de85:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65de90:	e9 94 fe ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65de95:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dea0:	e9 96 fe ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dea5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65deb0:	e9 9b fe ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65deb5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dec0:	e9 49 fe ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65dec5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65ded0:	e9 54 fe ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65ded5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dee0:	e9 56 fe ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dee5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65def0:	e9 5b fe ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65def5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df00:	e9 09 fe ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65df05:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df10:	e9 26 fe ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65df15:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df20:	e9 2b fe ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65df25:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df30:	e9 d9 fd ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65df35:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df40:	e9 e4 fd ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65df45:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df50:	e9 d4 fd ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65df55:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df60:	e9 d6 fd ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65df65:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df70:	e9 db fd ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65df75:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df80:	e9 89 fd ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65df85:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65df90:	e9 a6 fd ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65df95:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dfa0:	e9 ab fd ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65dfa5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dfb0:	e9 59 fd ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65dfb5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dfc0:	e9 64 fd ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65dfc5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dfd0:	e9 54 fd ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65dfd5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dfe0:	e9 56 fd ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65dfe5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65dff0:	e9 5b fd ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65dff5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e000:	e9 09 fd ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65e005:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e010:	e9 26 fd ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65e015:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e020:	e9 2b fd ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65e025:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e030:	e9 d9 fc ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65e035:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e040:	e9 e4 fc ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65e045:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e050:	e9 d4 fc ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65e055:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e060:	e9 d6 fc ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65e065:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e070:	e9 db fc ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65e075:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e080:	e9 89 fc ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65e085:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e090:	e9 a6 fc ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65e095:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0a0:	e9 ab fc ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65e0a5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0b0:	e9 59 fc ff ff       	jmp    65dd0e <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18fe>
  65e0b5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0c0:	e9 64 fc ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65e0c5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0d0:	e9 66 fc ff ff       	jmp    65dd3b <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x192b>
  65e0d5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0e0:	e9 6b fc ff ff       	jmp    65dd50 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1940>
  65e0e5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
  65e0f0:	e9 34 fc ff ff       	jmp    65dd29 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1919>
  65e0f5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e0f8:	8d 50 ff             	lea    edx,[rax-0x1]
  65e0fb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e0fe:	66 90                	xchg   ax,ax
  65e100:	e9 f2 f1 ff ff       	jmp    65d2f7 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xee7>
  65e105:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e108:	8d 50 ff             	lea    edx,[rax-0x1]
  65e10b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e10e:	e9 a5 f2 ff ff       	jmp    65d3b8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xfa8>
  65e113:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e116:	8d 50 ff             	lea    edx,[rax-0x1]
  65e119:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e11c:	e9 1f f4 ff ff       	jmp    65d540 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1130>
  65e121:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e124:	8d 50 ff             	lea    edx,[rax-0x1]
  65e127:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e12a:	e9 51 f3 ff ff       	jmp    65d480 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1070>
  65e12f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e132:	8d 50 ff             	lea    edx,[rax-0x1]
  65e135:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e138:	e9 cb f4 ff ff       	jmp    65d608 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x11f8>
  65e13d:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e140:	8d 50 ff             	lea    edx,[rax-0x1]
  65e143:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e146:	e9 0d f2 ff ff       	jmp    65d358 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf48>
  65e14b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e14e:	8d 50 ff             	lea    edx,[rax-0x1]
  65e151:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e154:	e9 8f f6 ff ff       	jmp    65d7e8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x13d8>
  65e159:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e15c:	8d 50 ff             	lea    edx,[rax-0x1]
  65e15f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e162:	e9 01 f5 ff ff       	jmp    65d668 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1258>
  65e167:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e16a:	8d 50 ff             	lea    edx,[rax-0x1]
  65e16d:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e170:	e9 f3 f7 ff ff       	jmp    65d968 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1558>
  65e175:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e178:	8d 50 ff             	lea    edx,[rax-0x1]
  65e17b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e17e:	e9 5d f3 ff ff       	jmp    65d4e0 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x10d0>
  65e183:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e186:	8d 50 ff             	lea    edx,[rax-0x1]
  65e189:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e18c:	e9 17 f7 ff ff       	jmp    65d8a8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1498>
  65e191:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e194:	8d 50 ff             	lea    edx,[rax-0x1]
  65e197:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e19a:	e9 89 f5 ff ff       	jmp    65d728 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1318>
  65e19f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1a2:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1a5:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1a8:	e9 7b f8 ff ff       	jmp    65da28 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1618>
  65e1ad:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1b0:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1b3:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1b6:	e9 65 f2 ff ff       	jmp    65d420 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1010>
  65e1bb:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1be:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1c1:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1c4:	e9 7f f6 ff ff       	jmp    65d848 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1438>
  65e1c9:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1cc:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1cf:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1d2:	e9 f1 f4 ff ff       	jmp    65d6c8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x12b8>
  65e1d7:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1da:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1dd:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1e0:	e9 e3 f7 ff ff       	jmp    65d9c8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x15b8>
  65e1e5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1e8:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1eb:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1ee:	e9 b5 f3 ff ff       	jmp    65d5a8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1198>
  65e1f3:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e1f6:	8d 50 ff             	lea    edx,[rax-0x1]
  65e1f9:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e1fc:	e9 07 f7 ff ff       	jmp    65d908 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x14f8>
  65e201:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e204:	8d 50 ff             	lea    edx,[rax-0x1]
  65e207:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e20a:	e9 79 f5 ff ff       	jmp    65d788 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1378>
  65e20f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e212:	8d 50 ff             	lea    edx,[rax-0x1]
  65e215:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e218:	e9 6b f8 ff ff       	jmp    65da88 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1678>
  65e21d:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  65e220:	8d 4a ff             	lea    ecx,[rdx-0x1]
  65e223:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  65e226:	e9 fc f0 ff ff       	jmp    65d327 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf17>
  65e22b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e22e:	8d 50 ff             	lea    edx,[rax-0x1]
  65e231:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e234:	e9 ff f6 ff ff       	jmp    65d938 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1528>
  65e239:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e23c:	8d 50 ff             	lea    edx,[rax-0x1]
  65e23f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e242:	e9 f1 f3 ff ff       	jmp    65d638 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1228>
  65e247:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e24a:	8d 50 ff             	lea    edx,[rax-0x1]
  65e24d:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e250:	e9 23 f9 ff ff       	jmp    65db78 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1768>
  65e255:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e258:	8d 50 ff             	lea    edx,[rax-0x1]
  65e25b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e25e:	e9 4d f2 ff ff       	jmp    65d4b0 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x10a0>
  65e263:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e266:	8d 50 ff             	lea    edx,[rax-0x1]
  65e269:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e26c:	e9 47 f8 ff ff       	jmp    65dab8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x16a8>
  65e271:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e274:	8d 50 ff             	lea    edx,[rax-0x1]
  65e277:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e27a:	e9 39 f5 ff ff       	jmp    65d7b8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x13a8>
  65e27f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e282:	8d 50 ff             	lea    edx,[rax-0x1]
  65e285:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e288:	e9 ab f9 ff ff       	jmp    65dc38 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1828>
  65e28d:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  65e290:	8d 4a ff             	lea    ecx,[rdx-0x1]
  65e293:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  65e296:	e9 4d f1 ff ff       	jmp    65d3e8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xfd8>
  65e29b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e29e:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2a1:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2a4:	e9 4f f7 ff ff       	jmp    65d9f8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x15e8>
  65e2a9:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e2ac:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2af:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2b2:	e9 41 f4 ff ff       	jmp    65d6f8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x12e8>
  65e2b7:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e2ba:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2bd:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2c0:	e9 13 f9 ff ff       	jmp    65dbd8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x17c8>
  65e2c5:	8b 57 10             	mov    edx,DWORD PTR [rdi+0x10]
  65e2c8:	8d 4a ff             	lea    ecx,[rdx-0x1]
  65e2cb:	89 4f 10             	mov    DWORD PTR [rdi+0x10],ecx
  65e2ce:	e9 9d f2 ff ff       	jmp    65d570 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1160>
  65e2d3:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e2d6:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2d9:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2dc:	e9 37 f8 ff ff       	jmp    65db18 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1708>
  65e2e1:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e2e4:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2e7:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2ea:	e9 89 f5 ff ff       	jmp    65d878 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1468>
  65e2ef:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e2f2:	8d 50 ff             	lea    edx,[rax-0x1]
  65e2f5:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e2f8:	e9 9b f9 ff ff       	jmp    65dc98 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1888>
  65e2fd:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e300:	8d 50 ff             	lea    edx,[rax-0x1]
  65e303:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e306:	e9 7d f0 ff ff       	jmp    65d388 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0xf78>
  65e30b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e30e:	8d 50 ff             	lea    edx,[rax-0x1]
  65e311:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e314:	e9 7f f6 ff ff       	jmp    65d998 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1588>
  65e319:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e31c:	8d 50 ff             	lea    edx,[rax-0x1]
  65e31f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e322:	e9 71 f3 ff ff       	jmp    65d698 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1288>
  65e327:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e32a:	8d 50 ff             	lea    edx,[rax-0x1]
  65e32d:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e330:	e9 73 f8 ff ff       	jmp    65dba8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1798>
  65e335:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e338:	8d 50 ff             	lea    edx,[rax-0x1]
  65e33b:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e33e:	e9 cd f1 ff ff       	jmp    65d510 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1100>
  65e343:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e346:	8d 50 ff             	lea    edx,[rax-0x1]
  65e349:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e34c:	e9 97 f7 ff ff       	jmp    65dae8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x16d8>
  65e351:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e354:	8d 50 ff             	lea    edx,[rax-0x1]
  65e357:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e35a:	e9 b9 f4 ff ff       	jmp    65d818 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1408>
  65e35f:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e362:	8d 50 ff             	lea    edx,[rax-0x1]
  65e365:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e368:	e9 fb f8 ff ff       	jmp    65dc68 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1858>
  65e36d:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e370:	8d 50 ff             	lea    edx,[rax-0x1]
  65e373:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e376:	e9 d5 f0 ff ff       	jmp    65d450 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1040>
  65e37b:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e37e:	8d 50 ff             	lea    edx,[rax-0x1]
  65e381:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e384:	e9 cf f6 ff ff       	jmp    65da58 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1648>
  65e389:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e38c:	8d 50 ff             	lea    edx,[rax-0x1]
  65e38f:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e392:	e9 c1 f3 ff ff       	jmp    65d758 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1348>
  65e397:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e39a:	8d 50 ff             	lea    edx,[rax-0x1]
  65e39d:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e3a0:	e9 63 f8 ff ff       	jmp    65dc08 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x17f8>
  65e3a5:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e3a8:	8d 50 ff             	lea    edx,[rax-0x1]
  65e3ab:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e3ae:	e9 25 f2 ff ff       	jmp    65d5d8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x11c8>
  65e3b3:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e3b6:	8d 50 ff             	lea    edx,[rax-0x1]
  65e3b9:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e3bc:	e9 87 f7 ff ff       	jmp    65db48 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x1738>
  65e3c1:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e3c4:	8d 50 ff             	lea    edx,[rax-0x1]
  65e3c7:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e3ca:	e9 09 f5 ff ff       	jmp    65d8d8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x14c8>
  65e3cf:	8b 47 10             	mov    eax,DWORD PTR [rdi+0x10]
  65e3d2:	8d 50 ff             	lea    edx,[rax-0x1]
  65e3d5:	89 57 10             	mov    DWORD PTR [rdi+0x10],edx
  65e3d8:	e9 eb f8 ff ff       	jmp    65dcc8 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()+0x18b8>
  65e3dd:	90                   	nop
  65e3de:	66 90                	xchg   ax,ax

