
/* WARNING: Removing unreachable block (ram,0x00ba501d) */
/* WARNING: Removing unreachable block (ram,0x00ba50dd) */
/* WARNING: Removing unreachable block (ram,0x00ba4ced) */
/* WARNING: Removing unreachable block (ram,0x00ba4c8e) */
/* WARNING: Removing unreachable block (ram,0x00ba5000) */
/* WARNING: Removing unreachable block (ram,0x00ba516f) */
/* WARNING: Removing unreachable block (ram,0x00ba4cf8) */
/* WARNING: Removing unreachable block (ram,0x00ba506a) */
/* WARNING: Removing unreachable block (ram,0x00ba50e8) */
/* WARNING: Type propagation algorithm not settling */
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
  uint *puVar15;
  undefined8 *puVar16;
  long lVar17;
  CPetMenu *pCVar18;
  ulong uVar19;
  uint uVar20;
  String *pSVar21;
  CEquipment *pCVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  int local_22c8;
  void *local_22b8;
  String local_2268;
  String local_21b8;
  String local_2108;
  String local_2058;
  String local_1fa8;
  String local_1ef8;
  String local_1e48;
  String local_1d98;
  String local_1ce8;
  String local_1c38;
  String local_1b88;
  String local_1ad8;
  String local_1a28;
  String local_1978;
  String local_18c8;
  String local_1818;
  String local_1768;
  String local_16b8;
  String local_1608;
  String local_1558;
  String local_14a8;
  String local_13f8;
  String local_1348;
  String local_1298;
  String local_11e8;
  String local_1138;
  String local_1088;
  String local_fd8;
  String local_f28;
  String local_e78;
  String local_dc8;
  String local_d18;
  String local_c68;
  String local_bb8;
  String local_b08;
  String local_a58;
  String local_9a8;
  String local_8f8;
  String local_848;
  String local_798;
  String local_6e8;
  String local_638;
  String local_588;
  String local_4d8;
  String local_428;
  String local_378;
  String local_2c8;
  String local_218;
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
    lVar17 = 0;
    do {
      while ((pvVar11 = *(void **)((long)&this->m_pUnknown1378 + lVar17), pvVar11 != (void *)0x0 &&
             (*(long *)((long)pvVar11 + 0x80) - (long)*(undefined8 **)((long)pvVar11 + 0x78) >> 3 !=
              0))) {
        lVar17 = lVar17 + 8;
        CEGUI::Window::removeChildWindow(pvVar11,(void *)**(undefined8 **)((long)pvVar11 + 0x78));
        if (lVar17 == 0x60) goto LAB_00ba2760;
      }
      lVar17 = lVar17 + 8;
    } while (lVar17 != 0x60);
LAB_00ba2760:
    uVar20 = 0;
    pCVar18 = this;
    do {
      while (pCVar18->m_pUnknown1378 == (void *)0x0) {
LAB_00ba313c:
        uVar20 = uVar20 + 1;
        pCVar18 = (CPetMenu *)&pCVar18->m_pSafePointers;
        if (uVar20 == 0xc) goto LAB_00ba3150;
      }
      lVar17 = CInventory::getEquipmentRefInSlot(this_00,uVar20);
      if (lVar17 == 0) {
        if (pCVar18->m_pUnknown1378 != (void *)0x0) {
          local_1558.d_reserve = 0x20;
          local_1558.d_encodedbuff = (uchar *)0x0;
          local_1558.d_encodedbufflen = 0;
          local_1558.d_encodeddatlen = 0;
          local_1558.d_buffer = (uint *)0x0;
          local_1558.d_cplength = 0;
          local_1558.d_quickbuff[0] = 0;
          CEGUI::String::grow((String *)&local_1558,0);
          puVar15 = local_1558.d_quickbuff;
          if (0x20 < local_1558.d_reserve) {
            puVar15 = local_1558.d_buffer;
          }
          local_1558.d_cplength = 0;
          *puVar15 = 0;
                    /* try { // try from 00ba2fa0 to 00ba2fa4 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::String((String *)&local_14a8,"Image");
                    /* try { // try from 00ba2fb7 to 00ba2fbb has its CatchHandler @ 00ba4ebd */
          CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1608,&local_14a8,&local_1558);
                    /* try { // try from 00ba2fbf to 00ba2fc3 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::~String((String *)&local_14a8);
          CEGUI::String::~String((String *)&local_1558);
          CEGUI::String::String((String *)&local_16b8,"");
                    /* try { // try from 00ba2ff6 to 00ba2ffa has its CatchHandler @ 00ba4eca */
          CEGUI::String::String((String *)&local_1608,"Image");
                    /* try { // try from 00ba3008 to 00ba300c has its CatchHandler @ 00ba4ecf */
          CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1B28,&local_1608,&local_16b8);
                    /* try { // try from 00ba3010 to 00ba3014 has its CatchHandler @ 00ba4eca */
          CEGUI::String::~String((String *)&local_1608);
          CEGUI::String::~String((String *)&local_16b8);
          CEGUI::Window::getSize(&local_158,pCVar18->m_pUnknown1378);
                    /* try { // try from 00ba303e to 00ba3042 has its CatchHandler @ 00ba4ed5 */
          CEGUI::Window::setSize((void *)pCVar18->m_iUnknown1B28,&local_158);
          CEGUI::String::String((String *)&local_1818,"");
                    /* try { // try from 00ba3068 to 00ba306c has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::String((String *)&local_1768,"Image");
                    /* try { // try from 00ba307a to 00ba307e has its CatchHandler @ 00ba4ef5 */
          CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1898,&local_1768,&local_1818);
                    /* try { // try from 00ba3082 to 00ba3086 has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::~String((String *)&local_1768);
          CEGUI::String::~String((String *)&local_1818);
          CEGUI::Window::getSize(&local_168,pCVar18->m_pUnknown1378);
                    /* try { // try from 00ba30b0 to 00ba30b4 has its CatchHandler @ 00ba4f05 */
          CEGUI::Window::setSize((void *)pCVar18->m_iUnknown1898,&local_168);
          puVar12 = CEGUI::String::build_utf8_buff
                              ((String *)(&this->m_Unknown58A8 + (ulong)uVar20 * 0x16));
          CEGUI::String::String((String *)&local_18c8,puVar12);
                    /* try { // try from 00ba30ef to 00ba30f3 has its CatchHandler @ 00ba4f15 */
          CEGUI::Window::setTooltipText(pCVar18->m_pUnknown1378,&local_18c8);
          CEGUI::String::~String((String *)&local_18c8);
          CEGUI::String::String((String *)&local_1978,"Image");
                    /* try { // try from 00ba312f to 00ba3133 has its CatchHandler @ 00ba4f2d */
          CEGUI::PropertySet::setProperty
                    (pCVar18->m_pUnknown1378,&local_1978,
                     (String *)(&this->m_Unknown2048 + (ulong)uVar20 * 0x16));
          CEGUI::String::~String((String *)&local_1978);
        }
        goto LAB_00ba313c;
      }
      pCVar22 = *(CEquipment **)(lVar17 + 0x10);
      local_22b8 = pCVar22->m_pIconWindow;
      if (local_22b8 == (void *)0x0) {
        CEquipment::createIcon(pCVar22,this->m_pGameUI,false);
        local_22b8 = pCVar22->m_pIconWindow;
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
        CEGUI::Window::addChildWindow(pCVar18->m_pUnknown1378,local_22b8);
      }
      pUVar8 = CEGUI::Window::getPosition(pCVar18->m_pUnknown1378);
      fVar28 = (pUVar8->d_x).d_scale * 0.0;
      uVar23 = -(uint)(0.0 < fVar28);
      fVar26 = (pUVar8->d_x).d_offset;
      pUVar8 = CEGUI::Window::getPosition(pCVar18->m_pUnknown1378);
      fVar29 = (pUVar8->d_y).d_scale * 0.0;
      uVar24 = -(uint)(0.0 < fVar29);
      fVar27 = (pUVar8->d_y).d_offset;
      if (((pCVar22->m_bUnknown348 == false) || (pCVar22->m_iSocketCount == 0)) ||
         (bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar18->m_pUnknown1378 + 0xb0),false),
         !bVar5)) {
        local_6e8.d_reserve = 0x20;
        local_6e8.d_encodedbuff = (uchar *)0x0;
        local_6e8.d_encodedbufflen = 0;
        local_6e8.d_encodeddatlen = 0;
        local_6e8.d_buffer = (uint *)0x0;
        local_6e8.d_cplength = 0;
        local_6e8.d_quickbuff[0] = 0;
        CEGUI::String::grow((String *)&local_6e8,0);
        local_6e8.d_cplength = 0;
        puVar15 = local_6e8.d_quickbuff;
        if (0x20 < local_6e8.d_reserve) {
          puVar15 = local_6e8.d_buffer;
        }
        *puVar15 = 0;
        local_638.d_reserve = 0x20;
        local_638.d_encodedbuff = (uchar *)0x0;
        local_638.d_encodedbufflen = 0;
        local_638.d_encodeddatlen = 0;
        local_638.d_buffer = (uint *)0x0;
        local_638.d_cplength = 0;
        local_638.d_quickbuff[0] = 0;
                    /* try { // try from 00ba29d1 to 00ba29d5 has its CatchHandler @ 00ba4d59 */
        CEGUI::String::grow((String *)&local_638,5);
        puVar15 = local_638.d_buffer;
        if (local_638.d_reserve < 0x21) {
          puVar15 = local_638.d_quickbuff;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_638.d_cplength = 5;
        puVar15 = local_638.d_quickbuff;
        if (0x20 < local_638.d_reserve) {
          puVar15 = local_638.d_buffer;
        }
        puVar15[5] = 0;
                    /* try { // try from 00ba2a5a to 00ba2a5e has its CatchHandler @ 00ba4d34 */
        CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1B28,&local_638,&local_6e8);
                    /* try { // try from 00ba2a67 to 00ba2a6b has its CatchHandler @ 00ba4d59 */
        CEGUI::String::~String((String *)&local_638);
        CEGUI::String::~String((String *)&local_6e8);
      }
      else {
        if (pCVar22->m_iSocketCount < 2) {
          if (pCVar22->m_iSocketCount == 1) {
            CEGUI::String::String((String *)&local_428,"onesocketglow");
                    /* try { // try from 00ba4967 to 00ba497e has its CatchHandler @ 00ba5118 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,&local_428);
            CEGUI::PropertyHelper::imageToString(&local_4d8,pvVar11);
                    /* try { // try from 00ba498f to 00ba4993 has its CatchHandler @ 00ba5130 */
            CEGUI::String::String((String *)&local_588,"Image");
                    /* try { // try from 00ba49a1 to 00ba49a5 has its CatchHandler @ 00ba513d */
            CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1B28,&local_588,&local_4d8);
                    /* try { // try from 00ba49a9 to 00ba49ad has its CatchHandler @ 00ba5130 */
            CEGUI::String::~String((String *)&local_588);
                    /* try { // try from 00ba49b1 to 00ba49b5 has its CatchHandler @ 00ba5118 */
            CEGUI::String::~String((String *)&local_4d8);
            CEGUI::String::~String((String *)&local_428);
          }
        }
        else {
          local_218.d_reserve = 0x20;
          local_218.d_encodedbuff = (uchar *)0x0;
          local_218.d_encodedbufflen = 0;
          local_218.d_encodeddatlen = 0;
          local_218.d_buffer = (uint *)0x0;
          local_218.d_cplength = 0;
          local_218.d_quickbuff[0] = 0;
          CEGUI::String::grow((String *)&local_218,0xd);
          puVar15 = local_218.d_quickbuff;
          if (0x20 < local_218.d_reserve) {
            puVar15 = local_218.d_buffer;
          }
          pcVar10 = "twosocketglow";
          do {
            bVar4 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            *puVar15 = (uint)bVar4;
            puVar15 = puVar15 + 1;
          } while ((byte *)pcVar10 != (byte *)0xfe60d0);
          local_218.d_cplength = 0xd;
          puVar15 = local_218.d_quickbuff;
          if (0x20 < local_218.d_reserve) {
            puVar15 = local_218.d_buffer;
          }
          puVar15[0xd] = 0;
                    /* try { // try from 00ba442d to 00ba4441 has its CatchHandler @ 00ba50d8 */
          pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,&local_218);
          CEGUI::PropertyHelper::imageToString(&local_2c8,pvVar11);
          local_378.d_reserve = 0x20;
          local_378.d_encodedbuff = (uchar *)0x0;
          local_378.d_encodedbufflen = 0;
          local_378.d_encodeddatlen = 0;
          local_378.d_buffer = (uint *)0x0;
          local_378.d_cplength = 0;
          local_378.d_quickbuff[0] = 0;
                    /* try { // try from 00ba44a5 to 00ba44a9 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::grow((String *)&local_378,5);
          puVar15 = local_378.d_quickbuff;
          if (0x20 < local_378.d_reserve) {
            puVar15 = local_378.d_buffer;
          }
          pbVar9 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            *puVar15 = (uint)bVar4;
            puVar15 = puVar15 + 1;
          } while (pbVar9 != (byte *)0xfd0c12);
          local_378.d_cplength = 5;
          puVar15 = local_378.d_quickbuff;
          if (0x20 < local_378.d_reserve) {
            puVar15 = local_378.d_buffer;
          }
          puVar15[5] = 0;
                    /* try { // try from 00ba4524 to 00ba4528 has its CatchHandler @ 00ba510b */
          CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1B28,&local_378,&local_2c8);
                    /* try { // try from 00ba452c to 00ba4530 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::~String((String *)&local_378);
                    /* try { // try from 00ba4539 to 00ba453d has its CatchHandler @ 00ba50d8 */
          CEGUI::String::~String((String *)&local_2c8);
          CEGUI::String::~String((String *)&local_218);
        }
        CEGUI::Window::moveToFront((void *)pCVar18->m_iUnknown1B28);
      }
      if (pCVar22->m_bUnknown348 == false) {
        pSVar21 = &local_798;
        local_798.d_reserve = 0x20;
        local_798.d_encodedbuff = (uchar *)0x0;
        local_798.d_encodedbufflen = 0;
        local_798.d_encodeddatlen = 0;
        local_798.d_buffer = (uint *)0x0;
        local_798.d_cplength = 0;
        local_798.d_quickbuff[0] = 0;
        CEGUI::String::grow((String *)pSVar21,0xc);
        puVar15 = local_798.d_quickbuff;
        if (0x20 < local_798.d_reserve) {
          puVar15 = local_798.d_buffer;
        }
        pcVar10 = "unidentified";
        do {
          bVar4 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfef79d);
        local_798.d_cplength = 0xc;
        puVar15 = local_798.d_quickbuff;
        if (0x20 < local_798.d_reserve) {
          puVar15 = local_798.d_buffer;
        }
        puVar15[0xc] = 0;
                    /* try { // try from 00ba2b5d to 00ba2b71 has its CatchHandler @ 00ba4d84 */
        pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar21);
        CEGUI::PropertyHelper::imageToString(&local_848,pvVar11);
        local_8f8.d_reserve = 0x20;
        local_8f8.d_encodedbuff = (uchar *)0x0;
        local_8f8.d_encodedbufflen = 0;
        local_8f8.d_encodeddatlen = 0;
        local_8f8.d_buffer = (uint *)0x0;
        local_8f8.d_cplength = 0;
        local_8f8.d_quickbuff[0] = 0;
                    /* try { // try from 00ba2bd5 to 00ba2bd9 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::grow((String *)&local_8f8,5);
        puVar15 = local_8f8.d_quickbuff;
        if (0x20 < local_8f8.d_reserve) {
          puVar15 = local_8f8.d_buffer;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_8f8.d_cplength = 5;
        puVar15 = local_8f8.d_quickbuff;
        if (0x20 < local_8f8.d_reserve) {
          puVar15 = local_8f8.d_buffer;
        }
        puVar15[5] = 0;
                    /* try { // try from 00ba2c54 to 00ba2c58 has its CatchHandler @ 00ba4d62 */
        CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1608,&local_8f8,&local_848);
                    /* try { // try from 00ba2c5c to 00ba2c60 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::~String((String *)&local_8f8);
                    /* try { // try from 00ba2c69 to 00ba2c6d has its CatchHandler @ 00ba4d84 */
        CEGUI::String::~String((String *)&local_848);
      }
      else {
        pSVar21 = &local_a58;
        local_a58.d_reserve = 0x20;
        local_a58.d_encodedbuff = (uchar *)0x0;
        local_a58.d_encodedbufflen = 0;
        local_a58.d_encodeddatlen = 0;
        local_a58.d_buffer = (uint *)0x0;
        local_a58.d_cplength = 0;
        local_a58.d_quickbuff[0] = 0;
        CEGUI::String::grow((String *)pSVar21,0);
        local_a58.d_cplength = 0;
        puVar15 = local_a58.d_quickbuff;
        if (0x20 < local_a58.d_reserve) {
          puVar15 = local_a58.d_buffer;
        }
        *puVar15 = 0;
        local_9a8.d_reserve = 0x20;
        local_9a8.d_encodedbuff = (uchar *)0x0;
        local_9a8.d_encodedbufflen = 0;
        local_9a8.d_encodeddatlen = 0;
        local_9a8.d_buffer = (uint *)0x0;
        local_9a8.d_cplength = 0;
        local_9a8.d_quickbuff[0] = 0;
                    /* try { // try from 00ba410b to 00ba410f has its CatchHandler @ 00ba4d06 */
        CEGUI::String::grow((String *)&local_9a8,5);
        puVar15 = local_9a8.d_quickbuff;
        if (0x20 < local_9a8.d_reserve) {
          puVar15 = local_9a8.d_buffer;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_9a8.d_cplength = 5;
        puVar15 = local_9a8.d_quickbuff;
        if (0x20 < local_9a8.d_reserve) {
          puVar15 = local_9a8.d_buffer;
        }
        puVar15[5] = 0;
                    /* try { // try from 00ba417f to 00ba4183 has its CatchHandler @ 00ba4cd2 */
        CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1608,&local_9a8,pSVar21);
                    /* try { // try from 00ba4187 to 00ba418b has its CatchHandler @ 00ba4d06 */
        CEGUI::String::~String((String *)&local_9a8);
      }
      CEGUI::String::~String((String *)pSVar21);
      fVar27 = (float)(int)(fVar29 + (float)(~uVar24 & 0xbf000000 | uVar24 & 0x3f000000)) + fVar27;
      if (1 < pCVar22->m_iSocketCount) {
        CEGUI::Window::getSize(&local_e8,pCVar18->m_pUnknown1378);
        uVar24 = -(uint)(0.0 < local_e8.d_y.d_scale * 0.0);
        fVar27 = ((float)(int)((float)(~uVar24 & 0xbf000000 | uVar24 & 0x3f000000) +
                              local_e8.d_y.d_scale * 0.0) + local_e8.d_y.d_offset) * -0.19 + fVar27;
      }
      bVar5 = CEGUI::Window::isVisible(*(void **)((long)pCVar18->m_pUnknown1378 + 0xb0),false);
      if ((bVar5) && ((pCVar22->m_SocketedEquipment).m_nCount != 0)) {
        uVar24 = 0;
        do {
          if (uVar24 < (pCVar22->m_SocketedEquipment).m_nCapacity) {
            this_01 = (pCVar22->m_SocketedEquipment).m_pData[uVar24];
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
            this_01 = *(pCVar22->m_SocketedEquipment).m_pData;
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
                 (float)(int)((float)(~uVar23 & 0xbf000000 | uVar23 & 0x3f000000) + fVar28) + fVar26
            ;
            local_f8.d_y.d_offset = fVar27;
                    /* try { // try from 00ba2dcd to 00ba2dd1 has its CatchHandler @ 00ba4d5e */
            CEGUI::Window::setPosition(pvVar11,&local_f8);
            CEGUI::Window::getSize(&local_108,pCVar18->m_pUnknown1378);
                    /* try { // try from 00ba2df1 to 00ba2df5 has its CatchHandler @ 00ba4d2a */
            CEGUI::Window::setSize(pvVar11,&local_108);
            CEGUI::Window::moveToFront(pvVar11);
            *(undefined1 *)((long)pvVar11 + 0x3e2) = 1;
          }
LAB_00ba2e05:
          uVar24 = uVar24 + 1;
          CEGUI::Window::getSize(&local_118,pCVar18->m_pUnknown1378);
          uVar25 = -(uint)(0.0 < local_118.d_y.d_scale * 0.0);
          if ((pCVar22->m_SocketedEquipment).m_nCount <= uVar24) break;
          fVar27 = ((float)(int)((float)(~uVar25 & 0xbf000000 | uVar25 & 0x3f000000) +
                                local_118.d_y.d_scale * 0.0) + local_118.d_y.d_offset) * 0.4 +
                   fVar27;
        } while( true );
      }
      bVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar22,0x36);
      if (bVar5) {
        pSVar21 = &local_b08;
        local_b08.d_reserve = 0x20;
        local_b08.d_encodedbuff = (uchar *)0x0;
        local_b08.d_encodedbufflen = 0;
        local_b08.d_encodeddatlen = 0;
        local_b08.d_buffer = (uint *)0x0;
        local_b08.d_cplength = 0;
        local_b08.d_quickbuff[0] = 0;
        CEGUI::String::grow((String *)pSVar21,0xc);
        puVar15 = local_b08.d_quickbuff;
        if (0x20 < local_b08.d_reserve) {
          puVar15 = local_b08.d_buffer;
        }
        pcVar10 = "goldslotglow";
        do {
          bVar4 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe60a7);
        local_b08.d_cplength = 0xc;
        puVar15 = local_b08.d_quickbuff;
        if (0x20 < local_b08.d_reserve) {
          puVar15 = local_b08.d_buffer;
        }
        puVar15[0xc] = 0;
                    /* try { // try from 00ba39ed to 00ba3a04 has its CatchHandler @ 00ba4d8b */
        pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar21);
        CEGUI::PropertyHelper::imageToString(&local_bb8,pvVar11);
        local_c68.d_reserve = 0x20;
        local_c68.d_encodedbuff = (uchar *)0x0;
        local_c68.d_encodedbufflen = 0;
        local_c68.d_encodeddatlen = 0;
        local_c68.d_buffer = (uint *)0x0;
        local_c68.d_cplength = 0;
        local_c68.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3a68 to 00ba3a6c has its CatchHandler @ 00ba4e0f */
        CEGUI::String::grow((String *)&local_c68,5);
        puVar15 = local_c68.d_quickbuff;
        if (0x20 < local_c68.d_reserve) {
          puVar15 = local_c68.d_buffer;
        }
        pbVar9 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *puVar15 = (uint)bVar4;
          puVar15 = puVar15 + 1;
        } while (pbVar9 != (byte *)0xfd0c12);
        local_c68.d_cplength = 5;
        puVar15 = local_c68.d_quickbuff;
        if (0x20 < local_c68.d_reserve) {
          puVar15 = local_c68.d_buffer;
        }
        puVar15[5] = 0;
                    /* try { // try from 00ba3adf to 00ba3ae3 has its CatchHandler @ 00ba4df7 */
        CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1898,&local_c68,&local_bb8);
                    /* try { // try from 00ba3ae7 to 00ba3aeb has its CatchHandler @ 00ba4e0f */
        CEGUI::String::~String((String *)&local_c68);
                    /* try { // try from 00ba3aef to 00ba3af3 has its CatchHandler @ 00ba4d8b */
        CEGUI::String::~String((String *)&local_bb8);
      }
      else {
        cVar6 = (*pCVar22->_vptr->isMagical)(pCVar22);
        if (cVar6 == '\0') {
          pSVar21 = &local_11e8;
          local_11e8.d_reserve = 0x20;
          local_11e8.d_encodedbuff = (uchar *)0x0;
          local_11e8.d_encodedbufflen = 0;
          local_11e8.d_encodeddatlen = 0;
          local_11e8.d_buffer = (uint *)0x0;
          local_11e8.d_cplength = 0;
          local_11e8.d_quickbuff[0] = 0;
          CEGUI::String::grow((String *)pSVar21,0);
          local_11e8.d_cplength = 0;
          puVar15 = local_11e8.d_quickbuff;
          if (0x20 < local_11e8.d_reserve) {
            puVar15 = local_11e8.d_buffer;
          }
          *puVar15 = 0;
          local_1138.d_reserve = 0x20;
          local_1138.d_encodedbuff = (uchar *)0x0;
          local_1138.d_encodedbufflen = 0;
          local_1138.d_encodeddatlen = 0;
          local_1138.d_buffer = (uint *)0x0;
          local_1138.d_cplength = 0;
          local_1138.d_quickbuff[0] = 0;
                    /* try { // try from 00ba4299 to 00ba429d has its CatchHandler @ 00ba4d86 */
          CEGUI::String::grow((String *)&local_1138,5);
          puVar15 = local_1138.d_quickbuff;
          if (0x20 < local_1138.d_reserve) {
            puVar15 = local_1138.d_buffer;
          }
          pbVar9 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar9;
            pbVar9 = pbVar9 + 1;
            *puVar15 = (uint)bVar4;
            puVar15 = puVar15 + 1;
          } while (pbVar9 != (byte *)0xfd0c12);
          local_1138.d_cplength = 5;
          puVar15 = local_1138.d_quickbuff;
          if (0x20 < local_1138.d_reserve) {
            puVar15 = local_1138.d_buffer;
          }
          puVar15[5] = 0;
                    /* try { // try from 00ba430f to 00ba4313 has its CatchHandler @ 00ba4d32 */
          CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1898,&local_1138,pSVar21);
                    /* try { // try from 00ba4317 to 00ba431b has its CatchHandler @ 00ba4d86 */
          CEGUI::String::~String((String *)&local_1138);
        }
        else {
          bVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar22,0x37);
          if (bVar5) {
            pSVar21 = &local_d18;
            local_d18.d_reserve = 0x20;
            local_d18.d_encodedbuff = (uchar *)0x0;
            local_d18.d_encodedbufflen = 0;
            local_d18.d_encodeddatlen = 0;
            local_d18.d_buffer = (uint *)0x0;
            local_d18.d_cplength = 0;
            local_d18.d_quickbuff[0] = 0;
            CEGUI::String::grow((String *)pSVar21,0xc);
            puVar15 = local_d18.d_quickbuff;
            if (0x20 < local_d18.d_reserve) {
              puVar15 = local_d18.d_buffer;
            }
            pcVar10 = "blueslotglow";
            do {
              bVar4 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              *puVar15 = (uint)bVar4;
              puVar15 = puVar15 + 1;
            } while ((byte *)pcVar10 != (byte *)0xfe60b4);
            local_d18.d_cplength = 0xc;
            puVar15 = local_d18.d_quickbuff;
            if (0x20 < local_d18.d_reserve) {
              puVar15 = local_d18.d_buffer;
            }
            puVar15[0xc] = 0;
                    /* try { // try from 00ba3f0d to 00ba3f24 has its CatchHandler @ 00ba4f55 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar21);
            CEGUI::PropertyHelper::imageToString(&local_dc8,pvVar11);
            local_e78.d_reserve = 0x20;
            local_e78.d_encodedbuff = (uchar *)0x0;
            local_e78.d_encodedbufflen = 0;
            local_e78.d_encodeddatlen = 0;
            local_e78.d_buffer = (uint *)0x0;
            local_e78.d_cplength = 0;
            local_e78.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3f88 to 00ba3f8c has its CatchHandler @ 00ba4f65 */
            CEGUI::String::grow((String *)&local_e78,5);
            puVar15 = local_e78.d_quickbuff;
            if (0x20 < local_e78.d_reserve) {
              puVar15 = local_e78.d_buffer;
            }
            pbVar9 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              *puVar15 = (uint)bVar4;
              puVar15 = puVar15 + 1;
            } while (pbVar9 != (byte *)0xfd0c12);
            local_e78.d_cplength = 5;
            puVar15 = local_e78.d_quickbuff;
            if (0x20 < local_e78.d_reserve) {
              puVar15 = local_e78.d_buffer;
            }
            puVar15[5] = 0;
                    /* try { // try from 00ba3fff to 00ba4003 has its CatchHandler @ 00ba4f75 */
            CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1898,&local_e78,&local_dc8);
                    /* try { // try from 00ba4007 to 00ba400b has its CatchHandler @ 00ba4f65 */
            CEGUI::String::~String((String *)&local_e78);
                    /* try { // try from 00ba400f to 00ba4013 has its CatchHandler @ 00ba4f55 */
            CEGUI::String::~String((String *)&local_dc8);
          }
          else {
            pSVar21 = &local_f28;
            local_f28.d_reserve = 0x20;
            local_f28.d_encodedbuff = (uchar *)0x0;
            local_f28.d_encodedbufflen = 0;
            local_f28.d_encodeddatlen = 0;
            local_f28.d_buffer = (uint *)0x0;
            local_f28.d_cplength = 0;
            local_f28.d_quickbuff[0] = 0;
            CEGUI::String::grow((String *)pSVar21,0xd);
            puVar15 = local_f28.d_quickbuff;
            if (0x20 < local_f28.d_reserve) {
              puVar15 = local_f28.d_buffer;
            }
            pcVar10 = "greenslotglow";
            do {
              bVar4 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              *puVar15 = (uint)bVar4;
              puVar15 = puVar15 + 1;
            } while ((byte *)pcVar10 != (byte *)0xfe60c2);
            local_f28.d_cplength = 0xd;
            puVar15 = local_f28.d_quickbuff;
            if (0x20 < local_f28.d_reserve) {
              puVar15 = local_f28.d_buffer;
            }
            puVar15[0xd] = 0;
                    /* try { // try from 00ba463d to 00ba4654 has its CatchHandler @ 00ba4f32 */
            pvVar11 = CEGUI::Imageset::getImage((void *)this->m_iUnknown9108,pSVar21);
            CEGUI::PropertyHelper::imageToString(&local_fd8,pvVar11);
            local_1088.d_reserve = 0x20;
            local_1088.d_encodedbuff = (uchar *)0x0;
            local_1088.d_encodedbufflen = 0;
            local_1088.d_encodeddatlen = 0;
            local_1088.d_buffer = (uint *)0x0;
            local_1088.d_cplength = 0;
            local_1088.d_quickbuff[0] = 0;
                    /* try { // try from 00ba46b8 to 00ba46bc has its CatchHandler @ 00ba4f37 */
            CEGUI::String::grow((String *)&local_1088,5);
            puVar15 = local_1088.d_quickbuff;
            if (0x20 < local_1088.d_reserve) {
              puVar15 = local_1088.d_buffer;
            }
            pbVar9 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar9;
              pbVar9 = pbVar9 + 1;
              *puVar15 = (uint)bVar4;
              puVar15 = puVar15 + 1;
            } while (pbVar9 != (byte *)0xfd0c12);
            local_1088.d_cplength = 5;
            puVar15 = local_1088.d_quickbuff;
            if (0x20 < local_1088.d_reserve) {
              puVar15 = local_1088.d_buffer;
            }
            puVar15[5] = 0;
                    /* try { // try from 00ba472f to 00ba4733 has its CatchHandler @ 00ba4f45 */
            CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1898,&local_1088,&local_fd8);
                    /* try { // try from 00ba4737 to 00ba473b has its CatchHandler @ 00ba4f37 */
            CEGUI::String::~String((String *)&local_1088);
                    /* try { // try from 00ba473f to 00ba4743 has its CatchHandler @ 00ba4f32 */
            CEGUI::String::~String((String *)&local_fd8);
          }
        }
      }
      CEGUI::String::~String((String *)pSVar21);
      local_1348.d_reserve = 0x20;
      local_1348.d_encodedbuff = (uchar *)0x0;
      local_1348.d_encodedbufflen = 0;
      local_1348.d_encodeddatlen = 0;
      local_1348.d_buffer = (uint *)0x0;
      local_1348.d_cplength = 0;
      local_1348.d_quickbuff[0] = 0;
      CEGUI::String::grow((String *)&local_1348,0);
      puVar15 = local_1348.d_quickbuff;
      if (0x20 < local_1348.d_reserve) {
        puVar15 = local_1348.d_buffer;
      }
      local_1348.d_cplength = 0;
      *puVar15 = 0;
      local_1298.d_reserve = 0x20;
      local_1298.d_encodedbuff = (uchar *)0x0;
      local_1298.d_encodedbufflen = 0;
      local_1298.d_encodeddatlen = 0;
      local_1298.d_buffer = (uint *)0x0;
      local_1298.d_cplength = 0;
      local_1298.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3be7 to 00ba3beb has its CatchHandler @ 00ba4df2 */
      CEGUI::String::grow((String *)&local_1298,5);
      puVar15 = local_1298.d_buffer;
      if (local_1298.d_reserve < 0x21) {
        puVar15 = local_1298.d_quickbuff;
      }
      pbVar9 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar15 = (uint)bVar4;
        puVar15 = puVar15 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1298.d_cplength = 5;
      puVar15 = local_1298.d_quickbuff;
      if (0x20 < local_1298.d_reserve) {
        puVar15 = local_1298.d_buffer;
      }
      puVar15[5] = 0;
                    /* try { // try from 00ba3c6a to 00ba3c6e has its CatchHandler @ 00ba4dcd */
      CEGUI::PropertySet::setProperty(pCVar18->m_pUnknown1378,&local_1298,&local_1348);
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
        CEGUI::Window::getSize(&local_148,pCVar18->m_pUnknown1378);
        fVar26 = local_148.d_x.d_scale * 0.0;
        if (0.0 < fVar26) {
          fVar27 = 0.5;
        }
        else {
          fVar27 = -0.5;
        }
        local_148.d_y.d_scale = 0.0;
        local_148.d_x.d_scale = 0.0;
        local_148.d_x.d_offset = (float)(int)(fVar26 + fVar27) + local_148.d_x.d_offset;
        local_148.d_y.d_offset = local_148.d_x.d_offset * 1.5;
                    /* try { // try from 00ba3d9d to 00ba3dbd has its CatchHandler @ 00ba4d1e */
        CEGUI::Window::setSize(local_22b8,&local_148);
        CEGUI::Window::moveToFront(local_22b8);
        CEGUI::Window::update(local_22b8,0.001);
      }
      CEGUI::String::String((String *)&local_13f8,"");
                    /* try { // try from 00ba3ddd to 00ba3de1 has its CatchHandler @ 00ba4d0b */
      CEGUI::Window::setTooltipText(pCVar18->m_pUnknown1378,&local_13f8);
      pCVar18 = (CPetMenu *)&pCVar18->m_pSafePointers;
      CEGUI::String::~String((String *)&local_13f8);
      uVar20 = uVar20 + 1;
    } while (uVar20 != 0xc);
LAB_00ba3150:
    uVar20 = 0;
    pCVar18 = this;
    do {
      if (pCVar18->m_pUnknown1040 != (void *)0x0) {
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
        this_02 = (CSkill *)CCharacter::getKnownSpell(this->m_pOwner,uVar20);
        if ((this_02 == (CSkill *)0x0) ||
           (plVar14 = (long *)CSkill::getSkillIcon(this_02), *(long *)(*plVar14 + -0x18) == 0)) {
          CEGUI::String::String((String *)&local_1ce8,"");
                    /* try { // try from 00ba32b0 to 00ba32b4 has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::String((String *)&local_1c38,"Image");
                    /* try { // try from 00ba32cc to 00ba32d0 has its CatchHandler @ 00ba4e7b */
          CEGUI::PropertySet::setProperty(pCVar18->m_pUnknown1040,&local_1c38,&local_1ce8);
                    /* try { // try from 00ba32d9 to 00ba32dd has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::~String((String *)&local_1c38);
          CEGUI::String::~String((String *)&local_1ce8);
          *(longlong **)((long)pCVar18->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1368;
          CEGUI::String::String((String *)&local_1d98,updateLayout()::g_DragASpell);
                    /* try { // try from 00ba3321 to 00ba3325 has its CatchHandler @ 00ba4e63 */
          CEGUI::Window::setTooltipText(pCVar18->m_pUnknown1040,&local_1d98);
          CEGUI::String::~String((String *)&local_1d98);
        }
        else {
          puVar16 = (undefined8 *)CSkill::getSkillIcon(this_02);
          STRINGS::StringConvertToNarrow((STRINGS *)local_b8,(wchar_t *)*puVar16);
                    /* try { // try from 00ba47d1 to 00ba47e5 has its CatchHandler @ 00ba4ffb */
          pvVar11 = CGameUI::getImageFromImageSet(this->m_pGameUI,local_b8[0]);
          CEGUI::PropertyHelper::imageToString(&local_1a28,pvVar11);
                    /* try { // try from 00ba47f3 to 00ba47f7 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::String((String *)&local_1ad8,"Image");
                    /* try { // try from 00ba480f to 00ba4813 has its CatchHandler @ 00ba500b */
          CEGUI::PropertySet::setProperty(pCVar18->m_pUnknown1040,&local_1ad8,&local_1a28);
                    /* try { // try from 00ba481c to 00ba4820 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::~String((String *)&local_1ad8);
                    /* try { // try from 00ba4829 to 00ba482d has its CatchHandler @ 00ba4ffb */
          CEGUI::String::~String((String *)&local_1a28);
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
          pCVar18->m_Unknown1050 = *(longlong *)(this_02->m_SkillData148 + 8);
          *(longlong **)((long)pCVar18->m_pUnknown1040 + 0x1d8) = &this->m_Unknown1050 + uVar20;
          std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);
                    /* try { // try from 00ba4888 to 00ba488c has its CatchHandler @ 00ba5057 */
          std::string::append((char *)local_c8,0xfa04e8);
                    /* try { // try from 00ba489d to 00ba48a1 has its CatchHandler @ 00ba5075 */
          std::operator+((string *)local_d8,(string *)local_c8);
                    /* try { // try from 00ba48b2 to 00ba48b6 has its CatchHandler @ 00ba5088 */
          CEGUI::String::String((String *)&local_1b88,local_d8[0]);
                    /* try { // try from 00ba48c6 to 00ba48ca has its CatchHandler @ 00ba509a */
          CEGUI::Window::setTooltipText(pCVar18->m_pUnknown1040,&local_1b88);
                    /* try { // try from 00ba48d3 to 00ba48d7 has its CatchHandler @ 00ba5088 */
          CEGUI::String::~String((String *)&local_1b88);
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
      uVar20 = uVar20 + 1;
      pCVar18 = (CPetMenu *)&pCVar18->m_pSafePointers;
    } while (uVar20 != 2);
    local_22c8 = 0x13;
    pCVar18 = this;
    do {
      local_1ef8.d_reserve = 0x20;
      local_1ef8.d_encodedbuff = (uchar *)0x0;
      local_1ef8.d_encodedbufflen = 0;
      local_1ef8.d_encodeddatlen = 0;
      local_1ef8.d_buffer = (uint *)0x0;
      local_1ef8.d_cplength = 0;
      local_1ef8.d_quickbuff[0] = 0;
      CEGUI::String::grow((String *)&local_1ef8,0);
      puVar15 = local_1ef8.d_quickbuff;
      if (0x20 < local_1ef8.d_reserve) {
        puVar15 = local_1ef8.d_buffer;
      }
      local_1ef8.d_cplength = 0;
      *puVar15 = 0;
      local_1e48.d_reserve = 0x20;
      local_1e48.d_encodedbuff = (uchar *)0x0;
      local_1e48.d_encodedbufflen = 0;
      local_1e48.d_encodeddatlen = 0;
      local_1e48.d_buffer = (uint *)0x0;
      local_1e48.d_cplength = 0;
      local_1e48.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3496 to 00ba349a has its CatchHandler @ 00ba4e5e */
      CEGUI::String::grow((String *)&local_1e48,5);
      puVar15 = local_1e48.d_quickbuff;
      if (0x20 < local_1e48.d_reserve) {
        puVar15 = local_1e48.d_buffer;
      }
      pbVar9 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar15 = (uint)bVar4;
        puVar15 = puVar15 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1e48.d_cplength = 5;
      puVar15 = local_1e48.d_quickbuff;
      if (0x20 < local_1e48.d_reserve) {
        puVar15 = local_1e48.d_buffer;
      }
      puVar15[5] = 0;
                    /* try { // try from 00ba3514 to 00ba3518 has its CatchHandler @ 00ba4e3e */
      CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1930,&local_1e48,&local_1ef8);
                    /* try { // try from 00ba351c to 00ba3520 has its CatchHandler @ 00ba4e5e */
      CEGUI::String::~String((String *)&local_1e48);
      CEGUI::String::~String((String *)&local_1ef8);
      local_2058.d_reserve = 0x20;
      local_2058.d_encodedbuff = (uchar *)0x0;
      local_2058.d_encodedbufflen = 0;
      local_2058.d_encodeddatlen = 0;
      local_2058.d_buffer = (uint *)0x0;
      local_2058.d_cplength = 0;
      local_2058.d_quickbuff[0] = 0;
      CEGUI::String::grow((String *)&local_2058,0);
      puVar15 = local_2058.d_quickbuff;
      if (0x20 < local_2058.d_reserve) {
        puVar15 = local_2058.d_buffer;
      }
      local_2058.d_cplength = 0;
      *puVar15 = 0;
      local_1fa8.d_reserve = 0x20;
      local_1fa8.d_encodedbuff = (uchar *)0x0;
      local_1fa8.d_encodedbufflen = 0;
      local_1fa8.d_encodeddatlen = 0;
      local_1fa8.d_buffer = (uint *)0x0;
      local_1fa8.d_cplength = 0;
      local_1fa8.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3614 to 00ba3618 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::grow((String *)&local_1fa8,5);
      pbVar9 = (byte *)0xfd0c0d;
      puVar15 = local_1fa8.d_quickbuff;
      if (0x20 < local_1fa8.d_reserve) {
        puVar15 = local_1fa8.d_buffer;
      }
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar15 = (uint)bVar4;
        puVar15 = puVar15 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_1fa8.d_cplength = 5;
      puVar15 = local_1fa8.d_quickbuff;
      if (0x20 < local_1fa8.d_reserve) {
        puVar15 = local_1fa8.d_buffer;
      }
      puVar15[5] = 0;
                    /* try { // try from 00ba3689 to 00ba368d has its CatchHandler @ 00ba4e19 */
      CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown1BC0,&local_1fa8,&local_2058);
                    /* try { // try from 00ba3691 to 00ba3695 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::~String((String *)&local_1fa8);
      CEGUI::String::~String((String *)&local_2058);
      local_21b8.d_reserve = 0x20;
      local_21b8.d_encodedbuff = (uchar *)0x0;
      local_21b8.d_encodedbufflen = 0;
      local_21b8.d_encodeddatlen = 0;
      local_21b8.d_buffer = (uint *)0x0;
      local_21b8.d_cplength = 0;
      local_21b8.d_quickbuff[0] = 0;
      CEGUI::String::grow((String *)&local_21b8,0);
      puVar15 = local_21b8.d_quickbuff;
      if (0x20 < local_21b8.d_reserve) {
        puVar15 = local_21b8.d_buffer;
      }
      local_21b8.d_cplength = 0;
      *puVar15 = 0;
      local_2108.d_reserve = 0x20;
      local_2108.d_encodedbuff = (uchar *)0x0;
      local_2108.d_encodedbufflen = 0;
      local_2108.d_encodeddatlen = 0;
      local_2108.d_buffer = (uint *)0x0;
      local_2108.d_cplength = 0;
      local_2108.d_quickbuff[0] = 0;
                    /* try { // try from 00ba3789 to 00ba378d has its CatchHandler @ 00ba4e14 */
      CEGUI::String::grow((String *)&local_2108,5);
      pbVar9 = (byte *)0xfd0c0d;
      puVar15 = local_2108.d_quickbuff;
      if (0x20 < local_2108.d_reserve) {
        puVar15 = local_2108.d_buffer;
      }
      do {
        bVar4 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        *puVar15 = (uint)bVar4;
        puVar15 = puVar15 + 1;
      } while (pbVar9 != (byte *)0xfd0c12);
      local_2108.d_cplength = 5;
      puVar15 = local_2108.d_quickbuff;
      if (0x20 < local_2108.d_reserve) {
        puVar15 = local_2108.d_buffer;
      }
      puVar15[5] = 0;
                    /* try { // try from 00ba3802 to 00ba3806 has its CatchHandler @ 00ba4dad */
      CEGUI::PropertySet::setProperty((void *)pCVar18->m_iUnknown16A0,&local_2108,&local_21b8);
                    /* try { // try from 00ba380a to 00ba380e has its CatchHandler @ 00ba4e14 */
      CEGUI::String::~String((String *)&local_2108);
      CEGUI::String::~String((String *)&local_21b8);
      if (pCVar18->m_pUnknown1E50 != (void *)0x0) {
        CEGUI::String::String((String *)&local_2268,"");
                    /* try { // try from 00ba3847 to 00ba384b has its CatchHandler @ 00ba4d95 */
        CEGUI::Window::setText(pCVar18->m_pUnknown1E50,&local_2268);
        CEGUI::String::~String((String *)&local_2268);
      }
      pvVar11 = pCVar18->m_pUnknown1410;
      if (*(long *)((long)pvVar11 + 0x80) - (long)*(undefined8 **)((long)pvVar11 + 0x78) >> 3 != 0)
      {
        CEGUI::Window::removeChildWindow(pvVar11,(void *)**(undefined8 **)((long)pvVar11 + 0x78));
      }
      local_22c8 = local_22c8 + 1;
      pCVar18 = (CPetMenu *)&pCVar18->m_pSafePointers;
    } while (local_22c8 != 0x52);
    if (*(int *)(this_00->m_Unknown30 + 8) != 0) {
      uVar19 = 0;
      do {
        uVar20 = (uint)uVar19;
        if (uVar20 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
          plVar14 = *(long **)this_00->m_Unknown30;
          lVar17 = plVar14[uVar19];
          pCVar22 = *(CEquipment **)(lVar17 + 0x10);
        }
        else {
          plVar14 = *(long **)this_00->m_Unknown30;
          lVar17 = *plVar14;
          pCVar22 = *(CEquipment **)(lVar17 + 0x10);
        }
        if (0x12 < *(int *)(lVar17 + 0x18)) {
          if (uVar20 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
            plVar14 = (long *)(uVar19 * 8 + *(long *)this_00->m_Unknown30);
          }
          iVar7 = CInventory::getItemPane(this_00,*(uint *)(*plVar14 + 0x18));
          if (iVar7 == this->m_iUnknown6C) {
            if (uVar20 < *(uint *)(this_00->m_Unknown30 + 0xc)) {
              plVar14 = (long *)(uVar19 * 8 + *(long *)this_00->m_Unknown30);
            }
            else {
              plVar14 = *(long **)this_00->m_Unknown30;
            }
            setSlotIcon(this,pCVar22,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
          }
        }
        uVar19 = (ulong)(uVar20 + 1);
      } while (uVar20 + 1 < *(uint *)(this_00->m_Unknown30 + 8));
    }
    CEGUI::Window::moveToBack(this->m_pUnknown20);
    CEGUI::Window::moveToFront(this->m_pUnknown48);
    CEGUI::Window::moveToFront(this->m_pUnknown28);
    CEGUI::Window::moveToFront(this->m_pUnknown30);
    CEGUI::Window::moveToFront(this->m_pUnknown40);
  }
  return;
}

