#include"数据结构.h"
#include <graphics.h>		//包含图形库文件
#include <conio.h>
#include<windows.h>
#ifndef 订单管理_h
#define 订单管理_h 
void ReadInfo(List_F *);    //读入航班信息
void PrintAirmsg_U(List_F );  //打印航班信息(用户版)
void PrintAirmsg_A(List_F);  //打印航班信息(管理员版)

void Readorder(List_P *);   //读入购票信息
void Printorder(List_P );   //打印购票信息

void ReadInfo_otherday(List_F *,int);//读入其他日航班信息
void calculate_F(List_F *);// 计算满座率以及余票和票数
void Income_Rank(List_F *);//按照收入排序
void Rate_Rank(List_F *);  //按照满座率排序
void Book_Rank(List_F *F,Admination); //按照购票数排序
void Showorder(List_F ,List_P , Admination ); //根据航空公司查询用户订单
void ReadAdmination(Admination*);//读取当前管理员信息
void Recommend(List_F *F);

void QRcode();//弹出付款码
void Boardcheck(Passenger ,List_F ,int);//弹出登机牌
#endif 


