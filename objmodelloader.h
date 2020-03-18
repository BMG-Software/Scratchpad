#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

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

		void ApplyToModel(const std::vector<GLfloat> &toInsert, ObjModel& model);


		std::vector<GLfloat> m_TempVertices;
		std::vector<GLfloat> m_TempTextureCoords;
		std::vector<GLfloat> m_TempNormals;

		Logger& m_Logger;

	};

}






#endif // OBJMODELLOADER_H