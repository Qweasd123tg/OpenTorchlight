/* Targeted Ghidra class export.
   namespace=CSoundManager
   Treat pseudocode as navigation evidence. */


/* address=00a6ae80
   symbol=CSoundManager::fmodFileReadCallback */

/* CSoundManager::fmodFileReadCallback(void*, void*, unsigned int, unsigned int*, void*) */

byte CSoundManager::fmodFileReadCallback
               (void *param_1,void *param_2,uint param_3,uint *param_4,void *param_5)

{
  uint uVar1;

  uVar1 = (**(code **)(**(long **)((long)param_1 + 0x20) + 0x10))
                    (*(long **)((long)param_1 + 0x20),param_2,param_3);
  *param_4 = uVar1;
  return -(uVar1 == 0) & 0x16;
}

/* address=00a6aea0
   symbol=CSoundManager::fmodFileSeekCallback */

/* CSoundManager::fmodFileSeekCallback(void*, unsigned int, void*) */

undefined8 CSoundManager::fmodFileSeekCallback(void *param_1,uint param_2,void *param_3)

{
  long *plVar1;

  if ((param_1 != (void *)0x0) && (plVar1 = *(long **)((long)param_1 + 0x20), plVar1 != (long *)0x0)
     ) {
    (**(code **)(*plVar1 + 0x40))(plVar1,param_2);
    return 0;
  }
  return 0x14;
}

/* address=00a6aee0
   symbol=CSoundManager::releaseSound */

/* CSoundManager::releaseSound(CSoundInstance*) */

void __thiscall CSoundManager::releaseSound(CSoundManager *this,CSoundInstance *param_1)

{
  int iVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  uint uVar5;
  long lVar6;

  if (((param_1 == (CSoundInstance *)0x0) ||
      (iVar1 = *(int *)(param_1 + 0x48), *(int *)(param_1 + 0x48) = iVar1 + -1, iVar1 + -1 != 0)) ||
     (*(long *)(param_1 + 0x20) == 0)) {
    return;
  }
  uVar2 = *(uint *)(this + 0x98);
  if (uVar2 == 0) {
LAB_00a6af35:
                    /* WARNING: Could not recover jumptable at 0x00a6af3f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)param_1 + 8))(param_1);
    return;
  }
  plVar3 = *(long **)(this + 0x90);
  uVar5 = 0;
  lVar4 = 8;
  if (param_1 == (CSoundInstance *)*plVar3) {
    lVar6 = 0;
  }
  else {
    do {
      lVar6 = lVar4;
      uVar5 = uVar5 + 1;
      if (uVar2 <= uVar5) goto LAB_00a6af35;
      lVar4 = lVar6 + 8;
    } while (param_1 != *(CSoundInstance **)((long)plVar3 + lVar6));
  }
  *(uint *)(this + 0x98) = uVar2 - 1;
  *(long *)((long)plVar3 + lVar6) = plVar3[uVar2 - 1];
                    /* WARNING: Could not recover jumptable at 0x00a6af70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 8))(param_1);
  return;
}

/* address=00a6af80
   symbol=CSoundManager::getNumberOfChannelsPlaying */

/* CSoundManager::getNumberOfChannelsPlaying() */

undefined4 __thiscall CSoundManager::getNumberOfChannelsPlaying(CSoundManager *this)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x18) != 0) {
    uVar1 = *(undefined4 *)(this + 0x14);
  }
  return uVar1;
}

/* address=00a6af90
   symbol=CSoundManager::incrementSoundBank */

/* CSoundManager::incrementSoundBank() */

void __thiscall CSoundManager::incrementSoundBank(CSoundManager *this)

{
  *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1;
  return;
}

/* address=00a6afa0
   symbol=CSoundManager::fmodFileCloseCallback */

/* CSoundManager::fmodFileCloseCallback(void*, void*) */

undefined8 CSoundManager::fmodFileCloseCallback(void *param_1,void *param_2)

{
  int iVar1;
  int *piVar2;

  if (*(long *)((long)param_1 + 0x20) != 0) {
    piVar2 = *(int **)((long)param_1 + 0x28);
    if (piVar2 != (int *)0x0) {
      iVar1 = *piVar2;
      *piVar2 = iVar1 + -1;
      if (iVar1 + -1 == 0) {
        (**(code **)(*(long *)((long)param_1 + 0x18) + 0x10))((long)param_1 + 0x18);
      }
    }
    *(undefined8 *)((long)param_1 + 0x20) = 0;
    *(undefined8 *)((long)param_1 + 0x28) = 0;
  }
  return 0;
}

/* address=00a6aff0
   symbol=CSoundManager::soundLoops */

/* CSoundManager::soundLoops(CSoundInstance*) */

uint __thiscall CSoundManager::soundLoops(CSoundManager *this,CSoundInstance *param_1)

{
  uint local_c;

  if ((param_1 != (CSoundInstance *)0x0) && (*(uint **)(param_1 + 0x40) != (uint *)0x0)) {
    FMOD::Sound::getMode(*(uint **)(param_1 + 0x40));
    return local_c >> 1 & 1;
  }
  return 0;
}

/* address=00a6b030
   symbol=CSoundManager::findSound */

/* CSoundManager::findSound(std::wstring&, SOUND_TYPE, bool, float, float) */

undefined8
CSoundManager::findSound(float param_1_00,long param_1,undefined8 *param_3,int param_4,char param_5)

{
  uint uVar1;
  uint uVar2;
  size_t __n;
  int iVar3;
  long *plVar4;
  uint uVar5;
  undefined8 *puVar6;
  long lVar7;

  uVar1 = *(uint *)(param_1 + 0x98);
  if (uVar1 != 0) {
    uVar2 = *(uint *)(param_1 + 0x9c);
    lVar7 = 0;
    uVar5 = 0;
    do {
      if (uVar5 < uVar2) {
        iVar3 = *(int *)(*(long *)(lVar7 + *(long *)(param_1 + 0x90)) + 0x38);
      }
      else {
        iVar3 = *(int *)(**(long **)(param_1 + 0x90) + 0x38);
      }
      if (iVar3 == param_4) {
        if (uVar5 < uVar2) {
          plVar4 = (long *)(lVar7 + *(long *)(param_1 + 0x90));
        }
        else {
          plVar4 = *(long **)(param_1 + 0x90);
        }
        __n = *(size_t *)((wchar_t *)*param_3 + -6);
        if (__n == *(size_t *)(*(wchar_t **)(*plVar4 + 0x10) + -6)) {
          iVar3 = wmemcmp((wchar_t *)*param_3,*(wchar_t **)(*plVar4 + 0x10),__n);
          if (iVar3 == 0) {
            if (uVar5 < uVar2) {
              plVar4 = (long *)(lVar7 + *(long *)(param_1 + 0x90));
            }
            else {
              plVar4 = *(long **)(param_1 + 0x90);
            }
            if (*(char *)(*plVar4 + 0x3c) == param_5) {
              if (uVar5 < uVar2) {
                plVar4 = (long *)(lVar7 + *(long *)(param_1 + 0x90));
              }
              else {
                plVar4 = *(long **)(param_1 + 0x90);
              }
              if ((param_1_00 == *(float *)(*plVar4 + 0x4c)) &&
                 (!NAN(param_1_00) && !NAN(*(float *)(*plVar4 + 0x4c)))) {
                if (uVar5 < uVar2) {
                  puVar6 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(param_1 + 0x90));
                }
                else {
                  puVar6 = *(undefined8 **)(param_1 + 0x90);
                }
                return *puVar6;
              }
            }
          }
        }
      }
      uVar5 = uVar5 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar5 < uVar1);
  }
  return 0;
}

/* address=00a6b1c0
   symbol=CSoundManager::stopSound */

/* CSoundManager::stopSound(int) */

void __thiscall CSoundManager::stopSound(CSoundManager *this,int param_1)

{
  int iVar1;
  undefined4 in_register_00000034;

  iVar1 = 0;
  if (*(int *)(this + 0x14) + -1 != -1) {
    iVar1 = *(int *)(this + 0x14) + -1;
  }
  *(int *)(this + 0x14) = iVar1;
  if ((param_1 != -1) && (param_1 < 0x40)) {
    FMOD::System::getChannel
              ((int)*(undefined8 *)(this + 0x18),(Channel **)CONCAT44(in_register_00000034,param_1))
    ;
    FMOD::Channel::stop();
    *(undefined8 *)(this + (long)param_1 * 0x18 + 0xb8) = 0;
    return;
  }
  return;
}

/* address=00a6b240
   symbol=CSoundManager::stopMusic */

/* CSoundManager::stopMusic() */

void __thiscall CSoundManager::stopMusic(CSoundManager *this)

{
  CSoundInstance *pCVar1;

  pCVar1 = *(CSoundInstance **)(this + 0x6d0);
  if (pCVar1 != (CSoundInstance *)0x0) {
    if (*(int *)(this + 0x6d8) != -1) {
      stopSound(this,*(int *)(this + 0x6d8));
      pCVar1 = *(CSoundInstance **)(this + 0x6d0);
    }
    releaseSound(this,pCVar1);
    *(undefined8 *)(this + 0x6d0) = 0;
  }
  return;
}

/* address=00a6b280
   symbol=CSoundManager::stopAllSounds */

/* CSoundManager::stopAllSounds() */

void __thiscall CSoundManager::stopAllSounds(CSoundManager *this)

{
  int iVar1;
  uint uVar2;
  CSoundManager *pCVar3;
  long local_30;

  uVar2 = 0;
  *(undefined4 *)(this + 0x14) = 0;
  stopSound(this,*(int *)(this + 0x6f0));
  pCVar3 = this;
  do {
    iVar1 = FMOD::System::getChannel((int)*(undefined8 *)(this + 0x18),(Channel **)(ulong)uVar2);
    if ((iVar1 == 0) && (local_30 != 0)) {
      FMOD::Channel::stop();
    }
    uVar2 = uVar2 + 1;
    *(undefined8 *)(pCVar3 + 0xb8) = 0;
    pCVar3 = pCVar3 + 0x18;
  } while (uVar2 != 0x40);
  return;
}

/* address=00a6b300
   symbol=CSoundManager::set3DMinMaxDistance */

/* CSoundManager::set3DMinMaxDistance(int, float, float) */

void __thiscall
CSoundManager::set3DMinMaxDistance(CSoundManager *this,int param_1,float param_2,float param_3)

{
  int extraout_EAX;
  undefined4 in_register_00000034;

  if ((param_1 != -1) && (param_1 < 0x40)) {
    FMOD::System::getChannel
              ((int)*(undefined8 *)(this + 0x18),(Channel **)CONCAT44(in_register_00000034,param_1))
    ;
    if (extraout_EAX == 0) {
      FMOD::Channel::set3DMinMaxDistance(param_2,param_3);
      return;
    }
  }
  return;
}

/* address=00a6b350
   symbol=CSoundManager::isChannelPlaying */

/* CSoundManager::isChannelPlaying(int) */

undefined8 __thiscall CSoundManager::isChannelPlaying(CSoundManager *this,int param_1)

{
  int iVar1;
  undefined4 in_register_00000034;
  bool *local_18;

  if (((param_1 != -1) && (param_1 < 0x40)) &&
     (iVar1 = FMOD::System::getChannel
                        ((int)*(undefined8 *)(this + 0x18),
                         (Channel **)CONCAT44(in_register_00000034,param_1)), iVar1 == 0)) {
    FMOD::Channel::isPlaying(local_18);
    return 0;
  }
  return 0;
}

/* address=00a6b3a0
   symbol=CSoundManager::setSoundVolume */

/* CSoundManager::setSoundVolume(int, float) */

void __thiscall CSoundManager::setSoundVolume(CSoundManager *this,int param_1,float param_2)

{
  int extraout_EAX;
  undefined4 in_register_00000034;

  if ((param_1 != -1) && (param_1 < 0x40)) {
    FMOD::System::getChannel
              ((int)*(undefined8 *)(this + 0x18),(Channel **)CONCAT44(in_register_00000034,param_1))
    ;
    if (extraout_EAX == 0) {
      FMOD::Channel::setVolume(param_2);
      return;
    }
  }
  return;
}

/* address=00a6b3e0
   symbol=CSoundManager::setPauseSound */

/* CSoundManager::setPauseSound(int, bool) */

void CSoundManager::setPauseSound(int param_1,bool param_2)

{
  int iVar1;
  undefined7 in_register_00000031;
  undefined4 in_register_0000003c;
  undefined1 local_10;

  iVar1 = (int)(Channel **)CONCAT71(in_register_00000031,param_2);
  if ((iVar1 != -1) && (iVar1 < 0x40)) {
    iVar1 = FMOD::System::getChannel
                      ((int)*(undefined8 *)(CONCAT44(in_register_0000003c,param_1) + 0x18),
                       (Channel **)CONCAT71(in_register_00000031,param_2));
    if (iVar1 == 0) {
      FMOD::Channel::setPaused(local_10);
      return;
    }
  }
  return;
}

/* address=00a6b430
   symbol=CSoundManager::getMusicFilePlaying */

/* CSoundManager::getMusicFilePlaying() */

void CSoundManager::getMusicFilePlaying(void)

{
  long in_RSI;
  wstring_conflict *in_RDI;

  if (*(long *)(in_RSI + 0x6d0) != 0) {
    std::wstring::wstring(in_RDI,(wstring_conflict *)(*(long *)(in_RSI + 0x6d0) + 0x10));
    return;
  }
  std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  return;
}

/* address=00a6b460
   symbol=CSoundManager::CSoundManager */

/* CSoundManager::CSoundManager(bool) */

void __thiscall CSoundManager::CSoundManager(CSoundManager *this,bool param_1)

{
  CRunicCore *this_00;
  long lVar1;

  this_00 = (CRunicCore *)(this + 0xa8);
  lVar1 = 0x3e;
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CSoundManager_00fe3bf0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x2c) = 0xffffffff;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  *(undefined4 *)(this + 0xa0) = 0x19;
  do {
                    /* try { // try from 00a6b55b to 00a6b55f has its CatchHandler @ 00a6b63f */
    CRunicCore::CRunicCore(this_00);
    lVar1 = lVar1 + -1;
    *(undefined ***)this_00 = &PTR__CChannelInstance_00fe3dd0;
    *(undefined8 *)(this_00 + 0x10) = 0;
    this_00 = this_00 + 0x18;
  } while (lVar1 != -2);
  this[0x6a8] = (CSoundManager)0x0;
  this[0x6a9] = (CSoundManager)0x0;
  lVar1 = 0;
  *(undefined8 *)(this + 0x6b0) = 0;
  *(undefined8 *)(this + 0x6b8) = 0;
  *(undefined8 *)(this + 0x6c0) = 0;
  this[0x6c8] = (CSoundManager)param_1;
  *(undefined8 *)(this + 0x6d0) = 0;
  *(undefined4 *)(this + 0x6f0) = 0xffffffff;
  *(undefined4 *)(this + 0x6f4) = 0;
  *(undefined4 **)(this + 0x6f8) = &DAT_01424558;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  do {
    *(undefined8 *)(this + lVar1 + 0xb8) = 0;
    lVar1 = lVar1 + 0x18;
  } while (lVar1 != 0x600);
  return;
}

/* address=00a6b6e0
   symbol=CSoundManager::createSoundGroup */

/* CSoundManager::createSoundGroup(std::string) */

undefined8 __thiscall CSoundManager::createSoundGroup(CSoundManager *this,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined8 local_10;

  uVar1 = 0;
  if (*(char **)(this + 0x18) != (char *)0x0) {
    FMOD::System::createSoundGroup(*(char **)(this + 0x18),(SoundGroup **)*param_2);
    uVar1 = local_10;
  }
  return uVar1;
}

/* address=00a6b710
   symbol=CSoundManager::getMemoryInUse */

/* CSoundManager::getMemoryInUse() */

undefined4 __thiscall CSoundManager::getMemoryInUse(CSoundManager *this)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c [3];

  local_c[0] = 0;
  local_10 = 0;
  uVar1 = 0;
  if (*(long *)(this + 0x18) != 0) {
    FMOD_Memory_GetStats(local_c,&local_10,1);
    uVar1 = local_c[0];
  }
  return uVar1;
}

/* address=00a6b750
   symbol=CSoundManager::updateAudioLevels */

/* CSoundManager::updateAudioLevels(float, float, bool, bool) */

void CSoundManager::updateAudioLevels(float param_1,float param_2,bool param_3,bool param_4)

{
  int iVar1;
  undefined7 in_register_00000039;
  long lVar2;
  undefined1 local_30;
  undefined1 local_28;

  lVar2 = CONCAT71(in_register_00000039,param_3);
  if (*(char *)(lVar2 + 0x6a8) != '\0') {
    iVar1 = FMOD::System::getMasterSoundGroup(*(SoundGroup ***)(lVar2 + 0x18));
    if (iVar1 == 0) {
      FMOD::SoundGroup::setVolume(param_1);
    }
    iVar1 = FMOD::System::getMasterChannelGroup(*(ChannelGroup ***)(lVar2 + 0x18));
    if (iVar1 == 0) {
      FMOD::ChannelGroup::setVolume(param_1);
      FMOD::ChannelGroup::setMute(local_28);
    }
    if (*(long *)(lVar2 + 0x6d0) != 0) {
      FMOD::SoundGroup::setVolume(param_2);
      if (*(uint *)(lVar2 + 0x6d8) != 0) {
        FMOD::System::getChannel
                  ((int)*(undefined8 *)(lVar2 + 0x18),(Channel **)(ulong)*(uint *)(lVar2 + 0x6d8));
        FMOD::Channel::setMute(local_30);
      }
    }
  }
  return;
}

/* address=00a6bb90
   symbol=CSoundManager::~CSoundManager */

/* WARNING: Removing unreachable block (ram,0x00a6be62) */
/* CSoundManager::~CSoundManager() */

void __thiscall CSoundManager::~CSoundManager(CSoundManager *this)

{
  int *piVar1;
  allocator *paVar2;
  long lVar3;
  int iVar4;
  long *plVar5;
  uint uVar6;
  long lVar7;
  CSoundManager *pCVar8;
  ulong uVar9;

  *(undefined ***)this = &PTR__CSoundManager_00fe3bf0;
  if (*(long *)(this + 0x6b8) != 0) {
                    /* try { // try from 00a6bbb0 to 00a6bcfd has its CatchHandler @ 00a6bda1 */
    FMOD::DSP::release();
  }
  if (*(long *)(this + 0x6c0) != 0) {
    FMOD::ChannelGroup::release();
  }
  stopMusic(this);
  stopSound(this,*(int *)(this + 0x6f0));
  lVar7 = *(long *)(this + 0x48);
  *(undefined4 *)(this + 0x6f0) = 0xffffffff;
  if (*(long *)(this + 0x50) - lVar7 >> 3 != 0) {
    uVar9 = 0;
    uVar6 = 0;
    do {
      lVar3 = uVar9 * 8;
      uVar6 = uVar6 + 1;
      uVar9 = (ulong)uVar6;
      piVar1 = (int *)(*(long *)(lVar7 + lVar3) + 0x48);
      *piVar1 = *piVar1 + -1;
      lVar7 = *(long *)(this + 0x48);
    } while (uVar9 < (ulong)(*(long *)(this + 0x50) - lVar7 >> 3));
  }
  *(long *)(this + 0x50) = lVar7;
  *(undefined8 *)(this + 0x38) = *(undefined8 *)(this + 0x30);
  *(undefined8 *)(this + 0x68) = *(undefined8 *)(this + 0x60);
  *(undefined8 *)(this + 0x80) = *(undefined8 *)(this + 0x78);
  if (*(int *)(this + 0x98) != 0) {
    uVar6 = 0;
    do {
      lVar7 = (ulong)uVar6 * 8;
      plVar5 = (long *)(lVar7 + *(long *)(this + 0x90));
      if ((long *)*plVar5 != (long *)0x0) {
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)(this + 0x90) + (ulong)uVar6 * 8) = 0;
        plVar5 = (long *)(lVar7 + *(long *)(this + 0x90));
      }
      *plVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x98));
  }
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
  }
  *(undefined8 *)(this + 0x90) = 0;
  if (*(long *)(this + 0x6e0) != 0) {
    FMOD::SoundGroup::release();
  }
  if (*(long *)(this + 0x6e8) != 0) {
    FMOD::ChannelGroup::release();
  }
  if (*(long *)(this + 0x18) != 0) {
    FMOD::System::release();
  }
  paVar2 = (allocator *)(*(long *)(this + 0x6f8) + -0x18);
  if (paVar2 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x6f8) + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar2);
    }
  }
  pCVar8 = this + 0x6a8;
  do {
    pCVar8 = pCVar8 + -0x18;
                    /* try { // try from 00a6bd33 to 00a6bd34 has its CatchHandler @ 00a6bdd2 */
    (*(code *)**(undefined8 **)pCVar8)(pCVar8);
  } while (pCVar8 != this + 0xa8);
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x78));
  }
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x60));
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x48));
  }
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x30));
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00a6be70
   symbol=CSoundManager::~CSoundManager */

/* CSoundManager::~CSoundManager() */

void __thiscall CSoundManager::~CSoundManager(CSoundManager *this)

{
  ~CSoundManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a6bf80
   symbol=CSoundManager::queueSound */

/* CSoundManager::queueSound(int, CSoundInstance*, float, float) */

void __thiscall
CSoundManager::queueSound
          (CSoundManager *this,int param_1,CSoundInstance *param_2,float param_3,float param_4)

{
  int iVar1;
  int *piVar2;
  undefined8 *puVar3;
  float *pfVar4;
  char cVar5;
  uint uVar6;
  long lVar7;
  ulong uVar8;
  float local_20;
  float local_1c;
  CSoundInstance *local_18;
  int local_c;

  local_20 = param_4;
  local_1c = param_3;
  local_18 = param_2;
  local_c = param_1;
  if ((*(int *)(this + 0x2c) != param_1) ||
     (cVar5 = isChannelPlaying(this,*(int *)(this + 0x6f0)), cVar5 == '\0')) {
    piVar2 = *(int **)(this + 0x30);
    uVar8 = *(long *)(this + 0x38) - (long)piVar2 >> 2;
    if (uVar8 == 0) {
LAB_00a6bfe3:
      *(int *)(local_18 + 0x48) = *(int *)(local_18 + 0x48) + 1;
      puVar3 = *(undefined8 **)(this + 0x50);
      if (puVar3 == *(undefined8 **)(this + 0x58)) {
        std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>::_M_insert_aux
                  ((vector<CSoundInstance*,std::allocator<CSoundInstance*>> *)(this + 0x48),puVar3,
                   &local_18);
      }
      else {
        lVar7 = 0;
        if (puVar3 != (undefined8 *)0x0) {
          *puVar3 = local_18;
          lVar7 = *(long *)(this + 0x50);
        }
        *(long *)(this + 0x50) = lVar7 + 8;
      }
      pfVar4 = *(float **)(this + 0x68);
      if (pfVar4 == *(float **)(this + 0x70)) {
        std::vector<float,std::allocator<float>>::_M_insert_aux
                  ((vector<float,std::allocator<float>> *)(this + 0x60),pfVar4,&local_1c);
      }
      else {
        lVar7 = 0;
        if (pfVar4 != (float *)0x0) {
          *pfVar4 = local_1c;
          lVar7 = *(long *)(this + 0x68);
        }
        *(long *)(this + 0x68) = lVar7 + 4;
      }
      pfVar4 = *(float **)(this + 0x80);
      if (pfVar4 == *(float **)(this + 0x88)) {
        std::vector<float,std::allocator<float>>::_M_insert_aux
                  ((vector<float,std::allocator<float>> *)(this + 0x78),pfVar4,&local_20);
      }
      else {
        lVar7 = 0;
        if (pfVar4 != (float *)0x0) {
          *pfVar4 = local_20;
          lVar7 = *(long *)(this + 0x80);
        }
        *(long *)(this + 0x80) = lVar7 + 4;
      }
      piVar2 = *(int **)(this + 0x38);
      if (piVar2 == *(int **)(this + 0x40)) {
        std::vector<int,std::allocator<int>>::_M_insert_aux
                  ((vector<int,std::allocator<int>> *)(this + 0x30),piVar2,&local_c);
      }
      else {
        lVar7 = 0;
        if (piVar2 != (int *)0x0) {
          *piVar2 = local_c;
          lVar7 = *(long *)(this + 0x38);
        }
        *(long *)(this + 0x38) = lVar7 + 4;
      }
    }
    else {
      uVar6 = 0;
      iVar1 = *piVar2;
      while (iVar1 != local_c) {
        uVar6 = uVar6 + 1;
        if (uVar8 <= uVar6) goto LAB_00a6bfe3;
        iVar1 = piVar2[uVar6];
      }
    }
  }
  return;
}

/* address=00a6c100
   symbol=CSoundManager::fmodFileOpenCallback */

/* WARNING: Removing unreachable block (ram,0x00a6c5ad) */
/* WARNING: Removing unreachable block (ram,0x00a6c583) */
/* WARNING: Removing unreachable block (ram,0x00a6c63b) */
/* WARNING: Removing unreachable block (ram,0x00a6c59f) */
/* WARNING: Removing unreachable block (ram,0x00a6c5bb) */
/* WARNING: Removing unreachable block (ram,0x00a6c591) */
/* CSoundManager::fmodFileOpenCallback(char const*, int, unsigned int*, void**, void**) */

undefined8
CSoundManager::fmodFileOpenCallback
          (char *param_1,int param_2,uint *param_3,void **param_4,void **param_5)

{
  int iVar1;
  int *piVar2;
  long lVar3;
  CFileSystem *this;
  undefined8 uVar4;
  undefined1 *local_f8;
  string local_f0 [8];
  long local_e8;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined1 *local_d8;
  undefined1 local_d0;
  undefined **local_c8;
  long local_c0;
  int *local_b8;
  undefined4 local_b0;
  undefined **local_a8;
  long local_a0;
  int *local_98;
  undefined4 local_90;
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  undefined4 *local_58 [2];
  undefined4 *local_48 [3];

  *param_4 = param_1;
  *param_5 = (void *)0x0;
  local_48[0] = &DAT_01424558;
  local_58[0] = &DAT_01424558;
                    /* try { // try from 00a6c151 to 00a6c155 has its CatchHandler @ 00a6c5e2 */
  std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(param_1 + 0x10));
                    /* try { // try from 00a6c174 to 00a6c178 has its CatchHandler @ 00a6c60c */
  FILESYSTEM::GetFileName((FILESYSTEM *)local_78,(wstring_conflict *)local_68);
                    /* try { // try from 00a6c187 to 00a6c18b has its CatchHandler @ 00a6c623 */
  std::wstring::assign((wstring_conflict *)local_48);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_78[0] + -8);
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 00a6c1bd to 00a6c1c1 has its CatchHandler @ 00a6c60c */
  FILESYSTEM::RemoveFileName((FILESYSTEM *)local_88,(wstring_conflict *)local_68);
                    /* try { // try from 00a6c1d0 to 00a6c1d4 has its CatchHandler @ 00a6c530 */
  std::wstring::assign((wstring_conflict *)local_58);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  local_f8 = &DAT_01423a38;
                    /* try { // try from 00a6c201 to 00a6c205 has its CatchHandler @ 00a6c571 */
  std::string::string(local_f0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00a6c20f to 00a6c213 has its CatchHandler @ 00a6c55b */
  std::wstring::wstring((wstring_conflict *)&local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_e0 = 4;
  local_dc = 3;
  local_d8 = &DAT_01423a38;
  local_d0 = 0;
                    /* try { // try from 00a6c232 to 00a6c29c has its CatchHandler @ 00a6c576 */
  this = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this,(wstring_conflict *)(param_1 + 0x10),(CFileInfo *)&local_f8,false,true,false);
  if (*(long *)(param_1 + 0x20) != 0) {
    piVar2 = *(int **)(param_1 + 0x28);
    if ((piVar2 != (int *)0x0) && (iVar1 = *piVar2, *piVar2 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00a6c408 to 00a6c40a has its CatchHandler @ 00a6c576 */
      (**(code **)(*(long *)(param_1 + 0x18) + 0x10))(param_1 + 0x18);
    }
    param_1[0x20] = '\0';
    param_1[0x21] = '\0';
    param_1[0x22] = '\0';
    param_1[0x23] = '\0';
    param_1[0x24] = '\0';
    param_1[0x25] = '\0';
    param_1[0x26] = '\0';
    param_1[0x27] = '\0';
    param_1[0x28] = '\0';
    param_1[0x29] = '\0';
    param_1[0x2a] = '\0';
    param_1[0x2b] = '\0';
    param_1[0x2c] = '\0';
    param_1[0x2d] = '\0';
    param_1[0x2e] = '\0';
    param_1[0x2f] = '\0';
  }
  CFileSystem::getSingleton();
  CFileSystem::getDataStream((CFileInfo *)&local_a8);
  if (*(long *)(param_1 + 0x20) != local_a0) {
    local_c0 = local_a0;
    local_c8 = &PTR__SharedPtr_00fe3cb0;
    local_b8 = local_98;
    local_b0 = local_90;
    if (local_98 != (int *)0x0) {
      *local_98 = *local_98 + 1;
    }
                    /* try { // try from 00a6c2dd to 00a6c2df has its CatchHandler @ 00a6c614 */
    (**(code **)(*(long *)(param_1 + 0x18) + 0x18))(param_1 + 0x18,&local_c8);
    local_c8 = &PTR__SharedPtr_00fe3cb0;
    if ((local_b8 != (int *)0x0) && (iVar1 = *local_b8, *local_b8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00a6c3f5 to 00a6c3f9 has its CatchHandler @ 00a6c5fa */
      Ogre::SharedPtr<Ogre::DataStream>::destroy((SharedPtr<Ogre::DataStream> *)&local_c8);
    }
  }
  local_a8 = &PTR__SharedPtr_00fe3cb0;
  if ((local_98 == (int *)0x0) || (iVar1 = *local_98, *local_98 = iVar1 + -1, iVar1 + -1 != 0)) {
    lVar3 = *(long *)(param_1 + 0x20);
  }
  else {
                    /* try { // try from 00a6c3c5 to 00a6c3c9 has its CatchHandler @ 00a6c576 */
    Ogre::SharedPtr<Ogre::DataStream>::destroy((SharedPtr<Ogre::DataStream> *)&local_a8);
    lVar3 = *(long *)(param_1 + 0x20);
  }
  if (lVar3 == 0) {
    uVar4 = 0x17;
    *param_3 = 0;
  }
  else {
    uVar4 = 0;
    *param_3 = (uint)*(undefined8 *)(lVar3 + 0x10);
  }
                    /* try { // try from 00a6c342 to 00a6c346 has its CatchHandler @ 00a6c5c9 */
  std::string::~string((string *)&local_d8);
  if ((allocator *)(local_e8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_e8 + -8);
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8 + -0x18));
    }
  }
                    /* try { // try from 00a6c35d to 00a6c361 has its CatchHandler @ 00a6c5e0 */
  std::string::~string(local_f0);
                    /* try { // try from 00a6c365 to 00a6c369 has its CatchHandler @ 00a6c60c */
  std::string::~string((string *)&local_f8);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_68[0] + -8);
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = local_58[0] + -2;
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
    }
  }
  if ((allocator *)(local_48[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = local_48[0] + -2;
    iVar1 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -6));
    }
  }
  return uVar4;
}

/* address=00a6c650
   symbol=CSoundManager::releaseUnusedSounds */

/* WARNING: Removing unreachable block (ram,0x00a6c86e) */
/* WARNING: Removing unreachable block (ram,0x00a6c863) */
/* CSoundManager::releaseUnusedSounds() */

void __thiscall CSoundManager::releaseUnusedSounds(CSoundManager *this)

{
  int *piVar1;
  long *plVar2;
  uint uVar3;
  undefined8 uVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  int iVar8;
  ulong uVar9;
  long *plVar10;
  long local_38 [2];
  long local_28 [2];

  stopSound(this,*(int *)(this + 0x6f0));
  lVar6 = *(long *)(this + 0x48);
  *(undefined4 *)(this + 0x6f0) = 0xffffffff;
  if (*(long *)(this + 0x50) - lVar6 >> 3 != 0) {
    uVar9 = 0;
    uVar5 = 0;
    do {
      lVar7 = uVar9 * 8;
      uVar5 = uVar5 + 1;
      uVar9 = (ulong)uVar5;
      piVar1 = (int *)(*(long *)(lVar6 + lVar7) + 0x48);
      *piVar1 = *piVar1 + -1;
      lVar6 = *(long *)(this + 0x48);
    } while (uVar9 < (ulong)(*(long *)(this + 0x50) - lVar6 >> 3));
  }
  uVar5 = *(uint *)(this + 0x98);
  iVar8 = 0;
  *(long *)(this + 0x50) = lVar6;
  *(undefined8 *)(this + 0x38) = *(undefined8 *)(this + 0x30);
  *(undefined8 *)(this + 0x68) = *(undefined8 *)(this + 0x60);
  *(undefined8 *)(this + 0x80) = *(undefined8 *)(this + 0x78);
  uVar3 = 0;
  if (uVar5 != 0) {
    do {
      while (*(uint *)(this + 0x9c) <= uVar3) {
        plVar10 = (long *)**(long **)(this + 0x90);
        if (0 < (int)plVar10[9]) goto LAB_00a6c6fb;
LAB_00a6c723:
        if (uVar5 != 0) {
          plVar2 = *(long **)(this + 0x90);
          uVar3 = 0;
          lVar6 = 8;
          if (plVar10 == (long *)*plVar2) {
            lVar7 = 0;
          }
          else {
            do {
              lVar7 = lVar6;
              uVar3 = uVar3 + 1;
              if (uVar5 <= uVar3) goto LAB_00a6c758;
              lVar6 = lVar7 + 8;
            } while (plVar10 != *(long **)((long)plVar2 + lVar7));
          }
          *(uint *)(this + 0x98) = uVar5 - 1;
          *(long *)((long)plVar2 + lVar7) = plVar2[uVar5 - 1];
        }
LAB_00a6c758:
        iVar8 = iVar8 + 1;
        (**(code **)(*plVar10 + 8))();
        uVar5 = *(uint *)(this + 0x98);
        uVar3 = 1;
        if (uVar5 < 2) goto LAB_00a6c770;
      }
      plVar10 = *(long **)((ulong)uVar3 * 8 + *(long *)(this + 0x90));
      if ((int)plVar10[9] < 1) goto LAB_00a6c723;
LAB_00a6c6fb:
      uVar3 = uVar3 + 1;
    } while (uVar3 < uVar5);
  }
LAB_00a6c770:
  Ogre::StringConverter::toString(local_28,iVar8,0,0x20,0);
                    /* try { // try from 00a6c794 to 00a6c798 has its CatchHandler @ 00a6c7f8 */
  std::operator+((char *)local_38,(string *)"Released sounds : ");
                    /* try { // try from 00a6c799 to 00a6c7af has its CatchHandler @ 00a6c856 */
  uVar4 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar4,local_38,2,0);
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar8 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
  if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_28[0] + -8);
    iVar8 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
    }
  }
  return;
}

/* address=00a6c880
   symbol=CSoundManager::getSoundLength */

/* WARNING: Removing unreachable block (ram,0x00a6c9e0) */
/* WARNING: Removing unreachable block (ram,0x00a6ca07) */
/* CSoundManager::getSoundLength(CSoundInstance*) */

undefined8 __thiscall CSoundManager::getSoundLength(CSoundManager *this,CSoundInstance *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  char *__s;
  float fVar5;
  undefined4 extraout_XMM0_Db;
  undefined4 uVar6;
  long local_38 [2];
  long local_28;
  uint local_20;
  allocator local_19;

  if ((param_1 != (CSoundInstance *)0x0) && (*(uint **)(param_1 + 0x40) != (uint *)0x0)) {
    uVar3 = FMOD::Sound::getLength(*(uint **)(param_1 + 0x40),(uint)&local_20);
    if (uVar3 == 0) {
      fVar5 = (float)local_20 / DAT_00fa871c;
      uVar6 = extraout_XMM0_Db;
      goto LAB_00a6c944;
    }
    __s = "Unknown error.";
    if (uVar3 < 0x60) {
      __s = *(char **)(CSWTCH_3054 + (ulong)uVar3 * 8);
    }
                    /* try { // try from 00a6c8e0 to 00a6c8e4 has its CatchHandler @ 00a6c9d5 */
    std::string::string((string *)&local_28,
                        "SoundManager::GetSoundLength could not get length  FMOD Error:",&local_19);
                    /* try { // try from 00a6c8eb to 00a6c8ef has its CatchHandler @ 00a6c9eb */
    std::string::string((string *)local_38,(string *)&local_28);
    strlen(__s);
                    /* try { // try from 00a6c901 to 00a6c905 has its CatchHandler @ 00a6c9f8 */
    std::string::append((char *)local_38,(ulong)__s);
                    /* try { // try from 00a6c906 to 00a6c91c has its CatchHandler @ 00a6ca05 */
    uVar4 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar4,local_38,2,0);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
        fVar5 = 0.0;
        uVar6 = 0;
        goto LAB_00a6c944;
      }
    }
  }
  fVar5 = 0.0;
  uVar6 = 0;
LAB_00a6c944:
  return CONCAT44(uVar6,fVar5);
}

/* address=00a6ca20
   symbol=CSoundManager::playSound */

/* WARNING: Removing unreachable block (ram,0x00a6d18b) */
/* WARNING: Removing unreachable block (ram,0x00a6d20e) */
/* CSoundManager::playSound(CSoundInstance*, Ogre::SceneNode*, int, float) */

int __thiscall
CSoundManager::playSound
          (CSoundManager *this,CSoundInstance *param_1,SceneNode *param_2,int param_3,float param_4)

{
  int *piVar1;
  short *psVar2;
  undefined4 *puVar3;
  wstring_conflict *pwVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  long lVar9;
  short *psVar10;
  ulong uVar11;
  long lVar12;
  long *plVar13;
  short *psVar14;
  char *__s;
  float fVar15;
  float fVar16;
  short *local_118;
  int local_110;
  wstring_conflict *local_100;
  undefined2 *local_f8;
  undefined4 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  UTFString local_d8 [32];
  wstring_conflict local_b8 [16];
  STRINGS local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  long local_78 [2];
  long local_68 [2];
  wstring_conflict local_58 [16];
  bool *local_48;
  int local_40;
  allocator local_3a;
  char local_39;

  uVar6 = KSETTINGS_SOUND_DEBUG;
  if ((((this[0x6a9] != (CSoundManager)0x0) && (this[0x6a8] != (CSoundManager)0x0)) ||
      (param_1 == (CSoundInstance *)0x0)) ||
     (((iVar5 = *(int *)(param_1 + 0x38), iVar5 == 4 || (iVar5 == 2)) ||
      ((iVar5 == 6 || (iVar5 == 5)))))) {
    if ((param_4 <= DAT_00fa47f8) && (!NAN(param_4) && !NAN(DAT_00fa47f8))) {
      lVar9 = CMasterResourceManager::getSingleton();
      iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar9 + 0x90),uVar6);
      if (iVar5 == 0) {
        return -1;
      }
      std::operator+((wchar_t *)local_58,(wstring_conflict *)L"CULLED ZERO VOLUME SOUND : ");
                    /* try { // try from 00a6cc3a to 00a6cc4d has its CatchHandler @ 00a6d247 */
      lVar9 = CMasterResourceManager::getSingleton();
      CConsole::addTextNoHistory(*(CConsole **)(lVar9 + 0xa0),local_58);
      std::wstring::~wstring(local_58);
      return -1;
    }
    if (param_1 != (CSoundInstance *)0x0) {
      if ((((param_3 != -1) && (param_3 < 0x40)) &&
          (*(long *)(this + (long)param_3 * 0x18 + 0xb8) != 0)) &&
         ((((iVar5 = *(int *)(param_1 + 0x38), iVar5 == 4 || (iVar5 == 2)) || (iVar5 == 6)) &&
          (iVar5 = FMOD::System::getChannel
                             ((int)*(undefined8 *)(this + 0x18),(Channel **)(ulong)(uint)param_3),
          iVar5 == 0)))) {
        iVar5 = FMOD::Channel::isPlaying(local_48);
        *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
        if (((iVar5 == 0) && (local_39 != '\0')) &&
           (*(SceneNode **)(this + (long)param_3 * 0x18 + 0xb8) == param_2)) {
          return param_3;
        }
        stopSound(this,param_3);
      }
      uVar6 = FMOD::System::playSound
                        (*(undefined8 *)(this + 0x18),0xffffffff,*(undefined8 *)(param_1 + 0x40),1,
                         &local_48);
      if (uVar6 == 0) {
        *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
        FMOD::Channel::getIndex((int *)local_48);
        iVar5 = local_40;
        if (0x3f < param_3) {
          FMOD::Channel::stop();
          return -1;
        }
        *(SceneNode **)(this + (long)local_40 * 0x18 + 0xb8) = param_2;
        fVar15 = (float)UTILITIES::randomBetweenVolatile(0.0,*(float *)(param_1 + 0x4c));
        fVar16 = DAT_00fa47fc;
        if (fVar15 + param_4 <= DAT_00fa47fc) {
          fVar16 = fVar15 + param_4;
        }
        FMOD::Channel::setVolume(fVar16);
        FMOD::Channel::setPaused((bool)local_48._0_1_);
        uVar6 = KSETTINGS_SOUND_DEBUG;
        lVar9 = CMasterResourceManager::getSingleton();
        iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar9 + 0x90),uVar6);
        if (iVar7 == 0) {
          return iVar5;
        }
        STRINGS::GetValueAsString(local_a8,local_40);
        local_f8 = &DAT_01426458;
        local_e0 = 0;
        local_f0 = 0;
        local_e8 = 0;
                    /* try { // try from 00a6cdcf to 00a6cdd3 has its CatchHandler @ 00a6d21c */
        Ogre::UTFString::assign((UTFString *)&local_f8,(string *)local_a8);
                    /* try { // try from 00a6cde5 to 00a6cde9 has its CatchHandler @ 00a6d267 */
        std::operator+((wchar_t *)local_88,(wstring_conflict *)L"PLAYING SOUND : ");
                    /* try { // try from 00a6cdfa to 00a6cdfe has its CatchHandler @ 00a6d262 */
        std::wstring::wstring(local_98,local_88);
        wcslen(L" on channel ");
                    /* try { // try from 00a6ce19 to 00a6ce1d has its CatchHandler @ 00a6d235 */
        std::wstring::append((wchar_t *)local_98,0xfe3808);
                    /* try { // try from 00a6ce2b to 00a6ce2f has its CatchHandler @ 00a6d230 */
        Ogre::UTFString::UTFString(local_d8,local_98);
                    /* try { // try from 00a6ce3f to 00a6ce43 has its CatchHandler @ 00a6d22b */
        Ogre::operator+((Ogre *)&local_118,local_d8,(UTFString *)&local_f8);
        if (local_110 != 2) {
                    /* try { // try from 00a6ce54 to 00a6d04a has its CatchHandler @ 00a6d209 */
          Ogre::UTFString::_cleanBuffer((UTFString *)&local_118);
          local_100 = operator_new(8);
          *(undefined4 **)local_100 = &DAT_01424558;
          local_110 = 2;
        }
        std::wstring::clear();
        pwVar4 = local_100;
        std::wstring::reserve((ulong)local_100);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_118);
        psVar2 = local_118 + *(long *)(local_118 + -0xc);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_118);
        psVar10 = local_118;
        while (psVar14 = psVar10, psVar2 != psVar14) {
          while( true ) {
            psVar10 = local_118 + -0xc;
            if ((-1 < *(int *)(local_118 + -4)) &&
               (psVar10 !=
                (short *)&std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_S_empty_rep_storage)) {
              if (*(int *)(local_118 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_118,0,0,0);
                psVar10 = local_118 + -0xc;
              }
              psVar10[8] = -1;
              psVar10[9] = -1;
            }
            lVar9 = (long)psVar14 - (long)local_118 >> 1;
            uVar6 = (ushort)local_118[lVar9] + 0x2800;
            if ((((ushort)uVar6 < 0x400) &&
                (uVar11 = lVar9 + 1, uVar11 < *(ulong *)(local_118 + -0xc))) &&
               ((ushort)(local_118[uVar11] + 0x2400U) < 0x400)) {
              uVar6 = ((ushort)(local_118[uVar11] + 0x2400U) & 0x3ff | (uVar6 & 0x3ff) << 10) +
                      0x10000;
            }
            else {
              uVar6 = (uint)(ushort)local_118[lVar9];
            }
            lVar9 = *(long *)pwVar4;
            lVar12 = *(long *)(lVar9 + -0x18);
            uVar11 = lVar12 + 1;
            if ((*(ulong *)(lVar9 + -0x10) < uVar11) || (0 < *(int *)(lVar9 + -8))) {
              std::wstring::reserve((ulong)pwVar4);
              lVar9 = *(long *)pwVar4;
              lVar12 = *(long *)(lVar9 + -0x18);
            }
            *(uint *)(lVar9 + lVar12 * 4) = uVar6;
            puVar3 = *(undefined4 **)pwVar4;
            if (puVar3 != &DAT_01424558) {
              puVar3[-2] = 0;
              *(ulong *)(puVar3 + -6) = uVar11;
              puVar3[uVar11] = 0;
            }
            plVar13 = (long *)(local_118 + -0xc);
            if ((-1 < *(int *)(local_118 + -4)) &&
               (plVar13 !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage)) {
              if (*(int *)(local_118 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_118,0,0,0);
                plVar13 = (long *)(local_118 + -0xc);
              }
              *(undefined4 *)(plVar13 + 2) = 0xffffffff;
              plVar13 = (long *)(local_118 + -0xc);
            }
            psVar10 = psVar14 + 1;
            if (((psVar10 == local_118 + *plVar13) || (0x3ff < (ushort)(psVar14[1] + 0x2400U))) ||
               (0x3ff < (ushort)(*psVar14 + 0x2800U))) break;
            psVar14 = psVar14 + 2;
            if (psVar2 == psVar14) goto LAB_00a6d036;
          }
        }
LAB_00a6d036:
        std::wstring::wstring(local_b8,local_100);
                    /* try { // try from 00a6d04b to 00a6d05e has its CatchHandler @ 00a6d1c4 */
        lVar9 = CMasterResourceManager::getSingleton();
        CConsole::addTextNoHistory(*(CConsole **)(lVar9 + 0xa0),local_b8);
                    /* try { // try from 00a6d062 to 00a6d066 has its CatchHandler @ 00a6d209 */
        std::wstring::~wstring(local_b8);
                    /* try { // try from 00a6d06c to 00a6d070 has its CatchHandler @ 00a6d22b */
        Ogre::UTFString::~UTFString((UTFString *)&local_118);
                    /* try { // try from 00a6d076 to 00a6d07a has its CatchHandler @ 00a6d230 */
        Ogre::UTFString::~UTFString(local_d8);
                    /* try { // try from 00a6d083 to 00a6d087 has its CatchHandler @ 00a6d262 */
        std::wstring::~wstring(local_98);
                    /* try { // try from 00a6d090 to 00a6d094 has its CatchHandler @ 00a6d267 */
        std::wstring::~wstring(local_88);
                    /* try { // try from 00a6d09a to 00a6d09e has its CatchHandler @ 00a6d1b2 */
        Ogre::UTFString::~UTFString((UTFString *)&local_f8);
        std::string::~string((string *)local_a8);
        return iVar5;
      }
      __s = "Unknown error.";
      if (uVar6 < 0x60) {
        __s = *(char **)(CSWTCH_3054 + (ulong)uVar6 * 8);
      }
                    /* try { // try from 00a6cb27 to 00a6cb2b has its CatchHandler @ 00a6d180 */
      std::string::string((string *)local_68,
                          "SoundManager::PlaySound could not play sound  FMOD Error:",&local_3a);
                    /* try { // try from 00a6cb3a to 00a6cb3e has its CatchHandler @ 00a6d25a */
      std::string::string((string *)local_78,(string *)local_68);
      strlen(__s);
                    /* try { // try from 00a6cb50 to 00a6cb54 has its CatchHandler @ 00a6d196 */
      std::string::append((char *)local_78,(ulong)__s);
                    /* try { // try from 00a6cb55 to 00a6cb6b has its CatchHandler @ 00a6d1ab */
      uVar8 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar8,(string *)local_78,2,0);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_68[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
          return -1;
        }
      }
    }
  }
  return -1;
}

/* address=00a6d270
   symbol=CSoundManager::update */

/* CSoundManager::update(Ogre::SceneNode*, Ogre::Vector3 const&, float) */

void __thiscall
CSoundManager::update(CSoundManager *this,SceneNode *param_1,Vector3 *param_2,float param_3)

{
  undefined8 *puVar1;
  float fVar2;
  char cVar3;
  undefined4 uVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  long lVar8;

  if (this[0x6a8] != (CSoundManager)0x0) {
    *(undefined4 *)(this + 0x10) = 0;
    (**(code **)(*(long *)param_1 + 200))(param_1);
    Ogre::Quaternion::zAxis();
    (**(code **)(*(long *)param_1 + 200))(param_1);
    Ogre::Quaternion::yAxis();
    FMOD::System::update();
    *(undefined4 *)(this + 0x20) = *(undefined4 *)param_2;
    *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_2 + 4);
    *(undefined4 *)(this + 0x28) = *(undefined4 *)(param_2 + 8);
    if (*(long *)(this + 0x68) - *(long *)(this + 0x60) >> 2 == 0) {
      cVar3 = isChannelPlaying(this,*(int *)(this + 0x6f0));
      if (cVar3 == '\0') {
        *(undefined4 *)(this + 0x6f4) = 0;
        *(undefined4 *)(this + 0x6f0) = 0xffffffff;
      }
    }
    else if (((*(int *)(this + 0x6f0) == -1) ||
             (cVar3 = isChannelPlaying(this,*(int *)(this + 0x6f0)), cVar3 == '\0')) &&
            (fVar2 = *(float *)(this + 0x6f4), *(float *)(this + 0x6f4) = param_3 + fVar2,
            **(float **)(this + 0x78) <= param_3 + fVar2)) {
      *(undefined4 *)(this + 0x6f4) = 0;
      stopSound(this,*(int *)(this + 0x6f0));
      uVar4 = playSound(this,(CSoundInstance *)**(undefined8 **)(this + 0x48),(SceneNode *)0x0,
                        (int)**(float **)(this + 0x60),DAT_00fa47fc);
      *(undefined4 *)(this + 0x6f0) = uVar4;
      *(int *)(**(long **)(this + 0x48) + 0x48) = *(int *)(**(long **)(this + 0x48) + 0x48) + -1;
      lVar8 = *(long *)(this + 0x38);
      *(undefined4 *)(this + 0x2c) = **(undefined4 **)(this + 0x30);
      if (1 < (int)(lVar8 - (long)*(undefined4 **)(this + 0x30) >> 2)) {
        lVar7 = 0;
        iVar6 = 0;
        lVar5 = 0;
        do {
          iVar6 = iVar6 + 1;
          puVar1 = (undefined8 *)(*(long *)(this + 0x48) + lVar7);
          lVar7 = lVar7 + 8;
          *puVar1 = *(undefined8 *)(*(long *)(this + 0x48) + lVar7);
          *(undefined4 *)(*(long *)(this + 0x60) + lVar5) =
               *(undefined4 *)(*(long *)(this + 0x60) + 4 + lVar5);
          *(undefined4 *)(*(long *)(this + 0x30) + lVar5) =
               *(undefined4 *)(*(long *)(this + 0x30) + 4 + lVar5);
          *(undefined4 *)(*(long *)(this + 0x78) + lVar5) =
               *(undefined4 *)(*(long *)(this + 0x78) + 4 + lVar5);
          lVar8 = *(long *)(this + 0x38);
          lVar5 = lVar5 + 4;
        } while (iVar6 < (int)(lVar8 - *(long *)(this + 0x30) >> 2) + -1);
      }
      *(long *)(this + 0x50) = *(long *)(this + 0x50) + -8;
      *(long *)(this + 0x68) = *(long *)(this + 0x68) + -4;
      *(long *)(this + 0x38) = lVar8 + -4;
      *(long *)(this + 0x80) = *(long *)(this + 0x80) + -4;
    }
  }
  return;
}

/* address=00a6d4b0
   symbol=CSoundManager::createSound */

/* WARNING: Removing unreachable block (ram,0x00a6dae6) */
/* WARNING: Removing unreachable block (ram,0x00a6dad8) */
/* CSoundManager::createSound(std::wstring, SOUND_TYPE, bool, float, float) */

CRunicCore *
CSoundManager::createSound(undefined4 param_1,long param_2,wstring_conflict *param_3,int param_4)

{
  int *piVar1;
  CRunicCore *this;
  long lVar2;
  undefined8 uVar3;
  void *pvVar4;
  uint uVar5;
  FMOD_CREATESOUNDEXINFO *pFVar6;
  ulong uVar7;
  int iVar8;
  char *pcVar9;
  uint uVar10;
  Ogre local_228 [32];
  UTFString local_208 [32];
  Ogre local_1e8 [32];
  UTFString local_1c8 [32];
  Ogre local_1a8 [32];
  UTFString local_188 [32];
  UTFString local_168 [32];
  Ogre local_148 [32];
  UTFString local_128 [32];
  Ogre local_108 [32];
  UTFString local_e8 [32];
  UTFString local_c8 [32];
  string local_a8 [16];
  string local_98 [16];
  UTFString local_88 [16];
  UTFString local_78 [16];
  long local_68 [2];
  undefined4 *local_58 [2];
  undefined8 local_48;

  if (*(char *)(param_2 + 0x6a8) == '\0') {
    return (CRunicCore *)0x0;
  }
  local_58[0] = &DAT_01424558;
  if ((1 < param_4 - 5U) && (this = (CRunicCore *)findSound(), this != (CRunicCore *)0x0)) {
    *(int *)(this + 0x48) = *(int *)(this + 0x48) + 1;
    goto LAB_00a6d518;
  }
                    /* try { // try from 00a6d57b to 00a6d58f has its CatchHandler @ 00a6db74 */
  std::wstring::assign((wstring_conflict *)local_58);
  this = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a6d599 to 00a6d59d has its CatchHandler @ 00a6db9c */
  CRunicCore::CRunicCore(this);
  *(undefined ***)this = &PTR__CSoundInstance_00fe3c10;
  *(undefined4 **)(this + 0x10) = &DAT_01424558;
  *(undefined ***)(this + 0x18) = &PTR__SharedPtr_00fe3cb0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  this[0x3c] = (CRunicCore)0x0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
                    /* try { // try from 00a6d5f9 to 00a6d5fd has its CatchHandler @ 00a6dbae */
  CSoundInstance::clear((CSoundInstance *)this);
                    /* try { // try from 00a6d605 to 00a6d636 has its CatchHandler @ 00a6db74 */
  std::wstring::assign((wstring_conflict *)(this + 0x10));
  *(int *)(this + 0x38) = param_4;
  this[0x3c] = (CRunicCore)0x0;
  *(undefined4 *)(this + 0x4c) = param_1;
  *(undefined4 *)(this + 0x50) = 0;
  STRINGS::StringUpper((STRINGS *)local_68,param_3);
  wcslen(L".OGG");
                    /* try { // try from 00a6d64e to 00a6d652 has its CatchHandler @ 00a6db65 */
  lVar2 = std::wstring::find((wchar_t *)local_68,0xfe3878,0);
  uVar5 = 0x20;
  if (lVar2 != -1) {
    uVar5 = 0x40;
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar8 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  switch(param_4) {
  default:
                    /* try { // try from 00a6d68e to 00a6d6a2 has its CatchHandler @ 00a6db74 */
    (**(code **)(*(long *)this + 8))(this);
    Ogre::UTFString::UTFString(local_128,"\' (invalid soundType)");
                    /* try { // try from 00a6d6b1 to 00a6d6b5 has its CatchHandler @ 00a6db40 */
    Ogre::UTFString::UTFString(local_e8,param_3);
                    /* try { // try from 00a6d6c6 to 00a6d6ca has its CatchHandler @ 00a6db39 */
    Ogre::UTFString::UTFString(local_c8,"SoundManager::CreateSound could not load sound \'");
                    /* try { // try from 00a6d6dc to 00a6d6e0 has its CatchHandler @ 00a6db32 */
    Ogre::operator+(local_108,local_c8,local_e8);
                    /* try { // try from 00a6d6f7 to 00a6d6fb has its CatchHandler @ 00a6daf1 */
    Ogre::operator+(local_148,(UTFString *)local_108,local_128);
                    /* try { // try from 00a6d70a to 00a6d70e has its CatchHandler @ 00a6db95 */
    Ogre::UTFString::operator_cast_to_string(local_78);
                    /* try { // try from 00a6d70f to 00a6d725 has its CatchHandler @ 00a6db7b */
    uVar3 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar3,local_78,2,0);
                    /* try { // try from 00a6d729 to 00a6d72d has its CatchHandler @ 00a6db95 */
    std::string::~string((string *)local_78);
                    /* try { // try from 00a6d731 to 00a6d735 has its CatchHandler @ 00a6daf1 */
    Ogre::UTFString::~UTFString((UTFString *)local_148);
                    /* try { // try from 00a6d739 to 00a6d73d has its CatchHandler @ 00a6db32 */
    Ogre::UTFString::~UTFString((UTFString *)local_108);
                    /* try { // try from 00a6d741 to 00a6d745 has its CatchHandler @ 00a6db39 */
    Ogre::UTFString::~UTFString(local_c8);
                    /* try { // try from 00a6d749 to 00a6d74d has its CatchHandler @ 00a6db40 */
    Ogre::UTFString::~UTFString(local_e8);
                    /* try { // try from 00a6d756 to 00a6d7c8 has its CatchHandler @ 00a6db74 */
    Ogre::UTFString::~UTFString(local_128);
    goto LAB_00a6d75b;
  case 1:
    pFVar6 = (FMOD_CREATESOUNDEXINFO *)(ulong)(uVar5 | 0x1000010);
    break;
  case 2:
    pFVar6 = (FMOD_CREATESOUNDEXINFO *)(ulong)(uVar5 | 0x1000012);
    break;
  case 3:
    pFVar6 = (FMOD_CREATESOUNDEXINFO *)(ulong)(uVar5 | 0x1000009);
    break;
  case 4:
    pFVar6 = (FMOD_CREATESOUNDEXINFO *)(ulong)(uVar5 | 0x100000a);
    break;
  case 5:
    uVar5 = uVar5 | 0x1000008;
    goto LAB_00a6d77e;
  case 6:
    uVar5 = uVar5 | 0x100000a;
LAB_00a6d77e:
    uVar5 = FMOD::System::createStream
                      (*(char **)(param_2 + 0x18),(uint)this,(FMOD_CREATESOUNDEXINFO *)(ulong)uVar5,
                       (Sound **)0x0);
    goto LAB_00a6d794;
  }
  uVar5 = FMOD::System::createSound(*(char **)(param_2 + 0x18),(uint)this,pFVar6,(Sound **)0x0);
LAB_00a6d794:
  if (uVar5 == 0) {
    *(int *)(this + 0x48) = *(int *)(this + 0x48) + 1;
    *(undefined8 *)(this + 0x40) = local_48;
    uVar5 = *(uint *)(param_2 + 0x98);
    if (uVar5 < *(uint *)(param_2 + 0x9c)) {
      pvVar4 = *(void **)(param_2 + 0x90);
    }
    else if (*(long *)(param_2 + 0x90) == 0) {
      *(uint *)(param_2 + 0x9c) = *(uint *)(param_2 + 0xa0);
      pvVar4 = operator_new__((ulong)*(uint *)(param_2 + 0xa0) * 8);
      *(void **)(param_2 + 0x90) = pvVar4;
      uVar5 = *(uint *)(param_2 + 0x98);
    }
    else {
      uVar10 = *(uint *)(param_2 + 0x9c) + *(int *)(param_2 + 0xa0);
      pvVar4 = operator_new__((ulong)uVar10 << 3);
      if (*(int *)(param_2 + 0x9c) != 0) {
        uVar5 = 0;
        do {
          uVar7 = (ulong)uVar5;
          uVar5 = uVar5 + 1;
          *(undefined8 *)((long)pvVar4 + uVar7 * 8) =
               *(undefined8 *)(*(long *)(param_2 + 0x90) + uVar7 * 8);
        } while (uVar5 < *(uint *)(param_2 + 0x9c));
      }
      if (*(void **)(param_2 + 0x90) != (void *)0x0) {
        operator_delete__(*(void **)(param_2 + 0x90));
      }
      uVar5 = *(uint *)(param_2 + 0x98);
      *(void **)(param_2 + 0x90) = pvVar4;
      *(uint *)(param_2 + 0x9c) = uVar10;
    }
    *(CRunicCore **)((long)pvVar4 + (ulong)uVar5 * 8) = this;
    iVar8 = *(int *)(param_2 + 0x98) + 1;
    *(int *)(param_2 + 0x98) = iVar8;
    Ogre::StringConverter::toString(local_98,iVar8,0,0x20,0);
                    /* try { // try from 00a6da33 to 00a6da37 has its CatchHandler @ 00a6db5e */
    std::operator+((char *)local_a8,(string *)"Total sounds loaded: ");
                    /* try { // try from 00a6da38 to 00a6da4e has its CatchHandler @ 00a6db47 */
    uVar3 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar3,local_a8,2,0);
                    /* try { // try from 00a6da52 to 00a6da56 has its CatchHandler @ 00a6db5e */
    std::string::~string(local_a8);
                    /* try { // try from 00a6da5a to 00a6da90 has its CatchHandler @ 00a6db74 */
    std::string::~string(local_98);
  }
  else {
    (**(code **)(*(long *)this + 8))(this);
    pcVar9 = "Unknown error.";
    if (uVar5 < 0x60) {
      pcVar9 = *(char **)(CSWTCH_3054 + (ulong)uVar5 * 8);
    }
    Ogre::UTFString::UTFString(local_208,pcVar9);
                    /* try { // try from 00a6d7d3 to 00a6d7d7 has its CatchHandler @ 00a6dc47 */
    Ogre::UTFString::UTFString(local_1c8,"\'  FMOD Error:");
                    /* try { // try from 00a6d7e6 to 00a6d7ea has its CatchHandler @ 00a6dc40 */
    Ogre::UTFString::UTFString(local_188,param_3);
                    /* try { // try from 00a6d7fb to 00a6d7ff has its CatchHandler @ 00a6dc39 */
    Ogre::UTFString::UTFString(local_168,"SoundManager::CreateSound could not load sound \'");
                    /* try { // try from 00a6d811 to 00a6d815 has its CatchHandler @ 00a6dc32 */
    Ogre::operator+(local_1a8,local_168,local_188);
                    /* try { // try from 00a6d826 to 00a6d82a has its CatchHandler @ 00a6dc2b */
    Ogre::operator+(local_1e8,(UTFString *)local_1a8,local_1c8);
                    /* try { // try from 00a6d83b to 00a6d83f has its CatchHandler @ 00a6dc24 */
    Ogre::operator+(local_228,(UTFString *)local_1e8,local_208);
                    /* try { // try from 00a6d84e to 00a6d852 has its CatchHandler @ 00a6dc1d */
    Ogre::UTFString::operator_cast_to_string(local_88);
                    /* try { // try from 00a6d853 to 00a6d869 has its CatchHandler @ 00a6dbcf */
    uVar3 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar3,local_88,2,0);
                    /* try { // try from 00a6d86d to 00a6d871 has its CatchHandler @ 00a6dc1d */
    std::string::~string((string *)local_88);
                    /* try { // try from 00a6d875 to 00a6d879 has its CatchHandler @ 00a6dc24 */
    Ogre::UTFString::~UTFString((UTFString *)local_228);
                    /* try { // try from 00a6d87d to 00a6d881 has its CatchHandler @ 00a6dc2b */
    Ogre::UTFString::~UTFString((UTFString *)local_1e8);
                    /* try { // try from 00a6d885 to 00a6d889 has its CatchHandler @ 00a6dc32 */
    Ogre::UTFString::~UTFString((UTFString *)local_1a8);
                    /* try { // try from 00a6d88d to 00a6d891 has its CatchHandler @ 00a6dc39 */
    Ogre::UTFString::~UTFString(local_168);
                    /* try { // try from 00a6d895 to 00a6d899 has its CatchHandler @ 00a6dc40 */
    Ogre::UTFString::~UTFString(local_188);
                    /* try { // try from 00a6d89f to 00a6d8a3 has its CatchHandler @ 00a6dc47 */
    Ogre::UTFString::~UTFString(local_1c8);
                    /* try { // try from 00a6d8a9 to 00a6da1f has its CatchHandler @ 00a6db74 */
    Ogre::UTFString::~UTFString(local_208);
LAB_00a6d75b:
    this = (CRunicCore *)0x0;
  }
LAB_00a6d518:
  if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = local_58[0] + -2;
    iVar8 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
    }
  }
  return this;
}

/* address=00a6dc50
   symbol=CSoundManager::playMusic */

/* WARNING: Removing unreachable block (ram,0x00a6e097) */
/* WARNING: Removing unreachable block (ram,0x00a6e13d) */
/* WARNING: Removing unreachable block (ram,0x00a6e148) */
/* WARNING: Removing unreachable block (ram,0x00a6e16e) */
/* WARNING: Removing unreachable block (ram,0x00a6e0b7) */
/* CSoundManager::playMusic(std::wstring&, bool) */

undefined4 __thiscall
CSoundManager::playMusic(CSoundManager *this,wstring_conflict *param_1,bool param_2)

{
  int *piVar1;
  CDynamicPropertyFile *this_00;
  uint uVar2;
  int iVar3;
  long lVar4;
  long lVar5;
  CFileSystem *this_01;
  CFileInfo *this_02;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined1 *local_b8;
  string local_b0 [8];
  long local_a8;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined1 *local_98;
  undefined1 local_90;
  ChannelGroup *local_80;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];

  stopMusic(this);
  STRINGS::StringUpper((STRINGS *)local_48,param_1);
                    /* try { // try from 00a6dc88 to 00a6dc8c has its CatchHandler @ 00a6e0b5 */
  std::wstring::assign(param_1);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  wcslen(L"MUSIC");
  lVar4 = std::wstring::find((wchar_t *)param_1,0xfd7bb0,0);
  if (lVar4 != -1) {
    this_02 = *(CFileInfo **)(*(long *)param_1 + -0x18);
    wcslen(L"MUSIC");
    lVar4 = std::wstring::find((wchar_t *)param_1,0xfd7bb0,0);
    wcslen(L"MUSIC");
    lVar5 = std::wstring::find((wchar_t *)param_1,0xfd7bb0,0);
    if (*(ulong *)(*(long *)param_1 + -0x18) < lVar5 + 5U) {
LAB_00a6dfd5:
      std::__throw_out_of_range("basic_string::substr");
LAB_00a6dfe0:
      uVar8 = 0;
LAB_00a6df0d:
                    /* try { // try from 00a6df17 to 00a6df1b has its CatchHandler @ 00a6e051 */
      std::string::~string((string *)(this_02 + 0x20));
      if ((allocator *)(local_a8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_a8 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8 + -0x18));
        }
      }
                    /* try { // try from 00a6df32 to 00a6df36 has its CatchHandler @ 00a6e00e */
      std::string::~string((string *)(this_02 + 8));
      std::string::~string((string *)this_02);
      return uVar8;
    }
    std::wstring::wstring
              ((wstring_conflict *)local_58,param_1,lVar5 + 5U,(ulong)(this_02 + (5 - lVar4)));
                    /* try { // try from 00a6dd3e to 00a6dd42 has its CatchHandler @ 00a6e169 */
    std::wstring::assign(param_1);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
  }
  this_02 = (CFileInfo *)local_68;
LAB_00a6dd60:
  piVar1 = *(int **)param_1;
  lVar4 = *(long *)(piVar1 + -6);
  if (lVar4 == 0) {
    iVar3 = *piVar1;
LAB_00a6dd72:
    if (iVar3 != 0x2f) {
      this_02 = (CFileInfo *)&local_b8;
      local_b8 = &DAT_01423a38;
                    /* try { // try from 00a6dd92 to 00a6dd96 has its CatchHandler @ 00a6e0c5 */
      std::string::string(local_b0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00a6dda0 to 00a6dda4 has its CatchHandler @ 00a6e158 */
      std::wstring::wstring((wstring_conflict *)&local_a8,(wstring_conflict *)&::EMPTY_WSTRING);
      local_a0 = 4;
      local_9c = 3;
      local_98 = &DAT_01423a38;
      local_90 = 0;
                    /* try { // try from 00a6ddc3 to 00a6ddfa has its CatchHandler @ 00a6e153 */
      this_01 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(this_01,param_1,this_02,false,true,false);
      std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&local_a8);
                    /* try { // try from 00a6de0b to 00a6de0f has its CatchHandler @ 00a6e122 */
      lVar4 = createSound(0,this,(wstring_conflict *)local_78,6 - (uint)!param_2,0);
      *(long *)(this + 0x6d0) = lVar4;
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
        lVar4 = *(long *)(this + 0x6d0);
      }
      if (lVar4 == 0) goto LAB_00a6dfe0;
                    /* try { // try from 00a6de3d to 00a6df0c has its CatchHandler @ 00a6e153 */
      FMOD::Sound::setSoundGroup(*(SoundGroup **)(lVar4 + 0x40));
      uVar2 = playSound(this,*(CSoundInstance **)(this + 0x6d0),(SceneNode *)0x0,-1,DAT_00fa47fc);
      *(uint *)(this + 0x6d8) = uVar2;
      if (uVar2 == 0xffffffff) goto LAB_00a6dfe0;
      iVar3 = FMOD::System::getChannel((int)*(undefined8 *)(this + 0x18),(Channel **)(ulong)uVar2);
      if (iVar3 == 0) {
                    /* try { // try from 00a6dff4 to 00a6dff8 has its CatchHandler @ 00a6e153 */
        FMOD::Channel::setChannelGroup(local_80);
        this_00 = *(CDynamicPropertyFile **)(this + 0x6b0);
      }
      else {
        this_00 = *(CDynamicPropertyFile **)(this + 0x6b0);
      }
      if (this_00 != (CDynamicPropertyFile *)0x0) {
        CDynamicPropertyFile::GetInt(this_00,KSETTINGS_MUSICMUTE);
        iVar3 = CDynamicPropertyFile::GetInt
                          (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_SOUNDMUTE);
        fVar6 = (float)CDynamicPropertyFile::GetFloat
                                 (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_F_MUSICVOLUME);
        fVar7 = (float)CDynamicPropertyFile::GetFloat
                                 (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_F_SOUNDVOLUME);
        updateAudioLevels(fVar7,fVar6,SUB81(this,0),iVar3 != 0);
      }
      uVar8 = getSoundLength(this,*(CSoundInstance **)(this + 0x6d0));
      goto LAB_00a6df0d;
    }
    if (lVar4 == 0) goto LAB_00a6dfd5;
  }
  else {
    iVar3 = *piVar1;
    if (iVar3 != 0x2e) goto LAB_00a6dd72;
  }
  std::wstring::wstring((wstring_conflict *)this_02,param_1,1,lVar4 - 1);
                    /* try { // try from 00a6df85 to 00a6df89 has its CatchHandler @ 00a6e0a2 */
  std::wstring::assign(param_1);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  goto LAB_00a6dd60;
}

/* address=00a6e180
   symbol=CSoundManager::dumpSounds */

/* WARNING: Removing unreachable block (ram,0x00a6e7f1) */
/* WARNING: Removing unreachable block (ram,0x00a6e733) */
/* WARNING: Removing unreachable block (ram,0x00a6e764) */
/* WARNING: Removing unreachable block (ram,0x00a6e772) */
/* WARNING: Removing unreachable block (ram,0x00a6e78b) */
/* CSoundManager::dumpSounds() */

void __thiscall CSoundManager::dumpSounds(CSoundManager *this)

{
  ulong uVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined8 uVar7;
  long *plVar8;
  undefined2 *puVar9;
  long lVar10;
  uint *puVar11;
  long lVar12;
  short sVar13;
  short sVar14;
  uint local_e4;
  undefined2 *local_d8;
  undefined4 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined2 *local_b8;
  undefined4 local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined2 *local_98;
  undefined4 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined2 *local_78;
  undefined4 local_70;
  undefined8 local_68;
  undefined8 local_60;
  string local_58 [16];
  long local_48;
  allocator local_39 [9];

  if (*(int *)(this + 0x98) != 0) {
    local_e4 = 0;
    do {
      if (local_e4 < *(uint *)(this + 0x9c)) {
        plVar8 = (long *)((ulong)local_e4 * 8 + *(long *)(this + 0x90));
      }
      else {
        plVar8 = *(long **)(this + 0x90);
      }
      lVar12 = *plVar8;
      local_98 = &DAT_01426458;
      local_80 = 0;
      local_90 = 0;
      local_88 = 0;
                    /* try { // try from 00a6e202 to 00a6e2ef has its CatchHandler @ 00a6e6a9 */
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 *)&local_98,0,
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_Rep::_S_empty_rep_storage,0);
      std::
      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
      reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_98,*(ulong *)(*(long *)(lVar12 + 0x10) + -0x18));
      puVar11 = *(uint **)(lVar12 + 0x10);
      puVar3 = puVar11 + *(long *)(puVar11 + -6);
      if (puVar11 != puVar3) {
        sVar14 = 0;
        do {
          uVar5 = *puVar11;
          lVar12 = 1;
          sVar13 = (short)uVar5;
          if (0xffff < uVar5) {
            lVar12 = 2;
            sVar14 = ((ushort)(uVar5 - 0x10000) & 0x3ff) + 0xdc00;
            sVar13 = ((ushort)(uVar5 - 0x10000 >> 10) & 0x3ff) + 0xd800;
          }
          lVar10 = *(long *)(local_98 + -0xc);
          uVar1 = lVar10 + 1;
          if ((*(ulong *)(local_98 + -8) < uVar1) || (0 < *(int *)(local_98 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_98,uVar1);
            lVar10 = *(long *)(local_98 + -0xc);
          }
          local_98[lVar10] = sVar13;
          if (local_98 != &DAT_01426458) {
            *(undefined4 *)(local_98 + -4) = 0;
            *(ulong *)(local_98 + -0xc) = uVar1;
            local_98[uVar1] = 0;
          }
          if (lVar12 == 2) {
            lVar12 = *(long *)(local_98 + -0xc);
            uVar1 = lVar12 + 1;
            if ((*(ulong *)(local_98 + -8) < uVar1) || (0 < *(int *)(local_98 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_98,uVar1);
              lVar12 = *(long *)(local_98 + -0xc);
            }
            local_98[lVar12] = sVar14;
            if (local_98 != &DAT_01426458) {
              *(undefined4 *)(local_98 + -4) = 0;
              *(ulong *)(local_98 + -0xc) = uVar1;
              local_98[uVar1] = 0;
            }
          }
          puVar11 = puVar11 + 1;
        } while (puVar3 != puVar11);
      }
      local_78 = &DAT_01426458;
      local_60 = 0;
      local_70 = 0;
      local_68 = 0;
                    /* try { // try from 00a6e366 to 00a6e36a has its CatchHandler @ 00a6e6be */
      std::string::string(local_58,"Sound : ",local_39);
                    /* try { // try from 00a6e37e to 00a6e382 has its CatchHandler @ 00a6e6e3 */
      Ogre::UTFString::assign((UTFString *)&local_78,local_58);
                    /* try { // try from 00a6e38b to 00a6e38f has its CatchHandler @ 00a6e6f5 */
      std::string::~string(local_58);
      local_d8 = &DAT_01426458;
      local_c0 = 0;
      local_d0 = 0;
      local_c8 = 0;
      puVar9 = local_78;
      puVar6 = local_d8;
      if (local_78 != &DAT_01426458) {
        if (*(int *)(local_78 + -4) < 0) {
                    /* try { // try from 00a6e5ba to 00a6e5be has its CatchHandler @ 00a6e7fc */
          puVar9 = (undefined2 *)
                   std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_M_clone((_Rep *)(local_78 + -0xc),(allocator *)local_58,0);
          puVar6 = puVar9;
          if ((ulong *)(local_d8 + -0xc) !=
              &std::
               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8 + -4);
            iVar4 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              operator_delete(local_d8 + -0xc);
            }
          }
        }
        else {
          puVar6 = local_78;
          if ((_Rep *)(local_78 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_78 + -4) = *(int *)(local_78 + -4) + 1;
            UNLOCK();
            puVar6 = local_78;
          }
        }
      }
      local_d8 = puVar6;
      lVar12 = *(long *)(local_98 + -0xc);
      if (lVar12 != 0) {
        lVar10 = *(long *)(puVar9 + -0xc);
        uVar1 = lVar10 + lVar12;
        if ((*(ulong *)(puVar9 + -8) < uVar1) || (0 < *(int *)(puVar9 + -4))) {
                    /* try { // try from 00a6e42e to 00a6e432 has its CatchHandler @ 00a6e717 */
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_d8,uVar1);
          lVar10 = *(long *)(local_d8 + -0xc);
        }
        if (lVar12 == 1) {
          local_d8[lVar10] = *local_98;
        }
        else {
          memmove(local_d8 + lVar10,local_98,lVar12 * 2);
        }
        if (local_d8 != &DAT_01426458) {
          *(undefined4 *)(local_d8 + -4) = 0;
          *(ulong *)(local_d8 + -0xc) = uVar1;
          local_d8[uVar1] = 0;
        }
      }
      local_b8 = &DAT_01426458;
      local_a0 = 0;
      local_b0 = 0;
      local_a8 = 0;
      puVar9 = local_b8;
      if (local_d8 != &DAT_01426458) {
        if (*(int *)(local_d8 + -4) < 0) {
                    /* try { // try from 00a6e61a to 00a6e61e has its CatchHandler @ 00a6e80e */
          puVar9 = (undefined2 *)
                   std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_M_clone((_Rep *)(local_d8 + -0xc),(allocator *)local_58,0);
          if ((ulong *)(local_b8 + -0xc) !=
              &std::
               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8 + -4);
            iVar4 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              operator_delete(local_b8 + -0xc);
            }
          }
        }
        else {
          puVar9 = local_d8;
          if ((_Rep *)(local_d8 + -0xc) !=
              (_Rep *)&std::
                       basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       ::_Rep::_S_empty_rep_storage) {
            LOCK();
            *(int *)(local_d8 + -4) = *(int *)(local_d8 + -4) + 1;
            UNLOCK();
            puVar9 = local_d8;
          }
        }
      }
      local_b8 = puVar9;
                    /* try { // try from 00a6e4d2 to 00a6e4d6 has its CatchHandler @ 00a6e786 */
      Ogre::UTFString::~UTFString((UTFString *)&local_d8);
                    /* try { // try from 00a6e4e4 to 00a6e4e8 has its CatchHandler @ 00a6e799 */
      Ogre::UTFString::operator_cast_to_string((UTFString *)&local_48);
                    /* try { // try from 00a6e4e9 to 00a6e504 has its CatchHandler @ 00a6e7ab */
      uVar7 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar7,&local_48,3,0);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar2 = (int *)(local_48 + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
                    /* try { // try from 00a6e523 to 00a6e527 has its CatchHandler @ 00a6e786 */
      Ogre::UTFString::~UTFString((UTFString *)&local_b8);
                    /* try { // try from 00a6e530 to 00a6e534 has its CatchHandler @ 00a6e7e9 */
      Ogre::UTFString::~UTFString((UTFString *)&local_78);
      Ogre::UTFString::~UTFString((UTFString *)&local_98);
      local_e4 = local_e4 + 1;
    } while (local_e4 < *(uint *)(this + 0x98));
  }
  return;
}

/* address=00a6e820
   symbol=CSoundManager::initialize */

/* WARNING: Removing unreachable block (ram,0x00a6ed4f) */
/* WARNING: Removing unreachable block (ram,0x00a6ed5d) */
/* WARNING: Removing unreachable block (ram,0x00a6ed0f) */
/* CSoundManager::initialize(CSettings*) */

void __thiscall CSoundManager::initialize(CSoundManager *this,CSettings *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  Exception *pEVar5;
  char *__s;
  float fVar6;
  float fVar7;
  long local_e8 [2];
  string local_d8 [16];
  string local_c8 [16];
  string local_b8 [16];
  string local_a8 [16];
  string local_98 [16];
  long local_88 [2];
  long local_78 [2];
  string local_68 [16];
  string local_58 [16];
  string local_48 [13];
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  *(CSettings **)(this + 0x6b0) = param_1;
  if (this[0x6c8] != (CSoundManager)0x0) {
    uVar3 = FMOD_System_Create(this + 0x18);
    if (uVar3 != 0) {
      __s = "Unknown error.";
      if (uVar3 < 0x60) {
        __s = *(char **)(CSWTCH_3054 + (ulong)uVar3 * 8);
      }
      Ogre::StringConverter::toString(local_48,uVar3,0,0x20,0);
                    /* try { // try from 00a6e99e to 00a6e9a2 has its CatchHandler @ 00a6ed01 */
      std::operator+((char *)local_58,(string *)"FMOD error! (");
                    /* try { // try from 00a6e9b1 to 00a6e9b5 has its CatchHandler @ 00a6edd8 */
      std::string::string(local_68,local_58);
                    /* try { // try from 00a6e9c3 to 00a6e9c7 has its CatchHandler @ 00a6ede2 */
      std::string::append((char *)local_68,0xfe171c);
                    /* try { // try from 00a6e9d6 to 00a6e9da has its CatchHandler @ 00a6ed6f */
      std::string::string((string *)local_78,local_68);
      strlen(__s);
                    /* try { // try from 00a6e9ec to 00a6e9f0 has its CatchHandler @ 00a6ed81 */
      std::string::append((char *)local_78,(ulong)__s);
                    /* try { // try from 00a6ea09 to 00a6ea0d has its CatchHandler @ 00a6ed95 */
      std::string::string((string *)local_88,"SoundManager::Initialize",local_39);
      pEVar5 = (Exception *)__cxa_allocate_exception(0x40);
                    /* try { // try from 00a6ea3d to 00a6ea41 has its CatchHandler @ 00a6eda4 */
      Ogre::Exception::Exception
                (pEVar5,7,(string *)local_78,(string *)local_88,"InternalErrorException",
                 "/builddir/Torchlight/TorchlightMacPort_09b/Projects_9156/Delvers/Delvers/sound/SoundManager.cpp"
                 ,0x123);
      *(undefined ***)pEVar5 = &PTR__InternalErrorException_00fe3d70;
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_88[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
                    /* try { // try from 00a6ea80 to 00a6ea84 has its CatchHandler @ 00a6ecdc */
      std::string::~string(local_68);
                    /* try { // try from 00a6ea88 to 00a6ea8c has its CatchHandler @ 00a6ed3f */
      std::string::~string(local_58);
                    /* try { // try from 00a6ea90 to 00a6ea94 has its CatchHandler @ 00a6ed1d */
      std::string::~string(local_48);
                    /* WARNING: Subroutine does not return */
      __cxa_throw(pEVar5,&Ogre::InternalErrorException::typeinfo,
                  Ogre::InternalErrorException::~InternalErrorException);
    }
    iVar2 = FMOD::System::init((int)*(undefined8 *)(this + 0x18),0x40,(void *)0x0);
    if (iVar2 != 0) {
      return;
    }
    iVar2 = FMOD::System::setFileSystem
                      (*(_func_FMOD_RESULT_char_ptr_int_uint_ptr_void_ptr_ptr_void_ptr_ptr **)
                        (this + 0x18),fmodFileOpenCallback,fmodFileCloseCallback,
                       fmodFileReadCallback,fmodFileSeekCallback,
                       (_func_FMOD_RESULT_void_ptr_void_ptr *)0x0,0);
    if (iVar2 != 0) {
      Ogre::StringConverter::toString(local_98,iVar2,0,0x20,0);
                    /* try { // try from 00a6eb53 to 00a6eb57 has its CatchHandler @ 00a6eea5 */
      std::operator+((char *)local_a8,(string *)"FMOD error! (");
                    /* try { // try from 00a6eb68 to 00a6eb6c has its CatchHandler @ 00a6ee6c */
      std::operator+(local_b8,(char *)local_a8);
                    /* try { // try from 00a6eb7b to 00a6eb7f has its CatchHandler @ 00a6ee94 */
      std::operator+(local_c8,(char *)local_b8);
                    /* try { // try from 00a6eb95 to 00a6eb99 has its CatchHandler @ 00a6ee2e */
      std::string::string(local_d8,"SoundManager::Initialize",&local_3a);
      pEVar5 = (Exception *)__cxa_allocate_exception(0x40);
                    /* try { // try from 00a6ebc9 to 00a6ebcd has its CatchHandler @ 00a6ee55 */
      Ogre::Exception::Exception
                (pEVar5,7,local_c8,local_d8,"InternalErrorException",
                 "/builddir/Torchlight/TorchlightMacPort_09b/Projects_9156/Delvers/Delvers/sound/SoundManager.cpp"
                 ,0x136);
      *(undefined ***)pEVar5 = &PTR__InternalErrorException_00fe3d70;
                    /* try { // try from 00a6ebd8 to 00a6ebdc has its CatchHandler @ 00a6ee45 */
      std::string::~string(local_d8);
                    /* try { // try from 00a6ebe0 to 00a6ebe4 has its CatchHandler @ 00a6ee73 */
      std::string::~string(local_c8);
                    /* try { // try from 00a6ebe8 to 00a6ebec has its CatchHandler @ 00a6ee15 */
      std::string::~string(local_b8);
                    /* try { // try from 00a6ebf0 to 00a6ebf4 has its CatchHandler @ 00a6edf9 */
      std::string::~string(local_a8);
                    /* try { // try from 00a6ebf8 to 00a6ebfc has its CatchHandler @ 00a6edf4 */
      std::string::~string(local_98);
                    /* WARNING: Subroutine does not return */
      __cxa_throw(pEVar5,&Ogre::InternalErrorException::typeinfo,
                  Ogre::InternalErrorException::~InternalErrorException);
    }
    FMOD::System::createSoundGroup(*(char **)(this + 0x18),(SoundGroup **)"Music");
    FMOD::System::createChannelGroup(*(char **)(this + 0x18),(ChannelGroup **)"MusicChannel");
    this[0x6a8] = (CSoundManager)0x1;
    param_1 = *(CSettings **)(this + 0x6b0);
  }
  if (param_1 != (CSettings *)0x0) {
    CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)param_1,KSETTINGS_MUSICMUTE);
    iVar2 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_SOUNDMUTE);
    fVar6 = (float)CDynamicPropertyFile::GetFloat
                             (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_F_MUSICVOLUME);
    fVar7 = (float)CDynamicPropertyFile::GetFloat
                             (*(CDynamicPropertyFile **)(this + 0x6b0),KSETTINGS_F_SOUNDVOLUME);
    updateAudioLevels(fVar7,fVar6,SUB81(this,0),iVar2 != 0);
  }
                    /* try { // try from 00a6e8e3 to 00a6e8e7 has its CatchHandler @ 00a6ed08 */
  std::string::string((string *)local_e8,"SoundManager Initialized",&local_3b);
                    /* try { // try from 00a6e8e8 to 00a6e8fe has its CatchHandler @ 00a6ed30 */
  uVar4 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar4,(string *)local_e8,2,0);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  return;
}

/* export-summary functions=32 failures=0 */
