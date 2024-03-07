#include <tngin/rendering/graphics_transforms.h>


namespace TAL {
    void WorldTransform::SetScale(float scale) {
        _scale = scale;
    }

    void WorldTransform::SetRotation(float x, float y, float z) {
        _rotation.x = x;
        _rotation.y = y;
        _rotation.z = z;
    }

    void WorldTransform::SetTranslation(float x, float y, float z) {
        _position.x = x;
        _position.y = y;
        _position.z = z;
    }

    void WorldTransform::Rotate(float x, float y, float z) {
        _rotation.x += x;
        _rotation.y += y;
        _rotation.z += z;
    }

    Matrix4f WorldTransform::GetMatrix() {
        Matrix4f Rotation;
        Rotation.InitRotateTransform(_rotation.x, _rotation.y, _rotation.z);

        Matrix4f Translation;
        Translation.InitTranslationTransform(_position.x, _position.y, _position.z);

        Matrix4f Scale;
        Scale.InitScaleTransform(_scale, _scale, _scale);

        return Translation * Rotation * Scale;
    }
}