#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "../core/Constants.h"

/**
 * @brief The Transition class provides static functions for performing various types of transitions.
 */
class Transition
{
public:
	Transition();
    void getIn(const float &dT);
    void NewFunction(const float &dT);
    void getOut(const float &dT);
    virtual void finishGetIn();
    virtual void finishGetOut();
    void handleTransition(const float &dT);
	void renderTransitionFx(SDL_Renderer *ren);
	void startGetInEffect();
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