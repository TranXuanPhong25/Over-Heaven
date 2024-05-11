#include "Levels.h"

Level::Level()
{
	path_ = LEVEL_PATH[Level1];
	row_ = 0;
	col_ = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		for (int j = 0; j < MAX_TILES; j++)
		{
			tiles_[i][j] = EMPTY;
		}
	}
	id_ = Level1;
	back_ground_ = NULL;
	far_ground_ = NULL;
	fore_ground_ = NULL;
	face_ground_ = NULL;
	near_ground_ = NULL;

	width_ = 0;
	height_ = 0;

	background_width_ = 0;
	background_height_ = 0;
	far_ground_width_ = 0;
	far_ground_height_ = 0;
	fore_ground_width_ = 0;
	fore_ground_height_ = 0;
	face_ground_width_ = 0;
	face_ground_height_ = 0;
	near_ground_height_ = 0;
	near_ground_width_ = 0;

	background_clip_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	far_ground_clip_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	fore_ground_clip_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	face_ground_clip_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	near_ground_clip_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Level::~Level()
{
	if (back_ground_ != NULL)
	{
		SDL_DestroyTexture(back_ground_);
		back_ground_ = NULL;
	}
	if (far_ground_ != NULL)
	{
		SDL_DestroyTexture(far_ground_);
		far_ground_ = NULL;
	}
	if (fore_ground_ != NULL)
	{
		SDL_DestroyTexture(fore_ground_);
		fore_ground_ = NULL;
	}
	if (face_ground_ != NULL)
	{
		SDL_DestroyTexture(face_ground_);
		face_ground_ = NULL;
	}
	if (near_ground_ != NULL)
	{
		SDL_DestroyTexture(near_ground_);
		near_ground_ = NULL;
	}
}

void Level::setPath(const std::string &path)
{
	path_ = path;
}

void Level::processCSVLine(const std::string &line, int &r, int &c)
{
	for (const char &ch : line)
	{
		if (ch != ',')
		{
			tiles_[r][c] = static_cast<Tile>(ch - '0');
			c++;
		}
	}
}

bool Level::loadTiles()
{
	std::ifstream file(path_);
	if (!file.is_open())
	{
		std::cerr << "Error: Unable to open file " << path_ << std::endl;
		return false;
	}
	int r = 0;
	int c = 0;
	std::string line;
	while (std::getline(file, line))
	{
		processCSVLine(line, r, c);
		col_ = c;
		c = 0;
		r++;
	}
	row_ = r;
	width_ = col_ * TILE_SIZE - SCREEN_WIDTH;
	height_ = row_ * TILE_SIZE - SCREEN_HEIGHT;

	file.close();
	return true;
}

std::string Level::getPath() const
{
	return path_;
}

Level::LevelIndex Level::getLevelIndex() const
{
	return id_;
}

Level::Tile Level::getTile(const int &x, const int &y) const
{
	return tiles_[y][x];
}

int Level::getWidth() const
{
	return col_ * TILE_SIZE;
}

int Level::getHeight() const
{
	return row_ * TILE_SIZE;
}
int Level::getTileWidth() const
{
	return col_;
}
int Level::getTileHeight() const
{
	return row_;
}

void Level::loadResources(SDL_Renderer *ren, std::atomic<float> *progress)
{
	if (back_ground_ != NULL)
		SDL_DestroyTexture(back_ground_);
	back_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + BACKGROUND_PATH).c_str());
	if (back_ground_ == NULL)
	{
		std::cout << SDL_GetError();
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	if (far_ground_ != NULL)
		SDL_DestroyTexture(far_ground_);
	far_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FARGROUND_PATH).c_str());
	if (far_ground_ == NULL)
	{
		std::cout << SDL_GetError();
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	if (fore_ground_ != NULL)
		SDL_DestroyTexture(fore_ground_);
	fore_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FOREGROUND_PATH).c_str());
	if (fore_ground_ == NULL)
	{
		std::cout << SDL_GetError();
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	if (face_ground_ != NULL)
		SDL_DestroyTexture(face_ground_);
	face_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FACEGROUND_PATH).c_str());
	if (face_ground_ == NULL)
	{
		std::cout << SDL_GetError();
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	if (near_ground_ != NULL)
		SDL_DestroyTexture(near_ground_);
	near_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + NEARGROUND_PATH).c_str());
	if (near_ground_ == NULL)
	{
		std::cout << SDL_GetError();
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	// get the width and height of the textures
	SDL_QueryTexture(back_ground_, NULL, NULL, &background_width_, &background_height_);
	SDL_QueryTexture(far_ground_, NULL, NULL, &far_ground_width_, &far_ground_height_);
	SDL_QueryTexture(fore_ground_, NULL, NULL, &fore_ground_width_, &fore_ground_height_);
	SDL_QueryTexture(face_ground_, NULL, NULL, &face_ground_width_, &face_ground_height_);
	SDL_QueryTexture(near_ground_, NULL, NULL, &near_ground_width_, &near_ground_height_);
}
void Level::update(Camera &cam)
{
	// move relative to camera
	background_clip_.x = cam.getPos().x / width_ * (background_width_ - SCREEN_WIDTH);
	background_clip_.y = cam.getPos().y / height_ * (background_height_ - SCREEN_HEIGHT);
	fore_ground_clip_.x = cam.getPos().x / width_ * (fore_ground_width_ - SCREEN_WIDTH);
	fore_ground_clip_.y = cam.getPos().y / height_ * (fore_ground_height_ - SCREEN_HEIGHT);
	far_ground_clip_.x = cam.getPos().x / width_ * (far_ground_width_ - SCREEN_WIDTH);
	far_ground_clip_.y = cam.getPos().y / height_ * (far_ground_height_ - SCREEN_HEIGHT);
	face_ground_clip_.x = cam.getPos().x / width_ * (face_ground_width_ - SCREEN_WIDTH);
	face_ground_clip_.y = cam.getPos().y / height_ * (face_ground_height_ - SCREEN_HEIGHT);
	near_ground_clip_.x = cam.getPos().x / width_ * (near_ground_width_ - SCREEN_WIDTH);
	near_ground_clip_.y = cam.getPos().y / height_ * (near_ground_height_ - SCREEN_HEIGHT);
}

void Level::renderFarGround(SDL_Renderer *ren)
{
	if (far_ground_ != NULL)
		SDL_RenderCopy(ren, far_ground_, &far_ground_clip_, NULL);
}

void Level::renderBackground(SDL_Renderer *ren)
{
	if (back_ground_ != NULL)
		SDL_RenderCopy(ren, back_ground_, &background_clip_, NULL);
}
void Level::renderForeGround(SDL_Renderer *ren)
{
	if (fore_ground_ != NULL)
		SDL_RenderCopy(ren, fore_ground_, &fore_ground_clip_, NULL);
}

void Level::renderFaceGround(SDL_Renderer *ren)
{
	if (face_ground_ != NULL)
		SDL_RenderCopy(ren, face_ground_, &face_ground_clip_, NULL);
}

void Level::renderNearGround(SDL_Renderer *ren)
{
	if (near_ground_ != NULL)
		SDL_RenderCopy(ren, near_ground_, &near_ground_clip_, NULL);
}

// tilebased map render

// void Level::render(SDL_Renderer* ren, Camera& cam) {
// 	SDL_Rect viewport = cam.getViewport();

// 	int x, y, mapX, x1, x2, mapY, y1, y2;

// 	mapX = viewport.x;
// 	x1 = (int(cam.getPos().x) % TILE_SIZE) * -1;
// 	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

// 	mapY = viewport.y;
// 	y1 = (int(cam.getPos().y) % TILE_SIZE) * -1;
// 	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

// 	for (y = y1; y <= y2; y += TILE_SIZE)
// 	{

// 		mapX = viewport.x;
// 		for (x = x1; x <= x2; x += TILE_SIZE)
// 		{
// 			SDL_Rect des = { x ,y ,TILE_SIZE,TILE_SIZE };
// 			if (tiles_[mapY][mapX] == EMPTY) {
// 				SDL_RenderCopy(ren, sprite_tiles_, &EMPTY_TILE_CLIP, &des);
// 			}
// 			else if (tiles_[mapY][mapX] == GROUND) {
// 				SDL_RenderCopy(ren, sprite_tiles_, &GROUND_TILE_CLIP, &des);
// 			}

// 			mapX++;
// 		}

// 		mapY++;
// 	}
// }

void Level::loadSavedPath()
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(SAVE_PATH) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLElement *root = doc.RootElement();
		if (!root)
		{
			return;
		}
		tinyxml2::XMLElement *levelPath = root->FirstChildElement("LevelPath");
		if (!levelPath)
		{
			id_ = Level1;
			setPath(LEVEL_PATH[Level1] + MAP_NAME[Level1]);
		}
		else
		{
			int id = 1;
			levelPath->QueryIntAttribute("id", &id);
			id_ = static_cast<LevelIndex>(id);
			setPath(LEVEL_PATH[id_] + MAP_NAME[id_]);
		}
	}
	else
	{
		id_ = Level1;
		setPath(LEVEL_PATH[Level1] + MAP_NAME[Level1]);
		savePath();
	}
}

void Level::savePath()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *root;
	if (doc.LoadFile(SAVE_PATH) == tinyxml2::XML_SUCCESS)
	{
		root = doc.RootElement();
	}
	else
	{
		root = doc.NewElement("SaveData");
		doc.InsertFirstChild(root);
	}
	if (root)
	{
		tinyxml2::XMLElement *levelPath = doc.NewElement("LevelPath");
		levelPath->SetAttribute("id", static_cast<int>(id_));
		levelPath->SetText(path_.c_str());
		root->InsertEndChild(levelPath);
	}
	try {
		std::filesystem::create_directories("save");
	}catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	doc.SaveFile(SAVE_PATH);
}

void Level::toNextLevel()
{
	if (id_ == Level3)
	{
		StateMachine::get()->setNextState(CreditState::get());
		return;
	}
	id_ = static_cast<LevelIndex>(id_ + 1);
	setPath(LEVEL_PATH[id_] + MAP_NAME[id_]);
	savePath();
	StateMachine::get()->setNextState(LoadingState::get());
}
