#include "lines.h"
#include <SFML/Graphics.hpp>
#include <array>


void drawPixel(sf::RenderWindow& window, sf::Vector2u position, sf::Color color) {
	sf::Vertex pixel[1] = {
		sf::Vertex(sf::Vector2f(position.x, position.y), color)
	};
	window.draw(pixel, 1, sf::Points);
}

// This version of drawLine uses SFML to more-efficiently draw the line, instead of using repeated
// calls to our drawPixel.
// SFML uses Bresenham's algorithm like us; but they avoid the overhead of multiple "draw a pixel"
// calls because they have low-level access to the framebuffer.
// You can replace this method with your Bresenham's algorithms from Homework 1; the demo will run
// slower, but it will more truly be *your* own work.
void drawLine(sf::RenderWindow& window, sf::Vector2i start, sf::Vector2i end, sf::Color color) {
	std::array<sf::Vertex, 2> points = {
		sf::Vertex(sf::Vector2f(start.x, start.y), color),
		sf::Vertex(sf::Vector2f(end.x, end.y), color)
	};
	window.draw(points.data(), 2, sf::Lines);
}
