#pragma once

#include <string>

class Command
{
public:
	//constructor
	Command(const std::string &new_input, const std::string &new_description, const std::string &new_specificity);

	//setters
	void setInput(const std::string &new_input);
	void setDescription(const std::string &new_description);
	void setSpecificity(const std::string &new_specificity);

	//getters
	std::string getInput();
	std::string getDescription();
	std::string getSpecificity();

private:
	//data members
	std::string input;
	std::string description;
	std::string specificity; //general, graph, function, specific_function
};