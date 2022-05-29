#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	UpdateDisplayList();
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}


void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	GetPlayerInput();

	GetKeyboardInput();
}

void PlayScene::GetPlayerInput()
{
	switch (m_pCurrentInputType)
	{
	case static_cast<int>(InputType::GAME_CONTROLLER):
	{
		// handle player movement with GameController
		if (SDL_NumJoysticks() > 0)
		{
			if (EventManager::Instance().GetGameController(0) != nullptr)
			{
				constexpr auto dead_zone = 10000;
				if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL > dead_zone)
				{
					
				}
				else if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL < -dead_zone)
				{
					
				}
				else
				{
					
				}
			}
		}
	}
	break;
	case static_cast<int>(InputType::KEYBOARD_MOUSE):
	{
		// handle player movement with mouse and keyboard
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			
		}
		else
		{
			
		}
	}
	break;
	case static_cast<int>(InputType::ALL):
	{
		if (SDL_NumJoysticks() > 0)
		{
			if (EventManager::Instance().GetGameController(0) != nullptr)
			{
				constexpr auto dead_zone = 10000;
				if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL > dead_zone
					|| EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
				{
					
				}
				else if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL < -dead_zone
					|| EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
				{
					
				}
				else
				{
					
				}
			}
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			
		}
		else
		{
			
		}
	}
	break;
	}
}

void PlayScene::GetKeyboardInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);
	
	m_pTarget = new Target(); // instantiates the target GameObject and allocates memory on the Heap
	AddChild(m_pTarget);

	m_pStarship = new Starship();
	m_pStarship->SetTargetPosition(m_pTarget->GetTransform()->position);
	AddChild(m_pStarship);
	m_pStarship->SetEnabled(false);
	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));

	ImGui::Separator();
	static float targetPosition[2] = { m_pTarget->GetTransform()->position.x, m_pTarget->GetTransform()->position.y };
	if (ImGui::SliderFloat2("Target Position", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->GetTransform()->position.x = targetPosition[0];
		m_pTarget->GetTransform()->position.y = targetPosition[1];
	}



	if (ImGui::Button("resrt target position")) {

		m_pTarget->Reset();
		targetPosition[0] = m_pTarget->GetTransform()->position.x;
		targetPosition[1] = m_pTarget->GetTransform()->position.y;
	}


	ImGui::Separator();
	static float shipPosition[2] = { m_pStarship->GetTransform()->position.x, m_pTarget->GetTransform()->position.y };
	if (ImGui::SliderFloat2("ship Position", shipPosition, 0.0f, 800.0f))
	{
		m_pStarship->GetTransform()->position.x = shipPosition[0];
		m_pStarship->GetTransform()->position.y = shipPosition[1];
	}



	if (ImGui::Button("resrt ship position")) {

		m_pStarship->Reset();
		
	}

	ImGui::Separator();
	static bool toggle_seek = m_pStarship->IsEnabled();
	if (ImGui::Checkbox("toggle seek", &toggle_seek)) {
		m_pStarship->SetEnabled(toggle_seek);
	}

	if (ImGui::Button("reset seek")) {
		m_pStarship->Reset();
		m_pStarship->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			m_pStarship->GetRigidBody()->acceleration= glm::vec2(0.0f, 0.0f);
			m_pStarship->GetRigidBody()->isColliding = false;
			m_pStarship->setMaxSpeed(20.0f);
			m_pStarship->setTurnRate(5.0f);
			m_pStarship->setAccelerationRate(2.0f);
			m_pStarship->SetCurrentHeading(0.0f);
			m_pStarship->SetEnabled(false);
			toggle_seek = false;

	}

	ImGui::Separator();

	float max_speed = m_pStarship->getMaxSpeed();
	if (ImGui::SliderFloat("max speed", &max_speed, 0.0f, 100.0f)) {
		m_pStarship->setMaxSpeed(max_speed);
	}

	ImGui::End();
}
