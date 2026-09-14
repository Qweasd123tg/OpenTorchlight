/* Targeted Ghidra class export.
   namespace=CSoundObject
   Treat pseudocode as navigation evidence. */


/* address=00a07e20
   symbol=CSoundObject::positionUpdated */

/* CSoundObject::positionUpdated(Ogre::Vector3 const&) */

void CSoundObject::positionUpdated(Vector3 *param_1)

{
  if (*(long *)(param_1 + 0x118) != 0) {
    *(undefined1 *)(*(long *)(param_1 + 0x118) + 0xa8) = 1;
  }
  return;
}

/* address=00a07e40
   symbol=CSoundObject::isLooping */

/* CSoundObject::isLooping() */

undefined1 __thiscall CSoundObject::isLooping(CSoundObject *this)

{
  undefined1 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x118) != 0) {
    uVar1 = *(undefined1 *)(*(long *)(this + 0x118) + 200);
  }
  return uVar1;
}

/* address=00a07e60
   symbol=CSoundObject::stop */

/* CSoundObject::stop() */

void __thiscall CSoundObject::stop(CSoundObject *this)

{
  if (*(CSoundBank **)(this + 0x118) != (CSoundBank *)0x0) {
    CSoundBank::stop(*(CSoundBank **)(this + 0x118));
    (**(code **)(*(long *)this + 0x30))(this,0xc);
    this[0x121] = (CSoundObject)0x0;
  }
  return;
}

/* address=00a07e90
   symbol=CSoundObject::resume */

/* CSoundObject::resume() */

void __thiscall CSoundObject::resume(CSoundObject *this)

{
  if (*(CSoundBank **)(this + 0x118) != (CSoundBank *)0x0) {
    CSoundBank::resume(*(CSoundBank **)(this + 0x118));
    this[0x122] = (CSoundObject)0x0;
    *(undefined1 *)(*(long *)(this + 0x118) + 0xa8) = 1;
  }
  return;
}

/* address=00a07ec0
   symbol=CSoundObject::pause */

/* CSoundObject::pause() */

void __thiscall CSoundObject::pause(CSoundObject *this)

{
  if (*(CSoundBank **)(this + 0x118) != (CSoundBank *)0x0) {
    CSoundBank::pause(*(CSoundBank **)(this + 0x118));
    this[0x122] = (CSoundObject)0x1;
  }
  return;
}

/* address=00a07ee0
   symbol=CSoundObject::setVisible */

/* CSoundObject::setVisible(bool) */

void __thiscall CSoundObject::setVisible(CSoundObject *this,bool param_1)

{
  CSceneNodeObject::setVisible((CSceneNodeObject *)this,param_1);
  if (*(long *)(this + 0x118) != 0) {
    *(undefined1 *)(*(long *)(this + 0x118) + 0xa8) = 1;
  }
  return;
}

/* address=00a07f10
   symbol=CSoundObject::play */

/* CSoundObject::play() */

void __thiscall CSoundObject::play(CSoundObject *this)

{
  long lVar1;
  CSoundObject CVar2;
  int iVar3;
  SceneNode *pSVar4;
  CSoundBank *this_00;

  lVar1 = *(long *)(this + 0x118);
  if (lVar1 == 0) {
    return;
  }
  if (((*(char *)(*(long *)(lVar1 + 0x10) + 0x6a9) == '\0') ||
      (*(char *)(*(long *)(lVar1 + 0x10) + 0x6a8) == '\0')) && (this[0x123] == (CSoundObject)0x0)) {
    return;
  }
  *(undefined1 *)(lVar1 + 0xa8) = 1;
  if (this[0x81] == (CSoundObject)0x0) {
    CSceneNodeObject::setVisible((CSceneNodeObject *)this,true);
  }
  CSoundBank::stop(*(CSoundBank **)(this + 0x118));
  CVar2 = this[0x123];
  this[0x121] = (CSoundObject)0x1;
  if (CVar2 == (CSoundObject)0x0) {
    CSoundBank::setRadius(*(CSoundBank **)(this + 0x118),0.0);
    this_00 = *(CSoundBank **)(this + 0x118);
    CVar2 = this[0x123];
    if (this_00[200] != (CSoundBank)0x0) goto LAB_00a07fa0;
LAB_00a07f7c:
    if (CVar2 == (CSoundObject)0x0) goto LAB_00a07fa4;
    pSVar4 = *(SceneNode **)(this + 0x58);
  }
  else {
    this_00 = *(CSoundBank **)(this + 0x118);
    if (this_00[200] == (CSoundBank)0x0) goto LAB_00a07f7c;
LAB_00a07fa0:
    if (CVar2 != (CSoundObject)0x0) goto LAB_00a07fc0;
LAB_00a07fa4:
    pSVar4 = (SceneNode *)0x0;
  }
  iVar3 = CSoundBank::playSample(this_00,0,pSVar4,0.0,0.0,false);
  if (iVar3 < 0) {
    this[0x121] = (CSoundObject)0x0;
  }
LAB_00a07fc0:
  (**(code **)(*(long *)this + 0x30))(this,0xb);
  if (this[0x122] == (CSoundObject)0x0) {
    return;
  }
  pause(this);
  return;
}

/* address=00a08030
   symbol=CSoundObject::setEnabled */

/* CSoundObject::setEnabled(bool) */

void __thiscall CSoundObject::setEnabled(CSoundObject *this,bool param_1)

{
  this[0x82] = (CSoundObject)param_1;
  if (((*(long *)(this + 0x118) != 0) && (param_1)) && (this[0x120] != (CSoundObject)0x0)) {
    play(this);
    *(undefined1 *)(*(long *)(this + 0x118) + 0xa8) = 1;
    return;
  }
  return;
}

/* address=00a08070
   symbol=CSoundObject::reset */

/* CSoundObject::reset() */

void __thiscall CSoundObject::reset(CSoundObject *this)

{
  CSoundBank::stop(*(CSoundBank **)(this + 0x118));
  play(this);
  return;
}

/* address=00a08090
   symbol=CSoundObject::updateSounds */

/* CSoundObject::updateSounds(float) */

void __thiscall CSoundObject::updateSounds(CSoundObject *this,float param_1)

{
  long lVar1;
  char cVar2;

  if ((((*(long *)(this + 0x118) != 0) &&
       (cVar2 = (**(code **)(*(long *)this + 0x48))(), cVar2 != '\0')) &&
      (this[0x121] != (CSoundObject)0x0)) && (this[0x122] == (CSoundObject)0x0)) {
    lVar1 = *(long *)(*(SceneNode **)(this + 0x118) + 0x10);
    if (((*(char *)(lVar1 + 0x6a9) != '\0') && (*(char *)(lVar1 + 0x6a8) != '\0')) &&
       ((CSoundBank::update(param_1,*(SceneNode **)(this + 0x118)),
        *(int *)(*(long *)(this + 0x118) + 0x20) == 0 && (this[0x123] == (CSoundObject)0x0)))) {
      this[0x121] = (CSoundObject)0x0;
                    /* WARNING: Could not recover jumptable at 0x00a0812f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)this + 0x30))(this,0xd);
      return;
    }
  }
  return;
}

/* address=00a08140
   symbol=CSoundObject::setSoundBankGuid */

/* CSoundObject::setSoundBankGuid(long long) */

void __thiscall CSoundObject::setSoundBankGuid(CSoundObject *this,longlong param_1)

{
  if (*(long *)(this + 0x118) != 0) {
    *(longlong *)(this + 0x108) = param_1;
    CSoundBank::clear(*(CSoundBank **)(this + 0x118));
    if (*(long *)(this + 0x108) != -1) {
      CSoundBank::addSample(*(CSoundBank **)(this + 0x118),0,param_1);
      if (this[0x121] != (CSoundObject)0x0) {
        reset(this);
        return;
      }
    }
  }
  return;
}

/* address=00a081c0
   symbol=CSoundObject::editorSelectionChanged */

/* non-virtual thunk to CSoundObject::editorSelectionChanged(bool) */

void __thiscall CSoundObject::editorSelectionChanged(CSoundObject *this,bool param_1)

{
  editorSelectionChanged(this + -0x100,param_1);
  return;
}

/* address=00a081d0
   symbol=CSoundObject::editorSelectionChanged */

/* CSoundObject::editorSelectionChanged(bool) */

void __thiscall CSoundObject::editorSelectionChanged(CSoundObject *this,bool param_1)

{
  char cVar1;

  if (*(long *)(this + 0x68) != 0) {
    cVar1 = CResourceManager::getEditorIsRunning();
    if (cVar1 != '\0') {
      if (!param_1) {
        CSceneNodeObject::sceneNodeDetachEntity((CSceneNodeObject *)this);
        return;
      }
      CSceneNodeObject::sceneNodeAttachEntity((CSceneNodeObject *)this,*(Entity **)(this + 0x60));
      return;
    }
  }
  return;
}

/* address=00a08240
   symbol=CSoundObject::~CSoundObject */

/* CSoundObject::~CSoundObject() */

void __thiscall CSoundObject::~CSoundObject(CSoundObject *this)

{
  *(undefined ***)this = &PTR__CSoundObject_00fdacb0;
  *(undefined ***)(this + 0x100) = &PTR__CSoundObject_00fdae98;
  if (*(long **)(this + 0x118) != (long *)0x0) {
                    /* try { // try from 00a08269 to 00a0826b has its CatchHandler @ 00a0828f */
    (**(code **)(**(long **)(this + 0x118) + 8))();
    *(undefined8 *)(this + 0x118) = 0;
  }
  *(undefined ***)(this + 0x100) = &PTR__iSelected_00fdaf10;
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}

/* address=00a082c0
   symbol=CSoundObject::~CSoundObject */

/* non-virtual thunk to CSoundObject::~CSoundObject() */

void __thiscall CSoundObject::~CSoundObject(CSoundObject *this)

{
  ~CSoundObject(this + -0x100);
  return;
}

/* address=00a082d0
   symbol=CSoundObject::~CSoundObject */

/* non-virtual thunk to CSoundObject::~CSoundObject() */

void __thiscall CSoundObject::~CSoundObject(CSoundObject *this)

{
  ~CSoundObject(this + -0x100);
  return;
}

/* address=00a082e0
   symbol=CSoundObject::~CSoundObject */

/* CSoundObject::~CSoundObject() */

void __thiscall CSoundObject::~CSoundObject(CSoundObject *this)

{
  ~CSoundObject(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00a08300
   symbol=CSoundObject::CSoundObject */

/* CSoundObject::CSoundObject(CResourceManager*) */

void __thiscall CSoundObject::CSoundObject(CSoundObject *this,CResourceManager *param_1)

{
  CSoundManager *pCVar1;
  long lVar2;
  CSoundBank *this_00;

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CSoundObject_00fdacb0;
  *(undefined ***)(this + 0x100) = &PTR__CSoundObject_00fdae98;
  *(undefined8 *)(this + 0x108) = 0xffffffffffffffff;
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  *(undefined8 *)(this + 0x118) = 0;
  this[0x120] = (CSoundObject)0x1;
  this[0x121] = (CSoundObject)0x0;
  this[0x122] = (CSoundObject)0x0;
  this[0x123] = (CSoundObject)0x1;
                    /* try { // try from 00a08366 to 00a08390 has its CatchHandler @ 00a083ee */
  lVar2 = CMasterResourceManager::getSingleton();
  if (*(long *)(lVar2 + 0x98) != 0) {
    lVar2 = CMasterResourceManager::getSingleton();
    pCVar1 = *(CSoundManager **)(lVar2 + 0x98);
    this_00 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00a0839f to 00a083a3 has its CatchHandler @ 00a0840c */
    CSoundBank::CSoundBank(this_00,pCVar1,true);
    *(CSoundBank **)(this + 0x118) = this_00;
    if (this_00 != (CSoundBank *)0x0) {
                    /* try { // try from 00a083bb to 00a083da has its CatchHandler @ 00a083ee */
      CSoundBank::setRadius(this_00,DAT_00fa86d0);
      (**(code **)(*(long *)this + 0x90))(*(undefined4 *)(*(long *)(this + 0x118) + 0xb0),this);
      *(undefined1 *)(*(long *)(this + 0x118) + 0xa8) = 1;
    }
  }
  return;
}

/* address=00a08420
   symbol=CSoundObject::_GLOBAL__I_CSoundObject */

/* CSoundObject::CSoundObject(CResourceManager*) */

void CSoundObject::_GLOBAL__I_CSoundObject(void)

{
  allocator local_bb;
  allocator local_ba;
  allocator local_b9;
  allocator local_b8;
  allocator local_b7;
  allocator local_b6;
  allocator local_b5;
  allocator local_b4;
  allocator local_b3;
  allocator local_b2;
  allocator local_b1;
  allocator local_b0;
  allocator local_af;
  allocator local_ae;
  allocator local_ad;
  allocator local_ac;
  allocator local_ab;
  allocator local_aa;
  allocator local_a9;
  allocator local_a8;
  allocator local_a7;
  allocator local_a6;
  allocator local_a5;
  allocator local_a4;
  allocator local_a3;
  allocator local_a2;
  allocator local_a1;
  allocator local_a0;
  allocator local_9f;
  allocator local_9e;
  allocator local_9d;
  allocator local_9c;
  allocator local_9b;
  allocator local_9a;
  allocator local_99;
  allocator local_98;
  allocator local_97;
  allocator local_96;
  allocator local_95;
  allocator local_94;
  allocator local_93;
  allocator local_92;
  allocator local_91;
  allocator local_90;
  allocator local_8f;
  allocator local_8e;
  allocator local_8d;
  allocator local_8c;
  allocator local_8b;
  allocator local_8a;
  allocator local_89;
  allocator local_88;
  allocator local_87;
  allocator local_86;
  allocator local_85;
  allocator local_84;
  allocator local_83;
  allocator local_82;
  allocator local_81;
  allocator local_80;
  allocator local_7f;
  allocator local_7e;
  allocator local_7d;
  allocator local_7c;
  allocator local_7b;
  allocator local_7a;
  allocator local_79;
  allocator local_78;
  allocator local_77;
  allocator local_76;
  allocator local_75;
  allocator local_74;
  allocator local_73;
  allocator local_72;
  allocator local_71;
  allocator local_70;
  allocator local_6f;
  allocator local_6e;
  allocator local_6d;
  allocator local_6c;
  allocator local_6b;
  allocator local_6a;
  allocator local_69;
  allocator local_68;
  allocator local_67;
  allocator local_66;
  allocator local_65;
  allocator local_64;
  allocator local_63;
  allocator local_62;
  allocator local_61;
  allocator local_60;
  allocator local_5f;
  allocator local_5e;
  allocator local_5d;
  allocator local_5c;
  allocator local_5b;
  allocator local_5a;
  allocator local_59;
  allocator local_58;
  allocator local_57;
  allocator local_56;
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
  allocator local_39;
  allocator local_38;
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;
  allocator local_28;
  allocator local_27;
  allocator local_26;
  allocator local_25;
  allocator local_24;
  allocator local_23;
  allocator local_22;
  allocator local_21;
  allocator local_20;
  allocator local_1f;
  allocator local_1e;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;
  allocator local_18;
  allocator local_17;
  allocator local_16;
  allocator local_15;
  allocator local_14;
  allocator local_13;
  allocator local_12;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
                    /* try { // try from 00a084d6 to 00a084da has its CatchHandler @ 00a09832 */
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&local_9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
                    /* try { // try from 00a08501 to 00a08505 has its CatchHandler @ 00a0a195 */
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&local_a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
                    /* try { // try from 00a0852c to 00a08530 has its CatchHandler @ 00a0a185 */
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&local_b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
                    /* try { // try from 00a08557 to 00a0855b has its CatchHandler @ 00a0a175 */
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&local_c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
                    /* try { // try from 00a08582 to 00a08586 has its CatchHandler @ 00a0a165 */
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&local_d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
                    /* try { // try from 00a085ad to 00a085b1 has its CatchHandler @ 00a0a155 */
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&local_e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
                    /* try { // try from 00a085d8 to 00a085dc has its CatchHandler @ 00a0a145 */
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&local_f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
                    /* try { // try from 00a08603 to 00a08607 has its CatchHandler @ 00a0a135 */
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&local_10);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
                    /* try { // try from 00a0862e to 00a08632 has its CatchHandler @ 00a0a125 */
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&local_11);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
                    /* try { // try from 00a08659 to 00a0865d has its CatchHandler @ 00a0a115 */
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&local_12);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
                    /* try { // try from 00a08684 to 00a08688 has its CatchHandler @ 00a0a107 */
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&local_13);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
                    /* try { // try from 00a086af to 00a086b3 has its CatchHandler @ 00a0a102 */
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&local_14);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
                    /* try { // try from 00a086df to 00a086e3 has its CatchHandler @ 00a0a0f6 */
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&local_15);
                    /* try { // try from 00a086fb to 00a086ff has its CatchHandler @ 00a0a0f4 */
  std::wstring::wstring((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&local_16)
  ;
                    /* try { // try from 00a08717 to 00a0871b has its CatchHandler @ 00a0a0f2 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&local_17);
                    /* try { // try from 00a08733 to 00a08737 has its CatchHandler @ 00a0a0ec */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&local_18);
                    /* try { // try from 00a0874f to 00a08753 has its CatchHandler @ 00a0a0ea */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&local_19);
                    /* try { // try from 00a08768 to 00a0876c has its CatchHandler @ 00a0a0b5 */
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&local_1a);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
                    /* try { // try from 00a08795 to 00a08799 has its CatchHandler @ 00a0a0a5 */
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&local_1b);
                    /* try { // try from 00a087b1 to 00a087b5 has its CatchHandler @ 00a0a095 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&local_1c);
                    /* try { // try from 00a087cd to 00a087d1 has its CatchHandler @ 00a0a085 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&local_1d);
                    /* try { // try from 00a087e9 to 00a087ed has its CatchHandler @ 00a0a075 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",&local_1e
            );
                    /* try { // try from 00a08805 to 00a08809 has its CatchHandler @ 00a0a065 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&local_1f)
  ;
                    /* try { // try from 00a08821 to 00a08825 has its CatchHandler @ 00a0a055 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&local_20);
                    /* try { // try from 00a0883d to 00a08841 has its CatchHandler @ 00a0a045 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&local_21);
                    /* try { // try from 00a08859 to 00a0885d has its CatchHandler @ 00a0a035 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&local_22);
                    /* try { // try from 00a08875 to 00a08879 has its CatchHandler @ 00a0a025 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&local_23);
                    /* try { // try from 00a08891 to 00a08895 has its CatchHandler @ 00a0a015 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&local_24);
                    /* try { // try from 00a088ad to 00a088b1 has its CatchHandler @ 00a0a005 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&local_25);
                    /* try { // try from 00a088c9 to 00a088cd has its CatchHandler @ 00a09ff5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&local_26);
                    /* try { // try from 00a088e5 to 00a088e9 has its CatchHandler @ 00a09fe5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&local_27);
                    /* try { // try from 00a08901 to 00a08905 has its CatchHandler @ 00a09fd5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&local_28);
                    /* try { // try from 00a0891d to 00a08921 has its CatchHandler @ 00a09fc5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&local_29);
                    /* try { // try from 00a08939 to 00a0893d has its CatchHandler @ 00a09fb5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&local_2a);
                    /* try { // try from 00a08955 to 00a08959 has its CatchHandler @ 00a09fa5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&local_2b);
                    /* try { // try from 00a08971 to 00a08975 has its CatchHandler @ 00a09f95 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&local_2c);
                    /* try { // try from 00a0898d to 00a08991 has its CatchHandler @ 00a09f85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&local_2d);
                    /* try { // try from 00a089a9 to 00a089ad has its CatchHandler @ 00a09f75 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&local_2e);
                    /* try { // try from 00a089c5 to 00a089c9 has its CatchHandler @ 00a09f65 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&local_2f);
                    /* try { // try from 00a089e1 to 00a089e5 has its CatchHandler @ 00a09f55 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&local_30);
                    /* try { // try from 00a089fd to 00a08a01 has its CatchHandler @ 00a09f45 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &local_31);
                    /* try { // try from 00a08a19 to 00a08a1d has its CatchHandler @ 00a09f35 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&local_32);
                    /* try { // try from 00a08a35 to 00a08a39 has its CatchHandler @ 00a09f25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&local_33);
                    /* try { // try from 00a08a51 to 00a08a55 has its CatchHandler @ 00a09f15 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&local_34);
                    /* try { // try from 00a08a6d to 00a08a71 has its CatchHandler @ 00a09f05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&local_35);
                    /* try { // try from 00a08a89 to 00a08a8d has its CatchHandler @ 00a09ef5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&local_36);
                    /* try { // try from 00a08aa5 to 00a08aa9 has its CatchHandler @ 00a09ee5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&local_37);
                    /* try { // try from 00a08ac1 to 00a08ac5 has its CatchHandler @ 00a09ed5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&local_38);
                    /* try { // try from 00a08add to 00a08ae1 has its CatchHandler @ 00a09ec5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &local_39);
                    /* try { // try from 00a08af9 to 00a08afd has its CatchHandler @ 00a09eb5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&local_3a);
                    /* try { // try from 00a08b15 to 00a08b19 has its CatchHandler @ 00a09ea5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&local_3b);
                    /* try { // try from 00a08b31 to 00a08b35 has its CatchHandler @ 00a09e95 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&local_3c);
                    /* try { // try from 00a08b4d to 00a08b51 has its CatchHandler @ 00a09e85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&local_3d);
                    /* try { // try from 00a08b69 to 00a08b6d has its CatchHandler @ 00a09e75 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&local_3e);
                    /* try { // try from 00a08b85 to 00a08b89 has its CatchHandler @ 00a09e65 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&local_3f);
                    /* try { // try from 00a08ba1 to 00a08ba5 has its CatchHandler @ 00a09e55 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&local_40);
                    /* try { // try from 00a08bbd to 00a08bc1 has its CatchHandler @ 00a09e45 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&local_41);
                    /* try { // try from 00a08bd9 to 00a08bdd has its CatchHandler @ 00a09e35 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&local_42);
                    /* try { // try from 00a08bf5 to 00a08bf9 has its CatchHandler @ 00a09e25 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&local_43);
                    /* try { // try from 00a08c11 to 00a08c15 has its CatchHandler @ 00a09e15 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&local_44);
                    /* try { // try from 00a08c2d to 00a08c31 has its CatchHandler @ 00a09e05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&local_45);
                    /* try { // try from 00a08c49 to 00a08c4d has its CatchHandler @ 00a09df5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&local_46);
                    /* try { // try from 00a08c65 to 00a08c69 has its CatchHandler @ 00a09de5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&local_47);
                    /* try { // try from 00a08c81 to 00a08c85 has its CatchHandler @ 00a09dd5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&local_48);
                    /* try { // try from 00a08c9d to 00a08ca1 has its CatchHandler @ 00a09dc5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&local_49)
  ;
                    /* try { // try from 00a08cb9 to 00a08cbd has its CatchHandler @ 00a09db5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&local_4a)
  ;
                    /* try { // try from 00a08cd5 to 00a08cd9 has its CatchHandler @ 00a09da5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&local_4b);
                    /* try { // try from 00a08cf1 to 00a08cf5 has its CatchHandler @ 00a09d95 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&local_4c);
                    /* try { // try from 00a08d0d to 00a08d11 has its CatchHandler @ 00a09d85 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&local_4d);
                    /* try { // try from 00a08d29 to 00a08d2d has its CatchHandler @ 00a09d75 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&local_4e);
                    /* try { // try from 00a08d45 to 00a08d49 has its CatchHandler @ 00a09d65 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&local_4f);
                    /* try { // try from 00a08d61 to 00a08d65 has its CatchHandler @ 00a09d55 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&local_50);
                    /* try { // try from 00a08d7d to 00a08d81 has its CatchHandler @ 00a09d45 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&local_51);
                    /* try { // try from 00a08d99 to 00a08d9d has its CatchHandler @ 00a09d35 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&local_52);
                    /* try { // try from 00a08db5 to 00a08db9 has its CatchHandler @ 00a09d25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&local_53)
  ;
                    /* try { // try from 00a08dd1 to 00a08dd5 has its CatchHandler @ 00a09d15 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&local_54)
  ;
                    /* try { // try from 00a08ded to 00a08df1 has its CatchHandler @ 00a09d05 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&local_55)
  ;
                    /* try { // try from 00a08e09 to 00a08e0d has its CatchHandler @ 00a09cf5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&local_56)
  ;
                    /* try { // try from 00a08e25 to 00a08e29 has its CatchHandler @ 00a09ce5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&local_57)
  ;
                    /* try { // try from 00a08e41 to 00a08e45 has its CatchHandler @ 00a09cd5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&local_58)
  ;
                    /* try { // try from 00a08e5a to 00a08e5e has its CatchHandler @ 00a09cc5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&local_59)
  ;
                    /* try { // try from 00a08e73 to 00a08e77 has its CatchHandler @ 00a09cb5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&local_5a)
  ;
                    /* try { // try from 00a08e8c to 00a08e90 has its CatchHandler @ 00a09ca5 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&local_5b)
  ;
                    /* try { // try from 00a08ea5 to 00a08ea9 has its CatchHandler @ 00a09c95 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&local_5c)
  ;
                    /* try { // try from 00a08ebe to 00a08ec2 has its CatchHandler @ 00a09c85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&local_5d);
                    /* try { // try from 00a08ed7 to 00a08edb has its CatchHandler @ 00a09c75 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &local_5e);
                    /* try { // try from 00a08ef0 to 00a08ef4 has its CatchHandler @ 00a09c65 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &local_5f);
                    /* try { // try from 00a08f09 to 00a08f0d has its CatchHandler @ 00a09c55 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &local_60);
                    /* try { // try from 00a08f22 to 00a08f26 has its CatchHandler @ 00a09c45 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &local_61);
                    /* try { // try from 00a08f3b to 00a08f3f has its CatchHandler @ 00a09c35 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &local_62);
                    /* try { // try from 00a08f54 to 00a08f58 has its CatchHandler @ 00a09c25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &local_63);
                    /* try { // try from 00a08f6d to 00a08f71 has its CatchHandler @ 00a09c15 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &local_64);
                    /* try { // try from 00a08f86 to 00a08f8a has its CatchHandler @ 00a09c05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &local_65);
                    /* try { // try from 00a08f9f to 00a08fa3 has its CatchHandler @ 00a09bf5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&local_66)
  ;
                    /* try { // try from 00a08fb8 to 00a08fbc has its CatchHandler @ 00a09be5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &local_67);
                    /* try { // try from 00a08fd1 to 00a08fd5 has its CatchHandler @ 00a09bd5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &local_68);
                    /* try { // try from 00a08fea to 00a08fee has its CatchHandler @ 00a09bc5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &local_69);
                    /* try { // try from 00a09003 to 00a09007 has its CatchHandler @ 00a09bb5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &local_6a);
                    /* try { // try from 00a0901c to 00a09020 has its CatchHandler @ 00a09ba5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &local_6b);
                    /* try { // try from 00a09035 to 00a09039 has its CatchHandler @ 00a09b95 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &local_6c);
                    /* try { // try from 00a0904e to 00a09052 has its CatchHandler @ 00a09b85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &local_6d);
                    /* try { // try from 00a09067 to 00a0906b has its CatchHandler @ 00a09b75 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &local_6e);
                    /* try { // try from 00a09080 to 00a09084 has its CatchHandler @ 00a09b65 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &local_6f);
                    /* try { // try from 00a09099 to 00a0909d has its CatchHandler @ 00a09b55 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&local_70);
                    /* try { // try from 00a090b2 to 00a090b6 has its CatchHandler @ 00a09b45 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&local_71);
                    /* try { // try from 00a090cb to 00a090cf has its CatchHandler @ 00a09b35 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&local_72);
                    /* try { // try from 00a090e4 to 00a090e8 has its CatchHandler @ 00a09b25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&local_73);
                    /* try { // try from 00a090fd to 00a09101 has its CatchHandler @ 00a09b15 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&local_74);
                    /* try { // try from 00a09116 to 00a0911a has its CatchHandler @ 00a09b05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &local_75);
                    /* try { // try from 00a0912f to 00a09133 has its CatchHandler @ 00a09af5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&local_76);
                    /* try { // try from 00a09148 to 00a0914c has its CatchHandler @ 00a09ae5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&local_77);
                    /* try { // try from 00a09161 to 00a09165 has its CatchHandler @ 00a09ad5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&local_78);
                    /* try { // try from 00a0917a to 00a0917e has its CatchHandler @ 00a09ac5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&local_79);
                    /* try { // try from 00a09193 to 00a09197 has its CatchHandler @ 00a09ab5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&local_7a);
                    /* try { // try from 00a091ac to 00a091b0 has its CatchHandler @ 00a09aa5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&local_7b);
                    /* try { // try from 00a091c5 to 00a091c9 has its CatchHandler @ 00a09a95 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&local_7c);
                    /* try { // try from 00a091de to 00a091e2 has its CatchHandler @ 00a09a85 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&local_7d);
                    /* try { // try from 00a091f7 to 00a091fb has its CatchHandler @ 00a09a75 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&local_7e);
                    /* try { // try from 00a09210 to 00a09214 has its CatchHandler @ 00a09a65 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&local_7f);
                    /* try { // try from 00a09229 to 00a0922d has its CatchHandler @ 00a09a55 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&local_80);
                    /* try { // try from 00a09242 to 00a09246 has its CatchHandler @ 00a09a45 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&local_81);
                    /* try { // try from 00a0925b to 00a0925f has its CatchHandler @ 00a09a35 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&local_82);
                    /* try { // try from 00a09274 to 00a09278 has its CatchHandler @ 00a09a25 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&local_83);
                    /* try { // try from 00a0928d to 00a09291 has its CatchHandler @ 00a09a15 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&local_84);
                    /* try { // try from 00a092a6 to 00a092aa has its CatchHandler @ 00a09a05 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&local_85);
                    /* try { // try from 00a092bf to 00a092c3 has its CatchHandler @ 00a099f5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&local_86);
                    /* try { // try from 00a092d8 to 00a092dc has its CatchHandler @ 00a099e6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&local_87);
                    /* try { // try from 00a092f1 to 00a092f5 has its CatchHandler @ 00a099e4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&local_88);
                    /* try { // try from 00a0930a to 00a0930e has its CatchHandler @ 00a099e2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&local_89);
                    /* try { // try from 00a09323 to 00a09327 has its CatchHandler @ 00a099d6 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&local_8a);
                    /* try { // try from 00a0933c to 00a09340 has its CatchHandler @ 00a099d4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&local_8b);
                    /* try { // try from 00a09355 to 00a09359 has its CatchHandler @ 00a099d2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&local_8c);
                    /* try { // try from 00a0936e to 00a09372 has its CatchHandler @ 00a099c6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&local_8d);
                    /* try { // try from 00a09387 to 00a0938b has its CatchHandler @ 00a099c4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&local_8e);
                    /* try { // try from 00a093a0 to 00a093a4 has its CatchHandler @ 00a099c2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&local_8f);
                    /* try { // try from 00a093b9 to 00a093bd has its CatchHandler @ 00a099b6 */
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&local_90);
                    /* try { // try from 00a093d2 to 00a093d6 has its CatchHandler @ 00a099b4 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&local_91);
                    /* try { // try from 00a093eb to 00a093ef has its CatchHandler @ 00a099b2 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&local_92);
                    /* try { // try from 00a09404 to 00a09408 has its CatchHandler @ 00a099a6 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&local_93);
                    /* try { // try from 00a0941d to 00a09421 has its CatchHandler @ 00a099a4 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&local_94);
                    /* try { // try from 00a09436 to 00a0943a has its CatchHandler @ 00a099a2 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&local_95);
                    /* try { // try from 00a0944f to 00a09453 has its CatchHandler @ 00a0999d */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&local_96);
                    /* try { // try from 00a09468 to 00a0946c has its CatchHandler @ 00a0999b */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&local_97);
                    /* try { // try from 00a0947e to 00a09482 has its CatchHandler @ 00a09966 */
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&local_98);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
                    /* try { // try from 00a094a8 to 00a094ac has its CatchHandler @ 00a09964 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&local_99);
                    /* try { // try from 00a094c1 to 00a094c5 has its CatchHandler @ 00a09962 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&local_9a);
                    /* try { // try from 00a094da to 00a094de has its CatchHandler @ 00a09956 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&local_9b);
                    /* try { // try from 00a094f3 to 00a094f7 has its CatchHandler @ 00a09954 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&local_9c);
                    /* try { // try from 00a0950c to 00a09510 has its CatchHandler @ 00a09952 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&local_9d);
                    /* try { // try from 00a09525 to 00a09529 has its CatchHandler @ 00a09946 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&local_9e);
                    /* try { // try from 00a0953e to 00a09542 has its CatchHandler @ 00a09944 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&local_9f);
                    /* try { // try from 00a09557 to 00a0955b has its CatchHandler @ 00a09942 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&local_a0);
                    /* try { // try from 00a09570 to 00a09574 has its CatchHandler @ 00a09936 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&local_a1);
                    /* try { // try from 00a09589 to 00a0958d has its CatchHandler @ 00a09934 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&local_a2);
                    /* try { // try from 00a095a2 to 00a095a6 has its CatchHandler @ 00a09932 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&local_a3);
                    /* try { // try from 00a095bb to 00a095bf has its CatchHandler @ 00a0992b */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&local_a4);
                    /* try { // try from 00a095d4 to 00a095d8 has its CatchHandler @ 00a09929 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&local_a5);
                    /* try { // try from 00a095ea to 00a095ee has its CatchHandler @ 00a098f4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&local_a6);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
                    /* try { // try from 00a09614 to 00a09618 has its CatchHandler @ 00a098f2 */
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&local_a7);
                    /* try { // try from 00a0962d to 00a09631 has its CatchHandler @ 00a098e6 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&local_a8);
                    /* try { // try from 00a09646 to 00a0964a has its CatchHandler @ 00a098e4 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&local_a9);
                    /* try { // try from 00a0965f to 00a09663 has its CatchHandler @ 00a098e2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&local_aa);
                    /* try { // try from 00a09678 to 00a0967c has its CatchHandler @ 00a098d6 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&local_ab);
                    /* try { // try from 00a09691 to 00a09695 has its CatchHandler @ 00a098d4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&local_ac);
                    /* try { // try from 00a096aa to 00a096ae has its CatchHandler @ 00a098d2 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&local_ad);
                    /* try { // try from 00a096c3 to 00a096c7 has its CatchHandler @ 00a098c6 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&local_ae)
  ;
                    /* try { // try from 00a096dc to 00a096e0 has its CatchHandler @ 00a098c4 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&local_af);
                    /* try { // try from 00a096f5 to 00a096f9 has its CatchHandler @ 00a098c2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&local_b0);
                    /* try { // try from 00a0970e to 00a09712 has its CatchHandler @ 00a098b6 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&local_b1)
  ;
                    /* try { // try from 00a09727 to 00a0972b has its CatchHandler @ 00a098b4 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&local_b2);
                    /* try { // try from 00a09740 to 00a09744 has its CatchHandler @ 00a098b2 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&local_b3);
                    /* try { // try from 00a09759 to 00a0975d has its CatchHandler @ 00a098a9 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&local_b4);
                    /* try { // try from 00a09772 to 00a09776 has its CatchHandler @ 00a098a7 */
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&local_b5);
                    /* try { // try from 00a0978b to 00a0978f has its CatchHandler @ 00a098a5 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&local_b6)
  ;
                    /* try { // try from 00a097a1 to 00a097a5 has its CatchHandler @ 00a09874 */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&local_b7);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
                    /* try { // try from 00a097cb to 00a097cf has its CatchHandler @ 00a09872 */
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&local_b8);
                    /* try { // try from 00a097e4 to 00a097e8 has its CatchHandler @ 00a0986d */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&local_b9);
                    /* try { // try from 00a097fd to 00a09801 has its CatchHandler @ 00a0986b */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&local_ba);
                    /* try { // try from 00a09813 to 00a09817 has its CatchHandler @ 00a0983a */
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&local_bb);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  return;
}

/* address=00a0a420
   symbol=CSoundObject::setSoundBankNameIndex */

/* WARNING: Removing unreachable block (ram,0x00a0a581) */
/* WARNING: Removing unreachable block (ram,0x00a0a591) */
/* CSoundObject::setSoundBankNameIndex(unsigned int) */

void __thiscall CSoundObject::setSoundBankNameIndex(CSoundObject *this,uint param_1)

{
  int *piVar1;
  int iVar2;
  CSoundBankDataInformation *this_00;
  long lVar3;
  long local_48 [2];
  long local_38 [3];

  *(uint *)(this + 0x114) = param_1;
  lVar3 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar3 + 0x100);
  if (this_00 != (CSoundBankDataInformation *)0x0) {
    CSoundBankDataInformation::getSoundNameByCategoryIndex
              ((uint)(wstring_conflict *)local_48,(uint)this_00);
                    /* try { // try from 00a0a483 to 00a0a487 has its CatchHandler @ 00a0a58c */
    CSoundBankDataInformation::getCategoryNameByID((uint)(wstring_conflict *)local_38);
                    /* try { // try from 00a0a491 to 00a0a495 has its CatchHandler @ 00a0a566 */
    lVar3 = CSoundBankDataInformation::getSoundDataObject
                      (this_00,(wstring_conflict *)local_38,(wstring_conflict *)local_48);
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
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if ((lVar3 != 0) &&
       ((setSoundBankGuid(this,*(longlong *)(lVar3 + 0x20)), this[0x121] != (CSoundObject)0x0 ||
        (this[0x120] != (CSoundObject)0x0)))) {
      play(this);
    }
  }
  return;
}

/* export-summary functions=20 failures=0 */
