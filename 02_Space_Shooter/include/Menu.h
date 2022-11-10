#pragma once

#include "Properties.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <vector>
class Menu : public sf::Drawable
{
public:
	Menu();

	void Main();

	void InGame(int HP);

	void Lost();

	void Win();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::RectangleShape> _elements;
	std::vector<sf::Text> _texts;
};