#pragma once
#include "PhysicalObject.h"

// StaticBlock is a class that represents a static block
class StaticBlock : public PhysicalObject
{
public:
	// Constructor that sets m_body to nullptr
	StaticBlock() { m_body = nullptr; }

	// Constructor that creates a static block with a given position, size, orientation, and restitution
	StaticBlock(sf::Vector2f position, 
		sf::Vector2f size, 
		unsigned int index,
		float orientationDegrees = 0.f, 
		float restitution = 0.f, 
		unsigned int maskbits = ObjectCollisionFilter::block | ObjectCollisionFilter::dynblock,
		sf::Color colour = sf::Color::White);

	// Override onContact function to be called when contact is made with another fixture
	void onContact(b2Fixture* contactFixture) override;

	// Override offContact function to be called when contact is lost with a fixture
	void offContact(b2Fixture* contactFixture) override;

	// Overridden draw method that draws the static block
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	b2Fixture* m_firstContact = nullptr; // Pointer to the first contact fixture

	sf::RectangleShape m_shape; // m_shape is a rectangle shape that represents the visual aspect of the static block
};
