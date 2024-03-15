#pragma once
#pragma warning(disable : 4996)
char* GetTime();
#include "time.h" 
char* GetTime()
{
	time_t rawtime;     //其实本质是long
	static char ptime[30] = { 0 };
	struct tm * timeinfo;
	time(&rawtime);              //函数获取当前时间距1970年1月1日的秒数，以秒计数单位，存于rawtime 中。
	timeinfo = localtime(&rawtime); // 转为时间结构
	strftime(ptime, 30, "%Y-%m-%d %T", timeinfo);
	//printf(ptime); //函数将ptr所指向的时间结构转换成下列字符串：day month date hours : minutes:seconds year / n / 0
	return ptime;
}