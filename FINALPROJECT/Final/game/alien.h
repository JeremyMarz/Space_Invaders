//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#pragma once
#include <iostream>
#include <list>
#include "missile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


//Alien class that houses the actions and the variables used by Alien
class Alien : public Sprite
{
private: 
	//Alien	
	int walk; //walk integers used by moveAlien function
	Vector2f initial; //initial position of Aliens	
	Texture enemyTexture;//texture of level 1 aliens
	Texture level2Texture; //texture of level 2 aliens

	//bomb
	Texture bomb; //texture of bomb
	list<Missile> bombList; //list of bombs
public:
	Alien(Vector2f location);
	void processAlien(RenderWindow&);
	void moveAlien();
	void setInitial(Vector2f);
	void dropBomb();
	void drawBomb(RenderWindow&, int);
	bool playerHit(FloatRect);
};