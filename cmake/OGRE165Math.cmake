# Exact OGRE 1.6.5 Quaternion translation unit, with its Linux header closure.
# Hidden section GC keeps only the math actually called by the adapter; the
# unused Quaternion APIs depend on Ogre::Math and are outside this subset.
set(_ogre165_root "${CMAKE_CURRENT_LIST_DIR}/../third_party/ogre-1.6.5-math")
if(NOT UNIX OR APPLE OR NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(FATAL_ERROR "The pinned OGRE math subset currently supports Linux GNU/Clang builds")
endif()
add_library(ogre165_math STATIC "${_ogre165_root}/OgreMain/src/OgreQuaternion.cpp")
add_library(OGRE165::Math ALIAS ogre165_math)
set_target_properties(ogre165_math PROPERTIES
    CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES
    POSITION_INDEPENDENT_CODE ON CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)
target_include_directories(ogre165_math SYSTEM PUBLIC "${_ogre165_root}/OgreMain/include")
target_compile_definitions(ogre165_math PUBLIC OGRE_STATIC_LIB OGRE_MEMORY_ALLOCATOR=1)
target_compile_options(ogre165_math PRIVATE -ffunction-sections -fdata-sections -ffp-contract=off)
target_link_options(ogre165_math INTERFACE "LINKER:--gc-sections")
