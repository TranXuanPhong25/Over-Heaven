#include "Tile.h"
Tile::Tile() {
	type_ = Type::EMPTY;
	clip_ = { 0,0,0,0 };
}
Tile::Tile(Type type) {
	type_ = type;
	clip_ = { 0,0,0,0 };
}
Tile::Type Tile::getType() const {
	return type_;
}
void Tile::setType(Type type) {
	type_ = type;
}
