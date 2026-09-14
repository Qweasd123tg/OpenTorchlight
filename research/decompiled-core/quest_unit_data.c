/* Targeted Ghidra class export.
   namespace=CQuestUnitData
   Treat pseudocode as navigation evidence. */


/* address=00d3dc60
   symbol=CQuestUnitData::getDungeonFloorActiveOn */

/* CQuestUnitData::getDungeonFloorActiveOn() */

int __thiscall CQuestUnitData::getDungeonFloorActiveOn(CQuestUnitData *this)

{
  int iVar1;
  int iVar2;

  if (*(int *)(this + 0xa0) != 0) {
    iVar2 = *(int *)(this + 0xa0) + *(int *)(*(long *)(this + 0x18) + 0x20);
    iVar1 = -1;
    if (-1 < iVar2) {
      iVar1 = iVar2;
    }
    iVar2 = *(int *)(*(long *)(this + 0x18) + 0x20);
    if (iVar1 != -1) {
      iVar2 = iVar1;
    }
    return iVar2;
  }
  if (*(int *)(this + 0xa4) != -1) {
    return *(int *)(this + 0xa4);
  }
  return *(int *)(*(long *)(this + 0x18) + 0x20);
}

/* address=00d3dca0
   symbol=CQuestUnitData::getDeepestFloor */

/* CQuestUnitData::getDeepestFloor() */

int __thiscall CQuestUnitData::getDeepestFloor(CQuestUnitData *this)

{
  int iVar1;
  undefined8 *puVar2;
  uint uVar3;
  int iVar4;

  if (*(int *)(this + 0xa0) == 0) {
    iVar4 = *(int *)(this + 0xa4);
    if (iVar4 == -1) {
      iVar4 = 0;
    }
  }
  else {
    iVar1 = *(int *)(this + 0xa0) + *(int *)(*(long *)(this + 0x18) + 0x20);
    iVar4 = 1;
    if (-1 < iVar1) {
      iVar4 = iVar1;
    }
  }
  uVar3 = 0;
  if (*(int *)(this + 0x50) != 0) {
    do {
      if (uVar3 < *(uint *)(this + 0x54)) {
        puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x48);
      }
      iVar1 = getDeepestFloor((CQuestUnitData *)*puVar2);
      if (iVar4 < iVar1) {
        iVar4 = iVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x50));
  }
  return iVar4;
}

/* address=00d3dd20
   symbol=CQuestUnitData::isComplete */

/* CQuestUnitData::isComplete(bool) */

undefined8 __thiscall CQuestUnitData::isComplete(CQuestUnitData *this,bool param_1)

{
  char cVar1;
  uint uVar2;

  if (this[0x60] == (CQuestUnitData)0x0) {
    return 0;
  }
  if ((!param_1) && (*(int *)(this + 0x50) != 0)) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x54)) {
        cVar1 = isComplete(*(CQuestUnitData **)((ulong)uVar2 * 8 + *(long *)(this + 0x48)),false);
      }
      else {
        cVar1 = isComplete((CQuestUnitData *)**(undefined8 **)(this + 0x48),false);
      }
      if (cVar1 == '\0') {
        return 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x50));
  }
  return 1;
}

/* address=00d3dda0
   symbol=CQuestUnitData::save */

/* CQuestUnitData::save(_IO_FILE*) */

void __thiscall CQuestUnitData::save(CQuestUnitData *this,_IO_FILE *param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  CQuestUnitData local_19;

  local_19 = (CQuestUnitData)isComplete(this,false);
  fwrite(&local_19,1,1,param_1);
  local_19 = this[0xb9];
  fwrite(&local_19,1,1,param_1);
  local_20 = *(undefined4 *)(this + 0x38);
  fwrite(&local_20,4,1,param_1);
  fwrite(this + 0x3c,4,1,param_1);
  local_24 = *(undefined4 *)(this + 0x10);
  fwrite(&local_24,4,1,param_1);
  fwrite(this + 0x30,8,1,param_1);
  local_28 = *(int *)(this + 0x50);
  fwrite(&local_28,4,1,param_1);
  if ((local_28 != 0) && (*(int *)(this + 0x50) != 0)) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x54)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x48);
      }
      uVar2 = uVar2 + 1;
      save((CQuestUnitData *)*puVar1,param_1);
    } while (uVar2 < *(uint *)(this + 0x50));
  }
  return;
}

/* address=00d3ded0
   symbol=CQuestUnitData::spawnUnit */

/* CQuestUnitData::spawnUnit(CResourceManager*, Ogre::Vector3 const&) */

CBaseUnit * __thiscall
CQuestUnitData::spawnUnit(CQuestUnitData *this,CResourceManager *param_1,Vector3 *param_2)

{
  int iVar1;
  CLevel *this_00;
  int iVar2;
  CBaseUnit *pCVar3;
  CCharacter *pCVar4;
  CItem *this_01;
  wstring_conflict awStack_38 [15];
  allocator local_29;

  if ((((param_1 == (CResourceManager *)0x0) || (*(CDataGroup **)(this + 0x20) == (CDataGroup *)0x0)
       ) || (this_00 = *(CLevel **)(param_1 + 0x18), this_00 == (CLevel *)0x0)) ||
     (this[0x60] != (CQuestUnitData)0x0)) {
    pCVar3 = (CBaseUnit *)0x0;
  }
  else {
    pCVar3 = (CBaseUnit *)
             CResourceManager::createUnit
                       (param_1,*(CDataGroup **)(this + 0x20),*(int *)(this_00 + 0x1a8),false,false)
    ;
    if (pCVar3 != (CBaseUnit *)0x0) {
      CLevel::addUnit(this_00,pCVar3,param_2);
      *(undefined8 *)(pCVar3 + 0x170) = *(undefined8 *)(*(long *)(this + 0x18) + 0x1c8);
      *(undefined4 *)(pCVar3 + 0x178) = *(undefined4 *)(this + 0x10);
      if (this[0x61] != (CQuestUnitData)0x0) {
        pCVar4 = (CCharacter *)__dynamic_cast(pCVar3,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
        if (pCVar4 != (CCharacter *)0x0) {
                    /* try { // try from 00d3dfb0 to 00d3dfb4 has its CatchHandler @ 00d3e048 */
          std::wstring::wstring(awStack_38,L"CHAMPION",&local_29);
          iVar1 = *(int *)(this_00 + 0x1a8);
                    /* try { // try from 00d3dfc3 to 00d3dfdd has its CatchHandler @ 00d3e035 */
          iVar2 = UTILITIES::randomIntegerBetween(0,2);
          CCharacter::makeChampion(pCVar4,this + 0xc0,iVar2 + iVar1,awStack_38);
                    /* try { // try from 00d3dfe1 to 00d3dfe5 has its CatchHandler @ 00d3e048 */
          std::wstring::~wstring(awStack_38);
          CQuestManager::calculateNPCIcon
                    (*(CQuestManager **)(*(long *)(this + 0x18) + 0x1d0),pCVar4);
        }
      }
      this_01 = (CItem *)__dynamic_cast(pCVar3,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0);
      if (this_01 != (CItem *)0x0) {
        this_01[0x348] = (CItem)0x1;
        CItem::destroyItemText(this_01);
        CItem::destroyItemText(this_01);
      }
    }
  }
  return pCVar3;
}

/* address=00d3e050
   symbol=CQuestUnitData::spawnChildrenUnits */

/* CQuestUnitData::spawnChildrenUnits(CResourceManager*, Ogre::Vector3 const&) */

void CQuestUnitData::spawnChildrenUnits(CResourceManager *param_1,Vector3 *param_2)

{
  CLevel *this;
  undefined8 *puVar1;
  Vector3 *in_RDX;
  uint uVar2;
  ulong uVar3;
  long *plVar4;
  float fVar5;
  undefined4 local_48;
  float fStack_44;
  undefined8 uVar6;

  if (((param_2 != (Vector3 *)0x0) && (this = *(CLevel **)(param_2 + 0x18), this != (CLevel *)0x0))
     && (*(int *)(param_1 + 0x50) != 0)) {
    uVar2 = 0;
    do {
      uVar3 = (ulong)uVar2;
      fVar5 = (float)uVar3 * DAT_00fa4810;
      if ((float)uVar3 * DAT_00fa4810 <= DAT_00fa47fc) {
        fVar5 = DAT_00fa47fc;
      }
      uVar6 = CLevel::randomOpenPosition(this,in_RDX,fVar5,false);
      _local_48 = CONCAT44(DAT_00fce498 + (float)((ulong)uVar6 >> 0x20),(int)uVar6);
      if (uVar2 < *(uint *)(param_1 + 0x54)) {
        puVar1 = (undefined8 *)(uVar3 * 8 + *(long *)(param_1 + 0x48));
      }
      else {
        puVar1 = *(undefined8 **)(param_1 + 0x48);
      }
      spawnUnit((CQuestUnitData *)*puVar1,(CResourceManager *)param_2,(Vector3 *)&local_48);
      if (uVar2 < *(uint *)(param_1 + 0x54)) {
        plVar4 = (long *)(uVar3 * 8 + *(long *)(param_1 + 0x48));
      }
      else {
        plVar4 = *(long **)(param_1 + 0x48);
      }
      uVar2 = uVar2 + 1;
      *(undefined1 *)(*plVar4 + 0xb9) = 1;
    } while (uVar2 < *(uint *)(param_1 + 0x50));
  }
  return;
}

/* address=00d3e160
   symbol=CQuestUnitData::createUnit */

/* CQuestUnitData::createUnit(CLevel*) */

CPositionableObject * CQuestUnitData::createUnit(CLevel *param_1)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  CPositionableObject *pCVar4;
  CLevel *pCVar5;
  undefined8 *puVar6;
  long lVar7;
  int iVar8;
  long in_RSI;
  long *plVar9;
  ulong uVar10;
  float fVar11;
  float fVar12;
  undefined4 in_XMM1_Db;
  float local_dc;
  undefined8 *local_c8;
  int local_c0;
  uint local_bc;
  undefined4 local_b8;
  undefined8 local_a8;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_88 [2];
  undefined8 local_78 [2];
  undefined8 local_68 [2];
  undefined8 local_58;
  float local_50;
  wstring_conflict local_48 [24];

  if ((param_1[99] == (CLevel)0x0) || (in_RSI == 0)) {
    return (CPositionableObject *)0x0;
  }
  plVar9 = (long *)(in_RSI + 0xf0);
  if (*(int *)(param_1 + 0xb4) != 0) {
    if (*(int *)(param_1 + 0xb4) != 1) goto LAB_00d3e340;
    plVar9 = (long *)(in_RSI + 0x108);
  }
  if ((plVar9 != (long *)0x0) && (*(uint *)(plVar9 + 1) != 0)) {
    fVar12 = (float)*(uint *)(plVar9 + 1);
    fVar11 = (float)UTILITIES::randomBetween(DAT_00fa47fc,fVar12);
    uVar10 = (ulong)(fVar11 - DAT_00fa47fc);
    if ((uint)uVar10 < *(uint *)((long)plVar9 + 0xc)) {
      puVar6 = (undefined8 *)((uVar10 & 0xffffffff) * 8 + *plVar9);
    }
    else {
      puVar6 = (undefined8 *)*plVar9;
    }
    local_58 = CPositionableObject::getPosition((CPositionableObject *)*puVar6,true);
    local_50 = fVar12;
    pCVar4 = (CPositionableObject *)
             spawnUnit((CQuestUnitData *)param_1,
                       *(CResourceManager **)(*(long *)(param_1 + 0x18) + 0x1d8),
                       (Vector3 *)&local_58);
    if (pCVar4 == (CPositionableObject *)0x0) {
      return (CPositionableObject *)0x0;
    }
    pcVar1 = *(code **)(*(long *)pCVar4 + 0x108);
    if ((uint)uVar10 < *(uint *)((long)plVar9 + 0xc)) {
      puVar6 = (undefined8 *)((uVar10 & 0xffffffff) * 8 + *plVar9);
    }
    else {
      puVar6 = (undefined8 *)*plVar9;
    }
    local_a8 = (**(code **)(*(long *)*puVar6 + 0xf0))();
    local_a0 = CONCAT44(in_XMM1_Db,fVar12);
    (*pcVar1)(pCVar4,&local_a8);
    pCVar5 = (CLevel *)__dynamic_cast(pCVar4,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
    if (pCVar5 != (CLevel *)0x0) {
      CQuestManager::calculateNPCIcon
                (*(CQuestManager **)(*(long *)(param_1 + 0x18) + 0x1d0),(CCharacter *)pCVar5);
      cVar2 = std::operator==((wstring_conflict *)(param_1 + 0x70),
                              (wstring_conflict *)&::EMPTY_WSTRING);
      if (cVar2 == '\0') {
        std::wstring::wstring(local_48,(wstring_conflict *)(param_1 + 0x70));
                    /* try { // try from 00d3e313 to 00d3e317 has its CatchHandler @ 00d3e5f5 */
        std::wstring::assign((wstring_conflict *)(pCVar5 + 0x4c0));
        std::wstring::~wstring(local_48);
      }
      CCharacter::dropToGround(pCVar5,DAT_00fa8768,SUB81(in_RSI,0));
      return pCVar4;
    }
    lVar7 = __dynamic_cast(pCVar4,&CBaseUnit::typeinfo,&CItem::typeinfo,0);
    if (lVar7 == 0) {
      return pCVar4;
    }
    CItem::snapToGround();
    return pCVar4;
  }
LAB_00d3e340:
  local_c8 = (undefined8 *)0x0;
  local_c0 = 0;
  local_bc = 0;
  local_b8 = 10;
                    /* try { // try from 00d3e36e to 00d3e523 has its CatchHandler @ 00d3e5e2 */
  CLevel::getUnitsByUnitType();
  uVar3 = UTILITIES::randomIntegerBetween(0,local_c0 + -1);
  puVar6 = local_c8;
  if (uVar3 < local_bc) {
    puVar6 = local_c8 + uVar3;
  }
  pCVar4 = (CPositionableObject *)*puVar6;
  if (pCVar4 != (CPositionableObject *)0x0) {
    local_78[0] = CPositionableObject::getPosition(pCVar4,true);
    pCVar5 = (CLevel *)0x0;
    if (*(long *)(pCVar4 + 0x68) != 0) {
      pCVar5 = *(CLevel **)(*(long *)(pCVar4 + 0x68) + 0x18);
    }
    local_68[0] = CLevel::randomOpenPosition(pCVar5,(Vector3 *)local_78,DAT_00fa86e0,false);
    iVar8 = 0;
    local_dc = DAT_00fa86e0;
    while( true ) {
      pCVar5 = (CLevel *)0x0;
      if (*(long *)(pCVar4 + 0x68) != 0) {
        pCVar5 = *(CLevel **)(*(long *)(pCVar4 + 0x68) + 0x18);
      }
      cVar2 = CLevel::isInNoSpawnRegion(pCVar5,(Vector3 *)local_68,0.0);
      if ((cVar2 == '\0') || (iVar8 == 0x29)) break;
      uVar3 = UTILITIES::randomIntegerBetween(0,local_c0 + -1);
      puVar6 = local_c8;
      if (uVar3 < local_bc) {
        puVar6 = local_c8 + uVar3;
      }
      pCVar4 = (CPositionableObject *)*puVar6;
      local_88[0] = CPositionableObject::getPosition(pCVar4,true);
      pCVar5 = (CLevel *)0x0;
      if (*(long *)(pCVar4 + 0x68) != 0) {
        pCVar5 = *(CLevel **)(*(long *)(pCVar4 + 0x68) + 0x18);
      }
      local_98 = CLevel::randomOpenPosition(pCVar5,(Vector3 *)local_88,local_dc,false);
      iVar8 = iVar8 + 1;
      local_dc = DAT_00fce520 + local_dc;
      local_68[0] = local_98;
    }
    spawnUnit((CQuestUnitData *)param_1,*(CResourceManager **)(pCVar4 + 0x68),(Vector3 *)local_68);
  }
  TArrayList<CBaseUnit*>::~TArrayList((TArrayList<CBaseUnit*> *)&local_c8);
  return pCVar4;
}

/* address=00d3e610
   symbol=CQuestUnitData::CQuestUnitData */

/* CQuestUnitData::CQuestUnitData(CQuest*) */

void __thiscall CQuestUnitData::CQuestUnitData(CQuestUnitData *this,CQuest *param_1)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuestUnitData_00ff7df0;
  *(int *)(this + 0x10) = m_gQuestUnitDataID;
  m_gQuestUnitDataID = m_gQuestUnitDataID + 1;
  *(CQuest **)(this + 0x18) = param_1;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0xffffffffffffffff;
  *(undefined4 *)(this + 0x38) = 1;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 0x16;
  *(undefined4 *)(this + 0x44) = 0x16;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 10;
  this[0x60] = (CQuestUnitData)0x0;
  this[0x61] = (CQuestUnitData)0x0;
  this[0x62] = (CQuestUnitData)0x1;
  this[99] = (CQuestUnitData)0x1;
  this[100] = (CQuestUnitData)0x1;
  *(undefined4 **)(this + 0x68) = &DAT_01424558;
                    /* try { // try from 00d3e6b4 to 00d3e6b8 has its CatchHandler @ 00d3e749 */
  std::wstring::wstring((wstring_conflict *)(this + 0x70),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 **)(this + 0x78) = &DAT_01424558;
  *(undefined4 **)(this + 0x80) = &DAT_01424558;
  *(undefined4 **)(this + 0x88) = &DAT_01424558;
  *(undefined4 **)(this + 0x90) = &DAT_01424558;
  *(undefined4 **)(this + 0x98) = &DAT_01424558;
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa4) = 0xffffffff;
  *(undefined4 *)(this + 0xa8) = 1;
  *(undefined4 *)(this + 0xac) = 1;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  this[0xb8] = (CQuestUnitData)0x1;
  this[0xb9] = (CQuestUnitData)0x0;
  *(undefined4 **)(this + 0xc0) = &DAT_01424558;
  return;
}

/* address=00d45860
   symbol=CQuestUnitData::_GLOBAL__I_CQuestUnitData */

/* CQuestUnitData::CQuestUnitData(CQuest*) */

void CQuestUnitData::_GLOBAL__I_CQuestUnitData(void)

{
  allocator aStack_2ab;
  allocator aStack_2aa;
  allocator aStack_2a9;
  allocator aStack_2a8;
  allocator aStack_2a7;
  allocator aStack_2a6;
  allocator aStack_2a5;
  allocator aStack_2a4;
  allocator aStack_2a3;
  allocator aStack_2a2;
  allocator aStack_2a1;
  allocator aStack_2a0;
  allocator aStack_29f;
  allocator aStack_29e;
  allocator aStack_29d;
  allocator aStack_29c;
  allocator aStack_29b;
  allocator aStack_29a;
  allocator aStack_299;
  allocator aStack_298;
  allocator aStack_297;
  allocator aStack_296;
  allocator aStack_295;
  allocator aStack_294;
  allocator aStack_293;
  allocator aStack_292;
  allocator aStack_291;
  allocator aStack_290;
  allocator aStack_28f;
  allocator aStack_28e;
  allocator aStack_28d;
  allocator aStack_28c;
  allocator aStack_28b;
  allocator aStack_28a;
  allocator aStack_289;
  allocator aStack_288;
  allocator aStack_287;
  allocator aStack_286;
  allocator aStack_285;
  allocator aStack_284;
  allocator aStack_283;
  allocator aStack_282;
  allocator aStack_281;
  allocator aStack_280;
  allocator aStack_27f;
  allocator aStack_27e;
  allocator aStack_27d;
  allocator aStack_27c;
  allocator aStack_27b;
  allocator aStack_27a;
  allocator aStack_279;
  allocator aStack_278;
  allocator aStack_277;
  allocator aStack_276;
  allocator aStack_275;
  allocator aStack_274;
  allocator aStack_273;
  allocator aStack_272;
  allocator aStack_271;
  allocator aStack_270;
  allocator aStack_26f;
  allocator aStack_26e;
  allocator aStack_26d;
  allocator aStack_26c;
  allocator aStack_26b;
  allocator aStack_26a;
  allocator aStack_269;
  allocator aStack_268;
  allocator aStack_267;
  allocator aStack_266;
  allocator aStack_265;
  allocator aStack_264;
  allocator aStack_263;
  allocator aStack_262;
  allocator aStack_261;
  allocator aStack_260;
  allocator aStack_25f;
  allocator aStack_25e;
  allocator aStack_25d;
  allocator aStack_25c;
  allocator aStack_25b;
  allocator aStack_25a;
  allocator aStack_259;
  allocator aStack_258;
  allocator aStack_257;
  allocator aStack_256;
  allocator aStack_255;
  allocator aStack_254;
  allocator aStack_253;
  allocator aStack_252;
  allocator aStack_251;
  allocator aStack_250;
  allocator aStack_24f;
  allocator aStack_24e;
  allocator aStack_24d;
  allocator aStack_24c;
  allocator aStack_24b;
  allocator aStack_24a;
  allocator aStack_249;
  allocator aStack_248;
  allocator aStack_247;
  allocator aStack_246;
  allocator aStack_245;
  allocator aStack_244;
  allocator aStack_243;
  allocator aStack_242;
  allocator aStack_241;
  allocator aStack_240;
  allocator aStack_23f;
  allocator aStack_23e;
  allocator aStack_23d;
  allocator aStack_23c;
  allocator aStack_23b;
  allocator aStack_23a;
  allocator aStack_239;
  allocator aStack_238;
  allocator aStack_237;
  allocator aStack_236;
  allocator aStack_235;
  allocator aStack_234;
  allocator aStack_233;
  allocator aStack_232;
  allocator aStack_231;
  allocator aStack_230;
  allocator aStack_22f;
  allocator aStack_22e;
  allocator aStack_22d;
  allocator aStack_22c;
  allocator aStack_22b;
  allocator aStack_22a;
  allocator aStack_229;
  allocator aStack_228;
  allocator aStack_227;
  allocator aStack_226;
  allocator aStack_225;
  allocator aStack_224;
  allocator aStack_223;
  allocator aStack_222;
  allocator aStack_221;
  allocator aStack_220;
  allocator aStack_21f;
  allocator aStack_21e;
  allocator aStack_21d;
  allocator aStack_21c;
  allocator aStack_21b;
  allocator aStack_21a;
  allocator aStack_219;
  allocator aStack_218;
  allocator aStack_217;
  allocator aStack_216;
  allocator aStack_215;
  allocator aStack_214;
  allocator aStack_213;
  allocator aStack_212;
  allocator aStack_211;
  allocator aStack_210;
  allocator aStack_20f;
  allocator aStack_20e;
  allocator aStack_20d;
  allocator aStack_20c;
  allocator aStack_20b;
  allocator aStack_20a;
  allocator aStack_209;
  allocator aStack_208;
  allocator aStack_207;
  allocator aStack_206;
  allocator aStack_205;
  allocator aStack_204;
  allocator aStack_203;
  allocator aStack_202;
  allocator aStack_201;
  allocator aStack_200;
  allocator aStack_1ff;
  allocator aStack_1fe;
  allocator aStack_1fd;
  allocator aStack_1fc;
  allocator aStack_1fb;
  allocator aStack_1fa;
  allocator aStack_1f9;
  allocator aStack_1f8;
  allocator aStack_1f7;
  allocator aStack_1f6;
  allocator aStack_1f5;
  allocator aStack_1f4;
  allocator aStack_1f3;
  allocator aStack_1f2;
  allocator aStack_1f1;
  allocator aStack_1f0;
  allocator aStack_1ef;
  allocator aStack_1ee;
  allocator aStack_1ed;
  allocator aStack_1ec;
  allocator aStack_1eb;
  allocator aStack_1ea;
  allocator aStack_1e9;
  allocator aStack_1e8;
  allocator aStack_1e7;
  allocator aStack_1e6;
  allocator aStack_1e5;
  allocator aStack_1e4;
  allocator aStack_1e3;
  allocator aStack_1e2;
  allocator aStack_1e1;
  allocator aStack_1e0;
  allocator aStack_1df;
  allocator aStack_1de;
  allocator aStack_1dd;
  allocator aStack_1dc;
  allocator aStack_1db;
  allocator aStack_1da;
  allocator aStack_1d9;
  allocator aStack_1d8;
  allocator aStack_1d7;
  allocator aStack_1d6;
  allocator aStack_1d5;
  allocator aStack_1d4;
  allocator aStack_1d3;
  allocator aStack_1d2;
  allocator aStack_1d1;
  allocator aStack_1d0;
  allocator aStack_1cf;
  allocator aStack_1ce;
  allocator aStack_1cd;
  allocator aStack_1cc;
  allocator aStack_1cb;
  allocator aStack_1ca;
  allocator aStack_1c9;
  allocator aStack_1c8;
  allocator aStack_1c7;
  allocator aStack_1c6;
  allocator aStack_1c5;
  allocator aStack_1c4;
  allocator aStack_1c3;
  allocator aStack_1c2;
  allocator aStack_1c1;
  allocator aStack_1c0;
  allocator aStack_1bf;
  allocator aStack_1be;
  allocator aStack_1bd;
  allocator aStack_1bc;
  allocator aStack_1bb;
  allocator aStack_1ba;
  allocator aStack_1b9;
  allocator aStack_1b8;
  allocator aStack_1b7;
  allocator aStack_1b6;
  allocator aStack_1b5;
  allocator aStack_1b4;
  allocator aStack_1b3;
  allocator aStack_1b2;
  allocator aStack_1b1;
  allocator aStack_1b0;
  allocator aStack_1af;
  allocator aStack_1ae;
  allocator aStack_1ad;
  allocator aStack_1ac;
  allocator aStack_1ab;
  allocator aStack_1aa;
  allocator aStack_1a9;
  allocator aStack_1a8;
  allocator aStack_1a7;
  allocator aStack_1a6;
  allocator aStack_1a5;
  allocator aStack_1a4;
  allocator aStack_1a3;
  allocator aStack_1a2;
  allocator aStack_1a1;
  allocator aStack_1a0;
  allocator aStack_19f;
  allocator aStack_19e;
  allocator aStack_19d;
  allocator aStack_19c;
  allocator aStack_19b;
  allocator aStack_19a;
  allocator aStack_199;
  allocator aStack_198;
  allocator aStack_197;
  allocator aStack_196;
  allocator aStack_195;
  allocator aStack_194;
  allocator aStack_193;
  allocator aStack_192;
  allocator aStack_191;
  allocator aStack_190;
  allocator aStack_18f;
  allocator aStack_18e;
  allocator aStack_18d;
  allocator aStack_18c;
  allocator aStack_18b;
  allocator aStack_18a;
  allocator aStack_189;
  allocator aStack_188;
  allocator aStack_187;
  allocator aStack_186;
  allocator aStack_185;
  allocator aStack_184;
  allocator aStack_183;
  allocator aStack_182;
  allocator aStack_181;
  allocator aStack_180;
  allocator aStack_17f;
  allocator aStack_17e;
  allocator aStack_17d;
  allocator aStack_17c;
  allocator aStack_17b;
  allocator aStack_17a;
  allocator aStack_179;
  allocator aStack_178;
  allocator aStack_177;
  allocator aStack_176;
  allocator aStack_175;
  allocator aStack_174;
  allocator aStack_173;
  allocator aStack_172;
  allocator aStack_171;
  allocator aStack_170;
  allocator aStack_16f;
  allocator aStack_16e;
  allocator aStack_16d;
  allocator aStack_16c;
  allocator aStack_16b;
  allocator aStack_16a;
  allocator aStack_169;
  allocator aStack_168;
  allocator aStack_167;
  allocator aStack_166;
  allocator aStack_165;
  allocator aStack_164;
  allocator aStack_163;
  allocator aStack_162;
  allocator aStack_161;
  allocator aStack_160;
  allocator aStack_15f;
  allocator aStack_15e;
  allocator aStack_15d;
  allocator aStack_15c;
  allocator aStack_15b;
  allocator aStack_15a;
  allocator aStack_159;
  allocator aStack_158;
  allocator aStack_157;
  allocator aStack_156;
  allocator aStack_155;
  allocator aStack_154;
  allocator aStack_153;
  allocator aStack_152;
  allocator aStack_151;
  allocator aStack_150;
  allocator aStack_14f;
  allocator aStack_14e;
  allocator aStack_14d;
  allocator aStack_14c;
  allocator aStack_14b;
  allocator aStack_14a;
  allocator aStack_149;
  allocator aStack_148;
  allocator aStack_147;
  allocator aStack_146;
  allocator aStack_145;
  allocator aStack_144;
  allocator aStack_143;
  allocator aStack_142;
  allocator aStack_141;
  allocator aStack_140;
  allocator aStack_13f;
  allocator aStack_13e;
  allocator aStack_13d;
  allocator aStack_13c;
  allocator aStack_13b;
  allocator aStack_13a;
  allocator aStack_139;
  allocator aStack_138;
  allocator aStack_137;
  allocator aStack_136;
  allocator aStack_135;
  allocator aStack_134;
  allocator aStack_133;
  allocator aStack_132;
  allocator aStack_131;
  allocator aStack_130;
  allocator aStack_12f;
  allocator aStack_12e;
  allocator aStack_12d;
  allocator aStack_12c;
  allocator aStack_12b;
  allocator aStack_12a;
  allocator aStack_129;
  allocator aStack_128;
  allocator aStack_127;
  allocator aStack_126;
  allocator aStack_125;
  allocator aStack_124;
  allocator aStack_123;
  allocator aStack_122;
  allocator aStack_121;
  allocator aStack_120;
  allocator aStack_11f;
  allocator aStack_11e;
  allocator aStack_11d;
  allocator aStack_11c;
  allocator aStack_11b;
  allocator aStack_11a;
  allocator aStack_119;
  allocator aStack_118;
  allocator aStack_117;
  allocator aStack_116;
  allocator aStack_115;
  allocator aStack_114;
  allocator aStack_113;
  allocator aStack_112;
  allocator aStack_111;
  allocator aStack_110;
  allocator aStack_10f;
  allocator aStack_10e;
  allocator aStack_10d;
  allocator aStack_10c;
  allocator aStack_10b;
  allocator aStack_10a;
  allocator aStack_109;
  allocator aStack_108;
  allocator aStack_107;
  allocator aStack_106;
  allocator aStack_105;
  allocator aStack_104;
  allocator aStack_103;
  allocator aStack_102;
  allocator aStack_101;
  allocator aStack_100;
  allocator aStack_ff;
  allocator aStack_fe;
  allocator aStack_fd;
  allocator aStack_fc;
  allocator aStack_fb;
  allocator aStack_fa;
  allocator aStack_f9;
  allocator aStack_f8;
  allocator aStack_f7;
  allocator aStack_f6;
  allocator aStack_f5;
  allocator aStack_f4;
  allocator aStack_f3;
  allocator aStack_f2;
  allocator aStack_f1;
  allocator aStack_f0;
  allocator aStack_ef;
  allocator aStack_ee;
  allocator aStack_ed;
  allocator aStack_ec;
  allocator aStack_eb;
  allocator aStack_ea;
  allocator aStack_e9;
  allocator aStack_e8;
  allocator aStack_e7;
  allocator aStack_e6;
  allocator aStack_e5;
  allocator aStack_e4;
  allocator aStack_e3;
  allocator aStack_e2;
  allocator aStack_e1;
  allocator aStack_e0;
  allocator aStack_df;
  allocator aStack_de;
  allocator aStack_dd;
  allocator aStack_dc;
  allocator aStack_db;
  allocator aStack_da;
  allocator aStack_d9;
  allocator aStack_d8;
  allocator aStack_d7;
  allocator aStack_d6;
  allocator aStack_d5;
  allocator aStack_d4;
  allocator aStack_d3;
  allocator aStack_d2;
  allocator aStack_d1;
  allocator aStack_d0;
  allocator aStack_cf;
  allocator aStack_ce;
  allocator aStack_cd;
  allocator aStack_cc;
  allocator aStack_cb;
  allocator aStack_ca;
  allocator aStack_c9;
  allocator aStack_c8;
  allocator aStack_c7;
  allocator aStack_c6;
  allocator aStack_c5;
  allocator aStack_c4;
  allocator aStack_c3;
  allocator aStack_c2;
  allocator aStack_c1;
  allocator aStack_c0;
  allocator aStack_bf;
  allocator aStack_be;
  allocator aStack_bd;
  allocator aStack_bc;
  allocator aStack_bb;
  allocator aStack_ba;
  allocator aStack_b9;
  allocator aStack_b8;
  allocator aStack_b7;
  allocator aStack_b6;
  allocator aStack_b5;
  allocator aStack_b4;
  allocator aStack_b3;
  allocator aStack_b2;
  allocator aStack_b1;
  allocator aStack_b0;
  allocator aStack_af;
  allocator aStack_ae;
  allocator aStack_ad;
  allocator aStack_ac;
  allocator aStack_ab;
  allocator aStack_aa;
  allocator aStack_a9;
  allocator aStack_a8;
  allocator aStack_a7;
  allocator aStack_a6;
  allocator aStack_a5;
  allocator aStack_a4;
  allocator aStack_a3;
  allocator aStack_a2;
  allocator aStack_a1;
  allocator aStack_a0;
  allocator aStack_9f;
  allocator aStack_9e;
  allocator aStack_9d;
  allocator aStack_9c;
  allocator aStack_9b;
  allocator aStack_9a;
  allocator aStack_99;
  allocator aStack_98;
  allocator aStack_97;
  allocator aStack_96;
  allocator aStack_95;
  allocator aStack_94;
  allocator aStack_93;
  allocator aStack_92;
  allocator aStack_91;
  allocator aStack_90;
  allocator aStack_8f;
  allocator aStack_8e;
  allocator aStack_8d;
  allocator aStack_8c;
  allocator aStack_8b;
  allocator aStack_8a;
  allocator aStack_89;
  allocator aStack_88;
  allocator aStack_87;
  allocator aStack_86;
  allocator aStack_85;
  allocator aStack_84;
  allocator aStack_83;
  allocator aStack_82;
  allocator aStack_81;
  allocator aStack_80;
  allocator aStack_7f;
  allocator aStack_7e;
  allocator aStack_7d;
  allocator aStack_7c;
  allocator aStack_7b;
  allocator aStack_7a;
  allocator aStack_79;
  allocator aStack_78;
  allocator aStack_77;
  allocator aStack_76;
  allocator aStack_75;
  allocator aStack_74;
  allocator aStack_73;
  allocator aStack_72;
  allocator aStack_71;
  allocator aStack_70;
  allocator aStack_6f;
  allocator aStack_6e;
  allocator aStack_6d;
  allocator aStack_6c;
  allocator aStack_6b;
  allocator aStack_6a;
  allocator aStack_69;
  allocator aStack_68;
  allocator aStack_67;
  allocator aStack_66;
  allocator aStack_65;
  allocator aStack_64;
  allocator aStack_63;
  allocator aStack_62;
  allocator aStack_61;
  allocator aStack_60;
  allocator aStack_5f;
  allocator aStack_5e;
  allocator aStack_5d;
  allocator aStack_5c;
  allocator aStack_5b;
  allocator aStack_5a;
  allocator aStack_59;
  allocator aStack_58;
  allocator aStack_57;
  allocator aStack_56;
  allocator aStack_55;
  allocator aStack_54;
  allocator aStack_53;
  allocator aStack_52;
  allocator aStack_51;
  allocator aStack_50;
  allocator aStack_4f;
  allocator aStack_4e;
  allocator aStack_4d;
  allocator aStack_4c;
  allocator aStack_4b;
  allocator aStack_4a;
  allocator aStack_49;
  allocator aStack_48;
  allocator aStack_47;
  allocator aStack_46;
  allocator aStack_45;
  allocator aStack_44;
  allocator aStack_43;
  allocator aStack_42;
  allocator aStack_41;
  allocator aStack_40;
  allocator aStack_3f;
  allocator aStack_3e;
  allocator aStack_3d;
  allocator aStack_3c;
  allocator aStack_3b;
  allocator aStack_3a;
  allocator aStack_39;
  allocator aStack_38;
  allocator aStack_37;
  allocator aStack_36;
  allocator aStack_35;
  allocator aStack_34;
  allocator aStack_33;
  allocator aStack_32;
  allocator aStack_31;
  allocator aStack_30;
  allocator aStack_2f;
  allocator aStack_2e;
  allocator aStack_2d;
  allocator aStack_2c;
  allocator aStack_2b;
  allocator aStack_2a;
  allocator aaStack_29 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_2aa);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_2a9);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_2a8);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_2a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_2a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_2a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_2a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_2a2);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES,L"",&aStack_2a1);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 8),
             L"LEVEL_QUEST_MONSTERS",&aStack_2a0);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 0x10),
             L"LEVEL_QUEST_CHAMPIONS",&aStack_29f);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 0x18),
             L"LEVEL_QUEST_ITEMS",&aStack_29e);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_29d);
  std::wstring::wstring((wstring_conflict *)&DAT_014ff248,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_29c)
  ;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_29b);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_299)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_298);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_297)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_296);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_295);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_294);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_293);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_292);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_291);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_290);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_28f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_28e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_28d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_28c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_28b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_28a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_289);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_288);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_227);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_225);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_224);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_223);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_220);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_21b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_219)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_218)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_217)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_216)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_215)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_214)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_212);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_211);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_206)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_204)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1f5
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1f2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1f0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1ef)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1e6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1e5);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1de);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1d7);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1d0);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)&DAT_014ff928,L"ITEM",&aStack_1ce);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1ca)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1c6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1c3);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_e1);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_de);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_dd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_d8);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_d7);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_d6);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_d5
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_d4);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_d3);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_d2);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_d1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_d0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_cf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_ce);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_cd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_cc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_cb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_ca);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_c9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_c8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_c7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_c6);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_c5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_c4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_c3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_c2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_c1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_c0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_bf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_be);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_bd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_bc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_bb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_ba);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_b9);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_b8);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_b7);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_b6);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_b5);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_b4);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_b3);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_b2);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_b1);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_b0);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_af);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_ae);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_a9);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_a4);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_a2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_a0)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_95)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_90)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_82);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",&aStack_7e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_77);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_74);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_6c);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_56);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_47)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_46)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_45)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_44)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_43)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_42)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_41)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_40)
  ;
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_3f);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_39);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gPROPERTY_NODE_TYPE_NAMES,L"Point of Interest",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 8),L"Player Start",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x10),L"Editor Player Start",
             &aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x18),L"No Spawn Region",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x20),L"Entrance",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x28),L"Exit",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x30),L"Jump Down Area",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x38),L"Town Portal",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x40),L"Path Node Occupation Circle",
             &aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x48),L"Path Node Occupation Box",
             &aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x50),L"Camera Position",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x58),L"Camera Target",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x60),L"Quest Item",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x68),L"Quest Boss",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x70),L"Waypoint",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x78),L"Waypoint Start",aaStack_29);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  return;
}

/* address=00d45ac0
   symbol=CQuestUnitData::getIsRandom */

/* CQuestUnitData::getIsRandom() */

undefined8 __thiscall CQuestUnitData::getIsRandom(CQuestUnitData *this)

{
  size_t __n;
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;

  if (*(int *)(this + 0xa8) == *(int *)(this + 0xac)) {
    __n = *(size_t *)(*(wchar_t **)(this + 0x78) + -6);
    if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
       (iVar2 = wmemcmp(*(wchar_t **)(this + 0x78),::EMPTY_WSTRING,__n), iVar2 == 0)) {
      if (*(int *)(this + 0x50) != 0) {
        uVar4 = 0;
        do {
          if (uVar4 < *(uint *)(this + 0x54)) {
            puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x48);
          }
          cVar1 = getIsRandom((CQuestUnitData *)*puVar3);
          if (cVar1 != '\0') {
            return 1;
          }
          uVar4 = uVar4 + 1;
        } while (uVar4 < *(uint *)(this + 0x50));
      }
      return 0;
    }
  }
  return 1;
}

/* address=00d467d0
   symbol=CQuestUnitData::~CQuestUnitData */

/* WARNING: Removing unreachable block (ram,0x00d46a08) */
/* WARNING: Removing unreachable block (ram,0x00d46a70) */
/* WARNING: Removing unreachable block (ram,0x00d46ad8) */
/* WARNING: Removing unreachable block (ram,0x00d46b40) */
/* WARNING: Removing unreachable block (ram,0x00d46b35) */
/* WARNING: Removing unreachable block (ram,0x00d46acd) */
/* WARNING: Removing unreachable block (ram,0x00d46a65) */
/* WARNING: Removing unreachable block (ram,0x00d469fd) */
/* CQuestUnitData::~CQuestUnitData() */

void __thiscall CQuestUnitData::~CQuestUnitData(CQuestUnitData *this)

{
  allocator *paVar1;
  int *piVar2;
  long lVar3;
  int iVar4;
  long *plVar5;
  uint uVar6;

  *(undefined ***)this = &PTR__CQuestUnitData_00ff7df0;
  if (*(int *)(this + 0x50) != 0) {
    uVar6 = 0;
    do {
      lVar3 = (ulong)uVar6 * 8;
      plVar5 = (long *)(lVar3 + *(long *)(this + 0x48));
      if ((long *)*plVar5 != (long *)0x0) {
                    /* try { // try from 00d4680d to 00d4680f has its CatchHandler @ 00d4692b */
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)(this + 0x48) + (ulong)uVar6 * 8) = 0;
        plVar5 = (long *)(lVar3 + *(long *)(this + 0x48));
      }
      *plVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x50));
  }
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
  }
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  paVar1 = (allocator *)(*(long *)(this + 0xc0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xc0) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x98) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x98) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x90) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x90) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x88) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x88) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x80) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x80) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x78) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x78) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x70) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x70) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x68) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x68) + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
    *(undefined8 *)(this + 0x48) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d46b50
   symbol=CQuestUnitData::~CQuestUnitData */

/* CQuestUnitData::~CQuestUnitData() */

void __thiscall CQuestUnitData::~CQuestUnitData(CQuestUnitData *this)

{
  ~CQuestUnitData(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00d46b70
   symbol=CQuestUnitData::parseDataGroup */

/* WARNING: Removing unreachable block (ram,0x00d4745d) */
/* WARNING: Removing unreachable block (ram,0x00d4744f) */
/* WARNING: Removing unreachable block (ram,0x00d474b1) */
/* WARNING: Removing unreachable block (ram,0x00d47350) */
/* WARNING: Removing unreachable block (ram,0x00d47495) */
/* WARNING: Removing unreachable block (ram,0x00d4750a) */
/* WARNING: Removing unreachable block (ram,0x00d474fc) */
/* WARNING: Removing unreachable block (ram,0x00d47518) */
/* WARNING: Removing unreachable block (ram,0x00d474e0) */
/* WARNING: Removing unreachable block (ram,0x00d474d2) */
/* WARNING: Removing unreachable block (ram,0x00d47479) */
/* WARNING: Removing unreachable block (ram,0x00d474ee) */
/* WARNING: Removing unreachable block (ram,0x00d474a3) */
/* WARNING: Removing unreachable block (ram,0x00d47487) */
/* WARNING: Removing unreachable block (ram,0x00d4746b) */
/* WARNING: Removing unreachable block (ram,0x00d474c4) */
/* CQuestUnitData::parseDataGroup(CDataGroup*, CDataGroup*) */

undefined8 __thiscall
CQuestUnitData::parseDataGroup(CQuestUnitData *this,CDataGroup *param_1,CDataGroup *param_2)

{
  int *piVar1;
  CQuestUnitData CVar2;
  undefined4 uVar3;
  int iVar4;
  wstring_conflict *pwVar5;
  int iVar6;
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [4];
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  if (param_1 != (CDataGroup *)0x0) {
                    /* try { // try from 00d46ba9 to 00d46bad has its CatchHandler @ 00d4734b */
    std::wstring::wstring((wstring_conflict *)local_58,L"REMOVEFROMINVENTORY",&local_29);
                    /* try { // try from 00d46bb9 to 00d46bbd has its CatchHandler @ 00d47338 */
    CVar2 = (CQuestUnitData)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_58,true);
    this[0x62] = CVar2;
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
                    /* try { // try from 00d46bf4 to 00d46bf8 has its CatchHandler @ 00d474bf */
    std::wstring::wstring((wstring_conflict *)local_68,L"RELATIVEFLOOR",&local_2a);
                    /* try { // try from 00d46c01 to 00d46c05 has its CatchHandler @ 00d4735d */
    uVar3 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_68,0);
    *(undefined4 *)(this + 0xa0) = uVar3;
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 00d46c39 to 00d46c3d has its CatchHandler @ 00d4736c */
    std::wstring::wstring((wstring_conflict *)local_78,L"SPECIFICFLOOR",&local_2b);
                    /* try { // try from 00d46c49 to 00d46c4d has its CatchHandler @ 00d4736a */
    uVar3 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_78,-1);
    *(undefined4 *)(this + 0xa4) = uVar3;
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    *(CDataGroup **)(this + 0x28) = param_2;
    *(undefined8 *)(this + 0x20) = 0;
                    /* try { // try from 00d46c8d to 00d46c91 has its CatchHandler @ 00d4735b */
    std::wstring::wstring((wstring_conflict *)local_88,L"SPAWNCLASS",&local_2c);
                    /* try { // try from 00d46c9d to 00d46cb4 has its CatchHandler @ 00d4738f */
    pwVar5 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (param_1,(wstring_conflict *)local_88,(wstring_conflict *)&::EMPTY_WSTRING);
    STRINGS::StringUpper((STRINGS *)local_98,pwVar5);
                    /* try { // try from 00d46cbc to 00d46cc0 has its CatchHandler @ 00d47376 */
    std::wstring::assign((wstring_conflict *)(this + 0x78));
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00d46d03 to 00d46d07 has its CatchHandler @ 00d47374 */
    std::wstring::wstring((wstring_conflict *)local_a8,L"ITEM",&local_2d);
                    /* try { // try from 00d46d13 to 00d46d26 has its CatchHandler @ 00d47372 */
    CDataGroup::GetDataValue
              (param_1,(wstring_conflict *)local_a8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x80));
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46d54 to 00d46d58 has its CatchHandler @ 00d473a6 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"MONSTER",&local_2e);
                    /* try { // try from 00d46d64 to 00d46d77 has its CatchHandler @ 00d473a4 */
    CDataGroup::GetDataValue
              (param_1,(wstring_conflict *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x88));
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46da5 to 00d46da9 has its CatchHandler @ 00d473c6 */
    std::wstring::wstring((wstring_conflict *)local_c8,L"UNITTYPE",&local_2f);
                    /* try { // try from 00d46db5 to 00d46dc8 has its CatchHandler @ 00d473c4 */
    CDataGroup::GetDataValue
              (param_1,(wstring_conflict *)local_c8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x90));
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46df3 to 00d46df7 has its CatchHandler @ 00d473c2 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"NEVERDESTROY",&local_30);
                    /* try { // try from 00d46e03 to 00d46e07 has its CatchHandler @ 00d473b6 */
    CVar2 = (CQuestUnitData)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_d8,true);
    this[0xb8] = CVar2;
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46e35 to 00d46e39 has its CatchHandler @ 00d473b4 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"SPAWNFROMUNITTYPE",&local_31);
                    /* try { // try from 00d46e45 to 00d46e58 has its CatchHandler @ 00d473b2 */
    CDataGroup::GetDataValue
              (param_1,(wstring_conflict *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x98));
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46e80 to 00d46e84 has its CatchHandler @ 00d47396 */
    std::wstring::wstring((wstring_conflict *)local_f8,L"UNIQUE_MONSTER_NAME",&local_32);
                    /* try { // try from 00d46e90 to 00d46ea0 has its CatchHandler @ 00d47394 */
    CDataGroup::GetDataValue
              (param_1,(wstring_conflict *)local_f8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x70));
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
                    /* try { // try from 00d46ec8 to 00d46ecc has its CatchHandler @ 00d47405 */
    std::wstring::wstring((wstring_conflict *)local_108,L"REMOVE_ONLY_QUESTITEMS",&local_33);
                    /* try { // try from 00d46ed8 to 00d46edc has its CatchHandler @ 00d473f5 */
    CVar2 = (CQuestUnitData)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_108,true);
    this[100] = CVar2;
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 00d46f07 to 00d46f0b has its CatchHandler @ 00d473e5 */
    std::wstring::wstring((wstring_conflict *)local_118,L"MINCOUNT",&local_34);
                    /* try { // try from 00d46f14 to 00d46f18 has its CatchHandler @ 00d473d5 */
    iVar4 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_118,0);
    *(int *)(this + 0xa8) = iVar4;
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
      iVar4 = *(int *)(this + 0xa8);
    }
    iVar6 = 1;
    if (0 < iVar4) {
      iVar6 = iVar4;
    }
    *(int *)(this + 0xa8) = iVar6;
                    /* try { // try from 00d46f59 to 00d46f5d has its CatchHandler @ 00d473a2 */
    std::wstring::wstring((wstring_conflict *)local_128,L"MAXCOUNT",&local_35);
                    /* try { // try from 00d46f67 to 00d46f6b has its CatchHandler @ 00d47398 */
    iVar4 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_128,iVar6);
    *(int *)(this + 0xac) = iVar4;
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
      iVar4 = *(int *)(this + 0xac);
    }
    if (iVar4 < *(int *)(this + 0xa8)) {
      iVar4 = *(int *)(this + 0xa8);
    }
    *(int *)(this + 0xac) = iVar4;
                    /* try { // try from 00d46faa to 00d46fae has its CatchHandler @ 00d47425 */
    std::wstring::wstring((wstring_conflict *)local_138,L"CREATE",&local_36);
                    /* try { // try from 00d46fba to 00d46fbe has its CatchHandler @ 00d47415 */
    CVar2 = (CQuestUnitData)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_138,true);
    this[99] = CVar2;
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    CVar2 = this[0x61];
                    /* try { // try from 00d46fe9 to 00d46fed has its CatchHandler @ 00d4744a */
    std::wstring::wstring((wstring_conflict *)local_148,L"MAKECHAMPION",&local_37);
                    /* try { // try from 00d46ff7 to 00d46ffb has its CatchHandler @ 00d47435 */
    CVar2 = (CQuestUnitData)
            CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_148,(bool)CVar2);
    this[0x61] = CVar2;
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    return 1;
  }
  return 0;
}

/* address=00d47530
   symbol=CQuestUnitData::cleanUpForQuestRemoveall */

/* WARNING: Removing unreachable block (ram,0x00d476a4) */
/* CQuestUnitData::cleanUpForQuestRemoveall(bool) */

void __thiscall CQuestUnitData::cleanUpForQuestRemoveall(CQuestUnitData *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  long lVar4;
  CPlayer *pCVar5;
  uint uVar6;
  long local_38;
  allocator local_29 [9];

  if (*(int *)(this + 0x50) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x54)) {
        puVar3 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x48);
      }
      uVar6 = uVar6 + 1;
      cleanUpForQuestRemoveall((CQuestUnitData *)*puVar3,param_1);
    } while (uVar6 < *(uint *)(this + 0x50));
  }
  if ((((*(long *)(this + 0x18) != 0) && (*(long *)(this + 0x20) != 0)) &&
      (*(int *)(this + 0xb4) == 1)) && (this[0x62] != (CQuestUnitData)0x0)) {
                    /* try { // try from 00d475c3 to 00d475c7 has its CatchHandler @ 00d4769f */
    std::wstring::wstring((wstring_conflict *)&local_38,L"UNIT_GUID",local_29);
                    /* try { // try from 00d475da to 00d475de has its CatchHandler @ 00d4768c */
    lVar4 = CResourceManager::getUnitGuidByDataGroup
                      (*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8),
                       *(CDataGroup **)(this + 0x20),(wstring_conflict *)&local_38);
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    if ((lVar4 != -1) &&
       (pCVar5 = (CPlayer *)CQuest::getPlayer(*(CQuest **)(this + 0x18)), pCVar5 != (CPlayer *)0x0))
    {
      if (this[100] == (CQuestUnitData)0x0) {
        CPlayer::removeItemFromInventoryOrPetsInventoryByGuid(pCVar5,lVar4,1,1,-!param_1 & 0x67);
      }
      else {
        CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid
                  (pCVar5,*(undefined8 *)(*(long *)(this + 0x18) + 0x1c8),lVar4,1,1,-!param_1 & 0x67
                  );
      }
    }
  }
  return;
}

/* address=00d476b0
   symbol=CQuestUnitData::getSpawnClassUnitDataLookingFor */

/* WARNING: Removing unreachable block (ram,0x00d47dca) */
/* WARNING: Removing unreachable block (ram,0x00d47d77) */
/* WARNING: Removing unreachable block (ram,0x00d47d3e) */
/* WARNING: Removing unreachable block (ram,0x00d47d8c) */
/* CQuestUnitData::getSpawnClassUnitDataLookingFor() */

undefined8 __thiscall CQuestUnitData::getSpawnClassUnitDataLookingFor(CQuestUnitData *this)

{
  int *piVar1;
  wchar_t wVar2;
  CLevelTemplateData *this_00;
  undefined8 uVar3;
  bool bVar4;
  long lVar5;
  CSpawnClassParser *pCVar6;
  CSpawnClass *this_01;
  int iVar7;
  size_t sVar8;
  int iVar9;
  CGameClient *this_02;
  wchar_t *__s1;
  undefined8 *puVar10;
  wchar_t *pwVar11;
  int iVar12;
  int iVar13;
  undefined8 *local_b8;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  long local_98 [2];
  wstring_conflict local_88 [16];
  long local_78 [2];
  wstring_conflict local_68 [16];
  long local_58 [2];
  wchar_t *local_48 [3];

  if (*(int *)(this + 0xb0) == 0) {
    pwVar11 = *(wchar_t **)(this + 0x78);
    puVar10 = (undefined8 *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 8);
    iVar9 = 1;
    do {
      sVar8 = *(size_t *)((wchar_t *)*puVar10 + -6);
      if ((sVar8 == *(size_t *)(pwVar11 + -6)) &&
         (iVar7 = wmemcmp((wchar_t *)*puVar10,pwVar11,sVar8), iVar7 == 0)) {
        *(int *)(this + 0xb0) = iVar9;
      }
      iVar9 = iVar9 + 1;
      puVar10 = puVar10 + 1;
    } while (iVar9 != 4);
    if (((*(int *)(this + 0xb0) == 0) &&
        (*(size_t *)(pwVar11 + -6) == *(size_t *)(::EMPTY_WSTRING + -6))) &&
       (iVar9 = wmemcmp(pwVar11,::EMPTY_WSTRING,*(size_t *)(pwVar11 + -6)), iVar9 == 0)) {
      return 0;
    }
  }
  if ((*(long *)(*(CQuest **)(this + 0x18) + 0x10) == 0) ||
     (lVar5 = CQuest::getPlayer(*(CQuest **)(this + 0x18)), lVar5 == 0)) {
    return 0;
  }
  lVar5 = CQuest::getPlayer(*(CQuest **)(this + 0x18));
  if (*(long *)(lVar5 + 0x68) == 0) {
    return 0;
  }
  if (*(long *)(*(long *)(lVar5 + 0x68) + 0x18) == 0) {
    return 0;
  }
  lVar5 = *(long *)(this + 0x18);
  this_02 = (CGameClient *)0x0;
  this_00 = *(CLevelTemplateData **)(lVar5 + 0x10);
  if (*(int *)(*(long *)(lVar5 + 0x1d8) + 0x30) == 0) {
    iVar9 = *(int *)(this + 0xa0);
    iVar7 = *(int *)(lVar5 + 0x1c);
    if (iVar9 != 0) goto LAB_00d4778b;
LAB_00d47978:
    iVar9 = *(int *)(this + 0xa4);
    if (iVar9 == -1) {
      iVar9 = *(int *)(lVar5 + 0x20);
    }
  }
  else {
    iVar9 = *(int *)(this + 0xa0);
    iVar7 = *(int *)(lVar5 + 0x1c);
    this_02 = (CGameClient *)**(undefined8 **)(*(long *)(lVar5 + 0x1d8) + 0x28);
    if (iVar9 == 0) goto LAB_00d47978;
LAB_00d4778b:
    iVar9 = iVar9 + *(int *)(lVar5 + 0x20);
    iVar12 = -1;
    if (-1 < iVar9) {
      iVar12 = iVar9;
    }
    iVar9 = *(int *)(lVar5 + 0x20);
    if (iVar12 != -1) {
      iVar9 = iVar12;
    }
  }
  CGameClient::resetGameSeed(this_02,iVar9 + iVar7);
  CLevelTemplateData::chooseUnitSpawners
            (this_00,*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8));
  std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(this + 0x78));
  __s1 = local_48[0];
  pwVar11 = ::EMPTY_WSTRING;
  if (*(size_t *)(local_48[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
    this_01 = (CSpawnClass *)0x0;
    iVar9 = wmemcmp(local_48[0],::EMPTY_WSTRING,*(size_t *)(local_48[0] + -6));
    if (iVar9 != 0) goto LAB_00d477ea;
LAB_00d47a16:
    iVar9 = *(int *)(this + 0xb0);
    if (iVar9 == 2) {
                    /* try { // try from 00d47a57 to 00d47a5b has its CatchHandler @ 00d47d82 */
      std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)(this_00 + 0x5c8));
                    /* try { // try from 00d47a62 to 00d47a66 has its CatchHandler @ 00d47d9a */
      std::wstring::assign((wstring_conflict *)local_48);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar9 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
                    /* try { // try from 00d47a85 to 00d47aa1 has its CatchHandler @ 00d47d82 */
      iVar9 = std::wstring::compare((wchar_t *)local_48);
      if (iVar9 == 0) {
        std::wstring::wstring(local_88,(wstring_conflict *)(this_00 + 0x580));
                    /* try { // try from 00d47aa8 to 00d47aac has its CatchHandler @ 00d47d9c */
        std::wstring::assign((wstring_conflict *)local_48);
                    /* try { // try from 00d47ab0 to 00d47ad6 has its CatchHandler @ 00d47d82 */
        std::wstring::~wstring(local_88);
      }
      iVar9 = std::wstring::compare((wchar_t *)local_48);
      if ((iVar9 == 0) || (sVar8 = *(size_t *)(local_48[0] + -6), sVar8 == 0)) {
        std::wstring::assign((wchar_t *)local_48);
LAB_00d47ad7:
        bVar4 = false;
        sVar8 = *(size_t *)(local_48[0] + -6);
        __s1 = local_48[0];
        pwVar11 = ::EMPTY_WSTRING;
      }
      else {
LAB_00d47b85:
        bVar4 = false;
        __s1 = local_48[0];
        pwVar11 = ::EMPTY_WSTRING;
      }
    }
    else if (iVar9 == 3) {
      std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)(this_00 + 0x5c0));
                    /* try { // try from 00d47c4b to 00d47c4f has its CatchHandler @ 00d47d31 */
      std::wstring::assign((wstring_conflict *)local_48);
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_98[0] + -8);
        iVar9 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
      bVar4 = true;
      sVar8 = *(size_t *)(local_48[0] + -6);
      __s1 = local_48[0];
      pwVar11 = ::EMPTY_WSTRING;
    }
    else {
      if (iVar9 == 1) {
                    /* try { // try from 00d47baa to 00d47bae has its CatchHandler @ 00d47d82 */
        std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(this_00 + 0x5b8));
                    /* try { // try from 00d47bb5 to 00d47bb9 has its CatchHandler @ 00d47d75 */
        std::wstring::assign((wstring_conflict *)local_48);
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar9 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar9 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
                    /* try { // try from 00d47bdb to 00d47bfa has its CatchHandler @ 00d47d82 */
        iVar9 = std::wstring::compare((wchar_t *)local_48);
        if (iVar9 == 0) {
          std::wstring::wstring(local_68,(wstring_conflict *)(this_00 + 0x578));
                    /* try { // try from 00d47c01 to 00d47c05 has its CatchHandler @ 00d47d8a */
          std::wstring::assign((wstring_conflict *)local_48);
                    /* try { // try from 00d47c09 to 00d47c44 has its CatchHandler @ 00d47d82 */
          std::wstring::~wstring(local_68);
        }
        iVar9 = std::wstring::compare((wchar_t *)local_48);
        if ((iVar9 != 0) && (sVar8 = *(size_t *)(local_48[0] + -6), sVar8 != 0)) goto LAB_00d47b85;
        std::wstring::assign((wchar_t *)local_48);
        goto LAB_00d47ad7;
      }
      sVar8 = *(size_t *)(__s1 + -6);
      bVar4 = false;
    }
    if ((*(size_t *)(pwVar11 + -6) == sVar8) && (iVar9 = wmemcmp(__s1,pwVar11,sVar8), iVar9 == 0))
    goto LAB_00d47b07;
  }
  else {
LAB_00d477ea:
                    /* try { // try from 00d477ea to 00d477f9 has its CatchHandler @ 00d47d82 */
    pCVar6 = (CSpawnClassParser *)CSpawnClassParser::getSingleton();
    this_01 = (CSpawnClass *)CSpawnClassParser::getSpawnClass(pCVar6,(wstring_conflict *)local_48);
    if (this_01 == (CSpawnClass *)0x0) {
      std::wstring::assign((wstring_conflict *)local_48);
    }
    __s1 = local_48[0];
    pwVar11 = ::EMPTY_WSTRING;
    if ((*(size_t *)(local_48[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) &&
       (iVar9 = wmemcmp(local_48[0],::EMPTY_WSTRING,*(size_t *)(local_48[0] + -6)), iVar9 == 0))
    goto LAB_00d47a16;
    bVar4 = false;
  }
  if (this_01 == (CSpawnClass *)0x0) {
                    /* try { // try from 00d47ca0 to 00d47cd4 has its CatchHandler @ 00d47d82 */
    pCVar6 = (CSpawnClassParser *)CSpawnClassParser::getSingleton();
    this_01 = (CSpawnClass *)CSpawnClassParser::getSpawnClass(pCVar6,(wstring_conflict *)local_48);
    if (this_01 == (CSpawnClass *)0x0) goto LAB_00d47b07;
  }
  lVar5 = *(long *)(this + 0x18);
  if (*(int *)(this + 0xa0) == 0) {
    if (*(int *)(this + 0xa4) == -1) {
      iVar7 = *(int *)(lVar5 + 0x20);
      iVar9 = iVar7;
    }
    else {
      iVar7 = *(int *)(this + 0xa4);
      iVar9 = *(int *)(lVar5 + 0x20);
    }
  }
  else {
    iVar9 = *(int *)(lVar5 + 0x20);
    iVar7 = *(int *)(this + 0xa0) + iVar9;
    iVar12 = -1;
    if (-1 < iVar7) {
      iVar12 = iVar7;
    }
    iVar7 = iVar9;
    if (iVar12 != -1) {
      iVar7 = iVar12;
    }
  }
  local_b8 = (undefined8 *)0x0;
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 10;
  if (bVar4) {
    iVar13 = 1;
    iVar12 = -1;
  }
  else {
    iVar13 = -1;
    iVar12 = 0;
  }
                    /* try { // try from 00d478c9 to 00d478cd has its CatchHandler @ 00d47cda */
  CSpawnClass::rollSpawnClass
            (this_01,(TArrayList *)&local_b8,(TArrayList *)0x0,(CCharacter *)0x0,(CCharacter *)0x0,
             (iVar7 + *(int *)(lVar5 + 0x20c)) - iVar9,0xffffffff,iVar12,iVar13,0,0);
  if (local_b0 != 0) {
    uVar3 = *local_b8;
    operator_delete__(local_b8);
    if ((allocator *)(local_48[0] + -6) == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      return uVar3;
    }
    local_b8 = (undefined8 *)0x0;
    LOCK();
    pwVar11 = local_48[0] + -2;
    wVar2 = *pwVar11;
    *pwVar11 = *pwVar11 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -6));
      return uVar3;
    }
    return uVar3;
  }
  if (local_b8 != (undefined8 *)0x0) {
    operator_delete__(local_b8);
    local_b8 = (undefined8 *)0x0;
  }
LAB_00d47b07:
  std::wstring::~wstring((wstring_conflict *)local_48);
  return 0;
}

/* address=00d47de0
   symbol=CQuestUnitData::getBaseUnitDataGroup */

/* WARNING: Removing unreachable block (ram,0x00d48108) */
/* CQuestUnitData::getBaseUnitDataGroup() */

CDataGroup * __thiscall CQuestUnitData::getBaseUnitDataGroup(CQuestUnitData *this)

{
  int *piVar1;
  size_t __n;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  CDataGroup *pCVar6;
  long lVar7;
  CUnitResourceList *pCVar8;
  wstring_conflict awStack_68 [16];
  wstring_conflict local_58 [16];
  wstring_conflict local_48 [16];
  long local_38;
  allocator local_2a;
  allocator local_29 [9];

  if (*(long *)(this + 0x18) == 0) {
    return (CDataGroup *)0x0;
  }
  if (*(long *)(this + 0x28) != 0) {
                    /* try { // try from 00d47e1f to 00d47e23 has its CatchHandler @ 00d48103 */
    std::wstring::wstring((wstring_conflict *)&local_38,L"UNIT_GUID",local_29);
                    /* try { // try from 00d47e36 to 00d47e3a has its CatchHandler @ 00d480f0 */
    uVar5 = CResourceManager::getUnitGuidByDataGroup
                      (*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8),
                       *(CDataGroup **)(this + 0x28),(wstring_conflict *)&local_38);
    *(undefined8 *)(this + 0x30) = uVar5;
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    return *(CDataGroup **)(this + 0x28);
  }
  if ((*(long *)(this + 0x30) != -1) &&
     (pCVar6 = (CDataGroup *)
               CResourceManager::getUnitDataByGuid
                         (*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8),
                          *(long *)(this + 0x30)), pCVar6 != (CDataGroup *)0x0)) {
    return pCVar6;
  }
  __n = *(size_t *)(*(wchar_t **)(this + 0x78) + -6);
  if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar3 = wmemcmp(*(wchar_t **)(this + 0x78),::EMPTY_WSTRING,__n), iVar3 == 0)) {
    cVar2 = std::operator==((wstring_conflict *)(this + 0x90),(wstring_conflict *)&::EMPTY_WSTRING);
    if (cVar2 == '\0') {
      lVar7 = CMasterResourceManager::getSingleton();
      uVar4 = CHierarchy::getTypeIDByName
                        (*(CHierarchy **)(lVar7 + 0x80),(wstring_conflict *)(this + 0x90));
      *(undefined4 *)(this + 0x44) = uVar4;
      CMasterResourceManager::getSingleton();
      CHierarchy::getTypeName((uint)local_48);
                    /* try { // try from 00d47fe2 to 00d47fe6 has its CatchHandler @ 00d48113 */
      std::wstring::assign((wstring_conflict *)(this + 0x68));
      pCVar6 = (CDataGroup *)0x0;
      std::wstring::~wstring(local_48);
    }
    else {
      cVar2 = std::operator==((wstring_conflict *)(this + 0x80),(wstring_conflict *)&::EMPTY_WSTRING
                             );
      if (cVar2 == '\0') {
        pCVar8 = (CUnitResourceList *)CUnitResourceList::getSingleton();
        pCVar6 = (CDataGroup *)
                 CUnitResourceList::getDataGroupByObjectName
                           (pCVar8,(wstring_conflict *)::gRESOURCE_GROUP_NAMES,
                            (wstring_conflict *)(this + 0x80));
        goto LAB_00d47ebd;
      }
      cVar2 = std::operator==((wstring_conflict *)(this + 0x88),(wstring_conflict *)&::EMPTY_WSTRING
                             );
      if (cVar2 == '\0') {
        pCVar8 = (CUnitResourceList *)CUnitResourceList::getSingleton();
        pCVar6 = (CDataGroup *)
                 CUnitResourceList::getDataGroupByObjectName
                           (pCVar8,(wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),
                            (wstring_conflict *)(this + 0x88));
        this[0x62] = (CQuestUnitData)0x0;
      }
      else {
        if (*(int *)(this + 0xb4) == 1) {
          std::wstring::assign((wstring_conflict *)(this + 0x78));
          pCVar6 = (CDataGroup *)getSpawnClassUnitDataLookingFor(this);
          goto LAB_00d47ebd;
        }
        if (this[0x61] == (CQuestUnitData)0x0) {
          std::wstring::assign((wstring_conflict *)(this + 0x78));
          goto LAB_00d47eac;
        }
        std::wstring::assign((wstring_conflict *)(this + 0x78));
        pCVar6 = (CDataGroup *)getSpawnClassUnitDataLookingFor(this);
      }
    }
  }
  else {
LAB_00d47eac:
    pCVar6 = (CDataGroup *)getSpawnClassUnitDataLookingFor(this);
  }
  if (this[0x61] != (CQuestUnitData)0x0) {
    iVar3 = UTILITIES::getRandState();
    UTILITIES::setSeed(*(int *)(*(long *)(this + 0x18) + 0x1c));
    CRandomNames::getSingleton();
    CRandomNames::generateName(SUB81(local_58,0));
                    /* try { // try from 00d47f48 to 00d47f4c has its CatchHandler @ 00d4812c */
    std::wstring::assign((wstring_conflict *)(this + 0xc0));
    std::wstring::~wstring(local_58);
    UTILITIES::setSeed(iVar3);
  }
LAB_00d47ebd:
  if (pCVar6 == (CDataGroup *)0x0) {
    *(undefined8 *)(this + 0x30) = 0xffffffffffffffff;
    pCVar6 = (CDataGroup *)0x0;
  }
  else {
                    /* try { // try from 00d47ed6 to 00d47ef6 has its CatchHandler @ 00d48117 */
    std::wstring::wstring(awStack_68,L"UNIT_GUID",&local_2a);
    uVar5 = CResourceManager::getUnitGuidByDataGroup
                      (*(CResourceManager **)(*(long *)(this + 0x18) + 0x1d8),pCVar6,awStack_68);
    *(undefined8 *)(this + 0x30) = uVar5;
                    /* try { // try from 00d47efe to 00d47f02 has its CatchHandler @ 00d48115 */
    std::wstring::~wstring(awStack_68);
  }
  return pCVar6;
}

/* address=00d48140
   symbol=CQuestUnitData::unitPickedUp */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00d48800
   symbol=CQuestUnitData::unitDropped */

/* CQuestUnitData::unitDropped(CBaseUnit*) */

undefined8 __thiscall CQuestUnitData::unitDropped(CQuestUnitData *this,CBaseUnit *param_1)

{
  char cVar1;
  undefined8 uVar2;
  uint uVar3;

  if (this[0xb9] != (CQuestUnitData)0x0) {
    if (*(int *)(this + 0x50) != 0) {
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x54)) {
          cVar1 = unitDropped(*(CQuestUnitData **)((ulong)uVar3 * 8 + *(long *)(this + 0x48)),
                              param_1);
        }
        else {
          cVar1 = unitDropped((CQuestUnitData *)**(undefined8 **)(this + 0x48),param_1);
        }
        if (cVar1 != '\0') {
          return 1;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(this + 0x50));
    }
    if (*(long *)(this + 0x20) == 0) {
      uVar2 = getBaseUnitDataGroup(this);
      *(undefined8 *)(this + 0x20) = uVar2;
    }
    if ((param_1 != (CBaseUnit *)0x0) &&
       (((*(int *)(this + 0x44) != 0x16 && (cVar1 = CBaseUnit::ISA(param_1), cVar1 != '\0')) ||
        ((*(long *)(param_1 + 0x170) == *(long *)(*(long *)(this + 0x18) + 0x1c8) &&
         (*(int *)(param_1 + 0x178) == *(int *)(this + 0x10))))))) {
      if (*(int *)(this + 0x3c) != 0) {
        *(int *)(this + 0x3c) = *(int *)(this + 0x3c) + -1;
      }
      this[0x60] = (CQuestUnitData)0x0;
      return 1;
    }
  }
  return 0;
}

/* address=00d488f0
   symbol=CQuestUnitData::unitDefeated */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00d48d00
   symbol=CQuestUnitData::unitInteracted */

/* CQuestUnitData::unitInteracted(CBaseUnit*) */

undefined8 __thiscall CQuestUnitData::unitInteracted(CQuestUnitData *this,CBaseUnit *param_1)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined8 *puVar5;
  long lVar6;
  uint uVar7;

  if (param_1 == (CBaseUnit *)0x0) {
    return 0;
  }
  if (*(long *)(param_1 + 0x68) == 0) {
    return 0;
  }
  if (*(long *)(*(long *)(param_1 + 0x68) + 0x18) == 0) {
    return 0;
  }
  lVar6 = *(long *)(this + 0x20);
  if (lVar6 == 0) {
    lVar6 = getBaseUnitDataGroup(this);
    *(long *)(this + 0x20) = lVar6;
  }
  if (lVar6 != *(long *)(param_1 + 0x1b0)) {
    bVar2 = false;
    cVar4 = CBaseUnit::ISA(param_1,*(undefined4 *)(this + 0x44));
    if (cVar4 == '\0') goto LAB_00d48d5c;
  }
  bVar2 = true;
LAB_00d48d5c:
  if (((*(int *)(this + 0x44) == 0x16) || (cVar4 = CBaseUnit::ISA(param_1), cVar4 == '\0')) &&
     ((*(long *)(param_1 + 0x170) != *(long *)(*(long *)(this + 0x18) + 0x1c8) ||
      (*(int *)(param_1 + 0x178) != *(int *)(this + 0x10))))) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if ((this[0x60] == (CQuestUnitData)0x0) && (bVar2)) {
    iVar1 = *(int *)(this + 0x3c);
    *(uint *)(this + 0x3c) = iVar1 + 1U;
    if (*(uint *)(this + 0x38) <= iVar1 + 1U) {
      CPositionableObject::getPosition((CPositionableObject *)param_1,true);
      spawnChildrenUnits((CResourceManager *)this,*(Vector3 **)(param_1 + 0x68));
      this[0x60] = (CQuestUnitData)0x1;
      return 1;
    }
  }
  else if ((!bVar3) && ((this[0x60] != (CQuestUnitData)0x0 && (*(int *)(this + 0x50) != 0)))) {
    uVar7 = 0;
    do {
      if (uVar7 < *(uint *)(this + 0x54)) {
        puVar5 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x48);
      }
      cVar4 = unitInteracted((CQuestUnitData *)*puVar5,param_1);
      if (cVar4 != '\0') {
        return 1;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(this + 0x50));
  }
  return 0;
}

/* address=00d48ea0
   symbol=CQuestUnitData::populate */

/* CQuestUnitData::populate(CLevel*) */

void __thiscall CQuestUnitData::populate(CQuestUnitData *this,CLevel *param_1)

{
  size_t sVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CBaseUnit *pCVar5;
  CCharacter *pCVar6;
  CItem *this_00;
  undefined8 uVar7;
  long *plVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  long *local_98;
  uint local_90;
  uint local_8c;
  undefined4 local_88;
  string local_78 [16];
  STRINGS local_68 [16];
  char *local_58 [2];
  string local_48 [16];
  STRINGS local_38 [14];
  allocator local_2a;
  allocator local_29;

  if (param_1 == (CLevel *)0x0) {
    return;
  }
  lVar4 = *(long *)(this + 0x18);
  sVar1 = *(size_t *)(*(wchar_t **)(lVar4 + 0x30) + -6);
  if ((sVar1 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar11 = wmemcmp(*(wchar_t **)(lVar4 + 0x30),::EMPTY_WSTRING,sVar1), iVar11 == 0)) {
    this[99] = (CQuestUnitData)0x0;
  }
  iVar11 = *(int *)(this + 0xa0);
  if (iVar11 == 0) {
    iVar9 = *(int *)(this + 0xa4);
    if (iVar9 == -1) {
      iVar9 = *(int *)(lVar4 + 0x20);
    }
  }
  else {
    iVar9 = *(int *)(lVar4 + 0x20) + iVar11;
    iVar3 = -1;
    if (-1 < iVar9) {
      iVar3 = iVar9;
    }
    iVar9 = *(int *)(lVar4 + 0x20);
    if (iVar3 != -1) {
      iVar9 = iVar3;
    }
  }
  if (*(int *)(param_1 + 0x1a4) == iVar9) {
    sVar1 = *(size_t *)(*(wchar_t **)(param_1 + 0x280) + -6);
    if ((sVar1 == *(size_t *)(*(wchar_t **)(lVar4 + 0x30) + -6)) &&
       (iVar3 = wmemcmp(*(wchar_t **)(param_1 + 0x280),*(wchar_t **)(lVar4 + 0x30),sVar1),
       iVar3 == 0)) goto LAB_00d48fa1;
  }
  if (this[99] != (CQuestUnitData)0x0) {
    return;
  }
  if (iVar11 != 0) {
    return;
  }
  if (0 < *(int *)(this + 0xa4)) {
    return;
  }
  cVar2 = std::operator==((wstring_conflict *)(lVar4 + 0x30),(wstring_conflict *)&::EMPTY_WSTRING);
  if ((cVar2 == '\0') &&
     (cVar2 = std::operator==((wstring_conflict *)(param_1 + 0x280),
                              (wstring_conflict *)(*(long *)(this + 0x18) + 0x30)), cVar2 == '\0'))
  {
    return;
  }
LAB_00d48fa1:
  iVar11 = 1;
  if (*(long *)(this + 0x20) == 0) {
    while( true ) {
      lVar4 = getBaseUnitDataGroup(this);
      *(long *)(this + 0x20) = lVar4;
      if (lVar4 != 0) break;
      if (iVar11 == 5) {
        STRINGS::StringConvertToNarrow(local_38,*(wchar_t **)(*(long *)(this + 0x18) + 0x50));
                    /* try { // try from 00d490a4 to 00d490a8 has its CatchHandler @ 00d493b2 */
        std::operator+((char *)local_58,(string *)"Unable to spawn unit for quest ");
                    /* try { // try from 00d490ac to 00d490b0 has its CatchHandler @ 00d493af */
        std::string::~string((string *)local_38);
                    /* try { // try from 00d490c3 to 00d490c7 has its CatchHandler @ 00d493aa */
        std::string::string(local_48,local_58[0],&local_29);
                    /* try { // try from 00d490c8 to 00d490de has its CatchHandler @ 00d4938f */
        uVar7 = Ogre::LogManager::getSingleton();
        Ogre::LogManager::logMessage(uVar7,local_48,3,0);
                    /* try { // try from 00d490e2 to 00d490e6 has its CatchHandler @ 00d493aa */
        std::string::~string(local_48);
        this[0x60] = (CQuestUnitData)0x1;
        this[0xb9] = (CQuestUnitData)0x1;
        std::string::~string((string *)local_58);
        return;
      }
      iVar11 = iVar11 + 1;
    }
  }
  lVar4 = *(long *)(this + 0x18);
  if ((((*(char *)(lVar4 + 0x26) == '\0') &&
       (cVar2 = CQuestManager::getQuestComplete
                          (*(CQuestManager **)(lVar4 + 0x1d0),(wstring_conflict *)(lVar4 + 0x50)),
       cVar2 != '\0')) && (this[0xb8] == (CQuestUnitData)0x0)) &&
     (pCVar5 = (CBaseUnit *)CLevel::getBaseUnitByDataGroup(param_1,*(CDataGroup **)(this + 0x20)),
     pCVar5 != (CBaseUnit *)0x0)) {
    CLevel::removeUnit(param_1,pCVar5,true);
    (**(code **)(*(long *)pCVar5 + 8))(pCVar5);
  }
  if (((this[0x60] == (CQuestUnitData)0x0) && (*(char *)(*(long *)(this + 0x18) + 0x26) != '\0')) &&
     ((this[0xb9] == (CQuestUnitData)0x0 &&
      (this[0xb9] = (CQuestUnitData)0x1, *(int *)(this + 0x44) == 0x16)))) {
    if (*(int *)(this + 0x40) == 0x16) {
      uVar10 = 0;
      if (*(int *)(this + 0x38) != 0) {
        do {
          uVar10 = uVar10 + 1;
          createUnit((CLevel *)this);
        } while (uVar10 < *(uint *)(this + 0x38));
      }
    }
    else {
      local_98 = (long *)0x0;
      local_90 = 0;
      local_8c = 0;
      local_88 = 10;
                    /* try { // try from 00d491c5 to 00d492eb has its CatchHandler @ 00d4934c */
      CLevel::getUnitsByUnitType(param_1,*(undefined4 *)(this + 0x40),&local_98);
      if (local_90 == 0) {
        STRINGS::StringConvertToNarrow(local_68,*(wchar_t **)(*(long *)(this + 0x18) + 0x50));
                    /* try { // try from 00d492fc to 00d49300 has its CatchHandler @ 00d49382 */
        std::operator+((char *)local_58,(string *)"No units found for quest : \n");
                    /* try { // try from 00d49304 to 00d49308 has its CatchHandler @ 00d49379 */
        std::string::~string((string *)local_68);
                    /* try { // try from 00d4931b to 00d4931f has its CatchHandler @ 00d49374 */
        std::string::string(local_78,local_58[0],&local_2a);
                    /* try { // try from 00d49320 to 00d49336 has its CatchHandler @ 00d4935f */
        uVar7 = Ogre::LogManager::getSingleton();
        Ogre::LogManager::logMessage(uVar7,local_78,3,0);
                    /* try { // try from 00d4933a to 00d4933e has its CatchHandler @ 00d49374 */
        std::string::~string(local_78);
                    /* try { // try from 00d49342 to 00d49346 has its CatchHandler @ 00d4934c */
        std::string::~string((string *)local_58);
      }
      else {
        do {
          uVar10 = UTILITIES::randomIntegerBetween(0,local_90 - 1);
          plVar8 = local_98;
          if (uVar10 < local_8c) {
            plVar8 = local_98 + uVar10;
          }
          lVar4 = *plVar8;
          if (uVar10 < local_90) {
            local_90 = local_90 - 1;
            local_98[uVar10] = local_98[local_90];
          }
          if (*(long *)(lVar4 + 0x170) != -1) {
            *(undefined8 *)(lVar4 + 0x170) = *(undefined8 *)(*(long *)(this + 0x18) + 0x1c8);
            *(undefined4 *)(lVar4 + 0x178) = *(undefined4 *)(this + 0x10);
            pCVar6 = (CCharacter *)
                     __dynamic_cast(lVar4,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
            if (pCVar6 != (CCharacter *)0x0) {
              CQuestManager::calculateNPCIcon
                        (*(CQuestManager **)(*(long *)(this + 0x18) + 0x1d0),pCVar6);
            }
            this_00 = (CItem *)__dynamic_cast(lVar4,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0);
            if (this_00 != (CItem *)0x0) {
              this_00[0x348] = (CItem)0x1;
              CItem::destroyItemText(this_00);
              CItem::destroyItemText(this_00);
            }
            break;
          }
        } while (local_90 != 0);
      }
      TArrayList<CBaseUnit*>::~TArrayList((TArrayList<CBaseUnit*> *)&local_98);
    }
  }
  return;
}

/* address=00d493d0
   symbol=CQuestUnitData::reinitialize */

/* CQuestUnitData::reinitialize(bool) */

void __thiscall CQuestUnitData::reinitialize(CQuestUnitData *this,bool param_1)

{
  size_t __n;
  undefined4 uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  long lVar5;
  uint uVar6;

  *(undefined8 *)(this + 0x30) = 0xffffffffffffffff;
  this[0xb9] = (CQuestUnitData)0x0;
  this[0x60] = (CQuestUnitData)0x0;
  if (*(int *)(this + 0x50) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x54)) {
        puVar3 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x48);
      }
      uVar6 = uVar6 + 1;
      reinitialize((CQuestUnitData *)*puVar3,param_1);
    } while (uVar6 < *(uint *)(this + 0x50));
  }
  if (!param_1) {
    return;
  }
  UTILITIES::setSeed(*(int *)(*(long *)(this + 0x18) + 0x1c));
  uVar4 = getBaseUnitDataGroup(this);
  *(undefined8 *)(this + 0x20) = uVar4;
  __n = *(size_t *)(*(wchar_t **)(this + 0x98) + -6);
  if (__n == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar2 = wmemcmp(*(wchar_t **)(this + 0x98),::EMPTY_WSTRING,__n);
    if (iVar2 == 0) {
      *(undefined4 *)(this + 0x40) = 0x16;
      goto LAB_00d4948b;
    }
  }
  lVar5 = CMasterResourceManager::getSingleton();
  uVar1 = CHierarchy::getTypeIDByName
                    (*(CHierarchy **)(lVar5 + 0x80),(wstring_conflict *)(this + 0x98));
  *(undefined4 *)(this + 0x40) = uVar1;
LAB_00d4948b:
  uVar1 = UTILITIES::randomIntegerBetween(*(int *)(this + 0xa8),*(int *)(this + 0xac));
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x38) = uVar1;
  return;
}

/* address=00d494d0
   symbol=CQuestUnitData::load */

/* CQuestUnitData::load(_IO_FILE*, int) */

void __thiscall CQuestUnitData::load(CQuestUnitData *this,_IO_FILE *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined8 *puVar3;
  uint uVar4;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  char local_29;

  reinitialize(this,true);
  fread(&local_29,1,1,param_1);
  cVar1 = local_29;
  fread(&local_29,1,1,param_1);
  this[0xb9] = (CQuestUnitData)(local_29 != '\0');
  fread(&local_30,4,1,param_1);
  fread(this + 0x3c,4,1,param_1);
  if (param_2 < 10) {
    local_34 = 0;
    fread(&local_34,4,1,param_1);
    fread(&local_38,4,1,param_1);
  }
  else {
    fread(&local_38,4,1,param_1);
    if (0x13 < param_2) {
      fread(this + 0x30,8,1,param_1);
    }
  }
  this[0x60] = (CQuestUnitData)(cVar1 != '\0');
  *(undefined4 *)(this + 0x38) = local_30;
  *(undefined4 *)(this + 0x10) = local_38;
  fread(&local_3c,4,1,param_1);
  if (local_3c != 0) {
    uVar4 = 0;
    uVar2 = local_3c;
    do {
      if (uVar2 <= *(uint *)(this + 0x50)) {
        if (uVar4 < *(uint *)(this + 0x54)) {
          puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x48));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0x48);
        }
        load((CQuestUnitData *)*puVar3,param_1,param_2);
        uVar2 = local_3c;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  return;
}

/* address=00d49670
   symbol=CQuestUnitData::getUnitName */

/* WARNING: Removing unreachable block (ram,0x00d498ea) */
/* WARNING: Removing unreachable block (ram,0x00d49916) */
/* WARNING: Removing unreachable block (ram,0x00d49925) */
/* CQuestUnitData::getUnitName() */

void CQuestUnitData::getUnitName(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  wstring_conflict *pwVar5;
  CQuestUnitData *in_RSI;
  wstring_conflict *in_RDI;
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  lVar4 = getBaseUnitDataGroup(in_RSI);
  *(long *)(in_RSI + 0x20) = lVar4;
  if (*(long *)(*(long *)(in_RSI + 0xc0) + -0x18) == 0) {
    if ((*(int *)(in_RSI + 0x44) == 0x16) && (lVar4 != 0)) {
                    /* try { // try from 00d496db to 00d496df has its CatchHandler @ 00d49902 */
      std::wstring::wstring((wstring_conflict *)local_58,L"DISPLAYNAME",local_39);
                    /* try { // try from 00d496ec to 00d49700 has its CatchHandler @ 00d49907 */
      pwVar5 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)(in_RSI + 0x20),(wstring_conflict *)local_58,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)&local_48,pwVar5);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (*(long *)(local_48 + -0x18) == 0) {
                    /* try { // try from 00d49732 to 00d49736 has its CatchHandler @ 00d498d7 */
        std::wstring::wstring((wstring_conflict *)local_68,L"NAME",&local_3a);
                    /* try { // try from 00d49743 to 00d49752 has its CatchHandler @ 00d498f5 */
        CDataGroup::GetDataValue
                  (*(CDataGroup **)(in_RSI + 0x20),(wstring_conflict *)local_68,
                   (wstring_conflict *)&::EMPTY_WSTRING);
        std::wstring::assign((wstring_conflict *)&local_48);
        if ((allocator *)(local_68[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_68[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
          }
        }
      }
      wcslen(L"{");
                    /* try { // try from 00d4977b to 00d497c1 has its CatchHandler @ 00d49914 */
      iVar2 = std::wstring::find((wchar_t *)&local_48,0xfa3b9c,0);
      wcslen(L"}");
      iVar3 = std::wstring::find((wchar_t *)&local_48,0xfa3bac,(long)iVar2);
      if (((iVar3 != -1) && (iVar2 != -1)) && (iVar2 + 1 < iVar3)) {
        wcslen(L"");
                    /* try { // try from 00d4984a to 00d4984e has its CatchHandler @ 00d49914 */
        std::wstring::replace
                  ((ulong)&local_48,(long)iVar2,(wchar_t *)(long)((iVar3 - iVar2) + 1),0x1001608);
      }
      std::wstring::wstring(in_RDI,(wstring_conflict *)&local_48);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
    }
    else {
      std::wstring::wstring(in_RDI,(wstring_conflict *)(in_RSI + 0x68));
    }
  }
  else {
    std::wstring::wstring(in_RDI,(wstring_conflict *)(in_RSI + 0xc0));
  }
  return;
}

/* export-summary functions=24 failures=2 */
