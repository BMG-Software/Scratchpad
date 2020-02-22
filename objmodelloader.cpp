

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
	std::ifstream filereader;
	filereader.open(objFilename, std::fstream::in);
	if (filereader.is_open())
	{
		char line[MaxLineLength];
		do
		{
			filereader.getline(line, MaxLineLength);
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
		} while (!filereader.eof());
		result = true;
	}
	filereader.close();
	return result;
}

void ObjModelLoader::InitialiseModel(ObjModel & obj) // TODO: Remove
{
	obj.m_Texture = nullptr;
}

bool ObjModelLoader::LoadMaterial(const char * line, ObjModel &)
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
		else
		{
			m_Logger.LogError("Material file not found");
		}
		fileReader.close();
	}
	return result;
}

bool ObjModelLoader::LoadTexture(const char * textureFilename, ObjModel & obj)
{
	obj.m_Texture = IMG_Load(textureFilename);
	if (obj.m_Texture == nullptr)
	{
		m_Logger.LogError("Failed to load obj model texture");
		return false;
	}
	return true;
}

bool ObjModelLoader::LoadVertices(const char* line, ObjModel& model)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	char *type = strtok_s(lineCopy, " ", &nextToken); 
	if (type != NULL)
	{
		token = strtok_s(NULL, " ", &nextToken);
		while (token != NULL)
		{
			if (strcmp(type, "v") == 0)
			{
				model.m_Vertices.push_back((GLfloat)atof(token));
				result = true;
			}
			else if (strcmp(type, "vt") == 0)
			{
				model.m_TextureCoords.push_back((GLfloat)atof(token));
				result = true;
			}
			else if (strcmp(type, "vn") == 0)
			{
				model.m_VertexNormals.push_back((GLfloat)atof(token));
				result = true;
			}
			token = strtok_s(NULL, " ", &nextToken);
		}
	}
	return result;
}

bool ObjModelLoader::LoadIndices(const char* line, ObjModel& model)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	token = strtok_s(lineCopy, " ", &nextToken);
	if (token != NULL && strcmp(token, "f") == 0)
	{
		token = strtok_s(NULL, " /", &nextToken);
		while (token != NULL)
		{
			// NOTE: This is not robust at all, will probably improve in the future but this
			// is very low priority for this project

			model.m_Indices.push_back((GLushort)atoi(token) - 1);
			token = strtok_s(NULL, " /", &nextToken);
			model.m_TextureIndices.push_back((GLushort)atoi(token) - 1);
			token = strtok_s(NULL, " /", &nextToken);
			model.m_NormalIndices.push_back((GLushort)atoi(token) - 1);
			token = strtok_s(NULL, " /", &nextToken);
		}
		result = true;
	}
	return result;
}
