/* address=00815ad0
   symbol=CCharacter::runningSpeed */


/* CCharacter::runningSpeed() */

float __thiscall CCharacter::runningSpeed(CCharacter *this)

{
  float fVar1;
  float fVar2;
  float fVar3;

  fVar1 = (float)getEffectValue(this,0x15,7);
  if (fVar1 < 0.0) {
    fVar3 = (float)getEffectValue(this,0x8c,7);
    fVar3 = fVar3 / DAT_00fa483c;
    fVar2 = DAT_00fa47fc;
    if ((fVar3 < DAT_00fa47fc) && (fVar2 = fVar3, fVar3 <= 0.0)) {
      fVar2 = 0.0;
    }
    fVar1 = fVar1 * (DAT_00fa47fc - fVar2);
  }
  fVar2 = (*(float *)(this + 0x290) * fVar1) / DAT_00fa483c + *(float *)(this + 0x290);
  fVar1 = 0.0;
  if (0.0 <= fVar2) {
    fVar1 = fVar2;
  }
  return fVar1;
}
