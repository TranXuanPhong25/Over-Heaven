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
		DASH_LEFT,
		DASH_RIGHT,
		SLIDE_LEFT,
		SLIDE_RIGHT,
	};
	Character();
	~Character();
	void handleInput(SDL_Event& e);
	Vector2D getVel()const;
	void update(Level& level, Camera& cam, const float& dT);
	void moveX(const float& dT);
	void moveY(const float& dT);
	void applyGravity(const float& dT);
	void dash(const float& dT);
	void jump(const float& dT);
	void CollideX(Level& level);
	void CollideY(Level& level);
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& s);
private:
	bool shoudSlowDown() const;
	State state_;
	int speed_;
	int dir_left_;
	int dir_right_;
	Vector2D vel_;
	float gravity_scalar_;
	bool on_ground_;
	bool spacekey_pressed_;
	int jump_count_;
	//int accelerator_;
	bool dashing_;
	int dash_counter_;
	int dash_dir_;
	int dashing_frame_;
	int dash_cooldown_;
	bool wall_collided_;
	bool collide_x_;
	int coyote_time_;
	int jump_buffer_;

};


#endif // !CHARACTER_H_
