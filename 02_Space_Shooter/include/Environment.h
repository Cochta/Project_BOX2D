#pragma once

#include "Properties.h"
#include "Utility.h"

#include "Laser.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/box2d.h>

#include <list>
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
