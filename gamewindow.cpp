#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

GameWindow & Graphics::GameWindow::Get()
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

	// Draw renderer contents to the screen
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_Renderer);


	SDL_RenderPresent(m_Renderer);
}

GameWindow::GameWindow()
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_SHOWN /*SDL_WINDOW_OPENGL*/);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
}

GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}
