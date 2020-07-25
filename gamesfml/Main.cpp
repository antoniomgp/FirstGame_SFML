#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>


int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My first game", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//Game loop
	while (window.isOpen()) {
		//Event pooling
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

	//Update

	//Render
	window.clear(sf::Color::Blue); // Clear old frame

	// Draw game
	window.display();

	//End of application
	return 0;
}