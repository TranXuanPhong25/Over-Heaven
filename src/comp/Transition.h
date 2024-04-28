#ifndef TRANSITION_H_
#define TRANSITION_H_

class Transition {
public:
    template <typename T>
    static T lerp(T a, T b, float t) {
        return a + (b - a) * t;
    }

    template <typename T>
    static T easeIn(T a, T b, float t) {
        return a + t * t * (b - a);
    }
    
    template <typename T>
    static T easeOut(T a, T b, float t) {
        return a + t * (2 - t) * (b - a);
    }

    template <typename T>
    static T easeInOut(T a, T b, float t) {
        return a + t * t * (3 - 2 * t) * (b - a);
    }

    template <typename T>
    static T easeOutIn(T a, T b, float t) {
        return a + t * (3 - 2 * t) * (b - a);
    }

    template <typename T>
    static T easeInCubic(T a, T b, float t) {
        return a + (b - a) * t * t * t;
    }
};

#endif // TRANSITION_H_