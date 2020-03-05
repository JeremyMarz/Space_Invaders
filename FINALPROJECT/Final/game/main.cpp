//========================================================
//Jeremy Martinez
//4-20-2016
//Progamming Assignment #8
//Description: Space Invaders
//========================================================
#include "alien.h"
#include "ship.h"
#include "Settings.h"
#include "missile.h"
#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	//Window Size
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	//Player Initialization
	Ship player;

	//Setting Initialization and Variables that deal with Settings
	Settings settings;
	int	frame = 0,
		level = 1,
	 lifeCount = 3;
	bool start = false,
	       end = false,
	   	 reset = false;

	//Variables used with Alien Location and Move
	Vector2f location(70, 50);
	Vector2f initial[10];

	//Renders Window
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders!");

	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);


	// set up textures
	Texture starsTexture;
	if (!starsTexture.loadFromFile("background2.png"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture level2Texture;
	if (!level2Texture.loadFromFile("gengar.png"))
	{
		cout << "Unable to load enemy texture!" << endl;
		exit(EXIT_FAILURE);
	}

	//Sprite used to make the background
	Sprite background;
	background.setTexture(starsTexture);
	background.setScale(0.5, 0.5);

	//Alien and List Initialization
	list<Alien> enemy;
	Alien alien(location);
	alien.scale(sf::Vector2f(0.2, 0.2));

	
	//Fills list with Aliens
	for (int i = 0; i < 10; i++)
	{	
		alien.setPosition(location);
		alien.setInitial(location);
		enemy.push_back(alien);
		location.x += 70;
	}
	
	// this is the main animation loop. The body of the loop runs ~ 60 times per second
	while (window.isOpen())
	{

		Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				else if (start == false) //Creates Start Screen
				{
					window.draw(background);
					settings.drawDefaults(window);
					window.display();
					if (settings.processClick(window)) //if start button is pressed then start the game
					{
						start = true;
					}
				}
			}
			if (start == true) //If start is clicked
			{
				window.draw(background);
				if (reset == true) //reset used for when a life is lost
				{
					reset = false;
					enemy.clear();
					lifeCount--;
					if (level == 1) //if level is 1
					{		

						Vector2f location(70, 50);
						for (int i = 0; i < 10; i++)
						{
							alien.setPosition(location);
							alien.setInitial(location);
							enemy.push_back(alien);
							location.x += 70;
						}		
						player.setKillCount(0);

					}
					else if (level == 2) //if level is 2
					{
						Vector2f location(70, 50);

						for (int i = 0; i < 10; i++)
						{
							alien.setTexture(level2Texture);
							alien.setPosition(location);
							alien.setInitial(location);
							enemy.push_back(alien);	
							location.x += 70;
						}
						location.y += 100;
						for (int i = 0; i < 10; i++)
						{		
							location.x -= 70;

							alien.setTexture(level2Texture);
							alien.setPosition(location);
							alien.setInitial(location);
							enemy.push_back(alien);
						}	
						player.setKillCount(10);

					}
				}
			
				settings.drawStats(window); //Draws Lives and Alien Kill stats	
				player.displayLife(window, lifeCount); //Displays Lives
				player.play(window, enemy); //Play function that does all Player/Ship functionality
				frame++;

				player.shipBounds(); //also keeps the ship within the global bounds			
				window.draw(player);// draw the ship on top of background 
				
				//Iterators used to find a certain Alien
				list<Alien>::iterator iter; 
				vector<list<Alien>::iterator> toDelete;

				//does all Alien and Bomb fuctionalities
				for (iter = enemy.begin(); iter != enemy.end(); iter++)
				{
					iter->moveAlien(); //moves Alien
					window.draw(*iter); //draws Alien
					iter->processAlien(window);	//process Alien 
					iter->drawBomb(window, level);	//draws bomb

					if (iter->playerHit(player.getGlobalBounds()) || iter->getPosition().y > 500) //If player losses a life it resets the original state of the current level
					{
						reset = true;
					}

					if (frame == 100 || frame == 50) //randomizer for bomb, drop bomb at random location every 50 to 100 seconds
					{			
						list<Alien>::iterator bombIterator;
						bombIterator = enemy.begin();
						
						srand(time(NULL));
						int randomizer = (rand() % enemy.size() - 1);
						for (int i = 0; i < randomizer && bombIterator != enemy.end(); i++)
						{
							bombIterator++;
						}					
						bombIterator->dropBomb(); //drops bomb
					}		
				}
				for (int i = 0; i < toDelete.size(); i++)
				{
					enemy.erase(toDelete[i]);
				}
			}
			
			if (player.getKillCount() == 10 && level == 1) //sets level 1 to level 2 if beaten
			{
				level = 2;
				reset = true;
				lifeCount++;
			}

			if (player.getKillCount() == 30) //if game is won, display win screen
			{
				settings.drawWinScreen(window);
				player.setMissileTexture();
			}
			if (lifeCount <= 0) //if you are out of lives, display lose screen
			{		
				end == true;
				while (!end)
				{			

					window.draw(background);
					settings.drawLoseScreen(window);
					window.display();
					if (event.type == Event::Closed)
						window.close();
				}
			}
			if (frame == 100) //resets frame counter
			{
				frame = 0;
			}
			window.display();				// end the current frame; 
	}
return 0;
}