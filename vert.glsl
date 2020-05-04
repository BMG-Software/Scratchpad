#version 330 core

/**
* Sets up for basic phong shading in fragment shader
*/


attribute vec3 coord3d;
attribute vec3 norm;
attribute vec2 coordTex;

varying vec4 position;						// Position of vertex (and fragment) in world space
varying vec3 varyingNormalDirection;		// The surface normal vector in world space

uniform mat4 model, view, projection;
uniform mat3 m_3x3_inv_transp;				// Whatever this is, it needs to be passed in

out vec2 coordTexture;

void main()
{

  position = model * vec4(coord3d, 1.0);
  varyingNormalDirection = normalize(m_3x3_inv_transp * norm);

  gl_Position = projection * view * model * vec4(coord3d, 1.0);
  coordTexture = coordTex;
}