#pragma once

#include "Test.h"

namespace tests
{
    class Test1_ClearColor : public Test
    {
        private:
            float m_ClearColor[4];

        public:
            Test1_ClearColor(float color[]);
            Test1_ClearColor(float v0 = 0.2f, float v1 = 0.3f, float v2 = 0.8f, float v3 = 1.0f);
            ~Test1_ClearColor();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests