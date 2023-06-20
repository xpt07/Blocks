#include "collisionListener.h"
#include <iostream>
#include "Scene.h"

void collisionListener::BeginContact(b2Contact* contact)
{
	// An array of labels for the collision filter types
	const char* labels[4] = { "Unset", "Block", "Error" , "DynBlock"};

	// Get the collision filter types and object indices for both fixtures
	unsigned int bitsA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	unsigned int bitsB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	unsigned int filterA = (bitsA & 0xFFFF0000) >> 16;
	unsigned int filterB = (bitsB & 0xFFFF0000) >> 16;

	unsigned int indexA = (bitsA & 0x0000FFFF);
	unsigned int indexB = (bitsB & 0x0000FFFF);

	// Get pointers to the fixtures
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	// Print a message indicating that a collision has started between the two objects
	std::cout << "begin contact between " << labels[filterA] << "(" << indexA << ")" << " and " << labels[filterB] << "(" << indexB << ")" << std::endl;

	// Call the onContact function of the appropriate object, depending on its collision filter type
	switch (filterA)
	{
	case ObjectCollisionFilter::block:
		m_scene->m_blocks[indexA].onContact(fixtureB);
		break;

	case ObjectCollisionFilter::dynblock:
		m_scene->m_dblocks[indexA].onContact(fixtureB);
		break;

	default:
		break;
	}

	// Call the onContact function of the appropriate object, depending on its collision filter type
	switch (filterB)
	{
	case ObjectCollisionFilter::block:
		m_scene->m_blocks[indexB].onContact(fixtureA);
		break;

	case ObjectCollisionFilter::dynblock:
		m_scene->m_dblocks[indexB].onContact(fixtureA);
		break;

	default:
		break;
	}
}


void collisionListener::EndContact(b2Contact* contact)
{
	// An array of labels for the collision filter types
	const char* labels[4] = { "Unset", "Block", "Error", "DynBlock"};
	unsigned int bitsA = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	unsigned int bitsB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	// Get the collision filter types and object indices for both fixtures
	unsigned int filterA = (bitsA & 0xFFFF0000) >> 16;
	unsigned int filterB = (bitsB & 0xFFFF0000) >> 16;

	unsigned int indexA = (bitsA & 0x0000FFFF);
	unsigned int indexB = (bitsB & 0x0000FFFF);

	// Get pointers to the fixtures
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	// Print a message indicating that a collision has ended
	std::cout << "end contact between " << labels[filterA] << "(" << indexA << ")" << " and " << labels[filterB] << "(" << indexB << ")" << std::endl;

	// Call the ofContact function of the appropriate object, depending on its collision filter type
	switch (filterA)
	{
	case ObjectCollisionFilter::block:
		m_scene->m_blocks[indexA].offContact(fixtureB);
		break;

	case ObjectCollisionFilter::dynblock:
		m_scene->m_dblocks[indexA].offContact(fixtureB);
		break;

	default:
		break;
	}

	// Call the offContact function of the appropriate object, depending on its collision filter type
	switch (filterB)
	{
	case ObjectCollisionFilter::block:
		m_scene->m_blocks[indexB].offContact(fixtureA);
		break;

	case ObjectCollisionFilter::dynblock:
		m_scene->m_dblocks[indexB].offContact(fixtureA);
		break;

	default:
		break;
	}
}