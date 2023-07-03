#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"

class UserInput
{
public:
	//constructors
	UserInput(const WindowData &new_win_data, const sf::Font &new_font);

	//window-related methods
	void updateWindowData(const WindowData &new_data);
	void drawUserInput(sf::RenderWindow &window);

	//setters
	void setFont(const sf::Font &new_font);
	void setTitleText(const std::string &new_text);
	void setUserInputText(const std::string &new_text);
	void setDefaultInputText(const std::string& new_default_text);

	void appendToUserInputText(const std::string &append_text);
	void removePreviousUserInputText();
	void resetUserInputText();

	//getters
	sf::Font getFont();
	std::string getTitleText();
	std::string getUserInputText();
	std::string getDefaultInputText();
	sf::Text& getUserInputTextRef();

	std::string findCurrentUserInputSpecificity();

private:
	//class WindowData object
	WindowData win_data;

	//data members
	sf::Font font;

	sf::RectangleShape title_box;
	sf::Text title_text;

	sf::RectangleShape user_input_box;
	sf::Text user_input_text;
	std::string default_input_text = "Click \"ctrl\" to enter a command...";
};