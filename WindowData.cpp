#include "WindowData.h"

//constructor
WindowData::WindowData(const sf::RenderWindow &window)
{
	//window
	window_size = window.getSize();

	//graph
	int graph_x_dimension = (window_size.x / 2) * 0.8;
	int graph_y_dimension = window_size.y * 0.8;
	graph_size = sf::Vector2u(graph_x_dimension, graph_y_dimension);

	int graph_x_origin = (window_size.x / 2) * 1.1;
	int graph_y_origin = window_size.y * 0.1;
	graph_origin = sf::Vector2u(graph_x_origin, graph_y_origin);

	x_true_to_pixel_ratio = (true_x_range[1] - true_x_range[0]) / graph_size.x;
	y_true_to_pixel_ratio = (true_y_range[1] - true_y_range[0]) / graph_size.y;

	graph_y_pixel_middle = (graph_size.y / 2) + graph_origin.y;
	graph_x_pixel_middle = (graph_size.x / 2) + graph_origin.x;
	graph_y_true_middle = (true_y_range[0] + true_y_range[1]) / 2.0;
	graph_x_true_middle = (true_x_range[0] + true_x_range[1]) / 2.0;

	//GUI structure
	const int left_x_cord = (window_size.x / 2.0) * 0.1;
	const int total_x_width = (window_size.x / 2.0) * 0.9;

	user_input_size = sf::Vector2u(total_x_width, 60);
	user_input_origin = sf::Vector2u(left_x_cord, window_size.y * 0.1);

	const int y_gap = (graph_size.y - user_input_size.y) * 0.05;
	const int y_list_size = (graph_size.y - user_input_size.y) * 0.45;

	command_list_size = sf::Vector2u(total_x_width, y_list_size);
	command_list_origin = sf::Vector2u(left_x_cord, user_input_origin.y + user_input_size.y + y_gap);

	function_list_size = sf::Vector2u(total_x_width, y_list_size);
	function_list_origin = sf::Vector2u(left_x_cord, command_list_origin.y + command_list_size.y + y_gap);
}

//conversion functions
double WindowData::y_pixelToTrue(int y_pixel)
{
	return graph_y_true_middle + (-(y_pixel - graph_y_pixel_middle) * y_true_to_pixel_ratio);
}

double WindowData::x_pixelToTrue(int x_pixel)
{
	return graph_x_true_middle + ((x_pixel - graph_x_pixel_middle) * x_true_to_pixel_ratio);
}

int WindowData::y_trueToPixel(double y_true)
{
	return graph_y_pixel_middle - ((y_true - graph_y_true_middle) / y_true_to_pixel_ratio);
}

int WindowData::x_trueToPixel(double x_true)
{
	return graph_x_pixel_middle + ((x_true - graph_x_true_middle) / x_true_to_pixel_ratio);
}

//setters
void WindowData::setWindowSize(const sf::Vector2u &dimensions)
{
	window_size = dimensions;
}

void WindowData::setGraphSize(const sf::Vector2u &dimensions)
{
	graph_size = dimensions;
}

void WindowData::setGraphOrigin(const sf::Vector2u &coords)
{
	graph_origin = coords;
}

void WindowData::setTrueXRange(double min, double max)
{
	true_x_range[0] = min;
	true_x_range[1] = max;

	x_true_to_pixel_ratio = (true_x_range[1] - true_x_range[0]) / graph_size.x;

	graph_x_true_middle = (true_x_range[0] + true_x_range[1]) / 2.0;
}

void WindowData::setTrueYRange(double min, double max)
{
	true_y_range[0] = min;
	true_y_range[1] = max;

	y_true_to_pixel_ratio = (true_y_range[1] - true_y_range[0]) / graph_size.y;

	graph_y_true_middle = (true_y_range[0] + true_y_range[1]) / 2.0;
}

void WindowData::setUserInputSize(const sf::Vector2u &dimensions)
{
	user_input_size = dimensions;
}

void WindowData::setUserInputOrigin(const sf::Vector2u &coords)
{
	user_input_origin = coords;
}

void WindowData::setCommandListSize(const sf::Vector2u &dimensions)
{
	command_list_size = dimensions;
}

void WindowData::setCommandListOrigin(const sf::Vector2u &coords)
{
	command_list_origin = coords;
}

void WindowData::setFunctionListSize(const sf::Vector2u &dimensions)
{
	function_list_size = dimensions;
}

void WindowData::setFunctionListOrigin(const sf::Vector2u &coords)
{
	function_list_origin = coords;
}

void WindowData::updateResizedWindow(const sf::RenderWindow& window)
{
	//RECONSTRUCT window using new overall window sizes

	//window
	window_size = window.getSize();

	//graph
	int graph_x_dimension = (window_size.x / 2) * 0.8;
	int graph_y_dimension = window_size.y * 0.8;
	graph_size = sf::Vector2u(graph_x_dimension, graph_y_dimension);

	int graph_x_origin = (window_size.x / 2) * 1.1;
	int graph_y_origin = window_size.y * 0.1;
	graph_origin = sf::Vector2u(graph_x_origin, graph_y_origin);

	x_true_to_pixel_ratio = (std::abs(true_x_range[0]) + std::abs(true_x_range[1])) / graph_size.x;
	y_true_to_pixel_ratio = (std::abs(true_y_range[0]) + std::abs(true_y_range[1])) / graph_size.y;

	graph_y_pixel_middle = (graph_size.y / 2) + graph_origin.y;
	graph_x_pixel_middle = (graph_size.x / 2) + graph_origin.x;
	graph_y_true_middle = (true_y_range[0] + true_y_range[1]) / 2.0;
	graph_x_true_middle = (true_x_range[0] + true_x_range[1]) / 2.0;

	//GUI structure
	const int left_x_cord = (window_size.x / 2.0) * 0.1;
	const int total_x_width = (window_size.x / 2.0) * 0.9;

	user_input_size = sf::Vector2u(total_x_width, 60);
	user_input_origin = sf::Vector2u(left_x_cord, window_size.y * 0.1);

	const int y_gap = (graph_size.y - user_input_size.y) * 0.05;
	const int y_list_size = (graph_size.y - user_input_size.y) * 0.45;

	command_list_size = sf::Vector2u(total_x_width, y_list_size);
	command_list_origin = sf::Vector2u(left_x_cord, user_input_origin.y + user_input_size.y + y_gap);

	function_list_size = sf::Vector2u(total_x_width, y_list_size);
	function_list_origin = sf::Vector2u(left_x_cord, command_list_origin.y + command_list_size.y + y_gap);
}

//getters
sf::Vector2u WindowData::getWindowSize()
{
	return window_size;
}

sf::Vector2u WindowData::getGraphSize()
{
	return graph_size;
}

sf::Vector2u WindowData::getGraphOrigin()
{
	return graph_origin;
}

double* WindowData::getTrueXRange()
{
	return true_x_range;
}

double* WindowData::getTrueYRange()
{
	return true_y_range;
}

sf::Vector2u WindowData::getUserInputSize()
{
	return user_input_size;
}

sf::Vector2u WindowData::getUserInputOrigin()
{
	return user_input_origin;
}

sf::Vector2u WindowData::getCommandListSize()
{
	return command_list_size;
}

sf::Vector2u WindowData::getCommandListOrigin()
{
	return command_list_origin;
}

sf::Vector2u WindowData::getFunctionListSize()
{
	return function_list_size;
}

sf::Vector2u WindowData::getFunctionListOrigin()
{
	return function_list_origin;
}

double WindowData::getXTrueToPixelRatio()
{
	return x_true_to_pixel_ratio;
}

double WindowData::getYTrueToPixelRatio()
{
	return y_true_to_pixel_ratio;
}

//default graph scale
const double WindowData::default_true_x_range[2] = { -50, 50 };
const double WindowData::default_true_y_range[2] = { -50, 50 };