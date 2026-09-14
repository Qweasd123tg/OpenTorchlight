/* address=00dd3ac0
   symbol=CAnimationPlayer::update */


/* CAnimationPlayer::update(float) */

void __thiscall CAnimationPlayer::update(CAnimationPlayer *this,float param_1)

{
  char cVar1;
  float fVar2;

  cVar1 = CResourceManager::getEditorIsRunning();
  if ((cVar1 != '\0') || (this[0x91] == (CAnimationPlayer)0x0)) {
    return;
  }
  if (this[0x94] != (CAnimationPlayer)0x0) {
    if (*(float *)(this + 0x98) <= *(float *)(this + 0xa0)) {
      return;
    }
    fVar2 = *(float *)(this + 0x98) - param_1;
    *(float *)(this + 0x98) = fVar2;
    if (fVar2 <= *(float *)(this + 0xa0)) {
      stopAnimation(this,false);
      return;
    }
  }
  playAnimation(this);
  return;
}
