#pragma once

#include <SFML/Graphics.hpp>

class WindowData
{
public:
	//constructor
	WindowData(const sf::RenderWindow &window);

	//conversion functions
	double y_pixelToTrue(int y_pixel);
	double x_pixelToTrue(int x_pixel);
	int y_trueToPixel(double y_true);
	int x_trueToPixel(double x_true);

	//window resizing methods
	void updateResizedWindow(const sf::RenderWindow &window);

	//setters
	void setWindowSize(const sf::Vector2u &dimensions);

	void setGraphSize(const sf::Vector2u &dimensions);
	void setGraphOrigin(const sf::Vector2u &coords);

	void setTrueXRange(double min, double max);
	void setTrueYRange(double min, double max);

	void setUserInputSize(const sf::Vector2u &dimensions);
	void setUserInputOrigin(const sf::Vector2u &coords);

	void setCommandListSize(const sf::Vector2u &dimensions);
	void setCommandListOrigin(const sf::Vector2u &coords);

	void setFunctionListSize(const sf::Vector2u &dimensions);
	void setFunctionListOrigin(const sf::Vector2u &coords);

	//getters
	sf::Vector2u getWindowSize();

	sf::Vector2u getGraphSize();
	sf::Vector2u getGraphOrigin();

	double* getTrueXRange();
	double* getTrueYRange();

	sf::Vector2u getUserInputSize();
	sf::Vector2u getUserInputOrigin();

	sf::Vector2u getCommandListSize();
	sf::Vector2u getCommandListOrigin();

	sf::Vector2u getFunctionListSize();
	sf::Vector2u getFunctionListOrigin();

	double getXTrueToPixelRatio();
	double getYTrueToPixelRatio();

	//default graph scale
	static const double default_true_x_range[2];
	static const double default_true_y_range[2];

private:
	//data members
	sf::Vector2u window_size;

	sf::Vector2u graph_size;
	sf::Vector2u graph_origin; //origin refers to the pixel in the upper left corner

	double true_x_range[2] = { -50, 50 };
	double true_y_range[2] = { -50, 50 };

	double x_true_to_pixel_ratio;
	double y_true_to_pixel_ratio;

	int graph_y_pixel_middle;
	int graph_x_pixel_middle;
	double graph_y_true_middle;
	double graph_x_true_middle;

	sf::Vector2u user_input_size;
	sf::Vector2u user_input_origin;

	sf::Vector2u command_list_size;
	sf::Vector2u command_list_origin;

	sf::Vector2u function_list_size;
	sf::Vector2u function_list_origin;
};