//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#pragma once
#include <iostream>
#include <list>
#include "alien.h"
#include "missile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Ship class that contains the ship and all its functionalities 
class Ship :public Sprite
{
private:	
	//Ship
	int killCount;//amount of kills
	bool reset; //reset for launch missile
	Texture shipTexture;//Texture of ship/pokemon trainer

	//Life
	Sprite life[3]; //array of Sprites of Lives
	Texture lifeTexture;//Texture of life


	//missile
	Missile missile;
	Texture missileTexture;//Texture of Missile
	list<Missile> missileList;//list of missile
	Texture master;//Texture of Winner Missile

public:
	Ship();
	void play(RenderWindow&, list<Alien>&);
	void moveShip();
	void shipBounds();
	void moveMissile();
	void launchMissile();
	void drawMissile(RenderWindow&);
	void checkHit(list<Alien>&);
	void displayLife(RenderWindow&, int);
	void drawKills(RenderWindow&);
	void setMissileTexture();
	int getKillCount();
	void setKillCount(int);
	
};