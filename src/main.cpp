#include "PriorityQueue.h"
#include "PriorityQueue.cpp"

#include "Particle.h"
#include "CollisionSystem.h"

#include <vector>
#include <iostream>

int main(){

	std::vector<Particle> particles = {Particle(200, 142, 0.2, 0.5, 20, 20)};
	CollisionSystem C(particles);

	C.simulate();

	return 0;
}

