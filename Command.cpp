#include "Command.h"

//constructor
Command::Command(const std::string& new_input, const std::string& new_description, const std::string& new_specificity) : input(new_input), description(new_description), specificity(new_specificity) {}

//setters
void Command::setInput(const std::string &new_input)
{
	input = new_input;
}

void Command::setDescription(const std::string &new_description)
{
	description = new_description;
}

void Command::setSpecificity(const std::string &new_specificity)
{
	specificity = new_specificity;
}

//getters
std::string Command::getInput()
{
	return input;
}

std::string Command::getDescription()
{
	return description;
}

std::string Command::getSpecificity()
{
	return specificity;
}