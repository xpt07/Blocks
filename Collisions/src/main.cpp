/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <SFML/Graphics.hpp>
#include "ui.h"
#include "Scene.h"
#include "collisionListener.h"

void main() /** Entry point for the application */
{
	sf::Vector2i windowSize(1024, 800);
	sf::ContextSettings settings(0, 0, 16, 4, 4, 0, false);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Collisions", 7U, settings); // Open main window

	sf::Clock clock;

	collisionListener collisions;
	UI points({ 1024.f, 800.f }, windowSize, { 700, 10 });
	Scene scene({ 8,6 }, windowSize);

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			sf::Vector2i pixelCoords(event.mouseButton.x, event.mouseButton.y);

			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				scene.onKeyPress(event.key.code);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << pixelCoords.x << " " << pixelCoords.y << std::endl;
				scene.onMouseButtonPressed(pixelCoords, event.mouseButton.button);
			}

			else if (event.type == sf::Event::Resized)
				windowSize = { static_cast<int>(event.size.width), static_cast<int>(event.size.height) };
		}

		points.setTextString(collisions.getCollisionCount());

		float fElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		window.clear(sf::Color::Black);

		scene.onUpdate(fElapsedTime);

		window.draw(scene);
		window.draw(points);

		window.display();
	}

}