
/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64:     file format elf64-x86-64


Disassembly of section .text:

000000000057a9f0 <CGameClient::clickLeft()>:
  57a9f0:	mov    %rbx,-0x20(%rsp)
  57a9f5:	mov    %rbp,-0x18(%rsp)
  57a9fa:	mov    %rdi,%rbx
  57a9fd:	mov    %r12,-0x10(%rsp)
  57aa02:	mov    %r13,-0x8(%rsp)
  57aa07:	sub    $0x78,%rsp
  57aa0b:	call   56e570 <CGameClient::getIsPaused()>
  57aa10:	test   %al,%al
  57aa12:	je     57aa30 <CGameClient::clickLeft()+0x40>
  57aa14:	mov    0x58(%rsp),%rbx
  57aa19:	mov    0x60(%rsp),%rbp
  57aa1e:	mov    0x68(%rsp),%r12
  57aa23:	mov    0x70(%rsp),%r13
  57aa28:	add    $0x78,%rsp
  57aa2c:	ret
  57aa2d:	nopl   (%rax)
  57aa30:	mov    0x58(%rbx),%rdi
  57aa34:	call   80e850 <CCharacter::alive()>
  57aa39:	test   %al,%al
  57aa3b:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57aa3d:	mov    0x58(%rbx),%rdi
  57aa41:	mov    (%rdi),%rax
  57aa44:	call   *0x48(%rax)
  57aa47:	test   %al,%al
  57aa49:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57aa4b:	mov    0x58(%rbx),%rax
  57aa4f:	mov    0x330(%rax),%edx
  57aa55:	cmp    $0x22,%edx
  57aa58:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57aa5a:	cmp    $0x14,%edx
  57aa5d:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57aa5f:	cmpb   $0x0,0x99(%rbx)
  57aa66:	jne    57aa72 <CGameClient::clickLeft()+0x82>
  57aa68:	movl   $0x41200000,0x278(%rax)
  57aa72:	cmpq   $0x0,0x1d8(%rbx)
  57aa7a:	je     57aaad <CGameClient::clickLeft()+0xbd>
  57aa7c:	mov    0x1c8(%rbx),%rdi
  57aa83:	test   %rdi,%rdi
  57aa86:	je     57aaad <CGameClient::clickLeft()+0xbd>
  57aa88:	call   80e850 <CCharacter::alive()>
  57aa8d:	test   %al,%al
  57aa8f:	jne    57aaad <CGameClient::clickLeft()+0xbd>
  57aa91:	mov    0x1d8(%rbx),%rsi
  57aa98:	cmp    0x1c8(%rbx),%rsi
  57aa9f:	je     57aaad <CGameClient::clickLeft()+0xbd>
  57aaa1:	lea    0x1c8(%rbx),%rdi
  57aaa8:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57aaad:	mov    0x1e8(%rbx),%rsi
  57aab4:	test   %rsi,%rsi
  57aab7:	je     57aac7 <CGameClient::clickLeft()+0xd7>
  57aab9:	cmpq   $0x0,0x1f8(%rbx)
  57aac1:	je     57ada0 <CGameClient::clickLeft()+0x3b0>
  57aac7:	mov    0x1d8(%rbx),%rsi
  57aace:	test   %rsi,%rsi
  57aad1:	je     57aae1 <CGameClient::clickLeft()+0xf1>
  57aad3:	cmpq   $0x0,0x1c8(%rbx)
  57aadb:	je     57add0 <CGameClient::clickLeft()+0x3e0>
  57aae1:	mov    0x58(%rbx),%rax
  57aae5:	cmpb   $0x0,0x4d0(%rax)
  57aaec:	mov    %rax,%rdi
  57aaef:	je     57ac00 <CGameClient::clickLeft()+0x210>
  57aaf5:	cmpb   $0x0,0x266(%rax)
  57aafc:	jne    57ab05 <CGameClient::clickLeft()+0x115>
  57aafe:	movb   $0x1,0x98(%rbx)
  57ab05:	movb   $0x0,0x4d0(%rax)
  57ab0c:	mov    0x58(%rbx),%rax
  57ab10:	movb   $0x0,0x4d1(%rax)
  57ab17:	mov    0x58(%rbx),%rdi
  57ab1b:	call   80e9b0 <CCharacter::performingSkillLoose()>
  57ab20:	test   %al,%al
  57ab22:	jne    57aa14 <CGameClient::clickLeft()+0x24>
  57ab28:	mov    0x58(%rbx),%rdi
  57ab2c:	mov    0x350(%rdi),%rbp
  57ab33:	mov    0x340(%rdi),%r12
  57ab3a:	call   80e9b0 <CCharacter::performingSkillLoose()>
  57ab3f:	test   %al,%al
  57ab41:	je     57ae00 <CGameClient::clickLeft()+0x410>
  57ab47:	mov    0x1c8(%rbx),%rdi
  57ab4e:	test   %rdi,%rdi
  57ab51:	je     57ab6e <CGameClient::clickLeft()+0x17e>
  57ab53:	cmpb   $0x0,0x81(%rdi)
  57ab5a:	jne    57af2d <CGameClient::clickLeft()+0x53d>
  57ab60:	lea    0x1c8(%rbx),%rdi
  57ab67:	xor    %esi,%esi
  57ab69:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57ab6e:	mov    0x1f8(%rbx),%rdi
  57ab75:	test   %rdi,%rdi
  57ab78:	je     57ac18 <CGameClient::clickLeft()+0x228>
  57ab7e:	mov    $0x1d,%esi
  57ab83:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  57ab88:	test   %al,%al
  57ab8a:	je     57ac18 <CGameClient::clickLeft()+0x228>
  57ab90:	mov    0x58(%rbx),%rdi
  57ab94:	call   80e910 <CCharacter::performingAttackLoose()>
  57ab99:	test   %al,%al
  57ab9b:	je     57af45 <CGameClient::clickLeft()+0x555>
  57aba1:	mov    0x58(%rbx),%rdi
  57aba5:	call   80e910 <CCharacter::performingAttackLoose()>
  57abaa:	test   %al,%al
  57abac:	jne    57aa14 <CGameClient::clickLeft()+0x24>
  57abb2:	mov    0x58(%rbx),%rdi
  57abb6:	cmpl   $0x3,0x330(%rdi)
  57abbd:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57abc3:	call   80e930 <CCharacter::performingSkill()>
  57abc8:	test   %al,%al
  57abca:	jne    57aa14 <CGameClient::clickLeft()+0x24>
  57abd0:	mov    0x58(%rbx),%rdi
  57abd4:	call   80e8b0 <CCharacter::stopPathing()>
  57abd9:	mov    0x58(%rbx),%rdi
  57abdd:	mov    0x58(%rsp),%rbx
  57abe2:	mov    0x60(%rsp),%rbp
  57abe7:	mov    0x68(%rsp),%r12
  57abec:	mov    0x70(%rsp),%r13
  57abf1:	add    $0x78,%rsp
  57abf5:	jmp    82b550 <CCharacter::attack()>
  57abfa:	nopw   0x0(%rax,%rax,1)
  57ac00:	cmpb   $0x0,0x4d1(%rax)
  57ac07:	je     57ab1b <CGameClient::clickLeft()+0x12b>
  57ac0d:	jmp    57aaf5 <CGameClient::clickLeft()+0x105>
  57ac12:	nopw   0x0(%rax,%rax,1)
  57ac18:	mov    0x1c8(%rbx),%rsi
  57ac1f:	test   %rsi,%rsi
  57ac22:	je     57ace0 <CGameClient::clickLeft()+0x2f0>
  57ac28:	mov    0x58(%rbx),%rdi
  57ac2c:	call   810200 <CCharacter::isEnemy(CCharacter*)>
  57ac31:	test   %al,%al
  57ac33:	je     57ae44 <CGameClient::clickLeft()+0x454>
  57ac39:	mov    0x58(%rbx),%rdi
  57ac3d:	call   80e910 <CCharacter::performingAttackLoose()>
  57ac42:	test   %al,%al
  57ac44:	jne    57aba1 <CGameClient::clickLeft()+0x1b1>
  57ac4a:	mov    0x58(%rbx),%rdi
  57ac4e:	xor    %esi,%esi
  57ac50:	call   826140 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)>
  57ac55:	test   %al,%al
  57ac57:	jne    57aba1 <CGameClient::clickLeft()+0x1b1>
  57ac5d:	cmp    0x1c8(%rbx),%r12
  57ac64:	je     57ac76 <CGameClient::clickLeft()+0x286>
  57ac66:	mov    0x58(%rbx),%rdi
  57ac6a:	call   80e8b0 <CCharacter::stopPathing()>
  57ac6f:	mov    0x1c8(%rbx),%r12
  57ac76:	mov    0x58(%rbx),%rdi
  57ac7a:	mov    %r12,%rsi
  57ac7d:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57ac82:	mov    0x58(%rbx),%rdi
  57ac86:	mov    $0x4,%esi
  57ac8b:	mov    (%rdi),%rax
  57ac8e:	call   *0x348(%rax)
  57ac94:	mov    0x58(%rbx),%rdi
  57ac98:	mov    0x70(%rbx),%rsi
  57ac9c:	xorps  %xmm0,%xmm0
  57ac9f:	mov    (%rdi),%rax
  57aca2:	call   *0x3b8(%rax)
  57aca8:	mov    0x58(%rbx),%rdi
  57acac:	cmpl   $0x3,0x330(%rdi)
  57acb3:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57acb9:	call   80e930 <CCharacter::performingSkill()>
  57acbe:	test   %al,%al
  57acc0:	jne    57aa14 <CGameClient::clickLeft()+0x24>
  57acc6:	mov    0x58(%rbx),%rdi
  57acca:	cmpb   $0x0,0x264(%rdi)
  57acd1:	jne    57aa14 <CGameClient::clickLeft()+0x24>
  57acd7:	jmp    57abdd <CGameClient::clickLeft()+0x1ed>
  57acdc:	nopl   0x0(%rax)
  57ace0:	mov    0x1f8(%rbx),%rdi
  57ace7:	test   %rdi,%rdi
  57acea:	je     57af82 <CGameClient::clickLeft()+0x592>
  57acf0:	cmpb   $0x0,0x198(%rdi)
  57acf7:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57acfd:	mov    (%rdi),%rax
  57ad00:	call   *0x48(%rax)
  57ad03:	test   %al,%al
  57ad05:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57ad0b:	mov    0x50(%rbx),%rdi
  57ad0f:	mov    0xf9090b(%rip),%esi        # 150b620 <KSETTINGS_KEYMAP_HOLDPOS>
  57ad15:	mov    0x58(%rbx),%r12
  57ad19:	call   c6e440 <CDynamicPropertyFile::GetInt(unsigned int)>
  57ad1e:	lea    0x2d0(%rbx),%rdi
  57ad25:	mov    %eax,%esi
  57ad27:	call   91a680 <CKeyManager::keyHeld(unsigned int)>
  57ad2c:	test   %al,%al
  57ad2e:	jne    57afc9 <CGameClient::clickLeft()+0x5d9>
  57ad34:	cmp    0x350(%r12),%rbp
  57ad3c:	je     57ad46 <CGameClient::clickLeft()+0x356>
  57ad3e:	mov    %r12,%rdi
  57ad41:	call   80e8b0 <CCharacter::stopPathing()>
  57ad46:	mov    0x1f8(%rbx),%rsi
  57ad4d:	mov    %r12,%rdi
  57ad50:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57ad55:	mov    (%r12),%rax
  57ad59:	mov    $0x7,%esi
  57ad5e:	mov    %r12,%rdi
  57ad61:	call   *0x348(%rax)
  57ad67:	mov    %r12,%rdi
  57ad6a:	call   80e8b0 <CCharacter::stopPathing()>
  57ad6f:	mov    (%r12),%rax
  57ad73:	mov    0x70(%rbx),%rsi
  57ad77:	mov    %r12,%rdi
  57ad7a:	mov    0x58(%rsp),%rbx
  57ad7f:	mov    0x60(%rsp),%rbp
  57ad84:	mov    0x68(%rsp),%r12
  57ad89:	mov    0x70(%rsp),%r13
  57ad8e:	mov    0x3c8(%rax),%rax
  57ad95:	xorps  %xmm0,%xmm0
  57ad98:	add    $0x78,%rsp
  57ad9c:	jmp    *%rax
  57ad9e:	xchg   %ax,%ax
  57ada0:	cmpq   $0x0,0x1c8(%rbx)
  57ada8:	jne    57aac7 <CGameClient::clickLeft()+0xd7>
  57adae:	cmpb   $0x0,0x99(%rbx)
  57adb5:	jne    57aac7 <CGameClient::clickLeft()+0xd7>
  57adbb:	lea    0x1f8(%rbx),%rdi
  57adc2:	call   591b80 <TSafePointer<CItem>::setObject(CItem*)>
  57adc7:	jmp    57aac7 <CGameClient::clickLeft()+0xd7>
  57adcc:	nopl   0x0(%rax)
  57add0:	cmpq   $0x0,0x1f8(%rbx)
  57add8:	jne    57aae1 <CGameClient::clickLeft()+0xf1>
  57adde:	cmpb   $0x0,0x99(%rbx)
  57ade5:	jne    57aae1 <CGameClient::clickLeft()+0xf1>
  57adeb:	lea    0x1c8(%rbx),%rdi
  57adf2:	call   591af0 <TSafePointer<CCharacter>::setObject(CCharacter*)>
  57adf7:	jmp    57aae1 <CGameClient::clickLeft()+0xf1>
  57adfc:	nopl   0x0(%rax)
  57ae00:	mov    0x58(%rbx),%rdi
  57ae04:	call   80e910 <CCharacter::performingAttackLoose()>
  57ae09:	test   %al,%al
  57ae0b:	jne    57ab47 <CGameClient::clickLeft()+0x157>
  57ae11:	mov    0x1f8(%rbx),%rsi
  57ae18:	test   %rsi,%rsi
  57ae1b:	je     57ae26 <CGameClient::clickLeft()+0x436>
  57ae1d:	mov    0x58(%rbx),%rdi
  57ae21:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57ae26:	mov    0x1c8(%rbx),%rsi
  57ae2d:	test   %rsi,%rsi
  57ae30:	je     57ab6e <CGameClient::clickLeft()+0x17e>
  57ae36:	mov    0x58(%rbx),%rdi
  57ae3a:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57ae3f:	jmp    57ab47 <CGameClient::clickLeft()+0x157>
  57ae44:	mov    0x1c8(%rbx),%rdi
  57ae4b:	test   %rdi,%rdi
  57ae4e:	je     57ace0 <CGameClient::clickLeft()+0x2f0>
  57ae54:	mov    $0x83,%esi
  57ae59:	call   7f62a0 <CBaseUnit::ISA(UNITTYPES::EUNITTYPES)>
  57ae5e:	test   %al,%al
  57ae60:	je     57ace0 <CGameClient::clickLeft()+0x2f0>
  57ae66:	mov    0x1c8(%rbx),%rsi
  57ae6d:	mov    0x58(%rbx),%rdi
  57ae71:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57ae76:	mov    0x58(%rbx),%rdi
  57ae7a:	mov    $0x9,%esi
  57ae7f:	mov    (%rdi),%rax
  57ae82:	call   *0x348(%rax)
  57ae88:	mov    0x1c8(%rbx),%rdi
  57ae8f:	mov    $0x1,%esi
  57ae94:	call   9e7080 <CPositionableObject::getPosition(bool)>
  57ae99:	movq   %xmm0,0x8(%rsp)
  57ae9f:	mov    0x8(%rsp),%rax
  57aea4:	mov    0x1c8(%rbx),%rdi
  57aeab:	movss  %xmm1,0x28(%rsp)
  57aeb1:	mov    $0x1,%esi
  57aeb6:	mov    %rax,0x20(%rsp)
  57aebb:	mov    %rax,0x30(%rsp)
  57aec0:	mov    0x28(%rsp),%eax
  57aec4:	mov    %eax,0x38(%rsp)
  57aec8:	movss  0x38(%rsp),%xmm0
  57aece:	movss  %xmm0,0x1c(%rsp)
  57aed4:	call   9e7080 <CPositionableObject::getPosition(bool)>
  57aed9:	movq   %xmm0,0x8(%rsp)
  57aedf:	mov    0x8(%rsp),%rax
  57aee4:	movss  %xmm1,0x28(%rsp)
  57aeea:	mov    0x70(%rbx),%rsi
  57aeee:	mov    0x58(%rbx),%rdi
  57aef2:	movss  0x1c(%rsp),%xmm1
  57aef8:	mov    %rax,0x40(%rsp)
  57aefd:	mov    %rax,0x20(%rsp)
  57af02:	mov    0x28(%rsp),%eax
  57af06:	movss  0x40(%rsp),%xmm0
  57af0c:	mov    0x58(%rsp),%rbx
  57af11:	mov    0x60(%rsp),%rbp
  57af16:	mov    0x68(%rsp),%r12
  57af1b:	mov    %eax,0x48(%rsp)
  57af1f:	mov    0x70(%rsp),%r13
  57af24:	add    $0x78,%rsp
  57af28:	jmp    82ac30 <CCharacter::setDestination(CLevel&, float, float)>
  57af2d:	mov    (%rdi),%rax
  57af30:	call   *0x48(%rax)
  57af33:	test   %al,%al
  57af35:	jne    57ab6e <CGameClient::clickLeft()+0x17e>
  57af3b:	nopl   0x0(%rax,%rax,1)
  57af40:	jmp    57ab60 <CGameClient::clickLeft()+0x170>
  57af45:	mov    0x58(%rbx),%rdi
  57af49:	xor    %esi,%esi
  57af4b:	call   826140 <CCharacter::inAttackRange(EATTACK_RANGE_TYPE)>
  57af50:	test   %al,%al
  57af52:	jne    57aba1 <CGameClient::clickLeft()+0x1b1>
  57af58:	cmp    0x1f8(%rbx),%rbp
  57af5f:	je     57af71 <CGameClient::clickLeft()+0x581>
  57af61:	mov    0x58(%rbx),%rdi
  57af65:	call   80e8b0 <CCharacter::stopPathing()>
  57af6a:	mov    0x1f8(%rbx),%rbp
  57af71:	mov    0x58(%rbx),%rdi
  57af75:	mov    %rbp,%rsi
  57af78:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57af7d:	jmp    57ac82 <CGameClient::clickLeft()+0x292>
  57af82:	cmpb   $0x0,0x99(%rbx)
  57af89:	je     57b073 <CGameClient::clickLeft()+0x683>
  57af8f:	cmpb   $0x0,0x98(%rbx)
  57af96:	jne    57b05d <CGameClient::clickLeft()+0x66d>
  57af9c:	movzbl 0x99(%rbx),%eax
  57afa3:	mov    %rbx,%rdi
  57afa6:	mov    0x60(%rsp),%rbp
  57afab:	mov    0x58(%rsp),%rbx
  57afb0:	mov    0x68(%rsp),%r12
  57afb5:	mov    0x70(%rsp),%r13
  57afba:	add    $0x78,%rsp
  57afbe:	xor    $0x1,%eax
  57afc1:	movzbl %al,%esi
  57afc4:	jmp    57a900 <CGameClient::moveToMouse(bool)>
  57afc9:	mov    0x58(%rbx),%rax
  57afcd:	mov    0x648(%rax),%rdx
  57afd4:	mov    0x650(%rax),%rax
  57afdb:	sub    %rdx,%rax
  57afde:	sar    $0x3,%rax
  57afe2:	test   %rax,%rax
  57afe5:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57afeb:	mov    (%rdx),%r13
  57afee:	test   %r13,%r13
  57aff1:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57aff7:	mov    %r13,%rdi
  57affa:	call   814440 <CCharacter::isPetNearDeath()>
  57afff:	test   %al,%al
  57b001:	jne    57ad34 <CGameClient::clickLeft()+0x344>
  57b007:	mov    %r13,%rdi
  57b00a:	call   80e850 <CCharacter::alive()>
  57b00f:	test   %al,%al
  57b011:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57b017:	mov    0x330(%r13),%eax
  57b01e:	cmp    $0x2a,%eax
  57b021:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57b027:	cmp    $0x29,%eax
  57b02a:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57b030:	mov    0x58(%rbx),%rax
  57b034:	xor    %r12d,%r12d
  57b037:	mov    0x648(%rax),%rdx
  57b03e:	mov    0x650(%rax),%rax
  57b045:	sub    %rdx,%rax
  57b048:	sar    $0x3,%rax
  57b04c:	test   %rax,%rax
  57b04f:	je     57ad34 <CGameClient::clickLeft()+0x344>
  57b055:	mov    (%rdx),%r12
  57b058:	jmp    57ad34 <CGameClient::clickLeft()+0x344>
  57b05d:	mov    0x58(%rbx),%rax
  57b061:	cmpb   $0x0,0x266(%rax)
  57b068:	je     57aa14 <CGameClient::clickLeft()+0x24>
  57b06e:	jmp    57af9c <CGameClient::clickLeft()+0x5ac>
  57b073:	mov    0x58(%rbx),%rdi
  57b077:	xor    %esi,%esi
  57b079:	movb   $0x0,0x98(%rbx)
  57b080:	call   825310 <CCharacter::setTarget(CCharacter*)>
  57b085:	mov    0x58(%rbx),%rdi
  57b089:	xor    %esi,%esi
  57b08b:	call   824920 <CCharacter::setTargetItem(CItem*)>
  57b090:	mov    0x58(%rbx),%rdi
  57b094:	xor    %esi,%esi
  57b096:	mov    (%rdi),%rax
  57b099:	call   *0x348(%rax)
  57b09f:	jmp    57af8f <CGameClient::clickLeft()+0x59f>
