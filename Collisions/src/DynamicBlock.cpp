#include "Scene.h"

DynamicBlock::DynamicBlock(sf::Vector2f position, sf::Vector2f size, unsigned int index, float density, float orientationDegrees, float restitution, unsigned int maskbits)
{
	// Set collision filter for this object
	m_filter = ObjectCollisionFilter::dynblock;

	// Create the shape, setting the position, orientation, size, etc..
	m_shape.setPosition(position);

	if (index == 1)
	{
		m_shape.setSize(sf::Vector2f(1.5 * size.x, 1.5 * size.y));
		m_shape.setOrigin(sf::Vector2f(size.x, size.y / 2.f));
	}
	else
	{
		m_shape.setSize(size);
		m_shape.setOrigin(size / 2.f);
	}
	m_shape.setRotation(orientationDegrees);
	m_shape.setFillColor(sf::Color::Black);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOutlineThickness(0.01f);

	// Calculate the half extents of the box in x and y direction
	float halfExtentX = size.x * 0.5f;
	float halfExtentY = size.y * 0.5f;

	// Convert the orientation from degrees to radians
	float orientationRadians = orientationDegrees * b2_pi / 180.f;

	// Get the world from the Scene class
	auto world = Scene::getWorld();

	// Create the body definition for a dynamic body
	b2BodyDef rigidBodyDef;
	rigidBodyDef.type = b2_dynamicBody;
	rigidBodyDef.position = b2Vec2(position.x, position.y);
	rigidBodyDef.angle = orientationRadians;
	rigidBodyDef.fixedRotation = true;
	rigidBodyDef.linearDamping = 0.0f;
	m_body = world->CreateBody(&rigidBodyDef);

	// Create a box shape for the dynamic block
	b2PolygonShape box;
	box.SetAsBox(halfExtentX, halfExtentY);

	// Create a fixture definition for the collider
	b2FixtureDef colliderDef;
	colliderDef.restitution = 1.f;
	colliderDef.shape = &box;
	colliderDef.density = density;
	colliderDef.friction = 0.0f;

	colliderDef.filter.categoryBits = m_filter;
	colliderDef.filter.maskBits = maskbits;

	// Attach the collider to the body
	m_body->CreateFixture(&colliderDef);

	m_index = index;
	m_density = density;
	setUserData(index);
}

void DynamicBlock::onContact(b2Fixture* contactFixture)
{
	// If this is the first contact, set m_firstContact to the contactFixture and change the colour of the shape
	if (m_firstContact == nullptr)
	{
		m_firstContact = contactFixture;

		if (m_index == 1)
		{
			// Apply your impulse here
			b2Vec2 impulse(m_density, 0.0f);  // Modify the impulse vector as per your requirement
			m_body->ApplyLinearImpulseToCenter(impulse, true);
		}
	}
}

void DynamicBlock::offContact(b2Fixture* contactFixture)
{
	// If the contactFixture is the same as m_firstContact, set m_firstContact to nullptr and restore the previous colour of the shape
	if (m_firstContact == contactFixture)
	{
		m_firstContact = nullptr;;
	}
}

void DynamicBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape); // Draws the shape
}

void DynamicBlock::onUpdate()
{
	// Update the position and rotation of the shape to match the position and angle of the body
	m_shape.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
}