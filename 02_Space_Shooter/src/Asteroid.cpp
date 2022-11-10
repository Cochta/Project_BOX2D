#include "Asteroid.h"

#include "Properties.h"
#include "Properties.h"

int Asteroid::globalIndex = 0;
Asteroid::Asteroid(float x, float y, int spriteIndex, b2World& world) : _world(world)
{
	globalIndex++;
	_index = globalIndex;
	type = Properties::Type::Asteroid;
	IsBroken = false;
	_shape.setTexture(Properties::Instance()->GetAsteroidTexture(spriteIndex));
	//_shape.setScale(0.5, 0.5);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);


	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT));
	bodyDef.position.Set(x, y);

	_body = _world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape laser;
	laser.SetAsBox(Utility::PixelsToMeters(_shape.getGlobalBounds().width / 2),
		Utility::PixelsToMeters(_shape.getGlobalBounds().height / 2));

	// The fixture is what it defines the physic react
	b2FixtureDef asteroidFixtureDef;
	asteroidFixtureDef.shape = &laser;
	asteroidFixtureDef.density = 1.0f;
	asteroidFixtureDef.isSensor = false;
	asteroidFixtureDef.filter.groupIndex = static_cast<int16>(type);
	asteroidFixtureDef.userData.pointer = reinterpret_cast<std::uintptr_t>(this);

	//laserFixtureDef.friction = 1.0f;
	////playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

	_body->CreateFixture(&asteroidFixtureDef);
}

Asteroid Asteroid::operator=(const Asteroid& other)
{
	Asteroid a(other);
	/*a._world = other._world
	b2World& _world;
	sf::Sprite _shape;
	b2Body* _body;*/

	return a;
}

void Asteroid::Update()
{
	b2Vec2 bodyPos = _body->GetPosition();

	// Translate meters to pixels
	sf::Vector2f graphicPosition = Utility::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	_shape.setPosition(graphicPosition);
}

void Asteroid::DeleteBody()
{
	
	std::cout << "delete id:" << _index << std::endl;
	_world.DestroyBody(_body);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}
