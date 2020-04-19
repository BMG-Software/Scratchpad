
#ifndef CAMERA_H
#define CAMERA_H

#include "linmath.h"
#include "logger.h"

namespace Graphics
{

    class Camera
    {

    public:
        Camera();
        virtual ~Camera() = default;

        void SetPosition(vec3 pos);

        void MoveForward();

        void MoveBackward();

        void StrafeLeft();

        void StrafeRight();

        void Rotate(); // Rotate the camera around the Y axis

        void GetWorldToViewMatrix(mat4x4 wtv);

    private:
        vec3 m_Position, m_ViewDirection;

        int m_OldMouseX, m_OldMouseY;

        Logger &m_Logger;

    };

}

#endif // CAMERA_H