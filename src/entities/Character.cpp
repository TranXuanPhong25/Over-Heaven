#include "Character.h"
Character::Character() {
	speed_ = 540;
	vel_ = { 0,0 };
	state_ = IDLE;
	spacekey_pressed_ = false;
	/*accelerator_ = 0;*/
	on_ground_ = false;
	dir_left_ = 0;
	dir_right_ = 0;
	double_jump_ = true;
}
Character::~Character() {
	free();
}

void Character::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = true;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {

			dir_left_ = 1;
			/*if (accelerator_ <= 0) {
				state_ = MOVE_LEFT;
			}*/
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 1;
			/*if (accelerator_ >= 0) {

				state_ = MOVE_RIGHT;
			}*/
		}
	}
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = false;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {
			dir_left_ = 0;
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 0;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN) {

	}
	if (e.type == SDL_MOUSEBUTTONUP) {

	}


}

bool Character::shoudSlowDown() const {
	//return (state_ == MOVE_LEFT && accelerator_ < 0 && vel_.x == 0)
	//	|| (state_ == MOVE_RIGHT && accelerator_ > 0 && vel_.x == 0);
	return true;
}
Vector2D Character::getVel() const {
	return vel_;
}
//void Character::update(Level& level, const float& dT) {
//	/*if (shoudSlowDown()) {
//		if (state_ == MOVE_RIGHT) {
//			accelerator_ -= RIGHT * speed_ / RUN_SPEED;
//		}
//		else {
//			accelerator_ -= LEFT * speed_ / RUN_SPEED;
//		}
//	}
//	else if (vel_.x != 0) {
//		accelerator_ += vel_.x * speed_ / RUN_SPEED;
//	}
//	else {
//		accelerator_ = 0;
//	}
//	if (accelerator_ >= MAX_RUN_SPEED) {
//		accelerator_ = MAX_RUN_SPEED;
//	}
//	if (accelerator_ <= -MAX_RUN_SPEED) {
//		accelerator_ = -MAX_RUN_SPEED;
//	}*/
//
//	/*pos_.x += static_cast<int>(round(accelerator_ * dT));*/
//
//	//jump
//	pos_.x += vel_.x * 5;
//	updateRect();
//	handleLevelInteraction(level);
//	if (spacekey_pressed_) {
//		if (on_ground_) {
//			on_ground_ = false;
//			vel_.y -= static_cast<int>(speed_ * 2.8);
//		}
//	}
//	//gravity
//	if (!on_ground_) {
//		if (vel_.y > 0) {
//			vel_.y -= static_cast<int>(GRAVITY * 0.7 * dT);
//		}
//		vel_.y += static_cast<int>(GRAVITY * dT);
//
//		pos_.y += int(round(vel_.y * dT));
//		//vel_.y *= dT;
//	}
//	else {
//		vel_.y = 0;
//	}
//	updateRect();
//	handleLevelInteraction(level);
//
//	//pos_.y += vel_.y;
//
//	//Character wrapper screen
//	//if (pos_.y + rect_.w > SCREEN_WIDTH) {
//	//	pos_.y = SCREEN_WIDTH - rect_.w;
//	//}
//	//if (pos_.y >= SCREEN_HEIGHT - rect_.h) {
//	//	pos_.y = SCREEN_HEIGHT - rect_.h;
//	//	vel_.y = 0;
//	//	on_ground_ = true;
//	//}
//	//if (pos_.y < 0) {
//	//	pos_.y = 0;
//	//}
//	//if (pos_.y < 0) {
//	//	pos_.y = 0;
//	//}
//}
bool Character::checkCollision(const SDL_Rect& a, const SDL_Rect& s) {
	return  a.x < s.x + s.w &&
		a.x + a.w > s.x &&
		a.y < s.y + s.h &&
		a.y + a.h > s.y;
}

//void Character::handleLevelInteraction(Level& level) {
//	bool isCollided = false;
//	int tileX = (int)pos_.x / TILE_SIZE;
//	int tileY = (int)pos_.y / TILE_SIZE;
//	int levelWidth = level.getWidth();
//	int levelHeight = level.getHeight();
//	int minX = max(0, int(pos_.x) / TILE_SIZE - 1);
//	int maxX = min(levelWidth - 1, int(pos_.x + rect_.w) / TILE_SIZE + 1);
//	int minY = max(0, int(pos_.y) / TILE_SIZE - 1);
//	int maxY = min(levelHeight - 1, int(pos_.y + rect_.h) / TILE_SIZE + 1);
//	std::cout << on_ground_;
//	for (int x = minX; x <= maxX; x++) {
//		for (int y = minY; y <= maxY; y++)
//		{
//			SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
//			if (checkCollision(rect_, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {
//
//				if (vel_.y >= 0) {
//					if (y != tileY) {
//						//move down
//						//std::cout << vel_.y;
//						std::cout << "vailon";
//						on_ground_ = true;
//						//pos_.y -= vel_.y;
//						vel_.y = 0;
//						pos_.y = tileRect.y - rect_.h;;
//						rect_.y = pos_.y;
//					}
//					else {
//						std::cout << "lam gi di\n";
//
//					}
//				}
//				if (vel_.y < 0 && y == tileY) {
//					//jump
//					vel_.y = 0;
//					pos_.y = tileRect.y + tileRect.h;
//					rect_.y = pos_.y;
//
//				}
//
//				//if () {
//				//	if (vel_.y >= 0) {
//				//		vel_.y = 0;
//				//		on_ground_ = true;
//				//		pos_.y = tileRect.y - rect_.h;;
//				//		rect_.y = pos_.y;
//				//	}
//				//	else {
//				//		vel_.y = 0;
//				//		pos_.y = tileRect.y + tileRect.h;
//				//		rect_.y = pos_.y;
//
//				//	}
//				//}
//
//				isCollided = true;
//
//			}
//			if (checkCollision(rect_, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {
//
//				/*if (tileY == y) {*/
//
//				if (vel_.x > 0) {
//					//move right
//					pos_.x = tileRect.x - rect_.w;
//
//					rect_.x = pos_.x;
//				}
//				if (vel_.x < 0) {
//					std::cout << "x ";
//					//move left
//						//pos_.y = tileRect.x - rect_.w;
//					pos_.x = tileRect.x + tileRect.w;
//					rect_.x = pos_.x;
//				}
//
//
//				//}
//				isCollided = true;
//
//
//			}
//		}
//	}
//
	/*if (tileY < levelHeight && ((level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY && level.getTile(tileX + 1, tileY + 1)->getType() == Tile::EMPTY) || pos_.x == tileX * TILE_SIZE && (level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY))) {
		on_ground_ = false;
	}*/
	//
	//
	//
	//
	//}
void Character::update(Level& level, const float& dT) {
	moveAndCollideX(dT, level);
	moveAndCollideY(0.01667f, level);
}
void Character::moveAndCollideX(const float dT, Level& level) {
	int tileX = rect_.x / TILE_SIZE;
	int tileY = rect_.y / TILE_SIZE;
	vel_.x = (dir_right_ - dir_left_);
	rect_.x += vel_.x * 5 * dT;
	if (rect_.x <= 0) rect_.x = 0;
	//if (tileY < 0 || tileY >= level.getWidth() || tileX < 0) return;
	//Tile* curTile = level.getTile(tileX, tileY);
	//SDL_Rect curTileRect = { (tileX)*TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE };;
	//Tile* nextTile = level.getTile(tileX + vel_.x, tileY);
	//SDL_Rect tileRect = { (tileX + vel_.x) * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	//if (nextTile->getType() != Tile::EMPTY && checkCollision(tileRect, rect_)) {
	//	if (vel_.x == RIGHT) {
	//		rect_.x = tileRect.x - rect_.w;
	//	}
	//	if (vel_.x == LEFT) {
	//		rect_.x = tileRect.x + tileRect.w;
	//	}
	//}
	//if (curTile->getType() != Tile::EMPTY && checkCollision(curTileRect, rect_)) {
	//	if (vel_.x == RIGHT) {
	//		rect_.x = curTileRect.x - rect_.w;
	//	}
	//	if (vel_.x == LEFT) {
	//		rect_.x = curTileRect.x + curTileRect.w;
	//	}
	//}
	for (int x = tileX - 1; x <= tileX + 1; x++) {
		for (int y = tileY - 2; y <= tileY + 2; y++)
		{
			SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			if (checkCollision(rect_, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {

				if (vel_.x == RIGHT) {
					rect_.x = tileRect.x - rect_.w;
				}
				if (vel_.x == LEFT) {
					rect_.x = tileRect.x + tileRect.w;
				}


			}

		}
	}
}
void Character::moveAndCollideY(const float& dT, Level& level)
{
	if (spacekey_pressed_) {
		if (on_ground_) {
			on_ground_ = false;
			vel_.y -= static_cast<int>(speed_ * 2.8);
		}
		else if (double_jump_) {
			double_jump_ = false;
			vel_.y -= static_cast<int>(speed_ * 2.8);
		}
	}
	//gravity
	if (!on_ground_) {
		if (vel_.y < 0) {
			vel_.y += static_cast<int>(GRAVITY * 0.4 * dT);
		}
		vel_.y += static_cast<int>(GRAVITY * 0.8 * dT);

		rect_.y += int(round(vel_.y * dT));
	}
	int tileX = rect_.x / TILE_SIZE;
	int tileY = rect_.y / TILE_SIZE;
	for (int x = tileX - 1; x <= tileX + 1; x++) {
		for (int y = tileY - 2; y <= tileY + 2; y++)
		{
			SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			if (checkCollision(rect_, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {

				if (vel_.y >= 0) {
					//move down

					if (tileY < level.getHeight() && ((level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY && level.getTile(tileX + 1, tileY + 1)->getType() == Tile::EMPTY) || pos_.x == tileX * TILE_SIZE && (level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY))) {
						on_ground_ = false;
						double_jump_ = true;
					}
					else {
						on_ground_ = true;
						double_jump_ = false;

					}
					//pos_.y -= vel_.y;
					vel_.y = 0;
					rect_.y = tileRect.y - rect_.h;;
				}
				else if (vel_.y < 0 && y == tileY) {
					//jump
					vel_.y = 0;
					rect_.y = tileRect.y + tileRect.h;


				}


			}

		}
	}
	if (tileY < level.getHeight() && ((level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY && level.getTile(tileX + 1, tileY + 1)->getType() == Tile::EMPTY) || (rect_.x == tileX * TILE_SIZE && (level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY)))) {
		on_ground_ = false;
	}
}
