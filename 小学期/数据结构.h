#pragma once
#define MAX1 200

typedef struct
{
	char Flightnum[20];//�����
	char Name[20];//�˿�����
	char ID[20];//���֤
	char Company[20];//���չ�˾
	char Seatnum[20];//��λ��
	char Time_date[20];//��������ʱ��-����
	char Time_min[20];//���������ʱ��-�֡��� 
	char payername[20];//��������ĸ�����
	char FlyTime[20];//�������
	char Flighttime_up[20];//���ʱ��
	char Flighttime_down[20];//����ʱ��
	char Startland[20];//������
	char Downland[20];//Ŀ�ĵ�
	char Flighttype[20];//�ɻ�����
	char Pilot_1[20];//����Ա1����
	char Pilot_2[20];//����Ա2����
	char SeatType[20];//��λ����

}Passenger;//һ��������������Ϣ
typedef struct
{
	Passenger a[2000];    //��¼�ܹ�Ʊ����
	int count;               //��¼�������
}List_P;
//�˿ͽṹ


//�û��ṹ
typedef struct
{
	char ID[20];//�û���½ID
	char Name[20];//�û�����
	char Sex[20];//�û��Ա�
	char Phone[20];//�û��ֻ���
	char PassWord[20];//�û�����
	char Email[20];//����
	char mail[20];
    char *BuyTime;//��Ʊʱʱ��
	int Odernum; //��Ʊ��
   
}User;

typedef struct
{
	User u[50];    //��¼���û�
	int count;     //��¼�û���
}List_U;

//����Ա�ṹ
typedef struct
{
	char ID[20];//����ԱID
	char Name[20];//����Ա����
	char Company[20];//����Ա���չ�˾
	char mail[20];//����Ա����
	char Password[20];//����Ա����
	

}Admination;


typedef struct
{
	Admination a[50];    //��¼�ܹ���Ա
	int count;               //��¼����Ա��
}List_A;


//����ṹ
typedef struct
{
	char Company[20];//���չ�˾
	char Flightnum[20];//�����
	char Flighttime_up_date[20];//��������
	char Flighttime_down_date[20];//��������
	char Flighttime_up[20];//����ʱ��
	char Flighttime_down[20];//����ʱ��
	char Startland[20];//������
	char Downland[20];//Ŀ�ĵ�
	double Rate;//������
	char Flighttype[20];//�ɻ�����
	int Economfare;//���ò�Ʊ��
	int Firstfare;//ͷ�Ȳ�Ʊ��
	char Pilot_1[20];//����Ա1����
	char Pilot_2[20];//����Ա2����
	int Economrest;//���ò���Ʊ
	int Firstrest;//ͷ�Ȳ���Ʊ
	int Ordernum;//���������ܣ�
	int Ordernum_econ;//���òն�����
	int Ordernum_firs;//ͷ�Ȳն�����
	int Income;//������
	char Ontimerate[20];

}FlightInfo;


//��������
typedef struct
{
	FlightInfo Flight[150];   //��������150
	int count;               //��¼�������
}List_F;