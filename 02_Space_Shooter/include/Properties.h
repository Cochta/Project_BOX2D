#pragma once

#include <random>
#include <string>

#include <box2d/b2_math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <iomanip>
#include <sstream>
#include <windows.h>

#include <vector>

class Properties
{
public:
	const std::string MAIN_FONT_PATH = "data/assets/Bonus/kenvector_future_thin.ttf";
	inline static int FONT_SIZE = 20;

	const std::string BACKGROUND_PATH = "data/assets/Backgrounds/blue.PNG";

	const std::string PLAYER_PATH = "data/assets/PNG/playerShip2_blue.png";
	inline static float PLAYER_SPEED = 300.0f;

	const std::string LASER_PATH = "data/assets/PNG/Lasers/laserBlue01.png";
	inline static float FIRE_RATE = 0.25f; //sec
	inline static float LASER_SPEED = 40.0f;

	const std::string PLANET_PATH = "data/assets/PNG/earth.png";

	std::string EXPLOSION_PATH = "data/assets/PNG/boom.png";

	const std::string THEME_PATH = "data/sounds/Theme.flac";

	/*inline static const std::string BOOM_PATH = "data/sounds/Boom.wav";
	inline static const std::string CLONG_PATH = "data/sounds/Clong.wav"; // version débile
	inline static const std::string PIOU_PATH = "data/sounds/Tic.wav";
	inline static const std::string FLOP_PATH = "data/sounds/Flop.wav";*/

	const std::string BOOM_PATH = "data/sounds/AsteroidBreak.ogg";
	const std::string CLONG_PATH = "data/sounds/DamageTaken.ogg";// version normale
	const std::string PIOU_PATH = "data/sounds/Piou.ogg";
	const std::string FLOP_PATH = "data/sounds/EarthDamaged.ogg";

	inline static float ENEMY_SPAWN_RATE = 0.5f; //sec

	Properties(Properties& other) = delete;

	void operator=(const Properties&) = delete;

	static Properties* Instance();

	sf::Font& GetMainFont();

	sf::Texture& GetAsteroidTexture(int index);
	sf::Texture& GetBackgroundTexture();
	sf::Texture& GetPlanetTexture();
	sf::Texture& GetShipTexture();
	sf::Texture& GetLaserTexture();
	sf::Texture& GetExplosionTexture();

	sf::Music& GetTheme();
	sf::SoundBuffer& GetBoom();
	sf::SoundBuffer& GetClong();
	sf::SoundBuffer& GetPiou();
	sf::SoundBuffer& GetFlop();

	int& GetScreenWidth();
	int& GetScreenHeight();

private:
	Properties();

	static Properties* _properties;

	sf::Font _mainF;

	sf::Texture _laserT;
	sf::Texture _shipT;
	sf::Texture _backgroundT;
	sf::Texture _planetT;
	sf::Texture _explosionT;
	std::vector<sf::Texture> _asteroidT;

	sf::Music _theme;
	sf::SoundBuffer _boom;
	sf::SoundBuffer _clong;
	sf::SoundBuffer _piou;
	sf::SoundBuffer _flop;

	int _screenWidth;
	int _screenHeight;
};

