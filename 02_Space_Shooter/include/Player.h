#pragma once

#include "Properties.h"
#include "Utility.h"

#include "Laser.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/box2d.h>

#include <list>
class Player : public sf::Drawable
{
public:
	Player();

	void Init(b2World& world);

	void Move(float time);

	void Fire(b2World& world);
	void TakeDMG() { _HP -= 1; }
	int GetHP() { return _HP; }

	void AddScore(int scoreToAdd) { _score += scoreToAdd; }
	int GetScore() { return _score; }

	b2Body* GetBody() { return _body; }

	void Update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void SetDirection(b2Vec2 direction) { _direction = direction; }
	void SetDirectionX(float x) { _direction.x = x; }
	void SetDirectionY(float y) { _direction.y = y; }
	void SetDumping(float damping) { _body->SetLinearDamping(damping); }
	sf::Time time;


private:
	b2Body* _body;
	sf::Sprite _shape;
	b2Vec2 _direction;
	std::list<Laser> _lasers;
	sf::Sound _piou;
	sf::Clock _clock;

	int _HP = 3;
	int _score = 0;
};