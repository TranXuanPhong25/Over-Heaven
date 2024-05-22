#include "Character.hpp"
Character::Character()
{
	speed_ = DEFAULT_SPEED;
	vel_ = {0, 0};
	spacekey_pressed_ = false;

	on_ground_ = false;
	direction_ = RIGHT;
	dir_left_ = 0;
	dir_right_ = 0;
	gravity_scalar_ = DEFAULT_SCALAR;

	required_frame_to_apply_jump_ = 0;
	coyote_time_ = 0;
	should_change_level_ = false;

	frames_clips_.resize(NUM_ANIMATIONS);
	current_animation_ = IDLE;
	current_frame_ = 0;
	flip_ = false;

	animation_time_ = 0;
	jump_sound_ = NULL;
	land_sound_ = NULL;
	walk_sound_ = NULL;
}
Character::~Character()
{
	free();
	Mix_FreeChunk(jump_sound_);
	Mix_FreeChunk(land_sound_);
	Mix_FreeMusic(walk_sound_);
}
void Character::handleInput(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		handleKeyPressed(e);
	}
	if (e.type == SDL_KEYUP)
	{
		handleKeyReleased(e);
	}
}

void Character::handleKeyPressed(const SDL_Event &e)
{
	if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)
	{
		spacekey_pressed_ = true;
	}
	if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a))
	{
		dir_left_ = 1;
		direction_ = LEFT;
	}
	if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d))
	{
		dir_right_ = 1;
		direction_ = RIGHT;
	}
}
void Character::handleKeyReleased(const SDL_Event &e)
{
	if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)
	{
		spacekey_pressed_ = false;
	}
	if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a))
	{
		dir_left_ = 0;
	}
	if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d))
	{
		dir_right_ = 0;
	}
}

Vector2D Character::getVel() const
{
	return vel_;
}
bool Character::checkCollision(const SDL_Rect &a, const SDL_Rect &s)
{
	return a.x < s.x + s.w && a.x + a.w > s.x && a.y < s.y + s.h && a.y + a.h > s.y;
}
void Character::setDefaultPosition(Level &level)
{
	pos_.x = PLAYER_DEFAULT_POS[level.getLevelIndex()][0];
	pos_.y = PLAYER_DEFAULT_POS[level.getLevelIndex()][1];
}
void Character::update(Level &level, Camera &cam, const float &dT)
{

	moveX(dT);
	CollideX(level);
	moveY(dT);
	CollideY(level);
	animate(dT);
	handleSoundFx();
}
void Character::handleSoundFx()
{
	static bool playedLandSound = false;

	if (on_ground_)
	{
		if (current_animation_ == RUNNING)
		{
			if (dir_left_ != dir_right_)
			{
				if (Mix_PlayingMusic() == 0)
				{
					Mix_PlayMusic(walk_sound_, -1);
				}
			}
		}
		else if (current_animation_ == JUMPING)
		{
			if(!playedLandSound){
				if (Mix_PlayChannel(-1, land_sound_, 0) == -1)
				{
					printf("Failed to play sound! SDL_mixer Error: %s\n", Mix_GetError());
				}
				playedLandSound = true;
			}
		}
		else
		{
			Mix_HaltMusic();
		}
		
	}
	else
	{
		playedLandSound = false;
		Mix_HaltMusic();
	}

}
void Character::animate(const float &dT)
{
	animation_time_ += dT;
	if (animation_time_ < frame_duration_)
	{
		return;
	}
	animation_time_ -= frame_duration_;

	if (direction_ == LEFT)
	{
		flip_ = true;
	}
	else
	{
		flip_ = false;
	}

	int numFrames = frames_clips_[current_animation_].size();

	if (on_ground_)
	{
		current_frame_ = (current_frame_ + 1) % numFrames;
		if (dir_left_ != dir_right_ && current_animation_ == IDLE)
		{
			current_animation_ = RUNNING;
		}
		if (current_animation_ == RUNNING)
		{
			
			if (dir_left_ == dir_right_)
			{
				//continue play music 
				if (current_frame_ % numFrames == 0)
				{
					current_frame_ = 0;
					current_animation_ = IDLE;
				}
				else if (current_frame_ < frames_clips_[RUNNING].size() - 2)
				{
					current_frame_ = frames_clips_[RUNNING].size() - 2;
				}
			}
			
		}
		else if (current_animation_ == JUMPING)
		{
			
			if (current_frame_ % numFrames == 0)
			{
				current_frame_ = 0;
				current_animation_ = IDLE;
			}
			else if (current_frame_ < frames_clips_[JUMPING].size() - 4)
			{
				current_frame_ = frames_clips_[JUMPING].size() - 4;
			}
		}
	}
	else
	{
		current_animation_ = JUMPING;
		if (vel_.y < -600)
		{
			current_frame_ = current_frame_ < 4 ? (current_frame_ + 1) : 4;
		}
		else if (vel_.y < -FLOATY_FALL_VEL)
		{
			// loop between 4-5
			current_frame_ = (current_frame_ + 1) % 3 + 4;
		}
		else if (vel_.y < FLOATY_FALL_VEL)
		{
			current_frame_ = (current_frame_ + 1) % 2 + 7;
		}
		else
		{
			current_frame_ = (current_frame_ + 1) % 3 + 9;
		}
	}
}
void Character::handleReachGoal()
{
	should_change_level_ = false;
}
void Character::moveX(const float &dT)
{
	vel_.x = (dir_right_ - dir_left_) * speed_;
	pos_.x += vel_.x * dT;
}
void Character::GroundCollideX(const SDL_Rect &tileRect)
{
	if (vel_.x > 0)
	{
		pos_.x = tileRect.x - width_;
	}
	else if (vel_.x < 0)
	{
		pos_.x = tileRect.x + tileRect.w;
	}
}

void Character::handleCollideX(const int &x, const int &y, Level::Tile tile)
{
	SDL_Rect tileRect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
	if (checkCollision({(int)pos_.x, (int)pos_.y, width_, height_}, tileRect))
	{
		if (tile == Level::GROUND)
		{
			GroundCollideX(tileRect);
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
	int endX = min(level.getTileWidth(), static_cast<int>((pos_.x + width_) / TILE_SIZE + 1));
	int endY = min(level.getTileHeight(), static_cast<int>((pos_.y + height_) / TILE_SIZE + 1));
	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			handleCollideX(x, y, level.getTile(x, y));
		}
	}
}

void Character::jump(const float &dT)
{
	// play jump sound
	if (jump_sound_ != NULL)
	{
		if (Mix_PlayChannel(-1, jump_sound_, 0) == -1)
		{
			printf("Failed to play sound! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
	on_ground_ = false;
	vel_.y = -JUMP_HEIGHT;
	coyote_time_ = 0;
	gravity_scalar_ = DEFAULT_SCALAR;
	required_frame_to_apply_jump_ = 50;
}

bool Character::isReachedGoal() const
{
	return should_change_level_;
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
	else if (spacekey_pressed_)
	{
		// variable jump height
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
	if (spacekey_pressed_)
	{
		if (on_ground_ || coyote_time_)
		{
			jump(dT);
		}
	}

	if (!on_ground_)
	{
		if (coyote_time_)
			coyote_time_--;
		applyGravity(dT);
	}
	else if (on_ground_)
	{
		required_frame_to_apply_jump_ = 0;
		coyote_time_ = MAX_COYOTE_TIME;
		vel_.y = 0;
	}
	pos_.y += vel_.y * dT;
}
void Character::GroundCollideY(const SDL_Rect &tileRect)
{
	if (checkCollision({(int)pos_.x, (int)pos_.y, width_, height_}, tileRect))
	{
		if (vel_.y >= 0)
		{
			on_ground_ = true;
			vel_.y = 0;
			pos_.y = tileRect.y - height_;
		}
		else if (vel_.y < 0)
		{
			vel_.y = 0;
			pos_.y = tileRect.y + tileRect.h;
		}
	}
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
		GroundCollideY(tileRect);
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
	int endX = min(level.getTileWidth(), static_cast<int>((pos_.x + width_) / TILE_SIZE));
	int endY = min(level.getTileHeight(), static_cast<int>((pos_.y + height_) / TILE_SIZE));
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

void Character::saveStats() const
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *root = doc.NewElement("SaveData");
	doc.InsertFirstChild(root);
	tinyxml2::XMLElement *playerPos = doc.NewElement("PlayerPosition");
	playerPos->SetAttribute("x", static_cast<int>(pos_.x));
	playerPos->SetAttribute("y", static_cast<int>(pos_.y));
	root->InsertEndChild(playerPos);
	try
	{
		std::filesystem::create_directories("save");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	doc.SaveFile(SAVE_PATH);
}

void Character::loadStats(Level &level)
{
	resetStats();
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(SAVE_PATH) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Failed to load save file." << std::endl;
	}

	tinyxml2::XMLElement *root = doc.FirstChildElement("SaveData");
	if (!root)
	{
		std::cout << "Save file is missing SaveData element." << std::endl;
		return;
	}

	// default value will be set if position node not found
	setDefaultPosition(level);

	tinyxml2::XMLElement *playerPos = root->FirstChildElement("PlayerPosition");
	if (!playerPos)
	{
		saveStats();
		std::cout << "Save file is missing PlayerPosition element. \n -> Set position to default" << std::endl;
	}
	else
	{
		int posX = -1, posY = -1;
		playerPos->QueryIntAttribute("x", &posX);
		playerPos->QueryIntAttribute("y", &posY);
		pos_.x = posX == -1 ? pos_.x : posX;
		pos_.y = posY == -1 ? pos_.y : posY;
	}
}

void Character::resetStats()
{
	pos_ = {0, 0};
	vel_ = {0, 0};
	on_ground_ = false;
	spacekey_pressed_ = false;
	gravity_scalar_ = DEFAULT_SCALAR;
	required_frame_to_apply_jump_ = 0;
	coyote_time_ = 0;
	should_change_level_ = false;

	current_animation_ = 0;
	current_frame_ = 0;
	flip_ = false;

	dir_left_ = 0;
	dir_right_ = 0;

	animation_time_ = 0;
}



bool Character::loadSpriteSheetData(const std::string &path)
{

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Error opening file: " << path << std::endl;
		return false;
	}

	nlohmann::json spriteSheetData;
	try
	{
		spriteSheetData = nlohmann::json::parse(file);
	}
	catch (nlohmann::json::parse_error &e)
	{
		std::cout << "Error parsing JSON: " << e.what() << std::endl;
		return false;
	}

	sprite_sheet_path_ = spriteSheetData[IMAGES_PATH_KEY];
	frame_duration_ = spriteSheetData[FRAME_DURATION_KEY];
	rect_.w = spriteSheetData[FRAME_SIZE_KEY][WIDTH_KEY];
	rect_.h = spriteSheetData[FRAME_SIZE_KEY][HEIGHT_KEY];

	std::vector<nlohmann::json> idleClips = spriteSheetData[IDLE_ANIMATION_KEY];
	std::vector<nlohmann::json> jumpClips = spriteSheetData[JUMP_ANIMATION_KEY];
	std::vector<nlohmann::json> runClips = spriteSheetData[RUN_ANIMATION_KEY];

	int x, y, w, h;
	SDL_Rect rect;

	int index = 0;
	for (const auto &clips : {idleClips, jumpClips, runClips})
	{
		for (const auto &frame_clip_ : clips)
		{
			x = frame_clip_[X_KEY];
			y = frame_clip_[Y_KEY];
			w = frame_clip_[WIDTH_KEY];
			h = frame_clip_[HEIGHT_KEY];
			rect = {x, y, w, h};
			frames_clips_[index].push_back(rect);
		}
		index++;
	}

	file.close();

	return true;
}
bool Character::loadData(const std::string &path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Error opening file: " << path << std::endl;
	}
	nlohmann::json playerData;

	try
	{
		playerData = nlohmann::json::parse(file);
	}
	catch (nlohmann::json::parse_error &e)
	{

		std::cout << "Error parsing JSON: " << e.what() << std::endl;
		return false;
	}

	std::string spriteSheetDataPath = playerData[PLAYER_SPRITESHEET_DATA_PATH_KEY];
	if (!loadSpriteSheetData(spriteSheetDataPath))
	{
		std::cout << "Error loading sprite sheet data" << std::endl;
		return false;
	}

	width_ = playerData[SIZE_KEY][WIDTH_KEY];
	height_ = playerData[SIZE_KEY][HEIGHT_KEY];
	width_offset_ = (rect_.w - width_) / 2;
	height_offset_ = (rect_.h - height_);

	try
	{
		/* code */
		std::string jumpSoundPath = playerData[JUMP_SOUND_KEY];
		std::string landSoundPath = playerData[LAND_SOUND_KEY];
		std::string walkSoundPath = playerData[WALK_SOUND_KEY];
		jump_sound_ = Mix_LoadWAV(jumpSoundPath.c_str());
		land_sound_ = Mix_LoadWAV(landSoundPath.c_str());
		walk_sound_ = Mix_LoadMUS(walkSoundPath.c_str());
		
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		std::cerr << SDL_GetError() << '\n';
	}

	file.close();
	return true;
}
