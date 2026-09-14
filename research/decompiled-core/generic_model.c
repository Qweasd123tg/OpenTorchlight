/* Targeted Ghidra class export.
   namespace=CGenericModel
   Treat pseudocode as navigation evidence. */


/* address=00899e20
   symbol=CGenericModel::setQueryMask */

/* CGenericModel::setQueryMask(OGRE_UTILITIES::EQUERYMASK) */

void __thiscall CGenericModel::setQueryMask(CGenericModel *this,undefined4 param_2)

{
  *(undefined4 *)(this + 0x204) = param_2;
  if (*(long **)(this + 0x60) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00899e39. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(this + 0x60) + 0x158))();
    return;
  }
  return;
}



/* address=00899e50
   symbol=CGenericModel::findKey */

/* CGenericModel::findKey(int, CKeyframe*) */

uint __thiscall CGenericModel::findKey(CGenericModel *this,int param_1,CKeyframe *param_2)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;
  ulong uVar4;

  plVar2 = (long *)((long)param_1 * 0x18 + *(long *)(*(long *)(this + 0x1e0) + 0x58));
  plVar1 = (long *)*plVar2;
  uVar4 = plVar2[1] - (long)plVar1 >> 3;
  if (uVar4 != 0) {
    uVar3 = 0;
    if ((CKeyframe *)*plVar1 == param_2) {
      return 0;
    }
    while( true ) {
      uVar3 = uVar3 + 1;
      if (uVar4 <= uVar3) break;
      if ((CKeyframe *)plVar1[uVar3] == param_2) {
        return uVar3;
      }
    }
  }
  return 0xffffffff;
}



/* address=00899eb0
   symbol=CGenericModel::getValueIndexes */

/* CGenericModel::getValueIndexes(int, CKeyframe*) */

long __thiscall CGenericModel::getValueIndexes(CGenericModel *this,int param_1,CKeyframe *param_2)

{
  int iVar1;

  iVar1 = findKey(this,param_1,param_2);
  return (long)iVar1 * 0x18 + *(long *)(*(long *)(this + 0x1c8) + (long)param_1 * 0x18);
}



/* address=00899f00
   symbol=CGenericModel::getAnimationCount */

/* CGenericModel::getAnimationCount() const */

undefined4 __thiscall CGenericModel::getAnimationCount(CGenericModel *this)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x1e0) != 0) {
    uVar1 = *(undefined4 *)(*(long *)(this + 0x1e0) + 0x20);
  }
  return uVar1;
}



/* address=00899f20
   symbol=CGenericModel::getAnimationName */

/* CGenericModel::getAnimationName(unsigned int) const */

undefined8 * __thiscall CGenericModel::getAnimationName(CGenericModel *this,uint param_1)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_STRING;
  if (*(long *)(this + 0x1e0) != 0) {
    puVar1 = (undefined8 *)((ulong)param_1 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x28));
  }
  return puVar1;
}



/* address=00899f40
   symbol=CGenericModel::getKeyCount */

/* CGenericModel::getKeyCount(unsigned int) */

ulong __thiscall CGenericModel::getKeyCount(CGenericModel *this,uint param_1)

{
  long *plVar1;
  long lVar2;
  ulong uVar3;
  ulong uVar4;

  lVar2 = *(long *)(this + 0x1e0);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar4 = (*(long *)(lVar2 + 0x60) - *(long *)(lVar2 + 0x58) >> 3) * -0x5555555555555555;
    uVar3 = uVar4 & 0xffffffff;
    if (param_1 < uVar4) {
      plVar1 = (long *)(*(long *)(lVar2 + 0x58) + (ulong)param_1 * 0x18);
      uVar3 = (ulong)(plVar1[1] - *plVar1) >> 3;
    }
  }
  return uVar3;
}



/* address=00899f90
   symbol=CGenericModel::getKeyFrame */

/* CGenericModel::getKeyFrame(unsigned int, unsigned int) */

undefined8 __thiscall CGenericModel::getKeyFrame(CGenericModel *this,uint param_1,uint param_2)

{
  long *plVar1;
  long lVar2;

  lVar2 = *(long *)(this + 0x1e0);
  if (lVar2 != 0) {
    if ((ulong)param_1 <
        (ulong)((*(long *)(lVar2 + 0x60) - *(long *)(lVar2 + 0x58) >> 3) * -0x5555555555555555)) {
      plVar1 = (long *)(*(long *)(lVar2 + 0x58) + (ulong)param_1 * 0x18);
      lVar2 = *plVar1;
      if ((ulong)param_2 < (ulong)(plVar1[1] - lVar2 >> 3)) {
        return *(undefined8 *)(lVar2 + (ulong)param_2 * 8);
      }
    }
  }
  return 0;
}



/* address=00899ff0
   symbol=CGenericModel::setHighlighted */

/* non-virtual thunk to CGenericModel::setHighlighted(bool) */

void __thiscall CGenericModel::setHighlighted(CGenericModel *this,bool param_1)

{
  setHighlighted(this + -0x108,param_1);
  return;
}



/* address=0089a000
   symbol=CGenericModel::setHighlighted */

/* CGenericModel::setHighlighted(bool) */

void __thiscall CGenericModel::setHighlighted(CGenericModel *this,bool param_1)

{
  long lVar1;
  uint uVar2;
  ulong uVar3;

  lVar1 = *(long *)(this + 0x208);
  if ((int)((ulong)(*(long *)(this + 0x210) - lVar1) >> 6) != 0) {
    uVar3 = 0;
    do {
      uVar2 = (int)uVar3 + 1;
      *(bool *)(uVar3 * 0x40 + 3 + lVar1) = param_1;
      lVar1 = *(long *)(this + 0x208);
      uVar3 = (ulong)uVar2;
    } while (uVar2 < (uint)(*(long *)(this + 0x210) - lVar1 >> 6));
  }
  return;
}



/* address=0089a050
   symbol=CGenericModel::setCastsShadows */

/* CGenericModel::setCastsShadows(bool) */

void __thiscall CGenericModel::setCastsShadows(CGenericModel *this,bool param_1)

{
  long *plVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;

  lVar2 = *(long *)(this + 0x208);
  if ((int)((ulong)(*(long *)(this + 0x210) - lVar2) >> 6) != 0) {
    uVar4 = 0;
    do {
      uVar3 = (int)uVar4 + 1;
      *(bool *)(uVar4 * 0x40 + 1 + lVar2) = param_1;
      lVar2 = *(long *)(this + 0x208);
      uVar4 = (ulong)uVar3;
    } while (uVar3 < (uint)(*(long *)(this + 0x210) - lVar2 >> 6));
  }
  if (param_1) {
    plVar1 = *(long **)(this + 0x60);
    if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0089a0b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x178))(plVar1,4);
      return;
    }
  }
  else {
    plVar1 = *(long **)(this + 0x60);
    if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0089a0d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x178))(plVar1,1);
      return;
    }
  }
  return;
}



/* address=0089a0e0
   symbol=CGenericModel::getName */

/* CGenericModel::getName() */

CGenericModel * __thiscall CGenericModel::getName(CGenericModel *this)

{
  return this + 0x120;
}



/* address=0089a0f0
   symbol=CGenericModel::getTexureName */

/* CGenericModel::getTexureName() */

void CGenericModel::getTexureName(void)

{
  long lVar1;
  long lVar2;
  string *psVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  long in_RSI;
  string *in_RDI;

  lVar4 = *(long *)(in_RSI + 0x210);
  lVar2 = *(long *)(in_RSI + 0x208);
  if ((int)((ulong)(lVar4 - lVar2) >> 6) != 0) {
    uVar6 = 0;
    do {
      lVar1 = *(long *)(lVar2 + 0x10 + uVar6 * 0x40);
      if (lVar1 != 0) {
        lVar2 = Ogre::Material::getBestTechnique((ushort)lVar1,(Renderable *)0x0);
        if (lVar2 != 0) {
          lVar2 = Ogre::Technique::getPass((ushort)lVar2);
          if ((lVar2 != 0) &&
             ((short)((ulong)(*(long *)(lVar2 + 0xf0) - *(long *)(lVar2 + 0xe8)) >> 3) != 0)) {
            lVar2 = Ogre::Pass::getTextureUnitState((ushort)lVar2);
            if (lVar2 != 0) {
              psVar3 = (string *)Ogre::TextureUnitState::getTextureName();
              std::string::string(in_RDI,psVar3);
              return;
            }
          }
        }
        lVar2 = *(long *)(in_RSI + 0x208);
        lVar4 = *(long *)(in_RSI + 0x210);
      }
      uVar5 = (int)uVar6 + 1;
      uVar6 = (ulong)uVar5;
    } while (uVar5 < (uint)(lVar4 - lVar2 >> 6));
  }
  std::string::string(in_RDI,(string *)&::EMPTY_STRING);
  return;
}



/* address=0089a1d0
   symbol=CGenericModel::setRenderBehind */

/* CGenericModel::setRenderBehind(bool) */

void __thiscall CGenericModel::setRenderBehind(CGenericModel *this,bool param_1)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;

  uVar3 = KSETTINGS_NETBOOK_MODE;
  lVar2 = CMasterResourceManager::getSingleton();
  iVar1 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar2 + 0x90),uVar3);
  if ((iVar1 != 1) &&
     (lVar2 = *(long *)(this + 0x208), (int)((ulong)(*(long *)(this + 0x210) - lVar2) >> 6) != 0)) {
    uVar4 = 0;
    do {
      uVar3 = (int)uVar4 + 1;
      *(bool *)(uVar4 * 0x40 + 4 + lVar2) = param_1;
      lVar2 = *(long *)(this + 0x208);
      uVar4 = (ulong)uVar3;
    } while (uVar3 < (uint)(*(long *)(this + 0x210) - lVar2 >> 6));
  }
  return;
}



/* address=0089a250
   symbol=CGenericModel::setOpacity */

/* CGenericModel::setOpacity(float) */

void __thiscall CGenericModel::setOpacity(CGenericModel *this,float param_1)

{
  char cVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  ushort uVar8;
  long lVar9;
  uint local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;

  uVar2 = KSETTINGS_NETBOOK_MODE;
  if (param_1 == *(float *)(this + 0x228)) {
    return;
  }
  lVar6 = CMasterResourceManager::getSingleton();
  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar2);
  if ((iVar5 == 0) &&
     (lVar6 = *(long *)(this + 0x208), (int)((ulong)(*(long *)(this + 0x210) - lVar6) >> 6) != 0)) {
    local_4c = 0;
    do {
      lVar9 = (ulong)local_4c * 0x40;
      *(float *)(lVar6 + 0x34 + lVar9) = param_1;
      uVar8 = (ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar9);
      Ogre::Material::getBestTechnique(uVar8,(Renderable *)0x0);
      uVar3 = Ogre::Technique::getNumPasses();
      if (uVar3 != 0) {
        iVar5 = 0;
        do {
          while( true ) {
            uVar4 = Ogre::Material::getBestTechnique(uVar8,(Renderable *)0x0);
            lVar6 = Ogre::Technique::getPass(uVar4);
            if ((short)((ulong)(*(long *)(lVar6 + 0xf0) - *(long *)(lVar6 + 0xe8)) >> 3) != 0)
            break;
LAB_0089a320:
            iVar5 = iVar5 + 1;
            if ((int)(uint)uVar3 <= iVar5) goto LAB_0089a3e0;
          }
          uVar4 = (ushort)lVar6;
          Ogre::Pass::getTextureUnitState(uVar4);
          if (param_1 < DAT_00fa47fc) {
            if (iVar5 == 0) {
              if (*(char *)(*(long *)(this + 0x208) + 0x2f + lVar9) == '\0') {
                uVar7 = Ogre::Pass::getTextureUnitState(uVar4);
                Ogre::TextureUnitState::setAlphaOperation(DAT_00fa47fc,param_1,uVar7,2,1,4);
                Ogre::Pass::setSceneBlending(lVar6,0);
                Ogre::Pass::setAlphaRejectSettings(lVar6,7,5,0);
              }
              else {
                local_48 = param_1;
                local_44 = param_1;
                local_40 = param_1;
                local_3c = param_1;
                uVar7 = Ogre::Pass::getTextureUnitState(uVar4);
                Ogre::TextureUnitState::setColourOperationEx
                          (DAT_00fa47fc,uVar7,2,4,1,&local_48,&Ogre::ColourValue::Black);
              }
            }
            else {
              uVar7 = Ogre::Pass::getTextureUnitState(uVar4);
              Ogre::TextureUnitState::setAlphaOperation(DAT_00fa47fc,param_1,uVar7,2,1,4);
              Ogre::Pass::setSeparateSceneBlending(lVar6,7,0,1,1);
            }
            goto LAB_0089a320;
          }
          if ((*(char *)(lVar9 + *(long *)(this + 0x208) + 0x2f) == '\0') || (iVar5 != 0)) {
            if (*(char *)(lVar9 + *(long *)(this + 0x208) + 0x2e) != '\0') {
              if (iVar5 != 0) goto LAB_0089a49a;
              Ogre::Pass::setSceneBlending(lVar6,0);
              if (this[0x23b] == (CGenericModel)0x0) {
                Ogre::Pass::setAlphaRejectSettings(lVar6,7,0x96,0);
              }
              else {
                Ogre::Pass::setAlphaRejectSettings(lVar6,7,5,0);
              }
              goto LAB_0089a3a4;
            }
            if (iVar5 == 0) {
              Ogre::Pass::setSceneBlending(lVar6,4);
              goto LAB_0089a3a4;
            }
LAB_0089a49a:
            Ogre::Pass::setSeparateSceneBlending(lVar6,7,0,1,1);
            cVar1 = *(char *)(*(long *)(this + 0x208) + 0x2f + lVar9);
          }
          else {
            Ogre::Pass::setSceneBlending(lVar6,2);
LAB_0089a3a4:
            cVar1 = *(char *)(*(long *)(this + 0x208) + 0x2f + lVar9);
          }
          if (cVar1 == '\0') {
            uVar7 = Ogre::Pass::getTextureUnitState(uVar4);
            Ogre::TextureUnitState::setAlphaOperation(DAT_00fa47fc,DAT_00fa47fc,0,uVar7,2,1);
            goto LAB_0089a320;
          }
          iVar5 = iVar5 + 1;
          uVar7 = Ogre::Pass::getTextureUnitState(uVar4);
          Ogre::TextureUnitState::setColourOperation(uVar7);
        } while (iVar5 < (int)(uint)uVar3);
      }
LAB_0089a3e0:
      local_4c = local_4c + 1;
      lVar6 = *(long *)(this + 0x208);
    } while (local_4c < (uint)(*(long *)(this + 0x210) - lVar6 >> 6));
  }
  *(float *)(this + 0x228) = param_1;
  return;
}



/* address=0089a640
   symbol=CGenericModel::setLightOverride */

/* CGenericModel::setLightOverride(float) */

void __thiscall CGenericModel::setLightOverride(CGenericModel *this,float param_1)

{
  undefined8 uVar1;
  long lVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  ColourValue *pCVar6;
  long lVar7;
  uint uVar8;

  uVar8 = KSETTINGS_NETBOOK_MODE;
  lVar5 = CMasterResourceManager::getSingleton();
  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar5 + 0x90),uVar8);
  if ((iVar4 != 1) && ((int)((ulong)(*(long *)(this + 0x210) - *(long *)(this + 0x208)) >> 6) != 0))
  {
    uVar8 = 0;
    do {
      lVar7 = (ulong)uVar8 * 0x40;
      uVar1 = *(undefined8 *)(lVar7 + *(long *)(this + 0x208) + 0x10);
      uVar3 = Ogre::Material::getBestTechnique
                        ((ushort)*(undefined8 *)(lVar7 + *(long *)(this + 0x208) + 8),
                         (Renderable *)0x0);
      Ogre::Technique::getPass(uVar3);
      Ogre::Pass::getAmbient();
      Ogre::Pass::getDiffuse();
      Ogre::Pass::getSelfIllumination();
      uVar3 = Ogre::Material::getBestTechnique((ushort)uVar1,(Renderable *)0x0);
      pCVar6 = (ColourValue *)Ogre::Technique::getPass(uVar3);
      Ogre::Pass::setAmbient(pCVar6);
      Ogre::Pass::setDiffuse(pCVar6);
      Ogre::Pass::setSelfIllumination(pCVar6);
      lVar5 = *(long *)(this + 0x208);
      lVar2 = *(long *)((undefined1 *)(lVar5 + lVar7) + 0x20);
      if (lVar2 != 0) {
        param_1 = param_1 * param_1 * param_1 * param_1;
        if (param_1 <= DAT_00fc67e8) {
          *(undefined1 *)(lVar5 + lVar7) = 1;
          lVar5 = *(long *)(this + 0x208);
        }
        else {
          uVar3 = Ogre::Material::getBestTechnique((ushort)lVar2,(Renderable *)0x0);
          Ogre::Technique::getPass(uVar3);
          Ogre::Pass::setSelfIllumination(param_1,param_1,param_1);
          *(undefined1 *)(*(long *)(this + 0x208) + lVar7) = 0;
          lVar5 = *(long *)(this + 0x208);
        }
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < (uint)(*(long *)(this + 0x210) - lVar5 >> 6));
  }
  return;
}



/* address=0089a900
   symbol=CGenericModel::releaseUniqueMaterials */

/* CGenericModel::releaseUniqueMaterials() */

void __thiscall CGenericModel::releaseUniqueMaterials(CGenericModel *this)

{
  code *pcVar1;
  char cVar2;
  long lVar3;
  long *plVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  uint uVar8;

  if (this[0x224] != (CGenericModel)0x0) {
    lVar6 = *(long *)(this + 0x208);
    if ((int)((ulong)(*(long *)(this + 0x210) - lVar6) >> 6) != 0) {
      uVar8 = 0;
      do {
        lVar7 = (ulong)uVar8 * 0x40;
        if (*(long *)(lVar6 + 0x10 + lVar7) != 0) {
          plVar4 = (long *)Ogre::MaterialManager::getSingleton();
          pcVar1 = *(code **)(*plVar4 + 0xb0);
          uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar7) + 200))();
          cVar2 = (*pcVar1)(plVar4,uVar5);
          if (cVar2 != '\0') {
            (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar7) + 0xb0))();
            plVar4 = (long *)Ogre::MaterialManager::getSingleton();
            pcVar1 = *(code **)(*plVar4 + 0x88);
            uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar7) + 200))();
            (*pcVar1)(plVar4,uVar5);
          }
          lVar6 = *(long *)(this + 0x208);
        }
        lVar3 = lVar6 + lVar7;
        if (*(long *)(lVar3 + 0x18) != 0) {
          plVar4 = (long *)Ogre::MaterialManager::getSingleton();
          pcVar1 = *(code **)(*plVar4 + 0xb0);
          uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x18 + lVar7) + 200))();
          cVar2 = (*pcVar1)(plVar4,uVar5);
          if (cVar2 != '\0') {
            (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x18 + lVar7) + 0xb0))();
            plVar4 = (long *)Ogre::MaterialManager::getSingleton();
            pcVar1 = *(code **)(*plVar4 + 0x88);
            uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x18 + lVar7) + 200))();
            (*pcVar1)(plVar4,uVar5);
          }
          lVar6 = *(long *)(this + 0x208);
          lVar3 = lVar6 + lVar7;
        }
        if (*(long *)(lVar3 + 0x20) != 0) {
          plVar4 = (long *)Ogre::MaterialManager::getSingleton();
          pcVar1 = *(code **)(*plVar4 + 0xb0);
          uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x20 + lVar7) + 200))();
          cVar2 = (*pcVar1)(plVar4,uVar5);
          if (cVar2 != '\0') {
            (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x20 + lVar7) + 0xb0))();
            plVar4 = (long *)Ogre::MaterialManager::getSingleton();
            pcVar1 = *(code **)(*plVar4 + 0x88);
            uVar5 = (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x20 + lVar7) + 200))();
            (*pcVar1)(plVar4,uVar5);
          }
          lVar6 = *(long *)(this + 0x208);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < (uint)(*(long *)(this + 0x210) - lVar6 >> 6));
    }
    lVar6 = *(long *)(this + 0x68);
    if (((lVar6 != 0) && (*(int *)(lVar6 + 0x30) != 0)) && (**(long **)(lVar6 + 0x28) != 0)) {
      *(undefined1 *)(**(long **)(lVar6 + 0x28) + 0x38d4) = 1;
    }
  }
  return;
}



/* address=0089ab60
   symbol=CGenericModel::getAnimationLengthSeconds */

/* CGenericModel::getAnimationLengthSeconds(int) const */

undefined8 __thiscall CGenericModel::getAnimationLengthSeconds(CGenericModel *this,int param_1)

{
  undefined8 uVar1;

  if (((-1 < param_1) && (*(long *)(this + 0x1e0) != 0)) &&
     (param_1 < *(int *)(*(long *)(this + 0x1e0) + 0x20))) {
    if ((uint)param_1 < *(uint *)(this + 0x154)) {
      uVar1 = Ogre::AnimationState::getLength();
      return uVar1;
    }
    uVar1 = Ogre::AnimationState::getLength();
    return uVar1;
  }
  return 0;
}



/* address=0089abb0
   symbol=CGenericModel::getAnimationLength */

/* CGenericModel::getAnimationLength(int) const */

undefined8 __thiscall CGenericModel::getAnimationLength(CGenericModel *this,int param_1)

{
  getAnimationLengthSeconds(this,param_1);
  return 0;
}



/* address=0089abc0
   symbol=CGenericModel::addValueIndex */

/* CGenericModel::addValueIndex(int, CKeyframe*, int) */

void __thiscall
CGenericModel::addValueIndex(CGenericModel *this,int param_1,CKeyframe *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  ulong uVar4;
  long *plVar5;
  uint uVar6;

  iVar1 = findKey(this,param_1,param_2);
  plVar5 = (long *)((long)iVar1 * 0x18 + *(long *)(*(long *)(this + 0x1c8) + (long)param_1 * 0x18));
  uVar2 = *(uint *)(plVar5 + 1);
  if (uVar2 < *(uint *)((long)plVar5 + 0xc)) {
    pvVar3 = (void *)*plVar5;
  }
  else if (*plVar5 == 0) {
    *(uint *)((long)plVar5 + 0xc) = *(uint *)(plVar5 + 2);
    pvVar3 = operator_new__((ulong)*(uint *)(plVar5 + 2) << 2);
    *plVar5 = (long)pvVar3;
    uVar2 = *(uint *)(plVar5 + 1);
  }
  else {
    uVar6 = *(uint *)((long)plVar5 + 0xc) + (int)plVar5[2];
    pvVar3 = operator_new__((ulong)uVar6 << 2);
    if (*(int *)((long)plVar5 + 0xc) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined4 *)((long)pvVar3 + uVar4 * 4) = *(undefined4 *)(*plVar5 + uVar4 * 4);
      } while (uVar2 < *(uint *)((long)plVar5 + 0xc));
    }
    if ((void *)*plVar5 != (void *)0x0) {
      operator_delete__((void *)*plVar5);
    }
    uVar2 = *(uint *)(plVar5 + 1);
    *plVar5 = (long)pvVar3;
    *(uint *)((long)plVar5 + 0xc) = uVar6;
  }
  *(int *)((long)pvVar3 + (ulong)uVar2 * 4) = param_3;
  *(int *)(plVar5 + 1) = (int)plVar5[1] + 1;
  return;
}



/* address=0089ac90
   symbol=CGenericModel::clearProjectorPass */

/* CGenericModel::clearProjectorPass() */

void __thiscall CGenericModel::clearProjectorPass(CGenericModel *this)

{
  undefined8 uVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  int iVar9;

  lVar5 = *(long *)(this + 0x210);
  lVar6 = *(long *)(this + 0x208);
  if ((int)((ulong)(lVar5 - lVar6) >> 6) != 0) {
    uVar8 = 0;
    do {
      lVar7 = (ulong)uVar8 * 0x40;
      if (*(char *)(lVar6 + lVar7 + 0x31) != '\0') {
        uVar1 = *(undefined8 *)(lVar6 + lVar7 + 0x10);
        uVar3 = Ogre::Material::getBestTechnique((ushort)uVar1,(Renderable *)0x0);
        lVar5 = Ogre::Technique::getPass(uVar3);
        uVar2 = KSETTINGS_SHADOWS_ENABLED;
        lVar6 = *(long *)(this + 0x208);
        iVar9 = (int)*(short *)(lVar6 + lVar7 + 0x2a);
        if (iVar9 < (int)((uint)((ulong)(*(long *)(lVar5 + 0xf0) - *(long *)(lVar5 + 0xe8)) >> 3) &
                         0xffff)) {
          uVar3 = (ushort)lVar5;
          if (*(char *)(lVar6 + lVar7 + 0x30) == '\0') {
LAB_0089ad3b:
            if (iVar9 < 2) {
              Ogre::Pass::removeTextureUnitState(uVar3);
            }
            else {
              Ogre::Pass::removeTextureUnitState(uVar3);
            }
          }
          else {
            lVar6 = CMasterResourceManager::getSingleton();
            iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar2);
            if (iVar4 == 0) goto LAB_0089ad3b;
            Ogre::Pass::removeTextureUnitState(uVar3);
            Ogre::Pass::removeTextureUnitState(uVar3);
          }
          *(undefined2 *)(*(long *)(this + 0x208) + 0x28 + lVar7) = 0xffff;
          Ogre::Material::compile(SUB81(uVar1,0));
          lVar6 = *(long *)(this + 0x208);
        }
        lVar5 = *(long *)(this + 0x210);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < (uint)(lVar5 - lVar6 >> 6));
  }
  return;
}



/* address=0089ae20
   symbol=CGenericModel::setRenderToLightMap */

/* CGenericModel::setRenderToLightMap(bool) */

void __thiscall CGenericModel::setRenderToLightMap(CGenericModel *this,bool param_1)

{
  undefined1 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar2;
  long *plVar3;

  plVar3 = *(long **)(this + 0x60);
  this[0x239] = (CGenericModel)param_1;
  if (plVar3 != (long *)0x0) {
    if (param_1) {
      (**(code **)(*plVar3 + 0x140))(plVar3,0x5f);
      plVar3 = *(long **)(this + 0x60);
      uVar2 = 2;
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar3 + 0x178);
    }
    else {
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar3 + 0x140);
      (**(code **)(**(long **)(*(long *)(this + 0x68) + 0x10) + 0x540))();
      uVar1 = Ogre::RenderQueue::getDefaultQueueGroup();
      (*UNRECOVERED_JUMPTABLE)(plVar3,uVar1);
      plVar3 = *(long **)(this + 0x60);
      uVar2 = 1;
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar3 + 0x178);
    }
                    /* WARNING: Could not recover jumptable at 0x0089aea1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(plVar3,uVar2);
    return;
  }
  return;
}



/* address=0089aef0
   symbol=CGenericModel::setAmbient */

/* CGenericModel::setAmbient(Ogre::ColourValue&) */

void CGenericModel::setAmbient(ColourValue *param_1)

{
  ColourValue *pCVar1;
  long lVar2;
  uint uVar3;
  ulong uVar4;

  lVar2 = *(long *)(param_1 + 0x208);
  if ((int)((ulong)(*(long *)(param_1 + 0x210) - lVar2) >> 6) != 0) {
    uVar4 = 0;
    do {
      uVar3 = (int)uVar4 + 1;
      pCVar1 = *(ColourValue **)(uVar4 * 0x40 + 0x10 + lVar2);
      Ogre::Material::setAmbient(pCVar1);
      Ogre::Material::setDiffuse(pCVar1);
      lVar2 = *(long *)(param_1 + 0x208);
      uVar4 = (ulong)uVar3;
    } while (uVar3 < (uint)(*(long *)(param_1 + 0x210) - lVar2 >> 6));
  }
  return;
}



/* address=008a1120
   symbol=CGenericModel::_GLOBAL__I_CGenericModel */

/* CGenericModel::CGenericModel(CResourceManager*, Ogre::SceneManager*, OGRE_UTILITIES::EPRIMITIVES)
    */

void CGenericModel::_GLOBAL__I_CGenericModel(void)

{
  allocator aStack_248;
  allocator aStack_247;
  allocator aStack_246;
  allocator aStack_245;
  allocator aStack_244;
  allocator aStack_243;
  allocator aStack_242;
  allocator aStack_241;
  allocator aStack_240;
  allocator aStack_23f;
  allocator aStack_23e;
  allocator aStack_23d;
  allocator aStack_23c;
  allocator aStack_23b;
  allocator aStack_23a;
  allocator aStack_239;
  allocator aStack_238;
  allocator aStack_237;
  allocator aStack_236;
  allocator aStack_235;
  allocator aStack_234;
  allocator aStack_233;
  allocator aStack_232;
  allocator aStack_231;
  allocator aStack_230;
  allocator aStack_22f;
  allocator aStack_22e;
  allocator aStack_22d;
  allocator aStack_22c;
  allocator aStack_22b;
  allocator aStack_22a;
  allocator aStack_229;
  allocator aStack_228;
  allocator aStack_227;
  allocator aStack_226;
  allocator aStack_225;
  allocator aStack_224;
  allocator aStack_223;
  allocator aStack_222;
  allocator aStack_221;
  allocator aStack_220;
  allocator aStack_21f;
  allocator aStack_21e;
  allocator aStack_21d;
  allocator aStack_21c;
  allocator aStack_21b;
  allocator aStack_21a;
  allocator aStack_219;
  allocator aStack_218;
  allocator aStack_217;
  allocator aStack_216;
  allocator aStack_215;
  allocator aStack_214;
  allocator aStack_213;
  allocator aStack_212;
  allocator aStack_211;
  allocator aStack_210;
  allocator aStack_20f;
  allocator aStack_20e;
  allocator aStack_20d;
  allocator aStack_20c;
  allocator aStack_20b;
  allocator aStack_20a;
  allocator aStack_209;
  allocator aStack_208;
  allocator aStack_207;
  allocator aStack_206;
  allocator aStack_205;
  allocator aStack_204;
  allocator aStack_203;
  allocator aStack_202;
  allocator aStack_201;
  allocator aStack_200;
  allocator aStack_1ff;
  allocator aStack_1fe;
  allocator aStack_1fd;
  allocator aStack_1fc;
  allocator aStack_1fb;
  allocator aStack_1fa;
  allocator aStack_1f9;
  allocator aStack_1f8;
  allocator aStack_1f7;
  allocator aStack_1f6;
  allocator aStack_1f5;
  allocator aStack_1f4;
  allocator aStack_1f3;
  allocator aStack_1f2;
  allocator aStack_1f1;
  allocator aStack_1f0;
  allocator aStack_1ef;
  allocator aStack_1ee;
  allocator aStack_1ed;
  allocator aStack_1ec;
  allocator aStack_1eb;
  allocator aStack_1ea;
  allocator aStack_1e9;
  allocator aStack_1e8;
  allocator aStack_1e7;
  allocator aStack_1e6;
  allocator aStack_1e5;
  allocator aStack_1e4;
  allocator aStack_1e3;
  allocator aStack_1e2;
  allocator aStack_1e1;
  allocator aStack_1e0;
  allocator aStack_1df;
  allocator aStack_1de;
  allocator aStack_1dd;
  allocator aStack_1dc;
  allocator aStack_1db;
  allocator aStack_1da;
  allocator aStack_1d9;
  allocator aStack_1d8;
  allocator aStack_1d7;
  allocator aStack_1d6;
  allocator aStack_1d5;
  allocator aStack_1d4;
  allocator aStack_1d3;
  allocator aStack_1d2;
  allocator aStack_1d1;
  allocator aStack_1d0;
  allocator aStack_1cf;
  allocator aStack_1ce;
  allocator aStack_1cd;
  allocator aStack_1cc;
  allocator aStack_1cb;
  allocator aStack_1ca;
  allocator aStack_1c9;
  allocator aStack_1c8;
  allocator aStack_1c7;
  allocator aStack_1c6;
  allocator aStack_1c5;
  allocator aStack_1c4;
  allocator aStack_1c3;
  allocator aStack_1c2;
  allocator aStack_1c1;
  allocator aStack_1c0;
  allocator aStack_1bf;
  allocator aStack_1be;
  allocator aStack_1bd;
  allocator aStack_1bc;
  allocator aStack_1bb;
  allocator aStack_1ba;
  allocator aStack_1b9;
  allocator aStack_1b8;
  allocator aStack_1b7;
  allocator aStack_1b6;
  allocator aStack_1b5;
  allocator aStack_1b4;
  allocator aStack_1b3;
  allocator aStack_1b2;
  allocator aStack_1b1;
  allocator aStack_1b0;
  allocator aStack_1af;
  allocator aStack_1ae;
  allocator aStack_1ad;
  allocator aStack_1ac;
  allocator aStack_1ab;
  allocator aStack_1aa;
  allocator aStack_1a9;
  allocator aStack_1a8;
  allocator aStack_1a7;
  allocator aStack_1a6;
  allocator aStack_1a5;
  allocator aStack_1a4;
  allocator aStack_1a3;
  allocator aStack_1a2;
  allocator aStack_1a1;
  allocator aStack_1a0;
  allocator aStack_19f;
  allocator aStack_19e;
  allocator aStack_19d;
  allocator aStack_19c;
  allocator aStack_19b;
  allocator aStack_19a;
  allocator aStack_199;
  allocator aStack_198;
  allocator aStack_197;
  allocator aStack_196;
  allocator aStack_195;
  allocator aStack_194;
  allocator aStack_193;
  allocator aStack_192;
  allocator aStack_191;
  allocator aStack_190;
  allocator aStack_18f;
  allocator aStack_18e;
  allocator aStack_18d;
  allocator aStack_18c;
  allocator aStack_18b;
  allocator aStack_18a;
  allocator aStack_189;
  allocator aStack_188;
  allocator aStack_187;
  allocator aStack_186;
  allocator aStack_185;
  allocator aStack_184;
  allocator aStack_183;
  allocator aStack_182;
  allocator aStack_181;
  allocator aStack_180;
  allocator aStack_17f;
  allocator aStack_17e;
  allocator aStack_17d;
  allocator aStack_17c;
  allocator aStack_17b;
  allocator aStack_17a;
  allocator aStack_179;
  allocator aStack_178;
  allocator aStack_177;
  allocator aStack_176;
  allocator aStack_175;
  allocator aStack_174;
  allocator aStack_173;
  allocator aStack_172;
  allocator aStack_171;
  allocator aStack_170;
  allocator aStack_16f;
  allocator aStack_16e;
  allocator aStack_16d;
  allocator aStack_16c;
  allocator aStack_16b;
  allocator aStack_16a;
  allocator aStack_169;
  allocator aStack_168;
  allocator aStack_167;
  allocator aStack_166;
  allocator aStack_165;
  allocator aStack_164;
  allocator aStack_163;
  allocator aStack_162;
  allocator aStack_161;
  allocator aStack_160;
  allocator aStack_15f;
  allocator aStack_15e;
  allocator aStack_15d;
  allocator aStack_15c;
  allocator aStack_15b;
  allocator aStack_15a;
  allocator aStack_159;
  allocator aStack_158;
  allocator aStack_157;
  allocator aStack_156;
  allocator aStack_155;
  allocator aStack_154;
  allocator aStack_153;
  allocator aStack_152;
  allocator aStack_151;
  allocator aStack_150;
  allocator aStack_14f;
  allocator aStack_14e;
  allocator aStack_14d;
  allocator aStack_14c;
  allocator aStack_14b;
  allocator aStack_14a;
  allocator aStack_149;
  allocator aStack_148;
  allocator aStack_147;
  allocator aStack_146;
  allocator aStack_145;
  allocator aStack_144;
  allocator aStack_143;
  allocator aStack_142;
  allocator aStack_141;
  allocator aStack_140;
  allocator aStack_13f;
  allocator aStack_13e;
  allocator aStack_13d;
  allocator aStack_13c;
  allocator aStack_13b;
  allocator aStack_13a;
  allocator aStack_139;
  allocator aStack_138;
  allocator aStack_137;
  allocator aStack_136;
  allocator aStack_135;
  allocator aStack_134;
  allocator aStack_133;
  allocator aStack_132;
  allocator aStack_131;
  allocator aStack_130;
  allocator aStack_12f;
  allocator aStack_12e;
  allocator aStack_12d;
  allocator aStack_12c;
  allocator aStack_12b;
  allocator aStack_12a;
  allocator aStack_129;
  allocator aStack_128;
  allocator aStack_127;
  allocator aStack_126;
  allocator aStack_125;
  allocator aStack_124;
  allocator aStack_123;
  allocator aStack_122;
  allocator aStack_121;
  allocator aStack_120;
  allocator aStack_11f;
  allocator aStack_11e;
  allocator aStack_11d;
  allocator aStack_11c;
  allocator aStack_11b;
  allocator aStack_11a;
  allocator aStack_119;
  allocator aStack_118;
  allocator aStack_117;
  allocator aStack_116;
  allocator aStack_115;
  allocator aStack_114;
  allocator aStack_113;
  allocator aStack_112;
  allocator aStack_111;
  allocator aStack_110;
  allocator aStack_10f;
  allocator aStack_10e;
  allocator aStack_10d;
  allocator aStack_10c;
  allocator aStack_10b;
  allocator aStack_10a;
  allocator aStack_109;
  allocator aStack_108;
  allocator aStack_107;
  allocator aStack_106;
  allocator aStack_105;
  allocator aStack_104;
  allocator aStack_103;
  allocator aStack_102;
  allocator aStack_101;
  allocator aStack_100;
  allocator aStack_ff;
  allocator aStack_fe;
  allocator aStack_fd;
  allocator aStack_fc;
  allocator aStack_fb;
  allocator aStack_fa;
  allocator aStack_f9;
  allocator aStack_f8;
  allocator aStack_f7;
  allocator aStack_f6;
  allocator aStack_f5;
  allocator aStack_f4;
  allocator aStack_f3;
  allocator aStack_f2;
  allocator aStack_f1;
  allocator aStack_f0;
  allocator aStack_ef;
  allocator aStack_ee;
  allocator aStack_ed;
  allocator aStack_ec;
  allocator aStack_eb;
  allocator aStack_ea;
  allocator aStack_e9;
  allocator aStack_e8;
  allocator aStack_e7;
  allocator aStack_e6;
  allocator aStack_e5;
  allocator aStack_e4;
  allocator aStack_e3;
  allocator aStack_e2;
  allocator aStack_e1;
  allocator aStack_e0;
  allocator aStack_df;
  allocator aStack_de;
  allocator aStack_dd;
  allocator aStack_dc;
  allocator aStack_db;
  allocator aStack_da;
  allocator aStack_d9;
  allocator aStack_d8;
  allocator aStack_d7;
  allocator aStack_d6;
  allocator aStack_d5;
  allocator aStack_d4;
  allocator aStack_d3;
  allocator aStack_d2;
  allocator aStack_d1;
  allocator aStack_d0;
  allocator aStack_cf;
  allocator aStack_ce;
  allocator aStack_cd;
  allocator aStack_cc;
  allocator aStack_cb;
  allocator aStack_ca;
  allocator aStack_c9;
  allocator aStack_c8;
  allocator aStack_c7;
  allocator aStack_c6;
  allocator aStack_c5;
  allocator aStack_c4;
  allocator aStack_c3;
  allocator aStack_c2;
  allocator aStack_c1;
  allocator aStack_c0;
  allocator aStack_bf;
  allocator aStack_be;
  allocator aStack_bd;
  allocator aStack_bc;
  allocator aStack_bb;
  allocator aStack_ba;
  allocator aStack_b9;
  allocator aStack_b8;
  allocator aStack_b7;
  allocator aStack_b6;
  allocator aStack_b5;
  allocator aStack_b4;
  allocator aStack_b3;
  allocator aStack_b2;
  allocator aStack_b1;
  allocator aStack_b0;
  allocator aStack_af;
  allocator aStack_ae;
  allocator aStack_ad;
  allocator aStack_ac;
  allocator aStack_ab;
  allocator aStack_aa;
  allocator aStack_a9;
  allocator aStack_a8;
  allocator aStack_a7;
  allocator aStack_a6;
  allocator aStack_a5;
  allocator aStack_a4;
  allocator aStack_a3;
  allocator aStack_a2;
  allocator aStack_a1;
  allocator aStack_a0;
  allocator aStack_9f;
  allocator aStack_9e;
  allocator aStack_9d;
  allocator aStack_9c;
  allocator aStack_9b;
  allocator aStack_9a;
  allocator aStack_99;
  allocator aStack_98;
  allocator aStack_97;
  allocator aStack_96;
  allocator aStack_95;
  allocator aStack_94;
  allocator aStack_93;
  allocator aStack_92;
  allocator aStack_91;
  allocator aStack_90;
  allocator aStack_8f;
  allocator aStack_8e;
  allocator aStack_8d;
  allocator aStack_8c;
  allocator aStack_8b;
  allocator aStack_8a;
  allocator aStack_89;
  allocator aStack_88;
  allocator aStack_87;
  allocator aStack_86;
  allocator aStack_85;
  allocator aStack_84;
  allocator aStack_83;
  allocator aStack_82;
  allocator aStack_81;
  allocator aStack_80;
  allocator aStack_7f;
  allocator aStack_7e;
  allocator aStack_7d;
  allocator aStack_7c;
  allocator aStack_7b;
  allocator aStack_7a;
  allocator aStack_79;
  allocator aStack_78;
  allocator aStack_77;
  allocator aStack_76;
  allocator aStack_75;
  allocator aStack_74;
  allocator aStack_73;
  allocator aStack_72;
  allocator aStack_71;
  allocator aStack_70;
  allocator aStack_6f;
  allocator aStack_6e;
  allocator aStack_6d;
  allocator aStack_6c;
  allocator aStack_6b;
  allocator aStack_6a;
  allocator aStack_69;
  allocator aStack_68;
  allocator aStack_67;
  allocator aStack_66;
  allocator aStack_65;
  allocator aStack_64;
  allocator aStack_63;
  allocator aStack_62;
  allocator aStack_61;
  allocator aStack_60;
  allocator aStack_5f;
  allocator aStack_5e;
  allocator aStack_5d;
  allocator aStack_5c;
  allocator aStack_5b;
  allocator aStack_5a;
  allocator aStack_59;
  allocator aStack_58;
  allocator aStack_57;
  allocator aStack_56;
  allocator aStack_55;
  allocator aStack_54;
  allocator aStack_53;
  allocator aStack_52;
  allocator aStack_51;
  allocator aStack_50;
  allocator aStack_4f;
  allocator aStack_4e;
  allocator aStack_4d;
  allocator aStack_4c;
  allocator aStack_4b;
  allocator aStack_4a;
  allocator aStack_49;
  allocator aStack_48;
  allocator aStack_47;
  allocator aStack_46;
  allocator aStack_45;
  allocator aStack_44;
  allocator aStack_43;
  allocator aStack_42;
  allocator aStack_41;
  allocator aStack_40;
  allocator aStack_3f;
  allocator aStack_3e;
  allocator aStack_3d;
  allocator aStack_3c;
  allocator aStack_3b;
  allocator aStack_3a;
  allocator aStack_39;
  allocator aStack_38;
  allocator aStack_37;
  allocator aStack_36;
  allocator aStack_35;
  allocator aStack_34;
  allocator aStack_33;
  allocator aStack_32;
  allocator aStack_31;
  allocator aStack_30;
  allocator aStack_2f;
  allocator aStack_2e;
  allocator aStack_2d;
  allocator aStack_2c;
  allocator aStack_2b;
  allocator aStack_2a;
  allocator aStack_29;
  allocator aStack_28;
  allocator aStack_27;
  allocator aStack_26;
  allocator aStack_25;
  allocator aStack_24;
  allocator aStack_23;
  allocator aStack_22;
  allocator aStack_21;
  allocator aStack_20;
  allocator aStack_1f;
  allocator aStack_1e;
  allocator aStack_1d;
  allocator aStack_1c;
  allocator aStack_1b;
  allocator aStack_1a;
  allocator aStack_19;
  allocator aStack_18;
  allocator aStack_17;
  allocator aStack_16;
  allocator aStack_15;
  allocator aStack_14;
  allocator aStack_13;
  allocator aStack_12;
  allocator aStack_11;
  allocator aStack_10;
  allocator aStack_f;
  allocator aStack_e;
  allocator aStack_d;
  allocator aStack_c;
  allocator aStack_b;
  allocator aStack_a;
  allocator aStack_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_248);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_245);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_244);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_243);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_23e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_23c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_23b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_239);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_237);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_235)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_230);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_226);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_225);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_224);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_223);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_222);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_221);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_220);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_21f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_21e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_21d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_21c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_21b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_21a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1b9);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1ad)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1ab)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1aa)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1a9)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1a8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1a7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1a6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_198)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_196)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_18a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_188);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_187
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_184)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_182
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_181)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_180);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_178
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_177);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_170);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_169);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_162);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_161);
  std::wstring::wstring((wstring_conflict *)&DAT_014835c8,L"ITEM",&aStack_160);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_15c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_157);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_156);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_155);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_73);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_71)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_6f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_64)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_5f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_56);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_51);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_4d);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_47);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_44);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_3e);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_3d);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_3c);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_3b
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_3a);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_39);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_38);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_37);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_36);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_35);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_34);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_33);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_32);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_31);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_30);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_2f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_2e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_2d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_2c);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_2b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_2a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_29);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_28);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_27);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_26);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_25);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_24);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_23);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_22);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_21);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_20);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_1f);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_1e);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_1d);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_1c);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_1b);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_1a);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_19);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_18);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_17);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_16);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_15);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_14);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_f);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_a);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}



/* address=008a1130
   symbol=CGenericModel::unloadModel */

/* CGenericModel::unloadModel() */

void __thiscall CGenericModel::unloadModel(CGenericModel *this)

{
  CAnimationSet *pCVar1;
  CMasterResourceManager *this_00;
  Entity *pEVar2;

  pCVar1 = *(CAnimationSet **)(this + 0x1e0);
  if (pCVar1 != (CAnimationSet *)0x0) {
    this_00 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
    CMasterResourceManager::removeAnimationSet(this_00,pCVar1);
  }
  pEVar2 = *(Entity **)(this + 0x230);
  *(undefined8 *)(this + 0x1e0) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x1b8) = *(undefined8 *)(this + 0x1b0);
  if (pEVar2 == (Entity *)0x0) {
    pEVar2 = *(Entity **)(this + 0x60);
    if (pEVar2 == (Entity *)0x0) goto LAB_008a11ab;
  }
  else {
    *(Entity **)(this + 0x60) = pEVar2;
  }
  OGRE_UTILITIES::detachEntityFromParent(pEVar2);
  (**(code **)(**(long **)(*(long *)(this + 0x68) + 0x10) + 0x288))
            (*(long **)(*(long *)(this + 0x68) + 0x10),*(undefined8 *)(this + 0x60));
  *(undefined8 *)(this + 0x60) = 0;
LAB_008a11ab:
  wcslen(L"");
  std::wstring::assign((wchar_t *)(this + 0x110),0x1001608);
  wcslen(L"");
  std::wstring::assign((wchar_t *)(this + 0x118),0x1001608);
  return;
}



/* address=008a1200
   symbol=CGenericModel::loadPrefabType */

/* CGenericModel::loadPrefabType(OGRE_UTILITIES::EPRIMITIVES) */

void __thiscall CGenericModel::loadPrefabType(CGenericModel *this,undefined4 param_2)

{
  long *plVar1;

  unloadModel(this);
  std::wstring::assign((wstring_conflict *)(this + 0x110));
                    /* try { // try from 008a123b to 008a125e has its CatchHandler @ 008a12a5 */
  plVar1 = (long *)OGRE_UTILITIES::createEntity
                             (*(undefined8 *)(this + 0x140),param_2,*(undefined4 *)(this + 0x204),
                              &DAT_00faa818);
  *(long **)(this + 0x60) = plVar1;
  (**(code **)(*plVar1 + 0x88))(plVar1);
  std::string::assign((string *)(this + 0x120));
  *(undefined1 *)(*(long *)(this + 0x60) + 0xc0) = 0;
  setQueryMask(this,8);
  CSceneNodeObject::sceneNodeAttachEntity((CSceneNodeObject *)this,*(Entity **)(this + 0x60));
  (**(code **)(*(long *)this + 0x1c8))(this);
  setRenderToLightMap(this,(bool)this[0x239]);
  return;
}



/* address=008a1320
   symbol=CGenericModel::queueBlendAnimation */

/* CGenericModel::queueBlendAnimation(unsigned int, bool, float, float) */

void __thiscall
CGenericModel::queueBlendAnimation
          (CGenericModel *this,uint param_1,bool param_2,float param_3,float param_4)

{
  CRunicCore *this_00;
  void *pvVar1;
  long lVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  uint uVar7;

  if ((param_1 != 0xffffffff) && (*(int *)(this + 0x150) != 0)) {
    fVar4 = (float)getAnimationLengthSeconds(this,param_1);
    fVar4 = (float)((uint)param_3 & -(uint)(fVar4 != 0.0));
    if (param_1 < *(uint *)(this + 0x154)) {
      *(bool *)(*(long *)((ulong)param_1 * 8 + *(long *)(this + 0x148)) + 0x2d) = param_2;
    }
    else {
      *(bool *)(**(long **)(this + 0x148) + 0x2d) = param_2;
    }
    fVar5 = (float)Ogre::AnimationState::getLength();
    fVar6 = fVar5;
    if (fVar4 <= fVar5) {
      fVar6 = fVar4;
    }
    this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a140b to 008a140f has its CatchHandler @ 008a1596 */
    CRunicCore::CRunicCore(this_00);
    *(undefined ***)this_00 = &PTR__CActiveAnimation_00fd1750;
    *(uint *)(this_00 + 0x10) = param_1;
    *(undefined4 *)(this_00 + 0x20) = 0;
    *(float *)(this_00 + 0x18) = fVar5;
    this_00[0x24] = (CRunicCore)param_2;
    this_00[0x27] = (CRunicCore)0x0;
    *(float *)(this_00 + 0x1c) = fVar5;
    this_00[0x28] = (CRunicCore)0x0;
    this_00[0x29] = (CRunicCore)0x0;
    this_00[0x2a] = (CRunicCore)0x0;
    *(float *)(this_00 + 0x38) = param_4;
    this_00[0x25] = (CRunicCore)0x0;
    this_00[0x26] = (CRunicCore)0x1;
    uVar7 = DAT_00fd1a30;
    *(undefined4 *)(this_00 + 0x34) = 0x3f800000;
    uVar7 = ~-(uint)(0.0 < fVar6) & uVar7 | (uint)fVar6 & -(uint)(0.0 < fVar6);
    *(uint *)(this_00 + 0x2c) = uVar7;
    *(uint *)(this_00 + 0x30) = uVar7;
    lVar3 = *(long *)(this + 0x170);
    if (lVar3 == *(long *)(this + 0x178)) {
      lVar3 = *(long *)(this + 0x188);
      if (lVar3 - *(long *)(this + 0x160) >> 3 == 0) {
        std::deque<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_reallocate_map
                  ((deque<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),1,
                   true);
        lVar3 = *(long *)(this + 0x188);
      }
      pvVar1 = operator_new(0x200);
      *(void **)(lVar3 + -8) = pvVar1;
      lVar3 = *(long *)(this + 0x188);
      *(long *)(this + 0x188) = lVar3 + -8;
      lVar3 = *(long *)(lVar3 + -8);
      *(long *)(this + 0x178) = lVar3;
      *(long *)(this + 0x180) = lVar3 + 0x200;
      *(long *)(this + 0x170) = lVar3 + 0x1f8;
      if (lVar3 + 0x1f8 != 0) {
        *(CRunicCore **)(lVar3 + 0x1f8) = this_00;
      }
    }
    else {
      lVar2 = 0;
      if (lVar3 != 8) {
        *(CRunicCore **)(lVar3 + -8) = this_00;
        lVar2 = *(long *)(this + 0x170) + -8;
      }
      *(long *)(this + 0x170) = lVar2;
    }
  }
  return;
}



/* address=008a15b0
   symbol=CGenericModel::activeAnimations */

/* CGenericModel::activeAnimations() const */

long __thiscall CGenericModel::activeAnimations(CGenericModel *this)

{
  return (*(long *)(this + 0x1a8) - *(long *)(this + 0x188) >> 3) * 0x40 + -0x40 +
         (*(long *)(this + 0x180) - *(long *)(this + 0x170) >> 3) +
         (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3);
}



/* address=008a1600
   symbol=CGenericModel::AddKey */

/* WARNING: Removing unreachable block (ram,0x008a16ea) */
/* CGenericModel::AddKey(unsigned int, CDataGroup*) */

void __thiscall CGenericModel::AddKey(CGenericModel *this,uint param_1,CDataGroup *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  CKeyframe *this_00;
  long lVar3;
  long lVar4;
  ulong uVar5;
  undefined8 *puVar6;
  vector<CKeyframe*,std::allocator<CKeyframe*>> *pvVar7;
  CKeyframe *local_40 [2];

  lVar3 = *(long *)(this + 0x1e0);
  if (lVar3 != 0) {
    if ((ulong)((*(long *)(lVar3 + 0x60) - *(long *)(lVar3 + 0x58) >> 3) * -0x5555555555555555) <=
        (ulong)param_1) {
      uVar5 = (ulong)(param_1 + 1);
      puVar2 = *(undefined8 **)(lVar3 + 0x60);
      lVar4 = (long)puVar2 - *(long *)(lVar3 + 0x58) >> 3;
      if (uVar5 < (ulong)(lVar4 * -0x5555555555555555)) {
        puVar1 = (undefined8 *)(*(long *)(lVar3 + 0x58) + uVar5 * 0x18);
        for (puVar6 = puVar1; puVar2 != puVar6; puVar6 = puVar6 + 3) {
          if ((void *)*puVar6 != (void *)0x0) {
            operator_delete((void *)*puVar6);
          }
        }
        *(undefined8 **)(lVar3 + 0x60) = puVar1;
      }
      else {
                    /* try { // try from 008a1782 to 008a1786 has its CatchHandler @ 008a179c */
        std::
        vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
        ::_M_fill_insert((vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
                          *)(lVar3 + 0x58),puVar2,uVar5 + lVar4 * 0x5555555555555555);
      }
    }
    this_00 = (CKeyframe *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a170b to 008a170f has its CatchHandler @ 008a17af */
    CKeyframe::CKeyframe(this_00,param_1,param_2);
    pvVar7 = (vector<CKeyframe*,std::allocator<CKeyframe*>> *)
             ((ulong)param_1 * 0x18 + *(long *)(*(long *)(this + 0x1e0) + 0x58));
    puVar2 = *(undefined8 **)(pvVar7 + 8);
    if (puVar2 == *(undefined8 **)(pvVar7 + 0x10)) {
      local_40[0] = this_00;
      std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux(pvVar7,puVar2,local_40);
    }
    else {
      lVar3 = 0;
      if (puVar2 != (undefined8 *)0x0) {
        *puVar2 = this_00;
        lVar3 = *(long *)(pvVar7 + 8);
      }
      *(long *)(pvVar7 + 8) = lVar3 + 8;
    }
  }
  return;
}



/* address=008a17d0
   symbol=CGenericModel::generateExtremes */

/* CGenericModel::generateExtremes(unsigned long, bool) */

void __thiscall CGenericModel::generateExtremes(CGenericModel *this,ulong param_1,bool param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint uVar4;
  int iVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  undefined8 *puVar9;
  long lVar10;
  int iVar11;
  uint uVar12;
  bool bVar13;
  uint local_90;
  void *local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 *local_58;
  undefined8 *local_50;
  undefined8 local_48;

  uVar4 = Ogre::Entity::getNumSubEntities();
  local_58 = (undefined8 *)0x0;
  local_50 = (undefined8 *)0x0;
  local_48 = 0;
  local_78 = (void *)0x0;
  local_70 = 0;
  local_68 = 0;
                    /* try { // try from 008a183b to 008a183f has its CatchHandler @ 008a1abd */
  std::
  vector<std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>,std::allocator<std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>>>
  ::_M_fill_insert((vector<std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>,std::allocator<std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>>>
                    *)&local_58,0,uVar4,&local_78);
  if (local_78 != (void *)0x0) {
    operator_delete(local_78);
  }
  if (uVar4 != 0) {
    uVar12 = 0;
    local_90 = uVar4;
    do {
      local_90 = local_90 - 1;
                    /* try { // try from 008a1877 to 008a1a58 has its CatchHandler @ 008a1ae1 */
      Ogre::Entity::getSubEntity((uint)*(undefined8 *)(this + 0x60));
      uVar6 = Ogre::SubEntity::getSubMesh();
      Ogre::SubMesh::generateExtremes(uVar6);
      lVar7 = Ogre::SubEntity::getSubMesh();
      iVar11 = (int)(*(long *)(lVar7 + 0x50) - *(long *)(lVar7 + 0x48) >> 2) * -0x55555555;
      iVar5 = iVar11 + -1;
      if (-1 < iVar5) {
        lVar7 = (long)iVar5 * 0xc;
        iVar5 = iVar11 + -2;
        do {
          while( true ) {
            lVar8 = Ogre::SubEntity::getSubMesh();
            puVar9 = (undefined8 *)(lVar7 + *(long *)(lVar8 + 0x48));
            puVar1 = (undefined8 *)local_58[(ulong)local_90 * 3 + 1];
            if (puVar1 != (undefined8 *)local_58[(ulong)local_90 * 3 + 2]) break;
            std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux();
            lVar7 = lVar7 + -0xc;
            bVar13 = iVar5 < 0;
            iVar5 = iVar5 + -1;
            if (bVar13) goto LAB_008a1948;
          }
          lVar8 = 0;
          if (puVar1 != (undefined8 *)0x0) {
            *puVar1 = *puVar9;
            *(undefined4 *)(puVar1 + 1) = *(undefined4 *)(puVar9 + 1);
            lVar8 = local_58[(ulong)local_90 * 3 + 1];
          }
          lVar7 = lVar7 + -0xc;
          local_58[(ulong)local_90 * 3 + 1] = lVar8 + 0xc;
          bVar13 = -1 < iVar5;
          iVar5 = iVar5 + -1;
        } while (bVar13);
      }
LAB_008a1948:
      uVar12 = uVar12 + 1;
    } while (uVar12 < uVar4);
  }
  puVar1 = local_58;
  puVar9 = local_50;
  puVar2 = local_50;
  if ((param_2) && (uVar4 != 0)) {
    lVar7 = 0;
    local_90 = 0;
    do {
      Ogre::Entity::getSubEntity((uint)*(undefined8 *)(this + 0x60));
      uVar6 = Ogre::SubEntity::getSubMesh();
      Ogre::SubMesh::generateExtremes(uVar6);
      lVar8 = Ogre::SubEntity::getSubMesh();
      *(undefined8 *)(lVar8 + 0x50) = *(undefined8 *)(lVar8 + 0x48);
      lVar8 = *(long *)(lVar7 + (long)local_58);
      if ((((long *)(lVar7 + (long)local_58))[1] - lVar8 >> 2) * -0x5555555555555555 != 0) {
        uVar6 = 0;
        do {
          puVar1 = (undefined8 *)(lVar8 + uVar6 * 0xc);
          lVar8 = Ogre::SubEntity::getSubMesh();
          puVar9 = *(undefined8 **)(lVar8 + 0x50);
          if (puVar9 == *(undefined8 **)(lVar8 + 0x58)) {
            std::vector<Ogre::Vector3,std::allocator<Ogre::Vector3>>::_M_insert_aux
                      ((vector<Ogre::Vector3,std::allocator<Ogre::Vector3>> *)(lVar8 + 0x48),puVar9,
                       puVar1);
          }
          else {
            lVar10 = 0;
            if (puVar9 != (undefined8 *)0x0) {
              *puVar9 = *puVar1;
              *(undefined4 *)(puVar9 + 1) = *(undefined4 *)(puVar1 + 1);
              lVar10 = *(long *)(lVar8 + 0x50);
            }
            *(long *)(lVar8 + 0x50) = lVar10 + 0xc;
          }
          uVar6 = (ulong)((int)uVar6 + 1);
          lVar8 = *(long *)(lVar7 + (long)local_58);
        } while (uVar6 < (ulong)((((long *)(lVar7 + (long)local_58))[1] - lVar8 >> 2) *
                                -0x5555555555555555));
      }
      local_90 = local_90 + 1;
      lVar7 = lVar7 + 0x18;
      puVar1 = local_58;
      puVar9 = local_50;
      puVar2 = local_50;
    } while (local_90 < uVar4);
  }
  for (; puVar3 = local_50, local_50 != puVar1; puVar1 = puVar1 + 3) {
    local_50 = puVar2;
    if ((void *)*puVar1 != (void *)0x0) {
      operator_delete((void *)*puVar1);
    }
    puVar9 = local_58;
    puVar2 = local_50;
    local_50 = puVar3;
  }
  if (puVar9 != (undefined8 *)0x0) {
    local_50 = puVar2;
    operator_delete(puVar9);
  }
  return;
}



/* address=008a22c0
   symbol=CGenericModel::getAnimationNameByPath */

/* WARNING: Removing unreachable block (ram,0x008a2481) */
/* WARNING: Removing unreachable block (ram,0x008a24a3) */
/* CGenericModel::getAnimationNameByPath(std::wstring const&) const */

undefined8 * __thiscall
CGenericModel::getAnimationNameByPath(CGenericModel *this,wstring_conflict *param_1)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  allocator *paVar8;
  bool bVar9;
  wchar_t *local_58 [2];
  wchar_t *local_48 [3];

  lVar5 = *(long *)(this + 0x1e0);
  if ((lVar5 != 0) && (*(long *)(lVar5 + 0x48) - *(long *)(lVar5 + 0x40) >> 3 != 0)) {
    uVar6 = 0;
    uVar7 = 0;
    do {
      STRINGS::StringUpper((STRINGS *)local_58,param_1);
                    /* try { // try from 008a2375 to 008a2379 has its CatchHandler @ 008a248e */
      STRINGS::StringUpper
                ((STRINGS *)local_48,
                 (wstring_conflict *)(uVar6 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x40)));
      pwVar2 = local_48[0];
      bVar9 = false;
      paVar1 = (allocator *)(local_48[0] + -6);
      paVar8 = (allocator *)(local_58[0] + -6);
      if (*(size_t *)(local_48[0] + -6) == *(size_t *)(local_58[0] + -6)) {
        iVar4 = wmemcmp(local_48[0],local_58[0],*(size_t *)(local_48[0] + -6));
        bVar9 = iVar4 == 0;
      }
      if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar2 = pwVar2 + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy(paVar1);
          paVar8 = (allocator *)(local_58[0] + -6);
        }
        else {
          paVar8 = (allocator *)(local_58[0] + -6);
        }
      }
      if (paVar8 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        paVar1 = paVar8 + 0x10;
        iVar4 = *(int *)paVar1;
        *(int *)paVar1 = *(int *)paVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy(paVar8);
        }
      }
      if (bVar9) {
        lVar5 = *(long *)(this + 0x1e0);
        if (uVar6 < (ulong)(*(long *)(lVar5 + 0x30) - *(long *)(lVar5 + 0x28) >> 3)) {
          return (undefined8 *)(*(long *)(lVar5 + 0x28) + uVar6 * 8);
        }
      }
      else {
        lVar5 = *(long *)(this + 0x1e0);
      }
      uVar7 = uVar7 + 1;
      uVar6 = (ulong)uVar7;
    } while (uVar6 < (ulong)(*(long *)(lVar5 + 0x48) - *(long *)(lVar5 + 0x40) >> 3));
  }
  return &::EMPTY_STRING;
}



/* address=008a25c0
   symbol=CGenericModel::animationExists */

/* WARNING: Removing unreachable block (ram,0x008a271b) */
/* WARNING: Removing unreachable block (ram,0x008a2739) */
/* CGenericModel::animationExists(std::string const&) const */

undefined8 __thiscall CGenericModel::animationExists(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  char *local_58 [2];
  char *local_48 [3];

  bVar8 = 0;
  if ((*(long *)(this + 0x1e0) != 0) && (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0)) {
    uVar4 = 0;
    do {
      STRINGS::StringUpper((STRINGS *)local_58,param_1);
                    /* try { // try from 008a2652 to 008a2656 has its CatchHandler @ 008a2726 */
      STRINGS::StringUpper
                ((STRINGS *)local_48,
                 (string *)((ulong)uVar4 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x28)));
      bVar7 = false;
      lVar3 = *(long *)(local_48[0] + -0x18);
      if (lVar3 == *(long *)(local_58[0] + -0x18)) {
        bVar7 = true;
        pcVar5 = local_48[0];
        pcVar6 = local_58[0];
        do {
          if (lVar3 == 0) break;
          lVar3 = lVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
          pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
        } while (bVar7);
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (bVar7) {
        return 1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
  }
  return 0;
}



/* address=008a2750
   symbol=CGenericModel::getAnimationLengthSeconds */

/* WARNING: Removing unreachable block (ram,0x008a28b0) */
/* WARNING: Removing unreachable block (ram,0x008a28ce) */
/* CGenericModel::getAnimationLengthSeconds(std::string const&) const */

undefined8 __thiscall CGenericModel::getAnimationLengthSeconds(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  undefined8 uVar9;
  char *local_58 [2];
  char *local_48 [3];

  bVar8 = 0;
  if ((*(long *)(this + 0x1e0) != 0) && (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0)) {
    uVar4 = 0;
    do {
      STRINGS::StringUpper((STRINGS *)local_58,param_1);
                    /* try { // try from 008a27e2 to 008a27e6 has its CatchHandler @ 008a28bb */
      STRINGS::StringUpper
                ((STRINGS *)local_48,
                 (string *)((ulong)uVar4 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x28)));
      bVar7 = false;
      lVar3 = *(long *)(local_48[0] + -0x18);
      if (lVar3 == *(long *)(local_58[0] + -0x18)) {
        bVar7 = true;
        pcVar5 = local_48[0];
        pcVar6 = local_58[0];
        do {
          if (lVar3 == 0) break;
          lVar3 = lVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
          pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
        } while (bVar7);
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (bVar7) {
        uVar9 = getAnimationLengthSeconds(this,uVar4);
        return uVar9;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
  }
  return 0;
}



/* address=008a28e0
   symbol=CGenericModel::getAnimationLength */

/* WARNING: Removing unreachable block (ram,0x008a2a35) */
/* WARNING: Removing unreachable block (ram,0x008a2a53) */
/* CGenericModel::getAnimationLength(std::string const&) const */

long __thiscall CGenericModel::getAnimationLength(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  float fVar9;
  char *local_58 [2];
  char *local_48 [3];

  bVar8 = 0;
  if (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0) {
    uVar4 = 0;
    do {
      STRINGS::StringUpper((STRINGS *)local_58,param_1);
                    /* try { // try from 008a2962 to 008a2966 has its CatchHandler @ 008a2a40 */
      STRINGS::StringUpper
                ((STRINGS *)local_48,
                 (string *)((ulong)uVar4 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x28)));
      bVar7 = false;
      lVar3 = *(long *)(local_48[0] + -0x18);
      if (lVar3 == *(long *)(local_58[0] + -0x18)) {
        bVar7 = true;
        pcVar5 = local_48[0];
        pcVar6 = local_58[0];
        do {
          if (lVar3 == 0) break;
          lVar3 = lVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
          pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
        } while (bVar7);
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (bVar7) {
        fVar9 = (float)getAnimationLengthSeconds(this,uVar4);
        return (long)fVar9;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
  }
  return 0;
}



/* address=008a2a60
   symbol=CGenericModel::CGenericModel */

/* CGenericModel::CGenericModel(CResourceManager*, Ogre::SceneManager*, OGRE_UTILITIES::EPRIMITIVES)
    */

void __thiscall
CGenericModel::CGenericModel
          (CGenericModel *this,CResourceManager *param_1,SceneManager *param_2,undefined4 param_4)

{
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,param_2);
  *(undefined ***)this = &PTR__CGenericModel_00fd1470;
  *(undefined ***)(this + 0x100) = &PTR__CGenericModel_00fd1668;
  *(undefined ***)(this + 0x108) = &PTR__CGenericModel_00fd1698;
                    /* try { // try from 008a2ac9 to 008a2acd has its CatchHandler @ 008a2dd7 */
  std::wstring::wstring((wstring_conflict *)(this + 0x110),L"",local_39);
                    /* try { // try from 008a2ae2 to 008a2ae6 has its CatchHandler @ 008a2dd2 */
  std::wstring::wstring((wstring_conflict *)(this + 0x118),L"",&local_3a);
                    /* try { // try from 008a2afb to 008a2aff has its CatchHandler @ 008a2dcd */
  std::string::string((string *)(this + 0x120),"",&local_3b);
                    /* try { // try from 008a2b14 to 008a2b18 has its CatchHandler @ 008a2dc8 */
  std::string::string((string *)(this + 0x128),"",&local_3c);
  *(SceneManager **)(this + 0x140) = param_2;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  *(undefined4 *)(this + 0x158) = 10;
  *(undefined8 *)(this + 0x160) = 0;
  *(undefined8 *)(this + 0x168) = 0;
  *(undefined8 *)(this + 0x170) = 0;
  *(undefined8 *)(this + 0x178) = 0;
  *(undefined8 *)(this + 0x180) = 0;
  *(undefined8 *)(this + 0x188) = 0;
  *(undefined8 *)(this + 400) = 0;
  *(undefined8 *)(this + 0x198) = 0;
  *(undefined8 *)(this + 0x1a0) = 0;
  *(undefined8 *)(this + 0x1a8) = 0;
                    /* try { // try from 008a2bd9 to 008a2bdd has its CatchHandler @ 008a2dc3 */
  std::_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_initialize_map
            ((_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),0);
  *(undefined8 *)(this + 0x1b0) = 0;
  *(undefined8 *)(this + 0x1b8) = 0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined8 *)(this + 0x1e0) = 0;
  this[0x1e8] = (CGenericModel)0x0;
  this[0x1e9] = (CGenericModel)0x0;
  *(undefined4 *)(this + 0x204) = 8;
  *(undefined8 *)(this + 0x208) = 0;
  *(undefined8 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x218) = 0;
  *(undefined4 *)(this + 0x220) = 1;
  this[0x224] = (CGenericModel)0x0;
  *(undefined4 *)(this + 0x228) = 0x3f800000;
  *(undefined8 *)(this + 0x230) = 0;
  this[0x238] = (CGenericModel)0x0;
  this[0x239] = (CGenericModel)0x0;
  this[0x23a] = (CGenericModel)0x0;
  this[0x23b] = (CGenericModel)0x0;
  this[0x23c] = (CGenericModel)0x1;
  *(undefined4 *)(this + 0x240) = 0x3f800000;
  *(undefined4 *)(this + 0x244) = 0;
  *(undefined4 *)(this + 0x248) = 0;
  *(undefined4 *)(this + 0x24c) = 0x3c7c0fc1;
  this[0x82] = (CGenericModel)0x1;
  if (param_1 != (CResourceManager *)0x0) {
    if (*(long *)(this + 0x140) == 0) {
      *(undefined8 *)(this + 0x140) = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
    }
                    /* try { // try from 008a2cf2 to 008a2cf6 has its CatchHandler @ 008a2d31 */
    loadPrefabType(this,param_4);
  }
  return;
}



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



/* address=008a2fc0
   symbol=CGenericModel::setTextureOverride */

/* WARNING: Removing unreachable block (ram,0x008a3242) */
/* WARNING: Removing unreachable block (ram,0x008a3222) */
/* CGenericModel::setTextureOverride(Ogre::TexturePtr, std::string, std::string) */

void __thiscall
CGenericModel::setTextureOverride
          (CGenericModel *this,undefined8 param_2,ulong *param_3,ulong *param_4)

{
  int *piVar1;
  undefined8 uVar2;
  ushort uVar3;
  int iVar4;
  long lVar5;
  TexturePtr *pTVar6;
  long lVar7;
  uint uVar8;
  long local_58 [2];
  long local_48 [3];

  lVar5 = *(long *)(this + 0x208);
  if ((int)((ulong)(*(long *)(this + 0x210) - lVar5) >> 6) != 0) {
    uVar8 = 0;
    do {
      lVar7 = (ulong)uVar8 * 0x40;
      uVar2 = *(undefined8 *)(lVar5 + 0x10 + lVar7);
      iVar4 = std::string::compare((char *)param_3);
      if (iVar4 == 0) {
LAB_008a308b:
        iVar4 = std::string::compare((char *)param_4);
        if (iVar4 != 0) {
          STRINGS::StringUpper
                    ((STRINGS *)local_58,(string *)(lVar7 + *(long *)(this + 0x208) + 0x38));
                    /* try { // try from 008a30c2 to 008a30c6 has its CatchHandler @ 008a322d */
          lVar5 = std::string::find((char *)local_58,*param_4,0);
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar4 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
          }
          if (lVar5 != -1) goto LAB_008a3048;
        }
        uVar3 = Ogre::Material::getBestTechnique((ushort)uVar2,(Renderable *)0x0);
        lVar5 = Ogre::Technique::getPass(uVar3);
        if ((short)((ulong)(*(long *)(lVar5 + 0xf0) - *(long *)(lVar5 + 0xe8)) >> 3) != 0) {
          pTVar6 = (TexturePtr *)Ogre::Pass::getTextureUnitState((ushort)lVar5);
          Ogre::TextureUnitState::_setTexturePtr(pTVar6);
        }
        lVar5 = *(long *)(this + 0x208);
        lVar7 = *(long *)(lVar5 + 0x18 + lVar7);
        if (lVar7 != 0) {
          uVar3 = Ogre::Material::getBestTechnique((ushort)lVar7,(Renderable *)0x0);
          lVar5 = Ogre::Technique::getPass(uVar3);
          if ((short)((ulong)(*(long *)(lVar5 + 0xf0) - *(long *)(lVar5 + 0xe8)) >> 3) != 0) {
            pTVar6 = (TexturePtr *)Ogre::Pass::getTextureUnitState((ushort)lVar5);
            Ogre::TextureUnitState::_setTexturePtr(pTVar6);
          }
          goto LAB_008a3048;
        }
      }
      else {
        STRINGS::StringUpper((STRINGS *)local_48,(string *)(lVar7 + *(long *)(this + 0x208) + 0x38))
        ;
                    /* try { // try from 008a3027 to 008a302b has its CatchHandler @ 008a320d */
        lVar5 = std::string::find((char *)local_48,*param_3,0);
        if ((allocator *)(local_48[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_48[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
          }
        }
        if (lVar5 == -1) goto LAB_008a308b;
LAB_008a3048:
        lVar5 = *(long *)(this + 0x208);
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < (uint)(*(long *)(this + 0x210) - lVar5 >> 6));
  }
  return;
}



/* address=008a3430
   symbol=CGenericModel::setTextureOverrideSingle */

/* WARNING: Removing unreachable block (ram,0x008a36c3) */
/* WARNING: Removing unreachable block (ram,0x008a36dc) */
/* WARNING: Removing unreachable block (ram,0x008a36ce) */
/* CGenericModel::setTextureOverrideSingle(std::string, Ogre::TexturePtr) */

void CGenericModel::setTextureOverrideSingle(long param_1,string *param_2)

{
  int *piVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  ushort uVar5;
  TexturePtr *pTVar6;
  undefined8 uVar7;
  bool bVar8;
  long lVar9;
  byte *pbVar10;
  byte *pbVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  byte bVar15;
  byte *local_68 [2];
  long local_58 [2];
  long local_48 [3];

  bVar15 = 0;
  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 008a345c to 008a3460 has its CatchHandler @ 008a36b0 */
  std::string::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  lVar9 = *(long *)(param_1 + 0x208);
  if ((int)((ulong)(*(long *)(param_1 + 0x210) - lVar9) >> 6) != 0) {
    uVar12 = 0;
    do {
      lVar9 = lVar9 + (ulong)uVar12 * 0x40;
      uVar7 = *(undefined8 *)(lVar9 + 0x10);
      STRINGS::StringUpper((STRINGS *)local_58,(string *)(lVar9 + 0x38));
      uVar3 = *(ulong *)(local_58[0] + -0x18);
      uVar4 = *(ulong *)(*(long *)param_2 + -0x18);
      if (uVar4 <= uVar3) {
        if (uVar3 < uVar4) {
                    /* try { // try from 008a366d to 008a3671 has its CatchHandler @ 008a3685 */
          uVar7 = std::__throw_out_of_range("basic_string::substr");
                    /* catch() { ... } // from try @ 008a3559 with catch @ 008a3672 */
          std::string::~string((string *)local_58);
                    /* WARNING: Subroutine does not return */
          _Unwind_Resume(uVar7);
        }
                    /* try { // try from 008a3515 to 008a3519 has its CatchHandler @ 008a3685 */
        std::string::string((string *)local_68,(string *)local_58,uVar3 - uVar4,uVar4);
        lVar9 = *(long *)(local_68[0] + -0x18);
        if (lVar9 == *(long *)(*(byte **)param_2 + -0x18)) {
          bVar13 = false;
          bVar14 = true;
          pbVar10 = local_68[0];
          pbVar11 = *(byte **)param_2;
          do {
            if (lVar9 == 0) break;
            lVar9 = lVar9 + -1;
            bVar13 = *pbVar10 < *pbVar11;
            bVar14 = *pbVar10 == *pbVar11;
            pbVar10 = pbVar10 + (ulong)bVar15 * -2 + 1;
            pbVar11 = pbVar11 + (ulong)bVar15 * -2 + 1;
          } while (bVar14);
          bVar8 = true;
          if ((!bVar13 && !bVar14) != bVar13) goto LAB_008a3535;
        }
        else {
LAB_008a3535:
          bVar8 = false;
        }
        if ((allocator *)(local_68[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          pbVar10 = local_68[0] + -8;
          iVar2 = *(int *)pbVar10;
          *(int *)pbVar10 = *(int *)pbVar10 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
          }
        }
        if (bVar8) {
                    /* try { // try from 008a3559 to 008a35b9 has its CatchHandler @ 008a3672 */
          uVar5 = Ogre::Material::getBestTechnique((ushort)uVar7,(Renderable *)0x0);
          uVar5 = Ogre::Technique::getPass(uVar5);
          pTVar6 = (TexturePtr *)Ogre::Pass::getTextureUnitState(uVar5);
          Ogre::TextureUnitState::_setTexturePtr(pTVar6);
          lVar9 = *(long *)(*(long *)(param_1 + 0x208) + 0x18 + (ulong)uVar12 * 0x40);
          if (lVar9 != 0) {
            uVar5 = Ogre::Material::getBestTechnique((ushort)lVar9,(Renderable *)0x0);
            uVar5 = Ogre::Technique::getPass(uVar5);
            pTVar6 = (TexturePtr *)Ogre::Pass::getTextureUnitState(uVar5);
            Ogre::TextureUnitState::_setTexturePtr(pTVar6);
          }
        }
      }
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      lVar9 = *(long *)(param_1 + 0x208);
      uVar12 = uVar12 + 1;
    } while (uVar12 < (uint)(*(long *)(param_1 + 0x210) - lVar9 >> 6));
  }
  return;
}



/* address=008a36f0
   symbol=CGenericModel::setProjectorPass */

/* WARNING: Removing unreachable block (ram,0x008a4115) */
/* WARNING: Removing unreachable block (ram,0x008a3f43) */
/* WARNING: Removing unreachable block (ram,0x008a3f87) */
/* WARNING: Removing unreachable block (ram,0x008a3fd4) */
/* WARNING: Removing unreachable block (ram,0x008a4103) */
/* WARNING: Removing unreachable block (ram,0x008a4065) */
/* WARNING: Removing unreachable block (ram,0x008a40c5) */
/* WARNING: Removing unreachable block (ram,0x008a4075) */
/* CGenericModel::setProjectorPass(Ogre::Frustum*, Ogre::Frustum*, std::string const&, std::string
   const&) */

void __thiscall
CGenericModel::setProjectorPass
          (CGenericModel *this,Frustum *param_1,Frustum *param_2,string *param_3,string *param_4)

{
  int *piVar1;
  long lVar2;
  short sVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  string *psVar8;
  long lVar9;
  long lVar10;
  TextureUnitState *pTVar11;
  TextureUnitState *pTVar12;
  string *psVar13;
  undefined8 uVar14;
  long lVar15;
  uint uVar16;
  int iVar17;
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  lVar10 = *(long *)(this + 0x210);
  lVar9 = *(long *)(this + 0x208);
  if ((int)((ulong)(lVar10 - lVar9) >> 6) != 0) {
    uVar16 = 0;
    do {
      lVar15 = (ulong)uVar16 * 0x40;
      lVar2 = lVar9 + lVar15;
      if ((*(short *)(lVar2 + 0x28) == -1) && (*(char *)(lVar2 + 0x31) != '\0')) {
        uVar5 = Ogre::Material::getBestTechnique
                          ((ushort)*(undefined8 *)(lVar2 + 0x10),(Renderable *)0x0);
        psVar8 = (string *)Ogre::Technique::getPass(uVar5);
        uVar4 = KSETTINGS_SHADOWS_ENABLED;
        lVar10 = *(long *)(psVar8 + 0xf0);
        lVar2 = *(long *)(psVar8 + 0xe8);
        lVar9 = *(long *)(this + 0x208);
        sVar3 = *(short *)(lVar9 + lVar15 + 0x2a);
        iVar17 = (int)sVar3;
        iVar7 = iVar17 + 1;
        if (*(char *)(lVar9 + lVar15 + 0x30) != '\0') {
          lVar9 = CMasterResourceManager::getSingleton();
          iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar9 + 0x90),uVar4);
          if (iVar6 != 0) {
            iVar7 = iVar17 + 2;
          }
          lVar9 = *(long *)(this + 0x208);
        }
        if ((int)((uint)(lVar10 - lVar2 >> 3) & 0xffff) < iVar7) {
          lVar9 = lVar9 + lVar15;
          if (*(long *)(lVar9 + 0x18) != 0) {
            uVar5 = Ogre::Material::getBestTechnique
                              ((ushort)*(long *)(lVar9 + 0x18),(Renderable *)0x0);
            lVar10 = Ogre::Technique::getPass(uVar5);
            if ((short)((ulong)(*(long *)(lVar10 + 0xf0) - *(long *)(lVar10 + 0xe8)) >> 3) != 0) {
              Ogre::Material::setLightingEnabled
                        (SUB81(*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar15),0));
              uVar5 = Ogre::Material::getBestTechnique
                                ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar15),
                                 (Renderable *)0x0);
              uVar5 = Ogre::Technique::getPass(uVar5);
              uVar14 = Ogre::Pass::getTextureUnitState(uVar5);
              Ogre::TextureUnitState::setColourOperationEx(0,uVar14,3,1,0,&Ogre::ColourValue::White)
              ;
            }
            lVar9 = lVar15 + *(long *)(this + 0x208);
          }
          uVar4 = KSETTINGS_SHADOWS_ENABLED;
          uVar5 = (ushort)psVar8;
          if (*(char *)(lVar9 + 0x30) == '\0') {
LAB_008a381d:
            if (iVar17 < 2) {
              psVar8 = (string *)Ogre::Pass::createTextureUnitState(psVar8,(ushort)param_4);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar8,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar8,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar8,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx(0,psVar8,4,1,0,&Ogre::ColourValue::White)
              ;
                    /* try { // try from 008a3d4f to 008a3d53 has its CatchHandler @ 008a410e */
              std::string::string((string *)local_c8,"LIGHTPASS",&local_40);
                    /* try { // try from 008a3d5c to 008a3d60 has its CatchHandler @ 008a3f94 */
              Ogre::TextureUnitState::setName(psVar8);
              if ((allocator *)(local_c8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_c8[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                }
              }
            }
            else {
              pTVar11 = (TextureUnitState *)Ogre::Pass::createTextureUnitState();
              pTVar12 = (TextureUnitState *)Ogre::Pass::getTextureUnitState(uVar5);
              Ogre::TextureUnitState::operator=(pTVar11,pTVar12);
                    /* try { // try from 008a3862 to 008a3866 has its CatchHandler @ 008a3f29 */
              std::string::string((string *)local_a8,"",&local_3e);
                    /* try { // try from 008a386f to 008a3873 has its CatchHandler @ 008a4053 */
              Ogre::TextureUnitState::setName((string *)pTVar11);
              if ((allocator *)(local_a8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_a8[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
                }
              }
              psVar8 = (string *)Ogre::Pass::getTextureUnitState(uVar5);
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar8,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar8,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar8,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx(0,psVar8,4,1,0,&Ogre::ColourValue::White)
              ;
                    /* try { // try from 008a3905 to 008a3909 has its CatchHandler @ 008a4070 */
              std::string::string((string *)local_b8,"LIGHTPASS",&local_3f);
                    /* try { // try from 008a3912 to 008a3916 has its CatchHandler @ 008a4015 */
              Ogre::TextureUnitState::setName(psVar8);
              if ((allocator *)(local_b8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_b8[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                }
              }
              Ogre::TextureUnitState::setTextureName(psVar8,param_4,2);
            }
            lVar10 = *(long *)(this + 0x68);
            if (((lVar10 != 0) && (*(int *)(lVar10 + 0x30) != 0)) &&
               (**(long **)(lVar10 + 0x28) != 0)) {
              *(undefined1 *)(**(long **)(lVar10 + 0x28) + 0x38d4) = 1;
            }
          }
          else {
            lVar10 = CMasterResourceManager::getSingleton();
            iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar4);
            if (iVar7 == 0) goto LAB_008a381d;
            if (iVar17 < 2) {
              psVar13 = (string *)Ogre::Pass::createTextureUnitState(psVar8,(ushort)param_3);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar13,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar13,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar13,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar13,3,0,1,&Ogre::ColourValue::White);
                    /* try { // try from 008a3e2d to 008a3e31 has its CatchHandler @ 008a3f92 */
              std::string::string((string *)local_88,"LIGHTPASS",&local_3c);
                    /* try { // try from 008a3e38 to 008a3e3c has its CatchHandler @ 008a3f7a */
              Ogre::TextureUnitState::setName(psVar13);
              if ((allocator *)(local_88[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_88[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
                }
              }
              psVar8 = (string *)Ogre::Pass::createTextureUnitState(psVar8,(ushort)param_4);
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar8,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar8,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar8,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx(0,psVar8,4,0,1,&Ogre::ColourValue::White)
              ;
                    /* try { // try from 008a3ed3 to 008a3ed7 has its CatchHandler @ 008a3f41 */
              std::string::string((string *)local_98,"LIGHTPASS",&local_3d);
                    /* try { // try from 008a3ede to 008a3ee2 has its CatchHandler @ 008a3f34 */
              Ogre::TextureUnitState::setName(psVar8);
              if ((allocator *)(local_98[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_98[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
                }
              }
            }
            else {
              Ogre::Pass::createTextureUnitState();
              pTVar11 = (TextureUnitState *)Ogre::Pass::createTextureUnitState();
              pTVar12 = (TextureUnitState *)Ogre::Pass::getTextureUnitState(uVar5);
              Ogre::TextureUnitState::operator=(pTVar11,pTVar12);
                    /* try { // try from 008a3a50 to 008a3a54 has its CatchHandler @ 008a3fdf */
              std::string::string((string *)local_58,"",local_39);
                    /* try { // try from 008a3a5d to 008a3a61 has its CatchHandler @ 008a3fcf */
              Ogre::TextureUnitState::setName((string *)pTVar11);
              if ((allocator *)(local_58[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_58[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
                }
              }
              psVar8 = (string *)Ogre::Pass::getTextureUnitState(uVar5);
              psVar13 = (string *)Ogre::Pass::getTextureUnitState(uVar5);
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setBlank();
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar8,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar8,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar8,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx(0,psVar8,3,0,1,&Ogre::ColourValue::White)
              ;
              Ogre::TextureUnitState::setTextureName(psVar8,param_3,2);
                    /* try { // try from 008a3b2c to 008a3b30 has its CatchHandler @ 008a40b9 */
              std::string::string((string *)local_68,"LIGHTPASS",&local_3a);
                    /* try { // try from 008a3b37 to 008a3b3b has its CatchHandler @ 008a40b4 */
              Ogre::TextureUnitState::setName(psVar8);
              if ((allocator *)(local_68[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_68[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
                }
              }
              Ogre::TextureUnitState::setProjectiveTexturing(SUB81(psVar13,0),(Frustum *)0x1);
              Ogre::TextureUnitState::setTextureAddressingMode(psVar13,2);
              Ogre::TextureUnitState::setTextureFiltering(psVar13,1,2,0);
              Ogre::TextureUnitState::setColourOperationEx
                        (0,psVar13,4,0,1,&Ogre::ColourValue::White);
              Ogre::TextureUnitState::setTextureName(psVar13,param_4,2);
                    /* try { // try from 008a3bd3 to 008a3bd7 has its CatchHandler @ 008a4083 */
              std::string::string((string *)local_78,"LIGHTPASS",&local_3b);
                    /* try { // try from 008a3bde to 008a3be2 has its CatchHandler @ 008a40fe */
              Ogre::TextureUnitState::setName(psVar13);
              if ((allocator *)(local_78[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_78[0] + -8);
                iVar7 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
                }
              }
            }
            *(short *)(*(long *)(this + 0x208) + 0x28 + lVar15) = sVar3;
            lVar10 = *(long *)(this + 0x68);
            if (((lVar10 != 0) && (*(int *)(lVar10 + 0x30) != 0)) &&
               (**(long **)(lVar10 + 0x28) != 0)) {
              *(undefined1 *)(**(long **)(lVar10 + 0x28) + 0x38d4) = 1;
              lVar9 = *(long *)(this + 0x208);
              lVar10 = *(long *)(this + 0x210);
              goto LAB_008a3740;
            }
          }
          lVar9 = *(long *)(this + 0x208);
        }
        lVar10 = *(long *)(this + 0x210);
      }
LAB_008a3740:
      uVar16 = uVar16 + 1;
    } while (uVar16 < (uint)(lVar10 - lVar9 >> 6));
  }
  return;
}



/* address=008a4130
   symbol=CGenericModel::getAnimationIndex */

/* WARNING: Removing unreachable block (ram,0x008a42a1) */
/* WARNING: Removing unreachable block (ram,0x008a42ac) */
/* CGenericModel::getAnimationIndex(std::string const&) const */

uint __thiscall CGenericModel::getAnimationIndex(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  char *local_58 [2];
  char *local_48 [3];

  bVar8 = 0;
  uVar4 = 0xffffffff;
  if (*(long *)(this + 0x1e0) != 0) {
    STRINGS::StringUpper((STRINGS *)local_48,param_1);
    lVar3 = *(long *)(this + 0x1e0);
    if (*(int *)(lVar3 + 0x20) != 0) {
      uVar4 = 0;
      do {
                    /* try { // try from 008a41c3 to 008a41c7 has its CatchHandler @ 008a428e */
        STRINGS::StringUpper
                  ((STRINGS *)local_58,(string *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x28)));
        bVar7 = false;
        lVar3 = *(long *)(local_58[0] + -0x18);
        if (lVar3 == *(long *)(local_48[0] + -0x18)) {
          bVar7 = true;
          pcVar5 = local_58[0];
          pcVar6 = local_48[0];
          do {
            if (lVar3 == 0) break;
            lVar3 = lVar3 + -1;
            bVar7 = *pcVar5 == *pcVar6;
            pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
            pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
          } while (bVar7);
        }
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        if (bVar7) goto LAB_008a4205;
        lVar3 = *(long *)(this + 0x1e0);
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(lVar3 + 0x20));
    }
    uVar4 = 0xffffffff;
LAB_008a4205:
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
  }
  return uVar4;
}



/* address=008a42c0
   symbol=CGenericModel::queueBlendAnimation */

/* CGenericModel::queueBlendAnimation(std::string const&, bool, float, float) */

void __thiscall
CGenericModel::queueBlendAnimation
          (CGenericModel *this,string *param_1,bool param_2,float param_3,float param_4)

{
  uint uVar1;

  uVar1 = getAnimationIndex(this,param_1);
  queueBlendAnimation(this,uVar1,param_2,param_3,param_4);
  return;
}



/* address=008a4310
   symbol=CGenericModel::animationExistsSubstring */

/* WARNING: Removing unreachable block (ram,0x008a44f2) */
/* WARNING: Removing unreachable block (ram,0x008a44b9) */
/* WARNING: Removing unreachable block (ram,0x008a4500) */
/* CGenericModel::animationExistsSubstring(std::string const&) const */

undefined8 __thiscall CGenericModel::animationExistsSubstring(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  ulong uVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  byte bVar9;
  char *local_58 [2];
  long local_48 [3];

  bVar9 = 0;
  lVar3 = *(long *)(this + 0x1e0);
  if ((lVar3 != 0) && (*(int *)(lVar3 + 0x20) != 0)) {
    uVar5 = *(ulong *)(*(long *)param_1 + -0x18) & 0xffffffff;
    uVar4 = 0;
    do {
      STRINGS::StringUpper
                ((STRINGS *)local_48,(string *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x28)));
      if (uVar5 <= *(ulong *)(local_48[0] + -0x18)) {
                    /* try { // try from 008a43ad to 008a43b1 has its CatchHandler @ 008a44a6 */
        std::string::string((string *)local_58,(string *)local_48,0,uVar5);
        bVar8 = false;
        lVar3 = *(long *)(local_58[0] + -0x18);
        if (lVar3 == *(long *)(*(char **)param_1 + -0x18)) {
          bVar8 = true;
          pcVar6 = local_58[0];
          pcVar7 = *(char **)param_1;
          do {
            if (lVar3 == 0) break;
            lVar3 = lVar3 + -1;
            bVar8 = *pcVar6 == *pcVar7;
            pcVar6 = pcVar6 + (ulong)bVar9 * -2 + 1;
            pcVar7 = pcVar7 + (ulong)bVar9 * -2 + 1;
          } while (bVar8);
        }
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        if (bVar8) {
          if ((allocator *)(local_48[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_48[0] + -8);
            iVar2 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar2 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
              return 1;
            }
          }
          return 1;
        }
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      lVar3 = *(long *)(this + 0x1e0);
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(lVar3 + 0x20));
  }
  return 0;
}



/* address=008a4510
   symbol=CGenericModel::setWireframe */

/* WARNING: Removing unreachable block (ram,0x008a4642) */
/* WARNING: Removing unreachable block (ram,0x008a4669) */
/* CGenericModel::setWireframe(bool) */

void __thiscall CGenericModel::setWireframe(CGenericModel *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  long local_38 [2];
  long local_28;
  allocator local_1a;
  allocator local_19 [9];

  if (*(long *)(this + 0x60) != 0) {
    if (!param_1) {
                    /* try { // try from 008a459d to 008a45a1 has its CatchHandler @ 008a465a */
      std::string::string((string *)local_38,"",&local_1a);
                    /* try { // try from 008a45a9 to 008a45ad has its CatchHandler @ 008a465c */
      Ogre::Entity::setMaterialName(*(string **)(this + 0x60));
      if ((allocator *)(local_38[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_38[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
        }
      }
      plVar3 = (long *)(**(code **)(**(long **)(this + 0x60) + 0xa0))();
      (**(code **)(*plVar3 + 0x308))(plVar3,0);
      *(undefined1 *)(*(long *)(this + 0x60) + 0xc0) = 0;
      return;
    }
                    /* try { // try from 008a4537 to 008a453b has its CatchHandler @ 008a4637 */
    std::string::string((string *)&local_28,"Points",local_19);
                    /* try { // try from 008a4543 to 008a4547 has its CatchHandler @ 008a464d */
    Ogre::Entity::setMaterialName(*(string **)(this + 0x60));
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    plVar3 = (long *)(**(code **)(**(long **)(this + 0x60) + 0xa0))();
    (**(code **)(*plVar3 + 0x308))(plVar3,1);
    *(undefined1 *)(*(long *)(this + 0x60) + 0xc0) = 0;
  }
  return;
}



/* address=008a4680
   symbol=CGenericModel::setTextureOverrideSingle */

/* WARNING: Removing unreachable block (ram,0x008a4bef) */
/* CGenericModel::setTextureOverrideSingle(std::string const&, std::wstring const&) */

void __thiscall
CGenericModel::setTextureOverrideSingle
          (CGenericModel *this,string *param_1,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long lVar4;
  CFileSystem *this_00;
  long *plVar5;
  undefined1 *local_158;
  string local_150 [8];
  wstring_conflict local_148 [8];
  undefined4 local_140;
  undefined4 local_13c;
  undefined1 *local_138;
  char local_130;
  undefined **local_128;
  long *local_120;
  int *local_118;
  undefined4 local_110;
  undefined **local_108;
  long *local_100;
  int *local_f8;
  undefined **local_e8;
  long *local_e0;
  int *local_d8;
  undefined4 local_d0;
  undefined **local_c8 [2];
  int *local_b8;
  undefined **local_a8;
  long *local_a0;
  int *local_98;
  undefined4 local_90;
  undefined **local_88;
  long *local_80;
  int *local_78;
  undefined **local_68;
  long *local_60;
  int *local_58;
  undefined4 local_50;
  string local_48 [16];
  long local_38 [2];

  if ((*(long *)(*(long *)param_2 + -0x18) != 0) &&
     (lVar4 = Ogre::TextureManager::getSingletonPtr(), lVar4 != 0)) {
    local_158 = &DAT_01423a38;
                    /* try { // try from 008a4709 to 008a470d has its CatchHandler @ 008a4bce */
    std::string::string(local_150,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a4717 to 008a471b has its CatchHandler @ 008a4be1 */
    std::wstring::wstring(local_148,(wstring_conflict *)&::EMPTY_WSTRING);
    local_140 = 4;
    local_13c = 3;
    local_138 = &DAT_01423a38;
    local_130 = '\0';
                    /* try { // try from 008a473a to 008a4782 has its CatchHandler @ 008a4bc6 */
    this_00 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo(this_00,param_2,(CFileInfo *)&local_158,false,true,false);
    if (local_130 != '\0') {
      plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
      (**(code **)(*plVar5 + 0xa0))((SharedPtr<Ogre::Resource> *)&local_88,plVar5,local_150);
      local_50 = 0;
      local_68 = &PTR__TexturePtr_00fa8610;
      local_60 = local_80;
      local_58 = local_78;
      if (local_78 != (int *)0x0) {
        *local_78 = *local_78 + 1;
      }
      local_88 = &PTR__SharedPtr_00fa45d0;
      if ((local_78 != (int *)0x0) && (iVar2 = *local_78, *local_78 = iVar2 + -1, iVar2 + -1 == 0))
      {
                    /* try { // try from 008a47e9 to 008a4820 has its CatchHandler @ 008a4b82 */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_88);
      }
      if ((local_60 == (long *)0x0) || (cVar3 = (**(code **)(*local_60 + 0xe0))(), cVar3 == '\0')) {
                    /* try { // try from 008a4930 to 008a49ce has its CatchHandler @ 008a4b82 */
        plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
        (**(code **)(*plVar5 + 0x128))
                  (DAT_00fa47fc,local_c8,plVar5,local_150,
                   &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,0xffffffff,0,0,0);
        local_c8[0] = &PTR__SharedPtr_00fa86b0;
        if ((local_b8 != (int *)0x0) && (iVar2 = *local_b8, *local_b8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
          (*(code *)PTR_destroy_00fa86c0)(local_c8);
        }
        plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
        (**(code **)(*plVar5 + 0xa0))((SharedPtr<Ogre::Resource> *)&local_108,plVar5,local_150);
        local_d0 = 0;
        local_e8 = &PTR__TexturePtr_00fa8610;
        local_e0 = local_100;
        local_d8 = local_f8;
        if (local_f8 != (int *)0x0) {
          *local_f8 = *local_f8 + 1;
        }
        local_108 = &PTR__SharedPtr_00fa45d0;
        if ((local_f8 != (int *)0x0) && (iVar2 = *local_f8, *local_f8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
                    /* try { // try from 008a4a2f to 008a4a66 has its CatchHandler @ 008a4b25 */
          Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_108);
        }
        if ((local_e0 != (long *)0x0) && (cVar3 = (**(code **)(*local_e0 + 0xe0))(), cVar3 != '\0'))
        {
          std::string::assign((string *)(this + 0x128));
          local_120 = local_e0;
          local_110 = local_d0;
          local_118 = local_d8;
          if (local_d8 != (int *)0x0) {
            *local_d8 = *local_d8 + 1;
          }
          local_128 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 008a4ab9 to 008a4abd has its CatchHandler @ 008a4bc1 */
          std::string::string(local_48,param_1);
                    /* try { // try from 008a4acc to 008a4ad0 has its CatchHandler @ 008a4ba9 */
          setTextureOverrideSingle(this,local_48,(TexturePtr *)&local_128);
                    /* try { // try from 008a4ad4 to 008a4ad8 has its CatchHandler @ 008a4bc1 */
          std::string::~string(local_48);
                    /* try { // try from 008a4adc to 008a4ae0 has its CatchHandler @ 008a4b25 */
          Ogre::TexturePtr::~TexturePtr((TexturePtr *)&local_128);
        }
        local_e8 = &PTR__SharedPtr_00fa86b0;
        if ((local_d8 != (int *)0x0) && (iVar2 = *local_d8, *local_d8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
                    /* try { // try from 008a4b1d to 008a4b1f has its CatchHandler @ 008a4b82 */
          (*(code *)PTR_destroy_00fa86c0)(&local_e8);
        }
      }
      else {
        std::string::assign((string *)(this + 0x128));
        local_a0 = local_60;
        local_90 = local_50;
        local_98 = local_58;
        if (local_58 != (int *)0x0) {
          *local_58 = *local_58 + 1;
        }
        local_a8 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 008a487d to 008a4881 has its CatchHandler @ 008a4b9c */
        std::string::string((string *)local_38,param_1);
                    /* try { // try from 008a4893 to 008a4897 has its CatchHandler @ 008a4b87 */
        setTextureOverrideSingle(this,(string *)local_38,&local_a8);
        if ((allocator *)(local_38[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_38[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
          }
        }
        local_a8 = &PTR__SharedPtr_00fa86b0;
        if ((local_98 != (int *)0x0) && (iVar2 = *local_98, *local_98 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
                    /* try { // try from 008a48e0 to 008a48e2 has its CatchHandler @ 008a4b82 */
          (*(code *)PTR_destroy_00fa86c0)(&local_a8);
        }
      }
      local_68 = &PTR__SharedPtr_00fa86b0;
      if ((local_58 != (int *)0x0) && (iVar2 = *local_58, *local_58 = iVar2 + -1, iVar2 + -1 == 0))
      {
                    /* try { // try from 008a4917 to 008a4919 has its CatchHandler @ 008a4bc6 */
        (*(code *)PTR_destroy_00fa86c0)(&local_68);
      }
    }
    CFileInfo::~CFileInfo((CFileInfo *)&local_158);
  }
  return;
}



/* address=008a4c00
   symbol=CGenericModel::setTextureOverride */

/* WARNING: Removing unreachable block (ram,0x008a51c5) */
/* WARNING: Removing unreachable block (ram,0x008a51ba) */
/* CGenericModel::setTextureOverride(std::wstring const&) */

void __thiscall CGenericModel::setTextureOverride(CGenericModel *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long lVar4;
  CFileSystem *this_00;
  long *plVar5;
  undefined1 *local_178;
  string local_170 [8];
  wstring_conflict local_168 [8];
  undefined4 local_160;
  undefined4 local_15c;
  undefined1 *local_158;
  char local_150;
  undefined **local_148;
  long *local_140;
  int *local_138;
  undefined4 local_130;
  undefined **local_128;
  long *local_120;
  int *local_118;
  undefined **local_108;
  long *local_100;
  int *local_f8;
  undefined4 local_f0;
  undefined **local_e8 [2];
  int *local_d8;
  undefined **local_c8;
  long *local_c0;
  int *local_b8;
  undefined4 local_b0;
  undefined **local_a8;
  long *local_a0;
  int *local_98;
  undefined **local_88;
  long *local_80;
  int *local_78;
  undefined4 local_70;
  string local_68 [16];
  string local_58 [16];
  long local_48 [2];
  long local_38;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  if ((*(long *)(*(long *)param_1 + -0x18) != 0) &&
     (lVar4 = Ogre::TextureManager::getSingletonPtr(), lVar4 != 0)) {
    local_178 = &DAT_01423a38;
                    /* try { // try from 008a4c81 to 008a4c85 has its CatchHandler @ 008a522b */
    std::string::string(local_170,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a4c8f to 008a4c93 has its CatchHandler @ 008a5207 */
    std::wstring::wstring(local_168,(wstring_conflict *)&::EMPTY_WSTRING);
    local_160 = 4;
    local_15c = 3;
    local_158 = &DAT_01423a38;
    local_150 = '\0';
                    /* try { // try from 008a4cb2 to 008a4cfa has its CatchHandler @ 008a5223 */
    this_00 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo(this_00,param_1,(CFileInfo *)&local_178,false,true,false);
    if (local_150 != '\0') {
      plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
      (**(code **)(*plVar5 + 0xa0))((SharedPtr<Ogre::Resource> *)&local_a8,plVar5,local_170);
      local_70 = 0;
      local_88 = &PTR__TexturePtr_00fa8610;
      local_80 = local_a0;
      local_78 = local_98;
      if (local_98 != (int *)0x0) {
        *local_98 = *local_98 + 1;
      }
      local_a8 = &PTR__SharedPtr_00fa45d0;
      if ((local_98 != (int *)0x0) && (iVar2 = *local_98, *local_98 = iVar2 + -1, iVar2 + -1 == 0))
      {
                    /* try { // try from 008a4d61 to 008a4d98 has its CatchHandler @ 008a5205 */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_a8);
      }
      if ((local_80 == (long *)0x0) || (cVar3 = (**(code **)(*local_80 + 0xe0))(), cVar3 == '\0')) {
                    /* try { // try from 008a4ee8 to 008a4f86 has its CatchHandler @ 008a5205 */
        plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
        (**(code **)(*plVar5 + 0x128))
                  (DAT_00fa47fc,local_e8,plVar5,local_170,
                   &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,0xffffffff,0,0,0);
        local_e8[0] = &PTR__SharedPtr_00fa86b0;
        if ((local_d8 != (int *)0x0) && (iVar2 = *local_d8, *local_d8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
          (*(code *)PTR_destroy_00fa86c0)(local_e8);
        }
        plVar5 = (long *)Ogre::TextureManager::getSingletonPtr();
        (**(code **)(*plVar5 + 0xa0))((SharedPtr<Ogre::Resource> *)&local_128,plVar5,local_170);
        local_f0 = 0;
        local_108 = &PTR__TexturePtr_00fa8610;
        local_100 = local_120;
        local_f8 = local_118;
        if (local_118 != (int *)0x0) {
          *local_118 = *local_118 + 1;
        }
        local_128 = &PTR__SharedPtr_00fa45d0;
        if ((local_118 != (int *)0x0) &&
           (iVar2 = *local_118, *local_118 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 008a4fe7 to 008a501e has its CatchHandler @ 008a515e */
          Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_128);
        }
        if ((local_100 != (long *)0x0) &&
           (cVar3 = (**(code **)(*local_100 + 0xe0))(), cVar3 != '\0')) {
          std::string::assign((string *)(this + 0x128));
                    /* try { // try from 008a5037 to 008a503b has its CatchHandler @ 008a5159 */
          std::string::string(local_68,"",&local_2c);
                    /* try { // try from 008a5054 to 008a5058 has its CatchHandler @ 008a510a */
          std::string::string(local_58,"",&local_2b);
          local_140 = local_100;
          local_130 = local_f0;
          local_138 = local_f8;
          if (local_f8 != (int *)0x0) {
            *local_f8 = *local_f8 + 1;
          }
          local_148 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 008a50a9 to 008a50ad has its CatchHandler @ 008a514c */
          setTextureOverride(this,(TexturePtr *)&local_148,local_58,local_68);
                    /* try { // try from 008a50b1 to 008a50b5 has its CatchHandler @ 008a513f */
          Ogre::TexturePtr::~TexturePtr((TexturePtr *)&local_148);
                    /* try { // try from 008a50b9 to 008a50bd has its CatchHandler @ 008a510a */
          std::string::~string(local_58);
                    /* try { // try from 008a50c1 to 008a50c5 has its CatchHandler @ 008a5159 */
          std::string::~string(local_68);
        }
        local_108 = &PTR__SharedPtr_00fa86b0;
        if ((local_f8 != (int *)0x0) && (iVar2 = *local_f8, *local_f8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
                    /* try { // try from 008a5102 to 008a5104 has its CatchHandler @ 008a5205 */
          (*(code *)PTR_destroy_00fa86c0)(&local_108);
        }
      }
      else {
        std::string::assign((string *)(this + 0x128));
                    /* try { // try from 008a4db1 to 008a4db5 has its CatchHandler @ 008a51fa */
        std::string::string((string *)local_48,"",&local_2a);
                    /* try { // try from 008a4dce to 008a4dd2 has its CatchHandler @ 008a51f5 */
        std::string::string((string *)&local_38,"",&local_29);
        local_c0 = local_80;
        local_b0 = local_70;
        local_b8 = local_78;
        if (local_78 != (int *)0x0) {
          *local_78 = *local_78 + 1;
        }
        local_c8 = &PTR__TexturePtr_00fa8610;
                    /* try { // try from 008a4e35 to 008a4e39 has its CatchHandler @ 008a51e8 */
        setTextureOverride(this,&local_c8,(string *)&local_38,(string *)local_48);
        local_c8 = &PTR__SharedPtr_00fa86b0;
        if ((local_b8 != (int *)0x0) && (iVar2 = *local_b8, *local_b8 = iVar2 + -1, iVar2 + -1 == 0)
           ) {
                    /* try { // try from 008a4e69 to 008a4e6b has its CatchHandler @ 008a51d0 */
          (*(code *)PTR_destroy_00fa86c0)(&local_c8);
        }
        if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
           ) {
          LOCK();
          piVar1 = (int *)(local_38 + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
          }
        }
        if ((allocator *)(local_48[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_48[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
          }
        }
      }
      local_88 = &PTR__SharedPtr_00fa86b0;
      if ((local_78 != (int *)0x0) && (iVar2 = *local_78, *local_78 = iVar2 + -1, iVar2 + -1 == 0))
      {
                    /* try { // try from 008a4ed3 to 008a4ed5 has its CatchHandler @ 008a5223 */
        (*(code *)PTR_destroy_00fa86c0)(&local_88);
      }
    }
    CFileInfo::~CFileInfo((CFileInfo *)&local_178);
  }
  return;
}



/* address=008a5230
   symbol=CGenericModel::setAnimationTime */

/* CGenericModel::setAnimationTime(float) */

void __thiscall CGenericModel::setAnimationTime(CGenericModel *this,float param_1)

{
  float fVar1;
  ulong uVar2;
  long *plVar3;
  ulong uVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  ulong uVar13;
  float fVar14;

  lVar11 = *(long *)(this + 400);
  lVar8 = *(long *)(this + 0x170);
  lVar12 = *(long *)(this + 0x1a8);
  lVar10 = *(long *)(this + 0x188);
  lVar7 = *(long *)(this + 0x198);
  lVar6 = *(long *)(this + 0x180);
  if ((lVar12 - lVar10 >> 3) * 0x40 + -0x40 + (lVar11 - lVar7 >> 3) + (lVar6 - lVar8 >> 3) != 0) {
    uVar5 = 0;
    uVar9 = 0;
    do {
      uVar2 = (lVar8 - *(long *)(this + 0x178) >> 3) + uVar5;
      uVar4 = (long)uVar2 >> 6;
      if ((long)uVar2 < 0) {
LAB_008a53c0:
        uVar13 = ~(~uVar2 >> 6);
LAB_008a530b:
        plVar3 = (long *)((uVar2 + uVar13 * -0x40) * 8 + *(long *)(lVar10 + uVar13 * 8));
      }
      else {
        plVar3 = (long *)(lVar8 + uVar5 * 8);
        if (0x3f < (long)uVar2) {
          uVar13 = uVar4;
          if ((long)uVar2 < 1) goto LAB_008a53c0;
          goto LAB_008a530b;
        }
      }
      if (*(char *)(*plVar3 + 0x26) == '\0') {
        if ((long)uVar2 < 0) {
LAB_008a53d8:
          uVar4 = ~(~uVar2 >> 6);
LAB_008a5353:
          plVar3 = (long *)((uVar2 + uVar4 * -0x40) * 8 + *(long *)(lVar10 + uVar4 * 8));
        }
        else {
          plVar3 = (long *)(lVar8 + uVar5 * 8);
          if (0x3f < (long)uVar2) {
            if ((long)uVar2 < 1) goto LAB_008a53d8;
            goto LAB_008a5353;
          }
        }
        fVar14 = param_1;
        if (param_1 <= 0.0) {
          fVar14 = 0.0;
        }
        fVar1 = *(float *)(*plVar3 + 0x18);
        if (fVar1 <= fVar14) {
          fVar14 = fVar1;
        }
        *(float *)(*plVar3 + 0x20) = fVar14;
        lVar10 = *(long *)(this + 0x188);
        lVar8 = *(long *)(this + 0x170);
        lVar7 = *(long *)(this + 0x198);
        lVar11 = *(long *)(this + 400);
        lVar6 = *(long *)(this + 0x180);
        lVar12 = *(long *)(this + 0x1a8);
      }
      uVar9 = uVar9 + 1;
      uVar5 = (ulong)uVar9;
    } while (uVar5 < (ulong)((lVar12 - lVar10 >> 3) * 0x40 + -0x40 +
                            (lVar6 - lVar8 >> 3) + (lVar11 - lVar7 >> 3)));
  }
  return;
}



/* address=008a53f0
   symbol=CGenericModel::animationQueued */

/* CGenericModel::animationQueued(unsigned int) const */

undefined8 __thiscall CGenericModel::animationQueued(CGenericModel *this,uint param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) +
          (*(long *)(this + 0x180) - lVar2 >> 3);
  if (uVar1 != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar7 = uVar4 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar7 >> 6;
      if ((long)uVar7 < 0) {
LAB_008a5500:
        uVar9 = ~(~uVar7 >> 6);
LAB_008a5490:
        plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar4 * 8);
        if (0x3f < (long)uVar7) {
          uVar9 = uVar6;
          if ((long)uVar7 < 1) goto LAB_008a5500;
          goto LAB_008a5490;
        }
      }
      if (*(char *)(*plVar5 + 0x26) != '\0') {
        if ((long)uVar7 < 0) {
LAB_008a5510:
          uVar6 = ~(~uVar7 >> 6);
LAB_008a54cc:
          plVar5 = (long *)((uVar7 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar4 * 8);
          if (0x3f < (long)uVar7) {
            if ((long)uVar7 < 1) goto LAB_008a5510;
            goto LAB_008a54cc;
          }
        }
        if (param_1 == *(uint *)(*plVar5 + 0x10)) {
          return 1;
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < uVar1);
  }
  return 0;
}



/* address=008a5530
   symbol=CGenericModel::animationQueued */

/* CGenericModel::animationQueued(std::string const&) const */

void __thiscall CGenericModel::animationQueued(CGenericModel *this,string *param_1)

{
  uint uVar1;

  uVar1 = getAnimationIndex(this,param_1);
  animationQueued(this,uVar1);
  return;
}



/* address=008a5550
   symbol=CGenericModel::animationPlaying */

/* CGenericModel::animationPlaying() const */

undefined8 __thiscall CGenericModel::animationPlaying(CGenericModel *this)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) +
          (*(long *)(this + 0x180) - lVar2 >> 3);
  if (uVar1 != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar7 = uVar4 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar7 >> 6;
      if ((long)uVar7 < 0) {
LAB_008a5660:
        uVar9 = ~(~uVar7 >> 6);
LAB_008a55f0:
        plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar4 * 8);
        if (0x3f < (long)uVar7) {
          uVar9 = uVar6;
          if ((long)uVar7 < 1) goto LAB_008a5660;
          goto LAB_008a55f0;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar7 < 0) {
LAB_008a5670:
          uVar6 = ~(~uVar7 >> 6);
LAB_008a562c:
          plVar5 = (long *)((uVar7 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar4 * 8);
          if (0x3f < (long)uVar7) {
            if ((long)uVar7 < 1) goto LAB_008a5670;
            goto LAB_008a562c;
          }
        }
        if (*(char *)(*plVar5 + 0x25) != '\0') {
          return 1;
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < uVar1);
  }
  return 0;
}



/* address=008a5690
   symbol=CGenericModel::clearAnimations */

/* CGenericModel::clearAnimations() */

void __thiscall CGenericModel::clearAnimations(CGenericModel *this)

{
  ulong uVar1;
  undefined8 *puVar2;
  ulong uVar3;
  ulong uVar4;
  undefined8 *puVar5;
  long *plVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  int iVar10;
  long lVar11;

  lVar7 = *(long *)(this + 0x180);
  lVar8 = *(long *)(this + 0x170);
  lVar9 = *(long *)(this + 0x1a8);
  puVar2 = *(undefined8 **)(this + 0x188);
  if ((int)(lVar9 - (long)puVar2 >> 3) * 0x40 + -0x40 +
      (int)(lVar7 - lVar8 >> 3) + (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) < 1) {
    lVar11 = *(long *)(this + 0x178);
  }
  else {
    lVar11 = *(long *)(this + 0x178);
    iVar10 = 0;
    do {
      lVar7 = (long)iVar10;
      uVar1 = (lVar8 - lVar11 >> 3) + lVar7;
      uVar4 = (long)uVar1 >> 6;
      if ((long)uVar1 < 0) {
LAB_008a5960:
        uVar3 = ~(~uVar1 >> 6);
LAB_008a58aa:
        plVar6 = (long *)((uVar1 + uVar3 * -0x40) * 8 + puVar2[uVar3]);
      }
      else {
        plVar6 = (long *)(lVar8 + lVar7 * 8);
        if (0x3f < (long)uVar1) {
          uVar3 = uVar4;
          if ((long)uVar1 < 1) goto LAB_008a5960;
          goto LAB_008a58aa;
        }
      }
      if (*(uint *)(*plVar6 + 0x10) < *(uint *)(this + 0x150)) {
        if ((long)uVar1 < 0) {
LAB_008a5a20:
          uVar4 = ~(~uVar1 >> 6);
LAB_008a58f2:
          plVar6 = (long *)((uVar1 + uVar4 * -0x40) * 8 + puVar2[uVar4]);
        }
        else {
          plVar6 = (long *)(lVar8 + lVar7 * 8);
          if (0x3f < (long)uVar1) {
            if ((long)uVar1 < 1) goto LAB_008a5a20;
            goto LAB_008a58f2;
          }
        }
        if (*(uint *)(*plVar6 + 0x10) < *(uint *)(this + 0x154)) {
          puVar2 = (undefined8 *)((ulong)*(uint *)(*plVar6 + 0x10) * 8 + *(long *)(this + 0x148));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x148);
        }
        Ogre::AnimationState::setEnabled(SUB81(*puVar2,0));
        lVar11 = *(long *)(this + 0x178);
        puVar2 = *(undefined8 **)(this + 0x188);
        lVar8 = *(long *)(this + 0x170);
      }
      uVar1 = (lVar8 - lVar11 >> 3) + lVar7;
      uVar4 = (long)uVar1 >> 6;
      if ((long)uVar1 < 0) {
LAB_008a5948:
        uVar3 = ~(~uVar1 >> 6);
LAB_008a5744:
        plVar6 = (long *)((uVar1 + uVar3 * -0x40) * 8 + puVar2[uVar3]);
      }
      else {
        plVar6 = (long *)(lVar8 + lVar7 * 8);
        if (0x3f < (long)uVar1) {
          uVar3 = uVar4;
          if ((long)uVar1 < 1) goto LAB_008a5948;
          goto LAB_008a5744;
        }
      }
      if (*plVar6 != 0) {
        if ((long)uVar1 < 0) {
LAB_008a59a8:
          uVar4 = ~(~uVar1 >> 6);
LAB_008a578a:
          plVar6 = (long *)((uVar1 + uVar4 * -0x40) * 8 + puVar2[uVar4]);
        }
        else {
          plVar6 = (long *)(lVar8 + lVar7 * 8);
          if (0x3f < (long)uVar1) {
            if ((long)uVar1 < 1) goto LAB_008a59a8;
            goto LAB_008a578a;
          }
        }
        if ((long *)*plVar6 != (long *)0x0) {
          (**(code **)(*(long *)*plVar6 + 8))();
          lVar8 = *(long *)(this + 0x170);
          puVar2 = *(undefined8 **)(this + 0x188);
          uVar1 = lVar7 + (lVar8 - *(long *)(this + 0x178) >> 3);
        }
        if ((long)uVar1 < 0) {
LAB_008a5990:
          uVar4 = ~(~uVar1 >> 6);
LAB_008a57f4:
          puVar5 = (undefined8 *)((uVar1 + uVar4 * -0x40) * 8 + puVar2[uVar4]);
        }
        else {
          puVar5 = (undefined8 *)(lVar8 + lVar7 * 8);
          if (0x3f < (long)uVar1) {
            if ((long)uVar1 < 1) goto LAB_008a5990;
            uVar4 = (long)uVar1 >> 6;
            goto LAB_008a57f4;
          }
        }
        *puVar5 = 0;
        puVar2 = *(undefined8 **)(this + 0x188);
        lVar8 = *(long *)(this + 0x170);
        lVar11 = *(long *)(this + 0x178);
      }
      lVar7 = *(long *)(this + 0x180);
      iVar10 = iVar10 + 1;
      lVar9 = *(long *)(this + 0x1a8);
    } while (iVar10 < (int)(lVar9 - (long)puVar2 >> 3) * 0x40 + -0x40 +
                      (int)(lVar7 - lVar8 >> 3) +
                      (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3));
  }
  puVar5 = puVar2;
  while (puVar5 = puVar5 + 1, puVar5 < (undefined8 *)(lVar9 + 8U)) {
    operator_delete((void *)*puVar5);
  }
  *(undefined8 **)(this + 0x1a8) = puVar2;
  *(long *)(this + 0x198) = lVar11;
  *(long *)(this + 400) = lVar8;
  *(long *)(this + 0x1a0) = lVar7;
  return;
}



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



/* address=008a5cf0
   symbol=CGenericModel::playAnimation */

/* WARNING: Removing unreachable block (ram,0x008a5df0) */
/* CGenericModel::playAnimation(std::string const&, bool, float, float) */

void __thiscall
CGenericModel::playAnimation
          (CGenericModel *this,string *param_1,bool param_2,float param_3,float param_4)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  char *local_48 [3];

  bVar8 = 0;
  lVar3 = *(long *)(this + 0x1e0);
  if ((lVar3 != 0) && (*(int *)(lVar3 + 0x20) != 0)) {
    uVar4 = 0;
    do {
      STRINGS::StringUpper
                ((STRINGS *)local_48,(string *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x28)));
      bVar7 = false;
      lVar3 = *(long *)(local_48[0] + -0x18);
      if (lVar3 == *(long *)(*(char **)param_1 + -0x18)) {
        bVar7 = true;
        pcVar5 = local_48[0];
        pcVar6 = *(char **)param_1;
        do {
          if (lVar3 == 0) break;
          lVar3 = lVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
          pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
        } while (bVar7);
      }
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if (bVar7) {
        playAnimation(this,uVar4,param_2,param_3,param_4);
        return;
      }
      lVar3 = *(long *)(this + 0x1e0);
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(lVar3 + 0x20));
  }
  return;
}



/* address=008a5e00
   symbol=CGenericModel::~CGenericModel */

/* WARNING: Removing unreachable block (ram,0x008a6172) */
/* WARNING: Removing unreachable block (ram,0x008a6167) */
/* WARNING: Removing unreachable block (ram,0x008a6180) */
/* WARNING: Removing unreachable block (ram,0x008a6159) */
/* CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;
  long lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  long lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;

  *(undefined ***)this = &PTR__CGenericModel_00fd1470;
  *(undefined ***)(this + 0x100) = &PTR__CGenericModel_00fd1668;
  *(undefined ***)(this + 0x108) = &PTR__CGenericModel_00fd1698;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
  }
  *(undefined8 *)(this + 0x148) = 0;
                    /* try { // try from 008a5e5f to 008a5e73 has its CatchHandler @ 008a5feb */
  unloadModel(this);
  clearAnimations(this);
  releaseUniqueMaterials(this);
  lVar4 = *(long *)(this + 0x210);
  for (lVar7 = *(long *)(this + 0x208); lVar4 != lVar7; lVar7 = lVar7 + 0x40) {
                    /* try { // try from 008a5e94 to 008a5e98 has its CatchHandler @ 008a613c */
    std::string::~string((string *)(lVar7 + 0x38));
  }
  if (*(void **)(this + 0x208) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x208));
  }
  puVar5 = *(undefined8 **)(this + 0x1d0);
  for (puVar9 = *(undefined8 **)(this + 0x1c8); puVar5 != puVar9; puVar9 = puVar9 + 3) {
    puVar6 = (undefined8 *)puVar9[1];
    for (puVar8 = (undefined8 *)*puVar9; puVar6 != puVar8; puVar8 = puVar8 + 3) {
      if ((void *)*puVar8 != (void *)0x0) {
        operator_delete__((void *)*puVar8);
        *puVar8 = 0;
      }
    }
    if ((void *)*puVar9 != (void *)0x0) {
      operator_delete((void *)*puVar9);
    }
  }
  if (*(void **)(this + 0x1c8) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1c8));
  }
  if (*(void **)(this + 0x1b0) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x1b0));
  }
  std::_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>>::~_Deque_base
            ((_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160));
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
    *(undefined8 *)(this + 0x148) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x128) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x128) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x120) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x120) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x118) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x118) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x110) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x110) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  *(undefined ***)(this + 0x108) = &PTR__iHighlight_00fd19d0;
  *(undefined ***)(this + 0x100) = &PTR__iRandomWeight_00fd1a10;
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}



/* address=008a6190
   symbol=CGenericModel::~CGenericModel */

/* non-virtual thunk to CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  ~CGenericModel(this + -0x108);
  return;
}



/* address=008a61a0
   symbol=CGenericModel::~CGenericModel */

/* non-virtual thunk to CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  ~CGenericModel(this + -0x100);
  return;
}



/* address=008a61b0
   symbol=CGenericModel::~CGenericModel */

/* non-virtual thunk to CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  ~CGenericModel(this + -0x108);
  return;
}



/* address=008a61c0
   symbol=CGenericModel::~CGenericModel */

/* non-virtual thunk to CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  ~CGenericModel(this + -0x100);
  return;
}



/* address=008a61d0
   symbol=CGenericModel::~CGenericModel */

/* CGenericModel::~CGenericModel() */

void __thiscall CGenericModel::~CGenericModel(CGenericModel *this)

{
  ~CGenericModel(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=008a61f0
   symbol=CGenericModel::animationQueuedSubstring */

/* WARNING: Removing unreachable block (ram,0x008a6507) */
/* WARNING: Removing unreachable block (ram,0x008a64fc) */
/* WARNING: Removing unreachable block (ram,0x008a6553) */
/* CGenericModel::animationQueuedSubstring(std::string const&) const */

undefined8 __thiscall CGenericModel::animationQueuedSubstring(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  string *psVar11;
  char *pcVar12;
  ulong uVar13;
  char *pcVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  bool bVar19;
  byte bVar20;
  char *local_58 [2];
  long local_48 [3];

  bVar20 = 0;
  lVar16 = *(long *)(this + 0x180);
  lVar17 = *(long *)(this + 400);
  lVar10 = *(long *)(this + 0x170);
  lVar18 = *(long *)(this + 0x198);
  lVar15 = *(long *)(this + 0x1a8);
  uVar3 = *(uint *)(*(long *)param_1 + -0x18);
  lVar7 = *(long *)(this + 0x188);
  if ((lVar15 - lVar7 >> 3) * 0x40 + -0x40 + (lVar16 - lVar10 >> 3) + (lVar17 - lVar18 >> 3) != 0) {
    uVar4 = 0;
    uVar9 = 0;
    do {
      uVar8 = (lVar10 - *(long *)(this + 0x178) >> 3) + uVar4;
      uVar6 = (long)uVar8 >> 6;
      if ((long)uVar8 < 0) {
LAB_008a63c0:
        uVar13 = ~(~uVar8 >> 6);
LAB_008a62e9:
        plVar5 = (long *)((uVar8 + uVar13 * -0x40) * 8 + *(long *)(lVar7 + uVar13 * 8));
      }
      else {
        plVar5 = (long *)(lVar10 + uVar4 * 8);
        if (0x3f < (long)uVar8) {
          uVar13 = uVar6;
          if ((long)uVar8 < 1) goto LAB_008a63c0;
          goto LAB_008a62e9;
        }
      }
      if (*(char *)(*plVar5 + 0x26) != '\0') {
        if ((long)uVar8 < 0) {
LAB_008a6430:
          uVar6 = ~(~uVar8 >> 6);
LAB_008a6331:
          plVar5 = (long *)((uVar8 + uVar6 * -0x40) * 8 + *(long *)(lVar7 + uVar6 * 8));
        }
        else {
          plVar5 = (long *)(lVar10 + uVar4 * 8);
          if (0x3f < (long)uVar8) {
            if ((long)uVar8 < 1) goto LAB_008a6430;
            goto LAB_008a6331;
          }
        }
        psVar11 = (string *)&::EMPTY_STRING;
        if (*(long *)(this + 0x1e0) != 0) {
          psVar11 = (string *)
                    ((ulong)*(uint *)(*plVar5 + 0x10) * 8 +
                    *(long *)(*(long *)(this + 0x1e0) + 0x28));
        }
        STRINGS::StringUpper((STRINGS *)local_48,psVar11);
        if ((ulong)uVar3 <= *(ulong *)(local_48[0] + -0x18)) {
                    /* try { // try from 008a63e5 to 008a63e9 has its CatchHandler @ 008a6512 */
          std::string::string((string *)local_58,(string *)local_48,0,(ulong)uVar3);
          bVar19 = false;
          lVar7 = *(long *)(local_58[0] + -0x18);
          if (lVar7 == *(long *)(*(char **)param_1 + -0x18)) {
            bVar19 = true;
            pcVar12 = local_58[0];
            pcVar14 = *(char **)param_1;
            do {
              if (lVar7 == 0) break;
              lVar7 = lVar7 + -1;
              bVar19 = *pcVar12 == *pcVar14;
              pcVar12 = pcVar12 + (ulong)bVar20 * -2 + 1;
              pcVar14 = pcVar14 + (ulong)bVar20 * -2 + 1;
            } while (bVar19);
          }
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar2 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar2 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
          }
          if (bVar19) {
            if ((allocator *)(local_48[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_48[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
                return 1;
              }
            }
            return 1;
          }
        }
        if ((allocator *)(local_48[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_48[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
          }
        }
        lVar7 = *(long *)(this + 0x188);
        lVar10 = *(long *)(this + 0x170);
        lVar16 = *(long *)(this + 0x180);
        lVar18 = *(long *)(this + 0x198);
        lVar17 = *(long *)(this + 400);
        lVar15 = *(long *)(this + 0x1a8);
      }
      uVar9 = uVar9 + 1;
      uVar4 = (ulong)uVar9;
    } while (uVar4 < (ulong)((lVar15 - lVar7 >> 3) * 0x40 + -0x40 +
                            (lVar16 - lVar10 >> 3) + (lVar17 - lVar18 >> 3)));
  }
  return 0;
}



/* address=008a6560
   symbol=CGenericModel::animationPlayingSubstring */

/* WARNING: Removing unreachable block (ram,0x008a68c6) */
/* WARNING: Removing unreachable block (ram,0x008a68bb) */
/* CGenericModel::animationPlayingSubstring(std::string const&) const */

undefined8 __thiscall CGenericModel::animationPlayingSubstring(CGenericModel *this,string *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  string *psVar11;
  char *pcVar12;
  ulong uVar13;
  char *pcVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  bool bVar19;
  byte bVar20;
  char *local_58 [2];
  long local_48 [3];

  bVar20 = 0;
  lVar17 = *(long *)(this + 400);
  lVar16 = *(long *)(this + 0x180);
  lVar10 = *(long *)(this + 0x170);
  lVar18 = *(long *)(this + 0x198);
  lVar15 = *(long *)(this + 0x1a8);
  uVar3 = *(uint *)(*(long *)param_1 + -0x18);
  lVar7 = *(long *)(this + 0x188);
  if ((lVar15 - lVar7 >> 3) * 0x40 + -0x40 + (lVar17 - lVar18 >> 3) + (lVar16 - lVar10 >> 3) != 0) {
    uVar4 = 0;
    uVar9 = 0;
    do {
      uVar8 = (lVar10 - *(long *)(this + 0x178) >> 3) + uVar4;
      uVar6 = (long)uVar8 >> 6;
      if ((long)uVar8 < 0) {
LAB_008a6778:
        uVar13 = ~(~uVar8 >> 6);
LAB_008a6659:
        plVar5 = (long *)((uVar8 + uVar13 * -0x40) * 8 + *(long *)(lVar7 + uVar13 * 8));
      }
      else {
        plVar5 = (long *)(lVar10 + uVar4 * 8);
        if (0x3f < (long)uVar8) {
          uVar13 = uVar6;
          if ((long)uVar8 < 1) goto LAB_008a6778;
          goto LAB_008a6659;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar8 < 0) {
LAB_008a6790:
          uVar13 = ~(~uVar8 >> 6);
LAB_008a66a1:
          plVar5 = (long *)((uVar8 + uVar13 * -0x40) * 8 + *(long *)(lVar7 + uVar13 * 8));
        }
        else {
          plVar5 = (long *)(lVar10 + uVar4 * 8);
          if (0x3f < (long)uVar8) {
            uVar13 = uVar6;
            if ((long)uVar8 < 1) goto LAB_008a6790;
            goto LAB_008a66a1;
          }
        }
        if (*(char *)(*plVar5 + 0x25) != '\0') {
          if ((long)uVar8 < 0) {
LAB_008a6818:
            uVar6 = ~(~uVar8 >> 6);
LAB_008a66e9:
            plVar5 = (long *)((uVar8 + uVar6 * -0x40) * 8 + *(long *)(lVar7 + uVar6 * 8));
          }
          else {
            plVar5 = (long *)(lVar10 + uVar4 * 8);
            if (0x3f < (long)uVar8) {
              if ((long)uVar8 < 1) goto LAB_008a6818;
              goto LAB_008a66e9;
            }
          }
          psVar11 = (string *)&::EMPTY_STRING;
          if (*(long *)(this + 0x1e0) != 0) {
            psVar11 = (string *)
                      ((ulong)*(uint *)(*plVar5 + 0x10) * 8 +
                      *(long *)(*(long *)(this + 0x1e0) + 0x28));
          }
          STRINGS::StringUpper((STRINGS *)local_48,psVar11);
          if ((ulong)uVar3 <= *(ulong *)(local_48[0] + -0x18)) {
                    /* try { // try from 008a67b5 to 008a67b9 has its CatchHandler @ 008a68a8 */
            std::string::string((string *)local_58,(string *)local_48,0,(ulong)uVar3);
            bVar19 = false;
            lVar7 = *(long *)(local_58[0] + -0x18);
            if (lVar7 == *(long *)(*(char **)param_1 + -0x18)) {
              bVar19 = true;
              pcVar12 = local_58[0];
              pcVar14 = *(char **)param_1;
              do {
                if (lVar7 == 0) break;
                lVar7 = lVar7 + -1;
                bVar19 = *pcVar12 == *pcVar14;
                pcVar12 = pcVar12 + (ulong)bVar20 * -2 + 1;
                pcVar14 = pcVar14 + (ulong)bVar20 * -2 + 1;
              } while (bVar19);
            }
            if ((allocator *)(local_58[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_58[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
              }
            }
            if (bVar19) {
              std::string::~string((string *)local_48);
              return 1;
            }
          }
          if ((allocator *)(local_48[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_48[0] + -8);
            iVar2 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar2 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
            }
          }
          lVar7 = *(long *)(this + 0x188);
          lVar10 = *(long *)(this + 0x170);
          lVar18 = *(long *)(this + 0x198);
          lVar17 = *(long *)(this + 400);
          lVar16 = *(long *)(this + 0x180);
          lVar15 = *(long *)(this + 0x1a8);
        }
      }
      uVar9 = uVar9 + 1;
      uVar4 = (ulong)uVar9;
    } while (uVar4 < (ulong)((lVar15 - lVar7 >> 3) * 0x40 + -0x40 +
                            (lVar16 - lVar10 >> 3) + (lVar17 - lVar18 >> 3)));
  }
  return 0;
}



/* address=008a68e0
   symbol=CGenericModel::clearQueuedAnimations */

/* CGenericModel::clearQueuedAnimations() */

void __thiscall CGenericModel::clearQueuedAnimations(CGenericModel *this)

{
  ulong uVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 *puVar4;
  long lVar5;
  long *plVar6;
  long *plVar7;
  ulong uVar8;
  long lVar9;
  long lVar10;
  ulong uVar11;
  void *pvVar12;
  int iVar13;
  int iVar14;
  void *pvVar15;
  long lVar16;

  lVar3 = *(long *)(this + 0x180);
  lVar5 = *(long *)(this + 0x170);
  plVar7 = *(long **)(this + 0x1a8);
  lVar10 = *(long *)(this + 0x188);
  if (0 < (int)((long)plVar7 - lVar10 >> 3) * 0x40 + -0x40 +
          (int)(lVar3 - lVar5 >> 3) + (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3)) {
    iVar14 = 0;
    do {
      lVar16 = *(long *)(this + 0x178);
      lVar9 = (long)iVar14;
      uVar1 = (lVar5 - lVar16 >> 3) + lVar9;
      uVar8 = (long)uVar1 >> 6;
      if ((long)uVar1 < 0) {
LAB_008a6cb0:
        uVar11 = ~(~uVar1 >> 6);
LAB_008a69cb:
        plVar6 = (long *)((uVar1 + uVar11 * -0x40) * 8 + *(long *)(lVar10 + uVar11 * 8));
      }
      else {
        plVar6 = (long *)(lVar5 + lVar9 * 8);
        if (0x3f < (long)uVar1) {
          uVar11 = uVar8;
          if ((long)uVar1 < 1) goto LAB_008a6cb0;
          goto LAB_008a69cb;
        }
      }
      if (*(char *)(*plVar6 + 0x26) == '\0') {
        lVar16 = *(long *)(this + 400);
        pvVar12 = *(void **)(this + 0x198);
      }
      else {
        if ((long)uVar1 < 0) {
LAB_008a6cc8:
          uVar11 = ~(~uVar1 >> 6);
LAB_008a6a13:
          plVar6 = (long *)((uVar1 + uVar11 * -0x40) * 8 + *(long *)(lVar10 + uVar11 * 8));
        }
        else {
          plVar6 = (long *)(lVar5 + lVar9 * 8);
          if (0x3f < (long)uVar1) {
            uVar11 = uVar8;
            if ((long)uVar1 < 1) goto LAB_008a6cc8;
            goto LAB_008a6a13;
          }
        }
        if (*plVar6 != 0) {
          if ((long)uVar1 < 0) {
LAB_008a6cf8:
            uVar8 = ~(~uVar1 >> 6);
LAB_008a6a58:
            plVar7 = (long *)((uVar1 + uVar8 * -0x40) * 8 + *(long *)(lVar10 + uVar8 * 8));
          }
          else {
            plVar7 = (long *)(lVar5 + lVar9 * 8);
            if (0x3f < (long)uVar1) {
              if ((long)uVar1 < 1) goto LAB_008a6cf8;
              goto LAB_008a6a58;
            }
          }
          if ((long *)*plVar7 != (long *)0x0) {
            (**(code **)(*(long *)*plVar7 + 8))();
            lVar16 = *(long *)(this + 0x178);
            lVar10 = *(long *)(this + 0x188);
            lVar5 = *(long *)(this + 0x170);
          }
          uVar1 = (lVar5 - lVar16 >> 3) + lVar9;
          if ((long)uVar1 < 0) {
LAB_008a6ce0:
            uVar8 = ~(~uVar1 >> 6);
LAB_008a6ac1:
            puVar2 = (undefined8 *)((uVar1 + uVar8 * -0x40) * 8 + *(long *)(lVar10 + uVar8 * 8));
          }
          else {
            puVar2 = (undefined8 *)(lVar5 + lVar9 * 8);
            if (0x3f < (long)uVar1) {
              if ((long)uVar1 < 1) goto LAB_008a6ce0;
              uVar8 = (long)uVar1 >> 6;
              goto LAB_008a6ac1;
            }
          }
          *puVar2 = 0;
          lVar10 = *(long *)(this + 0x188);
          lVar5 = *(long *)(this + 0x170);
          lVar3 = *(long *)(this + 0x180);
          plVar7 = *(long **)(this + 0x1a8);
        }
        pvVar15 = *(void **)(this + 400);
        pvVar12 = *(void **)(this + 0x198);
        if (iVar14 < (int)((long)pvVar15 - (long)pvVar12 >> 3) + (int)(lVar3 - lVar5 >> 3) + -0x41 +
                     (int)(((long)plVar7 - lVar10 >> 3) << 6)) {
          lVar16 = lVar9 * 8;
          iVar13 = iVar14;
          do {
            lVar3 = lVar5 - *(long *)(this + 0x178) >> 3;
            uVar1 = lVar3 + lVar9;
            if ((long)uVar1 < 0) {
LAB_008a6c70:
              uVar8 = ~(~uVar1 >> 6);
LAB_008a6c09:
              puVar2 = (undefined8 *)((uVar1 + uVar8 * -0x40) * 8 + *(long *)(lVar10 + uVar8 * 8));
              uVar1 = lVar3 + lVar9 + 1;
              if ((long)uVar1 < 0) goto LAB_008a6c2c;
LAB_008a6b65:
              if (0x3f < (long)uVar1) {
                if ((long)uVar1 < 1) goto LAB_008a6c2c;
                uVar8 = (long)uVar1 >> 6;
                goto LAB_008a6c4c;
              }
              puVar4 = (undefined8 *)(lVar5 + lVar16 + 8);
            }
            else {
              if (0x3f < (long)uVar1) {
                if ((long)uVar1 < 1) goto LAB_008a6c70;
                uVar8 = (long)uVar1 >> 6;
                goto LAB_008a6c09;
              }
              puVar2 = (undefined8 *)(lVar5 + lVar16);
              uVar1 = lVar3 + lVar9 + 1;
              if (-1 < (long)uVar1) goto LAB_008a6b65;
LAB_008a6c2c:
              uVar8 = ~(~uVar1 >> 6);
LAB_008a6c4c:
              puVar4 = (undefined8 *)((uVar1 + uVar8 * -0x40) * 8 + *(long *)(lVar10 + uVar8 * 8));
            }
            iVar13 = iVar13 + 1;
            lVar16 = lVar16 + 8;
            lVar9 = lVar9 + 1;
            *puVar2 = *puVar4;
            pvVar15 = *(void **)(this + 400);
            lVar3 = *(long *)(this + 0x180);
            pvVar12 = *(void **)(this + 0x198);
            lVar5 = *(long *)(this + 0x170);
            plVar7 = *(long **)(this + 0x1a8);
            lVar10 = *(long *)(this + 0x188);
          } while (iVar13 < (int)(lVar3 - lVar5 >> 3) + (int)((long)pvVar15 - (long)pvVar12 >> 3) +
                            -0x41 + (int)(((long)plVar7 - lVar10 >> 3) << 6));
        }
        if (pvVar12 == pvVar15) {
          operator_delete(pvVar12);
          lVar10 = *(long *)(this + 0x188);
          lVar5 = *(long *)(this + 0x170);
          lVar3 = *(long *)(this + 0x180);
          plVar7 = (long *)(*(long *)(this + 0x1a8) + -8);
          *(long **)(this + 0x1a8) = plVar7;
          pvVar12 = (void *)*plVar7;
          lVar16 = (long)pvVar12 + 0x1f8;
          *(void **)(this + 0x198) = pvVar12;
          *(long *)(this + 0x1a0) = (long)pvVar12 + 0x200;
          *(long *)(this + 400) = lVar16;
        }
        else {
          lVar16 = (long)pvVar15 + -8;
          *(long *)(this + 400) = lVar16;
        }
        iVar14 = iVar14 + -1;
      }
      iVar14 = iVar14 + 1;
    } while (iVar14 < (int)((long)plVar7 - lVar10 >> 3) * 0x40 + -0x40 +
                      (int)(lVar16 - (long)pvVar12 >> 3) + (int)(lVar3 - lVar5 >> 3));
  }
  return;
}



/* address=008a6d70
   symbol=CGenericModel::blendAnimation */

/* CGenericModel::blendAnimation(unsigned int, bool, float, float, float) */

void __thiscall
CGenericModel::blendAnimation
          (CGenericModel *this,uint param_1,bool param_2,float param_3,float param_4,float param_5)

{
  long lVar1;
  CRunicCore *this_00;
  long lVar2;
  ulong uVar3;
  undefined8 *puVar4;
  void *pvVar5;
  int iVar6;
  long *plVar7;
  int iVar8;
  long *plVar9;
  ulong uVar10;
  long lVar11;
  float fVar12;
  float fVar13;
  float local_38;

  if (*(int *)(this + 0x150) == 0) {
    return;
  }
  fVar12 = (float)getAnimationLengthSeconds(this,param_1);
  if ((fVar12 != 0.0) && ((param_3 != 0.0 || (NAN(param_3))))) {
    if (param_1 < *(uint *)(this + 0x154)) {
      *(bool *)(*(long *)((ulong)param_1 * 8 + *(long *)(this + 0x148)) + 0x2d) = param_2;
    }
    else {
      *(bool *)(**(long **)(this + 0x148) + 0x2d) = param_2;
    }
    fVar13 = (float)Ogre::AnimationState::getLength();
    fVar12 = fVar13;
    if (param_3 <= fVar13) {
      fVar12 = param_3;
    }
    clearQueuedAnimations(this);
    this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x40,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a6e5c to 008a6e60 has its CatchHandler @ 008a71af */
    CRunicCore::CRunicCore(this_00);
    *(undefined ***)this_00 = &PTR__CActiveAnimation_00fd1750;
    *(uint *)(this_00 + 0x10) = param_1;
    *(undefined4 *)(this_00 + 0x20) = 0;
    *(float *)(this_00 + 0x18) = fVar13;
    this_00[0x24] = (CRunicCore)param_2;
    this_00[0x25] = (CRunicCore)0x0;
    *(float *)(this_00 + 0x1c) = fVar13;
    this_00[0x26] = (CRunicCore)0x0;
    this_00[0x27] = (CRunicCore)0x0;
    this_00[0x28] = (CRunicCore)0x0;
    this_00[0x29] = (CRunicCore)0x0;
    this_00[0x2a] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x2c) = 0;
    *(undefined4 *)(this_00 + 0x30) = 0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    *(float *)(this_00 + 0x38) = param_4;
    if (((param_5 != DAT_00fa8760) || (local_38 = fVar12, NAN(param_5) || NAN(DAT_00fa8760))) &&
       (*(float *)(this_00 + 0x18) = param_5, local_38 = param_5, fVar12 <= param_5)) {
      local_38 = fVar12;
    }
    this_00[0x25] = (CRunicCore)0x1;
    this_00[0x26] = (CRunicCore)0x0;
    *(undefined4 *)(this_00 + 0x34) = 0;
    if (*(float *)(this_00 + 0x18) != 0.0) {
      *(float *)(this_00 + 0x2c) = local_38;
      *(float *)(this_00 + 0x30) = local_38;
      *(uint *)(this_00 + 0x34) = DAT_00fa47fc & -(uint)(local_38 != 0.0);
    }
    if (param_1 < *(uint *)(this + 0x154)) {
      puVar4 = (undefined8 *)((ulong)param_1 * 8 + *(long *)(this + 0x148));
    }
    else {
      puVar4 = *(undefined8 **)(this + 0x148);
    }
    Ogre::AnimationState::setEnabled(SUB81(*puVar4,0));
    lVar11 = *(long *)(this + 0x170);
    if (lVar11 == *(long *)(this + 0x178)) {
      lVar11 = *(long *)(this + 0x188);
      if (lVar11 - *(long *)(this + 0x160) >> 3 == 0) {
        std::deque<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_reallocate_map
                  ((deque<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),1,
                   true);
        lVar11 = *(long *)(this + 0x188);
      }
      pvVar5 = operator_new(0x200);
      *(void **)(lVar11 + -8) = pvVar5;
      lVar2 = *(long *)(this + 0x188);
      plVar9 = (long *)0x0;
      lVar11 = lVar2 + -8;
      *(long *)(this + 0x188) = lVar11;
      lVar1 = *(long *)(lVar2 + -8);
      lVar2 = lVar1 + 0x200;
      *(long *)(this + 0x178) = lVar1;
      *(long *)(this + 0x180) = lVar2;
      *(long *)(this + 0x170) = lVar1 + 0x1f8;
      if (lVar1 + 0x1f8 != 0) {
        *(CRunicCore **)(lVar1 + 0x1f8) = this_00;
        lVar11 = *(long *)(this + 0x188);
        plVar9 = *(long **)(this + 0x170);
        lVar2 = *(long *)(this + 0x180);
      }
    }
    else {
      plVar9 = (long *)0x0;
      if (lVar11 != 8) {
        *(CRunicCore **)(lVar11 + -8) = this_00;
        plVar9 = (long *)(*(long *)(this + 0x170) + -8);
      }
      lVar11 = *(long *)(this + 0x188);
      lVar2 = *(long *)(this + 0x180);
      *(long **)(this + 0x170) = plVar9;
    }
    iVar8 = (int)(lVar2 - (long)plVar9 >> 3) +
            (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) + -0x40 +
            (int)((*(long *)(this + 0x1a8) - lVar11 >> 3) << 6);
    if (1 < iVar8) {
      iVar6 = 1;
      uVar3 = (long)plVar9 - *(long *)(this + 0x178) >> 3;
      do {
        plVar9 = plVar9 + 1;
        uVar3 = uVar3 + 1;
        if (((long)uVar3 < 0) || (plVar7 = plVar9, 0x3f < (long)uVar3)) {
          if ((long)uVar3 < 1) {
            uVar10 = ~(~uVar3 >> 6);
          }
          else {
            uVar10 = (long)uVar3 >> 6;
          }
          plVar7 = (long *)((uVar3 + uVar10 * -0x40) * 8 + *(long *)(lVar11 + uVar10 * 8));
        }
        if (param_1 == *(uint *)(*plVar7 + 0x10)) {
          return;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar8);
    }
    Ogre::AnimationState::setWeight(0.0);
    return;
  }
  playAnimation(this,param_1,param_2,param_4,param_5);
  return;
}



/* address=008a71d0
   symbol=CGenericModel::blendAnimation */

/* WARNING: Removing unreachable block (ram,0x008a72f1) */
/* CGenericModel::blendAnimation(std::string const&, bool, float, float, float) */

void __thiscall
CGenericModel::blendAnimation
          (CGenericModel *this,string *param_1,bool param_2,float param_3,float param_4,
          float param_5)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  byte bVar8;
  char *local_48 [3];

  bVar8 = 0;
  lVar3 = *(long *)(this + 0x1e0);
  if ((lVar3 == 0) || (*(int *)(lVar3 + 0x20) == 0)) {
    return;
  }
  uVar4 = 0;
  do {
    STRINGS::StringUpper((STRINGS *)local_48,(string *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x28)))
    ;
    bVar7 = false;
    lVar3 = *(long *)(local_48[0] + -0x18);
    if (lVar3 == *(long *)(*(char **)param_1 + -0x18)) {
      bVar7 = true;
      pcVar5 = local_48[0];
      pcVar6 = *(char **)param_1;
      do {
        if (lVar3 == 0) break;
        lVar3 = lVar3 + -1;
        bVar7 = *pcVar5 == *pcVar6;
        pcVar5 = pcVar5 + (ulong)bVar8 * -2 + 1;
        pcVar6 = pcVar6 + (ulong)bVar8 * -2 + 1;
      } while (bVar7);
    }
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if (bVar7) {
      blendAnimation(this,uVar4,param_2,param_3,param_4,param_5);
      lVar3 = *(long *)(this + 0x1e0);
      uVar4 = uVar4 + 1;
      if (*(uint *)(lVar3 + 0x20) <= uVar4) {
        return;
      }
    }
    else {
      lVar3 = *(long *)(this + 0x1e0);
      uVar4 = uVar4 + 1;
      if (*(uint *)(lVar3 + 0x20) <= uVar4) {
        return;
      }
    }
  } while( true );
}



/* address=008a7300
   symbol=CGenericModel::loopingAnimationPlaying */

/* CGenericModel::loopingAnimationPlaying() */

undefined8 __thiscall CGenericModel::loopingAnimationPlaying(CGenericModel *this)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 0x180) - lVar2 >> 3) +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3);
  if (uVar1 != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar7 = uVar4 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar7 >> 6;
      if ((long)uVar7 < 0) {
LAB_008a7458:
        uVar9 = ~(~uVar7 >> 6);
LAB_008a73a4:
        plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar4 * 8);
        if (0x3f < (long)uVar7) {
          uVar9 = uVar6;
          if ((long)uVar7 < 1) goto LAB_008a7458;
          goto LAB_008a73a4;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar7 < 0) {
LAB_008a7470:
          uVar9 = ~(~uVar7 >> 6);
LAB_008a73e8:
          plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar4 * 8);
          if (0x3f < (long)uVar7) {
            uVar9 = uVar6;
            if ((long)uVar7 < 1) goto LAB_008a7470;
            goto LAB_008a73e8;
          }
        }
        if (*(char *)(*plVar5 + 0x25) != '\0') {
          if ((long)uVar7 < 0) {
LAB_008a7490:
            uVar6 = ~(~uVar7 >> 6);
LAB_008a7428:
            plVar5 = (long *)((uVar7 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
          }
          else {
            plVar5 = (long *)(lVar2 + uVar4 * 8);
            if (0x3f < (long)uVar7) {
              if ((long)uVar7 < 1) goto LAB_008a7490;
              goto LAB_008a7428;
            }
          }
          if (*(char *)(*plVar5 + 0x24) != '\0') {
            return 1;
          }
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < uVar1);
  }
  return 0;
}



/* address=008a74a0
   symbol=CGenericModel::setAnimationSpeed */

/* CGenericModel::setAnimationSpeed(std::string const&, float) */

void CGenericModel::setAnimationSpeed(string *param_1,float param_2)

{
  ulong uVar1;
  long *plVar2;
  ulong uVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;

  lVar11 = *(long *)(param_1 + 400);
  lVar7 = *(long *)(param_1 + 0x170);
  lVar10 = *(long *)(param_1 + 0x1a8);
  lVar9 = *(long *)(param_1 + 0x188);
  lVar6 = *(long *)(param_1 + 0x180);
  lVar5 = *(long *)(param_1 + 0x198);
  if ((lVar10 - lVar9 >> 3) * 0x40 + -0x40 + (lVar6 - lVar7 >> 3) + (lVar11 - lVar5 >> 3) != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar1 = (lVar7 - *(long *)(param_1 + 0x178) >> 3) + uVar4;
      uVar3 = (long)uVar1 >> 6;
      if ((long)uVar1 < 0) {
LAB_008a7670:
        uVar12 = ~(~uVar1 >> 6);
LAB_008a757b:
        plVar2 = (long *)((uVar1 + uVar12 * -0x40) * 8 + *(long *)(lVar9 + uVar12 * 8));
      }
      else {
        plVar2 = (long *)(lVar7 + uVar4 * 8);
        if (0x3f < (long)uVar1) {
          uVar12 = uVar3;
          if ((long)uVar1 < 1) goto LAB_008a7670;
          goto LAB_008a757b;
        }
      }
      if (*(char *)(*plVar2 + 0x26) == '\0') {
        if ((long)uVar1 < 0) {
LAB_008a7688:
          uVar12 = ~(~uVar1 >> 6);
LAB_008a75c3:
          plVar2 = (long *)((uVar1 + uVar12 * -0x40) * 8 + *(long *)(lVar9 + uVar12 * 8));
        }
        else {
          plVar2 = (long *)(lVar7 + uVar4 * 8);
          if (0x3f < (long)uVar1) {
            uVar12 = uVar3;
            if ((long)uVar1 < 1) goto LAB_008a7688;
            goto LAB_008a75c3;
          }
        }
        if (*(char *)(*plVar2 + 0x25) != '\0') {
          if ((long)uVar1 < 0) {
LAB_008a76a0:
            uVar3 = ~(~uVar1 >> 6);
LAB_008a760b:
            plVar2 = (long *)((uVar1 + uVar3 * -0x40) * 8 + *(long *)(lVar9 + uVar3 * 8));
          }
          else {
            plVar2 = (long *)(lVar7 + uVar4 * 8);
            if (0x3f < (long)uVar1) {
              if ((long)uVar1 < 1) goto LAB_008a76a0;
              goto LAB_008a760b;
            }
          }
          *(float *)(*plVar2 + 0x38) = param_2;
          lVar9 = *(long *)(param_1 + 0x188);
          lVar7 = *(long *)(param_1 + 0x170);
          lVar6 = *(long *)(param_1 + 0x180);
          lVar5 = *(long *)(param_1 + 0x198);
          lVar11 = *(long *)(param_1 + 400);
          lVar10 = *(long *)(param_1 + 0x1a8);
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < (ulong)((lVar10 - lVar9 >> 3) * 0x40 + -0x40 +
                            (lVar6 - lVar7 >> 3) + (lVar11 - lVar5 >> 3)));
  }
  return;
}



/* address=008a76c0
   symbol=CGenericModel::animationPlaying */

/* CGenericModel::animationPlaying(unsigned int) const */

undefined8 __thiscall CGenericModel::animationPlaying(CGenericModel *this,uint param_1)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 0x180) - lVar2 >> 3) +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3);
  if (uVar1 != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar7 = uVar4 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar7 >> 6;
      if ((long)uVar7 < 0) {
LAB_008a7818:
        uVar9 = ~(~uVar7 >> 6);
LAB_008a7764:
        plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar4 * 8);
        if (0x3f < (long)uVar7) {
          uVar9 = uVar6;
          if ((long)uVar7 < 1) goto LAB_008a7818;
          goto LAB_008a7764;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar7 < 0) {
LAB_008a7830:
          uVar9 = ~(~uVar7 >> 6);
LAB_008a77a8:
          plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar4 * 8);
          if (0x3f < (long)uVar7) {
            uVar9 = uVar6;
            if ((long)uVar7 < 1) goto LAB_008a7830;
            goto LAB_008a77a8;
          }
        }
        if (param_1 == *(uint *)(*plVar5 + 0x10)) {
          if ((long)uVar7 < 0) {
LAB_008a7850:
            uVar6 = ~(~uVar7 >> 6);
LAB_008a77e7:
            plVar5 = (long *)((uVar7 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
          }
          else {
            plVar5 = (long *)(lVar2 + uVar4 * 8);
            if (0x3f < (long)uVar7) {
              if ((long)uVar7 < 1) goto LAB_008a7850;
              goto LAB_008a77e7;
            }
          }
          if (*(char *)(*plVar5 + 0x25) != '\0') {
            return 1;
          }
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < uVar1);
  }
  return 0;
}



/* address=008a7860
   symbol=CGenericModel::animationPlaying */

/* CGenericModel::animationPlaying(std::string const&) const */

void __thiscall CGenericModel::animationPlaying(CGenericModel *this,string *param_1)

{
  uint uVar1;

  uVar1 = getAnimationIndex(this,param_1);
  animationPlaying(this,uVar1);
  return;
}



/* address=008a7880
   symbol=CGenericModel::currentAnimation */

/* CGenericModel::currentAnimation() const */

undefined4 __thiscall CGenericModel::currentAnimation(CGenericModel *this)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 0x180) - lVar2 >> 3) +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3);
  if (uVar1 != 0) {
    uVar7 = 0;
    uVar8 = 0;
    do {
      uVar4 = uVar7 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar4 >> 6;
      if ((long)uVar4 < 0) {
LAB_008a7979:
        uVar9 = ~(~uVar4 >> 6);
LAB_008a7906:
        plVar5 = (long *)((uVar4 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar7 * 8);
        if (0x3f < (long)uVar4) {
          uVar9 = uVar6;
          if ((long)uVar4 < 1) goto LAB_008a7979;
          goto LAB_008a7906;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar4 < 0) {
LAB_008a7990:
          uVar9 = ~(~uVar4 >> 6);
LAB_008a7942:
          plVar5 = (long *)((uVar4 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar7 * 8);
          if (0x3f < (long)uVar4) {
            uVar9 = uVar6;
            if ((long)uVar4 < 1) goto LAB_008a7990;
            goto LAB_008a7942;
          }
        }
        if (*(char *)(*plVar5 + 0x25) != '\0') {
          if ((long)uVar4 < 0) {
LAB_008a79f0:
            uVar6 = ~(~uVar4 >> 6);
          }
          else {
            plVar5 = (long *)(lVar2 + uVar7 * 8);
            if ((long)uVar4 < 0x40) goto LAB_008a79e1;
            if ((long)uVar4 < 1) goto LAB_008a79f0;
          }
          plVar5 = (long *)((uVar4 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
LAB_008a79e1:
          return *(undefined4 *)(*plVar5 + 0x10);
        }
      }
      uVar8 = uVar8 + 1;
      uVar7 = (ulong)uVar8;
    } while (uVar7 < uVar1);
  }
  return 0xffffffff;
}



/* address=008a7a00
   symbol=CGenericModel::setHighlightTexture */

/* WARNING: Removing unreachable block (ram,0x008a7bf4) */
/* WARNING: Removing unreachable block (ram,0x008a7c5c) */
/* WARNING: Removing unreachable block (ram,0x008a7c51) */
/* WARNING: Removing unreachable block (ram,0x008a7be9) */
/* CGenericModel::setHighlightTexture(std::wstring const&) */

void __thiscall CGenericModel::setHighlightTexture(CGenericModel *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  ushort uVar3;
  CFileSystem *this_00;
  long lVar4;
  string *psVar5;
  uint uVar6;
  ulong uVar7;
  undefined1 *local_68;
  long local_60;
  long local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  char local_40;

  local_68 = &DAT_01423a38;
                    /* try { // try from 008a7a25 to 008a7a29 has its CatchHandler @ 008a7b92 */
  std::string::string((string *)&local_60,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a7a34 to 008a7a38 has its CatchHandler @ 008a7c7a */
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)&::EMPTY_WSTRING);
  local_50 = 4;
  local_4c = 3;
  local_48 = &DAT_01423a38;
  local_40 = '\0';
                    /* try { // try from 008a7a57 to 008a7afb has its CatchHandler @ 008a7c67 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_1,(CFileInfo *)&local_68,false,true,false);
  if ((local_40 != '\0') &&
     (lVar4 = *(long *)(this + 0x208), (int)((ulong)(*(long *)(this + 0x210) - lVar4) >> 6) != 0)) {
    uVar7 = 0;
    do {
      uVar3 = Ogre::Material::getBestTechnique
                        ((ushort)*(undefined8 *)(uVar7 * 0x40 + 0x18 + lVar4),(Renderable *)0x0);
      lVar4 = Ogre::Technique::getPass(uVar3);
      if (1 < (ushort)((ulong)(*(long *)(lVar4 + 0xf0) - *(long *)(lVar4 + 0xe8)) >> 3)) {
        psVar5 = (string *)Ogre::Pass::getTextureUnitState((ushort)lVar4);
        Ogre::TextureUnitState::setCubicTextureName(psVar5,SUB81(&local_60,0));
        lVar4 = *(long *)(this + 0x68);
        if (((lVar4 != 0) && (*(int *)(lVar4 + 0x30) != 0)) && (**(long **)(lVar4 + 0x28) != 0)) {
          *(undefined1 *)(**(long **)(lVar4 + 0x28) + 0x38d4) = 1;
        }
      }
      lVar4 = *(long *)(this + 0x208);
      uVar6 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar6;
    } while (uVar6 < (uint)(*(long *)(this + 0x210) - lVar4 >> 6));
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if ((allocator *)(local_60 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_60 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_60 + -0x18));
    }
  }
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  return;
}



/* address=008a7c90
   symbol=CGenericModel::setRenderBehindTexture */

/* WARNING: Removing unreachable block (ram,0x008a7ea5) */
/* WARNING: Removing unreachable block (ram,0x008a7f0d) */
/* WARNING: Removing unreachable block (ram,0x008a7f02) */
/* WARNING: Removing unreachable block (ram,0x008a7e9a) */
/* CGenericModel::setRenderBehindTexture(std::wstring const&) */

void __thiscall CGenericModel::setRenderBehindTexture(CGenericModel *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  ushort uVar4;
  CFileSystem *this_00;
  long lVar5;
  undefined8 uVar6;
  long lVar7;
  uint uVar8;
  undefined1 *local_68;
  long local_60;
  long local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  char local_40;

  local_68 = &DAT_01423a38;
                    /* try { // try from 008a7cb5 to 008a7cb9 has its CatchHandler @ 008a7e43 */
  std::string::string((string *)&local_60,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a7cc4 to 008a7cc8 has its CatchHandler @ 008a7f2b */
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)&::EMPTY_WSTRING);
  local_50 = 4;
  local_4c = 3;
  local_48 = &DAT_01423a38;
  local_40 = '\0';
                    /* try { // try from 008a7ce7 to 008a7db6 has its CatchHandler @ 008a7f18 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_1,(CFileInfo *)&local_68,false,true,false);
  if (local_40 != '\0') {
    lVar7 = *(long *)(this + 0x210);
    lVar5 = *(long *)(this + 0x208);
    if ((int)((ulong)(lVar7 - lVar5) >> 6) != 0) {
      uVar8 = 0;
      do {
        lVar3 = *(long *)(lVar5 + 0x20 + (ulong)uVar8 * 0x40);
        if (lVar3 != 0) {
          uVar4 = Ogre::Material::getBestTechnique((ushort)lVar3,(Renderable *)0x0);
          lVar5 = Ogre::Technique::getPass(uVar4);
          if ((short)((ulong)(*(long *)(lVar5 + 0xf0) - *(long *)(lVar5 + 0xe8)) >> 3) != 0) {
            uVar6 = Ogre::Pass::getTextureUnitState((ushort)lVar5);
            Ogre::TextureUnitState::setTextureName(uVar6,&local_60,2);
            lVar5 = *(long *)(this + 0x68);
            if (((lVar5 != 0) && (*(int *)(lVar5 + 0x30) != 0)) && (**(long **)(lVar5 + 0x28) != 0))
            {
              *(undefined1 *)(**(long **)(lVar5 + 0x28) + 0x38d4) = 1;
            }
          }
          lVar5 = *(long *)(this + 0x208);
          lVar7 = *(long *)(this + 0x210);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < (uint)(lVar7 - lVar5 >> 6));
    }
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if ((allocator *)(local_60 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_60 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_60 + -0x18));
    }
  }
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  return;
}



/* address=008a7f40
   symbol=CGenericModel::getAnimationTime */

/* CGenericModel::getAnimationTime() */

undefined4 __thiscall CGenericModel::getAnimationTime(CGenericModel *this)

{
  ulong uVar1;
  long lVar2;
  long lVar3;
  ulong uVar4;
  long *plVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  lVar2 = *(long *)(this + 0x170);
  lVar3 = *(long *)(this + 0x188);
  uVar1 = (*(long *)(this + 0x1a8) - lVar3 >> 3) * 0x40 + -0x40 +
          (*(long *)(this + 0x180) - lVar2 >> 3) +
          (*(long *)(this + 400) - *(long *)(this + 0x198) >> 3);
  if (uVar1 != 0) {
    uVar4 = 0;
    uVar8 = 0;
    do {
      uVar7 = uVar4 + (lVar2 - *(long *)(this + 0x178) >> 3);
      uVar6 = (long)uVar7 >> 6;
      if ((long)uVar7 < 0) {
LAB_008a8090:
        uVar9 = ~(~uVar7 >> 6);
LAB_008a7fe4:
        plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
      }
      else {
        plVar5 = (long *)(lVar2 + uVar4 * 8);
        if (0x3f < (long)uVar7) {
          uVar9 = uVar6;
          if ((long)uVar7 < 1) goto LAB_008a8090;
          goto LAB_008a7fe4;
        }
      }
      if (*(char *)(*plVar5 + 0x26) == '\0') {
        if ((long)uVar7 < 0) {
LAB_008a80a8:
          uVar9 = ~(~uVar7 >> 6);
LAB_008a8028:
          plVar5 = (long *)((uVar7 + uVar9 * -0x40) * 8 + *(long *)(lVar3 + uVar9 * 8));
        }
        else {
          plVar5 = (long *)(lVar2 + uVar4 * 8);
          if (0x3f < (long)uVar7) {
            uVar9 = uVar6;
            if ((long)uVar7 < 1) goto LAB_008a80a8;
            goto LAB_008a8028;
          }
        }
        if (*(char *)(*plVar5 + 0x25) != '\0') {
          if ((long)uVar7 < 0) {
LAB_008a80c5:
            uVar6 = ~(~uVar7 >> 6);
          }
          else {
            plVar5 = (long *)(lVar2 + uVar4 * 8);
            if ((long)uVar7 < 0x40) goto LAB_008a807e;
            if ((long)uVar7 < 1) goto LAB_008a80c5;
          }
          plVar5 = (long *)((uVar7 + uVar6 * -0x40) * 8 + *(long *)(lVar3 + uVar6 * 8));
LAB_008a807e:
          return *(undefined4 *)(*plVar5 + 0x20);
        }
      }
      uVar8 = uVar8 + 1;
      uVar4 = (ulong)uVar8;
    } while (uVar4 < uVar1);
  }
  return 0;
}



/* address=008a80e0
   symbol=CGenericModel::setRimLighting */

/* WARNING: Removing unreachable block (ram,0x008a859d) */
/* WARNING: Removing unreachable block (ram,0x008a85df) */
/* WARNING: Removing unreachable block (ram,0x008a8685) */
/* WARNING: Removing unreachable block (ram,0x008a85ea) */
/* WARNING: Removing unreachable block (ram,0x008a85a8) */
/* WARNING: Removing unreachable block (ram,0x008a858f) */
/* CGenericModel::setRimLighting(std::wstring) */

void __thiscall CGenericModel::setRimLighting(CGenericModel *this,wstring_conflict *param_2)

{
  int *piVar1;
  long lVar2;
  CGenericModel CVar3;
  ushort uVar4;
  int iVar5;
  CFileSystem *this_00;
  long lVar6;
  string *psVar7;
  long lVar8;
  uint uVar9;
  undefined1 *local_c8;
  long local_c0;
  long local_b8;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined1 *local_a8;
  char local_a0;
  undefined **local_98;
  undefined8 local_90;
  int *local_88;
  undefined **local_78;
  undefined8 local_70;
  int *local_68;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  local_c8 = &DAT_01423a38;
                    /* try { // try from 008a810c to 008a8110 has its CatchHandler @ 008a8532 */
  std::string::string((string *)&local_c0,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a811e to 008a8122 has its CatchHandler @ 008a8512 */
  std::wstring::wstring((wstring_conflict *)&local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_b0 = 4;
  local_ac = 3;
  local_a8 = &DAT_01423a38;
  local_a0 = '\0';
                    /* try { // try from 008a8141 to 008a8259 has its CatchHandler @ 008a8510 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_2,(CFileInfo *)&local_c8,false,true,false);
  uVar9 = KSETTINGS_RIMLIGHTS_ENABLED;
  lVar6 = CMasterResourceManager::getSingleton();
  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar9);
  uVar9 = KSETTINGS_NETBOOK_MODE;
  if (iVar5 != 0) {
    lVar6 = CMasterResourceManager::getSingleton();
    iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar9);
    if ((iVar5 != 1) && (local_a0 != '\0')) {
      lVar8 = *(long *)(this + 0x210);
      lVar6 = *(long *)(this + 0x208);
      CVar3 = this[0x238];
      if ((int)((ulong)(lVar8 - lVar6) >> 6) != 0) {
        uVar9 = 0;
        do {
          lVar2 = lVar6 + (ulong)uVar9 * 0x40;
          if ((*(char *)(lVar2 + 0x2f) == '\0') && (lVar2 = *(long *)(lVar2 + 0x10), lVar2 != 0)) {
                    /* try { // try from 008a8332 to 008a83bc has its CatchHandler @ 008a8510 */
            uVar4 = Ogre::Material::getBestTechnique((ushort)lVar2,(Renderable *)0x0);
            lVar6 = Ogre::Technique::getPass(uVar4);
            if ((lVar6 != 0) &&
               ((short)((ulong)(*(long *)(lVar6 + 0xf0) - *(long *)(lVar6 + 0xe8)) >> 3) != 0)) {
              if (CVar3 == (CGenericModel)0x0) {
                psVar7 = (string *)Ogre::Pass::createTextureUnitState();
                Ogre::TextureUnitState::setCubicTextureName(psVar7,SUB81(&local_c0,0));
                Ogre::TextureUnitState::setTextureCoordSet((uint)psVar7);
                Ogre::TextureUnitState::setTextureAddressingMode(psVar7,2);
                Ogre::TextureUnitState::setEnvironmentMap(psVar7,1,3);
                Ogre::TextureUnitState::setColourOperation(psVar7);
                if (*(long *)(lVar6 + 0x100) != 0) {
                    /* try { // try from 008a83dd to 008a83e1 has its CatchHandler @ 008a8619 */
                  std::string::string((string *)local_58,"texViewProj",&local_3a);
                    /* try { // try from 008a83ea to 008a83ee has its CatchHandler @ 008a8614 */
                  Ogre::Pass::getVertexProgramParameters();
                    /* try { // try from 008a8400 to 008a8404 has its CatchHandler @ 008a85f8 */
                  Ogre::GpuProgramParameters::setNamedAutoConstant(local_90,local_58,0x79,0);
                  local_98 = &PTR__SharedPtr_00fd1950;
                  if ((local_88 != (int *)0x0) &&
                     (iVar5 = *local_88, *local_88 = iVar5 + -1, iVar5 + -1 == 0)) {
                    /* try { // try from 008a8428 to 008a842c has its CatchHandler @ 008a8614 */
                    Ogre::SharedPtr<Ogre::GpuProgramParameters>::destroy
                              ((SharedPtr<Ogre::GpuProgramParameters> *)&local_98);
                  }
                  if ((allocator *)(local_58[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_58[0] + -8);
                    iVar5 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar5 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
                    }
                  }
                }
              }
              else {
                psVar7 = (string *)Ogre::Pass::getTextureUnitState((ushort)lVar6);
                Ogre::TextureUnitState::setCubicTextureName(psVar7,SUB81(&local_c0,0));
                Ogre::TextureUnitState::setTextureCoordSet((uint)psVar7);
                Ogre::TextureUnitState::setTextureAddressingMode(psVar7,2);
                Ogre::TextureUnitState::setEnvironmentMap(psVar7,1,3);
                Ogre::TextureUnitState::setColourOperation(psVar7);
                if (*(long *)(lVar6 + 0x100) != 0) {
                    /* try { // try from 008a827d to 008a8281 has its CatchHandler @ 008a84fd */
                  std::string::string((string *)&local_48,"texViewProj",local_39);
                    /* try { // try from 008a828a to 008a828e has its CatchHandler @ 008a8680 */
                  Ogre::Pass::getVertexProgramParameters();
                    /* try { // try from 008a82a3 to 008a82a7 has its CatchHandler @ 008a8661 */
                  Ogre::GpuProgramParameters::setNamedAutoConstant(local_70,&local_48,0x79,0);
                  local_78 = &PTR__SharedPtr_00fd1950;
                  if ((local_68 != (int *)0x0) &&
                     (iVar5 = *local_68, *local_68 = iVar5 + -1, iVar5 + -1 == 0)) {
                    /* try { // try from 008a82cb to 008a82cf has its CatchHandler @ 008a8680 */
                    Ogre::SharedPtr<Ogre::GpuProgramParameters>::destroy
                              ((SharedPtr<Ogre::GpuProgramParameters> *)&local_78);
                  }
                  if ((allocator *)(local_48 + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_48 + -8);
                    iVar5 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar5 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
                      lVar6 = *(long *)(this + 0x208);
                      lVar8 = *(long *)(this + 0x210);
                      goto LAB_008a8300;
                    }
                  }
                }
              }
            }
            lVar6 = *(long *)(this + 0x208);
            lVar8 = *(long *)(this + 0x210);
          }
LAB_008a8300:
          uVar9 = uVar9 + 1;
        } while (uVar9 < (uint)(lVar8 - lVar6 >> 6));
      }
      this[0x238] = (CGenericModel)0x1;
      if ((allocator *)(local_a8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_a8 + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_a8 + -0x18));
        }
      }
      if ((allocator *)(local_b8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_b8 + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8 + -0x18));
        }
      }
      if ((allocator *)(local_c0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_c0 + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_c0 + -0x18));
        }
      }
      if ((allocator *)(local_c8 + -0x18) == (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        return;
      }
      LOCK();
      piVar1 = (int *)(local_c8 + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (0 < iVar5) {
        return;
      }
      std::string::_Rep::_M_destroy((allocator *)(local_c8 + -0x18));
      return;
    }
  }
  CFileInfo::~CFileInfo((CFileInfo *)&local_c8);
  return;
}



/* address=008a8690
   symbol=CGenericModel::loadAnimations */

/* WARNING: Removing unreachable block (ram,0x008a9ab7) */
/* WARNING: Removing unreachable block (ram,0x008a9b25) */
/* WARNING: Removing unreachable block (ram,0x008a9e14) */
/* WARNING: Removing unreachable block (ram,0x008a9da6) */
/* WARNING: Removing unreachable block (ram,0x008aa2e5) */
/* WARNING: Removing unreachable block (ram,0x008aa12c) */
/* WARNING: Removing unreachable block (ram,0x008aa19b) */
/* WARNING: Removing unreachable block (ram,0x008aa3b6) */
/* WARNING: Removing unreachable block (ram,0x008aa077) */
/* WARNING: Removing unreachable block (ram,0x008a9d2a) */
/* WARNING: Removing unreachable block (ram,0x008a9f67) */
/* WARNING: Removing unreachable block (ram,0x008a9d35) */
/* WARNING: Removing unreachable block (ram,0x008a9bfd) */
/* WARNING: Removing unreachable block (ram,0x008a9b30) */
/* WARNING: Removing unreachable block (ram,0x008a9ef9) */
/* WARNING: Removing unreachable block (ram,0x008a9ebd) */
/* WARNING: Removing unreachable block (ram,0x008a9b86) */
/* WARNING: Removing unreachable block (ram,0x008a9d1c) */
/* WARNING: Removing unreachable block (ram,0x008a9d43) */
/* WARNING: Removing unreachable block (ram,0x008a9fae) */
/* WARNING: Removing unreachable block (ram,0x008aa01e) */
/* WARNING: Removing unreachable block (ram,0x008aa47a) */
/* WARNING: Removing unreachable block (ram,0x008aa423) */
/* WARNING: Removing unreachable block (ram,0x008aa30e) */
/* WARNING: Removing unreachable block (ram,0x008aa137) */
/* WARNING: Removing unreachable block (ram,0x008a9f5c) */
/* WARNING: Removing unreachable block (ram,0x008a9db1) */
/* WARNING: Removing unreachable block (ram,0x008a9e1f) */
/* WARNING: Removing unreachable block (ram,0x008a9ac2) */
/* WARNING: Removing unreachable block (ram,0x008aa45e) */
/* WARNING: Removing unreachable block (ram,0x008aa42e) */
/* WARNING: Removing unreachable block (ram,0x008aa1fe) */
/* WARNING: Removing unreachable block (ram,0x008aa46c) */
/* WARNING: Removing unreachable block (ram,0x008aa209) */
/* WARNING: Removing unreachable block (ram,0x008aa488) */
/* WARNING: Removing unreachable block (ram,0x008aa26c) */
/* WARNING: Removing unreachable block (ram,0x008aa496) */
/* WARNING: Removing unreachable block (ram,0x008aa277) */
/* WARNING: Removing unreachable block (ram,0x008a9a51) */
/* WARNING: Removing unreachable block (ram,0x008aa2da) */
/* CGenericModel::loadAnimations(Ogre::Entity*, std::wstring, std::wstring, bool) */

void __thiscall
CGenericModel::loadAnimations
          (CGenericModel *this,long param_1,undefined8 param_3,wstring_conflict *param_4,
          char param_5)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  int *piVar3;
  undefined8 *puVar4;
  wchar_t wVar5;
  int iVar6;
  long *plVar7;
  CDataGroup *this_00;
  wchar_t *pwVar8;
  code *pcVar9;
  undefined8 *puVar10;
  string *psVar11;
  string *psVar12;
  char cVar13;
  ushort uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  CFileSystem *pCVar18;
  CDataGroup *this_01;
  wstring_conflict *pwVar19;
  long *plVar20;
  string *psVar21;
  string *psVar22;
  undefined8 uVar23;
  long lVar24;
  long lVar25;
  ulong uVar26;
  uint uVar27;
  char *pcVar28;
  char *pcVar29;
  uint uVar30;
  undefined8 *puVar31;
  bool bVar32;
  bool bVar33;
  byte bVar34;
  uint local_388;
  long local_370;
  uint local_368;
  char local_341;
  undefined1 *local_328;
  long local_320;
  long local_318;
  undefined4 local_310;
  undefined4 local_30c;
  undefined1 *local_308;
  char local_300;
  undefined1 *local_2f8;
  long local_2f0;
  long local_2e8;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined1 *local_2d8;
  char local_2d0;
  undefined **local_2c8;
  long *local_2c0;
  int *local_2b8;
  undefined **local_2a8;
  long *local_2a0;
  int *local_298;
  undefined4 local_290;
  void *local_288;
  void *local_280;
  undefined8 local_278;
  void *local_268;
  undefined8 local_260;
  undefined8 local_258;
  string *local_248;
  string *local_240;
  undefined8 local_238;
  void *local_228;
  undefined8 local_220;
  undefined8 local_218;
  void *local_208;
  void *local_200;
  undefined8 local_1f8;
  string *local_1e8;
  string *local_1e0;
  string *local_1d8;
  long local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  char *local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  wchar_t *local_128 [2];
  long local_118 [2];
  wchar_t *local_108 [2];
  char *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  wchar_t *local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [7];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  bVar34 = 0;
  local_2f8 = &DAT_01423a38;
                    /* try { // try from 008a86d5 to 008a86d9 has its CatchHandler @ 008a9e2a */
  std::string::string((string *)&local_2f0,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a86eb to 008a86ef has its CatchHandler @ 008a9e42 */
  std::wstring::wstring((wstring_conflict *)&local_2e8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_2e0 = 4;
  local_2dc = 3;
  local_2d8 = &DAT_01423a38;
  local_2d0 = '\0';
                    /* try { // try from 008a872d to 008a8731 has its CatchHandler @ 008a9e58 */
  std::operator+((wstring_conflict *)local_78,param_4);
                    /* try { // try from 008a8732 to 008a8754 has its CatchHandler @ 008a9ead */
  pCVar18 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar18,(wstring_conflict *)local_78,(CFileInfo *)&local_2f8,false,true,false);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_78[0] + -8);
    iVar16 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar16 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (local_2d0 == '\0') {
    if ((allocator *)(local_2d8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2d8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2d8 + -0x18));
      }
    }
    if ((allocator *)(local_2e8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar3 = (int *)(local_2e8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2e8 + -0x18));
      }
    }
    if ((allocator *)(local_2f0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2f0 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2f0 + -0x18));
      }
    }
    if ((allocator *)(local_2f8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2f8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2f8 + -0x18));
      }
    }
  }
  else {
                    /* try { // try from 008a8794 to 008a8798 has its CatchHandler @ 008aa0f6 */
    std::wstring::wstring((wstring_conflict *)local_88,L"ANIMATION",local_39);
                    /* try { // try from 008a87a4 to 008a87a8 has its CatchHandler @ 008a9e60 */
    this_01 = (CDataGroup *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008a87c4 to 008a87c8 has its CatchHandler @ 008a9e70 */
    CDataGroup::CDataGroup
              (this_01,(wstring_conflict *)local_88,(CDataGroup *)0x0,0x14,10,(TRepository *)0x0);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_88[0] + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 008a87f6 to 008a87fa has its CatchHandler @ 008a9e58 */
    std::operator+((wstring_conflict *)local_98,param_4);
                    /* try { // try from 008a8805 to 008a8809 has its CatchHandler @ 008a9eab */
    CDataGroup::LoadFile(this_01,(wstring_conflict *)local_98,(CTimerStatics *)0x0);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_98[0] + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    local_1e8 = (string *)0x0;
    local_1e0 = (string *)0x0;
    local_1d8 = (string *)0x0;
    plVar7 = *(long **)(param_1 + 0x2e8);
    local_208 = (void *)0x0;
    local_200 = (void *)0x0;
    local_1f8 = 0;
                    /* try { // try from 008a8895 to 008a8899 has its CatchHandler @ 008a9b3b */
    std::wstring::wstring((wstring_conflict *)local_a8,L"ANIMATION",&local_3a);
                    /* try { // try from 008a88aa to 008a88ae has its CatchHandler @ 008a9b4b */
    uVar15 = CDataGroup::GetDataGroupsMatchingName
                       (this_01,(wstring_conflict *)local_a8,(vector *)&local_208);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_a8[0] + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
                    /* try { // try from 008a88e1 to 008a88e5 has its CatchHandler @ 008a9b84 */
    FILESYSTEM::GetFileName((FILESYSTEM *)local_b8,(wstring_conflict *)(this + 0x110));
    local_341 = param_5;
    if (uVar15 != 0) {
      local_370 = 0;
      local_368 = 0;
      do {
        this_00 = *(CDataGroup **)((long)local_208 + local_370);
                    /* try { // try from 008a89ec to 008a89f0 has its CatchHandler @ 008a9b92 */
        std::wstring::wstring((wstring_conflict *)local_d8,L"FILE",&local_3b);
                    /* try { // try from 008a8a03 to 008a8a17 has its CatchHandler @ 008a9ba2 */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_d8,L"");
        std::wstring::wstring((wstring_conflict *)local_c8,pwVar19);
        if ((allocator *)(local_d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_d8[0] + -8);
          iVar16 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar16 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
          }
        }
        local_328 = &DAT_01423a38;
                    /* try { // try from 008a8a48 to 008a8a4c has its CatchHandler @ 008a9be0 */
        std::string::string((string *)&local_320,(string *)&::EMPTY_STRING);
                    /* try { // try from 008a8a5e to 008a8a62 has its CatchHandler @ 008a9c08 */
        std::wstring::wstring((wstring_conflict *)&local_318,(wstring_conflict *)&::EMPTY_WSTRING);
        local_310 = 4;
        local_30c = 3;
        local_308 = &DAT_01423a38;
        local_300 = '\0';
                    /* try { // try from 008a8aa5 to 008a8aa9 has its CatchHandler @ 008a9c1e */
        std::operator+((wstring_conflict *)local_e8,param_4);
                    /* try { // try from 008a8aaa to 008a8acc has its CatchHandler @ 008a9c2e */
        pCVar18 = (CFileSystem *)CFileSystem::getSingleton();
        CFileSystem::getFileInfo
                  (pCVar18,(wstring_conflict *)local_e8,(CFileInfo *)&local_328,false,true,false);
        if ((allocator *)(local_e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_e8[0] + -8);
          iVar16 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar16 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
          }
        }
        if (local_300 == '\0') {
          if ((allocator *)(local_308 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_308 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_308 + -0x18));
            }
          }
          if ((allocator *)(local_318 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_318 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_318 + -0x18));
            }
          }
          if ((allocator *)(local_320 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_320 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_320 + -0x18));
            }
          }
          if ((allocator *)(local_328 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_328 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_328 + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = local_c8[0] + -2;
            wVar5 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar5 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -6));
            }
          }
        }
        else {
                    /* try { // try from 008a8af5 to 008a8b28 has its CatchHandler @ 008a9c1e */
          plVar20 = (long *)Ogre::SkeletonManager::getSingleton();
          (**(code **)(*plVar20 + 0xe0))
                    ((SharedPtr<Ogre::Resource> *)&local_2c8,plVar20,(string *)&local_320,
                     &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
          local_290 = 0;
          local_2a8 = &PTR__SkeletonPtr_00fd17b0;
          local_2a0 = local_2c0;
          local_298 = local_2b8;
          if (local_2b8 != (int *)0x0) {
            *local_2b8 = *local_2b8 + 1;
          }
          local_2c8 = &PTR__SharedPtr_00fa45d0;
          if ((local_2b8 != (int *)0x0) &&
             (iVar16 = *local_2b8, *local_2b8 = iVar16 + -1, iVar16 + -1 == 0)) {
                    /* try { // try from 008a8b8f to 008a8bda has its CatchHandler @ 008a9f9e */
            Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_2c8);
          }
          local_388 = (uint)((ulong)(*(long *)(*(long *)(this + 0x1e0) + 0x30) -
                                    *(long *)(*(long *)(this + 0x1e0) + 0x28)) >> 3);
          (**(code **)(*local_2a0 + 0x220))(local_2a0,0);
          psVar21 = (string *)Ogre::Animation::getName();
          std::string::string((string *)local_f8,psVar21);
                    /* try { // try from 008a8c03 to 008a8c07 has its CatchHandler @ 008a9fb9 */
          std::wstring::wstring
                    ((wstring_conflict *)local_118,(wstring_conflict *)local_c8,0,
                     *(long *)(local_c8[0] + -6) - 9);
                    /* try { // try from 008a8c16 to 008a8c1a has its CatchHandler @ 008a9fc1 */
          STRINGS::StringUpper((STRINGS *)local_128,(wstring_conflict *)local_118);
                    /* try { // try from 008a8c3d to 008a8c41 has its CatchHandler @ 008a9fd9 */
          std::wstring::wstring
                    ((wstring_conflict *)local_108,(wstring_conflict *)local_b8,0,
                     *(long *)(local_b8[0] + -0x18) - 5);
          pwVar2 = local_108[0];
          pwVar8 = local_128[0];
          bVar33 = false;
          paVar1 = (allocator *)(local_108[0] + -6);
          if (*(size_t *)(local_108[0] + -6) == *(size_t *)(local_128[0] + -6)) {
            iVar16 = wmemcmp(local_108[0],local_128[0],*(size_t *)(local_108[0] + -6));
            bVar33 = iVar16 == 0;
          }
          if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = pwVar2 + -2;
            wVar5 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            pwVar8 = local_128[0];
            if (wVar5 < L'\x01') {
              std::wstring::_Rep::_M_destroy(paVar1);
              pwVar8 = local_128[0];
            }
          }
          if ((allocator *)(pwVar8 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
          {
            LOCK();
            pwVar2 = pwVar8 + -2;
            wVar5 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar5 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(pwVar8 + -6));
            }
          }
          if ((allocator *)(local_118[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_118[0] + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
            }
          }
          uVar30 = 0;
          uVar17 = 0;
          if (bVar33) {
                    /* try { // try from 008a8cd2 to 008a8d11 has its CatchHandler @ 008a9fb9 */
            for (; uVar14 = (**(code **)(*local_2a0 + 0x218))(), (int)uVar30 < (int)(uint)uVar14;
                uVar30 = uVar30 + 1) {
              (**(code **)(*local_2a0 + 0x220))(local_2a0,uVar30 & 0xffff);
              psVar21 = (string *)Ogre::Animation::getName();
              STRINGS::StringUpper((STRINGS *)local_138,psVar21);
                    /* try { // try from 008a8d1a to 008a8d1e has its CatchHandler @ 008aa0de */
              iVar16 = std::string::compare((char *)local_138);
              if ((allocator *)(local_138[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_138[0] + -8);
                iVar6 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                }
              }
              if (iVar16 == 0) {
                    /* try { // try from 008a8d4d to 008a8e39 has its CatchHandler @ 008a9fb9 */
                (**(code **)(*local_2a0 + 0x220))(local_2a0,uVar30 & 0xffff);
                Ogre::Animation::getName();
                std::string::assign((string *)local_f8);
                uVar17 = uVar30;
              }
            }
          }
          cVar13 = (**(code **)(**(long **)(this + 0x130) + 0x1e8))
                             (*(long **)(this + 0x130),local_f8);
          psVar21 = local_1e0;
          if (cVar13 == '\0') {
            bVar33 = false;
          }
          else if ((long)local_1e0 - (long)local_1e8 >> 3 == 0) {
            bVar33 = false;
          }
          else {
            uVar26 = 0;
            uVar30 = 0;
            bVar33 = false;
            psVar22 = local_1e8;
            do {
              lVar24 = *(long *)(*(char **)(psVar22 + uVar26 * 8) + -0x18);
              if (lVar24 == *(long *)(local_f8[0] + -0x18)) {
                bVar32 = true;
                pcVar28 = *(char **)(psVar22 + uVar26 * 8);
                pcVar29 = local_f8[0];
                do {
                  if (lVar24 == 0) break;
                  lVar24 = lVar24 + -1;
                  bVar32 = *pcVar28 == *pcVar29;
                  pcVar28 = pcVar28 + (ulong)bVar34 * -2 + 1;
                  pcVar29 = pcVar29 + (ulong)bVar34 * -2 + 1;
                } while (bVar32);
                if (bVar32) {
                  STRINGS::StringConvertToNarrow((STRINGS *)local_168,local_c8[0]);
                    /* try { // try from 008a8e4f to 008a8e53 has its CatchHandler @ 008aa05a */
                  std::operator+((char *)local_148,(string *)"Animation duplicate named: ");
                    /* try { // try from 008a8e5f to 008a8e63 has its CatchHandler @ 008aa086 */
                  std::string::string((string *)local_158,(string *)local_148);
                    /* try { // try from 008a8e71 to 008a8e75 has its CatchHandler @ 008aa098 */
                  std::string::append((char *)local_158,0xfd1146);
                    /* try { // try from 008a8e7c to 008a8e80 has its CatchHandler @ 008aa0a5 */
                  std::string::string((string *)local_198,(string *)local_158);
                    /* try { // try from 008a8e8c to 008a8e90 has its CatchHandler @ 008aa44e */
                  std::string::append((string *)local_198);
                  if ((allocator *)(local_158[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_158[0] + -8);
                    iVar16 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar16 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_148[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_148[0] + -8);
                    iVar16 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar16 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_168[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_168[0] + -8);
                    iVar16 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar16 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
                    }
                  }
                    /* try { // try from 008a8eed to 008a8ef1 has its CatchHandler @ 008aa40b */
                  std::string::string((string *)local_178,local_198[0],&local_3c);
                    /* try { // try from 008a8ef2 to 008a8f0d has its CatchHandler @ 008aa43c */
                  uVar23 = Ogre::LogManager::getSingleton();
                  Ogre::LogManager::logMessage(uVar23,local_178,3,0);
                  if ((allocator *)(local_178[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_178[0] + -8);
                    iVar16 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar16 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_198[0] + -0x18) !=
                      (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar3 = (int *)(local_198[0] + -8);
                    iVar16 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar16 < 1) {
                      std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
                      bVar33 = true;
                      psVar22 = local_1e8;
                      psVar21 = local_1e0;
                      goto LAB_008a8de8;
                    }
                  }
                  bVar33 = true;
                  psVar22 = local_1e8;
                  psVar21 = local_1e0;
                }
              }
LAB_008a8de8:
              uVar30 = uVar30 + 1;
              uVar26 = (ulong)uVar30;
            } while (uVar26 < (ulong)((long)psVar21 - (long)psVar22 >> 3));
          }
          if (local_1d8 == psVar21) {
                    /* try { // try from 008a9673 to 008a9677 has its CatchHandler @ 008a9fb9 */
            std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
                      ((vector<std::string,std::allocator<std::string>> *)&local_1e8,psVar21,
                       local_f8);
          }
          else {
            if (psVar21 == (string *)0x0) {
              local_1e0 = (string *)0x0;
            }
            else {
                    /* try { // try from 008a8f7e to 008a8f82 has its CatchHandler @ 008aa350 */
              std::string::string(psVar21,(string *)local_f8);
            }
            local_1e0 = local_1e0 + 8;
          }
                    /* try { // try from 008a8fad to 008a8fb1 has its CatchHandler @ 008a9fb9 */
          STRINGS::StringUpper((STRINGS *)local_188,(string *)local_f8);
                    /* try { // try from 008a8fba to 008a8fbe has its CatchHandler @ 008aa360 */
          iVar16 = std::string::compare((char *)local_188);
          if ((allocator *)(local_188[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_188[0] + -8);
            iVar6 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
            }
          }
          if (iVar16 == 0) {
            uVar30 = *(uint *)(*(long *)(this + 0x1e0) + 0x20);
            if (uVar30 != 0) {
              uVar27 = 0;
              lVar24 = 0;
              do {
                pcVar28 = *(char **)(*(long *)(*(long *)(this + 0x1e0) + 0x28) + lVar24);
                if (*(long *)(pcVar28 + -0x18) == *(long *)(local_f8[0] + -0x18)) {
                  bVar32 = true;
                  lVar25 = *(long *)(local_f8[0] + -0x18);
                  pcVar29 = local_f8[0];
                  do {
                    if (lVar25 == 0) break;
                    lVar25 = lVar25 + -1;
                    bVar32 = *pcVar28 == *pcVar29;
                    pcVar28 = pcVar28 + (ulong)bVar34 * -2 + 1;
                    pcVar29 = pcVar29 + (ulong)bVar34 * -2 + 1;
                  } while (bVar32);
                  if (bVar32) {
                    bVar32 = true;
                    local_388 = uVar27;
                    goto LAB_008a9048;
                  }
                }
                uVar27 = uVar27 + 1;
                lVar24 = lVar24 + 8;
              } while (uVar27 < uVar30);
            }
            bVar32 = true;
LAB_008a9048:
            if (!bVar33) {
              if ((local_341 != '\0') && (!bVar32)) {
                local_228 = (void *)0x0;
                local_220 = 0;
                local_218 = 0;
                    /* try { // try from 008a957e to 008a9583 has its CatchHandler @ 008aa2f0 */
                (**(code **)(*local_2a0 + 0x288))(local_2a0,local_2a0,&local_228);
                local_248 = (string *)0x0;
                local_240 = (string *)0x0;
                local_238 = 0;
                    /* try { // try from 008a95d2 to 008a95d3 has its CatchHandler @ 008aa31c */
                (**(code **)(*plVar7 + 0x280))(plVar7,local_2a0,&local_228,&local_248);
                psVar11 = local_240;
                psVar22 = local_240;
                for (psVar21 = local_248; psVar11 != psVar21; psVar21 = psVar21 + 8) {
                    /* try { // try from 008a95f3 to 008a95f7 has its CatchHandler @ 008aa329 */
                  std::string::~string(psVar21);
                  psVar22 = local_248;
                }
                if (psVar22 != (string *)0x0) {
                  operator_delete(psVar22);
                }
                if (local_228 != (void *)0x0) {
                  operator_delete(local_228);
                }
              }
LAB_008a9065:
                    /* try { // try from 008a9078 to 008a9095 has its CatchHandler @ 008a9fb9 */
              (**(code **)(*local_2a0 + 0x220))(local_2a0,uVar17 & 0xffff);
              psVar21 = (string *)Ogre::Animation::getName();
              std::string::string((string *)local_198,psVar21);
              lVar24 = *(long *)(this + 0x1e0);
              psVar21 = *(string **)(lVar24 + 0x30);
              if ((long)(int)local_388 == (long)psVar21 - *(long *)(lVar24 + 0x28) >> 3) {
                if (psVar21 == *(string **)(lVar24 + 0x38)) {
                  std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
                            ((vector<std::string,std::allocator<std::string>> *)(lVar24 + 0x28),
                             psVar21,local_198);
                }
                else {
                  if (psVar21 == (string *)0x0) {
                    lVar25 = 0;
                  }
                  else {
                    /* try { // try from 008a94ef to 008a94f3 has its CatchHandler @ 008a99c9 */
                    std::string::string(psVar21,(string *)local_198);
                    lVar25 = *(long *)(lVar24 + 0x30);
                  }
                  *(long *)(lVar24 + 0x30) = lVar25 + 8;
                }
                lVar24 = *(long *)(this + 0x1e0);
                pwVar19 = *(wstring_conflict **)(lVar24 + 0x48);
                if (pwVar19 == *(wstring_conflict **)(lVar24 + 0x50)) {
                    /* try { // try from 008a985c to 008a987c has its CatchHandler @ 008aa3ac */
                  std::vector<std::wstring,std::allocator<std::wstring>>::_M_insert_aux
                            ((vector<std::wstring,std::allocator<std::wstring>> *)(lVar24 + 0x40),
                             pwVar19,local_c8);
                }
                else {
                  if (pwVar19 == (wstring_conflict *)0x0) {
                    lVar25 = 0;
                  }
                  else {
                    /* try { // try from 008a952b to 008a952f has its CatchHandler @ 008aa127 */
                    std::wstring::wstring(pwVar19,(wstring_conflict *)local_c8);
                    lVar25 = *(long *)(lVar24 + 0x48);
                  }
                  *(long *)(lVar24 + 0x48) = lVar25 + 8;
                }
              }
                    /* try { // try from 008a90bf to 008a90c3 has its CatchHandler @ 008aa3ac */
              plVar20 = (long *)Ogre::SkeletonManager::getSingleton();
              pcVar9 = *(code **)(*plVar20 + 0x88);
                    /* try { // try from 008a90f1 to 008a90f5 has its CatchHandler @ 008aa3b1 */
              std::wstring::wstring((wstring_conflict *)local_1a8,local_c8[0],&local_3d);
                    /* try { // try from 008a9104 to 008a9108 has its CatchHandler @ 008aa3c2 */
              STRINGS::StringConvertToUTF8((wstring_conflict *)local_1b8);
                    /* try { // try from 008a910f to 008a9112 has its CatchHandler @ 008aa3d2 */
              (*pcVar9)(plVar20,(wstring_conflict *)local_1b8);
              if ((allocator *)(local_1b8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_1b8[0] + -8);
                iVar16 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar16 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
                }
              }
              if ((allocator *)(local_1a8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_1a8[0] + -8);
                iVar16 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar16 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
                }
              }
              lVar24 = *(long *)(this + 0x1e0);
              if ((ulong)((*(long *)(lVar24 + 0x60) - *(long *)(lVar24 + 0x58) >> 3) *
                         -0x5555555555555555) < (ulong)*(uint *)(lVar24 + 0x20)) {
                local_268 = (void *)0x0;
                local_260 = 0;
                local_258 = 0;
                puVar10 = *(undefined8 **)(lVar24 + 0x60);
                uVar26 = (ulong)*(uint *)(lVar24 + 0x20);
                lVar25 = (long)puVar10 - *(long *)(lVar24 + 0x58) >> 3;
                if (uVar26 < (ulong)(lVar25 * -0x5555555555555555)) {
                  puVar4 = (undefined8 *)(*(long *)(lVar24 + 0x58) + uVar26 * 0x18);
                  for (puVar31 = puVar4; puVar10 != puVar31; puVar31 = puVar31 + 3) {
                    if ((void *)*puVar31 != (void *)0x0) {
                      operator_delete((void *)*puVar31);
                    }
                  }
                  *(undefined8 **)(lVar24 + 0x60) = puVar4;
                }
                else {
                    /* try { // try from 008a9649 to 008a964d has its CatchHandler @ 008aa340 */
                  std::
                  vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
                  ::_M_fill_insert((vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
                                    *)(lVar24 + 0x58),puVar10,uVar26 + lVar25 * 0x5555555555555555);
                }
                if (local_268 != (void *)0x0) {
                  operator_delete(local_268);
                }
              }
              local_288 = (void *)0x0;
              local_280 = (void *)0x0;
              local_278 = 0;
                    /* try { // try from 008a9246 to 008a924a has its CatchHandler @ 008aa142 */
              std::wstring::wstring((wstring_conflict *)local_1c8,L"KEY",&local_3e);
                    /* try { // try from 008a925b to 008a925f has its CatchHandler @ 008aa160 */
              uVar17 = CDataGroup::GetDataGroupsMatchingName
                                 (this_00,(wstring_conflict *)local_1c8,(vector *)&local_288);
              if ((allocator *)(local_1c8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_1c8[0] + -8);
                iVar16 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar16 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
                }
              }
              lVar24 = 0;
              uVar30 = 0;
              if (uVar17 != 0) {
                do {
                    /* try { // try from 008a92a5 to 008a92a9 has its CatchHandler @ 008aa199 */
                  AddKey(this,local_388,*(CDataGroup **)((long)local_288 + lVar24));
                  uVar30 = uVar30 + 1;
                  lVar24 = lVar24 + 8;
                } while (uVar30 < uVar17);
              }
              local_280 = local_288;
              if ((local_341 != '\0') && (!bVar32)) {
                *(int *)(*(long *)(this + 0x1e0) + 0x20) =
                     *(int *)(*(long *)(this + 0x1e0) + 0x20) + 1;
              }
              if (local_288 != (void *)0x0) {
                operator_delete(local_288);
              }
              if ((allocator *)(local_198[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_198[0] + -8);
                iVar16 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar16 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
                }
              }
            }
          }
          else {
                    /* try { // try from 008a941a to 008a941f has its CatchHandler @ 008a9fb9 */
            cVar13 = (**(code **)(**(long **)(this + 0x130) + 0x1e8))
                               (*(long **)(this + 0x130),local_f8);
            bVar32 = false;
            if (cVar13 == '\0') goto LAB_008a9048;
            if (!bVar33) {
              uVar30 = *(uint *)(*(long *)(this + 0x1e0) + 0x20);
              if (uVar30 != 0) {
                uVar27 = 0;
                lVar24 = 0;
                do {
                  pcVar28 = *(char **)(*(long *)(*(long *)(this + 0x1e0) + 0x28) + lVar24);
                  if (*(long *)(pcVar28 + -0x18) == *(long *)(local_f8[0] + -0x18)) {
                    bVar33 = true;
                    lVar25 = *(long *)(local_f8[0] + -0x18);
                    pcVar29 = local_f8[0];
                    do {
                      if (lVar25 == 0) break;
                      lVar25 = lVar25 + -1;
                      bVar33 = *pcVar28 == *pcVar29;
                      pcVar28 = pcVar28 + (ulong)bVar34 * -2 + 1;
                      pcVar29 = pcVar29 + (ulong)bVar34 * -2 + 1;
                    } while (bVar33);
                    if (bVar33) {
                      bVar32 = false;
                      local_341 = '\0';
                      local_388 = uVar27;
                      goto LAB_008a9065;
                    }
                  }
                  uVar27 = uVar27 + 1;
                  lVar24 = lVar24 + 8;
                } while (uVar27 < uVar30);
              }
              bVar32 = false;
              local_341 = '\0';
              goto LAB_008a9065;
            }
          }
          if ((allocator *)(local_f8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_f8[0] + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
            }
          }
          local_2a8 = &PTR__SharedPtr_00fd1870;
          if ((local_298 != (int *)0x0) &&
             (iVar16 = *local_298, *local_298 = iVar16 + -1, iVar16 + -1 == 0)) {
                    /* try { // try from 008a9355 to 008a9357 has its CatchHandler @ 008a9c1e */
            (*(code *)PTR_destroy_00fd1880)(&local_2a8);
          }
          if ((allocator *)(local_308 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_308 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_308 + -0x18));
            }
          }
          if ((allocator *)(local_318 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_318 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_318 + -0x18));
            }
          }
          if ((allocator *)(local_320 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_320 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_320 + -0x18));
            }
          }
          if ((allocator *)(local_328 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_328 + -8);
            iVar16 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar16 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_328 + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = local_c8[0] + -2;
            wVar5 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar5 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -6));
            }
          }
        }
        local_368 = local_368 + 1;
        local_370 = local_370 + 8;
      } while (local_368 < uVar15);
    }
    local_200 = local_208;
    if (local_341 != '\0') {
      pcVar9 = *(code **)(*plVar7 + 0x208);
                    /* try { // try from 008a97a8 to 008a97b6 has its CatchHandler @ 008a9ef4 */
      uVar23 = Ogre::Entity::getAllAnimationStates();
      (*pcVar9)(plVar7,uVar23);
    }
    if (this_01 != (CDataGroup *)0x0) {
                    /* try { // try from 008a96ab to 008a96ad has its CatchHandler @ 008a9ef4 */
      (**(code **)(*(long *)this_01 + 8))(this_01);
    }
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_b8[0] + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    psVar21 = local_1e8;
    psVar22 = local_1e0;
    psVar11 = local_1e0;
    if (local_208 != (void *)0x0) {
      operator_delete(local_208);
      psVar21 = local_1e8;
      psVar22 = local_1e0;
      psVar11 = local_1e0;
    }
    for (; psVar12 = local_1e0, local_1e0 != psVar21; psVar21 = psVar21 + 8) {
      local_1e0 = psVar11;
                    /* try { // try from 008a96f3 to 008a96f7 has its CatchHandler @ 008a9cfe */
      std::string::~string(psVar21);
      psVar22 = local_1e8;
      psVar11 = local_1e0;
      local_1e0 = psVar12;
    }
    local_1e0 = psVar11;
    if (psVar22 != (string *)0x0) {
      operator_delete(psVar22);
    }
    if ((allocator *)(local_2d8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2d8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2d8 + -0x18));
      }
    }
    if ((allocator *)(local_2e8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar3 = (int *)(local_2e8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2e8 + -0x18));
      }
    }
    if ((allocator *)(local_2f0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2f0 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2f0 + -0x18));
      }
    }
    if ((allocator *)(local_2f8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_2f8 + -8);
      iVar16 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2f8 + -0x18));
      }
    }
  }
  return;
}



/* address=008aa4b0
   symbol=CGenericModel::updateAnimation */

/* CGenericModel::updateAnimation(float, bool) */

void __thiscall CGenericModel::updateAnimation(CGenericModel *this,float param_1,bool param_2)

{
  vector<CKeyframe*,std::allocator<CKeyframe*>> *pvVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  long lVar8;
  ulong uVar9;
  float *pfVar10;
  uint *puVar11;
  undefined8 uVar12;
  long lVar13;
  ulong uVar14;
  long lVar15;
  long lVar16;
  undefined8 *puVar17;
  long *plVar18;
  long *plVar19;
  ulong uVar20;
  long *plVar21;
  long *plVar22;
  long *plVar23;
  uint uVar24;
  uint uVar25;
  long lVar26;
  ulong uVar27;
  void *pvVar28;
  int iVar29;
  long lVar30;
  long lVar31;
  ulong uVar32;
  ulong uVar33;
  bool bVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  int local_108;
  uint local_fc;
  float local_f0;
  float local_ec;
  float local_cc;
  bool local_a9;
  void *local_98;
  uint *local_90;
  uint *local_88;
  void *local_78;
  float *local_70;
  float *local_68;
  long local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  uint local_40;
  float local_3c [3];

  if (*(long *)(this + 0x60) == 0) {
    return;
  }
  cVar7 = (**(code **)(*(long *)this + 0x48))();
  if ((cVar7 != '\0') || (param_1 == DAT_00fa871c)) {
    local_f0 = param_1;
    if (this[0x1e8] != (CGenericModel)0x0) {
      local_f0 = 0.0;
    }
    lVar13 = *(long *)(this + 0x180);
    lVar30 = *(long *)(this + 400);
    plVar18 = *(long **)(this + 0x170);
    lVar26 = *(long *)(this + 0x198);
    lVar31 = *(long *)(this + 0x188);
    puVar17 = *(undefined8 **)(this + 0x1a8);
    lVar8 = ((long)puVar17 - lVar31 >> 3) * 0x40 + -0x40 +
            (lVar13 - (long)plVar18 >> 3) + (lVar30 - lVar26 >> 3);
    if (lVar8 != 0) {
      if (*(char *)(*(long *)(this + 0x68) + 0x40) == '\0') {
        local_a9 = param_2;
        if ((!param_2) && (lVar8 == 1)) {
          plVar18 = (long *)std::
                            _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                            ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                          *)(this + 0x170),0);
          if (*(char *)(*plVar18 + 0x28) != '\0') goto LAB_008aa4f1;
          plVar18 = *(long **)(this + 0x170);
          lVar13 = *(long *)(this + 0x180);
          lVar26 = *(long *)(this + 0x198);
          lVar30 = *(long *)(this + 400);
          lVar31 = *(long *)(this + 0x188);
          puVar17 = *(undefined8 **)(this + 0x1a8);
        }
      }
      else {
        local_a9 = true;
      }
      *(undefined8 *)(this + 0x1b8) = *(undefined8 *)(this + 0x1b0);
      local_78 = (void *)0x0;
      local_70 = (float *)0x0;
      local_68 = (float *)0x0;
      local_98 = (void *)0x0;
      local_90 = (uint *)0x0;
      local_88 = (uint *)0x0;
      iVar29 = (int)(lVar30 - lVar26 >> 3) + (int)(lVar13 - (long)plVar18 >> 3) + -0x40 +
               (int)(((long)puVar17 - lVar31 >> 3) << 6);
      if (iVar29 < 1) {
        bVar6 = false;
      }
      else {
        pvVar1 = (vector<CKeyframe*,std::allocator<CKeyframe*>> *)(this + 0x1b0);
        iVar2 = 0;
        bVar6 = false;
        bVar4 = false;
        bVar5 = false;
        local_ec = 0.0;
        do {
          lVar30 = (long)iVar2;
          lVar8 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
          uVar20 = lVar30 + lVar8;
          uVar9 = (long)uVar20 >> 6;
          if ((long)uVar20 < 0) {
LAB_008ab1a8:
            uVar32 = ~(~uVar20 >> 6);
            local_fc = *(uint *)(*(long *)(*(long *)(lVar31 + uVar32 * 8) +
                                          (uVar20 + uVar32 * -0x40) * 8) + 0x10);
            if ((-1 < (long)uVar20) && (uVar32 = uVar9, (long)uVar20 < 0x40)) goto LAB_008aa69c;
LAB_008aafac:
            plVar21 = (long *)((uVar20 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
          }
          else {
            if (0x3f < (long)uVar20) {
              if ((long)uVar20 < 1) goto LAB_008ab1a8;
              local_fc = *(uint *)(*(long *)(*(long *)(lVar31 + uVar9 * 8) +
                                            (ulong)((uint)uVar20 & 0x3f) * 8) + 0x10);
              uVar32 = uVar9;
              goto LAB_008aafac;
            }
            local_fc = *(uint *)(plVar18[lVar30] + 0x10);
LAB_008aa69c:
            plVar21 = plVar18 + lVar30;
          }
          if ((*(char *)(*plVar21 + 0x26) == '\0') || (local_f0 == 0.0)) {
LAB_008aae10:
            bVar3 = false;
            bVar34 = false;
            if (iVar2 != 0) goto LAB_008aa850;
LAB_008aae20:
            if (!bVar3) goto LAB_008aa870;
LAB_008aae28:
            if ((local_f0 == 0.0) && (!NAN(local_f0))) goto LAB_008aa870;
          }
          else {
            if (iVar2 < iVar29 + -1) {
              uVar9 = (iVar2 + 1) + lVar8;
              if ((long)uVar9 < 0) {
LAB_008abea1:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aaded:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + (iVar2 + 1);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abea1;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aaded;
                }
              }
              if (*(char *)(*plVar21 + 0x26) != '\0') goto LAB_008aae10;
            }
            if (iVar2 == iVar29 + -1) {
LAB_008aa729:
              uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
LAB_008aa738:
              if ((long)uVar9 < 0) {
LAB_008ac0a9:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa760:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0a9;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa760;
                }
              }
              lVar8 = *plVar18;
              *(undefined1 *)(lVar8 + 0x25) = 1;
              *(undefined1 *)(lVar8 + 0x26) = 0;
              *(undefined4 *)(lVar8 + 0x34) = 0;
              if (local_fc < *(uint *)(this + 0x154)) {
                puVar17 = (undefined8 *)((ulong)local_fc * 8 + *(long *)(this + 0x148));
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x148);
              }
                    /* try { // try from 008aa7a6 to 008ac07c has its CatchHandler @ 008ac15d */
              Ogre::AnimationState::setEnabled(SUB81(*puVar17,0));
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ac0bb:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa7f1:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0bb;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa7f1;
                }
              }
              Ogre::AnimationState::setTimePosition(*(float *)(*plVar18 + 0x20));
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
              bVar34 = false;
            }
            else {
              lVar26 = (long)(iVar2 + 1);
              uVar9 = lVar8 + lVar26;
              if ((long)uVar9 < 0) {
LAB_008ac082:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aa706:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + lVar26;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac082;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aa706;
                }
              }
              if (*(char *)(*plVar21 + 0x25) == '\0') goto LAB_008aa729;
              plVar18 = (long *)std::
                                _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                              *)(this + 0x170),lVar26);
              lVar8 = *plVar18;
              fVar37 = 0.0;
              if (*(char *)(lVar8 + 0x27) == '\0') {
                fVar37 = *(float *)(lVar8 + 0x18) - *(float *)(lVar8 + 0x20);
              }
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
              lVar8 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
              uVar9 = lVar26 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008ac0df:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abf43:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar21 = plVar18 + lVar26;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0df;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abf43;
                }
              }
              uVar9 = lVar30 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008ac0cd:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abf8d:
                plVar19 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar19 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ac0cd;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abf8d;
                }
              }
              bVar34 = true;
              if (fVar37 / *(float *)(*plVar21 + 0x38) - local_f0 <= *(float *)(*plVar19 + 0x30))
              goto LAB_008aa738;
            }
            bVar3 = bVar34;
            if (iVar2 == 0) goto LAB_008aae20;
LAB_008aa850:
            if (bVar34) goto LAB_008aae28;
            if (local_f0 != 0.0) {
              uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008abe8f:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab408:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar30;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abe8f;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab408;
                }
              }
              *(undefined1 *)(*plVar18 + 0x2a) = 1;
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
            }
LAB_008aa870:
            uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
            uVar20 = (long)uVar9 >> 6;
            if ((long)uVar9 < 0) {
LAB_008ab390:
              uVar32 = ~(~uVar9 >> 6);
              lVar8 = *(long *)(*(long *)(lVar31 + uVar32 * 8) + (uVar9 + uVar32 * -0x40) * 8);
              fVar37 = *(float *)(lVar8 + 0x20);
              if (-1 < (long)uVar9) {
                if (0x3f < (long)uVar9) goto LAB_008ab0d9;
                lVar8 = plVar18[lVar30];
                goto LAB_008aa8a7;
              }
              cVar7 = *(char *)(lVar8 + 0x25);
LAB_008ab0f2:
              plVar18 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
            }
            else {
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab390;
                fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                             (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
LAB_008ab0d9:
                cVar7 = *(char *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                           (ulong)((uint)uVar9 & 0x3f) * 8) + 0x25);
                uVar32 = uVar20;
                goto LAB_008ab0f2;
              }
              lVar8 = plVar18[lVar30];
              fVar37 = *(float *)(lVar8 + 0x20);
LAB_008aa8a7:
              cVar7 = *(char *)(lVar8 + 0x25);
              plVar18 = plVar18 + lVar30;
            }
            lVar8 = *plVar18;
            *(undefined1 *)(lVar8 + 0x27) = 0;
            if (*(char *)(lVar8 + 0x25) == '\0') {
              local_cc = DAT_00fa47fc;
            }
            else {
              if (0.0 < *(float *)(lVar8 + 0x2c)) {
                fVar36 = *(float *)(lVar8 + 0x2c) - local_f0;
                *(float *)(lVar8 + 0x2c) = fVar36;
                local_cc = 1.0;
                *(undefined4 *)(lVar8 + 0x34) = 0x3f800000;
                if ((*(float *)(lVar8 + 0x30) != 0.0) && (0.0 < fVar36)) {
                  fVar35 = fVar36 / *(float *)(lVar8 + 0x30);
                  uVar24 = -(uint)(fVar35 <= DAT_00fa47fc);
                  *(uint *)(lVar8 + 0x34) = ~uVar24 & (uint)DAT_00fa47fc | (uint)fVar35 & uVar24;
                }
                if (fVar36 <= 0.0) {
                  *(undefined1 *)(lVar8 + 0x29) = 1;
                  *(undefined4 *)(lVar8 + 0x34) = 0;
                  *(undefined4 *)(lVar8 + 0x2c) = 0;
                }
              }
              else {
                local_cc = DAT_00fa47fc;
              }
              fVar36 = *(float *)(lVar8 + 0x18);
              fVar35 = local_f0 * *(float *)(lVar8 + 0x38) + *(float *)(lVar8 + 0x20);
              *(float *)(lVar8 + 0x20) = fVar35;
              if (fVar36 == 0.0) {
                if (*(char *)(lVar8 + 0x24) == '\0') {
                  *(undefined4 *)(lVar8 + 0x20) = 0;
                  *(undefined1 *)(lVar8 + 0x25) = 0;
                  *(undefined1 *)(lVar8 + 0x28) = 1;
                  *(undefined1 *)(lVar8 + 0x29) = 1;
                }
                else {
                  *(undefined1 *)(lVar8 + 0x27) = 1;
                  *(undefined4 *)(lVar8 + 0x20) = 0;
                }
              }
              else if (fVar36 < fVar35) {
                *(float *)(lVar8 + 0x20) = fVar35 - fVar36;
                if (*(char *)(lVar8 + 0x24) != '\0') {
                  do {
                    if (*(float *)(lVar8 + 0x20) <= fVar36) {
                      *(undefined1 *)(lVar8 + 0x27) = 1;
                      goto LAB_008aa8d3;
                    }
                    *(float *)(lVar8 + 0x20) = *(float *)(lVar8 + 0x20) - fVar36;
                  } while (*(char *)(lVar8 + 0x24) != '\0');
                  *(undefined1 *)(lVar8 + 0x27) = 1;
                }
                *(float *)(lVar8 + 0x20) = fVar36;
                *(undefined1 *)(lVar8 + 0x28) = 1;
                *(undefined1 *)(lVar8 + 0x29) = 1;
                *(undefined1 *)(lVar8 + 0x25) = 0;
              }
            }
LAB_008aa8d3:
            lVar8 = *(long *)(this + 0x170);
            lVar26 = *(long *)(this + 0x188);
            uVar9 = (lVar8 - *(long *)(this + 0x178) >> 3) + lVar30;
            uVar20 = (long)uVar9 >> 6;
            if ((long)uVar9 < 0) {
LAB_008ab330:
              uVar32 = ~(~uVar9 >> 6);
              fVar36 = *(float *)(*(long *)(*(long *)(lVar26 + uVar32 * 8) +
                                           (uVar9 + uVar32 * -0x40) * 8) + 0x20);
              if ((-1 < (long)uVar9) && (uVar32 = uVar20, (long)uVar9 < 0x40)) goto LAB_008aa918;
LAB_008ab090:
              plVar18 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar26 + uVar32 * 8));
            }
            else {
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab330;
                fVar36 = *(float *)(*(long *)(*(long *)(lVar26 + uVar20 * 8) +
                                             (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
                uVar32 = uVar20;
                goto LAB_008ab090;
              }
              fVar36 = *(float *)(*(long *)(lVar8 + lVar30 * 8) + 0x20);
LAB_008aa918:
              plVar18 = (long *)(lVar8 + lVar30 * 8);
            }
            local_3c[0] = local_cc - *(float *)(*plVar18 + 0x34);
            if (local_3c[0] != 0.0) {
              uVar9 = (lVar8 - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab4e2:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab148:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar26 + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(lVar8 + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab4e2;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab148;
                }
              }
              if ((((*(char *)(*plVar18 + 0x25) != '\0') || (cVar7 != '\0')) || (local_a9 != false))
                 || (fVar37 != fVar36)) {
                Ogre::AnimationState::setTimePosition(fVar36);
                bVar6 = true;
              }
            }
            local_3c[0] = local_3c[0] - local_ec;
            local_ec = local_ec + local_3c[0];
            if ((bVar4) || (local_3c[0] == 0.0)) {
              if (local_3c[0] != 0.0) goto LAB_008aae58;
LAB_008aaa20:
              bVar34 = NAN(local_3c[0]) || NAN(local_cc);
            }
            else {
              if ((local_a9 == false) && (fVar37 == fVar36)) {
LAB_008aae58:
                uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
                if ((long)uVar9 < 0) {
LAB_008ab4f4:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008aae9e:
                  plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                    *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
                }
                else {
                  plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008ab4f4;
                    uVar20 = (long)uVar9 >> 6;
                    goto LAB_008aae9e;
                  }
                }
                if ((*(char *)(*plVar18 + 0x25) == '\0') ||
                   ((local_a9 == false && (fVar37 == fVar36)))) goto LAB_008aaa20;
                Ogre::AnimationState::setWeight(local_3c[0]);
              }
              else {
                if (local_70 == local_68) {
                  std::vector<float,std::allocator<float>>::_M_insert_aux
                            ((vector<float,std::allocator<float>> *)&local_78,local_70,local_3c);
                }
                else {
                  pfVar10 = (float *)0x0;
                  if (local_70 != (float *)0x0) {
                    *local_70 = local_3c[0];
                    pfVar10 = local_70;
                  }
                  local_70 = pfVar10 + 1;
                }
                local_40 = local_fc;
                if (local_90 != local_88) {
                  puVar11 = (uint *)0x0;
                  if (local_90 != (uint *)0x0) {
                    *local_90 = local_fc;
                    puVar11 = local_90;
                  }
                  local_90 = puVar11 + 1;
                  goto LAB_008aaa20;
                }
                std::vector<int,std::allocator<int>>::_M_insert_aux
                          ((vector<int,std::allocator<int>> *)&local_98,local_90,&local_40);
              }
              bVar34 = NAN(local_3c[0]) || NAN(local_cc);
            }
            if ((local_3c[0] == local_cc) && (!bVar34)) {
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab4d0:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aaf4d:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab4d0;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aaf4d;
                }
              }
              if (*(char *)(*plVar18 + 0x2a) != '\0') {
                bVar4 = true;
              }
            }
            if ((((cVar7 != '\0') && (local_fc != 0xffffffff)) && (local_f0 != 0.0)) &&
               (lVar8 = *(long *)(this + 0x1e0), lVar8 != 0)) {
              plVar18 = (long *)(*(long *)(lVar8 + 0x58) + (ulong)local_fc * 0x18);
              lVar26 = *plVar18;
              if ((int)((ulong)(plVar18[1] - lVar26) >> 3) != 0) {
                uVar24 = 0;
                do {
                  fVar35 = *(float *)(*(long *)(lVar26 + (ulong)uVar24 * 8) + 0x10) / DAT_00fa4820;
                  if (fVar35 < fVar37) {
                    if ((fVar35 <= fVar36) && (fVar36 < fVar37)) {
                      uVar12 = getKeyFrame(this,local_fc,uVar24);
                      puVar17 = *(undefined8 **)(this + 0x1b8);
                      local_58 = uVar12;
                      if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                        std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                  (pvVar1,puVar17,&local_58);
                        goto LAB_008aab8e;
                      }
                      goto LAB_008aaada;
                    }
                  }
                  else if (fVar36 < fVar35) {
                    if (fVar36 < fVar37) {
                      uVar12 = getKeyFrame(this,local_fc,uVar24);
                      puVar17 = *(undefined8 **)(this + 0x1b8);
                      local_50 = uVar12;
                      if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                        std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                  (pvVar1,puVar17,&local_50);
                        goto LAB_008aab8e;
                      }
                      goto LAB_008aaada;
                    }
                  }
                  else {
                    uVar12 = getKeyFrame(this,local_fc,uVar24);
                    puVar17 = *(undefined8 **)(this + 0x1b8);
                    local_48 = uVar12;
                    if (puVar17 == *(undefined8 **)(this + 0x1c0)) {
                      std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                (pvVar1,puVar17,&local_48);
LAB_008aab8e:
                      lVar8 = *(long *)(this + 0x1e0);
                    }
                    else {
LAB_008aaada:
                      lVar26 = 0;
                      if (puVar17 != (undefined8 *)0x0) {
                        *puVar17 = uVar12;
                        lVar26 = *(long *)(this + 0x1b8);
                        lVar8 = *(long *)(this + 0x1e0);
                      }
                      *(long *)(this + 0x1b8) = lVar26 + 8;
                    }
                  }
                  if (lVar8 == 0) break;
                  uVar24 = uVar24 + 1;
                  plVar18 = (long *)(*(long *)(lVar8 + 0x58) + (ulong)local_fc * 0x18);
                  lVar26 = *plVar18;
                } while (uVar24 < (uint)(plVar18[1] - lVar26 >> 3));
              }
            }
            if ((bVar5) && (local_f0 != 0.0)) {
              uVar9 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar30;
              if ((long)uVar9 < 0) {
LAB_008ab506:
                uVar20 = ~(~uVar9 >> 6);
LAB_008ab2f6:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                  *(long *)(*(long *)(this + 0x188) + uVar20 * 8));
              }
              else {
                plVar18 = (long *)(*(long *)(this + 0x170) + lVar30 * 8);
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008ab506;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008ab2f6;
                }
              }
              *(undefined1 *)(*plVar18 + 0x28) = 1;
            }
            plVar18 = *(long **)(this + 0x170);
            lVar31 = *(long *)(this + 0x188);
            uVar9 = ((long)plVar18 - *(long *)(this + 0x178) >> 3) + lVar30;
            if ((long)uVar9 < 0) {
LAB_008ab378:
              uVar20 = ~(~uVar9 >> 6);
LAB_008aac05:
              plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
            }
            else {
              plVar21 = plVar18 + lVar30;
              if (0x3f < (long)uVar9) {
                if ((long)uVar9 < 1) goto LAB_008ab378;
                uVar20 = (long)uVar9 >> 6;
                goto LAB_008aac05;
              }
            }
            if (*(char *)(*plVar21 + 0x29) != '\0') {
              if (local_f0 != 0.0) {
                bVar5 = true;
              }
              if (NAN(local_f0)) {
                bVar5 = true;
              }
            }
          }
          iVar2 = iVar2 + 1;
          lVar13 = *(long *)(this + 0x180);
          lVar30 = *(long *)(this + 400);
          lVar26 = *(long *)(this + 0x198);
          puVar17 = *(undefined8 **)(this + 0x1a8);
          iVar29 = (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3) + -0x40 +
                   (int)(((long)puVar17 - lVar31 >> 3) << 6);
        } while (iVar2 < iVar29);
        fVar37 = DAT_00fa4824;
        if (DAT_00fa47fc <= local_ec) {
          lVar8 = (long)local_90 - (long)local_98 >> 2;
        }
        else {
          lVar8 = (long)local_90 - (long)local_98 >> 2;
          if ((local_ec != 0.0) || (NAN(local_ec))) {
            fVar37 = DAT_00fa47fc - local_ec;
          }
        }
        if (lVar8 != 0) {
          uVar9 = 0;
          uVar24 = 0;
          do {
            Ogre::AnimationState::setWeight(*(float *)((long)local_78 + uVar9 * 4) * fVar37);
            uVar24 = uVar24 + 1;
            uVar9 = (ulong)uVar24;
          } while (uVar9 < (ulong)((long)local_90 - (long)local_98 >> 2));
          plVar18 = *(long **)(this + 0x170);
          lVar13 = *(long *)(this + 0x180);
          lVar26 = *(long *)(this + 0x198);
          lVar30 = *(long *)(this + 400);
          lVar31 = *(long *)(this + 0x188);
          puVar17 = *(undefined8 **)(this + 0x1a8);
        }
      }
      if ((local_f0 != DAT_00fa47f8) || (NAN(local_f0) || NAN(DAT_00fa47f8))) {
        iVar29 = (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3) + -0x40 +
                 (int)(((long)puVar17 - lVar31 >> 3) << 6);
        if (1 < iVar29) {
          local_108 = 1;
          do {
            lVar8 = *(long *)(this + 0x178);
            lVar30 = (long)local_108;
            uVar32 = (long)plVar18 - lVar8 >> 3;
            uVar20 = uVar32 + lVar30;
            uVar9 = (long)uVar20 >> 6;
            if ((long)uVar20 < 0) {
LAB_008abc60:
              uVar14 = ~(~uVar20 >> 6);
LAB_008ab620:
              plVar21 = (long *)((uVar20 + uVar14 * -0x40) * 8 + *(long *)(lVar31 + uVar14 * 8));
            }
            else {
              plVar21 = plVar18 + lVar30;
              if (0x3f < (long)uVar20) {
                uVar14 = uVar9;
                if ((long)uVar20 < 1) goto LAB_008abc60;
                goto LAB_008ab620;
              }
            }
            if (*(char *)(*plVar21 + 0x28) == '\0') {
              lVar8 = *(long *)(this + 400);
              pvVar28 = *(void **)(this + 0x198);
            }
            else {
              plVar21 = plVar18 + lVar30;
              uVar33 = ~(~uVar20 >> 6);
              uVar14 = uVar32;
              plVar19 = plVar18;
              do {
                if (((long)uVar14 < 0) || (plVar23 = plVar19, 0x3f < (long)uVar14)) {
                  if ((long)uVar14 < 1) {
                    uVar27 = ~(~uVar14 >> 6);
                  }
                  else {
                    uVar27 = (long)uVar14 >> 6;
                  }
                  plVar23 = (long *)((uVar14 + uVar27 * -0x40) * 8 + *(long *)(lVar31 + uVar27 * 8))
                  ;
                }
                if ((long)uVar20 < 0) {
LAB_008ab710:
                  uVar27 = uVar33;
LAB_008ab699:
                  plVar22 = (long *)((uVar20 + uVar27 * -0x40) * 8 + *(long *)(lVar31 + uVar27 * 8))
                  ;
                }
                else {
                  plVar22 = plVar21;
                  if (0x3f < (long)uVar20) {
                    uVar27 = uVar9;
                    if ((long)uVar20 < 1) goto LAB_008ab710;
                    goto LAB_008ab699;
                  }
                }
                if (*(int *)(*plVar23 + 0x10) == *(int *)(*plVar22 + 0x10)) goto LAB_008ab790;
                uVar14 = uVar14 + 1;
                plVar19 = plVar19 + 1;
              } while ((int)uVar14 - (int)uVar32 < local_108);
              if ((long)uVar20 < 0) {
LAB_008ab742:
                plVar21 = (long *)((uVar20 + uVar33 * -0x40) * 8 + *(long *)(lVar31 + uVar33 * 8));
              }
              else if (0x3f < (long)uVar20) {
                if (0 < (long)uVar20) {
                  uVar33 = uVar9;
                }
                goto LAB_008ab742;
              }
              if (*(uint *)(*plVar21 + 0x10) < *(uint *)(this + 0x154)) {
                puVar17 = (undefined8 *)
                          ((ulong)*(uint *)(*plVar21 + 0x10) * 8 + *(long *)(this + 0x148));
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x148);
              }
              Ogre::AnimationState::setEnabled(SUB81(*puVar17,0));
              lVar8 = *(long *)(this + 0x178);
              plVar18 = *(long **)(this + 0x170);
              lVar31 = *(long *)(this + 0x188);
LAB_008ab790:
              lVar26 = (long)plVar18 - lVar8 >> 3;
              uVar9 = lVar26 + lVar30;
              uVar20 = (long)uVar9 >> 6;
              if ((long)uVar9 < 0) {
LAB_008abd38:
                uVar32 = ~(~uVar9 >> 6);
                fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar32 * 8) +
                                             (uVar9 + uVar32 * -0x40) * 8) + 0x20);
                if ((-1 < (long)uVar9) && (uVar32 = uVar20, (long)uVar9 < 0x40)) goto LAB_008ab7bf;
LAB_008abbe2:
                plVar21 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd38;
                  fVar37 = *(float *)(*(long *)(*(long *)(lVar31 + uVar20 * 8) +
                                               (ulong)((uint)uVar9 & 0x3f) * 8) + 0x20);
                  uVar32 = uVar20;
                  goto LAB_008abbe2;
                }
                fVar37 = *(float *)(plVar18[lVar30] + 0x20);
LAB_008ab7bf:
                plVar21 = plVar18 + lVar30;
              }
              if (fVar37 < *(float *)(*plVar21 + 0x18)) {
                if ((long)uVar9 < 0) {
LAB_008abdce:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abcfa:
                  plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdce;
                    goto LAB_008abcfa;
                  }
                  plVar21 = plVar18 + lVar30;
                }
                uVar24 = *(uint *)(*plVar21 + 0x10);
                lVar13 = *(long *)(this + 0x1e0);
                if (lVar13 != 0) {
                  lVar15 = (ulong)uVar24 * 0x18;
                  plVar21 = (long *)(lVar15 + *(long *)(lVar13 + 0x58));
                  lVar16 = *plVar21;
                  if ((int)((ulong)(plVar21[1] - lVar16) >> 3) != 0) {
                    uVar25 = 0;
                    do {
                      uVar9 = ((long)plVar18 - lVar8 >> 3) + lVar30;
                      if ((long)uVar9 < 0) {
LAB_008abb00:
                        uVar20 = ~(~uVar9 >> 6);
LAB_008ab8b9:
                        plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 +
                                          *(long *)(lVar31 + uVar20 * 8));
                      }
                      else {
                        if (0x3f < (long)uVar9) {
                          if ((long)uVar9 < 1) goto LAB_008abb00;
                          uVar20 = (long)uVar9 >> 6;
                          goto LAB_008ab8b9;
                        }
                        plVar21 = plVar18 + lVar30;
                      }
                      fVar37 = *(float *)(*(long *)(lVar16 + (ulong)uVar25 * 8) + 0x10) /
                               DAT_00fa4820;
                      if (*(float *)(*plVar21 + 0x20) <= fVar37 &&
                          fVar37 != *(float *)(*plVar21 + 0x20)) {
                        lVar26 = getKeyFrame(this,uVar24,uVar25);
                        iVar29 = *(int *)(lVar26 + 0x58);
                        if ((((iVar29 == 0xd) || (iVar29 == 0xc)) || (iVar29 == 0x17)) ||
                           ((((iVar29 == 0x19 || (iVar29 == 0x11)) ||
                             ((iVar29 == 0x13 || ((iVar29 == 0x14 || (iVar29 == 8)))))) ||
                            (iVar29 == 10)))) {
                          plVar21 = *(long **)(this + 0x1b8);
                          local_60 = lVar26;
                          if (plVar21 == *(long **)(this + 0x1c0)) {
                            std::vector<CKeyframe*,std::allocator<CKeyframe*>>::_M_insert_aux
                                      ((vector<CKeyframe*,std::allocator<CKeyframe*>> *)
                                       (this + 0x1b0),plVar21,&local_60);
                            plVar18 = *(long **)(this + 0x170);
                            lVar31 = *(long *)(this + 0x188);
                            lVar8 = *(long *)(this + 0x178);
                            lVar13 = *(long *)(this + 0x1e0);
                          }
                          else {
                            lVar16 = 0;
                            if (plVar21 != (long *)0x0) {
                              *plVar21 = lVar26;
                              lVar16 = *(long *)(this + 0x1b8);
                              plVar18 = *(long **)(this + 0x170);
                              lVar31 = *(long *)(this + 0x188);
                              lVar8 = *(long *)(this + 0x178);
                              lVar13 = *(long *)(this + 0x1e0);
                            }
                            *(long *)(this + 0x1b8) = lVar16 + 8;
                          }
                        }
                      }
                      if (lVar13 == 0) break;
                      plVar21 = (long *)(lVar15 + *(long *)(lVar13 + 0x58));
                      uVar25 = uVar25 + 1;
                      lVar16 = *plVar21;
                    } while (uVar25 < (uint)(plVar21[1] - lVar16 >> 3));
                    lVar26 = (long)plVar18 - lVar8 >> 3;
                    uVar9 = lVar30 + lVar26;
                  }
                }
              }
              uVar20 = (long)uVar9 >> 6;
              if ((long)uVar9 < 0) {
LAB_008abd80:
                uVar32 = ~(~uVar9 >> 6);
LAB_008abc40:
                plVar21 = (long *)((uVar9 + uVar32 * -0x40) * 8 + *(long *)(lVar31 + uVar32 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  uVar32 = uVar20;
                  if ((long)uVar9 < 1) goto LAB_008abd80;
                  goto LAB_008abc40;
                }
                plVar21 = plVar18 + lVar30;
              }
              if (*plVar21 != 0) {
                if ((long)uVar9 < 0) {
LAB_008abdaa:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abc88:
                  plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdaa;
                    goto LAB_008abc88;
                  }
                  plVar21 = plVar18 + lVar30;
                }
                if ((long *)*plVar21 != (long *)0x0) {
                  (**(code **)(*(long *)*plVar21 + 8))();
                  plVar18 = *(long **)(this + 0x170);
                  lVar31 = *(long *)(this + 0x188);
                  uVar9 = lVar30 + ((long)plVar18 - *(long *)(this + 0x178) >> 3);
                }
                if ((long)uVar9 < 0) {
LAB_008abdbc:
                  uVar20 = ~(~uVar9 >> 6);
LAB_008abcb8:
                  plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
                }
                else {
                  if (0x3f < (long)uVar9) {
                    if ((long)uVar9 < 1) goto LAB_008abdbc;
                    uVar20 = (long)uVar9 >> 6;
                    goto LAB_008abcb8;
                  }
                  plVar18 = plVar18 + lVar30;
                }
                *plVar18 = 0;
                plVar18 = *(long **)(this + 0x170);
                lVar31 = *(long *)(this + 0x188);
                lVar26 = (long)plVar18 - *(long *)(this + 0x178) >> 3;
                uVar9 = lVar30 + lVar26;
              }
              if ((long)uVar9 < 0) {
LAB_008abd20:
                uVar20 = ~(~uVar9 >> 6);
LAB_008abc10:
                plVar21 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd20;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008abc10;
                }
                plVar21 = plVar18 + lVar30;
              }
              lVar8 = (long)((int)(*(long *)(this + 0x180) - (long)plVar18 >> 3) +
                             (int)(*(long *)(this + 400) - *(long *)(this + 0x198) >> 3) + -0x41 +
                            (int)((*(long *)(this + 0x1a8) - lVar31 >> 3) << 6));
              uVar9 = lVar26 + lVar8;
              if ((long)uVar9 < 0) {
LAB_008abd98:
                uVar20 = ~(~uVar9 >> 6);
LAB_008aba8d:
                plVar18 = (long *)((uVar9 + uVar20 * -0x40) * 8 + *(long *)(lVar31 + uVar20 * 8));
              }
              else {
                plVar18 = plVar18 + lVar8;
                if (0x3f < (long)uVar9) {
                  if ((long)uVar9 < 1) goto LAB_008abd98;
                  uVar20 = (long)uVar9 >> 6;
                  goto LAB_008aba8d;
                }
              }
              *plVar21 = *plVar18;
              pvVar28 = *(void **)(this + 0x198);
              if (*(void **)(this + 400) == pvVar28) {
                operator_delete(pvVar28);
                puVar17 = (undefined8 *)(*(long *)(this + 0x1a8) + -8);
                *(undefined8 **)(this + 0x1a8) = puVar17;
                pvVar28 = (void *)*puVar17;
                lVar8 = (long)pvVar28 + 0x1f8;
                *(void **)(this + 0x198) = pvVar28;
                *(long *)(this + 0x1a0) = (long)pvVar28 + 0x200;
                *(long *)(this + 400) = lVar8;
              }
              else {
                puVar17 = *(undefined8 **)(this + 0x1a8);
                lVar8 = (long)*(void **)(this + 400) + -8;
                *(long *)(this + 400) = lVar8;
              }
              local_108 = local_108 + -1;
              bVar6 = true;
              plVar18 = *(long **)(this + 0x170);
              lVar13 = *(long *)(this + 0x180);
              lVar31 = *(long *)(this + 0x188);
            }
            local_108 = local_108 + 1;
            iVar29 = (int)(lVar8 - (long)pvVar28 >> 3) + (int)(lVar13 - (long)plVar18 >> 3) + -0x40
                     + (int)(((long)puVar17 - lVar31 >> 3) << 6);
          } while (local_108 < iVar29);
        }
      }
      else {
        iVar29 = (int)(((long)puVar17 - lVar31 >> 3) << 6) + -0x40 +
                 (int)(lVar13 - (long)plVar18 >> 3) + (int)(lVar30 - lVar26 >> 3);
      }
      if (((bVar6) || (local_a9 != false)) ||
         ((0 < iVar29 &&
          ((iVar29 != 1 ||
           (plVar18 = (long *)std::
                              _Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                              ::operator[]((_Deque_iterator<CActiveAnimation*,CActiveAnimation*&,CActiveAnimation**>
                                            *)(this + 0x170),0), *(char *)(*plVar18 + 0x28) == '\0')
           ))))) {
        Ogre::Entity::_updateAnimation();
      }
      if (local_98 != (void *)0x0) {
        operator_delete(local_98);
      }
      if (local_78 == (void *)0x0) {
        return;
      }
      operator_delete(local_78);
      return;
    }
  }
LAB_008aa4f1:
  *(undefined8 *)(this + 0x1b8) = *(undefined8 *)(this + 0x1b0);
  return;
}



/* address=008ac190
   symbol=CGenericModel::reInitialize */

/* WARNING: Removing unreachable block (ram,0x008ae9bd) */
/* WARNING: Removing unreachable block (ram,0x008aeaa1) */
/* WARNING: Removing unreachable block (ram,0x008ae48d) */
/* WARNING: Removing unreachable block (ram,0x008aec05) */
/* WARNING: Removing unreachable block (ram,0x008ae8bd) */
/* WARNING: Removing unreachable block (ram,0x008ae816) */
/* WARNING: Removing unreachable block (ram,0x008ae72e) */
/* WARNING: Removing unreachable block (ram,0x008aecb5) */
/* WARNING: Removing unreachable block (ram,0x008aea7e) */
/* WARNING: Removing unreachable block (ram,0x008ae84f) */
/* WARNING: Removing unreachable block (ram,0x008ae778) */
/* WARNING: Removing unreachable block (ram,0x008ae5ec) */
/* WARNING: Removing unreachable block (ram,0x008aeb37) */
/* WARNING: Removing unreachable block (ram,0x008aebde) */
/* WARNING: Removing unreachable block (ram,0x008ae995) */
/* WARNING: Removing unreachable block (ram,0x008aec1a) */
/* WARNING: Removing unreachable block (ram,0x008ae8b2) */
/* WARNING: Removing unreachable block (ram,0x008aea39) */
/* WARNING: Removing unreachable block (ram,0x008ae73c) */
/* WARNING: Removing unreachable block (ram,0x008ae5bf) */
/* WARNING: Removing unreachable block (ram,0x008ae9a5) */
/* WARNING: Removing unreachable block (ram,0x008ae8f9) */
/* WARNING: Removing unreachable block (ram,0x008aea70) */
/* WARNING: Removing unreachable block (ram,0x008ae9c8) */
/* WARNING: Removing unreachable block (ram,0x008aeb6e) */
/* WARNING: Removing unreachable block (ram,0x008aec6e) */
/* WARNING: Removing unreachable block (ram,0x008ae498) */
/* WARNING: Removing unreachable block (ram,0x008aeb7c) */
/* WARNING: Removing unreachable block (ram,0x008aeae0) */
/* WARNING: Removing unreachable block (ram,0x008aeafb) */
/* WARNING: Removing unreachable block (ram,0x008aeb15) */
/* WARNING: Removing unreachable block (ram,0x008aea8e) */
/* WARNING: Removing unreachable block (ram,0x008ae582) */
/* WARNING: Removing unreachable block (ram,0x008ae58d) */
/* WARNING: Removing unreachable block (ram,0x008ae62b) */
/* WARNING: Removing unreachable block (ram,0x008ae6f7) */
/* WARNING: Removing unreachable block (ram,0x008aea2e) */
/* CGenericModel::reInitialize(Ogre::Entity*, bool) */

void __thiscall CGenericModel::reInitialize(CGenericModel *this,Entity *param_1,bool param_2)

{
  int *piVar1;
  undefined **ppuVar2;
  code *pcVar3;
  char cVar4;
  undefined1 uVar5;
  bool bVar6;
  char cVar7;
  ushort uVar8;
  undefined2 uVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  undefined8 uVar14;
  void *pvVar15;
  ulong uVar16;
  long *plVar17;
  string *psVar18;
  long lVar19;
  string *psVar20;
  ColourValue *pCVar21;
  CFileSystem *pCVar22;
  ulong uVar23;
  ulong uVar24;
  long lVar25;
  long lVar26;
  long lVar27;
  ushort uVar28;
  allocator *paVar29;
  long lVar30;
  long lVar31;
  long lVar32;
  int iVar33;
  undefined8 *puVar34;
  uint uVar35;
  uint local_494;
  int local_490;
  undefined1 *local_428;
  long local_420;
  long local_418;
  undefined4 local_410;
  undefined4 local_40c;
  undefined1 *local_408;
  undefined1 local_400;
  undefined **local_3f8;
  long local_3f0;
  int *local_3e8;
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined1 *local_3d8;
  undefined1 local_3d0;
  undefined **local_3c8;
  long local_3c0;
  int *local_3b8;
  undefined **local_3a8;
  undefined8 local_3a0;
  int *local_398;
  undefined **local_388;
  undefined8 local_380;
  int *local_378;
  SharedPtr<Ogre::GpuProgramParameters> local_368 [8];
  undefined8 local_360;
  undefined **local_348;
  undefined8 local_340;
  int *local_338;
  undefined **local_328;
  undefined8 local_320;
  int *local_318;
  undefined **local_308;
  undefined8 local_300;
  int *local_2f8;
  undefined **local_2e8;
  undefined8 local_2e0;
  int *local_2d8;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined **local_2a8;
  undefined8 *local_2a0;
  long local_298 [2];
  long local_288 [2];
  long local_278 [2];
  long local_268 [2];
  long local_258 [2];
  long local_248 [2];
  long local_238 [2];
  long local_228 [2];
  long local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  string local_1e8 [16];
  long local_1d8 [2];
  string local_1c8 [16];
  long local_1b8 [2];
  string local_1a8 [16];
  long local_198 [2];
  string local_188 [16];
  long local_178 [2];
  string local_168 [16];
  string local_158 [16];
  string local_148 [16];
  string local_138 [16];
  string local_128 [16];
  string local_118 [16];
  string local_108 [16];
  string local_f8 [16];
  string local_e8 [16];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [6];
  allocator local_55;
  allocator local_54;
  allocator local_53;
  allocator local_52;
  allocator local_51;
  allocator local_50;
  allocator local_4f;
  allocator local_4e;
  allocator local_4d;
  allocator local_4c;
  allocator local_4b;
  allocator local_4a;
  allocator local_49;
  allocator local_48;
  allocator local_47;
  allocator local_46;
  allocator local_45;
  allocator local_44;
  allocator local_43;
  allocator local_42;
  allocator local_41;
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  uVar11 = Ogre::Entity::getNumSubEntities();
  if (param_2) {
    this[0x238] = (CGenericModel)0x0;
    releaseUniqueMaterials(this);
    lVar19 = *(long *)(this + 0x208);
    lVar27 = *(long *)(this + 0x210);
    lVar26 = lVar19;
    if (lVar19 != lVar27) {
      do {
        paVar29 = (allocator *)(*(long *)(lVar26 + 0x38) + -0x18);
        if (paVar29 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(*(long *)(lVar26 + 0x38) + -8);
          iVar33 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar33 < 1) {
            std::string::_Rep::_M_destroy(paVar29);
          }
        }
        lVar26 = lVar26 + 0x40;
      } while (lVar27 != lVar26);
      lVar26 = *(long *)(this + 0x208);
    }
    *(long *)(this + 0x210) = lVar19;
    uVar23 = (ulong)uVar11;
    uVar16 = lVar19 - lVar26 >> 6;
    if (uVar23 < uVar16) {
      lVar26 = lVar26 + uVar23 * 0x40;
      for (lVar27 = lVar26; lVar19 != lVar27; lVar27 = lVar27 + 0x40) {
        paVar29 = (allocator *)(*(long *)(lVar27 + 0x38) + -0x18);
        if (paVar29 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(*(long *)(lVar27 + 0x38) + -8);
          iVar33 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar33 < 1) {
            std::string::_Rep::_M_destroy(paVar29);
          }
        }
      }
      *(long *)(this + 0x210) = lVar26;
    }
    else {
                    /* try { // try from 008adff0 to 008adff4 has its CatchHandler @ 008aebc5 */
      std::vector<CRenderableStates,std::allocator<CRenderableStates>>::_M_fill_insert
                ((vector<CRenderableStates,std::allocator<CRenderableStates>> *)(this + 0x208),
                 lVar19,uVar23 - uVar16);
    }
    if (uVar11 != 0) {
      lVar26 = 0;
      local_494 = 0;
      do {
        psVar18 = (string *)Ogre::Entity::getSubEntity((uint)param_1);
        lVar19 = *(long *)(this + 0x208);
        pcVar3 = *(code **)(*(long *)psVar18 + 0x78);
        local_2a8 = &PTR__Any_00fceab0;
        local_2a0 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
        if (local_2a0 != (undefined8 *)0x0) {
          *local_2a0 = &PTR__holder_00fd18b0;
          local_2a0[1] = lVar19 + lVar26;
        }
                    /* try { // try from 008ac8b1 to 008ac8b3 has its CatchHandler @ 008ae4a3 */
        (*pcVar3)(psVar18);
        local_2a8 = &PTR__Any_00fceab0;
        if (local_2a0 != (undefined8 *)0x0) {
          (**(code **)*local_2a0)();
          Ogre::NedAllocImpl::deallocBytes(local_2a0);
        }
        lVar19 = *(long *)(this + 0x208);
        lVar27 = (**(code **)(*(long *)psVar18 + 0x10))(psVar18);
        *(undefined8 *)(lVar26 + lVar19 + 0x10) = *(undefined8 *)(lVar27 + 8);
        uVar8 = Ogre::Material::getBestTechnique
                          ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),
                           (Renderable *)0x0);
        lVar19 = Ogre::Technique::getPass(uVar8);
        uVar16 = *(long *)(lVar19 + 0xf0) - *(long *)(lVar19 + 0xe8) >> 3 & 0xffff;
        uVar12 = (uint)uVar16;
        uVar35 = uVar12;
        if (1 < uVar12) {
          iVar33 = 1;
          do {
            lVar27 = Ogre::Pass::getTextureUnitState((ushort)lVar19);
            iVar13 = std::string::compare((char *)(lVar27 + 0x160));
            uVar35 = (int)uVar16 - (uint)(iVar13 == 0);
            uVar16 = (ulong)uVar35;
            iVar33 = iVar33 + 1;
          } while (iVar33 < (int)uVar12);
        }
        *(short *)(*(long *)(this + 0x208) + 0x2a + lVar26) = (short)uVar35;
        (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar26) + 200))();
        std::string::assign((string *)(lVar26 + *(long *)(this + 0x208) + 0x38));
        if (this[0x224] == (CGenericModel)0x0) {
          (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar26) + 200))();
          std::operator+((char *)local_208,(string *)"highlightmat_");
                    /* try { // try from 008accb5 to 008acd5f has its CatchHandler @ 008ae5cd */
          plVar17 = (long *)Ogre::MaterialManager::getSingleton();
          cVar4 = (**(code **)(*plVar17 + 0xb0))(plVar17,(string *)local_208);
          if (cVar4 == '\0') {
            Ogre::Material::clone
                      ((string *)&local_328,
                       SUB81(*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),0),
                       (string *)local_208);
            uVar14 = local_320;
            local_328 = &PTR__SharedPtr_00fa4590;
            if ((local_318 != (int *)0x0) &&
               (iVar33 = *local_318, *local_318 = iVar33 + -1, iVar33 + -1 == 0)) {
              (*(code *)PTR_destroy_00fa45a0)(&local_328);
            }
            *(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26) = uVar14;
            Ogre::Material::setLightingEnabled(SUB81(uVar14,0));
            uVar8 = Ogre::Material::getBestTechnique((ushort)uVar14,(Renderable *)0x0);
            lVar19 = Ogre::Technique::getPass(uVar8);
            bVar6 = true;
            if ((short)((ulong)(*(long *)(lVar19 + 0xf0) - *(long *)(lVar19 + 0xe8)) >> 3) != 0) {
                    /* try { // try from 008ada4f to 008ada87 has its CatchHandler @ 008ae5cd */
              uVar8 = Ogre::Material::getBestTechnique((ushort)uVar14,(Renderable *)0x0);
              uVar8 = Ogre::Technique::getPass(uVar8);
              uVar14 = Ogre::Pass::getTextureUnitState(uVar8);
              Ogre::TextureUnitState::setColourOperationEx(0,uVar14,3,1,0,&Ogre::ColourValue::White)
              ;
              bVar6 = true;
            }
          }
          else {
            lVar19 = *(long *)(this + 0x208);
                    /* try { // try from 008ad452 to 008ad4aa has its CatchHandler @ 008ae5cd */
            plVar17 = (long *)Ogre::MaterialManager::getSingleton();
            (**(code **)(*plVar17 + 0xa0))(&local_348,plVar17,(string *)local_208);
            *(undefined8 *)(lVar26 + lVar19 + 0x18) = local_340;
            local_348 = &PTR__SharedPtr_00fa45d0;
            if ((local_338 != (int *)0x0) &&
               (iVar33 = *local_338, *local_338 = iVar33 + -1, iVar33 + -1 == 0)) {
              Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_348);
            }
            bVar6 = false;
          }
          if ((allocator *)(local_208[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_208[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
            }
          }
        }
        else {
          psVar20 = (string *)
                    (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar26) + 200))();
          std::string::string((string *)local_208,psVar20);
                    /* try { // try from 008aca04 to 008aca08 has its CatchHandler @ 008ae2ab */
          std::string::string((string *)local_88,"highlightmat_",local_39);
                    /* try { // try from 008aca1c to 008aca20 has its CatchHandler @ 008ae2b8 */
          STRINGS::uniqueName((STRINGS *)local_98,(string *)local_88);
                    /* try { // try from 008aca27 to 008aca2b has its CatchHandler @ 008ae420 */
          std::string::assign((string *)local_208);
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_98[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_88[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
                    /* try { // try from 008aca5e to 008acafe has its CatchHandler @ 008ae488 */
          plVar17 = (long *)Ogre::MaterialManager::getSingleton();
          cVar4 = (**(code **)(*plVar17 + 0xb0))(plVar17,(string *)local_208);
          if (cVar4 == '\0') {
            Ogre::Material::clone
                      ((string *)&local_2e8,
                       SUB81(*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),0),
                       (string *)local_208);
            uVar14 = local_2e0;
            local_2e8 = &PTR__SharedPtr_00fa4590;
            if ((local_2d8 != (int *)0x0) &&
               (iVar33 = *local_2d8, *local_2d8 = iVar33 + -1, iVar33 + -1 == 0)) {
              (*(code *)PTR_destroy_00fa45a0)(&local_2e8);
            }
            *(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26) = uVar14;
            uVar28 = (ushort)uVar14;
            uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
            lVar19 = Ogre::Technique::getPass(uVar8);
            if ((short)((ulong)(*(long *)(lVar19 + 0xf0) - *(long *)(lVar19 + 0xe8)) >> 3) != 0) {
                    /* try { // try from 008ad746 to 008ad754 has its CatchHandler @ 008ae488 */
              uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
              lVar19 = Ogre::Technique::getPass(uVar8);
              if (*(long *)(lVar19 + 0x100) != 0) {
                    /* try { // try from 008ad774 to 008ad778 has its CatchHandler @ 008ae773 */
                std::string::string((string *)local_a8,"",&local_3a);
                    /* try { // try from 008ad780 to 008ad7a3 has its CatchHandler @ 008ae783 */
                uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81(local_a8,0));
                if ((allocator *)(local_a8[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_a8[0] + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
                  }
                }
              }
              if (*(char *)(*(long *)(this + 0x208) + 0x2f + lVar26) == '\0') {
                if (this[0x238] != (CGenericModel)0x0) {
                  local_490 = 1;
                  iVar33 = uVar35 - 1;
                  if ((int)(uVar35 - 1) < 1) {
                    iVar33 = local_490;
                  }
                  while( true ) {
                    uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                    lVar19 = Ogre::Technique::getPass(uVar8);
                    if ((int)((uint)(*(long *)(lVar19 + 0xf0) - *(long *)(lVar19 + 0xe8) >> 3) &
                             0xffff) <= iVar33) break;
                    /* try { // try from 008ad807 to 008ad8a6 has its CatchHandler @ 008ae488 */
                    uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                    Ogre::Technique::getPass(uVar8);
                    uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                    uVar8 = Ogre::Technique::getPass(uVar8);
                    Ogre::Pass::removeTextureUnitState(uVar8);
                  }
                }
                uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                Ogre::Technique::getPass(uVar8);
                psVar20 = (string *)Ogre::Pass::createTextureUnitState();
                local_3f8 = (undefined **)&DAT_01423a38;
                    /* try { // try from 008ad8c0 to 008ad8c4 has its CatchHandler @ 008ae7c4 */
                std::string::string((string *)&local_3f0,(string *)&::EMPTY_STRING);
                    /* try { // try from 008ad8d6 to 008ad8da has its CatchHandler @ 008ae800 */
                std::wstring::wstring
                          ((wstring_conflict *)&local_3e8,(wstring_conflict *)&::EMPTY_WSTRING);
                local_3e0 = 4;
                local_3dc = 3;
                local_3d8 = &DAT_01423a38;
                local_3d0 = 0;
                    /* try { // try from 008ad91a to 008ad91e has its CatchHandler @ 008ae7d9 */
                std::wstring::wstring
                          ((wstring_conflict *)local_b8,L"media/sharedtextures/highlight.dds",
                           &local_3b);
                    /* try { // try from 008ad91f to 008ad946 has its CatchHandler @ 008ae7ee */
                pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
                CFileSystem::getFileInfo
                          (pCVar22,(wstring_conflict *)local_b8,(CFileInfo *)&local_3f8,false,true,
                           false);
                if ((allocator *)(local_b8[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_b8[0] + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                  }
                }
                    /* try { // try from 008ad96d to 008ad9aa has its CatchHandler @ 008ae84d */
                Ogre::TextureUnitState::setCubicTextureName(psVar20,SUB81((string *)&local_3f0,0));
                Ogre::TextureUnitState::setTextureCoordSet((uint)psVar20);
                Ogre::TextureUnitState::setTextureAddressingMode(psVar20,2);
                Ogre::TextureUnitState::setEnvironmentMap(psVar20,1,3);
                Ogre::TextureUnitState::setColourOperation(psVar20);
                if ((allocator *)(local_3d8 + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_3d8 + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_3d8 + -0x18));
                  }
                }
                if ((allocator *)(local_3e8 + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = local_3e8 + -2;
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_3e8 + -6));
                  }
                }
                if ((allocator *)(local_3f0 + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_3f0 + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_3f0 + -0x18));
                  }
                }
                if ((allocator *)(local_3f8 + -3) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  ppuVar2 = local_3f8 + -1;
                  iVar33 = *(int *)ppuVar2;
                  *(int *)ppuVar2 = *(int *)ppuVar2 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_3f8 + -3));
                    bVar6 = true;
                    goto LAB_008acb1f;
                  }
                }
              }
              else {
                    /* try { // try from 008adda7 to 008adddf has its CatchHandler @ 008ae488 */
                uVar8 = Ogre::Material::getBestTechnique(uVar28,(Renderable *)0x0);
                uVar8 = Ogre::Technique::getPass(uVar8);
                uVar14 = Ogre::Pass::getTextureUnitState(uVar8);
                Ogre::TextureUnitState::setColourOperationEx
                          (0,uVar14,4,1,0,&Ogre::ColourValue::White);
              }
            }
            bVar6 = true;
          }
          else {
            lVar19 = *(long *)(this + 0x208);
                    /* try { // try from 008ad4c7 to 008ad522 has its CatchHandler @ 008ae488 */
            plVar17 = (long *)Ogre::MaterialManager::getSingleton();
            (**(code **)(*plVar17 + 0xa0))
                      ((SharedPtr<Ogre::Resource> *)&local_308,plVar17,(string *)local_208);
            *(undefined8 *)(lVar19 + lVar26 + 0x18) = local_300;
            local_308 = &PTR__SharedPtr_00fa45d0;
            if ((local_2f8 != (int *)0x0) &&
               (iVar33 = *local_2f8, *local_2f8 = iVar33 + -1, iVar33 + -1 == 0)) {
              Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_308);
            }
            bVar6 = false;
          }
LAB_008acb1f:
          if ((allocator *)(local_208[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_208[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
            }
          }
        }
        lVar19 = Ogre::Material::getBestTechnique
                           ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),
                            (Renderable *)0x0);
        if (lVar19 == 0) {
LAB_008acc12:
          lVar19 = lVar26 + *(long *)(this + 0x208);
        }
        else {
                    /* try { // try from 008acb72 to 008acb76 has its CatchHandler @ 008ae5ba */
          std::string::string((string *)local_c8,*(char **)(*(long *)(this + 0x208) + 0x38 + lVar26)
                              ,&local_3c);
                    /* try { // try from 008acb8a to 008acb8e has its CatchHandler @ 008ae598 */
          STRINGS::StringUpper((STRINGS *)local_d8,(string *)local_c8);
                    /* try { // try from 008acb9e to 008acba2 has its CatchHandler @ 008ae5ad */
          lVar19 = std::string::find((char *)local_d8,0xfd115e,0);
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_d8[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_c8[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
          if (lVar19 != -1) {
            *(undefined1 *)(*(long *)(this + 0x208) + 0x2f + lVar26) = 1;
            this[0x23a] = (CGenericModel)0x1;
          }
          uVar12 = KSETTINGS_ALLOW_HWSKINNING;
          lVar19 = CMasterResourceManager::getSingleton();
          iVar33 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar19 + 0x90),uVar12);
          if (iVar33 != 1) goto LAB_008acc12;
          uVar8 = Ogre::Material::getBestTechnique
                            ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),
                             (Renderable *)0x0);
          psVar20 = (string *)Ogre::Technique::getPass(uVar8);
          cVar4 = *(char *)(*(long *)(this + 0x208) + 2 + lVar26);
          if (*(long *)(psVar20 + 0x100) == 0) {
LAB_008ada92:
            if (((*(long *)(this + 0x130) != 0) && (this[0x1e9] != (CGenericModel)0x0)) &&
               (cVar4 == '\0')) {
              Ogre::Entity::getMesh();
              sVar10 = Ogre::Mesh::getMaxBoneAssignments();
              *(short *)(*(long *)(this + 0x208) + 0x2c + lVar26) = sVar10;
              if (sVar10 != 0) {
                if (sVar10 == 2) {
                  if ((int)uVar35 < 2) {
                    /* try { // try from 008ae27f to 008ae283 has its CatchHandler @ 008ae2df */
                    std::string::string(local_118,"Ogre/HardwareSkinningTwo",&local_40);
                    /* try { // try from 008ae294 to 008ae298 has its CatchHandler @ 008ae2ca */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_118,0));
                    /* try { // try from 008ae2a1 to 008ae2a5 has its CatchHandler @ 008ae2df */
                    std::string::~string(local_118);
                  }
                  else {
                    /* try { // try from 008ae20f to 008ae213 has its CatchHandler @ 008ae265 */
                    std::string::string(local_108,"Ogre/HardwareSkinningTwoSecondary",&local_3f);
                    /* try { // try from 008ae224 to 008ae228 has its CatchHandler @ 008ae253 */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_108,0));
                    /* try { // try from 008ae231 to 008ae235 has its CatchHandler @ 008ae265 */
                    std::string::~string(local_108);
                  }
                }
                else if (sVar10 == 3) {
                  if ((int)uVar35 < 2) {
                    /* try { // try from 008ae4ea to 008ae4ee has its CatchHandler @ 008ae5e7 */
                    std::string::string(local_f8,"Ogre/HardwareSkinningThree",&local_3e);
                    /* try { // try from 008ae4ff to 008ae503 has its CatchHandler @ 008ae5d2 */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_f8,0));
                    /* try { // try from 008ae50c to 008ae510 has its CatchHandler @ 008ae5e7 */
                    std::string::~string(local_f8);
                  }
                  else {
                    /* try { // try from 008ae1c8 to 008ae1cc has its CatchHandler @ 008ae4d0 */
                    std::string::string(local_e8,"Ogre/HardwareSkinningThreeSecondary",&local_3d);
                    /* try { // try from 008ae1dd to 008ae1e1 has its CatchHandler @ 008ae4bb */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_e8,0));
                    /* try { // try from 008ae1ea to 008ae1ee has its CatchHandler @ 008ae4d0 */
                    std::string::~string(local_e8);
                  }
                }
                else if (sVar10 == 1) {
                  if ((int)uVar35 < 2) {
                    /* try { // try from 008ae2f8 to 008ae2fc has its CatchHandler @ 008ae360 */
                    std::string::string(local_138,"Ogre/HardwareSkinningOne",&local_42);
                    /* try { // try from 008ae30d to 008ae311 has its CatchHandler @ 008ae34b */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_138,0));
                    /* try { // try from 008ae31a to 008ae31e has its CatchHandler @ 008ae360 */
                    std::string::~string(local_138);
                  }
                  else {
                    /* try { // try from 008ae17d to 008ae181 has its CatchHandler @ 008ae2e1 */
                    std::string::string(local_128,"Ogre/HardwareSkinningOneSecondary",&local_41);
                    /* try { // try from 008ae192 to 008ae196 has its CatchHandler @ 008ae23b */
                    Ogre::Pass::setVertexProgram(psVar20,SUB81(local_128,0));
                    /* try { // try from 008ae19f to 008ae1a3 has its CatchHandler @ 008ae2e1 */
                    std::string::~string(local_128);
                  }
                }
                else if ((int)uVar35 < 2) {
                    /* try { // try from 008ae3a4 to 008ae3a8 has its CatchHandler @ 008ae66a */
                  std::string::string(local_158,"Ogre/HardwareSkinning",&local_44);
                    /* try { // try from 008ae3b9 to 008ae3bd has its CatchHandler @ 008ae655 */
                  Ogre::Pass::setVertexProgram(psVar20,SUB81(local_158,0));
                    /* try { // try from 008ae3c6 to 008ae3ca has its CatchHandler @ 008ae66a */
                  std::string::~string(local_158);
                }
                else {
                    /* try { // try from 008adb1f to 008adb23 has its CatchHandler @ 008ae38a */
                  std::string::string(local_148,"Ogre/HardwareSkinningSecondary",&local_43);
                    /* try { // try from 008adb34 to 008adb38 has its CatchHandler @ 008ae375 */
                  Ogre::Pass::setVertexProgram(psVar20,SUB81(local_148,0));
                    /* try { // try from 008adb41 to 008adb45 has its CatchHandler @ 008ae38a */
                  std::string::~string(local_148);
                }
                    /* try { // try from 008adb5b to 008adb5f has its CatchHandler @ 008ae365 */
                std::string::string(local_168,"texViewProj",&local_45);
                    /* try { // try from 008adb6b to 008adb6f has its CatchHandler @ 008ae346 */
                Ogre::Pass::getVertexProgramParameters();
                    /* try { // try from 008adb87 to 008adb8b has its CatchHandler @ 008ae324 */
                Ogre::GpuProgramParameters::setNamedAutoConstant(local_360,local_168,0x79);
                    /* try { // try from 008adb94 to 008adb98 has its CatchHandler @ 008ae346 */
                Ogre::SharedPtr<Ogre::GpuProgramParameters>::~SharedPtr(local_368);
                    /* try { // try from 008adba1 to 008adba5 has its CatchHandler @ 008ae365 */
                std::string::~string(local_168);
                Ogre::Material::compile
                          (SUB81(*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),0));
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),
                                   (Renderable *)0x0);
                lVar19 = Ogre::Technique::getPass(uVar8);
                if (*(long *)(lVar19 + 0x100) != 0) {
                  lVar19 = Ogre::Pass::getVertexProgram();
                  cVar7 = (**(code **)(**(long **)(lVar19 + 8) + 0x1c8))();
                  if (cVar7 != '\0') {
                    *(undefined1 *)(*(long *)(this + 0x208) + 2 + lVar26) = 1;
                  }
                }
              }
            }
          }
          else {
            lVar19 = Ogre::Pass::getVertexProgram();
            cVar7 = (**(code **)(**(long **)(lVar19 + 8) + 0x1c8))();
            if (cVar7 == '\0') goto LAB_008ada92;
            *(undefined1 *)(*(long *)(this + 0x208) + 2 + lVar26) = 1;
            Ogre::Entity::getMesh();
            uVar9 = Ogre::Mesh::getMaxBoneAssignments();
            *(undefined2 *)(*(long *)(this + 0x208) + 0x2c + lVar26) = uVar9;
          }
          lVar19 = lVar26 + *(long *)(this + 0x208);
          if (((*(char *)(lVar19 + 2) != '\0') && (bVar6)) &&
             ((sVar10 = *(short *)(lVar19 + 0x2c), sVar10 != 0 && (cVar4 == '\0')))) {
            if (sVar10 == 2) {
              if ((int)uVar35 < 2) {
                    /* try { // try from 008ae11d to 008ae121 has its CatchHandler @ 008aeb87 */
                std::string::string(local_1a8,"Ogre/HardwareSkinningTwo",&local_49);
                    /* try { // try from 008ae132 to 008ae150 has its CatchHandler @ 008aeb27 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81(local_1a8,0));
                    /* try { // try from 008ae154 to 008ae158 has its CatchHandler @ 008aeb87 */
                std::string::~string(local_1a8);
              }
              else {
                    /* try { // try from 008adf52 to 008adf56 has its CatchHandler @ 008aebec */
                std::string::string((string *)local_198,"Ogre/HardwareSkinningTwoSecondary",
                                    &local_48);
                    /* try { // try from 008adf67 to 008adf85 has its CatchHandler @ 008aebd9 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81((string *)local_198,0));
                if ((allocator *)(local_198[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_198[0] + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
                  }
                }
              }
            }
            else if (sVar10 == 3) {
              if ((int)uVar35 < 2) {
                    /* try { // try from 008ae06b to 008ae06f has its CatchHandler @ 008aeba2 */
                std::string::string(local_188,"Ogre/HardwareSkinningThree",&local_47);
                    /* try { // try from 008ae080 to 008ae09e has its CatchHandler @ 008aeb95 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81(local_188,0));
                    /* try { // try from 008ae0a2 to 008ae0a6 has its CatchHandler @ 008aeba2 */
                std::string::~string(local_188);
              }
              else {
                    /* try { // try from 008adeaa to 008adeae has its CatchHandler @ 008aec15 */
                std::string::string((string *)local_178,"Ogre/HardwareSkinningThreeSecondary",
                                    &local_46);
                    /* try { // try from 008adebf to 008adedd has its CatchHandler @ 008aebf1 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81((string *)local_178,0));
                if ((allocator *)(local_178[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_178[0] + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
                  }
                }
              }
            }
            else if (sVar10 == 1) {
              if ((int)uVar35 < 2) {
                    /* try { // try from 008ae012 to 008ae016 has its CatchHandler @ 008aebb5 */
                std::string::string(local_1c8,"Ogre/HardwareSkinningOne",&local_4b);
                    /* try { // try from 008ae027 to 008ae045 has its CatchHandler @ 008aeba7 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81(local_1c8,0));
                    /* try { // try from 008ae049 to 008ae04d has its CatchHandler @ 008aebb5 */
                std::string::~string(local_1c8);
              }
              else {
                    /* try { // try from 008ade07 to 008ade0b has its CatchHandler @ 008aec28 */
                std::string::string((string *)local_1b8,"Ogre/HardwareSkinningOneSecondary",
                                    &local_4a);
                    /* try { // try from 008ade1c to 008ade3a has its CatchHandler @ 008aebf6 */
                uVar8 = Ogre::Material::getBestTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                   (Renderable *)0x0);
                psVar20 = (string *)Ogre::Technique::getPass(uVar8);
                Ogre::Pass::setVertexProgram(psVar20,SUB81((string *)local_1b8,0));
                if ((allocator *)(local_1b8[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_1b8[0] + -8);
                  iVar33 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar33 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
                  }
                }
              }
            }
            else if ((int)uVar35 < 2) {
                    /* try { // try from 008ae0c4 to 008ae0c8 has its CatchHandler @ 008aeb8e */
              std::string::string(local_1e8,"Ogre/HardwareSkinning",&local_4d);
                    /* try { // try from 008ae0d9 to 008ae0f7 has its CatchHandler @ 008aeb8c */
              uVar8 = Ogre::Material::getBestTechnique
                                ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                 (Renderable *)0x0);
              psVar20 = (string *)Ogre::Technique::getPass(uVar8);
              Ogre::Pass::setVertexProgram(psVar20,SUB81(local_1e8,0));
                    /* try { // try from 008ae0fb to 008ae0ff has its CatchHandler @ 008aeb8e */
              std::string::~string(local_1e8);
            }
            else {
                    /* try { // try from 008ad62c to 008ad630 has its CatchHandler @ 008aecaf */
              std::string::string((string *)local_1d8,"Ogre/HardwareSkinningSecondary",&local_4c);
                    /* try { // try from 008ad641 to 008ad65f has its CatchHandler @ 008aecaa */
              uVar8 = Ogre::Material::getBestTechnique
                                ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                                 (Renderable *)0x0);
              psVar20 = (string *)Ogre::Technique::getPass(uVar8);
              Ogre::Pass::setVertexProgram(psVar20,SUB81((string *)local_1d8,0));
              if ((allocator *)(local_1d8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_1d8[0] + -8);
                iVar33 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar33 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
                }
              }
            }
                    /* try { // try from 008ad691 to 008ad695 has its CatchHandler @ 008aec79 */
            std::string::string((string *)local_1f8,"texViewProj",&local_4e);
                    /* try { // try from 008ad6a6 to 008ad6c7 has its CatchHandler @ 008aec69 */
            uVar8 = Ogre::Material::getBestTechnique
                              ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),
                               (Renderable *)0x0);
            Ogre::Technique::getPass(uVar8);
            Ogre::Pass::getVertexProgramParameters();
                    /* try { // try from 008ad6da to 008ad6de has its CatchHandler @ 008aec59 */
            Ogre::GpuProgramParameters::setNamedAutoConstant(local_380,(string *)local_1f8,0x79);
            local_388 = &PTR__SharedPtr_00fd1950;
            if ((local_378 != (int *)0x0) &&
               (iVar33 = *local_378, *local_378 = iVar33 + -1, iVar33 + -1 == 0)) {
                    /* try { // try from 008ad706 to 008ad70a has its CatchHandler @ 008aec69 */
              Ogre::SharedPtr<Ogre::GpuProgramParameters>::destroy
                        ((SharedPtr<Ogre::GpuProgramParameters> *)&local_388);
            }
            if ((allocator *)(local_1f8[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_1f8[0] + -8);
              iVar33 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar33 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
              }
            }
            Ogre::Material::compile
                      (SUB81(*(undefined8 *)(*(long *)(this + 0x208) + 0x18 + lVar26),0));
            goto LAB_008acc12;
          }
        }
        if (this[0x224] == (CGenericModel)0x0) {
          psVar20 = (string *)(**(code **)(**(long **)(lVar19 + 0x10) + 200))();
          std::string::string((string *)local_208,psVar20);
                    /* try { // try from 008acdf7 to 008ace21 has its CatchHandler @ 008ae3d0 */
          lVar19 = std::string::find((char *)local_208,0xfd11ca,0);
          if (lVar19 != -1) {
            *(undefined1 *)(*(long *)(this + 0x208) + 0x30 + lVar26) = 1;
          }
          lVar19 = std::string::find((char *)local_208,0xfd11d1,0);
          if (lVar19 != -1) {
            *(undefined1 *)(*(long *)(this + 0x208) + 0x31 + lVar26) = 0;
          }
          if ((allocator *)(local_208[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_208[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
            }
          }
        }
        else {
          *(undefined1 *)(lVar19 + 1) = 1;
          if (param_1 != (Entity *)0x0) {
            (**(code **)(*(long *)param_1 + 0x178))(param_1,4);
          }
        }
        *(undefined8 *)(lVar26 + *(long *)(this + 0x208) + 8) =
             *(undefined8 *)(lVar26 + *(long *)(this + 0x208) + 0x10);
        if (this[0x224] != (CGenericModel)0x0) {
          psVar20 = (string *)
                    (**(code **)(**(long **)(*(long *)(this + 0x208) + 0x10 + lVar26) + 200))();
          std::string::string((string *)local_218,psVar20);
                    /* try { // try from 008aceb5 to 008aceb9 has its CatchHandler @ 008ae643 */
          std::string::append((char *)local_218,0xfd11d9);
                    /* try { // try from 008acec0 to 008acec4 has its CatchHandler @ 008ae653 */
          STRINGS::uniqueName((STRINGS *)local_208,(string *)local_218);
          if ((allocator *)(local_218[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_218[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
            }
          }
          lVar19 = *(long *)(this + 0x208);
                    /* try { // try from 008acf03 to 008acf7f has its CatchHandler @ 008ae626 */
          Ogre::Material::clone
                    ((string *)&local_3a8,SUB81(*(undefined8 *)(lVar26 + lVar19 + 0x10),0),
                     (string *)local_208);
          *(undefined8 *)(lVar26 + lVar19 + 0x10) = local_3a0;
          local_3a8 = &PTR__SharedPtr_00fa4590;
          if ((local_398 != (int *)0x0) &&
             (iVar33 = *local_398, *local_398 = iVar33 + -1, iVar33 + -1 == 0)) {
            (*(code *)PTR_destroy_00fa45a0)((string *)&local_3a8);
          }
          Ogre::SubEntity::setMaterialName(psVar18);
          lVar19 = Ogre::Material::getBestTechnique
                             ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x10 + lVar26),
                              (Renderable *)0x0);
          if (lVar19 != 0) {
            lVar19 = *(long *)(this + 0x208);
            uVar5 = Ogre::Material::isTransparent();
            *(undefined1 *)(lVar26 + lVar19 + 0x2e) = uVar5;
          }
                    /* try { // try from 008acf9d to 008acfa1 has its CatchHandler @ 008ae636 */
          std::string::string((string *)local_228,"rbmat_",&local_4f);
                    /* try { // try from 008acfb0 to 008acfb4 has its CatchHandler @ 008ae63b */
          STRINGS::uniqueName((STRINGS *)local_238,(string *)local_228);
                    /* try { // try from 008acfbb to 008acfbf has its CatchHandler @ 008ae408 */
          std::string::assign((string *)local_208);
          if ((allocator *)(local_238[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_238[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
            }
          }
          if ((allocator *)(local_228[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_228[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
            }
          }
                    /* try { // try from 008acff2 to 008ad021 has its CatchHandler @ 008ae626 */
          plVar17 = (long *)Ogre::MaterialManager::getSingleton();
          (**(code **)(*plVar17 + 0x28))
                    ((SharedPtr<Ogre::Resource> *)&local_3c8,plVar17,(string *)local_208,
                     &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
          local_3e0 = 0;
          local_3f8 = &PTR__MaterialPtr_00fa44d0;
          local_3f0 = local_3c0;
          local_3e8 = local_3b8;
          if (local_3b8 != (int *)0x0) {
            *local_3b8 = *local_3b8 + 1;
          }
          local_3c8 = &PTR__SharedPtr_00fa45d0;
          if ((local_3b8 != (int *)0x0) &&
             (iVar33 = *local_3b8, *local_3b8 = iVar33 + -1, iVar33 + -1 == 0)) {
                    /* try { // try from 008ad088 to 008ad166 has its CatchHandler @ 008ae6f2 */
            Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_3c8);
          }
          *(long *)(*(long *)(this + 0x208) + 0x20 + lVar26) = local_3f0;
          *(undefined1 *)(*(long *)(*(long *)(this + 0x208) + 0x20 + lVar26) + 0xf0) = 0;
          uVar8 = Ogre::Material::getTechnique
                            ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x20 + lVar26));
          pCVar21 = (ColourValue *)Ogre::Technique::getPass(uVar8);
          Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
          local_2b8 = 0;
          local_2b4 = 0;
          local_2b0 = 0;
          local_2ac = 0x3f800000;
          Ogre::Pass::setAmbient(pCVar21);
          local_2c8 = 0;
          local_2c4 = 0;
          local_2c0 = 0;
          local_2bc = 0x3f800000;
          Ogre::Pass::setDiffuse(pCVar21);
          Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar21,0));
          local_428 = &DAT_01423a38;
                    /* try { // try from 008ad17d to 008ad181 has its CatchHandler @ 008ae66f */
          std::string::string((string *)&local_420,(string *)&::EMPTY_STRING);
                    /* try { // try from 008ad193 to 008ad197 has its CatchHandler @ 008ae691 */
          std::wstring::wstring((wstring_conflict *)&local_418,(wstring_conflict *)&::EMPTY_WSTRING)
          ;
          local_410 = 4;
          local_40c = 3;
          local_408 = &DAT_01423a38;
          local_400 = 0;
                    /* try { // try from 008ad1da to 008ad1de has its CatchHandler @ 008ae6a7 */
          std::wstring::wstring
                    ((wstring_conflict *)local_248,L"media/sharedTextures/outlineblue.dds",&local_50
                    );
                    /* try { // try from 008ad1df to 008ad201 has its CatchHandler @ 008ae6b9 */
          pCVar22 = (CFileSystem *)CFileSystem::getSingleton();
          CFileSystem::getFileInfo
                    (pCVar22,(wstring_conflict *)local_248,(CFileInfo *)&local_428,false,true,false)
          ;
          if ((allocator *)(local_248[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_248[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
            }
          }
                    /* try { // try from 008ad225 to 008ad2c9 has its CatchHandler @ 008aea89 */
          Ogre::Pass::createTextureUnitState((string *)pCVar21,(ushort)(string *)&local_420);
          Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar21);
          Ogre::Pass::setFog(DAT_00fa4828,0,pCVar21,1,0);
          uVar14 = Ogre::Pass::getTextureUnitState((ushort)pCVar21);
          Ogre::TextureUnitState::setEnvironmentMap(uVar14,1,1);
          uVar14 = Ogre::Material::getTechnique
                             ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x20 + lVar26));
          Ogre::Technique::setDepthFunction(uVar14,7);
          bVar6 = (bool)Ogre::Material::getTechnique
                                  ((ushort)*(undefined8 *)(*(long *)(this + 0x208) + 0x20 + lVar26))
          ;
          Ogre::Technique::setDepthWriteEnabled(bVar6);
          Ogre::Material::setSceneBlending
                    (*(undefined8 *)(*(long *)(this + 0x208) + 0x20 + lVar26),2);
          lVar19 = lVar26 + *(long *)(this + 0x208);
          if ((*(char *)(lVar19 + 2) != '\0') && (sVar10 = *(short *)(lVar19 + 0x2c), sVar10 != 0))
          {
            if (sVar10 == 2) {
                    /* try { // try from 008add38 to 008add3c has its CatchHandler @ 008ae9b8 */
              std::string::string((string *)local_268,"Ogre/HardwareSkinningBehindTwo",&local_52);
                    /* try { // try from 008add48 to 008add4c has its CatchHandler @ 008ae9b3 */
              Ogre::Pass::setVertexProgram((string *)pCVar21,SUB81((string *)local_268,0));
              if ((allocator *)(local_268[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_268[0] + -8);
                iVar33 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar33 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
                  lVar19 = lVar26 + *(long *)(this + 0x208);
                  goto LAB_008ad351;
                }
              }
            }
            else if (sVar10 == 3) {
                    /* try { // try from 008adcb8 to 008adcbc has its CatchHandler @ 008ae975 */
              std::string::string((string *)local_258,"Ogre/HardwareSkinningBehindThree",&local_51);
                    /* try { // try from 008adcc8 to 008adccc has its CatchHandler @ 008ae985 */
              Ogre::Pass::setVertexProgram((string *)pCVar21,SUB81((string *)local_258,0));
              if ((allocator *)(local_258[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_258[0] + -8);
                iVar33 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar33 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
                  lVar19 = lVar26 + *(long *)(this + 0x208);
                  goto LAB_008ad351;
                }
              }
            }
            else if (sVar10 == 1) {
                    /* try { // try from 008adc38 to 008adc3c has its CatchHandler @ 008ae8f4 */
              std::string::string((string *)local_278,"Ogre/HardwareSkinningBehindOne",&local_53);
                    /* try { // try from 008adc48 to 008adc4c has its CatchHandler @ 008ae904 */
              Ogre::Pass::setVertexProgram((string *)pCVar21,SUB81((string *)local_278,0));
              if ((allocator *)(local_278[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_278[0] + -8);
                iVar33 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar33 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
                  lVar19 = lVar26 + *(long *)(this + 0x208);
                  goto LAB_008ad351;
                }
              }
            }
            else {
                    /* try { // try from 008ad319 to 008ad31d has its CatchHandler @ 008ae970 */
              std::string::string((string *)local_288,"Ogre/HardwareSkinningBehind",&local_54);
                    /* try { // try from 008ad329 to 008ad32d has its CatchHandler @ 008aea9c */
              Ogre::Pass::setVertexProgram((string *)pCVar21,SUB81((string *)local_288,0));
              if ((allocator *)(local_288[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_288[0] + -8);
                iVar33 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar33 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
                }
              }
            }
            lVar19 = lVar26 + *(long *)(this + 0x208);
          }
LAB_008ad351:
                    /* try { // try from 008ad35a to 008ad35e has its CatchHandler @ 008aea89 */
          Ogre::Material::compile(SUB81(*(undefined8 *)(lVar19 + 0x20),0));
          if ((allocator *)(local_408 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_408 + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_408 + -0x18));
            }
          }
          if ((allocator *)(local_418 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_418 + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_418 + -0x18));
            }
          }
          if ((allocator *)(local_420 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_420 + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_420 + -0x18));
            }
          }
          if ((allocator *)(local_428 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_428 + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_428 + -0x18));
            }
          }
          local_3f8 = &PTR__SharedPtr_00fa4590;
          if ((local_3e8 != (int *)0x0) &&
             (iVar33 = *local_3e8, *local_3e8 = iVar33 + -1, iVar33 + -1 == 0)) {
                    /* try { // try from 008ad3f8 to 008ad3fa has its CatchHandler @ 008ae626 */
            (*(code *)PTR_destroy_00fa45a0)(&local_3f8);
          }
          if ((allocator *)(local_208[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_208[0] + -8);
            iVar33 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar33 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
            }
          }
        }
        local_494 = local_494 + 1;
        lVar26 = lVar26 + 0x40;
      } while (local_494 < uVar11);
    }
  }
  if (*(Entity **)(this + 0x60) != param_1) {
    if (*(long *)(this + 0x230) == 0) {
      *(Entity **)(this + 0x230) = *(Entity **)(this + 0x60);
    }
    *(undefined8 *)(this + 0x60) = 0;
  }
  CSceneNodeObject::sceneNodeAttachEntity((CSceneNodeObject *)this,param_1);
  if (*(long *)(this + 0x130) != 0) {
    *(undefined8 *)(this + 0x130) = *(undefined8 *)(param_1 + 0x2e8);
    if (*(int *)(this + 0x150) == 0) {
      if (*(long *)(this + 0x1e0) != 0) {
        if (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0) {
          uVar11 = 0;
          do {
            uVar14 = Ogre::Entity::getAnimationState((string *)param_1);
            uVar35 = *(uint *)(this + 0x150);
            if (uVar35 < *(uint *)(this + 0x154)) {
              pvVar15 = *(void **)(this + 0x148);
            }
            else if (*(long *)(this + 0x148) == 0) {
              *(uint *)(this + 0x154) = *(uint *)(this + 0x158);
              pvVar15 = operator_new__((ulong)*(uint *)(this + 0x158) << 3);
              *(void **)(this + 0x148) = pvVar15;
              uVar35 = *(uint *)(this + 0x150);
            }
            else {
              uVar35 = *(uint *)(this + 0x154) + *(int *)(this + 0x158);
              pvVar15 = operator_new__((ulong)uVar35 << 3);
              if (*(int *)(this + 0x154) != 0) {
                uVar12 = 0;
                do {
                  uVar16 = (ulong)uVar12;
                  uVar12 = uVar12 + 1;
                  *(undefined8 *)((long)pvVar15 + uVar16 * 8) =
                       *(undefined8 *)(*(long *)(this + 0x148) + uVar16 * 8);
                } while (uVar12 < *(uint *)(this + 0x154));
              }
              if (*(void **)(this + 0x148) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0x148));
              }
              *(void **)(this + 0x148) = pvVar15;
              *(uint *)(this + 0x154) = uVar35;
              uVar35 = *(uint *)(this + 0x150);
            }
            uVar11 = uVar11 + 1;
            *(undefined8 *)((long)pvVar15 + (ulong)uVar35 * 8) = uVar14;
            *(int *)(this + 0x150) = *(int *)(this + 0x150) + 1;
          } while (uVar11 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
        }
                    /* try { // try from 008ac32e to 008ac332 has its CatchHandler @ 008aeadb */
        std::string::string((string *)local_298,"IDLE",&local_55);
                    /* try { // try from 008ac34e to 008ac352 has its CatchHandler @ 008aeaeb */
        playAnimation(this,(string *)local_298,true,DAT_00fa47fc,DAT_00fa8760);
        if ((allocator *)(local_298[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_298[0] + -8);
          iVar33 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar33 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
          }
        }
      }
    }
    else if (*(long *)(this + 0x1e0) != 0) {
      if (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(this + 0x154)) {
            puVar34 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x148));
          }
          else {
            puVar34 = *(undefined8 **)(this + 0x148);
          }
          uVar11 = uVar11 + 1;
          uVar14 = Ogre::Entity::getAnimationState((string *)param_1);
          *puVar34 = uVar14;
        } while (uVar11 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
      }
      lVar27 = *(long *)(this + 0x180);
      lVar30 = *(long *)(this + 400);
      lVar19 = *(long *)(this + 0x170);
      lVar31 = *(long *)(this + 0x198);
      lVar32 = *(long *)(this + 0x1a8);
      lVar26 = *(long *)(this + 0x188);
      if (0 < (int)(lVar32 - lVar26 >> 3) * 0x40 + -0x40 +
              (int)(lVar27 - lVar19 >> 3) + (int)(lVar30 - lVar31 >> 3)) {
        iVar33 = 0;
        do {
          lVar25 = (long)iVar33;
          uVar16 = (lVar19 - *(long *)(this + 0x178) >> 3) + lVar25;
          uVar23 = (long)uVar16 >> 6;
          if ((long)uVar16 < 0) {
LAB_008ac607:
            uVar24 = ~(~uVar16 >> 6);
            uVar11 = *(uint *)(*(long *)(*(long *)(lVar26 + uVar24 * 8) +
                                        (uVar16 + uVar24 * -0x40) * 8) + 0x10);
            if ((-1 < (long)uVar16) && (uVar24 = uVar23, (long)uVar16 < 0x40)) goto LAB_008ac478;
LAB_008ac5ca:
            plVar17 = (long *)((uVar16 + uVar24 * -0x40) * 8 + *(long *)(lVar26 + uVar24 * 8));
          }
          else {
            if (0x3f < (long)uVar16) {
              if ((long)uVar16 < 1) goto LAB_008ac607;
              uVar11 = *(uint *)(*(long *)(*(long *)(lVar26 + uVar23 * 8) +
                                          (ulong)((uint)uVar16 & 0x3f) * 8) + 0x10);
              uVar24 = uVar23;
              goto LAB_008ac5ca;
            }
            uVar11 = *(uint *)(*(long *)(lVar19 + lVar25 * 8) + 0x10);
LAB_008ac478:
            plVar17 = (long *)(lVar19 + lVar25 * 8);
          }
          if (*(char *)(*plVar17 + 0x28) == '\0') {
            if (uVar11 < *(uint *)(this + 0x154)) {
              puVar34 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(this + 0x148));
            }
            else {
              puVar34 = *(undefined8 **)(this + 0x148);
            }
            Ogre::AnimationState::setEnabled(SUB81(*puVar34,0));
            uVar16 = (*(long *)(this + 0x170) - *(long *)(this + 0x178) >> 3) + lVar25;
            if ((long)uVar16 < 0) {
LAB_008ac689:
              uVar23 = ~(~uVar16 >> 6);
LAB_008ac4e9:
              plVar17 = (long *)((uVar16 + uVar23 * -0x40) * 8 +
                                *(long *)(*(long *)(this + 0x188) + uVar23 * 8));
            }
            else {
              plVar17 = (long *)(*(long *)(this + 0x170) + lVar25 * 8);
              if (0x3f < (long)uVar16) {
                if ((long)uVar16 < 1) goto LAB_008ac689;
                uVar23 = (long)uVar16 >> 6;
                goto LAB_008ac4e9;
              }
            }
            Ogre::AnimationState::setTimePosition(*(float *)(*plVar17 + 0x20));
            lVar26 = *(long *)(this + 0x188);
            lVar19 = *(long *)(this + 0x170);
            lVar27 = *(long *)(this + 0x180);
            lVar31 = *(long *)(this + 0x198);
            lVar30 = *(long *)(this + 400);
            lVar32 = *(long *)(this + 0x1a8);
          }
          iVar33 = iVar33 + 1;
        } while (iVar33 < (int)(lVar32 - lVar26 >> 3) * 0x40 + -0x40 +
                          (int)(lVar27 - lVar19 >> 3) + (int)(lVar30 - lVar31 >> 3));
      }
      updateAnimation(this,0.0,true);
    }
  }
  return;
}



/* address=008aecd0
   symbol=CGenericModel::loadModel */

/* WARNING: Removing unreachable block (ram,0x008b070c) */
/* WARNING: Removing unreachable block (ram,0x008b0442) */
/* WARNING: Removing unreachable block (ram,0x008b04c4) */
/* WARNING: Removing unreachable block (ram,0x008b0607) */
/* WARNING: Removing unreachable block (ram,0x008b067c) */
/* WARNING: Removing unreachable block (ram,0x008b0640) */
/* WARNING: Removing unreachable block (ram,0x008b052d) */
/* WARNING: Removing unreachable block (ram,0x008b03ed) */
/* WARNING: Removing unreachable block (ram,0x008b0755) */
/* WARNING: Removing unreachable block (ram,0x008b06fe) */
/* CGenericModel::loadModel(std::wstring, std::wstring, bool, bool, bool) */

void __thiscall
CGenericModel::loadModel
          (CGenericModel *this,wstring_conflict *param_2,wstring_conflict *param_3,char param_4,
          CGenericModel param_5,char param_6)

{
  int *piVar1;
  short *psVar2;
  uint *puVar3;
  byte *pbVar4;
  int iVar5;
  byte bVar6;
  size_t __n;
  wstring_conflict *pwVar7;
  ushort uVar8;
  int iVar9;
  long lVar10;
  long *plVar11;
  CMasterResourceManager *pCVar12;
  long lVar13;
  undefined4 *puVar14;
  CAnimationSet *pCVar15;
  string *psVar16;
  ulong uVar17;
  runtime_error *prVar18;
  undefined8 uVar19;
  short *psVar20;
  ulong uVar21;
  uint uVar22;
  uint *puVar23;
  byte *pbVar24;
  short *psVar25;
  uint uVar26;
  undefined8 *puVar27;
  undefined8 *puVar28;
  undefined8 *puVar29;
  byte *pbVar30;
  undefined8 *puVar31;
  vector<TArrayList<int>,std::allocator<TArrayList<int>>> *pvVar32;
  undefined8 *puVar33;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined2 *local_2c8 [4];
  short *local_2a8;
  int local_2a0;
  wstring_conflict *local_290;
  ushort *local_288;
  undefined4 local_280;
  undefined8 local_278;
  undefined8 local_270;
  undefined2 *local_268;
  undefined4 local_260;
  undefined8 local_258;
  undefined8 local_250;
  void *local_248;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined8 *local_228;
  undefined8 *local_220;
  undefined8 local_218;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  long local_1e8 [2];
  string local_1d8 [16];
  string local_1c8 [16];
  undefined8 local_1b8;
  wstring_conflict local_1a8 [16];
  wstring_conflict local_198 [16];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  long local_168 [2];
  byte *local_158 [2];
  long local_148 [2];
  long local_138 [2];
  wstring_conflict local_128 [16];
  FILESYSTEM local_118 [16];
  wstring_conflict local_108 [16];
  FILESYSTEM local_f8 [16];
  long local_e8 [2];
  long local_d8 [2];
  string local_c8 [16];
  wstring_conflict local_b8 [16];
  undefined1 *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  ushort local_58;
  short local_56;
  undefined2 local_54;
  allocator local_42;
  allocator local_41 [8];
  allocator local_39 [9];

  uVar22 = KSETTINGS_NETBOOK_MODE;
  lVar10 = CMasterResourceManager::getSingleton();
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar22);
  *(undefined4 *)(this + 0x248) = 0;
  clearAnimations(this);
  STRINGS::StringUpper((STRINGS *)local_68,param_2);
                    /* try { // try from 008aed3c to 008aed40 has its CatchHandler @ 008b0677 */
  std::wstring::assign(param_2);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  STRINGS::StringUpper((STRINGS *)local_78,param_3);
                    /* try { // try from 008aed73 to 008aed77 has its CatchHandler @ 008b063e */
  std::wstring::assign(param_3);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  __n = *(size_t *)(*(wchar_t **)param_2 + -6);
  if ((__n == *(size_t *)(*(wchar_t **)(this + 0x110) + -6)) &&
     (iVar9 = wmemcmp(*(wchar_t **)param_2,*(wchar_t **)(this + 0x110),__n), iVar9 == 0)) {
    return;
  }
  this[0x224] = param_5;
  unloadModel(this);
  std::wstring::assign((wstring_conflict *)(this + 0x110));
  std::wstring::assign((wstring_conflict *)(this + 0x118));
  FILESYSTEM::CleanPath((FILESYSTEM *)local_88,param_2);
                    /* try { // try from 008aedf7 to 008aedfb has its CatchHandler @ 008b05f4 */
  std::wstring::assign(param_2);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  FILESYSTEM::RemoveFileName((FILESYSTEM *)local_98,param_2);
  local_a8[0] = &DAT_01423a38;
                    /* try { // try from 008aee4f to 008aee8b has its CatchHandler @ 008b0687 */
  plVar11 = (long *)OGRE_UTILITIES::createEntity
                              (*(undefined8 *)(this + 0x140),param_2,*(undefined4 *)(this + 0x204),
                               &DAT_00faa818);
  *(long **)(this + 0x60) = plVar11;
  if (plVar11 == (long *)0x0) {
                    /* try { // try from 008afde3 to 008afde7 has its CatchHandler @ 008b0687 */
    STRINGS::StringConvertToUTF8(local_b8);
                    /* try { // try from 008afe08 to 008afe0c has its CatchHandler @ 008b0791 */
    std::operator+((char *)local_c8,(string *)"Unable to find file : ");
                    /* try { // try from 008afe1b to 008afe1f has its CatchHandler @ 008b0760 */
    std::string::assign((string *)local_a8);
                    /* try { // try from 008afe23 to 008afe27 has its CatchHandler @ 008b0791 */
    std::string::~string(local_c8);
                    /* try { // try from 008afe30 to 008afe34 has its CatchHandler @ 008b0687 */
    std::string::~string((string *)local_b8);
                    /* try { // try from 008afe48 to 008afe4c has its CatchHandler @ 008b06ba */
    std::operator+((char *)local_d8,(string *)"[Genericmodel] Error creating entity\n");
                    /* try { // try from 008afe4d to 008afe63 has its CatchHandler @ 008b0743 */
    uVar19 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar19,local_d8,3,0);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    wcslen(L"");
                    /* try { // try from 008afe92 to 008afecb has its CatchHandler @ 008b06ba */
    std::wstring::assign((wchar_t *)(this + 0x110),0x1001608);
    wcslen(L"");
    std::wstring::assign((wchar_t *)(this + 0x118),0x1001608);
    *(undefined8 *)(this + 0x60) = 0;
    std::string::assign((char *)(this + 0x120),0x10257f7);
    goto LAB_008afecc;
  }
  (**(code **)(*plVar11 + 0x88))(plVar11);
  std::string::assign((string *)(this + 0x120));
  *(undefined1 *)(*(long *)(this + 0x60) + 0xc0) = 0;
                    /* try { // try from 008aeeaa to 008aeeae has its CatchHandler @ 008b06ba */
  std::wstring::wstring((wstring_conflict *)local_e8,param_3);
  if (*(long *)(local_e8[0] + -0x18) == 0) {
                    /* try { // try from 008af553 to 008af557 has its CatchHandler @ 008b05bf */
    FILESYSTEM::GetFileName(local_f8,param_2);
                    /* try { // try from 008af563 to 008af567 has its CatchHandler @ 008b0360 */
    std::wstring::assign((wstring_conflict *)local_e8);
                    /* try { // try from 008af56b to 008af599 has its CatchHandler @ 008b05bf */
    std::wstring::~wstring((wstring_conflict *)local_f8);
    std::wstring::wstring
              (local_108,(wstring_conflict *)local_e8,0,*(long *)(local_e8[0] + -0x18) - 5);
                    /* try { // try from 008af5a5 to 008af5a9 has its CatchHandler @ 008b0538 */
    std::wstring::assign((wstring_conflict *)local_e8);
                    /* try { // try from 008af5ad to 008af5b1 has its CatchHandler @ 008b05bf */
    std::wstring::~wstring(local_108);
  }
  else {
                    /* try { // try from 008aeed0 to 008aeed4 has its CatchHandler @ 008b05bf */
    FILESYSTEM::GetFileName(local_118,param_3);
                    /* try { // try from 008aeee0 to 008aeee4 has its CatchHandler @ 008b05af */
    std::wstring::assign((wstring_conflict *)local_e8);
                    /* try { // try from 008aeee8 to 008aef34 has its CatchHandler @ 008b05bf */
    std::wstring::~wstring((wstring_conflict *)local_118);
  }
  plVar11 = *(long **)(*(long *)(this + 0x60) + 0x2e8);
  if (plVar11 != (long *)0x0) {
    *(long **)(this + 0x130) = plVar11;
    uVar8 = (**(code **)(*plVar11 + 0x218))();
    std::operator+((wstring_conflict *)local_138,(wstring_conflict *)local_98);
                    /* try { // try from 008aef40 to 008aef44 has its CatchHandler @ 008b0528 */
    std::wstring::wstring(local_128,(wstring_conflict *)local_138);
    wcslen(L".animation");
                    /* try { // try from 008aef5f to 008aef63 has its CatchHandler @ 008b0513 */
    std::wstring::append((wchar_t *)local_128,0xfd12c8);
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    lVar10 = *(long *)(this + 0x1e0);
                    /* try { // try from 008aef98 to 008aef9c has its CatchHandler @ 008b04df */
    std::wstring::wstring((wstring_conflict *)local_148,local_128);
                    /* try { // try from 008aef9d to 008aefac has its CatchHandler @ 008b04cf */
    pCVar12 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
    lVar13 = CMasterResourceManager::getAnimationSet(pCVar12);
    *(long *)(this + 0x1e0) = lVar13;
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
      lVar13 = *(long *)(this + 0x1e0);
    }
    if (lVar10 == 0) {
      pCVar15 = (CAnimationSet *)0x0;
      if (lVar13 != 0) {
        *(int *)(lVar13 + 0x10) = *(int *)(lVar13 + 0x10) + 1;
        goto LAB_008aefd7;
      }
    }
    else {
LAB_008aefd7:
      pCVar15 = *(CAnimationSet **)(this + 0x1e0);
    }
    if (param_6 == '\0') {
LAB_008aeffd:
      if (pCVar15 == (CAnimationSet *)0x0) goto LAB_008af5d6;
      if (param_6 != '\0') goto LAB_008af60f;
    }
    else {
      if (pCVar15 != (CAnimationSet *)0x0) {
                    /* try { // try from 008aeff1 to 008aeff5 has its CatchHandler @ 008b04df */
        CAnimationSet::clear(pCVar15);
        pCVar15 = *(CAnimationSet **)(this + 0x1e0);
        goto LAB_008aeffd;
      }
LAB_008af5d6:
                    /* try { // try from 008af5e1 to 008af5e5 has its CatchHandler @ 008b04df */
      pCVar15 = (CAnimationSet *)Ogre::NedAllocImpl::allocBytes(0x70,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008af5ec to 008af5f0 has its CatchHandler @ 008b0595 */
      CAnimationSet::CAnimationSet(pCVar15);
      *(CAnimationSet **)(this + 0x1e0) = pCVar15;
                    /* try { // try from 008af5f8 to 008af671 has its CatchHandler @ 008b04df */
      pCVar12 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
      CMasterResourceManager::addAnimationSet(pCVar12,pCVar15);
      pCVar15 = *(CAnimationSet **)(this + 0x1e0);
LAB_008af60f:
      std::wstring::assign((wstring_conflict *)(pCVar15 + 0x18));
      *(uint *)(*(long *)(this + 0x1e0) + 0x20) = (uint)uVar8;
      if (*(int *)(*(long *)(this + 0x1e0) + 0x20) != 0) {
        uVar22 = 0;
        do {
          (**(code **)(**(long **)(this + 0x130) + 0x220))(*(long **)(this + 0x130),uVar22 & 0xffff)
          ;
          psVar16 = (string *)Ogre::Animation::getName();
          std::string::string((string *)local_158,psVar16);
          lVar10 = *(long *)(this + 0x1e0);
          psVar16 = *(string **)(lVar10 + 0x30);
          if (psVar16 == *(string **)(lVar10 + 0x38)) {
                    /* try { // try from 008b01b2 to 008b01b6 has its CatchHandler @ 008b03e8 */
            std::vector<std::string,std::allocator<std::string>>::_M_insert_aux
                      ((vector<std::string,std::allocator<std::string>> *)(lVar10 + 0x28),psVar16,
                       local_158);
          }
          else {
            if (psVar16 == (string *)0x0) {
              lVar13 = 0;
            }
            else {
                    /* try { // try from 008af698 to 008af69c has its CatchHandler @ 008b028f */
              std::string::string(psVar16,(string *)local_158);
              lVar13 = *(long *)(lVar10 + 0x30);
            }
            *(long *)(lVar10 + 0x30) = lVar13 + 8;
          }
                    /* try { // try from 008af6b9 to 008af6bd has its CatchHandler @ 008b03e8 */
          STRINGS::StringUpper((STRINGS *)local_168,(string *)local_158);
                    /* try { // try from 008af6cb to 008af6cf has its CatchHandler @ 008b03d3 */
          iVar9 = std::string::compare((char *)local_168);
          if ((allocator *)(local_168[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_168[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
            }
          }
          if (iVar9 == 0) {
                    /* try { // try from 008b0014 to 008b0018 has its CatchHandler @ 008b03e8 */
            std::operator+(local_188,(wchar_t *)local_e8);
                    /* try { // try from 008b002c to 008b0030 has its CatchHandler @ 008b034b */
            std::vector<std::wstring,std::allocator<std::wstring>>::push_back
                      ((vector<std::wstring,std::allocator<std::wstring>> *)
                       (*(long *)(this + 0x1e0) + 0x40),local_188);
                    /* try { // try from 008b0039 to 008b003d has its CatchHandler @ 008b03e8 */
            std::wstring::~wstring(local_188);
          }
          else {
            local_288 = &DAT_01426458;
            local_270 = 0;
            local_280 = 0;
            local_278 = 0;
            local_1b8 = &DAT_01424558;
                    /* try { // try from 008af73b to 008af86c has its CatchHandler @ 008b0248 */
            std::wstring::assign((wchar_t *)&local_1b8);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_288,0,*(ulong *)(local_288 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_288,*(ulong *)(local_1b8 + -6));
            puVar3 = local_1b8 + *(long *)(local_1b8 + -6);
            if (local_1b8 != puVar3) {
              iVar9 = 0;
              puVar23 = local_1b8;
              do {
                uVar26 = *puVar23;
                lVar10 = 1;
                uVar8 = (ushort)uVar26;
                if (0xffff < uVar26) {
                  lVar10 = 2;
                  iVar9 = (uVar26 - 0x10000 & 0xffff03ff) - 0x2400;
                  uVar8 = ((ushort)(uVar26 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar13 = *(long *)(local_288 + -0xc);
                uVar21 = lVar13 + 1;
                if ((*(ulong *)(local_288 + -8) < uVar21) || (0 < *(int *)(local_288 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_288,uVar21);
                  lVar13 = *(long *)(local_288 + -0xc);
                }
                local_288[lVar13] = uVar8;
                if (local_288 != &DAT_01426458) {
                  local_288[-4] = 0;
                  local_288[-3] = 0;
                  *(ulong *)(local_288 + -0xc) = uVar21;
                  local_288[uVar21] = 0;
                }
                if (lVar10 == 2) {
                  lVar10 = *(long *)(local_288 + -0xc);
                  uVar21 = lVar10 + 1;
                  if ((*(ulong *)(local_288 + -8) < uVar21) || (0 < *(int *)(local_288 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_288,uVar21);
                    lVar10 = *(long *)(local_288 + -0xc);
                  }
                  local_288[lVar10] = (ushort)iVar9;
                  if (local_288 != &DAT_01426458) {
                    local_288[-4] = 0;
                    local_288[-3] = 0;
                    *(ulong *)(local_288 + -0xc) = uVar21;
                    local_288[uVar21] = 0;
                  }
                }
                puVar23 = puVar23 + 1;
              } while (puVar3 != puVar23);
            }
                    /* try { // try from 008af8af to 008af8b3 has its CatchHandler @ 008b01bc */
            std::wstring::~wstring((wstring_conflict *)&local_1b8);
            local_268 = &DAT_01426458;
            local_250 = 0;
            local_260 = 0;
            local_258 = 0;
                    /* try { // try from 008af8eb to 008af9b1 has its CatchHandler @ 008b0424 */
            uVar21 = Ogre::UTFString::_verifyUTF8((string *)local_158);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_268,0,*(ulong *)(local_268 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_268,uVar21);
            local_1b8._0_7_ = (uint7)(uint6)local_1b8;
            local_54 = 0;
            pbVar30 = local_158[0] + *(long *)(local_158[0] + -0x18);
            for (pbVar24 = local_158[0]; pbVar24 != pbVar30; pbVar24 = pbVar24 + 1) {
              bVar6 = *pbVar24;
              uVar21 = 1;
              if (((((char)bVar6 < '\0') && (uVar21 = 2, (bVar6 & 0xe0) != 0xc0)) &&
                  (uVar21 = 3, (bVar6 & 0xf0) != 0xe0)) &&
                 ((uVar21 = 4, (bVar6 & 0xf8) != 0xf0 && (uVar21 = 5, (bVar6 & 0xfc) != 0xf8)))) {
                if ((bVar6 & 0xfe) != 0xfc) {
                    /* try { // try from 008afcd2 to 008afcd6 has its CatchHandler @ 008b058d */
                  std::string::string(local_1d8,"invalid UTF-8 sequence header value",local_41);
                  prVar18 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 008afcea to 008afcee has its CatchHandler @ 008b0575 */
                  std::runtime_error::runtime_error(prVar18,local_1d8);
                  *(undefined ***)prVar18 = &PTR__invalid_data_00fa4490;
                    /* try { // try from 008afcf9 to 008afcfd has its CatchHandler @ 008b056a */
                  std::string::~string(local_1d8);
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 008afd0b to 008afd0f has its CatchHandler @ 008b0424 */
                  __cxa_throw(prVar18,&Ogre::UTFString::invalid_data::typeinfo,
                              Ogre::UTFString::invalid_data::~invalid_data);
                }
                uVar21 = 6;
              }
              uVar17 = 0;
              do {
                *(byte *)((long)&local_1b8 + uVar17) = pbVar24[uVar17];
                uVar17 = uVar17 + 1;
              } while (uVar17 < uVar21);
              *(undefined1 *)((long)&local_1b8 + uVar21) = 0;
              if ((char)local_1b8._0_1_ < '\0') {
                if (((byte)local_1b8._0_1_ & 0xffffffe0) == 0xc0) {
                  uVar26 = (byte)local_1b8._0_1_ & 0x1f;
                  uVar21 = 2;
                }
                else {
                  uVar26 = (uint)(byte)local_1b8._0_1_;
                  if ((uVar26 & 0xfffffff0) == 0xe0) {
                    uVar26 = uVar26 & 0xf;
                    uVar21 = 3;
                  }
                  else if ((uVar26 & 0xfffffff8) == 0xf0) {
                    uVar26 = uVar26 & 7;
                    uVar21 = 4;
                  }
                  else {
                    uVar26 = (uint)(byte)local_1b8._0_1_;
                    if ((uVar26 & 0xfffffffc) == 0xf8) {
                      uVar26 = uVar26 & 3;
                      uVar21 = 5;
                    }
                    else {
                      if ((uVar26 & 0xfffffffe) != 0xfc) {
                    /* try { // try from 008afd80 to 008afd84 has its CatchHandler @ 008b048d */
                        std::string::string((string *)local_1e8,
                                            "invalid UTF-8 sequence header value",&local_42);
                        prVar18 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 008afd98 to 008afd9c has its CatchHandler @ 008b0429 */
                        std::runtime_error::runtime_error(prVar18,(string *)local_1e8);
                        *(undefined ***)prVar18 = &PTR__invalid_data_00fa4490;
                        if ((allocator *)(local_1e8[0] + -0x18) !=
                            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                          LOCK();
                          piVar1 = (int *)(local_1e8[0] + -8);
                          iVar9 = *piVar1;
                          *piVar1 = *piVar1 + -1;
                          UNLOCK();
                          if (iVar9 < 1) {
                            std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
                          }
                        }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 008afdcb to 008afdcf has its CatchHandler @ 008b0424 */
                        __cxa_throw(prVar18,&Ogre::UTFString::invalid_data::typeinfo,
                                    Ogre::UTFString::invalid_data::~invalid_data);
                      }
                      uVar26 = uVar26 & 1;
                      uVar21 = 6;
                    }
                  }
                }
                uVar17 = 1;
                do {
                  pbVar4 = (byte *)((long)&local_1b8 + uVar17);
                  if ((*pbVar4 & 0xffffffc0) != 0x80) {
                    /* try { // try from 008aff7b to 008aff7f has its CatchHandler @ 008b0392 */
                    std::string::string(local_1c8,"bad UTF-8 continuation byte",local_39);
                    prVar18 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 008aff93 to 008aff97 has its CatchHandler @ 008b0370 */
                    std::runtime_error::runtime_error(prVar18,local_1c8);
                    *(undefined ***)prVar18 = &PTR__invalid_data_00fa4490;
                    /* try { // try from 008affa2 to 008affa6 has its CatchHandler @ 008b03a5 */
                    std::string::~string(local_1c8);
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 008affb4 to 008affb8 has its CatchHandler @ 008b0424 */
                    __cxa_throw(prVar18,&Ogre::UTFString::invalid_data::typeinfo,
                                Ogre::UTFString::invalid_data::~invalid_data);
                  }
                  uVar17 = uVar17 + 1;
                  uVar26 = uVar26 << 6 | *pbVar4 & 0x3f;
                } while (uVar17 < uVar21);
                pbVar24 = pbVar24 + (uVar21 - 1);
                if (uVar26 < 0x10000) goto LAB_008af990;
                local_56 = ((ushort)(uVar26 - 0x10000) & 0x3ff) + 0xdc00;
                local_58 = ((ushort)(uVar26 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                uVar21 = 2;
              }
              else {
                uVar26 = (uint)(byte)local_1b8._0_1_;
LAB_008af990:
                local_58 = (ushort)uVar26;
                uVar21 = 1;
              }
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::append((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        *)&local_268,&local_58,uVar21);
            }
                    /* try { // try from 008af9c8 to 008af9cc has its CatchHandler @ 008b0464 */
            Ogre::UTFString::UTFString((UTFString *)local_2c8,(UTFString *)&local_268);
            uVar21 = *(ulong *)(local_288 + -0xc);
            if (uVar21 != 0) {
              lVar10 = *(long *)(local_2c8[0] + -0xc);
              uVar17 = lVar10 + uVar21;
              if ((*(ulong *)(local_2c8[0] + -8) < uVar17) || (0 < *(int *)(local_2c8[0] + -4))) {
                    /* try { // try from 008af9ff to 008afa56 has its CatchHandler @ 008b0452 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)local_2c8,uVar17);
                lVar10 = *(long *)(local_2c8[0] + -0xc);
              }
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_M_copy(local_2c8[0] + lVar10,local_288,uVar21);
              if (local_2c8[0] != &DAT_01426458) {
                *(undefined4 *)(local_2c8[0] + -4) = 0;
                *(ulong *)(local_2c8[0] + -0xc) = uVar17;
                local_2c8[0][uVar17] = 0;
              }
            }
            Ogre::UTFString::UTFString((UTFString *)&local_2a8,(UTFString *)local_2c8);
                    /* try { // try from 008afa5c to 008afa60 has its CatchHandler @ 008b0464 */
            Ogre::UTFString::~UTFString((UTFString *)local_2c8);
            if (local_2a0 != 2) {
              Ogre::UTFString::_cleanBuffer((UTFString *)&local_2a8);
                    /* try { // try from 008afa79 to 008afc20 has its CatchHandler @ 008b0317 */
              local_290 = operator_new(8);
              *(undefined4 **)local_290 = &DAT_01424558;
              local_2a0 = 2;
            }
            std::wstring::clear();
            pwVar7 = local_290;
            std::wstring::reserve((ulong)local_290);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_2a8);
            psVar2 = local_2a8 + *(long *)(local_2a8 + -0xc);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_2a8);
            if (psVar2 != local_2a8) {
              plVar11 = (long *)(local_2a8 + -0xc);
              psVar25 = local_2a8;
              do {
                if ((-1 < (int)plVar11[2]) &&
                   (plVar11 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if ((int)plVar11[2] != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_2a8,0,0,0);
                    plVar11 = (long *)(local_2a8 + -0xc);
                  }
                  *(undefined4 *)(plVar11 + 2) = 0xffffffff;
                }
                lVar10 = (long)psVar25 - (long)local_2a8 >> 1;
                uVar26 = (ushort)local_2a8[lVar10] + 0x2800;
                if ((((ushort)uVar26 < 0x400) &&
                    (uVar21 = lVar10 + 1, uVar21 < *(ulong *)(local_2a8 + -0xc))) &&
                   ((ushort)(local_2a8[uVar21] + 0x2400U) < 0x400)) {
                  uVar26 = ((ushort)(local_2a8[uVar21] + 0x2400U) & 0x3ff | (uVar26 & 0x3ff) << 10)
                           + 0x10000;
                }
                else {
                  uVar26 = (uint)(ushort)local_2a8[lVar10];
                }
                lVar10 = *(long *)pwVar7;
                lVar13 = *(long *)(lVar10 + -0x18);
                uVar21 = lVar13 + 1;
                if ((*(ulong *)(lVar10 + -0x10) < uVar21) || (0 < *(int *)(lVar10 + -8))) {
                  std::wstring::reserve((ulong)pwVar7);
                  lVar10 = *(long *)pwVar7;
                  lVar13 = *(long *)(lVar10 + -0x18);
                }
                *(uint *)(lVar10 + lVar13 * 4) = uVar26;
                puVar14 = *(undefined4 **)pwVar7;
                if (puVar14 != &DAT_01424558) {
                  puVar14[-2] = 0;
                  *(ulong *)(puVar14 + -6) = uVar21;
                  puVar14[uVar21] = 0;
                }
                plVar11 = (long *)(local_2a8 + -0xc);
                if ((-1 < *(int *)(local_2a8 + -4)) &&
                   (plVar11 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if (*(int *)(local_2a8 + -4) != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_2a8,0,0,0);
                    plVar11 = (long *)(local_2a8 + -0xc);
                  }
                  *(undefined4 *)(plVar11 + 2) = 0xffffffff;
                  plVar11 = (long *)(local_2a8 + -0xc);
                }
                psVar20 = psVar25 + 1;
                if (((psVar20 != local_2a8 + *plVar11) && ((ushort)(psVar25[1] + 0x2400U) < 0x400))
                   && ((ushort)(*psVar25 + 0x2800U) < 0x400)) {
                  psVar20 = psVar25 + 2;
                }
                psVar25 = psVar20;
              } while (psVar20 != psVar2);
            }
                    /* try { // try from 008b02d0 to 008b02d4 has its CatchHandler @ 008b0317 */
            std::wstring::wstring(local_178,local_290);
                    /* try { // try from 008b02e3 to 008b02e7 has its CatchHandler @ 008b0475 */
            std::vector<std::wstring,std::allocator<std::wstring>>::push_back
                      ((vector<std::wstring,std::allocator<std::wstring>> *)
                       (*(long *)(this + 0x1e0) + 0x40),local_178);
                    /* try { // try from 008b02eb to 008b02ef has its CatchHandler @ 008b0317 */
            std::wstring::~wstring(local_178);
                    /* try { // try from 008b02f3 to 008b02f7 has its CatchHandler @ 008b0464 */
            Ogre::UTFString::~UTFString((UTFString *)&local_2a8);
                    /* try { // try from 008b0300 to 008b0304 has its CatchHandler @ 008b046c */
            Ogre::UTFString::~UTFString((UTFString *)&local_268);
                    /* try { // try from 008b030d to 008b0311 has its CatchHandler @ 008b03e8 */
            Ogre::UTFString::~UTFString((UTFString *)&local_288);
          }
                    /* try { // try from 008b0046 to 008b007b has its CatchHandler @ 008b04df */
          std::string::~string((string *)local_158);
          uVar22 = uVar22 + 1;
        } while (uVar22 < *(uint *)(*(long *)(this + 0x1e0) + 0x20));
      }
      std::wstring::wstring(local_1a8,(wstring_conflict *)local_98);
                    /* try { // try from 008b0094 to 008b0098 has its CatchHandler @ 008b0565 */
      std::operator+(local_198,(wchar_t *)local_e8);
                    /* try { // try from 008b00ac to 008b00b0 has its CatchHandler @ 008b054d */
      loadAnimations(this,*(undefined8 *)(this + 0x60),local_198,local_1a8,1);
                    /* try { // try from 008b00b4 to 008b00b8 has its CatchHandler @ 008b0565 */
      std::wstring::~wstring(local_198);
                    /* try { // try from 008b00bc to 008b00c0 has its CatchHandler @ 008b04df */
      std::wstring::~wstring(local_1a8);
      local_208 = 0;
      local_200 = 0;
      local_1f8 = 0;
                    /* try { // try from 008b00fe to 008b0102 has its CatchHandler @ 008b053d */
      std::
      vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
      ::resize((vector<std::vector<CKeyframe*,std::allocator<CKeyframe*>>,std::allocator<std::vector<CKeyframe*,std::allocator<CKeyframe*>>>>
                *)(*(long *)(this + 0x1e0) + 0x58),*(undefined4 *)(*(long *)(this + 0x1e0) + 0x20),
               (vector<CKeyframe*,std::allocator<CKeyframe*>> *)&local_208);
      std::vector<CKeyframe*,std::allocator<CKeyframe*>>::~vector
                ((vector<CKeyframe*,std::allocator<CKeyframe*>> *)&local_208);
    }
                    /* try { // try from 008af019 to 008af444 has its CatchHandler @ 008b05bf */
    std::wstring::~wstring(local_128);
  }
  puVar27 = *(undefined8 **)(this + 0x1d0);
  puVar31 = *(undefined8 **)(this + 0x1c8);
  puVar33 = puVar31;
  if (((long)puVar27 - (long)puVar31 >> 3) * -0x5555555555555555 != 0) {
    uVar21 = 0;
    uVar22 = 0;
    do {
      uVar17 = 0;
      puVar31 = puVar31 + uVar21 * 3;
      puVar33 = (undefined8 *)puVar31[1];
      puVar27 = (undefined8 *)*puVar31;
      puVar28 = puVar27;
      if (((long)puVar33 - (long)puVar27 >> 3) * -0x5555555555555555 != 0) {
        do {
          puVar27 = puVar27 + uVar17 * 3;
          *(undefined4 *)(puVar27 + 1) = 0;
          *(undefined4 *)((long)puVar27 + 0xc) = 0;
          if ((void *)*puVar27 != (void *)0x0) {
            operator_delete__((void *)*puVar27);
          }
          *puVar27 = 0;
          uVar17 = (ulong)((int)uVar17 + 1);
          puVar31 = (undefined8 *)(*(long *)(this + 0x1c8) + uVar21 * 0x18);
          puVar33 = (undefined8 *)puVar31[1];
          puVar27 = (undefined8 *)*puVar31;
          puVar28 = puVar27;
        } while (uVar17 < (ulong)(((long)puVar33 - (long)puVar27 >> 3) * -0x5555555555555555));
      }
      for (; puVar27 != puVar33; puVar27 = puVar27 + 3) {
        if ((void *)*puVar27 != (void *)0x0) {
          operator_delete__((void *)*puVar27);
          *puVar27 = 0;
        }
      }
      puVar31[1] = puVar28;
      uVar22 = uVar22 + 1;
      puVar27 = *(undefined8 **)(this + 0x1d0);
      puVar31 = *(undefined8 **)(this + 0x1c8);
      uVar21 = (ulong)uVar22;
      puVar33 = puVar31;
    } while (uVar21 < (ulong)(((long)puVar27 - (long)puVar31 >> 3) * -0x5555555555555555));
  }
  for (; puVar31 != puVar27; puVar31 = puVar31 + 3) {
    puVar28 = (undefined8 *)puVar31[1];
    for (puVar29 = (undefined8 *)*puVar31; puVar28 != puVar29; puVar29 = puVar29 + 3) {
      if ((void *)*puVar29 != (void *)0x0) {
        operator_delete__((void *)*puVar29);
        *puVar29 = 0;
      }
    }
    if ((void *)*puVar31 != (void *)0x0) {
      operator_delete((void *)*puVar31);
    }
  }
  *(undefined8 **)(this + 0x1d0) = puVar33;
  if (*(long *)(this + 0x1e0) != 0) {
    local_228 = (undefined8 *)0x0;
    local_220 = (undefined8 *)0x0;
    local_218 = 0;
    lVar10 = (long)puVar33 - *(long *)(this + 0x1c8) >> 3;
    lVar13 = *(long *)(*(long *)(this + 0x1e0) + 0x60) - *(long *)(*(long *)(this + 0x1e0) + 0x58)
             >> 3;
    uVar21 = lVar13 * -0x5555555555555555;
    if (uVar21 < (ulong)(lVar10 * -0x5555555555555555)) {
      puVar31 = (undefined8 *)(*(long *)(this + 0x1c8) + lVar13 * 8);
      for (puVar27 = puVar31; puVar33 != puVar27; puVar27 = puVar27 + 3) {
        puVar28 = (undefined8 *)puVar27[1];
        for (puVar29 = (undefined8 *)*puVar27; puVar28 != puVar29; puVar29 = puVar29 + 3) {
          if ((void *)*puVar29 != (void *)0x0) {
            operator_delete__((void *)*puVar29);
            *puVar29 = 0;
          }
        }
        if ((void *)*puVar27 != (void *)0x0) {
          operator_delete((void *)*puVar27);
        }
      }
      *(undefined8 **)(this + 0x1d0) = puVar31;
      puVar31 = local_228;
      puVar27 = local_220;
      puVar33 = local_220;
    }
    else {
                    /* try { // try from 008b0142 to 008b0146 has its CatchHandler @ 008b0297 */
      std::
      vector<std::vector<TArrayList<int>,std::allocator<TArrayList<int>>>,std::allocator<std::vector<TArrayList<int>,std::allocator<TArrayList<int>>>>>
      ::_M_fill_insert((vector<std::vector<TArrayList<int>,std::allocator<TArrayList<int>>>,std::allocator<std::vector<TArrayList<int>,std::allocator<TArrayList<int>>>>>
                        *)(this + 0x1c8),puVar33,uVar21 + lVar10 * 0x5555555555555555);
      puVar31 = local_228;
      puVar27 = local_220;
      puVar33 = local_220;
    }
    for (; puVar28 = local_220, local_220 != puVar31; puVar31 = puVar31 + 3) {
      local_220 = puVar33;
      if ((void *)*puVar31 != (void *)0x0) {
        operator_delete__((void *)*puVar31);
        *puVar31 = 0;
      }
      puVar27 = local_228;
      puVar33 = local_220;
      local_220 = puVar28;
    }
    local_220 = puVar33;
    if (puVar27 != (undefined8 *)0x0) {
      operator_delete(puVar27);
    }
    lVar10 = *(long *)(this + 0x1e0);
    if ((*(long *)(lVar10 + 0x60) - *(long *)(lVar10 + 0x58) >> 3) * -0x5555555555555555 != 0) {
      uVar21 = 0;
      uVar22 = 0;
      do {
        local_248 = (void *)0x0;
        local_240 = 0;
        local_23c = 0;
        local_238 = 10;
        plVar11 = (long *)(*(long *)(lVar10 + 0x58) + uVar21 * 0x18);
        pvVar32 = (vector<TArrayList<int>,std::allocator<TArrayList<int>>> *)
                  (uVar21 * 0x18 + *(long *)(this + 0x1c8));
        puVar31 = *(undefined8 **)(pvVar32 + 8);
        uVar21 = plVar11[1] - *plVar11 >> 3;
        lVar10 = (long)puVar31 - *(long *)pvVar32 >> 3;
        if (uVar21 < (ulong)(lVar10 * -0x5555555555555555)) {
          puVar27 = (undefined8 *)(*(long *)pvVar32 + uVar21 * 0x18);
          for (puVar33 = puVar27; puVar31 != puVar33; puVar33 = puVar33 + 3) {
            if ((void *)*puVar33 != (void *)0x0) {
              operator_delete__((void *)*puVar33);
              *puVar33 = 0;
            }
          }
          *(undefined8 **)(pvVar32 + 8) = puVar27;
        }
        else {
                    /* try { // try from 008af5cc to 008af5d0 has its CatchHandler @ 008b025d */
          std::vector<TArrayList<int>,std::allocator<TArrayList<int>>>::_M_fill_insert
                    (pvVar32,puVar31,uVar21 + lVar10 * 0x5555555555555555,&local_248);
        }
        if (local_248 != (void *)0x0) {
          operator_delete__(local_248);
          local_248 = (void *)0x0;
        }
        lVar10 = *(long *)(this + 0x1e0);
        uVar22 = uVar22 + 1;
        uVar21 = (ulong)uVar22;
      } while (uVar21 < (ulong)((*(long *)(lVar10 + 0x60) - *(long *)(lVar10 + 0x58) >> 3) *
                               -0x5555555555555555));
    }
  }
  if ((*(long *)(this + 0x130) == 0) || (param_4 == '\0')) {
    reInitialize(this,*(Entity **)(this + 0x60),true);
    (**(code **)(*(long *)this + 0x1c8))(this);
    puVar14 = (undefined4 *)(**(code **)(**(long **)(this + 0x60) + 0xd8))();
    if ((puVar14[6] != 0) && (puVar14[6] != 2)) {
      local_2e0 = *puVar14;
      local_2dc = puVar14[1];
      local_2d8 = puVar14[2];
      local_2d4 = puVar14[3];
      local_2d0 = puVar14[4];
      local_2cc = puVar14[5];
    }
    *(undefined4 *)(this + 0x1ec) = local_2e0;
    *(undefined4 *)(this + 0x1f0) = local_2dc;
    *(undefined4 *)(this + 500) = local_2d8;
    *(undefined4 *)(this + 0x1f8) = local_2d4;
    *(undefined4 *)(this + 0x1fc) = local_2d0;
    *(undefined4 *)(this + 0x200) = local_2cc;
                    /* try { // try from 008af4f0 to 008af4f4 has its CatchHandler @ 008b0485 */
    setRenderToLightMap(this,(bool)this[0x239]);
                    /* try { // try from 008af505 to 008af509 has its CatchHandler @ 008b06ba */
    std::wstring::~wstring((wstring_conflict *)local_e8);
                    /* try { // try from 008af512 to 008af516 has its CatchHandler @ 008b0287 */
    std::string::~string((string *)local_a8);
    std::wstring::~wstring((wstring_conflict *)local_98);
    return;
  }
                    /* try { // try from 008b0120 to 008b0124 has its CatchHandler @ 008b06ba */
  std::wstring::~wstring((wstring_conflict *)local_e8);
LAB_008afecc:
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  return;
}



/* address=008b07a0
   symbol=CGenericModel::reloadAnimations */

/* WARNING: Removing unreachable block (ram,0x008b0a99) */
/* WARNING: Removing unreachable block (ram,0x008b0b01) */
/* WARNING: Removing unreachable block (ram,0x008b0a27) */
/* WARNING: Removing unreachable block (ram,0x008b0af6) */
/* WARNING: Removing unreachable block (ram,0x008b0a8e) */
/* CGenericModel::reloadAnimations() */

void __thiscall CGenericModel::reloadAnimations(CGenericModel *this)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  long lVar5;
  long *plVar6;
  undefined8 uVar7;
  uint uVar8;
  Entity *pEVar9;
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];

  clearAnimations(this);
  if (*(long *)(this + 0x1e0) != 0) {
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(this + 0x110));
                    /* try { // try from 008b07e4 to 008b07e8 has its CatchHandler @ 008b0a37 */
    std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(this + 0x118));
                    /* try { // try from 008b07ed to 008b0864 has its CatchHandler @ 008b0a32 */
    lVar5 = Ogre::Entity::getMesh();
    (**(code **)(**(long **)(lVar5 + 8) + 0xb0))();
    pEVar9 = *(Entity **)(this + 0x60);
    plVar6 = *(long **)(pEVar9 + 0x2e8);
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 0x218))(plVar6);
      lVar5 = *(long *)(this + 0x1e0);
      if (*(int *)(lVar5 + 0x20) != 0) {
        uVar8 = 0;
        do {
          while( true ) {
            STRINGS::StringUpper
                      ((STRINGS *)local_68,(string *)((ulong)uVar8 * 8 + *(long *)(lVar5 + 0x28)));
                    /* try { // try from 008b086d to 008b0871 has its CatchHandler @ 008b0a02 */
            iVar4 = std::string::compare((char *)local_68);
            if ((allocator *)(local_68[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_68[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
              }
            }
            if (iVar4 == 0) break;
                    /* try { // try from 008b08a0 to 008b093e has its CatchHandler @ 008b0a32 */
            (**(code **)(*plVar6 + 0x1f0))
                      (plVar6,(ulong)uVar8 * 8 + *(long *)(*(long *)(this + 0x1e0) + 0x28));
            lVar5 = *(long *)(this + 0x1e0);
            uVar8 = uVar8 + 1;
            if (*(uint *)(lVar5 + 0x20) <= uVar8) goto LAB_008b08b5;
          }
          lVar5 = *(long *)(this + 0x1e0);
          uVar8 = uVar8 + 1;
        } while (uVar8 < *(uint *)(lVar5 + 0x20));
      }
LAB_008b08b5:
      (**(code **)(*plVar6 + 0xb0))(plVar6);
      pEVar9 = *(Entity **)(this + 0x60);
    }
    if (pEVar9 != (Entity *)0x0) {
      OGRE_UTILITIES::detachEntityFromParent(pEVar9);
      plVar6 = (long *)Ogre::MeshManager::getSingleton();
      pcVar3 = *(code **)(*plVar6 + 0x88);
      lVar5 = Ogre::Entity::getMesh();
      uVar7 = (**(code **)(**(long **)(lVar5 + 8) + 200))();
      (*pcVar3)(plVar6,uVar7);
      (**(code **)(**(long **)(this + 0x140) + 0x288))
                (*(long **)(this + 0x140),*(undefined8 *)(this + 0x60));
    }
    *(undefined8 *)(this + 0x60) = 0;
    *(undefined8 *)(this + 0x230) = 0;
    unloadModel(this);
    std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)local_58);
                    /* try { // try from 008b094c to 008b0950 has its CatchHandler @ 008b0b24 */
    std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)local_48);
                    /* try { // try from 008b0965 to 008b0969 has its CatchHandler @ 008b0b0c */
    loadModel(this,(wstring_conflict *)local_78,(wstring_conflict *)local_88,0,0,1);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 008b099f to 008b09a1 has its CatchHandler @ 008b0a32 */
    (**(code **)(*(long *)this + 0x40))(this,1);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
  }
  return;
}



/* address=008b0b30
   symbol=CGenericModel::CGenericModel */

/* WARNING: Removing unreachable block (ram,0x008b0fc5) */
/* WARNING: Removing unreachable block (ram,0x008b0fa3) */
/* CGenericModel::CGenericModel(CResourceManager*, Ogre::SceneManager*, std::wstring, std::wstring,
   bool) */

void __thiscall
CGenericModel::CGenericModel
          (CGenericModel *this,CResourceManager *param_1,SceneManager *param_2,
          wstring_conflict *param_4,wstring_conflict *param_5,CGenericModel param_6)

{
  int *piVar1;
  size_t __n;
  int iVar2;
  long local_58 [2];
  long local_48;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,param_2);
  *(undefined ***)this = &PTR__CGenericModel_00fd1470;
  *(undefined ***)(this + 0x100) = &PTR__CGenericModel_00fd1668;
  *(undefined ***)(this + 0x108) = &PTR__CGenericModel_00fd1698;
                    /* try { // try from 008b0b8d to 008b0b91 has its CatchHandler @ 008b0f9e */
  std::wstring::wstring((wstring_conflict *)(this + 0x110),L"",local_39);
                    /* try { // try from 008b0bab to 008b0baf has its CatchHandler @ 008b0fb6 */
  std::wstring::wstring((wstring_conflict *)(this + 0x118),L"",&local_3a);
                    /* try { // try from 008b0bc8 to 008b0bcc has its CatchHandler @ 008b0fb1 */
  std::string::string((string *)(this + 0x120),"",&local_3b);
  *(undefined1 **)(this + 0x128) = &DAT_01423a38;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined8 *)(this + 0x138) = 0;
  *(SceneManager **)(this + 0x140) = param_2;
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  *(undefined4 *)(this + 0x158) = 10;
  *(undefined8 *)(this + 0x160) = 0;
  *(undefined8 *)(this + 0x168) = 0;
  *(undefined8 *)(this + 0x170) = 0;
  *(undefined8 *)(this + 0x178) = 0;
  *(undefined8 *)(this + 0x180) = 0;
  *(undefined8 *)(this + 0x188) = 0;
  *(undefined8 *)(this + 400) = 0;
  *(undefined8 *)(this + 0x198) = 0;
  *(undefined8 *)(this + 0x1a0) = 0;
  *(undefined8 *)(this + 0x1a8) = 0;
                    /* try { // try from 008b0c98 to 008b0c9c has its CatchHandler @ 008b0fbb */
  std::_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>>::_M_initialize_map
            ((_Deque_base<CActiveAnimation*,std::allocator<CActiveAnimation*>> *)(this + 0x160),0);
  *(undefined8 *)(this + 0x1b0) = 0;
  *(undefined8 *)(this + 0x1b8) = 0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined8 *)(this + 0x1e0) = 0;
  this[0x1e8] = (CGenericModel)0x0;
  this[0x1e9] = param_6;
  *(undefined4 *)(this + 0x1ec) = 0;
  *(undefined4 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 500) = 0;
  *(undefined4 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x1fc) = 0;
  *(undefined4 *)(this + 0x200) = 0;
  *(undefined4 *)(this + 0x204) = 2;
  *(undefined8 *)(this + 0x208) = 0;
  *(undefined8 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x218) = 0;
  *(undefined4 *)(this + 0x220) = 1;
  this[0x224] = (CGenericModel)0x0;
  *(undefined4 *)(this + 0x228) = 0x3f800000;
  *(undefined8 *)(this + 0x230) = 0;
  this[0x238] = (CGenericModel)0x0;
  this[0x239] = (CGenericModel)0x0;
  this[0x23b] = (CGenericModel)0x0;
  this[0x23c] = (CGenericModel)0x1;
  *(undefined4 *)(this + 0x240) = 0x3f800000;
  *(undefined4 *)(this + 0x244) = 0;
  *(undefined4 *)(this + 0x248) = 0;
  *(undefined4 *)(this + 0x24c) = 0x3c7c0fc1;
  if (param_1 != (CResourceManager *)0x0) {
    this[0x82] = (CGenericModel)0x1;
    if (*(long *)(this + 0x140) == 0) {
      *(undefined8 *)(this + 0x140) = *(undefined8 *)(*(long *)(this + 0x68) + 0x10);
    }
    __n = *(size_t *)(*(wchar_t **)param_4 + -6);
    if ((__n != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar2 = wmemcmp(*(wchar_t **)param_4,::EMPTY_WSTRING,__n), iVar2 != 0)) {
                    /* try { // try from 008b0e09 to 008b0e0d has its CatchHandler @ 008b0ee7 */
      std::wstring::wstring((wstring_conflict *)&local_48,param_5);
                    /* try { // try from 008b0e19 to 008b0e1d has its CatchHandler @ 008b0f99 */
      std::wstring::wstring((wstring_conflict *)local_58,param_4);
                    /* try { // try from 008b0e2f to 008b0e33 has its CatchHandler @ 008b0f81 */
      loadModel(this,(wstring_conflict *)local_58,(wstring_conflict *)&local_48,0,0,0);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
    }
  }
  return;
}



/* address=008b1000
   symbol=CGenericModel::GetRandomWeight */

/* non-virtual thunk to CGenericModel::GetRandomWeight() */

void __thiscall CGenericModel::GetRandomWeight(CGenericModel *this)

{
  GetRandomWeight(this + -0x100);
  return;
}



/* address=008b1010
   symbol=CGenericModel::GetRandomWeight */

/* CGenericModel::GetRandomWeight() */

undefined4 __thiscall CGenericModel::GetRandomWeight(CGenericModel *this)

{
  return *(undefined4 *)(this + 0x220);
}



/* address=008b1020
   symbol=CGenericModel::SetRandomWeight */

/* non-virtual thunk to CGenericModel::SetRandomWeight(unsigned int) */

void __thiscall CGenericModel::SetRandomWeight(CGenericModel *this,uint param_1)

{
  SetRandomWeight(this + -0x100,param_1);
  return;
}



/* address=008b1030
   symbol=CGenericModel::SetRandomWeight */

/* CGenericModel::SetRandomWeight(unsigned int) */

void __thiscall CGenericModel::SetRandomWeight(CGenericModel *this,uint param_1)

{
  *(uint *)(this + 0x220) = param_1;
  return;
}



/* export-summary functions=81 failures=0 */
