// Extract metadata with the project's existing OGRE skeleton parser; no assets copied.
#include "torchlight/ogre_skeleton.hpp"
#include "torchlight/pak_archive.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
int main(int argc,char** argv){
 try {
  if(argc!=2) throw std::runtime_error("usage: probe_inventory_assets original_pak.zip");
  PakArchive pak(argv[1]); std::cout<<std::setprecision(9);
  for(const auto* file:{"inventory.SKELETON","open.SKELETON","idle.SKELETON","close.SKELETON"}){
   const auto path=std::string("media/UI/models/inventory/")+file;
   const auto skeleton=parse_ogre_skeleton(pak.read_normalized(path));
   std::cout<<"file\t"<<path<<"\tserializer\t"<<skeleton.serializer_version<<"\tbones\t"<<skeleton.bones.size()<<'\n';
   for(const auto& b:skeleton.bones) if(b.name=="tag_topinventory" || b.name=="tag_bottominventory")
    std::cout<<"anchor\t"<<b.name<<"\thandle\t"<<b.handle<<"\tposition\t"<<b.position[0]<<'\t'<<b.position[1]<<'\t'<<b.position[2]<<'\n';
   for(const auto& a:skeleton.animations)
    std::cout<<"animation\t"<<a.name<<"\tlength_seconds\t"<<a.length<<"\ttracks\t"<<a.tracks.size()<<'\n';
  }
  return 0;
 } catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
