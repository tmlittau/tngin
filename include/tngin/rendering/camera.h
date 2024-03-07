#pragma once

#include "graphics_types.h"

namespace TAL {
    class Camera {
        public:
            virtual void Init() = 0;

            virtual void SetPosition(float x, float y, float z) = 0;
            virtual void Move(float x, float y, float z) = 0;

            virtual Matrix4f GetMatrix() = 0;

        private:
            Vector3f _position;
            Vector3f _target;
            Vector3f _up;
            float _speed = 1.0f;
    };
}