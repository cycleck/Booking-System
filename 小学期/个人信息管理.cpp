#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "���ݽṹ.h"

void Readuser(List_U *);
void changeUser();
int main()
{
	changeUser();
	return 0;
}

//�û���Ϣ����
void changeUser()
{
	User user, b;
	FILE *fp, *outFile,*reWrite;
	List_U U = { 0 };
	int num = 4, i = 0,cho=3,count=0;

	//printf("\n��ӭ�����û�������Ϣ�������\n");
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	outFile = fopen("��ǰ�û�.txt", "r");
	if (!outFile)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	else
	{
		fscanf(outFile, "%s%s%s%s%s%s\n", user.ID, user.Name, user.Sex, user.Phone, user.mail, user.PassWord);
		fclose(outFile);
	}
	
	fp = fopen("�û���Ϣ.txt", "r");

	fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
	//printf("%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
	while (!feof(fp))//���û�ж������
	{
		if (!strcmp(user.ID, b.ID))//����д��û���
			break;
		else
		{
			fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);//������
			i++;
		}
	}
	if (!strcmp(user.ID, b.ID))
	{
		printf("\n%s,���ã���ӭ���������Ϣ�������\n",b.Name);
		printf("\n���������룺");
		scanf("%s", b.PassWord);
		if (!strcmp(b.PassWord, user.PassWord))//������ȷ
		{
			Readuser(&U);
			printf("�޸���Ϣ��\n");
			printf("����: %s\n��1.�޸�,2.���޸ģ���ѡ��->", b.mail);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("�����������䣺");
				//���������ʽ
				while (1)
				{
					int Enum1 = 0, Enum2 = 0, text1 = 0;
					scanf("%s", U.u[i].mail);
					while (1)
					{
						if (U.u[i].mail[Enum1] == '@')//������'@'
						{
							if (Enum1 != 0)//��@�����ڵ�һλ
							{
								Enum1++;
								while (1)
								{
									if (U.u[i].mail[Enum1] == '.' && Enum2 != 0)//������'.'��'.'��ֱ����'@'����
									{
										text1++;
										Enum1++;
										while (1)
										{
											if (U.u[i].mail[Enum1] == '\0')//��������˻س������˳�����
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
							else//��@���ڵ�һλ
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
						printf("*��������ɹ�*\n\n");
						break;
					}
					else
						printf("*�����ʽ��������������*\n");
				}
			}
			else if (cho != 2)
			{
				return;
			}
			printf("�绰: %s\n��1.�޸�,2.���޸ģ���ѡ��->", b.Phone);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("�������µ绰���룺");
				while (1)
				{
					scanf("%s", U.u[i].Phone);
					/*��֤�绰����λ����11λ��*/
					int phoneNum = 0;
					while (1)
					{
						if (U.u[i].Phone[phoneNum] == '\0')/*���˻س�*/
							break;
						else
							if (U.u[i].Phone[phoneNum] >= '0'&&U.u[i].Phone[phoneNum] <= '9')
								phoneNum++;/*�绰�������������*/
							else
								break;
					}
					if (phoneNum == 11)
					{
						printf("*�绰��������ɹ�*\n\n");
						break;
					}
					else
						printf("*�绰�����������������*\n");
				}
			}
			else if (cho != 2)
			{
				return;
			}
			printf("����: %s\n��1.�޸�,2.���޸ģ���ѡ��->", b.PassWord);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("�����������룺");
				scanf("%s", U.u[i].PassWord);
			}
			else if (cho != 2)
			{
				return;
			}
			fclose(fp);
			outFile = fopen("��ǰ�û�.txt", "w");
			fprintf(outFile, "%s %s %s %s %s %s\n", U.u[i].ID, U.u[i].Name, U.u[i].Sex, U.u[i].Phone, U.u[i].mail, U.u[i].PassWord);
			fclose(outFile);
		
			reWrite = fopen("�û���Ϣ.txt", "w");
			for (count = 0; count <= U.count; count++)
			{
				fprintf(reWrite, "%s %s %s %s %s %s\n", U.u[count].ID, U.u[count].Name, U.u[count].Sex, U.u[count].Phone, U.u[count].mail, U.u[count].PassWord);
			}
			fclose(fp);
		}
		else
		{
			printf("�������\n");
			fclose(fp);
			exit(1);
		}
	}
	else
	{
		printf("δ�ҵ���ID\n");
		fclose(fp);
	}
}

void Readuser(List_U *U)
{
	FILE *fp;
	if ((fp = fopen("�û���Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		U->count = 0;//��ʼ������(������)
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n��
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