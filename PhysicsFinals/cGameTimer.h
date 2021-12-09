#pragma once
#include "cGameTimer.h"
template <typename RealType>
class cGameTimer;

/// <summary>
/// TODO: is this class a better place to have min/max delta times? probably...
/// </summary>
/// <typeparam name="RealType"></typeparam>
template <typename RealType>
class cTimeStepInfo
{
	friend class cGameTimer<float>;
	// This forces RealType to be either float or double
	static_assert(std::is_floating_point<RealType>::value, "cFPSTimer can only be instantiated with floating point types");
public:
	cTimeStepInfo()
		: mDeltaTime((RealType)0.0)
		, mElapsedTime((RealType)0.0)
	{

	}
	/// <summary>
	/// Time elapsed during the current time step
	/// </summary>
	/// <returns></returns>
	inline RealType DeltaTime() const { return mDeltaTime; }
	/// <summary>
	/// Total elapsed time during the game
	/// </summary>
	/// <returns></returns>
	inline RealType ElapsedTime() const { return mElapsedTime; }
private:
	/// <summary>
	/// Time elapsed during the current time step
	/// </summary>
	RealType mDeltaTime;
	/// <summary>
	/// Total elapsed time during the game
	/// </summary>
	RealType mElapsedTime;
};

/// <summary>
/// A basic timer with periodic FPS calculations built in
/// </summary>
/// <typeparam name="RealType"></typeparam>
template <typename RealType>
class cGameTimer
{
	// This forces RealType to be either float or double
	static_assert(std::is_floating_point<RealType>::value, "cFPSTimer can only be instantiated with floating point types");
public:
	typedef void (*fps_cb_func)(cGameTimer<RealType>*);
	/// <summary>
	/// constructor to specify min and max delta to report
	/// </summary>
	/// <param name="minDelta"></param>
	/// <param name="maxDelta"></param>
	cGameTimer(RealType minDelta, RealType maxDelta);

	/// <summary>
	/// constructor with defaults
	/// </summary>
	cGameTimer();

	/// <summary>
	/// Get the latest calculated frames per second.
	/// Cached during the last call to Tick().
	/// </summary>
	/// <returns></returns>
	inline RealType GetFPS() const { return mFPSLatest; }

	/// <summary>
	/// Get the latest calculated milliseconds per frame.
	/// Cached during the last call to Tick().
	/// </summary>
	/// <returns></returns>
	inline RealType GetMSPF() const { return mMSPFLatest; }

	/// <summary>
	/// Get the latest delta time.
	/// Cached during the last call to Tick().
	/// </summary>
	/// <returns></returns>
	inline RealType GetDeltaTime() const { return mDeltaTime; }

	/// <summary>
	/// Get the total elapsed time.
	/// Cached during the last call to Tick().
	/// </summary>
	/// <returns></returns>
	inline RealType GetElapsedTime() const { return mElapsedTime; }
	/// <summary>
	/// Start the timer.
	/// Call once. Call Tick() once per frame after.
	/// </summary>
	void Start();
	/// <summary>
	/// To periodically retrieve fps info updates
	/// </summary>
	/// <param name="cbFunction"></param>
	/// <param name="frequency"></param>
	void SetFPSCallback(fps_cb_func cbFunction, RealType frequency);

	/// <summary>
	/// Tick() is to be called once per frame
	/// </summary>
	void Tick();

	/// <summary>
	/// Populate timestep info
	/// </summary>
	/// <param name="timeStepInfoOut"></param>
	void GetTimeStepInfo(cTimeStepInfo<RealType>& timeStepInfoOut);

	/// <summary>
	/// Helper
	/// Tick() and retrieve timestep info in one step
	/// </summary>
	/// <param name="timeStepInfoOut"></param>
	void Tick(cTimeStepInfo<RealType>& timeStepInfoOut);
private:
	/// <summary>
	/// The timer used for timing
	/// </summary>
	cTimer<RealType> mTimer;

	/// <summary>
	/// Minimum delta we want
	/// </summary>
	RealType mMinDelta;

	/// <summary>
	/// Maximum delta we want
	/// </summary>
	RealType mMaxDelta;

	/// <summary>
	/// The latest delta time.
	/// </summary>
	RealType mDeltaTime;

	/// <summary>
	/// The total elapsed time
	/// </summary>
	RealType mElapsedTime;

	/// <summary>
	/// Frames-per-second frame counter
	/// Stored as floating point to avoid casting for it's only use.
	/// </summary>
	RealType mFPSFrameCount;

	/// <summary>
	/// Elapsed time counter for the periodic FPS calculations
	/// </summary>
	RealType mFPSElapsedTime;

	/// <summary>
	/// The last calculated Frames-per-second
	/// </summary>
	RealType mFPSLatest;

	/// <summary>
	/// The last calculated milliseconds-per-frame
	/// </summary>
	RealType mMSPFLatest;

	/// <summary>
	/// Callback function for periodic fps updates
	/// </summary>
	fps_cb_func mFPSCallbackFunction;

	/// <summary>
	/// FPS calculation frequency
	/// </summary>
	RealType mFPSFrequency;
};

template<typename RealType>
inline cGameTimer<RealType>::cGameTimer(RealType minDelta, RealType maxDelta)
	: mTimer()
	, mMinDelta(minDelta)
	, mMaxDelta(maxDelta)
	, mDeltaTime(minDelta)
	, mElapsedTime((RealType)0.0)
	, mFPSFrameCount((RealType)0.0)
	, mFPSElapsedTime((RealType)0.0)
	, mFPSLatest((RealType)0.0)
	, mMSPFLatest((RealType)0.0)
	, mFPSCallbackFunction(0)
	, mFPSFrequency((RealType)0.1)
{

}

template<typename RealType>
inline cGameTimer<RealType>::cGameTimer()
	: cGameTimer((RealType)0.0001, (RealType)0.05)
{
}

template<typename RealType>
inline void cGameTimer<RealType>::Start()
{
	mTimer.Start();
	mDeltaTime = mMinDelta;
	mElapsedTime = (RealType)0.0;
	mFPSFrameCount = (RealType)0.0;
	mFPSElapsedTime = (RealType)0.0;
	mFPSLatest = (RealType)0.0;
	mMSPFLatest = (RealType)0.0;
}

template<typename RealType>
inline void cGameTimer<RealType>::SetFPSCallback(fps_cb_func cbFunction, RealType frequency)
{
	mFPSCallbackFunction = cbFunction;
	mFPSFrequency = frequency;
}

template<typename RealType>
inline void cGameTimer<RealType>::Tick()
{
	RealType deltaTime;
	mTimer.Split(deltaTime, mElapsedTime);
	// use the true delta time for incrementing the fps counter
	mFPSElapsedTime += deltaTime;
	mFPSFrameCount += (RealType)1.0;
	mDeltaTime = glm::clamp(deltaTime, mMinDelta, mMaxDelta);
	// if it's time to do an FPS update
	if (mFPSElapsedTime > mFPSFrequency)
	{
		// calculate the frames per second
		mFPSLatest = mFPSFrameCount / mFPSElapsedTime;
		// calculate the milliseconds per frame
		mMSPFLatest = (RealType)1000.0 * mFPSElapsedTime / mFPSFrameCount;
		// reset the counters
		mFPSElapsedTime = (RealType)0.0;
		mFPSFrameCount = (RealType)0.0;
		// call the callback if it exists
		if (mFPSCallbackFunction)
		{
			mFPSCallbackFunction(this);
		}
	}
}

template<typename RealType>
inline void cGameTimer<RealType>::GetTimeStepInfo(cTimeStepInfo<RealType>& timeStepInfoOut)
{
	timeStepInfoOut.mDeltaTime = mDeltaTime;
	timeStepInfoOut.mElapsedTime = mElapsedTime;
}

template<typename RealType>
inline void cGameTimer<RealType>::Tick(cTimeStepInfo<RealType>& timeStepInfoOut)
{
	Tick();
	GetTimeStepInfo(timeStepInfoOut);
}
