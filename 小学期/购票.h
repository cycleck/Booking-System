#include"数据结构.h"
#ifndef 购票_h
#define 购票_h 

void ui();//用户界面
void ticketBuy(char* Fnum, char* Ftime, char* Uname, char* Upassword); // 用于购买航班的函数，输入航班号,输入起飞日期,当前用户的姓名和密码
void myTicket(char* Uname);//查看我的订单
void UserReadorder(List_P *P);//用户查看我的订单时，用于从文件订单.txt读取全部订单的函数

void checkPass(char *Upassword);//验证支付密码
char* checkSeatFir();//验证座位号
char* checkSeatEco();//验证座位号
#endif

//修改日期 2021.9.6.18：45