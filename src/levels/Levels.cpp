#include "Levels.h"

/**
 * @brief Default constructor for the Level class.
 */
Level::Level() {
	path_ = LEVEL_PATH[Level1];
	row_ = 0;
	col_ = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		for (int j = 0; j < MAX_TILES; j++) {
			tiles_[i][j] = new Tile(Tile::Type::EMPTY);
		}
	}
	id_ = Level1;
	sprite_tiles_ = NULL;
}

/**
 * @brief Destructor for the Level class.
 */
Level::~Level() {

}

/**
 * @brief Sets the path of the level file.
 * @param path The path of the level file.
 * @return True if the file is successfully loaded, false otherwise.
 */
bool Level::setPath(const std::string& path) {
	path_ = path;
	return loadFromFile();
}

/**
 * @brief Loads the level data from the file.
 * @return True if the file is successfully loaded, false otherwise.
 */
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
				tiles_[r][c]->setType(static_cast<Tile::Type>(ch - '0'));
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

/**
 * @brief Gets the path of the level file.
 * @return The path of the level file.
 */
std::string Level::getPath() {
	return path_;
}

/**
 * @brief Loads the sprite tiles from the given file path.
 * @param ren The SDL renderer.
 * @param path The path of the sprite tiles file.
 * @return True if the sprite tiles are successfully loaded, false otherwise.
 */
bool Level::loadSpriteTiles(SDL_Renderer* ren) {
	sprite_tiles_ = IMG_LoadTexture(ren, "assets/level/0.png");
	if (sprite_tiles_ == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	return sprite_tiles_ == NULL;
}

/**
 * @brief Gets the tile at the specified position.
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @return A pointer to the tile at the specified position.
 */
Tile* Level::getTile(const int& x, const int& y)
{
	return tiles_[y][x];
}

/**
 * @brief Gets the width of the level in tiles.
 * @return The width of the level in tiles.
 */
int Level::getWidth() const { return col_; }

/**
 * @brief Gets the height of the level in tiles.
 * @return The height of the level in tiles.
 */
int Level::getHeight() const { return row_; }

/**
 * @brief Renders the level on the screen.
 * @param ren - SDL renderer.
 * @param cam - camera object.
 */
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
			if (tiles_[mapY][mapX]->getType() == Tile::Type::EMPTY) {
				SDL_RenderCopy(ren, sprite_tiles_, &EMPTY_TILE_CLIP, &des);
			}
			else if (tiles_[mapY][mapX]->getType() == Tile::Type::GROUND) {
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
				path_ = levelPath->GetText();
				loadFromFile();
			}
		}
	}
	else {
		setPath(LEVEL_PATH[Level1]);
		id_ = Level1;
		savePath();
		std::cout << "Failed to load level." << std::endl;
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
	if (doc.SaveFile("save/save_game.xml") == tinyxml2::XML_SUCCESS) {
		std::cout << "Game saved successfully!" << std::endl;
	}
	else {
		std::cout << "Failed to save game." << std::endl;
	}
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
	savePath();
	setPath(LEVEL_PATH[id_]);
}