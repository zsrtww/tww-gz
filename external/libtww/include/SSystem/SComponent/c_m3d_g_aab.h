#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "c_xyz.h"
#include "c_m3d_g_lin.h"
#include "../../defines.h"
#include "../../m_Do/m_Do_printf.h"

class cM3dGAab;
class cM3dGCyl;
class cM3dGSph;

LIBTWW_DEFINE_FUNC(cM3d_Cross_MinMaxBoxLine__FPC3VecPC3VecPC3VecPC3Vec,
                  bool, cM3d_Cross_MinMaxBoxLine, (const Vec*, const Vec*, const Vec*, const Vec*))

LIBTWW_DEFINE_FUNC(cM3d_Cross_AabAab__FPC8cM3dGAabPC8cM3dGAab,
                  bool, cM3d_Cross_AabAab, (const cM3dGAab*, const cM3dGAab*))

LIBTWW_DEFINE_FUNC(cM3d_Cross_AabCyl__FPC8cM3dGAabPC8cM3dGCyl,
                  bool, cM3d_Cross_AabCyl, (const cM3dGAab*, const cM3dGCyl*))

LIBTWW_DEFINE_FUNC(cM3d_Cross_AabSph__FPC8cM3dGAabPC8cM3dGSph,
                  bool, cM3d_Cross_AabSph, (const cM3dGAab*, const cM3dGSph*))

// Axis aligned bounding box
class cM3dGAab {
private:
public:
    /* 0x00 */ cXyz mMin;
    /* 0x0C */ cXyz mMax;
    /* 0x18 */ void* vtable;

    const cXyz* GetMaxP() const { return &mMax; }
    const cXyz* GetMinP() const { return &mMin; }
    const f32 GetMaxX() const { return mMax.x; }
    const f32 GetMaxY() const { return mMax.y; }
    const f32 GetMaxZ() const { return mMax.z; }
    const f32 GetMinX() const { return mMin.x; }
    const f32 GetMinY() const { return mMin.y; }
    const f32 GetMinZ() const { return mMin.z; }

    bool Cross(const cM3dGLin *param_1) {
        return cM3d_Cross_MinMaxBoxLine(GetMinP(), GetMaxP(), (Vec*)param_1->GetStartP(), (Vec*)param_1->GetEndP());
    }
    bool Cross(const cM3dGAab *param_1) {
        return cM3d_Cross_AabAab(this, param_1);
    }
    bool Cross(const cM3dGCyl *param_1) {
        return cM3d_Cross_AabCyl(this, param_1);
    }
    bool Cross(const cM3dGSph *param_1) {
        return cM3d_Cross_AabSph(this, param_1);
    }
};  // Size = 0x1C

static_assert(0x1C == sizeof(cM3dGAab));

#endif /* C_M3D_G_AAB_H */
