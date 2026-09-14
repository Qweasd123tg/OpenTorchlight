/* Targeted Ghidra class export.
   namespace=CLayout
   Treat pseudocode as navigation evidence. */


/* address=009d3b30
   symbol=CLayout::setCacheingParticlesForLevel */

/* CLayout::setCacheingParticlesForLevel(bool) */

void CLayout::setCacheingParticlesForLevel(bool param_1)

{
  g_bCachParticles._0_1_ = 1;
  return;
}

/* address=009d3b40
   symbol=CLayout::editorObjectLoaded */

/* CLayout::editorObjectLoaded(CEditorBaseObject*) */

void CLayout::editorObjectLoaded(CEditorBaseObject *param_1)

{
  return;
}

/* address=009d3b50
   symbol=CLayout::update */

/* CLayout::update(float) */

void __thiscall CLayout::update(CLayout *this,float param_1)

{
  char cVar1;

  if (this[0x81] != (CLayout)0x0) {
    cVar1 = (**(code **)(*(long *)this + 0x48))();
    if (cVar1 != '\0') {
      CEditorScene::update((CEditorScene *)this,param_1);
      return;
    }
  }
  return;
}

/* address=009d3ba0
   symbol=CLayout::processInputs */

/* CLayout::processInputs(unsigned int, CEditorBaseObject*) */

undefined8 CLayout::processInputs(uint param_1,CEditorBaseObject *param_2)

{
  uint uVar1;
  code *pcVar2;
  long *plVar3;
  long lVar4;
  uint uVar5;
  undefined4 in_register_0000003c;
  long lVar6;
  undefined8 uVar7;

  lVar6 = CONCAT44(in_register_0000003c,param_1);
  uVar7 = 0;
  uVar5 = 0;
  if (*(int *)(lVar6 + 0x1d8) != 0) {
    do {
      while( true ) {
        uVar1 = *(uint *)(lVar6 + 0x1dc);
        if (uVar5 < uVar1) {
          plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(lVar6 + 0x1d0));
        }
        else {
          plVar3 = *(long **)(lVar6 + 0x1d0);
        }
        if (*(long *)(*plVar3 + 0x38) != 0) break;
LAB_009d3c15:
        uVar5 = uVar5 + 1;
        if (*(uint *)(lVar6 + 0x1d8) <= uVar5) {
          return uVar7;
        }
      }
      if (*(int *)(lVar6 + 0x1b8) != 2) {
LAB_009d3bea:
        if (uVar5 < uVar1) {
          lVar4 = *(long *)(*(long *)(lVar6 + 0x1d0) + (ulong)uVar5 * 8);
          plVar3 = *(long **)(lVar4 + 0x38);
          pcVar2 = *(code **)(*plVar3 + 0xa0);
        }
        else {
          lVar4 = **(long **)(lVar6 + 0x1d0);
          plVar3 = *(long **)(lVar4 + 0x38);
          pcVar2 = *(code **)(*plVar3 + 0xa0);
        }
        uVar7 = 1;
        (*pcVar2)(plVar3,lVar4,(ulong)param_2 & 0xffffffff);
        goto LAB_009d3c15;
      }
      if (uVar5 < uVar1) {
        plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(lVar6 + 0x1d0));
      }
      else {
        plVar3 = *(long **)(lVar6 + 0x1d0);
      }
      if ((*plVar3 == 0) ||
         (lVar4 = __dynamic_cast(*plVar3,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo,0),
         lVar4 == 0)) goto LAB_009d3c15;
      if (*(char *)(lVar4 + 0x8b) != '\0') goto LAB_009d3bea;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(lVar6 + 0x1d8));
  }
  return uVar7;
}

/* address=009d3cd0
   symbol=CLayout::editorObjectsAboutToBeDelete */

/* CLayout::editorObjectsAboutToBeDelete() */

void __thiscall CLayout::editorObjectsAboutToBeDelete(CLayout *this)

{
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  if (*(void **)(this + 0x1d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1d0));
  }
  *(undefined8 *)(this + 0x1d0) = 0;
  return;
}

/* address=009d3d10
   symbol=CLayout::setDurationModification */

/* CLayout::setDurationModification(float) */

void __thiscall CLayout::setDurationModification(CLayout *this,float param_1)

{
  float fVar1;
  CTimeline *this_00;
  long *plVar2;
  uint uVar3;

  fVar1 = DAT_00fa47f8;
  if (((*(int *)(this + 0x1b8) == 2) && (*(float *)(this + 0x1b4) = param_1, fVar1 < param_1)) &&
     (*(int *)(this + 0x1d8) != 0)) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x1dc)) {
        plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x1d0));
      }
      else {
        plVar2 = *(long **)(this + 0x1d0);
      }
      if (((*plVar2 != 0) &&
          (this_00 = (CTimeline *)
                     __dynamic_cast(*plVar2,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo,0),
          this_00 != (CTimeline *)0x0)) && (this_00[0x8b] != (CTimeline)0x0)) {
        CTimeline::setDurationModificationTime(this_00,*(float *)(this + 0x1b4));
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x1d8));
  }
  return;
}

/* address=009d3dc0
   symbol=CLayout::eventFiredByDescriptor */

/* CLayout::eventFiredByDescriptor(unsigned int, CDescriptor*, CEditorBaseObject*) */

void CLayout::eventFiredByDescriptor(uint param_1,CDescriptor *param_2,CEditorBaseObject *param_3)

{
  CDescriptor *this;
  undefined4 in_register_0000003c;

  if ((param_3 != (CEditorBaseObject *)0x0) &&
     (this = *(CDescriptor **)((CEditorBaseObject *)CONCAT44(in_register_0000003c,param_1) + 0x38),
     this != (CDescriptor *)0x0)) {
    CDescriptor::BroadcastEventFromObject
              (this,(CEditorBaseObject *)CONCAT44(in_register_0000003c,param_1),(uint)param_2);
    return;
  }
  return;
}

/* address=009d3df0
   symbol=CLayout::setHighlighted */

/* non-virtual thunk to CLayout::setHighlighted(bool) */

void __thiscall CLayout::setHighlighted(CLayout *this,bool param_1)

{
  setHighlighted(this + -0x198,param_1);
  return;
}

/* address=009d3e00
   symbol=CLayout::setHighlighted */

/* CLayout::setHighlighted(bool) */

void __thiscall CLayout::setHighlighted(CLayout *this,bool param_1)

{
  long *plVar1;
  _Rb_tree_node_base *p_Var2;

  for (p_Var2 = *(_Rb_tree_node_base **)(this + 0x120);
      p_Var2 != (_Rb_tree_node_base *)(this + 0x110);
      p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2)) {
    if ((*(long *)(p_Var2 + 0x28) != 0) &&
       (plVar1 = (long *)__dynamic_cast(*(long *)(p_Var2 + 0x28),&CEditorBaseObject::typeinfo,
                                        &iHighlight::typeinfo,0xfffffffffffffffe),
       plVar1 != (long *)0x0)) {
      (**(code **)(*plVar1 + 0x10))(plVar1,param_1);
    }
  }
  return;
}

/* address=009d3e70
   symbol=CLayout::getNumberOfParticlesUpdating */

/* CLayout::getNumberOfParticlesUpdating() */

void __thiscall CLayout::getNumberOfParticlesUpdating(CLayout *this)

{
  if (*(CParticle **)(this + 0x1f0) != (CParticle *)0x0) {
    CParticle::getNumberOfParticlesUpdating(*(CParticle **)(this + 0x1f0),false);
    return;
  }
  CEditorScene::getNumberOfParticlesUpdating((CEditorScene *)this);
  return;
}

/* address=009d3ea0
   symbol=CLayout::setVisible */

/* CLayout::setVisible(bool) */

void __thiscall CLayout::setVisible(CLayout *this,bool param_1)

{
  CLayout CVar1;

  CVar1 = this[0x81];
  CSceneNodeObject::setVisible((CSceneNodeObject *)this,param_1);
  if (((CLayout)param_1 != CVar1) && (*(CParticle **)(this + 0x1f0) != (CParticle *)0x0)) {
    if (param_1) {
      CParticle::Start();
      return;
    }
    CParticle::Stop(*(CParticle **)(this + 0x1f0),false);
    return;
  }
  return;
}

/* address=009d3f40
   symbol=CLayout::CLayout */

/* CLayout::CLayout(CResourceManager*, ELAYOUT_TYPES) */

void __thiscall CLayout::CLayout(CLayout *this,CResourceManager *param_1,undefined4 param_3)

{
  CAllDescriptorsScene::CAllDescriptorsScene((CAllDescriptorsScene *)this);
  *(undefined ***)this = &PTR__CLayout_00fd9770;
  *(undefined ***)(this + 400) = &PTR__CLayout_00fd99e8;
  *(undefined ***)(this + 0x198) = &PTR__CLayout_00fd9a18;
  this[0x1a0] = (CLayout)0x1;
  *(undefined4 *)(this + 0x1a4) = 1;
  *(undefined4 *)(this + 0x1a8) = 0;
  *(undefined4 *)(this + 0x1ac) = 0;
  *(undefined4 *)(this + 0x1b0) = 0;
  *(undefined4 *)(this + 0x1b4) = 0;
  *(undefined4 *)(this + 0x1b8) = param_3;
  *(undefined8 *)(this + 0x1c0) = 0;
  this[0x1c8] = (CLayout)0x0;
  this[0x1c9] = (CLayout)0x0;
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  *(undefined4 *)(this + 0x1e0) = 10;
  this[0x1e8] = (CLayout)0x0;
  *(undefined8 *)(this + 0x1f0) = 0;
                    /* try { // try from 009d401a to 009d402b has its CatchHandler @ 009d403f */
  CEditorScene::InitScene((CEditorScene *)this,param_1,0);
  CEditorScene::setEnabled((CEditorScene *)this,true);
  return;
}

/* address=009dd740
   symbol=CLayout::_GLOBAL__I_setCacheingParticlesForLevel */

/* CLayout::setCacheingParticlesForLevel(bool) */

void CLayout::_GLOBAL__I_setCacheingParticlesForLevel(void)

{
  allocator aStack_373;
  allocator aStack_372;
  allocator aStack_371;
  allocator aStack_370;
  allocator aStack_36f;
  allocator aStack_36e;
  allocator aStack_36d;
  allocator aStack_36c;
  allocator aStack_36b;
  allocator aStack_36a;
  allocator aStack_369;
  allocator aStack_368;
  allocator aStack_367;
  allocator aStack_366;
  allocator aStack_365;
  allocator aStack_364;
  allocator aStack_363;
  allocator aStack_362;
  allocator aStack_361;
  allocator aStack_360;
  allocator aStack_35f;
  allocator aStack_35e;
  allocator aStack_35d;
  allocator aStack_35c;
  allocator aStack_35b;
  allocator aStack_35a;
  allocator aStack_359;
  allocator aStack_358;
  allocator aStack_357;
  allocator aStack_356;
  allocator aStack_355;
  allocator aStack_354;
  allocator aStack_353;
  allocator aStack_352;
  allocator aStack_351;
  allocator aStack_350;
  allocator aStack_34f;
  allocator aStack_34e;
  allocator aStack_34d;
  allocator aStack_34c;
  allocator aStack_34b;
  allocator aStack_34a;
  allocator aStack_349;
  allocator aStack_348;
  allocator aStack_347;
  allocator aStack_346;
  allocator aStack_345;
  allocator aStack_344;
  allocator aStack_343;
  allocator aStack_342;
  allocator aStack_341;
  allocator aStack_340;
  allocator aStack_33f;
  allocator aStack_33e;
  allocator aStack_33d;
  allocator aStack_33c;
  allocator aStack_33b;
  allocator aStack_33a;
  allocator aStack_339;
  allocator aStack_338;
  allocator aStack_337;
  allocator aStack_336;
  allocator aStack_335;
  allocator aStack_334;
  allocator aStack_333;
  allocator aStack_332;
  allocator aStack_331;
  allocator aStack_330;
  allocator aStack_32f;
  allocator aStack_32e;
  allocator aStack_32d;
  allocator aStack_32c;
  allocator aStack_32b;
  allocator aStack_32a;
  allocator aStack_329;
  allocator aStack_328;
  allocator aStack_327;
  allocator aStack_326;
  allocator aStack_325;
  allocator aStack_324;
  allocator aStack_323;
  allocator aStack_322;
  allocator aStack_321;
  allocator aStack_320;
  allocator aStack_31f;
  allocator aStack_31e;
  allocator aStack_31d;
  allocator aStack_31c;
  allocator aStack_31b;
  allocator aStack_31a;
  allocator aStack_319;
  allocator aStack_318;
  allocator aStack_317;
  allocator aStack_316;
  allocator aStack_315;
  allocator aStack_314;
  allocator aStack_313;
  allocator aStack_312;
  allocator aStack_311;
  allocator aStack_310;
  allocator aStack_30f;
  allocator aStack_30e;
  allocator aStack_30d;
  allocator aStack_30c;
  allocator aStack_30b;
  allocator aStack_30a;
  allocator aStack_309;
  allocator aStack_308;
  allocator aStack_307;
  allocator aStack_306;
  allocator aStack_305;
  allocator aStack_304;
  allocator aStack_303;
  allocator aStack_302;
  allocator aStack_301;
  allocator aStack_300;
  allocator aStack_2ff;
  allocator aStack_2fe;
  allocator aStack_2fd;
  allocator aStack_2fc;
  allocator aStack_2fb;
  allocator aStack_2fa;
  allocator aStack_2f9;
  allocator aStack_2f8;
  allocator aStack_2f7;
  allocator aStack_2f6;
  allocator aStack_2f5;
  allocator aStack_2f4;
  allocator aStack_2f3;
  allocator aStack_2f2;
  allocator aStack_2f1;
  allocator aStack_2f0;
  allocator aStack_2ef;
  allocator aStack_2ee;
  allocator aStack_2ed;
  allocator aStack_2ec;
  allocator aStack_2eb;
  allocator aStack_2ea;
  allocator aStack_2e9;
  allocator aStack_2e8;
  allocator aStack_2e7;
  allocator aStack_2e6;
  allocator aStack_2e5;
  allocator aStack_2e4;
  allocator aStack_2e3;
  allocator aStack_2e2;
  allocator aStack_2e1;
  allocator aStack_2e0;
  allocator aStack_2df;
  allocator aStack_2de;
  allocator aStack_2dd;
  allocator aStack_2dc;
  allocator aStack_2db;
  allocator aStack_2da;
  allocator aStack_2d9;
  allocator aStack_2d8;
  allocator aStack_2d7;
  allocator aStack_2d6;
  allocator aStack_2d5;
  allocator aStack_2d4;
  allocator aStack_2d3;
  allocator aStack_2d2;
  allocator aStack_2d1;
  allocator aStack_2d0;
  allocator aStack_2cf;
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
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_373);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_372);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_371);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_370);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_36f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_36e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_36d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_36c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_36b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_36a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_369)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_368);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_367);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_366);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_365);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_364);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_363)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_362);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_361)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_360);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_35f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_35e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_35d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_35c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_35b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_35a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_359);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_358);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_357)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_356);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_355);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_354);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_353);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_352);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_351);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_350);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_34f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_34e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_34d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_34c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_34b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_34a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_349);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_348);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_347);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_346);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_345);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_344);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_343);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_342);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_341);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_340);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_33f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_33e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_33d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_33c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_33b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_33a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_339)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_338);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_337);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_336);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_335);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_334);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_333);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_332);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_331);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_330);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_32f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_32e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_32d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_32c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_32b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_32a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_328);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_327);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_326);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_325);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_324)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_323);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_322);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_321);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_320);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_31f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_31e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_31d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_31c)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_31b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_31a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_319);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_318);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_317);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_316);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_315);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_314);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_313);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_312);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_311);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_310);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_30f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_30e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_30d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_30c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_30b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_30a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_309)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",
             &aStack_308);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_307);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_306);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_305);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_304);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_303);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_302);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_301);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_2fe);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_2fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_2fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_2fb);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_2fa);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_2f9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_2f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_2f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_2f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",
             &aStack_2f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_2f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_2f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_2f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_2f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_2f0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_2ef);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_2ee);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_2ed);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_2ec);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_2ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_2e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_2e8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_2e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_2e6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_2e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_2e4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_2e3
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_2e2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_2e1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_2e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_2df);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_2de);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_2dd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_2dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_2db)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_2da);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_2d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_2d8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_2d7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_2d6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_2d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_2d4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_2d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_2d2
            );
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_2d1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_2d0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_2cf);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_2ce);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_2cd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_2cc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_2ca);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_2c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_2c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_2c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_2c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_2c4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_2c3)
  ;
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_2c2);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_2c1);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_2c0);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_2bd);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_2bb);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_2b9);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_2b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_2b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_2b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_2b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_2b3);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_28e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_28d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_28c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_28b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_28a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_289);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_288);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_252);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_250);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_24f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_24e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_24d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_24c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_24b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_249);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_248);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_246)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_244)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_243)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_242)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_241)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_240)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_23f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_23d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_23c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_23a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_239);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_237);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_235);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_234);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_233);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_231)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_230);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_22f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_22a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_226);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_225);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_224);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_223
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_220
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_21f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_21d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_21b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_21a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_216);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_214);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_213);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_212);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_211
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_210);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_209);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_202);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1fb);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)&DAT_014a4fc8,L"ITEM",&aStack_1f9);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1f5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1ee);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_10c);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_10a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_109);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_104);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_103);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_102);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_101);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_100);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_ff);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_fe);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_fd);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)&DAT_014a57f8,L"Two",&aStack_fb);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_f9);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_f8);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_ee);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_INTERP_TYPES,L"Linear",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 8),L"Linear Round",&aStack_ec)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x10),L"Linear Round Down",&aStack_eb);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x18),L"Linear Round Up",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x20),L"Spline",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x28),L"Quaternion",&aStack_e8);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x30),L"No Interpolation",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x38),L"Use Timeline Default",&aStack_e6)
  ;
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_e5);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_e4);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_e3);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_e1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_de);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_dd
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_d8);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_d6);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_d5
            );
  std::wstring::wstring((wstring_conflict *)&DAT_014a5978,L"Add",&aStack_d4);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)&DAT_014a5988,L"Texture",&aStack_d2);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_cf);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_cd);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_c4);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_c0);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_bb);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_b9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_b7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_ac)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_a7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_99);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_98);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_97);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_96);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_95);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_94);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_93);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_92);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_91);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_90);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_8f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_8e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_8d);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_8c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_8b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_8a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_89);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_88);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_87);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_86);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_85);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_84);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_83);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_82);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_81);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_80);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_7f);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_7e);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_7d);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_7c);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_7b);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_7a);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_79);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_78);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_77);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_76);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_75);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_70);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_6b);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_6a);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gINPUT_EVENT_NAMES,L"Show",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 8),L"Hide",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x10),L"Enable",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x18),L"Disable",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x20),L"Enable and Show",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x28),L"Disable and Hide",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x30),L"Reset",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x38),L"Add",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x40),L"Subtract",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x48),L"Play",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x50),L"Stop",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x58),L"Pause",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x60),L"Resume",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x68),L"Play Level Music",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x70),L"Increment",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x78),L"Activate",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x80),L"Start Particle",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x88),L"Stop Particle",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x90),L"Force Stop Particle",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x98),L"Pause Particle",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa0),L"Resume Particle",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa8),L"Play",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb0),L"Play Backwards",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb8),L"Stop",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xc0),L"Stop to End",&aStack_51)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 200),L"Pause",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd0),L"Reset",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd8),L"Reset To End",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe0),L"Fast Forward To End",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe8),L"Rewind to Start",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf0),L"Set State One",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf8),L"Set State Two",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x100),L"Spawn Units",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x108),L"Destroy Spawned Units",&aStack_48)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x110),L"Hide And Disable Spawned Units",
             &aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x118),L"Increment Level Delta",&aStack_46)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x120),L"Decrement Level Delta",&aStack_45)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x128),L"Activate Warper",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x130),L"Activate Teleport",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x138),L"Roll",&aStack_42);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x140),L"Input 1",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x148),L"Input 2",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x150),L"Input 3",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x158),L"Input 4",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x160),L"Input 5",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x168),L"Input 6",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x170),L"Trigger",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x178),L"Toggle",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x180),L"Interact",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x188),L"Make Invulnerable",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 400),L"Make Vulnerable",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x198),L"Start Camera",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a0),L"Camera Off",&aStack_35)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a8),L"Force Accept",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b0),L"Force Not Accepted",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b8),L"Force Complete",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c0),L"Force Not Complete",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c8),L"Start Skill",&aStack_30);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d0),L"Stop Skill",&aStack_2f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d8),L"Learn Skill",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e0),L"Unlearn Skill",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e8),L"Alert Monster",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f0),L"Enable Targeting",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f8),L"Disable Targeting",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x200),L"Enable Targeting & Alert",
             &aStack_29);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x208),L"Hunt",&aStack_28);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x210),L"Play",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x218),L"Play Looping",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x220),L"Stop",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x228),L"Stop and Idle",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x230),L"Cannot be Targeted",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x238),L"Can be Targeted",&aStack_22);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x240),L"Add as Pet",&aStack_21)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x248),L"Remove as Pet",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x250),L"Kill Monster",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 600),L"Warp Pets to Player",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x260),L"Heal Player",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x268),L"Collidable",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x270),L"Not Collidable",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x278),L"Take Money",&aStack_1a)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x280),L"Show Tip",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x288),L"Clear History",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x290),L"Stop Skills",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x298),L"Kill Pets",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a0),L"Stop",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a8),L"Start",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b0),L"Pause",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b8),L"Input1",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c0),L"Input2",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c8),L"Input3",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d0),L"Input4",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d8),L"Input5",&aStack_e);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gRANDOMGROUP_NAMES,L"ALL",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 8),L"Weight",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 0x10),L"Random Chance",&aStack_b);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gCAMERASHAKE_ORIENTATION,L"ABSOLUTE",&aStack_a);
  std::wstring::wstring((wstring_conflict *)&DAT_014a6068,L"RELATIVE",&aStack_9);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  g_LayoutToCloneOrControl._40_8_ = 0;
  g_LayoutToCloneOrControl._8_4_ = 0;
  g_LayoutToCloneOrControl._16_8_ = 0;
  g_LayoutToCloneOrControl._24_8_ = 0x14a6088;
  g_LayoutToCloneOrControl._32_8_ = 0x14a6088;
  __cxa_atexit(std::
               map<std::wstring,CLayout*,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CLayout*>>>
               ::~map,g_LayoutToCloneOrControl,&__dso_handle);
  return;
}

/* address=009dd9a0
   symbol=CLayout::SetSceneOwner */

/* WARNING: Removing unreachable block (ram,0x009ddaf2) */
/* CLayout::SetSceneOwner(CEditorScene*) */

void __thiscall CLayout::SetSceneOwner(CLayout *this,CEditorScene *param_1)

{
  int *piVar1;
  int iVar2;
  CEditorScene *pCVar3;
  long lVar4;
  char cVar5;
  Entity *pEVar6;
  uint uVar7;
  long local_48;
  allocator local_39 [9];

  CSceneNodeObject::SetSceneOwner((CSceneNodeObject *)this,param_1);
  cVar5 = CResourceManager::getEditorIsRunning();
  lVar4 = gEditor;
  if ((cVar5 != '\0') && (*(int *)(gEditor + 200) != 0)) {
    uVar7 = 0;
    do {
      while( true ) {
        if (uVar7 < *(uint *)(lVar4 + 0xcc)) {
          pCVar3 = *(CEditorScene **)((ulong)uVar7 * 8 + *(long *)(lVar4 + 0xc0));
        }
        else {
          pCVar3 = (CEditorScene *)**(long **)(lVar4 + 0xc0);
        }
        if ((param_1 == pCVar3) && (*(long *)(this + 0x58) != 0)) break;
        uVar7 = uVar7 + 1;
        if (*(uint *)(lVar4 + 200) <= uVar7) {
          return;
        }
      }
      pEVar6 = (Entity *)
               OGRE_UTILITIES::createEntity
                         (*(undefined8 *)(*(long *)(this + 0x68) + 0x10),0,8,&DAT_00faa818);
      CSceneNodeObject::sceneNodeAttachEntity((CSceneNodeObject *)this,pEVar6);
                    /* try { // try from 009dda5d to 009dda61 has its CatchHandler @ 009ddab7 */
      std::string::string((string *)&local_48,"lightBlue",local_39);
                    /* try { // try from 009dda6a to 009dda6e has its CatchHandler @ 009ddae4 */
      Ogre::Entity::setMaterialName(*(string **)(this + 0x60));
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      uVar7 = uVar7 + 1;
      (**(code **)(*(long *)this + 0x90))(DAT_00fa47fc,this);
    } while (uVar7 < *(uint *)(lVar4 + 200));
  }
  return;
}

/* address=009ddb00
   symbol=CLayout::getLayoutToClone */

/* CLayout::getLayoutToClone(std::wstring const&) */

undefined8 __thiscall CLayout::getLayoutToClone(CLayout *this,wstring_conflict *param_1)

{
  wchar_t *__s2;
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  ulong uVar4;
  long lVar5;
  long lVar6;
  long lVar7;

  lVar7 = 0x14a6088;
  if (g_LayoutToCloneOrControl._16_8_ != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar1 = *(ulong *)(__s2 + -6);
    lVar6 = g_LayoutToCloneOrControl._16_8_;
    do {
      uVar2 = *(ulong *)(*(wchar_t **)(lVar6 + 0x20) + -6);
      uVar4 = uVar1;
      if (uVar2 <= uVar1) {
        uVar4 = uVar2;
      }
      iVar3 = wmemcmp(*(wchar_t **)(lVar6 + 0x20),__s2,uVar4);
      if (iVar3 == 0) {
        lVar5 = uVar2 - uVar1;
        if (0x7fffffff < lVar5) goto LAB_009ddb36;
        if (-0x80000001 < lVar5) {
          iVar3 = (int)lVar5;
          goto LAB_009ddb32;
        }
LAB_009ddb78:
        lVar5 = *(long *)(lVar6 + 0x18);
      }
      else {
LAB_009ddb32:
        if (iVar3 < 0) goto LAB_009ddb78;
LAB_009ddb36:
        lVar5 = *(long *)(lVar6 + 0x10);
        lVar7 = lVar6;
      }
      lVar6 = lVar5;
    } while (lVar6 != 0);
    if (lVar7 == 0x14a6088) {
      return 0;
    }
    uVar1 = *(ulong *)(*(wchar_t **)param_1 + -6);
    uVar2 = *(ulong *)(*(wchar_t **)(lVar7 + 0x20) + -6);
    uVar4 = uVar1;
    if (uVar2 <= uVar1) {
      uVar4 = uVar2;
    }
    iVar3 = wmemcmp(*(wchar_t **)param_1,*(wchar_t **)(lVar7 + 0x20),uVar4);
    if (iVar3 == 0) {
      lVar6 = uVar1 - uVar2;
      if (0x7fffffff < lVar6) goto LAB_009ddbe6;
      if (lVar6 < -0x80000000) {
        return 0;
      }
      iVar3 = (int)lVar6;
    }
    if (-1 < iVar3) {
LAB_009ddbe6:
      return *(undefined8 *)(lVar7 + 0x28);
    }
  }
  return 0;
}

/* address=009ddc00
   symbol=CLayout::callFunctionOnObjects */

/* CLayout::callFunctionOnObjects(CLayout::ELAYOUT_FUNCTION_TYPES, bool) */

void CLayout::callFunctionOnObjects
               (undefined8 param_1,undefined4 param_2,CPositionableObject *param_3,int param_4,
               bool param_5)

{
  CParticle *this;
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  code *UNRECOVERED_JUMPTABLE;
  long *plVar4;
  CTimeline *this_00;
  CSoundObject *pCVar5;
  CRunicCore *this_01;
  long lVar6;
  TSafePointer *pTVar7;
  void *pvVar8;
  uint uVar9;
  ulong uVar10;
  uint uVar11;
  undefined8 uVar12;
  undefined4 local_48;
  undefined4 uStack_44;

  this = *(CParticle **)(param_3 + 0x1f0);
  if (this != (CParticle *)0x0) {
    switch(param_4) {
    case 0:
    case 4:
      CParticle::Start();
      uVar12 = 0x1f;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)param_3 + 0x30);
      break;
    case 1:
      CParticle::Stop(this,param_5);
      uVar12 = 0x20;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)param_3 + 0x30);
      break;
    case 2:
      CParticle::Pause(this);
      uVar12 = 0x21;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)param_3 + 0x30);
      break;
    case 3:
      CParticle::Resume(this);
      uVar12 = 0x22;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)param_3 + 0x30);
      break;
    default:
      goto switchD_009ddc43_default;
    }
                    /* WARNING: Could not recover jumptable at 0x009ddc72. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(param_3,uVar12);
    return;
  }
  uVar11 = 0;
  if (*(int *)(param_3 + 0x1d8) != 0) {
    do {
      if (*(int *)(param_3 + 0x1b8) == 1) {
        uVar9 = *(uint *)(param_3 + 0x1dc);
        if (uVar11 < uVar9) {
          lVar6 = *(long *)((ulong)uVar11 * 8 + *(long *)(param_3 + 0x1d0));
        }
        else {
          lVar6 = **(long **)(param_3 + 0x1d0);
        }
        if ((lVar6 == 0) ||
           (plVar4 = (long *)__dynamic_cast(lVar6,&CEditorBaseObject::typeinfo,
                                            &CParticleTechWrapper::typeinfo), plVar4 == (long *)0x0)
           ) {
          if (uVar11 < uVar9) {
            plVar4 = (long *)((ulong)uVar11 * 8 + *(long *)(param_3 + 0x1d0));
          }
          else {
            plVar4 = *(long **)(param_3 + 0x1d0);
          }
          if ((*plVar4 == 0) ||
             (pCVar5 = (CSoundObject *)
                       __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CSoundObject::typeinfo),
             pCVar5 == (CSoundObject *)0x0)) {
            if (uVar11 < uVar9) {
              plVar4 = (long *)((ulong)uVar11 * 8 + *(long *)(param_3 + 0x1d0));
            }
            else {
              plVar4 = *(long **)(param_3 + 0x1d0);
            }
            if (((*plVar4 != 0) &&
                (this_01 = (CRunicCore *)
                           __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,
                                          &CCameraShake::typeinfo), this_01 != (CRunicCore *)0x0))
               && (param_4 == 0)) {
              uVar12 = CPositionableObject::getPosition(param_3,true);
              local_48 = (undefined4)uVar12;
              *(undefined4 *)(this_01 + 0x8c) = local_48;
              uStack_44 = (undefined4)((ulong)uVar12 >> 0x20);
              *(undefined4 *)(this_01 + 0x90) = uStack_44;
              this_01[0x98] = (CRunicCore)0x1;
              *(undefined4 *)(this_01 + 0x94) = param_2;
              lVar6 = CResourceManager::getCameraControl();
              pTVar7 = (TSafePointer *)
                       Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
              *(undefined4 *)(pTVar7 + 8) = 0xffffffff;
              *(undefined8 *)pTVar7 = 0;
                    /* try { // try from 009de186 to 009de18a has its CatchHandler @ 009de25f */
              uVar2 = CRunicCore::addSafePointer(this_01,pTVar7);
              *(CRunicCore **)pTVar7 = this_01;
              *(undefined4 *)(pTVar7 + 8) = uVar2;
              uVar9 = *(uint *)(lVar6 + 0x78);
              if (uVar9 < *(uint *)(lVar6 + 0x7c)) {
                pvVar8 = *(void **)(lVar6 + 0x70);
              }
              else if (*(long *)(lVar6 + 0x70) == 0) {
                *(uint *)(lVar6 + 0x7c) = *(uint *)(lVar6 + 0x80);
                pvVar8 = operator_new__((ulong)*(uint *)(lVar6 + 0x80) * 8);
                uVar9 = *(uint *)(lVar6 + 0x78);
                *(void **)(lVar6 + 0x70) = pvVar8;
              }
              else {
                uVar3 = *(uint *)(lVar6 + 0x7c) + *(int *)(lVar6 + 0x80);
                pvVar8 = operator_new__((ulong)uVar3 << 3);
                if (*(int *)(lVar6 + 0x7c) != 0) {
                  uVar10 = 0;
                  do {
                    uVar9 = (int)uVar10 + 1;
                    *(undefined8 *)((long)pvVar8 + uVar10 * 8) =
                         *(undefined8 *)(*(long *)(lVar6 + 0x70) + uVar10 * 8);
                    uVar10 = (ulong)uVar9;
                  } while (uVar9 < *(uint *)(lVar6 + 0x7c));
                }
                if (*(void **)(lVar6 + 0x70) != (void *)0x0) {
                  operator_delete__(*(void **)(lVar6 + 0x70));
                }
                *(void **)(lVar6 + 0x70) = pvVar8;
                uVar9 = *(uint *)(lVar6 + 0x78);
                *(uint *)(lVar6 + 0x7c) = uVar3;
              }
              *(TSafePointer **)((long)pvVar8 + (ulong)uVar9 * 8) = pTVar7;
              *(int *)(lVar6 + 0x78) = *(int *)(lVar6 + 0x78) + 1;
            }
          }
          else if (param_4 == 1) {
            cVar1 = CSoundObject::isLooping(pCVar5);
            if (cVar1 != '\0') {
              CSoundObject::stop(pCVar5);
            }
          }
          else if (param_4 < 2) {
            if ((param_4 == 0) && (pCVar5[0x120] != (CSoundObject)0x0)) {
              CSoundObject::play(pCVar5);
            }
          }
          else if (param_4 == 2) {
            CSoundObject::pause(pCVar5);
          }
          else if (param_4 == 3) {
            CSoundObject::resume(pCVar5);
          }
        }
        else {
          switch(param_4) {
          case 0:
          case 4:
            (**(code **)(*plVar4 + 0x218))(plVar4,1);
            break;
          case 1:
            (**(code **)(*plVar4 + 0x218))(plVar4,0);
            break;
          case 2:
            if ((ParticleSystem *)plVar4[0x23] != (ParticleSystem *)0x0) {
              ParticleUniverse::ParticleSystem::pause((ParticleSystem *)plVar4[0x23]);
            }
            break;
          case 3:
            if ((ParticleSystem *)plVar4[0x23] != (ParticleSystem *)0x0) {
              ParticleUniverse::ParticleSystem::resume((ParticleSystem *)plVar4[0x23]);
            }
          }
        }
      }
      else if (*(int *)(param_3 + 0x1b8) == 2) {
        uVar9 = *(uint *)(param_3 + 0x1dc);
        if (uVar11 < uVar9) {
          plVar4 = (long *)((ulong)uVar11 * 8 + *(long *)(param_3 + 0x1d0));
        }
        else {
          plVar4 = *(long **)(param_3 + 0x1d0);
        }
        if (((*plVar4 == 0) ||
            (this_00 = (CTimeline *)
                       __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo),
            this_00 == (CTimeline *)0x0)) || (this_00[0x8b] == (CTimeline)0x0)) {
          if (uVar11 < uVar9) {
            plVar4 = (long *)((ulong)uVar11 * 8 + *(long *)(param_3 + 0x1d0));
          }
          else {
            plVar4 = *(long **)(param_3 + 0x1d0);
          }
          if ((*plVar4 != 0) &&
             (pCVar5 = (CSoundObject *)
                       __dynamic_cast(*plVar4,&CEditorBaseObject::typeinfo,&CSoundObject::typeinfo),
             pCVar5 != (CSoundObject *)0x0)) {
            if (param_4 == 1) {
              cVar1 = CSoundObject::isLooping(pCVar5);
              if (cVar1 != '\0') {
                CSoundObject::stop(pCVar5);
              }
            }
            else if (param_4 < 2) {
              if ((param_4 == 0) && (pCVar5[0x120] != (CSoundObject)0x0)) {
                CSoundObject::play(pCVar5);
              }
            }
            else if (param_4 == 2) {
              CSoundObject::pause(pCVar5);
            }
            else if (param_4 == 3) {
              CSoundObject::resume(pCVar5);
            }
          }
        }
        else {
          switch(param_4) {
          case 0:
            CTimeline::Reset_To_Beginning(this_00);
            CTimeline::SetEnabled(this_00,false);
            CTimeline::Play(this_00,true);
            break;
          case 1:
            CTimeline::Stop(this_00);
            break;
          case 2:
            CTimeline::Pause(this_00);
            break;
          case 3:
            CTimeline::Play(this_00,true);
            break;
          case 4:
            CTimeline::Reset_To_End(this_00);
            CTimeline::SetEnabled(this_00,false);
            CTimeline::Play_Backwards(this_00);
          }
        }
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(param_3 + 0x1d8));
  }
switchD_009ddc43_default:
  return;
}

/* address=009de280
   symbol=CLayout::resume */

/* CLayout::resume() */

void __thiscall CLayout::resume(CLayout *this)

{
  callFunctionOnObjects(this,3,0);
  return;
}

/* address=009de290
   symbol=CLayout::pause */

/* CLayout::pause() */

void __thiscall CLayout::pause(CLayout *this)

{
  callFunctionOnObjects(this,2,0);
  return;
}

/* address=009de2a0
   symbol=CLayout::stop */

/* CLayout::stop(bool) */

void __thiscall CLayout::stop(CLayout *this,bool param_1)

{
  callFunctionOnObjects(this,1,param_1);
  return;
}

/* address=009de2b0
   symbol=CLayout::startBackwards */

/* CLayout::startBackwards() */

void __thiscall CLayout::startBackwards(CLayout *this)

{
  callFunctionOnObjects(this,4,0);
  return;
}

/* address=009de2c0
   symbol=CLayout::start */

/* CLayout::start() */

void __thiscall CLayout::start(CLayout *this)

{
  callFunctionOnObjects(this,0,0);
  return;
}

/* address=009de2d0
   symbol=CLayout::setStartOnLoad */

/* CLayout::setStartOnLoad(bool) */

void __thiscall CLayout::setStartOnLoad(CLayout *this,bool param_1)

{
  char cVar1;
  long lVar2;
  long *plVar3;
  uint uVar4;

  this[0x1a0] = (CLayout)param_1;
  cVar1 = CResourceManager::getEditorIsRunning();
  if (cVar1 == '\0') {
    return;
  }
  if (this[0x1a0] != (CLayout)0x0) {
    if ((*(int *)(this + 0x1b8) == 2) && (*(int *)(this + 0x1d8) != 0)) {
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x1dc)) {
          plVar3 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x1d0));
        }
        else {
          plVar3 = *(long **)(this + 0x1d0);
        }
        if (*plVar3 != 0) {
          lVar2 = __dynamic_cast(*plVar3,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo,0);
          if (lVar2 != 0) {
            *(undefined1 *)(lVar2 + 0x8c) = 1;
          }
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(this + 0x1d8));
    }
    start(this);
    return;
  }
  stop(this,false);
  return;
}

/* address=009de390
   symbol=CLayout::addLayoutForCloningAndControlling */

/* CLayout::addLayoutForCloningAndControlling(std::wstring) */

void __thiscall CLayout::addLayoutForCloningAndControlling(CLayout *this,wstring_conflict *param_2)

{
  wchar_t *__s2;
  ulong uVar1;
  ulong uVar2;
  int iVar3;
  long lVar4;
  ulong uVar5;
  long lVar6;
  long lVar7;
  wstring_conflict local_48 [8];
  undefined8 local_40;

  lVar4 = getLayoutToClone(this,param_2);
  if (lVar4 != 0) {
    return;
  }
  lVar4 = 0x14a6088;
  if (g_LayoutToCloneOrControl._16_8_ != 0) {
    __s2 = *(wchar_t **)param_2;
    uVar1 = *(ulong *)(__s2 + -6);
    lVar7 = g_LayoutToCloneOrControl._16_8_;
    do {
      uVar2 = *(ulong *)(*(wchar_t **)(lVar7 + 0x20) + -6);
      uVar5 = uVar2;
      if (uVar1 <= uVar2) {
        uVar5 = uVar1;
      }
      iVar3 = wmemcmp(*(wchar_t **)(lVar7 + 0x20),__s2,uVar5);
      if (iVar3 == 0) {
        lVar6 = uVar2 - uVar1;
        if (0x7fffffff < lVar6) goto LAB_009de417;
        if (-0x80000001 < lVar6) {
          iVar3 = (int)lVar6;
          goto LAB_009de413;
        }
LAB_009de45b:
        lVar6 = *(long *)(lVar7 + 0x18);
      }
      else {
LAB_009de413:
        if (iVar3 < 0) goto LAB_009de45b;
LAB_009de417:
        lVar6 = *(long *)(lVar7 + 0x10);
        lVar4 = lVar7;
      }
      lVar7 = lVar6;
    } while (lVar7 != 0);
  }
  if (lVar4 != 0x14a6088) {
    uVar1 = *(ulong *)(*(wchar_t **)param_2 + -6);
    uVar2 = *(ulong *)(*(wchar_t **)(lVar4 + 0x20) + -6);
    uVar5 = uVar1;
    if (uVar2 <= uVar1) {
      uVar5 = uVar2;
    }
    iVar3 = wmemcmp(*(wchar_t **)param_2,*(wchar_t **)(lVar4 + 0x20),uVar5);
    if (iVar3 == 0) {
      lVar7 = uVar1 - uVar2;
      if (0x7fffffff < lVar7) goto LAB_009de4e4;
      if (lVar7 < -0x80000000) goto LAB_009de4b0;
      iVar3 = (int)lVar7;
    }
    if (-1 < iVar3) goto LAB_009de4e4;
  }
LAB_009de4b0:
  std::wstring::wstring(local_48,param_2);
  local_40 = 0;
                    /* try { // try from 009de4d4 to 009de4d8 has its CatchHandler @ 009de4f4 */
  lVar4 = std::
          _Rb_tree<std::wstring,std::pair<std::wstring_const,CLayout*>,std::_Select1st<std::pair<std::wstring_const,CLayout*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CLayout*>>>
          ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,CLayout*>,std::_Select1st<std::pair<std::wstring_const,CLayout*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CLayout*>>>
                               *)g_LayoutToCloneOrControl,lVar4,local_48);
  std::wstring::~wstring(local_48);
LAB_009de4e4:
  *(CLayout **)(lVar4 + 0x28) = this;
  this[0x1c8] = (CLayout)0x1;
  return;
}

/* address=009df7d0
   symbol=CLayout::removeAllCloneableObjects */

/* CLayout::removeAllCloneableObjects() */

void CLayout::removeAllCloneableObjects(void)

{
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,CLayout*>,std::_Select1st<std::pair<std::wstring_const,CLayout*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CLayout*>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,CLayout*>,std::_Select1st<std::pair<std::wstring_const,CLayout*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CLayout*>>>
              *)g_LayoutToCloneOrControl,(_Rb_tree_node *)g_LayoutToCloneOrControl._16_8_);
  g_LayoutToCloneOrControl._24_8_ = 0x14a6088;
  g_LayoutToCloneOrControl._16_8_ = 0;
  g_LayoutToCloneOrControl._32_8_ = 0x14a6088;
  g_LayoutToCloneOrControl._40_8_ = 0;
  return;
}

/* address=009df820
   symbol=CLayout::editorObjectCreated */

/* CLayout::editorObjectCreated(CEditorBaseObject*) */

void __thiscall CLayout::editorObjectCreated(CLayout *this,CEditorBaseObject *param_1)

{
  uint uVar1;
  long lVar2;
  void *pvVar3;
  ulong uVar4;
  undefined **ppuVar5;
  uint uVar6;

  if ((*(long *)(param_1 + 0x50) == 0) || (*(long *)(this + 0x48) == *(long *)(param_1 + 0x50))) {
    (**(code **)(*(long *)param_1 + 0x10))(param_1,this);
  }
  if (*(int *)(this + 0x1b8) == 1) {
    lVar2 = __dynamic_cast(param_1,&CEditorBaseObject::typeinfo,&CParticleTechWrapper::typeinfo,0);
    if ((lVar2 != 0) ||
       (lVar2 = __dynamic_cast(param_1,&CEditorBaseObject::typeinfo,&CSoundObject::typeinfo,0),
       lVar2 != 0)) goto LAB_009df8ad;
    ppuVar5 = &CCameraShake::typeinfo;
  }
  else {
    if (*(int *)(this + 0x1b8) != 2) {
      return;
    }
    lVar2 = __dynamic_cast(param_1,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo,0);
    if (lVar2 != 0) {
      *(undefined1 *)(lVar2 + 0x8c) = 1;
      uVar1 = *(uint *)(this + 0x1d8);
      if (uVar1 < *(uint *)(this + 0x1dc)) {
        pvVar3 = *(void **)(this + 0x1d0);
      }
      else if (*(long *)(this + 0x1d0) == 0) {
        *(uint *)(this + 0x1dc) = *(uint *)(this + 0x1e0);
        pvVar3 = operator_new__((ulong)*(uint *)(this + 0x1e0) * 8);
        *(void **)(this + 0x1d0) = pvVar3;
        uVar1 = *(uint *)(this + 0x1d8);
      }
      else {
        uVar6 = *(uint *)(this + 0x1dc) + *(int *)(this + 0x1e0);
        pvVar3 = operator_new__((ulong)uVar6 << 3);
        if (*(int *)(this + 0x1dc) != 0) {
          uVar1 = 0;
          do {
            uVar4 = (ulong)uVar1;
            uVar1 = uVar1 + 1;
            *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x1d0) + uVar4 * 8);
          } while (uVar1 < *(uint *)(this + 0x1dc));
        }
        if (*(void **)(this + 0x1d0) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x1d0));
        }
        uVar1 = *(uint *)(this + 0x1d8);
        *(void **)(this + 0x1d0) = pvVar3;
        *(uint *)(this + 0x1dc) = uVar6;
      }
      *(CEditorBaseObject **)((long)pvVar3 + (ulong)uVar1 * 8) = param_1;
      *(int *)(this + 0x1d8) = *(int *)(this + 0x1d8) + 1;
      return;
    }
    ppuVar5 = &CSoundObject::typeinfo;
  }
  lVar2 = __dynamic_cast(param_1,&CEditorBaseObject::typeinfo,ppuVar5,0);
  if (lVar2 == 0) {
    return;
  }
LAB_009df8ad:
  TArrayList<CEditorBaseObject*>::add((TArrayList<CEditorBaseObject*> *)(this + 0x1d0),param_1);
  return;
}

/* address=009dfa60
   symbol=CLayout::initOnLoad */

/* WARNING: Removing unreachable block (ram,0x009dfb3c) */
/* CLayout::initOnLoad() */

void __thiscall CLayout::initOnLoad(CLayout *this)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  long *plVar4;
  uint uVar5;
  long local_28;
  allocator local_19 [9];

  if (this[0x1a0] == (CLayout)0x0) {
                    /* try { // try from 009dfa92 to 009dfa96 has its CatchHandler @ 009dfaf5 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"Timeline",local_19);
                    /* try { // try from 009dfa9d to 009dfaa1 has its CatchHandler @ 009dfb00 */
    plVar3 = (long *)CEditorScene::GetObjectsCreatedByADescriptor
                               ((CEditorScene *)this,(wstring_conflict *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if ((plVar3 != (long *)0x0) && ((int)plVar3[1] != 0)) {
      uVar5 = 0;
      do {
        if (uVar5 < *(uint *)((long)plVar3 + 0xc)) {
          plVar4 = (long *)((ulong)uVar5 * 8 + *plVar3);
        }
        else {
          plVar4 = (long *)*plVar3;
        }
        uVar5 = uVar5 + 1;
        *(undefined1 *)(*plVar4 + 0x8a) = 0;
      } while (uVar5 < *(uint *)(plVar3 + 1));
    }
  }
  return;
}

/* address=009dfb50
   symbol=CLayout::~CLayout */

/* WARNING: Removing unreachable block (ram,0x009dfdf4) */
/* WARNING: Removing unreachable block (ram,0x009dfe01) */
/* CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  int *piVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  _Rb_tree_node_base *p_Var5;
  int iVar6;
  void *pvVar7;
  ulong uVar8;
  _Rb_tree_node_base *p_Var9;
  long lVar10;
  allocator *paVar11;
  _Rb_tree_node_base *local_50;
  wchar_t *local_48 [3];

  *(undefined ***)this = &PTR__CLayout_00fd9770;
  *(undefined ***)(this + 400) = &PTR__CLayout_00fd99e8;
  *(undefined ***)(this + 0x198) = &PTR__CLayout_00fd9a18;
  if (*(long **)(this + 0x1f0) != (long *)0x0) {
                    /* try { // try from 009dfba1 to 009dfba3 has its CatchHandler @ 009dfdbf */
    (**(code **)(**(long **)(this + 0x1f0) + 8))();
    *(undefined8 *)(this + 0x1f0) = 0;
  }
  if (this[0x1c8] == (CLayout)0x0) goto LAB_009dfbb8;
  this[0x1c8] = (CLayout)0x0;
                    /* try { // try from 009dfc43 to 009dfd32 has its CatchHandler @ 009dfdbf */
  std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(this + 0x168));
  local_50 = (_Rb_tree_node_base *)(g_LayoutToCloneOrControl + 8);
  if (g_LayoutToCloneOrControl._16_8_ != 0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    p_Var9 = (_Rb_tree_node_base *)g_LayoutToCloneOrControl._16_8_;
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(p_Var9 + 0x20) + -6);
      uVar8 = uVar4;
      if (uVar3 <= uVar4) {
        uVar8 = uVar3;
      }
      iVar6 = wmemcmp(*(wchar_t **)(p_Var9 + 0x20),local_48[0],uVar8);
      if (iVar6 == 0) {
        lVar10 = uVar4 - uVar3;
        if (0x7fffffff < lVar10) goto LAB_009dfc77;
        if (-0x80000001 < lVar10) {
          iVar6 = (int)lVar10;
          goto LAB_009dfc73;
        }
LAB_009dfcbb:
        p_Var5 = *(_Rb_tree_node_base **)(p_Var9 + 0x18);
      }
      else {
LAB_009dfc73:
        if (iVar6 < 0) goto LAB_009dfcbb;
LAB_009dfc77:
        p_Var5 = *(_Rb_tree_node_base **)(p_Var9 + 0x10);
        local_50 = p_Var9;
      }
      p_Var9 = p_Var5;
    } while (p_Var9 != (_Rb_tree_node_base *)0x0);
  }
  paVar11 = (allocator *)(local_48[0] + -6);
  if (local_50 != (_Rb_tree_node_base *)(g_LayoutToCloneOrControl + 8)) {
    uVar3 = *(ulong *)paVar11;
    uVar4 = *(ulong *)(*(wchar_t **)(local_50 + 0x20) + -6);
    uVar8 = uVar3;
    if (uVar4 <= uVar3) {
      uVar8 = uVar4;
    }
    iVar6 = wmemcmp(local_48[0],*(wchar_t **)(local_50 + 0x20),uVar8);
    if (iVar6 == 0) {
      lVar10 = uVar3 - uVar4;
      if (lVar10 < 0x80000000) {
        if (-0x80000001 < lVar10) {
          iVar6 = (int)lVar10;
          goto LAB_009dfd5b;
        }
        goto LAB_009dfd09;
      }
    }
    else {
LAB_009dfd5b:
      if (iVar6 < 0) {
LAB_009dfd09:
        local_50 = (_Rb_tree_node_base *)(g_LayoutToCloneOrControl + 8);
      }
    }
  }
  if (paVar11 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(paVar11);
    }
  }
  if (local_50 != (_Rb_tree_node_base *)(g_LayoutToCloneOrControl + 8)) {
    pvVar7 = (void *)std::_Rb_tree_rebalance_for_erase
                               (local_50,(_Rb_tree_node_base *)(g_LayoutToCloneOrControl + 8));
    paVar11 = (allocator *)(*(long *)((long)pvVar7 + 0x20) + -0x18);
    if (paVar11 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)((long)pvVar7 + 0x20) + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::wstring::_Rep::_M_destroy(paVar11);
      }
    }
    operator_delete(pvVar7);
    g_LayoutToCloneOrControl._40_8_ = g_LayoutToCloneOrControl._40_8_ + -1;
  }
LAB_009dfbb8:
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  if (*(void **)(this + 0x1d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1d0));
  }
  *(undefined8 *)(this + 0x1d0) = 0;
  *(undefined ***)(this + 0x198) = &PTR__iHighlight_00fd19d0;
  *(undefined ***)(this + 400) = &PTR__iRandomWeight_00fd1a10;
  CAllDescriptorsScene::~CAllDescriptorsScene((CAllDescriptorsScene *)this);
  return;
}

/* address=009dfe10
   symbol=CLayout::~CLayout */

/* non-virtual thunk to CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  ~CLayout(this + -0x198);
  return;
}

/* address=009dfe20
   symbol=CLayout::~CLayout */

/* non-virtual thunk to CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  ~CLayout(this + -400);
  return;
}

/* address=009dfe30
   symbol=CLayout::~CLayout */

/* non-virtual thunk to CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  ~CLayout(this + -0x198);
  return;
}

/* address=009dfe40
   symbol=CLayout::~CLayout */

/* non-virtual thunk to CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  ~CLayout(this + -400);
  return;
}

/* address=009dfe50
   symbol=CLayout::~CLayout */

/* CLayout::~CLayout() */

void __thiscall CLayout::~CLayout(CLayout *this)

{
  ~CLayout(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=009dfe70
   symbol=CLayout::loadLayoutFile */

/* WARNING: Removing unreachable block (ram,0x009e0905) */
/* WARNING: Removing unreachable block (ram,0x009e080c) */
/* WARNING: Removing unreachable block (ram,0x009e09d8) */
/* WARNING: Removing unreachable block (ram,0x009e0959) */
/* WARNING: Removing unreachable block (ram,0x009e08a1) */
/* WARNING: Removing unreachable block (ram,0x009e0896) */
/* WARNING: Removing unreachable block (ram,0x009e09e3) */
/* WARNING: Removing unreachable block (ram,0x009e0817) */
/* WARNING: Removing unreachable block (ram,0x009e07a6) */
/* WARNING: Removing unreachable block (ram,0x009e0764) */
/* WARNING: Removing unreachable block (ram,0x009e0728) */
/* WARNING: Removing unreachable block (ram,0x009e079b) */
/* CLayout::loadLayoutFile(std::wstring const&, bool, CTimerStatics*, bool, bool, unsigned int) */

void __thiscall
CLayout::loadLayoutFile
          (CLayout *this,wstring_conflict *param_1,bool param_2,CTimerStatics *param_3,bool param_4,
          bool param_5,uint param_6)

{
  wchar_t *pwVar1;
  int *piVar2;
  wstring_conflict *pwVar3;
  wchar_t wVar4;
  size_t sVar5;
  code *pcVar6;
  wchar_t *__s1;
  CResourceManager *pCVar7;
  char cVar8;
  int iVar9;
  ulong *puVar10;
  undefined8 uVar11;
  uint uVar12;
  ulong *puVar13;
  ulong uVar14;
  long lVar15;
  allocator *paVar16;
  bool bVar17;
  uint uVar18;
  wchar_t *local_150;
  bool local_141;
  bool local_131;
  undefined8 local_128;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  long local_108 [2];
  wchar_t *local_f8 [2];
  wstring_conflict local_e8 [16];
  wstring_conflict local_d8 [16];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  wchar_t *local_88 [2];
  wchar_t *local_78 [2];
  long local_68 [2];
  wchar_t *local_58 [5];

  STRINGS::StringUpper((STRINGS *)local_68,param_1);
                    /* try { // try from 009dfeb0 to 009dfeb4 has its CatchHandler @ 009e0883 */
  FILESYSTEM::CleanPath((FILESYSTEM *)local_58,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_68[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (*(long *)(local_58[0] + -6) == 0) goto LAB_009dfee3;
  pwVar3 = (wstring_conflict *)(this + 0x168);
                    /* try { // try from 009dff1f to 009dff23 has its CatchHandler @ 009e075f */
  std::wstring::wstring((wstring_conflict *)local_78,pwVar3);
  if ((*(size_t *)(local_58[0] + -6) == *(size_t *)(local_78[0] + -6)) &&
     (iVar9 = wmemcmp(local_58[0],local_78[0],*(size_t *)(local_58[0] + -6)), iVar9 == 0)) {
    bVar17 = !param_5;
  }
  else {
    bVar17 = false;
  }
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_78[0] + -2;
    wVar4 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar4 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
    }
  }
  if (bVar17) goto LAB_009dfee3;
                    /* try { // try from 009dff66 to 009dffdb has its CatchHandler @ 009e0822 */
  CEditorScene::setFileLoaded((CEditorScene *)this,(wstring_conflict *)local_58);
  cVar8 = CResourceManager::getEditorIsRunning();
  if (cVar8 == '\0') {
    local_131 = param_2;
    if (*(int *)(this + 0x1b8) == 1) {
      if ((char)g_bCachParticles != '\0') {
        this[0x1e8] = (CLayout)0x1;
        if (*(long **)(this + 0x1f0) != (long *)0x0) {
                    /* try { // try from 009e04d6 to 009e04f8 has its CatchHandler @ 009e0822 */
          (**(code **)(**(long **)(this + 0x1f0) + 8))();
          *(undefined8 *)(this + 0x1f0) = 0;
        }
        std::wstring::wstring((wstring_conflict *)local_88,pwVar3);
        pCVar7 = *(CResourceManager **)(this + 0x68);
                    /* try { // try from 009e0508 to 009e050c has its CatchHandler @ 009e0900 */
        std::wstring::wstring((wstring_conflict *)local_108,(wstring_conflict *)local_88);
                    /* try { // try from 009e050d to 009e0520 has its CatchHandler @ 009e08e8 */
        lVar15 = CMasterResourceManager::getSingleton();
        CParticlePreloader::LoadParticle
                  (*(CParticlePreloader **)(lVar15 + 0xf8),(wstring_conflict *)local_108);
        if ((allocator *)(local_108[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_108[0] + -8);
          iVar9 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar9 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
          }
        }
                    /* try { // try from 009e053b to 009e0551 has its CatchHandler @ 009e0900 */
        lVar15 = CMasterResourceManager::getSingleton();
        uVar11 = CParticlePreloader::GetParticle
                           (*(CParticlePreloader **)(lVar15 + 0xf8),pCVar7,local_88[0]);
        *(undefined8 *)(this + 0x1f0) = uVar11;
                    /* try { // try from 009e055c to 009e0591 has its CatchHandler @ 009e0822 */
        std::wstring::~wstring((wstring_conflict *)local_88);
        if (*(CSceneNodeObject **)(this + 0x1f0) != (CSceneNodeObject *)0x0) {
          CSceneNodeObject::sceneNodeSetParent
                    (*(CSceneNodeObject **)(this + 0x1f0),*(SceneNode **)(this + 0x58),false);
          (**(code **)(**(long **)(this + 0x1f0) + 0x58))(0,0);
        }
        goto LAB_009dfee3;
      }
      goto LAB_009e00a0;
    }
  }
  else {
LAB_009e00a0:
    local_131 = true;
  }
  local_141 = param_4;
  if (!param_4) {
    local_141 = true;
    if (*(int *)(this + 0x1b8) != 0) {
      local_141 = *(int *)(this + 0x1b8) == 2;
    }
  }
  if ((loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::mRecursiveFix
       == '\0') &&
     (iVar9 = __cxa_guard_acquire(&loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)
                                   ::mRecursiveFix), iVar9 != 0)) {
    loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::mRecursiveFix =
         (ulong *)0x0;
    DAT_014a60d8 = 0;
    DAT_014a60dc = 0;
    DAT_014a60e0 = 100;
    __cxa_guard_release(&loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)
                         ::mRecursiveFix);
    __cxa_atexit(TArrayList<std::wstring>::~TArrayList,
                 &loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
                  mRecursiveFix,&__dso_handle);
  }
  if (DAT_014a60d8 == 0) {
    loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::iChildCount = 0;
  }
  std::wstring::wstring((wstring_conflict *)local_98,pwVar3);
                    /* try { // try from 009dffec to 009e0127 has its CatchHandler @ 009e0951 */
  std::wstring::wstring((wstring_conflict *)local_a8,(wstring_conflict *)local_98);
  uVar18 = DAT_014a60d8;
  if (DAT_014a60d8 != 0) {
    uVar12 = 0;
    sVar5 = *(size_t *)(local_a8[0] + -6);
    puVar13 = loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
              mRecursiveFix;
    do {
      if ((*(size_t *)((wchar_t *)*puVar13 + -6) == sVar5) &&
         (iVar9 = wmemcmp((wchar_t *)*puVar13,local_a8[0],sVar5), iVar9 == 0)) goto LAB_009e004b;
      uVar12 = uVar12 + 1;
      puVar13 = puVar13 + 1;
    } while (uVar12 < uVar18);
  }
  uVar12 = 0xffffffff;
LAB_009e004b:
  if ((allocator *)(local_a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_a8[0] + -2;
    wVar4 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar4 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
    }
  }
  if (uVar12 != 0xffffffff) {
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_98[0] + -8);
      iVar9 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
LAB_009dfee3:
    if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_58[0] + -2;
      wVar4 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
      }
    }
    return;
  }
  std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)local_98);
  puVar13 = loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
            mRecursiveFix;
  uVar18 = DAT_014a60dc;
  if (DAT_014a60dc <= DAT_014a60d8) {
    if (loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
        mRecursiveFix == (ulong *)0x0) {
      uVar14 = (ulong)DAT_014a60e0;
      DAT_014a60dc = DAT_014a60e0;
                    /* try { // try from 009e0668 to 009e066c has its CatchHandler @ 009e06fb */
      puVar10 = operator_new__(uVar14 * 8 + 8);
      *puVar10 = uVar14;
      puVar13 = puVar10 + 1;
      while (uVar14 = uVar14 - 1, uVar18 = DAT_014a60dc, uVar14 != 0xffffffffffffffff) {
        puVar10[1] = (ulong)&DAT_01424558;
        puVar10 = puVar10 + 1;
      }
    }
    else {
      uVar18 = DAT_014a60dc + DAT_014a60e0;
      uVar14 = (ulong)uVar18;
                    /* try { // try from 009e015e to 009e023b has its CatchHandler @ 009e06fb */
      puVar10 = operator_new__(uVar14 * 8 + 8);
      *puVar10 = uVar14;
      puVar13 = puVar10 + 1;
      if (uVar14 != 0) {
        lVar15 = uVar14 - 2;
        do {
          lVar15 = lVar15 + -1;
          puVar10[1] = (ulong)&DAT_01424558;
          puVar10 = puVar10 + 1;
        } while (lVar15 != -2);
      }
      if (DAT_014a60dc != 0) {
        uVar12 = 0;
        do {
          std::wstring::assign((wstring_conflict *)(puVar13 + uVar12));
          uVar12 = uVar12 + 1;
        } while (uVar12 < DAT_014a60dc);
      }
      if (loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
          mRecursiveFix != (ulong *)0x0) {
        puVar10 = loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
                  mRecursiveFix +
                  loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
                  mRecursiveFix[-1];
        while (puVar10 !=
               loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
               mRecursiveFix) {
          puVar10 = puVar10 + -1;
          paVar16 = (allocator *)(*puVar10 - 0x18);
          if (paVar16 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*puVar10 - 8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::wstring::_Rep::_M_destroy(paVar16);
            }
          }
        }
        operator_delete__(puVar10 + -1);
      }
    }
  }
  DAT_014a60dc = uVar18;
  loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::mRecursiveFix =
       puVar13;
  std::wstring::assign
            ((wstring_conflict *)
             (loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
              mRecursiveFix + DAT_014a60d8));
  DAT_014a60d8 = DAT_014a60d8 + 1;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  if (*(char *)(*(long *)(this + 0x68) + 0x42) != '\0') {
    loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::iChildCount =
         loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::iChildCount
         + 1;
    iVar9 = CResourceManager::getCurrentLevelSeed(*(CResourceManager **)(this + 0x68));
    UTILITIES::setSeed(param_6 + DAT_014a60d8 +
                       loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)
                       ::iChildCount + iVar9);
  }
  *(undefined4 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1dc) = 0;
  if (*(void **)(this + 0x1d0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1d0));
  }
  *(undefined8 *)(this + 0x1d0) = 0;
                    /* try { // try from 009e0299 to 009e0303 has its CatchHandler @ 009e0951 */
  CEditorScene::DeleteAllObjectsFromScene((CEditorScene *)this);
  std::wstring::wstring((wstring_conflict *)local_c8,pwVar3);
  lVar15 = getLayoutToClone(this,(wstring_conflict *)local_c8);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_c8[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if ((local_141 == false) && (lVar15 != 0)) {
    if (*(long *)(this + 0x48) != 0) {
      local_128 = 0;
      local_120 = 0;
      local_11c = 0;
      local_118 = 0x19;
                    /* try { // try from 009e0491 to 009e0496 has its CatchHandler @ 009e08ac */
      (**(code **)(*(long *)this + 0x1f8))
                (this,lVar15,(TArrayList<CEditorBaseObject*> *)&local_128,param_3);
      TArrayList<CEditorBaseObject*>::~TArrayList((TArrayList<CEditorBaseObject*> *)&local_128);
      goto LAB_009e0348;
    }
                    /* try { // try from 009e04b5 to 009e04ba has its CatchHandler @ 009e0951 */
    (**(code **)(*(long *)this + 0x1f8))(this,lVar15,0,param_3);
  }
  else {
    pcVar6 = *(code **)(*(long *)this + 0x1e8);
    std::wstring::wstring(local_d8,pwVar3);
                    /* try { // try from 009e0321 to 009e0323 has its CatchHandler @ 009e0964 */
    (*pcVar6)(this,local_d8,0,0,0xffffffffffffffff,local_131,param_3);
                    /* try { // try from 009e0327 to 009e035c has its CatchHandler @ 009e0951 */
    std::wstring::~wstring(local_d8);
                    /* try { // try from 009e059b to 009e05bc has its CatchHandler @ 009e0951 */
    if ((local_141 == false) && (cVar8 = CResourceManager::getEditorIsRunning(), cVar8 == '\0')) {
      std::wstring::wstring(local_e8,pwVar3);
                    /* try { // try from 009e05c3 to 009e05c7 has its CatchHandler @ 009e09d6 */
      addLayoutForCloningAndControlling(this,local_e8);
                    /* try { // try from 009e05cb to 009e061f has its CatchHandler @ 009e0951 */
      std::wstring::~wstring(local_e8);
    }
  }
  cVar8 = CResourceManager::getEditorIsRunning();
  if (cVar8 != '\0') {
    setStartOnLoad(this,(bool)this[0x1a0]);
  }
LAB_009e0348:
  std::wstring::wstring((wstring_conflict *)local_f8,(wstring_conflict *)local_98);
  pwVar1 = local_f8[0];
  uVar18 = DAT_014a60d8;
  puVar13 = loadLayoutFile(std::wstring_const&,bool,CTimerStatics*,bool,bool,unsigned_int)::
            mRecursiveFix;
  if (DAT_014a60d8 == 0) {
LAB_009e0640:
    local_150 = local_f8[0];
  }
  else {
    lVar15 = 0;
    uVar12 = 0;
    local_150 = local_f8[0];
    sVar5 = *(size_t *)(local_f8[0] + -6);
    do {
      __s1 = *(wchar_t **)((long)puVar13 + lVar15);
      if ((*(size_t *)(__s1 + -6) == sVar5) && (iVar9 = wmemcmp(__s1,pwVar1,sVar5), iVar9 == 0)) {
        if (uVar12 < uVar18) {
          DAT_014a60d8 = uVar18 - 1;
                    /* try { // try from 009e063b to 009e063f has its CatchHandler @ 009e0910 */
          std::wstring::assign((wstring_conflict *)((long)puVar13 + lVar15));
          goto LAB_009e0640;
        }
        break;
      }
      uVar12 = uVar12 + 1;
      lVar15 = lVar15 + 8;
    } while (uVar12 < uVar18);
  }
  if ((allocator *)(local_150 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_150 + -2;
    wVar4 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar4 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_150 + -6));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -6) == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    return;
  }
  LOCK();
  pwVar1 = local_58[0] + -2;
  wVar4 = *pwVar1;
  *pwVar1 = *pwVar1 + L'\xffffffff';
  UNLOCK();
  if (L'\0' < wVar4) {
    return;
  }
  std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
  return;
}

/* address=009e09f0
   symbol=CLayout::GetRandomWeight */

/* non-virtual thunk to CLayout::GetRandomWeight() */

void __thiscall CLayout::GetRandomWeight(CLayout *this)

{
  GetRandomWeight(this + -400);
  return;
}

/* address=009e0a00
   symbol=CLayout::GetRandomWeight */

/* CLayout::GetRandomWeight() */

undefined4 __thiscall CLayout::GetRandomWeight(CLayout *this)

{
  return *(undefined4 *)(this + 0x1a4);
}

/* address=009e0a10
   symbol=CLayout::SetRandomWeight */

/* non-virtual thunk to CLayout::SetRandomWeight(unsigned int) */

void __thiscall CLayout::SetRandomWeight(CLayout *this,uint param_1)

{
  SetRandomWeight(this + -400,param_1);
  return;
}

/* address=009e0a20
   symbol=CLayout::SetRandomWeight */

/* CLayout::SetRandomWeight(unsigned int) */

void __thiscall CLayout::SetRandomWeight(CLayout *this,uint param_1)

{
  *(uint *)(this + 0x1a4) = param_1;
  return;
}

/* export-summary functions=37 failures=0 */
