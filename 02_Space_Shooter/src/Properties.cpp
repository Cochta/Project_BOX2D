#include "Properties.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

Properties* Properties::_properties = nullptr;

Properties::Properties()
{
    for (size_t i = 1; i <= 12; i++)
    {
        sf::Texture newTexture;
        std::stringstream path;
        path << "data/assets/PNG/Meteors/meteor" << i << ".png";
        std::cout << "Path=" << path.str() << std::endl;

        newTexture.loadFromFile(path.str());
        _asteroidT.push_back(newTexture);
    }
    _shipT.loadFromFile(PLAYER_PATH);
    _laserT.loadFromFile(LASER_PATH);
    _planetT.loadFromFile(PLANET_PATH);
    _backgroundT.loadFromFile(BACKGROUND_PATH);
    _mainF.loadFromFile(MAIN_FONT_PATH);
}
Properties* Properties::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangerous in case two instance threads wants to access at the same time
     */
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
sf::Texture& Properties::GetLaserTexture(){
    return _laserT;
}
sf::Texture& Properties::GetBackgroundTexture(){
    return _backgroundT;
}
sf::Texture& Properties::GetPlanetTexture() {
    return _planetT;
}
sf::Font& Properties::GetMainFont(){
    return _mainF;
}

