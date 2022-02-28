#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

struct Vector2
{
    float x;
    float y;
    float magnitude() {
        return sqrtf(x * x + y * y);
    }
    float magnitude_sq() {
        return x * x + y * y;
    }
    void Normalise() {
        float mag = magnitude();
        x = x / mag;
        y = y / mag;
    }
    Vector2 GetNormalised() {
        float mag = magnitude();
        return Vector2{ x / mag,y / mag };
    }
    Vector2 To(Vector2 obj) {
        return obj - (*this);
    }
    Vector2 ToOrigin() {
        return Vector2{-x, -y};
    }
    float DistanceTo(Vector2& obj) {
        return To(obj).magnitude();
    }
    void RotateDegrees(double degrees)
    {
        double DegToRad = M_PI / 180;
        RotateRadians(degrees * DegToRad);
    }
    void RotateRadians(double radians)
    {
        float currX = x;
        float currY = y;
        x = currX * cosf(radians) + currY * -sinf(radians);
        y = currX * sinf(radians) + currY * cosf(radians);
    }
    // operator overloads
    bool operator == (Vector2 & obj) {
        return ((x == obj.x) && (y == obj.y));
    }
    bool operator != (Vector2 & obj) {
        return ((x != obj.x) || (y != obj.y));
    }

    static float FindAngle(Vector2 v1, Vector2 v2) {
        return atan2f(v2.y, v2.x) - atan2f(v1.y, v1.x);
    }
    static float DotProduct(Vector2 v1, Vector2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float CrossProduct( Vector2 p1,  Vector2 p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
    static Vector2 TripleProduct( Vector2 a,  Vector2 b, Vector2 c) {
        float acDP = DotProduct(a, c);
        float bcDP = DotProduct(b, c);
        return (b * acDP) - (a * bcDP);
    }
    static bool IsZero( Vector2& v)    {
        return abs(v.x) <= std::numeric_limits<float>::epsilon()
            && abs(v.y) <= std::numeric_limits<float>::epsilon();
    }
    static bool IsIND(Vector2& v) {
        return (v.x != v.x) || (v.y != v.y);
    }
    static Vector2 Left(Vector2& v)
    {
        return Vector2{ v.y, -v.x };
    }
    static Vector2 Right(Vector2& v)
    {
        return Vector2{ -v.y, v.x };
    }

    Vector2 operator + (Vector2& obj) {
        Vector2 res;
        res.x = x + obj.x;
        res.y = y + obj.y;
        return res;
    }
    Vector2 operator += (Vector2& obj) {
        x += obj.x;
        y += obj.y;
        return (*this);
    }
    Vector2 operator - (Vector2& obj) {
        Vector2 res;
        res.x = x - obj.x;
        res.y = y - obj.y;
        return res;
    }
    Vector2 operator -= (Vector2& obj) {
        x -= obj.x;
        y -= obj.y;
        return (*this);
    }
    Vector2 operator * (float& val) {
        Vector2 res;
        res.x = x * val;
        res.y = y * val;
        return res;
    }
    Vector2 operator *= (float val) {
        x *= val;
        y *= val;
        return (*this);
    }
    Vector2 operator / (float& val) {
        Vector2 res;
        res.x = x / val;
        res.y = y / val;
        return res;
    }
    Vector2 operator /= (float val) {
        x /= val;
        y /= val;
        return (*this);
    }
    Vector2 operator * (double& val) {
        Vector2 res;
        res.x = x * val;
        res.y = y * val;
        return res;
    }
    Vector2 operator *= (double val) {
        x *= val;
        y *= val;
        return (*this);
    }
    Vector2 operator / (double& val) {
        Vector2 res;
        res.x = x / val;
        res.y = y / val;
        return res;
    }
    Vector2 operator /= (double val) {
        x /= val;
        y /= val;
        return (*this);
    }
};
