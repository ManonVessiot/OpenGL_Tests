#include "Test5_MVP.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"
#include "../../easyGL/TextureManager.h"
#include "../../easyGL/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    Test5_MVP::Test5_MVP()
        :m_Proj(glm::mat4(1.0f)),
        m_CameraTranslation(0,0,0),
        m_model1Translation(-0.5f,0,0),
        m_model2Translation(0.5f,0,0),
        m_CameraRotation(0,0,0),
        m_model1Rotation(0,0,0),
        m_model2Rotation(0,0,0),
        m_R(0.0f), m_G(0.0f), m_B(0.0f), m_IncrementR(0.02f), m_IncrementG(0.01f), m_IncrementB(0.03f)
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        easyGL::Renderer::Blend(true);
        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/MVPTexture.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(positions, 4 * 4 * sizeof(float));

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VB, layout);
        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(indices, 6);
        
        m_Shader->Bind();

        m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        // MVP matrix        
        int height = 620;
        int width = 620;
        float miniSize = std::min(width, height);
        float borderLimit = 0.66f;
        float verticalLimit = (height / miniSize) * borderLimit;
        float horizontalLimit = (width / miniSize) * borderLimit;
        m_Proj = glm::ortho(-horizontalLimit, horizontalLimit, -verticalLimit, verticalLimit, -1.0f, 1.0f);

        m_Texture = easyGL::TextureManager::Instance()->CreateTexture("textures/zelda.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    Test5_MVP::~Test5_MVP()
    {
        
    }

    void Test5_MVP::OnUpdate(float deltaTime)
    {    
    }

    void Test5_MVP::OnRender(){
        easyGL::Renderer::Clear();

        m_Texture->Bind();
        m_Shader->Bind();
            
        // move camera
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model1 = glm::mat4(1.0f);
        glm::mat4 model2 = glm::mat4(1.0f);

        view = glm::translate(view, m_CameraTranslation);
        model1 = glm::translate(model1, m_model1Translation);
        model2 = glm::translate(model2, m_model2Translation);

        view = glm::rotate(view, glm::radians(m_CameraRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model1 = glm::rotate(model1, glm::radians(m_model1Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model2 = glm::rotate(model2, glm::radians(m_model2Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        view = glm::rotate(view, glm::radians(m_CameraRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model1 = glm::rotate(model1, glm::radians(m_model1Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model2 = glm::rotate(model2, glm::radians(m_model2Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

        view = glm::rotate(view, glm::radians(m_CameraRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model1 = glm::rotate(model1, glm::radians(m_model1Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = glm::rotate(model2, glm::radians(m_model2Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        updateColor();
        glm::mat4 mvp;

        // first object
        m_Shader->SetUniform4f("u_Color", m_R, m_G, m_B, 1.0f);
        mvp = m_Proj * view * model1;
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
            
        // second object
        m_Shader->SetUniform4f("u_Color", 1, 1, 1, 1.0f);
        mvp = m_Proj * view * model2;
        m_Shader->SetUniformMat4f("u_MVP", mvp);            
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test5_MVP::OnImGuiRender(){
        ImGui::SliderFloat3("cameraTranslation", &m_CameraTranslation.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("model1Translation", &m_model1Translation.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("model2Translation", &m_model2Translation.x, -1.0f, 1.0f);

        ImGui::SliderFloat3("cameraRotation", &m_CameraRotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat3("model1Rotation", &m_model1Rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat3("model2Rotation", &m_model2Rotation.x, -180.0f, 180.0f);
    }

    void Test5_MVP::updateColor(){    
        if (m_R > 1.0f){
            m_IncrementR *= -1;
        }
        else if (m_R < 0.0f){
            m_IncrementR *= -1;
        }

        if (m_G > 1.0f){
            m_IncrementG *= -1;
        }
        else if (m_G < 0.0f){
            m_IncrementG *= -1;
        }

        if (m_B > 1.0f){
            m_IncrementB *= -1;
        }
        else if (m_B < 0.0f){
            m_IncrementB *= -1;
        }
        m_R += m_IncrementR;
        m_G += m_IncrementG;
        m_B += m_IncrementB;
    }
}