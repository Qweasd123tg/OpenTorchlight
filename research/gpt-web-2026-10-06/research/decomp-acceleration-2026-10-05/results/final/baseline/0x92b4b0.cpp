void CAutomap::setFullMap(std::wstring param_1, float param_2, float param_3, Ogre::Vector3& param_4, Ogre::Vector3& param_5, float param_6)
{
    int iVar4;
    code *pcVar5;
    long long *puVar6;
    int *puVar7;
    char cVar8;
    unsigned short uVar9;
    long *plVar10;
    CFileSystem *pCVar11;
    long long uVar12;
    long lVar13;
    long lVar14;
    string *psVar15;
    double dVar16;
    char local_148 [8];
    string local_140;
    std::wstring local_138;
    string local_128;
    char **local_118;
    long local_110;
    int *local_108;
    char **local_f8;
    long local_f0;
    int *local_e8;
    char **local_d8;
    long local_d0;
    int *local_c8;
    Radian *local_a0;
    int local_5c;

    m_bFullMap = true;
    plVar10 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar5 = *(code **)(*plVar10 + 0xb0);

    cVar8 = (*pcVar5)(plVar10,"AutomapStatic");
    if (!cVar8) {
        plVar10 = (long *)Ogre::MaterialManager::getSingleton();
        pcVar5 = *(code **)(*plVar10 + 0x28);

        (*pcVar5)(&local_118,plVar10,"AutomapStatic", &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
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
        *(char *)(local_f0 + 0xf0) = 0;

        Ogre::Material::setLightingEnabled(SUB81(local_f0,0));
        uVar9 = Ogre::Material::getTechnique((unsigned short)local_f0);
        psVar15 = (string *)Ogre::Technique::getPass(uVar9);
        Ogre::Pass::setDepthCheckEnabled(SUB81(psVar15,0));
        Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
        Ogre::Pass::setDepthWriteEnabled(SUB81(psVar15,0));
        Ogre::Material::setSceneBlending(local_f0,0);
        Ogre::Material::setCullingMode(local_f0,1);
        local_148 = (char  [8])&DAT_01423a38;

        std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);

        std::((std::wstring *)&local_138)->basic_string((std::wstring *)&::EMPTY_WSTRING);
        local_128._M_p = &DAT_01423a38;

        pCVar11 = CFileSystem::getSingleton();
        pCVar11->getFileInfo((std::wstring *)param_1._M_p, (CFileInfo *)local_148, false, true, false);
        uVar12 = Ogre::Pass::createTextureUnitState(psVar15,(unsigned short)&local_140);
        Ogre::TextureUnitState::setTextureFiltering(uVar12,2,2,0);
    }
    else {
        plVar10 = (long *)Ogre::MaterialManager::getSingleton();
        pcVar5 = *(code **)(*plVar10 + 0xa0);

        (*pcVar5)(&local_d8,plVar10,"AutomapStatic");
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

        pCVar11 = CFileSystem::getSingleton();
        pCVar11->getFileInfo((std::wstring *)param_1._M_p, (CFileInfo *)local_148, false, true, false);
        uVar9 = Ogre::Material::getTechnique((unsigned short)local_f0);
        uVar9 = Ogre::Technique::getPass(uVar9);
        uVar12 = Ogre::Pass::getTextureUnitState(uVar9);
        Ogre::TextureUnitState::setTextureName(uVar12,&local_140,2);
    }
    local_f8 = &PTR__SharedPtr_00fa4590;
    if ((local_e8 != NULL) && (iVar4 = *local_e8, *local_e8 = iVar4 - 1, iVar4 - 1 == 0)) {
        Ogre::((SharedPtr<Ogre::Material> *)&local_f8)->destroy();
    }
    pcVar5 = *(code **)(*(long *)m_pStaticTileBillboardSet + 0x280);

    (*pcVar5)(m_pStaticTileBillboardSet,"AutomapStatic");
    (**(code **)(*(long *)m_pStaticTileBillboardSet + 0x260))(param_2);
    (**(code **)(*(long *)m_pStaticTileBillboardSet + 0x270))(param_3);
    local_a0 = (Radian *)Ogre::BillboardSet::createBillboard(m_pStaticTileBillboardSet,param_4);
    Ogre::Billboard::setTexcoordRect(1.0,0.0,0.0,1.0);
    Ogre::Billboard::setDimensions(param_2,param_3);
    dVar16 = atan2((double)*(float *)param_5,(double)*(float *)((long)param_5 + 8));
    Ogre::Billboard::setRotation(local_a0);
    Ogre::Billboard::setColour((ColourValue *)local_a0);
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
