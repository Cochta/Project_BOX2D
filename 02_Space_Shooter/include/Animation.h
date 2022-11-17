#pragma once

#include <iostream>

#include "Properties.h"
#include "Utility.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class AnimType
{
	Explosion
};

class Animation : public sf::Drawable
{
public:
	Animation(AnimType type);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _shape;

	void Explosion();
};