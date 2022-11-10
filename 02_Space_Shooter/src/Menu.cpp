#include "Menu.h"

Menu::Menu()
{

}

void Menu::Main()
{
	_elements.clear();
	_texts.clear();
	sf::RectangleShape play;
	play.setSize(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH / 2, Properties::WINDOW_SIZE_HEIGHT / 6));
	play.setFillColor(sf::Color::Cyan);
	play.setOrigin(play.getSize() * 0.5f);
	play.setPosition(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH / 2, Properties::WINDOW_SIZE_HEIGHT / 6));
	play.setOutlineThickness(4.0f);
	play.setOutlineColor(sf::Color::Blue);
	sf::Text playText;

	playText.setFont(Properties::Instance()->GetMainFont());
	playText.setCharacterSize(Properties::FONT_SIZE);
	playText.setString("Press Enter to start a new game !");
	playText.setColor(sf::Color::Black);
	playText.setOrigin(playText.getGlobalBounds().width / 2, playText.getGlobalBounds().height / 2);
	playText.setPosition(play.getPosition());
	_elements.emplace_back(play);
	_texts.emplace_back(playText);

	sf::RectangleShape quit = play;
	quit.setPosition(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH / 2, Properties::WINDOW_SIZE_HEIGHT - Properties::WINDOW_SIZE_HEIGHT / 6));

	sf::Text quitText = playText;

	quitText.setString("Press Esc to quit !");
	quitText.setOrigin(quitText.getGlobalBounds().width / 2, quitText.getGlobalBounds().height / 2);
	quitText.setPosition(quit.getPosition());
	_elements.emplace_back(quit);
	_texts.emplace_back(quitText);
}

void Menu::InGame(int HP)
{
	_elements.clear();
	_texts.clear();
	sf::RectangleShape stats;
	stats.setSize(sf::Vector2f(Properties::WINDOW_SIZE_WIDTH, Properties::WINDOW_SIZE_HEIGHT / 16));
	stats.setFillColor(sf::Color::Cyan);
	stats.setOrigin(stats.getSize() * 0.5f);
	stats.setPosition(sf::Vector2f(stats.getSize() * 0.5f));
	stats.setOutlineThickness(4.0f);
	stats.setOutlineColor(sf::Color::Blue);
	sf::Text healthText;

	healthText.setFont(Properties::Instance()->GetMainFont());
	healthText.setCharacterSize(Properties::FONT_SIZE);
	healthText.setString("Lives: "+ std::to_string(HP));
	healthText.setColor(sf::Color::Black);
	healthText.setOrigin(healthText.getGlobalBounds().width / 2, healthText.getGlobalBounds().height / 2);
	healthText.setPosition(stats.getPosition());
	_elements.emplace_back(stats);
	_texts.emplace_back(healthText);
}

void Menu::Lost()
{
}

void Menu::Win()
{
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& element : _elements)
	{
		target.draw(element);
	}
	for (const auto& text : _texts)
	{
		target.draw(text);
	}
}
