

#ifndef _PLAYSTATEVSAI_H_
#define _PLAYSTATEVSAI_H_

#include "GameState.h"

class PlayStateVsAI : public GameState
{
	public:
		PlayStateVsAI();
		virtual ~PlayStateVsAI();

		void Init( MainGame *Game );
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent( MainGame *Game, sf::Event Event );
		void OnUpdate( MainGame *Game );
		void Draw( MainGame *Game );

		static PlayStateVsAI *Instance();

        bool check_collision( sf::Sprite A, sf::Sprite B );
        void showWinner( MainGame *Game , Winner win );
        void moveAI();

    private:
        static PlayStateVsAI	mPlayStateVsAI;

    private:
        sf::Clock           mClock;
        sf::Image           mBgPlayerOneWins;
        sf::Image           mBgPlayerTwoWins;
        sf::Sprite          mPlayerOneSprite;
        sf::Sprite          mPlayerTwoSprite;

        sf::Image           mBgWhite;
        sf::Image           mBgGray;
        sf::Sprite          mPad1, mPad2, mBall, mSeparator;

        // scores

        float               mPadSpeed, mBallSpeed;
        int                 mBallDirectionX, mBallDirectionY, mBallAlive;
        int                 mPad1Score, mPad2Score;


        float               mCPULevel;
        float               mSpeedUp, mSpeedDown;
        float               mCPULevelUp;

        sf::SoundBuffer     mSoundBuffer;
        sf::Sound           mSoundHit;
};


#endif
