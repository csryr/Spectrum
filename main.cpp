#include "spectrum.h"


sf::RenderWindow window(sf::VideoMode(1200, 600), "Spec");

int main()
{

	
	sf::Event event;
	Spectrum spec(window);

	spec.loadBuffer("test2.wav");

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		spec.wavFFT();
	}
}
