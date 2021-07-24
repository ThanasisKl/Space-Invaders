#pragma once
#include "gameobject.h"
#include "config.h"
#include "graphics.h"

class Player : public GameObject
{
	float player_speed = 10.0f;
	float pos_x, pos_y;
	int lives = 3;
	float radius = 25.0f;
public:
	Player(const class Game& mygame);
	~Player();
	void update()override;
	void draw()override;
	void draw_lives();
	void init()override;
	float getY() const { return pos_y;}
	float getX() const { return pos_x; }
	float getRadius() const { return radius; }
	int getLives() const { return lives; }
	void drainLives() { lives--; }
	void resetLives() { lives = 3; }
	void resetPosition() { pos_x = CANVAS_WIDTH / 2;}
};
