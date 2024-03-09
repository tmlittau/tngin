#pragma once

#include "graphics_utils.h"

namespace TAL {
    #define powi(base,exp) (int)powf((float)(base), (float)(exp))

    #define ToRadian(x) (float)(((x) * M_PI / 180.0f))
    #define ToDegree(x) (float)(((x) * 180.0f / M_PI))

    float RandomFloat();
    float RandomFloatRange(float Start, float End);
    
    struct Vector2i
    {
        int x;
        int y;
    };

    struct Vector3i
    {
        union {
            float x;
            float r;
        };

        union {
            float y;
            float g;
        };

        union {
            float z;
            float b;
        };
    };
    
    struct Vector2f
    {
        union {
            float x;
            float u;
        };

        union {
            float y;
            float v;
        };

        Vector2f()
        {
        }

        Vector2f(float _x, float _y)
        {
            x = _x;
            y = _y;
        }

        void Print(bool endl = true) const
        {
            printf("(%f, %f)", x, y);

            if (endl) {
                printf("\n");
            }
        }

        float Length() const
        {
            float len = sqrtf(x * x + y * y);
            return len;
        }


        void Normalize()
        {
            float len = Length();

            assert(len != 0);

            x /= len;
            y /= len;
        }
    };

    inline Vector2f operator*(const Vector2f& l, float f)
    {
        Vector2f Ret(l.x * f, l.y * f);

        return Ret;
    }

    struct Vector4f;

    struct Vector3f 
    {
        union {
            float x;
            float r;
        };

        union {
            float y;
            float g;
        };

        union {
            float z;
            float b;
        };

        Vector3f() {}

        Vector3f(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        Vector3f(const float* pFloat)
        {
            x = pFloat[0];
            y = pFloat[1];
            z = pFloat[2];
        }


        void InitBySphericalCoords(float Radius, float Pitch, float Heading)
        {
            x = Radius * cosf(ToRadian(Pitch)) * sinf(ToRadian(Heading));
            y = -Radius * sinf(ToRadian(Pitch));
            z = Radius * cosf(ToRadian(Pitch)) * cosf(ToRadian(Heading));
        }

        Vector3f(float f)
        {
            x = y = z = f;
        }

        Vector3f(const Vector4f& v);

        Vector3f& operator+=(const Vector3f& r)
        {
            x += r.x;
            y += r.y;
            z += r.z;

            return *this;
        }

        Vector3f& operator-=(const Vector3f& r)
        {
            x -= r.x;
            y -= r.y;
            z -= r.z;

            return *this;
        }

        Vector3f& operator*=(float f)
        {
            x *= f;
            y *= f;
            z *= f;

            return *this;
        }

        bool operator==(const Vector3f& r)
        {
            return ((x == r.x) && (y == r.y) && (z == r.z));
        }

        bool operator!=(const Vector3f& r)
        {
            return !(*this == r);
        }

        operator const float*() const
        {
            return &(x);
        }


        Vector3f Cross(const Vector3f& v) const;

        float Dot(const Vector3f& v) const
        {
            float ret = x * v.x + y * v.y + z * v.z;
            return ret;
        }

        float Distance(const Vector3f& v) const
        {
            float delta_x = x - v.x;
            float delta_y = y - v.y;
            float delta_z = z - v.z;
            float distance = sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
            return distance;
        }

        float Length() const
        {
            float len = sqrtf(x * x + y * y + z * z);
            return len;
        }

        bool IsZero() const
        {
            return ((x + y + z) == 0.0f);
        }

        Vector3f& Normalize();

        void Rotate(float Angle, const Vector3f& Axis);

        Vector3f Negate() const;

        void Print(bool endl = true) const
        {
            printf("(%f, %f, %f)", x, y, z);

            if (endl) {
                printf("\n");
            }
        }
    };

    struct Vector4f {
        float x, y, z, w;

        Vector4f() {}

        Vector4f(float _x, float _y, float _z, float _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        Vector4f(const Vector3f& v, float _w) 
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = _w;
        }

        void Print(bool endl = true) const
        {
            printf("%f, %f, %f, %f", x, y, z, w);

            if (endl) printf("\n");
        }

        Vector3f to3f() const
        {
            return Vector3f(x, y, z);
        }

        float Length() const
        {
            return sqrt(x * x + y * y + z * z + w * w);
        }

        Vector4f& Normalize();

        float Dot(const Vector4f& v) const
        {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }
    };

    inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
    {
        Vector3f Ret(l.x + r.x,
                    l.y + r.y,
                    l.z + r.z);

        return Ret;
    }

    inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
    {
        Vector3f Ret(l.x - r.x,
                    l.y - r.y,
                    l.z - r.z);

        return Ret;
    }

    inline Vector3f operator*(const Vector3f& l, float f)
    {
        Vector3f Ret(l.x * f,
                    l.y * f,
                    l.z * f);

        return Ret;
    }


    inline Vector3f operator/(const Vector3f& l, float f)
    {
        Vector3f Ret(l.x / f,
                    l.y / f,
                    l.z / f);

        return Ret;
    }


    inline Vector3f::Vector3f(const Vector4f& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    inline Vector4f operator+(const Vector4f& l, const Vector4f& r)
    {
        Vector4f Ret(l.x + r.x,
                    l.y + r.y,
                    l.z + r.z,
                    l.w + r.w);

        return Ret;
    }


    inline Vector4f operator-(const Vector4f& l, const Vector4f& r)
    {
        Vector4f Ret(l.x - r.x,
                    l.y - r.y,
                    l.z - r.z,
                    l.w - r.w);

        return Ret;
    }


    inline Vector4f operator/(const Vector4f& l, float f)
    {
        Vector4f Ret(l.x / f,
                    l.y / f,
                    l.z / f,
                    l.w / f);

        return Ret;
    }


    inline Vector4f operator*(const Vector4f& l, float f)
    {
        Vector4f Ret(l.x * f,
                    l.y * f,
                    l.z * f,
                    l.w * f);

        return Ret;
    }


    inline Vector4f operator*(float f, const Vector4f& l)
    {
        Vector4f Ret(l.x * f,
                    l.y * f,
                    l.z * f,
                    l.w * f);

        return Ret;
    }

    struct PersProjInfo
    {
        float FOV;
        float ar;
        float zNear;
        float zFar;
    };


    struct OrthoProjInfo
    {
        float r;        // right
        float l;        // left
        float b;        // bottom
        float t;        // top
        float n;        // z near
        float f;        // z far

        float Width;
        float Height;    

        void Print()
        {
            printf("Left %f   Right %f\n", l, r);
            printf("Bottom %f Top %f\n", b, t);
            printf("Near %f   Far %f\n", n, f);
        }
    };


    struct Quaternion
    {
        float x, y, z, w;

        Quaternion(float Angle, const Vector3f& V);

        Quaternion(float _x, float _y, float _z, float _w);

        void Normalize();

        Quaternion Conjugate() const;

        Vector3f ToDegrees();
    };

    Quaternion operator*(const Quaternion& l, const Quaternion& r);

    Quaternion operator*(const Quaternion& q, const Vector3f& v);

    class Matrix4f
    {
        public:
            float m[4][4];

            Matrix4f() {}

            Matrix4f(float a00, float a01, float a02, float a03,
                    float a10, float a11, float a12, float a13,
                    float a20, float a21, float a22, float a23,
                    float a30, float a31, float a32, float a33)
            {
                m[0][0] = a00;
                m[0][1] = a01;
                m[0][2] = a02;
                m[0][3] = a03;

                m[1][0] = a10;
                m[1][1] = a11;
                m[1][2] = a12;
                m[1][3] = a13;

                m[2][0] = a20;
                m[2][1] = a21;
                m[2][2] = a22;
                m[2][3] = a23;

                m[3][0] = a30;
                m[3][1] = a31;
                m[3][2] = a32;
                m[3][3] = a33;
            }

            inline Matrix4f operator*(const Matrix4f& Right) const
            {
                Matrix4f Ret;

                for (unsigned int i = 0 ; i < 4 ; i++) {
                    for (unsigned int j = 0 ; j < 4 ; j++) {
                        Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                                    m[i][1] * Right.m[1][j] +
                                    m[i][2] * Right.m[2][j] +
                                    m[i][3] * Right.m[3][j];
                    }
                }

                return Ret;
            }

            void Print() const
            {
                for (int i = 0 ; i < 4 ; i++) {
                    printf("%f %f %f %f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
                }
            }

            void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ);

            void InitRotateTransform(float RotateX, float RotateY, float RotateZ);

            void InitTranslationTransform(float x, float y, float z);

            void InitCameraTransform(const Vector3f& Target, const Vector3f& Up);

            void InitCameraTransform(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

            void InitPersProjTransform(const PersProjInfo& p);
            
            void InitOrthoProjTransform(const OrthoProjInfo& p);

        private:
            void InitRotationX(float RotateX);
            void InitRotationY(float RotateY);
            void InitRotationZ(float RotateZ);
        

    };

    struct Vertex {
        Vector3f _pos;
        Vector2f _tex;

        Vertex() {};

        Vertex(const Vector3f& pos, const Vector2f& tex)
        {
            _pos = pos;
            _tex = tex;
        }
    };

}