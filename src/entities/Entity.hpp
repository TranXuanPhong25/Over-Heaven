#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
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
	SDL_Texture* getTexture();
	Vector2D getPos() const;
	SDL_Rect getRect() const;
	void updateRect(Camera& cam);

protected:
	int width_offset_;
	int height_offset_;

	int width_;
	int height_;
	std::string sprite_sheet_path_;
	std::vector<std::vector<SDL_Rect>> frames_clips_;
	std::pair<int, int> current_frame_clip_;
	SDL_Rect rect_;
	SDL_Texture* texture_;
	Vector2D pos_;
};
#endif // !BASE_OBJECT_H_