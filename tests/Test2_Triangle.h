#pragma once

#include "Test.h"

#include "../../easyGL/VertexArray.h"
#include "../../easyGL/IndexBuffer.h"
#include "../../easyGL/Shader.h"
#include "../../easyGL/VertexBuffer.h"

#include <memory>

namespace tests
{
    class Test2_Triangle : public Test
    {
        private:
            float m_Color[4];

            std::unique_ptr<easyGL::VertexArray> m_VAO;
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            easyGL::Shader* m_Shader;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test2_Triangle();
            ~Test2_Triangle();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests