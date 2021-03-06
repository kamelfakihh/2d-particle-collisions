#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "Particle.h"
#include "Event.h"
#include "PriorityQueue.h"

#include <vector>
#include <SFML/Graphics.hpp>

class CollisionSystem : public sf::RenderWindow {

public:

    CollisionSystem(std::vector<Particle*> particles);

    // predict possible collisions of a particle
    void predict(Particle *P);

    // update the screen
    void update_screen();

    // run the simulation
    void simulate();

private:

    std::vector<Particle*> particles;  // pointer to particles
    float t;                            // simulation clock
    MinPQ<Event> pq;

};

#endif