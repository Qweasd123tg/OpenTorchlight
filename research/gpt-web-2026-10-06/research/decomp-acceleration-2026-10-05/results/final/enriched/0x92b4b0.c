
/* WARNING: Removing unreachable block (ram,0x0092beb9) */
/* WARNING: Removing unreachable block (ram,0x0092be81) */
/* WARNING: Removing unreachable block (ram,0x0092befa) */
/* WARNING: Removing unreachable block (ram,0x0092be57) */
/* WARNING: Removing unreachable block (ram,0x0092be9d) */
/* WARNING: Removing unreachable block (ram,0x0092bf16) */
/* WARNING: Removing unreachable block (ram,0x0092beab) */
/* WARNING: Removing unreachable block (ram,0x0092be8f) */
/* WARNING: Removing unreachable block (ram,0x0092bf08) */
/* WARNING: Removing unreachable block (ram,0x0092be65) */
/* WARNING: Removing unreachable block (ram,0x0092be73) */
/* WARNING: Removing unreachable block (ram,0x0092be0b) */
/* CAutomap::setFullMap(std::wstring, float, float, Ogre::Vector3&, Ogre::Vector3&, float) */

void __thiscall
CAutomap::setFullMap
          (CAutomap *this,wstring param_1,float param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,float param_6)

{
  wchar32 *pwVar1;
  int *piVar2;
  wchar32 wVar3;
  int iVar4;
  code *pcVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  char cVar8;
  long *plVar9;
  CFileSystem *pCVar10;
  void *pvVar11;
  TextureUnitState *pTVar12;
  long lVar13;
  long lVar14;
  double dVar15;
  undefined1 local_148 [8];
  string local_140;
  wstring local_138;
  int local_130;
  int local_12c;
  string local_128;
  bool local_120;
  undefined **local_118;
  void *local_110;
  int *local_108;
  undefined **local_f8;
  void *local_f0;
  int *local_e8;
  undefined4 local_e0;
  undefined **local_d8;
  void *local_d0;
  int *local_c8;
  ColourValue local_b8;
  Billboard *local_a0;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68;
  undefined4 local_5c;
  float local_58 [7];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];
  
  this->m_bFullMap = true;
  plVar9 = Ogre::MaterialManager::getSingleton();
  pcVar5 = *(code **)(*plVar9 + 0xb0);
                    /* try { // try from 0092b512 to 0092b516 has its CatchHandler @ 0092bec7 */
  std::string::string((string *)&local_68,"AutomapStatic",local_39);
                    /* try { // try from 0092b51d to 0092b51f has its CatchHandler @ 0092bee8 */
  cVar8 = (*pcVar5)(plVar9,(string *)&local_68);
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_68 + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  if (cVar8 == '\0') {
    plVar9 = Ogre::MaterialManager::getSingleton();
    pcVar5 = *(code **)(*plVar9 + 0x28);
                    /* try { // try from 0092b934 to 0092b938 has its CatchHandler @ 0092be34 */
    std::string::string((string *)local_88,"AutomapStatic",&local_3b);
                    /* try { // try from 0092b957 to 0092b95a has its CatchHandler @ 0092be32 */
    (*pcVar5)(&local_118,plVar9,(string *)local_88,
              &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
    local_e0 = 0;
    local_f8 = &PTR__MaterialPtr_00fa44d0;
    local_f0 = local_110;
    local_e8 = local_108;
    if (local_108 != (int *)0x0) {
      *local_108 = *local_108 + 1;
    }
    local_118 = &PTR__SharedPtr_00fa45d0;
    if ((local_108 != (int *)0x0) && (iVar4 = *local_108, *local_108 = iVar4 + -1, iVar4 + -1 == 0))
    {
                    /* try { // try from 0092b9bd to 0092b9c1 has its CatchHandler @ 0092bed1 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_118);
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_88[0] + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    *(undefined1 *)((long)local_f0 + 0xf0) = 0;
                    /* try { // try from 0092b9f0 to 0092ba59 has its CatchHandler @ 0092bdce */
    Ogre::Material::setLightingEnabled(local_f0,false);
    pvVar11 = Ogre::Material::getTechnique(local_f0,0);
    pvVar11 = Ogre::Technique::getPass(pvVar11,0);
    Ogre::Pass::setDepthCheckEnabled(pvVar11,true);
    Ogre::Pass::setSelfIllumination(pvVar11,0.0,0.0,0.0);
    Ogre::Pass::setDepthWriteEnabled(pvVar11,false);
    Ogre::Material::setSceneBlending(local_f0,0);
    Ogre::Material::setCullingMode(local_f0,1);
    local_148 = (undefined1  [8])&DAT_01423a38;
                    /* try { // try from 0092ba71 to 0092ba75 has its CatchHandler @ 0092be2c */
    std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);
                    /* try { // try from 0092ba7f to 0092ba83 has its CatchHandler @ 0092be16 */
    std::wstring::wstring((wstring *)&local_138,(wstring_conflict *)&::EMPTY_WSTRING);
    local_130 = 4;
    local_12c = 3;
    local_128._M_p = &DAT_01423a38;
    local_120 = false;
                    /* try { // try from 0092baa2 to 0092bae1 has its CatchHandler @ 0092becc */
    pCVar10 = CFileSystem::getSingleton();
    CFileSystem::getFileInfo
              (pCVar10,(wstring *)param_1._M_p,(CFileInfo *)local_148,false,true,false);
    pTVar12 = Ogre::Pass::createTextureUnitState(pvVar11,&local_140,0);
    Ogre::TextureUnitState::setTextureFiltering(pTVar12,2,2,0);
    if ((allocator *)(local_128._M_p + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_128._M_p + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128._M_p + -0x18));
      }
    }
    if ((allocator *)(local_138._M_p + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      pwVar1 = local_138._M_p + -2;
      wVar3 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138._M_p + -6));
      }
    }
    if ((allocator *)(local_140._M_p + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_140._M_p + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_140._M_p + -0x18));
      }
    }
    if ((allocator *)((long)local_148 + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)((long)local_148 + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)((long)local_148 + -0x18));
      }
    }
  }
  else {
    plVar9 = Ogre::MaterialManager::getSingleton();
    pcVar5 = *(code **)(*plVar9 + 0xa0);
                    /* try { // try from 0092b572 to 0092b576 has its CatchHandler @ 0092bdf9 */
    std::string::string((string *)local_78,"AutomapStatic",&local_3a);
                    /* try { // try from 0092b585 to 0092b588 has its CatchHandler @ 0092bde6 */
    (*pcVar5)(&local_d8,plVar9,(string *)local_78);
    local_e0 = 0;
    local_f8 = &PTR__MaterialPtr_00fa44d0;
    local_f0 = local_d0;
    local_e8 = local_c8;
    if (local_c8 != (int *)0x0) {
      *local_c8 = *local_c8 + 1;
    }
    local_d8 = &PTR__SharedPtr_00fa45d0;
    if ((local_c8 != (int *)0x0) && (iVar4 = *local_c8, *local_c8 = iVar4 + -1, iVar4 + -1 == 0)) {
                    /* try { // try from 0092b5f4 to 0092b5f8 has its CatchHandler @ 0092bee6 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_d8);
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_78[0] + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    local_148 = (undefined1  [8])&DAT_01423a38;
                    /* try { // try from 0092b625 to 0092b629 has its CatchHandler @ 0092be42 */
    std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);
                    /* try { // try from 0092b633 to 0092b637 has its CatchHandler @ 0092be55 */
    std::wstring::wstring((wstring *)&local_138,(wstring_conflict *)&::EMPTY_WSTRING);
    local_130 = 4;
    local_12c = 3;
    local_128._M_p = &DAT_01423a38;
    local_120 = false;
                    /* try { // try from 0092b656 to 0092b6a7 has its CatchHandler @ 0092be44 */
    pCVar10 = CFileSystem::getSingleton();
    CFileSystem::getFileInfo
              (pCVar10,(wstring *)param_1._M_p,(CFileInfo *)local_148,false,true,false);
    pvVar11 = Ogre::Material::getTechnique(local_f0,0);
    pvVar11 = Ogre::Technique::getPass(pvVar11,0);
    pTVar12 = Ogre::Pass::getTextureUnitState(pvVar11,0);
    Ogre::TextureUnitState::setTextureName(pTVar12,&local_140,2);
    if ((allocator *)(local_128._M_p + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_128._M_p + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128._M_p + -0x18));
      }
    }
    if ((allocator *)(local_138._M_p + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      pwVar1 = local_138._M_p + -2;
      wVar3 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138._M_p + -6));
      }
    }
    if ((allocator *)(local_140._M_p + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_140._M_p + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_140._M_p + -0x18));
      }
    }
    if ((allocator *)((long)local_148 + -0x18) !=
        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)((long)local_148 + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)((long)local_148 + -0x18));
      }
    }
  }
  local_f8 = &PTR__SharedPtr_00fa4590;
  if ((local_e8 != (int *)0x0) && (iVar4 = *local_e8, *local_e8 = iVar4 + -1, iVar4 + -1 == 0)) {
    Ogre::SharedPtr<Ogre::Material>::destroy((SharedPtr<Ogre::Material> *)&local_f8);
  }
  pcVar5 = *(code **)(*(long *)this->m_pStaticTileBillboardSet + 0x280);
                    /* try { // try from 0092b742 to 0092b746 has its CatchHandler @ 0092be36 */
  std::string::string((string *)local_98,"AutomapStatic",&local_3c);
                    /* try { // try from 0092b74e to 0092b750 has its CatchHandler @ 0092bdfe */
  (*pcVar5)(this->m_pStaticTileBillboardSet,(string *)local_98);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  (**(code **)(*(long *)this->m_pStaticTileBillboardSet + 0x260))(param_2);
  (**(code **)(*(long *)this->m_pStaticTileBillboardSet + 0x270))(param_3);
  local_a0 = Ogre::BillboardSet::createBillboard
                       (this->m_pStaticTileBillboardSet,param_4,
                        (ColourValue *)&Ogre::ColourValue::White);
  Ogre::Billboard::setTexcoordRect(local_a0,1.0,0.0,0.0,1.0);
  Ogre::Billboard::setDimensions(local_a0,param_2,param_3);
  dVar15 = atan2((double)param_5->x,(double)param_5->z);
  local_58[0] = (float)dVar15 + param_6 * 0.017453292;
  Ogre::Billboard::setRotation(local_a0,local_58);
  local_b8.r = 1.0;
  local_b8.g = 1.0;
  local_b8.b = 1.0;
  local_b8.a = 1.0;
  Ogre::Billboard::setColour(local_a0,&local_b8);
  puVar6 = *(undefined8 **)&(this->m_vMapTileBillboards).m_nCount;
  if (puVar6 == *(undefined8 **)&(this->m_vMapTileBillboards).m_nGrowBy) {
    std::vector<Ogre::Billboard*,std::allocator<Ogre::Billboard*>>::_M_insert_aux
              ((vector<Ogre::Billboard*,std::allocator<Ogre::Billboard*>> *)
               &this->m_vMapTileBillboards,puVar6,&local_a0);
  }
  else {
    lVar13 = 0;
    if (puVar6 != (undefined8 *)0x0) {
      *puVar6 = local_a0;
      lVar13._0_4_ = (this->m_vMapTileBillboards).m_nCount;
      lVar13._4_4_ = (this->m_vMapTileBillboards).m_nCapacity;
    }
    *(long *)&(this->m_vMapTileBillboards).m_nCount = lVar13 + 8;
  }
  local_5c = 0x42c80000;
  puVar7 = *(undefined4 **)&(this->m_vMapTileRevealValues).m_nCount;
  if (puVar7 == *(undefined4 **)&(this->m_vMapTileRevealValues).m_nGrowBy) {
    std::vector<float,std::allocator<float>>::_M_insert_aux
              ((vector<float,std::allocator<float>> *)&this->m_vMapTileRevealValues,puVar7,&local_5c
              );
  }
  else {
    lVar14 = 0;
    if (puVar7 != (undefined4 *)0x0) {
      *puVar7 = 0x42c80000;
      lVar14._0_4_ = (this->m_vMapTileRevealValues).m_nCount;
      lVar14._4_4_ = (this->m_vMapTileRevealValues).m_nCapacity;
    }
    *(long *)&(this->m_vMapTileRevealValues).m_nCount = lVar14 + 4;
  }
  this->m_bTilesChanged = true;
  return;
}

