#include "Constants.h"
#include "Particle.h"
#include "Vector.h"

#include <math.h>
#include <iostream>

Particle::Particle(float x, float y, float vx, float vy, float radius, float mass)
: sf::CircleShape(radius), r(Vector(x, y)), v(Vector(vx, vy)), radius(radius), m(mass), count(0)
{
    this->setPosition(r);
}

void Particle::setPosition (Vector r){

    // transforms circle position, so its drawn around its center
    // and not the top left corner
    sf::CircleShape::setPosition(r.x+radius/2, r.y+radius/2);
}

void Particle::move(float dt){

    r = r + (v*dt);

    std::cout << r.x << " " << r.y << std::endl;
}

int Particle::getCount(){

    return count;
}

float Particle::timeToHitParticle(Particle &P){

    Vector dv = this->v - P.v;
    Vector dr = this->r - P.r;
    float dvdr = dv*dr;

    if(dvdr >= 0){
        return INFINITY;
    }

    float drdr = dr*dr;
    float dvdv = dv*dv;
    float d = pow(dvdr, 2) - dvdv*(drdr - pow(this->radius + this->radius, 2));

    if(d < 0){
        return INFINITY;
    }

    return -(dvdr + pow(d, 0.5))/dvdv;
}

float Particle::timeToHitVerticalWall(){

    // time to hit right wall
    if(v.x > 0){

        return (R_WALL_POS - radius - r.x)/v.x;
    }
    // time to hit right wall
    else{

        return -(r.x - radius - L_WALL_POS)/v.x;
    }
}

float Particle::timeToHitHorizontalWall(){

    // time to down wall
    if(v.y > 0){

        return (D_WALL_POS - radius - r.y)/v.y;
    }
    // time to up wall
    else{

        return -(r.y - radius - U_WALL_POS)/v.y;
    }
}

void Particle::bounceOffParticle(Particle *P){

    Vector dv = this->v - P->v;
    Vector dr = this->r - P->r;
    float dvdr = dv*dr;
    float sigma = radius + P->radius;

    float j = ( 2*m*P->m*dvdr )/( m*P->m*sigma );
    
    float jx = (j*(r.x - P->r.x))/sigma;
    float jy = (j*(r.y - P->r.y))/sigma;

    this->v = this->v + Vector(jx, jy)*(1/m);
    P->v = P->v - Vector(jx, jy)*(1/P->m);

    this->count += 1;
    P->count += 1;

    return;
}

void Particle::bounceOffVerticalWall(){

    v.x = v.x*(-1);
    this->count += 1;
}

void Particle::bounceOffHorizontalWall(){

    v.y = v.y*(-1);
    this->count += 1;
}