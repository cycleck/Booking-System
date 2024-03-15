#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"数据结构.h"
#include <graphics.h>		//包含图形库文件
#include <conio.h>
#include<windows.h> 
#pragma warning(disable : 4996)
//***********************
//***********************
//读取当日航班信息
void ReadInfo(List_F *F)
{
	FILE*fp;
	if ((fp = fopen("data/flight/9.9航空信息.txt", "r")) == NULL)
	{
		printf("航班文件不存在 \n");
		exit(1);
	}
	else
	{
		F->count = 0;//初始化行数
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			 if ( fgetc(fp)== '\n')   //n行有（n-1）个‘\n’，去除第一行 n-1为航班数
				F->count++;
		}
		
		rewind(fp);
			for (int i = 0; i <F->count; i++)
			{
				fscanf(fp, "%s %s %s %s %s %s %d %d %d %d %s %s %s %s\n", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
					F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, &F->Flight[i].Firstfare,
					&F->Flight[i].Economfare, &F->Flight[i].Firstrest, &F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2,
					F->Flight[i].Company,F->Flight[i].Ontimerate);
				
				
            }
		
	}

}
//***********************
//***********************
//打印航班信息（用户版）
void PrintAirmsg_U(List_F F)     //购票用户使用
{
	printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格  经济舱价格   头等舱余票    经济舱余票   飞行员1    飞行员2    航空公司  准点率\n");
	printf("\n");
	for (int i = 0; i < F.count; i++)
	{
		printf(" %6s\t%5s\t %5s\t %7s\t %7s\t  %6s\t  %6d\t  %6d    %6d  %6d       %-6s    %-6s\t  %6s %7s\n", F.Flight[i].Flightnum, F.Flight[i].Flighttime_up,
			F.Flight[i].Flighttime_down, F.Flight[i].Startland, F.Flight[i].Downland, F.Flight[i].Flighttype, F.Flight[i].Firstfare,
			F.Flight[i].Economfare, F.Flight[i].Firstrest, F.Flight[i].Economrest, F.Flight[i].Pilot_1, F.Flight[i].Pilot_2, F.Flight[i].Company, F.Flight[i].Ontimerate);
	}



}
//***********************
//***********************
//打印航班信息（管理员版）
void PrintAirmsg_A(List_F F)   //管理员使用
{
	printf("航班号  起飞时间    降落时间    出发地    目的地      机型  头等舱价格 经济舱价格 头等舱余票 经济舱余票   飞行员1  飞行员2  航空公司  准点率  收入 上座率 购票数\n");
	printf("\n");
	for (int i = 0; i < F.count; i++)
	{
		printf(" %s\t %5s\t  %5s\t  %7s\t %7s\t%6s\t%6d\t%6d\t%3d\t%3d\t%5s\t%5s\t%5s\t%10s %8d\t%2.2lf\t%4d \n", F.Flight[i].Flightnum, F.Flight[i].Flighttime_up,
			F.Flight[i].Flighttime_down, F.Flight[i].Startland, F.Flight[i].Downland, F.Flight[i].Flighttype, F.Flight[i].Firstfare,
			F.Flight[i].Economfare, F.Flight[i].Firstrest, F.Flight[i].Economrest, F.Flight[i].Pilot_1, F.Flight[i].Pilot_2, F.Flight[i].Company, F.Flight[i].Ontimerate,F.Flight[i].Income,F.Flight[i].Rate,F.Flight[i].Ordernum);
	}



}
//***********************
//***********************
//读取订单文件
void Readorder(List_P *P)
{
	FILE *fp;
	if ((fp = fopen("9.9订单信息.txt", "r")) == NULL)
	{
		printf("订单文件不存在 \n");
		exit(1);
	}
	else
	{//算出文件内有几行（几条航班信息）
		P->count= 0;//初始化行数(订单数)
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行有（n-1）个‘\n’
				P->count++;
		}
		rewind(fp);//光标恢复到初始位置

		for (int i = 0; i < P->count; i++)
		{
			
			fscanf(fp, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", P->a[i].Flightnum, P->a[i].Name, P->a[i].ID, 
				P->a[i].Company, P->a[i].Seatnum,P->a[i].Time_date, P->a[i].Time_min, P->a[i].payername, P->a[i].Time_date,
				P->a[i].Flighttime_up, P->a[i].Flighttime_down, P->a[i].Startland, P->a[i].Downland, P->a[i].Flighttype, P->a[i].Pilot_1, P->a[i].Pilot_2);
		}
	}
	
}
//***********************
//***********************
//打印订单
void Printorder(List_P P)
{
	printf("航班号   姓名   身份证   航空公司        座位     时间\n");
	printf("\n");
	for (int i = 0; i < P.count; i++)
	{
		printf("%s\t %s\t %s\t %s\t %s\t %s%s\n", P.a[i].Flightnum, P.a[i].Name, P.a[i].ID, P.a[i].Company, P.a[i].Seatnum, P.a[i].Time_date, P.a[i].Time_min);

	}
}
//***********************
//***********************
//查询管理员自己所属航空公司的航班的订票情况N各航班已被订票的详细信息
//如何时哪个用户购买了哪个航班的哪个座位
void Showorder(List_F F, List_P P, Admination A)
{
	while (1)
	{
		printf("为您查询到您公司航班如下:\n");
	printf("航班号 起飞时间 降落时间  出发地            目的地         机型      头等舱价格     经济舱价格    头等舱余票 经济舱余票   飞行员1   飞行员2  航空公司\n");
	printf("\n");
	for (int i = 0; i < F.count; i++)
	{
		if (!strcmp(A.Company, F.Flight[i].Company))//比对航空公司，一致则打印
		{
			printf(" %6s\t%5s\t %5s\t %7s\t %7s\t  %6s\t  %6d\t  %6d    %6d  %6d     %6s\t%6s  %6s\n", F.Flight[i].Flightnum, F.Flight[i].Flighttime_up,
				F.Flight[i].Flighttime_down, F.Flight[i].Startland, F.Flight[i].Downland, F.Flight[i].Flighttype, F.Flight[i].Firstfare,
				F.Flight[i].Economfare, F.Flight[i].Firstrest, F.Flight[i].Economrest, F.Flight[i].Pilot_1, F.Flight[i].Pilot_2, F.Flight[i].Company);
		}
	}
	printf("请输入您想查看购票信息的航班的航班号：\n");
	char temp[7] = { 0 };       
	getchar();
	gets_s(temp);
	printf("为您查询的乘客信息如下：\n");
	printf("航班号   姓名   身份证            航空公司        座位     日期     时间\n");
	printf("\n");
	for (int i = 0; i < P.count; i++)
	{
		if (!strcmp(temp, P.a[i].Flightnum))
		{
			printf("%7s\t %10s\t %11s\t %7s\t %5s\t %5s\t %5s\n", P.a[i].Flightnum, P.a[i].Name, P.a[i].ID, P.a[i].Company, P.a[i].Seatnum, P.a[i].Time_date, P.a[i].Time_min);
		}

	}
	printf("请选择是否退出回主菜单（1.是/2.否）\n");
	int a;//判断是否退出
	scanf("%d", &a);
	if (a == 1)
	{
		return;
	}

}
	

}
//***********************
//***********************
//读取其他天航班信息
void ReadInfo_otherday(List_F *F, int i)//i 代表9月i日
{
	char  str1[20] = "航空信息.txt";
	char  str2[100] = { 0 };
	char  str3[50] = "data/flight/";
	sprintf(str2, "9.%d", i);//读出今天是几号
	strcat(str2, str1);
	strcat(str3, str2);
	FILE*fp;
	if ((fp = fopen(str3, "r")) == NULL)
	{
		printf("航班文件不存在 \n");
		exit(1);
	}
	else
	{
		F->count = 0;//初始化行数
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行有（n-1）个‘\n’
				F->count++;
		}
		
		rewind(fp);
	    for (int i = 0; i < F->count; i++)
		{
			fscanf(fp, "%s %s %s %s %s %s %d %d %d %d %s %s %s %s", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
				F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, &F->Flight[i].Firstfare,
				&F->Flight[i].Economfare, &F->Flight[i].Firstrest, &F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2, F->Flight[i].Company,F->Flight[i].Ontimerate);
		}

	}

}
//***********************
//***********************
//计算订单数上座数/总收入/上座率
void calculate_F(List_F *F)
{
	for (int i = 0; i < F->count; i++)
	{
		F->Flight[i].Firstrest -= F->Flight[i].Ordernum_firs;
		F->Flight[i].Economrest -= F->Flight[i].Ordernum_econ;
	    F->Flight[i].Ordernum = 200 - F->Flight[i].Firstrest - F->Flight[i].Economrest;//经济舱一共150座位
		F->Flight[i].Income = (150 - F->Flight[i].Economrest)*F->Flight[i].Economfare 
			+ (50 - F->Flight[i].Firstrest)*F->Flight[i].Firstfare;//头等舱一共50座位
		F->Flight[i].Rate = (double)F->Flight[i].Ordernum / 200;
    }
}
//***********************
//***********************
//按收入排序
void Income_Rank(List_F *F)
{
	FlightInfo temp = { 0 };
	for (int j = F->count; j >= 1; j--)
	{
		for (int i = 0; i <F->count - 1; i++)
		{
			if (F->Flight[i].Income < F->Flight[i + 1].Income)
			{
				temp = F->Flight[i];
				F->Flight[i] = F->Flight[i + 1];
				F->Flight[i + 1] = temp;
			}
		}
	}
}
//***********************
//***********************
//按上座率排序
void Rate_Rank(List_F *F)
{
	FlightInfo temp = {0};
	for (int j = F->count; j >= 1; j--)
	{
		for (int i = 0; i < F->count - 1; i++)
		{
			if (F->Flight[i].Rate < F->Flight[i + 1].Rate)
			{
				temp = F->Flight[i];
				F->Flight[i] = F->Flight[i + 1];
				F->Flight[i + 1] = temp;
			}
		}   
	}
}
//***********************
//***********************
//按订单数排序
void Book_Rank(List_F *F, Admination A)
{
	FlightInfo temp = { 0 };
	for (int j = F->count; j >= 1; j--)
	{
		for (int i = 0; i < F->count - 1; i++)
		{
			if (F->Flight[i].Ordernum < F->Flight[i + 1].Ordernum)
			{
				temp = F->Flight[i];
				F->Flight[i] = F->Flight[i + 1];
				F->Flight[i + 1] = temp;
			}
		}
	}
	printf("航班号 起飞时间 降落时间 出发地 目的地 机型 头等舱价格   经济舱价格    头等舱余票     经济舱余票    飞行员1    飞行员2   航空公司   订单数\n");
	printf("\n");
	for (int i = 0; i < F->count; i++)
	{
		if (!strcmp(A.Company, F->Flight[i].Company))
		{
			printf(" %6s\t%5s\t %5s\t %7s\t %7s\t  %6s\t  %6d\t  %6d    %6d  %6d       %6s\t%6s\t  %6s  %3d %10d\n", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
				F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, F->Flight[i].Firstfare,
				F->Flight[i].Economfare, F->Flight[i].Firstrest, F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2, F->Flight[i].Company,F->Flight[i].Ordernum,F->Flight[i].Ontimerate);
		}
	}
}
//***********************
//***********************
//推荐航班（推荐当日买票最多的三条）
void Recommend(List_F *F)
{
	FlightInfo temp = { 0 };
	for (int j = F->count; j >= 1; j--)
	{
		for (int i = 0; i < F->count - 1; i++)
		{
			if (F->Flight[i].Ordernum < F->Flight[i + 1].Ordernum)
			{
				temp = F->Flight[i];
				F->Flight[i] = F->Flight[i + 1];
				F->Flight[i + 1] = temp;
			}
		}
	}
	printf("*******************************************热门推荐航班***********************************************************\n");
	printf("航班号 起飞时间 降落时间 出发地 目的地 机型 头等舱价格 经济舱价格 头等舱余票 经济舱余票 飞行员1 飞行员2 航空公司 准点率\n");
	printf("\n");
	for (int i = 0; i < 3; i++)
	{
			printf(" %5s\t%5s\t%5s\t%5s\t%5s  %5s\t%5d\t%5d\t%5d\t      %5d\t%5s\t%5s\t%5s\t%5s\n", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
				F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, F->Flight[i].Firstfare,
				F->Flight[i].Economfare, F->Flight[i].Firstrest, F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2, F->Flight[i].Company,F->Flight[i].Ontimerate);
	}
	printf("******************************************************************************************************************\n");

}
//***********************
//***********************
//读取当前管理员的信息
void ReadAdmination(Admination* A)
{
	FILE*fp;
	if ((fp = fopen("当前管理员.txt", "r")) == NULL)
	{
		printf("文件不存在 \n");
		exit(1);
	}
	else
	{
	    rewind(fp);
		fscanf(fp, "%s %s", A->ID, A->Company);
		

	}


}
//***********************
//***********************
//弹出二维码
void QRcode()
{
	initgraph(500, 500, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img;
	loadimage(&img, "QR.jpg", 500, 500);
	putimage(0, 0, &img);
	Sleep(10000);
	closegraph();
}
//***********************
//***********************
//弹出登机牌
void Boardcheck(Passenger P,List_F F,int i)
{
	initgraph(800, 600, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img;//加载图片
	loadimage(&img, "登机牌.png", 800, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);


	setfillcolor(WHITE);//出发地
	fillrectangle(158, 205, 208, 235);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, "黑体");
	outtextxy(164, 212, F.Flight[i].Startland);//飞机出发地

	setfillcolor(WHITE);
	fillrectangle(375, 205, 424, 235);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, "黑体");
	outtextxy(375, 212, F.Flight[i].Downland);//飞机目的地


	setfillcolor(WHITE);
	fillrectangle(211, 277, 293, 295);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0,"黑体");
	outtextxy(216, 280, P.Name);//乘客姓名

	setfillcolor(WHITE);
	fillrectangle(395, 277, 407, 295);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, "黑体");
	outtextxy(395, 280,P.Flighttype );//仓位类型

	setfillcolor(RGB(26, 35, 126));
	solidrectangle(579, 230, 656, 360);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(18, 0, "黑体");
	outtextxy(579, 246, F.Flight[i].Flightnum);
	settextstyle(18, 0, "黑体");
	outtextxy(579, 338, P.Seatnum);//座位号

	getchar();
	getchar();
	closegraph();
}