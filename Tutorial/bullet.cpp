#include "bullet.h"

Bullet::Bullet(const class Game& mygame,float x, float y, bool t)
	:GameObject(mygame)
{
	pos_x = x;
	pos_y = y;
	type = t;          // Το type καθορίζει τον τύπο της σφαίρας δηλαδή αν είναι παίχτη ή εχθρού 
	init();
}

void Bullet::resetBullet()
{
	pos_y = -20.0f;
}

void Bullet::update()
{
	if (type)
		pos_y -= bullet_speed * graphics::getDeltaTime() / 10.0f;
	else 
		pos_y += bullet_speed/2.5f * graphics::getDeltaTime() / 10.0f;
}

void Bullet::draw()
{
	br.outline_opacity = 0.0f;
	br.texture = "";
	if(invisible)
		br.fill_opacity = 0.0f;
	else
		br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f; 
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.gradient = true;
	graphics::drawDisk(pos_x, pos_y - 20, 5, br);    //Draw Bullet
}

void Bullet::init()
{
}

