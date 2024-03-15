#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "数据结构.h"
#include "管理员航班查询及添加.h"
#pragma warning(disable : 4996)

/*声明结构体所在的头文件*/

/*判断飞行员姓名是否为汉语*/
int is_Chinese(char* str)
{
	int len = strlen(str);
	/*判断字符串长度是否大于2且为2的倍数*/
	if (len < 2 && len%2 )
	{
		return 0;
	}
	for (int i = 0; i < len; i++)
	{
		if (~(str[i]>> 8) != 0)
		{
		return 0; //代表不是汉字
		}
	}
	return 1;
}

/*航班查询*/
void search_Flight() 
{	
	FILE *Admin_list,*Flight_list;//分别打开管理员文件与航班文件的指针
	Admin_list = fopen("当前管理员.txt", "r");//打开管理员文件
	if (Admin_list == NULL) {
		exit(1);
	}
	Admination Admin;//用于储存当前管理员信息
	fscanf(Admin_list, "%s%s%s%s%s", Admin.ID, Admin.Company, Admin.Name, Admin.mail, Admin.Password);
	fclose(Admin_list);//关闭管理员文件
	
	Flight_list = fopen("9.1航班信息.txt", "r");//打开航班信息文件
	if (Flight_list == NULL) {
		exit(1);
	}
	FlightInfo Flight;//用于储存当前航班信息

	int cons = 0;//用于判断现有航班中是否有该公司航班
	printf("航班号  起飞时间  降落时间  出发地  目的地  机型  头等舱价格  经济舱价格   头等舱余票  经济舱余票  飞行员1  飞行员2  航空公司 准点率\n");
	printf("\n");

	//读入所有航班信息，并与管理员所属公司比较
	while (fscanf(Flight_list, "%s%s%s%s%s%s%d%d%d%d%s%s%s%s", Flight.Flightnum, Flight.Flighttime_up,
		Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, &Flight.Firstfare,
		&Flight.Economfare, &Flight.Firstrest, &Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2, 
		Flight.Company,Flight.Ontimerate) != EOF)
	{
		if ( strcmp( Admin.Company , Flight.Company ) == 0)//当前航班与管理员在同一公司
		{
			
			printf(" %6s\t   %6s\t   %6s\t   %6s\t   %6s\t   %6s\t   %5d\t   %5d\t  %5d\t   %5d\t    %3s\t  %3s\t  %6s\n", 
				Flight.Flightnum, Flight.Flighttime_up,
					Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, Flight.Firstfare,
					Flight.Economfare, Flight.Firstrest, Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2, Flight.Company);//输出当前航班信息
			cons = 1;
		}
	}
	//当前所有航班中无该公司航班
	if (!cons) {
		printf("暂无该公司航班信息\n");
	}
	fclose(Flight_list);//关闭航班信息文件

}

/*选择城市*/
char* choose_City() 
{
	FILE *fp = fopen("data/city/省份.txt", "r");
	if (fp == NULL) {
		exit(1);
	}
	int num;/*用于记录省份序号*/
	char  Place[50];
	printf("*    请选择省份或输入目的城市中文名称：\n");
	while (fscanf(fp, "%d%s", &num, Place) != EOF)
	{
		printf("*    %d. %s\n", num, Place);
	}
	fclose(fp);
	while (1)
	{
		char In[50];
		memset(In, '/0', sizeof In);
		scanf("%s", In);
		if (In[0] > '0'&&In[0] <= '9')
		{
			int cnt;/*用于记录城市序号*/
			if (In[1] >= '0'&&In[1] <= '9')
			{
				cnt = (In[0] - '0') * 10 + In[1] - '0';
			}
			else
			{
				cnt = In[0] - '0';
			}
			fp = fopen("data/city/省份.txt", "r");
			if (fp == NULL) {
				exit(1);
			}
			while (fscanf(fp, "%d%s", &num, Place) != EOF)
			{
				if (cnt == num)
				{
					fclose(fp);
					char str[1000]="data/city/", out[] = ".txt";
					strcat(str, Place);
					strcat(str, out);
					FILE *hp = fopen(str, "r");
					if (hp == NULL)
					{
						return Place;
					}
					else
					{
						while (1)
						{
							printf("*    请选择城市序号或输入目的城市中文名称：\n");
							printf("*    输入“*”取消选择\n");
							printf("*    输入“返回”返回上一界面\n");
							while (fscanf(hp, "%d%s", &num, Place) != EOF)
							{
								printf("*    %d.%s\n", num, Place);
							}
							fclose(hp);
							memset(In, '/0', sizeof In);
							scanf("%s", In);
							if (In[0] > '0'&&In[0] < '9')
							{
								if (In[1] > '0'&&In[1] < '9')
								{
									cnt = (In[0] - '0') * 10 + In[1] - '0';
								}
								else
								{
									cnt = In[0] - '0';
								}
								hp = fopen(str, "r");
								while (fscanf(hp, "%d%s", &num, Place) != EOF)
								{
									if (cnt == num)
									{
										fclose(hp);
										return Place;

									}
								}
							}
							else if (In[0] == '*')
							{
								return In;
							}
							else
							{
								if (is_Chinese(In))
								{
									if (!strcmp(In, "返回")) {
										break;
									}
									FILE *tp = fopen("data/city/地区代码.txt", "r");
									if (tp == NULL) {
										exit(1);
									}
									while (fscanf(tp, "%d%s", &num, Place) != EOF)
									{
										if (!strcmp(In, Place)) {
											return Place;
										}
									}
									fclose(tp);
									printf("无法选择该城市，请重新选择\n");
								}
								else
								{
									printf("输入错误，请重新选择\n");
								}

							}
						}
					}
					break;
				}
			}
		}
		else if (In[0] == '*')
		{
			return In;
		}
		else
		{
			if (is_Chinese(In))
			{
				FILE *tp = fopen("data/city/地区代码.txt", "r");
				if (tp == NULL) {
					exit(1);
				}
				while (fscanf(tp, "%d%s", &num, Place) != EOF)
				{
					if (!strcmp(In, Place)) {
						return Place;
					}
				}
				fclose(tp);
				printf("*    无法选择该城市，请重新选择\n");
				continue;
			}
			else
			{
				printf("*    输入错误，请重新选择\n");
				continue;
			}

		}
	}
}

/*生成航班号*/
char *build_Flightnum(FlightInfo Now, FlightInfo Past)
{	
	memset(Now.Flightnum, '\0', sizeof Now.Flightnum);
	/*前两位生成公司代号*/
	FILE *Cmy = fopen("航空公司.txt", "r");
	if ( Cmy == NULL) {
		exit(1);
	}
	char Company[50], Cmy_sig[10];
	while (fscanf(Cmy, "%s%s", Company,Cmy_sig) != EOF) 
	{
		if (strcmp(Company, Now.Company) == 0)
		{
			Now.Flightnum[0] = Cmy_sig[0];
			Now.Flightnum[1] = Cmy_sig[1];
			break;
		}
	}
	fclose(Cmy);
	/*第三第四位分别为出发地与目的地的地区代号*/
	FILE *City = fopen("data/city/地区代码.txt", "r");
	if (City == NULL) {
		exit(1);
	}
	char Land[50], Land_sig[10];
	int cnt = 2;//用于判断目的地与出发地代码是否生成完毕
	while (fscanf(City, "%s %s",Land_sig,Land) != EOF && cnt)
	{
		if (strcmp(Land, Now.Startland) == 0)
		{
			Now.Flightnum[2] = Land_sig[0];
			--cnt;
		}
		if (strcmp(Land, Now.Downland) == 0)
		{
			Now.Flightnum[3] = Land_sig[0];
			--cnt;
		}
	}
	fclose(City);

	/*生成后两位航班号，第五位为航班序号，第六位的奇偶表示去回*/
	if (strcmp(Now.Company, Past.Company) == 0)
	{	
		/*若两航班的起点终点恰好颠倒，说明为去回程航班，只改变第六位*/
		if (strcmp(Now.Downland, Past.Startland) == 0 && strcmp(Now.Startland, Past.Downland) == 0)
		{	
			/*防止序号溢出*/
			if (Past.Flightnum[5] == '9')
			{
				Now.Flightnum[5] = '0';
			}
			else
			{
				Now.Flightnum[5] = Past.Flightnum[5] + 1;
				Now.Flightnum[4] = Past.Flightnum[4];
			}
		}


		/*起点终点相同，说明为该航空公司在该条路线上有多条航班*/
		else if (strcmp(Now.Downland, Past.Downland) == 0 && strcmp(Now.Startland, Past.Startland) == 0)
		{
			/*防止序号溢出*/
			if (Past.Flightnum[4] == '9')
			{
				Now.Flightnum[4] = '1';
			}
			else
			{
				Now.Flightnum[4] = Past.Flightnum[4] + 1;
				Now.Flightnum[5] = Past.Flightnum[5];
			}
			
		}
		else
		{
			Now.Flightnum[4] = '0';
			Now.Flightnum[5] = '0';
		}
	}

	else
	{
		Now.Flightnum[4] = '0';
		Now.Flightnum[5] = '0';
	}
	
	return Now.Flightnum;
}

/*输入航班*/
int in_Put(FlightInfo* Flight_new)
{
	/*输入航班信息*/
	FlightInfo Now;
	/*输入预处理*/
	char in[10][50] = { {"起飞时间"},{"降落时间"},{"出发地"},{"目的地"},{"机型 "},
						{"头等舱价格" }, {"经济舱价格"}, {"飞行员1"}, {"飞行员2"}};
	printf("请输入航班信息：\n请输入对应信息序号进行添加\n");
	int last = 9,sum = 9, Has_in_put;/*last代表未填信息总数，sum代表当前未填信息总数，Has_in_put代表已填入信息序号*/

	while (sum > 0)
	{
		
		for (int i = 0; i < 9; i++)
		{
			if (in[i][0] != '\0')
			{
				printf("*    %d. %s       \n", i, in[i]);
			}
		}
		printf("输入“*”取消输入\n\n");

		char num,ch;
		ch = getchar();
		scanf("%c", &num);
		if (in[num - '0'][0] == '\0') {
			num = '-';
		}
		
		switch (num)
		{
		case '*':/*取消输入*/
		{
			printf("*    已取消输入\n");
			return 0;
		}
		case '0':/*起飞时间*/
		{
			while(1){
				printf("*    输入“*”取消输入\n");
				printf("*    起飞时间：（形如xx:xx，24时制）  ");
				char str[50];/*读入时间*/
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("*    已取消输入\n");
					break;
				}
				else
				{
					int len = strlen(str);
					if (len != 5 || str[2] != ':')
					{
						printf("*    输入不合法\n");
						continue;
					}
					else {
						strcpy(Now.Flighttime_up, str);
						printf("\n*    输入成功\n");
						sum--;
						break;
					}
				}
			}
			break;
		}
		case '1':/*降落时间*/
		{
			while (1) {
				printf("*    输入“*”取消输入\n");
				printf("*    降落时间：（形如xx;xx，24时制）  ");
				char str[50];/*读入时间*/
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*     已取消输入\n");
					break;
				}
				else
				{
					int len = strlen(str);
					if (len != 5 || str[2] != ':')
					{
						printf("*    输入不合法\n");
						continue;
					}
					else {
						sum--;
						printf("\n*    输入成功\n");
						strcpy(Now.Flighttime_down, str);
						break;
					}
				}
			}
			break;
		}
		/*出发地*/
		case '2':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    请选择出发地： ");
			char str[50];
			strcpy(str, choose_City());
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			else
			{
				sum--;
				printf("\n*    输入成功\n");
				strcpy(Now.Startland, str);
			}
			break;
		}
		/*目的地*/
		case '3':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    目的地： ");
			char str[50];
			strcpy(str, choose_City());
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			else
			{
				sum--;
				printf("\n*    输入成功\n");
				strcpy(Now.Downland, str);
			}
			break;
		}
		/*机型*/
		case '4':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    机型： (请输入机型名称，以下为可选机型)\n");
			printf("*    1.JET\n");
			printf("*    2.空客320\n");
			printf("*    3.空客321\n");
			printf("*    4.波音737\n");
			printf("*    请输入机型：");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			else
			{
				sum--; 

				printf("\n*    输入成功\n");
				strcpy(Now.Flighttype, str);
			}
			break;
		}
		/*头等舱价格*/
		case '5':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    头等舱价格： ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			else
			{
				int num = 0, len = strlen(str);
				for (int i = 0; i < len; i++)
				{
					num *= 10;
					num += (str[i] - '0');
				}
				Now.Firstfare = num;
				printf("\n*    输入成功\n");
				sum--;
			}
			break;
		}
		/*经济舱价格*/
		case '6':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    经济舱价格： ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			else
			{
				int num = 0, len = strlen(str);
				for (int i = 0; i < len; i++)
				{
					num *= 10;
					num += (str[i] - '0');
				}
				Now.Economfare = num;
				printf("\n*    输入成功\n");
				sum--;
			}
			break;
		}
		/*飞行员1*/
		case '7':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    飞行员1： ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			int flag = 1;//用于判断是否输入成功
			/*判断输入是否为中文，否则重新输入*/
			while (!is_Chinese(str))
			{
				printf("*    输入不合法，请重新输入\n");
				printf("*    输入“*”取消输入\n");
				printf("*    飞行员1： ");
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*    已取消输入\n");
					flag = 0;
					break;
				}
			}
			/*输入成功*/
			if (flag)
			{
				strcpy(Now.Pilot_1, str);
				sum--;
				printf("\n*    输入成功\n");
				break;
			}
			break;
		}
		/*飞行员2*/
		case '8':
		{
			printf("*    输入“*”取消输入\n");
			printf("*    飞行员2： ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    已取消输入\n");
				break;
			}
			int flag = 1;//用于判断是否输入成功
			/*判断输入是否为中文，否则重新输入*/
			while (!is_Chinese(str))
			{
				printf("*    输入不合法，请重新输入\n");
				printf("*    输入“*”取消输入\n");
				printf("*    飞行员2： \n");
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*    已取消输入\n");
					flag = 0;
					break;
				}
			}
			/*输入成功*/
			if (flag)
			{
				strcpy(Now.Pilot_2, str);
				printf("\n*    输入成功\n");
				sum--;
				break;
			}
			break;
		}
		default: 
		{
			printf("错误输入，请重新输入.\n");
			break;
		}
		}
		/*判断是否已经成功填写了一项内容，若成功，则将该项删去*/
		if (num >= '0'&&num <= '8'&&last - sum == 1)
		{
			last--;
			Has_in_put = num - '0';
			memset(in[Has_in_put], '\0', sizeof in[Has_in_put]);
			
		}
	}
	if (!sum)
	{
		printf("*    添加完成！\n");
		strcpy(Flight_new->Downland , Now.Downland);
		strcpy(Flight_new->Startland, Now.Startland);
		strcpy(Flight_new->Flighttime_down, Now.Flighttime_down);
		strcpy(Flight_new->Flighttime_up, Now.Flighttime_up);
		strcpy(Flight_new->Flighttype, Now.Flighttype);
		strcpy(Flight_new->Pilot_1, Now.Pilot_1);
		strcpy(Flight_new->Pilot_2, Now.Pilot_2);
		Flight_new->Economfare = Now.Economfare;
		Flight_new->Firstfare = Now.Firstfare;
		
		return 1;
	}
	else
	{
		return 0;
	}
}

/*判断时间是否冲突*/
int judge_Time(FlightInfo Now,FlightInfo Past) 
{
	/*计算间隔时间差*/
	int	Hour = (Now.Flighttime_up[0] - '0') * 10 + (Now.Flighttime_up[1] - '0');
	int	Min = (Now.Flighttime_up[3] - '0') * 10 + (Now.Flighttime_up[4] - '0');
	Hour -= (Past.Flighttime_down[0] - '0') * 10 + (Past.Flighttime_down[1] - '0');
	Min -= (Past.Flighttime_down[3] - '0') * 10 + (Past.Flighttime_down[4] - '0');
	int Time_1 = Hour * 60 - Min;
	Hour = (Now.Flighttime_down[0] - '0') * 10 + (Now.Flighttime_down[1] - '0');
	Min = (Now.Flighttime_down[3] - '0') * 10 + (Now.Flighttime_down[4] - '0');
	Hour -= (Past.Flighttime_up[0] - '0') * 10 + (Past.Flighttime_up[1] - '0');
	Min -= (Past.Flighttime_up[3] - '0') * 10 + (Past.Flighttime_up[4] - '0');
	int Time_2 = Hour * 60 - Min;
	/*当前出发时间在历史航班到达时间之前，而当前到达时间在历史航班出发时间之后则有冲突*/
	 if (Time_1<0&&Time_2>0)
	 {
		return 0;
	 }
	 /*无冲突*/
	 return 1;
	
}

/*判断地点是否冲突*/
int judge_Land(FlightInfo Now, FlightInfo Past)
{	
	/*当前航班的起点是历史航班的重点*/
	if (strcmp(Now.Downland, Past.Startland) == 0)
	{
		/*计算间隔时间*/
		int	Hour = (Now.Flighttime_up[0] - '0') * 10 + (Now.Flighttime_up[1] - '0');
		int	Min = (Now.Flighttime_up[3] - '0') * 10 + (Now.Flighttime_up[4] - '0');
		Hour -= (Past.Flighttime_down[0] - '0') * 10 + (Past.Flighttime_down[1] - '0');
		Min -= (Past.Flighttime_down[3] - '0') * 10 + (Past.Flighttime_down[4] - '0');
		int Time = Hour * 60 - Min;
		/*间隔时间大于30min，则地点不冲突*/
		if (Time >= 30)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else {
		return 0;
	}
}

/*修改航班信息*/
void modify_Flight(FlightInfo* Flight_new)
{
	FlightInfo Now;
	strcpy(Now.Downland, Flight_new->Downland);
	strcpy(Now.Startland,Flight_new->Startland);
	strcpy(Now.Flighttime_down, Flight_new->Flighttime_down);
	strcpy(Now.Flighttime_up, Flight_new->Flighttime_up);
	strcpy(Now.Flighttype, Flight_new->Flighttype);
	strcpy(Now.Pilot_1, Flight_new->Pilot_1);
	strcpy(Now.Pilot_2, Flight_new->Pilot_2);
	Now.Economfare = Flight_new->Economfare;
	Now.Firstfare = Flight_new->Firstfare;
	while (1)
	{	
		char ch;
		ch = getchar();
		printf("*    请输入需要修改信息的序号:\n");
		printf("*    1.机型: %s\n*    2.头等舱票价: %d\n",Now.Flighttype, Now.Firstfare);
		printf("*    3.经济舱票价: %d\n*    4.起飞地: %s\n*    5.降落地: %s\n", Now.Economfare, Now.Startland, Now.Downland);
		printf("*    6.起飞时间: %s\n*    7.降落时间: %s\n*    8.飞行员1: %s\n*    9.飞行员2: %s\n\n", Now.Flighttime_up, Now.Flighttime_down, Now.Pilot_1,Now.Pilot_2);
		printf("*    0.完成修改\n\n");
		printf("*    *.取消修改\n\n");
		scanf("%c", &ch);
		switch (ch)
		{
			case '1':
			{	
				printf("*    1.机型:\n");
				scanf("%s", Now.Flighttype);
				printf("*    修改成功\n\n");
				break;

			}
			case '2':
			{
				printf("*    2.头等舱票价:\n");
				scanf("%d", &Now.Firstfare);
				printf("\n修改成功\n\n");
				break;
			}
			case '3':
			{
				printf("*    3.经济舱票价:\n");
				scanf("%d", &Now.Economfare);
				printf("\n修改成功\n\n");
				break;
			}
			case '4':
			{
				printf("*    4.起飞地:\n");
				scanf("%s", Now.Startland);
				printf("\n修改成功\n\n");
				break;
			}
			case '5':
			{
				printf("*    5.降落地:\n");
				scanf("%s", Now.Downland);
				printf("\n修改成功\n\n");
				break;
			}
			case '6':
			{
				printf("*    6.起飞时间:\n");
				scanf("%s", Now.Flighttime_up);
				printf("\n修改成功\n\n");
				break;
			}
			case '7':
			{
				printf("*    7.降落时间:\n");
				scanf("%s", Now.Flighttime_down);
				printf("\n修改成功\n\n");
			}
			case '8':
			{
				printf("*    8.飞行员1:\n");
				scanf("%s", Now.Pilot_1);
				printf("\n修改成功\n\n");
				break;
			}
			case '9':
			{
				printf("*    9.飞行员2:\n");
				scanf("%s", Now.Pilot_2);
				printf("\n修改成功\n\n");
				break;
			}
			case '0':
			{
				printf("*    修改成功\n\n");
				strcpy(Flight_new->Downland, Now.Downland);
				strcpy(Flight_new->Startland, Now.Startland);
				strcpy(Flight_new->Flighttime_down, Now.Flighttime_down);
				strcpy(Flight_new->Flighttime_up, Now.Flighttime_up);
				strcpy(Flight_new->Flighttype, Now.Flighttype);
				strcpy(Flight_new->Pilot_1, Now.Pilot_1);
				strcpy(Flight_new->Pilot_2, Now.Pilot_2);
				Flight_new->Economfare = Now.Economfare;
				Flight_new->Firstfare = Now.Firstfare;
				return;
				break;
			}
			case '*':
			{
				printf("*    已取消修改\n");
				return;
				break;
			}
			default:
			{
				printf("*    错误指令，请重新输入\n");
				break;
			}

		}
	}
	return ;
}

/*判断修改飞行员信息是否需要验证*/
int modify_Polit(int On_plane_1, int On_plane_2, FlightInfo *Flight_new)
{
	/*2号飞行员参与航班*/
	if (On_plane_1 != 0)
	{
		while (1)
		{
			printf("请重新填入2号飞行员\n输入\"0\"取消航班录入\n");
			char str[1000];
			scanf("%s", str);
			if (str[0] == '0')
			{
				printf("已取消添加\n");
				return 1;
				break;
			}
			else if (!is_Chinese(str))
			{
				printf("输入不合法，请重新输入\n");
				continue;
			}
			else
			{
				strcpy(Flight_new->Pilot_2, str);
				return 0;
				break;
			}
		}

	}
	/*1号飞行员参与航班*/
	else if (On_plane_2 != 0)
	{
		while (1)
		{
			printf("请重新填入1号飞行员\n输入\"0\"取消航班录入\n");
			char str[1000];
			scanf("%s", str);
			if (str[0] = '0')
			{
				printf("已取消添加\n");
				return 1;
				break;
			}
			else if (!is_Chinese(str))
			{
				printf("输入不合法，请重新输入\n");
				continue;
			}
			else
			{
				strcpy(Flight_new ->Pilot_1, str);
				return 0;
				break;
			}
		}
	}
	/*两名飞行员均参与航班*/
	else
	{
		while (1)
		{
			printf("请重新填入两名飞行员\n输入\"0\"取消航班录入\n");
			char str_1[1000], str_2[1000];
			printf("1号飞行员    2号飞行员\n");
			scanf("%s", str_1);
			if (str_1[0] = '0')
			{
				printf("已取消添加\n");
				return 1;
				break;
			}
			scanf("%s", str_2);
			if (!is_Chinese(str_1) || !is_Chinese(str_2))
			{
				printf("输入不合法，请重新输入\n");
				continue;
			}
			else
			{
				strcpy(Flight_new ->Pilot_1, str_1);
				strcpy(Flight_new ->Pilot_2, str_2);
				return 0;
				break;
			}

		}

	}
}

/*进行下一步操作并判断是否需要验证*/
int reserve_Flight(FlightInfo* Flight_new)
{
	printf("*    航班可以录入!\n");
	while (1)
	{
		printf("*    输入\"1\"发布航班信息\n*    输入\"2\"修改航班信息\n*    输入\"0\"取消添加航班信息\n\n");
		/*输出航班信息*/
		printf("航班号    起飞时间         降落时间        出发地  目的地   机型       头等舱价格  经济舱价格   头等舱余票    经济舱余票   飞行员1       飞行员2          航空公司\n");
		printf("\n");
		printf(" %s\t   %s\t   %s\t   %s\t   %s\t   %5s\t   %d\t   %d\t           %d\t         %d\t    %s\t  %s\t  %s\n",
			Flight_new->Flightnum, Flight_new->Flighttime_up,
			Flight_new->Flighttime_down, Flight_new->Startland,
			Flight_new->Downland, Flight_new->Flighttype, Flight_new->Firstfare,
			Flight_new->Economfare, Flight_new->Firstrest, Flight_new->Economrest,
			Flight_new->Pilot_1, Flight_new->Pilot_2, Flight_new->Company);
		char Command;
		char i = getchar();
		scanf("%c", &Command);
		
		switch (Command)
		{	
			/*发布航班信息，将航班信息添加到航班文件最后一行*/
			case '1':
			{
				FILE *fp = fopen("data/flight/9.9航空信息.txt", "a");
				if (fp == NULL) {
					exit(1);
				}

				memset(Flight_new->Ontimerate, '\0', sizeof Flight_new->Ontimerate);
				/*随机准点率*/
				Flight_new->Ontimerate[0] = '9';
				Flight_new->Ontimerate[1] = '9';
				Flight_new->Ontimerate[2] = '.';
				Flight_new->Ontimerate[3] = rand() % 9 - '0';
				Flight_new->Ontimerate[4] = rand() % 9 - '0';
				Flight_new->Ontimerate[4] = '%';
				fprintf(fp, " %s %s %s %s %s %s %d %d %d %d %s %s %s %s\n",
					Flight_new->Flightnum, Flight_new->Flighttime_up,
					Flight_new->Flighttime_down, Flight_new->Startland,
					Flight_new->Downland, Flight_new->Flighttype, Flight_new->Firstfare,
					Flight_new->Economfare, Flight_new->Firstrest, Flight_new->Economrest,
					Flight_new->Pilot_1, Flight_new->Pilot_2, Flight_new->Company,Flight_new->Ontimerate);
				fclose(fp);
				printf("*    发布成功！\n");
				return 1;
				break ;
			}
			/*修改航班*/
			case '2':
			{
				modify_Flight(Flight_new);
				return 0;
				break;
			}
			case '0':
			{
				printf("*    已取消添加\n");
				return 1;
				break;
			}
			default:
			{
				printf("*    错误指令，请重新输入\n");
				break;
			}

		}

	}
}

/*添加航班*/
void add_Flight()
{
	FlightInfo Flight_new, Flight;//分别储存新添加航班信息与历史航班信息
	FILE *Admin_list;//打开当前管理员文件
	Admin_list = fopen("当前管理员.txt", "r");//打开管理员文件
	if (Admin_list == NULL) {
		exit(1);
	}
	Admination Admin;//用于储存当前管理员信息
	fscanf(Admin_list, "%s%s%s%s%s", Admin.ID, Admin.Company, Admin.Name, Admin.mail, Admin.Password);
	fclose(Admin_list);//关闭管理员文件

	strcpy(Flight_new.Company, Admin.Company);//保证同一公司
	Flight_new.Economrest = 150;
	Flight_new.Firstrest = 50;
	int Is_ok = in_Put(&Flight_new);

	
	if (Is_ok) {
		while (1)
		{

			/*查询历史航班信息*/
			FILE *fp = fopen("data/flight/9.9航空信息.txt", "r");
			if (fp == NULL) {
				exit(1);
			}
			int Judge_time = 0, Judge_land = 0;//用于判断飞行员时间和路线是否冲突
			int On_plane_1, On_plane_2;//用于判断飞行员是否参与两个航班

			while (fscanf(fp, "%s%s%s%s%s%s%d%d%d%d%s%s%s%s", Flight.Flightnum, Flight.Flighttime_up,
				Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, &Flight.Firstfare,
				&Flight.Economfare, &Flight.Firstrest, &Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2,
				Flight.Company,Flight.Ontimerate) != EOF)
			{

				//判断飞行员时间和路线是否冲突
				On_plane_1 = strcmp(Flight.Pilot_1, Flight_new.Pilot_1);
				On_plane_1 *= strcmp(Flight.Pilot_2, Flight_new.Pilot_1);
				On_plane_2 = strcmp(Flight.Pilot_1, Flight_new.Pilot_2);
				On_plane_2 *= strcmp(Flight.Pilot_2, Flight_new.Pilot_2);
				/*若有飞行员参与了两个航班*/
				if (On_plane_1 == 0 || On_plane_2 == 0)
				{
					Judge_time = judge_Time(Flight_new, Flight);
					//时间不冲突
					if (Judge_time) {
						Judge_land = judge_Land(Flight_new, Flight);

						//路线不冲突
						if (Judge_land)
						{

							strcpy(Flight_new.Flightnum, build_Flightnum(Flight_new, Flight));

							continue;
						}

						//路线冲突
						else
						{
							/*判断哪位飞行员无法执行此次航班*/
							if (On_plane_1 != 0)
							{
								printf("2号飞行员");
							}
							else if (On_plane_2 != 0)
							{
								printf("1号飞行员");
							}
							else
							{
								printf("两名飞行员均");
							}
							printf("路线冲突，请重新安排飞行员.\n");
							break;
						}
					}
					//时间冲突
					else
					{
						/*判断哪位飞行员无法执行此次航班*/
						if (On_plane_1 != 0)
						{
							printf("2号飞行员");
						}
						else if (On_plane_2 != 0)
						{
							printf("1号飞行员");
						}
						else
						{
							printf("两名飞行员均");
						}
						printf("时间冲突，请重新安排飞行员.\n");
						break;
					}

				}
				/*不冲突*/
				else
				{
					Judge_land = 1;
					Judge_time = 1;
					strcpy(Flight_new.Flightnum, build_Flightnum(Flight_new, Flight));
					//printf("%s\n", Flight_new.Flightnum);
				}
				
			}
			fclose(fp);

			int flag = 1;//判断是否需要重新验证航班信息
			/*如果有飞行员路线或时间冲突*/
			if (Judge_land * Judge_time == 0)
			{
				/*修改飞行员信息，并判断是否需要验证*/
				flag = modify_Polit(On_plane_1, On_plane_2, &Flight_new);
			}
			/*不冲突*/
			else
			{
				/*进行下一步操作并判断是否需要验证*/
				flag = reserve_Flight(&Flight_new);
			}
			if (flag)//不需要验证航班信息
			{
				break;
			}
		}
	}
}
