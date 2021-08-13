#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

template<typename T>
class Matrix2
{
public:
    sf::Vector2<T> iHat, jHat;
    Matrix2() : Matrix2(sf::Vector2<T>(), sf::Vector2<T>()) {};
    Matrix2(sf::Vector2<T> iHat, sf::Vector2<T> jHat) : iHat(iHat), jHat(jHat) {};

    Matrix2 operator+(const Matrix2& other) const
    {
        return Matrix2(iHat+other.iHat, jHat+other.jHat);
    }
    Matrix2 operator-() const
    {
        return Matrix2(-iHat, -jHat);
    }
    Matrix2 operator-(const Matrix2& other) const
    {
        return *this + (-other);
    }
    Matrix2 operator*(float scalar) const
    {
        return Matrix2(iHat*scalar, jHat*scalar);
    }
    Matrix2 operator/(float scalar) const
    {
        return (1.f/scalar) * (*this);
    }
    Matrix2 operator*(const Matrix2& other) const
    {
        return Matrix2(
            other.iHat.x * iHat + other.iHat.y * jHat,
            other.jHat.x * iHat + other.jHat.y * jHat
        );
    }

    explicit operator sf::Transform() const
    {
        return sf::Transform(iHat.x, jHat.x, 0,
                            iHat.y, jHat.y, 0,
                            0, 0, 1);
    }
};

template<typename T>
Matrix2<T> operator*(float scalar, const Matrix2<T>& matrix)
{
    return matrix*scalar;
}

using Matrix2f = Matrix2<float>;
