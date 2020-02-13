

#include "objmodelloader.h"

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
	m_FileReader.open(objFilename, std::fstream::in);
	if (m_FileReader.is_open())
	{
		char line[MaxLineLength];
		m_FileReader.getline(line, MaxLineLength);

		// TODO: Tokenize and parse each line.

		m_FileReader.close(); // Do I need to close if it fails?
		return true;
	}
	else
	{
		return false;
	}
}
