#include "Player.h"

Player::Player()
{
	_direction = b2Vec2(0, 0);
	_clock.restart();
	_piou.setBuffer(Properties::Instance()->GetPiou());
	_piou.setVolume(10);
}

void Player::Init(b2World& world)
{
	_shape.setTexture(Properties::Instance()->GetShipTexture());
	_shape.setScale(0.5f, 0.5f);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);


	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT));
	bodyDef.position.Set(windowSize.x / 2, windowSize.y / 2);

	_body = world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape ship;
	ship.SetAsBox(Utility::PixelsToMeters(_shape.getGlobalBounds().width / 2),
		Utility::PixelsToMeters(_shape.getGlobalBounds().height / 2));

	// The fixture is what it defines the physic react
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &ship;
	playerFixtureDef.density = 1.0f;
	playerFixtureDef.friction = 1.0f;
	ContactEvent* m_userData = new ContactEvent(*this);
	playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

	//playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit


	_body->CreateFixture(&playerFixtureDef);
}

void Player::Move(float time)
{
	_body->ApplyForceToCenter(b2Vec2(_direction.x * Properties::PLAYER_SPEED * time, _direction.y * Properties::PLAYER_SPEED * time), true);
}

void Player::Fire(b2World& world)
{
	if (time.asSeconds() > Properties::FIRE_RATE)
	{
		_lasers.emplace_back(world, _body->GetPosition().x, _body->GetPosition().y, *this);
		_lasers.back().SetDirection(0, -1);
		_piou.play();
		
		_clock.restart();
	}
	time = _clock.getElapsedTime();
}

void Player::Update()
{
	b2Vec2 bodyPos = _body->GetPosition();

	// Translate meters to pixels
	sf::Vector2f graphicPosition = Utility::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	_shape.setPosition(graphicPosition);

	std::erase_if(_lasers, [](Laser& laser)
		{
			return laser.IsBroken();
		}
	);

	for (auto& laser : _lasers)
	{
		laser.Update();
	}
}

inline void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);

	for (auto& laser : _lasers)
	{
		target.draw(laser);
	}
}
