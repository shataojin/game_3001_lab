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

	// Lab 2 Game Objects
	m_pTarget = new Target();
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

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::Begin(m_guiTitle.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));

	ImGui::Separator();

	static bool toggle_seek = m_pStarship->IsEnabled();
	if (ImGui::Checkbox("Toggle Seek", &toggle_seek))
	{
		m_pStarship->SetEnabled(toggle_seek);
	}

	if (ImGui::Button("Reset Seek"))
	{
		m_pStarship->Reset();
		m_pStarship->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pStarship->GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		m_pStarship->GetRigidBody()->isColliding = false;
		m_pStarship->SetMaxSpeed(20.0f);
		m_pStarship->SetTurnRate(5.0f);
		m_pStarship->SetAccelerationRate(2.0f);
		m_pStarship->SetCurrentHeading(0.0f);
		m_pStarship->SetEnabled(false);

		toggle_seek = false;
	}

	ImGui::Separator();

	// Expose properties of ship
	static float max_speed = m_pStarship->GetMaxSpeed();
	if (ImGui::SliderFloat("Max Speed", &max_speed, 0.0f, 100.0f))
	{
		m_pStarship->SetMaxSpeed(max_speed);
	}
	static float acceleration = m_pStarship->GetAccelerationRate();
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration, 0.0f, 50.0f))
	{
		m_pStarship->SetAccelerationRate(acceleration);
		m_pStarship->GetRigidBody()->acceleration = m_pStarship->GetCurrentDirection() * m_pStarship->GetAccelerationRate();
	}
	static float turn_rate = m_pStarship->GetTurnRate();
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pStarship->SetTurnRate(turn_rate);
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->GetTransform()->position.x, m_pTarget->GetTransform()->position.y };
	if ( ImGui::SliderFloat2( "Target Position", targetPosition, 0.0f, 800.f) )
	{
		m_pTarget->GetTransform()->position.x = targetPosition[0];
		m_pTarget->GetTransform()->position.y = targetPosition[1];
		m_pStarship->SetTargetPosition({ targetPosition[0], targetPosition[1] }); 
	}

	if (ImGui::Button("Reset Target Position"))
	{
		m_pTarget->Reset();
		targetPosition[0] = m_pTarget->GetTransform()->position.x;
		targetPosition[1] = m_pTarget->GetTransform()->position.y;
		m_pStarship->SetTargetPosition({ targetPosition[0], targetPosition[1] });
	}

	ImGui::Separator();

	float shipPosition[2] = { m_pStarship->GetTransform()->position.x, m_pStarship->GetTransform()->position.y };
	if (ImGui::SliderFloat2("Ship Position", shipPosition, 0.0f, 800.f))
	{
		m_pStarship->GetTransform()->position.x = shipPosition[0];
		m_pStarship->GetTransform()->position.y = shipPosition[1];
	}

	if (ImGui::Button("Reset Ship Position"))
	{
		m_pStarship->Reset();
		shipPosition[0] = m_pStarship->GetTransform()->position.x;
		shipPosition[1] = m_pStarship->GetTransform()->position.y;
	}

	ImGui::End();
}
