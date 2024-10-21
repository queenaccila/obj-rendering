#pragma once
#include "Mesh3D.h"
#include "Object3D.h"
#include <filesystem>
#include <assimp/scene.h>
Mesh3D fromAssimpMesh(const aiMesh* mesh, size_t attributes);
Object3D assimpLoad(const std::filesystem::path& path);
