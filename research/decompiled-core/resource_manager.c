/* Targeted Ghidra class export.
   namespace=CResourceManager
   Treat pseudocode as navigation evidence. */


/* address=00d6f4e0
   symbol=CResourceManager::getEditorIsRunning */

/* CResourceManager::getEditorIsRunning() */

uint CResourceManager::getEditorIsRunning(void)

{
  return *(int *)(gEditor + 100) >> 1 & 1U ^ 1;
}

/* address=00d6f500
   symbol=CResourceManager::getDungeonManager */

/* CResourceManager::getDungeonManager() */

undefined8 CResourceManager::getDungeonManager(void)

{
  return g_pDungeonManager;
}

/* address=00d6f510
   symbol=CResourceManager::getMissilePreloader */

/* CResourceManager::getMissilePreloader() */

undefined8 CResourceManager::getMissilePreloader(void)

{
  return g_MissilePreloader;
}

/* address=00d6f520
   symbol=CResourceManager::createMissile */

/* CResourceManager::createMissile(std::wstring const&) */

void __thiscall CResourceManager::createMissile(CResourceManager *this,wstring_conflict *param_1)

{
  CMissilePreloader *this_00;

  this_00 = (CMissilePreloader *)CMissilePreloader::getSinglelton();
  CMissilePreloader::createNewMissileRef(this_00,this,param_1);
  return;
}

/* address=00d6f560
   symbol=CResourceManager::createParticle */

/* CResourceManager::createParticle(wchar_t const*) */

undefined8 __thiscall CResourceManager::createParticle(CResourceManager *this,wchar_t *param_1)

{
  long lVar1;
  undefined8 uVar2;

  lVar1 = CMasterResourceManager::getSingleton();
  if (*(long *)(lVar1 + 0xf8) != 0) {
    lVar1 = CMasterResourceManager::getSingleton();
    uVar2 = CParticlePreloader::GetParticle(*(CParticlePreloader **)(lVar1 + 0xf8),this,param_1);
    return uVar2;
  }
  return 0;
}

/* address=00d6f5d0
   symbol=CResourceManager::getUnitDataByGuid */

/* CResourceManager::getUnitDataByGuid(long long) */

void __thiscall CResourceManager::getUnitDataByGuid(CResourceManager *this,longlong param_1)

{
  CUnitResourceList *this_00;

  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  CUnitResourceList::getDataGroupByGuid(this_00,param_1);
  return;
}

/* address=00d6f5f0
   symbol=CResourceManager::getMasterResourceList */

/* CResourceManager::getMasterResourceList() */

undefined8 CResourceManager::getMasterResourceList(void)

{
  return m_pGlobalUnitResourceList;
}

/* address=00d6f600
   symbol=CResourceManager::getGroupByName */

/* CResourceManager::getGroupByName(std::wstring const&) */

void __thiscall CResourceManager::getGroupByName(CResourceManager *this,wstring_conflict *param_1)

{
  long lVar1;
  CUnitResourceList *this_00;

  lVar1 = CUnitResourceList::getSingleton();
  if (lVar1 != 0) {
    this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
    CUnitResourceList::getGroupByName(this_00,param_1);
    return;
  }
  return;
}

/* address=00d6f630
   symbol=CResourceManager::getUnitGuidByDataGroup */

/* CResourceManager::getUnitGuidByDataGroup(CDataGroup*, std::wstring const&) */

undefined8 __thiscall
CResourceManager::getUnitGuidByDataGroup
          (CResourceManager *this,CDataGroup *param_1,wstring_conflict *param_2)

{
  wstring_conflict *pwVar1;
  undefined8 uVar2;

  if (param_1 != (CDataGroup *)0x0) {
    pwVar1 = (wstring_conflict *)
             CDataGroup::GetDataValue(param_1,param_2,(wstring_conflict *)&::EMPTY_WSTRING);
    if (*(long *)(*(long *)pwVar1 + -0x18) != 0) {
      uVar2 = STRINGS::GetInt64(pwVar1);
      return uVar2;
    }
  }
  return 0xffffffffffffffff;
}

/* address=00d6f670
   symbol=CResourceManager::ISA */

/* CResourceManager::ISA(UNITTYPES::EUNITTYPES, UNITTYPES::EUNITTYPES) */

undefined8 __thiscall CResourceManager::ISA(CResourceManager *this,uint param_2,uint param_3)

{
  undefined8 uVar1;

  if (*(CHierarchy **)(this + 0x20) != (CHierarchy *)0x0) {
    uVar1 = CHierarchy::ISA(*(CHierarchy **)(this + 0x20),param_2,param_3);
    return uVar1;
  }
  return 0;
}

/* address=00d6f690
   symbol=CResourceManager::getUnitTypeByName */

/* CResourceManager::getUnitTypeByName(std::wstring const&) */

undefined8 __thiscall
CResourceManager::getUnitTypeByName(CResourceManager *this,wstring_conflict *param_1)

{
  undefined8 uVar1;

  if (*(CHierarchy **)(this + 0x20) != (CHierarchy *)0x0) {
    uVar1 = CHierarchy::getTypeIDByName(*(CHierarchy **)(this + 0x20),param_1);
    if ((int)uVar1 != -1) {
      return uVar1;
    }
  }
  return 0x16;
}

/* address=00d6f6c0
   symbol=CResourceManager::ISA */

/* CResourceManager::ISA(std::wstring const&, std::wstring const&) */

undefined8 __thiscall
CResourceManager::ISA(CResourceManager *this,wstring_conflict *param_1,wstring_conflict *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;

  if (*(long *)(this + 0x20) != 0) {
    uVar1 = getUnitTypeByName(this,param_2);
    uVar2 = getUnitTypeByName(this,param_1);
    uVar3 = CHierarchy::ISA(*(CHierarchy **)(this + 0x20),uVar2,uVar1);
    return uVar3;
  }
  return 0;
}

/* address=00d6f740
   symbol=CResourceManager::getGameUI */

/* CResourceManager::getGameUI() */

undefined8 CResourceManager::getGameUI(void)

{
  return g_pGameUI;
}

/* address=00d6f750
   symbol=CResourceManager::getTextureManager */

/* CResourceManager::getTextureManager() */

void CResourceManager::getTextureManager(void)

{
  (*(code *)PTR_getSingletonPtr_014200c0)();
  return;
}

/* address=00d6f760
   symbol=CResourceManager::getCameraControl */

/* CResourceManager::getCameraControl() */

undefined8 CResourceManager::getCameraControl(void)

{
  return g_pCameraControl;
}

/* address=00d6f770
   symbol=CResourceManager::getSpawnClassByName */

/* CResourceManager::getSpawnClassByName(std::wstring const&) */

void __thiscall
CResourceManager::getSpawnClassByName(CResourceManager *this,wstring_conflict *param_1)

{
  long lVar1;

  lVar1 = CMasterResourceManager::getSingleton();
  CSpawnClassParser::getSpawnClass(*(CSpawnClassParser **)(lVar1 + 0x78),param_1);
  return;
}

/* address=00d6f790
   symbol=CResourceManager::createAffixesForUnit */

/* CResourceManager::createAffixesForUnit(CBaseUnit*, unsigned int, unsigned int) */

void __thiscall
CResourceManager::createAffixesForUnit
          (CResourceManager *this,CBaseUnit *param_1,uint param_2,uint param_3)

{
  long lVar1;
  undefined8 *puVar2;
  uint uVar3;
  undefined8 *local_48;
  uint local_40;
  uint local_3c;
  uint local_38;

  if ((param_3 != 0) && (param_1 != (CBaseUnit *)0x0)) {
    local_48 = (undefined8 *)0x0;
    local_40 = 0;
    local_3c = 0;
    uVar3 = *(uint *)(param_1 + 0x1ac);
    local_38 = param_3;
                    /* try { // try from 00d6f7e0 to 00d6f824 has its CatchHandler @ 00d6f85d */
    lVar1 = CMasterResourceManager::getSingleton();
    CEffectGroupManager::rollAndCreateRandomAffixes
              (*(CEffectGroupManager **)(lVar1 + 0x58),uVar3,param_2,param_3,(TArrayList *)&local_48
              );
    if (local_40 != 0) {
      uVar3 = 0;
      do {
        puVar2 = local_48;
        if (uVar3 < local_3c) {
          puVar2 = local_48 + uVar3;
        }
        CBaseUnit::addAffix(param_1,(CAffix *)*puVar2,param_2,param_1,DAT_00fa8760);
        uVar3 = uVar3 + 1;
      } while (uVar3 < local_40);
    }
    if (local_48 != (undefined8 *)0x0) {
      operator_delete__(local_48);
      return;
    }
  }
  return;
}

/* address=00d6f880
   symbol=CResourceManager::getGraphDamage */

/* CResourceManager::getGraphDamage() */

undefined8 __thiscall CResourceManager::getGraphDamage(CResourceManager *this)

{
  int iVar1;
  CGraphManager *pCVar2;
  undefined8 uVar3;
  wstring_conflict awStack_58 [16];
  wstring_conflict local_48 [16];
  wstring_conflict local_38 [16];
  wstring_conflict local_28 [12];
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19 [9];

  if ((*(int *)(this + 0x30) != 0) && (**(long **)(this + 0x28) != 0)) {
    iVar1 = *(int *)(**(long **)(this + 0x28) + 0x38ec);
    if (iVar1 == 1) {
                    /* try { // try from 00d6f962 to 00d6f966 has its CatchHandler @ 00d6f9f2 */
      std::wstring::wstring(local_38,L"DAMAGE_MONSTER",&local_1a);
                    /* try { // try from 00d6f967 to 00d6f976 has its CatchHandler @ 00d6f9e9 */
      pCVar2 = (CGraphManager *)CGraphManager::getSingleton();
      uVar3 = CGraphManager::getGraph(pCVar2,local_38);
                    /* try { // try from 00d6f97d to 00d6f981 has its CatchHandler @ 00d6f9f2 */
      std::wstring::~wstring(local_38);
      return uVar3;
    }
    if (iVar1 < 2) {
      if (iVar1 == 0) {
                    /* try { // try from 00d6f9aa to 00d6f9ae has its CatchHandler @ 00d6f9e7 */
        std::wstring::wstring(local_28,L"DAMAGE_MONSTER_EASY",local_19);
                    /* try { // try from 00d6f9af to 00d6f9be has its CatchHandler @ 00d6f9da */
        pCVar2 = (CGraphManager *)CGraphManager::getSingleton();
        uVar3 = CGraphManager::getGraph(pCVar2,local_28);
                    /* try { // try from 00d6f9c5 to 00d6f9c9 has its CatchHandler @ 00d6f9e7 */
        std::wstring::~wstring(local_28);
        return uVar3;
      }
    }
    else {
      if (iVar1 == 2) {
                    /* try { // try from 00d6f8f2 to 00d6f8f6 has its CatchHandler @ 00d6f9cf */
        std::wstring::wstring(local_48,L"DAMAGE_MONSTER_HARD",&local_1b);
                    /* try { // try from 00d6f8f7 to 00d6f906 has its CatchHandler @ 00d6fa04 */
        pCVar2 = (CGraphManager *)CGraphManager::getSingleton();
        uVar3 = CGraphManager::getGraph(pCVar2,local_48);
                    /* try { // try from 00d6f90d to 00d6f911 has its CatchHandler @ 00d6f9cf */
        std::wstring::~wstring(local_48);
        return uVar3;
      }
      if (iVar1 == 3) {
                    /* try { // try from 00d6f925 to 00d6f929 has its CatchHandler @ 00d6fa02 */
        std::wstring::wstring(awStack_58,L"DAMAGE_MONSTER_VERYHARD",&local_1c);
                    /* try { // try from 00d6f92a to 00d6f939 has its CatchHandler @ 00d6f9f4 */
        pCVar2 = (CGraphManager *)CGraphManager::getSingleton();
        uVar3 = CGraphManager::getGraph(pCVar2,awStack_58);
                    /* try { // try from 00d6f940 to 00d6f944 has its CatchHandler @ 00d6fa02 */
        std::wstring::~wstring(awStack_58);
        return uVar3;
      }
    }
  }
  return 0;
}

/* address=00d6fa10
   symbol=CResourceManager::getGraph */

/* CResourceManager::getGraph(std::wstring const&) */

undefined8 __thiscall CResourceManager::getGraph(CResourceManager *this,wstring_conflict *param_1)

{
  long lVar1;
  undefined8 uVar2;

  lVar1 = CMasterResourceManager::getSingleton();
  if (lVar1 != 0) {
    lVar1 = CMasterResourceManager::getSingleton();
    if (*(long *)(lVar1 + 0x48) != 0) {
      lVar1 = CMasterResourceManager::getSingleton();
      uVar2 = CGraphManager::getGraph(*(CGraphManager **)(lVar1 + 0x48),param_1);
      return uVar2;
    }
  }
  return 0;
}

/* address=00d6fa50
   symbol=CResourceManager::getCurrentLevelSeed */

/* CResourceManager::getCurrentLevelSeed() */

undefined8 __thiscall CResourceManager::getCurrentLevelSeed(CResourceManager *this)

{
  undefined8 uVar1;

  if (*(CLevel **)(this + 0x18) != (CLevel *)0x0) {
    uVar1 = CLevel::getCurrentLevelSeed(*(CLevel **)(this + 0x18));
    return uVar1;
  }
  return 0;
}

/* address=00d6fa70
   symbol=CResourceManager::~CResourceManager */

/* CResourceManager::~CResourceManager() */

void __thiscall CResourceManager::~CResourceManager(CResourceManager *this)

{
  *(undefined ***)this = &PTR__CResourceManager_00ff8cf0;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  if (*(void **)(this + 0x28) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x28));
    *(undefined8 *)(this + 0x28) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d6fac0
   symbol=CResourceManager::~CResourceManager */

/* CResourceManager::~CResourceManager() */

void __thiscall CResourceManager::~CResourceManager(CResourceManager *this)

{
  ~CResourceManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00d76930
   symbol=CResourceManager::_GLOBAL__I_CResourceManager */

/* CResourceManager::CResourceManager(Ogre::SceneManager*) */

void CResourceManager::_GLOBAL__I_CResourceManager(void)

{
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
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_290);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_28f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_28e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_28d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_28c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_28b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_28a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_289);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_288);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_287);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_286);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_285);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_282)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_281);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_280)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_27f);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_27e);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_27d);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_27b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_27a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_278);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_277);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_276);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_275);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_272)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_26f);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_26c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_26a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_268);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_265);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_263);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_260)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_25e);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_25a);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1f9);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1ed)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1eb)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1ea)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1e9)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1e8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1e7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1e6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1dc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1db);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1da);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1d9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1d8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1d6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1ce);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1ca
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1c8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1c7
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1c6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1c4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1c2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1c1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1b8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1b7);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1b0);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1a9);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1a2);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)&DAT_0150a688,L"ITEM",&aStack_1a0);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_19c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_195);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_b3);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_b1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_af)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_a4)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_9f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_91);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_8d);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_87);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_84);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_7e);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_7d);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_7c);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_7b
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_7a);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_79);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_78);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_77);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_76);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_75);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_74);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_73);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_72);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_71);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_70);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_6f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_6e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_6d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_6c);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_6b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_6a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_69);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_68);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_67);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_66);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_65);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_64);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_63);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_62);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_61);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_60);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_5f);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_5e);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_5d);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_5c);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_5b);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_5a);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_59);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_58);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_57);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_56);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_55);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_54);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_4f);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_4d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_4b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_4a);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_49);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_42);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_3c);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)&DAT_0150b258,L"ABOVE",&aStack_3a);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_35);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_2f);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_29);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_20);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_1c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_1b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_12);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_11);
  std::wstring::wstring((wstring_conflict *)&DAT_0150b3d8,L"Two",&aStack_10);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_e);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_d);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_c);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_b);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_a);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_9);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  return;
}

/* address=00d76940
   symbol=CResourceManager::createMonster */

/* CResourceManager::createMonster(long long, int, bool) */

CMonster * __thiscall
CResourceManager::createMonster(CResourceManager *this,longlong param_1,int param_2,bool param_3)

{
  CUnitResourceList *this_00;
  long lVar1;
  CMonster *this_01;

  this_01 = (CMonster *)0x0;
  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  lVar1 = CUnitResourceList::getDataGroupByGuid(this_00,param_1);
  if (lVar1 != 0) {
    if (param_2 < 1) {
      param_2 = 1;
      if (*(long *)(this + 0x18) != 0) {
        param_2 = *(int *)(*(long *)(this + 0x18) + 0x1a8);
      }
    }
    this_01 = (CMonster *)Ogre::NedAllocImpl::allocBytes(0x7f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d769ad to 00d769b1 has its CatchHandler @ 00d76a08 */
    CMonster::CMonster(this_01,this,param_2);
    (**(code **)(*(long *)this_01 + 0x1f0))(this_01,lVar1,param_3);
  }
  return this_01;
}

/* address=00d76a20
   symbol=CResourceManager::getNewAffixByName */

/* CResourceManager::getNewAffixByName(std::wstring const&, unsigned int) */

CAffix * __thiscall
CResourceManager::getNewAffixByName(CResourceManager *this,wstring_conflict *param_1,uint param_2)

{
  long lVar1;
  CAffix *pCVar2;
  CAffix *this_00;

  lVar1 = CMasterResourceManager::getSingleton();
  pCVar2 = (CAffix *)CEffectGroupManager::getAffix(*(CEffectGroupManager **)(lVar1 + 0x58),param_1);
  if (pCVar2 == (CAffix *)0x0) {
    this_00 = (CAffix *)0x0;
  }
  else {
    this_00 = (CAffix *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d76a76 to 00d76a7a has its CatchHandler @ 00d76aa4 */
    CAffix::CAffix(this_00,pCVar2,param_2);
  }
  return this_00;
}

/* address=00d77bf0
   symbol=CResourceManager::getDungeonByName */

/* WARNING: Removing unreachable block (ram,0x00d77c70) */
/* CResourceManager::getDungeonByName(std::wstring const&) */

undefined8 __thiscall
CResourceManager::getDungeonByName(CResourceManager *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  CDungeonManager *pCVar3;
  undefined8 uVar4;
  long local_18 [2];

  std::wstring::wstring((wstring_conflict *)local_18,param_1);
                    /* try { // try from 00d77c02 to 00d77c11 has its CatchHandler @ 00d77c56 */
  pCVar3 = (CDungeonManager *)CDungeonManager::getSingleton();
  uVar4 = CDungeonManager::getDungeonByName(pCVar3,(wstring_conflict *)local_18);
  if ((allocator *)(local_18[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_18[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_18[0] + -0x18));
    }
  }
  return uVar4;
}

/* address=00d77c80
   symbol=CResourceManager::createMonster */

/* WARNING: Removing unreachable block (ram,0x00d77e01) */
/* WARNING: Removing unreachable block (ram,0x00d77e2b) */
/* CResourceManager::createMonster(wchar_t const*, int, bool) */

CMonster * __thiscall
CResourceManager::createMonster(CResourceManager *this,wchar_t *param_1,int param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  CUnitResourceList *this_00;
  long lVar3;
  CMonster *this_01;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

                    /* try { // try from 00d77cb3 to 00d77cb7 has its CatchHandler @ 00d77e0c */
  std::wstring::wstring((wstring_conflict *)local_58,param_1,&local_3a);
                    /* try { // try from 00d77cca to 00d77cce has its CatchHandler @ 00d77dee */
  std::wstring::wstring((wstring_conflict *)&local_48,L"MONSTERS",local_39);
                    /* try { // try from 00d77ccf to 00d77ce1 has its CatchHandler @ 00d77e11 */
  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  lVar3 = CUnitResourceList::getDataGroupByObjectName
                    (this_00,(wstring_conflict *)&local_48,(wstring_conflict *)local_58);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  this_01 = (CMonster *)0x0;
  if (lVar3 != 0) {
    if (param_2 < 1) {
      param_2 = 1;
      if (*(long *)(this + 0x18) != 0) {
        param_2 = *(int *)(*(long *)(this + 0x18) + 0x1a8);
      }
    }
    this_01 = (CMonster *)Ogre::NedAllocImpl::allocBytes(0x7f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d77d3d to 00d77d41 has its CatchHandler @ 00d77e1e */
    CMonster::CMonster(this_01,this,param_2);
    (**(code **)(*(long *)this_01 + 0x1f0))(this_01,lVar3,param_3);
  }
  return this_01;
}

/* address=00d77e40
   symbol=CResourceManager::createGenericModel */

/* WARNING: Removing unreachable block (ram,0x00d780d0) */
/* WARNING: Removing unreachable block (ram,0x00d780ec) */
/* WARNING: Removing unreachable block (ram,0x00d780de) */
/* WARNING: Removing unreachable block (ram,0x00d78096) */
/* CResourceManager::createGenericModel(Ogre::SceneManager*, wchar_t const*, wchar_t const*, bool,
   bool, bool) */

CGenericModel * __thiscall
CResourceManager::createGenericModel
          (CResourceManager *this,SceneManager *param_1,wchar_t *param_2,wchar_t *param_3,
          bool param_4,bool param_5,bool param_6)

{
  int *piVar1;
  int iVar2;
  CGenericModel *pCVar3;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  std::wstring::wstring((wstring_conflict *)&local_48,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d77ea8 to 00d77eac has its CatchHandler @ 00d780a6 */
  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d77eb8 to 00d77ebc has its CatchHandler @ 00d780a1 */
  pCVar3 = (CGenericModel *)Ogre::NedAllocImpl::allocBytes(0x250,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d77ed5 to 00d77ed9 has its CatchHandler @ 00d78073 */
  CGenericModel::CGenericModel
            (pCVar3,this,param_1,(wstring_conflict *)&local_48,(wstring_conflict *)local_58,param_4)
  ;
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if (param_3 == (wchar_t *)0x0) {
                    /* try { // try from 00d77fbd to 00d77fc1 has its CatchHandler @ 00d780cb */
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else {
                    /* try { // try from 00d77f1c to 00d77f20 has its CatchHandler @ 00d780cb */
    std::wstring::wstring((wstring_conflict *)local_68,param_3,local_39);
  }
                    /* try { // try from 00d77f33 to 00d77f37 has its CatchHandler @ 00d780c6 */
  std::wstring::wstring((wstring_conflict *)local_78,param_2,&local_3a);
                    /* try { // try from 00d77f4f to 00d77f53 has its CatchHandler @ 00d780ab */
  CGenericModel::loadModel(pCVar3,(wstring_conflict *)local_78,local_68,param_5,param_6,0);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  return pCVar3;
}

/* address=00d78100
   symbol=CResourceManager::createPlayer */

/* WARNING: Removing unreachable block (ram,0x00d78277) */
/* WARNING: Removing unreachable block (ram,0x00d7824b) */
/* CResourceManager::createPlayer(wchar_t const*, bool) */

CPlayer * __thiscall
CResourceManager::createPlayer(CResourceManager *this,wchar_t *param_1,bool param_2)

{
  int *piVar1;
  int iVar2;
  CUnitResourceList *this_00;
  long lVar3;
  CPlayer *this_01;
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29;

                    /* try { // try from 00d7812b to 00d7812f has its CatchHandler @ 00d78272 */
  std::wstring::wstring((wstring_conflict *)local_48,param_1,&local_2a);
                    /* try { // try from 00d78142 to 00d78146 has its CatchHandler @ 00d78256 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"PLAYERS",&local_29);
                    /* try { // try from 00d78147 to 00d78159 has its CatchHandler @ 00d78263 */
  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  lVar3 = CUnitResourceList::getDataGroupByObjectName
                    (this_00,(wstring_conflict *)&local_38,(wstring_conflict *)local_48);
  if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
    }
  }
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  this_01 = (CPlayer *)0x0;
  if (lVar3 != 0) {
    this_01 = (CPlayer *)Ogre::NedAllocImpl::allocBytes(0xa70,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d781a9 to 00d781ad has its CatchHandler @ 00d78238 */
    CPlayer::CPlayer(this_01,this);
    (**(code **)(*(long *)this_01 + 0x1f0))(this_01,lVar3,param_2);
  }
  return this_01;
}

/* address=00d78290
   symbol=CResourceManager::createNewItem */

/* WARNING: Removing unreachable block (ram,0x00d78494) */
/* WARNING: Removing unreachable block (ram,0x00d78472) */
/* CResourceManager::createNewItem(CDataGroup*) */

CEquipment * __thiscall CResourceManager::createNewItem(CResourceManager *this,CDataGroup *param_1)

{
  int *piVar1;
  int iVar2;
  wstring_conflict *pwVar3;
  CEquipment *this_00;
  long local_38 [2];
  long local_28;
  allocator local_19;

                    /* try { // try from 00d782b0 to 00d782b4 has its CatchHandler @ 00d7848f */
  std::wstring::wstring((wstring_conflict *)local_38,L"CREATEAS",&local_19);
                    /* try { // try from 00d782c0 to 00d782d4 has its CatchHandler @ 00d78482 */
  pwVar3 = (wstring_conflict *)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_38,L"");
  STRINGS::StringUpper((STRINGS *)&local_28,pwVar3);
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
                    /* try { // try from 00d782f3 to 00d7830b has its CatchHandler @ 00d7847d */
  iVar2 = std::wstring::compare((wchar_t *)&local_28);
  if (iVar2 == 0) {
    this_00 = (CEquipment *)Ogre::NedAllocImpl::allocBytes(0x438,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d78315 to 00d78319 has its CatchHandler @ 00d7844b */
    CEquipment::CEquipment(this_00,this);
  }
  else {
                    /* try { // try from 00d78348 to 00d78360 has its CatchHandler @ 00d7847d */
    iVar2 = std::wstring::compare((wchar_t *)&local_28);
    if (iVar2 == 0) {
      this_00 = (CEquipment *)Ogre::NedAllocImpl::allocBytes(0x248,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d7836a to 00d7836e has its CatchHandler @ 00d78466 */
      CBreakable::CBreakable((CBreakable *)this_00,this);
    }
    else {
                    /* try { // try from 00d78380 to 00d78398 has its CatchHandler @ 00d7847d */
      iVar2 = std::wstring::compare((wchar_t *)&local_28);
      if (iVar2 == 0) {
        this_00 = (CEquipment *)Ogre::NedAllocImpl::allocBytes(0x300,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d783a2 to 00d783a6 has its CatchHandler @ 00d7846a */
        CTriggerUnit::CTriggerUnit((CTriggerUnit *)this_00,this);
      }
      else {
                    /* try { // try from 00d783b8 to 00d783d6 has its CatchHandler @ 00d7847d */
        iVar2 = std::wstring::compare((wchar_t *)&local_28);
        this_00 = (CEquipment *)0x0;
        if (iVar2 == 0) {
          this_00 = (CEquipment *)Ogre::NedAllocImpl::allocBytes(0x288,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d783e5 to 00d783e9 has its CatchHandler @ 00d78468 */
          CItemGold::CItemGold((CItemGold *)this_00,this,1);
        }
      }
    }
  }
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
  return this_00;
}

/* address=00d784a0
   symbol=CResourceManager::createItem */

/* CResourceManager::createItem(long long, bool, bool, bool) */

long * __thiscall
CResourceManager::createItem
          (CResourceManager *this,longlong param_1,bool param_2,bool param_3,bool param_4)

{
  CUnitResourceList *this_00;
  CDataGroup *pCVar1;
  long *plVar2;
  CEquipment *this_01;

  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  plVar2 = (long *)0x0;
  pCVar1 = (CDataGroup *)CUnitResourceList::getDataGroupByGuid(this_00,param_1);
  if (pCVar1 != (CDataGroup *)0x0) {
    plVar2 = (long *)createNewItem(this,pCVar1);
    if (plVar2 != (long *)0x0) {
      *(bool *)((long)plVar2 + 0x20a) = param_3;
      (**(code **)(*plVar2 + 0x1f0))(plVar2,pCVar1,param_2);
      this_01 = (CEquipment *)__dynamic_cast(plVar2,&CItem::typeinfo,&CEquipment::typeinfo,0);
      if ((param_4) && (this_01 != (CEquipment *)0x0)) {
        CEquipment::enchant(this_01,true);
      }
    }
  }
  return plVar2;
}

/* address=00d78570
   symbol=CResourceManager::createItem */

/* WARNING: Removing unreachable block (ram,0x00d786c9) */
/* WARNING: Removing unreachable block (ram,0x00d786d9) */
/* CResourceManager::createItem(wchar_t const*, bool, bool) */

long * __thiscall
CResourceManager::createItem(CResourceManager *this,wchar_t *param_1,bool param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  CUnitResourceList *this_00;
  CDataGroup *pCVar3;
  long *plVar4;
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29;

                    /* try { // try from 00d785a3 to 00d785a7 has its CatchHandler @ 00d786c4 */
  std::wstring::wstring((wstring_conflict *)local_48,param_1,&local_2a);
                    /* try { // try from 00d785ba to 00d785be has its CatchHandler @ 00d786d4 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"ITEMS",&local_29);
                    /* try { // try from 00d785bf to 00d785d1 has its CatchHandler @ 00d786a9 */
  this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
  pCVar3 = (CDataGroup *)
           CUnitResourceList::getDataGroupByObjectName
                     (this_00,(wstring_conflict *)&local_38,(wstring_conflict *)local_48);
  if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
    }
  }
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  plVar4 = (long *)0x0;
  if ((pCVar3 != (CDataGroup *)0x0) &&
     (plVar4 = (long *)createNewItem(this,pCVar3), plVar4 != (long *)0x0)) {
    *(bool *)((long)plVar4 + 0x20a) = param_3;
    (**(code **)(*plVar4 + 0x1f0))(plVar4,pCVar3,param_2);
  }
  return plVar4;
}

/* address=00d786f0
   symbol=CResourceManager::createEquipment */

/* CResourceManager::createEquipment(wchar_t const*, bool, bool) */

long __thiscall
CResourceManager::createEquipment(CResourceManager *this,wchar_t *param_1,bool param_2,bool param_3)

{
  long *plVar1;
  long lVar2;

  plVar1 = (long *)createItem(this,param_1,param_2,param_3);
  lVar2 = 0;
  if (plVar1 != (long *)0x0) {
    lVar2 = __dynamic_cast(plVar1,&CItem::typeinfo,&CEquipment::typeinfo,0);
    if (lVar2 == 0) {
      (**(code **)(*plVar1 + 8))(plVar1);
      return 0;
    }
  }
  return lVar2;
}

/* address=00d78750
   symbol=CResourceManager::getResourceGroupFromDataGroup */

/* WARNING: Removing unreachable block (ram,0x00d7880e) */
/* CResourceManager::getResourceGroupFromDataGroup(CDataGroup*) */

ulong __thiscall
CResourceManager::getResourceGroupFromDataGroup(CResourceManager *this,CDataGroup *param_1)

{
  int *piVar1;
  int iVar2;
  ulong uVar3;
  long local_28;
  allocator local_19 [9];

  if (param_1 != (CDataGroup *)0x0) {
                    /* try { // try from 00d78778 to 00d7877c has its CatchHandler @ 00d78809 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"RESOURCEGROUP",local_19);
                    /* try { // try from 00d78788 to 00d7878c has its CatchHandler @ 00d787f6 */
    uVar3 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)&local_28,0xffffffff);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
        uVar3 = uVar3 & 0xffffffff;
      }
    }
    if ((int)uVar3 != -1) {
      return uVar3;
    }
  }
  return 4;
}

/* address=00d78820
   symbol=CResourceManager::CResourceManager */

/* WARNING: Removing unreachable block (ram,0x00d78a70) */
/* WARNING: Removing unreachable block (ram,0x00d78a3d) */
/* WARNING: Removing unreachable block (ram,0x00d78a62) */
/* CResourceManager::CResourceManager(Ogre::SceneManager*) */

void __thiscall CResourceManager::CResourceManager(CResourceManager *this,SceneManager *param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int iVar4;
  long lVar5;
  CResourceManager CVar6;
  wchar_t *local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_29 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CResourceManager_00ff8cf0;
  *(SceneManager **)(this + 0x10) = param_1;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 10;
  this[0x40] = (CResourceManager)0x0;
  this[0x41] = (CResourceManager)0x1;
  this[0x42] = (CResourceManager)0x0;
  this[0x43] = (CResourceManager)0x0;
                    /* try { // try from 00d78883 to 00d788d0 has its CatchHandler @ 00d78a14 */
  lVar5 = CMasterResourceManager::getSingleton();
  if (lVar5 != 0) {
    lVar5 = CMasterResourceManager::getSingleton();
    *(undefined8 *)(this + 0x20) = *(undefined8 *)(lVar5 + 0x80);
    if (*(long *)(this + 0x10) == 0) {
                    /* try { // try from 00d78980 to 00d78984 has its CatchHandler @ 00d78a14 */
      lVar5 = CMasterResourceManager::getSingleton();
      *(undefined8 *)(this + 0x10) = *(undefined8 *)(lVar5 + 200);
    }
    lVar5 = CMasterResourceManager::getSingleton();
    if (*(long *)(lVar5 + 0x90) != 0) {
      std::wstring::wstring((wstring_conflict *)&local_38,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d788e3 to 00d788e7 has its CatchHandler @ 00d78a5d */
      std::wstring::wstring((wstring_conflict *)local_48,L"COMPRESS",local_29);
                    /* try { // try from 00d788e8 to 00d78908 has its CatchHandler @ 00d78a48 */
      lVar5 = CMasterResourceManager::getSingleton();
      CCmdLineParser::GetStringParam
                (local_58,*(undefined8 *)(*(long *)(lVar5 + 0x90) + 0x140),
                 (wstring_conflict *)local_48,(wstring_conflict *)&local_38);
      CVar6 = (CResourceManager)0x1;
      if (*(size_t *)(local_58[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar4 = wmemcmp(local_58[0],::EMPTY_WSTRING,*(size_t *)(local_58[0] + -6));
        CVar6 = (CResourceManager)(iVar4 != 0);
      }
      this[0x43] = CVar6;
      if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar2 = local_58[0] + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
        }
      }
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
      if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_38 + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
        }
      }
    }
  }
  return;
}

/* address=00d78a80
   symbol=CResourceManager::createUnit */

/* WARNING: Removing unreachable block (ram,0x00d78c36) */
/* CResourceManager::createUnit(long long, int, bool, bool) */

long * __thiscall
CResourceManager::createUnit
          (CResourceManager *this,longlong param_1,int param_2,bool param_3,bool param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  CUnitResourceList *this_00;
  CDataGroup *this_01;
  long *plVar4;
  long local_48;
  allocator local_39 [9];

  if (param_1 != -1) {
    if (param_2 < 1) {
      param_2 = 1;
      if (*(long *)(this + 0x18) != 0) {
        param_2 = *(int *)(*(long *)(this + 0x18) + 0x1a8);
      }
    }
    this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
    this_01 = (CDataGroup *)CUnitResourceList::getDataGroupByGuid(this_00,param_1);
    if (this_01 != (CDataGroup *)0x0) {
                    /* try { // try from 00d78b0f to 00d78b13 has its CatchHandler @ 00d78c31 */
      std::wstring::wstring((wstring_conflict *)&local_48,L"RESOURCEGROUP",local_39);
                    /* try { // try from 00d78b21 to 00d78b25 has its CatchHandler @ 00d78c1c */
      iVar3 = CDataGroup::GetDataValue(this_01,(wstring_conflict *)&local_48,0xffffffff);
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
      if (iVar3 != -1) {
        if (iVar3 == 1) {
          plVar4 = (long *)createMonster(this,param_1,param_2,param_3);
          return plVar4;
        }
        if (iVar3 != 2) {
          if (iVar3 == 0) {
            plVar4 = (long *)createItem(this,param_1,param_3,true,param_4);
            return plVar4;
          }
          plVar4 = (long *)createItem(this,param_1,param_3,true,false);
          if (plVar4 == (long *)0x0) {
            return (long *)0x0;
          }
          (**(code **)(*plVar4 + 0x278))(plVar4,param_2);
          return plVar4;
        }
      }
    }
  }
  return (long *)0x0;
}

/* address=00d78c50
   symbol=CResourceManager::createUnit */

/* WARNING: Removing unreachable block (ram,0x00d78d3c) */
/* CResourceManager::createUnit(CDataGroup*, int, bool, bool) */

undefined8 __thiscall
CResourceManager::createUnit
          (CResourceManager *this,CDataGroup *param_1,int param_2,bool param_3,bool param_4)

{
  int *piVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  long local_48;
  allocator local_39 [9];

  uVar4 = 0;
  if (param_1 != (CDataGroup *)0x0) {
                    /* try { // try from 00d78c9a to 00d78c9e has its CatchHandler @ 00d78d37 */
    std::wstring::wstring((wstring_conflict *)&local_48,L"UNIT_GUID",local_39);
                    /* try { // try from 00d78ca8 to 00d78cac has its CatchHandler @ 00d78d24 */
    lVar3 = getUnitGuidByDataGroup(this,param_1,(wstring_conflict *)&local_48);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    uVar4 = createUnit(this,lVar3,param_2,param_3,param_4);
  }
  return uVar4;
}

/* address=00d78d50
   symbol=CResourceManager::createUnit */

/* WARNING: Removing unreachable block (ram,0x00d78eb4) */
/* WARNING: Removing unreachable block (ram,0x00d78ecc) */
/* CResourceManager::createUnit(wchar_t const*, wchar_t const*, int, bool) */

undefined8 __thiscall
CResourceManager::createUnit
          (CResourceManager *this,wchar_t *param_1,wchar_t *param_2,int param_3,bool param_4)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  CUnitResourceList *this_00;
  CDataGroup *pCVar4;
  undefined8 uVar5;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (((param_2 != (wchar_t *)0x0) && (param_1 != (wchar_t *)0x0)) &&
     (lVar3 = CUnitResourceList::getSingleton(), lVar3 != 0)) {
                    /* try { // try from 00d78dcf to 00d78dd3 has its CatchHandler @ 00d78eaf */
    std::wstring::wstring((wstring_conflict *)local_58,param_2,&local_3a);
                    /* try { // try from 00d78de4 to 00d78de8 has its CatchHandler @ 00d78e9c */
    std::wstring::wstring((wstring_conflict *)&local_48,param_1,local_39);
                    /* try { // try from 00d78de9 to 00d78dfb has its CatchHandler @ 00d78ebf */
    this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
    pCVar4 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (this_00,(wstring_conflict *)&local_48,(wstring_conflict *)local_58);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if (pCVar4 != (CDataGroup *)0x0) {
      uVar5 = createUnit(this,pCVar4,param_3,param_4,false);
      return uVar5;
    }
  }
  return 0;
}

/* address=00d78ee0
   symbol=CResourceManager::createUnitsBySpawnClass */

/* CResourceManager::createUnitsBySpawnClass(CSpawnClass*, TArrayList<CBaseUnit*>&, unsigned int,
   CCharacter*, CCharacter*, int, int) */

void __thiscall
CResourceManager::createUnitsBySpawnClass
          (CResourceManager *this,CSpawnClass *param_1,TArrayList *param_2,uint param_3,
          CCharacter *param_4,CCharacter *param_5,int param_6,int param_7)

{
  undefined1 uVar1;
  undefined8 *puVar2;
  long lVar3;
  void *pvVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  uint local_9c;
  undefined1 *local_78;
  undefined4 local_70;
  uint local_6c;
  undefined4 local_68;
  undefined8 *local_58;
  uint local_50;
  uint local_4c;
  undefined4 local_48;

  if ((param_1 != (CSpawnClass *)0x0) && (param_3 != 0)) {
    local_58 = (undefined8 *)0x0;
    local_48 = 10;
    local_78 = (undefined1 *)0x0;
    local_70 = 0;
    local_6c = 0;
    local_68 = 10;
    local_9c = 0;
    do {
      local_50 = 0;
      local_4c = 0;
      if (local_58 != (undefined8 *)0x0) {
        operator_delete__(local_58);
      }
      local_58 = (undefined8 *)0x0;
                    /* try { // try from 00d78fe0 to 00d79100 has its CatchHandler @ 00d7915b */
      CSpawnClass::rollSpawnClass
                (param_1,(TArrayList *)&local_58,(TArrayList *)&local_78,param_4,param_5,param_6,
                 0xffffffff,0,-1,0,param_7);
      if (local_50 != 0) {
        uVar6 = 0;
        do {
          uVar7 = (uint)uVar6;
          if (uVar7 < local_6c) {
            uVar1 = local_78[uVar6];
          }
          else {
            uVar1 = *local_78;
          }
          puVar2 = local_58;
          if (uVar7 < local_4c) {
            puVar2 = local_58 + uVar6;
          }
          lVar3 = createUnit(this,(CDataGroup *)*puVar2,param_6,false,(bool)uVar1);
          if (lVar3 != 0) {
            uVar8 = *(uint *)(param_2 + 8);
            if (uVar8 < *(uint *)(param_2 + 0xc)) {
              pvVar4 = *(void **)param_2;
            }
            else if (*(long *)param_2 == 0) {
              *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
              pvVar4 = operator_new__((ulong)*(uint *)(param_2 + 0x10) << 3);
              *(void **)param_2 = pvVar4;
              uVar8 = *(uint *)(param_2 + 8);
            }
            else {
              uVar8 = *(uint *)(param_2 + 0xc) + *(int *)(param_2 + 0x10);
              pvVar4 = operator_new__((ulong)uVar8 << 3);
              if (*(int *)(param_2 + 0xc) != 0) {
                uVar6 = 0;
                do {
                  uVar5 = (int)uVar6 + 1;
                  *(undefined8 *)((long)pvVar4 + uVar6 * 8) =
                       *(undefined8 *)(*(long *)param_2 + uVar6 * 8);
                  uVar6 = (ulong)uVar5;
                } while (uVar5 < *(uint *)(param_2 + 0xc));
              }
              if (*(void **)param_2 != (void *)0x0) {
                operator_delete__(*(void **)param_2);
              }
              *(void **)param_2 = pvVar4;
              *(uint *)(param_2 + 0xc) = uVar8;
              uVar8 = *(uint *)(param_2 + 8);
            }
            *(long *)((long)pvVar4 + (ulong)uVar8 * 8) = lVar3;
            *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
          }
          uVar6 = (ulong)(uVar7 + 1);
        } while (uVar7 + 1 < local_50);
      }
      local_9c = local_9c + 1;
    } while (local_9c < param_3);
    if (local_78 != (undefined1 *)0x0) {
      operator_delete__(local_78);
      local_78 = (undefined1 *)0x0;
    }
    if (local_58 != (undefined8 *)0x0) {
      operator_delete__(local_58);
    }
  }
  return;
}

/* address=00d79190
   symbol=CResourceManager::createUnitsBySpawnClass */

/* CResourceManager::createUnitsBySpawnClass(std::wstring const&, TArrayList<CBaseUnit*>&, unsigned
   int, CCharacter*, CCharacter*, int, int) */

void __thiscall
CResourceManager::createUnitsBySpawnClass
          (CResourceManager *this,wstring_conflict *param_1,TArrayList *param_2,uint param_3,
          CCharacter *param_4,CCharacter *param_5,int param_6,int param_7)

{
  CSpawnClass *pCVar1;

  *(undefined4 *)(param_2 + 8) = 0;
  *(undefined4 *)(param_2 + 0xc) = 0;
  if (*(void **)param_2 != (void *)0x0) {
    operator_delete__(*(void **)param_2);
  }
  *(undefined8 *)param_2 = 0;
  if ((*(long *)(*(long *)param_1 + -0x18) != 0) && (param_3 != 0)) {
    pCVar1 = (CSpawnClass *)getSpawnClassByName(this,param_1);
    if (pCVar1 != (CSpawnClass *)0x0) {
      createUnitsBySpawnClass(this,pCVar1,param_2,param_3,param_4,param_5,param_6,param_7);
      return;
    }
  }
  return;
}

/* address=00d79290
   symbol=CResourceManager::createUnitsBySpawnClassAtPositionInLevel */

/* CResourceManager::createUnitsBySpawnClassAtPositionInLevel(CSpawnClass*, unsigned int,
   Ogre::Vector3 const&, CLevel*, CCharacter*, CCharacter*, int) */

void __thiscall
CResourceManager::createUnitsBySpawnClassAtPositionInLevel
          (CResourceManager *this,CSpawnClass *param_1,uint param_2,Vector3 *param_3,CLevel *param_4
          ,CCharacter *param_5,CCharacter *param_6,int param_7)

{
  char cVar1;
  long *plVar2;
  CPositionableObject *this_00;
  ulong uVar3;
  uint uVar4;
  float fVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  float fVar8;
  long *local_a8;
  uint local_a0;
  uint local_9c;
  undefined4 local_98;
  float local_88;
  float local_84;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  undefined8 local_48;
  float local_40;

  if ((param_1 != (CSpawnClass *)0x0) && (param_4 != (CLevel *)0x0)) {
    local_a8 = (long *)0x0;
    local_a0 = 0;
    local_9c = 0;
    local_98 = 10;
    if (param_7 == -1) {
      param_7 = *(int *)(param_4 + 0x1a8);
    }
                    /* try { // try from 00d7930d to 00d795ce has its CatchHandler @ 00d7969d */
    createUnitsBySpawnClass(this,param_1,(TArrayList *)&local_a8,param_2,param_5,param_6,param_7,0);
    if (local_a0 != 0) {
      uVar4 = 0;
      do {
        uVar3 = (ulong)uVar4;
        fVar5 = (float)-(uint)(DAT_00fa4810 < (float)uVar3 / DAT_00fa86d4);
        uVar6 = CLevel::randomOpenPosition
                          (param_4,param_3,
                           (float)(~(uint)fVar5 & (uint)DAT_00fa4810 |
                                  (uint)((float)uVar3 / DAT_00fa86d4) & (uint)fVar5),false);
        local_48 = CONCAT44(DAT_00fa4810 + *(float *)(param_3 + 4),uVar6);
        plVar2 = local_a8;
        if (uVar4 < local_9c) {
          plVar2 = local_a8 + uVar3;
        }
        local_40 = fVar5;
        cVar1 = CBaseUnit::ISA((CBaseUnit *)*plVar2,0x1f);
        if (cVar1 != '\0') {
          plVar2 = local_a8;
          if (uVar4 < local_9c) {
            plVar2 = local_a8 + uVar3;
          }
          cVar1 = CBaseUnit::ISA((CBaseUnit *)*plVar2,0x22);
          if (cVar1 == '\0') {
            local_48 = *(undefined8 *)param_3;
            local_40 = *(float *)(param_3 + 8);
          }
        }
        plVar2 = local_a8;
        if (uVar4 < local_9c) {
          plVar2 = local_a8 + uVar3;
        }
        CLevel::addUnit(param_4,(CBaseUnit *)*plVar2,(Vector3 *)&local_48);
        plVar2 = local_a8;
        if (uVar4 < local_9c) {
          plVar2 = local_a8 + uVar3;
        }
        if ((*plVar2 != 0) &&
           (this_00 = (CPositionableObject *)
                      __dynamic_cast(*plVar2,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
           this_00 != (CPositionableObject *)0x0)) {
          if (param_5 != (CCharacter *)0x0) {
            local_78 = CPositionableObject::getPosition(this_00,true);
            local_70 = fVar5;
            uVar7 = CPositionableObject::getPosition((CPositionableObject *)param_5,true);
            local_68._4_4_ = (float)((ulong)uVar7 >> 0x20);
            local_68._0_4_ = (float)uVar7;
            local_54 = local_68._4_4_ - local_78._4_4_;
            local_58 = (float)local_68 - (float)local_78;
            local_50 = fVar5 - local_70;
            fVar8 = SQRT(local_58 * local_58 + local_54 * local_54 + local_50 * local_50);
            if (DAT_00fa87a0 < (double)fVar8) {
              fVar8 = DAT_00fa47fc / fVar8;
              local_58 = local_58 * fVar8;
              local_54 = local_54 * fVar8;
              local_50 = fVar8 * local_50;
            }
            local_80 = local_54 * Ogre::Vector3::UNIT_Y - DAT_01424b38 * local_58;
            local_84 = local_58 * DAT_01424b3c - Ogre::Vector3::UNIT_Y * local_50;
            local_88 = local_50 * DAT_01424b38 - local_54 * DAT_01424b3c;
            local_68 = uVar7;
            local_60 = fVar5;
            (**(code **)(*(long *)this_00 + 0x148))(this_00,&local_58);
            (**(code **)(*(long *)this_00 + 0x170))(this_00,&local_88);
          }
          CCharacter::spawn((CCharacter *)this_00);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < local_a0);
    }
    if (local_a8 != (long *)0x0) {
      operator_delete__(local_a8);
    }
  }
  return;
}

/* export-summary functions=41 failures=0 */
