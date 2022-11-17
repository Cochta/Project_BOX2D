#pragma once

#include <iostream>
#include <fstream>

#include "Properties.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <vector>
class Menu : public sf::Drawable
{
public:
	Menu();

	void Main();

	void InGame(int HP, int score);

	void GameOver(int score);

	void Rules();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::RectangleShape> _elements;
	std::vector<sf::Text> _texts;
	int _highScore;
};