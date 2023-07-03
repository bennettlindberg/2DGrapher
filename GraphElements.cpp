#include "GraphElements.h"
#include <cmath>
#include <sstream>
#include <iomanip>

GraphElements::GraphElements(const WindowData& new_win_data, const sf::Font& new_font) : win_data(new_win_data), font(new_font)
{
	//border concealer
	sf::RectangleShape temp_border_left;
	temp_border_left.setFillColor(sf::Color::Black);
	temp_border_left.setPosition(win_data.getWindowSize().x / 2, 0);
	temp_border_left.setSize(sf::Vector2f(win_data.getWindowSize().x * 0.05, win_data.getWindowSize().y));
	border_concealer.push_back(temp_border_left);

	sf::RectangleShape temp_border_right;
	temp_border_right.setFillColor(sf::Color::Black);
	temp_border_right.setPosition(win_data.getWindowSize().x - win_data.getWindowSize().x * 0.05, 0);
	temp_border_right.setSize(sf::Vector2f(win_data.getWindowSize().x * 0.05, win_data.getWindowSize().y));
	border_concealer.push_back(temp_border_right);

	sf::RectangleShape temp_border_top;
	temp_border_top.setFillColor(sf::Color::Black);
	temp_border_top.setPosition(win_data.getWindowSize().x / 2, 0);
	temp_border_top.setSize(sf::Vector2f(win_data.getWindowSize().x / 2, win_data.getWindowSize().y * 0.1));
	border_concealer.push_back(temp_border_top);

	sf::RectangleShape temp_border_bottom;
	temp_border_bottom.setFillColor(sf::Color::Black);
	temp_border_bottom.setPosition(win_data.getWindowSize().x / 2, win_data.getWindowSize().y - win_data.getWindowSize().y * 0.1);
	temp_border_bottom.setSize(sf::Vector2f(win_data.getWindowSize().x / 2, win_data.getWindowSize().y * 0.1));
	border_concealer.push_back(temp_border_bottom);

	//graph itself
	double x_true_tick_spacing = (win_data.getTrueXRange()[1] - win_data.getTrueXRange()[0]) / 10.0;
	double y_true_tick_spacing = (win_data.getTrueYRange()[1] - win_data.getTrueYRange()[0]) / 10.0;

	//x elements
	for (int i = win_data.getTrueXRange()[0] / x_true_tick_spacing; i * x_true_tick_spacing < win_data.getTrueXRange()[1]; ++i)
	{
		if (std::abs(win_data.x_trueToPixel(i * x_true_tick_spacing) - win_data.x_trueToPixel(0)) > 5)
		{
			int x_pixel_loc = win_data.x_trueToPixel(i * x_true_tick_spacing);

			//always create graph lines (except for when near axis)
			sf::RectangleShape temp_graph_line;
			temp_graph_line.setFillColor(graph_lines_color);
			temp_graph_line.setPosition(x_pixel_loc, win_data.getGraphOrigin().y);
			temp_graph_line.setSize(sf::Vector2f(1, win_data.getGraphSize().y));
			x_graph_lines.push_back(temp_graph_line);

			//only create ticks and labels if the x-axis ticks can be seen
			int upper_bound_tick = win_data.y_trueToPixel(0) + pixel_tick_half_width;
			int lower_bound_tick = win_data.y_trueToPixel(0) - pixel_tick_half_width;
			if ((upper_bound_tick >= win_data.getGraphOrigin().y && upper_bound_tick < win_data.getGraphOrigin().y + win_data.getGraphSize().y) ||
				(lower_bound_tick >= win_data.getGraphOrigin().y && lower_bound_tick < win_data.getGraphOrigin().y + win_data.getGraphSize().y))
			{
				if (upper_bound_tick >= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
				{
					upper_bound_tick = win_data.getGraphOrigin().y + win_data.getGraphSize().y - 1;
				}
				if (lower_bound_tick < win_data.getGraphOrigin().y)
				{
					lower_bound_tick = win_data.getGraphOrigin().y;
				}
				sf::RectangleShape temp_tick;
				temp_tick.setFillColor(ticks_color);
				temp_tick.setPosition(x_pixel_loc, lower_bound_tick);
				temp_tick.setSize(sf::Vector2f(1, upper_bound_tick - lower_bound_tick));
				x_axis_ticks.push_back(temp_tick);

				sf::Text temp_tick_label;
				temp_tick_label.setFillColor(tick_labels_color);
				temp_tick_label.setCharacterSize(20);
				temp_tick_label.setFont(font);
				temp_tick_label.setStyle(sf::Text::Bold);
				std::ostringstream stream;
				stream << std::setprecision(4);
				stream << i * x_true_tick_spacing;
				temp_tick_label.setString(stream.str());
				temp_tick_label.setPosition(x_pixel_loc - temp_tick_label.getGlobalBounds().width / 2, win_data.y_trueToPixel(0) - pixel_tick_half_width - 23);
				x_axis_tick_labels.push_back(temp_tick_label);
			}
		}
	}

	//y elements
	for (int i = win_data.getTrueYRange()[0] / y_true_tick_spacing; i * y_true_tick_spacing < win_data.getTrueYRange()[1]; ++i)
	{
		if (std::abs(win_data.y_trueToPixel(i * y_true_tick_spacing) - win_data.y_trueToPixel(0)) > 5)
		{
			int y_pixel_loc = win_data.y_trueToPixel(i * y_true_tick_spacing);

			//always create graph lines (except for when near axis)
			sf::RectangleShape temp_graph_line;
			temp_graph_line.setFillColor(graph_lines_color);
			temp_graph_line.setPosition(win_data.getGraphOrigin().x, y_pixel_loc);
			temp_graph_line.setSize(sf::Vector2f(win_data.getGraphSize().x, 1));
			y_graph_lines.push_back(temp_graph_line);

			//only create ticks and labels if the x-axis ticks can be seen
			int upper_bound_tick = win_data.x_trueToPixel(0) + pixel_tick_half_width;
			int lower_bound_tick = win_data.x_trueToPixel(0) - pixel_tick_half_width;
			if ((upper_bound_tick >= win_data.getGraphOrigin().x && upper_bound_tick < win_data.getGraphOrigin().x + win_data.getGraphSize().x) ||
				(lower_bound_tick >= win_data.getGraphOrigin().x && lower_bound_tick < win_data.getGraphOrigin().x + win_data.getGraphSize().x))
			{
				if (upper_bound_tick >= win_data.getGraphOrigin().x + win_data.getGraphSize().x)
				{
					upper_bound_tick = win_data.getGraphOrigin().x + win_data.getGraphSize().x - 1;
				}
				if (lower_bound_tick < win_data.getGraphOrigin().x)
				{
					lower_bound_tick = win_data.getGraphOrigin().x;
				}
				sf::RectangleShape temp_tick;
				temp_tick.setFillColor(ticks_color);
				temp_tick.setPosition(lower_bound_tick, y_pixel_loc);
				temp_tick.setSize(sf::Vector2f(upper_bound_tick - lower_bound_tick, 1));
				y_axis_ticks.push_back(temp_tick);

				sf::Text temp_tick_label;
				temp_tick_label.setFillColor(tick_labels_color);
				temp_tick_label.setCharacterSize(20);
				temp_tick_label.setFont(font);
				temp_tick_label.setStyle(sf::Text::Bold);
				std::ostringstream stream;
				stream << std::setprecision(4);
				stream << i * y_true_tick_spacing;
				temp_tick_label.setString(stream.str());
				temp_tick_label.setPosition(win_data.x_trueToPixel(0) + pixel_tick_half_width + 3, y_pixel_loc - 13);
				y_axis_tick_labels.push_back(temp_tick_label);
			}
		}
	}
}

void GraphElements::updateWindowData(const WindowData& new_data)
{
	win_data = new_data;

	x_axis_ticks.clear();
	y_axis_ticks.clear();
	x_axis_tick_labels.clear();
	y_axis_tick_labels.clear();
	x_graph_lines.clear();
	y_graph_lines.clear();
	border_concealer.clear();

	//border concealer
	sf::RectangleShape temp_border_left;
	temp_border_left.setFillColor(sf::Color::Black);
	temp_border_left.setPosition(win_data.getWindowSize().x / 2, 0);
	temp_border_left.setSize(sf::Vector2f(win_data.getWindowSize().x * 0.05, win_data.getWindowSize().y));
	border_concealer.push_back(temp_border_left);

	sf::RectangleShape temp_border_right;
	temp_border_right.setFillColor(sf::Color::Black);
	temp_border_right.setPosition(win_data.getWindowSize().x - win_data.getWindowSize().x * 0.05, 0);
	temp_border_right.setSize(sf::Vector2f(win_data.getWindowSize().x * 0.05, win_data.getWindowSize().y));
	border_concealer.push_back(temp_border_right);

	sf::RectangleShape temp_border_top;
	temp_border_top.setFillColor(sf::Color::Black);
	temp_border_top.setPosition(win_data.getWindowSize().x / 2, 0);
	temp_border_top.setSize(sf::Vector2f(win_data.getWindowSize().x / 2, win_data.getWindowSize().y * 0.1));
	border_concealer.push_back(temp_border_top);

	sf::RectangleShape temp_border_bottom;
	temp_border_bottom.setFillColor(sf::Color::Black);
	temp_border_bottom.setPosition(win_data.getWindowSize().x / 2, win_data.getWindowSize().y - win_data.getWindowSize().y * 0.1);
	temp_border_bottom.setSize(sf::Vector2f(win_data.getWindowSize().x / 2, win_data.getWindowSize().y * 0.1));
	border_concealer.push_back(temp_border_bottom);
	
	//Update all ticks, labels, and graph lines using new win_data
	double x_true_tick_spacing = (win_data.getTrueXRange()[1] - win_data.getTrueXRange()[0]) / 10.0;
	double y_true_tick_spacing = (win_data.getTrueYRange()[1] - win_data.getTrueYRange()[0]) / 10.0;

	//x elements
	for (int i = win_data.getTrueXRange()[0] / x_true_tick_spacing; i * x_true_tick_spacing < win_data.getTrueXRange()[1]; ++i)
	{
		if (std::abs(win_data.x_trueToPixel(i * x_true_tick_spacing) - win_data.x_trueToPixel(0)) > 5)
		{
			int x_pixel_loc = win_data.x_trueToPixel(i * x_true_tick_spacing);

			//always create graph lines (except for when near axis)
			sf::RectangleShape temp_graph_line;
			temp_graph_line.setFillColor(graph_lines_color);
			temp_graph_line.setPosition(x_pixel_loc, win_data.getGraphOrigin().y);
			temp_graph_line.setSize(sf::Vector2f(1, win_data.getGraphSize().y));
			x_graph_lines.push_back(temp_graph_line);

			//only create ticks and labels if the x-axis ticks can be seen
			int upper_bound_tick = win_data.y_trueToPixel(0) + pixel_tick_half_width;
			int lower_bound_tick = win_data.y_trueToPixel(0) - pixel_tick_half_width;
			if ((upper_bound_tick >= win_data.getGraphOrigin().y && upper_bound_tick < win_data.getGraphOrigin().y + win_data.getGraphSize().y) ||
				(lower_bound_tick >= win_data.getGraphOrigin().y && lower_bound_tick < win_data.getGraphOrigin().y + win_data.getGraphSize().y))
			{
				if (upper_bound_tick >= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
				{
					upper_bound_tick = win_data.getGraphOrigin().y + win_data.getGraphSize().y - 1;
				}
				if (lower_bound_tick < win_data.getGraphOrigin().y)
				{
					lower_bound_tick = win_data.getGraphOrigin().y;
				}
				sf::RectangleShape temp_tick;
				temp_tick.setFillColor(ticks_color);
				temp_tick.setPosition(x_pixel_loc, lower_bound_tick);
				temp_tick.setSize(sf::Vector2f(1, upper_bound_tick - lower_bound_tick));
				x_axis_ticks.push_back(temp_tick);

				sf::Text temp_tick_label;
				temp_tick_label.setFillColor(tick_labels_color);
				temp_tick_label.setCharacterSize(20);
				temp_tick_label.setFont(font);
				temp_tick_label.setStyle(sf::Text::Bold);
				std::ostringstream stream;
				stream << std::setprecision(4);
				stream << i * x_true_tick_spacing;
				temp_tick_label.setString(stream.str());
				temp_tick_label.setPosition(x_pixel_loc - temp_tick_label.getGlobalBounds().width / 2, win_data.y_trueToPixel(0) - pixel_tick_half_width - 23);
				x_axis_tick_labels.push_back(temp_tick_label);
			}
		}
	}

	//y elements
	for (int i = win_data.getTrueYRange()[0] / y_true_tick_spacing; i * y_true_tick_spacing < win_data.getTrueYRange()[1]; ++i)
	{
		if (std::abs(win_data.y_trueToPixel(i * y_true_tick_spacing) - win_data.y_trueToPixel(0)) > 5)
		{
			int y_pixel_loc = win_data.y_trueToPixel(i * y_true_tick_spacing);

			//always create graph lines (except for when near axis)
			sf::RectangleShape temp_graph_line;
			temp_graph_line.setFillColor(graph_lines_color);
			temp_graph_line.setPosition(win_data.getGraphOrigin().x, y_pixel_loc);
			temp_graph_line.setSize(sf::Vector2f(win_data.getGraphSize().x, 1));
			y_graph_lines.push_back(temp_graph_line);

			//only create ticks and labels if the x-axis ticks can be seen
			int upper_bound_tick = win_data.x_trueToPixel(0) + pixel_tick_half_width;
			int lower_bound_tick = win_data.x_trueToPixel(0) - pixel_tick_half_width;
			if ((upper_bound_tick >= win_data.getGraphOrigin().x && upper_bound_tick < win_data.getGraphOrigin().x + win_data.getGraphSize().x) ||
				(lower_bound_tick >= win_data.getGraphOrigin().x && lower_bound_tick < win_data.getGraphOrigin().x + win_data.getGraphSize().x))
			{
				if (upper_bound_tick >= win_data.getGraphOrigin().x + win_data.getGraphSize().x)
				{
					upper_bound_tick = win_data.getGraphOrigin().x + win_data.getGraphSize().x - 1;
				}
				if (lower_bound_tick < win_data.getGraphOrigin().x)
				{
					lower_bound_tick = win_data.getGraphOrigin().x;
				}
				sf::RectangleShape temp_tick;
				temp_tick.setFillColor(ticks_color);
				temp_tick.setPosition(lower_bound_tick, y_pixel_loc);
				temp_tick.setSize(sf::Vector2f(upper_bound_tick - lower_bound_tick, 1));
				y_axis_ticks.push_back(temp_tick);

				sf::Text temp_tick_label;
				temp_tick_label.setFillColor(tick_labels_color);
				temp_tick_label.setCharacterSize(20);
				temp_tick_label.setFont(font);
				temp_tick_label.setStyle(sf::Text::Bold);
				std::ostringstream stream;
				stream << std::setprecision(4);
				stream << i * y_true_tick_spacing;
				temp_tick_label.setString(stream.str());
				temp_tick_label.setPosition(win_data.x_trueToPixel(0) + pixel_tick_half_width + 3, y_pixel_loc - 13);
				y_axis_tick_labels.push_back(temp_tick_label);
			}
		}
	}
}

void GraphElements::drawGraphElements(sf::RenderWindow& window)
{
	//graph lines
	if (graph_lines_drawable) {
		for (sf::RectangleShape& graph_line : x_graph_lines)
		{
			window.draw(graph_line);
		}
		for (sf::RectangleShape& graph_line : y_graph_lines)
		{
			window.draw(graph_line);
		}
	}

	//ticks
	if (ticks_drawable) {
		for (sf::RectangleShape& tick : x_axis_ticks)
		{
			window.draw(tick);
		}
		for (sf::RectangleShape& tick : y_axis_ticks)
		{
			window.draw(tick);
		}
	}

	//tick labels
	if (tick_labels_drawable) {
		for (sf::Text& tick_label : x_axis_tick_labels)
		{
			window.draw(tick_label);
		}
		for (sf::Text& tick_label : y_axis_tick_labels)
		{
			window.draw(tick_label);
		}
	}

	//border concealer
	for (sf::RectangleShape& border : border_concealer)
	{
		window.draw(border);
	}
}

void GraphElements::setTicksDrawability(bool new_drawability)
{
	ticks_drawable = new_drawability;
}

void GraphElements::setTicksColor(sf::Color new_color)
{
	ticks_color = new_color;
}

void GraphElements::setTickLabelsDrawability(bool new_drawability)
{
	tick_labels_drawable = new_drawability;
}

void GraphElements::setTickLabelsColor(sf::Color new_color)
{
	tick_labels_color = new_color;
}

void GraphElements::setGraphLinesDrawability(bool new_drawability)
{
	graph_lines_drawable = new_drawability;
}

void GraphElements::setGraphLinesColor(sf::Color new_color)
{
	graph_lines_color = new_color;
}

bool GraphElements::getTicksDrawability()
{
	return ticks_drawable;
}

bool GraphElements::getTickLabelsDrawability()
{
	return tick_labels_drawable;
}

bool GraphElements::getGraphLinesDrawability()
{
	return graph_lines_drawable;
}