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

//Missile class that is a Missile Sprite, just used to move the missile
class Missile : public Sprite
{
public:
	//======================================================
	// Missile: Missile Constructor
	// parameters: none
	// return type: Missile
	//======================================================
	Missile() {};

	//======================================================
	// shootMissile: shoots missile
	// parameters:
	//    speed: speed of missile
	// return type: none
	//======================================================
	void shootMissile(int speed)
	{
		int Y = getPosition().y;
		move(0, speed);
	}
};