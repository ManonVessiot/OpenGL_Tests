#pragma once

#include "Test.h"

#include <vector>

#include <glm/glm.hpp>

#include "../../Maze/Maze.h"
#include "../../Maze/Player.h"


namespace tests
{
    class Test15_MazeWithBullet : public Test
    {
        private:
            MazeGame::Maze m_Maze;
            MazeGame::Player m_Player;

            float m_EyesPos[3];
            float m_LookPos[3];
            float m_UpVec[3];

            int m_Moves[2];

            glm::vec3 m_Gravity;

        public:
            Test15_MazeWithBullet();
            ~Test15_MazeWithBullet();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;
    };
    
} // namespace tests