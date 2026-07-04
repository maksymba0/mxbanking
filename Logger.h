#pragma once
#include <string>
class Logger
{
	 

public: 

	void PrintMsg(std::string message);
	void ErrorMsg(std::string message, const char* ErrorType);
	void InformationMsg(std::string message);

	bool ShowMsg, ShowErrors, ShowInformation;
	Logger();
};

static Logger Log;
