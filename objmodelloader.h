#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include <fstream>

#include <SDL_opengl.h>

#include "imodelloader.h"
#include "logger.h"

namespace Graphics
{
	// Completely temporary
	static const int MaxVertices = 128;
	static const int MaxIndices = 128;

	struct ObjModel
	{
		GLfloat m_Vertices[MaxVertices];
		GLubyte m_Indices[MaxIndices];

		int m_VertexCount, m_IndexCount;
	};

	class ObjModelLoader : public IModelLoader
	{

	public:
		ObjModelLoader();
		virtual ~ObjModelLoader();

		bool LoadModel(const char* objFilename, ObjModel& obj);

	private:

		Logger& m_Logger;
		std::ifstream m_FileReader;

	};

}






#endif // OBJMODELLOADER_H