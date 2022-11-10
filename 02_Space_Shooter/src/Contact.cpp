#include "Contact.h"

#include <iostream>
#include <box2d/b2_contact.h>

Contact::Contact()
{
}

void Contact::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	auto typeA = static_cast<Properties::Type>(bodyA->GetFixtureList()->GetFilterData().groupIndex);
	auto typeB = static_cast<Properties::Type>(bodyB->GetFixtureList()->GetFilterData().groupIndex);

	auto userDataA = contact->GetFixtureA()->GetUserData();
	auto userDataB = contact->GetFixtureB()->GetUserData();

	auto aPointer = userDataA.pointer;
	auto bPointer = userDataA.pointer;

	if (typeA == Properties::Type::Asteroid && typeB == Properties::Type::Laser ||
		typeA == Properties::Type::Laser && typeB == Properties::Type::Asteroid)
	{
		Asteroid* a;

		if (typeA == Properties::Type::Asteroid)
		{
			a = reinterpret_cast<Asteroid*>(userDataA.pointer);

		}
		else if (typeB == Properties::Type::Asteroid)
		{
			a = reinterpret_cast<Asteroid*>(userDataB.pointer);
		}
		a->IsBroken = true;
		std::cout << a->_index << std::endl;
		// Player hit an enemy
		/*asteroid->IsBroken = true;
		std::cout << asteroid->_index << std::endl;
		std::cout << (asteroid->IsBroken ? "true" : "false") << std::endl;*/

	}
	/*
	auto elementA = contact->GetFixtureA()->GetBody()->GetUserData();
	auto elementB = contact->GetFixtureB()->GetBody()->GetUserData();

	Asteroid* asteroid = reinterpret_cast<Asteroid*>(elementA.pointer);
	Laser* laser = reinterpret_cast<Laser*>(elementB.pointer);*/

	//if (laser != nullptr && asteroid != nullptr)
	//{
	//	//asteroid->IsBroken = true;
	//	std::cout << asteroid->IsBroken << std::endl;
	//}
	//else
	//{
	//	//std::cout << "not boom" << std::endl;
	//}
}

void Contact::EndContact(b2Contact* contact)
{

}
