
#pragma warning(disable : 4996)
#include "数据结构.h"
#ifndef 管理员航班查询及添加_h
#define 管理员航班查询及添加_h


/*判断字符串是否为中文*/
int is_Chinese(char*);

/*查询当前公司所有航班*/
void search_Flight();

/*选择城市*/
char* choose_City();

/*根据已填航班信息构筑航班号*/
char *build_Flightnum(FlightInfo, FlightInfo);

/*输入航班信息*/
int in_Put(FlightInfo*);

/*判断时间是否冲突*/
int judge_Time(FlightInfo , FlightInfo );

/*判断地点是否冲突*/
int judge_Land(FlightInfo , FlightInfo );

/*修改航班信息*/
void modify_Flight(FlightInfo*);

/*修改飞行员姓名*/
int modify_Polit(int , int , FlightInfo* );

/*添加完成后选择进行下一步*/
int reserve_Flight(FlightInfo*);

/*添加航班内容*/
void add_Flight();


#endif 

