void CGenericModel::reInitialize(Ogre::Entity* param_1, bool param_2)
{
    wchar_t wVar4;
    code *pcVar5;
    char cVar6;
    char uVar7;
    bool bVar8;
    char cVar9;
    unsigned short uVar10;
    short uVar11;
    short sVar12;
    unsigned int uVar13;
    unsigned int uVar14;
    int iVar15;
    long long uVar16;
    void *pvVar17;
    unsigned long uVar18;
    long *plVar19;
    string *psVar20;
    long lVar21;
    string *psVar22;
    CMasterResourceManager *pCVar23;
    ColourValue *pCVar24;
    CFileSystem *pCVar25;
    unsigned long uVar26;
    unsigned long uVar27;
    long lVar28;
    long lVar29;
    long lVar30;
    unsigned short uVar31;
    long lVar33;
    long lVar34;
    long lVar35;
    int iVar36;
    long long *puVar37;
    unsigned int uVar38;
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
    long long local_380;
    int *local_378;
    SharedPtr<Ogre::GpuProgramParameters> local_368 [8];
    long long local_360;
    char **local_348;
    long long local_340;
    int *local_338;
    char **local_328;
    long long local_320;
    int *local_318;
    char **local_308;
    long long local_300;
    int *local_2f8;
    char **local_2e8;
    long long local_2e0;
    int *local_2d8;
    long long *local_2a0;
    long local_238 [2];
    long local_218 [2];
    long local_208 [2];
    string local_1e8 [16];
    string local_1c8 [16];
    string local_1a8 [16];
    string local_188 [16];
    string local_168 [16];
    string local_158 [16];
    string local_148 [16];
    string local_138 [16];
    string local_128 [16];
    string local_118 [16];
    string local_108 [16];
    string local_f8 [16];
    string local_e8 [16];
    long local_d8 [2];
    long local_c8 [2];
    long local_98 [2];
    allocator local_4d;
    allocator local_4b;
    allocator local_49;
    allocator local_47;
    allocator local_45;
    allocator local_44;
    allocator local_43;
    allocator local_42;
    allocator local_41;
    allocator local_40;
    allocator local_3f;
    allocator local_3e;
    allocator local_3d;
    allocator local_3c;

    uVar13 = Ogre::Entity::getNumSubEntities();
    if (param_2) {
        m_ModelData1C8[0x70] = '\0';
        releaseUniqueMaterials();
        lVar21 = *(long *)(m_ModelData1C8 + 0x40);
        lVar30 = *(long *)(m_ModelData1C8 + 0x48);
        lVar29 = lVar21;
        if (lVar21 != lVar30) {
            do {
                lVar29 = lVar29 + 0x40;
            } while (lVar30 != lVar29);
            lVar29 = *(long *)(m_ModelData1C8 + 0x40);
        }
        *(long *)(m_ModelData1C8 + 0x48) = lVar21;
        uVar26 = (unsigned long)uVar13;
        uVar18 = lVar21 - lVar29 >> 6;
        if (uVar26 < uVar18) {
            lVar29 = lVar29 + uVar26 * 0x40;
            for (lVar30 = lVar29; lVar21 != lVar30; lVar30 = lVar30 + 0x40) {
            }
            *(long *)(m_ModelData1C8 + 0x48) = lVar29;
        }
        else {

            std::((vector<CRenderableStates,std::allocator<CRenderableStates>> *) (m_ModelData1C8 + 0x40),lVar21,uVar26 - uVar18)->_M_fill_insert();
        }
        if (uVar13 != 0) {
            lVar29 = 0;
            local_494 = 0;
            do {
                psVar20 = (string *)Ogre::Entity::getSubEntity((unsigned int)param_1);
                lVar21 = *(long *)(m_ModelData1C8 + 0x40);
                pcVar5 = *(code **)(*(long *)psVar20 + 0x78);
                local_2a0 = (long long *)Ogre::NedAllocImpl::allocBytes(0x10,NULL,0,NULL);
                if (local_2a0 != NULL) {
                    *local_2a0 = &PTR__holder_00fd18b0;
                    local_2a0[1] = lVar21 + lVar29;
                }

                (*pcVar5)(psVar20);
                if (local_2a0 != NULL) {
                    (**(code **)*local_2a0)();
                    Ogre::NedAllocImpl::deallocBytes(local_2a0);
                }
                lVar21 = *(long *)(m_ModelData1C8 + 0x40);
                lVar30 = (**(code **)(*(long *)psVar20 + 0x10))(psVar20);
                *(long long *)(lVar29 + lVar21 + 0x10) = *(long long *)(lVar30 + 8);
                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29), NULL);
                lVar21 = Ogre::Technique::getPass(uVar10);
                uVar18 = *(long *)(lVar21 + 0xf0) - *(long *)(lVar21 + 0xe8) >> 3 & 0xffff;
                uVar14 = (unsigned int)uVar18;
                uVar38 = uVar14;
                if (1 < uVar14) {
                    iVar36 = 1;
                    do {
                        lVar30 = Ogre::Pass::getTextureUnitState((unsigned short)lVar21);
                        iVar15 = std::string::compare((char *)(lVar30 + 0x160));
                        uVar38 = (int)uVar18 - (unsigned int)(iVar15 == 0);
                        uVar18 = (unsigned long)uVar38;
                        iVar36 = iVar36 + 1;
                    } while (iVar36 < (int)uVar14);
                }
                *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2a + lVar29) = (short)uVar38;
                (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) + 200))();
                std::((string *)(lVar29 + *(long *)(m_ModelData1C8 + 0x40) + 0x38))->assign();
                if (!m_ModelData1C8[0x5c]) {
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) + 200))()
                    ;
                    std::operator+((char *)local_208,(string *)"highlightmat_");

                    plVar19 = (long *)Ogre::MaterialManager::getSingleton();
                    cVar6 = (**(code **)(*plVar19 + 0xb0))(plVar19,(string *)local_208);
                    if (!cVar6) {
                        Ogre::Material::clone((string *)&local_328, SUB81(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) ,0),(string *)local_208);
                        uVar16 = local_320;
                        local_328 = &PTR__SharedPtr_00fa4590;
                        if ((local_318 != NULL) && (iVar36 = *local_318, *local_318 = iVar36 - 1, iVar36 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Material> *)&local_328)->destroy();
                        }
                        *(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29) = uVar16;
                        Ogre::Material::setLightingEnabled(SUB81(uVar16,0));
                        uVar10 = Ogre::Material::getBestTechnique((unsigned short)uVar16,NULL);
                        lVar21 = Ogre::Technique::getPass(uVar10);
                        bVar8 = true;
                        if ((short)((unsigned long)(*(long *)(lVar21 + 0xf0) - *(long *)(lVar21 + 0xe8)) >> 3) != 0) {

                            uVar10 = Ogre::Material::getBestTechnique((unsigned short)uVar16,NULL);
                            uVar10 = Ogre::Technique::getPass(uVar10);
                            uVar16 = Ogre::Pass::getTextureUnitState(uVar10);
                            Ogre::TextureUnitState::setColourOperationEx(0,uVar16,3,1,0,&Ogre::ColourValue::White)
                            ;
                            bVar8 = true;
                        }
                    }
                    else {
                        lVar21 = *(long *)(m_ModelData1C8 + 0x40);

                        plVar19 = (long *)Ogre::MaterialManager::getSingleton();
                        (**(code **)(*plVar19 + 0xa0))(&local_348,plVar19,(string *)local_208);
                        *(long long *)(lVar29 + lVar21 + 0x18) = local_340;
                        local_348 = &PTR__SharedPtr_00fa45d0;
                        if ((local_338 != NULL) && (iVar36 = *local_338, *local_338 = iVar36 - 1, iVar36 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Resource> *)&local_348)->destroy();
                        }
                        bVar8 = false;
                    }
                }
                else {
                    psVar22 = (string *)
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) + 200))();
                    std::string::string((string *)local_208,psVar22);

                    ((STRINGS *)local_98)->uniqueName("highlightmat_");

                    std::((string *)local_208)->assign();

                    plVar19 = (long *)Ogre::MaterialManager::getSingleton();
                    cVar6 = (**(code **)(*plVar19 + 0xb0))(plVar19,(string *)local_208);
                    if (!cVar6) {
                        Ogre::Material::clone((string *)&local_2e8, SUB81(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) ,0),(string *)local_208);
                        uVar16 = local_2e0;
                        local_2e8 = &PTR__SharedPtr_00fa4590;
                        if ((local_2d8 != NULL) && (iVar36 = *local_2d8, *local_2d8 = iVar36 - 1, iVar36 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Material> *)&local_2e8)->destroy();
                        }
                        *(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29) = uVar16;
                        uVar31 = (unsigned short)uVar16;
                        uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                        lVar21 = Ogre::Technique::getPass(uVar10);
                        if ((short)((unsigned long)(*(long *)(lVar21 + 0xf0) - *(long *)(lVar21 + 0xe8)) >> 3) != 0) {

                            uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                            lVar21 = Ogre::Technique::getPass(uVar10);
                            if (*(long *)(lVar21 + 0x100) != 0) {

                                uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81("",0));
                            }
                            if (*(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2f + lVar29) == '\0') {
                                if (m_ModelData1C8[0x70]) {
                                    local_490 = 1;
                                    iVar36 = uVar38 - 1;
                                    if ((int)(uVar38 - 1) < 1) {
                                        iVar36 = local_490;
                                    }
                                    while(true) {
                                        uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                        lVar21 = Ogre::Technique::getPass(uVar10);
                                        if ((int)((unsigned int)(*(long *)(lVar21 + 0xf0) - *(long *)(lVar21 + 0xe8) >> 3) & 0xffff) <= iVar36) break;

                                        uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                        Ogre::Technique::getPass(uVar10);
                                        uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                        uVar10 = Ogre::Technique::getPass(uVar10);
                                        Ogre::Pass::removeTextureUnitState(uVar10);
                                    }
                                }
                                uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                Ogre::Technique::getPass(uVar10);
                                psVar22 = (string *)Ogre::Pass::createTextureUnitState();
                                local_3f8 = (char  [8])&DAT_01423a38;

                                std::string::string((string *)&local_3f0,(string *)&::EMPTY_STRING);

                                std::((std::wstring *)&local_3e8)->basic_string((std::wstring *)&::EMPTY_WSTRING);
                                local_3d8._M_p = &DAT_01423a38;

                                pCVar25 = CFileSystem::getSingleton();
                                pCVar25->getFileInfo(L"media/sharedtextures/highlight.dds", (CFileInfo *)local_3f8, false, true, false);

                                Ogre::TextureUnitState::setCubicTextureName(psVar22,SUB81((string *)&local_3f0,0));
                                Ogre::TextureUnitState::setTextureCoordSet((unsigned int)psVar22);
                                Ogre::TextureUnitState::setTextureAddressingMode(psVar22,2);
                                Ogre::TextureUnitState::setEnvironmentMap(psVar22,1,3);
                                Ogre::TextureUnitState::setColourOperation(psVar22);
                            }
                            else {

                                uVar10 = Ogre::Material::getBestTechnique(uVar31,NULL);
                                uVar10 = Ogre::Technique::getPass(uVar10);
                                uVar16 = Ogre::Pass::getTextureUnitState(uVar10);
                                Ogre::TextureUnitState::setColourOperationEx(0,uVar16,4,1,0,&Ogre::ColourValue::White);
                            }
                        }
                        bVar8 = true;
                    }
                    else {
                        lVar21 = *(long *)(m_ModelData1C8 + 0x40);

                        plVar19 = (long *)Ogre::MaterialManager::getSingleton();
                        (**(code **)(*plVar19 + 0xa0))
                        ((SharedPtr<Ogre::Resource> *)&local_308,plVar19,(string *)local_208);
                        *(long long *)(lVar21 + lVar29 + 0x18) = local_300;
                        local_308 = &PTR__SharedPtr_00fa45d0;
                        if ((local_2f8 != NULL) && (iVar36 = *local_2f8, *local_2f8 = iVar36 - 1, iVar36 - 1 == 0)) {
                            Ogre::((SharedPtr<Ogre::Resource> *)&local_308)->destroy();
                        }
                        bVar8 = false;
                    }
                    LAB_008acb1f:
                }
                lVar21 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29), NULL);
                if (lVar21 == 0) {
                    LAB_008acc12:
                    lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);
                }
                else {

                    std::string::string((string *)local_c8, *(char **)(*(long *)(m_ModelData1C8 + 0x40) + 0x38 + lVar29), &local_3c);

                    ((STRINGS *)local_d8)->StringUpper((string *)local_c8);

                    lVar21 = std::string::find((char *)local_d8,0xfd115e,0);
                    if (lVar21 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2f + lVar29) = 1;
                        m_ModelData1C8[0x72] = '\x01';
                    }
                    uVar14 = KSETTINGS_ALLOW_HWSKINNING;
                    pCVar23 = CMasterResourceManager::getSingleton();
                    iVar36 = pCVar23->m_pSettings->GetInt(uVar14)
                    ;
                    if (iVar36 != 1) goto LAB_008acc12;
                    uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29), NULL);
                    psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                    cVar6 = *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar29);
                    if (*(long *)(psVar22 + 0x100) == 0) {
                        LAB_008ada92:
                        if (((*(long *)(m_ModelData118 + 0x18) != 0) && (m_ModelData1C8[0x21])) && (!cVar6)) {
                            Ogre::Entity::getMesh();
                            sVar12 = Ogre::Mesh::getMaxBoneAssignments();
                            *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2c + lVar29) = sVar12;
                            if (sVar12 != 0) {
                                if (sVar12 == 2) {
                                    if ((int)uVar38 < 2) {

                                        std::string::string(local_118,"Ogre/HardwareSkinningTwo",&local_40);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_118,0));

                                        std::string::~string(local_118);
                                    }
                                    else {

                                        std::string::string(local_108,"Ogre/HardwareSkinningTwoSecondary",&local_3f);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_108,0));

                                        std::string::~string(local_108);
                                    }
                                }
                                else if (sVar12 == 3) {
                                    if ((int)uVar38 < 2) {

                                        std::string::string(local_f8,"Ogre/HardwareSkinningThree",&local_3e);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_f8,0));

                                        std::string::~string(local_f8);
                                    }
                                    else {

                                        std::string::string(local_e8,"Ogre/HardwareSkinningThreeSecondary",&local_3d);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_e8,0));

                                        std::string::~string(local_e8);
                                    }
                                }
                                else if (sVar12 == 1) {
                                    if ((int)uVar38 < 2) {

                                        std::string::string(local_138,"Ogre/HardwareSkinningOne",&local_42);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_138,0));

                                        std::string::~string(local_138);
                                    }
                                    else {

                                        std::string::string(local_128,"Ogre/HardwareSkinningOneSecondary",&local_41);

                                        Ogre::Pass::setVertexProgram(psVar22,SUB81(local_128,0));

                                        std::string::~string(local_128);
                                    }
                                }
                                else if ((int)uVar38 < 2) {

                                    std::string::string(local_158,"Ogre/HardwareSkinning",&local_44);

                                    Ogre::Pass::setVertexProgram(psVar22,SUB81(local_158,0));

                                    std::string::~string(local_158);
                                }
                                else {

                                    std::string::string(local_148,"Ogre/HardwareSkinningSecondary",&local_43);

                                    Ogre::Pass::setVertexProgram(psVar22,SUB81(local_148,0));

                                    std::string::~string(local_148);
                                }

                                std::string::string(local_168,"texViewProj",&local_45);

                                Ogre::Pass::getVertexProgramParameters();

                                Ogre::GpuProgramParameters::setNamedAutoConstant(local_360,local_168,0x79);

                                Ogre::SharedPtr<Ogre::GpuProgramParameters>::~SharedPtr(local_368);

                                std::string::~string(local_168);
                                Ogre::Material::compile(SUB81(*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29),0));
                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29),NULL);
                                lVar21 = Ogre::Technique::getPass(uVar10);
                                if (*(long *)(lVar21 + 0x100) != 0) {
                                    lVar21 = Ogre::Pass::getVertexProgram();
                                    cVar9 = (**(code **)(**(long **)(lVar21 + 8) + 0x1c8))();
                                    if (cVar9) {
                                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar29) = 1;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        lVar21 = Ogre::Pass::getVertexProgram();
                        cVar9 = (**(code **)(**(long **)(lVar21 + 8) + 0x1c8))();
                        if (!cVar9) goto LAB_008ada92;
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 2 + lVar29) = 1;
                        Ogre::Entity::getMesh();
                        uVar11 = Ogre::Mesh::getMaxBoneAssignments();
                        *(short *)(*(long *)(m_ModelData1C8 + 0x40) + 0x2c + lVar29) = uVar11;
                    }
                    lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);
                    if (((*(char *)(lVar21 + 2) != '\0') && (bVar8)) && ((sVar12 = *(short *)(lVar21 + 0x2c), sVar12 != 0 && (!cVar6)))) {
                        if (sVar12 == 2) {
                            if ((int)uVar38 < 2) {

                                std::string::string(local_1a8,"Ogre/HardwareSkinningTwo",&local_49);

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81(local_1a8,0));

                                std::string::~string(local_1a8);
                            }
                            else {

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81("Ogre/HardwareSkinningTwoSecondary",0));
                            }
                        }
                        else if (sVar12 == 3) {
                            if ((int)uVar38 < 2) {

                                std::string::string(local_188,"Ogre/HardwareSkinningThree",&local_47);

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81(local_188,0));

                                std::string::~string(local_188);
                            }
                            else {

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81("Ogre/HardwareSkinningThreeSecondary",0));
                            }
                        }
                        else if (sVar12 == 1) {
                            if ((int)uVar38 < 2) {

                                std::string::string(local_1c8,"Ogre/HardwareSkinningOne",&local_4b);

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81(local_1c8,0));

                                std::string::~string(local_1c8);
                            }
                            else {

                                uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29),NULL);
                                psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                                Ogre::Pass::setVertexProgram(psVar22,SUB81("Ogre/HardwareSkinningOneSecondary",0));
                            }
                        }
                        else if ((int)uVar38 < 2) {

                            std::string::string(local_1e8,"Ogre/HardwareSkinning",&local_4d);

                            uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29), NULL);
                            psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                            Ogre::Pass::setVertexProgram(psVar22,SUB81(local_1e8,0));

                            std::string::~string(local_1e8);
                        }
                        else {

                            uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29), NULL);
                            psVar22 = (string *)Ogre::Technique::getPass(uVar10);
                            Ogre::Pass::setVertexProgram(psVar22,SUB81("Ogre/HardwareSkinningSecondary",0));
                        }

                        uVar10 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29), NULL);
                        Ogre::Technique::getPass(uVar10);
                        Ogre::Pass::getVertexProgramParameters();

                        Ogre::GpuProgramParameters::setNamedAutoConstant(local_380,"texViewProj",0x79);
                        local_388 = &PTR__SharedPtr_00fd1950;
                        if ((local_378 != NULL) && (iVar36 = *local_378, *local_378 = iVar36 - 1, iVar36 - 1 == 0)) {

                            Ogre::((SharedPtr<Ogre::GpuProgramParameters> *)&local_388)->destroy();
                        }
                        Ogre::Material::compile(SUB81(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x18 + lVar29) ,0));
                        goto LAB_008acc12;
                    }
                }
                if (!m_ModelData1C8[0x5c]) {
                    psVar22 = (string *)(**(code **)(**(long **)(lVar21 + 0x10) + 200))();
                    std::string::string((string *)local_208,psVar22);

                    lVar21 = std::string::find((char *)local_208,0xfd11ca,0);
                    if (lVar21 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x30 + lVar29) = 1;
                    }
                    lVar21 = std::string::find((char *)local_208,0xfd11d1,0);
                    if (lVar21 != -1) {
                        *(char *)(*(long *)(m_ModelData1C8 + 0x40) + 0x31 + lVar29) = 0;
                    }
                }
                else {
                    *(char *)(lVar21 + 1) = 1;
                    if (param_1 != NULL) {
                        (**(code **)(*(long *)param_1 + 0x178))(param_1,4);
                    }
                }
                lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);
                *(long long *)(lVar21 + 8) = *(long long *)(lVar21 + 0x10);
                if (m_ModelData1C8[0x5c]) {
                    psVar22 = (string *)
                    (**(code **)(**(long **)(*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29) + 200))();
                    std::string::string((string *)local_218,psVar22);

                    std::string::append((char *)local_218, 0xfd11d9);

                    ((STRINGS *)local_208)->uniqueName((string *)local_218);
                    lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);

                    Ogre::Material::clone((string *)&local_3a8,SUB81(*(long long *)(lVar21 + 0x10),0), (string *)local_208);
                    *(long long *)(lVar21 + 0x10) = local_3a0;
                    local_3a8 = &PTR__SharedPtr_00fa4590;
                    if ((local_398 != NULL) && (iVar36 = *local_398, *local_398 = iVar36 - 1, iVar36 - 1 == 0)) {
                        Ogre::((SharedPtr<Ogre::Material> *)&local_3a8)->destroy();
                    }
                    Ogre::SubEntity::setMaterialName(psVar20);
                    lVar21 = Ogre::Material::getBestTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x10 + lVar29), NULL);
                    if (lVar21 != 0) {
                        lVar21 = *(long *)(m_ModelData1C8 + 0x40);
                        uVar7 = Ogre::Material::isTransparent();
                        *(char *)(lVar29 + lVar21 + 0x2e) = uVar7;
                    }

                    ((STRINGS *)local_238)->uniqueName("rbmat_");

                    std::((string *)local_208)->assign();

                    plVar19 = (long *)Ogre::MaterialManager::getSingleton();
                    (**(code **)(*plVar19 + 0x28))
                    ((SharedPtr<Ogre::Resource> *)&local_3c8,plVar19,(string *)local_208, &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
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
                    *(char **)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29) = local_3f0._M_p;
                    *(char *)(*(long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29) + 0xf0)
                    = 0;
                    uVar10 = Ogre::Material::getTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29));
                    pCVar24 = (ColourValue *)Ogre::Technique::getPass(uVar10);
                    Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
                    Ogre::Pass::setAmbient(pCVar24);
                    Ogre::Pass::setDiffuse(pCVar24);
                    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar24,0));
                    local_428 = (char  [8])&DAT_01423a38;

                    std::string::string((string *)&local_420,(string *)&::EMPTY_STRING);

                    std::((std::wstring *)&local_418)->basic_string((std::wstring *)&::EMPTY_WSTRING);
                    local_408._M_p = &DAT_01423a38;

                    pCVar25 = CFileSystem::getSingleton();
                    pCVar25->getFileInfo(L"media/sharedTextures/outlineblue.dds", (CFileInfo *)local_428, false, true, false);

                    Ogre::Pass::createTextureUnitState((string *)pCVar24,(unsigned short)(string *)&local_420);
                    Ogre::Pass::setMaxSimultaneousLights((unsigned short)pCVar24);
                    Ogre::Pass::setFog(0x3a83126f,0,pCVar24,1,0);
                    uVar16 = Ogre::Pass::getTextureUnitState((unsigned short)pCVar24);
                    Ogre::TextureUnitState::setEnvironmentMap(uVar16,1,1);
                    uVar16 = Ogre::Material::getTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29));
                    Ogre::Technique::setDepthFunction(uVar16,7);
                    bVar8 = (bool)Ogre::Material::getTechnique((unsigned short)*(long long *) (*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29));
                    Ogre::Technique::setDepthWriteEnabled(bVar8);
                    Ogre::Material::setSceneBlending(*(long long *)(*(long *)(m_ModelData1C8 + 0x40) + 0x20 + lVar29),2);
                    lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);
                    if ((*(char *)(lVar21 + 2) != '\0') && (sVar12 = *(short *)(lVar21 + 0x2c), sVar12 != 0))
                    {
                        if (sVar12 == 2) {

                            Ogre::Pass::setVertexProgram((string *)pCVar24,SUB81("Ogre/HardwareSkinningBehindTwo",0));
                        }
                        else if (sVar12 == 3) {

                            Ogre::Pass::setVertexProgram((string *)pCVar24,SUB81("Ogre/HardwareSkinningBehindThree",0));
                        }
                        else if (sVar12 == 1) {

                            Ogre::Pass::setVertexProgram((string *)pCVar24,SUB81("Ogre/HardwareSkinningBehindOne",0));
                        }
                        else {

                            Ogre::Pass::setVertexProgram((string *)pCVar24,SUB81("Ogre/HardwareSkinningBehind",0));
                        }
                        lVar21 = lVar29 + *(long *)(m_ModelData1C8 + 0x40);
                    }
                    LAB_008ad351:

                    Ogre::Material::compile(SUB81(*(long long *)(lVar21 + 0x20),0));
                    local_3f8 = (char  [8])&PTR__SharedPtr_00fa4590;
                    if ((local_3e8._M_p != NULL) && (wVar4 = *local_3e8._M_p, *local_3e8._M_p = wVar4 + L'\xffffffff', wVar4 + L'\xffffffff' == L'\0')) {

                        Ogre::((SharedPtr<Ogre::Material> *)local_3f8)->destroy();
                    }
                }
                local_494 = local_494 + 1;
                lVar29 = lVar29 + 0x40;
            } while (local_494 < uVar13);
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
            if (*(long *)(m_ModelData1C8 + 0x18) != 0) {
                if (*(int *)(*(long *)(m_ModelData1C8 + 0x18) + 0x20) != 0) {
                    uVar13 = 0;
                    do {
                        uVar16 = Ogre::Entity::getAnimationState((string *)param_1);
                        uVar38 = *(unsigned int *)(m_ModelData118 + 0x38);
                        if (uVar38 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                            pvVar17 = *(void **)(m_ModelData118 + 0x30);
                        }
                        else if (*(long *)(m_ModelData118 + 0x30) == 0) {
                            *(unsigned int *)(m_ModelData118 + 0x3c) = *(unsigned int *)(m_ModelData118 + 0x40);
                            pvVar17 = operator new[]((unsigned long)*(unsigned int *)(m_ModelData118 + 0x40) << 3);
                            *(void **)(m_ModelData118 + 0x30) = pvVar17;
                            uVar38 = *(unsigned int *)(m_ModelData118 + 0x38);
                        }
                        else {
                            uVar38 = *(unsigned int *)(m_ModelData118 + 0x3c) +
                            *(int *)(m_ModelData118 + 0x40);
                            pvVar17 = operator new[]((unsigned long)uVar38 << 3);
                            if (*(int *)(m_ModelData118 + 0x3c) != 0) {
                                uVar14 = 0;
                                do {
                                    uVar18 = (unsigned long)uVar14;
                                    uVar14 = uVar14 + 1;
                                    *(long long *)((long)pvVar17 + uVar18 * 8) = *(long long *)(*(long *)(m_ModelData118 + 0x30) + uVar18 * 8);
                                } while (uVar14 < *(unsigned int *)(m_ModelData118 + 0x3c));
                            }
                            if (*(void **)(m_ModelData118 + 0x30) != NULL) {
                                operator delete[](*(void **)(m_ModelData118 + 0x30));
                            }
                            *(void **)(m_ModelData118 + 0x30) = pvVar17;
                            *(unsigned int *)(m_ModelData118 + 0x3c) = uVar38;
                            uVar38 = *(unsigned int *)(m_ModelData118 + 0x38);
                        }
                        uVar13 = uVar13 + 1;
                        *(long long *)((long)pvVar17 + (unsigned long)uVar38 * 8) = uVar16;
                        lVar29 = *(long *)(m_ModelData1C8 + 0x18);
                        *(int *)(m_ModelData118 + 0x38) = *(int *)(m_ModelData118 + 0x38) + 1;
                    } while (uVar13 < *(unsigned int *)(lVar29 + 0x20));
                }

                playAnimation("IDLE",true,1.0,-1.0);
            }
        }
        else if (*(long *)(m_ModelData1C8 + 0x18) != 0) {
            if (*(int *)(*(long *)(m_ModelData1C8 + 0x18) + 0x20) != 0) {
                uVar13 = 0;
                do {
                    if (uVar13 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                        puVar37 = (long long *)((unsigned long)uVar13 * 8 + *(long *)(m_ModelData118 + 0x30));
                    }
                    else {
                        puVar37 = *(long long **)(m_ModelData118 + 0x30);
                    }
                    uVar13 = uVar13 + 1;
                    uVar16 = Ogre::Entity::getAnimationState((string *)param_1);
                    *puVar37 = uVar16;
                } while (uVar13 < *(unsigned int *)(*(long *)(m_ModelData1C8 + 0x18) + 0x20));
            }
            lVar30 = *(long *)(m_ModelData118 + 0x68);
            lVar33 = *(long *)(m_ModelData118 + 0x78);
            lVar21 = *(long *)(m_ModelData118 + 0x58);
            lVar34 = *(long *)(m_ModelData118 + 0x80);
            lVar35 = *(long *)(m_ModelData118 + 0x90);
            lVar29 = *(long *)(m_ModelData118 + 0x70);
            if (0 < (int)(lVar35 - lVar29 >> 3) * 0x40 - 0x40 + (int)(lVar30 - lVar21 >> 3) + (int)(lVar33 - lVar34 >> 3)) {
                iVar36 = 0;
                do {
                    lVar28 = (long)iVar36;
                    uVar18 = (lVar21 - *(long *)(m_ModelData118 + 0x60) >> 3) + lVar28;
                    uVar26 = (long)uVar18 >> 6;
                    if ((long)uVar18 < 0) {
                        LAB_008ac607:
                        uVar27 = ~(~uVar18 >> 6);
                        uVar13 = *(unsigned int *)(*(long *)(*(long *)(lVar29 + uVar27 * 8) + (uVar18 + uVar27 * -0x40) * 8) + 0x10);
                        if ((-1 < (long)uVar18) && (uVar27 = uVar26, (long)uVar18 < 0x40)) goto LAB_008ac478;
                        LAB_008ac5ca:
                        plVar19 = (long *)((uVar18 + uVar27 * -0x40) * 8 + *(long *)(lVar29 + uVar27 * 8));
                    }
                    else {
                        if (0x3f < (long)uVar18) {
                            if ((long)uVar18 < 1) goto LAB_008ac607;
                            uVar13 = *(unsigned int *)(*(long *)(*(long *)(lVar29 + uVar26 * 8) + (unsigned long)((unsigned int)uVar18 & 0x3f) * 8) + 0x10);
                            uVar27 = uVar26;
                            goto LAB_008ac5ca;
                        }
                        uVar13 = *(unsigned int *)(*(long *)(lVar21 + lVar28 * 8) + 0x10);
                        LAB_008ac478:
                        plVar19 = (long *)(lVar21 + lVar28 * 8);
                    }
                    if (*(char *)(*plVar19 + 0x28) == '\0') {
                        if (uVar13 < *(unsigned int *)(m_ModelData118 + 0x3c)) {
                            puVar37 = (long long *)((unsigned long)uVar13 * 8 + *(long *)(m_ModelData118 + 0x30));
                        }
                        else {
                            puVar37 = *(long long **)(m_ModelData118 + 0x30);
                        }
                        Ogre::AnimationState::setEnabled(SUB81(*puVar37,0));
                        uVar18 = (*(long *)(m_ModelData118 + 0x58) - *(long *)(m_ModelData118 + 0x60) >> 3) + lVar28;
                        if ((long)uVar18 < 0) {
                            LAB_008ac689:
                            uVar26 = ~(~uVar18 >> 6);
                            LAB_008ac4e9:
                            plVar19 = (long *)((uVar18 + uVar26 * -0x40) * 8 + *(long *)(*(long *)(m_ModelData118 + 0x70) + uVar26 * 8));
                        }
                        else {
                            plVar19 = (long *)(*(long *)(m_ModelData118 + 0x58) + lVar28 * 8);
                            if (0x3f < (long)uVar18) {
                                if ((long)uVar18 < 1) goto LAB_008ac689;
                                uVar26 = (long)uVar18 >> 6;
                                goto LAB_008ac4e9;
                            }
                        }
                        Ogre::AnimationState::setTimePosition(*(float *)(*plVar19 + 0x20));
                        lVar29 = *(long *)(m_ModelData118 + 0x70);
                        lVar21 = *(long *)(m_ModelData118 + 0x58);
                        lVar30 = *(long *)(m_ModelData118 + 0x68);
                        lVar34 = *(long *)(m_ModelData118 + 0x80);
                        lVar33 = *(long *)(m_ModelData118 + 0x78);
                        lVar35 = *(long *)(m_ModelData118 + 0x90);
                    }
                    iVar36 = iVar36 + 1;
                } while (iVar36 < (int)(lVar35 - lVar29 >> 3) * 0x40 - 0x40 + (int)(lVar30 - lVar21 >> 3) + (int)(lVar33 - lVar34 >> 3));
            }
            updateAnimation(0.0,true);
        }
    }
}
