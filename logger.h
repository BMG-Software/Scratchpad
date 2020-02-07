
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

class Logger
{

public:
	static Logger& Get();

	void LogDebug(const char* message);
	void LogError(const char* message);


	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

private:

	void Log(const char* message);

	Logger();
	~Logger();

	std::ofstream m_LogFile;

};





#endif // LOGGER_H