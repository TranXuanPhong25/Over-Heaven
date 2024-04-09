#ifndef LEVEL_H_
#define LEVEL_H_

#include "Tile.h"
#include "Camera.h"
#include "../comp/Vector2D.h"
#include "../thirdParty/tinyxml2_10.0.0/tinyxml2.h"

class Level {
public:
	enum LevelIndex {
		NONE,
		Level1,
		Level2,
		Level3
	};
	LevelIndex id_;
	Level();
	~Level();
	bool setPath(const std::string& path);
	std::string getPath();
	void render(SDL_Renderer* ren, Camera& cam);
	void loadSavedPath();
	void savePath();
	void toNextLevel();
	bool loadSpriteTiles(SDL_Renderer* ren);
	Tile* getTile(const int& x, const int& y);
	int getWidth()const;
	int getHeight()const;
private:
	bool loadFromFile();
	int row_;
	int col_;
	std::string path_;
	Tile* tiles_[MAX_TILES][MAX_TILES];
	SDL_Texture* sprite_tiles_;
};

#endif