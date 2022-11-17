#include "Planet.h"

Planet::Planet()
{

}

void Planet::Init(b2World& world)
{
	_shape.setTexture(Properties::Instance()->GetPlanetTexture());
	_shape.setScale(1.0f, 1.0f);
	_shape.setOrigin(_shape.getGlobalBounds().width / 2, _shape.getGlobalBounds().height / 2);

	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_staticBody;
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::Instance()->GetScreenWidth(), Properties::Instance()->GetScreenHeight()));
	bodyDef.position.Set(windowSize.x / 2, (windowSize.y + Utility::PixelsToMeters(_shape.getGlobalBounds().height / 2)) - windowSize.y / 12);

	_body = world.CreateBody(&bodyDef);

	// Shape of the physical (A circle)
	b2CircleShape planet;
	planet.m_radius = Utility::PixelsToMeters((_shape.getLocalBounds().width - 30) / 2); // 30 is magic number

	// The fixture is what it defines the physic react
	b2FixtureDef planetFixtureDef;
	planetFixtureDef.shape = &planet;
	planetFixtureDef.density = 0.0f;

	ContactEvent* m_userData = new ContactEvent(*this);
	planetFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

	_body->CreateFixture(&planetFixtureDef);

	b2Vec2 bodyPos = _body->GetPosition();

	// Translate meters to pixels
	sf::Vector2f graphicPosition = Utility::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	_shape.setPosition(graphicPosition);
}
void Planet::Update()
{
	_shape.rotate(0.1f);
}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}
