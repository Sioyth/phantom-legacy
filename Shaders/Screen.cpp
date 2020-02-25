#include "Screen.h"


Screen* Screen::Instance()
{
	static Screen* screen = new Screen;

	return screen;
}

//-----------------------------------------------------------------------------
void Screen::Initialize(int widht, int height, int major, int minor, bool mode)
{
	m_widht = widht;
	m_height = height;
	m_depthTest = true;

	// -------------------------------------------# Initialize SDL.

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL didn't initilize" << std::endl;
		return;
	}
	else
	{
		// -------------------------------------------# Set buffer RGBA component

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

		// -------------------------------------------# turn on double buffering

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// -------------------------------------------# set OpenGL to compatibility mode

		if (mode)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}

		// -------------------------------------------# set OpenGL version

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

		// -------------------------------------------# Create application window

		m_window = SDL_CreateWindow("Phantom Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widht, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		
		if (!m_window)
		{
			std::cout << "Error! Window was not created!" << std::endl;
			return;
		}

		// -------------------------------------------# create the OpenGL context

		m_context = SDL_GL_CreateContext(m_window);

		if (!m_context)
		{
			std::cout << "Error! Context was not created!" << std::endl;
			return;
		}

		// -------------------------------------------# Initiliaze Glad

		if (!gladLoadGL())
		{
			// CHANGE TO THE LOG CLASS
			std::cout << "Error initializing Glad" << std::endl;
		}

		// -------------------------------------------# Setup Dear ImGui context

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		io = ImGui::GetIO(); (void)io;
		ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
		ImGui_ImplOpenGL3_Init();

		//m_scene->getScenePvdClient()->setScenePvdFlags(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS | physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES | physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS);
	}
}

//-----------------------------------------------------------------------------
void Screen::ClearBuffers()
{
	glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);

	if (m_depthTest)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

}

//-----------------------------------------------------------------------------
void Screen::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

//-----------------------------------------------------------------------------
void Screen::DisplayGraphicsInfo()
{
	// Display graphics card info
	std::cout << (const char*)glGetString(GL_VENDOR) << std::endl;
	std::cout << (const char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << (const char*)glGetString(GL_VERSION) << std::endl;
	std::cout << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}

//-----------------------------------------------------------------------------
void Screen::DisplayExtensionsInfo()
{
	// Extensions
	
	GLint totalExtensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	for (int i = 0; i < totalExtensions; i++)
	{
		std::cout << "Extension #" << i + 1 << " " << glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}
}

//-----------------------------------------------------------------------------
int Screen::GetScreenWidth()
{
	return m_widht;
}

//-----------------------------------------------------------------------------
int Screen::GetScreenHeight()
{
	return m_height;
}

//-----------------------------------------------------------------------------
void Screen::SetDepthTest(bool flag)
{
	if(flag)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	m_depthTest = flag;
}

//-----------------------------------------------------------------------------
void Screen::SetBackgroundColor(glm::vec4 bgcolor)
{
	m_backgroundColor.r = bgcolor.r;
	m_backgroundColor.g = bgcolor.g;
	m_backgroundColor.b = bgcolor.b;
	m_backgroundColor.a = bgcolor.a;
}

//-----------------------------------------------------------------------------
void Screen::SetBackgroundColor(float r, float g, float b, float a)
{
	m_backgroundColor.r = r;
	m_backgroundColor.g = g;
	m_backgroundColor.b = b;
	m_backgroundColor.a = a;
}

//-----------------------------------------------------------------------------
void Screen::ImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

//-----------------------------------------------------------------------------
void Screen::ImGuiRender()
{
	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//-----------------------------------------------------------------------------
void Screen::ShutDown()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

