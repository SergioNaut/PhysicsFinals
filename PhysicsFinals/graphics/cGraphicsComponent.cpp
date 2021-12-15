#include <graphics/cGraphicsComponent.h>
#include <graphics/graphics.h>

namespace nGraphics
{
	cGraphicsComponent::cGraphicsComponent(const sGraphicsComponentDef& def)
	{
		if (def.Mesh != "")
		{
			SetMesh(def.Mesh);
		}
		if (def.TexCubeMap != "")
		{
			mVars.CubeMap = gTextureManager->GetTextureByName(def.TexCubeMap);
			mVars.IsCubeMap = true;
		}
		if (def.TexDiffuse != "")
		{
			SetDiffuseTexture(def.TexDiffuse);
		}
		mVars.ModelMatrix = glm::eulerAngleXYZ(def.Rotation.x, def.Rotation.y, def.Rotation.z);
		mVars.ModelMatrix = glm::translate(mVars.ModelMatrix, def.Position);
		mVars.ModelMatrix = glm::scale(mVars.ModelMatrix, def.Scale);
	}
	cGraphicsComponent::cGraphicsComponent(): mMesh(0){}

	cGraphicsComponent::~cGraphicsComponent()
	{
		mMesh = 0;
	}

	bool cGraphicsComponent::SetMesh(const std::string& meshName)
	{
		mMesh = nGraphics::gMeshManager->GetMeshByName(meshName);
		return mMesh != 0;
	}

	bool cGraphicsComponent::SetDiffuseTexture(const std::string& texName, float factor)
	{
		mVars.TexDiffuse = nGraphics::gTextureManager->GetTextureByName(texName);
		if (mVars.TexDiffuse)
		{
			mVars.TexFactors.x = factor;
			return true;
		}
		else
		{
			mVars.TexFactors.x = 0.f;
			return false;
		}
	}

	void cGraphicsComponent::Render()
	{
		if (!mMesh) return;
		nGraphics::Render(mMesh, mVars);
	}

	//TODO: Add CylinderRenderer
	//Kinda ugly to just set this here, but I hope it works
	void cGraphicsComponent::RenderCylinder(const glm::vec3& from, const glm::vec3& to, float radius, const glm::vec4& color, glm::vec3 cylinderAxis)
	{
	
		glm::vec3 separation = to - from;
		float length = glm::length(separation);

		//TODO: Comment better
		//I'll believe the example's logic and pray it works
		glm::vec3 diagonal(2.0f / glm::sqrt(3));
		//cylinderAxis can be (0.0f,0.0f,1.0f)?
		glm::vec3 diameterScaling = diagonal - cylinderAxis * glm::dot(diagonal, cylinderAxis);
		diameterScaling = glm::normalize(diameterScaling) * radius;
		glm::vec3 scaleVector = diameterScaling + cylinderAxis * length * 0.5f;

		glm::mat4 matScale = glm::scale(scaleVector);
		//Function from the professor's extra glm functions
		glm::mat4 matRotation = glm::rotation_from_to(cylinderAxis, separation / length);
		glm::mat4 matTranslation = glm::translate((from + to) * 0.5f);

		glm::mat4 matrix = matTranslation * matRotation * matScale;
		this->GetVars()->ModelColor = color;
		this->GetVars()->ModelMatrix = matrix;
		this->Render();
	}
}