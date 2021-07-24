#include "Enemy.h"

void Enemy::update()
{
	pos_x += direction * enemy_speed * graphics::getDeltaTime();

	if (enemy_speed == 0.3f) // Όταν έχει μείνει μόνο ένας ζωντανός εχθρός
	{
		if (pos_x + (index % 12) * 50 > 980 && !movement_flag)
		{
			pos_y += 50;
			direction = -direction;
			movement_flag = true;
		}

		if (pos_x + (index % 12) * 50 < 20 && movement_flag)
		{
			pos_y += 50;
			direction = -direction;
			movement_flag = false;
		}
	}
	else
	{
		if (pos_x > 425 && !movement_flag)
		{
			pos_y += 50;
			direction = -direction;
			movement_flag = true;
		}

		if (pos_x < 20 && movement_flag)
		{
			pos_y += 50;
			direction = -direction;
			movement_flag = false;
		}
	}
}


void Enemy::draw()
{
	int x = (index % 12) * 50;
	int y = (index / 12) * 50;
	if (aliens_image && index >= 0 && index <= 11 ) {
		brush.texture = std::string(ASSET_PATH) + "enemy1_closed.png";
	}
	else if(index >= 0 && index <= 11)
	{
		brush.texture = std::string(ASSET_PATH) + "enemy1_open.png";
	}
	else if (aliens_image && index >= 12 && index <= 35) {
		brush.texture = std::string(ASSET_PATH) + "enemy2_closed.png";
	}
	else if (index >= 12 && index <= 35)
	{
		brush.texture = std::string(ASSET_PATH) + "enemy2_open.png";
	}
	else if (aliens_image && index >= 36 && index <= 47) {
		brush.texture = std::string(ASSET_PATH) + "enemy3_closed.png";
	}
	else 
	{
		brush.texture = std::string(ASSET_PATH) + "enemy3_open.png";
	}
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x + x, pos_y - y, 25, 25, brush);          //Draw Aliens
	
	if (DEBUG_MODE) {
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		graphics::drawDisk(pos_x + x, pos_y - y, radius, br);
	}
}

void Enemy::init()
{
	pos_x = CANVAS_WIDTH - 925;
	pos_y = CANVAS_HEIGHT - 270 ;
}

Enemy::Enemy(const class Game& mygame,int i)
	:GameObject(mygame)
{
	index = i;
	init();
}

Enemy::~Enemy()
{
	
}


