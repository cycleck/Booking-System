#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "��¼����.h"
#include "���ݽṹ.h"
#include"����Ա�����ѯ�����.h"
#include"��Ʊ.h"
#include"��������.h"

//��ע�ᣨ�ظ�id��������ע�ᣬ���õ�¼
//�����ַ�

void manLogin();
void admPrint();
void Readuser(List_U *);
void Readadm(List_A *);
void muea1(List_F);


void(*chooseIdentity[2])() = { isUser,manLogin };/*��ѡ���¼����ѡ��*/
void(*userLogArray[3])() = { userLogin ,userReg,retFirst };/*�û���¼��ѡ��ѡ��*/
List_F F = { 0 };
List_P P = { 0 };
Admination A = { 0 };
/*�û���¼����*/
void isUser()
{
	
	int reg = 3;
	printf("��ӭ�����û���¼����\n");
	printf("**************************\n");
	printf("*        �û���¼        *\n");
	printf("*                        *\n");
	printf("*       1.��¼�˺�       *\n");
	printf("*       2.ע���˺�       *\n");
	printf("*       3.����           *\n");
	printf("*                        *\n");
	printf("**************************\n\n");
	printf("��ѡ�� ->");
	scanf_s("%d", &reg);
	/*����һ������ָ�����飬����ѡ��ĺ�����ִ��*/
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
			printf("*�������,��������*\n");
			isUser();
			return;
		}
	return;
}

/*�û���¼*/
void userLogin()
{
	User user/*������û���Ϣ*/, b/*ƥ�����һ���û���Ϣ*/;
	FILE *fp,*now;
	int num = 1, choose=1;

	printf("\n*��¼*\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fp = fopen("�û���Ϣ.txt", "r");
	if (!fp)
	{
		printf("�ļ���ʧ��\n");
	}
	else
	{
		printf("ID:");
		scanf_s("%s", &user.ID, 20);
		fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);/*���û���Ϣ���һ���û�����Ϣ��b��*/
		//printf("%s %s %s %s %s %s\n",b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord );
		while (!feof(fp))//���û�ж������
		{
			if (!strcmp(user.ID, b.ID))//����д��û���
				break;
			else
				fscanf(fp, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
		}
		if (!strcmp(user.ID, b.ID))//��ͬid��������¼
		{
			int a = 1;
			while (a == 1)
			{
				printf("����:");
				scanf_s("%s", &user.PassWord, 20);
				if (!strcmp(user.PassWord, b.PassWord))
				{
					printf("*��¼�ɹ�*\n\n");
					a = 2;
					fclose(fp);
					now = fopen("��ǰ�û�.txt", "w");
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
					printf("*�������*\n");
					printf("��ѡ��(1.��������,2.���أ�3.�һ�����)->");
					fclose(fp);
					scanf("%d", &choose);
					if (choose >=1 && choose <=3)
					{
						if (choose == 1)//��������
						{
							choose = 2;
							fclose(fp);
						}
						else if (choose == 2)//����
						{
							a = 2;
							fclose(fp);
							isUser();
							exit(1);//Ҫ��Ҫ��
						}
						else//��������
						{
							printf("\n*�һ�����*\n");
							printf("������ע�����䣺");
							scanf("%s", user.mail);
							printf("������ע��绰���룺");
							scanf("%s", user.Phone);
							if ((strcmp(user.mail, b.mail) == 0) && (strcmp(user.Phone, b.Phone) == 0))
							{
								printf("%s ���ã����������ǣ�%s\n", b.Name, b.PassWord);
								printf("*��������������*\n\n");
							}
							else
							{
								printf("*ƥ�����ݳ�����������*\n");
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
			printf("*δ��⵽id,�����ص�¼����*\n\n");
			fclose(fp);
			isUser();
		}
	}
}

/*�û�ע��*/
void userReg()
{
	User user = { NULL }, b = { NULL };
	int userNum = 1/*�û�����*/, userIDnum = 0/*ID��*/, chID = 0, chid = 0/*ID����ѭ������*/, a=2,r=0,s=0;
	int phoneNum = 0;
	int Enum1 = 0/*1.���ڼ�¼'@'���ֵ�λ�� 2.���ڼ�¼�������䳤��*/, Enum2 = 0/*���ڼ�¼.��λ��*/, text1 = 0/*���ڼ���*/;
	FILE *outFile;
	
	printf("\n��ʼע�᣺\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf("�û�ID��6-10λ��ĸ���֣������������ַ�����");
	/*���벢���ID*/
	while (1)
	{
		userNum = 0;
		scanf_s("%s", &user.ID, 20);/*�����û�ID*/
		/*��֤ID��ȷ*/
		userIDnum = 0, chID = 0, chid = 0;

		while (userIDnum < 6)/*��id��С��6�������*/
		{
			/*��������ȫ����ĸ���֣�˵�����У�chID�����¼id����*/
			if ((user.ID[userIDnum] >= '0'&&user.ID[userIDnum] <= '9') || (user.ID[userIDnum] >= 'a'&&user.ID[userIDnum] <= 'z') || (user.ID[userIDnum] >= 'A'&&user.ID[userIDnum] <= 'z'))
				chID++;
			else/*����������ַ��������У�ֱ������whileѭ��*/
				break;
			userIDnum++;/*Ϊ������whileѭ��������*/
		}
		while (userIDnum >= 6 && userIDnum < 11)/*��id������6С��10�������*/
		{
			/*���������������ַ�����������*/
			if ((user.ID[userIDnum] >= '0'&&user.ID[userIDnum] <= '9') || (user.ID[userIDnum] >= 'a'&&user.ID[userIDnum] <= 'z') || (user.ID[userIDnum] >= 'A'&&user.ID[userIDnum] <= 'z'))
				chID++;
			else/*�������ַ������*/
				if (user.ID[userIDnum] == '\0')/*�����ַ��ǻس���������֤*/
				{
					chID++;
					break;
				}
				else/*�������ַ�,�Ǵ�ı�����һ*/
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
				printf("*����ID*\n");
				outFile = fopen("�û���Ϣ.txt", "r");
				fscanf(outFile, "%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				//printf("print%s %s %s %s %s %s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				//fclose(outFile);
				//break;
				while (!feof(outFile))
				{
					if (strcmp(user.ID, b.ID) == 0)//��⵽��ͬid
					{
						a = 1;
						break;
					}
					else
						fscanf(outFile, "%s%s%s%s%s%s\n", b.ID, b.Name, b.Sex, b.Phone, b.mail, b.PassWord);
				}
				if (a == 1)
				{
					printf("*id�ظ�,������ע��*\n");
					userReg();
					exit(1);
				}
				else
				{
					printf("*id����ɹ�*\n");
					break;
				}
				fclose(outFile);
			}
			else
				printf("*id��ʽ����ȷ������������*\n");
		}
		else
		{
			printf("*ID��ʽ����ȷ������������*\n");
		}
	}

	printf("\n������");
	scanf_s("%s", &user.Name, 20);
	/*r = is_Chinese(user.Name);
	if (r == 1)
	{
		printf("������");
	}
	else 
	{
		printf("��������");
	}*/

	printf("*��������ɹ�*\n\n");
	while (1)
	{
		printf("�Ա�(��ѡ��1.�� 2.Ů 3.������:");
		scanf("%d", &s);
		if (s == 1 || s == 2 || s == 3)
		{
			if (s == 1)
			{
				strcpy(user.Sex, "��");
				//printf("%s", user.Sex);
				break;
			}
			else if (s == 2)
			{
				strcpy(user.Sex, "Ů");
				//printf("%s", user.Sex);
				break;
			}
			else
			{
				strcpy(user.Sex, "����");
				//printf("%s", user.Sex);
				break;
			}

		}
		else
		{
			printf("��ѡ��1.�� 2.Ů 3.����\n");
		}
	}
	printf("*�����Ա�Ϊ��%s��*\n\n",user.Sex);
	//fprintf(outFile, "%-3s",user.Sex);

	printf("�绰��");
	while (1)
	{
		scanf_s("%s", &user.Phone, 20);
		/*��֤�绰����λ����11λ��*/
		phoneNum = 0;
		while (1)
		{
			if (user.Phone[phoneNum] == '\0')/*���˻س�*/
				break;
			else
				if (user.Phone[phoneNum] >= '0'&&user.Phone[phoneNum] <= '9')
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

	printf("���䣺");
	while (1)
	{
		Enum1 = 0, Enum2 = 0, text1 = 0;
		scanf("%s", user.mail);
		//printf("%s", user.mail);
		while (1)
		{
			if (user.mail[Enum1] == '@' && Enum1 != 0)//������'@'
			{
				if (Enum1 != 0)
				{
					Enum1++;
					while (1)
					{
						if (user.mail[Enum1] == '.' && Enum2 != 0)//������'.'��'.'��ֱ����'@'����
						{
							text1++;
							Enum1++;
							while (1)
							{
								if (user.mail[Enum1] == '\0')//��������˻س������˳�����
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
			printf("*��������ɹ�*\n\n");
			break;
		}
		else
			printf("*�����ʽ��������������*\n");
	}

	printf("���룺");
	scanf_s("%s", &user.PassWord, 20);
	printf("*��������ɹ�*\n\n");
	//fprintf(outFile, "%-20s", user.PassWord);
	//printf("%s %s %s %s %s %s", user.ID, user.Name, user.Sex, user.Phone, user.PassWord,user.mail);

	outFile = fopen("�û���Ϣ.txt", "a");
	/*����ļ��Ƿ�ɹ���*/
	if (outFile == NULL)
	{
		printf("�ļ���ʧ��");
		exit(1);
	}
	else
	{
		fprintf(outFile, "%s %s %s %s %s %s\n", user.ID, user.Name, user.Sex, user.Phone, user.mail, user.PassWord);
		fclose(outFile);
	}
	printf("\n\nע��ɹ������¼��\n");
	isUser();
}

/*����Ա��Ϣ�Ǽ�*/
void admPrint()
{
	Admination adm;
	FILE *fp;
	int a = 1;
	fp = fopen("����Ա��Ϣ.txt","w");
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


/*����Ա��¼*/
void manLogin()
{
	Readorder(&P);
	ReadInfo(&F);
	calculate_F(&F);
	Admination a, b = { NULL };
	FILE *fp,*now;
	int num=2;

	printf("\n\n��ӭ�������Ա��¼����\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fp = fopen("����Ա��Ϣ.txt", "r");
	if (!fp)
	{
		printf("�ļ���ʧ��\n");
	}
	else
	{
		printf("ID��");
		scanf("%s", a.ID);
		fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password); 
		//printf("%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
		while (!feof(fp))
		{
			if (!strcmp(a.ID, b.ID))//����д��û���
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
			printf("���룺");
			scanf("%s", a.Password);
			if (!strcmp(a.Password, b.Password))
			{
				fclose(fp);
				now = fopen("��ǰ����Ա.txt", "w");
				fprintf(now, "%s %s %s %s %s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
				fclose(now);
				while (1)
				{
					printf("\n\n\n\n");
					printf("\t��ӭ���뺽�ඩƱϵͳ(����Աģʽ)\n");
					printf("*******************************************\n");
					printf("*                 ���ն�Ʊ����ϵͳ        *\n");
					printf("*      1.          ��ѯ��������Ϣ         *\n");
					printf("*      2.   ��ѯ���չ�˾�ĺ���Ķ�Ʊ���  *\n");
					printf("*      3.          �ѳ�������ͳ��         *\n");
					printf("*      4.     δ�������ఴ��Ʊͳ��        *\n");
					printf("*      5.          ��Ӻ�����Ϣ           *\n");
					printf("*      6.          ������Ϣ����           *\n");
					printf("*      0.         ��  ��  ϵ  ͳ          *\n");
					printf("*******************************************\n");
					printf("��ѡ�� ->");
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
						printf("����ָ��!������ѡ��\n");
						break;
					}
				}
			}
			else
			{
				printf("*�������*\n");
				printf("��ѡ��1.���µ�¼��2.����)->");
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
			printf("*����ԱID������*\n");
			printf("��ѡ��(1.��������,2.�˳�����)->");
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
		printf("\t        ��ѡ������ʽ\n");
		printf("*******************************************\n");
		printf("*      1.          ���ɻ�����������       *\n");
		printf("*      2.        ��������Ʊ����������     *\n");
		printf("*      0.           ��         ��         *\n");
		printf("*******************************************\n");
		int flag;
		printf("����ѡ��\n");
		scanf("%d", &flag);
		switch (flag) {
		case 1:printf("�����������ѯ������(x.x)��\n");
			   getchar();
			   scanf_s("9.%d",&i);
			   ReadInfo_otherday(&F,i);
			   calculate_F(&F);
               Rate_Rank(&F);
			   PrintAirmsg_A(F);
			break;
		case 2:
			printf("�����������ѯ������(x.x)��\n");
			getchar();
			scanf("9.%d",&i);
			ReadInfo_otherday(&F, i);
			calculate_F(&F);
			Income_Rank(&F); 
			PrintAirmsg_A(F);
			break;
		case 0:return;
		default:
			printf("�Ƿ�����");

		}

	}
	return;
}

/*��һ������*/
void retFirst()
{
	int logCate = 0;
	printf("\n��ӭ���뺽����Ʊϵͳ\n");
	printf("**************************\n");
	printf("*      ����ѡ���¼      *\n");
	printf("*                        *\n");
	printf("*      1.�û���¼        *\n");
	printf("*      2.����Ա��¼      *\n");
	printf("*      3.�˳�����        *\n");
	printf("*                        *\n");
	printf("**************************\n\n");
	printf("��ѡ�� ->");
	/*ѡ���¼*/
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
			printf("*�������,�˳�����*\n");
			exit(1);
		}
	//��һ���˳�
}

/*������Ϣ����*/
void changeUser()
{
	User user, b;
	FILE *fp, *outFile, *reWrite;
	List_U U = { 0 };
	int num = 4, i = 0, cho = 3, count = 0;

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
		printf("\n%s,���ã���ӭ���������Ϣ�������\n", b.Name);
		printf("\n���������룺");
		while (1)
		{
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
				break;
			}
			else
			{
				printf("�����������������\n");
				fclose(fp);
			}
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
			fscanf(fp, "%s %s %s %s %s %s", U->u[i].ID, U->u[i].Name, U->u[i].Sex, U->u[i].Phone, U->u[i].mail, U->u[i].PassWord);
		}
	}
}

/*����Ա��Ϣ����*/
void changeAdm()
{
	Admination adm, b;
	FILE *fp, *outFile, *reWrite;
	List_A A = { 0 };
	int num = 4, i = 0, cho = 3, count = 0;

	//printf("\n��ӭ�����û�������Ϣ�������\n");
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	outFile = fopen("��ǰ����Ա.txt", "r");
	if (!outFile)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	else
	{
		fscanf(outFile, "%s%s%s%s%s\n", adm.ID, adm.Company, adm.Name, adm.mail, adm.Password);
		fclose(outFile);
	}

	fp = fopen("����Ա��Ϣ.txt", "r");

	fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);
	while (!feof(fp))//���û�ж������
	{
		if (!strcmp(adm.ID, b.ID))//����д��û���
			break;
		else
		{
			fscanf(fp, "%s%s%s%s%s\n", b.ID, b.Company, b.Name, b.mail, b.Password);//������
			i++;
		}
	}
	if (!strcmp(adm.ID, b.ID))
	{
		printf("\n%s ����Ա,���ã���ӭ���������Ϣ�������\n", b.Name);
		printf("\n���������룺");
		scanf("%s", b.Password);
		if (!strcmp(b.Password, adm.Password))//������ȷ
		{
			Readadm(&A);
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
					scanf("%s", A.a[i].mail);
					while (1)
					{
						if (A.a[i].mail[Enum1] == '@')//������'@'
						{
							if (Enum1 != 0)//��@�����ڵ�һλ
							{
								Enum1++;
								while (1)
								{
									if (A.a[i].mail[Enum1] == '.' && Enum2 != 0)//������'.'��'.'��ֱ����'@'����
									{
										text1++;
										Enum1++;
										while (1)
										{
											if (A.a[i].mail[Enum1] == '\0')//��������˻س������˳�����
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
							else//��@���ڵ�һλ
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

			printf("����: %s\n��1.�޸�,2.���޸ģ���ѡ��->", b.Password);
			scanf("%d", &cho);
			if (cho == 1)
			{
				printf("�����������룺");
				scanf("%s", A.a[i].Password);
			}
			else if (cho != 2)
			{
				return;
			}
			fclose(fp);
			outFile = fopen("��ǰ����Ա.txt", "w");
			fprintf(outFile, "%s %s %s %s %s\n", A.a[i].ID, A.a[i].Company, A.a[i].Name, A.a[i].mail, A.a[i].Password);
			fclose(outFile);

			reWrite = fopen("����Ա��Ϣ.txt", "w");
			for (count = 0; count <= A.count; count++)
			{
				fprintf(reWrite, "%s %s %s %s %s\n", A.a[count].ID, A.a[count].Company, A.a[count].Name, A.a[count].mail, A.a[count].Password);
			}
			fclose(fp);
		}
		else
		{
			printf("�������\n");
			fclose(fp);
			manLogin();
			exit(1);
		}
	}
	else
	{
		printf("δ�ҵ���ID\n");
		fclose(fp);
	}
}

void Readadm(List_A *A)
{
	FILE *fp;
	if ((fp = fopen("����Ա��Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		A->count = 0;//��ʼ������(������)
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n��
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