#pragma once
#pragma warning(disable : 4996)
char* GetTime();
#include "time.h" 
char* GetTime()
{
	time_t rawtime;     //��ʵ������long
	static char ptime[30] = { 0 };
	struct tm * timeinfo;
	time(&rawtime);              //������ȡ��ǰʱ���1970��1��1�յ����������������λ������rawtime �С�
	timeinfo = localtime(&rawtime); // תΪʱ��ṹ
	strftime(ptime, 30, "%Y-%m-%d %T", timeinfo);
	//printf(ptime); //������ptr��ָ���ʱ��ṹת���������ַ�����day month date hours : minutes:seconds year / n / 0
	return ptime;
}