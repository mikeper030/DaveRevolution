#include "TimeUtils.h"
#include <sstream>
#include <iostream>

int TimeUtils::m_time = 0;
int TimeUtils::start_time = 0;

TimeUtils::TimeUtils(const int& seconds)
	:unlimited(false)
{
	m_time = seconds;
	start_time = seconds;
}

void TimeUtils::restart()
{
	m_time = start_time;
}

void TimeUtils::setTime(const int& seconds)
{

	m_time = seconds;
}
void TimeUtils::setUnlimitedTimeMode(const bool& b)
{
	unlimited = b;
	if (b)m_time = -2;
}
void TimeUtils::secondPassed()
{
	if (!unlimited)m_time++;
}
int TimeUtils::getElapsedTimeAsSeconds() const
{
	return m_time;
}
std::string TimeUtils::getTimeFormatted()
{

	if (m_time == -2)
	{
		std::string s;
		s = "-:--";
		return s;
	}
	std::ostringstream o;
	int minutes = m_time / 60;
	int seconds = m_time % 60;

	if (seconds >= 10)
		o << minutes << ":" << seconds;
	else
		o << minutes << ":0" << seconds;
	std::string f(o.str()); m_time_formatted = f;
	return m_time_formatted;
}

bool TimeUtils::isFinished() const
{
	return m_time == 0;
}
