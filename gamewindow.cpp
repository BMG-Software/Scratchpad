#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

GameWindow & GameWindow::Get()
{
	static GameWindow gameWindow; // TODO: I need to properly understand how static works
	return gameWindow;
}

void GameWindow::Render(/*DrawableObject &obj*/)
{
	// TODO: Lock rendering and drawing so we can't draw mid render (if we end up using threading this way...)

	// Render object

}

void GameWindow::Draw()
{
	
	glViewport(0, 0, Width, Height);
	glClearColor(1.f, 0.f, 1.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the draw queue here

	SDL_GL_SwapWindow(m_Window);
}

GameWindow::GameWindow() : m_Logger(Logger::Get())
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_OPENGL);
	m_GLContext = SDL_GL_CreateContext(m_Window);

#ifdef _DEBUG
	m_Logger.LogDebug("Created GameWindow");
#endif

}

GameWindow::~GameWindow()
{
	SDL_DestroyWindow(m_Window);

#ifdef _DEBUG
	m_Logger.LogDebug("Destroyed GameWindow");
#endif
}
