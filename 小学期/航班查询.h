#include"数据结构.h"
#ifndef 航班查询_h
#define 航班查询_h 

//主航班查询键
void Select_Flight();

//通过航班号和出发时间（天）进行挑选   num---航班号，date---当天日期
void select_Flightnum_Date(char* num, char* Date,List_F F);
//通过出发城市+到达城市+出发时间（天）进行挑选   start---出发城市，down---到达城市，date---当天日期
void select_City_Date(char* start, char* down, char* Date,List_F F);

//是否选择过滤查询结果       F1---航班信息的结构体  Date---日期
void if_filter(List_F F1,char*Date);
//选择yes的过滤查询过程       F1---航班信息的结构体  Date---日期
void if_filter_yes(List_F F1,char*Date);
//通过时间段过滤       F1---航班信息的结构体  Date---日期
void filter_time(List_F F1,char*Date);
//通过航空公司过滤       F1---航班信息的结构体  Date---日期
void filter_company(List_F F1,char*Date);
//通过舱位过滤       F1---航班信息的结构体  Date---日期
void filter_class(List_F F1,char*Date);
//通过机型过滤       F1---航班信息的结构体  Date---日期
void filter_type(List_F F1,char*Date);

//根据起飞时间排序      F1---航班信息的结构体 k---航班数
void sort_by_Time(List_F F1, int k);
//根据价格排序     F1---航班信息的结构体指针 i---sort_by_Time进行的第i+1次循环
void sortTime(List_F* F1, int i);
//根据价格排序     F1---航班信息的结构体指针 i---sort_by_Price进行的第i+1次循环
void sortPrice(List_F* F1, int i);
//根据价格排序并显示      F1---航班信息的结构体指针 k---航班数
void sort_by_Price(List_F* F1, int k);

//是否选择购票      F1---航班信息的结构体 Date---日期
void if_buy_ticket(char*Flightnum,char*Date);
//根据所有起飞时间排序      F1---航班信息的结构体指针
void sort_All_by_Time(List_F* F1);
//判断航班号输入是否正确,并找到对应日期的航班号       Flightnum---航班号 Date---该日期航班文件信息的路径
char* judge_Flightnum(char* Flightnum, char* Date);
//判断日期输入是否正确，并将正确的文件信息打开输入到结构体中     Date---日期
char* judge_Date(char* Date);
//判断日期输入是否正确      Date---日期
char* judgedate(char*Date);
//用户得到的航班查询结果       F---航班信息的结构体指针 Date---该日期航班文件信息的路径
void user_readinfo(List_F* F, char* Date);


#endif 
