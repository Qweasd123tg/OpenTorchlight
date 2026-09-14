/* Targeted Ghidra class export.
   namespace=CMasterResourceManager
   Treat pseudocode as navigation evidence. */


/* address=00a54460
   symbol=CMasterResourceManager::destroyStash */

/* CMasterResourceManager::destroyStash() */

void __thiscall CMasterResourceManager::destroyStash(CMasterResourceManager *this)

{
  if (*(long **)(this + 0x178) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x178) + 8))();
    *(undefined8 *)(this + 0x178) = 0;
  }
  *(undefined8 *)(this + 0x178) = 0;
  return;
}

/* address=00a54490
   symbol=CMasterResourceManager::getSingleton */

/* CMasterResourceManager::getSingleton() */

undefined8 CMasterResourceManager::getSingleton(void)

{
  return m_pMasterResourceManager;
}

/* address=00a544a0
   symbol=CMasterResourceManager::getCollisionModel */

/* CMasterResourceManager::getCollisionModel(CCollisionModel*) */

long __thiscall
CMasterResourceManager::getCollisionModel(CMasterResourceManager *this,CCollisionModel *param_1)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;

  plVar1 = *(long **)(this + 0x120);
  uVar3 = *(long *)(this + 0x128) - (long)plVar1 >> 3;
  if (uVar3 == 0) {
LAB_00a544e4:
    lVar2 = 0;
  }
  else {
    uVar4 = 0;
    if (*(CCollisionModel **)(*plVar1 + 0x10) == param_1) {
      return *plVar1;
    }
    do {
      uVar4 = uVar4 + 1;
      if (uVar3 <= uVar4) goto LAB_00a544e4;
      lVar2 = plVar1[uVar4];
    } while (*(CCollisionModel **)(lVar2 + 0x10) != param_1);
  }
  return lVar2;
}

/* address=00a544f0
   symbol=CMasterResourceManager::removeCollisionModel */

/* CMasterResourceManager::removeCollisionModel(CCollisionModel*) */

void __thiscall
CMasterResourceManager::removeCollisionModel(CMasterResourceManager *this,CCollisionModel *param_1)

{
  long lVar1;

  lVar1 = getCollisionModel(this,param_1);
  if (lVar1 != 0) {
    *(int *)(lVar1 + 0x18) = *(int *)(lVar1 + 0x18) + -1;
  }
  return;
}

/* address=00a54500
   symbol=CMasterResourceManager::getBatchModel */

/* CMasterResourceManager::getBatchModel(CGenericModel*) */

long __thiscall
CMasterResourceManager::getBatchModel(CMasterResourceManager *this,CGenericModel *param_1)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  uint uVar4;

  plVar1 = *(long **)(this + 0x138);
  uVar3 = *(long *)(this + 0x140) - (long)plVar1 >> 3;
  if (uVar3 == 0) {
LAB_00a54544:
    lVar2 = 0;
  }
  else {
    uVar4 = 0;
    if (*(CGenericModel **)(*plVar1 + 0x10) == param_1) {
      return *plVar1;
    }
    do {
      uVar4 = uVar4 + 1;
      if (uVar3 <= uVar4) goto LAB_00a54544;
      lVar2 = plVar1[uVar4];
    } while (*(CGenericModel **)(lVar2 + 0x10) != param_1);
  }
  return lVar2;
}

/* address=00a54550
   symbol=CMasterResourceManager::removeBatchModel */

/* CMasterResourceManager::removeBatchModel(CGenericModel*) */

void __thiscall
CMasterResourceManager::removeBatchModel(CMasterResourceManager *this,CGenericModel *param_1)

{
  long lVar1;

  lVar1 = getBatchModel(this,param_1);
  if (lVar1 != 0) {
    *(int *)(lVar1 + 0x18) = *(int *)(lVar1 + 0x18) + -1;
  }
  return;
}

/* address=00a54560
   symbol=CMasterResourceManager::getAnimationSet */

/* CMasterResourceManager::getAnimationSet(CAnimationSet*) */

CAnimationSet * __thiscall
CMasterResourceManager::getAnimationSet(CMasterResourceManager *this,CAnimationSet *param_1)

{
  long *plVar1;
  CAnimationSet *pCVar2;
  ulong uVar3;
  uint uVar4;

  plVar1 = *(long **)(this + 0x150);
  uVar3 = *(long *)(this + 0x158) - (long)plVar1 >> 3;
  if (uVar3 == 0) {
LAB_00a545a3:
    pCVar2 = (CAnimationSet *)0x0;
  }
  else {
    uVar4 = 0;
    if ((CAnimationSet *)*plVar1 == param_1) {
      return (CAnimationSet *)*plVar1;
    }
    do {
      uVar4 = uVar4 + 1;
      if (uVar3 <= uVar4) goto LAB_00a545a3;
      pCVar2 = (CAnimationSet *)plVar1[uVar4];
    } while (pCVar2 != param_1);
  }
  return pCVar2;
}

/* address=00a545b0
   symbol=CMasterResourceManager::removeAnimationSet */

/* CMasterResourceManager::removeAnimationSet(CAnimationSet*) */

void __thiscall
CMasterResourceManager::removeAnimationSet(CMasterResourceManager *this,CAnimationSet *param_1)

{
  long lVar1;

  lVar1 = getAnimationSet(this,param_1);
  if (lVar1 != 0) {
    *(int *)(lVar1 + 0x10) = *(int *)(lVar1 + 0x10) + -1;
  }
  return;
}

/* address=00a545c0
   symbol=CMasterResourceManager::removeUnused */

/* CMasterResourceManager::removeUnused() */

void __thiscall CMasterResourceManager::removeUnused(CMasterResourceManager *this)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  long lVar5;

  lVar3 = *(long *)(this + 0x128);
  lVar2 = *(long *)(this + 0x120);
  if (0 < (int)(lVar3 - lVar2 >> 3)) {
    iVar4 = 0;
    do {
      lVar5 = (long)iVar4;
      plVar1 = *(long **)(lVar2 + lVar5 * 8);
      if ((int)plVar1[3] == 0) {
        iVar4 = iVar4 + -1;
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x120) + lVar5 * 8) = 0;
        lVar3 = *(long *)(this + 0x120);
        *(undefined8 *)(lVar3 + lVar5 * 8) =
             *(undefined8 *)(lVar3 + -8 + (*(long *)(this + 0x128) - lVar3 >> 3) * 8);
        lVar2 = *(long *)(this + 0x120);
        lVar3 = *(long *)(this + 0x128) + -8;
        *(long *)(this + 0x128) = lVar3;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(lVar3 - lVar2 >> 3));
  }
  lVar3 = *(long *)(this + 0x140);
  lVar2 = *(long *)(this + 0x138);
  if (0 < (int)(lVar3 - lVar2 >> 3)) {
    iVar4 = 0;
    do {
      lVar5 = (long)iVar4;
      plVar1 = *(long **)(lVar2 + lVar5 * 8);
      if ((int)plVar1[3] == 0) {
        iVar4 = iVar4 + -1;
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x138) + lVar5 * 8) = 0;
        lVar3 = *(long *)(this + 0x138);
        *(undefined8 *)(lVar3 + lVar5 * 8) =
             *(undefined8 *)(lVar3 + -8 + (*(long *)(this + 0x140) - lVar3 >> 3) * 8);
        lVar2 = *(long *)(this + 0x138);
        lVar3 = *(long *)(this + 0x140) + -8;
        *(long *)(this + 0x140) = lVar3;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(lVar3 - lVar2 >> 3));
  }
  lVar3 = *(long *)(this + 0x158);
  lVar2 = *(long *)(this + 0x150);
  if (0 < (int)(lVar3 - lVar2 >> 3)) {
    iVar4 = 0;
    do {
      lVar5 = (long)iVar4;
      plVar1 = *(long **)(lVar2 + lVar5 * 8);
      if ((int)plVar1[2] == 0) {
        iVar4 = iVar4 + -1;
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x150) + lVar5 * 8) = 0;
        lVar3 = *(long *)(this + 0x150);
        *(undefined8 *)(lVar3 + lVar5 * 8) =
             *(undefined8 *)(lVar3 + -8 + (*(long *)(this + 0x158) - lVar3 >> 3) * 8);
        lVar2 = *(long *)(this + 0x150);
        lVar3 = *(long *)(this + 0x158) + -8;
        *(long *)(this + 0x158) = lVar3;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(lVar3 - lVar2 >> 3));
  }
  return;
}

/* address=00a54790
   symbol=CMasterResourceManager::removeAll */

/* CMasterResourceManager::removeAll() */

void __thiscall CMasterResourceManager::removeAll(CMasterResourceManager *this)

{
  long *plVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  uint uVar5;

  lVar2 = *(long *)(this + 0x128);
  lVar3 = *(long *)(this + 0x120);
  if (lVar2 - lVar3 >> 3 != 0) {
    uVar4 = 0;
    do {
      plVar1 = *(long **)(lVar3 + uVar4 * 8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x120) + uVar4 * 8) = 0;
        lVar3 = *(long *)(this + 0x120);
        lVar2 = *(long *)(this + 0x128);
      }
      uVar4 = (ulong)((int)uVar4 + 1);
    } while (uVar4 < (ulong)(lVar2 - lVar3 >> 3));
  }
  lVar2 = *(long *)(this + 0x140);
  *(long *)(this + 0x128) = lVar3;
  lVar3 = *(long *)(this + 0x138);
  if (lVar2 - lVar3 >> 3 != 0) {
    uVar4 = 0;
    do {
      plVar1 = *(long **)(lVar3 + uVar4 * 8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x138) + uVar4 * 8) = 0;
        lVar3 = *(long *)(this + 0x138);
        lVar2 = *(long *)(this + 0x140);
      }
      uVar4 = (ulong)((int)uVar4 + 1);
    } while (uVar4 < (ulong)(lVar2 - lVar3 >> 3));
  }
  lVar2 = *(long *)(this + 0x158);
  *(long *)(this + 0x140) = lVar3;
  lVar3 = *(long *)(this + 0x150);
  if (lVar2 - lVar3 >> 3 != 0) {
    uVar4 = 0;
    uVar5 = 0;
    do {
      plVar1 = *(long **)(lVar3 + uVar4 * 8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 8))();
        *(undefined8 *)(*(long *)(this + 0x150) + uVar4 * 8) = 0;
        lVar3 = *(long *)(this + 0x150);
        lVar2 = *(long *)(this + 0x158);
      }
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
    } while (uVar4 < (ulong)(lVar2 - lVar3 >> 3));
  }
  *(long *)(this + 0x158) = lVar3;
  return;
}

/* address=00a548f0
   symbol=CMasterResourceManager::reloadSoundBankData */

/* CMasterResourceManager::reloadSoundBankData() */

void __thiscall CMasterResourceManager::reloadSoundBankData(CMasterResourceManager *this)

{
  if ((*(CSoundManager **)(this + 0x98) != (CSoundManager *)0x0) && (*(long *)(this + 0x100) != 0))
  {
    CSoundManager::stopAllSounds(*(CSoundManager **)(this + 0x98));
    CSoundBankDataInformation::reload
              (*(CSoundBankDataInformation **)(this + 0x100),*(CResourceSettings **)(this + 0x68));
    return;
  }
  return;
}

/* address=00a54930
   symbol=CMasterResourceManager::getMaxFameLevel */

/* CMasterResourceManager::getMaxFameLevel() */

void __thiscall CMasterResourceManager::getMaxFameLevel(CMasterResourceManager *this)

{
  CGraph::getControlPoints(*(CGraph **)(this + 0x170));
  return;
}

/* address=00a54940
   symbol=CMasterResourceManager::fameGate */

/* CMasterResourceManager::fameGate(int) */

int __thiscall CMasterResourceManager::fameGate(CMasterResourceManager *this,int param_1)

{
  int iVar1;
  float fVar2;

  if (param_1 == 0) {
    return 0;
  }
  iVar1 = CGraph::getControlPoints(*(CGraph **)(this + 0x170));
  if (iVar1 < param_1) {
    param_1 = CGraph::getControlPoints(*(CGraph **)(this + 0x170));
  }
  fVar2 = (float)CGraph::getValue(*(CGraph **)(this + 0x170),(float)param_1,0);
  return (int)fVar2;
}

/* address=00a549c0
   symbol=CMasterResourceManager::getMaxLevel */

/* CMasterResourceManager::getMaxLevel() */

void __thiscall CMasterResourceManager::getMaxLevel(CMasterResourceManager *this)

{
  CGraph::getControlPoints(*(CGraph **)(this + 0x168));
  return;
}

/* address=00a549d0
   symbol=CMasterResourceManager::experienceGate */

/* CMasterResourceManager::experienceGate(int) */

int __thiscall CMasterResourceManager::experienceGate(CMasterResourceManager *this,int param_1)

{
  int iVar1;
  float fVar2;

  if (param_1 == 0) {
    return 0;
  }
  iVar1 = CGraph::getControlPoints(*(CGraph **)(this + 0x168));
  if (iVar1 < param_1) {
    param_1 = CGraph::getControlPoints(*(CGraph **)(this + 0x168));
  }
  fVar2 = (float)CGraph::getValue(*(CGraph **)(this + 0x168),(float)param_1,0);
  return (int)fVar2;
}

/* address=00a5c700
   symbol=CMasterResourceManager::getCollisionModel */

/* CMasterResourceManager::getCollisionModel(std::wstring) */

long __thiscall
CMasterResourceManager::getCollisionModel(CMasterResourceManager *this,undefined8 *param_2)

{
  long lVar1;
  wchar_t *__s2;
  size_t __n;
  long lVar2;
  wchar_t *__s1;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x120);
  uVar6 = *(long *)(this + 0x128) - lVar1 >> 3;
  if (uVar6 != 0) {
    __s2 = (wchar_t *)*param_2;
    uVar4 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      lVar2 = *(long *)(lVar1 + uVar4 * 8);
      __s1 = *(wchar_t **)(lVar2 + 0x20);
      if ((*(size_t *)(__s1 + -6) == __n) && (iVar3 = wmemcmp(__s1,__s2,__n), iVar3 == 0)) {
        return lVar2;
      }
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
    } while (uVar4 < uVar6);
  }
  return 0;
}

/* address=00a5c780
   symbol=CMasterResourceManager::getAnimationSet */

/* CMasterResourceManager::getAnimationSet(std::wstring) */

long __thiscall
CMasterResourceManager::getAnimationSet(CMasterResourceManager *this,undefined8 *param_2)

{
  long lVar1;
  wchar_t *__s2;
  size_t __n;
  long lVar2;
  wchar_t *__s1;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x150);
  uVar6 = *(long *)(this + 0x158) - lVar1 >> 3;
  if (uVar6 != 0) {
    __s2 = (wchar_t *)*param_2;
    uVar4 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      lVar2 = *(long *)(lVar1 + uVar4 * 8);
      __s1 = *(wchar_t **)(lVar2 + 0x18);
      if ((*(size_t *)(__s1 + -6) == __n) && (iVar3 = wmemcmp(__s1,__s2,__n), iVar3 == 0)) {
        return lVar2;
      }
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
    } while (uVar4 < uVar6);
  }
  return 0;
}

/* address=00a5c800
   symbol=CMasterResourceManager::getBatchModel */

/* CMasterResourceManager::getBatchModel(std::wstring) */

long __thiscall
CMasterResourceManager::getBatchModel(CMasterResourceManager *this,undefined8 *param_2)

{
  long lVar1;
  wchar_t *__s2;
  size_t __n;
  long lVar2;
  wchar_t *__s1;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x138);
  uVar6 = *(long *)(this + 0x140) - lVar1 >> 3;
  if (uVar6 != 0) {
    __s2 = (wchar_t *)*param_2;
    uVar4 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      lVar2 = *(long *)(lVar1 + uVar4 * 8);
      __s1 = *(wchar_t **)(lVar2 + 0x20);
      if ((*(size_t *)(__s1 + -6) == __n) && (iVar3 = wmemcmp(__s1,__s2,__n), iVar3 == 0)) {
        return lVar2;
      }
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
    } while (uVar4 < uVar6);
  }
  return 0;
}

/* address=00a5c880
   symbol=CMasterResourceManager::createParticleReloader */

/* CMasterResourceManager::createParticleReloader() */

void __thiscall CMasterResourceManager::createParticleReloader(CMasterResourceManager *this)

{
  CParticlePreloader *this_00;

  if (*(long *)(this + 0xf8) != 0) {
    return;
  }
  this_00 = (CParticlePreloader *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5c8ca to 00a5c8ce has its CatchHandler @ 00a5c8e5 */
  CParticlePreloader::CParticlePreloader(this_00,*(CResourceSettings **)(this + 0x68));
  *(CParticlePreloader **)(this + 0xf8) = this_00;
  return;
}

/* address=00a5c900
   symbol=CMasterResourceManager::loadParticles */

/* CMasterResourceManager::loadParticles() */

void __thiscall CMasterResourceManager::loadParticles(CMasterResourceManager *this)

{
  if ((((*(long *)(this + 0xf0) != 0) && (*(long *)(this + 0x90) != 0)) &&
      (*(long *)(this + 0x98) != 0)) && (*(long *)(this + 200) != 0)) {
    createParticleReloader(this);
    CParticlePreloader::ReloadParticles(*(CParticlePreloader **)(this + 0xf8));
    return;
  }
  return;
}

/* address=00a5cc80
   symbol=CMasterResourceManager::addAnimationSet */

/* CMasterResourceManager::addAnimationSet(CAnimationSet*) */

void __thiscall
CMasterResourceManager::addAnimationSet(CMasterResourceManager *this,CAnimationSet *param_1)

{
  undefined8 *puVar1;
  long lVar2;
  CAnimationSet *local_10 [2];

  puVar1 = *(undefined8 **)(this + 0x158);
  if (puVar1 == *(undefined8 **)(this + 0x160)) {
    local_10[0] = param_1;
    std::vector<CAnimationSet*,std::allocator<CAnimationSet*>>::_M_insert_aux
              ((vector<CAnimationSet*,std::allocator<CAnimationSet*>> *)(this + 0x150),puVar1,
               local_10);
  }
  else {
    lVar2 = 0;
    if (puVar1 != (undefined8 *)0x0) {
      *puVar1 = param_1;
      lVar2 = *(long *)(this + 0x158);
    }
    *(long *)(this + 0x158) = lVar2 + 8;
  }
  return;
}

/* address=00a5dba0
   symbol=CMasterResourceManager::reloadResources */

/* WARNING: Removing unreachable block (ram,0x00a5dd04) */
/* WARNING: Removing unreachable block (ram,0x00a5dcdb) */
/* CMasterResourceManager::reloadResources() */

void __thiscall CMasterResourceManager::reloadResources(CMasterResourceManager *this)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  long local_38 [2];
  long local_28;
  allocator local_1a;
  allocator local_19 [9];

  CGraphManager::reload(*(CGraphManager **)(m_pMasterResourceManager + 0x48));
  CEffectGroupManager::reload(*(CEffectGroupManager **)(m_pMasterResourceManager + 0x58));
  CParticlePreloader::ReloadParticles(*(CParticlePreloader **)(m_pMasterResourceManager + 0xf8));
  CMissilePreloader::reloadMissiles(*(CMissilePreloader **)(m_pMasterResourceManager + 0x60));
  CSkillParser::reloadSkills();
  CSpawnClassParser::reloadFromDirectory
            (*(CSpawnClassParser **)(m_pMasterResourceManager + 0x78),L"media/SpawnClasses/");
  reloadSoundBankData(m_pMasterResourceManager);
                    /* try { // try from 00a5dc24 to 00a5dc28 has its CatchHandler @ 00a5dcd0 */
  std::wstring::wstring((wstring_conflict *)&local_28,L"EXPERIENCEGATE",local_19);
                    /* try { // try from 00a5dc30 to 00a5dc34 has its CatchHandler @ 00a5dcf3 */
  uVar3 = CGraphManager::getGraph(*(CGraphManager **)(this + 0x48),(wstring_conflict *)&local_28);
  *(undefined8 *)(this + 0x168) = uVar3;
  if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_28 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
    }
  }
                    /* try { // try from 00a5dc5b to 00a5dc5f has its CatchHandler @ 00a5dd02 */
  std::wstring::wstring((wstring_conflict *)local_38,L"FAMEGATE",&local_1a);
                    /* try { // try from 00a5dc67 to 00a5dc6b has its CatchHandler @ 00a5dce6 */
  uVar3 = CGraphManager::getGraph(*(CGraphManager **)(this + 0x48),(wstring_conflict *)local_38);
  *(undefined8 *)(this + 0x170) = uVar3;
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
  return;
}

/* address=00a5de90
   symbol=CMasterResourceManager::CMasterResourceManager */

/* WARNING: Removing unreachable block (ram,0x00a5eaff) */
/* WARNING: Removing unreachable block (ram,0x00a5eb1b) */
/* WARNING: Removing unreachable block (ram,0x00a5eae3) */
/* WARNING: Removing unreachable block (ram,0x00a5ead5) */
/* WARNING: Removing unreachable block (ram,0x00a5e8db) */
/* WARNING: Removing unreachable block (ram,0x00a5eaf1) */
/* WARNING: Removing unreachable block (ram,0x00a5eb29) */
/* WARNING: Removing unreachable block (ram,0x00a5eb0d) */
/* WARNING: Removing unreachable block (ram,0x00a5eac5) */
/* CMasterResourceManager::CMasterResourceManager(CSettings*) */

void __thiscall
CMasterResourceManager::CMasterResourceManager(CMasterResourceManager *this,CSettings *param_1)

{
  int *piVar1;
  wchar_t wVar2;
  code *pcVar3;
  wchar_t *pwVar4;
  int iVar5;
  uint uVar6;
  CFileSystem *this_00;
  CResourceSettings *this_01;
  wstring_conflict *pwVar7;
  CStringTranslate *this_02;
  CSteamStats *this_03;
  CAchievements *pCVar8;
  CHierarchy *this_04;
  CUnitThemes *this_05;
  CRecipes *this_06;
  CCinematics *this_07;
  CRandomNames *this_08;
  CGameGlobals *this_09;
  CUnitResourceList *this_10;
  CGraphManager *this_11;
  undefined8 uVar9;
  undefined8 *puVar10;
  CEffectGroupManager *this_12;
  CSets *this_13;
  CRoomPieceDataInformation *this_14;
  CSoundBankDataInformation *this_15;
  CDungeonManager *pCVar11;
  CSkillParser *this_16;
  CMissilePreloader *this_17;
  CSpawnClassParser *this_18;
  CGameSpeed *pCVar12;
  CSharedStash *this_19;
  CAchievement *pCVar13;
  ParticleUniversePlugin *this_20;
  Plugin *pPVar14;
  bool bVar15;
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  wchar_t *local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CMasterResourceManager_00fe0910;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
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
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  this[0xc0] = (CMasterResourceManager)0x0;
  this[0xc1] = (CMasterResourceManager)0x1;
  *(undefined8 *)(this + 200) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined8 *)(this + 0x100) = 0;
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined8 *)(this + 0x118) = 0;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  *(undefined8 *)(this + 0x140) = 0;
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined8 *)(this + 0x150) = 0;
  *(undefined8 *)(this + 0x158) = 0;
  *(undefined8 *)(this + 0x160) = 0;
  *(undefined8 *)(this + 0x168) = 0;
  *(undefined8 *)(this + 0x170) = 0;
  *(undefined8 *)(this + 0x178) = 0;
  *(undefined8 *)(this + 0x180) = 0;
  *(undefined8 *)(this + 0x188) = 0;
  *(CSettings **)(this + 0x90) = param_1;
  m_pMasterResourceManager = this;
                    /* try { // try from 00a5e078 to 00a5e07c has its CatchHandler @ 00a5ea82 */
  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a5e092 to 00a5e096 has its CatchHandler @ 00a5ea75 */
  std::wstring::wstring((wstring_conflict *)local_68,L"COMPRESS",local_39);
                    /* try { // try from 00a5e0a9 to 00a5e0ad has its CatchHandler @ 00a5e9f5 */
  CCmdLineParser::GetStringParam
            (local_78,*(undefined8 *)(param_1 + 0x140),(wstring_conflict *)local_68);
  bVar15 = true;
  if (*(size_t *)(local_78[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar5 = wmemcmp(local_78[0],::EMPTY_WSTRING,*(size_t *)(local_78[0] + -6));
    bVar15 = iVar5 != 0;
  }
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar4 = local_78[0] + -2;
    wVar2 = *pwVar4;
    *pwVar4 = *pwVar4 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e113 to 00a5e117 has its CatchHandler @ 00a5ea82 */
  this_00 = (CFileSystem *)Ogre::NedAllocImpl::allocBytes(0xc0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e122 to 00a5e126 has its CatchHandler @ 00a5e9ac */
  CFileSystem::CFileSystem(this_00,bVar15);
  *(CFileSystem **)(this + 0xb8) = this_00;
                    /* try { // try from 00a5e139 to 00a5e13d has its CatchHandler @ 00a5ea82 */
  this_01 = (CResourceSettings *)Ogre::NedAllocImpl::allocBytes(0x140,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e144 to 00a5e148 has its CatchHandler @ 00a5e9e5 */
  CResourceSettings::CResourceSettings(this_01);
  *(CResourceSettings **)(this + 0x68) = this_01;
  pcVar3 = *(code **)(*(long *)this_01 + 0x18);
                    /* try { // try from 00a5e16a to 00a5e16e has its CatchHandler @ 00a5e9d5 */
  std::wstring::wstring((wstring_conflict *)local_88,L"",&local_3a);
                    /* try { // try from 00a5e176 to 00a5e178 has its CatchHandler @ 00a5e9aa */
  (*pcVar3)(*(undefined8 *)(this + 0x68),(wstring_conflict *)local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e195 to 00a5e1ac has its CatchHandler @ 00a5ea82 */
  pwVar7 = (wstring_conflict *)
           CDynamicPropertyFile::GetString
                     (*(CDynamicPropertyFile **)(this + 0x68),KRESOURCESETTING_S_TRANSLATE_FILE);
  this_02 = (CStringTranslate *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e1b6 to 00a5e1ba has its CatchHandler @ 00a5e975 */
  CStringTranslate::CStringTranslate(this_02,pwVar7);
  *(CStringTranslate **)(this + 0x10) = this_02;
                    /* try { // try from 00a5e1ca to 00a5e1ce has its CatchHandler @ 00a5ea82 */
  this_03 = (CSteamStats *)Ogre::NedAllocImpl::allocBytes(0xa0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e1d5 to 00a5e1d9 has its CatchHandler @ 00a5e965 */
  CSteamStats::CSteamStats(this_03);
  *(CSteamStats **)(this + 0x180) = this_03;
                    /* try { // try from 00a5e1ec to 00a5e1f0 has its CatchHandler @ 00a5ea82 */
  pCVar8 = (CAchievements *)Ogre::NedAllocImpl::allocBytes(0x78,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e1f7 to 00a5e1fb has its CatchHandler @ 00a5e955 */
  CAchievements::CAchievements(pCVar8);
  *(CAchievements **)(this + 0x188) = pCVar8;
                    /* try { // try from 00a5e203 to 00a5e217 has its CatchHandler @ 00a5ea82 */
  parseEffects();
  this_04 = (CHierarchy *)Ogre::NedAllocImpl::allocBytes(0x88,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e223 to 00a5e227 has its CatchHandler @ 00a5e945 */
  CHierarchy::CHierarchy(this_04,L"media/unittypes.hie");
  *(CHierarchy **)(this + 0x80) = this_04;
                    /* try { // try from 00a5e23a to 00a5e23e has its CatchHandler @ 00a5ea82 */
  this_05 = (CUnitThemes *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e24a to 00a5e24e has its CatchHandler @ 00a5e935 */
  CUnitThemes::CUnitThemes(this_05,L"media/unitthemes/");
  *(CUnitThemes **)(this + 0x20) = this_05;
                    /* try { // try from 00a5e25e to 00a5e262 has its CatchHandler @ 00a5ea82 */
  this_06 = (CRecipes *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e26e to 00a5e272 has its CatchHandler @ 00a5e925 */
  CRecipes::CRecipes(this_06,L"media/recipes/");
  *(CRecipes **)(this + 0x28) = this_06;
                    /* try { // try from 00a5e282 to 00a5e286 has its CatchHandler @ 00a5ea82 */
  this_07 = (CCinematics *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e292 to 00a5e296 has its CatchHandler @ 00a5e91f */
  CCinematics::CCinematics(this_07,L"media/cinematics/");
  *(CCinematics **)(this + 0x38) = this_07;
                    /* try { // try from 00a5e2a6 to 00a5e2aa has its CatchHandler @ 00a5ea82 */
  this_08 = (CRandomNames *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e2b6 to 00a5e2ba has its CatchHandler @ 00a5e91a */
  CRandomNames::CRandomNames(this_08,L"media/randomnames.dat");
  *(CRandomNames **)(this + 0x40) = this_08;
                    /* try { // try from 00a5e2ca to 00a5e2ce has its CatchHandler @ 00a5ea82 */
  this_09 = (CGameGlobals *)Ogre::NedAllocImpl::allocBytes(0x2d0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e2da to 00a5e2de has its CatchHandler @ 00a5ea65 */
  CGameGlobals::CGameGlobals(this_09,L"media/globals.dat");
  *(CGameGlobals **)(this + 0x18) = this_09;
                    /* try { // try from 00a5e2ee to 00a5e2f2 has its CatchHandler @ 00a5ea82 */
  this_10 = (CUnitResourceList *)Ogre::NedAllocImpl::allocBytes(0x120,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e2f9 to 00a5e2fd has its CatchHandler @ 00a5ea55 */
  CUnitResourceList::CUnitResourceList(this_10);
  *(CUnitResourceList **)(this + 0x88) = this_10;
                    /* try { // try from 00a5e313 to 00a5e339 has its CatchHandler @ 00a5ea82 */
  CUnitResourceList::InitUnitResourceList
            (this_10,*(CResourceSettings **)(this + 0x68),*(CHierarchy **)(this + 0x80));
  pwVar7 = (wstring_conflict *)
           CDynamicPropertyFile::GetString
                     (*(CDynamicPropertyFile **)(this + 0x68),KRESOURCESETTING_S_GRAPH_MANAGER);
  this_11 = (CGraphManager *)Ogre::NedAllocImpl::allocBytes(0x90,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e343 to 00a5e347 has its CatchHandler @ 00a5ea45 */
  CGraphManager::CGraphManager(this_11,pwVar7);
  *(CGraphManager **)(this + 0x48) = this_11;
                    /* try { // try from 00a5e361 to 00a5e365 has its CatchHandler @ 00a5ea35 */
  std::wstring::wstring((wstring_conflict *)local_98,L"EXPERIENCEGATE",&local_3b);
                    /* try { // try from 00a5e36d to 00a5e371 has its CatchHandler @ 00a5e995 */
  uVar9 = CGraphManager::getGraph(*(CGraphManager **)(this + 0x48),(wstring_conflict *)local_98);
  *(undefined8 *)(this + 0x168) = uVar9;
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e3a0 to 00a5e3a4 has its CatchHandler @ 00a5ea25 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"FAMEGATE",&local_3c);
                    /* try { // try from 00a5e3ac to 00a5e3b0 has its CatchHandler @ 00a5ea17 */
  uVar9 = CGraphManager::getGraph(*(CGraphManager **)(this + 0x48),(wstring_conflict *)local_a8);
  *(undefined8 *)(this + 0x170) = uVar9;
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e3d4 to 00a5e3eb has its CatchHandler @ 00a5ea82 */
  puVar10 = (undefined8 *)
            CDynamicPropertyFile::GetString
                      (*(CDynamicPropertyFile **)(this + 0x68),KRESOURCESETTING_S_AFFIXES_FOLDER);
  pwVar4 = (wchar_t *)*puVar10;
  this_12 = (CEffectGroupManager *)Ogre::NedAllocImpl::allocBytes(0x78,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e3f5 to 00a5e3f9 has its CatchHandler @ 00a5e985 */
  CEffectGroupManager::CEffectGroupManager(this_12,pwVar4);
  *(CEffectGroupManager **)(this + 0x58) = this_12;
                    /* try { // try from 00a5e409 to 00a5e40d has its CatchHandler @ 00a5ea82 */
  this_13 = (CSets *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e41d to 00a5e421 has its CatchHandler @ 00a5e9c5 */
  CSets::CSets(this_13,L"media/sets/",*(CEffectGroupManager **)(this + 0x58));
  *(CSets **)(this + 0x30) = this_13;
                    /* try { // try from 00a5e431 to 00a5e435 has its CatchHandler @ 00a5ea82 */
  this_14 = (CRoomPieceDataInformation *)
            Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e440 to 00a5e444 has its CatchHandler @ 00a5e9b5 */
  CRoomPieceDataInformation::CRoomPieceDataInformation(this_14,*(CResourceSettings **)(this + 0x68))
  ;
  *(CRoomPieceDataInformation **)(this + 0xe8) = this_14;
                    /* try { // try from 00a5e457 to 00a5e45b has its CatchHandler @ 00a5ea82 */
  this_15 = (CSoundBankDataInformation *)
            Ogre::NedAllocImpl::allocBytes(0xa0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e466 to 00a5e46a has its CatchHandler @ 00a5eabc */
  CSoundBankDataInformation::CSoundBankDataInformation(this_15,*(CResourceSettings **)(this + 0x68))
  ;
  *(CSoundBankDataInformation **)(this + 0x100) = this_15;
                    /* try { // try from 00a5e487 to 00a5e48b has its CatchHandler @ 00a5eab7 */
  std::wstring::wstring((wstring_conflict *)local_b8,L"media/dungeons/",&local_3d);
                    /* try { // try from 00a5e497 to 00a5e49b has its CatchHandler @ 00a5eab2 */
  pCVar11 = (CDungeonManager *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e4a5 to 00a5e4a9 has its CatchHandler @ 00a5ea95 */
  CDungeonManager::CDungeonManager(pCVar11);
  *(CDungeonManager **)(this + 0x50) = pCVar11;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e4cb to 00a5e4cf has its CatchHandler @ 00a5ea82 */
  this_16 = (CSkillParser *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e4da to 00a5e4de has its CatchHandler @ 00a5ea12 */
  CSkillParser::CSkillParser(this_16,*(CResourceSettings **)(this + 0x68));
  *(CSkillParser **)(this + 0x70) = this_16;
                    /* try { // try from 00a5e4ee to 00a5e4f2 has its CatchHandler @ 00a5ea82 */
  this_17 = (CMissilePreloader *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e4fd to 00a5e501 has its CatchHandler @ 00a5e8d9 */
  CMissilePreloader::CMissilePreloader(this_17,*(CResourceSettings **)(this + 0x68));
  *(CMissilePreloader **)(this + 0x60) = this_17;
                    /* try { // try from 00a5e511 to 00a5e515 has its CatchHandler @ 00a5ea82 */
  this_18 = (CSpawnClassParser *)Ogre::NedAllocImpl::allocBytes(0x70,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e51c to 00a5e520 has its CatchHandler @ 00a5e87f */
  CSpawnClassParser::CSpawnClassParser(this_18);
  *(CSpawnClassParser **)(this + 0x78) = this_18;
                    /* try { // try from 00a5e53a to 00a5e53e has its CatchHandler @ 00a5e912 */
  std::wstring::wstring
            ((wstring_conflict *)local_c8,L"media/graphs/camerashakes/DecelerateGameSpeed.dat",
             &local_3e);
                    /* try { // try from 00a5e54f to 00a5e553 has its CatchHandler @ 00a5e90b */
  std::wstring::wstring
            ((wstring_conflict *)local_d8,L"media/graphs/camerashakes/DecelerateGameSpeed.dat",
             &local_3f);
                    /* try { // try from 00a5e55f to 00a5e563 has its CatchHandler @ 00a5e906 */
  pCVar12 = (CGameSpeed *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e570 to 00a5e574 has its CatchHandler @ 00a5e8e9 */
  CGameSpeed::CGameSpeed(pCVar12,(wstring_conflict *)local_c8,local_d8);
  *(CGameSpeed **)(this + 0xa8) = pCVar12;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00a5e5aa to 00a5e5ae has its CatchHandler @ 00a5ea82 */
  this_19 = (CSharedStash *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e5bf to 00a5e5c3 has its CatchHandler @ 00a5ea8c */
  CSharedStash::CSharedStash(this_19,L"sharedstash.bin",L"sharedstashh.bin");
  *(CSharedStash **)(this + 0x178) = this_19;
                    /* try { // try from 00a5e5d5 to 00a5e678 has its CatchHandler @ 00a5ea82 */
  CSteamStats::update(0.0);
  CSteamStats::update(0.0);
  iVar5 = CFileSystem::getNumberOfMods(*(CFileSystem **)(this + 0xb8));
  if (iVar5 != 0) {
    pCVar8 = (CAchievements *)CAchievements::getSingleton();
    pCVar13 = (CAchievement *)CAchievements::getAchievement(pCVar8);
    CAchievement::forceComplete(pCVar13);
  }
  uVar6 = CFileSystem::getNumberOfMods(*(CFileSystem **)(this + 0xb8));
  if (4 < uVar6) {
    pCVar8 = (CAchievements *)CAchievements::getSingleton();
    pCVar13 = (CAchievement *)CAchievements::getAchievement(pCVar8);
    CAchievement::forceComplete(pCVar13);
  }
  uVar6 = CFileSystem::getNumberOfMods(*(CFileSystem **)(this + 0xb8));
  if (9 < uVar6) {
    pCVar8 = (CAchievements *)CAchievements::getSingleton();
    pCVar13 = (CAchievement *)CAchievements::getAchievement(pCVar8);
    CAchievement::forceComplete(pCVar13);
  }
  this_20 = (ParticleUniversePlugin *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5e67f to 00a5e683 has its CatchHandler @ 00a5ea87 */
  ParticleUniverse::ParticleUniversePlugin::ParticleUniversePlugin(this_20);
                    /* try { // try from 00a5e684 to 00a5e698 has its CatchHandler @ 00a5ea82 */
  pPVar14 = (Plugin *)Ogre::Root::getSingleton();
  Ogre::Root::installPlugin(pPVar14);
  uVar9 = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
  *(undefined8 *)(this + 0xf0) = uVar9;
  return;
}

/* address=00a5eb40
   symbol=CMasterResourceManager::~CMasterResourceManager */

/* WARNING: Removing unreachable block (ram,0x00a5f0ad) */
/* WARNING: Removing unreachable block (ram,0x00a5f09d) */
/* CMasterResourceManager::~CMasterResourceManager() */

void __thiscall CMasterResourceManager::~CMasterResourceManager(CMasterResourceManager *this)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  code *pcVar4;
  CRandomNames *this_00;
  ulong uVar5;
  long lVar6;
  uint uVar7;
  long *plVar8;
  long lVar9;
  allocator *paVar10;
  long local_48;
  allocator local_39 [9];

  lVar9 = *(long *)(this + 0x128);
  lVar6 = *(long *)(this + 0x120);
  *(undefined ***)this = &PTR__CMasterResourceManager_00fe0910;
  if (lVar9 - lVar6 >> 3 != 0) {
    uVar5 = 0;
    do {
      plVar3 = *(long **)(lVar6 + uVar5 * 8);
      if (plVar3 != (long *)0x0) {
                    /* try { // try from 00a5eb94 to 00a5ed68 has its CatchHandler @ 00a5f0ab */
        (**(code **)(*plVar3 + 8))();
        *(undefined8 *)(*(long *)(this + 0x120) + uVar5 * 8) = 0;
        lVar6 = *(long *)(this + 0x120);
        lVar9 = *(long *)(this + 0x128);
      }
      uVar5 = (ulong)((int)uVar5 + 1);
    } while (uVar5 < (ulong)(lVar9 - lVar6 >> 3));
  }
  lVar9 = *(long *)(this + 0x140);
  lVar6 = *(long *)(this + 0x138);
  if (lVar9 - lVar6 >> 3 != 0) {
    uVar5 = 0;
    do {
      plVar3 = *(long **)(lVar6 + uVar5 * 8);
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
        *(undefined8 *)(*(long *)(this + 0x138) + uVar5 * 8) = 0;
        lVar6 = *(long *)(this + 0x138);
        lVar9 = *(long *)(this + 0x140);
      }
      uVar5 = (ulong)((int)uVar5 + 1);
    } while (uVar5 < (ulong)(lVar9 - lVar6 >> 3));
  }
  lVar9 = *(long *)(this + 0x158);
  lVar6 = *(long *)(this + 0x150);
  if (lVar9 - lVar6 >> 3 != 0) {
    uVar5 = 0;
    uVar7 = 0;
    do {
      plVar3 = *(long **)(lVar6 + uVar5 * 8);
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 8))();
        *(undefined8 *)(*(long *)(this + 0x150) + uVar5 * 8) = 0;
        lVar6 = *(long *)(this + 0x150);
        lVar9 = *(long *)(this + 0x158);
      }
      uVar7 = uVar7 + 1;
      uVar5 = (ulong)uVar7;
    } while (uVar5 < (ulong)(lVar9 - lVar6 >> 3));
  }
  *(long *)(this + 0x158) = lVar6;
  if (*(long **)(this + 0x188) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x188) + 8))();
    *(undefined8 *)(this + 0x188) = 0;
  }
  if (*(long **)(this + 0x180) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x180) + 8))();
    *(undefined8 *)(this + 0x180) = 0;
  }
  if (*(long **)(this + 0x178) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x178) + 8))();
    *(undefined8 *)(this + 0x178) = 0;
  }
  if (*(long **)(this + 0x60) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x60) + 8))();
    *(undefined8 *)(this + 0x60) = 0;
  }
  if (*(long **)(this + 0xf8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xf8) + 8))();
    *(undefined8 *)(this + 0xf8) = 0;
  }
  if (*(long **)(this + 0x80) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x80) + 8))();
    *(undefined8 *)(this + 0x80) = 0;
  }
  if (*(long **)(this + 0x88) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x88) + 8))();
    *(undefined8 *)(this + 0x88) = 0;
  }
  if (*(long **)(this + 0x68) != (long *)0x0) {
    pcVar4 = *(code **)(**(long **)(this + 0x68) + 0x10);
                    /* try { // try from 00a5ed91 to 00a5ed95 has its CatchHandler @ 00a5f03e */
    std::wstring::wstring((wstring_conflict *)&local_48,L"",local_39);
                    /* try { // try from 00a5ed9d to 00a5ed9f has its CatchHandler @ 00a5f090 */
    (*pcVar4)(*(undefined8 *)(this + 0x68),&local_48);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if (*(long **)(this + 0x68) != (long *)0x0) {
                    /* try { // try from 00a5edc1 to 00a5ef3b has its CatchHandler @ 00a5f0ab */
      (**(code **)(**(long **)(this + 0x68) + 8))();
      *(undefined8 *)(this + 0x68) = 0;
    }
  }
  if (*(long **)(this + 0xe8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xe8) + 8))();
    *(undefined8 *)(this + 0xe8) = 0;
  }
  if (*(long **)(this + 0x100) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x100) + 8))();
    *(undefined8 *)(this + 0x100) = 0;
  }
  if (*(long **)(this + 0x78) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x78) + 8))();
    *(undefined8 *)(this + 0x78) = 0;
  }
  if (*(long **)(this + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x48) + 8))();
    *(undefined8 *)(this + 0x48) = 0;
  }
  if (*(long **)(this + 0x70) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x70) + 8))();
    *(undefined8 *)(this + 0x70) = 0;
  }
  if (*(long **)(this + 0x58) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x58) + 8))();
    *(undefined8 *)(this + 0x58) = 0;
  }
  if (*(long **)(this + 0xa8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa8) + 8))();
    *(undefined8 *)(this + 0xa8) = 0;
  }
  if (*(long **)(this + 0x20) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x20) + 8))();
    *(undefined8 *)(this + 0x20) = 0;
  }
  if (*(long **)(this + 0x28) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x28) + 8))();
    *(undefined8 *)(this + 0x28) = 0;
  }
  if (*(long **)(this + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x38) + 8))();
    *(undefined8 *)(this + 0x38) = 0;
  }
  if (*(long **)(this + 0x30) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x30) + 8))();
    *(undefined8 *)(this + 0x30) = 0;
  }
  this_00 = *(CRandomNames **)(this + 0x40);
  if (this_00 != (CRandomNames *)0x0) {
    CRandomNames::~CRandomNames(this_00);
    Ogre::NedAllocImpl::deallocBytes(this_00);
    *(undefined8 *)(this + 0x40) = 0;
  }
  if (*(long **)(this + 0x10) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x10) + 8))();
    *(undefined8 *)(this + 0x10) = 0;
  }
  if (*(long **)(this + 0x18) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x18) + 8))();
    *(undefined8 *)(this + 0x18) = 0;
  }
  if (*(long **)(this + 0xb8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xb8) + 8))();
    *(undefined8 *)(this + 0xb8) = 0;
  }
  m_pMasterResourceManager = 0;
  if (*(void **)(this + 0x150) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x150));
  }
  if (*(void **)(this + 0x138) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x138));
  }
  if (*(void **)(this + 0x120) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x120));
  }
  plVar3 = *(long **)(this + 0x110);
  for (plVar8 = *(long **)(this + 0x108); plVar3 != plVar8; plVar8 = plVar8 + 1) {
    paVar10 = (allocator *)(*plVar8 + -0x18);
    if (paVar10 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar8 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy(paVar10);
      }
    }
  }
  if (*(void **)(this + 0x108) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x108));
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00a5f0c0
   symbol=CMasterResourceManager::~CMasterResourceManager */

/* CMasterResourceManager::~CMasterResourceManager() */

void __thiscall CMasterResourceManager::~CMasterResourceManager(CMasterResourceManager *this)

{
  ~CMasterResourceManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a5f0e0
   symbol=CMasterResourceManager::addResourceLocation */

/* WARNING: Removing unreachable block (ram,0x00a5f368) */
/* WARNING: Removing unreachable block (ram,0x00a5f3fc) */
/* WARNING: Removing unreachable block (ram,0x00a5f373) */
/* WARNING: Removing unreachable block (ram,0x00a5f3ef) */
/* WARNING: Removing unreachable block (ram,0x00a5f2ef) */
/* CMasterResourceManager::addResourceLocation(std::wstring const&, std::string const&, bool) */

void __thiscall
CMasterResourceManager::addResourceLocation
          (CMasterResourceManager *this,wstring_conflict *param_1,string *param_2,bool param_3)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  string *psVar4;
  string *psVar5;
  long lVar6;
  long lVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  bool bVar12;
  byte bVar13;
  long local_78 [2];
  long local_68 [2];
  wchar_t *local_58 [2];
  char *local_48;
  allocator local_3a;
  allocator local_39 [9];

  bVar13 = 0;
                    /* try { // try from 00a5f0ff to 00a5f103 has its CatchHandler @ 00a5f2e4 */
  STRINGS::StringUpper((STRINGS *)local_58,param_1);
                    /* try { // try from 00a5f116 to 00a5f11a has its CatchHandler @ 00a5f311 */
  std::wstring::wstring((wstring_conflict *)local_68,local_58[0],local_39);
                    /* try { // try from 00a5f126 to 00a5f12a has its CatchHandler @ 00a5f2fc */
  STRINGS::StringConvertToUTF8((wstring_conflict *)&local_48);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar11 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_58[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
    }
  }
  psVar5 = *(string **)(this + 0x110);
  iVar11 = (int)((ulong)((long)psVar5 - *(long *)(this + 0x108)) >> 3);
  if (0 < iVar11) {
    lVar7 = 0;
    iVar8 = 0;
    do {
      pcVar9 = *(char **)(*(long *)(this + 0x108) + lVar7);
      if (*(long *)(pcVar9 + -0x18) == *(long *)(local_48 + -0x18)) {
        bVar12 = true;
        lVar6 = *(long *)(local_48 + -0x18);
        pcVar10 = local_48;
        do {
          if (lVar6 == 0) break;
          lVar6 = lVar6 + -1;
          bVar12 = *pcVar9 == *pcVar10;
          pcVar9 = pcVar9 + (ulong)bVar13 * -2 + 1;
          pcVar10 = pcVar10 + (ulong)bVar13 * -2 + 1;
        } while (bVar12);
        if (bVar12) {
          if (!param_3) {
            if ((allocator *)(local_48 + -0x18) ==
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              return;
            }
            LOCK();
            piVar1 = (int *)(local_48 + -8);
            iVar11 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (0 < iVar11) {
              return;
            }
            std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
            return;
          }
          goto LAB_00a5f1c0;
        }
      }
      iVar8 = iVar8 + 1;
      lVar7 = lVar7 + 8;
    } while (iVar8 < iVar11);
  }
  if (psVar5 == *(string **)(this + 0x118)) {
                    /* try { // try from 00a5f2da to 00a5f2de has its CatchHandler @ 00a5f3fa */
    std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
              ((vector<std::string,std::allocator<std::string>> *)(this + 0x108),psVar5,
               (wstring_conflict *)&local_48);
  }
  else {
    if (psVar5 == (string *)0x0) {
      lVar7 = 0;
    }
    else {
                    /* try { // try from 00a5f275 to 00a5f279 has its CatchHandler @ 00a5f3b7 */
      std::string::string(psVar5,(string *)&local_48);
      lVar7 = *(long *)(this + 0x110);
    }
    *(long *)(this + 0x110) = lVar7 + 8;
  }
LAB_00a5f1c0:
  psVar5 = (string *)&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
  if (*(long *)(*(long *)param_2 + -0x18) != 0) {
    psVar5 = param_2;
  }
                    /* try { // try from 00a5f1de to 00a5f1e2 has its CatchHandler @ 00a5f37e */
  std::string::string((string *)local_78,"FileSystem",&local_3a);
                    /* try { // try from 00a5f1e3 to 00a5f1fe has its CatchHandler @ 00a5f3e2 */
  psVar4 = (string *)Ogre::ResourceGroupManager::getSingleton();
  Ogre::ResourceGroupManager::addResourceLocation
            (psVar4,(string *)&local_48,(string *)local_78,SUB81(psVar5,0));
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar11 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 00a5f225 to 00a5f234 has its CatchHandler @ 00a5f3fa */
  psVar5 = (string *)Ogre::ResourceGroupManager::getSingleton();
  Ogre::ResourceGroupManager::initialiseResourceGroup(psVar5);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar11 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  return;
}

/* address=00a5f410
   symbol=CMasterResourceManager::addBatchModel */

/* WARNING: Removing unreachable block (ram,0x00a5f7b3) */
/* WARNING: Removing unreachable block (ram,0x00a5f7c1) */
/* WARNING: Removing unreachable block (ram,0x00a5f7a8) */
/* WARNING: Removing unreachable block (ram,0x00a5f833) */
/* WARNING: Removing unreachable block (ram,0x00a5f825) */
/* CMasterResourceManager::addBatchModel(CResourceManager*, Ogre::SceneManager*, std::wstring,
   bool&) */

CGenericModel * __thiscall
CMasterResourceManager::addBatchModel
          (CMasterResourceManager *this,undefined8 param_1,undefined8 param_3,
          wstring_conflict *param_4,undefined1 *param_5)

{
  int *piVar1;
  undefined8 *puVar2;
  int iVar3;
  CFileSystem *this_00;
  long lVar4;
  CGenericModel *this_01;
  BatchModelRef *this_02;
  undefined1 *local_a8;
  long local_a0;
  long local_98;
  undefined4 local_90;
  undefined4 local_8c;
  undefined1 *local_88;
  char local_80;
  BatchModelRef *local_70;
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [16];
  long local_48 [3];

  local_a8 = &DAT_01423a38;
                    /* try { // try from 00a5f458 to 00a5f45c has its CatchHandler @ 00a5f818 */
  std::string::string((string *)&local_a0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00a5f466 to 00a5f46a has its CatchHandler @ 00a5f7fc */
  std::wstring::wstring((wstring_conflict *)&local_98,(wstring_conflict *)&::EMPTY_WSTRING);
  local_90 = 4;
  local_8c = 3;
  local_88 = &DAT_01423a38;
  local_80 = '\0';
                    /* try { // try from 00a5f489 to 00a5f59c has its CatchHandler @ 00a5f81d */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_4,(CFileInfo *)&local_a8,false,true,false);
  if (local_80 == '\0') {
    this_01 = (CGenericModel *)0x0;
  }
  else {
    *param_5 = 1;
    std::wstring::wstring((wstring_conflict *)local_48,param_4);
    lVar4 = getBatchModel(this,(wstring_conflict *)local_48);
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if (lVar4 == 0) {
      std::wstring::wstring(local_58,param_4);
                    /* try { // try from 00a5f5a7 to 00a5f5ab has its CatchHandler @ 00a5f7f7 */
      std::wstring::wstring(local_68,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a5f5b7 to 00a5f5bb has its CatchHandler @ 00a5f7f2 */
      this_01 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5f5d9 to 00a5f5dd has its CatchHandler @ 00a5f7cf */
      CGenericModel::CGenericModel(this_01,param_1,0,local_58,local_68,0);
                    /* try { // try from 00a5f5e3 to 00a5f5e7 has its CatchHandler @ 00a5f7f7 */
      std::wstring::~wstring(local_68);
                    /* try { // try from 00a5f5ed to 00a5f61f has its CatchHandler @ 00a5f81d */
      std::wstring::~wstring(local_58);
      iVar3 = CGenericModel::getAnimationCount(this_01);
      if (iVar3 == 0) {
        this_02 = (BatchModelRef *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5f626 to 00a5f62a has its CatchHandler @ 00a5f78d */
        BatchModelRef::BatchModelRef(this_02);
        puVar2 = *(undefined8 **)(this + 0x140);
        local_70 = this_02;
        if (puVar2 == *(undefined8 **)(this + 0x148)) {
          std::vector<BatchModelRef*,std::allocator<BatchModelRef*>>::_M_insert_aux
                    ((vector<BatchModelRef*,std::allocator<BatchModelRef*>> *)(this + 0x138),puVar2,
                     &local_70);
        }
        else {
          lVar4 = 0;
          if (puVar2 != (undefined8 *)0x0) {
            *puVar2 = this_02;
            lVar4 = *(long *)(this + 0x140);
          }
          *(long *)(this + 0x140) = lVar4 + 8;
        }
        *(CGenericModel **)(local_70 + 0x10) = this_01;
        *(undefined4 *)(local_70 + 0x18) = 1;
                    /* try { // try from 00a5f682 to 00a5f6a5 has its CatchHandler @ 00a5f81d */
        std::wstring::assign((wstring_conflict *)(local_70 + 0x20));
        this_01 = *(CGenericModel **)(local_70 + 0x10);
      }
      else {
        *param_5 = 0;
      }
    }
    else {
      *(int *)(lVar4 + 0x18) = *(int *)(lVar4 + 0x18) + 1;
      this_01 = *(CGenericModel **)(lVar4 + 0x10);
    }
  }
  if ((allocator *)(local_88 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_88 + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88 + -0x18));
    }
  }
  if ((allocator *)(local_98 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98 + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98 + -0x18));
    }
  }
  if ((allocator *)(local_a0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a0 + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a0 + -0x18));
    }
  }
  if ((allocator *)(local_a8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8 + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8 + -0x18));
    }
  }
  return this_01;
}

/* address=00a5f850
   symbol=CMasterResourceManager::addCollisionModel */

/* WARNING: Removing unreachable block (ram,0x00a5fc24) */
/* WARNING: Removing unreachable block (ram,0x00a5fbe8) */
/* WARNING: Removing unreachable block (ram,0x00a5fbb5) */
/* WARNING: Removing unreachable block (ram,0x00a5fc11) */
/* WARNING: Removing unreachable block (ram,0x00a5fbf6) */
/* CMasterResourceManager::addCollisionModel(std::wstring) */

undefined8 __thiscall
CMasterResourceManager::addCollisionModel(CMasterResourceManager *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  CFileSystem *this_00;
  long lVar4;
  undefined8 uVar5;
  CollisionModelRef *this_01;
  CCollisionModel *pCVar6;
  undefined1 *local_78;
  long local_70;
  long local_68;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 *local_58;
  char local_50;
  wstring_conflict local_48 [8];
  CollisionModelRef *local_40;
  long local_38 [2];

  local_78 = &DAT_01423a38;
                    /* try { // try from 00a5f88d to 00a5f891 has its CatchHandler @ 00a5fbb0 */
  std::string::string((string *)&local_70,(string *)&::EMPTY_STRING);
                    /* try { // try from 00a5f89b to 00a5f89f has its CatchHandler @ 00a5fb94 */
  std::wstring::wstring((wstring_conflict *)&local_68,(wstring_conflict *)&::EMPTY_WSTRING);
  local_60 = 4;
  local_5c = 3;
  local_58 = &DAT_01423a38;
  local_50 = '\0';
                    /* try { // try from 00a5f8be to 00a5f9b7 has its CatchHandler @ 00a5fc1f */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_2,(CFileInfo *)&local_78,false,true,false);
  if (local_50 == '\0') {
    uVar5 = 0;
  }
  else {
    std::wstring::wstring((wstring_conflict *)local_38,param_2);
    lVar4 = getCollisionModel(this);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    if (lVar4 == 0) {
      this_01 = (CollisionModelRef *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5f9be to 00a5f9c2 has its CatchHandler @ 00a5fc04 */
      CollisionModelRef::CollisionModelRef(this_01);
      puVar3 = *(undefined8 **)(this + 0x128);
      local_40 = this_01;
      if (puVar3 == *(undefined8 **)(this + 0x130)) {
        std::vector<CollisionModelRef*,std::allocator<CollisionModelRef*>>::_M_insert_aux
                  ((vector<CollisionModelRef*,std::allocator<CollisionModelRef*>> *)(this + 0x120),
                   puVar3,&local_40);
      }
      else {
        lVar4 = 0;
        if (puVar3 != (undefined8 *)0x0) {
          *puVar3 = this_01;
          lVar4 = *(long *)(this + 0x128);
        }
        *(long *)(this + 0x128) = lVar4 + 8;
      }
                    /* try { // try from 00a5fa07 to 00a5fa0b has its CatchHandler @ 00a5fc1f */
      std::wstring::wstring(local_48,param_2);
                    /* try { // try from 00a5fa17 to 00a5fa1b has its CatchHandler @ 00a5fbe3 */
      pCVar6 = (CCollisionModel *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a5fa2d to 00a5fa31 has its CatchHandler @ 00a5fbc0 */
      CCollisionModel::CCollisionModel(pCVar6,*(undefined8 *)(this + 200),local_48);
      *(CCollisionModel **)(local_40 + 0x10) = pCVar6;
                    /* try { // try from 00a5fa3e to 00a5fa7f has its CatchHandler @ 00a5fc1f */
      std::wstring::~wstring(local_48);
      *(undefined4 *)(local_40 + 0x18) = 1;
      std::wstring::assign((wstring_conflict *)(local_40 + 0x20));
      uVar5 = *(undefined8 *)(local_40 + 0x10);
    }
    else {
      *(int *)(lVar4 + 0x18) = *(int *)(lVar4 + 0x18) + 1;
      uVar5 = *(undefined8 *)(lVar4 + 0x10);
    }
  }
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  if ((allocator *)(local_70 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_70 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_70 + -0x18));
    }
  }
  if ((allocator *)(local_78 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78 + -0x18));
    }
  }
  return uVar5;
}

/* export-summary functions=28 failures=0 */
