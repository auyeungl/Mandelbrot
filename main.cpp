// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width / 4;
	int pixelHeight = VideoMode::getDesktopMode().height / 4;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

	ComplexPlane plane(pixelWidth, pixelHeight);


	bool update = true;
	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Mouse mouse;
		Event event;
		while (window.pollEvent(event))
		{
			plane.setMouseLocation(mouse.getPosition(window));
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;


					plane.setCenter(mouse.getPosition(window));
					plane.zoomIn();
					update = true;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					plane.setCenter(mouse.getPosition(window));
					plane.zoomOut();
					update = true;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (update)
		{
			plane.updateRender();
			update = false;

		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		//Handle font initialization
		Font comic;
		comic.loadFromFile("comic.ttf");

		//Handle the text initialization + setting
		Text text;
		text.setPosition(10, 10);
		text.setCharacterSize(20);
		text.setFont(comic);
		text.setFillColor(Color::White);
		plane.loadText(text);
		window.draw(text);

		window.draw(plane);

		window.display();

		window.clear();
	}
}