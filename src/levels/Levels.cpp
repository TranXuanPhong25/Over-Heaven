#include "Levels.h"

Level::Level() {
	path_ = LEVEL_PATH[Level1];
	row_ = 0;
	col_ = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		for (int j = 0; j < MAX_TILES; j++) {
			tiles_[i][j] = EMPTY;
		}
	}
	id_ = Level1;
	sprite_tiles_ = NULL;
	back_ground_ = NULL;
	far_ground_ = NULL;
	fore_ground_ = NULL;
	background_clip_.x = 0;
	background_clip_.y = 0;
	background_clip_.w = SCREEN_WIDTH;
	background_clip_.h = SCREEN_HEIGHT;
}

Level::~Level() {
	if (sprite_tiles_ != NULL) {
		SDL_DestroyTexture(sprite_tiles_);
		sprite_tiles_ = NULL;
	}
	if (back_ground_ != NULL) {
		SDL_DestroyTexture(back_ground_);
		back_ground_ = NULL;
	}
	if (far_ground_ != NULL) {
		SDL_DestroyTexture(far_ground_);
		far_ground_ = NULL;
	}
	if (fore_ground_ != NULL) {
		SDL_DestroyTexture(fore_ground_);
		fore_ground_ = NULL;
	}
}

bool Level::setPath(const std::string& path) {
	path_ = path;
	return loadFromFile();
}

bool Level::loadFromFile() {
	std::ifstream file(path_);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file " << path_ << std::endl;
		return false;
	}
	int r = 0;
	int c = 0;
	std::string line;
	while (std::getline(file, line)) {
		for (char ch : line)
		{
			if (ch != ',') {
				tiles_[r][c] = static_cast<Tile>(ch - '0');
				c++;
			}
		}
		col_ = c;
		c = 0;
		r++;
	}
	row_ = r;
	file.close();
	return true;
}

std::string Level::getPath() {
	return path_;
}

bool Level::loadSpriteTiles(SDL_Renderer* ren) {
	sprite_tiles_ = IMG_LoadTexture(ren, "assets/level/0.png");
	if (sprite_tiles_ == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	return sprite_tiles_ == NULL;
}

Level::Tile Level::getTile(const int& x, const int& y)
{
	return tiles_[y][x];
}

int Level::getWidth() const { return col_; }


int Level::getHeight() const { return row_; }

void Level::loadResources(SDL_Renderer* ren)
{
	back_ground_ = IMG_LoadTexture(ren, "assets/level/bg1.png");
	far_ground_ = IMG_LoadTexture(ren, "assets/level/farground.png");
	far_ground_clip_.x = 0;
	far_ground_clip_.y = 0;
	far_ground_clip_.w = 1920;
	far_ground_clip_.h = 1080;
	fore_ground_ = IMG_LoadTexture(ren, "assets/level/foreground.png");
}
void Level::update(Camera& cam) {
	background_clip_.x = cam.getPos().x;
	background_clip_.y = cam.getPos().y;
	far_ground_clip_.x = cam.getPos().x / 5760 * 1642;
}

void Level::renderFarGround(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, far_ground_, &far_ground_clip_, NULL);
}

void Level::renderForeGround(SDL_Renderer* ren)
{

	SDL_RenderCopy(ren, fore_ground_, &background_clip_, NULL);
}

void Level::renderBackground(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, back_ground_, &background_clip_, NULL);
}

void Level::render(SDL_Renderer* ren, Camera& cam) {
	SDL_Rect viewport = cam.getViewport();

	int x, y, mapX, x1, x2, mapY, y1, y2;

	mapX = viewport.x;
	x1 = (int(cam.getPos().x) % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	mapY = viewport.y;
	y1 = (int(cam.getPos().y) % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (y = y1; y <= y2; y += TILE_SIZE)
	{

		mapX = viewport.x;
		for (x = x1; x <= x2; x += TILE_SIZE)
		{
			SDL_Rect des = { x ,y ,TILE_SIZE,TILE_SIZE };
			if (tiles_[mapY][mapX] == EMPTY) {
				SDL_RenderCopy(ren, sprite_tiles_, &EMPTY_TILE_CLIP, &des);
			}
			else if (tiles_[mapY][mapX] == GROUND) {
				SDL_RenderCopy(ren, sprite_tiles_, &GROUND_TILE_CLIP, &des);
			}

			mapX++;
		}

		mapY++;
	}
}

void Level::loadSavedPath()
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("save/save_game.xml") == tinyxml2::XML_SUCCESS) {
		tinyxml2::XMLElement* root = doc.RootElement();
		if (root) {
			tinyxml2::XMLElement* levelPath = root->FirstChildElement("LevelPath");
			if (levelPath) {
				int id;
				levelPath->QueryIntAttribute("id", &id);
				id_ = static_cast<LevelIndex>(id);
				setPath(levelPath->GetText());
			}
		}
	}
	else {
		id_ = Level1;
		setPath(LEVEL_PATH[Level1]);
		savePath();
	}
}

void Level::savePath() {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;
	if (doc.LoadFile("save/save_game.xml") == tinyxml2::XML_SUCCESS) {
		root = doc.RootElement();
	}
	else {
		root = doc.NewElement("SaveData");
		doc.InsertFirstChild(root);
	}
	if (root) {
		tinyxml2::XMLElement* levelPath = doc.NewElement("LevelPath");
		levelPath->SetAttribute("id", static_cast<int>(id_));
		levelPath->SetText(path_.c_str());
		root->InsertEndChild(levelPath);
	}
	doc.SaveFile("save/save_game.xml");
}

void Level::toNextLevel() {
	if (id_ == Level1) {
		id_ = Level2;
	}
	else if (id_ == Level2) {
		id_ = Level3;
	}
	else {
		return;
	}
	setPath(LEVEL_PATH[id_]);
	savePath();
}