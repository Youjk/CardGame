#include "TimeUtils.h"
#include "cocos2d.h"

USING_NS_CC;

TimeUtils::TimeUtils(void)
{

}


TimeUtils::~TimeUtils(void)
{
}

std::string TimeUtils::getSystemTime()
{
	 
	struct tm *tm;  
	time_t timep;  
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
		time(&timep);  
	#else  
		struct timeval tv;  
		gettimeofday(&tv,NULL);  
		timep = tv.tv_sec;  
	#endif  
		tm = localtime(&timep);  
		char date[20];
		sprintf(date, "%02d:%02d:%02d", (int) tm->tm_hour,  
			(int) tm->tm_min, (int) tm->tm_sec);  
		return std::string(date);  
}
