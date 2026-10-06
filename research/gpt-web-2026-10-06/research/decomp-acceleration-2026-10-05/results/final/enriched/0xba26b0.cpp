void CPetMenu::updateLayout()
{
    unsigned char bVar4;
    CInventory *this_00;
    bool bVar5;
    char cVar6;
    int iVar7;
    UVector2 *pUVar8;
    unsigned char *pbVar9;
    char *pcVar10;
    void *pvVar11;
    CEquipment *this_01;
    unsigned char *puVar12;
    CStringTranslate *pCVar13;
    CSkill *this_02;
    long *plVar14;
    int *puVar15;
    unsigned int *puVar16;
    long long *puVar17;
    long lVar18;
    CPetMenu *pCVar19;
    unsigned long uVar20;
    unsigned int uVar21;
    String *pSVar22;
    CEquipment *pCVar23;
    unsigned int uVar24;
    unsigned int uVar25;
    unsigned int uVar26;
    float fVar27;
    float fVar28;
    float fVar29;
    float fVar30;
    int local_22c8;
    void *local_22b8;
    String local_2268 [176];
    long long local_21b8;
    unsigned long local_21b0;
    int local_2190 [32];
    int *local_2110;
    long long local_2108;
    unsigned long local_2100;
    unsigned int local_20e0 [5];
    unsigned int local_20cc [27];
    unsigned int *local_2060;
    long long local_2058;
    unsigned long local_2050;
    int local_2030 [32];
    int *local_1fb0;
    long long local_1fa8;
    unsigned long local_1fa0;
    unsigned int local_1f80 [5];
    unsigned int local_1f6c [27];
    unsigned int *local_1f00;
    long long local_1ef8;
    unsigned long local_1ef0;
    int local_1ed0 [32];
    int *local_1e50;
    long long local_1e48;
    unsigned long local_1e40;
    unsigned int local_1e20 [5];
    unsigned int local_1e0c [27];
    unsigned int *local_1da0;
    String local_1d98 [176];
    String local_1ce8 [176];
    String local_1c38 [176];
    String local_1b88 [176];
    String local_1ad8 [176];
    String local_1a28 [176];
    String local_1978 [176];
    String local_18c8 [176];
    String local_1818 [176];
    String local_1768 [176];
    String local_16b8 [176];
    String local_1608 [176];
    long long local_1558;
    unsigned long local_1550;
    int local_1530 [32];
    int *local_14b0;
    String local_14a8 [176];
    String local_13f8 [176];
    long long local_1348;
    unsigned long local_1340;
    int local_1320 [32];
    int *local_12a0;
    long long local_1298;
    unsigned long local_1290;
    unsigned int local_1270 [5];
    unsigned int local_125c [27];
    unsigned int *local_11f0;
    long long local_11e8;
    unsigned long local_11e0;
    int local_11c0 [32];
    int *local_1140;
    long long local_1138;
    unsigned long local_1130;
    unsigned int local_1110 [5];
    unsigned int local_10fc [27];
    unsigned int *local_1090;
    long long local_1088;
    unsigned long local_1080;
    unsigned int local_1060 [5];
    unsigned int local_104c [27];
    unsigned int *local_fe0;
    String local_fd8 [176];
    long long local_f28;
    unsigned long local_f20;
    unsigned int local_f00 [13];
    unsigned int local_ecc [19];
    unsigned int *local_e80;
    long long local_e78;
    unsigned long local_e70;
    unsigned int local_e50 [5];
    unsigned int local_e3c [27];
    unsigned int *local_dd0;
    String local_dc8 [176];
    long long local_d18;
    unsigned long local_d10;
    unsigned int local_cf0 [12];
    unsigned int local_cc0 [20];
    unsigned int *local_c70;
    long long local_c68;
    unsigned long local_c60;
    unsigned int local_c40 [5];
    unsigned int local_c2c [27];
    unsigned int *local_bc0;
    String local_bb8 [176];
    long long local_b08;
    unsigned long local_b00;
    unsigned int local_ae0 [12];
    unsigned int local_ab0 [20];
    unsigned int *local_a60;
    long long local_a58;
    unsigned long local_a50;
    int local_a30 [32];
    int *local_9b0;
    long long local_9a8;
    unsigned long local_9a0;
    unsigned int local_980 [5];
    unsigned int local_96c [27];
    unsigned int *local_900;
    long long local_8f8;
    unsigned long local_8f0;
    unsigned int local_8d0 [5];
    unsigned int local_8bc [27];
    unsigned int *local_850;
    String local_848 [176];
    long long local_798;
    unsigned long local_790;
    unsigned int local_770 [12];
    unsigned int local_740 [20];
    unsigned int *local_6f0;
    long long local_6e8;
    unsigned long local_6e0;
    int local_6c0 [32];
    int *local_640;
    long long local_638;
    unsigned long local_630;
    unsigned int local_610 [5];
    unsigned int local_5fc [27];
    unsigned int *local_590;
    String local_588 [176];
    String local_4d8 [176];
    String local_428 [176];
    long long local_378;
    unsigned long local_370;
    unsigned int local_350 [5];
    unsigned int local_33c [27];
    unsigned int *local_2d0;
    String local_2c8 [176];
    long long local_218;
    unsigned long local_210;
    unsigned int local_1f0 [13];
    unsigned int local_1bc [19];
    unsigned int *local_170;
    UVector2 local_168;
    UVector2 local_158;
    UVector2 local_148;
    UVector2 local_138;
    UVector2 local_128;
    UVector2 local_118;
    UVector2 local_108;
    UVector2 local_f8;
    UVector2 local_e8;
    unsigned char *local_d8 [2];
    long local_c8 [2];
    unsigned char *local_b8 [2];
    long local_a8 [2];
    std::wstring local_98 [2];
    long local_88 [2];
    std::wstring local_78 [2];
    long local_68 [2];
    std::wstring local_58 [5];

    if (((m_pOwner != NULL) && (m_bOpenPartial)) && (this_00 = *(CInventory **)(m_pOwner->m_CharacterData448 + 0x48), this_00 != NULL)) {
        while(true) {
            pvVar11 = m_pUnknown30;
            if (*(long *)((long)pvVar11 + 0x80) - (long)*(long long **)((long)pvVar11 + 0x78) >> 3 == 0)
            break;
            CEGUI::Window::removeChildWindow(pvVar11,(void *)**(long long **)((long)pvVar11 + 0x78));
        }
        lVar18 = 0;
        do {
            while ((pvVar11 = *(void **)((long)&m_pUnknown1378 + lVar18), pvVar11 != NULL && (*(long *)((long)pvVar11 + 0x80) - (long)*(long long **)((long)pvVar11 + 0x78) >> 3 != 0))) {
                lVar18 = lVar18 + 8;
                CEGUI::Window::removeChildWindow(pvVar11,(void *)**(long long **)((long)pvVar11 + 0x78));
                if (lVar18 == 0x60) goto LAB_00ba2760;
            }
            lVar18 = lVar18 + 8;
        } while (lVar18 != 0x60);
        LAB_00ba2760:
        uVar21 = 0;
        pCVar19 = this;
        do {
            while (pCVar19->m_pUnknown1378 == NULL) {
                LAB_00ba313c:
                uVar21 = uVar21 + 1;
                pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
                if (uVar21 == 0xc) goto LAB_00ba3150;
            }
            lVar18 = this_00->getEquipmentRefInSlot(uVar21);
            if (lVar18 == 0) {
                if (pCVar19->m_pUnknown1378 != NULL) {
                    local_1550 = 0x20;
                    local_14b0 = NULL;
                    local_1558 = 0;
                    local_1530[0] = 0;
                    CEGUI::((String *)&local_1558)->grow(0);
                    puVar15 = local_1530;
                    if (0x20 < local_1550) {
                        puVar15 = local_14b0;
                    }
                    local_1558 = 0;
                    *puVar15 = 0;

                    CEGUI::String::String(local_14a8,"Image");

                    CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1608,local_14a8,&local_1558);

                    CEGUI::String::~String(local_14a8);
                    CEGUI::((String *)&local_1558)->~String();
                    CEGUI::String::String(local_16b8,"");

                    CEGUI::String::String(local_1608,"Image");

                    CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,local_1608,local_16b8);

                    CEGUI::String::~String(local_1608);
                    CEGUI::String::~String(local_16b8);
                    CEGUI::Window::getSize(&local_158,pCVar19->m_pUnknown1378);

                    CEGUI::Window::setSize((void *)pCVar19->m_iUnknown1B28,&local_158);
                    CEGUI::String::String(local_1818,"");

                    CEGUI::String::String(local_1768,"Image");

                    CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,local_1768,local_1818);

                    CEGUI::String::~String(local_1768);
                    CEGUI::String::~String(local_1818);
                    CEGUI::Window::getSize(&local_168,pCVar19->m_pUnknown1378);

                    CEGUI::Window::setSize((void *)pCVar19->m_iUnknown1898,&local_168);
                    puVar12 = CEGUI::((String *)(&m_Unknown58A8 + (unsigned long)uVar21 * 0x16))->build_utf8_buff();
                    CEGUI::String::String(local_18c8,puVar12);

                    CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1378,local_18c8);
                    CEGUI::String::~String(local_18c8);
                    CEGUI::String::String(local_1978,"Image");

                    CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1378,local_1978,&m_Unknown2048 + (unsigned long)uVar21 * 0x16)
                    ;
                    CEGUI::String::~String(local_1978);
                }
                goto LAB_00ba313c;
            }
            pCVar23 = *(CEquipment **)(lVar18 + 0x10);
            local_22b8 = pCVar23->m_pIconWindow;
            if (local_22b8 == NULL) {
                pCVar23->createIcon(m_pGameUI, false);
                local_22b8 = pCVar23->m_pIconWindow;
                if (local_22b8 != NULL) {
                    CEGUI::EventSet::setMutedState((void *)((long)local_22b8 + 0x38),true);
                    *(char *)((long)local_22b8 + 0x3e2) = 1;
                    goto LAB_00ba2806;
                }
            }
            else {
                LAB_00ba2806:
                if (*(void **)((long)local_22b8 + 0xb0) != NULL) {
                    CEGUI::Window::removeChildWindow(*(void **)((long)local_22b8 + 0xb0),local_22b8);
                }
                CEGUI::Window::addChildWindow(pCVar19->m_pUnknown1378,local_22b8);
            }
            pUVar8 = CEGUI::Window::getPosition(pCVar19->m_pUnknown1378);
            fVar29 = (pUVar8->d_x).d_scale * 0.0;
            uVar24 = -(unsigned int)(0.0 < fVar29);
            fVar27 = (pUVar8->d_x).d_offset;
            pUVar8 = CEGUI::Window::getPosition(pCVar19->m_pUnknown1378);
            fVar30 = (pUVar8->d_y).d_scale * 0.0;
            uVar25 = -(unsigned int)(0.0 < fVar30);
            fVar28 = (pUVar8->d_y).d_offset;
            if (((!pCVar23->m_bUnknown348) || (pCVar23->m_iSocketCount == 0)) || (bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar19->m_pUnknown1378 + 0xb0),false), !bVar5)) {
                local_6e0 = 0x20;
                local_640 = NULL;
                local_6e8 = 0;
                local_6c0[0] = 0;
                CEGUI::((String *)&local_6e8)->grow(0);
                local_6e8 = 0;
                puVar15 = local_6c0;
                if (0x20 < local_6e0) {
                    puVar15 = local_640;
                }
                *puVar15 = 0;
                local_630 = 0x20;
                local_590 = NULL;
                local_638 = 0;
                local_610[0] = 0;

                CEGUI::((String *)&local_638)->grow(5);
                puVar16 = local_590;
                if (local_630 < 0x21) {
                    puVar16 = local_610;
                }
                pbVar9 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar9 != (unsigned char *)0xfd0c12);
                local_638 = 5;
                puVar16 = local_5fc;
                if (0x20 < local_630) {
                    puVar16 = local_590 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,&local_638,&local_6e8);

                CEGUI::((String *)&local_638)->~String();
                CEGUI::((String *)&local_6e8)->~String();
            }
            else {
                if (pCVar23->m_iSocketCount < 2) {
                    if (pCVar23->m_iSocketCount == 1) {
                        CEGUI::String::String(local_428,"onesocketglow");

                        pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,local_428);
                        CEGUI::PropertyHelper::imageToString((char (*) [176])local_4d8,pvVar11);

                        CEGUI::String::String(local_588,"Image");

                        CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,local_588,local_4d8);

                        CEGUI::String::~String(local_588);

                        CEGUI::String::~String(local_4d8);
                        CEGUI::String::~String(local_428);
                    }
                }
                else {
                    local_210 = 0x20;
                    local_170 = NULL;
                    local_218 = 0;
                    local_1f0[0] = 0;
                    CEGUI::((String *)&local_218)->grow(0xd);
                    puVar16 = local_1f0;
                    if (0x20 < local_210) {
                        puVar16 = local_170;
                    }
                    pcVar10 = "twosocketglow";
                    do {
                        bVar4 = *pcVar10;
                        pcVar10 = pcVar10 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while ((unsigned char *)pcVar10 != (unsigned char *)0xfe60d0);
                    local_218 = 0xd;
                    puVar16 = local_1bc;
                    if (0x20 < local_210) {
                        puVar16 = local_170 + 0xd;
                    }
                    *puVar16 = 0;

                    pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,(String *)&local_218);
                    CEGUI::PropertyHelper::imageToString((char (*) [176])local_2c8,pvVar11);
                    local_370 = 0x20;
                    local_2d0 = NULL;
                    local_378 = 0;
                    local_350[0] = 0;

                    CEGUI::((String *)&local_378)->grow(5);
                    puVar16 = local_350;
                    if (0x20 < local_370) {
                        puVar16 = local_2d0;
                    }
                    pbVar9 = (unsigned char *)0xfd0c0d;
                    do {
                        bVar4 = *pbVar9;
                        pbVar9 = pbVar9 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while (pbVar9 != (unsigned char *)0xfd0c12);
                    local_378 = 5;
                    puVar16 = local_33c;
                    if (0x20 < local_370) {
                        puVar16 = local_2d0 + 5;
                    }
                    *puVar16 = 0;

                    CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,(String *)&local_378,local_2c8);

                    CEGUI::((String *)&local_378)->~String();

                    CEGUI::String::~String(local_2c8);
                    CEGUI::((String *)&local_218)->~String();
                }
                CEGUI::Window::moveToFront((void *)pCVar19->m_iUnknown1B28);
            }
            if (!pCVar23->m_bUnknown348) {
                pSVar22 = (String *)&local_798;
                local_790 = 0x20;
                local_6f0 = NULL;
                local_798 = 0;
                local_770[0] = 0;
                CEGUI::String::grow(pSVar22,0xc);
                puVar16 = local_770;
                if (0x20 < local_790) {
                    puVar16 = local_6f0;
                }
                pcVar10 = "unidentified";
                do {
                    bVar4 = *pcVar10;
                    pcVar10 = pcVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while ((unsigned char *)pcVar10 != (unsigned char *)0xfef79d);
                local_798 = 0xc;
                puVar16 = local_740;
                if (0x20 < local_790) {
                    puVar16 = local_6f0 + 0xc;
                }
                *puVar16 = 0;

                pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,pSVar22);
                CEGUI::PropertyHelper::imageToString((char (*) [176])local_848,pvVar11);
                local_8f0 = 0x20;
                local_850 = NULL;
                local_8f8 = 0;
                local_8d0[0] = 0;

                CEGUI::((String *)&local_8f8)->grow(5);
                puVar16 = local_8d0;
                if (0x20 < local_8f0) {
                    puVar16 = local_850;
                }
                pbVar9 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar9 != (unsigned char *)0xfd0c12);
                local_8f8 = 5;
                puVar16 = local_8bc;
                if (0x20 < local_8f0) {
                    puVar16 = local_850 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1608,(String *)&local_8f8,local_848);

                CEGUI::((String *)&local_8f8)->~String();

                CEGUI::String::~String(local_848);
            }
            else {
                pSVar22 = (String *)&local_a58;
                local_a50 = 0x20;
                local_9b0 = NULL;
                local_a58 = 0;
                local_a30[0] = 0;
                CEGUI::String::grow(pSVar22,0);
                local_a58 = 0;
                puVar15 = local_a30;
                if (0x20 < local_a50) {
                    puVar15 = local_9b0;
                }
                *puVar15 = 0;
                local_9a0 = 0x20;
                local_900 = NULL;
                local_9a8 = 0;
                local_980[0] = 0;

                CEGUI::((String *)&local_9a8)->grow(5);
                puVar16 = local_980;
                if (0x20 < local_9a0) {
                    puVar16 = local_900;
                }
                pbVar9 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar9 != (unsigned char *)0xfd0c12);
                local_9a8 = 5;
                puVar16 = local_96c;
                if (0x20 < local_9a0) {
                    puVar16 = local_900 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1608,(String *)&local_9a8,pSVar22);

                CEGUI::((String *)&local_9a8)->~String();
            }
            CEGUI::String::~String(pSVar22);
            fVar28 = (float)(int)(fVar30 + (float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000)) + fVar28;
            if (1 < pCVar23->m_iSocketCount) {
                CEGUI::Window::getSize(&local_e8,pCVar19->m_pUnknown1378);
                uVar25 = -(unsigned int)(0.0 < local_e8.d_y.d_scale * 0.0);
                fVar28 = ((float)(int)((float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000) + local_e8.d_y.d_scale * 0.0) + local_e8.d_y.d_offset) * -0.19 + fVar28;
            }
            bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar19->m_pUnknown1378 + 0xb0),false);
            if ((bVar5) && (pCVar23->m_SocketedEquipment.size() != 0)) {
                uVar25 = 0;
                do {
                    if (uVar25 < (pCVar23->m_SocketedEquipment).m_nCapacity) {
                        this_01 = (pCVar23->m_SocketedEquipment).m_pData[uVar25];
                        pvVar11 = this_01->m_pIconWindow;
                        if (pvVar11 != NULL) goto LAB_00ba2d5a;
                        LAB_00ba2eb2:
                        this_01->createIcon(m_pGameUI, false);
                        pvVar11 = this_01->m_pIconWindow;
                        if (pvVar11 != NULL) {
                            CEGUI::EventSet::setMutedState((void *)((long)pvVar11 + 0x38),true);
                            *(char *)((long)pvVar11 + 0x3e2) = 1;
                            goto LAB_00ba2d5a;
                        }
                    }
                    else {
                        this_01 = *(pCVar23->m_SocketedEquipment).m_pData;
                        pvVar11 = this_01->m_pIconWindow;
                        if (pvVar11 == NULL) goto LAB_00ba2eb2;
                        LAB_00ba2d5a:
                        if (*(void **)((long)pvVar11 + 0xb0) != NULL) {
                            CEGUI::Window::removeChildWindow(*(void **)((long)pvVar11 + 0xb0),pvVar11);
                        }
                        bVar5 = CEGUI::Window::isChild(m_pUnknown30,pvVar11);
                        if (bVar5) {
                            if (pvVar11 == NULL) goto LAB_00ba2e05;
                        }
                        else {
                            CEGUI::Window::addChildWindow(m_pUnknown30,pvVar11);
                        }
                        local_f8.d_x.d_scale = 0.0;
                        local_f8.d_y.d_scale = 0.0;
                        local_f8.d_x.d_offset = (float)(int)((float)(~uVar24 & 0xbf000000 | uVar24 & 0x3f000000) + fVar29) + fVar27
                        ;
                        local_f8.d_y.d_offset = fVar28;

                        CEGUI::Window::setPosition(pvVar11,&local_f8);
                        CEGUI::Window::getSize(&local_108,pCVar19->m_pUnknown1378);

                        CEGUI::Window::setSize(pvVar11,&local_108);
                        CEGUI::Window::moveToFront(pvVar11);
                        *(char *)((long)pvVar11 + 0x3e2) = 1;
                    }
                    LAB_00ba2e05:
                    uVar25 = uVar25 + 1;
                    CEGUI::Window::getSize(&local_118,pCVar19->m_pUnknown1378);
                    uVar26 = -(unsigned int)(0.0 < local_118.d_y.d_scale * 0.0);
                    if (pCVar23->m_SocketedEquipment.size() <= uVar25) break;
                    fVar28 = ((float)(int)((float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000) + local_118.d_y.d_scale * 0.0) + local_118.d_y.d_offset) * 0.4 +
                    fVar28;
                } while(true);
            }
            bVar5 = pCVar23->ISA(0x36);
            if (bVar5) {
                pSVar22 = (String *)&local_b08;
                local_b00 = 0x20;
                local_a60 = NULL;
                local_b08 = 0;
                local_ae0[0] = 0;
                CEGUI::String::grow(pSVar22,0xc);
                puVar16 = local_ae0;
                if (0x20 < local_b00) {
                    puVar16 = local_a60;
                }
                pcVar10 = "goldslotglow";
                do {
                    bVar4 = *pcVar10;
                    pcVar10 = pcVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while ((unsigned char *)pcVar10 != (unsigned char *)0xfe60a7);
                local_b08 = 0xc;
                puVar16 = local_ab0;
                if (0x20 < local_b00) {
                    puVar16 = local_a60 + 0xc;
                }
                *puVar16 = 0;

                pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,pSVar22);
                CEGUI::PropertyHelper::imageToString((char (*) [176])local_bb8,pvVar11);
                local_c60 = 0x20;
                local_bc0 = NULL;
                local_c68 = 0;
                local_c40[0] = 0;

                CEGUI::((String *)&local_c68)->grow(5);
                puVar16 = local_c40;
                if (0x20 < local_c60) {
                    puVar16 = local_bc0;
                }
                pbVar9 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar9 != (unsigned char *)0xfd0c12);
                local_c68 = 5;
                puVar16 = local_c2c;
                if (0x20 < local_c60) {
                    puVar16 = local_bc0 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,(String *)&local_c68,local_bb8);

                CEGUI::((String *)&local_c68)->~String();

                CEGUI::String::~String(local_bb8);
            }
            else {
                cVar6 = pCVar23->isMagical();
                if (!cVar6) {
                    pSVar22 = (String *)&local_11e8;
                    local_11e0 = 0x20;
                    local_1140 = NULL;
                    local_11e8 = 0;
                    local_11c0[0] = 0;
                    CEGUI::String::grow(pSVar22,0);
                    local_11e8 = 0;
                    puVar15 = local_11c0;
                    if (0x20 < local_11e0) {
                        puVar15 = local_1140;
                    }
                    *puVar15 = 0;
                    local_1130 = 0x20;
                    local_1090 = NULL;
                    local_1138 = 0;
                    local_1110[0] = 0;

                    CEGUI::((String *)&local_1138)->grow(5);
                    puVar16 = local_1110;
                    if (0x20 < local_1130) {
                        puVar16 = local_1090;
                    }
                    pbVar9 = (unsigned char *)0xfd0c0d;
                    do {
                        bVar4 = *pbVar9;
                        pbVar9 = pbVar9 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while (pbVar9 != (unsigned char *)0xfd0c12);
                    local_1138 = 5;
                    puVar16 = local_10fc;
                    if (0x20 < local_1130) {
                        puVar16 = local_1090 + 5;
                    }
                    *puVar16 = 0;

                    CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,(String *)&local_1138,pSVar22);

                    CEGUI::((String *)&local_1138)->~String();
                }
                else {
                    bVar5 = pCVar23->ISA(0x37);
                    if (bVar5) {
                        pSVar22 = (String *)&local_d18;
                        local_d10 = 0x20;
                        local_c70 = NULL;
                        local_d18 = 0;
                        local_cf0[0] = 0;
                        CEGUI::String::grow(pSVar22,0xc);
                        puVar16 = local_cf0;
                        if (0x20 < local_d10) {
                            puVar16 = local_c70;
                        }
                        pcVar10 = "blueslotglow";
                        do {
                            bVar4 = *pcVar10;
                            pcVar10 = pcVar10 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while ((unsigned char *)pcVar10 != (unsigned char *)0xfe60b4);
                        local_d18 = 0xc;
                        puVar16 = local_cc0;
                        if (0x20 < local_d10) {
                            puVar16 = local_c70 + 0xc;
                        }
                        *puVar16 = 0;

                        pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,pSVar22);
                        CEGUI::PropertyHelper::imageToString((char (*) [176])local_dc8,pvVar11);
                        local_e70 = 0x20;
                        local_dd0 = NULL;
                        local_e78 = 0;
                        local_e50[0] = 0;

                        CEGUI::((String *)&local_e78)->grow(5);
                        puVar16 = local_e50;
                        if (0x20 < local_e70) {
                            puVar16 = local_dd0;
                        }
                        pbVar9 = (unsigned char *)0xfd0c0d;
                        do {
                            bVar4 = *pbVar9;
                            pbVar9 = pbVar9 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while (pbVar9 != (unsigned char *)0xfd0c12);
                        local_e78 = 5;
                        puVar16 = local_e3c;
                        if (0x20 < local_e70) {
                            puVar16 = local_dd0 + 5;
                        }
                        *puVar16 = 0;

                        CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,(String *)&local_e78,local_dc8);

                        CEGUI::((String *)&local_e78)->~String();

                        CEGUI::String::~String(local_dc8);
                    }
                    else {
                        pSVar22 = (String *)&local_f28;
                        local_f20 = 0x20;
                        local_e80 = NULL;
                        local_f28 = 0;
                        local_f00[0] = 0;
                        CEGUI::String::grow(pSVar22,0xd);
                        puVar16 = local_f00;
                        if (0x20 < local_f20) {
                            puVar16 = local_e80;
                        }
                        pcVar10 = "greenslotglow";
                        do {
                            bVar4 = *pcVar10;
                            pcVar10 = pcVar10 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while ((unsigned char *)pcVar10 != (unsigned char *)0xfe60c2);
                        local_f28 = 0xd;
                        puVar16 = local_ecc;
                        if (0x20 < local_f20) {
                            puVar16 = local_e80 + 0xd;
                        }
                        *puVar16 = 0;

                        pvVar11 = CEGUI::Imageset::getImage((void *)m_iUnknown9108,pSVar22);
                        CEGUI::PropertyHelper::imageToString((char (*) [176])local_fd8,pvVar11);
                        local_1080 = 0x20;
                        local_fe0 = NULL;
                        local_1088 = 0;
                        local_1060[0] = 0;

                        CEGUI::((String *)&local_1088)->grow(5);
                        puVar16 = local_1060;
                        if (0x20 < local_1080) {
                            puVar16 = local_fe0;
                        }
                        pbVar9 = (unsigned char *)0xfd0c0d;
                        do {
                            bVar4 = *pbVar9;
                            pbVar9 = pbVar9 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while (pbVar9 != (unsigned char *)0xfd0c12);
                        local_1088 = 5;
                        puVar16 = local_104c;
                        if (0x20 < local_1080) {
                            puVar16 = local_fe0 + 5;
                        }
                        *puVar16 = 0;

                        CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,(String *)&local_1088,local_fd8);

                        CEGUI::((String *)&local_1088)->~String();

                        CEGUI::String::~String(local_fd8);
                    }
                }
            }
            CEGUI::String::~String(pSVar22);
            local_1340 = 0x20;
            local_12a0 = NULL;
            local_1348 = 0;
            local_1320[0] = 0;
            CEGUI::((String *)&local_1348)->grow(0);
            puVar15 = local_1320;
            if (0x20 < local_1340) {
                puVar15 = local_12a0;
            }
            local_1348 = 0;
            *puVar15 = 0;
            local_1290 = 0x20;
            local_11f0 = NULL;
            local_1298 = 0;
            local_1270[0] = 0;

            CEGUI::((String *)&local_1298)->grow(5);
            puVar16 = local_11f0;
            if (local_1290 < 0x21) {
                puVar16 = local_1270;
            }
            pbVar9 = (unsigned char *)0xfd0c0d;
            do {
                bVar4 = *pbVar9;
                pbVar9 = pbVar9 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar9 != (unsigned char *)0xfd0c12);
            local_1298 = 5;
            puVar16 = local_125c;
            if (0x20 < local_1290) {
                puVar16 = local_11f0 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1378,&local_1298,&local_1348);

            CEGUI::((String *)&local_1298)->~String();
            CEGUI::((String *)&local_1348)->~String();
            if (local_22b8 != NULL) {
                local_128.d_x.d_offset = 0.0;
                local_128.d_x.d_scale = 0.0;
                local_128.d_y.d_offset = 1.0;
                local_128.d_y.d_scale = 0.0;

                CEGUI::Window::setPosition(local_22b8,&local_128);
                local_138.d_x.d_offset = 0.0;
                local_138.d_x.d_scale = 0.0;
                local_138.d_y.d_offset = 0.0;
                local_138.d_y.d_scale = 0.0;

                CEGUI::Window::setPosition(local_22b8,&local_138);
                CEGUI::Window::getSize(&local_148,pCVar19->m_pUnknown1378);
                fVar27 = local_148.d_x.d_scale * 0.0;
                if (0.0 < fVar27) {
                    fVar28 = 0.5;
                }
                else {
                    fVar28 = -0.5;
                }
                local_148.d_y.d_scale = 0.0;
                local_148.d_x.d_scale = 0.0;
                local_148.d_x.d_offset = (float)(int)(fVar27 + fVar28) + local_148.d_x.d_offset;
                local_148.d_y.d_offset = local_148.d_x.d_offset * 1.5;

                CEGUI::Window::setSize(local_22b8,&local_148);
                CEGUI::Window::moveToFront(local_22b8);
                CEGUI::Window::update(local_22b8, 0.001);
            }
            CEGUI::String::String(local_13f8,"");

            CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1378,local_13f8);
            pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
            CEGUI::String::~String(local_13f8);
            uVar21 = uVar21 + 1;
        } while (uVar21 != 0xc);
        LAB_00ba3150:
        uVar21 = 0;
        pCVar19 = this;
        do {
            if (pCVar19->m_pUnknown1040 != NULL) {
                if ((updateLayout()::!g_RemoveASpell) && (iVar7 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar7 != 0)) {
                    updateLayout()::g_RemoveASpell = &DAT_01423a38;
                    __cxa_guard_release(&updateLayout()::g_RemoveASpell);
                    __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell,&__dso_handle);
                }
                if (*(long *)(updateLayout()::g_RemoveASpell - 0x18) == 0) {
                    pCVar13 = CStringTranslate::getSinglton();
                    local_58->getTranslateString(pCVar13, L"Hold [CTRL] and left-click to");

                    ((STRINGS *)local_68)->StringConvertToNarrow(local_58[0]._M_p);

                    std::((string *)&updateLayout()::g_RemoveASpell)->assign();
                }
                if ((updateLayout()::!g_RemoveASpell2) && (iVar7 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar7 != 0)) {
                    updateLayout()::g_RemoveASpell2 = &DAT_01423a38;
                    __cxa_guard_release(&updateLayout()::g_RemoveASpell2);
                    __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell2,&__dso_handle);
                }
                if (*(long *)(updateLayout()::g_RemoveASpell2 - 0x18) == 0) {
                    pCVar13 = CStringTranslate::getSinglton();
                    local_78->getTranslateString(pCVar13, L"un-learn this spell");

                    ((STRINGS *)local_88)->StringConvertToNarrow(local_78[0]._M_p);

                    std::((string *)&updateLayout()::g_RemoveASpell2)->assign();
                }
                if ((updateLayout()::!g_DragASpell) && (iVar7 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar7 != 0)) {
                    updateLayout()::g_DragASpell = &DAT_01423a38;
                    __cxa_guard_release(&updateLayout()::g_DragASpell);
                    __cxa_atexit(std::string::~string,&updateLayout()::g_DragASpell,&__dso_handle);
                }
                if (*(long *)(updateLayout()::g_DragASpell - 0x18) == 0) {
                    pCVar13 = CStringTranslate::getSinglton();
                    local_98->getTranslateString(pCVar13, L"Drag a spell here to learn it");

                    ((STRINGS *)local_a8)->StringConvertToNarrow(local_98[0]._M_p);

                    std::((string *)&updateLayout()::g_DragASpell)->assign();
                }
                this_02 = (CSkill *)m_pOwner->getKnownSpell(uVar21);
                if ((this_02 == NULL) || (plVar14 = (long *)this_02->getSkillIcon(), *(long *)(*plVar14 - 0x18) == 0)) {
                    CEGUI::String::String(local_1ce8,"");

                    CEGUI::String::String(local_1c38,"Image");

                    CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1040,local_1c38,local_1ce8);

                    CEGUI::String::~String(local_1c38);
                    CEGUI::String::~String(local_1ce8);
                    *(long long **)((long)pCVar19->m_pUnknown1040 + 0x1d8) = &m_Unknown1368;
                    CEGUI::String::String(local_1d98,updateLayout()::g_DragASpell);

                    CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1040,local_1d98);
                    CEGUI::String::~String(local_1d98);
                }
                else {
                    puVar17 = (long long *)this_02->getSkillIcon();
                    ((STRINGS *)local_b8)->StringConvertToNarrow((wchar_t *)*puVar17);

                    pvVar11 = m_pGameUI->getImageFromImageSet(local_b8[0]);
                    CEGUI::PropertyHelper::imageToString((char (*) [176])local_1a28,pvVar11);

                    CEGUI::String::String(local_1ad8,"Image");

                    CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1040,local_1ad8,local_1a28);

                    CEGUI::String::~String(local_1ad8);

                    CEGUI::String::~String(local_1a28);
                    pCVar19->m_Unknown1050 = *(long long *)(this_02->m_SkillData148 + 8);
                    *(long long **)((long)pCVar19->m_pUnknown1040 + 0x1d8) = &m_Unknown1050 + uVar21;
                    std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);

                    std::string::append((char *)local_c8, 0xfa04e8);

                    std::operator+((string *)local_d8,(string *)local_c8);

                    CEGUI::String::String(local_1b88,local_d8[0]);

                    CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1040,local_1b88);

                    CEGUI::String::~String(local_1b88);
                }
            }
            uVar21 = uVar21 + 1;
            pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
        } while (uVar21 != 2);
        local_22c8 = 0x13;
        pCVar19 = this;
        do {
            local_1ef0 = 0x20;
            local_1e50 = NULL;
            local_1ef8 = 0;
            local_1ed0[0] = 0;
            CEGUI::((String *)&local_1ef8)->grow(0);
            puVar15 = local_1ed0;
            if (0x20 < local_1ef0) {
                puVar15 = local_1e50;
            }
            local_1ef8 = 0;
            *puVar15 = 0;
            local_1e40 = 0x20;
            local_1da0 = NULL;
            local_1e48 = 0;
            local_1e20[0] = 0;

            CEGUI::((String *)&local_1e48)->grow(5);
            puVar16 = local_1e20;
            if (0x20 < local_1e40) {
                puVar16 = local_1da0;
            }
            pbVar9 = (unsigned char *)0xfd0c0d;
            do {
                bVar4 = *pbVar9;
                pbVar9 = pbVar9 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar9 != (unsigned char *)0xfd0c12);
            local_1e48 = 5;
            puVar16 = local_1e0c;
            if (0x20 < local_1e40) {
                puVar16 = local_1da0 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1930,(String *)&local_1e48,&local_1ef8);

            CEGUI::((String *)&local_1e48)->~String();
            CEGUI::((String *)&local_1ef8)->~String();
            local_2050 = 0x20;
            local_1fb0 = NULL;
            local_2058 = 0;
            local_2030[0] = 0;
            CEGUI::((String *)&local_2058)->grow(0);
            puVar15 = local_2030;
            if (0x20 < local_2050) {
                puVar15 = local_1fb0;
            }
            local_2058 = 0;
            *puVar15 = 0;
            local_1fa0 = 0x20;
            local_1f00 = NULL;
            local_1fa8 = 0;
            local_1f80[0] = 0;

            CEGUI::((String *)&local_1fa8)->grow(5);
            pbVar9 = (unsigned char *)0xfd0c0d;
            puVar16 = local_1f80;
            if (0x20 < local_1fa0) {
                puVar16 = local_1f00;
            }
            do {
                bVar4 = *pbVar9;
                pbVar9 = pbVar9 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar9 != (unsigned char *)0xfd0c12);
            local_1fa8 = 5;
            puVar16 = local_1f6c;
            if (0x20 < local_1fa0) {
                puVar16 = local_1f00 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1BC0,(String *)&local_1fa8,&local_2058);

            CEGUI::((String *)&local_1fa8)->~String();
            CEGUI::((String *)&local_2058)->~String();
            local_21b0 = 0x20;
            local_2110 = NULL;
            local_21b8 = 0;
            local_2190[0] = 0;
            CEGUI::((String *)&local_21b8)->grow(0);
            puVar15 = local_2190;
            if (0x20 < local_21b0) {
                puVar15 = local_2110;
            }
            local_21b8 = 0;
            *puVar15 = 0;
            local_2100 = 0x20;
            local_2060 = NULL;
            local_2108 = 0;
            local_20e0[0] = 0;

            CEGUI::((String *)&local_2108)->grow(5);
            pbVar9 = (unsigned char *)0xfd0c0d;
            puVar16 = local_20e0;
            if (0x20 < local_2100) {
                puVar16 = local_2060;
            }
            do {
                bVar4 = *pbVar9;
                pbVar9 = pbVar9 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar9 != (unsigned char *)0xfd0c12);
            local_2108 = 5;
            puVar16 = local_20cc;
            if (0x20 < local_2100) {
                puVar16 = local_2060 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown16A0,(String *)&local_2108,&local_21b8);

            CEGUI::((String *)&local_2108)->~String();
            CEGUI::((String *)&local_21b8)->~String();
            if (pCVar19->m_pUnknown1E50 != NULL) {
                CEGUI::String::String(local_2268,"");

                CEGUI::Window::setText(pCVar19->m_pUnknown1E50,local_2268);
                CEGUI::String::~String(local_2268);
            }
            pvVar11 = pCVar19->m_pUnknown1410;
            if (*(long *)((long)pvVar11 + 0x80) - (long)*(long long **)((long)pvVar11 + 0x78) >> 3 != 0)
            {
                CEGUI::Window::removeChildWindow(pvVar11,(void *)**(long long **)((long)pvVar11 + 0x78));
            }
            local_22c8 = local_22c8 + 1;
            pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
        } while (local_22c8 != 0x52);
        if (*(int *)(this_00->m_Unknown30 + 8) != 0) {
            uVar20 = 0;
            do {
                uVar21 = (unsigned int)uVar20;
                if (uVar21 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                    plVar14 = *(long **)this_00->m_Unknown30;
                    lVar18 = plVar14[uVar20];
                    pCVar23 = *(CEquipment **)(lVar18 + 0x10);
                }
                else {
                    plVar14 = *(long **)this_00->m_Unknown30;
                    lVar18 = *plVar14;
                    pCVar23 = *(CEquipment **)(lVar18 + 0x10);
                }
                if (0x12 < *(int *)(lVar18 + 0x18)) {
                    if (uVar21 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                        plVar14 = (long *)(uVar20 * 8 + *(long *)this_00->m_Unknown30);
                    }
                    iVar7 = this_00->getItemPane(*(unsigned int *)(*plVar14 + 0x18));
                    if (iVar7 == m_iUnknown6C) {
                        if (uVar21 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                            plVar14 = (long *)(uVar20 * 8 + *(long *)this_00->m_Unknown30);
                        }
                        else {
                            plVar14 = *(long **)this_00->m_Unknown30;
                        }
                        setSlotIcon(pCVar23,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
                    }
                }
                uVar20 = (unsigned long)(uVar21 + 1);
            } while (uVar21 + 1 < *(unsigned int *)(this_00->m_Unknown30 + 8));
        }
        CEGUI::Window::moveToBack(m_pUnknown20);
        CEGUI::Window::moveToFront(m_pUnknown48);
        CEGUI::Window::moveToFront(m_pUnknown28);
        CEGUI::Window::moveToFront(m_pUnknown30);
        CEGUI::Window::moveToFront(m_pUnknown40);
    }
}
