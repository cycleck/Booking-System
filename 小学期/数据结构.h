#pragma once
#define MAX1 200

typedef struct
{
	char Flightnum[20];//航班号
	char Name[20];//乘客姓名
	char ID[20];//身份证
	char Company[20];//航空公司
	char Seatnum[20];//座位号
	char Time_date[20];//订单付款时间-日子
	char Time_min[20];//订单付款的时间-分、秒 
	char payername[20];//这个订单的付款人
	char FlyTime[20];//起飞日期
	char Flighttime_up[20];//起飞时间
	char Flighttime_down[20];//降落时间
	char Startland[20];//出发地
	char Downland[20];//目的地
	char Flighttype[20];//飞机类型
	char Pilot_1[20];//飞行员1姓名
	char Pilot_2[20];//飞行员2姓名
	char SeatType[20];//舱位类型

}Passenger;//一个订单的所有信息
typedef struct
{
	Passenger a[2000];    //记录总购票人数
	int count;               //记录航班次数
}List_P;
//乘客结构


//用户结构
typedef struct
{
	char ID[20];//用户登陆ID
	char Name[20];//用户姓名
	char Sex[20];//用户性别
	char Phone[20];//用户手机号
	char PassWord[20];//用户密码
	char Email[20];//邮箱
	char mail[20];
    char *BuyTime;//买票时时间
	int Odernum; //购票数
   
}User;

typedef struct
{
	User u[50];    //记录总用户
	int count;     //记录用户数
}List_U;

//管理员结构
typedef struct
{
	char ID[20];//管理员ID
	char Name[20];//管理员姓名
	char Company[20];//管理员航空公司
	char mail[20];//管理员邮箱
	char Password[20];//管理员密码
	

}Admination;


typedef struct
{
	Admination a[50];    //记录总管理员
	int count;               //记录管理员数
}List_A;


//航班结构
typedef struct
{
	char Company[20];//航空公司
	char Flightnum[20];//航班号
	char Flighttime_up_date[20];//出发日期
	char Flighttime_down_date[20];//到达日期
	char Flighttime_up[20];//出发时间
	char Flighttime_down[20];//到达时间
	char Startland[20];//出发地
	char Downland[20];//目的地
	double Rate;//上座率
	char Flighttype[20];//飞机类型
	int Economfare;//经济舱票价
	int Firstfare;//头等舱票价
	char Pilot_1[20];//飞行员1姓名
	char Pilot_2[20];//飞行员2姓名
	int Economrest;//经济舱余票
	int Firstrest;//头等舱余票
	int Ordernum;//订单数（总）
	int Ordernum_econ;//经济舱订单数
	int Ordernum_firs;//头等舱订单数
	int Income;//总收入
	char Ontimerate[20];

}FlightInfo;


//航班数组
typedef struct
{
	FlightInfo Flight[150];   //航班上限150
	int count;               //记录航班次数
}List_F;