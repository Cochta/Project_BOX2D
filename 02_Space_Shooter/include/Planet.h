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
class Planet : public sf::Drawable
{
public:
	Planet();

	void Init(b2World& world);

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _shape;
	b2Body* _body{};
};