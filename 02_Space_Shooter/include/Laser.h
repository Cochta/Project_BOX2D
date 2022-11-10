#pragma once

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
class Laser : public sf::Drawable
{
public:
	Laser(b2World& world, float x, float y);

	Properties::Type type;

	void Update();

	void SetDirection(float x, float y){ _body->ApplyForceToCenter(b2Vec2(x, y), true); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	b2Body* _body;
	sf::Sprite _shape;
};