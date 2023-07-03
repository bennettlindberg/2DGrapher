#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"
#include "Command.h"
#include <vector>

class CommandList
{
public:
	//constructor
	CommandList(const WindowData& new_win_data, const sf::Font& new_font, const std::vector<Command>& new_commands);

	//window-related methods
	void updateWindowData(const WindowData& new_data);
	void drawCommandList(sf::RenderWindow& window);

	//setters
	void setFont(const sf::Font& new_font);
	void setTitleText(const std::string& new_text);
	void setNameHeaderText(const std::string& new_text);
	void setDescriptionHeaderText(const std::string& new_text);
	
	void setCurrentSpecificity(const std::string& new_specificity);
	void replaceCommandList(const std::vector<Command>& new_commands);
	void appendToCommandList(const Command& new_command);
	void scrollCommandList(int scroll_amount);

	//getters
	sf::Font getFont();
	std::string getTitleText();
	std::string getNameHeaderText();
	std::string getDescriptionHeaderText();
	std::string getCurrentSpecificity();

private:
	//class WindowData object
	WindowData win_data;

	//data members
	sf::Font font;

	sf::RectangleShape title_box;
	sf::Text title_text;

	sf::RectangleShape header_border;
	sf::Text name_header_text;
	sf::Text description_header_text;

	sf::RectangleShape list_border;
	std::vector<sf::Text> name_list_texts;
	std::vector<sf::Text> description_list_texts;

	std::vector<Command> all_commands;
	std::vector<Command> commands_of_specificity;
	std::string current_specificity = "all";
	int starting_pos_in_commands = 0;
	int num_commands_included = 1;

	sf::Color getSpecificityAssociatedColor(std::string the_specificity);
};