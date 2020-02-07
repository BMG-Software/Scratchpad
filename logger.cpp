

#include "logger.h"

static const char* LogFilename = "scratchpad.log";



Logger & Logger::Get()
{
	static Logger logger;
	return logger;
}

void Logger::LogDebug(const char * message)
{
	m_LogFile << "[Debug]";
	Log(message);
}

void Logger::LogError(const char * message)
{
	m_LogFile << "[Error]";
	Log(message);
}

void Logger::Log(const char * message)
{
	m_LogFile << " " << message << "\n";
}

Logger::Logger()
{
	m_LogFile.open(LogFilename, std::ofstream::trunc);
}

Logger::~Logger()
{
	m_LogFile.close();
}