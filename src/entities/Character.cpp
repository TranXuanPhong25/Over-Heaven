#include "Character.h"
Character::Character()
{
	speed_ = DEFAULT_SPEED;
	vel_ = {0, 0};
	state_ = IDLE_RIGHT;
	spacekey_pressed_ = false;
	/*accelerator_ = 0;*/
	on_ground_ = false;
	dir_left_ = 0;
	dir_right_ = 0;
	gravity_scalar_ = DEFAULT_SCALAR;
	jump_count_ = 1;

	// dashing_ = false;
	// dash_counter_ = 1;
	// dashing_frame_ = 0;
	// dash_dir_ = 0;
	// dash_cooldown_ = 0;
	required_frame_to_apply_jump_ = 0;
	wall_collided_ = false;
	collide_x_ = false;
	coyote_time_ = 0;
	/*jump_buffer_ = 0;*/
	should_change_level_ = false;
}
Character::~Character()
{
	free();
}

void Character::handleInput(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{

		if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)
		{
			spacekey_pressed_ = true;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a))
		{

			dir_left_ = 1;
			if (state_ < JUMP_LEFT)
			{
				state_ = MOVE_LEFT;
			}

			if (state_ == JUMP_RIGHT)
			{
				state_ = JUMP_LEFT;
			}
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d))
		{
			dir_right_ = 1;
			if (state_ < JUMP_LEFT)
			{
				state_ = MOVE_RIGHT;
			}

			if (state_ == JUMP_LEFT)
			{
				state_ = JUMP_RIGHT;
			}
		}
		// dash
		/*if (e.key.keysym.sym == SDLK_LSHIFT && e.key.repeat == 0) {

			if (dash_counter_ && !dash_cooldown_) {
				if (state_ == MOVE_LEFT || state_ == IDLE_LEFT || state_ == JUMP_LEFT) {
					state_ = DASH_LEFT;
					dash_dir_ = LEFT;
				}
				else if (state_ == MOVE_RIGHT || state_ == IDLE_RIGHT || state_ == JUMP_RIGHT) {
					state_ = DASH_RIGHT;
					dash_dir_ = RIGHT;
				}

				dashing_ = true;
				if (dash_counter_)dash_counter_--;
			}
		}*/
	}
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)
		{
			spacekey_pressed_ = false;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a))
		{
			if (state_ < JUMP_LEFT)
			{
				state_ = IDLE_LEFT;
			}
			dir_left_ = 0;
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d))
		{
			dir_right_ = 0;
			if (state_ < JUMP_LEFT)
			{
				state_ = IDLE_RIGHT;
			}
		}
	}
}

Vector2D Character::getVel() const
{
	return vel_;
}
bool Character::checkCollision(const SDL_Rect &a, const SDL_Rect &s)
{
	return a.x < s.x + s.w &&
		   a.x + a.w > s.x &&
		   a.y < s.y + s.h &&
		   a.y + a.h > s.y;
}
void Character::update(Level &level, Camera &cam, const float &dT)
{

	// if (dashing_) {
	//	dash(dT);
	// }
	// else {
	moveX(dT);
	//}
	CollideX(level);
	moveY(dT);
	CollideY(level);
	handleReachGoal(level, cam);
}
void Character::handleReachGoal(Level &level, Camera &cam)
{
	if (should_change_level_)
	{
		level.toNextLevel();
		cam.setPosition(0, 0);
		pos_.x = TILE_SIZE * 3;
		pos_.y = 0;
		saveStats();
		should_change_level_ = false;
	}
}
void Character::moveX(const float &dT)
{
	vel_.x = (dir_right_ - dir_left_) * speed_;
	pos_.x += vel_.x * dT;
}
void Character::handleCollideX(const int &x, const int &y, Level::Tile tile)
{
	SDL_Rect tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
	if (checkCollision({(int)pos_.x, (int)pos_.y, rect_.w, rect_.h}, tileRect))
	{
		if (tile == Level::GROUND)
		{
			collide_x_ = true;
			if (!on_ground_)
				wall_collided_ = true;
			if (vel_.x > 0)
			{
				pos_.x = tileRect.x - rect_.w;
			}
			else if (vel_.x < 0)
			{
				pos_.x = tileRect.x + tileRect.w;
			}
		}

		if (tile == Level::GOAL)
		{
			should_change_level_ = true;
			return;
		}
	}
}

void Character::CollideX(Level &level)
{
	int tileX = pos_.x / TILE_SIZE;
	int tileY = pos_.y / TILE_SIZE;
	int startX = max(0, tileX - 1);
	int startY = max(0, tileY - 1);
	int endX = min(level.getWidth(), (pos_.x + rect_.w) / TILE_SIZE + 1);
	int endY = min(level.getHeight(), (pos_.y + rect_.h) / TILE_SIZE + 1);
	wall_collided_ = false;
	collide_x_ = false;
	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			handleCollideX(x, y, level.getTile(x, y));
		}
	}
}

// void Character::dash(const float& dT) {
//	if (dashing_frame_ < MAX_DASH_FRAMES) {
//		vel_.x = dash_dir_ * speed_ * DASH_FORCE;
//		pos_.x += vel_.x * dT;
//		dashing_frame_++;
//		vel_.y = 0;
//	}
//	else {
//		dashing_frame_ = 0;
//		dashing_ = false;
//		dash_cooldown_ = DASH_COOLDOWN;
//		if (state_ == DASH_LEFT) state_ = IDLE_LEFT;
//		if (state_ == DASH_RIGHT) state_ = IDLE_RIGHT;
//	}
//
// }
void Character::jump(const float &dT)
{
	if (state_ == MOVE_LEFT || state_ == IDLE_LEFT /*|| state_ == DASH_LEFT*/)
		state_ = JUMP_LEFT;
	if (state_ == MOVE_RIGHT || state_ == IDLE_RIGHT /*|| state_ == DASH_LEFT*/)
		state_ = JUMP_RIGHT;
	on_ground_ = false;
	vel_.y = -JUMP_HEIGHT;
	coyote_time_ = 0;
	gravity_scalar_ = DEFAULT_SCALAR;
	/*jump_buffer_ = 0;*/
	required_frame_to_apply_jump_ = 50;
}

void Character::applyGravity(const float &dT)
{

	if (vel_.y > FLOATY_FALL_VEL)
	{
		gravity_scalar_ = FALL_SCALAR;
	}
	else if (vel_.y > -FLOATY_FALL_VEL)
	{
		gravity_scalar_ = FLOATY_SCALAR;
	}
	else
	{

		if (spacekey_pressed_)
		{
			if (required_frame_to_apply_jump_ > 46)
			{
				gravity_scalar_ = DEFAULT_SCALAR;
			}
			else if (required_frame_to_apply_jump_ == 46)
			{
				vel_.y = -JUMP_HEIGHT;
				gravity_scalar_ -= (gravity_scalar_ > MIN_SCALAR) ? REDUCE_SCALAR * 2.75 : 0;
			}
			else if (required_frame_to_apply_jump_ > 32 && required_frame_to_apply_jump_ < 46)
			{
				gravity_scalar_ -= (gravity_scalar_ > MIN_SCALAR) ? REDUCE_SCALAR * 2 : 0;
			}
		}
		else
		{
			gravity_scalar_ = DEFAULT_SCALAR;
		}
	}

	if (wall_collided_ && vel_.y > 0)
	{
		gravity_scalar_ = FRICTION_SCALAR;
	}
	if (vel_.y > MAX_FALL_SPEED)
	{
		vel_.y = MAX_FALL_SPEED;
	}
	else
	{
		vel_.y += GRAVITY * gravity_scalar_ * dT;
	}
}

void Character::moveY(const float &dT)
{
	if (required_frame_to_apply_jump_)
		required_frame_to_apply_jump_--;
	if (spacekey_pressed_ /*|| jump_buffer_*/)
	{
		if (on_ground_ || coyote_time_)
		{
			jump(dT);
		}
		/*if (spacekey_pressed_) jump_buffer_ = MAX_JUMP_BUFFER;*/
	}

	/*if (jump_buffer_) {
		jump_buffer_--;
	}*/

	if (!on_ground_ /*&& !dashing_*/)
	{
		if (coyote_time_)
			coyote_time_--;
		applyGravity(dT);
	}
	else if (on_ground_)
	{
		required_frame_to_apply_jump_ = 0;
		// dash_counter_ = 1;
		coyote_time_ = MAX_COYOTE_TIME;
		vel_.y = 0;
	}

	/*if (!dashing_) {
		if (dash_cooldown_ - dT > 0) {
			dash_cooldown_ -= dT;
		}
		else dash_cooldown_ = 0;
	}*/
	pos_.y += vel_.y * dT;
}
void Character::handleCollideY(const int &x, const int &y, const int &endY, Level::Tile tile, bool &somethingBelow)
{
	SDL_Rect tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
	if (tile == Level::GROUND)
	{
		if (y == endY)
		{
			somethingBelow = true;
		}
		if (checkCollision({(int)pos_.x, (int)pos_.y, rect_.w, rect_.h}, tileRect))
		{
			if (vel_.y >= 0)
			{
				on_ground_ = true;
				vel_.y = 0;
				pos_.y = tileRect.y - rect_.h;
			}
			else if (vel_.y < 0)
			{
				vel_.y = 0;
				pos_.y = tileRect.y + tileRect.h;
			}
		}
	}
	if (tile == Level::GOAL)
	{
		should_change_level_ = true;
	}
}
void Character::CollideY(Level &level)
{
	int tileX = pos_.x / TILE_SIZE;
	int tileY = pos_.y / TILE_SIZE;
	int startX = max(0, tileX);
	int startY = max(0, tileY);
	int endX = min(level.getWidth(), (pos_.x + rect_.w) / TILE_SIZE);
	int endY = min(level.getHeight(), (pos_.y + rect_.h) / TILE_SIZE);
	bool somethingBelow = false;

	for (int y = startY; y <= endY; y++)
	{
		for (int x = startX; x <= endX; x++)
		{
			handleCollideY(x, y, endY, level.getTile(x, y), somethingBelow);
		}
	}
	if (!somethingBelow)
	{
		on_ground_ = false;
	}
}
void Character::saveStats()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *root = doc.NewElement("SaveData");
	doc.InsertFirstChild(root);
	tinyxml2::XMLElement *playerPos = doc.NewElement("PlayerPosition");
	playerPos->SetAttribute("x", static_cast<int>(pos_.x));
	playerPos->SetAttribute("y", static_cast<int>(pos_.y));
	// save another member variable

	root->InsertEndChild(playerPos);

	doc.SaveFile("save/save_game.xml");
}
void Character::loadStats(Level &level)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("save/save_game.xml") != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Failed to load save file." << std::endl;
	}

	tinyxml2::XMLElement *root = doc.FirstChildElement("SaveData");
	if (!root)
	{
		std::cout << "Save file is missing SaveData element." << std::endl;
		return;
	}
	
	pos_.x = PLAYER_DEFAULT_POS[level.getLevelIndex()][0];
	pos_.y = PLAYER_DEFAULT_POS[level.getLevelIndex()][1];

	tinyxml2::XMLElement *playerPos = root->FirstChildElement("PlayerPosition");
	if (playerPos)
	{
		int posX=-1,posY=-1;
		playerPos->QueryIntAttribute("x", &posX);
		playerPos->QueryIntAttribute("y", &posY);
		pos_.x = posX==-1?pos_.x:posX;
		pos_.y = posY==-1?pos_.y:posY;
	}
	else
	{
		saveStats();
		std::cout << "Save file is missing PlayerPosition element." << std::endl;
	}
}
