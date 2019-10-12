#include "Debug.h"
#include "glad/glad.h"

std::vector<std::string> Debug::m_logs;

void Debug::Log(int i)
{
	std::string tempLog;
	tempLog = "" + std::to_string(i);
	m_logs.push_back(tempLog);
}

void Debug::Log(float f)
{
	std::string tempLog;
	tempLog = "" + std::to_string(f);
	m_logs.push_back(tempLog);
}

void Debug::Log(glm::vec2 vec2)
{
	std::string tempLog;
	tempLog = "x: " + std::to_string(vec2.x) + " | y: " + std::to_string(vec2.y);

	m_logs.push_back(tempLog);
}

void Debug::Log(glm::vec3 vec3)
{
	std::string tempLog;
	tempLog = "x: " + std::to_string(vec3.x) + " | y: " + std::to_string(vec3.y) + " | z: " + std::to_string(vec3.z);

	m_logs.push_back(tempLog);
}

void Debug::Log(std::string log)
{
	std::string tempLog = log;
	m_logs.push_back(tempLog);
}

void Debug::ClearLog()
{
	m_logs.clear();
}

void Debug::ErrorLog(std::string log)
{
	std::string tempLog = "[Error] " + log;
	m_logs.push_back(tempLog);
}

void Debug::WarningLog(std::string log)
{
	std::cout << "[Warning] " << log << std::endl;
}

void Debug::GLErrors()
{
	GLenum errorCode = glGetError();

	if (errorCode == GL_NO_ERROR)
	{

	}
	else if (errorCode == GL_INVALID_OPERATION)
	{
		ErrorLog("OpenGL invalid operation");
	}
}

const std::vector<std::string>& Debug::GetLogs()
{
	return m_logs;
}
