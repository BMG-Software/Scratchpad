

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
			char* token = NULL, *nextToken = NULL;
			token = strtok_s(line, " ", &nextToken);
			if (token == NULL) continue;
			if (strcmp(token, "v") == 0)
			{
				token = strtok_s(NULL, " ", &nextToken);
				while (token != NULL)
				{
					obj.m_Vertices[obj.m_VertexCount] = (GLfloat)atof(token);
					obj.m_VertexCount++;
					token = strtok_s(NULL, " ", &nextToken);
				}
			}
			else if (strcmp(token, "f") == 0)
			{
				token = strtok_s(NULL, " ", &nextToken);
				while (token != NULL)
				{
					obj.m_Indices[obj.m_IndexCount] = ((GLushort)atoi(token) - 1); // Normalise so indices should start at 0
					obj.m_IndexCount++;
					token = strtok_s(NULL, " ", &nextToken);
				}
			}
		} while (!m_FileReader.eof());
		result = true;
	}
	m_FileReader.close();
	return result;
}
