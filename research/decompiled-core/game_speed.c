/* Targeted Ghidra class export.
   namespace=CGameSpeed
   Treat pseudocode as navigation evidence. */


/* address=00c77c20
   symbol=CGameSpeed::getSingleton */

/* CGameSpeed::getSingleton() */

undefined8 CGameSpeed::getSingleton(void)

{
  return g_pGameSpeed;
}



/* address=00c77c30
   symbol=CGameSpeed::getGameSpeed */

/* CGameSpeed::getGameSpeed() */

undefined4 CGameSpeed::getGameSpeed(void)

{
  if (g_pGameSpeed != 0) {
    return *(undefined4 *)(g_pGameSpeed + 0x10);
  }
  return DAT_00fa47fc;
}



/* address=00c77c60
   symbol=CGameSpeed::_GLOBAL__I_CGameSpeed */

/* CGameSpeed::CGameSpeed(std::basic_string<wchar_t, std::char_traits<wchar_t>,
   std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>,
   std::allocator<wchar_t> >) */

void CGameSpeed::_GLOBAL__I_CGameSpeed(void)

{
  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  return;
}



/* address=00c77d10
   symbol=CGameSpeed::calculateGameSpeed */

/* CGameSpeed::calculateGameSpeed(float) */

void CGameSpeed::calculateGameSpeed(float param_1)

{
  float fVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  float fVar7;
  float fVar8;
  float local_24;

  lVar4 = g_pGameSpeed;
  if (g_pGameSpeed != 0) {
    *(undefined4 *)(g_pGameSpeed + 0x10) = 0x3f800000;
    local_24 = 1.0;
    uVar6 = 0;
    fVar8 = 1.0;
    if (*(int *)(lVar4 + 0x30) != 0) {
      do {
        uVar5 = (uint)uVar6;
        if (uVar5 < *(uint *)(lVar4 + 0x34)) {
          plVar3 = (long *)(uVar6 * 8 + *(long *)(lVar4 + 0x28));
        }
        else {
          plVar3 = *(long **)(lVar4 + 0x28);
        }
        plVar3 = (long *)*plVar3;
        fVar7 = param_1 + *(float *)(plVar3 + 3);
        fVar8 = *(float *)((long)plVar3 + 0x14);
        *(float *)(plVar3 + 3) = fVar7;
        if (fVar7 < fVar8) {
          local_24 = DAT_00fa47fc + local_24;
          if ((int)plVar3[2] == 0) {
            fVar1 = *(float *)(lVar4 + 0x10);
            fVar8 = (float)CGraph::getValue((CGraph *)plVar3[4],fVar7 / fVar8,0);
            fVar8 = DAT_00fa47fc - fVar8 * *(float *)(plVar3 + 5);
            if (fVar8 <= 0.0) {
              fVar8 = 0.0;
            }
            *(float *)(lVar4 + 0x10) = fVar8 + fVar1;
          }
          else if ((int)plVar3[2] == 1) {
            fVar1 = *(float *)(lVar4 + 0x10);
            fVar8 = (float)CGraph::getValue((CGraph *)plVar3[4],fVar7 / fVar8,0);
            fVar8 = fVar8 * *(float *)(plVar3 + 5);
            if (fVar8 <= 0.0) {
              fVar8 = 0.0;
            }
            *(float *)(lVar4 + 0x10) = fVar8 + DAT_00fa47fc + fVar1;
          }
        }
        else {
          if (uVar5 < *(uint *)(lVar4 + 0x30)) {
            uVar2 = *(uint *)(lVar4 + 0x30) - 1;
            *(uint *)(lVar4 + 0x30) = uVar2;
            *(undefined8 *)(*(long *)(lVar4 + 0x28) + uVar6 * 8) =
                 *(undefined8 *)(*(long *)(lVar4 + 0x28) + (ulong)uVar2 * 8);
          }
          (**(code **)(*plVar3 + 8))(plVar3);
        }
        uVar6 = (ulong)(uVar5 + 1);
        lVar4 = g_pGameSpeed;
      } while (uVar5 + 1 < *(uint *)(g_pGameSpeed + 0x30));
      fVar8 = *(float *)(g_pGameSpeed + 0x10);
    }
    *(float *)(lVar4 + 0x10) = fVar8 / local_24;
  }
  return;
}



/* address=00c77ea0
   symbol=CGameSpeed::addSpeedModifier */

/* CGameSpeed::addSpeedModifier(EGAMESPEED_TYPE, float, float) */

void CGameSpeed::addSpeedModifier(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  CRunicCore *this;
  void *pvVar2;
  long lVar3;
  ulong uVar4;
  CRunicCore *pCVar5;
  uint uVar6;
  byte bVar7;

  bVar7 = 0;
  if (g_pGameSpeed != 0) {
    this = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
    pCVar5 = this;
    for (lVar3 = 5; lVar3 != 0; lVar3 = lVar3 + -1) {
      *(undefined8 *)pCVar5 = 0;
      pCVar5 = pCVar5 + (ulong)bVar7 * -0x10 + 8;
    }
    *(undefined4 *)pCVar5 = 0;
                    /* try { // try from 00c77efd to 00c77f01 has its CatchHandler @ 00c78017 */
    CRunicCore::CRunicCore(this);
    *(undefined ***)this = &PTR__CSpeedInstance_00ff3e90;
    *(int *)(this + 0x10) = param_3;
    *(undefined4 *)(this + 0x18) = 0;
    *(undefined4 *)(this + 0x14) = param_1;
    *(undefined4 *)(this + 0x28) = param_2;
    lVar3 = g_pGameSpeed;
    if (param_3 == 0) {
      *(undefined8 *)(this + 0x20) = *(undefined8 *)(g_pGameSpeed + 0x18);
    }
    else if (param_3 == 1) {
      *(undefined8 *)(this + 0x20) = *(undefined8 *)(g_pGameSpeed + 0x20);
    }
    if (*(uint *)(lVar3 + 0x34) <= *(uint *)(lVar3 + 0x30)) {
      if (*(long *)(lVar3 + 0x28) == 0) {
        *(uint *)(lVar3 + 0x34) = *(uint *)(lVar3 + 0x38);
        pvVar2 = operator_new__((ulong)*(uint *)(lVar3 + 0x38) << 3);
        *(void **)(lVar3 + 0x28) = pvVar2;
      }
      else {
        uVar6 = *(uint *)(lVar3 + 0x34) + *(int *)(lVar3 + 0x38);
        pvVar2 = operator_new__((ulong)uVar6 << 3);
        if (*(int *)(lVar3 + 0x34) != 0) {
          uVar1 = 0;
          do {
            uVar4 = (ulong)uVar1;
            uVar1 = uVar1 + 1;
            *(undefined8 *)((long)pvVar2 + uVar4 * 8) =
                 *(undefined8 *)(*(long *)(lVar3 + 0x28) + uVar4 * 8);
          } while (uVar1 < *(uint *)(lVar3 + 0x34));
        }
        if (*(void **)(lVar3 + 0x28) != (void *)0x0) {
          operator_delete__(*(void **)(lVar3 + 0x28));
        }
        *(void **)(lVar3 + 0x28) = pvVar2;
        *(uint *)(lVar3 + 0x34) = uVar6;
      }
    }
    *(CRunicCore **)(*(long *)(lVar3 + 0x28) + (ulong)*(uint *)(lVar3 + 0x30) * 8) = this;
    *(int *)(lVar3 + 0x30) = *(int *)(lVar3 + 0x30) + 1;
  }
  return;
}



/* address=00c78030
   symbol=CGameSpeed::clear */

/* CGameSpeed::clear() */

void CGameSpeed::clear(void)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  uint uVar4;

  lVar2 = g_pGameSpeed;
  if (g_pGameSpeed != 0) {
    plVar1 = (long *)(g_pGameSpeed + 0x28);
    if (*(int *)(g_pGameSpeed + 0x30) != 0) {
      uVar4 = 0;
      do {
        plVar3 = (long *)((ulong)uVar4 * 8 + *plVar1);
        if ((long *)*plVar3 != (long *)0x0) {
          (**(code **)(*(long *)*plVar3 + 8))();
          plVar3 = (long *)((ulong)uVar4 * 8 + *plVar1);
        }
        *plVar3 = 0;
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(lVar2 + 0x30));
    }
    *(undefined4 *)(lVar2 + 0x30) = 0;
    *(undefined4 *)(lVar2 + 0x34) = 0;
    if (*(void **)(lVar2 + 0x28) != (void *)0x0) {
      operator_delete__(*(void **)(lVar2 + 0x28));
    }
    *(undefined8 *)(lVar2 + 0x28) = 0;
  }
  return;
}



/* address=00c780c0
   symbol=CGameSpeed::CGameSpeed */

/* CGameSpeed::CGameSpeed(std::wstring, std::wstring) */

void __thiscall
CGameSpeed::CGameSpeed(CGameSpeed *this,wstring_conflict *param_2,wstring_conflict *param_3)

{
  CGraph *pCVar1;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CGameSpeed_00ff3e30;
  *(undefined4 *)(this + 0x10) = 0x3f800000;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 10;
  if (g_pGameSpeed == (CGameSpeed *)0x0) {
    g_pGameSpeed = this;
                    /* try { // try from 00c7814a to 00c7814e has its CatchHandler @ 00c78185 */
    pCVar1 = (CGraph *)Ogre::NedAllocImpl::allocBytes(0x58,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c78158 to 00c7815c has its CatchHandler @ 00c781bb */
    CGraph::CGraph(pCVar1,param_2);
    *(CGraph **)(this + 0x18) = pCVar1;
                    /* try { // try from 00c7816c to 00c78170 has its CatchHandler @ 00c78185 */
    pCVar1 = (CGraph *)Ogre::NedAllocImpl::allocBytes(0x58,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c7817a to 00c7817e has its CatchHandler @ 00c781ae */
    CGraph::CGraph(pCVar1,param_3);
    *(CGraph **)(this + 0x20) = pCVar1;
  }
  return;
}



/* address=00c781d0
   symbol=CGameSpeed::~CGameSpeed */

/* CGameSpeed::~CGameSpeed() */

void __thiscall CGameSpeed::~CGameSpeed(CGameSpeed *this)

{
  long *plVar1;
  uint uVar2;

  *(undefined ***)this = &PTR__CGameSpeed_00ff3e30;
  if (*(long **)(this + 0x18) != (long *)0x0) {
                    /* try { // try from 00c781f0 to 00c7823b has its CatchHandler @ 00c78295 */
    (**(code **)(**(long **)(this + 0x18) + 8))();
    *(undefined8 *)(this + 0x18) = 0;
  }
  if (*(long **)(this + 0x20) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x20) + 8))();
    *(undefined8 *)(this + 0x20) = 0;
  }
  if (*(int *)(this + 0x30) != 0) {
    uVar2 = 0;
    do {
      plVar1 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0x28));
      if ((long *)*plVar1 != (long *)0x0) {
        (**(code **)(*(long *)*plVar1 + 8))();
        plVar1 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0x28));
      }
      *plVar1 = 0;
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x30));
  }
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x28));
  }
  *(undefined8 *)(this + 0x28) = 0;
  g_pGameSpeed = 0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00c782c0
   symbol=CGameSpeed::~CGameSpeed */

/* CGameSpeed::~CGameSpeed() */

void __thiscall CGameSpeed::~CGameSpeed(CGameSpeed *this)

{
  ~CGameSpeed(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00c782e0
   symbol=CGameSpeed::CSpeedInstance::~CSpeedInstance */

/* CGameSpeed::CSpeedInstance::~CSpeedInstance() */

void __thiscall CGameSpeed::CSpeedInstance::~CSpeedInstance(CSpeedInstance *this)

{
  *(undefined ***)this = &PTR__CSpeedInstance_00ff3e90;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00c782f0
   symbol=CGameSpeed::CSpeedInstance::~CSpeedInstance */

/* CGameSpeed::CSpeedInstance::~CSpeedInstance() */

void __thiscall CGameSpeed::CSpeedInstance::~CSpeedInstance(CSpeedInstance *this)

{
  *(undefined ***)this = &PTR__CSpeedInstance_00ff3e90;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=11 failures=0 */
