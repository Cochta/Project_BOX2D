#include "Game.h"

Game::Game() :
	_world(b2Vec2(0.0f, 0.0f)) // gravity
{
	Properties::Instance()->GetTheme().play();

	_window.create(sf::VideoMode(Properties::Instance()->GetScreenWidth(), Properties::Instance()->GetScreenHeight()), "EARTH DEFENDER", sf::Style::Fullscreen);
	_window.setPosition(sf::Vector2i(0, 0));
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(144);

	sf::Sprite s;
	s.setTexture(Properties::Instance()->GetBackgroundTexture(), true);
	for (int i = 0; i < ceil(Properties::Instance()->GetScreenWidth() / s.getGlobalBounds().width); ++i)
	{
		for (int j = 0; j < ceil(Properties::Instance()->GetScreenHeight() / s.getGlobalBounds().height); ++j)
		{
			s.setPosition(i * s.getGlobalBounds().width, j * s.getGlobalBounds().height);
			_background.emplace_back(s);
		}
	}
	_menu.Main();
	_world.SetContactListener(&_contact);
	_planet.Init(_world);
}

void Game::Play()
{
	CreateEnvironnent();

	sf::Event event;

	sf::Clock clock;
	sf::Time totalElapsed;

	while (_window.isOpen())
	{
		if (!Lost)
			spawnAsteroid();
		// on inspecte tous les ?v?nements de la fen?tre qui ont ?t? ?mis depuis la pr?c?dente it?ration

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

void Game::CreateEnvironnent()
{
	Environment rightWall(Wall::Right, _world);
	Environment leftWall(Wall::Left, _world);
	Roof roof(_world);
	Environment floor(Wall::Bottom, _world);
}

void Game::spawnAsteroid()
{
	if (IsStarted && _enemyClock.getElapsedTime().asSeconds() >= Properties::ENEMY_SPAWN_RATE)
	{
		_asteroids.emplace_back(
			Utility::getRandomInt(Utility::PixelsToMeters(Properties::Instance()->GetScreenWidth() / 10),
				Utility::PixelsToMeters(Properties::Instance()->GetScreenWidth() - (Properties::Instance()->GetScreenWidth() / 10))),
			0,
			Utility::getRandomInt(0, 11),
			_world
		);
		_asteroids.back().SetDirection(Utility::getRandomInt(0, 80) - 40, Utility::getRandomInt(10, 100));
		_enemyClock.restart();
	}
}

void Game::checkEvent(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_player.Fire(_world);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player.SetDirectionX(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player.SetDirectionX(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_player.SetDirectionY(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_player.SetDirectionY(1);
	}
}

void Game::checkEventPoll(sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
	{
		_player.time = sf::seconds(3.0f);
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
	{
		_player.SetDirectionX(0);
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
	{
		_player.SetDirectionX(0);
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
	{
		_player.SetDirectionY(0);
	}
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
	{
		_player.SetDirectionY(0);
	}
	if (event.type == sf::Event::Closed)
	{
		_window.close();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !IsStarted && !IsRules)
	{
		IsStarted = true;
		_player.Init(_world);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !IsStarted && !IsRules)
	{
		IsRules = true;
		_menu.Rules();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !IsStarted && !IsRules)
	{
		exit(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && IsRules)
	{
		IsRules = false;
		_menu.Main();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && Lost)
	{
		_menu.Main();
		Lost = false;
		IsStarted = false;
		_world.DestroyBody(_player.GetBody());
		_player = Player();
		_asteroids.clear();
		_planet.ResetHP();
	}
}

void Game::update(sf::Clock& clock, sf::Time& totalElapsed)
{
	sf::Time elapsed = clock.restart();
	if (_player.GetHP() <= 0 || _planet.GetHP() <= 0)
	{
		Lost = true;
	}
	if (Lost)
	{
		_menu.GameOver(_player.GetHP(), _player.GetScore(), _planet.GetHP());
	}
	else
	{
		_world.Step(elapsed.asSeconds(), 6, 2);
	}
	_player.Move(elapsed.asSeconds());
	_player.Update();
	_planet.Update();

	std::erase_if(_asteroids, [](Asteroid& asteroid)
		{
			return asteroid.IsBroken();
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

	for (const auto& sprite : _background)
	{
		_window.draw(sprite);
	}

	for (const auto& asteroid : _asteroids)
	{
		_window.draw(asteroid);
	}

	_window.draw(_player);
	if (IsStarted && !Lost)
	{
		_menu.InGame(_player.GetHP(), _player.GetScore(), _planet.GetHP());
	}

	_window.draw(_menu);
	_window.draw(_planet);
	// Window Display
	_window.display();
}