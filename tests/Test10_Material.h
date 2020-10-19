#pragma once

#include "Test.h"

#include "../../OpenglToolKit/GameObject.h"

#include "../../easyGL/VertexArray.h"
#include "../../easyGL/IndexBuffer.h"
#include "../../easyGL/VertexBuffer.h"

#include <memory>

namespace tests
{
    class Test10_Material : public Test
    {
        private:
            OpenglToolKit::GameObject m_GameObject;
            
            float m_Trans[3];
            float m_Rot[3];
            float m_Scale[3];

            float m_TexOffset[2];
            float m_TexScale[2];
            
            std::unique_ptr<easyGL::VertexArray> m_VAO; 
            std::unique_ptr<easyGL::IndexBuffer> m_IndexBuffer;
            std::unique_ptr<easyGL::VertexBuffer> m_VB;

        public:
            Test10_Material();
            ~Test10_Material();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests