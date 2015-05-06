#include "GameState.h"

GameState::GameState()
{
	// virtual
}

void GameState::Init( MainGame *Game )
{
	// virtual
}

void GameState::Cleanup()
{
	// virtual
}

void GameState::Pause()
{
	// virtual
}

void GameState::Resume()
{
	// virtual
}

void GameState::OnEvent(MainGame *Game, sf::Event Event)
{
	// virtual
}

void GameState::OnUpdate(MainGame *Game)
{
	// virtual
}

void GameState::Draw(MainGame *Game)
{
	// virtual
}

void GameState::ChangeState(MainGame Game, GameState *newState)
{
	Game.ChangeState(newState);
}

