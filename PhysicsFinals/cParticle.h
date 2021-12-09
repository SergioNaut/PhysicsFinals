#pragma once
#include "extern_includes.h"

namespace nPhysics
{
	class cParticle
	{
	private:
		// Linear position of the particle in world space
		glm::vec3 mPosition;
		// Linear velocity of the particle in world space
		glm::vec3 mVelocity;
		// Linear acceleration of the particle in world space
		glm::vec3 mAcceleration;
		// Inverse mass
		float mInverseMass;
		// Externally applied forces accumulated during a time step
		glm::vec3 mAppliedForce;
		// Damping is applied to linear motion
		// Required to remove energy added through numerical instability of integration
		// Also generally used as an overall "friction" for the particle
		float mDamping;
	protected:
		bool mIsAlive;
		float mAge;
	public:
		cParticle(float mass, const glm::vec3& position);
		virtual ~cParticle();

		cParticle() = delete;
		cParticle(cParticle& other) = delete;
		cParticle& operator=(cParticle& other) = delete;

		void SetDamping(float damping);
		float GetDamping() const;

		float GetAge() const;

		bool GetIsAlive() const;
		void SetIsAlive(bool alive);

		void SetMass(float mass);
		float GetMass() const;
		float GetInverseMass() const;

		bool IsStaticObject() const;

		glm::vec3 GetPosition() const;
		void GetPosition(glm::vec3& position);
		void SetPosition(const glm::vec3& position);

		glm::vec3 GetVelocity() const;
		void GetVelocity(glm::vec3& velocity);
		void SetVelocity(const glm::vec3& velocity);

		glm::vec3 GetAcceleration() const;
		void GetAcceleration(glm::vec3& acceleration);
		void SetAcceleration(const glm::vec3& acceleration);

		void ApplyForce(const glm::vec3& force);
		void ApplyImpulse(const glm::vec3& impulse);

		void ClearAppliedForces();

		virtual void Integrate(float deltaTime);

	};
}