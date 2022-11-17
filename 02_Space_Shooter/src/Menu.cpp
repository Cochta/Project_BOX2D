#include "Menu.h"

Menu::Menu()
{
	std::fstream f;
	f.open("data/HighScore.txt");
	int ch;
	while (true) {
		f >> ch;
		if (f.eof())
			break;
	}
	f.close();
	_highScore = ch;
}

void Menu::Main()
{
	_elements.clear();
	_texts.clear();
	sf::RectangleShape play;
	play.setSize(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() / 6));
	play.setFillColor(sf::Color::Black);
	play.setOrigin(play.getSize() * 0.5f);
	play.setPosition(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() / 6));
	play.setOutlineThickness(4.0f);
	play.setOutlineColor(sf::Color::White);

	sf::Text playText;
	playText.setColor(sf::Color::White);
	playText.setFont(Properties::Instance()->GetMainFont());
	playText.setCharacterSize(Properties::FONT_SIZE);
	playText.setString("Press Enter to start a new game !");
	playText.setOrigin(playText.getGlobalBounds().width / 2, playText.getGlobalBounds().height / 2);
	playText.setPosition(play.getPosition());
	_elements.emplace_back(play);
	_texts.emplace_back(playText);

	sf::RectangleShape rules = play;
	rules.setPosition(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() - Properties::Instance()->GetScreenHeight() / 2));

	sf::Text ruleText = playText;
	ruleText.setColor(sf::Color::White);
	ruleText.setString("Press R for rules !");
	ruleText.setOrigin(ruleText.getGlobalBounds().width / 2, ruleText.getGlobalBounds().height / 2);
	ruleText.setPosition(rules.getPosition());
	_elements.emplace_back(rules);
	_texts.emplace_back(ruleText);

	sf::RectangleShape quit = play;
	quit.setPosition(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() - Properties::Instance()->GetScreenHeight() / 6));

	sf::Text quitText = playText;
	quitText.setColor(sf::Color::White);
	quitText.setString("Press Esc to quit !");
	quitText.setOrigin(quitText.getGlobalBounds().width / 2, quitText.getGlobalBounds().height / 2);
	quitText.setPosition(quit.getPosition());
	_elements.emplace_back(quit);
	_texts.emplace_back(quitText);
}

void Menu::InGame(int player_HP, int score, int planet_HP)
{
	_elements.clear();
	_texts.clear();
	sf::RectangleShape stats;
	stats.setSize(sf::Vector2f(Properties::Instance()->GetScreenWidth(), Properties::Instance()->GetScreenHeight() / 16));
	stats.setFillColor(sf::Color::Black);
	stats.setOrigin(stats.getSize() * 0.5f);
	stats.setPosition(sf::Vector2f(stats.getSize() * 0.5f));
	stats.setOutlineThickness(4.0f);
	stats.setOutlineColor(sf::Color::White);

	sf::Text healthText;
	healthText.setColor(sf::Color::White);
	healthText.setFont(Properties::Instance()->GetMainFont());
	healthText.setCharacterSize(Properties::FONT_SIZE);
	healthText.setString("SCORE: " + std::format("{:_>6}", score) +
		"	Player HP: " + std::format("{: ^3}", player_HP) +
		"	Planet HP: " + std::format("{: ^3}", planet_HP));
	healthText.setColor(sf::Color::White);
	healthText.setOrigin(healthText.getGlobalBounds().width / 2, healthText.getGlobalBounds().height / 2);
	healthText.setPosition(stats.getPosition());
	_elements.emplace_back(stats);
	_texts.emplace_back(healthText);
}

void Menu::GameOver(int score)
{
	if (score > _highScore)
	{
		_highScore = score;
		std::fstream f;
		f.open("data/HighScore.txt");
		f.clear();
		f << _highScore;
	}

	_elements.clear();
	_texts.clear();
	sf::RectangleShape end;
	end.setSize(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() / 1.5));
	end.setFillColor(sf::Color::Black);
	end.setOrigin(end.getSize() * 0.5f);
	end.setPosition(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() / 2));
	end.setOutlineThickness(4.0f);
	end.setOutlineColor(sf::Color::White);

	sf::Text endText;
	endText.setColor(sf::Color::White);
	endText.setFont(Properties::Instance()->GetMainFont());
	endText.setCharacterSize(Properties::FONT_SIZE);
	endText.setString("GAME OVER\n\n\n\n\nyour score : " + std::to_string(score) + "\nHIGH SCORE: "
		+ std::to_string(_highScore) + "\n\n\n\n\nPress B to go back to main menu!");
	endText.setOrigin(endText.getGlobalBounds().width / 2, endText.getGlobalBounds().height / 2);
	endText.setPosition(end.getPosition());
	_elements.emplace_back(end);
	_texts.emplace_back(endText);
}

void Menu::Rules()
{
	_elements.clear();
	_texts.clear();
	sf::RectangleShape rules;
	rules.setSize(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 1.5, Properties::Instance()->GetScreenHeight() / 1.5));
	rules.setFillColor(sf::Color::Black);
	rules.setOrigin(rules.getSize() * 0.5f);
	rules.setPosition(sf::Vector2f(Properties::Instance()->GetScreenWidth() / 2, Properties::Instance()->GetScreenHeight() / 2));
	rules.setOutlineThickness(4.0f);
	rules.setOutlineColor(sf::Color::White);

	sf::Text ruleText;
	ruleText.setColor(sf::Color::White);
	ruleText.setFont(Properties::Instance()->GetMainFont());
	ruleText.setCharacterSize(Properties::FONT_SIZE);
	ruleText.setString("!!! THE EARTH IS ATTACKED !!!\n\nProtect it using WASD or ARROWS to move and SPACE to shoot"
		"\n\nYou start with 3 lives.\nThe planet starts with 5 lives.\nWhen an asteroid touches the ship, you lose 1 life.\n"
		"When an asteroid touches the planet, it loses 1 life.\n\nTry Making à High Score!\n\n"
		"GOOD LUCK\n\n\nPress M to return to menu");
	ruleText.setOrigin(ruleText.getGlobalBounds().width / 2, ruleText.getGlobalBounds().height / 2);
	ruleText.setPosition(rules.getPosition());
	_elements.emplace_back(rules);
	_texts.emplace_back(ruleText);
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
