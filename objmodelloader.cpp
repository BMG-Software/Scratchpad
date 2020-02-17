

#include "objmodelloader.h"

#include <stdio.h>
#include <stdlib.h>

using namespace Graphics;

static const int MaxLineLength = 256;

ObjModelLoader::ObjModelLoader() : m_Logger(Logger::Get())
{
}

ObjModelLoader::~ObjModelLoader()
{
}

bool ObjModelLoader::LoadModel(const char* objFilename, ObjModel& obj)
{
	bool result = false;
	obj.m_IndexCount = 0;
	obj.m_VertexCount = 0;
	m_FileReader.open(objFilename, std::fstream::in);
	if (m_FileReader.is_open())
	{
		char line[MaxLineLength];
		do
		{
			m_FileReader.getline(line, MaxLineLength);
			if (!LoadVertices(line, obj))
			{
				if (!LoadIndices(line, obj))
				{
					m_Logger.LogDebug("Skipping unsupported line type in .obj file");
				}
			}
		} while (!m_FileReader.eof());
		result = true;
	}
	m_FileReader.close();
	return result;
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
