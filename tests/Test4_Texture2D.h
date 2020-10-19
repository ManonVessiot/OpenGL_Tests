#pragma once

#include "Test.h"

#include "../../easyGL/Renderer.h"
#include "../../easyGL/VertexArray.h"
#include "../../easyGL/VertexBufferLayout.h"
#include "../../easyGL/Texture.h"

#include <memory>

namespace tests
{
    class Test4_Texture2D : public Test
    {
        private:
            float m_R;
            float m_G;
            float m_B;
            float m_IncrementR;
            float m_IncrementG;
            float m_IncrementB;

            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            easyGL::Shader* m_Shader;
            easyGL::Texture* m_Texture;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;
            
        public:
            Test4_Texture2D();
            ~Test4_Texture2D();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            void updateColor();
    };
    
} // namespace tests