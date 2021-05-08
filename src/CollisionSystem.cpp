#include "Constants.h"
#include "CollisionSystem.h"
#include "Particle.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "PriorityQueue.cpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


CollisionSystem::CollisionSystem(std::vector<Particle*> particles)
: sf::RenderWindow(sf::VideoMode(SCRN_W, SCRN_H), "particles"), particles(particles), t(0), pq()
{

}

void CollisionSystem::predict(Particle *P){

    float dt;

    if(P == nullptr) return;
    for(unsigned int i=0; i<particles.size(); i++){

        dt = P->timeToHitParticle(*particles[i]);
        if(dt != INFINITY) pq.insert(Event(t+dt, P, particles[i]));
    }

    dt = P->timeToHitVerticalWall();
    if(dt != INFINITY) pq.insert(Event(t + dt, P, nullptr));

    dt = P->timeToHitHorizontalWall();
    if(dt != INFINITY) pq.insert(Event(t + dt, nullptr, P));

}


// update the displayed window
// then insert a null event, to re-update if no collision happens before t+0.5
void CollisionSystem::update_screen(){

    this->clear(sf::Color::Black);

    for(unsigned int i=0; i<particles.size(); i++){
        this->draw(*particles[i]);
    }

    this->display();

    // pause execution (limit fps to aprx 60)
    std::this_thread::sleep_for (std::chrono::seconds(1/60));

    pq.insert(Event(t+0.1, nullptr, nullptr));

}

void CollisionSystem::simulate(){

    // initialize PQ with collision events
    for(unsigned int i=0; i<particles.size(); i++){

        predict(particles[i]);
    }

    pq.insert(Event(0, nullptr, nullptr));

    while(!pq.isEmpty() && this->isOpen()){

        sf::Event event;
        while(this->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                this->close();
                return;
            }
        }

        // get next event
        Event e = pq.delMin();
        if(!e.isValid()) continue;

        Particle* p1 = e.getP1();
        Particle* p2 = e.getP2();

        // update position and time (change particle position to the event time)
        for(unsigned int i=0; i<particles.size(); i++){
            particles[i]->move(e.getTime() - t);
        }
        t = e.getTime();

        // process collision events
        if (p1 != nullptr && p2 != nullptr) p1->bounceOffParticle(p2);
        else if(p1 != nullptr && p2 == nullptr) p1->bounceOffVerticalWall();
        else if(p1 == nullptr && p2 != nullptr) p2->bounceOffHorizontalWall();
        if(p1 == nullptr && p2 == nullptr) update_screen();
        
        if(p1 != nullptr) predict(p1);
        if(p2 != nullptr) predict(p2);   
    }

    return;
}