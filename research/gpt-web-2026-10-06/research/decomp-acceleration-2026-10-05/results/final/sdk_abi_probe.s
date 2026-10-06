	.file	"sdk_abi_probe.cpp"
	.text
	.p2align 4,,15
	.type	_GLOBAL__I__Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E, @function
_GLOBAL__I__Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E:
.LFB10815:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE10815:
	.size	_GLOBAL__I__Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E, .-_GLOBAL__I__Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E
	.text
	.p2align 4,,15
.globl _Z8abi_sizePKN5CEGUI6WindowE
	.type	_Z8abi_sizePKN5CEGUI6WindowE, @function
_Z8abi_sizePKN5CEGUI6WindowE:
.LFB7130:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	call	_ZNK5CEGUI6Window7getSizeEv
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE7130:
	.size	_Z8abi_sizePKN5CEGUI6WindowE, .-_Z8abi_sizePKN5CEGUI6WindowE
	.p2align 4,,15
.globl _Z15abi_orientationPKN4Ogre6CameraE
	.type	_Z15abi_orientationPKN4Ogre6CameraE, @function
_Z15abi_orientationPKN4Ogre6CameraE:
.LFB7129:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	jmp	_ZNK4Ogre6Camera14getOrientationEv
	.cfi_endproc
.LFE7129:
	.size	_Z15abi_orientationPKN4Ogre6CameraE, .-_Z15abi_orientationPKN4Ogre6CameraE
	.p2align 4,,15
.globl _Z10abi_extentPN5CEGUI4FontERKNS_6StringE
	.type	_Z10abi_extentPN5CEGUI4FontERKNS_6StringE, @function
_Z10abi_extentPN5CEGUI4FontERKNS_6StringE:
.LFB7128:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	movss	.LC0(%rip), %xmm0
	jmp	_ZN5CEGUI4Font13getTextExtentERKNS_6StringEf
	.cfi_endproc
.LFE7128:
	.size	_Z10abi_extentPN5CEGUI4FontERKNS_6StringE, .-_Z10abi_extentPN5CEGUI4FontERKNS_6StringE
	.p2align 4,,15
.globl _Z13abi_singletonv
	.type	_Z13abi_singletonv, @function
_Z13abi_singletonv:
.LFB7127:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	jmp	_ZN4Ogre11MeshManager12getSingletonEv
	.cfi_endproc
.LFE7127:
	.size	_Z13abi_singletonv, .-_Z13abi_singletonv
	.p2align 4,,15
.globl _Z10abi_colourRKN5CEGUI6colourE
	.type	_Z10abi_colourRKN5CEGUI6colourE, @function
_Z10abi_colourRKN5CEGUI6colourE:
.LFB7126:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	call	_ZN5CEGUI14PropertyHelper14colourToStringERKNS_6colourE
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE7126:
	.size	_Z10abi_colourRKN5CEGUI6colourE, .-_Z10abi_colourRKN5CEGUI6colourE
	.p2align 4,,15
.globl _Z9abi_widthPKN5CEGUI6WindowE
	.type	_Z9abi_widthPKN5CEGUI6WindowE, @function
_Z9abi_widthPKN5CEGUI6WindowE:
.LFB7125:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	call	_ZNK5CEGUI6Window8getWidthEv
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE7125:
	.size	_Z9abi_widthPKN5CEGUI6WindowE, .-_Z9abi_widthPKN5CEGUI6WindowE
	.p2align 4,,15
.globl _Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E
	.type	_Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E, @function
_Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E:
.LFB7124:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	jmp	_ZN5CEGUI6Window11setPositionERKNS_8UVector2E
	.cfi_endproc
.LFE7124:
	.size	_Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E, .-_Z12abi_positionPN5CEGUI6WindowERKNS_8UVector2E
	.weak	_ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll
	.section	.bss._ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll,"awG",@nobits,_ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll,comdat
	.align 8
	.type	_ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll, @gnu_unique_object
	.size	_ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll, 8
_ZGVZNK4Ogre14OverlayElement9getLightsEvE2ll:
	.zero	8
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1065353216
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
