#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "数据结构.h"

void Readuser(List_U *);
void changeUser();
int main()
{
	changeUser();
	return 0;
}

//用户信息管理
void changeUser()
{
	User user, b;
	FILE *fp, *outFile,*reWrite;
	List_U U = { 0 };
	int num = 4, i = 0,cho=3,count=0;

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
		printf("\n%s,您好！欢迎进入个人信息管理界面\n",b.Name);
		printf("\n请输入密码：");
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
		}
		else
		{
			printf("密码错误\n");
			fclose(fp);
			exit(1);
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
			char ID[20];
			fscanf(fp, "%s %s %s %s %s %s", U->u[i].ID, U->u[i].Name, U->u[i].Sex, U->u[i].Phone, U->u[i].mail, U->u[i].PassWord);
		}
	}
}