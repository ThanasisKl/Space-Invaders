#include "ufo.h"

void Ufo::update()
{
	pos_x -=  ufo_speed * graphics::getDeltaTime();
}

void Ufo::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "enemy4.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 35, 17 ,br);             //Draw Ufo

	if (DEBUG_MODE)
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		graphics::drawDisk(pos_x, pos_y, getRadius(), br);
	}
}

void Ufo::init()
{
	pos_x = 1050;
	pos_y = 80;
}

Ufo::Ufo(const class Game& mygame)
	: GameObject(mygame)
{
	init();
}

Ufo::~Ufo()
{
}
