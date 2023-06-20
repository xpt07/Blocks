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
	void onMouseButtonPressed(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button) override; //!< On key press
	void onKeyPress(const sf::Keyboard::Key& key) override; //!< On key press

	static inline std::shared_ptr<b2World> getWorld() { return m_world; }
private:
	static std::shared_ptr<b2World> m_world;
	std::vector<StaticBlock> m_blocks;
	std::vector<DynamicBlock> m_dblocks;
	bool m_debugMode = true;
	SFMLDebugDraw m_debugDraw;

	collisionListener m_collisionListener;
};