#include "Test7_SimpleBatching.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"
#include "../../easyGL/TextureManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {
    Test7_SimpleBatching::Test7_SimpleBatching()
    {
        float positions[] = {
             0.0f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
             1.0f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             1.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
        };

        easyGL::Renderer::Blend(true);
        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/MVPTextureBatching.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(positions, 8 * 10 * sizeof(float));

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 1);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(indices, 2 * 6);
        
        m_Shader->Bind();
        int samplers[2] = {0, 1};
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);
        
        // MVP matrix        
        int height = 620;
        int width = 620;
        float miniSize = std::min(width, height);
        float borderLimit = 1.0f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        glm::mat4 proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", proj);

        m_Texture1 = easyGL::TextureManager::Instance()->CreateTexture("textures/zelda.png");
        m_Texture2 = easyGL::TextureManager::Instance()->CreateTexture("textures/white.png");
    }

    Test7_SimpleBatching::~Test7_SimpleBatching()
    {
    }

    void Test7_SimpleBatching::OnUpdate(float deltaTime)
    {    
    }

    void Test7_SimpleBatching::OnRender()
    {
        easyGL::Renderer::Clear();

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test7_SimpleBatching::OnImGuiRender()
    {        
    }
}