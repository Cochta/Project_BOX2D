#pragma once

#include <iostream>

#include "Properties.h"
#include "Utility.h"
#include "ContactEvent.h"

#include "SFML/Graphics.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/box2d.h>

class Asteroid : public sf::Drawable
{
public:
	Asteroid(float x, float y, int spriteIndex, b2World& world);
	Asteroid operator=(const Asteroid& other);
	~Asteroid();

	bool IsBroken() { return _isBroken; }
	void SetBroken() { _isBroken = true; }

	bool HasExploded() { return _hasExploded; }
	void SetExploded() { _hasExploded = true; }
	bool IsInAnimation() { return _isInAnimation; }

	void Update();
	void SetDirection(float x, float y) { _body->ApplyForceToCenter(b2Vec2(x, y), true); }

	void Boom();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	b2World& _world;
	sf::Sprite _shape;
	b2Body* _body;

	bool _isBroken = false;
	bool _hasExploded = false;
	bool _isInAnimation = false;

	b2Fixture* _fixture;

	sf::Clock _clock;
	float _rotation;
};
