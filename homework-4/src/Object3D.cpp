#include "Object3D.h"

glm::mat4 Object3D::buildModelMatrix() const {
	// Initialize the model matrix as the identity matrix.
	auto model = glm::mat4(1);

	// TODO: initialize your own mat4 objects to represent scale/yaw/pitch/roll/translate
	// matrices and then multiply them together, writing the expression as you would in mathematics.
	// Remember that the transformations must be applied in the correct order:
	//    scale, yaw, pitch, roll, translate

	// scale martix
	glm::mat4 scaleMatrix = glm::mat4(m_scale.x, 0, 0, 0,
		0, m_scale.y, 0, 0,
		0, 0, m_scale.z, 0,
		0, 0, 0, 1);
	
	// ROTATION
	// yaw
	float cosYaw = cos(m_orientation.y);
	float sinYaw = sin(m_orientation.y);
	// yaw matrix
	glm::mat4 yawMatrix = glm::mat4(cosYaw, 0, -sinYaw, 0,
		0, 1, 0, 0,
		sinYaw, 0, cosYaw, 0,
		0, 0, 0, 1);

	// pitch
	float cosPitch = cos(m_orientation.x);
	float sinPitch = sin(m_orientation.x);
	// pitch matrix
	glm::mat4 pitchMatrix = glm::mat4(1, 0, 0, 0,
		0, cosPitch, sinPitch, 0,
		0, -sinPitch, cosPitch, 0,
		0, 0, 0, 1);

	// roll
	float cosRoll = cos(m_orientation.z);
	float sinRoll = sin(m_orientation.z);
	// roll matrix
	glm::mat4 rollMatrix = glm::mat4(cosRoll, sinRoll, 0, 0,
		-sinRoll, cosRoll, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	// calculation for rotation matrices
	glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

	// translate matrix
	glm::mat4 translateMatrix = glm::mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		m_position.x, m_position.y, m_position.z, 1);

	// In the end, assign the computed model matrix to m_modelMatrix.
	model = translateMatrix * yawMatrix * pitchMatrix * rollMatrix * scaleMatrix;

	return model;
}

Object3D::Object3D(std::shared_ptr<Mesh3D>&& mesh) : m_mesh(mesh), m_position(), m_orientation(), m_scale(1.0) {
}

const glm::vec3& Object3D::getPosition() const {
	return m_position;
}

const glm::vec3& Object3D::getOrientation() const {
	return m_orientation;
}

const glm::vec3& Object3D::getScale() const {
	return m_scale;
}

void Object3D::setPosition(const glm::vec3& position) {
	m_position = position;
}

void Object3D::setOrientation(const glm::vec3& orientation) {
	m_orientation = orientation;
}

void Object3D::setScale(const glm::vec3& scale) {
	m_scale = scale;
}

void Object3D::move(const glm::vec3& offset) {
	m_position = m_position + offset;
}

void Object3D::rotate(const glm::vec3& rotation) {
	m_orientation = m_orientation + rotation;
}

void Object3D::grow(const glm::vec3& growth) {
	m_scale = m_scale * growth;
}

void Object3D::render(sf::RenderWindow& window, const glm::mat4& view, const glm::mat4& proj) const {
	auto modelMatrix = buildModelMatrix();
	m_mesh->render(window, modelMatrix, view, proj);
}
