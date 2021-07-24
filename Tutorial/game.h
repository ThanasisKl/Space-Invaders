#pragma once
#include "player.h"
#include "Enemy.h"
#include "bullet.h"
#include "ufo.h"
#include "Explosion.h"
#include "config.h"
#include <vector> 
#include "graphics.h"
#include <random>

class Game
{
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_FINISH} status_t;
	bool player_initialized = false;
	bool aliens_initialized = false;
	bool ufo_initialized = false;
	bool explosion_initialized = false;
	bool aliens_movement = false;
	bool first_bullet = true;
	bool first_bullet2 = true;
	bool shoot = true;
	bool shoot2 = true;
	int next_id = 0;
	int next_id2 = 0;
	int swap = 0;
	int score = 0;
	bool ufo23 = true;  
	bool ufo40 = true;
	float creation_time;
	float aliens_initialized_time;
	std::vector<int> bullet_vec;
	std::vector<int> bullet2_vec;
	std::vector<int> shooting_aliens;
	void checkCollisionWithShip();
	status_t status = STATUS_START;
	int dead_aliens = 0;
	Player* player = nullptr;
	Bullet* bullet = nullptr;
	Bullet* bullet2 = nullptr;
	Ufo* ufo = nullptr;
	Enemy* alien[ALIENS_NUMBER];
	Explosion* explosion = nullptr;
	void updateStartScreen();
	void updateLevelScreen();
	void updateFinishScreen();
	void drawStartScreen();
	void drawLevelScreen();
	void drawFinishScreen();
	void checkCollisionWithUfo();
	void checkCollisionWithBullet();
	void checkCollisionWithBullet2();
	void fill_array() { for (int i = 0; i < ALIENS_NUMBER; i++) { alien[i] = nullptr; } }
	void setSpeed();
	void createExplosion(float, float);
	int find_alien_2shoot();
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();
};

