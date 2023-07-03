// Old version of the Source.cpp file

//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//#include <cmath>
//#include <iostream>
//
//// true cords = x and y cords in terms of the actual function values
//// pixel cords = x and y raster cords of the display pixel for each point
//double y_pixelToTrue(int y_pixel, int vertical_dimension, double y_increment)
//{
//	int y_middle = vertical_dimension / 2;
//	return -((y_pixel - y_middle) * y_increment);
//}
//
//double x_pixelToTrue(int x_pixel, int horizontal_dimension, double x_increment)
//{
//	int x_middle = horizontal_dimension / 2;
//	return (x_pixel - x_middle) * x_increment;
//}
//
//int y_trueToPixel(double y_true, int vertical_dimension, double y_increment)
//{
//	int y_middle = vertical_dimension / 2;
//	return y_middle - (y_true / y_increment);
//}
//
//int x_trueToPixel(double x_true, int horizontal_dimension, double x_increment)
//{
//	int x_middle = horizontal_dimension / 2;
//	return x_middle + (x_true / x_increment);
//}
//
//std::string shortenFunctionEquation(std::string funct_eqn)
//{
//	std::string shortened = "";
//	for (std::string::iterator i = funct_eqn.begin() + funct_eqn.find('=') + 2; i != funct_eqn.end(); ++i)
//	{
//		if (!isspace(*i))
//		{
//			shortened.push_back(*i);
//		}
//	}
//	return shortened;
//}
//
//bool isSpecialChar(char current)
//{
//	static const char special_chars[] = { '(', ')', '*', '/', '+', '-', '^' };
//	for (char c : special_chars)
//	{
//		if (current == c)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
//double evaluateFunction(bool &exception_thrown, double input, std::string equation)
//{
//	bool special_char_found = false;
//	std::string::size_type i;
//	for (i = equation.size() - 1; i >= 0; --i) // watch out -- std::string::size_type is unsigned!
//	{
//		if (i >= equation.size())
//		{
//			break;
//		}
//		else if (isSpecialChar(equation[i]))
//		{
//			special_char_found = true;
//			break;
//		}
//	}
//
//	// base case:
//	if (!special_char_found)
//	{
//		double return_val = 0;
//		if (equation == "x" || equation == "y")
//		{
//			return input;
//		}
//		else if (equation.size() == 0) // to avoid attempting to convert a "" equation to double
//		{
//			return 0;
//		}
//		try
//		{
//			return_val = std::stod(equation); //unhandled exceptions -- such as log(-x), x^x -- maybe try a bool for whole stack trace for a given point and set color to black for such points (ie, don't display them)?
//		}
//		catch (std::exception)
//		{
//			exception_thrown = true;
//			return_val = 0;
//		}
//		return return_val;
//	}
//
//	// recursive case:
//	char special_char = equation[i];
//	switch (special_char)
//	{
//	case ')':
//	{
//		std::string::size_type j;
//		for (j = i - 1; j >= 0; --j)
//		{
//			if (j >= i)
//			{
//				j = -1;
//				break;
//			}
//			else if (equation[j] == '(')
//			{
//				break;
//			}
//		}
//		double evaled_sub_eqn = evaluateFunction(exception_thrown, input, equation.substr(j + 1, i - j - 1));
//		return evaluateFunction(exception_thrown, input, equation.substr(0, j) + std::to_string(evaled_sub_eqn));
//		break;
//	}
//	case '*':
//	case '/':
//	{
//		std::string::size_type j;
//		for (j = i - 1; j >= 0; --j)
//		{
//			if (j >= i)
//			{
//				j = -1;
//				break;
//			}
//			else if (equation[j] == '+' || equation[j] == '-')
//			{
//				break;
//			}
//		}
//		double evaled_sub_eqn = 0;
//		if (equation[i] == '*')
//		{
//			evaled_sub_eqn = evaluateFunction(exception_thrown, input, equation.substr(j + 1, i - j - 1)) * evaluateFunction(exception_thrown, input, equation.substr(i + 1));
//		}
//		else if (equation[i] == '/')
//		{
//			evaled_sub_eqn = evaluateFunction(exception_thrown, input, equation.substr(j + 1, i - j - 1)) / evaluateFunction(exception_thrown, input, equation.substr(i + 1));
//		}
//		return evaluateFunction(exception_thrown, input, equation.substr(0, j + 1) + std::to_string(evaled_sub_eqn));
//		break;
//	}
//	case '+':
//	{
//		return evaluateFunction(exception_thrown, input, equation.substr(0, i)) + evaluateFunction(exception_thrown, input, equation.substr(i + 1));
//		break;
//	}
//	case '-':
//	{
//		if (i == 0) // to support a negative first term of equation without needing to type (0-...)
//		{
//			return -(evaluateFunction(exception_thrown, input, equation.substr(1)));
//		}
//		return evaluateFunction(exception_thrown, input, equation.substr(0, i)) - evaluateFunction(exception_thrown, input, equation.substr(i + 1));
//		break;
//	}
//	case '^':
//	{
//		std::string::size_type j;
//		for (j = i - 1; j >= 0; --j)
//		{
//			if (j >= i)
//			{
//				j = -1;
//				break;
//			}
//			else if (equation[j] == ')') // to handle parenthetical base of exponential term
//			{
//				std::string::size_type k;
//				for (k = j - 1; k >= 0; --k)
//				{
//					if (k >= j)
//					{
//						k = -1;
//						break;
//					}
//					else if (equation[k] == '(')
//					{
//						break;
//					}
//				}
//				double paren_sub_eqn = evaluateFunction(exception_thrown, input, equation.substr(k + 1, j - k - 1));
//				double expon_sub_eqn = std::pow(paren_sub_eqn, evaluateFunction(exception_thrown, input, equation.substr(i + 1)));
//				return evaluateFunction(exception_thrown, input, equation.substr(0, k) + std::to_string(expon_sub_eqn));
//			}
//			else if (isSpecialChar(equation[j])) // not ')'
//			{
//				break;
//			}
//		}
//		double evaled_sub_eqn = std::pow(evaluateFunction(exception_thrown, input, equation.substr(j + 1, i - j - 1)), evaluateFunction(exception_thrown, input, equation.substr(i + 1)));
//		return evaluateFunction(exception_thrown, input, equation.substr(0, j + 1) + std::to_string(evaled_sub_eqn));
//		break;
//	}
//	}
//}
//
//struct Function
//{
//	char function_of;
//	std::string equation;
//	bool to_be_drawn = true;
//	sf::VertexArray depiction;
//	Function(char funct_of, std::string eqn, int horizontal_dimension, int vertical_dimension) : function_of(funct_of), equation(eqn)
//	{
//		if (function_of == 'x')
//		{
//			depiction = sf::VertexArray(sf::LinesStrip, horizontal_dimension);
//			for (int i = 0; i < horizontal_dimension; ++i)
//			{
//				depiction[i].position.x = i;
//			}
//		}
//		else if (function_of == 'y')
//		{
//			depiction = sf::VertexArray(sf::LinesStrip, vertical_dimension);
//			for (int i = 0; i < vertical_dimension; ++i)
//			{
//				depiction[i].position.y = i;
//			}
//		}
//	}
//	void updateValues(sf::Color color, int horizontal_dimension, int vertical_dimension, double x_increment, double y_increment)
//	{
//		if (function_of == 'x')
//		{
//			bool prev_exception_thrown = false;
//			for (int i = 0; i < horizontal_dimension; ++i)
//			{
//				bool exception_thrown = false;
//				depiction[i].position.y = y_trueToPixel(evaluateFunction(exception_thrown, x_pixelToTrue(i, horizontal_dimension, x_increment), equation), vertical_dimension, y_increment);
//				if (exception_thrown)
//				{
//					depiction[i].color = sf::Color::Transparent;
//					prev_exception_thrown = true;
//				}
//				else if (prev_exception_thrown)
//				{
//					depiction[i].color = sf::Color::Transparent;
//					prev_exception_thrown = false;
//				}
//				else
//				{
//					depiction[i].color = color;
//				}
//			}
//		}
//		else if (function_of == 'y')
//		{
//			bool prev_exception_thrown = false;
//			for (int i = 0; i < vertical_dimension; ++i)
//			{
//				bool exception_thrown = false;
//				depiction[i].position.x = x_trueToPixel(evaluateFunction(exception_thrown, y_pixelToTrue(i, vertical_dimension, y_increment), equation), horizontal_dimension, x_increment);
//				if (exception_thrown)
//				{
//					depiction[i].color = sf::Color::Transparent;
//					prev_exception_thrown = true;
//				}
//				else if (prev_exception_thrown)
//				{
//					depiction[i].color = sf::Color::Transparent;
//					prev_exception_thrown = false;
//				}
//				else
//				{
//					depiction[i].color = color;
//				}
//			}
//		}
//	}
//};
//
//void createFunction(char function_of, sf::RenderWindow &window, std::vector<Function> &functions, std::vector<sf::Text> &funct_texts, int horizontal_dimension, int vertical_dimension, double x_increment, double y_increment)
//{
//	static int next_vertical_position = -10;
//	next_vertical_position += 30;
//
//	static int next_x_funct_num = 0;
//	if (function_of == 'x')
//	{
//		++next_x_funct_num;
//	}
//
//	static int next_y_funct_num = 0;
//	if (function_of == 'y')
//	{
//		++next_y_funct_num;
//	}
//
//	int random_red = rand() % 256;
//	int random_green = rand() % 256;
//	int random_blue = rand() % 256;
//	sf::Color random_color = sf::Color(random_red, random_green, random_blue);
//
//	sf::Font consolas_font;
//	consolas_font.loadFromFile("Consolas.ttf");
//
//	bool done_entering_funct = false;
//	sf::Text display_funct_text;
//	display_funct_text.setFont(consolas_font);
//	display_funct_text.setCharacterSize(24);
//	display_funct_text.setFillColor(random_color);
//	display_funct_text.setPosition(sf::Vector2f(20, next_vertical_position));
//	if (function_of == 'x')
//	{
//		display_funct_text.setString("f" + std::to_string(next_x_funct_num) + "(x) = ");
//	}
//	else if (function_of == 'y')
//	{
//		display_funct_text.setString("g" + std::to_string(next_y_funct_num) + "(y) = ");
//	}
//
//	sf::RectangleShape cursor;
//	cursor.setPosition(display_funct_text.getGlobalBounds().left + display_funct_text.getGlobalBounds().width, display_funct_text.getGlobalBounds().top);
//	cursor.setSize(sf::Vector2f(3, 24));
//	bool cursor_to_be_drawn = true;
//	float delay = 0.5f;
//	sf::Clock clock;
//
//	while (!done_entering_funct)
//	{
//		bool event_already_processed = false; // to avoid adding a char when deleting or exiting
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::Enter)
//				{
//					done_entering_funct = true;
//					event_already_processed = true;
//				}
//				else if (event.key.code == sf::Keyboard::Backspace)
//				{
//					if (display_funct_text.getString().getSize() > display_funct_text.getString().find('=') + 2)
//					{
//						std::string temp = display_funct_text.getString().toAnsiString();
//						temp.pop_back();
//						display_funct_text.setString(temp);
//						cursor.setPosition(display_funct_text.getGlobalBounds().left + display_funct_text.getGlobalBounds().width, display_funct_text.getGlobalBounds().top);
//					}
//					event_already_processed = true;
//				}
//				break;
//			case sf::Event::TextEntered:
//				if (!event_already_processed)
//				{
//					display_funct_text.setString(display_funct_text.getString() + event.text.unicode);
//					cursor.setPosition(display_funct_text.getGlobalBounds().left + display_funct_text.getGlobalBounds().width, display_funct_text.getGlobalBounds().top);
//				}
//				break;
//			}
//		}
//
//		window.clear(sf::Color::Black);
//
//		for (Function& funct : functions) //REFACTOR SO THAT AXES ARE DRAWN LAST??????
//		{
//			if (funct.to_be_drawn)
//			{
//				window.draw(funct.depiction);
//			}
//		}
//
//		for (sf::Text& text : funct_texts)
//		{
//			text.setFont(consolas_font);
//			window.draw(text);
//		}
//
//		window.draw(display_funct_text);
//
//		if (clock.getElapsedTime().asSeconds() >= delay)
//		{
//			cursor_to_be_drawn = !cursor_to_be_drawn;
//			clock.restart();
//		}
//		if (cursor_to_be_drawn)
//		{
//			window.draw(cursor);
//		}
//
//		window.display();
//	}
//
//	Function my_funct(function_of, shortenFunctionEquation(display_funct_text.getString()), horizontal_dimension, vertical_dimension);
//	my_funct.updateValues(random_color, horizontal_dimension, vertical_dimension, x_increment, y_increment);
//	functions.push_back(my_funct);
//	funct_texts.push_back(display_funct_text);
//}
//
//int main()
//{
//	srand(time(0));
//
//	sf::Font consolas_font;
//	consolas_font.loadFromFile("Consolas.ttf");
//
//	int horizontal_dimension = 1000;
//	int vertical_dimension = 1000;
//
//	double x_range[] = { -50, 50 };
//	double y_range[] = { -50, 50 };
//
//	double x_increment = (std::abs(x_range[0]) + std::abs(x_range[1])) / horizontal_dimension;
//	double y_increment = (std::abs(y_range[0]) + std::abs(y_range[1])) / vertical_dimension;
//
//	std::vector<sf::Text> funct_texts;
//
//	std::vector<Function> functions;
//
//	Function x_axis('x', "0", horizontal_dimension, vertical_dimension);
//	x_axis.updateValues(sf::Color::Cyan, horizontal_dimension, vertical_dimension, x_increment, y_increment);
//	functions.push_back(x_axis);
//
//	Function y_axis('y', "0", horizontal_dimension, vertical_dimension);
//	y_axis.updateValues(sf::Color::Cyan, horizontal_dimension, vertical_dimension, x_increment, y_increment);
//	functions.push_back(y_axis);
//
//	sf::RenderWindow window(sf::VideoMode(horizontal_dimension, vertical_dimension), "2D Grapher");
//	
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::KeyPressed:
//				if (event.key.code == sf::Keyboard::X)
//				{
//					createFunction('x', window, functions, funct_texts, horizontal_dimension, vertical_dimension, x_increment, y_increment);
//				}
//				else if (event.key.code == sf::Keyboard::Y)
//				{
//					createFunction('y', window, functions, funct_texts, horizontal_dimension, vertical_dimension, x_increment, y_increment);
//				}
//				break;
//			//case sf::Event::MouseWheelScrolled:
//			//	break;
//			//case sf::Event::MouseButtonPressed:
//			//	break;
//			//case sf::Event::MouseButtonReleased:
//			//	break;
//			}
//		}
//
//		window.clear(sf::Color::Black);
//
//		for (Function& funct : functions)
//		{
//			if (funct.to_be_drawn)
//			{
//				window.draw(funct.depiction);
//			}
//		}
//
//		for (sf::Text& text : funct_texts)
//		{
//			text.setFont(consolas_font);
//			window.draw(text);
//		}
//
//		window.display();
//	}
//}