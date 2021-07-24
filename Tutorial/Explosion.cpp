#include "Explosion.h"

void Explosion::update()
{

}

void Explosion::draw()
{
	brush.texture = std::string(ASSET_PATH) + "explosion.png";  //Draw Explosion
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 25, 25, brush);
}

void Explosion::init()
{

}

Explosion::Explosion(const class Game& mygame,float x, float y)
	:GameObject(mygame)
{
	pos_x = x;
	pos_y = y;
	init();
}

Explosion::~Explosion()
{
}
