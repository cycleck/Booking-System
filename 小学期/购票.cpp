#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"GetTime.h"
#include <graphics.h>		//����ͼ�ο��ļ�
#include <conio.h>
#include<time.h>
#include"���ݽṹ.h"
#include"��������.h"
#include"��¼����.h"
#include"�����ѯ.h"
#include"��Ʊ.h"
char* buy(char*,char*,int);
//�޸����� 2021.9.6.18��45




void ui()//���溯��
{
	User Usenow = { 0 };
	int ichioce;//�û���ѡ�� ������ת�˵�

	//ȷ�ϵ�ǰ�û�
	FILE *fusenow;
	fusenow=fopen("��ǰ�û�.txt", "r");
	fscanf(fusenow,"%s %s %s %s %s %s",Usenow.ID,Usenow.Name, Usenow.Sex, Usenow.Phone, Usenow.mail, Usenow.PassWord);
	fclose(fusenow);

	while (1)
	{
		printf("%s,��ӭ���뺽�ඩƱϵͳ���û�ģʽ��\n", Usenow.Name);

		printf("*************************************************************************\n");
		printf("*                          ���ն�Ʊ����ϵͳ ���˵�                      *\n");
		printf("*                         1.��ѯ������Ϣ����Ʊ                          *\n");
		printf("*                         2.�鿴�ҵĶ���                                *\n");
		printf("*                         3.������Ϣ����                                *\n");
		printf("*                         4.�˳�ϵͳ                                    *\n");
		printf("*************************************************************************\n");
		printf("��ѡ��1-4\n");
		scanf("%d", &ichioce);
		switch (ichioce)
		{
		case 1:
		{
			Select_Flight();
			FILE *ftt;
			ftt = fopen("��ǰ����.txt", "r");
			char Fnum[20] = "0";     //�û�Ҫ�����Ʊ�ĺ����
			char Ftime[20] = "0";   //�û�Ҫ������������
			fscanf(ftt,"%s  %s", Fnum, Ftime);
			ticketBuy(Fnum,Ftime,Usenow.Name,Usenow.PassWord);       
		    break;
		}//�����ŷ�ֹ����case������ʼ������
		case 2:myTicket(Usenow.Name); 
			break;
		case 3:changeUser();//��wbn������Ϣ������
			break;

		case 4:exit(1);//�˳�
		default:printf("������ڣ����������룡");
			    break;
		}


	}


}
void ticketBuy(char *Fnum,char *Ftime,char *Uname,char *Upassword) // ���ڹ��򺽰�ĺ��������뺽���,�����������,��ǰ�û�������������
{
	Passenger P = { 0 };   //��ǰ�����˻�����Ϣ
	List_F list1 = { 0 };  //��������Ʊ�õ�����p
	List_F list2 = { 0 }; //�ȶԸ��û�֮ǰ�Ķ����õ�����pp

    List_P Pcheck = { 0 };

	int usecho;//�û���ѡ�� ������ת�˵�
	int flag = 0;
	int flag1 = 0;
	
	char *time=0;//��¼����ʱ��
	char *timecheck = 0;//��⡾���졿���user�����Ƿ��򡾳�����Ʊ��!!
	char timedate[12] = "0";//����ȡ����
	
	char s,ss;//���տո�
	int t = list1.count;//t�Ǻ�������
	
	int i = 0, j = 0,k=0;//����
	int p = 0,pp=0;//�û�ѭ������

	//��⡾���졿���user�����Ƿ��򡾳�����Ʊ��
	//Ҳ�����Ϊһ����������д���������������Ǻ�����֤ ��Ҫ�����������Ϣ
    timecheck = GetTime();
	strncpy(timedate, timecheck, 10);//�����������ڡ���timedate
	
	
	UserReadorder(&Pcheck);//��ȡĿǰ���ж�������Ϣ��Pcheck��List_P
	for (i = 0; i <= Pcheck.count; i++)
	{
		if (!strcmp(Uname, Pcheck.a[i].payername))//ɸѡ��ǰ�û��Ķ���
		{
			if(!strncmp(timedate,Pcheck.a[i].Time_date,10))//����ǽ������Ʊ
				j++;
		}

	}

	if (j >= 5)
	{
		printf("%s,�������ѹ������Ż�Ʊ�������ٹ���\n", Uname);
		printf("*     ��Enter���������˵�    *");
		scanf("%c", &s);
		return;
	}





	ReadInfo(&list1);//��������Ϣ
	ReadInfo(&list2);//�ֶ���һ�ݺ�����Ϣ
	
	//ɸ�麽�࣬��ȡ���û�Ŀǰ��ѡ����һ�������ڵġ�������p
	for (p = 0; p <= list1.count; p++)
	{
		if (!strcmp(Fnum, list1.Flight[p].Flightnum))
			break;
	}



	//for (k = 0; k<= Pcheck.count; k++)//ɸѡ���û����ܳ�ͻ��Ʊ �����ж�����ġ�������k
	//{
	//	if (!strcmp(Uname, Pcheck.a[k].payername))//ɸѡ��ǰ�û��Ķ���
	//	{
	//		if (!strcmp(Uname, Pcheck.a[k].Name))//ɸѡ��ǰ�û���Ϊ�Լ����Ʊ
	//		{
	//			if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//�������������Ҫ���Ʊ��һ��
	//			{
	//				for (pp = 0; pp <= list1.count; pp++)//���ܳ�ͻ���Ǹ�Ʊ�ĺ����ں�����Ϣ������pp
	//				{
	//					if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
	//					{
	//						if (strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0)
	//						{
	//							printf("��Ϊ�Լ�����ĸú�����֮ǰ���ѹ���ĺ���ʱ���ϳ�ͻ������������������\n\n\n");
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
		printf("                 ͷ�Ȳգ� %dԪ             ���òգ�%dԪ                  \n\n", list1.Flight[p].Firstfare, list1.Flight[p].Economfare);
		printf("          1.����ͷ�Ȳ�       2.���򾭼ò�        3.ȡ��������            \n");
		scanf("%d", &usecho);


		switch (usecho)
		{
		case 1:
			scanf("%c", &ss);//���տո�
			printf("������˻��˵�������\n");
			gets_s(P.Name);
			
			if (!strcmp(P.Name, Uname))//���Ϊ�Լ���Ʊ
			{
				for (k = 0; k <= Pcheck.count; k++)//ɸѡ���û����ܳ�ͻ��Ʊ �����ж�����ġ�������k
				{
					if (!strcmp(Uname, Pcheck.a[k].payername))//ɸѡ��ǰ�û��Ķ���
					{
						if (!strcmp(Uname, Pcheck.a[k].Name))//ɸѡ��ǰ�û���Ϊ�Լ����Ʊ
						{
							if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//�������������Ҫ���Ʊ��һ��
							{
								for (pp = 0; pp <= list1.count; pp++)//���ܳ�ͻ���Ǹ�Ʊ�ĺ����ں�����Ϣ������pp
								{
									if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
									{
										if ((strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0) && (strcmp(list2.Flight[pp].Flighttime_up, list1.Flight[pp].Flighttime_down) < 0))
										{
											printf("��Ϊ�Լ�����ĸú�����֮ǰ���ѹ���ĺ���ʱ���ϳ�ͻ������������������\n\n\n");
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



			//���ﲻ�ý��ܻس�����Ϊ������ַ���ĩ�˽����� ��һ������Ϊǰһ��������int
			printf("������˻��˵�ID��\n");
			gets_s(P.ID);

			strcpy(P.Seatnum, checkSeatFir());//ѡ����λ�������ݴ��ݸ��û��������ݽṹP
			

			printf("*��֧��%dԪ*\n", list1.Flight[p].Firstfare);
			printf("ѡ��֧����ʽ��1.�û�����֧��/2.ɨ��֧����\n");
			
			scanf("%d", &flag);
			switch (flag)
			{
			case 1:
				checkPass(Upassword);
				break;
			case 2:
				QRcode();
				char usesec[20];
				printf("�������½���루��֧�����룩��\n");
				while (1)
				{
					scanf("%s", usesec);
					if (strcmp(usesec, "asdfg"))
					{
						printf("����������������룡\n");
					}
					else break;
				}

				printf("������ȷ��֧���ɹ����ѳɹ���Ʊ��\n");
				break;
			default:
				break;
			}
			sprintf(P.Flighttype, "ͷ�Ȳ�");
			printf("*���ڳ�Ʊ*\n");
			printf("��\n");
			Sleep(1000);
			printf("��\n");
			Sleep(1000);
			printf("��\n");
			Sleep(1000);
			Boardcheck(P,list1,p);

			time = GetTime();//��ȡ����ʱ��
			list1.Flight[p].Ordernum_firs++;//��p�еĺ���ͷ��Ʊ+1��

			FILE *fa;//д�û���Ʊ�ļ����ļ�ָ��
			fa = fopen("9.9������Ϣ.txt", "a");

			//fprintf(fa, "�����	    �ǻ���	   ID     ���չ�˾       ��λ     ����ʱ��        ������    ������Ϣ��������� ���ʱ�� ����ʱ�� ������ Ŀ�ĵ� ���� ����Ա1 ����Ա2��\n");
			fprintf(fa, "%-8s %-10s %-12s %-10s %-10s   %-10s      %-10s  %-10s  %-10s  %-8s  %-8s  %-8s  %-8s  %-8s  %-8s\n", 
				list1.Flight[p].Flightnum, P.Name, P.ID, list1.Flight[p].Company, 
				P.Seatnum, time,Uname, Ftime,list1.Flight[p].Flighttime_up, 
				list1.Flight[p].Flighttime_down, list1.Flight[p].Startland, list1.Flight[p].Downland, 
				list1.Flight[p].Flighttype, list1.Flight[p].Pilot_1, list1.Flight[p].Pilot_2);
			
			scanf("%c", &ss);//��ô����Ҫ������
			printf("*     ��Enter���������˵�    *");
			scanf("%c", &s);
			fclose(fa);

			break;
		case 2:
			printf("������˻��˵�������\n");
			scanf("%c", &ss);
			gets_s(P.Name);
			if (!strcmp(P.Name, Uname))//���Ϊ�Լ���Ʊ
			{
				for (k = 0; k <= Pcheck.count; k++)//ɸѡ���û����ܳ�ͻ��Ʊ �����ж�����ġ�������k
				{
					if (!strcmp(Uname, Pcheck.a[k].payername))//ɸѡ��ǰ�û��Ķ���
					{
						if (!strcmp(Uname, Pcheck.a[k].Name))//ɸѡ��ǰ�û���Ϊ�Լ����Ʊ
						{
							if (!strcmp(Ftime, Pcheck.a[k].FlyTime))//�������������Ҫ���Ʊ��һ��
							{
								for (pp = 0; pp <= list1.count; pp++)//���ܳ�ͻ���Ǹ�Ʊ�ĺ����ں�����Ϣ������pp
								{
									if (!strcmp(Fnum, list2.Flight[pp].Flightnum))
									{
										if ((strcmp(list1.Flight[pp].Flighttime_up, list2.Flight[pp].Flighttime_down) < 0) && (strcmp(list2.Flight[pp].Flighttime_up, list1.Flight[pp].Flighttime_down) < 0))
										{
											printf("��Ϊ�Լ�����ĸú�����֮ǰ���ѹ���ĺ���ʱ���ϳ�ͻ������������������\n\n\n");
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


			printf("������˻��˵�ID��\n");
			gets_s(P.ID);
			strcpy(P.Seatnum, checkSeatEco());//ѡ����λ�������ݴ��ݸ��û��������ݽṹP
			
			//֧������֤����
			printf("*��֧��%dԪ*\n", list1.Flight[p].Economfare);

			printf("ѡ��֧����ʽ��1.�û�����֧��/2.ɨ��֧����\n");
			
			scanf("%d", &flag1);
			switch (flag1)
			{
			case 1:
				checkPass(Upassword);
				break;
			case 2:
				QRcode();
				char usesec[20];
				printf("��������֤�룺\n");
				while (1)
				{
					scanf("%s", usesec);
					if (strcmp(usesec, "asdfg"))
					{
						printf("����������������룡\n");
					}
					else break;
				}

				printf("������ȷ��֧���ɹ����ѳɹ���Ʊ��\n");
				break;
			default:
				break;
			}
			
			sprintf(P.Flighttype, "���ò�");
			printf("*���ڳ�Ʊ*\n");
			printf("��\n");
			Sleep(1000);
			printf("��\n");
			Sleep(1000);
			printf("��\n");
			Sleep(1000);
			Boardcheck(P,list1,p);

			time = GetTime();//��ȡ����ʱ��
			list1.Flight[p].Ordernum_econ++;//��p�еĺ��ྭ��Ʊ+1��


			FILE *fr;//д�û���Ʊ�ļ����ļ�ָ��
			fr = fopen("9.9������Ϣ.txt", "a");
			//fprintf(fr, "�����	     ����	      ID	    ���չ�˾     ��λ   ����ʱ��     ������Ϣ�����ʱ�� ����ʱ�� ������ Ŀ�ĵ� ���� ����Ա1 ����Ա2��\n");
			fprintf(fr, "%-8s %-10s %-12s %-10s %-10s   %-10s      %-10s  %-10s  %-10s  %-8s  %-8s  %-8s  %-8s  %-8s  %-8s\n",
				list1.Flight[p].Flightnum, P.Name, P.ID, list1.Flight[p].Company,
				P.Seatnum, time, Uname, Ftime, list1.Flight[p].Flighttime_up,
				list1.Flight[p].Flighttime_down, list1.Flight[p].Startland, list1.Flight[p].Downland,
				list1.Flight[p].Flighttype, list1.Flight[p].Pilot_1, list1.Flight[p].Pilot_2);
			
			scanf("%c", &ss);//��ô����Ҫ������
			printf("*     ��Enter���������˵�    *");
			scanf("%c", &s);
			fclose(fr);
			break;
		case 3:  //��ô���ذ�
			break;

		default:printf("������ڣ����������룡\n");    //��ô����������򵥣� ��while��1����

		};
		return;//���ص����˵�����ʹ����
	};


}

void myTicket(char *Uname)
{
	char s,ss;//���ջس�

	List_P P = { 0 };
	UserReadorder(&P);//��ȡ���ж�������Ϣ
	
	printf("%s������! Ϊ����ѯ�����Ķ������£�\n", Uname);
	printf("�����   �ǻ���    ID          ���չ�˾ ��λ        ����ʱ��             ������    �������\n");
	//��ʼɸѡ
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
		printf("����ǰ��û�ж�����\n");
	scanf("%c", &ss);//��ô����Ҫ������
	printf("*     ��Enter���������˵�    *");
	scanf("%c", &s);
}

void UserReadorder(List_P *P)
{
	FILE *fp;
	if ((fp = fopen("9.9������Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		P->count = 0;//��ʼ������(������)
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n���У�n-1������\n����ȥ����һ�� n-1Ϊ������
				P->count++;
		}
		rewind(fp);
		//char temp[300] = { 0 };
		//fgets(temp, 300, fp);
		for (int i = 0; i < P->count; i++)
		{
			char ID[20];

			//yza�޸ģ���Ϊ�Ҳ����һ��������һ�С��������Ҿ�ȫ������ȥ
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
	char usesec[20];//�û���������룬������֤�ȶ��Ƿ���ȷ


	printf("�������½���루��֧�����룩��\n");
	while (1)
	{
		scanf("%s", usesec);
		if (strcmp(usesec, Upassword))
		{
			printf("����������������룡\n");
		}
		else break;
	}

	printf("������ȷ��֧���ɹ����ѳɹ���Ʊ��\n");

}

char* checkSeatFir()
{

	char seat1[20];//����
    char seat2[20];//��λ��
	char seat[10] = "F";
	strcat(seat,buy(seat1, seat2,1));
	printf("��λѡ��ɹ���\n");
	return seat;
}
char* checkSeatEco()
{
	char seat1[20] = {0};//����
	char seat2[20] = {0};//��λ��
	char seat[10] = "Y";
	strcat(seat, buy(seat1, seat2, 2));
	printf("��λѡ��ɹ���\n");
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
	loadimage(&img, "�ɻ�.jpg", 1300, 800);
	putimage(0, 0, &img);
	settextcolor(BLACK);
	settextstyle(30, 0, "����");
	if (q == 1)
	{
		outtextxy(460, 300, "������������1-10��:");
		InputBox(c1, 10, "������������1-10��:");
	}
	else
	{
		outtextxy(460, 300, "������������11-30��:");
		InputBox(c1, 10, "������������11-30��:");
	}
	for (int i = 0; i < 5; i++)
	{
      outtextxy(420 + i * 90, 430, seatnum[i]);
		if (i == a)
		{
			loadimage(&img2, "����λ.png", 50, 50);
			putimage(420 + i * 90, 480, &img2);
			continue;
		}
		
		loadimage(&img1, "����λ.png", 50, 50);

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
					settextstyle(50, 0, "����");
					outtextxy(460, 570, "����λ�����ˣ�");
				}
				else {
					if (msg.x > 420 && msg.x < 470 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "����λ.png", 50, 50);
						b = 1;
						putimage(420, 480, &img1);
						sprintf(c2, "A");
						break;

					}
					else if
						(msg.x > 420 + 90 && msg.x < 470 + 90 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "����λ.png", 50, 50);
						b = 1;
						putimage(420 + 90, 480, &img1);
						sprintf(c2, "B");
						break;
					}
					else if (msg.x > 420 + 180 && msg.x < 470 + 180 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "����λ.png", 50, 50);
						b = 1;
						putimage(420 + 180, 480, &img1);
						sprintf(c2, "C");
						break;
					}
					else if (msg.x > 420 + 270 && msg.x < 470 + 270 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "����λ.png", 50, 50);
						b = 1;
						putimage(420 + 270, 480, &img1);
						sprintf(c2, "D");
						break;
					}
					else if (msg.x > 420 + 360 && msg.x < 470 + 360 && msg.y>480 && msg.y < 530)
					{
						loadimage(&img1, "����λ.png", 50, 50);
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