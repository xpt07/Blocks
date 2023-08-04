#include "Scene.h"

std::shared_ptr<b2World> Scene::m_world = std::make_shared<b2World>(b2Vec2(0.0f, 0.0f));

Scene::Scene(const sf::Vector2f& viewSize, sf::Vector2i& parentSize) : Layer(viewSize, parentSize)
{
	// Set the world for m_degbugDraw
	m_debugDraw.setWorld(m_world);

	m_blocks.push_back(StaticBlock(sf::Vector2f(4.f, 0.5f), sf::Vector2f(bw * 30, bw / 50), m_blocks.size(), 0.f, 1.0f));
	m_blocks.push_back(StaticBlock(sf::Vector2f(7.f, 2.f), sf::Vector2f(bw * 30, bw / 50), m_blocks.size(), 90.f, 1.0f));

	//m_dblocks.push_back(DynamicBlock(sf::Vector2f(1.f, 0.65f), sf::Vector2f(bw, bw), m_dblocks.size(), 1.f, 0.0f, 1.f));
	//m_dblocks.push_back(DynamicBlock(sf::Vector2f(4.f, 0.65f), sf::Vector2f(bw, bw), m_dblocks.size(), 1.f, 0.0f, 1.f));

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

	// Flag to keep track if any dynamic block is not in contact
	bool anyBlockNotInContact = false;

	// Loop through each dynamic block object in the vector
	for (int i = 0; i < m_dblocks.size(); ++i)
	{
		auto& dblock = m_dblocks[i];
		dblock.onUpdate();

		if (!dblock.bContact())
		{
			anyBlockNotInContact = true;
			// Don't remove the dynamic block here, just mark it as not in contact
		}
	}

	// Check the flag after the loop to see if any block is not in contact
	if (anyBlockNotInContact)
	{
		// Destroy the Box2D body associated with all dynamic block objects
		for (int i = 0; i < m_dblocks.size(); ++i)
		{
			m_world->DestroyBody(m_dblocks[i].getBody());
		}

		// Clear the entire vector of dynamic blocks
		m_dblocks.clear();
	}

	// Clearing the debug draw
	m_debugDraw.clear();
}

void Scene::onKeyPress(const sf::Keyboard::Key& key)
{
	// If the Tab key is pressed, toggle the debug mode
	if (key == sf::Keyboard::Tab)
	{
		m_debugMode = !m_debugMode;
	}
}

void Scene::CreateBlock(float density)
{

	m_dblocks.push_back(DynamicBlock(sf::Vector2f(4.f, 0.65f), sf::Vector2f(bw, bw), m_dblocks.size(), 1.f, 0.0f, 1.f));

	if (m_dblocks.size() == 1)
	{
		m_collisionListener.setCollisionCount(-1);
		m_dblocks.push_back(DynamicBlock(sf::Vector2f(1.f, 0.65f), sf::Vector2f(bw, bw), m_dblocks.size(), density, 0.0f, 1.f));
	}
}

std::string Scene::getCollisionCount()
{
	std::string text = "Number of Collisions: ";

	std::string collisions = std::to_string(m_collisionListener.getCollisionCount() - 1);

	return text + collisions;
}
