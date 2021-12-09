#pragma once
#include <chrono>
#include <type_traits>

/// <summary>
/// A simple timer class
/// </summary>
/// <typeparam name="RealType">must be a floating point type</typeparam>
template <typename RealType>
class cTimer
{
	// This forces RealType to be either float or double
	static_assert(std::is_floating_point<RealType>::value, "cTimer can only be instantiated with floating point types");
	// could also do something like this, but it doesn't have nice and easy to understand errors:
	/*using value_type = typename std::enable_if<
		std::is_same<float, RealType>::value ||
		std::is_same<double, RealType>::value,
		RealType
	>::type;*/
public:
	using time_point = std::chrono::high_resolution_clock::time_point;
	using duration = std::chrono::duration<RealType>;

	/// <summary>
	/// Constructor
	/// </summary>
	cTimer();

	/// <summary>
	/// Destructor
	/// </summary>
	~cTimer() {}

	/// <summary>
	/// Starts or Restarts the timer.
	/// </summary>
	void Start();

	/// <summary>
	/// Get the time passed since the most recent call to Split(), or Start().
	/// Does not reset the timer.
	/// </summary>
	/// <returns>The total time passed</returns>
	RealType Split();

	/// <summary>
	/// Get the split time and the total elapsed time simultaneously
	/// </summary>
	/// <param name="splitTimeOut"></param>
	/// <param name="totalElapsedTimeOut"></param>
	void Split(RealType& splitTimeOut, RealType& totalElapsedTimeOut);

	/// <summary>
	/// Get the total time passed since Start() was called.
	/// </summary>
	/// <returns>The total time passed</returns>
	RealType Elapsed();

private:
	/// <summary>
	/// The time this timer was created, or Start() was called.
	/// </summary>
	time_point mStartTime;

	/// <summary>
	/// The time the timer was created, or the most recent time Split() was called.
	/// </summary>
	time_point mStopTime;

	/// <summary>
	/// Helper to get right now
	/// </summary>
	/// <returns>Time point for now</returns>
	inline time_point GetNow() { return std::chrono::high_resolution_clock::now(); }

	/// <summary>
	/// Helper method to get the duration between two time points.
	/// Having this as a method helps with proper casting to avoid compiler warnings.
	/// </summary>
	/// <param name="t0">start</param>
	/// <param name="t1">end</param>
	/// <returns>The duration from start to end</returns>
	duration GetDuration(const time_point& t0, const time_point& t1) { return t1 - t0; }
};

template <typename RealType>
inline cTimer<RealType>::cTimer()
{
	this->mStartTime = GetNow();
	this->mStopTime = this->mStartTime;
}

template <typename RealType>
inline void cTimer<RealType>::Start()
{
	this->mStartTime = GetNow();
	this->mStopTime = this->mStartTime;
}

template <typename RealType>
inline RealType cTimer<RealType>::Split()
{
	time_point now = GetNow();
	duration dur = GetDuration(mStopTime, now);
	mStopTime = now;
	return dur.count();
}

template<typename RealType>
inline void cTimer<RealType>::Split(RealType& splitTimeOut, RealType& totalElapsedTimeOut)
{
	time_point now = GetNow();
	duration dur = GetDuration(mStopTime, now);
	mStopTime = now;
	splitTimeOut = dur.count();
	duration elapsedDur = GetDuration(mStartTime, now);
	totalElapsedTimeOut = elapsedDur.count();
}

template <typename RealType>
inline RealType cTimer<RealType>::Elapsed()
{
	return GetDuration(mStartTime, GetNow()).count();
}