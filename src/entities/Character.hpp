#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Entity.hpp"
#include "../levels/Levels.hpp"

class Character : public Entity {
public:
	enum Animation {
		IDLE,
		JUMPING,
		RUNNING,
		NUM_ANIMATIONS
	};
	enum Channel {
		JUMP,
		LAND,
		RUN,
		NUM_CHANNELS
	};
	Character();
	~Character();

	void handleInput(SDL_Event& e);
	void handleKeyPressed(const SDL_Event& e);
	void handleKeyReleased(const SDL_Event& e);
	void releaseEvent();

	Vector2D getVel()const;
	void update(Level& level, Camera& cam, const float& dT);
	virtual void animate(const float& dT) override;

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
	void jump(const float& dT);

	bool isReachedGoal() const;
	void handleReachGoal();

	void saveStats() const;
	void loadStats(Level& level);
	bool loadSpriteSheetData(const std::string& path) override;
	bool loadData(const std::string& path) override;
	void resetStats();

	void handleSoundFx();
	void playJumpSound();
	void playLandSound(int& playedLandSound);
	void playRunSound();

private:
	float speed_;
	int direction_;
	int dir_left_;
	int dir_right_;
	Vector2D vel_;

	float gravity_scalar_;
	bool on_ground_;
	bool spacekey_pressed_;
	int required_frame_to_apply_jump_;
	int coyote_time_;

	bool should_change_level_;

	bool play_jump_sound_;
	Mix_Chunk* jump_sound_;
	Mix_Chunk* land_sound_;
	Mix_Chunk* walk_sound_;
};


#endif // !CHARACTER_H_
