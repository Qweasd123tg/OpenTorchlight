# 07-placeholder-panels-and-hud

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/inventory_view.cpp:26–71`

SHA256 полного файла: `958443f4982dacc02ec3341affd961598b191ce37630e904de69ef2e5a330e66`

```text
   26 | std::vector<InventoryViewLine> InventoryView::lines(const PlayerSession& session,
   27 |                                                  std::size_t visible_items) const {
   28 |     const auto& inventory = session.inventory();
   29 |     std::vector<InventoryViewLine> result;
   30 |     std::ostringstream stats;
   31 |     stats << "HP " << std::fixed << std::setprecision(0) << session.health().health()
   32 |           << '/' << session.health().maximum_health() << "  ARMOR "
   33 |           << session.health().armor_class() << "  DAMAGE " << session.combat().minimum_damage()
   34 |           << '-' << session.combat().maximum_damage() << "  ITEMS " << inventory.items().size();
   35 |     stats << "  GOLD " << session.gold();
   36 |     if (session.health().mana()) stats << "  MANA " << *session.health().mana()
   37 |         << '/' << *session.health().maximum_mana();
   38 |     else stats << "  MANA ?";
   39 |     result.push_back({stats.str(), false});
   40 |     const auto& progress = session.progression();
   41 |     std::ostringstream xp;
   42 |     xp << "LEVEL " << progress.level << "  XP ";
   43 |     if (const auto* rules = session.progression_rules()) {
   44 |         xp << progress.experience << '/' << rules->gate(progress.level)
   45 |            << "  STAT POINTS " << progress.stat_points << "  SKILL POINTS " << progress.skill_points;
   46 |         if (progress.level == rules->maximum_level()) xp << "  MAX LEVEL";
   47 |     } else xp << "? - PROGRESSION GRAPHS UNAVAILABLE";
   48 |     result.push_back({xp.str(), false});
   49 |     result.push_back({"INVENTORY - PAUSED", false});
   50 |     if (session.progression_rules()) {
   51 |         const auto a = session.attributes();
   52 |         result.push_back({"1 STR " + std::to_string(a[0]) + " | 2 DEX " + std::to_string(a[1]) +
   53 |             " | 3 MAGIC " + std::to_string(a[2]) + " | 4 DEF " + std::to_string(a[3]) +
   54 |             " - SPEND ONE STAT POINT", false});
   55 |         result.push_back({"SKILL POINTS RETAINED; ACTIVE SKILLS / MAGIC COMBAT NOT IMPLEMENTED.", false});
   56 |     }
   57 |     result.push_back({"UP/DOWN SELECT | ENTER EQUIP/USE | U UNEQUIP | I/ESC CLOSE", false});
   58 |     if (inventory.items().empty()) result.push_back({"BAG IS EMPTY. PICK UP EQUIPMENT IN THE WORLD.", false});
   59 |     const auto selected = inventory.items().empty() ? 0 : std::min(selected_, inventory.items().size() - 1);
   60 |     visible_items = std::max<std::size_t>(1, visible_items);
   61 |     const auto first = selected >= visible_items ? selected - visible_items + 1 : 0;
   62 |     for (auto i = first; i < inventory.items().size() && i - first < visible_items; ++i) {
   63 |         const auto& item = inventory.items()[i];
   64 |         const auto slot = inventory.equipped_slot(item.id);
   65 |         const auto supported_slot = PlayerInventory::slot_for(item);
   66 |         std::ostringstream row;
   67 |         row << (i == selected ? "> " : "  ") << '#' << item.id << ' '
   68 |             << (slot ? "[ON] " : "[BAG] ") << display_name(item).substr(0, 28) << "  "
   69 |             << (supported_slot ? inventory_slot_name(*supported_slot) : (item.consumable && item.consumable->unavailable_reason.empty() ? "POTION" : "VIEW ONLY"));
   70 |         if (item.consumable) row << " x" << item.consumable->count;
   71 |         result.push_back({row.str(), i == selected});
```

## `src/application.cpp:1689–1773`

SHA256 полного файла: `76f54e35350880bc0452d038db73d6ef06f474447594b30bcc5bb8125d7a3143`

```text
 1689 |                 auto overlay = inventory_view.lines(session,
 1690 |                     static_cast<std::size_t>(std::max(1, window.height() / (window.width() >= 950 ? 22 : 11) - 10)));
 1691 |                 if (inventory_view.open && skill_panel) {
 1692 |                     overlay.resize(2);
 1693 |                     overlay.push_back({"PORT SKILLS | POINTS " + std::to_string(session.progression().skill_points) + " | UP/DOWN SELECT | ENTER INVEST | F CAST", true});
 1694 |                     const auto& skills = session.skills().skills;
 1695 |                     const auto visible = static_cast<std::size_t>(std::max(1, window.height() / (window.width() >= 950 ? 22 : 11) - 9));
 1696 |                     const auto first = selected_skill >= visible ? selected_skill - visible + 1 : 0;
 1697 |                     for (auto i = first; i < skills.size() && i < first + visible; ++i) {
 1698 |                         const auto* def = skills_catalog ? skills_catalog->find(skills[i].name) : nullptr;
 1699 |                         const auto* rank = def ? def->rank(std::max(1, skills[i].invested)) : nullptr;
 1700 |                         std::string text = narrow_ascii(def ? def->display_name : skills[i].name) + " [" + std::to_string(skills[i].invested) + "]";
 1701 |                         if (rank) text += " MANA " + std::to_string(rank->mana_cost) + (rank->self_buff ? "" : " | NOT IMPLEMENTED");
 1702 |                         overlay.push_back({std::move(text), i == selected_skill});
 1703 |                     }
 1704 |                     overlay.push_back({inventory_view.status, false});
 1705 |                 }
 1706 |                 if (inventory_view.open && quest_panel) {
 1707 |                     overlay.resize(2);
 1708 |                     overlay.push_back({"PORT JOURNAL | SCRIPT FLAGS | COMPLETED " + std::to_string(campaign.quests.completed_count), true});
 1709 |                     const auto visible = static_cast<std::size_t>(std::max(1, window.height() / (window.width() >= 950 ? 22 : 11) - 9));
 1710 |                     const auto first = selected_quest >= visible ? selected_quest - visible + 1 : 0;
 1711 |                     for (auto i = first; i < campaign.quests.flags.size() && i < first + visible; ++i) {
 1712 |                         const auto& state = campaign.quests.flags[i];
 1713 |                         const auto* def = quest_catalog.find(state.name);
 1714 |                         const auto text = narrow_ascii(def ? def->display_name : state.name);
 1715 |                         overlay.push_back({(state.complete ? "[COMPLETE] " : state.active ? "[ACTIVE] " : "[INACTIVE] ") + text, i == selected_quest});
 1716 |                     }
 1717 |                     overlay.push_back({"OBJECTIVES, REWARDS, NPC DIALOG AND FULL CAMPAIGN REMAIN INCOMPLETE.", false});
 1718 |                 }
 1719 |                 if (inventory_view.open && merchant_entity) {
 1720 |                     overlay.resize(2);
 1721 |                     const auto* npc = entity_world.find(merchant_entity);
 1722 |                     const auto* merchant = npc ? merchant_catalog.find(npc->resource_guid) : nullptr;
 1723 |                     overlay.push_back({merchant ? narrow_ascii(merchant->name) : "MERCHANT UNAVAILABLE", true});
 1724 |                     overlay.push_back({"PORT SHOP | UP/DOWN SELECT | ENTER BUY ONE | ESC CLOSE", false});
 1725 |                     if (merchant) {
 1726 |                         const auto offers = merchant_catalog.offers(merchant->guid, session.progression().level);
 1727 |                         for (std::size_t i = 0; i < offers.size(); ++i) {
 1728 |                             const auto* offer = offers[i];
 1729 |                             const auto price = torchlight::equipment_buy_price(offer->prices, 1, true, session.barter_percent());
 1730 |                             overlay.push_back({narrow_ascii(offer->item.display_name) + " | " + std::to_string(price) + " GOLD", i == selected_offer});
 1731 |                         }
 1732 |                     }
 1733 |                     overlay.push_back({inventory_view.status, false});
 1734 |                 }
 1735 |                 if (!inventory_view.open) {
 1736 |                     overlay.resize(2);
 1737 |                     overlay.push_back({inventory_view.status.empty()
 1738 |                         ? "I INVENTORY | K SKILLS / F CAST | J JOURNAL | Q/E POTIONS | ESC PAUSE / SAVE"
 1739 |                         : inventory_view.status, false});
 1740 |                 }
 1741 |                 if (!player_combat.alive()) {
 1742 |                     overlay.resize(2);
 1743 |                     overlay.push_back({"PLAYER DIED - SIMULATION PAUSED", false});
 1744 |                     overlay.push_back({session.hardcore() ? "HARDCORE: RECOVERY DISABLED. ESC FOR MENU." :
 1745 |                         "R: RECOVER AT LEVEL ENTRY | ESC: PAUSE / SAVE", true});
 1746 |                     if (!session.hardcore()) overlay.push_back({"COST " + std::to_string(session.gold() / 10) +
 1747 |                         " GOLD. INVENTORY AND FLOOR ARE RETAINED.", false});
 1748 |                 }
 1749 |                 // PORT diagnostics are opt-in. Keep the still-unrecovered
 1750 |                 // interactive panels and recovery prompt usable; do not turn
 1751 |                 // their removal into a claim of an original UI replacement.
 1752 |                 if (!inventory_view.open && player_combat.alive() && !options.debug_ui)
 1753 |                     overlay.clear();
 1754 |                 torchlight::UiHudValues hud_values;
 1755 |                 const auto& vitals = session.health();
 1756 |                 if (vitals.maximum_health() > 0)
 1757 |                     hud_values.health_fraction = vitals.health() / vitals.maximum_health();
 1758 |                 if (vitals.maximum_mana() && *vitals.maximum_mana() > 0 && vitals.mana())
 1759 |                     hud_values.mana_fraction = *vitals.mana() / *vitals.maximum_mana();
 1760 |                 hud_values.level_name = narrow_ascii(level.address.dungeon_name);
 1761 |                 if (const auto* rules = session.progression_rules()) {
 1762 |                     const auto current_level = session.progression().level;
 1763 |                     const auto gate = rules->gate(current_level);
 1764 |                     if (current_level == rules->maximum_level())
 1765 |                         hud_values.experience_fraction = 1.0F;
 1766 |                     else if (gate > 0)
 1767 |                         hud_values.experience_fraction =
 1768 |                             static_cast<float>(session.progression().experience) / gate;
 1769 |                 }
 1770 |                 const auto hud = ui_hud.frame(window.width(), window.height(), hud_values,
 1771 |                                               window.ui_pointer_state());
 1772 |                 window.draw_scene_frame(*renderer, ui_renderer, overlay,
 1773 |                                         inventory_view.open || !player_combat.alive(), hud);
```

## `src/ui_hud.cpp:30–99`

SHA256 полного файла: `7565ef8b750e88b0c672bde1c5f315e31643bcbebb22abddb993cfeed9e8a765`

```text
   30 | } // namespace
   31 | const UiResolvedWidget *hud_button_at(const UiHudFrame &frame, float x, float y) {
   32 |     for (auto it = frame.buttons.rbegin(); it != frame.buttons.rend(); ++it)
   33 |         if (it->visible && it->rect.contains(x, y) &&
   34 |             (!it->has_clip || it->clip.contains(x, y))) return &*it;
   35 |     return nullptr;
   36 | }
   37 | std::optional<std::string> hud_press_callback(const UiHudFrame &frame, float x, float y) {
   38 |     const auto *pressed = hud_button_at(frame, x, y);
   39 |     if (!pressed || !pressed->enabled || pressed->callback.empty())
   40 |         return std::nullopt;
   41 |     return pressed->callback;
   42 | }
   43 | UiHudFrame UiHud::frame(int width, int height, const UiHudValues &values,
   44 |                         const UiPointerState &pointer) const {
   45 |     UiHudFrame result;
   46 |     if (width <= 0 || height <= 0)
   47 |         return result;
   48 |     const auto *layout = resources_->layout("media/UI/bottomhud.layout");
   49 |     if (layout == nullptr)
   50 |         return result;
   51 |     const bool target_present = values.target_health_fraction.has_value();
   52 |     for (const auto &widget : layout->resolve(width, height)) {
   53 |         if (!widget.visible)
   54 |             continue;
   55 |         const auto name = leaf_upper(widget.name);
   56 |         if (name.rfind("TARGET", 0) == 0 && !target_present)
   57 |             continue;
   58 |         if (name == "PLAYERHEALTHBARSUB")
   59 |             result.bars.push_back({widget, clamp_fraction_low(values.health_fraction), true, true});
   60 |         else if (name == "PLAYERMANABARSUB")
   61 |             result.bars.push_back({widget, clamp_fraction_low(values.mana_fraction), true, true});
   62 |         else if (name == "EXPERIENCEBARSUB")
   63 |             result.bars.push_back({widget, clamp_fraction_low(values.experience_fraction), false, false});
   64 |         else if (name == "TARGETHEALTHBARSUB" && target_present)
   65 |             result.bars.push_back(
   66 |                 {widget, clamp_fraction_low(*values.target_health_fraction), false, false});
   67 |         else if (!widget.callback.empty())
   68 |             // resource-derived: several bottomhud ImageButtons intentionally
   69 |             // have NormalImage="". The callback/hit rectangle still exists.
   70 |             result.buttons.push_back(widget);
   71 |         else if (!widget.image.empty())
   72 |             result.images.push_back(widget);
   73 |         else if (name == "LEVELNAME" && !values.level_name.empty()) {
   74 |             auto text_widget = widget;
   75 |             text_widget.text = values.level_name;
   76 |             result.texts.push_back(std::move(text_widget));
   77 |         } else if (!widget.text.empty() && widget.text != "1" && hotkey_label(name))
   78 |             result.texts.push_back(widget);
   79 |     }
   80 |     const auto *hover = pointer.position ? hud_button_at(result, (*pointer.position)[0],
   81 |                                                          (*pointer.position)[1]) : nullptr;
   82 |     const auto *pressed = pointer.left_press_origin
   83 |         ? hud_button_at(result, (*pointer.left_press_origin)[0], (*pointer.left_press_origin)[1])
   84 |         : nullptr;
   85 |     for (auto &button : result.buttons) {
   86 |         // Bounded original ImageButton look only. RadioButton selection,
   87 |         // script-updated visibility and other widget types remain separate.
   88 |         if (upper(button.type) != "GUILOOK/IMAGEBUTTON") continue;
   89 |         const char *property = !button.enabled ? "DisabledImage"
   90 |             : &button == pressed ? (&button == hover ? "PushedImage" : "HoverImage")
   91 |             : &button == hover ? "HoverImage" : "NormalImage";
   92 |         // GuiLook/ImageButton StateImagery PushedOff references section hover.
   93 |         const auto value = button.properties.find(property);
   94 |         button.image = value != button.properties.end() ? value->second
   95 |             : resources_->look_default(button.type, property);
   96 |     }
   97 |     return result;
   98 | }
   99 | } // namespace torchlight
```

