#include "Test1_GameObject.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"
#include "../../easyGL/Renderer.h"

namespace tests {
    Test1_GameObject::Test1_GameObject()
        :m_Trans{0.0f, 0.0f, 0.0f},
         m_Rot{0.0f, 0.0f, 0.0f},
         m_Scale{1.0f, 1.0f, 1.0f}
    {        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/BasicColor.shader");
        
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
        
        m_Shader->Bind();

        m_GameObject.m_Mesh.Clear();
        m_GameObject.m_Mesh.AddVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject.m_Mesh.AddVertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f));
        m_GameObject.m_Mesh.AddVertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f));
        m_GameObject.m_Mesh.AddVertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec4(0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f));

        m_GameObject.m_Mesh.AddTriangle(0, 1, 2);
        m_GameObject.m_Mesh.AddTriangle(2, 3, 0);
    }

    Test1_GameObject::~Test1_GameObject()
    {
    }

    void Test1_GameObject::OnUpdate(float deltaTime)
    {
        m_GameObject.m_Transform.m_Position = glm::vec3(m_Trans[0], m_Trans[1], m_Trans[2]);
        m_GameObject.m_Transform.m_Rotation = glm::quat(glm::vec3(glm::radians(m_Rot[0]), glm::radians(m_Rot[1]), glm::radians(m_Rot[2])));
        m_GameObject.m_Transform.m_Scale = glm::vec3(m_Scale[0], m_Scale[1], m_Scale[2]);
        glm::mat4 transformMatrix = m_GameObject.m_Transform.GetTransformMatrix();

        unsigned int numberOfVertex = m_GameObject.m_Mesh.m_Vertices.size();

        std::vector<OpenglToolKit::VertexData> vertices;
        for (int i = 0; i < numberOfVertex; i++){
            vertices.push_back(m_GameObject.m_Mesh.m_Vertices[i]);
            vertices[i].Position = transformMatrix * glm::vec4(vertices[i].Position, 1.0f);       
        }

        m_VB->Bind();
        m_VB->WriteData(0, numberOfVertex * sizeof(OpenglToolKit::VertexData), vertices.data()); // write vertices in VertexBuffer
        
        unsigned int * indices = m_GameObject.m_Mesh.m_Triangles.data();

        m_IndexBuffer->Bind();
        m_IndexBuffer->WriteData(0, m_GameObject.m_Mesh.m_Triangles.size(), indices); // write indices in IndexBuffer
    }

    void Test1_GameObject::OnRender()
    {
        easyGL::Renderer::Clear();

        m_Shader->Bind();
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test1_GameObject::OnImGuiRender()
    {
        ImGui::DragFloat3("Translation", m_Trans, 0.1f);
        ImGui::DragFloat3("Rotation", m_Rot, 0.1f);
        ImGui::DragFloat3("Scale", m_Scale, 0.1f);
    }
}