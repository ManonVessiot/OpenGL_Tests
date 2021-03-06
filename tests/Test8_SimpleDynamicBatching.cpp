#include "Test8_SimpleDynamicBatching.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/ShaderManager.h"
#include "../../easyGL/TextureManager.h"
#include "../../easyGL/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tests {

    std::array<TVertex, 4> Test8_SimpleDynamicBatching::CreateQuad(glm::vec3 cornerPos, float size, glm::vec4 color, float texID){
        TVertex v0;
        v0.Position = cornerPos;
        v0.Color = color;
        v0.TexCoords = glm::vec2(0, 0);
        v0.TexID = texID;

        TVertex v1;
        v1.Position = glm::vec3(cornerPos.x + size, cornerPos.y, cornerPos.z);
        v1.Color = color;
        v1.TexCoords = glm::vec2(1, 0);
        v1.TexID = texID;

        TVertex v2;
        v2.Position = glm::vec3(cornerPos.x + size, cornerPos.y + size, cornerPos.z);
        v2.Color = color;
        v2.TexCoords = glm::vec2(1, 1);
        v2.TexID = texID;

        TVertex v3;
        v3.Position = glm::vec3(cornerPos.x, cornerPos.y + size, cornerPos.z);
        v3.Color = color;
        v3.TexCoords = glm::vec2(0, 1);
        v3.TexID = texID;

        return {v0, v1, v2, v3};
    }

    std::array<unsigned int, 6> Test8_SimpleDynamicBatching::CreateQuadIndices(unsigned int offsetCount){
        unsigned int offset = offsetCount * 4;
        return {0+offset, 1+offset, 2+offset, 2+offset, 3+offset, 0+offset};
    }


    Test8_SimpleDynamicBatching::Test8_SimpleDynamicBatching()
        :m_PosQuad1{-1.50f, -0.50f},
         m_PosQuad2{-0.25f, -0.25f},
         m_PosQuad3{-1.00f, -0.50f}
    {
        easyGL::Renderer::Blend(true);
        
        m_Shader = easyGL::ShaderManager::Instance()->GetSaher("shaders/MVPTextureBatching.shader");
        m_VAO = std::make_unique<easyGL::VertexArray>();
        m_VB = std::make_unique<easyGL::VertexBuffer>(nullptr, sizeof(TVertex) * 1000, GL_DYNAMIC_DRAW); // allocate memory for 1000 vertex

        easyGL::VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 3);
        layout.Push(GL_FLOAT, 4);
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 1);

        m_VAO->AddBuffer(*m_VB, layout);

        m_IndexBuffer = std::make_unique<easyGL::IndexBuffer>(nullptr, 5 * 6, GL_DYNAMIC_DRAW); // allocate memory for 5 quads
        
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

    Test8_SimpleDynamicBatching::~Test8_SimpleDynamicBatching()
    {
    }

    void Test8_SimpleDynamicBatching::OnUpdate(float deltaTime)
    {
        // create 3 quads
        std::vector<std::array<TVertex, 4>> quads;
        quads.push_back(CreateQuad(glm::vec3(m_PosQuad1[0], m_PosQuad1[1], 0.0f), 1.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), 1.0f));
        quads.push_back(CreateQuad(glm::vec3(m_PosQuad2[0], m_PosQuad2[1], 0.0f), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f));
        quads.push_back(CreateQuad(glm::vec3(m_PosQuad3[0], m_PosQuad3[1], 0.0f), 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.0f));

        std::vector<std::array<unsigned int, 6>> indicesList; // array for the quads's indices
        
        // fusion quads for VertexBuffer
        TVertex vertices[4 * quads.size()];
        unsigned int offsetQuad = 0;
        for (int i = 0; i < quads.size(); i++){
            indicesList.push_back(CreateQuadIndices(i)); // populate array of the quads's indices

            std::array<TVertex, 4> quad = quads[i];
            memcpy(vertices + offsetQuad, quad.data(), quad.size() * sizeof(TVertex));
            offsetQuad += quad.size();
        }

        m_VB->Bind();
        m_VB->WriteData(0, sizeof(vertices), vertices); // write vertices in VertexBuffer

        // fusion indices of quads for IndexBuffer
        unsigned int indices[6 * indicesList.size()];
        unsigned int offsetIndices = 0;
        for (std::array<unsigned int, 6> indice : indicesList){
            memcpy(indices + offsetIndices, indice.data(), indice.size() * sizeof(TVertex));
            offsetIndices += indice.size();
        }

        m_IndexBuffer->Bind();
        m_IndexBuffer->WriteData(0, 6 * indicesList.size(), indices); // write indices in IndexBuffer
    }

    void Test8_SimpleDynamicBatching::OnRender()
    {
        easyGL::Renderer::Clear();

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        easyGL::Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void Test8_SimpleDynamicBatching::OnImGuiRender()
    {
        ImGui::DragFloat2("Quad 1 Position", m_PosQuad1, 0.1f);
        ImGui::DragFloat2("Quad 2 Position", m_PosQuad2, 0.1f);
        ImGui::DragFloat2("Quad 3 Position", m_PosQuad3, 0.1f);
    }
}