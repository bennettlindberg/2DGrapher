#include "CommandList.h"

//constructor
CommandList::CommandList(const WindowData& new_win_data, const sf::Font& new_font, const std::vector<Command>& new_commands) : win_data(new_win_data), font(new_font), all_commands(new_commands)
{
	//specificity
	current_specificity = "general";

	//update current specific command list using new specificity
	commands_of_specificity.clear();
	for (Command& command : all_commands)
	{
		if (command.getSpecificity() == current_specificity)
		{
			commands_of_specificity.push_back(command);
		}
	}

	//title
	title_text.setFillColor(sf::Color::Black);
	title_text.setCharacterSize(24);
	title_text.setFont(font);
	title_text.setStyle(sf::Text::Bold);
	title_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y - 1));
	title_text.setString("Command List");

	title_box.setFillColor(sf::Color::White);
	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getCommandListOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	//header
	name_header_text.setFillColor(sf::Color::Red);
	name_header_text.setCharacterSize(24);
	name_header_text.setFont(font);
	name_header_text.setStyle(sf::Text::Regular);
	name_header_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y + 30 - 1));
	name_header_text.setString("Input");

	description_header_text.setFillColor(sf::Color::Red);
	description_header_text.setCharacterSize(24);
	description_header_text.setFont(font);
	description_header_text.setStyle(sf::Text::Regular);
	description_header_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6 + (win_data.getCommandListSize().x * 0.35), win_data.getCommandListOrigin().y + 30 - 1));
	description_header_text.setString("Description");

	header_border.setFillColor(sf::Color::Transparent);
	header_border.setOutlineColor(sf::Color::White);
	header_border.setOutlineThickness(3);
	header_border.setPosition(win_data.getCommandListOrigin().x, win_data.getCommandListOrigin().y + 30);
	header_border.setSize(sf::Vector2f(win_data.getCommandListSize().x, 30 - 1));

	//list
	int leftover_list_y_space = win_data.getCommandListSize().y - 60;
	num_commands_included = (leftover_list_y_space - 1) / 30;

	list_border.setFillColor(sf::Color::Transparent);
	list_border.setOutlineColor(sf::Color::White);
	list_border.setOutlineThickness(3);
	list_border.setPosition(win_data.getCommandListOrigin().x, win_data.getCommandListOrigin().y + 30 + 30 + 1);
	list_border.setSize(sf::Vector2f(win_data.getCommandListSize().x, leftover_list_y_space - 1));
	
	name_list_texts.clear();
	description_list_texts.clear();

	sf::Text temp_text;
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(24);
	temp_text.setFont(font);
	temp_text.setStyle(sf::Text::Regular);
	temp_text.setString("");
	for (int i = 0; i < num_commands_included; ++i)
	{
		temp_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y + 30 + 30 + (i * 30) - 1));
		name_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6 + (win_data.getCommandListSize().x * 0.35), win_data.getCommandListOrigin().y + 30 + 30 + (i * 30) - 1));
		description_list_texts.push_back(temp_text);
	}

	for (int i = 0; i < num_commands_included && i < commands_of_specificity.size(); ++i)
	{
		name_list_texts[i].setString(commands_of_specificity[i].getInput());
		description_list_texts[i].setString(commands_of_specificity[i].getDescription());

		name_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
		description_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
	}
}

//window-related methods
void CommandList::updateWindowData(const WindowData& new_data)
{
	win_data = new_data;

	//update sizes and positions in relation to new window data
	//title
	title_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y - 1));

	title_box.setPosition(title_text.getGlobalBounds().left - 3, win_data.getCommandListOrigin().y);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));

	//header
	name_header_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y + 30 - 1));
	description_header_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6 + (win_data.getCommandListSize().x * 0.35), win_data.getCommandListOrigin().y + 30 - 1));

	header_border.setPosition(win_data.getCommandListOrigin().x, win_data.getCommandListOrigin().y + 30);
	header_border.setSize(sf::Vector2f(win_data.getCommandListSize().x, 30 - 1));

	//list
	int leftover_list_y_space = win_data.getCommandListSize().y - 60;
	num_commands_included = (leftover_list_y_space - 1) / 30;

	list_border.setPosition(win_data.getCommandListOrigin().x, win_data.getCommandListOrigin().y + 30 + 30 + 1);
	list_border.setSize(sf::Vector2f(win_data.getCommandListSize().x, leftover_list_y_space - 1));

	name_list_texts.clear();
	description_list_texts.clear();

	sf::Text temp_text;
	temp_text.setFillColor(sf::Color::White);
	temp_text.setCharacterSize(24);
	temp_text.setFont(font);
	temp_text.setStyle(sf::Text::Regular);
	temp_text.setString("");
	for (int i = 0; i < num_commands_included; ++i)
	{
		temp_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6, win_data.getCommandListOrigin().y + 30 + 30 + (i * 30) - 1));
		name_list_texts.push_back(temp_text);

		temp_text.setPosition(sf::Vector2f(win_data.getCommandListOrigin().x + 6 + (win_data.getCommandListSize().x * 0.35), win_data.getCommandListOrigin().y + 30 + 30 + (i * 30) - 1));
		description_list_texts.push_back(temp_text);
	}

	starting_pos_in_commands = 0;

	for (int i = 0; i < num_commands_included && i < commands_of_specificity.size(); ++i)
	{
		name_list_texts[i].setString(commands_of_specificity[i].getInput());
		description_list_texts[i].setString(commands_of_specificity[i].getDescription());

		name_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
		description_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
	}
}

void CommandList::drawCommandList(sf::RenderWindow& window)
{
	window.draw(title_box);
	window.draw(title_text);

	window.draw(header_border);
	window.draw(name_header_text);
	window.draw(description_header_text);

	window.draw(list_border);
	for (const sf::Text& text : name_list_texts)
	{
		window.draw(text);
	}
	for (const sf::Text& text : description_list_texts)
	{
		window.draw(text);
	}
}

//setters
void CommandList::setFont(const sf::Font& new_font)
{
	font = new_font;
}

void CommandList::setTitleText(const std::string& new_text)
{
	title_text.setString(new_text);
	title_box.setSize(sf::Vector2f(title_text.getGlobalBounds().width + 6, 30));
}

void CommandList::setNameHeaderText(const std::string& new_text)
{
	name_header_text.setString(new_text);
}

void CommandList::setDescriptionHeaderText(const std::string& new_text)
{
	description_header_text.setString(new_text);
}

void CommandList::setCurrentSpecificity(const std::string& new_specificity)
{
	current_specificity = new_specificity;

	//update current specific command list using new specificity
	commands_of_specificity.clear();
	for (Command &command : all_commands)
	{
		if (command.getSpecificity() == current_specificity)
		{
			commands_of_specificity.push_back(command);
		}
	}

	//update command list display
	for (int i = 0; i < num_commands_included; ++i)
	{
		name_list_texts[i].setString("");
		description_list_texts[i].setString("");
	}

	starting_pos_in_commands = 0;

	for (int i = 0; i < num_commands_included && i < commands_of_specificity.size(); ++i)
	{
		name_list_texts[i].setString(commands_of_specificity[i].getInput());
		description_list_texts[i].setString(commands_of_specificity[i].getDescription());

		name_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
		description_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
	}
}

void CommandList::replaceCommandList(const std::vector<Command>& new_commands)
{
	all_commands = new_commands;
	setCurrentSpecificity(current_specificity);
}

void CommandList::appendToCommandList(const Command& new_command)
{
	all_commands.push_back(new_command);

	for (int i = 0; i < num_commands_included; ++i)
	{
		name_list_texts[i].setString("");
		description_list_texts[i].setString("");
	}

	starting_pos_in_commands = commands_of_specificity.size() - num_commands_included;
	if (starting_pos_in_commands < 0)
	{
		starting_pos_in_commands = 0;
	}

	for (int i = 0; i < num_commands_included && i < commands_of_specificity.size(); ++i)
	{
		name_list_texts[i].setString(commands_of_specificity[i + starting_pos_in_commands].getInput());
		description_list_texts[i].setString(commands_of_specificity[i + starting_pos_in_commands].getDescription());

		name_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
		description_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
	}
}

void CommandList::scrollCommandList(int scroll_amount)
{  
	starting_pos_in_commands -= scroll_amount;
	if (starting_pos_in_commands < 0 || commands_of_specificity.size() < num_commands_included)
	{
		starting_pos_in_commands = 0;
	}
	else if (starting_pos_in_commands > commands_of_specificity.size() - num_commands_included)
	{
		starting_pos_in_commands = commands_of_specificity.size() - num_commands_included;
	}

	for (int i = 0; i < num_commands_included; ++i)
	{
		if (i + starting_pos_in_commands >= 0 && i + starting_pos_in_commands < commands_of_specificity.size())
		{
			name_list_texts[i].setString(commands_of_specificity[i + starting_pos_in_commands].getInput());
			description_list_texts[i].setString(commands_of_specificity[i + starting_pos_in_commands].getDescription());

			name_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
			description_list_texts[i].setFillColor(getSpecificityAssociatedColor(commands_of_specificity[i].getSpecificity()));
		}
		else
		{
			name_list_texts[i].setString("");
			description_list_texts[i].setString("");

			name_list_texts[i].setFillColor(sf::Color::White);
			description_list_texts[i].setFillColor(sf::Color::White);
		}
	}
}

//getters
sf::Font CommandList::getFont()
{
	return font;
}

std::string CommandList::getTitleText()
{
	return title_text.getString().toAnsiString();
}

std::string CommandList::getNameHeaderText()
{
	return name_header_text.getString().toAnsiString();
}

std::string CommandList::getDescriptionHeaderText()
{
	return description_header_text.getString().toAnsiString();
}

std::string CommandList::getCurrentSpecificity()
{
	return current_specificity;
}

sf::Color CommandList::getSpecificityAssociatedColor(std::string the_specificity)
{
	if (the_specificity == "general")
	{
		return sf::Color(128, 235, 122);
	}
	else if (the_specificity == "function")
	{
		return sf::Color(255, 54, 121);
	}
	else if (the_specificity == "specific_function")
	{
		return sf::Color(120, 255, 255);
	}
	else if (the_specificity == "graph")
	{
		return sf::Color(255, 201, 41);
	}
	else
	{
		return sf::Color::White;
	}
}
