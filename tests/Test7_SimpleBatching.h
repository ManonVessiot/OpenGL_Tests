#pragma once

#include "Test.h"

#include "../../easyGL/Renderer.h"
#include "../../easyGL/VertexArray.h"
#include "../../easyGL/VertexBufferLayout.h"
#include "../../easyGL/Texture.h"

#include <memory>

namespace tests
{
    class Test7_SimpleBatching : public Test
    {
        private:
            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            easyGL::Shader* m_Shader;
            easyGL::Texture* m_Texture1;
            easyGL::Texture* m_Texture2;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test7_SimpleBatching();
            ~Test7_SimpleBatching();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests