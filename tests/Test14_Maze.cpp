#include "Test14_Maze.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../OpenglToolKit/WorldManager.h"
#include "../../OpenglToolKit/GameObjectManager.h"
#include "../../OpenglToolKit/BatchManager.h"

namespace tests {
    Test14_Maze::Test14_Maze()
        :m_Maze({
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        }),
        m_Player(1, 1, 0.25f, 5.0f, 5.0f),
        m_PlayerTranslation{0.0f, 0.0f, 0.0f},
        m_EyesPos{0.0f, 0.0f, 19.0f},
        m_LookPos{0.0f, 0.0f, 0.0f},
        m_UpVec{0.0f, 1.0f, 0.0f},
        m_Gravity(0.0f, 0.0f, -1.0f),
        m_Moves{0, 0}
    {
        /*
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        }
        */
        OpenglToolKit::BatchManager::Init(20, 2000, 1000);
    }

    Test14_Maze::~Test14_Maze()
    {
    }

    void Test14_Maze::OnUpdate(float deltaTime)
    {
        m_EyesPos[0] += - 0.1f * m_Moves[0];
        m_EyesPos[1] += - 0.1f * m_Moves[1];
        OpenglToolKit::WorldManager::Instance()->m_ViewMatrix = glm::lookAt(glm::vec3(m_EyesPos[0], m_EyesPos[1], m_EyesPos[2]),
                                                                glm::vec3(m_LookPos[0], m_LookPos[1], m_LookPos[2]),
                                                                glm::vec3(m_UpVec[0], m_UpVec[1], m_UpVec[2]));

        glm::vec3 position;
        glm::quat rotation;
        OpenglToolKit::WorldManager::Instance()->GetCameraTransform(position, rotation);
        m_Gravity = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        m_Gravity = 9.81f * glm::normalize(m_Gravity);
        std::cout << " m_Gravity : " << m_Gravity.x << ", " << m_Gravity.y << ", " << m_Gravity.z << std::endl;

        m_PlayerTranslation[0] = glm::dot(m_Gravity, glm::vec3(1.0f, 0.0f, 0.0f)) * deltaTime;
        m_PlayerTranslation[1] = glm::dot(m_Gravity, glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
        ////m_PlayerTranslation[2] = glm::dot(m_Gravity, glm::vec3(0.0f, 0.0f, 1.0f)) * deltaTime;

        m_Player.Translate(m_PlayerTranslation[0], m_PlayerTranslation[1], m_PlayerTranslation[2]);
    }

    void Test14_Maze::OnRender()
    {
        OpenglToolKit::GameObjectManager::Instance()->Render();
        OpenglToolKit::BatchManager::Instance()->EmptyAll();
    }

    void Test14_Maze::OnImGuiRender()
    {
        ImGui::DragFloat("z-Pose of eyes", &m_EyesPos[2], 0.1f);

        ImGui::DragInt("l-r", &m_Moves[0], 0.1f, -1.0f, 1.0f);
        ImGui::DragInt("d-u", &m_Moves[1], 0.1f, -1.0f, 1.0f);
    }
}