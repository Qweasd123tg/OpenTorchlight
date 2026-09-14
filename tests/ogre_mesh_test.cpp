#include "torchlight/ogre_mesh.hpp"
#include "torchlight/pak_archive.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool ends_with_mesh(const std::string& path) {
    if (path.size() < 5) {
        return false;
    }
    std::string suffix = path.substr(path.size() - 5);
    for (auto& character : suffix) {
        if (character >= 'A' && character <= 'Z') {
            character = static_cast<char>(character - 'A' + 'a');
        }
    }
    return suffix == ".mesh";
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: ogre_mesh_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        std::size_t mesh_files = 0;
        std::size_t submeshes = 0;
        std::uint64_t vertices = 0;
        std::uint64_t indices = 0;
        std::size_t skeletal_meshes = 0;
        std::size_t meshes_without_bounds = 0;
        std::size_t geometries = 0;
        std::size_t textured_geometries = 0;
        std::size_t normal_geometries = 0;
        std::size_t colored_geometries = 0;
        std::uint64_t colored_vertices = 0;
        std::size_t bone_assignments = 0;
        for (const auto& entry : archive.entries()) {
            if (!ends_with_mesh(entry.name)) {
                continue;
            }
            torchlight::OgreMesh mesh;
            try {
                mesh = torchlight::parse_ogre_mesh(archive.read(entry));
            } catch (const std::exception& error) {
                throw std::runtime_error(entry.name + ": " + error.what());
            }
            require(mesh.serializer_version == "[MeshSerializer_v1.40]",
                    "mesh has the wrong serializer version");
            meshes_without_bounds += static_cast<std::size_t>(!mesh.bounds.has_value());
            ++mesh_files;
            submeshes += mesh.submeshes.size();
            skeletal_meshes += static_cast<std::size_t>(mesh.skeletally_animated);
            bone_assignments += mesh.shared_bone_assignments.size();
            if (mesh.shared_geometry.has_value()) {
                vertices += mesh.shared_geometry->vertex_count;
                ++geometries;
                textured_geometries +=
                    static_cast<std::size_t>(!mesh.shared_geometry->texcoords.empty());
                normal_geometries +=
                    static_cast<std::size_t>(!mesh.shared_geometry->normals.empty());
                colored_geometries +=
                    static_cast<std::size_t>(!mesh.shared_geometry->colors.empty());
                colored_vertices += mesh.shared_geometry->colors.size();
            }
            for (const auto& submesh : mesh.submeshes) {
                indices += submesh.indices.size();
                bone_assignments += submesh.bone_assignments.size();
                if (submesh.geometry.has_value()) {
                    vertices += submesh.geometry->vertex_count;
                    ++geometries;
                    textured_geometries +=
                        static_cast<std::size_t>(!submesh.geometry->texcoords.empty());
                    normal_geometries +=
                        static_cast<std::size_t>(!submesh.geometry->normals.empty());
                    colored_geometries +=
                        static_cast<std::size_t>(!submesh.geometry->colors.empty());
                    colored_vertices += submesh.geometry->colors.size();
                }
            }
        }
        require(mesh_files == 3312, "unexpected OGRE mesh file count");
        require(submeshes == 5105, "unexpected OGRE submesh count");
        require(vertices == 1939624, "unexpected OGRE vertex count");
        require(indices == 2461269, "unexpected OGRE index count");
        require(skeletal_meshes == 223, "unexpected skeletal mesh count");
        require(meshes_without_bounds == 0, "OGRE mesh has no bounds");
        require(geometries == 3528, "unexpected OGRE geometry count");
        require(textured_geometries == geometries,
                "OGRE geometry has no primary texture coordinates");
        require(normal_geometries == geometries,
                "OGRE geometry has no primary vertex normals");
        require(colored_geometries == 360 && colored_vertices == 591528,
                "unexpected original vertex-color coverage");
        require(bone_assignments == 477008, "unexpected vertex bone-assignment count");
        std::cout << "PASS: parsed 3312 OGRE v1.40 meshes, 1939624 vertices, "
                     "2461269 indices, 5105 submeshes and "
                  << bone_assignments << " bone assignments\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
