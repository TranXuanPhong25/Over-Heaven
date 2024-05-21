#ifndef ENTITY_H_
#define ENTITY_H_
#include "../levels/Camera.hpp"
#include "../thirdParty/nlohmann/json.hpp"

class Entity
{
public:
	Entity();
	~Entity();
	void render(SDL_Renderer* ren);
	void free();
	bool loadTexture(SDL_Renderer* ren);
	virtual bool loadSpriteSheetData(const std::string& path) = 0;
	virtual bool loadData(const std::string& path) = 0;
	virtual void animate(const float&dT) = 0;
	SDL_Texture* getTexture();
	Vector2D getPos() const;
	SDL_Rect getRect() const;
	void updateRect(Camera& cam);

protected:
	int width_offset_;
	int height_offset_;

	float frame_duration_;
	float animation_time_;
	bool flip_;
	int width_;
	int height_;
	std::string sprite_sheet_path_;
	std::vector<std::vector<SDL_Rect>> frames_clips_;
	int current_animation_;
	int current_frame_;
	SDL_Rect rect_;
	SDL_Texture* texture_;
	Vector2D pos_;
};
#endif // !ENTITY_H_