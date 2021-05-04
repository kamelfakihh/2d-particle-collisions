#include "PriorityQueue.h"
#include "PriorityQueue.cpp"
#include "Particle.h"
#include "CollisionSystem.h"
#include "Constants.h"

#include <vector>
#include <SFML/Graphics.hpp>

int main(){

	Particle p1 = Particle(200, 142, 0.2, 0.5, 20, 20);
	std::vector<Particle*> particles = {&p1};
	CollisionSystem C(particles);


    sf::RenderWindow window(sf::VideoMode(SCRN_W, SCRN_H), "particles");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
            window.close();
        }

        window.clear(sf::Color::Black);

		C.update();

		for(unsigned int i=0; i<particles.size(); i++){
			window.draw(p1);
		}

        window.display();

    }

	return 0;
}

