#ifndef LEVEL_H_
#define LEVEL_H_

#include "Camera.h"
#include "../comp/Vector2D.h"
#include "../thirdParty/tinyxml2_10.0.0/tinyxml2.h"
#include "../states/LoadingScreenState.h"

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
	void setPath(const std::string& path);

	std::string getPath();
	void loadResources(SDL_Renderer* ren);
	void loadSavedPath();
	bool loadFromFile();

	void savePath();

	void update(Camera& cam);

	void toNextLevel();
	void handleLineCSV(const std::string& line, int& r, int& c);
	Tile getTile(const int& x, const int& y);
	LevelIndex getLevelIndex();

	int getWidth()const;
	int getHeight()const;

	void renderFarGround(SDL_Renderer* ren);
	void renderForeGround(SDL_Renderer* ren);
	void renderFaceGround(SDL_Renderer* ren);
	void renderBackground(SDL_Renderer* ren);
private:

	int far_ground_width_;
	int far_ground_height_;
	int fore_ground_width_;
	int fore_ground_height_;
	int face_ground_width_;
	int face_ground_height_;
	int background_width_;
	int background_height_;
	
	SDL_Rect far_ground_clip_;
	SDL_Rect background_clip_;

	SDL_Texture* back_ground_;
	SDL_Texture* far_ground_;
	SDL_Texture* fore_ground_;
	SDL_Texture* face_ground_;

	int row_;
	int col_;

	std::string path_;
	Tile tiles_[MAX_TILES][MAX_TILES];
};

#endif