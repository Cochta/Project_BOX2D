#pragma once

#include <box2d/b2_world_callbacks.h>

#include "Laser.h"
#include "Asteroid.h"
class Contact : public b2ContactListener
{
public:
	Contact();

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
private:

};