#include "tngin_camera.h"

namespace TAL {
    void TNGINCamera::Init() {
        _position = Vector3f(0, 0, 0);
        _target = Vector3f(0, 0, 1);
        _up = Vector3f(0, 1, 0);
    }

    void TNGINCamera::SetPosition(float x, float y, float z) 
    {
        _position = Vector3f(x, y, z);
    }

    Matrix4f TNGINCamera::GetMatrix() 
    {
        Matrix4f CameraTransformation;
        CameraTransformation.InitCameraTransform(_position, _target, _up);

        return CameraTransformation;
    }

    void TNGINCamera::Move(float x, float y, float z) 
    {
        _position.x += x * _speed;
        _position.y += y * _speed;
        _position.z += z * _speed;
    }

}