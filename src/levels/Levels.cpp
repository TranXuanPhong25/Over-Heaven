#include "Levels.h"
Level::Level() {
	path_ = "";
	row_ = 0;
	col_ = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		for (int j = 0; j < MAX_TILES; j++) {
			tiles_[i][j] = new Tile(Tile::Type::EMPTY);
		}
	}
	sprite_tiles_ = NULL;
}
Level::~Level() {

}
bool Level::setPath(const std::string& path) {
	path_ = path;
	return loadFromFile();
}
std::string Level::getPath() {
	return path_;
}
bool Level::loadSpriteTiles(SDL_Renderer* ren, const std::string& path) {
	sprite_tiles_ = IMG_LoadTexture(ren, path.c_str());
	if (sprite_tiles_ == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	return sprite_tiles_ == NULL;
}
Tile* Level::getTile(const int& x, const int& y)
{
	return tiles_[y][x];
}
int Level::getWidth() const { return col_; }
int Level::getHeight() const { return row_; }
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
void Level::render(SDL_Renderer* ren, Camera* cam) {
	int x = 0;
	int y = 0;
	SDL_Rect viewport = cam->getViewport();
	for (int i = viewport.y; i <= viewport.y + viewport.h; i++)
	{
		for (int j = viewport.x; j <= viewport.x + viewport.w; j++)
		{
			SDL_Rect des = { x * TILE_SIZE,y * TILE_SIZE ,TILE_SIZE,TILE_SIZE };
			if (tiles_[i][j]->getType() == Tile::Type::EMPTY) {
				SDL_RenderCopy(ren, sprite_tiles_, &EMPTY_TILE_CLIP, &des);
			}
			else if (tiles_[i][j]->getType() == Tile::Type::GROUND) {
				SDL_RenderCopy(ren, sprite_tiles_, &GROUND_TILE_CLIP, &des);
			}
			x++;
		}
		y++;
		x = 0;

	}
}