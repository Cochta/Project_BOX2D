#pragma once
#include <iostream>
#include <box2d/b2_settings.h>

class Laser;
class Asteroid;
class Environment;
class Roof;
class Player;
class Planet;

// Event Type -------------------------------------------
enum class ContactType
{
	Laser = 1, Asteroid, Environment, Roof, Player, Planet, None
};

class ContactEvent
{
public:

	ContactType TypeOfContact = ContactType::None;
	ContactEvent()
	{
		std::cout << "passe dedans" << std::endl;
		TypeOfContact = ContactType::None;
	}

	ContactEvent(Laser& laser) :
		TypeOfContact(ContactType::Laser),
		_laser(&laser)
	{

	};
	Laser* _laser = nullptr;

	ContactEvent(Asteroid& asteroid) :
		TypeOfContact(ContactType::Asteroid),
		_asteroid(&asteroid)
	{

	};
	Asteroid* _asteroid = nullptr;

	ContactEvent(Environment& environment) :
		TypeOfContact(ContactType::Environment),
		_environment(&environment)
	{

	};
	Environment* _environment = nullptr;

	ContactEvent(Roof& roof) :
		TypeOfContact(ContactType::Roof),
		_roof(&roof)
	{

	};
	Roof* _roof = nullptr;

	ContactEvent(Player& player) :
		TypeOfContact(ContactType::Player),
		_player(&player)
	{

	};
	Player* _player = nullptr;

	ContactEvent(Planet& planet) :
		TypeOfContact(ContactType::Planet),
		_planet(&planet)
	{

	};
	Planet* _planet = nullptr;

};