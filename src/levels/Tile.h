#ifndef TILE_H_
#define TILE_H_
#include "../core/Constants.h"
class Tile {
public:
	enum Type {
		EMPTY = 0,
		GROUND = 1,
	};
	Tile();
	Tile(Type type);
	Type getType() const;
	void setType(Type type);
private:
	Type type_;
	//clip_ to specify pos of sprite where will take to render
	SDL_Rect clip_;
};
#endif // !TILE_H_
