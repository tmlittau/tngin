#pragma once

#include <tngin/rendering/graphics_types.h>
#include <tngin/rendering/camera.h>

namespace TAL {
    class TNGINCamera : public Camera {
        public:
            void Init() override;
            void SetPosition(float x, float y, float z) override;
            void Move(float x, float y, float z) override;
            void Rotate(float delta_x, float delta_y) override;

            Matrix4f GetMatrix() override;

        private:
            Vector3f _position;
            Vector3f _target;
            Vector3f _up;
            float _speed = 1.0f;

            float _angle_h;
            float _angle_v;
    };
}
