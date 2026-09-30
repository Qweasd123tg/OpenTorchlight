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
# Prefer an installed SDK; Fedora may have the runtime without its headers.
find_package(EXPAT QUIET)
if(NOT EXPAT_FOUND)
    find_library(CEGUI062_EXPAT_LIBRARY NAMES expat libexpat.so.1 REQUIRED)
    add_library(cegui062_expat_runtime UNKNOWN IMPORTED)
    set_target_properties(cegui062_expat_runtime PROPERTIES
        IMPORTED_LOCATION "${CEGUI062_EXPAT_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/../third_party/expat-2.8.3-headers")
    set(_cegui062_expat_target cegui062_expat_runtime)
else()
    set(_cegui062_expat_target EXPAT::EXPAT)
endif()

# Static System refers to createParser/destroyParser even when a parser is
# supplied. Use the same original 0.6.2 Expat module for all XML resources.
add_library(cegui062_base STATIC
    ${_cegui062_core_sources}
    "${_cegui062_root}/XMLParserModules/expatParser/CEGUIExpatParser.cpp"
    "${_cegui062_root}/XMLParserModules/expatParser/CEGUIExpatParserModule.cpp")
add_library(CEGUI062::Base ALIAS cegui062_base)
set_target_properties(cegui062_base PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(cegui062_base SYSTEM PUBLIC
    "${_cegui062_root}/include"
    "${_cegui062_root}/XMLParserModules/expatParser")
target_compile_definitions(cegui062_base PUBLIC
    CEGUI_STATIC
    CEGUI_WITH_EXPAT
    CEGUI_FALAGARD_RENDERER
    CEGUI_DEFAULT_XMLPARSER=ExpatParser)
target_compile_features(cegui062_base PUBLIC cxx_std_11)
target_link_libraries(cegui062_base PUBLIC
    Freetype::Freetype
    ${_cegui062_expat_target}
    PkgConfig::CEGUI062_PCRE
    ${CMAKE_DL_LIBS})

file(GLOB _cegui062_falagard_sources CONFIGURE_DEPENDS
    "${_cegui062_root}/WindowRendererSets/Falagard/src/*.cpp")
add_library(cegui062_falagard STATIC ${_cegui062_falagard_sources})
add_library(CEGUI062::Falagard ALIAS cegui062_falagard)
set_target_properties(cegui062_falagard PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(cegui062_falagard SYSTEM PUBLIC
    "${_cegui062_root}/WindowRendererSets/Falagard/include")
target_compile_features(cegui062_falagard PUBLIC cxx_std_11)
target_link_libraries(cegui062_falagard PUBLIC cegui062_base)
