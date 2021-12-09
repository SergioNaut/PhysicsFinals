#pragma once
#include <physics/iParticleContactGenerator.h>

namespace nPhysics
{
	/// <summary>
	/// This is a 'dumb' gound plane (y is always 'up' <0,1,0>)
	/// Set the groundHeight value in the constructor and contacts will be created for
	/// particles that have y values below that ground height.
	/// </summary>
	class cGroundPlaneParticleContactGenerator : public iParticleContactGenerator
	{
		float mGroundHeight;
	public:
		cGroundPlaneParticleContactGenerator(float groundHeight);

		cGroundPlaneParticleContactGenerator() = delete;
		cGroundPlaneParticleContactGenerator(const cGroundPlaneParticleContactGenerator& other) = delete;
		cGroundPlaneParticleContactGenerator& operator=(const cGroundPlaneParticleContactGenerator& other) = delete;

		virtual ~cGroundPlaneParticleContactGenerator();
		/// <summary>
		/// Fills the given contact structure with the generated contact(s).
		/// The contact pointer should point to the first available contact in the contact array,
		/// where limit is the maximum number of contacts in the array that can be written to.
		/// The method returns the number of contacts generated.
		/// </summary>
		/// <param name="contact"></param>
		/// <param name="limit"></param>
		/// <param name="particles"></param>
		/// <returns></returns>
		virtual size_t AddContact(cParticleContact* contact, size_t limit, std::vector<cParticle*>& particles) const;
	};
}