#include <SFML/Graphics.hpp>
#include <iostream>

#include "Mesh3D.h"
#include "Object3D.h"

#include <memory>
#include <glm/ext.hpp>
#include <vector>

#include <iostream>

#include "AssimpImport.h"

#define LOG_FPS

// A Scene stores a list of objects to be rendered.
struct Scene {
	std::vector<Object3D> objects;
};

// Constructs a scene of a single cube.
Scene cube() {
	auto cube = Object3D(std::make_shared<Mesh3D>(Mesh3D::cube(sf::Color::Red)));
	// The cube in local space is at the origin; move it away from the camera so we can see it.
	cube.move(glm::vec3(0, 0, -3));

	return Scene{
		{ cube }
	};
}

// makes scene for the house
Scene house() {
	auto cube = Object3D(std::make_shared<Mesh3D>(Mesh3D::house(sf::Color::Red)));
	// The cube in local space is at the origin; move it away from the camera so we can see it.
	cube.move(glm::vec3(0, 0, -3));

	return Scene{
		{ cube }
	};
}

// loads bunny model
Scene bunny() {
	// only absolute path made it render properly
	auto bunny = assimpLoad("C:\\Users\\Helen\\ComputerGraphics\\obj-rendering\\homework-4\\models\\bunny.obj");
	std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;

	bunny.grow(glm::vec3(20, 20, 20));
	bunny.move(glm::vec3(-1, -1.5, -2));

	return Scene{
		{ bunny }
	};
}

// extra test to run miku model
Scene miku() {
	// only absolute path made it render properly
	auto miku = assimpLoad("C:\\Users\\Helen\\ComputerGraphics\\obj-rendering\\homework-4\\models\\HatsuneMiku.obj");

	miku.grow(glm::vec3(1.15, 1.15, 1.15));
	miku.move(glm::vec3(-2.4, -2.2, -2.5));

	return Scene{
		{ miku }
	};
}

int main() {
	sf::RenderWindow window{ sf::VideoMode{1200, 800}, "Homework 4" };
	sf::Clock c;

	// Construct the scene.
	//Scene myScene = cube();
	//Scene myScene = house();
	Scene myScene = bunny();
	//Scene myScene = miku(); // extra test to run a different model

	// For convenience, create a local reference to a specific object in the scene.
	Object3D& obj = myScene.objects[0];

	// Use GLM to create a perspective-projection matrix with a 45deg FOVY.
	auto proj = glm::perspective(glm::radians(45.0), (double)window.getSize().x / window.getSize().y, 0.1, 100.0);

	// Use an identity matrix for the camera, which places it at (0, 0, 0) looking down the negative z axis.
	auto view = glm::mat4(1);
	// TODO: learn how to use glm::lookAt, to place the camera at (3, 0, 3) looking at the origin.

	// lookat matrix
	glm::mat4 lookMatrix = glm::lookAt(glm::vec3(3, 0, 3), // camera position
		glm::vec3(0, 0, 0), // target position
		glm::vec3(0, 1, 0)); // up direction

	view = lookMatrix;

	auto last = c.getElapsedTime();
	while (window.isOpen()) {
		// Check for events.
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}
		
#ifdef LOG_FPS
		// FPS calculation.
		auto now = c.getElapsedTime();
		auto diff = now - last;
		std::cout << 1 / diff.asSeconds() << " FPS " << std::endl;
		last = now;
#endif
		// Render the scene.
		window.clear();
		obj.rotate(glm::vec3(0, 0.01, 0));

		for (auto& o : myScene.objects) {
			o.render(window, view, proj);
		}
		window.display();
	}

	return 0;
}


