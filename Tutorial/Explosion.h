#pragma once
#include "graphics.h"
#include "config.h"
#include "gameobject.h"

class Explosion : public GameObject
{
	float pos_x, pos_y;
	graphics::Brush brush;
public:
	void update() override;
	void draw() override;
	void init() override;
	float getX() const { return pos_x; }
	float getY() const { return pos_y; }
	Explosion(const class Game& mygame,float,float);
	~Explosion();

};