
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

namespace Graphics
{

	struct TexturedMaterial
	{

		GLfloat m_AmbientColour[3];
		GLfloat m_DiffuseColour[3];
		GLfloat m_SpecularColour[3];
		GLfloat m_SpecularExponent;

		GLfloat m_Dissolved; // Transparent

		SDL_Surface* m_TextureMap;

	};


	// Structure that wraps .obj 3D model data
	struct ObjModel
	{

		std::vector<GLfloat> m_Vertices;
		std::vector<GLushort> m_Indices;

		TexturedMaterial m_Material;

	};

}

#endif // OBJMODEL_H