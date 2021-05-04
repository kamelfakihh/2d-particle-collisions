#include "Constants.h"
#include "CollisionSystem.h"
#include "Particle.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "PriorityQueue.cpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

CollisionSystem::CollisionSystem(std::vector<Particle*> particles)
: particles(particles), t(0), pq()
{
    // initialize PQ with collision events
    for(unsigned int i=0; i<particles.size(); i++){

        predict(particles[i]);
    }

    pq.insert(Event(0, nullptr, nullptr));

}

void CollisionSystem::predict(Particle *P){

    if(P == nullptr) return;
    for(unsigned int i=0; i<particles.size(); i++){

        float dt = P->timeToHitParticle(*particles[i]);
        pq.insert(Event(t+dt, P, particles[i]));
    }

    pq.insert(Event(t + P->timeToHitVerticalWall(), P, nullptr));
    pq.insert(Event(t + P->timeToHitHorizontalWall(), nullptr, P));

}

void CollisionSystem::moveParticles(float dt){
    for(unsigned int i=0; i<particles.size(); i++){
        particles[i]->move(dt);
    }
    t += dt;
}

void CollisionSystem::update(float dt){

    if(!pq.isEmpty()){

        Event e = pq.getMin();
        
        // // if the next event (collision) time is not reached yet
        // we only move particles
        if(t+dt < e.getTime()){
            
            moveParticles(dt);
            return;
        }

        // get next event
        e = pq.delMin();
        if(!e.isValid()) return;

        Particle* p1 = e.getP1();
        Particle* p2 = e.getP2();

        // update position and time (change particle position to the event time)
        moveParticles(e.getTime() - t);

        // process collision events
        if (p1 != nullptr && p2 != nullptr) p1->bounceOffParticle(p2);
        else if(p1 != nullptr && p2 == nullptr) p1->bounceOffVerticalWall();
        else if(p1 == nullptr && p2 != nullptr) p2->bounceOffHorizontalWall();
        
        if(p1 != nullptr) predict(p1);
        if(p2 != nullptr) predict(p2);   
    }

    return;
}