/* address=00811130
   symbol=CCharacter::blendAnimation */


/* CCharacter::blendAnimation(int, bool, float, float, float) */

void CCharacter::blendAnimation(int param_1,bool param_2,float param_3,float param_4,float param_5)

{
  long *plVar1;
  bool in_DL;
  undefined7 in_register_00000031;
  undefined4 in_register_0000003c;
  long lVar2;

  lVar2 = CONCAT44(in_register_0000003c,param_1);
  if (*(long *)(lVar2 + 0x200) != 0) {
    if (*(char *)(lVar2 + 0x705) != '\0') {
      *(undefined1 *)(lVar2 + 0x705) = 0;
      plVar1 = *(long **)(lVar2 + 0x2e8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x378))(plVar1,1,1);
      }
      plVar1 = *(long **)(lVar2 + 0x2f8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x378))(plVar1,1,1);
      }
    }
    *(undefined4 *)(lVar2 + 600) = 0x3f800000;
    CGenericModel::blendAnimation
              (*(CGenericModel **)(lVar2 + 0x200),(uint)CONCAT71(in_register_00000031,param_2),in_DL
               ,param_3,param_4,DAT_00fa8760);
    return;
  }
  return;
}
