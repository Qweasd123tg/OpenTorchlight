
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
  Window *pWVar5;
  char cVar6;
  bool bVar7;
  int iVar8;
  float *pfVar9;
  byte *pbVar10;
  char *pcVar11;
  CEquipment *this_01;
  uchar *puVar12;
  CStringTranslate *pCVar13;
  CSkill *this_02;
  long *plVar14;
  undefined4 *puVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  UVector2 *pUVar19;
  CPetMenu *pCVar20;
  ulong uVar21;
  uint uVar22;
  String *pSVar23;
  CEquipment *pCVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  int local_22c8;
  UVector2 *local_22b8;
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
  Image local_1a28 [176];
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
  Image local_fd8 [176];
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
  Image local_dc8 [176];
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
  Image local_bb8 [176];
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
  Image local_848 [176];
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
  Image local_4d8 [176];
  String local_428 [176];
  undefined8 local_378;
  ulong local_370;
  undefined8 local_368;
  undefined8 local_360;
  undefined8 local_358;
  uint local_350 [5];
  uint local_33c [27];
  uint *local_2d0;
  Image local_2c8 [176];
  undefined8 local_218;
  ulong local_210;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  uint local_1f0 [13];
  uint local_1bc [19];
  uint *local_170;
  float local_148;
  float local_144;
  undefined4 local_140;
  float local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  float local_110;
  float local_10c;
  undefined4 local_f8;
  float local_f4;
  undefined4 local_f0;
  float local_ec;
  float local_e0;
  float local_dc;
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
    while (pWVar5 = this->m_pUnknown30,
          *(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0) {
      CEGUI::Window::removeChildWindow(pWVar5);
    }
    lVar18 = 0;
    do {
      while ((pWVar5 = *(Window **)((long)&this->m_pUnknown1378 + lVar18), pWVar5 != (Window *)0x0
             && (*(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0))) {
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
      while (pCVar20->m_pUnknown1378 == (void *)0x0) {
LAB_00ba313c:
        uVar22 = uVar22 + 1;
        pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
        if (uVar22 == 0xc) goto LAB_00ba3150;
      }
      lVar18 = CInventory::getEquipmentRefInSlot(this_00,uVar22);
      if (lVar18 == 0) {
        if (pCVar20->m_pUnknown1378 != (void *)0x0) {
          local_1550 = 0x20;
          local_1548 = 0;
          local_1538 = 0;
          local_1540 = 0;
          local_14b0 = (undefined4 *)0x0;
          local_1558 = 0;
          local_1530[0] = 0;
          CEGUI::String::grow((ulong)&local_1558);
          puVar15 = local_1530;
          if (0x20 < local_1550) {
            puVar15 = local_14b0;
          }
          local_1558 = 0;
          *puVar15 = 0;
                    /* try { // try from 00ba2fa0 to 00ba2fa4 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::String(local_14a8,"Image");
                    /* try { // try from 00ba2fb7 to 00ba2fbb has its CatchHandler @ 00ba4ebd */
          CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,local_14a8);
                    /* try { // try from 00ba2fbf to 00ba2fc3 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::~String(local_14a8);
          CEGUI::String::~String((String *)&local_1558);
          CEGUI::String::String(local_16b8,"");
                    /* try { // try from 00ba2ff6 to 00ba2ffa has its CatchHandler @ 00ba4eca */
          CEGUI::String::String(local_1608,"Image");
                    /* try { // try from 00ba3008 to 00ba300c has its CatchHandler @ 00ba4ecf */
          CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,local_1608);
                    /* try { // try from 00ba3010 to 00ba3014 has its CatchHandler @ 00ba4eca */
          CEGUI::String::~String(local_1608);
          CEGUI::String::~String(local_16b8);
          CEGUI::Window::getSize();
                    /* try { // try from 00ba303e to 00ba3042 has its CatchHandler @ 00ba4ed5 */
          CEGUI::Window::setSize((UVector2 *)pCVar20->m_iUnknown1B28);
          CEGUI::String::String(local_1818,"");
                    /* try { // try from 00ba3068 to 00ba306c has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::String(local_1768,"Image");
                    /* try { // try from 00ba307a to 00ba307e has its CatchHandler @ 00ba4ef5 */
          CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,local_1768);
                    /* try { // try from 00ba3082 to 00ba3086 has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::~String(local_1768);
          CEGUI::String::~String(local_1818);
          CEGUI::Window::getSize();
                    /* try { // try from 00ba30b0 to 00ba30b4 has its CatchHandler @ 00ba4f05 */
          CEGUI::Window::setSize((UVector2 *)pCVar20->m_iUnknown1898);
          puVar12 = (uchar *)CEGUI::String::build_utf8_buff();
          CEGUI::String::String(local_18c8,puVar12);
                    /* try { // try from 00ba30ef to 00ba30f3 has its CatchHandler @ 00ba4f15 */
          CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1378);
          CEGUI::String::~String(local_18c8);
          CEGUI::String::String(local_1978,"Image");
                    /* try { // try from 00ba312f to 00ba3133 has its CatchHandler @ 00ba4f2d */
          CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1378,local_1978);
          CEGUI::String::~String(local_1978);
        }
        goto LAB_00ba313c;
      }
      pCVar24 = *(CEquipment **)(lVar18 + 0x10);
      local_22b8 = pCVar24->m_pIconWindow;
      if (local_22b8 == (UVector2 *)0x0) {
        CEquipment::createIcon(pCVar24,this->m_pGameUI,false);
        local_22b8 = pCVar24->m_pIconWindow;
        if (local_22b8 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)local_22b8 + '8'));
          local_22b8[0x3e2] = (UVector2)0x1;
          goto LAB_00ba2806;
        }
      }
      else {
LAB_00ba2806:
        if (*(Window **)(local_22b8 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(local_22b8 + 0xb0));
        }
        CEGUI::Window::addChildWindow(pCVar20->m_pUnknown1378);
      }
      pfVar9 = (float *)CEGUI::Window::getPosition();
      fVar28 = *pfVar9;
      uVar25 = -(uint)(0.0 < fVar28 * 0.0);
      fVar30 = pfVar9[1];
      lVar18 = CEGUI::Window::getPosition();
      fVar31 = *(float *)(lVar18 + 8) * 0.0;
      uVar26 = -(uint)(0.0 < fVar31);
      fVar29 = *(float *)(lVar18 + 0xc);
      if (((pCVar24->m_bUnknown348 == false) || (pCVar24->m_iSocketCount == 0)) ||
         (cVar6 = CEGUI::Window::isVisible
                            (SUB81(*(undefined8 *)((long)pCVar20->m_pUnknown1378 + 0xb0),0)),
         cVar6 == '\0')) {
        local_6e0 = 0x20;
        local_6d8 = 0;
        local_6c8 = 0;
        local_6d0 = 0;
        local_640 = (undefined4 *)0x0;
        local_6e8 = 0;
        local_6c0[0] = 0;
        CEGUI::String::grow((ulong)&local_6e8);
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
        CEGUI::String::grow((ulong)&local_638);
        puVar16 = local_590;
        if (local_630 < 0x21) {
          puVar16 = local_610;
        }
        pbVar10 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar10 != (byte *)0xfd0c12);
        local_638 = 5;
        puVar16 = local_5fc;
        if (0x20 < local_630) {
          puVar16 = local_590 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2a5a to 00ba2a5e has its CatchHandler @ 00ba4d34 */
        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,(String *)&local_638);
                    /* try { // try from 00ba2a67 to 00ba2a6b has its CatchHandler @ 00ba4d59 */
        CEGUI::String::~String((String *)&local_638);
        CEGUI::String::~String((String *)&local_6e8);
      }
      else {
        if (pCVar24->m_iSocketCount < 2) {
          if (pCVar24->m_iSocketCount == 1) {
            CEGUI::String::String(local_428,"onesocketglow");
                    /* try { // try from 00ba4967 to 00ba497e has its CatchHandler @ 00ba5118 */
            CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
            CEGUI::PropertyHelper::imageToString(local_4d8);
                    /* try { // try from 00ba498f to 00ba4993 has its CatchHandler @ 00ba5130 */
            CEGUI::String::String(local_588,"Image");
                    /* try { // try from 00ba49a1 to 00ba49a5 has its CatchHandler @ 00ba513d */
            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,local_588);
                    /* try { // try from 00ba49a9 to 00ba49ad has its CatchHandler @ 00ba5130 */
            CEGUI::String::~String(local_588);
                    /* try { // try from 00ba49b1 to 00ba49b5 has its CatchHandler @ 00ba5118 */
            CEGUI::String::~String((String *)local_4d8);
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
          CEGUI::String::grow((ulong)&local_218);
          puVar16 = local_1f0;
          if (0x20 < local_210) {
            puVar16 = local_170;
          }
          pcVar11 = "twosocketglow";
          do {
            bVar4 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while ((byte *)pcVar11 != (byte *)0xfe60d0);
          local_218 = 0xd;
          puVar16 = local_1bc;
          if (0x20 < local_210) {
            puVar16 = local_170 + 0xd;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba442d to 00ba4441 has its CatchHandler @ 00ba50d8 */
          CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
          CEGUI::PropertyHelper::imageToString(local_2c8);
          local_370 = 0x20;
          local_368 = 0;
          local_358 = 0;
          local_360 = 0;
          local_2d0 = (uint *)0x0;
          local_378 = 0;
          local_350[0] = 0;
                    /* try { // try from 00ba44a5 to 00ba44a9 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::grow((ulong)&local_378);
          puVar16 = local_350;
          if (0x20 < local_370) {
            puVar16 = local_2d0;
          }
          pbVar10 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar10 != (byte *)0xfd0c12);
          local_378 = 5;
          puVar16 = local_33c;
          if (0x20 < local_370) {
            puVar16 = local_2d0 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba4524 to 00ba4528 has its CatchHandler @ 00ba510b */
          CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1B28,(String *)&local_378);
                    /* try { // try from 00ba452c to 00ba4530 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::~String((String *)&local_378);
                    /* try { // try from 00ba4539 to 00ba453d has its CatchHandler @ 00ba50d8 */
          CEGUI::String::~String((String *)local_2c8);
          CEGUI::String::~String((String *)&local_218);
        }
        CEGUI::Window::moveToFront();
      }
      if (pCVar24->m_bUnknown348 == false) {
        pSVar23 = (String *)&local_798;
        local_790 = 0x20;
        local_788 = 0;
        local_778 = 0;
        local_780 = 0;
        local_6f0 = (uint *)0x0;
        local_798 = 0;
        local_770[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
        puVar16 = local_770;
        if (0x20 < local_790) {
          puVar16 = local_6f0;
        }
        pcVar11 = "unidentified";
        do {
          bVar4 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar11 != (byte *)0xfef79d);
        local_798 = 0xc;
        puVar16 = local_740;
        if (0x20 < local_790) {
          puVar16 = local_6f0 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2b5d to 00ba2b71 has its CatchHandler @ 00ba4d84 */
        CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
        CEGUI::PropertyHelper::imageToString(local_848);
        local_8f0 = 0x20;
        local_8e8 = 0;
        local_8d8 = 0;
        local_8e0 = 0;
        local_850 = (uint *)0x0;
        local_8f8 = 0;
        local_8d0[0] = 0;
                    /* try { // try from 00ba2bd5 to 00ba2bd9 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::grow((ulong)&local_8f8);
        puVar16 = local_8d0;
        if (0x20 < local_8f0) {
          puVar16 = local_850;
        }
        pbVar10 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar10 != (byte *)0xfd0c12);
        local_8f8 = 5;
        puVar16 = local_8bc;
        if (0x20 < local_8f0) {
          puVar16 = local_850 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2c54 to 00ba2c58 has its CatchHandler @ 00ba4d62 */
        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,(String *)&local_8f8);
                    /* try { // try from 00ba2c5c to 00ba2c60 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::~String((String *)&local_8f8);
                    /* try { // try from 00ba2c69 to 00ba2c6d has its CatchHandler @ 00ba4d84 */
        CEGUI::String::~String((String *)local_848);
      }
      else {
        pSVar23 = (String *)&local_a58;
        local_a50 = 0x20;
        local_a48 = 0;
        local_a38 = 0;
        local_a40 = 0;
        local_9b0 = (undefined4 *)0x0;
        local_a58 = 0;
        local_a30[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
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
        CEGUI::String::grow((ulong)&local_9a8);
        puVar16 = local_980;
        if (0x20 < local_9a0) {
          puVar16 = local_900;
        }
        pbVar10 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar10 != (byte *)0xfd0c12);
        local_9a8 = 5;
        puVar16 = local_96c;
        if (0x20 < local_9a0) {
          puVar16 = local_900 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba417f to 00ba4183 has its CatchHandler @ 00ba4cd2 */
        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1608,(String *)&local_9a8);
                    /* try { // try from 00ba4187 to 00ba418b has its CatchHandler @ 00ba4d06 */
        CEGUI::String::~String((String *)&local_9a8);
      }
      CEGUI::String::~String(pSVar23);
      fVar29 = (float)(int)(fVar31 + (float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000)) + fVar29;
      if (1 < pCVar24->m_iSocketCount) {
        CEGUI::Window::getSize();
        uVar26 = -(uint)(0.0 < local_e0 * 0.0);
        fVar29 = ((float)(int)((float)(~uVar26 & 0xbf000000 | uVar26 & 0x3f000000) + local_e0 * 0.0)
                 + local_dc) * -0.19 + fVar29;
      }
      cVar6 = CEGUI::Window::isVisible
                        (SUB81(*(undefined8 *)((long)pCVar20->m_pUnknown1378 + 0xb0),0));
      if ((cVar6 != '\0') && ((pCVar24->m_SocketedEquipment).m_nCount != 0)) {
        uVar26 = 0;
        do {
          if (uVar26 < (pCVar24->m_SocketedEquipment).m_nCapacity) {
            this_01 = (pCVar24->m_SocketedEquipment).m_pData[uVar26];
            pUVar19 = this_01->m_pIconWindow;
            if (pUVar19 != (UVector2 *)0x0) goto LAB_00ba2d5a;
LAB_00ba2eb2:
            CEquipment::createIcon(this_01,this->m_pGameUI,false);
            pUVar19 = this_01->m_pIconWindow;
            if (pUVar19 != (UVector2 *)0x0) {
              CEGUI::EventSet::setMutedState((bool)((char)pUVar19 + '8'));
              pUVar19[0x3e2] = (UVector2)0x1;
              goto LAB_00ba2d5a;
            }
          }
          else {
            this_01 = *(pCVar24->m_SocketedEquipment).m_pData;
            pUVar19 = this_01->m_pIconWindow;
            if (pUVar19 == (UVector2 *)0x0) goto LAB_00ba2eb2;
LAB_00ba2d5a:
            if (*(Window **)(pUVar19 + 0xb0) != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(*(Window **)(pUVar19 + 0xb0));
            }
            cVar6 = CEGUI::Window::isChild(this->m_pUnknown30);
            if (cVar6 == '\0') {
              CEGUI::Window::addChildWindow(this->m_pUnknown30);
            }
            else if (pUVar19 == (UVector2 *)0x0) goto LAB_00ba2e05;
            local_f8 = 0;
            local_f0 = 0;
            local_f4 = (float)(int)((float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000) +
                                   fVar28 * 0.0) + fVar30;
            local_ec = fVar29;
                    /* try { // try from 00ba2dcd to 00ba2dd1 has its CatchHandler @ 00ba4d5e */
            CEGUI::Window::setPosition(pUVar19);
            CEGUI::Window::getSize();
                    /* try { // try from 00ba2df1 to 00ba2df5 has its CatchHandler @ 00ba4d2a */
            CEGUI::Window::setSize(pUVar19);
            CEGUI::Window::moveToFront();
            pUVar19[0x3e2] = (UVector2)0x1;
          }
LAB_00ba2e05:
          uVar26 = uVar26 + 1;
          CEGUI::Window::getSize();
          uVar27 = -(uint)(0.0 < local_110 * 0.0);
          if ((pCVar24->m_SocketedEquipment).m_nCount <= uVar26) break;
          fVar29 = ((float)(int)((float)(~uVar27 & 0xbf000000 | uVar27 & 0x3f000000) +
                                local_110 * 0.0) + local_10c) * 0.4 + fVar29;
        } while( true );
      }
      bVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar24,0x36);
      if (bVar7) {
        pSVar23 = (String *)&local_b08;
        local_b00 = 0x20;
        local_af8 = 0;
        local_ae8 = 0;
        local_af0 = 0;
        local_a60 = (uint *)0x0;
        local_b08 = 0;
        local_ae0[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
        puVar16 = local_ae0;
        if (0x20 < local_b00) {
          puVar16 = local_a60;
        }
        pcVar11 = "goldslotglow";
        do {
          bVar4 = *pcVar11;
          pcVar11 = pcVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar11 != (byte *)0xfe60a7);
        local_b08 = 0xc;
        puVar16 = local_ab0;
        if (0x20 < local_b00) {
          puVar16 = local_a60 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba39ed to 00ba3a04 has its CatchHandler @ 00ba4d8b */
        CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
        CEGUI::PropertyHelper::imageToString(local_bb8);
        local_c60 = 0x20;
        local_c58 = 0;
        local_c48 = 0;
        local_c50 = 0;
        local_bc0 = (uint *)0x0;
        local_c68 = 0;
        local_c40[0] = 0;
                    /* try { // try from 00ba3a68 to 00ba3a6c has its CatchHandler @ 00ba4e0f */
        CEGUI::String::grow((ulong)&local_c68);
        puVar16 = local_c40;
        if (0x20 < local_c60) {
          puVar16 = local_bc0;
        }
        pbVar10 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar10 != (byte *)0xfd0c12);
        local_c68 = 5;
        puVar16 = local_c2c;
        if (0x20 < local_c60) {
          puVar16 = local_bc0 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba3adf to 00ba3ae3 has its CatchHandler @ 00ba4df7 */
        CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_c68);
                    /* try { // try from 00ba3ae7 to 00ba3aeb has its CatchHandler @ 00ba4e0f */
        CEGUI::String::~String((String *)&local_c68);
                    /* try { // try from 00ba3aef to 00ba3af3 has its CatchHandler @ 00ba4d8b */
        CEGUI::String::~String((String *)local_bb8);
      }
      else {
        cVar6 = (*pCVar24->_vptr->isMagical)(pCVar24);
        if (cVar6 == '\0') {
          pSVar23 = (String *)&local_11e8;
          local_11e0 = 0x20;
          local_11d8 = 0;
          local_11c8 = 0;
          local_11d0 = 0;
          local_1140 = (undefined4 *)0x0;
          local_11e8 = 0;
          local_11c0[0] = 0;
          CEGUI::String::grow((ulong)pSVar23);
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
          CEGUI::String::grow((ulong)&local_1138);
          puVar16 = local_1110;
          if (0x20 < local_1130) {
            puVar16 = local_1090;
          }
          pbVar10 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar10 != (byte *)0xfd0c12);
          local_1138 = 5;
          puVar16 = local_10fc;
          if (0x20 < local_1130) {
            puVar16 = local_1090 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba430f to 00ba4313 has its CatchHandler @ 00ba4d32 */
          CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_1138);
                    /* try { // try from 00ba4317 to 00ba431b has its CatchHandler @ 00ba4d86 */
          CEGUI::String::~String((String *)&local_1138);
        }
        else {
          bVar7 = CBaseUnit::ISA((CBaseUnit *)pCVar24,0x37);
          if (bVar7) {
            pSVar23 = (String *)&local_d18;
            local_d10 = 0x20;
            local_d08 = 0;
            local_cf8 = 0;
            local_d00 = 0;
            local_c70 = (uint *)0x0;
            local_d18 = 0;
            local_cf0[0] = 0;
            CEGUI::String::grow((ulong)pSVar23);
            puVar16 = local_cf0;
            if (0x20 < local_d10) {
              puVar16 = local_c70;
            }
            pcVar11 = "blueslotglow";
            do {
              bVar4 = *pcVar11;
              pcVar11 = pcVar11 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar11 != (byte *)0xfe60b4);
            local_d18 = 0xc;
            puVar16 = local_cc0;
            if (0x20 < local_d10) {
              puVar16 = local_c70 + 0xc;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3f0d to 00ba3f24 has its CatchHandler @ 00ba4f55 */
            CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
            CEGUI::PropertyHelper::imageToString(local_dc8);
            local_e70 = 0x20;
            local_e68 = 0;
            local_e58 = 0;
            local_e60 = 0;
            local_dd0 = (uint *)0x0;
            local_e78 = 0;
            local_e50[0] = 0;
                    /* try { // try from 00ba3f88 to 00ba3f8c has its CatchHandler @ 00ba4f65 */
            CEGUI::String::grow((ulong)&local_e78);
            puVar16 = local_e50;
            if (0x20 < local_e70) {
              puVar16 = local_dd0;
            }
            pbVar10 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar10;
              pbVar10 = pbVar10 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar10 != (byte *)0xfd0c12);
            local_e78 = 5;
            puVar16 = local_e3c;
            if (0x20 < local_e70) {
              puVar16 = local_dd0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3fff to 00ba4003 has its CatchHandler @ 00ba4f75 */
            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_e78);
                    /* try { // try from 00ba4007 to 00ba400b has its CatchHandler @ 00ba4f65 */
            CEGUI::String::~String((String *)&local_e78);
                    /* try { // try from 00ba400f to 00ba4013 has its CatchHandler @ 00ba4f55 */
            CEGUI::String::~String((String *)local_dc8);
          }
          else {
            pSVar23 = (String *)&local_f28;
            local_f20 = 0x20;
            local_f18 = 0;
            local_f08 = 0;
            local_f10 = 0;
            local_e80 = (uint *)0x0;
            local_f28 = 0;
            local_f00[0] = 0;
            CEGUI::String::grow((ulong)pSVar23);
            puVar16 = local_f00;
            if (0x20 < local_f20) {
              puVar16 = local_e80;
            }
            pcVar11 = "greenslotglow";
            do {
              bVar4 = *pcVar11;
              pcVar11 = pcVar11 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar11 != (byte *)0xfe60c2);
            local_f28 = 0xd;
            puVar16 = local_ecc;
            if (0x20 < local_f20) {
              puVar16 = local_e80 + 0xd;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba463d to 00ba4654 has its CatchHandler @ 00ba4f32 */
            CEGUI::Imageset::getImage((String *)this->m_iUnknown9108);
            CEGUI::PropertyHelper::imageToString(local_fd8);
            local_1080 = 0x20;
            local_1078 = 0;
            local_1068 = 0;
            local_1070 = 0;
            local_fe0 = (uint *)0x0;
            local_1088 = 0;
            local_1060[0] = 0;
                    /* try { // try from 00ba46b8 to 00ba46bc has its CatchHandler @ 00ba4f37 */
            CEGUI::String::grow((ulong)&local_1088);
            puVar16 = local_1060;
            if (0x20 < local_1080) {
              puVar16 = local_fe0;
            }
            pbVar10 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar10;
              pbVar10 = pbVar10 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar10 != (byte *)0xfd0c12);
            local_1088 = 5;
            puVar16 = local_104c;
            if (0x20 < local_1080) {
              puVar16 = local_fe0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba472f to 00ba4733 has its CatchHandler @ 00ba4f45 */
            CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1898,(String *)&local_1088)
            ;
                    /* try { // try from 00ba4737 to 00ba473b has its CatchHandler @ 00ba4f37 */
            CEGUI::String::~String((String *)&local_1088);
                    /* try { // try from 00ba473f to 00ba4743 has its CatchHandler @ 00ba4f32 */
            CEGUI::String::~String((String *)local_fd8);
          }
        }
      }
      CEGUI::String::~String(pSVar23);
      local_1340 = 0x20;
      local_1338 = 0;
      local_1328 = 0;
      local_1330 = 0;
      local_12a0 = (undefined4 *)0x0;
      local_1348 = 0;
      local_1320[0] = 0;
      CEGUI::String::grow((ulong)&local_1348);
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
      CEGUI::String::grow((ulong)&local_1298);
      puVar16 = local_11f0;
      if (local_1290 < 0x21) {
        puVar16 = local_1270;
      }
      pbVar10 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar10 != (byte *)0xfd0c12);
      local_1298 = 5;
      puVar16 = local_125c;
      if (0x20 < local_1290) {
        puVar16 = local_11f0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3c6a to 00ba3c6e has its CatchHandler @ 00ba4dcd */
      CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1378,(String *)&local_1298);
                    /* try { // try from 00ba3c77 to 00ba3c7b has its CatchHandler @ 00ba4df2 */
      CEGUI::String::~String((String *)&local_1298);
      CEGUI::String::~String((String *)&local_1348);
      if (local_22b8 != (UVector2 *)0x0) {
        local_124 = 0;
        local_128 = 0;
        local_11c = 0x3f800000;
        local_120 = 0;
                    /* try { // try from 00ba3cce to 00ba3cd2 has its CatchHandler @ 00ba4d28 */
        CEGUI::Window::setPosition(local_22b8);
        local_134 = 0;
        local_138 = 0;
        local_12c = 0;
        local_130 = 0;
                    /* try { // try from 00ba3d0c to 00ba3d10 has its CatchHandler @ 00ba4d26 */
        CEGUI::Window::setPosition(local_22b8);
        CEGUI::Window::getSize();
        fVar28 = local_148 * 0.0;
        if (0.0 < fVar28) {
          fVar30 = 0.5;
        }
        else {
          fVar30 = -0.5;
        }
        local_140 = 0;
        local_148 = 0.0;
        local_144 = (float)(int)(fVar28 + fVar30) + local_144;
        local_13c = local_144 * 1.5;
                    /* try { // try from 00ba3d9d to 00ba3dbd has its CatchHandler @ 00ba4d1e */
        CEGUI::Window::setSize(local_22b8);
        CEGUI::Window::moveToFront();
        CEGUI::Window::update(0.001);
      }
      CEGUI::String::String(local_13f8,"");
                    /* try { // try from 00ba3ddd to 00ba3de1 has its CatchHandler @ 00ba4d0b */
      CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1378);
      pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
      CEGUI::String::~String(local_13f8);
      uVar22 = uVar22 + 1;
    } while (uVar22 != 0xc);
LAB_00ba3150:
    uVar22 = 0;
    pCVar20 = this;
    do {
      if (pCVar20->m_pUnknown1040 != (void *)0x0) {
        if ((updateLayout()::g_RemoveASpell == '\0') &&
           (iVar8 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar8 != 0)) {
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
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
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
           (iVar8 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar8 != 0)) {
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
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
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
           (iVar8 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar8 != 0)) {
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
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
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
        this_02 = (CSkill *)CCharacter::getKnownSpell(this->m_pOwner,uVar22);
        if ((this_02 == (CSkill *)0x0) ||
           (plVar14 = (long *)CSkill::getSkillIcon(this_02), *(long *)(*plVar14 + -0x18) == 0)) {
          CEGUI::String::String(local_1ce8,"");
                    /* try { // try from 00ba32b0 to 00ba32b4 has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::String(local_1c38,"Image");
                    /* try { // try from 00ba32cc to 00ba32d0 has its CatchHandler @ 00ba4e7b */
          CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1040,local_1c38);
                    /* try { // try from 00ba32d9 to 00ba32dd has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::~String(local_1c38);
          CEGUI::String::~String(local_1ce8);
          *(longlong **)((long)pCVar20->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1368;
          CEGUI::String::String(local_1d98,updateLayout()::g_DragASpell);
                    /* try { // try from 00ba3321 to 00ba3325 has its CatchHandler @ 00ba4e63 */
          CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1040);
          CEGUI::String::~String(local_1d98);
        }
        else {
          puVar17 = (undefined8 *)CSkill::getSkillIcon(this_02);
          STRINGS::StringConvertToNarrow((STRINGS *)local_b8,(wchar_t *)*puVar17);
                    /* try { // try from 00ba47d1 to 00ba47e5 has its CatchHandler @ 00ba4ffb */
          CGameUI::getImageFromImageSet(this->m_pGameUI,local_b8[0]);
          CEGUI::PropertyHelper::imageToString(local_1a28);
                    /* try { // try from 00ba47f3 to 00ba47f7 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::String(local_1ad8,"Image");
                    /* try { // try from 00ba480f to 00ba4813 has its CatchHandler @ 00ba500b */
          CEGUI::PropertySet::setProperty(pCVar20->m_pUnknown1040,local_1ad8);
                    /* try { // try from 00ba481c to 00ba4820 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::~String(local_1ad8);
                    /* try { // try from 00ba4829 to 00ba482d has its CatchHandler @ 00ba4ffb */
          CEGUI::String::~String((String *)local_1a28);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
          pCVar20->m_Unknown1050 = *(longlong *)(this_02->m_SkillData148 + 8);
          *(longlong **)((long)pCVar20->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1050 + uVar22;
          std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);
                    /* try { // try from 00ba4888 to 00ba488c has its CatchHandler @ 00ba5057 */
          std::string::append((char *)local_c8,0xfa04e8);
                    /* try { // try from 00ba489d to 00ba48a1 has its CatchHandler @ 00ba5075 */
          std::operator+((string *)local_d8,(string *)local_c8);
                    /* try { // try from 00ba48b2 to 00ba48b6 has its CatchHandler @ 00ba5088 */
          CEGUI::String::String(local_1b88,local_d8[0]);
                    /* try { // try from 00ba48c6 to 00ba48ca has its CatchHandler @ 00ba509a */
          CEGUI::Window::setTooltipText(pCVar20->m_pUnknown1040);
                    /* try { // try from 00ba48d3 to 00ba48d7 has its CatchHandler @ 00ba5088 */
          CEGUI::String::~String(local_1b88);
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
        }
      }
      uVar22 = uVar22 + 1;
      pCVar20 = (CPetMenu *)&pCVar20->m_pSafePointers;
    } while (uVar22 != 2);
    local_22c8 = 0x13;
    pCVar20 = this;
    do {
      local_1ef0 = 0x20;
      local_1ee8 = 0;
      local_1ed8 = 0;
      local_1ee0 = 0;
      local_1e50 = (undefined4 *)0x0;
      local_1ef8 = 0;
      local_1ed0[0] = 0;
      CEGUI::String::grow((ulong)&local_1ef8);
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
      CEGUI::String::grow((ulong)&local_1e48);
      puVar16 = local_1e20;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0;
      }
      pbVar10 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar10 != (byte *)0xfd0c12);
      local_1e48 = 5;
      puVar16 = local_1e0c;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3514 to 00ba3518 has its CatchHandler @ 00ba4e3e */
      CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1930,(String *)&local_1e48);
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
      CEGUI::String::grow((ulong)&local_2058);
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
      CEGUI::String::grow((ulong)&local_1fa8);
      pbVar10 = (byte *)0xfd0c0d;
      puVar16 = local_1f80;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00;
      }
      do {
        bVar4 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar10 != (byte *)0xfd0c12);
      local_1fa8 = 5;
      puVar16 = local_1f6c;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3689 to 00ba368d has its CatchHandler @ 00ba4e19 */
      CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown1BC0,(String *)&local_1fa8);
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
      CEGUI::String::grow((ulong)&local_21b8);
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
      CEGUI::String::grow((ulong)&local_2108);
      pbVar10 = (byte *)0xfd0c0d;
      puVar16 = local_20e0;
      if (0x20 < local_2100) {
        puVar16 = local_2060;
      }
      do {
        bVar4 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar10 != (byte *)0xfd0c12);
      local_2108 = 5;
      puVar16 = local_20cc;
      if (0x20 < local_2100) {
        puVar16 = local_2060 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3802 to 00ba3806 has its CatchHandler @ 00ba4dad */
      CEGUI::PropertySet::setProperty((String *)pCVar20->m_iUnknown16A0,(String *)&local_2108);
                    /* try { // try from 00ba380a to 00ba380e has its CatchHandler @ 00ba4e14 */
      CEGUI::String::~String((String *)&local_2108);
      CEGUI::String::~String((String *)&local_21b8);
      if (pCVar20->m_pUnknown1E50 != (void *)0x0) {
        CEGUI::String::String(local_2268,"");
                    /* try { // try from 00ba3847 to 00ba384b has its CatchHandler @ 00ba4d95 */
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
        uVar22 = (uint)uVar21;
        if (uVar22 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
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
          if (uVar22 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
            plVar14 = (long *)(uVar21 * 8 + *(long *)this_00->m_Unknown30);
          }
          iVar8 = CInventory::getItemPane(this_00,*(uint *)(*plVar14 + 0x18));
          if (iVar8 == this->m_iUnknown6C) {
            if (uVar22 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
              plVar14 = (long *)(uVar21 * 8 + *(long *)this_00->m_Unknown30);
            }
            else {
              plVar14 = *(long **)this_00->m_Unknown30;
            }
            setSlotIcon(this,pCVar24,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
          }
        }
        uVar21 = (ulong)(uVar22 + 1);
      } while (uVar22 + 1 < *(uint *)(this_00->m_Unknown30 + 8));
    }
    CEGUI::Window::moveToBack();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
  }
  return;
}

