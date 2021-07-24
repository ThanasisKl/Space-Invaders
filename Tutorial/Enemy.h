#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"

class Enemy : public GameObject
{
	float pos_x, pos_y;
	int index;
	graphics::Brush brush;
	float enemy_speed = 0.025f;
	float radius = 16.0f;
	int direction = 1;
	bool movement_flag = false;
	bool aliens_image = true;
public:
	void update();
	void draw();
	void init();
	float getX(int i) const { return pos_x + (i % 12) * 50; }
	float getY(int i) const { return pos_y - (i / 12) * 50; }
	float getRadius() const { return radius; }
	void setSpeed(float speed) { enemy_speed = speed; }
	void swapImage() { aliens_image = !aliens_image; }
	Enemy(const class Game& mygame, int index);
	~Enemy();

};
