#include "../OpenglToolKit/WorldManager.h"
#include "../ImGuiToolKit/ImGuiManager.h"

#include "tests/Test.h"
#include "tests/Test1_ClearColor.h"
#include "tests/Test2_Triangle.h"
#include "tests/Test3_SquareAnimatedColor.h"
#include "tests/Test4_Texture2D.h"
#include "tests/Test5_MVP.h"
#include "tests/Test6_Cube.h"
#include "tests/Test7_SimpleBatching.h"
#include "tests/Test8_SimpleDynamicBatching.h"

#include "tests/Test9_GameObject.h"
#include "tests/Test10_Material.h"
#include "tests/Test12_BatchManager.h"
#include "tests/Test11_ZBuffer.h"
#include "tests/Test13_MeshBuilder.h"

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

        testMenu->RegisterTest<tests::Test1_ClearColor>("Test1_ClearColor");
        testMenu->RegisterTest<tests::Test2_Triangle>("Test2_Triangle");
        testMenu->RegisterTest<tests::Test3_SquareAnimatedColor>("Test3_SquareAnimatedColor");
        testMenu->RegisterTest<tests::Test4_Texture2D>("Test4_Texture2D");
        testMenu->RegisterTest<tests::Test5_MVP>("Test5_MVP");
        testMenu->RegisterTest<tests::Test6_Cube>("Test6_Cube");
        testMenu->RegisterTest<tests::Test7_SimpleBatching>("Test7_SimpleBatching");
        testMenu->RegisterTest<tests::Test8_SimpleDynamicBatching>("Test8_SimpleDynamicBatching");
        
        testMenu->RegisterTest<tests::Test9_GameObject>("Test9_GameObject");
        testMenu->RegisterTest<tests::Test10_Material>("Test10_Material");
        testMenu->RegisterTest<tests::Test11_ZBuffer>("Test11_ZBuffer");
        testMenu->RegisterTest<tests::Test12_BatchManager>("Test12_BatchManager");
        testMenu->RegisterTest<tests::Test13_MeshBuilder>("Test13_MeshBuilder");

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