# 2DGrapher
*An application for quickly generating graphs of mathematical functions in the two-dimensional coordinate plane.*

- **Author:** Bennett Lindberg
- **Date:** Summer 2022 (with minor modifications made Summer 2023)
- **Technologies:** C++, SFML

## Overview

The 2DGrapher application is a tool capable of plotting mathematical functions in the two-dimensional coordinate plane. 
Beyond plotting, the application supports editing, hiding, revealing, and inspecting graphed mathematical functions, and
features a customizable, zoomable, and scrollable viewing pane.

### Interface

The application consists of multiple interface areas used for displaying and editing the graph's information. The main viewing areas are:
1. Two-dimensional coordinate plane: displays all visible functions in a specific horitontal and vertical range
2. Input field: used for entering controls and data
3. Control list: itemizes available controls
4. Function list: itemizes existing functions
5. Function information panel: (open using controls) displays extended information about a specific function

***........IMAGE........***

### Functions

The set of functions that can be plotted using the tool is limited to those containing only the operations listed below:
- `+` (addition)
- `-` (subtraction)
- `*` (multiplication)
- `/` (division)
- `^` (exponentation)

Note the following regarding function equations:
- Operations can be used an unlimited number of times in a function's equation
- Functions are parsed per the usual PEMDAS order of operations
- All numbers zero through nine, the `.` character for creating decimal values, and parentheses are supported
- When utilizing multiplication, an explicit use of the `*` character is required

### Controls

The application is controlled using *controls*, which are inputted in the window's control input field. 
Each control is entered in a 'sticky keys'-esque manner, with each control's keys being pressed sequentially.
The supported controls illustrate the application's array of features and are categorized as follows:

#### Main Controls
- `ctrl+R`: Reset the window size to default (2000px wide, 1000px tall)
- `ctrl+C+X`: Change the window's horizontal (x) dimension
- `ctrl+C+Y`: Change the window's vertical (y) dimension

#### Function Controls (General)
- `ctrl+F+A+X`: Add a function of x (e.g. f(x))
- `ctrl+F+A+Y`: Add a function of y (e.g. f(y))
- `ctrl+F+E+D`: Enable drawing for all functions
- `ctrl+F+D+D`: Disable drawing for all functions
- `ctrl+F+E+X`: Enable drawing for all functions of x
- `ctrl+F+D+X`: Disable drawing for all functions of x
- `ctrl+F+E+Y`: Enable drawing for all functions of y
- `ctrl+F+D+Y`: Disable drawing for all functions of y
- `ctrl+F+E+A`: Enable drawing for all axes
- `ctrl+F+D+A`: Disable drawing for all axes

#### Function Controls (Specific)
*'#' refers to the id number of the function in question*
- `ctrl+F+#+R`: Remove this function
- `ctrl+F+#+E+D`: Enable drawing for this function
- `ctrl+F+#+D+D`: Disable drawing for this function
- `ctrl+F+#+C`: Set this function's color
- `ctrl+F+#+T`: Set this function's title
- `ctrl+F+#+E`: Set this function's equation
- `ctrl+#+O+I`: Open this function's information panel
- `ctrl+#+C+I`: Close this function's information panel

#### Graph Controls
- `ctrl+G+R`: Reset the graph zoom and scroll to default (horizontal range: \[-50, 50\], vertical range: \[-50, 50\], centered on the origin)
- `ctrl+G+R+Z`: Reset the graph zoom to default (the magnitude of the horizontal and vertical ranges becomes 100)
- `ctrl+G+R+S`: Reset the graph scroll to default (the graph becomes centered on the origin)
- `ctrl+G+C+X`: Change the graph's horizontal range
- `ctrl+G+C+Y`: Change the graph's vertical range
- `ctrl+G+E+T`: Enable drawing for all tick marks
- `ctrl+G+D+T`: Disable drawing for all tick marks
- `ctrl+G+E+L`: Enable drawing for all numerical tick labels
- `ctrl+G+D+L`: Disable drawing for all numerical tick labels
- `ctrl+G+E+G`: Enable drawing for all graph lines
- `ctrl+G+D+G`: Disable drawing for all graph lines
- `ctrl+G+T+C`: Set tick mark color
- `ctrl+G+L+C`: Set numerical tick label color
- `ctrl+G+G+C`: Set graph line color

## Examples

Text
