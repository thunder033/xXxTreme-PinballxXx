#include "AppClass.h"
#include "GameObject.h"
#include "Flipper.h"
#include "Ball.h"
void App::InitWindow(String a_sWindowName)
{
	super::InitWindow("xXxTreme-PinballxXx"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void App::InitVariables(void)
{
	GameObject::Init();

	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, -7.f, 13.0f),//Camera position
		vector3(0.0f, -0.75f, 0.0f),//What Im looking at
		REAXISY);//What is up

	Table = new PinballTable();

	octree = new Octree(vector3(-5.f, -7.f, -10.f), vector3(5.f, 7.f, 2.f), 1);

	//GameObject* obj = new GameObject();
	//obj->Rotate(quaternion(vector3(45, 45, 45)));

	PrimitiveClass* cone = new PrimitiveClass();
	cone->GenerateCone(1, 1.5f, 10, REBLUE);

	obj2 = new Ball();
	obj2->Translate(vector3(3.25f, -2.f, 0));
	//obj2->Rotate(quaternion(vector3(0, 45, 0)));
	//obj2->SetOrigin(vector3(0, 0.5f, 0));

	flipper = new Flipper(false);
	flipper->Translate(vector3(-2.5f, -4.5f, 0.75f));
	flipperR = new Flipper(true);
	flipperR->Translate(vector3(1.f, -4.5f, 0.75f));

	plunger = new Plunger(vector3(3.5f, -5.4f, 0.75f), vector3(3.5f, 0.f, 0.75f));

	physicsTickTime = 1.0 / 95.0; // We don't do integration, so we have to set the physics tick rate to be _really_ high
	timeSinceLastPhysicsUpdate = 0.0;

	octree->GenerateTree();
}

void App::Update(void)
{

	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	octree->GenerateTree();
	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);

	//obj2->RotateTo(m_qArcBall);

	double deltaTime = m_pSystem->LapClock();

	timeSinceLastPhysicsUpdate += deltaTime;
	if (timeSinceLastPhysicsUpdate >= physicsTickTime)
	{
		int tickCount = 0;
		while (timeSinceLastPhysicsUpdate >= physicsTickTime)
		{
			++tickCount;
			timeSinceLastPhysicsUpdate -= physicsTickTime;
			for (auto* ent : Entity::GetInstances())
			{
				ent->PhysicsUpdate(physicsTickTime);
			}
		}

		if (tickCount > 4)
		{
			std::cout << "Warning: physics tick is running slow, had to tick " << tickCount << " times in a single frame!" << std::endl;
		}
	}

	GameObject::UpdateAll(deltaTime);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Number of Game Objects: ");
	m_pMeshMngr->PrintLine(std::to_string(GameObject::GetGameObjectCount()), REGREEN);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	m_pMeshMngr->Print("Number of Checks: ");
	m_pMeshMngr->PrintLine(std::to_string(GameObject::GetCheckCount()), REGREEN);
}

void App::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	octree->DrawOctree();

	matrix4 projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 view = m_pCameraMngr->GetViewMatrix();

	GameObject::RenderAll(projection, view);
	Table->Render(projection, view);
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void App::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	GameObject::ReleaseInstances();

	delete Table;
}