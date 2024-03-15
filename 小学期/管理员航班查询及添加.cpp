#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "���ݽṹ.h"
#include "����Ա�����ѯ�����.h"
#pragma warning(disable : 4996)

/*�����ṹ�����ڵ�ͷ�ļ�*/

/*�жϷ���Ա�����Ƿ�Ϊ����*/
int is_Chinese(char* str)
{
	int len = strlen(str);
	/*�ж��ַ��������Ƿ����2��Ϊ2�ı���*/
	if (len < 2 && len%2 )
	{
		return 0;
	}
	for (int i = 0; i < len; i++)
	{
		if (~(str[i]>> 8) != 0)
		{
		return 0; //�����Ǻ���
		}
	}
	return 1;
}

/*�����ѯ*/
void search_Flight() 
{	
	FILE *Admin_list,*Flight_list;//�ֱ�򿪹���Ա�ļ��뺽���ļ���ָ��
	Admin_list = fopen("��ǰ����Ա.txt", "r");//�򿪹���Ա�ļ�
	if (Admin_list == NULL) {
		exit(1);
	}
	Admination Admin;//���ڴ��浱ǰ����Ա��Ϣ
	fscanf(Admin_list, "%s%s%s%s%s", Admin.ID, Admin.Company, Admin.Name, Admin.mail, Admin.Password);
	fclose(Admin_list);//�رչ���Ա�ļ�
	
	Flight_list = fopen("9.1������Ϣ.txt", "r");//�򿪺�����Ϣ�ļ�
	if (Flight_list == NULL) {
		exit(1);
	}
	FlightInfo Flight;//���ڴ��浱ǰ������Ϣ

	int cons = 0;//�����ж����к������Ƿ��иù�˾����
	printf("�����  ���ʱ��  ����ʱ��  ������  Ŀ�ĵ�  ����  ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ  ���ò���Ʊ  ����Ա1  ����Ա2  ���չ�˾ ׼����\n");
	printf("\n");

	//�������к�����Ϣ���������Ա������˾�Ƚ�
	while (fscanf(Flight_list, "%s%s%s%s%s%s%d%d%d%d%s%s%s%s", Flight.Flightnum, Flight.Flighttime_up,
		Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, &Flight.Firstfare,
		&Flight.Economfare, &Flight.Firstrest, &Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2, 
		Flight.Company,Flight.Ontimerate) != EOF)
	{
		if ( strcmp( Admin.Company , Flight.Company ) == 0)//��ǰ���������Ա��ͬһ��˾
		{
			
			printf(" %6s\t   %6s\t   %6s\t   %6s\t   %6s\t   %6s\t   %5d\t   %5d\t  %5d\t   %5d\t    %3s\t  %3s\t  %6s\n", 
				Flight.Flightnum, Flight.Flighttime_up,
					Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, Flight.Firstfare,
					Flight.Economfare, Flight.Firstrest, Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2, Flight.Company);//�����ǰ������Ϣ
			cons = 1;
		}
	}
	//��ǰ���к������޸ù�˾����
	if (!cons) {
		printf("���޸ù�˾������Ϣ\n");
	}
	fclose(Flight_list);//�رպ�����Ϣ�ļ�

}

/*ѡ�����*/
char* choose_City() 
{
	FILE *fp = fopen("data/city/ʡ��.txt", "r");
	if (fp == NULL) {
		exit(1);
	}
	int num;/*���ڼ�¼ʡ�����*/
	char  Place[50];
	printf("*    ��ѡ��ʡ�ݻ�����Ŀ�ĳ����������ƣ�\n");
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
			int cnt;/*���ڼ�¼�������*/
			if (In[1] >= '0'&&In[1] <= '9')
			{
				cnt = (In[0] - '0') * 10 + In[1] - '0';
			}
			else
			{
				cnt = In[0] - '0';
			}
			fp = fopen("data/city/ʡ��.txt", "r");
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
							printf("*    ��ѡ�������Ż�����Ŀ�ĳ����������ƣ�\n");
							printf("*    ���롰*��ȡ��ѡ��\n");
							printf("*    ���롰���ء�������һ����\n");
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
									if (!strcmp(In, "����")) {
										break;
									}
									FILE *tp = fopen("data/city/��������.txt", "r");
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
									printf("�޷�ѡ��ó��У�������ѡ��\n");
								}
								else
								{
									printf("�������������ѡ��\n");
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
				FILE *tp = fopen("data/city/��������.txt", "r");
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
				printf("*    �޷�ѡ��ó��У�������ѡ��\n");
				continue;
			}
			else
			{
				printf("*    �������������ѡ��\n");
				continue;
			}

		}
	}
}

/*���ɺ����*/
char *build_Flightnum(FlightInfo Now, FlightInfo Past)
{	
	memset(Now.Flightnum, '\0', sizeof Now.Flightnum);
	/*ǰ��λ���ɹ�˾����*/
	FILE *Cmy = fopen("���չ�˾.txt", "r");
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
	/*��������λ�ֱ�Ϊ��������Ŀ�ĵصĵ�������*/
	FILE *City = fopen("data/city/��������.txt", "r");
	if (City == NULL) {
		exit(1);
	}
	char Land[50], Land_sig[10];
	int cnt = 2;//�����ж�Ŀ�ĵ�������ش����Ƿ��������
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

	/*���ɺ���λ����ţ�����λΪ������ţ�����λ����ż��ʾȥ��*/
	if (strcmp(Now.Company, Past.Company) == 0)
	{	
		/*�������������յ�ǡ�õߵ���˵��Ϊȥ�س̺��ֻ࣬�ı����λ*/
		if (strcmp(Now.Downland, Past.Startland) == 0 && strcmp(Now.Startland, Past.Downland) == 0)
		{	
			/*��ֹ������*/
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


		/*����յ���ͬ��˵��Ϊ�ú��չ�˾�ڸ���·�����ж�������*/
		else if (strcmp(Now.Downland, Past.Downland) == 0 && strcmp(Now.Startland, Past.Startland) == 0)
		{
			/*��ֹ������*/
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

/*���뺽��*/
int in_Put(FlightInfo* Flight_new)
{
	/*���뺽����Ϣ*/
	FlightInfo Now;
	/*����Ԥ����*/
	char in[10][50] = { {"���ʱ��"},{"����ʱ��"},{"������"},{"Ŀ�ĵ�"},{"���� "},
						{"ͷ�Ȳռ۸�" }, {"���òռ۸�"}, {"����Ա1"}, {"����Ա2"}};
	printf("�����뺽����Ϣ��\n�������Ӧ��Ϣ��Ž������\n");
	int last = 9,sum = 9, Has_in_put;/*last����δ����Ϣ������sum����ǰδ����Ϣ������Has_in_put������������Ϣ���*/

	while (sum > 0)
	{
		
		for (int i = 0; i < 9; i++)
		{
			if (in[i][0] != '\0')
			{
				printf("*    %d. %s       \n", i, in[i]);
			}
		}
		printf("���롰*��ȡ������\n\n");

		char num,ch;
		ch = getchar();
		scanf("%c", &num);
		if (in[num - '0'][0] == '\0') {
			num = '-';
		}
		
		switch (num)
		{
		case '*':/*ȡ������*/
		{
			printf("*    ��ȡ������\n");
			return 0;
		}
		case '0':/*���ʱ��*/
		{
			while(1){
				printf("*    ���롰*��ȡ������\n");
				printf("*    ���ʱ�䣺������xx:xx��24ʱ�ƣ�  ");
				char str[50];/*����ʱ��*/
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("*    ��ȡ������\n");
					break;
				}
				else
				{
					int len = strlen(str);
					if (len != 5 || str[2] != ':')
					{
						printf("*    ���벻�Ϸ�\n");
						continue;
					}
					else {
						strcpy(Now.Flighttime_up, str);
						printf("\n*    ����ɹ�\n");
						sum--;
						break;
					}
				}
			}
			break;
		}
		case '1':/*����ʱ��*/
		{
			while (1) {
				printf("*    ���롰*��ȡ������\n");
				printf("*    ����ʱ�䣺������xx;xx��24ʱ�ƣ�  ");
				char str[50];/*����ʱ��*/
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*     ��ȡ������\n");
					break;
				}
				else
				{
					int len = strlen(str);
					if (len != 5 || str[2] != ':')
					{
						printf("*    ���벻�Ϸ�\n");
						continue;
					}
					else {
						sum--;
						printf("\n*    ����ɹ�\n");
						strcpy(Now.Flighttime_down, str);
						break;
					}
				}
			}
			break;
		}
		/*������*/
		case '2':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ��ѡ������أ� ");
			char str[50];
			strcpy(str, choose_City());
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
				break;
			}
			else
			{
				sum--;
				printf("\n*    ����ɹ�\n");
				strcpy(Now.Startland, str);
			}
			break;
		}
		/*Ŀ�ĵ�*/
		case '3':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    Ŀ�ĵأ� ");
			char str[50];
			strcpy(str, choose_City());
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
				break;
			}
			else
			{
				sum--;
				printf("\n*    ����ɹ�\n");
				strcpy(Now.Downland, str);
			}
			break;
		}
		/*����*/
		case '4':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ���ͣ� (������������ƣ�����Ϊ��ѡ����)\n");
			printf("*    1.JET\n");
			printf("*    2.�տ�320\n");
			printf("*    3.�տ�321\n");
			printf("*    4.����737\n");
			printf("*    ��������ͣ�");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
				break;
			}
			else
			{
				sum--; 

				printf("\n*    ����ɹ�\n");
				strcpy(Now.Flighttype, str);
			}
			break;
		}
		/*ͷ�Ȳռ۸�*/
		case '5':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ͷ�Ȳռ۸� ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
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
				printf("\n*    ����ɹ�\n");
				sum--;
			}
			break;
		}
		/*���òռ۸�*/
		case '6':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ���òռ۸� ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
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
				printf("\n*    ����ɹ�\n");
				sum--;
			}
			break;
		}
		/*����Ա1*/
		case '7':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ����Ա1�� ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
				break;
			}
			int flag = 1;//�����ж��Ƿ�����ɹ�
			/*�ж������Ƿ�Ϊ���ģ�������������*/
			while (!is_Chinese(str))
			{
				printf("*    ���벻�Ϸ�������������\n");
				printf("*    ���롰*��ȡ������\n");
				printf("*    ����Ա1�� ");
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*    ��ȡ������\n");
					flag = 0;
					break;
				}
			}
			/*����ɹ�*/
			if (flag)
			{
				strcpy(Now.Pilot_1, str);
				sum--;
				printf("\n*    ����ɹ�\n");
				break;
			}
			break;
		}
		/*����Ա2*/
		case '8':
		{
			printf("*    ���롰*��ȡ������\n");
			printf("*    ����Ա2�� ");
			char str[50];
			scanf("%s", str);
			if (str[0] == '*')
			{
				printf("\n*    ��ȡ������\n");
				break;
			}
			int flag = 1;//�����ж��Ƿ�����ɹ�
			/*�ж������Ƿ�Ϊ���ģ�������������*/
			while (!is_Chinese(str))
			{
				printf("*    ���벻�Ϸ�������������\n");
				printf("*    ���롰*��ȡ������\n");
				printf("*    ����Ա2�� \n");
				scanf("%s", str);
				if (str[0] == '*')
				{
					printf("\n*    ��ȡ������\n");
					flag = 0;
					break;
				}
			}
			/*����ɹ�*/
			if (flag)
			{
				strcpy(Now.Pilot_2, str);
				printf("\n*    ����ɹ�\n");
				sum--;
				break;
			}
			break;
		}
		default: 
		{
			printf("�������룬����������.\n");
			break;
		}
		}
		/*�ж��Ƿ��Ѿ��ɹ���д��һ�����ݣ����ɹ����򽫸���ɾȥ*/
		if (num >= '0'&&num <= '8'&&last - sum == 1)
		{
			last--;
			Has_in_put = num - '0';
			memset(in[Has_in_put], '\0', sizeof in[Has_in_put]);
			
		}
	}
	if (!sum)
	{
		printf("*    �����ɣ�\n");
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

/*�ж�ʱ���Ƿ��ͻ*/
int judge_Time(FlightInfo Now,FlightInfo Past) 
{
	/*������ʱ���*/
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
	/*��ǰ����ʱ������ʷ���ൽ��ʱ��֮ǰ������ǰ����ʱ������ʷ�������ʱ��֮�����г�ͻ*/
	 if (Time_1<0&&Time_2>0)
	 {
		return 0;
	 }
	 /*�޳�ͻ*/
	 return 1;
	
}

/*�жϵص��Ƿ��ͻ*/
int judge_Land(FlightInfo Now, FlightInfo Past)
{	
	/*��ǰ������������ʷ������ص�*/
	if (strcmp(Now.Downland, Past.Startland) == 0)
	{
		/*������ʱ��*/
		int	Hour = (Now.Flighttime_up[0] - '0') * 10 + (Now.Flighttime_up[1] - '0');
		int	Min = (Now.Flighttime_up[3] - '0') * 10 + (Now.Flighttime_up[4] - '0');
		Hour -= (Past.Flighttime_down[0] - '0') * 10 + (Past.Flighttime_down[1] - '0');
		Min -= (Past.Flighttime_down[3] - '0') * 10 + (Past.Flighttime_down[4] - '0');
		int Time = Hour * 60 - Min;
		/*���ʱ�����30min����ص㲻��ͻ*/
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

/*�޸ĺ�����Ϣ*/
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
		printf("*    ��������Ҫ�޸���Ϣ�����:\n");
		printf("*    1.����: %s\n*    2.ͷ�Ȳ�Ʊ��: %d\n",Now.Flighttype, Now.Firstfare);
		printf("*    3.���ò�Ʊ��: %d\n*    4.��ɵ�: %s\n*    5.�����: %s\n", Now.Economfare, Now.Startland, Now.Downland);
		printf("*    6.���ʱ��: %s\n*    7.����ʱ��: %s\n*    8.����Ա1: %s\n*    9.����Ա2: %s\n\n", Now.Flighttime_up, Now.Flighttime_down, Now.Pilot_1,Now.Pilot_2);
		printf("*    0.����޸�\n\n");
		printf("*    *.ȡ���޸�\n\n");
		scanf("%c", &ch);
		switch (ch)
		{
			case '1':
			{	
				printf("*    1.����:\n");
				scanf("%s", Now.Flighttype);
				printf("*    �޸ĳɹ�\n\n");
				break;

			}
			case '2':
			{
				printf("*    2.ͷ�Ȳ�Ʊ��:\n");
				scanf("%d", &Now.Firstfare);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '3':
			{
				printf("*    3.���ò�Ʊ��:\n");
				scanf("%d", &Now.Economfare);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '4':
			{
				printf("*    4.��ɵ�:\n");
				scanf("%s", Now.Startland);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '5':
			{
				printf("*    5.�����:\n");
				scanf("%s", Now.Downland);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '6':
			{
				printf("*    6.���ʱ��:\n");
				scanf("%s", Now.Flighttime_up);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '7':
			{
				printf("*    7.����ʱ��:\n");
				scanf("%s", Now.Flighttime_down);
				printf("\n�޸ĳɹ�\n\n");
			}
			case '8':
			{
				printf("*    8.����Ա1:\n");
				scanf("%s", Now.Pilot_1);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '9':
			{
				printf("*    9.����Ա2:\n");
				scanf("%s", Now.Pilot_2);
				printf("\n�޸ĳɹ�\n\n");
				break;
			}
			case '0':
			{
				printf("*    �޸ĳɹ�\n\n");
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
				printf("*    ��ȡ���޸�\n");
				return;
				break;
			}
			default:
			{
				printf("*    ����ָ�����������\n");
				break;
			}

		}
	}
	return ;
}

/*�ж��޸ķ���Ա��Ϣ�Ƿ���Ҫ��֤*/
int modify_Polit(int On_plane_1, int On_plane_2, FlightInfo *Flight_new)
{
	/*2�ŷ���Ա���뺽��*/
	if (On_plane_1 != 0)
	{
		while (1)
		{
			printf("����������2�ŷ���Ա\n����\"0\"ȡ������¼��\n");
			char str[1000];
			scanf("%s", str);
			if (str[0] == '0')
			{
				printf("��ȡ�����\n");
				return 1;
				break;
			}
			else if (!is_Chinese(str))
			{
				printf("���벻�Ϸ�������������\n");
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
	/*1�ŷ���Ա���뺽��*/
	else if (On_plane_2 != 0)
	{
		while (1)
		{
			printf("����������1�ŷ���Ա\n����\"0\"ȡ������¼��\n");
			char str[1000];
			scanf("%s", str);
			if (str[0] = '0')
			{
				printf("��ȡ�����\n");
				return 1;
				break;
			}
			else if (!is_Chinese(str))
			{
				printf("���벻�Ϸ�������������\n");
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
	/*��������Ա�����뺽��*/
	else
	{
		while (1)
		{
			printf("������������������Ա\n����\"0\"ȡ������¼��\n");
			char str_1[1000], str_2[1000];
			printf("1�ŷ���Ա    2�ŷ���Ա\n");
			scanf("%s", str_1);
			if (str_1[0] = '0')
			{
				printf("��ȡ�����\n");
				return 1;
				break;
			}
			scanf("%s", str_2);
			if (!is_Chinese(str_1) || !is_Chinese(str_2))
			{
				printf("���벻�Ϸ�������������\n");
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

/*������һ���������ж��Ƿ���Ҫ��֤*/
int reserve_Flight(FlightInfo* Flight_new)
{
	printf("*    �������¼��!\n");
	while (1)
	{
		printf("*    ����\"1\"����������Ϣ\n*    ����\"2\"�޸ĺ�����Ϣ\n*    ����\"0\"ȡ����Ӻ�����Ϣ\n\n");
		/*���������Ϣ*/
		printf("�����    ���ʱ��         ����ʱ��        ������  Ŀ�ĵ�   ����       ͷ�Ȳռ۸�  ���òռ۸�   ͷ�Ȳ���Ʊ    ���ò���Ʊ   ����Ա1       ����Ա2          ���չ�˾\n");
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
			/*����������Ϣ����������Ϣ��ӵ������ļ����һ��*/
			case '1':
			{
				FILE *fp = fopen("data/flight/9.9������Ϣ.txt", "a");
				if (fp == NULL) {
					exit(1);
				}

				memset(Flight_new->Ontimerate, '\0', sizeof Flight_new->Ontimerate);
				/*���׼����*/
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
				printf("*    �����ɹ���\n");
				return 1;
				break ;
			}
			/*�޸ĺ���*/
			case '2':
			{
				modify_Flight(Flight_new);
				return 0;
				break;
			}
			case '0':
			{
				printf("*    ��ȡ�����\n");
				return 1;
				break;
			}
			default:
			{
				printf("*    ����ָ�����������\n");
				break;
			}

		}

	}
}

/*��Ӻ���*/
void add_Flight()
{
	FlightInfo Flight_new, Flight;//�ֱ𴢴�����Ӻ�����Ϣ����ʷ������Ϣ
	FILE *Admin_list;//�򿪵�ǰ����Ա�ļ�
	Admin_list = fopen("��ǰ����Ա.txt", "r");//�򿪹���Ա�ļ�
	if (Admin_list == NULL) {
		exit(1);
	}
	Admination Admin;//���ڴ��浱ǰ����Ա��Ϣ
	fscanf(Admin_list, "%s%s%s%s%s", Admin.ID, Admin.Company, Admin.Name, Admin.mail, Admin.Password);
	fclose(Admin_list);//�رչ���Ա�ļ�

	strcpy(Flight_new.Company, Admin.Company);//��֤ͬһ��˾
	Flight_new.Economrest = 150;
	Flight_new.Firstrest = 50;
	int Is_ok = in_Put(&Flight_new);

	
	if (Is_ok) {
		while (1)
		{

			/*��ѯ��ʷ������Ϣ*/
			FILE *fp = fopen("data/flight/9.9������Ϣ.txt", "r");
			if (fp == NULL) {
				exit(1);
			}
			int Judge_time = 0, Judge_land = 0;//�����жϷ���Աʱ���·���Ƿ��ͻ
			int On_plane_1, On_plane_2;//�����жϷ���Ա�Ƿ������������

			while (fscanf(fp, "%s%s%s%s%s%s%d%d%d%d%s%s%s%s", Flight.Flightnum, Flight.Flighttime_up,
				Flight.Flighttime_down, Flight.Startland, Flight.Downland, Flight.Flighttype, &Flight.Firstfare,
				&Flight.Economfare, &Flight.Firstrest, &Flight.Economrest, Flight.Pilot_1, Flight.Pilot_2,
				Flight.Company,Flight.Ontimerate) != EOF)
			{

				//�жϷ���Աʱ���·���Ƿ��ͻ
				On_plane_1 = strcmp(Flight.Pilot_1, Flight_new.Pilot_1);
				On_plane_1 *= strcmp(Flight.Pilot_2, Flight_new.Pilot_1);
				On_plane_2 = strcmp(Flight.Pilot_1, Flight_new.Pilot_2);
				On_plane_2 *= strcmp(Flight.Pilot_2, Flight_new.Pilot_2);
				/*���з���Ա��������������*/
				if (On_plane_1 == 0 || On_plane_2 == 0)
				{
					Judge_time = judge_Time(Flight_new, Flight);
					//ʱ�䲻��ͻ
					if (Judge_time) {
						Judge_land = judge_Land(Flight_new, Flight);

						//·�߲���ͻ
						if (Judge_land)
						{

							strcpy(Flight_new.Flightnum, build_Flightnum(Flight_new, Flight));

							continue;
						}

						//·�߳�ͻ
						else
						{
							/*�ж���λ����Ա�޷�ִ�д˴κ���*/
							if (On_plane_1 != 0)
							{
								printf("2�ŷ���Ա");
							}
							else if (On_plane_2 != 0)
							{
								printf("1�ŷ���Ա");
							}
							else
							{
								printf("��������Ա��");
							}
							printf("·�߳�ͻ�������°��ŷ���Ա.\n");
							break;
						}
					}
					//ʱ���ͻ
					else
					{
						/*�ж���λ����Ա�޷�ִ�д˴κ���*/
						if (On_plane_1 != 0)
						{
							printf("2�ŷ���Ա");
						}
						else if (On_plane_2 != 0)
						{
							printf("1�ŷ���Ա");
						}
						else
						{
							printf("��������Ա��");
						}
						printf("ʱ���ͻ�������°��ŷ���Ա.\n");
						break;
					}

				}
				/*����ͻ*/
				else
				{
					Judge_land = 1;
					Judge_time = 1;
					strcpy(Flight_new.Flightnum, build_Flightnum(Flight_new, Flight));
					//printf("%s\n", Flight_new.Flightnum);
				}
				
			}
			fclose(fp);

			int flag = 1;//�ж��Ƿ���Ҫ������֤������Ϣ
			/*����з���Ա·�߻�ʱ���ͻ*/
			if (Judge_land * Judge_time == 0)
			{
				/*�޸ķ���Ա��Ϣ�����ж��Ƿ���Ҫ��֤*/
				flag = modify_Polit(On_plane_1, On_plane_2, &Flight_new);
			}
			/*����ͻ*/
			else
			{
				/*������һ���������ж��Ƿ���Ҫ��֤*/
				flag = reserve_Flight(&Flight_new);
			}
			if (flag)//����Ҫ��֤������Ϣ
			{
				break;
			}
		}
	}
}
