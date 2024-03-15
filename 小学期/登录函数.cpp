#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "登录函数.h"
#include "数据结构.h"
#include"管理员航班查询及添加.h"
#include"购票.h"
#include"订单管理.h"

//先注册（重复id），正常注册，再用登录
//特殊字符

void manLogin();
void admPrint();
void Readuser(List_U *);
void Readadm(List_A *);
void muea1(List_F);


void(*chooseIdentity[2])() = { isUser,manLogin };/*“选择登录”的选项*/
void(*userLogArray[3])() = { userLogin ,userReg,retFirst };/*用户登录的选择选项*/
List_F F = { 0 };
List_P P = { 0 };
Admination A = { 0 };
/*用户登录界面*/
void isUser()
{
	
	int reg = 3;
	printf("欢迎进入用户登录界面\n");
	printf("**************************\n");
	printf("*        用户登录        *\n");
	printf("*                        *\n");
	printf("*       1.登录账号       *\n");
	printf("*       2.注册账号       *\n");
	printf("*       3.返回           *\n");
	printf("*                        *\n");
	printf("**************************\n\n");
	printf("请选择 ->");
	scanf_s("%d", &reg);
	/*这是一个函数指针数组，跳到选择的函数里执行*/
	if (reg == 1 || reg == 2)
	{
		userLogArray[reg - 1]();
	}
	else
		if (reg == 3)
		{
			retFirst();
		}
		else
		{
			printf("*输入错误,即将返回*\n");
			isUser();
			return;
		}
	return;
}

/*用户登录*/
void userLogin()
{
	User user/*输入的用户信息*/, b/*匹配出的一行用户信息*/;
	FILE *fp,*now;
	int num = 1, choose=1;

	printf("\n*登录*\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fp = fopen("用户信息.txt", "r");
	if (!fp)
	{
		printf("文件打开失败\n");
	}
	else
	{
		printf("ID:");
		scanf_s("%s", &user.ID, 20);
		fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);/*从用户信息里读一个用户的信息到b中*/
		//printf("%s %s %s %s %s %s\n",b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord );
		while (!feof(fp))//如果没有读到最后
		{
			if (!strcmp(user.ID, b.ID))//如果有此用户名
				break;
			else
				fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
		}
		if (!strcmp(user.ID, b.ID))//相同id，继续登录
		{
			int a = 1;
			while (a == 1)
			{
				printf("密码:");
				scanf_s("%s", &user.PassWord, 20);
				if (!strcmp(user.PassWord, b.PassWord))
				{
					printf("*登录成功*\n\n");
					a = 2;
					fclose(fp);
					now = fopen("当前用户.txt", "w");
					fprintf(now, "%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
					fclose(now);
					//return;
					ReadInfo(&F);
					calculate_F(&F);
					Recommend(&F);
					ui();
				}
				else
				{
					printf("*密码错误*\n");
					printf("请选择(1.重新输入,2.返回，3.找回密码)->");
					fclose(fp);
					scanf("%d", &choose);
					if (choose >=1 && choose <=3)
					{
						if (choose == 1)//重新输入
						{
							choose = 2;
							fclose(fp);
						}
						else if (choose == 2)//返回
						{
							a = 2;
							fclose(fp);
							isUser();
							exit(1);//要不要？
						}
						else//返回密码
						{
							printf("\n*找回密码*\n");
							printf("请输入注册邮箱：");
							scanf("%s", user.mail);
							printf("请输入注册电话号码：");
							scanf("%s", user.Phone);
							if ((strcmp(user.mail, b.mail) == 0) && (strcmp(user.Phone, b.Phone) == 0))
							{
								printf("%s 您好，您的密码是：%s\n", b.Name, b.PassWord);
								printf("*请重新输入密码*\n\n");
							}
							else
							{
								printf("*匹配内容出错，即将返回*\n");
								a = 2;
								isUser();
								return;
								exit(1);
							}
						}
					}
					else
					{
						a = 2;
						fclose(fp);
						isUser();
					}
				}
			}
				//return;
		}
		else
		{
			printf("*未检测到id,将返回登录界面*\n\n");
			fclose(fp);
			isUser();
		}
	}
}

/*用户注册*/
void userReg()
{
	User user = { NULL }, b = { NULL };
	int userNum = 1/*用户个数*/, userIDnum = 0/*ID数*/, chID = 0, chid = 0/*ID部分循环变量*/, a=2,r=0,s=0;
	int phoneNum = 0;
	int Enum1 = 0/*1.用于记录'@'出现的位数 2.用于记录整个邮箱长度*/, Enum2 = 0/*用于记录.的位置*/, text1 = 0/*用于计数*/;
	FILE *outFile;
	
	printf("\n开始注册：\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf("用户ID（6-10位字母数字，不包含特殊字符）：");
	/*输入并检测ID*/
	while (1)
	{
		userNum = 0;
		scanf_s("%s", &user.ID, 20);/*输入用户ID*/
		/*验证ID正确*/
		userIDnum = 0, chID = 0, chid = 0;

		while (userIDnum < 6)/*在id数小于6的情况中*/
		{
			/*如果输入的全是字母数字，说明可行，chID负责记录id个数*/
			if ((user.ID[userIDnum] >= '0'&&user.ID[userIDnum] <= '9') || (user.ID[userIDnum] >= 'a'&&user.ID[userIDnum] <= 'z') || (user.ID[userIDnum] >= 'A'&&user.ID[userIDnum] <= 'z'))
				chID++;
			else/*如果有特殊字符，不可行，直接跳出while循环*/
				break;
			userIDnum++;/*为了满足while循环的条件*/
		}
		while (userIDnum >= 6 && userIDnum < 11)/*在id数大于6小于10的情况中*/
		{
			/*如果输入的无特殊字符，继续计数*/
			if ((user.ID[userIDnum] >= '0'&&user.ID[userIDnum] <= '9') || (user.ID[userIDnum] >= 'a'&&user.ID[userIDnum] <= 'z') || (user.ID[userIDnum] >= 'A'&&user.ID[userIDnum] <= 'z'))
				chID++;
			else/*有特殊字符的情况*/
				if (user.ID[userIDnum] == '\0')/*特殊字符是回车，结束验证*/
				{
					chID++;
					break;
				}
				else/*有特殊字符,记错的变量加一*/
				{
					chid++;
					break;
				}
			userIDnum++;
		}
		if (userIDnum >= 6 && userIDnum < 11)
		{
			if (chID >= 6 && chID <= 11 && chid == 0)
			{
				printf("*检验ID*\n");
				outFile = fopen("用户信息.txt", "r");
				fscanf(outFile, "%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				//printf("print%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				//fclose(outFile);
				//break;
				while (!feof(outFile))
				{
					if (strcmp(user.ID, b.ID) == 0)//检测到相同id
					{
						a = 1;
						break;
					}
					else
						fscanf(outFile, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				}
				if (a == 1)
				{
					printf("*id重复,请重新注册*\n");
					userReg();
					exit(1);
				}
				else
				{
					printf("*id输入成功*\n");
					break;
				}
				fclose(outFile);
			}
			else
				printf("*id格式不正确，请重新输入*\n");
		}
		else
		{
			printf("*ID格式不正确，请重新输入*\n");
		}
	}

	printf("\n姓名：");
	scanf_s("%s", &user.Name, 20);
	/*r = is_Chinese(user.Name);
	if (r == 1)
	{
		printf("是中文");
	}
	else 
	{
		printf("不是中文");
	}*/

	printf("*姓名输入成功*\n\n");
	while (1)
	{
		printf("性别(请选择1.男 2.女 3.其他）:");
		scanf("%d", &s);
		if (s == 1 || s == 2 || s == 3)
		{
			if (s == 1)
			{
				strcpy(user.Sex, "男");
				//printf("%s", user.Sex);
				break;
			}
			else if (s == 2)
			{
				strcpy(user.Sex, "女");
				//printf("%s", user.Sex);
				break;
			}
			else
			{
				strcpy(user.Sex, "其他");
				//printf("%s", user.Sex);
				break;
			}

		}
		else
		{
			printf("请选择1.男 2.女 3.其他\n");
		}
	}
	printf("*您的性别为“%s”*\n\n",user.Sex);
	//fprintf(outFile, "%-3s",user.Sex);

	printf("电话：");
	while (1)
	{
		scanf_s("%s", &user.Phone, 20);
		/*验证电话号码位数（11位）*/
		phoneNum = 0;
		while (1)
		{
			if (user.Phone[phoneNum] == '\0')/*按了回车*/
				break;
			else
				if (user.Phone[phoneNum] >= '0'&&user.Phone[phoneNum] <= '9')
					phoneNum++;/*电话号码必须是数字*/
				else
					break;
		}
		if (phoneNum == 11)
		{
			printf("*电话号码输入成功*\n\n");
			break;
		}
		else
			printf("*电话号码错误，请重新输入*\n");
	}

	printf("邮箱：");
	while (1)
	{
		Enum1 = 0, Enum2 = 0, text1 = 0;
		scanf("%s", user.mail);
		//printf("%s", user.mail);
		while (1)
		{
			if (user.mail[Enum1] == '@' && Enum1 != 0)//出现了'@'
			{
				if (Enum1 != 0)
				{
					Enum1++;
					while (1)
					{
						if (user.mail[Enum1] == '.' && Enum2 != 0)//出现了'.'且'.'不直接在'@'后面
						{
							text1++;
							Enum1++;
							while (1)
							{
								if (user.mail[Enum1] == '\0')//如果出现了回车键，退出程序
									break;
								else
								{
									text1++;
									Enum1++;
								}
							}
							break;
						}
						else
							if (user.mail[Enum1] == '.' && Enum2 == 0)
								break;
							else
							{
								if (user.mail[Enum1] == '\0')
									break;
								else
								{
									Enum2++;
									Enum1++;
								}
							}
					}
					break;
				}
				else
				{
					break;
				}
			}
			else
				if (user.mail[Enum1] == '\0')
				{
					break;
				}
				else
				{
					Enum1++;
				}
		}
		if (text1 > 1)
		{
			printf("*邮箱输入成功*\n\n");
			break;
		}
		else
			printf("*邮箱格式错误，请重新输入*\n");
	}

	printf("密码：");
	scanf_s("%s", &user.PassWord, 20);
	printf("*密码输入成功*\n\n");
	//fprintf(outFile, "%-20s", user.PassWord);
	//printf("%s %s %s %s %s %s", user.ID, user.Name, user.Sex, user.Phone, user.PassWord,user.mail);

	outFile = fopen("用户信息.txt", "a");
	/*检查文件是否成功打开*/
	if (outFile == NULL)
	{
		printf("文件打开失败");
		exit(1);
	}
	else
	{
		fprintf(outFile, "%s %s %s %s %s %s\n", user.ID, user.Name, user.Sex, user.Phone, user.mail, user.PassWord);
		fclose(outFile);
	}
	printf("\n\n注册成功，请登录：\n");
	isUser();
}

/*管理员信息登记*/
void admPrint()
{
	Admination adm;
	FILE *fp;
	int a = 1;
	fp = fopen("管理员信息.txt","w");
	while (a == 1)
	{
		scanf("%s %s %s %s %s", adm.ID, adm.Company, adm.Name, adm.mail, adm.Password);
		fprintf(fp, "%s %s %s %s %s\n", adm.ID, adm.Company, adm.Name, adm.mail, adm.Password);
		//printf("%s %s %s %s %s\n", adm.ID, adm.Company, adm.Name, adm.mail, adm.Password);
		scanf("%d", &a);
	}
	fclose(fp);
	exit(1);
}


/*管理员登录*/
void manLogin()
{
	Readorder(&P);
	ReadInfo(&F);
	calculate_F(&F);
	Admination a, b = { NULL };
	FILE *fp,*now;
	int num=2;

	printf("\n\n欢迎进入管理员登录界面\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fp = fopen("管理员信息.txt", "r");
	if (!fp)
	{
		printf("文件打开失败\n");
	}
	else
	{
		printf("ID：");
		scanf("%s", a.ID);
		fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password); 
		//printf("%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
		while (!feof(fp))
		{
			if (!strcmp(a.ID, b.ID))//如果有此用户名
			{
				//printf("%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
				break;
			}
			else
			{
				fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
				//printf("%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
			}
		}
		
		if (!strcmp(a.ID, b.ID))
		{
			printf("密码：");
			scanf("%s", a.Password);
			if (!strcmp(a.Password, b.Password))
			{
				fclose(fp);
				now = fopen("当前管理员.txt", "w");
				fprintf(now, "%s %s %s %s %s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
				fclose(now);
				while (1)
				{
					printf("\n\n\n\n");
					printf("\t欢迎进入航班订票系统(管理员模式)\n");
					printf("*******************************************\n");
					printf("*                 航空订票客运系统        *\n");
					printf("*      1.          查询各航线信息         *\n");
					printf("*      2.   查询航空公司的航班的订票情况  *\n");
					printf("*      3.          已出发航班统计         *\n");
					printf("*      4.     未出发航班按售票统计        *\n");
					printf("*      5.          添加航班信息           *\n");
					printf("*      6.          个人信息管理           *\n");
					printf("*      0.         退  出  系  统          *\n");
					printf("*******************************************\n");
					printf("请选择 ->");
					int c;
					scanf("%d", &c);
					switch (c)
					{
					case 1: {
						ReadInfo(&F);   
						 PrintAirmsg_U(F);  
						break;
					}
					case 2: {
						Readorder(&P);
						/*printf("%d\n", P.count);*/
					/*	Printorder(P);*/
						ReadAdmination(&A);
						Showorder(F, P, A);
						break;
					}
					case 3: {
						muea1(F);
						break;
					}
					case 4: {
						Readorder(&P);
						ReadAdmination(&A);
						
						calculate_F(&F);
						Book_Rank(&F, A);
					
						break;
					}
					case 5: {
						add_Flight();
						break;
					}
					case 6: {
						changeAdm();
						break;
					}
					case 0: {
						retFirst();
						break;
					}




					default:
						printf("错误指令!请重新选择\n");
						break;
					}
				}
			}
			else
			{
				printf("*密码错误*\n");
				printf("请选择（1.重新登录，2.返回)->");
				scanf("%d", &num);
				if (num == 1)
				{
					fclose(fp);
					manLogin();	
				}
				else
				{
					fclose(fp);
					retFirst();
				}
			}
		}
		else
		{
			printf("*管理员ID不存在*\n");
			printf("请选择(1.重新输入,2.退出程序)->");
			scanf("%d", &num);
			if (num == 1)
			{
				fclose(fp);
				manLogin();
			}
			else
			{
				fclose(fp);
				exit(1);
			}
		}
	}
}
void muea1(List_F F)
{
	int i=0;
	
	while (1)
	{
		printf("\n\n\n\n");
		printf("\t        请选择排序方式\n");
		printf("*******************************************\n");
		printf("*      1.          按飞机上座率排序       *\n");
		printf("*      2.        按航班总票价收入排序     *\n");
		printf("*      0.           返         回         *\n");
		printf("*******************************************\n");
		int flag;
		printf("请您选择：\n");
		scanf("%d", &flag);
		switch (flag) {
		case 1:printf("请输入您想查询的日期(x.x)：\n");
			   getchar();
			   scanf_s("9.%d",&i);
			   ReadInfo_otherday(&F,i);
			   calculate_F(&F);
               Rate_Rank(&F);
			   PrintAirmsg_A(F);
			break;
		case 2:
			printf("请输入您想查询的日期(x.x)：\n");
			getchar();
			scanf("9.%d",&i);
			ReadInfo_otherday(&F, i);
			calculate_F(&F);
			Income_Rank(&F); 
			PrintAirmsg_A(F);
			break;
		case 0:return;
		default:
			printf("非法请求！");

		}

	}
	return;
}

/*第一个界面*/
void retFirst()
{
	int logCate = 0;
	printf("\n欢迎进入航空售票系统\n");
	printf("**************************\n");
	printf("*      请您选择登录      *\n");
	printf("*                        *\n");
	printf("*      1.用户登录        *\n");
	printf("*      2.管理员登录      *\n");
	printf("*      3.退出程序        *\n");
	printf("*                        *\n");
	printf("**************************\n\n");
	printf("请选择 ->");
	/*选择登录*/
	scanf("%d", &logCate);
	if (logCate==1 || logCate==2)
	{
		chooseIdentity[logCate - 1]();
	}
	else
		if(logCate == 3)
		{
			exit(1);
		}
		else 
		{
			printf("*输入错误,退出程序*\n");
			exit(1);
		}
	//加一个退出
}

/*个人信息管理*/
void changeUser()
{
	User user, b;
	FILE *fp, *outFile, *reWrite;
	List_U U = { 0 };
	int num = 4, i = 0, cho = 3, count = 0;

	//printf("\n欢迎进入用户个人信息管理界面\n");
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	outFile = fopen("当前用户.txt", "r");
	if (!outFile)
	{
		printf("文件打开失败\n");
		exit(1);
	}
	else
	{
		fscanf(outFile, "%s%s%s%s%s%s\n", user.ID, user.Name, user.Sex, user.Phone, user.mail, user.PassWord);
		fclose(outFile);
	}

	fp = fopen("用户信息.txt", "r");

	fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
	//printf("%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
	while (!feof(fp))//如果没有读到最后
	{
		if (!strcmp(user.ID, b.ID))//如果有此用户名
			break;
		else
		{
			fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);//继续读
			i++;
		}
	}
	if (!strcmp(user.ID, b.ID))
	{
		printf("\n%s,您好！欢迎进入个人信息管理界面\n", b.Name);
		printf("\n请输入密码：");
		while (1)
		{
			scanf("%s", b.PassWord);
			if (!strcmp(b.PassWord, user.PassWord))//密码正确
			{
				Readuser(&U);
				printf("修改信息：\n");
				printf("邮箱: %s\n（1.修改,2.不修改）请选择->", b.mail);
				scanf("%d", &cho);
				if (cho == 1)
				{
					printf("请输入新邮箱：");
					//检验邮箱格式
					while (1)
					{
						int Enum1 = 0, Enum2 = 0, text1 = 0;
						scanf("%s", U.u[i].mail);
						while (1)
						{
							if (U.u[i].mail[Enum1] == '@')//出现了'@'
							{
								if (Enum1 != 0)//‘@’不在第一位
								{
									Enum1++;
									while (1)
									{
										if (U.u[i].mail[Enum1] == '.' && Enum2 != 0)//出现了'.'且'.'不直接在'@'后面
										{
											text1++;
											Enum1++;
											while (1)
											{
												if (U.u[i].mail[Enum1] == '\0')//如果出现了回车键，退出程序
													break;
												else
												{
													text1++;
													Enum1++;
												}
											}
											break;
										}
										else
											if (U.u[i].mail[Enum1] == '.' && Enum2 == 0)
												break;
											else
											{
												if (U.u[i].mail[Enum1] == '\0')
													break;
												else
												{
													Enum2++;
													Enum1++;
												}
											}
									}
									break;
								}
								else//‘@’在第一位
								{
									break;
								}
							}
							else if (U.u[i].mail[Enum1] == '\0')
							{
								break;
							}
							else
							{
								Enum1++;
							}
						}
						if (text1 > 1)
						{
							printf("*邮箱输入成功*\n\n");
							break;
						}
						else
							printf("*邮箱格式错误，请重新输入*\n");
					}
				}
				else if (cho != 2)
				{
					return;
				}
				printf("电话: %s\n（1.修改,2.不修改）请选择->", b.Phone);
				scanf("%d", &cho);
				if (cho == 1)
				{
					printf("请输入新电话号码：");
					while (1)
					{
						scanf("%s", U.u[i].Phone);
						/*验证电话号码位数（11位）*/
						int phoneNum = 0;
						while (1)
						{
							if (U.u[i].Phone[phoneNum] == '\0')/*按了回车*/
								break;
							else
								if (U.u[i].Phone[phoneNum] >= '0'&&U.u[i].Phone[phoneNum] <= '9')
									phoneNum++;/*电话号码必须是数字*/
								else
									break;
						}
						if (phoneNum == 11)
						{
							printf("*电话号码输入成功*\n\n");
							break;
						}
						else
							printf("*电话号码错误，请重新输入*\n");
					}
				}
				else if (cho != 2)
				{
					return;
				}
				printf("密码: %s\n（1.修改,2.不修改）请选择->", b.PassWord);
				scanf("%d", &cho);
				if (cho == 1)
				{
					printf("请输入新密码：");
					scanf("%s", U.u[i].PassWord);
				}
				else if (cho != 2)
				{
					return;
				}
				fclose(fp);
				outFile = fopen("当前用户.txt", "w");
				fprintf(outFile, "%s %s %s %s %s %s\n", U.u[i].ID, U.u[i].Name, U.u[i].Sex, U.u[i].Phone, U.u[i].mail, U.u[i].PassWord);
				fclose(outFile);

				reWrite = fopen("用户信息.txt", "w");
				for (count = 0; count <= U.count; count++)
				{
					fprintf(reWrite, "%s %s %s %s %s %s\n", U.u[count].ID, U.u[count].Name, U.u[count].Sex, U.u[count].Phone, U.u[count].mail, U.u[count].PassWord);
				}
				fclose(fp);
				break;
			}
			else
			{
				printf("密码错误，请重新输入\n");
				fclose(fp);
			}
		}
	}
	else
	{
		printf("未找到此ID\n");
		fclose(fp);
	}
}

void Readuser(List_U *U)
{
	FILE *fp;
	if ((fp = fopen("用户信息.txt", "r")) == NULL)
	{
		printf("订单文件不存在 \n");
		exit(1);
	}
	else
	{
		U->count = 0;//初始化行数(订单数)
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行
				U->count++;
		}
		rewind(fp);
		for (int i = 0; i < U->count; i++)
		{
			fscanf(fp, "%s %s %s %s %s %s", U->u[i].ID, U->u[i].Name, U->u[i].Sex, U->u[i].Phone, U->u[i].mail, U->u[i].PassWord);
		}
	}
}

/*管理员信息管理*/
void changeAdm()
{
	Admination adm, b;
	FILE *fp, *outFile, *reWrite;
	List_A A = { 0 };
	int num = 4, i = 0, cho = 3, count = 0;

	//printf("\n欢迎进入用户个人信息管理界面\n");
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	outFile = fopen("当前管理员.txt", "r");
	if (!outFile)
	{
		printf("文件打开失败\n");
		exit(1);
	}
	else
	{
		fscanf(outFile, "%s%s%s%s%s\n", adm.ID, adm.Company, adm.Name, adm.mail, adm.Password);
		fclose(outFile);
	}

	fp = fopen("管理员信息.txt", "r");

	fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
	while (!feof(fp))//如果没有读到最后
	{
		if (!strcmp(adm.ID, b.ID))//如果有此用户名
			break;
		else
		{
			fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);//继续读
			i++;
		}
	}
	if (!strcmp(adm.ID, b.ID))
	{
		printf("\n%s 管理员,您好！欢迎进入个人信息管理界面\n", b.Name);
		printf("\n请输入密码：");
		scanf("%s", b.Password);
		if (!strcmp(b.Password, adm.Password))//密码正确
		{
			Readadm(&A);
			printf("修改信息：\n");
			printf("邮箱: %s\n（1.修改,2.不修改）请选择->", b.mail);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("请输入新邮箱：");
				//检验邮箱格式
				while (1)
				{
					int Enum1 = 0, Enum2 = 0, text1 = 0;
					scanf("%s", A.a[i].mail);
					while (1)
					{
						if (A.a[i].mail[Enum1] == '@')//出现了'@'
						{
							if (Enum1 != 0)//‘@’不在第一位
							{
								Enum1++;
								while (1)
								{
									if (A.a[i].mail[Enum1] == '.' && Enum2 != 0)//出现了'.'且'.'不直接在'@'后面
									{
										text1++;
										Enum1++;
										while (1)
										{
											if (A.a[i].mail[Enum1] == '\0')//如果出现了回车键，退出程序
												break;
											else
											{
												text1++;
												Enum1++;
											}
										}
										break;
									}
									else
										if (A.a[i].mail[Enum1] == '.' && Enum2 == 0)
											break;
										else
										{
											if (A.a[i].mail[Enum1] == '\0')
												break;
											else
											{
												Enum2++;
												Enum1++;
											}
										}
								}
								break;
							}
							else//‘@’在第一位
							{
								break;
							}
						}
						else if (A.a[i].mail[Enum1] == '\0')
						{
							break;
						}
						else
						{
							Enum1++;
						}
					}
					if (text1 > 1)
					{
						printf("*邮箱输入成功*\n\n");
						break;
					}
					else
						printf("*邮箱格式错误，请重新输入*\n");
				}
			}
			else if (cho != 2)
			{
				return;
			}

			printf("密码: %s\n（1.修改,2.不修改）请选择->", b.Password);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("请输入新密码：");
				scanf("%s", A.a[i].Password);
			}
			else if (cho != 2)
			{
				return;
			}
			fclose(fp);
			outFile = fopen("当前管理员.txt", "w");
			fprintf(outFile, "%s %s %s %s %s\n", A.a[i].ID, A.a[i].Company, A.a[i].Name, A.a[i].mail, A.a[i].Password);
			fclose(outFile);

			reWrite = fopen("管理员信息.txt", "w");
			for (count = 0; count <= A.count; count++)
			{
				fprintf(reWrite, "%s %s %s %s %s\n", A.a[count].ID, A.a[count].Company, A.a[count].Name, A.a[count].mail, A.a[count].Password);
			}
			fclose(fp);
		}
		else
		{
			printf("密码错误\n");
			fclose(fp);
			manLogin();
			exit(1);
		}
	}
	else
	{
		printf("未找到此ID\n");
		fclose(fp);
	}
}

void Readadm(List_A *A)
{
	FILE *fp;
	if ((fp = fopen("管理员信息.txt", "r")) == NULL)
	{
		printf("订单文件不存在 \n");
		exit(1);
	}
	else
	{
		A->count = 0;//初始化行数(订单数)
		while (!feof(fp))//feof:光标位于文本结尾为1 非结尾为0
		{
			if (fgetc(fp) == '\n')   //n行
				A->count++;
		}
		rewind(fp);
		for (int i = 0; i < A->count; i++)
		{
			char ID[20] = {0};
			fscanf(fp, "%s %s %s %s %s", A->a[i].ID, A->a[i].Company, A->a[i].Name, A->a[i].mail, A->a[i].Password);
		}
	}
}