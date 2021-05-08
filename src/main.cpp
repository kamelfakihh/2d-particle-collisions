#include "PriorityQueue.h"
#include "PriorityQueue.cpp"
#include "Particle.h"
#include "CollisionSystem.h"
#include "Constants.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[]){

    std::string filename("data.txt");
    if(argc >= 2) filename = std::string(argv[1]);

    std::ifstream input(filename, std::ios::in);
	std::vector<Particle*> particles;

    float x, y, vx, vy, mass, radius, temp;

    if(input.is_open()){

        input >> temp;

        while(input >> x >> y >> vx >> vy >> radius >> mass >> temp >> temp >> temp){
            particles.push_back(new Particle(x, y, vx, vy, radius, mass));
        }

        CollisionSystem C(particles);

        C.simulate();

    }else{

        std::cout << "failed to open file!" << std::endl;
    }


	return 0;
}

