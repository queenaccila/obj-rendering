#include "AssimpImport.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <iostream>

Mesh3D fromAssimpMesh(const aiMesh* mesh, size_t attributes) {
	std::vector<Vertex3D> vertices;

	// TODO: fill in this vertices list, by iterating over each element of 
	// the mVertices field of the aiMesh pointer. Each element of mNumVertices
	// has x, y, and z values that you can use to construct a Vertex3D object.
	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		auto& meshVertex = mesh->mVertices[i];
		// See above.

		// using push_back to add to a group of vertices
		vertices.push_back(Vertex3D{ meshVertex.x, meshVertex.y, meshVertex.z });

	}

	std::vector<size_t> faces;
	// TODO: fill in the faces list, by iterating over each element of
	// the mFaces field of the aiMesh pointer. Each element of mFaces
	// has an mIndices list, which will have three elements of its own at 
	// [0], [1], and [2]. Each of those should be pushed individually onto 
	// the faces list.
	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		auto& meshFace = mesh->mFaces[i];
		// See above.

		faces.push_back(meshFace.mIndices[0]);
		faces.push_back(meshFace.mIndices[1]);
		faces.push_back(meshFace.mIndices[2]);
	}

	return Mesh3D(std::move(vertices), std::move(faces), sf::Color::White);
}

Object3D assimpLoad(const std::filesystem::path& path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path.string(), aiProcessPreset_TargetRealtime_MaxQuality);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cerr << importer.GetErrorString() << std::endl;
		throw std::runtime_error("Could not load assimp asset file");
	}
	else {
		auto ret = Object3D(std::make_shared<Mesh3D>(fromAssimpMesh(scene->mMeshes[0], 3)));
		return ret;
	}
}
