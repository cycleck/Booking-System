#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"GetTime.h"
#include <graphics.h>		//包含图形库文件
#include <conio.h>
#include<time.h>
#include"数据结构.h"
#include"订单管理.h"
#include"登录函数.h"
#include"航班查询.h"
#include"购票.h"
char* buy(char*,char*,int);
//修改日期 2021.9.6.18：45




void ui()//界面函数
{
	User Usenow = { 0 };
	int ichioce;//用户的选择 用于跳转菜单

	//确认当前用户
	FILE *fusenow;
	fusenow=fopen("当前用户.txt", "r");
	fscanf(fusenow,"%s %s %s %s %s %s",Usenow.ID,Usenow.Name, Usenow.Sex, Usenow.Phone, Usenow.mail, Usenow.PassWord);
	fclose(fusenow);

	while (1)
	{
		printf("%s,欢迎进入航班订票系统（用户模式）\n", Usenow.Name);

		printf("*************************************************************************\n");
		printf("*                          航空订票客运系统 主菜单                      *\n");
		printf("*                         1.查询航班信息并购票                          *\n");
		printf("*                         2.查看我的订单                                *\n");
		printf("*                         3.个人信息管理                                *\n");
		printf("*                         4.退出系统                                    *\n");
		printf("*************************************************************************\n");
		printf("请选择1-4\n");
		scanf("%d", &ichioce);
		switch (ichioce)
		{
		case 1:
		{
			Select_Flight();
			FILE *ftt;
			ftt = fopen("当前订单.txt", "r");
			char Fnum[20] = "0";     //用户要购买的票的航班号
			char Ftime[20] = "0";   //用户要购买的起飞日期
			fscanf(ftt,"%s  %s", Fnum, Ftime);
			ticketBuy(Fnum,Ftime,Usenow.Name,Usenow.PassWord);       
		    break;
		}//大括号防止出现case跳过初始化问题
		case 2:myTicket(Usenow.Name); 
			break;
		case 3:changeUser();//接wbn个人信息管理函数
			break;

		case 4:exit(1);//退出
		default:printf("该项不存在，请重新输入！");
			    break;
		}


	}


}
void ticketBuy(char *Fnum,char *Ftime,char *Uname,char *Upassword) // 用于购买航班的函数，输入航班号,输入起飞日期,当前用户的姓名和密码
{
	Passenger P = { 0 };   //当前订单乘机人信息
	List_F list1 = { 0 };  //用于新买票得到行数p
	List_F list2 = { 0 }; //比对该用户之前的订单得到行数pp

    List_P Pcheck = { 0 };

	int usecho;//用户的选择 用于跳转菜单
	int flag = 0;
	int flag1 = 0;
	
	char *time=0;//记录购买时间
	char *timecheck = 0;//检测【今天】这个user今天是否买【超五张票】!!
	char timedate[12] = "0";//仅读取日期
	
	char s,ss;//接收空格
	int t = list1.count;//t是航班总数
	
	int i = 0, j = 0,k=0;//计数
	int p = 0,pp=0;//用户循环计数

	//检测【今天】这个user今天是否买【超五张票】
	//也许该作为一个函数单独写出来？。。啊但是后面验证 还要用这个订单信息
    timecheck = GetTime();
	strncpy(timedate, timecheck, 10);//【仅复制日期】到timedate
	
	
	UserReadorder(&Pcheck);//读取目前所有订单的信息到Pcheck（List_P
	for (i = 0; i <= Pcheck.count; i++)
	{
		if (!strcmp(Uname, Pcheck.a[i].payername))//筛选当前用户的订单
		{
			if(!strncmp(timedate,Pcheck.a[i].Time_date,10))//如果是今天买的票
				j++;
		}

	}

	if (j >= 5)
	{
		printf("%s,您今日已购买五张机票，不能再购买！\n", Uname);
		printf("*     按Enter键返回主菜单    *");
		scanf("%c", &s);
		return;
	}





	ReadInfo(&list1);//读航班信息
	ReadInfo(&list2);//又读了一份航班信息
	
	//筛查航班，读取出用户目前所选的那一航班所在的【行数】p
	for (p = 0; p <= list1.count; p++)
	{
		if (!strcmp(Fnum, list1.Flight[p].Flightnum))
			break;
	}



	//for (k = 0; k<= Pcheck.count; k++)//筛选出用户可能冲突的票 在所有订单里的【行数】k
	//{
	//	if (!strcmp(Uname, Pcheck.a[k].payername))//筛选当前用户的订单
	//	{
	//		if (!strcmp(Uname, Pcheck.a[k].Name))//筛选当前用户的为自己买的票
	//		{
	//			if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//如果日期与现在要买的票在一天
	//			{
	//				for (pp = 0; pp <= list1.count; pp++)//可能冲突的那个票的航班在航空信息的行数pp
	//				{
	//					if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
	//					{
	//						if (strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0)
	//						{
	//							printf("您为自己购买的该航班与之前您已购买的航班时间上冲突，请重新搜索并购买！\n\n\n");
	//							return;
	//						}
	//						else continue;
	//					}
	//					else continue;
	//				}
	//			}
	//			else continue;

	//		}
	//		else continue;
	//	}
	//	else continue;
	//}


	while (1)
	{
		printf("                 头等舱： %d元             经济舱：%d元                  \n\n", list1.Flight[p].Firstfare, list1.Flight[p].Economfare);
		printf("          1.购买头等舱       2.购买经济舱        3.取消并返回            \n");
		scanf("%d", &usecho);


		switch (usecho)
		{
		case 1:
			scanf("%c", &ss);//接收空格
			printf("请输入乘机人的姓名：\n");
			gets_s(P.Name);
			
			if (!strcmp(P.Name, Uname))//如果为自己买票
			{
				for (k = 0; k <= Pcheck.count; k++)//筛选出用户可能冲突的票 在所有订单里的【行数】k
				{
					if (!strcmp(Uname, Pcheck.a[k].payername))//筛选当前用户的订单
					{
						if (!strcmp(Uname, Pcheck.a[k].Name))//筛选当前用户的为自己买的票
						{
							if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//如果日期与现在要买的票在一天
							{
								for (pp = 0; pp <= list1.count; pp++)//可能冲突的那个票的航班在航空信息的行数pp
								{
									if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
									{
										if ((strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0) && (strcmp(list2.Flight[pp].Flighttime_up, list1.Flight[pp].Flighttime_down) < 0))
										{
											printf("您为自己购买的该航班与之前您已购买的航班时间上冲突，请重新搜索并购买！\n\n\n");
											return;
										}
										else continue;
									}
									else continue;
								}
							}
							else continue;

						}
						else continue;
					}
					else continue;
				}
			}



			//这里不用接受回车了因为上面的字符串末端接收了 第一个是因为前一个变量是int
			printf("请输入乘机人的ID：\n");
			gets_s(P.ID);

			strcpy(P.Seatnum, checkSeatFir());//选择座位并将数据传递给用户订单数据结构P
			

			printf("*请支付%d元*\n", list1.Flight[p].Firstfare);
			printf("选择支付方式（1.用户密码支付/2.扫码支付）\n");
			
			scanf("%d", &flag);
			switch (flag)
			{
			case 1:
				checkPass(Upassword);
				break;
			case 2:
				QRcode();
				char usesec[20];
				printf("请输入登陆密码（即支付密码）：\n");
				while (1)
				{
					scanf("%s", usesec);
					if (strcmp(usesec, "asdfg"))
					{
						printf("密码错误，请重新输入！\n");
					}
					else break;
				}

				printf("密码正确，支付成功，已成功购票！\n");
				break;
			default:
				break;
			}
			sprintf(P.Flighttype, "头等舱");
			printf("*正在出票*\n");
			printf("。\n");
			Sleep(1000);
			printf("。\n");
			Sleep(1000);
			printf("。\n");
			Sleep(1000);
			Boardcheck(P,list1,p);

			time = GetTime();//获取购买时间
			list1.Flight[p].Ordernum_firs++;//第p行的航班头等票+1张

			FILE *fa;//写用户购票文件的文件指针
			fa = fopen("9.9订单信息.txt", "a");

			//fprintf(fa, "航班号	    登机人	   ID     航空公司       座位     付款时间        付款人    航班信息（起飞日期 起飞时间 降落时间 出发地 目的地 机型 飞行员1 飞行员2）\n");
			fprintf(fa, "%-8s %-10s %-12s %-10s %-10s   %-10s      %-10s  %-10s  %-10s  %-8s  %-8s  %-8s  %-8s  %-8s  %-8s\n", 
				list1.Flight[p].Flightnum, P.Name, P.ID, list1.Flight[p].Company, 
				P.Seatnum, time,Uname, Ftime,list1.Flight[p].Flighttime_up, 
				list1.Flight[p].Flighttime_down, list1.Flight[p].Startland, list1.Flight[p].Downland, 
				list1.Flight[p].Flighttype, list1.Flight[p].Pilot_1, list1.Flight[p].Pilot_2);
			
			scanf("%c", &ss);//怎么又需要个接收
			printf("*     按Enter键返回主菜单    *");
			scanf("%c", &s);
			fclose(fa);

			break;
		case 2:
			printf("请输入乘机人的姓名：\n");
			scanf("%c", &ss);
			gets_s(P.Name);
			if (!strcmp(P.Name, Uname))//如果为自己买票
			{
				for (k = 0; k <= Pcheck.count; k++)//筛选出用户可能冲突的票 在所有订单里的【行数】k
				{
					if (!strcmp(Uname, Pcheck.a[k].payername))//筛选当前用户的订单
					{
						if (!strcmp(Uname, Pcheck.a[k].Name))//筛选当前用户的为自己买的票
						{
							if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//如果日期与现在要买的票在一天
							{
								for (pp = 0; pp <= list1.count; pp++)//可能冲突的那个票的航班在航空信息的行数pp
								{
									if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
									{
										if ((strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0) && (strcmp(list2.Flight[pp].Flighttime_up, list1.Flight[pp].Flighttime_down) < 0))
										{
											printf("您为自己购买的该航班与之前您已购买的航班时间上冲突，请重新搜索并购买！\n\n\n");
											return;
										}
										else continue;
									}
									else continue;
								}
							}
							else continue;

						}
						else continue;
					}
					else continue;
				}
			}


			printf("请输入乘机人的ID：\n");
			gets_s(P.ID);
			strcpy(P.Seatnum, checkSeatEco());//选择座位并将数据传递给用户订单数据结构P
			
			//支付，验证密码
			printf("*请支付%d元*\n", list1.Flight[p].Economfare);

			printf("选择支付方式（1.用户密码支付/2.扫码支付）\n");
			
			scanf("%d", &flag1);
			switch (flag1)
			{
			case 1:
				checkPass(Upassword);
				break;
			case 2:
				QRcode();
				char usesec[20];
				printf("请输入验证码：\n");
				while (1)
				{
					scanf("%s", usesec);
					if (strcmp(usesec, "asdfg"))
					{
						printf("密码错误，请重新输入！\n");
					}
					else break;
				}

				printf("密码正确，支付成功，已成功购票！\n");
				break;
			default:
				break;
			}
			
			sprintf(P.Flighttype, "经济舱");
			printf("*正在出票*\n");
			printf("。\n");
			Sleep(1000);
			printf("。\n");
			Sleep(1000);
			printf("。\n");
			Sleep(1000);
			Boardcheck(P,list1,p);

			time = GetTime();//获取购买时间
			list1.Flight[p].Ordernum_econ++;//第p行的航班经济票+1张


			FILE *fr;//写用户购票文件的文件指针
			fr = fopen("9.9订单信息.txt", "a");
			//fprintf(fr, "航班号	     姓名	      ID	    航空公司     座位   付款时间     航班信息（起飞时间 降落时间 出发地 目的地 机型 飞行员1 飞行员2）\n");
			fprintf(fr, "%-8s %-10s %-12s %-10s %-10s   %-10s      %-10s  %-10s  %-10s  %-8s  %-8s  %-8s  %-8s  %-8s  %-8s\n",
				list1.Flight[p].Flightnum, P.Name, P.ID, list1.Flight[p].Company,
				P.Seatnum, time, Uname, Ftime, list1.Flight[p].Flighttime_up,
				list1.Flight[p].Flighttime_down, list1.Flight[p].Startland, list1.Flight[p].Downland,
				list1.Flight[p].Flighttype, list1.Flight[p].Pilot_1, list1.Flight[p].Pilot_2);
			
			scanf("%c", &ss);//怎么又需要个接收
			printf("*     按Enter键返回主菜单    *");
			scanf("%c", &s);
			fclose(fr);
			break;
		case 3:  //怎么返回啊
			break;

		default:printf("该项不存在，请重新输入！\n");    //怎么重新输入最简单？ 加while（1）！

		};
		return;//返回到主菜单，好使！！
	};


}

void myTicket(char *Uname)
{
	char s,ss;//接收回车

	List_P P = { 0 };
	UserReadorder(&P);//读取所有订单的信息
	
	printf("%s，您好! 为您查询到您的订单如下：\n", Uname);
	printf("航班号   登机人    ID          航空公司 座位        付款时间             付款人    起飞日期\n");
	//开始筛选
	int i = 0,j=0;//counting
	for (i = 0; i <= P.count; i++)
	{
		if (!strcmp(Uname, P.a[i].payername))
		{
		printf("%-8s %-8s %-12s %-6s %-5s %-12s %-12s %-8s %-8s\n",
		P.a[i].Flightnum, P.a[i].Name, P.a[i].ID, P.a[i].Company, P.a[i].Seatnum, 
		P.a[i].Time_date, P.a[i].Time_min, P.a[i].payername, P.a[i].FlyTime);
		j = j + 1;
		}

	}
	if (0 == j)
		printf("您当前还没有订单！\n");
	scanf("%c", &ss);//怎么又需要个接收
	printf("*     按Enter键返回主菜单    *");
	scanf("%c", &s);
}

void UserReadorder(List_P *P)
{
	FILE *fp;
	if ((fp = fopen("9.9订单信息.txt", "r")) == NULL)
	{
		printf("订单文件不存在 \n");
		exit(1);
	}
	else
	{
		P->count = 0;//初始化行数(订单数)
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行有（n-1）个‘\n’，去除第一行 n-1为航班数
				P->count++;
		}
		rewind(fp);
		//char temp[300] = { 0 };
		//fgets(temp, 300, fp);
		for (int i = 0; i < P->count; i++)
		{
			char ID[20];

			//yza修改，因为我不会读一半跳到下一行。。所以我就全都读进去
			fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
				P->a[i].Flightnum, P->a[i].Name, P->a[i].ID, P->a[i].Company, P->a[i].Seatnum, P->a[i].Time_date, P->a[i].Time_min, P->a[i].payername,
				P->a[i].FlyTime, P->a[i].Flighttime_up, P->a[i].Flighttime_down, P->a[i].Startland, P->a[i].Downland,
				P->a[i].Flighttype, P->a[i].Pilot_1, P->a[i].Pilot_2);
		}
		fclose(fp);
	}
}

void checkPass(char *Upassword)
{
	char usesec[20];//用户输入的密码，用于验证比对是否正确


	printf("请输入登陆密码（即支付密码）：\n");
	while (1)
	{
		scanf("%s", usesec);
		if (strcmp(usesec, Upassword))
		{
			printf("密码错误，请重新输入！\n");
		}
		else break;
	}

	printf("密码正确，支付成功，已成功购票！\n");

}

char* checkSeatFir()
{

	char seat1[20];//排数
    char seat2[20];//座位号
	char seat[10] = "F";
	strcat(seat,buy(seat1, seat2,1));
	printf("座位选择成功！\n");
	return seat;
}
char* checkSeatEco()
{
	char seat1[20] = {0};//排数
	char seat2[20] = {0};//座位号
	char seat[10] = "Y";
	strcat(seat, buy(seat1, seat2, 2));
	printf("座位选择成功！\n");
	return seat;
}


char* buy(char* c1,char* c2,int q)
{
	char seatnum[5] = { 'A','B','C','D','E' };
	time_t ts;
	unsigned int num = time(&ts);
	srand(num);
	int a = rand() % 5;
	int b = 0;
	
	initgraph(1300, 800, SHOWCONSOLE);

	setbkcolor(WHITE);
	cleardevice();

	IMAGE img, img1, img2;
	loadimage(&img, "飞机.jpg", 1300, 800);
	putimage(0, 0, &img);
	settextcolor(BLACK);
	settextstyle(30, 0, "楷体");
	if (q == 1)
	{
		outtextxy(460, 300, "请输入排数（1-10）:");
		InputBox(c1, 10, "请输入排数（1-10）:");
	}
	else
	{
		outtextxy(460, 300, "请输入排数（11-30）:");
		InputBox(c1, 10, "请输入排数（11-30）:");
	}
	for (int i = 0; i < 5; i++)
	{
      outtextxy(420 + i * 90, 430, seatnum[i]);
		if (i == a)
		{
			loadimage(&img2, "红座位.png", 50, 50);
			putimage(420 + i * 90, 480, &img2);
			continue;
		}
		
		loadimage(&img1, "白座位.png", 50, 50);

		putimage(420 + i * 90, 480, &img1);

	}
	
	while (1)
	{
		

ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{


			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 420 + 90 * a && msg.x < 470 + 90 * a && msg.y>480 && msg.y < 530)
				{
					setbkmode(TRANSPARENT);
					settextcolor(RED);
					settextstyle(50, 0, "楷体");
					outtextxy(460, 570, "该座位已有人！");
				}
				else {
					if (msg.x > 420 && msg.x < 470 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "绿座位.png", 50, 50);
						b = 1;
						putimage(420, 480, &img1);
						sprintf(c2, "A");
						break;

					}
					else if
						(msg.x > 420 + 90 && msg.x < 470 + 90 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "绿座位.png", 50, 50);
						b = 1;
						putimage(420 + 90, 480, &img1);
						sprintf(c2, "B");
						break;
					}
					else if (msg.x > 420 + 180 && msg.x < 470 + 180 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "绿座位.png", 50, 50);
						b = 1;
						putimage(420 + 180, 480, &img1);
						sprintf(c2, "C");
						break;
					}
					else if (msg.x > 420 + 270 && msg.x < 470 + 270 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "绿座位.png", 50, 50);
						b = 1;
						putimage(420 + 270, 480, &img1);
						sprintf(c2, "D");
						break;
					}
					else if (msg.x > 420 + 360 && msg.x < 470 + 360 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "绿座位.png", 50, 50);
						b = 1;
						putimage(420 + 360, 480, &img1);
						sprintf(c2, "E");
						break;
					}
					
					

				}

			}
			if (b == 1)
			{
				strcat(c1, c2);
				getchar();
				closegraph();
				return c1;
			}

		}

	}
}