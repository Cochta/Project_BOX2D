
#include <iostream>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

int main()
{
	std::cout << "Hello Box 2D World" << std::endl;

	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	// The Floor

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// The Object
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(1.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	for (int32 i = 0; i < 60; ++i)
	{
		float timeStep = 1.0f / 60.0f;
		int32 v = 6;
		int32 p = 2;

		world.Step(timeStep, v, p);
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		std::cout << "Object position: x: " << position.x << " y: " << position.y << " a: " << angle << std::endl;
	}

}
