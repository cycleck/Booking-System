#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"���ݽṹ.h"
#include <graphics.h>		//����ͼ�ο��ļ�
#include <conio.h>
#include<windows.h> 
#pragma warning(disable : 4996)
//***********************
//***********************
//��ȡ���պ�����Ϣ
void ReadInfo(List_F *F)
{
	FILE*fp;
	if ((fp = fopen("data/flight/9.9������Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		F->count = 0;//��ʼ������
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			 if ( fgetc(fp)== '\n')   //n���У�n-1������\n����ȥ����һ�� n-1Ϊ������
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
//��ӡ������Ϣ���û��棩
void PrintAirmsg_U(List_F F)     //��Ʊ�û�ʹ��
{
	printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ    ���ò���Ʊ   ����Ա1    ����Ա2    ���չ�˾  ׼����\n");
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
//��ӡ������Ϣ������Ա�棩
void PrintAirmsg_A(List_F F)   //����Աʹ��
{
	printf("�����  ���ʱ��    ����ʱ��    ������    Ŀ�ĵ�      ����  ͷ�Ȳռ۸� ���òռ۸� ͷ�Ȳ���Ʊ ���ò���Ʊ   ����Ա1  ����Ա2  ���չ�˾  ׼����  ���� ������ ��Ʊ��\n");
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
//��ȡ�����ļ�
void Readorder(List_P *P)
{
	FILE *fp;
	if ((fp = fopen("9.9������Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{//����ļ����м��У�����������Ϣ��
		P->count= 0;//��ʼ������(������)
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n���У�n-1������\n��
				P->count++;
		}
		rewind(fp);//���ָ�����ʼλ��

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
//��ӡ����
void Printorder(List_P P)
{
	printf("�����   ����   ���֤   ���չ�˾        ��λ     ʱ��\n");
	printf("\n");
	for (int i = 0; i < P.count; i++)
	{
		printf("%s\t %s\t %s\t %s\t %s\t %s%s\n", P.a[i].Flightnum, P.a[i].Name, P.a[i].ID, P.a[i].Company, P.a[i].Seatnum, P.a[i].Time_date, P.a[i].Time_min);

	}
}
//***********************
//***********************
//��ѯ����Ա�Լ��������չ�˾�ĺ���Ķ�Ʊ���N�������ѱ���Ʊ����ϸ��Ϣ
//���ʱ�ĸ��û��������ĸ�������ĸ���λ
void Showorder(List_F F, List_P P, Admination A)
{
	while (1)
	{
		printf("Ϊ����ѯ������˾��������:\n");
	printf("����� ���ʱ�� ����ʱ��  ������            Ŀ�ĵ�         ����      ͷ�Ȳռ۸�     ���òռ۸�    ͷ�Ȳ���Ʊ ���ò���Ʊ   ����Ա1   ����Ա2  ���չ�˾\n");
	printf("\n");
	for (int i = 0; i < F.count; i++)
	{
		if (!strcmp(A.Company, F.Flight[i].Company))//�ȶԺ��չ�˾��һ�����ӡ
		{
			printf(" %6s\t%5s\t %5s\t %7s\t %7s\t  %6s\t  %6d\t  %6d    %6d  %6d     %6s\t%6s  %6s\n", F.Flight[i].Flightnum, F.Flight[i].Flighttime_up,
				F.Flight[i].Flighttime_down, F.Flight[i].Startland, F.Flight[i].Downland, F.Flight[i].Flighttype, F.Flight[i].Firstfare,
				F.Flight[i].Economfare, F.Flight[i].Firstrest, F.Flight[i].Economrest, F.Flight[i].Pilot_1, F.Flight[i].Pilot_2, F.Flight[i].Company);
		}
	}
	printf("����������鿴��Ʊ��Ϣ�ĺ���ĺ���ţ�\n");
	char temp[7] = { 0 };       
	getchar();
	gets_s(temp);
	printf("Ϊ����ѯ�ĳ˿���Ϣ���£�\n");
	printf("�����   ����   ���֤            ���չ�˾        ��λ     ����     ʱ��\n");
	printf("\n");
	for (int i = 0; i < P.count; i++)
	{
		if (!strcmp(temp, P.a[i].Flightnum))
		{
			printf("%7s\t %10s\t %11s\t %7s\t %5s\t %5s\t %5s\n", P.a[i].Flightnum, P.a[i].Name, P.a[i].ID, P.a[i].Company, P.a[i].Seatnum, P.a[i].Time_date, P.a[i].Time_min);
		}

	}
	printf("��ѡ���Ƿ��˳������˵���1.��/2.��\n");
	int a;//�ж��Ƿ��˳�
	scanf("%d", &a);
	if (a == 1)
	{
		return;
	}

}
	

}
//***********************
//***********************
//��ȡ�����캽����Ϣ
void ReadInfo_otherday(List_F *F, int i)//i ����9��i��
{
	char  str1[20] = "������Ϣ.txt";
	char  str2[100] = { 0 };
	char  str3[50] = "data/flight/";
	sprintf(str2, "9.%d", i);//���������Ǽ���
	strcat(str2, str1);
	strcat(str3, str2);
	FILE*fp;
	if ((fp = fopen(str3, "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		F->count = 0;//��ʼ������
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n���У�n-1������\n��
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
//���㶩����������/������/������
void calculate_F(List_F *F)
{
	for (int i = 0; i < F->count; i++)
	{
		F->Flight[i].Firstrest -= F->Flight[i].Ordernum_firs;
		F->Flight[i].Economrest -= F->Flight[i].Ordernum_econ;
	    F->Flight[i].Ordernum = 200 - F->Flight[i].Firstrest - F->Flight[i].Economrest;//���ò�һ��150��λ
		F->Flight[i].Income = (150 - F->Flight[i].Economrest)*F->Flight[i].Economfare 
			+ (50 - F->Flight[i].Firstrest)*F->Flight[i].Firstfare;//ͷ�Ȳ�һ��50��λ
		F->Flight[i].Rate = (double)F->Flight[i].Ordernum / 200;
    }
}
//***********************
//***********************
//����������
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
//������������
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
//������������
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
	printf("����� ���ʱ�� ����ʱ�� ������ Ŀ�ĵ� ���� ͷ�Ȳռ۸�   ���òռ۸�    ͷ�Ȳ���Ʊ     ���ò���Ʊ    ����Ա1    ����Ա2   ���չ�˾   ������\n");
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
//�Ƽ����ࣨ�Ƽ�������Ʊ����������
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
	printf("*******************************************�����Ƽ�����***********************************************************\n");
	printf("����� ���ʱ�� ����ʱ�� ������ Ŀ�ĵ� ���� ͷ�Ȳռ۸� ���òռ۸� ͷ�Ȳ���Ʊ ���ò���Ʊ ����Ա1 ����Ա2 ���չ�˾ ׼����\n");
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
//��ȡ��ǰ����Ա����Ϣ
void ReadAdmination(Admination* A)
{
	FILE*fp;
	if ((fp = fopen("��ǰ����Ա.txt", "r")) == NULL)
	{
		printf("�ļ������� \n");
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
//������ά��
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
//�����ǻ���
void Boardcheck(Passenger P,List_F F,int i)
{
	initgraph(800, 600, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE img;//����ͼƬ
	loadimage(&img, "�ǻ���.png", 800, 600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);


	setfillcolor(WHITE);//������
	fillrectangle(158, 205, 208, 235);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, "����");
	outtextxy(164, 212, F.Flight[i].Startland);//�ɻ�������

	setfillcolor(WHITE);
	fillrectangle(375, 205, 424, 235);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, "����");
	outtextxy(375, 212, F.Flight[i].Downland);//�ɻ�Ŀ�ĵ�


	setfillcolor(WHITE);
	fillrectangle(211, 277, 293, 295);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0,"����");
	outtextxy(216, 280, P.Name);//�˿�����

	setfillcolor(WHITE);
	fillrectangle(395, 277, 407, 295);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(16, 0, "����");
	outtextxy(395, 280,P.Flighttype );//��λ����

	setfillcolor(RGB(26, 35, 126));
	solidrectangle(579, 230, 656, 360);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(18, 0, "����");
	outtextxy(579, 246, F.Flight[i].Flightnum);
	settextstyle(18, 0, "����");
	outtextxy(579, 338, P.Seatnum);//��λ��

	getchar();
	getchar();
	closegraph();
}