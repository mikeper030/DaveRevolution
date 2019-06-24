#pragma once
#include <string>
//A utility class for countdown timer implementation
class TimeUtils
{
public:
	//constructor
	TimeUtils(const int& seconds);
	//restart the timer
	static void restart();
	//set the timer
	void setTime(const int& seconds);
	//set the timer on unlimited time mode
	void setUnlimitedTimeMode(const bool& b);
	//update the timer
	void secondPassed();
	//get elapsed  time as seconds
	int getElapsedTimeAsSeconds() const;
	//get the time formatted
	std::string getTimeFormatted();
	//return if the timer is finished
	bool isFinished() const;
private:
	std::string m_time_formatted;
	bool unlimited;
	static int m_time, start_time;
};

