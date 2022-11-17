#include "Laser.h"

Laser::Laser(b2World& world, float x, float y, Player& player) : _world(world), player(player)
{
	_shape.setTexture(Properties::Instance()->GetLaserTexture());
	_shape.setScale(0.5, 0.5);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);


	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::Instance()->GetScreenWidth(), Properties::Instance()->GetScreenHeight()));
	bodyDef.position.Set(x, y - Utility::PixelsToMeters(_shape.getLocalBounds().height));

	_body = _world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape laser;
	laser.SetAsBox(Utility::PixelsToMeters(_shape.getLocalBounds().width / 2),
		Utility::PixelsToMeters(_shape.getLocalBounds().height / 2));

	// The fixture is what it defines the physic react
	b2FixtureDef laserFixtureDef;
	laserFixtureDef.shape = &laser;
	laserFixtureDef.density = 1.0f;
	laserFixtureDef.isSensor = true;

	ContactEvent* m_userData = new ContactEvent(*this);
	laserFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
	//laserFixtureDef.friction = 1.0f;
	////playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

	_body->CreateFixture(&laserFixtureDef);
}

Laser& Laser::operator=(const Laser& other)
{
	Laser laser(other);
	return laser;
}

Laser::~Laser()
{
	_world.DestroyBody(_body);
}


void Laser::Update()
{
	b2Vec2 bodyPos = _body->GetPosition();

	// Translate meters to pixels
	sf::Vector2f graphicPosition = Utility::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	_shape.setPosition(graphicPosition);
}

void Laser::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}