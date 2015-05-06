#include "Menu.h"

Menu::Menu()
{
	mSelectedItem = 0;
}

void Menu::loadFont( string name )
{
	if( !mMenuFont.LoadFromFile( name.c_str() ) )
	{
		cout << "[!] Could not load font: " << name.c_str() << endl;
	} 
	else 
	{
		cout << "[ ] Font :" << name.c_str() << " succesfully loaded" << endl;
	}
}

void Menu::loadFontSize( float fontSize )
{
	mMenuFontSize = fontSize;
}

void Menu::addString( string n )
{
	mMenu.push_back( sf::String( n.c_str() ) );
}

int	Menu::getMenuSize()
{
	return mMenu.size();
}

sf::String Menu::draw(int i)
{
	return mMenu.at(i);
}

void Menu::setPosition(int i, float x, float y)
{
	mMenu.at(i).SetPosition(x, y);
}

void Menu::setRotation(int i, float rotation)
{
	mMenu.at(i).SetRotation(rotation);
}

void Menu::setScale(int i, float x, float y)
{
	if( x == 0 )
		mMenu.at(i).SetScaleY(y);

	if( y == 0 )
		mMenu.at(i).SetScaleX(x);

	if( x != 0 && y != 0 )
		mMenu.at(i).SetScale(x, y);
}

void Menu::cleanMenu()
{
	mMenu.clear();
}

void Menu::goUp()
{
	if( mSelectedItem > 0 )
		mSelectedItem--;
	else
		mSelectedItem = ( mMenu.size() - 1 ) ;
}

void Menu::goDown()
{
	if( mSelectedItem < ( mMenu.size() - 1 ) )
		mSelectedItem++;
	else
		mSelectedItem = 0;
}

void Menu::goLast()
{
	mSelectedItem = mMenu.size() -1;
}

int Menu::getSelectedItem()
{
	return mSelectedItem;
}

void Menu::setMenuColor(int r, int g, int b, int alpha)
{
	mMenuColor = sf::Color(r, g, b, alpha);
}

void Menu::setMenuColorSelected(int r, int g, int b, int alpha)
{
	mMenuColorSelected = sf::Color(r, g, b, alpha);
}


void Menu::isSelected( int i )
{
	mMenu.at(i).SetFont(mMenuFont);
	mMenu.at(i).SetSize(mMenuFontSize);
	mMenu.at(i).SetColor(mMenuColorSelected);
}

void Menu::isNotSelected(int i)
{
	mMenu.at(i).SetFont(mMenuFont);
	mMenu.at(i).SetSize(mMenuFontSize);
	mMenu.at(i).SetColor(mMenuColor);
}




