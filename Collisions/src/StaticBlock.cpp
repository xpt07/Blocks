#include "StaticBlock.h"
#include "Scene.h"

StaticBlock::StaticBlock(sf::Vector2f position, sf::Vector2f size, unsigned int index, float orientationDegrees, float restitution, unsigned int maskbits, sf::Color colour)
{
	// Set the collision filter for the block
	m_filter = ObjectCollisionFilter::block;

	// Create the shape, setting the position, orientation, size, etc..
	m_shape.setPosition(position);
	m_shape.setSize(size);
	m_shape.setOrigin(size / 2.f);
	m_shape.setRotation(orientationDegrees);
	m_shape.setFillColor(colour);
	m_shape.setOutlineColor(colour);
	m_shape.setOutlineThickness(0.01f);

	// Calculate the half extents of the box in x and y direction
	float halfExtentX = size.x * 0.5f;
	float halfExtentY = size.y * 0.5f;

	// Convert the orientation from degrees to radians
	float orientationRadians = orientationDegrees * b2_pi / 180.f;

	// Get the world from the Scene class
	auto world = Scene::getWorld();

	// Create the body definition for a static body
	b2BodyDef rigidBodyDef;
	rigidBodyDef.type = b2_staticBody;
	rigidBodyDef.position = b2Vec2(position.x, position.y);
	rigidBodyDef.angle = orientationRadians;
	m_body = world->CreateBody(&rigidBodyDef);

	// Create a box shape for the static block
	b2PolygonShape box;
	box.SetAsBox(halfExtentX, halfExtentY);

	// Create a fixture definition for the collider
	b2FixtureDef colliderDef;
	colliderDef.restitution = restitution;
	colliderDef.shape = &box;

	// Set collision filtering for the fixture
	colliderDef.filter.categoryBits = m_filter;
	colliderDef.filter.maskBits = maskbits;

	// Attach the collider to the body
	m_body->CreateFixture(&colliderDef);

	// Set the user data for the object
	setUserData(index);
}

void StaticBlock::onContact(b2Fixture* contactFixture)
{
	// If this is the first contact, store the fixture and change the color of the pentagon
	if (m_firstContact == nullptr)
	{
		m_firstContact = contactFixture;
	}
}

void StaticBlock::offContact(b2Fixture* contactFixture)
{
	// If the stored fixture is the one that has stopped colliding, reset the stored fixture and change the color of the pentagon back
	if (m_firstContact == contactFixture)
	{
		m_firstContact = nullptr;;
	}
}

void StaticBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape); // Draws the shape
}
