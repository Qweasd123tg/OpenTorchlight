/* address=0080f230
   symbol=CCharacter::setAnimationPlaying */


/* CCharacter::setAnimationPlaying(unsigned int) */

void __thiscall CCharacter::setAnimationPlaying(CCharacter *this,uint param_1)

{
  CGenericModel *this_00;
  long lVar1;
  ulong uVar2;

  if (*(CGenericModel **)(this + 0x200) != (CGenericModel *)0x0) {
    CGenericModel::clearAnimations(*(CGenericModel **)(this + 0x200));
    this_00 = *(CGenericModel **)(this + 0x200);
    lVar1 = *(long *)(this_00 + 0x1e0);
    *(uint *)(this_00 + 0x244) = param_1;
    if ((lVar1 != 0) && (uVar2 = *(long *)(lVar1 + 0x30) - *(long *)(lVar1 + 0x28) >> 3, uVar2 != 0)
       ) {
      if (uVar2 <= param_1) {
        param_1 = 0;
        CGenericModel::clearAnimations(this_00);
        *(undefined4 *)(this_00 + 0x244) = 0;
      }
      CGenericModel::playAnimation
                (this_00,param_1,(bool)this_00[0x23c],*(float *)(this_00 + 0x240),DAT_00fa8760);
      return;
    }
  }
  return;
}
