#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

static const char* VertexShaderFile = "vert.glsl";
static const char* FragmentShaderFile = "frag.glsl";

static const GLfloat Vertices[] = 
{
	0.0f, 0.8f,
	-0.8f, -0.8f,
	0.8f, -0.8f
};

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
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: Draw the (eventual) draw queue here
	glEnableVertexAttribArray(m_AttributeCoord2d);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(m_AttributeCoord2d);
	SDL_GL_SwapWindow(m_Window);
}

GameWindow::GameWindow() : m_Logger(Logger::Get())
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_OPENGL);
	m_GLContext = SDL_GL_CreateContext(m_Window);

	glewInit();

	m_ShaderProgram = m_ShaderLoader.GetShaderProgram(VertexShaderFile, FragmentShaderFile);
	m_AttributeCoord2d = glGetAttribLocation(m_ShaderProgram, "coord2d");

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeCoord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(m_ShaderProgram);
	glViewport(0, 0, Width, Height);
	glClearColor(1.f, 0.f, 1.f, 0.f);

	m_Logger.LogDebug("Created game window");

}

GameWindow::~GameWindow()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_ShaderProgram);
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
}
