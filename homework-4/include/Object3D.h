#pragma once
#include <memory>
#include <glm/ext.hpp>
#include "Mesh3D.h"

/**
 * @brief Represents an object placed in a 3D scene.
*/
class Object3D {
private:
	// The object's mesh.
	std::shared_ptr<Mesh3D> m_mesh;

	// The object's position, orientation, and scale in world space.
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_scale;

	// Computes the local->world transformation matrix.
	glm::mat4 buildModelMatrix() const;

public:
	// No default constructor; you must have a mesh to initialize an object.
	Object3D() = delete;

	/**
	 * @brief Constructs an Object3D at the origin of world space using the given mesh.
	*/
	Object3D(std::shared_ptr<Mesh3D>&& mesh);

	// Simple accessors.
	const glm::vec3& getPosition() const;
	const glm::vec3& getOrientation() const;
	const glm::vec3& getScale() const;

	// Simple mutators. These functions *override* the current position, rotation, or scale.
	void setPosition(const glm::vec3& position);

	/**
	 * @brief Sets the object's orientation angles.
	 * @param orientation pitch, yaw, and roll angles in radians.
	*/
	void setOrientation(const glm::vec3& orientation);
	void setScale(const glm::vec3& scale);

	// Transformations. These functions *incrementally update* the current position, rotation, or scale.
	void move(const glm::vec3& offset);

	/**
	 * @brief Rotates the object's current orientation angles.
	 * @param rotation pitch, yaw, and roll angles in radians, to apply to the object's current orientation.
	*/
	void rotate(const glm::vec3& rotation);

	void grow(const glm::vec3& growth);

	/**
	 * @brief Renders the object to a RenderWindow, using the given view and projection matrices.
	*/
	void render(sf::RenderWindow& window, const glm::mat4& view, const glm::mat4& proj) const;
};