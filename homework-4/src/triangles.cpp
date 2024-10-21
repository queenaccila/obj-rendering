#include "triangles.h"
#include "lines.h"

void drawTriangle(sf::RenderWindow& window, sf::Vector2i a, sf::Vector2i b,
	sf::Vector2i c, sf::Color color) {
	drawLine(window, a, b, color);
	drawLine(window, a, c, color);
	drawLine(window, b, c, color);
}