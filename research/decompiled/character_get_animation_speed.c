/* address=0080ee30
   symbol=CCharacter::getAnimationSpeed */


/* CCharacter::getAnimationSpeed() */

undefined4 __thiscall CCharacter::getAnimationSpeed(CCharacter *this)

{
  if (*(long *)(this + 0x200) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x200) + 0x240);
  }
  return DAT_00fa47fc;
}
