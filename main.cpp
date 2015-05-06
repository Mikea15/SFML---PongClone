#include "MainGame.h"
#include "IntroState.h"

int main(int argc, char *argv[])
{
	MainGame Game("PongClone", 400, 300, 32, 60);

	// initialize the engine
	if( Game.Init() == false )
		return EXIT_FAILURE;

	// load the intro
	Game.ChangeState( IntroState::Instance() );

	// main loop
	while(Game.isRunning())
	{
		Game.OnEvent();

		Game.OnUpdate();

		Game.OnDraw();
	}

	// cleanup the engine
	Game.Cleanup();

	return EXIT_SUCCESS;
}


