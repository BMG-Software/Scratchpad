

#include "objmodelloader.h"

#include <SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

using namespace Graphics;

static const int MaxLineLength = 256;

ObjModelLoader::ObjModelLoader() : m_Logger(Logger::Get())
{
}

bool ObjModelLoader::LoadModel(const char* objFilename, ObjModel& obj)
{
	bool result = false;
	InitialiseModel(obj); // Initialise to a clean, known state
	// All of this is .obj file handling
	m_FileReader.open(objFilename, std::fstream::in);
	if (m_FileReader.is_open())
	{
		char line[MaxLineLength];
		do
		{
			m_FileReader.getline(line, MaxLineLength);
			if (!LoadMaterial(line, obj))
			{
				if (!LoadVertices(line, obj))
				{
					if (!LoadIndices(line, obj))
					{
						m_Logger.LogDebug("Skipping unsupported line type in .obj file");
					}
				}
			}
		} while (!m_FileReader.eof());
		result = true;
	}
	m_FileReader.close();
	return result;
}

void Graphics::ObjModelLoader::InitialiseModel(ObjModel & obj)
{
	obj.m_IndexCount = 0;
	obj.m_VertexCount = 0;
	memset(obj.m_Vertices, 0, MaxVertices);
	memset(obj.m_Indices, 0, MaxIndices);
	obj.m_Texture = nullptr;
}

bool Graphics::ObjModelLoader::LoadMaterial(const char * line, ObjModel &)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	token = strtok_s(lineCopy, " ", &nextToken);
	if (token != NULL && strcmp(token, "mtllib") == 0)
	{
		std::ifstream fileReader;
		fileReader.open(nextToken, std::fstream::in);
		if (fileReader.is_open())
		{
			m_Logger.LogDebug("Successfully opened material file");
			// TODO: Load the material file

		}
		fileReader.close();
	}
	return result;
}

bool Graphics::ObjModelLoader::LoadTexture(const char * textureFilename, ObjModel & obj)
{
	obj.m_Texture = IMG_Load(textureFilename);
	if (obj.m_Texture == nullptr)
	{
		m_Logger.LogError("Failed to load obj model texture");
		return false;
	}
	return true;
}

bool Graphics::ObjModelLoader::LoadVertices(const char* line, ObjModel& model)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	token = strtok_s(lineCopy, " ", &nextToken); 
	if (token != NULL && strcmp(token, "v") == 0)
	{
		token = strtok_s(NULL, " ", &nextToken);
		while (token != NULL)
		{
			model.m_Vertices[model.m_VertexCount] = (GLfloat)atof(token);
			model.m_VertexCount++;
			token = strtok_s(NULL, " ", &nextToken);
		}
		result = true;
	}
	return result;
}

bool Graphics::ObjModelLoader::LoadIndices(const char* line, ObjModel& model)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	token = strtok_s(lineCopy, " ", &nextToken);
	if (token != NULL && strcmp(token, "f") == 0)
	{
		token = strtok_s(NULL, " ", &nextToken);
		while (token != NULL)
		{
			model.m_Indices[model.m_IndexCount] = ((GLushort)atoi(token) - 1); // Normalise to reflect 0 based indexing
			model.m_IndexCount++;
			token = strtok_s(NULL, " ", &nextToken);
		}
		result = true;
	}
	return result;
}
