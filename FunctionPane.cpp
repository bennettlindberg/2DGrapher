#include "FunctionPane.h"

FunctionPane::FunctionPane(const WindowData& new_win_data, const sf::Font& new_font, const std::vector<Function>& new_functions) : win_data(new_win_data), font(new_font), functions(new_functions)
{
	//header
	header.setFillColor(sf::Color::Magenta);
	header.setCharacterSize(24);
	header.setFont(font);
	header.setStyle(sf::Text::Bold | sf::Text::Underlined);
	header.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 30));
	header.setString("Function #0 Information Pane");

	//traits and values
	sf::Text temp_trait_text;
	temp_trait_text.setFillColor(sf::Color::Yellow);
	temp_trait_text.setCharacterSize(20);
	temp_trait_text.setFont(font);
	temp_trait_text.setStyle(sf::Text::Bold);
	temp_trait_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 70));

	sf::Text temp_value_text;
	temp_value_text.setFillColor(sf::Color::Green);
	temp_value_text.setCharacterSize(20);
	temp_value_text.setFont(font);
	temp_value_text.setStyle(sf::Text::Bold);
	temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70));
	temp_value_text.setString("");
	
	std::vector<std::string> trait_texts;
	trait_texts.push_back("ID Number:");
	trait_texts.push_back("Function of:");
	trait_texts.push_back("Title:");
	trait_texts.push_back("Equation:");
	trait_texts.push_back("Color:");
	trait_texts.push_back("Drawable:");

	for (int i = 0; i < 6; ++i)
	{
		temp_trait_text.setString(trait_texts[i]);
		temp_trait_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 70 + i * 30));
		traits.push_back(temp_trait_text);
		temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70 + i * 30));
		values.push_back(temp_value_text);
	}

	//graph concealer
	graph_concealer.setFillColor(sf::Color::Black);
	graph_concealer.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
	graph_concealer.setSize(sf::Vector2f(win_data.getGraphSize().x, values[5].getPosition().y - win_data.getGraphOrigin().y + 60));

	//border line
	border_line.setFillColor(sf::Color::White);
	border_line.setPosition(win_data.getGraphOrigin().x, graph_concealer.getPosition().y + graph_concealer.getSize().y);
	border_line.setSize(sf::Vector2f(win_data.getGraphSize().x, 3));
}

void FunctionPane::updateWindowData(const WindowData& new_data)
{
	win_data = new_data;

	Function* funct_of_id = nullptr;
	for (Function& funct : functions)
	{
		if (funct.getIdNumber() == active_function_id)
		{
			funct_of_id = &funct;
		}
	}

	//header
	header.setFillColor(sf::Color::Magenta);
	header.setCharacterSize(24);
	header.setFont(font);
	header.setStyle(sf::Text::Bold | sf::Text::Underlined);
	header.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 30));
	if (funct_of_id == nullptr)
	{
		header.setString("Function #0 Information Pane");
	}
	else
	{
		header.setString("Function #" + std::to_string(funct_of_id->getIdNumber()) + " Information Pane");
	}

	//traits and values
	sf::Text temp_trait_text;
	temp_trait_text.setFillColor(sf::Color::Yellow);
	temp_trait_text.setCharacterSize(20);
	temp_trait_text.setFont(font);
	temp_trait_text.setStyle(sf::Text::Bold);
	temp_trait_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 70));

	sf::Text temp_value_text;
	temp_value_text.setFillColor(sf::Color::Green);
	temp_value_text.setCharacterSize(20);
	temp_value_text.setFont(font);
	temp_value_text.setStyle(sf::Text::Bold);
	temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70));

	std::vector<std::string> trait_texts;
	trait_texts.push_back("ID Number:");
	trait_texts.push_back("Function of:");
	trait_texts.push_back("Title:");
	trait_texts.push_back("Equation:");
	trait_texts.push_back("Color:");
	trait_texts.push_back("Drawable:");

	std::vector<std::string> value_texts;
	if (funct_of_id == nullptr)
	{
		value_texts.push_back("");
		value_texts.push_back("");
		value_texts.push_back("");
		value_texts.push_back("");
		value_texts.push_back("");
		value_texts.push_back("");
	}
	else
	{
		value_texts.push_back(std::to_string(funct_of_id->getIdNumber()));
		value_texts.push_back(std::to_string(funct_of_id->getFunctionOf()));
		value_texts.push_back(funct_of_id->getTitle());
		value_texts.push_back(funct_of_id->getEquation());
		value_texts.push_back(std::to_string(funct_of_id->getColor().toInteger()));
		value_texts.push_back(std::to_string(funct_of_id->isDrawable()));
	}

	for (int i = 0; i < 6; ++i)
	{
		temp_trait_text.setString(trait_texts[i]);
		temp_value_text.setString(value_texts[i]);
		temp_trait_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + 30, win_data.getGraphOrigin().y + 70 + i * 30));
		temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70 + i * 30));
		traits.push_back(temp_trait_text);
		values.push_back(temp_value_text);
	}

	//graph concealer
	graph_concealer.setFillColor(sf::Color::Black);
	graph_concealer.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
	graph_concealer.setSize(sf::Vector2f(win_data.getGraphSize().x, values[5].getPosition().y - win_data.getGraphOrigin().y + 60));

	//border line
	border_line.setFillColor(sf::Color::White);
	border_line.setPosition(win_data.getGraphOrigin().x, graph_concealer.getPosition().y + graph_concealer.getSize().y);
	border_line.setSize(sf::Vector2f(win_data.getGraphSize().x, 3));
}

void FunctionPane::drawFunctionPane(sf::RenderWindow& window)
{
	if (active_function_id != 0)
	{
		window.draw(graph_concealer);
		window.draw(border_line);
		window.draw(header);
		for (int i = 0; i < 6; ++i)
		{
			window.draw(traits[i]);
			window.draw(values[i]);
		}
	}
}

void FunctionPane::setActiveFunctionID(int new_id)
{
	active_function_id = new_id;

	if (new_id != 0)
	{
		values.clear();

		sf::Text temp_value_text;
		temp_value_text.setFillColor(sf::Color::Green);
		temp_value_text.setCharacterSize(20);
		temp_value_text.setFont(font);
		temp_value_text.setStyle(sf::Text::Bold);
		temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70));

		Function* funct_of_id = nullptr;
		for (Function& funct : functions)
		{
			if (funct.getIdNumber() == active_function_id)
			{
				funct_of_id = &funct;
			}
		}

		header.setString("Function #" + std::to_string(funct_of_id->getIdNumber()) + " Information Pane");

		std::vector<std::string> value_texts;
		value_texts.push_back(std::to_string(funct_of_id->getIdNumber()));
		value_texts.push_back(funct_of_id->getFunctionOf() == 'x' ? "x" : "y");
		value_texts.push_back(funct_of_id->getTitle());
		value_texts.push_back(funct_of_id->getTitle() + " = " + funct_of_id->getEquation());
		value_texts.push_back(std::to_string(funct_of_id->getColor().toInteger()));
		value_texts.push_back(funct_of_id->isDrawable() == true ? "true" : "false");

		for (int i = 0; i < 6; ++i)
		{
			temp_value_text.setPosition(sf::Vector2f(win_data.getGraphOrigin().x + win_data.getGraphSize().x / 4, win_data.getGraphOrigin().y + 70 + i * 30));
			temp_value_text.setString(value_texts[i]);
			values.push_back(temp_value_text);
		}

		//graph concealer
		graph_concealer.setFillColor(sf::Color::Black);
		graph_concealer.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
		graph_concealer.setSize(sf::Vector2f(win_data.getGraphSize().x, values[5].getPosition().y - win_data.getGraphOrigin().y + 60));
	
		//border line
		border_line.setFillColor(sf::Color::White);
		border_line.setPosition(win_data.getGraphOrigin().x, graph_concealer.getPosition().y + graph_concealer.getSize().y);
		border_line.setSize(sf::Vector2f(win_data.getGraphSize().x, 3));
	}
}

int FunctionPane::getActiveFunctionID()
{
	return active_function_id;
}