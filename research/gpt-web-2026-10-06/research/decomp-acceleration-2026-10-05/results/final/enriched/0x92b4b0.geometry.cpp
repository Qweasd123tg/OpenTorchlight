void CAutomap::setFullMap(std::wstring param_1, float param_2, float param_3, Ogre::Vector3& param_4, Ogre::Vector3& param_5, float param_6)
{
    int iVar4;
    code *pcVar5;
    long long *puVar6;
    int *puVar7;
    char cVar8;
    long *plVar9;
    CFileSystem *pCVar10;
    void *pvVar11;
    TextureUnitState *pTVar12;
    long lVar13;
    long lVar14;
    double dVar15;
    char local_148 [8];
    string local_140;
    std::wstring local_138;
    string local_128;
    char **local_118;
    void *local_110;
    int *local_108;
    char **local_f8;
    void *local_f0;
    int *local_e8;
    char **local_d8;
    void *local_d0;
    int *local_c8;
    ColourValue local_b8;
    Billboard *local_a0;
    int local_5c;
    float local_58 [7];

    m_bFullMap = true;
    plVar9 = Ogre::MaterialManager::getSingleton();
    pcVar5 = *(code **)(*plVar9 + 0xb0);

    cVar8 = (*pcVar5)(plVar9,"AutomapStatic");
    if (!cVar8) {
        plVar9 = Ogre::MaterialManager::getSingleton();
        pcVar5 = *(code **)(*plVar9 + 0x28);

        (*pcVar5)(&local_118,plVar9,"AutomapStatic", &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
        local_f8 = &PTR__MaterialPtr_00fa44d0;
        local_f0 = local_110;
        local_e8 = local_108;
        if (local_108 != NULL) {
            *local_108 = *local_108 + 1;
        }
        local_118 = &PTR__SharedPtr_00fa45d0;
        if ((local_108 != NULL) && (iVar4 = *local_108, *local_108 = iVar4 - 1, iVar4 - 1 == 0))
        {

            Ogre::((SharedPtr<Ogre::Resource> *)&local_118)->destroy();
        }
        *(char *)((long)local_f0 + 0xf0) = 0;

        Ogre::Material::setLightingEnabled(local_f0,false);
        pvVar11 = Ogre::Material::getTechnique(local_f0,0);
        pvVar11 = Ogre::Technique::getPass(pvVar11,0);
        Ogre::Pass::setDepthCheckEnabled(pvVar11,true);
        Ogre::Pass::setSelfIllumination(pvVar11,0.0,0.0,0.0);
        Ogre::Pass::setDepthWriteEnabled(pvVar11,false);
        Ogre::Material::setSceneBlending(local_f0,0);
        Ogre::Material::setCullingMode(local_f0,1);
        local_148 = (char  [8])&DAT_01423a38;

        std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);

        std::((std::wstring *)&local_138)->basic_string((std::wstring *)&::EMPTY_WSTRING);
        local_128._M_p = &DAT_01423a38;

        pCVar10 = CFileSystem::getSingleton();
        pCVar10->getFileInfo((std::wstring *)param_1._M_p, (CFileInfo *)local_148, false, true, false);
        pTVar12 = Ogre::Pass::createTextureUnitState(pvVar11,&local_140,0);
        Ogre::TextureUnitState::setTextureFiltering(pTVar12,2,2,0);
    }
    else {
        plVar9 = Ogre::MaterialManager::getSingleton();
        pcVar5 = *(code **)(*plVar9 + 0xa0);

        (*pcVar5)(&local_d8,plVar9,"AutomapStatic");
        local_f8 = &PTR__MaterialPtr_00fa44d0;
        local_f0 = local_d0;
        local_e8 = local_c8;
        if (local_c8 != NULL) {
            *local_c8 = *local_c8 + 1;
        }
        local_d8 = &PTR__SharedPtr_00fa45d0;
        if ((local_c8 != NULL) && (iVar4 = *local_c8, *local_c8 = iVar4 - 1, iVar4 - 1 == 0)) {

            Ogre::((SharedPtr<Ogre::Resource> *)&local_d8)->destroy();
        }
        local_148 = (char  [8])&DAT_01423a38;

        std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);

        std::((std::wstring *)&local_138)->basic_string((std::wstring *)&::EMPTY_WSTRING);
        local_128._M_p = &DAT_01423a38;

        pCVar10 = CFileSystem::getSingleton();
        pCVar10->getFileInfo((std::wstring *)param_1._M_p, (CFileInfo *)local_148, false, true, false);
        pvVar11 = Ogre::Material::getTechnique(local_f0,0);
        pvVar11 = Ogre::Technique::getPass(pvVar11,0);
        pTVar12 = Ogre::Pass::getTextureUnitState(pvVar11,0);
        Ogre::TextureUnitState::setTextureName(pTVar12,&local_140,2);
    }
    local_f8 = &PTR__SharedPtr_00fa4590;
    if ((local_e8 != NULL) && (iVar4 = *local_e8, *local_e8 = iVar4 - 1, iVar4 - 1 == 0)) {
        Ogre::((SharedPtr<Ogre::Material> *)&local_f8)->destroy();
    }
    pcVar5 = *(code **)(*(long *)m_pStaticTileBillboardSet + 0x280);

    (*pcVar5)(m_pStaticTileBillboardSet,"AutomapStatic");
    (**(code **)(*(long *)m_pStaticTileBillboardSet + 0x260))(param_2);
    (**(code **)(*(long *)m_pStaticTileBillboardSet + 0x270))(param_3);
    local_a0 = Ogre::BillboardSet::createBillboard(m_pStaticTileBillboardSet,param_4, (ColourValue *)&Ogre::ColourValue::White);
    Ogre::Billboard::setTexcoordRect(local_a0,1.0,0.0,0.0,1.0);
    Ogre::Billboard::setDimensions(local_a0, param_2, param_3);
    dVar15 = atan2((double)param_5->x,(double)param_5->z);
    local_58[0] = (float)dVar15 + param_6 * 0.017453292;
    Ogre::Billboard::setRotation(local_a0,local_58);
    local_b8.r = 1.0;
    local_b8.g = 1.0;
    local_b8.b = 1.0;
    local_b8.a = 1.0;
    Ogre::Billboard::setColour(local_a0,&local_b8);
    puVar6 = *(long long **)&(m_vMapTileBillboards).m_nCount;
    if (puVar6 == *(long long **)&(m_vMapTileBillboards).m_nGrowBy) {
        std::vector<Ogre::Billboard*,std::allocator<Ogre::Billboard*>>::_M_insert_aux((vector<Ogre::Billboard*,std::allocator<Ogre::Billboard*>> *) &m_vMapTileBillboards,puVar6,&local_a0);
    }
    else {
        lVar13 = 0;
        if (puVar6 != NULL) {
            *puVar6 = local_a0;
            lVar13._0_4_ = m_vMapTileBillboards.size();
            lVar13._4_4_ = (m_vMapTileBillboards).m_nCapacity;
        }
        *(long *)&(m_vMapTileBillboards).m_nCount = lVar13 + 8;
    }
    local_5c = 0x42c80000;
    puVar7 = *(int **)&(m_vMapTileRevealValues).m_nCount;
    if (puVar7 == *(int **)&(m_vMapTileRevealValues).m_nGrowBy) {
        std::((vector<float,std::allocator<float>> *)&m_vMapTileRevealValues,puVar7,&local_5c)->_M_insert_aux();
    }
    else {
        lVar14 = 0;
        if (puVar7 != NULL) {
            *puVar7 = 0x42c80000;
            lVar14._0_4_ = m_vMapTileRevealValues.size();
            lVar14._4_4_ = (m_vMapTileRevealValues).m_nCapacity;
        }
        *(long *)&(m_vMapTileRevealValues).m_nCount = lVar14 + 4;
    }
    m_bTilesChanged = true;
}
