#pragma once

#include <vector>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Debug.h";

class Interface
{
public:

	static Interface* Instance();

public:

	void DrawUi();

private:

	void DrawConsole();
	void DrawMainMenuBar();
	
private:

	Interface();
	Interface(const Interface&);
	Interface operator=(const Interface);

private:

	static std::vector<std::string>* m_logs;
};

