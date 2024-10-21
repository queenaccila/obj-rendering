#include <iostream>
#include "Mesh3D.h"
#include "triangles.h"

sf::Vector2i Mesh3D::clipToScreen(const sf::View& viewport, const glm::vec4& clip) {
	int32_t xs = static_cast<uint32_t>(viewport.getSize().x * (clip.x / clip.w + 1) / 2.0);
	int32_t ys = static_cast<uint32_t>(viewport.getSize().y - viewport.getSize().y * (clip.y / clip.w + 1) / 2.0);

	return sf::Vector2i{ xs, ys };
}

Mesh3D::Mesh3D(std::vector<Vertex3D>&& vertices, std::vector<size_t>&& faces, sf::Color color) : m_vertices(vertices), m_faces(faces), m_color(color) {
}

Mesh3D::Mesh3D(const std::vector<Vertex3D>& vertices, const std::vector<size_t>& faces, sf::Color color) : m_vertices(vertices), m_faces(faces), m_color(color) {
}

void Mesh3D::render(sf::RenderWindow& window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const {
	// TODO: multiply the model, view, and projection matrices together and save the result as the MVP matrix.
	glm::mat4 mvpMatrix = proj * view * model;

	for (size_t i = 0; i < m_faces.size(); i += 3) {
		size_t a = m_faces[i], b = m_faces[i + 1], c = m_faces[i + 2];

		// Construct homogenous coordinates for the 3 vertices of the triangular face.
		auto localA = glm::vec4(m_vertices[a].x, m_vertices[a].y, m_vertices[a].z, 1);
		auto localB = glm::vec4(m_vertices[b].x, m_vertices[b].y, m_vertices[b].z, 1);
		auto localC = glm::vec4(m_vertices[c].x, m_vertices[c].y, m_vertices[c].z, 1);

		// TODO: localA, localB, and localC form the 3 vertices of a triangular face of the mesh.
		// Multiply the MVP matrix by each vertex to transform it to clip space.
		auto clipA = mvpMatrix * localA; // fix this
		auto clipB = mvpMatrix * localB;
		auto clipC = mvpMatrix * localC;

		// Only draw the triangles if they are fully in the screen.
		if (inBounds(clipA) && inBounds(clipB) && inBounds(clipC)) {
			auto drawA = clipToScreen(window.getView(), clipA);
			auto drawB = clipToScreen(window.getView(), clipB);
			auto drawC = clipToScreen(window.getView(), clipC);

			drawTriangle(window, drawA, drawB, drawC, m_color);
		}
		else {
			// Clip the lines and draw them separately.
			// (Skipping this for now.)
		}

	}
}

bool Mesh3D::inBounds(float a) {
	return -1 <= a && a <= 1;
}

bool Mesh3D::inBounds(const glm::vec4& clip) {
	return inBounds(clip.x / clip.w) && inBounds(clip.y / clip.w) && inBounds(clip.z / clip.w);
}

Mesh3D Mesh3D::square(sf::Color color) {
	return Mesh3D(
		{ { -0.5, -0.5, 0 },
		  { -0.5, 0.5, 0 },
		  { 0.5, 0.5, 0 },
		  { 0.5, -0.5, 0 } },
		{ 0, 1, 2, 0, 2, 3 },
		color
	);
}

Mesh3D Mesh3D::cube(sf::Color color) {
	std::vector<Vertex3D> verts = {
		{ 0.5, 0.5, -0.5 },
		{ -0.5, 0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 },
		{ 0.5, 0.5, 0.5 },
		{ -0.5, 0.5, 0.5 },
		{ -0.5, -0.5, 0.5 },
		{ 0.5, -0.5, 0.5 }
	};
	std::vector<size_t> tris = {
		0, 1, 2,
		0, 2, 3,
		4, 0, 3,
		4, 3, 7,
		5, 4, 7,
		5, 7, 6,
		1, 5, 6,
		1, 6, 2,
		4, 5, 1,
		4, 1, 0,
		2, 6, 7,
		2, 7, 3
	};

	return Mesh3D(std::move(verts), std::move(tris), color);
}

// house mesh
Mesh3D Mesh3D::house(sf::Color color) {
	std::vector<Vertex3D> verts = {
		{ 0.5, 0.5, -0.5 }, // initial cube
		{ -0.5, 0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 },
		{ 0.5, 0.5, 0.5 },
		{ -0.5, 0.5, 0.5 },
		{ -0.5, -0.5, 0.5 },
		{ 0.5, -0.5, 0.5 },
		{ 0, 1, 0 } // pyramid point
	};
	std::vector<size_t> tris = {
		0, 1, 2, // initial cube
		0, 2, 3,
		4, 0, 3,
		4, 3, 7,
		5, 4, 7,
		5, 7, 6,
		1, 5, 6,
		1, 6, 2,
		4, 5, 1,
		4, 1, 0,
		2, 6, 7,
		2, 7, 3,
		0, 8, 4, // pyramind point
		5, 8, 1
	};

	return Mesh3D(std::move(verts), std::move(tris), color);
}
