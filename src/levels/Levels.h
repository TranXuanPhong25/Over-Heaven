#ifndef LEVEL_H_
#define LEVEL_H_

#include "Camera.h"
#include "../comp/Vector2D.h"
#include "../thirdParty/tinyxml2_10.0.0/tinyxml2.h"
#include "../states/LoadingState.h"
#include "../states/CreditState.h"
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

	std::string getPath() const;

	void loadResources(SDL_Renderer* ren, std::atomic<float>* progress);
	void loadSavedPath();
	bool loadTiles();

	void savePath();

	void update(Camera& cam);

	void toNextLevel();
	void processCSVLine(const std::string& line, int& r, int& c);

	Tile getTile(const int& x, const int& y) const;
	LevelIndex getLevelIndex() const;

	int getWidth()const;
	int getHeight()const;

	int getTileWidth()const;
	int getTileHeight()const;
	void renderFarGround(SDL_Renderer* ren);
	void renderBackground(SDL_Renderer* ren);
	void renderForeGround(SDL_Renderer* ren);
	void renderFaceGround(SDL_Renderer* ren);
	void renderNearGround(SDL_Renderer* ren);
private:

	int far_ground_width_;
	int far_ground_height_;
	int fore_ground_width_;
	int fore_ground_height_;
	int face_ground_width_;
	int face_ground_height_;
	int background_width_;
	int background_height_;
	int near_ground_width_;
	int near_ground_height_;

	SDL_Rect far_ground_clip_;
	SDL_Rect background_clip_;
	SDL_Rect fore_ground_clip_;
	SDL_Rect face_ground_clip_;
	SDL_Rect near_ground_clip_;

	SDL_Texture* back_ground_;
	SDL_Texture* far_ground_;
	SDL_Texture* fore_ground_;
	SDL_Texture* near_ground_;
	SDL_Texture* face_ground_;


	int row_;
	int col_;

	int width_;
	int height_;

	std::string path_;
	Tile tiles_[MAX_TILES][MAX_TILES];
};

#endif