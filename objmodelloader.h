#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include <fstream>

#include <SDL_opengl.h>

#include "imodelloader.h"
#include "logger.h"

namespace Graphics
{
	// Temporary values for the maximum vertices and indices
	static const int MaxVertices = 128;
	static const int MaxIndices = 128;

	// Structure that wraps .obj 3D model data
	struct ObjModel
	{
		GLfloat m_Vertices[MaxVertices];
		GLushort m_Indices[MaxIndices];

		int m_VertexCount, m_IndexCount;
	};

	// Class for loading .obj models
	class ObjModelLoader : public IModelLoader
	{

	public:
		ObjModelLoader();
		virtual ~ObjModelLoader();

		bool LoadModel(const char* objFilename, ObjModel& obj);

	private:

		bool LoadVertices(const char* line, ObjModel& model);
		bool LoadIndices(const char* line, ObjModel& model);

		Logger& m_Logger;
		std::ifstream m_FileReader;

	};

}






#endif // OBJMODELLOADER_H