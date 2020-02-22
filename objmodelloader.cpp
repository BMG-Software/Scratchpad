

#include "objmodelloader.h"

#include <SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

using namespace Graphics;

static const int MaxLineLength = 256;

static const std::string Fileprefix = "resources/materialcube/";

ObjModelLoader::ObjModelLoader() : m_Logger(Logger::Get())
{
}

bool ObjModelLoader::LoadModel(const char* objFilename, ObjModel& obj)
{
	bool result = false;
	std::string fullFilepath = Fileprefix + std::string(objFilename);
	std::ifstream filereader;
	filereader.open(fullFilepath.c_str(), std::fstream::in);
	if (filereader.is_open())
	{
		char line[MaxLineLength];
		do
		{
			filereader.getline(line, MaxLineLength);
			if (!FindMaterialFile(line, obj.m_Material))
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

bool ObjModelLoader::FindMaterialFile(const char * line, TexturedMaterial& mtl)
{
	bool result = false;
	char *token = NULL, *nextToken = NULL;
	char lineCopy[MaxLineLength];
	strncpy_s(lineCopy, line, MaxLineLength);
	token = strtok_s(lineCopy, " ", &nextToken);
	if (token != NULL && strcmp(token, "mtllib") == 0)
	{
		result = LoadMaterial(nextToken, mtl);
	}
	return result;
}

bool ObjModelLoader::LoadMaterial(const char* materialFilename, TexturedMaterial& mtl)
{
	bool result = false;
	std::ifstream fileReader;
	std::string fullFilepath = Fileprefix + std::string(materialFilename);
	fileReader.open(fullFilepath, std::fstream::in);
	if (fileReader.is_open())
	{
		m_Logger.LogDebug("Successfully opened material file");
		char line[MaxLineLength];
		char *token = NULL, *nextToken = NULL;
		do
		{
			fileReader.getline(line, MaxLineLength);
			token = strtok_s(line, " ", &nextToken);
			while (token != NULL)
			{
				/* // TODO: Handle all the extra material related stuff
				if (strcmp(token, "Ka") == 0)
				{
					
				}
				else if (strcmp(token, "Kd") == 0)
				{

				}
				else if (strcmp(token, "Ks") == 0)
				{

				}
				else if (strcmp(token, "Ns") == 0)
				{

				}
				else if (strcmp(token, "d") == 0 || strcmp(token, "Tr") == 0)
				{

				}
				else */
				if (strcmp(token, "map_Ka") == 0)
				{
					std::string materialFilepath = Fileprefix + std::string(nextToken);
					mtl.m_TextureMap = IMG_Load(materialFilepath.c_str());
					result = (mtl.m_TextureMap != nullptr);
					if (!result)
					{
						m_Logger.LogError("Failed to load obj model texture");
						m_Logger.LogError(SDL_GetError());
						break;
					}
				}
				token = strtok_s(NULL, " ", &nextToken);
			}

		} while (!fileReader.eof());
	}
	else
	{
		m_Logger.LogError("Material file not found");
	}
	fileReader.close();
	return result;
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
			// is very low priority for this project at this stage. We're all about opengl here

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
