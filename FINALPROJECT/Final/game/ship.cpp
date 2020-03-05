//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#include "ship.h"
#include "alien.h"
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//======================================================
// Ship: ship constructor
// parameters: none
// return type: Ship
//======================================================
Ship::Ship()
{
	reset = false; //reset for missileLaunch

	//Loads Texture
	if (!shipTexture.loadFromFile("trainer.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!missileTexture.loadFromFile("pokeball.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!master.loadFromFile("master.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!lifeTexture.loadFromFile("life.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	scale(sf::Vector2f(0.15, 0.15));
	setTexture(shipTexture); //set Texture of Ship
	setPosition(400, 550);	// initial position of the ship

	//creates hearts/lives
	Vector2f heartLoc(60, 5);
	for (int i = 0; i < 3; i++)
	{
		life[i].setTexture(lifeTexture);
		life[i].scale(sf::Vector2f(0.035, 0.035));
		life[i].setPosition(heartLoc);
		heartLoc.x += 30;
	}

	//sets missile texture
	missile.setTexture(missileTexture);
	missile.setScale(0.02, 0.02);
}

//======================================================
// play: calls functions from player to perform the game actions
// parameters:
//    win: window rendered in main
//    enemy:  list of aliens
// return type: none
//======================================================
void Ship::play(RenderWindow& win, list<Alien>& enemy)
{
	moveMissile();
	drawMissile(win);
	launchMissile();
	checkHit(enemy);
	drawKills(win);
}

//======================================================
// moveShip: moves ship sprite
// parameters: none
// return type: none
//======================================================
void Ship::moveShip()
{
	const float DISTANCE = 5.0f;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		move(DISTANCE, 0);
	}
}

//======================================================
// shipBounds: keeps the ship sprite in the bounds of the window
// parameters: none
// return type: none
//======================================================
void Ship::shipBounds()
{
	if (getPosition().y > 599)
	{
		setPosition(getPosition().x, 580);
	}
	else if (getPosition().y < 480)
	{
		setPosition(getPosition().x, 480);
	}
	else if (getPosition().x < 0)
	{
		setPosition(1, getPosition().y);
	}
	else if (getPosition().x > 780)
	{
		setPosition(780, getPosition().y);
	} 
	else
	{
		moveShip();
	}
}

//======================================================
// moveMissile: moves the missile sprite
// parameters: none
// return type: none
//======================================================
void Ship::moveMissile()
{
	list<Missile>::iterator missileIter;

	for (missileIter = missileList.begin(); missileIter != missileList.end(); missileIter++)
	{
		missileIter->move(0, -10);
	}

}

//======================================================
// launchMissile: detects if key is hit so missile will launch
// parameters: none
// return type: none
//======================================================
void Ship::launchMissile()
{	
	if (Keyboard::isKeyPressed(Keyboard::Space) && reset == true)
	{
		Vector2f missilePos(getPosition().x + 8, getPosition().y);
		missile.setPosition(missilePos);
		missileList.push_back(missile);
		reset = false;
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space))
	{
		reset = true;
	}
}

//======================================================
// drawMissile: calls functions from player to perform the game actions
// parameters: 
//    win: window rendered in main
// return type: none
//======================================================
void Ship::drawMissile(RenderWindow& win)
{
	list<Missile>::iterator missileIter;
	missileIter = missileList.begin();

	for (missileIter; missileIter != missileList.end(); missileIter++)
	{
		win.draw(*missileIter);
	}
}

//======================================================
// checkHit: checks to see if ship sprite is hit
// parameters: 
//    enemy: list of aliens
// return type: none
//======================================================
void Ship::checkHit(list<Alien>& enemy)
{
	list<Missile>::iterator missileIter;
	vector<list<Missile>::iterator> missileDelete;

	list<Alien>::iterator alienIter;
	vector<list<Alien>::iterator> aliensDelete;

	for (missileIter = missileList.begin(); missileIter != missileList.end(); missileIter++)
	{	
		FloatRect missileBounds = missileIter->getGlobalBounds();
		for (alienIter = enemy.begin(); alienIter != enemy.end(); alienIter++)
		{
			FloatRect enemyBounds = alienIter->getGlobalBounds();

			if (missileBounds.intersects(enemyBounds))
			{
				killCount++;
				aliensDelete.push_back(alienIter);
				missileDelete.push_back(missileIter);//bug
			}
		}
	}
	for (int i = 0; i < missileDelete.size(); i++)
		missileList.erase(missileDelete[i]);
	for (int i = 0; i < aliensDelete.size(); i++)
			enemy.erase(aliensDelete[i]);
	missileDelete.clear();
	for (missileIter = missileList.begin(); missileIter != missileList.end(); missileIter++)
	{
		if (missileIter->getPosition().y < 0)
		{
			missileDelete.push_back(missileIter);
		}
	}
	
	for (int i = 0; i < missileDelete.size(); i++)
		missileList.erase(missileDelete[i]);
}

//======================================================
// displayLife: displays lives
//		win: window rendered in main
//		lifeCount: amount of lives 
// return type: none
//======================================================
void Ship::displayLife(RenderWindow& win, int lifeCount)
{	
	for (int i = 0; i < lifeCount; i++)
	{
		win.draw(life[i]);
	}
}

//======================================================
// drawKills: displays amount of kills
// parameters: 
//    win: window rendered in main
// return type: none
//======================================================
void Ship::drawKills(RenderWindow& win)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		cout << "Not Loading" << endl;
	}

	string kill = "Alien Kills:";
	kill += to_string(killCount);

	Text killText(kill, font, 20);
	killText.setPosition(670, 0);
	win.draw(killText);
}

//======================================================
// setMissileTexture: sets Texture of missile
// parameters: none
// return type: none
//======================================================
void Ship::setMissileTexture()
{
	missile.setTexture(master);
	missile.setScale(0.06, 0.06);
}

//======================================================
// getKillCount: gets amount of kills
// parameters: none
// return type: int
//======================================================
int Ship::getKillCount()
{
	return killCount;
}

//======================================================
// setKillCount: sets Kill Count
// parameters: 
//    kills: amount of kills
// return type: none
//======================================================
void Ship::setKillCount(int kills)
{
	killCount = kills;
}

