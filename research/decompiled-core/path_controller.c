/* Targeted Ghidra class export.
   namespace=CPathController
   Treat pseudocode as navigation evidence. */


/* address=00593970
   symbol=CPathController::setVisible */

/* CPathController::setVisible(bool) */

void __thiscall CPathController::setVisible(CPathController *this,bool param_1)

{
  undefined8 *puVar1;
  uint uVar2;

  this[0x130] = (CPathController)param_1;
  if (*(int *)(this + 0x140) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x144)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x138));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x138);
      }
      uVar2 = uVar2 + 1;
      (**(code **)(*(long *)*puVar1 + 0x50))((long *)*puVar1,param_1);
    } while (uVar2 < *(uint *)(this + 0x140));
  }
  return;
}



/* address=005939d0
   symbol=CPathController::getClosestPctOfPath */

/* CPathController::getClosestPctOfPath(Ogre::Vector3 const&) */

float __thiscall CPathController::getClosestPctOfPath(CPathController *this,Vector3 *param_1)

{
  uint uVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  uint uVar5;
  float fVar6;

  if (((this[0x135] != (CPathController)0x0) || (*(int *)(this + 0x158) == 1)) ||
     (fVar6 = *(float *)(this + 0x180), fVar6 == 0.0)) {
    return DAT_00fa47fc;
  }
  if (*(int *)(this + 0x158) != 0) {
    uVar5 = 0;
    do {
      while( true ) {
        uVar1 = *(uint *)(this + 0x15c);
        if (uVar5 + 2 < uVar1) {
          pfVar2 = *(float **)(this + 0x150);
          pfVar3 = pfVar2 + (uVar5 + 2);
        }
        else {
          pfVar2 = *(float **)(this + 0x150);
          pfVar3 = pfVar2;
        }
        pfVar4 = pfVar2;
        if (uVar5 + 1 < uVar1) {
          pfVar4 = pfVar2 + (uVar5 + 1);
        }
        if (uVar5 < uVar1) {
          pfVar2 = pfVar2 + uVar5;
        }
        fVar6 = (*pfVar2 - *(float *)param_1) * (*pfVar2 - *(float *)param_1) +
                (*pfVar4 - *(float *)(param_1 + 4)) * (*pfVar4 - *(float *)(param_1 + 4)) +
                (*pfVar3 - *(float *)(param_1 + 8)) * (*pfVar3 - *(float *)(param_1 + 8));
        if ((fVar6 < 0.0) && (NAN(SQRT(fVar6)))) break;
        uVar5 = uVar5 + 3;
        if (*(uint *)(this + 0x158) <= uVar5) goto LAB_00593ae6;
      }
      uVar5 = uVar5 + 3;
      sqrtf(fVar6);
    } while (uVar5 < *(uint *)(this + 0x158));
LAB_00593ae6:
    fVar6 = *(float *)(this + 0x180);
  }
  return **(float **)(this + 0x168) / fVar6;
}



/* address=00593b10
   symbol=CPathController::caculatePointInFrontOfPlayer */

/* CPathController::caculatePointInFrontOfPlayer(CBaseUnit*) */

float CPathController::caculatePointInFrontOfPlayer(CBaseUnit *param_1)

{
  CPositionableObject *this;
  long lVar1;
  long in_RSI;
  float fVar2;
  float fVar3;
  float fVar4;
  float in_XMM1_Da;

  fVar2 = (float)CPositionableObject::getPosition((CPositionableObject *)param_1,true);
  if (((*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) &&
      (lVar1 = **(long **)(*(long *)(param_1 + 0x68) + 0x28), lVar1 != 0)) &&
     (this = *(CPositionableObject **)(lVar1 + 0x58), this != (CPositionableObject *)0x0)) {
    fVar4 = in_XMM1_Da;
    fVar3 = (float)CPositionableObject::getPosition(this,true);
    fVar2 = fVar2 - fVar3;
    fVar4 = SQRT(fVar2 * fVar2 + DAT_00fa47f8 + (in_XMM1_Da - fVar4) * (in_XMM1_Da - fVar4));
    if (DAT_00fa87a0 < (double)fVar4) {
      fVar2 = fVar2 * (DAT_00fa47fc / fVar4);
    }
    lVar1 = 0;
    if (*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) {
      lVar1 = **(long **)(*(long *)(param_1 + 0x68) + 0x28);
    }
    fVar4 = *(float *)(*(long *)(lVar1 + 0x58) + 0x194) + *(float *)(in_RSI + 0x194);
    fVar2 = fVar2 * (fVar4 + fVar4) + fVar3;
  }
  return fVar2;
}



/* address=00593c80
   symbol=CPathController::getNextPointAtPercent */

/* CPathController::getNextPointAtPercent(float, CBaseUnit*, bool) */

undefined8 __thiscall
CPathController::getNextPointAtPercent
          (CPathController *this,float param_1,CBaseUnit *param_2,bool param_3)

{
  uint uVar1;
  uint uVar2;
  long lVar3;
  float *pfVar4;
  float *pfVar5;
  float fVar6;
  undefined8 uVar7;
  undefined8 local_38;
  float local_28;
  float fStack_24;

  if (this[0x135] != (CPathController)0x0) {
    uVar7 = caculatePointInFrontOfPlayer((CBaseUnit *)this);
    local_38._4_4_ = (float)((ulong)uVar7 >> 0x20);
    local_38._0_4_ = (float)uVar7;
    goto LAB_00593dd8;
  }
  if (0.0 < param_1) {
    if (DAT_00fa47fc <= param_1) {
      param_1 = DAT_00fa47fc;
    }
  }
  else {
    param_1 = 0.0;
  }
  uVar7 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x48),true);
  local_28 = (float)uVar7;
  fStack_24 = (float)((ulong)uVar7 >> 0x20);
  if (!param_3) {
    uVar2 = *(uint *)(this + 0x170);
    do {
      uVar2 = uVar2 - 1;
      if (*(float *)(this + 0x180) == 0.0) {
        if (uVar2 < *(uint *)(this + 0x174)) {
          pfVar5 = (float *)((ulong)uVar2 * 4 + *(long *)(this + 0x168));
        }
        else {
          pfVar5 = *(float **)(this + 0x168);
        }
        fVar6 = *pfVar5;
      }
      else {
        if (uVar2 < *(uint *)(this + 0x174)) {
          pfVar5 = (float *)((ulong)uVar2 * 4 + *(long *)(this + 0x168));
        }
        else {
          pfVar5 = *(float **)(this + 0x168);
        }
        fVar6 = *pfVar5 / *(float *)(this + 0x180);
      }
    } while (param_1 < fVar6);
LAB_00593d88:
    uVar2 = uVar2 * 3;
    uVar1 = *(uint *)(this + 0x15c);
    if (uVar2 + 2 < uVar1) {
      pfVar5 = *(float **)(this + 0x150);
    }
    else {
      pfVar5 = *(float **)(this + 0x150);
    }
    pfVar4 = pfVar5;
    if (uVar2 + 1 < uVar1) {
      pfVar4 = pfVar5 + (uVar2 + 1);
    }
    if (uVar2 < uVar1) {
      pfVar5 = pfVar5 + uVar2;
    }
    local_38._4_4_ = *pfVar4 + fStack_24;
    local_38._0_4_ = *pfVar5 + local_28;
    goto LAB_00593dd8;
  }
  if (*(uint *)(this + 0x170) != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (*(float *)(this + 0x180) == 0.0) {
        if (uVar2 < *(uint *)(this + 0x174)) {
          pfVar5 = (float *)(lVar3 + *(long *)(this + 0x168));
        }
        else {
          pfVar5 = *(float **)(this + 0x168);
        }
        fVar6 = *pfVar5;
      }
      else {
        if (uVar2 < *(uint *)(this + 0x174)) {
          pfVar5 = (float *)(lVar3 + *(long *)(this + 0x168));
        }
        else {
          pfVar5 = *(float **)(this + 0x168);
        }
        fVar6 = *pfVar5 / *(float *)(this + 0x180);
      }
      if (param_1 <= fVar6) goto LAB_00593d88;
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 4;
    } while (uVar2 < *(uint *)(this + 0x170));
  }
  if (*(uint *)(this + 0x15c) < 3) {
    pfVar5 = *(float **)(this + 0x150);
    local_38._4_4_ = *pfVar5;
    if (*(uint *)(this + 0x15c) == 2) goto LAB_00593f15;
  }
  else {
    pfVar5 = *(float **)(this + 0x150);
LAB_00593f15:
    local_38._4_4_ = pfVar5[1];
  }
  local_38._4_4_ = local_38._4_4_ + fStack_24;
  local_38._0_4_ = *pfVar5 + local_28;
LAB_00593dd8:
  return local_38;
}



/* address=00593f50
   symbol=CPathController::childNodeMoved */

/* CPathController::childNodeMoved() */

void CPathController::childNodeMoved(void)

{
  CPositionableObject *in_RDI;
  undefined8 local_18 [2];

  if ((*(int *)(in_RDI + 0x140) != 0) &&
     ((CPositionableObject *)**(undefined8 **)(in_RDI + 0x138) != (CPositionableObject *)0x0)) {
    local_18[0] = CPositionableObject::getPosition
                            ((CPositionableObject *)**(undefined8 **)(in_RDI + 0x138),true);
    CPositionableObject::setPosition(in_RDI,(Vector3 *)local_18);
  }
  return;
}



/* address=00593fc0
   symbol=CPathController::positionUpdated */

/* CPathController::positionUpdated(Ogre::Vector3 const&) */

void CPathController::positionUpdated(Vector3 *param_1)

{
  Vector3 *in_RSI;
  undefined8 uVar1;
  float in_XMM1_Da;
  float fVar2;

  if (*(int *)(param_1 + 0x140) != 0) {
    uVar1 = CPositionableObject::getPosition
                      ((CPositionableObject *)**(undefined8 **)(param_1 + 0x138),false);
    fVar2 = (float)((ulong)uVar1 >> 0x20);
    if (((((float)uVar1 != *(float *)in_RSI) || (NAN((float)uVar1) || NAN(*(float *)in_RSI))) ||
        (fVar2 != *(float *)(in_RSI + 4))) ||
       ((NAN(fVar2) || NAN(*(float *)(in_RSI + 4)) || (in_XMM1_Da != *(float *)(in_RSI + 8))))) {
      *(undefined8 *)(**(long **)(param_1 + 0x138) + 0x100) = 0;
      CPositionableObject::setPosition
                ((CPositionableObject *)**(undefined8 **)(param_1 + 0x138),in_RSI);
      *(Vector3 **)(**(long **)(param_1 + 0x138) + 0x100) = param_1;
      return;
    }
  }
  return;
}



/* address=005940a0
   symbol=CPathController::setUnitInteractWith */

/* CPathController::setUnitInteractWith(std::wstring) */

void __thiscall
CPathController::setUnitInteractWith(CPathController *this,wstring_conflict *param_2)

{
  CPathController *pCVar1;
  long lVar2;
  TSafePointer *pTVar3;
  int iVar4;
  undefined8 *puVar5;
  CUnitResourceList *this_00;
  undefined8 uVar6;
  uint uVar7;

  if (*(long *)(this + 0x68) != 0) {
    std::wstring::assign((wstring_conflict *)(this + 0x128));
    iVar4 = std::wstring::compare((wchar_t *)(this + 0x128));
    if (iVar4 == 0) {
      *(undefined8 *)(this + 0x100) = 0;
      this[0x137] = (CPathController)0x1;
    }
    else {
      this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
      uVar6 = CUnitResourceList::getDataGroupByObjectName(this_00,param_2);
      this[0x137] = (CPathController)0x0;
      *(undefined8 *)(this + 0x100) = uVar6;
    }
    pCVar1 = this + 0x108;
    if (*(int *)(this + 0x110) != 0) {
      uVar7 = 0;
      do {
        lVar2 = (ulong)uVar7 * 8;
        puVar5 = (undefined8 *)(lVar2 + *(long *)pCVar1);
        pTVar3 = (TSafePointer *)*puVar5;
        if (pTVar3 != (TSafePointer *)0x0) {
          if (*(CRunicCore **)pTVar3 != (CRunicCore *)0x0) {
                    /* try { // try from 00594138 to 0059413c has its CatchHandler @ 005941e4 */
            CRunicCore::removeSafePointer(*(CRunicCore **)pTVar3,pTVar3,*(uint *)(pTVar3 + 8));
          }
          *(undefined8 *)pTVar3 = 0;
          *(undefined4 *)(pTVar3 + 8) = 0xffffffff;
          Ogre::NedAllocImpl::deallocBytes(pTVar3);
          *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar7 * 8) = 0;
          puVar5 = (undefined8 *)(lVar2 + *(long *)pCVar1);
        }
        *puVar5 = 0;
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(this + 0x110));
    }
    *(undefined4 *)(this + 0x110) = 0;
    *(undefined4 *)(this + 0x114) = 0;
    if (*(void **)(this + 0x108) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x108));
    }
    *(undefined8 *)(this + 0x108) = 0;
  }
  return;
}



/* address=005941f0
   symbol=CPathController::CPathController */

/* CPathController::CPathController(CResourceManager*) */

void __thiscall CPathController::CPathController(CPathController *this,CResourceManager *param_1)

{
  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CPathController_00faa610;
  *(undefined8 *)(this + 0x100) = 0;
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  *(undefined4 *)(this + 0x118) = 5;
                    /* try { // try from 00594248 to 0059424c has its CatchHandler @ 0059433c */
  std::wstring::wstring
            ((wstring_conflict *)(this + 0x120),(wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8));
  *(undefined4 **)(this + 0x128) = &DAT_01424558;
  this[0x130] = (CPathController)0x0;
  this[0x131] = (CPathController)0x0;
  this[0x132] = (CPathController)0x0;
  this[0x133] = (CPathController)0x1;
  this[0x134] = (CPathController)0x1;
  this[0x135] = (CPathController)0x0;
  this[0x136] = (CPathController)0x0;
  this[0x137] = (CPathController)0x0;
  *(undefined8 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x140) = 0;
  *(undefined4 *)(this + 0x144) = 0;
  *(undefined4 *)(this + 0x148) = 10;
  *(undefined8 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x158) = 0;
  *(undefined4 *)(this + 0x15c) = 0;
  *(undefined4 *)(this + 0x160) = 0x15;
  *(undefined8 *)(this + 0x168) = 0;
  *(undefined4 *)(this + 0x170) = 0;
  *(undefined4 *)(this + 0x174) = 0;
  *(undefined4 *)(this + 0x178) = 10;
  *(undefined4 *)(this + 0x180) = 0;
                    /* try { // try from 00594321 to 00594325 has its CatchHandler @ 0059436b */
  std::wstring::wstring((wstring_conflict *)(this + 0x188),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 400) = 0;
  this[0x194] = (CPathController)0x0;
  return;
}



/* address=0059bc30
   symbol=CPathController::_GLOBAL__I_CPathController */

/* CPathController::CPathController(CResourceManager*) */

void CPathController::_GLOBAL__I_CPathController(void)

{
  allocator aStack_2ce;
  allocator aStack_2cd;
  allocator aStack_2cc;
  allocator aStack_2cb;
  allocator aStack_2ca;
  allocator aStack_2c9;
  allocator aStack_2c8;
  allocator aStack_2c7;
  allocator aStack_2c6;
  allocator aStack_2c5;
  allocator aStack_2c4;
  allocator aStack_2c3;
  allocator aStack_2c2;
  allocator aStack_2c1;
  allocator aStack_2c0;
  allocator aStack_2bf;
  allocator aStack_2be;
  allocator aStack_2bd;
  allocator aStack_2bc;
  allocator aStack_2bb;
  allocator aStack_2ba;
  allocator aStack_2b9;
  allocator aStack_2b8;
  allocator aStack_2b7;
  allocator aStack_2b6;
  allocator aStack_2b5;
  allocator aStack_2b4;
  allocator aStack_2b3;
  allocator aStack_2b2;
  allocator aStack_2b1;
  allocator aStack_2b0;
  allocator aStack_2af;
  allocator aStack_2ae;
  allocator aStack_2ad;
  allocator aStack_2ac;
  allocator aStack_2ab;
  allocator aStack_2aa;
  allocator aStack_2a9;
  allocator aStack_2a8;
  allocator aStack_2a7;
  allocator aStack_2a6;
  allocator aStack_2a5;
  allocator aStack_2a4;
  allocator aStack_2a3;
  allocator aStack_2a2;
  allocator aStack_2a1;
  allocator aStack_2a0;
  allocator aStack_29f;
  allocator aStack_29e;
  allocator aStack_29d;
  allocator aStack_29c;
  allocator aStack_29b;
  allocator aStack_29a;
  allocator aStack_299;
  allocator aStack_298;
  allocator aStack_297;
  allocator aStack_296;
  allocator aStack_295;
  allocator aStack_294;
  allocator aStack_293;
  allocator aStack_292;
  allocator aStack_291;
  allocator aStack_290;
  allocator aStack_28f;
  allocator aStack_28e;
  allocator aStack_28d;
  allocator aStack_28c;
  allocator aStack_28b;
  allocator aStack_28a;
  allocator aStack_289;
  allocator aStack_288;
  allocator aStack_287;
  allocator aStack_286;
  allocator aStack_285;
  allocator aStack_284;
  allocator aStack_283;
  allocator aStack_282;
  allocator aStack_281;
  allocator aStack_280;
  allocator aStack_27f;
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
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_2ce);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_2cd);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_2cc)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_2cb);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_2ca)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_2c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_2c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_2c7);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_2c6);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_2c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_2c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_2c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_2c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_2c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_2c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_2bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_2bc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_2bb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_2ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_2b9);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_2b6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_2b4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_2b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_2b0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_2af);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_2ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_2ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_2ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_2aa)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_2a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_2a8);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_2a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_2a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_2a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_2a4);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_2a3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_2a2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_2a1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_2a0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_29f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_29e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_29d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_29c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_29b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_29a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_299);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_298);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_28e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_28d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_28c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_28b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_28a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_289);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_288);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_237);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_235);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_234);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_233);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_230);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_22b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_229)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_228)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_227)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_226)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_225)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_224)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_21f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_216)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_214)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_213);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_212);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_208
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_206);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_205
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_202)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_200
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1ff)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1fe);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1f6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1f5);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1ee);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1e7);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1e0);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)&DAT_01428f48,L"ITEM",&aStack_1de);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1da)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1d3);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_f1);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_ef)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_ed)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_e2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_dd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_cf);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_cb);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_c5);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_c2);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_bc);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_bb);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_ba);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_b9
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_b8);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_b7);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_b6);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_b5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_b4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_b3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_b2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_b1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_b0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_af);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_ae);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_ad);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_ac);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_ab);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_aa);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_a9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_a8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_a7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_a6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_a5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_a4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_a3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_a2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_a1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_a0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_9f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_9e);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_9d);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_9c);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_9b);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_9a);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_99);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_98);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_97);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_96);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_95);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_94);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_93);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_92);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_8d);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_88);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_87);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_7e)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_74);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_59)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_56);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_4e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_3b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_32);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_31)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_30)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_29)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_28)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_1d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_18)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_9);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  return;
}



/* address=0059be90
   symbol=CPathController::caculateSpline */

/* CPathController::caculateSpline() */

void CPathController::caculateSpline(void)

{
  char cVar1;
  uint uVar2;
  float *pfVar3;
  void *pvVar4;
  uint uVar5;
  float *pfVar6;
  ulong uVar7;
  long in_RDI;
  uint uVar8;
  float in_XMM0_Da;
  float fVar9;
  float in_XMM1_Da;
  float fVar10;
  float in_XMM2_Da;
  float fVar11;

  *(undefined4 *)(in_RDI + 0x180) = 0;
  if (((*(char *)(in_RDI + 0x135) == '\0') && (*(long *)(in_RDI + 0x48) != 0)) &&
     (cVar1 = CResourceManager::getEditorIsRunning(), cVar1 == '\0')) {
    *(undefined4 *)(in_RDI + 0x170) = 0;
    *(undefined4 *)(in_RDI + 0x174) = 0;
    if (*(void **)(in_RDI + 0x168) != (void *)0x0) {
      operator_delete__(*(void **)(in_RDI + 0x168));
    }
    *(undefined8 *)(in_RDI + 0x168) = 0;
    if (*(int *)(in_RDI + 0x158) != 0) {
      uVar8 = 0;
      uVar2 = *(uint *)(in_RDI + 0x15c);
      uVar5 = 2;
      if (2 < uVar2) goto LAB_0059c0a6;
      do {
        pfVar3 = *(float **)(in_RDI + 0x150);
        pfVar6 = pfVar3;
        fVar9 = in_XMM0_Da;
        fVar10 = in_XMM1_Da;
        fVar11 = in_XMM2_Da;
        uVar5 = uVar8;
        while( true ) {
          in_XMM1_Da = *pfVar6;
          pfVar6 = pfVar3;
          if (uVar5 + 1 < uVar2) {
            pfVar6 = pfVar3 + (uVar5 + 1);
          }
          in_XMM2_Da = *pfVar6;
          if (uVar5 < uVar2) {
            pfVar3 = pfVar3 + uVar5;
          }
          in_XMM0_Da = *pfVar3;
          if (uVar5 == 0) {
            uVar2 = *(uint *)(in_RDI + 0x170);
            if (uVar2 < *(uint *)(in_RDI + 0x174)) {
              pvVar4 = *(void **)(in_RDI + 0x168);
            }
            else if (*(long *)(in_RDI + 0x168) == 0) {
              *(uint *)(in_RDI + 0x174) = *(uint *)(in_RDI + 0x178);
              pvVar4 = operator_new__((ulong)*(uint *)(in_RDI + 0x178) << 2);
              *(void **)(in_RDI + 0x168) = pvVar4;
              uVar2 = *(uint *)(in_RDI + 0x170);
            }
            else {
              uVar8 = *(uint *)(in_RDI + 0x174) + *(int *)(in_RDI + 0x178);
              pvVar4 = operator_new__((ulong)uVar8 << 2);
              if (*(int *)(in_RDI + 0x174) != 0) {
                uVar2 = 0;
                do {
                  uVar7 = (ulong)uVar2;
                  uVar2 = uVar2 + 1;
                  *(undefined4 *)((long)pvVar4 + uVar7 * 4) =
                       *(undefined4 *)(*(long *)(in_RDI + 0x168) + uVar7 * 4);
                } while (uVar2 < *(uint *)(in_RDI + 0x174));
              }
              if (*(void **)(in_RDI + 0x168) != (void *)0x0) {
                operator_delete__(*(void **)(in_RDI + 0x168));
              }
              uVar2 = *(uint *)(in_RDI + 0x170);
              *(void **)(in_RDI + 0x168) = pvVar4;
              *(uint *)(in_RDI + 0x174) = uVar8;
            }
            *(undefined4 *)((long)pvVar4 + (ulong)uVar2 * 4) = 0;
            *(int *)(in_RDI + 0x170) = *(int *)(in_RDI + 0x170) + 1;
          }
          else {
            uVar2 = *(uint *)(in_RDI + 0x170);
            fVar9 = SQRT((in_XMM0_Da - fVar9) * (in_XMM0_Da - fVar9) +
                         (in_XMM2_Da - fVar11) * (in_XMM2_Da - fVar11) +
                         (in_XMM1_Da - fVar10) * (in_XMM1_Da - fVar10)) + *(float *)(in_RDI + 0x180)
            ;
            *(float *)(in_RDI + 0x180) = fVar9;
            if (uVar2 < *(uint *)(in_RDI + 0x174)) {
              pvVar4 = *(void **)(in_RDI + 0x168);
            }
            else if (*(long *)(in_RDI + 0x168) == 0) {
              *(uint *)(in_RDI + 0x174) = *(uint *)(in_RDI + 0x178);
              pvVar4 = operator_new__((ulong)*(uint *)(in_RDI + 0x178) << 2);
              *(void **)(in_RDI + 0x168) = pvVar4;
              uVar2 = *(uint *)(in_RDI + 0x170);
            }
            else {
              uVar8 = *(uint *)(in_RDI + 0x174) + *(int *)(in_RDI + 0x178);
              pvVar4 = operator_new__((ulong)uVar8 << 2);
              if (*(int *)(in_RDI + 0x174) != 0) {
                uVar2 = 0;
                do {
                  uVar7 = (ulong)uVar2;
                  uVar2 = uVar2 + 1;
                  *(undefined4 *)((long)pvVar4 + uVar7 * 4) =
                       *(undefined4 *)(*(long *)(in_RDI + 0x168) + uVar7 * 4);
                } while (uVar2 < *(uint *)(in_RDI + 0x174));
              }
              if (*(void **)(in_RDI + 0x168) != (void *)0x0) {
                operator_delete__(*(void **)(in_RDI + 0x168));
              }
              uVar2 = *(uint *)(in_RDI + 0x170);
              *(void **)(in_RDI + 0x168) = pvVar4;
              *(uint *)(in_RDI + 0x174) = uVar8;
            }
            *(float *)((long)pvVar4 + (ulong)uVar2 * 4) = fVar9;
            *(int *)(in_RDI + 0x170) = *(int *)(in_RDI + 0x170) + 1;
          }
          uVar8 = uVar5 + 3;
          if (*(uint *)(in_RDI + 0x158) <= uVar8) {
            return;
          }
          uVar2 = *(uint *)(in_RDI + 0x15c);
          uVar5 = uVar5 + 5;
          if (uVar2 <= uVar5) break;
LAB_0059c0a6:
          pfVar3 = *(float **)(in_RDI + 0x150);
          pfVar6 = pfVar3 + uVar5;
          fVar9 = in_XMM0_Da;
          fVar10 = in_XMM1_Da;
          fVar11 = in_XMM2_Da;
          uVar5 = uVar8;
        }
      } while( true );
    }
  }
  return;
}



/* address=0059c2e0
   symbol=CPathController::setEnabled */

/* CPathController::setEnabled(bool) */

void CPathController::setEnabled(bool param_1)

{
  long *plVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  TSafePointer *pTVar5;
  void *pvVar6;
  long *plVar7;
  CRunicCore *pCVar8;
  ulong uVar9;
  uint uVar10;
  CPositionableObject in_SIL;
  undefined7 in_register_00000039;
  CPositionableObject *this;
  uint uVar11;
  uint uVar12;
  long *local_68;
  uint local_60;
  uint local_5c;
  undefined4 local_58;
  undefined8 local_48 [3];

  this = (CPositionableObject *)CONCAT71(in_register_00000039,param_1);
  if (this[0x133] != in_SIL) {
    this[0x133] = in_SIL;
    (**(code **)(*(long *)this + 0x30))();
    if (*(int *)(this + 0x110) == 0) {
      if (this[0x137] == (CPositionableObject)0x0) {
        local_68 = (long *)0x0;
        local_60 = 0;
        local_5c = 0;
        local_58 = 100;
                    /* try { // try from 0059c61a to 0059c688 has its CatchHandler @ 0059c830 */
        CLevel::getBaseUnitsByDataGroup
                  (*(CLevel **)(*(long *)(this + 0x68) + 0x18),*(CDataGroup **)(this + 0x100),
                   (TArrayList *)&local_68);
        if (local_60 != 0) {
          uVar10 = 0;
          do {
            plVar7 = local_68;
            if (uVar10 < local_5c) {
              plVar7 = local_68 + uVar10;
            }
            if ((*plVar7 != 0) &&
               (pCVar8 = (CRunicCore *)
                         __dynamic_cast(*plVar7,&CBaseUnit::typeinfo,&CCharacter::typeinfo),
               pCVar8 != (CRunicCore *)0x0)) {
              pTVar5 = (TSafePointer *)
                       Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
              *(undefined4 *)(pTVar5 + 8) = 0xffffffff;
              *(undefined8 *)pTVar5 = 0;
                    /* try { // try from 0059c6a0 to 0059c6a4 has its CatchHandler @ 0059c814 */
              uVar2 = CRunicCore::addSafePointer(pCVar8,pTVar5);
              *(undefined4 *)(pTVar5 + 8) = uVar2;
              *(CRunicCore **)pTVar5 = pCVar8;
              uVar11 = *(uint *)(this + 0x110);
              if (uVar11 < *(uint *)(this + 0x114)) {
                pvVar6 = *(void **)(this + 0x108);
              }
              else if (*(long *)(this + 0x108) == 0) {
                *(uint *)(this + 0x114) = *(uint *)(this + 0x118);
                pvVar6 = operator_new__((ulong)*(uint *)(this + 0x118) * 8);
                *(void **)(this + 0x108) = pvVar6;
                uVar11 = *(uint *)(this + 0x110);
              }
              else {
                uVar12 = *(uint *)(this + 0x114) + *(int *)(this + 0x118);
                    /* try { // try from 0059c6e0 to 0059c7c0 has its CatchHandler @ 0059c830 */
                pvVar6 = operator_new__((ulong)uVar12 << 3);
                if (*(int *)(this + 0x114) != 0) {
                  uVar9 = 0;
                  do {
                    uVar11 = (int)uVar9 + 1;
                    *(undefined8 *)((long)pvVar6 + uVar9 * 8) =
                         *(undefined8 *)(*(long *)(this + 0x108) + uVar9 * 8);
                    uVar9 = (ulong)uVar11;
                  } while (uVar11 < *(uint *)(this + 0x114));
                }
                if (*(void **)(this + 0x108) != (void *)0x0) {
                  operator_delete__(*(void **)(this + 0x108));
                }
                uVar11 = *(uint *)(this + 0x110);
                *(void **)(this + 0x108) = pvVar6;
                *(uint *)(this + 0x114) = uVar12;
              }
              *(TSafePointer **)((long)pvVar6 + (ulong)uVar11 * 8) = pTVar5;
              *(int *)(this + 0x110) = *(int *)(this + 0x110) + 1;
            }
            uVar10 = uVar10 + 1;
          } while (uVar10 < local_60);
        }
        if (local_68 != (long *)0x0) {
          operator_delete__(local_68);
          local_68 = (long *)0x0;
        }
        iVar3 = *(int *)(this + 0x110);
      }
      else {
        lVar4 = 0;
        if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
          lVar4 = **(long **)(*(long *)(this + 0x68) + 0x28);
        }
        pCVar8 = *(CRunicCore **)(lVar4 + 0x58);
        if (pCVar8 == (CRunicCore *)0x0) {
          return;
        }
        (**(code **)(*(long *)pCVar8 + 0x348))(pCVar8);
        pTVar5 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
        *(undefined4 *)(pTVar5 + 8) = 0xffffffff;
        *(undefined8 *)pTVar5 = 0;
                    /* try { // try from 0059c4e0 to 0059c4e4 has its CatchHandler @ 0059c801 */
        uVar2 = CRunicCore::addSafePointer(pCVar8,pTVar5);
        *(CRunicCore **)pTVar5 = pCVar8;
        *(undefined4 *)(pTVar5 + 8) = uVar2;
        uVar10 = *(uint *)(this + 0x110);
        if (uVar10 < *(uint *)(this + 0x114)) {
          pvVar6 = *(void **)(this + 0x108);
        }
        else if (*(long *)(this + 0x108) == 0) {
          *(uint *)(this + 0x114) = *(uint *)(this + 0x118);
          pvVar6 = operator_new__((ulong)*(uint *)(this + 0x118) * 8);
          *(void **)(this + 0x108) = pvVar6;
          uVar10 = *(uint *)(this + 0x110);
        }
        else {
          uVar11 = *(uint *)(this + 0x114) + *(int *)(this + 0x118);
          pvVar6 = operator_new__((ulong)uVar11 << 3);
          if (*(int *)(this + 0x114) != 0) {
            uVar10 = 0;
            do {
              uVar9 = (ulong)uVar10;
              uVar10 = uVar10 + 1;
              *(undefined8 *)((long)pvVar6 + uVar9 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x108) + uVar9 * 8);
            } while (uVar10 < *(uint *)(this + 0x114));
          }
          if (*(void **)(this + 0x108) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x108));
          }
          uVar10 = *(uint *)(this + 0x110);
          *(void **)(this + 0x108) = pvVar6;
          *(uint *)(this + 0x114) = uVar11;
        }
        *(TSafePointer **)((long)pvVar6 + (ulong)uVar10 * 8) = pTVar5;
        iVar3 = *(int *)(this + 0x110) + 1;
        *(int *)(this + 0x110) = iVar3;
      }
      if (iVar3 == 0) {
        return;
      }
    }
    uVar10 = 0;
    do {
      while (*(uint *)(this + 0x114) <= uVar10) {
        plVar7 = (long *)**(undefined8 **)(this + 0x108);
        if (in_SIL == (CPositionableObject)0x0) goto LAB_0059c347;
LAB_0059c396:
        caculateSpline();
        this[0x136] = (CPositionableObject)0x0;
        if (this[0x135] == (CPositionableObject)0x0) {
          CCharacter::setTarget((CCharacter *)*plVar7,(CCharacter *)0x0);
        }
        else {
          local_48[0] = CPositionableObject::getPosition((CPositionableObject *)*plVar7,true);
          CPositionableObject::setPosition(this,(Vector3 *)local_48);
          lVar4 = 0;
          if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
            lVar4 = **(long **)(*(long *)(this + 0x68) + 0x28);
          }
          CCharacter::setTarget((CCharacter *)*plVar7,*(CCharacter **)(lVar4 + 0x58));
        }
        CCharacter::stopPathing((CCharacter *)*plVar7);
        CCharacter::setTargetItem((CCharacter *)*plVar7,(CItem *)0x0);
        (**(code **)(*(long *)*plVar7 + 0x310))((long *)*plVar7,this);
        (**(code **)(*(long *)*plVar7 + 0x348))();
        if (this[0x194] != (CPositionableObject)0x0) goto LAB_0059c452;
LAB_0059c36a:
        uVar10 = uVar10 + 1;
        if (*(uint *)(this + 0x110) <= uVar10) {
          return;
        }
      }
      plVar7 = *(long **)((ulong)uVar10 * 8 + *(long *)(this + 0x108));
      if (in_SIL != (CPositionableObject)0x0) goto LAB_0059c396;
LAB_0059c347:
      plVar1 = (long *)*plVar7;
      if ((plVar1 != (long *)0x0) && (this == (CPositionableObject *)plVar1[0xea])) {
        (**(code **)(*plVar1 + 0x310))();
      }
      if (this[0x194] == (CPositionableObject)0x0) goto LAB_0059c36a;
LAB_0059c452:
      uVar10 = uVar10 + 1;
      (**(code **)(*(long *)*plVar7 + 0x40))();
    } while (uVar10 < *(uint *)(this + 0x110));
  }
  return;
}



/* address=0059c840
   symbol=CPathController::initPathController */

/* CPathController::initPathController() */

void __thiscall CPathController::initPathController(CPathController *this)

{
  char cVar1;

  cVar1 = CResourceManager::getEditorIsRunning();
  if (cVar1 == '\0') {
    caculateSpline();
    if (this[0x133] != (CPathController)0x0) {
      this[0x133] = (CPathController)0x0;
                    /* WARNING: Could not recover jumptable at 0x0059c880. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)this + 0x40))(this,1);
      return;
    }
  }
  return;
}



/* address=0059c890
   symbol=CPathController::getArrayOfVectors */

/* CPathController::getArrayOfVectors(unsigned int&) */

undefined8 CPathController::getArrayOfVectors(uint *param_1)

{
  uint *puVar1;
  char cVar2;
  void *pvVar3;
  undefined8 *puVar4;
  ulong uVar5;
  uint uVar6;
  uint *in_RSI;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 extraout_XMM0_Db;
  undefined4 in_XMM1_Da;
  undefined4 uVar10;

  cVar2 = CResourceManager::getEditorIsRunning();
  if (cVar2 != '\0') {
    param_1[0x56] = 0;
    param_1[0x57] = 0;
    if (*(void **)(param_1 + 0x54) != (void *)0x0) {
      operator_delete__(*(void **)(param_1 + 0x54));
    }
    param_1[0x54] = 0;
    param_1[0x55] = 0;
    if (param_1[0x50] != 0) {
      puVar1 = param_1 + 0x54;
      uVar7 = 0;
      do {
        if (uVar7 < param_1[0x51]) {
          puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(param_1 + 0x4e));
        }
        else {
          puVar4 = *(undefined8 **)(param_1 + 0x4e);
        }
        uVar9 = CPositionableObject::getPosition((CPositionableObject *)*puVar4,false);
        uVar6 = param_1[0x56];
        if (uVar6 < param_1[0x57]) {
          pvVar3 = *(void **)(param_1 + 0x54);
          uVar10 = in_XMM1_Da;
        }
        else if (*(long *)(param_1 + 0x54) == 0) {
          param_1[0x57] = param_1[0x58];
          pvVar3 = operator_new__((ulong)param_1[0x58] << 2);
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
          uVar10 = in_XMM1_Da;
        }
        else {
          uVar8 = param_1[0x57] + param_1[0x58];
          pvVar3 = operator_new__((ulong)uVar8 << 2);
          if (param_1[0x57] != 0) {
            uVar5 = 0;
            do {
              uVar6 = (int)uVar5 + 1;
              *(undefined4 *)((long)pvVar3 + uVar5 * 4) =
                   *(undefined4 *)(*(long *)puVar1 + uVar5 * 4);
              uVar5 = (ulong)uVar6;
            } while (uVar6 < param_1[0x57]);
          }
          if (*(void **)(param_1 + 0x54) != (void *)0x0) {
            operator_delete__(*(void **)(param_1 + 0x54));
          }
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
          param_1[0x57] = uVar8;
          uVar10 = in_XMM1_Da;
        }
        *(undefined4 *)((long)pvVar3 + (ulong)uVar6 * 4) = uVar9;
        param_1[0x56] = param_1[0x56] + 1;
        if (uVar7 < param_1[0x51]) {
          puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(param_1 + 0x4e));
        }
        else {
          puVar4 = *(undefined8 **)(param_1 + 0x4e);
        }
        CPositionableObject::getPosition((CPositionableObject *)*puVar4,false);
        uVar6 = param_1[0x56];
        if (uVar6 < param_1[0x57]) {
          pvVar3 = *(void **)(param_1 + 0x54);
        }
        else if (*(long *)(param_1 + 0x54) == 0) {
          param_1[0x57] = param_1[0x58];
          pvVar3 = operator_new__((ulong)param_1[0x58] << 2);
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
        }
        else {
          uVar8 = param_1[0x57] + param_1[0x58];
          pvVar3 = operator_new__((ulong)uVar8 << 2);
          if (param_1[0x57] != 0) {
            uVar6 = 0;
            do {
              uVar5 = (ulong)uVar6;
              uVar6 = uVar6 + 1;
              *(undefined4 *)((long)pvVar3 + uVar5 * 4) =
                   *(undefined4 *)(*(long *)puVar1 + uVar5 * 4);
            } while (uVar6 < param_1[0x57]);
          }
          if (*(void **)(param_1 + 0x54) != (void *)0x0) {
            operator_delete__(*(void **)(param_1 + 0x54));
          }
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
          param_1[0x57] = uVar8;
        }
        *(undefined4 *)((long)pvVar3 + (ulong)uVar6 * 4) = extraout_XMM0_Db;
        param_1[0x56] = param_1[0x56] + 1;
        if (uVar7 < param_1[0x51]) {
          puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(param_1 + 0x4e));
        }
        else {
          puVar4 = *(undefined8 **)(param_1 + 0x4e);
        }
        CPositionableObject::getPosition((CPositionableObject *)*puVar4,false);
        uVar6 = param_1[0x56];
        in_XMM1_Da = uVar10;
        if (uVar6 < param_1[0x57]) {
          pvVar3 = *(void **)(param_1 + 0x54);
        }
        else if (*(long *)(param_1 + 0x54) == 0) {
          param_1[0x57] = param_1[0x58];
          pvVar3 = operator_new__((ulong)param_1[0x58] << 2);
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
        }
        else {
          uVar8 = param_1[0x57] + param_1[0x58];
          pvVar3 = operator_new__((ulong)uVar8 << 2);
          if (param_1[0x57] != 0) {
            uVar5 = 0;
            do {
              uVar6 = (int)uVar5 + 1;
              *(undefined4 *)((long)pvVar3 + uVar5 * 4) =
                   *(undefined4 *)(*(long *)puVar1 + uVar5 * 4);
              uVar5 = (ulong)uVar6;
            } while (uVar6 < param_1[0x57]);
          }
          if (*(void **)(param_1 + 0x54) != (void *)0x0) {
            operator_delete__(*(void **)(param_1 + 0x54));
          }
          uVar6 = param_1[0x56];
          *(void **)(param_1 + 0x54) = pvVar3;
          param_1[0x57] = uVar8;
        }
        uVar7 = uVar7 + 1;
        *(undefined4 *)((long)pvVar3 + (ulong)uVar6 * 4) = uVar10;
        uVar6 = param_1[0x56] + 1;
        param_1[0x56] = uVar6;
      } while (uVar7 < param_1[0x50]);
      goto LAB_0059cbb9;
    }
  }
  uVar6 = param_1[0x56];
LAB_0059cbb9:
  *in_RSI = uVar6;
  return *(undefined8 *)(param_1 + 0x54);
}



/* address=0059d750
   symbol=CPathController::~CPathController */

/* WARNING: Removing unreachable block (ram,0x0059da00) */
/* WARNING: Removing unreachable block (ram,0x0059da39) */
/* WARNING: Removing unreachable block (ram,0x0059d9f5) */
/* CPathController::~CPathController() */

void __thiscall CPathController::~CPathController(CPathController *this)

{
  allocator *paVar1;
  int *piVar2;
  CPathController *pCVar3;
  long lVar4;
  int iVar5;
  TSafePointer *pTVar6;
  undefined8 *puVar7;
  uint uVar8;

  *(undefined ***)this = &PTR__CPathController_00faa610;
  *(undefined4 *)(this + 0x140) = 0;
  *(undefined4 *)(this + 0x144) = 0;
  if (*(void **)(this + 0x138) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x138));
  }
  *(undefined8 *)(this + 0x138) = 0;
  pCVar3 = this + 0x108;
  if (*(int *)(this + 0x110) != 0) {
    uVar8 = 0;
    do {
      lVar4 = (ulong)uVar8 * 8;
      puVar7 = (undefined8 *)(lVar4 + *(long *)pCVar3);
      pTVar6 = (TSafePointer *)*puVar7;
      if (pTVar6 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar6 != (CRunicCore *)0x0) {
                    /* try { // try from 0059d7d8 to 0059d7dc has its CatchHandler @ 0059d91c */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar6,pTVar6,*(uint *)(pTVar6 + 8));
        }
        *(undefined8 *)pTVar6 = 0;
        *(undefined4 *)(pTVar6 + 8) = 0xffffffff;
                    /* try { // try from 0059d7ee to 0059d7f2 has its CatchHandler @ 0059da34 */
        Ogre::NedAllocImpl::deallocBytes(pTVar6);
        *(undefined8 *)(*(long *)pCVar3 + (ulong)uVar8 * 8) = 0;
        puVar7 = (undefined8 *)(lVar4 + *(long *)pCVar3);
      }
      *puVar7 = 0;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x110));
  }
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  if (*(void **)(this + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x108));
  }
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined8 *)(this + 0x100) = 0;
  paVar1 = (allocator *)(*(long *)(this + 0x188) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x188) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x168) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x168));
    *(undefined8 *)(this + 0x168) = 0;
  }
  if (*(void **)(this + 0x150) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x150));
    *(undefined8 *)(this + 0x150) = 0;
  }
  if (*(void **)(this + 0x138) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x138));
    *(undefined8 *)(this + 0x138) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x128) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x128) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x120) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x120) + -8);
    iVar5 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x108));
    *(undefined8 *)(this + 0x108) = 0;
  }
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}



/* address=0059da50
   symbol=CPathController::~CPathController */

/* CPathController::~CPathController() */

void __thiscall CPathController::~CPathController(CPathController *this)

{
  ~CPathController(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=0059da70
   symbol=CPathController::setPathName */

/* WARNING: Removing unreachable block (ram,0x0059e86c) */
/* WARNING: Removing unreachable block (ram,0x0059e90d) */
/* WARNING: Removing unreachable block (ram,0x0059e8d4) */
/* WARNING: Removing unreachable block (ram,0x0059e85c) */
/* WARNING: Removing unreachable block (ram,0x0059e7dd) */
/* WARNING: Removing unreachable block (ram,0x0059e8e2) */
/* WARNING: Removing unreachable block (ram,0x0059e6ea) */
/* CPathController::setPathName(std::wstring const&) */

void CPathController::setPathName(wstring_conflict *param_1)

{
  allocator *paVar1;
  undefined2 *puVar2;
  int *piVar3;
  uint *puVar4;
  short *psVar5;
  byte *pbVar6;
  int iVar7;
  byte bVar8;
  undefined4 *puVar9;
  wstring_conflict *pwVar10;
  ulong uVar11;
  ulong uVar12;
  runtime_error *prVar13;
  undefined8 *puVar14;
  uint uVar15;
  short *psVar16;
  long lVar17;
  long *plVar18;
  byte *pbVar19;
  uint *puVar20;
  short *psVar21;
  long lVar22;
  byte *pbVar23;
  short sVar24;
  short sVar25;
  uint local_18c;
  short *local_188;
  int local_180;
  undefined8 local_178;
  wstring_conflict *local_170;
  undefined2 *local_168;
  undefined4 local_160;
  undefined8 local_158;
  undefined8 local_150;
  Ogre local_148 [32];
  undefined2 *local_128;
  undefined4 local_120;
  undefined8 local_118;
  undefined8 local_110;
  undefined2 *local_108;
  undefined4 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  byte *local_b8 [2];
  wstring_conflict local_a8 [16];
  uint *local_98 [2];
  undefined4 *local_88 [2];
  long local_78 [2];
  byte local_68 [16];
  ushort local_58;
  short local_56;
  undefined2 local_54;
  allocator local_3f [2];
  allocator local_3d [3];
  allocator local_3a;
  allocator local_39 [9];

  std::wstring::assign(param_1 + 0x188);
  if (*(int *)(param_1 + 0x140) != 0) {
    local_18c = 0;
    do {
      if (*(long *)(*(long *)(param_1 + 0x188) + -0x18) == 0) {
        STRINGS::GetValueAsWString((uint)local_78);
        wcslen(L"Node _ ");
        local_88[0] = &DAT_01424558;
                    /* try { // try from 0059db08 to 0059db27 has its CatchHandler @ 0059e61a */
        std::wstring::reserve((ulong)local_88);
        std::wstring::append((wchar_t *)local_88,0xfaa5a8);
        std::wstring::append((wstring_conflict *)local_88);
        if (local_18c < *(uint *)(param_1 + 0x144)) {
          puVar14 = (undefined8 *)((ulong)local_18c * 8 + *(long *)(param_1 + 0x138));
        }
        else {
          puVar14 = *(undefined8 **)(param_1 + 0x138);
        }
                    /* try { // try from 0059db49 to 0059db4d has its CatchHandler @ 0059e857 */
        CPathNode::setText((wstring_conflict *)*puVar14);
        if ((allocator *)(local_88[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = local_88[0] + -2;
          iVar7 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
          }
        }
        if ((allocator *)(local_78[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_78[0] + -8);
          iVar7 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
          }
        }
      }
      else {
        STRINGS::GetValueAsWString((uint)local_98);
        local_168 = &DAT_01426458;
        local_150 = 0;
        local_160 = 0;
        local_158 = 0;
                    /* try { // try from 0059dbf4 to 0059dce5 has its CatchHandler @ 0059e7e8 */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_168,0,
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_Rep::_S_empty_rep_storage,0);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_168,*(ulong *)(local_98[0] + -6));
        puVar4 = local_98[0] + *(long *)(local_98[0] + -6);
        if (local_98[0] != puVar4) {
          sVar25 = 0;
          puVar20 = local_98[0];
          do {
            uVar15 = *puVar20;
            lVar22 = 1;
            sVar24 = (short)uVar15;
            if (0xffff < uVar15) {
              lVar22 = 2;
              sVar25 = ((ushort)(uVar15 - 0x10000) & 0x3ff) + 0xdc00;
              sVar24 = ((ushort)(uVar15 - 0x10000 >> 10) & 0x3ff) + 0xd800;
            }
            lVar17 = *(long *)(local_168 + -0xc);
            uVar11 = lVar17 + 1;
            if ((*(ulong *)(local_168 + -8) < uVar11) || (0 < *(int *)(local_168 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_168,uVar11);
              lVar17 = *(long *)(local_168 + -0xc);
            }
            local_168[lVar17] = sVar24;
            if (local_168 != &DAT_01426458) {
              *(undefined4 *)(local_168 + -4) = 0;
              *(ulong *)(local_168 + -0xc) = uVar11;
              local_168[uVar11] = 0;
            }
            if (lVar22 == 2) {
              lVar22 = *(long *)(local_168 + -0xc);
              uVar11 = lVar22 + 1;
              if ((*(ulong *)(local_168 + -8) < uVar11) || (0 < *(int *)(local_168 + -4))) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_168,uVar11);
                lVar22 = *(long *)(local_168 + -0xc);
              }
              local_168[lVar22] = sVar25;
              if (local_168 != &DAT_01426458) {
                *(undefined4 *)(local_168 + -4) = 0;
                *(ulong *)(local_168 + -0xc) = uVar11;
                local_168[uVar11] = 0;
              }
            }
            puVar20 = puVar20 + 1;
          } while (puVar4 != puVar20);
        }
        local_128 = &DAT_01426458;
        local_110 = 0;
        local_120 = 0;
        local_118 = 0;
                    /* try { // try from 0059dd56 to 0059dd5a has its CatchHandler @ 0059e66c */
        std::string::string((string *)local_b8," _ ",local_39);
                    /* try { // try from 0059dd68 to 0059de1d has its CatchHandler @ 0059e635 */
        uVar11 = Ogre::UTFString::_verifyUTF8((string *)local_b8);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_128,0,*(ulong *)(local_128 + -0xc),0);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_128,uVar11);
        local_68[6] = 0;
        local_54 = 0;
        pbVar23 = local_b8[0] + *(long *)(local_b8[0] + -0x18);
        for (pbVar19 = local_b8[0]; pbVar19 != pbVar23; pbVar19 = pbVar19 + 1) {
          bVar8 = *pbVar19;
          uVar11 = 1;
          if (((((char)bVar8 < '\0') && (uVar11 = 2, (bVar8 & 0xe0) != 0xc0)) &&
              (uVar11 = 3, (bVar8 & 0xf0) != 0xe0)) &&
             ((uVar11 = 4, (bVar8 & 0xf8) != 0xf0 && (uVar11 = 5, (bVar8 & 0xfc) != 0xf8)))) {
            if ((bVar8 & 0xfe) != 0xfc) {
                    /* try { // try from 0059e285 to 0059e289 has its CatchHandler @ 0059e867 */
              std::string::string((string *)local_d8,"invalid UTF-8 sequence header value",local_3d)
              ;
              prVar13 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0059e29d to 0059e2a1 has its CatchHandler @ 0059e697 */
              std::runtime_error::runtime_error(prVar13,(string *)local_d8);
              *(undefined ***)prVar13 = &PTR__invalid_data_00fa4490;
              if ((allocator *)(local_d8[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_d8[0] + -8);
                iVar7 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
                }
              }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0059e2cf to 0059e2d3 has its CatchHandler @ 0059e635 */
              __cxa_throw(prVar13,&Ogre::UTFString::invalid_data::typeinfo,
                          Ogre::UTFString::invalid_data::~invalid_data);
            }
            uVar11 = 6;
          }
          uVar12 = 0;
          do {
            local_68[uVar12] = pbVar19[uVar12];
            uVar12 = uVar12 + 1;
          } while (uVar12 < uVar11);
          local_68[uVar11] = 0;
          if ((char)local_68[0] < '\0') {
            if ((local_68[0] & 0xffffffe0) == 0xc0) {
              uVar15 = local_68[0] & 0x1f;
              uVar11 = 2;
            }
            else {
              uVar15 = (uint)local_68[0];
              if ((uVar15 & 0xfffffff0) == 0xe0) {
                uVar15 = uVar15 & 0xf;
                uVar11 = 3;
              }
              else if ((uVar15 & 0xfffffff8) == 0xf0) {
                uVar15 = uVar15 & 7;
                uVar11 = 4;
              }
              else {
                uVar15 = (uint)local_68[0];
                if ((uVar15 & 0xfffffffc) == 0xf8) {
                  uVar15 = uVar15 & 3;
                  uVar11 = 5;
                }
                else {
                  if ((uVar15 & 0xfffffffe) != 0xfc) {
                    /* try { // try from 0059e348 to 0059e34c has its CatchHandler @ 0059e826 */
                    std::string::string((string *)local_e8,"invalid UTF-8 sequence header value",
                                        local_3f);
                    prVar13 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0059e360 to 0059e364 has its CatchHandler @ 0059e794 */
                    std::runtime_error::runtime_error(prVar13,(string *)local_e8);
                    *(undefined ***)prVar13 = &PTR__invalid_data_00fa4490;
                    if ((allocator *)(local_e8[0] + -0x18) !=
                        (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar3 = (int *)(local_e8[0] + -8);
                      iVar7 = *piVar3;
                      *piVar3 = *piVar3 + -1;
                      UNLOCK();
                      if (iVar7 < 1) {
                        std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                      }
                    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0059e392 to 0059e396 has its CatchHandler @ 0059e635 */
                    __cxa_throw(prVar13,&Ogre::UTFString::invalid_data::typeinfo,
                                Ogre::UTFString::invalid_data::~invalid_data);
                  }
                  uVar15 = uVar15 & 1;
                  uVar11 = 6;
                }
              }
            }
            uVar12 = 1;
            do {
              pbVar6 = local_68 + uVar12;
              if ((*pbVar6 & 0xffffffc0) != 0x80) {
                    /* try { // try from 0059e450 to 0059e454 has its CatchHandler @ 0059e88f */
                std::string::string((string *)local_c8,"bad UTF-8 continuation byte",&local_3a);
                prVar13 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0059e468 to 0059e46c has its CatchHandler @ 0059e877 */
                std::runtime_error::runtime_error(prVar13,(string *)local_c8);
                *(undefined ***)prVar13 = &PTR__invalid_data_00fa4490;
                if ((allocator *)(local_c8[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar3 = (int *)(local_c8[0] + -8);
                  iVar7 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar7 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                  }
                }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0059e49a to 0059e49e has its CatchHandler @ 0059e635 */
                __cxa_throw(prVar13,&Ogre::UTFString::invalid_data::typeinfo,
                            Ogre::UTFString::invalid_data::~invalid_data);
              }
              uVar12 = uVar12 + 1;
              uVar15 = uVar15 << 6 | *pbVar6 & 0x3f;
            } while (uVar12 < uVar11);
            pbVar19 = pbVar19 + (uVar11 - 1);
            if (uVar15 < 0x10000) goto LAB_0059ddff;
            local_56 = ((ushort)(uVar15 - 0x10000) & 0x3ff) + 0xdc00;
            local_58 = ((ushort)(uVar15 - 0x10000 >> 10) & 0x3ff) + 0xd800;
            uVar11 = 2;
          }
          else {
            uVar15 = (uint)local_68[0];
LAB_0059ddff:
            local_58 = (ushort)uVar15;
            uVar11 = 1;
          }
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::append((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    *)&local_128,&local_58,uVar11);
        }
                    /* try { // try from 0059de2f to 0059de33 has its CatchHandler @ 0059e692 */
        std::string::~string((string *)local_b8);
        local_108 = &DAT_01426458;
        local_f0 = 0;
        local_100 = 0;
        local_f8 = 0;
                    /* try { // try from 0059de76 to 0059df86 has its CatchHandler @ 0059e676 */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_108,0,
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_Rep::_S_empty_rep_storage,0);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_108,*(ulong *)(*(long *)(param_1 + 0x188) + -0x18));
        puVar20 = *(uint **)(param_1 + 0x188);
        puVar4 = puVar20 + *(long *)(puVar20 + -6);
        if (puVar20 != puVar4) {
          sVar25 = 0;
          do {
            uVar15 = *puVar20;
            lVar22 = 1;
            sVar24 = (short)uVar15;
            if (0xffff < uVar15) {
              lVar22 = 2;
              sVar25 = ((ushort)(uVar15 - 0x10000) & 0x3ff) + 0xdc00;
              sVar24 = ((ushort)(uVar15 - 0x10000 >> 10) & 0x3ff) + 0xd800;
            }
            lVar17 = *(long *)(local_108 + -0xc);
            uVar11 = lVar17 + 1;
            if ((*(ulong *)(local_108 + -8) < uVar11) || (0 < *(int *)(local_108 + -4))) {
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_108,uVar11);
              lVar17 = *(long *)(local_108 + -0xc);
            }
            local_108[lVar17] = sVar24;
            if (local_108 != &DAT_01426458) {
              *(undefined4 *)(local_108 + -4) = 0;
              *(ulong *)(local_108 + -0xc) = uVar11;
              local_108[uVar11] = 0;
            }
            if (lVar22 == 2) {
              lVar22 = *(long *)(local_108 + -0xc);
              uVar11 = lVar22 + 1;
              if ((*(ulong *)(local_108 + -8) < uVar11) || (0 < *(int *)(local_108 + -4))) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_108,uVar11);
                lVar22 = *(long *)(local_108 + -0xc);
              }
              local_108[lVar22] = sVar25;
              if (local_108 != &DAT_01426458) {
                *(undefined4 *)(local_108 + -4) = 0;
                *(ulong *)(local_108 + -0xc) = uVar11;
                local_108[uVar11] = 0;
              }
            }
            puVar20 = puVar20 + 1;
          } while (puVar4 != puVar20);
        }
                    /* try { // try from 0059dfd1 to 0059dfd5 has its CatchHandler @ 0059e8f5 */
        Ogre::operator+(local_148,(UTFString *)&local_108,(UTFString *)&local_128);
                    /* try { // try from 0059dfe8 to 0059dfec has its CatchHandler @ 0059e8ed */
        Ogre::operator+((Ogre *)&local_188,(UTFString *)local_148,(UTFString *)&local_168);
        pwVar10 = local_170;
        if (local_180 != 2) {
          if (local_170 != (wstring_conflict *)0x0) {
            if (local_180 == 3) {
              if (local_170 != (wstring_conflict *)0x0) {
                puVar2 = (undefined2 *)(*(long *)local_170 + -0x18);
                if (puVar2 != &std::
                               basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                               ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar3 = (int *)(*(long *)local_170 + -8);
                  iVar7 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar7 < 1) {
                    operator_delete(puVar2);
                  }
                }
                goto LAB_0059e59f;
              }
            }
            else if ((local_180 == 1) && (local_170 != (wstring_conflict *)0x0)) {
              paVar1 = (allocator *)(*(long *)local_170 + -0x18);
              if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(*(long *)local_170 + -8);
                iVar7 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::string::_Rep::_M_destroy(paVar1);
                }
              }
LAB_0059e59f:
              operator_delete(pwVar10);
            }
            local_170 = (wstring_conflict *)0x0;
            local_178 = 0;
          }
                    /* try { // try from 0059e02b to 0059e1ca has its CatchHandler @ 0059e724 */
          local_170 = operator_new(8);
          *(undefined4 **)local_170 = &DAT_01424558;
          local_180 = 2;
        }
        std::wstring::clear();
        pwVar10 = local_170;
        std::wstring::reserve((ulong)local_170);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_188);
        psVar5 = local_188 + *(long *)(local_188 + -0xc);
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_188);
        if (psVar5 != local_188) {
          plVar18 = (long *)(local_188 + -0xc);
          psVar21 = local_188;
          do {
            if ((-1 < (int)plVar18[2]) &&
               ((ulong *)plVar18 !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage)) {
              if ((int)plVar18[2] != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_188,0,0,0);
                plVar18 = (long *)(local_188 + -0xc);
              }
              *(undefined4 *)(plVar18 + 2) = 0xffffffff;
            }
            lVar22 = (long)psVar21 - (long)local_188 >> 1;
            uVar15 = (ushort)local_188[lVar22] + 0x2800;
            if ((((ushort)uVar15 < 0x400) &&
                (uVar11 = lVar22 + 1, uVar11 < *(ulong *)(local_188 + -0xc))) &&
               ((ushort)(local_188[uVar11] + 0x2400U) < 0x400)) {
              uVar15 = ((ushort)(local_188[uVar11] + 0x2400U) & 0x3ff | (uVar15 & 0x3ff) << 10) +
                       0x10000;
            }
            else {
              uVar15 = (uint)(ushort)local_188[lVar22];
            }
            lVar22 = *(long *)pwVar10;
            lVar17 = *(long *)(lVar22 + -0x18);
            uVar11 = lVar17 + 1;
            if ((*(ulong *)(lVar22 + -0x10) < uVar11) || (0 < *(int *)(lVar22 + -8))) {
              std::wstring::reserve((ulong)pwVar10);
              lVar22 = *(long *)pwVar10;
              lVar17 = *(long *)(lVar22 + -0x18);
            }
            *(uint *)(lVar22 + lVar17 * 4) = uVar15;
            puVar9 = *(undefined4 **)pwVar10;
            if (puVar9 != &DAT_01424558) {
              puVar9[-2] = 0;
              *(ulong *)(puVar9 + -6) = uVar11;
              puVar9[uVar11] = 0;
            }
            plVar18 = (long *)(local_188 + -0xc);
            if ((-1 < *(int *)(local_188 + -4)) &&
               ((ulong *)plVar18 !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage)) {
              if (*(int *)(local_188 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_188,0,0,0);
                plVar18 = (long *)(local_188 + -0xc);
              }
              *(undefined4 *)(plVar18 + 2) = 0xffffffff;
              plVar18 = (long *)(local_188 + -0xc);
            }
            psVar16 = psVar21 + 1;
            if (((psVar16 != local_188 + *plVar18) && ((ushort)(psVar21[1] + 0x2400U) < 0x400)) &&
               ((ushort)(*psVar21 + 0x2800U) < 0x400)) {
              psVar16 = psVar21 + 2;
            }
            psVar21 = psVar16;
          } while (psVar16 != psVar5);
        }
                    /* try { // try from 0059e4ea to 0059e4ee has its CatchHandler @ 0059e724 */
        std::wstring::wstring(local_a8,local_170);
        if (local_18c < *(uint *)(param_1 + 0x144)) {
          puVar14 = (undefined8 *)((ulong)local_18c * 8 + *(long *)(param_1 + 0x138));
        }
        else {
          puVar14 = *(undefined8 **)(param_1 + 0x138);
        }
                    /* try { // try from 0059e50c to 0059e510 has its CatchHandler @ 0059e8fd */
        CPathNode::setText((wstring_conflict *)*puVar14);
                    /* try { // try from 0059e514 to 0059e518 has its CatchHandler @ 0059e724 */
        std::wstring::~wstring(local_a8);
        Ogre::UTFString::~UTFString((UTFString *)&local_188);
        Ogre::UTFString::~UTFString((UTFString *)local_148);
        Ogre::UTFString::~UTFString((UTFString *)&local_108);
        Ogre::UTFString::~UTFString((UTFString *)&local_128);
        Ogre::UTFString::~UTFString((UTFString *)&local_168);
        std::wstring::~wstring((wstring_conflict *)local_98);
      }
      local_18c = local_18c + 1;
    } while (local_18c < *(uint *)(param_1 + 0x140));
  }
  return;
}



/* address=0059e920
   symbol=CPathController::setNumberOfPathPoints */

/* WARNING: Removing unreachable block (ram,0x0059ec59) */
/* CPathController::setNumberOfPathPoints(unsigned int) */

void CPathController::setNumberOfPathPoints(uint param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  long lVar5;
  CEditorBaseObject *this;
  void *pvVar6;
  uint uVar7;
  uint in_ESI;
  ulong uVar8;
  undefined4 in_register_0000003c;
  CPositionableObject *this_00;
  uint uVar9;
  undefined8 local_58 [2];
  long local_48;
  allocator local_39 [9];

  this_00 = (CPositionableObject *)CONCAT44(in_register_0000003c,param_1);
  uVar9 = 100;
  if (in_ESI < 0x65) {
    uVar9 = in_ESI;
  }
  if (*(uint *)(this_00 + 400) != uVar9) {
    *(uint *)(this_00 + 400) = uVar9;
    cVar3 = CResourceManager::getEditorIsRunning();
    if (cVar3 != '\0') {
      while (uVar4 = *(uint *)(this_00 + 0x140), uVar9 < uVar4) {
        CEditorObjectManager::EditorObjectDeleted
                  (*(CEditorObjectManager **)(gEditor + 0x120),
                   (CEditorBaseObject *)**(undefined8 **)(this_00 + 0x138));
        if ((long *)**(long **)(this_00 + 0x138) != (long *)0x0) {
          (**(code **)(*(long *)**(long **)(this_00 + 0x138) + 8))();
          **(undefined8 **)(this_00 + 0x138) = 0;
        }
        uVar4 = 0;
        if (*(int *)(this_00 + 0x140) == 0) break;
        uVar4 = *(int *)(this_00 + 0x140) - 1;
        *(uint *)(this_00 + 0x140) = uVar4;
        **(undefined8 **)(this_00 + 0x138) = (*(undefined8 **)(this_00 + 0x138))[uVar4];
      }
      while (uVar4 < uVar9) {
        while( true ) {
                    /* try { // try from 0059e9f2 to 0059e9f6 has its CatchHandler @ 0059ec54 */
          std::wstring::wstring((wstring_conflict *)&local_48,L"Path Node",local_39);
                    /* try { // try from 0059ea03 to 0059ea07 has its CatchHandler @ 0059ec41 */
          lVar5 = CEditorScene::CreateObjectByDescriptor
                            (*(CEditorScene **)(this_00 + 0x48),(wstring_conflict *)&local_48,true);
          if ((allocator *)(local_48 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_48 + -8);
            iVar2 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar2 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
            }
          }
          if ((lVar5 == 0) ||
             (this = (CEditorBaseObject *)
                     __dynamic_cast(lVar5,&CEditorBaseObject::typeinfo,&CPathNode::typeinfo,0),
             this == (CEditorBaseObject *)0x0)) break;
          uVar4 = *(uint *)(this_00 + 0x140);
          if (uVar4 < *(uint *)(this_00 + 0x144)) {
            pvVar6 = *(void **)(this_00 + 0x138);
          }
          else if (*(long *)(this_00 + 0x138) == 0) {
            *(uint *)(this_00 + 0x144) = *(uint *)(this_00 + 0x148);
            pvVar6 = operator_new__((ulong)*(uint *)(this_00 + 0x148) << 3);
            uVar4 = *(uint *)(this_00 + 0x140);
            *(void **)(this_00 + 0x138) = pvVar6;
          }
          else {
            uVar4 = *(uint *)(this_00 + 0x144) + *(int *)(this_00 + 0x148);
            pvVar6 = operator_new__((ulong)uVar4 << 3);
            if (*(int *)(this_00 + 0x144) != 0) {
              uVar7 = 0;
              do {
                uVar8 = (ulong)uVar7;
                uVar7 = uVar7 + 1;
                *(undefined8 *)((long)pvVar6 + uVar8 * 8) =
                     *(undefined8 *)(*(long *)(this_00 + 0x138) + uVar8 * 8);
              } while (uVar7 < *(uint *)(this_00 + 0x144));
            }
            if (*(void **)(this_00 + 0x138) != (void *)0x0) {
              operator_delete__(*(void **)(this_00 + 0x138));
            }
            *(void **)(this_00 + 0x138) = pvVar6;
            *(uint *)(this_00 + 0x144) = uVar4;
            uVar4 = *(uint *)(this_00 + 0x140);
          }
          *(CEditorBaseObject **)((long)pvVar6 + (ulong)uVar4 * 8) = this;
          *(int *)(this_00 + 0x140) = *(int *)(this_00 + 0x140) + 1;
          CEditorObjectManager::EditorObjectCreated
                    (*(CEditorObjectManager **)(gEditor + 0x120),this);
          CEditorObjectManager::EditorObjectSelected
                    (*(CEditorObjectManager **)(gEditor + 0x120),this);
          local_58[0] = CPositionableObject::getPosition(this_00,false);
          CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)local_58);
          *(CPositionableObject **)(this + 0x100) = this_00;
          if (uVar9 <= *(uint *)(this_00 + 0x140)) goto LAB_0059eaf8;
        }
        uVar4 = *(uint *)(this_00 + 0x140);
      }
LAB_0059eaf8:
      setPathName((wstring_conflict *)this_00);
    }
  }
  return;
}



/* address=0059ec70
   symbol=CPathController::setArrayOfVectors */

/* CPathController::setArrayOfVectors(float const*, unsigned int) */

void __thiscall
CPathController::setArrayOfVectors(CPathController *this,float *param_1,uint param_2)

{
  CPathController *pCVar1;
  float fVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  void *pvVar6;
  long *plVar7;
  undefined8 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  ulong uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  uint uVar14;
  long lVar15;

  *(undefined4 *)(this + 0x158) = 0;
  *(undefined4 *)(this + 0x15c) = 0;
  if (*(void **)(this + 0x150) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x150));
  }
  *(undefined8 *)(this + 0x150) = 0;
  if ((param_1 != (float *)0x0) && (param_2 != 0)) {
    uVar5 = *(uint *)(this + 0x158);
    pCVar1 = this + 0x150;
    uVar14 = 0;
    do {
      fVar2 = *param_1;
      if (uVar5 < *(uint *)(this + 0x15c)) {
        pvVar6 = *(void **)pCVar1;
      }
      else if (*(long *)pCVar1 == 0) {
        *(uint *)(this + 0x15c) = *(uint *)(this + 0x160);
        pvVar6 = operator_new__((ulong)*(uint *)(this + 0x160) << 2);
        uVar5 = *(uint *)(this + 0x158);
        *(void **)pCVar1 = pvVar6;
      }
      else {
        uVar5 = *(uint *)(this + 0x15c) + *(int *)(this + 0x160);
        pvVar6 = operator_new__((ulong)uVar5 << 2);
        if (*(int *)(this + 0x15c) != 0) {
          uVar11 = 0;
          do {
            uVar10 = (int)uVar11 + 1;
            *(undefined4 *)((long)pvVar6 + uVar11 * 4) =
                 *(undefined4 *)(*(long *)pCVar1 + uVar11 * 4);
            uVar11 = (ulong)uVar10;
          } while (uVar10 < *(uint *)(this + 0x15c));
        }
        if (*(void **)pCVar1 != (void *)0x0) {
          operator_delete__(*(void **)pCVar1);
        }
        *(void **)pCVar1 = pvVar6;
        *(uint *)(this + 0x15c) = uVar5;
        uVar5 = *(uint *)(this + 0x158);
      }
      uVar14 = uVar14 + 1;
      param_1 = param_1 + 1;
      *(float *)((long)pvVar6 + (ulong)uVar5 * 4) = fVar2;
      uVar5 = *(int *)(this + 0x158) + 1;
      *(uint *)(this + 0x158) = uVar5;
    } while (uVar14 < param_2);
  }
  setNumberOfPathPoints((uint)this);
  cVar4 = CResourceManager::getEditorIsRunning();
  if ((cVar4 != '\0') && (*(long *)(this + 0x48) != 0)) {
    if (param_2 != 0) {
      lVar15 = 0;
      uVar14 = 2;
      uVar5 = 0;
      do {
        if (uVar14 < param_2) {
          uVar10 = uVar5 / 3;
          if (uVar10 < *(uint *)(this + 0x144)) {
            plVar7 = (long *)((ulong)uVar10 * 8 + *(long *)(this + 0x138));
          }
          else {
            plVar7 = *(long **)(this + 0x138);
          }
          *(undefined8 *)(*plVar7 + 0x100) = 0;
          if (uVar10 < *(uint *)(this + 0x144)) {
            puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x138));
          }
          else {
            puVar8 = *(undefined8 **)(this + 0x138);
          }
          uVar3 = *(uint *)(this + 0x15c);
          if (uVar14 < uVar3) {
            puVar9 = *(undefined4 **)(this + 0x150);
            puVar12 = puVar9 + uVar14;
          }
          else {
            puVar9 = *(undefined4 **)(this + 0x150);
            puVar12 = puVar9;
          }
          puVar13 = puVar9;
          if (uVar5 + 1 < uVar3) {
            puVar13 = puVar9 + (uVar5 + 1);
          }
          if (uVar5 < uVar3) {
            puVar9 = (undefined4 *)((long)puVar9 + lVar15);
          }
          (**(code **)(*(long *)*puVar8 + 0x58))(*puVar9,*puVar13,*puVar12);
          if (uVar10 < *(uint *)(this + 0x144)) {
            plVar7 = (long *)((ulong)uVar10 * 8 + *(long *)(this + 0x138));
          }
          else {
            plVar7 = *(long **)(this + 0x138);
          }
          *(CPathController **)(*plVar7 + 0x100) = this;
        }
        uVar5 = uVar5 + 3;
        uVar14 = uVar14 + 3;
        lVar15 = lVar15 + 0xc;
      } while (uVar5 < param_2);
    }
                    /* WARNING: Could not recover jumptable at 0x0059ef27. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x50))(this,this[0x130]);
    return;
  }
  return;
}



/* address=0059ef70
   symbol=CPathController::initObjectInEditor */

/* CPathController::initObjectInEditor() */

void CPathController::initObjectInEditor(void)

{
  char cVar1;
  CPositionableObject *in_RDI;
  undefined4 uVar2;
  undefined4 extraout_XMM0_Db;
  float local_18 [4];

  cVar1 = CResourceManager::getEditorIsRunning();
  if (cVar1 != '\0') {
    (**(code **)(*(long *)in_RDI + 0x50))();
    local_18[0] = 0.0;
    local_18[1] = 0.0;
    local_18[2] = 0.0;
    uVar2 = CPositionableObject::getPosition(in_RDI,false);
    local_18[0] = (float)uVar2;
    CPositionableObject::getPosition(in_RDI,false);
    local_18[1] = (float)extraout_XMM0_Db;
    CPositionableObject::getPosition(in_RDI,false);
    setArrayOfVectors((CPathController *)in_RDI,local_18,3);
    in_RDI[0x132] = (CPositionableObject)0x1;
  }
  return;
}



/* address=0059f710
   symbol=CPathController::getEnabled */

/* CPathController::getEnabled() */

CPathController __thiscall CPathController::getEnabled(CPathController *this)

{
  return this[0x133];
}



/* export-summary functions=20 failures=0 */
