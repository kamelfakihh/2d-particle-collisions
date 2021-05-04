#include "PriorityQueue.h"
#include "PriorityQueue.cpp"
#include "Particle.h"
#include "CollisionSystem.h"
#include "Constants.h"

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[]){

	std::vector<Particle*> particles;

    srand(time(nullptr));

    int nb;
    if(argc >= 2) nb = atoi(argv[1]);
    else nb = 10;

    for(int i=0; i<nb; i++){
        int r = 10 + rand()%15;
        float mass = 18 + rand()%20;
        float x = r + rand()%(SCRN_W-r);
        float y = r + rand()%(SCRN_H-r);
        float vx = ((float)rand()/(float)(RAND_MAX)) * 0.3 - 0.3;
        float vy = ((float)rand()/(float)(RAND_MAX)) * 0.3 - 0.3;
        particles.push_back(new Particle(x, y, vx, vy, r, mass));
    }

    // std::vector<Particle*> particles = {&p1};
	CollisionSystem C(particles);

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(SCRN_W, SCRN_H), "particles");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
            window.close();
        }

        window.clear(sf::Color::Black);
        sf::Time elapsed = clock.restart();

		C.update(elapsed.asMilliseconds());

		for(unsigned int i=0; i<particles.size(); i++){
			window.draw(*particles[i]);
		}

        window.display();

    }

	return 0;
}

