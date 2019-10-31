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
	
	void RightClickMenu();

private:

	bool m_isRightMenuEnabled = false;

private:

	Interface();
	Interface(const Interface&);
	Interface operator=(const Interface);
};

