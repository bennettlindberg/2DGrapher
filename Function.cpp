#include "Function.h"

//class counters
sf::RenderWindow window(sf::VideoMode(2000, 1000), "2D Grapher");
WindowData Function::win_data(window);
int Function::next_id_num = 1;
int Function::next_x_funct_num = 1;
int Function::next_y_funct_num = 1;

//constructors
Function::Function(char funct_of, const std::string& new_equation, const sf::Color& new_color) : function_of(funct_of), color(new_color)
{
	std::string shortened;
	for (std::string::const_iterator i = new_equation.begin(); i != new_equation.end(); ++i)
	{
		if (!isspace(*i))
		{
			shortened.push_back(*i);
		}
	}
	equation = shortened;

	id_number = next_id_num++;
	if (function_of == 'x')
	{
		title = "f" + std::to_string(next_x_funct_num++) + "(x)";
		depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().x);
		for (int i = 0; i < win_data.getGraphSize().x; ++i)
		{
			depiction[i].position.x = i + win_data.getGraphOrigin().x;
			depiction[i].color = color;
		}
	}
	else if (function_of == 'y')
	{
		title = "g" + std::to_string(next_y_funct_num++) + "(y)";
		depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().y);
		for (int i = 0; i < win_data.getGraphSize().y; ++i)
		{
			depiction[i].position.y = i + win_data.getGraphOrigin().y;
			depiction[i].color = color;
		}
	}
	updateValues();
}

Function::Function(char funct_of, const std::string& new_equation, const sf::Color& new_color, const std::string& new_classification) : function_of(funct_of), color(new_color), classification(new_classification)
{
	std::string shortened;
	for (std::string::const_iterator i = new_equation.begin(); i != new_equation.end(); ++i)
	{
		if (!isspace(*i))
		{
			shortened.push_back(*i);
		}
	}
	equation = shortened;

	id_number = next_id_num++;
	if (classification == "axis")
	{
		if (function_of == 'x')
		{
			title = "y";
			depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().x);
			for (int i = 0; i < win_data.getGraphSize().x; ++i)
			{
				depiction[i].position.x = i + win_data.getGraphOrigin().x;
				depiction[i].position.y = win_data.getGraphOrigin().y + (win_data.getGraphSize().y / 2);
				depiction[i].color = color;
			}
		}
		else if (function_of == 'y')
		{
			title = "x";
			depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().y);
			for (int i = 0; i < win_data.getGraphSize().y; ++i)
			{
				depiction[i].position.y = i + win_data.getGraphOrigin().y;
				depiction[i].position.x = win_data.getGraphOrigin().x + (win_data.getGraphSize().x / 2);
				depiction[i].color = color;
			}
		}
	}
}

//update methods
void Function::updateValues()
{
	if (function_of == 'x')
	{
		bool prev_exception_thrown = false;
		for (int i = 0; i < win_data.getGraphSize().x; ++i)
		{
			bool exception_thrown = false;
			depiction[i].position.y = win_data.y_trueToPixel(evaluateExpression(exception_thrown, win_data.x_pixelToTrue(i + win_data.getGraphOrigin().x), equation));
			if (exception_thrown)
			{
				depiction[i].color = sf::Color::Transparent;
				prev_exception_thrown = true;
			}
			else if (prev_exception_thrown)
			{
				depiction[i].color = sf::Color::Transparent;
				prev_exception_thrown = false;
			}
			else if (depiction[i].position.y < win_data.getGraphOrigin().y)
			{
				//depiction[i].color = sf::Color::Transparent;
				depiction[i].position.y = win_data.getGraphOrigin().y - 1;
			}
			else if (depiction[i].position.y > win_data.getGraphOrigin().y + win_data.getGraphSize().y)
			{
				//depiction[i].color = sf::Color::Transparent;
				depiction[i].position.y = win_data.getGraphOrigin().y + win_data.getGraphSize().y + 1;
			}
			else
			{
				depiction[i].color = color;
			}
		}
	}
	else if (function_of == 'y')
	{
		bool prev_exception_thrown = false;
		for (int i = 0; i < win_data.getGraphSize().y; ++i)
		{
			bool exception_thrown = false;
			depiction[i].position.x = win_data.x_trueToPixel(evaluateExpression(exception_thrown, win_data.y_pixelToTrue(i + win_data.getGraphOrigin().y), equation));
			if (exception_thrown)
			{
				depiction[i].color = sf::Color::Transparent;
				prev_exception_thrown = true;
			}
			else if (prev_exception_thrown)
			{
				depiction[i].color = sf::Color::Transparent;
				prev_exception_thrown = false;
			}
			else if (depiction[i].position.x < win_data.getGraphOrigin().x || depiction[i].position.x > win_data.getGraphOrigin().x + win_data.getGraphSize().x)
			{
				depiction[i].color = sf::Color::Transparent;
			}
			else
			{
				depiction[i].color = color;
			}
		}
	}
}

void Function::updateDepictionUponResize()
{
	if (function_of == 'x')
	{
		depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().x);
		for (int i = 0; i < win_data.getGraphSize().x; ++i)
		{
			depiction[i].position.x = i + win_data.getGraphOrigin().x;
			depiction[i].color = color;
		}
	}
	else if (function_of == 'y')
	{
		depiction = sf::VertexArray(sf::LinesStrip, win_data.getGraphSize().y);
		for (int i = 0; i < win_data.getGraphSize().y; ++i)
		{
			depiction[i].position.y = i + win_data.getGraphOrigin().y;
			depiction[i].color = color;
		}
	}
	updateValues();
}

void Function::updateWindowData(const WindowData& new_data)
{
	win_data = new_data;
	//Must manually updateDepictionUponResize() for each function in Source.cpp after updating the window
}

//setters
void Function::setTitle(const std::string& new_title)
{
	title = new_title;
}

void Function::setEquation(const std::string& new_equation)
{
	std::string shortened;
	for (std::string::const_iterator i = new_equation.begin(); i != new_equation.end(); ++i)
	{
		if (!isspace(*i))
		{
			shortened.push_back(*i);
		}
	}
	equation = shortened;
}

void Function::setColor(const sf::Color& new_color)
{
	color = new_color;
}

void Function::setDrawableStatus(bool new_status)
{
	drawable = new_status;
}

void Function::setClassification(std::string new_classification)
{
	classification = new_classification;
}

//getters
std::string Function::getTitle()
{
	return title;
}

std::string Function::getEquation()
{
	return equation;
}

sf::Color Function::getColor()
{
	return color;
}

bool Function::isDrawable()
{
	return drawable;
}

std::string Function::getClassification()
{
	return classification;
}

char Function::getFunctionOf()
{
	return function_of;
}

int Function::getIdNumber()
{
	return id_number;
}

sf::VertexArray Function::getDepiction()
{
	return depiction;
}

std::string Function::getType()
{
	if (classification == "axis")
	{
		return "Axis";
	}
	else if (function_of == 'x')
	{
		return "Fn of x";
	}
	else if (function_of == 'y')
	{
		return "Fn of y";
	}
	else
	{
		return "Other";
	}
}

//private static methods
bool Function::isSpecialChar(char current)
{
	static const char special_chars[] = { '(', ')', '*', '/', '+', '-', '^' };
	for (char c : special_chars)
	{
		if (current == c)
		{
			return true;
		}
	}
	return false;
}

double Function::evaluateExpression(bool& exception_thrown, double input, std::string expression)
{
	bool special_char_found = false;
	std::string::size_type i;
	for (i = expression.size() - 1; i >= 0; --i) // watch out -- std::string::size_type is unsigned!
	{
		if (i >= expression.size())
		{
			break;
		}
		else if (isSpecialChar(expression[i]))
		{
			special_char_found = true;
			break;
		}
	}

	// base case:
	if (!special_char_found)
	{
		double return_val = 0;
		if (expression == "x" || expression == "y")
		{
			return input;
		}
		else if (expression.size() == 0) // to avoid attempting to convert a "" expression to double
		{
			return 0;
		}
		try
		{
			return_val = std::stod(expression); //unhandled exceptions -- such as log(-x), x^x -- maybe try a bool for whole stack trace for a given point and set color to black for such points (ie, don't display them)?
		}
		catch (std::exception)
		{
			exception_thrown = true;
			return_val = 0;
		}
		return return_val;
	}

	// recursive case:
	char special_char = expression[i];
	switch (special_char)
	{
	case ')':
	{
		std::string::size_type j;
		for (j = i - 1; j >= 0; --j)
		{
			if (j >= i)
			{
				j = -1;
				break;
			}
			else if (expression[j] == '(')
			{
				break;
			}
		}
		double evaled_sub_expr = evaluateExpression(exception_thrown, input, expression.substr(j + 1, i - j - 1));
		return evaluateExpression(exception_thrown, input, expression.substr(0, j) + std::to_string(evaled_sub_expr));
		break;
	}
	case '*':
	case '/':
	{
		std::string::size_type j;
		for (j = i - 1; j >= 0; --j)
		{
			if (j >= i)
			{
				j = -1;
				break;
			}
			else if (expression[j] == '+' || expression[j] == '-')
			{
				break;
			}
		}
		double evaled_sub_expr = 0;
		if (expression[i] == '*')
		{
			evaled_sub_expr = evaluateExpression(exception_thrown, input, expression.substr(j + 1, i - j - 1)) * evaluateExpression(exception_thrown, input, expression.substr(i + 1));
		}
		else if (expression[i] == '/')
		{
			evaled_sub_expr = evaluateExpression(exception_thrown, input, expression.substr(j + 1, i - j - 1)) / evaluateExpression(exception_thrown, input, expression.substr(i + 1));
		}
		return evaluateExpression(exception_thrown, input, expression.substr(0, j + 1) + std::to_string(evaled_sub_expr));
		break;
	}
	case '+':
	{
		return evaluateExpression(exception_thrown, input, expression.substr(0, i)) + evaluateExpression(exception_thrown, input, expression.substr(i + 1));
		break;
	}
	case '-':
	{
		if (i == 0) // to support a negative first term of expression without needing to type (0-...)
		{
			return -(evaluateExpression(exception_thrown, input, expression.substr(1)));
		}
		return evaluateExpression(exception_thrown, input, expression.substr(0, i)) - evaluateExpression(exception_thrown, input, expression.substr(i + 1));
		break;
	}
	case '^':
	{
		std::string::size_type j;
		for (j = i - 1; j >= 0; --j)
		{
			if (j >= i)
			{
				j = -1;
				break;
			}
			else if (expression[j] == ')') // to handle parenthetical base of exponential term
			{
				std::string::size_type k;
				for (k = j - 1; k >= 0; --k)
				{
					if (k >= j)
					{
						k = -1;
						break;
					}
					else if (expression[k] == '(')
					{
						break;
					}
				}
				double paren_sub_expr = evaluateExpression(exception_thrown, input, expression.substr(k + 1, j - k - 1));
				double expon_sub_expr = std::pow(paren_sub_expr, evaluateExpression(exception_thrown, input, expression.substr(i + 1)));
				return evaluateExpression(exception_thrown, input, expression.substr(0, k) + std::to_string(expon_sub_expr));
			}
			else if (isSpecialChar(expression[j])) // not ')'
			{
				break;
			}
		}
		double evaled_sub_expr = std::pow(evaluateExpression(exception_thrown, input, expression.substr(j + 1, i - j - 1)), evaluateExpression(exception_thrown, input, expression.substr(i + 1)));
		return evaluateExpression(exception_thrown, input, expression.substr(0, j + 1) + std::to_string(evaled_sub_expr));
		break;
	}
	}
}