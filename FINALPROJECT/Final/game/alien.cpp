//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#include "alien.h"
#include "missile.h"
#include <iostream>
#include <list>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//======================================================
// Alien: Alien Contructor
// parameters:
//    location: location of Alien
// return type: Alien
//======================================================
Alien::Alien(Vector2f location)
{
	if (!enemyTexture.loadFromFile("haunter.png"))
	{
		cout << "Unable to load enemy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!bomb.loadFromFile("shadow.png"))
	{
		cout << "Unable to load enemy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	setTexture(enemyTexture);
	setPosition(location);
	walk = 0;
};

//======================================================
// moveAlien: moves Alien
// parameters: none
// return type: none
//======================================================
void Alien::moveAlien()
{
	const float dash = 3.0f;
	const float slow = 0.25f;
	if (walk == 0)
	{
		move(-dash, slow);//left and slowly downward
		if (getPosition().x < initial.x - 50)
		{
			walk = 1;
		}
	}
	else if (walk == 1)
	{
		move(dash, slow);//right and slowly downward
		if (getPosition().x > initial.x + 50)
		{
			walk = 0;
		}
	}
}

//======================================================
// processAlien: processes the bomb functionality
// parameters:
//    location: location of Alien
// return type: none
//======================================================
void Alien::processAlien(RenderWindow&)
{
	list<Missile>::iterator bombIter;

	for (bombIter = bombList.begin(); bombIter != bombList.end(); bombIter++)
		if(bombIter == bombList.begin())
			bombIter->shootMissile(5);
}

//======================================================
// setInitial: sets Initial Location of Alien
// parameters:
//    loc: initial location of Alien
// return type: none
//======================================================
void Alien::setInitial(Vector2f loc)
{
	initial = loc;
}

//======================================================
// dropBomb: drops bomb
// parameters: none
// return type: none
//======================================================
void Alien::dropBomb()
{
	Missile alienBomb;
	alienBomb.setPosition(getPosition().x, getPosition().y+40);
	bombList.push_back(alienBomb);
}

//======================================================
// drawBomb: draws the bomb
// parameters:
//		win: window rendered in main
//		level: current level of the game
// return type: none
//======================================================
void Alien::drawBomb(RenderWindow& win, int level)
{
	list<Missile>::iterator bombIter;

	for (bombIter = bombList.begin(); bombIter != bombList.end(); bombIter++)
	{
		bombIter->setTexture(bomb);
		
		if (level == 2)
		{
			bombIter->setScale(0.025, 0.025);
		}
		else
		{
		bombIter->setScale(0.02, 0.02);
		}
		if(bombIter == bombList.begin())
			win.draw(*bombIter);
	}
}

//======================================================
// playerHit: checks if player was hit
// parameters:
//    player: the globalbounds of the player
// return type: bool
//======================================================
bool Alien::playerHit(FloatRect player)
{	
	bool hit = false;
	list<Missile>::iterator bombIter;
	vector<list<Missile>::iterator> bombDelete;
	for (bombIter = bombList.begin(); bombIter != bombList.end(); bombIter++)
	{	
		FloatRect bombBounds = bombIter->getGlobalBounds();

		if (bombBounds.intersects(player))
		{
			bombDelete.push_back(bombIter);
			hit = true;
		}
	}
	for (int i = 0; i < bombDelete.size(); i++)
	{
		bombList.erase(bombDelete[i]);
	}	
	return hit;
}





