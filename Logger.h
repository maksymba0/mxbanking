#pragma once
#include <string>
class Logger
{
	bool ShowMsg, ShowErrors, ShowInformation;

public: 

	void PrintMsg(std::string message);
	void ErrorMsg(std::string message, const char* ErrorType);
	void InformationMsg(std::string message);

	Logger();
};

static Logger Log;
