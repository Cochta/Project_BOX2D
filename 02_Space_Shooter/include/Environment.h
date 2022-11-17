#pragma once

#include "Properties.h"
#include "Utility.h"
#include "ContactEvent.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/box2d.h>

enum class Wall
{
	Left,
	Right,
	Bottom
};
class Environment
{
public:

	Environment(Wall wall, b2World& world);
};

class Roof
{
public:
	Roof(b2World& world);
};
