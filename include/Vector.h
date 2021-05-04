#ifndef VECTOR_H
#define VECTOR_H

struct Vector {

    Vector(float x, float y);

    float x;
    float y;
};

Vector operator+(Vector v1, Vector v2);
Vector operator-(Vector v1, Vector v2);
Vector operator*(Vector v1, float k);
Vector operator*(float k, Vector v1);
float operator*(Vector v1, Vector v2);    // dot product

#endif