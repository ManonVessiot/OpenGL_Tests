#pragma once

#include "Test.h"

#include "../../easyGL/Renderer.h"
#include "../../easyGL/VertexArray.h"
#include "../../easyGL/VertexBufferLayout.h"
#include "../../easyGL/Texture.h"

#include <memory>

namespace tests
{
    class Test3_SquareAnimatedColor : public Test
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
            std::unique_ptr<easyGL::VertexBuffer> m_VB;
            
        public:
            Test3_SquareAnimatedColor();
            ~Test3_SquareAnimatedColor();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            void updateColor();
    };
    
} // namespace tests