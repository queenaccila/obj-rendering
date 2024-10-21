#pragma once
#include <SFML/Graphics.hpp>
#include <glm/ext.hpp>

/**
 * @brief One vertex in 3D space.
*/
struct Vertex3D {
	float_t x;
	float_t y;
	float_t z;

	Vertex3D(float_t a, float_t b, float_t c) : x(a), y(b), z(c) {}
};

/**
 * @brief A collection of vertices and triangular faces represnting a 3D surface.
*/
class Mesh3D {
private:
	std::vector<Vertex3D> m_vertices;
	std::vector<size_t> m_faces;
	sf::Color m_color;

	static sf::Vector2i clipToScreen(const sf::View& viewport, const glm::vec4& clip);
	static bool inBounds(float a);
	static bool inBounds(const glm::vec4& clip);

public:
	Mesh3D() = delete;

	/**
	 * @brief Constructs a Mesh3D by taking ownership of existing vectors of vertices and faces.
	 * @param color the color to draw the mesh.
	*/
	Mesh3D(std::vector<Vertex3D>&& vertices, std::vector<size_t>&& faces, sf::Color color);

	/**
	 * @brief Construcst a Mesh3D by copying existing vectors of vertices and faces.
	 * @param color the color to draw the mesh.
	*/
	Mesh3D(const std::vector<Vertex3D>& vertices, const std::vector<size_t>& faces, sf::Color color);

	/**
	 * @brief Constructs a 1x1 square centered at the origin in world space.
	*/
	static Mesh3D square(sf::Color color);
	/**
	 * @brief Constructs a 1x1x1 cube centered at the origin in world space.
	*/
	static Mesh3D cube(sf::Color color);

	// builds a house (based on the cube)
	static Mesh3D house(sf::Color color);

	/**
	 * @brief Renders the mesh to the given context.
	 * @param model the local->world model transformation matrix.
	 * @param view the world->view camera matrix.
	 * @param proj the view->clip projection matrix.
	*/
	void render(sf::RenderWindow& window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const;

};
