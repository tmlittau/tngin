#pragma once

#include "graphics_types.h"


namespace TAL {
    class WorldTransform
    {
        public:
            WorldTransform() {}

            void SetScale(float scale);
            void SetRotation(float x, float y, float z);
            void SetTranslation(float x, float y, float z);

            void Rotate(float x, float y, float z);

            Matrix4f GetMatrix();

        private:
            float _scale = 1.0f;
            Vector3f _rotation = Vector3f(0.0f, 0.0f, 0.0f);
            Vector3f _position = Vector3f(0.0f, 0.0f, 0.0f);
    };
}