#ifndef EVENT_H
#define EVENT_H

#include "Particle.h"

class Event {

public:

    Event(float time, Particle *p1, Particle *p2);

    bool isValid();             // check if collision is still valid
    bool operator<(Event &E);    // ordered by time

    Particle* getP1();
    Particle* getP2();
    float getTime();

private:

    int count1, count2;       // collision count for a and b (to check if other collision happened before)
    Particle *p1, *p2;        // particles involved in the event
    float t;                  // expected collision time

};

#endif