/* address=009156f0
   symbol=CWardrobe::setBaseTexture */


/* WARNING: Removing unreachable block (ram,0x00915937) */
/* WARNING: Removing unreachable block (ram,0x0091591b) */
/* WARNING: Removing unreachable block (ram,0x009158e2) */
/* WARNING: Removing unreachable block (ram,0x00915929) */
/* CWardrobe::setBaseTexture(EWardrobeSlot, std::wstring) */

void __thiscall CWardrobe::setBaseTexture(CWardrobe *this,int param_2,wstring_conflict *param_3)

{
  int *piVar1;
  int iVar2;
  CFileSystem *this_00;
  Image *this_01;
  long lVar3;
  undefined1 *local_68;
  long local_60;
  long local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  char local_40;

  lVar3 = (long)param_2;
  std::wstring::assign((wstring_conflict *)(this + lVar3 * 8 + 0xb0));
  if (*(long **)(this + (lVar3 + 0xc) * 8) != (long *)0x0) {
    (**(code **)(**(long **)(this + (lVar3 + 0xc) * 8) + 8))();
    *(undefined8 *)(this + (lVar3 + 0xc) * 8) = 0;
  }
  local_68 = &DAT_01423a38;
                    /* try { // try from 00915746 to 0091574a has its CatchHandler @ 009158ed */
  std::string::string((string *)&local_60,(string *)&::EMPTY_STRING);
                    /* try { // try from 00915755 to 00915759 has its CatchHandler @ 00915900 */
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)&::EMPTY_WSTRING);
  local_50 = 4;
  local_4c = 3;
  local_48 = &DAT_01423a38;
  local_40 = '\0';
                    /* try { // try from 00915778 to 009157ac has its CatchHandler @ 009158cf */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_3,(CFileInfo *)&local_68,false,true,false);
  if (local_40 != '\0') {
    this_01 = (Image *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 009157b3 to 009157b7 has its CatchHandler @ 0091590e */
    Ogre::Image::Image(this_01);
    *(Image **)(this + lVar3 * 8 + 0x60) = this_01;
                    /* try { // try from 009157dd to 009157e1 has its CatchHandler @ 009158cf */
    Ogre::Image::load((string *)this_01,(string *)&local_60);
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if ((allocator *)(local_60 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_60 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_60 + -0x18));
    }
  }
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  return;
}
