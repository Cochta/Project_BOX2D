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
	b2Vec2 windowSize = Utility::PixelsToMeters(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT));
	bodyDef.position.Set(windowSize.x / 2, (windowSize.y + Utility::PixelsToMeters(_shape.getGlobalBounds().height / 2)) - windowSize.y / 12);

	_body = world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape planet;
	planet.SetAsBox(windowSize.x - 2, Utility::PixelsToMeters(_shape.getGlobalBounds().height / 2));

	// The fixture is what it defines the physic react
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &planet;
	playerFixtureDef.density = 0.0f;

	_body->CreateFixture(&playerFixtureDef);

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
