#pragma once

#include "Test.h"

#include "../../OpenglToolKit/GameObject.h"

namespace tests
{
    class Test13_MeshBuilder : public Test
    {
        private:
            OpenglToolKit::GameObject m_GameObject1;
            OpenglToolKit::GameObject m_GameObject2;
            OpenglToolKit::GameObject m_GameObject3;
            
            bool m_active1;
            float m_Trans1[3];
            float m_Rot1[3];
            float m_Scale1[3];
            
            bool m_active2;
            float m_Trans2[3];
            float m_Rot2[3];
            float m_Scale2[3];
            
            bool m_active3;
            float m_Trans3[3];
            float m_Rot3[3];
            float m_Scale3[3];

        public:
            Test13_MeshBuilder();
            ~Test13_MeshBuilder();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests