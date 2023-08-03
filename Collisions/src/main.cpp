/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <SFML/Graphics.hpp>
#include "ui.h"
#include "Button.h"
#include "Scene.h"
#include "collisionListener.h"

int main() /** Entry point for the application */
{
	sf::Vector2i windowSize(1024, 800);
	sf::ContextSettings settings(0, 0, 16, 4, 4, 0, false);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Collisions", 7U, settings); // Open main window

	sf::Clock clock;

	Button onegbutton({ 1024.f, 800.f }, windowSize, { 900, 300 }, "1g Block");
	Button hundredgbutton({ 1024.f, 800.f }, windowSize, { 900, 200 }, "100g Block");
	collisionListener collisions;
	UI points({ 1024.f, 800.f }, windowSize, { 750, 50 });
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

			if (event.type == sf::Event::MouseEntered)
			{
				onegbutton.onMouseMoved(pixelCoords);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::FloatRect onegbuttonBounds = onegbutton.getShape().getGlobalBounds();

					sf::FloatRect hundredgbuttonBounds = hundredgbutton.getShape().getGlobalBounds();

					sf::Vector2f mousePosition(pixelCoords.x, pixelCoords.y);

					if (onegbuttonBounds.contains(mousePosition))
					{
						scene.CreateBlock(1.f);
					}

					if (hundredgbuttonBounds.contains(mousePosition))
					{
						scene.CreateBlock(100.f);
					}
				}
			}



			if (event.type == sf::Event::MouseButtonReleased)
			{
				onegbutton.onMouseButtonReleased(pixelCoords, event.mouseButton.button);
				hundredgbutton.onMouseButtonReleased(pixelCoords, event.mouseButton.button);
			}

			else if (event.type == sf::Event::Resized)
				windowSize = { static_cast<int>(event.size.width), static_cast<int>(event.size.height) };
		}

		float fElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		window.clear(sf::Color::Black);

		scene.onUpdate(fElapsedTime);

		points.setTextString(scene.getCollisionCount());

		window.draw(scene);
		window.draw(points);
		window.draw(onegbutton);
		window.draw(hundredgbutton);

		window.display();
	}
	return 0;
}