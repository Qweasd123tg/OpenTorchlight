void CShape::updateVisual(bool param_1, float param_2)
{
    int iVar2;
    code *pcVar3;
    char auVar4 [12];
    char auVar5 [12];
    bool bVar6;
    long long uVar7;
    CGenericModel *pCVar8;
    string *psVar9;
    void *pvVar10;
    long *plVar11;
    long lVar12;
    TextureUnitState *this_00;
    Quaternion *this_01;
    unsigned int uVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    double dVar17;
    char auVar18 [12];
    Vector3 local_208;
    int uStack_1fc;
    int *local_1f8;
    Quaternion local_1e8 [16];
    Quaternion local_1d8;
    Quaternion local_1c8;
    ColourValue local_1b8;
    ColourValue local_1a8;
    Vector3 local_198;
    Vector3 local_188;
    char local_178 [8];
    int local_170;
    float local_168;
    float local_164;
    float local_160;
    float local_158;
    float local_154;
    float local_150;
    Vector3 local_148;
    Vector3 local_138;
    long local_118 [2];
    long local_e8 [2];
    long local_b8 [2];
    long local_98 [2];
    long local_78 [2];
    float local_58 [6];

    plVar11 = *(long **)(m_ShapeData100 + 0x48);
    if (plVar11 == NULL) {
        pvVar10 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_78)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar8,m_pResourceManager,pvVar10,L"media/models/spawn_circle/spawn_circle.mesh",(std::wstring *)local_78,0);
        *(CGenericModel **)(m_ShapeData100 + 0x48) = pCVar8;
        (*(CGenericModel **)(m_ShapeData100 + 0x48))->setQueryMask(8);

        ((STRINGS *)local_98)->uniqueName("shape");

        plVar11 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
        lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
        Ogre::Material::clone((string *)&local_208,SUB81(*(long long *)(lVar12 + 8),0),(string *)local_98);

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
        pvVar10 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
        Ogre::SubEntity::setMaterialName(pvVar10,psVar9);
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x48) + 0x60) + 0xc0) = 0;
        pvVar10 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_b8)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar8,m_pResourceManager,pvVar10,L"media/models/primitives/sphere.mesh",(std::wstring *)local_b8,0);
        *(CGenericModel **)(m_ShapeData100 + 0x50) = pCVar8;

        (*(CGenericModel **)(m_ShapeData100 + 0x50))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(void **)(*(long *)(m_ShapeData100 + 0x50) + 0x60),"lightBlue");
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x50) + 0x60) + 0xc0) = 0;
        pvVar10 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_e8)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar8,m_pResourceManager,pvVar10,L"media/models/primitives/box.mesh",(std::wstring *)local_e8,0);
        *(CGenericModel **)(m_ShapeData100 + 0x58) = pCVar8;

        (*(CGenericModel **)(m_ShapeData100 + 0x58))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(void **)(*(long *)(m_ShapeData100 + 0x58) + 0x60),"lightBlue");
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x58) + 0x60) + 0xc0) = 0;
        pvVar10 = m_pResourceManager->m_pSceneManager;

        std::((std::wstring *)local_118)->basic_string((std::wstring *)&::EMPTY_WSTRING);

        pCVar8 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,NULL,0,NULL);

        CGenericModel::CGenericModel(pCVar8,m_pResourceManager,pvVar10,L"media/models/primitives/box.mesh",(std::wstring *)local_118,0);
        *(CGenericModel **)(m_ShapeData100 + 0x60) = pCVar8;

        (*(CGenericModel **)(m_ShapeData100 + 0x60))->setQueryMask(8);

        Ogre::Entity::setMaterialName(*(void **)(*(long *)(m_ShapeData100 + 0x60) + 0x60),"lightBlue");
        *(char *)(*(long *)(*(long *)(m_ShapeData100 + 0x60) + 0x60) + 0xc0) = 0;
        local_208._0_8_ = &PTR__SharedPtr_00fa4590;
        if ((local_1f8 != NULL) && (iVar2 = *local_1f8, *local_1f8 = iVar2 - 1, iVar2 - 1 == 0))
        {
            Ogre::((SharedPtr<Ogre::Material> *)&local_208)->destroy();
        }
        plVar11 = *(long **)(m_ShapeData100 + 0x48);
    }
    (**(code **)(*plVar11 + 0x50))(plVar11,0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
    (*(long **)(m_ShapeData100 + 0x50),0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x50))
    (*(long **)(m_ShapeData100 + 0x58),0);
    (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x50))
    (*(long **)(m_ShapeData100 + 0x60),0);
    if ((param_1) && ((bVar6 = m_pResourceManager->getEditorIsRunning(), !bVar6 || (bVar6 = HasBaseObjectFlag(8), !bVar6)))) {
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
            auVar5._8_4_ = local_170;
            auVar5._0_8_ = local_178;
            auVar4._8_4_ = local_170;
            auVar4._0_8_ = local_178;
            auVar18._8_4_ = local_170;
            auVar18._0_8_ = local_178;
            if ((local_158 == local_168) && (_local_178 = auVar5, local_154 == local_164)) {
                _local_178 = auVar18;
                if ((local_150 == local_160) && (_local_178 = auVar4, !NAN(local_150) && !NAN(local_160))) {
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
            dVar17 = atan2((double)local_168,(double)local_160);
            local_138.x = (float)dVar17;
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x58) + 0x108);
            Ogre::Quaternion::FromAngleAxis(local_1e8,&local_138,(Vector3 *)&Ogre::Vector3::UNIT_Y);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x58),local_1e8);
            local_164 = local_164 * 0.5;
            local_168 = local_168 * 0.5;
            local_160 = local_160 * 0.5;
            local_208.z = local_160 + local_150;
            local_208.y = local_164 + local_154 + 0.5;
            local_208.x = local_168 + local_158;
            (*(CPositionableObject **)(m_ShapeData100 + 0x58))->setPosition(local_208);
        }
        else if (iVar2 == 0) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x50))();
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x90);
            getMaxRadiusAtPercent(param_2);
            getMinRadiusAtPercent(param_2);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x48));
            fVar14 = (float)getMaxRadiusAtPercent(param_2);
            fVar15 = (float)getMinRadiusAtPercent(param_2);
            if (fVar15 <= fVar14) {
                fVar14 = fVar15;
            }
            fVar15 = (float)getMaxRadiusAtPercent(param_2);
            fVar16 = (float)getMinRadiusAtPercent(param_2);
            if (fVar15 <= fVar16) {
                fVar15 = fVar16;
            }
            uVar13 = -(unsigned int)(0.05 < fVar14 / fVar15);
            fVar16 = (float)getAngleOfReleaseAtPercent(param_2);
            pvVar10 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
            if (pvVar10 != NULL) {
                plVar11 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
                lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
                pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
                if (pvVar10 != NULL) {
                    plVar11 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
                    lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
                    pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
                    pvVar10 = Ogre::Technique::getPass(pvVar10,0);
                    if (pvVar10 != NULL) {
                        plVar11 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
                        lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
                        pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
                        pvVar10 = Ogre::Technique::getPass(pvVar10,0);
                        if ((short)((unsigned long)(*(long *)((long)pvVar10 + 0xf0) - *(long *)((long)pvVar10 + 0xe8)) >> 3) != 0) {
                            plVar11 = Ogre::Entity::getSubEntity(*(void **)(*(long *)(m_ShapeData100 + 0x48) + 0x60),0);
                            lVar12 = (**(code **)(*plVar11 + 0x10))(plVar11);
                            pvVar10 = Ogre::Material::getTechnique(*(void **)(lVar12 + 8),0);
                            pvVar10 = Ogre::Technique::getPass(pvVar10,0);
                            this_00 = Ogre::Pass::getTextureUnitState(pvVar10,0);
                            Ogre::TextureUnitState::setTextureScroll(this_00,(fVar16 / -360.0 + 1.0) * 0.5, (float)(~uVar13 & 0x3d4ccccd | (unsigned int)(fVar14 / fVar15) & uVar13) * -0.5);
                        }
                    }
                }
            }
            fVar14 = (float)getAngleOffsetAtPercent(param_2);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x48) + 0x108);
            local_58[0] = Ogre::Math::AngleUnitsToRadians((180.0 - fVar14) - fVar16);
            Ogre::((Quaternion *)&local_1c8)->FromAngleAxis(local_58, (Vector3 *)&Ogre::Vector3::UNIT_Y);
            this_01 = (Quaternion *)(**(code **)(*(long *)m_pSceneNode + 0x1f8))();
            local_1d8 = Ogre::Quaternion::operator*(this_01,&local_1c8);
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x48),&local_1d8);
            auVar18 = getPosition(true);
            local_138.z = auVar18._8_4_;
            local_138.y = auVar18._4_4_;
            local_138.x = auVar18._0_4_;
            local_138.y = local_138.y + 0.25;
            (*(CPositionableObject **)(m_ShapeData100 + 0x48))->setPosition(local_138);
        }
        else if (iVar2 == 2) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(m_ShapeData100 + 0x50),1);
            fVar14 = (float)getMaxRadiusAtPercent(param_2);
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x90))
            (~-(unsigned int)(0.1 < fVar14) & 0x3dcccccd | (unsigned int)fVar14 & -(unsigned int)(0.1 < fVar14));
            local_188 = (Vector3)getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x50))->setPosition(local_188);
        }
        else if (iVar2 == 4) {
            (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x50))
            (*(long **)(m_ShapeData100 + 0x60),1);
            local_148 = (Vector3)getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x60))->setPosition(local_148);
            pcVar3 = *(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x108);
            uVar7 = (**(code **)(*(long *)m_pSceneNode + 0x1f8))();
            (*pcVar3)(*(long long *)(m_ShapeData100 + 0x60),uVar7);
            (**(code **)(**(long **)(m_ShapeData100 + 0x60) + 0x98))();
        }
        else {
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x50))
            (*(long **)(m_ShapeData100 + 0x50),1);
            (**(code **)(**(long **)(m_ShapeData100 + 0x50) + 0x90))();
            local_198 = (Vector3)getPosition(true);
            (*(CPositionableObject **)(m_ShapeData100 + 0x50))->setPosition(local_198);
        }
    }
}
