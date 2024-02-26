#pragma once

namespace TAL {
    struct Vector3f {
        float x, y, z;

        Vector3f() {}

        Vector3f(float _x, float _y, float _z) {
            x = _x;
            y = _y;
            z = _z;
        }

        Vector3f(const float* pFloat) {
            x = pFloat[0];
            y = pFloat[1];
            z = pFloat[2];
        }

        Vector3f(float f) {
            x = f;
            y = f;
            z = f;
        }
    };
}