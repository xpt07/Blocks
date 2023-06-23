#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

enum ObjectCollisionFilter { unset = 0, block = 1,  dynblock = 2};

// PhysicalObject is a class that represents an object with a physical body
class PhysicalObject : public sf::Drawable
{
public:

	virtual void onContact(b2Fixture* contactFixture) {};
	virtual void offContact(b2Fixture* contactFixture) {};

	void setUserData(unsigned int index) 
	{ 
		unsigned int filterbits = m_filter << 16;

		unsigned int finalbits = filterbits | index;

		m_body->GetUserData().pointer = finalbits; 
	};

	inline ObjectCollisionFilter getCollisionFilter() { return m_filter; };

	// onUpdate is a virtual method which updates the object every time step. This is left empty by default.
	virtual void onUpdate(float timestep) {};

	// getBody returns the b2Body of the object
	inline b2Body* getBody() { return m_body; }

protected:
	b2Body* m_body; // b2Body is a Box2D class that represents a rigid body in a physical simulation

	ObjectCollisionFilter m_filter;
};
