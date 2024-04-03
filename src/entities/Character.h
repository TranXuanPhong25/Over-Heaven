#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Entity.h"
#include "../levels/Levels.h"
class Character : public Entity {
public:
	enum State {
		IDLE,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMPING,
		SCROLLING
	};
	Character();
	~Character();
	void handleInput(SDL_Event& e);
	Vector2D getVel()const;
	void update(Level& level, Camera& cam, const float& dT);
	void moveX(const float& dT);
	void moveY(const float& dT);
	//void roll(const float& dT);
	void CollideX(Level& level);
	void CollideY(Level& level);
	void handleLevelInteraction(Level& level);
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& s);
private:
	bool shoudSlowDown() const;
	int speed_;
	bool on_ground_;
	bool spacekey_pressed_;
	int dir_left_;
	int dir_right_;
	bool double_jump_;
	//int accelerator_;
	State state_;
	bool rolling_;
	bool can_roll_;
	int roll_dir_;
	int rolling_frame_;
	Vector2D vel_;

};


#endif // !CHARACTER_H_
