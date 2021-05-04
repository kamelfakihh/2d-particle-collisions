#include "Vector.h"

Vector::Vector(float x, float y)
: x(x), y(y) {}

Vector operator+(Vector v1, Vector v2){

    return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator-(Vector v1, Vector v2){

   return Vector(v1.x - v2.x, v1.y - v2.y); 
}

Vector operator*(Vector v1, float k){

    return Vector(v1.x * k, v1.y *k );
}

Vector operator*(float k, Vector v1){

    return v1*k;
}

// dot product
float operator*(Vector v1, Vector v2){

    return v1.x*v2.x + v1.y*v2.y;
}