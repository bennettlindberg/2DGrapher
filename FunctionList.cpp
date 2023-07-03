#include "FunctionList.h"

//constructor
FunctionList::FunctionList(const WindowData& new_win_data, const sf::Font& new_font, const std::vector<Function>& new_functions) : win_data(new_win_data), font(new_font), functions(new_functions)
{
	//title
	title_text.setFillColor(sf::Color::Black);
	title_text.setCharacterSize(24);
	title_text.setFont(font);
	title_text.setStyle(sf::Text::Bold);
	title_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y - 1));
	title_text.setString("Function List");

	title_box.setFillColor(sf::Color::White);
	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getFunctionListOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	//header
	id_number_header_text.setFillColor(sf::Color::Yellow);
	id_number_header_text.setCharacterSize(24);
	id_number_header_text.setFont(font);
	id_number_header_text.setStyle(sf::Text::Regular);
	id_number_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y + 30 - 1));
	id_number_header_text.setString("ID");

	type_header_text.setFillColor(sf::Color::Yellow);
	type_header_text.setCharacterSize(24);
	type_header_text.setFont(font);
	type_header_text.setStyle(sf::Text::Regular);
	type_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.15), win_data.getFunctionListOrigin().y + 30 - 1));
	type_header_text.setString("Type");

	equation_header_text.setFillColor(sf::Color::Yellow);
	equation_header_text.setCharacterSize(24);
	equation_header_text.setFont(font);
	equation_header_text.setStyle(sf::Text::Regular);
	equation_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.35), win_data.getFunctionListOrigin().y + 30 - 1));
	equation_header_text.setString("Equation");

	header_border.setFillColor(sf::Color::Transparent);
	header_border.setOutlineColor(sf::Color::White);
	header_border.setOutlineThickness(3);
	header_border.setPosition(win_data.getFunctionListOrigin().x, win_data.getFunctionListOrigin().y + 30);
	header_border.setSize(sf::Vector2f(win_data.getFunctionListSize().x, 30 - 1));

	//list
	int leftover_list_y_space = win_data.getFunctionListSize().y - 60;
	num_functions_included = (leftover_list_y_space - 1) / 30;

	list_border.setFillColor(sf::Color::Transparent);
	list_border.setOutlineColor(sf::Color::White);
	list_border.setOutlineThickness(3);
	list_border.setPosition(win_data.getFunctionListOrigin().x, win_data.getFunctionListOrigin().y + 30 + 30 + 1);
	list_border.setSize(sf::Vector2f(win_data.getFunctionListSize().x, leftover_list_y_space - 1));

	sf::Text temp_text;
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(24);
	temp_text.setFont(font);
	temp_text.setStyle(sf::Text::Regular);
	temp_text.setString("");
	for (int i = 0; i < num_functions_included; ++i)
	{
		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		id_number_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.15), win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		type_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.35), win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		equation_list_texts.push_back(temp_text);
	}

	for (int i = 0; i < num_functions_included && i < functions.size(); ++i)
	{
		id_number_list_texts[i].setString(std::to_string(functions[i].getIdNumber()));
		type_list_texts[i].setString(functions[i].getType());
		equation_list_texts[i].setString(functions[i].getTitle() + " = " + functions[i].getEquation());

		id_number_list_texts[i].setFillColor(functions[i].getColor());
		type_list_texts[i].setFillColor(functions[i].getColor());
		equation_list_texts[i].setFillColor(functions[i].getColor());
	}
}

//window-related methods
void FunctionList::updateWindowData(const WindowData& new_data)
{
	win_data = new_data;

	//update sizes and positions in relation to new window data
	//title
	title_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y - 1));
	title_text.setString("Function List");

	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getFunctionListOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	//header
	id_number_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y + 30 - 1));
	type_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.15), win_data.getFunctionListOrigin().y + 30 - 1));
	equation_header_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.35), win_data.getFunctionListOrigin().y + 30 - 1));

	header_border.setPosition(win_data.getFunctionListOrigin().x, win_data.getFunctionListOrigin().y + 30);
	header_border.setSize(sf::Vector2f(win_data.getFunctionListSize().x, 30 - 1));

	//list
	int leftover_list_y_space = win_data.getFunctionListSize().y - 60;
	num_functions_included = (leftover_list_y_space - 1) / 30;

	list_border.setPosition(win_data.getFunctionListOrigin().x, win_data.getFunctionListOrigin().y + 30 + 30 + 1);
	list_border.setSize(sf::Vector2f(win_data.getFunctionListSize().x, leftover_list_y_space - 1));

	id_number_list_texts.clear();
	type_list_texts.clear();
	equation_list_texts.clear();

	sf::Text temp_text;
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(24);
	temp_text.setFont(font);
	temp_text.setStyle(sf::Text::Regular);
	temp_text.setString("");
	for (int i = 0; i < num_functions_included; ++i)
	{
		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6, win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		id_number_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.15), win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		type_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getFunctionListOrigin().x + 6 + (win_data.getFunctionListSize().x * 0.35), win_data.getFunctionListOrigin().y + 30 + 30 + (i * 30) - 1));
		equation_list_texts.push_back(temp_text);
	}

	starting_pos_in_functions = 0;

	for (int i = 0; i < num_functions_included && i < functions.size(); ++i)
	{
		id_number_list_texts[i].setString(std::to_string(functions[i].getIdNumber()));
		type_list_texts[i].setString(functions[i].getType());
		equation_list_texts[i].setString(functions[i].getTitle() + " = " + functions[i].getEquation());

		id_number_list_texts[i].setFillColor(functions[i].getColor());
		type_list_texts[i].setFillColor(functions[i].getColor());
		equation_list_texts[i].setFillColor(functions[i].getColor());
	}
}

void FunctionList::drawFunctionList(sf::RenderWindow& window)
{
	window.draw(title_box);
	window.draw(title_text);

	window.draw(header_border);
	window.draw(id_number_header_text);
	window.draw(type_header_text);
	window.draw(equation_header_text);

	window.draw(list_border);
	for (const sf::Text& text : id_number_list_texts)
	{
		window.draw(text);
	}
	for (const sf::Text& text : type_list_texts)
	{
		window.draw(text);
	}
	for (const sf::Text& text : equation_list_texts)
	{
		window.draw(text);
	}
}

//setters
void FunctionList::setFont(const sf::Font& new_font)
{
	font = new_font;
}

void FunctionList::setTitleText(const std::string& new_text)
{
	title_text.setString(new_text);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));
}

void FunctionList::setIDNumberHeaderText(const std::string& new_text)
{
	id_number_header_text.setString(new_text);
}

void FunctionList::setTypeHeaderText(const std::string& new_text)
{
	type_header_text.setString(new_text);
}

void FunctionList::setEquationHeaderText(const std::string& new_text)
{
	equation_header_text.setString(new_text);
}

void FunctionList::replaceFunctionList(const std::vector<Function>& new_functions)
{
	functions = new_functions;

	for (int i = 0; i < num_functions_included; ++i)
	{
		id_number_list_texts[i].setString("");
		type_list_texts[i].setString("");
		equation_list_texts[i].setString("");
	}

	starting_pos_in_functions = 0;

	for (int i = 0; i < num_functions_included && i < functions.size(); ++i)
	{
		id_number_list_texts[i].setString(std::to_string(functions[i].getIdNumber()));
		type_list_texts[i].setString(functions[i].getType());
		equation_list_texts[i].setString(functions[i].getTitle() + " = " + functions[i].getEquation());

		id_number_list_texts[i].setFillColor(functions[i].getColor());
		type_list_texts[i].setFillColor(functions[i].getColor());
		equation_list_texts[i].setFillColor(functions[i].getColor());
	}
}

void FunctionList::appendToFunctionList(const Function& new_function)
{
	functions.push_back(new_function);

	for (int i = 0; i < num_functions_included; ++i)
	{
		id_number_list_texts[i].setString("");
		type_list_texts[i].setString("");
		equation_list_texts[i].setString("");
	}

	starting_pos_in_functions = functions.size() - num_functions_included;
	if (starting_pos_in_functions < 0)
	{
		starting_pos_in_functions = 0;
	}

	for (int i = 0; i < num_functions_included && i < functions.size(); ++i)
	{
		id_number_list_texts[i].setString(std::to_string(functions[i + starting_pos_in_functions].getIdNumber()));
		type_list_texts[i].setString(functions[i + starting_pos_in_functions].getType());
		equation_list_texts[i].setString(functions[i + starting_pos_in_functions].getTitle() + " = " + functions[i + starting_pos_in_functions].getEquation());
	
		id_number_list_texts[i].setFillColor(functions[i].getColor());
		type_list_texts[i].setFillColor(functions[i].getColor());
		equation_list_texts[i].setFillColor(functions[i].getColor());
	}
}

void FunctionList::removeFromFunctionList(Function &removed_function)
{
	std::vector<Function> temp;
	for (Function& funct : functions)
	{
		if (funct.getIdNumber() != removed_function.getIdNumber())
		{
			temp.push_back(funct);
		}
	}
	functions = temp;

	for (int i = 0; i < num_functions_included; ++i)
	{
		id_number_list_texts[i].setString("");
		type_list_texts[i].setString("");
		equation_list_texts[i].setString("");
	}

	starting_pos_in_functions = 0;

	for (int i = 0; i < num_functions_included && i < functions.size(); ++i)
	{
		id_number_list_texts[i].setString(std::to_string(functions[i].getIdNumber()));
		type_list_texts[i].setString(functions[i].getType());
		equation_list_texts[i].setString(functions[i].getTitle() + " = " + functions[i].getEquation());

		id_number_list_texts[i].setFillColor(functions[i].getColor());
		type_list_texts[i].setFillColor(functions[i].getColor());
		equation_list_texts[i].setFillColor(functions[i].getColor());
	}
}

void FunctionList::scrollFunctionList(int scroll_amount)
{
	starting_pos_in_functions -= scroll_amount;
	if (starting_pos_in_functions < 0 || functions.size() < num_functions_included)
	{
		starting_pos_in_functions = 0;
	}
	else if (starting_pos_in_functions > functions.size() - num_functions_included)
	{
		starting_pos_in_functions = functions.size() - num_functions_included;
	}

	for (int i = 0; i < num_functions_included; ++i)
	{
		if (i + starting_pos_in_functions >= 0 && i + starting_pos_in_functions < functions.size())
		{
			id_number_list_texts[i].setString(std::to_string(functions[i + starting_pos_in_functions].getIdNumber()));
			type_list_texts[i].setString(functions[i + starting_pos_in_functions].getType());
			equation_list_texts[i].setString(functions[i + starting_pos_in_functions].getTitle() + " = " + functions[i + starting_pos_in_functions].getEquation());
		
			id_number_list_texts[i].setFillColor(functions[i].getColor());
			type_list_texts[i].setFillColor(functions[i].getColor());
			equation_list_texts[i].setFillColor(functions[i].getColor());
		}
		else
		{
			id_number_list_texts[i].setString("");
			type_list_texts[i].setString("");
			equation_list_texts[i].setString("");

			id_number_list_texts[i].setFillColor(sf::Color::White);
			type_list_texts[i].setFillColor(sf::Color::White);
			equation_list_texts[i].setFillColor(sf::Color::White);
		}
	}
}

//getters
sf::Font FunctionList::getFont()
{
	return font;
}

std::string FunctionList::getTitleText()
{
	return title_text.getString().toAnsiString();
}

std::string FunctionList::getIDNumberHeaderText()
{
	return id_number_header_text.getString().toAnsiString();
}

std::string FunctionList::getTypeHeaderText()
{
	return type_header_text.getString().toAnsiString();
}

std::string FunctionList::getEquationHeaderText()
{
	return equation_header_text.getString().toAnsiString();
}