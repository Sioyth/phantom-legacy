#pragma once
#include <string>
#include <iostream>
#include <glm.hpp>
#include <vector>
#include <string>

class Debug
{
public:

	//static Debug* Instance();

public:

	static void ClearLog();

	static void Log(int i);
	static void Log(float f);
	static void Log(glm::vec2 vec2);
	static void Log(glm::vec3 vec3);
	static void Log(std::string log);

	static void ErrorLog(std::string log);
	static void WarningLog(std::string log);

	static void GLErrors();
public:

	static const std::vector<std::string> &GetLogs();

private:

	static std::vector<std::string> m_logs;
};

