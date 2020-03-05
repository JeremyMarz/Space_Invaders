//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#pragma once
#include "Settings.h"
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//======================================================
// Settings: Settings Contructor
// parameters: none
// return type: Settings
//======================================================
Settings::Settings()
{
	Vector2f sqPos(300, 250);
	start.setPosition(sqPos);
	start.setOutlineColor(Color::White);
	start.setOutlineThickness(2);
	start.setSize(Vector2f(200, 50));
	start.setFillColor(Color::Black);
}

//======================================================
// drawDefaults: draws startScreen
// parameters:
//		win: window rendered in main
// return type: none
//======================================================
void Settings::drawDefaults(RenderWindow& win)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		die("couldn't load font");
	Text title("Start", font, 30);
	title.setPosition(360, 255);
	Text title2("Space Invaders", font, 100);
	title2.setPosition(50, 100);
	title2.setStyle(Text::Bold);
	win.draw(start);
	win.draw(title);
	win.draw(title2);
}

//======================================================
// processClick: processes button click
// parameters:
//		win: window rendered in main
// return type: bool
//======================================================
bool Settings::processClick(RenderWindow& win)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f mouse = win.mapPixelToCoords(Mouse::getPosition(win));

		if (start.getGlobalBounds().contains(mouse))
		{
			cout << "Begin" << endl;
			return true;
		}
	}
	return false;
}

//======================================================
// die: tells when to exit
// parameters:
//		msg: string of message
// return type: none
//======================================================
void Settings::die(string msg)
{
	cout << msg << endl;
	exit(-1);
}

//======================================================
// drawStats: draws Lives and Aliens killed
// parameters:
//		win: window rendered in main
// return type: none
//======================================================
void Settings::drawStats(RenderWindow& win)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		die("couldn't load font");
	Text life("Lives:", font, 20);
	life.setPosition(2, 0);
	win.draw(life);
}

//======================================================
// drawWinScreen: draws win Screen
// parameters:
//		win: window rendered in main
// return type: none
//======================================================
void Settings::drawWinScreen(RenderWindow& win)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		die("couldn't load font");
	Text end("You Win!", font, 100);
	end.setPosition(200, 100);
	end.setFillColor(Color::Black);
	Text master("You are a Pokemon Master!", font, 20);
	master.setPosition(270, 240);
	master.setFillColor(Color::Black);

	win.draw(master);
	win.draw(end);

}

//======================================================
// drawWinScreen: draws lose Screen
// parameters:
//		win: window rendered in main
// return type: none
//======================================================
void Settings::drawLoseScreen(RenderWindow& win)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		die("couldn't load font");
	Text lose("You Lose!", font, 100);
	lose.setPosition(200, 100);
	lose.setFillColor(Color::Black);
	Text loser("You are not a Pokemon Master!", font, 20);
	loser.setPosition(270, 240);
	loser.setFillColor(Color::Black);
	win.draw(loser);
	win.draw(lose);
}