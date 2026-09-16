#include "torchlight/adm_document.hpp"
#include "torchlight/animation_manifest.hpp"
#include "torchlight/dds_texture.hpp"
#include "torchlight/diagnostic_json.hpp"
#include "torchlight/level_scene.hpp"
#include "torchlight/ogre_material.hpp"
#include "torchlight/ogre_mesh.hpp"
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/player.hpp"
#include "torchlight/png_texture.hpp"
#include "torchlight/scene_animation.hpp"
#include "torchlight/ui_layout.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

namespace {
using namespace torchlight;
namespace json = torchlight::diagnostic;
std::string ascii(std::u16string_view value) {
    std::string s;
    for (const auto c : value) {
        if (c > 127) throw std::runtime_error("non-ASCII path identifier");
        s.push_back(static_cast<char>(c));
    }
    return s;
}
std::string normalized(std::string value) {
    for (auto& c : value) {
        if (c == '\\') c = '/';
        else if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
    }
    return value;
}
bool ends(const std::string& path, const std::string& suffix) {
    return path.size() >= suffix.size() && path.compare(path.size()-suffix.size(), suffix.size(), suffix)==0;
}
std::string sibling(const std::string& path, const std::string& file) {
    const auto slash = path.find_last_of("/\\");
    return normalized((slash==std::string::npos ? "" : path.substr(0, slash+1)) + file);
}
struct Node {
    std::string status = "unsupported", capability = "indexed-only", detail;
    std::uint64_t bytes=0, crc=0;
};
struct Edge { std::string from, to, relation; };
class Catalog {
public:
    explicit Catalog(const std::filesystem::path& path) : archive_(path), materials_(archive_), definitions_(archive_) {}
    void collect() {
        for (const auto& e : archive_.entries()) {
            if (e.is_directory()) continue;
            auto& node=nodes_[normalized(e.name)]; node.bytes=e.uncompressed_size;node.crc=e.crc32;
        }
        for (const auto& material : materials_.materials()) {
            const auto id="material:"+material.name;
            nodes_[id] = {"supported","parsed-material-subset-not-full-OGRE", "",0,0};
            edge(id,material.source_path,"defined-in");
            if (!material.base_material.empty()) edge(id,"material:"+material.base_material,"inherits-material",false);
            for (const auto& texture : material.textures) {
                const auto* resolved = resolve_material_texture(archive_,material,texture);
                edge(id,resolved ? resolved->name : texture,"resolved-texture");
            }
        }
        for (const auto& entry : archive_.entries()) {
            if (entry.is_directory()) continue;
            const auto path=normalized(entry.name);
            auto& node=nodes_.at(path);
            try {
                if (ends(path,".adm")) {
                    const auto doc=parse_adm(archive_.read(entry));
                    adm_edges(path,doc.root);
                    support(node,"ADM-syntax; runtime-property-coverage-not-claimed");
                } else if (ends(path,".mesh")) {
                    const auto mesh=parse_ogre_mesh(archive_.read(entry));
                    if (!mesh.skeleton_file.empty()) edge(path,sibling(path,mesh.skeleton_file),"bind-skeleton");
                    for (const auto& sub : mesh.submeshes) edge(path,"material:"+sub.material,"submesh-material",false);
                    if (!mesh.skeleton_file.empty()) {
                        // Use the production manifest selector, not a basename heuristic.
                        for (auto kind : {SceneAnimationKind::idle,SceneAnimationKind::run,SceneAnimationKind::attack}) {
                            const auto clip=load_model_animation(archive_,path,mesh.skeleton_file,kind);
                            if (clip) {
                                edge(path,clip->manifest_path,"selected-animation-manifest");
                                edge(path,clip->skeleton_path,"selected-animation-clip");
                            }
                        }
                    }
                    support(node,"mesh-decoded; selected-idle/run/attack-dependencies");
                } else if (ends(path,".skeleton")) {
                    const auto skeleton=parse_ogre_skeleton(archive_.read(entry));
                    for (const auto& link:skeleton.animation_links) edge(path,sibling(path,link.skeleton_file),"animation-link");
                    support(node,"skeleton-and-tracks-parsed");
                } else if (ends(path,".animation")) {
                    const auto manifest=parse_animation_manifest(archive_.read(entry));
                    for (const auto& clip:manifest.clips) {
                        edge(path,sibling(path,clip.file),"animation-clip");
                        for (const auto& k:clip.keys) {
                            if (k.layout) {
                                auto target=normalized(*k.layout);if (!ends(target,".adm")) target+=".adm";
                                edge(path,target,"animation-event-layout");
                            }
                        }
                    }
                    support(node,"manifest-and-events-parsed; all-event-execution-not-claimed");
                } else if (ends(path,".dds")) {
                    static_cast<void>(decode_dds(archive_.read(entry)));support(node,"full-image-and-mips-decoded");
                } else if (ends(path,".png")) {
                    static_cast<void>(decode_png(archive_.read(entry)));support(node,"image-decoded");
                } else if (ends(path,".material")) {
                    const auto bytes=archive_.read(entry);
                    static_cast<void>(parse_ogre_material_script(std::string(bytes.begin(),bytes.end()),entry.name));
                    support(node,"material-subset-parsed; shader/technique-coverage-not-claimed");
                } else if (ends(path,".layout") && path.rfind("media/ui/",0)==0) {
                    const auto layout=UiLayout::parse(archive_.read(entry));
                    UiResources ui(archive_);
                    for (const auto& w:layout.resolve(1024,768)) {
                        if (!w.image.empty()) {
                            const auto image=ui.image(w.image);
                            if (image) edge(path,image->texture_path,"UI-imageset-texture");
                            else {
                                const auto id="unresolved-ui-image:"+w.image;
                                nodes_[id]={"unsupported","imageset-reference-unresolved","not replaced silently",0,0};
                                edge(path,id,"UI-image",false);
                            }
                        }
                    }
                    support(node,"bounded-CEGUI-XML-subset; full-skin-behavior-not-claimed");
                }
            } catch (const std::exception& e) {
                // A decoder rejection is not proof that shipped data is corrupt.
                node.status="unsupported";node.detail=e.what();node.capability="decoder-rejected; corruption-unproven";
                if (std::string(e.what()).find("ZIP CRC mismatch")!=std::string::npos) {
                    node.status="corrupt";node.capability="CRC-integrity-failed";
                }
                ++rejections_;
            }
        }
        const MasterResourceIndex master(parse_adm(archive_.read_normalized("media/masterresourceunits.dat.adm")));
        for (const auto& resource:master.records()) {
            const auto id="unit:"+std::to_string(resource.guid);
            nodes_[id]={"supported","inherited-UNIT-loaded; full-gameplay-semantics-not-claimed","",0,0};
            edge(id,resource.compiled_adm_path(),"UNIT-file");
            try {
                const auto definition=definitions_.load(resource);
                for (const auto& file:definition->inheritance_chain) edge(id,file,"BASEFILE-chain");
                const auto* dir=definition->find_property(u"RESOURCEDIRECTORY");
                const auto* mesh=definition->find_property(u"MESHFILE");
                if (dir && mesh && std::holds_alternative<std::u16string>(dir->value) && std::holds_alternative<std::u16string>(mesh->value)) {
                    auto path=normalized(ascii(std::get<std::u16string>(dir->value)));
                    if (!path.empty() && path.back()!='/') path+='/';
                    path+=normalized(ascii(std::get<std::u16string>(mesh->value)));
                    if (!ends(path,".mesh")) path+=".mesh";
                    edge(id,path,"UNIT-model");
                }
                adm_edges(id,definition->root);
            } catch (const std::exception& e) {
                nodes_[id].status="unsupported";nodes_[id].detail=e.what();++rejections_;
            }
        }
        LevelsetCatalog levelsets(archive_);
        for (const auto& piece:levelsets.pieces()) {
            const auto id="piece:"+std::to_string(piece.guid);
            nodes_[id]={"supported","levelset-record","",0,0};
            if (!piece.mesh_file.empty()) edge(id,ascii(piece.mesh_file),"render-mesh");
            if (!piece.collision_file.empty()) edge(id,ascii(piece.collision_file),"collision-mesh");
        }
        // No guessing for omitted runtime families: keep them first-class nodes.
        nodes_["runtime:full-effects"]={"unsupported","runtime","only fixed unconditional passives implemented",0,0};
        nodes_["runtime:timeline"]={"unsupported","runtime","property/event timeline not executed",0,0};
        nodes_["runtime:full-CEGUI"]={"unsupported","runtime","port UI subset and prototype skins",0,0};
        for (const auto& e:edges_) {
            if (!nodes_.count(e.to)) nodes_[e.to]={"missing","unresolved-dependency","no matching resource; no fallback applied",0,0};
        }
    }
    void write(std::ostream& out) const {
        std::map<std::string,std::size_t> counts;
        for(const auto& pair:nodes_)++counts[pair.second.status];
        out<<"{\"schema\":1,\"evidence\":\"resource-derived-not-original-execution\","
              "\"supported_meaning\":\"listed parser capability only, never full game fidelity\","
              "\"corrupt_meaning\":\"reserved for independently established integrity failure; parser rejection is unsupported\","
              "\"decoder_rejections\":"<<rejections_<<",\"counts\":{";
        bool comma=false;
        for(const auto& [name,n]:counts){if(comma)out<<',';comma=true;json::string(out,name);out<<':'<<n;}
        out<<"},\"nodes\":[";comma=false;
        for(const auto& [id,n]:nodes_){
            if(comma)out<<',';
            comma=true;
            out<<"{\"id\":";json::string(out,id);out<<",\"status\":";json::string(out,n.status);
            out<<",\"capability\":";json::string(out,n.capability);out<<",\"detail\":";json::string(out,n.detail);
            out<<",\"bytes\":"<<n.bytes<<",\"crc32\":"<<n.crc<<'}';
        }
        out<<"],\"edges\":[";comma=false;
        for(const auto& e:edges_){
            if(comma)out<<',';
            comma=true;
            out<<"{\"from\":";json::string(out,e.from);out<<",\"to\":";json::string(out,e.to);
            out<<",\"relation\":";json::string(out,e.relation);out<<",\"target_status\":";json::string(out,nodes_.at(e.to).status);out<<'}';
        }
        out<<"]}\n";
    }
private:
    static void support(Node& n,const char* capability){n.status="supported";n.capability=capability;}
    void edge(const std::string& from,std::string to,const std::string& relation,bool file=true){
        if(file) to=normalized(to);
        if(to.empty())return;
        const auto key=from+'\n'+to+'\n'+relation;
        if(edge_set_.insert(key).second)edges_.push_back({from,std::move(to),relation});
    }
    void adm_edges(const std::string& source,const AdmGroup& group){
        if(group.name==u"TIMELINEDATA")edge(source,"runtime:timeline","requires-runtime",false);
        if(group.name==u"EFFECT" || group.name==u"EFFECTS")edge(source,"runtime:full-effects","requires-runtime",false);
        for(const auto& p:group.properties){
            if(p.name==u"GUID" && std::holds_alternative<std::int64_t>(p.value) && group.name==u"PROPERTIES") {
                const auto* descriptor=group.find_property(u"DESCRIPTOR");
                if(descriptor && std::holds_alternative<std::u16string>(descriptor->value) &&
                   std::get<std::u16string>(descriptor->value)==u"Room Piece")
                    edge(source,"piece:"+std::to_string(std::get<std::int64_t>(p.value)),"Room-Piece-GUID",false);
                continue;
            }
            if(!std::holds_alternative<std::u16string>(p.value))continue;
            const auto& v=std::get<std::u16string>(p.value);
            if(v.empty())continue;
            if(p.name==u"PARENT_DUNGEON")edge(source,"media/dungeons/"+ascii(v)+".dat.adm","parent-dungeon");
            else if(p.name==u"BASEFILE")edge(source,compiled_adm_path(v),"BASEFILE");
            else if(p.name==u"LAYOUT FILE" || p.name==u"LAYOUTFILE") {
                auto path=normalized(ascii(v));
                if(path.find('/')==std::string::npos && !ends(path,".layout") && !ends(path,".adm")) {
                    const auto id="symbolic-layout:"+path;
                    nodes_[id]={"unsupported","symbolic-reference","context-specific resolution is not asserted",0,0};
                    edge(source,id,"layout-symbol",false);
                } else {
                    if(!ends(path,".adm"))path+=".adm";
                    edge(source,path,"layout-link");
                }
            } else if(p.name==u"RULESET") {
                const auto path=normalized(ascii(v));
                if(path.find('/')==std::string::npos && !ends(path,".dat") && !ends(path,".adm")) {
                    const auto id="symbolic-ruleset:"+path;
                    nodes_[id]={"unsupported","symbolic-reference","not misreported as a missing file",0,0};
                    edge(source,id,"ruleset-symbol",false);
                } else edge(source,compiled_adm_path(v),"ruleset");
            }
        }
        for(const auto& child:group.groups)adm_edges(source,child);
    }
    PakArchive archive_;
    OgreMaterialCatalog materials_;
    UnitDefinitionLoader definitions_;
    std::map<std::string,Node> nodes_;
    std::vector<Edge> edges_;
    std::set<std::string> edge_set_;
    std::size_t rejections_=0;
};
}
int main(int argc,char** argv){
    try{
        if(argc!=3)throw std::runtime_error("usage: torchlight_asset_catalog pak.zip new-output.json");
        const std::filesystem::path input(argv[1]),output(argv[2]);
        if(std::filesystem::exists(output))throw std::runtime_error("output already exists; never overwrite source or previous evidence");
        Catalog catalog(input);catalog.collect();
        std::ofstream out(output);catalog.write(out);
        if(!out)throw std::runtime_error("catalog write failed");
        std::cout<<"Resource catalog generated; inspect unsupported/missing nodes; not a fidelity certificate\n";
        return 0;
    }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
