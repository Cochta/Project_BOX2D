#pragma once

#include "Properties.h"
#include "Utility.h"
#include "ContactEvent.h"

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
private:
	b2World& _world;
	b2Body* _body;
	sf::Sprite _shape;

	bool _isBroken = false;

public:
	Laser(b2World& world, float x, float y, Player& player);
	Laser& operator=(const Laser& other);
	~Laser();

	Player& player;

	bool IsBroken() { return _isBroken; }
	void SetBroken() { _isBroken = true; }

	void Update();

	void SetDirection(float x, float y) { _body->ApplyForceToCenter(b2Vec2(x * Properties::LASER_SPEED, y * Properties::LASER_SPEED), true); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};