#pragma once
#include <iostream>
#include "layer.h"
#include <memory>
#include <vector>
#include "box2d/box2d.h"
#include "StaticBlock.h"
#include "DynamicBlock.h"
#include "PhysicalObject.h"
#include "SFMLDebugDraw.h"
#include "collisionListener.h"

class Scene : public Layer
{
public:
	friend class collisionListener;
	Scene(const sf::Vector2f& viewSize, sf::Vector2i& parentSize); //!<Constructor with view size
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< Draw the Scene
	void onUpdate(float timestep) override; //!< Update the scene
	void onKeyPress(const sf::Keyboard::Key& key) override; //!< On key press
	void CreateBlock(float density);

	static inline std::shared_ptr<b2World> getWorld() { return m_world; }
private:
	static std::shared_ptr<b2World> m_world;
	std::vector<StaticBlock> m_blocks;
	std::vector<DynamicBlock> m_dblocks;
	bool m_debugMode = true;
	SFMLDebugDraw m_debugDraw;

	collisionListener m_collisionListener;

	// Constants used for creating blocks
	const float bw = 0.5f; // Block width
	const float halfbw = bw / 2; // Half of the block width
	//const sf::Vector2f halfViewSize(viewSize.x / 2, viewSize.y / 2); // Half of the view size
	//const float halfRoot2 = sqrt(2.f) / 2; // Half of the square root of 2
};