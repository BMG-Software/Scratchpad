
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

namespace Graphics
{

	class TexturedMaterial
	{
    public:
        TexturedMaterial()
        {
            memset(m_AmbientColour, 0, sizeof(GLfloat) * 3);
            memset(m_DiffuseColour, 0, sizeof(GLfloat) * 3);
            memset(m_SpecularColour, 0, sizeof(GLfloat) * 3);
            m_SpecularExponent = 0;
            m_Dissolved = 0;
            m_TextureMap = nullptr;
        }

        virtual ~TexturedMaterial()
        {
            if (m_TextureMap != nullptr)
            {
                SDL_FreeSurface(m_TextureMap);
            }
        }

    private:

		GLfloat m_AmbientColour[3];
		GLfloat m_DiffuseColour[3];
		GLfloat m_SpecularColour[3];
		GLfloat m_SpecularExponent;

		GLfloat m_Dissolved; // Transparent

    public:

		SDL_Surface* m_TextureMap; // TODO: Proper getter/setter

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