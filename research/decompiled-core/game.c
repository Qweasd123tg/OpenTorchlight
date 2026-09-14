/* Targeted Ghidra class export.
   namespace=CGame
   Treat pseudocode as navigation evidence. */


/* address=005566a0
   symbol=CGame::requestingRestart */

/* CGame::requestingRestart() */

CGame __thiscall CGame::requestingRestart(CGame *this)

{
  return this[0xcb];
}



/* address=005566b0
   symbol=CGame::setupResources */

/* CGame::setupResources() */

void CGame::setupResources(void)

{
  return;
}



/* address=005566c0
   symbol=CGame::createResourceListener */

/* CGame::createResourceListener() */

void CGame::createResourceListener(void)

{
  return;
}



/* address=005566d0
   symbol=CGame::loadResources */

/* CGame::loadResources() */

void CGame::loadResources(void)

{
  return;
}



/* address=005566e0
   symbol=CGame::destroyMasterResourceManager */

/* CGame::destroyMasterResourceManager() */

void __thiscall CGame::destroyMasterResourceManager(CGame *this)

{
  if (*(long **)(this + 0x1d8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1d8) + 8))();
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  return;
}



/* address=00556710
   symbol=CGame::destroyGameClient */

/* CGame::destroyGameClient() */

void __thiscall CGame::destroyGameClient(CGame *this)

{
  if (*(long **)(this + 0x98) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x98) + 8))();
    *(undefined8 *)(this + 0x98) = 0;
  }
  return;
}



/* address=00556740
   symbol=CGame::windowResized */

/* non-virtual thunk to CGame::windowResized(Ogre::RenderWindow*) */

void __thiscall CGame::windowResized(CGame *this,RenderWindow *param_1)

{
  windowResized((RenderWindow *)(this + -0x18));
  return;
}



/* address=00556750
   symbol=CGame::windowResized */

/* CGame::windowResized(Ogre::RenderWindow*) */

void CGame::windowResized(RenderWindow *param_1)

{
  return;
}



/* address=00556760
   symbol=CGame::getGameCamera */

/* non-virtual thunk to CGame::getGameCamera() */

void __thiscall CGame::getGameCamera(CGame *this)

{
  getGameCamera(this + -0x20);
  return;
}



/* address=00556770
   symbol=CGame::getGameCamera */

/* CGame::getGameCamera() */

undefined8 __thiscall CGame::getGameCamera(CGame *this)

{
  undefined8 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x38) != 0) {
    uVar1 = *(undefined8 *)(*(long *)(this + 0x38) + 0x10);
  }
  return uVar1;
}



/* address=00556790
   symbol=CGame::setupForEditor */

/* CGame::setupForEditor(void*, void*) */

undefined4 __thiscall CGame::setupForEditor(CGame *this,void *param_1,void *param_2)

{
  Viewport *pVVar1;
  undefined8 uVar2;
  long lVar3;
  undefined4 uVar4;
  uint uVar5;
  CEditor *this_00;
  void *pvVar6;
  ulong uVar7;
  uint uVar8;

  *(void **)(this + 0xa0) = param_2;
  *(void **)(this + 0xa8) = param_1;
  CEditor::removeFlag(gEditor,1);
  uVar4 = (**(code **)(*(long *)this + 0x60))(this,1);
  pVVar1 = *(Viewport **)(this + 0x78);
  this_00 = (CEditor *)CEditor::getSingleton();
  CEditor::InitEditor(this_00,(iEditorResourceManager *)(this + 0x20),pVVar1);
  uVar2 = *(undefined8 *)(this + 0x98);
  lVar3 = *(long *)(gEditor + 0x128);
  uVar5 = *(uint *)(lVar3 + 0x30);
  if (uVar5 < *(uint *)(lVar3 + 0x34)) {
    pvVar6 = *(void **)(lVar3 + 0x28);
  }
  else if (*(long *)(lVar3 + 0x28) == 0) {
    *(uint *)(lVar3 + 0x34) = *(uint *)(lVar3 + 0x38);
    pvVar6 = operator_new__((ulong)*(uint *)(lVar3 + 0x38) << 3);
    *(void **)(lVar3 + 0x28) = pvVar6;
    uVar5 = *(uint *)(lVar3 + 0x30);
  }
  else {
    uVar8 = *(uint *)(lVar3 + 0x34) + *(int *)(lVar3 + 0x38);
    pvVar6 = operator_new__((ulong)uVar8 << 3);
    if (*(int *)(lVar3 + 0x34) != 0) {
      uVar5 = 0;
      do {
        uVar7 = (ulong)uVar5;
        uVar5 = uVar5 + 1;
        *(undefined8 *)((long)pvVar6 + uVar7 * 8) =
             *(undefined8 *)(*(long *)(lVar3 + 0x28) + uVar7 * 8);
      } while (uVar5 < *(uint *)(lVar3 + 0x34));
    }
    if (*(void **)(lVar3 + 0x28) != (void *)0x0) {
      operator_delete__(*(void **)(lVar3 + 0x28));
    }
    uVar5 = *(uint *)(lVar3 + 0x30);
    *(void **)(lVar3 + 0x28) = pvVar6;
    *(uint *)(lVar3 + 0x34) = uVar8;
  }
  *(undefined8 *)((long)pvVar6 + (ulong)uVar5 * 8) = uVar2;
  *(int *)(lVar3 + 0x30) = *(int *)(lVar3 + 0x30) + 1;
  return uVar4;
}



/* address=005568a0
   symbol=CGame::editorUpdateSceneOnce */

/* non-virtual thunk to CGame::editorUpdateSceneOnce(int) */

void __thiscall CGame::editorUpdateSceneOnce(CGame *this,int param_1)

{
  editorUpdateSceneOnce((int)this + -0x20);
  return;
}



/* address=005568b0
   symbol=CGame::editorUpdateSceneOnce */

/* CGame::editorUpdateSceneOnce(int) */

void CGame::editorUpdateSceneOnce(int param_1)

{
  undefined4 in_register_0000003c;

  if (*(long *)(CONCAT44(in_register_0000003c,param_1) + 0x40) != 0) {
    Ogre::Root::renderOneFrame();
    return;
  }
  return;
}



/* address=005568d0
   symbol=CGame::postViewportUpdate */

/* non-virtual thunk to CGame::postViewportUpdate(Ogre::RenderTargetViewportEvent const&) */

void __thiscall CGame::postViewportUpdate(CGame *this,RenderTargetViewportEvent *param_1)

{
  postViewportUpdate(this + -0x30,param_1);
  return;
}



/* address=005568e0
   symbol=CGame::postViewportUpdate */

/* CGame::postViewportUpdate(Ogre::RenderTargetViewportEvent const&) */

void __thiscall CGame::postViewportUpdate(CGame *this,RenderTargetViewportEvent *param_1)

{
  CLevel *this_00;
  long *plVar1;
  long lVar2;

  if (*(long *)param_1 != *(long *)(this + 0x78)) {
    return;
  }
  (**(code **)(**(long **)(this + 0x50) + 0x7f0))(*(long **)(this + 0x50),7);
  if ((*(long *)(this + 0x98) != 0) &&
     (this_00 = *(CLevel **)(*(long *)(this + 0x98) + 0x70), this_00 != (CLevel *)0x0)) {
    CLevel::setLightStaticGeometryVisible(this_00,true);
  }
  Ogre::Viewport::getCamera();
  plVar1 = (long *)Ogre::Camera::getSceneManager();
  lVar2 = (**(code **)(*plVar1 + 0x540))(plVar1);
  *(undefined8 *)(lVar2 + 0x40) = 0;
  return;
}



/* address=00556980
   symbol=CGame::preViewportUpdate */

/* non-virtual thunk to CGame::preViewportUpdate(Ogre::RenderTargetViewportEvent const&) */

void __thiscall CGame::preViewportUpdate(CGame *this,RenderTargetViewportEvent *param_1)

{
  preViewportUpdate(this + -0x30,param_1);
  return;
}



/* address=00556990
   symbol=CGame::preViewportUpdate */

/* CGame::preViewportUpdate(Ogre::RenderTargetViewportEvent const&) */

void __thiscall CGame::preViewportUpdate(CGame *this,RenderTargetViewportEvent *param_1)

{
  CLevel *this_00;
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  long *plVar5;
  long lVar6;
  CGameUI *this_01;
  float fVar7;
  float fVar8;
  float fVar9;

  if (*(long *)param_1 != *(long *)(this + 0x78)) {
    return;
  }
  if (*(long *)param_1 != 0) {
    lVar6 = *(long *)(this + 0x98);
    if ((lVar6 != 0) && (*(CGameUI **)(lVar6 + 0x78) != (CGameUI *)0x0)) {
      cVar1 = CGameUI::bothCovered(*(CGameUI **)(lVar6 + 0x78));
      if (cVar1 == '\0') {
        if (*(long *)(this + 0x78) == 0) goto LAB_00556b7a;
        lVar6 = *(long *)(this + 0x98);
        goto LAB_00556b32;
      }
LAB_00556a03:
      uVar2 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
      if (*(CGameUI **)(*(long *)(this + 0x98) + 0x78) == (CGameUI *)0x0) {
        fVar7 = DAT_00fa4800 / (float)uVar2;
LAB_00556bac:
        fVar9 = (float)uVar2;
        fVar8 = 0.0;
      }
      else {
        fVar7 = (float)CGameUI::rightScreenEdge(*(CGameUI **)(*(long *)(this + 0x98) + 0x78));
        fVar9 = (float)uVar2;
        fVar7 = fVar7 / fVar9;
        if (*(CGameUI **)(*(long *)(this + 0x98) + 0x78) == (CGameUI *)0x0) goto LAB_00556bac;
        fVar8 = (float)CGameUI::leftScreenEdge(*(CGameUI **)(*(long *)(this + 0x98) + 0x78));
      }
      Ogre::Viewport::setDimensions(fVar8 / fVar9,0.0,fVar7 - fVar8 / fVar9,DAT_00fa47fc);
      goto LAB_00556a9d;
    }
LAB_00556b32:
    if (lVar6 != 0) {
      this_01 = (CGameUI *)0x0;
      if (*(CGameUI **)(lVar6 + 0x78) != (CGameUI *)0x0) {
        cVar1 = CGameUI::rightCovered(*(CGameUI **)(lVar6 + 0x78));
        if (cVar1 != '\0') goto LAB_00556a03;
        if ((*(long *)(this + 0x78) == 0) || (*(long *)(this + 0x98) == 0)) goto LAB_00556b7a;
        this_01 = *(CGameUI **)(*(long *)(this + 0x98) + 0x78);
      }
      if ((this_01 != (CGameUI *)0x0) && (cVar1 = CGameUI::leftCovered(this_01), cVar1 != '\0'))
      goto LAB_00556a03;
    }
  }
LAB_00556b7a:
  Ogre::Viewport::setDimensions(0.0,0.0,DAT_00fa47fc,DAT_00fa47fc);
LAB_00556a9d:
  iVar3 = Ogre::Viewport::getActualHeight();
  iVar4 = Ogre::Viewport::getActualWidth();
  CCameraControl::setAspectRatio
            ((CCameraControl *)(float)iVar4,(float)iVar3,*(undefined8 *)(this + 0x38),0);
  (**(code **)(**(long **)(this + 0x50) + 0x7f0))();
  if ((*(long *)(this + 0x98) != 0) &&
     (this_00 = *(CLevel **)(*(long *)(this + 0x98) + 0x70), this_00 != (CLevel *)0x0)) {
    CLevel::setLightStaticGeometryVisible(this_00,false);
  }
  Ogre::Viewport::getCamera();
  plVar5 = (long *)Ogre::Camera::getSceneManager();
  lVar6 = (**(code **)(*plVar5 + 0x540))(plVar5);
  *(CGame **)(lVar6 + 0x40) = this + 0x28;
  return;
}



/* address=00556bc0
   symbol=CGame::frameEnded */

/* non-virtual thunk to CGame::frameEnded(Ogre::FrameEvent const&) */

void __thiscall CGame::frameEnded(CGame *this,FrameEvent *param_1)

{
  frameEnded(this + -0x10,param_1);
  return;
}



/* address=00556bd0
   symbol=CGame::frameEnded */

/* CGame::frameEnded(Ogre::FrameEvent const&) */

undefined8 __thiscall CGame::frameEnded(CGame *this,FrameEvent *param_1)

{
  int iVar1;
  uint uVar2;
  CGameUI *this_00;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  SceneNode *pSVar7;
  undefined8 uVar8;
  long lVar9;
  float fVar10;
  float fVar11;
  CCameraControl *pCVar12;
  undefined8 local_68;
  undefined4 local_60;
  string local_58 [16];
  STRINGS local_48 [8];
  int local_40;
  int local_3c [3];

  if ((*(long *)(this + 0x1d8) != 0) && (*(char *)(*(long *)(this + 0x1d8) + 0xc0) != '\0')) {
    return 1;
  }
  iVar4 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN)
  ;
  if ((((iVar4 == 0) &&
       (iVar4 = CDynamicPropertyFile::GetInt
                          (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH),
       iVar4 == gLastWidth)) &&
      (iVar4 = CDynamicPropertyFile::GetInt
                         (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT),
      iVar4 == gLastHeight)) &&
     (iVar4 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN),
     iVar4 == gLastFullscreen)) {
    SDL_GetWindowSize(*(undefined8 *)(this + 0x2a0),&local_40,local_3c);
    iVar1 = local_3c[0];
    iVar4 = local_40;
    iVar5 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
    iVar6 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
    if (((iVar4 != iVar5) || (iVar1 != iVar6)) && ((0x1ff < iVar4 && (0x17f < iVar1)))) {
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,iVar4);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,iVar1);
      GRecreateUI = '\x01';
      gLastWidth = iVar4;
      gLastHeight = iVar1;
      GResizeWidth = iVar4;
      GResizeHeight = iVar1;
    }
  }
  if (gLastWidth != 0) {
    lVar9 = *(long *)(this + 0x98);
    if (*(char *)(lVar9 + 0x103d) != '\0') goto LAB_00556c75;
    iVar4 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
    if (((iVar4 != gLastWidth) ||
        (iVar4 = CDynamicPropertyFile::GetInt
                           (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT),
        iVar4 != gLastHeight)) ||
       (iVar4 = CDynamicPropertyFile::GetInt
                          (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN),
       iVar4 != gLastFullscreen)) {
      GResizeWidth = CDynamicPropertyFile::GetInt
                               (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
      GResizeHeight =
           CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
      local_3c[0] = GResizeWidth;
      local_40 = GResizeHeight;
      CSettings::findClosestResolution
                (*(CSettings **)(this + 0xb8),GResizeWidth,GResizeHeight,local_3c,&local_40);
      GResizeWidth = local_3c[0];
      GResizeHeight = local_40;
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
      iVar4 = GResizeWidth;
      *(int *)(this + 0xb0) = GResizeWidth;
      *(int *)(this + 0xb4) = GResizeHeight;
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,iVar4);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,*(int *)(this + 0xb4))
      ;
      iVar4 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
      if (iVar4 == 0) {
        SDL_SetWindowGrab(*(undefined8 *)(this + 0x2a0),0);
        SDL_SetWindowFullscreen(*(undefined8 *)(this + 0x2a0),0);
        SDL_SetWindowSize(*(undefined8 *)(this + 0x2a0),*(undefined4 *)(this + 0xb0),
                          *(undefined4 *)(this + 0xb4));
      }
      else {
        SDL_SetWindowFullscreen(*(undefined8 *)(this + 0x2a0),0);
        SDL_SetWindowPosition(*(undefined8 *)(this + 0x2a0),0,0);
        SDL_SetWindowSize(*(undefined8 *)(this + 0x2a0),*(undefined4 *)(this + 0xb0),
                          *(undefined4 *)(this + 0xb4));
        SDL_SetWindowFullscreen(*(undefined8 *)(this + 0x2a0),1);
        SDL_SetWindowGrab(*(undefined8 *)(this + 0x2a0),1);
      }
      (**(code **)(**(long **)(this + 0x80) + 0x1b0))
                (*(long **)(this + 0x80),*(undefined4 *)(this + 0xb0),*(undefined4 *)(this + 0xb4));
      (**(code **)(**(long **)(this + 0x80) + 0x1b8))();
      fVar10 = (float)*(uint *)(this + 0xb4) / DAT_00fa4804;
      fVar11 = (float)*(uint *)(this + 0xb0) * DAT_00fa4808;
      STRINGS::GetValueAsString(local_48,fVar10);
                    /* try { // try from 00556e8b to 00556e8f has its CatchHandler @ 00557461 */
      std::operator+((char *)local_58,(string *)"Fullscreen Switch Setting YRatio - ");
                    /* try { // try from 00556e90 to 00556ea6 has its CatchHandler @ 00557474 */
      uVar8 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar8,local_58,3,0);
                    /* try { // try from 00556eaa to 00556eae has its CatchHandler @ 00557461 */
      std::string::~string(local_58);
      std::string::~string((string *)local_48);
      CDynamicPropertyFile::SetFloat
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_XRATIO,fVar11);
      CDynamicPropertyFile::SetFloat
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_YRATIO,fVar10);
      fVar10 = (float)CDynamicPropertyFile::GetFloat
                                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_SOUNDVOLUME);
      fVar11 = (float)CDynamicPropertyFile::GetFloat
                                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_MUSICVOLUME);
      iVar4 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_SOUNDMUTE);
      CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_MUSICMUTE);
      lVar9 = (**(code **)(*(long *)this + 0x30))(this);
      if (lVar9 != 0) {
        bVar3 = (bool)(**(code **)(*(long *)this + 0x30))(this);
        CSoundManager::updateAudioLevels(fVar10,fVar11,bVar3,iVar4 != 0);
      }
      gLastWidth = CDynamicPropertyFile::GetInt
                             (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
      gLastHeight = CDynamicPropertyFile::GetInt
                              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
      gLastFullscreen =
           CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
      GRecreateUI = '\x01';
      lVar9 = *(long *)(this + 0x98);
      goto LAB_00556c75;
    }
    if (GRecreateUI != '\0') {
      if (*(long *)(this + 0x98) == 0) {
        return 1;
      }
      *(int *)(this + 0xb0) = GResizeWidth;
      *(int *)(this + 0xb4) = GResizeHeight;
      iVar4 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
      if (iVar4 == 0) {
        SDL_GetWindowSize(*(undefined8 *)(this + 0x2a0),&local_40,local_3c);
        *(int *)(this + 0xb0) = local_40;
        *(int *)(this + 0xb4) = local_3c[0];
        iVar4 = local_40;
      }
      else {
        iVar4 = *(int *)(this + 0xb0);
      }
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,iVar4);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,*(int *)(this + 0xb4))
      ;
      if (*(CGameClient **)(this + 0x98) != (CGameClient *)0x0) {
        CGameClient::updateScreenInfo
                  (*(CGameClient **)(this + 0x98),*(void **)(this + 0xa0),*(int *)(this + 0xb0),
                   *(int *)(this + 0xb4));
      }
      lVar9 = *(long *)(this + 0x38);
      if (lVar9 != 0) {
        fVar10 = (float)*(uint *)(this + 0xb4);
        pCVar12._0_4_ = (CCameraControl *)(float)*(uint *)(this + 0xb0);
        CCameraControl::setAspectRatio(pCVar12._0_4_,fVar10,lVar9,0);
        CCameraControl::setAspectRatio(pCVar12._0_4_,fVar10,lVar9,1);
        CCameraControl::setAspectRatio(pCVar12._0_4_,fVar10,lVar9,2);
      }
      fVar10 = (float)*(uint *)(this + 0xb4) / DAT_00fa4804;
      CDynamicPropertyFile::SetFloat
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_XRATIO,
                 (float)*(uint *)(this + 0xb0) * DAT_00fa4808);
      CDynamicPropertyFile::SetFloat
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_YRATIO,fVar10);
      if ((*(long *)(this + 0x98) != 0) &&
         (this_00 = *(CGameUI **)(*(long *)(this + 0x98) + 0x78), this_00 != (CGameUI *)0x0)) {
        CGameUI::setLoadingVisible(this_00,true);
      }
      GRecreateUI = '\0';
      CGameClient::rescaleUI(*(CGameClient **)(this + 0x98));
      uVar2 = *(uint *)(this + 0xb4);
      iVar4 = *(int *)(this + 0xb0);
      lVar9 = CGameUI::getSingleton();
      if (lVar9 != 0) {
        CSplash::findCenterForWindow(0x1424b60,iVar4,(int *)(ulong)uVar2,local_3c);
        fVar11 = (float)local_40;
        fVar10 = (float)local_3c[0];
        CEGUI::System::getSingleton();
        CEGUI::System::injectMousePosition(fVar10,fVar11);
        CEGUI::System::getSingleton();
        CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
      }
      lVar9 = CMasterResourceManager::getSingleton();
      *(undefined1 *)(lVar9 + 0xc0) = 0;
      if (gFailWidth != 0) {
        CDynamicPropertyFile::SetInt
                  (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,gFailWidth);
        CDynamicPropertyFile::SetInt
                  (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,gFailHeight);
        gFailWidth = 0;
        gFailHeight = 0;
        GResizing = 1;
      }
    }
  }
  lVar9 = *(long *)(this + 0x98);
LAB_00556c75:
  if ((lVar9 != 0) && (*(long *)(this + 0xc0) != 0)) {
    local_68 = *(undefined8 *)(lVar9 + 0x2c0);
    fVar10 = *(float *)(param_1 + 4);
    local_60 = *(undefined4 *)(lVar9 + 0x2c8);
    pSVar7 = (SceneNode *)(**(code **)(**(long **)(this + 0x50) + 0x250))();
    CSoundManager::update(*(CSoundManager **)(this + 0xc0),pSVar7,(Vector3 *)&local_68,fVar10);
  }
  return 1;
}



/* address=00557490
   symbol=CGame::update */

/* CGame::update(float, float, bool) */

undefined8 __thiscall CGame::update(CGame *this,float param_1,float param_2,bool param_3)

{
  CGame *pCVar1;
  CGame *pCVar2;
  void *pvVar3;
  char cVar4;
  CGame CVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  _List_node_base *p_Var9;
  CGame *pCVar10;
  ulong uVar11;
  ulong uVar12;
  CGameClient *this_00;
  CGameUI *this_01;
  float fVar13;

  if (0 < g_ResetFrames) {
    g_ResetFrames = g_ResetFrames + -1;
  }
  gfLastTimeElapsed = param_1;
  iVar6 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RENDERBEHIND);
  this[600] = (CGame)(iVar6 != 0);
  if (GResizing == '\0') {
    gLastWidth = CDynamicPropertyFile::GetInt
                           (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
    gLastHeight = CDynamicPropertyFile::GetInt
                            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
    gLastFullscreen =
         CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
    this_00 = *(CGameClient **)(this + 0x98);
  }
  else {
    this_00 = *(CGameClient **)(this + 0x98);
  }
  if (this_00 == (CGameClient *)0x0) {
    return 1;
  }
  if (DAT_00fa47f8 < param_1) {
    *(float *)(this + 0x254) = param_1 + *(float *)(this + 0x254);
    p_Var9 = operator_new(0x18);
    if (p_Var9 != (_List_node_base *)0xfffffffffffffff0) {
      *(float *)(p_Var9 + 0x10) = param_1;
    }
    pCVar1 = this + 0x240;
    std::_List_node_base::hook(p_Var9);
    uVar11 = 0;
    pCVar10 = *(CGame **)(this + 0x240);
    for (pCVar2 = pCVar10; pCVar1 != pCVar2; pCVar2 = *(CGame **)pCVar2) {
      uVar11 = uVar11 + 1;
    }
    if (*(uint *)(this + 0x250) <= uVar11) {
      pvVar3 = *(void **)(this + 0x248);
      *(float *)(this + 0x254) = *(float *)(this + 0x254) - *(float *)((long)pvVar3 + 0x10);
      std::_List_node_base::unhook();
      operator_delete(pvVar3);
      pCVar10 = *(CGame **)(this + 0x240);
    }
    uVar11 = 0;
    uVar12 = 0;
    if (pCVar10 == pCVar1) {
LAB_00557734:
      fVar13 = (float)(long)uVar12;
    }
    else {
      do {
        pCVar10 = *(CGame **)pCVar10;
        uVar12 = uVar11 + 1;
        uVar11 = uVar12;
      } while (pCVar10 != pCVar1);
      if (-1 < (long)uVar12) goto LAB_00557734;
      fVar13 = (float)uVar12;
    }
    CDynamicPropertyFile::SetFloat
              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_AVERAGE_FPS,
               DAT_00fa47fc / (*(float *)(this + 0x254) / fVar13));
    this_00 = *(CGameClient **)(this + 0x98);
  }
  cVar4 = CGameClient::processInput(this_00,*(void **)(this + 0xa0),param_1,(bool)this[200]);
  if (cVar4 == '\0') {
    return 0;
  }
  CGameClient::update(*(CGameClient **)(this + 0x98),param_1,*(RenderWindow **)(this + 0x80),param_2
                      ,param_3);
  if (*(char *)(*(long *)(this + 0x98) + 0x103d) != '\0') {
    this[0xcb] = (CGame)0x1;
    return 0;
  }
  if (*(char *)(*(long *)(this + 0x98) + 0x103c) != '\0') {
    CSteamStats::getSingleton();
    CSteamStats::forceStatsToSave();
    return 0;
  }
  this[0xc9] = (CGame)0x0;
  uVar7 = SDL_GetWindowFlags(*(undefined8 *)(this + 0x2a0));
  if ((uVar7 & 0x240) == 0x200) {
    lVar8 = *(long *)(this + 0x98);
    if (*(CGameUI **)(lVar8 + 0x78) == (CGameUI *)0x0) {
LAB_0055787d:
      CVar5 = (CGame)0x0;
    }
    else {
      cVar4 = CGameUI::bothCovered(*(CGameUI **)(lVar8 + 0x78));
      if (cVar4 == '\0') {
        lVar8 = *(long *)(this + 0x98);
        if (*(CGameUI **)(lVar8 + 0x78) != (CGameUI *)0x0) {
          cVar4 = CGameUI::modalDialogOpenPartial(*(CGameUI **)(lVar8 + 0x78));
          if (cVar4 != '\0') goto LAB_00557829;
          lVar8 = *(long *)(this + 0x98);
        }
        goto LAB_0055787d;
      }
LAB_00557829:
      lVar8 = *(long *)(this + 0x98);
      CVar5 = (CGame)0x1;
    }
    this[0xc9] = CVar5;
    this_01 = *(CGameUI **)(lVar8 + 0x78);
    if (this_01 == (CGameUI *)0x0) goto LAB_00557800;
    if (this_01[0x1999] != (CGameUI)0x0) {
      this[0xc9] = (CGame)0x1;
      goto LAB_005575bd;
    }
  }
  else {
    lVar8 = *(long *)(this + 0x98);
    this[0xc9] = (CGame)0x1;
LAB_005575bd:
    this_01 = *(CGameUI **)(lVar8 + 0x78);
    if (this_01 == (CGameUI *)0x0) {
LAB_00557800:
      CVar5 = (CGame)0x0;
      goto LAB_005575cf;
    }
  }
  CVar5 = (CGame)CGameUI::getUIIsInCinematic(this_01);
LAB_005575cf:
  this[0xca] = CVar5;
  lVar8 = CSteamStats::getSingleton();
  if ((lVar8 != 0) && (lVar8 = CAchievements::getSingleton(), lVar8 != 0)) {
    CSteamStats::getSingleton();
    CSteamStats::update(param_1);
    CAchievements::getSingleton();
    CAchievements::update(param_1);
    return 1;
  }
  return 1;
}



/* address=00557890
   symbol=CGame::frameRenderingQueued */

/* non-virtual thunk to CGame::frameRenderingQueued(Ogre::FrameEvent const&) */

void __thiscall CGame::frameRenderingQueued(CGame *this,FrameEvent *param_1)

{
  frameRenderingQueued((FrameEvent *)(this + -0x10));
  return;
}



/* address=005578a0
   symbol=CGame::frameRenderingQueued */

/* CGame::frameRenderingQueued(Ogre::FrameEvent const&) */

undefined8 CGame::frameRenderingQueued(FrameEvent *param_1)

{
  CGameClient *this;
  char cVar1;

  if (*(long **)(param_1 + 0x80) != (long *)0x0) {
    cVar1 = (**(code **)(**(long **)(param_1 + 0x80) + 0x1d8))();
    if (cVar1 == '\0') {
      this = *(CGameClient **)(param_1 + 0x98);
      if ((this != (CGameClient *)0x0) && (this[0x38d4] != (CGameClient)0x0)) {
        CGameClient::clearSceneManagerPassMaps(this);
        return 1;
      }
      return 1;
    }
  }
  return 0;
}



/* address=005578f0
   symbol=CGame::frameStarted */

/* non-virtual thunk to CGame::frameStarted(Ogre::FrameEvent const&) */

void __thiscall CGame::frameStarted(CGame *this,FrameEvent *param_1)

{
  frameStarted(this + -0x10,param_1);
  return;
}



/* address=00557900
   symbol=CGame::frameStarted */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGame::frameStarted(Ogre::FrameEvent const&) */

undefined8 __thiscall CGame::frameStarted(CGame *this,FrameEvent *param_1)

{
  CGameClient *pCVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  float fVar5;
  double dVar6;

  if ((*(long *)(this + 0x1d8) == 0) || (*(char *)(*(long *)(this + 0x1d8) + 0xc0) == '\0')) {
    if ((frameStarted(Ogre::FrameEvent_const&)::g_LastTime == '\0') &&
       (iVar3 = __cxa_guard_acquire(&frameStarted(Ogre::FrameEvent_const&)::g_LastTime), iVar3 != 0)
       ) {
                    /* try { // try from 00557a09 to 00557a0d has its CatchHandler @ 00557aea */
      frameStarted(Ogre::FrameEvent_const&)::g_LastTime = Ogre::Timer::getMilliseconds();
      __cxa_guard_release(&frameStarted(Ogre::FrameEvent_const&)::g_LastTime);
    }
    fVar5 = *(float *)(param_1 + 4);
    if (DAT_00fa480c <= *(float *)(param_1 + 4)) {
      fVar5 = DAT_00fa480c;
    }
    cVar2 = update(this,fVar5,0.0,true);
    if (cVar2 == '\0') {
      pCVar1 = *(CGameClient **)(this + 0x98);
      if ((pCVar1 != (CGameClient *)0x0) && (pCVar1[0x38d4] != (CGameClient)0x0)) {
        CGameClient::clearSceneManagerPassMaps(pCVar1);
        return 0;
      }
      return 0;
    }
    lVar4 = Ogre::Timer::getMilliseconds();
    g_Frames = g_Frames + 1;
    if (1000 < (ulong)(lVar4 - frameStarted(Ogre::FrameEvent_const&)::g_LastTime)) {
      iVar3 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NUM_TICKS_PER_SECOND);
      dVar6 = (double)(ulong)(lVar4 - frameStarted(Ogre::FrameEvent_const&)::g_LastTime) /
              _DAT_00fa4840;
      frameStarted(Ogre::FrameEvent_const&)::g_LastTime = lVar4;
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NUM_TICKS_PER_SECOND,g_Frames);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_CURRENT_FPS,
                 (int)((double)iVar3 / dVar6));
      CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_UPDATE_PERF,1);
      g_Frames = 0;
    }
    pCVar1 = *(CGameClient **)(this + 0x98);
    if ((pCVar1 != (CGameClient *)0x0) && (pCVar1[0x38d4] != (CGameClient)0x0)) {
      CGameClient::clearSceneManagerPassMaps(pCVar1);
    }
  }
  return 1;
}



/* address=00557b00
   symbol=CGame::windowFocusChange */

/* non-virtual thunk to CGame::windowFocusChange(Ogre::RenderWindow*) */

void __thiscall CGame::windowFocusChange(CGame *this,RenderWindow *param_1)

{
  windowFocusChange(this + -0x18,param_1);
  return;
}



/* address=00557b10
   symbol=CGame::windowFocusChange */

/* CGame::windowFocusChange(Ogre::RenderWindow*) */

void __thiscall CGame::windowFocusChange(CGame *this,RenderWindow *param_1)

{
  CGame CVar1;

  if (*(RenderWindow **)(this + 0x80) == param_1) {
    CVar1 = (CGame)(**(code **)(*(long *)*(RenderWindow **)(this + 0x80) + 0xe8))();
    this[200] = CVar1;
  }
  if (*(CGameClient **)(this + 0x98) != (CGameClient *)0x0) {
    CGameClient::setWindowActive(*(CGameClient **)(this + 0x98),(bool)this[200]);
    return;
  }
  return;
}



/* address=00557b60
   symbol=CGame::windowClosed */

/* non-virtual thunk to CGame::windowClosed(Ogre::RenderWindow*) */

void __thiscall CGame::windowClosed(CGame *this,RenderWindow *param_1)

{
  windowClosed((RenderWindow *)(this + -0x18));
  return;
}



/* address=00557b70
   symbol=CGame::windowClosed */

/* CGame::windowClosed(Ogre::RenderWindow*) */

void CGame::windowClosed(RenderWindow *param_1)

{
  long lVar1;
  CGameClient *this;
  char cVar2;

  lVar1 = *(long *)(param_1 + 0x98);
  if ((lVar1 != 0) && (*(int *)(lVar1 + 0x38d0) == 1)) {
    cVar2 = CKeyManager::keyHeld((CKeyManager *)(lVar1 + 0x2d0),0x10);
    if (cVar2 == '\0') {
      cVar2 = (**(code **)(**(long **)(*(long *)(param_1 + 0x98) + 0x58) + 0x48))();
      if (((cVar2 != '\0') &&
          (this = *(CGameClient **)(param_1 + 0x98), *(int *)(this + 0x390c) != 1)) &&
         (*(int *)(*(long *)(this + 0x58) + 0x330) != 0x1f)) {
        CGameClient::killPets(this);
        CGameClient::saveCharacter(*(CGameClient **)(param_1 + 0x98),false,true);
        return;
      }
    }
  }
  return;
}



/* address=00557bf0
   symbol=CGame::createFrameListener */

/* CGame::createFrameListener() */

void __thiscall CGame::createFrameListener(CGame *this)

{
  Ogre::Root::addFrameListener(*(FrameListener **)(this + 0x40));
  return;
}



/* address=00557ef0
   symbol=CGame::WndProc */

/* CGame::WndProc(void*, unsigned int, unsigned int, long) */

undefined8 CGame::WndProc(void *param_1,uint param_2,uint param_3,long param_4)

{
  undefined8 uVar1;

  if (((((param_3 - 0x100 < 2) || (param_3 == 0x104)) || (param_3 == 0x102)) || (param_3 == 0x105))
     && (*(long *)((long)param_1 + 0x98) != 0)) {
    CGameClient::keyEvent((uint)*(long *)((long)param_1 + 0x98),param_3,param_4 & 0xffffffffU);
  }
  if (param_3 == 7) {
LAB_00557fe8:
    if (*(CGameClient **)((long)param_1 + 0x98) == (CGameClient *)0x0) {
      uVar1 = 0;
    }
    else {
      CGameClient::updateCursor(*(CGameClient **)((long)param_1 + 0x98));
      uVar1 = 0;
    }
  }
  else {
    if (param_3 < 8) {
      if (param_3 != 5) goto LAB_00557f56;
      if ((((uint)param_4 < 4) && ((1L << ((byte)(param_4 & 0xffffffffU) & 0x3f) & 0xdU) != 0)) &&
         (*(CGameClient **)((long)param_1 + 0x98) != (CGameClient *)0x0)) {
        CGameClient::updateCursor(*(CGameClient **)((long)param_1 + 0x98));
      }
    }
    else {
      if (param_3 == 0x32) goto LAB_00557fe8;
      if (param_3 == 0x214) {
        if (*(CGameClient **)((long)param_1 + 0x98) == (CGameClient *)0x0) {
          return 1;
        }
        CGameClient::updateCursor(*(CGameClient **)((long)param_1 + 0x98));
        return 1;
      }
LAB_00557f56:
      if (((((param_3 == 0x204) || (param_3 == 0x201)) ||
           (((param_3 == 0x203 ||
             ((((param_3 == 0x207 || (param_3 == 0x209)) || (param_3 == 0x206)) ||
              ((param_3 == 0x205 || (param_3 == 0x202)))))) || (param_3 == 0x20a)))) ||
          (param_3 == 0x208)) && (*(CGameClient **)((long)param_1 + 0x98) != (CGameClient *)0x0)) {
        CGameClient::mouseEvent(*(CGameClient **)((long)param_1 + 0x98),param_3,(uint)param_4);
        return 0xffffffffffffffff;
      }
    }
    uVar1 = 0xffffffffffffffff;
  }
  return uVar1;
}



/* address=005580e0
   symbol=CGame::cleanUpGameObjects */

/* CGame::cleanUpGameObjects() */

void __thiscall CGame::cleanUpGameObjects(CGame *this)

{
  if (*(CMasterResourceManager **)(this + 0x1d8) != (CMasterResourceManager *)0x0) {
    CMasterResourceManager::destroyStash(*(CMasterResourceManager **)(this + 0x1d8));
  }
  (**(code **)(*(long *)this + 0x90))(this);
  destroyMasterResourceManager(this);
  if (*(long **)(this + 0x50) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x50) + 0x368))();
  }
  if (*(long **)(this + 0x48) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x48) + 0x368))();
  }
  if (*(long **)(this + 0x58) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x58) + 0x368))();
  }
  if (*(long **)(this + 0x60) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x60) + 0x368))();
  }
  if (*(long **)(this + 0x68) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x68) + 0x368))();
  }
  if (*(long **)(this + 0x70) != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00558177. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(long **)(this + 0x70) + 0x368))();
    return;
  }
  return;
}



/* address=00558190
   symbol=CGame::shutdownForEditor */

/* CGame::shutdownForEditor() */

void __thiscall CGame::shutdownForEditor(CGame *this)

{
  CEditor *this_00;

  this_00 = (CEditor *)CEditor::getSingleton();
  CEditor::releaseResources(this_00);
  cleanUpGameObjects(this);
  return;
}



/* address=0055f660
   symbol=CGame::createGameClient */

/* CGame::createGameClient() */

void __thiscall CGame::createGameClient(CGame *this)

{
  CGameClient *this_00;
  undefined8 uVar1;

  this_00 = (CGameClient *)Ogre::NedAllocImpl::allocBytes(0x3910,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0055f6c2 to 0055f6c6 has its CatchHandler @ 0055f711 */
  CGameClient::CGameClient
            (this_00,*(CSettings **)(this + 0xb8),*(CMasterResourceManager **)(this + 0x1d8),
             *(RenderWindow **)(this + 0x80),*(Root **)(this + 0x40),
             *(CCameraControl **)(this + 0x38),*(SceneManager **)(this + 0x50),
             *(SceneManager **)(this + 0x58),*(SceneManager **)(this + 0x60),
             *(CSoundManager **)(this + 0xc0));
  *(CGameClient **)(this + 0x98) = this_00;
  CGameClient::create(this_00);
  uVar1 = 0;
  if (*(CGameClient **)(this + 0x98) != (CGameClient *)0x0) {
    CGameClient::updateScreenInfo
              (*(CGameClient **)(this + 0x98),*(void **)(this + 0xa0),*(int *)(this + 0xb0),
               *(int *)(this + 0xb4));
    uVar1 = *(undefined8 *)(this + 0x98);
  }
  *(undefined8 *)(this + 0x2b0) = uVar1;
  return;
}



/* address=005602d0
   symbol=CGame::checkCapabilities */

/* CGame::checkCapabilities(Ogre::RenderSystem*) */

void __thiscall CGame::checkCapabilities(CGame *this,RenderSystem *param_1)

{
  long lVar1;
  _Rb_tree_node *p_Var2;
  _Rb_tree_node *p_Var3;
  uint uVar4;
  _Rb_tree<std::string,std::string,std::_Identity<std::string>,std::less<std::string>,std::allocator<std::string>>
  a_Stack_48 [8];
  undefined4 local_40 [2];
  _Rb_tree_node *local_38;
  _Rb_tree_node *local_30;
  _Rb_tree_node *local_28;
  undefined8 local_20;

  lVar1 = *(long *)(param_1 + 0x398);
  if (lVar1 != 0) {
    local_30 = (_Rb_tree_node *)local_40;
    local_20 = 0;
    local_40[0] = 0;
    local_38 = (_Rb_tree_node *)0x0;
    local_28 = local_30;
    if (*(_Rb_tree_node **)(lVar1 + 0x80) != (_Rb_tree_node *)0x0) {
                    /* try { // try from 00560323 to 00560327 has its CatchHandler @ 00560416 */
      local_38 = (_Rb_tree_node *)
                 std::
                 _Rb_tree<std::string,std::string,std::_Identity<std::string>,std::less<std::string>,std::allocator<std::string>>
                 ::_M_copy(a_Stack_48,*(_Rb_tree_node **)(lVar1 + 0x80),local_30);
      p_Var3 = local_38;
      do {
        local_30 = p_Var3;
        p_Var2 = local_38;
        p_Var3 = *(_Rb_tree_node **)(local_30 + 0x10);
      } while (*(_Rb_tree_node **)(local_30 + 0x10) != (_Rb_tree_node *)0x0);
      do {
        local_28 = p_Var2;
        p_Var2 = *(_Rb_tree_node **)(local_28 + 0x18);
      } while (*(_Rb_tree_node **)(local_28 + 0x18) != (_Rb_tree_node *)0x0);
      local_20 = *(undefined8 *)(lVar1 + 0x98);
    }
                    /* try { // try from 00560374 to 005603c5 has its CatchHandler @ 005603fe */
    CDynamicPropertyFile::SetInt
              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_ALLOW_HWSKINNING,0);
    uVar4 = *(uint *)(lVar1 + 0x24);
    if ((uVar4 & 0x40000) == 0) {
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_SHADOWS_ENABLED,0);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_LIGHTING_ENABLED,0);
      uVar4 = *(uint *)(lVar1 + 0x24);
    }
    if ((uVar4 & 0x10) == 0) {
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RIMLIGHTS_ENABLED,0);
      uVar4 = *(uint *)(lVar1 + 0x24);
    }
    if ((uVar4 & 0x200) == 0) {
                    /* try { // try from 005603f7 to 005603fb has its CatchHandler @ 005603fe */
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_ALLOW_HWSKINNING,0);
    }
                    /* try { // try from 005603d6 to 005603da has its CatchHandler @ 0056041e */
    std::
    _Rb_tree<std::string,std::string,std::_Identity<std::string>,std::less<std::string>,std::allocator<std::string>>
    ::_M_erase(a_Stack_48,local_38);
  }
  return;
}



/* address=00560760
   symbol=CGame::~CGame */

/* WARNING: Removing unreachable block (ram,0x00560be8) */
/* WARNING: Removing unreachable block (ram,0x00560c2c) */
/* WARNING: Removing unreachable block (ram,0x00560bdd) */
/* CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  allocator *paVar1;
  int iVar2;
  code *pcVar3;
  int *piVar4;
  Root *this_00;
  CGame *pCVar5;
  CGame *pCVar6;
  long local_48;
  allocator local_39 [9];

  *(undefined ***)this = &PTR__CGame_00fa3e90;
  *(undefined ***)(this + 0x10) = &PTR_frameStarted_00fa3fa0;
  *(undefined ***)(this + 0x18) = &PTR__CGame_00fa3fd8;
  *(undefined ***)(this + 0x20) = &PTR__CGame_00fa4020;
  *(undefined ***)(this + 0x28) = &PTR__CGame_00fa4088;
  *(undefined ***)(this + 0x30) = &PTR__CGame_00fa40b0;
  if (*(long **)(this + 0xb8) != (long *)0x0) {
    pcVar3 = *(code **)(**(long **)(this + 0xb8) + 0x10);
                    /* try { // try from 005607c0 to 005607c4 has its CatchHandler @ 00560b70 */
    std::wstring::wstring((wstring_conflict *)&local_48,L"",local_39);
                    /* try { // try from 005607cf to 005607d1 has its CatchHandler @ 00560c1c */
    (*pcVar3)(*(undefined8 *)(this + 0xb8),&local_48);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(local_48 + -8);
      iVar2 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
  }
  if (*(RenderWindow **)(this + 0x80) != (RenderWindow *)0x0) {
                    /* try { // try from 00560805 to 0056094d has its CatchHandler @ 00560b2c */
    Ogre::WindowEventUtilities::removeWindowEventListener
              (*(RenderWindow **)(this + 0x80),(WindowEventListener *)(this + 0x18));
    windowClosed((RenderWindow *)this);
  }
  if (*(long *)(this + 0x220) != 0) {
    piVar4 = *(int **)(this + 0x228);
    if ((piVar4 != (int *)0x0) && (iVar2 = *piVar4, *piVar4 = iVar2 + -1, iVar2 + -1 == 0)) {
      (**(code **)(*(long *)(this + 0x218) + 0x10))(this + 0x218);
    }
    *(undefined8 *)(this + 0x220) = 0;
    *(undefined8 *)(this + 0x228) = 0;
  }
  if (*(long *)(this + 0x200) != 0) {
    piVar4 = *(int **)(this + 0x208);
    if ((piVar4 != (int *)0x0) && (iVar2 = *piVar4, *piVar4 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 00560a91 to 00560aba has its CatchHandler @ 00560b2c */
      (**(code **)(*(long *)(this + 0x1f8) + 0x10))(this + 0x1f8);
    }
    *(undefined8 *)(this + 0x200) = 0;
    *(undefined8 *)(this + 0x208) = 0;
  }
  if (*(long **)(this + 0x90) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x90) + 8))();
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(long **)(this + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x38) + 8))();
    *(undefined8 *)(this + 0x38) = 0;
  }
  if (*(long **)(this + 0x98) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x98) + 8))();
    *(undefined8 *)(this + 0x98) = 0;
  }
  if (*(long **)(this + 0xc0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xc0) + 8))();
    *(undefined8 *)(this + 0xc0) = 0;
  }
  this_00 = *(Root **)(this + 0x40);
  if (this_00 != (Root *)0x0) {
    Ogre::Root::~Root(this_00);
    Ogre::NedAllocImpl::deallocBytes(this_00);
    *(undefined8 *)(this + 0x40) = 0;
  }
  if (*(long **)(this + 0xb8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xb8) + 8))();
    *(undefined8 *)(this + 0xb8) = 0;
  }
  SDL_VideoQuit();
                    /* try { // try from 00560955 to 00560959 has its CatchHandler @ 00560c37 */
  SDLEventHandler::~SDLEventHandler((SDLEventHandler *)(this + 0x2a8));
                    /* try { // try from 00560961 to 00560965 has its CatchHandler @ 00560b6b */
  Ogre::GpuCommandBufferFlush::~GpuCommandBufferFlush((GpuCommandBufferFlush *)(this + 0x260));
  pCVar6 = *(CGame **)(this + 0x240);
  while (pCVar6 != this + 0x240) {
    pCVar5 = *(CGame **)pCVar6;
    operator_delete(pCVar6);
    pCVar6 = pCVar5;
  }
  *(undefined ***)(this + 0x218) = &PTR__SharedPtr_00fa4590;
  piVar4 = *(int **)(this + 0x228);
  if ((piVar4 != (int *)0x0) && (iVar2 = *piVar4, *piVar4 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 00560a72 to 00560a74 has its CatchHandler @ 00560b1f */
    (**(code **)(*(long *)(this + 0x218) + 0x10))(this + 0x218);
  }
  *(undefined ***)(this + 0x1f8) = &PTR__SharedPtr_00fa4590;
  piVar4 = *(int **)(this + 0x208);
  if ((piVar4 != (int *)0x0) && (iVar2 = *piVar4, *piVar4 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 00560a5a to 00560a5c has its CatchHandler @ 00560ac0 */
    (**(code **)(*(long *)(this + 0x1f8) + 0x10))(this + 0x1f8);
  }
                    /* try { // try from 005609da to 005609de has its CatchHandler @ 00560bd5 */
  Ogre::Timer::~Timer((Timer *)(this + 0x1e0));
  paVar1 = (allocator *)(*(long *)(this + 0xd0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar4 = (int *)(*(long *)(this + 0xd0) + -8);
    iVar2 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x88) + -0x18);
  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar4 = (int *)(*(long *)(this + 0x88) + -8);
    iVar2 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy(paVar1);
    }
  }
  *(undefined ***)(this + 0x30) = &PTR__RenderTargetListener_00fa4650;
  *(undefined ***)(this + 0x28) = &PTR__RenderableListener_00fa46b0;
  *(undefined ***)(this + 0x20) = &PTR__iEditorResourceManager_00fa46f0;
  *(undefined ***)(this + 0x18) = &PTR__WindowEventListener_00fa4770;
  *(undefined ***)(this + 0x10) = &PTR_frameStarted_00fa47d0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00560c50
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x30);
  return;
}



/* address=00560c60
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x28);
  return;
}



/* address=00560c70
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x20);
  return;
}



/* address=00560c80
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x18);
  return;
}



/* address=00560c90
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x10);
  return;
}



/* address=00560ca0
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x30);
  return;
}



/* address=00560cb0
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x28);
  return;
}



/* address=00560cc0
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x20);
  return;
}



/* address=00560cd0
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x18);
  return;
}



/* address=00560ce0
   symbol=CGame::~CGame */

/* non-virtual thunk to CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this + -0x10);
  return;
}



/* address=00560cf0
   symbol=CGame::~CGame */

/* CGame::~CGame() */

void __thiscall CGame::~CGame(CGame *this)

{
  ~CGame(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00560d10
   symbol=CGame::updateAspectRatio */

/* non-virtual thunk to CGame::updateAspectRatio(float, float) */

void __thiscall CGame::updateAspectRatio(CGame *this,float param_1,float param_2)

{
  updateAspectRatio(this + -0x20,param_1,param_2);
  return;
}



/* address=00560d20
   symbol=CGame::updateAspectRatio */

/* WARNING: Removing unreachable block (ram,0x005613ab) */
/* WARNING: Removing unreachable block (ram,0x00561357) */
/* WARNING: Removing unreachable block (ram,0x005613c7) */
/* WARNING: Removing unreachable block (ram,0x00561365) */
/* WARNING: Removing unreachable block (ram,0x00561381) */
/* WARNING: Removing unreachable block (ram,0x00561349) */
/* WARNING: Removing unreachable block (ram,0x00561286) */
/* WARNING: Removing unreachable block (ram,0x0056139d) */
/* WARNING: Removing unreachable block (ram,0x005613d5) */
/* WARNING: Removing unreachable block (ram,0x005613b9) */
/* WARNING: Removing unreachable block (ram,0x0056138f) */
/* WARNING: Removing unreachable block (ram,0x00561373) */
/* CGame::updateAspectRatio(float, float) */

void __thiscall CGame::updateAspectRatio(CGame *this,float param_1,float param_2)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
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
  long local_68 [2];
  long local_58 [5];

  STRINGS::GetValueAsString((STRINGS *)local_88,param_2);
                    /* try { // try from 00560d64 to 00560d68 has its CatchHandler @ 005612e0 */
  STRINGS::GetValueAsString((STRINGS *)local_58,param_1);
                    /* try { // try from 00560d7c to 00560d80 has its CatchHandler @ 005612ce */
  std::operator+((char *)local_68,(string *)0xfe4925);
                    /* try { // try from 00560d8f to 00560d93 has its CatchHandler @ 005612c9 */
  std::string::string((string *)local_78,(string *)local_68);
                    /* try { // try from 00560da1 to 00560da5 has its CatchHandler @ 005612bc */
  std::string::append((char *)local_78,0xfa040c);
                    /* try { // try from 00560db7 to 00560dbb has its CatchHandler @ 00561291 */
  std::operator+((string *)local_98,(string *)local_78);
                    /* try { // try from 00560dbc to 00560dd2 has its CatchHandler @ 005612d3 */
  uVar4 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar4,(string *)local_98,3,0);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT)
  ;
  STRINGS::GetValueAsString((STRINGS *)local_d8,iVar3);
                    /* try { // try from 00560e6c to 00560e7f has its CatchHandler @ 00561271 */
  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
  STRINGS::GetValueAsString((STRINGS *)local_a8,iVar3);
                    /* try { // try from 00560e90 to 00560e94 has its CatchHandler @ 00561332 */
  std::operator+((char *)local_b8,(string *)"stored res is - ");
                    /* try { // try from 00560ea0 to 00560ea4 has its CatchHandler @ 0056132d */
  std::string::string((string *)local_c8,(string *)local_b8);
                    /* try { // try from 00560eb2 to 00560eb6 has its CatchHandler @ 00561320 */
  std::string::append((char *)local_c8,0xfa040c);
                    /* try { // try from 00560ec7 to 00560ecb has its CatchHandler @ 00561300 */
  std::operator+((string *)local_e8,(string *)local_c8);
                    /* try { // try from 00560ecc to 00560ee2 has its CatchHandler @ 00561337 */
  uVar4 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar4,(string *)local_e8,3,0);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  STRINGS::GetValueAsString((STRINGS *)local_f8,param_1 / param_2);
                    /* try { // try from 00560f66 to 00560f6a has its CatchHandler @ 00561344 */
  std::operator+((char *)local_108,(string *)"AspectRatio message AR - ");
                    /* try { // try from 00560f6b to 00560f81 has its CatchHandler @ 005612e5 */
  uVar4 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar4,local_108,3,0);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  lVar2 = *(long *)(this + 0x38);
  if (lVar2 != 0) {
    CCameraControl::setAspectRatio((CCameraControl *)param_1,param_2,lVar2,0);
    CCameraControl::setAspectRatio((CCameraControl *)param_1,param_2,lVar2,1);
    CCameraControl::setAspectRatio((CCameraControl *)param_1,param_2,lVar2,2);
  }
  if (*(CGameClient **)(this + 0x98) != (CGameClient *)0x0) {
    CGameClient::updateScreenInfo
              (*(CGameClient **)(this + 0x98),*(void **)(this + 0xa0),(int)param_1,(int)param_2);
  }
  return;
}



/* address=005613f0
   symbol=CGame::createCamera */

/* WARNING: Removing unreachable block (ram,0x00561831) */
/* WARNING: Removing unreachable block (ram,0x00561872) */
/* WARNING: Removing unreachable block (ram,0x00561880) */
/* CGame::createCamera() */

void __thiscall CGame::createCamera(CGame *this)

{
  int *piVar1;
  code *pcVar2;
  int iVar3;
  Vector3 *pVVar4;
  Vector3 *pVVar5;
  Vector3 *pVVar6;
  CCameraControl *this_00;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  float local_68 [4];
  float local_58 [4];
  float local_48 [3];
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long **)(this + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x38) + 8))();
    *(undefined8 *)(this + 0x38) = 0;
  }
  pcVar2 = *(code **)(**(long **)(this + 0x50) + 0x1a8);
                    /* try { // try from 00561441 to 00561445 has its CatchHandler @ 00561856 */
  std::string::string((string *)local_78,"PlayerCam",local_39);
                    /* try { // try from 0056144d to 0056144f has its CatchHandler @ 0056183c */
  pVVar4 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x50),(string *)local_78);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  local_48[0] = DAT_00fa4814 * Ogre::Math::fDeg2Rad;
  (**(code **)(*(long *)pVVar4 + 0x248))(pVVar4,local_48);
  Ogre::Camera::setPosition(pVVar4);
  Ogre::Camera::lookAt(pVVar4);
  (**(code **)(*(long *)pVVar4 + 600))(DAT_00fa47fc,pVVar4);
  Ogre::Camera::setAutoAspectRatio(SUB81(pVVar4,0));
  iVar3 = CDynamicPropertyFile::GetInt
                    (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NETBOOK_MODE);
  if (iVar3 == 1) {
    (**(code **)(*(long *)pVVar4 + 0x268))(DAT_00fa4818,pVVar4);
  }
  else {
    (**(code **)(*(long *)pVVar4 + 0x268))(DAT_00fa481c,pVVar4);
  }
  pcVar2 = *(code **)(**(long **)(this + 0x58) + 0x1a8);
                    /* try { // try from 0056155e to 00561562 has its CatchHandler @ 00561826 */
  std::string::string((string *)local_88,"UICam",&local_3a);
                    /* try { // try from 0056156a to 0056156c has its CatchHandler @ 00561862 */
  pVVar5 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x58),(string *)local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  (**(code **)(*(long *)pVVar5 + 0x368))(pVVar5,0);
  local_58[0] = DAT_00fa4814 * Ogre::Math::fDeg2Rad;
  (**(code **)(*(long *)pVVar5 + 0x248))(pVVar5,local_58);
  Ogre::Camera::setPosition(pVVar5);
  Ogre::Camera::lookAt(pVVar5);
  (**(code **)(*(long *)pVVar5 + 600))(DAT_00fa480c,pVVar5);
  (**(code **)(*(long *)pVVar5 + 0x268))(DAT_00fa481c,pVVar5);
  Ogre::Camera::setAutoAspectRatio(SUB81(pVVar5,0));
  pcVar2 = *(code **)(**(long **)(this + 0x48) + 0x1a8);
                    /* try { // try from 00561666 to 0056166a has its CatchHandler @ 00561858 */
  std::string::string((string *)local_98,"BKCam",&local_3b);
                    /* try { // try from 00561672 to 00561674 has its CatchHandler @ 00561849 */
  pVVar6 = (Vector3 *)(*pcVar2)(*(undefined8 *)(this + 0x48),(string *)local_98);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  local_68[0] = Ogre::Math::fDeg2Rad * DAT_00fa4820;
  (**(code **)(*(long *)pVVar6 + 0x248))(pVVar6,local_68);
  Ogre::Camera::setPosition(pVVar6);
  Ogre::Camera::lookAt(pVVar6);
  (**(code **)(*(long *)pVVar6 + 600))(DAT_00fa47fc,pVVar6);
  (**(code **)(*(long *)pVVar6 + 0x268))(DAT_00fa4824,pVVar6);
  Ogre::Camera::setAutoAspectRatio(SUB81(pVVar6,0));
  this_00 = (CCameraControl *)Ogre::NedAllocImpl::allocBytes(0xa0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0056175e to 00561762 has its CatchHandler @ 00561864 */
  CCameraControl::CCameraControl
            (this_00,(Camera *)pVVar4,(Camera *)pVVar5,(Camera *)pVVar6,(Camera *)0x0,(Camera *)0x0)
  ;
  *(CCameraControl **)(this + 0x38) = this_00;
  return;
}



/* address=00561890
   symbol=CGame::chooseSceneManager */

/* WARNING: Removing unreachable block (ram,0x00561bec) */
/* WARNING: Removing unreachable block (ram,0x00561bde) */
/* WARNING: Removing unreachable block (ram,0x00561bc2) */
/* WARNING: Removing unreachable block (ram,0x00561b64) */
/* WARNING: Removing unreachable block (ram,0x00561bfa) */
/* WARNING: Removing unreachable block (ram,0x00561bd0) */
/* CGame::chooseSceneManager() */

void __thiscall CGame::chooseSceneManager(CGame *this)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  long *plVar4;
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38 [3];
  allocator local_1e;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;

  Ogre::MovableObject::msDefaultVisibilityFlags = 1;
                    /* try { // try from 005618b7 to 005618bb has its CatchHandler @ 00561ba4 */
  std::string::string((string *)local_38,"SMBKInstance",&local_19);
                    /* try { // try from 005618c8 to 005618cc has its CatchHandler @ 00561bb2 */
  uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(undefined8 *)(this + 0x48) = uVar3;
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
                    /* try { // try from 005618fa to 005618fe has its CatchHandler @ 00561b92 */
  std::string::string((string *)local_48,"SMInstance",&local_1a);
                    /* try { // try from 0056190b to 0056190f has its CatchHandler @ 00561b89 */
  plVar4 = (long *)Ogre::Root::createSceneManager
                             ((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(long **)(this + 0x50) = plVar4;
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
    plVar4 = *(long **)(this + 0x50);
  }
  (**(code **)(*plVar4 + 0x7f0))(plVar4,7);
                    /* try { // try from 00561949 to 0056194d has its CatchHandler @ 00561b87 */
  std::string::string((string *)local_58,"SMUIInstance",&local_1b);
                    /* try { // try from 0056195a to 0056195e has its CatchHandler @ 00561b7a */
  uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(undefined8 *)(this + 0x58) = uVar3;
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  Ogre::SceneManager::setAmbientLight(*(ColourValue **)(this + 0x58));
                    /* try { // try from 005619b2 to 005619b6 has its CatchHandler @ 00561bbf */
  std::string::string((string *)local_68,"SMRBInstance",&local_1c);
                    /* try { // try from 005619c3 to 005619c7 has its CatchHandler @ 00561ba2 */
  uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(undefined8 *)(this + 0x60) = uVar3;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
                    /* try { // try from 005619f0 to 005619f4 has its CatchHandler @ 00561b96 */
  std::string::string((string *)local_78,"SMRBPInstance",&local_1d);
                    /* try { // try from 00561a01 to 00561a05 has its CatchHandler @ 00561b94 */
  uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(undefined8 *)(this + 0x68) = uVar3;
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 00561a2e to 00561a32 has its CatchHandler @ 00561b6f */
  std::string::string((string *)local_88,"SMAMInstance",&local_1e);
                    /* try { // try from 00561a3f to 00561a43 has its CatchHandler @ 00561ba6 */
  uVar3 = Ogre::Root::createSceneManager((ushort)*(undefined8 *)(this + 0x40),(string *)0x10);
  *(undefined8 *)(this + 0x70) = uVar3;
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  return;
}



/* address=00561c10
   symbol=CGame::createViewports */

/* WARNING: Removing unreachable block (ram,0x00562180) */
/* WARNING: Removing unreachable block (ram,0x0056218e) */
/* WARNING: Removing unreachable block (ram,0x005620eb) */
/* WARNING: Removing unreachable block (ram,0x00562148) */
/* WARNING: Removing unreachable block (ram,0x00562172) */
/* WARNING: Removing unreachable block (ram,0x00562156) */
/* WARNING: Removing unreachable block (ram,0x00562164) */
/* CGame::createViewports() */

void __thiscall CGame::createViewports(CGame *this)

{
  int *piVar1;
  long *plVar2;
  int iVar3;
  int iVar4;
  ColourValue *pCVar5;
  undefined8 uVar6;
  float fVar7;
  CCameraControl *pCVar8;
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];

  if ((*(long *)(this + 0x38) != 0) && (plVar2 = *(long **)(this + 0x80), plVar2 != (long *)0x0)) {
    pCVar5 = (ColourValue *)
             (**(code **)(*plVar2 + 0x48))
                       (0,0,DAT_00fa47fc,plVar2,*(undefined8 *)(*(long *)(this + 0x38) + 0x10),1);
    *(ColourValue **)(this + 0x78) = pCVar5;
    Ogre::Viewport::setBackgroundColour(pCVar5);
    Ogre::Viewport::setClearEveryFrame(SUB81(pCVar5,0),0);
    pCVar5 = (ColourValue *)
             (**(code **)(**(long **)(this + 0x80) + 0x48))
                       (0,0,DAT_00fa47fc,*(long **)(this + 0x80),
                        *(undefined8 *)(*(long *)(this + 0x38) + 0x18),5);
    Ogre::Viewport::setBackgroundColour(pCVar5);
    Ogre::Viewport::setClearEveryFrame(SUB81(pCVar5,0),1);
    pCVar5 = (ColourValue *)
             (**(code **)(**(long **)(this + 0x80) + 0x48))
                       (0,0,DAT_00fa47fc,*(long **)(this + 0x80),
                        *(undefined8 *)(*(long *)(this + 0x38) + 0x20),0);
    Ogre::Viewport::setBackgroundColour(pCVar5);
    iVar3 = Ogre::Viewport::getActualHeight();
    fVar7 = (float)iVar3;
    iVar3 = Ogre::Viewport::getActualWidth();
    pCVar8._0_4_ = (CCameraControl *)(float)iVar3;
    uVar6 = *(undefined8 *)(this + 0x38);
    CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,0);
    CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,1);
    CCameraControl::setAspectRatio(pCVar8._0_4_,fVar7,uVar6,2);
    iVar3 = Ogre::Viewport::getActualHeight();
    STRINGS::GetValueAsString((STRINGS *)local_78,iVar3);
                    /* try { // try from 00561dfa to 00561e12 has its CatchHandler @ 00562123 */
    iVar3 = Ogre::Viewport::getActualWidth();
    STRINGS::GetValueAsString((STRINGS *)local_48,(float)iVar3);
                    /* try { // try from 00561e26 to 00561e2a has its CatchHandler @ 0056211c */
    std::operator+((char *)local_58,(string *)"CreateViewports AspectRatio message - ");
                    /* try { // try from 00561e39 to 00561e3d has its CatchHandler @ 005620e4 */
    std::string::string((string *)local_68,(string *)local_58);
                    /* try { // try from 00561e4b to 00561e4f has its CatchHandler @ 005620b5 */
    std::string::append((char *)local_68,0xfa040c);
                    /* try { // try from 00561e5e to 00561e62 has its CatchHandler @ 00562141 */
    std::operator+((string *)local_88,(string *)local_68);
                    /* try { // try from 00561e63 to 00561e79 has its CatchHandler @ 0056212a */
    uVar6 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar6,(string *)local_88,3,0);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    iVar3 = Ogre::Viewport::getActualWidth();
    iVar4 = Ogre::Viewport::getActualHeight();
    STRINGS::GetValueAsString((STRINGS *)local_98,(float)iVar3 / (float)iVar4);
                    /* try { // try from 00561f22 to 00561f26 has its CatchHandler @ 00562115 */
    std::operator+((char *)local_a8,(string *)"CreateViewports AspectRatio message AR - ");
                    /* try { // try from 00561f27 to 00561f3d has its CatchHandler @ 005620f6 */
    uVar6 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar6,local_a8,3,0);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
  }
  return;
}



/* address=005621a0
   symbol=CGame::convertAssetsToBinary */

/* WARNING: Removing unreachable block (ram,0x00562b68) */
/* WARNING: Removing unreachable block (ram,0x00562e24) */
/* WARNING: Removing unreachable block (ram,0x00562dd5) */
/* WARNING: Removing unreachable block (ram,0x00562ee4) */
/* WARNING: Removing unreachable block (ram,0x00562ed6) */
/* WARNING: Removing unreachable block (ram,0x00562ec8) */
/* WARNING: Removing unreachable block (ram,0x00562e16) */
/* WARNING: Removing unreachable block (ram,0x00562c0e) */
/* WARNING: Removing unreachable block (ram,0x00562c9e) */
/* WARNING: Removing unreachable block (ram,0x00562dfa) */
/* WARNING: Removing unreachable block (ram,0x00562c19) */
/* WARNING: Removing unreachable block (ram,0x00562d25) */
/* WARNING: Removing unreachable block (ram,0x00562eba) */
/* WARNING: Removing unreachable block (ram,0x00562e32) */
/* WARNING: Removing unreachable block (ram,0x00562e71) */
/* WARNING: Removing unreachable block (ram,0x00562d60) */
/* WARNING: Removing unreachable block (ram,0x00562dec) */
/* WARNING: Removing unreachable block (ram,0x00562b73) */
/* WARNING: Removing unreachable block (ram,0x00562ae6) */
/* WARNING: Removing unreachable block (ram,0x00562e08) */
/* CGame::convertAssetsToBinary() */

void __thiscall CGame::convertAssetsToBinary(CGame *this)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  int iVar4;
  char cVar5;
  undefined8 uVar6;
  ulong uVar7;
  CLayout *this_00;
  CDataGroup *this_01;
  wstring_conflict *pwVar8;
  uint uVar9;
  wstring_conflict *pwVar10;
  allocator *paVar11;
  wstring_conflict *local_178;
  uint local_170;
  uint local_16c;
  undefined4 local_168;
  long local_158 [2];
  wchar_t *local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  wchar_t *local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [4];
  allocator local_41;
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if ((*(long *)(this + 0x98) == 0) || (*(long *)(*(long *)(this + 0x98) + 0x2b8) == 0)) {
                    /* try { // try from 0056287c to 00562880 has its CatchHandler @ 00562de7 */
    std::string::string((string *)local_68,"Unable to convert raw assets to binary.",local_39);
                    /* try { // try from 00562881 to 00562897 has its CatchHandler @ 00562de2 */
    uVar6 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar6,(string *)local_68,3);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_68[0] + -8);
      iVar4 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
  }
                    /* try { // try from 005621ec to 005621f0 has its CatchHandler @ 00562c96 */
  std::string::string((string *)local_78,"Starting to convert layouts to compressed binary",
                      &local_3a);
                    /* try { // try from 005621f1 to 00562207 has its CatchHandler @ 00562c76 */
  uVar6 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar6,(string *)local_78,3);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_78[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  local_178 = (wstring_conflict *)0x0;
  local_170 = 0;
  local_16c = 0;
  local_168 = 10;
                    /* try { // try from 0056225c to 00562260 has its CatchHandler @ 00562c42 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"media/",&local_3b);
                    /* try { // try from 0056226c to 00562270 has its CatchHandler @ 00562c3c */
  FILESYSTEM::GetApplicationPath((FILESYSTEM *)local_98);
                    /* try { // try from 0056227f to 00562283 has its CatchHandler @ 00562c24 */
  FILESYSTEM::AssembleAbsolutePath
            ((FILESYSTEM *)local_88,(wstring_conflict *)local_98,(wstring_conflict *)local_a8);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_a8[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 005622cc to 005622d0 has its CatchHandler @ 00562d1f */
  std::wstring::wstring((wstring_conflict *)local_b8,L"*.layout",&local_3c);
                    /* try { // try from 005622e1 to 005622e5 has its CatchHandler @ 00562cf4 */
  FILESYSTEM::GetFileListRecursive
            ((wstring_conflict *)local_88,(TArrayList *)&local_178,(wstring_conflict *)local_b8);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  if (local_170 != 0) {
    uVar9 = 0;
    do {
      pwVar10 = local_178;
      if (uVar9 < local_16c) {
        pwVar10 = local_178 + (ulong)uVar9 * 8;
      }
                    /* try { // try from 00562328 to 0056232c has its CatchHandler @ 00562cbb */
      STRINGS::StringUpper((STRINGS *)local_c8,pwVar10);
      wcslen(L"/UI/");
                    /* try { // try from 00562344 to 0056239a has its CatchHandler @ 00562c8e */
      uVar7 = std::wstring::find((wchar_t *)local_c8,0xfa3e04,0);
      if ((uVar7 == 0) || (*(ulong *)(local_c8[0] + -0x18) <= uVar7)) {
        std::wstring::wstring((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
        wcslen(L".cmp");
                    /* try { // try from 005623b0 to 005623b4 has its CatchHandler @ 00562cb9 */
        std::wstring::append((wchar_t *)local_d8,0xfa3e18);
                    /* try { // try from 005623b8 to 005623bc has its CatchHandler @ 00562ca9 */
        cVar5 = FILESYSTEM::FileExists((wstring_conflict *)local_d8);
        if ((allocator *)(local_d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_d8[0] + -8);
          iVar4 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
          }
        }
        if (cVar5 == '\0') {
                    /* try { // try from 005623ea to 005623ee has its CatchHandler @ 00562c8e */
          std::operator+((wchar_t *)local_e8,(wstring_conflict *)L"Compressing layout file: ");
                    /* try { // try from 005623fc to 00562400 has its CatchHandler @ 00562d05 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_138,local_e8[0]);
          if ((allocator *)(local_e8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_e8[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -6));
            }
          }
                    /* try { // try from 00562416 to 00562456 has its CatchHandler @ 00562b7e */
          uVar6 = Ogre::LogManager::getSingleton();
          Ogre::LogManager::logMessage(uVar6,local_138,3);
          uVar6 = *(undefined8 *)(*(long *)(this + 0x98) + 0x2b8);
          this_00 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00562464 to 00562468 has its CatchHandler @ 00562a50 */
          CLayout::CLayout(this_00,uVar6,0);
          pwVar10 = local_178;
          if (uVar9 < local_16c) {
            pwVar10 = local_178 + (ulong)uVar9 * 8;
          }
                    /* try { // try from 0056248f to 005624a1 has its CatchHandler @ 00562b7e */
          CLayout::loadLayoutFile(this_00,pwVar10,true,(CTimerStatics *)0x0,false,false,0);
          if (this_00 != (CLayout *)0x0) {
            (**(code **)(*(long *)this_00 + 8))(this_00);
          }
          if ((allocator *)(local_138[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_138[0] + -8);
            iVar4 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
            }
          }
        }
        if ((allocator *)(local_c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_c8[0] + -8);
          iVar4 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
          }
        }
      }
      else if ((allocator *)(local_c8[0] + -0x18) !=
               (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_c8[0] + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < local_170);
  }
  local_170 = 0;
  local_16c = 0;
  if (local_178 != (wstring_conflict *)0x0) {
    pwVar10 = local_178 + *(long *)(local_178 + -8) * 8;
    pwVar8 = local_178;
    while (pwVar10 != pwVar8) {
      pwVar10 = pwVar10 + -8;
      paVar11 = (allocator *)(*(long *)pwVar10 + -0x18);
      if (paVar11 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(*(long *)pwVar10 + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        pwVar8 = local_178;
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy(paVar11);
          pwVar8 = local_178;
        }
      }
    }
    operator_delete__(pwVar10 + -8);
  }
  local_178 = (wstring_conflict *)0x0;
                    /* try { // try from 00562593 to 00562597 has its CatchHandler @ 00562d1a */
  std::wstring::wstring((wstring_conflict *)local_f8,L"*.dat",&local_3d);
                    /* try { // try from 005625a8 to 005625ac has its CatchHandler @ 00562e6c */
  FILESYSTEM::GetFileListRecursive
            ((wstring_conflict *)local_88,(TArrayList *)&local_178,(wstring_conflict *)local_f8);
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_f8[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 005625da to 005625de has its CatchHandler @ 00562db5 */
  std::wstring::wstring((wstring_conflict *)local_108,L"*.hie",&local_3e);
                    /* try { // try from 005625ef to 005625f3 has its CatchHandler @ 00562dac */
  FILESYSTEM::GetFileListRecursive
            ((wstring_conflict *)local_88,(TArrayList *)&local_178,(wstring_conflict *)local_108);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_108[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
                    /* try { // try from 00562621 to 00562625 has its CatchHandler @ 00562e7c */
  std::wstring::wstring((wstring_conflict *)local_118,L"*.animation",&local_3f);
                    /* try { // try from 00562636 to 0056263a has its CatchHandler @ 00562d5e */
  FILESYSTEM::GetFileListRecursive
            ((wstring_conflict *)local_88,(TArrayList *)&local_178,(wstring_conflict *)local_118);
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_118[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
                    /* try { // try from 00562668 to 0056266c has its CatchHandler @ 00562dc5 */
  std::string::string((string *)local_128,"Starting to convert dat and text files to binary",
                      &local_40);
                    /* try { // try from 0056266d to 00562683 has its CatchHandler @ 00562da7 */
  uVar6 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar6,(string *)local_128,3);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_128[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if (local_170 != 0) {
    uVar9 = 0;
    do {
                    /* try { // try from 005626cd to 005626d1 has its CatchHandler @ 00562cbb */
      std::operator+((wchar_t *)local_148,(wstring_conflict *)L"Converting file to binary: ");
                    /* try { // try from 005626da to 005626de has its CatchHandler @ 00562d6b */
      STRINGS::StringConvertToNarrow((STRINGS *)local_138,local_148[0]);
      if ((allocator *)(local_148[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        pwVar1 = local_148[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -6));
        }
      }
                    /* try { // try from 005626f1 to 00562717 has its CatchHandler @ 00562c86 */
      uVar6 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar6,(STRINGS *)local_138,3);
      this_01 = (CDataGroup *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00562733 to 00562737 has its CatchHandler @ 00562b86 */
      CDataGroup::CDataGroup
                (this_01,(wstring_conflict *)&::EMPTY_WSTRING,(CDataGroup *)0x0,0x14,10,
                 (TRepository *)0x0);
      pwVar10 = local_178;
      if (uVar9 < local_16c) {
        pwVar10 = local_178 + (ulong)uVar9 * 8;
      }
                    /* try { // try from 00562748 to 0056275b has its CatchHandler @ 00562c86 */
      CDataGroup::LoadFile(this_01,pwVar10,(CTimerStatics *)0x0);
      if (this_01 != (CDataGroup *)0x0) {
        (**(code **)(*(long *)this_01 + 8))(this_01);
      }
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_138[0] + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < local_170);
  }
                    /* try { // try from 005627bd to 005627c1 has its CatchHandler @ 00562bae */
  std::string::string((string *)local_158,"Completed Compression of files.",&local_41);
                    /* try { // try from 005627c2 to 005627d8 has its CatchHandler @ 00562b9e */
  uVar6 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar6,(string *)local_158,3,0);
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_158[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if (local_178 != (wstring_conflict *)0x0) {
    pwVar10 = local_178 + *(long *)(local_178 + -8) * 8;
    pwVar8 = local_178;
    while (pwVar8 != pwVar10) {
      pwVar10 = pwVar10 + -8;
      paVar11 = (allocator *)(*(long *)pwVar10 + -0x18);
      if (paVar11 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(*(long *)pwVar10 + -8);
        iVar4 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        pwVar8 = local_178;
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy(paVar11);
          pwVar8 = local_178;
        }
      }
    }
    operator_delete__(pwVar8 + -8);
  }
  return;
}



/* address=00562ef0
   symbol=CGame::begin */

/* WARNING: Removing unreachable block (ram,0x00563327) */
/* WARNING: Removing unreachable block (ram,0x005633ec) */
/* WARNING: Removing unreachable block (ram,0x0056338c) */
/* WARNING: Removing unreachable block (ram,0x005632b5) */
/* WARNING: Removing unreachable block (ram,0x00563332) */
/* WARNING: Removing unreachable block (ram,0x005632c0) */
/* CGame::begin(void*) */

undefined8 __thiscall CGame::begin(CGame *this,void *param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  uint uVar4;
  long *plVar5;
  char cVar6;
  int iVar7;
  long lVar8;
  undefined8 uVar9;
  bool bVar10;
  bool bVar11;
  int local_e8 [3];
  char local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  wchar_t *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  wchar_t *local_78 [2];
  long local_68 [2];
  long local_58 [2];
  int local_48;
  int local_44 [2];
  allocator local_3a;
  allocator local_39 [9];

  *(void **)(this + 0xa8) = param_1;
  std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00562f38 to 00562f3c has its CatchHandler @ 0056339b */
  std::wstring::wstring((wstring_conflict *)local_58,L"COMPRESS",local_39);
                    /* try { // try from 00562f43 to 00562f5f has its CatchHandler @ 00563371 */
  lVar8 = (**(code **)(*(long *)this + 0x18))(this);
  CCmdLineParser::GetStringParam
            (local_78,*(undefined8 *)(lVar8 + 0x140),(wstring_conflict *)local_58,
             (wstring_conflict *)local_68);
  bVar11 = false;
  if (*(size_t *)(local_78[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar7 = wmemcmp(local_78[0],::EMPTY_WSTRING,*(size_t *)(local_78[0] + -6));
    bVar11 = iVar7 == 0;
  }
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_78[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00562fe8 to 00562fec has its CatchHandler @ 005633bb */
  std::wstring::wstring((wstring_conflict *)local_88,L"NOWINDOW",&local_3a);
                    /* try { // try from 00563006 to 0056300a has its CatchHandler @ 005633a0 */
  CCmdLineParser::GetStringParam
            (local_a8,*(undefined8 *)(*(long *)(this + 0xb8) + 0x140),(wstring_conflict *)local_88,
             (wstring_conflict *)local_98);
  bVar10 = false;
  if (*(size_t *)(local_a8[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar7 = wmemcmp(local_a8[0],::EMPTY_WSTRING,*(size_t *)(local_a8[0] + -6));
    bVar10 = iVar7 == 0;
  }
  if ((allocator *)(local_a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_a8[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  cVar6 = (**(code **)(*(long *)this + 0x60))(this,bVar10);
  if (cVar6 == '\0') {
    uVar9 = 0x80004005;
    if (gUseSplash != '\0') {
      CSplash::Hide((CSplash *)m_gSplash);
      uVar9 = 0x80004005;
    }
  }
  else if (bVar11) {
    plVar5 = *(long **)(this + 0x80);
    if (plVar5 != (long *)0x0) {
      (**(code **)(*plVar5 + 0x1d0))(plVar5,1);
      uVar4 = *(uint *)(this + 0xb4);
      iVar7 = *(int *)(this + 0xb0);
      lVar8 = CGameUI::getSingleton();
      if (lVar8 != 0) {
        CSplash::findCenterForWindow(0x1424b60,iVar7,(int *)(ulong)uVar4,local_44);
        CEGUI::System::getSingleton();
        CEGUI::System::injectMousePosition((float)local_44[0],(float)local_48);
        CEGUI::System::getSingleton();
        CEGUI::System::injectMouseMove(DAT_00fa47fc,0.0);
      }
    }
    Ogre::Root::clearEventTimes();
    do {
      bVar11 = false;
      while (iVar7 = SDL_PollEvent((SDL_Event *)local_e8), iVar7 != 0) {
        while (local_e8[0] != 0x100) {
          if (local_e8[0] == 0x200) {
            if (local_dc == '\x04') {
              (**(code **)(**(long **)(this + 0x80) + 0x1c0))
                        (*(long **)(this + 0x80),local_d8,local_d4);
              (**(code **)(**(long **)(this + 0x80) + 0x1b8))();
            }
            else if (local_dc == '\x0e') {
              local_e8[0] = 0x100;
              SDL_PushEvent((SDL_Event *)local_e8);
            }
          }
          SDLEventHandler::ProcessEvent((SDLEventHandler *)(this + 0x2a8),(SDL_Event *)local_e8);
          iVar7 = SDL_PollEvent((SDL_Event *)local_e8);
          if (iVar7 == 0) goto LAB_0056319d;
        }
        bVar11 = true;
      }
LAB_0056319d:
      cVar6 = Ogre::Root::renderOneFrame();
    } while ((cVar6 != '\0') && (!bVar11));
    cleanUpGameObjects(this);
    uVar9 = 0;
  }
  else {
    convertAssetsToBinary(this);
    cleanUpGameObjects(this);
    uVar9 = 0;
  }
  return uVar9;
}



/* address=00563400
   symbol=CGame::renderableQueued */

/* non-virtual thunk to CGame::renderableQueued(Ogre::Renderable*, unsigned char, unsigned short,
   Ogre::Technique**, Ogre::RenderQueue*) */

void __thiscall
CGame::renderableQueued
          (CGame *this,Renderable *param_1,uchar param_2,ushort param_3,Technique **param_4,
          RenderQueue *param_5)

{
  renderableQueued(this + -0x28,param_1,param_2,param_3,param_4,param_5);
  return;
}



/* address=00563410
   symbol=CGame::renderableQueued */

/* CGame::renderableQueued(Ogre::Renderable*, unsigned char, unsigned short, Ogre::Technique**,
   Ogre::RenderQueue*) */

undefined8 __thiscall
CGame::renderableQueued
          (CGame *this,Renderable *param_1,uchar param_2,ushort param_3,Technique **param_4,
          RenderQueue *param_5)

{
  short sVar1;
  long *plVar2;
  long lVar3;
  Any *pAVar4;
  CRenderableStates *pCVar5;
  Technique *pTVar6;
  RenderQueueGroup *pRVar7;

  if ((byte)(param_2 + 0xa1) < 5) {
    return 0;
  }
  if (((param_1 != (Renderable *)0x0) &&
      (plVar2 = (long *)__dynamic_cast(param_1,&Ogre::Renderable::typeinfo,Ogre::SubEntity::typeinfo
                                       ,0), plVar2 != (long *)0x0)) &&
     (lVar3 = (**(code **)(*plVar2 + 0x80))(plVar2), *(long *)(lVar3 + 8) != 0)) {
    pAVar4 = (Any *)(**(code **)(*plVar2 + 0x80))(plVar2);
    pCVar5 = Ogre::any_cast<CRenderableStates*>(pAVar4);
    if (((pCVar5 != (CRenderableStates *)0x0) && (*param_4 != (Technique *)0x0)) &&
       (sVar1 = Ogre::Technique::getNumPasses(), sVar1 != 0)) {
      Ogre::Technique::getPass((ushort)*param_4);
      if (this[0x238] != (CGame)0x0) {
        pTVar6 = (Technique *)Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x220));
        pRVar7 = (RenderQueueGroup *)Ogre::RenderQueue::getQueueGroup((uchar)param_5);
        Ogre::RenderQueueGroup::addRenderable(pRVar7,param_1,pTVar6,param_3);
      }
      if ((((this[0xc9] != (CGame)0x0) || (this[0xca] != (CGame)0x0)) ||
          ((this[600] == (CGame)0x0 ||
           ((pCVar5[4] == (CRenderableStates)0x0 || (*(float *)(pCVar5 + 0x34) <= DAT_00fa47f8))))))
         || ((*(long *)(this + 0x98) != 0 && (*(int *)(*(long *)(this + 0x98) + 0x38d0) == 0)))) {
        if (pCVar5[3] == (CRenderableStates)0x0) {
          return 1;
        }
        lVar3 = *(long *)(pCVar5 + 0x18);
      }
      else {
        if (pCVar5[3] == (CRenderableStates)0x0) {
          pTVar6 = *param_4;
        }
        else {
          pTVar6 = (Technique *)Ogre::Material::getTechnique((ushort)*(undefined8 *)(pCVar5 + 0x18))
          ;
        }
        pRVar7 = (RenderQueueGroup *)Ogre::RenderQueue::getQueueGroup((uchar)param_5);
        Ogre::RenderQueueGroup::addRenderable(pRVar7,param_1,pTVar6,param_3);
        if (*pCVar5 != (CRenderableStates)0x0) {
          return 0;
        }
        lVar3 = *(long *)(pCVar5 + 0x20);
        if (lVar3 == 0) {
          pTVar6 = (Technique *)Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x200));
          *param_4 = pTVar6;
          return 1;
        }
      }
      pTVar6 = (Technique *)Ogre::Material::getTechnique((ushort)lVar3);
      *param_4 = pTVar6;
      return 1;
    }
  }
  return 1;
}



/* address=00563640
   symbol=CGame::createMaterials */

/* WARNING: Removing unreachable block (ram,0x00566890) */
/* WARNING: Removing unreachable block (ram,0x0056657c) */
/* WARNING: Removing unreachable block (ram,0x0056663d) */
/* WARNING: Removing unreachable block (ram,0x00566c11) */
/* WARNING: Removing unreachable block (ram,0x00566c2d) */
/* WARNING: Removing unreachable block (ram,0x00566c49) */
/* WARNING: Removing unreachable block (ram,0x00566c03) */
/* WARNING: Removing unreachable block (ram,0x00566905) */
/* WARNING: Removing unreachable block (ram,0x0056624e) */
/* WARNING: Removing unreachable block (ram,0x005666b2) */
/* WARNING: Removing unreachable block (ram,0x00566a75) */
/* WARNING: Removing unreachable block (ram,0x005669e8) */
/* WARNING: Removing unreachable block (ram,0x00566765) */
/* WARNING: Removing unreachable block (ram,0x005669f3) */
/* WARNING: Removing unreachable block (ram,0x005664d2) */
/* WARNING: Removing unreachable block (ram,0x005669fe) */
/* WARNING: Removing unreachable block (ram,0x00566ac6) */
/* WARNING: Removing unreachable block (ram,0x00566703) */
/* WARNING: Removing unreachable block (ram,0x00566957) */
/* WARNING: Removing unreachable block (ram,0x00566b6c) */
/* WARNING: Removing unreachable block (ram,0x00566648) */
/* WARNING: Removing unreachable block (ram,0x00566243) */
/* WARNING: Removing unreachable block (ram,0x00566566) */
/* WARNING: Removing unreachable block (ram,0x00566c65) */
/* WARNING: Removing unreachable block (ram,0x00566235) */
/* WARNING: Removing unreachable block (ram,0x00566bf5) */
/* WARNING: Removing unreachable block (ram,0x00566c57) */
/* WARNING: Removing unreachable block (ram,0x00566b77) */
/* WARNING: Removing unreachable block (ram,0x0056689b) */
/* WARNING: Removing unreachable block (ram,0x00566571) */
/* WARNING: Removing unreachable block (ram,0x00566c3b) */
/* WARNING: Removing unreachable block (ram,0x00566c1f) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CGame::createMaterials() */

void __thiscall CGame::createMaterials(CGame *this)

{
  int iVar1;
  code *pcVar2;
  int *piVar3;
  bool bVar4;
  ushort uVar5;
  long *plVar6;
  ColourValue *pCVar7;
  undefined8 uVar8;
  string *psVar9;
  CFileSystem *pCVar10;
  uint uVar11;
  float fVar12;
  undefined1 *local_8d8;
  long local_8d0;
  long local_8c8;
  undefined4 local_8c0;
  undefined4 local_8bc;
  undefined1 *local_8b8;
  undefined1 local_8b0;
  undefined **local_8a8;
  long local_8a0;
  int *local_898;
  undefined **local_888;
  long local_880;
  int *local_878;
  undefined4 local_870;
  undefined **local_868;
  long local_860;
  int *local_858;
  undefined **local_848;
  long local_840;
  int *local_838;
  undefined4 local_830;
  undefined **local_828;
  long local_820;
  int *local_818;
  undefined **local_808;
  long local_800;
  int *local_7f8;
  undefined4 local_7f0;
  undefined **local_7e8;
  long local_7e0;
  int *local_7d8;
  undefined **local_7c8;
  long local_7c0;
  int *local_7b8;
  undefined4 local_7b0;
  undefined **local_7a8;
  long local_7a0;
  int *local_798;
  undefined **local_788;
  long local_780;
  int *local_778;
  undefined4 local_770;
  undefined **local_768;
  long local_760;
  int *local_758;
  undefined **local_748;
  long local_740;
  int *local_738;
  undefined4 local_730;
  undefined **local_728;
  long local_720;
  int *local_718;
  undefined **local_708;
  long local_700;
  int *local_6f8;
  undefined4 local_6f0;
  undefined **local_6e8;
  long local_6e0;
  int *local_6d8;
  undefined **local_6c8;
  long local_6c0;
  int *local_6b8;
  undefined **local_6a8;
  long local_6a0;
  int *local_698;
  undefined4 local_690;
  undefined **local_688;
  long local_680;
  int *local_678;
  undefined **local_668;
  long local_660;
  int *local_658;
  undefined4 local_650;
  undefined **local_648;
  long local_640;
  int *local_638;
  undefined **local_628;
  long local_620;
  int *local_618;
  undefined4 local_610;
  undefined **local_608;
  long local_600;
  int *local_5f8;
  undefined **local_5e8;
  long local_5e0;
  int *local_5d8;
  undefined4 local_5d0;
  undefined **local_5c8;
  long local_5c0;
  int *local_5b8;
  undefined **local_5a8;
  long local_5a0;
  int *local_598;
  undefined4 local_590;
  undefined **local_588;
  long local_580;
  int *local_578;
  undefined **local_568;
  long local_560;
  int *local_558;
  undefined4 local_550;
  undefined **local_548;
  long local_540;
  int *local_538;
  undefined **local_528;
  long local_520;
  int *local_518;
  undefined4 local_510;
  undefined **local_508;
  long local_500;
  int *local_4f8;
  undefined **local_4e8;
  long local_4e0;
  int *local_4d8;
  undefined4 local_4d0;
  undefined **local_4c8;
  long local_4c0;
  int *local_4b8;
  undefined **local_4a8;
  long local_4a0;
  int *local_498;
  undefined4 local_490;
  undefined **local_488;
  long local_480;
  int *local_478;
  undefined **local_468;
  long local_460;
  int *local_458;
  undefined **local_448;
  long local_440;
  int *local_438;
  undefined4 local_430;
  undefined4 local_428;
  undefined4 local_424;
  undefined4 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  undefined4 local_414;
  undefined4 local_410;
  undefined4 local_40c;
  undefined4 local_408;
  undefined4 local_404;
  undefined4 local_400;
  undefined4 local_3fc;
  undefined4 local_3f8;
  undefined4 local_3f4;
  undefined4 local_3f0;
  undefined4 local_3ec;
  undefined4 local_3e8;
  undefined4 local_3e4;
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined4 local_3d8;
  undefined4 local_3d4;
  undefined4 local_3d0;
  undefined4 local_3cc;
  undefined4 local_3c8;
  undefined4 local_3c4;
  undefined4 local_3c0;
  undefined4 local_3bc;
  undefined4 local_3b8;
  undefined4 local_3b4;
  undefined4 local_3b0;
  undefined4 local_3ac;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  undefined4 local_38c;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined4 local_340;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_320;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2f8;
  undefined4 local_2f4;
  undefined4 local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
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
  long local_98 [2];
  long local_88 [2];
  long local_78 [5];
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

  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 0056367b to 0056367f has its CatchHandler @ 0056640f */
  std::string::string((string *)local_78,"Wireframe",local_39);
                    /* try { // try from 005636a4 to 005636a6 has its CatchHandler @ 005663ff */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_468,plVar6,(string *)local_78,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_430 = 0;
  local_448 = &PTR__MaterialPtr_00fa44d0;
  local_440 = local_460;
  local_438 = local_458;
  if (local_458 != (int *)0x0) {
    *local_458 = *local_458 + 1;
  }
  local_468 = &PTR__SharedPtr_00fa45d0;
  if ((local_458 != (int *)0x0) && (iVar1 = *local_458, *local_458 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565ee8 to 00565eec has its CatchHandler @ 00566b97 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_468);
  }
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_78[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  *(undefined1 *)(local_440 + 0xf0) = 0;
                    /* try { // try from 00563741 to 0056380b has its CatchHandler @ 00566460 */
  uVar5 = Ogre::Material::getTechnique((ushort)local_440);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setPolygonMode(pCVar7,2);
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
  local_238 = 0x3f800000;
  local_234 = 0x3f800000;
  local_230 = 0x3f800000;
  local_22c = 0x3dcccccd;
  Ogre::Pass::setDiffuse(pCVar7);
  local_248 = 0x3f800000;
  local_244 = 0x3f800000;
  local_240 = 0x3f800000;
  local_23c = 0x3dcccccd;
  Ogre::Pass::setAmbient(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_440,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 0056382e to 00563832 has its CatchHandler @ 00566458 */
  std::string::string((string *)local_88,"WireframeOverlay",&local_3a);
                    /* try { // try from 00563857 to 00563859 has its CatchHandler @ 00566bee */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_488,plVar6,(string *)local_88,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  if (*(long *)(this + 0x220) != local_480) {
    piVar3 = *(int **)(this + 0x228);
    if ((piVar3 != (int *)0x0) && (iVar1 = *piVar3, *piVar3 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565f19 to 00565f1b has its CatchHandler @ 00566bbc */
      (**(code **)(*(long *)(this + 0x218) + 0x10))(this + 0x218);
    }
    *(long *)(this + 0x220) = local_480;
    *(int **)(this + 0x228) = local_478;
    if (local_478 != (int *)0x0) {
      *local_478 = *local_478 + 1;
    }
  }
  local_488 = &PTR__SharedPtr_00fa45d0;
  if ((local_478 != (int *)0x0) && (iVar1 = *local_478, *local_478 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565ed8 to 00565edc has its CatchHandler @ 00566bee */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_488);
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_88[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  *(undefined1 *)(*(long *)(this + 0x220) + 0xf0) = 0;
                    /* try { // try from 00563900 to 005639fc has its CatchHandler @ 00566460 */
  uVar5 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x220));
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setPolygonMode(pCVar7,2);
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
  local_258 = 0x3f800000;
  local_254 = 0x3f800000;
  local_250 = 0x3f800000;
  local_24c = 0x3e4ccccd;
  Ogre::Pass::setDiffuse(pCVar7);
  local_268 = 0x3f800000;
  local_264 = 0x3f800000;
  local_260 = 0x3f800000;
  local_25c = 0x3e4ccccd;
  Ogre::Pass::setAmbient(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(*(undefined8 *)(this + 0x220),0);
  uVar8 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x220));
  Ogre::Technique::setDepthFunction(uVar8,3);
  bVar4 = (bool)Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x220));
  Ogre::Technique::setDepthWriteEnabled(bVar4);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00563a1f to 00563a23 has its CatchHandler @ 00566a19 */
  std::string::string((string *)local_98,"WeaponTrail",&local_3b);
                    /* try { // try from 00563a48 to 00563a4a has its CatchHandler @ 00566a09 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_4c8,plVar6,(string *)local_98,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_490 = 0;
  local_4a8 = &PTR__MaterialPtr_00fa44d0;
  local_4a0 = local_4c0;
  local_498 = local_4b8;
  if (local_4b8 != (int *)0x0) {
    *local_4b8 = *local_4b8 + 1;
  }
  local_4c8 = &PTR__SharedPtr_00fa45d0;
  if ((local_4b8 != (int *)0x0) && (iVar1 = *local_4b8, *local_4b8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565ec8 to 00565ecc has its CatchHandler @ 00566b82 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_4c8);
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_98[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  *(undefined1 *)(local_4a0 + 0xf0) = 0;
                    /* try { // try from 00563ae0 to 00563b4c has its CatchHandler @ 005663f7 */
  Ogre::Material::setLightingEnabled(SUB81(local_4a0,0));
  uVar5 = Ogre::Material::getTechnique((ushort)local_4a0);
  psVar9 = (string *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(psVar9,0));
  Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
  Ogre::Pass::setDepthWriteEnabled(SUB81(psVar9,0));
  Ogre::Material::setSceneBlending(local_4a0,2);
  Ogre::Material::setCullingMode(local_4a0,1);
  local_8d8 = &DAT_01423a38;
                    /* try { // try from 00563b65 to 00563b69 has its CatchHandler @ 005663e7 */
  std::string::string((string *)&local_8d0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00563b74 to 00563b78 has its CatchHandler @ 00566ad3 */
  std::wstring::wstring((wstring_conflict *)&local_8c8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_8c0 = 4;
  local_8bc = 3;
  local_8b8 = &DAT_01423a38;
  local_8b0 = 0;
                    /* try { // try from 00563baf to 00563bb3 has its CatchHandler @ 00566ad1 */
  std::wstring::wstring
            ((wstring_conflict *)local_a8,L"media/sharedTextures/weapontrail.dds",&local_3c);
                    /* try { // try from 00563bb4 to 00563bd1 has its CatchHandler @ 00566ab6 */
  pCVar10 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar10,(wstring_conflict *)local_a8,(CFileInfo *)&local_8d8,false,true,false);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_a8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 00563bf5 to 00563bfe has its CatchHandler @ 00566a88 */
  Ogre::Pass::createTextureUnitState(psVar9,(ushort)&local_8d0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00563c26 to 00563c2a has its CatchHandler @ 00566a80 */
  std::string::string((string *)local_b8,"WeaponTrailEvil",&local_3d);
                    /* try { // try from 00563c4f to 00563c52 has its CatchHandler @ 00566a6c */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_508,plVar6,(string *)local_b8,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_4d0 = 0;
  local_4e8 = &PTR__MaterialPtr_00fa44d0;
  local_4e0 = local_500;
  local_4d8 = local_4f8;
  if (local_4f8 != (int *)0x0) {
    *local_4f8 = *local_4f8 + 1;
  }
  local_508 = &PTR__SharedPtr_00fa45d0;
  if ((local_4f8 != (int *)0x0) && (iVar1 = *local_4f8, *local_4f8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565eb8 to 00565ebc has its CatchHandler @ 0056681b */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_508);
  }
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_b8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  *(undefined1 *)(local_4e0 + 0xf0) = 0;
                    /* try { // try from 00563ce8 to 00563d54 has its CatchHandler @ 0056670e */
  Ogre::Material::setLightingEnabled(SUB81(local_4e0,0));
  uVar5 = Ogre::Material::getTechnique((ushort)local_4e0);
  psVar9 = (string *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(psVar9,0));
  Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
  Ogre::Pass::setDepthWriteEnabled(SUB81(psVar9,0));
  Ogre::Material::setSceneBlending(local_4e0,2);
  Ogre::Material::setCullingMode(local_4e0,1);
                    /* try { // try from 00563d6d to 00563d71 has its CatchHandler @ 00566701 */
  std::wstring::wstring
            ((wstring_conflict *)local_c8,L"media/sharedTextures/weapontrailevil.dds",&local_3e);
                    /* try { // try from 00563d72 to 00563d8f has its CatchHandler @ 005666f1 */
  pCVar10 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar10,(wstring_conflict *)local_c8,(CFileInfo *)&local_8d8,false,true,false);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_c8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00563db4 to 00563dbd has its CatchHandler @ 0056670e */
  Ogre::Pass::createTextureUnitState(psVar9,(ushort)&local_8d0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00563de5 to 00563de9 has its CatchHandler @ 005666bd */
  std::string::string((string *)local_d8,"ArrowTrail",&local_3f);
                    /* try { // try from 00563e0e to 00563e11 has its CatchHandler @ 00566a64 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_548,plVar6,(string *)local_d8,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_510 = 0;
  local_528 = &PTR__MaterialPtr_00fa44d0;
  local_520 = local_540;
  local_518 = local_538;
  if (local_538 != (int *)0x0) {
    *local_538 = *local_538 + 1;
  }
  local_548 = &PTR__SharedPtr_00fa45d0;
  if ((local_538 != (int *)0x0) && (iVar1 = *local_538, *local_538 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565ea8 to 00565eac has its CatchHandler @ 005667fe */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_548);
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_d8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  *(undefined1 *)(local_520 + 0xf0) = 0;
                    /* try { // try from 00563ea7 to 00563f3a has its CatchHandler @ 00566962 */
  Ogre::Material::setLightingEnabled(SUB81(local_520,0));
  uVar5 = Ogre::Material::getTechnique((ushort)local_520);
  psVar9 = (string *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(psVar9,0));
  Ogre::Pass::setSelfIllumination(0.0,0.0,0.0);
  Ogre::Pass::setDepthWriteEnabled(SUB81(psVar9,0));
  Ogre::Pass::setFog(DAT_00fa4828,0,DAT_00fa47fc,psVar9,1,0);
  Ogre::Material::setSceneBlending(local_520,2);
  Ogre::Material::setCullingMode(local_520,1);
                    /* try { // try from 00563f53 to 00563f57 has its CatchHandler @ 00566955 */
  std::wstring::wstring
            ((wstring_conflict *)local_e8,L"media/sharedTextures/arrowtrail.dds",&local_40);
                    /* try { // try from 00563f58 to 00563f75 has its CatchHandler @ 00566944 */
  pCVar10 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar10,(wstring_conflict *)local_e8,(CFileInfo *)&local_8d8,false,true,false);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_e8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
                    /* try { // try from 00563f9a to 00563fa3 has its CatchHandler @ 00566962 */
  Ogre::Pass::createTextureUnitState(psVar9,(ushort)&local_8d0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00563fcb to 00563fcf has its CatchHandler @ 00566910 */
  std::string::string((string *)local_f8,"ArrowTrailReflect",&local_41);
                    /* try { // try from 00563ff4 to 00563ff7 has its CatchHandler @ 005668fc */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_588,plVar6,(string *)local_f8,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_550 = 0;
  local_568 = &PTR__MaterialPtr_00fa44d0;
  local_560 = local_580;
  local_558 = local_578;
  if (local_578 != (int *)0x0) {
    *local_578 = *local_578 + 1;
  }
  local_588 = &PTR__SharedPtr_00fa45d0;
  if ((local_578 != (int *)0x0) && (iVar1 = *local_578, *local_578 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e98 to 00565e9c has its CatchHandler @ 005667e1 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_588);
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_f8[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  *(undefined1 *)(local_560 + 0xf0) = 0;
                    /* try { // try from 0056408d to 0056419d has its CatchHandler @ 00566a36 */
  Ogre::Material::setLightingEnabled(SUB81(local_560,0));
  uVar5 = Ogre::Material::getTechnique((ushort)local_560);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
  local_278 = 0x3f800000;
  local_274 = 0;
  local_270 = 0;
  local_26c = 0x3f800000;
  Ogre::Pass::setAmbient(pCVar7);
  local_288 = 0x3f800000;
  local_284 = 0;
  local_280 = 0;
  local_27c = 0x3f800000;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setFog(DAT_00fa4828,0,DAT_00fa47fc,pCVar7,1,0);
  Ogre::Material::setSceneBlending(local_560,2);
  Ogre::Material::setCullingMode(local_560,1);
                    /* try { // try from 005641b6 to 005641ba has its CatchHandler @ 00566a2e */
  std::wstring::wstring
            ((wstring_conflict *)local_108,L"media/sharedTextures/arrowtrailreflect.dds",&local_42);
                    /* try { // try from 005641bb to 005641d8 has its CatchHandler @ 00566a1e */
  pCVar10 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (pCVar10,(wstring_conflict *)local_108,(CFileInfo *)&local_8d8,false,true,false);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_108[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
                    /* try { // try from 005641fd to 00564206 has its CatchHandler @ 00566a36 */
  Ogre::Pass::createTextureUnitState((string *)pCVar7,(ushort)&local_8d0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00564229 to 0056422d has its CatchHandler @ 00566ae5 */
  std::string::string((string *)local_118,"lightBlue",&local_43);
                    /* try { // try from 00564252 to 00564254 has its CatchHandler @ 005668f4 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_5c8,plVar6,(string *)local_118,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_590 = 0;
  local_5a8 = &PTR__MaterialPtr_00fa44d0;
  local_5a0 = local_5c0;
  local_598 = local_5b8;
  if (local_5b8 != (int *)0x0) {
    *local_5b8 = *local_5b8 + 1;
  }
  local_5c8 = &PTR__SharedPtr_00fa45d0;
  if ((local_5b8 != (int *)0x0) && (iVar1 = *local_5b8, *local_5b8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e88 to 00565e8c has its CatchHandler @ 005667c4 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_5c8);
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_118[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  *(undefined1 *)(local_5a0 + 0xf0) = 0;
                    /* try { // try from 005642ea to 005643b4 has its CatchHandler @ 00566675 */
  uVar5 = Ogre::Material::getTechnique((ushort)local_5a0);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setSelfIllumination(0.0,0.0,DAT_00fa47fc);
  local_298 = 0x3e4ccccd;
  local_294 = 0x3e4ccccd;
  local_290 = 0x3f800000;
  local_28c = 0x3e99999a;
  Ogre::Pass::setAmbient(pCVar7);
  local_2a8 = 0x3e4ccccd;
  local_2a4 = 0x3e4ccccd;
  local_2a0 = 0x3f800000;
  local_29c = 0x3e99999a;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_5a0,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 005643d7 to 005643db has its CatchHandler @ 0056666d */
  std::string::string((string *)local_128,"lightYellow",&local_44);
                    /* try { // try from 00564400 to 00564402 has its CatchHandler @ 0056665d */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_608,plVar6,(string *)local_128,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_5d0 = 0;
  local_5e8 = &PTR__MaterialPtr_00fa44d0;
  local_5e0 = local_600;
  local_5d8 = local_5f8;
  if (local_5f8 != (int *)0x0) {
    *local_5f8 = *local_5f8 + 1;
  }
  local_608 = &PTR__SharedPtr_00fa45d0;
  if ((local_5f8 != (int *)0x0) && (iVar1 = *local_5f8, *local_5f8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e78 to 00565e7c has its CatchHandler @ 005667af */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_608);
  }
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_128[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  *(undefined1 *)(local_5e0 + 0xf0) = 0;
                    /* try { // try from 00564498 to 00564562 has its CatchHandler @ 0056665b */
  uVar5 = Ogre::Material::getTechnique((ushort)local_5e0);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,0.0);
  local_2b8 = 0x3e4ccccd;
  local_2b4 = 0x3e4ccccd;
  local_2b0 = 0x3f800000;
  local_2ac = 0x3e99999a;
  Ogre::Pass::setAmbient(pCVar7);
  local_2c8 = 0x3e4ccccd;
  local_2c4 = 0x3e4ccccd;
  local_2c0 = 0x3f800000;
  local_2bc = 0x3e99999a;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_5e0,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00564585 to 00564589 has its CatchHandler @ 00566653 */
  std::string::string((string *)local_138,"lightOrange",&local_45);
                    /* try { // try from 005645ae to 005645b0 has its CatchHandler @ 00566601 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_648,plVar6,(string *)local_138,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_610 = 0;
  local_628 = &PTR__MaterialPtr_00fa44d0;
  local_620 = local_640;
  local_618 = local_638;
  if (local_638 != (int *)0x0) {
    *local_638 = *local_638 + 1;
  }
  local_648 = &PTR__SharedPtr_00fa45d0;
  if ((local_638 != (int *)0x0) && (iVar1 = *local_638, *local_638 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e68 to 00565e6c has its CatchHandler @ 0056679a */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_648);
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_138[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  *(undefined1 *)(local_620 + 0xf0) = 0;
                    /* try { // try from 00564646 to 00564715 has its CatchHandler @ 00566101 */
  uVar5 = Ogre::Material::getTechnique((ushort)local_620);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa482c,0.0);
  local_2d8 = 0x3e4ccccd;
  local_2d4 = 0x3e4ccccd;
  local_2d0 = 0x3f800000;
  local_2cc = 0x3e99999a;
  Ogre::Pass::setAmbient(pCVar7);
  local_2e8 = 0x3e4ccccd;
  local_2e4 = 0x3e4ccccd;
  local_2e0 = 0x3f800000;
  local_2dc = 0x3e99999a;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_620,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00564738 to 0056473c has its CatchHandler @ 00566345 */
  std::string::string((string *)local_148,"WireframeBlue",&local_46);
                    /* try { // try from 00564761 to 00564763 has its CatchHandler @ 00566335 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_688,plVar6,(string *)local_148,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_650 = 0;
  local_668 = &PTR__MaterialPtr_00fa44d0;
  local_660 = local_680;
  local_658 = local_678;
  if (local_678 != (int *)0x0) {
    *local_678 = *local_678 + 1;
  }
  local_688 = &PTR__SharedPtr_00fa45d0;
  if ((local_678 != (int *)0x0) && (iVar1 = *local_678, *local_678 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e59 to 00565e5d has its CatchHandler @ 00566785 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_688);
  }
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_148[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  *(undefined1 *)(local_660 + 0xf0) = 0;
                    /* try { // try from 005647f9 to 005648d0 has its CatchHandler @ 005666ab */
  uVar5 = Ogre::Material::getTechnique((ushort)local_660);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setPolygonMode(pCVar7,2);
  Ogre::Pass::setSelfIllumination(0.0,0.0,DAT_00fa47fc);
  local_2f8 = 0x3e4ccccd;
  local_2f4 = 0x3e4ccccd;
  local_2f0 = 0x3f800000;
  local_2ec = 0x3e99999a;
  Ogre::Pass::setAmbient(pCVar7);
  local_308 = 0x3e4ccccd;
  local_304 = 0x3e4ccccd;
  local_300 = 0x3f800000;
  local_2fc = 0x3e99999a;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_660,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 005648f3 to 005648f7 has its CatchHandler @ 005666a3 */
  std::string::string((string *)local_158,"WireframeYellow",&local_47);
                    /* try { // try from 0056491c to 0056491e has its CatchHandler @ 005661c0 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_6c8,plVar6,(string *)local_158,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_690 = 0;
  local_6a8 = &PTR__MaterialPtr_00fa44d0;
  local_6a0 = local_6c0;
  local_698 = local_6b8;
  if (local_6b8 != (int *)0x0) {
    *local_6b8 = *local_6b8 + 1;
  }
  local_6c8 = &PTR__SharedPtr_00fa45d0;
  if ((local_6b8 != (int *)0x0) && (iVar1 = *local_6b8, *local_6b8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e4c to 00565e50 has its CatchHandler @ 00566770 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_6c8);
  }
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_158[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  *(undefined1 *)(local_6a0 + 0xf0) = 0;
                    /* try { // try from 005649b4 to 00564a8b has its CatchHandler @ 005668bb */
  uVar5 = Ogre::Material::getTechnique((ushort)local_6a0);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setPolygonMode(pCVar7,2);
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,0.0);
  local_318 = 0x3f800000;
  local_314 = 0x3f800000;
  local_310 = 0x3e4ccccd;
  local_30c = 0x3e99999a;
  Ogre::Pass::setDiffuse(pCVar7);
  local_328 = 0x3f800000;
  local_324 = 0x3f800000;
  local_320 = 0x3e4ccccd;
  local_31c = 0x3e99999a;
  Ogre::Pass::setAmbient(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Material::setSceneBlending(local_6a0,0);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00564aae to 00564ab2 has its CatchHandler @ 005668b6 */
  std::string::string((string *)local_168,"RenderBehind",&local_48);
                    /* try { // try from 00564ad7 to 00564ad9 has its CatchHandler @ 005668a6 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_6e8,plVar6,(string *)local_168,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  if (*(long *)(this + 0x200) != local_6e0) {
    piVar3 = *(int **)(this + 0x208);
    if ((piVar3 != (int *)0x0) && (iVar1 = *piVar3, *piVar3 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565f03 to 00565f05 has its CatchHandler @ 00566bac */
      (**(code **)(*(long *)(this + 0x1f8) + 0x10))(this + 0x1f8);
    }
    *(long *)(this + 0x200) = local_6e0;
    *(int **)(this + 0x208) = local_6d8;
    if (local_6d8 != (int *)0x0) {
      *local_6d8 = *local_6d8 + 1;
    }
  }
  local_6e8 = &PTR__SharedPtr_00fa45d0;
  if ((local_6d8 != (int *)0x0) && (iVar1 = *local_6d8, *local_6d8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e3f to 00565e43 has its CatchHandler @ 005668a6 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_6e8);
  }
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_168[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
  *(undefined1 *)(*(long *)(this + 0x200) + 0xf0) = 0;
                    /* try { // try from 00564b80 to 00564db0 has its CatchHandler @ 005668bb */
  uVar5 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x200));
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setSelfIllumination(DAT_00fa4830,DAT_00fa4830,DAT_00fa4810);
  local_338 = 0;
  local_334 = 0;
  local_330 = 0;
  local_32c = 0;
  Ogre::Pass::setAmbient(pCVar7);
  local_348 = 0;
  local_344 = 0;
  local_340 = 0;
  local_33c = 0;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  uVar8 = Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x200));
  Ogre::Technique::setDepthFunction(uVar8,7);
  bVar4 = (bool)Ogre::Material::getTechnique((ushort)*(undefined8 *)(this + 0x200));
  Ogre::Technique::setDepthWriteEnabled(bVar4);
  Ogre::Pass::setSceneBlending(pCVar7,0,1);
  Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
  Ogre::Material::setSceneBlending(*(undefined8 *)(this + 0x200),1);
  Ogre::Material::createTechnique();
  pCVar7 = (ColourValue *)Ogre::Technique::createPass();
  Ogre::Pass::setSelfIllumination(DAT_00fa4830,DAT_00fa4830,DAT_00fa4810);
  local_358 = 0;
  local_354 = 0;
  local_350 = 0;
  local_34c = 0;
  Ogre::Pass::setAmbient(pCVar7);
  local_368 = 0;
  local_364 = 0;
  local_360 = 0;
  local_35c = 0;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setSceneBlending(pCVar7,0,1);
  Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
  Ogre::Material::compile(SUB81(*(undefined8 *)(this + 0x200),0));
  uVar11 = 0;
  do {
    fVar12 = DAT_00fa4810 - (float)uVar11 * _DAT_00fa4834;
    plVar6 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar2 = *(code **)(*plVar6 + 0x28);
    STRINGS::GetValueAsString((uint)local_178);
                    /* try { // try from 00564dc6 to 00564dca has its CatchHandler @ 005664dd */
    std::operator+((char *)local_188,(string *)"RenderShadow");
                    /* try { // try from 00564df1 to 00564df3 has its CatchHandler @ 00566491 */
    (*pcVar2)(&local_728,plVar6,local_188,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0
              ,0,0);
    local_6f0 = 0;
    local_708 = &PTR__MaterialPtr_00fa44d0;
    local_700 = local_720;
    local_6f8 = local_718;
    if (local_718 != (int *)0x0) {
      *local_718 = *local_718 + 1;
    }
    local_728 = &PTR__SharedPtr_00fa45d0;
    if ((local_718 != (int *)0x0) && (iVar1 = *local_718, *local_718 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 00564e5f to 00564e63 has its CatchHandler @ 00566462 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_728);
    }
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_188[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_178[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    *(undefined1 *)(local_700 + 0xf0) = 0;
                    /* try { // try from 00564ea7 to 00564f81 has its CatchHandler @ 005663e2 */
    uVar5 = Ogre::Material::getTechnique((ushort)local_700);
    pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
    Ogre::Pass::setSelfIllumination(fVar12,fVar12,fVar12);
    local_378 = 0;
    local_374 = 0;
    local_370 = 0;
    local_36c = 0x3f800000;
    Ogre::Pass::setAmbient(pCVar7);
    local_388 = 0;
    local_384 = 0;
    local_380 = 0;
    local_37c = 0x3f800000;
    Ogre::Pass::setDiffuse(pCVar7);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
    plVar6 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar2 = *(code **)(*plVar6 + 0x28);
    STRINGS::GetValueAsString((uint)local_198);
                    /* try { // try from 00564f97 to 00564f9b has its CatchHandler @ 005663d8 */
    std::operator+((char *)local_1a8,(string *)"RenderShadowSkinned");
                    /* try { // try from 00564fc2 to 00564fc4 has its CatchHandler @ 005663d3 */
    (*pcVar2)(&local_768,plVar6,local_1a8,&Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0
              ,0,0);
    local_730 = 0;
    local_748 = &PTR__MaterialPtr_00fa44d0;
    local_740 = local_760;
    local_738 = local_758;
    if (local_758 != (int *)0x0) {
      *local_758 = *local_758 + 1;
    }
    local_768 = &PTR__SharedPtr_00fa45d0;
    if ((local_758 != (int *)0x0) && (iVar1 = *local_758, *local_758 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 00565030 to 00565034 has its CatchHandler @ 005663a7 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_768);
    }
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1a8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_198[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
    *(undefined1 *)(local_740 + 0xf0) = 0;
                    /* try { // try from 00565078 to 0056516c has its CatchHandler @ 005663a2 */
    uVar5 = Ogre::Material::getTechnique((ushort)local_740);
    pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
    Ogre::Pass::setSelfIllumination(fVar12,fVar12,fVar12);
    local_398 = 0;
    local_394 = 0;
    local_390 = 0;
    local_38c = 0x3f800000;
    Ogre::Pass::setAmbient(pCVar7);
    local_3a8 = 0;
    local_3a4 = 0;
    local_3a0 = 0;
    local_39c = 0x3f800000;
    Ogre::Pass::setDiffuse(pCVar7);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
    Ogre::Material::compile(SUB81(local_740,0));
    plVar6 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar2 = *(code **)(*plVar6 + 0x28);
    STRINGS::GetValueAsString((uint)local_1b8);
                    /* try { // try from 00565180 to 00565184 has its CatchHandler @ 0056639b */
    std::operator+((char *)local_1c8,(string *)"RenderShadowSkinnedThree");
                    /* try { // try from 005651a9 to 005651ac has its CatchHandler @ 00566396 */
    (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_7a8,plVar6,local_1c8,
              &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
    local_770 = 0;
    local_788 = &PTR__MaterialPtr_00fa44d0;
    local_780 = local_7a0;
    local_778 = local_798;
    if (local_798 != (int *)0x0) {
      *local_798 = *local_798 + 1;
    }
    local_7a8 = &PTR__SharedPtr_00fa45d0;
    if ((local_798 != (int *)0x0) && (iVar1 = *local_798, *local_798 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 00565213 to 00565217 has its CatchHandler @ 0056634a */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_7a8);
    }
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1c8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1b8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    *(undefined1 *)(local_780 + 0xf0) = 0;
                    /* try { // try from 0056525b to 0056534f has its CatchHandler @ 00566453 */
    uVar5 = Ogre::Material::getTechnique((ushort)local_780);
    pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
    Ogre::Pass::setSelfIllumination(fVar12,fVar12,fVar12);
    local_3b8 = 0;
    local_3b4 = 0;
    local_3b0 = 0;
    local_3ac = 0x3f800000;
    Ogre::Pass::setAmbient(pCVar7);
    local_3c8 = 0;
    local_3c4 = 0;
    local_3c0 = 0;
    local_3bc = 0x3f800000;
    Ogre::Pass::setDiffuse(pCVar7);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
    Ogre::Material::compile(SUB81(local_780,0));
    plVar6 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar2 = *(code **)(*plVar6 + 0x28);
    STRINGS::GetValueAsString((uint)local_1d8);
                    /* try { // try from 00565363 to 00565367 has its CatchHandler @ 0056644e */
    std::operator+((char *)local_1e8,(string *)"RenderShadowSkinnedTwo");
                    /* try { // try from 0056538c to 0056538f has its CatchHandler @ 00566449 */
    (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_7e8,plVar6,local_1e8,
              &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
    local_7b0 = 0;
    local_7c8 = &PTR__MaterialPtr_00fa44d0;
    local_7c0 = local_7e0;
    local_7b8 = local_7d8;
    if (local_7d8 != (int *)0x0) {
      *local_7d8 = *local_7d8 + 1;
    }
    local_7e8 = &PTR__SharedPtr_00fa45d0;
    if ((local_7d8 != (int *)0x0) && (iVar1 = *local_7d8, *local_7d8 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 005653f6 to 005653fa has its CatchHandler @ 00566417 */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_7e8);
    }
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1e8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1d8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
    *(undefined1 *)(local_7c0 + 0xf0) = 0;
                    /* try { // try from 0056543e to 00565532 has its CatchHandler @ 00566b64 */
    uVar5 = Ogre::Material::getTechnique((ushort)local_7c0);
    pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
    Ogre::Pass::setSelfIllumination(fVar12,fVar12,fVar12);
    local_3d8 = 0;
    local_3d4 = 0;
    local_3d0 = 0;
    local_3cc = 0x3f800000;
    Ogre::Pass::setAmbient(pCVar7);
    local_3e8 = 0;
    local_3e4 = 0;
    local_3e0 = 0;
    local_3dc = 0x3f800000;
    Ogre::Pass::setDiffuse(pCVar7);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
    Ogre::Material::compile(SUB81(local_7c0,0));
    plVar6 = (long *)Ogre::MaterialManager::getSingleton();
    pcVar2 = *(code **)(*plVar6 + 0x28);
    STRINGS::GetValueAsString((uint)local_1f8);
                    /* try { // try from 00565546 to 0056554a has its CatchHandler @ 00566b16 */
    std::operator+((char *)local_208,(string *)"RenderShadowSkinnedOne");
                    /* try { // try from 0056556f to 00565572 has its CatchHandler @ 00566be9 */
    (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_828,plVar6,local_208,
              &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
    local_7f0 = 0;
    local_808 = &PTR__MaterialPtr_00fa44d0;
    local_800 = local_820;
    local_7f8 = local_818;
    if (local_818 != (int *)0x0) {
      *local_818 = *local_818 + 1;
    }
    local_828 = &PTR__SharedPtr_00fa45d0;
    if ((local_818 != (int *)0x0) && (iVar1 = *local_818, *local_818 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 005655d9 to 005655dd has its CatchHandler @ 00566bcc */
      Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_828);
    }
    if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_208[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_1f8[0] + -8);
      iVar1 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar1 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
    *(undefined1 *)(local_800 + 0xf0) = 0;
                    /* try { // try from 00565621 to 005656ee has its CatchHandler @ 0056658f */
    uVar5 = Ogre::Material::getTechnique((ushort)local_800);
    pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
    Ogre::Pass::setSelfIllumination(fVar12,fVar12,fVar12);
    local_3f8 = 0;
    local_3f4 = 0;
    local_3f0 = 0;
    local_3ec = 0x3f800000;
    Ogre::Pass::setAmbient(pCVar7);
    local_408 = 0;
    local_404 = 0;
    local_400 = 0;
    local_3fc = 0x3f800000;
    Ogre::Pass::setDiffuse(pCVar7);
    Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
    Ogre::Pass::setMaxSimultaneousLights((ushort)pCVar7);
    Ogre::Material::compile(SUB81(local_800,0));
    local_808 = &PTR__SharedPtr_00fa4590;
    if ((local_7f8 != (int *)0x0) && (iVar1 = *local_7f8, *local_7f8 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 00565723 to 00565725 has its CatchHandler @ 00566b64 */
      (*(code *)PTR_destroy_00fa45a0)(&local_808);
    }
    local_7c8 = &PTR__SharedPtr_00fa4590;
    if ((local_7b8 != (int *)0x0) && (iVar1 = *local_7b8, *local_7b8 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 0056575a to 0056575c has its CatchHandler @ 00566453 */
      (*(code *)PTR_destroy_00fa45a0)(&local_7c8);
    }
    local_788 = &PTR__SharedPtr_00fa4590;
    if ((local_778 != (int *)0x0) && (iVar1 = *local_778, *local_778 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 00565791 to 00565793 has its CatchHandler @ 005663a2 */
      (*(code *)PTR_destroy_00fa45a0)(&local_788);
    }
    local_748 = &PTR__SharedPtr_00fa4590;
    if ((local_738 != (int *)0x0) && (iVar1 = *local_738, *local_738 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 005657c8 to 005657ca has its CatchHandler @ 005663e2 */
      (*(code *)PTR_destroy_00fa45a0)(&local_748);
    }
    local_708 = &PTR__SharedPtr_00fa4590;
    if ((local_6f8 != (int *)0x0) && (iVar1 = *local_6f8, *local_6f8 = iVar1 + -1, iVar1 + -1 == 0))
    {
                    /* try { // try from 005657ff to 00565814 has its CatchHandler @ 005668bb */
      (*(code *)PTR_destroy_00fa45a0)(&local_708);
    }
    uVar11 = uVar11 + 1;
  } while (uVar11 != 0x40);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00565837 to 0056583b has its CatchHandler @ 00566587 */
  std::string::string((string *)local_218,"Points",&local_49);
                    /* try { // try from 00565860 to 00565862 has its CatchHandler @ 005664c2 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_868,plVar6,(string *)local_218,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_830 = 0;
  local_848 = &PTR__MaterialPtr_00fa44d0;
  local_840 = local_860;
  local_838 = local_858;
  if (local_858 != (int *)0x0) {
    *local_858 = *local_858 + 1;
  }
  local_868 = &PTR__SharedPtr_00fa45d0;
  if ((local_858 != (int *)0x0) && (iVar1 = *local_858, *local_858 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e32 to 00565e36 has its CatchHandler @ 00566750 */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_868);
  }
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_218[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
  *(undefined1 *)(local_840 + 0xf0) = 0;
                    /* try { // try from 005658f8 to 00565931 has its CatchHandler @ 005665d3 */
  uVar5 = Ogre::Material::getTechnique((ushort)local_840);
  uVar8 = Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setPolygonMode(uVar8,1);
  Ogre::Pass::setSelfIllumination(DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
  plVar6 = (long *)Ogre::MaterialManager::getSingleton();
  pcVar2 = *(code **)(*plVar6 + 0x28);
                    /* try { // try from 00565954 to 00565958 has its CatchHandler @ 005665ce */
  std::string::string((string *)local_228,"FishingLine",&local_4a);
                    /* try { // try from 0056597a to 0056597c has its CatchHandler @ 005665b1 */
  (*pcVar2)((SharedPtr<Ogre::Resource> *)&local_8a8,plVar6,(string *)local_228,
            &Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,0,0,0);
  local_870 = 0;
  local_888 = &PTR__MaterialPtr_00fa44d0;
  local_880 = local_8a0;
  local_878 = local_898;
  if (local_898 != (int *)0x0) {
    *local_898 = *local_898 + 1;
  }
  local_8a8 = &PTR__SharedPtr_00fa45d0;
  if ((local_898 != (int *)0x0) && (iVar1 = *local_898, *local_898 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e25 to 00565e29 has its CatchHandler @ 0056673e */
    Ogre::SharedPtr<Ogre::Resource>::destroy((SharedPtr<Ogre::Resource> *)&local_8a8);
  }
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_228[0] + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  *(undefined1 *)(local_880 + 0xf0) = 0;
                    /* try { // try from 005659fa to 00565adb has its CatchHandler @ 00566b26 */
  uVar5 = Ogre::Material::getTechnique((ushort)local_880);
  pCVar7 = (ColourValue *)Ogre::Technique::getPass(uVar5);
  Ogre::Pass::setSelfIllumination(DAT_00fa4838,DAT_00fa4838,DAT_00fa4838);
  local_418 = 0;
  local_414 = 0;
  local_410 = 0;
  local_40c = 0x3f800000;
  Ogre::Pass::setAmbient(pCVar7);
  local_428 = 0;
  local_424 = 0;
  local_420 = 0;
  local_41c = 0x3f800000;
  Ogre::Pass::setDiffuse(pCVar7);
  Ogre::Pass::setDepthWriteEnabled(SUB81(pCVar7,0));
  Ogre::Pass::setDepthCheckEnabled(SUB81(pCVar7,0));
  bVar4 = (bool)Ogre::Material::getTechnique((ushort)local_880);
  Ogre::Technique::setDepthWriteEnabled(bVar4);
  Ogre::Material::setSceneBlending(local_880,1);
  local_888 = &PTR__SharedPtr_00fa4590;
  if ((local_878 != (int *)0x0) && (iVar1 = *local_878, *local_878 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e1a to 00565e1c has its CatchHandler @ 005665d3 */
    (*(code *)PTR_destroy_00fa45a0)(&local_888);
  }
  local_848 = &PTR__SharedPtr_00fa4590;
  if ((local_838 != (int *)0x0) && (iVar1 = *local_838, *local_838 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565e08 to 00565e0a has its CatchHandler @ 005668bb */
    (*(code *)PTR_destroy_00fa45a0)(&local_848);
  }
  local_6a8 = &PTR__SharedPtr_00fa4590;
  if ((local_698 != (int *)0x0) && (iVar1 = *local_698, *local_698 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565df0 to 00565df2 has its CatchHandler @ 005666ab */
    (*(code *)PTR_destroy_00fa45a0)(&local_6a8);
  }
  local_668 = &PTR__SharedPtr_00fa4590;
  if ((local_658 != (int *)0x0) && (iVar1 = *local_658, *local_658 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565dd8 to 00565dda has its CatchHandler @ 00566101 */
    (*(code *)PTR_destroy_00fa45a0)(&local_668);
  }
  local_628 = &PTR__SharedPtr_00fa4590;
  if ((local_618 != (int *)0x0) && (iVar1 = *local_618, *local_618 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565dc0 to 00565dc2 has its CatchHandler @ 0056665b */
    (*(code *)PTR_destroy_00fa45a0)(&local_628);
  }
  local_5e8 = &PTR__SharedPtr_00fa4590;
  if ((local_5d8 != (int *)0x0) && (iVar1 = *local_5d8, *local_5d8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565da8 to 00565daa has its CatchHandler @ 00566675 */
    (*(code *)PTR_destroy_00fa45a0)(&local_5e8);
  }
  local_5a8 = &PTR__SharedPtr_00fa4590;
  if ((local_598 != (int *)0x0) && (iVar1 = *local_598, *local_598 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565d90 to 00565d92 has its CatchHandler @ 00566a36 */
    (*(code *)PTR_destroy_00fa45a0)(&local_5a8);
  }
  local_568 = &PTR__SharedPtr_00fa4590;
  if ((local_558 != (int *)0x0) && (iVar1 = *local_558, *local_558 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565d78 to 00565d7a has its CatchHandler @ 00566962 */
    (*(code *)PTR_destroy_00fa45a0)(&local_568);
  }
  local_528 = &PTR__SharedPtr_00fa4590;
  if ((local_518 != (int *)0x0) && (iVar1 = *local_518, *local_518 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565d60 to 00565d62 has its CatchHandler @ 0056670e */
    (*(code *)PTR_destroy_00fa45a0)(&local_528);
  }
  local_4e8 = &PTR__SharedPtr_00fa4590;
  if ((local_4d8 != (int *)0x0) && (iVar1 = *local_4d8, *local_4d8 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565d48 to 00565d4a has its CatchHandler @ 00566a88 */
    (*(code *)PTR_destroy_00fa45a0)(&local_4e8);
  }
  if ((allocator *)(local_8b8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_8b8 + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_8b8 + -0x18));
    }
  }
  if ((allocator *)(local_8c8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_8c8 + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_8c8 + -0x18));
    }
  }
  if ((allocator *)(local_8d0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_8d0 + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_8d0 + -0x18));
    }
  }
  if ((allocator *)(local_8d8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_8d8 + -8);
    iVar1 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar1 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_8d8 + -0x18));
    }
  }
  local_4a8 = &PTR__SharedPtr_00fa4590;
  if ((local_498 != (int *)0x0) && (iVar1 = *local_498, *local_498 = iVar1 + -1, iVar1 + -1 == 0)) {
                    /* try { // try from 00565d33 to 00565d35 has its CatchHandler @ 00566460 */
    (*(code *)PTR_destroy_00fa45a0)(&local_4a8);
  }
  local_448 = &PTR__SharedPtr_00fa4590;
  if ((local_438 != (int *)0x0) && (iVar1 = *local_438, *local_438 = iVar1 + -1, iVar1 + -1 == 0)) {
    (*(code *)PTR_destroy_00fa45a0)(&local_448);
  }
  return;
}



/* address=00566c80
   symbol=CGame::setup */

/* WARNING: Removing unreachable block (ram,0x00567c5c) */
/* WARNING: Removing unreachable block (ram,0x00567c86) */
/* WARNING: Removing unreachable block (ram,0x00567b02) */
/* WARNING: Removing unreachable block (ram,0x00567bfa) */
/* WARNING: Removing unreachable block (ram,0x00567c32) */
/* WARNING: Removing unreachable block (ram,0x00567c08) */
/* WARNING: Removing unreachable block (ram,0x00567c6a) */
/* WARNING: Removing unreachable block (ram,0x00567cc8) */
/* WARNING: Removing unreachable block (ram,0x00567c4e) */
/* WARNING: Removing unreachable block (ram,0x00567c16) */
/* WARNING: Removing unreachable block (ram,0x00567c24) */
/* WARNING: Removing unreachable block (ram,0x00567c40) */
/* WARNING: Removing unreachable block (ram,0x00567c78) */
/* WARNING: Removing unreachable block (ram,0x00567c94) */
/* WARNING: Type propagation algorithm not settling */
/* CGame::setup(bool) */

ulong __thiscall CGame::setup(CGame *this,bool param_1)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  code *pcVar4;
  bool bVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  Root *this_00;
  undefined8 uVar9;
  ulong uVar10;
  CMasterResourceManager *this_01;
  long lVar11;
  CSoundManager *this_02;
  float *pfVar12;
  float fVar13;
  float fVar14;
  undefined *local_2c8 [8];
  locale local_288 [8];
  undefined4 local_280;
  undefined1 *local_278;
  undefined *local_270 [27];
  undefined8 local_198;
  undefined1 local_190;
  undefined1 local_18f;
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 local_170;
  long local_168 [8];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  wchar_t *local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  wchar_t *local_78 [2];
  int local_64;
  int local_60;
  int local_5c;
  int local_58 [2];
  float local_50;
  float local_4c [4];
  allocator local_3a;
  allocator local_39 [9];

  if ((param_1) && (gUseSplash != '\0')) {
    CSplash::Init(m_gSplash,(int)*(undefined8 *)(this + 0xa8));
    CSplash::Show((CSplash *)m_gSplash);
  }
  FILESYSTEM::GetLocalPath((FILESYSTEM *)local_78);
                    /* try { // try from 00566cd3 to 00566cd7 has its CatchHandler @ 00567b40 */
  std::wstring::wstring((wstring_conflict *)local_88,local_78[0],local_39);
                    /* try { // try from 00566cdb to 00566cdf has its CatchHandler @ 00567b2e */
  SetCurrentDirectory((wstring_conflict *)local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
                    /* try { // try from 00566d0d to 00566d11 has its CatchHandler @ 00567b24 */
  std::string::string((string *)local_98,(string *)(this + 0x88));
                    /* try { // try from 00566d24 to 00566d28 has its CatchHandler @ 00567b65 */
  std::string::append((char *)local_98,0xfa062e);
                    /* try { // try from 00566d3b to 00566d52 has its CatchHandler @ 00567b56 */
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_OPENGL,1);
  std::string::string((string *)local_a8,(string *)(this + 0x88));
                    /* try { // try from 00566d60 to 00566d64 has its CatchHandler @ 00567b54 */
  std::string::append((char *)local_a8,0xfa063a);
                    /* try { // try from 00566d70 to 00566d74 has its CatchHandler @ 00567b42 */
  std::string::assign((string *)local_98);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_a8[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
                    /* try { // try from 00566d9b to 00566d9f has its CatchHandler @ 00567b1a */
  FILESYSTEM::GetAppDataPath((FILESYSTEM *)local_b8);
                    /* try { // try from 00566dae to 00566db2 has its CatchHandler @ 00567ba2 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_168);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00566dd6 to 00566dda has its CatchHandler @ 00567cbe */
  std::string::string((string *)local_c8,(string *)local_168);
                    /* try { // try from 00566de8 to 00566dec has its CatchHandler @ 00567be0 */
  std::string::append((char *)local_c8,0xfa0653);
                    /* try { // try from 00566dfb to 00566dff has its CatchHandler @ 00567bd6 */
  std::string::string((string *)local_d8,(string *)local_168);
                    /* try { // try from 00566e0d to 00566e11 has its CatchHandler @ 00567bbc */
  std::string::append((char *)local_d8,0xfa065c);
                    /* try { // try from 00566e1d to 00566e21 has its CatchHandler @ 00567b10 */
  this_00 = (Root *)Ogre::NedAllocImpl::allocBytes(0x398,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00566e38 to 00566e3c has its CatchHandler @ 00567a00 */
  Ogre::Root::Root(this_00,(string *)local_98,(string *)local_c8,(string *)local_d8);
  *(Root **)(this + 0x40) = this_00;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_d8[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_c8[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_168[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
  }
                    /* try { // try from 00566e85 to 00566ec5 has its CatchHandler @ 00567b56 */
  Ogre::LogManager::getSingleton();
  bVar5 = (bool)Ogre::LogManager::getDefaultLog();
  Ogre::Log::setDebugOutputEnabled(bVar5);
  Ogre::LogManager::getSingleton();
  uVar9 = Ogre::LogManager::getDefaultLog();
  Ogre::Log::setLogDetail(uVar9,1);
  FILESYSTEM::GetAppDataPath((FILESYSTEM *)local_f8);
                    /* try { // try from 00566ed4 to 00566ed8 has its CatchHandler @ 00567af2 */
  std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_f8);
  wcslen(L"Save");
                    /* try { // try from 00566eee to 00566ef2 has its CatchHandler @ 005679e9 */
  std::wstring::append((wchar_t *)local_e8,0xfa3e5c);
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_f8[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 00566f1b to 00566f1f has its CatchHandler @ 00567b8e */
  std::operator+((wchar_t *)local_108,(wstring_conflict *)L"Path for saving is ... ");
                    /* try { // try from 00566f26 to 00566f2a has its CatchHandler @ 00567b7c */
  std::wstring::assign((wstring_conflict *)local_e8);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_108[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
                    /* try { // try from 00566f50 to 00566f54 has its CatchHandler @ 00567b8e */
  STRINGS::StringConvertToNarrow((STRINGS *)local_118,local_e8[0]);
                    /* try { // try from 00566f55 to 00567061 has its CatchHandler @ 00567b98 */
  uVar9 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar9,local_118,3);
  (**(code **)(*(long *)this + 0xa0))(this);
  uVar10 = (**(code **)(*(long *)this + 0x68))(this,param_1);
  if (((char)uVar10 == '\0') && (param_1)) {
    if (*(long *)(this + 0x80) == 0) goto LAB_00567569;
LAB_00566fa4:
    if (gUseSplash != '\0') {
      CSplash::Show((CSplash *)m_gSplash);
    }
    (**(code **)(**(long **)(this + 0x80) + 0xf0))(*(long **)(this + 0x80),0);
    uVar6 = (**(code **)(**(long **)(this + 0x80) + 0x20))();
    *(undefined4 *)(this + 0xb0) = uVar6;
    uVar6 = (**(code **)(**(long **)(this + 0x80) + 0x28))();
    *(undefined4 *)(this + 0xb4) = uVar6;
    uVar7 = SDL_GetWindowID(*(undefined8 *)(this + 0x2a0));
    *(ulong *)(this + 0xa0) = (ulong)uVar7;
  }
  else if (*(long *)(this + 0x80) != 0) goto LAB_00566fa4;
  (**(code **)(*(long *)this + 0x70))(this);
  (**(code **)(*(long *)this + 0x78))(this);
  if (*(long *)(this + 0x80) != 0) {
    (**(code **)(*(long *)this + 0x98))(this);
  }
  Ogre::Viewport::setClearEveryFrame(SUB81(*(undefined8 *)(this + 0x78),0),1);
  Ogre::Root::renderOneFrame();
  Ogre::Viewport::setClearEveryFrame(SUB81(*(undefined8 *)(this + 0x78),0),0);
  this_01 = (CMasterResourceManager *)Ogre::NedAllocImpl::allocBytes(400,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 0056706f to 00567073 has its CatchHandler @ 00567ae0 */
  CMasterResourceManager::CMasterResourceManager(this_01,*(CSettings **)(this + 0xb8));
  *(CMasterResourceManager **)(this + 0x1d8) = this_01;
                    /* try { // try from 0056707b to 005670b1 has its CatchHandler @ 00567b98 */
  lVar11 = CSteamStats::getSingleton();
  *(CGame **)(lVar11 + 0x90) = this;
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NO_SOUNDS);
  this_02 = (CSoundManager *)Ogre::NedAllocImpl::allocBytes(0x700,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 005670bb to 005670bf has its CatchHandler @ 00567afc */
  CSoundManager::CSoundManager(this_02,iVar8 == 0);
  *(CSoundManager **)(this + 0xc0) = this_02;
                    /* try { // try from 005670d1 to 00567315 has its CatchHandler @ 00567b98 */
  CSoundManager::initialize(this_02,*(CSettings **)(this + 0xb8));
  *(undefined1 *)(*(long *)(this + 0xc0) + 0x6a9) = 0;
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_SOUNDMUTE);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_MUSICMUTE);
  fVar13 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_SOUNDVOLUME);
  fVar14 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_MUSICVOLUME);
  CSoundManager::updateAudioLevels(fVar13,fVar14,SUB81(*(undefined8 *)(this + 0xc0),0),iVar8 != 0);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 0xb0) = *(undefined8 *)(this + 0x80);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 0x98) = *(undefined8 *)(this + 0xc0);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 200) = *(undefined8 *)(this + 0x50);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 0xd0) = *(undefined8 *)(this + 0x60);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 0xd8) = *(undefined8 *)(this + 0x68);
  *(undefined8 *)(*(long *)(this + 0x1d8) + 0xe0) = *(undefined8 *)(this + 0x70);
  ParticleUniverse::ParticleSystemManager::setMaxNumberOfParticles
            (*(ParticleSystemManager **)(*(long *)(this + 0x1d8) + 0xf0),20000);
  uVar6 = CDynamicPropertyFile::GetFloat
                    (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_PARTICLE_FALLOFF);
  *(undefined4 *)(*(long *)(*(long *)(this + 0x1d8) + 0xf0) + 0x4d8) = uVar6;
  fVar13 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_PARTICLEFPS);
  ParticleUniverse::ParticleSystemManager::setParticleFPS(fVar13);
  local_50 = (float)CDynamicPropertyFile::GetFloat
                              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_F_PARTICLE_PCT);
  local_4c[0] = DAT_00fa483c;
  pfVar12 = local_4c;
  if (local_50 < DAT_00fa483c) {
    pfVar12 = &local_50;
  }
  local_58[1] = 0;
  fVar13 = *pfVar12;
  if (fVar13 <= 0.0) {
    fVar13 = 0.0;
  }
  ParticleUniverse::ParticleSystemManager::setEmitterLoopingReleasePCT(fVar13 / DAT_00fa483c);
  if ((*(long *)(this + 0x80) != 0) && (gUseSplash != '\0')) {
                    /* try { // try from 00567685 to 00567689 has its CatchHandler @ 00567b98 */
    CSplash::Show((CSplash *)m_gSplash);
  }
  CMasterResourceManager::loadParticles(*(CMasterResourceManager **)(this + 0x1d8));
  CMissilePreloader::reloadMissiles(*(CMissilePreloader **)(*(long *)(this + 0x1d8) + 0x60));
  (**(code **)(*(long *)this + 0xa8))(this);
  (**(code **)(*(long *)this + 0xb0))(this);
  createMaterials(this);
  if (*(long *)(this + 0x80) != 0) {
    (**(code **)(*(long *)this + 0xb8))(this);
  }
  (**(code **)(*(long *)this + 0x80))(this);
  local_128[1] = 0;
  std::ios_base::ios_base((ios_base *)local_270);
  uVar9 = std::ostringstream::VTT._8_8_;
  local_270[0] = (undefined *)0x1424610;
  local_198 = 0;
  local_190 = 0;
  local_18f = 0;
  local_188 = 0;
  local_2c8[0] = (undefined *)std::ostringstream::VTT._8_8_;
  local_180 = 0;
  local_178 = 0;
  local_170 = 0;
  *(undefined8 *)((long)local_2c8 + *(long *)(std::ostringstream::VTT._8_8_ + -0x18)) =
       std::ostringstream::VTT._16_8_;
                    /* try { // try from 00567395 to 00567399 has its CatchHandler @ 005679e2 */
  std::ios::init((streambuf *)((long)local_2c8 + *(long *)(local_2c8[0] + -0x18)));
  local_2c8[0] = &DAT_01423a98;
  local_270[0] = &DAT_01423ac0;
  local_2c8[1] = (undefined *)0x1424470;
  local_2c8[2] = (undefined *)0x0;
  local_2c8[3] = (undefined *)0x0;
  local_2c8[4] = (undefined *)0x0;
  local_2c8[5] = (undefined *)0x0;
  local_2c8[6] = (undefined *)0x0;
  local_2c8[7] = (undefined *)0x0;
  std::locale::locale(local_288);
  local_2c8[1] = (undefined *)0x1423930;
  local_280 = 0x10;
  local_278 = &DAT_01423a38;
                    /* try { // try from 00567416 to 0056741a has its CatchHandler @ 0056796e */
  std::ios::init((streambuf *)local_270);
  if (*(long **)(this + 0x80) != (long *)0x0) {
    pcVar4 = *(code **)(**(long **)(this + 0x80) + 0xb8);
                    /* try { // try from 0056744f to 00567453 has its CatchHandler @ 00567cb9 */
    std::string::string((string *)local_128,"WINDOW",&local_3a);
                    /* try { // try from 0056746b to 0056746e has its CatchHandler @ 00567ca2 */
    (*pcVar4)(*(undefined8 *)(this + 0x80),local_128,local_128 + 1);
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_128[0] + -8);
      iVar8 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar8 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
                    /* try { // try from 0056748f to 005674fd has its CatchHandler @ 005679d3 */
    std::ostream::_M_insert<unsigned_long>((ulong)local_2c8);
    Ogre::WindowEventUtilities::addWindowEventListener
              (*(RenderWindow **)(this + 0x80),(WindowEventListener *)(this + 0x18));
    (**(code **)(**(long **)(this + 0x80) + 0xc0))(*(long **)(this + 0x80),this + 0x30);
    (**(code **)(**(long **)(this + 0x80) + 0xf0))(*(long **)(this + 0x80),1);
    if ((*(long *)(this + 0x80) != 0) && (gUseSplash != '\0')) {
                    /* try { // try from 00567608 to 00567678 has its CatchHandler @ 005679d3 */
      LinuxUtils::GetDesktopResolution(local_58,&local_5c);
      SDL_GetWindowSize(*(undefined8 *)(this + 0x2a0),&local_60,&local_64);
      SDL_SetWindowPosition
                (*(undefined8 *)(this + 0x2a0),(local_58[0] - local_60) / 2,
                 (local_5c - local_64) / 2);
      SDL_ShowWindow(*(undefined8 *)(this + 0x2a0));
      CSplash::Hide((CSplash *)m_gSplash);
    }
  }
  *(undefined1 *)(*(long *)(this + 0xc0) + 0x6a9) = 1;
  (**(code **)(*(long *)this + 0x88))(this);
  local_2c8[0] = &DAT_01423a98;
  local_270[0] = &DAT_01423ac0;
  local_2c8[1] = (undefined *)0x1423930;
  if ((allocator *)(local_278 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_278 + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_278 + -0x18));
    }
  }
  local_2c8[1] = (undefined *)0x1424470;
  std::locale::~locale(local_288);
  local_2c8[0] = (undefined *)uVar9;
  *(undefined8 *)((long)local_2c8 + *(long *)(uVar9 + -0x18)) = std::ostringstream::VTT._16_8_;
  local_270[0] = (undefined *)0x1424610;
                    /* try { // try from 0056755f to 005675d9 has its CatchHandler @ 00567b98 */
  std::ios_base::~ios_base((ios_base *)local_270);
  uVar10 = 1;
LAB_00567569:
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_118[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      uVar10 = uVar10 & 0xff;
    }
  }
  if ((allocator *)(local_e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_e8[0] + -2;
    wVar3 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -6));
      uVar10 = uVar10 & 0xff;
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_98[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      uVar10 = uVar10 & 0xff;
    }
  }
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_78[0] + -2;
    wVar3 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
      uVar10 = uVar10 & 0xff;
    }
  }
  return uVar10;
}



/* address=00567ce0
   symbol=CGame::createWindow */

/* WARNING: Removing unreachable block (ram,0x00568ad7) */
/* CGame::createWindow(bool) */

long * __thiscall CGame::createWindow(CGame *this,bool param_1)

{
  int *piVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  code *pcVar5;
  long lVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  long lVar14;
  char *pcVar15;
  undefined8 uVar16;
  DefaultHardwareBufferManager *this_00;
  RenderSystem *pRVar17;
  string *psVar18;
  long *plVar19;
  char cVar20;
  ulong uVar21;
  long lVar22;
  uint *puVar23;
  byte *pbVar24;
  byte *pbVar25;
  short sVar26;
  short sVar27;
  bool bVar28;
  bool bVar29;
  byte bVar30;
  float fVar31;
  string *local_288;
  map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
  local_258 [8];
  undefined4 local_250 [2];
  _Rb_tree_node *local_248;
  undefined4 *local_240;
  undefined4 *local_238;
  undefined8 local_230;
  Ogre local_228 [32];
  undefined2 *local_208;
  undefined4 local_200;
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined2 *local_1e8;
  undefined4 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  void *local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  long local_1a8 [2];
  string local_198 [8];
  undefined1 local_190 [8];
  string local_188 [16];
  string local_178 [16];
  string local_168 [16];
  string local_158 [16];
  string local_148 [16];
  string local_138 [16];
  UTFString local_128 [16];
  uint *local_118 [2];
  wstring_conflict local_108 [16];
  string local_f8 [16];
  string local_e8 [16];
  string local_d8 [16];
  string local_c8 [16];
  STRINGS local_b8 [16];
  string local_a8 [16];
  string local_98 [16];
  string local_88 [16];
  byte *local_78 [2];
  undefined1 *local_68 [2];
  int local_58;
  uint local_54;
  int local_50;
  int local_4c [2];
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

  bVar30 = 0;
  g_pGame = this;
  if ((*(long *)(this + 0x40) == 0) || (lVar13 = (**(code **)(*(long *)this + 0x10))(), lVar13 != 0)
     ) {
    return (long *)0x0;
  }
  if ((createWindow(bool)::pList == '\0') && (iVar7 = __cxa_guard_acquire(), iVar7 != 0)) {
                    /* try { // try from 0056825a to 00568266 has its CatchHandler @ 00568b15 */
    Ogre::Root::getSingleton();
    createWindow(bool)::pList = (long *)Ogre::Root::getAvailableRenderers();
    __cxa_guard_release();
  }
  if ((undefined8 *)*createWindow(bool)::pList == (undefined8 *)createWindow(bool)::pList[1]) {
    MessageBoxA((void *)0x0,"Could not find a valid renderer","Initialization Error",0);
    return (long *)0x0;
  }
  plVar19 = *(long **)*createWindow(bool)::pList;
  local_68[0] = &DAT_01423a38;
                    /* try { // try from 00567db5 to 00567db9 has its CatchHandler @ 00568a1e */
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_OPENGL);
  if (iVar7 == 0) {
                    /* try { // try from 00567de4 to 00567de8 has its CatchHandler @ 00568b97 */
    std::string::string((string *)local_78,"Rendering Device",local_39);
                    /* try { // try from 00567df0 to 00567e8d has its CatchHandler @ 00568b75 */
    lVar14 = (**(code **)(*plVar19 + 0x18))(plVar19);
    lVar13 = lVar14 + 8;
    lVar22 = *(long *)(lVar14 + 0x10);
    lVar14 = lVar13;
    while (lVar6 = lVar22, lVar6 != 0) {
      uVar3 = *(ulong *)(local_78[0] + -0x18);
      uVar4 = *(ulong *)(*(byte **)(lVar6 + 0x20) + -0x18);
      uVar21 = uVar4;
      if (uVar3 <= uVar4) {
        uVar21 = uVar3;
      }
      bVar28 = false;
      bVar29 = true;
      pbVar24 = *(byte **)(lVar6 + 0x20);
      pbVar25 = local_78[0];
      do {
        if (uVar21 == 0) break;
        uVar21 = uVar21 - 1;
        bVar28 = *pbVar24 < *pbVar25;
        bVar29 = *pbVar24 == *pbVar25;
        pbVar24 = pbVar24 + (ulong)bVar30 * -2 + 1;
        pbVar25 = pbVar25 + (ulong)bVar30 * -2 + 1;
      } while (bVar29);
      cVar20 = (!bVar28 && !bVar29) - bVar28;
      iVar7 = (int)cVar20;
      if (cVar20 == '\0') {
        lVar22 = uVar4 - uVar3;
        if (0x7fffffff < lVar22) goto LAB_00567e16;
        if (-0x80000001 < lVar22) {
          iVar7 = (int)lVar22;
          goto LAB_00567e12;
        }
LAB_00567e69:
        lVar22 = *(long *)(lVar6 + 0x18);
      }
      else {
LAB_00567e12:
        if (iVar7 < 0) goto LAB_00567e69;
LAB_00567e16:
        lVar22 = *(long *)(lVar6 + 0x10);
        lVar14 = lVar6;
      }
    }
    lVar22 = lVar13;
    if ((lVar13 != lVar14) &&
       (iVar7 = std::string::compare((string *)local_78), lVar22 = lVar14, iVar7 < 0)) {
      lVar22 = lVar13;
    }
                    /* try { // try from 00567e9f to 00567ea3 has its CatchHandler @ 00568b97 */
    std::string::~string((string *)local_78);
                    /* try { // try from 00567ebc to 00567ee4 has its CatchHandler @ 00568a1e */
    std::string::assign((string *)(lVar22 + 0x30));
    std::string::assign((string *)local_68);
  }
  local_288 = (string *)local_68;
  Ogre::Root::setRenderSystem(*(RenderSystem **)(this + 0x40));
                    /* try { // try from 00567efd to 00567f01 has its CatchHandler @ 00568a1c */
  std::string::string(local_88,"Game",&local_3a);
                    /* try { // try from 00567f10 to 00567f14 has its CatchHandler @ 00568a0f */
  Ogre::Root::initialise(SUB81(*(undefined8 *)(this + 0x40),0),(string *)0x0,local_88);
                    /* try { // try from 00567f18 to 00567f1c has its CatchHandler @ 00568a1c */
  std::string::~string(local_88);
  local_230 = 0;
  local_250[0] = 0;
  local_240 = local_250;
  local_248 = (_Rb_tree_node *)0x0;
  local_238 = local_240;
                    /* try { // try from 00567f68 to 00567f6c has its CatchHandler @ 00568a0a */
  std::string::string(local_98,"border",&local_3b);
                    /* try { // try from 00567f75 to 00567f86 has its CatchHandler @ 00568a47 */
  pcVar15 = (char *)std::
                    map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                    ::operator[](local_258,local_98);
  std::string::assign(pcVar15);
                    /* try { // try from 00567f8a to 00567f8e has its CatchHandler @ 00568a0a */
  std::string::~string(local_98);
  if (gFirstRun != '\0') {
                    /* try { // try from 00567fa8 to 00567fac has its CatchHandler @ 00568ba1 */
    std::string::string(local_a8,local_288);
                    /* try { // try from 00567fad to 00567fcd has its CatchHandler @ 00568b9c */
    uVar8 = UTILITIES::getProcessorSpeed();
    uVar9 = UTILITIES::getAvailableRAM();
    CSettings::assignDefault(*(CSettings **)(this + 0xb8),uVar9,uVar8,local_a8);
                    /* try { // try from 00567fd1 to 005680ae has its CatchHandler @ 00568ba1 */
    std::string::~string(local_a8);
  }
  uVar10 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH)
  ;
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT)
  ;
  LinuxUtils::GetDesktopResolution(local_4c,&local_50);
  if ((local_4c[0] < (int)uVar10) || (local_50 < iVar7)) {
    iVar11 = CDynamicPropertyFile::GetInt
                       (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
    plVar19 = (long *)0x0;
    if (iVar11 != 0) goto LAB_00568224;
  }
  fVar31 = (float)iVar7 / DAT_00fa4804;
  CDynamicPropertyFile::SetFloat
            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_XRATIO,
             (float)(int)uVar10 * DAT_00fa4808);
  CDynamicPropertyFile::SetFloat(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_YRATIO,fVar31);
  STRINGS::GetValueAsString(local_b8,fVar31);
                    /* try { // try from 005680c2 to 005680c6 has its CatchHandler @ 00568af2 */
  std::operator+((char *)local_c8,(string *)"Setting YRatio Init - ");
                    /* try { // try from 005680c7 to 005680dd has its CatchHandler @ 00568ae2 */
  uVar16 = Ogre::LogManager::getSingleton();
  Ogre::LogManager::logMessage(uVar16,local_c8,3);
                    /* try { // try from 005680e1 to 005680e5 has its CatchHandler @ 00568af2 */
  std::string::~string(local_c8);
                    /* try { // try from 005680e9 to 00568118 has its CatchHandler @ 00568ba1 */
  std::string::~string((string *)local_b8);
  iVar11 = CDynamicPropertyFile::GetInt
                     (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN);
  iVar12 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_VSYNCH);
  if (iVar12 != 0) {
                    /* try { // try from 00568135 to 00568139 has its CatchHandler @ 00568a45 */
    std::string::string(local_d8,"vsync",&local_3c);
                    /* try { // try from 00568142 to 00568153 has its CatchHandler @ 00568a34 */
    pcVar15 = (char *)std::
                      map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                      ::operator[](local_258,local_d8);
    std::string::assign(pcVar15);
                    /* try { // try from 00568157 to 0056815b has its CatchHandler @ 00568a45 */
    std::string::~string(local_d8);
  }
                    /* try { // try from 00568169 to 0056816d has its CatchHandler @ 00568ba1 */
  iVar12 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FSAA);
  if (iVar12 != 0) {
                    /* try { // try from 0056818a to 0056818e has its CatchHandler @ 00568b05 */
    std::string::string(local_e8,"FSAA",&local_3d);
                    /* try { // try from 00568197 to 005681a8 has its CatchHandler @ 00568af7 */
    pcVar15 = (char *)std::
                      map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                      ::operator[](local_258,local_e8);
    std::string::assign(pcVar15);
                    /* try { // try from 005681ac to 005681b0 has its CatchHandler @ 00568b05 */
    std::string::~string(local_e8);
  }
                    /* try { // try from 005681be to 005681f5 has its CatchHandler @ 00568ba1 */
  iVar12 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_OPENGL);
  if (iVar12 != 0) {
                    /* try { // try from 005687a5 to 005687a9 has its CatchHandler @ 00568b67 */
    std::string::string(local_f8,"RTT Preferred Mode",&local_3e);
                    /* try { // try from 005687b2 to 005687c3 has its CatchHandler @ 00568b62 */
    pcVar15 = (char *)std::
                      map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                      ::operator[](local_258,local_f8);
    std::string::assign(pcVar15);
                    /* try { // try from 005687c7 to 005687cb has its CatchHandler @ 00568b67 */
    std::string::~string(local_f8);
  }
  bVar28 = gUseSplash == '\0';
  if (param_1) {
    local_1c8 = (void *)0x0;
    local_1c0 = 0;
    local_1b8 = 0;
    local_208 = &DAT_01426458;
    local_1f0 = 0;
    local_200 = 0;
    local_1f8 = 0;
                    /* try { // try from 005682eb to 005682ef has its CatchHandler @ 00568a7f */
    std::string::string((string *)local_1a8,"Torchlight.png",&local_44);
                    /* try { // try from 00568303 to 00568307 has its CatchHandler @ 00568aca */
    Ogre::UTFString::assign((UTFString *)&local_208,(string *)local_1a8);
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar12 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar12 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
                    /* try { // try from 00568329 to 0056832d has its CatchHandler @ 005689bc */
    FILESYSTEM::GetApplicationPath((FILESYSTEM *)local_118);
    local_1e8 = &DAT_01426458;
    local_1d0 = 0;
    local_1e0 = 0;
    local_1d8 = 0;
                    /* try { // try from 00568370 to 0056847c has its CatchHandler @ 00568962 */
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_1e8,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_1e8,*(ulong *)(local_118[0] + -6));
    lVar13 = *(long *)(local_118[0] + -6);
    if (local_118[0] != local_118[0] + lVar13) {
      sVar27 = 0;
      puVar23 = local_118[0];
      do {
        uVar2 = *puVar23;
        lVar14 = 1;
        sVar26 = (short)uVar2;
        if (0xffff < uVar2) {
          lVar14 = 2;
          sVar27 = ((ushort)(uVar2 - 0x10000) & 0x3ff) + 0xdc00;
          sVar26 = ((ushort)(uVar2 - 0x10000 >> 10) & 0x3ff) + 0xd800;
        }
        lVar22 = *(long *)(local_1e8 + -0xc);
        uVar3 = lVar22 + 1;
        if ((*(ulong *)(local_1e8 + -8) < uVar3) || (0 < *(int *)(local_1e8 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_1e8,uVar3);
          lVar22 = *(long *)(local_1e8 + -0xc);
        }
        local_1e8[lVar22] = sVar26;
        if (local_1e8 != &DAT_01426458) {
          *(undefined4 *)(local_1e8 + -4) = 0;
          *(ulong *)(local_1e8 + -0xc) = uVar3;
          local_1e8[uVar3] = 0;
        }
        if (lVar14 == 2) {
          lVar14 = *(long *)(local_1e8 + -0xc);
          uVar3 = lVar14 + 1;
          if ((*(ulong *)(local_1e8 + -8) < uVar3) || (0 < *(int *)(local_1e8 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_1e8,uVar3);
            lVar14 = *(long *)(local_1e8 + -0xc);
          }
          local_1e8[lVar14] = sVar27;
          if (local_1e8 != &DAT_01426458) {
            *(undefined4 *)(local_1e8 + -4) = 0;
            *(ulong *)(local_1e8 + -0xc) = uVar3;
            local_1e8[uVar3] = 0;
          }
        }
        puVar23 = puVar23 + 1;
      } while (local_118[0] + lVar13 != puVar23);
    }
                    /* try { // try from 005684cf to 005684d3 has its CatchHandler @ 00568a77 */
    Ogre::operator+(local_228,(UTFString *)&local_1e8,(UTFString *)&local_208);
                    /* try { // try from 005684e2 to 005684e6 has its CatchHandler @ 00568a6f */
    Ogre::UTFString::operator_cast_to_wstring(local_128);
                    /* try { // try from 005684f5 to 005684f9 has its CatchHandler @ 00568a62 */
    STRINGS::StringConvertToUTF8(local_108);
                    /* try { // try from 005684fd to 00568501 has its CatchHandler @ 005689e5 */
    std::wstring::~wstring((wstring_conflict *)local_128);
    Ogre::UTFString::~UTFString((UTFString *)local_228);
    Ogre::UTFString::~UTFString((UTFString *)&local_1e8);
                    /* try { // try from 0056851f to 00568523 has its CatchHandler @ 005689d8 */
    std::wstring::~wstring((wstring_conflict *)local_118);
    Ogre::UTFString::~UTFString((UTFString *)&local_208);
                    /* try { // try from 0056855b to 005685ab has its CatchHandler @ 005689cb */
    iVar12 = lodepng::decode(&local_1c8,&local_58,&local_54,local_108,6,8);
    lVar13 = 0;
    if ((iVar12 == 0) &&
       (lVar13 = SDL_CreateRGBSurfaceFrom
                           (local_1c8,local_58,local_54,0x20,local_58 * 4,0xff,0xff00,0xff0000,
                            0xff000000), lVar13 == 0)) {
                    /* try { // try from 005688fd to 00568912 has its CatchHandler @ 005689cb */
      pcVar15 = (char *)SDL_GetError();
      MessageBoxA((void *)0x0,pcVar15,"Error loading icon",0);
    }
                    /* try { // try from 005685bb to 005685bf has its CatchHandler @ 005689c6 */
    std::string::~string((string *)local_108);
    if (local_1c8 != (void *)0x0) {
      operator_delete(local_1c8);
    }
    if (bVar28 && iVar11 != 0) {
      *(uint *)(this + 0xb0) = uVar10;
      *(int *)(this + 0xb4) = iVar7;
                    /* try { // try from 00568600 to 00568685 has its CatchHandler @ 00568ba1 */
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,uVar10);
      CDynamicPropertyFile::SetInt
                (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,*(int *)(this + 0xb4))
      ;
      uVar16 = SDL_CreateWindow("Torchlight",0,0,uVar10,iVar7,3);
      *(undefined8 *)(this + 0x2a0) = uVar16;
      SDL_SetWindowIcon(uVar16,lVar13);
      SDL_SetWindowGrab(*(undefined8 *)(this + 0x2a0),1);
      uVar16 = LinuxUtils::GetSDLWindowHandle(*(SDL_Window **)(this + 0x2a0));
      Ogre::StringConverter::toString(local_148,uVar16,0,0x20,0);
                    /* try { // try from 0056869e to 005686a2 has its CatchHandler @ 00568a22 */
      std::string::string(local_138,"parentWindowHandle",&local_3f);
                    /* try { // try from 005686ab to 005686ba has its CatchHandler @ 00568b55 */
      psVar18 = (string *)
                std::
                map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                ::operator[](local_258,local_138);
      std::string::assign(psVar18);
                    /* try { // try from 005686be to 005686c2 has its CatchHandler @ 00568a22 */
      std::string::~string(local_138);
                    /* try { // try from 005686c6 to 005686ca has its CatchHandler @ 00568ba1 */
      std::string::~string(local_148);
                    /* try { // try from 005686e3 to 005686e7 has its CatchHandler @ 00568b45 */
      std::string::string(local_158,"Torchlight",&local_40);
                    /* try { // try from 00568702 to 00568706 has its CatchHandler @ 00568b3f */
      plVar19 = (long *)Ogre::Root::createRenderWindow
                                  (*(string **)(this + 0x40),(uint)local_158,uVar10,SUB41(iVar7,0),
                                   (map *)0x1);
                    /* try { // try from 0056870d to 00568711 has its CatchHandler @ 00568b45 */
      std::string::~string(local_158);
    }
    else {
                    /* try { // try from 005687d7 to 00568870 has its CatchHandler @ 00568ba1 */
      LinuxUtils::GetDesktopResolution((int *)&local_54,&local_58);
      if ((int)local_54 <= (int)uVar10) {
        uVar10 = local_54;
      }
      if (local_58 <= iVar7) {
        iVar7 = local_58;
      }
      uVar16 = SDL_CreateWindow("Torchlight",0x2fff0000,0x2fff0000,uVar10,iVar7,
                                (-(uint)(gUseSplash == '\0') & 0xfffffff8) + 10);
      *(undefined8 *)(this + 0x2a0) = uVar16;
      SDL_SetWindowIcon(uVar16,lVar13);
      uVar16 = LinuxUtils::GetSDLWindowHandle(*(SDL_Window **)(this + 0x2a0));
      Ogre::StringConverter::toString(local_178,uVar16,0,0x20);
                    /* try { // try from 00568889 to 0056888d has its CatchHandler @ 00568bd5 */
      std::string::string(local_168,"parentWindowHandle",&local_41);
                    /* try { // try from 00568896 to 005688a5 has its CatchHandler @ 00568bc5 */
      psVar18 = (string *)
                std::
                map<std::string,std::string,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
                ::operator[](local_258,local_168);
      std::string::assign(psVar18);
                    /* try { // try from 005688a9 to 005688ad has its CatchHandler @ 00568bd5 */
      std::string::~string(local_168);
                    /* try { // try from 005688b1 to 005688b5 has its CatchHandler @ 00568ba1 */
      std::string::~string(local_178);
                    /* try { // try from 005688ce to 005688d2 has its CatchHandler @ 00568bb5 */
      std::string::string(local_188,"Torchlight",&local_42);
                    /* try { // try from 005688e8 to 005688ec has its CatchHandler @ 00568ba6 */
      plVar19 = (long *)Ogre::Root::createRenderWindow
                                  (*(string **)(this + 0x40),(uint)local_188,uVar10,SUB41(iVar7,0),
                                   (map *)0x0);
                    /* try { // try from 005688f3 to 005688f7 has its CatchHandler @ 00568bb5 */
      std::string::~string(local_188);
    }
                    /* try { // try from 0056871e to 0056873d has its CatchHandler @ 00568ba1 */
    (**(code **)(*plVar19 + 0xf0))(plVar19,1);
    (**(code **)(*plVar19 + 0xf8))(plVar19,1);
    SDL_FreeSurface(lVar13);
    if (plVar19 != (long *)0x0) {
      pcVar5 = *(code **)(*plVar19 + 0xb8);
                    /* try { // try from 0056876a to 0056876e has its CatchHandler @ 00568b3a */
      std::string::string(local_198,"WINDOW",&local_43);
                    /* try { // try from 0056877d to 0056877f has its CatchHandler @ 00568b2a */
      (*pcVar5)(plVar19,local_198,local_190);
                    /* try { // try from 00568783 to 00568787 has its CatchHandler @ 00568b3a */
      std::string::~string(local_198);
    }
  }
  else {
    this_00 = operator_new(0x130);
                    /* try { // try from 005681fc to 00568200 has its CatchHandler @ 00568a52 */
    Ogre::DefaultHardwareBufferManager::DefaultHardwareBufferManager(this_00);
                    /* try { // try from 00568201 to 00568223 has its CatchHandler @ 00568ba1 */
    Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::initialise();
    plVar19 = (long *)0x0;
  }
  pRVar17 = (RenderSystem *)Ogre::Root::getRenderSystem();
  checkCapabilities(this,pRVar17);
LAB_00568224:
                    /* try { // try from 0056822e to 00568232 has its CatchHandler @ 00568a32 */
  std::
  _Rb_tree<std::string,std::pair<std::string_const,std::string>,std::_Select1st<std::pair<std::string_const,std::string>>,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
  ::_M_erase((_Rb_tree<std::string,std::pair<std::string_const,std::string>,std::_Select1st<std::pair<std::string_const,std::string>>,std::less<std::string>,std::allocator<std::pair<std::string_const,std::string>>>
              *)local_258,local_248);
  std::string::~string(local_288);
  return plVar19;
}



/* address=00568bf0
   symbol=CGame::configure */

/* WARNING: Removing unreachable block (ram,0x00568e9b) */
/* WARNING: Removing unreachable block (ram,0x00568ebc) */
/* WARNING: Removing unreachable block (ram,0x00568eca) */
/* CGame::configure(bool) */

undefined8 __thiscall CGame::configure(CGame *this,bool param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  bool bVar7;
  wchar_t *local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_39 [9];

  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00568c3c to 00568c40 has its CatchHandler @ 00568ea6 */
  std::wstring::wstring((wstring_conflict *)&local_48,L"COMPRESS",local_39);
                    /* try { // try from 00568c47 to 00568c5e has its CatchHandler @ 00568e80 */
  lVar5 = (**(code **)(*(long *)this + 0x18))(this);
  CCmdLineParser::GetStringParam
            (local_68,*(undefined8 *)(lVar5 + 0x140),(wstring_conflict *)&local_48,
             (wstring_conflict *)local_58);
  bVar7 = false;
  if (*(size_t *)(local_68[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
    iVar4 = wmemcmp(local_68[0],::EMPTY_WSTRING,*(size_t *)(local_68[0] + -6));
    bVar7 = iVar4 == 0;
  }
  if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_68[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
    }
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (!bVar7) {
    gFirstRun = 0;
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN,0);
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,0x400);
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,0x300)
    ;
  }
                    /* try { // try from 00568cc1 to 00568cc5 has its CatchHandler @ 00568eab */
  lVar5 = createWindow(this,param_1);
  *(long *)(this + 0x80) = lVar5;
  if (lVar5 == 0) {
    gFirstRun = 0;
                    /* try { // try from 00568d7c to 00568deb has its CatchHandler @ 00568eab */
    gFailWidth = CDynamicPropertyFile::GetInt
                           (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH);
    gFailHeight = CDynamicPropertyFile::GetInt
                            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT);
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_WIDTH,0x400);
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RES_HEIGHT,0x300)
    ;
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FSAA,0);
    uVar6 = createWindow(this,param_1);
    *(undefined8 *)(this + 0x80) = uVar6;
  }
  return 1;
}



/* address=00569080
   symbol=CGame::CGame */

/* WARNING: Removing unreachable block (ram,0x0056a017) */
/* WARNING: Removing unreachable block (ram,0x0056a009) */
/* WARNING: Removing unreachable block (ram,0x0056a4f8) */
/* WARNING: Removing unreachable block (ram,0x0056a552) */
/* WARNING: Removing unreachable block (ram,0x0056a3db) */
/* WARNING: Removing unreachable block (ram,0x0056a172) */
/* WARNING: Removing unreachable block (ram,0x0056a220) */
/* WARNING: Removing unreachable block (ram,0x0056a3e6) */
/* WARNING: Removing unreachable block (ram,0x0056a0b4) */
/* WARNING: Removing unreachable block (ram,0x0056a315) */
/* WARNING: Removing unreachable block (ram,0x0056a64b) */
/* WARNING: Removing unreachable block (ram,0x0056a6a2) */
/* WARNING: Removing unreachable block (ram,0x0056a376) */
/* WARNING: Removing unreachable block (ram,0x0056a2c4) */
/* WARNING: Removing unreachable block (ram,0x0056a1d0) */
/* WARNING: Removing unreachable block (ram,0x0056a1c5) */
/* WARNING: Removing unreachable block (ram,0x0056a425) */
/* WARNING: Removing unreachable block (ram,0x0056a278) */
/* WARNING: Removing unreachable block (ram,0x0056a63d) */
/* WARNING: Removing unreachable block (ram,0x0056a503) */
/* WARNING: Removing unreachable block (ram,0x0056a02d) */
/* WARNING: Removing unreachable block (ram,0x0056a022) */
/* WARNING: Removing unreachable block (ram,0x0056a466) */
/* CGame::CGame(std::string, CSettings*, bool) */

void __thiscall CGame::CGame(CGame *this,undefined8 param_2,undefined8 param_3,char param_4)

{
  ulong uVar1;
  undefined2 *puVar2;
  int *piVar3;
  wchar_t wVar4;
  int iVar5;
  code *pcVar6;
  wchar_t *pwVar7;
  size_t __n;
  string *psVar8;
  wstring_conflict *pwVar9;
  char cVar10;
  int iVar11;
  undefined8 *puVar12;
  time_t tVar13;
  char *pcVar14;
  undefined8 uVar15;
  long lVar16;
  wchar_t *pwVar17;
  long lVar18;
  short sVar19;
  short sVar20;
  CFileReader local_1e8 [32];
  long local_1c8;
  int local_1c0;
  undefined8 local_1b8;
  string *local_1b0;
  long local_1a8;
  int local_1a0;
  undefined8 local_198;
  wstring_conflict *local_190;
  undefined2 *local_188;
  int local_180;
  undefined8 local_178;
  string *local_170;
  undefined2 *local_168;
  int local_160;
  undefined8 local_158;
  string *local_150;
  undefined2 *local_148;
  int local_140;
  undefined8 local_138;
  wstring_conflict *local_130;
  undefined1 local_128 [4];
  int local_124;
  int local_120;
  long local_108 [2];
  wchar_t *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  char *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  char *local_78 [2];
  long local_68 [2];
  long local_58 [2];
  allocator local_43 [4];
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CGame_00fa3e90;
  *(undefined ***)(this + 0x10) = &PTR_frameStarted_00fa3fa0;
  *(undefined ***)(this + 0x18) = &PTR__CGame_00fa3fd8;
  *(undefined ***)(this + 0x20) = &PTR__CGame_00fa4020;
  *(undefined ***)(this + 0x28) = &PTR__CGame_00fa4088;
  *(undefined ***)(this + 0x30) = &PTR__CGame_00fa40b0;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
                    /* try { // try from 0056913c to 00569140 has its CatchHandler @ 0056a65b */
  std::string::string((string *)(this + 0x88),"",local_39);
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined8 *)(this + 0xb8) = param_3;
  *(undefined8 *)(this + 0xc0) = 0;
  this[200] = (CGame)0x1;
  this[0xc9] = (CGame)0x0;
  this[0xca] = (CGame)0x0;
  this[0xcb] = (CGame)0x0;
  *(undefined4 **)(this + 0xd0) = &DAT_01424558;
  *(undefined8 *)(this + 0x1d8) = 0;
                    /* try { // try from 005691c0 to 005691c4 has its CatchHandler @ 0056a5f5 */
  Ogre::Timer::Timer((Timer *)(this + 0x1e0));
  *(undefined8 *)(this + 0x200) = 0;
  *(undefined8 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x210) = 0;
  *(undefined ***)(this + 0x1f8) = &PTR__MaterialPtr_00fa44d0;
  *(undefined8 *)(this + 0x220) = 0;
  *(undefined8 *)(this + 0x228) = 0;
  *(undefined4 *)(this + 0x230) = 0;
  *(undefined ***)(this + 0x218) = &PTR__MaterialPtr_00fa44d0;
  this[0x238] = (CGame)0x0;
  *(CGame **)(this + 0x240) = this + 0x240;
  *(CGame **)(this + 0x248) = this + 0x240;
  *(undefined4 *)(this + 0x250) = 0x3c;
  *(undefined4 *)(this + 0x254) = 0;
  this[600] = (CGame)0x1;
                    /* try { // try from 00569266 to 0056926a has its CatchHandler @ 0056a5ed */
  Ogre::GpuCommandBufferFlush::GpuCommandBufferFlush((GpuCommandBufferFlush *)(this + 0x260));
  *(undefined8 *)(this + 0x2a0) = 0;
                    /* try { // try from 00569285 to 00569289 has its CatchHandler @ 0056a5e5 */
  SDLEventHandler::SDLEventHandler((SDLEventHandler *)(this + 0x2a8));
  setenv("SDL_VIDEO_X11_XINERAMA","0",0);
                    /* try { // try from 0056929d to 0056933a has its CatchHandler @ 0056a5fd */
  iVar11 = SDL_VideoInit(0);
  if (iVar11 < 0) {
                    /* try { // try from 005695e5 to 005695e9 has its CatchHandler @ 0056a461 */
    std::string::string((string *)local_78,"Could not initialize SDL Video: ",&local_3a);
                    /* try { // try from 005695ea to 0056961f has its CatchHandler @ 0056a475 */
    pcVar14 = (char *)SDL_GetError();
    strlen(pcVar14);
    std::string::append((char *)local_78,(ulong)pcVar14);
    MessageBoxA((void *)0x0,local_78[0],"Error on startup",0);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  PopulateSDLResolutions(*(CSettings **)(this + 0xb8));
  SDL_GetDesktopDisplayMode(0,local_128);
  LinuxUtils::SaveDesktopResolution(local_124,local_120);
  atexit(SDL_Quit);
  Ogre::Timer::reset();
  gFirstRun = param_4;
  if (param_4 == '\0') {
                    /* try { // try from 00569648 to 0056966a has its CatchHandler @ 0056a487 */
    std::wstring::wstring((wstring_conflict *)local_58,L"SAFEMODE",&local_3b);
    iVar11 = CCmdLineParser::GetIntParam
                       (*(CCmdLineParser **)(*(long *)(this + 0xb8) + 0x140),
                        (wstring_conflict *)local_58,0);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_58[0] + -8);
      iVar5 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if (iVar11 != 1) goto LAB_005693a1;
  }
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN,0);
  CDynamicPropertyFile::SetInt
            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RIMLIGHTS_ENABLED,0);
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_ALLOW_HWSKINNING,0)
  ;
  pcVar6 = *(code **)(**(long **)(this + 0xb8) + 0x10);
                    /* try { // try from 00569361 to 00569365 has its CatchHandler @ 0056a638 */
  std::wstring::wstring((wstring_conflict *)local_68,L"",&local_3c);
                    /* try { // try from 00569370 to 00569372 has its CatchHandler @ 0056a5d5 */
  cVar10 = (*pcVar6)(*(undefined8 *)(this + 0xb8),(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_68[0] + -8);
    iVar11 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (cVar10 == '\0') {
    pcVar14 = strerror(*(int *)(*(long *)(this + 0xb8) + 0x134));
                    /* try { // try from 005696e5 to 005696e9 has its CatchHandler @ 0056a389 */
    std::string::string((string *)local_78,pcVar14,&local_3d);
                    /* try { // try from 005696f5 to 005696f9 has its CatchHandler @ 0056a381 */
    FILESYSTEM::GetAppDataPath((FILESYSTEM *)local_88);
                    /* try { // try from 00569712 to 00569716 has its CatchHandler @ 0056a366 */
    std::operator+((wchar_t *)local_f8,
                   (wstring_conflict *)
                   L"An error has occurred on startup. Settings were unable to save. It is recommend that you restart Torchlight.\n\nAttempted to save settings at:\n"
                  );
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_88[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    local_148 = &DAT_01426458;
    local_130 = (wstring_conflict *)0x0;
    local_140 = 0;
    local_138 = 0;
                    /* try { // try from 0056976d to 00569771 has its CatchHandler @ 0056a335 */
    Ogre::UTFString::assign((UTFString *)&local_148,(string *)local_78);
    local_168 = &DAT_01426458;
    local_150 = (string *)0x0;
    local_160 = 0;
    local_158 = 0;
                    /* try { // try from 005697b9 to 005697bd has its CatchHandler @ 0056a320 */
    std::string::string((string *)local_108,"\n\nWindows Error: ",local_43);
                    /* try { // try from 005697d1 to 005697d5 has its CatchHandler @ 0056a305 */
    Ogre::UTFString::assign((UTFString *)&local_168,(string *)local_108);
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_108[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    local_188 = &DAT_01426458;
    local_170 = (string *)0x0;
    local_180 = 0;
    local_178 = 0;
                    /* try { // try from 00569831 to 0056993c has its CatchHandler @ 0056a23d */
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_188,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_188,*(ulong *)(local_f8[0] + -6));
    pwVar7 = local_f8[0] + *(long *)(local_f8[0] + -6);
    if (local_f8[0] != pwVar7) {
      sVar20 = 0;
      pwVar17 = local_f8[0];
      do {
        wVar4 = *pwVar17;
        lVar18 = 1;
        sVar19 = (short)wVar4;
        if (0xffff < (uint)wVar4) {
          lVar18 = 2;
          sVar20 = ((ushort)(wVar4 + L'\xffff0000') & 0x3ff) + 0xdc00;
          sVar19 = ((ushort)((uint)(wVar4 + L'\xffff0000') >> 10) & 0x3ff) + 0xd800;
        }
        lVar16 = *(long *)(local_188 + -0xc);
        uVar1 = lVar16 + 1;
        if ((*(ulong *)(local_188 + -8) < uVar1) || (0 < *(int *)(local_188 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_188,uVar1);
          lVar16 = *(long *)(local_188 + -0xc);
        }
        local_188[lVar16] = sVar19;
        if (local_188 != &DAT_01426458) {
          *(undefined4 *)(local_188 + -4) = 0;
          *(ulong *)(local_188 + -0xc) = uVar1;
          local_188[uVar1] = 0;
        }
        if (lVar18 == 2) {
          lVar18 = *(long *)(local_188 + -0xc);
          uVar1 = lVar18 + 1;
          if ((*(ulong *)(local_188 + -8) < uVar1) || (0 < *(int *)(local_188 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_188,uVar1);
            lVar18 = *(long *)(local_188 + -0xc);
          }
          local_188[lVar18] = sVar20;
          if (local_188 != &DAT_01426458) {
            *(undefined4 *)(local_188 + -4) = 0;
            *(ulong *)(local_188 + -0xc) = uVar1;
            local_188[uVar1] = 0;
          }
        }
        pwVar17 = pwVar17 + 1;
      } while (pwVar7 != pwVar17);
    }
                    /* try { // try from 0056998f to 00569993 has its CatchHandler @ 0056a22b */
    Ogre::operator+((Ogre *)&local_1a8,(UTFString *)&local_188,(UTFString *)&local_168);
                    /* try { // try from 005699a7 to 005699ab has its CatchHandler @ 0056a2d4 */
    Ogre::operator+((Ogre *)&local_1c8,(UTFString *)&local_1a8,(UTFString *)&local_148);
                    /* try { // try from 005699ba to 005699be has its CatchHandler @ 0056a2cf */
    Ogre::UTFString::operator_cast_to_wstring((UTFString *)local_98);
                    /* try { // try from 005699c7 to 005699cb has its CatchHandler @ 0056a2af */
    std::wstring::assign((wstring_conflict *)local_f8);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_98[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    if (local_1b0 != (string *)0x0) {
      if (local_1c0 == 2) {
        if (local_1b0 != (string *)0x0) {
                    /* try { // try from 00569efd to 00569f01 has its CatchHandler @ 0056a263 */
          std::wstring::~wstring((wstring_conflict *)local_1b0);
LAB_00569e41:
          operator_delete(local_1b0);
        }
      }
      else if (local_1c0 == 3) {
        if (local_1b0 != (string *)0x0) {
          puVar2 = (undefined2 *)(*(long *)local_1b0 + -0x18);
          if (puVar2 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_1b0 + -8);
            iVar11 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              operator_delete(puVar2);
            }
          }
          operator_delete(local_1b0);
        }
      }
      else if ((local_1c0 == 1) && (local_1b0 != (string *)0x0)) {
                    /* try { // try from 00569e3c to 00569e40 has its CatchHandler @ 0056a263 */
        std::string::~string(local_1b0);
        goto LAB_00569e41;
      }
      local_1b0 = (string *)0x0;
      local_1b8 = 0;
    }
    if ((undefined8 *)(local_1c8 + -0x18) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_1c8 + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        operator_delete((undefined8 *)(local_1c8 + -0x18));
      }
    }
    if (local_190 != (wstring_conflict *)0x0) {
      if (local_1a0 == 2) {
        if (local_190 != (wstring_conflict *)0x0) {
                    /* try { // try from 00569e9e to 00569ec8 has its CatchHandler @ 0056a415 */
          std::wstring::~wstring(local_190);
LAB_00569ea3:
          operator_delete(local_190);
        }
      }
      else if (local_1a0 == 3) {
        if (local_190 != (wstring_conflict *)0x0) {
          puVar2 = (undefined2 *)(*(long *)local_190 + -0x18);
          if (puVar2 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_190 + -8);
            iVar11 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              operator_delete(puVar2);
            }
          }
          operator_delete(local_190);
        }
      }
      else if ((local_1a0 == 1) && (local_190 != (wstring_conflict *)0x0)) {
        std::string::~string((string *)local_190);
        goto LAB_00569ea3;
      }
      local_190 = (wstring_conflict *)0x0;
      local_198 = 0;
    }
    if ((undefined8 *)(local_1a8 + -0x18) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_1a8 + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        operator_delete((undefined8 *)(local_1a8 + -0x18));
      }
    }
    psVar8 = local_170;
    if (local_170 != (string *)0x0) {
      if (local_180 == 2) {
        if (local_170 != (string *)0x0) {
                    /* try { // try from 00569f39 to 00569f3d has its CatchHandler @ 0056a201 */
          std::wstring::~wstring((wstring_conflict *)local_170);
          goto LAB_00569dca;
        }
      }
      else if (local_180 == 3) {
        if (local_170 != (string *)0x0) {
          puVar2 = (undefined2 *)(*(long *)local_170 + -0x18);
          if (puVar2 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_170 + -8);
            iVar11 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              operator_delete(puVar2);
            }
          }
          goto LAB_00569dca;
        }
      }
      else if ((local_180 == 1) && (local_170 != (string *)0x0)) {
                    /* try { // try from 00569edf to 00569ee3 has its CatchHandler @ 0056a201 */
        std::string::~string(local_170);
LAB_00569dca:
        operator_delete(psVar8);
      }
      local_170 = (string *)0x0;
      local_178 = 0;
    }
    if ((ulong *)(local_188 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_188 + -4);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        operator_delete(local_188 + -0xc);
      }
    }
    psVar8 = local_150;
    if (local_150 != (string *)0x0) {
      if (local_160 == 2) {
        if (local_150 != (string *)0x0) {
                    /* try { // try from 00569f1b to 00569f1f has its CatchHandler @ 0056a153 */
          std::wstring::~wstring((wstring_conflict *)local_150);
          goto LAB_00569d64;
        }
      }
      else if (local_160 == 3) {
        if (local_150 != (string *)0x0) {
          puVar2 = (undefined2 *)(*(long *)local_150 + -0x18);
          if (puVar2 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_150 + -8);
            iVar11 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              operator_delete(puVar2);
            }
          }
          goto LAB_00569d64;
        }
      }
      else if ((local_160 == 1) && (local_150 != (string *)0x0)) {
                    /* try { // try from 00569e80 to 00569e84 has its CatchHandler @ 0056a153 */
        std::string::~string(local_150);
LAB_00569d64:
        operator_delete(psVar8);
      }
      local_150 = (string *)0x0;
      local_158 = 0;
    }
    if ((ulong *)(local_168 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_168 + -4);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        operator_delete(local_168 + -0xc);
      }
    }
    pwVar9 = local_130;
    if (local_130 != (wstring_conflict *)0x0) {
      if (local_140 == 2) {
        if (local_130 != (wstring_conflict *)0x0) {
                    /* try { // try from 00569e1e to 00569e22 has its CatchHandler @ 0056a061 */
          std::wstring::~wstring(local_130);
          goto LAB_00569d31;
        }
      }
      else if (local_140 == 3) {
        if (local_130 != (wstring_conflict *)0x0) {
          puVar2 = (undefined2 *)(*(long *)local_130 + -0x18);
          if (puVar2 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(*(long *)local_130 + -8);
            iVar11 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar11 < 1) {
              operator_delete(puVar2);
            }
          }
          goto LAB_00569d31;
        }
      }
      else if ((local_140 == 1) && (local_130 != (wstring_conflict *)0x0)) {
                    /* try { // try from 00569e62 to 00569e66 has its CatchHandler @ 0056a061 */
        std::string::~string((string *)local_130);
LAB_00569d31:
        operator_delete(pwVar9);
      }
      local_130 = (wstring_conflict *)0x0;
      local_138 = 0;
    }
    if ((ulong *)(local_148 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_148 + -4);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        operator_delete(local_148 + -0xc);
      }
    }
                    /* try { // try from 00569bb8 to 00569bbc has its CatchHandler @ 0056a56a */
    MessageBox((void *)0x0,local_f8[0],L"Error on startup",0);
                    /* try { // try from 00569bd0 to 00569bd4 has its CatchHandler @ 0056a562 */
    STRINGS::StringConvertToNarrow((STRINGS *)local_a8,local_f8[0]);
                    /* try { // try from 00569bf0 to 00569bf4 has its CatchHandler @ 0056a55d */
    std::string::string((string *)local_b8,local_a8[0],&local_3e);
                    /* try { // try from 00569bf5 to 00569c0b has its CatchHandler @ 0056a53a */
    uVar15 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar15,(string *)local_b8,3,0);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar3 = (int *)(local_b8[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar3 = (int *)(local_a8[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_f8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar7 = local_f8[0] + -2;
      wVar4 = *pwVar7;
      *pwVar7 = *pwVar7 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -6));
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar3 = (int *)(local_78[0] + -8);
      iVar11 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
  }
  if (gFirstRun != '\0') {
                    /* try { // try from 00569cba to 00569cec has its CatchHandler @ 0056a5fd */
    CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN,1);
    CDynamicPropertyFile::SetInt
              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_RIMLIGHTS_ENABLED,1);
    CDynamicPropertyFile::SetInt
              (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_ALLOW_HWSKINNING,1);
  }
LAB_005693a1:
                    /* try { // try from 005693b9 to 005693bd has its CatchHandler @ 0056a656 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"1",&local_3f);
                    /* try { // try from 005693ce to 005693d2 has its CatchHandler @ 0056a663 */
  CDynamicPropertyFile::SetString
            ((uint)*(undefined8 *)(this + 0xb8),(wstring_conflict *)(ulong)KSETTINGS_S_VERSION);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_c8[0] + -8);
    iVar11 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 005693f6 to 005693fa has its CatchHandler @ 0056a5fd */
  CFileReader::CFileReader(local_1e8);
                    /* try { // try from 00569406 to 0056940a has its CatchHandler @ 0056a5c4 */
  FILESYSTEM::GetApplicationPath((FILESYSTEM *)local_d8);
                    /* try { // try from 00569419 to 0056941d has its CatchHandler @ 0056a697 */
  std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
  wcslen(L"\\buildver.txt");
                    /* try { // try from 00569433 to 00569437 has its CatchHandler @ 0056a67d */
  std::wstring::append((wchar_t *)local_e8,0xfa3778);
                    /* try { // try from 0056943e to 00569442 has its CatchHandler @ 0056a695 */
  cVar10 = CFileReader::ReadFile(local_1e8,(wstring_conflict *)local_e8);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_e8[0] + -8);
    iVar11 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_d8[0] + -8);
    iVar11 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar11 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  if (cVar10 != '\0') {
                    /* try { // try from 00569486 to 0056948a has its CatchHandler @ 0056a5c4 */
    CFileReader::ReadLine((wchar_t)local_f8);
    pwVar7 = local_f8[0];
    if ((*(size_t *)(local_f8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar11 = wmemcmp(local_f8[0],::EMPTY_WSTRING,*(size_t *)(local_f8[0] + -6)), iVar11 != 0)) {
                    /* try { // try from 005694be to 005694c2 has its CatchHandler @ 0056a66b */
      CDynamicPropertyFile::SetString
                ((uint)*(undefined8 *)(this + 0xb8),(wstring_conflict *)(ulong)KSETTINGS_S_VERSION);
      pwVar7 = local_f8[0];
    }
    if ((allocator *)(pwVar7 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar17 = pwVar7 + -2;
      wVar4 = *pwVar17;
      *pwVar17 = *pwVar17 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(pwVar7 + -6));
      }
    }
  }
                    /* try { // try from 005694ea to 0056958e has its CatchHandler @ 0056a5c4 */
  CDynamicPropertyFile::SetInt
            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_NUM_TICKS_PER_SECOND,1);
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_UPDATE_PERF,0);
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_CURRENT_FPS,0);
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_AI_FREEZE,0);
  CDynamicPropertyFile::SetInt
            (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_PLAYER_UNTARGETABLE,0);
  CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_DEBUG_LOGIC,0);
  puVar12 = (undefined8 *)
            CDynamicPropertyFile::GetString
                      (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_S_VERSION);
  __n = *(size_t *)((wchar_t *)*puVar12 + -6);
  if (((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
      (iVar11 = wmemcmp((wchar_t *)*puVar12,::EMPTY_WSTRING,__n), iVar11 == 0)) ||
     (iVar11 = CDynamicPropertyFile::GetInt
                         (*(CDynamicPropertyFile **)(this + 0xb8),KSETTINGS_FULLSCREEN), iVar11 != 0
     )) {
    gUseSplash = 0;
  }
  tVar13 = time((time_t *)0x0);
  srand((uint)tVar13);
                    /* try { // try from 005695ab to 005695af has its CatchHandler @ 0056a5fd */
  CFileReader::~CFileReader(local_1e8);
  return;
}



/* address=0056a820
   symbol=CGame::getWindowHandle */

/* non-virtual thunk to CGame::getWindowHandle() */

void __thiscall CGame::getWindowHandle(CGame *this)

{
  getWindowHandle(this + -0x20);
  return;
}



/* address=0056a830
   symbol=CGame::getWindowHandle */

/* CGame::getWindowHandle() */

undefined8 __thiscall CGame::getWindowHandle(CGame *this)

{
  return *(undefined8 *)(this + 0xa0);
}



/* address=0056a840
   symbol=CGame::getSettings */

/* non-virtual thunk to CGame::getSettings() */

void __thiscall CGame::getSettings(CGame *this)

{
  getSettings(this + -0x20);
  return;
}



/* address=0056a850
   symbol=CGame::getSettings */

/* CGame::getSettings() */

undefined8 __thiscall CGame::getSettings(CGame *this)

{
  return *(undefined8 *)(this + 0xb8);
}



/* address=0056a860
   symbol=CGame::getSceneManager */

/* non-virtual thunk to CGame::getSceneManager() */

void __thiscall CGame::getSceneManager(CGame *this)

{
  getSceneManager(this + -0x20);
  return;
}



/* address=0056a870
   symbol=CGame::getSceneManager */

/* CGame::getSceneManager() */

undefined8 __thiscall CGame::getSceneManager(CGame *this)

{
  return *(undefined8 *)(this + 0x50);
}



/* address=0056a880
   symbol=CGame::getRenderWindow */

/* non-virtual thunk to CGame::getRenderWindow() */

void __thiscall CGame::getRenderWindow(CGame *this)

{
  getRenderWindow(this + -0x20);
  return;
}



/* address=0056a890
   symbol=CGame::getRenderWindow */

/* CGame::getRenderWindow() */

undefined8 __thiscall CGame::getRenderWindow(CGame *this)

{
  return *(undefined8 *)(this + 0x80);
}



/* address=0056a8a0
   symbol=CGame::getSoundManager */

/* non-virtual thunk to CGame::getSoundManager() */

void __thiscall CGame::getSoundManager(CGame *this)

{
  getSoundManager(this + -0x20);
  return;
}



/* address=0056a8b0
   symbol=CGame::getSoundManager */

/* CGame::getSoundManager() */

undefined8 __thiscall CGame::getSoundManager(CGame *this)

{
  return *(undefined8 *)(this + 0xc0);
}



/* address=0056a8c0
   symbol=CGame::getGameClient */

/* non-virtual thunk to CGame::getGameClient() */

void __thiscall CGame::getGameClient(CGame *this)

{
  getGameClient(this + -0x20);
  return;
}



/* address=0056a8d0
   symbol=CGame::getGameClient */

/* CGame::getGameClient() */

undefined8 __thiscall CGame::getGameClient(CGame *this)

{
  return *(undefined8 *)(this + 0x98);
}



/* export-summary functions=72 failures=0 */
