# 11-original-inventory-open-and-anchors

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `research/decompiled-core/inventory_menu.c:2395–2574`

SHA256 полного файла: `a150b1aba4625eea2351e66d7995b715a3610feceeef729e25322719f74811bf`

```text
 2395 | /* address=00b4eb70
 2396 |    symbol=CInventoryMenu::setOpen */
 2397 | 
 2398 | /* WARNING: Removing unreachable block (ram,0x00b4f194) */
 2399 | /* WARNING: Removing unreachable block (ram,0x00b4f162) */
 2400 | /* WARNING: Removing unreachable block (ram,0x00b4f17e) */
 2401 | /* CInventoryMenu::setOpen(bool) */
 2402 | 
 2403 | void __thiscall CInventoryMenu::setOpen(CInventoryMenu *this,bool param_1)
 2404 | 
 2405 | {
 2406 |   int *piVar1;
 2407 |   Window *pWVar2;
 2408 |   code *pcVar3;
 2409 |   char cVar4;
 2410 |   int iVar5;
 2411 |   int iVar6;
 2412 |   Camera *pCVar7;
 2413 |   float fVar8;
 2414 |   float fVar9;
 2415 |   float fVar10;
 2416 |   float fVar11;
 2417 |   float fVar12;
 2418 |   float fVar13;
 2419 |   long local_78 [2];
 2420 |   long local_68 [2];
 2421 |   string local_58 [16];
 2422 |   string local_48 [16];
 2423 |   long local_38;
 2424 |   allocator local_2d;
 2425 |   allocator local_2c;
 2426 |   allocator local_2b;
 2427 |   allocator local_2a;
 2428 |   allocator local_29;
 2429 | 
 2430 |   if (this[0x60] == (CInventoryMenu)0x0) {
 2431 |     if (!param_1) {
 2432 |       this[0x60] = (CInventoryMenu)0x0;
 2433 |       return;
 2434 |     }
 2435 |     CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x16,(SceneNode *)0x0,0.0,0.0,false);
 2436 |     iVar5 = CDynamicPropertyFile::GetInt
 2437 |                       (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
 2438 |     fVar8 = (float)iVar5;
 2439 |     iVar5 = CDynamicPropertyFile::GetInt
 2440 |                       (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
 2441 |     (**(code **)(**(long **)(this + 0x9170) + 0x50))(*(long **)(this + 0x9170),1);
 2442 |                     /* try { // try from 00b4ed07 to 00b4ed0b has its CatchHandler @ 00b4f16d */
 2443 |     std::string::string((string *)&local_38,"CLOSE",&local_29);
 2444 |                     /* try { // try from 00b4ed16 to 00b4ed1a has its CatchHandler @ 00b4f17c */
 2445 |     cVar4 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x9170),(string *)&local_38);
 2446 |     if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 2447 |       LOCK();
 2448 |       piVar1 = (int *)(local_38 + -8);
 2449 |       iVar6 = *piVar1;
 2450 |       *piVar1 = *piVar1 + -1;
 2451 |       UNLOCK();
 2452 |       if (iVar6 < 1) {
 2453 |         std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
 2454 |       }
 2455 |     }
 2456 |     if (cVar4 == '\0') {
 2457 |                     /* try { // try from 00b4ee95 to 00b4ee99 has its CatchHandler @ 00b4f18e */
 2458 |       std::string::string(local_58,"OPEN",&local_2b);
 2459 |                     /* try { // try from 00b4eeb6 to 00b4eeba has its CatchHandler @ 00b4f18c */
 2460 |       CGenericModel::playAnimation
 2461 |                 (*(CGenericModel **)(this + 0x9170),local_58,false,DAT_00fa4824,DAT_00fa8760);
 2462 |                     /* try { // try from 00b4eebe to 00b4eec2 has its CatchHandler @ 00b4f18e */
 2463 |       std::string::~string(local_58);
 2464 |     }
 2465 |     else {
 2466 |                     /* try { // try from 00b4ed54 to 00b4ed58 has its CatchHandler @ 00b4f155 */
 2467 |       std::string::string(local_48,"OPEN",&local_2a);
 2468 |                     /* try { // try from 00b4ed7d to 00b4ed81 has its CatchHandler @ 00b4f153 */
 2469 |       CGenericModel::blendAnimation
 2470 |                 (*(CGenericModel **)(this + 0x9170),local_48,false,DAT_00fa480c,DAT_00fa4824,
 2471 |                  DAT_00fa8760);
 2472 |                     /* try { // try from 00b4ed85 to 00b4ed89 has its CatchHandler @ 00b4f155 */
 2473 |       std::string::~string(local_48);
 2474 |     }
 2475 |                     /* try { // try from 00b4ed9f to 00b4eda3 has its CatchHandler @ 00b4f15a */
 2476 |     std::string::string((string *)local_68,"IDLE",&local_2c);
 2477 |                     /* try { // try from 00b4edc3 to 00b4edc7 has its CatchHandler @ 00b4f140 */
 2478 |     CGenericModel::queueBlendAnimation
 2479 |               (*(CGenericModel **)(this + 0x9170),(string *)local_68,true,DAT_00fa480c,DAT_00fa47fc)
 2480 |     ;
 2481 |     if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2482 |     {
 2483 |       LOCK();
 2484 |       piVar1 = (int *)(local_68[0] + -8);
 2485 |       iVar6 = *piVar1;
 2486 |       *piVar1 = *piVar1 + -1;
 2487 |       UNLOCK();
 2488 |       if (iVar6 < 1) {
 2489 |         std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
 2490 |       }
 2491 |     }
 2492 |     CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
 2493 |     CEGUI::Window::moveToBack();
 2494 |     CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9120),0));
 2495 |     CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9128),0));
 2496 |     CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9130),0));
 2497 |     CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
 2498 |     CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
 2499 |     CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
 2500 |     if (*(long *)(this + 0x9158) == 0) {
 2501 |       pCVar7 = (Camera *)
 2502 |                (**(code **)(**(long **)(this + 0x9150) + 0x48))
 2503 |                          (0,0,DAT_00fa47fc,*(long **)(this + 0x9150),*(undefined8 *)(this + 0x9148),
 2504 |                           3);
 2505 |       *(Camera **)(this + 0x9158) = pCVar7;
 2506 |       fVar10 = *(float *)(this + 0x9184);
 2507 |       fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd50);
 2508 |       fVar13 = (fVar10 + fVar9) / fVar8;
 2509 |       fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd54);
 2510 |       fVar9 = fVar9 / (float)iVar5;
 2511 |       fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd58);
 2512 |       fVar10 = fVar10 / fVar8;
 2513 |       fVar11 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd5c);
 2514 |       fVar11 = fVar11 / (float)iVar5;
 2515 |       if (DAT_00fa47fc < fVar13 + fVar10) {
 2516 |         fVar10 = DAT_00fa47fc - fVar13;
 2517 |       }
 2518 |       if (DAT_00fa47fc < fVar9 + fVar11) {
 2519 |         fVar11 = DAT_00fa47fc - fVar9;
 2520 |       }
 2521 |       fVar13 = (float)((uint)fVar13 & -(uint)(0.0 <= fVar13));
 2522 |       fVar12 = 0.0;
 2523 |       if (0.0 <= fVar9) {
 2524 |         fVar12 = fVar9;
 2525 |       }
 2526 |       fVar8 = DAT_00fa47fc / fVar8;
 2527 |       if (fVar10 < fVar8) {
 2528 |         fVar13 = DAT_00fa47fc - fVar8;
 2529 |         fVar10 = fVar8;
 2530 |       }
 2531 |       Ogre::Viewport::setDimensions(fVar13,fVar12,fVar10,fVar11);
 2532 |       Ogre::Viewport::setBackgroundColour(*(ColourValue **)(this + 0x9158));
 2533 |       Ogre::Viewport::setClearEveryFrame(SUB81(*(undefined8 *)(this + 0x9158),0),1);
 2534 |       pcVar3 = *(code **)(**(long **)(this + 0x9148) + 0x278);
 2535 |       iVar5 = Ogre::Viewport::getActualWidth();
 2536 |       iVar6 = Ogre::Viewport::getActualHeight();
 2537 |       (*pcVar3)((float)iVar5 / (float)iVar6,*(undefined8 *)(this + 0x9148));
 2538 |       Ogre::Viewport::setCamera(pCVar7);
 2539 |     }
 2540 |     CGameUI::queueTip(*(CGameUI **)(this + 0x70),0);
 2541 |   }
 2542 |   else if (!param_1) {
 2543 |     if ((*(long *)(this + 0x91a0) != 0) &&
 2544 |        (pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x91a0) + 0x30) + 0xb0),
 2545 |        pWVar2 != (Window *)0x0)) {
 2546 |       CEGUI::Window::removeChildWindow(pWVar2);
 2547 |     }
 2548 |     CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x42,(SceneNode *)0x0,0.0,0.0,false);
 2549 |                     /* try { // try from 00b4ebf9 to 00b4ebfd has its CatchHandler @ 00b4f192 */
 2550 |     std::string::string((string *)local_78,"CLOSE",&local_2d);
 2551 |                     /* try { // try from 00b4ec22 to 00b4ec26 has its CatchHandler @ 00b4f16f */
 2552 |     CGenericModel::blendAnimation
 2553 |               (*(CGenericModel **)(this + 0x9170),(string *)local_78,false,DAT_00fa480c,DAT_00fa4824
 2554 |                ,DAT_00fa8760);
 2555 |     if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
 2556 |     {
 2557 |       LOCK();
 2558 |       piVar1 = (int *)(local_78[0] + -8);
 2559 |       iVar5 = *piVar1;
 2560 |       *piVar1 = *piVar1 + -1;
 2561 |       UNLOCK();
 2562 |       if (iVar5 < 1) {
 2563 |         std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
 2564 |       }
 2565 |     }
 2566 |     this[0x61] = (CInventoryMenu)0x0;
 2567 |     this[0x60] = (CInventoryMenu)0x0;
 2568 |     return;
 2569 |   }
 2570 |   this[0x60] = (CInventoryMenu)param_1;
 2571 |   (**(code **)(*(long *)this + 0x48))(this);
 2572 |   return;
 2573 | }
 2574 | 
```

## `research/decompiled-core/inventory_menu.c:3504–3684`

SHA256 полного файла: `a150b1aba4625eea2351e66d7995b715a3610feceeef729e25322719f74811bf`

```text
 3504 |     fStack_244 = local_1a4 * (float)local_148 + local_194 * local_148._4_4_ +
 3505 |                  local_184 * (float)local_140 + local_174 * local_140._4_4_;
 3506 |     local_240 = local_1a0 * (float)local_148 + local_190 * local_148._4_4_ +
 3507 |                 local_180 * (float)local_140 + local_170 * local_140._4_4_;
 3508 |     fStack_23c = (float)local_148 * local_19c + local_148._4_4_ * local_18c +
 3509 |                  (float)local_140 * local_17c + local_140._4_4_ * local_16c;
 3510 |     in_XMM1_Da = local_170 * local_130._4_4_;
 3511 |     local_238 = local_1a8 * (float)local_138 + local_198 * local_138._4_4_ +
 3512 |                 local_188 * (float)local_130 + local_178 * local_130._4_4_;
 3513 |     fStack_234 = local_1a4 * (float)local_138 + local_194 * local_138._4_4_ +
 3514 |                  local_184 * (float)local_130 + local_174 * local_130._4_4_;
 3515 |     local_230 = local_1a0 * (float)local_138 + local_190 * local_138._4_4_ +
 3516 |                 local_180 * (float)local_130 + in_XMM1_Da;
 3517 |     fStack_22c = (float)local_138 * local_19c + local_138._4_4_ * local_18c +
 3518 |                  (float)local_130 * local_17c + local_130._4_4_ * local_16c;
 3519 |     local_150 = CONCAT44(fStack_24c,local_250);
 3520 |     local_148 = CONCAT44(fStack_244,local_248);
 3521 |     local_140 = CONCAT44(fStack_23c,local_240);
 3522 |     local_138 = CONCAT44(fStack_234,local_238);
 3523 |     local_130 = CONCAT44(fStack_22c,local_230);
 3524 |     (**(code **)(**(long **)(in_RDI[10] + 0x208) + 0x118))
 3525 |               (*(long **)(in_RDI[10] + 0x208),&local_168,0);
 3526 |   }
 3527 |   if ((char)in_RDI[0xc] == '\0') {
 3528 |     in_RDI[0x204] = 0;
 3529 |     CEGUI::Window::setVisible(SUB81(in_RDI[6],0));
 3530 |     CEGUI::Window::setVisible(SUB81(in_RDI[7],0));
 3531 |     if (((char)in_RDI[0xc] == '\0') && (*(char *)((long)in_RDI + 0x61) != '\0')) {
 3532 |       if (in_RDI[0x1234] == 0) {
 3533 |         return;
 3534 |       }
 3535 |       pWVar6 = *(Window **)(*(long *)(in_RDI[0x1234] + 0x30) + 0xb0);
 3536 |       goto joined_r0x00b5051b;
 3537 |     }
 3538 |   }
 3539 |   CGenericModel::updateAnimation((CGenericModel *)in_RDI[0x122e],param_1,false);
 3540 |   Ogre::Entity::_updateAnimation();
 3541 |   plVar16 = *(long **)(in_RDI[0x122e] + 0x130);
 3542 |   pcVar5 = *(code **)(*plVar16 + 0x1b0);
 3543 |                     /* try { // try from 00b4fdf3 to 00b4fdf7 has its CatchHandler @ 00b519fc */
 3544 |   std::string::string((string *)local_b8,"tag_topinventory",&local_3a);
 3545 |                     /* try { // try from 00b4fdfe to 00b4fe00 has its CatchHandler @ 00b518a6 */
 3546 |   plVar16 = (long *)(*pcVar5)(plVar16);
 3547 |   if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 3548 |     LOCK();
 3549 |     piVar1 = (int *)(local_b8[0] + -8);
 3550 |     iVar10 = *piVar1;
 3551 |     *piVar1 = *piVar1 + -1;
 3552 |     UNLOCK();
 3553 |     if (iVar10 < 1) {
 3554 |       std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
 3555 |     }
 3556 |   }
 3557 |   fVar19 = (float)iVar8;
 3558 |   fVar21 = (float)iVar9;
 3559 |   local_f8 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x122e],false);
 3560 |   local_f0 = in_XMM1_Da;
 3561 |   pfVar11 = (float *)(**(code **)(*plVar16 + 0x200))(plVar16);
 3562 |   fVar22 = pfVar11[1] + local_f8._4_4_;
 3563 |   fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],*pfVar11 + (float)local_f8);
 3564 |   fVar24 = fVar19 * DAT_00fa4810;
 3565 |   fVar20 = fVar20 + fVar24;
 3566 |   fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],fVar22);
 3567 |   uVar17 = (uint)(fVar21 * DAT_00fa86f4 + fVar22) ^ DAT_00fa8780;
 3568 |   *(float *)((long)in_RDI + 0x9184) = fVar20;
 3569 |   local_118 = 0;
 3570 |   local_110 = 0;
 3571 |   local_114 = fVar20;
 3572 |   local_10c = uVar17;
 3573 |                     /* try { // try from 00b4ff5c to 00b4ff60 has its CatchHandler @ 00b51878 */
 3574 |   CEGUI::Window::setPosition((UVector2 *)in_RDI[5]);
 3575 |   plVar16 = *(long **)(in_RDI[0x122e] + 0x130);
 3576 |   pcVar5 = *(code **)(*plVar16 + 0x1b0);
 3577 |                     /* try { // try from 00b4ff92 to 00b4ff96 has its CatchHandler @ 00b51873 */
 3578 |   std::string::string((string *)local_c8,"tag_bottominventory",&local_3b);
 3579 |                     /* try { // try from 00b4ff9d to 00b4ff9f has its CatchHandler @ 00b517ee */
 3580 |   plVar16 = (long *)(*pcVar5)(plVar16);
 3581 |   if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
 3582 |     LOCK();
 3583 |     piVar1 = (int *)(local_c8[0] + -8);
 3584 |     iVar8 = *piVar1;
 3585 |     *piVar1 = *piVar1 + -1;
 3586 |     UNLOCK();
 3587 |     if (iVar8 < 1) {
 3588 |       std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
 3589 |     }
 3590 |   }
 3591 |   local_108 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x122e],false);
 3592 |   local_100 = fVar20;
 3593 |   pfVar11 = (float *)(**(code **)(*plVar16 + 0x200))(plVar16);
 3594 |   fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],*pfVar11 + (float)local_108);
 3595 |   local_128 = 0;
 3596 |   fVar24 = fVar24 + fVar20;
 3597 |   local_120 = 0;
 3598 |   local_124 = fVar24;
 3599 |   local_11c = uVar17;
 3600 |                     /* try { // try from 00b5006a to 00b5006e has its CatchHandler @ 00b518b6 */
 3601 |   CEGUI::Window::setPosition((UVector2 *)in_RDI[9]);
 3602 |   fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fa8738);
 3603 |   fVar20 = fVar20 + fVar24;
 3604 |   if (fVar19 <= fVar20) {
 3605 |     fVar20 = fVar19;
 3606 |   }
 3607 |   *(float *)(in_RDI + 0x1230) = fVar20;
 3608 |   if (in_RDI[0x122b] != 0) {
 3609 |     fVar20 = *(float *)((long)in_RDI + 0x9184);
 3610 |     fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd50);
 3611 |     fVar23 = (fVar20 + fVar22) / fVar19;
 3612 |     fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd54);
 3613 |     fVar22 = fVar22 / fVar21;
 3614 |     fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd58);
 3615 |     fVar20 = fVar20 / fVar19;
 3616 |     fVar24 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd5c);
 3617 |     fVar24 = fVar24 / fVar21;
 3618 |     if (DAT_00fa47fc < fVar23 + fVar20) {
 3619 |       fVar20 = DAT_00fa47fc - fVar23;
 3620 |     }
 3621 |     if (DAT_00fa47fc < fVar22 + fVar24) {
 3622 |       fVar24 = DAT_00fa47fc - fVar22;
 3623 |     }
 3624 |     fVar23 = (float)((uint)fVar23 & -(uint)(0.0 <= fVar23));
 3625 |     fVar21 = 0.0;
 3626 |     if (0.0 <= fVar22) {
 3627 |       fVar21 = fVar22;
 3628 |     }
 3629 |     fVar19 = DAT_00fa47fc / fVar19;
 3630 |     if (fVar20 < fVar19) {
 3631 |       fVar23 = DAT_00fa47fc - fVar19;
 3632 |       fVar20 = fVar19;
 3633 |     }
 3634 |     Ogre::Viewport::setDimensions(fVar23,fVar21,fVar20,fVar24);
 3635 |     pcVar5 = *(code **)(*(long *)in_RDI[0x1229] + 0x278);
 3636 |     iVar8 = Ogre::Viewport::getActualWidth();
 3637 |     iVar9 = Ogre::Viewport::getActualHeight();
 3638 |     (*pcVar5)((float)iVar8 / (float)iVar9,in_RDI[0x1229]);
 3639 |   }
 3640 |   if (((char)in_RDI[0xc] == '\0') && (*(char *)((long)in_RDI + 0x61) == '\0')) {
 3641 |                     /* try { // try from 00b5134a to 00b51363 has its CatchHandler @ 00b51b93 */
 3642 |     std::string::string(local_d8,"CLOSE",&local_3c);
 3643 |     cVar7 = CGenericModel::animationPlaying((CGenericModel *)in_RDI[0x122e],local_d8);
 3644 |     bVar18 = false;
 3645 |     if (cVar7 == '\0') {
 3646 |                     /* try { // try from 00b51795 to 00b517ae has its CatchHandler @ 00b51b93 */
 3647 |       std::string::string(local_e8,"CLOSE",&local_3d);
 3648 |       cVar7 = CGenericModel::animationQueued((CGenericModel *)in_RDI[0x122e],local_e8);
 3649 |       bVar18 = cVar7 == '\0';
 3650 |                     /* try { // try from 00b517b8 to 00b517bc has its CatchHandler @ 00b51801 */
 3651 |       std::string::~string(local_e8);
 3652 |     }
 3653 |                     /* try { // try from 00b51372 to 00b51376 has its CatchHandler @ 00b51bce */
 3654 |     std::string::~string(local_d8);
 3655 |     if (bVar18) {
 3656 |       (**(code **)(*(long *)in_RDI[0x122e] + 0x50))((long *)in_RDI[0x122e],0);
 3657 |       *(undefined1 *)((long)in_RDI + 0x61) = 1;
 3658 |       (**(code **)(*(long *)in_RDI[0x122a] + 0x60))((long *)in_RDI[0x122a],3);
 3659 |       CEGUI::Window::removeChildWindow((Window *)in_RDI[3]);
 3660 |       in_RDI[0x122b] = 0;
 3661 |     }
 3662 |   }
 3663 |   if ((*(char *)((long)in_RDI + 0x9161) != '\0') && (in_RDI[10] != 0)) {
 3664 |     this = *(CSkillManager **)(in_RDI[10] + 0x1c8);
 3665 |     if (this == (CSkillManager *)0x0) {
 3666 |       return;
 3667 |     }
 3668 |     pCVar12 = (CSkill *)CSkillManager::getSkillByGuid(this,in_RDI[0x122d]);
 3669 |     if (pCVar12 == (CSkill *)0x0) {
 3670 |       return;
 3671 |     }
 3672 |     CSkillTooltip::showTooltip
 3673 |               ((CSkillTooltip *)in_RDI[0x1234],(CBaseUnit *)in_RDI[10],pCVar12,
 3674 |                (float)*(long *)(in_RDI[0xe] + 0x12d0),(float)*(long *)(in_RDI[0xe] + 0x12d8));
 3675 |     return;
 3676 |   }
 3677 |   pWVar6 = *(Window **)(*(long *)(in_RDI[0x1234] + 0x30) + 0xb0);
 3678 | joined_r0x00b5051b:
 3679 |   if (pWVar6 != (Window *)0x0) {
 3680 |     CEGUI::Window::removeChildWindow(pWVar6);
 3681 |   }
 3682 |   return;
 3683 | }
 3684 | 
```

