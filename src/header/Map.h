#ifndef MAP_H_
#define MAP_H_

#include "BaseObject.h"


class Tile : public BaseObject {
public:


	Tile(char type);
	~Tile();
	char getType() const;
	bool loadTexture(SDL_Renderer* ren, std::string path);
	bool isLoadedTexture()const;
private:
	bool is_loaded_texture_;
	char type_;
};
class GameMap {

public:

	GameMap();
	~GameMap();
	void setPath(const std::string& path);
	std::string getPath();

	bool loadMap();
	void moveMap(SDL_Rect rect, int vel);

	void renderMap(SDL_Renderer* ren);
private:

	int start_tiles_x_;
	int start_tiles_y_;

	int end_tiles_x_;
	int end_tiles_y_;
	int max_x;
	int max_y;
	int map_pos_;
	std::string path_;
	std::vector<std::vector<Tile*>> tiles_;
};

#endif