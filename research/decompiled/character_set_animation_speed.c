/* address=00825290
   symbol=CCharacter::setAnimationSpeed */


/* CCharacter::setAnimationSpeed(float) */

void __thiscall CCharacter::setAnimationSpeed(CCharacter *this,float param_1)

{
  CGenericModel *this_00;
  long lVar1;
  ulong uVar2;
  uint uVar3;

  this_00 = *(CGenericModel **)(this + 0x200);
  if (this_00 != (CGenericModel *)0x0) {
    lVar1 = *(long *)(this_00 + 0x1e0);
    *(float *)(this_00 + 0x240) = param_1;
    uVar3 = *(uint *)(this_00 + 0x244);
    if ((lVar1 != 0) && (uVar2 = *(long *)(lVar1 + 0x30) - *(long *)(lVar1 + 0x28) >> 3, uVar2 != 0)
       ) {
      if (uVar2 <= uVar3) {
        CGenericModel::clearAnimations(this_00);
        *(undefined4 *)(this_00 + 0x244) = 0;
        param_1 = *(float *)(this_00 + 0x240);
        uVar3 = 0;
      }
      CGenericModel::playAnimation(this_00,uVar3,(bool)this_00[0x23c],param_1,DAT_00fa8760);
      return;
    }
  }
  return;
}
