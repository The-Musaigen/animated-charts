#ifndef CHART_H_
#define CHART_H_

class Chart
{
	float mProgress;
	float mEndProgress;
	float mSpeed;

	bool mAnimatingNow;

	std::chrono::steady_clock::time_point mStartPoint;
	std::chrono::milliseconds mDuration;
public:
	Chart() :
		mProgress(.0f),
		mEndProgress(.0f),
		mSpeed(1.f),
		mAnimatingNow(false),
		mDuration(std::chrono::milliseconds(1)),
		mStartPoint(std::chrono::steady_clock::now())
	{}

	void Start(float aEndProgress)
	{
		using namespace std::chrono;

		mStartPoint = steady_clock::now();
		mEndProgress = aEndProgress;
		mAnimatingNow = true;
	}

	void Update()
	{
		if (!mAnimatingNow)
			return;

		using namespace std::chrono;
		using float_duration = duration<float, std::milli>;
		
		float_duration delta = steady_clock::now() - mStartPoint;
		milliseconds elapsed = duration_cast<milliseconds>(delta);

		mProgress += (mEndProgress - mProgress) * ((delta / mDuration) * mSpeed);

		if (elapsed > mDuration)
		{
			mProgress = mEndProgress;
			mAnimatingNow = false;
		}
	}

	inline float GetProgress() const { return mProgress; }
	inline float GetEndProgress() const { return mEndProgress; }

	inline void SetDuration(const std::chrono::milliseconds& aDuration) 
	{
		if (mDuration.count() <= 0)
			return;

		mDuration = aDuration; 
	}

	inline void SetSpeed(const float aSpeed)
	{
		if (aSpeed <= 0.f)
			return;

		mSpeed = aSpeed;
	}
};

#endif // !CHART_H_
