#pragma once
#include "PhysicalObject.h"

// DynamicBlock is a class that represents a a dynamic block
class DynamicBlock : public PhysicalObject
{
public:
	// Constructor that sets m_body to nullptr
	DynamicBlock() { m_body = nullptr; }

	// Constructor that creates a dynamic block with a given position, size, index, colour, density, orientation, and restitution and maskbits
	DynamicBlock(sf::Vector2f position,
		sf::Vector2f size,
		unsigned int index,
		float density = 1.0f,
		float orientationDegrees = 0.f,
		float restitution = 0.f,
		unsigned int maskbits = ObjectCollisionFilter::block | ObjectCollisionFilter::dynblock);

	// Function called when the dynamic block comes into contact with another fixture in the physics simulation
	void onContact(b2Fixture* contactFixture) override;

	// Function called when the dynamic block goes out of contact with another fixture in the physics simulation
	void offContact(b2Fixture* contactFixture) override;

	// Overridden draw method that draws the static block
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Function called every frame to update the state of the dynamic block
	void onUpdate();

private:

	b2Fixture* m_firstContact = nullptr; // Pointer to the first fixture that the dynamic block comes into contact with in the physics simulation
	int m_index;
	sf::Color m_colour; // Current color of the dynamic block
	sf::RectangleShape m_shape; // m_shape is a rectangle shape that represents the visual aspect of the dynamic block
};
