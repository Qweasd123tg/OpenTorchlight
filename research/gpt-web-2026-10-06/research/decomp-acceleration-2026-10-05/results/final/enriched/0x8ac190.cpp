void CGenericModel::reInitialize(Ogre::Entity* param_1, bool param_2)
{
    wchar_t wVar4;
    code *pcVar5;
    char cVar6;
    bool bVar7;
    char cVar8;
    short uVar9;
    short sVar10;
    unsigned int uVar11;
    unsigned int uVar12;
    int iVar13;
    void *pvVar14;
    void *pvVar15;
    unsigned long uVar16;
    long *plVar17;
    string *psVar18;
    long *plVar19;
    long lVar20;
    CMasterResourceManager *pCVar21;
    CFileSystem *pCVar22;
    TextureUnitState *pTVar23;
    unsigned long uVar24;
    unsigned long uVar25;
    long lVar26;
    long lVar27;
    long lVar28;
    long lVar30;
    long lVar31;
    long lVar32;
    int iVar33;
    long long *puVar34;
    unsigned int uVar35;
    unsigned int local_494;
    int local_490;
    char local_428 [8];
    string local_420;
    std::wstring local_418;
    string local_408;
    char local_3f8 [8];
    string local_3f0;
    std::wstring local_3e8;
    string local_3d8;
    char **local_3c8;
    char *local_3c0;
    wchar_t *local_3b8;
    char **local_3a8;
    long long local_3a0;
    int *local_398;
    char **local_388;
    void *local_380;
    int *local_378;
    SharedPtr<Ogre::GpuProgramParameters> local_368 [8];
    void *local_360;
    char **local_348;
    long long local_340;
    int *local_338;
    char **local_328;
    void *local_320;
    int *local_318;
    char **local_308;
    long long local_300;
    int *local_2f8;
    char **local_2e8;
    void *local_2e0;
    int *local_2d8;
    ColourValue local_2c8;
    ColourValue local_2b8;
    long long *local_2a0;
    long local_238 [2];
    long local_218 [2];
    long local_208 [2];
    string local_1e8 [16];
    string local_1c8 [16];
    string local_1a8 [16];
    string local_188 [16];
    long local_d8 [2];
    long local_c8 [2];
    long local_98 [2];
    allocator local_4d;
    allocator local_4b;
    allocator local_49;
    allocator local_47;
    allocator local_3c;

    uVar11 = Ogre::Entity::getNumSubEntities(param_1);
    if (param_2) {
        m_ModelData1C8[0x70] = '\0';
        releaseUniqueMaterials();
        lVar20 = *(long *)(m_ModelData1C8 + 0x40);
        lVar28 = *(long *)(m_ModelData1C8 + 0x48);
        lVar27 = lVar20;
        if (lVar20 != lVar28) {
            do {
                lVar27 = lVar27 + 0x40;
            } while (lVar28 != lVar27);
            lVar27 = *(long *)(m_ModelData1C8 + 0x40);
        }
        *(long *)(m_ModelData1C8 + 0x48) = lVar20;
        uVar24 = (unsigned long)uVar11;
        uVar16 = lVar20 - lVar27 >> 6;
        if (uVar24 < uVar16) {
            lVar27 = lVar27 + uVar24 * 0x40;
            for (lVar28 = lVar27; lVar20 != lVar28; lVar28 = lVar28 + 0x40) {
            }
            *(long *)(m_ModelData1C8 + 0x48) = lVar27;
        }
        else {

            std::((vector<CRenderableStates,std::allocator<CRenderableStates>> *) (m_ModelData1C8 + 0x40),lVar20,uVar24 - uVar16)->_M_fill_insert();
        }
        if (uVar11 != 0) {
            lVar27 = 0;
            local_494 = 0;
            do {
                plVar17 = Ogre::Entity::getSubEntity(param_1,local_494);
                lVar20 = *(long *)(m_ModelData1C8 + 0x40);
                pcVar5 = *(code **)(*plVar17 + 0x78);
                local_2a0 = (long long *)Ogre::NedAllocImpl::allocBytes(0x10,NULL,0,NULL);
                if (local_2a0 != NULL) {
                    *local_2a0 = &PTR__holder_00fd18b0;
                    local_2a0[1] = lVar20 + lVar27;
                }

                (*pcVar5)(plVar17);
                if (local_2a0 != NULL) {
                    (**(code **)*local_2a0)();
                    Ogre::NedAllocImpl::deallocBytes(local_2a0);
                }
                lVar20 = *(long *)(m_ModelData1C8 + 0x40);
                lVar28 = (**(code **)(*plVar17 + 0x10))(plVar17);
                *(long long *)(lVar27 + lVar20 + 0x10) = *(long long *)(lVar28 + 8);
                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),0, NULL);
                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                uVar16 = *(long *)((long)pvVar14 + 0xf0) - *(long *)((long)pvVar14 + 0xe8) >> 3 & 0xffff;
                uVar12 = (unsigned int)uVar16;
                uVar35 = uVar12;
                if (1 < uVar12) {
                    iVar33 = 1;
                    do {
                        pvVar15 = Ogre::Pass::getTextureUnitState(pvVar14,(unsigned short)iVar33);
                        iVar13 = std::string::compare((char *)((long)pvVar15 + 0x160));
                        uVar35 = (int)uVar16 - (unsigned int)(iVar13 == 0);
                        uVar16 = (unsigned long)uVar35;
                        iVar33 = iVar33 + 1;
                    } while (iVar33 < (int)uVar12);
                }
                *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2a + lVar27) = (short)uVar35;
                (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) + 200))();
                std::((string *)(lVar27 + *(long *)(m_ModelData1C8 + 0x40) + 0x38))->assign();
                if (!m_ModelData1C8[0x5c]) {
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) + 200))()
                    ;
                    std::operator+((char *)local_208,(string *)"highlightmat_");

                    plVar19 = Ogre::MaterialManager::getSingleton();
                    cVar6 = (**(code **)(*plVar19 + 0xb0))(plVar19,(string *)local_208);
                    if (!cVar6) {
                        Ogre::Material::clone((string *)&local_328, SUB81(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) ,0),(string *)local_208);
                        pvVar14 = local_320;
                        local_328 = &PTR__SharedPtr_00fa4590;
                        if ((local_318 != NULL) && (iVar33 = *local_318, *local_318 = iVar33 - 1, iVar33 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Material> *)&local_328)->destroy();
                        }
                        *(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27) = pvVar14;
                        Ogre::Material::setLightingEnabled(pvVar14,false);
                        pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                        pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                        bVar7 = true;
                        if ((short)((unsigned long)(*(long *)((long)pvVar15 + 0xf0) - *(long *)((long)pvVar15 + 0xe8)) >> 3) != 0) {

                            pvVar14 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                            pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                            pTVar23 = Ogre::Pass::getTextureUnitState(pvVar14,0);
                            Ogre::TextureUnitState::setColourOperationEx(pTVar23,3,1,0,(ColourValue *)&Ogre::ColourValue::White, (ColourValue *)&Ogre::ColourValue::White,0.0);
                            bVar7 = true;
                        }
                    }
                    else {
                        lVar20 = *(long *)(m_ModelData1C8 + 0x40);

                        plVar19 = Ogre::MaterialManager::getSingleton();
                        (**(code **)(*plVar19 + 0xa0))(&local_348,plVar19,(string *)local_208);
                        *(long long *)(lVar27 + lVar20 + 0x18) = local_340;
                        local_348 = &PTR__SharedPtr_00fa45d0;
                        if ((local_338 != NULL) && (iVar33 = *local_338, *local_338 = iVar33 - 1, iVar33 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Resource> *)&local_348)->destroy();
                        }
                        bVar7 = false;
                    }
                }
                else {
                    psVar18 = (string *)
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) + 200))();
                    std::string::string((string *)local_208,psVar18);

                    ((STRINGS *)local_98)->uniqueName("highlightmat_");

                    std::((string *)local_208)->assign();

                    plVar19 = Ogre::MaterialManager::getSingleton();
                    cVar6 = (**(code **)(*plVar19 + 0xb0))(plVar19,(string *)local_208);
                    if (!cVar6) {
                        Ogre::Material::clone((string *)&local_2e8, SUB81(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) ,0),(string *)local_208);
                        pvVar14 = local_2e0;
                        local_2e8 = &PTR__SharedPtr_00fa4590;
                        if ((local_2d8 != NULL) && (iVar33 = *local_2d8, *local_2d8 = iVar33 - 1, iVar33 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Material> *)&local_2e8)->destroy();
                        }
                        *(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27) = pvVar14;
                        pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                        pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                        if ((short)((unsigned long)(*(long *)((long)pvVar15 + 0xf0) - *(long *)((long)pvVar15 + 0xe8)) >> 3) != 0) {

                            pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                            pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                            if (*(long *)((long)pvVar15 + 0x100) != 0) {

                                pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                                Ogre::Pass::setVertexProgram(pvVar15,"",true);
                            }
                            if (*(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2f + lVar27) == '\0') {
                                if (m_ModelData1C8[0x70]) {
                                    local_490 = 1;
                                    iVar33 = uVar35 - 1;
                                    if ((int)(uVar35 - 1) < 1) {
                                        iVar33 = local_490;
                                    }
                                    while(true) {
                                        pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                        pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                                        if ((int)((unsigned int)(*(long *)((long)pvVar15 + 0xf0) - *(long *)((long)pvVar15 + 0xe8) >> 3) & 0xffff) <= iVar33)
                                        break;

                                        pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                        pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                                        lVar20 = *(long *)((long)pvVar15 + 0xf0);
                                        lVar28 = *(long *)((long)pvVar15 + 0xe8);
                                        pvVar15 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                        pvVar15 = Ogre::Technique::getPass(pvVar15,0);
                                        Ogre::Pass::removeTextureUnitState(pvVar15,(short)(lVar20 - lVar28 >> 3) - 1);
                                    }
                                }
                                pvVar14 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                pTVar23 = Ogre::Pass::createTextureUnitState(pvVar14);
                                local_3f8 = (char  [8])&DAT_01423a38;

                                std::string::string((string *)&local_3f0,(string *)&::EMPTY_STRING);

                                std::((std::wstring *)&local_3e8)->basic_string((std::wstring *)&::EMPTY_WSTRING);
                                local_3d8._M_p = &DAT_01423a38;

                                pCVar22 = CFileSystem::getSingleton();
                                pCVar22->getFileInfo(L"media/sharedtextures/highlight.dds", (CFileInfo *)local_3f8, false, true, false);

                                Ogre::TextureUnitState::setCubicTextureName(pTVar23,&local_3f0,true);
                                Ogre::TextureUnitState::setTextureCoordSet(pTVar23,1);
                                Ogre::TextureUnitState::setTextureAddressingMode(pTVar23,2);
                                Ogre::TextureUnitState::setEnvironmentMap(pTVar23,true,3);
                                Ogre::TextureUnitState::setColourOperation(pTVar23,1);
                            }
                            else {

                                pvVar14 = Ogre::Material::getBestTechnique(pvVar14,0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                pTVar23 = Ogre::Pass::getTextureUnitState(pvVar14,0);
                                Ogre::TextureUnitState::setColourOperationEx(pTVar23,4,1,0,(ColourValue *)&Ogre::ColourValue::White, (ColourValue *)&Ogre::ColourValue::White,0.0);
                            }
                        }
                        bVar7 = true;
                    }
                    else {
                        lVar20 = *(long *)(m_ModelData1C8 + 0x40);

                        plVar19 = Ogre::MaterialManager::getSingleton();
                        (**(code **)(*plVar19 + 0xa0))
                        ((SharedPtr<Ogre::Resource> *)&local_308,plVar19,(string *)local_208);
                        *(long long *)(lVar20 + lVar27 + 0x18) = local_300;
                        local_308 = &PTR__SharedPtr_00fa45d0;
                        if ((local_2f8 != NULL) && (iVar33 = *local_2f8, *local_2f8 = iVar33 - 1, iVar33 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Resource> *)&local_308)->destroy();
                        }
                        bVar7 = false;
                    }
                    LAB_008acb1f:
                }
                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),0, NULL);
                if (pvVar14 == NULL) {
                    LAB_008acc12:
                    lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                }
                else {

                    std::string::string((string *)local_c8, *(char **)(*(long *)(m_ModelData1C8 + 0x40) + 0x38 + lVar27), &local_3c);

                    ((STRINGS *)local_d8)->StringUpper((string *)local_c8);

                    lVar20 = std::string::find((char *)local_d8,0xfd115e,0);
                    if (lVar20 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2f + lVar27) = 1;
                        m_ModelData1C8[0x72] = '\x01';
                    }
                    uVar12 = KSETTINGS_ALLOW_HWSKINNING;
                    pCVar21 = CMasterResourceManager::getSingleton();
                    iVar33 = pCVar21->m_pSettings->GetInt(uVar12)
                    ;
                    if (iVar33 != 1) goto LAB_008acc12;
                    pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),0, NULL);
                    pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                    cVar6 = *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar27);
                    if (*(long *)((long)pvVar14 + 0x100) == 0) {
                        LAB_008ada92:
                        if (((*(long *)(m_ModelData118 + 0x18) != 0) && (m_ModelData1C8[0x21])) && (!cVar6)) {
                            Ogre::Entity::getMesh(param_1);
                            sVar10 = Ogre::Mesh::getMaxBoneAssignments();
                            *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2c + lVar27) = sVar10;
                            if (sVar10 != 0) {
                                if (sVar10 == 2) {
                                    if ((int)uVar35 < 2) {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningTwo",true);

                                        std::string::~string("Ogre/HardwareSkinningTwo");
                                    }
                                    else {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningTwoSecondary",true);

                                        std::string::~string("Ogre/HardwareSkinningTwoSecondary");
                                    }
                                }
                                else if (sVar10 == 3) {
                                    if ((int)uVar35 < 2) {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningThree",true);

                                        std::string::~string("Ogre/HardwareSkinningThree");
                                    }
                                    else {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningThreeSecondary",true);

                                        std::string::~string("Ogre/HardwareSkinningThreeSecondary");
                                    }
                                }
                                else if (sVar10 == 1) {
                                    if ((int)uVar35 < 2) {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningOne",true);

                                        std::string::~string("Ogre/HardwareSkinningOne");
                                    }
                                    else {

                                        Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningOneSecondary",true);

                                        std::string::~string("Ogre/HardwareSkinningOneSecondary");
                                    }
                                }
                                else if ((int)uVar35 < 2) {

                                    Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinning",true);

                                    std::string::~string("Ogre/HardwareSkinning");
                                }
                                else {

                                    Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningSecondary",true);

                                    std::string::~string("Ogre/HardwareSkinningSecondary");
                                }

                                Ogre::Pass::getVertexProgramParameters((char (*) [32])local_368,pvVar14);

                                Ogre::GpuProgramParameters::setNamedAutoConstant(local_360,"texViewProj",0x79,0);

                                Ogre::SharedPtr<Ogre::GpuProgramParameters>::~SharedPtr(local_368);

                                std::string::~string("texViewProj");
                                Ogre::Material::compile(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),true);
                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                if (*(long *)((long)pvVar14 + 0x100) != 0) {
                                    pvVar14 = Ogre::Pass::getVertexProgram(pvVar14);
                                    cVar8 = (**(code **)(**(long **)((long)pvVar14 + 8) + 0x1c8))();
                                    if (cVar8) {
                                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar27) = 1;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        pvVar15 = Ogre::Pass::getVertexProgram(pvVar14);
                        cVar8 = (**(code **)(**(long **)((long)pvVar15 + 8) + 0x1c8))();
                        if (!cVar8) goto LAB_008ada92;
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar27) = 1;
                        Ogre::Entity::getMesh(param_1);
                        uVar9 = Ogre::Mesh::getMaxBoneAssignments();
                        *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2c + lVar27) = uVar9;
                    }
                    lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                    if (((*(char *)(lVar20 + 2) != '\0') && (bVar7)) && ((sVar10 = *(short *)(lVar20 + 0x2c), sVar10 != 0 && (!cVar6)))) {
                        if (sVar10 == 2) {
                            if ((int)uVar35 < 2) {

                                std::string::string(local_1a8,"Ogre/HardwareSkinningTwo",&local_49);

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,(string *)local_1a8,true);

                                std::string::~string(local_1a8);
                            }
                            else {

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningTwoSecondary",true);
                            }
                        }
                        else if (sVar10 == 3) {
                            if ((int)uVar35 < 2) {

                                std::string::string(local_188,"Ogre/HardwareSkinningThree",&local_47);

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,(string *)local_188,true);

                                std::string::~string(local_188);
                            }
                            else {

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningThreeSecondary",true);
                            }
                        }
                        else if (sVar10 == 1) {
                            if ((int)uVar35 < 2) {

                                std::string::string(local_1c8,"Ogre/HardwareSkinningOne",&local_4b);

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,(string *)local_1c8,true);

                                std::string::~string(local_1c8);
                            }
                            else {

                                pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                                pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                                Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningOneSecondary",true);
                            }
                        }
                        else if ((int)uVar35 < 2) {

                            std::string::string(local_1e8,"Ogre/HardwareSkinning",&local_4d);

                            pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                            pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                            Ogre::Pass::setVertexProgram(pvVar14,(string *)local_1e8,true);

                            std::string::~string(local_1e8);
                        }
                        else {

                            pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),0,NULL);
                            pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                            Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningSecondary",true);
                        }

                        pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27), 0,NULL);
                        pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                        Ogre::Pass::getVertexProgramParameters((char (*) [32])&local_388,pvVar14);

                        Ogre::GpuProgramParameters::setNamedAutoConstant(local_380,"texViewProj",0x79,0);
                        local_388 = &PTR__SharedPtr_00fd1950;
                        if ((local_378 != NULL) && (iVar33 = *local_378, *local_378 = iVar33 - 1, iVar33 - 1 == 0)) {

                            Ogre::((SharedPtr<Ogre::GpuProgramParameters> *)&local_388)->destroy();
                        }
                        Ogre::Material::compile(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar27),true);
                        goto LAB_008acc12;
                    }
                }
                if (!m_ModelData1C8[0x5c]) {
                    psVar18 = (string *)(**(code **)(**(long **)(lVar20 + 0x10) + 200))();
                    std::string::string((string *)local_208,psVar18);

                    lVar20 = std::string::find((char *)local_208,0xfd11ca,0);
                    if (lVar20 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x30 + lVar27) = 1;
                    }
                    lVar20 = std::string::find((char *)local_208,0xfd11d1,0);
                    if (lVar20 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x31 + lVar27) = 0;
                    }
                }
                else {
                    *(char *)(lVar20 + 1) = 1;
                    if (param_1 != NULL) {
                        (**(code **)(*(long *)param_1 + 0x178))(param_1,4);
                    }
                }
                lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                *(long long *)(lVar20 + 8) = *(long long *)(lVar20 + 0x10);
                if (m_ModelData1C8[0x5c]) {
                    psVar18 = (string *)
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27) + 200))();
                    std::string::string((string *)local_218,psVar18);

                    std::string::append((char *)local_218, 0xfd11d9);

                    ((STRINGS *)local_208)->uniqueName((string *)local_218);
                    lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);

                    Ogre::Material::clone((string *)&local_3a8,SUB81(*(long long *)(lVar20 + 0x10),0), (string *)local_208);
                    *(long long *)(lVar20 + 0x10) = local_3a0;
                    local_3a8 = &PTR__SharedPtr_00fa4590;
                    if ((local_398 != NULL) && (iVar33 = *local_398, *local_398 = iVar33 - 1, iVar33 - 1 == 0)) {
                        Ogre::((SharedPtr<Ogre::Material> *)&local_3a8)->destroy();
                    }
                    Ogre::SubEntity::setMaterialName(plVar17,(string *)local_208);
                    pvVar14 = Ogre::Material::getBestTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar27),0, NULL);
                    if (pvVar14 != NULL) {
                        lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                        bVar7 = Ogre::Material::isTransparent(*(void **)(lVar20 + 0x10));
                        *(bool *)(lVar20 + 0x2e) = bVar7;
                    }

                    ((STRINGS *)local_238)->uniqueName("rbmat_");

                    std::((string *)local_208)->assign();

                    plVar17 = Ogre::MaterialManager::getSingleton();
                    (**(code **)(*plVar17 + 0x28))
                    ((SharedPtr<Ogre::Resource> *)&local_3c8,plVar17,(string *)local_208, &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
                    local_3f8 = (char  [8])&PTR__MaterialPtr_00fa44d0;
                    local_3f0._M_p = local_3c0;
                    local_3e8._M_p = local_3b8;
                    if (local_3b8 != NULL) {
                        *local_3b8 = *local_3b8 + L'\x01';
                    }
                    local_3c8 = &PTR__SharedPtr_00fa45d0;
                    if ((local_3b8 != NULL) && (wVar4 = *local_3b8, *local_3b8 = wVar4 + L'\xffffffff', wVar4 + L'\xffffffff' == L'\0')) {

                        Ogre::((SharedPtr<Ogre::Resource> *)&local_3c8)->destroy();
                    }
                    *(char **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27) = local_3f0._M_p;
                    *(char *)(*(long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27) + 0xf0)
                    = 0;
                    pvVar14 = Ogre::Material::getTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27),0)
                    ;
                    pvVar14 = Ogre::Technique::getPass(pvVar14,0);
                    Ogre::Pass::setSelfIllumination(pvVar14,0.0,0.0,0.0);
                    local_2b8.r = 0.0;
                    local_2b8.g = 0.0;
                    local_2b8.b = 0.0;
                    local_2b8.a = 1.0;
                    Ogre::Pass::setAmbient(pvVar14,&local_2b8);
                    local_2c8.r = 0.0;
                    local_2c8.g = 0.0;
                    local_2c8.b = 0.0;
                    local_2c8.a = 1.0;
                    Ogre::Pass::setDiffuse(pvVar14,&local_2c8);
                    Ogre::Pass::setDepthWriteEnabled(pvVar14,false);
                    local_428 = (char  [8])&DAT_01423a38;

                    std::string::string((string *)&local_420,(string *)&::EMPTY_STRING);

                    std::((std::wstring *)&local_418)->basic_string((std::wstring *)&::EMPTY_WSTRING);
                    local_408._M_p = &DAT_01423a38;

                    pCVar22 = CFileSystem::getSingleton();
                    pCVar22->getFileInfo(L"media/sharedTextures/outlineblue.dds", (CFileInfo *)local_428, false, true, false);

                    Ogre::Pass::createTextureUnitState(pvVar14,&local_420,0);
                    Ogre::Pass::setMaxSimultaneousLights(pvVar14,0);
                    Ogre::Pass::setFog(pvVar14,true,0,(ColourValue *)&Ogre::ColourValue::White,0.001,0.0,1.0);
                    pTVar23 = Ogre::Pass::getTextureUnitState(pvVar14,0);
                    Ogre::TextureUnitState::setEnvironmentMap(pTVar23,true,1);
                    pvVar15 = Ogre::Material::getTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27),0)
                    ;
                    Ogre::Technique::setDepthFunction(pvVar15,7);
                    pvVar15 = Ogre::Material::getTechnique(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27),0)
                    ;
                    Ogre::Technique::setDepthWriteEnabled(pvVar15,false);
                    Ogre::Material::setSceneBlending(*(void **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar27),2);
                    lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                    if ((*(char *)(lVar20 + 2) != '\0') && (sVar10 = *(short *)(lVar20 + 0x2c), sVar10 != 0))
                    {
                        if (sVar10 == 2) {

                            Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningBehindTwo",true);
                        }
                        else if (sVar10 == 3) {

                            Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningBehindThree",true);
                        }
                        else if (sVar10 == 1) {

                            Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningBehindOne",true);
                        }
                        else {

                            Ogre::Pass::setVertexProgram(pvVar14,"Ogre/HardwareSkinningBehind",true);
                        }
                        lVar20 = lVar27 + *(long *)(m_ModelData1C8 + 0x40);
                    }
                    LAB_008ad351:

                    Ogre::Material::compile(*(void **)(lVar20 + 0x20),true);
                    local_3f8 = (char  [8])&PTR__SharedPtr_00fa4590;
                    if ((local_3e8._M_p != NULL) && (wVar4 = *local_3e8._M_p, *local_3e8._M_p = wVar4 + L'\xffffffff', wVar4 + L'\xffffffff' == L'\0')) {

                        Ogre::((SharedPtr<Ogre::Material> *)local_3f8)->destroy();
                    }
                }
                local_494 = local_494 + 1;
                lVar27 = lVar27 + 0x40;
            } while (local_494 < uVar11);
        }
    }
    if (m_pEntity != param_1) {
        if (*(long *)(m_ModelData1C8 + 0x68) == 0) {
            *(Entity **)(m_ModelData1C8 + 0x68) = m_pEntity;
        }
        m_pEntity = NULL;
    }
    sceneNodeAttachEntity(param_1);
    if (*(long *)(m_ModelData118 + 0x18) != 0) {
        *(long long *)(m_ModelData118 + 0x18) = *(long long *)(param_1 + 0x2e8);
        if (*(int *)(m_ModelData118 + 0x38) == 0) {
            lVar27 = *(long *)(m_ModelData1C8 + 0x18);
            if (lVar27 != 0) {
                if (*(int *)(lVar27 + 0x20) != 0) {
                    uVar11 = 0;
                    do {
                        pvVar14 = Ogre::Entity::getAnimationState(param_1,(string *)((unsigned long)uVar11 * 8 + *(long *)(lVar27 + 0x28)));
                        uVar35 = *(unsigned int *)(m_ModelData118 + 0x38);
                        if (uVar35 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                            pvVar15 = *(void **)(m_ModelData118 + 0x30);
                        }
                        else if (*(long *)(m_ModelData118 + 0x30) == 0) {
                            *(unsigned int *)(m_ModelData118 + 0x3c) = *(unsigned int *)(m_ModelData118 + 0x40);
                            pvVar15 = operator new[]((unsigned long)*(unsigned int *)(m_ModelData118 + 0x40) << 3);
                            *(void **)(m_ModelData118 + 0x30) = pvVar15;
                            uVar35 = *(unsigned int *)(m_ModelData118 + 0x38);
                        }
                        else {
                            uVar35 = *(unsigned int *)(m_ModelData118 + 0x3c) +
                            *(int *)(m_ModelData118 + 0x40);
                            pvVar15 = operator new[]((unsigned long)uVar35 << 3);
                            if (*(int *)(m_ModelData118 + 0x3c) != 0) {
                                uVar12 = 0;
                                do {
                                    uVar16 = (unsigned long)uVar12;
                                    uVar12 = uVar12 + 1;
                                    *(long long *)((long)pvVar15 + uVar16 * 8) = *(long long *)(*(long *)(m_ModelData118 + 0x30) + uVar16 * 8);
                                } while (uVar12 < *(unsigned int *)(m_ModelData118 + 0x3c));
                            }
                            if (*(void **)(m_ModelData118 + 0x30) != NULL) {
                                operator delete[](*(void **)(m_ModelData118 + 0x30));
                            }
                            *(void **)(m_ModelData118 + 0x30) = pvVar15;
                            *(unsigned int *)(m_ModelData118 + 0x3c) = uVar35;
                            uVar35 = *(unsigned int *)(m_ModelData118 + 0x38);
                        }
                        uVar11 = uVar11 + 1;
                        *(void **)((long)pvVar15 + (unsigned long)uVar35 * 8) = pvVar14;
                        lVar27 = *(long *)(m_ModelData1C8 + 0x18);
                        *(int *)(m_ModelData118 + 0x38) = *(int *)(m_ModelData118 + 0x38) + 1;
                    } while (uVar11 < *(unsigned int *)(lVar27 + 0x20));
                }

                playAnimation("IDLE",true,1.0,-1.0);
            }
        }
        else {
            lVar27 = *(long *)(m_ModelData1C8 + 0x18);
            if (lVar27 != 0) {
                if (*(int *)(lVar27 + 0x20) != 0) {
                    uVar16 = 0;
                    do {
                        if ((unsigned int)uVar16 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                            puVar34 = (long long *)(uVar16 * 8 + *(long *)(m_ModelData118 + 0x30));
                        }
                        else {
                            puVar34 = *(long long **)(m_ModelData118 + 0x30);
                        }
                        lVar20 = uVar16 * 8;
                        uVar11 = (unsigned int)uVar16 + 1;
                        uVar16 = (unsigned long)uVar11;
                        pvVar14 = Ogre::Entity::getAnimationState(param_1,(string *)(lVar20 + *(long *)(lVar27 + 0x28)));
                        *puVar34 = pvVar14;
                        lVar27 = *(long *)(m_ModelData1C8 + 0x18);
                    } while (uVar11 < *(unsigned int *)(lVar27 + 0x20));
                }
                lVar28 = *(long *)(m_ModelData118 + 0x68);
                lVar30 = *(long *)(m_ModelData118 + 0x78);
                lVar20 = *(long *)(m_ModelData118 + 0x58);
                lVar31 = *(long *)(m_ModelData118 + 0x80);
                lVar32 = *(long *)(m_ModelData118 + 0x90);
                lVar27 = *(long *)(m_ModelData118 + 0x70);
                if (0 < (int)(lVar32 - lVar27 >> 3) * 0x40 - 0x40 + (int)(lVar28 - lVar20 >> 3) + (int)(lVar30 - lVar31 >> 3)) {
                    iVar33 = 0;
                    do {
                        lVar26 = (long)iVar33;
                        uVar16 = (lVar20 - *(long *)(m_ModelData118 + 0x60) >> 3) + lVar26;
                        uVar24 = (long)uVar16 >> 6;
                        if ((long)uVar16 < 0) {
                            LAB_008ac607:
                            uVar25 = ~(~uVar16 >> 6);
                            uVar11 = *(unsigned int *)(*(long *)(*(long *)(lVar27 + uVar25 * 8) + (uVar16 + uVar25 * -0x40) * 8) + 0x10);
                            if ((-1 < (long)uVar16) && (uVar25 = uVar24, (long)uVar16 < 0x40)) goto LAB_008ac478;
                            LAB_008ac5ca:
                            plVar17 = (long *)((uVar16 + uVar25 * -0x40) * 8 + *(long *)(lVar27 + uVar25 * 8));
                        }
                        else {
                            if (0x3f < (long)uVar16) {
                                if ((long)uVar16 < 1) goto LAB_008ac607;
                                uVar11 = *(unsigned int *)(*(long *)(*(long *)(lVar27 + uVar24 * 8) + (unsigned long)((unsigned int)uVar16 & 0x3f) * 8) + 0x10);
                                uVar25 = uVar24;
                                goto LAB_008ac5ca;
                            }
                            uVar11 = *(unsigned int *)(*(long *)(lVar20 + lVar26 * 8) + 0x10);
                            LAB_008ac478:
                            plVar17 = (long *)(lVar20 + lVar26 * 8);
                        }
                        if (*(char *)(*plVar17 + 0x28) == '\0') {
                            if (uVar11 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                                puVar34 = (long long *)((unsigned long)uVar11 * 8 + *(long *)(m_ModelData118 + 0x30))
                                ;
                            }
                            else {
                                puVar34 = *(long long **)(m_ModelData118 + 0x30);
                            }
                            Ogre::AnimationState::setEnabled((void *)*puVar34,true);
                            uVar16 = (*(long *)(m_ModelData118 + 0x58) - *(long *)(m_ModelData118 + 0x60) >> 3) + lVar26;
                            if ((long)uVar16 < 0) {
                                LAB_008ac689:
                                uVar24 = ~(~uVar16 >> 6);
                                LAB_008ac4e9:
                                plVar17 = (long *)((uVar16 + uVar24 * -0x40) * 8 + *(long *)(*(long *)(m_ModelData118 + 0x70) + uVar24 * 8));
                            }
                            else {
                                plVar17 = (long *)(*(long *)(m_ModelData118 + 0x58) + lVar26 * 8);
                                if (0x3f < (long)uVar16) {
                                    if ((long)uVar16 < 1) goto LAB_008ac689;
                                    uVar24 = (long)uVar16 >> 6;
                                    goto LAB_008ac4e9;
                                }
                            }
                            if (uVar11 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                                puVar34 = (long long *)((unsigned long)uVar11 * 8 + *(long *)(m_ModelData118 + 0x30))
                                ;
                            }
                            else {
                                puVar34 = *(long long **)(m_ModelData118 + 0x30);
                            }
                            Ogre::AnimationState::setTimePosition((void *)*puVar34,*(float *)(*plVar17 + 0x20));
                            lVar27 = *(long *)(m_ModelData118 + 0x70);
                            lVar20 = *(long *)(m_ModelData118 + 0x58);
                            lVar28 = *(long *)(m_ModelData118 + 0x68);
                            lVar31 = *(long *)(m_ModelData118 + 0x80);
                            lVar30 = *(long *)(m_ModelData118 + 0x78);
                            lVar32 = *(long *)(m_ModelData118 + 0x90);
                        }
                        iVar33 = iVar33 + 1;
                    } while (iVar33 < (int)(lVar32 - lVar27 >> 3) * 0x40 - 0x40 + (int)(lVar28 - lVar20 >> 3) + (int)(lVar30 - lVar31 >> 3));
                }
                updateAnimation(0.0,true);
            }
        }
    }
}
