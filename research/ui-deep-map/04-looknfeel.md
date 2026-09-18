# 04-looknfeel

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/ui_layout.cpp:456–666`

SHA256 полного файла: `d7b82bdadff2ce2795c75ad371321aa641b377168e156277041cff2ba4964cb9`

```text
  456 | namespace {
  457 | // resource-derived: evaluates one Falagard edge/size Dim inside a TextComponent
  458 | // Area as (absolute pixels + scale * widget extent). Children forms observed
  459 | // in GuiLook.looknfeel: AbsoluteDim, UnifiedDim(scale, Width|Height) with an
  460 | // optional nested DimOperator, and direct DimOperator. Anything else fails the
  461 | // whole look so the caller keeps its single-pass fallback instead of rendering
  462 | // invented geometry.
  463 | bool dim_value(const std::vector<Node> &nodes, std::size_t dim, float extent,
  464 |                float &absolute, float &scale, std::string &error) {
  465 |     absolute = 0;
  466 |     scale = 0;
  467 |     for (std::size_t i = 0; i < nodes.size(); ++i) {
  468 |         if (nodes[i].parent != static_cast<int>(dim)) continue;
  469 |         if (nodes[i].tag == "AbsoluteDim") {
  470 |             const auto raw = attr(nodes[i], "value");
  471 |             float v = 0;
  472 |             const auto parsed =
  473 |                 std::from_chars(raw.data(), raw.data() + raw.size(), v);
  474 |             if (parsed.ec != std::errc{} || parsed.ptr != raw.data() + raw.size() ||
  475 |                 !std::isfinite(v)) {
  476 |                 error = "bad AbsoluteDim";
  477 |                 return false;
  478 |             }
  479 |             absolute += v;
  480 |         } else if (nodes[i].tag == "UnifiedDim") {
  481 |             const auto type = attr(nodes[i], "scale");
  482 |             const auto kind = attr(nodes[i], "type");
  483 |             if (kind != "Width" && kind != "Height") {
  484 |                 error = "unsupported UnifiedDim";
  485 |                 return false;
  486 |             }
  487 |             float s = 0;
  488 |             const auto parsed =
  489 |                 std::from_chars(type.data(), type.data() + type.size(), s);
  490 |             if (parsed.ec != std::errc{} || parsed.ptr != type.data() + type.size() ||
  491 |                 !std::isfinite(s)) {
  492 |                 error = "bad UnifiedDim scale";
  493 |                 return false;
  494 |             }
  495 |             scale += s;
  496 |             for (std::size_t k = 0; k < nodes.size(); ++k) {
  497 |                 if (nodes[k].parent != static_cast<int>(i)) continue;
  498 |                 if (nodes[k].tag != "DimOperator") {
  499 |                     error = "unsupported UnifiedDim child";
  500 |                     return false;
  501 |                 }
  502 |                 const auto op = attr(nodes[k], "op");
  503 |                 bool have_operand = false;
  504 |                 for (std::size_t m = 0; m < nodes.size(); ++m) {
  505 |                     if (nodes[m].parent != static_cast<int>(k) ||
  506 |                         nodes[m].tag != "AbsoluteDim")
  507 |                         continue;
  508 |                     const auto raw = attr(nodes[m], "value");
  509 |                     float v = 0;
  510 |                     const auto operand =
  511 |                         std::from_chars(raw.data(), raw.data() + raw.size(), v);
  512 |                     if (operand.ec != std::errc{} ||
  513 |                         operand.ptr != raw.data() + raw.size() || !std::isfinite(v)) {
  514 |                         error = "bad DimOperator operand";
  515 |                         return false;
  516 |                     }
  517 |                     have_operand = true;
  518 |                     if (op == "Add") absolute += v;
  519 |                     else if (op == "Subtract") absolute -= v;
  520 |                     else {
  521 |                         error = "unsupported DimOperator";
  522 |                         return false;
  523 |                     }
  524 |                     break;
  525 |                 }
  526 |                 if (!have_operand) {
  527 |                     error = "DimOperator without operand";
  528 |                     return false;
  529 |                 }
  530 |             }
  531 |         } else if (nodes[i].tag == "DimOperator") {
  532 |             const auto op = attr(nodes[i], "op");
  533 |             bool have_operand = false;
  534 |             for (std::size_t k = 0; k < nodes.size(); ++k) {
  535 |                 if (nodes[k].parent != static_cast<int>(i) ||
  536 |                     nodes[k].tag != "AbsoluteDim")
  537 |                     continue;
  538 |                 const auto raw = attr(nodes[k], "value");
  539 |                 float v = 0;
  540 |                 const auto operand =
  541 |                     std::from_chars(raw.data(), raw.data() + raw.size(), v);
  542 |                 if (operand.ec != std::errc{} || operand.ptr != raw.data() + raw.size() ||
  543 |                     !std::isfinite(v)) {
  544 |                     error = "bad DimOperator operand";
  545 |                     return false;
  546 |                 }
  547 |                 have_operand = true;
  548 |                 if (op == "Add") absolute += v;
  549 |                 else if (op == "Subtract") absolute -= v;
  550 |                 else {
  551 |                     error = "unsupported DimOperator";
  552 |                     return false;
  553 |                 }
  554 |                 break;
  555 |             }
  556 |             if (!have_operand) {
  557 |                 error = "DimOperator without operand";
  558 |                 return false;
  559 |             }
  560 |         } else {
  561 |             error = "unsupported Dim child";
  562 |             return false;
  563 |         }
  564 |     }
  565 |     static_cast<void>(extent);
  566 |     return true;
  567 | }
  568 | } // namespace
  569 | void UiResources::ensure_looknfeel() {
  570 |     if (looknfeel_loaded_)
  571 |         return;
  572 |     looknfeel_loaded_ = true;
  573 |     const auto *entry = archive_->find_normalized("media/UI/GuiLook.looknfeel");
  574 |     if (!entry)
  575 |         return;
  576 |     try {
  577 |         const auto text = decode(archive_->read(*entry));
  578 |         std::size_t position = 0;
  579 |         while (true) {
  580 |             const auto start = text.find("<WidgetLook", position);
  581 |             if (start == std::string::npos) break;
  582 |             const auto section_end = text.find("</WidgetLook>", start);
  583 |             if (section_end == std::string::npos)
  584 |                 throw std::runtime_error("unterminated WidgetLook");
  585 |             position = section_end + 13;
  586 |             const auto section = text.substr(start, position - start);
  587 |             const auto nodes = parse_xml({section.begin(), section.end()});
  588 |             if (nodes.empty() || nodes.front().tag != "WidgetLook") continue;
  589 |             const auto look = upper(attr(nodes.front(), "name"));
  590 |             UiWidgetImages images;
  591 |             std::map<std::string, std::string> defaults;
  592 |             // Only direct defaults, never similarly named properties
  593 |             // of a Child/ImagerySection or a later WidgetLook.
  594 |             for (const auto &n : nodes) {
  595 |                 if (n.parent != 0 || n.tag != "PropertyDefinition") continue;
  596 |                 const auto key = attr(n, "name"), value = attr(n, "initialValue");
  597 |                 if (key == "NormalImage") images.normal = value;
  598 |                 else if (key == "HoverImage") images.hover = value;
  599 |                 else if (key == "PushedImage") images.pushed = value;
  600 |                 else if (key == "DisabledImage") images.disabled = value;
  601 |                 if (!key.empty()) defaults[key] = value;
  602 |             }
  603 |             widget_images_.insert_or_assign(look, std::move(images));
  604 |             look_defaults_.insert_or_assign(look, std::move(defaults));
  605 |             // Ordered TextComponent passes in document order (shadow first).
  606 |             // Areas are widget-relative: absolute pixels plus a multiple of the
  607 |             // widget extent (Checkbox labels start past the box). Width comes
  608 |             // from the first component (Width, or RightEdge minus LeftEdge).
  609 |             std::vector<UiTextPass> passes;
  610 |             UiTextLayout text_layout;
  611 |             bool have_layout = false;
  612 |             std::string failure;
  613 |             for (std::size_t t = 0; t < nodes.size() && failure.empty(); ++t) {
  614 |                 if (nodes[t].tag != "TextComponent") continue;
  615 |                 UiTextPass pass;
  616 |                 bool have_x = false, have_y = false;
  617 |                 float left_abs = 0, left_scale = 0, top_abs = 0, top_scale = 0;
  618 |                 float width_abs = 0, width_scale = 0, right_abs = 0, right_scale = 0;
  619 |                 bool have_width = false, have_right = false;
  620 |                 for (std::size_t i = 0; i < nodes.size() && failure.empty(); ++i) {
  621 |                     if (nodes[i].parent != static_cast<int>(t)) continue;
  622 |                     if (nodes[i].tag == "Area") {
  623 |                         for (std::size_t d = 0; d < nodes.size() && failure.empty(); ++d) {
  624 |                             if (nodes[d].parent != static_cast<int>(i) ||
  625 |                                 nodes[d].tag != "Dim")
  626 |                                 continue;
  627 |                             const auto kind = attr(nodes[d], "type");
  628 |                             float absolute = 0, scale = 0;
  629 |                             if (kind == "LeftEdge") {
  630 |                                 if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
  631 |                                 left_abs = absolute;
  632 |                                 left_scale = scale;
  633 |                                 have_x = true;
  634 |                             } else if (kind == "TopEdge") {
  635 |                                 if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
  636 |                                 top_abs = absolute;
  637 |                                 top_scale = scale;
  638 |                                 have_y = true;
  639 |                             } else if (kind == "Width") {
  640 |                                 if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
  641 |                                 width_abs = absolute;
  642 |                                 width_scale = scale;
  643 |                                 have_width = true;
  644 |                             } else if (kind == "RightEdge") {
  645 |                                 if (!dim_value(nodes, d, 0, absolute, scale, failure)) break;
  646 |                                 right_abs = absolute;
  647 |                                 right_scale = scale;
  648 |                                 have_right = true;
  649 |                             } else if (kind == "Height" || kind == "BottomEdge") {
  650 |                                 float ignored_abs = 0, ignored_scale = 0;
  651 |                                 if (!dim_value(nodes, d, 0, ignored_abs, ignored_scale, failure))
  652 |                                     break;
  653 |                             } else {
  654 |                                 failure = "unsupported Area Dim";
  655 |                                 break;
  656 |                             }
  657 |                         }
  658 |                     } else if (nodes[i].tag == "ColourProperty") {
  659 |                         pass.colour_property = attr(nodes[i], "name");
  660 |                     } else if (nodes[i].tag == "HorzFormat") {
  661 |                         // resource-derived: Checkbox LeftAligned, StandardButton
  662 |                         // CentreAligned; StaticText/ItemText use *Property and
  663 |                         // stay deferred to the widget (pass fields unset).
  664 |                         const auto format = upper(attr(nodes[i], "type"));
  665 |                         if (format.find("CENTRE") != std::string::npos ||
  666 |                             format.find("CENTER") != std::string::npos)
```

## `src/gles_ui_renderer.cpp:333–454`

SHA256 полного файла: `46cdaa34cabd768fef0460e6801db6568a3da1861e0b8d647992da5ccdbf96c3`

```text
  333 |     void draw_widget_text(const UiResolvedWidget &w) {
  334 |         if (!w.visible || w.text.empty() || w.rect.width <= 0 || w.rect.height <= 0) return;
  335 |         // original-code: CEGUI default font is Serif
  336 |         // (CGameUI::create @0xa9f007 setDefaultFont("Serif", rodata 0xfe4944)).
  337 |         // Windows without Font inherit it; FrizQuadrata was a wrong fallback.
  338 |         auto *texture = prepare_font(w.font.empty() ? "Serif" : w.font,
  339 |                                      viewport_width, viewport_height);
  340 |         auto style = w.text_style();
  341 |         // resource-derived: an explicit per-TextComponent VertFormat/HorzFormat
  342 |         // (Checkbox Left/CentreAligned, StandardButton Centre/CentreAligned)
  343 |         // wins over the widget properties; components deferring through
  344 |         // *Property (StaticText/ItemText) keep the widget style. The last
  345 |         // specified pass is the main text.
  346 |         const auto passes = resources->widget_text_passes(w.type);
  347 |         if (passes && !passes->empty()) {
  348 |             for (const auto &pass : *passes) {
  349 |                 if (pass.horz) style.horizontal = *pass.horz;
  350 |                 if (pass.vert) style.vertical = *pass.vert;
  351 |             }
  352 |         }
  353 |         const int fallback_scale = viewport_width >= 950 ? 2 : 1;
  354 |         const float line_height = texture ? texture->font->line_height() : 8.0F * fallback_scale;
  355 |         // resource-derived: Falagard TextComponent passes from GuiLook.looknfeel
  356 |         // (shadow/outline offsets first, main text last). The look's first Area
  357 |         // sets the wrap width; a degenerate area (Checkbox labels past the box)
  358 |         // runs to the viewport edge. Unknown looks keep the widget-rect
  359 |         // single-pass fallback instead of invented geometry.
  360 |         const auto layout = resources->widget_text_layout(w.type);
  361 |         float wrap = w.rect.width;
  362 |         if (passes && !passes->empty() && layout) {
  363 |             const float candidate =
  364 |                 layout->width_abs + layout->width_scale * w.rect.width;
  365 |             wrap = candidate > 0 ? candidate
  366 |                                  : static_cast<float>(viewport_width) - w.rect.x;
  367 |             if (!(wrap > 0)) wrap = w.rect.width;
  368 |         }
  369 |         const auto lines = ui_text_lines(w.text, wrap, style.wrap, [&](char32_t c) {
  370 |             return texture ? texture->font->advance(c) : 6.0F * fallback_scale;
  371 |         });
  372 |         float y = w.rect.y;
  373 |         const float height = static_cast<float>(lines.size()) * line_height;
  374 |         if (style.vertical == UiTextVertical::centre) y += (w.rect.height - height) * .5F;
  375 |         else if (style.vertical == UiTextVertical::bottom) y += w.rect.height - height;
  376 |         const float top = y;
  377 |         std::vector<Vertex> letters;
  378 |         for (const auto &line : lines) {
  379 |             float x = w.rect.x;
  380 |             if (style.horizontal == UiTextHorizontal::centre) x += (wrap - line.width) * .5F;
  381 |             else if (style.horizontal == UiTextHorizontal::right) x += wrap - line.width;
  382 |             for (const auto c : line.text) {
  383 |                 if (texture) {
  384 |                     if (const auto *g = texture->font->glyph(c)) {
  385 |                         if (g->width > 0 && g->height > 0)
  386 |                             quad(letters, {x + g->bearing_x, y + texture->font->ascent() - g->bearing_y,
  387 |                                            g->width, g->height},
  388 |                                  {g->u0, g->v0, g->u1 - g->u0, g->v1 - g->v0});
  389 |                         x += g->advance;
  390 |                     }
  391 |                 } else {
  392 |                     // Missing font: visible diagnostic glyph, never reinterpret UTF-8 bytes.
  393 |                     const char glyph = c >= 32 && c < 127 ? static_cast<char>(c) : '?';
  394 |                     text(letters, std::string(1, glyph), x, y, fallback_scale, viewport_width + 16);
  395 |                     x += 6.0F * fallback_scale;
  396 |                 }
  397 |             }
  398 |             y += line_height;
  399 |         }
  400 |         sync_font(texture);
  401 |         if (!passes || passes->empty()) {
  402 |             scissor(w.clip);
  403 |             const auto base = text_colour(w);
  404 |             const std::array<float, 4> tint =
  405 |                 w.enabled ? base
  406 |                           : std::array<float, 4>{base[0] * 0.55F, base[1] * 0.55F,
  407 |                                                  base[2] * 0.55F, base[3]};
  408 |             draw_batch(letters, tint, texture ? texture->id : 0);
  409 |         } else {
  410 |             // Text lives in the look Area, which may extend past the widget
  411 |             // (Checkbox labels); clip to the area against the viewport, not to
  412 |             // the widget box. Ancestor-container clipping stays open.
  413 |             float x0 = w.rect.x + passes->front().dx +
  414 |                        passes->front().x_scale * w.rect.width;
  415 |             float x1 = x0;
  416 |             float y0 = top;
  417 |             for (const auto &pass : *passes) {
  418 |                 x0 = std::min(x0, w.rect.x + pass.dx + pass.x_scale * w.rect.width);
  419 |                 x1 = std::max(x1, w.rect.x + pass.dx + pass.x_scale * w.rect.width);
  420 |                 y0 = std::min(y0, top + pass.dy + pass.y_scale * w.rect.height);
  421 |             }
  422 |             UiRect area{x0, y0, (x1 - x0) + wrap, height + (top - y0)};
  423 |             area.x = std::max(area.x, 0.0F);
  424 |             area.y = std::max(area.y, 0.0F);
  425 |             area.width = std::min(area.width, static_cast<float>(viewport_width) - area.x);
  426 |             area.height = std::min(area.height, static_cast<float>(viewport_height) - area.y);
  427 |             scissor(area);
  428 |             for (const auto &pass : *passes) {
  429 |                 std::array<float, 4> colour{1, 1, 1, 1};
  430 |                 if (pass.colour_property.empty()) {
  431 |                     colour = text_colour(w);
  432 |                 } else {
  433 |                     auto raw = w.property(pass.colour_property);
  434 |                     if (raw.empty())
  435 |                         raw = resources->look_default(w.type, pass.colour_property);
  436 |                     colour = parse_text_argb(raw).value_or(std::array<float, 4>{1, 1, 1, 1});
  437 |                 }
  438 |                 if (!w.enabled) {
  439 |                     colour[0] *= 0.55F;
  440 |                     colour[1] *= 0.55F;
  441 |                     colour[2] *= 0.55F;
  442 |                 }
  443 |                 const float sx = pass.dx + pass.x_scale * w.rect.width;
  444 |                 const float sy = pass.dy + pass.y_scale * w.rect.height;
  445 |                 if (sx == 0 && sy == 0) {
  446 |                     draw_batch(letters, colour, texture ? texture->id : 0);
  447 |                 } else {
  448 |                     std::vector<Vertex> shifted;
  449 |                     shifted.reserve(letters.size());
  450 |                     for (const auto &v : letters)
  451 |                         shifted.push_back({v.x + sx, v.y + sy, v.u, v.v});
  452 |                     draw_batch(shifted, colour, texture ? texture->id : 0);
  453 |                 }
  454 |             }
```

## `src/frontend.cpp:598–624`

SHA256 полного файла: `7dd79f1b88839684dbe8e007fe8e516d025b23044cf60b74f9e75c776b0b680b`

```text
  598 |     } else if (page_ == FrontendPage::settings) {
  599 |         // resource-derived: settingsmenu.layout checkboxes toggle the live
  600 |         // draft; sliders/comboboxes show the draft value but stay disabled
  601 |         // (drag/dropdown interaction stays open). Apply persists the file.
  602 |         for (const auto &widget : widgets) {
  603 |             const auto kind = upper(widget.type);
  604 |             const auto key = upper(leaf(widget.name));
  605 |             if (kind.find("CHECKBOX") != std::string::npos) {
  606 |                 if (const auto field = setting_flag(key))
  607 |                     add("setting-" + key, std::string{}, true, settings_draft_.*field);
  608 |                 else if (key == "ANTIALIASING")
  609 |                     // No clean bool mapping (FSAA levels, needs restart): show
  610 |                     // the resource footprint display-only like sliders/lists.
  611 |                     add("setting-" + key, std::string{}, false);
  612 |             } else if (kind.find("SLIDER") != std::string::npos ||
  613 |                        kind.find("COMBOBOX") != std::string::npos) {
  614 |                 // The looks define no TextComponent: the original renders no
  615 |                 // value text here (drag/dropdown interaction stays open), so
  616 |                 // the box alone marks the control footprint. Headers from the
  617 |                 // layout name the rows.
  618 |                 add("setting-" + key, std::string{}, false);
  619 |             }
  620 |         }
  621 |         add("apply", "APPLY");
  622 |         add("decline-settings", "CANCEL");
  623 |         frame.notes.push_back(
  624 |             {"PORT: VIDEO CHANGES NEED A RESTART; SLIDERS, LISTS AND FSAA ARE DISPLAY-ONLY.", false});
```

