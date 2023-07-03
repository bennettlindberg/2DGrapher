#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"
#include "Function.h"
#include <vector>

class FunctionList
{
public:
	//constructor
	FunctionList(const WindowData &new_win_data, const sf::Font &new_font, const std::vector<Function> &new_functions);

	//window-related methods
	void updateWindowData(const WindowData &new_data);
	void drawFunctionList(sf::RenderWindow &window);

	//setters
	void setFont(const sf::Font &new_font);
	void setTitleText(const std::string &new_text);
	void setIDNumberHeaderText(const std::string &new_text);
	void setTypeHeaderText(const std::string &new_text);
	void setEquationHeaderText(const std::string &new_text);

	void replaceFunctionList(const std::vector<Function> &new_functions);
	void appendToFunctionList(const Function &new_function);
	void removeFromFunctionList(Function &removed_function);
	void scrollFunctionList(int scroll_amount);

	//getters
	sf::Font getFont();
	std::string getTitleText();
	std::string getIDNumberHeaderText();
	std::string getTypeHeaderText();
	std::string getEquationHeaderText();

private:
	//class WindowData object
	WindowData win_data;

	//data members
	sf::Font font;

	sf::RectangleShape title_box;
	sf::Text title_text;

	sf::RectangleShape header_border;
	sf::Text id_number_header_text;
	sf::Text type_header_text;
	sf::Text equation_header_text;

	sf::RectangleShape list_border;
	std::vector<sf::Text> id_number_list_texts;
	std::vector<sf::Text> type_list_texts;
	std::vector<sf::Text> equation_list_texts;

	std::vector<Function> functions;
	int starting_pos_in_functions = 0;
	int num_functions_included = 1;
};