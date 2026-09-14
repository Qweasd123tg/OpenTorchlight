/* Targeted Ghidra class export.
   namespace=CAnimationSet
   Treat pseudocode as navigation evidence. */


/* address=00a4d5d0
   symbol=CAnimationSet::CAnimationSet */

/* CAnimationSet::CAnimationSet() */

void __thiscall CAnimationSet::CAnimationSet(CAnimationSet *this)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CAnimationSet_00fdef10;
  *(undefined4 **)(this + 0x18) = &DAT_01424558;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x10) = 1;
  *(undefined4 *)(this + 0x20) = 0;
  return;
}



/* address=00a4d640
   symbol=CAnimationSet::_GLOBAL__I_CAnimationSet */

/* CAnimationSet::CAnimationSet() */

void CAnimationSet::_GLOBAL__I_CAnimationSet(void)

{
  allocator local_25;
  allocator local_24;
  allocator local_23;
  allocator local_22;
  allocator local_21;
  allocator local_20;
  allocator local_1f;
  allocator local_1e;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;
  allocator local_18;
  allocator local_17;
  allocator local_16;
  allocator local_15;
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
  allocator local_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
                    /* try { // try from 00a4d6b5 to 00a4d6b9 has its CatchHandler @ 00a4d98a */
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&local_9);
                    /* try { // try from 00a4d6ce to 00a4d6d2 has its CatchHandler @ 00a4dac5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&local_a);
                    /* try { // try from 00a4d6e7 to 00a4d6eb has its CatchHandler @ 00a4dab5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&local_b);
                    /* try { // try from 00a4d700 to 00a4d704 has its CatchHandler @ 00a4daa5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&local_c);
                    /* try { // try from 00a4d719 to 00a4d71d has its CatchHandler @ 00a4da95 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&local_d);
                    /* try { // try from 00a4d732 to 00a4d736 has its CatchHandler @ 00a4da85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",&local_e)
  ;
                    /* try { // try from 00a4d74b to 00a4d74f has its CatchHandler @ 00a4da75 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&local_f);
                    /* try { // try from 00a4d764 to 00a4d768 has its CatchHandler @ 00a4da65 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&local_10)
  ;
                    /* try { // try from 00a4d77d to 00a4d781 has its CatchHandler @ 00a4da55 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&local_11)
  ;
                    /* try { // try from 00a4d796 to 00a4d79a has its CatchHandler @ 00a4da45 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&local_12);
                    /* try { // try from 00a4d7af to 00a4d7b3 has its CatchHandler @ 00a4da35 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&local_13)
  ;
                    /* try { // try from 00a4d7c8 to 00a4d7cc has its CatchHandler @ 00a4da25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&local_14);
                    /* try { // try from 00a4d7e1 to 00a4d7e5 has its CatchHandler @ 00a4da15 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&local_15)
  ;
                    /* try { // try from 00a4d7fa to 00a4d7fe has its CatchHandler @ 00a4da06 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&local_16);
                    /* try { // try from 00a4d813 to 00a4d817 has its CatchHandler @ 00a4da04 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&local_17);
                    /* try { // try from 00a4d82c to 00a4d830 has its CatchHandler @ 00a4da02 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&local_18);
                    /* try { // try from 00a4d845 to 00a4d849 has its CatchHandler @ 00a4d9f6 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&local_19);
                    /* try { // try from 00a4d85e to 00a4d862 has its CatchHandler @ 00a4d9f4 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&local_1a);
                    /* try { // try from 00a4d877 to 00a4d87b has its CatchHandler @ 00a4d9f2 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&local_1b);
                    /* try { // try from 00a4d890 to 00a4d894 has its CatchHandler @ 00a4d9e6 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&local_1c);
                    /* try { // try from 00a4d8a9 to 00a4d8ad has its CatchHandler @ 00a4d9e4 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&local_1d);
                    /* try { // try from 00a4d8c2 to 00a4d8c6 has its CatchHandler @ 00a4d9e2 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&local_1e);
                    /* try { // try from 00a4d8db to 00a4d8df has its CatchHandler @ 00a4d9d9 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&local_1f);
                    /* try { // try from 00a4d8f4 to 00a4d8f8 has its CatchHandler @ 00a4d9d7 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&local_20);
                    /* try { // try from 00a4d90d to 00a4d911 has its CatchHandler @ 00a4d9d5 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&local_21);
                    /* try { // try from 00a4d926 to 00a4d92a has its CatchHandler @ 00a4d9c2 */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&local_22);
                    /* try { // try from 00a4d93f to 00a4d943 has its CatchHandler @ 00a4d9bd */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&local_23);
                    /* try { // try from 00a4d958 to 00a4d95c has its CatchHandler @ 00a4d9c4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&local_24);
                    /* try { // try from 00a4d96e to 00a4d972 has its CatchHandler @ 00a4d9bb */
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&local_25);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  return;
}



/* address=00a4db50
   symbol=CAnimationSet::clear */

/* WARNING: Removing unreachable block (ram,0x00a4dd31) */
/* WARNING: Removing unreachable block (ram,0x00a4dd3c) */
/* CAnimationSet::clear() */

void __thiscall CAnimationSet::clear(CAnimationSet *this)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  ulong uVar5;
  long *plVar6;
  ulong uVar7;
  long *plVar8;
  allocator *paVar9;
  uint uVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  uint uVar14;

  puVar13 = *(undefined8 **)(this + 0x60);
  puVar11 = *(undefined8 **)(this + 0x58);
  puVar12 = puVar11;
  if (((long)puVar13 - (long)puVar11 >> 3) * -0x5555555555555555 != 0) {
    uVar5 = 0;
    uVar14 = 0;
    do {
      uVar7 = 0;
      plVar6 = puVar11 + uVar5 * 3;
      uVar10 = 0;
      lVar4 = *plVar6;
      if (plVar6[1] - lVar4 >> 3 != 0) {
        do {
          plVar6 = *(long **)(lVar4 + uVar7 * 8);
          if (plVar6 != (long *)0x0) {
            (**(code **)(*plVar6 + 8))();
            *(undefined8 *)(*(long *)(*(long *)(this + 0x58) + uVar5 * 0x18) + uVar7 * 8) = 0;
          }
          uVar10 = uVar10 + 1;
          uVar7 = (ulong)uVar10;
          plVar6 = (long *)(*(long *)(this + 0x58) + uVar5 * 0x18);
          lVar4 = *plVar6;
        } while (uVar7 < (ulong)(plVar6[1] - lVar4 >> 3));
      }
      plVar6[1] = lVar4;
      puVar13 = *(undefined8 **)(this + 0x60);
      uVar14 = uVar14 + 1;
      puVar11 = *(undefined8 **)(this + 0x58);
      uVar5 = (ulong)uVar14;
      puVar12 = puVar11;
    } while (uVar5 < (ulong)(((long)puVar13 - (long)puVar11 >> 3) * -0x5555555555555555));
  }
  for (; puVar13 != puVar11; puVar11 = puVar11 + 3) {
    if ((void *)*puVar11 != (void *)0x0) {
      operator_delete((void *)*puVar11);
    }
  }
  *(undefined8 **)(this + 0x60) = puVar12;
  plVar3 = *(long **)(this + 0x30);
  plVar6 = *(long **)(this + 0x28);
  for (plVar8 = plVar6; plVar8 != plVar3; plVar8 = plVar8 + 1) {
    paVar9 = (allocator *)(*plVar8 + -0x18);
    if (paVar9 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar8 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy(paVar9);
      }
    }
  }
  *(long **)(this + 0x30) = plVar6;
  plVar6 = *(long **)(this + 0x48);
  plVar3 = *(long **)(this + 0x40);
  for (plVar8 = plVar3; plVar8 != plVar6; plVar8 = plVar8 + 1) {
    paVar9 = (allocator *)(*plVar8 + -0x18);
    if (paVar9 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar8 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar9);
      }
    }
  }
  *(long **)(this + 0x48) = plVar3;
  *(undefined4 *)(this + 0x20) = 0;
  return;
}



/* address=00a4dd50
   symbol=CAnimationSet::~CAnimationSet */

/* WARNING: Removing unreachable block (ram,0x00a4e0d8) */
/* WARNING: Removing unreachable block (ram,0x00a4e0bf) */
/* WARNING: Removing unreachable block (ram,0x00a4e0ca) */
/* CAnimationSet::~CAnimationSet() */

void __thiscall CAnimationSet::~CAnimationSet(CAnimationSet *this)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  long *plVar4;
  undefined8 *puVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  undefined8 *puVar9;
  long *plVar10;
  long lVar11;
  allocator *paVar12;
  uint uVar13;

  puVar9 = *(undefined8 **)(this + 0x60);
  puVar3 = *(undefined8 **)(this + 0x58);
  *(undefined ***)this = &PTR__CAnimationSet_00fdef10;
  if (((long)puVar9 - (long)puVar3 >> 3) * -0x5555555555555555 != 0) {
    uVar6 = 0;
    uVar13 = 0;
    do {
      uVar8 = 0;
      uVar7 = 0;
      plVar4 = puVar3 + uVar6 * 3;
      lVar11 = *plVar4;
      if (plVar4[1] - lVar11 >> 3 != 0) {
        do {
          plVar4 = *(long **)(lVar11 + uVar7 * 8);
          if (plVar4 != (long *)0x0) {
                    /* try { // try from 00a4dddc to 00a4ddde has its CatchHandler @ 00a4df61 */
            (**(code **)(*plVar4 + 8))();
            *(undefined8 *)(*(long *)(*(long *)(this + 0x58) + uVar6 * 0x18) + uVar7 * 8) = 0;
          }
          uVar8 = uVar8 + 1;
          uVar7 = (ulong)uVar8;
          plVar4 = (long *)(*(long *)(this + 0x58) + uVar6 * 0x18);
          lVar11 = *plVar4;
        } while (uVar7 < (ulong)(plVar4[1] - lVar11 >> 3));
      }
      plVar4[1] = lVar11;
      puVar9 = *(undefined8 **)(this + 0x60);
      uVar13 = uVar13 + 1;
      puVar3 = *(undefined8 **)(this + 0x58);
      uVar6 = (ulong)uVar13;
    } while (uVar6 < (ulong)(((long)puVar9 - (long)puVar3 >> 3) * -0x5555555555555555));
  }
  puVar5 = puVar3;
  if (puVar3 != puVar9) {
    do {
      if ((void *)*puVar5 != (void *)0x0) {
        operator_delete((void *)*puVar5);
      }
      puVar5 = puVar5 + 3;
    } while (puVar9 != puVar5);
    puVar5 = *(undefined8 **)(this + 0x58);
  }
  *(undefined8 **)(this + 0x60) = puVar3;
  for (; puVar3 != puVar5; puVar5 = puVar5 + 3) {
    if ((void *)*puVar5 != (void *)0x0) {
      operator_delete((void *)*puVar5);
    }
  }
  if (*(void **)(this + 0x58) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x58));
  }
  plVar4 = *(long **)(this + 0x48);
  for (plVar10 = *(long **)(this + 0x40); plVar4 != plVar10; plVar10 = plVar10 + 1) {
    paVar12 = (allocator *)(*plVar10 + -0x18);
    if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar10 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar12);
      }
    }
  }
  if (*(void **)(this + 0x40) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x40));
  }
  plVar4 = *(long **)(this + 0x30);
  for (plVar10 = *(long **)(this + 0x28); plVar4 != plVar10; plVar10 = plVar10 + 1) {
    paVar12 = (allocator *)(*plVar10 + -0x18);
    if (paVar12 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*plVar10 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy(paVar12);
      }
    }
  }
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x28));
  }
  paVar12 = (allocator *)(*(long *)(this + 0x18) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x18) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00a4e140
   symbol=CAnimationSet::~CAnimationSet */

/* CAnimationSet::~CAnimationSet() */

void __thiscall CAnimationSet::~CAnimationSet(CAnimationSet *this)

{
  ~CAnimationSet(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=5 failures=0 */
