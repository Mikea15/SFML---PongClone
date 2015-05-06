#ifndef _INTROSTATE_H_
#define _INTROSTATE_H_

#include "GameState.h"
#include "PlayState.h"

#include "PlayStateVsAI.h"

#include "Menu.h"

class IntroState : public GameState
{
	public:
		IntroState();
		virtual ~IntroState();

		void Init( MainGame *Game );
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(MainGame *Game);

		static IntroState *Instance();

    private:
        static IntroState	mIntroState;

        sf::Image           mBgImg;
        sf::Sprite          mBgSprite;

        Menu                mMenu;

        float               mLineSpacing;
        float               mInitPosX;
        float               mInitPosY;
};


#endif
