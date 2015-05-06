#ifndef _MENU_H_
#define _MENU_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Menu
{
	public:
		Menu();

		void		loadFont( string name );
		void		loadFontSize( float fontSize );

		void		addString( string n );

		int			getMenuSize();

		sf::String	draw(int i);

		void		setPosition(int i, float x, float y);
		void	    setRotation(int i, float rotation);
		void		setScale( int i, float x, float y);

		void		cleanMenu();

		void		goUp();
		void		goDown();
		void		goLast();

		int			getSelectedItem();

		void		setMenuColor(int r, int g, int b, int alpha = 255);
        void		setMenuColorSelected(int r, int g, int b, int alpha = 255);

		void		isSelected(int i);
		void		isNotSelected(int i);

	private:
		vector<sf::String>	mMenu;
		sf::Font			mMenuFont;
		float				mMenuFontSize;

		unsigned int		mSelectedItem;

		sf::Color			mMenuColor;
		sf::Color			mMenuColorSelected;
};


#endif
