#include "../OpenglToolKit/WorldManager.h"
#include "../ImGuiToolKit/ImGuiManager.h"

#include "tests/Test.h"
#include "tests/Test1_GameObject.h"
#include "tests/Test2_Material.h"
#include "tests/Test4_BatchManager.h"
#include "tests/Test3_ZBuffer.h"
#include "tests/Test5_MeshBuilder.h"

int main(int argc, char const *argv[])
{
    OpenglToolKit::WorldManager* worldManager = OpenglToolKit::WorldManager::Instance();
    ImGuiToolKit::ImGuiManager* imGuiManager = ImGuiToolKit::ImGuiManager::Instance();

    int height = 620;
    int width = 620;
    if (!worldManager->Init(width, height)){
        return -1;
    }
    OpenglToolKit::WorldManager::Instance()->m_ProjectionMatrix = glm::perspective(
        glm::radians(60.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        1.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );
    OpenglToolKit::WorldManager::Instance()->m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    imGuiManager->Init_imgui(worldManager->m_Window);
    {
        tests::Test* currentTest = nullptr;
        tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<tests::Test1_GameObject>("Test1_GameObject");
        testMenu->RegisterTest<tests::Test2_Material>("Test2_Material");
        testMenu->RegisterTest<tests::Test3_ZBuffer>("Test3_ZBuffer");
        testMenu->RegisterTest<tests::Test4_BatchManager>("Test4_BatchManager");
        testMenu->RegisterTest<tests::Test5_MeshBuilder>("Test5_MeshBuilder");

        // Loop until the user closes the window
        while (!worldManager->CheckCloseFlag())
        {
            std::cout << std::endl << "----------Start----------" << std::endl;
            worldManager->InitFrame();
            imGuiManager->InitFrame_imgui();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                imGuiManager->StartWindow("Test");
                if (currentTest != testMenu && imGuiManager->CreateButton("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                imGuiManager->EndWindow();
            }

            imGuiManager->Render_imgui();

            worldManager->EndFrame();
            std::cout << "-----------End-----------" << std::endl;
        }
        delete currentTest;
        if (currentTest != testMenu){
            delete testMenu;
        }
    }
    imGuiManager->Destroy_imgui();
    worldManager->Terminate();
    return 0;
}