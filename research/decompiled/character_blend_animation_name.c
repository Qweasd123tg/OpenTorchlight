/* address=00812830
   symbol=CCharacter::blendAnimation */


/* CCharacter::blendAnimation(std::string const&, bool, float, float, float) */

void CCharacter::blendAnimation
               (string *param_1,bool param_2,float param_3,float param_4,float param_5)

{
  long *plVar1;
  bool in_DL;
  undefined7 in_register_00000031;

  if (*(long *)(param_1 + 0x200) != 0) {
    if (param_1[0x705] != (string)0x0) {
      param_1[0x705] = (string)0x0;
      plVar1 = *(long **)(param_1 + 0x2e8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x378))(plVar1,1,1);
      }
      plVar1 = *(long **)(param_1 + 0x2f8);
      if (plVar1 != (long *)0x0) {
        (**(code **)(*plVar1 + 0x378))(plVar1,1,1);
      }
    }
    *(undefined4 *)(param_1 + 600) = 0x3f800000;
    CGenericModel::blendAnimation
              (*(CGenericModel **)(param_1 + 0x200),(string *)CONCAT71(in_register_00000031,param_2)
               ,in_DL,param_3,param_4,DAT_00fa8760);
    return;
  }
  return;
}
