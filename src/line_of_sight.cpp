#include "torchlight/collision_scene.hpp"

#include <algorithm>
#include <cmath>

namespace torchlight {
namespace {
using V = std::array<double, 3>;
V subtract(const V& a, const V& b) { return {a[0]-b[0], a[1]-b[1], a[2]-b[2]}; }
V cross(const V& a, const V& b) {
    return {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
}
double dot(const V& a, const V& b) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; }
bool valid(const std::array<float, 3>& a) {
    return std::all_of(a.begin(), a.end(), [](float x) { return std::isfinite(x); });
}
V convert(const std::array<float, 3>& a) { return {a[0],a[1],a[2]}; }
// Clip a coplanar segment to a triangle in the dominant two-dimensional plane.
// This includes grazing a wall; parallel rays outside the triangle remain clear.
bool coplanar_intersects(const V& a, const V& b, const V& c, const V& n,
                         const V& from, const V& to) {
    std::size_t k = 0;
    for (std::size_t i=1;i<3;++i) if (std::fabs(n[i]) > std::fabs(n[k])) k=i;
    const auto i=(k+1)%3, j=(k+2)%3;
    const auto side = [&](const V& p, const V& q, const V& r) {
        return (q[i]-p[i])*(r[j]-p[j])-(q[j]-p[j])*(r[i]-p[i]);
    };
    const double orientation = side(a,b,c) >= 0 ? 1 : -1;
    double lower = 1e-6, upper = 1-1e-6;
    const V vertices[]{a,b,c};
    for (std::size_t edge=0;edge<3;++edge) {
        const double start = orientation*side(vertices[edge],vertices[(edge+1)%3],from);
        const double end = orientation*side(vertices[edge],vertices[(edge+1)%3],to);
        const double change=end-start;
        if (std::fabs(change)<1e-12) { if (start < -1e-10) return false; }
        else {
            const double t=(-1e-10-start)/change;
            if (change>0) lower=std::max(lower,t); else upper=std::min(upper,t);
            if (upper<lower) return false;
        }
    }
    return lower<=upper;
}
} // namespace
bool collision_segment_clear(const CollisionScene& scene,
    const std::array<float,3>& from, const std::array<float,3>& to) noexcept {
    if (!valid(from) || !valid(to) || scene.missing_instances != 0) return false;
    const auto start=convert(from), end=convert(to), direction=subtract(end,start);
    if (dot(direction,direction)<1e-16) return true;
    for (const auto& triangle:scene.triangles) {
        if (!valid(triangle.vertices[0]) || !valid(triangle.vertices[1]) || !valid(triangle.vertices[2])) return false;
        const auto a=convert(triangle.vertices[0]), b=convert(triangle.vertices[1]), c=convert(triangle.vertices[2]);
        // Broad phase prevents both needless arithmetic and an accidental hit on
        // a parallel triangle elsewhere on the same wall plane.
        bool separated=false;
        for (std::size_t k=0;k<3;++k)
            if (std::max(start[k],end[k]) < std::min({a[k],b[k],c[k]})-1e-8 ||
                std::min(start[k],end[k]) > std::max({a[k],b[k],c[k]})+1e-8) separated=true;
        if (separated) continue;
        const auto e1=subtract(b,a), e2=subtract(c,a), normal=cross(e1,e2);
        const double normal_squared=dot(normal,normal);
        if (normal_squared<1e-20) continue;
        const auto p=cross(direction,e2);
        const double det=dot(e1,p);
        if (std::fabs(det)<1e-12) {
            const double plane=dot(subtract(start,a),normal);
            if (plane*plane <= 1e-16*normal_squared && coplanar_intersects(a,b,c,normal,start,end)) return false;
            continue;
        }
        const double inv=1/det;
        const auto offset=subtract(start,a);
        const double u=dot(offset,p)*inv;
        if (u < -1e-8 || u > 1+1e-8) continue;
        const auto q=cross(offset,e1);
        const double v=dot(direction,q)*inv;
        if (v < -1e-8 || u+v > 1+1e-8) continue;
        const double t=dot(e2,q)*inv;
        if (t > 1e-6 && t < 1-1e-6) return false;
    }
    return true;
}
} // namespace torchlight
