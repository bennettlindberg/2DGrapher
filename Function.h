#pragma once

#include <SFML/Graphics.hpp>
#include "WindowData.h"
#include <string>

class Function
{
public:
	//constructors
	Function(char funct_of, const std::string& new_equation, const sf::Color& new_color);
	Function(char funct_of, const std::string& new_equation, const sf::Color& new_color, const std::string& new_classification);

	//update methods
	void updateValues();
	void updateDepictionUponResize();
	static void updateWindowData(const WindowData& new_data);

	//setters
	void setTitle(const std::string& new_title);
	void setEquation(const std::string& new_equation);
	void setColor(const sf::Color& new_color);
	void setDrawableStatus(bool new_status);
	void setClassification(std::string new_classification);

	//getters
	std::string getTitle();
	std::string getEquation();
	sf::Color getColor();
	bool isDrawable();
	std::string getClassification();

	char getFunctionOf();
	int getIdNumber();
	sf::VertexArray getDepiction();

	std::string getType();

private:
	//static methods
	static bool isSpecialChar(char current);
	static double evaluateExpression(bool& exception_thrown, double input, std::string equation);

	//class WindowData object
	static WindowData win_data;

	//class counters
	static int next_id_num;
	static int next_x_funct_num;
	static int next_y_funct_num;

	//data members
	std::string title;
	std::string equation;
	sf::Color color;
	bool drawable = true;
	std::string classification = "none";

	char function_of;
	int id_number;
	sf::VertexArray depiction;
};