#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"
#include "Function.h"
#include <vector>

class FunctionPane
{
public:
	//constructor
	FunctionPane(const WindowData& new_win_data, const sf::Font& new_font, const std::vector<Function>& new_functions);

	//window-related methods
	void updateWindowData(const WindowData& new_data);
	void drawFunctionPane(sf::RenderWindow& window);

	//setters
	void setActiveFunctionID(int new_id);

	//getters
	int getActiveFunctionID();
private:
	//class WindowData object
	WindowData win_data;

	//data members
	sf::Font font;

	std::vector<Function> functions;

	sf::RectangleShape graph_concealer;
	sf::RectangleShape border_line;

	sf::Text header;

	std::vector<sf::Text> traits; //e.g., equation, color, title
	std::vector<sf::Text> values; //e.g., x^2, red, f1(x)

	int active_function_id = 0; //if 0, no pane will be drawn (inactive pane)
};