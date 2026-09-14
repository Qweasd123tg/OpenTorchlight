/* address=008110b0
   symbol=CCharacter::animationPlayAI */


/* CCharacter::animationPlayAI(float) */

void __thiscall CCharacter::animationPlayAI(CCharacter *this,float param_1)

{
  char cVar1;

  cVar1 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x200),*(uint *)(this + 0x2a8))
  ;
  if (cVar1 == '\0') {
    cVar1 = CGenericModel::animationQueued
                      (*(CGenericModel **)(this + 0x200),*(uint *)(this + 0x2a8));
    if (cVar1 == '\0') {
      (**(code **)(*(long *)this + 0x348))(this,0);
                    /* WARNING: Could not recover jumptable at 0x00811121. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)this + 0x358))(param_1,this,1);
      return;
    }
  }
  return;
}
