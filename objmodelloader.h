#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include <fstream>

#include <SDL.h>
#include <SDL_opengl.h>

#include "objmodel.h"
#include "imodelloader.h"
#include "logger.h"

namespace Graphics
{
	
	// Class for loading .obj models
	class ObjModelLoader : public IModelLoader
	{

	public:
		ObjModelLoader();
		virtual ~ObjModelLoader() = default;

		bool LoadModel(const char* objFilename, ObjModel& obj);

	private:

		bool LoadVertices(const char* line, ObjModel& model);
		bool LoadIndices(const char* line, ObjModel& model);

		bool FindMaterialFile(const char* line, TexturedMaterial& mtl);
		bool LoadMaterial(const char* materialFilename, TexturedMaterial& mtl);

		Logger& m_Logger;
		std::ifstream m_FileReader;

	};

}






#endif // OBJMODELLOADER_H