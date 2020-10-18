#pragma once

#include "Test.h"

#include "../../OpenglToolKit/GameObject.h"

#include "../../easyGL/Renderer.h"
#include "../../easyGL/VertexArray.h"
#include "../../easyGL/VertexBufferLayout.h"
#include "../../easyGL/Texture.h"

#include <memory>

namespace tests
{
    class Test1_GameObject : public Test
    {
        private:
            OpenglToolKit::GameObject m_GameObject;
            
            float m_Trans[3];
            float m_Rot[3];
            float m_Scale[3];
            
            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            easyGL::Shader* m_Shader;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test1_GameObject();
            ~Test1_GameObject();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests