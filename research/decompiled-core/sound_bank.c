/* Targeted Ghidra class export.
   namespace=CSoundBank
   Treat pseudocode as navigation evidence. */


/* address=00a687d0
   symbol=CSoundBank::setRadius */

/* CSoundBank::setRadius(float) */

void __thiscall CSoundBank::setRadius(CSoundBank *this,float param_1)

{
  uint uVar1;
  ulong uVar2;

  *(float *)(this + 0xb0) = param_1;
  this[0xa8] = (CSoundBank)0x1;
  if ((int)(*(long *)(this + 0x50) - *(long *)(this + 0x48) >> 3) * -0x55555555 != 0) {
    uVar2 = 0;
    do {
      uVar1 = (int)uVar2 + 1;
      *(float *)(*(long *)(this + 0x60) + uVar2 * 4) = param_1;
      uVar2 = (ulong)uVar1;
    } while (uVar1 < (uint)((int)(*(long *)(this + 0x50) - *(long *)(this + 0x48) >> 3) *
                           -0x55555555));
  }
  return;
}

/* address=00a68830
   symbol=CSoundBank::bankPlaying */

/* CSoundBank::bankPlaying(int) */

undefined8 __thiscall CSoundBank::bankPlaying(CSoundBank *this,int param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;

  if (((param_1 < (int)(*(long *)(this + 0x50) - *(long *)(this + 0x48) >> 3) * -0x55555555) &&
      (-1 < param_1)) && (*(uint *)(this + 0x38) != 0)) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x3c)) {
        iVar1 = *(int *)(lVar3 + *(long *)(this + 0x30));
      }
      else {
        iVar1 = **(int **)(this + 0x30);
      }
      if (param_1 == iVar1) {
        return 1;
      }
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 4;
    } while (uVar2 < *(uint *)(this + 0x38));
  }
  return 0;
}

/* address=00a688a0
   symbol=CSoundBank::queueGlobalSample */

/* CSoundBank::queueGlobalSample(int, float, float) */

void __thiscall
CSoundBank::queueGlobalSample(CSoundBank *this,int param_1,float param_2,float param_3)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  float fVar5;

  if ((((*(char *)(*(long *)(this + 0x10) + 0x6a9) != '\0') &&
       (*(char *)(*(long *)(this + 0x10) + 0x6a8) != '\0')) &&
      (lVar3 = *(long *)(this + 0x48),
      param_1 < (int)(*(long *)(this + 0x50) - lVar3 >> 3) * -0x55555555)) && (-1 < param_1)) {
    lVar4 = (long)param_1;
    if (-1 < *(int *)(*(long *)(this + 0x90) + lVar4 * 4)) {
      iVar1 = UTILITIES::randomIntegerBetweenVolatile(1,100);
      if (*(int *)(*(long *)(this + 0x90) + lVar4 * 4) <= iVar1) {
        return;
      }
      lVar3 = *(long *)(this + 0x48);
    }
    if ((param_2 != DAT_00fa47f8) || (NAN(param_2) || NAN(DAT_00fa47f8))) {
      fVar5 = param_2 * *(float *)(this + 0xac);
    }
    else {
      fVar5 = *(float *)(*(long *)(this + 0x78) + lVar4 * 4);
    }
    lVar4 = (ulong)(uint)param_1 * 0x18;
    if ((int)((ulong)(((long *)(lVar3 + lVar4))[1] - *(long *)(lVar3 + lVar4)) >> 3) != 0) {
      *(float *)(this + 0xc4) = fVar5;
      uVar2 = UTILITIES::randomIntegerBetweenVolatile
                        (0,(int)(((long *)(lVar4 + *(long *)(this + 0x48)))[1] -
                                 *(long *)(lVar4 + *(long *)(this + 0x48)) >> 3) + -1);
      CSoundManager::queueSound
                (*(CSoundManager **)(this + 0x10),param_1,
                 *(CSoundInstance **)(*(long *)(*(long *)(this + 0x48) + lVar4) + (ulong)uVar2 * 8),
                 *(float *)(this + 0xc4),param_3);
      return;
    }
  }
  return;
}

/* address=00a68a20
   symbol=CSoundBank::pause */

/* CSoundBank::pause() */

void __thiscall CSoundBank::pause(CSoundBank *this)

{
  undefined4 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x20) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x24)) {
        puVar1 = (undefined4 *)((ulong)uVar2 * 4 + *(long *)(this + 0x18));
      }
      else {
        puVar1 = *(undefined4 **)(this + 0x18);
      }
      uVar2 = uVar2 + 1;
      CSoundManager::setPauseSound((int)*(undefined8 *)(this + 0x10),SUB41(*puVar1,0));
    } while (uVar2 < *(uint *)(this + 0x20));
  }
  this[0xa8] = (CSoundBank)0x1;
  return;
}

/* address=00a68a80
   symbol=CSoundBank::resume */

/* CSoundBank::resume() */

void __thiscall CSoundBank::resume(CSoundBank *this)

{
  undefined4 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x20) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x24)) {
        puVar1 = (undefined4 *)((ulong)uVar2 * 4 + *(long *)(this + 0x18));
      }
      else {
        puVar1 = *(undefined4 **)(this + 0x18);
      }
      uVar2 = uVar2 + 1;
      CSoundManager::setPauseSound((int)*(undefined8 *)(this + 0x10),SUB41(*puVar1,0));
    } while (uVar2 < *(uint *)(this + 0x20));
  }
  this[0xa8] = (CSoundBank)0x1;
  return;
}

/* address=00a68ae0
   symbol=CSoundBank::stop */

/* CSoundBank::stop(int) */

void __thiscall CSoundBank::stop(CSoundBank *this,int param_1)

{
  undefined4 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x20) != 0) {
    uVar2 = 0;
    do {
      while (*(uint *)(this + 0x3c) <= uVar2) {
        if (**(int **)(this + 0x30) != param_1) goto LAB_00a68b01;
LAB_00a68b1d:
        if (uVar2 < *(uint *)(this + 0x24)) {
          CSoundManager::stopSound
                    (*(CSoundManager **)(this + 0x10),
                     *(int *)((ulong)uVar2 * 4 + *(long *)(this + 0x18)));
          if (uVar2 < *(uint *)(this + 0x3c)) goto LAB_00a68b72;
LAB_00a68b36:
          puVar1 = *(undefined4 **)(this + 0x30);
        }
        else {
          CSoundManager::stopSound(*(CSoundManager **)(this + 0x10),**(int **)(this + 0x18));
          if (*(uint *)(this + 0x3c) <= uVar2) goto LAB_00a68b36;
LAB_00a68b72:
          puVar1 = (undefined4 *)((ulong)uVar2 * 4 + *(long *)(this + 0x30));
        }
        *puVar1 = 0xffffffff;
        uVar2 = uVar2 + 1;
        if (*(uint *)(this + 0x20) <= uVar2) goto LAB_00a68b48;
      }
      if (*(int *)((ulong)uVar2 * 4 + *(long *)(this + 0x30)) == param_1) goto LAB_00a68b1d;
LAB_00a68b01:
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x20));
  }
LAB_00a68b48:
  this[0xa8] = (CSoundBank)0x1;
  return;
}

/* address=00a68b80
   symbol=CSoundBank::configureVolumeScale */

/* CSoundBank::configureVolumeScale(float, Ogre::Vector3 const&) */

float __thiscall CSoundBank::configureVolumeScale(CSoundBank *this,float param_1,Vector3 *param_2)

{
  float fVar1;
  float fVar2;

  if (param_1 != 0.0) {
    fVar2 = *(float *)(*(long *)(this + 0x10) + 0x20) - *(float *)param_2;
    fVar1 = *(float *)(*(long *)(this + 0x10) + 0x28) - *(float *)(param_2 + 8);
    fVar2 = SQRT(fVar2 * fVar2 + 0.0 + fVar1 * fVar1);
    fVar1 = param_1;
    if (fVar2 <= param_1) {
      fVar1 = fVar2;
    }
    return DAT_00fa47fc - fVar1 / param_1;
  }
  return 0.0;
}

/* address=00a68be0
   symbol=CSoundBank::CSoundBank */

/* CSoundBank::CSoundBank(CSoundManager&, bool) */

void __thiscall CSoundBank::CSoundBank(CSoundBank *this,CSoundManager *param_1,bool param_2)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(CSoundManager **)(this + 0x10) = param_1;
  this[0xb4] = (CSoundBank)param_2;
  *(undefined ***)this = &PTR__CSoundBank_00fe1670;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 2;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 2;
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
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  this[0xa8] = (CSoundBank)0x1;
  *(undefined4 *)(this + 0xac) = 0x3f800000;
  *(undefined4 *)(this + 0xb0) = 0x41200000;
  *(undefined4 *)(this + 0xc4) = 0;
  this[200] = (CSoundBank)0x0;
  return;
}

/* address=00a68d00
   symbol=CSoundBank::_GLOBAL__I_CSoundBank */

/* CSoundBank::CSoundBank(CSoundManager&, bool) */

void CSoundBank::_GLOBAL__I_CSoundBank(void)

{
  allocator local_14;
  allocator local_13;
  allocator local_12;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 00a68daf to 00a68db3 has its CatchHandler @ 00a68f85 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",local_9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 00a68dd7 to 00a68ddb has its CatchHandler @ 00a68fb6 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 00a68dff to 00a68e03 has its CatchHandler @ 00a68fb4 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 00a68e27 to 00a68e2b has its CatchHandler @ 00a68fb2 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 00a68e4f to 00a68e53 has its CatchHandler @ 00a68fa6 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 00a68e77 to 00a68e7b has its CatchHandler @ 00a68fa4 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 00a68e9f to 00a68ea3 has its CatchHandler @ 00a68fa2 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 00a68ec7 to 00a68ecb has its CatchHandler @ 00a68f96 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_10);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 00a68eef to 00a68ef3 has its CatchHandler @ 00a68f94 */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_11);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 00a68f17 to 00a68f1b has its CatchHandler @ 00a68f92 */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_12);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 00a68f3f to 00a68f43 has its CatchHandler @ 00a68f8f */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_13);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 00a68f67 to 00a68f6b has its CatchHandler @ 00a68f8d */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_14);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  return;
}

/* address=00a68fd0
   symbol=CSoundBank::stop */

/* CSoundBank::stop() */

void __thiscall CSoundBank::stop(CSoundBank *this)

{
  int *piVar1;
  uint uVar2;

  if (*(int *)(this + 0x20) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x24)) {
        piVar1 = (int *)((ulong)uVar2 * 4 + *(long *)(this + 0x18));
      }
      else {
        piVar1 = *(int **)(this + 0x18);
      }
      uVar2 = uVar2 + 1;
      CSoundManager::stopSound(*(CSoundManager **)(this + 0x10),*piVar1);
    } while (uVar2 < *(uint *)(this + 0x20));
  }
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
  }
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
  }
  *(undefined8 *)(this + 0x30) = 0;
  this[0xa8] = (CSoundBank)0x1;
  return;
}

/* address=00a69070
   symbol=CSoundBank::clear */

/* CSoundBank::clear() */

void __thiscall CSoundBank::clear(CSoundBank *this)

{
  long lVar1;
  undefined8 *puVar2;
  ulong uVar3;
  long lVar4;
  ulong uVar5;
  uint uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;

  if (this[200] != (CSoundBank)0x0) {
    stop(this);
  }
  puVar2 = *(undefined8 **)(this + 0x50);
  puVar7 = *(undefined8 **)(this + 0x48);
  puVar8 = puVar7;
  if (((long)puVar2 - (long)puVar7 >> 3) * -0x5555555555555555 != 0) {
    uVar3 = 0;
    uVar6 = 0;
    do {
      uVar5 = 0;
      lVar4 = puVar7[uVar3 * 3];
      if ((puVar7 + uVar3 * 3)[1] - lVar4 >> 3 != 0) {
        do {
          lVar1 = uVar5 * 8;
          uVar5 = (ulong)((int)uVar5 + 1);
          CSoundManager::releaseSound
                    (*(CSoundManager **)(this + 0x10),*(CSoundInstance **)(lVar4 + lVar1));
          puVar7 = *(undefined8 **)(this + 0x48);
          lVar4 = puVar7[uVar3 * 3];
        } while (uVar5 < (ulong)((puVar7 + uVar3 * 3)[1] - lVar4 >> 3));
        puVar2 = *(undefined8 **)(this + 0x50);
      }
      uVar6 = uVar6 + 1;
      uVar3 = (ulong)uVar6;
      puVar8 = puVar7;
    } while (uVar3 < (ulong)(((long)puVar2 - (long)puVar7 >> 3) * -0x5555555555555555));
  }
  for (; puVar2 != puVar7; puVar7 = puVar7 + 3) {
    if ((void *)*puVar7 != (void *)0x0) {
      operator_delete((void *)*puVar7);
    }
  }
  *(undefined8 **)(this + 0x50) = puVar8;
  return;
}

/* address=00a69180
   symbol=CSoundBank::addSample */

/* WARNING: Removing unreachable block (ram,0x00a69562) */
/* CSoundBank::addSample(int, std::wstring const&, bool, bool, float, float, float, float, int) */

long __thiscall
CSoundBank::addSample
          (CSoundBank *this,int param_1,wstring_conflict *param_2,bool param_3,bool param_4,
          float param_5,float param_6,float param_7,float param_8,int param_9)

{
  int *piVar1;
  undefined8 *puVar2;
  vector<CSoundInstance*,std::allocator<CSoundInstance*>> *pvVar3;
  int iVar4;
  undefined8 *puVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  undefined8 *puVar11;
  float local_88;
  float local_84;
  void *local_78;
  undefined8 local_70;
  undefined8 local_68;
  long local_58 [2];
  long local_48;
  undefined4 local_40 [4];

  local_48 = 0;
  if (-1 < param_1) {
    this[200] = (CSoundBank)param_3;
    std::wstring::wstring((wstring_conflict *)local_58,param_2);
                    /* try { // try from 00a6920d to 00a69211 has its CatchHandler @ 00a69543 */
    local_48 = CSoundManager::createSound
                         (param_6,param_7,*(undefined8 *)(this + 0x10),(wstring_conflict *)local_58,
                          4 - (uint)!param_3,param_4);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if (local_48 != 0) {
      puVar5 = *(undefined8 **)(this + 0x50);
      lVar7 = *(long *)(this + 0x48);
      lVar8 = (long)puVar5 - lVar7 >> 3;
      uVar9 = lVar8 * -0x5555555555555555;
      if ((uint)uVar9 <= (uint)param_1) {
        local_78 = (void *)0x0;
        local_70 = 0;
        local_68 = 0;
        uVar10 = (ulong)(param_1 + 1);
        if (uVar10 < uVar9) {
          puVar2 = (undefined8 *)(lVar7 + uVar10 * 0x18);
          for (puVar11 = puVar2; puVar5 != puVar11; puVar11 = puVar11 + 3) {
            if ((void *)*puVar11 != (void *)0x0) {
              operator_delete((void *)*puVar11);
            }
          }
          *(undefined8 **)(this + 0x50) = puVar2;
        }
        else {
                    /* try { // try from 00a694e5 to 00a694e9 has its CatchHandler @ 00a69529 */
          std::
          vector<std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>,std::allocator<std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>>>
          ::_M_fill_insert((vector<std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>,std::allocator<std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>>>
                            *)(this + 0x48),puVar5,uVar10 + lVar8 * 0x5555555555555555,&local_78);
        }
        if (local_78 != (void *)0x0) {
          operator_delete(local_78);
        }
        local_40[0] = 0;
        uVar9 = *(long *)(this + 0x68) - *(long *)(this + 0x60) >> 2;
        if (uVar10 < uVar9) {
          *(ulong *)(this + 0x68) = *(long *)(this + 0x60) + uVar10 * 4;
        }
        else {
          std::vector<float,std::allocator<float>>::_M_fill_insert
                    ((vector<float,std::allocator<float>> *)(this + 0x60),*(long *)(this + 0x68),
                     uVar10 - uVar9,local_40);
        }
        local_40[0] = 0;
        uVar9 = *(long *)(this + 0x80) - *(long *)(this + 0x78) >> 2;
        if (uVar10 < uVar9) {
          *(ulong *)(this + 0x80) = *(long *)(this + 0x78) + uVar10 * 4;
        }
        else {
          std::vector<float,std::allocator<float>>::_M_fill_insert
                    ((vector<float,std::allocator<float>> *)(this + 0x78),*(long *)(this + 0x80),
                     uVar10 - uVar9,local_40);
        }
        local_40[0] = 0;
        uVar9 = *(long *)(this + 0x98) - *(long *)(this + 0x90) >> 2;
        if (uVar10 < uVar9) {
          *(ulong *)(this + 0x98) = *(long *)(this + 0x90) + uVar10 * 4;
          lVar7 = *(long *)(this + 0x48);
        }
        else {
          std::vector<int,std::allocator<int>>::_M_fill_insert
                    ((vector<int,std::allocator<int>> *)(this + 0x90),*(long *)(this + 0x98),
                     uVar10 - uVar9,local_40);
          lVar7 = *(long *)(this + 0x48);
        }
      }
      lVar8 = (long)param_1;
      pvVar3 = (vector<CSoundInstance*,std::allocator<CSoundInstance*>> *)(lVar7 + lVar8 * 0x18);
      plVar6 = *(long **)(pvVar3 + 8);
      if (plVar6 == *(long **)(pvVar3 + 0x10)) {
        std::vector<CSoundInstance*,std::allocator<CSoundInstance*>>::_M_insert_aux
                  (pvVar3,plVar6,&local_48);
      }
      else {
        lVar7 = 0;
        if (plVar6 != (long *)0x0) {
          *plVar6 = local_48;
          lVar7 = *(long *)(pvVar3 + 8);
        }
        *(long *)(pvVar3 + 8) = lVar7 + 8;
      }
      local_84 = param_8;
      if ((param_8 == 0.0) && (!NAN(param_8))) {
        local_84 = *(float *)(this + 0xb0);
      }
      *(float *)(*(long *)(this + 0x60) + lVar8 * 4) = local_84;
      local_88 = param_5;
      if ((param_5 == 0.0) && (!NAN(param_5))) {
        local_88 = *(float *)(this + 0xac);
      }
      *(float *)(*(long *)(this + 0x78) + lVar8 * 4) = local_88;
      *(int *)(*(long *)(this + 0x90) + lVar8 * 4) = param_9;
    }
  }
  return local_48;
}

/* address=00a69570
   symbol=CSoundBank::addSample */

/* CSoundBank::addSample(int, long long) */

void __thiscall CSoundBank::addSample(CSoundBank *this,int param_1,longlong param_2)

{
  long lVar1;
  long lVar2;
  undefined8 uVar3;
  wstring_conflict *pwVar4;
  uint uVar5;
  string local_58 [16];
  char *local_48;
  allocator local_39 [9];

  if (-1 < param_1) {
    lVar1 = CMasterResourceManager::getSingleton();
    if (*(CSoundBankDataInformation **)(lVar1 + 0x100) != (CSoundBankDataInformation *)0x0) {
      lVar1 = CSoundBankDataInformation::getSoundDataObjectByGuid
                        (*(CSoundBankDataInformation **)(lVar1 + 0x100),param_2);
      if (lVar1 != 0) {
        if (*(long *)(lVar1 + 0x58) == 0) {
                    /* try { // try from 00a6968a to 00a6968e has its CatchHandler @ 00a696e7 */
          STRINGS::GetValueAsString((longlong)&local_48);
                    /* try { // try from 00a696a1 to 00a696a5 has its CatchHandler @ 00a69707 */
          std::string::string(local_58,local_48,local_39);
                    /* try { // try from 00a696ad to 00a696b1 has its CatchHandler @ 00a696f2 */
          uVar3 = CSoundManager::createSoundGroup(*(CSoundManager **)(this + 0x10),local_58);
          *(undefined8 *)(lVar1 + 0x58) = uVar3;
                    /* try { // try from 00a696b9 to 00a696bd has its CatchHandler @ 00a69707 */
          std::string::~string(local_58);
                    /* try { // try from 00a696c1 to 00a696c5 has its CatchHandler @ 00a696e7 */
          std::string::~string((string *)&local_48);
          FMOD::SoundGroup::setMaxAudible((int)*(undefined8 *)(lVar1 + 0x58));
          FMOD::SoundGroup::setMaxAudibleBehavior(*(undefined8 *)(lVar1 + 0x58),1);
        }
        if (*(char *)(lVar1 + 0x2c) != '\0') {
          this[200] = (CSoundBank)0x1;
        }
        if (*(int *)(lVar1 + 0x48) != 0) {
          uVar5 = 0;
          do {
            if (uVar5 < *(uint *)(lVar1 + 0x4c)) {
              pwVar4 = (wstring_conflict *)((ulong)uVar5 * 8 + *(long *)(lVar1 + 0x40));
            }
            else {
              pwVar4 = *(wstring_conflict **)(lVar1 + 0x40);
            }
            lVar2 = addSample(this,param_1,pwVar4,*(bool *)(lVar1 + 0x2c),false,
                              *(float *)(lVar1 + 0x28),*(float *)(lVar1 + 0x34),
                              *(float *)(lVar1 + 0x30),*(float *)(lVar1 + 0x38),
                              *(int *)(lVar1 + 0x3c));
            if (lVar2 != 0) {
              FMOD::Sound::getSoundGroup(*(SoundGroup ***)(lVar2 + 0x40));
              if (*(long *)(lVar1 + 0x58) != 0) {
                FMOD::Sound::setSoundGroup(*(SoundGroup **)(lVar2 + 0x40));
              }
              *(long *)(lVar2 + 0x58) = lVar1;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < *(uint *)(lVar1 + 0x48));
        }
      }
    }
  }
  return;
}

/* address=00a69710
   symbol=CSoundBank::~CSoundBank */

/* CSoundBank::~CSoundBank() */

void __thiscall CSoundBank::~CSoundBank(CSoundBank *this)

{
  undefined8 *puVar1;
  undefined8 *puVar2;

  *(undefined ***)this = &PTR__CSoundBank_00fe1670;
  if (this[200] != (CSoundBank)0x0) {
                    /* try { // try from 00a6972d to 00a69739 has its CatchHandler @ 00a697db */
    stop(this);
  }
  clear(this);
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x90));
  }
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x78));
  }
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x60));
  }
  puVar1 = *(undefined8 **)(this + 0x50);
  for (puVar2 = *(undefined8 **)(this + 0x48); puVar1 != puVar2; puVar2 = puVar2 + 3) {
    if ((void *)*puVar2 != (void *)0x0) {
      operator_delete((void *)*puVar2);
    }
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x48));
  }
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
    *(undefined8 *)(this + 0x30) = 0;
  }
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00a69880
   symbol=CSoundBank::~CSoundBank */

/* CSoundBank::~CSoundBank() */

void __thiscall CSoundBank::~CSoundBank(CSoundBank *this)

{
  ~CSoundBank(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a698a0
   symbol=CSoundBank::playSample */

/* CSoundBank::playSample(int, Ogre::SceneNode*, float, float, bool) */

int __thiscall
CSoundBank::playSample
          (CSoundBank *this,int param_1,SceneNode *param_2,float param_3,float param_4,bool param_5)

{
  CSoundInstance *pCVar1;
  int iVar2;
  uint uVar3;
  Vector3 *pVVar4;
  long lVar5;
  long lVar6;
  float fVar7;
  float fVar8;

  if ((((*(char *)(*(long *)(this + 0x10) + 0x6a9) == '\0') ||
       (*(char *)(*(long *)(this + 0x10) + 0x6a8) == '\0')) ||
      (lVar5 = *(long *)(this + 0x48),
      (int)(*(long *)(this + 0x50) - lVar5 >> 3) * -0x55555555 <= param_1)) || (param_1 < 0)) {
    iVar2 = -1;
  }
  else {
    lVar6 = (long)param_1;
    if (-1 < *(int *)(*(long *)(this + 0x90) + lVar6 * 4)) {
      iVar2 = UTILITIES::randomIntegerBetweenVolatile(1,100);
      if (*(int *)(*(long *)(this + 0x90) + lVar6 * 4) <= iVar2) {
        return -1;
      }
      lVar5 = *(long *)(this + 0x48);
    }
    if ((param_3 != 0.0) || (NAN(param_3))) {
      fVar8 = *(float *)(this + 0xac) * param_3;
    }
    else {
      fVar8 = *(float *)(*(long *)(this + 0x78) + lVar6 * 4);
    }
    if ((param_4 == 0.0) && (!NAN(param_4))) {
      param_4 = *(float *)(*(long *)(this + 0x60) + lVar6 * 4);
    }
    iVar2 = -1;
    lVar6 = (ulong)(uint)param_1 * 0x18;
    if ((int)((ulong)(((long *)(lVar5 + lVar6))[1] - *(long *)(lVar5 + lVar6)) >> 3) != 0) {
      fVar7 = DAT_00fa47fc;
      if (param_2 != (SceneNode *)0x0) {
        pVVar4 = (Vector3 *)(**(code **)(*(long *)param_2 + 0x200))(param_2);
        fVar7 = (float)configureVolumeScale(this,param_4,pVVar4);
      }
      *(float *)(this + 0xc4) = fVar8 * fVar7;
      uVar3 = UTILITIES::randomIntegerBetweenVolatile
                        (0,(int)(((long *)(*(long *)(this + 0x48) + lVar6))[1] -
                                 *(long *)(*(long *)(this + 0x48) + lVar6) >> 3) + -1);
      pCVar1 = *(CSoundInstance **)(*(long *)(*(long *)(this + 0x48) + lVar6) + (ulong)uVar3 * 8);
      if (this[200] == (CSoundBank)0x0) {
        *(undefined4 *)(this + 0x20) = 0;
        *(undefined4 *)(this + 0x24) = 0;
        if (*(void **)(this + 0x18) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x18));
        }
        *(undefined8 *)(this + 0x18) = 0;
        *(undefined4 *)(this + 0x38) = 0;
        *(undefined4 *)(this + 0x3c) = 0;
        if (*(void **)(this + 0x30) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x30));
        }
        *(undefined8 *)(this + 0x30) = 0;
      }
      else {
        stop(this);
      }
      if (this[200] == (CSoundBank)0x0) {
        param_2 = (SceneNode *)0x0;
      }
      iVar2 = CSoundManager::playSound
                        (*(CSoundManager **)(this + 0x10),pCVar1,param_2,-1,*(float *)(this + 0xc4))
      ;
      if ((!param_5) && (iVar2 != -1)) {
        TArrayList<int>::add((TArrayList<int> *)(this + 0x18),iVar2);
        TArrayList<int>::add((TArrayList<int> *)(this + 0x30),param_1);
      }
      this[0xa8] = (CSoundBank)0x1;
    }
  }
  return iVar2;
}

/* address=00a69b60
   symbol=CSoundBank::update */

/* CSoundBank::update(float, Ogre::SceneNode*) */

float CSoundBank::update(float param_1,SceneNode *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  undefined8 uVar6;
  char cVar7;
  uint uVar8;
  undefined8 *puVar9;
  int *piVar10;
  uint uVar11;
  SceneNode *in_RSI;
  float extraout_XMM0_Da;
  float fVar12;
  undefined8 local_28;
  float local_20;

  if (*(int *)(param_2 + 0x20) != 0) {
    uVar11 = 0;
    do {
      while( true ) {
        param_1 = (float)CSoundManager::incrementSoundBank(*(CSoundManager **)(param_2 + 0x10));
        if (uVar11 < *(uint *)(param_2 + 0x24)) break;
        if (**(int **)(param_2 + 0x18) != -1) goto LAB_00a69b89;
LAB_00a69bd4:
        if (param_2[200] != (SceneNode)0x0) {
          if (uVar11 < *(uint *)(param_2 + 0x24)) {
            piVar10 = (int *)((ulong)uVar11 * 4 + *(long *)(param_2 + 0x18));
          }
          else {
            piVar10 = *(int **)(param_2 + 0x18);
          }
          param_1 = (float)CSoundManager::stopSound(*(CSoundManager **)(param_2 + 0x10),*piVar10);
        }
        if (uVar11 < *(uint *)(param_2 + 0x20)) {
          uVar8 = *(uint *)(param_2 + 0x20) - 1;
          *(uint *)(param_2 + 0x20) = uVar8;
          *(undefined4 *)(*(long *)(param_2 + 0x18) + (ulong)uVar11 * 4) =
               *(undefined4 *)(*(long *)(param_2 + 0x18) + (ulong)uVar8 * 4);
        }
        if (uVar11 < *(uint *)(param_2 + 0x38)) {
          uVar8 = *(uint *)(param_2 + 0x38) - 1;
          *(uint *)(param_2 + 0x38) = uVar8;
          *(undefined4 *)(*(long *)(param_2 + 0x30) + (ulong)uVar11 * 4) =
               *(undefined4 *)(*(long *)(param_2 + 0x30) + (ulong)uVar8 * 4);
        }
        uVar11 = 1;
        if (*(uint *)(param_2 + 0x20) < 2) goto LAB_00a69c41;
      }
      if (*(int *)((ulong)uVar11 * 4 + *(long *)(param_2 + 0x18)) == -1) goto LAB_00a69bd4;
LAB_00a69b89:
      if (uVar11 < *(uint *)(param_2 + 0x24)) {
        piVar10 = (int *)((ulong)uVar11 * 4 + *(long *)(param_2 + 0x18));
      }
      else {
        piVar10 = *(int **)(param_2 + 0x18);
      }
      cVar7 = CSoundManager::isChannelPlaying(*(CSoundManager **)(param_2 + 0x10),*piVar10);
      param_1 = extraout_XMM0_Da;
      if (cVar7 == '\0') goto LAB_00a69bd4;
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(param_2 + 0x20));
  }
LAB_00a69c41:
  if ((in_RSI != (SceneNode *)0x0) && (param_2[200] != (SceneNode)0x0)) {
    lVar5 = *(long *)(param_2 + 0x10);
    fVar1 = *(float *)(lVar5 + 0x24);
    fVar2 = *(float *)(lVar5 + 0x28);
    fVar3 = *(float *)(lVar5 + 0x20);
    puVar9 = (undefined8 *)(**(code **)(*(long *)in_RSI + 0x200))();
    uVar6 = *puVar9;
    local_20 = *(float *)(puVar9 + 1);
    if ((fVar3 == 0.0) && ((fVar2 == 0.0 && (!NAN(fVar2))))) {
      local_28._0_4_ = (float)uVar6;
      if ((fVar3 == (float)local_28) && (!NAN(fVar3) && !NAN((float)local_28))) {
        local_28._4_4_ = (float)((ulong)uVar6 >> 0x20);
        if (((fVar1 == local_28._4_4_) && (!NAN(fVar1) && !NAN(local_28._4_4_))) &&
           (fVar2 == local_20)) {
          return fVar2;
        }
      }
    }
    fVar4 = *(float *)(param_2 + 0xac);
    local_28 = uVar6;
    fVar12 = (float)configureVolumeScale
                              ((CSoundBank *)param_2,*(float *)(param_2 + 0xb0),(Vector3 *)&local_28
                              );
    fVar12 = fVar12 * fVar4;
    if ((0.0 < fVar12) || (*(int *)(param_2 + 0x20) == 0)) {
      if ((fVar12 <= DAT_00fa4828) ||
         ((*(int *)(param_2 + 0x20) != 0 || (param_2[200] == (SceneNode)0x0)))) {
        if (param_2[0xa8] == (SceneNode)0x0) {
          if ((fVar3 == *(float *)(param_2 + 0xb8)) &&
             (!NAN(fVar3) && !NAN(*(float *)(param_2 + 0xb8)))) {
            if ((fVar1 == *(float *)(param_2 + 0xbc)) &&
               ((!NAN(fVar1) && !NAN(*(float *)(param_2 + 0xbc)) &&
                (fVar2 == *(float *)(param_2 + 0xc0))))) {
              return fVar2;
            }
          }
        }
      }
      else {
        playSample((CSoundBank *)param_2,0,in_RSI,0.0,*(float *)(param_2 + 0xb0),false);
        param_2[0xa8] = (SceneNode)0x1;
      }
      *(float *)(param_2 + 0xb8) = fVar3;
      uVar11 = 0;
      param_2[0xa8] = (SceneNode)0x0;
      *(float *)(param_2 + 0xbc) = fVar1;
      *(float *)(param_2 + 0xc0) = fVar2;
      *(float *)(param_2 + 0xc4) = fVar12;
      param_1 = fVar12;
      if (*(int *)(param_2 + 0x20) != 0) {
        do {
          if (uVar11 < *(uint *)(param_2 + 0x24)) {
            piVar10 = (int *)((ulong)uVar11 * 4 + *(long *)(param_2 + 0x18));
          }
          else {
            piVar10 = *(int **)(param_2 + 0x18);
          }
          uVar11 = uVar11 + 1;
          param_1 = (float)CSoundManager::setSoundVolume
                                     (*(CSoundManager **)(param_2 + 0x10),*piVar10,fVar12);
        } while (uVar11 < *(uint *)(param_2 + 0x20));
      }
    }
    else {
      *(undefined4 *)(param_2 + 0xc4) = 0;
      param_1 = (float)stop((CSoundBank *)param_2);
    }
  }
  return param_1;
}

/* export-summary functions=17 failures=0 */
