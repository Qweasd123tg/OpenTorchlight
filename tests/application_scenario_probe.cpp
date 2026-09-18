#include "torchlight/application.hpp"
#include "torchlight/application_keys.hpp"
#include "torchlight/checkpoint.hpp"
#include "torchlight/diagnostic_json.hpp"
#include "torchlight/skeletal_animation.hpp"
#include <GLES2/gl2.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_set>

namespace {
using namespace torchlight;
namespace key = torchlight::physical_key;
namespace json = torchlight::diagnostic;
struct Step { std::string verb; std::vector<std::string> args; unsigned visits = 0; };
std::string ascii(std::u16string_view text) {
    std::string out;
    for (const auto ch : text) {
        if (ch > 127) throw std::runtime_error("non-ASCII resource identifier in scenario");
        out.push_back(static_cast<char>(ch));
    }
    return out;
}
const char* page_name(FrontendPage page) {
    switch (page) {
    case FrontendPage::main: return "main"; case FrontendPage::create: return "create";
    case FrontendPage::load: return "load"; case FrontendPage::pause: return "pause";
    case FrontendPage::settings: return "settings";
    case FrontendPage::playing: return "playing"; case FrontendPage::quit: return "quit";
    }
    throw std::runtime_error("unknown frontend page");
}
std::uint32_t physical(std::string name) {
    if (name == "ESC") return key::ESC;
    if (name == "UP") return key::UP;
    if (name == "DOWN") return key::DOWN;
    if (name == "ENTER") return key::ENTER;
    if (name == "BACKSPACE") return key::BACKSPACE;
    if (name == "SPACE") return key::SPACE;
    if (name.size() != 1) throw std::runtime_error("unsupported physical key " + name);
    constexpr std::uint32_t letters[] = {key::A,key::B,key::C,key::D,key::E,key::F,key::G,key::H,
        key::I,key::J,key::K,key::L,key::M,key::N,key::O,key::P,key::Q,key::R,key::S,key::T,
        key::U,key::V,key::W,key::X,key::Y,key::Z};
    constexpr std::uint32_t digits[] = {key::DIGIT_0,key::DIGIT_1,key::DIGIT_2,key::DIGIT_3,
        key::DIGIT_4,key::DIGIT_5,key::DIGIT_6,key::DIGIT_7,key::DIGIT_8,key::DIGIT_9};
    const auto ch = name[0];
    if (ch >= 'a' && ch <= 'z') return letters[ch - 'a'];
    if (ch >= 'A' && ch <= 'Z') return letters[ch - 'A'];
    if (ch >= '0' && ch <= '9') return digits[ch - '0'];
    if (ch == '-') return key::MINUS;
    throw std::runtime_error("unsupported physical key " + name);
}
class ScenarioHost final : public ApplicationHost {
public:
    ScenarioHost(const std::filesystem::path& script, std::filesystem::path output)
        : output_(std::move(output)) {
        std::filesystem::create_directories(output_);
        events_.open(output_ / "events.jsonl"); rng_.open(output_ / "rng.jsonl");
        if (!events_ || !rng_) throw std::runtime_error("cannot create scenario reports");
        std::ifstream source(script);
        if (!source) throw std::runtime_error("cannot read scenario script");
        std::string line;
        while (std::getline(source, line)) {
            if (line.size() > 1024) throw std::runtime_error("scenario line too long");
            if (const auto hash = line.find('#'); hash != std::string::npos) line.resize(hash);
            std::istringstream fields(line); Step step;
            if (!(fields >> step.verb)) continue;
            std::string arg; while (fields >> arg) step.args.push_back(std::move(arg));
            const std::vector<std::pair<std::string,std::size_t>> counts = {
                {"menu",1},{"button",1},{"hud-button",1},{"name",1},{"level",2},{"frames",1},{"capture",1},
                {"walk",2},{"npc",1},{"select-skill",1},{"kill-nearest",0},{"trigger-nearest",0},{"still",0},{"key",1},{"inventory",1},{"unequip",1},{"equip",1},
                {"resize",2},{"dt",1},{"revision",1},{"quit",0},{"menu-capture",1},{"button-capture",2}};
            const auto spec = std::find_if(counts.begin(),counts.end(),[&](const auto& p){return p.first==step.verb;});
            if (spec == counts.end() || spec->second != step.args.size())
                throw std::runtime_error("invalid scenario command: " + line);
            if(step.verb=="inventory" && step.args[0]!="open" && step.args[0]!="closed")
                throw std::runtime_error("inventory expectation must be open or closed");
            steps_.push_back(std::move(step));
            if (steps_.size() > 1000) throw std::runtime_error("too many scenario commands");
        }
        if (steps_.empty()) throw std::runtime_error("empty scenario");
        notice("driver", "prototype_fixed_dt_1_over_60_not_original_scheduler");
    }
    bool process_events() override {
        ++ticks_;
        time_seconds_ += delta_seconds_;
        if (++step_wait_ > 1800 || ticks_ > 12000)
            throw std::runtime_error("scenario event timeout at " + step_text());
        if (cursor_ < steps_.size() && steps_[cursor_].verb == "quit") {
            done(); return false;
        }
        return true;
    }
    double clock_seconds() override { return time_seconds_; }
    std::uint32_t new_campaign_seed() override { return 491; }
    int width() const noexcept override { return width_; }
    int height() const noexcept override { return height_; }
    std::vector<std::uint32_t> take_key_presses() override { auto out = std::move(keys_); keys_.clear(); return out; }
    std::optional<std::array<int, 2>> take_left_click() override { auto out = click_; click_.reset(); return out; }
    std::optional<UiPointerClick> take_ui_click() override {
        auto result = ui_click_; ui_click_.reset(); return result;
    }
    UiPointerState ui_pointer_state() const noexcept override { return pointer_; }
    void draw_menu_frame(GlesUiRenderer& renderer, const FrontendFrame& frame) override {
        renderer.draw(frame, width_, height_); readback(); ++menu_frames_;
        if (!menu_capture_.empty()) { write_pixels(menu_capture_); menu_capture_.clear(); }
    }
    void draw_scene_frame(GlesSceneRenderer& renderer, GlesUiRenderer& ui_renderer,
                          const std::vector<InventoryViewLine>& lines, bool bag,
                          const UiHudFrame& hud) override {
        last_renderer_ = &renderer; last_ui_renderer_ = &ui_renderer;
        last_overlay_ = lines; last_bag_ = bag; last_hud_ = hud;
        renderer.draw(width_, height_);
        // Exact same HUD implementation as the Wayland adapter.
        ui_renderer.draw_hud(hud, width_, height_);
        ui_renderer.draw_overlay(lines, bag, width_, height_);
        readback(); ++scene_frames_;
    }
    void notice(std::string_view kind, std::string_view text) override {
        events_ << "{\"tick\":" << ticks_ << ",\"kind\":"; json::string(events_,kind);
        events_ << ",\"value\":"; json::string(events_,text); events_ << "}\n"; events_.flush();
        if (kind == "application_error" || kind == "runtime_error") failure_ = std::string(text);
    }
    bool release_hud_step(Step& step, FrontendPage page, bool bag_open, bool moving) {
        if (step.verb != "hud-button" || step.visits == 0) return false;
        if (moving) throw std::runtime_error("HUD press leaked into world movement");
        if (step.args[0] == "InventoryButton" && !bag_open)
            throw std::runtime_error("inventory did not open at MouseButtonDown");
        if (step.args[0] == "OptionsButton" && page != FrontendPage::pause)
            throw std::runtime_error("options did not open at MouseButtonDown");
        if (!pointer_.left_press_origin) throw std::runtime_error("lost HUD press state");
        // Deliberately release off the original target: original dispatch already happened.
        pointer_.position = std::array<float,2>{-10,-10};
        ui_click_ = UiPointerClick{*pointer_.left_press_origin, *pointer_.position};
        pointer_.left_press_origin.reset();
        notice("hud_release", step.args[0]);
        done();
        return true;
    }
    void observe_frontend(FrontendPage page, const FrontendFrame& frame, const std::string& name) override {
        if (!failure_.empty()) throw std::runtime_error(failure_);
        if (cursor_ == steps_.size()) return;
        auto& step = steps_[cursor_];
        if (release_hud_step(step, page, false, false)) return;
        if (step.verb == "menu") { if (step.args[0] == page_name(page)) done(); return; }
        if (step.verb == "button" || step.verb == "button-capture") {
            const auto it = std::find_if(frame.buttons.begin(), frame.buttons.end(),
                [&](const auto& b){return b.id == step.args[0];});
            if (it == frame.buttons.end() || !it->enabled)
                throw std::runtime_error("requested button absent or disabled: " + step.args[0]);
            click_ = {static_cast<int>(it->rect.x + it->rect.width * 0.5F),
                      static_cast<int>(it->rect.y + it->rect.height * 0.5F)};
            if (step.verb == "button-capture") menu_capture_ = label(step.args[1]);
            done(); return;
        }
        if (step.verb == "name" && page == FrontendPage::create) {
            keys_.insert(keys_.end(), name.size(), key::BACKSPACE);
            for (char ch : step.args[0]) keys_.push_back(physical(std::string(1,ch)));
            done(); return;
        }
        if (step.verb == "menu-capture") { menu_capture_ = label(step.args[0]); done(); return; }
        general(step);
    }
    void observe_game(const ApplicationView& view) override {
        if (!failure_.empty()) throw std::runtime_error(failure_);
        if (cursor_ == steps_.size()) return;
        auto& step = steps_[cursor_];
        if (std::string_view(view.phase) == "after_draw") {
            if (step.verb == "capture") { dump(label(step.args[0]), view); done(); }
            return;
        }
        if (release_hud_step(step, view.page, view.inventory_open, view.moving)) return;
        if (step.verb == "level") {
            if (ascii(view.address.dungeon_name) == step.args[0] && view.address.depth == std::stoi(step.args[1])) done();
        } else if (step.verb == "hud-button") {
            if (view.page != FrontendPage::playing || view.inventory_open)
                throw std::runtime_error("HUD input requires unobstructed gameplay");
            const auto it = std::find_if(last_hud_.buttons.begin(), last_hud_.buttons.end(),
                [&](const auto& button){ return button.name == step.args[0]; });
            if (it == last_hud_.buttons.end() || !it->enabled)
                throw std::runtime_error("requested HUD button absent or disabled: " + step.args[0]);
            const auto& rect = it->has_clip ? it->clip : it->rect;
            const std::array<float,2> point = {rect.x + rect.width/2, rect.y + rect.height/2};
            if (hud_button_at(last_hud_, point[0], point[1]) != &*it)
                throw std::runtime_error("requested HUD target is obstructed");
            pointer_.position = point;
            ++step.visits;
            click_ = {static_cast<int>(point[0]), static_cast<int>(point[1])};
            pointer_.left_press_origin = point;
            notice("hud_press", step.args[0]);
        } else if (step.verb == "frames") {
            if (++step.visits >= positive(step.args[0])) done();
        } else if (step.verb == "still") {
            if (!view.moving) done();
        } else if (step.verb == "revision") {
            if (view.revision == static_cast<std::uint64_t>(std::stoull(step.args[0]))) done();
        } else if (step.verb == "inventory") {
            if (view.inventory_open == (step.args[0] == "open")) done();
        } else if (step.verb == "walk") {
            if (view.level_frame == 0) return;
            auto destination = view.player_position;
            destination[0] += std::stof(step.args[0]); destination[2] += std::stof(step.args[1]);
            const auto cell = view.navigation->nearest_walkable(destination);
            if (!cell) throw std::runtime_error("scenario walk target has no walkable cell");
            destination = view.navigation->cell_center((*cell)[0], (*cell)[1]);
            if (view.navigation->find_path(view.player_position,destination).size() < 2)
                throw std::runtime_error("scenario walk target is unreachable");
            destination[1] += view.floor_offset;
            const auto pixel = view.renderer->pixel_position_of_world(destination);
            if (pixel[0] < 0 || pixel[1] < 0 || pixel[0] >= width_ || pixel[1] >= height_)
                throw std::runtime_error("walk target not visible to pointer input");
            click_ = {static_cast<int>(std::lround(pixel[0])),static_cast<int>(std::lround(pixel[1]))};
            notice("walk_pointer",std::to_string((*click_)[0])+","+std::to_string((*click_)[1]));
            done();
        } else if (step.verb == "select-skill") {
            if (!view.inventory_open) throw std::runtime_error("skill selection requires panel");
            const auto& skills=view.session->skills().skills;
            const auto found=std::find_if(skills.begin(),skills.end(),[&](const auto& skill){return ascii(skill.name)==step.args[0];});
            if (found==skills.end()) throw std::runtime_error("requested skill absent from class");
            keys_.insert(keys_.end(),skills.size(),key::UP);
            keys_.insert(keys_.end(),static_cast<std::size_t>(found-skills.begin()),key::DOWN);
            done();
        } else if (step.verb == "npc") {
            if (view.inventory_open) { done(); return; }
            if (view.moving || view.level_frame==0) return;
            const auto guid=std::stoll(step.args[0]);
            const RuntimeEntity* npc=nullptr;
            for (const auto& entity:view.world->entities()) if (entity.resource_guid==guid&&entity.alive&&entity.enabled&&entity.visible) {npc=&entity;break;}
            if (!npc) throw std::runtime_error("requested real NPC not present in scene");
            auto destination=npc->position;
            auto pixel=view.renderer->pixel_position_of_world(destination);
            if (pixel[0]<0||pixel[1]<0||pixel[0]>=width_||pixel[1]>=height_) {
                const auto path=view.navigation->find_path(view.player_position,destination);
                if(path.size()<2)throw std::runtime_error("NPC has no navigation route");
                destination=path[std::min<std::size_t>(4,path.size()-1)];destination[1]+=view.floor_offset;
                pixel=view.renderer->pixel_position_of_world(destination);
            }
            if(pixel[0]<0||pixel[1]<0||pixel[0]>=width_||pixel[1]>=height_)throw std::runtime_error("NPC approach waypoint offscreen");
            click_={static_cast<int>(std::lround(pixel[0])),static_cast<int>(std::lround(pixel[1]))};
            notice("npc_pointer",std::to_string(guid)+" at "+std::to_string((*click_)[0])+","+std::to_string((*click_)[1]));
        } else if (step.verb == "kill-nearest") {
            if (!view.session->health().alive()) throw std::runtime_error("player died in real-input combat scenario");
            if (view.level_frame==0) return;
            if (!combat_target_) {
                const auto* target=view.world->nearest_alive_monster(view.player_position,100);
                if (!target) throw std::runtime_error("populated floor has no ordinary target");
                combat_target_=target->id;
                notice("combat_target",std::to_string(*combat_target_));
            }
            const auto* target=view.world->find(*combat_target_);
            if (!target) throw std::runtime_error("combat target disappeared");
            if (!target->alive) {
                if (!target->player_kill) throw std::runtime_error("target died without player HIT");
                notice("combat_kill",std::to_string(*combat_target_));combat_target_.reset();done();return;
            }
            if (view.session->combat().target_id()==*combat_target_ || view.moving) return;
            auto destination=target->position;
            auto pixel=view.renderer->pixel_position_of_world(destination);
            if (pixel[0]<0 || pixel[1]<0 || pixel[0]>=width_ || pixel[1]>=height_) {
                const auto path=view.navigation->find_path(view.player_position,destination);
                if(path.size()<2)throw std::runtime_error("ordinary target has no navigation route");
                destination=path[std::min<std::size_t>(4,path.size()-1)];destination[1]+=view.floor_offset;
                pixel=view.renderer->pixel_position_of_world(destination);
            }
            if(pixel[0]<0 || pixel[1]<0 || pixel[0]>=width_ || pixel[1]>=height_)
                throw std::runtime_error("combat approach waypoint is not visible");
            click_={static_cast<int>(std::lround(pixel[0])),static_cast<int>(std::lround(pixel[1]))};
            notice("combat_pointer",std::to_string((*click_)[0])+","+std::to_string((*click_)[1]));
        } else if (step.verb == "trigger-nearest") {
            if (trigger_source_ && (trigger_source_->dungeon_name!=view.address.dungeon_name ||
                                    trigger_source_->depth!=view.address.depth)) {
                notice("trigger_transition","observed level change after real pointer interaction");
                trigger_source_.reset(); done(); return;
            }
            if (view.moving || view.level_frame==0) return;
            if (!trigger_source_) trigger_source_=view.address;
            const auto transforms=resolve_layout_world_transforms(*view.layout);
            std::optional<Vector3> destination;
            float distance=std::numeric_limits<float>::infinity();
            std::int64_t id=0;
            for(std::size_t i=0;i<view.layout->objects.size();++i) {
                const auto& object=view.layout->objects[i];
                const auto* state=view.logic->state(object.id);
                if(object.descriptor!=u"Unit Trigger" || !state || !state->enabled || !state->visible) continue;
                const auto& p=transforms[i].position;
                const auto d=std::hypot(p[0]-view.player_position[0],p[2]-view.player_position[2]);
                if(d<distance){distance=d;destination=p;id=object.id;}
            }
            if(!destination) throw std::runtime_error("no enabled Unit Trigger in loaded scene");
            if(distance>3.0F) {
                const auto path=view.navigation->find_path(view.player_position,*destination);
                if(path.size()<2)throw std::runtime_error("nearest trigger has no navigation route");
                *destination=path[std::min<std::size_t>(4,path.size()-1)];
                (*destination)[1]+=view.floor_offset;
            }
            const auto pixel=view.renderer->pixel_position_of_world(*destination);
            if(pixel[0]<0 || pixel[1]<0 || pixel[0]>=width_ || pixel[1]>=height_)
                throw std::runtime_error("trigger approach waypoint not visible for real pointer input");
            click_={static_cast<int>(std::lround(pixel[0])),static_cast<int>(std::lround(pixel[1]))};
            notice("trigger_pointer",std::to_string(id)+" at "+std::to_string((*click_)[0])+","+std::to_string((*click_)[1]));
            if(distance<=3.0F){trigger_source_.reset();done();}
        } else if (step.verb == "equip" || step.verb == "unequip") {
            if (!view.inventory_open) throw std::runtime_error("inventory command without opened UI");
            const auto& items = view.session->inventory().items();
            const auto found = std::find_if(items.begin(),items.end(),[&](const auto& item){
                const auto slot = PlayerInventory::slot_for(item);
                return slot && step.args[0] == inventory_slot_name(*slot);
            });
            if (found == items.end()) throw std::runtime_error("no item for slot " + step.args[0]);
            keys_.insert(keys_.end(), items.size(), key::UP);
            keys_.insert(keys_.end(), static_cast<std::size_t>(found-items.begin()), key::DOWN);
            keys_.push_back(step.verb == "equip" ? key::ENTER : key::U); done();
        } else general(step);
    }
    void finish(int result) {
        if (result || !failure_.empty() || cursor_ != steps_.size())
            throw std::runtime_error("application scenario incomplete at " + step_text() + ": " + failure_);
        if (trace_failed_ || !rng_ || !events_) throw std::runtime_error("failed scenario trace write");
        std::ofstream out(output_ / "result.json");
        out << "{\"status\":\"PASSED\",\"evidence\":\"port-regression-not-original\",\"commands\":" << cursor_
            << ",\"ticks\":" << ticks_ << ",\"scene_frames\":" << scene_frames_
            << ",\"menu_frames\":" << menu_frames_ << ",\"rng_calls\":" << rng_sequence_ << "}\n";
        if (!out) throw std::runtime_error("failed result write");
    }
    static void random_event(const RandomObservation& e, void* context) noexcept {
        auto& self = *static_cast<ScenarioHost*>(context);
        try {
            auto& out = self.rng_; out << "{\"sequence\":" << self.rng_sequence_++
                << ",\"tick\":" << self.ticks_ << ",\"kind\":" << static_cast<int>(e.kind)
                << ",\"before\":" << e.before << ",\"after\":" << e.after;
            if (e.kind == RandomObservation::Kind::integer)
                out << ",\"low\":" << e.integer_low << ",\"high\":" << e.integer_high << ",\"result\":" << e.integer_result;
            else if (e.kind == RandomObservation::Kind::real) {
                out << ",\"low\":"; json::number(out,e.real_low);
                out << ",\"high\":"; json::number(out,e.real_high);
                out << ",\"result\":"; json::number(out,e.real_result);
            }
            out << "}\n";
        } catch (...) { self.trace_failed_ = true; }
    }
private:
    static unsigned positive(const std::string& value) {
        std::size_t used=0; const auto n = std::stoul(value,&used);
        if (used!=value.size() || n == 0 || n > 12000) throw std::runtime_error("scenario count outside limit");
        return static_cast<unsigned>(n);
    }
    std::string label(const std::string& value) {
        if (value.empty() || value.size() > 64 || !std::all_of(value.begin(),value.end(),[](char c){
            return (c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_';}) || !labels_.insert(value).second)
            throw std::runtime_error("invalid or repeated capture label");
        return value;
    }
    void general(const Step& step) {
        if (step.verb == "key") { keys_.push_back(physical(step.args[0])); done(); }
        else if (step.verb == "dt") {
            std::size_t used=0; const auto value=std::stod(step.args[0],&used);
            if(used!=step.args[0].size() || !std::isfinite(value) || value<0 || value>0.1)
                throw std::runtime_error("scenario dt must be finite in [0,0.1]");
            delta_seconds_=value;done();
        }
        else if (step.verb == "resize") {
            width_ = static_cast<int>(positive(step.args[0])); height_ = static_cast<int>(positive(step.args[1]));
            if (width_ > 1024 || height_ > 768) throw std::runtime_error("scenario exceeds pbuffer capacity");
            done();
        }
    }
    std::string step_text() const { return cursor_ < steps_.size() ? std::to_string(cursor_)+":"+steps_[cursor_].verb : "end"; }
    void done() { notice("command",step_text()); ++cursor_; step_wait_ = 0; }
    void readback() {
        pixels_.resize(static_cast<std::size_t>(width_)*height_*4);
        glFinish(); glReadPixels(0,0,width_,height_,GL_RGBA,GL_UNSIGNED_BYTE,pixels_.data());
        if (glGetError()!=GL_NO_ERROR) throw std::runtime_error("scenario GLES readback failed");
    }
    void write_pixels(const std::string& name) {
        std::ofstream out(output_/(name+".rgba"),std::ios::binary);
        out.write(reinterpret_cast<const char*>(pixels_.data()), static_cast<std::streamsize>(pixels_.size()));
        if (!out) throw std::runtime_error("cannot write RGBA capture");
        std::ofstream meta(output_/(name+".image.json"));
        meta<<"{\"format\":\"RGBA8\",\"origin\":\"bottom-left\",\"viewport\":["<<width_<<','<<height_<<"]}\n";
        if(!meta)throw std::runtime_error("cannot write image metadata");
    }
    std::size_t visibility_mask(const std::string& name, const ApplicationView& v) {
        if (last_renderer_ != v.renderer) throw std::runtime_error("stale render diagnostic context");
        const auto original_pixels = pixels_;
        const bool player_visible = last_renderer_->instance_visible(v.player_instance);
        const bool weapon_visible = v.weapon_instance && last_renderer_->instance_visible(*v.weapon_instance);
        const auto redraw = [&] {
            last_renderer_->draw(width_,height_);
            if (last_ui_renderer_) {
                last_ui_renderer_->draw_hud(last_hud_,width_,height_);
                last_ui_renderer_->draw_overlay(last_overlay_,last_bag_,width_,height_);
            } else
                draw_inventory_overlay(last_overlay_,last_bag_,width_,height_);
            readback();
        };
        last_renderer_->set_instance_visible(v.player_instance,false);
        if (v.weapon_instance) last_renderer_->set_instance_visible(*v.weapon_instance,false);
        try { redraw(); }
        catch (...) {
            last_renderer_->set_instance_visible(v.player_instance,player_visible);
            if (v.weapon_instance) last_renderer_->set_instance_visible(*v.weapon_instance,weapon_visible);
            throw;
        }
        std::vector<unsigned char> mask(pixels_.size()/4);
        std::size_t count=0;
        for(std::size_t i=0;i<mask.size();++i) {
            mask[i]=!std::equal(pixels_.begin()+i*4,pixels_.begin()+i*4+4,original_pixels.begin()+i*4);
            count+=mask[i];
        }
        last_renderer_->set_instance_visible(v.player_instance,player_visible);
        if (v.weapon_instance) last_renderer_->set_instance_visible(*v.weapon_instance,weapon_visible);
        redraw();
        if(pixels_!=original_pixels) throw std::runtime_error("diagnostic draw did not restore the identical framebuffer");
        std::ofstream out(output_/(name+".actor-mask.bin"),std::ios::binary);
        out.write(reinterpret_cast<const char*>(mask.data()),static_cast<std::streamsize>(mask.size()));
        if(!out)throw std::runtime_error("cannot write actor contribution mask");
        return count;
    }
    void dump(const std::string& name, const ApplicationView& v) {
        if (trace_failed_) throw std::runtime_error("RNG trace dropped an event");
        write_pixels(name);
        const auto mask_pixels = visibility_mask(name, v);
        std::ofstream render(output_/(name+".render.json")); v.renderer->write_diagnostics(render); render << '\n';
        std::ofstream out(output_/(name+".state.json"));
        const auto player = CheckpointAccess::capture(*v.session);
        const auto world = CheckpointAccess::capture(*v.world);
        const auto logic = CheckpointAccess::capture(*v.logic);
        const auto enemy = CheckpointAccess::capture(*v.enemies);
        out << "{\"schema\":1,\"evidence\":\"port-regression-not-original\",\"viewport\":["<<width_<<','<<height_
            <<"],\"actor_visible_pixels\":"<<mask_pixels<<",\"frame\":"<<v.frame<<",\"class_guid\":"<<v.class_guid<<",\"seed\":"<<v.seed<<",\"revision\":"<<v.revision
            <<",\"name\":"; json::string(out,v.character_name);
        out << ",\"dungeon\":"; json::string(out,ascii(v.address.dungeon_name));
        out << ",\"depth\":"<<v.address.depth<<",\"position\":"; json::array(out,v.player_position);
        out << ",\"angle\":"; json::number(out,v.player_angle);
        out << ",\"recovery_anchor\":"; json::array(out,v.recovery_anchor);
        out << ",\"walkable\":"<<(checkpoint_position_walkable(*v.navigation,v.player_position,v.floor_offset)?"true":"false")
            << ",\"gold\":"<<player.gold<<",\"hp\":"; json::number(out,player.health);
        out << ",\"max_hp\":"; json::number(out,player.maximum_health);
        out << ",\"mana\":"; if(player.mana) json::number(out,*player.mana); else out<<"null";
        out << ",\"max_mana\":"; if(player.maximum_mana) json::number(out,*player.maximum_mana); else out<<"null";
        out << ",\"progression\":";
        if (player.progression) {
            const auto& p = *player.progression;
            out << "{\"level\":" << p.level << ",\"experience\":" << p.experience
                << ",\"stat_points\":" << p.stat_points << ",\"skill_points\":" << p.skill_points
                << ",\"allocated\":[";
            for (std::size_t i=0; i<p.allocated.size(); ++i) { if(i) out << ','; out << p.allocated[i]; }
            out << "]}";
        } else out << "null";
        out << ",\"damage\":["<<v.session->combat().minimum_damage()<<','<<v.session->combat().maximum_damage()
            <<"],\"armor\":"<<v.session->health().armor_class()<<",\"inventory\":[";
        bool comma=false;
        for (const auto& item : player.inventory.items) {
            if (comma) out << ',';
            comma = true;
            out<<"{\"id\":"<<item.id<<",\"guid\":"<<item.resource_guid<<",\"name\":";json::string(out,ascii(item.name));
            if(item.weapon) out<<",\"damage\":["<<item.weapon->minimum_damage<<','<<item.weapon->maximum_damage
                <<"],\"speed\":"<<item.weapon->prototype.speed;
            if(item.armor) out<<",\"armor\":"<<item.armor->armor;
            if(item.weapon) out<<",\"delivery\":"<<static_cast<unsigned>(item.weapon->prototype.delivery);
            if(item.consumable) out<<",\"stack\":"<<item.consumable->count<<",\"uses\":"<<item.consumable->uses;
            out<<'}';
        }
        out << "],\"active_recovery\":[";comma=false;
        for(const auto& active:player.active_recovery){
            if(comma)out<<',';
            comma=true;
            out<<"{\"name\":";json::string(out,ascii(active.effect.name));
            out<<",\"type\":"<<active.effect.type<<",\"remaining\":";json::number(out,active.remaining);
            out<<",\"value\":";json::number(out,active.effect.value);out<<'}';
        }
        out<<"],\"skills\":[";comma=false;
        if(player.skills)for(const auto& skill:player.skills->skills) {
            if(comma)out<<',';
            comma=true;
            out<<"{\"name\":";json::string(out,ascii(skill.name));out<<",\"rank\":"<<skill.invested<<",\"cooldown\":";json::number(out,skill.cooldown);out<<'}';
        }
        out<<"],\"skill_effects\":[";comma=false;
        if(player.skills)for(const auto& effect:player.skills->effects) {
            if(comma)out<<',';
            comma=true;
            out<<"{\"name\":";json::string(out,ascii(effect.name));out<<",\"type\":"<<effect.type<<",\"remaining\":";json::number(out,effect.remaining);out<<",\"value\":";json::number(out,effect.value);out<<'}';
        }
        out<<"],\"quests\":[";comma=false;
        if(v.quests)for(const auto& q:v.quests->flags) {
            if(comma)out<<',';
            comma=true;
            out<<"{\"name\":";json::string(out,ascii(q.name));out<<",\"active\":"<<(q.active?"true":"false")<<",\"complete\":"<<(q.complete?"true":"false")<<",\"dialog\":"<<(q.accept_dialog?"true":"false")<<'}';
        }
        out<<"],\"completed_quests\":"<<(v.quests?v.quests->completed_count:0);
        out<<",\"population_generated\":"<<(world.population_generated?"true":"false");
        out << ",\"slots\":[";
        for(std::size_t i=0;i<player.inventory.slots.size();++i){if(i)out<<',';out<<player.inventory.slots[i];}
        out<<"],\"rng\":{\"combat\":"<<player.combat_random<<",\"world\":"<<world.random_state
           <<",\"logic\":"<<logic.random_state<<",\"ai\":"<<enemy.random_state<<"},\"entities\":[";
        comma=false;
        for(const auto& entity:world.entities){
            if (comma) out << ',';
            comma = true;
            out<<"{\"id\":"<<entity.id<<",\"hp\":";json::number(out,entity.health);
            out<<",\"alive\":"<<(entity.alive?"true":"false")<<",\"enabled\":"<<(entity.enabled?"true":"false")
               <<",\"visible\":"<<(entity.visible?"true":"false")<<",\"position\":";json::array(out,entity.position);
            out << ",\"gold_amount\":"; if(entity.gold_amount) out << *entity.gold_amount; else out << "null";
            out << ",\"experience_reward\":"; if(entity.experience_reward) out << *entity.experience_reward; else out << "null";
            out << ",\"player_kill\":" << (entity.player_kill?"true":"false")
                << ",\"reward_claimed\":" << (entity.reward_claimed?"true":"false") << '}';
        }
        out << "],\"logic\":[";comma=false;
        for(const auto& node:logic.entries){
            if (comma) out << ',';
            comma = true;
            out<<"{\"id\":"<<node.id<<",\"counter\":"<<node.state.counter
               <<",\"enabled\":"<<(node.state.enabled?"true":"false")
               <<",\"timer\":";json::number(out,node.state.timer_remaining);
            out<<",\"loops\":"<<node.state.timer_loops_remaining<<",\"spawned\":"<<node.state.active_spawned_units<<'}';
        }
        out << "],\"player_instance\":"<<v.player_instance<<",\"weapon_instance\":";
        if(v.weapon_instance)out<<*v.weapon_instance;else out<<"null";
        out<<",\"bones\":[";comma=false;
        if(v.player_pose)for(const auto& bone:v.player_pose->bones){
            if (comma) out << ',';
            comma = true;
            out<<"{\"handle\":"<<bone.handle<<",\"name\":";json::string(out,bone.name);
            out<<",\"position\":";json::array(out,bone.position);
            out<<",\"rotation\":";json::array(out,bone.orientation);
            out<<",\"scale\":";json::array(out,bone.scale);out<<'}';
        }
        out<<"]}\n";
        if(!out||!render)throw std::runtime_error("diagnostic write failed");
        notice("capture",name);
    }
    std::filesystem::path output_;
    std::vector<Step> steps_;
    std::size_t cursor_=0;
    unsigned ticks_=0,step_wait_=0,scene_frames_=0,menu_frames_=0;
    double time_seconds_=0.0, delta_seconds_=1.0/60.0;
    // resource-derived: mainmenuframe.layout anchors its buttons at
    // {{.5,-507}..{.5,251},{1,-64}} for a 1024-wide design (NewGame reaches
    // x=0 only at W>=1014; CEGUI resolves the same offscreen in the original
    // below that). The harness therefore meets the layout design minimum
    // instead of testing below the original's supported modes.
    int width_=1024,height_=768;
    std::optional<DungeonAddress> trigger_source_;
    std::optional<std::uint64_t> combat_target_;
    std::optional<std::array<int,2>> click_;
    std::optional<UiPointerClick> ui_click_;
    UiPointerState pointer_;
    std::vector<std::uint32_t> keys_;
    std::vector<unsigned char> pixels_;
    GlesSceneRenderer* last_renderer_ = nullptr;
    GlesUiRenderer* last_ui_renderer_ = nullptr;
    std::vector<InventoryViewLine> last_overlay_;
    UiHudFrame last_hud_;
    bool last_bag_ = false;
    std::ofstream events_,rng_;
    std::unordered_set<std::string> labels_;
    std::uint64_t rng_sequence_=0;
    bool trace_failed_=false;
    std::string failure_,menu_capture_;
};
}
extern "C" int run_application_scenario(const char* game, const char* saves, const char* script,
                                        const char* output, char* error, unsigned error_size) {
    try {
        if(!game||!saves||!script||!output)throw std::runtime_error("null scenario path");
        ScenarioHost host(script,output);
        RandomObservationScope observation(&ScenarioHost::random_event,&host);
        ApplicationOptions options;options.game_directory=game;options.save_directory=saves;
        // Hermetic tests must never apply settings to the user's home directory.
        options.settings_directory=std::filesystem::path(output)/"settings";
        host.finish(run_application(options,host));
        return 0;
    } catch(const std::exception& e) {
        if(error&&error_size){std::strncpy(error,e.what(),error_size-1);error[error_size-1]=0;}
        return 1;
    }
}
