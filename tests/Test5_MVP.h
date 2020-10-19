#pragma once

#include "Test.h"

#include "../../easyGL/VertexArray.h"
#include "../../easyGL/IndexBuffer.h"
#include "../../easyGL/Shader.h"
#include "../../easyGL/Texture.h"
#include "../../easyGL/VertexBuffer.h"

#include <glm/glm.hpp>

#include <memory>

namespace tests
{
    class Test5_MVP : public Test
    {
        private:
            glm::vec3 m_CameraTranslation;
            glm::vec3 m_model1Translation;
            glm::vec3 m_model2Translation;
            
            glm::vec3 m_CameraRotation;
            glm::vec3 m_model1Rotation;
            glm::vec3 m_model2Rotation;

            glm::mat4 m_Proj;

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
            Test5_MVP();
            ~Test5_MVP();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

            void updateColor();
    };
    
} // namespace tests