# 02-pointer-and-keyboard

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/linux_desktop_main.cpp:448–507`

SHA256 полного файла: `4c9fac52eca090516da86a5e9f550ddac6cfa079373eb7cd1313952090e2b139`

```text
  448 |     static void pointer_enter(void* data, wl_pointer*, std::uint32_t, wl_surface*, wl_fixed_t x,
  449 |                               wl_fixed_t y) {
  450 |         static_cast<DesktopWindow*>(data)->pointer_inside_ = true;
  451 |         pointer_motion(data, nullptr, 0, x, y);
  452 |     }
  453 |     static void pointer_leave(void* data, wl_pointer*, std::uint32_t, wl_surface*) {
  454 |         auto &self = *static_cast<DesktopWindow*>(data);
  455 |         self.pointer_inside_ = false;
  456 |         self.ui_press_origin_.reset(); self.ui_click_.reset();
  457 |     }
  458 |     static void pointer_motion(void* data, wl_pointer*, std::uint32_t, wl_fixed_t x,
  459 |                                wl_fixed_t y) {
  460 |         auto& self = *static_cast<DesktopWindow*>(data);
  461 |         self.pointer_x_ = wl_fixed_to_int(x);
  462 |         self.pointer_y_ = wl_fixed_to_int(y);
  463 |     }
  464 |     static void pointer_button(void* data, wl_pointer*, std::uint32_t, std::uint32_t,
  465 |                                std::uint32_t button, std::uint32_t state) {
  466 |         auto& self = *static_cast<DesktopWindow*>(data);
  467 |         if (button != BTN_LEFT) return;
  468 |         if (state == WL_POINTER_BUTTON_STATE_PRESSED) {
  469 |             self.left_click_ = {self.pointer_x_, self.pointer_y_};
  470 |             self.ui_press_origin_ = std::array<float, 2>{
  471 |                 static_cast<float>(self.pointer_x_), static_cast<float>(self.pointer_y_)};
  472 |         } else if (state == WL_POINTER_BUTTON_STATE_RELEASED) {
  473 |             if (self.pointer_inside_ && self.ui_press_origin_)
  474 |                 self.ui_click_ = torchlight::UiPointerClick{*self.ui_press_origin_,
  475 |                     {static_cast<float>(self.pointer_x_), static_cast<float>(self.pointer_y_)}};
  476 |             self.ui_press_origin_.reset();
  477 |         }
  478 |     }
  479 |     static void pointer_axis(void*, wl_pointer*, std::uint32_t, std::uint32_t, wl_fixed_t) {}
  480 |     static void pointer_frame(void*, wl_pointer*) {}
  481 |     static void pointer_axis_source(void*, wl_pointer*, std::uint32_t) {}
  482 |     static void pointer_axis_stop(void*, wl_pointer*, std::uint32_t, std::uint32_t) {}
  483 |     static void pointer_axis_discrete(void*, wl_pointer*, std::uint32_t, std::int32_t) {}
  484 |     static void keyboard_keymap(void*, wl_keyboard*, std::uint32_t, std::int32_t fd,
  485 |                                 std::uint32_t) {
  486 |         if (fd >= 0) {
  487 |             close(fd);
  488 |         }
  489 |     }
  490 |     static void keyboard_enter(void*, wl_keyboard*, std::uint32_t, wl_surface*, wl_array*) {}
  491 |     static void keyboard_leave(void*, wl_keyboard*, std::uint32_t, wl_surface*) {}
  492 |     static void keyboard_key(void* data, wl_keyboard*, std::uint32_t, std::uint32_t,
  493 |                              std::uint32_t key, std::uint32_t state) {
  494 |         if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
  495 |             static_cast<DesktopWindow*>(data)->key_presses_.push_back(key);
  496 |     }
  497 |     static void keyboard_modifiers(void*, wl_keyboard*, std::uint32_t, std::uint32_t,
  498 |                                    std::uint32_t, std::uint32_t, std::uint32_t) {}
  499 |     static void keyboard_repeat_info(void*, wl_keyboard*, std::int32_t, std::int32_t) {}
  500 | 
  501 |     wl_display* display_ = nullptr;
  502 |     wl_registry* registry_ = nullptr;
  503 |     wl_compositor* compositor_ = nullptr;
  504 |     xdg_wm_base* wm_base_ = nullptr;
  505 |     wl_surface* surface_ = nullptr;
  506 |     xdg_surface* xdg_surface_ = nullptr;
  507 |     xdg_toplevel* toplevel_ = nullptr;
```

## `src/frontend.cpp:211–220`

SHA256 полного файла: `7dd79f1b88839684dbe8e007fe8e516d025b23044cf60b74f9e75c776b0b680b`

```text
  211 | void Frontend::click(float x, float y) {
  212 |     if (request_)
  213 |         return;
  214 |     for (std::size_t i = buttons_.size(); i > 0; --i)
  215 |         if (buttons_[i - 1].enabled && buttons_[i - 1].rect.contains(x, y) &&
  216 |             buttons_[i - 1].widget.clip.contains(x, y)) {
  217 |             focus_ = i - 1;
  218 |             activate(buttons_[i - 1].id);
  219 |             return;
  220 |         }
```

## `src/frontend.cpp:637–655`

SHA256 полного файла: `7dd79f1b88839684dbe8e007fe8e516d025b23044cf60b74f9e75c776b0b680b`

```text
  637 |     if (page_ == FrontendPage::main && show_credits_) {
  638 |         FrontendButton close;
  639 |         close.id = "credits-b";
  640 |         close.rect = {0, 0, static_cast<float>(width), static_cast<float>(height)};
  641 |         close.widget.rect = close.widget.clip = close.rect;
  642 |         close.enabled = true;
  643 |         frame.buttons.push_back(std::move(close));
  644 |     }
  645 |     if (!unsupported.empty()) frame.notes.push_back({
  646 |         "PORT: DISABLED RESOURCE CONTROLS ARE NOT IMPLEMENTED (SETTINGS / ORIGINAL EXIT / OTHER MENUS).", false});
  647 |     if (focus_ >= frame.buttons.size()) focus_ = 0;
  648 |     if (!frame.buttons.empty()) {
  649 |         for (std::size_t n = 0; n < frame.buttons.size() && !frame.buttons[focus_].enabled; ++n)
  650 |             focus_ = (focus_ + 1) % frame.buttons.size();
  651 |         if (frame.buttons[focus_].enabled) frame.buttons[focus_].focused = true;
  652 |     }
  653 |     if (!status_.empty()) frame.notes.push_back({status_, false});
  654 |     if (!frame.original_layout) frame.notes.push_back({"PORT FALLBACK: ORIGINAL LAYOUT UNAVAILABLE", false});
  655 |     buttons_ = frame.buttons;
```

## `src/application.cpp:1010–1043`

SHA256 полного файла: `76f54e35350880bc0452d038db73d6ef06f474447594b30bcc5bb8125d7a3143`

```text
 1010 |                 auto world_click = window.take_left_click();
 1011 |                 // Release state remains useful for host button visuals, but this HUD
 1012 |                 // subscribes to MouseButtonDown in the original, not EventClicked.
 1013 |                 static_cast<void>(window.take_ui_click());
 1014 |                 auto key_presses = window.take_key_presses();
 1015 |                 if (!inventory_view.open && world_click) {
 1016 |                     const auto input_hud = ui_hud.frame(window.width(), window.height(), {});
 1017 |                     const float x = static_cast<float>((*world_click)[0]);
 1018 |                     const float y = static_cast<float>((*world_click)[1]);
 1019 |                     if (torchlight::hud_button_at(input_hud, x, y)) {
 1020 |                         const auto callback = torchlight::hud_press_callback(input_hud, x, y);
 1021 |                         world_click.reset(); // Transparent/disabled targets also consume the press.
 1022 |                         if (callback && player_combat.alive()) {
 1023 |                             window.notice("hud_dispatch_down", *callback);
 1024 |                             // Existing PORT presentations, not original panel implementations.
 1025 |                             if (*callback == "guiToggleInventory") key_presses.push_back(torchlight::physical_key::I);
 1026 |                             else if (*callback == "guiToggleSkills") key_presses.push_back(torchlight::physical_key::K);
 1027 |                             else if (*callback == "guiToggleQuests") key_presses.push_back(torchlight::physical_key::J);
 1028 |                             else if (*callback == "guiToggleOptions") key_presses.push_back(torchlight::physical_key::ESC);
 1029 |                             else window.notice("hud_callback_unimplemented", *callback);
 1030 |                         }
 1031 |                     }
 1032 |                 }
 1033 |                 for (const auto key : key_presses) {
 1034 |                     if (!player_combat.alive()) {
 1035 |                         if (key == torchlight::physical_key::ESC) { frontend.pause(); continue; }
 1036 |                         if (key != torchlight::physical_key::R) continue;
 1037 |                         const auto recovery = session.recover_at_entry(enemies, player_motion, level.recovery_anchor);
 1038 |                         if (recovery.status != torchlight::RecoveryStatus::recovered) continue;
 1039 |                         inventory_view.open = false;
 1040 |                         active_interaction.reset(); interactions.cancel(); active_pickup = 0; active_path.clear(); next_path_node = 0;
 1041 |                         player_attack_animation_active = false;
 1042 |                         player_animation_state = player_transition_from_state = PlayerAnimationState::idle;
 1043 |                         player_animation_time = player_transition_time = 0;
```

