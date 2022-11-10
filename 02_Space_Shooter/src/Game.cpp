#include "Game.h"

#include <iostream>


Game::Game() :
	_world(b2Vec2(0.0f, 0.0f)) // gravity
{
	Init();
}

void Game::Init()
{
	_window.create(sf::VideoMode(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT), "Space shooter", sf::Style::Close);
	_window.setPosition(sf::Vector2i(500, 0));
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	sf::Sprite s;
	s.setTexture(Properties::Instance()->GetBackgroundTexture(), true);
	for (int i = 0; i < ceil(Properties::WINDOW_SIZE_WIDTH / s.getGlobalBounds().width); ++i)
	{
		for (int j = 0; j < ceil(Properties::WINDOW_SIZE_HEIGHT / s.getGlobalBounds().height); ++j)
		{
			s.setPosition(i * s.getGlobalBounds().width, j * s.getGlobalBounds().height);
			_background.emplace_back(s);
		}
	}
	_menu.Main();
	_world.SetContactListener(&_contact);
}
void Game::Play()
{

	//floor
	b2BodyDef leftWallBD;
	leftWallBD.position.Set(0.0f, 0.0f);
	b2Body* leftWallBody = _world.CreateBody(&leftWallBD);

	b2PolygonShape leftWallBox;
	leftWallBox.SetAsBox(1.0f / Utility::PIXEL_METER_RATIO, static_cast<float>(Properties::WINDOW_SIZE_HEIGHT));
	leftWallBody->CreateFixture(&leftWallBox, 0.0f);

	b2BodyDef rightWallBD = leftWallBD;
	rightWallBD.position.Set(static_cast<float>(Properties::WINDOW_SIZE_WIDTH) / Utility::PIXEL_METER_RATIO, 0.0f);
	b2Body* rightWallBody = _world.CreateBody(&rightWallBD);

	b2PolygonShape rightWallBox = leftWallBox;
	rightWallBody->CreateFixture(&rightWallBox, 0.0f);

	/*b2BodyDef roofBD = leftWallBD;
	roofBD.position.Set(0.0f, 0.0f);
	b2Body* roofBody = _world.CreateBody(&roofBD);

	b2PolygonShape roofBox = leftWallBox;
	roofBox.SetAsBox(static_cast<float>(Properties::WINDOW_SIZE_WIDTH), 1.0f / Utility::PIXEL_METER_RATIO);
	roofBody->CreateFixture(&roofBox, 0.0f);*/

	sf::Event event;

	sf::Clock clock;
	sf::Time totalElapsed;

	while (_window.isOpen())
	{
		spawnAsteroid();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération

		while (_window.pollEvent(event))
		{
			checkEventPoll(event);
		}
		if (IsStarted)
		{
			checkEvent(event);
			update(clock, totalElapsed);
		}

		display();
	}
}

void Game::spawnAsteroid()
{
	if (IsStarted && _enemyClock.getElapsedTime().asSeconds() >= Properties::ENEMY_SPAWN_RATE)
	{
		//Asteroid a(
		//	Utility::getRandomInt(0,Utility::PixelsToMeters(Properties::WINDOW_SIZE_WIDTH)),
		//	0,
		//	Utility::getRandomInt(0, 11),
		//	_world
		//);
		//a.SetDirection(Utility::getRandomInt(0, 40) - 20, Utility::getRandomInt(10, 100));


		//_asteroids.emplace_back(a);

		//a.SetDirection(Utility::getRandomInt(0, 40) - 20, Utility::getRandomInt(10, 100));


		_asteroids.emplace_back(
			Utility::getRandomInt(0, Utility::PixelsToMeters(Properties::WINDOW_SIZE_WIDTH)),
			0,
			Utility::getRandomInt(0, 11),
			_world
		);
		_asteroids.back().SetDirection(Utility::getRandomInt(0, 40) - 20, Utility::getRandomInt(10, 100));
		_enemyClock.restart();
	}
}

void Game::checkEvent(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_player.Fire(_world);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player.SetDumping(0);
		_player.SetDirectionX(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player.SetDumping(0);
		_player.SetDirectionX(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_player.SetDumping(0);
		_player.SetDirectionY(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_player.SetDumping(0);
		_player.SetDirectionY(1);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_player.SetDumping(100);
		_player.SetDirection(b2Vec2(0, 0));
	}
}

void Game::checkEventPoll(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		_window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (!IsStarted)
		{
			_menu.InGame(4);
			IsStarted = true;
			_player.Init(_world);
			_planet.Init(_world);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit(0);
	}
}

void Game::update(sf::Clock& clock, sf::Time& totalElapsed)
{
	sf::Time elapsed = clock.restart();
	_world.Step(elapsed.asSeconds(), 6, 2);
	_player.Move(elapsed.asSeconds());
	_player.Update();
	_planet.Update();

	/*std::vector<Asteroid> tempAsteroid;
	for (auto a : _asteroids)
	{
		if (!a.IsBroken)
		{
			tempAsteroid.emplace_back(a);
		}
	}
	_asteroids.clear();
	_asteroids = tempAsteroid;*/
	std::erase_if(_asteroids, [](Asteroid& asteroid)
		{
			if (asteroid.IsBroken)
			{
				std::cout << "delete " << asteroid._index << std::endl;
				//asteroid.DeleteBody();
				return true;
			}
			return false;
		}
	);

	for (auto& asteroid : _asteroids)
	{
		asteroid.Update();
	}
}

void Game::display()
{
	_window.clear();

	//_window.draw(something to draw);
	_window.draw(_menu);

	for (const auto& sprite : _background)
	{
		_window.draw(sprite);
	}

	for (const auto& asteroid : _asteroids)
	{
		_window.draw(asteroid);
	}


	_window.draw(_player);
	_window.draw(_menu);
	_window.draw(_planet);
	// Window Display
	_window.display();
}