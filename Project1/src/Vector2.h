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
    static float CalculateDistance(const Vector2& first, const Vector2& second);
    inline int getIntX() const { return static_cast<int>(x); }
    inline int getIntY() const { return static_cast<int>(y); }
    inline float getX() const { return x; }
    inline float getY() const { return y; }
    void setX(float _x) { x = _x; }
    void setY(float _y) { y = _y; }
    float dot(const Vector2& other) const;
    float magnitude() const;
    Vector2 normalize() const;
private:
    float x;
    float y;
};

