#ifndef PARTICLETECHWRAPPERDESCRIPTORNAMES_H
#define PARTICLETECHWRAPPERDESCRIPTORNAMES_H

#include <string>

static const std::wstring gPARTICLE_MATERIAL_TYPES[] =
{
    L"Alpha",
    L"Normal",
    L"Additive",
    L"Modulate",
};

static const std::wstring gPARTICLE_BILLBOARD_ORIGIN_POSITIONS[] =
{
    L"Top Left",
    L"Top Center",
    L"Top Right",
    L"Center Left",
    L"Center",
    L"Center Right",
    L"Bottom Left",
    L"Bottom Center",
    L"Bottom Right",
};

static const std::wstring gPARTICLE_BILLBOARD_ROTATION_TYPES[] =
{
    L"Geometry",
    L"Texture",
};

static const std::wstring gPARTICLE_RENDER_TYPE_NAMES[] =
{
    L"Billboard",
    L"Billboard Up",
    L"Billboard Forward",
    L"Billboard Up Camera",
    L"Billboard Forward Camera",
    L"Billboard Self",
    L"Billboard Common",
    L"Billboard Shape",
    L"Box",
    L"Sphere",
    L"Entity",
    L"EntityWorld",
    L"RibbonTrail",
};

#endif
