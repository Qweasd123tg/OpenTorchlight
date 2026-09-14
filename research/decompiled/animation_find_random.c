/* address=008a2de0
   symbol=CGenericModel::findRandomAnimation */


/* WARNING: Removing unreachable block (ram,0x008a2faa) */
/* WARNING: Removing unreachable block (ram,0x008a2f9d) */
/* CGenericModel::findRandomAnimation(std::string const&) */

uint __thiscall CGenericModel::findRandomAnimation(CGenericModel *this,string *param_1)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  char *pcVar7;
  allocator *paVar8;
  char *pcVar9;
  uint uVar10;
  bool bVar11;
  byte bVar12;
  float fVar13;
  char *local_58 [2];
  long local_48 [3];

  bVar12 = 0;
  lVar4 = *(long *)(this + 0x1e0);
  if ((lVar4 == 0) || (*(int *)(lVar4 + 0x20) == 0)) {
    uVar10 = 0xffffffff;
  }
  else {
    uVar6 = *(ulong *)(*(long *)param_1 + -0x18) & 0xffffffff;
    uVar5 = 0;
    uVar10 = 0xffffffff;
    do {
      STRINGS::StringUpper
                ((STRINGS *)local_48,(string *)((ulong)uVar5 * 8 + *(long *)(lVar4 + 0x28)));
      paVar8 = (allocator *)(local_48[0] + -0x18);
      if (uVar6 <= *(ulong *)(local_48[0] + -0x18)) {
                    /* try { // try from 008a2e87 to 008a2e8b has its CatchHandler @ 008a2f8a */
        std::string::string((string *)local_58,(string *)local_48,0,uVar6);
        bVar11 = false;
        lVar4 = *(long *)(local_58[0] + -0x18);
        if (lVar4 == *(long *)(*(char **)param_1 + -0x18)) {
          bVar11 = true;
          pcVar7 = local_58[0];
          pcVar9 = *(char **)param_1;
          do {
            if (lVar4 == 0) break;
            lVar4 = lVar4 + -1;
            bVar11 = *pcVar7 == *pcVar9;
            pcVar7 = pcVar7 + (ulong)bVar12 * -2 + 1;
            pcVar9 = pcVar9 + (ulong)bVar12 * -2 + 1;
          } while (bVar11);
        }
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_58[0] + -8);
          iVar3 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar3 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        if (bVar11) {
          if (uVar10 == 0xffffffff) {
            paVar8 = (allocator *)(local_48[0] + -0x18);
            uVar10 = uVar5;
            goto LAB_008a2e30;
          }
                    /* try { // try from 008a2edb to 008a2edf has its CatchHandler @ 008a2fa8 */
          fVar13 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
          if (fVar13 < DAT_00fd1a34) {
            uVar10 = uVar5;
          }
        }
        paVar8 = (allocator *)(local_48[0] + -0x18);
      }
LAB_008a2e30:
      if (paVar8 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        paVar1 = paVar8 + 0x10;
        iVar3 = *(int *)paVar1;
        *(int *)paVar1 = *(int *)paVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy(paVar8);
        }
      }
      lVar4 = *(long *)(this + 0x1e0);
    } while ((lVar4 != 0) && (uVar5 = uVar5 + 1, uVar5 < *(uint *)(lVar4 + 0x20)));
  }
  return uVar10;
}
