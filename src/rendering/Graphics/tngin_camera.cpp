#include "tngin_camera.h"

namespace TAL {
    void TNGINCamera::Init() {
        _position = Vector3f(0.0f, 0.5f, 0.0f);
        _target = Vector3f(0, 0, 1);
        _up = Vector3f(0, 1, 0);

        Vector3f HTarget(_target.x, 0.0, _target.z);
        HTarget.Normalize();

        float angle = ToDegree(asin(abs(HTarget.z)));

        if (HTarget.z >= 0.0f) {
            if (HTarget.x >= 0.0f) {
                _angle_h = 360.0f - angle;
            } else {
                _angle_h = 180.0f + angle;
            }
        } else {
            if (HTarget.x >= 0.0f) {
                _angle_h = angle;
            } else {
                _angle_h = 180.0f - angle;
            }
        }

        _angle_v = -ToDegree(asin(_target.y));
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

    void TNGINCamera::Rotate(float delta_x, float delta_y) 
    {
        _angle_h += (float)delta_x / 20.0f;
        _angle_v -= (float)delta_y / 50.0f;

        Vector3f Yaxis(0.0f, 1.0f, 0.0f);

        Vector3f View(1.0f, 0.0f, 0.0f);

        View.Rotate(_angle_h, Yaxis);
        View.Normalize();

        Vector3f U = Yaxis.Cross(View);
        U.Normalize();
        View.Rotate(_angle_v, U);

        _target = View;
        _target.Normalize();

        _up = _target.Cross(U);
        _up.Normalize();
        
    }

}