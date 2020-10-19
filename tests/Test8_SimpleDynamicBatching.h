#pragma once

#include "Test.h"

#include "../../easyGL/Renderer.h"
#include "../../easyGL/VertexArray.h"
#include "../../easyGL/VertexBufferLayout.h"
#include "../../easyGL/Texture.h"

#include <memory>

namespace tests
{
    struct TVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoords;
        float TexID;
    };

    class Test8_SimpleDynamicBatching : public Test
    {
        private:
            float m_PosQuad1[2];
            float m_PosQuad2[2];
            float m_PosQuad3[2];

            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            easyGL::Shader* m_Shader;
            easyGL::Texture* m_Texture1;
            easyGL::Texture* m_Texture2;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test8_SimpleDynamicBatching();
            ~Test8_SimpleDynamicBatching();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            static std::array<unsigned int, 6> CreateQuadIndices(unsigned int offsetCount);
            static std::array<TVertex, 4> CreateQuad(glm::vec3 cornerPos, float size, glm::vec4 color, float texID);
    };
    
} // namespace tests