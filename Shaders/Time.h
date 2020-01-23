#pragma once
class Time
{

public:

	static void Update();

	static float GetDeltaTime();
	static float GetElapsedTime();

private:

	static float m_deltaTime;
	static float m_elapsedTime;
};

