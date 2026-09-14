/* Targeted Ghidra class export.
   namespace=CMissile
   Treat pseudocode as navigation evidence. */


/* address=00cf8ea0
   symbol=CMissile::getCollisionSphereVisible */

/* CMissile::getCollisionSphereVisible() */

undefined8 CMissile::getCollisionSphereVisible(void)

{
  return 0;
}



/* address=00cf8eb0
   symbol=CMissile::setCollisionSphereVisible */

/* CMissile::setCollisionSphereVisible(bool) */

void CMissile::setCollisionSphereVisible(bool param_1)

{
  return;
}



/* address=00cf8ec0
   symbol=CMissile::getAOESphereVisible */

/* CMissile::getAOESphereVisible() */

undefined8 CMissile::getAOESphereVisible(void)

{
  return 0;
}



/* address=00cf8ed0
   symbol=CMissile::setAOESphereVisible */

/* CMissile::setAOESphereVisible(bool) */

void CMissile::setAOESphereVisible(bool param_1)

{
  return;
}



/* address=00cf8ee0
   symbol=CMissile::getRateOFire */

/* CMissile::getRateOFire() */

undefined4 CMissile::getRateOFire(void)

{
  return g_fMissileEditorRefreshRate;
}



/* address=00cf8ef0
   symbol=CMissile::setRateOFire */

/* CMissile::setRateOFire(float) */

void CMissile::setRateOFire(float param_1)

{
  g_fMissileEditorRefreshRate = param_1;
  return;
}



/* address=00cf8f00
   symbol=CMissile::resetMissile */

/* CMissile::resetMissile() */

void __thiscall CMissile::resetMissile(CMissile *this)

{
  undefined4 uVar1;

  this[0x185] = (CMissile)0x0;
  *(undefined4 *)(this + 0x1bc) = 0;
  *(undefined4 *)(this + 0x1c4) = 0;
  *(undefined4 *)(this + 0x1c0) = 0;
  *(undefined4 *)(this + 0x148) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 0x14c) = DAT_014241b0;
  *(undefined4 *)(this + 0x150) = DAT_014241b4;
  *(undefined4 *)(this + 0x1a0) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 0x1a4) = DAT_014241b0;
  uVar1 = DAT_014241b4;
  *(undefined4 *)(this + 0x17c) = 0;
  *(undefined4 *)(this + 0x1a8) = uVar1;
  return;
}



/* address=00cf8f70
   symbol=CMissile::setRadiusOfMissile */

/* CMissile::setRadiusOfMissile(float) */

void __thiscall CMissile::setRadiusOfMissile(CMissile *this,float param_1)

{
  *(float *)(this + 0x178) = param_1;
  return;
}



/* address=00cf8f80
   symbol=CMissile::setAOERadius */

/* CMissile::setAOERadius(float) */

void __thiscall CMissile::setAOERadius(CMissile *this,float param_1)

{
  *(float *)(this + 0x160) = param_1;
  return;
}



/* address=00cf8f90
   symbol=CMissile::placeSphere */

/* CMissile::placeSphere() */

void CMissile::placeSphere(void)

{
  code *pcVar1;
  uint uVar2;
  long *plVar3;
  void *pvVar4;
  undefined8 *puVar5;
  ulong uVar6;
  CPositionableObject *in_RDI;
  int iVar7;
  uint uVar8;
  undefined4 in_XMM1_Da;
  undefined8 local_38;
  undefined4 local_30;

  uVar8 = *(uint *)(in_RDI + 0x208);
  if (*(uint *)(in_RDI + 0x1f8) <= uVar8) {
    iVar7 = 0;
    do {
      plVar3 = (long *)(**(code **)(**(long **)(*(long *)(in_RDI + 0x68) + 0x10) + 0x230))();
      OGRE_UTILITIES::createEntity
                (*(undefined8 *)(*(long *)(in_RDI + 0x68) + 0x10),0,1,&DAT_00faa818);
      (**(code **)(*plVar3 + 0x278))(plVar3);
      in_XMM1_Da = DAT_00fa480c;
      (**(code **)(*plVar3 + 0x108))(DAT_00fa480c,plVar3);
      uVar8 = *(uint *)(in_RDI + 0x1f8);
      if (uVar8 < *(uint *)(in_RDI + 0x1fc)) {
        pvVar4 = *(void **)(in_RDI + 0x1f0);
      }
      else if (*(long *)(in_RDI + 0x1f0) == 0) {
        *(uint *)(in_RDI + 0x1fc) = *(uint *)(in_RDI + 0x200);
        pvVar4 = operator_new__((ulong)*(uint *)(in_RDI + 0x200) << 3);
        *(void **)(in_RDI + 0x1f0) = pvVar4;
        uVar8 = *(uint *)(in_RDI + 0x1f8);
      }
      else {
        uVar8 = *(uint *)(in_RDI + 0x1fc) + *(int *)(in_RDI + 0x200);
        pvVar4 = operator_new__((ulong)uVar8 << 3);
        if (*(int *)(in_RDI + 0x1fc) != 0) {
          uVar2 = 0;
          do {
            uVar6 = (ulong)uVar2;
            uVar2 = uVar2 + 1;
            *(undefined8 *)((long)pvVar4 + uVar6 * 8) =
                 *(undefined8 *)(*(long *)(in_RDI + 0x1f0) + uVar6 * 8);
          } while (uVar2 < *(uint *)(in_RDI + 0x1fc));
        }
        if (*(void **)(in_RDI + 0x1f0) != (void *)0x0) {
          operator_delete__(*(void **)(in_RDI + 0x1f0));
        }
        *(void **)(in_RDI + 0x1f0) = pvVar4;
        *(uint *)(in_RDI + 0x1fc) = uVar8;
        uVar8 = *(uint *)(in_RDI + 0x1f8);
      }
      iVar7 = iVar7 + 1;
      *(long **)((long)pvVar4 + (ulong)uVar8 * 8) = plVar3;
      *(int *)(in_RDI + 0x1f8) = *(int *)(in_RDI + 0x1f8) + 1;
    } while (iVar7 != 10);
    uVar8 = *(uint *)(in_RDI + 0x208);
  }
  if (uVar8 < *(uint *)(in_RDI + 0x1fc)) {
    puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(in_RDI + 0x1f0));
  }
  else {
    puVar5 = *(undefined8 **)(in_RDI + 0x1f0);
  }
  plVar3 = (long *)*puVar5;
  pcVar1 = *(code **)(*plVar3 + 0xe8);
  local_38 = CPositionableObject::getPosition(in_RDI,false);
  local_30 = in_XMM1_Da;
  (*pcVar1)(plVar3,&local_38);
  plVar3 = (long *)(**(code **)(**(long **)(*(long *)(in_RDI + 0x68) + 0x10) + 0x250))();
  if (*(uint *)(in_RDI + 0x208) < *(uint *)(in_RDI + 0x1fc)) {
    puVar5 = (undefined8 *)((ulong)*(uint *)(in_RDI + 0x208) * 8 + *(long *)(in_RDI + 0x1f0));
  }
  else {
    puVar5 = *(undefined8 **)(in_RDI + 0x1f0);
  }
  (**(code **)(*plVar3 + 0x1a8))(plVar3,*puVar5);
  *(int *)(in_RDI + 0x208) = *(int *)(in_RDI + 0x208) + 1;
  return;
}



/* address=00cf91e0
   symbol=CMissile::getClosestTarget */

/* CMissile::getClosestTarget(Ogre::Quaternion const&, Ogre::Vector3 const&) */

undefined8 __thiscall
CMissile::getClosestTarget(CMissile *this,Quaternion *param_1,Vector3 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  CCharacter *this_00;
  undefined8 uVar3;
  float fVar4;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;

  this_00 = (CCharacter *)0x0;
  if (*(long *)(this + 0x220) != 0) {
    this_00 = (CCharacter *)
              __dynamic_cast(*(long *)(this + 0x220),&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
  }
  if ((*(long *)(*(long *)(this + 0x68) + 0x18) == 0) || (this_00 == (CCharacter *)0x0)) {
    uVar3 = 0;
  }
  else {
    Ogre::Quaternion::ToRotationMatrix((Matrix3 *)param_1);
    fVar4 = DAT_00fa47fc + *(float *)(this + 0x1b8);
    uVar1 = *(undefined4 *)(this + 0x260);
    local_68 = DAT_01423ff0;
    local_60 = DAT_01423ff8;
    local_98 = local_58;
    local_94 = local_54;
    local_90 = local_50;
    local_88 = local_4c;
    local_84 = local_48;
    local_80 = local_44;
    local_78 = local_40;
    local_74 = local_3c;
    local_70 = local_38;
    local_8c = *(undefined4 *)param_2;
    local_7c = *(undefined4 *)(param_2 + 4);
    local_6c = *(undefined4 *)(param_2 + 8);
    uVar2 = CCharacter::getTargetAlignment(this_00);
    uVar3 = CLevel::findCharacterWithinView
                      ((CLevel *)0x0,uVar1,fVar4,*(undefined8 *)(*(long *)(this + 0x68) + 0x18),
                       &local_98,uVar2,1,0,0);
  }
  return uVar3;
}



/* address=00cf9350
   symbol=CMissile::removeArchFromMissile */

/* CMissile::removeArchFromMissile(float) */

void CMissile::removeArchFromMissile(float param_1)

{
  undefined8 uVar1;
  CPositionableObject *in_RDI;
  float fVar2;
  float extraout_XMM0_Db;
  undefined8 local_18;

  if (((*(long *)(in_RDI + 0x210) != 0) && (0.0 < *(float *)(in_RDI + 0x19c))) &&
     (0.0 < *(float *)(in_RDI + 0x198))) {
    local_18 = CPositionableObject::getPosition(in_RDI,true);
    if (*(float *)(in_RDI + 0x218) < DAT_00fa47fc) {
      CPath::GetSplinePositionAtDistance
                (*(CPath **)(in_RDI + 0x210),
                 *(float *)(in_RDI + 0x218) * *(float *)(*(CPath **)(in_RDI + 0x210) + 0x18));
      fVar2 = extraout_XMM0_Db;
      uVar1 = local_18;
    }
    else {
      fVar2 = (float)(*(uint *)(in_RDI + 0x158) ^ DAT_00fa8780) * param_1;
      uVar1 = local_18;
    }
    local_18._4_4_ = (float)((ulong)uVar1 >> 0x20);
    local_18._0_4_ = (undefined4)uVar1;
    local_18 = CONCAT44(local_18._4_4_ - fVar2,(undefined4)local_18);
    CPositionableObject::setPosition(in_RDI,(Vector3 *)&local_18);
    return;
  }
  return;
}



/* address=00cf9450
   symbol=CMissile::addArchFromMissile */

/* CMissile::addArchFromMissile(float) */

void __thiscall CMissile::addArchFromMissile(CMissile *this,float param_1)

{
  float fVar1;
  undefined8 uVar2;
  float fVar3;
  float fVar4;
  undefined4 local_38;
  float fStack_34;
  float local_30;
  undefined8 local_28;
  float local_20;
  undefined8 local_18;
  float local_10;

  fVar4 = DAT_00fa47fc;
  if (((*(long *)(this + 0x210) != 0) && (fVar3 = 0.0, 0.0 < *(float *)(this + 0x19c))) &&
     (fVar1 = *(float *)(this + 0x198), 0.0 < fVar1)) {
    if (this[0x186] == (CMissile)0x0) {
      fVar1 = *(float *)(this + 0x1b8);
    }
    fVar1 = *(float *)(this + 0x1bc) / fVar1;
    *(float *)(this + 0x218) = fVar1;
    if (fVar4 <= fVar1) {
      if (fVar4 < fVar1) {
        *(float *)(this + 0x218) = fVar4;
      }
      else {
        fVar4 = fVar3;
        if (0.0 <= fVar1) {
          fVar4 = fVar1;
          fVar3 = fVar1;
        }
      }
      *(float *)(this + 0x218) = fVar4;
      local_18 = CPath::GetSplinePositionAtDistance
                           (*(CPath **)(this + 0x210),*(float *)(*(CPath **)(this + 0x210) + 0x18));
      fVar4 = (float)(*(uint *)(this + 0x158) ^ DAT_00fa8780) * param_1 +
              (float)((ulong)local_18 >> 0x20);
      local_10 = fVar3;
    }
    else {
      if (fVar4 < fVar1) {
        *(float *)(this + 0x218) = fVar4;
      }
      else {
        fVar4 = fVar3;
        if (0.0 <= fVar1) {
          fVar4 = fVar1;
        }
        *(float *)(this + 0x218) = fVar1;
        fVar3 = fVar4;
      }
      *(float *)(this + 0x218) = fVar4;
      local_28 = CPath::GetSplinePositionAtDistance
                           (*(CPath **)(this + 0x210),
                            fVar4 * *(float *)(*(CPath **)(this + 0x210) + 0x18));
      fVar4 = (float)((ulong)local_28 >> 0x20);
      local_20 = fVar3;
    }
    uVar2 = CPositionableObject::getPosition((CPositionableObject *)this,true);
    _local_38 = CONCAT44(fVar4 + (float)((ulong)uVar2 >> 0x20),(int)uVar2);
    local_30 = fVar3;
    CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)&local_38);
  }
  return;
}



/* address=00cf9620
   symbol=CMissile::doDamageToCharacter */

/* CMissile::doDamageToCharacter(CCharacter*, Ogre::Vector3 const&, float, float) */

undefined8 __thiscall
CMissile::doDamageToCharacter
          (CMissile *this,CCharacter *param_1,Vector3 *param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  char cVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  CGraph *this_00;
  uint uVar8;
  ulong uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined8 local_48;
  float local_40;

  if (param_1 == (CCharacter *)0x0) {
    uVar5 = *(uint *)(this + 0x1d0);
  }
  else {
    uVar9 = 0;
    if (*(int *)(this + 0x1d0) == 0) goto LAB_00cf96be;
    do {
      if ((uint)uVar9 < *(uint *)(this + 0x1d4)) {
        puVar7 = (undefined8 *)(uVar9 * 8 + *(long *)(this + 0x1c8));
      }
      else {
        puVar7 = *(undefined8 **)(this + 0x1c8);
      }
      uVar6 = (**(code **)(*(long *)*puVar7 + 0x28))((long *)*puVar7,this,param_1);
      if ((char)uVar6 == '\0') {
        return uVar6;
      }
      uVar5 = *(uint *)(this + 0x1d0);
      uVar8 = (uint)uVar9 + 1;
      uVar9 = (ulong)uVar8;
    } while (uVar8 < uVar5);
  }
  uVar8 = 0;
  bVar3 = true;
  if (uVar5 != 0) {
    do {
      if (uVar8 < *(uint *)(this + 0x1d4)) {
        puVar7 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x1c8));
      }
      else {
        puVar7 = *(undefined8 **)(this + 0x1c8);
      }
      cVar4 = (**(code **)(*(long *)*puVar7 + 0x20))
                        (param_3 * *(float *)(this + 0x290),param_4,(long *)*puVar7,this,param_1,
                         param_2);
      if (cVar4 != '\0') {
        bVar3 = false;
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x1d0));
    if (!bVar3) {
      return 1;
    }
  }
LAB_00cf96be:
  uVar5 = *(uint *)(param_1 + 0x100);
  this_00 = (CGraph *)CResourceManager::getGraphDamage(*(CResourceManager **)(this + 0x68));
  fVar10 = (float)CGraph::getValue(this_00,(float)uVar5,0);
  fVar11 = (float)UTILITIES::randomBetweenVolatile
                            (*(float *)(this + 0x284),*(float *)(this + 0x288));
  fVar1 = *(float *)(this + 0x28c);
  fVar2 = *(float *)(this + 0x290);
  fVar12 = fVar1;
  local_48 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  local_40 = fVar12;
  CCharacter::applyDamage
            (param_1,*(CLevel **)(*(long *)(this + 0x68) + 0x18),(Vector3 *)&local_48,
             fVar10 * fVar11 * fVar2,param_2,fVar1,(CCharacter *)0x0,false,true,true,false,0x200);
  return 1;
}



/* address=00cf9840
   symbol=CMissile::handleDeathOfMissile */

/* CMissile::handleDeathOfMissile(float) */

undefined8 __thiscall CMissile::handleDeathOfMissile(CMissile *this,float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  long *plVar4;
  undefined8 *puVar5;
  uint uVar6;
  long lVar7;

  fVar2 = DAT_00fa47f8;
  fVar1 = *(float *)(this + 0x1b4);
  *(float *)(this + 0x1b4) = fVar1 - param_1;
  if (fVar2 < fVar1 - param_1) {
    return 1;
  }
  lVar7 = 0;
  do {
    if (*(CParticle **)(this + lVar7 + 0x100) != (CParticle *)0x0) {
      CParticle::Stop(*(CParticle **)(this + lVar7 + 0x100),false);
      iVar3 = CParticle::getNumberOfParticlesUpdating(*(CParticle **)(this + lVar7 + 0x100),true);
      if (iVar3 != 0) {
        return 1;
      }
      (**(code **)(**(long **)(this + lVar7 + 0x100) + 0x50))();
    }
    lVar7 = lVar7 + 8;
  } while (lVar7 != 0x20);
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d4) = 0;
  if (*(void **)(this + 0x1c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1c8));
  }
  *(undefined8 *)(this + 0x1c8) = 0;
  if (*(int *)(this + 0x1f8) != 0) {
    uVar6 = 0;
    do {
      lVar7 = Ogre::SceneNode::getParentSceneNode();
      if (lVar7 != 0) {
        plVar4 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x68) + 0x10) + 0x250))();
        if (uVar6 < *(uint *)(this + 0x1fc)) {
          puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x1f0));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x1f0);
        }
        (**(code **)(*plVar4 + 0x1e0))(plVar4,*puVar5);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x1f8));
  }
  return 0;
}



/* address=00cf99a0
   symbol=CMissile::getParticleFile */

/* CMissile::getParticleFile(EMISSILE_PARTICLES) */

wstring_conflict * CMissile::getParticleFile(wstring_conflict *param_1,long param_2,int param_3)

{
  if (*(long *)(param_2 + 0x100 + (long)param_3 * 8) != 0) {
    std::wstring::wstring(param_1,(wstring_conflict *)(param_2 + 0x120 + (long)param_3 * 8));
    return param_1;
  }
  std::wstring::wstring(param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}



/* address=00d00570
   symbol=CMissile::_GLOBAL__I_CMissile */

/* CMissile::CMissile(CResourceManager*) */

void CMissile::_GLOBAL__I_CMissile(void)

{
  allocator aStack_27e;
  allocator aStack_27d;
  allocator aStack_27c;
  allocator aStack_27b;
  allocator aStack_27a;
  allocator aStack_279;
  allocator aStack_278;
  allocator aStack_277;
  allocator aStack_276;
  allocator aStack_275;
  allocator aStack_274;
  allocator aStack_273;
  allocator aStack_272;
  allocator aStack_271;
  allocator aStack_270;
  allocator aStack_26f;
  allocator aStack_26e;
  allocator aStack_26d;
  allocator aStack_26c;
  allocator aStack_26b;
  allocator aStack_26a;
  allocator aStack_269;
  allocator aStack_268;
  allocator aStack_267;
  allocator aStack_266;
  allocator aStack_265;
  allocator aStack_264;
  allocator aStack_263;
  allocator aStack_262;
  allocator aStack_261;
  allocator aStack_260;
  allocator aStack_25f;
  allocator aStack_25e;
  allocator aStack_25d;
  allocator aStack_25c;
  allocator aStack_25b;
  allocator aStack_25a;
  allocator aStack_259;
  allocator aStack_258;
  allocator aStack_257;
  allocator aStack_256;
  allocator aStack_255;
  allocator aStack_254;
  allocator aStack_253;
  allocator aStack_252;
  allocator aStack_251;
  allocator aStack_250;
  allocator aStack_24f;
  allocator aStack_24e;
  allocator aStack_24d;
  allocator aStack_24c;
  allocator aStack_24b;
  allocator aStack_24a;
  allocator aStack_249;
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
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_27e);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_27d);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_27c);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_27b);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_278);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_277);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_276);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_275);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_272);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_270)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_26f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_26d);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_26a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_268)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_263);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_25e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_25c);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_25a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_259);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_258);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_257);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_256);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_255);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_254);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_253);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_252);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_251);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_250);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_24f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_24e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_24d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_24c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_248);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1e7);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1db)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1d9)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1d8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1d7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1d6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1d5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1d4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1ce);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1c8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1c6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1c4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1b8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1b5
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1b2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1b0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1af)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1ad);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1a6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1a5);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_19e);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_197);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_190);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)&DAT_014f88e8,L"ITEM",&aStack_18e);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_18a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_184);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_183);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_a1);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_9d);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_97);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_94);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_8e);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_8d);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_8c);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_8b
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_8a);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_89);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_88);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_87);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_86);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_85);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_84);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_83);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_82);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_81);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_80);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_7f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_7e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_7d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_7c);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_7b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_7a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_79);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_78);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_77);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_76);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_75);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_74);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_73);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_72);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_71);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_70);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_6f);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_6e);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_6d);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_6c);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_6b);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_6a);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_69);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_68);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_67);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_66);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_65);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_64);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_5f);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_5a);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_54
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_4d);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_4c
            );
  std::wstring::wstring((wstring_conflict *)&DAT_014f9398,L"Add",&aStack_4b);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_4a);
  std::wstring::wstring((wstring_conflict *)&DAT_014f93a8,L"Texture",&aStack_49);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_46);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_45);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_44);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_3b);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_37);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_32);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_30)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_2e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_2a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_27);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_23)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_1e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_1d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_10);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_f);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_9);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  return;
}



/* address=00d00580
   symbol=CMissile::setTarget */

/* CMissile::setTarget(CPositionableObject*) */

void __thiscall CMissile::setTarget(CMissile *this,CPositionableObject *param_1)

{
  CRunicCore *this_00;
  undefined4 uVar1;
  CRunicCore *pCVar2;

  pCVar2 = *(CRunicCore **)(this + 0x230);
  if (param_1 != (CPositionableObject *)pCVar2) {
    if (pCVar2 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(pCVar2,(TSafePointer *)(this + 0x230),*(uint *)(this + 0x238));
    }
    *(undefined8 *)(this + 0x230) = 0;
    if (param_1 != (CPositionableObject *)0x0) {
      uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x230));
      *(undefined4 *)(this + 0x238) = uVar1;
    }
    *(CPositionableObject **)(this + 0x230) = param_1;
  }
  pCVar2 = (CRunicCore *)0x0;
  if (param_1 != (CPositionableObject *)0x0) {
    pCVar2 = (CRunicCore *)
             __dynamic_cast(param_1,&CPositionableObject::typeinfo,&CCharacter::typeinfo,0);
  }
  this_00 = *(CRunicCore **)(this + 0x240);
  if (pCVar2 != this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x240),*(uint *)(this + 0x248));
    }
    *(undefined8 *)(this + 0x240) = 0;
    if (pCVar2 != (CRunicCore *)0x0) {
      uVar1 = CRunicCore::addSafePointer(pCVar2,(TSafePointer *)(this + 0x240));
      *(undefined4 *)(this + 0x248) = uVar1;
    }
    *(CRunicCore **)(this + 0x240) = pCVar2;
  }
  return;
}



/* address=00d00650
   symbol=CMissile::initialize */

/* CMissile::initialize() */

void __thiscall CMissile::initialize(CMissile *this)

{
  undefined4 uVar1;

  this[0x294] = (CMissile)0x0;
  *(undefined4 *)(this + 0x290) = 0x3f800000;
  if (*(CRunicCore **)(this + 0x240) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x240),(TSafePointer *)(this + 0x240),*(uint *)(this + 0x248)
              );
    *(undefined8 *)(this + 0x240) = 0;
  }
  *(undefined4 *)(this + 0x274) = 0;
  *(undefined4 *)(this + 0x170) = 0;
  *(undefined4 *)(this + 0x218) = 0;
  *(undefined4 *)(this + 0x198) = 0;
  *(undefined4 *)(this + 600) = 0;
  *(undefined4 *)(this + 0x19c) = 0;
  *(undefined4 *)(this + 0x254) = 0;
  this[0x186] = (CMissile)0x0;
  this[0x187] = (CMissile)0x1;
  this[0x188] = (CMissile)0x0;
  *(undefined4 *)(this + 0x260) = 0x42f00000;
  *(undefined4 *)(this + 0x174) = 0;
  *(undefined4 *)(this + 0x25c) = 0;
  *(undefined4 *)(this + 0x264) = 0;
  *(undefined4 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x27c) = 0x3f800000;
  *(undefined4 *)(this + 0x280) = 0x3f800000;
  *(undefined4 *)(this + 0x26c) = 0;
  *(undefined4 *)(this + 0x270) = 0x3e800000;
  *(undefined4 *)(this + 0x18c) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 400) = DAT_014241b0;
  uVar1 = DAT_014241b4;
  *(undefined4 *)(this + 0x250) = 0;
  *(undefined4 *)(this + 0x194) = uVar1;
  if (*(CRunicCore **)(this + 0x230) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x230),(TSafePointer *)(this + 0x230),*(uint *)(this + 0x238)
              );
    *(undefined8 *)(this + 0x230) = 0;
  }
  *(undefined4 *)(this + 0x164) = 0;
  *(undefined4 *)(this + 0x16c) = 0;
  *(undefined4 *)(this + 0x168) = 0x42480000;
  *(undefined4 *)(this + 0x1b8) = 0x41c80000;
  *(undefined4 *)(this + 0x1bc) = 0;
  *(undefined4 *)(this + 0x1c4) = 0;
  *(undefined4 *)(this + 0x1c0) = 0;
  this[0x185] = (CMissile)0x0;
  *(undefined4 *)(this + 0x1b4) = 0x4479c000;
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x1b0) = 0;
  *(undefined4 *)(this + 0x148) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 0x14c) = DAT_014241b0;
  *(undefined4 *)(this + 0x150) = DAT_014241b4;
  *(undefined4 *)(this + 0x1a0) = Ogre::Vector3::ZERO;
  *(undefined4 *)(this + 0x1a4) = DAT_014241b0;
  uVar1 = DAT_014241b4;
  *(undefined4 *)(this + 0x154) = 0;
  *(undefined4 *)(this + 0x158) = 0x3f800000;
  this[0x140] = (CMissile)0x1;
  *(undefined4 *)(this + 0x180) = 0;
  *(undefined4 *)(this + 0x1a8) = uVar1;
  *(undefined4 *)(this + 0x17c) = 0;
  *(undefined4 *)(this + 0x178) = 0x3e4ccccd;
  *(undefined4 *)(this + 0x15c) = 0x3f800000;
  this[0x141] = (CMissile)0x0;
  this[0x184] = (CMissile)0x0;
  *(undefined4 *)(this + 0x284) = 0;
  *(undefined4 *)(this + 0x288) = 0;
  *(undefined4 *)(this + 0x28c) = 0;
  if (*(CRunicCore **)(this + 0x220) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x220),(TSafePointer *)(this + 0x220),*(uint *)(this + 0x228)
              );
    *(undefined8 *)(this + 0x220) = 0;
  }
  *(undefined4 *)(this + 0x1ac) = 0x40400000;
  *(undefined8 *)(this + 0x100) = 0;
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined8 *)(this + 0x118) = 0;
  (**(code **)(*(long *)this + 0x50))(this,1);
  *(undefined4 *)(this + 0x160) = 0;
  return;
}



/* address=00d00c20
   symbol=CMissile::doAOEDamage */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMissile::doAOEDamage(CBaseUnit*) */

void CMissile::doAOEDamage(CBaseUnit *param_1)

{
  int iVar1;
  long *plVar2;
  long in_RSI;
  uint uVar3;
  ulong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  float in_XMM1_Da;
  float fVar7;
  float local_48;
  float local_44;
  float local_40;
  undefined8 local_38 [3];

  if ((doAOEDamage(CBaseUnit*)::mCharacterList == '\0') &&
     (iVar1 = __cxa_guard_acquire(&doAOEDamage(CBaseUnit*)::mCharacterList), iVar1 != 0)) {
    doAOEDamage(CBaseUnit*)::mCharacterList = (void *)0x0;
    DAT_014f9648 = 0;
    DAT_014f964c = 0;
    _DAT_014f9650 = 0x19;
    __cxa_guard_release(&doAOEDamage(CBaseUnit*)::mCharacterList);
    __cxa_atexit(TArrayList<CCharacter*>::~TArrayList,&doAOEDamage(CBaseUnit*)::mCharacterList,
                 &__dso_handle);
  }
  if ((doAOEDamage(CBaseUnit*)::mItemList == '\0') &&
     (iVar1 = __cxa_guard_acquire(&doAOEDamage(CBaseUnit*)::mItemList), iVar1 != 0)) {
    doAOEDamage(CBaseUnit*)::mItemList = (void *)0x0;
    DAT_014f9628 = 0;
    DAT_014f962c = 0;
    _DAT_014f9630 = 0x19;
    __cxa_guard_release(&doAOEDamage(CBaseUnit*)::mItemList);
    __cxa_atexit(TArrayList<CItem*>::~TArrayList,&doAOEDamage(CBaseUnit*)::mItemList,&__dso_handle);
  }
  DAT_014f9648 = 0;
  DAT_014f964c = 0;
  if (doAOEDamage(CBaseUnit*)::mCharacterList != (void *)0x0) {
    operator_delete__(doAOEDamage(CBaseUnit*)::mCharacterList);
  }
  doAOEDamage(CBaseUnit*)::mCharacterList = (long *)0x0;
  DAT_014f9628 = 0;
  DAT_014f962c = 0;
  if (doAOEDamage(CBaseUnit*)::mItemList != (void *)0x0) {
    operator_delete__(doAOEDamage(CBaseUnit*)::mItemList);
  }
  doAOEDamage(CBaseUnit*)::mItemList = (long *)0x0;
  fVar7 = *(float *)(param_1 + 0x160);
  if (DAT_00fa47f8 < fVar7) {
    local_38[0] = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    CLevel::getActiveUnitsAtPosition
              (*(Vector3 **)(*(long *)(param_1 + 0x68) + 0x18),fVar7,(TArrayList *)local_38,
               (TArrayList *)&doAOEDamage(CBaseUnit*)::mCharacterList);
    if (DAT_014f9648 != 0) {
      uVar4 = 0;
      do {
        uVar3 = (uint)uVar4;
        plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList;
        if (uVar3 < DAT_014f964c) {
          plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList + uVar4;
        }
        if (*plVar2 != *(long *)(param_1 + 0x220)) {
          plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList;
          if (uVar3 < DAT_014f964c) {
            plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList + uVar4;
          }
          if (*plVar2 != in_RSI) {
            uVar5 = CPositionableObject::getPosition((CPositionableObject *)param_1,false);
            plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList;
            if (uVar3 < DAT_014f964c) {
              plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList + uVar4;
            }
            fVar7 = in_XMM1_Da;
            uVar6 = CPositionableObject::getPosition((CPositionableObject *)*plVar2,true);
            local_44 = (float)((ulong)uVar6 >> 0x20) - (float)((ulong)uVar5 >> 0x20);
            local_48 = (float)uVar6 - (float)uVar5;
            local_40 = fVar7 - in_XMM1_Da;
            fVar7 = SQRT(local_48 * local_48 + local_44 * local_44 + local_40 * local_40);
            if (DAT_00fa87a0 < (double)fVar7) {
              fVar7 = DAT_00fa47fc / fVar7;
              local_48 = local_48 * fVar7;
              local_44 = local_44 * fVar7;
              local_40 = fVar7 * local_40;
            }
            in_XMM1_Da = *(float *)(param_1 + 0x280);
            plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList;
            if (uVar3 < DAT_014f964c) {
              plVar2 = doAOEDamage(CBaseUnit*)::mCharacterList + uVar4;
            }
            doDamageToCharacter((CMissile *)param_1,(CCharacter *)*plVar2,(Vector3 *)&local_48,
                                *(float *)(param_1 + 0x27c),in_XMM1_Da);
          }
        }
        uVar4 = (ulong)(uVar3 + 1);
      } while (uVar3 + 1 < DAT_014f9648);
    }
    if (DAT_014f9628 != 0) {
      uVar3 = 0;
      do {
        plVar2 = doAOEDamage(CBaseUnit*)::mItemList;
        if (uVar3 < DAT_014f962c) {
          plVar2 = doAOEDamage(CBaseUnit*)::mItemList + uVar3;
        }
        if (*plVar2 != *(long *)(param_1 + 0x220)) {
          plVar2 = doAOEDamage(CBaseUnit*)::mItemList;
          if (uVar3 < DAT_014f962c) {
            plVar2 = doAOEDamage(CBaseUnit*)::mItemList + uVar3;
          }
          if (*plVar2 != in_RSI) {
            plVar2 = doAOEDamage(CBaseUnit*)::mItemList;
            if (uVar3 < DAT_014f962c) {
              plVar2 = doAOEDamage(CBaseUnit*)::mItemList + uVar3;
            }
            (**(code **)(*(long *)*plVar2 + 0x280))((long *)*plVar2,0);
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < DAT_014f9628);
    }
  }
  return;
}



/* address=00d01090
   symbol=CMissile::calculateLaunchOrientation */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMissile::calculateLaunchOrientation(Ogre::Vector3 const&, Ogre::Vector3 const&) */

void __thiscall
CMissile::calculateLaunchOrientation(CMissile *this,Vector3 *param_1,Vector3 *param_2)

{
  undefined8 uVar1;
  long lVar2;
  CPath *pCVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  Vector3 local_a8 [16];
  Vector3 local_98 [16];
  undefined4 local_88;
  float fStack_84;
  float local_80;
  undefined4 local_78;
  float fStack_74;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  undefined4 local_50;
  float local_48;
  float fStack_44;
  float local_40;
  string local_38 [8];
  uint local_30;
  allocator local_29 [9];

  uVar1 = *(undefined8 *)param_2;
  fVar4 = *(float *)(param_1 + 4);
  local_40 = *(float *)(param_1 + 8);
  fVar7 = *(float *)param_1;
  fVar5 = *(float *)(param_2 + 8);
  local_48 = (float)uVar1;
  *(float *)(this + 0x18c) = local_48;
  fVar7 = local_48 - fVar7;
  fStack_44 = (float)((ulong)uVar1 >> 0x20);
  *(float *)(this + 400) = fStack_44;
  *(float *)(this + 0x194) = fVar5;
  local_40 = fVar5 - local_40;
  fVar6 = SQRT(local_48 * local_48 + fVar4 * fVar4 + fVar5 * fVar5) * DAT_00fce520;
  fVar5 = fStack_44 - fVar4;
  if (fVar6 <= fStack_44 - fVar4) {
    fVar5 = fVar6;
  }
  if (fVar5 <= (float)((uint)fVar6 ^ DAT_00fa8780)) {
    fVar5 = (float)((uint)fVar6 ^ DAT_00fa8780);
  }
  fVar4 = (fVar5 + fVar4) - fVar4;
  _local_48 = CONCAT44(fVar4,fVar7);
  fVar5 = SQRT(fVar7 * fVar7 + fVar4 * fVar4 + local_40 * local_40);
  if (DAT_00fa87a0 < (double)fVar5) {
    fVar5 = DAT_00fa47fc / fVar5;
    local_40 = local_40 * fVar5;
    _local_48 = CONCAT44(fVar4 * fVar5,fVar7 * fVar5);
  }
  local_58 = _UNIT_Y;
  local_50 = DAT_01424b3c;
  (**(code **)(*(long *)this + 0x128))(this,&local_48,&local_58);
  *(float *)(this + 0x198) =
       SQRT((*(float *)param_1 - *(float *)param_2) * (*(float *)param_1 - *(float *)param_2) +
            (*(float *)(param_1 + 4) - *(float *)(param_2 + 4)) *
            (*(float *)(param_1 + 4) - *(float *)(param_2 + 4)) +
            (*(float *)(param_1 + 8) - *(float *)(param_2 + 8)) *
            (*(float *)(param_1 + 8) - *(float *)(param_2 + 8)));
  if (0.0 < *(float *)(this + 0x19c)) {
    local_68 = *(undefined8 *)(this + 0x18c);
    local_60 = *(float *)(this + 0x194);
    lVar2 = *(long *)(this + 0x68);
    if ((*(int *)(lVar2 + 0x30) != 0) && (**(long **)(lVar2 + 0x28) != 0)) {
      fStack_74 = (float)((ulong)local_68 >> 0x20);
      fVar4 = fStack_74;
      local_78 = (undefined4)local_68;
      _local_78 = CONCAT44(fStack_74 + DAT_00fa483c,local_78);
      _local_88 = CONCAT44(fVar4 - DAT_00fa483c,local_78);
      local_80 = local_60;
      local_70 = local_60;
      CLevel::rayCollision
                (*(CLevel **)(lVar2 + 0x18),(Vector3 *)&local_78,(Vector3 *)&local_88,
                 (Vector3 *)&local_68,local_98,&local_30,local_a8,false);
    }
    pCVar3 = *(CPath **)(this + 0x210);
    if (pCVar3 == (CPath *)0x0) {
                    /* try { // try from 00d01410 to 00d01414 has its CatchHandler @ 00d0146d */
      std::string::string(local_38,"",local_29);
      local_b8 = 0;
      local_b4 = 0;
      local_b0 = 0;
                    /* try { // try from 00d01438 to 00d0143c has its CatchHandler @ 00d0148d */
      pCVar3 = (CPath *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d0144d to 00d01451 has its CatchHandler @ 00d01478 */
      CPath::CPath(pCVar3,local_38,0,&local_b8);
      *(CPath **)(this + 0x210) = pCVar3;
                    /* try { // try from 00d0145c to 00d01460 has its CatchHandler @ 00d0146d */
      std::string::~string(local_38);
      pCVar3 = *(CPath **)(this + 0x210);
    }
    CPath::Clear(pCVar3);
    CPath::AddPoint(*(CPath **)(this + 0x210),param_1,DAT_00fce4d4,DAT_00fa8778);
    local_c8 = (*(float *)param_1 + (float)local_68) * DAT_00fa4810 + 0.0;
    local_c4 = (*(float *)(param_1 + 4) + local_68._4_4_) * DAT_00fa4810 + *(float *)(this + 0x19c);
    local_c0 = (*(float *)(param_1 + 8) + local_60) * DAT_00fa4810 + 0.0;
    CPath::AddPoint(*(CPath **)(this + 0x210),(Vector3 *)&local_c8,DAT_00fce4d4,DAT_00fa8778);
    CPath::AddPoint(*(CPath **)(this + 0x210),(Vector3 *)&local_68,DAT_00fce4d4,DAT_00fa8778);
    *(undefined4 *)(this + 0x218) = 0;
  }
  return;
}



/* address=00d014a0
   symbol=CMissile::killMissile */

/* CMissile::killMissile() */

void CMissile::killMissile(void)

{
  undefined8 *puVar1;
  uint uVar2;
  CPositionableObject *in_RDI;
  undefined8 uVar3;
  undefined4 local_28;
  float fStack_24;

  in_RDI[0x184] = (CPositionableObject)0x1;
  *(undefined4 *)(in_RDI + 0x1b4) = 0x3f800000;
  if (*(long *)(in_RDI + 0x118) != 0) {
    uVar3 = CPositionableObject::getPosition(in_RDI,true);
    _local_28 = CONCAT44((float)((ulong)uVar3 >> 0x20) - *(float *)(in_RDI + 0x16c),(int)uVar3);
    CPositionableObject::setPosition(*(CPositionableObject **)(in_RDI + 0x118),(Vector3 *)&local_28)
    ;
    CParticle::Start();
  }
  if (*(int *)(in_RDI + 0x1d0) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(in_RDI + 0x1d4)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(in_RDI + 0x1c8));
      }
      else {
        puVar1 = *(undefined8 **)(in_RDI + 0x1c8);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x18))();
    } while (uVar2 < *(uint *)(in_RDI + 0x1d0));
  }
  return;
}



/* address=00d01580
   symbol=CMissile::ricochetMissile */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMissile::ricochetMissile(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3 const&,
   Ogre::Vector3 const&) */

undefined1  [16]
CMissile::ricochetMissile(Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4)

{
  float *in_R8;
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  float fVar9;
  undefined1 auVar10 [16];
  undefined8 local_58;
  undefined4 local_50;
  undefined8 local_48;
  float local_40;
  undefined4 local_38;
  float fStack_34;

  dVar8 = DAT_00fa87a0;
  if (*(long *)(param_1 + 0x110) != 0) {
    uVar3 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    fStack_34 = (float)((ulong)uVar3 >> 0x20);
    _local_38 = CONCAT44(fStack_34 - *(float *)(param_1 + 0x16c),(int)uVar3);
    CPositionableObject::setPosition
              (*(CPositionableObject **)(param_1 + 0x110),(Vector3 *)&local_38);
    dVar8 = DAT_00fa87a0;
    if (param_4 != (Vector3 *)0x0) {
      uVar3 = *(undefined8 *)param_4;
      local_40 = *(float *)(param_4 + 8);
      local_48._0_4_ = (float)uVar3;
      local_48._4_4_ = (float)((ulong)uVar3 >> 0x20);
      fVar1 = SQRT((float)local_48 * (float)local_48 + local_48._4_4_ * local_48._4_4_ +
                   local_40 * local_40);
      if (DAT_00fa87a0 < (double)fVar1) {
        fVar1 = DAT_00fa47fc / fVar1;
        local_40 = fVar1 * local_40;
        local_48 = CONCAT44(local_48._4_4_ * fVar1,(float)local_48 * fVar1);
        uVar3 = local_48;
      }
      local_48 = uVar3;
      local_58 = _UNIT_Y;
      local_50 = DAT_01424b3c;
      (**(code **)(**(long **)(param_1 + 0x110) + 0x128))
                (*(long **)(param_1 + 0x110),&local_48,&local_58);
    }
    CParticle::Start();
  }
  *(int *)(param_1 + 0x17c) = *(int *)(param_1 + 0x17c) + 1;
  fVar1 = in_R8[1];
  fVar5 = *in_R8;
  fVar4 = in_R8[2];
  fVar2 = SQRT(fVar5 * fVar5 + fVar1 * fVar1 + fVar4 * fVar4);
  if (dVar8 < (double)fVar2) {
    fVar2 = DAT_00fa47fc / fVar2;
    fVar5 = fVar5 * fVar2;
    fVar1 = fVar1 * fVar2;
    fVar4 = fVar4 * fVar2;
  }
  fVar2 = *(float *)(param_1 + 0x148) * fVar5 + *(float *)(param_1 + 0x14c) * fVar1 +
          *(float *)(param_1 + 0x150) * fVar4;
  fVar7 = *(float *)(param_1 + 0x148) - (fVar2 * fVar5 + fVar2 * fVar5);
  *(float *)(param_1 + 0x148) = fVar7;
  fVar6 = *(float *)(param_1 + 0x14c) - (fVar2 * fVar1 + fVar2 * fVar1);
  fVar2 = *(float *)(param_1 + 0x150) - (fVar2 * fVar4 + fVar2 * fVar4);
  *(float *)(param_1 + 0x14c) = fVar6;
  *(float *)(param_1 + 0x150) = fVar2;
  if ((in_R8[1] == 0.0) && (!NAN(in_R8[1]))) {
    *(undefined4 *)(param_1 + 0x14c) = 0;
    fVar6 = SQRT(fVar6 * fVar6 + fVar7 * fVar7 + fVar2 * fVar2);
    fVar9 = SQRT(fVar7 * fVar7 + 0.0 + fVar2 * fVar2);
    if (dVar8 < (double)fVar9) {
      fVar9 = DAT_00fa47fc / fVar9;
      fVar7 = *(float *)(param_1 + 0x148) * fVar9;
      *(float *)(param_1 + 0x148) = fVar7;
      *(float *)(param_1 + 0x14c) = fVar9 * 0.0;
      *(float *)(param_1 + 0x150) = fVar2 * fVar9;
    }
    *(float *)(param_1 + 0x148) = fVar7 * fVar6;
    *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) * fVar6;
    *(float *)(param_1 + 0x150) = fVar6 * *(float *)(param_1 + 0x150);
  }
  fVar2 = DAT_00fc67e8 + *(float *)(param_1 + 0x178);
  auVar10._8_4_ = fVar4 * fVar2 + *(float *)(param_4 + 8);
  auVar10._4_4_ = fVar1 * fVar2 + *(float *)(param_4 + 4);
  auVar10._0_4_ = fVar5 * fVar2 + *(float *)param_4;
  auVar10._12_4_ = 0;
  return auVar10;
}



/* address=00d02720
   symbol=CMissile::updatePositionByVelocity */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMissile::updatePositionByVelocity(float) */

undefined1  [16] __thiscall CMissile::updatePositionByVelocity(CMissile *this,float param_1)

{
  long lVar1;
  CPath *this_00;
  char cVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  CPositionableObject *pCVar6;
  long lVar7;
  float fVar8;
  undefined8 uVar9;
  float fVar10;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auVar18 [16];
  float local_e4;
  float local_e0;
  float local_dc;
  undefined8 local_c8;
  ulong local_c0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;
  undefined8 local_38;
  undefined4 local_30;
  undefined8 local_28;
  float local_20;
  ulong uVar11;

  pfVar5 = (float *)(**(code **)(*(long *)this + 0x130))();
  fVar14 = *(float *)(this + 0x154);
  fVar8 = *pfVar5;
  local_20 = pfVar5[1] * fVar14 * param_1 + *(float *)(this + 0x14c);
  *(float *)(this + 0x150) = pfVar5[2] * fVar14 * param_1 + *(float *)(this + 0x150);
  *(float *)(this + 0x14c) = local_20;
  *(float *)(this + 0x148) = fVar14 * fVar8 * param_1 + *(float *)(this + 0x148);
  uVar9 = (**(code **)(*(long *)this + 0x138))(this);
  fVar14 = *(float *)(this + 0x154);
  local_28._4_4_ = (float)((ulong)uVar9 >> 0x20);
  local_28._0_4_ = (float)uVar9;
  fVar10 = local_28._4_4_ * fVar14 * param_1 + *(float *)(this + 0x14c);
  fVar8 = local_20 * fVar14 * param_1 + *(float *)(this + 0x150);
  fVar12 = fVar14 * (float)local_28 * param_1 + *(float *)(this + 0x148);
  *(float *)(this + 0x14c) = fVar10;
  *(float *)(this + 0x150) = fVar8;
  *(float *)(this + 0x148) = fVar12;
  fVar14 = SQRT(fVar12 * fVar12 + fVar10 * fVar10 + fVar8 * fVar8);
  if (DAT_00fa87a0 < (double)fVar14) {
    fVar15 = DAT_00fa47fc / fVar14;
    fVar10 = fVar10 * fVar15;
    *(float *)(this + 0x148) = fVar12 * fVar15;
    *(float *)(this + 0x14c) = fVar10;
    *(float *)(this + 0x150) = fVar8 * fVar15;
  }
  uVar11 = (ulong)(uint)fVar10;
  fVar8 = *(float *)(this + 600) - param_1;
  *(float *)(this + 600) = fVar8;
  local_28 = uVar9;
  if (*(CCharacter **)(this + 0x240) != (CCharacter *)0x0) {
    cVar2 = CCharacter::alive(*(CCharacter **)(this + 0x240));
    if (cVar2 == '\0') {
LAB_00d02930:
      local_38 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_30 = (undefined4)uVar11;
      local_c8 = (**(code **)(*(long *)this + 0xf0))(this);
      local_c0 = uVar11;
      pCVar6 = (CPositionableObject *)
               getClosestTarget(this,(Quaternion *)&local_c8,(Vector3 *)&local_38);
      setTarget(this,pCVar6);
    }
    else if (*(uint *)(this + 0x2a0) != 0) {
      lVar7 = 0;
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x2a4)) {
          lVar1 = *(long *)(lVar7 + *(long *)(this + 0x298));
        }
        else {
          lVar1 = **(long **)(this + 0x298);
        }
        if (lVar1 == *(long *)(this + 0x240)) goto LAB_00d02930;
        uVar3 = uVar3 + 1;
        lVar7 = lVar7 + 8;
      } while (uVar3 < *(uint *)(this + 0x2a0));
    }
    fVar8 = *(float *)(this + 600);
  }
  if ((((fVar8 <= DAT_00fa47f8) && (!NAN(fVar8) && !NAN(DAT_00fa47f8))) &&
      (*(long *)(this + 0x230) != 0)) && (DAT_00fa47f8 < *(float *)(this + 0x250))) {
    fVar8 = param_1 + *(float *)(this + 0x25c);
    *(float *)(this + 0x25c) = fVar8;
    while (fVar10 = (float)uVar11, _DAT_00ff6858 <= fVar8) {
      *(float *)(this + 0x25c) = fVar8 - _DAT_00ff6858;
      uVar9 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x230),true);
      local_98._4_4_ = (float)((ulong)uVar9 >> 0x20);
      fVar15 = *(float *)(this + 0x178) + *(float *)(this + 0x178) + local_98._4_4_;
      local_98 = uVar9;
      local_90 = fVar10;
      uVar9 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_48._4_4_ = (float)((ulong)uVar9 >> 0x20);
      fVar15 = fVar15 - local_48._4_4_;
      local_48._0_4_ = (float)uVar9;
      local_48._0_4_ = (float)local_98 - (float)local_48;
      fVar12 = local_90 - fVar10;
      fVar16 = SQRT((float)local_48 * (float)local_48 + fVar15 * fVar15 + fVar12 * fVar12);
      fVar8 = 1.0;
      if (DAT_00fa87a0 < (double)fVar16) {
        fVar16 = DAT_00fa47fc / fVar16;
        local_48._0_4_ = (float)local_48 * fVar16;
        fVar15 = fVar15 * fVar16;
        fVar12 = fVar12 * fVar16;
        fVar8 = DAT_00fa47fc;
      }
      fVar16 = *(float *)(this + 0x250);
      fVar17 = fVar8 - fVar16;
      fVar13 = fVar15 * fVar16 + *(float *)(this + 0x14c) * fVar17;
      fVar15 = (float)local_48 * fVar16 + *(float *)(this + 0x148) * fVar17;
      *(float *)(this + 0x14c) = fVar13;
      *(float *)(this + 0x148) = fVar15;
      fVar12 = fVar12 * fVar16 + fVar17 * *(float *)(this + 0x150);
      *(float *)(this + 0x150) = fVar12;
      fVar16 = SQRT(fVar15 * fVar15 + fVar13 * fVar13 + fVar12 * fVar12);
      if (DAT_00fa87a0 < (double)fVar16) {
        fVar8 = fVar8 / fVar16;
        fVar15 = fVar15 * fVar8;
        *(float *)(this + 0x148) = fVar15;
        *(float *)(this + 0x14c) = fVar13 * fVar8;
        *(float *)(this + 0x150) = fVar12 * fVar8;
      }
      uVar11 = (ulong)(uint)fVar15;
      local_48 = uVar9;
      local_40 = fVar10;
      fVar8 = *(float *)(this + 0x25c);
    }
  }
  fVar10 = param_1 + *(float *)(this + 0x278);
  fVar8 = param_1 * *(float *)(this + 0x268) + *(float *)(this + 0x274);
  *(float *)(this + 0x278) = fVar10;
  *(float *)(this + 0x274) = fVar8;
  if (*(float *)(this + 0x270) <= fVar10 && fVar10 != *(float *)(this + 0x270)) {
    fVar10 = (float)UTILITIES::randomBetweenVolatile
                              ((float)(DAT_00fa8780 ^ (uint)*(float *)(this + 0x26c)),
                               *(float *)(this + 0x26c));
    *(undefined4 *)(this + 0x278) = 0;
    fVar8 = fVar8 + fVar10;
    *(float *)(this + 0x274) = fVar8;
  }
  fVar10 = *(float *)(this + 0x264);
  if ((float)(DAT_00fa8790 & (uint)fVar10) < (float)((uint)fVar8 & DAT_00fa8790)) {
    if (fVar8 < 0.0) {
      fVar10 = (float)((uint)fVar10 ^ DAT_00fa8780);
    }
    *(float *)(this + 0x274) = fVar10;
    fVar8 = fVar10;
  }
  MATH::rotateY((Vector3 *)(this + 0x148),(float)((double)(fVar8 * param_1) * _DAT_00fc4588));
  uVar9 = *(undefined8 *)(this + 0x148);
  fVar14 = fVar14 * *(float *)(this + 0x15c);
  local_90 = *(float *)(this + 0x150);
  local_98._0_4_ = (float)uVar9;
  local_98._4_4_ = (float)((ulong)uVar9 >> 0x20);
  fVar8 = SQRT((float)local_98 * (float)local_98 + local_98._4_4_ * local_98._4_4_ +
               local_90 * local_90);
  if (DAT_00fa87a0 < (double)fVar8) {
    fVar8 = DAT_00fa47fc / fVar8;
    local_90 = fVar8 * local_90;
    local_98 = CONCAT44(local_98._4_4_ * fVar8,(float)local_98 * fVar8);
    uVar9 = local_98;
  }
  local_98 = uVar9;
  local_a8 = _UNIT_Y;
  local_a0 = DAT_01424b3c;
  (**(code **)(*(long *)this + 0x128))(this,&local_98,&local_a8);
  *(float *)(this + 0x148) = *(float *)(this + 0x148) * fVar14;
  local_e4 = fVar14 * *(float *)(this + 0x150);
  *(float *)(this + 0x14c) = *(float *)(this + 0x14c) * fVar14;
  *(float *)(this + 0x150) = local_e4;
  uVar9 = CPositionableObject::getPosition((CPositionableObject *)this,true);
  local_58._4_4_ = (float)((ulong)uVar9 >> 0x20);
  local_58._0_4_ = (float)uVar9;
  local_58 = uVar9;
  local_50 = local_e4;
  if ((*(long *)(this + 0x210) == 0) || (*(float *)(this + 0x19c) <= DAT_00fa47f8)) {
    local_dc = local_58._4_4_ + param_1 * *(float *)(this + 0x14c);
    local_e0 = (float)local_58 + param_1 * *(float *)(this + 0x148);
    local_e4 = local_e4 + param_1 * *(float *)(this + 0x150);
    if (*(long *)(this + 0x108) != 0) {
      uVar9 = *(undefined8 *)(this + 0x148);
      local_90 = *(float *)(this + 0x150);
      local_98._0_4_ = (float)uVar9;
      local_98._4_4_ = (float)((ulong)uVar9 >> 0x20);
      fVar14 = SQRT((float)local_98 * (float)local_98 + local_98._4_4_ * local_98._4_4_ +
                    local_90 * local_90);
      if (DAT_00fa87a0 < (double)fVar14) {
        fVar14 = DAT_00fa47fc / fVar14;
        local_90 = fVar14 * local_90;
        local_98 = CONCAT44(local_98._4_4_ * fVar14,(float)local_98 * fVar14);
        uVar9 = local_98;
      }
      local_98 = uVar9;
      local_a8 = _UNIT_Y;
      local_a0 = DAT_01424b3c;
      (**(code **)(**(long **)(this + 0x108) + 0x128))(*(long **)(this + 0x108),&local_98,&local_a8)
      ;
    }
  }
  else {
    local_e4 = SQRT(*(float *)(this + 0x148) * *(float *)(this + 0x148) +
                    *(float *)(this + 0x14c) * *(float *)(this + 0x14c) +
                    *(float *)(this + 0x150) * *(float *)(this + 0x150)) * param_1 +
               *(float *)(this + 0x1c4);
    *(float *)(this + 0x1c4) = local_e4;
    fVar14 = *(float *)(*(CPath **)(this + 0x210) + 0x18);
    if (local_e4 <= fVar14) {
      fVar14 = local_e4;
    }
    *(float *)(this + 0x1c4) = fVar14;
    uVar9 = CPath::GetSplinePositionAtDistance(*(CPath **)(this + 0x210),fVar14);
    this_00 = *(CPath **)(this + 0x210);
    local_68._0_4_ = (float)uVar9;
    local_68._4_4_ = (float)((ulong)uVar9 >> 0x20);
    local_e0 = (float)local_68;
    local_dc = local_68._4_4_;
    fVar14 = *(float *)(this_00 + 0x18);
    if (fVar14 <= *(float *)(this + 0x1c4)) {
      *(undefined4 *)(this + 0x1c0) = *(undefined4 *)(this + 0x1b8);
      *(undefined4 *)(this + 0x1bc) = *(undefined4 *)(this + 0x198);
      fVar14 = *(float *)(this_00 + 0x18);
    }
    fVar8 = *(float *)(this + 0x1c4) + DAT_00fc67e8;
    if (fVar8 <= fVar14) {
      fVar14 = fVar8;
    }
    fVar8 = 0.0;
    if (0.0 <= fVar14 - DAT_00fce500) {
      fVar8 = fVar14 - DAT_00fce500;
    }
    local_68 = uVar9;
    local_60 = local_e4;
    local_88 = CPath::GetSplinePositionAtDistance(this_00,fVar8);
    local_80 = fVar8;
    uVar9 = CPath::GetSplinePositionAtDistance(*(CPath **)(this + 0x210),fVar14);
    local_78._4_4_ = (float)((ulong)uVar9 >> 0x20);
    local_78._0_4_ = (float)uVar9;
    local_78._4_4_ = local_78._4_4_ - local_88._4_4_;
    local_78._0_4_ = (float)local_78 - (float)local_88;
    local_a0 = fVar8 - local_80;
    local_a8 = CONCAT44(local_78._4_4_,(float)local_78);
    fVar14 = SQRT((float)local_78 * (float)local_78 + local_78._4_4_ * local_78._4_4_ +
                  local_a0 * local_a0);
    if (DAT_00fa87a0 < (double)fVar14) {
      fVar14 = DAT_00fa47fc / fVar14;
      local_a0 = local_a0 * fVar14;
      local_a8 = CONCAT44(local_78._4_4_ * fVar14,(float)local_78 * fVar14);
    }
    local_78 = uVar9;
    local_70 = fVar8;
    if (*(long *)(this + 0x108) != 0) {
      local_98 = _UNIT_Y;
      local_90 = DAT_01424b3c;
      (**(code **)(**(long **)(this + 0x108) + 0x128))(*(long **)(this + 0x108),&local_a8,&local_98)
      ;
    }
  }
  uVar3 = KSETTINGS_SHOW_MISSILE_TRAILS;
  lVar7 = CMasterResourceManager::getSingleton();
  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar7 + 0x90),uVar3);
  if ((iVar4 == 1) &&
     (DAT_00fa47fc <
      SQRT((local_e0 - *(float *)(this + 0x1e0)) * (local_e0 - *(float *)(this + 0x1e0)) +
           (local_dc - *(float *)(this + 0x1e4)) * (local_dc - *(float *)(this + 0x1e4)) +
           (local_e4 - *(float *)(this + 0x1e8)) * (local_e4 - *(float *)(this + 0x1e8))))) {
    *(float *)(this + 0x1e0) = local_e0;
    *(float *)(this + 0x1e4) = local_dc;
    *(float *)(this + 0x1e8) = local_e4;
    placeSphere();
  }
  auVar18._4_4_ = local_dc;
  auVar18._0_4_ = local_e0;
  auVar18._8_4_ = local_e4;
  auVar18._12_4_ = 0;
  return auVar18;
}



/* address=00d032b0
   symbol=CMissile::setParticleFile */

/* WARNING: Removing unreachable block (ram,0x00d03493) */
/* WARNING: Removing unreachable block (ram,0x00d034b1) */
/* CMissile::setParticleFile(EMISSILE_PARTICLES, std::wstring) */

void __thiscall CMissile::setParticleFile(CMissile *this,int param_2,wstring_conflict *param_3)

{
  int *piVar1;
  size_t __n;
  wchar_t *pwVar2;
  CResourceManager *pCVar3;
  int iVar4;
  long lVar5;
  CParticle *this_00;
  long lVar6;
  long local_48 [2];
  long local_38 [3];

  if (*(long *)(*(long *)param_3 + -0x18) == 0) {
    lVar6 = (long)param_2 + 0x20;
    if (*(long **)(this + lVar6 * 8) != (long *)0x0) {
      (**(code **)(**(long **)(this + lVar6 * 8) + 8))();
      *(undefined8 *)(this + lVar6 * 8) = 0;
    }
    std::wstring::assign((wstring_conflict *)(this + (long)param_2 * 8 + 0x120));
  }
  else {
    STRINGS::StringUpper((STRINGS *)local_38,param_3);
                    /* try { // try from 00d03346 to 00d0334a has its CatchHandler @ 00d0349e */
    std::wstring::assign(param_3);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    lVar6 = (long)param_2;
    __n = *(size_t *)(*(wchar_t **)param_3 + -6);
    if ((__n != *(size_t *)(*(wchar_t **)(this + lVar6 * 8 + 0x120) + -6)) ||
       (iVar4 = wmemcmp(*(wchar_t **)param_3,*(wchar_t **)(this + lVar6 * 8 + 0x120),__n),
       iVar4 != 0)) {
      if (*(long **)(this + (lVar6 + 0x20) * 8) != (long *)0x0) {
        (**(code **)(**(long **)(this + (lVar6 + 0x20) * 8) + 8))();
        *(undefined8 *)(this + (lVar6 + 0x20) * 8) = 0;
      }
      std::wstring::assign((wstring_conflict *)(this + lVar6 * 8 + 0x120));
      std::wstring::wstring((wstring_conflict *)local_48,param_3);
                    /* try { // try from 00d033b6 to 00d033c9 has its CatchHandler @ 00d03480 */
      lVar5 = CMasterResourceManager::getSingleton();
      CParticlePreloader::LoadParticle(*(CParticlePreloader **)(lVar5 + 0xf8),local_48);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      pwVar2 = *(wchar_t **)param_3;
      pCVar3 = *(CResourceManager **)(this + 0x68);
      lVar5 = CMasterResourceManager::getSingleton();
      this_00 = (CParticle *)
                CParticlePreloader::GetParticle
                          (*(CParticlePreloader **)(lVar5 + 0xf8),pCVar3,pwVar2);
      *(CParticle **)(this + lVar6 * 8 + 0x100) = this_00;
      if (this_00 != (CParticle *)0x0) {
        CParticle::Stop(this_00,false);
      }
    }
  }
  return;
}



/* address=00d034c0
   symbol=CMissile::handleMissileHitUnit */

/* CMissile::handleMissileHitUnit(CBaseUnit*, Ogre::Vector3) */

undefined8
CMissile::handleMissileHitUnit(float param_1_00,float param_2,CMissile *param_1,CCharacter *param_4)

{
  code *pcVar1;
  char cVar2;
  undefined8 *puVar3;
  uint *puVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float local_64;
  float local_60;
  float local_5c;
  undefined8 local_48;
  float local_40;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_28;
  uint local_24;
  uint local_20;

  if (param_4 != (CCharacter *)0x0) {
    local_5c = 0.0;
    fVar6 = SQRT(param_1_00 * param_1_00 + 0.0 + param_2 * param_2);
    local_64 = param_1_00;
    local_60 = param_2;
    if (DAT_00fa87a0 < (double)fVar6) {
      fVar6 = DAT_00fa47fc / fVar6;
      local_64 = param_1_00 * fVar6;
      local_5c = fVar6 * 0.0;
      local_60 = fVar6 * param_2;
    }
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_4,0x20);
    if (cVar2 != '\0') {
      return 1;
    }
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_4,2);
    if (cVar2 == '\0') {
      if (*(int *)(param_1 + 0x1d0) != 0) {
        uVar5 = 0;
        do {
          if (uVar5 < *(uint *)(param_1 + 0x1d4)) {
            puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(param_1 + 0x1c8));
          }
          else {
            puVar3 = *(undefined8 **)(param_1 + 0x1c8);
          }
          cVar2 = (**(code **)(*(long *)*puVar3 + 0x28))((long *)*puVar3,param_1,param_4);
          if (cVar2 == '\0') goto LAB_00d03620;
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(param_1 + 0x1d0));
      }
      fVar6 = (float)CCharacter::getDmgToReflectFromMissile(param_4);
      if (0.0 < fVar6) {
        *(float *)(param_1 + 0x290) = fVar6;
        param_1[0x294] = (CMissile)0x1;
        pcVar1 = *(code **)(*(long *)param_1 + 0x148);
        puVar4 = (uint *)(**(code **)(*(long *)param_1 + 0x130))(param_1);
        uVar5 = DAT_00fa8780;
        local_24 = puVar4[1] ^ DAT_00fa8780;
        local_28 = *puVar4 ^ DAT_00fa8780;
        local_20 = puVar4[2] ^ DAT_00fa8780;
        (*pcVar1)(param_1,&local_28);
        pcVar1 = *(code **)(*(long *)param_1 + 0x170);
        puVar4 = (uint *)(**(code **)(*(long *)param_1 + 0x158))(param_1);
        local_34 = puVar4[1] ^ uVar5;
        local_38 = *puVar4 ^ uVar5;
        local_30 = puVar4[2] ^ uVar5;
        (*pcVar1)(param_1);
        setTarget(param_1,(CPositionableObject *)0x0);
        *(undefined4 *)(param_1 + 0x1c4) = 0;
        *(undefined4 *)(param_1 + 0x1bc) = 0;
        *(undefined4 *)(param_1 + 0x1c0) = 0;
        *(uint *)(param_1 + 0x148) = *(uint *)(param_1 + 0x148) ^ uVar5;
        *(uint *)(param_1 + 0x14c) = *(uint *)(param_1 + 0x14c) ^ uVar5;
        *(uint *)(param_1 + 0x150) = *(uint *)(param_1 + 0x150) ^ uVar5;
        return 0;
      }
LAB_00d03620:
      fVar6 = *(float *)(param_1 + 0x150);
      local_48._0_4_ = (float)*(undefined8 *)(param_1 + 0x148);
      fVar8 = 0.0;
      fVar7 = SQRT((float)local_48 * (float)local_48 + 0.0 + fVar6 * fVar6);
      if (DAT_00fa87a0 < (double)fVar7) {
        fVar7 = DAT_00fa47fc / fVar7;
        fVar8 = fVar7 * 0.0;
        local_48._0_4_ = (float)local_48 * fVar7;
        fVar6 = fVar6 * fVar7;
      }
      local_64 = (float)local_48 + (float)local_48 + local_64;
      local_5c = fVar8 + fVar8 + local_5c;
      local_40 = fVar6 + fVar6 + local_60;
      local_48 = CONCAT44(local_5c,local_64);
      fVar6 = SQRT(local_64 * local_64 + local_5c * local_5c + local_40 * local_40);
      if (DAT_00fa87a0 < (double)fVar6) {
        fVar6 = DAT_00fa47fc / fVar6;
        local_40 = local_40 * fVar6;
        local_48 = CONCAT44(local_5c * fVar6,local_64 * fVar6);
      }
      cVar2 = doDamageToCharacter(param_1,param_4,(Vector3 *)&local_48,DAT_00fa47fc,
                                  *(float *)(param_1 + 0x280));
    }
    else {
      cVar2 = (**(code **)(*(long *)param_4 + 0x280))(param_4,0);
    }
    if (cVar2 != '\0') {
      doAOEDamage((CBaseUnit *)param_1);
      return 1;
    }
  }
  return 0;
}



/* address=00d038a0
   symbol=CMissile::checkCollision */

/* CMissile::checkCollision(Ogre::Vector3, Ogre::Vector3, Ogre::Vector3&, Ogre::Vector3&,
   Ogre::Vector3&, CBaseUnit**) */

undefined4
CMissile::checkCollision
          (undefined8 param_1,double param_2,undefined8 param_3,undefined4 param_4,
          CBaseUnit *param_5,Vector3 *param_6,Vector3 *param_7,Vector3 *param_8,undefined8 *param_9)

{
  float fVar1;
  CRunicCore *this;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  long *plVar6;
  undefined1 *puVar7;
  long lVar8;
  CRunicCore CVar9;
  float fVar10;
  undefined8 uVar11;
  float fVar12;
  undefined4 local_c8;
  float fStack_c4;
  undefined4 local_c0;
  undefined8 local_b8;
  float local_b0;
  CRunicCore *local_a8;
  uint local_a0;
  undefined8 local_98;
  float local_90;
  float local_88;
  float fStack_84;
  float local_80;
  undefined8 local_78;
  float local_70;
  Vector3 local_68 [16];
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  CBaseUnit *local_48;
  uint local_3c [3];

  fStack_c4 = (float)((ulong)param_3 >> 0x20);
  local_c8 = (undefined4)param_3;
  local_b0 = SUB84(param_2,0);
  local_48 = (CBaseUnit *)0x0;
  if ((param_5[0x142] != (CBaseUnit)0x0) && (*(int *)(param_5 + 0x2a0) != 0)) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(param_5 + 700)) {
        puVar7 = (undefined1 *)((ulong)uVar3 + *(long *)(param_5 + 0x2b0));
        if (*(uint *)(param_5 + 0x2a4) <= uVar3) goto LAB_00d0391f;
LAB_00d03973:
        plVar6 = (long *)((ulong)uVar3 * 8 + *(long *)(param_5 + 0x298));
      }
      else {
        puVar7 = *(undefined1 **)(param_5 + 0x2b0);
        if (uVar3 < *(uint *)(param_5 + 0x2a4)) goto LAB_00d03973;
LAB_00d0391f:
        plVar6 = *(long **)(param_5 + 0x298);
      }
      *puVar7 = *(undefined1 *)(*plVar6 + 0x18d);
      if (uVar3 < *(uint *)(param_5 + 0x2a4)) {
        plVar6 = (long *)((ulong)uVar3 * 8 + *(long *)(param_5 + 0x298));
      }
      else {
        plVar6 = *(long **)(param_5 + 0x298);
      }
      uVar3 = uVar3 + 1;
      *(undefined1 *)(*plVar6 + 0x18d) = 0;
    } while (uVar3 < *(uint *)(param_5 + 0x2a0));
  }
  local_a8 = (CRunicCore *)0x0;
  local_a0 = 0xffffffff;
  CVar9 = (CRunicCore)0x0;
  this = *(CRunicCore **)(param_5 + 0x220);
  local_c0 = param_4;
  local_b8 = param_1;
  if (this != (CRunicCore *)0x0) {
    CVar9 = this[0x18d];
                    /* try { // try from 00d039bc to 00d03bb5 has its CatchHandler @ 00d04100 */
    local_a0 = CRunicCore::addSafePointer(this,(TSafePointer *)&local_a8);
    local_a8 = this;
    if (param_5[0x144] == (CBaseUnit)0x0) {
      *(undefined1 *)(*(long *)(param_5 + 0x220) + 0x18d) = 0;
    }
    else {
      *(undefined1 *)(*(long *)(param_5 + 0x220) + 0x18d) = 1;
    }
  }
  local_b8 = CONCAT44(local_b8._4_4_ + *(float *)(param_5 + 0x170),(float)local_b8);
  fStack_c4 = fStack_c4 + *(float *)(param_5 + 0x170);
  *(undefined4 *)param_6 = local_c8;
  *(float *)(param_6 + 4) = fStack_c4;
  *(undefined4 *)(param_6 + 8) = local_c0;
  CLevel::sortForCollisionByPoints
            (*(CLevel **)(*(long *)(param_5 + 0x68) + 0x18),(Vector3 *)&local_b8,
             (Vector3 *)&local_c8,*(float *)(param_5 + 0x178));
  uVar4 = CLevel::preSortedSphereCollision
                    (*(CLevel **)(*(long *)(param_5 + 0x68) + 0x18),(Vector3 *)&local_b8,
                     (Vector3 *)&local_c8,*(float *)(param_5 + 0x178),(Vector3 *)&local_58,param_7,
                     param_8,local_3c,local_68,&local_48,(bool)param_5[0x187]);
  if (local_3c[0] == 100) {
    fVar12 = *(float *)param_8;
    fVar1 = *(float *)(param_8 + 8);
    *(undefined4 *)(param_8 + 4) = 0;
    fVar10 = SQRT(fVar12 * fVar12 + 0.0 + fVar1 * fVar1);
    param_2 = (double)fVar10;
    if (DAT_00fa87a0 < param_2) {
      fVar10 = DAT_00fa47fc / fVar10;
      param_2 = (double)(ulong)(uint)(fVar10 * fVar1);
      *(float *)param_8 = fVar12 * fVar10;
      *(float *)(param_8 + 4) = fVar10 * 0.0;
      *(float *)(param_8 + 8) = fVar10 * fVar1;
    }
  }
  fVar12 = SUB84(param_2,0);
  if ((((param_5[0x142] != (CBaseUnit)0x0) && (local_48 != (CBaseUnit *)0x0)) &&
      (cVar2 = CBaseUnit::ISA(local_48,0x19), cVar2 == '\0')) &&
     (cVar2 = CBaseUnit::ISA(local_48,0x1d), cVar2 == '\0')) {
    local_48 = (CBaseUnit *)0x0;
  }
  if ((char)uVar4 == '\0') {
LAB_00d03c30:
    *(float *)(param_6 + 4) = *(float *)(param_6 + 4) - *(float *)(param_5 + 0x170);
  }
  else {
    if (local_48 != (CBaseUnit *)0x0) {
      if ((param_5[0x144] == (CBaseUnit)0x0) &&
         (local_48 == (CBaseUnit *)*(CPositionableObject **)(param_5 + 0x220))) goto LAB_00d03c30;
      uVar11 = CPositionableObject::getPosition((CPositionableObject *)local_48,true);
      local_78._4_4_ = (float)((ulong)uVar11 >> 0x20);
      local_78._0_4_ = (float)uVar11;
      fStack_84 = local_78._4_4_ - local_b8._4_4_;
      local_88 = (float)local_78 - (float)local_b8;
      local_80 = fVar12 - local_b0;
      local_78 = uVar11;
      local_70 = fVar12;
      fVar12 = local_80;
      uVar4 = handleMissileHitUnit(CONCAT44(fStack_84,local_88),param_5,local_48);
      if (param_5[0x142] == (CBaseUnit)0x0) {
        if ((char)uVar4 == '\0') goto LAB_00d03d54;
      }
      else {
        if ((char)uVar4 == '\0') {
LAB_00d03d54:
          local_54 = *(float *)(param_6 + 4);
          goto LAB_00d03d59;
        }
        if (*(uint *)(param_5 + 0x2a0) != 0) {
          lVar8 = 0;
          uVar3 = 0;
          do {
            if (uVar3 < *(uint *)(param_5 + 0x2a4)) {
              plVar6 = (long *)(lVar8 + *(long *)(param_5 + 0x298));
            }
            else {
              plVar6 = *(long **)(param_5 + 0x298);
            }
            if ((CBaseUnit *)*plVar6 == local_48) goto LAB_00d03e60;
            uVar3 = uVar3 + 1;
            lVar8 = lVar8 + 8;
          } while (uVar3 < *(uint *)(param_5 + 0x2a0));
        }
                    /* try { // try from 00d03d93 to 00d03fc0 has its CatchHandler @ 00d04100 */
        TArrayList<CBaseUnit*>::add((TArrayList<CBaseUnit*> *)(param_5 + 0x298),local_48);
        TArrayList<bool>::add((TArrayList<bool> *)(param_5 + 0x2b0),true);
      }
LAB_00d03db0:
      if (param_5[0x142] == (CBaseUnit)0x0) {
LAB_00d03dbf:
        *(undefined4 *)param_6 = local_58;
        *(float *)(param_6 + 4) = local_54;
        *(undefined4 *)(param_6 + 8) = local_50;
        if ((*(uint *)(param_5 + 0x180) != 0) &&
           (*(uint *)(param_5 + 0x17c) <= *(uint *)(param_5 + 0x180))) {
          uVar11 = ricochetMissile((Vector3 *)param_5,param_6,(Vector3 *)&local_c8,param_7);
          local_98._0_4_ = (undefined4)uVar11;
          *(undefined4 *)param_6 = (undefined4)local_98;
          local_98._4_4_ = (undefined4)((ulong)uVar11 >> 0x20);
          *(undefined4 *)(param_6 + 4) = local_98._4_4_;
          *(float *)(param_6 + 8) = fVar12;
          if ((param_5[0x142] != (CBaseUnit)0x0) && (*(int *)(param_5 + 0x2a0) != 0)) {
            uVar3 = 0;
            do {
              if (uVar3 < *(uint *)(param_5 + 700)) {
                puVar7 = (undefined1 *)((ulong)uVar3 + *(long *)(param_5 + 0x2b0));
              }
              else {
                puVar7 = *(undefined1 **)(param_5 + 0x2b0);
              }
              if (uVar3 < *(uint *)(param_5 + 0x2a4)) {
                plVar6 = (long *)((ulong)uVar3 * 8 + *(long *)(param_5 + 0x298));
              }
              else {
                plVar6 = *(long **)(param_5 + 0x298);
              }
              uVar3 = uVar3 + 1;
              *(undefined1 *)(*plVar6 + 0x18d) = *puVar7;
            } while (uVar3 < *(uint *)(param_5 + 0x2a0));
          }
          *(undefined4 *)(param_5 + 0x2a0) = 0;
          *(undefined4 *)(param_5 + 0x2a4) = 0;
          local_98 = uVar11;
          local_90 = fVar12;
          if (*(void **)(param_5 + 0x298) != (void *)0x0) {
            operator_delete__(*(void **)(param_5 + 0x298));
          }
          *(undefined8 *)(param_5 + 0x298) = 0;
          *(undefined4 *)(param_5 + 0x2b8) = 0;
          *(undefined4 *)(param_5 + 700) = 0;
          if (*(void **)(param_5 + 0x2b0) != (void *)0x0) {
            operator_delete__(*(void **)(param_5 + 0x2b0));
          }
          *(undefined8 *)(param_5 + 0x2b0) = 0;
          *(undefined4 *)(param_5 + 0x1c0) = 0;
          if ((*(uint *)(param_5 + 0x180) != 0) &&
             (*(uint *)(param_5 + 0x17c) <= *(uint *)(param_5 + 0x180))) goto LAB_00d03e6f;
        }
        if (((param_5[0x142] == (CBaseUnit)0x0) || (local_48 == (CBaseUnit *)0x0)) &&
           ((param_5[0x184] == (CBaseUnit)0x0 && (killMissile(), local_48 == (CBaseUnit *)0x0)))) {
          doAOEDamage(param_5);
        }
      }
      else {
LAB_00d03e60:
        if (local_48 == (CBaseUnit *)0x0) goto LAB_00d03dbf;
      }
LAB_00d03e6f:
      *(float *)(param_6 + 4) = *(float *)(param_6 + 4) - *(float *)(param_5 + 0x170);
      *(float *)(param_7 + 4) = *(float *)(param_7 + 4) - *(float *)(param_5 + 0x170);
      goto LAB_00d03c51;
    }
    if ((param_5[0x188] == (CBaseUnit)0x0) || (*(float *)(param_8 + 4) <= DAT_00fa86e8))
    goto LAB_00d03db0;
    *(undefined4 *)param_6 = local_58;
    *(float *)(param_6 + 4) = local_54;
    *(undefined4 *)(param_6 + 8) = local_50;
    local_54 = local_54 + *(float *)(param_5 + 0x178);
    *(float *)(param_6 + 4) = local_54;
LAB_00d03d59:
    *(float *)(param_6 + 4) = local_54 - *(float *)(param_5 + 0x170);
    *(float *)(param_7 + 4) = *(float *)(param_7 + 4) - *(float *)(param_5 + 0x170);
  }
  local_48 = (CBaseUnit *)0x0;
  uVar4 = 0;
LAB_00d03c51:
  if ((param_5[0x142] != (CBaseUnit)0x0) && (*(int *)(param_5 + 0x2a0) != 0)) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(param_5 + 700)) {
        uVar5 = *(undefined1 *)((ulong)uVar3 + *(long *)(param_5 + 0x2b0));
        if (*(uint *)(param_5 + 0x2a4) <= uVar3) goto LAB_00d03c82;
LAB_00d03cb9:
        plVar6 = (long *)((ulong)uVar3 * 8 + *(long *)(param_5 + 0x298));
      }
      else {
        uVar5 = **(undefined1 **)(param_5 + 0x2b0);
        if (uVar3 < *(uint *)(param_5 + 0x2a4)) goto LAB_00d03cb9;
LAB_00d03c82:
        plVar6 = *(long **)(param_5 + 0x298);
      }
      uVar3 = uVar3 + 1;
      *(undefined1 *)(*plVar6 + 0x18d) = uVar5;
    } while (uVar3 < *(uint *)(param_5 + 0x2a0));
  }
  if ((param_9 != (undefined8 *)0x0) && ((char)uVar4 != '\0')) {
    *param_9 = local_48;
  }
  if ((local_a8 != (CRunicCore *)0x0) && (local_a8[0x18d] = CVar9, local_a8 != (CRunicCore *)0x0)) {
                    /* try { // try from 00d03d01 to 00d03d05 has its CatchHandler @ 00d040f8 */
    CRunicCore::removeSafePointer(local_a8,(TSafePointer *)&local_a8,local_a0);
  }
  return uVar4;
}



/* address=00d04120
   symbol=CMissile::update */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMissile::update(float) */

undefined8 CMissile::update(float param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  CPositionableObject *in_RDI;
  float fVar4;
  undefined8 uVar5;
  float in_XMM1_Da;
  float fVar6;
  undefined4 uVar7;
  undefined8 local_c8;
  undefined4 local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined4 local_a8;
  float fStack_a4;
  undefined4 local_a0;
  undefined8 local_98;
  undefined8 local_88;
  float local_80;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  long local_40;

  if (in_RDI[0x81] == (CPositionableObject)0x0) {
    return 0;
  }
  if (in_RDI[0x185] != (CPositionableObject)0x0) {
    if (in_RDI[0x184] != (CPositionableObject)0x0) {
      *(float *)(in_RDI + 0x174) = *(float *)(in_RDI + 0x174) - param_1;
    }
    if (*(CParticle **)(in_RDI + 0x108) != (CParticle *)0x0) {
      if (0.0 <= *(float *)(in_RDI + 0x174)) {
        uVar5 = CPositionableObject::getPosition(in_RDI,true);
        fStack_a4 = (float)((ulong)uVar5 >> 0x20);
        local_a8 = (undefined4)uVar5;
        _local_a8 = CONCAT44(fStack_a4 - *(float *)(in_RDI + 0x16c),local_a8);
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(in_RDI + 0x108),(Vector3 *)&local_a8);
      }
      else {
        CParticle::Stop(*(CParticle **)(in_RDI + 0x108),false);
      }
    }
    local_98 = CPositionableObject::getPosition(in_RDI,true);
    fVar4 = SQRT((*(float *)(in_RDI + 0x1a0) - (float)local_98) *
                 (*(float *)(in_RDI + 0x1a0) - (float)local_98) + 0.0 +
                 (*(float *)(in_RDI + 0x1a8) - in_XMM1_Da) *
                 (*(float *)(in_RDI + 0x1a8) - in_XMM1_Da));
    fVar6 = *(float *)(in_RDI + 0x1bc) + fVar4;
    fVar4 = fVar4 + *(float *)(in_RDI + 0x1c0);
    *(float *)(in_RDI + 0x1bc) = fVar6;
    *(float *)(in_RDI + 0x1c0) = fVar4;
    if (in_RDI[0x184] != (CPositionableObject)0x0) {
LAB_00d04550:
      uVar5 = handleDeathOfMissile((CMissile *)in_RDI,param_1);
      return uVar5;
    }
    if ((*(float *)(in_RDI + 0x1b8) <= fVar4) ||
       ((in_RDI[0x186] != (CPositionableObject)0x0 && (*(float *)(in_RDI + 0x198) <= fVar6)))) {
      killMissile();
      doAOEDamage((CBaseUnit *)in_RDI);
      if (in_RDI[0x184] != (CPositionableObject)0x0) goto LAB_00d04550;
    }
    uVar5 = CPositionableObject::getPosition(in_RDI,true);
    local_58._0_4_ = (undefined4)uVar5;
    *(undefined4 *)(in_RDI + 0x1a0) = (undefined4)local_58;
    local_58._4_4_ = (undefined4)((ulong)uVar5 >> 0x20);
    *(undefined4 *)(in_RDI + 0x1a4) = local_58._4_4_;
    *(float *)(in_RDI + 0x1a8) = fVar6;
    local_58 = uVar5;
    local_50 = fVar6;
    local_68 = updatePositionByVelocity((CMissile *)in_RDI,param_1);
    local_60 = fVar6;
    cVar3 = CResourceManager::getEditorIsRunning();
    if (cVar3 != '\0') {
      CPositionableObject::setPosition(in_RDI,(Vector3 *)&local_68);
      return 1;
    }
    bVar2 = false;
    do {
      local_40 = 0;
      uVar7 = *(undefined4 *)(in_RDI + 0x1a8);
      cVar3 = checkCollision(*(undefined8 *)(in_RDI + 0x1a0),uVar7,local_68,local_60);
      bVar1 = true;
      if (cVar3 == '\0') {
        bVar1 = bVar2;
      }
    } while ((in_RDI[0x142] != (CPositionableObject)0x0) && (bVar2 = bVar1, local_40 != 0));
    CPositionableObject::setPosition(in_RDI,(Vector3 *)&local_68);
    if ((bVar1) && (*(long *)(in_RDI + 0x110) != 0)) {
      uVar5 = CPositionableObject::getPosition(in_RDI,true);
      fStack_a4 = (float)((ulong)uVar5 >> 0x20);
      local_a8 = (undefined4)uVar5;
      _local_a8 = CONCAT44(fStack_a4 - *(float *)(in_RDI + 0x16c),local_a8);
      local_a0 = uVar7;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(in_RDI + 0x110),(Vector3 *)&local_a8);
      local_b8 = local_88;
      uVar5 = local_b8;
      local_b8._0_4_ = (float)local_88;
      local_b8._4_4_ = (float)((ulong)local_88 >> 0x20);
      local_b0 = local_80;
      fVar4 = SQRT((float)local_b8 * (float)local_b8 + local_b8._4_4_ * local_b8._4_4_ +
                   local_80 * local_80);
      if (DAT_00fa87a0 < (double)fVar4) {
        fVar4 = DAT_00fa47fc / fVar4;
        local_b0 = fVar4 * local_80;
        local_b8 = CONCAT44(local_b8._4_4_ * fVar4,(float)local_b8 * fVar4);
        uVar5 = local_b8;
      }
      local_b8 = uVar5;
      local_c8 = _UNIT_Y;
      local_c0 = DAT_01424b3c;
      (**(code **)(**(long **)(in_RDI + 0x110) + 0x128))
                (*(long **)(in_RDI + 0x110),&local_b8,&local_c8);
      CParticle::Start();
      return 1;
    }
  }
  return 1;
}



/* address=00d04610
   symbol=CMissile::fireMissile */

/* CMissile::fireMissile(CBaseUnit*, Ogre::Vector3, Ogre::Quaternion const&, CPositionableObject*,
   Ogre::Vector3) */

void CMissile::fireMissile
               (undefined8 param_1_00,float param_2,undefined8 param_3,float param_4,
               CMissile *param_1,CPositionableObject *param_6,Quaternion *param_7,
               CPositionableObject *param_8)

{
  CMissile CVar1;
  CRunicCore *pCVar2;
  char cVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  float *pfVar6;
  CRunicCore *this;
  long *plVar7;
  CPositionableObject *pCVar8;
  CGameClient *this_00;
  uint uVar9;
  long lVar10;
  float fVar11;
  undefined8 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float local_1c4;
  float local_1c0;
  undefined8 local_1a8;
  float local_1a0;
  undefined8 local_198;
  float local_190;
  undefined8 local_188;
  float local_180;
  undefined8 local_178;
  float local_170;
  undefined8 local_168;
  float local_160;
  float local_158;
  float fStack_154;
  float local_150;
  undefined1 local_148 [16];
  undefined1 local_138 [16];
  Vector3 local_128 [16];
  undefined8 local_118;
  float local_110;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  Vector3 local_e8 [16];
  Vector3 local_d8 [16];
  undefined8 local_c8;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  CBaseUnit *local_48;
  uint local_3c [3];

  *(undefined4 *)(param_1 + 0x2a0) = 0;
  *(undefined4 *)(param_1 + 0x2a4) = 0;
  local_1a8 = param_3;
  local_1a0 = param_4;
  local_198 = param_1_00;
  local_190 = param_2;
  if (*(void **)(param_1 + 0x298) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x298));
  }
  *(undefined8 *)(param_1 + 0x298) = 0;
  *(undefined4 *)(param_1 + 0x2b8) = 0;
  *(undefined4 *)(param_1 + 700) = 0;
  if (*(void **)(param_1 + 0x2b0) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x2b0));
  }
  *(undefined8 *)(param_1 + 0x2b0) = 0;
  lVar10 = 0;
  do {
    if (*(CParticle **)(param_1 + lVar10 + 0x100) != (CParticle *)0x0) {
      CParticle::Stop(*(CParticle **)(param_1 + lVar10 + 0x100),false);
      (**(code **)(**(long **)(param_1 + lVar10 + 0x100) + 0x50))
                (*(long **)(param_1 + lVar10 + 0x100),0);
      (**(code **)(**(long **)(param_1 + lVar10 + 0x100) + 0x108))
                (*(long **)(param_1 + lVar10 + 0x100),param_7);
      CPositionableObject::setPosition
                (*(CPositionableObject **)(param_1 + lVar10 + 0x100),(Vector3 *)&local_198);
    }
    lVar10 = lVar10 + 8;
  } while (lVar10 != 0x20);
  param_1[0x144] = (CMissile)0x0;
  if ((param_1[0x185] == (CMissile)0x0) && (*(int *)(param_1 + 0x1d0) != 0)) {
    uVar9 = 0;
    do {
      if (uVar9 < *(uint *)(param_1 + 0x1d4)) {
        puVar5 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(param_1 + 0x1c8));
      }
      else {
        puVar5 = *(undefined8 **)(param_1 + 0x1c8);
      }
      uVar9 = uVar9 + 1;
      param_8 = (CPositionableObject *)
                (**(code **)(*(long *)*puVar5 + 0x30))((long *)*puVar5,param_1,param_8,&local_1a8);
    } while (uVar9 < *(uint *)(param_1 + 0x1d0));
  }
  if ((param_6 == (CPositionableObject *)0x0) &&
     (param_6 = *(CPositionableObject **)(param_1 + 0x220), param_6 == (CPositionableObject *)0x0))
  {
    local_1c4 = 0.0;
  }
  else {
    uVar12 = CPositionableObject::getPosition(param_6,true);
    local_58._4_4_ = (float)((ulong)uVar12 >> 0x20);
    local_1c4 = local_58._4_4_ - *(float *)(param_6 + 0x194);
    local_58 = uVar12;
    local_50 = param_2;
  }
  local_1c0 = 0.0;
  fVar13 = (local_198._4_4_ - *(float *)(param_1 + 0x178)) - local_1c4;
  fVar14 = fVar13;
  fVar11 = local_198._4_4_;
  if ((fVar13 < DAT_00fc67e8) && (!NAN(fVar13) && !NAN(DAT_00fc67e8))) {
    fVar14 = (float)(DAT_00fa8780 ^ (uint)fVar13);
    fVar11 = local_198._4_4_ + fVar14;
    *(float *)(param_1 + 0x16c) = fVar14;
    local_198 = CONCAT44(fVar11,(float)local_198);
  }
  *(float *)(param_1 + 0x1a4) = fVar11;
  *(float *)(param_1 + 0x1e4) = fVar11;
  *(float *)(param_1 + 0x1a8) = local_190;
  *(float *)(param_1 + 0x1e8) = local_190;
  *(float *)(param_1 + 0x1a0) = (float)local_198;
  *(float *)(param_1 + 0x1e0) = (float)local_198;
  setTarget(param_1,param_8);
  pCVar2 = *(CRunicCore **)(param_1 + 0x220);
  *(undefined4 *)(param_1 + 0x25c) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = *(undefined4 *)(param_1 + 0x1ac);
  *(undefined4 *)(param_1 + 0x174) = 0x3dcccccd;
  param_1[0x141] = (CMissile)0x0;
  param_1[0x184] = (CMissile)0x0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 600) = *(undefined4 *)(param_1 + 0x254);
  if (param_6 != (CPositionableObject *)pCVar2) {
    if (pCVar2 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (pCVar2,(TSafePointer *)(param_1 + 0x220),*(uint *)(param_1 + 0x228));
    }
    *(undefined8 *)(param_1 + 0x220) = 0;
    if (param_6 != (CPositionableObject *)0x0) {
      uVar4 = CRunicCore::addSafePointer((CRunicCore *)param_6,(TSafePointer *)(param_1 + 0x220));
      *(undefined4 *)(param_1 + 0x228) = uVar4;
    }
    *(CPositionableObject **)(param_1 + 0x220) = param_6;
  }
  CPositionableObject::setPosition((CPositionableObject *)param_1,(Vector3 *)&local_198);
  (**(code **)(*(long *)param_1 + 0x108))(param_1,param_7);
  (**(code **)(**(long **)(param_1 + 0x58) + 0x218))(*(long **)(param_1 + 0x58),1,1);
  if ((((param_8 == (CPositionableObject *)0x0) &&
       (param_8 = *(CPositionableObject **)(param_1 + 0x230), param_8 == (CPositionableObject *)0x0)
       ) && (*(long *)(param_1 + 0x220) != 0)) &&
     (lVar10 = __dynamic_cast(*(long *)(param_1 + 0x220),&CBaseUnit::typeinfo,&CCharacter::typeinfo,
                              0), lVar10 != 0)) {
    pCVar8 = *(CPositionableObject **)(lVar10 + 0x340);
    if ((pCVar8 == (CPositionableObject *)0x0) &&
       (pCVar8 = *(CPositionableObject **)(lVar10 + 0x350), pCVar8 == (CPositionableObject *)0x0)) {
      if (0.0 < *(float *)(param_1 + 0x250)) {
        this = (CRunicCore *)getClosestTarget(param_1,param_7,(Vector3 *)&local_198);
        pCVar2 = *(CRunicCore **)(param_1 + 0x230);
        if (this != pCVar2) {
          if (pCVar2 != (CRunicCore *)0x0) {
            CRunicCore::removeSafePointer
                      (pCVar2,(TSafePointer *)(param_1 + 0x230),*(uint *)(param_1 + 0x238));
          }
          *(undefined8 *)(param_1 + 0x230) = 0;
          if (this != (CRunicCore *)0x0) {
            uVar4 = CRunicCore::addSafePointer(this,(TSafePointer *)(param_1 + 0x230));
            *(undefined4 *)(param_1 + 0x238) = uVar4;
          }
          *(CRunicCore **)(param_1 + 0x230) = this;
        }
        setTarget(param_1,(CPositionableObject *)this);
      }
    }
    else {
      setTarget(param_1,pCVar8);
      param_8 = *(CPositionableObject **)(param_1 + 0x230);
    }
  }
  fVar11 = local_1c0;
  if (param_6 != (CPositionableObject *)0x0) {
    local_68 = CPositionableObject::getPosition(param_6,true);
    fVar11 = SQRT(((float)local_198 - (float)local_68) * ((float)local_198 - (float)local_68) + 0.0
                  + (local_190 - fVar14) * (local_190 - fVar14));
    local_60 = fVar14;
  }
  if (param_8 == (CPositionableObject *)0x0) {
    fVar15 = fVar14;
    if ((*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) &&
       (**(long **)(*(long *)(param_1 + 0x68) + 0x28) != 0)) {
      fVar14 = (float)local_1a8;
      if (((float)local_1a8 == Ogre::Vector3::ZERO) &&
         (!NAN((float)local_1a8) && !NAN(Ogre::Vector3::ZERO))) {
        fVar15 = local_1a8._4_4_;
        if ((local_1a8._4_4_ == DAT_014241b0) && (!NAN(local_1a8._4_4_) && !NAN(DAT_014241b0))) {
          fVar15 = local_1a0;
          if ((local_1a0 == DAT_014241b4) &&
             ((!NAN(local_1a0) && !NAN(DAT_014241b4) && (param_6 != (CPositionableObject *)0x0)))) {
            cVar3 = CBaseUnit::ISA((CBaseUnit *)param_6,0x1c);
            if ((cVar3 == '\0') || (param_1[0x143] == (CMissile)0x0)) {
              fVar14 = (float)local_1a8;
            }
            else {
              this_00 = (CGameClient *)0x0;
              if (*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) {
                this_00 = (CGameClient *)**(undefined8 **)(*(long *)(param_1 + 0x68) + 0x28);
              }
              CGameClient::findWorldLocation(this_00,(Vector3 *)&local_1a8,true);
              uVar12 = local_1a8;
              local_b0 = local_1a0;
              local_c0 = local_1a0;
              local_b8._4_4_ = (float)(local_1a8 >> 0x20);
              fVar14 = local_b8._4_4_;
              local_1a8 = CONCAT44(DAT_014241b0,Ogre::Vector3::ZERO);
              local_b8._0_4_ = (float)uVar12;
              local_b8 = CONCAT44(local_b8._4_4_ + DAT_00fa483c,(float)local_b8);
              local_1a0 = DAT_014241b4;
              local_f8 = local_198;
              local_c8 = CONCAT44(fVar14 - DAT_00fa483c,(float)local_b8);
              local_f0 = local_190;
              fVar17 = DAT_00fa483c;
              cVar3 = CLevel::rayCollision
                                (*(CLevel **)(*(long *)(param_1 + 0x68) + 0x18),(Vector3 *)&local_b8
                                 ,(Vector3 *)&local_c8,(Vector3 *)&local_f8,local_d8,local_3c,
                                 local_e8,false);
              if ((cVar3 == '\0') || (local_3c[0] == 100)) {
                pfVar6 = (float *)(**(code **)(*(long *)param_1 + 0x130))(param_1);
                fVar15 = local_190 + pfVar6[2];
                local_1a8 = CONCAT44((local_198._4_4_ + pfVar6[1]) - fVar13,
                                     (float)local_198 + *pfVar6);
                fVar14 = (float)local_198 + *pfVar6;
                local_1a0 = fVar15;
              }
              else {
                local_188 = CPositionableObject::getPosition(param_6,true);
                fVar14 = (float)local_188;
                fVar15 = (float)local_f8 - (float)local_188;
                fVar18 = local_f8._4_4_;
                local_1a8 = (ulong)(uint)fVar15;
                local_1a0 = local_f0 - fVar17;
                fVar19 = SQRT(fVar15 * fVar15 + 0.0 + local_1a0 * local_1a0);
                fVar16 = fVar17;
                local_180 = fVar17;
                uVar12 = Ogre::Quaternion::zAxis();
                local_108._4_4_ = (float)((ulong)uVar12 >> 0x20);
                local_108._0_4_ = (float)uVar12;
                fVar15 = local_190 - fVar17;
                fVar14 = fVar19 * (float)local_108 + fVar14 + ((float)local_198 - fVar14);
                local_1a8 = CONCAT44((((fVar18 - local_1c4) + local_108._4_4_ * fVar19 + local_1c4)
                                     - fVar13) + (local_198._4_4_ - local_1c4),fVar14);
                local_1a0 = fVar16 * fVar19 + fVar17 + fVar15;
                local_108 = uVar12;
                local_100 = fVar16;
              }
            }
          }
        }
      }
      if ((Ogre::Vector3::ZERO == fVar14) && (!NAN(Ogre::Vector3::ZERO) && !NAN(fVar14))) {
        if ((local_1a8._4_4_ == DAT_014241b0) &&
           ((!NAN(local_1a8._4_4_) && !NAN(DAT_014241b0) && (local_1a0 == DAT_014241b4))))
        goto LAB_00d04b8a;
      }
      fVar17 = local_1c0;
      fVar14 = local_1c0;
      if (param_6 != (CPositionableObject *)0x0) {
        local_118 = CPositionableObject::getPosition(param_6,true);
        fVar14 = (float)local_1a8 - (float)local_118;
        fVar17 = local_1a0 - local_1c0;
        local_110 = local_1c0;
      }
      local_1a8 = CONCAT44(fVar13 + local_1a8._4_4_,(float)local_1a8);
      fVar15 = fVar11 + 0.1;
      if (fVar15 < SQRT(fVar14 * fVar14 + 0.0 + fVar17 * fVar17)) goto LAB_00d04ecb;
    }
LAB_00d04b8a:
    CVar1 = param_1[0x140];
  }
  else {
    if (param_6 == (CPositionableObject *)0x0) {
      uVar12 = CPositionableObject::getPosition(param_8,true);
      local_b8._0_4_ = (float)uVar12;
      fVar17 = (float)local_b8 - (float)local_198;
      local_b8._4_4_ = (float)((ulong)uVar12 >> 0x20);
      fVar15 = local_b8._4_4_;
      local_b0 = fVar14 - local_190;
      local_b8 = (ulong)(uint)fVar17;
      fVar17 = SQRT(fVar17 * fVar17 + 0.0 + local_b0 * local_b0);
      local_a8 = Ogre::Quaternion::zAxis();
      local_b0 = fVar14 * fVar17 + local_190;
      local_b8 = CONCAT44(fVar13 + fVar15,fVar17 * (float)local_a8 + (float)local_198);
      fVar15 = local_1c0;
      local_a0 = fVar14;
      if (fVar11 + 0.1 < 0.0) {
        calculateLaunchOrientation(param_1,(Vector3 *)&local_198,(Vector3 *)&local_b8);
        fVar15 = local_1c0;
      }
      goto LAB_00d04b8a;
    }
    local_b8 = CPositionableObject::getPosition(param_6,true);
    fVar13 = (float)local_b8;
    fVar15 = (float)local_b8;
    local_b0 = fVar14;
    uVar12 = CPositionableObject::getPosition(param_8,true);
    local_78._0_4_ = (float)uVar12;
    local_78._0_4_ = (float)local_78 - fVar13;
    local_78._4_4_ = (float)((ulong)uVar12 >> 0x20);
    local_1a0 = fVar15 - fVar14;
    fVar17 = local_78._4_4_ - *(float *)(param_8 + 0x194);
    local_1a8 = (ulong)(uint)(float)local_78;
    fVar18 = SQRT((float)local_78 * (float)local_78 + 0.0 + local_1a0 * local_1a0);
    local_78 = uVar12;
    local_70 = fVar15;
    uVar12 = Ogre::Quaternion::zAxis();
    local_88._4_4_ = (float)((ulong)uVar12 >> 0x20);
    local_88._0_4_ = (float)uVar12;
    fVar14 = fVar15 * fVar18 + fVar14 + (local_190 - fVar14);
    local_1a8 = CONCAT44(local_88._4_4_ * fVar18 + local_1c4 + (fVar17 - local_1c4) +
                         (local_198._4_4_ - local_1c4),
                         fVar18 * (float)local_88 + fVar13 + ((float)local_198 - fVar13));
    local_1a0 = fVar14;
    local_88 = uVar12;
    local_80 = fVar15;
    local_98 = CPositionableObject::getPosition(param_6,true);
    fVar15 = fVar11 + 0.1;
    local_90 = fVar14;
    if (SQRT(((float)local_1a8 - (float)local_98) * ((float)local_1a8 - (float)local_98) + 0.0 +
             (local_1a0 - fVar14) * (local_1a0 - fVar14)) <= fVar11 + 0.1) goto LAB_00d04b8a;
LAB_00d04ecb:
    fVar15 = fVar11 + 0.1;
    calculateLaunchOrientation(param_1,(Vector3 *)&local_198,(Vector3 *)&local_1a8);
    CVar1 = param_1[0x140];
  }
  if (CVar1 != (CMissile)0x0) {
    fVar14 = *(float *)(param_1 + 0x158);
    pfVar6 = (float *)(**(code **)(*(long *)param_1 + 0x130))(param_1);
    fVar11 = pfVar6[1];
    fVar15 = pfVar6[2] * fVar14;
    fVar13 = *pfVar6;
    *(float *)(param_1 + 0x150) = fVar15;
    *(float *)(param_1 + 0x14c) = fVar11 * fVar14;
    *(float *)(param_1 + 0x148) = fVar14 * fVar13;
  }
  (**(code **)(*(long *)param_1 + 0x50))(param_1,1);
  if ((param_1[0x185] == (CMissile)0x0) && (*(int *)(param_1 + 0x1d0) != 0)) {
    uVar9 = 0;
    do {
      if (uVar9 < *(uint *)(param_1 + 0x1d4)) {
        puVar5 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(param_1 + 0x1c8));
      }
      else {
        puVar5 = *(undefined8 **)(param_1 + 0x1c8);
      }
      uVar9 = uVar9 + 1;
      (**(code **)(*(long *)*puVar5 + 0x10))((long *)*puVar5,param_1);
    } while (uVar9 < *(uint *)(param_1 + 0x1d0));
  }
  local_48 = (CBaseUnit *)0x0;
  if (param_6 != (CPositionableObject *)0x0) {
    local_168 = CPositionableObject::getPosition(param_6,true);
    local_160 = fVar15;
    if (((float)local_198 == (float)local_168) && (!NAN((float)local_198) && !NAN((float)local_168))
       ) {
      local_168._4_4_ = (float)((ulong)local_168 >> 0x20);
      if ((local_198._4_4_ == local_168._4_4_) &&
         ((!NAN(local_198._4_4_) && !NAN(local_168._4_4_) && (local_190 == fVar15))))
      goto LAB_00d05066;
    }
    local_178 = CPositionableObject::getPosition(param_6,true);
    fVar14 = SQRT(((float)local_178 - (float)local_198) * ((float)local_178 - (float)local_198) +
                  (local_198._4_4_ - local_198._4_4_) * (local_198._4_4_ - local_198._4_4_) +
                  (fVar15 - local_190) * (fVar15 - local_190));
    local_170 = fVar15;
    if ((fVar14 < DAT_00fa8768) && (!NAN(fVar14) && !NAN(DAT_00fa8768))) {
      fStack_154 = local_198._4_4_;
      local_158 = (float)local_178;
      local_150 = fVar15;
      cVar3 = checkCollision(CONCAT44(local_198._4_4_,(float)local_178),fVar15,local_198,local_190,
                             param_1,local_128,local_148,local_138,&local_48);
      if ((cVar3 != '\0') && (local_48 != (CBaseUnit *)0x0)) {
        if (*(long *)(param_1 + 0x100) != 0) {
          uVar12 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
          local_188._4_4_ = (float)((ulong)uVar12 >> 0x20);
          local_188._0_4_ = (float)uVar12;
          local_188 = CONCAT44(local_188._4_4_ - *(float *)(param_1 + 0x16c),(float)local_188);
          local_180 = fVar15;
          CPositionableObject::setPosition
                    (*(CPositionableObject **)(param_1 + 0x100),(Vector3 *)&local_188);
          CParticle::Start();
        }
        CPositionableObject::setPosition((CPositionableObject *)param_1,local_128);
        if (local_48 == (CBaseUnit *)0x0) {
          doAOEDamage((CBaseUnit *)param_1);
        }
        if (((param_1[0x142] == (CMissile)0x0) &&
            (cVar3 = CBaseUnit::ISA(local_48,0x19), cVar3 == '\0')) &&
           (cVar3 = CBaseUnit::ISA(local_48,0x1d), cVar3 == '\0')) {
          killMissile();
        }
        else {
          if (*(long *)(param_1 + 0x108) != 0) {
            uVar12 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
            local_188._4_4_ = (float)((ulong)uVar12 >> 0x20);
            local_188._0_4_ = (float)uVar12;
            local_188 = CONCAT44(local_188._4_4_ - *(float *)(param_1 + 0x16c),(float)local_188);
            local_180 = fVar15;
            CPositionableObject::setPosition
                      (*(CPositionableObject **)(param_1 + 0x108),(Vector3 *)&local_188);
            CParticle::Start();
          }
          if (*(uint *)(param_1 + 0x2a0) != 0) {
            lVar10 = 0;
            uVar9 = 0;
            do {
              if (uVar9 < *(uint *)(param_1 + 0x2a4)) {
                plVar7 = (long *)(lVar10 + *(long *)(param_1 + 0x298));
              }
              else {
                plVar7 = *(long **)(param_1 + 0x298);
              }
              if ((CBaseUnit *)*plVar7 == local_48) goto LAB_00d0516c;
              uVar9 = uVar9 + 1;
              lVar10 = lVar10 + 8;
            } while (uVar9 < *(uint *)(param_1 + 0x2a0));
          }
          TArrayList<CBaseUnit*>::add((TArrayList<CBaseUnit*> *)(param_1 + 0x298),local_48);
          TArrayList<bool>::add((TArrayList<bool> *)(param_1 + 0x2b0),true);
        }
        goto LAB_00d0516c;
      }
    }
  }
LAB_00d05066:
  if (*(long *)(param_1 + 0x100) != 0) {
    uVar12 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    local_188._4_4_ = (float)((ulong)uVar12 >> 0x20);
    local_188._0_4_ = (float)uVar12;
    local_188 = CONCAT44(local_188._4_4_ - *(float *)(param_1 + 0x16c),(float)local_188);
    local_180 = fVar15;
    CPositionableObject::setPosition
              (*(CPositionableObject **)(param_1 + 0x100),(Vector3 *)&local_188);
    CParticle::Start();
  }
  if (*(long *)(param_1 + 0x108) != 0) {
    uVar12 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    local_188._4_4_ = (float)((ulong)uVar12 >> 0x20);
    local_188._0_4_ = (float)uVar12;
    local_188 = CONCAT44(local_188._4_4_ - *(float *)(param_1 + 0x16c),(float)local_188);
    local_180 = fVar15;
    CPositionableObject::setPosition
              (*(CPositionableObject **)(param_1 + 0x108),(Vector3 *)&local_188);
    CParticle::Start();
  }
LAB_00d0516c:
  param_1[0x185] = (CMissile)0x1;
  return;
}



/* address=00d05ad0
   symbol=CMissile::~CMissile */

/* WARNING: Removing unreachable block (ram,0x00d05f7f) */
/* WARNING: Removing unreachable block (ram,0x00d05ebe) */
/* CMissile::~CMissile() */

void __thiscall CMissile::~CMissile(CMissile *this)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  long lVar4;
  long *plVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  uint uVar8;
  ulong uVar9;
  allocator *paVar10;
  CMissile *pCVar11;

  *(undefined ***)this = &PTR__CMissile_00ff6650;
  if (*(int *)(this + 0x1f8) != 0) {
    uVar9 = 0;
    do {
      uVar8 = (uint)uVar9;
                    /* try { // try from 00d05b0a to 00d05cbc has its CatchHandler @ 00d05f27 */
      lVar4 = Ogre::SceneNode::getParentSceneNode();
      if (lVar4 != 0) {
        plVar5 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x68) + 0x10) + 0x250))();
        if (uVar8 < *(uint *)(this + 0x1fc)) {
          puVar7 = (undefined8 *)(uVar9 * 8 + *(long *)(this + 0x1f0));
        }
        else {
          puVar7 = *(undefined8 **)(this + 0x1f0);
        }
        (**(code **)(*plVar5 + 0x1e0))(plVar5,*puVar7);
      }
      plVar5 = *(long **)(*(long *)(this + 0x68) + 0x10);
      pcVar3 = *(code **)(*plVar5 + 0x288);
      if (uVar8 < *(uint *)(this + 0x1fc)) {
        puVar7 = (undefined8 *)(uVar9 * 8 + *(long *)(this + 0x1f0));
      }
      else {
        puVar7 = *(undefined8 **)(this + 0x1f0);
      }
      uVar6 = (**(code **)(*(long *)*puVar7 + 0x288))((long *)*puVar7,0);
      (*pcVar3)(plVar5,uVar6);
      (**(code **)(**(long **)(*(long *)(this + 0x68) + 0x10) + 0x248))();
      uVar9 = (ulong)(uVar8 + 1);
    } while (uVar8 + 1 < *(uint *)(this + 0x1f8));
  }
  *(undefined4 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x1fc) = 0;
  if (*(void **)(this + 0x1f0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1f0));
  }
  *(undefined8 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d4) = 0;
  if (*(void **)(this + 0x1c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1c8));
  }
  *(undefined8 *)(this + 0x1c8) = 0;
  lVar4 = 0;
  do {
    if (*(long **)(this + lVar4 + 0x100) != (long *)0x0) {
      (**(code **)(**(long **)(this + lVar4 + 0x100) + 8))();
      *(undefined8 *)(this + lVar4 + 0x100) = 0;
    }
    lVar4 = lVar4 + 8;
  } while (lVar4 != 0x20);
  if (*(long **)(this + 0x210) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x210) + 8))();
    *(undefined8 *)(this + 0x210) = 0;
  }
  paVar10 = (allocator *)(*(long *)(this + 0x2c8) + -0x18);
  if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x2c8) + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar10);
    }
  }
  if (*(void **)(this + 0x2b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2b0));
    *(undefined8 *)(this + 0x2b0) = 0;
  }
  if (*(void **)(this + 0x298) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x298));
    *(undefined8 *)(this + 0x298) = 0;
  }
  if (*(CRunicCore **)(this + 0x240) != (CRunicCore *)0x0) {
                    /* try { // try from 00d05d32 to 00d05d36 has its CatchHandler @ 00d05eed */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x240),(TSafePointer *)(this + 0x240),*(uint *)(this + 0x248)
              );
  }
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined4 *)(this + 0x248) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x230) != (CRunicCore *)0x0) {
                    /* try { // try from 00d05d65 to 00d05d69 has its CatchHandler @ 00d05ed9 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x230),(TSafePointer *)(this + 0x230),*(uint *)(this + 0x238)
              );
  }
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined4 *)(this + 0x238) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x220) != (CRunicCore *)0x0) {
                    /* try { // try from 00d05d98 to 00d05d9c has its CatchHandler @ 00d05e62 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x220),(TSafePointer *)(this + 0x220),*(uint *)(this + 0x228)
              );
  }
  *(undefined8 *)(this + 0x220) = 0;
  *(undefined4 *)(this + 0x228) = 0xffffffff;
  if (*(void **)(this + 0x1f0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1f0));
    *(undefined8 *)(this + 0x1f0) = 0;
  }
  if (*(void **)(this + 0x1c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1c8));
    *(undefined8 *)(this + 0x1c8) = 0;
  }
  pCVar11 = this + 0x140;
  do {
    pCVar11 = pCVar11 + -8;
    paVar10 = (allocator *)(*(long *)pCVar11 + -0x18);
    if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)pCVar11 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar10);
      }
    }
  } while (pCVar11 != this + 0x120);
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}



/* address=00d05f90
   symbol=CMissile::~CMissile */

/* CMissile::~CMissile() */

void __thiscall CMissile::~CMissile(CMissile *this)

{
  ~CMissile(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00d05fb0
   symbol=CMissile::CMissile */

/* CMissile::CMissile(CResourceManager*) */

void __thiscall CMissile::CMissile(CMissile *this,CResourceManager *param_1)

{
  long lVar1;

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CMissile_00ff6650;
  lVar1 = 0;
  do {
    *(undefined4 **)(this + lVar1 + 0x120) = &DAT_01424558;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x20);
  this[0x142] = (CMissile)0x0;
  this[0x143] = (CMissile)0x1;
  this[0x144] = (CMissile)0x0;
  *(undefined4 *)(this + 0x16c) = 0;
  *(undefined4 *)(this + 0x170) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d4) = 0;
  *(undefined4 *)(this + 0x1d8) = 10;
  *(undefined8 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x1fc) = 0;
  *(undefined4 *)(this + 0x200) = 10;
  *(undefined8 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x220) = 0;
  *(undefined4 *)(this + 0x228) = 0xffffffff;
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined4 *)(this + 0x238) = 0xffffffff;
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined4 *)(this + 0x248) = 0xffffffff;
  *(undefined4 *)(this + 0x264) = 0;
  *(undefined4 *)(this + 0x268) = 0;
  *(undefined4 *)(this + 0x26c) = 0;
  *(undefined4 *)(this + 0x270) = 0x3e800000;
  *(undefined4 *)(this + 0x274) = 0;
  *(undefined4 *)(this + 0x278) = 0;
  *(undefined4 *)(this + 0x284) = 0;
  *(undefined4 *)(this + 0x288) = 0;
  *(undefined4 *)(this + 0x28c) = 0;
  *(undefined8 *)(this + 0x298) = 0;
  *(undefined4 *)(this + 0x2a0) = 0;
  *(undefined4 *)(this + 0x2a4) = 0;
  *(undefined4 *)(this + 0x2a8) = 10;
  *(undefined8 *)(this + 0x2b0) = 0;
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  *(undefined4 *)(this + 0x2c0) = 10;
  *(undefined4 **)(this + 0x2c8) = &DAT_01424558;
  *(undefined4 *)(this + 0x2d0) = 0;
                    /* try { // try from 00d06170 to 00d06174 has its CatchHandler @ 00d06180 */
  initialize(this);
  return;
}



/* address=00d06250
   symbol=CMissile::CMissile */

/* WARNING: Removing unreachable block (ram,0x00d0672d) */
/* CMissile::CMissile(CResourceManager*, CMissile const*) */

void __thiscall CMissile::CMissile(CMissile *this,CResourceManager *param_1,CMissile *param_2)

{
  int *piVar1;
  int iVar2;
  CRunicCore *this_00;
  CRunicCore *this_01;
  undefined4 uVar3;
  long lVar4;
  uint uVar5;
  ulong uVar6;
  CMissile *pCVar7;
  long local_48 [3];

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CMissile_00ff6650;
  lVar4 = 0;
  do {
    *(undefined4 **)(this + lVar4 + 0x120) = &DAT_01424558;
    lVar4 = lVar4 + 8;
  } while (lVar4 != 0x20);
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined4 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d4) = 0;
  *(undefined4 *)(this + 0x1d8) = 10;
  *(undefined8 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x1fc) = 0;
  *(undefined4 *)(this + 0x200) = 10;
  *(undefined8 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x220) = 0;
  *(undefined4 *)(this + 0x228) = 0xffffffff;
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined4 *)(this + 0x238) = 0xffffffff;
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined4 *)(this + 0x248) = 0xffffffff;
  *(undefined8 *)(this + 0x298) = 0;
  *(undefined4 *)(this + 0x2a0) = 0;
  *(undefined4 *)(this + 0x2a4) = 0;
  *(undefined4 *)(this + 0x2a8) = 10;
  *(undefined8 *)(this + 0x2b0) = 0;
  *(undefined4 *)(this + 0x2b8) = 0;
  *(undefined4 *)(this + 700) = 0;
  *(undefined4 *)(this + 0x2c0) = 10;
  *(undefined4 **)(this + 0x2c8) = &DAT_01424558;
                    /* try { // try from 00d063a6 to 00d065f7 has its CatchHandler @ 00d06725 */
  initialize(this);
  CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)(param_2 + 0x84));
  this_00 = *(CRunicCore **)(this + 0x220);
  *(undefined4 *)(this + 0x2d0) = *(undefined4 *)(param_2 + 0x2d0);
  *(undefined4 *)(this + 0x19c) = *(undefined4 *)(param_2 + 0x19c);
  this[0x186] = param_2[0x186];
  this[0x187] = param_2[0x187];
  this[0x188] = param_2[0x188];
  *(undefined4 *)(this + 0x260) = *(undefined4 *)(param_2 + 0x260);
  *(undefined4 *)(this + 0x170) = *(undefined4 *)(param_2 + 0x88);
  *(undefined4 *)(this + 0x16c) = *(undefined4 *)(param_2 + 0x16c);
  *(undefined4 *)(this + 0x154) = *(undefined4 *)(param_2 + 0x154);
  *(undefined4 *)(this + 0x158) = *(undefined4 *)(param_2 + 0x158);
  *(undefined4 *)(this + 0x27c) = *(undefined4 *)(param_2 + 0x27c);
  *(undefined4 *)(this + 0x280) = *(undefined4 *)(param_2 + 0x280);
  this[0x140] = param_2[0x140];
  *(undefined4 *)(this + 0x180) = *(undefined4 *)(param_2 + 0x180);
  *(undefined4 *)(this + 0x178) = *(undefined4 *)(param_2 + 0x178);
  *(undefined4 *)(this + 0x15c) = *(undefined4 *)(param_2 + 0x15c);
  this_01 = *(CRunicCore **)(param_2 + 0x220);
  if (this_01 != this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x220),*(uint *)(this + 0x228));
    }
    *(undefined8 *)(this + 0x220) = 0;
    if (this_01 != (CRunicCore *)0x0) {
      uVar3 = CRunicCore::addSafePointer(this_01,(TSafePointer *)(this + 0x220));
      *(undefined4 *)(this + 0x228) = uVar3;
    }
    *(CRunicCore **)(this + 0x220) = this_01;
  }
  *(undefined4 *)(this + 0x1ac) = *(undefined4 *)(param_2 + 0x1ac);
  *(undefined4 *)(this + 0x1b8) = *(undefined4 *)(param_2 + 0x1b8);
  *(undefined4 *)(this + 0x160) = *(undefined4 *)(param_2 + 0x160);
  this[0x142] = param_2[0x142];
  this[0x143] = param_2[0x143];
  *(undefined4 *)(this + 0x264) = *(undefined4 *)(param_2 + 0x264);
  *(undefined4 *)(this + 0x268) = *(undefined4 *)(param_2 + 0x268);
  *(undefined4 *)(this + 0x26c) = *(undefined4 *)(param_2 + 0x26c);
  *(undefined4 *)(this + 0x270) = *(undefined4 *)(param_2 + 0x270);
  *(undefined4 *)(this + 0x284) = *(undefined4 *)(param_2 + 0x284);
  *(undefined4 *)(this + 0x288) = *(undefined4 *)(param_2 + 0x288);
  *(undefined4 *)(this + 0x28c) = *(undefined4 *)(param_2 + 0x28c);
  *(undefined4 *)(this + 0x250) = *(undefined4 *)(param_2 + 0x250);
  std::wstring::assign((wstring_conflict *)(this + 0x2c8));
  uVar3 = *(undefined4 *)(param_2 + 0x254);
  *(undefined4 *)(this + 0x274) = 0;
  uVar6 = 0;
  *(undefined4 *)(this + 0x254) = uVar3;
  pCVar7 = param_2;
  do {
    if (*(long *)(pCVar7 + 0x100) != 0) {
      std::wstring::wstring
                ((wstring_conflict *)local_48,(wstring_conflict *)(param_2 + uVar6 * 8 + 0x120));
                    /* try { // try from 00d06601 to 00d06605 has its CatchHandler @ 00d0665b */
      setParticleFile(this,uVar6,(wstring_conflict *)local_48);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
    }
    uVar5 = (int)uVar6 + 1;
    uVar6 = (ulong)uVar5;
    pCVar7 = pCVar7 + 8;
  } while (uVar5 != 4);
  return;
}



/* export-summary functions=33 failures=0 */
