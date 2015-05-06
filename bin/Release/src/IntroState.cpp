#include "IntroState.h"

// Initialize mIntroState as Static Variable
IntroState IntroState::mIntroState;

IntroState::IntroState()
{
    mLineSpacing = 10.0f;
    mInitPosX = 150.0f;
    mInitPosY = 150.0f;
}

IntroState::~IntroState()
{
}

void IntroState::Init( MainGame *Game )
{
    if( !mBgImg.LoadFromFile("data\\gfx\\intro.jpg"));
    {
        // error
    }

    mBgImg.SetSmooth(false);

    mBgSprite.SetImage(mBgImg);

    mMenu.loadFont("data\\fonts\\visitor2.ttf");
    mMenu.loadFontSize(13.0f);
    mMenu.setMenuColor(255, 255, 255);
    mMenu.setMenuColorSelected(66, 235, 14);

    mMenu.addString("One Player");
    mMenu.addString("Two Players");
    mMenu.addString("Quit");

    for( int i = 0; i < mMenu.getMenuSize(); i++ )
    {
        mMenu.setPosition(i, mInitPosX, mInitPosY );
        mInitPosY += mLineSpacing;
    }



}

void IntroState::Cleanup()
{
    mMenu.cleanMenu();
}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
}

void IntroState::OnEvent(MainGame *Game, sf::Event Event)
{
	switch(Event.Type)
	{
		case sf::Event::Closed:
			Game->Quit();
		break;
		case sf::Event::KeyPressed:
			switch(Event.Key.Code)
			{
				case sf::Key::Escape:
					mMenu.goLast();
				break;

				case sf::Key::Up:
					mMenu.goUp();
				break;
				case sf::Key::Down:
					mMenu.goDown();
				break;
				case sf::Key::Return:
					switch( mMenu.getSelectedItem() )
					{
						case 0:
							// playState
							Game->PushState( PlayStateVsAI::Instance() );
						break;
						case 1:
							Game->PushState( PlayState::Instance() );
						break;
						case 2:
							// quit
							Game->Quit();
						break;
						default: break;
					}
				break;
				default: break;
			}
		break;
		default: break;
	}
}

void IntroState::OnUpdate(MainGame *Game)
{

}

void IntroState::Draw(MainGame *Game)
{
	Game->mAppWindow.Clear();

    Game->mAppWindow.Draw(mBgSprite);

    for( int i = 0 ; i < mMenu.getMenuSize(); i++ )
	{
		if( i == mMenu.getSelectedItem() )
			mMenu.isSelected(i);
		else
			mMenu.isNotSelected(i);

		Game->mAppWindow.Draw( mMenu.draw(i) );
	}

	Game->mAppWindow.Display();
}


IntroState *IntroState::Instance()
{
    return &mIntroState;
}

