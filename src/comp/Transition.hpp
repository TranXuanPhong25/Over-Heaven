#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "../core/Constants.hpp"

/**
 * @brief Class representing a transition effect.
 */
class Transition {
public:
	/**
	 * @brief Default constructor for the Transition class.
	 */
	Transition();

	/**
	 * @brief Performs the "get in" transition effect.
	 *
	 * @param dT The time delta.
	 */
	void getIn(const float& dT);

	/**
	 * @brief Performs the "get out" transition effect.
	 *
	 * @param dT The time delta.
	 */
	void getOut(const float& dT);

	/**
	 * @brief Called when the "get in" transition effect finishes.
	 */
	virtual void finishGetIn();

	/**
	 * @brief Called when the "get out" transition effect finishes.
	 */
	virtual void finishGetOut();

	/**
	 * @brief Handles the transition effect.
	 *
	 * @param dT The time delta.
	 */
	void handleTransition(const float& dT);

	/**
	 * @brief Renders the transition effect.
	 *
	 * @param ren The SDL renderer.
	 */
	void renderTransitionFx(SDL_Renderer* ren);

	/**
	 * @brief Starts the "get in" effect.
	 */
	void startGetInEffect();

	/**
	 * @brief Starts the "get out" effect.
	 */
	void startGetOutEffect();

	/**
	 * @brief Performs linear interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T lerp(T a, T b, float t)
	{
		return static_cast<T>(a + (b - a) * t);
	}

	/**
	 * @brief Performs ease-in interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T easeIn(T a, T b, float t)
	{
		return static_cast<T>(a + t * t * (b - a));
	}

	/**
	 * @brief Performs ease-out interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T easeOut(T a, T b, float t)
	{
		return static_cast<T>(a + t * (2 - t) * (b - a));
	}

	/**
	 * @brief Performs ease-in-out interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T easeInOut(T a, T b, float t)
	{
		return static_cast<T>(a + t * t * (3 - 2 * t) * (b - a));
	}

	/**
	 * @brief Performs ease-out-in interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T easeOutIn(T a, T b, float t)
	{
		return static_cast<T>(a + t * (3 - 2 * t) * (b - a));
	}

	/**
	 * @brief Performs cubic ease-in interpolation between two values.
	 *
	 * @tparam T The type of the values to interpolate.
	 * @param a The starting value.
	 * @param b The ending value.
	 * @param t The interpolation factor (between 0 and 1).
	 * @return The interpolated value.
	 */
	template <typename T>
	static T easeInCubic(T a, T b, float t)
	{
		return static_cast<T>(a + (b - a) * t * t * t);
	}

	float overlay_alpha_;
protected:
	bool is_on_enter_;
	bool is_on_exit_;
};

#endif // TRANSITION_H_