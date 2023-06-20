#pragma once
#include<box2d/box2d.h>
#include "PhysicalObject.h"

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

private:
	//Pointer to the Scene object
	Scene* m_scene = nullptr;
};