# 01-frame-composition

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/linux_desktop_main.cpp:335–365`

SHA256 полного файла: `4c9fac52eca090516da86a5e9f550ddac6cfa079373eb7cd1313952090e2b139`

```text
  335 |     torchlight::UiPointerState ui_pointer_state() const noexcept override {
  336 |         torchlight::UiPointerState state;
  337 |         if (pointer_inside_) state.position = std::array<float, 2>{
  338 |             static_cast<float>(pointer_x_), static_cast<float>(pointer_y_)};
  339 |         state.left_press_origin = ui_press_origin_;
  340 |         return state;
  341 |     }
  342 |     [[nodiscard]] int width() const noexcept { return width_; }
  343 |     [[nodiscard]] int height() const noexcept { return height_; }
  344 | 
  345 |     [[nodiscard]] std::vector<std::uint32_t> take_key_presses() {
  346 |         auto keys = std::move(key_presses_);
  347 |         key_presses_.clear();
  348 |         return keys;
  349 |     }
  350 | 
  351 |     void draw_scene_frame(torchlight::GlesSceneRenderer& renderer,
  352 |                           torchlight::GlesUiRenderer& ui_renderer,
  353 |                           const std::vector<torchlight::InventoryViewLine>& lines,
  354 |                           bool inventory_open, const torchlight::UiHudFrame& hud) {
  355 |         renderer.draw(width_, height_);
  356 |         ui_renderer.draw_hud(hud, width_, height_);
  357 |         ui_renderer.draw_overlay(lines, inventory_open, width_, height_);
  358 |         require_egl(eglSwapBuffers(egl_display_, egl_surface_) == EGL_TRUE, "eglSwapBuffers");
  359 |     }
  360 | 
  361 |     void draw_menu_frame(torchlight::GlesUiRenderer& renderer, const torchlight::FrontendFrame& frame) {
  362 |         renderer.draw(frame, width_, height_);
  363 |         if (glGetError() != GL_NO_ERROR) throw DesktopError("OpenGL ES failed while drawing the frontend");
  364 |         require_egl(eglSwapBuffers(egl_display_, egl_surface_) == EGL_TRUE, "eglSwapBuffers");
  365 |     }
```

## `src/gles_ui_renderer.cpp:145–169`

SHA256 полного файла: `46cdaa34cabd768fef0460e6801db6568a3da1861e0b8d647992da5ccdbf96c3`

```text
  145 |         viewport_height = height;
  146 |         glViewport(0, 0, width, height);
  147 |         glDisable(GL_SCISSOR_TEST);
  148 |         glDisable(GL_DEPTH_TEST);
  149 |         glDisable(GL_CULL_FACE);
  150 |         glEnable(GL_BLEND);
  151 |         glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  152 |         glUseProgram(program);
  153 |         glUniform2f(screen, static_cast<float>(width), static_cast<float>(height));
  154 |         glUniform1i(sampler, 0);
  155 |         glBindBuffer(GL_ARRAY_BUFFER, buffer);
  156 |         glEnableVertexAttribArray(0);
  157 |         glEnableVertexAttribArray(1);
  158 |         glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
  159 |         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
  160 |                               reinterpret_cast<const void *>(2 * sizeof(float)));
  161 |     }
  162 |     void begin(int width, int height) {
  163 |         begin_state(width, height);
  164 |         glClearColor(.045F, .055F, .065F, 1);
  165 |         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  166 |     }
  167 |     void end() {
  168 |         glDisableVertexAttribArray(0);
  169 |         glDisableVertexAttribArray(1);
```

## `src/gles_ui_renderer.cpp:473–591`

SHA256 полного файла: `46cdaa34cabd768fef0460e6801db6568a3da1861e0b8d647992da5ccdbf96c3`

```text
  473 |                                              widget.has_clip ? &widget.clip : nullptr);
  474 |         // A valid image entirely outside its clip is successfully handled,
  475 |         // not a missing skin that should produce a fallback rectangle.
  476 |         if (!geometry) return true;
  477 |         std::vector<Vertex> vertices;
  478 |         quad(vertices, geometry->destination, geometry->source);
  479 |         draw_batch(vertices, {1, 1, 1, 1}, texture->id);
  480 |         return true;
  481 |     }
  482 |     // prototype: fallback palette, diagnostic glyphs and button chrome. The
  483 |     // resource-derived rectangles, images and fonts are not a complete CEGUI skin.
  484 |     void draw(const FrontendFrame &frame, int width, int height) {
  485 |         begin(width, height);
  486 |         for (const auto &w : frame.decorations)
  487 |             draw_image(w, {});
  488 |         if (!draw_text("FrizQuadrataBig", frame.title, 24, 16, static_cast<float>(width) - 24,
  489 |                        {.92F, .90F, .82F, 1})) {
  490 |             std::vector<Vertex> letters;
  491 |             text(letters, frame.title, 24, 20, width >= 950 ? 2 : 1, width);
  492 |             draw_batch(letters, {.92F, .90F, .82F, 1});
  493 |         }
  494 |         for (const auto &button : frame.buttons) {
  495 |             // resource-derived: checked GuiLook/Checkbox shows PushedImage
  496 |             // (UIIcons:CheckChecked, a complete checked box). Load slots and
  497 |             // class buttons carry selected without a pushed image, so they
  498 |             // keep the previous focus/normal choice.
  499 |             const auto explicit_state = [&](const char *name, const std::string &image) {
  500 |                 return !image.empty() || (!button.supplemental &&
  501 |                     button.widget.properties.find(name) != button.widget.properties.end());
  502 |             };
  503 |             const std::string image_name = !button.enabled && explicit_state("DisabledImage", button.disabled_image)
  504 |                 ? button.disabled_image : button.selected && button.enabled && explicit_state("PushedImage", button.pushed_image)
  505 |                 ? button.pushed_image : button.focused && button.enabled && explicit_state("HoverImage", button.hover_image)
  506 |                 ? button.hover_image : button.image;
  507 |             auto background = button.widget;
  508 |             background.rect = button.rect;
  509 |             background.image = image_name;
  510 |             // Keep the pre-existing diagnostic fallback for a genuinely
  511 |             // missing look (e.g. minimal authored fixtures). A known look or
  512 |             // an explicit image property, even empty, must never acquire it.
  513 |             const bool missing_look = !button.widget.type.empty() &&
  514 |                 !resources->widget_images(button.widget.type) &&
  515 |                 button.widget.properties.count("NormalImage") == 0 &&
  516 |                 button.widget.properties.count("Image") == 0;
  517 |             if (!draw_image(background, {}) && (button.supplemental || missing_look)) {
  518 |                 std::vector<Vertex> v; quad(v, button.rect);
  519 |                 draw_batch(v, button.enabled
  520 |                     ? (button.focused ? std::array<float, 4>{.32F, .30F, .21F, .95F}
  521 |                                       : std::array<float, 4>{.12F, .15F, .17F, .95F})
  522 |                     : std::array<float, 4>{.08F, .09F, .1F, .85F});
  523 |             }
  524 |             auto label = button.widget;
  525 |             label.rect = button.rect;
  526 |             label.text = button.text;
  527 |             label.font = button.font.empty() ? "Serif" : button.font;
  528 |             label.enabled = button.enabled;
  529 |             // Centring is a fallback-port policy only for controls whose look
  530 |             // defines no TextComponent area (supplemental buttons). Real looks
  531 |             // carry their own VertFormat/HorzFormat (Checkbox Left/Centre,
  532 |             // StandardButton Centre/Centre); forcing centre there pushed
  533 |             // checkbox labels hundreds of pixels right of the box.
  534 |             if (label.property("HorzFormatting").empty() && label.property("HorzTextFormatting").empty() &&
  535 |                 (!resources->widget_text_passes(label.type) ||
  536 |                  resources->widget_text_passes(label.type)->empty()))
  537 |                 label.properties["HorzFormatting"] = "CentreAligned";
  538 |             if (label.property("VertFormatting").empty() &&
  539 |                 (!resources->widget_text_passes(label.type) ||
  540 |                  resources->widget_text_passes(label.type)->empty()))
  541 |                 label.properties["VertFormatting"] = "VertCentred";
  542 |             draw_widget_text(label);
  543 |             // PORT selection chrome belongs only to PORT controls. An original
  544 |             // checkbox/tab must not acquire an invented gold border.
  545 |             if (button.selected && button.supplemental) {
  546 |                 std::vector<Vertex> border;
  547 |                 quad(border, {button.rect.x, button.rect.y, button.rect.width, 2});
  548 |                 quad(border, {button.rect.x, button.rect.y + button.rect.height - 2, button.rect.width, 2});
  549 |                 draw_batch(border, {.9F, .75F, .3F, 1});
  550 |             }
  551 |         }
  552 |         for (const auto &w : frame.texts) draw_widget_text(w);
  553 |         float y = 48.0F;
  554 |         auto *note_font = prepare_font("SerifSmall", width, height);
  555 |         for (const auto &line : frame.notes) {
  556 |             std::vector<Vertex> letters;
  557 |             if (note_font != nullptr &&
  558 |                 text_run(note_font, line.text, 24, y, static_cast<float>(width) - 24, letters))
  559 |                 draw_batch(letters, {.88F, .86F, .78F, 1}, note_font->id);
  560 |             else {
  561 |                 text(letters, line.text, 24, y, width >= 950 ? 2 : 1, width);
  562 |                 draw_batch(letters, {.92F, .90F, .82F, 1});
  563 |             }
  564 |             y += note_font != nullptr ? std::max(9.0F, note_font->font->line_height() + 2.0F)
  565 |                                       : 9.0F * (width >= 950 ? 2 : 1);
  566 |         }
  567 |         end();
  568 |     }
  569 |     // Composites over the current scene; never clears the framebuffer.
  570 |     void draw_hud(const UiHudFrame &frame, int width, int height) {
  571 |         begin_state(width, height);
  572 |         for (const auto &w : frame.images)
  573 |             draw_image(w, {});
  574 |         for (const auto &bar : frame.bars) {
  575 |             auto rect = bar.widget.rect;
  576 |             if (bar.vertical) {
  577 |                 const float full = rect.height;
  578 |                 rect.height = full * bar.fraction;
  579 |                 if (bar.bottom_anchored)
  580 |                     rect.y += full - rect.height;
  581 |             } else
  582 |                 rect.width *= bar.fraction;
  583 |             if (rect.width <= 0 || rect.height <= 0)
  584 |                 continue;
  585 |             auto widget = bar.widget;
  586 |             widget.rect = rect;
  587 |             draw_image(widget, {});
  588 |         }
  589 |         for (const auto &w : frame.buttons) draw_image(w, {});
  590 |         for (const auto &w : frame.texts) draw_widget_text(w);
  591 |         end();
```

## `src/application.cpp:967–1002`

SHA256 полного файла: `76f54e35350880bc0452d038db73d6ef06f474447594b30bcc5bb8125d7a3143`

```text
  967 |                     app_running = false;
  968 |                     break;
  969 |                 }
  970 |                 // PORT orchestration fix: settings opened from pause is still
  971 |                 // a modal frontend page, never a branch of the simulation.
  972 |                 if (frontend.page() == torchlight::FrontendPage::pause ||
  973 |                     frontend.page() == torchlight::FrontendPage::settings) {
  974 |                     window.observe_frontend(frontend.page(), frontend.frame(window.width(), window.height()), frontend.character_name());
  975 |                     static_cast<void>(frontend.frame(window.width(), window.height()));
  976 |                     for (const auto key : window.take_key_presses()) { frontend_key(frontend, key); static_cast<void>(frontend.frame(window.width(), window.height())); }
  977 |                     if (const auto click = window.take_left_click()) frontend.click(static_cast<float>((*click)[0]), static_cast<float>((*click)[1]));
  978 |                     static_cast<void>(window.take_ui_click());
  979 |                     if (const auto request = frontend.take_request()) {
  980 |                         if (request->command == torchlight::FrontendCommand::apply_settings) {
  981 |                             try { apply_settings(*request); }
  982 |                             catch (const std::exception &e) {
  983 |                                 frontend.error(std::string("CANNOT SAVE SETTINGS: ") + e.what());
  984 |                             }
  985 |                         } else if (request->command == torchlight::FrontendCommand::save ||
  986 |                                    request->command == torchlight::FrontendCommand::save_and_menu ||
  987 |                                    request->command == torchlight::FrontendCommand::save_and_quit) {
  988 |                             try {
  989 |                                 checkpoint_now(); frontend.saved(request->command);
  990 |                                 saved_for_exit = request->command == torchlight::FrontendCommand::save_and_quit;
  991 |                             } catch (const std::exception &e) {
  992 |                                 frontend.error(std::string("SAVE FAILED: ") + e.what());
  993 |                             }
  994 |                         } else frontend.error("UNSUPPORTED COMMAND WHILE GAMEPLAY IS PAUSED");
  995 |                     }
  996 |                     if (frontend.page() == torchlight::FrontendPage::main) { return_to_menu = true; break; }
  997 |                     if (frontend.page() == torchlight::FrontendPage::quit) { app_running = false; break; }
  998 |                     if (frontend.page() == torchlight::FrontendPage::pause ||
  999 |                         frontend.page() == torchlight::FrontendPage::settings)
 1000 |                         window.draw_menu_frame(ui_renderer, frontend.frame(window.width(), window.height()));
 1001 |                     previous_frame = window.clock_seconds();
 1002 |                     continue;
```

