
/* WARNING: Removing unreachable block (ram,0x00ba501d) */
/* WARNING: Removing unreachable block (ram,0x00ba50dd) */
/* WARNING: Removing unreachable block (ram,0x00ba4ced) */
/* WARNING: Removing unreachable block (ram,0x00ba4c8e) */
/* WARNING: Removing unreachable block (ram,0x00ba5000) */
/* WARNING: Removing unreachable block (ram,0x00ba516f) */
/* WARNING: Removing unreachable block (ram,0x00ba4cf8) */
/* WARNING: Removing unreachable block (ram,0x00ba506a) */
/* WARNING: Removing unreachable block (ram,0x00ba50e8) */
/* CPetMenu::updateLayout() */

void __thiscall CPetMenu::updateLayout(CPetMenu *this)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  byte bVar4;
  CInventory *this_00;
  bool bVar5;
  char cVar6;
  int iVar7;
  UVector2 *pUVar8;
  byte *pbVar9;
  char *pcVar10;
  void *pvVar11;
  CEquipment *this_01;
  uchar *puVar12;
  CStringTranslate *pCVar13;
  CSkill *this_02;
  long *plVar14;
  undefined4 *puVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  CPetMenu *pCVar19;
  ulong uVar20;
  uint uVar21;
  String *pSVar22;
  CEquipment *pCVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  int local_22c8;
  void *local_22b8;
  String local_2268 [176];
  undefined8 local_21b8;
  ulong local_21b0;
  undefined8 local_21a8;
  undefined8 local_21a0;
  undefined8 local_2198;
  undefined4 local_2190 [32];
  undefined4 *local_2110;
  undefined8 local_2108;
  ulong local_2100;
  undefined8 local_20f8;
  undefined8 local_20f0;
  undefined8 local_20e8;
  uint local_20e0 [5];
  uint local_20cc [27];
  uint *local_2060;
  undefined8 local_2058;
  ulong local_2050;
  undefined8 local_2048;
  undefined8 local_2040;
  undefined8 local_2038;
  undefined4 local_2030 [32];
  undefined4 *local_1fb0;
  undefined8 local_1fa8;
  ulong local_1fa0;
  undefined8 local_1f98;
  undefined8 local_1f90;
  undefined8 local_1f88;
  uint local_1f80 [5];
  uint local_1f6c [27];
  uint *local_1f00;
  undefined8 local_1ef8;
  ulong local_1ef0;
  undefined8 local_1ee8;
  undefined8 local_1ee0;
  undefined8 local_1ed8;
  undefined4 local_1ed0 [32];
  undefined4 *local_1e50;
  undefined8 local_1e48;
  ulong local_1e40;
  undefined8 local_1e38;
  undefined8 local_1e30;
  undefined8 local_1e28;
  uint local_1e20 [5];
  uint local_1e0c [27];
  uint *local_1da0;
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
  undefined8 local_1558;
  ulong local_1550;
  undefined8 local_1548;
  undefined8 local_1540;
  undefined8 local_1538;
  undefined4 local_1530 [32];
  undefined4 *local_14b0;
  String local_14a8 [176];
  String local_13f8 [176];
  undefined8 local_1348;
  ulong local_1340;
  undefined8 local_1338;
  undefined8 local_1330;
  undefined8 local_1328;
  undefined4 local_1320 [32];
  undefined4 *local_12a0;
  undefined8 local_1298;
  ulong local_1290;
  undefined8 local_1288;
  undefined8 local_1280;
  undefined8 local_1278;
  uint local_1270 [5];
  uint local_125c [27];
  uint *local_11f0;
  undefined8 local_11e8;
  ulong local_11e0;
  undefined8 local_11d8;
  undefined8 local_11d0;
  undefined8 local_11c8;
  undefined4 local_11c0 [32];
  undefined4 *local_1140;
  undefined8 local_1138;
  ulong local_1130;
  undefined8 local_1128;
  undefined8 local_1120;
  undefined8 local_1118;
  uint local_1110 [5];
  uint local_10fc [27];
  uint *local_1090;
  undefined8 local_1088;
  ulong local_1080;
  undefined8 local_1078;
  undefined8 local_1070;
  undefined8 local_1068;
  uint local_1060 [5];
  uint local_104c [27];
  uint *local_fe0;
  String local_fd8 [176];
  undefined8 local_f28;
  ulong local_f20;
  undefined8 local_f18;
  undefined8 local_f10;
  undefined8 local_f08;
  uint local_f00 [13];
  uint local_ecc [19];
  uint *local_e80;
  undefined8 local_e78;
  ulong local_e70;
  undefined8 local_e68;
  undefined8 local_e60;
  undefined8 local_e58;
  uint local_e50 [5];
  uint local_e3c [27];
  uint *local_dd0;
  String local_dc8 [176];
  undefined8 local_d18;
  ulong local_d10;
  undefined8 local_d08;
  undefined8 local_d00;
  undefined8 local_cf8;
  uint local_cf0 [12];
  uint local_cc0 [20];
  uint *local_c70;
  undefined8 local_c68;
  ulong local_c60;
  undefined8 local_c58;
  undefined8 local_c50;
  undefined8 local_c48;
  uint local_c40 [5];
  uint local_c2c [27];
  uint *local_bc0;
  String local_bb8 [176];
  undefined8 local_b08;
  ulong local_b00;
  undefined8 local_af8;
  undefined8 local_af0;
  undefined8 local_ae8;
  uint local_ae0 [12];
  uint local_ab0 [20];
  uint *local_a60;
  undefined8 local_a58;
  ulong local_a50;
  undefined8 local_a48;
  undefined8 local_a40;
  undefined8 local_a38;
  undefined4 local_a30 [32];
  undefined4 *local_9b0;
  undefined8 local_9a8;
  ulong local_9a0;
  undefined8 local_998;
  undefined8 local_990;
  undefined8 local_988;
  uint local_980 [5];
  uint local_96c [27];
  uint *local_900;
  undefined8 local_8f8;
  ulong local_8f0;
  undefined8 local_8e8;
  undefined8 local_8e0;
  undefined8 local_8d8;
  uint local_8d0 [5];
  uint local_8bc [27];
  uint *local_850;
  String local_848 [176];
  undefined8 local_798;
  ulong local_790;
  undefined8 local_788;
  undefined8 local_780;
  undefined8 local_778;
  uint local_770 [12];
  uint local_740 [20];
  uint *local_6f0;
  undefined8 local_6e8;
  ulong local_6e0;
  undefined8 local_6d8;
  undefined8 local_6d0;
  undefined8 local_6c8;
  undefined4 local_6c0 [32];
  undefined4 *local_640;
  undefined8 local_638;
  ulong local_630;
  undefined8 local_628;
  undefined8 local_620;
  undefined8 local_618;
  uint local_610 [5];
  uint local_5fc [27];
  uint *local_590;
  String local_588 [176];
  String local_4d8 [176];
  String local_428 [176];
  undefined8 local_378;
  ulong local_370;
  undefined8 local_368;
  undefined8 local_360;
  undefined8 local_358;
  uint local_350 [5];
  uint local_33c [27];
  uint *local_2d0;
  String local_2c8 [176];
  undefined8 local_218;
  ulong local_210;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  uint local_1f0 [13];
  uint local_1bc [19];
  uint *local_170;
  UVector2 local_168;
  UVector2 local_158;
  UVector2 local_148;
  UVector2 local_138;
  UVector2 local_128;
  UVector2 local_118;
  UVector2 local_108;
  UVector2 local_f8;
  UVector2 local_e8;
  uchar *local_d8 [2];
  long local_c8 [2];
  uchar *local_b8 [2];
  long local_a8 [2];
  wstring local_98 [2];
  long local_88 [2];
  wstring local_78 [2];
  long local_68 [2];
  wstring local_58 [5];
  
  if (((this->m_pOwner != (CCharacter *)0x0) && (this->m_bOpenPartial != false)) &&
     (this_00 = *(CInventory **)(this->m_pOwner->m_CharacterData448 + 0x48),
     this_00 != (CInventory *)0x0)) {
    while( true ) {
      pvVar11 = this->m_pUnknown30;
      if (*(long *)((long)pvVar11 + 0x80) - (long)*(undefined8 **)((long)pvVar11 + 0x78) >> 3 == 0)
      break;
      CEGUI::Window::removeChildWindow(pvVar11,(void *)**(undefined8 **)((long)pvVar11 + 0x78));
    }
    lVar18 = 0;
    do {
      while ((pvVar11 = *(void **)((long)&this->m_pUnknown1378 + lVar18), pvVar11 != (void *)0x0 &&
             (*(long *)((long)pvVar11 + 0x80) - (long)*(undefined8 **)((long)pvVar11 + 0x78) >> 3 !=
              0))) {
        lVar18 = lVar18 + 8;
        CEGUI::Window::removeChildWindow(pvVar11,(void *)**(undefined8 **)((long)pvVar11 + 0x78));
        if (lVar18 == 0x60) goto LAB_00ba2760;
      }
      lVar18 = lVar18 + 8;
    } while (lVar18 != 0x60);
LAB_00ba2760:
    uVar21 = 0;
    pCVar19 = this;
    do {
      while (pCVar19->m_pUnknown1378 == (void *)0x0) {
LAB_00ba313c:
        uVar21 = uVar21 + 1;
        pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
        if (uVar21 == 0xc) goto LAB_00ba3150;
      }
      lVar18 = CInventory::getEquipmentRefInSlot(this_00,uVar21);
      if (lVar18 == 0) {
        if (pCVar19->m_pUnknown1378 != (void *)0x0) {
          local_1550 = 0x20;
          local_1548 = 0;
          local_1538 = 0;
          local_1540 = 0;
          local_14b0 = (undefined4 *)0x0;
          local_1558 = 0;
          local_1530[0] = 0;
          CEGUI::String::grow((String *)&local_1558,0);
          puVar15 = local_1530;
          if (0x20 < local_1550) {
            puVar15 = local_14b0;
          }
          local_1558 = 0;
          *puVar15 = 0;
                    /* try { // try from 00ba2fa0 to 00ba2fa4 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::String(local_14a8,"Image");
                    /* try { // try from 00ba2fb7 to 00ba2fbb has its CatchHandler @ 00ba4ebd */
          CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1608,local_14a8,&local_1558);
                    /* try { // try from 00ba2fbf to 00ba2fc3 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::~String(local_14a8);
          CEGUI::String::~String((String *)&local_1558);
          CEGUI::String::String(local_16b8,"");
                    /* try { // try from 00ba2ff6 to 00ba2ffa has its CatchHandler @ 00ba4eca */
          CEGUI::String::String(local_1608,"Image");
                    /* try { // try from 00ba3008 to 00ba300c has its CatchHandler @ 00ba4ecf */
          CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,local_1608,local_16b8);
                    /* try { // try from 00ba3010 to 00ba3014 has its CatchHandler @ 00ba4eca */
          CEGUI::String::~String(local_1608);
          CEGUI::String::~String(local_16b8);
          CEGUI::Window::getSize(&local_158,pCVar19->m_pUnknown1378);
                    /* try { // try from 00ba303e to 00ba3042 has its CatchHandler @ 00ba4ed5 */
          CEGUI::Window::setSize((void *)pCVar19->m_iUnknown1B28,&local_158);
          CEGUI::String::String(local_1818,"");
                    /* try { // try from 00ba3068 to 00ba306c has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::String(local_1768,"Image");
                    /* try { // try from 00ba307a to 00ba307e has its CatchHandler @ 00ba4ef5 */
          CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1898,local_1768,local_1818);
                    /* try { // try from 00ba3082 to 00ba3086 has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::~String(local_1768);
          CEGUI::String::~String(local_1818);
          CEGUI::Window::getSize(&local_168,pCVar19->m_pUnknown1378);
                    /* try { // try from 00ba30b0 to 00ba30b4 has its CatchHandler @ 00ba4f05 */
          CEGUI::Window::setSize((void *)pCVar19->m_iUnknown1898,&local_168);
          puVar12 = CEGUI::String::build_utf8_buff
                              ((String *)(&this->m_Unknown58A8 + (ulong)uVar21 * 0x16));
          CEGUI::String::String(local_18c8,puVar12);
                    /* try { // try from 00ba30ef to 00ba30f3 has its CatchHandler @ 00ba4f15 */
          CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1378,local_18c8);
          CEGUI::String::~String(local_18c8);
          CEGUI::String::String(local_1978,"Image");
                    /* try { // try from 00ba312f to 00ba3133 has its CatchHandler @ 00ba4f2d */
          CEGUI::PropertySet::setProperty
                    (pCVar19->m_pUnknown1378,local_1978,&this->m_Unknown2048 + (ulong)uVar21 * 0x16)
          ;
          CEGUI::String::~String(local_1978);
        }
        goto LAB_00ba313c;
      }
      pCVar23 = *(CEquipment **)(lVar18 + 0x10);
      local_22b8 = pCVar23->m_pIconWindow;
      if (local_22b8 == (void *)0x0) {
        CEquipment::createIcon(pCVar23,this->m_pGameUI,false);
        local_22b8 = pCVar23->m_pIconWindow;
        if (local_22b8 != (void *)0x0) {
          CEGUI::EventSet::setMutedState((void *)((long)local_22b8 + 0x38),true);
          *(undefined1 *)((long)local_22b8 + 0x3e2) = 1;
          goto LAB_00ba2806;
        }
      }
      else {
LAB_00ba2806:
        if (*(void **)((long)local_22b8 + 0xb0) != (void *)0x0) {
          CEGUI::Window::removeChildWindow(*(void **)((long)local_22b8 + 0xb0),local_22b8);
        }
        CEGUI::Window::addChildWindow(pCVar19->m_pUnknown1378,local_22b8);
      }
      pUVar8 = CEGUI::Window::getPosition(pCVar19->m_pUnknown1378);
      fVar29 = (pUVar8->d_x).d_scale * 0.0;
      uVar24 = -(uint)(0.0 < fVar29);
      fVar27 = (pUVar8->d_x).d_offset;
      pUVar8 = CEGUI::Window::getPosition(pCVar19->m_pUnknown1378);
      fVar30 = (pUVar8->d_y).d_scale * 0.0;
      uVar25 = -(uint)(0.0 < fVar30);
      fVar28 = (pUVar8->d_y).d_offset;
      if (((pCVar23->m_bUnknown348 == false) || (pCVar23->m_iSocketCount == 0)) ||
         (bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar19->m_pUnknown1378 + 0xb0),false),
         !bVar5)) {
        local_6e0 = 0x20;
        local_6d8 = 0;
        local_6c8 = 0;
        local_6d0 = 0;
        local_640 = (undefined4 *)0x0;
        local_6e8 = 0;
        local_6c0[0] = 0;
        CEGUI::String::grow((String *)&local_6e8,0);
        local_6e8 = 0;
        puVar15 = local_6c0;
        if (0x20 < local_6e0) {
          puVar15 = local_640;
        }
        *puVar15 = 0;
        local_630 = 0x20;
        local_628 = 0;
        local_618 = 0;
        local_620 = 0;
        local_590 = (uint *)0x0;
        local_638 = 0;
        local_610[0] = 0;
                    /* try { // try from 00ba29d1 to 00ba29d5 has its CatchHandler @ 00ba4d59 */
        CEGUI::String::grow((String *)&local_638,5);
        puVar16 = local_590;
        if (local_630 < 0x21) {
          puVar16 = local_610;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_638 = 5;
        puVar16 = local_5fc;
        if (0x20 < local_630) {
          puVar16 = local_590 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2a5a to 00ba2a5e has its CatchHandler @ 00ba4d34 */
        CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,&local_638,&local_6e8);
                    /* try { // try from 00ba2a67 to 00ba2a6b has its CatchHandler @ 00ba4d59 */
        CEGUI::String::~String((String *)&local_638);
        CEGUI::String::~String((String *)&local_6e8);
      }
      else {
        if (pCVar23->m_iSocketCount < 2) {
          if (pCVar23->m_iSocketCount == 1) {
            CEGUI::String::String(local_428,"onesocketglow");
                    /* try { // try from 00ba4967 to 00ba497e has its CatchHandler @ 00ba5118 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,local_428);
            CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_4d8,pvVar11);
                    /* try { // try from 00ba498f to 00ba4993 has its CatchHandler @ 00ba5130 */
            CEGUI::String::String(local_588,"Image");
                    /* try { // try from 00ba49a1 to 00ba49a5 has its CatchHandler @ 00ba513d */
            CEGUI::PropertySet::setProperty((void *)pCVar19->m_iUnknown1B28,local_588,local_4d8);
                    /* try { // try from 00ba49a9 to 00ba49ad has its CatchHandler @ 00ba5130 */
            CEGUI::String::~String(local_588);
                    /* try { // try from 00ba49b1 to 00ba49b5 has its CatchHandler @ 00ba5118 */
            CEGUI::String::~String(local_4d8);
            CEGUI::String::~String(local_428);
          }
        }
        else {
          local_210 = 0x20;
          local_208 = 0;
          local_1f8 = 0;
          local_200 = 0;
          local_170 = (uint *)0x0;
          local_218 = 0;
          local_1f0[0] = 0;
          CEGUI::String::grow((String *)&local_218,0xd);
          puVar16 = local_1f0;
          if (0x20 < local_210) {
            puVar16 = local_170;
          }
          pcVar10 = "twosocketglow";
          do {
            bVar4 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while ((byte *)pcVar10 != (byte *)0xfe60d0);
          local_218 = 0xd;
          puVar16 = local_1bc;
          if (0x20 < local_210) {
            puVar16 = local_170 + 0xd;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba442d to 00ba4441 has its CatchHandler @ 00ba50d8 */
          pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,(String *)&local_218);
          CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_2c8,pvVar11);
          local_370 = 0x20;
          local_368 = 0;
          local_358 = 0;
          local_360 = 0;
          local_2d0 = (uint *)0x0;
          local_378 = 0;
          local_350[0] = 0;
                    /* try { // try from 00ba44a5 to 00ba44a9 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::grow((String *)&local_378,5);
          puVar16 = local_350;
          if (0x20 < local_370) {
            puVar16 = local_2d0;
          }
          pbVar9 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar9 != (byte *)0xfd0c12);
          local_378 = 5;
          puVar16 = local_33c;
          if (0x20 < local_370) {
            puVar16 = local_2d0 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba4524 to 00ba4528 has its CatchHandler @ 00ba510b */
          CEGUI::PropertySet::setProperty
                    ((void *)pCVar19->m_iUnknown1B28,(String *)&local_378,local_2c8);
                    /* try { // try from 00ba452c to 00ba4530 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::~String((String *)&local_378);
                    /* try { // try from 00ba4539 to 00ba453d has its CatchHandler @ 00ba50d8 */
          CEGUI::String::~String(local_2c8);
          CEGUI::String::~String((String *)&local_218);
        }
        CEGUI::Window::moveToFront((void *)pCVar19->m_iUnknown1B28);
      }
      if (pCVar23->m_bUnknown348 == false) {
        pSVar22 = (String *)&local_798;
        local_790 = 0x20;
        local_788 = 0;
        local_778 = 0;
        local_780 = 0;
        local_6f0 = (uint *)0x0;
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
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfef79d);
        local_798 = 0xc;
        puVar16 = local_740;
        if (0x20 < local_790) {
          puVar16 = local_6f0 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2b5d to 00ba2b71 has its CatchHandler @ 00ba4d84 */
        pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar22);
        CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_848,pvVar11);
        local_8f0 = 0x20;
        local_8e8 = 0;
        local_8d8 = 0;
        local_8e0 = 0;
        local_850 = (uint *)0x0;
        local_8f8 = 0;
        local_8d0[0] = 0;
                    /* try { // try from 00ba2bd5 to 00ba2bd9 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::grow((String *)&local_8f8,5);
        puVar16 = local_8d0;
        if (0x20 < local_8f0) {
          puVar16 = local_850;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_8f8 = 5;
        puVar16 = local_8bc;
        if (0x20 < local_8f0) {
          puVar16 = local_850 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2c54 to 00ba2c58 has its CatchHandler @ 00ba4d62 */
        CEGUI::PropertySet::setProperty
                  ((void *)pCVar19->m_iUnknown1608,(String *)&local_8f8,local_848);
                    /* try { // try from 00ba2c5c to 00ba2c60 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::~String((String *)&local_8f8);
                    /* try { // try from 00ba2c69 to 00ba2c6d has its CatchHandler @ 00ba4d84 */
        CEGUI::String::~String(local_848);
      }
      else {
        pSVar22 = (String *)&local_a58;
        local_a50 = 0x20;
        local_a48 = 0;
        local_a38 = 0;
        local_a40 = 0;
        local_9b0 = (undefined4 *)0x0;
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
        local_998 = 0;
        local_988 = 0;
        local_990 = 0;
        local_900 = (uint *)0x0;
        local_9a8 = 0;
        local_980[0] = 0;
                    /* try { // try from 00ba410b to 00ba410f has its CatchHandler @ 00ba4d06 */
        CEGUI::String::grow((String *)&local_9a8,5);
        puVar16 = local_980;
        if (0x20 < local_9a0) {
          puVar16 = local_900;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_9a8 = 5;
        puVar16 = local_96c;
        if (0x20 < local_9a0) {
          puVar16 = local_900 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba417f to 00ba4183 has its CatchHandler @ 00ba4cd2 */
        CEGUI::PropertySet::setProperty
                  ((void *)pCVar19->m_iUnknown1608,(String *)&local_9a8,pSVar22);
                    /* try { // try from 00ba4187 to 00ba418b has its CatchHandler @ 00ba4d06 */
        CEGUI::String::~String((String *)&local_9a8);
      }
      CEGUI::String::~String(pSVar22);
      fVar28 = (float)(int)(fVar30 + (float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000)) + fVar28;
      if (1 < pCVar23->m_iSocketCount) {
        CEGUI::Window::getSize(&local_e8,pCVar19->m_pUnknown1378);
        uVar25 = -(uint)(0.0 < local_e8.d_y.d_scale * 0.0);
        fVar28 = ((float)(int)((float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000) +
                              local_e8.d_y.d_scale * 0.0) + local_e8.d_y.d_offset) * -0.19 + fVar28;
      }
      bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar19->m_pUnknown1378 + 0xb0),false);
      if ((bVar5) && ((pCVar23->m_SocketedEquipment).m_nCount != 0)) {
        uVar25 = 0;
        do {
          if (uVar25 < (pCVar23->m_SocketedEquipment).m_nCapacity) {
            this_01 = (pCVar23->m_SocketedEquipment).m_pData[uVar25];
            pvVar11 = this_01->m_pIconWindow;
            if (pvVar11 != (void *)0x0) goto LAB_00ba2d5a;
LAB_00ba2eb2:
            CEquipment::createIcon(this_01,this->m_pGameUI,false);
            pvVar11 = this_01->m_pIconWindow;
            if (pvVar11 != (void *)0x0) {
              CEGUI::EventSet::setMutedState((void *)((long)pvVar11 + 0x38),true);
              *(undefined1 *)((long)pvVar11 + 0x3e2) = 1;
              goto LAB_00ba2d5a;
            }
          }
          else {
            this_01 = *(pCVar23->m_SocketedEquipment).m_pData;
            pvVar11 = this_01->m_pIconWindow;
            if (pvVar11 == (void *)0x0) goto LAB_00ba2eb2;
LAB_00ba2d5a:
            if (*(void **)((long)pvVar11 + 0xb0) != (void *)0x0) {
              CEGUI::Window::removeChildWindow(*(void **)((long)pvVar11 + 0xb0),pvVar11);
            }
            bVar5 = CEGUI::Window::isChild(this->m_pUnknown30,pvVar11);
            if (bVar5) {
              if (pvVar11 == (void *)0x0) goto LAB_00ba2e05;
            }
            else {
              CEGUI::Window::addChildWindow(this->m_pUnknown30,pvVar11);
            }
            local_f8.d_x.d_scale = 0.0;
            local_f8.d_y.d_scale = 0.0;
            local_f8.d_x.d_offset =
                 (float)(int)((float)(~uVar24 & 0xbf000000 | uVar24 & 0x3f000000) + fVar29) + fVar27
            ;
            local_f8.d_y.d_offset = fVar28;
                    /* try { // try from 00ba2dcd to 00ba2dd1 has its CatchHandler @ 00ba4d5e */
            CEGUI::Window::setPosition(pvVar11,&local_f8);
            CEGUI::Window::getSize(&local_108,pCVar19->m_pUnknown1378);
                    /* try { // try from 00ba2df1 to 00ba2df5 has its CatchHandler @ 00ba4d2a */
            CEGUI::Window::setSize(pvVar11,&local_108);
            CEGUI::Window::moveToFront(pvVar11);
            *(undefined1 *)((long)pvVar11 + 0x3e2) = 1;
          }
LAB_00ba2e05:
          uVar25 = uVar25 + 1;
          CEGUI::Window::getSize(&local_118,pCVar19->m_pUnknown1378);
          uVar26 = -(uint)(0.0 < local_118.d_y.d_scale * 0.0);
          if ((pCVar23->m_SocketedEquipment).m_nCount <= uVar25) break;
          fVar28 = ((float)(int)((float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000) +
                                local_118.d_y.d_scale * 0.0) + local_118.d_y.d_offset) * 0.4 +
                   fVar28;
        } while( true );
      }
      bVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar23,0x36);
      if (bVar5) {
        pSVar22 = (String *)&local_b08;
        local_b00 = 0x20;
        local_af8 = 0;
        local_ae8 = 0;
        local_af0 = 0;
        local_a60 = (uint *)0x0;
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
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe60a7);
        local_b08 = 0xc;
        puVar16 = local_ab0;
        if (0x20 < local_b00) {
          puVar16 = local_a60 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba39ed to 00ba3a04 has its CatchHandler @ 00ba4d8b */
        pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar22);
        CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_bb8,pvVar11);
        local_c60 = 0x20;
        local_c58 = 0;
        local_c48 = 0;
        local_c50 = 0;
        local_bc0 = (uint *)0x0;
        local_c68 = 0;
        local_c40[0] = 0;
                    /* try { // try from 00ba3a68 to 00ba3a6c has its CatchHandler @ 00ba4e0f */
        CEGUI::String::grow((String *)&local_c68,5);
        puVar16 = local_c40;
        if (0x20 < local_c60) {
          puVar16 = local_bc0;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_c68 = 5;
        puVar16 = local_c2c;
        if (0x20 < local_c60) {
          puVar16 = local_bc0 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba3adf to 00ba3ae3 has its CatchHandler @ 00ba4df7 */
        CEGUI::PropertySet::setProperty
                  ((void *)pCVar19->m_iUnknown1898,(String *)&local_c68,local_bb8);
                    /* try { // try from 00ba3ae7 to 00ba3aeb has its CatchHandler @ 00ba4e0f */
        CEGUI::String::~String((String *)&local_c68);
                    /* try { // try from 00ba3aef to 00ba3af3 has its CatchHandler @ 00ba4d8b */
        CEGUI::String::~String(local_bb8);
      }
      else {
        cVar6 = (*pCVar23->_vptr->isMagical)(pCVar23);
        if (cVar6 == '\0') {
          pSVar22 = (String *)&local_11e8;
          local_11e0 = 0x20;
          local_11d8 = 0;
          local_11c8 = 0;
          local_11d0 = 0;
          local_1140 = (undefined4 *)0x0;
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
          local_1128 = 0;
          local_1118 = 0;
          local_1120 = 0;
          local_1090 = (uint *)0x0;
          local_1138 = 0;
          local_1110[0] = 0;
                    /* try { // try from 00ba4299 to 00ba429d has its CatchHandler @ 00ba4d86 */
          CEGUI::String::grow((String *)&local_1138,5);
          puVar16 = local_1110;
          if (0x20 < local_1130) {
            puVar16 = local_1090;
          }
          pbVar9 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar9 != (byte *)0xfd0c12);
          local_1138 = 5;
          puVar16 = local_10fc;
          if (0x20 < local_1130) {
            puVar16 = local_1090 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba430f to 00ba4313 has its CatchHandler @ 00ba4d32 */
          CEGUI::PropertySet::setProperty
                    ((void *)pCVar19->m_iUnknown1898,(String *)&local_1138,pSVar22);
                    /* try { // try from 00ba4317 to 00ba431b has its CatchHandler @ 00ba4d86 */
          CEGUI::String::~String((String *)&local_1138);
        }
        else {
          bVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar23,0x37);
          if (bVar5) {
            pSVar22 = (String *)&local_d18;
            local_d10 = 0x20;
            local_d08 = 0;
            local_cf8 = 0;
            local_d00 = 0;
            local_c70 = (uint *)0x0;
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
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar10 != (byte *)0xfe60b4);
            local_d18 = 0xc;
            puVar16 = local_cc0;
            if (0x20 < local_d10) {
              puVar16 = local_c70 + 0xc;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3f0d to 00ba3f24 has its CatchHandler @ 00ba4f55 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar22);
            CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_dc8,pvVar11);
            local_e70 = 0x20;
            local_e68 = 0;
            local_e58 = 0;
            local_e60 = 0;
            local_dd0 = (uint *)0x0;
            local_e78 = 0;
            local_e50[0] = 0;
                    /* try { // try from 00ba3f88 to 00ba3f8c has its CatchHandler @ 00ba4f65 */
            CEGUI::String::grow((String *)&local_e78,5);
            puVar16 = local_e50;
            if (0x20 < local_e70) {
              puVar16 = local_dd0;
            }
            pbVar9 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar9 != (byte *)0xfd0c12);
            local_e78 = 5;
            puVar16 = local_e3c;
            if (0x20 < local_e70) {
              puVar16 = local_dd0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3fff to 00ba4003 has its CatchHandler @ 00ba4f75 */
            CEGUI::PropertySet::setProperty
                      ((void *)pCVar19->m_iUnknown1898,(String *)&local_e78,local_dc8);
                    /* try { // try from 00ba4007 to 00ba400b has its CatchHandler @ 00ba4f65 */
            CEGUI::String::~String((String *)&local_e78);
                    /* try { // try from 00ba400f to 00ba4013 has its CatchHandler @ 00ba4f55 */
            CEGUI::String::~String(local_dc8);
          }
          else {
            pSVar22 = (String *)&local_f28;
            local_f20 = 0x20;
            local_f18 = 0;
            local_f08 = 0;
            local_f10 = 0;
            local_e80 = (uint *)0x0;
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
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar10 != (byte *)0xfe60c2);
            local_f28 = 0xd;
            puVar16 = local_ecc;
            if (0x20 < local_f20) {
              puVar16 = local_e80 + 0xd;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba463d to 00ba4654 has its CatchHandler @ 00ba4f32 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar22);
            CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_fd8,pvVar11);
            local_1080 = 0x20;
            local_1078 = 0;
            local_1068 = 0;
            local_1070 = 0;
            local_fe0 = (uint *)0x0;
            local_1088 = 0;
            local_1060[0] = 0;
                    /* try { // try from 00ba46b8 to 00ba46bc has its CatchHandler @ 00ba4f37 */
            CEGUI::String::grow((String *)&local_1088,5);
            puVar16 = local_1060;
            if (0x20 < local_1080) {
              puVar16 = local_fe0;
            }
            pbVar9 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar9 != (byte *)0xfd0c12);
            local_1088 = 5;
            puVar16 = local_104c;
            if (0x20 < local_1080) {
              puVar16 = local_fe0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba472f to 00ba4733 has its CatchHandler @ 00ba4f45 */
            CEGUI::PropertySet::setProperty
                      ((void *)pCVar19->m_iUnknown1898,(String *)&local_1088,local_fd8);
                    /* try { // try from 00ba4737 to 00ba473b has its CatchHandler @ 00ba4f37 */
            CEGUI::String::~String((String *)&local_1088);
                    /* try { // try from 00ba473f to 00ba4743 has its CatchHandler @ 00ba4f32 */
            CEGUI::String::~String(local_fd8);
          }
        }
      }
      CEGUI::String::~String(pSVar22);
      local_1340 = 0x20;
      local_1338 = 0;
      local_1328 = 0;
      local_1330 = 0;
      local_12a0 = (undefined4 *)0x0;
      local_1348 = 0;
      local_1320[0] = 0;
      CEGUI::String::grow((String *)&local_1348,0);
      puVar15 = local_1320;
      if (0x20 < local_1340) {
        puVar15 = local_12a0;
      }
      local_1348 = 0;
      *puVar15 = 0;
      local_1290 = 0x20;
      local_1288 = 0;
      local_1278 = 0;
      local_1280 = 0;
      local_11f0 = (uint *)0x0;
      local_1298 = 0;
      local_1270[0] = 0;
                    /* try { // try from 00ba3be7 to 00ba3beb has its CatchHandler @ 00ba4df2 */
      CEGUI::String::grow((String *)&local_1298,5);
      puVar16 = local_11f0;
      if (local_1290 < 0x21) {
        puVar16 = local_1270;
      }
      pbVar9 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1298 = 5;
      puVar16 = local_125c;
      if (0x20 < local_1290) {
        puVar16 = local_11f0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3c6a to 00ba3c6e has its CatchHandler @ 00ba4dcd */
      CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1378,&local_1298,&local_1348);
                    /* try { // try from 00ba3c77 to 00ba3c7b has its CatchHandler @ 00ba4df2 */
      CEGUI::String::~String((String *)&local_1298);
      CEGUI::String::~String((String *)&local_1348);
      if (local_22b8 != (void *)0x0) {
        local_128.d_x.d_offset = 0.0;
        local_128.d_x.d_scale = 0.0;
        local_128.d_y.d_offset = 1.0;
        local_128.d_y.d_scale = 0.0;
                    /* try { // try from 00ba3cce to 00ba3cd2 has its CatchHandler @ 00ba4d28 */
        CEGUI::Window::setPosition(local_22b8,&local_128);
        local_138.d_x.d_offset = 0.0;
        local_138.d_x.d_scale = 0.0;
        local_138.d_y.d_offset = 0.0;
        local_138.d_y.d_scale = 0.0;
                    /* try { // try from 00ba3d0c to 00ba3d10 has its CatchHandler @ 00ba4d26 */
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
                    /* try { // try from 00ba3d9d to 00ba3dbd has its CatchHandler @ 00ba4d1e */
        CEGUI::Window::setSize(local_22b8,&local_148);
        CEGUI::Window::moveToFront(local_22b8);
        CEGUI::Window::update(local_22b8,0.001);
      }
      CEGUI::String::String(local_13f8,"");
                    /* try { // try from 00ba3ddd to 00ba3de1 has its CatchHandler @ 00ba4d0b */
      CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1378,local_13f8);
      pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
      CEGUI::String::~String(local_13f8);
      uVar21 = uVar21 + 1;
    } while (uVar21 != 0xc);
LAB_00ba3150:
    uVar21 = 0;
    pCVar19 = this;
    do {
      if (pCVar19->m_pUnknown1040 != (void *)0x0) {
        if ((updateLayout()::g_RemoveASpell == '\0') &&
           (iVar7 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar7 != 0)) {
          updateLayout()::g_RemoveASpell = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell);
          __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell + -0x18) == 0) {
          pCVar13 = CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString(local_58,pCVar13,L"Hold [CTRL] and left-click to");
                    /* try { // try from 00ba4a6f to 00ba4a73 has its CatchHandler @ 00ba514a */
          STRINGS::StringConvertToNarrow((STRINGS *)local_68,local_58[0]._M_p);
                    /* try { // try from 00ba4a7c to 00ba4a80 has its CatchHandler @ 00ba5162 */
          std::string::assign((string *)&updateLayout()::g_RemoveASpell);
          if ((allocator *)(local_68[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_68[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
            }
          }
          if ((allocator *)(local_58[0]._M_p + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_58[0]._M_p + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0]._M_p + -6));
            }
          }
        }
        if ((updateLayout()::g_RemoveASpell2 == '\0') &&
           (iVar7 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar7 != 0)) {
          updateLayout()::g_RemoveASpell2 = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell2);
          __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell2,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell2 + -0x18) == 0) {
          pCVar13 = CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString(local_78,pCVar13,L"un-learn this spell");
                    /* try { // try from 00ba4bd6 to 00ba4bda has its CatchHandler @ 00ba4c76 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_88,local_78[0]._M_p);
                    /* try { // try from 00ba4be3 to 00ba4be7 has its CatchHandler @ 00ba4c99 */
          std::string::assign((string *)&updateLayout()::g_RemoveASpell2);
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_88[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
          if ((allocator *)(local_78[0]._M_p + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_78[0]._M_p + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0]._M_p + -6));
            }
          }
        }
        if ((updateLayout()::g_DragASpell == '\0') &&
           (iVar7 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar7 != 0)) {
          updateLayout()::g_DragASpell = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_DragASpell);
          __cxa_atexit(std::string::~string,&updateLayout()::g_DragASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_DragASpell + -0x18) == 0) {
          pCVar13 = CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString(local_98,pCVar13,L"Drag a spell here to learn it");
                    /* try { // try from 00ba3201 to 00ba3205 has its CatchHandler @ 00ba4f85 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_a8,local_98[0]._M_p);
                    /* try { // try from 00ba320e to 00ba3212 has its CatchHandler @ 00ba4f9d */
          std::string::assign((string *)&updateLayout()::g_DragASpell);
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_a8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
          if ((allocator *)(local_98[0]._M_p + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_98[0]._M_p + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0]._M_p + -6));
            }
          }
        }
        this_02 = (CSkill *)CCharacter::getKnownSpell(this->m_pOwner,uVar21);
        if ((this_02 == (CSkill *)0x0) ||
           (plVar14 = (long *)CSkill::getSkillIcon(this_02), *(long *)(*plVar14 + -0x18) == 0)) {
          CEGUI::String::String(local_1ce8,"");
                    /* try { // try from 00ba32b0 to 00ba32b4 has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::String(local_1c38,"Image");
                    /* try { // try from 00ba32cc to 00ba32d0 has its CatchHandler @ 00ba4e7b */
          CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1040,local_1c38,local_1ce8);
                    /* try { // try from 00ba32d9 to 00ba32dd has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::~String(local_1c38);
          CEGUI::String::~String(local_1ce8);
          *(longlong **)((long)pCVar19->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1368;
          CEGUI::String::String(local_1d98,updateLayout()::g_DragASpell);
                    /* try { // try from 00ba3321 to 00ba3325 has its CatchHandler @ 00ba4e63 */
          CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1040,local_1d98);
          CEGUI::String::~String(local_1d98);
        }
        else {
          puVar17 = (undefined8 *)CSkill::getSkillIcon(this_02);
          STRINGS::StringConvertToNarrow((STRINGS *)local_b8,(wchar_t *)*puVar17);
                    /* try { // try from 00ba47d1 to 00ba47e5 has its CatchHandler @ 00ba4ffb */
          pvVar11 = CGameUI::getImageFromImageSet(this->m_pGameUI,local_b8[0]);
          CEGUI::PropertyHelper::imageToString((undefined1 (*) [176])local_1a28,pvVar11);
                    /* try { // try from 00ba47f3 to 00ba47f7 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::String(local_1ad8,"Image");
                    /* try { // try from 00ba480f to 00ba4813 has its CatchHandler @ 00ba500b */
          CEGUI::PropertySet::setProperty(pCVar19->m_pUnknown1040,local_1ad8,local_1a28);
                    /* try { // try from 00ba481c to 00ba4820 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::~String(local_1ad8);
                    /* try { // try from 00ba4829 to 00ba482d has its CatchHandler @ 00ba4ffb */
          CEGUI::String::~String(local_1a28);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
          pCVar19->m_Unknown1050 = *(longlong *)(this_02->m_SkillData148 + 8);
          *(longlong **)((long)pCVar19->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1050 + uVar21;
          std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);
                    /* try { // try from 00ba4888 to 00ba488c has its CatchHandler @ 00ba5057 */
          std::string::append((char *)local_c8,0xfa04e8);
                    /* try { // try from 00ba489d to 00ba48a1 has its CatchHandler @ 00ba5075 */
          std::operator+((string *)local_d8,(string *)local_c8);
                    /* try { // try from 00ba48b2 to 00ba48b6 has its CatchHandler @ 00ba5088 */
          CEGUI::String::String(local_1b88,local_d8[0]);
                    /* try { // try from 00ba48c6 to 00ba48ca has its CatchHandler @ 00ba509a */
          CEGUI::Window::setTooltipText(pCVar19->m_pUnknown1040,local_1b88);
                    /* try { // try from 00ba48d3 to 00ba48d7 has its CatchHandler @ 00ba5088 */
          CEGUI::String::~String(local_1b88);
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
        }
      }
      uVar21 = uVar21 + 1;
      pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
    } while (uVar21 != 2);
    local_22c8 = 0x13;
    pCVar19 = this;
    do {
      local_1ef0 = 0x20;
      local_1ee8 = 0;
      local_1ed8 = 0;
      local_1ee0 = 0;
      local_1e50 = (undefined4 *)0x0;
      local_1ef8 = 0;
      local_1ed0[0] = 0;
      CEGUI::String::grow((String *)&local_1ef8,0);
      puVar15 = local_1ed0;
      if (0x20 < local_1ef0) {
        puVar15 = local_1e50;
      }
      local_1ef8 = 0;
      *puVar15 = 0;
      local_1e40 = 0x20;
      local_1e38 = 0;
      local_1e28 = 0;
      local_1e30 = 0;
      local_1da0 = (uint *)0x0;
      local_1e48 = 0;
      local_1e20[0] = 0;
                    /* try { // try from 00ba3496 to 00ba349a has its CatchHandler @ 00ba4e5e */
      CEGUI::String::grow((String *)&local_1e48,5);
      puVar16 = local_1e20;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0;
      }
      pbVar9 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1e48 = 5;
      puVar16 = local_1e0c;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3514 to 00ba3518 has its CatchHandler @ 00ba4e3e */
      CEGUI::PropertySet::setProperty
                ((void *)pCVar19->m_iUnknown1930,(String *)&local_1e48,&local_1ef8);
                    /* try { // try from 00ba351c to 00ba3520 has its CatchHandler @ 00ba4e5e */
      CEGUI::String::~String((String *)&local_1e48);
      CEGUI::String::~String((String *)&local_1ef8);
      local_2050 = 0x20;
      local_2048 = 0;
      local_2038 = 0;
      local_2040 = 0;
      local_1fb0 = (undefined4 *)0x0;
      local_2058 = 0;
      local_2030[0] = 0;
      CEGUI::String::grow((String *)&local_2058,0);
      puVar15 = local_2030;
      if (0x20 < local_2050) {
        puVar15 = local_1fb0;
      }
      local_2058 = 0;
      *puVar15 = 0;
      local_1fa0 = 0x20;
      local_1f98 = 0;
      local_1f88 = 0;
      local_1f90 = 0;
      local_1f00 = (uint *)0x0;
      local_1fa8 = 0;
      local_1f80[0] = 0;
                    /* try { // try from 00ba3614 to 00ba3618 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::grow((String *)&local_1fa8,5);
      pbVar9 = (byte *)0xfd0c0d;
      puVar16 = local_1f80;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00;
      }
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1fa8 = 5;
      puVar16 = local_1f6c;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3689 to 00ba368d has its CatchHandler @ 00ba4e19 */
      CEGUI::PropertySet::setProperty
                ((void *)pCVar19->m_iUnknown1BC0,(String *)&local_1fa8,&local_2058);
                    /* try { // try from 00ba3691 to 00ba3695 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::~String((String *)&local_1fa8);
      CEGUI::String::~String((String *)&local_2058);
      local_21b0 = 0x20;
      local_21a8 = 0;
      local_2198 = 0;
      local_21a0 = 0;
      local_2110 = (undefined4 *)0x0;
      local_21b8 = 0;
      local_2190[0] = 0;
      CEGUI::String::grow((String *)&local_21b8,0);
      puVar15 = local_2190;
      if (0x20 < local_21b0) {
        puVar15 = local_2110;
      }
      local_21b8 = 0;
      *puVar15 = 0;
      local_2100 = 0x20;
      local_20f8 = 0;
      local_20e8 = 0;
      local_20f0 = 0;
      local_2060 = (uint *)0x0;
      local_2108 = 0;
      local_20e0[0] = 0;
                    /* try { // try from 00ba3789 to 00ba378d has its CatchHandler @ 00ba4e14 */
      CEGUI::String::grow((String *)&local_2108,5);
      pbVar9 = (byte *)0xfd0c0d;
      puVar16 = local_20e0;
      if (0x20 < local_2100) {
        puVar16 = local_2060;
      }
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_2108 = 5;
      puVar16 = local_20cc;
      if (0x20 < local_2100) {
        puVar16 = local_2060 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3802 to 00ba3806 has its CatchHandler @ 00ba4dad */
      CEGUI::PropertySet::setProperty
                ((void *)pCVar19->m_iUnknown16A0,(String *)&local_2108,&local_21b8);
                    /* try { // try from 00ba380a to 00ba380e has its CatchHandler @ 00ba4e14 */
      CEGUI::String::~String((String *)&local_2108);
      CEGUI::String::~String((String *)&local_21b8);
      if (pCVar19->m_pUnknown1E50 != (void *)0x0) {
        CEGUI::String::String(local_2268,"");
                    /* try { // try from 00ba3847 to 00ba384b has its CatchHandler @ 00ba4d95 */
        CEGUI::Window::setText(pCVar19->m_pUnknown1E50,local_2268);
        CEGUI::String::~String(local_2268);
      }
      pvVar11 = pCVar19->m_pUnknown1410;
      if (*(long *)((long)pvVar11 + 0x80) - (long)*(undefined8 **)((long)pvVar11 + 0x78) >> 3 != 0)
      {
        CEGUI::Window::removeChildWindow(pvVar11,(void *)**(undefined8 **)((long)pvVar11 + 0x78));
      }
      local_22c8 = local_22c8 + 1;
      pCVar19 = (CPetMenu *)&pCVar19->m_pSafePointers;
    } while (local_22c8 != 0x52);
    if (*(int *)(this_00->m_Unknown30 + 8) != 0) {
      uVar20 = 0;
      do {
        uVar21 = (uint)uVar20;
        if (uVar21 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
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
          if (uVar21 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
            plVar14 = (long *)(uVar20 * 8 + *(long *)this_00->m_Unknown30);
          }
          iVar7 = CInventory::getItemPane(this_00,*(uint *)(*plVar14 + 0x18));
          if (iVar7 == this->m_iUnknown6C) {
            if (uVar21 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
              plVar14 = (long *)(uVar20 * 8 + *(long *)this_00->m_Unknown30);
            }
            else {
              plVar14 = *(long **)this_00->m_Unknown30;
            }
            setSlotIcon(this,pCVar23,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
          }
        }
        uVar20 = (ulong)(uVar21 + 1);
      } while (uVar21 + 1 < *(uint *)(this_00->m_Unknown30 + 8));
    }
    CEGUI::Window::moveToBack(this->m_pUnknown20);
    CEGUI::Window::moveToFront(this->m_pUnknown48);
    CEGUI::Window::moveToFront(this->m_pUnknown28);
    CEGUI::Window::moveToFront(this->m_pUnknown30);
    CEGUI::Window::moveToFront(this->m_pUnknown40);
  }
  return;
}

