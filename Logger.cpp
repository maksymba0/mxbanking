#include "Logger.h"
#include <iostream>

void Logger::PrintMsg(std::string message)
{
	if (!ShowMsg)
	{
		return;
	}
	std::cout << message;
}

void Logger::ErrorMsg(std::string message, const char* ErrorType = nullptr)
{
	if (!ShowErrors)
	{
		return;
	}
	static const char* errorMsg = "[ERROR]: ";
	if (!ErrorType)
	{
		ErrorType = errorMsg;
	}
	std::cout << ErrorType << message;
}

void Logger::InformationMsg(std::string message)
{
	std::cout << "[Information]: " << message;
}

Logger::Logger() : ShowMsg(false), ShowErrors(false), ShowInformation(false)
{

}
