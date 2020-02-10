#version 120

in vec3 fragmentColour;
void main()
{
  gl_FragColor = vec4(fragmentColour, 1.0);
}