//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Settings class that sets the displays buttoms, and screens
class Settings
{
private:
	RectangleShape start;//Start button
public:
	Settings();
	void drawDefaults(RenderWindow&);
	bool processClick(RenderWindow&);
	void die(string msg);
	void drawStats(RenderWindow&);
	void drawWinScreen(RenderWindow&);
	void drawLoseScreen(RenderWindow&);
};