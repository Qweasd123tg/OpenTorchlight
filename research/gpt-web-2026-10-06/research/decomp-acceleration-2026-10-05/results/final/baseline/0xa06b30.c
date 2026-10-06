
/* WARNING: Removing unreachable block (ram,0x00a07db5) */
/* WARNING: Removing unreachable block (ram,0x00a07d42) */
/* WARNING: Removing unreachable block (ram,0x00a07d77) */
/* WARNING: Removing unreachable block (ram,0x00a07dc8) */
/* WARNING: Removing unreachable block (ram,0x00a07de5) */
/* WARNING: Removing unreachable block (ram,0x00a07cc0) */
/* WARNING: Removing unreachable block (ram,0x00a07d16) */
/* WARNING: Removing unreachable block (ram,0x00a07dff) */
/* WARNING: Removing unreachable block (ram,0x00a07c8b) */
/* WARNING: Removing unreachable block (ram,0x00a07d25) */
/* WARNING: Removing unreachable block (ram,0x00a07e0d) */
/* WARNING: Removing unreachable block (ram,0x00a07d95) */
/* WARNING: Removing unreachable block (ram,0x00a07cb2) */
/* CShape::updateVisual(bool, float) */

void __thiscall CShape::updateVisual(CShape *this,bool param_1,float param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  void *pvVar4;
  undefined1 auVar5 [12];
  undefined1 auVar6 [12];
  bool bVar7;
  ushort uVar8;
  undefined8 uVar9;
  CGenericModel *pCVar10;
  ColourValue *pCVar11;
  string *psVar12;
  long lVar13;
  long *plVar14;
  Quaternion *this_00;
  uint uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  double dVar19;
  undefined1 auVar20 [12];
  undefined8 local_208;
  float local_200;
  undefined4 uStack_1fc;
  int *local_1f8;
  Radian local_1e8 [16];
  undefined1 local_1d8 [16];
  Radian local_1c8 [16];
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined1 local_198 [12];
  undefined1 local_188 [12];
  undefined1 local_178 [8];
  undefined4 local_170;
  float local_168;
  float local_164;
  float local_160;
  float local_158;
  float local_154;
  float local_150;
  undefined1 local_148 [12];
  float local_138;
  float fStack_134;
  undefined4 local_130;
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
  undefined4 local_58 [6];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];
  
  plVar14 = *(long **)(this->m_ShapeData100 + 0x48);
  if (plVar14 == (long *)0x0) {
    pvVar4 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a06f70 to 00a06f74 has its CatchHandler @ 00a07c86 */
    std::wstring::wstring
              ((wstring *)local_68,L"media/models/spawn_circle/spawn_circle.mesh",local_39);
                    /* try { // try from 00a06f85 to 00a06f89 has its CatchHandler @ 00a07c73 */
    std::wstring::wstring((wstring *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a06f95 to 00a06f99 has its CatchHandler @ 00a07cab */
    pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a06fb0 to 00a06fb4 has its CatchHandler @ 00a07c96 */
    CGenericModel::CGenericModel
              (pCVar10,this->m_pResourceManager,pvVar4,(wstring *)local_68,(wstring *)local_78,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x48) = pCVar10;
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    CGenericModel::setQueryMask(*(CGenericModel **)(this->m_ShapeData100 + 0x48),8);
                    /* try { // try from 00a07015 to 00a07019 has its CatchHandler @ 00a07d60 */
    std::string::string((string *)local_88,"shape",&local_3a);
                    /* try { // try from 00a07028 to 00a0702c has its CatchHandler @ 00a07d50 */
    STRINGS::uniqueName((STRINGS *)local_98,(string *)local_88);
                    /* try { // try from 00a0703a to 00a07060 has its CatchHandler @ 00a07d65 */
    plVar14 = (long *)Ogre::Entity::getSubEntity
                                ((uint)*(undefined8 *)
                                        (*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
    lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
    Ogre::Material::clone
              ((string *)&local_208,SUB81(*(undefined8 *)(lVar13 + 8),0),(string *)local_98);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00a0709b to 00a0717e has its CatchHandler @ 00a07d37 */
    uVar8 = Ogre::Material::getTechnique(SUB42(local_200,0));
    pCVar11 = (ColourValue *)Ogre::Technique::getPass(uVar8);
    Ogre::Pass::setSelfIllumination(1.0,1.0,1.0);
    local_1a8 = 0x3f800000;
    local_1a4 = 0x3f800000;
    local_1a0 = 0x3f800000;
    local_19c = 0x3e800000;
    Ogre::Pass::setAmbient(pCVar11);
    local_1b8 = 0x3f800000;
    local_1b4 = 0x3f800000;
    local_1b0 = 0x3f800000;
    local_1ac = 0x3e800000;
    Ogre::Pass::setDiffuse(pCVar11);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar11,0));
    Ogre::Material::setSceneBlending(CONCAT44(uStack_1fc,local_200),0);
    (**(code **)(*(long *)CONCAT44(uStack_1fc,local_200) + 200))();
    psVar12 = (string *)
              Ogre::Entity::getSubEntity
                        ((uint)*(undefined8 *)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
    Ogre::SubEntity::setMaterialName(psVar12);
    *(undefined1 *)(*(long *)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60) + 0xc0) = 0;
    pvVar4 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a071b6 to 00a071ba has its CatchHandler @ 00a07d35 */
    std::wstring::wstring((wstring *)local_a8,L"media/models/primitives/sphere.mesh",&local_3b);
                    /* try { // try from 00a071cb to 00a071cf has its CatchHandler @ 00a07d33 */
    std::wstring::wstring((wstring *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a071db to 00a071df has its CatchHandler @ 00a07dfa */
    pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a071f8 to 00a071fc has its CatchHandler @ 00a07df5 */
    CGenericModel::CGenericModel
              (pCVar10,this->m_pResourceManager,pvVar4,(wstring *)local_a8,(wstring *)local_b8,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x50) = pCVar10;
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
                    /* try { // try from 00a0723a to 00a0723e has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this->m_ShapeData100 + 0x50),8);
                    /* try { // try from 00a07257 to 00a0725b has its CatchHandler @ 00a07dd8 */
    std::string::string((string *)local_c8,"lightBlue",&local_3c);
                    /* try { // try from 00a0726a to 00a0726e has its CatchHandler @ 00a07dd6 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this->m_ShapeData100 + 0x50) + 0x60));
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this->m_ShapeData100 + 0x50) + 0x60) + 0xc0) = 0;
    pvVar4 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a072c0 to 00a072c4 has its CatchHandler @ 00a07ddd */
    std::wstring::wstring((wstring *)local_d8,L"media/models/primitives/box.mesh",&local_3d);
                    /* try { // try from 00a072d5 to 00a072d9 has its CatchHandler @ 00a07d8a */
    std::wstring::wstring((wstring *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a072e5 to 00a072e9 has its CatchHandler @ 00a07d85 */
    pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a07302 to 00a07306 has its CatchHandler @ 00a07d8f */
    CGenericModel::CGenericModel
              (pCVar10,this->m_pResourceManager,pvVar4,(wstring *)local_d8,(wstring *)local_e8,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x58) = pCVar10;
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00a07344 to 00a07348 has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this->m_ShapeData100 + 0x58),8);
                    /* try { // try from 00a07361 to 00a07365 has its CatchHandler @ 00a07dc3 */
    std::string::string((string *)local_f8,"lightBlue",&local_3e);
                    /* try { // try from 00a07374 to 00a07378 has its CatchHandler @ 00a07da5 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this->m_ShapeData100 + 0x58) + 0x60));
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this->m_ShapeData100 + 0x58) + 0x60) + 0xc0) = 0;
    pvVar4 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a073ca to 00a073ce has its CatchHandler @ 00a07d02 */
    std::wstring::wstring((wstring *)local_108,L"media/models/primitives/box.mesh",&local_3f);
                    /* try { // try from 00a073df to 00a073e3 has its CatchHandler @ 00a07cfa */
    std::wstring::wstring((wstring *)local_118,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a073ef to 00a073f3 has its CatchHandler @ 00a07cf5 */
    pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a0740c to 00a07410 has its CatchHandler @ 00a07cce */
    CGenericModel::CGenericModel
              (pCVar10,this->m_pResourceManager,pvVar4,(wstring *)local_108,(wstring *)local_118,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x60) = pCVar10;
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 00a0744e to 00a07452 has its CatchHandler @ 00a07d37 */
    CGenericModel::setQueryMask(*(CGenericModel **)(this->m_ShapeData100 + 0x60),8);
                    /* try { // try from 00a0746b to 00a0746f has its CatchHandler @ 00a07d14 */
    std::string::string((string *)local_128,"lightBlue",&local_40);
                    /* try { // try from 00a0747e to 00a07482 has its CatchHandler @ 00a07d07 */
    Ogre::Entity::setMaterialName(*(string **)(*(long *)(this->m_ShapeData100 + 0x60) + 0x60));
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
    *(undefined1 *)(*(long *)(*(long *)(this->m_ShapeData100 + 0x60) + 0x60) + 0xc0) = 0;
    local_208 = &PTR__SharedPtr_00fa4590;
    if ((local_1f8 != (int *)0x0) && (iVar2 = *local_1f8, *local_1f8 = iVar2 + -1, iVar2 + -1 == 0))
    {
      Ogre::SharedPtr<Ogre::Material>::destroy((SharedPtr<Ogre::Material> *)&local_208);
    }
    plVar14 = *(long **)(this->m_ShapeData100 + 0x48);
  }
  (**(code **)(*plVar14 + 0x50))(plVar14,0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x50),0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x58),0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x60),0);
  if ((param_1) &&
     ((bVar7 = CResourceManager::getEditorIsRunning(this->m_pResourceManager), !bVar7 ||
      (bVar7 = CEditorBaseObject::HasBaseObjectFlag((CEditorBaseObject *)this,8), !bVar7)))) {
    iVar2 = *(int *)(this->m_ShapeData100 + 4);
    if (iVar2 == 1) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x58),1);
      local_158 = 0.0;
      local_154 = 0.0;
      local_150 = 0.0;
      local_168 = 0.0;
      local_164 = 0.0;
      local_160 = 0.0;
      calculateLineSequment(this,param_2,(Vector3 *)&local_158,(Vector3 *)&local_168);
      auVar6._8_4_ = local_170;
      auVar6._0_8_ = local_178;
      auVar5._8_4_ = local_170;
      auVar5._0_8_ = local_178;
      auVar20._8_4_ = local_170;
      auVar20._0_8_ = local_178;
      if ((local_158 == local_168) && (_local_178 = auVar6, local_154 == local_164)) {
        _local_178 = auVar20;
        if ((local_150 == local_160) && (_local_178 = auVar5, !NAN(local_150) && !NAN(local_160))) {
          _local_178 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          local_150 = local_178._8_4_;
          local_158 = (float)local_178._0_4_;
          local_154 = (float)local_178._4_4_;
        }
      }
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x98))();
      local_164 = local_164 - local_154;
      local_168 = local_168 - local_158;
      local_160 = local_160 - local_150;
      dVar19 = atan2((double)local_168,(double)local_160);
      _local_138 = CONCAT44(fStack_134,(float)dVar19);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x108);
      Ogre::Quaternion::FromAngleAxis(local_1e8,(Vector3 *)&local_138);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x58),local_1e8);
      local_164 = local_164 * 0.5;
      local_168 = local_168 * 0.5;
      local_160 = local_160 * 0.5;
      local_200 = local_160 + local_150;
      local_208 = (undefined **)CONCAT44(local_164 + local_154 + 0.5,local_168 + local_158);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x58),&local_208);
    }
    else if (iVar2 == 0) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x48),1);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x90);
      getMaxRadiusAtPercent(this,param_2);
      getMinRadiusAtPercent(this,param_2);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x48));
      fVar16 = (float)getMaxRadiusAtPercent(this,param_2);
      fVar17 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar17 <= fVar16) {
        fVar16 = fVar17;
      }
      fVar17 = (float)getMaxRadiusAtPercent(this,param_2);
      fVar18 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar17 <= fVar18) {
        fVar17 = fVar18;
      }
      uVar15 = -(uint)(0.05 < fVar16 / fVar17);
      fVar18 = (float)getAngleOfReleaseAtPercent(this,param_2);
      lVar13 = Ogre::Entity::getSubEntity
                         ((uint)*(undefined8 *)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
      if (lVar13 != 0) {
        plVar14 = (long *)Ogre::Entity::getSubEntity
                                    ((uint)*(undefined8 *)
                                            (*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
        lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
        lVar13 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar13 + 8));
        if (lVar13 != 0) {
          plVar14 = (long *)Ogre::Entity::getSubEntity
                                      ((uint)*(undefined8 *)
                                              (*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
          lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
          uVar8 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar13 + 8));
          lVar13 = Ogre::Technique::getPass(uVar8);
          if (lVar13 != 0) {
            plVar14 = (long *)Ogre::Entity::getSubEntity
                                        ((uint)*(undefined8 *)
                                                (*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
            lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
            uVar8 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar13 + 8));
            lVar13 = Ogre::Technique::getPass(uVar8);
            if ((short)((ulong)(*(long *)(lVar13 + 0xf0) - *(long *)(lVar13 + 0xe8)) >> 3) != 0) {
              plVar14 = (long *)Ogre::Entity::getSubEntity
                                          ((uint)*(undefined8 *)
                                                  (*(long *)(this->m_ShapeData100 + 0x48) + 0x60));
              lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
              uVar8 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(lVar13 + 8));
              uVar8 = Ogre::Technique::getPass(uVar8);
              Ogre::Pass::getTextureUnitState(uVar8);
              Ogre::TextureUnitState::setTextureScroll
                        ((fVar18 / -360.0 + 1.0) * 0.5,
                         (float)(~uVar15 & 0x3d4ccccd | (uint)(fVar16 / fVar17) & uVar15) * -0.5);
            }
          }
        }
      }
      fVar16 = (float)getAngleOffsetAtPercent(this,param_2);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x108);
      local_58[0] = Ogre::Math::AngleUnitsToRadians((180.0 - fVar16) - fVar18);
      Ogre::Quaternion::FromAngleAxis(local_1c8,(Vector3 *)local_58);
      this_00 = (Quaternion *)(**(code **)(*(long *)this->m_pSceneNode + 0x1f8))();
      local_1d8 = Ogre::Quaternion::operator*(this_00,(Quaternion *)local_1c8);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x48),local_1d8);
      auVar20 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_130 = auVar20._8_4_;
      fStack_134 = auVar20._4_4_;
      _local_138 = CONCAT44(fStack_134 + 0.25,auVar20._0_4_);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x48),&local_138);
    }
    else if (iVar2 == 2) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x50),1);
      fVar16 = (float)getMaxRadiusAtPercent(this,param_2);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x90))
                (~-(uint)(0.1 < fVar16) & 0x3dcccccd | (uint)fVar16 & -(uint)(0.1 < fVar16));
      local_188 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x50),local_188);
    }
    else if (iVar2 == 4) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x60),1);
      local_148 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x60),local_148);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x108);
      uVar9 = (**(code **)(*(long *)this->m_pSceneNode + 0x1f8))();
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x60),uVar9);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x98))();
    }
    else {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x50),1);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x90))();
      local_198 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x50),local_198);
    }
  }
  return;
}

