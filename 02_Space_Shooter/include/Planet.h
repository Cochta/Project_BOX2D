#pragma once

#include "Player.h"
#include "Properties.h"
#include "Utility.h"

#include "SFML/Graphics.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/box2d.h>

class Planet : public sf::Drawable
{
public:
	Planet();

	void TakeDMG() { _HP -= 1; }
	int GetHP() { return _HP; }
	void ResetHP() { _HP = 5; }

	void Init(b2World& world);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _shape;
	b2Body* _body{};

	int _HP = 5;
};
