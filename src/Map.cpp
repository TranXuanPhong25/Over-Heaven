#include "header/Map.h"

Tile::Tile(char type) {
	//type_ = static_cast<Tile::TileType> (type);
	type_ = type;
	is_loaded_texture_ = false;
}
Tile::~Tile() {
	free();
}
char Tile::getType() const {
	return type_;
}
bool Tile::loadTexture(SDL_Renderer* ren, std::string path) {
	is_loaded_texture_ = true;
	return BaseObject::loadTexture(ren, path);
}
bool Tile::isLoadedTexture() const {
	return is_loaded_texture_;
}
GameMap::GameMap() {
	path_ = "";

	end_tiles_y_ = min(SCREEN_HEIGHT / TILE_SIZE, 13);
	end_tiles_x_ = min(SCREEN_WIDTH / TILE_SIZE, 100);
	max_x = 1000;
	max_y = 1000;
	start_tiles_x_ = 0;
	start_tiles_y_ = 0;
	map_pos_ = 0;
}
GameMap::~GameMap() {
	path_ = "";
	tiles_.clear();
}
void GameMap::setPath(const std::string& path) {
	path_ = path;
}
std::string GameMap::getPath() {
	return path_;
}
bool GameMap::loadMap() {
	bool success = true;
	std::ifstream fMap(path_.c_str());
	if (fMap.fail()) {
		std::cout << "can't load map" << std::endl;
		success = false;
	}
	else {
		std::vector<Tile*> rowTile;
		char tileType;
		while (fMap >> std::noskipws >> tileType) {
			if (tileType == '\n') {
				tiles_.push_back(rowTile);
				rowTile.clear();
			}
			else if (tileType != ' ') {
				Tile* curTile = new Tile(tileType);
				//std::string tilePath = MAP_PATH + tileType + ".png";
				//curTile->loadTexture(tilePath);
				rowTile.push_back(curTile);
			}

		}
		tiles_.push_back(rowTile);
		max_x = static_cast<int>(tiles_[0].size());
		max_y = static_cast<int>(tiles_.size());

	}
	fMap.close();
	return success;
}
void GameMap::moveMap(SDL_Rect rect, int vel) {
	if (rect.x > SCREEN_WIDTH - rect.w - 100) {
		map_pos_ -= vel;
		start_tiles_x_ = abs(map_pos_ / TILE_SIZE);
		end_tiles_x_ = SCREEN_WIDTH / TILE_SIZE + start_tiles_x_;

	}

}
void GameMap::renderMap(SDL_Renderer* ren) {


	for (int i = start_tiles_y_; i < end_tiles_y_; i++)
	{
		for (int j = start_tiles_x_; j < end_tiles_x_; j++)
		{
			if (!tiles_[i][j]->isLoadedTexture()) {
				tiles_[i][j]->loadTexture(ren, MAP_PATH + tiles_[i][j]->getType() + ".png");
			}
			tiles_[i][j]->setRect((j - start_tiles_x_) * TILE_SIZE, i * TILE_SIZE);
			tiles_[i][j]->render(ren);
		}

	}
}