#pragma once

#include "Menu.h"
#include "Player.h"
#include "Planet.h"
#include "Asteroid.h"
#include "Utility.h"
#include "Contact.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
class Game
{
public:
	Game();

	void Init();
	void Play();

private:
	sf::RenderWindow _window;
	std::vector<sf::Sprite> _background;

	sf::Clock _enemyClock;

	Menu _menu;

	b2World _world;

	Player _player;
	Planet _planet;
	std::vector<Asteroid> _asteroids;

	Contact _contact;

	bool IsStarted = false;

	void spawnAsteroid();
	void checkEvent(sf::Event& event);
	void checkEventPoll(sf::Event& event);
	void update(sf::Clock& clock, sf::Time& totalElapsed);
	void display();
};