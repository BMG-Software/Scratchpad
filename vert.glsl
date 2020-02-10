#version 120
attribute vec3 coord3d;
attribute vec3 colour;
out vec3 fragmentColour;
void main()
{
  gl_Position = vec4(coord3d, 1.0);
  fragmentColour = colour;
}