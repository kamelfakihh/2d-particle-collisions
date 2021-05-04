#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

#include <SFML/Graphics.hpp>

class Particle : public sf::CircleShape {

public:

    Particle(float x, float y, float vx, float vy, float raduis, float mass);

    void setPosition (Vector r);     // overloaded base class method
    void move(float dt);                    // update particle position
    int getCount();                     // return number of collisions

    // predicting a collision
    float timeToHitParticle(Particle &P);
    float timeToHitVerticalWall();
    float timeToHitHorizontalWall();

    // resolving a collision
    void bounceOffParticle(Particle *P);
    void bounceOffVerticalWall();
    void bounceOffHorizontalWall();

private:

    Vector r;        // postion
    Vector v;        // velocity
    float radius;         // radius
    float m;         // mass
    int count;       // number of collisions

};

#endif