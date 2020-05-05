#include "camera.h"

#include <SDL.h>

#include <cstring>
#include <cmath>

#define DegreesToRadians(angleInDegrees) ((angleInDegrees) * (float)M_PI / 180.f)

static vec3 Up = { 0.f, 1.f, 0.f };
static const float MovementSpeed = 0.1f;

using namespace Graphics;

Camera::Camera() : m_Logger(Logger::Get())
{
    m_OldMouseX = 0;
    m_OldMouseY = 0;
    float position[3] = { 0.f, 0.f, 0.f };
    memcpy(m_Position, position, sizeof(vec3));
    float direction[3] = { 0.f, 0.f, -1.f };
    memcpy(m_ViewDirection, direction, sizeof(vec3));
}

void Camera::SetPosition(vec3 pos)
{
    memcpy(m_Position, pos, sizeof(vec3));
}

void Camera::MoveForwardBackward(char direction)
{
    vec3 movementVector = 
    { 
        m_ViewDirection[0] * MovementSpeed * direction, 
        m_ViewDirection[1] * MovementSpeed * direction, 
        m_ViewDirection[2] * MovementSpeed * direction
    };

    vec3 newPosition;

    vec3_add(newPosition, m_Position, movementVector);

    memcpy(m_Position, newPosition, sizeof(vec3));
}

void Camera::StrafeLeftRight(char direction)
{
    vec3 strafeVector;
    vec3_mul_cross(strafeVector, m_ViewDirection, Up);

    strafeVector[0] *= MovementSpeed * direction;
    strafeVector[1] *= MovementSpeed * direction;
    strafeVector[2] *= MovementSpeed * direction;

    vec3 newPosition;

    vec3_add(newPosition, m_Position, strafeVector);

    memcpy(m_Position, newPosition, sizeof(vec3));

}

void Camera::Rotate()
{
    // TODO: tidy this up
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    int mouseDeltaX = mouseX - m_OldMouseX;
    int mouseDeltaY = mouseY - m_OldMouseY;

    float angleX = DegreesToRadians(mouseDeltaX);
    float angleY = DegreesToRadians(mouseDeltaY);

    mat4x4 rotationMatrixX = // Rotation around the X axis (Up and Down movement)
    {
        { 1.f,          0.f,                 0.f, 0.f },
        { 0.f, cosf(angleY),       -sinf(angleY), 0.f },
        { 0.f, sinf(angleY),        cosf(angleY), 0.f },
        { 0.f,          0.f,                 0.f, 1.f }
    };

    mat4x4 rotationMatrixY = // Rotation around the Y axis (Left and right movement)
    {
        { cosf(angleX),  0.f, sinf(angleX), 0.f },
        {          0.f,  1.f,          0.f, 0.f },
        { -sinf(angleX), 0.f, cosf(angleX), 0.f },
        {           0.f, 0.f,          0.f, 1.f }
    };

    

    mat4x4 rotationMatrix;
    mat4x4_mul(rotationMatrix, rotationMatrixY, rotationMatrixX);

    vec4 viewDirection, result;
    memset(viewDirection, 0, sizeof(vec4));
    memcpy(viewDirection, m_ViewDirection, sizeof(vec3));
    mat4x4_mul_vec4(result, rotationMatrix, viewDirection);

    memcpy(m_ViewDirection, result, sizeof(vec3)); // trims off the end

    m_OldMouseX = mouseX;
    m_OldMouseY = mouseY;
}

void Camera::GetWorldToViewMatrix(mat4x4 wtv)
{
    vec3 center;
    vec3_add(center, m_Position, m_ViewDirection);
    mat4x4_look_at(wtv, m_Position, center, Up);
}
