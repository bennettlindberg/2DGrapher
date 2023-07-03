#include "UserInput.h"

//constructor
UserInput::UserInput(const WindowData &new_win_data, const sf::Font &new_font) : win_data(new_win_data), font(new_font)
{
	title_text.setFillColor(sf::Color::Black);
	title_text.setCharacterSize(24);
	title_text.setFont(font);
	title_text.setStyle(sf::Text::Bold);
	title_text.setPosition(sf::Vector2f(win_data.getUserInputOrigin().x + 6, win_data.getUserInputOrigin().y - 1));
	title_text.setString("Input Field");

	title_box.setFillColor(sf::Color::White);
	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getUserInputOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	user_input_text.setFillColor(sf::Color::Magenta);
	user_input_text.setCharacterSize(24);
	user_input_text.setFont(font);
	user_input_text.setStyle(sf::Text::Regular);
	user_input_text.setPosition(sf::Vector2f(win_data.getUserInputOrigin().x + 6, win_data.getUserInputOrigin().y + 30));
	user_input_text.setString(default_input_text);

	user_input_box.setFillColor(sf::Color::Transparent);
	user_input_box.setOutlineColor(sf::Color::White);
	user_input_box.setOutlineThickness(3);
	user_input_box.setPosition(win_data.getUserInputOrigin().x, win_data.getUserInputOrigin().y + 30);
	user_input_box.setSize(sf::Vector2f(win_data.getUserInputSize().x, 30));
}

//window-related methods
void UserInput::updateWindowData(const WindowData &new_data)
{
	win_data = new_data;
	
	//update sizes and positions in relation to new window data
	title_text.setPosition(sf::Vector2f(win_data.getUserInputOrigin().x + 6, win_data.getUserInputOrigin().y - 1));

	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getUserInputOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	user_input_text.setPosition(sf::Vector2f(win_data.getUserInputOrigin().x + 6, win_data.getUserInputOrigin().y + 30));

	user_input_box.setPosition(win_data.getUserInputOrigin().x, win_data.getUserInputOrigin().y + 30);
	user_input_box.setSize(sf::Vector2f(win_data.getUserInputSize().x, 30));
}

void UserInput::drawUserInput(sf::RenderWindow& window)
{
	window.draw(title_box);
	window.draw(title_text);

	window.draw(user_input_box);
	window.draw(user_input_text);
}

//setters
void UserInput::setFont(const sf::Font& new_font)
{
	font = new_font;
}

void UserInput::setTitleText(const std::string& new_text)
{
	title_text.setString(new_text);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));
}

void UserInput::setUserInputText(const std::string& new_text)
{
	user_input_text.setString(new_text);
}

void UserInput::setDefaultInputText(const std::string& new_default_text)
{
	default_input_text = new_default_text;
}

void UserInput::appendToUserInputText(const std::string& append_text)
{
	if (user_input_text.getString() == default_input_text)
	{
		user_input_text.setString(append_text);
	}
	else
	{
		user_input_text.setString(user_input_text.getString() + append_text);
	}
}

void UserInput::removePreviousUserInputText()
{
	if (user_input_text.getString() == default_input_text)
	{
		; //null statement -- do nothing
	}
	else if (user_input_text.getString().getSize() >= 4
		&& user_input_text.getString().toAnsiString()[user_input_text.getString().getSize() - 4] == 'c'
		&& user_input_text.getString().toAnsiString()[user_input_text.getString().getSize() - 3] == 't'
		&& user_input_text.getString().toAnsiString()[user_input_text.getString().getSize() - 2] == 'r'
		&& user_input_text.getString().toAnsiString()[user_input_text.getString().getSize() - 1] == 'l')
	{
		user_input_text.setString(user_input_text.getString().substring(0, user_input_text.getString().getSize() - 4));
	}
	else
	{
		user_input_text.setString(user_input_text.getString().substring(0, user_input_text.getString().getSize() - 1));
	}

	if (user_input_text.getString().getSize() == 0)
	{
		user_input_text.setString(default_input_text);
	}
}

void UserInput::resetUserInputText()
{
	user_input_text.setString(default_input_text);
}

//getters
sf::Font UserInput::getFont()
{
	return font;
}

std::string UserInput::getTitleText()
{
	return title_text.getString().toAnsiString();
}

std::string UserInput::getUserInputText()
{
	return user_input_text.getString().toAnsiString();
}

std::string UserInput::getDefaultInputText()
{
	return default_input_text;
}

sf::Text& UserInput::getUserInputTextRef()
{
	return user_input_text;
}

std::string UserInput::findCurrentUserInputSpecificity()
{
	if (user_input_text.getString().substring(0, 4) == "ctrl")
	{
		if (user_input_text.getString().substring(4, 1) == "G")
		{
			return "graph";
		}
		else if (user_input_text.getString().substring(4, 1) == "F")
		{
			char possible_num = user_input_text.getString().substring(5, 1).toAnsiString()[0];
			if (isdigit(possible_num))
			{
				return "specific_function";
			}
			else
			{
				return "function";
			}
		}
		else
		{
			return "general";
		}
	}
	else
	{
		return "general";
	}
}