
#pragma warning(disable : 4996)
#include "���ݽṹ.h"
#ifndef ����Ա�����ѯ�����_h
#define ����Ա�����ѯ�����_h


/*�ж��ַ����Ƿ�Ϊ����*/
int is_Chinese(char*);

/*��ѯ��ǰ��˾���к���*/
void search_Flight();

/*ѡ�����*/
char* choose_City();

/*�����������Ϣ���������*/
char *build_Flightnum(FlightInfo, FlightInfo);

/*���뺽����Ϣ*/
int in_Put(FlightInfo*);

/*�ж�ʱ���Ƿ��ͻ*/
int judge_Time(FlightInfo , FlightInfo );

/*�жϵص��Ƿ��ͻ*/
int judge_Land(FlightInfo , FlightInfo );

/*�޸ĺ�����Ϣ*/
void modify_Flight(FlightInfo*);

/*�޸ķ���Ա����*/
int modify_Polit(int , int , FlightInfo* );

/*�����ɺ�ѡ�������һ��*/
int reserve_Flight(FlightInfo*);

/*��Ӻ�������*/
void add_Flight();


#endif 

