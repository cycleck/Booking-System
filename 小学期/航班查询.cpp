#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "数据结构.h"
#include "订单管理.h"
#include"航班查询.h"
#include"购票.h"
#pragma warning(disable : 4996)
//包含四个过滤类型的函数指针数组
void(*FuncPointerArray[4])(List_F F1,char*Date) = { filter_time ,filter_company,filter_class,filter_type };

void Select_Flight() {
	getchar();//接收回车键
	printf("\n 欢迎进入航班查询\n");
	printf("您可以选择以下两种航班查询类型：\n");
	printf("******************************************\n");
	printf("*   1.以出发时间和航班号查询             *\n");
	printf("*   2.以出发时间和出发城市，到达城市查询 *\n");
	//printf("*   0.返回主菜单                           *\n");
	printf("******************************************\n");
	printf("请输入对应的选项的序号:\n");
	while (1) {
		List_F F = { 0 };
		char Date[20];//接收用户输入的日期
		char date[20];//接收Date中的字符串并进入judge_Date(date)函数，返回为data/flight/9.x航班信息.txt---航空信息路径
		char str3[50];//接收date字符串
		char flightnum[20];//接收航班号
		char startland[20];//接收出发地
		char downland[20];//接收目的地
		char type[20];//接受查询类型的选项序号
		gets_s(type);
		if (strncmp(type, "1", 20) == 0) {
			printf("请输入您选择的日期:(请以 9.2 的格式写日期）\n");
			gets_s(Date,20);
			strcpy(date, Date);
			//进入judge_Date(date)函数，返回航空信息路径 data/flight/9.x航班信息.txt
			strcpy(str3,judge_Date(date));//str3最终为 data/flight/9.x航班信息.txt
			user_readinfo(&F,str3);//得到航班信息里的每个参数的地址
			//输出当前查询日期的所有航班信息
			printf("请输入您选择的航班号:\n");
			gets_s(flightnum);
			select_Flightnum_Date(flightnum, Date,F);//进入出发时间和航班号查询
			break;
		}
		else if (strncmp(type, "2", 20) == 0) {
			printf("请输入您选择的日期:(请以 9.2 的格式写日期）\n");
			gets_s(Date, 20);
			strcpy(date, Date); 
			//进入judge_Date(date)函数，返回航空信息路径 data/flight/9.x航班信息.txt
			strcpy(str3, judge_Date(date));//str3最终为 data/flight/9.x航班信息.txt
			user_readinfo(&F, str3);//得到航班信息里的每个参数的地址
			//输出当前查询日期的所有航班信息
			printf("请输入您选择的出发地:\n");
			gets_s(startland);
			printf("请输入您选择的目的地:\n");
			gets_s(downland);
			select_City_Date(startland, downland,Date,F);//进入出发时间和出发城市，到达城市查询
			break;
		}
		else {
			printf("您输入的类型错误\n请重新输入：\n");
		}
	}
}
void select_Flightnum_Date(char* num, char*Date,List_F F) {
	int j = 0;//查询到的航班次数
	List_F F1 = { 0 };
	for (int i = 0; i < F.count; i++) {//F.count为查询到的航班数量
		if (strcmp(num,F.Flight[i].Flightnum)== 0) {//判断用户输入的航班号是否存在
				//查询到有相同的航班号的次数
				F1.Flight[j] = F.Flight[i];
				j++;//查询到j次就有j次航班数
		}
	}
	F1.count = j;//将航班次数赋值给空的结构体 F1.count
	if (!j) {//如果未查询到该航班号
		printf("无法查询到该航班信息\n");
		printf("*   点击enter键返回航班主查询    *\n");
		Select_Flight();
	}
	else {
		sort_by_Price(&F1, j);
		//因为每天航班只有一趟，所以直接跳转到询问是否购票的界面
		if_buy_ticket(F1.Flight[0].Flightnum,Date);
	}
	

	
}
void select_City_Date(char* start, char* down, char*Date,List_F F) {
	int j = 0;
	List_F F1 = { 0 };
	for (int i = 0; i < F.count; i++) {//F.count为查询到的航班数量
		if (strcmp(start, F.Flight[i].Startland) == 0 && strcmp(down, F.Flight[i].Downland) == 0)//判断用户输入的出发地与目的地是否在航班信息内存在
		{
			//查询到有相同的航班号的次数
			F1.Flight[j] = F.Flight[i];
			j++;//查询到j次就有j次航班数
		}
	}
	F1.count = j;//将航班次数赋值给空的结构体 F1.count
	if (!j) {//如果未查询到该航班号
		printf("无法查询到该航班信息\n");
		printf("*   点击enter键返回航班主查询    *\n");
		Select_Flight();
	}
	else if (j == 1) {
		sort_by_Price(&F1, j);
		printf("*       检测到您查询到的航班信息仅一条，按enter键直接为您跳转到购票页面      *\n");
		getchar();
		if_buy_ticket(F1.Flight[0].Flightnum, Date);
	}
	else {
		sort_by_Price(&F1, j);
		if_filter(F1, Date);
		//因为不同航班可能有相同的出发地与目的地，所以跳转到是否要进行筛查选项的界面
	}
}

void if_filter(List_F F1,char*Date) {
	char answer[20];
	printf("******************************************\n");
	printf("*   是否选择在查询结果上继续进行筛选？   *\n");
	printf("*   您可选择的筛选类型有:                *\n");
	printf("* 1，时间段 2，航空公司 3，舱位 4，机型  *\n");
	printf("******************************************\n");
	printf("输入是，进入筛选。输入否，进入购票。\n");
	gets_s(answer);
	while (1) {
		if (strncmp(answer,"否",20) == 0) {
			sort_by_Price(&F1, F1.count);//通过最低票价排序航班查询到的航班
			if (F1.count > 1) {
				char Flightnum[20];
				char Flightnumber[20];
				char date[50];
				char str3[50];
				printf("*           因您查询到的航班信息大于一条，请您先输入您想乘坐的航班号            *\n");
				gets_s(Flightnum, 20);
				strcpy(date, Date);
				strcpy(str3, judge_Date(date));
				strcpy(Flightnumber, judge_Flightnum(Flightnum, str3));
				if_buy_ticket(Flightnumber, Date);
			}
			else
				if_buy_ticket(F1.Flight[0].Flightnum, Date);
			break;

		}
		else if (strncmp(answer, "是", 20) == 0) {
			if_filter_yes(F1,Date);//选择进行筛查，进入筛查界面
			break;
		}
		else {
			printf("您的输入有误，请重新输入\n");
			printf("输入是，进入筛选。输入否，进入购票。\n");
			gets_s(answer);
		}
	}
}
void if_filter_yes(List_F F1,char*Date) {
	while (1) {
		int num;
		printf("******************************************\n");
		printf("*   您可选择的筛选类型有:                *\n");
		printf("* 1，时间段 2，航空公司 3，舱位 4，机型  *\n");
		printf("******************************************\n");
		printf("请输入对应选项的序号\n");
		scanf_s("%d", &num);
		if (num == 1 || num == 2 || num == 3 || num == 4) {
			num--;
			//(*FuncPointerArray[4])(List_F F1, char* Date) = { filter_time ,filter_company,filter_class,filter_type };
			FuncPointerArray[num](F1, Date);//选择过滤类型
			break;
		}
		else {
			printf("请输入正确的值\n");
		}
	}
}

void filter_time(List_F F1,char*Date) {
	int put;//用户输入排序序号
	int j = 0;
	int num[6] = { 1,2,3,4,5,6 };
	char time_start[6][20] = { "00:01","04:01","08:01" ,"12:01" ,"16:01" ,"20:01" };
	char time_end[6][20] = { "04:00","08:00","12:00" ,"16:00" ,"20:00" ,"24:00" };
	char answer[20];
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("************************\n");
		printf("*   请选择时间段:      *\n");
		printf("*   1. 00:01 -- 04:00  *\n");
		printf("*   2. 04:01 -- 08:00  *\n");
		printf("*   3. 08:01 -- 12:00  *\n");
		printf("*   4. 12:01 -- 16:00  *\n");
		printf("*   5. 16:01 -- 20:00  *\n");
		printf("*   6. 20:01 -- 24:00  *\n");
		printf("************************\n");
		printf("请输入对应的选项的序号:\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] || put == num[3] || put == num[4] || put == num[5])) {
			printf("您输入的值有误\n请重新输入\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				//比较所选的时间段中是否有查询到的航班
				if (strcmp(F1.Flight[j].Flighttime_up, time_start[put - 1]) == 1 && strcmp(F1.Flight[j].Flighttime_up, time_end[put - 1]) == -1) {
					F2.Flight[k] = F1.Flight[j];//将查询到的结果赋给一个新的List_F结构体
					k++;//k即表示数组下标，又表示筛选得到的航班数
				}
			}
			printf("筛选完毕\n");
			sort_by_Price(&F2, k);//通过最低价格进行排序
			if (!k) {
				if_filter_yes(F1, Date);//继续筛选
				break;
			}
			else {
				printf("是否继续进行筛查？\n");
				printf("输入'购票'进入购票界面，输入其他键继续筛选\n");
				getchar();//防止gets_s被忽略
				gets_s(answer, 20);
				if (strncmp(answer, "购票", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   因您查询到的航班信息大于一条，请您先输入您想乘坐的航班号     *\n");
						gets_s(Flightnum, 20);
						strcpy(date, Date);
						strcpy(str3, judge_Date(date));
						strcpy(Flightnumber, judge_Flightnum(Flightnum, str3));
						if_buy_ticket(Flightnumber, Date);
					}
					else
						if_buy_ticket(F2.Flight[0].Flightnum, Date);
					break;
				}
				else {
					if_filter_yes(F1, Date);//继续筛选
					break;
				}
			}
		}
	}
}
void filter_company(List_F F1,char*Date) {
	int put;
	int j = 0;
	int num[3] = { 1,2,3 };
	char CompanyList[3][20] = { "南方航空","海南航空","东方航空" };
	char answer[20]; 
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("**********************\n");
		printf("*   请选择航空公司:  *\n");
		printf("*   1. 南方航空      *\n");
		printf("*   2. 海南航空      *\n");
		printf("*   3. 东方航空      *\n");
		printf("**********************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] )) {
			printf("您输入的值有误\n请重新输入\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				if (strcmp(F1.Flight[j].Company, CompanyList[put - 1]) == 0) {
					F2.Flight[k] = F1.Flight[j];
					k++;
				}
			}
			printf("筛选完毕\n");
			sort_by_Price(&F2, k);
			if (!k) {
				if_filter_yes(F1, Date);//继续筛选
				break;
			}
			else {
				printf("输入'购票'进入购票界面，输入其他键继续筛选\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "购票", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   因您查询到的航班信息大于一条，请您先输入您想乘坐的航班号     *\n");
						gets_s(Flightnum, 20);
						strcpy(date, Date);
						strcpy(str3, judge_Date(date));
						strcpy(Flightnumber, judge_Flightnum(Flightnum, str3));
						if_buy_ticket(Flightnumber, Date);
					}
					else
						if_buy_ticket(F2.Flight[0].Flightnum, Date);
					break;
				}

				else
				{
					if_filter_yes(F1, Date);
					break;
				}
			}
		}
	}
}
void filter_class(List_F F1,char*Date) {
	int put;
	int num[2] = { 1,2 };
	char answer[20];
	while (1) {
		int k = 0;
		printf("********************\n");
		printf("*     请选择舱位:  *\n");
		printf("*   1. 头等舱      *\n");
		printf("*   2. 经济舱      *\n");
		printf("********************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1])) {
			printf("您输入的值有误\n");
			printf("请重新输入\n\n");
		}
		else {
			if (put == 1) {
				if (F1.count == 0)
					printf("未查询到航班消息\n");
				else {
					printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格     头等舱余票           航空公司  准点率\n");
					printf("\n");
					for (int i = 0; i < F1.count; i++)
						sortPrice(&F1, i);
					for (int i = 0; i < F1.count; i++) {
						printf(" %s\t   %s\t   %s\t   %s\t   %s\t   %5s\t   %d\t    %d     %5s   %10s \n", F1.Flight[i].Flightnum, F1.Flight[i].Flighttime_up,
							F1.Flight[i].Flighttime_down, F1.Flight[i].Startland, F1.Flight[i].Downland, F1.Flight[i].Flighttype, F1.Flight[i].Firstfare,F1.Flight[i].Firstrest,
							F1.Flight[i].Company,F1.Flight[i].Ontimerate);
					}
				}
			}
			else if (put == 2) {
				if (F1.count == 0)
					printf("未查询到航班消息\n");
				else {
					printf("航班号    起飞时间         降落时间        出发地  目的地   机型         经济舱价格       经济舱余票       航空公司  准点率\n");
					printf("\n");
					for (int i = 0; i < F1.count; i++)
						sortPrice(&F1, i);
					for (int i = 0; i < F1.count; i++) {
						printf(" %s\t   %s\t   %s\t   %s\t   %s\t   %5s\t   %d\t    %d     %5s   %10s\n", F1.Flight[i].Flightnum, F1.Flight[i].Flighttime_up,
							F1.Flight[i].Flighttime_down, F1.Flight[i].Startland, F1.Flight[i].Downland, F1.Flight[i].Flighttype, F1.Flight[i].Economfare,F1.Flight[i].Economrest,
							F1.Flight[i].Company, F1.Flight[i].Ontimerate);
					}

				}
			}
			printf("筛选完毕\n");
			if (!F1.count) {
				if_filter_yes(F1, Date);//继续筛选
				break;
			}
			else {
				printf("输入'购票'进入购票界面，输入其他键继续筛选\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "购票", 20) == 0) {
					if (F1.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   因您查询到的航班信息大于一条，请您先输入您想乘坐的航班号     *\n");
						gets_s(Flightnum, 20);
						strcpy(date, Date);
						strcpy(str3, judge_Date(date));
						strcpy(Flightnumber, judge_Flightnum(Flightnum, str3));
						if_buy_ticket(Flightnumber, Date);
					}
					else
						if_buy_ticket(F1.Flight[0].Flightnum, Date);
					break;
				}
				else {
					if_filter_yes(F1, Date);
					break;
				}
			}
		}
	}
}
void filter_type(List_F F1,char*Date) {
	int put;
	int j = 0;
	int num[4] = { 1,2,3,4 };
	char TypeList[4][20] = { "空客321","波音737","JET" ,"空客320"};
	char answer[20];
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("*******************\n");
		printf("* 请选择飞机类型: *\n");
		printf("*   1. 空客321    *\n");
		printf("*   2. 波音737    *\n");
		printf("*   3. JET        *\n");
		printf("*   4. 空客320    *\n");
		printf("*******************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] || put==num[3])) {
			printf("您输入的值有误\n");
			printf("请重新输入\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				if (strcmp(F1.Flight[j].Flighttype, TypeList[put - 1]) == 0) {
					F2.Flight[k] = F1.Flight[j];
					k++;
				}
			}
			printf("筛选完毕\n");
			sort_by_Price(&F2, k);
			if (!k) {
				if_filter_yes(F1, Date);//继续筛选
				break;
			}
			else {
				printf("输入'购票'进入购票界面，输入其他键继续筛选\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "购票", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   因您查询到的航班信息大于一条，请您先输入您想乘坐的航班号     *\n");
						gets_s(Flightnum, 20);
						strcpy(date, Date);
						strcpy(str3, judge_Date(date));
						strcpy(Flightnumber, judge_Flightnum(Flightnum, str3));
						if_buy_ticket(Flightnumber, Date);
					}
					else
						if_buy_ticket(F2.Flight[0].Flightnum, Date);
					break;
				}
				else {
					if_filter_yes(F1, Date);
					break;
				}
			}
		}
	}
}

void sortTime(List_F* F1, int i) {
	for (int j = 0; j < i; j++) {
		FlightInfo Temp;//设置一个暂时的结构体
		//由小到大排序起飞时间
		if (strcmp(F1->Flight[j].Flighttime_up, F1->Flight[i].Flighttime_up) == 1) {
			Temp = F1->Flight[j];
			F1->Flight[j] = F1->Flight[i];
			F1->Flight[i] = Temp;
		}
	}
}
void sort_by_Time(List_F F1,int k) {
	for (int i = 0; i < k; i++) 
		sortTime(&F1, i);
	if (k == 0) {
		printf("*****   未查询到航班消息\n");
		return ;
	}
	printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格  经济舱价格   头等舱余票    经济舱余票       航空公司  准点率\n");
	printf("\n");
	for(int i=0;i<k;i++){
		printf(" %7s\t   %7s\t %5s\t   %5s\t   %5s\t   %5s\t   %5d\t   %5d\t           %5d\t         %5d\t    %7s  %10s\n", F1.Flight[i].Flightnum, F1.Flight[i].Flighttime_up,
			F1.Flight[i].Flighttime_down, F1.Flight[i].Startland, F1.Flight[i].Downland, F1.Flight[i].Flighttype, F1.Flight[i].Firstfare,
			F1.Flight[i].Economfare, F1.Flight[i].Firstrest, F1.Flight[i].Economrest, F1.Flight[i].Company,F1.Flight[i].Ontimerate);

	}
}
void sort_All_by_Time(List_F* F1) {
	for (int i = 0; i < F1->count; i++) 
		sortTime(F1, i);
	printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格  经济舱价格   头等舱余票    经济舱余票       航空公司  准点率\n");
	printf("\n"); 
	for (int i = 0; i < F1->count; i++) {
		
		printf(" %7s\t   %7s\t %5s\t   %5s\t   %5s\t   %5s\t   %5d\t   %5d\t           %5d         %5d    %7s  %10s\n", F1->Flight[i].Flightnum, F1->Flight[i].Flighttime_up,
			F1->Flight[i].Flighttime_down, F1->Flight[i].Startland, F1->Flight[i].Downland, F1->Flight[i].Flighttype, F1->Flight[i].Firstfare,
			F1->Flight[i].Economfare, F1->Flight[i].Firstrest, F1->Flight[i].Economrest, F1->Flight[i].Company, F1->Flight[i].Ontimerate);

		
	}

}
void sortPrice(List_F* F1, int i) {
	for (int j = 0; j < i; j++) {
		FlightInfo Temp;//获得一个暂存的FlightInfo结构体
		if (F1->Flight[j].Economfare > F1->Flight[i].Economfare) {//比较查询结构的航班的最低价格
			//将航班信息以最低价格的形式，从低到高排序
			Temp = F1->Flight[j];
			F1->Flight[j] = F1->Flight[i];
			F1->Flight[i] = Temp;
		}
	}
}
void sort_by_Price(List_F* F1, int k) {
	for (int i = 0; i < k; i++)
		sortPrice(F1, i);//i表示内层循环的第i+1次
	if (k == 0) {
		printf("未查询到航班消息\n\n");
	}
	else {
		printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格  经济舱价格   头等舱余票    经济舱余票       航空公司  准点率\n");
		printf("\n");
		for (int i = 0; i < k; i++) {

			printf(" %7s\t   %7s\t %5s\t   %5s\t   %5s\t   %5s\t   %5d\t   %5d\t           %5d         %5d    %7s  %10s\n", F1->Flight[i].Flightnum, F1->Flight[i].Flighttime_up,
				F1->Flight[i].Flighttime_down, F1->Flight[i].Startland, F1->Flight[i].Downland, F1->Flight[i].Flighttype, F1->Flight[i].Firstfare,
				F1->Flight[i].Economfare, F1->Flight[i].Firstrest, F1->Flight[i].Economrest, F1->Flight[i].Company,F1->Flight[i].Ontimerate);


		}
	}
}

void if_buy_ticket(char* Flightnum,char* Date) {

	FILE *ft;
	ft = fopen("当前订单.txt", "w");
	fprintf(ft, "%s   %s", Flightnum, Date);//将数据输入到当前订单.txt中
    fclose(ft);


	printf("\n");
	printf("\n                     *****************************************                   \n");
	
}
char* judge_Flightnum(char* Flightnum,char* Date) {
	while (1) {
		//判断航班号是否符合前两个字符为大写字母后四个字符为数字
		if (Flightnum[0] >= 'A' && Flightnum[0] <= 'Z' && Flightnum[1] >= 'A' && Flightnum[1] <= 'Z' 
			&& Flightnum[2] >= '0' && Flightnum[2] <= '9' && Flightnum[3] >= '0' && Flightnum[3] <= '9' 
			&& Flightnum[4] >= '0' && Flightnum[4] <= '9' && Flightnum[5] >= '0' && Flightnum[5] <= '9' 
			&& strlen(Flightnum) == 6) {
			break;

		}
		else {
			printf("您输入的航班号错误，请按格式输入六位号的航班   例：CZ9424\n");
			gets_s(Flightnum, 20);
		}
	}
	int j = 0;
	List_F F = { 0 };
	List_F F1 = { 0 };
	F.count = 0;//初始化行数
	FILE* fp = fopen(Date, "r");//Date为航班路径
	if (fp == NULL)
	{
		printf("抱歉，该日期的航班信息不存在/// \n");
		exit(1);
	}
	else
	{
	    
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行有（n-1）个‘\n’，去除第一行 n-1为航班数
				F.count++;
		}
		rewind(fp);

		for (int i = 0; i < F.count; i++)
		{
			fscanf(fp, "%s%s%s%s%s%s%d%d%d%d%s%s%s%s", F.Flight[i].Flightnum, F.Flight[i].Flighttime_up,
				F.Flight[i].Flighttime_down, F.Flight[i].Startland, F.Flight[i].Downland, F.Flight[i].Flighttype, &F.Flight[i].Firstfare,
				&F.Flight[i].Economfare, &F.Flight[i].Firstrest, &F.Flight[i].Economrest, F.Flight[i].Pilot_1, F.Flight[i].Pilot_2, F.Flight[i].Company,F.Flight[i].Ontimerate);

		}

	}
	fclose(fp);
	for (int i = 0; i < F.count; i++) {
		//若存在该航班号，则可返回该航班号
		if (strcmp(Flightnum ,F.Flight[i].Flightnum)==0) {
			j=1;
		}
	}
	if (!j) {
		printf("该航班号不存在");
		printf("请重新输入航班号\n");
		gets_s(Flightnum, 20);
		judge_Flightnum(Flightnum, Date);
	}
	else
	    return Flightnum;
}
char* judgedate(char*Date) {
	while (1) {
		if (strlen(Date) == 3) {

			if (Date[0] == '9' && Date[1] == '.' && Date[2] <= '9' && Date[2] >= '1') {
				break;
			}
			else {
				printf("您输入的日期有错误,请以9.xx的格式输入  例：9.1\n");
				gets_s(Date, 20);
			}

		}
		else if (strlen(Date) == 4) {
			if (Date[0] == '9' && Date[1] == '.' && Date[2] == '1' && Date[3] >= '0' && Date[3] <= '9') {
				break;
			}
			else {
				printf("您输入的日期有错误，请以9.xx的格式输入  例：9.1\n");
				gets_s(Date, 20);
			}
		}
		else {
			printf("您输入的日期有错误，请以9.xx的格式输入  例：9.1\n");
			gets_s(Date, 20);
		}
	}
	return Date;
}
char* judge_Date(char* Date) {
	judgedate(Date);

	char  str1[50] = "航空信息.txt";
	char  str3[50] = "data/flight/";
	strcat(Date, str1);
	strcat(str3,Date);
	FILE* fp = fopen(str3, "r");//str3=data/flight/9.x航空信息.txt
	if (fp == NULL)
	{
		printf("抱歉，该日期的航班信息不存在!!! \n");
		exit(1);
	}
	fclose(fp);
	
	return str3;
}

void user_readinfo(List_F* F, char* Date) {

	FILE* fp = fopen(Date, "r");
	if (fp == NULL)
	{
		printf("抱歉，该日期的航班信息不存在111 \n");
		exit(1);
	}
	else
	{
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行有（n-1）个‘\n’，去除第一行 n-1为航班数
				F->count++;
		}
		rewind(fp);
		for (int i = 0; i < F->count; i++)
		{
			fscanf(fp, "%s %s %s %s %s %s %d %d %d %d %s %s %s %s \n", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
				F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, &F->Flight[i].Firstfare,
				&F->Flight[i].Economfare, &F->Flight[i].Firstrest, &F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2, F->Flight[i].Company,F->Flight[i].Ontimerate);
		}
	
		printf("为您查询到该日期的航班信息如下:\n");
		sort_All_by_Time(F);

	}
	fclose(fp);

}


