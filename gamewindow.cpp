#include "gamewindow.h"

#include <map>

using namespace Graphics;

static const char* Title = "Scratchpad";
static const int PosX = 50, PosY = 50, Width = 640, Height = 480;
static const char* VertexShaderFile = "vert.glsl";
static const char* FragmentShaderFile = "frag.glsl";


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
	if (m_AttributeCoord3d == -1)
	{
		m_Logger.LogError("Could not find 3D coord attribute");
	}

	m_AttributeTexture = glGetAttribLocation(m_ShaderProgram, "coordTex");
	if (m_AttributeTexture == -1)
	{
		m_Logger.LogError("Could not find Tex coord attribute");
	}

    m_AttributeNormal = glGetAttribLocation(m_ShaderProgram, "norm");
    if (m_AttributeNormal == -1)
    {
        m_Logger.LogError("Could not find normal attribute");
    }

	glGenBuffers(1, &m_VBO); // Bind vertices. Vertices of a cube
	glGenBuffers(1, &m_TexCoords);
	glGenBuffers(1, &m_IBO);

	glEnable(GL_DEPTH_TEST);  // Enabling Z buffer.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // GL_FRONT, GL_BACK, GL_FRONT_AND_BACK -> options for culling
	glDepthFunc(GL_LESS);

    m_Camera = nullptr; // Camera not setup yet TODO: add checks for non-setup camera

    m_3x3InvTransp = glGetUniformLocation(m_ShaderProgram, "m_3x3_inv_transp");
    if (m_3x3InvTransp == -1)
    {
        m_Logger.LogError("Could not find 3x3InvTransp");
    }

	m_ModelMatID = glGetUniformLocation(m_ShaderProgram, "model");
    m_ViewMatID = glGetUniformLocation(m_ShaderProgram, "view");
    m_ProjMatID = glGetUniformLocation(m_ShaderProgram, "projection");
	if (m_ModelMatID == -1 || m_ViewMatID == -1 || m_ProjMatID == -1)
	{
		m_Logger.LogError("Could not find mvp attributes");
	}

	glViewport(0, 0, Width, Height);
	glClearColor(0.9f, 0.9f, 0.9f, 0.f);

	m_Logger.LogDebug("Created game window");

}

GameWindow::~GameWindow()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteTextures(1, &m_TextureID);
	glDeleteProgram(m_ShaderProgram);
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
}

void Graphics::GameWindow::SetCamera(Camera *camera)
{
    m_Camera = camera;
    m_Camera->SetPosition(vec3{ 0.f, 0.f, 0.9f }); // Set camera to an initial position
    // Model, View, Projection
    UpdateMVPMatrix();

}

void GameWindow::AddDrawableObject(ObjModel* model)
{
	// Definitely move this to the per model drawing
    if (model->m_Material.m_TextureMap != nullptr) // We only want to map a texture if the model has one loaded
    {
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, model->m_Material.m_TextureMap->w, model->m_Material.m_TextureMap->h,
            0, GL_RGBA, GL_UNSIGNED_BYTE, model->m_Material.m_TextureMap->pixels);
    }
    else
    {
        glGenTextures(1, &m_TextureID);
        GLubyte data[] = { 255, 255, 0, 255 };
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    }
	m_Models.push_back(model);
}

void GameWindow::Draw() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_ShaderProgram);

	for (ObjModel *model : m_Models) // Draw each model we have a reference to
	{

        glActiveTexture(GL_TEXTURE0);
        glUniform1i(m_UniformTexture, 0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, model->m_Vertices.size() * sizeof(GLfloat), model->m_Vertices.data(), GL_DYNAMIC_DRAW);
		
        // TODO: Looks like all this can be done just once. Look into
        glVertexAttribPointer(m_AttributeCoord3d, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glVertexAttribPointer(m_AttributeTexture, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(m_AttributeNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
        // TODO: One of these for the normals handle in shader (also add this to the shader...)


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO); // GL draw elements knows to use what is bound to the ELEMENT_ARRAY_BUFFER
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->m_Indices.size() * sizeof(GLushort), model->m_Indices.data(), GL_DYNAMIC_DRAW);

        m_Camera->Rotate();
        UpdateMVPMatrix();

        mat4x4 invertedModel;
        mat4x4_invert(invertedModel, m_Model);
        mat4x4 transposed;
        mat4x4_transpose(transposed, invertedModel);
        
        vec3 mat3x3[3]; // TODO: fix this dirty mat4x4 to 3x3 conversion
        memcpy(mat3x3[0], transposed[0], sizeof(vec3));
        memcpy(mat3x3[1], transposed[1], sizeof(vec3));
        memcpy(mat3x3[2], transposed[2], sizeof(vec3));

        glUniformMatrix3fv(m_3x3InvTransp, 1, GL_FALSE, &mat3x3[0][0]);

		glUniformMatrix4fv(m_ModelMatID, 1, GL_FALSE, &m_Model[0][0]);
        glUniformMatrix4fv(m_ViewMatID, 1, GL_FALSE, &m_View[0][0]);
        glUniformMatrix4fv(m_ProjMatID, 1, GL_FALSE, &m_Projection[0][0]);

		glEnableVertexAttribArray(m_AttributeCoord3d);
        glEnableVertexAttribArray(m_AttributeTexture);
        glEnableVertexAttribArray(m_AttributeNormal);

		glDrawElements(GL_TRIANGLES, (GLsizei)model->m_Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

        glDisableVertexAttribArray(m_AttributeNormal);
        glEnableVertexAttribArray(m_AttributeTexture);
        glDisableVertexAttribArray(m_AttributeCoord3d);

		// TODO: Unbind buffers for safety here
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_IBO);

	}
	SDL_GL_SwapWindow(m_Window);
}

void GameWindow::UpdateMVPMatrix()
{
    // Generate the matrices

    // Projection
	mat4x4_perspective(m_Projection, 45.0f, float(Width)/float(Height), 0.1f, 10.0f);
    // View
    m_Camera->GetWorldToViewMatrix(m_View); 
    // Model
    mat4x4_translate(m_Model, 0.f, 0.f, -1.f);
	
    
    /*mat4x4 intermediate;
	mat4x4_mul(intermediate, projection, view); // TODO: offload onto the GPU
	mat4x4_mul(mvp, intermediate, model);*/
}
