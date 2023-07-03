/*
Project: 2D Grapher
Author: Bennett Lindberg
Tools: C++, SFML
*/

#include <SFML/Graphics.hpp>

#include "WindowData.h"
#include "GraphElements.h"
#include "UserInput.h"
#include "CommandList.h"
#include "FunctionList.h"
#include "Command.h"
#include "Function.h"

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

std::string inputHandler(std::string prompt, sf::RenderWindow& window, WindowData& win_data, GraphElements& graph_elements, sf::RectangleShape graph_border, UserInput& user_input, CommandList& command_list, FunctionList& function_list, std::vector<Function>& functions, FunctionPane& function_pane)
{
	user_input.setDefaultInputText(prompt);
	user_input.setUserInputText(prompt);

	sf::RectangleShape cursor;
	cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
	cursor.setSize(sf::Vector2f(3, 24));
	bool cursor_to_be_drawn = true;
	float delay = 0.5f;
	sf::Clock clock;

	bool finished_entering_input = false;
	while (window.isOpen() && !finished_entering_input)
	{
		bool event_already_processed = false;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				win_data = WindowData(window);
				graph_elements.updateWindowData(win_data);
				Function::updateWindowData(win_data);
				for (Function& function : functions)
				{
					{
						function.updateDepictionUponResize();
					}
				}
				graph_border.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
				graph_border.setSize(sf::Vector2f(win_data.getGraphSize().x, win_data.getGraphSize().y));
				user_input.updateWindowData(win_data);
				command_list.updateWindowData(win_data);
				function_list.updateWindowData(win_data);
				function_pane.updateWindowData(win_data);
				cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				sf::Vector2i local_mouse_coords = sf::Mouse::getPosition(window);
				//command list scroll
				if (local_mouse_coords.x >= win_data.getCommandListOrigin().x &&
					local_mouse_coords.x <= win_data.getCommandListOrigin().x + win_data.getCommandListSize().x &&
					local_mouse_coords.y >= win_data.getCommandListOrigin().y &&
					local_mouse_coords.y <= win_data.getCommandListOrigin().y + win_data.getCommandListSize().y)
				{
					command_list.scrollCommandList(event.mouseWheelScroll.delta);
				}
				//function list scroll
				else if (local_mouse_coords.x >= win_data.getFunctionListOrigin().x &&
					local_mouse_coords.x <= win_data.getFunctionListOrigin().x + win_data.getFunctionListSize().x &&
					local_mouse_coords.y >= win_data.getFunctionListOrigin().y &&
					local_mouse_coords.y <= win_data.getFunctionListOrigin().y + win_data.getFunctionListSize().y)
				{
					command_list.scrollCommandList(event.mouseWheelScroll.delta);
				}
				//graph zooming
				else if (local_mouse_coords.x >= win_data.getGraphOrigin().x &&
					local_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
					local_mouse_coords.y >= win_data.getGraphOrigin().y &&
					local_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
				{
					win_data.setTrueXRange(win_data.getTrueXRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueXRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
					win_data.setTrueYRange(win_data.getTrueYRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueYRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
					graph_elements.updateWindowData(win_data);
					Function::updateWindowData(win_data);
					for (Function& function : functions)
					{
						{
							function.updateValues();
						}
					}
					function_pane.updateWindowData(win_data);
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					break;
				}
				bool mouse_button_released = false;
				sf::Vector2i original_mouse_coords = sf::Mouse::getPosition(window);
				while (window.isOpen() && !mouse_button_released)
				{
					sf::Event event;
					while (window.pollEvent(event))
					{
						switch (event.type)
						{
						case sf::Event::Closed:
						{
							window.close();
							break;
						}
						case sf::Event::MouseButtonReleased:
						{
							mouse_button_released = true;
							break;
						}
						}
					}

					sf::Vector2i new_mouse_coords = sf::Mouse::getPosition(window);

					if (new_mouse_coords.x >= win_data.getGraphOrigin().x &&
						new_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
						new_mouse_coords.y >= win_data.getGraphOrigin().y &&
						new_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
					{
						double x_true_delta = (new_mouse_coords.x - original_mouse_coords.x) * win_data.getXTrueToPixelRatio();
						double y_true_delta = (new_mouse_coords.y - original_mouse_coords.y) * win_data.getYTrueToPixelRatio();

						win_data.setTrueXRange(win_data.getTrueXRange()[0] - x_true_delta, win_data.getTrueXRange()[1] - x_true_delta);
						win_data.setTrueYRange(win_data.getTrueYRange()[0] + y_true_delta, win_data.getTrueYRange()[1] + y_true_delta);
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
						function_pane.updateWindowData(win_data);
					}
					else
					{
						mouse_button_released = true; //moving mouse off graph is equivalent to terminating the graph scroll
					}

					window.clear(sf::Color::Black);

					for (Function& function : functions)
					{
						if (function.isDrawable())
						{
							window.draw(function.getDepiction());
						}
					}

					window.draw(graph_border);

					user_input.drawUserInput(window);
					function_list.drawFunctionList(window);
					command_list.drawCommandList(window);

					function_pane.drawFunctionPane(window);

					window.display();

					original_mouse_coords = new_mouse_coords;
				}
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					finished_entering_input = true;
					event_already_processed = true;
				}
				else if (event.key.code == sf::Keyboard::Backspace)
				{
					user_input.removePreviousUserInputText();
					cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
					event_already_processed = true;
				}
				break;
			case sf::Event::TextEntered:
				if (!event_already_processed)
				{
					user_input.appendToUserInputText(sf::String(event.text.unicode));
					cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
				}
				break;
			}
			}
		}

		window.clear(sf::Color::Black);

		graph_elements.drawGraphElements(window);

		for (Function& function : functions)
		{
			if (function.isDrawable())
			{
				window.draw(function.getDepiction());
			}
		}

		window.draw(graph_border);

		user_input.drawUserInput(window);
		function_list.drawFunctionList(window);
		command_list.drawCommandList(window);

		function_pane.drawFunctionPane(window);

		if (clock.getElapsedTime().asSeconds() >= delay)
		{
			cursor_to_be_drawn = !cursor_to_be_drawn;
			clock.restart();
		}
		if (cursor_to_be_drawn)
		{
			window.draw(cursor);
		}

		window.display();
	}
	user_input.setDefaultInputText("Click \"ctrl\" to enter a command...");
	return user_input.getUserInputText();
}

int main()
{
	srand(time(0));

	//font
	sf::Font consolas_font;
	consolas_font.loadFromFile("Consolas.ttf");

	//window
	sf::RenderWindow window(sf::VideoMode(2000, 1000), "2D Grapher");
	WindowData win_data(window);
	Function::updateWindowData(win_data);

	//graph border
	sf::RectangleShape graph_border;
	graph_border.setFillColor(sf::Color::Transparent);
	graph_border.setOutlineColor(sf::Color::White);
	graph_border.setOutlineThickness(3);
	graph_border.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
	graph_border.setSize(sf::Vector2f(win_data.getGraphSize().x, win_data.getGraphSize().y));

	//graph elements
	GraphElements graph_elements(win_data, consolas_font);

	//user input
	UserInput user_input(win_data, consolas_font);

	//command list
	std::vector<Command> commands;
	
	//general specificity
	commands.push_back(Command("ctrlR", "Reset window size to default", "general"));
	commands.push_back(Command("ctrlCX", "Change window's x dimension", "general"));
	commands.push_back(Command("ctrlCY", "Change window's y dimension", "general"));
	commands.push_back(Command("ctrlF...", "See function-specific commands", "general"));
	commands.push_back(Command("ctrlG...", "See graph-specific commands", "general"));

	//function specificity
	commands.push_back(Command("ctrlFAX", "Add function of x", "function"));
	commands.push_back(Command("ctrlFAY", "Add function of y", "function"));
	commands.push_back(Command("ctrlFED", "Enable drawing for all functions", "function"));
	commands.push_back(Command("ctrlFDD", "Disable drawing for all functions", "function"));
	commands.push_back(Command("ctrlFEX", "Enable drawing for all functions of x", "function"));
	commands.push_back(Command("ctrlFDX", "Disable drawing for all functions of x", "function"));
	commands.push_back(Command("ctrlFEY", "Enable drawing for all functions of y", "function"));
	commands.push_back(Command("ctrlFDY", "Disable drawing for all functions of y", "function"));
	commands.push_back(Command("ctrlFEA", "Enable drawing for all axes", "function"));
	commands.push_back(Command("ctrlFDA", "Disable drawing for all axes", "function"));
	commands.push_back(Command("ctrlF#...", "See commands for a given function", "function"));

	//specific_function specificity
	commands.push_back(Command("ctrlF#R", "Remove function", "specific_function"));
	commands.push_back(Command("ctrlF#ED", "Enable drawing for function", "specific_function"));
	commands.push_back(Command("ctrlF#DD", "Disable drawing for function", "specific_function"));
	commands.push_back(Command("ctrlF#C", "Set function's color", "specific_function"));
	commands.push_back(Command("ctrlF#T", "Set function's title", "specific_function"));
	commands.push_back(Command("ctrlF#E", "Set function's equation", "specific_function"));
	commands.push_back(Command("ctrlF#OI", "Open function's info panel", "specific_function"));
	commands.push_back(Command("ctrlF#CI", "Close function's info panel", "specific_function"));

	//graph specificity
	commands.push_back(Command("ctrlGR", "Reset graph to default zoom and scroll", "graph"));
	commands.push_back(Command("ctrlGRZ", "Reset graph zoom", "graph"));
	commands.push_back(Command("ctrlGRS", "Reset graph scroll", "graph"));
	commands.push_back(Command("ctrlGCX", "Change graph x range", "graph"));
	commands.push_back(Command("ctrlGCY", "Change graph y range", "graph"));
	commands.push_back(Command("ctrlGET", "Enable drawing for all tick marks", "graph"));
	commands.push_back(Command("ctrlGDT", "Disable drawing for all tick marks", "graph"));
	commands.push_back(Command("ctrlGEL", "Enable drawing for all tick labels", "graph"));
	commands.push_back(Command("ctrlGDL", "Disable drawing for all tick labels", "graph"));
	commands.push_back(Command("ctrlGEG", "Enable drawing for all graph lines", "graph"));
	commands.push_back(Command("ctrlGDG", "Disable drawing for all graph lines", "graph"));
	commands.push_back(Command("ctrlGTC", "Set tick mark color", "graph"));
	commands.push_back(Command("ctrlGLC", "Set tick label color", "graph"));
	commands.push_back(Command("ctrlGGC", "Set graph line color", "graph"));

	CommandList command_list(win_data, consolas_font, commands);

	//function list
	std::vector<Function> functions;

	functions.push_back(Function('x', "0", sf::Color::Cyan, "axis"));
	functions.push_back(Function('y', "0", sf::Color::Cyan, "axis"));
	functions.push_back(Function('x', "3*x", sf::Color::Yellow));

	FunctionList function_list(win_data, consolas_font, functions);

	FunctionPane function_pane(win_data, consolas_font, functions);

	//game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				win_data = WindowData(window);
				graph_elements.updateWindowData(win_data);
				Function::updateWindowData(win_data);
				for (Function& function : functions)
				{
					{
						function.updateDepictionUponResize();
					}
				}
				graph_border.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
				graph_border.setSize(sf::Vector2f(win_data.getGraphSize().x, win_data.getGraphSize().y));
				user_input.updateWindowData(win_data);
				command_list.updateWindowData(win_data);
				function_list.updateWindowData(win_data);
				function_pane.updateWindowData(win_data);
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				sf::Vector2i local_mouse_coords = sf::Mouse::getPosition(window);
				//command list scroll
				if (local_mouse_coords.x >= win_data.getCommandListOrigin().x &&
					local_mouse_coords.x <= win_data.getCommandListOrigin().x + win_data.getCommandListSize().x &&
					local_mouse_coords.y >= win_data.getCommandListOrigin().y &&
					local_mouse_coords.y <= win_data.getCommandListOrigin().y + win_data.getCommandListSize().y)
				{
					command_list.scrollCommandList(event.mouseWheelScroll.delta);
				}
				//function list scroll
				else if (local_mouse_coords.x >= win_data.getFunctionListOrigin().x &&
					local_mouse_coords.x <= win_data.getFunctionListOrigin().x + win_data.getFunctionListSize().x &&
					local_mouse_coords.y >= win_data.getFunctionListOrigin().y &&
					local_mouse_coords.y <= win_data.getFunctionListOrigin().y + win_data.getFunctionListSize().y)
				{
					command_list.scrollCommandList(event.mouseWheelScroll.delta);
				}
				//graph zooming
				else if (local_mouse_coords.x >= win_data.getGraphOrigin().x &&
					local_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
					local_mouse_coords.y >= win_data.getGraphOrigin().y &&
					local_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
				{
					win_data.setTrueXRange(win_data.getTrueXRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueXRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
					win_data.setTrueYRange(win_data.getTrueYRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueYRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
					graph_elements.updateWindowData(win_data);
					Function::updateWindowData(win_data);
					for (Function& function : functions)
					{
						{
							function.updateValues();
						}
					}
					function_pane.updateWindowData(win_data);
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					break;
				}
				bool mouse_button_released = false;
				sf::Vector2i original_mouse_coords = sf::Mouse::getPosition(window);
				while (window.isOpen() && !mouse_button_released)
				{
					sf::Event event;
					while (window.pollEvent(event))
					{
						switch (event.type)
						{
						case sf::Event::Closed:
						{
							window.close();
							break;
						}
						case sf::Event::MouseButtonReleased:
						{
							mouse_button_released = true;
							break;
						}
						}
					}

					sf::Vector2i new_mouse_coords = sf::Mouse::getPosition(window);
					
					if (new_mouse_coords.x >= win_data.getGraphOrigin().x &&
						new_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
						new_mouse_coords.y >= win_data.getGraphOrigin().y &&
						new_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
					{
						double x_true_delta = (new_mouse_coords.x - original_mouse_coords.x) * win_data.getXTrueToPixelRatio();
						double y_true_delta = (new_mouse_coords.y - original_mouse_coords.y) * win_data.getYTrueToPixelRatio();

						win_data.setTrueXRange(win_data.getTrueXRange()[0] - x_true_delta, win_data.getTrueXRange()[1] - x_true_delta);
						win_data.setTrueYRange(win_data.getTrueYRange()[0] + y_true_delta, win_data.getTrueYRange()[1] + y_true_delta);
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
						function_pane.updateWindowData(win_data);
					}
					else
					{
						mouse_button_released = true; //moving mouse off graph is equivalent to terminating the graph scroll
					}

					window.clear(sf::Color::Black);

					graph_elements.drawGraphElements(window);

					for (Function& function : functions)
					{
						if (function.isDrawable())
						{
							window.draw(function.getDepiction());
						}
					}

					window.draw(graph_border);

					user_input.drawUserInput(window);
					function_list.drawFunctionList(window);
					command_list.drawCommandList(window);

					function_pane.drawFunctionPane(window);

					window.display();

					original_mouse_coords = new_mouse_coords;
				}
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl)
				{
					user_input.setDefaultInputText("Click \"ctrl\" to enter a command...");
					user_input.setUserInputText("ctrl");

					sf::RectangleShape cursor;
					cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
					cursor.setSize(sf::Vector2f(3, 24));
					bool cursor_to_be_drawn = true;
					float delay = 0.5f;
					sf::Clock clock;

					bool finished_entering_cmd = false;
					while (window.isOpen() && !finished_entering_cmd)
					{
						std::string deduced_specificity = user_input.findCurrentUserInputSpecificity();
						if (command_list.getCurrentSpecificity() != deduced_specificity)
						{
							command_list.setCurrentSpecificity(user_input.findCurrentUserInputSpecificity());
						}
						bool event_already_processed = false;
						sf::Event event;
						while (window.pollEvent(event))
						{
							switch (event.type)
							{
							case sf::Event::Closed:
							{
								window.close();
								break;
							}
							case sf::Event::Resized:
							{
								sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
								window.setView(sf::View(visibleArea));
								win_data = WindowData(window);
								graph_elements.updateWindowData(win_data);
								Function::updateWindowData(win_data);
								for (Function& function : functions)
								{
									{
										function.updateDepictionUponResize();
									}
								}
								graph_border.setPosition(win_data.getGraphOrigin().x, win_data.getGraphOrigin().y);
								graph_border.setSize(sf::Vector2f(win_data.getGraphSize().x, win_data.getGraphSize().y));
								user_input.updateWindowData(win_data);
								command_list.updateWindowData(win_data);
								function_list.updateWindowData(win_data);
								function_pane.updateWindowData(win_data);
								cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
								break;
							}
							case sf::Event::MouseWheelScrolled:
							{
								sf::Vector2i local_mouse_coords = sf::Mouse::getPosition(window);
								//command list scroll
								if (local_mouse_coords.x >= win_data.getCommandListOrigin().x &&
									local_mouse_coords.x <= win_data.getCommandListOrigin().x + win_data.getCommandListSize().x &&
									local_mouse_coords.y >= win_data.getCommandListOrigin().y &&
									local_mouse_coords.y <= win_data.getCommandListOrigin().y + win_data.getCommandListSize().y)
								{
									command_list.scrollCommandList(event.mouseWheelScroll.delta);
								}
								//function list scroll
								else if (local_mouse_coords.x >= win_data.getFunctionListOrigin().x &&
									local_mouse_coords.x <= win_data.getFunctionListOrigin().x + win_data.getFunctionListSize().x &&
									local_mouse_coords.y >= win_data.getFunctionListOrigin().y &&
									local_mouse_coords.y <= win_data.getFunctionListOrigin().y + win_data.getFunctionListSize().y)
								{
									command_list.scrollCommandList(event.mouseWheelScroll.delta);
								}
								//graph zooming
								else if (local_mouse_coords.x >= win_data.getGraphOrigin().x &&
									local_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
									local_mouse_coords.y >= win_data.getGraphOrigin().y &&
									local_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
								{
									win_data.setTrueXRange(win_data.getTrueXRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueXRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
									win_data.setTrueYRange(win_data.getTrueYRange()[0] * std::pow(2.0, -event.mouseWheelScroll.delta), win_data.getTrueYRange()[1] * std::pow(2.0, -event.mouseWheelScroll.delta));
									graph_elements.updateWindowData(win_data);
									Function::updateWindowData(win_data);
									for (Function& function : functions)
									{
										{
											function.updateValues();
										}
									}
									function_pane.updateWindowData(win_data);
								}
								break;
							}
							case sf::Event::MouseButtonPressed:
							{
								if (event.mouseButton.button == sf::Mouse::Middle)
								{
									break;
								}
								bool mouse_button_released = false;
								sf::Vector2i original_mouse_coords = sf::Mouse::getPosition(window);
								while (window.isOpen() && !mouse_button_released)
								{
									sf::Event event;
									while (window.pollEvent(event))
									{
										switch (event.type)
										{
										case sf::Event::Closed:
										{
											window.close();
											break;
										}
										case sf::Event::MouseButtonReleased:
										{
											mouse_button_released = true;
											break;
										}
										}
									}

									sf::Vector2i new_mouse_coords = sf::Mouse::getPosition(window);

									if (new_mouse_coords.x >= win_data.getGraphOrigin().x &&
										new_mouse_coords.x <= win_data.getGraphOrigin().x + win_data.getGraphSize().x &&
										new_mouse_coords.y >= win_data.getGraphOrigin().y &&
										new_mouse_coords.y <= win_data.getGraphOrigin().y + win_data.getGraphSize().y)
									{
										double x_true_delta = (new_mouse_coords.x - original_mouse_coords.x) * win_data.getXTrueToPixelRatio();
										double y_true_delta = (new_mouse_coords.y - original_mouse_coords.y) * win_data.getYTrueToPixelRatio();

										win_data.setTrueXRange(win_data.getTrueXRange()[0] - x_true_delta, win_data.getTrueXRange()[1] - x_true_delta);
										win_data.setTrueYRange(win_data.getTrueYRange()[0] + y_true_delta, win_data.getTrueYRange()[1] + y_true_delta);
										graph_elements.updateWindowData(win_data);
										Function::updateWindowData(win_data);
										for (Function& function : functions)
										{
											{
												function.updateValues();
											}
										}
										function_pane.updateWindowData(win_data);
									}
									else
									{
										mouse_button_released = true; //moving mouse off graph is equivalent to terminating the graph scroll
									}

									window.clear(sf::Color::Black);

									graph_elements.drawGraphElements(window);

									for (Function& function : functions)
									{
										if (function.isDrawable())
										{
											window.draw(function.getDepiction());
										}
									}

									window.draw(graph_border);

									user_input.drawUserInput(window);
									function_list.drawFunctionList(window);
									command_list.drawCommandList(window);

									function_pane.drawFunctionPane(window);

									window.display();

									original_mouse_coords = new_mouse_coords;
								}
								break;
							}
							case sf::Event::KeyPressed:
							{
								if (event.key.code == sf::Keyboard::Enter)
								{
									finished_entering_cmd = true;
									event_already_processed = true;
								}
								else if (event.key.code == sf::Keyboard::Backspace)
								{
									user_input.removePreviousUserInputText();
									if (user_input.getUserInputText() == "Click \"ctrl\" to enter a command...")
									{
										finished_entering_cmd = true;
									}
									event_already_processed = true;
									cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
								}
								break;
							case sf::Event::TextEntered:
								if (!event_already_processed)
								{
									user_input.appendToUserInputText(sf::String(event.text.unicode));
									cursor.setPosition(user_input.getUserInputTextRef().getGlobalBounds().left + user_input.getUserInputTextRef().getGlobalBounds().width, win_data.getUserInputOrigin().y + 33);
								}
								break;
							}
							}
						}

						window.clear(sf::Color::Black);

						graph_elements.drawGraphElements(window);

						for (Function& function : functions)
						{
							if (function.isDrawable())
							{
								window.draw(function.getDepiction());
							}
						}

						window.draw(graph_border);

						user_input.drawUserInput(window);
						function_list.drawFunctionList(window);
						command_list.drawCommandList(window);

						function_pane.drawFunctionPane(window);

						if (clock.getElapsedTime().asSeconds() >= delay)
						{
							cursor_to_be_drawn = !cursor_to_be_drawn;
							clock.restart();
						}
						if (cursor_to_be_drawn)
						{
							window.draw(cursor);
						}

						window.display();
					}
				}
				if (command_list.getCurrentSpecificity() == "general")
				{
					if (user_input.getUserInputText() == "ctrlR") //Reset window size to default
					{
						window.setSize(sf::Vector2u(2000, 1000));
					}
					else if (user_input.getUserInputText() == "ctrlCX") //Change window's x dimension
					{
						int new_x = std::stoi(inputHandler("Enter a new x pixel dimension:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						window.setSize(sf::Vector2u(new_x, window.getSize().y));
					}
					else if (user_input.getUserInputText() == "ctrlCY") //Change window's y dimension
					{
						int new_y = std::stoi(inputHandler("Enter a new y pixel dimension:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						window.setSize(sf::Vector2u(window.getSize().x, new_y));
					}
				}
				else if (command_list.getCurrentSpecificity() == "function")
				{
					if (user_input.getUserInputText() == "ctrlFAX") //Add function of x
					{
						std::string new_equation = inputHandler("Enter the function's equation:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane);
						int red = rand() % 256;
						int green = rand() % 256;
						int blue = rand() % 256;
						Function temp('x', new_equation, sf::Color(red, green, blue));
						functions.push_back(temp);
						function_list.appendToFunctionList(functions[functions.size() - 1]);
					}
					else if (user_input.getUserInputText() == "ctrlFAY") //Add function of y
					{
						std::string new_equation = inputHandler("Enter the function's equation:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane);
						int red = rand() % 256;
						int green = rand() % 256;
						int blue = rand() % 256;
						Function temp('y', new_equation, sf::Color(red, green, blue));
						functions.push_back(temp);
						function_list.appendToFunctionList(functions[functions.size() - 1]);
					}
					else if (user_input.getUserInputText() == "ctrlFED") //Enable drawing for all functions
					{
						for (Function& funct : functions)
						{
							funct.setDrawableStatus(true);
						}
					}
					else if (user_input.getUserInputText() == "ctrlFDD") //Disable drawing for all functions
					{
						for (Function& funct : functions)
						{
							funct.setDrawableStatus(false);
						}
					}
					else if (user_input.getUserInputText() == "ctrlFEX") //Enable drawing for all functions of x
					{
						for (Function& funct : functions)
						{
							if (funct.getFunctionOf() == 'x')
							{
								funct.setDrawableStatus(true);
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrFDX") //Disable drawing for all functions of x
					{
						for (Function& funct : functions)
						{
							if (funct.getFunctionOf() == 'x')
							{
								funct.setDrawableStatus(false);
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlFEY") //Enable drawing for all functions of y
					{
						for (Function& funct : functions)
						{
							if (funct.getFunctionOf() == 'y')
							{
								funct.setDrawableStatus(true);
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlFDY") //Disable drawing for all functions of y
					{
						for (Function& funct : functions)
						{
							if (funct.getFunctionOf() == 'y')
							{
								funct.setDrawableStatus(false);
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlFEA") //Enable drawing for all axes
					{
						for (Function& funct : functions)
						{
							if (funct.getClassification() == "axis")
							{
								funct.setDrawableStatus(true);
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlFDA") //Disable drawing for all axes
					{
						for (Function& funct : functions)
						{
							if (funct.getClassification() == "axis")
							{
								funct.setDrawableStatus(false);
							}
						}
					}
				}
				else if (command_list.getCurrentSpecificity() == "specific_function")
				{
					//get requested id number of function
					std::string requested_funct_id_str = "";
					for (const char c : user_input.getUserInputText())
					{
						if (isdigit(c))
						{
							requested_funct_id_str.push_back(c);
						}
					}
					int requested_funct_id = std::stoi(requested_funct_id_str);

					//get function of the requested id number
					Function* requested_funct_ptr = nullptr;
					for (Function& funct : functions)
					{
						if (funct.getIdNumber() == requested_funct_id)
						{
							requested_funct_ptr = &funct;
						}
					}

					//get remainder of command
					std::string specific_cmd = "";
					for (const char c : user_input.getUserInputText().substr(5))
					{
						if (!isdigit(c))
						{
							specific_cmd.push_back(c);
						}
					}

					if (specific_cmd == "R") //Remove requested function
					{
						function_list.removeFromFunctionList(*requested_funct_ptr);
						std::vector<Function> temp;
						for (Function& funct : functions)
						{
							if (funct.getIdNumber() != requested_funct_id)
							{
								temp.push_back(funct);
							}
						}
						functions = temp;
					}
					else if (specific_cmd == "ED") //Enable drawing for requested function
					{
						requested_funct_ptr->setDrawableStatus(true);
					}
					else if (specific_cmd == "DD") //Disable drawing for requested function
					{
						requested_funct_ptr->setDrawableStatus(false);
					}
					else if (specific_cmd == "C") //Set requested function's color
					{
						int red = std::stoi(inputHandler("Enter a red value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int green = std::stoi(inputHandler("Enter a green value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int blue = std::stoi(inputHandler("Enter a blue value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						requested_funct_ptr->setColor(sf::Color(red, green, blue));

						for (Function funct : functions) {
							if (funct.getIdNumber() == requested_funct_ptr->getIdNumber()) {
								funct.setColor(sf::Color(red, green, blue));
							}
						}

						function_list.replaceFunctionList(functions);

						function_list.updateWindowData(win_data);
					}
					else if (specific_cmd == "T") //Set requested function's title
					{
						std::string new_title = inputHandler("Enter a new title:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane);
						requested_funct_ptr->setTitle(new_title);

						for (Function funct : functions) {
							if (funct.getIdNumber() == requested_funct_ptr->getIdNumber()) {
								funct.setTitle(new_title);
							}
						}

						function_list.replaceFunctionList(functions);

						function_list.updateWindowData(win_data);
					}
					else if (specific_cmd == "E") //Set requested function's equation
					{
						std::string new_equation = inputHandler("Enter a new equation:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane);
						requested_funct_ptr->setEquation(new_equation);

						for (Function funct : functions) {
							if (funct.getIdNumber() == requested_funct_ptr->getIdNumber()) {
								funct.setEquation(new_equation);
							}
						}

						function_list.replaceFunctionList(functions);

						function_list.updateWindowData(win_data);
					}
					else if (specific_cmd == "OI") //Open requested function's info panel
					{
						function_pane.setActiveFunctionID(requested_funct_ptr->getIdNumber());
					}
					else if (specific_cmd == "CI") //Close requested function's info panel
					{
						function_pane.setActiveFunctionID(0);
					}
				}
				else if (command_list.getCurrentSpecificity() == "graph")
				{
					if (user_input.getUserInputText() == "ctrlGR") //Reset graph to default zoom and scroll
					{
						win_data.setTrueXRange(WindowData::default_true_x_range[0], WindowData::default_true_x_range[1]);
						win_data.setTrueYRange(WindowData::default_true_y_range[0], WindowData::default_true_y_range[1]);
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlGRZ") //Reset graph zoom
					{
						double original_x_dist = std::abs(WindowData::default_true_x_range[0]) + std::abs(WindowData::default_true_x_range[1]);
						double original_y_dist = std::abs(WindowData::default_true_y_range[0]) + std::abs(WindowData::default_true_y_range[1]);

						double current_x_center = (win_data.getTrueXRange()[0] + win_data.getTrueXRange()[1]) / 2.0;
						double current_y_center = (win_data.getTrueYRange()[0] + win_data.getTrueYRange()[1]) / 2.0;

						win_data.setTrueXRange(current_x_center - (original_x_dist / 2.0), current_x_center + (original_x_dist / 2.0));
						win_data.setTrueYRange(current_y_center - (original_y_dist / 2.0), current_y_center + (original_y_dist / 2.0));
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlGRS") //Reset graph scroll
					{
						double current_x_dist = std::abs(win_data.getTrueXRange()[0]) + std::abs(win_data.getTrueXRange()[1]);
						double current_y_dist = std::abs(win_data.getTrueYRange()[0]) + std::abs(win_data.getTrueYRange()[1]);

						double original_x_center = (WindowData::default_true_x_range[0] + WindowData::default_true_x_range[1]) / 2.0;
						double original_y_center = (WindowData::default_true_y_range[0] + WindowData::default_true_y_range[1]) / 2.0;

						win_data.setTrueXRange(original_x_center - (current_x_dist / 2.0), original_x_center + (current_x_dist / 2.0));
						win_data.setTrueYRange(original_y_center - (current_y_dist / 2.0), original_y_center + (current_y_dist / 2.0));
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlGCX") //Change graph x range
					{
						double new_min = std::stod(inputHandler("Enter a new true minimum x:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						double new_max = std::stod(inputHandler("Enter a new true maximum x:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						win_data.setTrueXRange(new_min, new_max);
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlGCY") //Change graph y range
					{
						double new_min = std::stod(inputHandler("Enter a new true minimum y:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						double new_max = std::stod(inputHandler("Enter a new true maximum y:", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						win_data.setTrueYRange(new_min, new_max);
						graph_elements.updateWindowData(win_data);
						Function::updateWindowData(win_data);
						for (Function& function : functions)
						{
							{
								function.updateValues();
							}
						}
					}
					else if (user_input.getUserInputText() == "ctrlGET") //Enable drawing for all tick marks
					{
						graph_elements.setTicksDrawability(true);
					}
					else if (user_input.getUserInputText() == "ctrlGDT") //Disable drawing for all tick marks
					{
						graph_elements.setTicksDrawability(false);
					}
					else if (user_input.getUserInputText() == "ctrlGEL") //Enable drawing for all tick labels
					{
						graph_elements.setTickLabelsDrawability(true);
					}
					else if (user_input.getUserInputText() == "ctrlGDL") //Disable drawing for all tick labels
					{
						graph_elements.setTickLabelsDrawability(false);
					}
					else if (user_input.getUserInputText() == "ctrlGEG") //Enable drawing for all graph lines
					{
						graph_elements.setGraphLinesDrawability(true);
					}
					else if (user_input.getUserInputText() == "ctrlGDG") //Disable drawing for all graph lines
					{
						graph_elements.setGraphLinesDrawability(false);
					}
					else if (user_input.getUserInputText() == "ctrlGTC") //Set tick mark color
					{
						int red = std::stoi(inputHandler("Enter a red value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int green = std::stoi(inputHandler("Enter a green value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int blue = std::stoi(inputHandler("Enter a blue value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						graph_elements.setTicksColor(sf::Color(red, green, blue));
					}
					else if (user_input.getUserInputText() == "ctrlGLC") //Set tick label color
					{
						int red = std::stoi(inputHandler("Enter a red value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int green = std::stoi(inputHandler("Enter a green value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int blue = std::stoi(inputHandler("Enter a blue value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						graph_elements.setTickLabelsColor(sf::Color(red, green, blue));
					}
					else if (user_input.getUserInputText() == "ctrlGGC") //Set graph line color
					{
						int red = std::stoi(inputHandler("Enter a red value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int green = std::stoi(inputHandler("Enter a green value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						int blue = std::stoi(inputHandler("Enter a blue value (0-255):", window, win_data, graph_elements, graph_border, user_input, command_list, function_list, functions, function_pane));
						graph_elements.setGraphLinesColor(sf::Color(red, green, blue));
					}
				}
				command_list.setCurrentSpecificity("general");
				user_input.resetUserInputText();
				break;
			}
			}
		}

		window.clear(sf::Color::Black);

		graph_elements.drawGraphElements(window);

		for (Function& function : functions)
		{
			if (function.isDrawable())
			{
				window.draw(function.getDepiction());
			}
		}

		window.draw(graph_border);

		user_input.drawUserInput(window);
		function_list.drawFunctionList(window);
		command_list.drawCommandList(window);

		function_pane.drawFunctionPane(window);

		window.display();
	}
}