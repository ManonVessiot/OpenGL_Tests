#pragma once

#include "Test.h"

#include "../../OpenglToolKit/GameObject.h"

#include "../../easyGL/VertexArray.h"
#include "../../easyGL/IndexBuffer.h"
#include "../../easyGL/VertexBuffer.h"

#include <memory>

namespace tests
{
    class Test11_ZBuffer : public Test
    {
        private:
            OpenglToolKit::GameObject m_GameObject1;
            OpenglToolKit::GameObject m_GameObject2;
            
            float m_Trans1[3];
            float m_Rot1[3];
            float m_Scale1[3];
            
            float m_Trans2[3];
            float m_Rot2[3];
            float m_Scale2[3];
            
            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test11_ZBuffer();
            ~Test11_ZBuffer();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests