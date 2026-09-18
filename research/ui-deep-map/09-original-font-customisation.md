# 09-original-font-customisation

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `research/decompiled-core/game_ui.c:8662–8878`

SHA256 полного файла: `f415f44a95978d36423f19824326b89f99d9870acd982f4bad5153364068c05f`

```text
 8662 |     }
 8663 |   }
 8664 |                     /* try { // try from 00a9eef5 to 00a9eef9 has its CatchHandler @ 00aa4e09 */
 8665 |   CEGUI::String::String(local_db8,"");
 8666 |   local_d00 = 0x20;
 8667 |   local_cf8 = 0;
 8668 |   local_ce8 = 0;
 8669 |   local_cf0 = 0;
 8670 |   local_c60 = (undefined4 *)0x0;
 8671 |   local_d08 = 0;
 8672 |   local_ce0[0] = 0;
 8673 |   lVar16 = *(long *)(local_8e0 + -0x18);
 8674 |                     /* try { // try from 00a9ef67 to 00a9ef6b has its CatchHandler @ 00aa5e79 */
 8675 |   CEGUI::String::grow((ulong)&local_d08);
 8676 |   puVar23 = local_ce0;
 8677 |   if (0x20 < local_d00) {
 8678 |     puVar23 = local_c60;
 8679 |   }
 8680 |   puVar23[lVar16] = 0;
 8681 |   if (lVar16 != 0) {
 8682 |     lVar28 = lVar16;
 8683 |     do {
 8684 |       lVar28 = lVar28 + -1;
 8685 |       puVar23 = local_ce0;
 8686 |       if (0x20 < local_d00) {
 8687 |         puVar23 = local_c60;
 8688 |       }
 8689 |       puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
 8690 |     } while (lVar28 != 0);
 8691 |   }
 8692 |   local_d08 = lVar16;
 8693 |                     /* try { // try from 00a9efe2 to 00a9efe6 has its CatchHandler @ 00aa5e5f */
 8694 |   CEGUI::SchemeManager::loadScheme
 8695 |             (CEGUI::Singleton<CEGUI::SchemeManager>::ms_Singleton,(String *)&local_d08);
 8696 |                     /* try { // try from 00a9efea to 00a9efee has its CatchHandler @ 00aa5e79 */
 8697 |   CEGUI::String::~String((String *)&local_d08);
 8698 |                     /* try { // try from 00a9eff2 to 00a9f00b has its CatchHandler @ 00aa4e09 */
 8699 |   CEGUI::String::~String(local_db8);
 8700 |   CEGUI::String::String(local_e68,(uchar *)"Serif");
 8701 |                     /* try { // try from 00a9f016 to 00a9f01a has its CatchHandler @ 00aa5e4d */
 8702 |   CEGUI::System::setDefaultFont(*(String **)(this + 0x430));
 8703 |                     /* try { // try from 00a9f01e to 00a9f037 has its CatchHandler @ 00aa4e09 */
 8704 |   CEGUI::String::~String(local_e68);
 8705 |   CEGUI::String::String(local_f18,(uchar *)"Serif");
 8706 |                     /* try { // try from 00a9f042 to 00a9f046 has its CatchHandler @ 00aa5e3b */
 8707 |   lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
 8708 |                     /* try { // try from 00a9f04d to 00a9f066 has its CatchHandler @ 00aa4e09 */
 8709 |   CEGUI::String::~String(local_f18);
 8710 |   CEGUI::String::String((String *)&local_fc8,"|c");
 8711 |                     /* try { // try from 00a9f079 to 00a9f07d has its CatchHandler @ 00aa620a */
 8712 |   CEGUI::String::grow(lVar28 + 0x368);
 8713 |   *(long *)(lVar28 + 0x368) = local_fc8;
 8714 |   lVar16 = lVar28 + 0x390;
 8715 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8716 |     lVar16 = *(long *)(lVar28 + 0x410);
 8717 |   }
 8718 |   *(undefined4 *)(lVar16 + local_fc8 * 4) = 0;
 8719 |   puVar30 = local_fa0;
 8720 |   if (0x20 < local_fc0) {
 8721 |     puVar30 = local_f20;
 8722 |   }
 8723 |   pvVar20 = (void *)(lVar28 + 0x390);
 8724 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8725 |     pvVar20 = *(void **)(lVar28 + 0x410);
 8726 |   }
 8727 |   memcpy(pvVar20,puVar30,local_fc8 * 4);
 8728 |                     /* try { // try from 00a9f0e4 to 00a9f0fd has its CatchHandler @ 00aa4e09 */
 8729 |   CEGUI::String::~String((String *)&local_fc8);
 8730 |   CEGUI::String::String((String *)&local_1078,"|u");
 8731 |                     /* try { // try from 00a9f110 to 00a9f114 has its CatchHandler @ 00aa61f8 */
 8732 |   CEGUI::String::grow(lVar28 + 0x418);
 8733 |   *(long *)(lVar28 + 0x418) = local_1078;
 8734 |   lVar16 = lVar28 + 0x440;
 8735 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8736 |     lVar16 = *(long *)(lVar28 + 0x4c0);
 8737 |   }
 8738 |   *(undefined4 *)(lVar16 + local_1078 * 4) = 0;
 8739 |   puVar30 = local_1050;
 8740 |   if (0x20 < local_1070) {
 8741 |     puVar30 = local_fd0;
 8742 |   }
 8743 |   pvVar20 = (void *)(lVar28 + 0x440);
 8744 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8745 |     pvVar20 = *(void **)(lVar28 + 0x4c0);
 8746 |   }
 8747 |   memcpy(pvVar20,puVar30,local_1078 * 4);
 8748 |                     /* try { // try from 00a9f17b to 00a9f19b has its CatchHandler @ 00aa4e09 */
 8749 |   CEGUI::String::~String((String *)&local_1078);
 8750 |   *(undefined1 *)(lVar28 + 0x4c8) = 1;
 8751 |   CEGUI::String::String(local_1128,(uchar *)"SerifBig");
 8752 |                     /* try { // try from 00a9f1a6 to 00a9f1aa has its CatchHandler @ 00aa61e6 */
 8753 |   lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
 8754 |                     /* try { // try from 00a9f1b1 to 00a9f1ca has its CatchHandler @ 00aa4e09 */
 8755 |   CEGUI::String::~String(local_1128);
 8756 |   CEGUI::String::String((String *)&local_11d8,"|c");
 8757 |                     /* try { // try from 00a9f1dd to 00a9f1e1 has its CatchHandler @ 00aa61d4 */
 8758 |   CEGUI::String::grow(lVar28 + 0x368);
 8759 |   *(long *)(lVar28 + 0x368) = local_11d8;
 8760 |   lVar16 = lVar28 + 0x390;
 8761 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8762 |     lVar16 = *(long *)(lVar28 + 0x410);
 8763 |   }
 8764 |   *(undefined4 *)(lVar16 + local_11d8 * 4) = 0;
 8765 |   puVar30 = local_11b0;
 8766 |   if (0x20 < local_11d0) {
 8767 |     puVar30 = local_1130;
 8768 |   }
 8769 |   pvVar20 = (void *)(lVar28 + 0x390);
 8770 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8771 |     pvVar20 = *(void **)(lVar28 + 0x410);
 8772 |   }
 8773 |   memcpy(pvVar20,puVar30,local_11d8 * 4);
 8774 |                     /* try { // try from 00a9f248 to 00a9f261 has its CatchHandler @ 00aa4e09 */
 8775 |   CEGUI::String::~String((String *)&local_11d8);
 8776 |   CEGUI::String::String((String *)&local_1288,"|u");
 8777 |                     /* try { // try from 00a9f274 to 00a9f278 has its CatchHandler @ 00aa61c2 */
 8778 |   CEGUI::String::grow(lVar28 + 0x418);
 8779 |   *(long *)(lVar28 + 0x418) = local_1288;
 8780 |   lVar16 = lVar28 + 0x440;
 8781 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8782 |     lVar16 = *(long *)(lVar28 + 0x4c0);
 8783 |   }
 8784 |   *(undefined4 *)(lVar16 + local_1288 * 4) = 0;
 8785 |   puVar30 = local_1260;
 8786 |   if (0x20 < local_1280) {
 8787 |     puVar30 = local_11e0;
 8788 |   }
 8789 |   pvVar20 = (void *)(lVar28 + 0x440);
 8790 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8791 |     pvVar20 = *(void **)(lVar28 + 0x4c0);
 8792 |   }
 8793 |   memcpy(pvVar20,puVar30,local_1288 * 4);
 8794 |                     /* try { // try from 00a9f2df to 00a9f2ff has its CatchHandler @ 00aa4e09 */
 8795 |   CEGUI::String::~String((String *)&local_1288);
 8796 |   *(undefined1 *)(lVar28 + 0x4c8) = 1;
 8797 |   CEGUI::String::String(local_1338,(uchar *)"SerifHuge");
 8798 |                     /* try { // try from 00a9f30a to 00a9f30e has its CatchHandler @ 00aa61b0 */
 8799 |   lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
 8800 |                     /* try { // try from 00a9f315 to 00a9f32e has its CatchHandler @ 00aa4e09 */
 8801 |   CEGUI::String::~String(local_1338);
 8802 |   CEGUI::String::String((String *)&local_13e8,"|c");
 8803 |                     /* try { // try from 00a9f341 to 00a9f345 has its CatchHandler @ 00aa619e */
 8804 |   CEGUI::String::grow(lVar28 + 0x368);
 8805 |   *(long *)(lVar28 + 0x368) = local_13e8;
 8806 |   lVar16 = lVar28 + 0x390;
 8807 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8808 |     lVar16 = *(long *)(lVar28 + 0x410);
 8809 |   }
 8810 |   *(undefined4 *)(lVar16 + local_13e8 * 4) = 0;
 8811 |   puVar30 = local_13c0;
 8812 |   if (0x20 < local_13e0) {
 8813 |     puVar30 = local_1340;
 8814 |   }
 8815 |   pvVar20 = (void *)(lVar28 + 0x390);
 8816 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8817 |     pvVar20 = *(void **)(lVar28 + 0x410);
 8818 |   }
 8819 |   memcpy(pvVar20,puVar30,local_13e8 * 4);
 8820 |                     /* try { // try from 00a9f3ac to 00a9f3c5 has its CatchHandler @ 00aa4e09 */
 8821 |   CEGUI::String::~String((String *)&local_13e8);
 8822 |   CEGUI::String::String((String *)&local_1498,"|u");
 8823 |                     /* try { // try from 00a9f3d8 to 00a9f3dc has its CatchHandler @ 00aa618c */
 8824 |   CEGUI::String::grow(lVar28 + 0x418);
 8825 |   *(long *)(lVar28 + 0x418) = local_1498;
 8826 |   lVar16 = lVar28 + 0x440;
 8827 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8828 |     lVar16 = *(long *)(lVar28 + 0x4c0);
 8829 |   }
 8830 |   *(undefined4 *)(lVar16 + local_1498 * 4) = 0;
 8831 |   puVar30 = local_1470;
 8832 |   if (0x20 < local_1490) {
 8833 |     puVar30 = local_13f0;
 8834 |   }
 8835 |   pvVar20 = (void *)(lVar28 + 0x440);
 8836 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8837 |     pvVar20 = *(void **)(lVar28 + 0x4c0);
 8838 |   }
 8839 |   memcpy(pvVar20,puVar30,local_1498 * 4);
 8840 |                     /* try { // try from 00a9f443 to 00a9f463 has its CatchHandler @ 00aa4e09 */
 8841 |   CEGUI::String::~String((String *)&local_1498);
 8842 |   *(undefined1 *)(lVar28 + 0x4c8) = 1;
 8843 |   CEGUI::String::String(local_1548,(uchar *)"SerifSmall");
 8844 |                     /* try { // try from 00a9f46e to 00a9f472 has its CatchHandler @ 00aa5af9 */
 8845 |   lVar28 = CEGUI::FontManager::getFont(CEGUI::Singleton<CEGUI::FontManager>::ms_Singleton);
 8846 |                     /* try { // try from 00a9f479 to 00a9f492 has its CatchHandler @ 00aa4e09 */
 8847 |   CEGUI::String::~String(local_1548);
 8848 |   CEGUI::String::String((String *)&local_15f8,"|c");
 8849 |                     /* try { // try from 00a9f4a5 to 00a9f4a9 has its CatchHandler @ 00aa5ae7 */
 8850 |   CEGUI::String::grow(lVar28 + 0x368);
 8851 |   *(long *)(lVar28 + 0x368) = local_15f8;
 8852 |   lVar16 = lVar28 + 0x390;
 8853 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8854 |     lVar16 = *(long *)(lVar28 + 0x410);
 8855 |   }
 8856 |   *(undefined4 *)(lVar16 + local_15f8 * 4) = 0;
 8857 |   puVar30 = local_15d0;
 8858 |   if (0x20 < local_15f0) {
 8859 |     puVar30 = local_1550;
 8860 |   }
 8861 |   pvVar20 = (void *)(lVar28 + 0x390);
 8862 |   if (0x20 < *(ulong *)(lVar28 + 0x370)) {
 8863 |     pvVar20 = *(void **)(lVar28 + 0x410);
 8864 |   }
 8865 |   memcpy(pvVar20,puVar30,local_15f8 * 4);
 8866 |                     /* try { // try from 00a9f510 to 00a9f529 has its CatchHandler @ 00aa4e09 */
 8867 |   CEGUI::String::~String((String *)&local_15f8);
 8868 |   CEGUI::String::String((String *)&local_16a8,"|u");
 8869 |                     /* try { // try from 00a9f53c to 00a9f540 has its CatchHandler @ 00aa5ad5 */
 8870 |   CEGUI::String::grow(lVar28 + 0x418);
 8871 |   *(long *)(lVar28 + 0x418) = local_16a8;
 8872 |   lVar16 = lVar28 + 0x440;
 8873 |   if (0x20 < *(ulong *)(lVar28 + 0x420)) {
 8874 |     lVar16 = *(long *)(lVar28 + 0x4c0);
 8875 |   }
 8876 |   *(undefined4 *)(lVar16 + local_16a8 * 4) = 0;
 8877 |   puVar30 = local_1680;
 8878 |   if (0x20 < local_16a0) {
```

## `research/decompiled-core/game_ui.c:8497–8507` — renderer setup / изменение HUD после XML

SHA256 полного файла: `f415f44a95978d36423f19824326b89f99d9870acd982f4bad5153364068c05f`

```text
 8497 |     }
 8498 |   }
 8499 |   if (lVar16 != 0) {
 8500 |     CSoundBank::addSample(*(CSoundBank **)(this + 0x16a8),0x1e,*(longlong *)(lVar16 + 0x20));
 8501 |   }
 8502 |   this_02 = operator_new(0x2c8);
 8503 |                     /* try { // try from 00a9ead7 to 00a9eadb has its CatchHandler @ 00aa50e0 */
 8504 |   CEGUI::OgreCEGUIRenderer::OgreCEGUIRenderer
 8505 |             (this_02,*(RenderWindow **)(this + 0x4d0),'d',false,3000,*(SceneManager **)(this + 0x18)
 8506 |             );
 8507 |   *(OgreCEGUIRenderer **)(this + 0x428) = this_02;
```

## `research/decompiled-core/game_ui.c:9450–9496` — renderer setup / изменение HUD после XML

SHA256 полного файла: `f415f44a95978d36423f19824326b89f99d9870acd982f4bad5153364068c05f`

```text
 9450 |       if (0x20 < local_2930) {
 9451 |         puVar23 = local_2890;
 9452 |       }
 9453 |       puVar23[lVar28] = (uint)*(byte *)(local_8e0 + lVar28);
 9454 |     } while (lVar28 != 0);
 9455 |   }
 9456 |   local_2938 = lVar16;
 9457 |                     /* try { // try from 00aa07bc to 00aa07c0 has its CatchHandler @ 00aa4a3a */
 9458 |   uVar14 = CEGUI::WindowManager::loadWindowLayout
 9459 |                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
 9460 |                       SUB81((String *)&local_2938,0));
 9461 |   *(undefined8 *)(this + 0x138) = uVar14;
 9462 |                     /* try { // try from 00aa07cb to 00aa0813 has its CatchHandler @ 00aa4e09 */
 9463 |   CEGUI::String::~String((String *)&local_2938);
 9464 |   convertToScreenScale(this,*(Window **)(this + 0x138),false);
 9465 |   mapToFunctions(this,*(Window **)(this + 0x138));
 9466 |   mapEventHandlers(this,*(Window **)(this + 0x138));
 9467 |   CEGUI::String::String(local_29e8,"PlayButton");
 9468 |                     /* try { // try from 00aa081e to 00aa0822 has its CatchHandler @ 00aa4a28 */
 9469 |   uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
 9470 |   *(undefined8 *)(this + 0x130) = uVar14;
 9471 |                     /* try { // try from 00aa082d to 00aa0859 has its CatchHandler @ 00aa4e09 */
 9472 |   CEGUI::String::~String(local_29e8);
 9473 |   CEGUI::Window::removeChildWindow(*(Window **)(this + 0x138));
 9474 |   CEGUI::String::String(local_2a98,"LeftPaneBlocker");
 9475 |                     /* try { // try from 00aa0864 to 00aa0868 has its CatchHandler @ 00aa4a16 */
 9476 |   CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
 9477 |                     /* try { // try from 00aa086f to 00aa08d4 has its CatchHandler @ 00aa4e09 */
 9478 |   CEGUI::String::~String(local_2a98);
 9479 |   local_6b8 = CEGUI::Window::getPixelRect();
 9480 |   local_6b0 = CONCAT44(uVar34,fVar33);
 9481 |   CEGUI::Rect::operator=((Rect *)(this + 0x199c),(Rect *)&local_6b8);
 9482 |   CEGUI::String::String(local_2b48,"RightPaneBlocker");
 9483 |                     /* try { // try from 00aa08df to 00aa08e3 has its CatchHandler @ 00aa4a04 */
 9484 |   CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
 9485 |                     /* try { // try from 00aa08ea to 00aa094f has its CatchHandler @ 00aa4e09 */
 9486 |   CEGUI::String::~String(local_2b48);
 9487 |   local_6c8 = CEGUI::Window::getPixelRect();
 9488 |   local_6c0 = CONCAT44(uVar34,fVar33);
 9489 |   CEGUI::Rect::operator=((Rect *)(this + 0x19ac),(Rect *)&local_6c8);
 9490 |   CEGUI::String::String(local_2bf8,"PetHudBlocker");
 9491 |                     /* try { // try from 00aa095a to 00aa095e has its CatchHandler @ 00aa49f2 */
 9492 |   CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x138));
 9493 |                     /* try { // try from 00aa0965 to 00aa09ca has its CatchHandler @ 00aa4e09 */
 9494 |   CEGUI::String::~String(local_2bf8);
 9495 |   local_6d8 = CEGUI::Window::getPixelRect();
 9496 |   local_6d0 = CONCAT44(uVar34,fVar33);
```

