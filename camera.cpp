#include "camera.h"

#include <cstring>
#include <cmath>

static vec3 Up = { 0.f, 1.f, 0.f };

Camera::Camera() 
{
    // TODO: Check this over and make sure it's the right way of doing it
    float position[3] = { 0.f, 0.f, 0.f };
    memcpy(m_Position, position, sizeof(vec3));
    float direction[3] = { 0.f, 0.f, -1.f };
    memcpy(m_ViewDirection, direction, sizeof(vec3));
}

void Camera::SetPosition(vec3 pos)
{
    memcpy(m_Position, pos, sizeof(vec3));
}

void Camera::UpdatePosition(float x, float y, float z)
{
    m_Position[0] += x;
    m_Position[1] += y;
    m_Position[2] += z;
}

void Camera::Rotate(float angle)
{
    mat4x4 rotationMatrix = 
    {
        {        cosf(angle), 0.f, sinf(angle), 0.f},
        {                0.f, 1.f,         0.f, 0.f},
        { sinf(angle) * -1.f, 0.f, cosf(angle), 0.f},
        {                0.f, 0.f,         0.f, 1.f }
    };

    vec4 viewDirection, result;
    memset(viewDirection, 0, sizeof(vec4));
    memcpy(viewDirection, m_ViewDirection, sizeof(vec3));
    mat4x4_mul_vec4(result, rotationMatrix, viewDirection);

    memcpy(m_ViewDirection, result, sizeof(vec3)); // trims off the end

}

void Camera::GetWorldToViewMatrix(mat4x4 wtv)
{
    vec3 center;
    vec3_add(center, m_Position, m_ViewDirection);
    mat4x4_look_at(wtv, m_Position, center, Up);
}
