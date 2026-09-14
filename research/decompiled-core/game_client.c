/* Targeted Ghidra class export.
   namespace=CGameClient
   Treat pseudocode as navigation evidence. */


/* address=0056e110
   symbol=CGameClient::destroyGameUI */

/* CGameClient::destroyGameUI() */

void __thiscall CGameClient::destroyGameUI(CGameClient *this)

{
  if (*(long **)(this + 0x78) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x78) + 8))();
    *(undefined8 *)(this + 0x78) = 0;
  }
  *(undefined8 *)(this + 0x78) = 0;
  return;
}



/* address=0056e140
   symbol=CGameClient::updateScreenInfo */

/* CGameClient::updateScreenInfo(void*, int, int) */

void __thiscall
CGameClient::updateScreenInfo(CGameClient *this,void *param_1,int param_2,int param_3)

{
  *(void **)(this + 0x88) = param_1;
  *(int *)(this + 0x90) = param_2;
  *(int *)(this + 0x94) = param_3;
  return;
}



/* address=0056e160
   symbol=CGameClient::handleFunctionKeys */

/* CGameClient::handleFunctionKeys() */

void CGameClient::handleFunctionKeys(void)

{
  return;
}



/* address=0056e170
   symbol=CGameClient::setSpeedMult */

/* CGameClient::setSpeedMult(float) */

void __thiscall CGameClient::setSpeedMult(CGameClient *this,float param_1)

{
  if ((DAT_00fa47f8 < param_1) || (NAN(param_1) || NAN(DAT_00fa47f8))) {
    if (DAT_00fa86d0 < param_1) {
      *(float *)(this + 0x38c0) = DAT_00fa86d0;
      return;
    }
  }
  else {
    param_1 = 0.0;
  }
  *(float *)(this + 0x38c0) = param_1;
  return;
}



/* address=0056e1b0
   symbol=CGameClient::toggleLighting */

/* CGameClient::toggleLighting(bool) */

void CGameClient::toggleLighting(bool param_1)

{
  return;
}



/* address=0056e1c0
   symbol=CGameClient::togglePlayerLight */

/* CGameClient::togglePlayerLight() */

void __thiscall CGameClient::togglePlayerLight(CGameClient *this)

{
  long lVar1;

  if ((*(long *)(this + 0x220) != 0) && (*(long **)(this + 0x230) != (long *)0x0)) {
    lVar1 = (**(code **)(**(long **)(this + 0x230) + 0xa0))();
    if (lVar1 != 0) {
                    /* WARNING: Could not recover jumptable at 0x0056e201. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(**(long **)(this + 0x220) + 0x2a0))
                (*(long **)(this + 0x220),*(undefined8 *)(this + 0x230));
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x0056e229. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(this + 0x220) + 0x278))
              (*(long **)(this + 0x220),*(undefined8 *)(this + 0x230));
    return;
  }
  return;
}



/* address=0056e230
   symbol=CGameClient::getPlayerIsCheat */

/* CGameClient::getPlayerIsCheat() */

bool __thiscall CGameClient::getPlayerIsCheat(CGameClient *this)

{
  bool bVar1;

  bVar1 = false;
  if (*(long *)(this + 0x58) != 0) {
    bVar1 = *(char *)(*(long *)(this + 0x58) + 0x791) == -0x2a;
  }
  return bVar1;
}



/* address=0056e250
   symbol=CGameClient::getPlayerClassName */

/* CGameClient::getPlayerClassName() */

void CGameClient::getPlayerClassName(void)

{
  long in_RSI;
  STRINGS *in_RDI;

  if (*(long *)(in_RSI + 0x58) != 0) {
    CPlayer::getPlayerClassName();
    return;
  }
  STRINGS::StringUpper(in_RDI,(wstring_conflict *)(in_RSI + 0x1a8));
  return;
}



/* address=0056e290
   symbol=CGameClient::setEditorCreationPet */

/* CGameClient::setEditorCreationPet(std::wstring) */

void CGameClient::setEditorCreationPet(long param_1)

{
  std::wstring::assign((wstring_conflict *)(param_1 + 0x1b0));
  return;
}



/* address=0056e2a0
   symbol=CGameClient::setEditorCreationClass */

/* CGameClient::setEditorCreationClass(std::wstring) */

void CGameClient::setEditorCreationClass(long param_1)

{
  std::wstring::assign((wstring_conflict *)(param_1 + 0x1a8));
  return;
}



/* address=0056e2b0
   symbol=CGameClient::findCameraTargetLocation */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameClient::findCameraTargetLocation(Ogre::Vector3&, float) */

void __thiscall
CGameClient::findCameraTargetLocation(CGameClient *this,Vector3 *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined8 local_48;
  float local_40;
  undefined8 local_3c;
  float local_34;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;

  local_28 = 0;
  local_20 = 0;
  local_24 = 0x3f800000;
  local_48 = _ZERO;
  local_40 = DAT_014241b4;
  local_3c = _UNIT_Z;
  local_34 = DAT_014241a0;
  Ogre::Camera::getCameraToViewportRay
            (DAT_00fa4810,DAT_00fa4810,*(Ray **)(*(long *)(this + 0x20) + 0x10));
  fVar2 = local_34;
  fVar1 = (float)local_3c;
  fVar3 = (float)MATH::distanceToPlane
                           ((Vector3 *)&local_48,(Vector3 *)&local_3c,(Vector3 *)&local_28,param_2);
  *(undefined4 *)(param_1 + 4) = 0;
  *(float *)(param_1 + 8) = fVar2 * fVar3 + local_40;
  *(float *)param_1 = fVar3 * fVar1 + (float)local_48;
  return;
}



/* address=0056e3a0
   symbol=CGameClient::autoPickupGold */

/* CGameClient::autoPickupGold() */

void CGameClient::autoPickupGold(void)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  char cVar3;
  long in_RDI;
  float fVar4;
  float fVar5;
  float in_XMM1_Da;
  float fVar6;

  if (((*(CCharacter **)(in_RDI + 0x58) != (CCharacter *)0x0) &&
      (cVar3 = CCharacter::alive(*(CCharacter **)(in_RDI + 0x58)), cVar3 != '\0')) &&
     (*(char *)(*(long *)(in_RDI + 0x58) + 0x264) != '\0')) {
    puVar1 = (undefined8 *)**(undefined8 **)(*(long *)(in_RDI + 0x70) + 0xc0);
    while (puVar2 = puVar1, puVar2 != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)puVar2[1];
      cVar3 = CBaseUnit::ISA((CBaseUnit *)*puVar2,0x22);
      if (cVar3 != '\0') {
        fVar4 = (float)CPositionableObject::getPosition
                                 (*(CPositionableObject **)(in_RDI + 0x58),true);
        fVar6 = in_XMM1_Da;
        fVar5 = (float)CPositionableObject::getPosition((CPositionableObject *)*puVar2,true);
        fVar6 = fVar6 - in_XMM1_Da;
        in_XMM1_Da = DAT_00fa86d4;
        if (SQRT((fVar5 - fVar4) * (fVar5 - fVar4) + 0.0 + fVar6 * fVar6) < DAT_00fa86d4) {
          CCharacter::getItem(*(CCharacter **)(in_RDI + 0x58),(CItem *)*puVar2,
                              *(CLevel **)(in_RDI + 0x70));
        }
      }
    }
  }
  return;
}



/* address=0056e4d0
   symbol=CGameClient::processMenuInput */

/* CGameClient::processMenuInput(void*, float, bool) */

undefined8 __thiscall
CGameClient::processMenuInput(CGameClient *this,void *param_1,float param_2,bool param_3)

{
  CMouseManager *pCVar1;
  char cVar2;

  pCVar1 = (CMouseManager *)(this + 0xfe8);
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    cVar2 = CGameUI::processInput(*(CGameUI **)(this + 0x78),this,param_1,param_2,param_3);
    if (cVar2 == '\0') {
      cVar2 = CMouseManager::buttonHeld(pCVar1,0);
      if (cVar2 != '\0') {
        this[0x99] = (CGameClient)0x1;
      }
      cVar2 = CMouseManager::buttonHeld(pCVar1,1);
      if (cVar2 != '\0') {
        this[0x9a] = (CGameClient)0x1;
      }
      this[0x98] = (CGameClient)0x1;
    }
  }
  CMouseManager::update(pCVar1);
  return 1;
}



/* address=0056e570
   symbol=CGameClient::getIsPaused */

/* CGameClient::getIsPaused() */

undefined1 __thiscall CGameClient::getIsPaused(CGameClient *this)

{
  char cVar1;
  int iVar2;

  if (this[0x10bb] != (CGameClient)0x0) {
    return 1;
  }
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    cVar1 = CGameUI::bothCoveredPartial(*(CGameUI **)(this + 0x78));
    if (cVar1 != '\0') {
      return 1;
    }
    if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
      cVar1 = CGameUI::getConsoleIsOpen(*(CGameUI **)(this + 0x78));
      if ((cVar1 != '\0') &&
         (iVar2 = CDynamicPropertyFile::GetInt
                            (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_CONSOLE_NOPAUSE),
         iVar2 == 0)) {
        return 1;
      }
      if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
        cVar1 = CGameUI::modalDialogOpenPartial(*(CGameUI **)(this + 0x78));
        if (cVar1 != '\0') {
          return 1;
        }
        if (*(long *)(this + 0x78) != 0) {
          return *(undefined1 *)(*(long *)(this + 0x78) + 0x1999);
        }
      }
    }
  }
  return 0;
}



/* address=0056e600
   symbol=CGameClient::mouseEvent */

/* CGameClient::mouseEvent(unsigned int, unsigned int) */

void __thiscall CGameClient::mouseEvent(CGameClient *this,uint param_1,uint param_2)

{
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::mouseEvent(*(CGameUI **)(this + 0x78),param_1,param_2);
  }
  CMouseManager::mouseEvent((CMouseManager *)(this + 0xfe8),param_1,param_2);
  return;
}



/* address=0056e650
   symbol=CGameClient::keyEvent */

/* CGameClient::keyEvent(unsigned int, unsigned int, long) */

void CGameClient::keyEvent(uint param_1,uint param_2,long param_3)

{
  long lVar1;
  undefined4 in_register_0000003c;

  lVar1 = *(long *)(CONCAT44(in_register_0000003c,param_1) + 0x78);
  if (lVar1 != 0) {
    CGameUI::keyEvent((uint)lVar1,param_2,param_3);
  }
  CKeyManager::keyEvent
            ((CKeyManager *)(CONCAT44(in_register_0000003c,param_1) + 0x2d0),param_2,(uint)param_3);
  return;
}



/* address=0056e6a0
   symbol=CGameClient::setWindowActive */

/* CGameClient::setWindowActive(bool) */

void __thiscall CGameClient::setWindowActive(CGameClient *this,bool param_1)

{
  if ((!param_1) && (*(CCharacter **)(this + 0x58) != (CCharacter *)0x0)) {
    CCharacter::stopPathing(*(CCharacter **)(this + 0x58));
    *(undefined1 *)(*(long *)(this + 0x58) + 0x266) = 0;
    CKeyManager::flushAll((CKeyManager *)(this + 0x2d0));
    CMouseManager::flushAll((CMouseManager *)(this + 0xfe8));
    this[0x99] = (CGameClient)0x0;
    this[0x9a] = (CGameClient)0x0;
    this[0x98] = (CGameClient)0x1;
    if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
      CGameUI::setWindowActive(*(CGameUI **)(this + 0x78),false);
      return;
    }
  }
  return;
}



/* address=0056e710
   symbol=CGameClient::resetGameSeed */

/* CGameClient::resetGameSeed(int) */

void __thiscall CGameClient::resetGameSeed(CGameClient *this,int param_1)

{
  int iVar1;

  iVar1 = 0;
  if (*(long *)(this + 0x38d8) != 0) {
    iVar1 = *(int *)(*(long *)(this + 0x38d8) + 0x58);
  }
  if (param_1 == -1) {
    param_1 = *(int *)(this + 0x1094);
  }
  UTILITIES::setSeed(iVar1 + *(int *)(this + 0x1090) + param_1);
  return;
}



/* address=0056e740
   symbol=CGameClient::notifyOfDeletion */

/* CGameClient::notifyOfDeletion(CItem*) */

void __thiscall CGameClient::notifyOfDeletion(CGameClient *this,CItem *param_1)

{
  if (param_1 == *(CItem **)(this + 0x1e8)) {
    TSafePointer<CItem>::setObject((TSafePointer<CItem> *)(this + 0x1e8),(CItem *)0x0);
  }
  if (param_1 == *(CItem **)(this + 0x1f8)) {
    TSafePointer<CItem>::setObject((TSafePointer<CItem> *)(this + 0x1f8),(CItem *)0x0);
  }
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::notifyOfDeletion(*(CGameUI **)(this + 0x78),param_1);
    return;
  }
  return;
}



/* address=0056e7c0
   symbol=CGameClient::notifyOfDeletion */

/* CGameClient::notifyOfDeletion(CCharacter*) */

void __thiscall CGameClient::notifyOfDeletion(CGameClient *this,CCharacter *param_1)

{
  if (param_1 == *(CCharacter **)(this + 0x1d8)) {
    TSafePointer<CCharacter>::setObject
              ((TSafePointer<CCharacter> *)(this + 0x1d8),(CCharacter *)0x0);
  }
  if (param_1 == *(CCharacter **)(this + 0x1c8)) {
    TSafePointer<CCharacter>::setObject
              ((TSafePointer<CCharacter> *)(this + 0x1c8),(CCharacter *)0x0);
  }
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::notifyOfDeletion(*(CGameUI **)(this + 0x78),param_1);
    return;
  }
  return;
}



/* address=0056e840
   symbol=CGameClient::updateCursor */

/* CGameClient::updateCursor() */

void __thiscall CGameClient::updateCursor(CGameClient *this)

{
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::updateHardwareCursor(*(CGameUI **)(this + 0x78));
    return;
  }
  return;
}



/* address=0056e860
   symbol=CGameClient::reloadSoundBankData */

/* CGameClient::reloadSoundBankData() */

void __thiscall CGameClient::reloadSoundBankData(CGameClient *this)

{
  if (*(long *)(this + 0x1040) != 0) {
    CSoundManager::stopAllSounds(*(CSoundManager **)(this + 0x48));
    CMasterResourceManager::reloadSoundBankData(*(CMasterResourceManager **)(this + 0x1040));
    return;
  }
  return;
}



/* address=0056e890
   symbol=CGameClient::questEventFire */

/* CGameClient::questEventFire(EQUEST_EVENTS, CCharacter*, CBaseUnit*) */

void CGameClient::questEventFire(long param_1)

{
  if (*(long *)(param_1 + 0x68) != 0) {
    CQuestManager::questEventUpdate();
    return;
  }
  return;
}



/* address=0056e8b0
   symbol=CGameClient::clearSceneManagerPassMaps */

/* CGameClient::clearSceneManagerPassMaps() */

void __thiscall CGameClient::clearSceneManagerPassMaps(CGameClient *this)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree_node_base *p_Var2;
  long lVar3;
  _Rb_tree_node_base *p_Var4;
  undefined1 auVar5 [16];

  this[0x38d4] = (CGameClient)0x0;
  if (*(long *)(this + 0x1058) == 0) {
    return;
  }
  auVar5 = Ogre::Root::getSceneManagerIterator();
  p_Var4 = auVar5._0_8_;
  while (p_Var4 != auVar5._8_8_) {
    p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var4);
    p_Var1 = p_Var4 + 0x28;
    p_Var4 = p_Var2;
    if ((*(long **)p_Var1 != (long *)0x0) &&
       (lVar3 = (**(code **)(**(long **)p_Var1 + 0x540))(), lVar3 != 0)) {
      Ogre::RenderQueue::clear(SUB81(lVar3,0));
    }
  }
  Ogre::Pass::processPendingPassUpdates();
  return;
}



/* address=00578fe0
   symbol=CGameClient::_GLOBAL__I_CGameClient */

/* CGameClient::CGameClient(CSettings&, CMasterResourceManager*, Ogre::RenderWindow*, Ogre::Root*,
   CCameraControl*, Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CSoundManager&)
    */

void CGameClient::_GLOBAL__I_CGameClient(void)

{
  allocator aStack_3c9;
  allocator aStack_3c8;
  allocator aStack_3c7;
  allocator aStack_3c6;
  allocator aStack_3c5;
  allocator aStack_3c4;
  allocator aStack_3c3;
  allocator aStack_3c2;
  allocator aStack_3c1;
  allocator aStack_3c0;
  allocator aStack_3bf;
  allocator aStack_3be;
  allocator aStack_3bd;
  allocator aStack_3bc;
  allocator aStack_3bb;
  allocator aStack_3ba;
  allocator aStack_3b9;
  allocator aStack_3b8;
  allocator aStack_3b7;
  allocator aStack_3b6;
  allocator aStack_3b5;
  allocator aStack_3b4;
  allocator aStack_3b3;
  allocator aStack_3b2;
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
  allocator aaStack_29 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_3c9);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_3c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_3c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_3c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_3c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_3c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_3c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_3c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_3c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_3c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_3bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_3be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_3bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_3bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_3bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_3ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_3b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_3b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_3b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_3b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_3b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_3b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_3b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_3b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_3b1);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_3b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_3af);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_3ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_3ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_3ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_3ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_3aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_3a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_3a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_3a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_3a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_3a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_3a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_3a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_3a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_3a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_3a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_39f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_39e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_39d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_39c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_39b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_39a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_399);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_398);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_397);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_396);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_395);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_394);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_393);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_392);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_391);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_390);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_38f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_38e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_38d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_38c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_38b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_38a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_389);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_388);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_387);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_386);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_385);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_384);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_383);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_382);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_381);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_380);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_37f);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_37e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_37d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_37c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_37b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_37a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_379);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_378);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_377);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_376);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_375);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_374);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_373);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_372);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_371);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_370);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_36f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_36e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_36d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_36c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_36b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_36a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_369);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_368);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_367);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_366);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_365);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_364);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_363);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_362);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_361);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_360);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_35f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_35e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_35d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_35c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_35b)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_35a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_359)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_358)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_357)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_356)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_355);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_354);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_353);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_352);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_351);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_350);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_34f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_34e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_34d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_34c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_34b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_34a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_349);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_348)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_347);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_346)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_345);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_344);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_343);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_342);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_341);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_340);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_33f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_33e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_33d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_33c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_33b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_33a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_339);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_338);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_337
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_336);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_335);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_334)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_333);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_332
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_331)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_330);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_32f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_32e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_32d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_32c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_32b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_32a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_328
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_327);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_326);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_325);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_324);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_323);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_322);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_321);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_320);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_31f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_31e);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_31d);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_31c);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_31b);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_31a);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_319);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_318);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_317);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_316);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_315);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_314);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_313);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_312);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_311);
  std::wstring::wstring((wstring_conflict *)&DAT_01426aa8,L"ITEM",&aStack_310);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_30f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_30e);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_30d);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_30c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_30b);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_30a);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_309);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_308);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_307);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_306);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_305);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_304);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_303);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_302);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_301);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_300);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_2ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_2fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_2fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_2fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_2fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_2fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_2f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_2f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_2f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_2f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_2f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_2f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_2f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_2f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_2ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_2ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_2ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_2eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_2ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_2e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_2e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_2e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_2e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_2e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_2e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_2e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_2e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_2e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_2e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_2df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_2de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_2dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_2dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_2db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_2da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_2d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_2d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_2d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_2d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_2d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_2d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_2d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_2d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_2d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_2d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_2cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_2ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_2cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_2cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_2ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_2c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_2c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_2c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_2c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_2c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_2c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_2c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_2c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_2c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_2bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_2be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_2bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_2bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_2b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_2b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_2b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_2b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_2b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_2af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_2ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_2ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_2aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_2a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_2a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_2a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_2a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_2a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_2a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_29d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_29b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_299);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_298);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_297);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_296);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_295);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_28f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_28c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_289);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_279);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_273);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_271);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_270);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_25e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_25d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_25c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_25b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_259);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_258);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_254);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_223);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_220);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_21d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_214);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_213);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_210);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_201);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_200);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_1ff);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_1fe);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_1fd);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_1fc);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_1fb);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_1fa);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_1f9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_1f8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_1f7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_1f6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_1f5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_1f1);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_1eb);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_1e9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_1e8);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_1e2);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_1e1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_1e0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_1df);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_1de)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_1dd)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_1dc)
  ;
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_1db);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_1da);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_1d9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_1d8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_1d7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_1d6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_1d5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_1d4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_1d3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_1d2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_1d1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_1d0);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_1cf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_1ce);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_1cd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_1cc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_1cb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_1ca);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_1c9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_1c8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_1c7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_1c6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_1c5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_1c4);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_1c3);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_1c2);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_1c1);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_1c0);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_1bf);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_1be);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_1bd);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_1bc);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_1bb);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_1ba);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_1b9);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_1b8);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_1b3);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_1ae);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_1ad);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",
             &aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_1a2);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_197);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_18d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_188);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_184);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_182);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_181);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_180);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_17d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_17c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_17b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_178)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_177)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_16e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_16d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_16c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_16b);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)&DAT_01427898,L"Two",&aStack_169);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_167);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_166);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_160);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_15f);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_15a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_159);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_158);
  std::wstring::wstring((wstring_conflict *)&DAT_01427938,L"ABOVE",&aStack_157);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_154);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_153);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_152);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_150);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_14f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_14a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_149);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_148);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_147)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_146);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_144);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_141)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_13f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_13d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_13b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_13a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_139);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_138);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_135)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_133);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_131);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_130);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_12f);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_129);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_124)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_123);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_11d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_11c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_11b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_10c);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_108
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_105)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_104)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_103
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_101
            );
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_ff)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_fb);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_f9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_f8)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_f5);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_f3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_f0);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_ec);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_e9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_e8);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_e6);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_e4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_e3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_e2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_e1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_e0);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_dc);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gPROPERTY_NODE_TYPE_NAMES,L"Point of Interest",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 8),L"Player Start",&aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x10),L"Editor Player Start",
             &aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x18),L"No Spawn Region",&aStack_d8);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x20),L"Entrance",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x28),L"Exit",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x30),L"Jump Down Area",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x38),L"Town Portal",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x40),L"Path Node Occupation Circle",
             &aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x48),L"Path Node Occupation Box",
             &aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x50),L"Camera Position",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x58),L"Camera Target",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x60),L"Quest Item",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x68),L"Quest Boss",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x70),L"Waypoint",&aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x78),L"Waypoint Start",&aStack_cc);
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gCOUNTER_TYPE_NAMES,L"Activate only once",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 8),L"Activate and reset",&aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x10),L"Activate on each add",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x18),L"Activate on each add and reset",
             &aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x20),L"Activate on each subtract",
             &aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x28),L"Activate on each subtract and reset"
             ,&aStack_c6);
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_bc);
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_INTERP_TYPES,L"Linear",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 8),L"Linear Round",&aStack_ba)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x10),L"Linear Round Down",&aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x18),L"Linear Round Up",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x20),L"Spline",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x28),L"Quaternion",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x30),L"No Interpolation",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x38),L"Use Timeline Default",&aStack_b4)
  ;
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_b1);
  __cxa_atexit(__tcf_45,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gRANDOMGROUP_NAMES,L"ALL",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 8),L"Weight",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 0x10),L"Random Chance",&aStack_ae)
  ;
  __cxa_atexit(__tcf_46,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gANIMATIONPLAYER_TYPE_NAMES,L"PLAYER",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 8),L"MONSTERS",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 0x10),L"UNITTYPE",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 0x18),L"PROP",&aStack_aa)
  ;
  __cxa_atexit(__tcf_47,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_a9);
  std::wstring::wstring((wstring_conflict *)&DAT_01427fa8,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_a8);
  __cxa_atexit(__tcf_48,0,&__dso_handle);
  ::g_strStatDefines._0_4_ = 1;
  ::g_strStatDefines._4_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 8),"STAT_DEATHS",&aStack_a7);
  ::g_strStatDefines[0x10] = 0;
  ::g_strStatDefines._24_4_ = 2;
  ::g_strStatDefines._28_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x20),"STAT_BREAKABLES",&aStack_a6);
  ::g_strStatDefines[0x28] = 0;
  ::g_strStatDefines._48_4_ = 3;
  ::g_strStatDefines._52_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x38),"STAT_CRITICAL_STRIKES",&aStack_a5);
  ::g_strStatDefines[0x40] = 0;
  ::g_strStatDefines._72_4_ = 4;
  ::g_strStatDefines._76_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x50),"STAT_MAX_DMG_DONE",&aStack_a4);
  ::g_strStatDefines[0x58] = 0;
  ::g_strStatDefines._96_4_ = 5;
  ::g_strStatDefines._100_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x68),"STAT_MONSTERS_KILLED",&aStack_a3);
  ::g_strStatDefines[0x70] = 0;
  ::g_strStatDefines._120_4_ = 6;
  ::g_strStatDefines._124_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x80),"STAT_DEEPEST_FLOOR",&aStack_a2);
  ::g_strStatDefines[0x88] = 0;
  ::g_strStatDefines._144_4_ = 7;
  ::g_strStatDefines._148_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x98),"STAT_FISH_CAUGHT",&aStack_a1);
  ::g_strStatDefines[0xa0] = 0;
  ::g_strStatDefines._168_4_ = 8;
  ::g_strStatDefines._172_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xb0),"STAT_ENCHANTER_FAILS",&aStack_a0);
  ::g_strStatDefines[0xb8] = 0;
  ::g_strStatDefines._192_4_ = 9;
  ::g_strStatDefines._196_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 200),"STAT_RECIPES_MADE",&aStack_9f);
  ::g_strStatDefines[0xd0] = 0;
  ::g_strStatDefines._216_4_ = 10;
  ::g_strStatDefines._220_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xe0),"STAT_GAMBLE_COUNT",&aStack_9e);
  ::g_strStatDefines[0xe8] = 0;
  ::g_strStatDefines._240_4_ = 0xb;
  ::g_strStatDefines._244_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xf8),"STAT_QUESTS_COMPLETED",&aStack_9d);
  ::g_strStatDefines[0x100] = 0;
  ::g_strStatDefines._264_4_ = 0xc;
  ::g_strStatDefines._268_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x110),"STAT_RETIRED_COUNT",&aStack_9c);
  ::g_strStatDefines[0x118] = 0;
  ::g_strStatDefines._288_4_ = 0xd;
  ::g_strStatDefines._292_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x128),"STAT_RETIRED_LVLS_TOTAL",&aStack_9b);
  ::g_strStatDefines[0x130] = 0;
  ::g_strStatDefines._312_4_ = 0xe;
  ::g_strStatDefines._316_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x140),"STAT_GOLD_COLLECTED",&aStack_9a);
  ::g_strStatDefines[0x148] = 0;
  ::g_strStatDefines._336_4_ = 0xf;
  ::g_strStatDefines._340_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x158),"STAT_LEVERS_PULLED",&aStack_99);
  ::g_strStatDefines[0x160] = 0;
  ::g_strStatDefines._360_4_ = 0x10;
  ::g_strStatDefines._364_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x170),"STAT_TOTAL_STEPS",&aStack_98);
  ::g_strStatDefines[0x178] = 0;
  ::g_strStatDefines._384_4_ = 0x11;
  ::g_strStatDefines._388_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x188),"STAT_TOTAL_POTIONS_USED",&aStack_97);
  ::g_strStatDefines[400] = 0;
  ::g_strStatDefines._408_4_ = 0x12;
  ::g_strStatDefines._412_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1a0),"STAT_TOTAL_ITEMS_SOLD",&aStack_96);
  ::g_strStatDefines[0x1a8] = 0;
  ::g_strStatDefines._432_4_ = 0x13;
  ::g_strStatDefines._436_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1b8),"STAT_DEATHS_HARDCORE",&aStack_95);
  ::g_strStatDefines[0x1c0] = 0;
  ::g_strStatDefines._456_4_ = 0x14;
  ::g_strStatDefines._460_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1d0),"STAT_TROLL_CHMPS",&aStack_94);
  ::g_strStatDefines[0x1d8] = 0;
  ::g_strStatDefines._480_4_ = 0x15;
  ::g_strStatDefines._484_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1e8),"STAT_POTIONS_PET",&aStack_93);
  ::g_strStatDefines[0x1f0] = 0;
  ::g_strStatDefines._504_4_ = 0x16;
  ::g_strStatDefines._508_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x200),"STAT_WIN_VANQ",&aStack_92);
  ::g_strStatDefines[0x208] = 0;
  ::g_strStatDefines._528_4_ = 0x17;
  ::g_strStatDefines._532_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x218),"STAT_WIN_ALCH",&aStack_91);
  ::g_strStatDefines[0x220] = 0;
  ::g_strStatDefines._552_4_ = 0x18;
  ::g_strStatDefines._556_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x230),"STAT_WIN_DESTROYER",&aStack_90);
  ::g_strStatDefines[0x238] = 0;
  ::g_strStatDefines._576_4_ = 0x19;
  ::g_strStatDefines._580_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x248),"STAT_EXPLODE_ENEMY",&aStack_8f);
  ::g_strStatDefines[0x250] = 0;
  ::g_strStatDefines._600_4_ = 0x1a;
  ::g_strStatDefines._604_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x260),"STAT_QUESTS_COMPLETED_HATCH",
                      &aStack_8e);
  ::g_strStatDefines[0x268] = 0;
  ::g_strStatDefines._624_4_ = 0x1b;
  ::g_strStatDefines._628_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x278),"STAT_QUESTS_COMPLETED_GARR",&aStack_8d
                     );
  ::g_strStatDefines[0x280] = 0;
  ::g_strStatDefines._648_4_ = 0x1c;
  ::g_strStatDefines._652_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x290),"STAT_HORSE_TALK",&aStack_8c);
  ::g_strStatDefines[0x298] = 0;
  ::g_strStatDefines._672_4_ = 0xffffffff;
  ::g_strStatDefines._676_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2a8),"PLAYER_DEATHS",&aStack_8b);
  ::g_strStatDefines[0x2b0] = 0;
  ::g_strStatDefines._696_4_ = 0xffffffff;
  ::g_strStatDefines._700_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2c0),"PLAYER_GOLD",&aStack_8a);
  ::g_strStatDefines[0x2c8] = 0;
  ::g_strStatDefines._720_4_ = 0xffffffff;
  ::g_strStatDefines._724_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2d8),"NONE",&aStack_89);
  ::g_strStatDefines[0x2e0] = 0;
  __cxa_atexit(__tcf_49,0,&__dso_handle);
  std::string::string((string *)g_strAchievementsCodeName,"TORCHLIGHT_ACHIEVEMENT_FIRSTLEVEL",
                      &aStack_88);
  std::string::string((string *)(g_strAchievementsCodeName + 8),"BEAST_OF_BURDEN",&aStack_87);
  std::string::string((string *)(g_strAchievementsCodeName + 0x10),"PET_SEND_TO_TOWN",&aStack_86);
  std::string::string((string *)(g_strAchievementsCodeName + 0x18),"PET_FEED_FISH_ANY",&aStack_85);
  std::string::string((string *)(g_strAchievementsCodeName + 0x20),"PET_FEED_FISH_PERMANENT",
                      &aStack_84);
  std::string::string((string *)(g_strAchievementsCodeName + 0x28),"GAMBLE_UNIQUE",&aStack_83);
  std::string::string((string *)(g_strAchievementsCodeName + 0x30),"MAX_FAME",&aStack_82);
  std::string::string((string *)(g_strAchievementsCodeName + 0x38),"KILL_BRINK",&aStack_81);
  std::string::string((string *)(g_strAchievementsCodeName + 0x40),"KILL_LICH",&aStack_80);
  std::string::string((string *)(g_strAchievementsCodeName + 0x48),"KILL_ROOT_GOLEM",&aStack_7f);
  std::string::string((string *)(g_strAchievementsCodeName + 0x50),"KILL_EMBER_COLOSSUS",&aStack_7e)
  ;
  std::string::string((string *)(g_strAchievementsCodeName + 0x58),"KILL_TROLL_BOSS",&aStack_7d);
  std::string::string((string *)(g_strAchievementsCodeName + 0x60),"KILL_MEDEA",&aStack_7c);
  std::string::string((string *)(g_strAchievementsCodeName + 0x68),"KILL_ALRIC",&aStack_7b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x70),"BEASTSLAYERI",&aStack_7a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x78),"BEASTSLAYERII",&aStack_79);
  std::string::string((string *)(g_strAchievementsCodeName + 0x80),"BEASTSLAYERIII",&aStack_78);
  std::string::string((string *)(g_strAchievementsCodeName + 0x88),"HARDCORE_VICTOR",&aStack_77);
  std::string::string((string *)(g_strAchievementsCodeName + 0x90),"HARDCORE_HERO",&aStack_76);
  std::string::string((string *)(g_strAchievementsCodeName + 0x98),"HARDCORE_CHAMPION",&aStack_75);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa0),"HARDCORE_GOD",&aStack_74);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa8),"SPEEDY",&aStack_73);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb0),"SPEED_KING",&aStack_72);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb8),"HAT_TRICK",&aStack_71);
  std::string::string((string *)(g_strAchievementsCodeName + 0xc0),"PLAYER_LEVEL_65",&aStack_70);
  std::string::string((string *)(g_strAchievementsCodeName + 200),"PLAYER_LEVEL_100",&aStack_6f);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd0),"MODS_1",&aStack_6e);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd8),"MODS_5",&aStack_6d);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe0),"MODS_10",&aStack_6c);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe8),"ENCHANTER_FAILURE_FIRST",
                      &aStack_6b);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf0),"PET_MIMIC",&aStack_6a);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf8),"PET_TRAINER",&aStack_69);
  std::string::string((string *)(g_strAchievementsCodeName + 0x100),"ENCHANTER_SUCCESS_5",&aStack_68
                     );
  std::string::string((string *)(g_strAchievementsCodeName + 0x108),"ENCHANTER_SUCCESS_10",
                      &aStack_67);
  std::string::string((string *)(g_strAchievementsCodeName + 0x110),"PERFECT_VICTORY",&aStack_66);
  std::string::string((string *)(g_strAchievementsCodeName + 0x118),"PLAYER_GOLD_IN_POCKET",
                      &aStack_65);
  __cxa_atexit(__tcf_50,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_5f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_58);
  __cxa_atexit(__tcf_51,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_57
            );
  std::wstring::wstring((wstring_conflict *)&DAT_01428458,L"Add",&aStack_56);
  __cxa_atexit(__tcf_52,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_55);
  std::wstring::wstring((wstring_conflict *)&DAT_01428468,L"Texture",&aStack_54);
  __cxa_atexit(__tcf_53,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_51);
  __cxa_atexit(__tcf_54,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_4f);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(__tcf_55,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_46);
  __cxa_atexit(__tcf_56,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_45);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_42);
  __cxa_atexit(__tcf_57,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_3d);
  __cxa_atexit(__tcf_58,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_3a);
  __cxa_atexit(__tcf_59,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_35);
  __cxa_atexit(__tcf_60,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&aStack_31
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_30);
  __cxa_atexit(__tcf_61,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_2d);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_2a);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",aaStack_29);
  __cxa_atexit(__tcf_62,0,&__dso_handle);
  return;
}



/* address=00578ff0
   symbol=CGameClient::killPets */

/* CGameClient::killPets() */

void __thiscall CGameClient::killPets(CGameClient *this)

{
  char cVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  CCharacter *this_00;

  lVar3 = *(long *)(*(long *)(this + 0x58) + 0x648);
  lVar2 = *(long *)(*(long *)(this + 0x58) + 0x650) - lVar3 >> 3;
  if (0 < (int)lVar2) {
    uVar4 = 0;
    do {
      this_00 = (CCharacter *)0x0;
      if (lVar2 != 0) {
        this_00 = *(CCharacter **)(lVar3 + (ulong)uVar4 * 8);
      }
      cVar1 = CCharacter::diesOnWarp(this_00);
      if (cVar1 != '\0') {
        uVar4 = uVar4 - 1;
        (**(code **)(*(long *)this_00 + 0x330))(0,this_00,0,0,0);
      }
      uVar4 = uVar4 + 1;
      lVar3 = *(long *)(*(long *)(this + 0x58) + 0x648);
      lVar2 = *(long *)(*(long *)(this + 0x58) + 0x650) - lVar3 >> 3;
    } while ((int)uVar4 < (int)lVar2);
  }
  return;
}



/* address=00579080
   symbol=CGameClient::createGameUI */

/* CGameClient::createGameUI(Ogre::RenderWindow*, void*) */

void __thiscall CGameClient::createGameUI(CGameClient *this,RenderWindow *param_1,void *param_2)

{
  Camera *pCVar1;
  long lVar2;
  CGameUI *this_00;

  if (*(long *)(this + 0x78) == 0) {
    lVar2 = CMasterResourceManager::getSingleton();
    *(undefined8 *)(this + 0x40) = *(undefined8 *)(lVar2 + 0xd8);
    pCVar1 = *(Camera **)(*(long *)(this + 0x20) + 0x10);
    this_00 = (CGameUI *)Ogre::NedAllocImpl::allocBytes(0x1a08,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00579134 to 00579138 has its CatchHandler @ 005791a3 */
    CGameUI::CGameUI(this_00,*(CSettings **)(this + 0x50),this,param_2,param_1,pCVar1,
                     *(SceneManager **)(this + 0x30),*(SceneManager **)(this + 0x38),
                     *(SceneManager **)(this + 0x40),*(CResourceManager **)(this + 0x2b8));
    *(CGameUI **)(this + 0x78) = this_00;
    CGameUI::setCursorState(this_00);
    CGameUI::updateHardwareCursor(*(CGameUI **)(this + 0x78));
    CGameUI::setLoadingVisible(*(CGameUI **)(this + 0x78),false);
    if (*(CCharacter **)(this + 0x58) != (CCharacter *)0x0) {
      CGameUI::setPlayer(*(CGameUI **)(this + 0x78),*(CCharacter **)(this + 0x58));
    }
    if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
      CGameUI::setLevel(*(CGameUI **)(this + 0x78),*(CLevel **)(this + 0x70));
      return;
    }
  }
  return;
}



/* address=005791c0
   symbol=CGameClient::rescaleUI */

/* CGameClient::rescaleUI() */

void __thiscall CGameClient::rescaleUI(CGameClient *this)

{
  CLevel *this_00;
  long lVar1;

  if (*(long *)(this + 0x78) != 0) {
    if (*(CCharacter **)(this + 0x58) != (CCharacter *)0x0) {
      CCharacter::destroyIcons(*(CCharacter **)(this + 0x58));
    }
    if (*(CCharacter **)(this + 0x60) != (CCharacter *)0x0) {
      CCharacter::destroyIcons(*(CCharacter **)(this + 0x60));
    }
    if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
      CLevel::destroyIcons(*(CLevel **)(this + 0x70));
    }
    if (*(CQuestManager **)(this + 0x68) != (CQuestManager *)0x0) {
      CQuestManager::destroyIcons(*(CQuestManager **)(this + 0x68));
    }
    lVar1 = CSharedStash::getSingleton();
    if ((lVar1 != 0) && (lVar1 = CSharedStash::getSingleton(), *(long *)(lVar1 + 0x10) != 0)) {
      lVar1 = CSharedStash::getSingleton();
      CInventory::destroyIcons(*(CInventory **)(lVar1 + 0x10));
    }
    destroyGameUI(this);
    createGameUI(this,*(RenderWindow **)(this + 0x1050),(void *)0x0);
    if (*(int *)(this + 0x38d0) != 0) {
      CGameUI::setIngameUIVisible(*(CGameUI **)(this + 0x78),true);
      this_00 = *(CLevel **)(this + 0x70);
      goto joined_r0x00579295;
    }
    CGameUI::setIngameUIVisible(*(CGameUI **)(this + 0x78),false);
    CGameUI::setActiveMenu(*(undefined8 *)(this + 0x78),0);
  }
  this_00 = *(CLevel **)(this + 0x70);
joined_r0x00579295:
  if (this_00 != (CLevel *)0x0) {
    CLevel::toggleAutomap(this_00);
    CLevel::toggleAutomap(*(CLevel **)(this + 0x70));
    return;
  }
  return;
}



/* address=005792a0
   symbol=CGameClient::preRenderTargetUpdate */

/* non-virtual thunk to CGameClient::preRenderTargetUpdate(Ogre::RenderTargetEvent const&) */

void __thiscall CGameClient::preRenderTargetUpdate(CGameClient *this,RenderTargetEvent *param_1)

{
  preRenderTargetUpdate(this + -0x10,param_1);
  return;
}



/* address=005792b0
   symbol=CGameClient::preRenderTargetUpdate */

/* CGameClient::preRenderTargetUpdate(Ogre::RenderTargetEvent const&) */

void __thiscall CGameClient::preRenderTargetUpdate(CGameClient *this,RenderTargetEvent *param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  undefined **local_48;
  long *local_40;
  int *local_38;

  lVar2 = (**(code **)(**(long **)(this + 0x28) + 0x540))();
  *(CGameClient **)(lVar2 + 0x40) = this + 0x18;
  if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
    CLevel::setNonLightStaticGeometryVisible(*(CLevel **)(this + 0x70),false);
  }
  plVar4 = *(long **)(this + 0x208);
  if (plVar4 != (long *)0x0) {
                    /* try { // try from 0057930f to 00579329 has its CatchHandler @ 0057945d */
    (**(code **)(*plVar4 + 0x2b0))(&local_48,plVar4,0,0);
    lVar3 = (**(code **)(*local_40 + 0x80))(local_40,0);
    lVar2 = *(long *)param_1;
    local_48 = &PTR__SharedPtr_00fa85d0;
    if ((local_38 != (int *)0x0) && (iVar1 = *local_38, *local_38 = iVar1 + -1, iVar1 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa85e0)(&local_48);
    }
    if (lVar3 == lVar2) {
      this[0x2b0] = (CGameClient)0x1;
      (**(code **)(**(long **)(this + 0x28) + 0x7f0))(*(long **)(this + 0x28),4);
      lVar2 = Ogre::SceneNode::getParentSceneNode();
      if (lVar2 != 0) {
        return;
      }
      plVar4 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
      (**(code **)(*plVar4 + 0x1a8))(plVar4,*(undefined8 *)(this + 0x218));
      return;
    }
  }
  (**(code **)(**(long **)(this + 0x28) + 0x7f0))(*(long **)(this + 0x28),2);
  this[0x2b0] = (CGameClient)0x0;
  lVar2 = Ogre::SceneNode::getParentSceneNode();
  if (lVar2 == 0) {
    plVar4 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
    (**(code **)(*plVar4 + 0x1a8))(plVar4,*(undefined8 *)(this + 0x220));
  }
  lVar2 = Ogre::SceneNode::getParentSceneNode();
  if (lVar2 == 0) {
    plVar4 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
    (**(code **)(*plVar4 + 0x1a8))(plVar4,*(undefined8 *)(this + 0x228));
  }
  return;
}



/* address=00579480
   symbol=CGameClient::postRenderTargetUpdate */

/* non-virtual thunk to CGameClient::postRenderTargetUpdate(Ogre::RenderTargetEvent const&) */

void __thiscall CGameClient::postRenderTargetUpdate(CGameClient *this,RenderTargetEvent *param_1)

{
  postRenderTargetUpdate(this + -0x10,param_1);
  return;
}



/* address=00579490
   symbol=CGameClient::postRenderTargetUpdate */

/* CGameClient::postRenderTargetUpdate(Ogre::RenderTargetEvent const&) */

void __thiscall CGameClient::postRenderTargetUpdate(CGameClient *this,RenderTargetEvent *param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  long *plVar4;
  undefined **local_48;
  long *local_40;
  int *local_38;

  lVar2 = (**(code **)(**(long **)(this + 0x28) + 0x540))();
  *(undefined8 *)(lVar2 + 0x40) = 0;
  if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
    CLevel::setNonLightStaticGeometryVisible(*(CLevel **)(this + 0x70),true);
  }
  (**(code **)(**(long **)(this + 0x28) + 0x7f0))(*(long **)(this + 0x28),7);
  plVar4 = *(long **)(this + 0x208);
  if (plVar4 != (long *)0x0) {
                    /* try { // try from 00579504 to 0057951e has its CatchHandler @ 00579617 */
    (**(code **)(*plVar4 + 0x2b0))(&local_48,plVar4,0,0);
    lVar3 = (**(code **)(*local_40 + 0x80))(local_40,0);
    lVar2 = *(long *)param_1;
    local_48 = &PTR__SharedPtr_00fa85d0;
    if ((local_38 != (int *)0x0) && (iVar1 = *local_38, *local_38 = iVar1 + -1, iVar1 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa85e0)(&local_48);
    }
    if (lVar3 == lVar2) {
      lVar2 = Ogre::SceneNode::getParentSceneNode();
      if (lVar2 == 0) {
        return;
      }
      plVar4 = (long *)Ogre::SceneNode::getParentSceneNode();
      (**(code **)(*plVar4 + 0x1e0))(plVar4,*(undefined8 *)(this + 0x218));
      return;
    }
  }
  lVar2 = Ogre::SceneNode::getParentSceneNode();
  if (lVar2 != 0) {
    plVar4 = (long *)Ogre::SceneNode::getParentSceneNode();
    (**(code **)(*plVar4 + 0x1e0))(plVar4,*(undefined8 *)(this + 0x220));
  }
  lVar2 = Ogre::SceneNode::getParentSceneNode();
  if (lVar2 != 0) {
    plVar4 = (long *)Ogre::SceneNode::getParentSceneNode();
    (**(code **)(*plVar4 + 0x1e0))(plVar4,*(undefined8 *)(this + 0x228));
  }
  return;
}



/* address=00579630
   symbol=CGameClient::updateMenu */

/* WARNING: Removing unreachable block (ram,0x00579764) */
/* CGameClient::updateMenu(float, Ogre::RenderWindow*, float, bool) */

void __thiscall
CGameClient::updateMenu
          (CGameClient *this,float param_1,RenderWindow *param_2,float param_3,bool param_4)

{
  float fVar1;
  CGameUI *pCVar2;
  char cVar3;
  bool bVar4;
  uint uVar5;
  long lVar6;
  Vector3 *pVVar7;
  long lVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_60;

  if ((*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) &&
     (cVar3 = CGameUI::isCinematicMenuOpen(*(CGameUI **)(this + 0x78)), cVar3 != '\0')) {
    CGameUI::closeCinematicMenu(*(CGameUI **)(this + 0x78));
  }
  fVar12 = (float)(~-(uint)(param_1 <= DAT_00fa86d8) & (uint)DAT_00fa86d8 |
                  (uint)param_1 & -(uint)(param_1 <= DAT_00fa86d8));
  updateMenu(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate =
       updateMenu(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate + fVar12;
  if (DAT_00fa86dc < updateMenu(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate) {
    updateMenu(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate = 0.0;
    fVar10 = *(float *)(this + 0x2a8);
    fVar11 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa4824,DAT_00fa86d0);
    fVar1 = DAT_00fa86e0;
    *(float *)(this + 0x2a8) = fVar11 * fVar12 + fVar10;
    fVar10 = (float)UTILITIES::randomBetweenVolatile(0.0,fVar1);
    if (DAT_00fa86e4 < fVar10) {
      fVar1 = *(float *)(this + 0x2a8);
      fVar10 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa86ec,DAT_00fa86e8);
      fVar10 = fVar10 + fVar1;
      *(float *)(this + 0x2a8) = fVar10;
    }
    else {
      fVar10 = *(float *)(this + 0x2a8);
    }
    if (DAT_00fa86f0 <= fVar10) {
      do {
        fVar10 = fVar10 - DAT_00fa86f0;
      } while (DAT_00fa86f0 <= fVar10);
      *(float *)(this + 0x2a8) = fVar10;
    }
  }
  Ogre::Rectangle2D::setCorners(DAT_00fa86f4,DAT_00fa4810,DAT_00fa4810,DAT_00fa86f4);
                    /* try { // try from 00579755 to 00579759 has its CatchHandler @ 00579aed */
  Ogre::SimpleRenderable::setBoundingBox(*(AxisAlignedBox **)(this + 0x230));
  lVar6 = CMasterResourceManager::getSingleton();
  *(undefined1 *)(*(long *)(lVar6 + 0xf0) + 0x540) = 0;
  CMouseManager::capture((CMouseManager *)(this + 0xfe8));
  CKeyManager::capture((CKeyManager *)(this + 0x2d0));
  fVar10 = ceilf(fVar12 / DAT_00fa86dc);
  uVar5 = (uint)(long)fVar10;
  if (uVar5 < 6) {
    if (uVar5 == 0) {
      iVar9 = 0;
      uVar5 = (uint)CONCAT71((int7)((ulong)(long)fVar10 >> 8),1);
      goto LAB_005797be;
    }
  }
  else {
    uVar5 = 5;
  }
  iVar9 = uVar5 - 1;
LAB_005797be:
  fVar12 = fVar12 / (float)uVar5;
  local_60 = param_3;
  if (((param_3 == DAT_00fa47f8) && (!NAN(param_3) && !NAN(DAT_00fa47f8))) && (param_4)) {
    local_60 = (float)uVar5 * fVar12;
  }
  for (; -1 < iVar9; iVar9 = iVar9 + -1) {
    CLevel::update(*(Camera **)(this + 0x70),*(Vector3 **)(*(long *)(this + 0x20) + 0x10),fVar12,
                   DAT_00fa47fc,(CPlayer *)(*(Camera **)(this + 0x70) + 0x194));
  }
  if (*(long **)(this + 0x1080) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1080) + 0x208))(local_60);
  }
  if (param_4) {
    CLevel::updateLayouts(*(CLevel **)(this + 0x70),local_60);
    CLevel::updateCharacterAnimation(*(CLevel **)(this + 0x70),local_60,DAT_00fa47fc,(CPlayer *)0x0)
    ;
    bVar4 = (bool)getIsPaused(this);
    CLevel::updateVisibleParticles
              (*(CLevel **)(this + 0x70),*(Camera **)(*(long *)(this + 0x20) + 0x10),
               (Vector3 *)(*(long *)(this + 0x20) + 0x4c),bVar4);
  }
  if (*(CGameClient **)(this + 0x78) != (CGameClient *)0x0) {
    CGameUI::update(local_60,*(CGameClient **)(this + 0x78),(RenderWindow *)this);
    pCVar2 = *(CGameUI **)(this + 0x78);
    if (pCVar2[0x12f9] != (CGameUI)0x0) {
      this[0x103c] = (CGameClient)0x1;
    }
    if (pCVar2[0x12fa] != (CGameUI)0x0) {
      this[0x103d] = (CGameClient)0x1;
    }
    CGameUI::setCursorState(pCVar2,0);
  }
  if ((*(long *)(*(long *)(this + 0x20) + 0x10) != 0) &&
     (CCameraControl::updateGameCamera
                (local_60,*(undefined8 *)(*(long *)(this + 0x70) + 0x194),
                 *(undefined4 *)(*(long *)(this + 0x70) + 0x19c),*(long *)(this + 0x20),
                 *(undefined8 *)(this + 0x2b8),3), *(long *)(this + 0x1060) != 0)) {
    pVVar7 = (Vector3 *)Ogre::Camera::getPosition();
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x1060),pVVar7);
  }
  lVar6 = *(long *)(this + 0x70);
  *(undefined4 *)(this + 0x2c0) = *(undefined4 *)(lVar6 + 0x194);
  *(undefined4 *)(this + 0x2c4) = *(undefined4 *)(lVar6 + 0x198);
  *(undefined4 *)(this + 0x2c8) = *(undefined4 *)(lVar6 + 0x19c);
  lVar8 = CMasterResourceManager::getSingleton();
  lVar8 = *(long *)(lVar8 + 0xf0);
  *(undefined4 *)(lVar8 + 0x4e0) = *(undefined4 *)(lVar6 + 0x194);
  *(undefined4 *)(lVar8 + 0x4e4) = *(undefined4 *)(lVar6 + 0x198);
  *(undefined4 *)(lVar8 + 0x4e8) = *(undefined4 *)(lVar6 + 0x19c);
  if (*(CPositionableObject **)(this + 0x1080) != (CPositionableObject *)0x0) {
    CPositionableObject::setPosition
              (*(CPositionableObject **)(this + 0x1080),(Vector3 *)(*(long *)(this + 0x70) + 0x194))
    ;
  }
  CSkillManager::globallyDisableSkills(false);
  return;
}



/* address=00579b10
   symbol=CGameClient::unloadCurrentLevel */

/* CGameClient::unloadCurrentLevel(bool) */

undefined8 __thiscall CGameClient::unloadCurrentLevel(CGameClient *this,bool param_1)

{
  long *plVar1;
  long lVar2;
  CCameraControl *this_00;
  ColourValue *pCVar3;

  CGameSpeed::getSingleton();
  CGameSpeed::clear();
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::hideTextEvents(*(CGameUI **)(this + 0x78));
  }
  CQuestManager::setPlayer(*(CQuestManager **)(this + 0x68),(CPlayer *)0x0);
  if (param_1) {
    if ((*(CCharacter **)(this + 0x58) != (CCharacter *)0x0) &&
       (*(CLevel **)(this + 0x70) != (CLevel *)0x0)) {
      CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x58),true);
    }
    if ((*(CCharacter **)(this + 0x60) != (CCharacter *)0x0) &&
       (*(CLevel **)(this + 0x70) != (CLevel *)0x0)) {
      CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x60),true);
    }
  }
  lVar2 = CResourceManager::getCameraControl();
  if (lVar2 != 0) {
    this_00 = (CCameraControl *)CResourceManager::getCameraControl();
    CCameraControl::clearCameraShakes(this_00);
  }
  plVar1 = *(long **)(this + 0x1050);
  if (plVar1 != (long *)0x0) {
    pCVar3 = (ColourValue *)(**(code **)(*plVar1 + 0x58))(plVar1,0);
    Ogre::Viewport::setBackgroundColour(pCVar3);
  }
  Ogre::SceneManager::setFog
            (DAT_00fa4828,0,DAT_00fa47fc,*(undefined8 *)(this + 0x28),0,&Ogre::ColourValue::White);
  if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),*(uint *)(this + 0x1e0)
              );
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1c8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1c8),(TSafePointer *)(this + 0x1c8),*(uint *)(this + 0x1d0)
              );
    *(undefined8 *)(this + 0x1c8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),*(uint *)(this + 0x1f0)
              );
    *(undefined8 *)(this + 0x1e8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1f8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1f8),(TSafePointer *)(this + 0x1f8),*(uint *)(this + 0x200)
              );
    *(undefined8 *)(this + 0x1f8) = 0;
  }
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::setPlayer(*(CGameUI **)(this + 0x78),(CCharacter *)0x0);
    CGameUI::setLevel(*(CGameUI **)(this + 0x78),(CLevel *)0x0);
    CGameUI::cleanupReferences(*(CGameUI **)(this + 0x78));
  }
  if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
    CLevel::clearProjectorPass
              (*(CLevel **)(this + 0x70),*(CGenericModel **)(this + 0x1068),
               *(CGenericModel **)(this + 0x1070));
    if (*(long **)(this + 0x70) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x70) + 8))();
      *(undefined8 *)(this + 0x70) = 0;
    }
  }
  *(undefined8 *)(*(long *)(this + 0x2b8) + 0x18) = 0;
  if (*(long **)(this + 0x1080) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1080) + 0x50))();
    if (*(long **)(this + 0x1080) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x1080) + 8))();
      *(undefined8 *)(this + 0x1080) = 0;
    }
  }
  if (*(long **)(this + 0x1060) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1060) + 0x50))();
    if (*(long **)(this + 0x1060) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x1060) + 8))();
      *(undefined8 *)(this + 0x1060) = 0;
    }
    *(undefined8 *)(this + 0x1060) = 0;
  }
  if (*(long **)(this + 0x1068) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1068) + 0x50))();
    if (*(long **)(this + 0x1068) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x1068) + 8))();
      *(undefined8 *)(this + 0x1068) = 0;
    }
    *(undefined8 *)(this + 0x1068) = 0;
  }
  if (*(long **)(this + 0x1078) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1078) + 0x50))();
    if (*(long **)(this + 0x1078) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x1078) + 8))();
      *(undefined8 *)(this + 0x1078) = 0;
    }
    *(undefined8 *)(this + 0x1078) = 0;
  }
  if (*(long **)(this + 0x1070) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1070) + 0x50))();
    if (*(long **)(this + 0x1070) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x1070) + 8))();
      *(undefined8 *)(this + 0x1070) = 0;
    }
    *(undefined8 *)(this + 0x1070) = 0;
  }
  if (param_1) {
    if (*(long **)(this + 0x58) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x58) + 8))();
      *(undefined8 *)(this + 0x58) = 0;
    }
    if (*(long **)(this + 0x60) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x60) + 8))();
      *(undefined8 *)(this + 0x60) = 0;
    }
  }
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  CQuestManager::setPlayer(*(CQuestManager **)(this + 0x68),(CPlayer *)0x0);
  return 1;
}



/* address=00579e90
   symbol=CGameClient::findWorldLocation */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameClient::findWorldLocation(Ogre::Vector3&, bool) */

uint __thiscall CGameClient::findWorldLocation(CGameClient *this,Vector3 *param_1,bool param_2)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  undefined8 *puVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  uint uVar10;
  float fVar11;
  float local_1ec;
  float local_158;
  float fStack_144;
  undefined8 local_118;
  float local_110;
  undefined8 local_10c;
  float local_104;
  undefined8 local_f8;
  undefined8 local_f0;
  int local_e8;
  undefined4 uStack_e4;
  int local_e0;
  undefined4 uStack_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  Vector3 local_c8 [16];
  Vector3 local_b8 [4];
  float local_b4;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  uint local_80;
  undefined8 local_78;
  uint local_70;
  undefined8 local_68;
  uint local_60;
  undefined8 local_58;
  uint local_50;
  float local_48;
  float local_44;
  float local_40;
  uint local_3c [3];

  GetCursorPos((POINT *)&local_e8);
  lVar6 = CONCAT44(uStack_e4,local_e8);
  local_48 = 0.0;
  local_44 = 1.0;
  local_40 = 0.0;
  uVar10 = *(uint *)(this + 0x94);
  lVar1 = CONCAT44(uStack_dc,local_e0);
  fVar9 = DAT_00fa8700 / (float)*(uint *)(this + 0x90);
  uVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_RES_HEIGHT);
  uVar4 = CGameUI::mouseOverPanel(*(CGameUI **)(this + 0x78),local_e8,local_e0);
  lVar6 = (long)(int)((float)lVar6 * fVar9);
  uVar4 = uVar4 ^ 1;
  if (*(CGameUI **)(this + 0x78) == (CGameUI *)0x0) {
LAB_0057a828:
    local_1ec = (float)lVar6;
  }
  else {
    cVar2 = CGameUI::rightCovered(*(CGameUI **)(this + 0x78));
    if (cVar2 == '\0') {
      if (*(CGameUI **)(this + 0x78) == (CGameUI *)0x0) goto LAB_0057a828;
      cVar2 = CGameUI::leftCovered(*(CGameUI **)(this + 0x78));
      if (cVar2 == '\0') {
        local_1ec = (float)lVar6;
        goto LAB_00579fbe;
      }
      fVar9 = 0.0;
      if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
        fVar9 = (float)CGameUI::leftScreenEdge(*(CGameUI **)(this + 0x78));
      }
      lVar6 = (long)((float)(long)((float)lVar6 + DAT_00fa8704 * (fVar9 / (float)uVar3)) *
                    (DAT_00fa47fc / (DAT_00fa47fc - fVar9 / (float)uVar3)));
      if (-1 < lVar6) {
        local_1ec = (float)lVar6;
        goto LAB_00579fbe;
      }
      local_1ec = (float)lVar6;
    }
    else {
      fVar9 = DAT_00fa4800;
      if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
        fVar9 = (float)CGameUI::rightScreenEdge(*(CGameUI **)(this + 0x78));
      }
      local_1ec = (float)(long)((float)lVar6 * (DAT_00fa47fc / (fVar9 / (float)uVar3)));
      if (local_1ec <= DAT_00fa8700) goto LAB_00579fbe;
    }
    uVar4 = 0;
  }
LAB_00579fbe:
  fVar7 = (float)(**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x260))();
  fVar8 = (float)(**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x270))();
  puVar5 = (undefined8 *)(**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x2d8))();
  fVar9 = DAT_00fa8708;
  local_158 = (float)*puVar5;
  local_158 = (local_1ec * DAT_00fa4808 - DAT_00fa47fc) / local_158;
  local_58._0_4_ = fVar7 * local_158;
  local_68._0_4_ = local_158 * fVar8;
  fVar11 = (float)(int)((float)lVar1 * (DAT_00fa8708 / (float)uVar10));
  fStack_144 = (float)((ulong)puVar5[2] >> 0x20);
  fStack_144 = (fVar11 / _DAT_00fa870c + DAT_00fa47fc) / fStack_144;
  local_58._4_4_ = fVar7 * fStack_144;
  local_68._4_4_ = fStack_144 * fVar8;
  uVar10 = (uint)fVar7 ^ DAT_00fa8780;
  local_60 = (uint)fVar8 ^ DAT_00fa8780;
  local_50 = uVar10;
  (**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x2e0))();
  Ogre::Matrix4::inverse();
  puVar5 = (undefined8 *)Ogre::Camera::getOrientation();
  local_f8 = *puVar5;
  local_f0 = puVar5[1];
  local_78 = Ogre::Quaternion::operator*((Quaternion *)&local_f8,(Vector3 *)&local_58);
  local_70 = uVar10;
  local_50 = uVar10;
  local_58 = local_78;
  local_88 = Ogre::Quaternion::operator*((Quaternion *)&local_f8,(Vector3 *)&local_68);
  fVar11 = fVar11 / fVar9;
  local_118 = _ZERO;
  local_110 = DAT_014241b4;
  local_1ec = local_1ec * _DAT_00fa8710;
  local_10c = _UNIT_Z;
  local_104 = DAT_014241a0;
  local_80 = uVar10;
  local_60 = uVar10;
  local_68 = local_88;
  Ogre::Camera::getCameraToViewportRay(local_1ec,fVar11,*(Ray **)(*(long *)(this + 0x20) + 0x10));
  fVar7 = local_104;
  lVar6 = *(long *)(this + 0x58);
  fVar9 = (float)local_10c;
  fVar8 = 0.0;
  if (param_2) {
    fVar8 = DAT_00fa8714;
  }
  fVar8 = (float)MATH::distanceToPlane
                           ((Vector3 *)&local_118,(Vector3 *)&local_10c,(Vector3 *)&local_48,
                            *(float *)(lVar6 + 0x210) * local_48 +
                            (fVar8 + *(float *)(lVar6 + 0x214)) * local_44 +
                            local_40 * *(float *)(lVar6 + 0x218));
  *(undefined4 *)(param_1 + 4) = 0;
  *(float *)(param_1 + 8) = fVar7 * fVar8 + local_110;
  *(float *)param_1 = fVar8 * fVar9 + (float)local_118;
  if ((*(long *)(this + 0x70) != 0) && (*(char *)(*(long *)(this + 0x58) + 0x264) == '\0')) {
    Ogre::Camera::getCameraToViewportRay(local_1ec,fVar11,*(Ray **)(*(long *)(this + 0x20) + 0x10));
    local_98 = local_118;
    local_a8 = (float)local_10c * DAT_00fa8718 + (float)local_118;
    local_a4 = local_10c._4_4_ * DAT_00fa8718 + local_118._4_4_;
    local_90 = local_110;
    local_a0 = local_104 * DAT_00fa8718 + local_110;
    cVar2 = CLevel::rayCollision
                      (*(CLevel **)(*(long *)(this + 0x2b8) + 0x18),(Vector3 *)&local_98,
                       (Vector3 *)&local_a8,(Vector3 *)&local_d8,local_b8,local_3c,local_c8,false);
    if ((cVar2 != '\0') && (local_3c[0] != 100)) {
      if (DAT_00fa86e0 <
          SQRT((local_d8 - (float)local_98) * (local_d8 - (float)local_98) +
               (local_d4 - local_98._4_4_) * (local_d4 - local_98._4_4_) +
               (local_d0 - local_90) * (local_d0 - local_90))) {
        local_a4 = local_d4 - DAT_00fa871c;
        local_90 = local_d0;
        local_a8 = local_d8;
        local_a0 = local_d0;
        local_98 = CONCAT44(local_d4 + DAT_00fa871c,local_d8);
        cVar2 = CLevel::rayCollision
                          (*(CLevel **)(*(long *)(this + 0x2b8) + 0x18),(Vector3 *)&local_98,
                           (Vector3 *)&local_a8,(Vector3 *)&local_d8,local_b8,local_3c,local_c8,
                           false);
        if (((cVar2 != '\0') && (local_3c[0] != 100)) && (DAT_00fa86e8 < local_b4)) {
          fVar7 = local_d4 - *(float *)(*(long *)(this + 0x58) + 0x214);
          fVar9 = (float)(DAT_00fa8790 & (uint)fVar7);
          if ((fVar9 < DAT_00fa8720) && (!NAN(fVar9) && !NAN(DAT_00fa8720))) {
            Ogre::Camera::getCameraToViewportRay
                      (local_1ec,fVar11,*(Ray **)(*(long *)(this + 0x20) + 0x10));
            fVar8 = local_104;
            fVar9 = (float)local_10c;
            fVar11 = 0.0;
            if (param_2) {
              fVar11 = DAT_00fa8714;
            }
            fVar7 = (float)MATH::distanceToPlane
                                     ((Vector3 *)&local_118,(Vector3 *)&local_10c,
                                      (Vector3 *)&local_48,
                                      *(float *)(*(long *)(this + 0x58) + 0x214) + fVar7 + fVar11);
            *(undefined4 *)(param_1 + 4) = 0;
            *(float *)(param_1 + 8) = fVar8 * fVar7 + local_110;
            *(float *)param_1 = fVar7 * fVar9 + (float)local_118;
          }
        }
      }
    }
  }
  if ((char)uVar4 == '\0') {
    if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),
                 *(uint *)(this + 0x1e0));
      *(undefined8 *)(this + 0x1d8) = 0;
    }
    if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),
                 *(uint *)(this + 0x1f0));
      *(undefined8 *)(this + 0x1e8) = 0;
    }
  }
  return uVar4;
}



/* address=0057a900
   symbol=CGameClient::moveToMouse */

/* CGameClient::moveToMouse(bool) */

void CGameClient::moveToMouse(bool param_1)

{
  char cVar1;
  undefined7 in_register_00000039;
  CGameClient *this;
  undefined8 uVar2;
  float in_XMM1_Da;
  float local_18;
  float local_14;
  float local_10;
  float fVar3;

  this = (CGameClient *)CONCAT71(in_register_00000039,param_1);
  cVar1 = findWorldLocation(this,(Vector3 *)&local_18,*(bool *)(*(long *)(this + 0x58) + 0x266));
  if (cVar1 != '\0') {
    uVar2 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),true);
    fVar3 = (float)((ulong)uVar2 >> 0x20);
    if ((local_18 == (float)uVar2) && (!NAN(local_18) && !NAN((float)uVar2))) {
      if ((local_14 == fVar3) && (!NAN(local_14) && !NAN(fVar3))) {
        if ((local_10 == in_XMM1_Da) && (!NAN(local_10) && !NAN(in_XMM1_Da))) {
          CCharacter::setDestination
                    (*(CCharacter **)(this + 0x58),*(CLevel **)(this + 0x70),local_18,local_10);
          *(undefined4 *)(this + 0x80) = 0x3dcccccd;
          return;
        }
      }
    }
    if (*(float *)(this + 0x80) <= 0.0) {
      CCharacter::setDestination
                (*(CCharacter **)(this + 0x58),*(CLevel **)(this + 0x70),local_18,local_10);
      *(undefined4 *)(this + 0x80) = 0x3dcccccd;
      return;
    }
  }
  return;
}



/* address=0057a9f0
   symbol=CGameClient::clickLeft */

/* CGameClient::clickLeft() */

void CGameClient::clickLeft(void)

{
  int iVar1;
  long *plVar2;
  undefined8 *puVar3;
  char cVar4;
  uint uVar5;
  CItem *pCVar6;
  CGameClient *in_RDI;
  CCharacter *pCVar7;
  CCharacter *pCVar8;
  float fVar9;
  float in_XMM1_Da;

  cVar4 = getIsPaused(in_RDI);
  if (cVar4 != '\0') {
    return;
  }
  cVar4 = CCharacter::alive(*(CCharacter **)(in_RDI + 0x58));
  if (cVar4 == '\0') {
    return;
  }
  cVar4 = (**(code **)(**(long **)(in_RDI + 0x58) + 0x48))();
  if (cVar4 == '\0') {
    return;
  }
  iVar1 = *(int *)(*(long *)(in_RDI + 0x58) + 0x330);
  if (iVar1 == 0x22) {
    return;
  }
  if (iVar1 == 0x14) {
    return;
  }
  if (in_RDI[0x99] == (CGameClient)0x0) {
    *(undefined4 *)(*(long *)(in_RDI + 0x58) + 0x278) = 0x41200000;
  }
  if ((((*(long *)(in_RDI + 0x1d8) != 0) && (*(CCharacter **)(in_RDI + 0x1c8) != (CCharacter *)0x0))
      && (cVar4 = CCharacter::alive(*(CCharacter **)(in_RDI + 0x1c8)), cVar4 == '\0')) &&
     (*(CCharacter **)(in_RDI + 0x1d8) != *(CCharacter **)(in_RDI + 0x1c8))) {
    TSafePointer<CCharacter>::setObject
              ((TSafePointer<CCharacter> *)(in_RDI + 0x1c8),*(CCharacter **)(in_RDI + 0x1d8));
  }
  if (((*(CItem **)(in_RDI + 0x1e8) != (CItem *)0x0) && (*(long *)(in_RDI + 0x1f8) == 0)) &&
     ((*(long *)(in_RDI + 0x1c8) == 0 && (in_RDI[0x99] == (CGameClient)0x0)))) {
    TSafePointer<CItem>::setObject
              ((TSafePointer<CItem> *)(in_RDI + 0x1f8),*(CItem **)(in_RDI + 0x1e8));
  }
  if (((*(CCharacter **)(in_RDI + 0x1d8) != (CCharacter *)0x0) && (*(long *)(in_RDI + 0x1c8) == 0))
     && ((*(long *)(in_RDI + 0x1f8) == 0 && (in_RDI[0x99] == (CGameClient)0x0)))) {
    TSafePointer<CCharacter>::setObject
              ((TSafePointer<CCharacter> *)(in_RDI + 0x1c8),*(CCharacter **)(in_RDI + 0x1d8));
  }
  pCVar8 = *(CCharacter **)(in_RDI + 0x58);
  if ((pCVar8[0x4d0] != (CCharacter)0x0) || (pCVar8[0x4d1] != (CCharacter)0x0)) {
    if (pCVar8[0x266] == (CCharacter)0x0) {
      in_RDI[0x98] = (CGameClient)0x1;
    }
    pCVar8[0x4d0] = (CCharacter)0x0;
    *(undefined1 *)(*(long *)(in_RDI + 0x58) + 0x4d1) = 0;
    pCVar8 = *(CCharacter **)(in_RDI + 0x58);
  }
  cVar4 = CCharacter::performingSkillLoose(pCVar8);
  if (cVar4 != '\0') {
    return;
  }
  pCVar8 = *(CCharacter **)(in_RDI + 0x58);
  pCVar6 = *(CItem **)(pCVar8 + 0x350);
  pCVar7 = *(CCharacter **)(pCVar8 + 0x340);
  cVar4 = CCharacter::performingSkillLoose(pCVar8);
  if ((cVar4 == '\0') &&
     (cVar4 = CCharacter::performingAttackLoose(*(CCharacter **)(in_RDI + 0x58)), cVar4 == '\0')) {
    if (*(CItem **)(in_RDI + 0x1f8) != (CItem *)0x0) {
      CCharacter::setTargetItem(*(CCharacter **)(in_RDI + 0x58),*(CItem **)(in_RDI + 0x1f8));
    }
    if (*(CCharacter **)(in_RDI + 0x1c8) != (CCharacter *)0x0) {
      CCharacter::setTarget(*(CCharacter **)(in_RDI + 0x58),*(CCharacter **)(in_RDI + 0x1c8));
      goto LAB_0057ab47;
    }
  }
  else {
LAB_0057ab47:
    plVar2 = *(long **)(in_RDI + 0x1c8);
    if ((plVar2 != (long *)0x0) &&
       ((*(char *)((long)plVar2 + 0x81) == '\0' ||
        (cVar4 = (**(code **)(*plVar2 + 0x48))(), cVar4 == '\0')))) {
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(in_RDI + 0x1c8),(CCharacter *)0x0);
    }
  }
  if ((*(CBaseUnit **)(in_RDI + 0x1f8) == (CBaseUnit *)0x0) ||
     (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(in_RDI + 0x1f8),0x1d), cVar4 == '\0')) {
    if (*(CCharacter **)(in_RDI + 0x1c8) != (CCharacter *)0x0) {
      cVar4 = CCharacter::isEnemy(*(CCharacter **)(in_RDI + 0x58),*(CCharacter **)(in_RDI + 0x1c8));
      if (cVar4 != '\0') {
        cVar4 = CCharacter::performingAttackLoose(*(CCharacter **)(in_RDI + 0x58));
        if ((cVar4 == '\0') &&
           (cVar4 = CCharacter::inAttackRange(*(undefined8 *)(in_RDI + 0x58),0), cVar4 == '\0')) {
          if (pCVar7 != *(CCharacter **)(in_RDI + 0x1c8)) {
            CCharacter::stopPathing(*(CCharacter **)(in_RDI + 0x58));
            pCVar7 = *(CCharacter **)(in_RDI + 0x1c8);
          }
          CCharacter::setTarget(*(CCharacter **)(in_RDI + 0x58),pCVar7);
          goto LAB_0057ac82;
        }
        goto LAB_0057aba1;
      }
      if ((*(long *)(in_RDI + 0x1c8) != 0) && (cVar4 = CBaseUnit::ISA(), cVar4 != '\0')) {
        CCharacter::setTarget(*(CCharacter **)(in_RDI + 0x58),*(CCharacter **)(in_RDI + 0x1c8));
        (**(code **)(**(long **)(in_RDI + 0x58) + 0x348))(*(long **)(in_RDI + 0x58),9);
        CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x1c8),true);
        fVar9 = (float)CPositionableObject::getPosition
                                 (*(CPositionableObject **)(in_RDI + 0x1c8),true);
        CCharacter::setDestination
                  (*(CCharacter **)(in_RDI + 0x58),*(CLevel **)(in_RDI + 0x70),fVar9,in_XMM1_Da);
        return;
      }
    }
    plVar2 = *(long **)(in_RDI + 0x1f8);
    if (plVar2 == (long *)0x0) {
      if (in_RDI[0x99] == (CGameClient)0x0) {
        in_RDI[0x98] = (CGameClient)0x0;
        CCharacter::setTarget(*(CCharacter **)(in_RDI + 0x58),(CCharacter *)0x0);
        CCharacter::setTargetItem(*(CCharacter **)(in_RDI + 0x58),(CItem *)0x0);
        (**(code **)(**(long **)(in_RDI + 0x58) + 0x348))(*(long **)(in_RDI + 0x58),0);
      }
      if ((in_RDI[0x98] == (CGameClient)0x0) ||
         (*(char *)(*(long *)(in_RDI + 0x58) + 0x266) != '\0')) {
        moveToMouse(SUB81(in_RDI,0));
        return;
      }
    }
    else if (((char)plVar2[0x33] != '\0') &&
            (cVar4 = (**(code **)(*plVar2 + 0x48))(), cVar4 != '\0')) {
      pCVar8 = *(CCharacter **)(in_RDI + 0x58);
      uVar5 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(in_RDI + 0x50),KSETTINGS_KEYMAP_HOLDPOS);
      cVar4 = CKeyManager::keyHeld((CKeyManager *)(in_RDI + 0x2d0),uVar5);
      if (((cVar4 != '\0') &&
          (((puVar3 = *(undefined8 **)(*(long *)(in_RDI + 0x58) + 0x648),
            *(long *)(*(long *)(in_RDI + 0x58) + 0x650) - (long)puVar3 >> 3 != 0 &&
            (pCVar7 = (CCharacter *)*puVar3, pCVar7 != (CCharacter *)0x0)) &&
           (cVar4 = CCharacter::isPetNearDeath(pCVar7), cVar4 == '\0')))) &&
         (((cVar4 = CCharacter::alive(pCVar7), cVar4 != '\0' && (*(int *)(pCVar7 + 0x330) != 0x2a))
          && (*(int *)(pCVar7 + 0x330) != 0x29)))) {
        pCVar8 = (CCharacter *)0x0;
        puVar3 = *(undefined8 **)(*(long *)(in_RDI + 0x58) + 0x648);
        if (*(long *)(*(long *)(in_RDI + 0x58) + 0x650) - (long)puVar3 >> 3 != 0) {
          pCVar8 = (CCharacter *)*puVar3;
        }
      }
      if (pCVar6 != *(CItem **)(pCVar8 + 0x350)) {
        CCharacter::stopPathing(pCVar8);
      }
      CCharacter::setTargetItem(pCVar8,*(CItem **)(in_RDI + 0x1f8));
      (**(code **)(*(long *)pCVar8 + 0x348))(pCVar8,7);
      CCharacter::stopPathing(pCVar8);
                    /* WARNING: Could not recover jumptable at 0x0057ad9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)pCVar8 + 0x3c8))(0,pCVar8,*(undefined8 *)(in_RDI + 0x70));
      return;
    }
  }
  else {
    cVar4 = CCharacter::performingAttackLoose(*(CCharacter **)(in_RDI + 0x58));
    if ((cVar4 == '\0') &&
       (cVar4 = CCharacter::inAttackRange(*(undefined8 *)(in_RDI + 0x58),0), cVar4 == '\0')) {
      if (pCVar6 != *(CItem **)(in_RDI + 0x1f8)) {
        CCharacter::stopPathing(*(CCharacter **)(in_RDI + 0x58));
        pCVar6 = *(CItem **)(in_RDI + 0x1f8);
      }
      CCharacter::setTargetItem(*(CCharacter **)(in_RDI + 0x58),pCVar6);
LAB_0057ac82:
      (**(code **)(**(long **)(in_RDI + 0x58) + 0x348))(*(long **)(in_RDI + 0x58),4);
      (**(code **)(**(long **)(in_RDI + 0x58) + 0x3b8))
                (0,*(long **)(in_RDI + 0x58),*(undefined8 *)(in_RDI + 0x70));
      if (*(int *)(*(CCharacter **)(in_RDI + 0x58) + 0x330) == 3) {
        return;
      }
      cVar4 = CCharacter::performingSkill(*(CCharacter **)(in_RDI + 0x58));
      if (cVar4 != '\0') {
        return;
      }
      if (*(char *)(*(long *)(in_RDI + 0x58) + 0x264) != '\0') {
        return;
      }
      goto LAB_0057abdd;
    }
LAB_0057aba1:
    cVar4 = CCharacter::performingAttackLoose(*(CCharacter **)(in_RDI + 0x58));
    if (((cVar4 == '\0') && (*(int *)(*(CCharacter **)(in_RDI + 0x58) + 0x330) != 3)) &&
       (cVar4 = CCharacter::performingSkill(*(CCharacter **)(in_RDI + 0x58)), cVar4 == '\0')) {
      CCharacter::stopPathing(*(CCharacter **)(in_RDI + 0x58));
LAB_0057abdd:
      CCharacter::attack();
      return;
    }
  }
  return;
}



/* address=0057b0b0
   symbol=CGameClient::mouseOverCharacter */

/* CGameClient::mouseOverCharacter() */

void __thiscall CGameClient::mouseOverCharacter(CGameClient *this)

{
  TSafePointer *pTVar1;
  uint uVar2;
  CRunicCore *this_00;
  char cVar3;
  short sVar4;
  short sVar5;
  uint uVar6;
  undefined4 uVar7;
  Matrix3 *pMVar8;
  undefined4 *puVar9;
  undefined8 *puVar10;
  CRunicCore *this_01;
  CItem *pCVar11;
  long lVar12;
  float fVar13;
  float fVar14;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  Matrix4 local_a8 [8];
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined8 local_78;
  undefined8 local_70;
  undefined4 local_60;
  undefined4 local_54;
  undefined4 local_48;
  long local_38;
  long local_30;

  GetCursorPos((POINT *)&local_38);
  sVar4 = GetAsyncKeyState(1);
  sVar5 = GetAsyncKeyState(2);
  if ((this[0x99] != (CGameClient)0x0) && (-1 < sVar4)) {
    mouseEvent(this,0x202,1);
  }
  if ((this[0x9a] != (CGameClient)0x0) && (-1 < sVar5)) {
    mouseEvent(this,0x205,1);
  }
  uVar2 = *(uint *)(this + 0x94);
  fVar13 = DAT_00fa8700 / (float)*(uint *)(this + 0x90);
  uVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_RES_HEIGHT);
  lVar12 = (long)(int)((float)local_38 * fVar13);
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    cVar3 = CGameUI::rightCovered(*(CGameUI **)(this + 0x78));
    if (cVar3 == '\0') {
      if ((*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) &&
         (cVar3 = CGameUI::leftCovered(*(CGameUI **)(this + 0x78)), cVar3 != '\0')) {
        fVar13 = 0.0;
        if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
          fVar13 = (float)CGameUI::leftScreenEdge(*(CGameUI **)(this + 0x78));
        }
        lVar12 = (long)((float)(long)((float)lVar12 + DAT_00fa8704 * (fVar13 / (float)uVar6)) *
                       (DAT_00fa47fc / (DAT_00fa47fc - fVar13 / (float)uVar6)));
        if (lVar12 < 0) {
          TSafePointer<CCharacter>::setObject
                    ((TSafePointer<CCharacter> *)(this + 0x1d8),(CCharacter *)0x0);
          TSafePointer<CItem>::setObject((TSafePointer<CItem> *)(this + 0x1e8),(CItem *)0x0);
          return;
        }
      }
    }
    else {
      fVar13 = DAT_00fa4800;
      if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
        fVar13 = (float)CGameUI::rightScreenEdge(*(CGameUI **)(this + 0x78));
      }
      lVar12 = (long)((float)lVar12 * (DAT_00fa47fc / (fVar13 / (float)uVar6)));
      if (0x800 < lVar12) {
        if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
          CRunicCore::removeSafePointer
                    (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),
                     *(uint *)(this + 0x1e0));
          *(undefined8 *)(this + 0x1d8) = 0;
        }
        goto LAB_0057b55e;
      }
    }
  }
  pTVar1 = (TSafePointer *)(this + 0x1d8);
  fVar13 = ((float)lVar12 - DAT_00fa4800) * DAT_00fa4808;
  fVar14 = (float)((uint)((float)(int)((float)local_30 * (DAT_00fa8708 / (float)uVar2)) -
                         DAT_00fa4804) ^ DAT_00fa8780) / DAT_00fa4804;
  pMVar8 = (Matrix3 *)Ogre::Camera::getOrientation();
  Ogre::Quaternion::ToRotationMatrix(pMVar8);
  local_78 = DAT_01423ff0;
  local_70 = DAT_01423ff8;
  _local_a0 = CONCAT44((int)((ulong)DAT_01423fc8 >> 0x20),local_60);
  _local_90 = CONCAT44((int)((ulong)DAT_01423fd8 >> 0x20),local_54);
  _local_80 = CONCAT44((int)((ulong)DAT_01423fe8 >> 0x20),local_48);
  puVar9 = (undefined4 *)Ogre::Camera::getPosition();
  _local_a0 = CONCAT44(*puVar9,local_a0);
  _local_90 = CONCAT44(puVar9[1],local_90);
  _local_80 = CONCAT44(puVar9[2],local_80);
  Ogre::Matrix4::inverse();
  puVar10 = (undefined8 *)(**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x2d8))();
  local_e8 = *puVar10;
  local_e0 = puVar10[1];
  local_d8 = puVar10[2];
  local_d0 = puVar10[3];
  local_c8 = puVar10[4];
  local_c0 = puVar10[5];
  local_b8 = puVar10[6];
  local_b0 = puVar10[7];
  this_01 = (CRunicCore *)
            CLevel::findCharacterAtScreenCoordinates
                      (*(CLevel **)(this + 0x70),local_a8,(Matrix4 *)&local_e8,fVar13,fVar14,
                       *(CCharacter **)(this + 0x58));
  this_00 = *(CRunicCore **)(this + 0x1d8);
  if (this_01 != this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,pTVar1,*(uint *)(this + 0x1e0));
    }
    *(undefined8 *)(this + 0x1d8) = 0;
    if (this_01 != (CRunicCore *)0x0) {
      uVar7 = CRunicCore::addSafePointer(this_01,pTVar1);
      *(undefined4 *)(this + 0x1e0) = uVar7;
    }
    *(CRunicCore **)(this + 0x1d8) = this_01;
  }
  if (this_01 == (CRunicCore *)0x0) goto LAB_0057b4fd;
  if (this_01[0x81] != (CRunicCore)0x0) {
    cVar3 = (**(code **)(*(long *)this_01 + 0x48))(this_01);
    if (cVar3 != '\0') {
      if (*(long *)(this + 0x1d8) != 0) {
LAB_0057b55e:
        if (*(CRunicCore **)(this + 0x1e8) == (CRunicCore *)0x0) {
          return;
        }
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),
                   *(uint *)(this + 0x1f0));
        *(undefined8 *)(this + 0x1e8) = 0;
        return;
      }
      goto LAB_0057b4fd;
    }
    this_01 = *(CRunicCore **)(this + 0x1d8);
    if (this_01 == (CRunicCore *)0x0) goto LAB_0057b4fd;
  }
  CRunicCore::removeSafePointer(this_01,pTVar1,*(uint *)(this + 0x1e0));
  *(undefined8 *)(this + 0x1d8) = 0;
LAB_0057b4fd:
  pCVar11 = (CItem *)CLevel::findItemAtScreenCoordinates
                               (*(CLevel **)(this + 0x70),local_a8,(Matrix4 *)&local_e8,fVar13,
                                fVar14);
  TSafePointer<CItem>::setObject((TSafePointer<CItem> *)(this + 0x1e8),pCVar11);
  return;
}



/* address=0057b6a0
   symbol=CGameClient::clickRight */

/* CGameClient::clickRight(long long, bool, bool) */

uint __thiscall
CGameClient::clickRight(CGameClient *this,longlong param_1,bool param_2,bool param_3)

{
  CRunicCore *pCVar1;
  CRunicCore *this_00;
  long *plVar2;
  long lVar3;
  CSkillManager *this_01;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  CSkill *pCVar8;
  long lVar9;
  undefined3 in_register_00000009;
  bool bVar10;
  CCharacter *pCVar11;
  CBaseUnit *pCVar12;
  longlong lVar13;
  ulong uVar14;
  uint *puVar15;
  float local_58 [2];
  float local_50;
  Vector3 local_48 [24];

  cVar4 = CCharacter::alive(*(CCharacter **)(this + 0x58));
  if (cVar4 == '\0') {
    return 0;
  }
  cVar4 = (**(code **)(**(long **)(this + 0x58) + 0x48))();
  if (cVar4 == '\0') {
    return 0;
  }
  if (!param_2) {
    *(undefined4 *)(*(long *)(this + 0x58) + 0x278) = 0x41200000;
    CCharacter::setTarget(*(CCharacter **)(this + 0x58),*(CCharacter **)(this + 0x1c8));
    CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),*(CItem **)(this + 0x1f8));
  }
  if ((*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8) == (CSkillManager *)0x0) ||
     ((pCVar8 = (CSkill *)
                CSkillManager::getSkillByGuid
                          (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),param_1),
      pCVar8 == (CSkill *)0x0 &&
      (pCVar8 = (CSkill *)
                CSkillManager::getSkillByGuid
                          (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),
                           *(longlong *)(*(long *)(this + 0x58) + 0x3b0)), pCVar8 == (CSkill *)0x0))
     )) {
LAB_0057bb30:
    cVar4 = findWorldLocation(this,local_48,true);
    if (cVar4 == '\0') {
      return 0;
    }
  }
  else {
    iVar5 = CSkill::getTargetType(pCVar8);
    if ((iVar5 == 7) || (iVar5 = CSkill::getTargetType(pCVar8), iVar5 == 8)) {
      if (param_2) {
        return 0;
      }
      iVar5 = *(int *)(*(long *)(this + 0x78) + 0x12fc);
      if ((iVar5 == 4) || (bVar10 = false, iVar5 == 3)) {
        *(undefined8 *)(*(long *)(this + 0x78) + 0xb0) = 0xffffffffffffffff;
        CGameUI::setCursorState(*(CGameUI **)(this + 0x78),0);
        return 0;
      }
    }
    else {
      bVar10 = true;
      if (pCVar8 == (CSkill *)0x0) goto LAB_0057bb30;
    }
    iVar5 = CSkill::getTargetType(pCVar8);
    if ((((iVar5 != 3) && (iVar5 = CSkill::getTargetType(pCVar8), iVar5 != 9)) &&
        (iVar5 = CSkill::getTargetType(pCVar8), iVar5 != 10)) && (bVar10)) goto LAB_0057bb30;
  }
  if (((*(long *)(this + 0x1d8) != 0) && (*(CCharacter **)(this + 0x1c8) != (CCharacter *)0x0)) &&
     (cVar4 = CCharacter::alive(*(CCharacter **)(this + 0x1c8)), cVar4 == '\0')) {
    pCVar1 = *(CRunicCore **)(this + 0x1d8);
    this_00 = *(CRunicCore **)(this + 0x1c8);
    if (pCVar1 != this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (this_00,(TSafePointer *)(this + 0x1c8),*(uint *)(this + 0x1d0));
      }
      *(undefined8 *)(this + 0x1c8) = 0;
      if (pCVar1 != (CRunicCore *)0x0) {
        uVar6 = CRunicCore::addSafePointer(pCVar1,(TSafePointer *)(this + 0x1c8));
        *(undefined4 *)(this + 0x1d0) = uVar6;
      }
      *(CRunicCore **)(this + 0x1c8) = pCVar1;
    }
  }
  pCVar1 = *(CRunicCore **)(this + 0x1e8);
  if (((pCVar1 != (CRunicCore *)0x0) && (*(long *)(this + 0x1f8) == 0)) &&
     ((*(long *)(this + 0x1c8) == 0 &&
      ((this[0x99] == (CGameClient)0x0 && (this[0x9a] == (CGameClient)0x0)))))) {
    *(undefined8 *)(this + 0x1f8) = 0;
    uVar6 = CRunicCore::addSafePointer(pCVar1,(TSafePointer *)(this + 0x1f8));
    *(CRunicCore **)(this + 0x1f8) = pCVar1;
    *(undefined4 *)(this + 0x200) = uVar6;
  }
  if ((((*(long *)(this + 0x1d8) != 0) && (*(long *)(this + 0x1c8) == 0)) &&
      (*(long *)(this + 0x1f8) == 0)) &&
     ((this[0x99] == (CGameClient)0x0 && (this[0x9a] == (CGameClient)0x0)))) {
    puVar15 = &KSkillSlotsKeys;
    uVar14 = 0;
    do {
      if (*(long *)(*(long *)(this + 0x58) + (uVar14 + 0x116) * 8) != -1) {
        uVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),*puVar15);
        cVar4 = CKeyManager::keyHeld((CKeyManager *)(this + 0x2d0),uVar7);
        if (cVar4 != '\0') {
          this_01 = *(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8);
          if (this_01 != (CSkillManager *)0x0) {
            lVar9 = CSkillManager::getSkillByGuid
                              (this_01,*(longlong *)(*(long *)(this + 0x58) + (uVar14 + 0x116) * 8))
            ;
            if ((lVar9 == *(long *)(*(CCharacter **)(this + 0x58) + 0x398)) &&
               (cVar4 = CCharacter::performingSkillLoose(*(CCharacter **)(this + 0x58)),
               cVar4 != '\0')) goto LAB_0057b87e;
          }
          break;
        }
      }
      uVar7 = (int)uVar14 + 1;
      uVar14 = (ulong)uVar7;
      puVar15 = puVar15 + 1;
    } while (uVar7 != 10);
    if (*(CCharacter **)(this + 0x1d8) != *(CCharacter **)(this + 0x1c8)) {
      TSafePointer<CCharacter>::setObject
                ((TSafePointer<CCharacter> *)(this + 0x1c8),*(CCharacter **)(this + 0x1d8));
    }
  }
LAB_0057b87e:
  pCVar11 = *(CCharacter **)(this + 0x58);
  if ((pCVar11[0x4d0] != (CCharacter)0x0) || (pCVar11[0x4d1] != (CCharacter)0x0)) {
    if (pCVar11[0x266] == (CCharacter)0x0) {
      this[0x98] = (CGameClient)0x1;
    }
    pCVar11[0x4d1] = (CCharacter)0x0;
    *(undefined1 *)(*(long *)(this + 0x58) + 0x4d0) = 0;
    pCVar11 = *(CCharacter **)(this + 0x58);
  }
  cVar4 = CCharacter::performingAttackLoose(pCVar11);
  if (cVar4 != '\0') {
    return 0;
  }
  if (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8) != (CSkillManager *)0x0) {
    pCVar8 = (CSkill *)
             CSkillManager::getSkillByGuid
                       (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),param_1);
    if (pCVar8 == (CSkill *)0x0) {
      param_1 = *(longlong *)(*(long *)(this + 0x58) + 0x3b0);
      pCVar8 = (CSkill *)
               CSkillManager::getSkillByGuid
                         (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),param_1);
      if (pCVar8 != (CSkill *)0x0) goto LAB_0057b8e6;
    }
    else {
LAB_0057b8e6:
      cVar4 = CGameUI::equipmentTooltipVisible(*(CGameUI **)(this + 0x78));
      if (((cVar4 == '\0') ||
          (cVar4 = CMouseManager::buttonHeld((CMouseManager *)(this + 0xfe8),1), cVar4 == '\0')) &&
         ((iVar5 = CSkill::getTargetType(pCVar8), iVar5 == 7 ||
          (iVar5 = CSkill::getTargetType(pCVar8), iVar5 == 8)))) {
        CGameUI::setCursorState(*(CGameUI **)(this + 0x78),4);
        *(longlong *)(*(long *)(this + 0x78) + 0xb0) = param_1;
        CGameUI::flushInput(*(CGameUI **)(this + 0x78));
        CGameUI::setRightButtonPressed(*(CGameUI **)(this + 0x78));
        return 1;
      }
    }
    cVar4 = getIsPaused(this);
    if (((cVar4 != '\0') && (pCVar8 != (CSkill *)0x0)) &&
       (iVar5 = CSkill::getAnimationIndex(pCVar8), iVar5 != -1)) {
      return 0;
    }
  }
  cVar4 = getIsPaused(this);
  if (cVar4 == '\0') {
LAB_0057b968:
    lVar9 = *(long *)(*(CCharacter **)(this + 0x58) + 0x398);
    if ((lVar9 != 0) && (*(char *)(lVar9 + 0x68) != '\0')) {
      cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
      if (cVar4 != '\0') {
        moveToMouse(SUB81(this,0));
        return 1;
      }
      cVar4 = CCharacter::castSkill(*(longlong *)(this + 0x58));
      if ((cVar4 == '\0') && (plVar2 = *(long **)(this + 0x58), (int)plVar2[0x66] != 0xd)) {
        (**(code **)(*plVar2 + 0x348))(plVar2,2);
      }
    }
  }
  else if (*(CSkill **)(*(long *)(this + 0x58) + 0x398) != (CSkill *)0x0) {
    iVar5 = CSkill::getAnimationIndex(*(CSkill **)(*(long *)(this + 0x58) + 0x398));
    if (iVar5 != -1) {
      return 0;
    }
    goto LAB_0057b968;
  }
  if (param_3) {
    pCVar12 = *(CBaseUnit **)(this + 0x1f8);
    if (pCVar12 == (CBaseUnit *)0x0) {
      pCVar11 = *(CCharacter **)(this + 0x1c8);
      if (pCVar11 == (CCharacter *)0x0) {
        return 0;
      }
LAB_0057b9e1:
      cVar4 = CCharacter::isEnemy(*(CCharacter **)(this + 0x58),pCVar11);
      if (cVar4 == '\0') {
        return 0;
      }
      pCVar12 = *(CBaseUnit **)(this + 0x1f8);
    }
    else {
      pCVar11 = *(CCharacter **)(this + 0x1c8);
      if (pCVar11 != (CCharacter *)0x0) goto LAB_0057b9e1;
    }
    if ((pCVar12 != (CBaseUnit *)0x0) && (cVar4 = CBaseUnit::ISA(pCVar12,0x1d), cVar4 == '\0')) {
      return 0;
    }
  }
  pCVar11 = *(CCharacter **)(this + 0x58);
  lVar9 = *(long *)(pCVar11 + 0x350);
  lVar3 = *(long *)(pCVar11 + 0x340);
  cVar4 = CCharacter::performingSkillLoose(pCVar11);
  if ((cVar4 == '\0') &&
     (cVar4 = CCharacter::performingAttackLoose(*(CCharacter **)(this + 0x58)), cVar4 == '\0')) {
    if (*(CItem **)(this + 0x1f8) != (CItem *)0x0) {
      CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),*(CItem **)(this + 0x1f8));
    }
    if (*(CCharacter **)(this + 0x1c8) != (CCharacter *)0x0) {
      CCharacter::setTarget(*(CCharacter **)(this + 0x58),*(CCharacter **)(this + 0x1c8));
    }
  }
  bVar10 = SUB81(param_1,0);
  if ((*(CBaseUnit **)(this + 0x1f8) == (CBaseUnit *)0x0) ||
     (cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x1f8),0x1d), cVar4 == '\0')) {
    if ((*(CCharacter **)(this + 0x1c8) == (CCharacter *)0x0) ||
       (cVar4 = CCharacter::isEnemy(*(CCharacter **)(this + 0x58),*(CCharacter **)(this + 0x1c8)),
       cVar4 == '\0')) {
      if (!param_2) {
        this[0x98] = (CGameClient)0x0;
        CCharacter::setTarget(*(CCharacter **)(this + 0x58),(CCharacter *)0x0);
        CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),(CItem *)0x0);
        cVar4 = CCharacter::performingSkillLoose(*(CCharacter **)(this + 0x58));
        if (cVar4 == '\0') {
          (**(code **)(**(long **)(this + 0x58) + 0x348))(*(long **)(this + 0x58),0);
        }
      }
      findWorldLocation(this,(Vector3 *)local_58,true);
      CCharacter::setTarget(*(CCharacter **)(this + 0x58),(CCharacter *)0x0);
      CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),(CItem *)0x0);
      CCharacter::setTargetDirection(*(CCharacter **)(this + 0x58),local_58[0],local_50);
      CCharacter::castSkill(*(longlong *)(this + 0x58));
      cVar4 = CCharacter::castSkill(*(longlong *)(this + 0x58));
      if (cVar4 != '\0') {
        return 1;
      }
      if (*(int *)(*(long *)(this + 0x58) + 0x330) == 0xd) {
        return 1;
      }
      return CONCAT31(in_register_00000009,param_3) ^ 1;
    }
    if (lVar3 != *(long *)(this + 0x1c8)) {
      CCharacter::stopPathing(*(CCharacter **)(this + 0x58));
    }
    cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
    if ((cVar4 == '\0') &&
       (iVar5 = CCharacter::inSkillRange(*(longlong *)(this + 0x58),bVar10), iVar5 != 0)) {
      CCharacter::setTarget(*(CCharacter **)(this + 0x58),*(CCharacter **)(this + 0x1c8));
      (**(code **)(**(long **)(this + 0x58) + 0x348))(*(long **)(this + 0x58),0xf);
      (**(code **)(**(long **)(this + 0x58) + 0x3c0))
                (0,*(long **)(this + 0x58),*(undefined8 *)(this + 0x70),param_1);
      cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
      if (cVar4 != '\0') {
        return 1;
      }
      iVar5 = CCharacter::inSkillRange(*(longlong *)(this + 0x58),bVar10);
      if (iVar5 == 0) {
        return 1;
      }
      if (*(char *)(*(long *)(this + 0x58) + 0x264) != '\0') {
        return 1;
      }
      cVar4 = CCharacter::castSkill(*(long *)(this + 0x58));
      if (cVar4 == '\0') {
        if (param_3) {
          return 0;
        }
        (**(code **)(**(long **)(this + 0x58) + 0x348))(*(long **)(this + 0x58),2);
        return 1;
      }
      return 1;
    }
    cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
    if (cVar4 != '\0') {
      return 1;
    }
    lVar13 = *(longlong *)(this + 0x58);
  }
  else {
    if (lVar9 != *(long *)(this + 0x1f8)) {
      CCharacter::stopPathing(*(CCharacter **)(this + 0x58));
    }
    cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
    if ((cVar4 != '\0') ||
       (iVar5 = CCharacter::inSkillRange(*(longlong *)(this + 0x58),bVar10), iVar5 == 0)) {
      cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
      if (cVar4 != '\0') {
        return 1;
      }
      cVar4 = CCharacter::castSkill(*(longlong *)(this + 0x58));
      goto joined_r0x0057bd9a;
    }
    CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),*(CItem **)(this + 0x1f8));
    (**(code **)(**(long **)(this + 0x58) + 0x348))(*(long **)(this + 0x58),0xf);
    (**(code **)(**(long **)(this + 0x58) + 0x3c0))
              (0,*(long **)(this + 0x58),*(undefined8 *)(this + 0x70),param_1);
    cVar4 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
    if (cVar4 != '\0') {
      return 1;
    }
    iVar5 = CCharacter::inSkillRange(*(longlong *)(this + 0x58),bVar10);
    if (iVar5 == 0) {
      return 1;
    }
    lVar13 = *(longlong *)(this + 0x58);
    if (*(char *)(lVar13 + 0x264) != '\0') {
      return 1;
    }
  }
  cVar4 = CCharacter::castSkill(lVar13);
joined_r0x0057bd9a:
  if ((cVar4 == '\0') && (plVar2 = *(long **)(this + 0x58), (int)plVar2[0x66] != 0xd)) {
    if (param_3) {
      return 0;
    }
    (**(code **)(*plVar2 + 0x348))(plVar2,2);
    return 1;
  }
  return 1;
}



/* address=0057c060
   symbol=CGameClient::processIngameInput */

/* CGameClient::processIngameInput(void*, float, bool) */

undefined8 __thiscall
CGameClient::processIngameInput(CGameClient *this,void *param_1,float param_2,bool param_3)

{
  CMouseManager *this_00;
  CKeyManager *pCVar1;
  TSafePointer<CCharacter> *this_01;
  TSafePointer<CItem> *this_02;
  char cVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  CGameUI *pCVar10;
  long lVar11;
  long *plVar12;
  CSkill *this_03;
  ulong uVar13;
  CCharacter *this_04;
  uint *puVar14;
  bool bVar15;
  float fVar16;
  uint *local_58;
  float local_48 [2];
  float local_40;

  if (*(CGameUI **)(this + 0x78) == (CGameUI *)0x0) {
    return 0;
  }
  cVar2 = CGameUI::isCinematicMenuOpen(*(CGameUI **)(this + 0x78));
  if ((cVar2 == '\0') &&
     ((((*(long **)(this + 0x58) == (long *)0x0 ||
        (cVar2 = (**(code **)(**(long **)(this + 0x58) + 0x48))(), cVar2 != '\0')) &&
       (cVar2 = CKeyManager::keyPressed((CKeyManager *)(this + 0x2d0),0x1b), cVar2 != '\0')) &&
      (cVar2 = CGameUI::getUIIsInCinematic(*(CGameUI **)(this + 0x78)), cVar2 == '\0')))) {
    pCVar10 = *(CGameUI **)(this + 0x78);
    if (pCVar10[0x1999] == (CGameUI)0x0) {
      cVar2 = CGameUI::getConsoleIsOpen(pCVar10);
      if (cVar2 == '\0') {
        cVar2 = CGameUI::eitherCoveredPartial(*(CGameUI **)(this + 0x78));
        if (cVar2 == '\0') {
          cVar2 = CGameUI::getDieMenuIsOpen(*(CGameUI **)(this + 0x78));
          if (cVar2 == '\0') {
            CGameUI::closeAll(*(CGameUI **)(this + 0x78));
            CGameUI::toggleOptions(*(CGameUI **)(this + 0x78));
          }
        }
        else {
          CGameUI::closeAll(*(CGameUI **)(this + 0x78));
        }
      }
      else {
        CGameUI::toggleConsole(*(CGameUI **)(this + 0x78));
      }
    }
    else {
      CGameUI::togglePause(pCVar10);
    }
  }
  cVar3 = '\x01';
  cVar2 = getIsPaused(this);
  pCVar10 = (CGameUI *)0x0;
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    cVar3 = CGameUI::processInput(*(CGameUI **)(this + 0x78),this,param_1,param_2,param_3);
    pCVar10 = *(CGameUI **)(this + 0x78);
  }
  cVar4 = CGameUI::getUIIsInCinematic(pCVar10);
  if (cVar4 != '\0') {
    CMouseManager::flushAll((CMouseManager *)(this + 0xfe8));
    this[0x99] = (CGameClient)0x0;
    this[0x9a] = (CGameClient)0x0;
    this[0x98] = (CGameClient)0x1;
    if (*(CCharacter **)(this + 0x58) == (CCharacter *)0x0) {
      return 1;
    }
    cVar2 = CCharacter::performingSkill(*(CCharacter **)(this + 0x58));
    if ((cVar2 == '\0') &&
       (cVar2 = CCharacter::performingAttack(*(CCharacter **)(this + 0x58)), cVar2 == '\0')) {
      return 1;
    }
    (**(code **)(**(long **)(this + 0x58) + 0x348))(*(long **)(this + 0x58),2);
    return 1;
  }
  this_00 = (CMouseManager *)(this + 0xfe8);
  if (cVar3 == '\0') {
    cVar4 = CMouseManager::buttonHeld(this_00,0);
    if (cVar4 != '\0') {
      this[0x99] = (CGameClient)0x1;
    }
    cVar4 = CMouseManager::buttonHeld(this_00,1);
    if (cVar4 != '\0') {
      this[0x9a] = (CGameClient)0x1;
    }
    this[0x98] = (CGameClient)0x1;
    CMouseManager::flushAll(this_00);
  }
  CMouseManager::update(this_00);
  if ((cVar2 != '\0') ||
     ((*(long **)(this + 0x58) != (long *)0x0 &&
      (cVar4 = (**(code **)(**(long **)(this + 0x58) + 0x48))(), cVar4 == '\0')))) {
    plVar12 = *(long **)(*(CGameUI **)(this + 0x78) + 0x58);
    if (plVar12 == (long *)0x0) {
      lVar11 = CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
      if (lVar11 != 0) {
        plVar12 = (long *)CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
        (**(code **)(*plVar12 + 0x208))(plVar12);
      }
    }
    else {
      (**(code **)(*plVar12 + 0x208))();
    }
    if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),
                 *(uint *)(this + 0x1f0));
      *(undefined8 *)(this + 0x1e8) = 0;
    }
    if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),
                 *(uint *)(this + 0x1e0));
      *(undefined8 *)(this + 0x1d8) = 0;
    }
    CGameUI::setMouseOverItem(*(CGameUI **)(this + 0x78),(CItem *)0x0,false);
    lVar11 = *(long *)(this + 0x78);
    if (*(CRunicCore **)(lVar11 + 0x58) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar11 + 0x58),(TSafePointer *)(lVar11 + 0x58),
                 *(uint *)(lVar11 + 0x60));
      *(undefined8 *)(lVar11 + 0x58) = 0;
    }
  }
  if ((((cVar3 != '\0') ||
       ((*(long *)(this + 0x58) != 0 && (*(int *)(*(long *)(this + 0x58) + 0x330) == 0x21)))) &&
      ((*(void **)(this + 0x20) == (void *)0x0 ||
       (cVar4 = CCameraControl::processInput
                          (*(void **)(this + 0x20),param_1,*(CKeyManager **)(this + 0x50),
                           (CMouseManager *)(this + 0x2d0),param_2,SUB81(this_00,0)), cVar4 != '\0')
       ))) && ((cVar3 != '\0' &&
               ((*(CGameUI **)(this + 0x78) == (CGameUI *)0x0 ||
                (cVar3 = CGameUI::modalDialogOpen(*(CGameUI **)(this + 0x78)), cVar3 == '\0')))))) {
    if ((param_3) &&
       (((*(CCharacter **)(this + 0x58) != (CCharacter *)0x0 &&
         (cVar3 = CCharacter::alive(*(CCharacter **)(this + 0x58)), cVar3 != '\0')) &&
        (cVar3 = (**(code **)(**(long **)(this + 0x58) + 0x48))(), cVar3 != '\0')))) {
      mouseOverCharacter(this);
      if (DAT_00fa47f8 < *(float *)(this + 0x80)) {
        *(float *)(this + 0x80) = *(float *)(this + 0x80) - param_2;
      }
      if (*(long *)(this + 0x58) != 0) {
        pCVar1 = (CKeyManager *)(this + 0x2d0);
        if (cVar2 == '\0') {
          uVar9 = CDynamicPropertyFile::GetInt
                            (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_KEYMAP_HOLDPOS);
          cVar2 = CKeyManager::keyHeld(pCVar1,uVar9);
          if (cVar2 == '\0') {
            *(undefined1 *)(*(long *)(this + 0x58) + 0x266) = 0;
          }
          else {
            *(undefined1 *)(*(long *)(this + 0x58) + 0x266) = 1;
            findWorldLocation(this,(Vector3 *)local_48,true);
            CCharacter::setTargetDirection(*(CCharacter **)(this + 0x58),local_48[0],local_40);
          }
        }
        cVar2 = CMouseManager::buttonPressed(this_00,0);
        if ((cVar2 != '\0') || (cVar2 = CMouseManager::buttonPressed(this_00,1), cVar2 != '\0')) {
          if (this[0x99] == (CGameClient)0x0) {
            *(undefined4 *)(this + 0x80) = 0;
            *(undefined4 *)(*(long *)(this + 0x58) + 0x278) = 0x41200000;
          }
          this_04 = *(CCharacter **)(this + 0x58);
          goto LAB_0057c557;
        }
        this_04 = *(CCharacter **)(this + 0x58);
        if (*(long *)(this_04 + 0x398) == 0) goto LAB_0057c557;
        cVar2 = CCharacter::performingSkill(this_04);
        if (cVar2 == '\0') {
          this_04 = *(CCharacter **)(this + 0x58);
          goto LAB_0057c557;
        }
        cVar2 = CMouseManager::buttonHeld(this_00,1);
        if (cVar2 == '\0') {
          this_04 = *(CCharacter **)(this + 0x58);
LAB_0057c98d:
          bVar15 = true;
        }
        else {
          this_04 = *(CCharacter **)(this + 0x58);
          if (*(long *)(*(long *)(this_04 + 0x398) + 0x150) != *(long *)(this_04 + 0x3b0))
          goto LAB_0057c98d;
          bVar15 = false;
        }
        puVar14 = &KSkillSlotsKeys;
        uVar9 = 0;
        do {
          if (*(long *)(this_04 + ((ulong)uVar9 + 0x116) * 8) != -1) {
            uVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),*puVar14);
            cVar2 = CKeyManager::keyHeld(pCVar1,uVar6);
            if (cVar2 != '\0') {
              this_04 = *(CCharacter **)(this + 0x58);
              if (*(CSkillManager **)(this_04 + 0x1c8) != (CSkillManager *)0x0) {
                lVar11 = CSkillManager::getSkillByGuid
                                   (*(CSkillManager **)(this_04 + 0x1c8),
                                    *(longlong *)(this_04 + ((ulong)uVar9 + 0x116) * 8));
                this_04 = *(CCharacter **)(this + 0x58);
                if (lVar11 == *(long *)(this_04 + 0x398)) goto LAB_0057c557;
              }
              break;
            }
            this_04 = *(CCharacter **)(this + 0x58);
          }
          uVar9 = uVar9 + 1;
          puVar14 = puVar14 + 1;
        } while (uVar9 != 10);
        if (bVar15) {
          CPlayer::attemptToStopPlayerSkill((CPlayer *)this_04,(bool)((byte)this[0x99] ^ 1));
          this_04 = *(CCharacter **)(this + 0x58);
        }
LAB_0057c557:
        this_01 = (TSafePointer<CCharacter> *)(this + 0x1c8);
        this_02 = (TSafePointer<CItem> *)(this + 0x1f8);
        local_58 = &KSkillSlotsKeys;
        uVar9 = 0;
        do {
          uVar13 = (ulong)uVar9;
          if (*(long *)(this_04 + (uVar13 + 0x116) * 8) == -1) {
LAB_0057c638:
            if (*(long *)(this_04 + uVar13 * 8 + 0x900) != -1) {
              uVar6 = CDynamicPropertyFile::GetInt
                                (*(CDynamicPropertyFile **)(this + 0x50),*local_58);
              cVar2 = CKeyManager::keyPressed(pCVar1,uVar6);
              if (cVar2 != '\0') {
                CGameUI::activateItemSlot(*(CGameUI **)(this + 0x78),uVar9,true);
                goto LAB_0057c672;
              }
            }
          }
          else {
            lVar11 = CSkillManager::getSkillByGuid
                               (*(CSkillManager **)(this_04 + 0x1c8),
                                *(long *)(this_04 + (uVar13 + 0x116) * 8));
            if (lVar11 == 0) {
              this_04 = *(CCharacter **)(this + 0x58);
              goto LAB_0057c638;
            }
            uVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),*local_58);
            cVar2 = CKeyManager::keyHeld(pCVar1,uVar6);
            if (cVar2 != '\0') {
              uVar9 = CDynamicPropertyFile::GetInt
                                (*(CDynamicPropertyFile **)(this + 0x50),(&KSkillSlotsKeys)[uVar13])
              ;
              bVar5 = CKeyManager::keyPressed(pCVar1,uVar9);
              clickRight(this,*(longlong *)(*(long *)(this + 0x58) + (uVar13 + 0x116) * 8),
                         (bool)(bVar5 ^ 1),false);
              goto LAB_0057c672;
            }
            uVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x50),*local_58);
            cVar2 = CKeyManager::keyReleased(pCVar1,uVar6);
            if ((cVar2 != '\0') && (this[0x9a] == (CGameClient)0x0)) {
              TSafePointer<CCharacter>::setObject(this_01,(CCharacter *)0x0);
              TSafePointer<CItem>::setObject(this_02,(CItem *)0x0);
            }
          }
          uVar9 = uVar9 + 1;
          local_58 = local_58 + 1;
          if (uVar9 == 10) goto LAB_0057c7c0;
          this_04 = *(CCharacter **)(this + 0x58);
        } while( true );
      }
    }
    else {
      if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),
                   *(uint *)(this + 0x1e0));
        *(undefined8 *)(this + 0x1d8) = 0;
      }
      if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),
                   *(uint *)(this + 0x1f0));
        *(undefined8 *)(this + 0x1e8) = 0;
      }
    }
  }
  goto LAB_0057c1c3;
LAB_0057c7c0:
  cVar2 = CMouseManager::buttonHeld(this_00);
  if (cVar2 == '\0') {
    if (this[0x9a] != (CGameClient)0x0) {
      TSafePointer<CCharacter>::setObject(this_01,(CCharacter *)0x0);
      TSafePointer<CItem>::setObject(this_02,(CItem *)0x0);
    }
    this[0x9a] = (CGameClient)0x0;
  }
  else {
    clickRight(this,0xffffffff,(bool)this[0x9a],false);
    this[0x9a] = (CGameClient)0x1;
  }
LAB_0057c672:
  cVar2 = CMouseManager::buttonHeld(this_00);
  if (cVar2 == '\0') {
    if (this[0x98] != (CGameClient)0x0) {
      this[0x98] = (CGameClient)0x0;
    }
    if (this[0x99] != (CGameClient)0x0) {
      TSafePointer<CCharacter>::setObject(this_01,(CCharacter *)0x0);
      TSafePointer<CItem>::setObject(this_02,(CItem *)0x0);
    }
    this[0x99] = (CGameClient)0x0;
  }
  else {
    cVar2 = CMouseManager::buttonHeld(this_00);
    if (cVar2 == '\0') {
      lVar11 = *(long *)(*(long *)(this + 0x58) + 0x3c0);
      if (((lVar11 != -1) &&
          (this_03 = (CSkill *)
                     CSkillManager::getSkillByGuid
                               (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),lVar11),
          this_03 != (CSkill *)0x0)) &&
         (cVar2 = CSkillManager::getSkillIsCooling
                            (*(CSkillManager **)(*(long *)(this + 0x58) + 0x1c8),this_03),
         cVar2 == '\0')) {
        iVar7 = CCharacter::mana(*(CCharacter **)(this + 0x58));
        iVar8 = CSkill::getManaCost(this_03);
        if (iVar8 <= iVar7) {
          iVar7 = CCharacter::mana(*(CCharacter **)(this + 0x58));
          iVar8 = CSkill::getManaCostOT(this_03);
          if (iVar8 <= iVar7) {
            uVar9 = CDynamicPropertyFile::GetInt
                              (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_KEYMAP_HOLDPOS);
            cVar2 = CKeyManager::keyHeld(pCVar1,uVar9);
            if ((cVar2 == '\0') ||
               ((*(CBaseUnit **)(this + 0x1f8) != (CBaseUnit *)0x0 &&
                (cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x1f8),0x1f), cVar2 != '\0')))) {
              bVar15 = true;
            }
            else {
              bVar15 = false;
            }
            cVar2 = clickRight(this,*(longlong *)(*(long *)(this + 0x58) + 0x3c0),(bool)this[0x99],
                               bVar15);
            if (cVar2 != '\0') goto LAB_0057c8f9;
          }
        }
      }
      clickLeft();
    }
LAB_0057c8f9:
    this[0x99] = (CGameClient)0x1;
  }
  if ((*(CCharacter **)(this + 0x1c8) != (CCharacter *)0x0) &&
     (cVar2 = CCharacter::alive(*(CCharacter **)(this + 0x1c8)), cVar2 == '\0')) {
    TSafePointer<CCharacter>::setObject(this_01,(CCharacter *)0x0);
    CCharacter::setTarget(*(CCharacter **)(this + 0x58),(CCharacter *)0x0);
  }
  lVar11 = *(long *)(this + 0x1f8);
  if ((lVar11 != 0) && ((*(char *)(lVar11 + 0x1f0) == '\0' || (*(char *)(lVar11 + 0x1f1) != '\0'))))
  {
    TSafePointer<CItem>::setObject(this_02,(CItem *)0x0);
    CCharacter::setTargetItem(*(CCharacter **)(this + 0x58),(CItem *)0x0);
  }
LAB_0057c1c3:
  if ((*(long *)(this + 0x2b8) == 0) ||
     (cVar2 = CResourceManager::getEditorIsRunning(), cVar2 != '\0')) goto LAB_0057c280;
  pCVar1 = (CKeyManager *)(this + 0x2d0);
  cVar2 = CKeyManager::keyHeld(pCVar1,0x11);
  if (cVar2 == '\0') {
    return 1;
  }
  cVar2 = CKeyManager::keyHeld(pCVar1,0xbb);
  if (cVar2 == '\0') {
    cVar2 = CKeyManager::keyHeld(pCVar1,0xbd);
    if (cVar2 != '\0') {
      fVar16 = param_2 * DAT_00fa86ec + *(float *)(this + 0x38c0);
      bVar15 = NAN(fVar16) || NAN(DAT_00fa47f8);
      if (fVar16 <= DAT_00fa47f8) goto LAB_0057c748;
      goto LAB_0057c234;
    }
  }
  else {
    fVar16 = param_2 * DAT_00fa86e8 + *(float *)(this + 0x38c0);
    bVar15 = NAN(fVar16) || NAN(DAT_00fa47f8);
    if (fVar16 <= DAT_00fa47f8) {
LAB_0057c748:
      if (bVar15) goto LAB_0057c234;
      fVar16 = 0.0;
    }
    else {
LAB_0057c234:
      if (DAT_00fa86d0 < fVar16) {
        fVar16 = DAT_00fa86d0;
      }
    }
    *(float *)(this + 0x38c0) = fVar16;
  }
  cVar2 = CKeyManager::keyHeld(pCVar1,0xbb);
  if ((cVar2 == '\0') || (cVar2 = CKeyManager::keyHeld(pCVar1,0xbd), cVar2 == '\0')) {
    return 1;
  }
LAB_0057c280:
  *(undefined4 *)(this + 0x38c0) = 0x3f800000;
  return 1;
}



/* address=0057cbb0
   symbol=CGameClient::processInput */

/* CGameClient::processInput(void*, float, bool) */

undefined8 __thiscall
CGameClient::processInput(CGameClient *this,void *param_1,float param_2,bool param_3)

{
  undefined8 uVar1;

  if (param_3) {
    if (*(int *)(this + 0x38d0) == 0) {
      uVar1 = processMenuInput(this,param_1,param_2,true);
      return uVar1;
    }
    if (*(int *)(this + 0x38d0) == 1) {
      uVar1 = processIngameInput(this,param_1,param_2,true);
      return uVar1;
    }
  }
  return 1;
}



/* address=0057ec60
   symbol=CGameClient::~CGameClient */

/* WARNING: Removing unreachable block (ram,0x0057f5ff) */
/* WARNING: Removing unreachable block (ram,0x0057f360) */
/* WARNING: Removing unreachable block (ram,0x0057f3c8) */
/* WARNING: Removing unreachable block (ram,0x0057f355) */
/* WARNING: Removing unreachable block (ram,0x0057f4c9) */
/* WARNING: Removing unreachable block (ram,0x0057f3bd) */
/* WARNING: Removing unreachable block (ram,0x0057f55f) */
/* WARNING: Removing unreachable block (ram,0x0057f5f4) */
/* CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  allocator *paVar1;
  uint uVar2;
  int iVar3;
  long lVar4;
  int *piVar5;
  long lVar6;
  uint uVar7;
  long *plVar8;
  long lVar9;
  CGameClient *pCVar10;
  undefined **local_78;
  long *local_70;
  int *local_68;
  undefined **local_58;
  long *local_50;
  int *local_48;

  *(undefined ***)this = &PTR__CGameClient_00fa83d0;
  *(undefined ***)(this + 0x10) = &PTR__CGameClient_00fa8408;
  *(undefined ***)(this + 0x18) = &PTR__CGameClient_00fa8458;
  if ((*(CCharacter **)(this + 0x58) != (CCharacter *)0x0) &&
     (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0)) {
                    /* try { // try from 0057ec98 to 0057edd5 has its CatchHandler @ 0057f59a */
    CGameUI::notifyOfDeletion(*(CGameUI **)(this + 0x78),*(CCharacter **)(this + 0x58));
  }
  if ((*(CCharacter **)(this + 0x60) != (CCharacter *)0x0) &&
     (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0)) {
    CGameUI::notifyOfDeletion(*(CGameUI **)(this + 0x78),*(CCharacter **)(this + 0x60));
  }
  if (*(long *)(this + 0x38c8) != 0) {
    (**(code **)(**(long **)(this + 0x28) + 0x208))();
  }
  lVar4 = *(long *)(this + 0x2b8);
  if ((lVar4 != 0) && (uVar2 = *(uint *)(lVar4 + 0x30), uVar2 != 0)) {
    plVar8 = *(long **)(lVar4 + 0x28);
    uVar7 = 0;
    lVar6 = 8;
    if (this == (CGameClient *)*plVar8) {
      lVar9 = 0;
    }
    else {
      do {
        lVar9 = lVar6;
        uVar7 = uVar7 + 1;
        if (uVar2 <= uVar7) goto LAB_0057ed10;
        lVar6 = lVar9 + 8;
      } while (this != *(CGameClient **)((long)plVar8 + lVar9));
    }
    *(uint *)(lVar4 + 0x30) = uVar2 - 1;
    *(long *)((long)plVar8 + lVar9) = plVar8[uVar2 - 1];
  }
LAB_0057ed10:
  if (*(long **)(this + 0x1080) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1080) + 8))();
    *(undefined8 *)(this + 0x1080) = 0;
  }
  if (*(long **)(this + 0x1060) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1060) + 8))();
    *(undefined8 *)(this + 0x1060) = 0;
  }
  if (*(long **)(this + 0x1068) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1068) + 8))();
    *(undefined8 *)(this + 0x1068) = 0;
  }
  if (*(long **)(this + 0x1070) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1070) + 8))();
    *(undefined8 *)(this + 0x1070) = 0;
  }
  if (*(long **)(this + 0x1078) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1078) + 8))();
    *(undefined8 *)(this + 0x1078) = 0;
  }
  *(undefined8 *)(this + 0x38d8) = 0;
  CSoundManager::stopMusic(*(CSoundManager **)(this + 0x48));
  plVar8 = *(long **)(this + 0x208);
  if (plVar8 != (long *)0x0) {
    (**(code **)(*plVar8 + 0x2b0))(&local_58,plVar8,0,0);
                    /* try { // try from 0057ede0 to 0057ede5 has its CatchHandler @ 0057f2f6 */
    plVar8 = (long *)(**(code **)(*local_50 + 0x80))(local_50,0);
    local_58 = &PTR__SharedPtr_00fa85d0;
    if ((local_48 != (int *)0x0) && (iVar3 = *local_48, *local_48 = iVar3 + -1, iVar3 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa85e0)(&local_58);
    }
                    /* try { // try from 0057ee15 to 0057ee36 has its CatchHandler @ 0057f59a */
    (**(code **)(*plVar8 + 200))(plVar8,this + 0x10);
  }
  plVar8 = *(long **)(this + 0x210);
  if (plVar8 != (long *)0x0) {
    (**(code **)(*plVar8 + 0x2b0))(&local_78,plVar8,0,0);
                    /* try { // try from 0057ee41 to 0057ee46 has its CatchHandler @ 0057f2ad */
    plVar8 = (long *)(**(code **)(*local_70 + 0x80))(local_70,0);
    local_78 = &PTR__SharedPtr_00fa85d0;
    if ((local_68 != (int *)0x0) && (iVar3 = *local_68, *local_68 = iVar3 + -1, iVar3 + -1 == 0)) {
                    /* try { // try from 0057f277 to 0057f28a has its CatchHandler @ 0057f59a */
      (*(code *)PTR_destroy_00fa85e0)(&local_78);
    }
                    /* try { // try from 0057ee75 to 0057ef4c has its CatchHandler @ 0057f59a */
    (**(code **)(*plVar8 + 200))(plVar8,this + 0x10);
  }
  unloadCurrentLevel(this,true);
  if (*(long **)(this + 0x1088) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1088) + 8))();
    *(undefined8 *)(this + 0x1088) = 0;
  }
  if (*(long **)(this + 0x68) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x68) + 8))();
    *(undefined8 *)(this + 0x68) = 0;
  }
  if (*(long **)(this + 0x78) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x78) + 8))();
    *(undefined8 *)(this + 0x78) = 0;
  }
  if (*(CMasterResourceManager **)(this + 0x1040) != (CMasterResourceManager *)0x0) {
    CMasterResourceManager::removeUnused(*(CMasterResourceManager **)(this + 0x1040));
  }
  if (*(long **)(this + 0x2b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2b8) + 8))();
    *(undefined8 *)(this + 0x2b8) = 0;
  }
  if (*(long **)(this + 0x230) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x230) + 8))();
    *(undefined8 *)(this + 0x230) = 0;
  }
  if (*(long **)(this + 0x238) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x238) + 8))();
    *(undefined8 *)(this + 0x238) = 0;
  }
  if (*(long **)(this + 0x240) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x240) + 8))();
    *(undefined8 *)(this + 0x240) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x38f8) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x38f8) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x38f0) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x38f0) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  pCVar10 = this + 0x38c0;
  do {
    pCVar10 = pCVar10 + -0x20;
                    /* try { // try from 0057efaa to 0057efab has its CatchHandler @ 0057f4ab */
    (*(code *)**(undefined8 **)pCVar10)(pCVar10);
  } while (pCVar10 != this + 0x30c0);
  do {
    pCVar10 = pCVar10 + -0x20;
                    /* try { // try from 0057efca to 0057efcb has its CatchHandler @ 0057f4d4 */
    (*(code *)**(undefined8 **)pCVar10)(pCVar10);
  } while (pCVar10 != this + 0x28c0);
  do {
    pCVar10 = pCVar10 + -0x20;
                    /* try { // try from 0057efea to 0057efeb has its CatchHandler @ 0057f60a */
    (*(code *)**(undefined8 **)pCVar10)(pCVar10);
  } while (pCVar10 != this + 0x20c0);
  do {
    pCVar10 = pCVar10 + -0x20;
                    /* try { // try from 0057f00a to 0057f00b has its CatchHandler @ 0057f627 */
    (*(code *)**(undefined8 **)pCVar10)(pCVar10);
  } while (pCVar10 != this + 0x18c0);
  do {
    pCVar10 = pCVar10 + -0x20;
                    /* try { // try from 0057f02a to 0057f02b has its CatchHandler @ 0057f4f6 */
    (*(code *)**(undefined8 **)pCVar10)(pCVar10);
  } while (pCVar10 != this + 0x10c0);
  paVar1 = (allocator *)(*(long *)(this + 0x10b0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x10b0) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x10a8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x10a8) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1098) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x1098) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
                    /* try { // try from 0057f079 to 0057f07d has its CatchHandler @ 0057f3d3 */
  CMouseManager::~CMouseManager((CMouseManager *)(this + 0xfe8));
                    /* try { // try from 0057f085 to 0057f089 has its CatchHandler @ 0057f4a3 */
  CKeyManager::~CKeyManager((CKeyManager *)(this + 0x2d0));
  *(undefined ***)(this + 0x288) = &PTR__SharedPtr_00fa4590;
  piVar5 = *(int **)(this + 0x298);
  if ((piVar5 != (int *)0x0) && (iVar3 = *piVar5, *piVar5 = iVar3 + -1, iVar3 + -1 == 0)) {
                    /* try { // try from 0057f267 to 0057f269 has its CatchHandler @ 0057f592 */
    (**(code **)(*(long *)(this + 0x288) + 0x10))();
  }
  *(undefined ***)(this + 0x268) = &PTR__SharedPtr_00fa4590;
  piVar5 = *(int **)(this + 0x278);
  if ((piVar5 != (int *)0x0) && (iVar3 = *piVar5, *piVar5 = iVar3 + -1, iVar3 + -1 == 0)) {
                    /* try { // try from 0057f257 to 0057f259 has its CatchHandler @ 0057f58a */
    (**(code **)(*(long *)(this + 0x268) + 0x10))();
  }
  *(undefined ***)(this + 0x248) = &PTR__SharedPtr_00fa4590;
  piVar5 = *(int **)(this + 600);
  if ((piVar5 != (int *)0x0) && (iVar3 = *piVar5, *piVar5 = iVar3 + -1, iVar3 + -1 == 0)) {
                    /* try { // try from 0057f23f to 0057f241 has its CatchHandler @ 0057f582 */
    (**(code **)(*(long *)(this + 0x248) + 0x10))();
  }
  if (*(CRunicCore **)(this + 0x1f8) != (CRunicCore *)0x0) {
                    /* try { // try from 0057f121 to 0057f125 has its CatchHandler @ 0057f57a */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1f8),(TSafePointer *)(this + 0x1f8),*(uint *)(this + 0x200)
              );
  }
  *(undefined8 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x200) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
                    /* try { // try from 0057f154 to 0057f158 has its CatchHandler @ 0057f572 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),*(uint *)(this + 0x1f0)
              );
  }
  *(undefined8 *)(this + 0x1e8) = 0;
  *(undefined4 *)(this + 0x1f0) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
                    /* try { // try from 0057f187 to 0057f18b has its CatchHandler @ 0057f56a */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),*(uint *)(this + 0x1e0)
              );
  }
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1e0) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x1c8) != (CRunicCore *)0x0) {
                    /* try { // try from 0057f1ba to 0057f1be has its CatchHandler @ 0057f557 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1c8),(TSafePointer *)(this + 0x1c8),*(uint *)(this + 0x1d0)
              );
  }
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined4 *)(this + 0x1d0) = 0xffffffff;
  paVar1 = (allocator *)(*(long *)(this + 0x1b0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x1b0) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1a8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x1a8) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x1a0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar5 = (int *)(*(long *)(this + 0x1a0) + -8);
    iVar3 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  *(undefined ***)(this + 0x18) = &PTR__RenderableListener_00fa46b0;
  *(undefined ***)(this + 0x10) = &PTR__RenderTargetListener_00fa4650;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=0057f650
   symbol=CGameClient::~CGameClient */

/* non-virtual thunk to CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  ~CGameClient(this + -0x18);
  return;
}



/* address=0057f660
   symbol=CGameClient::~CGameClient */

/* non-virtual thunk to CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  ~CGameClient(this + -0x10);
  return;
}



/* address=0057f670
   symbol=CGameClient::~CGameClient */

/* non-virtual thunk to CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  ~CGameClient(this + -0x18);
  return;
}



/* address=0057f680
   symbol=CGameClient::~CGameClient */

/* non-virtual thunk to CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  ~CGameClient(this + -0x10);
  return;
}



/* address=0057f690
   symbol=CGameClient::~CGameClient */

/* CGameClient::~CGameClient() */

void __thiscall CGameClient::~CGameClient(CGameClient *this)

{
  ~CGameClient(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=0057f6b0
   symbol=CGameClient::setCurrentDungeon */

/* WARNING: Removing unreachable block (ram,0x0057f7b5) */
/* WARNING: Removing unreachable block (ram,0x0057f7a8) */
/* CGameClient::setCurrentDungeon(std::wstring) */

void __thiscall CGameClient::setCurrentDungeon(CGameClient *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  CDungeonManager *pCVar3;
  long lVar4;
  long local_38 [2];
  long local_28 [2];

  STRINGS::StringUpper((STRINGS *)local_28,param_2);
                    /* try { // try from 0057f6dc to 0057f6e0 has its CatchHandler @ 0057f795 */
  std::wstring::assign(param_2);
  if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_28[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
    }
  }
  std::wstring::wstring((wstring_conflict *)local_38,param_2);
                    /* try { // try from 0057f703 to 0057f712 has its CatchHandler @ 0057f7b3 */
  pCVar3 = (CDungeonManager *)CDungeonManager::getSingleton();
  lVar4 = CDungeonManager::getDungeonByName(pCVar3,(wstring_conflict *)local_38);
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
  if (lVar4 != 0) {
    *(long *)(this + 0x38d8) = lVar4;
  }
  return;
}



/* address=0057f7c0
   symbol=CGameClient::restoreLevelState */

/* WARNING: Removing unreachable block (ram,0x0058198b) */
/* WARNING: Removing unreachable block (ram,0x00581576) */
/* WARNING: Removing unreachable block (ram,0x00581619) */
/* WARNING: Removing unreachable block (ram,0x005813fc) */
/* WARNING: Removing unreachable block (ram,0x0058158f) */
/* WARNING: Removing unreachable block (ram,0x00580e23) */
/* WARNING: Removing unreachable block (ram,0x005813f1) */
/* WARNING: Removing unreachable block (ram,0x005818b7) */
/* WARNING: Removing unreachable block (ram,0x00581581) */
/* WARNING: Removing unreachable block (ram,0x005818de) */
/* WARNING: Removing unreachable block (ram,0x00581513) */
/* WARNING: Removing unreachable block (ram,0x005817f6) */
/* WARNING: Removing unreachable block (ram,0x00580dcb) */
/* WARNING: Removing unreachable block (ram,0x005817c0) */
/* CGameClient::restoreLevelState(CLevelState*) */

void __thiscall CGameClient::restoreLevelState(CGameClient *this,CLevelState *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  CEditorScene *this_00;
  long lVar5;
  CFormationNodeSaveAndLoad *pCVar6;
  CEditorBaseObject CVar7;
  char cVar8;
  int iVar9;
  CEditorBaseObject *pCVar10;
  CPositionableObject *pCVar11;
  CAnimationPlayer *this_01;
  CLogicTimer *this_02;
  COutputIncrementor *this_03;
  undefined8 *puVar12;
  CCharacter *pCVar13;
  long *plVar14;
  undefined8 uVar15;
  long lVar16;
  CItem *pCVar17;
  CItemGold *this_04;
  CFormationNode *this_05;
  void *pvVar18;
  long lVar19;
  ulong uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  long local_190;
  long local_168;
  long *local_158;
  int local_150;
  uint local_14c;
  undefined4 local_148;
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [4];
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

  *(undefined4 *)(this + 0x84) = 3;
  *(undefined1 *)(*(long *)(this + 0x2b8) + 0x41) = 0;
  lVar4 = *(long *)(this + 0x70);
  iVar3 = *(int *)(lVar4 + 0x18);
  local_168 = 0;
  for (uVar22 = 0; (int)uVar22 < iVar3; uVar22 = uVar22 + 1) {
    if (uVar22 < *(uint *)(lVar4 + 0x1c)) {
      puVar12 = (undefined8 *)(local_168 + *(long *)(lVar4 + 0x10));
    }
    else {
      puVar12 = *(undefined8 **)(lVar4 + 0x10);
    }
    this_00 = (CEditorScene *)*puVar12;
    local_148 = 0x19;
    local_150 = 0;
    local_14c = 0;
    local_158 = (long *)0x0;
                    /* try { // try from 0057f86b to 0057f86f has its CatchHandler @ 005812f2 */
    std::wstring::wstring((wstring_conflict *)local_68,L"Timeline",local_39);
                    /* try { // try from 0057f882 to 0057f886 has its CatchHandler @ 00581718 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_68,(TArrayList *)&local_158);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar10 = (CEditorBaseObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CTimeline::typeinfo),
           pCVar10 != (CEditorBaseObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar10 + 0x20))) {
                if (*(long *)(pCVar10 + 0x28) == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode(pCVar10);
                  if (*(long *)(lVar5 + 0x40) == *(long *)(pCVar10 + 0x28)) goto LAB_00580b2e;
                }
                else if (*(long *)(lVar5 + 0x40) == *(long *)(pCVar10 + 0x28)) {
LAB_00580b2e:
                  iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28));
                  if (iVar9 == 0) {
                    if (*(char *)(lVar5 + 0x14) == '\0') {
                      CTimeline::Stop((CTimeline *)pCVar10);
                    }
                    else {
                      CTimeline::SetEnabled((CTimeline *)pCVar10,true);
                      CVar7 = (CEditorBaseObject)(DAT_00fa47fc == *(float *)(lVar5 + 0x24));
                      pCVar10[0xa0] = CVar7;
                      if (((0.0 < *(float *)(lVar5 + 0x20)) &&
                          (pCVar10[0xa3] != (CEditorBaseObject)0x0)) && (!(bool)CVar7)) {
                        CTimeline::Play((CTimeline *)pCVar10,true);
                        CTimeline::UpdateTimeline
                                  ((CTimeline *)pCVar10,
                                   *(float *)(lVar5 + 0x20) * *(float *)(pCVar10 + 0x94));
                      }
                    }
                    pCVar10[0xa2] = (CEditorBaseObject)(*(byte *)(lVar5 + 0x14) ^ 1);
                    CTimeline::SetEnabled((CTimeline *)pCVar10,*(bool *)(lVar5 + 0x10));
                  }
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0057f9cd to 0057f9d1 has its CatchHandler @ 0058144f */
    std::wstring::wstring((wstring_conflict *)local_78,L"Player Sphere Trigger",&local_3a);
                    /* try { // try from 0057f9df to 0057f9e3 has its CatchHandler @ 00581407 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_78,(TArrayList *)&local_158);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar11 = (CPositionableObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CTriggerSphere::typeinfo
                                    ), pCVar11 != (CPositionableObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar11 + 0x20))) {
                lVar16 = *(long *)(pCVar11 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)pCVar11);
                  lVar16 = *(long *)(pCVar11 + 0x28);
                }
                    /* try { // try from 0057fad8 to 0057fb1b has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  (**(code **)(*(long *)pCVar11 + 0x40))(pCVar11,*(undefined1 *)(lVar5 + 0x10));
                  pCVar11[0x100] = *(CPositionableObject *)(lVar5 + 0x11);
                  pCVar11[0x101] = *(CPositionableObject *)(lVar5 + 0x12);
                  pCVar11[0x102] = *(CPositionableObject *)(lVar5 + 0x13);
                  CPositionableObject::setPosition(pCVar11,(Vector3 *)(lVar5 + 0x50));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0057fb71 to 0057fb75 has its CatchHandler @ 0058149c */
    std::wstring::wstring((wstring_conflict *)local_88,L"Player Box Trigger",&local_3b);
                    /* try { // try from 0057fb83 to 0057fb87 has its CatchHandler @ 00581454 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_88,(TArrayList *)&local_158);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar11 = (CPositionableObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CTriggerBox::typeinfo),
           pCVar11 != (CPositionableObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar11 + 0x20))) {
                lVar16 = *(long *)(pCVar11 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)pCVar11);
                  lVar16 = *(long *)(pCVar11 + 0x28);
                }
                    /* try { // try from 0057fc78 to 0057fcbb has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  (**(code **)(*(long *)pCVar11 + 0x40))(pCVar11,*(undefined1 *)(lVar5 + 0x10));
                  pCVar11[0x100] = *(CPositionableObject *)(lVar5 + 0x11);
                  pCVar11[0x101] = *(CPositionableObject *)(lVar5 + 0x12);
                  pCVar11[0x102] = *(CPositionableObject *)(lVar5 + 0x13);
                  CPositionableObject::setPosition(pCVar11,(Vector3 *)(lVar5 + 0x50));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0057fd11 to 0057fd15 has its CatchHandler @ 00581677 */
    std::wstring::wstring((wstring_conflict *)local_98,L"Property Node",&local_3c);
                    /* try { // try from 0057fd23 to 0057fd27 has its CatchHandler @ 0058162f */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_98,(TArrayList *)&local_158);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar11 = (CPositionableObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CPropertyNode::typeinfo)
           , pCVar11 != (CPositionableObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar11 + 0x20))) {
                lVar16 = *(long *)(pCVar11 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)pCVar11);
                  lVar16 = *(long *)(pCVar11 + 0x28);
                }
                    /* try { // try from 0057fe14 to 0057fe36 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  CPositionableObject::setPosition(pCVar11,(Vector3 *)(lVar5 + 0x50));
                  (**(code **)(*(long *)pCVar11 + 0x40))(pCVar11,*(undefined1 *)(lVar5 + 0x10));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0057fe8c to 0057fe90 has its CatchHandler @ 00580e1e */
    std::wstring::wstring((wstring_conflict *)local_a8,L"Group",&local_3d);
                    /* try { // try from 0057fe9e to 0057fea2 has its CatchHandler @ 00580dd6 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_a8,(TArrayList *)&local_158);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar11 = (CPositionableObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CRandomGroup::typeinfo),
           pCVar11 != (CPositionableObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar11 + 0x20))) {
                lVar16 = *(long *)(pCVar11 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)pCVar11);
                  lVar16 = *(long *)(pCVar11 + 0x28);
                }
                    /* try { // try from 0057ff94 to 0057ffc4 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  (**(code **)(*(long *)pCVar11 + 0x40))(pCVar11,*(undefined1 *)(lVar5 + 0x10));
                  (**(code **)(*(long *)pCVar11 + 0x50))(pCVar11,*(undefined1 *)(lVar5 + 0x11));
                  CPositionableObject::setPosition(pCVar11,(Vector3 *)(lVar5 + 0x50));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0058001a to 0058001e has its CatchHandler @ 005816e1 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"Animation Controller",&local_3e);
                    /* try { // try from 0058002c to 00580030 has its CatchHandler @ 00581695 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_b8,(TArrayList *)&local_158);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (this_01 = (CAnimationPlayer *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,
                                     &CAnimationPlayer::typeinfo),
           this_01 != (CAnimationPlayer *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(this_01 + 0x20))) {
                lVar16 = *(long *)(this_01 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)this_01);
                  lVar16 = *(long *)(this_01 + 0x28);
                }
                    /* try { // try from 00580124 to 0058014b has its CatchHandler @ 00581614 */
                if (((*(long *)(lVar5 + 0x40) == lVar16) &&
                    (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) &&
                   (*(char *)(lVar5 + 0x10) != '\0')) {
                  CAnimationPlayer::playAnimation(this_01,*(bool *)(lVar5 + 0x14));
                  CAnimationPlayer::setAnimationDuration(this_01,*(float *)(lVar5 + 0x18));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 005801a1 to 005801a5 has its CatchHandler @ 00580d66 */
    std::wstring::wstring((wstring_conflict *)local_c8,L"Counter",&local_3f);
                    /* try { // try from 005801b3 to 005801b7 has its CatchHandler @ 00580d07 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_c8,(TArrayList *)&local_158);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar10 = (CEditorBaseObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CCounter::typeinfo),
           pCVar10 != (CEditorBaseObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar10 + 0x20))) {
                lVar16 = *(long *)(pCVar10 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode(pCVar10);
                  lVar16 = *(long *)(pCVar10 + 0x28);
                }
                    /* try { // try from 005802a4 to 005802a8 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  pCVar10[0x68] = *(CEditorBaseObject *)(lVar5 + 0x10);
                  *(int *)(pCVar10 + 0x60) = (int)*(float *)(lVar5 + 0x20);
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 00580313 to 00580317 has its CatchHandler @ 00581343 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"Timer",&local_40);
                    /* try { // try from 00580325 to 00580329 has its CatchHandler @ 005812f7 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_d8,(TArrayList *)&local_158);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (this_02 = (CLogicTimer *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CLogicTimer::typeinfo),
           this_02 != (CLogicTimer *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(this_02 + 0x20))) {
                lVar16 = *(long *)(this_02 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)this_02);
                  lVar16 = *(long *)(this_02 + 0x28);
                }
                    /* try { // try from 00580424 to 0058044e has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  CLogicTimer::setEnabled(this_02,*(bool *)(lVar5 + 0x10));
                  *(undefined4 *)(this_02 + 0x68) = *(undefined4 *)(lVar5 + 0x1c);
                  *(undefined4 *)(this_02 + 0x58) = *(undefined4 *)(lVar5 + 0x20);
                  CLogicTimer::resetTimer(this_02);
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 005804a4 to 005804a8 has its CatchHandler @ 005815e2 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"Output Incrementor",&local_41);
                    /* try { // try from 005804b6 to 005804ba has its CatchHandler @ 0058159a */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_e8,(TArrayList *)&local_158);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (this_03 = (COutputIncrementor *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,
                                     &COutputIncrementor::typeinfo),
           this_03 != (COutputIncrementor *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(this_03 + 0x20))) {
                lVar16 = *(long *)(this_03 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode((CEditorBaseObject *)this_03);
                  lVar16 = *(long *)(this_03 + 0x28);
                }
                    /* try { // try from 005805b4 to 005805c8 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  COutputIncrementor::setEnabled(this_03,*(bool *)(lVar5 + 0x10));
                  *(int *)(this_03 + 100) = (int)*(float *)(lVar5 + 0x20);
                  *(undefined4 *)(this_03 + 0x5c) = *(undefined4 *)(lVar5 + 0x1c);
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 00580632 to 00580636 has its CatchHandler @ 0058184c */
    std::wstring::wstring((wstring_conflict *)local_f8,L"Teleport",&local_42);
                    /* try { // try from 00580644 to 00580648 has its CatchHandler @ 00581804 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_f8,(TArrayList *)&local_158);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar10 = (CEditorBaseObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CTeleport::typeinfo),
           pCVar10 != (CEditorBaseObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar10 + 0x20))) {
                lVar16 = *(long *)(pCVar10 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode(pCVar10);
                  lVar16 = *(long *)(pCVar10 + 0x28);
                }
                    /* try { // try from 0058073c to 00580752 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  (**(code **)(*(long *)pCVar10 + 0x40))(pCVar10,*(undefined1 *)(lVar5 + 0x10));
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 005807ad to 005807b1 has its CatchHandler @ 005818b2 */
    std::wstring::wstring((wstring_conflict *)local_108,L"Puzzle Input",&local_43);
                    /* try { // try from 005807bf to 005807c3 has its CatchHandler @ 0058186a */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_108,(TArrayList *)&local_158);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar10 = (CEditorBaseObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,
                                     &CPuzzleRandomizer::typeinfo),
           pCVar10 != (CEditorBaseObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar10 + 0x20))) {
                lVar16 = *(long *)(pCVar10 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode(pCVar10);
                  lVar16 = *(long *)(pCVar10 + 0x28);
                }
                    /* try { // try from 005808b4 to 005808b8 has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  pCVar10[0x68] = *(CEditorBaseObject *)(lVar5 + 0x10);
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    local_150 = 0;
    local_14c = 0;
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
    }
    local_158 = (long *)0x0;
                    /* try { // try from 0058091a to 0058091e has its CatchHandler @ 00581394 */
    std::wstring::wstring((wstring_conflict *)local_118,L"Unit Spawner",&local_44);
                    /* try { // try from 0058092c to 00580930 has its CatchHandler @ 00581348 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (this_00,(wstring_conflict *)local_118,(TArrayList *)&local_158);
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    iVar2 = local_150;
    if ((local_150 != 0) && (0 < local_150)) {
      local_190 = 0;
      uVar23 = 0;
      do {
        plVar14 = local_158;
        if (uVar23 < local_14c) {
          plVar14 = (long *)(local_190 + (long)local_158);
        }
        if ((*plVar14 != 0) &&
           (pCVar10 = (CEditorBaseObject *)
                      __dynamic_cast(*plVar14,&CEditorBaseObject::typeinfo,&CUnitSpawner::typeinfo),
           pCVar10 != (CEditorBaseObject *)0x0)) {
          lVar19 = *(long *)(param_1 + 0x58);
          lVar16 = *(long *)(param_1 + 0x50);
          if ((int)((ulong)(lVar19 - lVar16) >> 3) != 0) {
            uVar20 = 0;
            do {
              lVar5 = *(long *)(lVar16 + uVar20 * 8);
              if (((*(uint *)(lVar5 + 0x30) != 0xffffffff) && (uVar22 == *(uint *)(lVar5 + 0x30)))
                 && (*(long *)(lVar5 + 0x48) == *(long *)(pCVar10 + 0x20))) {
                lVar16 = *(long *)(pCVar10 + 0x28);
                if (lVar16 == 0) {
                  CEditorBaseObject::calculateParentHierarchyHashCode(pCVar10);
                  lVar16 = *(long *)(pCVar10 + 0x28);
                }
                    /* try { // try from 00580a98 to 00580cea has its CatchHandler @ 00581614 */
                if ((*(long *)(lVar5 + 0x40) == lVar16) &&
                   (iVar9 = std::wstring::compare((wchar_t *)(lVar5 + 0x28)), iVar9 == 0)) {
                  pCVar10[0x1c1] = *(CEditorBaseObject *)(lVar5 + 0x10);
                  uVar21 = (uint)(long)*(float *)(lVar5 + 0x20);
                  *(uint *)(pCVar10 + 0x18c) = uVar21;
                  if (*(uint *)(pCVar10 + 400) <= uVar21) {
                    pCVar10[0x1c1] = (CEditorBaseObject)0x0;
                  }
                  *(undefined4 *)(pCVar10 + 0x188) = *(undefined4 *)(lVar5 + 0x24);
                  break;
                }
                lVar16 = *(long *)(param_1 + 0x50);
                lVar19 = *(long *)(param_1 + 0x58);
              }
              uVar21 = (int)uVar20 + 1;
              uVar20 = (ulong)uVar21;
            } while (uVar21 < (uint)(lVar19 - lVar16 >> 3));
          }
        }
        uVar23 = uVar23 + 1;
        local_190 = local_190 + 8;
      } while ((int)uVar23 < iVar2);
    }
    if (local_158 != (long *)0x0) {
      operator_delete__(local_158);
      local_158 = (long *)0x0;
    }
    local_168 = local_168 + 8;
  }
  if (*(CAutomap **)(*(long *)(this + 0x70) + 0x1e0) != (CAutomap *)0x0) {
    CLevelState::restoreAutomap(param_1,*(CAutomap **)(*(long *)(this + 0x70) + 0x1e0));
  }
  for (uVar22 = 0; uVar22 < (uint)(*(long *)(param_1 + 0x28) - *(long *)(param_1 + 0x20) >> 3);
      uVar22 = uVar22 + 1) {
    lVar4 = *(long *)(*(long *)(param_1 + 0x20) + (ulong)uVar22 * 8);
    if (*(char *)(lVar4 + 0x18) == '\0') {
      plVar14 = (long *)CResourceManager::createUnit
                                  (*(CResourceManager **)(this + 0x2b8),*(longlong *)(lVar4 + 0x20),
                                   *(int *)(lVar4 + 0xd0),true,false);
      if (plVar14 != (long *)0x0) {
LAB_00580e8d:
        pCVar13 = (CCharacter *)__dynamic_cast(plVar14,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
        if (pCVar13 == (CCharacter *)0x0) {
          if (plVar14 != (long *)0x0) {
            (**(code **)(*plVar14 + 8))(plVar14);
          }
        }
        else {
          if (*(char *)(lVar4 + 0x18) == '\0') {
            CLevel::addCharacter(*(CLevel **)(this + 0x70),pCVar13,(Vector3 *)(lVar4 + 0x6c),false);
          }
          (**(code **)(*(long *)pCVar13 + 0x2a0))(pCVar13);
        }
      }
    }
    else {
                    /* try { // try from 00580e75 to 00580f5b has its CatchHandler @ 00580f38 */
      plVar14 = (long *)CLevel::getCharacterByOriginalGuid
                                  (*(longlong *)(this + 0x70),*(longlong *)(lVar4 + 0x10),-1);
      if (plVar14 != (long *)0x0) {
        *(undefined1 *)(plVar14 + 0x32) = 0;
        goto LAB_00580e8d;
      }
      STRINGS::StringConvertToNarrow((STRINGS *)local_128,*(wchar_t **)(lVar4 + 0x40));
                    /* try { // try from 00580f6b to 00580f6f has its CatchHandler @ 0058194e */
      std::operator+((char *)local_138,(string *)"Unable to find editor character ");
                    /* try { // try from 00580f70 to 00580f88 has its CatchHandler @ 005818ec */
      uVar15 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar15,local_138,3);
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_138[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_128[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
    }
  }
  uVar22 = 0;
  do {
    if ((uint)(*(long *)(param_1 + 0x40) - *(long *)(param_1 + 0x38) >> 3) <= uVar22) {
      for (uVar22 = 0; uVar22 < *(uint *)(param_1 + 0x88); uVar22 = uVar22 + 1) {
        if (uVar22 < *(uint *)(param_1 + 0x8c)) {
          puVar12 = (undefined8 *)((ulong)uVar22 * 8 + *(long *)(param_1 + 0x80));
        }
        else {
          puVar12 = *(undefined8 **)(param_1 + 0x80);
        }
        pCVar6 = (CFormationNodeSaveAndLoad *)*puVar12;
                    /* try { // try from 0058118f to 00581193 has its CatchHandler @ 00580f38 */
        this_05 = (CFormationNode *)Ogre::NedAllocImpl::allocBytes(0x118,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005811a9 to 005811ad has its CatchHandler @ 00581296 */
        CFormationNode::CFormationNode(this_05,*(CResourceManager **)(this + 0x2b8),pCVar6);
        lVar4 = *(long *)(this + 0x70);
        uVar23 = *(uint *)(lVar4 + 0x208);
        if (uVar23 < *(uint *)(lVar4 + 0x20c)) {
          pvVar18 = *(void **)(lVar4 + 0x200);
        }
        else if (*(long *)(lVar4 + 0x200) == 0) {
          *(uint *)(lVar4 + 0x20c) = *(uint *)(lVar4 + 0x210);
          pvVar18 = operator_new__((ulong)*(uint *)(lVar4 + 0x210) << 3);
          *(void **)(lVar4 + 0x200) = pvVar18;
          uVar23 = *(uint *)(lVar4 + 0x208);
        }
        else {
          uVar21 = *(uint *)(lVar4 + 0x20c) + *(int *)(lVar4 + 0x210);
                    /* try { // try from 005811e9 to 00581283 has its CatchHandler @ 00580f38 */
          pvVar18 = operator_new__((ulong)uVar21 << 3);
          if (*(int *)(lVar4 + 0x20c) != 0) {
            uVar23 = 0;
            do {
              uVar20 = (ulong)uVar23;
              uVar23 = uVar23 + 1;
              *(undefined8 *)((long)pvVar18 + uVar20 * 8) =
                   *(undefined8 *)(*(long *)(lVar4 + 0x200) + uVar20 * 8);
            } while (uVar23 < *(uint *)(lVar4 + 0x20c));
          }
          if (*(void **)(lVar4 + 0x200) != (void *)0x0) {
            operator_delete__(*(void **)(lVar4 + 0x200));
          }
          uVar23 = *(uint *)(lVar4 + 0x208);
          *(void **)(lVar4 + 0x200) = pvVar18;
          *(uint *)(lVar4 + 0x20c) = uVar21;
        }
        *(CFormationNode **)((long)pvVar18 + (ulong)uVar23 * 8) = this_05;
        *(int *)(lVar4 + 0x208) = *(int *)(lVar4 + 0x208) + 1;
      }
      *(undefined1 *)(*(long *)(this + 0x2b8) + 0x41) = 1;
                    /* try { // try from 005812bf to 005812df has its CatchHandler @ 00580f38 */
      CCameraControl::clearCameraShakes(*(CCameraControl **)(this + 0x20));
      CLevel::populateNewMerchantsInventory(*(CLevel **)(this + 0x70));
      CLevel::updateNPCIcons(*(CLevel **)(this + 0x70));
      return;
    }
    lVar4 = *(long *)(*(long *)(param_1 + 0x38) + (ulong)uVar22 * 8);
    if (*(long *)(lVar4 + 0x60) == -1) {
      this_04 = (CItemGold *)Ogre::NedAllocImpl::allocBytes(0x288,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00581116 to 0058111a has its CatchHandler @ 00581149 */
      CItemGold::CItemGold(this_04,*(CResourceManager **)(this + 0x2b8),*(int *)(lVar4 + 0x68));
                    /* try { // try from 00581130 to 00581143 has its CatchHandler @ 00580f38 */
      CLevel::addItem(*(CLevel **)(this + 0x70),(CItem *)this_04,(Vector3 *)(lVar4 + 0x84),false);
    }
    else if (*(char *)(lVar4 + 0x48) == '\0') {
      plVar14 = (long *)CResourceManager::createUnit
                                  (*(CResourceManager **)(this + 0x2b8),*(long *)(lVar4 + 0x60),1,
                                   true,false);
      if (plVar14 != (long *)0x0) {
        pCVar17 = (CItem *)__dynamic_cast(plVar14,&CBaseUnit::typeinfo,&CItem::typeinfo);
        if (pCVar17 != (CItem *)0x0) {
          CLevel::addItem(*(CLevel **)(this + 0x70),pCVar17,(Vector3 *)(lVar4 + 0x84),false);
          goto LAB_00581027;
        }
        (**(code **)(*plVar14 + 8))(plVar14);
      }
    }
    else {
                    /* try { // try from 00581001 to 00581100 has its CatchHandler @ 00580f38 */
      lVar16 = CLevel::getItemByOriginalGuid
                         (*(longlong *)(this + 0x70),*(longlong *)(lVar4 + 0x30),
                          (int)*(undefined8 *)(lVar4 + 0x38),(ulong)*(uint *)(lVar4 + 0x80));
      if ((lVar16 != 0) &&
         (pCVar17 = (CItem *)__dynamic_cast(lVar16,&CBaseUnit::typeinfo,&CItem::typeinfo),
         pCVar17 != (CItem *)0x0)) {
LAB_00581027:
        (**(code **)(*(long *)pCVar17 + 0x298))(pCVar17,lVar4);
        cVar8 = CBaseUnit::ISA((CBaseUnit *)pCVar17);
        if ((cVar8 != '\0') && (*(CBaseUnit *)(pCVar17 + 0x1f2) != (CBaseUnit)0x0)) {
          CItem::snapToGround();
        }
      }
    }
    uVar22 = uVar22 + 1;
  } while( true );
}



/* address=005819b0
   symbol=CGameClient::warpLevels */

/* WARNING: Removing unreachable block (ram,0x00581bad) */
/* WARNING: Removing unreachable block (ram,0x00581b8f) */
/* CGameClient::warpLevels(std::wstring, int, int, bool, std::wstring, bool) */

void __thiscall
CGameClient::warpLevels
          (CGameClient *this,wstring_conflict *param_2,undefined4 param_3,undefined4 param_4,
          CGameClient param_5,wstring_conflict *param_6,CGameClient param_7)

{
  int *piVar1;
  undefined4 uVar2;
  size_t __n;
  int iVar3;
  bool bVar4;
  long local_58 [2];
  long local_48 [3];

  this[0x10ba] = param_5;
  this[0x10b8] = param_7;
  STRINGS::StringUpper((STRINGS *)local_48,param_6);
                    /* try { // try from 00581a09 to 00581a0d has its CatchHandler @ 00581b9a */
  std::wstring::assign((wstring_conflict *)(this + 0x10b0));
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
                    /* try { // try from 00581a2d to 00581a44 has its CatchHandler @ 00581b77 */
  STRINGS::StringUpper((STRINGS *)local_58,param_2);
  iVar3 = std::wstring::compare((wchar_t *)local_58);
  bVar4 = false;
  if (iVar3 == 0) {
    bVar4 = true;
    __n = *(size_t *)(*(wchar_t **)(*(long *)(this + 0x58) + 2000) + -6);
    if (__n == *(size_t *)(::EMPTY_WSTRING + -6)) {
      iVar3 = wmemcmp(*(wchar_t **)(*(long *)(this + 0x58) + 2000),::EMPTY_WSTRING,__n);
      bVar4 = iVar3 != 0;
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (bVar4) {
    std::wstring::assign((wstring_conflict *)(this + 0x10a8));
    uVar2 = *(undefined4 *)(*(long *)(this + 0x58) + 0x7cc);
    *(undefined4 *)(this + 0x10a0) = 0;
    *(undefined4 *)(this + 0x10a4) = uVar2;
  }
  else {
    std::wstring::assign((wstring_conflict *)(this + 0x10a8));
    *(undefined4 *)(this + 0x10a4) = param_4;
    *(undefined4 *)(this + 0x10a0) = param_3;
  }
  this[0x10b9] = (CGameClient)0x1;
  return;
}



/* address=00581bc0
   symbol=CGameClient::storedUnitExists */

/* WARNING: Removing unreachable block (ram,0x00581cca) */
/* CGameClient::storedUnitExists(long long) */

undefined8 __thiscall CGameClient::storedUnitExists(CGameClient *this,longlong param_1)

{
  int *piVar1;
  long *plVar2;
  int iVar3;
  undefined4 uVar4;
  long *plVar5;
  uint uVar6;
  long lVar7;
  long lVar8;
  uint uVar9;
  long local_38 [3];

  lVar7 = *(long *)(this + 0x70);
  if ((lVar7 != 0) && (*(long *)(this + 0x58) != 0)) {
    uVar4 = *(undefined4 *)(lVar7 + 0x1a4);
    std::wstring::wstring((wstring_conflict *)local_38,(wstring_conflict *)(lVar7 + 0x280));
                    /* try { // try from 00581c0e to 00581c12 has its CatchHandler @ 00581cb7 */
    lVar7 = CPlayer::getLevelSavedState
                      (*(CPlayer **)(this + 0x58),(wstring_conflict *)local_38,uVar4);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    plVar5 = *(long **)(lVar7 + 0x20);
    uVar9 = (uint)((ulong)(*(long *)(lVar7 + 0x28) - (long)plVar5) >> 3);
    if (uVar9 != 0) {
      uVar6 = 0;
      lVar8 = 8;
      lVar7 = *(long *)(*plVar5 + 0x10);
      while( true ) {
        if (lVar7 == param_1) {
          return 1;
        }
        uVar6 = uVar6 + 1;
        if (uVar9 <= uVar6) break;
        plVar2 = (long *)((long)plVar5 + lVar8);
        lVar8 = lVar8 + 8;
        lVar7 = *(long *)(*plVar2 + 0x10);
      }
    }
  }
  return 0;
}



/* address=00581ce0
   symbol=CGameClient::loadCharacter */

/* WARNING: Removing unreachable block (ram,0x00582cce) */
/* WARNING: Removing unreachable block (ram,0x00582b40) */
/* WARNING: Removing unreachable block (ram,0x00582cd9) */
/* WARNING: Removing unreachable block (ram,0x00582c53) */
/* WARNING: Removing unreachable block (ram,0x00582c17) */
/* WARNING: Removing unreachable block (ram,0x00582b35) */
/* WARNING: Removing unreachable block (ram,0x00582bab) */
/* CGameClient::loadCharacter(std::wstring const&, std::vector<CCharacter*,
   std::allocator<CCharacter*> >&, std::vector<CCharacterSaveState*,
   std::allocator<CCharacterSaveState*> >&, bool) */

CPlayer * __thiscall
CGameClient::loadCharacter
          (CGameClient *this,wstring_conflict *param_1,vector *param_2,vector *param_3,bool param_4)

{
  wchar_t *pwVar1;
  int *piVar2;
  int iVar3;
  wchar_t wVar4;
  undefined8 *puVar5;
  CResourceManager *pCVar6;
  char cVar7;
  long lVar8;
  CCharacterSaveState *pCVar9;
  CPlayer *this_00;
  CSharedStash *pCVar10;
  long *plVar11;
  CLevelState *this_01;
  wstring_conflict *pwVar12;
  void *pvVar13;
  CDungeonManager *pCVar14;
  CQuest *pCVar15;
  ulong uVar16;
  ushort uVar17;
  int iVar18;
  uint uVar19;
  uint uVar20;
  bool bVar21;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  CCharacter *local_f0;
  long local_e8 [2];
  long local_d8;
  CCharacterSaveState *local_d0;
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  wchar_t *local_88 [2];
  FILE *local_78;
  undefined4 local_6c;
  int local_68;
  int local_64;
  uint local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  uint local_4c;
  ushort local_46;
  ushort local_44 [5];
  CPlayer local_3a;
  char local_39 [9];

  _wfopen_s(&local_78,*(wchar_t **)param_1,L"rb");
  if (local_78 != (FILE *)0x0) {
    local_4c = 0;
    fseek(local_78,0,2);
    lVar8 = ftell(local_78);
    if ((int)lVar8 != 0) {
      uVar16 = (ulong)((int)lVar8 - 4);
      fseek(local_78,uVar16,0);
      fread(&local_4c,4,1,local_78);
      fseek(local_78,0,0);
      if ((ulong)local_4c == uVar16 + 4) {
        local_50 = 0;
        fread(&local_50,4,1,local_78);
        wcslen(L"");
        std::wstring::assign((wchar_t *)(this + 0x1a8),0x1001608);
        fread(local_44,2,1,local_78);
        FILESYSTEM::ReadWString((FILESYSTEM *)local_88,local_78,(uint)local_44[0]);
                    /* try { // try from 00581e60 to 00581ecf has its CatchHandler @ 00582b78 */
        fread(&local_54,4,1,local_78);
        *(undefined4 *)(this + 0x38ec) = local_54;
        fread(local_39,1,1,local_78);
        cVar7 = local_39[0];
        local_58 = 0;
        local_3a = (CPlayer)0x0;
        if (0xc < local_50) {
                    /* try { // try from 005829b3 to 005829d6 has its CatchHandler @ 00582b78 */
          fread(&local_58,4,1,local_78);
          fread(&local_3a,1,1,local_78);
        }
        pCVar9 = (CCharacterSaveState *)
                 Ogre::NedAllocImpl::allocBytes(0x228,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00581ed6 to 00581eda has its CatchHandler @ 00582c66 */
        CCharacterSaveState::CCharacterSaveState(pCVar9);
                    /* try { // try from 00581eed to 005821bb has its CatchHandler @ 00582b78 */
        CCharacterSaveState::load(pCVar9,local_78,local_50);
        *(undefined4 *)(this + 0x1090) = *(undefined4 *)(pCVar9 + 0x60);
        *(undefined4 *)(this + 0x1094) = *(undefined4 *)(pCVar9 + 100);
        this_00 = (CPlayer *)
                  CResourceManager::createPlayer
                            (*(CResourceManager **)(this + 0x2b8),local_88[0],true);
        CCharacter::setAlignment((CCharacter *)this_00,1);
        this_00[0xa15] = (CPlayer)(cVar7 != '\0');
        *(undefined4 *)(this_00 + 0xa10) = local_58;
        this_00[0xa14] = local_3a;
        (**(code **)(*(long *)this_00 + 0x2a0))(this_00,pCVar9);
        (**(code **)(*(long *)pCVar9 + 8))(pCVar9);
        pCVar10 = (CSharedStash *)CSharedStash::getSingleton();
        CSharedStash::setPlayer(pCVar10,this_00);
        fread(&local_46,2,1,local_78);
        if (local_46 != 0) {
          uVar17 = 0;
          do {
            fread(&local_d0,8,1,local_78);
            *(CCharacterSaveState **)(this_00 + (ulong)uVar17 * 8 + 0x8b0) = local_d0;
            if (local_d0 != (CCharacterSaveState *)0xffffffffffffffff) {
              *(undefined8 *)(this_00 + (ulong)uVar17 * 8 + 0x900) = 0xffffffffffffffff;
            }
            uVar17 = uVar17 + 1;
          } while (uVar17 < local_46);
        }
        fread(&local_46,2,1,local_78);
        if (local_46 != 0) {
          uVar17 = 0;
          do {
            while( true ) {
              fread(&local_d0,8,1,local_78);
              CPlayer::setMappedFunctionSkill(this_00,(uint)uVar17,(longlong)local_d0);
              if (local_50 < 0xc) break;
              fread(&local_d0,8,1,local_78);
              CPlayer::setLeftMappedFunctionSkill(this_00,(uint)uVar17,(longlong)local_d0);
              uVar17 = uVar17 + 1;
              if (local_46 <= uVar17) goto LAB_005820c6;
            }
            uVar17 = uVar17 + 1;
          } while (uVar17 < local_46);
        }
LAB_005820c6:
        fread(&local_46,2,1,local_78);
        if (local_46 != 0) {
          uVar17 = 0;
          do {
            fread(&local_d0,8,1,local_78);
            *(CCharacterSaveState **)(this_00 + (ulong)uVar17 * 8 + 0x900) = local_d0;
            if (local_d0 != (CCharacterSaveState *)0xffffffffffffffff) {
              *(undefined8 *)(this_00 + (ulong)uVar17 * 8 + 0x8b0) = 0xffffffffffffffff;
            }
            uVar17 = uVar17 + 1;
          } while (uVar17 < local_46);
        }
        iVar18 = 0;
        do {
          fread(&local_d0,4,1,local_78);
          CPlayer::setJournalStatistic(this_00,iVar18,(ulong)local_d0 & 0xffffffff);
          iVar18 = iVar18 + 1;
        } while (iVar18 != 0x12);
        fread(local_44,2,1,local_78);
        FILESYSTEM::ReadWString((FILESYSTEM *)local_98,local_78,(uint)local_44[0]);
                    /* try { // try from 005821cf to 005821d3 has its CatchHandler @ 00582c5e */
        std::wstring::wstring((wstring_conflict *)local_a8,(wstring_conflict *)local_98);
                    /* try { // try from 005821dc to 005821e0 has its CatchHandler @ 00582c4e */
        setCurrentDungeon(this,(wstring_conflict *)local_a8);
        if ((allocator *)(local_a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_a8[0] + -8);
          iVar18 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar18 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
          }
        }
                    /* try { // try from 0058220e to 0058225c has its CatchHandler @ 00582c5e */
        std::wstring::assign((wstring_conflict *)(this + 0x1098));
        if (1 < local_50) {
          fread(local_44,2,1,local_78);
          FILESYSTEM::ReadWString((FILESYSTEM *)local_b8,local_78,(uint)local_44[0]);
                    /* try { // try from 00582268 to 0058226c has its CatchHandler @ 00582ba9 */
          std::wstring::assign((wstring_conflict *)local_98);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar18 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar18 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
                    /* try { // try from 00582293 to 0058235f has its CatchHandler @ 00582c5e */
          std::wstring::assign((wstring_conflict *)(this_00 + 2000));
          fread(&local_d0,4,1,local_78);
          *(undefined4 *)(this_00 + 0x7cc) = local_d0._0_4_;
        }
        fread(local_39,1,1,local_78);
        this_00[0x7b0] = (CPlayer)(local_39[0] != '\0');
        fread(&local_108,0xc,1,local_78);
        *(undefined4 *)(this_00 + 0x7c4) = local_104;
        *(undefined4 *)(this_00 + 0x7c0) = local_108;
        *(undefined4 *)(this_00 + 0x7c8) = local_100;
        fread(local_44,2,1,local_78);
        FILESYSTEM::ReadWString((FILESYSTEM *)local_c8,local_78,(uint)local_44[0]);
                    /* try { // try from 0058236b to 0058236f has its CatchHandler @ 00582b4b */
        std::wstring::assign((wstring_conflict *)local_98);
        if ((allocator *)(local_c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_c8[0] + -8);
          iVar18 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar18 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
          }
        }
                    /* try { // try from 00582396 to 0058244a has its CatchHandler @ 00582c5e */
        std::wstring::assign((wstring_conflict *)(this_00 + 0x7b8));
        fread(&local_5c,4,1,local_78);
        *(undefined4 *)(this_00 + 0x7b4) = local_5c;
        local_60 = 0;
        fread(&local_60,4,1,local_78);
        if (local_60 != 0) {
          uVar19 = 0;
          do {
            while( true ) {
              pCVar9 = (CCharacterSaveState *)
                       Ogre::NedAllocImpl::allocBytes(0x228,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00582451 to 00582455 has its CatchHandler @ 00582bb6 */
              CCharacterSaveState::CCharacterSaveState(pCVar9);
              local_d0 = pCVar9;
                    /* try { // try from 0058246d to 00582629 has its CatchHandler @ 00582c5e */
              CCharacterSaveState::load(pCVar9,local_78,local_50);
              if (!param_4) break;
              if (local_d0 != (CCharacterSaveState *)0x0) {
                (**(code **)(*(long *)local_d0 + 8))();
                local_d0 = (CCharacterSaveState *)0x0;
              }
LAB_00582429:
              uVar19 = uVar19 + 1;
              if (local_60 <= uVar19) goto LAB_0058254d;
            }
            plVar11 = (long *)CResourceManager::createUnit
                                        (*(CResourceManager **)(this + 0x2b8),
                                         *(longlong *)(local_d0 + 0x20),*(int *)(local_d0 + 0xd0),
                                         true,false);
            if (plVar11 == (long *)0x0) {
              local_f0 = (CCharacter *)0x0;
              goto LAB_00582429;
            }
            local_f0 = (CCharacter *)
                       __dynamic_cast(plVar11,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
            if (local_f0 == (CCharacter *)0x0) {
              (**(code **)(*plVar11 + 8))(plVar11);
              goto LAB_00582429;
            }
            CCharacter::setAlignment(local_f0,1);
            puVar5 = *(undefined8 **)(param_2 + 8);
            if (puVar5 == *(undefined8 **)(param_2 + 0x10)) {
              std::vector<CCharacter*,std::allocator<CCharacter*>>::_M_insert_aux
                        ((vector<CCharacter*,std::allocator<CCharacter*>> *)param_2,puVar5,&local_f0
                        );
            }
            else {
              lVar8 = 0;
              if (puVar5 != (undefined8 *)0x0) {
                *puVar5 = local_f0;
                lVar8 = *(long *)(param_2 + 8);
              }
              *(long *)(param_2 + 8) = lVar8 + 8;
            }
            puVar5 = *(undefined8 **)(param_3 + 8);
            if (puVar5 == *(undefined8 **)(param_3 + 0x10)) {
                    /* try { // try from 005829e2 to 005829fa has its CatchHandler @ 00582c5e */
              std::vector<CCharacterSaveState*,std::allocator<CCharacterSaveState*>>::_M_insert_aux
                        ((vector<CCharacterSaveState*,std::allocator<CCharacterSaveState*>> *)
                         param_3,puVar5,&local_d0);
              goto LAB_00582429;
            }
            lVar8 = 0;
            if (puVar5 != (undefined8 *)0x0) {
              *puVar5 = local_d0;
              lVar8 = *(long *)(param_3 + 8);
            }
            uVar19 = uVar19 + 1;
            *(long *)(param_3 + 8) = lVar8 + 8;
          } while (uVar19 < local_60);
        }
LAB_0058254d:
        bVar21 = local_50 == 10;
        uVar19 = 0;
        do {
          fread(&local_d0,1,1,local_78);
          this_00[(long)(int)uVar19 + 0xa17] = (CPlayer)((char)local_d0 != '\0');
          uVar19 = uVar19 + 1;
        } while (uVar19 < bVar21 + 0x22);
        local_64 = 0;
        fread(&local_64,4,1,local_78);
        if (0 < local_64) {
          iVar18 = 0;
          do {
            while( true ) {
              this_01 = (CLevelState *)
                        Ogre::NedAllocImpl::allocBytes(0xb8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00582632 to 00582636 has its CatchHandler @ 00582cec */
              CLevelState::CLevelState(this_01,0);
                    /* try { // try from 00582649 to 005826d4 has its CatchHandler @ 00582c5e */
              CLevelState::load(this_01,local_78,local_50);
              puVar5 = *(undefined8 **)(this_00 + 0x7a0);
              local_f0 = (CCharacter *)this_01;
              if (puVar5 != *(undefined8 **)(this_00 + 0x7a8)) break;
              std::vector<CLevelState*,std::allocator<CLevelState*>>::_M_insert_aux
                        ((vector<CLevelState*,std::allocator<CLevelState*>> *)(this_00 + 0x798),
                         puVar5,&local_f0);
              iVar18 = iVar18 + 1;
              if (local_64 <= iVar18) goto LAB_0058267c;
            }
            lVar8 = 0;
            if (puVar5 != (undefined8 *)0x0) {
              *puVar5 = this_01;
              lVar8 = *(long *)(this_00 + 0x7a0);
            }
            iVar18 = iVar18 + 1;
            *(long *)(this_00 + 0x7a0) = lVar8 + 8;
          } while (iVar18 < local_64);
        }
LAB_0058267c:
        local_68 = 0;
        fread(&local_68,4,1,local_78);
        if (0 < local_68) {
          iVar18 = 0;
          do {
            std::wstring::wstring
                      ((wstring_conflict *)&local_d8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 005826e0 to 005826e4 has its CatchHandler @ 00582ce4 */
            pwVar12 = (wstring_conflict *)
                      Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005826ee to 005826f2 has its CatchHandler @ 00582bff */
            std::wstring::wstring(pwVar12,(wstring_conflict *)&local_d8);
            *(undefined4 *)(pwVar12 + 8) = 0;
            *(undefined4 *)(pwVar12 + 0xc) = 0;
            *(undefined4 *)(pwVar12 + 0x10) = 0;
            *(undefined8 *)(pwVar12 + 0x18) = 0;
            *(undefined8 *)(pwVar12 + 0x20) = 0;
            *(undefined8 *)(pwVar12 + 0x28) = 0;
            if ((allocator *)(local_d8 + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_d8 + -8);
              iVar3 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar3 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_d8 + -0x18));
              }
            }
                    /* try { // try from 00582749 to 005827f8 has its CatchHandler @ 00582c5e */
            CDungeonTracker::load((CDungeonTracker *)pwVar12,local_78,local_50);
            uVar19 = *(uint *)(this_00 + 0xa48);
            if (uVar19 < *(uint *)(this_00 + 0xa4c)) {
              pvVar13 = *(void **)(this_00 + 0xa40);
            }
            else if (*(long *)(this_00 + 0xa40) == 0) {
              *(uint *)(this_00 + 0xa4c) = *(uint *)(this_00 + 0xa50);
              pvVar13 = operator_new__((ulong)*(uint *)(this_00 + 0xa50) << 3);
              *(void **)(this_00 + 0xa40) = pvVar13;
              uVar19 = *(uint *)(this_00 + 0xa48);
            }
            else {
              uVar20 = *(uint *)(this_00 + 0xa4c) + *(int *)(this_00 + 0xa50);
              pvVar13 = operator_new__((ulong)uVar20 << 3);
              if (*(int *)(this_00 + 0xa4c) != 0) {
                uVar16 = 0;
                do {
                  uVar19 = (int)uVar16 + 1;
                  *(undefined8 *)((long)pvVar13 + uVar16 * 8) =
                       *(undefined8 *)(*(long *)(this_00 + 0xa40) + uVar16 * 8);
                  uVar16 = (ulong)uVar19;
                } while (uVar19 < *(uint *)(this_00 + 0xa4c));
              }
              if (*(void **)(this_00 + 0xa40) != (void *)0x0) {
                operator_delete__(*(void **)(this_00 + 0xa40));
              }
              uVar19 = *(uint *)(this_00 + 0xa48);
              *(void **)(this_00 + 0xa40) = pvVar13;
              *(uint *)(this_00 + 0xa4c) = uVar20;
            }
            *(wstring_conflict **)((long)pvVar13 + (ulong)uVar19 * 8) = pwVar12;
            *(int *)(this_00 + 0xa48) = *(int *)(this_00 + 0xa48) + 1;
            std::wstring::wstring((wstring_conflict *)local_e8,pwVar12);
                    /* try { // try from 005827f9 to 00582808 has its CatchHandler @ 00582bef */
            pCVar14 = (CDungeonManager *)CDungeonManager::getSingleton();
            lVar8 = CDungeonManager::getDungeonByName(pCVar14,(wstring_conflict *)local_e8);
            if ((allocator *)(local_e8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_e8[0] + -8);
              iVar3 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar3 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
              }
            }
            if (lVar8 != 0) {
              *(undefined4 *)(lVar8 + 0x58) = *(undefined4 *)(pwVar12 + 0x10);
            }
            iVar18 = iVar18 + 1;
          } while (iVar18 < local_68);
        }
        local_6c = 0;
        if (*(CQuestManager **)(this + 0x68) == (CQuestManager *)0x0) {
                    /* try { // try from 00582a35 to 00582acf has its CatchHandler @ 00582c5e */
          fread(&local_6c,4,1,local_78);
        }
        else {
                    /* try { // try from 0058285d to 00582986 has its CatchHandler @ 00582c5e */
          CQuestManager::setPlayer(*(CQuestManager **)(this + 0x68),this_00);
          CQuestManager::load(*(CQuestManager **)(this + 0x68),local_78,local_50,
                              *(CResourceManager **)(this + 0x2b8));
        }
        fclose(local_78);
        pCVar10 = (CSharedStash *)CSharedStash::getSingleton();
        CSharedStash::setPlayer(pCVar10,this_00);
        pCVar6 = *(CResourceManager **)(this + 0x2b8);
        pCVar10 = (CSharedStash *)CSharedStash::getSingleton();
        CSharedStash::loadSharedStash(pCVar10,pCVar6,(CCharacter *)0x0);
        uVar19 = KSETTINGS_GAME_COMPLETED_ONCE;
        if (*(long *)(this + 0x68) != 0) {
          lVar8 = CMasterResourceManager::getSingleton();
          iVar18 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar19);
          uVar19 = KSETTINGS_RETIREE_QUEST;
          if (iVar18 == 1) {
            lVar8 = CMasterResourceManager::getSingleton();
            pwVar12 = (wstring_conflict *)
                      CDynamicPropertyFile::GetString
                                (*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar19);
            pCVar15 = (CQuest *)
                      CQuestManager::getQuestByName(*(CQuestManager **)(this + 0x68),pwVar12);
            uVar19 = KSETTINGS_RETIREE_QUEST;
            if (pCVar15 != (CQuest *)0x0) {
              lVar8 = CMasterResourceManager::getSingleton();
              pwVar12 = (wstring_conflict *)
                        CDynamicPropertyFile::GetString
                                  (*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar19);
              cVar7 = CQuestManager::getQuestComplete(*(CQuestManager **)(this + 0x68),pwVar12);
              if (cVar7 == '\0') {
                CQuestManager::giveQuest
                          (*(CQuestManager **)(this + 0x68),pCVar15,(CBaseUnit *)0x0,true);
                CQuestManager::completeQuest(*(CQuestManager **)(this + 0x68),pCVar15);
              }
            }
          }
        }
        if ((allocator *)(local_98[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_98[0] + -8);
          iVar18 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar18 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
          }
        }
        if ((allocator *)(local_88[0] + -6) ==
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          return this_00;
        }
        LOCK();
        pwVar1 = local_88[0] + -2;
        wVar4 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (L'\0' < wVar4) {
          return this_00;
        }
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
        return this_00;
      }
    }
    fclose(local_78);
  }
  return (CPlayer *)0x0;
}



/* address=00582d00
   symbol=CGameClient::setCreationClass */

/* WARNING: Removing unreachable block (ram,0x00582e6f) */
/* CGameClient::setCreationClass(std::wstring) */

void __thiscall CGameClient::setCreationClass(CGameClient *this,undefined8 *param_2)

{
  int *piVar1;
  size_t __n;
  int iVar2;
  CCharacter *pCVar3;
  long local_28 [3];

  __n = *(size_t *)(*(wchar_t **)(this + 0x1a8) + -6);
  if ((__n != *(size_t *)((wchar_t *)*param_2 + -6)) ||
     (iVar2 = wmemcmp(*(wchar_t **)(this + 0x1a8),(wchar_t *)*param_2,__n), iVar2 != 0)) {
    std::wstring::assign((wstring_conflict *)(this + 0x1a8));
    CGameUI::setPlayer(*(CGameUI **)(this + 0x78),(CCharacter *)0x0);
    CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x58),true);
    if (*(long **)(this + 0x58) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x58) + 8))();
      *(undefined8 *)(this + 0x58) = 0;
    }
    pCVar3 = (CCharacter *)
             CResourceManager::createPlayer
                       (*(CResourceManager **)(*(long *)(this + 0x70) + 0x138),
                        *(wchar_t **)(this + 0x1a8),false);
    *(CCharacter **)(this + 0x58) = pCVar3;
    CCharacter::setAlignment(pCVar3,1);
    CPlayer::firstTimeSetup(*(CPlayer **)(this + 0x58));
    std::wstring::wstring
              ((wstring_conflict *)local_28,(wstring_conflict *)(*(long *)(this + 0x78) + 0x16b0));
                    /* try { // try from 00582dbb to 00582dbf has its CatchHandler @ 00582e5c */
    std::wstring::assign((wstring_conflict *)(*(long *)(this + 0x58) + 0x4c0));
    if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_28[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
      }
    }
    pCVar3 = (CCharacter *)0x0;
    if (*(CCharacter **)(this + 0x58) != (CCharacter *)0x0) {
      CLevel::addCharacter
                (*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x58),
                 (Vector3 *)(*(CLevel **)(this + 0x70) + 0x140),false);
      CCharacter::setToward
                (*(CCharacter **)(this + 0x58),(Vector3 *)(*(long *)(this + 0x70) + 0x164));
      pCVar3 = *(CCharacter **)(this + 0x58);
    }
    CGameUI::setPlayer(*(CGameUI **)(this + 0x78),pCVar3);
  }
  *(undefined4 *)(this + 0x1038) = 3;
  return;
}



/* address=00582e80
   symbol=CGameClient::refreshLighting */

/* WARNING: Removing unreachable block (ram,0x005839a4) */
/* WARNING: Removing unreachable block (ram,0x00583a51) */
/* WARNING: Removing unreachable block (ram,0x00583a89) */
/* WARNING: Removing unreachable block (ram,0x00583a6d) */
/* WARNING: Removing unreachable block (ram,0x00583a5f) */
/* WARNING: Removing unreachable block (ram,0x00583a7b) */
/* WARNING: Removing unreachable block (ram,0x00583a43) */
/* WARNING: Removing unreachable block (ram,0x00583a35) */
/* WARNING: Removing unreachable block (ram,0x00583a27) */
/* CGameClient::refreshLighting() */

void __thiscall CGameClient::refreshLighting(CGameClient *this)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  ColourValue *pCVar10;
  long *plVar11;
  undefined8 uVar12;
  long lVar13;
  float fVar14;
  float fVar15;
  undefined **local_178;
  long *local_170;
  int *local_168;
  float local_158;
  float local_154;
  float local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  long local_d8 [2];
  long local_c8 [2];
  wchar_t *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  wchar_t *local_88 [2];
  long local_78 [2];
  long local_68 [2];
  wchar_t *local_58 [2];
  float local_48 [3];
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  local_f8 = Ogre::ColourValue::ZERO;
  local_f0 = DAT_01424708;
  if (*(int *)(this + 0x38d0) == 0) {
    (**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x268))(DAT_00fa8724);
  }
  else {
    iVar6 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_NETBOOK_MODE);
    if (iVar6 != 1) {
      (**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x268))(DAT_00fa481c);
      lVar13 = *(long *)(this + 0x70);
      goto joined_r0x00583540;
    }
    (**(code **)(**(long **)(*(long *)(this + 0x20) + 0x10) + 0x268))(DAT_00fa4818);
  }
  lVar13 = *(long *)(this + 0x70);
joined_r0x00583540:
  if ((lVar13 == 0) || (lVar13 = *(long *)(lVar13 + 0x1d8), lVar13 == 0)) {
    pCVar10 = (ColourValue *)
              (**(code **)(**(long **)(this + 0x1050) + 0x58))(*(long **)(this + 0x1050),0);
    local_12c = 0x3f800000;
    local_138 = 0;
    local_134 = 0;
    local_130 = 0;
    Ogre::Viewport::setBackgroundColour(pCVar10);
    local_148 = 0x3df0f0f1;
    local_144 = 0x3e28a8a9;
    local_140 = 0x3e68e8e9;
    local_13c = 0x3f800000;
    Ogre::SceneManager::setFog
              (0,DAT_00fa873c,DAT_00fa8738,*(undefined8 *)(this + 0x28),3,&local_148);
    uVar4 = KSETTINGS_AMBIENT_LIGHT_BLUE;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    uVar4 = KSETTINGS_AMBIENT_LIGHT_GREEN;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    uVar4 = KSETTINGS_AMBIENT_LIGHT_RED;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    fVar15 = DAT_00fa8740;
    local_14c = 0x3f800000;
    local_158 = (float)iVar8 / DAT_00fa8740;
    local_154 = (float)iVar7 / DAT_00fa8740;
    local_150 = (float)iVar6 / DAT_00fa8740;
    Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x28));
    uVar4 = KSETTINGS_F_DIRECTIONAL_INTENSITY;
    lVar13 = CMasterResourceManager::getSingleton();
    fVar14 = (float)CDynamicPropertyFile::GetFloat(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_BLUE;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_GREEN;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_RED;
    lVar13 = CMasterResourceManager::getSingleton();
    iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar4);
    local_14c = 0x3f800000;
    local_150 = ((float)iVar6 / fVar15) * fVar14;
    local_154 = ((float)iVar7 / fVar15) * fVar14;
    local_158 = ((float)iVar8 / fVar15) * fVar14;
    Ogre::Light::setDiffuseColour(*(ColourValue **)(this + 0x38c8));
  }
  else {
    local_f8 = *(undefined8 *)(lVar13 + 0x720);
    local_f0 = *(undefined8 *)(lVar13 + 0x728);
    Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x28));
    local_f8 = *(undefined8 *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x740);
    local_f0 = *(undefined8 *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x748);
    Ogre::Light::setDiffuseColour(*(ColourValue **)(this + 0x38c8));
    lVar13 = *(long *)(*(long *)(this + 0x70) + 0x1d8);
    local_e4 = *(undefined4 *)(lVar13 + 0x754);
    local_e8 = *(undefined4 *)(lVar13 + 0x750);
    local_e0 = *(undefined4 *)(lVar13 + 0x758);
    Ogre::Light::setPosition(*(Vector3 **)(this + 0x38c8));
    puVar9 = (uint *)Ogre::Light::getPosition();
    local_154 = (float)(puVar9[1] ^ DAT_00fa8780);
    local_158 = (float)(*puVar9 ^ DAT_00fa8780);
    local_150 = (float)(puVar9[2] ^ DAT_00fa8780);
    fVar15 = SQRT(local_158 * local_158 + local_154 * local_154 + local_150 * local_150);
    if (DAT_00fa87a0 < (double)fVar15) {
      fVar15 = DAT_00fa47fc / fVar15;
      local_158 = local_158 * fVar15;
      local_154 = local_154 * fVar15;
      local_150 = local_150 * fVar15;
    }
    Ogre::Light::setDirection(*(Vector3 **)(this + 0x38c8));
    CLevel::updateMaterialAmbient(*(CLevel **)(this + 0x70));
    pCVar10 = (ColourValue *)
              (**(code **)(**(long **)(this + 0x1050) + 0x58))(*(long **)(this + 0x1050),0);
    lVar13 = *(long *)(*(long *)(this + 0x70) + 0x1d8);
    local_104 = *(undefined4 *)(lVar13 + 0x714);
    local_100 = *(undefined4 *)(lVar13 + 0x718);
    local_108 = *(undefined4 *)(lVar13 + 0x710);
    local_fc = *(undefined4 *)(lVar13 + 0x71c);
    Ogre::Viewport::setBackgroundColour(pCVar10);
    iVar6 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_NETBOOK_MODE);
    fVar15 = DAT_00fa47fc;
    if (iVar6 != 1) {
      fVar15 = DAT_00fa8728;
    }
    lVar13 = *(long *)(*(long *)(this + 0x70) + 0x1d8);
    local_110 = *(undefined4 *)(lVar13 + 0x718);
    local_118 = *(undefined4 *)(lVar13 + 0x710);
    local_114 = *(undefined4 *)(lVar13 + 0x714);
    local_10c = *(undefined4 *)(lVar13 + 0x71c);
    Ogre::SceneManager::setFog
              (0,fVar15 * *(float *)(lVar13 + 0x6f8),*(float *)(lVar13 + 0x6fc) * fVar15,
               *(undefined8 *)(this + 0x28),3,&local_118);
    plVar11 = *(long **)(this + 0x210);
    if (plVar11 != (long *)0x0) {
      (**(code **)(*plVar11 + 0x2b0))(&local_178,plVar11,0,0);
                    /* try { // try from 0058319f to 005831a4 has its CatchHandler @ 005839e4 */
      plVar11 = (long *)(**(code **)(*local_170 + 0x80))(local_170,0);
      local_178 = &PTR__SharedPtr_00fa85d0;
      if ((local_168 != (int *)0x0) &&
         (iVar6 = *local_168, *local_168 = iVar6 + -1, iVar6 + -1 == 0)) {
        (*(code *)PTR_destroy_00fa85e0)(&local_178);
      }
      lVar13 = *(long *)(*(long *)(this + 0x70) + 0x1d8);
      local_124 = *(undefined4 *)(lVar13 + 0x704);
      local_128 = *(undefined4 *)(lVar13 + 0x700);
      local_120 = *(undefined4 *)(lVar13 + 0x708);
      local_11c = *(undefined4 *)(lVar13 + 0x70c);
      pCVar10 = (ColourValue *)(**(code **)(*plVar11 + 0x58))(plVar11,0);
      Ogre::Viewport::setBackgroundColour(pCVar10);
      uVar5 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x270));
      uVar5 = Ogre::Technique::getPass(uVar5);
      uVar12 = Ogre::Pass::getTextureUnitState(uVar5);
                    /* try { // try from 00583267 to 0058326b has its CatchHandler @ 005839f7 */
      std::wstring::wstring
                ((wstring_conflict *)local_58,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6d0));
                    /* try { // try from 00583287 to 0058328b has its CatchHandler @ 005839f9 */
      std::wstring::wstring((wstring_conflict *)local_68,local_58[0],local_39);
                    /* try { // try from 0058329a to 0058329e has its CatchHandler @ 00583a06 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_78);
                    /* try { // try from 005832aa to 005832ae has its CatchHandler @ 00583a13 */
      Ogre::TextureUnitState::setTextureName(uVar12,(wstring_conflict *)local_78,2);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_78[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_68[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
        }
      }
      if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar1 = local_58[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
        }
      }
      uVar5 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x250));
      uVar5 = Ogre::Technique::getPass(uVar5);
      uVar12 = Ogre::Pass::getTextureUnitState(uVar5);
                    /* try { // try from 0058333d to 00583341 has its CatchHandler @ 00583a22 */
      std::wstring::wstring
                ((wstring_conflict *)local_88,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6e0));
                    /* try { // try from 0058335d to 00583361 has its CatchHandler @ 005839d6 */
      std::wstring::wstring((wstring_conflict *)local_98,local_88[0],&local_3a);
                    /* try { // try from 00583370 to 00583374 has its CatchHandler @ 005839d8 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_a8);
                    /* try { // try from 00583382 to 00583386 has its CatchHandler @ 005839e2 */
      Ogre::TextureUnitState::setTextureName(uVar12,(wstring_conflict *)local_a8,2);
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_a8[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_98[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
      if ((allocator *)(local_88[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar1 = local_88[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
        }
      }
      uVar5 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x290));
      uVar5 = Ogre::Technique::getPass(uVar5);
      uVar12 = Ogre::Pass::getTextureUnitState(uVar5);
                    /* try { // try from 0058340a to 0058340e has its CatchHandler @ 00583999 */
      std::wstring::wstring
                ((wstring_conflict *)local_b8,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6e8));
                    /* try { // try from 0058342a to 0058342e has its CatchHandler @ 005839af */
      std::wstring::wstring((wstring_conflict *)local_c8,local_b8[0],&local_3b);
                    /* try { // try from 0058343d to 00583441 has its CatchHandler @ 005839bc */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_d8);
                    /* try { // try from 0058344f to 00583453 has its CatchHandler @ 005839c9 */
      Ogre::TextureUnitState::setTextureName(uVar12,(wstring_conflict *)local_d8,2);
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_d8[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_c8[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
      if ((allocator *)(local_b8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar1 = local_b8[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
        }
      }
      this[0x38d4] = (CGameClient)0x1;
    }
    plVar11 = *(long **)(*(long *)(this + 0x20) + 0x30);
    if (plVar11 != (long *)0x0) {
      if (*(char *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x760) == '\0') {
        (**(code **)(*plVar11 + 0x368))(plVar11,1);
        local_48[0] = DAT_00fa8734 * Ogre::Math::fDeg2Rad;
        (**(code **)(*plVar11 + 0x248))(plVar11,local_48);
        (**(code **)(*plVar11 + 0x2b8))(plVar11);
      }
      else {
        (**(code **)(*plVar11 + 0x368))(plVar11,0);
        (**(code **)(*plVar11 + 0x2b0))(DAT_00fa872c,DAT_00fa8730,plVar11);
      }
    }
  }
  return;
}



/* address=00583aa0
   symbol=CGameClient::resetShadows */

/* WARNING: Removing unreachable block (ram,0x00584443) */
/* WARNING: Removing unreachable block (ram,0x00584435) */
/* WARNING: Removing unreachable block (ram,0x00584427) */
/* WARNING: Removing unreachable block (ram,0x005843af) */
/* CGameClient::resetShadows(bool) */

void __thiscall CGameClient::resetShadows(CGameClient *this,bool param_1)

{
  int *piVar1;
  string *psVar2;
  code *pcVar3;
  uint uVar4;
  bool bVar5;
  int iVar6;
  undefined4 uVar7;
  long lVar8;
  long *plVar9;
  undefined8 uVar10;
  ColourValue *pCVar11;
  undefined8 in_stack_fffffffffffffe58;
  undefined4 uVar12;
  undefined **local_168;
  long *local_160;
  int *local_158;
  undefined **local_148;
  undefined8 local_140;
  int *local_138;
  undefined **local_128;
  long *local_120;
  int *local_118;
  undefined **local_108;
  undefined8 local_100;
  int *local_f8;
  undefined **local_e8 [2];
  int *local_d8;
  undefined **local_c8;
  long *local_c0;
  int *local_b8;
  undefined **local_a8;
  long *local_a0;
  int *local_98;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29;

  uVar4 = KSETTINGS_SHADOWS_ENABLED;
  uVar12 = (undefined4)((ulong)in_stack_fffffffffffffe58 >> 0x20);
  lVar8 = CMasterResourceManager::getSingleton();
  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar4);
  uVar4 = KSETTINGS_SHADOWS_ENABLED;
  lVar8 = CMasterResourceManager::getSingleton();
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar4,(uint)param_1);
  if (*(CLevel **)(this + 0x70) != (CLevel *)0x0) {
    CLevel::clearProjectorPass
              (*(CLevel **)(this + 0x70),*(CGenericModel **)(this + 0x1068),
               *(CGenericModel **)(this + 0x1070));
  }
  uVar4 = KSETTINGS_SHADOWS_ENABLED;
  lVar8 = CMasterResourceManager::getSingleton();
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar4,(uint)(iVar6 != 0));
  plVar9 = *(long **)(this + 0x208);
  if (plVar9 != (long *)0x0) {
    (**(code **)(*plVar9 + 0x2b0))(&local_a8,plVar9,0,0);
                    /* try { // try from 00583b62 to 00583b67 has its CatchHandler @ 005843fe */
    plVar9 = (long *)(**(code **)(*local_a0 + 0x80))(local_a0,0);
    local_a8 = &PTR__SharedPtr_00fa85d0;
    if ((local_98 != (int *)0x0) && (iVar6 = *local_98, *local_98 = iVar6 + -1, iVar6 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa85e0)(&local_a8);
    }
    (**(code **)(*plVar9 + 0xd0))(plVar9);
    (**(code **)(*plVar9 + 0x68))(plVar9);
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    pcVar3 = *(code **)(*plVar9 + 0xa0);
    uVar10 = (**(code **)(**(long **)(this + 0x208) + 200))();
    (*pcVar3)((SharedPtr<Ogre::Resource> *)local_e8,plVar9,uVar10);
                    /* try { // try from 00583be0 to 00583bf3 has its CatchHandler @ 005843e7 */
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    (**(code **)(*plVar9 + 0x80))(plVar9,(SharedPtr<Ogre::Resource> *)local_e8);
    local_e8[0] = &PTR__SharedPtr_00fa45d0;
    if ((local_d8 != (int *)0x0) && (iVar6 = *local_d8, *local_d8 = iVar6 + -1, iVar6 + -1 == 0)) {
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)local_e8);
    }
  }
  plVar9 = *(long **)(this + 0x210);
  if (plVar9 != (long *)0x0) {
    (**(code **)(*plVar9 + 0x2b0))(&local_c8,plVar9,0,0);
                    /* try { // try from 00583c51 to 00583c56 has its CatchHandler @ 005843cd */
    plVar9 = (long *)(**(code **)(*local_c0 + 0x80))(local_c0,0);
    local_c8 = &PTR__SharedPtr_00fa85d0;
    if ((local_b8 != (int *)0x0) && (iVar6 = *local_b8, *local_b8 = iVar6 + -1, iVar6 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa85e0)(&local_c8);
    }
    (**(code **)(*plVar9 + 0xd0))(plVar9);
    (**(code **)(*plVar9 + 0x68))(plVar9);
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    pcVar3 = *(code **)(*plVar9 + 0xa0);
    uVar10 = (**(code **)(**(long **)(this + 0x210) + 200))();
    (*pcVar3)((SharedPtr<Ogre::Resource> *)local_e8,plVar9,uVar10);
                    /* try { // try from 00583ccf to 00583ce2 has its CatchHandler @ 005843ba */
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    (**(code **)(*plVar9 + 0x80))(plVar9,(SharedPtr<Ogre::Resource> *)local_e8);
    local_e8[0] = &PTR__SharedPtr_00fa45d0;
    if ((local_d8 != (int *)0x0) && (iVar6 = *local_d8, *local_d8 = iVar6 + -1, iVar6 + -1 == 0)) {
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)local_e8);
    }
  }
  plVar9 = (long *)Ogre::TextureManager::getSingleton();
  (**(code **)(*plVar9 + 0x70))(plVar9,1);
  *(undefined8 *)(this + 0x208) = 0;
  *(undefined8 *)(this + 0x210) = 0;
  uVar7 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_SHADOW_RESOLUTION);
  uVar4 = KSETTINGS_SHADOWS_ENABLED;
  lVar8 = CMasterResourceManager::getSingleton();
  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar4);
  if (iVar6 != 0) {
                    /* try { // try from 00583d7f to 00583d83 has its CatchHandler @ 005843e2 */
    std::string::string((string *)&local_38,"ProjectorRTT",&local_29);
                    /* try { // try from 00583d92 to 00583d96 has its CatchHandler @ 00584422 */
    STRINGS::uniqueName((STRINGS *)local_48,(string *)&local_38);
                    /* try { // try from 00583da4 to 00583da8 has its CatchHandler @ 005843e9 */
    std::string::assign((string *)(this + 0x38f0));
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    uVar10 = CONCAT44(uVar12,uVar7);
    (**(code **)(*plVar9 + 0x140))
              (&local_108,plVar9,(string *)(this + 0x38f0),
               &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,uVar7,uVar10,1,0,10,0x200,
               0,0,0);
    uVar12 = (undefined4)((ulong)uVar10 >> 0x20);
    *(undefined8 *)(this + 0x208) = local_100;
    local_108 = &PTR__SharedPtr_00fa86b0;
    if ((local_f8 != (int *)0x0) && (iVar6 = *local_f8, *local_f8 = iVar6 + -1, iVar6 + -1 == 0)) {
      (*(code *)PTR_destroy_00fa86c0)(&local_108);
    }
    (**(code **)(**(long **)(this + 0x208) + 0x2b0))(&local_128,*(long **)(this + 0x208),0,0);
                    /* try { // try from 00583eb3 to 00583eb8 has its CatchHandler @ 0058439c */
    plVar9 = (long *)(**(code **)(*local_120 + 0x80))(local_120,0);
    local_128 = &PTR__SharedPtr_00fa85d0;
    if ((local_118 != (int *)0x0) && (iVar6 = *local_118, *local_118 = iVar6 + -1, iVar6 + -1 == 0))
    {
      (*(code *)PTR_destroy_00fa85e0)(&local_128);
    }
    (**(code **)(*plVar9 + 0x48))
              (0,0,DAT_00fa47fc,plVar9,*(undefined8 *)(*(long *)(this + 0x20) + 0x30),0);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setShadowsEnabled(bVar5);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setClearEveryFrame(bVar5,1);
    local_78 = 0x3f000000;
    local_74 = 0x3f000000;
    local_70 = 0x3f000000;
    local_6c = 0x3f800000;
    pCVar11 = (ColourValue *)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setBackgroundColour(pCVar11);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setOverlaysEnabled(bVar5);
    (**(code **)(*plVar9 + 0xf8))(plVar9,1);
    (**(code **)(*plVar9 + 0xc0))(plVar9,this + 0x10);
  }
  uVar4 = KSETTINGS_LIGHTING_ENABLED;
  lVar8 = CMasterResourceManager::getSingleton();
  psVar2 = (string *)(this + 0x38f8);
  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar4);
  if (iVar6 != 0) {
                    /* try { // try from 0058400b to 0058400f has its CatchHandler @ 0058441c */
    std::string::string((string *)local_58,"ProjectorRTTLight",&local_2a);
                    /* try { // try from 0058401e to 00584022 has its CatchHandler @ 00584417 */
    STRINGS::uniqueName((STRINGS *)local_68,(string *)local_58);
                    /* try { // try from 00584029 to 0058402d has its CatchHandler @ 00584402 */
    std::string::assign(psVar2);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    plVar9 = (long *)Ogre::TextureManager::getSingleton();
    (**(code **)(*plVar9 + 0x140))
              (&local_148,plVar9,psVar2,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,
               uVar7,CONCAT44(uVar12,uVar7),1,0,10,0x200,0,0,0);
    *(undefined8 *)(this + 0x210) = local_140;
    local_148 = &PTR__SharedPtr_00fa86b0;
    if ((local_138 != (int *)0x0) && (iVar6 = *local_138, *local_138 = iVar6 + -1, iVar6 + -1 == 0))
    {
      (*(code *)PTR_destroy_00fa86c0)(&local_148);
    }
    (**(code **)(**(long **)(this + 0x210) + 0x2b0))(&local_168,*(long **)(this + 0x210),0,0);
                    /* try { // try from 0058411d to 00584122 has its CatchHandler @ 005843cf */
    plVar9 = (long *)(**(code **)(*local_160 + 0x80))(local_160,0);
    local_168 = &PTR__SharedPtr_00fa85d0;
    if ((local_158 != (int *)0x0) && (iVar6 = *local_158, *local_158 = iVar6 + -1, iVar6 + -1 == 0))
    {
      (*(code *)PTR_destroy_00fa85e0)(&local_168);
    }
    (**(code **)(*plVar9 + 0x48))
              (0,0,DAT_00fa47fc,plVar9,*(undefined8 *)(*(long *)(this + 0x20) + 0x28),0);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setShadowsEnabled(bVar5);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setClearEveryFrame(bVar5,1);
    local_88 = 0x3dc0c0c1;
    local_84 = 0x3dc0c0c1;
    local_80 = 0x3dc0c0c1;
    local_7c = 0x3f800000;
    pCVar11 = (ColourValue *)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setBackgroundColour(pCVar11);
    bVar5 = (bool)(**(code **)(*plVar9 + 0x58))(plVar9,0);
    Ogre::Viewport::setOverlaysEnabled(bVar5);
    (**(code **)(*plVar9 + 0xf8))(plVar9,1);
    (**(code **)(*plVar9 + 0xc0))(plVar9,this + 0x10);
  }
  CLevel::setProjectorPass
            (*(CLevel **)(this + 0x70),*(Frustum **)(*(long *)(this + 0x20) + 0x30),
             *(Frustum **)(*(long *)(this + 0x20) + 0x28),*(CGenericModel **)(this + 0x1068),
             *(CGenericModel **)(this + 0x1070),(string *)(this + 0x38f0),psVar2);
  refreshLighting(this);
  return;
}



/* address=00584460
   symbol=CGameClient::applyCharacterState */

/* WARNING: Removing unreachable block (ram,0x00584711) */
/* WARNING: Removing unreachable block (ram,0x0058472f) */
/* CGameClient::applyCharacterState(CCharacterSaveState*, std::wstring&, CCharacterSaveState*) */

void __thiscall
CGameClient::applyCharacterState
          (CGameClient *this,CCharacterSaveState *param_1,wstring_conflict *param_2,
          CCharacterSaveState *param_3)

{
  int *piVar1;
  int iVar2;
  long *plVar3;
  long lVar4;
  long local_48 [2];
  long local_38 [3];

  if ((param_1 != (CCharacterSaveState *)0x0) && (*(long *)(this + 0x58) != 0)) {
    std::wstring::assign((wstring_conflict *)(this + 0x1a8));
    CGameUI::setPlayer(*(CGameUI **)(this + 0x78),(CCharacter *)0x0);
    CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x58),true);
    if (*(long **)(this + 0x58) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x58) + 8))();
      *(undefined8 *)(this + 0x58) = 0;
    }
    plVar3 = (long *)CResourceManager::createPlayer
                               (*(CResourceManager **)(*(long *)(this + 0x70) + 0x138),
                                *(wchar_t **)param_2,true);
    *(long **)(this + 0x58) = plVar3;
    (**(code **)(*plVar3 + 0x2a0))(plVar3,param_1);
    std::wstring::wstring((wstring_conflict *)local_38,(wstring_conflict *)(param_1 + 0x40));
                    /* try { // try from 00584546 to 0058454a has its CatchHandler @ 005846fe */
    std::wstring::assign((wstring_conflict *)(*(long *)(this + 0x58) + 0x4c0));
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    CLevel::addCharacter
              (*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x58),
               (Vector3 *)(*(CLevel **)(this + 0x70) + 0x140),false);
    CCharacter::setToward(*(CCharacter **)(this + 0x58),(Vector3 *)(*(long *)(this + 0x70) + 0x164))
    ;
    CGameUI::setPlayer(*(CGameUI **)(this + 0x78),*(CCharacter **)(this + 0x58));
    CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x60),true);
    if (*(long **)(this + 0x60) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x60) + 8))();
      *(undefined8 *)(this + 0x60) = 0;
    }
    if (param_3 != (CCharacterSaveState *)0x0) {
      lVar4 = CResourceManager::createUnit
                        (*(CResourceManager **)(this + 0x2b8),*(longlong *)(param_3 + 0x20),
                         *(int *)(param_3 + 0xd0),true,false);
      plVar3 = (long *)0x0;
      if (lVar4 != 0) {
        plVar3 = (long *)__dynamic_cast(lVar4,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
      }
      *(long **)(this + 0x60) = plVar3;
      (**(code **)(*plVar3 + 0x2a0))(plVar3,param_3);
      std::wstring::assign((wstring_conflict *)(this + 0x1b0));
      CCharacter::setAlignment(*(CCharacter **)(this + 0x60),1);
      *(undefined4 *)(*(long *)(this + 0x60) + 0x710) = 2;
      CLevel::addCharacter
                (*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x60),
                 (Vector3 *)(*(CLevel **)(this + 0x70) + 0x170),false);
      CCharacter::setToward
                (*(CCharacter **)(this + 0x60),(Vector3 *)(*(long *)(this + 0x70) + 0x17c));
      std::wstring::wstring
                ((wstring_conflict *)local_48,(wstring_conflict *)(*(long *)(this + 0x78) + 0x16b8))
      ;
                    /* try { // try from 00584691 to 00584695 has its CatchHandler @ 0058471c */
      std::wstring::assign((wstring_conflict *)(*(long *)(this + 0x60) + 0x4c0));
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
  }
  *(undefined4 *)(this + 0x1038) = 3;
  return;
}



/* address=00584740
   symbol=CGameClient::setCreationPet */

/* WARNING: Removing unreachable block (ram,0x0058489e) */
/* CGameClient::setCreationPet(std::wstring) */

void __thiscall CGameClient::setCreationPet(CGameClient *this,undefined8 *param_2)

{
  int *piVar1;
  size_t __n;
  int iVar2;
  long lVar3;
  long local_28 [3];

  __n = *(size_t *)(*(wchar_t **)(this + 0x1b0) + -6);
  if ((__n != *(size_t *)((wchar_t *)*param_2 + -6)) ||
     (iVar2 = wmemcmp(*(wchar_t **)(this + 0x1b0),(wchar_t *)*param_2,__n), iVar2 != 0)) {
    std::wstring::assign((wstring_conflict *)(this + 0x1b0));
    CLevel::removeCharacter(*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x60),true);
    if (*(long **)(this + 0x60) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x60) + 8))();
      *(undefined8 *)(this + 0x60) = 0;
    }
    lVar3 = CResourceManager::createMonster
                      (*(CResourceManager **)(*(long *)(this + 0x70) + 0x138),
                       *(wchar_t **)(this + 0x1b0),0,false);
    *(long *)(this + 0x60) = lVar3;
    if (lVar3 != 0) {
      std::wstring::wstring
                ((wstring_conflict *)local_28,(wstring_conflict *)(*(long *)(this + 0x78) + 0x16b8))
      ;
                    /* try { // try from 005847e1 to 005847e5 has its CatchHandler @ 0058488b */
      std::wstring::assign((wstring_conflict *)(*(long *)(this + 0x60) + 0x4c0));
      if ((allocator *)(local_28[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_28[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
        }
      }
      CCharacter::setAlignment(*(CCharacter **)(this + 0x60),1);
      *(undefined4 *)(*(long *)(this + 0x60) + 0x710) = 2;
      CLevel::addCharacter
                (*(CLevel **)(this + 0x70),*(CCharacter **)(this + 0x60),
                 (Vector3 *)(*(CLevel **)(this + 0x70) + 0x170),false);
      CCharacter::setToward
                (*(CCharacter **)(this + 0x60),(Vector3 *)(*(long *)(this + 0x70) + 0x17c));
    }
  }
  *(undefined4 *)(this + 0x1038) = 3;
  return;
}



/* address=005848b0
   symbol=CGameClient::getRankOfMonstersOnFloor */

/* WARNING: Removing unreachable block (ram,0x00584a87) */
/* WARNING: Removing unreachable block (ram,0x00584a92) */
/* CGameClient::getRankOfMonstersOnFloor(int, CDungeon*, bool) */

int __thiscall
CGameClient::getRankOfMonstersOnFloor(CGameClient *this,int param_1,CDungeon *param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  long local_58 [2];
  long local_48 [3];

  if (param_2 == (CDungeon *)0x0) {
    if (param_1 < 1) {
      return 1;
    }
    return param_1;
  }
  iVar5 = param_1 + 1;
  if (iVar5 < 1) {
    iVar5 = 1;
  }
  iVar5 = (int)((float)iVar5 * *(float *)(param_2 + 0x70) + DAT_00fa4810);
  if (iVar5 < 1) {
    iVar5 = 1;
  }
  if ((*(long *)(this + 0x58) == 0) && (param_3)) goto LAB_00584998;
  std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(param_2 + 0x60));
                    /* try { // try from 00584932 to 00584936 has its CatchHandler @ 00584ab5 */
  cVar3 = CPlayer::hasDungeonHistory(*(CPlayer **)(this + 0x58),(wstring_conflict *)local_48);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  if (!param_3) goto LAB_00584998;
  if (cVar3 == '\0') {
LAB_0058495d:
    iVar4 = *(int *)(*(long *)(this + 0x58) + 0x100);
    if (iVar4 == 0) goto LAB_00584998;
  }
  else {
                    /* try { // try from 005849f3 to 00584a0a has its CatchHandler @ 00584a9d */
    std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(param_2 + 0x60));
    iVar4 = CPlayer::getDungeonRank(*(CPlayer **)(this + 0x58),(wstring_conflict *)local_58);
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
    if (iVar4 == 0) goto LAB_0058495d;
  }
  iVar2 = *(int *)(param_2 + 0x74);
  if ((iVar2 != 0) || (0 < *(int *)(param_2 + 0x78))) {
    if (iVar4 < iVar2) {
      iVar4 = iVar2;
    }
    if (*(int *)(param_2 + 0x78) < iVar4) {
      iVar4 = *(int *)(param_2 + 0x78);
    }
    iVar5 = iVar5 + *(int *)(param_2 + 0x7c) + -1 + iVar4;
  }
LAB_00584998:
  iVar4 = 1;
  if (0 < iVar5) {
    iVar4 = iVar5;
  }
  return iVar4;
}



/* address=00584ad0
   symbol=CGameClient::getRankOfMonstersOnFloor */

/* CGameClient::getRankOfMonstersOnFloor(int, std::wstring const&, bool) */

ulong __thiscall
CGameClient::getRankOfMonstersOnFloor
          (CGameClient *this,int param_1,wstring_conflict *param_2,bool param_3)

{
  CDungeon *pCVar1;
  ulong uVar2;

  while( true ) {
    if (*(long *)(*(long *)param_2 + -0x18) != 0) {
      pCVar1 = (CDungeon *)
               CResourceManager::getDungeonByName(*(CResourceManager **)(this + 0x2b8),param_2);
      if (pCVar1 != (CDungeon *)0x0) {
        uVar2 = getRankOfMonstersOnFloor(this,param_1,pCVar1,param_3);
        return uVar2;
      }
    }
    if (*(long *)(this + 0x70) == 0) break;
    param_2 = (wstring_conflict *)(*(long *)(this + 0x70) + 0x280);
  }
  uVar2 = 1;
  if (0 < param_1) {
    uVar2 = (ulong)(uint)param_1;
  }
  return uVar2;
}



/* address=00584b80
   symbol=CGameClient::loadMenuLevel */

/* WARNING: Removing unreachable block (ram,0x00585753) */
/* WARNING: Removing unreachable block (ram,0x00585682) */
/* WARNING: Removing unreachable block (ram,0x00585690) */
/* WARNING: Removing unreachable block (ram,0x00585737) */
/* WARNING: Removing unreachable block (ram,0x0058570d) */
/* WARNING: Removing unreachable block (ram,0x00585745) */
/* WARNING: Removing unreachable block (ram,0x0058563d) */
/* WARNING: Removing unreachable block (ram,0x0058571b) */
/* WARNING: Removing unreachable block (ram,0x00585729) */
/* CGameClient::loadMenuLevel(int, int, std::wstring) */

void __thiscall
CGameClient::loadMenuLevel
          (CGameClient *this,undefined8 param_2_00,uint param_2,wstring_conflict *param_4)

{
  int *piVar1;
  int iVar2;
  CLevel *pCVar3;
  long lVar4;
  undefined8 uVar5;
  CLayout *pCVar6;
  CGenericModel *pCVar7;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  wstring_conflict local_148 [16];
  long local_138 [2];
  long local_128 [2];
  wchar_t *local_118 [2];
  wstring_conflict local_108 [16];
  wchar_t *local_f8 [2];
  wstring_conflict local_e8 [16];
  wchar_t *local_d8 [2];
  wstring_conflict local_c8 [16];
  wchar_t *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];
  allocator local_2a;
  allocator local_29;

  CSteamStats::getSingleton();
  CSteamStats::forceStatsToSave();
  std::wstring::wstring((wstring_conflict *)local_48,param_4);
                    /* try { // try from 00584bbe to 00584bc2 has its CatchHandler @ 005856fa */
  setCurrentDungeon(this,(wstring_conflict *)local_48);
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
  std::wstring::wstring((wstring_conflict *)local_58,param_4);
                    /* try { // try from 00584bfb to 00584bff has its CatchHandler @ 005856da */
  pCVar3 = (CLevel *)Ogre::NedAllocImpl::allocBytes(0x2f0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00584c35 to 00584c39 has its CatchHandler @ 005856c5 */
  CLevel::CLevel(pCVar3,(wstring_conflict *)local_58,*(undefined8 *)(this + 0x50),this,
                 *(undefined8 *)(this + 0x2b8),*(undefined8 *)(this + 0x28),
                 *(undefined8 *)(this + 0x48),*(undefined4 *)(this + 0x1090),0);
  *(CLevel **)(this + 0x70) = pCVar3;
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
  resetGameSeed(this,param_2);
  lVar4 = CDungeon::getLevelTemplateDataForDepth(*(CDungeon **)(this + 0x38d8),this,param_2);
  if (lVar4 == 0) {
    std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0058535d to 00585361 has its CatchHandler @ 00585638 */
    std::wstring::wstring
              ((wstring_conflict *)local_88,L"media/layouts/mainmenus/mainmenu_townrules.dat",
               &local_29);
                    /* try { // try from 00585376 to 0058537a has its CatchHandler @ 0058561d */
    CLevel::loadRoomLayout(*(CLevel **)(this + 0x70),(wstring_conflict *)local_88,0,3);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
  }
  else {
    std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00584ca4 to 00584ca8 has its CatchHandler @ 005856b5 */
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(lVar4 + 0x6f0));
                    /* try { // try from 00584cbd to 00584cc1 has its CatchHandler @ 005856ad */
    CLevel::loadRoomLayout(*(CLevel **)(this + 0x70),(wstring_conflict *)local_68,0,3);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
  }
  *(undefined4 *)(*(long *)(this + 0x70) + 0x278) = 0x4b18967f;
  *(undefined1 *)(*(long *)(this + 0x48) + 0x6a9) = 1;
  CLevel::activate(*(CLevel **)(this + 0x70));
  if (*(long *)(this + 0x1060) == 0) {
    if (*(long *)(*(long *)(this + 0x70) + 0x1d8) == 0) {
      lVar4 = CResourceManager::createGenericModel
                        (*(CResourceManager **)(this + 0x2b8),(SceneManager *)0x0,
                         L"media/skyboxes/crypt/crypt_sky.mesh",L"",false,false,false);
      *(long *)(this + 0x1060) = lVar4;
    }
    else {
      std::wstring::wstring
                ((wstring_conflict *)local_a8,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6a0));
      lVar4 = *(long *)(local_a8[0] + -0x18);
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_a8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
      if (lVar4 != 0) {
        std::wstring::wstring
                  ((wstring_conflict *)local_b8,
                   (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6a0));
                    /* try { // try from 0058544d to 00585451 has its CatchHandler @ 0058567f */
        uVar5 = CResourceManager::createGenericModel
                          (*(CResourceManager **)(this + 0x2b8),(SceneManager *)0x0,local_b8[0],L"",
                           false,false,false);
        *(undefined8 *)(this + 0x1060) = uVar5;
        std::wstring::~wstring((wstring_conflict *)local_b8);
      }
      lVar4 = *(long *)(this + 0x1060);
    }
    if (lVar4 != 0) {
      (**(code **)(**(long **)(lVar4 + 0x60) + 0x140))(*(long **)(lVar4 + 0x60),5);
      (**(code **)(**(long **)(this + 0x1060) + 0x50))(*(long **)(this + 0x1060),1);
      lVar4 = *(long *)(this + 0x1068);
      goto joined_r0x0058510a;
    }
  }
  lVar4 = *(long *)(this + 0x1068);
joined_r0x0058510a:
  if (lVar4 == 0) {
    pCVar3 = *(CLevel **)(this + 0x70);
    if (*(long *)(pCVar3 + 0x1d8) != 0) {
                    /* try { // try from 0058513c to 00585153 has its CatchHandler @ 00585667 */
      std::wstring::wstring(local_c8,(wstring_conflict *)(*(long *)(pCVar3 + 0x1d8) + 0x6b0));
      iVar2 = std::wstring::compare((wchar_t *)local_c8);
      if (iVar2 == 0) {
        std::wstring::~wstring(local_c8);
        pCVar3 = *(CLevel **)(this + 0x70);
      }
      else {
        std::wstring::~wstring(local_c8);
        std::wstring::wstring
                  ((wstring_conflict *)local_d8,
                   (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6b0));
                    /* try { // try from 005851a9 to 005851ad has its CatchHandler @ 00585665 */
        uVar5 = CResourceManager::createGenericModel
                          (*(CResourceManager **)(this + 0x2b8),(SceneManager *)0x0,local_d8[0],L"",
                           false,false,false);
        *(undefined8 *)(this + 0x1068) = uVar5;
        std::wstring::~wstring((wstring_conflict *)local_d8);
        (**(code **)(**(long **)(*(long *)(this + 0x1068) + 0x60) + 0x140))
                  (*(long **)(*(long *)(this + 0x1068) + 0x60),4);
        (**(code **)(**(long **)(this + 0x1068) + 0x50))(*(long **)(this + 0x1068),1);
        local_158 = 0;
        local_154 = 0;
        local_150 = 0;
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(this + 0x1068),(Vector3 *)&local_158);
        pCVar3 = *(CLevel **)(this + 0x70);
      }
    }
  }
  else {
    pCVar3 = *(CLevel **)(this + 0x70);
  }
  if ((*(long *)(this + 0x1078) == 0) && (*(long *)(pCVar3 + 0x1d8) != 0)) {
                    /* try { // try from 00585245 to 0058525c has its CatchHandler @ 0058565b */
    std::wstring::wstring(local_e8,(wstring_conflict *)(*(long *)(pCVar3 + 0x1d8) + 0x6b8));
    iVar2 = std::wstring::compare((wchar_t *)local_e8);
    if (iVar2 == 0) {
      std::wstring::~wstring(local_e8);
      pCVar3 = *(CLevel **)(this + 0x70);
    }
    else {
      std::wstring::~wstring(local_e8);
      std::wstring::wstring
                ((wstring_conflict *)local_f8,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6b8));
                    /* try { // try from 005852b2 to 005852b6 has its CatchHandler @ 00585648 */
      uVar5 = CResourceManager::createGenericModel
                        (*(CResourceManager **)(this + 0x2b8),(SceneManager *)0x0,local_f8[0],L"",
                         false,false,false);
      *(undefined8 *)(this + 0x1078) = uVar5;
      std::wstring::~wstring((wstring_conflict *)local_f8);
      (**(code **)(**(long **)(*(long *)(this + 0x1078) + 0x60) + 0x140))
                (*(long **)(*(long *)(this + 0x1078) + 0x60),0x59);
      (**(code **)(**(long **)(this + 0x1078) + 0x50))(*(long **)(this + 0x1078),1);
      local_168 = 0;
      local_164 = 0;
      local_160 = 0;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this + 0x1078),(Vector3 *)&local_168);
      pCVar3 = *(CLevel **)(this + 0x70);
    }
  }
  pCVar7 = *(CGenericModel **)(this + 0x1070);
  if ((pCVar7 == (CGenericModel *)0x0) && (*(long *)(pCVar3 + 0x1d8) != 0)) {
                    /* try { // try from 00584ec5 to 00584edc has its CatchHandler @ 005856f5 */
    std::wstring::wstring(local_108,(wstring_conflict *)(*(long *)(pCVar3 + 0x1d8) + 0x6c0));
    iVar2 = std::wstring::compare((wchar_t *)local_108);
    if (iVar2 == 0) {
      std::wstring::~wstring(local_108);
      pCVar7 = *(CGenericModel **)(this + 0x1070);
      pCVar3 = *(CLevel **)(this + 0x70);
    }
    else {
      std::wstring::~wstring(local_108);
      std::wstring::wstring
                ((wstring_conflict *)local_118,
                 (wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6c0));
                    /* try { // try from 00584f32 to 00584f36 has its CatchHandler @ 005856ab */
      uVar5 = CResourceManager::createGenericModel
                        (*(CResourceManager **)(this + 0x2b8),(SceneManager *)0x0,local_118[0],L"",
                         false,false,false);
      *(undefined8 *)(this + 0x1070) = uVar5;
      std::wstring::~wstring((wstring_conflict *)local_118);
      (**(code **)(**(long **)(*(long *)(this + 0x1070) + 0x60) + 0x140))
                (*(long **)(*(long *)(this + 0x1070) + 0x60),0x58);
      (**(code **)(**(long **)(this + 0x1070) + 0x50))(*(long **)(this + 0x1070),1);
      local_178 = 0;
      local_174 = 0;
      local_170 = 0;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this + 0x1070),(Vector3 *)&local_178);
      pCVar7 = *(CGenericModel **)(this + 0x1070);
      pCVar3 = *(CLevel **)(this + 0x70);
    }
  }
  CLevel::setProjectorPass
            (pCVar3,*(Frustum **)(*(long *)(this + 0x20) + 0x30),
             *(Frustum **)(*(long *)(this + 0x20) + 0x28),*(CGenericModel **)(this + 0x1068),pCVar7,
             (string *)(this + 0x38f0),(string *)(this + 0x38f8));
  refreshLighting(this);
  if (*(Vector3 **)(*(long *)(this + 0x20) + 0x10) != (Vector3 *)0x0) {
    Ogre::Camera::setPosition(*(Vector3 **)(*(long *)(this + 0x20) + 0x10));
    Ogre::Camera::lookAt(*(Vector3 **)(*(long *)(this + 0x20) + 0x10));
  }
  if (*(CGameUI **)(this + 0x78) != (CGameUI *)0x0) {
    CGameUI::setCursorState(*(CGameUI **)(this + 0x78),0);
  }
  CSoundManager::stopMusic(*(CSoundManager **)(this + 0x48));
                    /* try { // try from 00584dea to 00584dee has its CatchHandler @ 005856e5 */
  std::wstring::wstring((wstring_conflict *)local_128,L"../music/Title.ogg",&local_2a);
                    /* try { // try from 00584dfb to 00584e7b has its CatchHandler @ 005856df */
  CSoundManager::playMusic(*(CSoundManager **)(this + 0x48),(wstring_conflict *)local_128,true);
  if (*(long **)(this + 0x1080) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1080) + 8))();
    *(undefined8 *)(this + 0x1080) = 0;
  }
  pCVar3 = *(CLevel **)(this + 0x70);
  if (*(long *)(pCVar3 + 0x1d8) != 0) {
    std::wstring::wstring
              ((wstring_conflict *)local_138,(wstring_conflict *)(*(long *)(pCVar3 + 0x1d8) + 0x6a8)
              );
    lVar4 = *(long *)(local_138[0] + -0x18);
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    if (lVar4 != 0) {
                    /* try { // try from 00584fdb to 00584fdf has its CatchHandler @ 005856df */
      pCVar6 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00584ff2 to 00584ff6 has its CatchHandler @ 0058569e */
      CLayout::CLayout(pCVar6,*(undefined8 *)(this + 0x2b8),2);
      *(CLayout **)(this + 0x1080) = pCVar6;
                    /* try { // try from 00585018 to 0058501c has its CatchHandler @ 005856df */
      std::wstring::wstring
                (local_148,(wstring_conflict *)(*(long *)(*(long *)(this + 0x70) + 0x1d8) + 0x6a8));
                    /* try { // try from 0058503b to 0058503f has its CatchHandler @ 00585672 */
      CLayout::loadLayoutFile
                (*(CLayout **)(this + 0x1080),local_148,true,(CTimerStatics *)0x0,false,false,0);
                    /* try { // try from 00585043 to 0058507a has its CatchHandler @ 005856df */
      std::wstring::~wstring(local_148);
      (**(code **)(**(long **)(this + 0x1080) + 0x50))(*(long **)(this + 0x1080),1);
      (**(code **)(**(long **)(this + 0x1080) + 0x218))(*(long **)(this + 0x1080),1);
      CLayout::start(*(CLayout **)(this + 0x1080));
    }
    pCVar3 = *(CLevel **)(this + 0x70);
  }
  *(undefined4 *)(this + 0x1038) = 3;
  CLevel::setInited(pCVar3,true);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  return;
}



/* address=00585770
   symbol=CGameClient::loadLevel */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00587ee0
   symbol=CGameClient::renderableQueued */

/* non-virtual thunk to CGameClient::renderableQueued(Ogre::Renderable*, unsigned char, unsigned
   short, Ogre::Technique**, Ogre::RenderQueue*) */

void __thiscall
CGameClient::renderableQueued
          (CGameClient *this,Renderable *param_1,uchar param_2,ushort param_3,Technique **param_4,
          RenderQueue *param_5)

{
  undefined6 in_register_0000000a;
  undefined1 in_DH;

  renderableQueued((Renderable *)(this + -0x18),(uchar)param_1,CONCAT11(in_DH,param_2),
                   (Technique **)CONCAT62(in_register_0000000a,param_3),(RenderQueue *)param_4);
  return;
}



/* address=00587ef0
   symbol=CGameClient::renderableQueued */

/* CGameClient::renderableQueued(Ogre::Renderable*, unsigned char, unsigned short,
   Ogre::Technique**, Ogre::RenderQueue*) */

undefined8
CGameClient::renderableQueued
          (Renderable *param_1,uchar param_2,ushort param_3,Technique **param_4,RenderQueue *param_5
          )

{
  short sVar1;
  long *plVar2;
  long lVar3;
  Any *pAVar4;
  CRenderableStates *pCVar5;
  undefined8 uVar6;
  char cVar7;
  int iVar8;
  undefined7 in_register_00000031;
  float fVar9;

  cVar7 = (char)param_3;
  if (param_1[0x2b0] == (Renderable)0x0) {
    if (((cVar7 != 'e') && (cVar7 != '\0')) && (4 < (byte)(cVar7 + 0xa1U))) goto LAB_00587f22;
  }
  else if (cVar7 != '^') {
LAB_00587f22:
    if (((CONCAT71(in_register_00000031,param_2) != 0) &&
        (plVar2 = (long *)__dynamic_cast(CONCAT71(in_register_00000031,param_2),
                                         &Ogre::Renderable::typeinfo,Ogre::SubEntity::typeinfo,0),
        plVar2 != (long *)0x0)) &&
       (lVar3 = (**(code **)(*plVar2 + 0x80))(plVar2), *(long *)(lVar3 + 8) != 0)) {
      pAVar4 = (Any *)(**(code **)(*plVar2 + 0x80))(plVar2);
      pCVar5 = Ogre::any_cast<CRenderableStates*>(pAVar4);
      if (((pCVar5 != (CRenderableStates *)0x0) && (param_1[0x2b0] != (Renderable)0x0)) &&
         ((pCVar5[1] != (CRenderableStates)0x0 && (DAT_00fa47f8 < *(float *)(pCVar5 + 0x34))))) {
        fVar9 = floorf(*(float *)(pCVar5 + 0x34) * DAT_00fa874c);
        iVar8 = (int)fVar9 + -1;
        if (iVar8 < 0) {
          iVar8 = 0;
        }
        if (pCVar5[2] == (CRenderableStates)0x0) {
          uVar6 = Ogre::Material::getTechnique
                            ((ushort)*(undefined8 *)(param_1 + (long)iVar8 * 0x20 + 0x10c8));
          *(undefined8 *)param_5 = uVar6;
          return 1;
        }
        sVar1 = *(short *)(pCVar5 + 0x2c);
        if (sVar1 == 2) {
          uVar6 = Ogre::Material::getTechnique
                            ((ushort)*(undefined8 *)(param_1 + (long)iVar8 * 0x20 + 0x28c8));
          *(undefined8 *)param_5 = uVar6;
          return 1;
        }
        if (sVar1 != 3) {
          if (sVar1 != 1) {
            uVar6 = Ogre::Material::getTechnique
                              ((ushort)*(undefined8 *)(param_1 + (long)iVar8 * 0x20 + 0x18c8));
            *(undefined8 *)param_5 = uVar6;
            return 1;
          }
          uVar6 = Ogre::Material::getTechnique
                            ((ushort)*(undefined8 *)(param_1 + (long)iVar8 * 0x20 + 0x30c8));
          *(undefined8 *)param_5 = uVar6;
          return 1;
        }
        uVar6 = Ogre::Material::getTechnique
                          ((ushort)*(undefined8 *)(param_1 + (long)iVar8 * 0x20 + 0x20c8));
        *(undefined8 *)param_5 = uVar6;
        return 1;
      }
    }
    return 0;
  }
  return 1;
}



/* address=005880f0
   symbol=CGameClient::CGameClient */

/* WARNING: Removing unreachable block (ram,0x0058ac43) */
/* WARNING: Removing unreachable block (ram,0x0058ac8f) */
/* WARNING: Removing unreachable block (ram,0x0058b54f) */
/* WARNING: Removing unreachable block (ram,0x0058b595) */
/* WARNING: Removing unreachable block (ram,0x0058b5b1) */
/* WARNING: Removing unreachable block (ram,0x0058b55d) */
/* WARNING: Removing unreachable block (ram,0x0058b530) */
/* WARNING: Removing unreachable block (ram,0x0058af62) */
/* WARNING: Removing unreachable block (ram,0x0058af72) */
/* WARNING: Removing unreachable block (ram,0x0058ad70) */
/* WARNING: Removing unreachable block (ram,0x0058afbe) */
/* WARNING: Removing unreachable block (ram,0x0058b3a0) */
/* WARNING: Removing unreachable block (ram,0x0058b204) */
/* WARNING: Removing unreachable block (ram,0x0058b45e) */
/* WARNING: Removing unreachable block (ram,0x0058b11d) */
/* WARNING: Removing unreachable block (ram,0x0058b108) */
/* WARNING: Removing unreachable block (ram,0x0058b453) */
/* WARNING: Removing unreachable block (ram,0x0058b1f9) */
/* WARNING: Removing unreachable block (ram,0x0058b36a) */
/* WARNING: Removing unreachable block (ram,0x0058ace2) */
/* WARNING: Removing unreachable block (ram,0x0058ab75) */
/* WARNING: Removing unreachable block (ram,0x0058aea5) */
/* WARNING: Removing unreachable block (ram,0x0058af57) */
/* WARNING: Removing unreachable block (ram,0x0058ad7b) */
/* WARNING: Removing unreachable block (ram,0x0058b5a3) */
/* WARNING: Removing unreachable block (ram,0x0058b579) */
/* WARNING: Removing unreachable block (ram,0x0058b56b) */
/* WARNING: Removing unreachable block (ram,0x0058b5bf) */
/* WARNING: Removing unreachable block (ram,0x0058b587) */
/* WARNING: Removing unreachable block (ram,0x0058ac4e) */
/* WARNING: Removing unreachable block (ram,0x0058acf0) */
/* WARNING: Removing unreachable block (ram,0x0058a85d) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGameClient::CGameClient(CSettings&, CMasterResourceManager*, Ogre::RenderWindow*, Ogre::Root*,
   CCameraControl*, Ogre::SceneManager*, Ogre::SceneManager*, Ogre::SceneManager*, CSoundManager&)
    */

void __thiscall
CGameClient::CGameClient
          (CGameClient *this,CSettings *param_1,CMasterResourceManager *param_2,
          RenderWindow *param_3,Root *param_4,CCameraControl *param_5,SceneManager *param_6,
          SceneManager *param_7,SceneManager *param_8,CSoundManager *param_9)

{
  code *pcVar1;
  int *piVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  ushort uVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  long lVar10;
  CResourceManager *this_00;
  Vector3 *pVVar11;
  Vector3 *pVVar12;
  long *plVar13;
  ColourValue *pCVar14;
  Rectangle2D *pRVar15;
  string *psVar16;
  CFileSystem *pCVar17;
  CQuestManager *this_01;
  void *pvVar18;
  ulong uVar19;
  CGameClient *pCVar20;
  uint uVar21;
  undefined8 in_stack_fffffffffffffa58;
  undefined4 uVar23;
  undefined8 uVar22;
  undefined1 *local_4f8;
  long local_4f0;
  long local_4e8;
  undefined4 local_4e0;
  undefined4 local_4dc;
  undefined1 *local_4d8;
  undefined1 local_4d0;
  float local_4c8;
  float local_4c4;
  float local_4c0;
  float local_4bc;
  float local_4b8;
  float local_4b4;
  undefined4 local_4b0;
  void *local_4a8;
  float local_498;
  float local_494;
  float local_490;
  float local_48c;
  float local_488;
  float local_484;
  undefined4 local_480;
  void *local_478;
  float local_468;
  float local_464;
  float local_460;
  float local_45c;
  float local_458;
  float local_454;
  undefined4 local_450;
  void *local_448;
  undefined **local_438;
  long local_430;
  int *local_428;
  undefined **local_418;
  long local_410;
  int *local_408;
  undefined **local_3f8;
  long local_3f0;
  int *local_3e8;
  undefined **local_3d8;
  long local_3d0;
  int *local_3c8;
  undefined **local_3b8;
  long local_3b0;
  int *local_3a8;
  undefined **local_398;
  long local_390;
  int *local_388;
  undefined **local_378;
  long local_370;
  int *local_368;
  undefined **local_358;
  long local_350;
  int *local_348;
  undefined **local_338;
  long *local_330;
  int *local_328;
  undefined **local_318;
  undefined8 local_310;
  int *local_308;
  undefined **local_2f8;
  long *local_2f0;
  int *local_2e8;
  undefined **local_2d8;
  undefined8 local_2d0;
  int *local_2c8;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  Radian local_298 [16];
  Radian local_288 [16];
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  long local_258 [2];
  long local_248 [2];
  long local_238 [2];
  long local_228 [2];
  long local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  long local_1e8 [2];
  long local_1d8 [2];
  long local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  float local_98 [4];
  float local_88 [4];
  float local_78 [11];
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

  uVar23 = (undefined4)((ulong)in_stack_fffffffffffffa58 >> 0x20);
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CGameClient_00fa83d0;
  *(undefined ***)(this + 0x10) = &PTR__CGameClient_00fa8408;
  *(undefined ***)(this + 0x18) = &PTR__CGameClient_00fa8458;
  *(CCameraControl **)(this + 0x20) = param_5;
  *(undefined8 *)(this + 0x40) = 0;
  *(SceneManager **)(this + 0x28) = param_6;
  *(CSettings **)(this + 0x50) = param_1;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(SceneManager **)(this + 0x30) = param_7;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  *(SceneManager **)(this + 0x38) = param_8;
  this[0x98] = (CGameClient)0x0;
  this[0x99] = (CGameClient)0x0;
  this[0x9a] = (CGameClient)0x0;
  *(CSoundManager **)(this + 0x48) = param_9;
                    /* try { // try from 005881e7 to 005881eb has its CatchHandler @ 0058afce */
  std::wstring::wstring((wstring_conflict *)(this + 0x1a0),L"",local_39);
                    /* try { // try from 00588210 to 00588214 has its CatchHandler @ 0058b07e */
  std::wstring::wstring((wstring_conflict *)(this + 0x1a8),L"Destroyer",&local_3a);
                    /* try { // try from 00588234 to 00588238 has its CatchHandler @ 0058b074 */
  std::wstring::wstring((wstring_conflict *)(this + 0x1b0),L"Dog",&local_3b);
  this[0x1b8] = (CGameClient)0x0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  *(undefined4 *)(this + 0x1d0) = 0xffffffff;
  *(undefined8 *)(this + 0x1d8) = 0;
  *(undefined4 *)(this + 0x1e0) = 0xffffffff;
  *(undefined8 *)(this + 0x1e8) = 0;
  *(undefined4 *)(this + 0x1f0) = 0xffffffff;
  *(undefined8 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x200) = 0xffffffff;
  *(undefined8 *)(this + 0x208) = 0;
  *(undefined8 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x218) = 0;
  *(undefined8 *)(this + 0x220) = 0;
  *(undefined8 *)(this + 0x228) = 0;
  *(undefined8 *)(this + 0x230) = 0;
  *(undefined8 *)(this + 0x238) = 0;
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined8 *)(this + 0x250) = 0;
  *(undefined8 *)(this + 600) = 0;
  *(undefined4 *)(this + 0x260) = 0;
  *(undefined ***)(this + 0x248) = &PTR__MaterialPtr_00fa44d0;
  *(undefined8 *)(this + 0x270) = 0;
  *(undefined8 *)(this + 0x278) = 0;
  *(undefined4 *)(this + 0x280) = 0;
  *(undefined ***)(this + 0x268) = &PTR__MaterialPtr_00fa44d0;
  *(undefined8 *)(this + 0x290) = 0;
  *(undefined8 *)(this + 0x298) = 0;
  *(undefined4 *)(this + 0x2a0) = 0;
  *(undefined ***)(this + 0x288) = &PTR__MaterialPtr_00fa44d0;
  *(undefined4 *)(this + 0x2a8) = 0;
  *(undefined4 *)(this + 0x2ac) = 0x3f800000;
  this[0x2b0] = (CGameClient)0x0;
  *(undefined4 *)(this + 0x2c0) = 0;
  *(undefined4 *)(this + 0x2c4) = 0;
  *(undefined4 *)(this + 0x2c8) = 0;
                    /* try { // try from 005883d1 to 005883d5 has its CatchHandler @ 0058b043 */
  CKeyManager::CKeyManager((CKeyManager *)(this + 0x2d0));
                    /* try { // try from 005883e8 to 005883ec has its CatchHandler @ 0058b012 */
  CMouseManager::CMouseManager((CMouseManager *)(this + 0xfe8));
  *(undefined4 *)(this + 0x1038) = 0;
  this[0x103c] = (CGameClient)0x0;
  this[0x103d] = (CGameClient)0x0;
  lVar10 = 0;
  *(CMasterResourceManager **)(this + 0x1040) = param_2;
  *(undefined4 *)(this + 0x1048) = 0;
  *(undefined4 *)(this + 0x104c) = 0;
  *(RenderWindow **)(this + 0x1050) = param_3;
  *(Root **)(this + 0x1058) = param_4;
  *(undefined8 *)(this + 0x1060) = 0;
  *(undefined8 *)(this + 0x1068) = 0;
  *(undefined8 *)(this + 0x1070) = 0;
  *(undefined8 *)(this + 0x1078) = 0;
  *(undefined8 *)(this + 0x1080) = 0;
  *(undefined8 *)(this + 0x1088) = 0;
  *(undefined4 *)(this + 0x1090) = 0;
  *(undefined4 **)(this + 0x1098) = &DAT_01424558;
  *(undefined4 *)(this + 0x10a0) = 0;
  *(undefined4 **)(this + 0x10a8) = &DAT_01424558;
  *(undefined4 **)(this + 0x10b0) = &DAT_01424558;
  this[0x10b8] = (CGameClient)0x0;
  this[0x10b9] = (CGameClient)0x0;
  this[0x10ba] = (CGameClient)0x0;
  this[0x10bb] = (CGameClient)0x0;
  this[0x10bc] = (CGameClient)0x0;
  do {
    *(undefined8 *)(this + lVar10 + 0x10c8) = 0;
    *(undefined8 *)(this + lVar10 + 0x10d0) = 0;
    *(undefined4 *)(this + lVar10 + 0x10d8) = 0;
    *(undefined ***)(this + lVar10 + 0x10c0) = &PTR__MaterialPtr_00fa44d0;
    lVar10 = lVar10 + 0x20;
  } while (lVar10 != 0x800);
  lVar10 = 0;
  do {
    *(undefined8 *)(this + lVar10 + 0x18c8) = 0;
    *(undefined8 *)(this + lVar10 + 0x18d0) = 0;
    *(undefined4 *)(this + lVar10 + 0x18d8) = 0;
    *(undefined ***)(this + lVar10 + 0x18c0) = &PTR__MaterialPtr_00fa44d0;
    lVar10 = lVar10 + 0x20;
  } while (lVar10 != 0x800);
  lVar10 = 0;
  do {
    *(undefined8 *)(this + lVar10 + 0x20c8) = 0;
    *(undefined8 *)(this + lVar10 + 0x20d0) = 0;
    *(undefined4 *)(this + lVar10 + 0x20d8) = 0;
    *(undefined ***)(this + lVar10 + 0x20c0) = &PTR__MaterialPtr_00fa44d0;
    lVar10 = lVar10 + 0x20;
  } while (lVar10 != 0x800);
  lVar10 = 0;
  do {
    *(undefined8 *)(this + lVar10 + 0x28c8) = 0;
    *(undefined8 *)(this + lVar10 + 0x28d0) = 0;
    *(undefined4 *)(this + lVar10 + 0x28d8) = 0;
    *(undefined ***)(this + lVar10 + 0x28c0) = &PTR__MaterialPtr_00fa44d0;
    lVar10 = lVar10 + 0x20;
  } while (lVar10 != 0x800);
  lVar10 = 0;
  do {
    *(undefined8 *)(this + lVar10 + 0x30c8) = 0;
    *(undefined8 *)(this + lVar10 + 0x30d0) = 0;
    *(undefined4 *)(this + lVar10 + 0x30d8) = 0;
    *(undefined ***)(this + lVar10 + 0x30c0) = &PTR__MaterialPtr_00fa44d0;
    lVar10 = lVar10 + 0x20;
  } while (lVar10 != 0x800);
  *(undefined4 *)(this + 0x38c0) = 0x3f800000;
  *(undefined8 *)(this + 0x38c8) = 0;
  *(undefined4 *)(this + 0x38d0) = 6;
  this[0x38d4] = (CGameClient)0x0;
  *(undefined8 *)(this + 0x38d8) = 0;
  *(undefined4 *)(this + 0x38ec) = 1;
  *(undefined1 **)(this + 0x38f0) = &DAT_01423a38;
  *(undefined1 **)(this + 0x38f8) = &DAT_01423a38;
  *(undefined8 *)(this + 0x3900) = 0;
  *(undefined4 *)(this + 0x3908) = 0;
  *(undefined4 *)(this + 0x390c) = 0;
                    /* try { // try from 005886b5 to 005886b9 has its CatchHandler @ 0058b155 */
  this_00 = (CResourceManager *)Ogre::NedAllocImpl::allocBytes(0x48,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005886c2 to 005886c6 has its CatchHandler @ 0058b135 */
  CResourceManager::CResourceManager(this_00,(SceneManager *)0x0);
  *(CResourceManager **)(this + 0x2b8) = this_00;
  uVar21 = *(uint *)(this_00 + 0x30);
  if (uVar21 < *(uint *)(this_00 + 0x34)) {
    pvVar18 = *(void **)(this_00 + 0x28);
  }
  else if (*(long *)(this_00 + 0x28) == 0) {
    *(uint *)(this_00 + 0x34) = *(uint *)(this_00 + 0x38);
    pvVar18 = operator_new__((ulong)*(uint *)(this_00 + 0x38) * 8);
    *(void **)(this_00 + 0x28) = pvVar18;
    uVar21 = *(uint *)(this_00 + 0x30);
  }
  else {
    uVar21 = *(uint *)(this_00 + 0x34) + *(int *)(this_00 + 0x38);
    pvVar18 = operator_new__((ulong)uVar21 << 3);
    if (*(int *)(this_00 + 0x34) != 0) {
      uVar9 = 0;
      do {
        uVar19 = (ulong)uVar9;
        uVar9 = uVar9 + 1;
        *(undefined8 *)((long)pvVar18 + uVar19 * 8) =
             *(undefined8 *)(*(long *)(this_00 + 0x28) + uVar19 * 8);
      } while (uVar9 < *(uint *)(this_00 + 0x34));
    }
    if (*(void **)(this_00 + 0x28) != (void *)0x0) {
      operator_delete__(*(void **)(this_00 + 0x28));
    }
    *(void **)(this_00 + 0x28) = pvVar18;
    *(uint *)(this_00 + 0x34) = uVar21;
    uVar21 = *(uint *)(this_00 + 0x30);
  }
  *(CGameClient **)((long)pvVar18 + (ulong)uVar21 * 8) = this;
  *(int *)(this_00 + 0x30) = *(int *)(this_00 + 0x30) + 1;
  if (param_3 != (RenderWindow *)0x0) {
                    /* try { // try from 0058870a to 00588759 has its CatchHandler @ 0058b155 */
    createGameUI(this,param_3,(void *)0x0);
  }
  lVar10 = CMasterResourceManager::getSingleton();
  *(undefined8 *)(this + 0x40) = *(undefined8 *)(lVar10 + 0xd8);
  uVar21 = KSETTINGS_LEVEL_SEED;
  lVar10 = CMasterResourceManager::getSingleton();
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar21);
  uVar21 = KSETTINGS_LEVEL_SEED;
  if (iVar7 == 0) {
    uVar8 = UTILITIES::randomIntegerBetweenVolatile(0,0x7fffffff);
  }
  else {
                    /* try { // try from 0058a120 to 0058a162 has its CatchHandler @ 0058b155 */
    lVar10 = CMasterResourceManager::getSingleton();
    uVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar21);
  }
  *(undefined4 *)(this + 0x1090) = uVar8;
  pcVar1 = *(code **)(**(long **)(this + 0x28) + 0x1a8);
                    /* try { // try from 00588787 to 0058878b has its CatchHandler @ 0058b12b */
  std::string::string((string *)local_a8,"ProjectorCam",&local_3c);
                    /* try { // try from 00588793 to 00588794 has its CatchHandler @ 0058b0f6 */
  pVVar11 = (Vector3 *)(*pcVar1)(*(undefined8 *)(this + 0x28),(string *)local_a8);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_a8[0] + -8);
    iVar7 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 005887cf to 005888be has its CatchHandler @ 0058b155 */
  (**(code **)(*(long *)pVVar11 + 0x368))(pVVar11,0);
  (**(code **)(*(long *)pVVar11 + 0x2b0))(DAT_00fa8750,DAT_00fa873c,pVVar11);
  (**(code **)(*(long *)pVVar11 + 0x278))(DAT_00fa47fc,pVVar11);
  (**(code **)(*(long *)pVVar11 + 600))(DAT_00fa47fc,pVVar11);
  (**(code **)(*(long *)pVVar11 + 0x268))(DAT_00fa8754,pVVar11);
  local_268 = 0;
  local_264 = 0x42c80000;
  local_260 = 0;
  Ogre::Camera::setPosition(pVVar11);
  local_78[0] = DAT_00fa8758 * Ogre::Math::fDeg2Rad;
  Ogre::Quaternion::FromAngleAxis(local_288,(Vector3 *)local_78);
  Ogre::Camera::setOrientation((Quaternion *)pVVar11);
  pcVar1 = *(code **)(**(long **)(this + 0x28) + 0x1a8);
                    /* try { // try from 005888e5 to 005888e9 has its CatchHandler @ 0058b113 */
  std::string::string((string *)local_b8,"ProjectorCamShadow",&local_3d);
                    /* try { // try from 005888f1 to 005888f3 has its CatchHandler @ 0058b0b8 */
  pVVar12 = (Vector3 *)(*pcVar1)(*(undefined8 *)(this + 0x28),(string *)local_b8);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar7 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  local_88[0] = Ogre::Math::fDeg2Rad * DAT_00fa8734;
                    /* try { // try from 0058894f to 00588a53 has its CatchHandler @ 0058b155 */
  (**(code **)(*(long *)pVVar12 + 0x248))(pVVar12,local_88);
  (**(code **)(*(long *)pVVar12 + 0x278))(DAT_00fa47fc,pVVar12);
  (**(code **)(*(long *)pVVar12 + 600))(DAT_00fa47fc,pVVar12);
  (**(code **)(*(long *)pVVar12 + 0x268))(DAT_00fa875c,pVVar12);
  local_278 = 0;
  local_274 = 0;
  local_270 = 0x42fa0000;
  Ogre::Camera::setPosition(pVVar12);
  local_98[0] = DAT_00fa8758 * Ogre::Math::fDeg2Rad;
  Ogre::Quaternion::FromAngleAxis(local_298,(Vector3 *)local_98);
  Ogre::Camera::setOrientation((Quaternion *)pVVar12);
  lVar10 = Ogre::TextureManager::getSingletonPtr();
  if (lVar10 != 0) {
    uVar8 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x50),KSETTINGS_SHADOW_RESOLUTION);
    uVar21 = KSETTINGS_SHADOWS_ENABLED;
    lVar10 = CMasterResourceManager::getSingleton();
    iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar21);
    if (iVar7 != 0) {
                    /* try { // try from 00588a71 to 00588a75 has its CatchHandler @ 0058b20f */
      std::string::string((string *)local_c8,"ProjectorRTT",&local_3e);
                    /* try { // try from 00588a89 to 00588a8d has its CatchHandler @ 0058b3ce */
      STRINGS::uniqueName((STRINGS *)local_d8,(string *)local_c8);
                    /* try { // try from 00588a94 to 00588a98 has its CatchHandler @ 0058b3ec */
      std::string::assign((string *)(this + 0x38f0));
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_d8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_c8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
                    /* try { // try from 00588aca to 00588b8e has its CatchHandler @ 0058b155 */
      plVar13 = (long *)Ogre::TextureManager::getSingleton();
      uVar22 = CONCAT44(uVar23,uVar8);
      (**(code **)(*plVar13 + 0x140))
                (&local_2d8,plVar13,(string *)(this + 0x38f0),
                 &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,uVar8,uVar22,1,0,10,
                 0x200,0,0,0);
      uVar23 = (undefined4)((ulong)uVar22 >> 0x20);
      local_2d8 = &PTR__SharedPtr_00fa86b0;
      *(undefined8 *)(this + 0x208) = local_2d0;
      if ((local_2c8 != (int *)0x0) &&
         (iVar7 = *local_2c8, *local_2c8 = iVar7 + -1, iVar7 + -1 == 0)) {
        (*(code *)PTR_destroy_00fa86c0)(&local_2d8);
      }
      (**(code **)(**(long **)(this + 0x208) + 0x2b0))(&local_2f8,*(long **)(this + 0x208),0);
                    /* try { // try from 00588b9c to 00588ba1 has its CatchHandler @ 0058b4b5 */
      plVar13 = (long *)(**(code **)(*local_2f0 + 0x80))(local_2f0,0);
      local_2f8 = &PTR__SharedPtr_00fa85d0;
      if ((local_2e8 != (int *)0x0) &&
         (iVar7 = *local_2e8, *local_2e8 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 0058a4cf to 0058a554 has its CatchHandler @ 0058b155 */
        (*(code *)PTR_destroy_00fa85e0)(&local_2f8);
      }
                    /* try { // try from 00588bfb to 00588d20 has its CatchHandler @ 0058b155 */
      (**(code **)(*plVar13 + 0x48))(0,0,DAT_00fa47fc,plVar13,pVVar12,0);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setShadowsEnabled(bVar5);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setClearEveryFrame(bVar5,1);
      local_2a8 = 0x3f000000;
      local_2a4 = 0x3f000000;
      local_2a0 = 0x3f000000;
      local_29c = 0x3f800000;
      pCVar14 = (ColourValue *)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setBackgroundColour(pCVar14);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setOverlaysEnabled(bVar5);
      (**(code **)(*plVar13 + 0xf8))(plVar13,1);
      (**(code **)(*plVar13 + 0xc0))(plVar13,this + 0x10);
    }
    uVar21 = KSETTINGS_LIGHTING_ENABLED;
    lVar10 = CMasterResourceManager::getSingleton();
    iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar10 + 0x90),uVar21);
    if (iVar7 != 0) {
                    /* try { // try from 0058a1bc to 0058a1c0 has its CatchHandler @ 0058b15f */
      std::string::string((string *)local_e8,"ProjectorRTTLight",&local_3f);
                    /* try { // try from 0058a1d4 to 0058a1d8 has its CatchHandler @ 0058b177 */
      STRINGS::uniqueName((STRINGS *)local_f8,(string *)local_e8);
                    /* try { // try from 0058a1df to 0058a1e3 has its CatchHandler @ 0058b192 */
      std::string::assign((string *)(this + 0x38f8));
      if ((allocator *)(local_f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_f8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_e8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
                    /* try { // try from 0058a215 to 0058a2d9 has its CatchHandler @ 0058b155 */
      plVar13 = (long *)Ogre::TextureManager::getSingleton();
      (**(code **)(*plVar13 + 0x140))
                (&local_318,plVar13,(string *)(this + 0x38f8),
                 &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,2,uVar8,
                 CONCAT44(uVar23,uVar8),1,0,10,0x200,0,0,0);
      local_318 = &PTR__SharedPtr_00fa86b0;
      *(undefined8 *)(this + 0x210) = local_310;
      if ((local_308 != (int *)0x0) &&
         (iVar7 = *local_308, *local_308 = iVar7 + -1, iVar7 + -1 == 0)) {
        (*(code *)PTR_destroy_00fa86c0)(&local_318);
      }
      (**(code **)(**(long **)(this + 0x210) + 0x2b0))(&local_338,*(long **)(this + 0x210),0);
                    /* try { // try from 0058a2e7 to 0058a2ec has its CatchHandler @ 0058b497 */
      plVar13 = (long *)(**(code **)(*local_330 + 0x80))(local_330,0);
      local_338 = &PTR__SharedPtr_00fa85d0;
      if ((local_328 != (int *)0x0) &&
         (iVar7 = *local_328, *local_328 = iVar7 + -1, iVar7 + -1 == 0)) {
        (*(code *)PTR_destroy_00fa85e0)(&local_338);
      }
                    /* try { // try from 0058a346 to 0058a418 has its CatchHandler @ 0058b155 */
      (**(code **)(*plVar13 + 0x48))(0,0,DAT_00fa47fc,plVar13,pVVar11,0);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setShadowsEnabled(bVar5);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setClearEveryFrame(bVar5,1);
      local_2b8 = 0x3dc0c0c1;
      local_2b4 = 0x3dc0c0c1;
      local_2b0 = 0x3dc0c0c1;
      local_2ac = 0x3f800000;
      pCVar14 = (ColourValue *)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setBackgroundColour(pCVar14);
      bVar5 = (bool)(**(code **)(*plVar13 + 0x58))(plVar13,0);
      Ogre::Viewport::setOverlaysEnabled(bVar5);
      (**(code **)(*plVar13 + 0xf8))(plVar13,1);
      (**(code **)(*plVar13 + 0xc0))(plVar13);
    }
    pRVar15 = (Rectangle2D *)Ogre::NedAllocImpl::allocBytes(0x208,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00588d2e to 00588d32 has its CatchHandler @ 0058a744 */
    Ogre::Rectangle2D::Rectangle2D(pRVar15,true);
    fVar4 = DAT_00fa8760;
    fVar3 = DAT_00fa47fc;
    *(Rectangle2D **)(this + 0x240) = pRVar15;
                    /* try { // try from 00588d66 to 00588d6a has its CatchHandler @ 0058b155 */
    Ogre::Rectangle2D::setCorners(fVar4,fVar3,fVar3,fVar4);
    local_468 = DAT_00fa86f8 * Ogre::Vector3::UNIT_SCALE;
    local_45c = Ogre::Vector3::UNIT_SCALE * DAT_00fa86fc;
    local_448 = (void *)0x0;
    local_450 = 1;
    local_464 = DAT_00fa86f8 * DAT_0142463c;
    local_458 = DAT_0142463c * DAT_00fa86fc;
    local_460 = DAT_00fa86f8 * DAT_01424640;
    local_454 = DAT_01424640 * DAT_00fa86fc;
                    /* try { // try from 00588e19 to 00588e1d has its CatchHandler @ 0058b3b3 */
    Ogre::SimpleRenderable::setBoundingBox((AxisAlignedBox *)pRVar15);
    if (local_448 != (void *)0x0) {
                    /* try { // try from 00588e39 to 00588e6e has its CatchHandler @ 0058b155 */
      Ogre::NedAllocImpl::deallocBytes(local_448);
    }
    (**(code **)(*(long *)pRVar15 + 0x178))(pRVar15,4);
    plVar13 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
    pcVar1 = *(code **)(*plVar13 + 0x328);
                    /* try { // try from 00588e99 to 00588e9d has its CatchHandler @ 0058b3ae */
    std::string::string((string *)local_108,"ProjectorBackgroundQuad",&local_40);
                    /* try { // try from 00588eae to 00588eb1 has its CatchHandler @ 0058b375 */
    plVar13 = (long *)(*pcVar1)(plVar13,(string *)local_108,&Ogre::Vector3::ZERO,
                                &Ogre::Quaternion::IDENTITY);
    *(long **)(this + 0x218) = plVar13;
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_108[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
      plVar13 = *(long **)(this + 0x218);
    }
                    /* try { // try from 00588ee7 to 00588f2f has its CatchHandler @ 0058b155 */
    (**(code **)(*plVar13 + 0x278))(plVar13,pRVar15);
    lVar10 = Ogre::SceneNode::getParentSceneNode();
    if (lVar10 != 0) {
      plVar13 = (long *)Ogre::SceneNode::getParentSceneNode();
      (**(code **)(*plVar13 + 0x1e0))(plVar13,*(undefined8 *)(this + 0x218));
    }
    plVar13 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar1 = *(code **)(*plVar13 + 0x28);
                    /* try { // try from 00588f57 to 00588f5b has its CatchHandler @ 0058b387 */
    std::string::string((string *)local_118,"RttBackground",&local_41);
                    /* try { // try from 00588f7d to 00588f80 has its CatchHandler @ 0058b2f4 */
    (*pcVar1)(&local_358,plVar13,(string *)local_118,
              &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
    if (*(long *)(this + 0x250) != local_350) {
      piVar2 = *(int **)(this + 600);
      if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 0058a490 to 0058a492 has its CatchHandler @ 0058b469 */
        (**(code **)(*(long *)(this + 0x248) + 0x10))(this + 0x248);
      }
      *(long *)(this + 0x250) = local_350;
      *(int **)(this + 600) = local_348;
      if (local_348 != (int *)0x0) {
        *local_348 = *local_348 + 1;
      }
    }
    local_358 = &PTR__SharedPtr_00fa45d0;
    if ((local_348 != (int *)0x0) && (iVar7 = *local_348, *local_348 = iVar7 + -1, iVar7 + -1 == 0))
    {
                    /* try { // try from 0058a44a to 0058a44e has its CatchHandler @ 0058b2f4 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_358);
    }
    if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_118[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
                    /* try { // try from 00589027 to 0058906d has its CatchHandler @ 0058b155 */
    uVar6 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x250));
    psVar16 = (string *)Ogre::Technique::getPass(uVar6);
    bVar5 = SUB81(psVar16,0);
    Ogre::Pass::setLightingEnabled(bVar5);
    Ogre::Pass::setFog(DAT_00fa4828,0,DAT_00fa47fc,psVar16,1,0);
    local_4f8 = &DAT_01423a38;
                    /* try { // try from 0058908c to 00589090 has its CatchHandler @ 0058a9b3 */
    std::string::string((string *)&local_4f0,(string *)&::EMPTY_STRING);
                    /* try { // try from 0058909b to 0058909f has its CatchHandler @ 0058a9fa */
    std::wstring::wstring((wstring_conflict *)&local_4e8,(wstring_conflict *)&::EMPTY_WSTRING);
    local_4e0 = 4;
    local_4dc = 3;
    local_4d8 = &DAT_01423a38;
    local_4d0 = 0;
                    /* try { // try from 005890e2 to 005890e6 has its CatchHandler @ 0058ad86 */
    std::wstring::wstring
              ((wstring_conflict *)local_128,L"media/sharedtextures/shadowfade.dds",&local_42);
                    /* try { // try from 005890e7 to 00589104 has its CatchHandler @ 0058adbb */
    pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo
              (pCVar17,(wstring_conflict *)local_128,(CFileInfo *)&local_4f8,false,true,false);
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_128[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
                    /* try { // try from 0058912a to 00589154 has its CatchHandler @ 0058aa19 */
    Ogre::Pass::createTextureUnitState(psVar16,(ushort)&local_4f0);
    Ogre::Pass::setDepthWriteEnabled(bVar5);
    Ogre::Pass::setDepthCheckEnabled(bVar5);
    Ogre::Material::setSceneBlending(*(undefined8 *)(this + 0x250),0);
                    /* try { // try from 0058916d to 00589171 has its CatchHandler @ 0058afc9 */
    std::string::string((string *)local_138,"RttBackground",&local_43);
                    /* try { // try from 0058917a to 0058917e has its CatchHandler @ 0058afac */
    Ogre::SimpleRenderable::setMaterial((string *)pRVar15);
    if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_138[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
                    /* try { // try from 005891a4 to 005891cf has its CatchHandler @ 0058aa19 */
    (**(code **)(*(long *)pRVar15 + 0x140))(pRVar15,0x5e);
    (**(code **)(*(long *)pRVar15 + 0x178))(pRVar15);
    pRVar15 = (Rectangle2D *)Ogre::NedAllocImpl::allocBytes(0x208,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005891db to 005891df has its CatchHandler @ 0058abc1 */
    Ogre::Rectangle2D::Rectangle2D(pRVar15,true);
                    /* try { // try from 005891f9 to 005891fd has its CatchHandler @ 0058aa19 */
    Ogre::Rectangle2D::setCorners(DAT_00fa86f4,DAT_00fa4810,DAT_00fa4810,DAT_00fa86f4);
    local_498 = DAT_00fa86f8 * Ogre::Vector3::UNIT_SCALE;
    local_48c = Ogre::Vector3::UNIT_SCALE * DAT_00fa86fc;
    local_478 = (void *)0x0;
    local_480 = 1;
    local_494 = DAT_00fa86f8 * DAT_0142463c;
    local_488 = DAT_0142463c * DAT_00fa86fc;
    local_490 = DAT_00fa86f8 * DAT_01424640;
    local_484 = DAT_01424640 * DAT_00fa86fc;
                    /* try { // try from 005892aa to 005892ae has its CatchHandler @ 0058aba1 */
    Ogre::SimpleRenderable::setBoundingBox((AxisAlignedBox *)pRVar15);
    if (local_478 != (void *)0x0) {
                    /* try { // try from 005892bc to 005892de has its CatchHandler @ 0058aa19 */
      Ogre::NedAllocImpl::deallocBytes(local_478);
    }
    (**(code **)(*(long *)pRVar15 + 0x178))(pRVar15,2);
    plVar13 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
    pcVar1 = *(code **)(*plVar13 + 0x328);
                    /* try { // try from 00589308 to 0058930c has its CatchHandler @ 0058ab97 */
    std::string::string((string *)local_148,"ProjectorLightQuad",&local_44);
                    /* try { // try from 00589324 to 00589327 has its CatchHandler @ 0058ab80 */
    plVar13 = (long *)(*pcVar1)(plVar13,local_148,&Ogre::Vector3::ZERO,&Ogre::Quaternion::IDENTITY);
    *(long **)(this + 0x220) = plVar13;
    if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_148[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
      plVar13 = *(long **)(this + 0x220);
    }
                    /* try { // try from 0058934d to 0058938e has its CatchHandler @ 0058aa19 */
    (**(code **)(*plVar13 + 0x278))(plVar13,pRVar15);
    lVar10 = Ogre::SceneNode::getParentSceneNode();
    if (lVar10 != 0) {
      plVar13 = (long *)Ogre::SceneNode::getParentSceneNode();
      (**(code **)(*plVar13 + 0x1e0))(plVar13,*(undefined8 *)(this + 0x220));
    }
    *(Rectangle2D **)(this + 0x230) = pRVar15;
    plVar13 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar1 = *(code **)(*plVar13 + 0x28);
                    /* try { // try from 005893b5 to 005893b9 has its CatchHandler @ 0058a8b9 */
    std::string::string((string *)local_158,"RttLight",&local_45);
                    /* try { // try from 005893e2 to 005893e5 has its CatchHandler @ 0058a7bd */
    (*pcVar1)(&local_378,plVar13,local_158,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
              0,0,0);
    if (*(long *)(this + 0x270) != local_370) {
      piVar2 = *(int **)(this + 0x278);
      if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 0058a46a to 0058a46c has its CatchHandler @ 0058b220 */
        (**(code **)(*(long *)(this + 0x268) + 0x10))(this + 0x268);
      }
      *(long *)(this + 0x270) = local_370;
      *(int **)(this + 0x278) = local_368;
      if (local_368 != (int *)0x0) {
        *local_368 = *local_368 + 1;
      }
    }
    local_378 = &PTR__SharedPtr_00fa45d0;
    if ((local_368 != (int *)0x0) && (iVar7 = *local_368, *local_368 = iVar7 + -1, iVar7 + -1 == 0))
    {
                    /* try { // try from 0058a438 to 0058a43c has its CatchHandler @ 0058a7bd */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_378);
    }
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_158[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* try { // try from 0058947e to 005894c4 has its CatchHandler @ 0058aa19 */
    uVar6 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x270));
    psVar16 = (string *)Ogre::Technique::getPass(uVar6);
    bVar5 = SUB81(psVar16,0);
    Ogre::Pass::setLightingEnabled(bVar5);
    Ogre::Pass::setFog(DAT_00fa4828,0,DAT_00fa47fc,psVar16,1,0);
                    /* try { // try from 005894da to 005894de has its CatchHandler @ 0058ad12 */
    std::wstring::wstring
              ((wstring_conflict *)local_168,L"media/sharedtextures/lantern.dds",&local_46);
                    /* try { // try from 005894df to 00589501 has its CatchHandler @ 0058acfb */
    pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo
              (pCVar17,(wstring_conflict *)local_168,(CFileInfo *)&local_4f8,false,true,false);
    if ((allocator *)(local_168[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_168[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
                    /* try { // try from 00589528 to 00589555 has its CatchHandler @ 0058aa19 */
    Ogre::Pass::createTextureUnitState(psVar16,(ushort)&local_4f0);
    Ogre::Pass::setDepthWriteEnabled(bVar5);
    Ogre::Pass::setDepthCheckEnabled(bVar5);
    Ogre::Material::setSceneBlending(*(undefined8 *)(this + 0x270),4);
                    /* try { // try from 0058956b to 0058956f has its CatchHandler @ 0058ac9a */
    std::string::string((string *)local_178,"RttLight",&local_47);
                    /* try { // try from 0058957b to 0058957f has its CatchHandler @ 0058accb */
    Ogre::SimpleRenderable::setMaterial((string *)pRVar15);
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_178[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
                    /* try { // try from 0058959d to 005895b2 has its CatchHandler @ 0058aa19 */
    (**(code **)(*(long *)pRVar15 + 0x140))(pRVar15);
    pRVar15 = (Rectangle2D *)Ogre::NedAllocImpl::allocBytes(0x208,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005895be to 005895c2 has its CatchHandler @ 0058aeea */
    Ogre::Rectangle2D::Rectangle2D(pRVar15,true);
    fVar3 = DAT_00fa8760;
    *(Rectangle2D **)(this + 0x238) = pRVar15;
                    /* try { // try from 005895e3 to 005895e7 has its CatchHandler @ 0058aa19 */
    Ogre::Rectangle2D::setCorners(fVar3,DAT_00fa47fc,DAT_00fa47fc,fVar3);
    local_4c8 = DAT_00fa86f8 * Ogre::Vector3::UNIT_SCALE;
    local_4bc = Ogre::Vector3::UNIT_SCALE * DAT_00fa86fc;
    local_4a8 = (void *)0x0;
    local_4b0 = 1;
    local_4c4 = DAT_00fa86f8 * DAT_0142463c;
    local_4b8 = DAT_0142463c * DAT_00fa86fc;
    local_4c0 = DAT_00fa86f8 * DAT_01424640;
    local_4b4 = DAT_00fa86fc * DAT_01424640;
                    /* try { // try from 00589698 to 0058969c has its CatchHandler @ 0058aecf */
    Ogre::SimpleRenderable::setBoundingBox((AxisAlignedBox *)pRVar15);
    if (local_4a8 != (void *)0x0) {
                    /* try { // try from 005896aa to 005896bb has its CatchHandler @ 0058aa19 */
      Ogre::NedAllocImpl::deallocBytes(local_4a8);
    }
    plVar13 = (long *)(**(code **)(**(long **)(this + 0x28) + 0x250))();
    pcVar1 = *(code **)(*plVar13 + 0x328);
                    /* try { // try from 005896e5 to 005896e9 has its CatchHandler @ 0058aeca */
    std::string::string((string *)local_188,"ProjectorLightMask",&local_48);
                    /* try { // try from 00589701 to 00589704 has its CatchHandler @ 0058aeb3 */
    plVar13 = (long *)(*pcVar1)(plVar13,local_188,&Ogre::Vector3::ZERO,&Ogre::Quaternion::IDENTITY);
    *(long **)(this + 0x228) = plVar13;
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_188[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
      plVar13 = *(long **)(this + 0x228);
    }
                    /* try { // try from 0058972a to 00589764 has its CatchHandler @ 0058aa19 */
    (**(code **)(*plVar13 + 0x278))(plVar13,pRVar15);
    lVar10 = Ogre::SceneNode::getParentSceneNode();
    if (lVar10 != 0) {
      plVar13 = (long *)Ogre::SceneNode::getParentSceneNode();
      (**(code **)(*plVar13 + 0x1e0))(plVar13,*(undefined8 *)(this + 0x228));
    }
    plVar13 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar1 = *(code **)(*plVar13 + 0x28);
                    /* try { // try from 0058978b to 0058978f has its CatchHandler @ 0058b00d */
    std::string::string((string *)local_198,"RttLightMask",&local_49);
                    /* try { // try from 005897b8 to 005897bb has its CatchHandler @ 0058afea */
    (*pcVar1)(&local_398,plVar13,local_198,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
              0,0,0);
    if (*(long *)(this + 0x290) != local_390) {
      piVar2 = *(int **)(this + 0x298);
      if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 0058a4b0 to 0058a4b2 has its CatchHandler @ 0058b480 */
        (**(code **)(*(long *)(this + 0x288) + 0x10))(this + 0x288);
      }
      *(long *)(this + 0x290) = local_390;
      *(int **)(this + 0x298) = local_388;
      if (local_388 != (int *)0x0) {
        *local_388 = *local_388 + 1;
      }
    }
    local_398 = &PTR__SharedPtr_00fa45d0;
    if ((local_388 != (int *)0x0) && (iVar7 = *local_388, *local_388 = iVar7 + -1, iVar7 + -1 == 0))
    {
                    /* try { // try from 0058a426 to 0058a42a has its CatchHandler @ 0058afea */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_398);
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_198[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* try { // try from 00589854 to 0058989a has its CatchHandler @ 0058aa19 */
    uVar6 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x290));
    psVar16 = (string *)Ogre::Technique::getPass(uVar6);
    bVar5 = SUB81(psVar16,0);
    Ogre::Pass::setLightingEnabled(bVar5);
    Ogre::Pass::setFog(DAT_00fa4828,0,DAT_00fa47fc,psVar16,1,0);
                    /* try { // try from 005898b0 to 005898b4 has its CatchHandler @ 0058af6d */
    std::wstring::wstring
              ((wstring_conflict *)local_1a8,L"media/sharedtextures/lightmask.dds",&local_4a);
                    /* try { // try from 005898b5 to 005898d7 has its CatchHandler @ 0058aab9 */
    pCVar17 = (CFileSystem *)CFileSystem::getSingleton();
    CFileSystem::getFileInfo
              (pCVar17,(wstring_conflict *)local_1a8,(CFileInfo *)&local_4f8,false,true,false);
    if ((allocator *)(local_1a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1a8[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
                    /* try { // try from 005898fe to 00589928 has its CatchHandler @ 0058aa19 */
    Ogre::Pass::createTextureUnitState(psVar16,(ushort)&local_4f0);
    Ogre::Pass::setDepthWriteEnabled(bVar5);
    Ogre::Pass::setDepthCheckEnabled(bVar5);
    Ogre::Material::setSceneBlending(*(undefined8 *)(this + 0x290),0);
                    /* try { // try from 00589941 to 00589945 has its CatchHandler @ 0058b237 */
    std::string::string((string *)local_1b8,"RttLightMask",&local_4b);
                    /* try { // try from 0058994c to 00589950 has its CatchHandler @ 0058b51e */
    Ogre::SimpleRenderable::setMaterial((string *)pRVar15);
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_1b8[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* try { // try from 00589971 to 005899b8 has its CatchHandler @ 0058aa19 */
    (**(code **)(*(long *)pRVar15 + 0x140))(pRVar15,99);
    (**(code **)(*(long *)pRVar15 + 0x178))(pRVar15,2);
    uVar19 = 0;
    pCVar20 = this;
    do {
      plVar13 = (long *)Ogre::MaterialManager::getSingleton();
      pcVar1 = *(code **)(*plVar13 + 0xa0);
      STRINGS::GetValueAsString((uint)local_1c8);
                    /* try { // try from 005899ce to 005899d2 has its CatchHandler @ 0058b4eb */
      std::operator+((char *)local_1d8,(string *)"RenderShadow");
                    /* try { // try from 005899e8 to 005899eb has its CatchHandler @ 0058b4cc */
      (*pcVar1)(&local_3b8,plVar13,local_1d8);
      if (*(long *)(pCVar20 + 0x10c8) != local_3b0) {
        piVar2 = *(int **)(pCVar20 + 0x10d0);
        if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589a2a to 00589a2c has its CatchHandler @ 0058b53b */
          (**(code **)(*(long *)(pCVar20 + 0x10c0) + 0x10))(this + uVar19 * 0x20 + 0x10c0);
        }
        *(long *)(pCVar20 + 0x10c8) = local_3b0;
        *(int **)(pCVar20 + 0x10d0) = local_3a8;
        if (local_3a8 != (int *)0x0) {
          *local_3a8 = *local_3a8 + 1;
        }
      }
      local_3b8 = &PTR__SharedPtr_00fa45d0;
      if ((local_3a8 != (int *)0x0) &&
         (iVar7 = *local_3a8, *local_3a8 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589a7f to 00589a83 has its CatchHandler @ 0058b4cc */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_3b8);
      }
      if ((allocator *)(local_1d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1d8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1c8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
        }
      }
                    /* try { // try from 00589aae to 00589ad6 has its CatchHandler @ 0058aa19 */
      plVar13 = (long *)Ogre::MaterialManager::getSingleton();
      pcVar1 = *(code **)(*plVar13 + 0xa0);
      STRINGS::GetValueAsString((uint)local_1e8);
                    /* try { // try from 00589aec to 00589af0 has its CatchHandler @ 0058b281 */
      std::operator+((char *)local_1f8,(string *)"RenderShadowSkinned");
                    /* try { // try from 00589b06 to 00589b09 has its CatchHandler @ 0058b27a */
      (*pcVar1)(&local_3d8,plVar13,local_1f8);
      if (*(long *)(pCVar20 + 0x18c8) != local_3d0) {
        piVar2 = *(int **)(pCVar20 + 0x18d0);
        if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589b48 to 00589b4a has its CatchHandler @ 0058b24e */
          (**(code **)(*(long *)(pCVar20 + 0x18c0) + 0x10))(this + uVar19 * 0x20 + 0x18c0);
        }
        *(long *)(pCVar20 + 0x18c8) = local_3d0;
        *(int **)(pCVar20 + 0x18d0) = local_3c8;
        if (local_3c8 != (int *)0x0) {
          *local_3c8 = *local_3c8 + 1;
        }
      }
      local_3d8 = &PTR__SharedPtr_00fa45d0;
      if ((local_3c8 != (int *)0x0) &&
         (iVar7 = *local_3c8, *local_3c8 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589b9d to 00589ba1 has its CatchHandler @ 0058b27a */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_3d8);
      }
      if ((allocator *)(local_1f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1f8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1e8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
        }
      }
                    /* try { // try from 00589bcc to 00589bf4 has its CatchHandler @ 0058aa19 */
      plVar13 = (long *)Ogre::MaterialManager::getSingleton();
      pcVar1 = *(code **)(*plVar13 + 0xa0);
      STRINGS::GetValueAsString((uint)local_208);
                    /* try { // try from 00589c0a to 00589c0e has its CatchHandler @ 0058b23c */
      std::operator+((char *)local_218,(string *)"RenderShadowSkinnedThree");
                    /* try { // try from 00589c24 to 00589c27 has its CatchHandler @ 0058b2bd */
      (*pcVar1)(&local_3f8,plVar13,local_218);
      if (*(long *)(pCVar20 + 0x20c8) != local_3f0) {
        piVar2 = *(int **)(pCVar20 + 0x20d0);
        if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589c66 to 00589c68 has its CatchHandler @ 0058b29c */
          (**(code **)(*(long *)(pCVar20 + 0x20c0) + 0x10))(this + uVar19 * 0x20 + 0x20c0);
        }
        *(long *)(pCVar20 + 0x20c8) = local_3f0;
        *(int **)(pCVar20 + 0x20d0) = local_3e8;
        if (local_3e8 != (int *)0x0) {
          *local_3e8 = *local_3e8 + 1;
        }
      }
      local_3f8 = &PTR__SharedPtr_00fa45d0;
      if ((local_3e8 != (int *)0x0) &&
         (iVar7 = *local_3e8, *local_3e8 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589cbb to 00589cbf has its CatchHandler @ 0058b2bd */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_3f8);
      }
      if ((allocator *)(local_218[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_218[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
        }
      }
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_208[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
                    /* try { // try from 00589cea to 00589d12 has its CatchHandler @ 0058aa19 */
      plVar13 = (long *)Ogre::MaterialManager::getSingleton();
      pcVar1 = *(code **)(*plVar13 + 0xa0);
      STRINGS::GetValueAsString((uint)local_228);
                    /* try { // try from 00589d28 to 00589d2c has its CatchHandler @ 0058b292 */
      std::operator+((char *)local_238,(string *)"RenderShadowSkinnedTwo");
                    /* try { // try from 00589d42 to 00589d45 has its CatchHandler @ 0058b288 */
      (*pcVar1)(&local_418,plVar13,local_238);
      if (*(long *)(pCVar20 + 0x28c8) != local_410) {
        piVar2 = *(int **)(pCVar20 + 0x28d0);
        if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589d84 to 00589d86 has its CatchHandler @ 0058aae8 */
          (**(code **)(*(long *)(pCVar20 + 0x28c0) + 0x10))(this + uVar19 * 0x20 + 0x28c0);
        }
        *(long *)(pCVar20 + 0x28c8) = local_410;
        *(int **)(pCVar20 + 0x28d0) = local_408;
        if (local_408 != (int *)0x0) {
          *local_408 = *local_408 + 1;
        }
      }
      local_418 = &PTR__SharedPtr_00fa45d0;
      if ((local_408 != (int *)0x0) &&
         (iVar7 = *local_408, *local_408 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589dd9 to 00589ddd has its CatchHandler @ 0058b288 */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_418);
      }
      if ((allocator *)(local_238[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_238[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
        }
      }
      if ((allocator *)(local_228[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_228[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
        }
      }
                    /* try { // try from 00589e08 to 00589e30 has its CatchHandler @ 0058aa19 */
      plVar13 = (long *)Ogre::MaterialManager::getSingleton();
      pcVar1 = *(code **)(*plVar13 + 0xa0);
      STRINGS::GetValueAsString((uint)local_248);
                    /* try { // try from 00589e46 to 00589e4a has its CatchHandler @ 0058ac85 */
      std::operator+((char *)local_258,(string *)"RenderShadowSkinnedOne");
                    /* try { // try from 00589e60 to 00589e63 has its CatchHandler @ 0058ab3f */
      (*pcVar1)(&local_438,plVar13,local_258);
      if (*(long *)(pCVar20 + 0x30c8) != local_430) {
        piVar2 = *(int **)(pCVar20 + 0x30d0);
        if ((piVar2 != (int *)0x0) && (iVar7 = *piVar2, *piVar2 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589ea2 to 00589ea4 has its CatchHandler @ 0058ab16 */
          (**(code **)(*(long *)(pCVar20 + 0x30c0) + 0x10))(this + uVar19 * 0x20 + 0x30c0);
        }
        *(long *)(pCVar20 + 0x30c8) = local_430;
        *(int **)(pCVar20 + 0x30d0) = local_428;
        if (local_428 != (int *)0x0) {
          *local_428 = *local_428 + 1;
        }
      }
      local_438 = &PTR__SharedPtr_00fa45d0;
      if ((local_428 != (int *)0x0) &&
         (iVar7 = *local_428, *local_428 = iVar7 + -1, iVar7 + -1 == 0)) {
                    /* try { // try from 00589ef7 to 00589efb has its CatchHandler @ 0058ab3f */
        Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_438);
      }
      if ((allocator *)(local_258[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_258[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
        }
      }
      if ((allocator *)(local_248[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_248[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
        }
      }
      uVar21 = (int)uVar19 + 1;
      uVar19 = (ulong)uVar21;
      pCVar20 = pCVar20 + 0x20;
    } while (uVar21 != 0x40);
    *(Vector3 **)(*(long *)(this + 0x20) + 0x28) = pVVar11;
    *(Vector3 **)(*(long *)(this + 0x20) + 0x30) = pVVar12;
    if ((allocator *)(local_4d8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_4d8 + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4d8 + -0x18));
      }
    }
    if ((allocator *)(local_4e8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_4e8 + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_4e8 + -0x18));
      }
    }
    if ((allocator *)(local_4f0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_4f0 + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4f0 + -0x18));
      }
    }
    if ((allocator *)(local_4f8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_4f8 + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_4f8 + -0x18));
      }
    }
  }
                    /* try { // try from 00589fb9 to 00589fdb has its CatchHandler @ 0058b155 */
  lVar10 = CDungeonManager::getSingleton();
  *(undefined8 *)(this + 0x38d8) = **(undefined8 **)(lVar10 + 0x18);
  this_01 = (CQuestManager *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00589fe9 to 00589fed has its CatchHandler @ 0058afd8 */
  CQuestManager::CQuestManager(this_01,*(CResourceManager **)(this + 0x2b8));
  *(CQuestManager **)(this + 0x68) = this_01;
  KSkillSlotsKeys = KSETTINGS_KEYMAP_1;
  DAT_01428664 = KSETTINGS_KEYMAP_2;
  DAT_01428668 = KSETTINGS_KEYMAP_3;
  DAT_0142866c = KSETTINGS_KEYMAP_4;
  _DAT_01428670 = KSETTINGS_KEYMAP_5;
  _DAT_01428674 = KSETTINGS_KEYMAP_6;
  _DAT_01428678 = KSETTINGS_KEYMAP_7;
  _DAT_0142867c = KSETTINGS_KEYMAP_8;
  _DAT_01428680 = KSETTINGS_KEYMAP_9;
  _DAT_01428684 = KSETTINGS_KEYMAP_0;
  KSkillSlotsFunctionKeys._0_4_ = KSETTINGS_FKEYMAP_1;
  KSkillSlotsFunctionKeys._4_4_ = KSETTINGS_FKEYMAP_2;
  KSkillSlotsFunctionKeys._8_4_ = KSETTINGS_FKEYMAP_3;
  KSkillSlotsFunctionKeys._12_4_ = KSETTINGS_FKEYMAP_4;
  KSkillSlotsFunctionKeys._16_4_ = KSETTINGS_FKEYMAP_5;
  KSkillSlotsFunctionKeys._20_4_ = KSETTINGS_FKEYMAP_6;
  KSkillSlotsFunctionKeys._24_4_ = KSETTINGS_FKEYMAP_7;
  KSkillSlotsFunctionKeys._28_4_ = KSETTINGS_FKEYMAP_8;
  KSkillSlotsFunctionKeys._32_4_ = KSETTINGS_FKEYMAP_9;
  KSkillSlotsFunctionKeys._36_4_ = KSETTINGS_FKEYMAP_10;
  KSkillSlotsFunctionKeys._40_4_ = KSETTINGS_FKEYMAP_11;
  KSkillSlotsFunctionKeys._44_4_ = KSETTINGS_FKEYMAP_12;
  return;
}



/* address=0058b5d0
   symbol=CGameClient::saveCharacter */

/* WARNING: Removing unreachable block (ram,0x0058ce4b) */
/* WARNING: Removing unreachable block (ram,0x0058ce09) */
/* WARNING: Removing unreachable block (ram,0x0058cd9b) */
/* WARNING: Removing unreachable block (ram,0x0058cd2d) */
/* WARNING: Removing unreachable block (ram,0x0058cc7a) */
/* WARNING: Removing unreachable block (ram,0x0058ccbc) */
/* WARNING: Removing unreachable block (ram,0x0058cb7e) */
/* WARNING: Removing unreachable block (ram,0x0058cf47) */
/* WARNING: Removing unreachable block (ram,0x0058cf00) */
/* WARNING: Removing unreachable block (ram,0x0058d08d) */
/* WARNING: Removing unreachable block (ram,0x0058d0f9) */
/* WARNING: Removing unreachable block (ram,0x0058cf0b) */
/* WARNING: Removing unreachable block (ram,0x0058d0be) */
/* WARNING: Removing unreachable block (ram,0x0058d07f) */
/* WARNING: Removing unreachable block (ram,0x0058ccca) */
/* WARNING: Removing unreachable block (ram,0x0058cc85) */
/* WARNING: Removing unreachable block (ram,0x0058cd38) */
/* WARNING: Removing unreachable block (ram,0x0058cda6) */
/* WARNING: Removing unreachable block (ram,0x0058ce14) */
/* WARNING: Removing unreachable block (ram,0x0058ce56) */
/* WARNING: Type propagation algorithm not settling */
/* CGameClient::saveCharacter(bool, bool) */

void __thiscall CGameClient::saveCharacter(CGameClient *this,bool param_1,bool param_2)

{
  int *piVar1;
  allocator *paVar2;
  undefined2 *puVar3;
  short *psVar4;
  wchar_t wVar5;
  undefined4 *puVar6;
  char cVar7;
  CSharedStash *this_00;
  wchar_t *pwVar8;
  undefined8 uVar9;
  CCharacterSaveState *pCVar10;
  undefined8 *puVar11;
  char *pcVar12;
  short *psVar13;
  wchar_t *pwVar14;
  long lVar15;
  long *plVar16;
  short *psVar17;
  ushort uVar18;
  ulong uVar19;
  long lVar20;
  wstring_conflict *pwVar21;
  int iVar22;
  uint uVar23;
  short sVar24;
  short sVar25;
  short *local_2c8;
  int local_2c0;
  undefined8 local_2b8;
  wstring_conflict *local_2b0;
  undefined2 *local_2a8;
  undefined4 local_2a0;
  undefined8 local_298;
  undefined8 local_290;
  UTFString local_288 [32];
  undefined2 *local_268;
  undefined4 local_260;
  undefined8 local_258;
  undefined8 local_250;
  undefined2 *local_248;
  undefined4 local_240;
  undefined8 local_238;
  undefined8 local_230;
  undefined8 local_228;
  undefined4 local_220;
  string local_218 [16];
  long local_208 [2];
  long local_1f8 [2];
  long local_1e8 [2];
  char *local_1d8 [2];
  char *local_1c8 [2];
  char *local_1b8 [2];
  long local_1a8;
  undefined8 local_1a0;
  long local_198 [2];
  string local_188 [16];
  char *local_178 [2];
  wstring_conflict local_168 [16];
  wstring_conflict local_158 [16];
  FILESYSTEM local_148 [16];
  wchar_t *local_138 [2];
  string local_128 [8];
  FILE *local_120;
  long local_118 [2];
  char *local_108 [2];
  long local_f8 [2];
  wchar_t *local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  long local_88;
  int local_80 [3];
  int local_74;
  uint local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  ushort local_5c;
  ushort local_5a [11];
  allocator local_43;
  undefined1 local_42;
  undefined1 local_41;
  undefined1 local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x58) == 0) {
    return;
  }
  this_00 = (CSharedStash *)CSharedStash::getSingleton();
  CSharedStash::saveSharedStash(this_00);
  if ((!param_1) && (cVar7 = CCharacter::alive(*(CCharacter **)(this + 0x58)), cVar7 == '\0')) {
    return;
  }
  if ((*(CLevel **)(this + 0x70) != (CLevel *)0x0) && (param_2)) {
    iVar22 = 0;
    CLevel::updateLayouts(*(CLevel **)(this + 0x70),DAT_00fa4828);
    do {
      iVar22 = iVar22 + 1;
      CLevel::updateLayouts(*(CLevel **)(this + 0x70),DAT_00fa4824);
    } while (iVar22 != 10);
  }
  CPlayer::storeLevelSavedState(*(CLevel **)(this + 0x58));
  FILESYSTEM::GetSaveDataPath((FILESYSTEM *)&local_88);
                    /* try { // try from 0058b63a to 0058b66f has its CatchHandler @ 0058ce64 */
  cVar7 = FILESYSTEM::FileExists((wstring_conflict *)&local_88);
  if (cVar7 == '\0') {
    FILESYSTEM::CreateAppDataDirectory((wstring_conflict *)&local_88);
  }
  FILESYSTEM::AssembleAbsolutePath
            ((FILESYSTEM *)local_98,(wstring_conflict *)&local_88,
             (wstring_conflict *)(*(long *)(this + 0x78) + 0x16c0));
                    /* try { // try from 0058b688 to 0058b68c has its CatchHandler @ 0058ce6d */
  std::wstring::wstring((wstring_conflict *)local_b8,L"save.tmp",local_39);
                    /* try { // try from 0058b6a3 to 0058b6a7 has its CatchHandler @ 0058d039 */
  FILESYSTEM::AssembleAbsolutePath
            ((FILESYSTEM *)local_a8,(wstring_conflict *)&local_88,(wstring_conflict *)local_b8);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 0058b6d9 to 0058b6dd has its CatchHandler @ 0058d010 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"backup.tmp",&local_3a);
                    /* try { // try from 0058b6f1 to 0058b6f5 has its CatchHandler @ 0058d012 */
  FILESYSTEM::AssembleAbsolutePath
            ((FILESYSTEM *)local_c8,(wstring_conflict *)&local_88,(wstring_conflict *)local_d8);
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 0058b720 to 0058b724 has its CatchHandler @ 0058d076 */
  std::operator+((wchar_t *)local_e8,(wstring_conflict *)L"Saving character to :");
  if (*(long *)(local_a8[0] + -6) != 0) {
    uVar19 = 0;
    iVar22 = 0;
    pwVar8 = local_a8[0];
    do {
      if (L'\xffffffff' < pwVar8[-2]) {
                    /* try { // try from 0058b767 to 0058b78f has its CatchHandler @ 0058cf42 */
        std::wstring::_M_leak_hard();
        pwVar8 = local_a8[0];
      }
      pwVar14 = pwVar8 + uVar19;
      if (*pwVar14 == L'\\') {
        if (L'\xffffffff' < pwVar8[-2]) {
          std::wstring::_M_leak_hard();
          pwVar14 = local_a8[0] + uVar19;
        }
        *pwVar14 = L'/';
        pwVar8 = local_a8[0];
      }
      iVar22 = iVar22 + 1;
      uVar19 = (ulong)iVar22;
    } while (uVar19 < *(ulong *)(pwVar8 + -6));
  }
                    /* try { // try from 0058b91b to 0058b91f has its CatchHandler @ 0058ce76 */
  std::wstring::wstring((wstring_conflict *)local_f8,local_e8[0],&local_3b);
                    /* try { // try from 0058b92e to 0058b932 has its CatchHandler @ 0058ce7b */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_108);
                    /* try { // try from 0058b94e to 0058b952 has its CatchHandler @ 0058ce8c */
  std::string::string((string *)local_118,local_108[0],&local_3c);
                    /* try { // try from 0058b953 to 0058b969 has its CatchHandler @ 0058ce9a */
  uVar9 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar9,(string *)local_118,3,0);
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar22 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 0058b9cc to 0058ba0a has its CatchHandler @ 0058cf42 */
  iVar22 = _wfopen_s(&local_120,local_a8[0],L"wb");
  if (local_120 != (FILE *)0x0) {
    fwrite(&m_gFileVersion,4,1,local_120);
    std::wstring::wstring
              ((wstring_conflict *)local_198,(wstring_conflict *)(*(long *)(this + 0x58) + 0x40));
    local_5a[0] = (ushort)*(undefined8 *)(local_198[0] + -0x18);
                    /* try { // try from 0058ba39 to 0058bb28 has its CatchHandler @ 0058cf52 */
    fwrite(local_5a,2,1,local_120);
    WriteUTF32ToUTF16(local_120,(wstring_conflict *)local_198,(ulong)local_5a[0]);
    local_60 = *(undefined4 *)(this + 0x38ec);
    fwrite(&local_60,4,1,local_120);
    local_40 = *(undefined1 *)(*(long *)(this + 0x58) + 0xa15);
    fwrite(&local_40,1,1,local_120);
    local_64 = *(undefined4 *)(*(long *)(this + 0x58) + 0xa10);
    fwrite(&local_64,4,1,local_120);
    local_41 = *(undefined1 *)(*(long *)(this + 0x58) + 0xa14);
    fwrite(&local_41,1,1,local_120);
    pCVar10 = (CCharacterSaveState *)Ogre::NedAllocImpl::allocBytes(0x228,(char *)0x0,0,(char *)0x0)
    ;
                    /* try { // try from 0058bb2f to 0058bb33 has its CatchHandler @ 0058cf5b */
    CCharacterSaveState::CCharacterSaveState(pCVar10);
                    /* try { // try from 0058bb3e to 0058bd8d has its CatchHandler @ 0058cf52 */
    (**(code **)(**(long **)(this + 0x58) + 0x298))(*(long **)(this + 0x58),pCVar10);
    *(undefined4 *)(pCVar10 + 0x60) = *(undefined4 *)(this + 0x1090);
    pCVar10[0x34] = *(CCharacterSaveState *)(*(long *)(this + 0x58) + 0x791);
    CCharacterSaveState::save(pCVar10,local_120);
    (**(code **)(*(long *)pCVar10 + 8))(pCVar10);
    local_5c = 10;
    fwrite(&local_5c,2,1,local_120);
    if (local_5c != 0) {
      uVar18 = 0;
      do {
        local_1a0 = *(undefined8 *)(*(long *)(this + 0x58) + 0x8b0 + (ulong)uVar18 * 8);
        fwrite(&local_1a0,8,1,local_120);
        uVar18 = uVar18 + 1;
      } while (uVar18 < local_5c);
    }
    local_5c = 0xc;
    fwrite(&local_5c,2,1,local_120);
    if (local_5c != 0) {
      uVar18 = 0;
      do {
        local_1a0 = *(undefined8 *)(*(long *)(this + 0x58) + 0x950 + (ulong)uVar18 * 8);
        fwrite(&local_1a0,8,1,local_120);
        local_1a0 = *(undefined8 *)(*(long *)(this + 0x58) + 0x9b0 + (ulong)uVar18 * 8);
        fwrite(&local_1a0,8,1,local_120);
        uVar18 = uVar18 + 1;
      } while (uVar18 < local_5c);
    }
    local_5c = 10;
    fwrite(&local_5c,2,1,local_120);
    if (local_5c != 0) {
      uVar18 = 0;
      do {
        local_1a0 = *(undefined8 *)(*(long *)(this + 0x58) + 0x900 + (ulong)uVar18 * 8);
        fwrite(&local_1a0,8,1,local_120);
        uVar18 = uVar18 + 1;
      } while (uVar18 < local_5c);
    }
    iVar22 = 0;
    do {
      local_1a0 = CONCAT44(local_1a0._4_4_,
                           *(undefined4 *)(*(long *)(this + 0x58) + 0x7dc + (long)iVar22 * 4));
      fwrite(&local_1a0,4,1,local_120);
      iVar22 = iVar22 + 1;
    } while (iVar22 != 0x12);
    pwVar21 = (wstring_conflict *)&::EMPTY_WSTRING;
    if (*(long *)(this + 0x70) != 0) {
      pwVar21 = (wstring_conflict *)(*(long *)(this + 0x70) + 0x280);
    }
    std::wstring::wstring((wstring_conflict *)&local_1a8,pwVar21);
    local_5a[0] = (ushort)*(undefined8 *)(local_1a8 + -0x18);
                    /* try { // try from 0058bdbc to 0058bfc7 has its CatchHandler @ 0058cf6c */
    fwrite(local_5a,2,1,local_120);
    WriteUTF32ToUTF16(local_120,(wstring_conflict *)&local_1a8,(ulong)local_5a[0]);
    std::wstring::assign((wstring_conflict *)&local_1a8);
    local_5a[0] = (ushort)*(undefined8 *)(local_1a8 + -0x18);
    fwrite(local_5a,2,1,local_120);
    WriteUTF32ToUTF16(local_120,(wstring_conflict *)&local_1a8,(ulong)local_5a[0]);
    local_68 = *(undefined4 *)(*(long *)(this + 0x58) + 0x7cc);
    fwrite(&local_68,4,1,local_120);
    local_42 = *(undefined1 *)(*(long *)(this + 0x58) + 0x7b0);
    fwrite(&local_42,1,1,local_120);
    local_228 = *(undefined8 *)(*(long *)(this + 0x58) + 0x7c0);
    local_220 = *(undefined4 *)(*(long *)(this + 0x58) + 0x7c8);
    fwrite(&local_228,0xc,1,local_120);
    std::wstring::assign((wstring_conflict *)&local_1a8);
    local_5a[0] = (ushort)*(undefined8 *)(local_1a8 + -0x18);
    fwrite(local_5a,2,1,local_120);
    WriteUTF32ToUTF16(local_120,(wstring_conflict *)&local_1a8,(ulong)local_5a[0]);
    local_6c = *(undefined4 *)(*(long *)(this + 0x58) + 0x7b4);
    fwrite(&local_6c,4,1,local_120);
    local_70 = (uint)(*(long *)(*(long *)(this + 0x58) + 0x650) -
                      *(long *)(*(long *)(this + 0x58) + 0x648) >> 3);
    fwrite(&local_70,4,1,local_120);
    if (local_70 != 0) {
      uVar19 = 0;
      do {
        pCVar10 = (CCharacterSaveState *)
                  Ogre::NedAllocImpl::allocBytes(0x228,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0058bfce to 0058bfd2 has its CatchHandler @ 0058cf75 */
        CCharacterSaveState::CCharacterSaveState(pCVar10);
        plVar16 = (long *)0x0;
        lVar20 = *(long *)(*(long *)(this + 0x58) + 0x648);
        if (*(long *)(*(long *)(this + 0x58) + 0x650) - lVar20 >> 3 != 0) {
          plVar16 = *(long **)(lVar20 + uVar19 * 8);
        }
                    /* try { // try from 0058c000 to 0058c1d7 has its CatchHandler @ 0058cf6c */
        (**(code **)(*plVar16 + 0x298))(plVar16,pCVar10);
        CCharacterSaveState::save(pCVar10,local_120);
        if (pCVar10 != (CCharacterSaveState *)0x0) {
          (**(code **)(*(long *)pCVar10 + 8))(pCVar10);
        }
        uVar23 = (int)uVar19 + 1;
        uVar19 = (ulong)uVar23;
      } while (uVar23 < local_70);
    }
    iVar22 = 0;
    do {
      local_1a0 = CONCAT71(local_1a0._1_7_,
                           *(undefined1 *)(*(long *)(this + 0x58) + 0xa17 + (long)iVar22));
      fwrite(&local_1a0,1,1,local_120);
      iVar22 = iVar22 + 1;
    } while (iVar22 != 0x22);
    local_74 = (int)(*(long *)(*(long *)(this + 0x58) + 0x7a0) -
                     *(long *)(*(long *)(this + 0x58) + 0x798) >> 3);
    fwrite(&local_74,4,1,local_120);
    if (0 < local_74) {
      lVar20 = 0;
      iVar22 = 0;
      do {
        CLevelState::save(*(CLevelState **)(*(long *)(*(long *)(this + 0x58) + 0x798) + lVar20),
                          local_120);
        iVar22 = iVar22 + 1;
        lVar20 = lVar20 + 8;
      } while (iVar22 < local_74);
    }
    local_80[2] = *(int *)(*(long *)(this + 0x58) + 0xa48);
    fwrite(local_80 + 2,4,1,local_120);
    if (0 < local_80[2]) {
      lVar20 = 0;
      uVar23 = 0;
      do {
        lVar15 = *(long *)(this + 0x58);
        if (uVar23 < *(uint *)(lVar15 + 0xa4c)) {
          puVar11 = (undefined8 *)(lVar20 + *(long *)(lVar15 + 0xa40));
        }
        else {
          puVar11 = *(undefined8 **)(lVar15 + 0xa40);
        }
        CDungeonTracker::save((CDungeonTracker *)*puVar11,local_120);
        uVar23 = uVar23 + 1;
        lVar20 = lVar20 + 8;
      } while ((int)uVar23 < local_80[2]);
    }
    local_80[1] = 0;
    if (*(CQuestManager **)(this + 0x68) == (CQuestManager *)0x0) {
                    /* try { // try from 0058c978 to 0058c97c has its CatchHandler @ 0058cf6c */
      fwrite(local_80 + 1,4,1,local_120);
    }
    else {
      CQuestManager::save(*(CQuestManager **)(this + 0x68),local_120);
    }
    lVar20 = ftell(local_120);
    local_80[0] = (int)lVar20 + 4;
    fwrite(local_80,4,1,local_120);
    fclose(local_120);
    local_1b8[0] = &DAT_01423a38;
    local_1c8[0] = &DAT_01423a38;
    local_1d8[0] = &DAT_01423a38;
                    /* try { // try from 0058c21f to 0058c223 has its CatchHandler @ 0058d023 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_1e8);
                    /* try { // try from 0058c232 to 0058c236 has its CatchHandler @ 0058cf86 */
    std::string::assign((string *)local_1b8);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* try { // try from 0058c26c to 0058c270 has its CatchHandler @ 0058d023 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_1f8);
                    /* try { // try from 0058c27f to 0058c283 has its CatchHandler @ 0058cb9e */
    std::string::assign((string *)local_1c8);
    if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
                    /* try { // try from 0058c2ac to 0058c2b0 has its CatchHandler @ 0058d023 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_208);
                    /* try { // try from 0058c2bf to 0058c2c3 has its CatchHandler @ 0058cc14 */
    std::string::assign((string *)local_1d8);
    if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    remove(local_1b8[0]);
    rename(local_1c8[0],local_1b8[0]);
    rename(local_1d8[0],local_1c8[0]);
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1a8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_1a8 + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8 + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
    if ((allocator *)(local_e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar8 = local_e8[0] + -2;
      wVar5 = *pwVar8;
      *pwVar8 = *pwVar8 + L'\xffffffff';
      UNLOCK();
      if (wVar5 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -6));
      }
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar8 = local_a8[0] + -2;
      wVar5 = *pwVar8;
      *pwVar8 = *pwVar8 + L'\xffffffff';
      UNLOCK();
      if (wVar5 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar22 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar22 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if ((allocator *)(local_88 + -0x18) == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      return;
    }
    LOCK();
    piVar1 = (int *)(local_88 + -8);
    iVar22 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (0 < iVar22) {
      return;
    }
    std::wstring::_Rep::_M_destroy((allocator *)(local_88 + -0x18));
    return;
  }
  pcVar12 = strerror(iVar22);
                    /* try { // try from 0058c4bc to 0058c4c0 has its CatchHandler @ 0058cb95 */
  std::string::string(local_128,pcVar12,&local_3d);
                    /* try { // try from 0058c4cc to 0058c4d0 has its CatchHandler @ 0058cb8c */
  FILESYSTEM::GetAppDataPath(local_148);
                    /* try { // try from 0058c4e1 to 0058c4e5 has its CatchHandler @ 0058cb43 */
  std::operator+((wchar_t *)local_138,(wstring_conflict *)L"Unable to save character to :\n");
                    /* try { // try from 0058c4e9 to 0058c4ed has its CatchHandler @ 0058cb3a */
  std::wstring::~wstring((wstring_conflict *)local_148);
  local_2a8 = &DAT_01426458;
  local_290 = 0;
  local_2a0 = 0;
  local_298 = 0;
                    /* try { // try from 0058c51e to 0058c522 has its CatchHandler @ 0058cb27 */
  Ogre::UTFString::assign((UTFString *)&local_2a8,local_128);
  local_268 = &DAT_01426458;
  local_250 = 0;
  local_260 = 0;
  local_258 = 0;
                    /* try { // try from 0058c564 to 0058c568 has its CatchHandler @ 0058cb0a */
  std::string::string(local_218,"\n\nWindows Error: ",&local_43);
                    /* try { // try from 0058c579 to 0058c57d has its CatchHandler @ 0058cb5a */
  Ogre::UTFString::assign((UTFString *)&local_268,local_218);
                    /* try { // try from 0058c581 to 0058c585 has its CatchHandler @ 0058cb54 */
  std::string::~string(local_218);
  local_248 = &DAT_01426458;
  local_230 = 0;
  local_240 = 0;
  local_238 = 0;
                    /* try { // try from 0058c5c8 to 0058c6d6 has its CatchHandler @ 0058cb68 */
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_248,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_248,*(ulong *)(local_138[0] + -6));
  pwVar8 = local_138[0] + *(long *)(local_138[0] + -6);
  if (local_138[0] != pwVar8) {
    sVar25 = 0;
    pwVar14 = local_138[0];
    do {
      wVar5 = *pwVar14;
      lVar20 = 1;
      sVar24 = (short)wVar5;
      if (0xffff < (uint)wVar5) {
        lVar20 = 2;
        sVar25 = ((ushort)(wVar5 + L'\xffff0000') & 0x3ff) + 0xdc00;
        sVar24 = ((ushort)((uint)(wVar5 + L'\xffff0000') >> 10) & 0x3ff) + 0xd800;
      }
      lVar15 = *(long *)(local_248 + -0xc);
      uVar19 = lVar15 + 1;
      if ((*(ulong *)(local_248 + -8) < uVar19) || (0 < *(int *)(local_248 + -4))) {
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_248,uVar19);
        lVar15 = *(long *)(local_248 + -0xc);
      }
      local_248[lVar15] = sVar24;
      if (local_248 != &DAT_01426458) {
        *(undefined4 *)(local_248 + -4) = 0;
        *(ulong *)(local_248 + -0xc) = uVar19;
        local_248[uVar19] = 0;
      }
      if (lVar20 == 2) {
        lVar20 = *(long *)(local_248 + -0xc);
        uVar19 = lVar20 + 1;
        if ((*(ulong *)(local_248 + -8) < uVar19) || (0 < *(int *)(local_248 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_248,uVar19);
          lVar20 = *(long *)(local_248 + -0xc);
        }
        local_248[lVar20] = sVar25;
        if (local_248 != &DAT_01426458) {
          *(undefined4 *)(local_248 + -4) = 0;
          *(ulong *)(local_248 + -0xc) = uVar19;
          local_248[uVar19] = 0;
        }
      }
      pwVar14 = pwVar14 + 1;
    } while (pwVar8 != pwVar14);
  }
                    /* try { // try from 0058c722 to 0058c726 has its CatchHandler @ 0058ca14 */
  Ogre::operator+((Ogre *)local_288,(UTFString *)&local_248,(UTFString *)&local_268);
                    /* try { // try from 0058c736 to 0058c73a has its CatchHandler @ 0058caaf */
  Ogre::operator+((Ogre *)&local_2c8,local_288,(UTFString *)&local_2a8);
  if (local_2c0 == 2) goto LAB_0058c795;
  if (local_2b0 != (wstring_conflict *)0x0) {
    if (local_2c0 == 3) {
      if (local_2b0 != (wstring_conflict *)0x0) {
        puVar3 = (undefined2 *)(*(long *)local_2b0 + -0x18);
        if (puVar3 != &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(*(long *)local_2b0 + -8);
          iVar22 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar22 < 1) {
            operator_delete(puVar3);
          }
        }
        goto LAB_0058c9af;
      }
    }
    else if ((local_2c0 == 1) && (local_2b0 != (wstring_conflict *)0x0)) {
      paVar2 = (allocator *)(*(long *)local_2b0 + -0x18);
      if (paVar2 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)local_2b0 + -8);
        iVar22 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar22 < 1) {
          std::string::_Rep::_M_destroy(paVar2);
        }
      }
LAB_0058c9af:
      operator_delete(local_2b0);
    }
    local_2b0 = (wstring_conflict *)0x0;
    local_2b8 = 0;
  }
                    /* try { // try from 0058c779 to 0058c91f has its CatchHandler @ 0058d0b8 */
  local_2b0 = operator_new(8);
  *(undefined4 **)local_2b0 = &DAT_01424558;
  local_2c0 = 2;
LAB_0058c795:
  std::wstring::clear();
  pwVar21 = local_2b0;
  std::wstring::reserve((ulong)local_2b0);
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_2c8);
  psVar4 = local_2c8 + *(long *)(local_2c8 + -0xc);
  std::basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
  ::_M_leak((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_2c8);
  if (psVar4 != local_2c8) {
    plVar16 = (long *)(local_2c8 + -0xc);
    psVar17 = local_2c8;
    do {
      if ((-1 < (int)plVar16[2]) &&
         ((ulong *)plVar16 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if ((int)plVar16[2] != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_2c8,0,0,0);
          plVar16 = (long *)(local_2c8 + -0xc);
        }
        *(undefined4 *)(plVar16 + 2) = 0xffffffff;
      }
      lVar20 = (long)psVar17 - (long)local_2c8 >> 1;
      uVar23 = (ushort)local_2c8[lVar20] + 0x2800;
      if ((((ushort)uVar23 < 0x400) && (uVar19 = lVar20 + 1, uVar19 < *(ulong *)(local_2c8 + -0xc)))
         && ((ushort)(local_2c8[uVar19] + 0x2400U) < 0x400)) {
        uVar23 = ((ushort)(local_2c8[uVar19] + 0x2400U) & 0x3ff | (uVar23 & 0x3ff) << 10) + 0x10000;
      }
      else {
        uVar23 = (uint)(ushort)local_2c8[lVar20];
      }
      lVar20 = *(long *)pwVar21;
      lVar15 = *(long *)(lVar20 + -0x18);
      uVar19 = lVar15 + 1;
      if ((*(ulong *)(lVar20 + -0x10) < uVar19) || (0 < *(int *)(lVar20 + -8))) {
        std::wstring::reserve((ulong)pwVar21);
        lVar20 = *(long *)pwVar21;
        lVar15 = *(long *)(lVar20 + -0x18);
      }
      *(uint *)(lVar20 + lVar15 * 4) = uVar23;
      puVar6 = *(undefined4 **)pwVar21;
      if (puVar6 != &DAT_01424558) {
        puVar6[-2] = 0;
        *(ulong *)(puVar6 + -6) = uVar19;
        puVar6[uVar19] = 0;
      }
      plVar16 = (long *)(local_2c8 + -0xc);
      if ((-1 < *(int *)(local_2c8 + -4)) &&
         ((ulong *)plVar16 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage)) {
        if (*(int *)(local_2c8 + -4) != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_2c8,0,0,0);
          plVar16 = (long *)(local_2c8 + -0xc);
        }
        *(undefined4 *)(plVar16 + 2) = 0xffffffff;
        plVar16 = (long *)(local_2c8 + -0xc);
      }
      psVar13 = psVar17 + 1;
      if (((psVar13 != local_2c8 + *plVar16) && ((ushort)(psVar17[1] + 0x2400U) < 0x400)) &&
         ((ushort)(*psVar17 + 0x2800U) < 0x400)) {
        psVar13 = psVar17 + 2;
      }
      psVar17 = psVar13;
    } while (psVar4 != psVar13);
  }
                    /* try { // try from 0058b7bb to 0058b7bf has its CatchHandler @ 0058d0b8 */
  std::wstring::wstring(local_158,local_2b0);
                    /* try { // try from 0058b7cb to 0058b7cf has its CatchHandler @ 0058d09d */
  std::wstring::assign((wstring_conflict *)local_138);
                    /* try { // try from 0058b7d3 to 0058b7d7 has its CatchHandler @ 0058d0b8 */
  std::wstring::~wstring(local_158);
  Ogre::UTFString::~UTFString((UTFString *)&local_2c8);
  Ogre::UTFString::~UTFString(local_288);
  Ogre::UTFString::~UTFString((UTFString *)&local_248);
  Ogre::UTFString::~UTFString((UTFString *)&local_268);
  Ogre::UTFString::~UTFString((UTFString *)&local_2a8);
                    /* try { // try from 0058b828 to 0058b82c has its CatchHandler @ 0058d098 */
  std::wstring::wstring(local_168,local_138[0],&local_3e);
                    /* try { // try from 0058b83b to 0058b83f has its CatchHandler @ 0058d0e5 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_178);
                    /* try { // try from 0058b85b to 0058b85f has its CatchHandler @ 0058d0cc */
  std::string::string(local_188,local_178[0],&local_3f);
                    /* try { // try from 0058b860 to 0058b876 has its CatchHandler @ 0058d0eb */
  uVar9 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar9,local_188,3,0);
                    /* try { // try from 0058b87a to 0058b87e has its CatchHandler @ 0058d0cc */
  std::string::~string(local_188);
                    /* try { // try from 0058b882 to 0058b886 has its CatchHandler @ 0058d0e5 */
  std::string::~string((string *)local_178);
                    /* try { // try from 0058b88a to 0058b88e has its CatchHandler @ 0058d098 */
  std::wstring::~wstring(local_168);
                    /* try { // try from 0058b897 to 0058b89b has its CatchHandler @ 0058cb8c */
  std::wstring::~wstring((wstring_conflict *)local_138);
                    /* try { // try from 0058b8a4 to 0058b8a8 has its CatchHandler @ 0058cf42 */
  std::string::~string(local_128);
                    /* try { // try from 0058b8b1 to 0058b8b5 has its CatchHandler @ 0058d076 */
  std::wstring::~wstring((wstring_conflict *)local_e8);
                    /* try { // try from 0058b8be to 0058b8c2 has its CatchHandler @ 0058d007 */
  std::wstring::~wstring((wstring_conflict *)local_c8);
                    /* try { // try from 0058b8c6 to 0058b8ca has its CatchHandler @ 0058d034 */
  std::wstring::~wstring((wstring_conflict *)local_a8);
                    /* try { // try from 0058b8d3 to 0058b8d7 has its CatchHandler @ 0058ce64 */
  std::wstring::~wstring((wstring_conflict *)local_98);
  std::wstring::~wstring((wstring_conflict *)&local_88);
  return;
}



/* address=0058d110
   symbol=CGameClient::performWarp */

/* WARNING: Removing unreachable block (ram,0x0058e4fc) */
/* WARNING: Removing unreachable block (ram,0x0058e5ce) */
/* WARNING: Removing unreachable block (ram,0x0058e38a) */
/* WARNING: Removing unreachable block (ram,0x0058e405) */
/* WARNING: Removing unreachable block (ram,0x0058e205) */
/* WARNING: Removing unreachable block (ram,0x0058e1fa) */
/* WARNING: Removing unreachable block (ram,0x0058e54c) */
/* WARNING: Removing unreachable block (ram,0x0058e5d9) */
/* WARNING: Removing unreachable block (ram,0x0058e29e) */
/* WARNING: Removing unreachable block (ram,0x0058e375) */
/* WARNING: Removing unreachable block (ram,0x0058e1ec) */
/* WARNING: Removing unreachable block (ram,0x0058e259) */
/* WARNING: Removing unreachable block (ram,0x0058e5c0) */
/* WARNING: Removing unreachable block (ram,0x0058e339) */
/* WARNING: Removing unreachable block (ram,0x0058e213) */
/* WARNING: Removing unreachable block (ram,0x0058e45f) */
/* WARNING: Removing unreachable block (ram,0x0058e53e) */
/* WARNING: Removing unreachable block (ram,0x0058e410) */
/* WARNING: Removing unreachable block (ram,0x0058e507) */
/* CGameClient::performWarp() */

void CGameClient::performWarp(void)

{
  int *piVar1;
  wstring_conflict *pwVar2;
  wchar_t wVar3;
  wchar_t *pwVar4;
  size_t sVar5;
  size_t sVar6;
  bool bVar7;
  bool bVar8;
  char cVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  CLevel *pCVar13;
  time_t tVar14;
  CCharacter *pCVar15;
  Vector3 *pVVar16;
  CSteamStats *pCVar17;
  undefined8 uVar18;
  CDungeonManager *pCVar19;
  long lVar20;
  long lVar21;
  byte bVar22;
  uint uVar23;
  long lVar24;
  ulong uVar25;
  CEditorBaseObject *pCVar26;
  CGameClient *in_RDI;
  CPositionableObject *this;
  int iVar27;
  bool bVar28;
  undefined4 in_XMM1_Da;
  undefined4 in_XMM1_Db;
  int local_224;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  undefined4 local_1f0;
  undefined8 local_1e8;
  undefined4 local_1e0;
  undefined8 local_1d8;
  undefined4 local_1d0;
  undefined8 local_1c8;
  undefined4 local_1c0;
  undefined8 local_1b8;
  undefined4 local_1b0;
  undefined8 local_1a8;
  undefined4 local_1a0;
  undefined8 local_198;
  undefined4 local_190;
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wstring_conflict local_a8 [16];
  long local_98 [2];
  wchar_t *local_88 [2];
  wchar_t *local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar10 = *(int *)(in_RDI + 0x10a0);
  pwVar2 = (wstring_conflict *)(in_RDI + 0x10a8);
  in_RDI[0x10b9] = (CGameClient)0x0;
  STRINGS::StringUpper((STRINGS *)local_58,pwVar2);
                    /* try { // try from 0058d15c to 0058d160 has its CatchHandler @ 0058e370 */
  std::wstring::assign(pwVar2);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar11 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (*(long *)(in_RDI + 0x38d8) != 0) {
    pwVar4 = *(wchar_t **)(*(long *)(in_RDI + 0x38d8) + 0x60);
    sVar5 = *(size_t *)(*(wchar_t **)(in_RDI + 0x10a8) + -6);
    if ((sVar5 == *(size_t *)(pwVar4 + -6)) &&
       (iVar11 = wmemcmp(*(wchar_t **)(in_RDI + 0x10a8),pwVar4,sVar5), iVar11 == 0)) {
      std::wstring::assign(pwVar2);
    }
  }
  iVar11 = *(int *)(*(long *)(in_RDI + 0x70) + 0x1a4);
  bVar28 = *(int *)(in_RDI + 0x10a0) == -99;
  if (bVar28) {
    wcslen(L"Town");
    std::wstring::assign((wchar_t *)pwVar2,0xfa8394);
  }
  if (((iVar11 < 1) && (*(int *)(in_RDI + 0x10a0) < 0)) && (*(int *)(in_RDI + 0x10a0) != -99)) {
    if (*(long *)(in_RDI + 0x38d8) == 0) {
LAB_0058e05d:
      if (*(long *)(in_RDI + 0x38d8) != 0) {
        lVar20 = *(long *)(in_RDI + 0x58);
        pwVar4 = *(wchar_t **)(lVar20 + 2000);
        sVar5 = *(size_t *)(pwVar4 + -6);
        if ((sVar5 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
           (iVar27 = wmemcmp(pwVar4,::EMPTY_WSTRING,sVar5), iVar27 != 0)) {
          STRINGS::StringUpper((STRINGS *)local_68,(wstring_conflict *)(lVar20 + 2000));
                    /* try { // try from 0058e0a8 to 0058e0ac has its CatchHandler @ 0058e107 */
          std::wstring::assign(pwVar2);
          if ((allocator *)(local_68[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_68[0] + -8);
            iVar27 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar27 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
            }
          }
          *(undefined4 *)(in_RDI + 0x10a0) = 0;
          *(undefined4 *)(in_RDI + 0x10a4) = *(undefined4 *)(*(long *)(in_RDI + 0x58) + 0x7cc);
          goto LAB_0058da6b;
        }
      }
      goto LAB_0058d1c7;
    }
    pwVar4 = *(wchar_t **)(*(long *)(in_RDI + 0x38d8) + 0x80);
    sVar5 = *(size_t *)(pwVar4 + -6);
    if ((sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
       (iVar27 = wmemcmp(pwVar4,::EMPTY_WSTRING,sVar5), iVar27 == 0)) goto LAB_0058e05d;
    std::wstring::assign(pwVar2);
    *(undefined4 *)(in_RDI + 0x10a0) = 0;
    *(undefined4 *)(in_RDI + 0x10a4) = 0;
LAB_0058da6b:
    saveCharacter(in_RDI,false,true);
    CGameUI::setCursorState(*(CGameUI **)(in_RDI + 0x78),1);
    CGameUI::setLoadingVisible(*(CGameUI **)(in_RDI + 0x78),true);
    if (!bVar28) {
      local_224 = *(int *)(in_RDI + 0x10a4);
      goto joined_r0x0058d2a9;
    }
LAB_0058d1fd:
    in_XMM1_Da = 0;
    in_XMM1_Db = 0;
    CSoundBank::playSample
              (*(CSoundBank **)(in_RDI + 0x1088),0x1c,(SceneNode *)0x0,DAT_00fa47fc,0.0,false);
    if ((*(long *)(*(long *)(in_RDI + 0x70) + 0x1d8) == 0) ||
       (*(char *)(*(long *)(*(long *)(in_RDI + 0x70) + 0x1d8) + 0x86) == '\0')) {
      wcslen(L"TOWN");
      std::wstring::assign((wchar_t *)pwVar2,0xfa83a8);
      pCVar15 = *(CCharacter **)(in_RDI + 0x58);
      bVar8 = false;
      local_224 = 0;
    }
    else {
      std::wstring::assign(pwVar2);
      pCVar15 = *(CCharacter **)(in_RDI + 0x58);
      local_224 = *(int *)(pCVar15 + 0x7b4);
      bVar8 = true;
    }
  }
  else {
LAB_0058d1c7:
    if (bVar28) {
      saveCharacter(in_RDI,false,true);
      CGameUI::setCursorState(*(CGameUI **)(in_RDI + 0x78),1);
      CGameUI::setLoadingVisible(*(CGameUI **)(in_RDI + 0x78),true);
      goto LAB_0058d1fd;
    }
    if ((iVar11 < 1) && (*(int *)(in_RDI + 0x10a0) < 0)) {
      return;
    }
    saveCharacter(in_RDI,false,true);
    CGameUI::setCursorState(*(CGameUI **)(in_RDI + 0x78),1);
    CGameUI::setLoadingVisible(*(CGameUI **)(in_RDI + 0x78),true);
    local_224 = *(int *)(in_RDI + 0x10a4);
joined_r0x0058d2a9:
    if (local_224 == 0) {
      sVar5 = *(size_t *)(*(wchar_t **)(in_RDI + 0x10a8) + -6);
      if ((sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
         (iVar27 = wmemcmp(*(wchar_t **)(in_RDI + 0x10a8),::EMPTY_WSTRING,sVar5), iVar27 == 0)) {
        local_224 = *(int *)(in_RDI + 0x10a0) + iVar11;
      }
    }
    pCVar15 = *(CCharacter **)(in_RDI + 0x58);
    bVar8 = false;
  }
  CLevel::removeCharacter(*(CLevel **)(in_RDI + 0x70),pCVar15,true);
  killPets(in_RDI);
  pCVar13 = *(CLevel **)(in_RDI + 0x58);
  lVar20 = *(long *)(pCVar13 + 0x648);
  lVar21 = *(long *)(pCVar13 + 0x650) - lVar20 >> 3;
  if (0 < (int)lVar21) {
    lVar24 = 0;
    iVar27 = 0;
    do {
      pCVar26 = (CEditorBaseObject *)0x0;
      if (lVar21 != 0) {
        pCVar26 = *(CEditorBaseObject **)(lVar20 + lVar24);
      }
      if (*(CEditorScene **)(pCVar26 + 0x48) != (CEditorScene *)0x0) {
        CEditorScene::RemoveObjectInScene(*(CEditorScene **)(pCVar26 + 0x48),pCVar26);
        pCVar13 = *(CLevel **)(in_RDI + 0x58);
      }
      pCVar15 = (CCharacter *)0x0;
      if (*(long *)(pCVar13 + 0x650) - *(long *)(pCVar13 + 0x648) >> 3 != 0) {
        pCVar15 = *(CCharacter **)(*(long *)(pCVar13 + 0x648) + lVar24);
      }
      iVar27 = iVar27 + 1;
      lVar24 = lVar24 + 8;
      CLevel::removeCharacter(*(CLevel **)(in_RDI + 0x70),pCVar15,true);
      pCVar13 = *(CLevel **)(in_RDI + 0x58);
      lVar20 = *(long *)(pCVar13 + 0x648);
      lVar21 = *(long *)(pCVar13 + 0x650) - lVar20 >> 3;
    } while (iVar27 < (int)lVar21);
  }
  uVar23 = 2;
  CPlayer::storeLevelSavedState(pCVar13);
  uVar18 = *(undefined8 *)(in_RDI + 0x58);
  cVar9 = *(char *)(*(long *)(*(long *)(in_RDI + 0x70) + 0x1d8) + 0x5a);
  unloadCurrentLevel(in_RDI,false);
  *(undefined8 *)(in_RDI + 0x58) = uVar18;
  if ((!bVar28) && (uVar23 = 1, *(long *)(in_RDI + 0x10a0) != 0)) {
    uVar23 = (uint)(0 < *(int *)(in_RDI + 0x10a0));
  }
  std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
  if (*(long *)(in_RDI + 0x38d8) != 0) {
    pwVar4 = *(wchar_t **)(*(long *)(in_RDI + 0x38d8) + 0x60);
    sVar5 = *(size_t *)(pwVar4 + -6);
    if ((sVar5 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar27 = wmemcmp(pwVar4,::EMPTY_WSTRING,sVar5), iVar27 != 0)) {
                    /* try { // try from 0058d3fd to 0058d428 has its CatchHandler @ 0058e382 */
      std::wstring::assign((wstring_conflict *)local_78);
    }
    if (*(long *)(*(long *)(in_RDI + 0x10a8) + -0x18) == 0) {
                    /* try { // try from 0058db14 to 0058db18 has its CatchHandler @ 0058e382 */
      std::wstring::assign(pwVar2);
    }
  }
  std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)local_78);
  pwVar4 = *(wchar_t **)(in_RDI + 0x10a8);
  sVar5 = *(size_t *)(pwVar4 + -6);
  if (sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar27 = wmemcmp(pwVar4,::EMPTY_WSTRING,sVar5);
    if (iVar27 != 0) {
      sVar6 = *(size_t *)(local_78[0] + -6);
      goto joined_r0x0058d9e5;
    }
  }
  else {
    sVar6 = *(size_t *)(local_78[0] + -6);
joined_r0x0058d9e5:
    if (((sVar5 == sVar6) && (iVar27 = wmemcmp(pwVar4,local_78[0],sVar5), iVar27 == 0)) || (bVar28))
    {
LAB_0058d462:
      bVar7 = false;
    }
    else {
      if (cVar9 == '\0') {
                    /* try { // try from 0058dc60 to 0058dc8c has its CatchHandler @ 0058e2de */
        std::wstring::assign((wstring_conflict *)(*(long *)(in_RDI + 0x58) + 2000));
        *(int *)(*(long *)(in_RDI + 0x58) + 0x7cc) = iVar11;
      }
      std::wstring::wstring((wstring_conflict *)local_98,pwVar2);
                    /* try { // try from 0058db9c to 0058dba0 has its CatchHandler @ 0058e299 */
      cVar9 = CPlayer::hasDungeonHistory(*(CPlayer **)(in_RDI + 0x58),(wstring_conflict *)local_98);
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_98[0] + -8);
        iVar27 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar27 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
      if (cVar9 != '\0') goto LAB_0058d462;
                    /* try { // try from 0058dbce to 0058dbd2 has its CatchHandler @ 0058e2de */
      std::wstring::wstring(local_a8,pwVar2);
                    /* try { // try from 0058dbd3 to 0058dbe2 has its CatchHandler @ 0058e398 */
      pCVar19 = (CDungeonManager *)CDungeonManager::getSingleton();
      lVar20 = CDungeonManager::getDungeonByName(pCVar19,local_a8);
                    /* try { // try from 0058dbe9 to 0058dbed has its CatchHandler @ 0058e2de */
      std::wstring::~wstring(local_a8);
      if ((lVar20 != 0) && (*(char *)(lVar20 + 0x88) == '\0')) goto LAB_0058d462;
      bVar7 = true;
    }
                    /* try { // try from 0058d475 to 0058d479 has its CatchHandler @ 0058e2de */
    std::wstring::wstring((wstring_conflict *)local_b8,pwVar2);
                    /* try { // try from 0058d480 to 0058d484 has its CatchHandler @ 0058e21e */
    setCurrentDungeon();
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    tVar14 = time((time_t *)0x0);
    srand((uint)tVar14);
    if (bVar7) {
                    /* try { // try from 0058db61 to 0058db94 has its CatchHandler @ 0058e2de */
      uVar12 = UTILITIES::randomIntegerBetweenVolatile(0,0x7fffffff);
      *(undefined4 *)(*(long *)(in_RDI + 0x38d8) + 0x58) = uVar12;
    }
                    /* try { // try from 0058d4c1 to 0058d4c5 has its CatchHandler @ 0058e2de */
    std::wstring::wstring((wstring_conflict *)local_c8,pwVar2);
                    /* try { // try from 0058d4d1 to 0058d4d5 has its CatchHandler @ 0058e49f */
    CPlayer::updateDungeonTracking
              (*(CPlayer **)(in_RDI + 0x58),(wstring_conflict *)local_c8,local_224);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  if (in_RDI[0x10b8] == (CGameClient)0x0) {
    if (((*(size_t *)(local_78[0] + -6) != *(size_t *)(*(wchar_t **)(in_RDI + 0x10a8) + -6)) ||
        (iVar27 = wmemcmp(local_78[0],*(wchar_t **)(in_RDI + 0x10a8),*(size_t *)(local_78[0] + -6)),
        iVar27 != 0)) && (!bVar28)) {
      uVar23 = 6 - (in_RDI[0x10ba] == (CGameClient)0x0);
    }
  }
  if (*(long *)(in_RDI + 0x38d8) == 0) {
    std::wstring::wstring((wstring_conflict *)local_128,(wstring_conflict *)local_78);
                    /* try { // try from 0058dca2 to 0058dca6 has its CatchHandler @ 0058e254 */
    std::wstring::wstring((wstring_conflict *)local_118,L"media/layouts/crypt/rules.dat",&local_3c);
                    /* try { // try from 0058dcbf to 0058dcc3 has its CatchHandler @ 0058e24f */
    std::wstring::wstring((wstring_conflict *)local_108,L"",&local_3b);
                    /* try { // try from 0058dce0 to 0058dce4 has its CatchHandler @ 0058e1cf */
    loadLevel();
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
  }
  else {
                    /* try { // try from 0058d519 to 0058d51d has its CatchHandler @ 0058e2de */
    std::wstring::wstring((wstring_conflict *)local_f8,(wstring_conflict *)local_78);
                    /* try { // try from 0058d533 to 0058d537 has its CatchHandler @ 0058e2e6 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"",&local_3a);
                    /* try { // try from 0058d550 to 0058d554 has its CatchHandler @ 0058e317 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"",local_39);
                    /* try { // try from 0058d571 to 0058d575 has its CatchHandler @ 0058e32c */
    loadLevel();
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar27 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar27 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
  }
  if (uVar23 == 5) {
    if ((*(size_t *)(local_88[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar10 = wmemcmp(local_88[0],::EMPTY_WSTRING,*(size_t *)(local_88[0] + -6)), iVar10 != 0)) {
      std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)local_88);
                    /* try { // try from 0058de4d to 0058de51 has its CatchHandler @ 0058e11a */
      local_198 = CLevel::findTemporaryDungeonPortal
                            (*(CLevel **)(in_RDI + 0x70),(wstring_conflict *)local_138);
      local_190 = in_XMM1_Da;
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_138[0] + -8);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      if (local_198._4_4_ != DAT_00fa8764) {
                    /* try { // try from 0058deba to 0058df27 has its CatchHandler @ 0058e2de */
        local_1a8 = CLevel::randomOpenPosition
                              (*(CLevel **)(in_RDI + 0x70),(Vector3 *)&local_198,DAT_00fa47fc,false)
        ;
        local_1a0 = in_XMM1_Da;
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(in_RDI + 0x58),(Vector3 *)&local_1a8);
        CCharacter::dropToGround
                  (*(CLevel **)(in_RDI + 0x58),DAT_00fa8768,SUB81(*(undefined8 *)(in_RDI + 0x70),0))
        ;
      }
      std::wstring::wstring((wstring_conflict *)local_148,(wstring_conflict *)local_88);
                    /* try { // try from 0058df2f to 0058df33 has its CatchHandler @ 0058e2a9 */
      CLevel::deleteTemporaryDungeonPortals
                (*(CLevel **)(in_RDI + 0x70),(wstring_conflict *)local_148);
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_148[0] + -8);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
    }
LAB_0058d5dc:
                    /* try { // try from 0058d5e0 to 0058d6e8 has its CatchHandler @ 0058e2de */
    CLevel::deleteOpenPortals(*(CLevel **)(in_RDI + 0x70));
LAB_0058d5e5:
    CPlayer::createPortals(*(CPlayer **)(in_RDI + 0x58),*(CLevel **)(in_RDI + 0x70));
  }
  else {
    if (uVar23 != 2) {
      if ((uVar23 < 2) && (in_RDI[0x10b8] == (CGameClient)0x0)) {
                    /* try { // try from 0058df92 to 0058df96 has its CatchHandler @ 0058e2de */
        std::wstring::wstring((wstring_conflict *)local_168,(wstring_conflict *)(in_RDI + 0x10b0));
                    /* try { // try from 0058dfb6 to 0058dfba has its CatchHandler @ 0058e46a */
        std::wstring::wstring((wstring_conflict *)local_158,(wstring_conflict *)local_88);
                    /* try { // try from 0058dfcb to 0058dfcf has its CatchHandler @ 0058e447 */
        cVar9 = CLevel::placePlayerAtWarpToDungeonFloor
                          (*(undefined8 *)(in_RDI + 0x70),(wstring_conflict *)local_158,iVar11,
                           iVar10 == 0,(wstring_conflict *)local_168);
        if ((allocator *)(local_158[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_158[0] + -8);
          iVar10 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
          }
        }
        if ((allocator *)(local_168[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_168[0] + -8);
          iVar10 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
          }
        }
        if (cVar9 != '\0') {
                    /* try { // try from 0058e016 to 0058e01a has its CatchHandler @ 0058e2de */
          CCharacter::dropToGround
                    (*(CLevel **)(in_RDI + 0x58),DAT_00fa8768,
                     SUB81(*(undefined8 *)(in_RDI + 0x70),0));
        }
      }
      goto LAB_0058d5dc;
    }
                    /* try { // try from 0058dd82 to 0058de45 has its CatchHandler @ 0058e2de */
    CLevel::deleteOpenPortals(*(CLevel **)(in_RDI + 0x70));
    if (!bVar8) goto LAB_0058d5e5;
    local_1b8 = CLevel::randomOpenPosition
                          (*(CLevel **)(in_RDI + 0x70),(Vector3 *)(*(long *)(in_RDI + 0x58) + 0x7c0)
                           ,DAT_00fa47fc,false);
    local_1b0 = in_XMM1_Da;
    CPositionableObject::setPosition(*(CPositionableObject **)(in_RDI + 0x58),(Vector3 *)&local_1b8)
    ;
    CCharacter::dropToGround
              (*(CLevel **)(in_RDI + 0x58),DAT_00fa8768,SUB81(*(undefined8 *)(in_RDI + 0x70),0));
    *(undefined1 *)(*(long *)(in_RDI + 0x58) + 0x7b0) = 0;
  }
  this = *(CPositionableObject **)(in_RDI + 0x58);
  if ((int)((ulong)(*(long *)(this + 0x650) - *(long *)(this + 0x648)) >> 3) != 0) {
    uVar25 = 0;
    do {
      local_1c8 = CPositionableObject::getPosition(this,true);
      local_1c0 = in_XMM1_Da;
      local_1d8 = CLevel::randomOpenPosition
                            (*(CLevel **)(in_RDI + 0x70),(Vector3 *)&local_1c8,DAT_00fa86d0,false);
      pCVar15 = (CCharacter *)0x0;
      lVar20 = *(long *)(*(long *)(in_RDI + 0x58) + 0x648);
      if (*(long *)(*(long *)(in_RDI + 0x58) + 0x650) - lVar20 >> 3 != 0) {
        pCVar15 = *(CCharacter **)(lVar20 + uVar25 * 8);
      }
      local_1d0 = in_XMM1_Da;
      pCVar15 = (CCharacter *)
                CLevel::addCharacter
                          (*(CLevel **)(in_RDI + 0x70),pCVar15,(Vector3 *)&local_1d8,false);
      pVVar16 = (Vector3 *)(**(code **)(**(long **)(in_RDI + 0x58) + 0x130))();
      CCharacter::setToward(pCVar15,pVVar16);
      this = *(CPositionableObject **)(in_RDI + 0x58);
      uVar23 = (int)uVar25 + 1;
      uVar25 = (ulong)uVar23;
    } while (uVar23 < (uint)(*(long *)(this + 0x650) - *(long *)(this + 0x648) >> 3));
  }
                    /* try { // try from 0058d71d to 0058d733 has its CatchHandler @ 0058e557 */
  std::wstring::wstring((wstring_conflict *)local_178,pwVar2);
  iVar10 = CPlayer::getMaxDepth(*(CPlayer **)(in_RDI + 0x58));
  if (iVar10 <= local_224) {
    lVar20 = *(long *)(in_RDI + 0x70);
    pwVar4 = *(wchar_t **)(*(long *)(lVar20 + 0x1d8) + 0x698);
    sVar5 = *(size_t *)(pwVar4 + -6);
    if ((sVar5 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar10 = wmemcmp(pwVar4,::EMPTY_WSTRING,sVar5), iVar10 != 0)) {
      bVar22 = *(byte *)(lVar20 + 0x1a1) ^ 1;
      goto LAB_0058d740;
    }
  }
  bVar22 = 0;
LAB_0058d740:
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_178[0] + -8);
    iVar10 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
  if (bVar22 != 0) {
                    /* try { // try from 0058d776 to 0058d77a has its CatchHandler @ 0058e2de */
    std::wstring::wstring
              ((wstring_conflict *)local_188,
               (wstring_conflict *)(*(long *)(*(long *)(in_RDI + 0x70) + 0x1d8) + 0x698));
                    /* try { // try from 0058d782 to 0058d786 has its CatchHandler @ 0058e3d4 */
    CGameUI::setCinematicOpen(*(CGameUI **)(in_RDI + 0x78));
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
  }
  *(undefined4 *)(in_RDI + 0x1038) = 3;
                    /* try { // try from 0058d7b0 to 0058d906 has its CatchHandler @ 0058e2de */
  saveCharacter(in_RDI,false,true);
  CGameUI::setCursorState(*(CGameUI **)(in_RDI + 0x78));
  CGameUI::setLoadingVisible(*(CGameUI **)(in_RDI + 0x78),false);
  if ((bVar28) || (in_RDI[0x10ba] != (CGameClient)0x0)) {
    in_XMM1_Da = 0;
    in_XMM1_Db = 0;
    CSoundBank::playSample
              (*(CSoundBank **)(in_RDI + 0x1088),0x1c,(SceneNode *)0x0,DAT_00fa47fc,0.0,false);
  }
  if (*(long *)(*(CPositionableObject **)(in_RDI + 0x58) + 0x1c8) != 0) {
    local_1f8 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x58),true);
    local_1f0 = in_XMM1_Da;
    local_208 = (**(code **)(**(long **)(in_RDI + 0x58) + 0xf0))();
    local_200 = CONCAT44(in_XMM1_Db,in_XMM1_Da);
    local_1e8 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x58),true);
    local_1e0 = in_XMM1_Da;
    CSkillManager::startPassiveSkills
              (*(CSkillManager **)(*(CBaseUnit **)(in_RDI + 0x58) + 0x1c8),
               *(CBaseUnit **)(in_RDI + 0x58),(Vector3 *)&local_1e8,(Quaternion *)&local_208,
               (Vector3 *)&local_1f8);
  }
  CMouseManager::flushAll((CMouseManager *)(in_RDI + 0xfe8));
  CKeyManager::flushAll((CKeyManager *)(in_RDI + 0x2d0));
  in_RDI[0x99] = (CGameClient)0x0;
  in_RDI[0x9a] = (CGameClient)0x0;
  in_RDI[0x98] = (CGameClient)0x1;
  if (*(long *)(in_RDI + 0x70) != 0) {
    pCVar17 = (CSteamStats *)CSteamStats::getSingleton();
    iVar11 = CSteamStats::getStatInt(pCVar17,5);
    iVar10 = *(int *)(*(long *)(in_RDI + 0x70) + 0x1a4);
    if (iVar11 < iVar10) {
                    /* try { // try from 0058daee to 0058db01 has its CatchHandler @ 0058e2de */
      uVar18 = CSteamStats::getSingleton();
      CSteamStats::setStatInt(uVar18,5,iVar10);
    }
  }
  if ((allocator *)(local_88[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar4 = local_88[0] + -2;
    wVar3 = *pwVar4;
    *pwVar4 = *pwVar4 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
    }
  }
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar4 = local_78[0] + -2;
    wVar3 = *pwVar4;
    *pwVar4 = *pwVar4 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
    }
  }
  return;
}



/* address=0058e5f0
   symbol=CGameClient::updateIngame */

/* WARNING: Removing unreachable block (ram,0x0058e76e) */
/* CGameClient::updateIngame(float, Ogre::RenderWindow*, float, bool) */

void __thiscall
CGameClient::updateIngame
          (CGameClient *this,float param_1,RenderWindow *param_2,float param_3,bool param_4)

{
  code *pcVar1;
  undefined8 *puVar2;
  CRunicCore *this_00;
  bool bVar3;
  char cVar4;
  char cVar5;
  bool bVar6;
  undefined4 uVar7;
  long lVar8;
  float *pfVar9;
  long lVar10;
  Vector3 *pVVar11;
  CPositionableObject *pCVar12;
  CGameUI *pCVar13;
  long *plVar14;
  CBaseUnit *pCVar15;
  Camera *pCVar16;
  CLevel *pCVar17;
  CCharacter *this_01;
  CItem *pCVar18;
  uint uVar19;
  int iVar20;
  ulong uVar21;
  CRunicCore *this_02;
  float fVar22;
  float fVar23;
  float fVar24;
  undefined8 uVar25;
  undefined4 extraout_XMM1_Da;
  float extraout_XMM1_Da_00;
  float extraout_XMM1_Da_01;
  undefined4 extraout_XMM1_Da_02;
  undefined4 extraout_XMM1_Da_03;
  undefined4 extraout_XMM1_Da_04;
  float extraout_XMM1_Da_05;
  float fVar26;
  float extraout_XMM1_Da_06;
  float local_10c;
  undefined8 local_c8;
  undefined4 local_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  undefined4 local_60;
  undefined8 local_58;
  undefined4 local_50;
  wstring_conflict local_48 [15];
  allocator local_39 [9];

  if (this[0x10b9] != (CGameClient)0x0) {
    performWarp();
  }
  cVar4 = getIsPaused(this);
  if ((cVar4 == '\0') &&
     (updateIngame(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate =
           param_1 + updateIngame(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate,
     DAT_00fa86dc < updateIngame(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate)) {
    updateIngame(float,Ogre::RenderWindow*,float,bool)::gTorchlightUpdate = 0.0;
    fVar22 = *(float *)(this + 0x2a8);
    fVar23 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa4824,DAT_00fa86d0);
    fVar26 = DAT_00fa86e0;
    *(float *)(this + 0x2a8) = fVar23 * param_1 + fVar22;
    fVar22 = (float)UTILITIES::randomBetweenVolatile(0.0,fVar26);
    if (DAT_00fa86e4 < fVar22) {
      fVar26 = *(float *)(this + 0x2a8);
      fVar22 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa86ec,DAT_00fa86e8);
      fVar22 = fVar22 + fVar26;
      *(float *)(this + 0x2a8) = fVar22;
    }
    else {
      fVar22 = *(float *)(this + 0x2a8);
    }
    if (DAT_00fa86f0 <= fVar22) {
      do {
        fVar22 = fVar22 - DAT_00fa86f0;
      } while (DAT_00fa86f0 <= fVar22);
      *(float *)(this + 0x2a8) = fVar22;
    }
  }
  cVar5 = CResourceManager::getEditorIsRunning();
  if (cVar5 == '\0') {
    if (((*(long *)(this + 0x58) == 0) ||
        (pCVar15 = *(CBaseUnit **)(*(long *)(this + 0x58) + 0x340), pCVar15 == (CBaseUnit *)0x0)) ||
       (cVar5 = CBaseUnit::ISA(pCVar15,0x83), cVar5 == '\0')) {
      lVar8 = CMasterResourceManager::getSingleton();
      *(char *)(*(long *)(lVar8 + 0xf0) + 0x540) = cVar4;
    }
    else {
      lVar8 = CMasterResourceManager::getSingleton();
      *(undefined1 *)(*(long *)(lVar8 + 0xf0) + 0x540) = 0;
    }
  }
  Ogre::Rectangle2D::setCorners(DAT_00fa86f4,DAT_00fa4810,DAT_00fa4810,DAT_00fa86f4);
                    /* try { // try from 0058e75c to 0058e760 has its CatchHandler @ 0058fa4b */
  Ogre::SimpleRenderable::setBoundingBox(*(AxisAlignedBox **)(this + 0x230));
  *(float *)(this + 0x38c4) = param_3;
  CGameSpeed::getSingleton();
  CGameSpeed::calculateGameSpeed(param_1);
  CGameSpeed::getSingleton();
  fVar22 = (float)CGameSpeed::getGameSpeed();
  if (*(long *)(this + 0x2b8) != 0) {
    fVar26 = *(float *)(this + 0x38c0);
    lVar8 = CMasterResourceManager::getSingleton();
    *(float *)(*(long *)(lVar8 + 0xf0) + 0x4dc) = fVar22 * fVar26;
  }
  CMouseManager::capture((CMouseManager *)(this + 0xfe8));
  CKeyManager::capture((CKeyManager *)(this + 0x2d0));
  pCVar12 = *(CPositionableObject **)(this + 0x58);
  local_10c = param_3;
  if ((pCVar12 == (CPositionableObject *)0x0) ||
     (pCVar16 = *(Camera **)(this + 0x70), pCVar16 == (Camera *)0x0)) {
    if (*(long *)(this + 0x20) != 0) {
      findCameraTargetLocation(this,(Vector3 *)&local_a8,0.0);
      uVar19 = KSETTINGS_SHADOWS_ENABLED;
      local_a8 = CONCAT44(DAT_00fa876c + local_a8._4_4_,(float)local_a8 + 0.0);
      local_a0 = local_a0 + 0.0;
      lVar8 = CMasterResourceManager::getSingleton();
      iVar20 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar19);
      if (iVar20 != 0) {
        Ogre::Camera::setPosition(*(Vector3 **)(*(long *)(this + 0x20) + 0x30));
      }
      findCameraTargetLocation(this,(Vector3 *)&local_a8,0.0);
      uVar19 = KSETTINGS_LIGHTING_ENABLED;
      local_a0 = local_a0 + 0.0;
      local_a8 = CONCAT44(DAT_00fa483c + local_a8._4_4_,(float)local_a8 + 0.0);
      lVar8 = CMasterResourceManager::getSingleton();
      iVar20 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar8 + 0x90),uVar19);
      if (iVar20 != 0) {
        Ogre::Camera::setPosition(*(Vector3 **)(*(long *)(this + 0x20) + 0x28));
      }
    }
  }
  else {
    fVar26 = *(float *)(this + 0x38c0);
    fVar23 = fVar22 * DAT_00fa86d8 * fVar26;
    if (param_1 <= fVar23) {
      fVar23 = param_1;
    }
    fVar24 = ceilf(fVar23 / DAT_00fa86dc);
    uVar19 = (uint)(long)fVar24;
    if (uVar19 < 6) {
      uVar21 = (long)fVar24 & 0xffffffff;
      if (uVar19 == 0) {
        uVar21 = 1;
      }
    }
    else {
      uVar21 = 5;
    }
    fVar23 = fVar23 / (float)uVar21;
    if (((param_3 == DAT_00fa47f8) && (!NAN(param_3) && !NAN(DAT_00fa47f8))) && (param_4)) {
      local_10c = (float)uVar21 * fVar23;
    }
    if (cVar4 == '\0') {
      iVar20 = (int)uVar21 + -1;
      if (-1 < iVar20) {
        while( true ) {
          CLevel::update(pCVar16,*(Vector3 **)(*(long *)(this + 0x20) + 0x10),fVar23 * fVar26,fVar22
                         ,(CPlayer *)(*(long *)(this + 0x20) + 0x4c));
          iVar20 = iVar20 + -1;
          if (iVar20 < 0) break;
          pCVar16 = *(Camera **)(this + 0x70);
          fVar26 = *(float *)(this + 0x38c0);
        }
      }
      autoPickupGold();
      if (!param_4) goto LAB_0058e910;
      fVar26 = local_10c * fVar22 * *(float *)(this + 0x38c0);
      CLevel::updateLayouts(*(CLevel **)(this + 0x70),fVar26);
      if (*(long **)(this + 0x1080) != (long *)0x0) {
        (**(code **)(**(long **)(this + 0x1080) + 0x208))(fVar26);
      }
      CLevel::updateCharacterAnimation
                (*(CLevel **)(this + 0x70),local_10c * *(float *)(this + 0x38c0),fVar22,
                 *(CPlayer **)(this + 0x58));
      CLevel::findItemsOnscreen
                (*(CLevel **)(this + 0x70),*(Camera **)(*(long *)(this + 0x20) + 0x10));
      bVar6 = (bool)getIsPaused(this);
      CLevel::updateVisibleParticles
                (*(CLevel **)(this + 0x70),*(Camera **)(*(long *)(this + 0x20) + 0x10),
                 (Vector3 *)(*(long *)(this + 0x20) + 0x4c),bVar6);
      CCharacter::updateCameraOpacity
                (*(CCharacter **)(this + 0x58),*(Camera **)(*(long *)(this + 0x20) + 0x10),0.0);
      pCVar12 = *(CPositionableObject **)(this + 0x58);
    }
    else {
      if (!param_4) goto LAB_0058e914;
      if ((*(long *)(pCVar12 + 0x340) == 0) || (cVar5 = CBaseUnit::ISA(), cVar5 == '\0')) {
        bVar6 = false;
        bVar3 = false;
      }
      else {
        bVar6 = false;
        bVar3 = true;
        plVar14 = *(long **)(*(long *)(this + 0x58) + 0x340);
        if (plVar14 != (long *)0x0) {
          bVar6 = true;
          (**(code **)(*plVar14 + 0x200))
                    (local_10c,plVar14,*(undefined8 *)(*(long *)(this + 0x20) + 0x10),this + 0x2c0);
          (**(code **)(**(long **)(*(long *)(this + 0x58) + 0x340) + 0x300))(local_10c);
        }
      }
      lVar8 = CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
      if ((lVar8 == 0) ||
         ((lVar8 = *(long *)(*(long *)(this + 0x58) + 0x340),
          lVar10 = CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78)), lVar8 == lVar10 &&
          (bVar6)))) {
        if (bVar3) goto LAB_0058ef21;
        this_01 = *(CCharacter **)(this + 0x58);
        if (*(CGenericModel **)(this_01 + 0x208) != (CGenericModel *)0x0) {
          CGenericModel::updateAnimation(*(CGenericModel **)(this_01 + 0x208),local_10c,false);
          this_01 = *(CCharacter **)(this + 0x58);
        }
      }
      else {
        lVar8 = CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
        if (*(int *)(lVar8 + 0x188) == 0) {
          plVar14 = (long *)CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
          (**(code **)(*plVar14 + 0x200))
                    (local_10c,plVar14,*(undefined8 *)(*(long *)(this + 0x20) + 0x10),this + 0x2c0);
          plVar14 = (long *)CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
          (**(code **)(*plVar14 + 0x300))(local_10c,plVar14);
        }
LAB_0058ef21:
        pcVar1 = *(code **)(*(long *)*(CPositionableObject **)(this + 0x58) + 0x200);
        local_58 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),true);
        local_50 = extraout_XMM1_Da_04;
        (*pcVar1)(local_10c,*(undefined8 *)(this + 0x58),
                  *(undefined8 *)(*(long *)(this + 0x20) + 0x10),&local_58);
        (**(code **)(**(long **)(this + 0x58) + 0x300))(local_10c);
        this_01 = *(CCharacter **)(this + 0x58);
      }
      if (this_01 == (CCharacter *)0x0) {
LAB_0058f6e0:
        this_01 = (CCharacter *)0x0;
      }
      else {
        if (((*(long *)(this_01 + 0x650) - (long)*(long **)(this_01 + 0x648) >> 3 != 0) &&
            (lVar8 = **(long **)(this_01 + 0x648), lVar8 != 0)) && (*(long *)(lVar8 + 0x208) != 0))
        {
          CGenericModel::updateAnimation(*(CGenericModel **)(lVar8 + 0x208),local_10c,false);
          this_01 = *(CCharacter **)(this + 0x58);
          if (this_01 == (CCharacter *)0x0) goto LAB_0058f6e0;
        }
        if ((*(CEffectManager **)(this_01 + 0x1b8) != (CEffectManager *)0x0) &&
           (*(long *)(this + 0x70) != 0)) {
          CEffectManager::updateAffixes(*(CEffectManager **)(this_01 + 0x1b8),0.0);
          CCharacter::updateEffects(0.0,*(CLevel **)(this + 0x58));
          CEffectManager::calculateEffectValues
                    (*(CEffectManager **)(*(long *)(this + 0x58) + 0x1b8));
          CEffectManager::deleteDeadEffects(*(CEffectManager **)(*(long *)(this + 0x58) + 0x1b8));
          this_01 = *(CCharacter **)(this + 0x58);
          if (this_01 == (CCharacter *)0x0) goto LAB_0058f6e0;
        }
        if (((*(long *)(this_01 + 0x650) - (long)*(long **)(this_01 + 0x648) >> 3 != 0) &&
            (lVar8 = **(long **)(this_01 + 0x648), lVar8 != 0)) &&
           ((*(long *)(lVar8 + 0x1b8) != 0 && (*(long *)(this + 0x70) != 0)))) {
          CEffectManager::updateAffixes(*(CEffectManager **)(lVar8 + 0x1b8),0.0);
          pCVar17 = (CLevel *)0x0;
          puVar2 = *(undefined8 **)(*(long *)(this + 0x58) + 0x648);
          if (*(long *)(*(long *)(this + 0x58) + 0x650) - (long)puVar2 >> 3 != 0) {
            pCVar17 = (CLevel *)*puVar2;
          }
          CCharacter::updateEffects(0.0,pCVar17);
          lVar8 = 0;
          plVar14 = *(long **)(*(long *)(this + 0x58) + 0x648);
          if (*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar14 >> 3 != 0) {
            lVar8 = *plVar14;
          }
          CEffectManager::calculateEffectValues(*(CEffectManager **)(lVar8 + 0x1b8));
          CEffectManager::deleteDeadEffects(*(CEffectManager **)(*(long *)(this + 0x58) + 0x1b8));
          this_01 = *(CCharacter **)(this + 0x58);
        }
      }
      CCharacter::updateCameraOpacity(this_01,*(Camera **)(*(long *)(this + 0x20) + 0x10),local_10c)
      ;
      CLevel::findItemsOnscreen
                (*(CLevel **)(this + 0x70),*(Camera **)(*(long *)(this + 0x20) + 0x10));
      CLevel::updateDroppingItems(*(CLevel **)(this + 0x70),local_10c);
      bVar6 = (bool)getIsPaused(this);
      CLevel::updateVisibleParticles
                (*(CLevel **)(this + 0x70),*(Camera **)(*(long *)(this + 0x20) + 0x10),
                 (Vector3 *)(*(long *)(this + 0x20) + 0x4c),bVar6);
LAB_0058e910:
      pCVar12 = *(CPositionableObject **)(this + 0x58);
    }
LAB_0058e914:
    local_68 = CPositionableObject::getPosition(pCVar12,true);
    *(undefined8 *)(this + 0x2c0) = local_68;
    *(undefined4 *)(this + 0x2c8) = extraout_XMM1_Da;
    local_60 = extraout_XMM1_Da;
    if ((*(long *)(*(long *)(this + 0x20) + 0x10) != 0) &&
       (pCVar12 = *(CPositionableObject **)(this + 0x58), pCVar12 != (CPositionableObject *)0x0)) {
      if (*(CPositionableObject **)(this + 0x1c0) != (CPositionableObject *)0x0) {
        pCVar12 = *(CPositionableObject **)(this + 0x1c0);
      }
      uVar25 = CPositionableObject::getPosition(pCVar12,false);
      fVar22 = extraout_XMM1_Da_00;
      local_a8 = uVar25;
      local_a0 = extraout_XMM1_Da_00;
      if (*(int *)(this + 0x390c) == 0) {
        iVar20 = *(int *)(*(long *)(this + 0x58) + 0x330);
        if (((iVar20 == 0x21) || (iVar20 == 0x14)) || ((iVar20 == 0x1c || (iVar20 == 0x20)))) {
LAB_0058f430:
          uVar7 = 2;
        }
        else if (iVar20 == 0x2c) {
          uVar25 = *(undefined8 *)(this + 0x38e0);
          fVar22 = *(float *)(this + 0x38e8);
          uVar7 = 0;
        }
        else {
          if (((iVar20 == 0x1f) &&
              (cVar5 = CGameUI::questDialogOpen(*(CGameUI **)(this + 0x78)), cVar5 != '\0')) ||
             (cVar5 = CGameUI::modalDialogOpenPartial(*(CGameUI **)(this + 0x78)), cVar5 != '\0')) {
            if (*(long *)(*(long *)(this + 0x58) + 0x340) != 0) {
              pfVar9 = (float *)CGameUI::getQuestDialogCameraOffset(*(CGameUI **)(this + 0x78));
              local_78 = CPositionableObject::getPosition
                                   (*(CPositionableObject **)(*(long *)(this + 0x58) + 0x340),false)
              ;
              fVar22 = extraout_XMM1_Da_01 + pfVar9[2];
              uVar25 = CONCAT44((float)((ulong)local_78 >> 0x20) + pfVar9[1],
                                (float)local_78 + *pfVar9);
              local_70 = extraout_XMM1_Da_01;
            }
            pCVar13 = *(CGameUI **)(this + 0x78);
          }
          else {
            if ((cVar4 == '\0') && (*(int *)(*(long *)(this + 0x58) + 0x330) != 0x22))
            goto LAB_0058f189;
            pCVar13 = *(CGameUI **)(this + 0x78);
            uVar7 = 1;
            if (pCVar13[0x1999] != (CGameUI)0x0) goto LAB_0058f18b;
          }
          cVar5 = CGameUI::tipMenuOpen(pCVar13);
          uVar7 = gLastCameraState;
          if (cVar5 == '\0') goto LAB_0058f430;
        }
      }
      else {
        if (*(int *)(this + 0x390c) == 1) {
          if (((*(int *)(*(long *)(this + 0x58) + 0x330) == 0x1f) &&
              (cVar5 = CGameUI::questDialogOpen(*(CGameUI **)(this + 0x78)), cVar5 != '\0')) ||
             (cVar5 = CGameUI::modalDialogOpenPartial(*(CGameUI **)(this + 0x78)), cVar5 != '\0')) {
            lVar8 = CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
            if (lVar8 == 0) {
              if (*(CPositionableObject **)(*(long *)(this + 0x58) + 0x340) !=
                  (CPositionableObject *)0x0) {
                local_98 = CPositionableObject::getPosition
                                     (*(CPositionableObject **)(*(long *)(this + 0x58) + 0x340),
                                      false);
                fVar22 = extraout_XMM1_Da_06;
                local_90 = extraout_XMM1_Da_06;
                uVar25 = local_98;
              }
            }
            else {
              pCVar12 = (CPositionableObject *)
                        CGameUI::getQuestDialogNPC(*(CGameUI **)(this + 0x78));
              local_88 = CPositionableObject::getPosition(pCVar12,true);
              fVar22 = extraout_XMM1_Da_05;
              local_80 = extraout_XMM1_Da_05;
              uVar25 = local_88;
            }
            pfVar9 = (float *)CGameUI::getQuestDialogCameraOffset(*(CGameUI **)(this + 0x78));
            uVar25 = CONCAT44((float)((ulong)uVar25 >> 0x20) + pfVar9[1],(float)uVar25 + *pfVar9);
            fVar22 = fVar22 + pfVar9[2];
            uVar7 = 2;
            goto LAB_0058f18b;
          }
          uVar25 = *(undefined8 *)(this + 0x38e0);
          fVar22 = *(float *)(this + 0x38e8);
        }
LAB_0058f189:
        uVar7 = 0;
      }
LAB_0058f18b:
      gLastCameraState = uVar7;
      local_a8 = uVar25;
      local_a0 = fVar22;
      CCameraControl::updateGameCamera
                (local_10c * *(float *)(this + 0x38c0),uVar25,fVar22,*(undefined8 *)(this + 0x20));
      *(undefined8 *)(this + 0x2c0) = uVar25;
      *(float *)(this + 0x2c8) = fVar22;
      if (*(long *)(this + 0x1060) != 0) {
        pVVar11 = (Vector3 *)Ogre::Camera::getPosition();
        CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x1060),pVVar11);
      }
    }
  }
  pCVar13 = *(CGameUI **)(this + 0x78);
  if ((pCVar13 == (CGameUI *)0x0) || (!param_4)) goto LAB_0058ed72;
  this_02 = *(CRunicCore **)(this + 0x1c8);
  if ((this_02 == (CRunicCore *)0x0) && (this[0x99] == (CGameClient)0x0)) {
    pCVar18 = *(CItem **)(this + 0x1f8);
    if (pCVar18 == (CItem *)0x0) {
      this_02 = *(CRunicCore **)(this + 0x1d8);
LAB_0058f68c:
      pCVar18 = *(CItem **)(this + 0x1e8);
    }
  }
  else {
    pCVar18 = *(CItem **)(this + 0x1f8);
    if (((pCVar18 == (CItem *)0x0) && (this[0x99] == (CGameClient)0x0)) &&
       (this_02 == (CRunicCore *)0x0)) goto LAB_0058f68c;
  }
  if (*(long **)(pCVar13 + 0x58) == (long *)0x0) {
    if (cVar4 == '\0') {
      lVar8 = CGameUI::getMouseOverItem(pCVar13);
      if (lVar8 != 0) {
        plVar14 = (long *)CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
        (**(code **)(*plVar14 + 0x208))(plVar14,0);
        pCVar15 = (CBaseUnit *)CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
        cVar4 = CBaseUnit::ISA(pCVar15);
        if (cVar4 == '\0') {
          if ((*(int *)(*(long *)(this + 0x78) + 0x12fc) != 3) &&
             (*(int *)(*(long *)(this + 0x78) + 0x12fc) != 4)) {
            CGameUI::setCursorState();
          }
        }
        else if ((*(int *)(*(long *)(this + 0x78) + 0x12fc) != 3) &&
                (*(int *)(*(long *)(this + 0x78) + 0x12fc) != 4)) {
          CGameUI::setCursorState();
        }
        goto LAB_0058f46c;
      }
      pCVar13 = *(CGameUI **)(this + 0x78);
    }
    if ((*(int *)(pCVar13 + 0x12fc) != 3) && (*(int *)(pCVar13 + 0x12fc) != 4)) {
      CGameUI::setCursorState(pCVar13);
    }
    if (cVar4 == '\0') goto LAB_0058f46c;
LAB_0058ecdf:
    plVar14 = *(long **)(*(CGameUI **)(this + 0x78) + 0x58);
    if (plVar14 == (long *)0x0) {
      lVar8 = CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
      if (lVar8 != 0) {
        plVar14 = (long *)CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
        (**(code **)(*plVar14 + 0x208))(plVar14);
      }
    }
    else {
      (**(code **)(*plVar14 + 0x208))();
    }
    pCVar13 = *(CGameUI **)(this + 0x78);
    if (*(CRunicCore **)(pCVar13 + 0x58) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(pCVar13 + 0x58),(TSafePointer *)(pCVar13 + 0x58),
                 *(uint *)(pCVar13 + 0x60));
      *(undefined8 *)(pCVar13 + 0x58) = 0;
      pCVar13 = *(CGameUI **)(this + 0x78);
    }
    CGameUI::setMouseOverItem(pCVar13,(CItem *)0x0,false);
  }
  else {
    (**(code **)(**(long **)(pCVar13 + 0x58) + 0x208))();
    if (cVar4 != '\0') goto LAB_0058ecdf;
    cVar4 = CCharacter::isEnemy(*(CCharacter **)(this + 0x58),
                                *(CCharacter **)(*(long *)(this + 0x78) + 0x58));
    if (cVar4 != '\0') {
      iVar20 = *(int *)(*(long *)(this + 0x78) + 0x12fc);
      if ((iVar20 != 3) && (iVar20 != 4)) {
                    /* try { // try from 0058f601 to 0058f605 has its CatchHandler @ 0058fa68 */
        cVar4 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x78) + 0x58),0xa7);
        if (cVar4 != '\0') {
                    /* try { // try from 0058f8cf to 0058f8e9 has its CatchHandler @ 0058fa68 */
          std::wstring::wstring(local_48,L"MIMICIDLE",local_39);
          cVar4 = CBaseUnit::hasUnitTheme(*(CBaseUnit **)(*(long *)(this + 0x78) + 0x58),local_48);
                    /* try { // try from 0058f8f3 to 0058f8f7 has its CatchHandler @ 0058fa43 */
          std::wstring::~wstring(local_48);
          if (cVar4 != '\0') {
            CGameUI::setCursorState(*(CGameUI **)(this + 0x78));
            goto LAB_0058f46c;
          }
        }
        CGameUI::setCursorState(*(CGameUI **)(this + 0x78));
      }
    }
LAB_0058f46c:
    if ((*(long **)(this + 0x58) != (long *)0x0) &&
       (cVar4 = (**(code **)(**(long **)(this + 0x58) + 0x48))(), cVar4 == '\0')) goto LAB_0058ecdf;
    pCVar13 = *(CGameUI **)(this + 0x78);
    this_00 = *(CRunicCore **)(pCVar13 + 0x58);
    if (this_02 != this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (this_00,(TSafePointer *)(pCVar13 + 0x58),*(uint *)(pCVar13 + 0x60));
      }
      *(undefined8 *)(pCVar13 + 0x58) = 0;
      if (this_02 != (CRunicCore *)0x0) {
        uVar7 = CRunicCore::addSafePointer(this_02,(TSafePointer *)(pCVar13 + 0x58));
        *(undefined4 *)(pCVar13 + 0x60) = uVar7;
      }
      *(CRunicCore **)(pCVar13 + 0x58) = this_02;
      pCVar13 = *(CGameUI **)(this + 0x78);
    }
    CGameUI::setMouseOverItem(pCVar13,pCVar18,false);
    plVar14 = *(long **)(*(CGameUI **)(this + 0x78) + 0x58);
    if (plVar14 == (long *)0x0) {
      lVar8 = CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
      if (lVar8 != 0) {
        plVar14 = (long *)CGameUI::getMouseOverItem(*(CGameUI **)(this + 0x78));
        (**(code **)(*plVar14 + 0x208))(plVar14,1);
      }
    }
    else {
      (**(code **)(*plVar14 + 0x208))(plVar14,1);
    }
  }
  CGameUI::update(local_10c,*(CGameClient **)(this + 0x78),(RenderWindow *)this);
  if (*(char *)(*(long *)(this + 0x78) + 0x12f9) != '\0') {
    this[0x103c] = (CGameClient)0x1;
  }
  if (*(char *)(*(long *)(this + 0x78) + 0x12fa) != '\0') {
    if (*(int *)(this + 0x38d0) == 1) {
      saveCharacter(this,false,true);
    }
    this[0x103d] = (CGameClient)0x1;
  }
LAB_0058ed72:
  if (*(CPositionableObject **)(this + 0x58) != (CPositionableObject *)0x0) {
    local_b8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),true);
    local_b0 = extraout_XMM1_Da_02;
    lVar8 = CMasterResourceManager::getSingleton();
    lVar8 = *(long *)(lVar8 + 0xf0);
    *(undefined8 *)(lVar8 + 0x4e0) = local_b8;
    *(undefined4 *)(lVar8 + 0x4e8) = local_b0;
    if (*(long *)(this + 0x1080) != 0) {
      local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x58),true);
      local_c0 = extraout_XMM1_Da_03;
      CPositionableObject::setPosition
                (*(CPositionableObject **)(this + 0x1080),(Vector3 *)&local_c8);
    }
  }
  return;
}



/* address=0058fa90
   symbol=CGameClient::setGameState */

/* WARNING: Removing unreachable block (ram,0x00590ee7) */
/* CGameClient::setGameState(EGameState, EMenu) */

void CGameClient::setGameState
               (undefined8 param_1,undefined8 param_2,CGameClient *param_3,int param_4)

{
  wchar_t *pwVar1;
  long lVar2;
  wchar_t wVar3;
  long *plVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  short sVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  CCharacter *pCVar12;
  Vector3 *pVVar13;
  CSteamStats *pCVar14;
  undefined8 uVar15;
  CPlayer *pCVar16;
  ulong uVar17;
  CQuestManager *this;
  long lVar18;
  CSharedStash *this_00;
  void *pvVar19;
  uint uVar20;
  CLevel *this_01;
  CPositionableObject *this_02;
  uint uVar21;
  wstring_conflict *this_03;
  bool bVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined8 in_stack_fffffffffffffd08;
  int local_2d4;
  void *local_2b8;
  long local_2b0;
  undefined8 local_2a8;
  void *local_298;
  long local_290;
  undefined8 local_288;
  undefined8 local_278;
  undefined8 local_270;
  undefined8 local_268;
  undefined4 local_260;
  undefined8 local_258;
  undefined4 local_250;
  undefined8 local_248;
  undefined4 local_240;
  undefined8 local_238;
  undefined4 local_230;
  wstring_conflict local_228 [16];
  wchar_t *local_218 [2];
  wstring_conflict local_208 [16];
  wstring_conflict local_1f8 [16];
  wstring_conflict local_1e8 [16];
  wstring_conflict local_1d8 [16];
  FILESYSTEM local_1c8 [16];
  FILESYSTEM local_1b8 [16];
  wstring_conflict local_1a8 [16];
  wstring_conflict local_198 [16];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  wstring_conflict local_168 [16];
  wstring_conflict local_158 [16];
  wstring_conflict local_148 [16];
  wstring_conflict local_138 [16];
  wstring_conflict local_128 [16];
  wstring_conflict local_118 [16];
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
  wstring_conflict local_e8 [16];
  wstring_conflict local_d8 [16];
  wstring_conflict local_c8 [16];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  FILESYSTEM local_68 [16];
  wchar_t *local_58 [2];
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

  uVar24 = (undefined4)((ulong)param_2 >> 0x20);
  uVar23 = (undefined4)param_2;
  cVar7 = CResourceManager::getEditorIsRunning();
  if (cVar7 != '\0') {
    return;
  }
  if (*(long *)(param_3 + 0x78) == 0) {
    return;
  }
  CGameUI::setCursorState();
  if (*(int *)(param_3 + 0x38d0) == param_4) {
    bVar22 = *(long *)(param_3 + 0x70) == 0;
  }
  else {
    CGameUI::setLoadingVisible(*(CGameUI **)(param_3 + 0x78),true);
    bVar22 = *(long *)(param_3 + 0x70) == 0;
    if ((*(int *)(param_3 + 0x38d0) != param_4) && (param_4 != 5)) {
      bVar22 = true;
      unloadCurrentLevel(param_3,true);
    }
  }
  uVar21 = (uint)((ulong)in_stack_fffffffffffffd08 >> 0x20);
  local_58[0] = &DAT_01424558;
  local_2d4 = param_4;
  if (param_4 == 2) {
    CSteamStats::getSingleton();
    CSteamStats::forceStatsToSave();
    lVar18 = *(long *)(param_3 + 0x78);
    FILESYSTEM::GetSaveDataPath(local_68);
                    /* try { // try from 005902b0 to 005902b4 has its CatchHandler @ 00590ee5 */
    FILESYSTEM::AssembleAbsolutePath
              (local_1b8,(wstring_conflict *)local_68,(wstring_conflict *)(lVar18 + 0x16c0));
                    /* try { // try from 005902b8 to 005902bc has its CatchHandler @ 00590ebe */
    std::wstring::~wstring((wstring_conflict *)local_68);
    local_2b8 = (void *)0x0;
    local_2b0 = 0;
    local_2a8 = 0;
    local_298 = (void *)0x0;
    local_290 = 0;
    local_288 = 0;
    if (*(long *)(param_3 + 0x58) != 0) {
                    /* try { // try from 00590300 to 00590441 has its CatchHandler @ 00590e05 */
      CGameUI::setPlayer(*(CGameUI **)(param_3 + 0x78),(CCharacter *)0x0);
      if (*(CLevel **)(param_3 + 0x70) != (CLevel *)0x0) {
        CLevel::removeCharacter(*(CLevel **)(param_3 + 0x70),*(CCharacter **)(param_3 + 0x58),true);
      }
      if (*(long **)(param_3 + 0x58) != (long *)0x0) {
        (**(code **)(**(long **)(param_3 + 0x58) + 8))();
        *(undefined8 *)(param_3 + 0x58) = 0;
      }
    }
    pCVar12 = *(CCharacter **)(param_3 + 0x60);
    if (pCVar12 != (CCharacter *)0x0) {
      if (*(CLevel **)(param_3 + 0x70) != (CLevel *)0x0) {
        CLevel::removeCharacter(*(CLevel **)(param_3 + 0x70),pCVar12,true);
        pCVar12 = *(CCharacter **)(param_3 + 0x60);
        if (pCVar12 == (CCharacter *)0x0) goto LAB_00590369;
      }
      (**(code **)(*(long *)pCVar12 + 8))(pCVar12);
      *(undefined8 *)(param_3 + 0x60) = 0;
    }
LAB_00590369:
    pCVar16 = (CPlayer *)
              loadCharacter(param_3,(wstring_conflict *)local_1b8,(vector *)&local_2b8,
                            (vector *)&local_298,false);
    *(CPlayer **)(param_3 + 0x58) = pCVar16;
    CQuestManager::setPlayer(*(CQuestManager **)(param_3 + 0x68),pCVar16);
    uVar21 = (uint)((ulong)in_stack_fffffffffffffd08 >> 0x20);
    if (*(long *)(param_3 + 0x58) == 0) {
      bVar5 = false;
      pvVar19 = local_298;
    }
    else {
      if (local_2b0 - (long)local_2b8 >> 3 != 0) {
        uVar17 = 0;
        uVar21 = 0;
        do {
          if (local_290 - (long)local_298 >> 3 != 0) {
            plVar4 = *(long **)((long)local_2b8 + uVar17 * 8);
            (**(code **)(*plVar4 + 0x2a0))(plVar4,*(undefined8 *)((long)local_298 + uVar17 * 8));
          }
          lVar18 = uVar17 * 8;
          if (uVar21 == 0) {
            *(undefined1 *)(*(long *)((long)local_2b8 + lVar18) + 0x52e) = 1;
            *(undefined8 *)(param_3 + 0x60) = *(undefined8 *)((long)local_2b8 + lVar18);
          }
          CCharacter::addPet(*(CCharacter **)(param_3 + 0x58),
                             *(CCharacter **)((long)local_2b8 + lVar18));
          uVar21 = uVar21 + 1;
          uVar17 = (ulong)uVar21;
        } while (uVar17 < (ulong)(local_2b0 - (long)local_2b8 >> 3));
      }
      uVar21 = (uint)((ulong)in_stack_fffffffffffffd08 >> 0x20);
      pvVar19 = local_298;
      if (local_290 - (long)local_298 >> 3 != 0) {
        uVar17 = 0;
        uVar20 = 0;
        lVar18 = local_290;
        do {
          plVar4 = *(long **)((long)pvVar19 + uVar17 * 8);
          if (plVar4 != (long *)0x0) {
                    /* try { // try from 005904d4 to 005904d6 has its CatchHandler @ 00590e05 */
            (**(code **)(*plVar4 + 8))();
            *(undefined8 *)((long)local_298 + uVar17 * 8) = 0;
            pvVar19 = local_298;
            lVar18 = local_290;
          }
          uVar21 = (uint)((ulong)in_stack_fffffffffffffd08 >> 0x20);
          uVar20 = uVar20 + 1;
          uVar17 = (ulong)uVar20;
        } while (uVar17 < (ulong)(lVar18 - (long)pvVar19 >> 3));
      }
      bVar5 = true;
      local_2d4 = 1;
    }
    if (pvVar19 != (void *)0x0) {
      operator_delete(pvVar19);
    }
    if (local_2b8 != (void *)0x0) {
      operator_delete(local_2b8);
    }
    std::wstring::~wstring((wstring_conflict *)local_1b8);
LAB_0058fb4b:
    if (local_2d4 != 1) {
      if (local_2d4 == 5) {
        *(undefined4 *)(param_3 + 0x2ac) = 0x3f800000;
        CGameUI::setLoadingVisible(*(CGameUI **)(param_3 + 0x78),true);
        if (*(int *)(*(long *)(param_3 + 0x78) + 0x1928) == 2) {
          this_01 = *(CLevel **)(param_3 + 0x70);
          if (((this_01 == (CLevel *)0x0) || (*(long *)(this_01 + 0x1d8) == 0)) ||
             (*(char *)(*(long *)(this_01 + 0x1d8) + 0x86) == '\0')) {
            (**(code **)(**(long **)(param_3 + 0x58) + 0x1f8))();
            std::wstring::wstring(local_88,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 005905a8 to 005905ac has its CatchHandler @ 00590e87 */
            std::wstring::wstring(local_78,L"Town",local_39);
                    /* try { // try from 005905c7 to 005905cb has its CatchHandler @ 00590e67 */
            warpLevels(param_3,local_78,0xffffff9d,0,0,local_88,(ulong)uVar21 << 0x20);
                    /* try { // try from 005905cf to 005905d3 has its CatchHandler @ 00590e87 */
            std::wstring::~wstring(local_78);
                    /* try { // try from 005905df to 005905e3 has its CatchHandler @ 00590e3a */
            std::wstring::~wstring(local_88);
            goto LAB_0058fc68;
          }
        }
        else {
          this_01 = *(CLevel **)(param_3 + 0x70);
        }
        CLevel::restartLevel(this_01);
      }
      else {
        bVar6 = false;
        if (local_2d4 != 0) goto LAB_0058fc6d;
        *(undefined4 *)(param_3 + 0x38d0) = 0;
        if (bVar22) {
                    /* try { // try from 0058fb8f to 0058fbbd has its CatchHandler @ 00590e3a */
          CGameUI::reloadMenuCharacters(*(CGameUI **)(param_3 + 0x78));
          if (*(long *)(param_3 + 0x58) == 0) {
            lVar18 = *(long *)(param_3 + 0x78);
            FILESYSTEM::GetSaveDataPath(local_1c8);
                    /* try { // try from 00590751 to 00590755 has its CatchHandler @ 00590e8c */
            FILESYSTEM::AssembleAbsolutePath
                      (local_1b8,(wstring_conflict *)local_1c8,(wstring_conflict *)(lVar18 + 0x16c0)
                      );
                    /* try { // try from 00590759 to 0059075d has its CatchHandler @ 00590d8d */
            std::wstring::~wstring((wstring_conflict *)local_1c8);
            local_298 = (void *)0x0;
            local_290 = 0;
            local_288 = 0;
            local_2b8 = (void *)0x0;
            local_2b0 = 0;
            local_2a8 = 0;
                    /* try { // try from 005907a7 to 005907e0 has its CatchHandler @ 00590d5a */
            lVar18 = loadCharacter(param_3,(wstring_conflict *)local_1b8,(vector *)&local_298,
                                   (vector *)&local_2b8,false);
            *(long *)(param_3 + 0x58) = lVar18;
            if (lVar18 == 0) {
                    /* try { // try from 00590c32 to 00590c36 has its CatchHandler @ 00590dae */
              std::wstring::wstring(local_1d8,L"TOWN",&local_46);
                    /* try { // try from 00590c48 to 00590c4c has its CatchHandler @ 00590dac */
              loadMenuLevel(param_3,*(undefined4 *)(param_3 + 0x1090),1);
                    /* try { // try from 00590c50 to 00590c54 has its CatchHandler @ 00590dae */
              std::wstring::~wstring(local_1d8);
                    /* try { // try from 00590c69 to 00590cb3 has its CatchHandler @ 00590d5a */
              pCVar12 = (CCharacter *)
                        CResourceManager::createPlayer
                                  (*(CResourceManager **)(*(long *)(param_3 + 0x70) + 0x138),
                                   *(wchar_t **)(param_3 + 0x1a8),false);
              *(CCharacter **)(param_3 + 0x58) = pCVar12;
              CCharacter::setAlignment(pCVar12,1);
              *(CGameClient *)(*(long *)(param_3 + 0x58) + 0xa15) = param_3[0x1b8];
              CPlayer::firstTimeSetup(*(CPlayer **)(param_3 + 0x58));
              std::wstring::wstring
                        (local_1e8,(wstring_conflict *)(*(long *)(param_3 + 0x78) + 0x16b0));
                    /* try { // try from 00590cc2 to 00590cc6 has its CatchHandler @ 00590d9f */
              std::wstring::assign((wstring_conflict *)(*(long *)(param_3 + 0x58) + 0x4c0));
                    /* try { // try from 00590cca to 00590d0e has its CatchHandler @ 00590d5a */
              std::wstring::~wstring(local_1e8);
              pCVar16 = *(CPlayer **)(param_3 + 0x58);
              this_00 = (CSharedStash *)CSharedStash::getSingleton();
              CSharedStash::setPlayer(this_00,pCVar16);
              pCVar12 = (CCharacter *)
                        CResourceManager::createMonster
                                  (*(CResourceManager **)(*(long *)(param_3 + 0x70) + 0x138),
                                   *(wchar_t **)(param_3 + 0x1b0),0,false);
              *(CCharacter **)(param_3 + 0x60) = pCVar12;
              CCharacter::setAlignment(pCVar12,1);
            }
            else {
              std::wstring::assign((wchar_t *)(param_3 + 0x1a8));
              std::wstring::wstring(local_1f8,(wstring_conflict *)(param_3 + 0x1098));
                    /* try { // try from 005907f3 to 005907f7 has its CatchHandler @ 00590f25 */
              loadMenuLevel(param_3,*(undefined4 *)(param_3 + 0x1090),
                            *(undefined4 *)(param_3 + 0x1094));
                    /* try { // try from 005907fb to 005909a6 has its CatchHandler @ 00590d5a */
              std::wstring::~wstring(local_1f8);
            }
            if (*(CCharacter **)(param_3 + 0x58) != (CCharacter *)0x0) {
              CLevel::addCharacter
                        (*(CLevel **)(param_3 + 0x70),*(CCharacter **)(param_3 + 0x58),
                         (Vector3 *)(*(CLevel **)(param_3 + 0x70) + 0x140),false);
              CCharacter::setToward
                        (*(CCharacter **)(param_3 + 0x58),
                         (Vector3 *)(*(long *)(param_3 + 0x70) + 0x164));
              if (((*(long *)(param_3 + 0x58) != 0) && (lVar18 != 0)) &&
                 (local_290 - (long)local_298 >> 3 != 0)) {
                uVar17 = 0;
                uVar21 = 0;
                pvVar19 = local_298;
                lVar18 = local_290;
                do {
                  if (uVar21 == 0) {
                    if (local_2b0 - (long)local_2b8 >> 3 != 0) {
                      plVar4 = *(long **)((long)pvVar19 + uVar17 * 8);
                      lVar2 = uVar17 * 8;
                      (**(code **)(*plVar4 + 0x2a0))
                                (plVar4,*(undefined8 *)((long)local_2b8 + uVar17 * 8));
                      uVar20 = KSETTINGS_NO_PET;
                      lVar18 = CMasterResourceManager::getSingleton();
                      iVar11 = CDynamicPropertyFile::GetInt
                                         (*(CDynamicPropertyFile **)(lVar18 + 0x90),uVar20);
                      if (iVar11 == 0) {
                        pCVar12 = *(CCharacter **)((long)local_298 + lVar2);
                        *(CCharacter **)(param_3 + 0x60) = pCVar12;
                    /* try { // try from 00590a15 to 00590a2b has its CatchHandler @ 00590d5a */
                        CCharacter::setAlignment(pCVar12,1);
                        CCharacter::addPet(*(CCharacter **)(param_3 + 0x58),
                                           *(CCharacter **)((long)local_298 + lVar2));
                        pvVar19 = local_298;
                        lVar18 = local_290;
                      }
                      else {
                        pvVar19 = local_298;
                        lVar18 = local_290;
                        if (*(long **)((long)local_298 + lVar2) != (long *)0x0) {
                          (**(code **)(**(long **)((long)local_298 + lVar2) + 8))();
                          *(undefined8 *)((long)local_298 + lVar2) = 0;
                          pvVar19 = local_298;
                          lVar18 = local_290;
                        }
                      }
                    }
                  }
                  else {
                    plVar4 = *(long **)((long)pvVar19 + uVar17 * 8);
                    if (plVar4 != (long *)0x0) {
                      (**(code **)(*plVar4 + 8))();
                      *(undefined8 *)((long)local_298 + uVar17 * 8) = 0;
                      pvVar19 = local_298;
                      lVar18 = local_290;
                    }
                  }
                  uVar21 = uVar21 + 1;
                  uVar17 = (ulong)uVar21;
                } while (uVar17 < (ulong)(lVar18 - (long)pvVar19 >> 3));
              }
            }
            if (*(CCharacter **)(param_3 + 0x60) != (CCharacter *)0x0) {
              CLevel::addCharacter
                        (*(CLevel **)(param_3 + 0x70),*(CCharacter **)(param_3 + 0x60),
                         (Vector3 *)(*(CLevel **)(param_3 + 0x70) + 0x170),false);
              CCharacter::setToward
                        (*(CCharacter **)(param_3 + 0x60),
                         (Vector3 *)(*(long *)(param_3 + 0x70) + 0x17c));
            }
            pvVar19 = local_2b8;
            if (local_2b0 - (long)local_2b8 >> 3 != 0) {
              uVar17 = 0;
              uVar21 = 0;
              lVar18 = local_2b0;
              do {
                plVar4 = *(long **)((long)pvVar19 + uVar17 * 8);
                if (plVar4 != (long *)0x0) {
                  (**(code **)(*plVar4 + 8))();
                  *(undefined8 *)((long)local_2b8 + uVar17 * 8) = 0;
                  pvVar19 = local_2b8;
                  lVar18 = local_2b0;
                }
                uVar21 = uVar21 + 1;
                uVar17 = (ulong)uVar21;
              } while (uVar17 < (ulong)(lVar18 - (long)pvVar19 >> 3));
            }
            if (pvVar19 != (void *)0x0) {
              operator_delete(pvVar19);
            }
            if (local_298 != (void *)0x0) {
              operator_delete(local_298);
            }
                    /* try { // try from 005909f9 to 005909fd has its CatchHandler @ 00590e3a */
            std::wstring::~wstring((wstring_conflict *)local_1b8);
          }
          else {
            std::wstring::wstring(local_208,(wstring_conflict *)(param_3 + 0x1098));
                    /* try { // try from 0058fbd0 to 0058fbd4 has its CatchHandler @ 00590ea4 */
            loadMenuLevel(param_3,*(undefined4 *)(param_3 + 0x1090),
                          *(undefined4 *)(param_3 + 0x1094));
                    /* try { // try from 0058fbe0 to 0058fefc has its CatchHandler @ 00590e3a */
            std::wstring::~wstring(local_208);
          }
        }
        CQuestManager::setPlayer(*(CQuestManager **)(param_3 + 0x68),*(CPlayer **)(param_3 + 0x58));
        CGameUI::setActiveMenu(*(undefined8 *)(param_3 + 0x78));
        CGameUI::setIngameUIVisible(*(CGameUI **)(param_3 + 0x78),false);
      }
LAB_0058fc68:
      bVar6 = false;
      goto LAB_0058fc6d;
    }
  }
  else {
    bVar5 = false;
    if (1 < param_4 - 3U) goto LAB_0058fb4b;
    if ((param_4 == 3) && (*(long **)(param_3 + 0x3900) != (long *)0x0)) {
      (**(code **)(**(long **)(param_3 + 0x3900) + 8))();
      *(undefined8 *)(param_3 + 0x3900) = 0;
      *(undefined4 *)(param_3 + 0x3908) = 0;
    }
    uVar21 = KSETTINGS_LEVEL_SEED;
    lVar18 = CMasterResourceManager::getSingleton();
    iVar11 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar18 + 0x90),uVar21);
    uVar21 = KSETTINGS_LEVEL_SEED;
    if (iVar11 == 0) {
                    /* try { // try from 0059045b to 00590495 has its CatchHandler @ 00590e3a */
      uVar9 = UTILITIES::randomIntegerBetweenVolatile(0,0x7fffffff);
    }
    else {
      lVar18 = CMasterResourceManager::getSingleton();
      uVar9 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar18 + 0x90),uVar21);
    }
    *(undefined4 *)(param_3 + 0x1090) = uVar9;
    bVar5 = false;
    local_2d4 = 1;
  }
  *(int *)(param_3 + 0x38d0) = local_2d4;
  std::wstring::assign((wchar_t *)local_58);
  if (!bVar5) {
                    /* try { // try from 00590528 to 0059058f has its CatchHandler @ 00590e3a */
    this = (CQuestManager *)CQuestManager::getSingleton();
    CQuestManager::resetQuestManager(this,false);
  }
  bVar6 = false;
  if (bVar22) {
    sVar8 = GetAsyncKeyState(0x10);
                    /* try { // try from 00590a3b to 00590a3f has its CatchHandler @ 00590e3a */
    if ((sVar8 < 0) &&
       (iVar11 = CDynamicPropertyFile::GetInt
                           (*(CDynamicPropertyFile **)(param_3 + 0x50),KSETTINGS_ALLOW_CONSOLE),
       iVar11 != 0)) {
                    /* try { // try from 00590a60 to 00590a64 has its CatchHandler @ 00590ef5 */
      std::wstring::wstring(local_a8,L"TOWN",&local_3b);
                    /* try { // try from 00590a7d to 00590a81 has its CatchHandler @ 00590d46 */
      std::wstring::wstring(local_98,L"dungeon",&local_3a);
                    /* try { // try from 00590a9e to 00590aa2 has its CatchHandler @ 00590d31 */
      CCmdLineParser::GetStringParam
                ((wstring_conflict *)local_1b8,*(undefined8 *)(*(long *)(param_3 + 0x50) + 0x140),
                 local_98,local_a8);
                    /* try { // try from 00590aa6 to 00590aaa has its CatchHandler @ 00590d92 */
      std::wstring::~wstring(local_98);
                    /* try { // try from 00590aae to 00590ab2 has its CatchHandler @ 00590d16 */
      std::wstring::~wstring(local_a8);
                    /* try { // try from 00590ac1 to 00590ac5 has its CatchHandler @ 00590d58 */
      std::wstring::wstring(local_b8,(wstring_conflict *)local_1b8);
                    /* try { // try from 00590acc to 00590ad0 has its CatchHandler @ 00590d4b */
      setCurrentDungeon(param_3,local_b8);
                    /* try { // try from 00590ad4 to 00590af6 has its CatchHandler @ 00590d58 */
      std::wstring::~wstring(local_b8);
      if (bVar5) {
        this_03 = local_e8;
        std::wstring::wstring(this_03,(wstring_conflict *)&::EMPTY_WSTRING);
        uVar9 = *(undefined4 *)(param_3 + 0x1094);
                    /* try { // try from 00590b19 to 00590b1d has its CatchHandler @ 00590f1c */
        std::wstring::wstring(local_d8,local_58[0],&local_3d);
                    /* try { // try from 00590b36 to 00590b3a has its CatchHandler @ 00590f17 */
        std::wstring::wstring(local_c8,L"",&local_3c);
                    /* try { // try from 00590b5d to 00590b61 has its CatchHandler @ 00590efa */
        loadLevel(param_3,local_c8,local_d8,1,uVar9,4,this_03);
                    /* try { // try from 00590b65 to 00590b69 has its CatchHandler @ 00590f17 */
        std::wstring::~wstring(local_c8);
                    /* try { // try from 00590b72 to 00590b76 has its CatchHandler @ 00590f1c */
        std::wstring::~wstring(local_d8);
      }
      else {
        this_03 = local_118;
                    /* try { // try from 00590b9c to 00590ba0 has its CatchHandler @ 00590d58 */
        std::wstring::wstring(this_03,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00590bb9 to 00590bbd has its CatchHandler @ 00590f4c */
        std::wstring::wstring(local_108,local_58[0],&local_3f);
                    /* try { // try from 00590bd6 to 00590bda has its CatchHandler @ 00590f47 */
        std::wstring::wstring(local_f8,L"",&local_3e);
                    /* try { // try from 00590bfb to 00590bff has its CatchHandler @ 00590f2a */
        loadLevel(param_3,local_f8,local_108,1,0,7,this_03);
                    /* try { // try from 00590c03 to 00590c07 has its CatchHandler @ 00590f47 */
        std::wstring::~wstring(local_f8);
                    /* try { // try from 00590c10 to 00590c14 has its CatchHandler @ 00590f4c */
        std::wstring::~wstring(local_108);
      }
                    /* try { // try from 00590b7a to 00590b7e has its CatchHandler @ 00590d58 */
      std::wstring::~wstring(this_03);
                    /* try { // try from 00590b82 to 00590b86 has its CatchHandler @ 00590e3a */
      std::wstring::~wstring((wstring_conflict *)local_1b8);
LAB_005901bd:
      bVar6 = false;
    }
    else {
      if (bVar5) {
        std::wstring::wstring(local_148,(wstring_conflict *)&::EMPTY_WSTRING);
        uVar9 = *(undefined4 *)(param_3 + 0x1094);
                    /* try { // try from 00590164 to 00590168 has its CatchHandler @ 00590e62 */
        std::wstring::wstring(local_138,L"",&local_41);
                    /* try { // try from 00590181 to 00590185 has its CatchHandler @ 00590e5c */
        std::wstring::wstring(local_128,L"",&local_40);
                    /* try { // try from 005901a0 to 005901a4 has its CatchHandler @ 00590e3c */
        loadLevel(param_3,local_128,local_138,0,uVar9,4,local_148);
                    /* try { // try from 005901a8 to 005901ac has its CatchHandler @ 00590e5c */
        std::wstring::~wstring(local_128);
                    /* try { // try from 005901b0 to 005901b4 has its CatchHandler @ 00590e62 */
        std::wstring::~wstring(local_138);
                    /* try { // try from 005901b8 to 00590237 has its CatchHandler @ 00590e3a */
        std::wstring::~wstring(local_148);
        goto LAB_005901bd;
      }
                    /* try { // try from 00590601 to 00590605 has its CatchHandler @ 00590df5 */
      std::wstring::wstring(local_168,L"TOWN",&local_43);
                    /* try { // try from 0059061e to 00590622 has its CatchHandler @ 00590de7 */
      std::wstring::wstring(local_158,L"dungeon",&local_42);
                    /* try { // try from 0059063f to 00590643 has its CatchHandler @ 00590de2 */
      CCmdLineParser::GetStringParam
                ((wstring_conflict *)local_1b8,*(undefined8 *)(*(long *)(param_3 + 0x50) + 0x140),
                 local_158);
                    /* try { // try from 00590647 to 0059064b has its CatchHandler @ 00590dd5 */
      std::wstring::~wstring(local_158);
                    /* try { // try from 0059064f to 00590653 has its CatchHandler @ 00590dc5 */
      std::wstring::~wstring(local_168);
                    /* try { // try from 00590662 to 00590666 has its CatchHandler @ 00590db6 */
      std::wstring::wstring(local_178,(wstring_conflict *)local_1b8);
                    /* try { // try from 0059066d to 00590671 has its CatchHandler @ 00590db4 */
      setCurrentDungeon(param_3,local_178);
                    /* try { // try from 00590675 to 0059068e has its CatchHandler @ 00590db6 */
      std::wstring::~wstring(local_178);
      std::wstring::wstring(local_1a8,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 005906a4 to 005906a8 has its CatchHandler @ 00590db2 */
      std::wstring::wstring(local_198,L"",&local_45);
                    /* try { // try from 005906c1 to 005906c5 has its CatchHandler @ 00590ee0 */
      std::wstring::wstring(local_188,L"",&local_44);
                    /* try { // try from 005906e3 to 005906e7 has its CatchHandler @ 00590ec3 */
      loadLevel(param_3,local_188,local_198,0,0,7,local_1a8);
                    /* try { // try from 005906eb to 005906ef has its CatchHandler @ 00590ee0 */
      std::wstring::~wstring(local_188);
                    /* try { // try from 005906f8 to 005906fc has its CatchHandler @ 00590db2 */
      std::wstring::~wstring(local_198);
                    /* try { // try from 00590700 to 00590704 has its CatchHandler @ 00590db6 */
      std::wstring::~wstring(local_1a8);
                    /* try { // try from 00590708 to 0059073d has its CatchHandler @ 00590e3a */
      std::wstring::~wstring((wstring_conflict *)local_1b8);
      bVar6 = true;
    }
    if (*(long *)(param_3 + 0x70) != 0) {
      pCVar14 = (CSteamStats *)CSteamStats::getSingleton();
      iVar10 = CSteamStats::getStatInt(pCVar14,5);
      iVar11 = *(int *)(*(long *)(param_3 + 0x70) + 0x1a4);
      if (iVar10 < iVar11) {
        uVar15 = CSteamStats::getSingleton();
        CSteamStats::setStatInt(uVar15,5,iVar11);
      }
    }
  }
  CGameUI::closeMenus(*(CGameUI **)(param_3 + 0x78));
  CGameUI::setIngameUIVisible(*(CGameUI **)(param_3 + 0x78),true);
LAB_0058fc6d:
  if (bVar5) {
    this_02 = *(CPositionableObject **)(param_3 + 0x58);
    if ((int)((ulong)(*(long *)(this_02 + 0x650) - *(long *)(this_02 + 0x648)) >> 3) != 0) {
      uVar17 = 0;
      do {
        local_238 = CPositionableObject::getPosition(this_02,true);
        local_230 = uVar23;
        local_248 = CLevel::randomOpenPosition
                              (*(CLevel **)(param_3 + 0x70),(Vector3 *)&local_238,DAT_00fa86d0,false
                              );
        pCVar12 = (CCharacter *)0x0;
        lVar18 = *(long *)(*(long *)(param_3 + 0x58) + 0x648);
        if (*(long *)(*(long *)(param_3 + 0x58) + 0x650) - lVar18 >> 3 != 0) {
          pCVar12 = *(CCharacter **)(lVar18 + uVar17 * 8);
        }
        local_240 = uVar23;
        pCVar12 = (CCharacter *)
                  CLevel::addCharacter
                            (*(CLevel **)(param_3 + 0x70),pCVar12,(Vector3 *)&local_248,false);
        pVVar13 = (Vector3 *)(**(code **)(**(long **)(param_3 + 0x58) + 0x130))();
        CCharacter::setToward(pCVar12,pVVar13);
        CCharacter::setMaximumTreeDepth(pCVar12,800);
        this_02 = *(CPositionableObject **)(param_3 + 0x58);
        uVar21 = (int)uVar17 + 1;
        uVar17 = (ulong)uVar21;
      } while (uVar21 < (uint)(*(long *)(this_02 + 0x650) - *(long *)(this_02 + 0x648) >> 3));
    }
    CLevel::deleteOpenPortals(*(CLevel **)(param_3 + 0x70));
    CPlayer::createPortals(*(CPlayer **)(param_3 + 0x58),*(CLevel **)(param_3 + 0x70));
  }
  if ((*(long *)(*(CPositionableObject **)(param_3 + 0x58) + 0x1c8) != 0) && (local_2d4 != 0)) {
    local_268 = CPositionableObject::getPosition(*(CPositionableObject **)(param_3 + 0x58),true);
    local_260 = uVar23;
    local_278 = (**(code **)(**(long **)(param_3 + 0x58) + 0xf0))();
    local_270 = CONCAT44(uVar24,uVar23);
    local_258 = CPositionableObject::getPosition(*(CPositionableObject **)(param_3 + 0x58),true);
    local_250 = uVar23;
    CSkillManager::startPassiveSkills
              (*(CSkillManager **)(*(CBaseUnit **)(param_3 + 0x58) + 0x1c8),
               *(CBaseUnit **)(param_3 + 0x58),(Vector3 *)&local_258,(Quaternion *)&local_278,
               (Vector3 *)&local_268);
  }
  if ((bVar6) && (saveCharacter(param_3,false,false), *(long *)(param_3 + 0x58) != 0)) {
                    /* try { // try from 0058ff11 to 0058ff15 has its CatchHandler @ 00590e2a */
    CCharacter::getIntroCinematic();
    bVar22 = true;
    if (*(size_t *)(local_218[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
      iVar11 = wmemcmp(local_218[0],::EMPTY_WSTRING,*(size_t *)(local_218[0] + -6));
      bVar22 = iVar11 != 0;
    }
                    /* try { // try from 0058ff44 to 00590141 has its CatchHandler @ 00590e3a */
    std::wstring::~wstring((wstring_conflict *)local_218);
    if (bVar22) {
      CCharacter::getIntroCinematic();
                    /* try { // try from 0059023f to 00590243 has its CatchHandler @ 00590ea6 */
      CGameUI::setCinematicOpen(*(CGameUI **)(param_3 + 0x78));
                    /* try { // try from 0059024f to 0059029c has its CatchHandler @ 00590e3a */
      std::wstring::~wstring(local_228);
    }
  }
  CGameUI::setLoadingVisible(*(CGameUI **)(param_3 + 0x78),false);
  CGameUI::setCursorState(*(CGameUI **)(param_3 + 0x78),0);
  CMouseManager::flushAll((CMouseManager *)(param_3 + 0xfe8));
  CKeyManager::flushAll((CKeyManager *)(param_3 + 0x2d0));
  pCVar12 = *(CCharacter **)(param_3 + 0x58);
  param_3[0x99] = (CGameClient)0x0;
  param_3[0x9a] = (CGameClient)0x0;
  param_3[0x98] = (CGameClient)0x1;
  if ((pCVar12 != (CCharacter *)0x0) && (pCVar12[0x264] != (CCharacter)0x0)) {
    CCharacter::stopPathing(pCVar12);
  }
  if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_58[0] + -2;
    wVar3 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
    }
  }
  return;
}



/* address=00590f60
   symbol=CGameClient::create */

/* WARNING: Removing unreachable block (ram,0x0059162f) */
/* WARNING: Removing unreachable block (ram,0x00591672) */
/* WARNING: Removing unreachable block (ram,0x00591680) */
/* CGameClient::create() */

undefined8 __thiscall CGameClient::create(CGameClient *this)

{
  int *piVar1;
  code *pcVar2;
  CSoundManager *pCVar3;
  CSoundBankDataInformation *this_00;
  uint uVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  Vector3 *pVVar8;
  CSoundBank *this_01;
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  uVar4 = KSETTINGS_OVERRIDE_LIGHTING;
  lVar6 = CMasterResourceManager::getSingleton();
  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
  uVar4 = KSETTINGS_AMBIENT_LIGHT_BLUE;
  if (iVar5 < 1) {
    Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x28));
  }
  else {
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    uVar4 = KSETTINGS_AMBIENT_LIGHT_GREEN;
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    uVar4 = KSETTINGS_AMBIENT_LIGHT_RED;
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x28));
  }
  pcVar2 = *(code **)(**(long **)(this + 0x28) + 0x1d8);
                    /* try { // try from 00591062 to 00591066 has its CatchHandler @ 00591666 */
  std::string::string((string *)&local_38,"Sunlight",&local_29);
                    /* try { // try from 0059106e to 00591070 has its CatchHandler @ 00591650 */
  uVar7 = (*pcVar2)(*(undefined8 *)(this + 0x28),(string *)&local_38);
  *(undefined8 *)(this + 0x38c8) = uVar7;
  if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38 + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
    }
    uVar7 = *(undefined8 *)(this + 0x38c8);
  }
  Ogre::Light::setType(uVar7,1);
  Ogre::Light::setPosition(DAT_00fa8748,DAT_00fa875c,DAT_00fa8770);
  Ogre::Light::getPosition();
  Ogre::Light::setDirection(*(Vector3 **)(this + 0x38c8));
  Ogre::Light::setSpecularColour(DAT_00fa4810,DAT_00fa4810,DAT_00fa4810);
  uVar4 = KSETTINGS_OVERRIDE_LIGHTING;
  lVar6 = CMasterResourceManager::getSingleton();
  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
  uVar4 = KSETTINGS_F_DIRECTIONAL_INTENSITY;
  if (iVar5 < 1) {
    Ogre::Light::setDiffuseColour(*(ColourValue **)(this + 0x38c8));
  }
  else {
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetFloat(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_BLUE;
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_GREEN;
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    uVar4 = KSETTINGS_DIRECTIONAL_LIGHT_RED;
    lVar6 = CMasterResourceManager::getSingleton();
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar6 + 0x90),uVar4);
    Ogre::Light::setDiffuseColour(*(ColourValue **)(this + 0x38c8));
  }
  *(undefined1 *)(*(long *)(this + 0x38c8) + 0xc0) = 0;
  Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x38));
  Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x40));
  pcVar2 = *(code **)(**(long **)(this + 0x38) + 0x1d8);
                    /* try { // try from 00591308 to 0059130c has its CatchHandler @ 00591652 */
  std::string::string((string *)local_48,"Sunlight",&local_2a);
                    /* try { // try from 00591314 to 00591316 has its CatchHandler @ 0059163d */
  pVVar8 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x38),(string *)local_48);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  Ogre::Light::setType(pVVar8,1);
  Ogre::Light::setPosition(DAT_00fa86e0,DAT_00fa877c,DAT_00fa8778);
  Ogre::Light::getPosition();
  Ogre::Light::setDirection(pVVar8);
  Ogre::Light::setDiffuseColour(DAT_00fa4824,DAT_00fa4824,DAT_00fa4824);
  Ogre::Light::setSpecularColour(DAT_00fa4810,DAT_00fa4810,DAT_00fa4810);
  pVVar8[0xc0] = (Vector3)0x0;
  lVar6 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar6 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0059145c to 00591460 has its CatchHandler @ 0059161c */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0x1088) = this_01;
  lVar6 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar6 + 0x100);
                    /* try { // try from 00591489 to 0059148d has its CatchHandler @ 00591664 */
  std::wstring::wstring((wstring_conflict *)local_58,L"TOWNPORTALENTER",&local_2b);
                    /* try { // try from 00591494 to 00591498 has its CatchHandler @ 00591657 */
  lVar6 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (lVar6 != 0) {
    CSoundBank::addSample(*(CSoundBank **)(this + 0x1088),0x1c,*(longlong *)(lVar6 + 0x20));
  }
  if (*(char *)(*(long *)(this + 0x2b8) + 0x43) == '\0') {
    setGameState(this,0,0);
  }
  return 1;
}



/* address=00591690
   symbol=CGameClient::update */

/* CGameClient::update(float, Ogre::RenderWindow*, float, bool) */

void __thiscall
CGameClient::update(CGameClient *this,float param_1,RenderWindow *param_2,float param_3,bool param_4
                   )

{
  bool bVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  CGameUI *pCVar7;
  float fVar8;

  pCVar7 = *(CGameUI **)(this + 0x78);
  if (pCVar7 != (CGameUI *)0x0) {
    if (GForceMenuExit != '\0') {
      cVar3 = CGameUI::modalDialogOpen(pCVar7);
      if (cVar3 == '\0') {
        GForceMenuExit = '\0';
        setGameState(this,0,0);
      }
      pCVar7 = *(CGameUI **)(this + 0x78);
    }
    CGameUI::getUIIsInCinematic(pCVar7);
    cVar3 = CGameUI::getUIIsInCinematic(*(CGameUI **)(this + 0x78));
    if ((cVar3 != gCinematicActive) && (*(CLevel **)(this + 0x70) != (CLevel *)0x0)) {
      CLevel::updateNPCIcons(*(CLevel **)(this + 0x70));
      gCinematicActive = cVar3;
    }
  }
  if (*(int *)(this + 0x84) < 1) {
    *(undefined1 *)(*(long *)(this + 0x2b8) + 0x40) = 0;
  }
  else {
    *(int *)(this + 0x84) = *(int *)(this + 0x84) + -1;
    *(undefined1 *)(*(long *)(this + 0x2b8) + 0x40) = 1;
  }
  pCVar7 = *(CGameUI **)(this + 0x78);
  if ((pCVar7 != (CGameUI *)0x0) && (*(int *)(pCVar7 + 0x1914) != 6)) {
    cVar3 = CGameUI::modalDialogOpen(pCVar7);
    if (cVar3 == '\0') {
      cVar3 = CGameUI::leftCovered(*(CGameUI **)(this + 0x78));
      if (cVar3 == '\0') {
        cVar3 = CGameUI::rightCovered(*(CGameUI **)(this + 0x78));
        if (cVar3 == '\0') {
          pCVar7 = *(CGameUI **)(this + 0x78);
          iVar4 = *(int *)(pCVar7 + 0x1914);
          if ((iVar4 == 0) && (*(int *)(this + 0x38d0) == 1)) {
            CGameUI::closeAll(pCVar7);
            killPets(this);
            saveCharacter(this,false,true);
            pCVar7 = *(CGameUI **)(this + 0x78);
            iVar4 = *(int *)(pCVar7 + 0x1914);
          }
          setGameState(this,iVar4,*(undefined4 *)(pCVar7 + 0x1918));
          CGameUI::clearGameStateRequest(*(CGameUI **)(this + 0x78));
          CMouseManager::flushAll((CMouseManager *)(this + 0xfe8));
          CKeyManager::flushAll((CKeyManager *)(this + 0x2d0));
          this[0x99] = (CGameClient)0x0;
          this[0x9a] = (CGameClient)0x0;
          this[0x98] = (CGameClient)0x1;
        }
      }
    }
  }
  fVar2 = DAT_00fa47f8;
  iVar4 = *(int *)(this + 0x38d0);
  if (iVar4 == 1) {
    updateIngame(this,param_1,param_2,param_3,param_4);
  }
  else if (iVar4 == 5) {
    fVar8 = *(float *)(this + 0x2ac) - param_3;
    bVar1 = NAN(DAT_00fa47f8);
    *(float *)(this + 0x2ac) = fVar8;
    if ((fVar8 <= fVar2) && (!NAN(fVar8) && !bVar1)) {
      setGameState(this,1,0);
    }
  }
  else if (iVar4 == 0) {
    updateMenu(this,param_1,param_2,param_3,param_4);
  }
  if ((0 < *(int *)(this + 0x1038)) &&
     (iVar4 = *(int *)(this + 0x1038) + -1, *(int *)(this + 0x1038) = iVar4, iVar4 == 0)) {
    plVar5 = (long *)Ogre::MeshManager::getSingleton();
    (**(code **)(*plVar5 + 0x70))(plVar5,1);
    plVar5 = (long *)Ogre::MaterialManager::getSingleton();
    (**(code **)(*plVar5 + 0x70))(plVar5,1);
    plVar5 = (long *)Ogre::TextureManager::getSingleton();
    (**(code **)(*plVar5 + 0x70))(plVar5,1);
    lVar6 = CMasterResourceManager::getSingleton();
    CSoundManager::releaseUnusedSounds(*(CSoundManager **)(lVar6 + 0x98));
    CMasterResourceManager::removeUnused(*(CMasterResourceManager **)(this + 0x1040));
    return;
  }
  return;
}



/* address=00b342f0
   symbol=CGameClient::clearMouseClickUnits */

/* CGameClient::clearMouseClickUnits() */

void __thiscall CGameClient::clearMouseClickUnits(CGameClient *this)

{
  if (*(CRunicCore **)(this + 0x1f8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1f8),(TSafePointer *)(this + 0x1f8),*(uint *)(this + 0x200)
              );
    *(undefined8 *)(this + 0x1f8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1e8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1e8),(TSafePointer *)(this + 0x1e8),*(uint *)(this + 0x1f0)
              );
    *(undefined8 *)(this + 0x1e8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1c8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1c8),(TSafePointer *)(this + 0x1c8),*(uint *)(this + 0x1d0)
              );
    *(undefined8 *)(this + 0x1c8) = 0;
  }
  if (*(CRunicCore **)(this + 0x1d8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1d8),(TSafePointer *)(this + 0x1d8),*(uint *)(this + 0x1e0)
              );
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  return;
}



/* export-summary functions=71 failures=1 */
