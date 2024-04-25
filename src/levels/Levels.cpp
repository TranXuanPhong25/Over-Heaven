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
	back_ground_ = NULL;
	far_ground_ = NULL;
	fore_ground_ = NULL;
	face_ground_ = NULL;

	background_clip_={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	far_ground_clip_={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	SDL_QueryTexture(back_ground_, NULL, NULL, &background_width_,&background_height_ );
	SDL_QueryTexture(far_ground_, NULL, NULL, &far_ground_width_,&far_ground_height_ );
	SDL_QueryTexture(fore_ground_, NULL, NULL, &fore_ground_width_,&fore_ground_height_ );
	SDL_QueryTexture(face_ground_, NULL, NULL, &face_ground_width_,&face_ground_height_ );

}

Level::~Level() {
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
	if (face_ground_ != NULL) {
		SDL_DestroyTexture(face_ground_);
		face_ground_ = NULL;
	}
}

void Level::setPath(const std::string& path) {
	path_ = path;
}

void Level::handleLineCSV(const std::string &line, int &r, int &c)
{
    for (char ch : line)
		{
			if (ch != ',') {
				tiles_[r][c] = static_cast<Tile>(ch - '0');
				c++;
			}
		}
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
		handleLineCSV(line, r, c);
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

Level::LevelIndex Level::getLevelIndex()
{
	return id_;
}

Level::Tile Level::getTile(const int& x, const int& y)
{
	return tiles_[y][x];
}

int Level::getWidth() const { return col_; }


int Level::getHeight() const { return row_; }

void Level::loadResources(SDL_Renderer* ren)
{
	back_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + BACKGROUND_PATH).c_str());

	if (back_ground_ == NULL) {
		std::cout << SDL_GetError();
	}

	far_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FARGROUND_PATH).c_str());
	if (far_ground_ == NULL) {
		std::cout << SDL_GetError();
	}

	fore_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FOREGROUND_PATH).c_str());
	if (fore_ground_ == NULL) {
		std::cout << SDL_GetError();
	}

	face_ground_ = IMG_LoadTexture(ren, (LEVEL_PATH[id_] + FACEGROUND_PATH).c_str());
	if (face_ground_ == NULL) {
		std::cout << SDL_GetError();
	}
}
void Level::update(Camera& cam) {
	background_clip_.x = cam.getPos().x;
	background_clip_.y = cam.getPos().y;
	far_ground_clip_.x = cam.getPos().x / background_width_ * (far_ground_width_ - SCREEN_WIDTH);
	far_ground_clip_.y = cam.getPos().y / background_height_ * (far_ground_height_ - SCREEN_HEIGHT);
}

void Level::renderFarGround(SDL_Renderer* ren)
{
	if (far_ground_ != NULL) SDL_RenderCopy(ren, far_ground_, &far_ground_clip_, NULL);
}

void Level::renderForeGround(SDL_Renderer* ren)
{
	if (fore_ground_ != NULL) SDL_RenderCopy(ren, fore_ground_, &background_clip_, NULL);
}

void Level::renderFaceGround(SDL_Renderer* ren)
{
	if (face_ground_ != NULL) SDL_RenderCopy(ren, face_ground_, &background_clip_, NULL);
}

void Level::renderBackground(SDL_Renderer* ren)
{
	if (back_ground_ != NULL) SDL_RenderCopy (ren, back_ground_, &background_clip_, NULL);
}


//tilebase map render 

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
	if (doc.LoadFile("save/save_game.xml") == tinyxml2::XML_SUCCESS) {
		tinyxml2::XMLElement* root = doc.RootElement();
		if (root) {
			tinyxml2::XMLElement* levelPath = root->FirstChildElement("LevelPath");
			if (levelPath) {
				int id = 1;
				levelPath->QueryIntAttribute("id", &id);
				id_ = static_cast<LevelIndex>(id);
				setPath(levelPath->GetText());
			}
		}
	}
	else {

		id_ = Level1;
		setPath(LEVEL_PATH[Level1] + MAP_NAME[Level1]);
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
	if (id_ == Level3) {
		// StateMachine::changeState(CreditState::get());
		return;
	}
	if (id_ == Level1) {
		id_ = Level2;
	}
	else if (id_ == Level2) {
		id_ = Level3;
	}
	setPath(LEVEL_PATH[id_] + MAP_NAME[id_]);
	savePath();
	StateMachine::get()->setNextState(LoadingScreenState::get());
}
