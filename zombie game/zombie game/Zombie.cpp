// helloSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Player.h"

int main()
{
	//game is always in one of 4 states
	enum class State {
		Paused,LEVELING_UP,GAME_OVER,PLAYING
	};

	// start with gameOver state
	State state = State::GAME_OVER;
	
	// get window resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
	// create an SFML View for mainAction
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	//clock for timing everything
	Clock clock;
	//total Playing time
	Time gameTimeTotal;

	// mouse position relative to World coordinates
	Vector2f mouseWorldPosition;
	// mouse position relative to screen coordinates
	Vector2i mouseScreenPosition;
	
	// create an instance of player
	Player player;
	
	// arena boundaries
	IntRect arena;
	
	
	//main game loop
	while (window.isOpen()) {
		/*
		*****************************
		handle inputs
		*****************************
		*/
		

		// handle events
		Event event; 

		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				// pause game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING)
				{
					state = State::Paused;
				}
				
				if (event.key.code == Keyboard::Return && state == State::Paused)
				{
					state = State::PLAYING;
					//restart the clock to avoid frame jump
					clock.restart();
				}
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING) {

				}
			}
		}// end event polling\\

		// handle quiting
		if(Keyboard::isKeyPressed (Keyboard::Escape)) {
			window.close();
		}

		// handle controls while playing
		if (state == State::PLAYING) {
			// handling the pressing and releasing of wasd keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}// end wasd playing

		// handle the leveling up state
		if (state == State::LEVELING_UP) {
			// handle player leveling up
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}
			if (state == State::PLAYING) {
				//prepare the level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;
				// modified later;
				int tileSize = 50;
				// spawn the player
				player.spawn(arena, resolution, tileSize);

				//reset clock
				clock.restart();
			}
		}// end leveling up


		/*
		*******************************************
		Update the Scene
		*******************************************
		*/
		if (state == State::PLAYING) {
			// update the delta time
			Time dt = clock.restart();
			// update the total game time
			gameTimeTotal += dt;
			// make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();
			
			//where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();
			
			// convert mouse position to world coordinate of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
			// update the Player
			player.update(dtAsSeconds, Mouse::getPosition());

			// note players new position
			Vector2f playerPosition(player.getCenter());

			// make the view center aroun the player
			mainView.setCenter(player.getCenter());
		}// end updating the scene
		
		 /*
		*******************************************
		Draw the Scene
		*******************************************
		*/
		if (state == State::PLAYING) {
			window.clear();
			//set the mainView to be displayed in window
			// and draw everything related to it
			window.setView(mainView);
			
			//Draw the player
			window.draw(player.getSprite());

		}

		if (state == State::LEVELING_UP) {

		}


		if (state == State::Paused) {

		}

		if (state == State::GAME_OVER) {

		}

		window.display();

	}// end game loop
	


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
