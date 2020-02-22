
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

namespace Graphics
{

	// Temporary values for the maximum vertices and indices
	static const int MaxVertices		= 1024;
	static const int MaxIndices			= 1024;

	static const int MaxTextureCoords	= 512;
	static const int MaxTextureIndices	= 512;

	static const int MaxVertexNormals	= 512;
	static const int MaxNormalIndices	= 512;

	// Structure that wraps .obj 3D model data
	struct ObjModel
	{

		std::vector<GLfloat> m_Vertices;
		std::vector<GLushort> m_Indices;

		std::vector<GLfloat> m_TextureCoords;
		std::vector<GLushort> m_TextureIndices;

		std::vector<GLfloat> m_VertexNormals;
		std::vector<GLushort> m_NormalIndices;

		SDL_Surface* m_Texture;

	};

}

#endif // OBJMODEL_H