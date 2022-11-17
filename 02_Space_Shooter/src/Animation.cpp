#include "Animation.h"

Animation::Animation(AnimType type)
{
	if (type == AnimType::Explosion)
	{
		Explosion();
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape);
}

void Animation::Explosion()
{
}
