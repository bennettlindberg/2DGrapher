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
1. Two-dimensional coordinate plane: displays all visible functions in a specific horizontal and vertical range
2. Input field: used for entering controls and data
3. Command list: itemizes available controls
4. Function list: itemizes existing functions
5. Function information pane: (opened using controls) displays extended information about a specific function

<img width="1070" alt="overall_window_panes" src="https://github.com/bennettlindberg/2DGrapher/assets/54961751/bbd417f6-d39f-4e54-8ff9-5c51f67e9468">

### Functions

The set of functions that can be plotted using the tool is limited to those containing only the operations listed below:
- `+` (addition)
- `-` (subtraction)
- `*` (multiplication)
- `/` (division)
- `^` (exponentiation)

Note the following regarding function equations:
- Operations can be used an unlimited number of times in a function's equation
- Functions are parsed per the usual PEMDAS order of operations
- All numbers zero through nine, the `.` character for creating decimal values, and parentheses are supported
- When utilizing multiplication, explicit use of the `*` character is required

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

The 2DGrapher window can be adjusted in height and width to fit many screen sizes. Changing the size of the window is achieved either by dragging the corners of the window or by using the built-in resizing controls:

https://github.com/bennettlindberg/2DGrapher/assets/54961751/65eb96f4-f0dc-4d2b-ac18-3a7e92e17355

Adding functions to the graph window is performed using the `ctrl+F+A+_` control, with `_` being one of `X` or `Y`. After adding a function to the screen, some of the function's specifications are viewable in the function list, and the rest of the information can be viewed by opening the function's information panel:

https://github.com/bennettlindberg/2DGrapher/assets/54961751/d962ce08-46f8-4419-95be-3ce928539810

The graph of each visible function can be viewed in the coordinate plane. Clicking and dragging on the graph will cause it to scroll. The graph can also be zoomed in or out using either a mouse's scroll wheel or a trackpad:

https://github.com/bennettlindberg/2DGrapher/assets/54961751/2e5a8dff-a851-4404-a876-b2eb02d245bf

Both the coordinate plane and functions can be customized in numerous ways. Various controls allow for changing colors, equations, visibility, and more:

*If customizations are not immediately viewable, try scrolling or zooming the coordinate plane to trigger a re-render*

https://github.com/bennettlindberg/2DGrapher/assets/54961751/1667dbf7-05b0-48ed-bc5f-66133cf852e6

## Usage

The 2DGrapher application was developed using the 32-bit version of SFML 2.5 for Windows. To run the project, create a Microsoft Visual Studio Visual C++ project and configure the project per [these instructions](https://www.sfml-dev.org/tutorials/2.5/start-vc.php). Clone the files in this repository to the project and build a solution by clicking the green run button in the toolbar.
