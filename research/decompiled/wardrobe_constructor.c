/* address=00919810
   symbol=CWardrobe::CWardrobe */


/* WARNING: Removing unreachable block (ram,0x0091a4c2) */
/* WARNING: Removing unreachable block (ram,0x0091a4fa) */
/* WARNING: Removing unreachable block (ram,0x0091a516) */
/* WARNING: Removing unreachable block (ram,0x0091a48a) */
/* WARNING: Removing unreachable block (ram,0x0091a4a6) */
/* WARNING: Removing unreachable block (ram,0x0091a47c) */
/* WARNING: Removing unreachable block (ram,0x0091a498) */
/* WARNING: Removing unreachable block (ram,0x0091a418) */
/* WARNING: Removing unreachable block (ram,0x0091a4ec) */
/* WARNING: Removing unreachable block (ram,0x0091a524) */
/* WARNING: Removing unreachable block (ram,0x0091a4b4) */
/* WARNING: Removing unreachable block (ram,0x0091a508) */
/* WARNING: Removing unreachable block (ram,0x0091a4d0) */
/* WARNING: Removing unreachable block (ram,0x0091a4de) */
/* WARNING: Removing unreachable block (ram,0x0091a46e) */
/* CWardrobe::CWardrobe(CCharacter*, Ogre::SceneManager*, Ogre::SceneManager*, CGenericModel*,
   CGenericModel*, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring,
   std::wstring) */

void __thiscall
CWardrobe::CWardrobe
          (CWardrobe *this,undefined8 param_1,undefined8 param_2,undefined8 param_4_00,
          undefined8 param_4,undefined8 param_5,wstring_conflict *param_7,wstring_conflict *param_8,
          wstring_conflict *param_9,wstring_conflict *param_10,long *param_11,long *param_12)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  long lVar7;
  CFileSystem *pCVar8;
  long *plVar9;
  Image *pIVar10;
  undefined1 *local_178;
  long local_170;
  long local_168;
  undefined4 local_160;
  undefined4 local_15c;
  undefined1 *local_158;
  char local_150;
  undefined1 *local_148;
  long local_140;
  long local_138;
  undefined4 local_130;
  undefined4 local_12c;
  undefined1 *local_128;
  char local_120;
  undefined1 *local_118;
  long local_110;
  long local_108;
  undefined4 local_100;
  undefined4 local_fc;
  undefined1 *local_f8;
  char local_f0;
  undefined1 *local_e8;
  string local_e0 [8];
  wstring_conflict local_d8 [8];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined1 *local_c8;
  char local_c0;
  undefined **local_b8;
  long local_b0;
  int *local_a8;
  undefined4 local_a0;
  undefined **local_98;
  long local_90;
  int *local_88;
  undefined4 local_80;
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CWardrobe_00fd4190;
  *(undefined8 *)(this + 0x10) = param_2;
  *(undefined8 *)(this + 0x18) = param_4;
  *(undefined8 *)(this + 0x20) = param_5;
  *(undefined8 *)(this + 0x28) = 0;
                    /* try { // try from 00919864 to 00919868 has its CatchHandler @ 0091a58c */
  std::wstring::wstring((wstring_conflict *)(this + 0x30),param_7);
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined ***)(this + 0x38) = &PTR__TexturePtr_00fa8610;
  lVar7 = 0;
  *(undefined8 *)(this + 0x58) = 0;
  do {
    *(undefined4 **)(this + lVar7 + 0x88) = &DAT_01424558;
    lVar7 = lVar7 + 8;
  } while (lVar7 != 0x28);
  lVar7 = 0;
  do {
    *(undefined4 **)((wstring_conflict *)(this + 0xb0) + lVar7) = &DAT_01424558;
    lVar7 = lVar7 + 8;
  } while (lVar7 != 0x28);
  *(undefined8 *)(this + 0x100) = param_2;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined8 *)(this + 0xe8) = 0;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined8 *)(this + 0xf8) = param_1;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  local_e8 = &DAT_01423a38;
                    /* try { // try from 00919949 to 0091994d has its CatchHandler @ 0091a571 */
  std::string::string(local_e0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00919957 to 0091995b has its CatchHandler @ 0091a54d */
  std::wstring::wstring(local_d8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_d0 = 4;
  local_cc = 3;
  local_c8 = &DAT_01423a38;
  local_c0 = '\0';
  local_118 = &DAT_01423a38;
                    /* try { // try from 009199a3 to 009199a7 has its CatchHandler @ 0091a532 */
  std::string::string((string *)&local_110,(string *)&::EMPTY_STRING);
                    /* try { // try from 009199b1 to 009199b5 has its CatchHandler @ 0091a609 */
  std::wstring::wstring((wstring_conflict *)&local_108,(wstring_conflict *)&::EMPTY_WSTRING);
  local_100 = 4;
  local_fc = 3;
  local_f8 = &DAT_01423a38;
  local_f0 = '\0';
  local_148 = &DAT_01423a38;
                    /* try { // try from 009199fd to 00919a01 has its CatchHandler @ 0091a602 */
  std::string::string((string *)&local_140,(string *)&::EMPTY_STRING);
                    /* try { // try from 00919a13 to 00919a17 has its CatchHandler @ 0091a5d1 */
  std::wstring::wstring((wstring_conflict *)&local_138,(wstring_conflict *)&::EMPTY_WSTRING);
  local_130 = 4;
  local_12c = 3;
  local_128 = &DAT_01423a38;
  local_120 = '\0';
  local_178 = &DAT_01423a38;
                    /* try { // try from 00919a59 to 00919a5d has its CatchHandler @ 0091a5b6 */
  std::string::string((string *)&local_170,(string *)&::EMPTY_STRING);
                    /* try { // try from 00919a67 to 00919a6b has its CatchHandler @ 0091a62f */
  std::wstring::wstring((wstring_conflict *)&local_168,(wstring_conflict *)&::EMPTY_WSTRING);
  local_160 = 4;
  local_15c = 3;
  local_158 = &DAT_01423a38;
  local_150 = '\0';
                    /* try { // try from 00919a9b to 00919b6d has its CatchHandler @ 0091a383 */
  std::wstring::assign((wstring_conflict *)(this + 0xb0));
  std::wstring::assign((wstring_conflict *)(this + 0xb8));
  std::wstring::assign((wstring_conflict *)(this + 0xc0));
  pCVar8 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(pCVar8,param_7,(CFileInfo *)&local_e8,false,true,false);
  pCVar8 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(pCVar8,param_8,(CFileInfo *)&local_118,false,true,false);
  pCVar8 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(pCVar8,param_9,(CFileInfo *)&local_178,false,true,false);
  pCVar8 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(pCVar8,param_10,(CFileInfo *)&local_148,false,true,false);
  FILESYSTEM::RemoveFileName((FILESYSTEM *)local_58,param_7);
  if (local_c0 != '\0') {
    pIVar10 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0091a078 to 0091a07c has its CatchHandler @ 0091a46c */
    Ogre::Image::Image(pIVar10);
    *(Image **)(this + 0x58) = pIVar10;
                    /* try { // try from 0091a0a9 to 0091a0ad has its CatchHandler @ 0091a5a3 */
    Ogre::Image::load((string *)pIVar10,local_e0);
  }
  if (local_f0 != '\0') {
    pIVar10 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0091a020 to 0091a024 has its CatchHandler @ 0091a452 */
    Ogre::Image::Image(pIVar10);
    *(Image **)(this + 0x60) = pIVar10;
                    /* try { // try from 0091a051 to 0091a06f has its CatchHandler @ 0091a5a3 */
    Ogre::Image::load((string *)pIVar10,(string *)&local_110);
  }
  if (local_150 != '\0') {
    pIVar10 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00919fc8 to 00919fcc has its CatchHandler @ 0091a587 */
    Ogre::Image::Image(pIVar10);
    *(Image **)(this + 0x70) = pIVar10;
                    /* try { // try from 00919ff9 to 0091a017 has its CatchHandler @ 0091a5a3 */
    Ogre::Image::load((string *)pIVar10,(string *)&local_170);
  }
  if (local_120 != '\0') {
    pIVar10 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00919f60 to 00919f64 has its CatchHandler @ 0091a582 */
    Ogre::Image::Image(pIVar10);
    *(Image **)(this + 0x68) = pIVar10;
                    /* try { // try from 00919fa1 to 00919fbf has its CatchHandler @ 0091a5a3 */
    Ogre::Image::load((string *)pIVar10,(string *)&local_140);
  }
  if (*(long *)(*param_11 + -0x18) != 0) {
    std::wstring::assign((wstring_conflict *)(this + 0xa0));
  }
  if (*(long *)(*param_12 + -0x18) != 0) {
                    /* try { // try from 00919f22 to 00919f57 has its CatchHandler @ 0091a5a3 */
    std::wstring::assign((wstring_conflict *)(this + 0xa8));
  }
  if (*(long *)(this + 0x58) != 0) {
                    /* try { // try from 00919bdf to 00919c0a has its CatchHandler @ 0091a5a3 */
    uVar3 = Ogre::Image::getFormat();
    uVar4 = Ogre::Image::getNumMipmaps();
    uVar5 = Ogre::Image::getHeight();
    uVar6 = Ogre::Image::getWidth();
                    /* try { // try from 00919c24 to 00919c28 has its CatchHandler @ 0091a61c */
    std::string::string((string *)local_68,"wtex_",local_39);
                    /* try { // try from 00919c39 to 00919c3d has its CatchHandler @ 0091a642 */
    STRINGS::uniqueName((STRINGS *)local_78,(string *)local_68);
                    /* try { // try from 00919c3e to 00919cae has its CatchHandler @ 0091a442 */
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    (**(code **)(*plVar9 + 0x140))
              (&local_98,plVar9,local_78,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,
               uVar6,uVar5,1,uVar4,uVar3,0x105,0,0,0);
    if (*(long *)(this + 0x40) != local_90) {
      local_b0 = local_90;
      local_b8 = &PTR__SharedPtr_00fa86b0;
      local_a8 = local_88;
      local_a0 = local_80;
      if (local_88 != (int *)0x0) {
        *local_88 = *local_88 + 1;
      }
                    /* try { // try from 00919d0f to 00919d11 has its CatchHandler @ 0091a3cd */
      (**(code **)(*(long *)(this + 0x38) + 0x18))(this + 0x38,&local_b8);
      local_b8 = &PTR__SharedPtr_00fa86b0;
      if ((local_a8 != (int *)0x0) && (iVar2 = *local_a8, *local_a8 = iVar2 + -1, iVar2 + -1 == 0))
      {
                    /* try { // try from 00919f08 to 00919f0c has its CatchHandler @ 0091a578 */
        Ogre::SharedPtr<Ogre::Texture>::destroy((SharedPtr<Ogre::Texture> *)&local_b8);
      }
    }
    local_98 = &PTR__SharedPtr_00fa86b0;
    if ((local_88 != (int *)0x0) && (iVar2 = *local_88, *local_88 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 00919ef0 to 00919ef2 has its CatchHandler @ 0091a442 */
      (*(code *)PTR_destroy_00fa86c0)(&local_98);
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 00919da1 to 00919db0 has its CatchHandler @ 0091a5a3 */
    (**(code **)(**(long **)(this + 0x40) + 0x180))();
  }
  update(this,(CInventory *)0x0);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_158 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_158 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_158 + -0x18));
    }
  }
  if ((allocator *)(local_168 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_168 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168 + -0x18));
    }
  }
  if ((allocator *)(local_170 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_170 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_170 + -0x18));
    }
  }
  if ((allocator *)(local_178 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_178 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_178 + -0x18));
    }
  }
  if ((allocator *)(local_128 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_128 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_128 + -0x18));
    }
  }
  if ((allocator *)(local_138 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_138 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138 + -0x18));
    }
  }
  if ((allocator *)(local_140 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_140 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_140 + -0x18));
    }
  }
  if ((allocator *)(local_148 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_148 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_148 + -0x18));
    }
  }
  if ((allocator *)(local_f8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_f8 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8 + -0x18));
    }
  }
  if ((allocator *)(local_108 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_108 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108 + -0x18));
    }
  }
  if ((allocator *)(local_110 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_110 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_110 + -0x18));
    }
  }
  if ((allocator *)(local_118 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_118 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118 + -0x18));
    }
  }
  CFileInfo::~CFileInfo((CFileInfo *)&local_e8);
  return;
}
