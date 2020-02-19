#include "gamewindow.h"

using namespace Graphics;

static const char* Title = "Scratchpad";

static const int PosX = 50, PosY = 50, Width = 640, Height = 480;

static const char* VertexShaderFile = "vert.glsl";
static const char* FragmentShaderFile = "frag.glsl";

static const GLfloat VertexColours[] =
{
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
	1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
};

void GameWindow::HandleGLErrors(GLenum err)
{
	switch (err)
	{
	case GL_NO_ERROR:
		break;
	case GL_INVALID_ENUM:
		m_Logger.LogError("Invalid enum");
		break;
	case GL_INVALID_VALUE:
		m_Logger.LogError("Invalid value");
		break;
	case GL_INVALID_OPERATION:
		m_Logger.LogError("Invalid Operation");
		break;
	case GL_STACK_OVERFLOW:
		m_Logger.LogError("Stack Overflow");
		break;
	case GL_STACK_UNDERFLOW:
		m_Logger.LogError("Stack Underflow");
		break;
	case GL_OUT_OF_MEMORY:
		m_Logger.LogError("Out of memory");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		m_Logger.LogError("Invalid framebuffer operation");
		break;
	}
}

GameWindow::GameWindow() : m_Logger(Logger::Get())
{
	m_Window = SDL_CreateWindow(Title, PosX, PosY, Width, Height, SDL_WINDOW_OPENGL);
	m_GLContext = SDL_GL_CreateContext(m_Window);

	glewInit();

	m_ShaderProgram = m_ShaderLoader.GetShaderProgram(VertexShaderFile, FragmentShaderFile);
	m_AttributeCoord3d = glGetAttribLocation(m_ShaderProgram, "coord3d");
	m_AttributeColour = glGetAttribLocation(m_ShaderProgram, "colour");

	glGenBuffers(1, &m_VBO); // Bind vertices. Vertices of a cube

	glGenBuffers(1, &m_CBO); // Bind colours. A colour for each vertex
	glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColours), VertexColours, GL_STATIC_DRAW);
	glVertexAttribPointer(m_AttributeColour, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
	glGenBuffers(1, &m_IBO);

	glEnable(GL_DEPTH_TEST);  // Enabling Z buffer.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // GL_FRONT, GL_BACK, GL_FRONT_AND_BACK -> options for culling
	glDepthFunc(GL_LESS);

	// Model, View, Projection
	GenerateMVPMatrix(m_MVP);

	m_MatrixID = glGetUniformLocation(m_ShaderProgram, "mvp");

	glViewport(0, 0, Width, Height);
	glClearColor(0.9f, 0.9f, 0.9f, 0.f);

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

void GameWindow::AddDrawableObject(ObjModel* model)
{
	m_Models.push_back(model);
}

void GameWindow::Draw() // TOOD: Swap buffers
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_ShaderProgram);

	for (ObjModel *model : m_Models) // Draw each model we have a reference to
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model->m_Vertices), &model->m_Vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(m_AttributeCoord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); // GL draw elements knows to use what is bound to the ELEMENT_ARRAY_BUFFER
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->m_Indices), &model->m_Indices[0], GL_STATIC_DRAW);

		// AnimateMVP(m_MVP);

		glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &m_MVP[0][0]);

		// TODO: Draw the (eventual) draw queue here
		glEnableVertexAttribArray(m_AttributeCoord3d);
		glEnableVertexAttribArray(m_AttributeColour);

		glDrawElements(GL_TRIANGLES, model->m_IndexCount, GL_UNSIGNED_SHORT, (void*)0);

		glEnableVertexAttribArray(m_AttributeColour);
		glDisableVertexAttribArray(m_AttributeCoord3d);

		// TODO: Unbind buffers for safety here

	}
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

void GameWindow::AnimateMVP(mat4x4 mvp)
{
	float angle = SDL_GetTicks() / 1000.f * 45;
	vec3 axisY = { 0, 1, 0 };
	mat4x4 anim, identity;
	mat4x4_identity(identity);
	mat4x4_rotate(anim, identity, axisY[0], axisY[1], axisY[2], angle);
	mat4x4_mul(mvp, mvp, anim);
}
