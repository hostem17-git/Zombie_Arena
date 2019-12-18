#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class Player {
private:
		const float START_SPEED = 200;
		const float START_HEALTH = 100;
		// where is the player
		Vector2f m_Position;
		//sprite
		Sprite m_Sprite;
		//Texture
		Texture m_Texture;

		// screen Resolution
		Vector2f m_Resolution;

		// what is the current arena
		IntRect m_Arena;

		// sixe of tile of  each arena
		int m_TileSize;

		// direction of movement
		bool m_UpPressed;
		bool m_DownPressed;
		bool m_LeftPressed;
		bool m_RightPressed;

		//Player health
		int m_Health;
		
		//max player health
		int m_MaxHealth;

		// when was player last hit
		Time m_LastHit;

		// Speed in Pixels per second
		float m_Speed;

public:

	Player();
	
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// call at end of game
	void resetPlayerStats();

	// handle player getting hit by Zombie
	bool hit(Time timeHit);

	// how long ago was the player hit
	Time getLastHitTime();

	// where is the player
	FloatRect getPosition();

	// where is the center of the player
	Vector2f getCenter();

	// player angle
	float getRotation();

	// send a copy of sprite to main
	Sprite getSprite();

	// move player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//Stop the player moving in a specific direction

	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	// call this once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// give player a speed boost
	void upgradeSpeed();

	// give health
	void upgradeHealth();

	//increase maximum amount of health
	void increaseHealthLevel(int amount);

	//current health
	int getHealth();
};