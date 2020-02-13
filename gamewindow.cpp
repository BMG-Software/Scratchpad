#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

static const char* VertexShaderFile = "vert.glsl";
static const char* FragmentShaderFile = "frag.glsl";

/*
static const GLfloat Vertices[] = 
{
	-1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,	// triangle 1
	1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f,		// triangle 2 
	1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,		// triangle 3
	1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f,	-1.0f,-1.0f,-1.0f,		// triangle 4
	-1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f,	// triangle 5
	1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f,-1.0f,		// triangle 6
	-1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f,		// triangle 7
	1.0f, 1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f,		// triangle 8
	1.0f,-1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f,		// triangle 9
	1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f,		// triangle 10
	1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f,		// triangle 11
	1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f		// triangle 12


};

static const GLfloat VertexColours[] =
{
	0.583f,  0.771f,  0.014f, 0.609f,  0.115f,  0.436f, 0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f, 0.435f,  0.602f,  0.223f,	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f, 0.559f,  0.436f,  0.730f,	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f, 0.559f,  0.861f,  0.639f,	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f, 0.771f,  0.328f,  0.970f,	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f, 0.971f,  0.572f,  0.833f,	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f, 0.945f,  0.719f,  0.592f,	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f, 0.167f,  0.620f,  0.077f,	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f, 0.714f,  0.505f,  0.345f,	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f, 0.302f,  0.455f,  0.848f,	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f, 0.053f,  0.959f,  0.120f,	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f, 0.820f,  0.883f,  0.371f,	0.982f,  0.099f,  0.879f
};
*/

GameWindow::GameWindow() : m_Logger(Logger::Get())
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_OPENGL);
	m_GLContext = SDL_GL_CreateContext(m_Window);

	glewInit();

	m_ShaderProgram = m_ShaderLoader.GetShaderProgram(VertexShaderFile, FragmentShaderFile);
	m_AttributeCoord3d = glGetAttribLocation(m_ShaderProgram, "coord3d");
	m_AttributeColour = glGetAttribLocation(m_ShaderProgram, "colour");

	glGenBuffers(1, &m_VBO); // Bind vertices. Vertices of a cube
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeCoord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); // GL draw elements knows to use what is bound to the ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(/*indices*/), /*indices*/, GL_STATIC_DRAW);

	glGenBuffers(1, &m_CBO); // Bind colours. A colour for each vertex
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColours), VertexColours, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeColour, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnable(GL_DEPTH_TEST);  // Enabling Z buffer.
	glDepthFunc(GL_LESS);

	// Model, View, Projection
	GenerateMVPMatrix(m_MVP);

	m_MatrixID = glGetUniformLocation(m_ShaderProgram, "mvp");

	glViewport(0, 0, Width, Height);
	glClearColor(1.f, 0.f, 1.f, 0.f);

	m_Logger.LogDebug("Created game window");

}

GameWindow::~GameWindow()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteBuffers(1, &m_CBO);
	glDeleteProgram(m_ShaderProgram);
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
}

void GameWindow::Render(/*DrawableObject &obj*/) // TODO: Draw to back buffer
{
	// TODO: Lock rendering and drawing so we can't draw mid render (if we end up using threading this way...)

	// Render object

}

void GameWindow::Draw() // TOOD: Swap buffers
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_ShaderProgram);

	glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &m_MVP[0][0]);

	// TODO: Draw the (eventual) draw queue here
	glEnableVertexAttribArray(m_AttributeCoord3d);
	glEnableVertexAttribArray(m_AttributeColour);

	glDrawElements(GL_TRIANGLE_STRIP, 0/*TBD*/, GL_UNSIGNED_BYTE, (GLvoid*)0);

	//glDrawArrays(GL_TRIANGLES, 0, 12*3);
	glEnableVertexAttribArray(m_AttributeColour);
	glDisableVertexAttribArray(m_AttributeCoord3d);
	SDL_GL_SwapWindow(m_Window);
}

void GameWindow::GenerateMVPMatrix(mat4x4 mvp)
{
	mat4x4 projection;
	mat4x4_perspective(projection, 45.0f, float(Width)/float(Height), 0.1f, 100.0f);
	mat4x4 view;
	mat4x4_look_at(view, vec3{ 4.f, 3.f, 3.f }, vec3{ 0.f, 0.f, 0.f }, vec3{ 0.f, 1.f, 0.f });
	mat4x4 model;
	mat4x4_identity(model);
	mat4x4 intermediate;
	mat4x4_mul(intermediate, projection, view);
	mat4x4_mul(mvp, intermediate, model);
}
