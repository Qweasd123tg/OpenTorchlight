# 12-original-inventory-events

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `research/decompiled-core/inventory_menu.c:107–255`

SHA256 полного файла: `a150b1aba4625eea2351e66d7995b715a3610feceeef729e25322719f74811bf`

```text
  107 | /* address=00b45810
  108 |    symbol=CInventoryMenu::handle_ItemClick */
  109 | 
  110 | /* CInventoryMenu::handle_ItemClick(CEGUI::EventArgs const&) */
  111 | 
  112 | undefined8 __thiscall CInventoryMenu::handle_ItemClick(CInventoryMenu *this,EventArgs *param_1)
  113 | 
  114 | {
  115 |   undefined4 uVar1;
  116 | 
  117 |   if (*(long *)(param_1 + 0x10) != 0) {
  118 |     uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
  119 |     if (*(int *)(param_1 + 0x28) == 0) {
  120 |       *(undefined4 *)(this + 0x78) = uVar1;
  121 |       return 1;
  122 |     }
  123 |     if (*(int *)(param_1 + 0x28) == 1) {
  124 |       *(undefined4 *)(this + 0x7c) = uVar1;
  125 |       return 1;
  126 |     }
  127 |   }
  128 |   return 1;
  129 | }
  130 | 
  131 | /* address=00b45860
  132 |    symbol=CInventoryMenu::handle_RotateLeft */
  133 | 
  134 | /* CInventoryMenu::handle_RotateLeft(CEGUI::EventArgs const&) */
  135 | 
  136 | undefined8 CInventoryMenu::handle_RotateLeft(EventArgs *param_1)
  137 | 
  138 | {
  139 |   param_1[0x9162] = (EventArgs)0x1;
  140 |   return 1;
  141 | }
  142 | 
  143 | /* address=00b45870
  144 |    symbol=CInventoryMenu::handle_EndRotateLeft */
  145 | 
  146 | /* CInventoryMenu::handle_EndRotateLeft(CEGUI::EventArgs const&) */
  147 | 
  148 | undefined8 CInventoryMenu::handle_EndRotateLeft(EventArgs *param_1)
  149 | 
  150 | {
  151 |   param_1[0x9162] = (EventArgs)0x0;
  152 |   return 1;
  153 | }
  154 | 
  155 | /* address=00b45880
  156 |    symbol=CInventoryMenu::handle_RotateRight */
  157 | 
  158 | /* CInventoryMenu::handle_RotateRight(CEGUI::EventArgs const&) */
  159 | 
  160 | undefined8 CInventoryMenu::handle_RotateRight(EventArgs *param_1)
  161 | 
  162 | {
  163 |   param_1[0x9163] = (EventArgs)0x1;
  164 |   return 1;
  165 | }
  166 | 
  167 | /* address=00b45890
  168 |    symbol=CInventoryMenu::handle_EndRotateRight */
  169 | 
  170 | /* CInventoryMenu::handle_EndRotateRight(CEGUI::EventArgs const&) */
  171 | 
  172 | undefined8 CInventoryMenu::handle_EndRotateRight(EventArgs *param_1)
  173 | 
  174 | {
  175 |   param_1[0x9163] = (EventArgs)0x0;
  176 |   return 1;
  177 | }
  178 | 
  179 | /* address=00b458a0
  180 |    symbol=CInventoryMenu::handle_MouseThrough */
  181 | 
  182 | /* CInventoryMenu::handle_MouseThrough(CEGUI::EventArgs const&) */
  183 | 
  184 | undefined8 CInventoryMenu::handle_MouseThrough(EventArgs *param_1)
  185 | 
  186 | {
  187 |   param_1[0x9160] = (EventArgs)0x0;
  188 |   param_1[0x9161] = (EventArgs)0x0;
  189 |   return 1;
  190 | }
  191 | 
  192 | /* address=00b458c0
  193 |    symbol=CInventoryMenu::setTab */
  194 | 
  195 | /* CInventoryMenu::setTab(int) */
  196 | 
  197 | void __thiscall CInventoryMenu::setTab(CInventoryMenu *this,int param_1)
  198 | 
  199 | {
  200 |                     /* WARNING: Could not recover jumptable at 0x00b458cd. Too many branches */
  201 |                     /* WARNING: Treating indirect jump as call */
  202 |   (**(code **)(*(long *)this + 0x98))(this,param_1 + 0xe);
  203 |   return;
  204 | }
  205 | 
  206 | /* address=00b458d0
  207 |    symbol=CInventoryMenu::handle_onClick */
  208 | 
  209 | /* CInventoryMenu::handle_onClick(CEGUI::EventArgs const&) */
  210 | 
  211 | undefined8 __thiscall CInventoryMenu::handle_onClick(CInventoryMenu *this,EventArgs *param_1)
  212 | 
  213 | {
  214 |   undefined8 uVar1;
  215 | 
  216 |   if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
  217 |                     /* WARNING: Could not recover jumptable at 0x00b458f3. Too many branches */
  218 |                     /* WARNING: Treating indirect jump as call */
  219 |     uVar1 = (**(code **)(*(long *)this + 0x98))
  220 |                       (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
  221 |     return uVar1;
  222 |   }
  223 |   return 1;
  224 | }
  225 | 
  226 | /* address=00b45900
  227 |    symbol=CInventoryMenu::handle_SpellMouseOver */
  228 | 
  229 | /* CInventoryMenu::handle_SpellMouseOver(CEGUI::EventArgs const&) */
  230 | 
  231 | undefined8 __thiscall CInventoryMenu::handle_SpellMouseOver(CInventoryMenu *this,EventArgs *param_1)
  232 | 
  233 | {
  234 |   undefined8 uVar1;
  235 | 
  236 |   if (*(long *)(param_1 + 0x10) != 0) {
  237 |     uVar1 = **(undefined8 **)(*(long *)(param_1 + 0x10) + 0x1d8);
  238 |     this[0x9161] = (CInventoryMenu)0x1;
  239 |     *(undefined8 *)(this + 0x9168) = uVar1;
  240 |   }
  241 |   return 1;
  242 | }
  243 | 
  244 | /* address=00b45930
  245 |    symbol=CInventoryMenu::handle_SpellMouseOut */
  246 | 
  247 | /* CInventoryMenu::handle_SpellMouseOut(CEGUI::EventArgs const&) */
  248 | 
  249 | undefined8 CInventoryMenu::handle_SpellMouseOut(EventArgs *param_1)
  250 | 
  251 | {
  252 |   return 1;
  253 | }
  254 | 
  255 | /* address=00b45940
```

## `research/decompiled-core/inventory_menu.c:2575–2720`

SHA256 полного файла: `a150b1aba4625eea2351e66d7995b715a3610feceeef729e25322719f74811bf`

```text
 2575 | /* address=00b4f1b0
 2576 |    symbol=CInventoryMenu::mapEventHandlers */
 2577 | 
 2578 | /* CInventoryMenu::mapEventHandlers(CEGUI::Window*) */
 2579 | 
 2580 | void __thiscall CInventoryMenu::mapEventHandlers(CInventoryMenu *this,Window *param_1)
 2581 | 
 2582 | {
 2583 |   undefined8 *puVar1;
 2584 |   byte bVar2;
 2585 |   code *pcVar3;
 2586 |   char cVar4;
 2587 |   long lVar5;
 2588 |   char *pcVar6;
 2589 |   uint *puVar7;
 2590 |   int iVar8;
 2591 |   long lVar9;
 2592 |   int iVar10;
 2593 |   bool bVar11;
 2594 |   long local_268 [22];
 2595 |   undefined8 local_1b8;
 2596 |   ulong local_1b0;
 2597 |   undefined8 local_1a8;
 2598 |   undefined8 local_1a0;
 2599 |   undefined8 local_198;
 2600 |   uint local_190 [7];
 2601 |   uint local_174 [25];
 2602 |   uint *local_110;
 2603 |   undefined8 local_108;
 2604 |   ulong local_100;
 2605 |   undefined8 local_f8;
 2606 |   undefined8 local_f0;
 2607 |   undefined8 local_e8;
 2608 |   uint local_e0 [7];
 2609 |   uint local_c4 [25];
 2610 |   uint *local_60;
 2611 |   BoundSlot *local_58;
 2612 |   int *local_50;
 2613 |   undefined8 *local_48 [3];
 2614 | 
 2615 |   lVar5 = *(long *)(param_1 + 0x78);
 2616 |   iVar10 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar5) >> 3);
 2617 |   if (0 < iVar10) {
 2618 |     lVar9 = 0;
 2619 |     iVar8 = 0;
 2620 |     while( true ) {
 2621 |       puVar1 = (undefined8 *)(lVar5 + lVar9);
 2622 |       iVar8 = iVar8 + 1;
 2623 |       lVar9 = lVar9 + 8;
 2624 |       mapEventHandlers(this,(Window *)*puVar1);
 2625 |       if (iVar10 <= iVar8) break;
 2626 |       lVar5 = *(long *)(param_1 + 0x78);
 2627 |     }
 2628 |   }
 2629 |   local_100 = 0x20;
 2630 |   local_f8 = 0;
 2631 |   local_e8 = 0;
 2632 |   local_f0 = 0;
 2633 |   local_60 = (uint *)0x0;
 2634 |   local_108 = 0;
 2635 |   local_e0[0] = 0;
 2636 |                     /* try { // try from 00b4f276 to 00b4f2f3 has its CatchHandler @ 00b4f554 */
 2637 |   CEGUI::String::grow((ulong)&local_108);
 2638 |   puVar7 = local_e0;
 2639 |   if (0x20 < local_100) {
 2640 |     puVar7 = local_60;
 2641 |   }
 2642 |   pcVar6 = "onClick";
 2643 |   do {
 2644 |     bVar2 = *pcVar6;
 2645 |     pcVar6 = pcVar6 + 1;
 2646 |     *puVar7 = (uint)bVar2;
 2647 |     puVar7 = puVar7 + 1;
 2648 |   } while ((byte *)pcVar6 != (byte *)0xfe4847);
 2649 |   local_108 = 7;
 2650 |   puVar7 = local_c4;
 2651 |   if (0x20 < local_100) {
 2652 |     puVar7 = local_60 + 7;
 2653 |   }
 2654 |   *puVar7 = 0;
 2655 |   cVar4 = CEGUI::PropertySet::isPropertyPresent((String *)param_1);
 2656 |   bVar11 = false;
 2657 |   if (cVar4 != '\0') {
 2658 |     local_1b0 = 0x20;
 2659 |     local_1a8 = 0;
 2660 |     local_198 = 0;
 2661 |     local_1a0 = 0;
 2662 |     local_110 = (uint *)0x0;
 2663 |     local_1b8 = 0;
 2664 |     local_190[0] = 0;
 2665 |                     /* try { // try from 00b4f448 to 00b4f4c6 has its CatchHandler @ 00b4f554 */
 2666 |     CEGUI::String::grow((ulong)&local_1b8);
 2667 |     puVar7 = local_110;
 2668 |     if (local_1b0 < 0x21) {
 2669 |       puVar7 = local_190;
 2670 |     }
 2671 |     pcVar6 = "onClick";
 2672 |     do {
 2673 |       bVar2 = *pcVar6;
 2674 |       pcVar6 = pcVar6 + 1;
 2675 |       *puVar7 = (uint)bVar2;
 2676 |       puVar7 = puVar7 + 1;
 2677 |     } while ((byte *)pcVar6 != (byte *)0xfe4847);
 2678 |     local_1b8 = 7;
 2679 |     if (local_1b0 < 0x21) {
 2680 |       puVar7 = local_174;
 2681 |     }
 2682 |     else {
 2683 |       puVar7 = local_110 + 7;
 2684 |     }
 2685 |     *puVar7 = 0;
 2686 |     CEGUI::PropertySet::getProperty((String *)local_268);
 2687 |     bVar11 = local_268[0] != 0;
 2688 |                     /* try { // try from 00b4f4d3 to 00b4f4d7 has its CatchHandler @ 00b4f50e */
 2689 |     CEGUI::String::~String((String *)local_268);
 2690 |                     /* try { // try from 00b4f4e0 to 00b4f4e4 has its CatchHandler @ 00b4f547 */
 2691 |     CEGUI::String::~String((String *)&local_1b8);
 2692 |   }
 2693 |                     /* try { // try from 00b4f302 to 00b4f331 has its CatchHandler @ 00b4f535 */
 2694 |   CEGUI::String::~String((String *)&local_108);
 2695 |   if (bVar11) {
 2696 |     pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
 2697 |     local_48[0] = operator_new(0x20);
 2698 |     local_48[0][3] = this;
 2699 |     *local_48[0] = &PTR__MemberFunctionSlot_00fefcd0;
 2700 |     local_48[0][2] = 0;
 2701 |     local_48[0][1] = 0x59;
 2702 |                     /* try { // try from 00b4f371 to 00b4f3a6 has its CatchHandler @ 00b4f53a */
 2703 |     (*pcVar3)(&local_58,param_1 + 0x38,CEGUI::Window::EventMouseButtonDown,
 2704 |               (SubscriberSlot *)local_48);
 2705 |     if ((local_58 != (BoundSlot *)0x0) &&
 2706 |        (iVar10 = *local_50, *local_50 = iVar10 + -1, iVar10 + -1 == 0)) {
 2707 |       if (local_58 != (BoundSlot *)0x0) {
 2708 |         CEGUI::BoundSlot::~BoundSlot(local_58);
 2709 |         operator_delete(local_58);
 2710 |       }
 2711 |       operator_delete(local_50);
 2712 |       local_58 = (BoundSlot *)0x0;
 2713 |       local_50 = (int *)0x0;
 2714 |     }
 2715 |                     /* try { // try from 00b4f3d7 to 00b4f3db has its CatchHandler @ 00b4f535 */
 2716 |     CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
 2717 |   }
 2718 |   return;
 2719 | }
 2720 | 
```

