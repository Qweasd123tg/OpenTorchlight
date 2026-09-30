# CEGUI Mk-2 0.6.2 (upstream tag v0-6-2), vendored without its renderers.
# Include this module from the parent project after project() has enabled C++.
set(_cegui062_root "${CMAKE_CURRENT_LIST_DIR}/../third_party/cegui-0.6.2")

find_package(Freetype REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CEGUI062_PCRE REQUIRED IMPORTED_TARGET libpcre)

file(GLOB _cegui062_core_sources CONFIGURE_DEPENDS
    "${_cegui062_root}/src/*.cpp"
    "${_cegui062_root}/src/elements/*.cpp"
    "${_cegui062_root}/src/falagard/*.cpp")
file(GLOB _cegui062_tinyxml_sources CONFIGURE_DEPENDS
    "${_cegui062_root}/XMLParserModules/TinyXMLParser/*.cpp"
    "${_cegui062_root}/XMLParserModules/TinyXMLParser/ceguitinyxml/*.cpp")

# CEGUI's static System refers to createParser/destroyParser even when a parser
# is supplied by the caller, so the complete bundled TinyXML parser belongs in
# the same archive as the core. This also avoids a circular static link order.
add_library(cegui062_base STATIC
    ${_cegui062_core_sources}
    ${_cegui062_tinyxml_sources})
add_library(CEGUI062::Base ALIAS cegui062_base)
target_include_directories(cegui062_base SYSTEM PUBLIC
    "${_cegui062_root}/include"
    "${_cegui062_root}/XMLParserModules/TinyXMLParser")
target_compile_definitions(cegui062_base PUBLIC
    CEGUI_STATIC
    CEGUI_WITH_TINYXML
    CEGUI_FALAGARD_RENDERER
    CEGUI_DEFAULT_XMLPARSER=TinyXMLParser
    CEGUI_TINYXML_H="ceguitinyxml/tinyxml.h"
    CEGUI_TINYXML_NAMESPACE=CEGUITinyXML)
target_compile_features(cegui062_base PUBLIC cxx_std_11)
target_link_libraries(cegui062_base PUBLIC
    Freetype::Freetype
    PkgConfig::CEGUI062_PCRE
    ${CMAKE_DL_LIBS})

file(GLOB _cegui062_falagard_sources CONFIGURE_DEPENDS
    "${_cegui062_root}/WindowRendererSets/Falagard/src/*.cpp")
add_library(cegui062_falagard STATIC ${_cegui062_falagard_sources})
add_library(CEGUI062::Falagard ALIAS cegui062_falagard)
target_include_directories(cegui062_falagard SYSTEM PUBLIC
    "${_cegui062_root}/WindowRendererSets/Falagard/include")
target_compile_features(cegui062_falagard PUBLIC cxx_std_11)
target_link_libraries(cegui062_falagard PUBLIC cegui062_base)
