#version 330 core

attribute vec3 coord3d;
attribute vec3 colour;
uniform mat4 mvp;

out vec3 fragmentColour;

void main()
{
  gl_Position = mvp * vec4(coord3d, 1.0);
  fragmentColour = colour;
}