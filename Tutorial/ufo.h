#pragma once
#include "graphics.h"
#include "config.h"
#include "gameobject.h"

class Ufo : GameObject
{
	float pos_x, pos_y;
	graphics::Brush brush;
	float ufo_speed = 0.2f;
	float radius = 18.0f;
public:
	void update() override;
	void draw() override;
	void init() override;
	float getX() const { return pos_x; }
	float getY() const { return pos_y; }
	float getRadius() const { return radius; }
	Ufo(const class Game& mygame);
	~Ufo();
	
};

