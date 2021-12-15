#pragma once
#include <external_includes.h>
#include <string>
#include <vector>

namespace nGraphics
{
	struct sSubMeshLoadingInfo
	{
		sSubMeshLoadingInfo() : MeshIndex(0) {}
		sSubMeshLoadingInfo(const std::string& name, unsigned int meshIndex = 0)
			: Name(name), MeshIndex(meshIndex) {}
		std::string Name;
		unsigned int MeshIndex;
	};
	struct sMeshLoadingInfo
	{
		//sMeshLoadingInfo() : DoResize(false), Extents(1.f, 1.f, 1.f), MaintainDimensions(true) {}
		sMeshLoadingInfo() : DoResize(false),DoRotate(false), Rotation(1.0f), Extents(1.f, 1.f, 1.f), MaintainDimensions(true) {}

		std::string File;
		std::vector<sSubMeshLoadingInfo> SubMeshes;
		void AddSubMesh(const std::string& name, unsigned int meshIndex = 0) { SubMeshes.push_back(sSubMeshLoadingInfo(name, meshIndex)); }
		void AddSubMesh(const sSubMeshLoadingInfo& subMeshInfo) { SubMeshes.push_back(subMeshInfo); }
		//Used for resizing
		glm::vec3 Extents;
		// Checks if any resizing needs to be done
		bool DoResize;
		//Uses the minumum values from Extents if you want the dimensions to stay the same
		bool MaintainDimensions;

		//Rotation bits
		bool DoRotate;
		glm::mat3 Rotation;

		//Needs the triangleData bool?
	};
}
