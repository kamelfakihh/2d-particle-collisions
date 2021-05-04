#include "Event.h"

Event::Event(float time, Particle *p1, Particle *p2)
: t(time), p1(p1), p2(p2) {

    if(p1 != nullptr) count1 = p1->getCount();
    else count1=0;
 
    if(p2 != nullptr) count2 = p2->getCount();
    else count2=0;
}

bool Event::isValid(){

    if(p1 == nullptr && p2 != nullptr){
        return count2 == p2->getCount();
    }

    if(p2 == nullptr && p1 != nullptr){
        return count1 == p1->getCount();
    }

    if(p2 == nullptr && p1 == nullptr){
        return true;
    }

    return count1 == p1->getCount() && count2 == p2->getCount();
}

bool Event::operator<(Event &E){

    if(t < E.t) return true;
    else return false;
}

Particle* Event::getP1(){

    return p1;
}

Particle* Event::getP2(){

    return p2;
}

float Event::getTime(){

    return t;
}