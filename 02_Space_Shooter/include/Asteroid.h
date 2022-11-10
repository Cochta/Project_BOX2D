#pragma once

#include <iostream>

#include "Properties.h"
#include "Utility.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/box2d.h>

#include <vector>

#include "Properties.h"

class Asteroid : public sf::Drawable
{
public:
	Asteroid(float x, float y, int spriteIndex, b2World& world);
	Asteroid operator=(const Asteroid& other);

	bool IsBroken;
	Properties::Type type;

	void Update();
	static int globalIndex;
	int _index = 0;
	void SetDirection(float x, float y) { _body->ApplyForceToCenter(b2Vec2(x, y), true); }
	void DeleteBody();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	b2World& _world;
	sf::Sprite _shape;
	b2Body* _body;
};
