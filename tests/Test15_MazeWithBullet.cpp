#include "Test15_MazeWithBullet.h"

#include "../../ImGuiToolKit/vendor/imgui/imgui.h"

#include "../../OpenglToolKit/WorldManager.h"
#include "../../OpenglToolKit/GameObjectManager.h"
#include "../../OpenglToolKit/BatchManager.h"


namespace tests {
    Test15_MazeWithBullet::Test15_MazeWithBullet()
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
        m_EyesPos{0.0f, 0.0f, 19.0f},
        m_LookPos{0.0f, 0.0f, 0.0f},
        m_UpVec{0.0f, 1.0f, 0.0f},
        m_Gravity(0.0f, 0.0f, -1.0f),
        m_Moves{0, 0},

        localInertia(0,0,0),
        mass(0.5f),

        localInertiaSol(0,0,0),
        massSol(0)
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

        std::cout << "Initializing Bullet ..." << std::endl;
        myCollisionConfiguration = new btDefaultCollisionConfiguration();
        myDispatcher = new	btCollisionDispatcher(myCollisionConfiguration);
        myBroadphase = new btDbvtBroadphase();
        mySequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver;
        myWorld = new btDiscreteDynamicsWorld(myDispatcher,myBroadphase,mySequentialImpulseConstraintSolver,myCollisionConfiguration);
        myWorld->setGravity( btVector3(0,-9.81f,0) );

        shape = new btBoxShape( btVector3(1,1,1) );

        myTransform.setIdentity();
        myTransform.setOrigin( btVector3(10,5,0) );
        if ( mass )
	        shape->calculateLocalInertia( mass, localInertia );
        
        myMotionState = new btDefaultMotionState(myTransform);
        myBoxRigidBodyConstructionInfo = new btRigidBody::btRigidBodyConstructionInfo( mass, myMotionState, shape, localInertia );
        body = new btRigidBody(*myBoxRigidBodyConstructionInfo);

        myWorld->addRigidBody(body);

        shape_sol = new btBoxShape( btVector3(10,1,10) );

        myTransform.setIdentity();

        // Position du sol
        myTransform.setOrigin( btVector3(0,0,0) );

        myMotionState_Sol = new btDefaultMotionState(myTransform);

        sol_info = new btRigidBody::btRigidBodyConstructionInfo( massSol, myMotionState_Sol, shape_sol, localInertiaSol );

        body_sol = new btRigidBody(*sol_info);

        // On ajoute le sol dans le monde Bullet
        myWorld->addRigidBody(body_sol);

        std::cout << "Bullet initialized !" << std::endl;
    }

    Test15_MazeWithBullet::~Test15_MazeWithBullet()
    {
        delete myCollisionConfiguration;
        delete myDispatcher;
        delete myBroadphase;
        delete mySequentialImpulseConstraintSolver;
        delete myWorld;

        delete shape;
        delete myMotionState;
        delete myBoxRigidBodyConstructionInfo;
        delete body;

        delete shape_sol;
        delete myMotionState_Sol;
        delete sol_info;
        delete body_sol;
    }

    void Test15_MazeWithBullet::OnUpdate(float deltaTime)
    {
        if ( myWorld )
	        myWorld->stepSimulation( deltaTime );

        myMotionState->m_graphicsWorldTrans.getOpenGLMatrix( matrix );

        //m_Player.SetTransform((float*)(&matrix[0]));

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
    }

    void Test15_MazeWithBullet::OnRender()
    {
        OpenglToolKit::GameObjectManager::Instance()->Render();
        OpenglToolKit::BatchManager::Instance()->EmptyAll();
    }

    void Test15_MazeWithBullet::OnImGuiRender()
    {
        ImGui::DragFloat("z-Pose of eyes", &m_EyesPos[2], 0.1f);

        ImGui::DragInt("l-r", &m_Moves[0], 0.1f, -1.0f, 1.0f);
        ImGui::DragInt("d-u", &m_Moves[1], 0.1f, -1.0f, 1.0f);
    }
}