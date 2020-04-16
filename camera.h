
#ifndef CAMERA_H
#define CAMERA_H

#include "linmath.h"

class Camera
{

public:
    Camera();
    virtual ~Camera() = default;

    void SetPosition(vec3 pos);
    void UpdatePosition(float x, float y, float z);

    void Rotate(float value); // Rotate the camera around the Y axis

    void GetWorldToViewMatrix(mat4x4 wtv);

private:
    vec3 m_Position, m_ViewDirection;



};



#endif // CAMERA_H