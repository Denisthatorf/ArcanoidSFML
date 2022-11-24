#pragma once
#include <math.h>

template<typename T>
struct vector2d
{
    T x;
    T y;

    vector2d() : x(0), y(0) {}
    vector2d(T x, T y) : x(x), y(y) {};

    float length() const
        { return std::sqrt(x * x + y * y);}

    float lengthSquered() const
        { return x * x + y * y;}

    vector2d<T> dest_vector(vector2d<T> vector)
        { return { vector.x - this->x, vector.y - this->y }; }


    vector2d<T> normalize()
    {
        vector2d result;
        float length = this->length();

        result.x = this->x / length;
        result.y = this->y / length;

        return result;
    }

    T dot_product(vector2d<T> vector)
        { return x * vector.x + y * vector.y; }

    vector2d<T> reflect(vector2d<T> normal)
    {
       //r=d−2(d⋅n)n 
        float dn = 2 * this->dot_product(normal);
        vector2d<float> v = normal * dn;
        auto v2 = v.dest_vector(*(this));
        return v2;
    }

    vector2d<T> operator/ (T num)
        { return { x / num, y / num }; }

    vector2d<T> operator* (T num)
        { return { x * num, y * num }; }

    vector2d<T> operator- (T num)
        { return { x - num, y - num }; }

    vector2d<T> operator+ (T num)
        { return { x + num, y + num }; }

    void operator += (vector2d<T> vec)
        { this->x += vec.x; this->y += vec.y; }

};
