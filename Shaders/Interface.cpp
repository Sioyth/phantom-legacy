#include "Interface.h"
#include "Input.h"
#include "SceneManager.h"
#include "Cube.h"
#include "Quad.h"
#include "Light.h"
#include "SceneManager.h";
#include "EmptyGameObject.h"

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
	Inspector();
	ToolBar();

	// FOR DEBUG ONLY/ ALSO USED AS CODE REFERENCE FOR IMGUII
	//ImGui::ShowDemoWindow(); 
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
			// Primitives
			if (ImGui::BeginMenu("New Primitive"))
			{
				if (ImGui::MenuItem("Empty"))
				{
					EmptyGameObject* tempObj = new EmptyGameObject;
					tempObj->LoadModel("Models/sphere.obj");

					SceneManager::Instance()->GetCurrentScene().PushGameObject(tempObj);
					m_isRightMenuEnabled = false;
				}

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

			// Lights
			if (ImGui::BeginMenu("New Light"))
			{
				if (ImGui::MenuItem("Point Light"))
				{
					SceneManager::Instance()->GetCurrentScene().PushGameObject(new Light(PointLight));
					m_isRightMenuEnabled = false;
				}

				if (ImGui::MenuItem("Directional Light"))
				{
					SceneManager::Instance()->GetCurrentScene().PushGameObject(new Light(DirectionalLight));
					m_isRightMenuEnabled = false;
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
	}

	if (Input::Instance()->GetMouseButtonClick(1))
	{
		if (!ImGui::IsAnyWindowHovered())
		{
			m_isRightMenuEnabled = true;
		}
	}

}

void Interface::ToolBar()
{
	ImGui::Begin("ToolBar");
	{
		static bool gridFlag = SceneManager::Instance()->GetCurrentScene().GetGrid();
		if (ImGui::Checkbox("Grid:", &gridFlag))
		{
			SceneManager::Instance()->GetCurrentScene().SetGrid(gridFlag);
		}
		ImGui::SameLine();

		static bool planeFlag = SceneManager::Instance()->GetCurrentScene().GetPlane();
		if (ImGui::Checkbox("Plane:", &planeFlag))
		{
			SceneManager::Instance()->GetCurrentScene().SetPlane(planeFlag);
		}

		ImGui::End();
	}
}

void Interface::Inspector()
{
	static const int NUMBER_LINES = 3;

	if (SceneManager::Instance()->GetCurrentScene().GetSelectedGameObject() >= 0)
	{
		ImGui::Begin("Inspector");
		{
			GameObject* obj = SceneManager::Instance()->GetCurrentScene().GetGameObjects()[SceneManager::Instance()->GetCurrentScene().GetSelectedGameObject()];

			float position[3] = { obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z};
			float rotation[3] = { obj->GetRotation().x, obj->GetRotation().y, obj->GetRotation().z };
			float scale[3] = { obj->GetScale().x, obj->GetScale().y, obj->GetScale().z };
			float ambient[3] = { obj->GetAmbient().x,obj->GetAmbient().y, obj->GetAmbient().z };
			float diffuse[3] = { obj->GetDiffuse().x, obj->GetDiffuse().y, obj->GetDiffuse().z };
			float specular[3] = { obj->GetSpecular().x, obj->GetSpecular().y, obj->GetSpecular().z };

			ImGui::Text("Transform");

			if (ImGui::InputFloat3("Position", position, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
			{

				// X
				if (position[0] != obj->GetPosition().x)
				{
					float xOffset = position[0] - obj->GetPosition().x;
					obj->Translate(glm::vec3(xOffset, 0.0f, 0.0f));
					for (int i = 0; i < NUMBER_LINES; i++)
					{
						obj->GetTransformLines()[i].Translate(glm::vec3(xOffset, 0.0f, 0.0f));
					}
					
				}

				//Y
				if (position[1] != obj->GetPosition().y)
				{
					float yOffset = position[1] - obj->GetPosition().y;
					obj->Translate(glm::vec3(0.0f, yOffset, 0.0f));

					for (int i = 0; i < NUMBER_LINES; i++)
					{
						obj->GetTransformLines()[i].Translate(glm::vec3(0.0f, yOffset, 0.0f));
					}
				}

				//Z
				if (position[2] != obj->GetPosition().z)
				{
					float zOffset = position[2] - obj->GetPosition().z;
					obj->Translate(glm::vec3(0.0f, 0.0f, zOffset));

					for (int i = 0; i < NUMBER_LINES; i++)
					{
						obj->GetTransformLines()[i].Translate(glm::vec3(0.0f, 0.0f, zOffset));
					}
				}
				//obj->SetPosition(glm::vec3(position[0],position[1], position[2]));
			}
	
			// Rotation

			if (ImGui::InputFloat3("Rotation", rotation, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
			{
				obj->Rotate(rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
				obj->Rotate(rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
				obj->Rotate(rotation[2], glm::vec3(0.0f, 0.0f, 1.0));
			}

			// SCALE

			if (ImGui::InputFloat3("Scale", scale, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
			{
				// X
				if (scale[0] != obj->GetScale().x)
				{
					obj->Scale(glm::vec3(scale[0], 1.0f, 1.0f));
				}

				//Y
				if (scale[1] != obj->GetScale().y)
				{

					obj->Scale(glm::vec3(1.0f, scale[1], 1.0f));
				}

				//Z
				if (scale[2] != obj->GetScale().z)
				{

					obj->Scale(glm::vec3(1.0f, 1.0f, scale[2]));
				}

			}
			
			// Color

			ImGui::ColorEdit3("Ambient:", ambient);
			obj->SetAmbient(glm::vec3(ambient[0], ambient[1], ambient[2]));

			ImGui::ColorEdit3("Diffuse:", diffuse);
			obj->SetDiffuse(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));

			ImGui::ColorEdit3("Specular:", specular);
			obj->SetSpecular(glm::vec3(specular[0], specular[1], specular[2]));

			static bool isLit = obj->GetIsLit();
			if (ImGui::Checkbox("Lit:", &isLit))
			{
				obj->SetIsLit(isLit);
			}
			ImGui::SameLine();
		}
		ImGui::End();

	}
}


