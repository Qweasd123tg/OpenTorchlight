/* Targeted Ghidra class export.
   namespace=CLayoutScene
   Treat pseudocode as navigation evidence. */


/* address=0075ec10
   symbol=CLayoutScene::fireEvent */

/* CLayoutScene::fireEvent(EEDITOR_EVENTS, long long) */

void CLayoutScene::fireEvent(long param_1,uint param_2)

{
  long lVar1;
  CSoundObject *this;
  long *plVar2;
  uint uVar3;

  if (param_2 < 2) {
    lVar1 = CDescriptorManager::GetDescriptor
                      (*(CDescriptorManager **)(param_1 + 0x100),L"Sound",false);
    if ((lVar1 != 0) && (*(int *)(lVar1 + 0xe8) != 0)) {
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(lVar1 + 0xec)) {
          plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(lVar1 + 0xe0));
        }
        else {
          plVar2 = *(long **)(lVar1 + 0xe0);
        }
        if (*plVar2 != 0) {
          this = (CSoundObject *)
                 __dynamic_cast(*plVar2,&CEditorBaseObject::typeinfo,&CSoundObject::typeinfo,0);
          if (this != (CSoundObject *)0x0) {
            if (param_2 == 1) {
              CSoundObject::play(this);
            }
            else {
              CSoundObject::stop(this);
            }
          }
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(lVar1 + 0xe8));
    }
  }
  return;
}

/* address=0075ecc0
   symbol=CLayoutScene::createDescriptors */

/* CLayoutScene::createDescriptors() */

void __thiscall CLayoutScene::createDescriptors(CLayoutScene *this)

{
  char cVar1;

  cVar1 = CResourceManager::getEditorIsRunning();
  if (cVar1 == '\0') {
    return;
  }
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Group");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Monster");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Unit Spawner");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Layout Link");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Layout Link Particle");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Layout Link Timeline");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Generic Model");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Room Piece");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Sound");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Music");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Missile");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Light");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Image");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Button");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Timeline");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Logic Group");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Player Sphere Trigger");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Player Box Trigger");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Unit Trigger");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Counter");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Random Choice");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Warper");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Path");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Teleport");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Timer");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Output Incrementor");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Camera Shake");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Property Node");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Damage Shape");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Puzzle Input");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Interactive");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Camera Controller");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Game State Controller");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Quest Controller");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Skill Controller");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Pathing");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Animation Controller");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Skip Cutscene");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Cinematic");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Money Taker");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Dungeon Object");
  CEditorScene::AddDescriptor((CEditorScene *)this,L"Waypoint Activator");
  return;
}

/* address=0075ef00
   symbol=CLayoutScene::~CLayoutScene */

/* CLayoutScene::~CLayoutScene() */

void __thiscall CLayoutScene::~CLayoutScene(CLayoutScene *this)

{
  *(undefined ***)this = &PTR__CLayoutScene_00fc5db0;
  CEditorScene::~CEditorScene((CEditorScene *)this);
  return;
}

/* address=0075ef10
   symbol=CLayoutScene::~CLayoutScene */

/* CLayoutScene::~CLayoutScene() */

void __thiscall CLayoutScene::~CLayoutScene(CLayoutScene *this)

{
  ~CLayoutScene(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=0075ef30
   symbol=CLayoutScene::CLayoutScene */

/* CLayoutScene::CLayoutScene() */

void __thiscall CLayoutScene::CLayoutScene(CLayoutScene *this)

{
  CEditorScene::CEditorScene((CEditorScene *)this,L"Layout");
  *(undefined ***)this = &PTR__CLayoutScene_00fc5db0;
  return;
}

/* address=007690f0
   symbol=CLayoutScene::_GLOBAL__I_CLayoutScene */

/* CLayoutScene::CLayoutScene() */

void CLayoutScene::_GLOBAL__I_CLayoutScene(void)

{
  allocator aStack_3b1;
  allocator aStack_3b0;
  allocator aStack_3af;
  allocator aStack_3ae;
  allocator aStack_3ad;
  allocator aStack_3ac;
  allocator aStack_3ab;
  allocator aStack_3aa;
  allocator aStack_3a9;
  allocator aStack_3a8;
  allocator aStack_3a7;
  allocator aStack_3a6;
  allocator aStack_3a5;
  allocator aStack_3a4;
  allocator aStack_3a3;
  allocator aStack_3a2;
  allocator aStack_3a1;
  allocator aStack_3a0;
  allocator aStack_39f;
  allocator aStack_39e;
  allocator aStack_39d;
  allocator aStack_39c;
  allocator aStack_39b;
  allocator aStack_39a;
  allocator aStack_399;
  allocator aStack_398;
  allocator aStack_397;
  allocator aStack_396;
  allocator aStack_395;
  allocator aStack_394;
  allocator aStack_393;
  allocator aStack_392;
  allocator aStack_391;
  allocator aStack_390;
  allocator aStack_38f;
  allocator aStack_38e;
  allocator aStack_38d;
  allocator aStack_38c;
  allocator aStack_38b;
  allocator aStack_38a;
  allocator aStack_389;
  allocator aStack_388;
  allocator aStack_387;
  allocator aStack_386;
  allocator aStack_385;
  allocator aStack_384;
  allocator aStack_383;
  allocator aStack_382;
  allocator aStack_381;
  allocator aStack_380;
  allocator aStack_37f;
  allocator aStack_37e;
  allocator aStack_37d;
  allocator aStack_37c;
  allocator aStack_37b;
  allocator aStack_37a;
  allocator aStack_379;
  allocator aStack_378;
  allocator aStack_377;
  allocator aStack_376;
  allocator aStack_375;
  allocator aStack_374;
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
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_3b1);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_3b0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_3af);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_3ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_3ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_3ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_3ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_3aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_3a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_3a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_3a7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_3a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_3a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_3a4);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_3a3);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_3a2);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_3a1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_3a0);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_39f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_39e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_39d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_39c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_39b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_39a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_399);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_398);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_397);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_396);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_395)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_394);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_393);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_392);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_391);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_390);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_38f);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_38e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_38d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_38c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_38b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_38a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_389);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_388);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_387);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_386);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_385);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_384);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_383);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_382);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_381);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_380);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_37f);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_37e);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_37d);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_37c);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_37b);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_37a);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_379);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_378);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_377);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_376);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_375);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_374);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_373);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_372);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_371)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_370);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_36f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_36e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_36d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_36c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_36b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_36a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_369);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_368);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_367);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_366);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_365);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_364);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_363);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_362);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_361);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_360);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_35f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_35e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_35d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_35c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_35b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_35a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_359);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_358);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_357);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_356);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_355)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_354)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_353);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_352)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_351);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_350);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_34f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_34e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_34d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_34c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_34b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_34a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_349);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_348);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_347);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_346);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_345);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_344);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_343);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_342);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_341)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",
             &aStack_340);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_33f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_33e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_33d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_33c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_33b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_33a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_339);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_338);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_337);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_336);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_335);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_334);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_333);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_332);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_331);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_330);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_32f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_32e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",
             &aStack_32d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_32c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_32b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_32a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_328);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_327);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_326);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_325);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_324);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_323);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_322);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_321);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_320);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_31f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_31e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_31d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_31c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_31b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_31a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_319);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_318);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_317);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_316);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_315);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_314);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_313)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_312);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_311);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_310);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_30f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_30e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_30d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_30c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_30b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_30a
            );
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_309)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_308);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_307);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_306);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_305);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_304)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_303);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_302);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_301);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_2fe);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_2fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_2fc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_2fb)
  ;
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gINPUT_EVENT_NAMES,L"Show",&aStack_2fa);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 8),L"Hide",&aStack_2f9);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x10),L"Enable",&aStack_2f8);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x18),L"Disable",&aStack_2f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x20),L"Enable and Show",&aStack_2f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x28),L"Disable and Hide",&aStack_2f5);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x30),L"Reset",&aStack_2f4);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x38),L"Add",&aStack_2f3);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x40),L"Subtract",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x48),L"Play",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x50),L"Stop",&aStack_2f0);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x58),L"Pause",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x60),L"Resume",&aStack_2ee);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x68),L"Play Level Music",&aStack_2ed);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x70),L"Increment",&aStack_2ec);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x78),L"Activate",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x80),L"Start Particle",&aStack_2ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x88),L"Stop Particle",&aStack_2e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x90),L"Force Stop Particle",&aStack_2e8);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x98),L"Pause Particle",&aStack_2e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa0),L"Resume Particle",&aStack_2e6);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa8),L"Play",&aStack_2e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb0),L"Play Backwards",&aStack_2e4);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb8),L"Stop",&aStack_2e3);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xc0),L"Stop to End",&aStack_2e2);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 200),L"Pause",&aStack_2e1);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd0),L"Reset",&aStack_2e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd8),L"Reset To End",&aStack_2df);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe0),L"Fast Forward To End",&aStack_2de);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe8),L"Rewind to Start",&aStack_2dd);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf0),L"Set State One",&aStack_2dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf8),L"Set State Two",&aStack_2db);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x100),L"Spawn Units",&aStack_2da);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x108),L"Destroy Spawned Units",&aStack_2d9
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x110),L"Hide And Disable Spawned Units",
             &aStack_2d8);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x118),L"Increment Level Delta",&aStack_2d7
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x120),L"Decrement Level Delta",&aStack_2d6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x128),L"Activate Warper",&aStack_2d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x130),L"Activate Teleport",&aStack_2d4);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x138),L"Roll",&aStack_2d3);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x140),L"Input 1",&aStack_2d2);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x148),L"Input 2",&aStack_2d1);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x150),L"Input 3",&aStack_2d0);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x158),L"Input 4",&aStack_2cf);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x160),L"Input 5",&aStack_2ce);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x168),L"Input 6",&aStack_2cd);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x170),L"Trigger",&aStack_2cc);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x178),L"Toggle",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x180),L"Interact",&aStack_2ca);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x188),L"Make Invulnerable",&aStack_2c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 400),L"Make Vulnerable",&aStack_2c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x198),L"Start Camera",&aStack_2c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a0),L"Camera Off",&aStack_2c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a8),L"Force Accept",&aStack_2c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b0),L"Force Not Accepted",&aStack_2c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b8),L"Force Complete",&aStack_2c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c0),L"Force Not Complete",&aStack_2c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c8),L"Start Skill",&aStack_2c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d0),L"Stop Skill",&aStack_2c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d8),L"Learn Skill",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e0),L"Unlearn Skill",&aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e8),L"Alert Monster",&aStack_2bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f0),L"Enable Targeting",&aStack_2bc);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f8),L"Disable Targeting",&aStack_2bb);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x200),L"Enable Targeting & Alert",
             &aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x208),L"Hunt",&aStack_2b9);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x210),L"Play",&aStack_2b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x218),L"Play Looping",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x220),L"Stop",&aStack_2b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x228),L"Stop and Idle",&aStack_2b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x230),L"Cannot be Targeted",&aStack_2b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x238),L"Can be Targeted",&aStack_2b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x240),L"Add as Pet",&aStack_2b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x248),L"Remove as Pet",&aStack_2b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x250),L"Kill Monster",&aStack_2b0);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 600),L"Warp Pets to Player",&aStack_2af);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x260),L"Heal Player",&aStack_2ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x268),L"Collidable",&aStack_2ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x270),L"Not Collidable",&aStack_2ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x278),L"Take Money",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x280),L"Show Tip",&aStack_2aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x288),L"Clear History",&aStack_2a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x290),L"Stop Skills",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x298),L"Kill Pets",&aStack_2a7)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a0),L"Stop",&aStack_2a6);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a8),L"Start",&aStack_2a5);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b0),L"Pause",&aStack_2a4);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b8),L"Input1",&aStack_2a3);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c0),L"Input2",&aStack_2a2);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c8),L"Input3",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d0),L"Input4",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d8),L"Input5",&aStack_29f);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPOSITIONABLE_OBJECT_INPUT_EVENT_NAMES,L"Show",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)&DAT_01466ba8,L"Hide",&aStack_29d);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gRANDOMGROUP_NAMES,L"ALL",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 8),L"Weight",&aStack_29b);
  std::wstring::wstring
            ((wstring_conflict *)(gRANDOMGROUP_NAMES + 0x10),L"Random Chance",&aStack_29a);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_299);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_298);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_297);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_296);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_295);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_294);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_28f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_28d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_28a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_289);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_288);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_287);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_286)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_281);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_27a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_277);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_273);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_INTERP_TYPES,L"Linear",&aStack_272);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 8),L"Linear Round",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x10),L"Linear Round Down",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x18),L"Linear Round Up",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x20),L"Spline",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x28),L"Quaternion",&aStack_26d);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x30),L"No Interpolation",&aStack_26c);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x38),L"Use Timeline Default",&aStack_26b
            );
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_26a);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_269);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_268)
  ;
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_267);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_265);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_263);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",
             &aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_25b);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",
             &aStack_25a);
  std::wstring::wstring((wstring_conflict *)&DAT_01466e18,L"Add",&aStack_259);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_258);
  std::wstring::wstring((wstring_conflict *)&DAT_01466e28,L"Texture",&aStack_257);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_254)
  ;
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_252);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_251);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_250);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_24f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_24e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_24d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_24c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_24b);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_24a);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_249);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_245);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_240);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_23c);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_23a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_239);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_237);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_236);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1d5);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1ce);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1c9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1c7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1c6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1c5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1c4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1c3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1c2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1b4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1b2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1ad);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1a6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1a3
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1a0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_19e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_19d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_194
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_193);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_18c);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_185);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_17e);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)&DAT_014675a8,L"ITEM",&aStack_17c);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_178)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_171);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_8f);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_8c);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_86);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_85);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_84);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_83
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_82);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_81);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_80);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gPROPERTY_NODE_TYPE_NAMES,L"Point of Interest",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 8),L"Player Start",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x10),L"Editor Player Start",
             &aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x18),L"No Spawn Region",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x20),L"Entrance",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x28),L"Exit",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x30),L"Jump Down Area",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x38),L"Town Portal",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x40),L"Path Node Occupation Circle",
             &aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x48),L"Path Node Occupation Box",
             &aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x50),L"Camera Position",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x58),L"Camera Target",&aStack_74);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x60),L"Quest Item",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x68),L"Quest Boss",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x70),L"Waypoint",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x78),L"Waypoint Start",&aStack_70);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_6d);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_68);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&aStack_64
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_63);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",&aStack_5c);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)&DAT_01467f48,L"Two",&aStack_5a);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_57);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gCOUNTER_TYPE_NAMES,L"Activate only once",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 8),L"Activate and reset",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x10),L"Activate on each add",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x18),L"Activate on each add and reset",
             &aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x20),L"Activate on each subtract",
             &aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x28),L"Activate on each subtract and reset"
             ,&aStack_51);
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_50);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_4f);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_4e);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_4d);
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gCAMERASHAKE_ORIENTATION,L"ABSOLUTE",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)&DAT_01467fe8,L"RELATIVE",&aStack_4b);
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_4a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_49);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_48);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_47);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_46);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_45);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_44);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_43);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_42);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_41);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_40);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_3f);
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_3e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_3d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_3c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_3b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_3a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_39);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_38);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_37);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_36);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_35);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_34);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_33);
  __cxa_atexit(__tcf_45,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_32);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_31);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_30);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_2f);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_2e);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_2d);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_2c);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_2b);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_2a);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_29);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_28);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_27);
  __cxa_atexit(__tcf_46,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_24);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_22);
  __cxa_atexit(__tcf_47,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_1d);
  __cxa_atexit(__tcf_48,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_1c);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_16);
  __cxa_atexit(__tcf_49,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_11);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_10);
  __cxa_atexit(__tcf_50,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_f);
  std::wstring::wstring((wstring_conflict *)&DAT_01468218,L"ABOVE",&aStack_e);
  __cxa_atexit(__tcf_51,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_9);
  __cxa_atexit(__tcf_52,0,&__dso_handle);
  return;
}

/* export-summary functions=6 failures=0 */
