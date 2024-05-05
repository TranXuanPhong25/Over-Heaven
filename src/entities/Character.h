#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Entity.h"
#include "../levels/Levels.h"

class Character : public Entity {
public:
	enum State {
		IDLE_LEFT,
		IDLE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP_LEFT,
		JUMP_RIGHT,
		FALL_LEFT,
		FALL_RIGHT,
		/*DASH_LEFT,
		DASH_RIGHT,*/
		SLIDE_LEFT,
		SLIDE_RIGHT,

	};
	Character();
	~Character();
	void handleInput(SDL_Event& e);
	void handleKeyPressed(const SDL_Event& e);
	void handleKeyReleased(const SDL_Event& e);

	Vector2D getVel()const;
	void update(Level& level, Camera& cam, const float& dT);

	void moveX(const float& dT);
	void moveY(const float& dT);
	void CollideX(Level& level);
	void CollideY(Level& level);
	void GroundCollideX(const SDL_Rect& tileRect);
	void GroundCollideY(const SDL_Rect& tileRect);
	void handleCollideX(const int& x, const int& y, Level::Tile tile);
	void handleCollideY(const int& x, const int& y, const int& endY, Level::Tile tile, bool& somethingBelow);
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& s);
	void setDefaultPosition(Level& level);
	void applyGravity(const float& dT);
	//void dash(const float& dT);
	void jump(const float& dT);
	bool isReachedGoal() const;
	void handleReachGoal();
	void saveStats() const;
	void loadStats(Level& level);
	void resetStats();
private:
	State state_;
	float speed_;
	int dir_left_;
	int dir_right_;
	Vector2D vel_;
	float gravity_scalar_;
	bool on_ground_;
	bool spacekey_pressed_;
	int jump_count_;

	/*bool dashing_;
	int dash_counter_;
	int dash_dir_;
	int dashing_frame_;
	float dash_cooldown_;*/
	int required_frame_to_apply_jump_;
	bool wall_collided_;
	bool collide_x_;
	int coyote_time_;
	/*int jump_buffer_;*/
	bool should_change_level_;

};


#endif // !CHARACTER_H_
