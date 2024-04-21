#ifndef LEVEL_H_
#define LEVEL_H_

//#include "Tile.h"
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
	enum Tile {
		EMPTY = 0,
		GROUND = 1,
		GOAL = 2

	};
	LevelIndex id_;
	Level();
	~Level();
	bool setPath(const std::string& path);
	std::string getPath();
	void render(SDL_Renderer* ren, Camera& cam);
	void loadSavedPath();
	void savePath();
	void update(Camera& cam);
	void toNextLevel();
	bool loadSpriteTiles(SDL_Renderer* ren);
	Tile getTile(const int& x, const int& y);
	int getWidth()const;
	int getHeight()const;
	void loadResources(SDL_Renderer* ren);

	void renderFarGround(SDL_Renderer* ren);
	void renderForeGround(SDL_Renderer* ren);
	void renderBackground(SDL_Renderer* ren);
private:

	bool loadFromFile();
	SDL_Rect far_ground_clip_;
	SDL_Rect background_clip_;
	SDL_Texture* back_ground_;
	SDL_Texture* far_ground_;
	SDL_Texture* fore_ground_;
	int row_;
	int col_;
	std::string path_;
	Tile tiles_[MAX_TILES][MAX_TILES];
	SDL_Texture* sprite_tiles_;
	Vector2D default_pos_;
};

#endif