# OGRE 1.6.5 math subset

Unmodified OgreQuaternion.cpp and the Linux headers it includes, copied from
ogre-v1-6-5.tar.bz2. Archive and per-file SHA-256: source-inputs.json.
COPYING contains LGPL 2.1 and the original OGRE linking/header exceptions.

Production consumer: src/menu_scene.cpp; build: cmake/OGRE165Math.cmake.
Float Real, static/PIC, STD allocator, thread support0, C++11 for the stock
translation unit; the caller uses C++17. Hidden function/data sections and
linker GC discard unused APIs that require the rest of Ogre::Math. Stock source
has no edits. This is a Linux GNU/Clang math dependency, not the full OGRE SDK.
Shipped-library/source correspondence and limitations: research/menu-player-preview.md.
