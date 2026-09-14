/* address=00847280
   symbol=CCharacter::performAttack */


/* CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES) */

void __thiscall
CCharacter::performAttack
          (CCharacter *param_1_00,float param_4,CCharacter *this,CCharacter *param_1,uint param_2,
          undefined4 param_6)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  ulong uVar4;
  float fVar5;
  float fVar6;
  char cVar7;
  undefined4 uVar8;
  CCharacter *pCVar9;
  CCharacter *this_00;
  long lVar10;
  long *plVar11;
  undefined8 *puVar12;
  float *pfVar13;
  CWeaponTrail *pCVar14;
  CEquipment *pCVar15;
  CEquipment *this_01;
  undefined8 uVar16;
  string *psVar17;
  CLevel *pCVar18;
  CSoundBank *this_02;
  CPositionableObject *pCVar19;
  CCharacter *pCVar20;
  bool bVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  long local_228;
  SceneManager *local_208;
  float local_200;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  float local_1a0;
  undefined8 local_198;
  float local_190;
  undefined4 local_188 [2];
  undefined4 local_180;
  Vector3 local_178 [16];
  ulong local_168;
  float local_160;
  ulong local_158;
  float local_150;
  undefined8 local_148;
  float local_140;
  undefined8 local_138;
  float local_130;
  float local_128;
  float local_124;
  float local_120;
  float local_118;
  float local_114;
  float local_110;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  ulong local_e8;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  ulong local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  string local_88 [16];
  string local_78 [16];
  string local_68 [16];
  STRINGS local_58 [16];
  string local_48 [8];
  uint local_40;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  this[0x37e] = (CCharacter)((byte)this[0x37e] ^ 1);
  if (param_1 == (CCharacter *)0x0) {
    pCVar20 = *(CCharacter **)(this + 0x498);
LAB_00847f3f:
    local_228 = *(long *)(this + 0x390);
    if (local_228 == 0) {
      selectAttack(this,0);
      local_228 = *(long *)(this + 0x390);
      if (local_228 == 0) {
        return;
      }
    }
  }
  else {
    pCVar9 = (CCharacter *)getWeaponInLeftHand(this);
    pCVar20 = param_1;
    if (param_1 == pCVar9) {
LAB_00847a30:
      local_228 = *(long *)(param_1 + 0x2a8);
LAB_00847a3c:
      if (local_228 == 0) goto LAB_00847f3f;
    }
    else {
      pCVar9 = (CCharacter *)getWeaponInRightHand(this);
      if (param_1 == pCVar9) {
        local_228 = *(long *)(param_1 + 0x2a0);
        goto LAB_00847a3c;
      }
      local_228 = *(long *)(param_1 + 0x2a0);
      if (local_228 == 0) goto LAB_00847a30;
    }
  }
  this_01 = (CEquipment *)0x0;
  if (*(long *)(this + 0x350) != 0) {
    cVar7 = CBaseUnit::ISA();
    if (cVar7 == '\0') {
      setTargetItem(this,(CItem *)0x0);
    }
    this_01 = *(CEquipment **)(this + 0x350);
  }
  pCVar9 = *(CCharacter **)(this + 0x340);
  if ((pCVar9 != (CCharacter *)0x0) && ((param_2 & 0x40) == 0)) {
    cVar7 = isEnemy(this,pCVar9);
    if (cVar7 == '\0') {
      return;
    }
    this_01 = (CEquipment *)0x0;
  }
  if ((param_2 & 0x10) == 0) {
    pCVar15 = this_01;
    if (pCVar9 != (CCharacter *)0x0) {
      pCVar15 = (CEquipment *)pCVar9;
    }
    executeProcs(this,0x4a,pCVar15);
    if (pCVar20 != (CCharacter *)0x0) {
      cVar7 = doWeaponSkill((CEquipment *)this);
      if (cVar7 != '\0') {
        return;
      }
      cVar7 = CEquipment::fireMissiles(pCVar20,this);
      if (cVar7 != '\0') {
        return;
      }
      goto LAB_00847347;
    }
LAB_00847361:
    local_200 = 0.0;
    fVar23 = DAT_00fa8778;
    if (this_01 != (CEquipment *)0x0) goto LAB_00847aa9;
LAB_0084738b:
    if (pCVar9 != (CCharacter *)0x0) goto LAB_00847aa9;
LAB_00847394:
    local_1e8 = *(ulong *)(this + 0xc0);
    local_1d8 = *(undefined8 *)(this + 0xd0);
    local_1c8 = *(undefined8 *)(this + 0xe0);
    local_1b8 = *(undefined8 *)(this + 0xf0);
    local_1b0 = *(undefined8 *)(this + 0xf8);
    local_1e0._0_4_ = (float)*(undefined8 *)(this + 200);
    local_1e0 = CONCAT44(*(undefined4 *)(this + 0x84),(float)local_1e0);
    local_1d0 = CONCAT44(*(undefined4 *)(this + 0x88),(int)*(undefined8 *)(this + 0xd8));
    local_1c0 = CONCAT44(*(undefined4 *)(this + 0x8c),(int)*(undefined8 *)(this + 0xe8));
    fVar24 = *(float *)(this + 0x4e0);
    fVar22 = *(float *)(this + 0x98);
    fVar1 = *(float *)(local_228 + 0x6c);
    fVar2 = *(float *)(this + 0x4dc);
    uVar8 = getTargetAlignment(this);
    fVar6 = DAT_00fa86e8;
    fVar5 = DAT_00fa47fc;
    uVar16 = 0;
    if (*(long *)(this + 0x68) != 0) {
      uVar16 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
    }
    param_4 = fVar23;
    this_00 = (CCharacter *)
              CLevel::findCharacterWithinView
                        ((CLevel *)0x0,fVar23,
                         (fVar22 * fVar24 + DAT_00fa86e8 + fVar1 + local_200) * fVar2 + DAT_00fa47fc
                         ,uVar16,(Matrix4 *)&local_1e8,uVar8,1,0,0);
    if ((this_00 == (CCharacter *)0x0) && (this_00 = pCVar9, pCVar9 == (CCharacter *)0x0)) {
      pCVar18 = (CLevel *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        pCVar18 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      param_4 = (*(float *)(this + 0x98) * *(float *)(this + 0x4e0) + fVar6 +
                *(float *)(local_228 + 0x6c)) * *(float *)(this + 0x4dc) + fVar5;
      pCVar15 = (CEquipment *)
                CLevel::findItemWithinView(pCVar18,(Matrix4 *)&local_1e8,fVar23,param_4);
      if (pCVar15 != (CEquipment *)0x0) {
        this_01 = pCVar15;
      }
      this_00 = (CCharacter *)(CPositionableObject *)0x0;
    }
  }
  else {
LAB_00847347:
    if ((pCVar20 == (CCharacter *)0x0) ||
       (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20,0x23), cVar7 == '\0')) goto LAB_00847361;
    local_200 = (float)getEffectValue(this,0x4e,7);
    fVar23 = DAT_00fa86e0;
    if (this_01 == (CEquipment *)0x0) goto LAB_0084738b;
LAB_00847aa9:
    cVar7 = inStrikeRange(this,(CItem *)pCVar9,this_01);
    this_00 = pCVar9;
    if (cVar7 == '\0') goto LAB_00847394;
  }
  if ((param_2 & 4) != 0) goto LAB_00847f08;
  if ((pCVar20 == (CCharacter *)0x0) ||
     (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20,0x23), cVar7 == '\0')) {
    local_148 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    fVar23 = DAT_00fa86d0 + (float)(local_148 >> 0x20);
    local_138 = CONCAT44(fVar23,(int)local_148);
    local_140 = param_4;
    local_130 = param_4;
    if (this_01 == (CEquipment *)0x0) {
      if (this_00 != (CCharacter *)0x0) {
        local_168 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
        local_148 = local_168 & 0xffffffff;
        fVar23 = local_138._4_4_;
        local_160 = param_4;
        local_140 = param_4;
      }
    }
    else {
      local_158 = CPositionableObject::getPosition((CPositionableObject *)this_01,true);
      local_148 = local_158 & 0xffffffff;
      fVar23 = local_138._4_4_;
      local_150 = param_4;
      local_140 = param_4;
    }
    local_148 = CONCAT44(fVar23,(float)local_148);
    pCVar18 = (CLevel *)0x0;
    if (*(long *)(this + 0x68) != 0) {
      pCVar18 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
    }
    param_4 = local_140;
    cVar7 = CLevel::rayCollision
                      (pCVar18,(Vector3 *)&local_138,(Vector3 *)&local_148,local_178,
                       (Vector3 *)local_188,&local_40,(Vector3 *)&local_1e8,false);
    if (cVar7 == '\0') {
LAB_00847f08:
      bVar21 = false;
    }
    else {
      pfVar13 = (float *)(**(code **)(*(long *)this + 0x130))(this);
      fVar24 = DAT_00fce4cc;
      local_138._4_4_ = local_138._4_4_ - pfVar13[1] * DAT_00fce4cc;
      local_130 = local_130 - pfVar13[2] * DAT_00fce4cc;
      local_138._0_4_ = (float)local_138 - *pfVar13 * DAT_00fce4cc;
      pfVar13 = (float *)(**(code **)(*(long *)this + 0x158))(this);
      fVar23 = DAT_00fc6774;
      local_130 = pfVar13[2] * DAT_00fc6774 + local_130;
      local_138 = CONCAT44(pfVar13[1] * DAT_00fc6774 + local_138._4_4_,
                           *pfVar13 * DAT_00fc6774 + (float)local_138);
      pfVar13 = (float *)(**(code **)(*(long *)this + 0x158))();
      pCVar18 = (CLevel *)0x0;
      local_140 = pfVar13[2] * fVar23 + local_140;
      local_148 = CONCAT44(pfVar13[1] * fVar23 + local_148._4_4_,
                           fVar23 * *pfVar13 + (float)local_148);
      if (*(long *)(this + 0x68) != 0) {
        pCVar18 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      param_4 = fVar24;
      cVar7 = CLevel::rayCollision
                        (pCVar18,(Vector3 *)&local_138,(Vector3 *)&local_148,local_178,
                         (Vector3 *)local_188,&local_40,(Vector3 *)&local_1e8,false);
      if (cVar7 == '\0') goto LAB_00847f08;
      pfVar13 = (float *)(**(code **)(*(long *)this + 0x158))(this);
      local_138 = CONCAT44(local_138._4_4_ - pfVar13[1] * fVar24,
                           (float)local_138 - *pfVar13 * fVar24);
      local_130 = local_130 - pfVar13[2] * fVar24;
      pfVar13 = (float *)(**(code **)(*(long *)this + 0x158))();
      pCVar18 = (CLevel *)0x0;
      param_4 = fVar24 * *pfVar13;
      local_148 = CONCAT44(local_148._4_4_ - pfVar13[1] * fVar24,(float)local_148 - param_4);
      local_140 = local_140 - pfVar13[2] * fVar24;
      if (*(long *)(this + 0x68) != 0) {
        pCVar18 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      cVar7 = CLevel::rayCollision
                        (pCVar18,(Vector3 *)&local_138,(Vector3 *)&local_148,local_178,
                         (Vector3 *)local_188,&local_40,(Vector3 *)&local_1e8,false);
      bVar21 = true;
      if (cVar7 == '\0') goto LAB_00847f08;
    }
  }
  else {
    cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20,0x24);
    if (((cVar7 == '\0') && (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20,0x6e), cVar7 == '\0')) &&
       (cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20,0x74), cVar7 == '\0')) {
      cVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar20);
      bVar3 = false;
      if (cVar7 != '\0') goto LAB_0084756e;
    }
    else {
LAB_0084756e:
      pCVar14 = *(CWeaponTrail **)(this + 0x6a8);
      if (pCVar14 == (CWeaponTrail *)0x0) {
        local_208 = (SceneManager *)0x0;
        if (*(long *)(this + 0x68) != 0) {
          local_208 = *(SceneManager **)(*(long *)(this + 0x68) + 0x10);
        }
                    /* try { // try from 008480bf to 008480c3 has its CatchHandler @ 00848767 */
        std::string::string(local_48,"trail_",local_39);
        psVar17 = local_48;
                    /* try { // try from 008480d4 to 008480d8 has its CatchHandler @ 00848762 */
        STRINGS::uniqueName(local_58,psVar17);
                    /* try { // try from 008480de to 008480e2 has its CatchHandler @ 0084875d */
        pCVar14 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0xa0,(ulong)psVar17);
                    /* try { // try from 00848108 to 0084810c has its CatchHandler @ 00848734 */
        CWeaponTrail::CWeaponTrail(pCVar14,local_208,(string *)local_58,2,DAT_00fa4830);
        *(CWeaponTrail **)(this + 0x6a8) = pCVar14;
                    /* try { // try from 00848121 to 00848125 has its CatchHandler @ 00848762 */
        std::string::~string((string *)local_58);
                    /* try { // try from 0084812e to 00848132 has its CatchHandler @ 00848767 */
        std::string::~string(local_48);
                    /* try { // try from 00848148 to 0084814c has its CatchHandler @ 0084872f */
        std::string::string(local_68,"ArrowTrail",&local_3a);
                    /* try { // try from 0084815c to 00848160 has its CatchHandler @ 0084871d */
        CWeaponTrail::setMaterialName(*(string **)(this + 0x6a8));
                    /* try { // try from 00848169 to 0084816d has its CatchHandler @ 0084872f */
        std::string::~string(local_68);
        pCVar14 = *(CWeaponTrail **)(this + 0x6a8);
      }
      CWeaponTrail::setActive(pCVar14,true);
      bVar3 = true;
    }
    lVar10 = (**(code **)(*(long *)pCVar20 + 0x1e0))(pCVar20);
    plVar11 = (long *)(**(code **)(**(long **)(lVar10 + 0x60) + 0x98))();
    puVar12 = (undefined8 *)(**(code **)(*plVar11 + 0x200))();
    local_98 = *puVar12;
    local_90 = *(float *)(puVar12 + 1);
    if ((param_2 & 0x20) != 0) {
      local_98._4_4_ = (float)((ulong)local_98 >> 0x20);
      uVar8 = local_98._4_4_;
      local_a8 = CPositionableObject::getPosition((CPositionableObject *)this,false);
      local_98 = CONCAT44(uVar8,(int)local_a8);
      local_a0 = param_4;
      local_90 = param_4;
    }
    local_1e8 = local_98;
    local_1e0._0_4_ = local_90;
    if (this_01 == (CEquipment *)0x0) {
      if (this_00 == (CCharacter *)0x0) {
        local_200 = *(float *)(this + 0x4dc) * *(float *)(local_228 + 0x6c) + local_200;
        fVar23 = *(float *)(this + 0xb8) * local_200 + local_98._4_4_;
        local_1e0 = CONCAT44(local_1e0._4_4_,*(float *)(this + 0xbc) * local_200 + local_90);
        local_1e8 = (ulong)(uint)(local_200 * *(float *)(this + 0xb4) + (float)local_98);
      }
      else {
        local_1e8 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
        fVar23 = local_98._4_4_;
        local_1e0 = CONCAT44(local_1e0._4_4_,param_4);
        local_e8 = local_1e8;
        local_e0 = param_4;
        local_f8 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
        uVar4 = (ulong)local_f8 >> 0x20;
        fVar24 = *(float *)(this_00 + 0x194);
        local_f0 = param_4;
        local_108 = CPositionableObject::getPosition((CPositionableObject *)this,true);
        fVar23 = (((float)uVar4 - fVar24) -
                 ((float)((ulong)local_108 >> 0x20) - *(float *)(this + 0x194))) + fVar23;
        local_100 = param_4;
      }
    }
    else {
      local_1e8 = CPositionableObject::getPosition((CPositionableObject *)this_01,true);
      fVar23 = local_98._4_4_;
      local_1e0 = CONCAT44(local_1e0._4_4_,param_4);
      local_b8 = local_1e8;
      local_b0 = param_4;
      local_c8 = CPositionableObject::getPosition((CPositionableObject *)this_01,true);
      uVar4 = (ulong)local_c8 >> 0x20;
      fVar24 = *(float *)(this_01 + 0x194);
      local_c0 = param_4;
      local_d8 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      fVar23 = (((float)uVar4 - fVar24) -
               ((float)((ulong)local_d8 >> 0x20) - *(float *)(this + 0x194))) + fVar23;
      local_d0 = param_4;
    }
    pCVar18 = (CLevel *)0x0;
    fVar22 = SQRT((float)local_1e8 * (float)local_1e8 + local_98._4_4_ * local_98._4_4_ +
                  (float)local_1e0 * (float)local_1e0) / DAT_00fa86d0;
    fVar24 = fVar23 - local_98._4_4_;
    if (fVar22 <= fVar23 - local_98._4_4_) {
      fVar24 = fVar22;
    }
    if (fVar24 <= (float)((uint)fVar22 ^ DAT_00fa8780)) {
      fVar24 = (float)((uint)fVar22 ^ DAT_00fa8780);
    }
    local_120 = (float)local_1e0 + 0.0;
    local_128 = (float)local_1e8 + 0.0;
    local_1e8 = CONCAT44(fVar24 + local_98._4_4_,(float)local_1e8);
    local_124 = fVar24 + local_98._4_4_ + DAT_00fc676c;
    local_114 = local_98._4_4_ + DAT_00fc676c;
    local_110 = local_90 + 0.0;
    local_118 = (float)local_98 + 0.0;
    if (*(long *)(this + 0x68) != 0) {
      pCVar18 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
    }
    cVar7 = CLevel::rayCollision
                      (pCVar18,(Vector3 *)&local_118,(Vector3 *)&local_128,(Vector3 *)local_188,
                       local_178,&local_40,(Vector3 *)&local_148,false);
    bVar21 = cVar7 != '\0';
    param_4 = 0.0;
    if (bVar21) {
      local_1e0 = CONCAT44(local_1e0._4_4_,local_180);
      local_1e8 = CONCAT44(local_98._4_4_,local_188[0]);
    }
    if (bVar3) {
      local_138._0_4_ = (float)local_1e8 - (float)local_98;
      local_130 = (float)local_1e0 - local_90;
      local_138._4_4_ = 0.0;
      Ogre::Vector3::normalise((Vector3 *)&local_138);
      fVar24 = DAT_01424b38 * local_130;
      fVar23 = local_130 * Ogre::Vector3::UNIT_Y;
      local_130 = DAT_01424b38 * (float)local_138 - Ogre::Vector3::UNIT_Y * local_138._4_4_;
      local_138 = CONCAT44(fVar23 - DAT_01424b3c * (float)local_138,
                           local_138._4_4_ * DAT_01424b3c - fVar24);
      CWeaponTrail::update
                (0.0,*(Vector3 **)(this + 0x6a8),(Vector3 *)&local_98,SUB81(&local_138,0),
                 (CSceneNodeObject *)0x0);
      param_4 = 0.0;
      CWeaponTrail::update
                (0.0,*(Vector3 **)(this + 0x6a8),(Vector3 *)&local_1e8,SUB81(&local_138,0),
                 (CSceneNodeObject *)0x0);
      *(undefined1 *)(*(long *)(this + 0x6a8) + 0x88) = 1;
      if ((param_2 & 0x20) == 0) {
                    /* try { // try from 0084866d to 00848671 has its CatchHandler @ 00848784 */
        std::string::string(local_88,"ArrowTrail",&local_3c);
                    /* try { // try from 00848681 to 00848685 has its CatchHandler @ 00848772 */
        CWeaponTrail::setMaterialName(*(string **)(this + 0x6a8));
                    /* try { // try from 0084868e to 00848692 has its CatchHandler @ 00848784 */
        std::string::~string(local_88);
      }
      else {
                    /* try { // try from 0084852f to 00848533 has its CatchHandler @ 00848769 */
        std::string::string(local_78,"ArrowTrailReflect",&local_3b);
                    /* try { // try from 00848543 to 00848547 has its CatchHandler @ 00848705 */
        CWeaponTrail::setMaterialName(*(string **)(this + 0x6a8));
                    /* try { // try from 00848550 to 00848554 has its CatchHandler @ 00848769 */
        std::string::~string(local_78);
      }
    }
  }
  if (((param_2 & 1) == 0) && (cVar7 = inStrikeRange(this,(CItem *)this_00,this_01), cVar7 == '\0'))
  {
    return;
  }
  if (((param_2 & 2) == 0) && (cVar7 = facingTarget(this,(CItem *)this_00), cVar7 == '\0')) {
    return;
  }
  if (this_01 == (CEquipment *)0x0) {
    if ((this_00 == (CCharacter *)0x0) || (bVar21)) {
LAB_008479a1:
      if (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0) {
        CSoundBank::playSample
                  (*(CSoundBank **)(this + 0x298),0xf,*(SceneNode **)(this + 0x58),0.0,0.0,false);
      }
      return;
    }
    uVar16 = 0;
    if (*(long *)(this + 0x68) != 0) {
      uVar16 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
    }
    cVar7 = rollAttack(param_1_00._0_4_,this,uVar16,this_00,param_1,param_2,param_6);
    if (cVar7 == '\0') goto LAB_008479a1;
  }
  else {
    if (*(CPositionableObject *)(this_01 + 0x1f0) == (CPositionableObject)0x0) {
      setTargetItem(this,(CItem *)0x0);
      return;
    }
    (**(code **)(*(long *)this_01 + 0x280))(this_01,this);
    incrementJournalStatistic(this,0xb,1);
    local_1a8 = CPositionableObject::getPosition((CPositionableObject *)this_01,true);
    local_1a0 = param_4;
    local_198 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    local_190 = param_4;
    playStrikeParticle(this,(Vector3 *)&local_198,(Vector3 *)&local_1a8,DAT_00fa4838,false,false);
    if (bVar21) goto LAB_008479a1;
    if (this_00 == (CCharacter *)0x0) {
      executeProcs(this,0x4b,this_01);
      pCVar19 = (CPositionableObject *)this_01;
      goto LAB_0084801b;
    }
  }
  executeProcs(this,0x4b,this_00);
  pCVar19 = (CPositionableObject *)this_00;
LAB_0084801b:
  executeProcs(this,0x4c,pCVar19);
  if ((pCVar20 != (CCharacter *)0x0) &&
     ((this_01 != (CEquipment *)0x0 || (this_00 != (CCharacter *)0x0)))) {
    doWeaponProcs((CEquipment *)this,(CBaseUnit *)pCVar20);
  }
  if ((*(char *)(local_228 + 0x18) != '\0') ||
     (this_02 = *(CSoundBank **)(this + 0x298), this_02 == (CSoundBank *)0x0)) {
    if (pCVar20 == (CCharacter *)0x0) {
      return;
    }
    this_02 = *(CSoundBank **)(pCVar20 + 0x1d8);
    if (this_02 == (CSoundBank *)0x0) {
      return;
    }
  }
  CSoundBank::playSample(this_02,1,*(SceneNode **)(this + 0x58),0.0,0.0,false);
  return;
}
