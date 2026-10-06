void CShape::updateVisual(bool param_1, float param_2)
{
    int iVar2;
    code *pcVar3;
    void *pvVar4;
    char auVar5 [12];
    char auVar6 [12];
    bool bVar7;
    unsigned short uVar8;
    long long uVar9;
    CGenericModel *pCVar10;
    ColourValue *pCVar11;
    string *psVar12;
    long lVar13;
    long *plVar14;
    Quaternion *this_00;
    unsigned int uVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    double dVar19;
    char auVar20 [12];
    long long local_208;
    float local_200;
    int uStack_1fc;
    int *local_1f8;
    Radian local_1e8 [16];
    char local_1d8 [16];
    Radian local_1c8 [16];
    char local_198 [12];
    char local_188 [12];
    char local_178 [8];
    int local_170;
    float local_168;
    float local_164;
    float local_160;
    float local_158;
    float local_154;
    float local_150;
    char local_148 [12];
    float local_138;
    float fStack_134;
    long local_118 [2];
    long local_e8 [2];
    long local_b8 [2];
    long local_98 [2];
    long local_78 [2];
    int local_58 [6];

    plVar14 = *(long **)(m_ShapeData100 + 0x48);
    if (plVar14 == NULL) {
        pvVar4 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_78)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar10,m_pResourceManager,pvVar4,L"media/models/spawn_circle/spawn_circle.mesh",(std::wstring *)local_78,0);
        *(CGenericModel **)(m_ShapeData100 + 0x48) = pCVar10;
        (*(CGenericModel **)(m_ShapeData100 + 0x48))->setQueryMask(8);

        ((STRINGS *)local_98)->uniqueName("shape");

        plVar14 = (long *)Ogre::Entity::getSubEntity((unsigned int)*(long long *) (*(long *)(m_ShapeData100 + 0x48) + 0x60));
        lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
        Ogre::Material::clone((string *)&local_208,SUB81(*(long long *)(lVar13 + 8),0),(string *)local_98);

        uVar8 = Ogre::Material::getTechnique(SUB42(local_200,0));
        pCVar11 = (ColourValue *)Ogre::Technique::getPass(uVar8);
        Ogre::Pass::setSelfIllumination(1.0,1.0,1.0);
        Ogre::Pass::setAmbient(pCVar11);
        Ogre::Pass::setDiffuse(pCVar11);
        Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar11,0));
        Ogre::Material::setSceneBlending(CONCAT44(uStack_1fc,local_200),0);
        (**(code **)(*(long *)CONCAT44(uStack_1fc,local_200) + 200))();
        psVar12 = (string *)
        Ogre::Entity::getSubEntity((unsigned int)*(long long *)(*(long *)(m_ShapeData100 + 0x48) + 0x60));
        Ogre::SubEntity::setMaterialName(psVar12);
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x48) + 0x60) + 0xc0) = 0;
        pvVar4 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_b8)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar10,m_pResourceManager,pvVar4,L"media/models/primitives/sphere.mesh",(std::wstring *)local_b8,0);
        *(CGenericModel **)(m_ShapeData100 + 0x50) = pCVar10;

        (*(CGenericModel **)(m_ShapeData100 + 0x50))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(string **)(*(long *)(m_ShapeData100 + 0x50) + 0x60));
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x50) + 0x60) + 0xc0) = 0;
        pvVar4 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_e8)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar10,m_pResourceManager,pvVar4,L"media/models/primitives/box.mesh",(std::wstring *)local_e8,0);
        *(CGenericModel **)(m_ShapeData100 + 0x58) = pCVar10;

        (*(CGenericModel **)(m_ShapeData100 + 0x58))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(string **)(*(long *)(m_ShapeData100 + 0x58) + 0x60));
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x58) + 0x60) + 0xc0) = 0;
        pvVar4 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_118)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar10 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar10,m_pResourceManager,pvVar4,L"media/models/primitives/box.mesh",(std::wstring *)local_118,0);
        *(CGenericModel **)(m_ShapeData100 + 0x60) = pCVar10;

        (*(CGenericModel **)(m_ShapeData100 + 0x60))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(string **)(*(long *)(m_ShapeData100 + 0x60) + 0x60));
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x60) + 0x60) + 0xc0) = 0;
        local_208 = &PTR__SharedPtr_00fa4590;
        if ((local_1f8 != NULL) && (iVar2 = *local_1f8, *local_1f8 = iVar2 - 1, iVar2 - 1 == 0))
        {
            Ogre::((SharedPtr<Ogre::Material> *)&local_208)->destroy();
        }
        plVar14 = *(long **)(m_ShapeData100 + 0x48);
    }
    (**(code **)(*plVar14 + 0x50))(plVar14,0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
    (*(long **)(m_ShapeData100 + 0x50),0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x50))
    (*(long **)(m_ShapeData100 + 0x58),0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x50))
    (*(long **)(m_ShapeData100 + 0x60),0);
    if ((param_1) && ((bVar7 = m_pResourceManager->getEditorIsRunning(), !bVar7 || (bVar7 = HasBaseObjectFlag(8), !bVar7)))) {
        iVar2 = *(int *)(m_ShapeData100 + 4);
        if (iVar2 == 1) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x50))
            (*(long **)(m_ShapeData100 + 0x58),1);
            local_158 = 0.0;
            local_154 = 0.0;
            local_150 = 0.0;
            local_168 = 0.0;
            local_164 = 0.0;
            local_160 = 0.0;
            calculateLineSequment(param_2,(Vector3 *)&local_158,(Vector3 *)&local_168);
            auVar6._8_4_ = local_170;
            auVar6._0_8_ = local_178;
            auVar5._8_4_ = local_170;
            auVar5._0_8_ = local_178;
            auVar20._8_4_ = local_170;
            auVar20._0_8_ = local_178;
            if ((local_158 == local_168) && (_local_178 = auVar6, local_154 == local_164)) {
                _local_178 = auVar20;
                if ((local_150 == local_160) && (_local_178 = auVar5, !NAN(local_150) && !NAN(local_160))) {
                    _local_178 = getPosition(true);
                    local_150 = local_178._8_4_;
                    local_158 = (float)local_178._0_4_;
                    local_154 = (float)local_178._4_4_;
                }
            }
            (**(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x98))();
            local_164 = local_164 - local_154;
            local_168 = local_168 - local_158;
            local_160 = local_160 - local_150;
            dVar19 = atan2((double)local_168,(double)local_160);
            _local_138 = CONCAT44(fStack_134,(float)dVar19);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x108);
            Ogre::Quaternion::FromAngleAxis(local_1e8,(Vector3 *)&local_138);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x58),local_1e8);
            local_164 = local_164 * 0.5;
            local_168 = local_168 * 0.5;
            local_160 = local_160 * 0.5;
            local_200 = local_160 + local_150;
            local_208 = (char **)CONCAT44(local_164 + local_154 + 0.5,local_168 + local_158);
            (*(CPositionableObject **)(m_ShapeData100 + 0x58))->setPosition(local_208);
        }
        else if (iVar2 == 0) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x50))
            (*(long **)(m_ShapeData100 + 0x48),1);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x90);
            getMaxRadiusAtPercent(param_2);
            getMinRadiusAtPercent(param_2);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x48));
            fVar16 = (float)getMaxRadiusAtPercent(param_2);
            fVar17 = (float)getMinRadiusAtPercent(param_2);
            if (fVar17 <= fVar16) {
                fVar16 = fVar17;
            }
            fVar17 = (float)getMaxRadiusAtPercent(param_2);
            fVar18 = (float)getMinRadiusAtPercent(param_2);
            if (fVar17 <= fVar18) {
                fVar17 = fVar18;
            }
            uVar15 = -(unsigned int)(0.05 < fVar16 / fVar17);
            fVar18 = (float)getAngleOfReleaseAtPercent(param_2);
            lVar13 = Ogre::Entity::getSubEntity((unsigned int)*(long long *)(*(long *)(m_ShapeData100 + 0x48) + 0x60));
            if (lVar13 != 0) {
                plVar14 = (long *)Ogre::Entity::getSubEntity((unsigned int)*(long long *) (*(long *)(m_ShapeData100 + 0x48) + 0x60));
                lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
                lVar13 = Ogre::Material::getTechnique((unsigned short)*(long long *)(lVar13 + 8));
                if (lVar13 != 0) {
                    plVar14 = (long *)Ogre::Entity::getSubEntity((unsigned int)*(long long *) (*(long *)(m_ShapeData100 + 0x48) + 0x60));
                    lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
                    uVar8 = Ogre::Material::getTechnique((unsigned short)*(long long *)(lVar13 + 8));
                    lVar13 = Ogre::Technique::getPass(uVar8);
                    if (lVar13 != 0) {
                        plVar14 = (long *)Ogre::Entity::getSubEntity((unsigned int)*(long long *) (*(long *)(m_ShapeData100 + 0x48) + 0x60));
                        lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
                        uVar8 = Ogre::Material::getTechnique((unsigned short)*(long long *)(lVar13 + 8));
                        lVar13 = Ogre::Technique::getPass(uVar8);
                        if ((short)((unsigned long)(*(long *)(lVar13 + 0xf0) - *(long *)(lVar13 + 0xe8)) >> 3) != 0) {
                            plVar14 = (long *)Ogre::Entity::getSubEntity((unsigned int)*(long long *) (*(long *)(m_ShapeData100 + 0x48) + 0x60));
                            lVar13 = (**(code **)(*plVar14 + 0x10))(plVar14);
                            uVar8 = Ogre::Material::getTechnique((unsigned short)*(long long *)(lVar13 + 8));
                            uVar8 = Ogre::Technique::getPass(uVar8);
                            Ogre::Pass::getTextureUnitState(uVar8);
                            Ogre::TextureUnitState::setTextureScroll((fVar18 / -360.0 + 1.0) * 0.5, (float)(~uVar15 & 0x3d4ccccd | (unsigned int)(fVar16 / fVar17) & uVar15) * -0.5);
                        }
                    }
                }
            }
            fVar16 = (float)getAngleOffsetAtPercent(param_2);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x108);
            local_58[0] = Ogre::Math::AngleUnitsToRadians((180.0 - fVar16) - fVar18);
            Ogre::Quaternion::FromAngleAxis(local_1c8,(Vector3 *)local_58);
            this_00 = (Quaternion *)(**(code **)(*(long *)m_pSceneNode + 0x1f8))();
            local_1d8 = Ogre::Quaternion::operator*(this_00,(Quaternion *)local_1c8);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x48),local_1d8);
            auVar20 = getPosition(true);
            fStack_134 = auVar20._4_4_;
            _local_138 = CONCAT44(fStack_134 + 0.25,auVar20._0_4_);
            (*(CPositionableObject **)(m_ShapeData100 + 0x48))->setPosition(local_138);
        }
        else if (iVar2 == 2) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(m_ShapeData100 + 0x50),1);
            fVar16 = (float)getMaxRadiusAtPercent(param_2);
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x90))
            (~-(unsigned int)(0.1 < fVar16) & 0x3dcccccd | (unsigned int)fVar16 & -(unsigned int)(0.1 < fVar16));
            local_188 = getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x50))->setPosition(local_188);
        }
        else if (iVar2 == 4) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x50))
            (*(long **)(m_ShapeData100 + 0x60),1);
            local_148 = getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x60))->setPosition(local_148);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x108);
            uVar9 = (**(code **)(*(long *)m_pSceneNode + 0x1f8))();
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x60),uVar9);
            (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x98))();
        }
        else {
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(m_ShapeData100 + 0x50),1);
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x90))();
            local_198 = getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x50))->setPosition(local_198);
        }
    }
}
