#pragma once
#include<box2d/box2d.h>
#include "PhysicalObject.h"
#include <string>

// Forward declaration of the Scene class
class Scene;

class collisionListener : public b2ContactListener
{
public:
	// Destructor for the collisionListener class
	~collisionListener() { m_scene = nullptr; };

	// This function is called when two physical objects start colliding
	void BeginContact(b2Contact* contact) override;

	// This function is called when two physical objects stop colliding
	void EndContact(b2Contact* contact) override;

	// Setter function to set the pointer to the current Scene object
	void setScene(Scene* pScene) { m_scene = pScene; };

	inline std::string getCollisionCount()
	{
		return "Number of Collisions: " + std::to_string(m_collisionCount - 1);
	};


private:
	//Pointer to the Scene object
	Scene* m_scene = nullptr;

	int m_collisionCount = 0;
};
