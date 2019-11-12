#include "Interface.h"
#include "Input.h"
#include "SceneManager.h"
#include "Cube.h"
#include "Quad.h"

float startTimer = 0.0f;

Interface* Interface::Instance()
{
	static Interface* s_Interface = new Interface;
	return s_Interface;
}

Interface::Interface()
{
	m_click = false;
	m_cooldown = false;

	// -------------------------------------------# Set ImGui Style

	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 1.5f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 1.5f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 5.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;
	style.WindowBorderSize = 0.0f;

	// -------------------------------------------# Set ImGui Colors

	// Text
	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

	// Windows Background
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.13f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);

	// Border
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);

	// Frame
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

	// Title
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);

	// Menu 
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);

	// Scrollbar
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	
	// Check Bar
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);

	// Slider
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

	// Button
	style.Colors[ImGuiCol_Button] = ImVec4(0.45f, 0.40f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

	// Header
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

	// Resize Grip
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

	// Plot
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

	// Modal Window
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	
}

void Interface::DrawUi()
{
	// Draws all the UI or inferface component
	DrawMainMenuBar();
	DrawConsole();
	RightClickMenu();

	// FOR DEBUG ONLY/ ALSO USED AS CODE REFERENCE FOR IMGUII
	ImGui::ShowDemoWindow(); 
}

void Interface::DrawConsole()
{
	// #------------------------------------------#
	// -			Debug Console				  -
	// #------------------------------------------#

	// TODO: Option to Export Log Info to a file;


	ImGui::Begin("Debug Console");

	// -------------------------------------------# Adds Debug Buttons (TESTING)

	if (ImGui::Button("Add Log"))
		Debug::Log("Dummy log");
	
	ImGui::SameLine();

	if (ImGui::Button("Add Error Log"))
		Debug::Log("[Error] Dummy Log");
	

	ImGui::SameLine();

	// -------------------------------------------# Adds Clear Log Button

	if (ImGui::Button("Clear"))
		Debug::ClearLog();
	
	ImGui::Separator();

	// -------------------------------------------# 
	//Starts a child window that is scrollable so that the "Clear" Option stays always at the top.

	ImGui::BeginChild("Logs");

	// -------------------------------------------# Display the Logs

	bool pop_color = false;

	for (int i = 0; i < Debug::GetLogs().size(); i++)
	{
		// Reset Pop Color
		pop_color = false;

		// Checks if it's an Error, Warn or normal log
		if (strstr(Debug::GetLogs()[i].c_str(), "[Error]"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
			pop_color = true;
		}
		else if (strstr(Debug::GetLogs()[i].c_str(), "[Warn]"))
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f));
			pop_color = true;
		}

		ImGui::TextUnformatted(Debug::GetLogs()[i].c_str());

		if (pop_color)
		{
			ImGui::PopStyleColor();
		}

	}

	// Auto-Scroll
	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	// -------------------------------------------# Ends ImGuiFrames

	ImGui::EndChild();
	ImGui::End();
}

void Interface::DrawMainMenuBar()
{
	// -------------------------------------------# Draws Main Menu Bar

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	// -------------------------------------------# 
}

void Interface::RightClickMenu()
{
	// problems with depency as it depends on the current scene, and depends on having all includes for primitives..
	// Need to fix the vector of GameObjects in each scene.

	if (m_isRightMenuEnabled)
	{
		ImGui::OpenPopup("Menu");
		if (ImGui::BeginPopup("Menu", m_isRightMenuEnabled))
		{

			if (ImGui::BeginMenu("New Primitive"))
			{
				if (ImGui::MenuItem("Quad")) 
				{
					SceneManager::Instance()->GetCurrentScene().PushGameObject(new Quad);
					m_isRightMenuEnabled = false;
				}

				if (ImGui::MenuItem("Cube")) 
				{
					SceneManager::Instance()->GetCurrentScene().PushGameObject(new Cube);
					m_isRightMenuEnabled = false;
				}

				/*if (ImGui::MenuItem("Sphere")) 
				{

				}*/

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
	}

	// TODO add function GetMouseButtonClick() in input class.
	
	float currentTime = SDL_GetTicks() / 1000.0f;

	//Debug::Log(currentTime);

	
	if (Input::Instance()->GetMouseButtonDown(1))
	{
		if (!m_click)
		{
			m_cooldown = true;
			m_isRightMenuEnabled = false;
			startTimer = SDL_GetTicks() / 1000.0f;
		}

		m_click = true;
	}
	else 
	{
		startTimer = 0;
		m_click = false;
	}
	
	if (currentTime - 0.2f > startTimer && m_cooldown)
	{
		if (m_click)
		{
			m_cooldown = false;
		}
		else
		{
			m_isRightMenuEnabled = true;
			m_cooldown = false;
		}
	}
	

	if (Input::Instance()->GetMouseButtonDown(0))
	{
		//m_isRightMenuEnabled = false;
	}
}


