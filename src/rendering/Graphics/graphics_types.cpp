#include <tngin/rendering/graphics_types.h>


namespace TAL {
    Vector4f& Vector4f::Normalize() {
        float l = Length();

        assert (l != 0);

        x /= l;
        y /= l;
        z /= l;
        w /= l;

        return *this;
    }


    Vector3f Vector3f::Cross(const Vector3f& v) const {
        return Vector3f(
            y*v.z - z*v.y,
            z*v.x - x*v.z,
            x*v.y - y*v.x
        );
    }

    Vector3f& Vector3f::Normalize() {
        float l = Length();

        assert (l != 0);

        x /= l;
        y /= l;
        z /= l;

        return *this;
    }


    void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ) {
        m[0][0] = ScaleX; m[0][1] = 0.0f;  m[0][2] = 0.0f;   m[0][3] = 0.0f;
        m[1][0] = 0.0f;   m[1][1] = ScaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
        m[2][0] = 0.0f;   m[2][1] = 0.0f;  m[2][2] = ScaleZ; m[2][3] = 0.0f;
        m[3][0] = 0.0f;   m[3][1] = 0.0f;  m[3][2] = 0.0f;   m[3][3] = 1.0f;
    }

    void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ) {
        Matrix4f rx, ry, rz;

        const float x = ToRadian(RotateX);
        const float y = ToRadian(RotateY);
        const float z = ToRadian(RotateZ);

        rx.InitRotationX(x);

        ry.InitRotationY(y);

        rz.InitRotationZ(z);

        *this = rz * ry * rx;
    }

    void Matrix4f::InitRotationX(float x)
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f   ;  m[0][2] = 0.0f    ; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = cosf(x);  m[1][2] = sinf(x);  m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = -sinf(x); m[2][2] = cosf(x) ; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f   ;  m[3][2] = 0.0f    ; m[3][3] = 1.0f;
    }

    void Matrix4f::InitRotationY(float y)
    {
        m[0][0] = cosf(y); m[0][1] = 0.0f; m[0][2] = -sinf(y); m[0][3] = 0.0f;
        m[1][0] = 0.0f   ; m[1][1] = 1.0f; m[1][2] = 0.0f    ; m[1][3] = 0.0f;
        m[2][0] = sinf(y); m[2][1] = 0.0f; m[2][2] = cosf(y) ; m[2][3] = 0.0f;
        m[3][0] = 0.0f   ; m[3][1] = 0.0f; m[3][2] = 0.0f    ; m[3][3] = 1.0f;
    }

    void Matrix4f::InitRotationZ(float z)
    {
        m[0][0] = cosf(z);  m[0][1] = sinf(z);  m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = -sinf(z); m[1][1] = cosf(z) ; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f   ;  m[2][1] = 0.0f    ; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f   ;  m[3][1] = 0.0f    ; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void Matrix4f::InitTranslationTransform(float x, float y, float z) {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up) {
        Vector3f N = Target;
        N.Normalize();

        Vector3f U = Up;
        U.Normalize();

        U = U.Cross(N);
        Vector3f V = N.Cross(U);

        m[0][0] = U.x;           m[0][1] = U.y;           m[0][2] = U.z;           m[0][3] = 0.0f;
        m[1][0] = V.x;           m[1][1] = V.y;           m[1][2] = V.z;           m[1][3] = 0.0f;
        m[2][0] = N.x;           m[2][1] = N.y;           m[2][2] = N.z;           m[2][3] = 0.0f;
        m[3][0] = 0.0f;          m[3][1] = 0.0f;          m[3][2] = 0.0f;          m[3][3] = 1.0f;
    }

    void Matrix4f::InitCameraTransform(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up) {
        Matrix4f CameraTranslation;
        CameraTranslation.InitTranslationTransform(-Pos.x, -Pos.y, -Pos.z);

        Matrix4f CameraRotateTrans;
        CameraRotateTrans.InitCameraTransform(Target, Up);

        *this = CameraRotateTrans * CameraTranslation;
    }

    void Matrix4f::InitPersProjTransform(const PersProjInfo& p)
    {
        const float ar = p.ar;
        const float zRange = p.zNear - p.zFar;
        const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

        m[0][0] = 1.0f / (tanHalfFOV*ar); m[0][1] = 0.0f;              m[0][2] = 0.0f;                         m[0][3] = 0.0f;
        m[1][0] = 0.0f;                     m[1][1] = 1.0f / tanHalfFOV; m[1][2] = 0.0f;                         m[1][3] = 0.0f;
        m[2][0] = 0.0f;                     m[2][1] = 0.0f;              m[2][2] = (-p.zNear - p.zFar) / zRange; m[2][3] = 2.0f * p.zFar * p.zNear / zRange;
        m[3][0] = 0.0f;                     m[3][1] = 0.0f;              m[3][2] = 1.0f;                         m[3][3] = 0.0f;
    }

    void Matrix4f::InitOrthoProjTransform(const OrthoProjInfo& p) {
        float l = p.l;
        float r = p.r;
        float b = p.b;
        float t = p.t;
        float n = p.n;
        float f = p.f;

        m[0][0] = 2.0f / (r - l); m[0][1] = 0.0f;           m[0][2] = 0.0f;           m[0][3] = -(r + l) / (r - l);
        m[1][0] = 0.0f;           m[1][1] = 2.0f / (t - b); m[1][2] = 0.0f;           m[1][3] = -(t + b) / (t - b);
        m[2][0] = 0.0f;           m[2][1] = 0.0f;           m[2][2] = 2.0f / (f - n); m[2][3] = -(f + n) / (f - n);
        m[3][0] = 0.0f;           m[3][1] = 0.0f;           m[3][2] = 0.0f;           m[3][3] = 1.0f;
    }
}