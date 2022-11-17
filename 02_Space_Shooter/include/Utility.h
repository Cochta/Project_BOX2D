#pragma once

#include <random>

#include <box2d/b2_math.h>
#include <SFML/Graphics.hpp>

class Utility
{
public:
	static constexpr float PIXEL_METER_RATIO = 100.0f;

	static int getRandomInt(int min, int max) {
		std::random_device os_seed;
		uint_least32_t seed = os_seed();

		std::mt19937 generator(seed);
		std::uniform_int_distribution<uint_least32_t> distribute(min, max);

		return distribute(generator);
	}

	static float getRandomFloat(float min, float max) {
		std::random_device os_seed;
		uint_least32_t seed = os_seed();

		std::mt19937 generator(seed);
		std::uniform_int_distribution<uint_least32_t> distribute(min, max);

		return distribute(generator);
	}

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels)
	{
		return b2Vec2(pixels.x / PIXEL_METER_RATIO, 1.0f * pixels.y / PIXEL_METER_RATIO);
	}

	static b2Vec2 PixelsToMeters(sf::Vector2u pixels)
	{
		return b2Vec2(pixels.x / PIXEL_METER_RATIO, 1.0f * pixels.y / PIXEL_METER_RATIO);
	}

	static float PixelsToMeters(float pixels)
	{
		return pixels / PIXEL_METER_RATIO;
	}

	static sf::Vector2f MetersToPixels(b2Vec2 meters)
	{
		return sf::Vector2f(meters.x * PIXEL_METER_RATIO, 1.0f * meters.y * PIXEL_METER_RATIO);
	}

};