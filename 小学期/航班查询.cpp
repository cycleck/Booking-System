#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "���ݽṹ.h"
#include "��������.h"
#include"�����ѯ.h"
#include"��Ʊ.h"
#pragma warning(disable : 4996)
//�����ĸ��������͵ĺ���ָ������
void(*FuncPointerArray[4])(List_F F1,char*Date) = { filter_time ,filter_company,filter_class,filter_type };

void Select_Flight() {
	getchar();//���ջس���
	printf("\n ��ӭ���뺽���ѯ\n");
	printf("������ѡ���������ֺ����ѯ���ͣ�\n");
	printf("******************************************\n");
	printf("*   1.�Գ���ʱ��ͺ���Ų�ѯ             *\n");
	printf("*   2.�Գ���ʱ��ͳ������У�������в�ѯ *\n");
	//printf("*   0.�������˵�                           *\n");
	printf("******************************************\n");
	printf("�������Ӧ��ѡ������:\n");
	while (1) {
		List_F F = { 0 };
		char Date[20];//�����û����������
		char date[20];//����Date�е��ַ���������judge_Date(date)����������Ϊdata/flight/9.x������Ϣ.txt---������Ϣ·��
		char str3[50];//����date�ַ���
		char flightnum[20];//���պ����
		char startland[20];//���ճ�����
		char downland[20];//����Ŀ�ĵ�
		char type[20];//���ܲ�ѯ���͵�ѡ�����
		gets_s(type);
		if (strncmp(type, "1", 20) == 0) {
			printf("��������ѡ�������:(���� 9.2 �ĸ�ʽд���ڣ�\n");
			gets_s(Date,20);
			strcpy(date, Date);
			//����judge_Date(date)���������غ�����Ϣ·�� data/flight/9.x������Ϣ.txt
			strcpy(str3,judge_Date(date));//str3����Ϊ data/flight/9.x������Ϣ.txt
			user_readinfo(&F,str3);//�õ�������Ϣ���ÿ�������ĵ�ַ
			//�����ǰ��ѯ���ڵ����к�����Ϣ
			printf("��������ѡ��ĺ����:\n");
			gets_s(flightnum);
			select_Flightnum_Date(flightnum, Date,F);//�������ʱ��ͺ���Ų�ѯ
			break;
		}
		else if (strncmp(type, "2", 20) == 0) {
			printf("��������ѡ�������:(���� 9.2 �ĸ�ʽд���ڣ�\n");
			gets_s(Date, 20);
			strcpy(date, Date); 
			//����judge_Date(date)���������غ�����Ϣ·�� data/flight/9.x������Ϣ.txt
			strcpy(str3, judge_Date(date));//str3����Ϊ data/flight/9.x������Ϣ.txt
			user_readinfo(&F, str3);//�õ�������Ϣ���ÿ�������ĵ�ַ
			//�����ǰ��ѯ���ڵ����к�����Ϣ
			printf("��������ѡ��ĳ�����:\n");
			gets_s(startland);
			printf("��������ѡ���Ŀ�ĵ�:\n");
			gets_s(downland);
			select_City_Date(startland, downland,Date,F);//�������ʱ��ͳ������У�������в�ѯ
			break;
		}
		else {
			printf("����������ʹ���\n���������룺\n");
		}
	}
}
void select_Flightnum_Date(char* num, char*Date,List_F F) {
	int j = 0;//��ѯ���ĺ������
	List_F F1 = { 0 };
	for (int i = 0; i < F.count; i++) {//F.countΪ��ѯ���ĺ�������
		if (strcmp(num,F.Flight[i].Flightnum)== 0) {//�ж��û�����ĺ�����Ƿ����
				//��ѯ������ͬ�ĺ���ŵĴ���
				F1.Flight[j] = F.Flight[i];
				j++;//��ѯ��j�ξ���j�κ�����
		}
	}
	F1.count = j;//�����������ֵ���յĽṹ�� F1.count
	if (!j) {//���δ��ѯ���ú����
		printf("�޷���ѯ���ú�����Ϣ\n");
		printf("*   ���enter�����غ�������ѯ    *\n");
		Select_Flight();
	}
	else {
		sort_by_Price(&F1, j);
		//��Ϊÿ�캽��ֻ��һ�ˣ�����ֱ����ת��ѯ���Ƿ�Ʊ�Ľ���
		if_buy_ticket(F1.Flight[0].Flightnum,Date);
	}
	

	
}
void select_City_Date(char* start, char* down, char*Date,List_F F) {
	int j = 0;
	List_F F1 = { 0 };
	for (int i = 0; i < F.count; i++) {//F.countΪ��ѯ���ĺ�������
		if (strcmp(start, F.Flight[i].Startland) == 0 && strcmp(down, F.Flight[i].Downland) == 0)//�ж��û�����ĳ�������Ŀ�ĵ��Ƿ��ں�����Ϣ�ڴ���
		{
			//��ѯ������ͬ�ĺ���ŵĴ���
			F1.Flight[j] = F.Flight[i];
			j++;//��ѯ��j�ξ���j�κ�����
		}
	}
	F1.count = j;//�����������ֵ���յĽṹ�� F1.count
	if (!j) {//���δ��ѯ���ú����
		printf("�޷���ѯ���ú�����Ϣ\n");
		printf("*   ���enter�����غ�������ѯ    *\n");
		Select_Flight();
	}
	else if (j == 1) {
		sort_by_Price(&F1, j);
		printf("*       ��⵽����ѯ���ĺ�����Ϣ��һ������enter��ֱ��Ϊ����ת����Ʊҳ��      *\n");
		getchar();
		if_buy_ticket(F1.Flight[0].Flightnum, Date);
	}
	else {
		sort_by_Price(&F1, j);
		if_filter(F1, Date);
		//��Ϊ��ͬ�����������ͬ�ĳ�������Ŀ�ĵأ�������ת���Ƿ�Ҫ����ɸ��ѡ��Ľ���
	}
}

void if_filter(List_F F1,char*Date) {
	char answer[20];
	printf("******************************************\n");
	printf("*   �Ƿ�ѡ���ڲ�ѯ����ϼ�������ɸѡ��   *\n");
	printf("*   ����ѡ���ɸѡ������:                *\n");
	printf("* 1��ʱ��� 2�����չ�˾ 3����λ 4������  *\n");
	printf("******************************************\n");
	printf("�����ǣ�����ɸѡ������񣬽��빺Ʊ��\n");
	gets_s(answer);
	while (1) {
		if (strncmp(answer,"��",20) == 0) {
			sort_by_Price(&F1, F1.count);//ͨ�����Ʊ�����򺽰��ѯ���ĺ���
			if (F1.count > 1) {
				char Flightnum[20];
				char Flightnumber[20];
				char date[50];
				char str3[50];
				printf("*           ������ѯ���ĺ�����Ϣ����һ����������������������ĺ����            *\n");
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
		else if (strncmp(answer, "��", 20) == 0) {
			if_filter_yes(F1,Date);//ѡ�����ɸ�飬����ɸ�����
			break;
		}
		else {
			printf("����������������������\n");
			printf("�����ǣ�����ɸѡ������񣬽��빺Ʊ��\n");
			gets_s(answer);
		}
	}
}
void if_filter_yes(List_F F1,char*Date) {
	while (1) {
		int num;
		printf("******************************************\n");
		printf("*   ����ѡ���ɸѡ������:                *\n");
		printf("* 1��ʱ��� 2�����չ�˾ 3����λ 4������  *\n");
		printf("******************************************\n");
		printf("�������Ӧѡ������\n");
		scanf_s("%d", &num);
		if (num == 1 || num == 2 || num == 3 || num == 4) {
			num--;
			//(*FuncPointerArray[4])(List_F F1, char* Date) = { filter_time ,filter_company,filter_class,filter_type };
			FuncPointerArray[num](F1, Date);//ѡ���������
			break;
		}
		else {
			printf("��������ȷ��ֵ\n");
		}
	}
}

void filter_time(List_F F1,char*Date) {
	int put;//�û������������
	int j = 0;
	int num[6] = { 1,2,3,4,5,6 };
	char time_start[6][20] = { "00:01","04:01","08:01" ,"12:01" ,"16:01" ,"20:01" };
	char time_end[6][20] = { "04:00","08:00","12:00" ,"16:00" ,"20:00" ,"24:00" };
	char answer[20];
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("************************\n");
		printf("*   ��ѡ��ʱ���:      *\n");
		printf("*   1. 00:01 -- 04:00  *\n");
		printf("*   2. 04:01 -- 08:00  *\n");
		printf("*   3. 08:01 -- 12:00  *\n");
		printf("*   4. 12:01 -- 16:00  *\n");
		printf("*   5. 16:01 -- 20:00  *\n");
		printf("*   6. 20:01 -- 24:00  *\n");
		printf("************************\n");
		printf("�������Ӧ��ѡ������:\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] || put == num[3] || put == num[4] || put == num[5])) {
			printf("�������ֵ����\n����������\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				//�Ƚ���ѡ��ʱ������Ƿ��в�ѯ���ĺ���
				if (strcmp(F1.Flight[j].Flighttime_up, time_start[put - 1]) == 1 && strcmp(F1.Flight[j].Flighttime_up, time_end[put - 1]) == -1) {
					F2.Flight[k] = F1.Flight[j];//����ѯ���Ľ������һ���µ�List_F�ṹ��
					k++;//k����ʾ�����±꣬�ֱ�ʾɸѡ�õ��ĺ�����
				}
			}
			printf("ɸѡ���\n");
			sort_by_Price(&F2, k);//ͨ����ͼ۸��������
			if (!k) {
				if_filter_yes(F1, Date);//����ɸѡ
				break;
			}
			else {
				printf("�Ƿ��������ɸ�飿\n");
				printf("����'��Ʊ'���빺Ʊ���棬��������������ɸѡ\n");
				getchar();//��ֹgets_s������
				gets_s(answer, 20);
				if (strncmp(answer, "��Ʊ", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   ������ѯ���ĺ�����Ϣ����һ����������������������ĺ����     *\n");
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
					if_filter_yes(F1, Date);//����ɸѡ
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
	char CompanyList[3][20] = { "�Ϸ�����","���Ϻ���","��������" };
	char answer[20]; 
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("**********************\n");
		printf("*   ��ѡ�񺽿չ�˾:  *\n");
		printf("*   1. �Ϸ�����      *\n");
		printf("*   2. ���Ϻ���      *\n");
		printf("*   3. ��������      *\n");
		printf("**********************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] )) {
			printf("�������ֵ����\n����������\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				if (strcmp(F1.Flight[j].Company, CompanyList[put - 1]) == 0) {
					F2.Flight[k] = F1.Flight[j];
					k++;
				}
			}
			printf("ɸѡ���\n");
			sort_by_Price(&F2, k);
			if (!k) {
				if_filter_yes(F1, Date);//����ɸѡ
				break;
			}
			else {
				printf("����'��Ʊ'���빺Ʊ���棬��������������ɸѡ\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "��Ʊ", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   ������ѯ���ĺ�����Ϣ����һ����������������������ĺ����     *\n");
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
		printf("*     ��ѡ���λ:  *\n");
		printf("*   1. ͷ�Ȳ�      *\n");
		printf("*   2. ���ò�      *\n");
		printf("********************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1])) {
			printf("�������ֵ����\n");
			printf("����������\n\n");
		}
		else {
			if (put == 1) {
				if (F1.count == 0)
					printf("δ��ѯ��������Ϣ\n");
				else {
					printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�     ͷ�Ȳ���Ʊ           ���չ�˾  ׼����\n");
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
					printf("δ��ѯ��������Ϣ\n");
				else {
					printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����         ���òռ۸�       ���ò���Ʊ       ���չ�˾  ׼����\n");
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
			printf("ɸѡ���\n");
			if (!F1.count) {
				if_filter_yes(F1, Date);//����ɸѡ
				break;
			}
			else {
				printf("����'��Ʊ'���빺Ʊ���棬��������������ɸѡ\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "��Ʊ", 20) == 0) {
					if (F1.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   ������ѯ���ĺ�����Ϣ����һ����������������������ĺ����     *\n");
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
	char TypeList[4][20] = { "�տ�321","����737","JET" ,"�տ�320"};
	char answer[20];
	while (1) {
		List_F F2 = { 0 };
		int k = 0;
		printf("*******************\n");
		printf("* ��ѡ��ɻ�����: *\n");
		printf("*   1. �տ�321    *\n");
		printf("*   2. ����737    *\n");
		printf("*   3. JET        *\n");
		printf("*   4. �տ�320    *\n");
		printf("*******************\n");
		scanf_s("%d", &put);
		if (!(put == num[0] || put == num[1] || put == num[2] || put==num[3])) {
			printf("�������ֵ����\n");
			printf("����������\n\n");
		}
		else {
			for (j = 0; j < F1.count; j++) {
				if (strcmp(F1.Flight[j].Flighttype, TypeList[put - 1]) == 0) {
					F2.Flight[k] = F1.Flight[j];
					k++;
				}
			}
			printf("ɸѡ���\n");
			sort_by_Price(&F2, k);
			if (!k) {
				if_filter_yes(F1, Date);//����ɸѡ
				break;
			}
			else {
				printf("����'��Ʊ'���빺Ʊ���棬��������������ɸѡ\n");
				getchar();
				gets_s(answer, 20);
				if (strncmp(answer, "��Ʊ", 20) == 0) {
					if (F2.count > 1) {
						char Flightnum[20];
						char Flightnumber[20];
						char date[50];
						char str3[50];
						printf("*   ������ѯ���ĺ�����Ϣ����һ����������������������ĺ����     *\n");
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
		FlightInfo Temp;//����һ����ʱ�Ľṹ��
		//��С�����������ʱ��
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
		printf("*****   δ��ѯ��������Ϣ\n");
		return ;
	}
	printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ    ���ò���Ʊ       ���չ�˾  ׼����\n");
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
	printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ    ���ò���Ʊ       ���չ�˾  ׼����\n");
	printf("\n"); 
	for (int i = 0; i < F1->count; i++) {
		
		printf(" %7s\t   %7s\t %5s\t   %5s\t   %5s\t   %5s\t   %5d\t   %5d\t           %5d         %5d    %7s  %10s\n", F1->Flight[i].Flightnum, F1->Flight[i].Flighttime_up,
			F1->Flight[i].Flighttime_down, F1->Flight[i].Startland, F1->Flight[i].Downland, F1->Flight[i].Flighttype, F1->Flight[i].Firstfare,
			F1->Flight[i].Economfare, F1->Flight[i].Firstrest, F1->Flight[i].Economrest, F1->Flight[i].Company, F1->Flight[i].Ontimerate);

		
	}

}
void sortPrice(List_F* F1, int i) {
	for (int j = 0; j < i; j++) {
		FlightInfo Temp;//���һ���ݴ��FlightInfo�ṹ��
		if (F1->Flight[j].Economfare > F1->Flight[i].Economfare) {//�Ƚϲ�ѯ�ṹ�ĺ������ͼ۸�
			//��������Ϣ����ͼ۸����ʽ���ӵ͵�������
			Temp = F1->Flight[j];
			F1->Flight[j] = F1->Flight[i];
			F1->Flight[i] = Temp;
		}
	}
}
void sort_by_Price(List_F* F1, int k) {
	for (int i = 0; i < k; i++)
		sortPrice(F1, i);//i��ʾ�ڲ�ѭ���ĵ�i+1��
	if (k == 0) {
		printf("δ��ѯ��������Ϣ\n\n");
	}
	else {
		printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ    ���ò���Ʊ       ���չ�˾  ׼����\n");
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
	ft = fopen("��ǰ����.txt", "w");
	fprintf(ft, "%s   %s", Flightnum, Date);//���������뵽��ǰ����.txt��
    fclose(ft);


	printf("\n");
	printf("\n                     *****************************************                   \n");
	
}
char* judge_Flightnum(char* Flightnum,char* Date) {
	while (1) {
		//�жϺ�����Ƿ����ǰ�����ַ�Ϊ��д��ĸ���ĸ��ַ�Ϊ����
		if (Flightnum[0] >= 'A' && Flightnum[0] <= 'Z' && Flightnum[1] >= 'A' && Flightnum[1] <= 'Z' 
			&& Flightnum[2] >= '0' && Flightnum[2] <= '9' && Flightnum[3] >= '0' && Flightnum[3] <= '9' 
			&& Flightnum[4] >= '0' && Flightnum[4] <= '9' && Flightnum[5] >= '0' && Flightnum[5] <= '9' 
			&& strlen(Flightnum) == 6) {
			break;

		}
		else {
			printf("������ĺ���Ŵ����밴��ʽ������λ�ŵĺ���   ����CZ9424\n");
			gets_s(Flightnum, 20);
		}
	}
	int j = 0;
	List_F F = { 0 };
	List_F F1 = { 0 };
	F.count = 0;//��ʼ������
	FILE* fp = fopen(Date, "r");//DateΪ����·��
	if (fp == NULL)
	{
		printf("��Ǹ�������ڵĺ�����Ϣ������/// \n");
		exit(1);
	}
	else
	{
	    
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n���У�n-1������\n����ȥ����һ�� n-1Ϊ������
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
		//�����ڸú���ţ���ɷ��ظú����
		if (strcmp(Flightnum ,F.Flight[i].Flightnum)==0) {
			j=1;
		}
	}
	if (!j) {
		printf("�ú���Ų�����");
		printf("���������뺽���\n");
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
				printf("������������д���,����9.xx�ĸ�ʽ����  ����9.1\n");
				gets_s(Date, 20);
			}

		}
		else if (strlen(Date) == 4) {
			if (Date[0] == '9' && Date[1] == '.' && Date[2] == '1' && Date[3] >= '0' && Date[3] <= '9') {
				break;
			}
			else {
				printf("������������д�������9.xx�ĸ�ʽ����  ����9.1\n");
				gets_s(Date, 20);
			}
		}
		else {
			printf("������������д�������9.xx�ĸ�ʽ����  ����9.1\n");
			gets_s(Date, 20);
		}
	}
	return Date;
}
char* judge_Date(char* Date) {
	judgedate(Date);

	char  str1[50] = "������Ϣ.txt";
	char  str3[50] = "data/flight/";
	strcat(Date, str1);
	strcat(str3,Date);
	FILE* fp = fopen(str3, "r");//str3=data/flight/9.x������Ϣ.txt
	if (fp == NULL)
	{
		printf("��Ǹ�������ڵĺ�����Ϣ������!!! \n");
		exit(1);
	}
	fclose(fp);
	
	return str3;
}

void user_readinfo(List_F* F, char* Date) {

	FILE* fp = fopen(Date, "r");
	if (fp == NULL)
	{
		printf("��Ǹ�������ڵĺ�����Ϣ������111 \n");
		exit(1);
	}
	else
	{
		while (!feof(fp))//feof:���λ���ı���βΪ1 �ǽ�βΪ0
		{
			if (fgetc(fp) == '\n')   //n���У�n-1������\n����ȥ����һ�� n-1Ϊ������
				F->count++;
		}
		rewind(fp);
		for (int i = 0; i < F->count; i++)
		{
			fscanf(fp, "%s %s %s %s %s %s %d %d %d %d %s %s %s %s \n", F->Flight[i].Flightnum, F->Flight[i].Flighttime_up,
				F->Flight[i].Flighttime_down, F->Flight[i].Startland, F->Flight[i].Downland, F->Flight[i].Flighttype, &F->Flight[i].Firstfare,
				&F->Flight[i].Economfare, &F->Flight[i].Firstrest, &F->Flight[i].Economrest, F->Flight[i].Pilot_1, F->Flight[i].Pilot_2, F->Flight[i].Company,F->Flight[i].Ontimerate);
		}
	
		printf("Ϊ����ѯ�������ڵĺ�����Ϣ����:\n");
		sort_All_by_Time(F);

	}
	fclose(fp);

}


