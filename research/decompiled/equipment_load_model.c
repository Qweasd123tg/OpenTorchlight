/* address=00887b30
   symbol=CEquipment::loadModel */


/* WARNING: Removing unreachable block (ram,0x008884c6) */
/* WARNING: Removing unreachable block (ram,0x0088890b) */
/* WARNING: Removing unreachable block (ram,0x00888466) */
/* WARNING: Removing unreachable block (ram,0x00888832) */
/* WARNING: Removing unreachable block (ram,0x008888fd) */
/* WARNING: Removing unreachable block (ram,0x008886ce) */
/* WARNING: Removing unreachable block (ram,0x00888510) */
/* WARNING: Removing unreachable block (ram,0x00888581) */
/* WARNING: Removing unreachable block (ram,0x0088863b) */
/* WARNING: Removing unreachable block (ram,0x00888740) */
/* WARNING: Removing unreachable block (ram,0x00888502) */
/* WARNING: Removing unreachable block (ram,0x0088858c) */
/* WARNING: Removing unreachable block (ram,0x0088851e) */
/* WARNING: Removing unreachable block (ram,0x008886be) */
/* WARNING: Removing unreachable block (ram,0x0088874b) */
/* WARNING: Removing unreachable block (ram,0x00888824) */
/* WARNING: Removing unreachable block (ram,0x00888816) */
/* WARNING: Removing unreachable block (ram,0x00888808) */
/* WARNING: Removing unreachable block (ram,0x008888c6) */
/* WARNING: Removing unreachable block (ram,0x00888471) */
/* CEquipment::loadModel(std::wstring, std::wstring) */

void __thiscall
CEquipment::loadModel(CEquipment *this,undefined8 *param_2,wstring_conflict *param_3)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  size_t __n;
  CDataGroup *this_00;
  bool bVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  wstring_conflict *pwVar9;
  undefined8 uVar10;
  uint uVar11;
  void *local_198;
  undefined8 local_190;
  undefined8 local_188;
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  wchar_t *local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [5];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x68) != 0) {
    unloadModel(this);
    lVar7 = CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x68),(SceneManager *)0x0,(wchar_t *)*param_2,
                       (wchar_t *)0x0,false,false,true);
    *(long *)(this + 0x2b0) = lVar7;
    if ((*(long **)(lVar7 + 0x58) != (long *)0x0) &&
       (lVar7 = (**(code **)(**(long **)(lVar7 + 0x58) + 0xc0))(), lVar7 != 0)) {
      plVar8 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x2b0) + 0x58) + 0xc0))();
      (**(code **)(*plVar8 + 0x1e0))(plVar8,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
    }
    if (((*(long *)(this + 0x68) == 0) ||
        (lVar7 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar7 == 0)) ||
       (lVar7 = *(long *)(lVar7 + 0x1d8), lVar7 == 0)) {
                    /* try { // try from 008880a0 to 008880a4 has its CatchHandler @ 00888840 */
      std::wstring::wstring
                ((wstring_conflict *)local_68,L"media/sharedtextures/rimlight.dds",local_39);
    }
    else {
                    /* try { // try from 00887bfd to 00887c01 has its CatchHandler @ 00888840 */
      std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(lVar7 + 0x6d8));
    }
                    /* try { // try from 00887c0c to 00887c10 has its CatchHandler @ 008888b6 */
    CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b0));
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_68[0] + -8);
      iVar6 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    CGenericModel::setCastsShadows(*(CGenericModel **)(this + 0x2b0),false);
    (**(code **)(**(long **)(this + 0x58) + 0x1a8))
              (*(long **)(this + 0x58),*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
    (**(code **)(*(long *)this + 0x2c0))(this,0,1);
    (**(code **)(**(long **)(this + 0x2b0) + 0x58))(0,0);
    plVar8 = *(long **)(*(long *)(this + 0x2b0) + 0x60);
    if (plVar8 == (long *)0x0) {
      std::operator+((wchar_t *)local_138,(wstring_conflict *)L"Error loading model : ");
                    /* try { // try from 008882db to 008882df has its CatchHandler @ 008884d1 */
      STRINGS::StringConvertToNarrow((STRINGS *)local_78,local_138[0]);
                    /* try { // try from 008882e0 to 008882f6 has its CatchHandler @ 008884ab */
      uVar10 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar10,(STRINGS *)local_78,2,0);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_78[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if ((allocator *)(local_138[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        pwVar1 = local_138[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
        }
      }
    }
    else {
      (**(code **)(*plVar8 + 0x140))(plVar8,0x32);
      __n = *(size_t *)(*(wchar_t **)param_3 + -6);
      if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
         (iVar6 = wmemcmp(*(wchar_t **)param_3,::EMPTY_WSTRING,__n), iVar6 == 0)) {
                    /* try { // try from 008880d2 to 008880f0 has its CatchHandler @ 00888848 */
        std::wstring::wstring((wstring_conflict *)local_98,L"MESHFILE_SECONDARY",&local_3a);
        bVar4 = true;
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_98,
                            (wstring_conflict *)&::EMPTY_WSTRING);
      }
      else {
        bVar4 = false;
        pwVar9 = param_3;
      }
                    /* try { // try from 00887cc4 to 00887cc8 has its CatchHandler @ 00888848 */
      std::wstring::wstring((wstring_conflict *)local_88,pwVar9);
      if ((bVar4) &&
         ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
        LOCK();
        piVar2 = (int *)(local_98[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
      if (*(long *)(local_88[0] + -0x18) != 0) {
                    /* try { // try from 00887cf8 to 00887cfc has its CatchHandler @ 00888866 */
        std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)local_88);
        if (*(long *)(*(long *)param_3 + -0x18) == 0) {
                    /* try { // try from 00888111 to 00888115 has its CatchHandler @ 00888646 */
          std::wstring::wstring((wstring_conflict *)local_a8,L"RESOURCEDIRECTORY",&local_3b);
                    /* try { // try from 00888125 to 00888134 has its CatchHandler @ 0088862e */
          CDataGroup::GetDataValue
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,
                     (wstring_conflict *)&::EMPTY_WSTRING);
          std::wstring::assign((wstring_conflict *)local_138);
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_a8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
                    /* try { // try from 00888158 to 0088815c has its CatchHandler @ 008886de */
          std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)local_138);
          wcslen(L"/");
                    /* try { // try from 00888172 to 00888176 has its CatchHandler @ 008885f5 */
          std::wstring::append((wchar_t *)local_b8,0xfff8b8);
                    /* try { // try from 0088818a to 0088818e has its CatchHandler @ 008885f0 */
          std::operator+((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
                    /* try { // try from 008881a2 to 008881a6 has its CatchHandler @ 008885eb */
          std::wstring::wstring((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
          wcslen(L".mesh");
                    /* try { // try from 008881bc to 008881c0 has its CatchHandler @ 008885de */
          std::wstring::append((wchar_t *)local_d8,0xfafb04);
                    /* try { // try from 008881cf to 008881d3 has its CatchHandler @ 008885d9 */
          FILESYSTEM::CleanPath((FILESYSTEM *)local_e8,(wstring_conflict *)local_d8);
                    /* try { // try from 008881da to 008881de has its CatchHandler @ 00888597 */
          std::wstring::assign((wstring_conflict *)local_138);
          if ((allocator *)(local_e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_e8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
            }
          }
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
        }
                    /* try { // try from 00887d29 to 00887d76 has its CatchHandler @ 008886de */
        lVar7 = CResourceManager::createGenericModel
                          (*(CResourceManager **)(this + 0x68),(SceneManager *)0x0,local_138[0],
                           (wchar_t *)0x0,false,false,true);
        *(long *)(this + 0x2b8) = lVar7;
        if ((*(long **)(lVar7 + 0x58) != (long *)0x0) &&
           (lVar7 = (**(code **)(**(long **)(lVar7 + 0x58) + 0xc0))(), lVar7 != 0)) {
          plVar8 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x2b8) + 0x58) + 0xc0))();
          (**(code **)(*plVar8 + 0x1e0))(plVar8,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
        }
        if (((*(long *)(this + 0x68) == 0) ||
            (lVar7 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar7 == 0)) ||
           (lVar7 = *(long *)(lVar7 + 0x1d8), lVar7 == 0)) {
                    /* try { // try from 00888370 to 00888374 has its CatchHandler @ 008886c9 */
          std::wstring::wstring
                    ((wstring_conflict *)local_f8,L"media/sharedtextures/rimlight.dds",&local_3c);
        }
        else {
                    /* try { // try from 00887db3 to 00887db7 has its CatchHandler @ 008886c9 */
          std::wstring::wstring((wstring_conflict *)local_f8,(wstring_conflict *)(lVar7 + 0x6d8));
        }
                    /* try { // try from 00887dc2 to 00887dc6 has its CatchHandler @ 008886d9 */
        CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b8));
        if ((allocator *)(local_f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_f8[0] + -8);
          iVar6 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
          }
        }
                    /* try { // try from 00887de5 to 00887e18 has its CatchHandler @ 008886de */
        CGenericModel::setCastsShadows(*(CGenericModel **)(this + 0x2b8),false);
        (**(code **)(**(long **)(this + 0x2b8) + 0x58))(0,0);
        (**(code **)(**(long **)(*(long *)(this + 0x2b8) + 0x60) + 0x140))
                  (*(long **)(*(long *)(this + 0x2b8) + 0x60),0x32);
        if ((allocator *)(local_138[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_138[0] + -2;
          wVar3 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar3 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
          }
        }
      }
                    /* try { // try from 00887e46 to 00887e4a has its CatchHandler @ 008886b6 */
      std::wstring::wstring((wstring_conflict *)local_118,L"TEXTURE_OVERRIDE",&local_3d);
                    /* try { // try from 00887e5a to 00887e6e has its CatchHandler @ 008886a6 */
      pwVar9 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_118,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)local_108,pwVar9);
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_118[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      if (*(long *)(local_108[0] + -0x18) != 0) {
                    /* try { // try from 00887ea2 to 00887ea6 has its CatchHandler @ 00888756 */
        CGenericModel::setTextureOverride
                  (*(CGenericModel **)(this + 0x2b0),(wstring_conflict *)local_108);
      }
      local_198 = (void *)0x0;
      local_190 = 0;
      local_188 = 0;
                    /* try { // try from 00887eda to 00887ede has its CatchHandler @ 0088876b */
      std::wstring::wstring((wstring_conflict *)local_128,L"TEXTURE_REPLACE",&local_3e);
                    /* try { // try from 00887eee to 00887ef2 has its CatchHandler @ 0088877f */
      uVar5 = CDataGroup::GetDataGroupsMatchingName
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_128,
                         (vector *)&local_198);
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_128[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
      if (uVar5 != 0) {
        lVar7 = 0;
        uVar11 = 0;
        do {
          this_00 = *(CDataGroup **)((long)local_198 + lVar7);
                    /* try { // try from 00887f43 to 00887f47 has its CatchHandler @ 008887bc */
          std::wstring::wstring((wstring_conflict *)local_148,L"NAME",&local_3f);
                    /* try { // try from 00887f55 to 00887f69 has its CatchHandler @ 008887f6 */
          pwVar9 = (wstring_conflict *)
                   CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_148,L"");
          std::wstring::wstring((wstring_conflict *)local_138,pwVar9);
          if ((allocator *)(local_148[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_148[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
            }
          }
                    /* try { // try from 00887f8e to 00887f92 has its CatchHandler @ 0088886b */
          std::wstring::wstring((wstring_conflict *)local_168,L"TEXTURE",&local_40);
                    /* try { // try from 00887fa0 to 00887fb1 has its CatchHandler @ 008887be */
          pwVar9 = (wstring_conflict *)
                   CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_168,L"");
          std::wstring::wstring((wstring_conflict *)local_158,pwVar9);
          if ((allocator *)(local_168[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_168[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
            }
          }
                    /* try { // try from 00887fcf to 00887fd3 has its CatchHandler @ 008887da */
          STRINGS::StringConvertToNarrow((STRINGS *)local_178,local_138[0]);
                    /* try { // try from 00887fe3 to 00887fe7 has its CatchHandler @ 008887e9 */
          CGenericModel::setTextureOverrideSingle
                    (*(CGenericModel **)(this + 0x2b0),(string *)local_178,
                     (wstring_conflict *)local_158);
          if ((allocator *)(local_178[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_178[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
            }
          }
          if ((allocator *)(local_158[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_158[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
            }
          }
          if ((allocator *)(local_138[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_138[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
            }
          }
          uVar11 = uVar11 + 1;
          lVar7 = lVar7 + 8;
        } while (uVar11 < uVar5);
      }
      if (local_198 != (void *)0x0) {
        operator_delete(local_198);
      }
      if ((allocator *)(local_108[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_108[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
        }
      }
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_88[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
    }
  }
  return;
}
