#include "player.h"


Player::Player(const class Game& mygame)
	:GameObject(mygame)
{
	init();
}

Player::~Player()
{
}

void Player::update()
{ 
	
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) 
	{
		pos_x -= player_speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += player_speed * graphics::getDeltaTime() / 10.0f;
	}

	if (pos_x < 0)
		pos_x = 0;

	if (pos_x > CANVAS_WIDTH)
		pos_x = CANVAS_WIDTH;

	if (pos_y < 0)
		pos_y = 0;

	if (pos_y > CANVAS_HEIGHT)
		pos_y = CANVAS_HEIGHT;
}

void Player::draw() 
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);

	graphics::Brush br;
	
	br.texture = std::string(ASSET_PATH) + "spaceship.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 50, 50, br);        //Draw Spaceship

	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true; 
	graphics::drawDisk(pos_x, pos_y + 20, 10, br);    //Draw Fire

	if (DEBUG_MODE)
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		graphics::drawDisk(pos_x, pos_y, getRadius(), br);
	}
}

void Player::draw_lives()          //Εμφανίζει τις διαθέσιμες ζωές στην οθόνη
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "heart.png";
	br.outline_opacity = 0.0f;
	if(lives>=1)
		graphics::drawRect(965, 35, 35, 35, br);
	if (lives >= 2)
		graphics::drawRect(925, 35, 35, 35, br);
	if (lives == 3)
		graphics::drawRect(885, 35, 35, 35, br);
}

void Player::init() 
{
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2 + 185;
}

