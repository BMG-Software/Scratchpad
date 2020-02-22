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

		void InitialiseModel(ObjModel& obj);

		bool LoadMaterial(const char* line, ObjModel& obj);

		bool LoadTexture(const char* textureFilename, ObjModel& obj);
		bool LoadVertices(const char* line, ObjModel& model);
		bool LoadIndices(const char* line, ObjModel& model);

		Logger& m_Logger;
		std::ifstream m_FileReader;

	};

}






#endif // OBJMODELLOADER_H