#pragma once
/// This file expects to be in a subfolder of glm, acting as a custom extension
/// glm/
///     detail/
///     ext/
///     gtc/
///     gtx/
///     simd/
///     custom/
///            rotation_from_to.h
///
#include "../vec3.hpp"
#include "../mat4x4.hpp"
#include "../geometric.hpp"
#include "../ext/matrix_transform.hpp"

namespace glm
{
	/// <summary>
	/// Generate a rotation matrix representing a rotation from one vector to another.
	/// The length of each vector may vary.
	/// Zero-length and co-linear vectors are not handled gracefully.
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns>A rotation matrix</returns>
	inline mat4 rotation_from_to(const glm::vec3& from, const glm::vec3& to)
	{
		glm::vec3 v = cross(from, to);
		float angle = acos(dot(to, from) / (length(to) * length(from)));
		return rotate(glm::mat4(1.f), angle, normalize(v));
	}

	/// <summary>
	/// Generate a rotation matrix representing a rotation from one vector to another
	/// This function is optimized to assume the input vectors are already normalized.
	/// Use @rotation_from_to if the vectors 'from' and 'to' may not be unit lengths.
	/// Zero-length and co-linear vectors are not handled gracefully.
	/// </summary>
	/// <param name="from">a normalized vector</param>
	/// <param name="to">a normalized vector</param>
	/// <returns>A rotation matrix</returns>
	inline mat4 rotation_from_to_opt(const glm::vec3& from, const glm::vec3& to)
	{
		glm::vec3 v = cross(from, to);
		float angle = acos(dot(to, from));
		return rotate(glm::mat4(1.f), angle, v);
	}
}