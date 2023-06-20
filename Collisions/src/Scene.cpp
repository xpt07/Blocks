#include "Scene.h"

// Create a shared pointer to a Box2D world with a default gravity vector (0, -9.81)
std::shared_ptr<b2World> Scene::m_world = std::make_shared<b2World>(b2Vec2(0.0f, 0.0f));

Scene::Scene(const sf::Vector2f& viewSize, sf::Vector2i& parentSize) : Layer(viewSize, parentSize)
{
	// Constants used for creating blocks
	const float bw = 0.45f; // Block width
	const float halfbw = bw / 2; // Half of the block width
	const sf::Vector2f halfViewSize(viewSize.x / 2, viewSize.y / 2); // Half of the view size
	const float halfRoot2 = sqrt(2.f) / 2; // Half of the square root of 2

	// Set the world for m_degbugDraw
	m_debugDraw.setWorld(m_world);

	m_blocks.push_back(StaticBlock(sf::Vector2f(4.f, 0.5f), sf::Vector2f(bw * 30, bw / 50), m_blocks.size(), 0.f));
	m_blocks.push_back(StaticBlock(sf::Vector2f(7.f, 2.f), sf::Vector2f(bw * 30, bw / 50), m_blocks.size(), 90.f));

	m_dblocks.push_back(DynamicBlock(sf::Vector2f(4.f, 0.65f), sf::Vector2f(bw, bw), m_dblocks.size(), 1.f, 0.0f, 0.6f, ObjectCollisionFilter::block));

	// Set the collision listener for the scene and register it with the physics world
	m_collisionListener.setScene(this);
	m_world->SetContactListener(&m_collisionListener);

	// Rotate the view by 180 degrees
	m_view.rotate(180);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Set the target's view to the scene's view
	target.setView(m_view);

	// If the debug mode is enabled
	if (m_debugMode)
	{

		// Draw all the blocks
		for (int i = 0; i < m_blocks.size(); i++)
		{
			m_blocks[i].draw(target, states);
		}

		// Draw all the dynamic blocks
		for (int i = 0; i < m_dblocks.size(); i++)
		{
			m_dblocks[i].draw(target, states);
		}
	}

	else
	{
		// Draw m_debigdraw
		m_debugDraw.draw(target, states);
	}
}

void Scene::onUpdate(float timestep)
{
	// Setting the number of velocity and position iterations to update the Box2D simulation
	int velocityIteration = 3;
	int positionIterations = 5;

	// Updating the Box2D simulation by advancing it by "timestep"
	m_world->Step(timestep, velocityIteration, positionIterations);

	// Updating the position and state of each dynamic block object in the "m_dblocks" vector
	for (int i = 0; i < m_dblocks.size(); ++i)
	{
		auto& dblock = m_dblocks[i];
		dblock.onUpdate();
	}

	// Clearing the debug draw
	m_debugDraw.clear();
}

void Scene::onMouseButtonPressed(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button)
{
	// Convert the mouse coordinates to world coordinates
	sf::Vector2f Coords;
	Coords = mapPixelToView(pixelCoords);
}

void Scene::onKeyPress(const sf::Keyboard::Key& key)
{
	// If the Tab key is pressed, toggle the debug mode
	if (key == sf::Keyboard::Tab)
	{
		m_debugMode = !m_debugMode;
	}
}