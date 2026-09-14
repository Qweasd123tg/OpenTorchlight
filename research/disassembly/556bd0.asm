
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

0000000000556bd0 <CGame::frameEnded(Ogre::FrameEvent const&)>:
  556bd0:	mov    %rbx,-0x30(%rsp)
  556bd5:	mov    %rbp,-0x28(%rsp)
  556bda:	mov    %rdi,%rbx
  556bdd:	mov    %r12,-0x20(%rsp)
  556be2:	mov    %r13,-0x18(%rsp)
  556be7:	mov    %rsi,%rbp
  556bea:	mov    %r14,-0x10(%rsp)
  556bef:	mov    %r15,-0x8(%rsp)
  556bf4:	sub    $0x98,%rsp
  556bfb:	mov    0x1d8(%rdi),%rax
  556c02:	test   %rax,%rax
  556c05:	je     556c48 <CGame::frameEnded(Ogre::FrameEvent const&)+0x78>
  556c07:	cmpb   $0x0,0xc0(%rax)
  556c0e:	je     556c48 <CGame::frameEnded(Ogre::FrameEvent const&)+0x78>
  556c10:	mov    $0x1,%eax
  556c15:	mov    0x68(%rsp),%rbx
  556c1a:	mov    0x70(%rsp),%rbp
  556c1f:	mov    0x78(%rsp),%r12
  556c24:	mov    0x80(%rsp),%r13
  556c2c:	mov    0x88(%rsp),%r14
  556c34:	mov    0x90(%rsp),%r15
  556c3c:	add    $0x98,%rsp
  556c43:	ret
  556c44:	nopl   0x0(%rax)
  556c48:	mov    0xb8(%rbx),%rdi
  556c4f:	mov    0xfb47f7(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  556c55:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556c5a:	test   %eax,%eax
  556c5c:	je     556fe0 <CGame::frameEnded(Ogre::FrameEvent const&)+0x410>
  556c62:	mov    0xecf757(%rip),%r12d        # 14263c0 <gLastWidth>
  556c69:	test   %r12d,%r12d
  556c6c:	jne    556cd0 <CGame::frameEnded(Ogre::FrameEvent const&)+0x100>
  556c6e:	mov    0x98(%rbx),%rax
  556c75:	test   %rax,%rax
  556c78:	je     556c10 <CGame::frameEnded(Ogre::FrameEvent const&)+0x40>
  556c7a:	cmpq   $0x0,0xc0(%rbx)
  556c82:	je     556c10 <CGame::frameEnded(Ogre::FrameEvent const&)+0x40>
  556c84:	mov    0x2c0(%rax),%rdx
  556c8b:	movss  0x4(%rbp),%xmm0
  556c90:	mov    %rdx,0x30(%rsp)
  556c95:	mov    0x2c8(%rax),%eax
  556c9b:	mov    %eax,0x38(%rsp)
  556c9f:	mov    0x50(%rbx),%rdi
  556ca3:	mov    (%rdi),%rax
  556ca6:	movss  %xmm0,(%rsp)
  556cab:	call   *0x250(%rax)
  556cb1:	mov    0xc0(%rbx),%rdi
  556cb8:	lea    0x30(%rsp),%rdx
  556cbd:	mov    %rax,%rsi
  556cc0:	movss  (%rsp),%xmm0
  556cc5:	call   a6d270 <CSoundManager::update(Ogre::SceneNode*, Ogre::Vector3 const&, float)>
  556cca:	jmp    556c10 <CGame::frameEnded(Ogre::FrameEvent const&)+0x40>
  556ccf:	nop
  556cd0:	mov    0x98(%rbx),%rax
  556cd7:	cmpb   $0x0,0x103d(%rax)
  556cde:	jne    556c75 <CGame::frameEnded(Ogre::FrameEvent const&)+0xa5>
  556ce0:	mov    0xb8(%rbx),%rdi
  556ce7:	mov    0xfb4777(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  556ced:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556cf2:	cmp    0xecf6c8(%rip),%eax        # 14263c0 <gLastWidth>
  556cf8:	je     557180 <CGame::frameEnded(Ogre::FrameEvent const&)+0x5b0>
  556cfe:	mov    0xb8(%rbx),%rdi
  556d05:	mov    0xfb4759(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  556d0b:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556d10:	mov    0xfb4752(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  556d16:	mov    %eax,0xecf6b0(%rip)        # 14263cc <GResizeWidth>
  556d1c:	mov    0xb8(%rbx),%rdi
  556d23:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556d28:	mov    0xecf69e(%rip),%esi        # 14263cc <GResizeWidth>
  556d2e:	mov    %eax,0xecf69c(%rip)        # 14263d0 <GResizeHeight>
  556d34:	lea    0x5c(%rsp),%rcx
  556d39:	mov    %eax,0x58(%rsp)
  556d3d:	lea    0x58(%rsp),%r8
  556d42:	mov    %eax,%edx
  556d44:	mov    %esi,0x5c(%rsp)
  556d48:	mov    0xb8(%rbx),%rdi
  556d4f:	call   d799e0 <CSettings::findClosestResolution(int, int, int&, int&)>
  556d54:	mov    0x5c(%rsp),%eax
  556d58:	mov    0xfb46ee(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  556d5e:	mov    %eax,0xecf668(%rip)        # 14263cc <GResizeWidth>
  556d64:	mov    0x58(%rsp),%eax
  556d68:	mov    %eax,0xecf662(%rip)        # 14263d0 <GResizeHeight>
  556d6e:	mov    0xb8(%rbx),%rdi
  556d75:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556d7a:	mov    0xecf64c(%rip),%edx        # 14263cc <GResizeWidth>
  556d80:	mov    0xb8(%rbx),%rdi
  556d87:	mov    %edx,0xb0(%rbx)
  556d8d:	mov    0xecf63d(%rip),%eax        # 14263d0 <GResizeHeight>
  556d93:	mov    %eax,0xb4(%rbx)
  556d99:	mov    0xfb46c5(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  556d9f:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  556da4:	mov    0xb4(%rbx),%edx
  556daa:	mov    0xb8(%rbx),%rdi
  556db1:	mov    0xfb46b1(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  556db7:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  556dbc:	mov    0xb8(%rbx),%rdi
  556dc3:	mov    0xfb4683(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  556dc9:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556dce:	test   %eax,%eax
  556dd0:	jne    55710c <CGame::frameEnded(Ogre::FrameEvent const&)+0x53c>
  556dd6:	mov    0x2a0(%rbx),%rdi
  556ddd:	xor    %esi,%esi
  556ddf:	call   554478 <SDL_SetWindowGrab@plt>
  556de4:	mov    0x2a0(%rbx),%rdi
  556deb:	xor    %esi,%esi
  556ded:	call   552a48 <SDL_SetWindowFullscreen@plt>
  556df2:	mov    0xb4(%rbx),%edx
  556df8:	mov    0xb0(%rbx),%esi
  556dfe:	mov    0x2a0(%rbx),%rdi
  556e05:	call   554fd8 <SDL_SetWindowSize@plt>
  556e0a:	mov    0x80(%rbx),%rdi
  556e11:	mov    0xb4(%rbx),%edx
  556e17:	lea    0x50(%rsp),%r13
  556e1c:	mov    0xb0(%rbx),%esi
  556e22:	lea    0x40(%rsp),%r12
  556e27:	mov    (%rdi),%rax
  556e2a:	call   *0x1b0(%rax)
  556e30:	mov    0x80(%rbx),%rdi
  556e37:	mov    (%rdi),%rax
  556e3a:	call   *0x1b8(%rax)
  556e40:	mov    0xb4(%rbx),%eax
  556e46:	mov    %r13,%rdi
  556e49:	cvtsi2ss %rax,%xmm0
  556e4e:	divss  0xa4d9ae(%rip),%xmm0        # fa4804 <vtable for Ogre::FrameListener+0x44>
  556e56:	movss  %xmm0,0x28(%rsp)
  556e5c:	mov    0xb0(%rbx),%eax
  556e62:	cvtsi2ss %rax,%xmm0
  556e67:	mulss  0xa4d999(%rip),%xmm0        # fa4808 <vtable for Ogre::FrameListener+0x48>
  556e6f:	movss  %xmm0,0x2c(%rsp)
  556e75:	movss  0x28(%rsp),%xmm0
  556e7b:	call   c90a30 <STRINGS::GetValueAsString(float)>
  556e80:	mov    %r13,%rdx
  556e83:	mov    $0xf9f7c0,%esi
  556e88:	mov    %r12,%rdi
  556e8b:	call   56aee0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(char const*, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)>
  556e90:	call   554918 <Ogre::LogManager::getSingleton()@plt>
  556e95:	xor    %ecx,%ecx
  556e97:	mov    $0x3,%edx
  556e9c:	mov    %r12,%rsi
  556e9f:	mov    %rax,%rdi
  556ea2:	call   554e68 <Ogre::LogManager::logMessage(std::string const&, Ogre::LogMessageLevel, bool)@plt>
  556ea7:	mov    %r12,%rdi
  556eaa:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  556eaf:	mov    %r13,%rdi
  556eb2:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  556eb7:	mov    0xb8(%rbx),%rdi
  556ebe:	mov    0xfb45a8(%rip),%esi        # 150b46c <KSETTINGS_XRATIO>
  556ec4:	movss  0x2c(%rsp),%xmm0
  556eca:	call   c6e720 <CDynamicPropertyFile::SetFloat(unsigned int, float)>
  556ecf:	mov    0xb8(%rbx),%rdi
  556ed6:	mov    0xfb4594(%rip),%esi        # 150b470 <KSETTINGS_YRATIO>
  556edc:	movss  0x28(%rsp),%xmm0
  556ee2:	call   c6e720 <CDynamicPropertyFile::SetFloat(unsigned int, float)>
  556ee7:	mov    0xb8(%rbx),%rdi
  556eee:	mov    0xfb4618(%rip),%esi        # 150b50c <KSETTINGS_F_SOUNDVOLUME>
  556ef4:	call   c6e410 <CDynamicPropertyFile::GetFloat(unsigned int)>
  556ef9:	mov    0xfb4611(%rip),%esi        # 150b510 <KSETTINGS_F_MUSICVOLUME>
  556eff:	movss  %xmm0,0x2c(%rsp)
  556f05:	mov    0xb8(%rbx),%rdi
  556f0c:	call   c6e410 <CDynamicPropertyFile::GetFloat(unsigned int)>
  556f11:	mov    0xfb45fd(%rip),%esi        # 150b514 <KSETTINGS_SOUNDMUTE>
  556f17:	movss  %xmm0,0x28(%rsp)
  556f1d:	mov    0xb8(%rbx),%rdi
  556f24:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556f29:	mov    0xb8(%rbx),%rdi
  556f30:	mov    0xfb45e2(%rip),%esi        # 150b518 <KSETTINGS_MUSICMUTE>
  556f36:	mov    %eax,%r12d
  556f39:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556f3e:	mov    %eax,%r13d
  556f41:	mov    (%rbx),%rax
  556f44:	mov    %rbx,%rdi
  556f47:	call   *0x30(%rax)
  556f4a:	test   %rax,%rax
  556f4d:	je     556f7d <CGame::frameEnded(Ogre::FrameEvent const&)+0x3ad>
  556f4f:	mov    (%rbx),%rax
  556f52:	mov    %rbx,%rdi
  556f55:	call   *0x30(%rax)
  556f58:	xor    %edx,%edx
  556f5a:	test   %r13d,%r13d
  556f5d:	mov    %rax,%rdi
  556f60:	setne  %dl
  556f63:	xor    %esi,%esi
  556f65:	test   %r12d,%r12d
  556f68:	setne  %sil
  556f6c:	movss  0x28(%rsp),%xmm1
  556f72:	movss  0x2c(%rsp),%xmm0
  556f78:	call   a6b750 <CSoundManager::updateAudioLevels(float, float, bool, bool)>
  556f7d:	mov    0xb8(%rbx),%rdi
  556f84:	mov    0xfb44da(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  556f8a:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556f8f:	mov    0xfb44d3(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  556f95:	mov    %eax,0xecf425(%rip)        # 14263c0 <gLastWidth>
  556f9b:	mov    0xb8(%rbx),%rdi
  556fa2:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556fa7:	mov    0xfb449f(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  556fad:	mov    %eax,0xecf411(%rip)        # 14263c4 <gLastHeight>
  556fb3:	mov    0xb8(%rbx),%rdi
  556fba:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556fbf:	movb   $0x1,0xecf40e(%rip)        # 14263d4 <GRecreateUI>
  556fc6:	mov    %eax,0xecf3fc(%rip)        # 14263c8 <gLastFullscreen>
  556fcc:	mov    0x98(%rbx),%rax
  556fd3:	jmp    556c75 <CGame::frameEnded(Ogre::FrameEvent const&)+0xa5>
  556fd8:	nopl   0x0(%rax,%rax,1)
  556fe0:	mov    0xb8(%rbx),%rdi
  556fe7:	mov    0xfb4477(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  556fed:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  556ff2:	mov    0xecf3c7(%rip),%r12d        # 14263c0 <gLastWidth>
  556ff9:	cmp    %r12d,%eax
  556ffc:	jne    556c69 <CGame::frameEnded(Ogre::FrameEvent const&)+0x99>
  557002:	mov    0xb8(%rbx),%rdi
  557009:	mov    0xfb4459(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  55700f:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  557014:	cmp    0xecf3aa(%rip),%eax        # 14263c4 <gLastHeight>
  55701a:	jne    556c62 <CGame::frameEnded(Ogre::FrameEvent const&)+0x92>
  557020:	mov    0xb8(%rbx),%rdi
  557027:	mov    0xfb441f(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  55702d:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  557032:	cmp    0xecf390(%rip),%eax        # 14263c8 <gLastFullscreen>
  557038:	jne    556c62 <CGame::frameEnded(Ogre::FrameEvent const&)+0x92>
  55703e:	mov    0x2a0(%rbx),%rdi
  557045:	lea    0x5c(%rsp),%rdx
  55704a:	lea    0x58(%rsp),%rsi
  55704f:	call   554e28 <SDL_GetWindowSize@plt>
  557054:	mov    0xb8(%rbx),%rdi
  55705b:	mov    0xfb4403(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  557061:	mov    0x58(%rsp),%r12d
  557066:	mov    0x5c(%rsp),%r13d
  55706b:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  557070:	mov    0xfb43f2(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  557076:	mov    %eax,0x28(%rsp)
  55707a:	movslq %r12d,%r14
  55707d:	mov    0xb8(%rbx),%rdi
  557084:	movslq %r13d,%r15
  557087:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  55708c:	movslq 0x28(%rsp),%rdx
  557091:	cmp    %rdx,%r14
  557094:	je     557169 <CGame::frameEnded(Ogre::FrameEvent const&)+0x599>
  55709a:	nopw   0x0(%rax,%rax,1)
  5570a0:	cmp    $0x1ff,%r14
  5570a7:	jle    556c62 <CGame::frameEnded(Ogre::FrameEvent const&)+0x92>
  5570ad:	cmp    $0x17f,%r15
  5570b4:	jle    556c62 <CGame::frameEnded(Ogre::FrameEvent const&)+0x92>
  5570ba:	mov    0xb8(%rbx),%rdi
  5570c1:	mov    0xfb439d(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  5570c7:	mov    %r12d,%edx
  5570ca:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  5570cf:	mov    0xb8(%rbx),%rdi
  5570d6:	mov    0xfb438c(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  5570dc:	mov    %r13d,%edx
  5570df:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  5570e4:	mov    %r12d,0xecf2d5(%rip)        # 14263c0 <gLastWidth>
  5570eb:	mov    %r13d,0xecf2d2(%rip)        # 14263c4 <gLastHeight>
  5570f2:	mov    %r12d,0xecf2d3(%rip)        # 14263cc <GResizeWidth>
  5570f9:	mov    %r13d,0xecf2d0(%rip)        # 14263d0 <GResizeHeight>
  557100:	movb   $0x1,0xecf2cd(%rip)        # 14263d4 <GRecreateUI>
  557107:	jmp    556c69 <CGame::frameEnded(Ogre::FrameEvent const&)+0x99>
  55710c:	mov    0x2a0(%rbx),%rdi
  557113:	xor    %esi,%esi
  557115:	call   552a48 <SDL_SetWindowFullscreen@plt>
  55711a:	mov    0x2a0(%rbx),%rdi
  557121:	xor    %edx,%edx
  557123:	xor    %esi,%esi
  557125:	call   553cf8 <SDL_SetWindowPosition@plt>
  55712a:	mov    0xb4(%rbx),%edx
  557130:	mov    0xb0(%rbx),%esi
  557136:	mov    0x2a0(%rbx),%rdi
  55713d:	call   554fd8 <SDL_SetWindowSize@plt>
  557142:	mov    0x2a0(%rbx),%rdi
  557149:	mov    $0x1,%esi
  55714e:	call   552a48 <SDL_SetWindowFullscreen@plt>
  557153:	mov    0x2a0(%rbx),%rdi
  55715a:	mov    $0x1,%esi
  55715f:	call   554478 <SDL_SetWindowGrab@plt>
  557164:	jmp    556e0a <CGame::frameEnded(Ogre::FrameEvent const&)+0x23a>
  557169:	cltq
  55716b:	cmp    %rax,%r15
  55716e:	jne    5570a0 <CGame::frameEnded(Ogre::FrameEvent const&)+0x4d0>
  557174:	jmp    556c62 <CGame::frameEnded(Ogre::FrameEvent const&)+0x92>
  557179:	nopl   0x0(%rax)
  557180:	mov    0xb8(%rbx),%rdi
  557187:	mov    0xfb42db(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  55718d:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  557192:	cmp    0xecf22c(%rip),%eax        # 14263c4 <gLastHeight>
  557198:	jne    556cfe <CGame::frameEnded(Ogre::FrameEvent const&)+0x12e>
  55719e:	mov    0xb8(%rbx),%rdi
  5571a5:	mov    0xfb42a1(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  5571ab:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  5571b0:	cmp    0xecf212(%rip),%eax        # 14263c8 <gLastFullscreen>
  5571b6:	jne    556cfe <CGame::frameEnded(Ogre::FrameEvent const&)+0x12e>
  5571bc:	cmpb   $0x0,0xecf211(%rip)        # 14263d4 <GRecreateUI>
  5571c3:	je     556c6e <CGame::frameEnded(Ogre::FrameEvent const&)+0x9e>
  5571c9:	cmpq   $0x0,0x98(%rbx)
  5571d1:	je     556c10 <CGame::frameEnded(Ogre::FrameEvent const&)+0x40>
  5571d7:	mov    0xecf1ef(%rip),%eax        # 14263cc <GResizeWidth>
  5571dd:	mov    0xb8(%rbx),%rdi
  5571e4:	mov    %eax,0xb0(%rbx)
  5571ea:	mov    0xecf1e0(%rip),%eax        # 14263d0 <GResizeHeight>
  5571f0:	mov    %eax,0xb4(%rbx)
  5571f6:	mov    0xfb4250(%rip),%esi        # 150b44c <KSETTINGS_FULLSCREEN>
  5571fc:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  557201:	test   %eax,%eax
  557203:	je     557432 <CGame::frameEnded(Ogre::FrameEvent const&)+0x862>
  557209:	mov    0xb0(%rbx),%edx
  55720f:	mov    0xb8(%rbx),%rdi
  557216:	mov    0xfb4248(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  55721c:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  557221:	mov    0xb8(%rbx),%rdi
  557228:	mov    0xb4(%rbx),%edx
  55722e:	mov    0xfb4234(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  557234:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  557239:	mov    0x98(%rbx),%rdi
  557240:	test   %rdi,%rdi
  557243:	je     55725d <CGame::frameEnded(Ogre::FrameEvent const&)+0x68d>
  557245:	mov    0xb4(%rbx),%ecx
  55724b:	mov    0xb0(%rbx),%edx
  557251:	mov    0xa0(%rbx),%rsi
  557258:	call   56e140 <CGameClient::updateScreenInfo(void*, int, int)>
  55725d:	mov    0x38(%rbx),%r12
  557261:	test   %r12,%r12
  557264:	je     5572ca <CGame::frameEnded(Ogre::FrameEvent const&)+0x6fa>
  557266:	mov    0xb4(%rbx),%eax
  55726c:	xor    %esi,%esi
  55726e:	mov    %r12,%rdi
  557271:	cvtsi2ss %rax,%xmm0
  557276:	movss  %xmm0,0x2c(%rsp)
  55727c:	mov    0xb0(%rbx),%eax
  557282:	movss  0x2c(%rsp),%xmm1
  557288:	cvtsi2ss %rax,%xmm0
  55728d:	movss  %xmm0,0x28(%rsp)
  557293:	call   ce9ef0 <CCameraControl::setAspectRatio(ECAMERAS, float, float)>
  557298:	movss  0x2c(%rsp),%xmm1
  55729e:	mov    $0x1,%esi
  5572a3:	movss  0x28(%rsp),%xmm0
  5572a9:	mov    %r12,%rdi
  5572ac:	call   ce9ef0 <CCameraControl::setAspectRatio(ECAMERAS, float, float)>
  5572b1:	movss  0x2c(%rsp),%xmm1
  5572b7:	mov    $0x2,%esi
  5572bc:	movss  0x28(%rsp),%xmm0
  5572c2:	mov    %r12,%rdi
  5572c5:	call   ce9ef0 <CCameraControl::setAspectRatio(ECAMERAS, float, float)>
  5572ca:	mov    0xb4(%rbx),%eax
  5572d0:	mov    0xb8(%rbx),%rdi
  5572d7:	mov    0xfb418f(%rip),%esi        # 150b46c <KSETTINGS_XRATIO>
  5572dd:	cvtsi2ss %rax,%xmm1
  5572e2:	mov    0xb0(%rbx),%eax
  5572e8:	cvtsi2ss %rax,%xmm0
  5572ed:	divss  0xa4d50f(%rip),%xmm1        # fa4804 <vtable for Ogre::FrameListener+0x44>
  5572f5:	mulss  0xa4d50b(%rip),%xmm0        # fa4808 <vtable for Ogre::FrameListener+0x48>
  5572fd:	movss  %xmm1,0x10(%rsp)
  557303:	call   c6e720 <CDynamicPropertyFile::SetFloat(unsigned int, float)>
  557308:	movss  0x10(%rsp),%xmm1
  55730e:	mov    0xb8(%rbx),%rdi
  557315:	mov    0xfb4155(%rip),%esi        # 150b470 <KSETTINGS_YRATIO>
  55731b:	movaps %xmm1,%xmm0
  55731e:	call   c6e720 <CDynamicPropertyFile::SetFloat(unsigned int, float)>
  557323:	mov    0x98(%rbx),%rax
  55732a:	test   %rax,%rax
  55732d:	je     557342 <CGame::frameEnded(Ogre::FrameEvent const&)+0x772>
  55732f:	mov    0x78(%rax),%rdi
  557333:	test   %rdi,%rdi
  557336:	je     557342 <CGame::frameEnded(Ogre::FrameEvent const&)+0x772>
  557338:	mov    $0x1,%esi
  55733d:	call   a9c3b0 <CGameUI::setLoadingVisible(bool)>
  557342:	movb   $0x0,0xecf08b(%rip)        # 14263d4 <GRecreateUI>
  557349:	mov    0x98(%rbx),%rdi
  557350:	call   5791c0 <CGameClient::rescaleUI()>
  557355:	mov    0xb4(%rbx),%r13d
  55735c:	mov    0xb0(%rbx),%r12d
  557363:	call   a828e0 <CGameUI::getSingleton()>
  557368:	test   %rax,%rax
  55736b:	je     5573ce <CGame::frameEnded(Ogre::FrameEvent const&)+0x7fe>
  55736d:	lea    0x5c(%rsp),%rcx
  557372:	lea    0x58(%rsp),%r8
  557377:	mov    %r13d,%edx
  55737a:	mov    %r12d,%esi
  55737d:	mov    $0x1424b60,%edi
  557382:	call   eaa020 <CSplash::findCenterForWindow(int, int, int&, int&)>
  557387:	cvtsi2ssl 0x58(%rsp),%xmm1
  55738d:	cvtsi2ssl 0x5c(%rsp),%xmm0
  557393:	movss  %xmm1,0x10(%rsp)
  557399:	movss  %xmm0,(%rsp)
  55739e:	call   555678 <CEGUI::System::getSingleton()@plt>
  5573a3:	movss  0x10(%rsp),%xmm1
  5573a9:	mov    %rax,%rdi
  5573ac:	movss  (%rsp),%xmm0
  5573b1:	call   554108 <CEGUI::System::injectMousePosition(float, float)@plt>
  5573b6:	call   555678 <CEGUI::System::getSingleton()@plt>
  5573bb:	xorps  %xmm1,%xmm1
  5573be:	mov    %rax,%rdi
  5573c1:	movss  0xa4d433(%rip),%xmm0        # fa47fc <vtable for Ogre::FrameListener+0x3c>
  5573c9:	call   552838 <CEGUI::System::injectMouseMove(float, float)@plt>
  5573ce:	call   a54490 <CMasterResourceManager::getSingleton()>
  5573d3:	movb   $0x0,0xc0(%rax)
  5573da:	mov    0xeceff8(%rip),%edx        # 14263d8 <gFailWidth>
  5573e0:	test   %edx,%edx
  5573e2:	je     556c6e <CGame::frameEnded(Ogre::FrameEvent const&)+0x9e>
  5573e8:	mov    0xb8(%rbx),%rdi
  5573ef:	mov    0xfb406f(%rip),%esi        # 150b464 <KSETTINGS_RES_WIDTH>
  5573f5:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  5573fa:	mov    0xb8(%rbx),%rdi
  557401:	mov    0xecefd5(%rip),%edx        # 14263dc <gFailHeight>
  557407:	mov    0xfb405b(%rip),%esi        # 150b468 <KSETTINGS_RES_HEIGHT>
  55740d:	call   c6e650 <CDynamicPropertyFile::SetInt(unsigned int, int)>
  557412:	movl   $0x0,0xecefbc(%rip)        # 14263d8 <gFailWidth>
  55741c:	movl   $0x0,0xecefb6(%rip)        # 14263dc <gFailHeight>
  557426:	movb   $0x1,0xecefb3(%rip)        # 14263e0 <GResizing>
  55742d:	jmp    556c6e <CGame::frameEnded(Ogre::FrameEvent const&)+0x9e>
  557432:	mov    0x2a0(%rbx),%rdi
  557439:	lea    0x5c(%rsp),%rdx
  55743e:	lea    0x58(%rsp),%rsi
  557443:	call   554e28 <SDL_GetWindowSize@plt>
  557448:	mov    0x58(%rsp),%edx
  55744c:	mov    %edx,0xb0(%rbx)
  557452:	mov    0x5c(%rsp),%eax
  557456:	mov    %eax,0xb4(%rbx)
  55745c:	jmp    55720f <CGame::frameEnded(Ogre::FrameEvent const&)+0x63f>
  557461:	mov    %rax,%rbx
  557464:	mov    %r13,%rdi
  557467:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  55746c:	mov    %rbx,%rdi
  55746f:	call   554498 <_Unwind_Resume@plt>
  557474:	mov    %r12,%rdi
  557477:	mov    %rax,%rbx
  55747a:	call   556288 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
  55747f:	jmp    557464 <CGame::frameEnded(Ogre::FrameEvent const&)+0x894>
