#include "Asteroid.h"


Asteroid::Asteroid(float x, float y, int spriteIndex, b2World& world) : _world(world)
{
	_shape.setTexture(Properties::Instance()->GetAsteroidTexture(spriteIndex));
	//_shape.setScale(0.5, 0.5);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);


	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::Instance()->GetScreenWidth(), Properties::Instance()->GetScreenHeight()));
	bodyDef.position.Set(x, y);

	_body = _world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape laser;
	laser.SetAsBox(Utility::PixelsToMeters(_shape.getLocalBounds().width / 2),
		Utility::PixelsToMeters(_shape.getLocalBounds().height / 2));

	// The fixture is what it defines the physic react
	b2FixtureDef _asteroidFixtureDef;
	_asteroidFixtureDef.shape = &laser;
	_asteroidFixtureDef.density = 1.0f;
	_asteroidFixtureDef.isSensor = true;


	ContactEvent* m_userData = new ContactEvent(*this);
	_asteroidFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

	//laserFixtureDef.friction = 1.0f;
	////playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

	_fixture = _body->CreateFixture(&_asteroidFixtureDef);
}

Asteroid Asteroid::operator=(const Asteroid& other)
{
	Asteroid a(other);

	return a;
}

Asteroid::~Asteroid()
{
	_world.DestroyBody(_body);
}

void Asteroid::Update()
{
	if (_hasExploded)
	{
		Boom();
		_hasExploded = false;
		_clock.restart();
		_rotation = Utility::getRandomInt(0, 10) - 5;
	}
	b2Vec2 bodyPos = _body->GetPosition();

	// Translate meters to pixels
	sf::Vector2f graphicPosition = Utility::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	_shape.setPosition(graphicPosition);
	if (_isInAnimation)
	{
		_shape.rotate(_rotation);
		_shape.setScale(_shape.getScale().x + 0.02f, _shape.getScale().y + 0.02f);
		_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);
		if (_clock.getElapsedTime().asSeconds() >= 1)
		{
			SetBroken();
		}
	}
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}

void Asteroid::Boom()
{
	_body->DestroyFixture(_fixture);
	_body->SetLinearVelocity(b2Vec2(0, 0));

	_shape = sf::Sprite();
	_shape.setTexture(Properties::Instance()->GetExplosionTexture());
	_shape.setScale(0.01f, 0.01f);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);
	_isInAnimation = true;
}
