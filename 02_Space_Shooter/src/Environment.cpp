#include "Environment.h"

Environment::Environment(Wall wall, b2World& world)
{
	if (wall == Wall::Left)
	{
		b2BodyDef leftWallBD;
		leftWallBD.position.Set(0.0f, 0.0f);
		b2Body* leftWallBody = world.CreateBody(&leftWallBD);

		b2PolygonShape leftWallBox;
		leftWallBox.SetAsBox(1.0f / Utility::PIXEL_METER_RATIO, static_cast<float>(Properties::WINDOW_SIZE_HEIGHT));

		b2FixtureDef leftWallFixtureDef;
		leftWallFixtureDef.shape = &leftWallBox;
		leftWallFixtureDef.density = 1.0f;

		ContactEvent* m_userData = new ContactEvent(*this);
		leftWallFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
		leftWallBody->CreateFixture(&leftWallFixtureDef);
	}
	else if (wall == Wall::Right)
	{
		b2BodyDef rightWallBD;
		rightWallBD.position.Set(static_cast<float>(Properties::WINDOW_SIZE_WIDTH) / Utility::PIXEL_METER_RATIO, 0.0f);
		b2Body* rightWallBody = world.CreateBody(&rightWallBD);

		b2PolygonShape rightWallBox;
		rightWallBox.SetAsBox(1.0f / Utility::PIXEL_METER_RATIO, static_cast<float>(Properties::WINDOW_SIZE_HEIGHT));

		b2FixtureDef rightWallFixtureDef;
		rightWallFixtureDef.shape = &rightWallBox;
		rightWallFixtureDef.density = 1.0f;

		ContactEvent* m_userData = new ContactEvent(*this);
		rightWallFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
		rightWallBody->CreateFixture(&rightWallFixtureDef);
	}
	else if (wall == Wall::Bottom)
	{
		b2BodyDef floorBD;
		floorBD.position.Set(0.0f, (Properties::WINDOW_SIZE_HEIGHT / Utility::PIXEL_METER_RATIO));
		b2Body* floorBody = world.CreateBody(&floorBD);

		b2PolygonShape floorBox;
		floorBox.SetAsBox(static_cast<float>(Properties::WINDOW_SIZE_WIDTH), (Properties::WINDOW_SIZE_HEIGHT / 12) / Utility::PIXEL_METER_RATIO);

		b2FixtureDef floorFixtureDef;
		floorFixtureDef.shape = &floorBox;
		floorFixtureDef.density = 1.0f;

		/*ContactEvent* m_userData = new ContactEvent(*this);
		floorFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);*/
		floorBody->CreateFixture(&floorFixtureDef);

		b2BodyDef floorBD2;
		floorBD2.position.Set(0.0f, (Properties::WINDOW_SIZE_HEIGHT / Utility::PIXEL_METER_RATIO));
		b2Body* floorBody2 = world.CreateBody(&floorBD2);

		b2PolygonShape floorBox2;
		floorBox2.SetAsBox(static_cast<float>(Properties::WINDOW_SIZE_WIDTH), 1 / Utility::PIXEL_METER_RATIO);

		b2FixtureDef floorFixtureDef2;
		floorFixtureDef2.shape = &floorBox2;
		floorFixtureDef2.density = 1.0f;

		ContactEvent* m_userData = new ContactEvent(*this);
		floorFixtureDef2.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
		floorBody2->CreateFixture(&floorFixtureDef2);
	}

}

Roof::Roof(b2World& world)
{
	b2BodyDef roofBD;
	roofBD.position.Set(0.0f, 0.0f);
	b2Body* roofBody = world.CreateBody(&roofBD);

	b2PolygonShape roofBox;
	roofBox.SetAsBox(static_cast<float>(Properties::WINDOW_SIZE_WIDTH), 1.0f / Utility::PIXEL_METER_RATIO);


	b2FixtureDef roofFixtureDef;
	roofFixtureDef.shape = &roofBox;
	roofFixtureDef.density = 1.0f;

	ContactEvent* m_userData = new ContactEvent(*this);
	roofFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);
	roofBody->CreateFixture(&roofFixtureDef);
}
