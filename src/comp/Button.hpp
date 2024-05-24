#ifndef BUTTON_H_
#define BUTTON_H_

#include "Transition.hpp"

/**
 * @class Button
 * @brief Represents a button in a graphical user interface.
 */
class Button {
public:
	/**
	 * @enum Type
	 * @brief Represents the type of the button.
	 */
	enum Type {
		CONTINUE,       ///< Continue button
		NEWGAME,        ///< New game button
		OPTIONS,        ///< Options button
		EXIT,           ///< Exit button
		VOLUME_SLIDER,  ///< Volume slider button
		SLIDER,         ///< Slider button
		BACK,           ///< Back button
		NUM_BUTTONS     ///< Number of buttons
	};

	/**
	 * @brief Default constructor for Button.
	 */
	Button();

	/**
	 * @brief Destructor for Button.
	 */
	~Button();

	/**
	 * @brief Renders the button on the specified renderer.
	 * @param ren The SDL renderer to render the button on.
	 */
	void render(SDL_Renderer* ren);

	/**
	 * @brief Loads the texture for the button from the specified file path.
	 * @param ren The SDL renderer to load the texture on.
	 * @param path The file path of the texture image.
	 */
	void loadTexture(SDL_Renderer* ren, const std::string& path);

	/**
	 * @brief Returns the texture of the button.
	 * @return The SDL texture of the button.
	 */
	SDL_Texture* getTexture();

	/**
	 * @brief Sets the y-coordinate of the button's rectangle.
	 * @param y The y-coordinate value.
	 */
	void setRectY(const int& y);

	/**
	 * @brief Sets the x-coordinate of the button's rectangle to center on the specified x-coordinate.
	 * @param x The x-coordinate value.
	 */
	void setRectXCenterOn(const int& x);

	/**
	 * @brief Returns the rectangle of the button.
	 * @return The SDL rectangle of the button.
	 */
	SDL_Rect getRect() const;

	/**
	 * @brief Sets the type of the button.
	 * @param type The type of the button.
	 */
	void setType(Type type);

	/**
	 * @brief Reduces the alpha value of the button's texture.
	 */
	void reduceAlpha();

	/**
	 * @brief Enhances the alpha value of the button's texture.
	 */
	void enhanceAlpha();

	/**
	 * @brief Returns the type of the button.
	 * @return The type of the button.
	 */
	Type getType() const;

	/**
	 * @brief Vertically centers the button relative to the destination button.
	 * @param destination The destination button to center on.
	 */
	void verticalCenter(Button destination);

	/**
	 * @brief Frees the resources used by the button.
	 */
	void free();

private:
	Type type_;             ///< The type of the button.
	SDL_Texture* texture_;  ///< The texture of the button.
	SDL_Rect rect_;         ///< The rectangle of the button.
	bool is_focused_;       ///< Flag indicating if the button is currently focused.
	Uint8 alpha_;           ///< The alpha value of the button's texture.
};
#endif // !BUTTON_H_