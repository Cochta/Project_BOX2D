#include "Properties.h"

Properties* Properties::_properties = nullptr;

Properties::Properties()
{
	for (size_t i = 1; i <= 12; i++)
	{
		sf::Texture newTexture;
		std::stringstream path;
		path << "data/assets/PNG/Meteors/meteor" << i << ".png";
		newTexture.loadFromFile(path.str());
		_asteroidT.push_back(newTexture);
	}
	_shipT.loadFromFile(PLAYER_PATH);
	_laserT.loadFromFile(LASER_PATH);
	_planetT.loadFromFile(PLANET_PATH);
	_backgroundT.loadFromFile(BACKGROUND_PATH);
	_explosionT.loadFromFile(EXPLOSION_PATH);
	_mainF.loadFromFile(MAIN_FONT_PATH);

	_theme.openFromFile(THEME_PATH);
	_theme.setLoop(true);

	_boom.loadFromFile(BOOM_PATH);
	_clong.loadFromFile(CLONG_PATH);
	_piou.loadFromFile(PIOU_PATH);
	_flop.loadFromFile(FLOP_PATH);

	_screenWidth = sf::VideoMode::getDesktopMode().width;
	_screenHeight = sf::VideoMode::getDesktopMode().height;
}
Properties* Properties::Instance()
{
	if (_properties == nullptr) {
		_properties = new Properties();
	}
	return _properties;
}

sf::Texture& Properties::GetAsteroidTexture(int index) {
	return _asteroidT[index];
}
sf::Texture& Properties::GetShipTexture() {
	return _shipT;
}
sf::Texture& Properties::GetLaserTexture() {
	return _laserT;
}
sf::Texture& Properties::GetExplosionTexture() {
	return _explosionT;
}

sf::Texture& Properties::GetBackgroundTexture() {
	return _backgroundT;
}
sf::Texture& Properties::GetPlanetTexture() {
	return _planetT;
}
sf::Font& Properties::GetMainFont() {
	return _mainF;
}

sf::Music& Properties::GetTheme() {
	return _theme;
}
sf::SoundBuffer& Properties::GetBoom() {
	return _boom;
}
sf::SoundBuffer& Properties::GetClong() {
	return _clong;
}
sf::SoundBuffer& Properties::GetPiou() {
	return _piou;
}
sf::SoundBuffer& Properties::GetFlop() {
	return _flop;
}

int& Properties::GetScreenWidth()
{
	return _screenWidth;
}

int& Properties::GetScreenHeight()
{
	return _screenHeight;
}
