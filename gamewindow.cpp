#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

static const char* VertexShaderFile = "vert.glsl";
static const char* FragmentShaderFile = "frag.glsl";

static const GLfloat Vertices[] = 
{
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f


};

static const GLfloat VertexColours[] =
{
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

void GameWindow::Render(/*DrawableObject &obj*/) // TODO: Draw to back buffer
{
	// TODO: Lock rendering and drawing so we can't draw mid render (if we end up using threading this way...)

	// Render object

}

void GameWindow::Draw() // TOOD: Swap buffers
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: Draw the (eventual) draw queue here
	glEnableVertexAttribArray(m_AttributeCoord3d);
	glEnableVertexAttribArray(m_AttributeColour);
	glDrawArrays(GL_TRIANGLES, 0, 12*3);
	glEnableVertexAttribArray(m_AttributeColour);
	glDisableVertexAttribArray(m_AttributeCoord3d);
	SDL_GL_SwapWindow(m_Window);
}

GameWindow::GameWindow() : m_Logger(Logger::Get())
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_OPENGL);
	m_GLContext = SDL_GL_CreateContext(m_Window);

	glewInit();

	m_ShaderProgram = m_ShaderLoader.GetShaderProgram(VertexShaderFile, FragmentShaderFile);
	m_AttributeCoord3d = glGetAttribLocation(m_ShaderProgram, "coord3d");
	m_AttributeColour = glGetAttribLocation(m_ShaderProgram, "colour");

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeCoord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_CBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColours), VertexColours, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeColour, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);  // Enabling Z buffer.
	glDepthFunc(GL_LESS);

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
