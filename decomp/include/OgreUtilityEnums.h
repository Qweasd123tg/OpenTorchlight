#ifndef OGREUTILITYENUMS_H
#define OGREUTILITYENUMS_H
namespace OGRE_UTILITIES {
    // Enumerator names are ours; values follow gPRIMITIVE_NAMES.
    enum EQUERYMASK { QUERY_MASK_DEFAULT = 1 };

    enum EPRIMITIVES
    {
        PRIMITIVE_SPHERE,
        PRIMITIVE_BOX,
        PRIMITIVE_PLANE,
        PRIMITIVE_CYLINDER,
        PRIMITIVE_CONE,
        PRIMITIVE_ARROW,
        PRIMITIVE_COUNT
    };

}
#endif
