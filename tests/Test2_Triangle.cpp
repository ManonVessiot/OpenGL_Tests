#include "Test2_Triangle.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"

namespace tests {

    Test2_Triangle::Test2_Triangle()
        :m_Color {1.0f, 1.0f, 1.0f, 1.0f}
    {
        float positions[] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f
        };
        unsigned int indices[] = {
            0, 1, 2
        };
        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/BasicColor.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(positions, 3 * 2 * sizeof(float));

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(indices, 3);
        
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    Test2_Triangle::~Test2_Triangle()
    {
    }

    void Test2_Triangle::OnUpdate(float deltaTime)
    {    
    }

    void Test2_Triangle::OnRender()
    {   
        easyGL::Renderer::Clear();

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test2_Triangle::OnImGuiRender()
    {
        ImGui::ColorEdit4("Color", m_Color);
    }
}