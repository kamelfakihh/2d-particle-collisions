#include "Constants.h"
#include "CollisionSystem.h"
#include "Particle.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "PriorityQueue.cpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

CollisionSystem::CollisionSystem(std::vector<Particle> particles)
: particles(particles), t(0), pq(), sf::RenderWindow(sf::VideoMode(SCRN_W, SCRN_H), "Bouncing ball")
{

}

void CollisionSystem::predict(Particle *P){

    if(P == nullptr) return;
    for(unsigned int i=0; i<particles.size(); i++){

        float dt = P->timeToHitParticle(particles[i]);
        pq.insert(Event(t+dt, P, &particles[i]));
    }

    pq.insert(Event(t + P->timeToHitVerticalWall(), P, nullptr));
    pq.insert(Event(t + P->timeToHitHorizontalWall(), nullptr, P));

}

void CollisionSystem::update_screen(){

    this->clear(sf::Color::Black);

    for(unsigned int i=0; i<particles.size(); i++){
        this->draw(particles[i]);
    }

    this->display();
}

void CollisionSystem::simulate(){

    // initialize PQ with collision events
    for(unsigned int i=0; i<particles.size(); i++){

        predict(&particles[i]);
    }

    pq.insert(Event(0, nullptr, nullptr));
    update_screen();

    while(!pq.isEmpty() && this->isOpen()){

        sf::Event event;
        while(this->pollEvent(event)){
            if(event.type == sf::Event::Closed)
            this->close();
        }


        // get next event
        Event e = pq.delMax();
        if(!e.isValid()) continue;

        Particle* p1 = e.getP1();
        Particle* p2 = e.getP2();

        // update position and time (change particle position to the event time)
        for(unsigned int i=0; i<particles.size(); i++){
            particles[i].move(e.getTime() - t);
        }
        t = e.getTime();

        // process collision events
        if (p1 != nullptr && p2 != nullptr) p1->bounceOffParticle(p2);
        else if(p1 != nullptr && p2 == nullptr) p1->bounceOffVerticalWall();
        else if(p1 == nullptr && p2 != nullptr) p2->bounceOffHorizontalWall();
        
        this->update_screen();

        if(p1 != nullptr) predict(p1);
        if(p2 != nullptr) predict(p2);   
    }

    return;
}