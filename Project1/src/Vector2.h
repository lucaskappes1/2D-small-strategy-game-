#pragma once

class Vector2 {
public:
    Vector2();
    Vector2(float _x, float _y);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2 operator*(float scalar) const;
    Vector2& operator*=(float scalar);
    inline const int& getIntX() const { return (int)x; }
    inline const int& getIntY() const { return (int)y; }
    inline const float& getX() const { return x; }
    inline const float& getY() const { return y; }
    float dot(const Vector2& other) const;
    float magnitude() const;
    Vector2 normalize() const;
private:
    float x;
    float y;
};

