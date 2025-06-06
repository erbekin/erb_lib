//
// Created by github.com/erbekin on 6.06.2025.
//
#pragma once
#include <random>
#include <type_traits>
#include <stdexcept>

class Random {
public:
    /**
     * @brief Seed the internal RNG engine
     *
     * @param value Seed value
     */
    static void seed(unsigned int value) {
        engine().seed(value);
    }

    /**
     * @brief Uniform distribution between [0, max]
     *
     * @tparam T Arithmetic type (integral or floating-point)
     * @param max Maximum value (inclusive)
     * @return Random value in [0, max]
     */
    template <typename T>
    static T uniform(T max) {
        return uniform<T>(T(0), max);
    }

    /**
     * @brief Uniform distribution between [min, max]
     *
     * @tparam T Arithmetic type (integral or floating-point)
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive for int, inclusive-exclusive for float)
     * @return Random value in [min, max]
     */
    template <typename T>
    static T uniform(T min, T max) {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

        if (min > max) {
            throw std::invalid_argument("Random::uniform() - min > max");
        }

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(engine());
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(engine());
        }
    }

    /**
     * @brief Uniform distribution over full type range
     *
     * @tparam T Arithmetic type (integral or floating-point)
     * @return Random value in [numeric_limits<T>::min(), numeric_limits<T>::max()]
     */
    template <typename T>
    static T uniform() {
        return uniform<T>(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
    }

private:
    static std::mt19937& engine() {
        static std::mt19937 rng{std::random_device{}()};
        return rng;
    }
};
