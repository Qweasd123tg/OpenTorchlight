
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
  undefined1 auVar4 [12];
  undefined1 auVar5 [12];
  bool bVar6;
  undefined8 uVar7;
  CGenericModel *pCVar8;
  string *psVar9;
  void *pvVar10;
  long *plVar11;
  long lVar12;
  TextureUnitState *this_00;
  Quaternion *this_01;
  uint uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  double dVar17;
  undefined1 auVar18 [12];
  Vector3 local_208;
  undefined4 uStack_1fc;
  int *local_1f8;
  Quaternion local_1e8 [16];
  Quaternion local_1d8;
  Quaternion local_1c8;
  ColourValue local_1b8;
  ColourValue local_1a8;
  Vector3 local_198;
  Vector3 local_188;
  undefined1 local_178 [8];
  undefined4 local_170;
  float local_168;
  float local_164;
  float local_160;
  float local_158;
  float local_154;
  float local_150;
  Vector3 local_148;
  Vector3 local_138;
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
  float local_58 [6];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];
  
  plVar11 = *(long **)(this->m_ShapeData100 + 0x48);
  if (plVar11 == (long *)0x0) {
    pvVar10 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a06f70 to 00a06f74 has its CatchHandler @ 00a07c86 */
    std::wstring::wstring
              ((wstring *)local_68,L"media/models/spawn_circle/spawn_circle.mesh",local_39);
                    /* try { // try from 00a06f85 to 00a06f89 has its CatchHandler @ 00a07c73 */
    std::wstring::wstring((wstring *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a06f95 to 00a06f99 has its CatchHandler @ 00a07cab */
    pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a06fb0 to 00a06fb4 has its CatchHandler @ 00a07c96 */
    CGenericModel::CGenericModel
              (pCVar8,this->m_pResourceManager,pvVar10,(wstring *)local_68,(wstring *)local_78,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x48) = pCVar8;
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
    plVar11 = Ogre::Entity::getSubEntity
                        (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
    lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
    Ogre::Material::clone
              ((string *)&local_208,SUB81(*(undefined8 *)(lVar12 + 8),0),(string *)local_98);
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
    pvVar10 = Ogre::Material::getTechnique((void *)CONCAT44(uStack_1fc,local_208.z),0);
    pvVar10 = Ogre::Technique::getPass(pvVar10,0);
    Ogre::Pass::setSelfIllumination(pvVar10,1.0,1.0,1.0);
    local_1a8.r = 1.0;
    local_1a8.g = 1.0;
    local_1a8.b = 1.0;
    local_1a8.a = 0.25;
    Ogre::Pass::setAmbient(pvVar10,&local_1a8);
    local_1b8.r = 1.0;
    local_1b8.g = 1.0;
    local_1b8.b = 1.0;
    local_1b8.a = 0.25;
    Ogre::Pass::setDiffuse(pvVar10,&local_1b8);
    Ogre::Pass::setDepthWriteEnabled(pvVar10,false);
    Ogre::Material::setSceneBlending((void *)CONCAT44(uStack_1fc,local_208.z),0);
    psVar9 = (string *)(**(code **)(*(long *)CONCAT44(uStack_1fc,local_208.z) + 200))();
    pvVar10 = Ogre::Entity::getSubEntity
                        (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
    Ogre::SubEntity::setMaterialName(pvVar10,psVar9);
    *(undefined1 *)(*(long *)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60) + 0xc0) = 0;
    pvVar10 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a071b6 to 00a071ba has its CatchHandler @ 00a07d35 */
    std::wstring::wstring((wstring *)local_a8,L"media/models/primitives/sphere.mesh",&local_3b);
                    /* try { // try from 00a071cb to 00a071cf has its CatchHandler @ 00a07d33 */
    std::wstring::wstring((wstring *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a071db to 00a071df has its CatchHandler @ 00a07dfa */
    pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a071f8 to 00a071fc has its CatchHandler @ 00a07df5 */
    CGenericModel::CGenericModel
              (pCVar8,this->m_pResourceManager,pvVar10,(wstring *)local_a8,(wstring *)local_b8,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x50) = pCVar8;
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
    Ogre::Entity::setMaterialName
              (*(void **)(*(long *)(this->m_ShapeData100 + 0x50) + 0x60),(string *)local_c8);
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
    pvVar10 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a072c0 to 00a072c4 has its CatchHandler @ 00a07ddd */
    std::wstring::wstring((wstring *)local_d8,L"media/models/primitives/box.mesh",&local_3d);
                    /* try { // try from 00a072d5 to 00a072d9 has its CatchHandler @ 00a07d8a */
    std::wstring::wstring((wstring *)local_e8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a072e5 to 00a072e9 has its CatchHandler @ 00a07d85 */
    pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a07302 to 00a07306 has its CatchHandler @ 00a07d8f */
    CGenericModel::CGenericModel
              (pCVar8,this->m_pResourceManager,pvVar10,(wstring *)local_d8,(wstring *)local_e8,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x58) = pCVar8;
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
    Ogre::Entity::setMaterialName
              (*(void **)(*(long *)(this->m_ShapeData100 + 0x58) + 0x60),(string *)local_f8);
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
    pvVar10 = this->m_pResourceManager->m_pSceneManager;
                    /* try { // try from 00a073ca to 00a073ce has its CatchHandler @ 00a07d02 */
    std::wstring::wstring((wstring *)local_108,L"media/models/primitives/box.mesh",&local_3f);
                    /* try { // try from 00a073df to 00a073e3 has its CatchHandler @ 00a07cfa */
    std::wstring::wstring((wstring *)local_118,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00a073ef to 00a073f3 has its CatchHandler @ 00a07cf5 */
    pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a0740c to 00a07410 has its CatchHandler @ 00a07cce */
    CGenericModel::CGenericModel
              (pCVar8,this->m_pResourceManager,pvVar10,(wstring *)local_108,(wstring *)local_118,0);
    *(CGenericModel **)(this->m_ShapeData100 + 0x60) = pCVar8;
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
    Ogre::Entity::setMaterialName
              (*(void **)(*(long *)(this->m_ShapeData100 + 0x60) + 0x60),(string *)local_128);
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
    local_208._0_8_ = &PTR__SharedPtr_00fa4590;
    if ((local_1f8 != (int *)0x0) && (iVar2 = *local_1f8, *local_1f8 = iVar2 + -1, iVar2 + -1 == 0))
    {
      Ogre::SharedPtr<Ogre::Material>::destroy((SharedPtr<Ogre::Material> *)&local_208);
    }
    plVar11 = *(long **)(this->m_ShapeData100 + 0x48);
  }
  (**(code **)(*plVar11 + 0x50))(plVar11,0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x50),0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x58),0);
  (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x50))
            (*(long **)(this->m_ShapeData100 + 0x60),0);
  if ((param_1) &&
     ((bVar6 = CResourceManager::getEditorIsRunning(this->m_pResourceManager), !bVar6 ||
      (bVar6 = CEditorBaseObject::HasBaseObjectFlag((CEditorBaseObject *)this,8), !bVar6)))) {
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
      auVar5._8_4_ = local_170;
      auVar5._0_8_ = local_178;
      auVar4._8_4_ = local_170;
      auVar4._0_8_ = local_178;
      auVar18._8_4_ = local_170;
      auVar18._0_8_ = local_178;
      if ((local_158 == local_168) && (_local_178 = auVar5, local_154 == local_164)) {
        _local_178 = auVar18;
        if ((local_150 == local_160) && (_local_178 = auVar4, !NAN(local_150) && !NAN(local_160))) {
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
      dVar17 = atan2((double)local_168,(double)local_160);
      local_138.x = (float)dVar17;
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x58) + 0x108);
      Ogre::Quaternion::FromAngleAxis(local_1e8,&local_138,(Vector3 *)&Ogre::Vector3::UNIT_Y);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x58),local_1e8);
      local_164 = local_164 * 0.5;
      local_168 = local_168 * 0.5;
      local_160 = local_160 * 0.5;
      local_208.z = local_160 + local_150;
      local_208.y = local_164 + local_154 + 0.5;
      local_208.x = local_168 + local_158;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x58),&local_208);
    }
    else if (iVar2 == 0) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x50))();
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x90);
      getMaxRadiusAtPercent(this,param_2);
      getMinRadiusAtPercent(this,param_2);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x48));
      fVar14 = (float)getMaxRadiusAtPercent(this,param_2);
      fVar15 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar15 <= fVar14) {
        fVar14 = fVar15;
      }
      fVar15 = (float)getMaxRadiusAtPercent(this,param_2);
      fVar16 = (float)getMinRadiusAtPercent(this,param_2);
      if (fVar15 <= fVar16) {
        fVar15 = fVar16;
      }
      uVar13 = -(uint)(0.05 < fVar14 / fVar15);
      fVar16 = (float)getAngleOfReleaseAtPercent(this,param_2);
      pvVar10 = Ogre::Entity::getSubEntity
                          (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
      if (pvVar10 != (void *)0x0) {
        plVar11 = Ogre::Entity::getSubEntity
                            (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
        lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
        pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
        if (pvVar10 != (void *)0x0) {
          plVar11 = Ogre::Entity::getSubEntity
                              (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
          lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
          pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
          pvVar10 = Ogre::Technique::getPass(pvVar10,0);
          if (pvVar10 != (void *)0x0) {
            plVar11 = Ogre::Entity::getSubEntity
                                (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
            lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
            pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
            pvVar10 = Ogre::Technique::getPass(pvVar10,0);
            if ((short)((ulong)(*(long *)((long)pvVar10 + 0xf0) - *(long *)((long)pvVar10 + 0xe8))
                       >> 3) != 0) {
              plVar11 = Ogre::Entity::getSubEntity
                                  (*(void **)(*(long *)(this->m_ShapeData100 + 0x48) + 0x60),0);
              lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
              pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
              pvVar10 = Ogre::Technique::getPass(pvVar10,0);
              this_00 = Ogre::Pass::getTextureUnitState(pvVar10,0);
              Ogre::TextureUnitState::setTextureScroll
                        (this_00,(fVar16 / -360.0 + 1.0) * 0.5,
                         (float)(~uVar13 & 0x3d4ccccd | (uint)(fVar14 / fVar15) & uVar13) * -0.5);
            }
          }
        }
      }
      fVar14 = (float)getAngleOffsetAtPercent(this,param_2);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x48) + 0x108);
      local_58[0] = Ogre::Math::AngleUnitsToRadians((180.0 - fVar14) - fVar16);
      Ogre::Quaternion::FromAngleAxis
                ((Quaternion *)&local_1c8,local_58,(Vector3 *)&Ogre::Vector3::UNIT_Y);
      this_01 = (Quaternion *)(**(code **)(*(long *)this->m_pSceneNode + 0x1f8))();
      local_1d8 = Ogre::Quaternion::operator*(this_01,&local_1c8);
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x48),&local_1d8);
      auVar18 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_138.z = auVar18._8_4_;
      local_138.y = auVar18._4_4_;
      local_138.x = auVar18._0_4_;
      local_138.y = local_138.y + 0.25;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x48),&local_138);
    }
    else if (iVar2 == 2) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x50),1);
      fVar14 = (float)getMaxRadiusAtPercent(this,param_2);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x90))
                (~-(uint)(0.1 < fVar14) & 0x3dcccccd | (uint)fVar14 & -(uint)(0.1 < fVar14));
      local_188 = (Vector3)CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x50),&local_188);
    }
    else if (iVar2 == 4) {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x60),1);
      local_148 = (Vector3)CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x60),&local_148);
      pcVar3 = *(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x108);
      uVar7 = (**(code **)(*(long *)this->m_pSceneNode + 0x1f8))();
      (*pcVar3)(*(undefined8 *)(this->m_ShapeData100 + 0x60),uVar7);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x60) + 0x98))();
    }
    else {
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x50))
                (*(long **)(this->m_ShapeData100 + 0x50),1);
      (**(code **)(**(long **)(this->m_ShapeData100 + 0x50) + 0x90))();
      local_198 = (Vector3)CPositionableObject::getPosition((CPositionableObject *)this,true);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this->m_ShapeData100 + 0x50),&local_198);
    }
  }
  return;
}

