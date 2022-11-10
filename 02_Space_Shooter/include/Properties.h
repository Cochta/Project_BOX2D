#pragma once

#include <random>
#include <string>

#include <box2d/b2_math.h>
#include <SFML/Graphics.hpp>

class Properties
{
public:
	enum class Type
	{
		Asteroid = 1,
		Laser
	};
	static constexpr int WINDOW_SIZE_WIDTH = 1300;
	static constexpr int WINDOW_SIZE_HEIGHT = 900;

	inline static const std::string MAIN_FONT_PATH = "data/fonts/arial_narrow_7.ttf";
	static constexpr int FONT_SIZE = 20;

	inline static const std::string BACKGROUND_PATH = "data/assets/Backgrounds/blue.PNG";

	inline static const std::string PLAYER_PATH = "data/assets/PNG/playerShip2_blue.png";
	static constexpr float PLAYER_SPEED = 300.0f;

	inline static const std::string LASER_PATH = "data/assets/PNG/Lasers/laserBlue01.png";
	static constexpr float FIRE_RATE = 0.33f; //sec

	inline static const std::string PLANET_PATH = "data/assets/PNG/earth.png";

	static constexpr float ENEMY_SPAWN_RATE = 1.0f; //sec

	Properties(Properties& other) = delete;

	void operator=(const Properties&) = delete;

	static Properties* Instance();

	sf::Font& GetMainFont();

	sf::Texture& GetAsteroidTexture(int index);
	sf::Texture& GetBackgroundTexture();
	sf::Texture& GetPlanetTexture();
	sf::Texture& GetShipTexture();
	sf::Texture& GetLaserTexture();
	
private:
	Properties();

	static Properties* _properties;

	sf::Font _mainF;

	sf::Texture _laserT;
	sf::Texture _shipT;
	sf::Texture _backgroundT;
	sf::Texture _planetT;
	std::vector<sf::Texture> _asteroidT;

};

