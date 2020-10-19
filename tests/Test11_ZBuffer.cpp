#include "Test11_ZBuffer.h"


#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../OpenglToolKit/MaterialManager.h"

#include "../../easyGL/TextureManager.h"
#include "../../easyGL/Renderer.h"

namespace tests {
    Test11_ZBuffer::Test11_ZBuffer()
        :m_Trans1{0.0f, 0.0f, 0.0f},
         m_Rot1{0.0f, 0.0f, 0.0f},
         m_Scale1{1.0f, 1.0f, 1.0f},

         m_Trans2{0.0f, 0.0f, 0.0f},
         m_Rot2{0.0f, 0.0f, 0.0f},
         m_Scale2{1.0f, 1.0f, 1.0f}
    {
        glEnable(GL_DEPTH_TEST);
        
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(nullptr, 300 * sizeof(OpenglToolKit::VertexData), GL_DYNAMIC_DRAW); // allocate memory for 300 vertex

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 4);

        m_VAO->AddBuffer(*m_VB, layout);

        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(nullptr, 100 * 3, GL_DYNAMIC_DRAW); // allocate memory for 100 triangles
        
        m_GameObject1.m_Mesh.Clear();
        m_GameObject1.m_Mesh.AddVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject1.m_Mesh.AddVertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject1.m_Mesh.AddVertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f));
        m_GameObject1.m_Mesh.AddVertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f));

        m_GameObject1.m_Mesh.AddTriangle(0, 1, 2);
        m_GameObject1.m_Mesh.AddTriangle(2, 3, 0);

        m_GameObject1.m_Material = OpenglToolKit::MaterialManager::Instance()->CreateMaterial("shaders/ShaderBase.shader");
        m_GameObject1.m_Material->SetMainColor(1.0f, 0.0f, 1.0f, 1.0f);        
        
        m_GameObject1.m_Material->SetMainTexture(easyGL::TextureManager::Instance()->CreateTexture("textures/white.png"));
        
        /////////

        m_GameObject2.m_Mesh.Clear();
        m_GameObject2.m_Mesh.AddVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject2.m_Mesh.AddVertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject2.m_Mesh.AddVertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f));
        m_GameObject2.m_Mesh.AddVertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f));

        m_GameObject2.m_Mesh.AddTriangle(0, 1, 2);
        m_GameObject2.m_Mesh.AddTriangle(2, 3, 0);

        m_GameObject2.m_Material = OpenglToolKit::MaterialManager::Instance()->CreateMaterial("shaders/ShaderBase.shader");
        m_GameObject2.m_Material->SetMainColor(1.0f, 1.0f, 0.0f, 1.0f);        
        
        m_GameObject2.m_Material->SetMainTexture(easyGL::TextureManager::Instance()->CreateTexture("textures/white.png"));
    }

    Test11_ZBuffer::~Test11_ZBuffer()
    {
    }

    void Test11_ZBuffer::OnUpdate(float deltaTime)
    {
        m_GameObject1.m_Transform.m_Position = glm::vec3(m_Trans1[0], m_Trans1[1], m_Trans1[2]);
        m_GameObject1.m_Transform.m_Rotation = glm::quat(glm::vec3(glm::radians(m_Rot1[0]), glm::radians(m_Rot1[1]), glm::radians(m_Rot1[2])));
        m_GameObject1.m_Transform.m_Scale = glm::vec3(m_Scale1[0], m_Scale1[1], m_Scale1[2]);
        /////////
        m_GameObject2.m_Transform.m_Position = glm::vec3(m_Trans2[0], m_Trans2[1], m_Trans2[2]);
        m_GameObject2.m_Transform.m_Rotation = glm::quat(glm::vec3(glm::radians(m_Rot2[0]), glm::radians(m_Rot2[1]), glm::radians(m_Rot2[2])));
        m_GameObject2.m_Transform.m_Scale = glm::vec3(m_Scale2[0], m_Scale2[1], m_Scale2[2]);
    }

    void Test11_ZBuffer::OnRender()
    {
        easyGL::Renderer::Clear();
        {            
            glm::mat4 transformMatrix = m_GameObject1.m_Transform.GetTransformMatrix();

            unsigned int numberOfVertex = m_GameObject1.m_Mesh.m_Vertices.size();

            std::vector<OpenglToolKit::VertexData> vertices;
            for (int i = 0; i < numberOfVertex; i++){
                vertices.push_back(m_GameObject1.m_Mesh.m_Vertices[i]);
                vertices[i].Position = transformMatrix * glm::vec4(vertices[i].Position, 1.0f);       
            }

            m_VB->Bind();
            m_VB->WriteData(0, numberOfVertex * sizeof(OpenglToolKit::VertexData), vertices.data()); // write vertices in VertexBuffer
            
            unsigned int * indices = m_GameObject1.m_Mesh.m_Triangles.data();

            m_IndexBuffer->Bind();
            m_IndexBuffer->WriteData(0, m_GameObject1.m_Mesh.m_Triangles.size(), indices); // write indices in IndexBuffer

            m_GameObject1.m_Material->Bind();
            easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *(m_GameObject1.m_Material->GetShader()));
        }        
        {
            glm::mat4 transformMatrix = m_GameObject2.m_Transform.GetTransformMatrix();

            unsigned int numberOfVertex = m_GameObject2.m_Mesh.m_Vertices.size();

            std::vector<OpenglToolKit::VertexData> vertices;
            for (int i = 0; i < numberOfVertex; i++){
                vertices.push_back(m_GameObject2.m_Mesh.m_Vertices[i]);
                vertices[i].Position = transformMatrix * glm::vec4(vertices[i].Position, 1.0f);       
            }

            m_VB->Bind();
            m_VB->WriteData(0, numberOfVertex * sizeof(OpenglToolKit::VertexData), vertices.data()); // write vertices in VertexBuffer
            
            unsigned int * indices = m_GameObject2.m_Mesh.m_Triangles.data();

            m_IndexBuffer->Bind();
            m_IndexBuffer->WriteData(0, m_GameObject2.m_Mesh.m_Triangles.size(), indices); // write indices in IndexBuffer

            m_GameObject2.m_Material->Bind();
            easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *(m_GameObject2.m_Material->GetShader()));
        }
    }

    void Test11_ZBuffer::OnImGuiRender()
    {
        ImGui::DragFloat3("Translation1", m_Trans1, 0.1f);
        ImGui::DragFloat3("Rotation1", m_Rot1, 0.1f);
        ImGui::DragFloat3("Scale1", m_Scale1, 0.1f);

        ImGui::DragFloat3("Translation2", m_Trans2, 0.1f);
        ImGui::DragFloat3("Rotation2", m_Rot2, 0.1f);
        ImGui::DragFloat3("Scale2", m_Scale2, 0.1f);
    }
}