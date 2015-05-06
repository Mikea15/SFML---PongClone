

#include "PlayStateVsAI.h"

PlayStateVsAI PlayStateVsAI::mPlayStateVsAI;


PlayStateVsAI::PlayStateVsAI()
{

}

PlayStateVsAI::~PlayStateVsAI()
{

}

void PlayStateVsAI::Init( MainGame *Game )
{

    mBgWhite.Create(10, 10, sf::Color(255, 255, 255));
    mBgGray.Create(5, Game->mAppWindow.GetHeight(), sf::Color(80, 80, 80));

    mPad1.SetImage(mBgWhite);
	mPad1.SetScaleY(4.f);
	mPad1.SetPosition( (float) 0,
					  (float)( ( Game->mAppWindow.GetHeight() - mPad1.GetSize().y ) / 2 ) );

	mPad2.SetImage(mBgWhite);
	mPad2.SetScaleY(4.f);
	mPad2.SetPosition( (float)( Game->mAppWindow.GetWidth() - mPad2.GetSize().x ),
					  (float)( ( Game->mAppWindow.GetHeight() - mPad2.GetSize().y ) / 2 ) );

	mBall.SetImage(mBgWhite);
	mBall.SetScale(.5f, .5f);
	mBall.SetPosition( (float)( ( Game->mAppWindow.GetWidth() - mBall.GetSize().x ) / 2 ),
					  (float)( ( Game->mAppWindow.GetHeight() - mBall.GetSize().y ) / 2 ) );

	mSeparator.SetImage(mBgGray);
	mSeparator.SetPosition( (float) ( ( Game->mAppWindow.GetWidth () - mSeparator.GetSize().x ) / 2),
		(float) ( 0 ) );


    // scores

    mPadSpeed = 5.0f;
    mBallSpeed = 2.5f;

    mSpeedUp = 0.25f;
    mSpeedDown = 0.05f;
    mCPULevel = 40.0f;
    mCPULevelUp = 10.0f;

    if( sf::Randomizer::Random(0, 1) == 0 ) {
		mBallDirectionX = -1;
	} else {
		mBallDirectionX = 1;
	}

    if( sf::Randomizer::Random(0, 1) == 0 ) {
		mBallDirectionY = -1;
	} else {
		mBallDirectionY = 1;
	}

    mBallAlive = 1;
    mPad1Score = 0;
    mPad2Score = 0;


    if( !mBgPlayerOneWins.LoadFromFile("data\\gfx\\playeronewins.jpg"));
    {
        // error
    }
    mBgPlayerOneWins.CreateMaskFromColor(sf::Color::Black);
    mPlayerOneSprite.SetImage(mBgPlayerOneWins);

    if( !mBgPlayerTwoWins.LoadFromFile("data\\gfx\\computerwins.jpg"));
    {
        // error
    }

    mBgPlayerTwoWins.CreateMaskFromColor(sf::Color::Black);
    mPlayerTwoSprite.SetImage(mBgPlayerTwoWins);


    if( !mSoundBuffer.LoadFromFile( "data\\sfx\\hit3.wav" ) )
    {
        // error
    }

    mSoundHit.SetBuffer(mSoundBuffer);

    Game->mAppWindow.ShowMouseCursor(false);

}

void PlayStateVsAI::Cleanup()
{
}

void PlayStateVsAI::Pause()
{
}
void PlayStateVsAI::Resume()
{
}

void PlayStateVsAI::OnEvent(MainGame *Game, sf::Event Event)
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
					Game->PopState();
				break;
				default: break;
			}
		break;
		default: break;
	}
}

void PlayStateVsAI::OnUpdate(MainGame *Game)
{
    // Update
    if( mBallAlive == 1)
    {
        if( ( Game->mAppWindow.GetInput().IsKeyDown(sf::Key::Down) ) && ( ( mPad1.GetPosition().y + mPad1.GetSize().y ) <= Game->mAppWindow.GetHeight() ) )
            mPad1.Move(0 , mPadSpeed );
        if( ( Game->mAppWindow.GetInput().IsKeyDown(sf::Key::Up) ) && ( mPad1.GetPosition().y >= 0 ) )
            mPad1.Move(0,  -mPadSpeed );

        /* AI Operations */
        if( ( mPad2.GetPosition().y + mPad2.GetSize().y ) <= Game->mAppWindow.GetHeight() )
        {
            if( mBallDirectionX == 1 )
                if( mBall.GetPosition().y >= ( mPad2.GetPosition().y + mPad2.GetSize().y - mCPULevel ) )
                    mPad2.Move(0,  mPadSpeed );
        }
        if( mPad2.GetPosition().y >= 0 )
        {
            if( mBallDirectionX == 1)
                if( ( mBall.GetPosition().y + mBall.GetSize().y - mCPULevel ) <= mPad2.GetPosition().y )
                    mPad2.Move(0,  -mPadSpeed );
        }
        //-----------------------------------------------------------

        mBall.Move( mBallSpeed * mBallDirectionX , mBallSpeed * mBallDirectionY );

        // se bate na parede = golo, e bola para e 1 ponto para pad1
        if( ( mBall.GetPosition().x + mBall.GetSize().x ) >= Game->mAppWindow.GetWidth() )
        {
            // play sound
            mBallAlive = 0;

            // score 1 pad2
            mPad1Score++;

            //balldirectionX *=-1;
            mCPULevel -= mCPULevelUp;
        }

        // se bate na parede = golo, e bola para e 1 ponto para pad2
        if( mBall.GetPosition().x <= 0 )
        {
            // play sound
            mBallAlive = 0;
            // score 1 pad2
            mPad2Score++;

        }

        // colision with up and down walls.
        if( ( ( mBall.GetPosition().y + mBall.GetSize().y ) >= Game->mAppWindow.GetHeight() ) || ( mBall.GetPosition().y <= 0 ) )
        {
            mBallDirectionY = -mBallDirectionY;
            mSoundHit.Play();
        }

        if( ( mBall.GetPosition().x < ( mPad1.GetPosition().x + mPad1.GetSize().x - 1 ) ) ||
            ( ( mBall.GetPosition().x + mBall.GetSize().x ) > ( mPad2.GetPosition().x + 1 ) ) )
        {
            if( mBallDirectionX < 0 )
            {
                if( check_collision(mPad1, mBall) )
                {
                    mBallDirectionX *=-1;
                    mBallSpeed += mSpeedUp;
                    mSoundHit.Play();
                }
            }
            else
            {
                if( check_collision(mBall, mPad2) )
                {
                    mBallDirectionX *=-1;
                    mBallSpeed -= mSpeedDown;
                    mSoundHit.Play();
                }
            }
        }
    }
    else
    {
        mClock.Reset();

        sf::Sleep(1);

        mBallAlive = 1;

        mPad1.SetPosition( (float) 0,
                          (float)( ( Game->mAppWindow.GetHeight() - mPad1.GetSize().y ) / 2 ) );

        mPad2.SetPosition( (float)( Game->mAppWindow.GetWidth() - mPad2.GetSize().x ),
                          (float)( ( Game->mAppWindow.GetHeight() - mPad2.GetSize().y ) / 2 ) );

        mBall.SetPosition( (float)( ( Game->mAppWindow.GetWidth() - mBall.GetSize().x ) / 2 ),
                          (float)( ( Game->mAppWindow.GetHeight() - mBall.GetSize().y ) / 2 ) );

        if( sf::Randomizer::Random(0, 1) == 0 ) {
            mBallDirectionX = -1;
        } else {
            mBallDirectionX = 1;
        }

        if( sf::Randomizer::Random(0, 1) == 0 ) {
            mBallDirectionY = -1;
        } else {
            mBallDirectionY = 1;
        }

        mSpeedUp = 0.25f;
        mSpeedDown = 0.05f;
        mCPULevel = 40.0f;
        mCPULevelUp = 10.0f;
    }

    if( mPad1Score == 3 ) {
        showWinner(Game, PLAYERONE);

        mPad1Score = 0;
        mPad2Score = 0;

        mClock.Reset();

        mBallAlive = 1;

    }
    if( mPad2Score == 3 ) {
        showWinner(Game, PLAYERTWO);

        mPad1Score = 0;
        mPad2Score = 0;

        mClock.Reset();

        mBallAlive = 1;
    }

    Game->mSScore.str("");
    Game->mSScore << mPad1Score;
    Game->mScore1s.SetText(Game->mSScore.str());

    Game->mSScore2.str("");
    Game->mSScore2 << mPad2Score;
    Game->mScore2s.SetText(Game->mSScore2.str());
}

void PlayStateVsAI::Draw(MainGame *Game)
{
    Game->mAppWindow.Clear(sf::Color(30, 30, 30));

    // Draw
    Game->mAppWindow.Draw(mSeparator);

    Game->mAppWindow.Draw(Game->mScore1s);
    Game->mAppWindow.Draw(Game->mScore2s);

    Game->mAppWindow.Draw(mPad1);
    Game->mAppWindow.Draw(mPad2);
    Game->mAppWindow.Draw(mBall);

    // Finally, display the rendered frame on screen / refresh...
    Game->mAppWindow.Display();
}

PlayStateVsAI *PlayStateVsAI::Instance()
{
    return &mPlayStateVsAI;
}

void PlayStateVsAI::showWinner( MainGame *Game , Winner win )
{
	sf::Clock clock;
	clock.Reset();

	while(1) {
		// if 3 second have passed cia!
		if( clock.GetElapsedTime() > 2.5f )
			break;

		Game->mAppWindow.Clear();

		if( win == PLAYERONE )
		{
		    mPlayerOneSprite.SetPosition( ( Game->mAppWindow.GetWidth() - mPlayerOneSprite.GetSize().x ) / 2,
                                          ( Game->mAppWindow.GetHeight() - mPlayerOneSprite.GetSize().y ) / 2);

			Game->mAppWindow.Draw(mPlayerOneSprite);
		}

		if( win == PLAYERTWO )
		{
		    mPlayerTwoSprite.SetPosition( ( Game->mAppWindow.GetWidth() - mPlayerTwoSprite.GetSize().x ) / 2,
                                          ( Game->mAppWindow.GetHeight() - mPlayerTwoSprite.GetSize().y ) / 2);

			Game->mAppWindow.Draw(mPlayerTwoSprite);
		}

        // Finally, display the rendered frame on screen / refresh...
        Game->mAppWindow.Display();
	}
	Game->PopState();
}

bool PlayStateVsAI::check_collision( sf::Sprite A, sf::Sprite B )
{
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.GetPosition().x;
	rightA = leftA + A.GetSize().x;
	topA = A.GetPosition().y;
	bottomA = topA + A.GetSize().y;

	//Calculate the sides of rect B
	leftB = B.GetPosition().x;
	rightB = leftB + B.GetSize().x;
	topB = B.GetPosition().y;
	bottomB = topB + B.GetSize().y;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
		return false;

	if( topA >= bottomB )
		return false;

	if( rightA <= leftB )
		return false;

	if( leftA >= rightB )
		return false;

	//If none of the sides from A are outside B
	return true;
}







