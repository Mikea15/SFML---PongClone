#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class GameState;

using namespace std;

class MainGame
{
	public:
		MainGame(string title, int w, int h, int bpp, int fps = 60);

		bool Init();
        void Cleanup();
		void Quit();

        void ChangeState(GameState *newState);
        void PushState(GameState *newState);
        void PopState();

		int  OnExecute();
        void OnEvent();
        void OnUpdate();
        void OnDraw();

		bool isRunning();

	// need to be used on gamestate event, update and draw functions.
	public:
		sf::WindowSettings	mAppWindowSettings;
		sf::RenderWindow	mAppWindow;
		sf::Event			mAppEvent;
		sf::Clock			mAppClock;

		sf::Font            mFontType;
        float               mFontSize;
        sf::String          mScore1s, mScore2s;
        std::stringstream   mSScore, mSScore2;

        float               mPosX, mPosY, mPosX2, mPosY2;

        sf::Color           mGreen;

	private:
		vector<GameState*>	mGameState;

		string				mWinName;
		int                 mWinWidth;
		int                 mWinHeight;
		int                 mWinBPP;

		bool				mAppRunning;
		int					mAppFrameRateLimit;
};


#endif
