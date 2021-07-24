#pragma once
#include "graphics.h"
#include "config.h"
#include "gameobject.h"

class Bullet: public GameObject
{
	bool bullet_flag = false;
	bool flag = true;
	float pos_x, pos_y;
	float bullet_speed = 6.f;
	float radius = 5.0f;
	bool type;
	graphics::Brush br;
public:
	Bullet(const class Game& mygame, float, float, bool);
	unsigned int id = 0;
	bool invisible = false;
	void setId(int id_) { id = id_; }
	void resetId() { id = 0; }
	void resetBullet();
	float getX() const { return pos_x; }
	float getY() const { return pos_y; }
	float getRadius() const { return radius; }
	void update() override;
	void draw() override;
	void init() override;

};
