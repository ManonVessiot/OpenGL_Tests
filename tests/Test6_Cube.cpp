#include "Test6_Cube.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"
#include "../../easyGL/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    Test6_Cube::Test6_Cube()
        :m_modelTranslation(0,0,-3), m_modelRotation(40, 40, 40)
    {
        float positions[] = {
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            1, 7, 6,
            6, 2, 1,

            0, 3, 5,
            5, 4, 0,

            3, 2, 6,
            6, 5, 3,

            0, 4, 7,
            7, 1, 0
        };

        easyGL::Renderer::Blend(true);
        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/MVPColor.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(positions, 8 * 3 * sizeof(float));

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(indices, 6 * 6);
        
        m_Shader->Bind();

        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
        int height = 620;
        int width = 620;
        /*
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f); */
        m_Proj = glm::perspective(
                glm::radians(60.0f),
                (float)width / height,
                0.1f,
                100.0f
            );
    }

    Test6_Cube::~Test6_Cube()
    {
        
    }

    void Test6_Cube::OnUpdate(float deltaTime)
    {    
    }

    void Test6_Cube::OnRender(){
        easyGL::Renderer::Clear();

        m_Shader->Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_modelTranslation);
        model = glm::rotate(model, glm::radians(m_modelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_modelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_modelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 mvp;
        mvp = m_Proj * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test6_Cube::OnImGuiRender()
    {
        ImGui::SliderFloat3("model1Translation", &m_modelTranslation.x, -10.0f, 1.0f);
        ImGui::SliderFloat3("model1Rotation", &m_modelRotation.x, -180.0f, 180.0f);
    }
}