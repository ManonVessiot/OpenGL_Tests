#include "Test1_ClearColor.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../easyGL/Renderer.h"

namespace tests {
    Test1_ClearColor::Test1_ClearColor(float color[])
        :Test1_ClearColor(color[0], color[1], color[2], color[3])
    {
    }

    Test1_ClearColor::Test1_ClearColor(float v0, float v1, float v2, float v3)
        :m_ClearColor {v0, v1, v2, v3}
    {
    }

    Test1_ClearColor::~Test1_ClearColor()
    {
    }

    void Test1_ClearColor::OnUpdate(float deltaTime)
    {    
    }

    void Test1_ClearColor::OnRender(){
        easyGL::Renderer::Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    }

    void Test1_ClearColor::OnImGuiRender(){
        ImGui::ColorEdit4("Clear color", m_ClearColor);
    }
}