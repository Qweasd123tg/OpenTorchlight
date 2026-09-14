/* address=008a4130
   symbol=CGenericModel::getAnimationIndex */


/* WARNING: Removing unreachable block (ram,0x008a42a1) */
/* WARNING: Removing unreachable block (ram,0x008a42ac) */
/* CGenericModel::getAnimationIndex(std::string const&) const */

uint __thiscall CGenericModel::getAnimationIndex(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  char *local_58 [2];
  char *local_48 [3];

  bVar8 = 0;
  uVar4 = 0xffffffff;
  if (*(long *)(this + 0x1e0) != 0) {
    STRINGS::StringUpper((STRINGS *)local_48,param_1);
    lVar3 = *(long *)(this + 0x1e0);
    if (*(int *)(lVar3 + 0x20) != 0) {
      uVar4 = 0;
      do {
                    /* try { // try from 008a41c3 to 008a41c7 has its CatchHandler @ 008a428e */
        STRINGS::StringUpper
                  ((STRINGS *)local_58,(string *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x28)));
        bVar7 = false;
        lVar3 = *(long *)(local_58[0] + -0x18);
        if (lVar3 == *(long *)(local_48[0] + -0x18)) {
          bVar7 = true;
          pcVar5 = local_58[0];
          pcVar6 = local_48[0];
          do {
            if (lVar3 == 0) break;
            lVar3 = lVar3 + -1;
            bVar7 = *pcVar5 == *pcVar6;
            pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
            pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
          } while (bVar7);
        }
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        if (bVar7) goto LAB_008a4205;
        lVar3 = *(long *)(this + 0x1e0);
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(lVar3 + 0x20));
    }
    uVar4 = 0xffffffff;
LAB_008a4205:
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
  }
  return uVar4;
}
