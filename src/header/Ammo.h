#ifndef AMMO_H_
#define AMMO_H_

#include "Constants.h"
#include "BaseObject.h"

const int AMMO_A = 80;
const int AMMO_VEL = 1280;


class Ammo : public BaseObject {
public:
	enum AmmoType {
		DEFAULT,
		LASER,
		SPHERE
	};
	Ammo();
	~Ammo();

	void move(const float& dT);
	bool isMoving() const;

	void setType(const int& type);
	int getType() const;
private:
	int x_vel_;
	int y_vel_;
	bool is_move_;
	int type_;
	UINT32 shoot_time_;
};
#endif // !AMMO_H_
