#include "Laser.h"

Laser::Laser(b2World& world, float x, float y)
{
	type = Properties::Type::Laser;
	_shape.setTexture(Properties::Instance()->GetLaserTexture());
	_shape.setScale(0.5, 0.5);
	_shape.setOrigin(_shape.getLocalBounds().width / 2, _shape.getLocalBounds().height / 2);


	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT));
	bodyDef.position.Set(x, y - Utility::PixelsToMeters(_shape.getGlobalBounds().height));

	_body = world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape laser;
	laser.SetAsBox(Utility::PixelsToMeters(_shape.getGlobalBounds().width * _shape.getScale().x),
		Utility::PixelsToMeters(_shape.getGlobalBounds().height * _shape.getScale().y));

	// The fixture is what it defines the physic react
	b2FixtureDef laserFixtureDef;
	laserFixtureDef.shape = &laser;
	laserFixtureDef.density = 1.0f;
	laserFixtureDef.isSensor = true;
	laserFixtureDef.filter.groupIndex = static_cast<int16>(type);
	laserFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(this);
	//laserFixtureDef.friction = 1.0f;
	////playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

	_body->CreateFixture(&laserFixtureDef);
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