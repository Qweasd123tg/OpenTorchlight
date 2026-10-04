#ifndef GAMENAMESPACES_H
#define GAMENAMESPACES_H

// Free functions of game namespaces by symbol, promoted from the generated headers as
// recovered code needs them; return types from Ghidra until a TU defines them.

#include "TArrayList.h"
#include <Ogre.h>
#include <OgreMesh.h>
#include <OgreQuaternion.h>
#include <OgreSubMesh.h>
#include <OgreVector3.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

namespace LinuxUtils
{
    void Init();
}

namespace ShellUtils
{
    void LaunchBrowser(const std::string&);
    void LaunchProgram(const std::string&, const std::vector<std::string, std::allocator<std::string > >&);
}

#endif
