/* address=008a5a40
   symbol=CGenericModel::playAnimation */


/* CGenericModel::playAnimation(unsigned int, bool, float, float) */

void __thiscall
CGenericModel::playAnimation
          (CGenericModel *this,uint param_1,bool param_2,float param_3,float param_4)

{
  CRunicCore *this_00;
  void *pvVar1;
  long lVar2;
  undefined8 *puVar3;
  long lVar4;
  undefined4 uVar5;

  if (*(int *)(this + 0x150) != 0) {
    clearAnimations(this);
    if (param_1 < *(uint *)(this + 0x154)) {
      *(bool *)(*(long *)((ulong)param_1 * 8 + *(long *)(this + 0x148)) + 0x2d) = param_2;
    }
    else {
      *(bool *)(**(long **)(this + 0x148) + 0x2d) = param_2;
    }
    uVar5 = Ogre::AnimationState::getLength();
    this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a5aef to 008a5af3 has its CatchHandler @ 008a5cd2 */
    CRunicCore::CRunicCore(this_00);
    *(undefined ***)this_00 = &PTR__CActiveAnimation_00fd1750;
    *(uint *)(this_00 + 0x10) = param_1;
    *(undefined4 *)(this_00 + 0x20) = 0;
    *(undefined4 *)(this_00 + 0x18) = uVar5;
    this_00[0x24] = (CRunicCore)param_2;
    this_00[0x25] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x1c) = uVar5;
    this_00[0x26] = (CRunicCore)0x0;
    this_00[0x27] = (CRunicCore)0x0;
    this_00[0x28] = (CRunicCore)0x0;
    this_00[0x29] = (CRunicCore)0x0;
    this_00[0x2a] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x2c) = 0;
    *(undefined4 *)(this_00 + 0x30) = 0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    *(float *)(this_00 + 0x38) = param_3;
    if ((param_4 != DAT_00fa8760) || (NAN(param_4) || NAN(DAT_00fa8760))) {
      *(float *)(this_00 + 0x18) = param_4;
    }
    this_00[0x25] = (CRunicCore)0x1;
    this_00[0x26] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    if (param_1 < *(uint *)(this + 0x154)) {
      puVar3 = (undefined8 *)((ulong)param_1 * 8 + *(long *)(this + 0x148));
    }
    else {
      puVar3 = *(undefined8 **)(this + 0x148);
    }
    Ogre::AnimationState::setEnabled(SUB81(*puVar3,0));
    lVar4 = *(long *)(this + 0x170);
    if (lVar4 == *(long *)(this + 0x178)) {
      lVar4 = *(long *)(this + 0x188);
      if (lVar4 - *(long *)(this + 0x160) >> 3 == 0) {
        std::deque<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_reallocate_map
                  ((deque<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),1,
                   true);
        lVar4 = *(long *)(this + 0x188);
      }
      pvVar1 = operator_new(0x200);
      *(void **)(lVar4 + -8) = pvVar1;
      lVar4 = *(long *)(this + 0x188);
      *(long *)(this + 0x188) = lVar4 + -8;
      lVar4 = *(long *)(lVar4 + -8);
      *(long *)(this + 0x178) = lVar4;
      *(long *)(this + 0x180) = lVar4 + 0x200;
      *(long *)(this + 0x170) = lVar4 + 0x1f8;
      if (lVar4 + 0x1f8 != 0) {
        *(CRunicCore **)(lVar4 + 0x1f8) = this_00;
      }
    }
    else {
      lVar2 = 0;
      if (lVar4 != 8) {
        *(CRunicCore **)(lVar4 + -8) = this_00;
        lVar2 = *(long *)(this + 0x170) + -8;
      }
      *(long *)(this + 0x170) = lVar2;
    }
  }
  return;
}
