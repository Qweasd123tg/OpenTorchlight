/* Targeted Ghidra class export.
   namespace=CAstarPathfinder
   Treat pseudocode as navigation evidence. */


/* address=00592220
   symbol=CAstarPathfinder::reachedGoal */

/* CAstarPathfinder::reachedGoal() */

undefined8 __thiscall CAstarPathfinder::reachedGoal(CAstarPathfinder *this)

{
  undefined8 uVar1;

  uVar1 = 1;
  if (this[0x38] != (CAstarPathfinder)0x0) {
    uVar1 = CONCAT71((int7)((ulong)*(long *)(this + 0x28) >> 8),
                     *(long *)(*(long *)(this + 0x28) + 0x18) == 0);
  }
  return uVar1;
}



/* address=00592240
   symbol=CAstarPathfinder::tileIndex */

/* CAstarPathfinder::tileIndex(unsigned int, unsigned int) */

int __thiscall CAstarPathfinder::tileIndex(CAstarPathfinder *this,uint param_1,uint param_2)

{
  return param_2 * *(int *)(this + 0x40) + param_1;
}



/* address=00592250
   symbol=CAstarPathfinder::tileFree */

/* CAstarPathfinder::tileFree(unsigned int, unsigned int, ENodeDirection) */

undefined8 CAstarPathfinder::tileFree(long param_1,uint param_2,uint param_3)

{
  long lVar1;

  if ((param_2 < *(uint *)(param_1 + 0x40)) && (param_3 < *(uint *)(param_1 + 0x3c))) {
    if (*(short *)(*(long *)(*(long *)(param_1 + 0x50) + (ulong)param_2 * 8) + (ulong)param_3 * 2) <
        1) {
      if (*(char *)(param_1 + 0x69) != '\0') {
        return 1;
      }
      lVar1 = *(long *)(*(long *)(param_1 + 0x58) + (ulong)param_2 * 8);
      return CONCAT71((int7)((ulong)lVar1 >> 8),*(short *)(lVar1 + (ulong)param_3 * 2) < 1);
    }
  }
  return 0;
}



/* address=005922a0
   symbol=CAstarPathfinder::advanceNextNode */

/* CAstarPathfinder::advanceNextNode() */

void __thiscall CAstarPathfinder::advanceNextNode(CAstarPathfinder *this)

{
  *(undefined8 *)(this + 0x28) = *(undefined8 *)(*(long *)(this + 0x28) + 0x18);
  return;
}



/* address=005922b0
   symbol=CAstarPathfinder::getNodeX */

/* CAstarPathfinder::getNodeX() */

float __thiscall CAstarPathfinder::getNodeX(CAstarPathfinder *this)

{
  return (float)*(int *)(*(long *)(this + 0x28) + 0xc) * *(float *)(this + 0x44) +
         *(float *)(this + 0x44) * DAT_00fa4810 + *(float *)(this + 0x60);
}



/* address=005922e0
   symbol=CAstarPathfinder::getNodeY */

/* CAstarPathfinder::getNodeY() */

float __thiscall CAstarPathfinder::getNodeY(CAstarPathfinder *this)

{
  return (float)*(int *)(*(long *)(this + 0x28) + 0x10) * *(float *)(this + 0x44) +
         *(float *)(this + 0x44) * DAT_00fa4810 + *(float *)(this + 100);
}



/* address=00592310
   symbol=CAstarPathfinder::getNextNodeX */

/* CAstarPathfinder::getNextNodeX() */

float __thiscall CAstarPathfinder::getNextNodeX(CAstarPathfinder *this)

{
  return (float)*(int *)(*(long *)(*(long *)(this + 0x28) + 0x18) + 0xc) * *(float *)(this + 0x44) +
         *(float *)(this + 0x44) * DAT_00fa4810 + *(float *)(this + 0x60);
}



/* address=00592340
   symbol=CAstarPathfinder::getNextNodeY */

/* CAstarPathfinder::getNextNodeY() */

float __thiscall CAstarPathfinder::getNextNodeY(CAstarPathfinder *this)

{
  return (float)*(int *)(*(long *)(*(long *)(this + 0x28) + 0x18) + 0x10) * *(float *)(this + 0x44)
         + *(float *)(this + 0x44) * DAT_00fa4810 + *(float *)(this + 100);
}



/* address=00592370
   symbol=CAstarPathfinder::reverseNodes */

/* CAstarPathfinder::reverseNodes(CAstarPathfinder::CAstarNode*) */

CAstarNode * __thiscall CAstarPathfinder::reverseNodes(CAstarPathfinder *this,CAstarNode *param_1)

{
  CAstarNode *pCVar1;
  CAstarNode *pCVar2;
  CAstarNode *pCVar3;
  CAstarNode *pCVar4;

  if (param_1 != (CAstarNode *)0x0) {
    pCVar1 = param_1;
    pCVar2 = *(CAstarNode **)(param_1 + 0x18);
    pCVar4 = (CAstarNode *)0x0;
    if (*(CAstarNode **)(param_1 + 0x18) == (CAstarNode *)0x0) {
      pCVar3 = (CAstarNode *)0x0;
    }
    else {
      do {
        param_1 = pCVar2;
        pCVar3 = pCVar1;
        *(CAstarNode **)(pCVar3 + 0x18) = pCVar4;
        pCVar1 = param_1;
        pCVar2 = *(CAstarNode **)(param_1 + 0x18);
        pCVar4 = pCVar3;
      } while (*(CAstarNode **)(param_1 + 0x18) != (CAstarNode *)0x0);
    }
    *(CAstarNode **)(param_1 + 0x18) = pCVar3;
  }
  return param_1;
}



/* address=005923c0
   symbol=CAstarPathfinder::returnBestNode */

/* CAstarPathfinder::returnBestNode() */

void __thiscall CAstarPathfinder::returnBestNode(CAstarPathfinder *this)

{
  long lVar1;

  lVar1 = *(long *)(*(long *)(this + 0x18) + 0x60);
  if (lVar1 != 0) {
    *(undefined8 *)(*(long *)(this + 0x18) + 0x60) = *(undefined8 *)(lVar1 + 0x60);
    *(undefined8 *)(lVar1 + 0x60) = *(undefined8 *)(*(long *)(this + 0x20) + 0x60);
    *(long *)(*(long *)(this + 0x20) + 0x60) = lVar1;
    return;
  }
  this[0x38] = (CAstarPathfinder)0x0;
  return;
}



/* address=00592400
   symbol=CAstarPathfinder::openNode */

/* CAstarPathfinder::openNode(unsigned int) */

void __thiscall CAstarPathfinder::openNode(CAstarPathfinder *this,uint param_1)

{
  long lVar1;

  lVar1 = *(long *)(*(long *)(this + 0x18) + 0x60);
  if (lVar1 != 0) {
    if (*(uint *)(lVar1 + 0x14) == param_1) {
      return;
    }
    do {
      lVar1 = *(long *)(lVar1 + 0x60);
      if (lVar1 == 0) {
        return;
      }
    } while (*(uint *)(lVar1 + 0x14) != param_1);
  }
  return;
}



/* address=00592430
   symbol=CAstarPathfinder::closedNode */

/* CAstarPathfinder::closedNode(unsigned int) */

void __thiscall CAstarPathfinder::closedNode(CAstarPathfinder *this,uint param_1)

{
  long lVar1;

  lVar1 = *(long *)(*(long *)(this + 0x20) + 0x60);
  if (lVar1 != 0) {
    if (*(uint *)(lVar1 + 0x14) == param_1) {
      return;
    }
    do {
      lVar1 = *(long *)(lVar1 + 0x60);
      if (lVar1 == 0) {
        return;
      }
    } while (*(uint *)(lVar1 + 0x14) != param_1);
  }
  return;
}



/* address=00592460
   symbol=CAstarPathfinder::insert */

/* CAstarPathfinder::insert(CAstarPathfinder::CAstarNode*) */

void __thiscall CAstarPathfinder::insert(CAstarPathfinder *this,CAstarNode *param_1)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;

  pfVar2 = *(float **)(this + 0x18);
  pfVar3 = *(float **)(pfVar2 + 0x18);
  if (pfVar3 != (float *)0x0) {
    fVar1 = *(float *)param_1;
    if (*pfVar3 <= fVar1 && fVar1 != *pfVar3) {
      do {
        pfVar2 = pfVar3;
        pfVar3 = *(float **)(pfVar2 + 0x18);
        if (pfVar3 == (float *)0x0) break;
      } while (*pfVar3 <= fVar1 && fVar1 != *pfVar3);
    }
    *(float **)(param_1 + 0x60) = pfVar3;
  }
  *(CAstarNode **)(pfVar2 + 0x18) = param_1;
  return;
}



/* address=005924b0
   symbol=CAstarPathfinder::_GLOBAL__I_CAstarPathfinder */

/* CAstarPathfinder::CAstarPathfinder(float, float, unsigned int, unsigned int, short**, short**,
   float) */

void CAstarPathfinder::_GLOBAL__I_CAstarPathfinder(void)

{
  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  return;
}



/* address=00592520
   symbol=CAstarPathfinder::pop */

/* CAstarPathfinder::pop() */

undefined8 __thiscall CAstarPathfinder::pop(CAstarPathfinder *this)

{
  undefined8 *__ptr;
  undefined8 uVar1;

  __ptr = *(undefined8 **)(*(long *)(this + 0x30) + 8);
  uVar1 = *__ptr;
  *(undefined8 *)(*(long *)(this + 0x30) + 8) = __ptr[1];
  free(__ptr);
  return uVar1;
}



/* address=00592540
   symbol=CAstarPathfinder::freeNodes */

/* CAstarPathfinder::freeNodes() */

void __thiscall CAstarPathfinder::freeNodes(CAstarPathfinder *this)

{
  void *pvVar1;
  void *pvVar2;

  if (*(long *)(this + 0x18) != 0) {
    pvVar2 = *(void **)(*(long *)(this + 0x18) + 0x60);
    while (pvVar2 != (void *)0x0) {
      pvVar1 = *(void **)((long)pvVar2 + 0x60);
      free(pvVar2);
      pvVar2 = pvVar1;
    }
  }
  if (*(long *)(this + 0x20) != 0) {
    pvVar2 = *(void **)(*(long *)(this + 0x20) + 0x60);
    while (pvVar2 != (void *)0x0) {
      pvVar1 = *(void **)((long)pvVar2 + 0x60);
      free(pvVar2);
      pvVar2 = pvVar1;
    }
  }
  return;
}



/* address=005925a0
   symbol=CAstarPathfinder::push */

/* CAstarPathfinder::push(CAstarPathfinder::CAstarNode*) */

void __thiscall CAstarPathfinder::push(CAstarPathfinder *this,CAstarNode *param_1)

{
  long lVar1;
  undefined8 *puVar2;

  puVar2 = calloc(1,0x10);
  *puVar2 = param_1;
  lVar1 = *(long *)(this + 0x30);
  puVar2[1] = *(undefined8 *)(lVar1 + 8);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  return;
}



/* address=005925f0
   symbol=CAstarPathfinder::propagateDown */

/* CAstarPathfinder::propagateDown(CAstarPathfinder::CAstarNode*) */

void __thiscall CAstarPathfinder::propagateDown(CAstarPathfinder *this,CAstarNode *param_1)

{
  CAstarNode *pCVar1;
  float fVar2;
  long lVar3;
  CAstarNode *pCVar4;
  long lVar5;
  float fVar6;
  float fVar7;

  fVar2 = DAT_00fa47fc;
  fVar7 = *(float *)(param_1 + 8);
  pCVar4 = param_1;
  do {
    while( true ) {
      pCVar1 = *(CAstarNode **)(pCVar4 + 0x20);
      if (pCVar1 == (CAstarNode *)0x0) goto LAB_00592680;
      fVar6 = fVar7 + fVar2;
      if (*(float *)(pCVar1 + 8) <= fVar6) break;
      *(float *)(pCVar1 + 8) = fVar6;
      *(CAstarNode **)(pCVar1 + 0x18) = param_1;
      pCVar4 = pCVar4 + 8;
      *(float *)pCVar1 = fVar6 + *(float *)(pCVar1 + 4);
      push(this,pCVar1);
      if (pCVar4 == param_1 + 0x40) goto LAB_00592680;
    }
    pCVar4 = pCVar4 + 8;
  } while (pCVar4 != param_1 + 0x40);
LAB_00592680:
  lVar5 = *(long *)(*(long *)(this + 0x30) + 8);
  do {
    if (lVar5 == 0) {
      return;
    }
    lVar3 = pop(this);
    lVar5 = lVar3;
    do {
      pCVar4 = *(CAstarNode **)(lVar5 + 0x20);
      if (pCVar4 == (CAstarNode *)0x0) goto LAB_00592680;
      fVar7 = DAT_00fa47fc + *(float *)(lVar3 + 8);
      if (fVar7 < *(float *)(pCVar4 + 8)) {
        *(float *)(pCVar4 + 8) = fVar7;
        *(long *)(pCVar4 + 0x18) = lVar3;
        *(float *)pCVar4 = fVar7 + *(float *)(pCVar4 + 4);
        push(this,pCVar4);
      }
      lVar5 = lVar5 + 8;
    } while (lVar5 != lVar3 + 0x40);
    lVar5 = *(long *)(*(long *)(this + 0x30) + 8);
  } while( true );
}



/* address=00592710
   symbol=CAstarPathfinder::generateSuccessor */

/* CAstarPathfinder::generateSuccessor(CAstarPathfinder::CAstarNode*, unsigned int, unsigned int,
   unsigned int, unsigned int) */

void __thiscall
CAstarPathfinder::generateSuccessor
          (CAstarPathfinder *this,CAstarNode *param_1,uint param_2,uint param_3,uint param_4,
          uint param_5)

{
  float *pfVar1;
  float *pfVar2;
  CAstarNode *pCVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  CAstarNode *pCVar7;
  float fVar8;
  float fVar9;

  pfVar1 = *(float **)(this + 0x18);
  fVar9 = DAT_00fa47fc + *(float *)(param_1 + 8);
  fVar8 = (float)(*(int *)(this + 0x40) * param_3 + param_2);
  do {
    pfVar1 = *(float **)(pfVar1 + 0x18);
    if (pfVar1 == (float *)0x0) {
      pCVar3 = *(CAstarNode **)(*(long *)(this + 0x20) + 0x60);
      goto joined_r0x0059275e;
    }
  } while (fVar8 != pfVar1[5]);
  uVar4 = 0;
  pCVar3 = param_1;
  do {
    if (*(long *)(pCVar3 + 0x20) == 0) break;
    uVar4 = uVar4 + 1;
    pCVar3 = pCVar3 + 8;
  } while (uVar4 != 8);
  *(float **)(param_1 + (ulong)uVar4 * 8 + 0x20) = pfVar1;
  if (fVar9 < pfVar1[2]) {
    pfVar1[2] = fVar9;
    *(CAstarNode **)(pfVar1 + 6) = param_1;
    *pfVar1 = fVar9 + pfVar1[1];
    return;
  }
  return;
joined_r0x0059275e:
  if (pCVar3 == (CAstarNode *)0x0) goto LAB_00592764;
  if (fVar8 == *(float *)(pCVar3 + 0x14)) {
    uVar4 = 0;
    pCVar7 = param_1;
    goto LAB_00592860;
  }
  pCVar3 = *(CAstarNode **)(pCVar3 + 0x60);
  goto joined_r0x0059275e;
  while( true ) {
    uVar4 = uVar4 + 1;
    pCVar7 = pCVar7 + 8;
    if (uVar4 == 8) break;
LAB_00592860:
    if (*(long *)(pCVar7 + 0x20) == 0) break;
  }
  *(CAstarNode **)(param_1 + (ulong)uVar4 * 8 + 0x20) = pCVar3;
  if (fVar9 < *(float *)(pCVar3 + 8)) {
    *(float *)(pCVar3 + 8) = fVar9;
    *(CAstarNode **)(pCVar3 + 0x18) = param_1;
    *(float *)pCVar3 = fVar9 + *(float *)(pCVar3 + 4);
    propagateDown(this,pCVar3);
    return;
  }
  return;
LAB_00592764:
  pfVar2 = calloc(1,0x68);
  *(CAstarNode **)(pfVar2 + 6) = param_1;
  pfVar2[2] = fVar9;
  pfVar2[5] = fVar8;
  pfVar2[3] = (float)param_2;
  pfVar2[4] = (float)param_3;
  fVar8 = (float)(int)(param_2 - param_4) * (float)(int)(param_2 - param_4) +
          (float)(int)(param_3 - param_5) * (float)(int)(param_3 - param_5);
  fVar9 = fVar9 + fVar8;
  pfVar2[1] = fVar8;
  *pfVar2 = fVar9;
  pfVar1 = *(float **)(this + 0x18);
  pfVar5 = *(float **)(pfVar1 + 0x18);
  if (*(float **)(pfVar1 + 0x18) != (float *)0x0) {
    do {
      pfVar6 = pfVar5;
      if (fVar9 < *pfVar5 || fVar9 == *pfVar5) break;
      pfVar6 = *(float **)(pfVar5 + 0x18);
      pfVar1 = pfVar5;
      pfVar5 = pfVar6;
    } while (pfVar6 != (float *)0x0);
    *(float **)(pfVar2 + 0x18) = pfVar6;
  }
  *(float **)(pfVar1 + 0x18) = pfVar2;
  uVar4 = 0;
  pCVar3 = param_1;
  do {
    if (*(long *)(pCVar3 + 0x20) == 0) break;
    uVar4 = uVar4 + 1;
    pCVar3 = pCVar3 + 8;
  } while (uVar4 != 8);
  if ((*(long *)(this + 0x10) == 0) ||
     (fVar8 = *(float *)(*(long *)(this + 0x10) + 4), pfVar2[1] <= fVar8 && fVar8 != pfVar2[1])) {
    *(float **)(this + 0x10) = pfVar2;
  }
  *(float **)(param_1 + (ulong)uVar4 * 8 + 0x20) = pfVar2;
  return;
}



/* address=00592900
   symbol=CAstarPathfinder::generateSuccessors */

/* CAstarPathfinder::generateSuccessors(CAstarPathfinder::CAstarNode*, unsigned int, unsigned int)
    */

void __thiscall
CAstarPathfinder::generateSuccessors
          (CAstarPathfinder *this,CAstarNode *param_1,uint param_2,uint param_3)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  char local_41;

  uVar4 = *(uint *)(param_1 + 0x10);
  uVar3 = *(uint *)(param_1 + 0xc);
  uVar5 = uVar4 - 1;
  cVar1 = tileFree(this,uVar3,uVar5,1);
  if (cVar1 == '\0') {
    uVar6 = uVar3 - 1;
    local_41 = '\0';
  }
  else {
    uVar6 = uVar3 - 1;
    cVar1 = tileFree(this,uVar6,uVar4,4);
    if ((cVar1 == '\0') || (cVar1 = tileFree(this,uVar6,uVar5,6), cVar1 == '\0')) {
      local_41 = '\x01';
    }
    else {
      generateSuccessor(this,param_1,uVar6,uVar5,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar3 = *(uint *)(param_1 + 0xc);
      uVar5 = uVar4 - 1;
      uVar6 = uVar3 - 1;
      local_41 = tileFree(this,uVar3,uVar5,1);
    }
  }
  cVar1 = tileFree(this,uVar6,uVar5,1);
  if (cVar1 == '\0') {
    uVar6 = uVar3 + 1;
    cVar1 = tileFree(this,uVar6,uVar5,1);
    if (cVar1 != '\0') goto LAB_0059297e;
LAB_00592ba9:
    if (local_41 == '\0') goto LAB_00592989;
    cVar1 = tileFree(this,uVar6,uVar4,3);
    if ((cVar1 != '\0') && (cVar1 = tileFree(this,uVar6,uVar5,5), cVar1 != '\0')) {
      generateSuccessor(this,param_1,uVar6,uVar5,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar3 = *(uint *)(param_1 + 0xc);
      uVar5 = uVar4 - 1;
      goto LAB_00592989;
    }
  }
  else {
LAB_0059297e:
    if (local_41 != '\0') {
      generateSuccessor(this,param_1,uVar3,uVar5,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar3 = *(uint *)(param_1 + 0xc);
      uVar5 = uVar4 - 1;
      uVar6 = uVar3 + 1;
      local_41 = tileFree(this,uVar3,uVar5,1);
      goto LAB_00592ba9;
    }
LAB_00592989:
    uVar6 = uVar3 + 1;
  }
  cVar1 = tileFree(this,uVar6,uVar5,1);
  if (cVar1 == '\0') {
    uVar5 = uVar4 + 1;
    cVar1 = tileFree(this,uVar6,uVar5,1);
    if (cVar1 != '\0') goto LAB_00592ac0;
  }
  else {
LAB_00592ac0:
    uVar5 = uVar4 + 1;
    cVar1 = tileFree(this,uVar6,uVar4,3);
    if (cVar1 != '\0') {
      generateSuccessor(this,param_1,uVar6,uVar4,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar3 = *(uint *)(param_1 + 0xc);
      uVar5 = uVar4 + 1;
    }
  }
  cVar1 = tileFree(this,uVar3,uVar5,2);
  cVar2 = '\0';
  if (cVar1 != '\0') {
    uVar6 = uVar3 + 1;
    cVar1 = tileFree(this,uVar6,uVar4,3);
    if ((cVar1 == '\0') || (cVar1 = tileFree(this,uVar6,uVar5,7), cVar1 == '\0')) {
      cVar2 = '\x01';
    }
    else {
      generateSuccessor(this,param_1,uVar6,uVar5,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar3 = *(uint *)(param_1 + 0xc);
      uVar5 = uVar4 + 1;
      cVar2 = tileFree(this,uVar3,uVar5,2);
    }
  }
  uVar6 = uVar3 - 1;
  cVar1 = tileFree(this,uVar6,uVar5,1);
  if ((cVar1 != '\0') || (cVar1 = tileFree(this,uVar3 + 1,uVar5,1), cVar1 != '\0')) {
    if (cVar2 == '\0') goto LAB_00592a35;
    generateSuccessor(this,param_1,uVar3,uVar5,param_2,param_3);
    uVar4 = *(uint *)(param_1 + 0x10);
    uVar3 = *(uint *)(param_1 + 0xc);
    uVar5 = uVar4 + 1;
    uVar6 = uVar3 - 1;
    cVar2 = tileFree(this,uVar3,uVar5,2);
  }
  if (cVar2 == '\0') {
    uVar6 = uVar3 - 1;
  }
  else {
    cVar1 = tileFree(this,uVar6,uVar4,4);
    if ((cVar1 != '\0') && (cVar1 = tileFree(this,uVar6,uVar5,8), cVar1 != '\0')) {
      generateSuccessor(this,param_1,uVar6,uVar5,param_2,param_3);
      uVar4 = *(uint *)(param_1 + 0x10);
      uVar6 = *(int *)(param_1 + 0xc) - 1;
    }
  }
LAB_00592a35:
  cVar1 = tileFree(this,uVar6,uVar4 - 1,1);
  if ((cVar1 == '\0') && (cVar1 = tileFree(this,uVar6,uVar4 + 1,1), cVar1 == '\0')) {
    return;
  }
  cVar1 = tileFree(this,uVar6,uVar4,4);
  if (cVar1 == '\0') {
    return;
  }
  generateSuccessor(this,param_1,uVar6,uVar4,param_2,param_3);
  return;
}



/* address=00592da0
   symbol=CAstarPathfinder::createPath */

/* CAstarPathfinder::createPath(int, int, int, int, bool) */

void __thiscall
CAstarPathfinder::createPath
          (CAstarPathfinder *this,int param_1,int param_2,int param_3,int param_4,bool param_5)

{
  int iVar1;
  int iVar2;
  CAstarNode *pCVar3;
  void *pvVar4;
  float *pfVar5;
  CAstarNode *pCVar6;
  CAstarNode *pCVar7;
  CAstarNode *pCVar8;
  int iVar9;
  float fVar10;

  iVar1 = *(int *)(this + 0x40);
  *(undefined8 *)(this + 0x10) = 0;
  this[0x38] = (CAstarPathfinder)0x1;
  free(*(void **)(this + 0x18));
  free(*(void **)(this + 0x20));
  pvVar4 = calloc(1,0x68);
  *(void **)(this + 0x18) = pvVar4;
  pvVar4 = calloc(1,0x68);
  *(void **)(this + 0x20) = pvVar4;
  pfVar5 = calloc(1,0x68);
  pfVar5[2] = 0.0;
  fVar10 = (float)(param_3 - param_1) * (float)(param_3 - param_1) +
           (float)(param_4 - param_2) * (float)(param_4 - param_2);
  pfVar5[1] = fVar10;
  *pfVar5 = fVar10 + 0.0;
  iVar2 = *(int *)(this + 0x40);
  pfVar5[3] = (float)param_3;
  pfVar5[4] = (float)param_4;
  iVar9 = 0;
  pfVar5[5] = (float)(iVar2 * param_4 + param_3);
  *(float **)(*(long *)(this + 0x18) + 0x60) = pfVar5;
  while( true ) {
    pCVar6 = *(CAstarNode **)(*(long *)(this + 0x18) + 0x60);
    if (pCVar6 == (CAstarNode *)0x0) {
      this[0x38] = (CAstarPathfinder)0x0;
    }
    else {
      *(undefined8 *)(*(long *)(this + 0x18) + 0x60) = *(undefined8 *)(pCVar6 + 0x60);
      *(undefined8 *)(pCVar6 + 0x60) = *(undefined8 *)(*(long *)(this + 0x20) + 0x60);
      *(CAstarNode **)(*(long *)(this + 0x20) + 0x60) = pCVar6;
    }
    if (((this[0x68] != (CAstarPathfinder)0x0) &&
        (pCVar8 = *(CAstarNode **)(this + 0x10), pCVar8 != (CAstarNode *)0x0)) &&
       (*(float *)(pCVar8 + 4) <= DAT_00fa4824 && DAT_00fa4824 != *(float *)(pCVar8 + 4))) break;
    pCVar8 = pCVar6;
    if ((pCVar6 == (CAstarNode *)0x0) || (*(int *)(this + 0x6c) < iVar9)) {
      if (*(long *)(this + 0x10) == 0) {
        this[0x38] = (CAstarPathfinder)0x0;
      }
      else {
        this[0x6a] = (CAstarPathfinder)0x0;
        pCVar8 = *(CAstarNode **)(this + 0x10);
      }
LAB_00592f07:
      if ((param_5) && (pCVar8 != (CAstarNode *)0x0)) {
        pCVar6 = *(CAstarNode **)(pCVar8 + 0x18);
        if (pCVar6 != (CAstarNode *)0x0) {
          pCVar3 = pCVar6;
          pCVar7 = (CAstarNode *)0x0;
          do {
            pCVar6 = pCVar8;
            pCVar8 = pCVar3;
            *(CAstarNode **)(pCVar6 + 0x18) = pCVar7;
            pCVar3 = *(CAstarNode **)(pCVar8 + 0x18);
            pCVar7 = pCVar6;
          } while (*(CAstarNode **)(pCVar8 + 0x18) != (CAstarNode *)0x0);
        }
        *(CAstarNode **)(pCVar8 + 0x18) = pCVar6;
      }
      *(CAstarNode **)(this + 0x28) = pCVar8;
      return;
    }
    if (*(int *)(pCVar6 + 0x14) == iVar1 * param_2 + param_1) goto LAB_00592f07;
    iVar9 = iVar9 + 1;
    generateSuccessors(this,pCVar6,param_1,param_2);
  }
  this[0x6a] = (CAstarPathfinder)0x0;
  goto LAB_00592f07;
}



/* address=00592f70
   symbol=CAstarPathfinder::findNearestWideOpen */

/* CAstarPathfinder::findNearestWideOpen(unsigned int, unsigned int, unsigned int, unsigned int,
   unsigned int&, unsigned int&) */

void __thiscall
CAstarPathfinder::findNearestWideOpen
          (CAstarPathfinder *this,uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5,
          uint *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  float local_4c;

  uVar7 = param_3 - 0x10;
  fVar1 = *(float *)(this + 0x44);
  fVar2 = *(float *)(this + 0x60);
  fVar3 = *(float *)(this + 100);
  if ((int)uVar7 <= (int)(param_3 + 0x10)) {
    iVar6 = param_4 + 0x10;
    local_4c = DAT_00fa8818;
    do {
      if ((int)(param_4 - 0x10) <= iVar6) {
        uVar5 = param_4 - 0x10;
        do {
          while (((((-1 < (int)uVar5 && (-1 < (int)uVar7)) &&
                   (cVar4 = tileFree(this,uVar7,uVar5,0), cVar4 != '\0')) &&
                  ((cVar4 = tileFree(this,uVar7,uVar5 - 1,0), cVar4 != '\0' &&
                   (cVar4 = tileFree(this,uVar7,uVar5 + 1,0), cVar4 != '\0')))) &&
                 ((cVar4 = tileFree(this,uVar7 - 1,uVar5,0), cVar4 != '\0' &&
                  ((cVar4 = tileFree(this,uVar7 + 1,uVar5,0), cVar4 != '\0' &&
                   (fVar8 = ((float)(int)uVar7 * *(float *)(this + 0x44) + *(float *)(this + 0x60))
                            - ((float)param_3 * fVar1 + fVar2),
                   fVar9 = ((float)(int)uVar5 * *(float *)(this + 0x44) + *(float *)(this + 100)) -
                           (fVar1 * (float)param_4 + fVar3),
                   fVar8 = SQRT(fVar8 * fVar8 + 0.0 + fVar9 * fVar9), fVar8 < local_4c))))))) {
            *param_5 = uVar7;
            *param_6 = uVar5;
            uVar5 = uVar5 + 1;
            local_4c = fVar8;
            if (iVar6 < (int)uVar5) goto LAB_00593110;
          }
          uVar5 = uVar5 + 1;
        } while ((int)uVar5 <= iVar6);
      }
LAB_00593110:
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 <= (int)(param_3 + 0x10));
    if (local_4c != DAT_00fa8818) {
      return;
    }
    if (NAN(local_4c) || NAN(DAT_00fa8818)) {
      return;
    }
  }
  *param_5 = param_1;
  *param_6 = param_2;
  return;
}



/* address=00593160
   symbol=CAstarPathfinder::findNearestOpen */

/* WARNING: Type propagation algorithm not settling */
/* CAstarPathfinder::findNearestOpen(unsigned int, unsigned int, unsigned int, unsigned int,
   unsigned int&, unsigned int&) */

void __thiscall
CAstarPathfinder::findNearestOpen
          (CAstarPathfinder *this,uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5,
          uint *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  float fVar8;
  float fVar9;

  uVar7 = param_3 - 0x10;
  fVar1 = *(float *)(this + 0x44);
  fVar2 = *(float *)(this + 0x60);
  fVar3 = *(float *)(this + 100);
  if ((int)uVar7 <= (int)(param_3 + 0x10)) {
    uVar5 = param_4 - 0x10;
    fVar4 = DAT_00fa8818;
    do {
      while ((int)uVar5 <= (int)(param_4 + 0x10)) {
        if (((((int)uVar5 < 0) || ((int)uVar7 < 0)) ||
            (cVar6 = tileFree(this,uVar7,uVar5,0), cVar6 == '\0')) ||
           (fVar8 = ((float)(int)uVar7 * *(float *)(this + 0x44) + *(float *)(this + 0x60)) -
                    ((float)param_3 * fVar1 + fVar2),
           fVar9 = ((float)(int)uVar5 * *(float *)(this + 0x44) + *(float *)(this + 100)) -
                   (fVar1 * (float)param_4 + fVar3),
           fVar8 = SQRT(fVar8 * fVar8 + 0.0 + fVar9 * fVar9), fVar4 <= fVar8)) {
          uVar5 = uVar5 + 1;
        }
        else {
          *param_5 = uVar7;
          *param_6 = uVar5;
          uVar5 = uVar5 + 1;
          fVar4 = fVar8;
        }
      }
      uVar7 = uVar7 + 1;
      uVar5 = param_4 - 0x10;
    } while ((int)uVar7 <= (int)(param_3 + 0x10));
    if (fVar4 != DAT_00fa8818) {
      return;
    }
    if (NAN(fVar4) || NAN(DAT_00fa8818)) {
      return;
    }
  }
  *param_5 = param_1;
  *param_6 = param_2;
  return;
}



/* address=005932e0
   symbol=CAstarPathfinder::findNearestOpenDirected */

/* CAstarPathfinder::findNearestOpenDirected(unsigned int, unsigned int, unsigned int, unsigned int,
   unsigned int&, unsigned int&) */

void __thiscall
CAstarPathfinder::findNearestOpenDirected
          (CAstarPathfinder *this,uint param_1,uint param_2,uint param_3,uint param_4,uint *param_5,
          uint *param_6)

{
  float fVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_5c;

  fVar5 = *(float *)(this + 0x44);
  local_5c = (float)param_4 * fVar5 + *(float *)(this + 100);
  fVar8 = (float)param_3 * fVar5 + *(float *)(this + 0x60);
  fVar10 = ((float)param_1 * fVar5 + *(float *)(this + 0x60)) - fVar8;
  fVar9 = ((float)param_2 * fVar5 + *(float *)(this + 100)) - local_5c;
  fVar11 = fVar10 * fVar10 + DAT_00fa47f8 + fVar9 * fVar9;
  fVar12 = SQRT(fVar11);
  fVar5 = fVar12;
  if (NAN(fVar12)) {
    fVar5 = sqrtf(fVar11);
  }
  fVar1 = *(float *)(this + 0x44);
  if (NAN(fVar12)) {
    fVar12 = sqrtf(fVar11);
  }
  if (DAT_00fa87a0 < (double)fVar12) {
    fVar10 = fVar10 * (DAT_00fa47fc / fVar12);
    fVar9 = fVar9 * (DAT_00fa47fc / fVar12);
  }
  fVar12 = *(float *)(this + 0x44);
  if ((int)(fVar5 / fVar1) < 1) {
LAB_00593500:
    *param_5 = param_1;
    *param_6 = param_2;
  }
  else {
    fVar11 = *(float *)(this + 0x60);
    iVar4 = 0;
    fVar2 = *(float *)(this + 100);
    while( true ) {
      fVar6 = floorf((fVar8 - fVar11) / fVar12);
      fVar7 = floorf((local_5c - fVar2) / fVar12);
      cVar3 = tileFree(this,(long)fVar6 & 0xffffffff,(long)fVar7 & 0xffffffff,0);
      if (cVar3 != '\0') break;
      iVar4 = iVar4 + 1;
      if ((int)(fVar5 / fVar1) <= iVar4) goto LAB_00593500;
      fVar8 = fVar8 + fVar10 * fVar12;
      local_5c = local_5c + fVar9 * fVar12;
    }
    *param_5 = (uint)(long)fVar6;
    *param_6 = (uint)(long)fVar7;
  }
  return;
}



/* address=00593530
   symbol=CAstarPathfinder::findPath */

/* CAstarPathfinder::findPath(float, float, float, float) */

CAstarPathfinder __thiscall
CAstarPathfinder::findPath
          (CAstarPathfinder *this,float param_1,float param_2,float param_3,float param_4)

{
  char cVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c [3];

  this[0x6a] = (CAstarPathfinder)0x1;
  fVar10 = param_4 - *(float *)(this + 100);
  fVar8 = param_2 - *(float *)(this + 100);
  fVar9 = param_3 - *(float *)(this + 0x60);
  this[0x68] = (CAstarPathfinder)0x0;
  fVar6 = param_1 - *(float *)(this + 0x60);
  fVar7 = 0.0;
  if (0.0 <= fVar6) {
    fVar7 = fVar6;
  }
  fVar7 = floorf(fVar7 / *(float *)(this + 0x44));
  uVar2 = (uint)(long)fVar7;
  uVar5 = (long)fVar7 & 0xffffffff;
  local_3c[0] = uVar2;
  fVar7 = floorf((float)((uint)fVar8 & -(uint)(0.0 <= fVar8)) / *(float *)(this + 0x44));
  uVar4 = (uint)(long)fVar7;
  uVar3 = (long)fVar7 & 0xffffffff;
  local_40 = uVar4;
  fVar7 = floorf((float)((uint)fVar9 & -(uint)(0.0 <= fVar9)) / *(float *)(this + 0x44));
  local_4c = (uint)(long)fVar7;
  fVar6 = floorf((float)((uint)fVar10 & -(uint)(0.0 <= fVar10)) / *(float *)(this + 0x44));
  local_50 = (uint)(long)fVar6;
  local_48 = local_50;
  local_44 = local_4c;
  cVar1 = tileFree(this,(long)fVar7 & 0xffffffff,(long)fVar6 & 0xffffffff,0);
  if (cVar1 == '\0') {
    this[0x68] = (CAstarPathfinder)0x1;
    findNearestOpen(this,uVar2,uVar4,local_4c,local_50,&local_44,&local_48);
    uVar3 = (ulong)local_40;
    uVar5 = (ulong)local_3c[0];
    local_4c = local_44;
    local_50 = local_48;
  }
  uVar2 = (uint)uVar3;
  uVar4 = (uint)uVar5;
  cVar1 = tileFree(this,uVar5,uVar3,0);
  if ((((cVar1 == '\0') || (cVar1 = tileFree(this,uVar5,uVar2 - 1,0), cVar1 == '\0')) ||
      (cVar1 = tileFree(this,uVar5,uVar2 + 1,0), cVar1 == '\0')) ||
     ((cVar1 = tileFree(this,uVar4 + 1,uVar3,0), cVar1 == '\0' ||
      (cVar1 = tileFree(this,uVar4 - 1,uVar3,0), cVar1 == '\0')))) {
    findNearestWideOpen(this,local_4c,local_50,uVar4,uVar2,local_3c,&local_40);
    uVar4 = local_3c[0];
    uVar2 = local_40;
    cVar1 = tileFree(this,local_3c[0],local_40,0);
    if (cVar1 == '\0') goto LAB_005936c7;
  }
  if (uVar2 * *(int *)(this + 0x40) + uVar4 != *(int *)(this + 0x40) * local_50 + local_4c) {
    this[0x38] = (CAstarPathfinder)0x1;
    freeNodes(this);
    createPath(this,local_4c,local_50,local_3c[0],local_40,true);
    return this[0x38];
  }
LAB_005936c7:
  this[0x38] = (CAstarPathfinder)0x0;
  return (CAstarPathfinder)0x0;
}



/* address=00593810
   symbol=CAstarPathfinder::~CAstarPathfinder */

/* CAstarPathfinder::~CAstarPathfinder() */

void __thiscall CAstarPathfinder::~CAstarPathfinder(CAstarPathfinder *this)

{
  *(undefined ***)this = &PTR__CAstarPathfinder_00fa87d0;
  freeNodes(this);
  free(*(void **)(this + 0x30));
  free(*(void **)(this + 0x18));
  free(*(void **)(this + 0x20));
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00593860
   symbol=CAstarPathfinder::~CAstarPathfinder */

/* CAstarPathfinder::~CAstarPathfinder() */

void __thiscall CAstarPathfinder::~CAstarPathfinder(CAstarPathfinder *this)

{
  ~CAstarPathfinder(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00593880
   symbol=CAstarPathfinder::CAstarPathfinder */

/* CAstarPathfinder::CAstarPathfinder(float, float, unsigned int, unsigned int, short**, short**,
   float) */

void __thiscall
CAstarPathfinder::CAstarPathfinder
          (CAstarPathfinder *this,float param_1,float param_2,uint param_3,uint param_4,
          short **param_5,short **param_6,float param_7)

{
  void *pvVar1;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(uint *)(this + 0x40) = param_3;
  *(uint *)(this + 0x3c) = param_4;
  *(float *)(this + 0x44) = param_7;
  *(short ***)(this + 0x50) = param_5;
  *(short ***)(this + 0x58) = param_6;
  *(uint *)(this + 0x48) = param_3 * param_4;
  *(float *)(this + 0x60) = param_1;
  *(undefined ***)this = &PTR__CAstarPathfinder_00fa87d0;
  *(float *)(this + 100) = param_2;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  this[0x38] = (CAstarPathfinder)0x0;
  this[0x68] = (CAstarPathfinder)0x0;
  this[0x69] = (CAstarPathfinder)0x0;
  this[0x6a] = (CAstarPathfinder)0x1;
  *(undefined4 *)(this + 0x6c) = 0x96;
  pvVar1 = calloc(1,0x10);
  *(void **)(this + 0x30) = pvVar1;
  return;
}



/* export-summary functions=28 failures=0 */
