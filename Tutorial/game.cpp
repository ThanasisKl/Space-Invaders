#include "game.h"

void Game::checkCollisionWithUfo()  //Η συνάρτηση αυτή ελέγχει αν υπάρχει σύγκρουση μεταξύ της σφάιρας που εκτοξεύει ο παίκτης και του ufo. Αν υπάρξει διαγράφεται το ufo και δημιουργείτε έκρηξη στην θέση του.
{
	if (bullet && ufo) 
	{
		float dx = bullet->getX() - ufo->getX();
		float dy = bullet->getY() - ufo->getY();

		if (sqrt(dx * dx + dy * dy) < ufo->getRadius() + bullet->getRadius())
		{
			if (!std::count(bullet_vec.begin(), bullet_vec.end(), bullet->id)) {
				createExplosion(ufo->getX(), ufo->getY());
				delete ufo;
				ufo = nullptr;
				ufo_initialized = false;
				bullet->invisible = true;
				score += 70;         // Το UFO δένει 70 πόντους
				graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.2f, false);
			}
		}
	}
}

void Game::checkCollisionWithShip() //Η συνάρτηση αυτή ελέγχει αν υπάρχει σύγκρουση μεταξύ του παίκτη και του των εχθρών. Αν υπάρξει τελειώνει το παιχνίδι με game over.
{
	for (int index = 0; index < ALIENS_NUMBER; index++) {

		if (player && alien[index]) {
			float dx = player->getX() - alien[index]->getX(index); 
			float dy = player->getY() - alien[index]->getY(index);

			if (player->getY() < alien[index]->getY(index))
			{
				graphics::stopMusic();
				graphics::playSound(std::string(ASSET_PATH) + "game-over_sound.mp3", 0.3f, false);
				status = STATUS_FINISH;
			}

			if (sqrt(dx * dx + dy * dy) < player->getRadius() + alien[index]->getRadius())
			{
				delete alien[index];
				alien[index] = nullptr;
				graphics::stopMusic();
				graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.2f, false);
				graphics::playSound(std::string(ASSET_PATH) + "game-over_sound.mp3", 0.3f, false);
				status = STATUS_FINISH;
			}
		}
	}
}

void Game::checkCollisionWithBullet2() //Η συνάρτηση αυτή ελέγχει αν υπάρχει σύγκρουση μεταξύ της σφάιρας που εκτοξεύει κάποιος εχθρός και του παίκτη. Αν υπάρξει ο παίκτης χάνει μια ζωή και αν είναι η τελευταία του το παιχνίδι τελειώνει με game over.
{
	if (player && bullet2)
	{
		float dx = bullet2->getX() - player->getX();
		float dy = bullet2->getY() - player->getY();
		if (sqrt(dx * dx + dy * dy) < player->getRadius() + bullet2->getRadius())
		{
			if (!std::count(bullet2_vec.begin(), bullet2_vec.end(), bullet2->id)) 
			{
				bullet2_vec.push_back(bullet2->id); //Αποθηκεύουμε το id ώστε να μην χτυπήσει παραπάνω από μία φορά μία σφαίρα τον παίχτη
				player->drainLives();                // Αν χτυπηθεί ο παίκτης απο εχθρική σφαίρα οι ζωές του μειώνονται κατα 1 
				graphics::playSound(std::string(ASSET_PATH) + "life-lost.mp3", 0.2f, false);
				bullet2->invisible = true;
				if (player->getLives() == 0)       
				{
					graphics::stopMusic();
					graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.2f, false);
					graphics::playSound(std::string(ASSET_PATH) + "game-over_sound.mp3", 0.3f, false);
					status = STATUS_FINISH;
				}
			}
		}
	}
}

void Game::checkCollisionWithBullet()//Η συνάρτηση αυτή ελέγχει αν υπάρχει σύγκρουση μεταξύ της σφάιρας που εκτοξεύει ο παίκτης με κάποιον εχθρό. Αν υπάρξει ο εχθρός διαγράφεται και δημιουργείται έκρηξη στο σημείο του.
{
	for (int index = 0; index < ALIENS_NUMBER; index++) 
	{
		
		if (player && alien[index] && bullet) {
			int temp = bullet->id;
			float dx = bullet->getX() - alien[index]->getX(index);
			float dy = bullet->getY() - alien[index]->getY(index);

			if (sqrt(dx * dx + dy * dy) < alien[index]->getRadius() + bullet->getRadius())
			{
				if (!std::count(bullet_vec.begin(), bullet_vec.end(), bullet->id)) {
					createExplosion(alien[index]->getX(index), alien[index]->getY(index));
					graphics::playSound(std::string(ASSET_PATH) + "explosion.mp3", 0.2f, false);
					dead_aliens++;
					setSpeed();
					delete alien[index];
					alien[index] = nullptr;
					
					if (dead_aliens == ALIENS_NUMBER) {
						status = STATUS_FINISH;
						graphics::stopMusic();
						graphics::playSound(std::string(ASSET_PATH) + "you-win_sound.mp3", 1.0f, false);
					}

					if (dead_aliens == ALIENS_NUMBER - 1 ){
						graphics::stopMusic();
						graphics::playMusic(std::string(ASSET_PATH) + "last_alien_music.mp3", 1.0f, true, 4000);
					}

					bullet->invisible = true;
					if (index >= 0 && index <= 11) {    // Ανάλογα με το είδος του εχθρού υπάρχουν και αντίστοιχοι πόντοι. Η κατώτερη σειρά δίνει 10 πόντους
						score += 10;                   
					}
					else if (index >= 12 && index <= 35) // Οι 2 μεσαίες 20 πόντους
					{
						score += 20;
					}
					else
					{
						score += 30;                    // Η ανώτερη 30
					}
					bullet_vec.push_back(bullet->id);   //Αποθηκεύουμε το id ώστε να μην χτυπήσει παραπάνω από έναν εχθρό μία σφαίρα
				}
			
			}
		}
	}
}

void Game::createExplosion(float x , float y) //Δημιουργία έκρηξης
{
	explosion = new Explosion(*this, x, y);
	creation_time = graphics::getGlobalTime();
}

void Game::updateStartScreen() 
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed)  // Αν κάνει κλικ ο χρήστης ξεκινάει το παιχνίδι
	{
		status = STATUS_PLAYING;
	}
}

void Game::updateLevelScreen()
{
	if (!aliens_initialized)
	{
		fill_array();         // κάθε εχθρός αρχικοποιέιται με nullptr
	}

	if (!player_initialized && graphics::getGlobalTime() > 3000)  
	{
		player = new Player(*this);      // Δημιουργία παίχτη
		player_initialized = true;
	}

	if (!aliens_initialized && graphics::getGlobalTime() > 2000)
	{
		for (int index = 0; index < ALIENS_NUMBER; index++) 
		{
			alien[index] = new Enemy(*this, index);       // Δημιουργία εχθρών
		}
		aliens_initialized = true;
		aliens_initialized_time = graphics::getGlobalTime();
	}

	if (player)
		player->update();
	
	if (player) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE) && shoot)
		{
			shoot = false;
			bullet = new Bullet(*this, player->getX(), player->getY(),true);  // Δημιουργία σφάιρας που εκτοξεύει ο παίκτης
			bullet->setId(next_id);       //Κάθε σφαίρα έχει ένα id το οποίο την προσδιορίζει μοναδικά και η χρησιμότητα ειναι να σκοτώνει μονο έναν εχθρό
			graphics::playSound(std::string(ASSET_PATH) + "shoot.ogg", 0.1f, false);

			if (first_bullet) 
			{
				first_bullet = false;
				bullet->resetId();     // το id ξεκινάει απο 0 στο play again και στην αρχή.
			}
		}
	}

	
	if (bullet) {
		bullet->update();
		if (bullet->getY() < 0)
		{
			next_id = bullet->id + 1; // id επόμενης σφαίρας
			delete bullet;   // διαγραφή σφαίρας παίχτη
			bullet = nullptr;
			shoot = true;
		}
	}
	
	if (dead_aliens != ALIENS_NUMBER - 1 && aliens_initialized && (graphics::getGlobalTime() -  aliens_initialized_time > 3000)) 
	{
			if (shoot2)
			{
				shooting_aliens.clear();
				int alien_index = find_alien_2shoot();  // βρίσκουμε το index ενός εχθρού που μπορεί να πυροβολήσει
				if (alien_index != -1) 
				{
					shoot2 = false;
					bullet2 = new Bullet(*this, alien[alien_index]->getX(alien_index), alien[alien_index]->getY(alien_index), false); //Δημιουργία σφάιρας που εκτοξεύει ο εχθρός
					bullet2->setId(next_id2);  // Το id χρησομοποιείται ώστε κάθε σφαίρα να χτυπαέι μία φορά τον παιχτή

					if (first_bullet2)
					{
						first_bullet2 = false;
						bullet2->resetId();
					}
				}
			}

	}

	if (bullet2) {
		bullet2->update();
		if (bullet2->getY() > 700)
		{
			next_id2 = bullet2->id + 1;
			delete bullet2;  // διαγραφή σφαίρας εχθρού
			bullet2 = nullptr;
			shoot2 = true;
		}
	}
	


	if (aliens_initialized && graphics::getGlobalTime() > 3000) {
		for (int index = 0; index < ALIENS_NUMBER; index++) {
			if(alien[index])
				alien[index]->update();
		}
	}

	if (dead_aliens == 23 && ufo23)
	{
		ufo_initialized = true;
		ufo = new Ufo(*this);
		ufo23 = false;
	}

	if (dead_aliens == 40 && ufo40)
	{
		ufo_initialized = true;
		ufo = new Ufo(*this);
		ufo40 = false;
	}

	if (ufo) {
		ufo->update();

		if (ufo->getX() > 1000)
			graphics::playSound(std::string(ASSET_PATH) + "ufo.ogg", 0.01f, false);

		if (ufo->getX() < -20)
		{
			delete ufo;  //Διαγραφή UFO
			ufo = nullptr;
			ufo_initialized = false;
		}
	}


	if (explosion) {
		explosion->update();
		if (graphics::getGlobalTime() - creation_time > 50)
		{
			delete explosion;   //Διαγραφή έκρηξης
			explosion = nullptr;
		}
	}

	if (ufo)
		checkCollisionWithUfo();

	checkCollisionWithShip();
	checkCollisionWithBullet();
	checkCollisionWithBullet2();
}

void Game::updateFinishScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {   // Ο χρήστης επιθυμεί να ξανά παίξει πατώντας Enter
		
		aliens_initialized = false;
		ufo_initialized = false;
		bullet_vec.clear();
		bullet2_vec.clear();
		dead_aliens = 0;
		score = 0;
		first_bullet = true;
		next_id = 0;
	    ufo23 = true;
		ufo40 = true;
		first_bullet2 = true;
		next_id2 = 0;
		graphics::playMusic(std::string(ASSET_PATH) + "backround_music.mp3", 0.8f, true, 4000);
		player->resetLives();           // Η ζωές του παίχτη γίνονται και πάλι 3
 		player->resetPosition();        // Ο παίχτης τοποθετέιται στην μέση

		if (bullet)
			bullet->resetBullet();

		for (int i = 0; i < ALIENS_NUMBER; i++)
			if (alien[i])
				delete alien[i];

		if (ufo)
		{
			delete ufo;
			ufo = nullptr;
		}
		status = STATUS_START;
	}
}


void Game::drawStartScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "logo.png";     // Εικόνα αρχικής οθόνης
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2 , 200, 600 , 400 , br);

	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	char info[40];
	sprintf_s(info, "Click  to  start");
	graphics::drawText(CANVAS_WIDTH/2 - 100, 450, 30, info, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.3f;
	br.fill_color[2] = 0.0f;
	char info2[70];
	sprintf_s(info2, "Use  left  and  right  arrow  to  move  and  space  to  shoot");
	graphics::drawText(CANVAS_WIDTH / 2 - 185, 475, 15, info2, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	
	
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::setWindowBackground(br);

	if (player)
		player->draw();

	swap++;
	int limit;
	if (dead_aliens == ALIENS_NUMBER - 1) 
	{
		limit = 25;
	}
	else if (dead_aliens >= ALIENS_NUMBER / 2)
	{
		limit = 45;
	}
	else
	{
		limit = 55;
	}

	if (swap > limit) {
		for (int index = 0; index < ALIENS_NUMBER; index++) {
			if (alien[index])
				alien[index]->swapImage();    // Δημιουγεί την εντύπωση ότι ο εχθρός "πετάει" εναλλάσοντας τις 2 εικόνες του
		}
		swap = 0;
	}

	if (aliens_initialized) {
		for (int index = 0; index < ALIENS_NUMBER; index++) {
			if (alien[index])
				alien[index]->draw();
		}
	}

	if (bullet)
		bullet->draw();

	if (bullet2)
		bullet2->draw();

	if (player)
	{
		graphics::Brush br;
		char info[40];
		sprintf_s(info, "SCORE  %d", score);
		graphics::drawText(50, 50, 30, info, br);
	}

	if (ufo)
		ufo->draw();

	if (explosion) 
		explosion->draw();
	
	if (player)
	{
		player->draw_lives();
	}
}

void Game::drawFinishScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::setWindowBackground(br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	if (dead_aliens != ALIENS_NUMBER || player->getLives() == 0) {  // Ο χρήστης έχασε
		br.texture = std::string(ASSET_PATH) + "game_over.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, 150, 300, 170, br);
	}
	else                                                           // Ο χρήστης νίκησε
	{
		br.texture = std::string(ASSET_PATH) + "you_win.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, 150, 300, 170, br);
	}
	

	br.texture = "";
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100);
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	char info[40];
	sprintf_s(info, "Press  Enter  to  Play  Again");
	graphics::drawText(CANVAS_WIDTH / 2 - 190, 390, 30, info, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	char info2[40];
	sprintf_s(info2, "Press  Esc  to  Exit  the Game");
	graphics::drawText(CANVAS_WIDTH / 2 - 190, 450 , 30, info2, br);

	char info3[40];
	sprintf_s(info3, "Your  Score  %d",score);
	graphics::drawText(CANVAS_WIDTH / 2 - 100, 320, 30, info3, br);
}

void Game::update()
{	
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if(status == STATUS_PLAYING)
	{
		updateLevelScreen();
	}
	else
	{
		updateFinishScreen();
	}
}

void Game::draw() 
{

	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
	else
	{
		drawFinishScreen();
	}
}

void Game::setSpeed()
{
	for (int i = 0; i < ALIENS_NUMBER; i++) {
		if (alien[i]) {
			if(dead_aliens == ALIENS_NUMBER / 2)  // Αν έχουν μείνει οι μισοί εχθροί ζωντανοί τοτε αυξάνουμε την ταχύτητα τους από εδώ και στο εξής
				alien[i]->setSpeed(0.045f);
			if (dead_aliens == ALIENS_NUMBER - 1)  // Ο τελευταιός ζωντανός εχθρός κινείται πολύ γρήγορα
				alien[i]->setSpeed(0.3f);
		}
	}
}

int Game::find_alien_2shoot()  // Η συνάρτηση αυτή υπολογίζει το index ενός ζωντανού εχθρού που μπορέι να πυροβολήσει
{
	for (int i = 0; i < ALIENS_NUMBER; i++) // Για να μπορεί να πυροβολήσει θα πρεπει να είναι ζωντανός και να μην υπάρχουν απο κάτω του άλλοι εχθροί και αυτό διασφαλίζεται με τους παρακάτω ελέγχους
	{                                       // Υπολογίζουμε όλους τους εχθρούς που μπορούν να πυροβολήσουν
		if (alien[i] && i >= 0 && i <= 11)
		{
			shooting_aliens.push_back(i);
		}

		if (alien[i] && !alien[i - 12] && i >= 12 && i <= 23)
		{
			shooting_aliens.push_back(i);
		}

		if (alien[i] && !alien[i - 12] && !alien[i - 24] && i >= 24 && i <= 35)
		{
			shooting_aliens.push_back(i);
		}

		if (alien[i] && !alien[i - 12] && !alien[i - 24] && i >= 36 && !alien[i - 36] && i <= 47)
		{
			shooting_aliens.push_back(i);
		}
	}
	if (shooting_aliens.size() != 0) 
	{
		int value = shooting_aliens[rand() % shooting_aliens.size()]; // Στο τέλος επιλέγεται ένας τυχαίος από όλους αυτούς που μπόρουν να πυροβολήσουν
		return value;
	}
	else
	{
		return -1;
	}
}

void Game::init() 
{
	graphics::setFont(std::string(ASSET_PATH) + "arcade.ttf");  //Fonts
	graphics::playMusic(std::string(ASSET_PATH) + "backround_music.mp3",0.8f,true,4000); //Game music
}


Game::Game()
{
}

Game::~Game() {

	if (player) 
		delete player;
	
	if (bullet)
		delete bullet;

	if (bullet2)
		delete bullet2;

	if (ufo)
		delete ufo;

	if (explosion)
		delete explosion;
	
	for (int i = 0; i < ALIENS_NUMBER; i++)
		if (alien[i])
			delete alien[i];
}


