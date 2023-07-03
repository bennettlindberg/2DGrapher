#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"
#include "FunctionPane.h"
#include <vector>

class GraphElements
{
public:
	//constructors
	GraphElements(const WindowData& new_win_data, const sf::Font& new_font);

	//window-related methods
	void updateWindowData(const WindowData& new_data);
	void drawGraphElements(sf::RenderWindow& window);

	//setters
	void setTicksDrawability(bool new_drawability);
	void setTicksColor(sf::Color new_color);

	void setTickLabelsDrawability(bool new_drawability);
	void setTickLabelsColor(sf::Color new_color);

	void setGraphLinesDrawability(bool new_drawability);
	void setGraphLinesColor(sf::Color new_color);

	//getters
	bool getTicksDrawability();
	bool getTickLabelsDrawability();
	bool getGraphLinesDrawability();

private:
	//class WindowData object
	WindowData win_data;

	//data members
	sf::Font font;

	bool ticks_drawable = true;
	sf::Color ticks_color = sf::Color::Cyan;
	std::vector<sf::RectangleShape> x_axis_ticks;
	std::vector<sf::RectangleShape> y_axis_ticks;

	bool tick_labels_drawable = true;
	sf::Color tick_labels_color = sf::Color::Magenta;
	std::vector<sf::Text> x_axis_tick_labels;
	std::vector<sf::Text> y_axis_tick_labels;

	bool graph_lines_drawable = true;
	sf::Color graph_lines_color = sf::Color(66, 66, 66);
	std::vector<sf::RectangleShape> x_graph_lines;
	std::vector<sf::RectangleShape> y_graph_lines;

	std::vector<sf::RectangleShape> border_concealer;

	double pixel_tick_half_width = 10;
};