void CPetMenu::updateLayout()
{
    unsigned char bVar4;
    CInventory *this_00;
    Window *pWVar5;
    char cVar6;
    bool bVar7;
    int iVar8;
    float *pfVar9;
    unsigned char *pbVar10;
    char *pcVar11;
    CEquipment *this_01;
    unsigned char *puVar12;
    CStringTranslate *pCVar13;
    CSkill *this_02;
    long *plVar14;
    int *puVar15;
    unsigned int *puVar16;
    long long *puVar17;
    long lVar18;
    UVector2 *pUVar19;
    CPetMenu *pCVar20;
    unsigned long uVar21;
    unsigned int uVar22;
    String *pSVar23;
    CEquipment *pCVar24;
    unsigned int uVar26;
    unsigned int uVar27;
    float fVar28;
    float fVar29;
    float fVar30;
    float fVar31;
    int local_22c8;
    UVector2 *local_22b8;
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
    Image local_1a28 [176];
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
    Image local_fd8 [176];
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
    Image local_dc8 [176];
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
    Image local_bb8 [176];
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
    Image local_848 [176];
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
    Image local_4d8 [176];
    String local_428 [176];
    long long local_378;
    unsigned long local_370;
    unsigned int local_350 [5];
    unsigned int local_33c [27];
    unsigned int *local_2d0;
    Image local_2c8 [176];
    long long local_218;
    unsigned long local_210;
    unsigned int local_1f0 [13];
    unsigned int local_1bc [19];
    unsigned int *local_170;
    float local_148;
    float local_144;
    float local_110;
    float local_10c;
    float local_e0;
    float local_dc;
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
        while (pWVar5 = m_pUnknown30, *(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0) {
            CEGUI::Window::removeChildWindow(pWVar5);
        }
        lVar18 = 0;
        do {
            while ((pWVar5 = *(Window **)((long)&m_pUnknown1378 + lVar18), pWVar5 != NULL && (*(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0))) {
                lVar18 = lVar18 + 8;
                CEGUI::Window::removeChildWindow(pWVar5);
                if (lVar18 == 0x60) goto LAB_00ba2760;
            }
            lVar18 = lVar18 + 8;
        } while (lVar18 != 0x60);
        LAB_00ba2760:
        uVar22 = 0;
        pCVar20 = this;
        do {
            while (pCVar20->m_pUnknown1378 == NULL) {
                LAB_00ba313c:
                uVar22 = uVar22 + 1;
                pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
                if (uVar22 == 0xc) goto LAB_00ba3150;
            }
            lVar18 = this_00->getEquipmentRefInSlot(uVar22);
            if (lVar18 == 0) {
                if (pCVar20->m_pUnknown1378 != NULL) {
                    local_1550 = 0x20;
                    local_14b0 = NULL;
                    local_1558 = 0;
                    local_1530[0] = 0;
                    CEGUI::String::grow((unsigned long)&local_1558);
                    puVar15 = local_1530;
                    if (0x20 < local_1550) {
                        puVar15 = local_14b0;
                    }
                    local_1558 = 0;
                    *puVar15 = 0;

                    CEGUI::String::String(local_14a8,"Image");

                    CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,local_14a8);

                    CEGUI::String::~String(local_14a8);
                    CEGUI::((String *)&local_1558)->~String();
                    CEGUI::String::String(local_16b8,"");

                    CEGUI::String::String(local_1608,"Image");

                    CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,local_1608);

                    CEGUI::String::~String(local_1608);
                    CEGUI::String::~String(local_16b8);
                    CEGUI::Window::getSize();

                    CEGUI::Window::setSize((UVector2 *)pCVar20->m_iUnknown1B28);
                    CEGUI::String::String(local_1818,"");

                    CEGUI::String::String(local_1768,"Image");

                    CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,local_1768);

                    CEGUI::String::~String(local_1768);
                    CEGUI::String::~String(local_1818);
                    CEGUI::Window::getSize();

                    CEGUI::Window::setSize((UVector2 *)pCVar20->m_iUnknown1898);
                    puVar12 = (unsigned char *)CEGUI::String::build_utf8_buff();
                    CEGUI::String::String(local_18c8,puVar12);

                    CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1378);
                    CEGUI::String::~String(local_18c8);
                    CEGUI::String::String(local_1978,"Image");

                    CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1378,local_1978);
                    CEGUI::String::~String(local_1978);
                }
                goto LAB_00ba313c;
            }
            pCVar24 = *(CEquipment **)(lVar18 + 0x10);
            local_22b8 = pCVar24->m_pIconWindow;
            if (local_22b8 == NULL) {
                pCVar24->createIcon(m_pGameUI, false);
                local_22b8 = pCVar24->m_pIconWindow;
                if (local_22b8 != NULL) {
                    CEGUI::EventSet::setMutedState((bool)((char)local_22b8 + '8'));
                    local_22b8[0x3e2] = (UVector2)0x1;
                    goto LAB_00ba2806;
                }
            }
            else {
                LAB_00ba2806:
                if (*(Window **)(local_22b8 + 0xb0) != NULL) {
                    CEGUI::Window::removeChildWindow(*(Window **)(local_22b8 + 0xb0));
                }
                CEGUI::Window::addChildWindow(pCVar20->m_pUnknown1378);
            }
            pfVar9 = (float *)CEGUI::Window::getPosition();
            fVar28 = *pfVar9;
            fVar30 = pfVar9[1];
            lVar18 = CEGUI::Window::getPosition();
            fVar31 = *(float *)(lVar18 + 8) * 0.0;
            uVar26 = -(unsigned int)(0.0 < fVar31);
            fVar29 = *(float *)(lVar18 + 0xc);
            if (((!pCVar24->m_bUnknown348) || (pCVar24->m_iSocketCount == 0)) || (cVar6 = CEGUI::Window::isVisible(SUB81(*(long long *)((long)pCVar20->m_pUnknown1378 + 0xb0),0)), !cVar6)) {
                local_6e0 = 0x20;
                local_640 = NULL;
                local_6e8 = 0;
                local_6c0[0] = 0;
                CEGUI::String::grow((unsigned long)&local_6e8);
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

                CEGUI::String::grow((unsigned long)&local_638);
                puVar16 = local_590;
                if (local_630 < 0x21) {
                    puVar16 = local_610;
                }
                pbVar10 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar10;
                    pbVar10 = pbVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar10 != (unsigned char *)0xfd0c12);
                local_638 = 5;
                puVar16 = local_5fc;
                if (0x20 < local_630) {
                    puVar16 = local_590 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,(String *)&local_638);

                CEGUI::((String *)&local_638)->~String();
                CEGUI::((String *)&local_6e8)->~String();
            }
            else {
                if (pCVar24->m_iSocketCount < 2) {
                    if (pCVar24->m_iSocketCount == 1) {
                        CEGUI::String::String(local_428,"onesocketglow");

                        CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                        CEGUI::PropertyHelper::imageToString(local_4d8);

                        CEGUI::String::String(local_588,"Image");

                        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,local_588);

                        CEGUI::String::~String(local_588);

                        CEGUI::((String *)local_4d8)->~String();
                        CEGUI::String::~String(local_428);
                    }
                }
                else {
                    local_210 = 0x20;
                    local_170 = NULL;
                    local_218 = 0;
                    local_1f0[0] = 0;
                    CEGUI::String::grow((unsigned long)&local_218);
                    puVar16 = local_1f0;
                    if (0x20 < local_210) {
                        puVar16 = local_170;
                    }
                    pcVar11 = "twosocketglow";
                    do {
                        bVar4 = *pcVar11;
                        pcVar11 = pcVar11 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while ((unsigned char *)pcVar11 != (unsigned char *)0xfe60d0);
                    local_218 = 0xd;
                    puVar16 = local_1bc;
                    if (0x20 < local_210) {
                        puVar16 = local_170 + 0xd;
                    }
                    *puVar16 = 0;

                    CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                    CEGUI::PropertyHelper::imageToString(local_2c8);
                    local_370 = 0x20;
                    local_2d0 = NULL;
                    local_378 = 0;
                    local_350[0] = 0;

                    CEGUI::String::grow((unsigned long)&local_378);
                    puVar16 = local_350;
                    if (0x20 < local_370) {
                        puVar16 = local_2d0;
                    }
                    pbVar10 = (unsigned char *)0xfd0c0d;
                    do {
                        bVar4 = *pbVar10;
                        pbVar10 = pbVar10 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while (pbVar10 != (unsigned char *)0xfd0c12);
                    local_378 = 5;
                    puVar16 = local_33c;
                    if (0x20 < local_370) {
                        puVar16 = local_2d0 + 5;
                    }
                    *puVar16 = 0;

                    CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,(String *)&local_378);

                    CEGUI::((String *)&local_378)->~String();

                    CEGUI::((String *)local_2c8)->~String();
                    CEGUI::((String *)&local_218)->~String();
                }
                CEGUI::Window::moveToFront();
            }
            if (!pCVar24->m_bUnknown348) {
                pSVar23 = (String *)&local_798;
                local_790 = 0x20;
                local_6f0 = NULL;
                local_798 = 0;
                local_770[0] = 0;
                CEGUI::String::grow((unsigned long)pSVar23);
                puVar16 = local_770;
                if (0x20 < local_790) {
                    puVar16 = local_6f0;
                }
                pcVar11 = "unidentified";
                do {
                    bVar4 = *pcVar11;
                    pcVar11 = pcVar11 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while ((unsigned char *)pcVar11 != (unsigned char *)0xfef79d);
                local_798 = 0xc;
                puVar16 = local_740;
                if (0x20 < local_790) {
                    puVar16 = local_6f0 + 0xc;
                }
                *puVar16 = 0;

                CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                CEGUI::PropertyHelper::imageToString(local_848);
                local_8f0 = 0x20;
                local_850 = NULL;
                local_8f8 = 0;
                local_8d0[0] = 0;

                CEGUI::String::grow((unsigned long)&local_8f8);
                puVar16 = local_8d0;
                if (0x20 < local_8f0) {
                    puVar16 = local_850;
                }
                pbVar10 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar10;
                    pbVar10 = pbVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar10 != (unsigned char *)0xfd0c12);
                local_8f8 = 5;
                puVar16 = local_8bc;
                if (0x20 < local_8f0) {
                    puVar16 = local_850 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,(String *)&local_8f8);

                CEGUI::((String *)&local_8f8)->~String();

                CEGUI::((String *)local_848)->~String();
            }
            else {
                pSVar23 = (String *)&local_a58;
                local_a50 = 0x20;
                local_9b0 = NULL;
                local_a58 = 0;
                local_a30[0] = 0;
                CEGUI::String::grow((unsigned long)pSVar23);
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

                CEGUI::String::grow((unsigned long)&local_9a8);
                puVar16 = local_980;
                if (0x20 < local_9a0) {
                    puVar16 = local_900;
                }
                pbVar10 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar10;
                    pbVar10 = pbVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar10 != (unsigned char *)0xfd0c12);
                local_9a8 = 5;
                puVar16 = local_96c;
                if (0x20 < local_9a0) {
                    puVar16 = local_900 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,(String *)&local_9a8);

                CEGUI::((String *)&local_9a8)->~String();
            }
            CEGUI::String::~String(pSVar23);
            fVar29 = (float)(int)(fVar31 + (float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000)) + fVar29;
            if (1 < pCVar24->m_iSocketCount) {
                CEGUI::Window::getSize();
                uVar26 = -(unsigned int)(0.0 < local_e0 * 0.0);
                fVar29 = ((float)(int)((float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000) + local_e0 * 0.0) + local_dc) * -0.19 + fVar29;
            }
            cVar6 = CEGUI::Window::isVisible(SUB81(*(long long *)((long)pCVar20->m_pUnknown1378 + 0xb0),0));
            if ((cVar6) && (pCVar24->m_SocketedEquipment.size() != 0)) {
                uVar26 = 0;
                do {
                    if (uVar26 < (pCVar24->m_SocketedEquipment).m_nCapacity) {
                        this_01 = (pCVar24->m_SocketedEquipment).m_pData[uVar26];
                        pUVar19 = this_01->m_pIconWindow;
                        if (pUVar19 != NULL) goto LAB_00ba2d5a;
                        LAB_00ba2eb2:
                        this_01->createIcon(m_pGameUI, false);
                        pUVar19 = this_01->m_pIconWindow;
                        if (pUVar19 != NULL) {
                            CEGUI::EventSet::setMutedState((bool)((char)pUVar19 + '8'));
                            pUVar19[0x3e2] = (UVector2)0x1;
                            goto LAB_00ba2d5a;
                        }
                    }
                    else {
                        this_01 = *(pCVar24->m_SocketedEquipment).m_pData;
                        pUVar19 = this_01->m_pIconWindow;
                        if (pUVar19 == NULL) goto LAB_00ba2eb2;
                        LAB_00ba2d5a:
                        if (*(Window **)(pUVar19 + 0xb0) != NULL) {
                            CEGUI::Window::removeChildWindow(*(Window **)(pUVar19 + 0xb0));
                        }
                        cVar6 = CEGUI::Window::isChild(m_pUnknown30);
                        if (!cVar6) {
                            CEGUI::Window::addChildWindow(m_pUnknown30);
                        }
                        else if (pUVar19 == NULL) goto LAB_00ba2e05;

                        CEGUI::Window::setPosition(pUVar19);
                        CEGUI::Window::getSize();

                        CEGUI::Window::setSize(pUVar19);
                        CEGUI::Window::moveToFront();
                        pUVar19[0x3e2] = (UVector2)0x1;
                    }
                    LAB_00ba2e05:
                    uVar26 = uVar26 + 1;
                    CEGUI::Window::getSize();
                    uVar27 = -(unsigned int)(0.0 < local_110 * 0.0);
                    if (pCVar24->m_SocketedEquipment.size() <= uVar26) break;
                    fVar29 = ((float)(int)((float)(~uVar27 & 0xbf000000 | uVar27 & 0x3f000000) + local_110 * 0.0) + local_10c) * 0.4 + fVar29;
                } while(true);
            }
            bVar7 = pCVar24->ISA(0x36);
            if (bVar7) {
                pSVar23 = (String *)&local_b08;
                local_b00 = 0x20;
                local_a60 = NULL;
                local_b08 = 0;
                local_ae0[0] = 0;
                CEGUI::String::grow((unsigned long)pSVar23);
                puVar16 = local_ae0;
                if (0x20 < local_b00) {
                    puVar16 = local_a60;
                }
                pcVar11 = "goldslotglow";
                do {
                    bVar4 = *pcVar11;
                    pcVar11 = pcVar11 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while ((unsigned char *)pcVar11 != (unsigned char *)0xfe60a7);
                local_b08 = 0xc;
                puVar16 = local_ab0;
                if (0x20 < local_b00) {
                    puVar16 = local_a60 + 0xc;
                }
                *puVar16 = 0;

                CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                CEGUI::PropertyHelper::imageToString(local_bb8);
                local_c60 = 0x20;
                local_bc0 = NULL;
                local_c68 = 0;
                local_c40[0] = 0;

                CEGUI::String::grow((unsigned long)&local_c68);
                puVar16 = local_c40;
                if (0x20 < local_c60) {
                    puVar16 = local_bc0;
                }
                pbVar10 = (unsigned char *)0xfd0c0d;
                do {
                    bVar4 = *pbVar10;
                    pbVar10 = pbVar10 + 1;
                    *puVar16 = (unsigned int)bVar4;
                    puVar16 = puVar16 + 1;
                } while (pbVar10 != (unsigned char *)0xfd0c12);
                local_c68 = 5;
                puVar16 = local_c2c;
                if (0x20 < local_c60) {
                    puVar16 = local_bc0 + 5;
                }
                *puVar16 = 0;

                CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_c68);

                CEGUI::((String *)&local_c68)->~String();

                CEGUI::((String *)local_bb8)->~String();
            }
            else {
                cVar6 = pCVar24->isMagical();
                if (!cVar6) {
                    pSVar23 = (String *)&local_11e8;
                    local_11e0 = 0x20;
                    local_1140 = NULL;
                    local_11e8 = 0;
                    local_11c0[0] = 0;
                    CEGUI::String::grow((unsigned long)pSVar23);
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

                    CEGUI::String::grow((unsigned long)&local_1138);
                    puVar16 = local_1110;
                    if (0x20 < local_1130) {
                        puVar16 = local_1090;
                    }
                    pbVar10 = (unsigned char *)0xfd0c0d;
                    do {
                        bVar4 = *pbVar10;
                        pbVar10 = pbVar10 + 1;
                        *puVar16 = (unsigned int)bVar4;
                        puVar16 = puVar16 + 1;
                    } while (pbVar10 != (unsigned char *)0xfd0c12);
                    local_1138 = 5;
                    puVar16 = local_10fc;
                    if (0x20 < local_1130) {
                        puVar16 = local_1090 + 5;
                    }
                    *puVar16 = 0;

                    CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_1138);

                    CEGUI::((String *)&local_1138)->~String();
                }
                else {
                    bVar7 = pCVar24->ISA(0x37);
                    if (bVar7) {
                        pSVar23 = (String *)&local_d18;
                        local_d10 = 0x20;
                        local_c70 = NULL;
                        local_d18 = 0;
                        local_cf0[0] = 0;
                        CEGUI::String::grow((unsigned long)pSVar23);
                        puVar16 = local_cf0;
                        if (0x20 < local_d10) {
                            puVar16 = local_c70;
                        }
                        pcVar11 = "blueslotglow";
                        do {
                            bVar4 = *pcVar11;
                            pcVar11 = pcVar11 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while ((unsigned char *)pcVar11 != (unsigned char *)0xfe60b4);
                        local_d18 = 0xc;
                        puVar16 = local_cc0;
                        if (0x20 < local_d10) {
                            puVar16 = local_c70 + 0xc;
                        }
                        *puVar16 = 0;

                        CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                        CEGUI::PropertyHelper::imageToString(local_dc8);
                        local_e70 = 0x20;
                        local_dd0 = NULL;
                        local_e78 = 0;
                        local_e50[0] = 0;

                        CEGUI::String::grow((unsigned long)&local_e78);
                        puVar16 = local_e50;
                        if (0x20 < local_e70) {
                            puVar16 = local_dd0;
                        }
                        pbVar10 = (unsigned char *)0xfd0c0d;
                        do {
                            bVar4 = *pbVar10;
                            pbVar10 = pbVar10 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while (pbVar10 != (unsigned char *)0xfd0c12);
                        local_e78 = 5;
                        puVar16 = local_e3c;
                        if (0x20 < local_e70) {
                            puVar16 = local_dd0 + 5;
                        }
                        *puVar16 = 0;

                        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_e78);

                        CEGUI::((String *)&local_e78)->~String();

                        CEGUI::((String *)local_dc8)->~String();
                    }
                    else {
                        pSVar23 = (String *)&local_f28;
                        local_f20 = 0x20;
                        local_e80 = NULL;
                        local_f28 = 0;
                        local_f00[0] = 0;
                        CEGUI::String::grow((unsigned long)pSVar23);
                        puVar16 = local_f00;
                        if (0x20 < local_f20) {
                            puVar16 = local_e80;
                        }
                        pcVar11 = "greenslotglow";
                        do {
                            bVar4 = *pcVar11;
                            pcVar11 = pcVar11 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while ((unsigned char *)pcVar11 != (unsigned char *)0xfe60c2);
                        local_f28 = 0xd;
                        puVar16 = local_ecc;
                        if (0x20 < local_f20) {
                            puVar16 = local_e80 + 0xd;
                        }
                        *puVar16 = 0;

                        CEGUI::Imageset::getImage((String *)m_iUnknown9108);
                        CEGUI::PropertyHelper::imageToString(local_fd8);
                        local_1080 = 0x20;
                        local_fe0 = NULL;
                        local_1088 = 0;
                        local_1060[0] = 0;

                        CEGUI::String::grow((unsigned long)&local_1088);
                        puVar16 = local_1060;
                        if (0x20 < local_1080) {
                            puVar16 = local_fe0;
                        }
                        pbVar10 = (unsigned char *)0xfd0c0d;
                        do {
                            bVar4 = *pbVar10;
                            pbVar10 = pbVar10 + 1;
                            *puVar16 = (unsigned int)bVar4;
                            puVar16 = puVar16 + 1;
                        } while (pbVar10 != (unsigned char *)0xfd0c12);
                        local_1088 = 5;
                        puVar16 = local_104c;
                        if (0x20 < local_1080) {
                            puVar16 = local_fe0 + 5;
                        }
                        *puVar16 = 0;

                        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_1088)
                        ;

                        CEGUI::((String *)&local_1088)->~String();

                        CEGUI::((String *)local_fd8)->~String();
                    }
                }
            }
            CEGUI::String::~String(pSVar23);
            local_1340 = 0x20;
            local_12a0 = NULL;
            local_1348 = 0;
            local_1320[0] = 0;
            CEGUI::String::grow((unsigned long)&local_1348);
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

            CEGUI::String::grow((unsigned long)&local_1298);
            puVar16 = local_11f0;
            if (local_1290 < 0x21) {
                puVar16 = local_1270;
            }
            pbVar10 = (unsigned char *)0xfd0c0d;
            do {
                bVar4 = *pbVar10;
                pbVar10 = pbVar10 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar10 != (unsigned char *)0xfd0c12);
            local_1298 = 5;
            puVar16 = local_125c;
            if (0x20 < local_1290) {
                puVar16 = local_11f0 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1378,(String *)&local_1298);

            CEGUI::((String *)&local_1298)->~String();
            CEGUI::((String *)&local_1348)->~String();
            if (local_22b8 != NULL) {

                CEGUI::Window::setPosition(local_22b8);

                CEGUI::Window::setPosition(local_22b8);
                CEGUI::Window::getSize();
                fVar28 = local_148 * 0.0;
                if (0.0 < fVar28) {
                    fVar30 = 0.5;
                }
                else {
                    fVar30 = -0.5;
                }
                local_148 = 0.0;
                local_144 = (float)(int)(fVar28 + fVar30) + local_144;

                CEGUI::Window::setSize(local_22b8);
                CEGUI::Window::moveToFront();
                CEGUI::Window::update(0.001);
            }
            CEGUI::String::String(local_13f8,"");

            CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1378);
            pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
            CEGUI::String::~String(local_13f8);
            uVar22 = uVar22 + 1;
        } while (uVar22 != 0xc);
        LAB_00ba3150:
        uVar22 = 0;
        pCVar20 = this;
        do {
            if (pCVar20->m_pUnknown1040 != NULL) {
                if ((updateLayout()::!g_RemoveASpell) && (iVar8 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar8 != 0)) {
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
                if ((updateLayout()::!g_RemoveASpell2) && (iVar8 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar8 != 0)) {
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
                if ((updateLayout()::!g_DragASpell) && (iVar8 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar8 != 0)) {
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
                this_02 = (CSkill *)m_pOwner->getKnownSpell(uVar22);
                if ((this_02 == NULL) || (plVar14 = (long *)this_02->getSkillIcon(), *(long *)(*plVar14 - 0x18) == 0)) {
                    CEGUI::String::String(local_1ce8,"");

                    CEGUI::String::String(local_1c38,"Image");

                    CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1040,local_1c38);

                    CEGUI::String::~String(local_1c38);
                    CEGUI::String::~String(local_1ce8);
                    *(long long **)((long)pCVar20->m_pUnknown1040 + 0x1d8) = &m_Unknown1368;
                    CEGUI::String::String(local_1d98,updateLayout()::g_DragASpell);

                    CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1040);
                    CEGUI::String::~String(local_1d98);
                }
                else {
                    puVar17 = (long long *)this_02->getSkillIcon();
                    ((STRINGS *)local_b8)->StringConvertToNarrow((wchar_t *)*puVar17);

                    m_pGameUI->getImageFromImageSet(local_b8[0]);
                    CEGUI::PropertyHelper::imageToString(local_1a28);

                    CEGUI::String::String(local_1ad8,"Image");

                    CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1040,local_1ad8);

                    CEGUI::String::~String(local_1ad8);

                    CEGUI::((String *)local_1a28)->~String();
                    pCVar20->m_Unknown1050 = *(long long *)(this_02->m_SkillData148 + 8);
                    *(long long **)((long)pCVar20->m_pUnknown1040 + 0x1d8) = &m_Unknown1050 + uVar22;
                    std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);

                    std::string::append((char *)local_c8, 0xfa04e8);

                    std::operator+((string *)local_d8,(string *)local_c8);

                    CEGUI::String::String(local_1b88,local_d8[0]);

                    CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1040);

                    CEGUI::String::~String(local_1b88);
                }
            }
            uVar22 = uVar22 + 1;
            pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
        } while (uVar22 != 2);
        local_22c8 = 0x13;
        pCVar20 = this;
        do {
            local_1ef0 = 0x20;
            local_1e50 = NULL;
            local_1ef8 = 0;
            local_1ed0[0] = 0;
            CEGUI::String::grow((unsigned long)&local_1ef8);
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

            CEGUI::String::grow((unsigned long)&local_1e48);
            puVar16 = local_1e20;
            if (0x20 < local_1e40) {
                puVar16 = local_1da0;
            }
            pbVar10 = (unsigned char *)0xfd0c0d;
            do {
                bVar4 = *pbVar10;
                pbVar10 = pbVar10 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar10 != (unsigned char *)0xfd0c12);
            local_1e48 = 5;
            puVar16 = local_1e0c;
            if (0x20 < local_1e40) {
                puVar16 = local_1da0 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1930,(String *)&local_1e48);

            CEGUI::((String *)&local_1e48)->~String();
            CEGUI::((String *)&local_1ef8)->~String();
            local_2050 = 0x20;
            local_1fb0 = NULL;
            local_2058 = 0;
            local_2030[0] = 0;
            CEGUI::String::grow((unsigned long)&local_2058);
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

            CEGUI::String::grow((unsigned long)&local_1fa8);
            pbVar10 = (unsigned char *)0xfd0c0d;
            puVar16 = local_1f80;
            if (0x20 < local_1fa0) {
                puVar16 = local_1f00;
            }
            do {
                bVar4 = *pbVar10;
                pbVar10 = pbVar10 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar10 != (unsigned char *)0xfd0c12);
            local_1fa8 = 5;
            puVar16 = local_1f6c;
            if (0x20 < local_1fa0) {
                puVar16 = local_1f00 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1BC0,(String *)&local_1fa8);

            CEGUI::((String *)&local_1fa8)->~String();
            CEGUI::((String *)&local_2058)->~String();
            local_21b0 = 0x20;
            local_2110 = NULL;
            local_21b8 = 0;
            local_2190[0] = 0;
            CEGUI::String::grow((unsigned long)&local_21b8);
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

            CEGUI::String::grow((unsigned long)&local_2108);
            pbVar10 = (unsigned char *)0xfd0c0d;
            puVar16 = local_20e0;
            if (0x20 < local_2100) {
                puVar16 = local_2060;
            }
            do {
                bVar4 = *pbVar10;
                pbVar10 = pbVar10 + 1;
                *puVar16 = (unsigned int)bVar4;
                puVar16 = puVar16 + 1;
            } while (pbVar10 != (unsigned char *)0xfd0c12);
            local_2108 = 5;
            puVar16 = local_20cc;
            if (0x20 < local_2100) {
                puVar16 = local_2060 + 5;
            }
            *puVar16 = 0;

            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown16A0,(String *)&local_2108);

            CEGUI::((String *)&local_2108)->~String();
            CEGUI::((String *)&local_21b8)->~String();
            if (pCVar20->m_pUnknown1E50 != NULL) {
                CEGUI::String::String(local_2268,"");

                CEGUI::Window::setText(pCVar20->m_pUnknown1E50);
                CEGUI::String::~String(local_2268);
            }
            pWVar5 = pCVar20->m_pUnknown1410;
            if (*(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0) {
                CEGUI::Window::removeChildWindow(pWVar5);
            }
            local_22c8 = local_22c8 + 1;
            pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
        } while (local_22c8 != 0x52);
        if (*(int *)(this_00->m_Unknown30 + 8) != 0) {
            uVar21 = 0;
            do {
                uVar22 = (unsigned int)uVar21;
                if (uVar22 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                    plVar14 = *(long **)this_00->m_Unknown30;
                    lVar18 = plVar14[uVar21];
                    pCVar24 = *(CEquipment **)(lVar18 + 0x10);
                }
                else {
                    plVar14 = *(long **)this_00->m_Unknown30;
                    lVar18 = *plVar14;
                    pCVar24 = *(CEquipment **)(lVar18 + 0x10);
                }
                if (0x12 < *(int *)(lVar18 + 0x18)) {
                    if (uVar22 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                        plVar14 = (long *)(uVar21 * 8 + *(long *)this_00->m_Unknown30);
                    }
                    iVar8 = this_00->getItemPane(*(unsigned int *)(*plVar14 + 0x18));
                    if (iVar8 == m_iUnknown6C) {
                        if (uVar22 < *(unsigned int *)(this_00->m_Unknown30 + 0xc)) {
                            plVar14 = (long *)(uVar21 * 8 + *(long *)this_00->m_Unknown30);
                        }
                        else {
                            plVar14 = *(long **)this_00->m_Unknown30;
                        }
                        setSlotIcon(pCVar24,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
                    }
                }
                uVar21 = (unsigned long)(uVar22 + 1);
            } while (uVar22 + 1 < *(unsigned int *)(this_00->m_Unknown30 + 8));
        }
        CEGUI::Window::moveToBack();
        CEGUI::Window::moveToFront();
        CEGUI::Window::moveToFront();
        CEGUI::Window::moveToFront();
        CEGUI::Window::moveToFront();
    }
}
