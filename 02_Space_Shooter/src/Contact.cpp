#include "Contact.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "Planet.h"
#include "Player.h"

Contact::Contact()
{
	_boom.setBuffer(Properties::Instance()->GetBoom());
	_clong.setBuffer(Properties::Instance()->GetClong());
	_flop.setBuffer(Properties::Instance()->GetFlop());
}

void Contact::BeginContact(b2Contact* contact)
{
	auto userDataA = contact->GetFixtureA()->GetUserData().pointer;
	auto userDataB = contact->GetFixtureB()->GetUserData().pointer;


	if (userDataA != 0 && userDataB != 0)
	{
		auto infoA = reinterpret_cast<ContactEvent*>(userDataA);
		auto infoB = reinterpret_cast<ContactEvent*>(userDataB);

		if (infoA->TypeOfContact == ContactType::Laser && infoB->TypeOfContact == ContactType::Asteroid)
		{
			infoA->_laser->player.AddScore(100);
			infoB->_asteroid->SetExploded();
			infoA->_laser->SetBroken();
			_boom.play();
		}
		else if (infoA->TypeOfContact == ContactType::Asteroid && infoB->TypeOfContact == ContactType::Laser)
		{
			infoB->_laser->player.AddScore(100);
			infoA->_asteroid->SetExploded();
			infoB->_laser->SetBroken();
			_boom.play();
		}
		else if (infoA->TypeOfContact == ContactType::Asteroid && infoB->TypeOfContact == ContactType::Asteroid)
		{
			//do something (actually nothing)
		}
		else if (infoA->TypeOfContact == ContactType::Asteroid && infoB->TypeOfContact == ContactType::Player)
		{
			infoB->_player->TakeDMG();
			infoA->_asteroid->SetExploded();
			_clong.play();
		}
		else if (infoA->TypeOfContact == ContactType::Player && infoB->TypeOfContact == ContactType::Asteroid)
		{
			infoA->_player->TakeDMG();
			infoB->_asteroid->SetExploded();
			_clong.play();
		}
		else if (infoA->TypeOfContact == ContactType::Planet && infoB->TypeOfContact == ContactType::Asteroid)
		{
			infoA->_planet->TakeDMG();
			infoB->_asteroid->SetExploded();
			_flop.play();
		}
		else if (infoA->TypeOfContact == ContactType::Asteroid && infoB->TypeOfContact == ContactType::Planet)
		{
			infoB->_planet->TakeDMG();
			infoA->_asteroid->SetExploded();
			_flop.play();
		}
	}
}

void Contact::EndContact(b2Contact* contact)
{
	auto userDataA = contact->GetFixtureA()->GetUserData().pointer;
	auto userDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (userDataA != 0 && userDataB != 0)
	{
		auto infoA = reinterpret_cast<ContactEvent*>(userDataA);
		auto infoB = reinterpret_cast<ContactEvent*>(userDataB);

		if (infoA->TypeOfContact == ContactType::Environment && infoB->TypeOfContact == ContactType::Asteroid)
		{
			if (infoB->_asteroid->IsInAnimation())
				infoB->_asteroid->SetBroken();
		}
		else if (infoA->TypeOfContact == ContactType::Asteroid && infoB->TypeOfContact == ContactType::Environment)
		{
			if (infoA->_asteroid->IsInAnimation())
				infoA->_asteroid->SetBroken();
		}
		else if (infoA->TypeOfContact == ContactType::Laser && infoB->TypeOfContact == ContactType::Roof)
		{
			infoA->_laser->SetBroken();
		}
		else if (infoA->TypeOfContact == ContactType::Roof && infoB->TypeOfContact == ContactType::Laser)
		{
			infoB->_laser->SetBroken();
		}
	}
}
