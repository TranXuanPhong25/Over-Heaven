#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "BaseObject.h"
class Character : public BaseObject {
public:
	enum CharState {
		REST,
		MOVE_LEFT,
		MOVE_RIGHT,
	};
	Character();
	~Character();

	void handleInput(SDL_Event e);
	void move(const float& dT);
	int getVelX()const;
	bool shoudSlowDown() const;
private:
	int x_vel_;
	int y_vel_;
	int speed_;
	bool on_ground_;
	bool spacekey_pressed_;
	int accelerator_;
	CharState state_;
};

#endif // !CHARACTER_H_
